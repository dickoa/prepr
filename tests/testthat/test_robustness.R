context("st_probustness tests")

skip_if_win32 <- function() {
  win32_flag <- .Platform$OS.type == "windows" && .Machine$sizeof.pointer != 8
  if (win32_flag) {
    skip("Tests not supported on Windows i386")
  }
}

test_that("Polygon robustness can be computed", {
  skip_if_win32()
  library(sf)
  p <- st_as_sfc("POLYGON((0 0, 10 0, 10 11, 11 10, 0 10))")
  expect_is(st_probustness(p), "numeric")
})

test_that("Polygon robustness can be computed", {
  skip_if_win32()
  library(sf)
  p <- st_polygon()
  expect_equal(st_probustness(p), NA_real_)
})