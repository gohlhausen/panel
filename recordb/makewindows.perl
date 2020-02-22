#! /usr/bin/perl
# http://en.wikipedia.org/wiki/Window_function
use Math::Trig ':pi';
$len = 256;
for ($i=0; $i < $len; $i++) {
	$name = "Hanning";
	$val = 0.5 * (1 - cos(2 * pi * $i / ($len -1)));
	#$name = "Bartlett";
	#$val = 1 - abs(($i - ($len - 1) / 2) / ($len / 2));
	#$name = "Blackman";
	#$a0 = (1 - 0.16) / 2;
	#$a1 = 0.5;
	#$a2 = 0.16 / 2;
	#$val = $a0 - $a1 * cos(2 * pi * $i / ($len -1)) + $a2 * cos(4 * pi * $i / ($len -1));
	#$name = "Flattop";
	#$a0 = 1;
	#$a1 = 1.93;
	#$a2 = 1.29;
	#$a3 = 0.388;
	#$a4 = 0.028;
	#$max = $a0 - $a1 * cos(pi) + $a2 * cos(2 * pi) - $a3 * cos(3 * pi) + $a4 * cos(4 * pi) ;
	#$val = $a0 - $a1 * cos(2 * pi * $i / ($len -1)) + $a2 * cos(4 * pi * $i / ($len -1));
	#$val += -1 * $a3 * cos(6 * pi * $i / ($len -1)) + $a4 * cos(8 * pi * $i / ($len -1));
	#$val /= $max;
	#$name = "BlackmanHarris";
	#$a0 = 0.35875;
	#$a1 = 0.48829;
	#$a2 = 0.14128;
	#$a3 = 0.01168;
	#$a4 = 0;
	#$val = $a0 - $a1 * cos(2 * pi * $i / ($len -1)) + $a2 * cos(4 * pi * $i / ($len -1));
	#$val += -1 * $a3 * cos(6 * pi * $i / ($len -1)) + $a4 * cos(8 * pi * $i / ($len -1));
	#$name = "Nuttall";
	#$a0 = 0.355768;
	#$a1 = 0.487396;
	#$a2 = 0.144232;
	#$a3 = 0.012604;
	#$a4 = 0;
	#$val = $a0 - $a1 * cos(2 * pi * $i / ($len -1)) + $a2 * cos(4 * pi * $i / ($len -1));
	#$val += -1 * $a3 * cos(6 * pi * $i / ($len -1)) + $a4 * cos(8 * pi * $i / ($len -1));
	#$name = "BlackmanNuttall";
	#$a0 = 0.3635819;
	#$a1 = 0.4891775;
	#$a2 = 0.1365995;
	#$a3 = 0.0106411;
	#$a4 = 0;
	#$val = $a0 - $a1 * cos(2 * pi * $i / ($len -1)) + $a2 * cos(4 * pi * $i / ($len -1));
	#$val += -1 * $a3 * cos(6 * pi * $i / ($len -1)) + $a4 * cos(8 * pi * $i / ($len -1));
	#$name = "Welch";
	#$val = 1 - (($i - ($len - 1) / 2) / ($len / 2)) ** 2;
	#$name = "Hamming";
	#$val = 0.54 - 0.46 * cos(2 * pi * $i / ($len -1));
	#$name = "Cosine";
	#$val = cos((pi * $i / ($len -1)) - (pi / 2));
	#$name = "Tukey";
	#$a = 0.5;
	#if ($i <= ($a * ($len - 1) / 2)) {
	#	$val = 0.5 * (1 + cos(pi * ((2 * $i / ($a * ($len - 1))) - 1)));
	#} elsif ($i < (($len - 1) * (1 - $a / 2))) {
	#	$val = 0.99999;
	#} else {
	#	$val = 0.5 * (1 + cos(pi * ((2 * $i / ($a * ($len - 1))) - (2 / $a) + 1)));
	#}
	#$name = "KaiserBessel";
	# TODO: what is the full equation, with the "zero-th order modified Bessel function"?
	$n = int($val * 32768 + 0.5);
	$n = 32767 if $n > 32767;
	if (0) {
		print $i;
		print "\t";
		printf "%9.6f", $val;
		print "\t";
		print $n;
		print "\n";
	} else {
		if ($i == 0) {
			print "const int16_t AudioWindow${name}${len}[] __attribute__ ((aligned (4))) = {\n";
		}
		printf "%6d", $n;
		print "," if ($i < $len);
		print "\n" if ($i % 10) == 9;
	}
}
print "\n" unless ($len % 10) == 9;
print "};\n";
