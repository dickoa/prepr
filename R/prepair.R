#' Automatic repair of single polygons
#'
#' `st_prepair` repairs single polygons according to the international standards ISO 19107
#'  using a constrained triangulation approach.
#'
#' @param x object of class `sf`, `sfc` or `sfg`, it only works POLYGON or MULTIPOLYGON are supported

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
#' van Oosterom P., Quak W., Tijssen T. (2005).
#' About Invalid, Valid and Clean Polygons.
#' In: Developments in Spatial Data Handling. Springer, Berlin, Heidelberg
#'
#' @examples
#' \dontrun{
#' library(sf)
#' p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
#' st_is_valid(p1)
#' st_prepair(p1)
#' st_is_valid(st_prepair(p1))
#' }
#'
#' @seealso `sf::st_make_valid` for another approach to fix broken polygons
#'
#'
#' @return an object of class `sf`, `sfc` or `sfg` depending on whether
#' the input is respectively `sf`, `sfc` or `sfg`
#'
#' @export
st_prepair <- function(x) {
  UseMethod("st_prepair")
}

#' @export
#' @importFrom sf st_sfc st_crs
st_prepair.sfc <- function(x) {
  assert_2d_polygon_type(x)
  st_sfc(CPL_prepair(x), crs = st_crs(x))
}

#' @export
#' @importFrom sf st_set_geometry st_geometry
st_prepair.sf <- function(x) {
  st_set_geometry(x, st_prepair(st_geometry(x)))
}

#' @export
#' @importFrom sf st_sfc
st_prepair.sfg <- function(x) {
  first_sfg_from_sfc(st_prepair(st_sfc(x)))
}
