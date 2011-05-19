set terminal pdf
set output 'hreal00.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Transfer Function';
plot "./plotScripts/hreal00.out" with lines title "Bellhop model";

set terminal pdf
set output 'logh00.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Log Transfer Function (dB)';
plot "./plotScripts/logh00.out" with lines title "Bellhop model";

set terminal pdf
set output 'noise00.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Noise (dB / Pa)';
plot "./plotScripts/noise00.out" with lines title "Bellhop model";

set terminal pdf
set output 'sig2noise00.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Signal to Noise Ratio (dB)';
plot "./plotScripts/sig2noise00.out" with lines title "Bellhop model";

set terminal pdf
set output 'capacity00.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Capacity';
plot "./plotScripts/capacity00.out" with lines title "Bellhop model";

set terminal pdf
set output 'sig2noiseRange.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Signal to Noise Ratio (dB)'; 
plot "./plotScripts/sig2noise00.out" with lines title "Range 0.9km", \
     "./plotScripts/sig2noise01.out" with lines title "Range 1km", \
     "./plotScripts/sig2noise02.out" with lines title "Range 1.1km", \
     "./plotScripts/sig2noise03.out" with lines title "Range 1.9km", \
     "./plotScripts/sig2noise04.out" with lines title "Range 2km", \
     "./plotScripts/sig2noise05.out" with lines title "Range 2.1km";

set terminal pdf
set output 'sig2noiseDepth.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Signal to Noise Ratio (dB)'; 
plot "./plotScripts/sig2noise00.out" with lines title "Depth 87m", \
     "./plotScripts/sig2noise10.out" with lines title "Depth 88m", \
     "./plotScripts/sig2noise20.out" with lines title "Depth 89m", \
     "./plotScripts/sig2noise30.out" with lines title "Depth 90m", \
     "./plotScripts/sig2noise40.out" with lines title "Depth 91m", \
     "./plotScripts/sig2noise50.out" with lines title "Depth 92m";

set terminal pdf
set output 'capacityRange.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Capacity (bps)';
plot "./plotScripts/capacity00.out" with lines title "Range 0.9km", \
     "./plotScripts/capacity01.out" with lines title "Range 1km", \
     "./plotScripts/capacity02.out" with lines title "Range 1.1km", \
     "./plotScripts/capacity03.out" with lines title "Range 1.9km", \
     "./plotScripts/capacity04.out" with lines title "Range 2km", \
     "./plotScripts/capacity05.out" with lines title "Range 2.1km";

set terminal pdf
set output 'capacityDepth.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Capacity (bps)';
plot "./plotScripts/capacity00.out" with lines title "Depth 87m", \
     "./plotScripts/capacity10.out" with lines title "Depth 88m", \
     "./plotScripts/capacity20.out" with lines title "Depth 89m", \
     "./plotScripts/capacity30.out" with lines title "Depth 90m", \
     "./plotScripts/capacity40.out" with lines title "Depth 91m", \
     "./plotScripts/capacity50.out" with lines title "Depth 92m";