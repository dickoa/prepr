#' @noRd
#' @importFrom sf st_geometry_type
assert_2d_polygon_type <- function(x) {
  if (!any(st_geometry_type(x) %in% c("POLYGON", "MULTIPOLYGON")))
    stop("Only POLYGON or MULTIPOLYGON are supported", call. = FALSE)

  if (st_is_z_non_null(x))
    stop("3D object not allowed use st_zm to drop Z!", call. = FALSE)
}

#' @noRd
#' @importFrom sf st_multipolygon
first_sfg_from_sfc <- function(x) {
  if (length(x) == 0) {
    st_multipolygon()
  } else {
    x[[1]]
  }
}

#' @noRd
st_is_z_non_null <- function(x) {
  if (length(x) == 0) {
    FALSE
  } else {
    grepl("Z", class(x[[1]])[1])
  }
}