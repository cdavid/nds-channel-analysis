all: plot

run: find_bw
	@echo "Running now"

sig2noise: generate_sig2noise.cpp
	g++ -O3 -Wall -o sig2noise generate_sig2noise.cpp
	find ../output -name *arr -exec ./sig2noise {} \;

plotdata: sig2noise generatePlotData.cpp
	g++ -O3 -Wall -o plotData  generatePlotData.cpp
	./plotData plotScripts/plotData00.cfg
	./plotData plotScripts/plotData01.cfg
	./plotData plotScripts/plotData02.cfg
	./plotData plotScripts/plotData03.cfg
	./plotData plotScripts/plotData04.cfg
	./plotData plotScripts/plotData05.cfg
	./plotData plotScripts/plotData10.cfg
	./plotData plotScripts/plotData20.cfg
	./plotData plotScripts/plotData30.cfg
	./plotData plotScripts/plotData40.cfg
	./plotData plotScripts/plotData50.cfg

find_bw: plotdata find_bw.cpp
	g++ -O3 -Wall -o fb find_bw.cpp
	./fb plotScripts/plotData00.cfg
	./fb plotScripts/plotData01.cfg
	./fb plotScripts/plotData02.cfg
	./fb plotScripts/plotData03.cfg
	./fb plotScripts/plotData04.cfg
	./fb plotScripts/plotData05.cfg
	./fb plotScripts/plotData10.cfg
	./fb plotScripts/plotData20.cfg
	./fb plotScripts/plotData30.cfg
	./fb plotScripts/plotData40.cfg
	./fb plotScripts/plotData50.cfg

plot: run
	gnuplot gnuplot.p
	evince *pdf
