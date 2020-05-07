#' `spurcore` package
#'
#' Core classes and utilities for spur packages
#'
#' @docType package
#' @name spurcore
#' 
#' @import Rcpp
#' @import RcppArmadillo
#' @importFrom Rcpp evalCpp
#' @importFrom methods new
#' @importFrom crayon blurred blue silver
#' @importFrom magrittr %>%
#' @importFrom tibble as_tibble
#' @importFrom stringr str_c
#' @useDynLib spurcore, .registration = TRUE
NULL

## quiets concerns of R CMD check re:
##  - the "."s that appear in magrittr pipelines
if(getRversion() >= "2.15.1") utils::globalVariables(c("."))