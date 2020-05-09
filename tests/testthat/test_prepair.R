context("st_prepair tests")

test_that("st_prepair return the right class", {
  library(sf)
  p <- st_as_sfc("POLYGON((0 0, 0 10, 10 0, 10 10, 0 0))")
  expect_is(st_prepair(p), "sfc")
  expect_is(st_prepair(p[[1]]), "sfg")
  expect_is(st_prepair(st_sf(data.frame(id = 1), geometry = p)), "sf")
})

test_that("st_prepair remove small sliver", {
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_equal(st_prepair(p), st_as_sfc("MULTIPOLYGON (((10 0,10 10,0 10,0 0,10 0)),((11 10,10 11,10 10,11 10)))"))
})

test_that("st_prepair can remove area small than min_area", {
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_equal(st_prepair(p, min_area = 1), st_as_sfc("MULTIPOLYGON (((10 0,10 10,0 10,0 0,10 0)))"))
})
