
<!-- README.md is generated from README.Rmd. Please edit that file -->

# prepair

<!-- badges: start -->

[![GitLab CI Build
Status](https://gitlab.com/dickoa/prepair/badges/master/pipeline.svg)](https://gitlab.com/dickoa/prepair/pipelines)
[![Codecov Code
Coverage](https://codecov.io/gl/dickoa/prepair/branch/master/graph/badge.svg)](https://codecov.io/gl/dickoa/prepair)
[![](http://www.r-pkg.org/badges/version/prepair)](http://www.r-pkg.org/pkg/prepair)
<!-- badges: end -->

An R package to repair broken GIS polygons using the
[`prepair`](<https://github.com/tudelft3d/prepair>) Cpp library.

## Installation

You can install the development version of prepair from
[Gitlab](https://gitlab.com/dickoa/prepair) using the `remotes` package
with:

``` r
# install.packages("remotes")
remotes::install_gitlab("dickoa/prepair")
```

## A quick Example

This is a basic example which shows you how to solve a common problem:

``` r
library(prepair)
library(sf)
#> Linking to GEOS 3.8.0, GDAL 3.0.4, PROJ 6.3.1

# A 'bowtie' polygon:
p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
# Square with wrong orientation:
p2 <- st_as_sfc("POLYGON((0 0, 0 10, 10 10, 10 0, 0 0))")
# Inner ring with one edge sharing part of an edge of the outer ring:
p3 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0),(5 2,5 7,10 7, 10 2, 5 2))")
# Dangling edge:
p4 <- st_as_sfc("POLYGON((0 0, 10 0, 15 5, 10 0, 10 10, 0 10, 0 0))")
# Outer ring not closed:
p5 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10))")
# Two adjacent inner rings:
p6 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0), (1 1, 1 8, 3 8, 3 1, 1 1), (3 1, 3 8, 5 8, 5 1, 3 1))")
# Polygon with an inner ring inside another inner ring:
p7 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0), (2 8, 5 8, 5 2, 2 2, 2 8), (3 3, 4 3, 3 4, 3 3))")
p  <-  c(p1, p2, p3, p4, p5, p6, p7)
(valid <- st_is_valid(p))
#> [1] FALSE  TRUE FALSE FALSE    NA FALSE FALSE

st_is_valid(st_prepair(p1))
#> [1] TRUE
```
