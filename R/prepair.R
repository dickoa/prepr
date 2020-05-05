#' Polygon repair
#'
#' Automatically repair "broken" simple features polygons according to the international standard ISO19107
#'
#' @param x object of class \code{sf}, \code{sfc} or \code{sfg}
#' @param min_area mininum area to keep in output
#' @param point_set if TRUE use the point set difference algorithm for the rings (outer-inner)
#' by default use the odd-even algorithm
#' @param ... ignored
#'
#' @examples
#' library(sf)
#' p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
#' st_is_valid(p1)
#' st_prepair(p1)
#' st_is_valid(st_prepair(p1))
#'
#' @seealso \code{sf::st_make_valid} for another approach at fixing broken polygon
#' @export
st_prepair <- function(x, min_area = 0, point_set = FALSE)
  UseMethod("st_prepair")

#' @export
st_prepair.sfc <- function(x, min_area = 0, point_set = FALSE) {
  if (!sf::st_geometry_type(x) %in% c("POLYGON", "MULTIPOLYGON"))
    stop("Only POLYGON or MULTIPOLYGON are supported", call. = FALSE)
  st_sfc(CPL_prepair(x, min_area, point_set), crs = st_crs(x))
}

#' @export
st_prepair.sf <- function(x, min_area = 0, point_set = FALSE) {
  st_set_geometry(x, st_prepair(st_geometry(x), min_area, point_set))
}

#' @export
st_prepair.sfg <- function(x, min_area = 0, point_set = FALSE) {
  st_prepair(st_geometry(x), min_area, point_set)
}

#' @useDynLib prepair, .registration = TRUE
NULL
