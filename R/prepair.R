#' Polygon repair
#'
#' Automatically repair single polygons (according to the OGC Simple Features / ISO19107 rules) using a constrained triangulation approach.
#'
#' @param x object of class \code{sf}, \code{sfc} or \code{sfg}
#' @param min_area mininum area to keep in output
#' @param point_set if TRUE use the point set difference algorithm for the rings (outer-inner)
#' by default (point_set = FALSE) the odd-even algorithm is used
#'
#' @examples
#' library(sf)
#' p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
#' st_is_valid(p1)
#' st_prepair(p1)
#' st_is_valid(st_prepair(p1))
#' @seealso \code{sf::st_make_valid} for another approach at fixing broken polygons
#'
#' @importFrom sf st_geometry st_set_geometry st_geometry_type st_geometrycollection st_crs st_sfc
#'
#' @export
st_prepair <- function(x, min_area = 0, point_set = FALSE) {
  UseMethod("st_prepair")
}

#' @export
st_prepair.sfc <- function(x, min_area = 0, point_set = FALSE) {
  assert_polygon_type(x)
  st_sfc(CPL_prepair(x, min_area, point_set), crs = st_crs(x))
}

#' @export
st_prepair.sf <- function(x, min_area = 0, point_set = FALSE) {
  sf::st_set_geometry(x, st_prepair(sf::st_geometry(x), min_area, point_set))
}

#' @export
st_prepair.sfg <- function(x, min_area = 0, point_set = FALSE) {
  first_sfg_from_sfc(st_prepair(sf::st_sfc(x), min_area, point_set))
}

#' @noRd
assert_polygon_type <- function(x) {
  if (!any(sf::st_geometry_type(x) %in% c("POLYGON", "MULTIPOLYGON"))) {
    stop("Only POLYGON or MULTIPOLYGON are supported", call. = FALSE)
  }
}


#' @noRd
first_sfg_from_sfc <- function(x) {
  if (length(x) == 0) {
    sf::st_geometrycollection()
  } else {
    x[[1]]
  }
}
