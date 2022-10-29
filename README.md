
<!-- README.md is generated from README.Rmd. Please edit that file -->

# prepr <img src="man/figures/hex-prepr.png" align="right" height="139" />

<!-- badges: start -->

[![GitLab CI Build
Status](https://gitlab.com/dickoa/prepr/badges/master/pipeline.svg)](https://gitlab.com/dickoa/prepr/pipelines)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/gitlab/dickoa/prepr?branch=master&svg=true)](https://ci.appveyor.com/project/dickoa/prepr)
[![Codecov Code
Coverage](https://codecov.io/gl/dickoa/prepr/branch/master/graph/badge.svg)](https://codecov.io/gl/dickoa/prepr)
[![CRAN
status](http://www.r-pkg.org/badges/version/prepr)](http://www.r-pkg.org/pkg/prepr)
<!-- badges: end -->

An R package to repair broken GIS polygons using the
[`prepair`](https://github.com/tudelft3d/prepair) C++ library.

## Installation

The `prepair` C++ library need these two libraries to compile:

- [`CGAL`](https://www.cgal.org/)
- [`GDAL`](https://gdal.org/)

The R package `prepr` solves the CGAL dependencies by shipping with a
subset of the CGAL header. We also use
[`rwinlib`](https://github.com/rwinlib) to provide `GDAL` on Windows in
order to build this package from source. You will need the latest
version of [`rtools`](https://cran.r-project.org/bin/windows/Rtools/) in
order to build the source code on Windows.

`prepair` can also use these optional libraries:

- [`GMP`](https://gmplib.org/)
- [`MPFR`](https://www.mpfr.org/)

They are disabled by default on Windows but required if you want to
build the package in a Linux/OS X environment. After installing all
these libraries, you can now install the development version of the
`prepr` R package from [Gitlab](https://gitlab.com/dickoa/prepr) using
the `remotes` R package with:

``` r
# install.packages("remotes")
remotes::install_gitlab("dickoa/prepr")
remotes::install_github("dickoa/prepr") ## mirror
```

## A quick tutorial

This is a simple tutorial which shows you how to solve common problems
we can find with polygons:

### A ‘bowtie’ polygon:

``` r
library(prepr)
library(sf)

p1 <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
st_is_valid(p1, reason = TRUE)
#> [1] "Self-intersection[5 5]"
p11 <- st_prepair(p1)
st_is_valid(p11)
#> [1] TRUE

st_as_text(p11)
#> [1] "MULTIPOLYGON (((0 0, 5 5, 0 10, 0 0)), ((5 5, 10 0, 10 10, 5 5)))"

par(mfrow = c(1, 2))
plot(p1, main = "RAW", col = "#D7722C")
plot(p11, main = "Repaired", col = "#D7722C")
```

<img src="man/figures/README-p1-1.svg" width="100%" />

### Square with wrong orientation:

``` r
p2 <- st_as_sfc("POLYGON((0 0, 0 10, 10 10, 10 0, 0 0))")
st_is_valid(p2, reason = TRUE)
#> [1] "Valid Geometry"
plot(p2, main = "RAW", col = "#D7722C")
```

<img src="man/figures/README-p2-1.svg" width="100%" />

### Inner ring with one edge sharing part of an edge of the outer ring:

``` r
p3 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0),(5 2, 5 7, 10 7, 10 2, 5 2))")
st_is_valid(p3, reason = TRUE)
#> [1] "Self-intersection[10 2]"
p33 <- st_prepair(p3)
st_is_valid(p33)
#> [1] TRUE

st_as_text(p33)
#> [1] "POLYGON ((0 0, 10 0, 10 2, 5 2, 5 7, 10 7, 10 10, 0 10, 0 0))"

par(mfrow = c(1, 2))
plot(p3, main = "RAW", col = "#D7722C")
plot(p33, main = "Repaired", col = "#D7722C")
```

<img src="man/figures/README-p3-1.svg" width="100%" />

### Dangling edge:

``` r
p4 <- st_as_sfc("POLYGON((0 0, 10 0, 15 5, 10 0, 10 10, 0 10, 0 0))")
st_is_valid(p4, reason = TRUE)
#> [1] "Self-intersection[15 5]"
p44 <- st_prepair(p4)
st_is_valid(p44)
#> [1] TRUE

st_as_text(p44)
#> [1] "POLYGON ((0 0, 10 0, 10 10, 0 10, 0 0))"

par(mfrow = c(1, 2))
plot(p4, main = "RAW", col = "#D7722C")
plot(p44, main = "Repaired", col = "#D7722C")
```

<img src="man/figures/README-p4-1.svg" width="100%" />

### Two adjacent inner rings:

``` r
p6 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0), (1 1, 1 8, 3 8, 3 1, 1 1), (3 1, 3 8, 5 8, 5 1, 3 1))")
st_is_valid(p6, reason = TRUE)
#> [1] "Self-intersection[3 8]"
p66 <- st_prepair(p6)
st_is_valid(p66)
#> [1] TRUE

st_as_text(p66)
#> [1] "POLYGON ((0 0, 10 0, 10 10, 0 10, 0 0), (1 1, 1 8, 3 8, 5 8, 5 1, 3 1, 1 1))"

par(mfrow = c(1, 2))
plot(p6, main = "RAW", col = "#D7722C")
plot(p66, main = "Repaired", col = "#D7722C")
```

<img src="man/figures/README-p6-1.svg" width="100%" />

### Polygon with an inner ring inside another inner ring:

``` r
p7 <- st_as_sfc("POLYGON((0 0, 10 0, 10 10, 0 10, 0 0), (2 8, 5 8, 5 2, 2 2, 2 8), (3 3, 4 3, 3 4, 3 3))")
st_is_valid(p7, reason = TRUE)
#> [1] "Holes are nested[3 3]"
p77 <- st_prepair(p7)
st_is_valid(p77)
#> [1] TRUE

st_as_text(p77)
#> [1] "MULTIPOLYGON (((0 0, 10 0, 10 10, 0 10, 0 0), (2 2, 2 8, 5 8, 5 2, 2 2)), ((3 3, 4 3, 3 4, 3 3)))"

par(mfrow = c(1, 2))
plot(p7, main = "RAW", col = "#D7722C")
plot(p77, main = "Repaired", col = "#D7722C")
```

<img src="man/figures/README-p7-1.svg" width="100%" />

<!-- ## A exemple with a real dataset -->
<!-- ### Reading the data -->
<!-- ```{r read_data, cache = TRUE} -->
<!-- (clc1 <- read_sf("https://github.com/tudelft3d/prepair/raw/master/data/CLC2006_180927.geojson")) -->
<!-- (clc2 <- read_sf("https://github.com/tudelft3d/prepair/raw/master/data/CLC2006_2018418.geojson")) -->
<!-- par(mfrow = c(1, 2)) -->
<!-- plot(st_geometry(clc1), main = "CLC2006_180927", col = 'lightblue', axes = TRUE, graticule = TRUE, lwd = 0.2, cex.axis = 0.5) -->
<!-- plot(st_geometry(clc2), main = "CLC2006_2018418", col = "lightblue", axes = TRUE, graticule = TRUE, lwd = 0.2, cex.axis = 0.5) -->
<!-- ``` -->
<!-- ### Check if it's valid and repair it -->
<!-- ```{r clean_it, cache = TRUE} -->
<!-- st_is_valid(clc1, reason = TRUE) -->
<!-- (clc1_rpr <- st_prepair(clc1)) -->
<!-- st_is_valid(clc1_rpr) -->
<!-- st_is_valid(clc2, reason = TRUE) -->
<!-- (clc2_rpr <- st_prepair(clc2)) -->
<!-- st_is_valid(clc2_rpr) -->
<!-- ``` -->
<!-- ### How fast is `st_prepair` ? -->
<!-- `prepr::st_prepair` is fast and can be in some cases faster than `sf::st_make_valid` -->
<!-- ```{r bench, cache = TRUE} -->
<!-- (bnch1 <- bench::mark(st_make_valid(clc1), st_prepair(clc1), check = FALSE)) -->
<!-- summary(bnch1, relative = TRUE) -->
<!-- (bnch2 <- bench::mark(st_make_valid(clc2), st_prepair(clc2), check = FALSE)) -->
<!-- summary(bnch2, relative = TRUE) -->
<!-- ``` -->
<!-- You also have cases where it's slower to `sf::st_make_valid`, let's use this data from a [closed issue](https://github.com/r-spatial/sf/issues/1280) in the `sf` R package. -->
<!-- ```{r new_data, cache = TRUE} -->
<!-- ## need vsicurl -->
<!-- (agb <- read_sf("/vsicurl/http://files.hawaii.gov/dbedt/op/gis/data/2015AgBaseline.shp.zip")) -->
<!-- all(st_is_valid(agb)) -->
<!-- all(st_is_valid(st_make_valid(agb))) -->
<!-- all(st_is_valid(st_prepair(agb))) -->
<!-- plot(st_geometry(agb), main = "2015 Agriculture baseline", col = 'lightblue', axes = TRUE, graticule = TRUE, lwd = 0.2, cex.axis = 0.5) -->
<!-- ``` -->
<!-- `sf::st_make_valid` is faster with this data. -->
<!-- ```{r bench2, cache = TRUE} -->
<!-- (bnch3 <- bench::mark(st_make_valid(agb), st_prepair(agb), check = FALSE)) -->
<!-- summary(bnch3, relative = TRUE) -->
<!-- ``` -->

## Details and how to cite

Details of how we automatically repair broken polygons, and what results
you can expect, are available in this scientific article by the original
authors of `prepair`:

> Ledoux, H., Arroyo Ohori, K., and Meijers, M. (2014). A
> triangulation-based approach to automatically repair GIS polygons.
> *Computers & Geosciences* 66:121–131.
> [\[DOI\]](http://dx.doi.org/10.1016/j.cageo.2014.01.009)
> [\[PDF\]](http://3dgeoinfo.bk.tudelft.nl/hledoux/pdfs/14_cgeo_prepair.pdf)

If you use the R package `prepr` for a scientific project, please cite
their original work.

## License

This package is released under the GPL-3 license.
