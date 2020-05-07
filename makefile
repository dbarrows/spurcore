.PHONEY: install, readme, check, site
install:
	@Rscript -e 'devtools::install()'
readme:
	@make install &&\
	Rscript -e 'rmarkdown::render("README.Rmd")'
check:
	@Rscript -e 'devtools::check()'
site:
	@Rscript -e "devtools::document(); pkgdown::deploy_to_branch()"