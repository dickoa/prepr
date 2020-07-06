#' A package for automatically repairing broken polygons
#'
#' This package contains functions to repair single polygons according to the
#' international standards ISO 19107 using a constrained triangulation approach.
#' It is based on the prepair C++ tool.
#'
#' @docType package
#' @name prepr-package
"_PACKAGE"

#' @importFrom Rcpp evalCpp
#' @useDynLib prepr, .registration = TRUE
NULL
