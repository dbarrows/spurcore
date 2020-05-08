context("Volume")
library(spurcore)
library(magrittr)

test_that("Volume constructor", {
    vol <- volume(c(1, 1, 1), 1, seed = c(1, 2))
    expect_equal(
        vol$cpp$dims %>% as.vector(),
        c(1, 1, 1)
    )
    expect_equal(
        vol$cpp$h,
        1
    )
    expect_equal(
        vol$cpp$get(c(1, 1, 1)) %>% as.vector(),
        c(1, 2)
    )
})

test_that("Accessors", {
    vol <- volume(c(2, 1, 1), 1, seed = c(1, 2))
    expect_equal(
        volume_dims(vol),
        c(2, 1, 1)
    )
    expect_equal(
        volume_h(vol),
        1
    )
    expect_equal(
        volume_get(vol, c(1, 1, 1)),
        c(1, 2)
    )
})

test_that("State setter", {
    vol <- volume(c(2, 1, 1), 1, seed = c(1, 2))
    volume_set(vol, c(2, 1, 1), c(3, 4))
    expect_equal(
        volume_get(vol, c(1, 1, 1)),
        c(1, 2)
    )
    expect_equal(
        volume_get(vol, c(2, 1, 1)),
        c(3, 4)
    )

    vol <- volume(c(3, 3, 3), 1, seed = c(1, 1))
    volume_set(vol, c(1, 2, 3), c(4, 5))
    expect_equal(
        volume_get(vol, c(1, 2, 3)),
        c(4, 5)
    )
})