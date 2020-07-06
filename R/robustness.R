#' Compute polygons robustness
#'
#' Compute polygons robustness, the higher the value the more robust the polygon is.
#' robustness can be defined as the largest  distance  of  moving  a  vertex,
#' while  the  result  is  still  a  valid  polygon
#'
#' @param x object of class `sf`, `sfc` or `sfg`, it only works with POLYGON or MULTIPOLYGON
#'  are supported
#'
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
#'
#' @examples
#' \dontrun{
#' library(sf)
#' p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
#' st_is_valid(p1)
#' st_probustness(p1)
#' st_probustness(st_prepair(p1))
#' }
#'
#' @importFrom sf st_geometry st_sfc st_set_geometry
#'
#' @return a numeric vector
#'
#' @export
st_probustness <- function(x) {
  UseMethod("st_probustness")
}

#' @export
st_probustness.sfc <- function(x) {
  assert_2d_polygon_type(x)
  sqrt(CPL_robustness(x))
}

#' @export
st_probustness.sf <- function(x) {
  st_probustness(sf::st_geometry(x))
}

#' @export
st_probustness.sfg <- function(x) {
  st_probustness(sf::st_sfc(x))
}
