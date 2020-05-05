#include "PolygonRepair.h"

#include <Rcpp.h>

// [[Rcpp::depends(sf)]]
#include <sf.h>

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

OGRGeometry *single_ogr_from_sfc(Rcpp::List sfc) {
  OGRGeometry *g;
  Rcpp::List wkblst = sf::CPL_write_wkb(sfc, false);
  Rcpp::RawVector wkb = wkblst[0];
  OGRErr err = OGRGeometryFactory::createFromWkb(&(wkb[0]), NULL, &g, wkb.length(), wkbVariantIso);
  if (err != OGRERR_NONE) {
    if (g != NULL)
      OGRGeometryFactory::destroyGeometry(g);
    handle_error(err);
  }
  return g;
}

Rcpp::List sfc_from_single_ogr(OGRGeometry *g, bool destroy = false) {
  OGRwkbGeometryType type = wkbGeometryCollection;
  Rcpp::List crs = create_na_crs();
  type = g->getGeometryType();
  Rcpp::RawVector raw(g->WkbSize());
  g->exportToWkb(wkbNDR, &(raw[0]), wkbVariantIso);
  if (destroy)
    OGRGeometryFactory::destroyGeometry(g);
  Rcpp::List ret = sf::CPL_read_wkb(Rcpp::List::create(raw), false, false);
  ret.attr("crs") = crs;
  ret.attr("class") = "sfc";
  return ret;
}

Rcpp::List CPL_sfc_from_wkt2(Rcpp::CharacterVector wkt) {
  OGRGeometry *g;
  char *wkt_str = wkt(0);
  handle_error(OGRGeometryFactory::createFromWkt((const char*) wkt_str, NULL, &g));
  return sfc_from_single_ogr(g, true);
}

// [[Rcpp::export]]
Rcpp::List CPL_prepair(Rcpp::List sfc, double min_area, bool point_set) {

  OGRGeometry *geometry = single_ogr_from_sfc(sfc);
  PolygonRepair prepair;
  OGRMultiPolygon *out_polygons;

  if (point_set) {
    out_polygons = prepair.repairPointSet(geometry, 0);
  } else {
    out_polygons = prepair.repairOddEven(geometry, 0);
  }

  if (min_area > 0) {
    prepair.removeSmallPolygons(out_polygons, min_area);
  }

  char *output_wkt;
  out_polygons->exportToWkt(&output_wkt);
  return CPL_sfc_from_wkt2(output_wkt);
}
