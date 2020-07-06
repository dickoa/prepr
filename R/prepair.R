#' Automatic repair of single polygons
#'
#' `st_prepair` repairs single polygons according to the international standards ISO 19107
#'  using a constrained triangulation approach.
#'
#' @param x object of class `sf`, `sfc` or `sfg`, it only works POLYGON or MULTIPOLYGON are supported
#' @param algorithm character; algorithm used to repair the polygon. oddeven (default) or setdiff.
#' More on these two algorithm details.
#' @param min_area numeric; all polygons with areas smaller than `min_area` will be removed.

#' @details
#' `st_prepair` supports two algorithms:
#' * oddeven: an extension of the odd-even algorithm to handle GIS polygons containing inner rings and degeneracies;
#' * setdiff: one where we follow a point set difference rule for the rings (outer - inner).
#'
#' @references
#' Ledoux, H., Arroyo Ohori, K., and Meijers, M. (2014).
#' A triangulation-based approach to automatically repair GIS polygons.
#' Computers & Geosciences 66:121–131.
#'
#' @examples
#' library(sf)
#' p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
#' st_is_valid(p1)
#' st_prepair(p1)
#' st_is_valid(st_prepair(p1))
#'
#' @seealso `sf::st_make_valid` for another approach to fix broken polygons
#'
#' @importFrom sf st_geometry st_set_geometry st_geometry_type st_geometrycollection st_crs st_sfc
#'
#' @export
st_prepair <- function(x, algorithm = c("oddeven", "setdiff"), min_area = 0) {
  UseMethod("st_prepair")
}

#' @export
st_prepair.sfc <- function(x, algorithm = c("oddeven", "setdiff"), min_area = 0) {
  assert_2d_polygon_type(x)
  algorithm  <- match.arg(algorithm)
  switch(algorithm,
         oddeven = sf::st_sfc(CPL_prepair_oddeven(x, min_area), crs = sf::st_crs(x)),
         setdiff = sf::st_sfc(CPL_prepair_setdiff(x, min_area), crs = sf::st_crs(x)))
}

#' @export
st_prepair.sf <- function(x, algorithm = c("oddeven", "setdiff"), min_area = 0) {
  sf::st_set_geometry(x, st_prepair(sf::st_geometry(x), algorithm, min_area))
}

#' @export
st_prepair.sfg <- function(x, algorithm = c("oddeven", "setdiff"), min_area = 0) {
  first_sfg_from_sfc(st_prepair(sf::st_sfc(x), algorithm, min_area))
}
