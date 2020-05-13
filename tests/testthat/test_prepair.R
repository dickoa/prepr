context("st_prepair tests")

test_that("st_prepair return the right class", {
  library(sf)
  p <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
  expect_is(st_prepair(p), "sfc")
  expect_is(st_prepair(p[[1]]), "sfg")
  expect_is(st_prepair(st_sf(data.frame(id = 1), geometry = p)), "sf")
})

test_that("st_prepair only accepts polygon and multipolygon", {
  p1 <- st_as_sfc("POINT(1 1)")
  l1 <- st_as_sfc("LINESTRING (30 10, 10 30, 40 40)")
  c1 <- st_as_sfc("GEOMETRYCOLLECTION (POINT (40 10), LINESTRING (10 10, 20 20, 10 40), POLYGON ((40 40, 20 45, 45 30, 40 40)))")
  expect_error(st_prepair(p1), "Only POLYGON or MULTIPOLYGON are supported")
  expect_error(st_prepair(l1), "Only POLYGON or MULTIPOLYGON are supported")
  expect_error(st_prepair(c1), "Only POLYGON or MULTIPOLYGON are supported")
})

test_that("st_prepair remove small sliver", {
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_equal(st_prepair(p), st_as_sfc("MULTIPOLYGON (((10 0,10 10,0 10,0 0,10 0)),((11 10,10 11,10 10,11 10)))"))
})

test_that("st_prepair can remove area small than min_area", {
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_equal(st_prepair(p, min_area = 1), st_as_sfc("MULTIPOLYGON (((10 0,10 10,0 10,0 0,10 0)))"))
})
