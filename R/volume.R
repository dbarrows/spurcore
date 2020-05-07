#' Volume class
#' 
#' For setting initial conditions of inhomogeneous systems.
#'
#' @param dims [`vector`] of the dimensions of the system in the order (x, y, z)
#' @param h the side length of each cubic voxel
#' @param seed optional [`vector`] containing the initial state value for each voxel
#' 
#' @return An instance of the [`volume`] class
#' @export
volume <- function(dims, h, seed = numeric()) {
    structure(
        list(cpp = new(volume_cpp, dims, h, seed)),
        class = "volume"
    )
}

#' Set reaction system state
#' 
#' @param volume an instance of the [`volume`] class
#' @param index [`vector`] of the index (x, y, z) of the voxel to assign the state to
#' @param state [`vector`] of species quantities
#' 
#' @export
volume_set <- function(volume, index, state) {
    volume$cpp$set(index, state)
}

#' Get reaction system state
#' 
#' @param volume an instance of the [`volume`] class
#' @param index [`vector`] of the index (x, y, z) of the voxel to get the vector of species quantities
#' 
#' @return [`vector`] of species quantities
#' @export
volume_get <- function(volume, index) {
    volume$cpp$get(index) %>% as.vector()
}

#' Volume dimensions
#' 
#' @param volume an instance of the [`volume`] class
#' 
#' @return [`vector`] of dimensions of the system in the order (x, y, z).
#' @export
volume_dims <- function(volume) {
    volume$cpp$dims %>% as.vector()
}

#' Voxel side length
#' 
#' @param volume an instance of the [`volume`] class
#' 
#' @return Side length of each voxel
#' @export
volume_h <- function(volume) {
    volume$cpp$h
}

#' Volume states
#' 
#' @param volume an instance of the [`volume`] class
#' @param species an optional [`vector`] of species names to be used in the output header
#' @param ... additional options
#' 
#' @return States of [`volume`] as a [`tibble::tibble`]
#' @export
volume_states <- function(volume, species = NULL, ...) {
    dims <- volume_dims(volume)
    df_index <- expand.grid(x = 1:dims[1], y = 1:dims[2], z = 1:dims[3])
    df_state <- sapply(1:nrow(df_index), function(i) {
            s <- df_index[i,] %>% as.numeric() %>% volume_get(volume, .)
        }) %>%
        t() %>%
        rbind() %>%
        as.data.frame()
    names(df_state) <- if(is.null(species)) str_c("S", 1:ncol(df_state)) else species
    cbind(df_index, df_state) %>% as_tibble()
}

#' @export
print.volume <- function(x, ...) {
    dims <- x$cpp$dims
    cat(paste0(blurred("#"), blue(" dims: "), paste0(dims[1], " x ", dims[2], " x ", dims[3], "\n")))
    cat(paste0(blurred("#"), blue(" h: "), paste0(x$cpp$h, "\n")))
    cat(paste0(blurred("#"), blue(" states: "), blurred(paste0("\n", "# "))))
    print(volume_states(x, ...), ...)
}

Rcpp::loadModule("volume_cpp", TRUE)
