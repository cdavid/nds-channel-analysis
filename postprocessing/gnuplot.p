set terminal pdf
set output 'hreal.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Transfer Function';
plot "hreal.out" with lines title "Bellhop model";

set terminal pdf
set output 'logh.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Log Transfer Function (dB)';
plot "logh.out" with lines title "Bellhop model";

set terminal pdf
set output 'noise.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Noise (dB / Pa)';
plot "noise.out" with lines title "Bellhop model";

set terminal pdf
set output 'sig2noise.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Signal to Noise Ration (dB)';
plot "sig2noise.out" with lines title "Bellhop model";

set terminal pdf
set output 'capacity.pdf'
set xlabel 'Frequency (Hz)'
set ylabel 'Capacity';
plot "capacity.out" with lines title "Bellhop model";
