#include "PolygonRepair.h"

#include <Rcpp.h>

// [[Rcpp::depends(sf)]]
#include <sf.h>

OGRGeometry * single_ogr_from_sfc(Rcpp::List sfc) {
  OGRGeometry *g;
  Rcpp::List wkblst = sf::CPL_write_wkb(sfc, false);
  Rcpp::RawVector wkb = wkblst[0];
  OGRGeometryFactory::createFromWkb(&(wkb[0]), NULL, &g, -1, wkbVariantIso);
  return g;
}

Rcpp::List sfc_from_single_ogr(OGRGeometry * g, bool destroy = false) {
  OGRwkbGeometryType type = wkbGeometryCollection;
  type = g->getGeometryType();
  Rcpp::RawVector raw(g->WkbSize());
  g->exportToWkb(wkbNDR, &(raw[0]), wkbVariantIso);
  if (destroy)
    OGRGeometryFactory::destroyGeometry(g);
  Rcpp::List ret = sf::CPL_read_wkb(Rcpp::List::create(raw), false, false);
  ret.attr("class") = "sfc";
  return ret;
}

Rcpp::List CPL_sfc_from_wkt2(Rcpp::CharacterVector wkt) {
  OGRGeometry *g;
  char *wkt_str = wkt(0);
  OGRGeometryFactory::createFromWkt((const char*) wkt_str, NULL, &g);
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
