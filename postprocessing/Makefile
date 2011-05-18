all: plot

run: find_bw
	@echo "Running now"

sig2noise: generate_sig2noise.cpp
	g++ -O3 -Wall -o sig2noise generate_sig2noise.cpp
	find ../output -name *arr -exec ./sig2noise {} \;

plotdata: sig2noise generatePlotData.cpp
	g++ -O3 -Wall -o plotData  generatePlotData.cpp
	./plotData plotData.cfg

find_bw: plotdata find_bw.cpp
	g++ -O3 -Wall -o fb find_bw.cpp
	./fb plotData.cfg

plot: run
	gnuplot gnuplot.p
	evince *pdf
