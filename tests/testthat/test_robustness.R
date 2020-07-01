context("st_probustness tests")

test_that("Polygon robustness can be computed", {
  library(sf)
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_is(st_probustness(p), "numeric")
})