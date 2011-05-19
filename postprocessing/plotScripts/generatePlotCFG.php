<?php

//vary ranges
for($i = 0; $i < 6; $i++) {
	$output = "0 60000 250 0 $i 0 0\n";
	$output .= "plotScripts/hreal${i}0.out\n";
	$output .= "plotScripts/logh${i}0.out\n";
	$output .= "plotScripts/noise${i}0.out\n";
	$output .= "plotScripts/sig2noise${i}0.out\n";
	file_put_contents("plotData${i}0.cfg", $output);
}

for($i = 0; $i < 6; $i++) {
	$output = "0 60000 250 0 0 $i 0\n";
	$output .= "plotScripts/hreal0${i}.out\n";
	$output .= "plotScripts/logh0${i}.out\n";
	$output .= "plotScripts/noise0${i}.out\n";
	$output .= "plotScripts/sig2noise0${i}.out\n";
	file_put_contents("plotData0${i}.cfg", $output);
}
?>
