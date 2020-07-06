// [[Rcpp::depends(cgal4h, sf)]]
#include <sf.h>

#include <Rcpp.h>

#include "PolygonRepair.h"

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


// borrowed from sf source code, (c) Edzer Pebesma
std::vector<OGRGeometry *> ogr_geometry_from_sfc(Rcpp::List sfc) {

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
Rcpp::List sfc_from_ogr_geometry(std::vector<OGRGeometry *> g, bool destroy = false) {
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

// [[Rcpp::export]]
Rcpp::List CPL_prepair_oddeven(Rcpp::List sfc, double min_area) {

    std::vector<OGRGeometry *> input = ogr_geometry_from_sfc(sfc);
    PolygonRepair prepair;
    OGRMultiPolygon *out_polygons;

    for (size_t i = 0; i < input.size(); i++) {
        OGRGeometry *g = input[i];
        if (!g->IsEmpty()) {
            out_polygons = prepair.repairOddEven(g, 0);
            if (min_area > 0) {
                prepair.removeSmallPolygons(out_polygons, min_area);
            }
            input[i] = out_polygons;
        }
    }

    return sfc_from_ogr_geometry(input);
}

// [[Rcpp::export]]
Rcpp::List CPL_prepair_setdiff(Rcpp::List sfc, double min_area) {

    std::vector<OGRGeometry *> input = ogr_geometry_from_sfc(sfc);
    PolygonRepair prepair;
    OGRMultiPolygon *out_polygons;

    for (size_t i = 0; i < input.size(); i++) {
        OGRGeometry *g = input[i];
        if (!g->IsEmpty()) {
            out_polygons = prepair.repairPointSet(g, 0);
            if (min_area > 0) {
                prepair.removeSmallPolygons(out_polygons, min_area);
            }
            input[i] = out_polygons;
        }
    }

    return sfc_from_ogr_geometry(input);
}

// [[Rcpp::export]]
Rcpp::NumericVector CPL_robustness(Rcpp::List sfc) {

    std::vector<OGRGeometry *> input = ogr_geometry_from_sfc(sfc);
    Rcpp::NumericVector out(input.size(), NA_REAL);
    PolygonRepair prepair;

    for (size_t i = 0; i < input.size(); i++) {
        OGRGeometry *g = input[i];
        if (!g->IsEmpty())
            out[i] = prepair.computeRobustness(g);
    }
    return out;
}
