#include "PolygonRepair.h"

#include <Rcpp.h>

// [[Rcpp::depends(sf)]]
#include <sf.h>

// borrowed from sf source code, (c) Edzer Pebesma
void handle_error(OGRErr err) {
	if (err != OGRERR_NONE) {
		switch (err) {
			case OGRERR_NOT_ENOUGH_DATA:
				Rcpp::Rcout << "OGR: Not enough data " << std::endl;
				break;
			case OGRERR_UNSUPPORTED_GEOMETRY_TYPE:
				Rcpp::Rcout << "OGR: Unsupported geometry type" << std::endl;
				break;
			case OGRERR_CORRUPT_DATA:
				Rcpp::Rcout << "OGR: Corrupt data" << std::endl;
				break;
			case OGRERR_FAILURE:
				Rcpp::Rcout << "OGR: index invalid?" << std::endl;
				break;
			default:
				Rcpp::Rcout << "Error code: " << err << std::endl;
		}
		Rcpp::stop("OGR error");
	}
}

Rcpp::List create_na_crs() {
  Rcpp::List crs(2);
  crs(0) = Rcpp::CharacterVector::create(NA_STRING);
  crs(1) = Rcpp::CharacterVector::create(NA_STRING);
  Rcpp::CharacterVector nms(2);
  nms(0) = "input";
  nms(1) = "wkt";
  crs.attr("names") = nms;
  crs.attr("class") = "crs";
  return crs;
}

// borrowed from sf source code, (c) Edzer Pebesma
std::vector<OGRGeometry *> ogr_from_sfc2(Rcpp::List sfc) {

  Rcpp::List wkblst = sf::CPL_write_wkb(sfc, false);
  std::vector<OGRGeometry *> g(sfc.length());

  for (int i = 0; i < wkblst.length(); i++) {
    Rcpp::RawVector r = wkblst[i];
    OGRErr err = OGRGeometryFactory::createFromWkb(&(r[0]), NULL, &(g[i]),
						   r.length(), wkbVariantIso);
    if (err != OGRERR_NONE) {
      if (g[i] != NULL)
	OGRGeometryFactory::destroyGeometry(g[i]);
      handle_error(err);
    }
  }
  return g;
}

// borrowed from sf source code, (c) Edzer Pebesma
Rcpp::List sfc_from_ogr2(std::vector<OGRGeometry *> g, bool destroy = false) {
  OGRwkbGeometryType type = wkbGeometryCollection;
  Rcpp::List lst(g.size());
  for (size_t i = 0; i < g.size(); i++) {
    if (g[i] == NULL)
      g[i] = OGRGeometryFactory::createGeometry(type);
    else
      type = g[i]->getGeometryType();
    Rcpp::RawVector raw(g[i]->WkbSize());
    handle_error(g[i]->exportToWkb(wkbNDR, &(raw[0]), wkbVariantIso));
    lst[i] = raw;
    if (destroy)
      OGRGeometryFactory::destroyGeometry(g[i]);
  }
  Rcpp::List ret = sf::CPL_read_wkb(lst, false, false);
  ret.attr("class") = "sfc";
  return ret;
}

// borrowed from sf source code, (c) Edzer Pebesma
Rcpp::List CPL_sfc_from_wkt2(Rcpp::CharacterVector wkt) {
	std::vector<OGRGeometry *> g(wkt.size());
	OGRGeometryFactory f;
	for (int i = 0; i < wkt.size(); i++) {
		char *wkt_str = wkt(i);
#if GDAL_VERSION_MAJOR <= 2 && GDAL_VERSION_MINOR <= 2
		handle_error(f.createFromWkt(&wkt_str, NULL, &(g[i])));
#else
		handle_error(f.createFromWkt( (const char*) wkt_str, NULL, &(g[i])));
#endif
	}
	return sfc_from_ogr2(g, true);
}

// [[Rcpp::export]]
Rcpp::List CPL_prepair(Rcpp::List sfc, double min_area, bool point_set) {

  std::vector<OGRGeometry *> input = ogr_from_sfc2(sfc);
  Rcpp::CharacterVector wkt_v(input.size());
  PolygonRepair prepair;
  OGRMultiPolygon *out_polygons;

  for (size_t i = 0; i < input.size(); i++) {

    if (point_set) {
      out_polygons = prepair.repairPointSet(input[i], 0);
    } else {
      out_polygons = prepair.repairOddEven(input[i], 0);
    }

    if (min_area > 0) {
      prepair.removeSmallPolygons(out_polygons, min_area);
    }

    char *output_wkt;
    out_polygons->exportToWkt(&output_wkt);
    wkt_v[i] = output_wkt;
  }
  return CPL_sfc_from_wkt2(wkt_v);
}
