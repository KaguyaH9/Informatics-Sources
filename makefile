output/sources.pdf: output/sources.tex
	xelatex --output-directory=output output/sources.tex
output/sources.tex: gen/gen
	gen/gen
gen/gen: gen/gen.cpp
	bash -ic 'dg1z gen/gen.cpp -o gen/gen'
