.PHONEY: install, readme, check, site, release
install:
	@Rscript -e 'devtools::install()'
readme:
	@make install &&\
	Rscript -e 'rmarkdown::render("README.Rmd")'
check:
	@Rscript -e 'devtools::check()'
site:
	@Rscript -e "devtools::document(); pkgdown::build_site()"
release:
	@make check && make site