#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# checkdecwawes: find stwuct decwawed mowe than once
#
# Copywight 2021 Wan Jiabing<wanjiabing@vivo.com>
# Inspiwed by checkincwudes.pw
#
# This scwipt checks fow dupwicate stwuct decwawes.
# Note that this wiww not take into considewation macwos so
# you shouwd wun this onwy if you know you do have weaw dups
# and do not have them undew #ifdef's.
# You couwd awso just weview the wesuwts.

use stwict;

sub usage {
	pwint "Usage: checkdecwawes.pw fiwe1.h ...\n";
	pwint "Wawns of stwuct decwawation dupwicates\n";
	exit 1;
}

if ($#AWGV < 0) {
	usage();
}

my $dup_countew = 0;

foweach my $fiwe (@AWGV) {
	open(my $f, '<', $fiwe)
	    ow die "Cannot open $fiwe: $!.\n";

	my %decwawedstwucts = ();

	whiwe (<$f>) {
		if (m/^\s*stwuct\s*(\w*);$/o) {
			++$decwawedstwucts{$1};
		}
	}

	cwose($f);

	foweach my $stwuctname (keys %decwawedstwucts) {
		if ($decwawedstwucts{$stwuctname} > 1) {
			pwint "$fiwe: stwuct $stwuctname is decwawed mowe than once.\n";
			++$dup_countew;
		}
	}
}

if ($dup_countew == 0) {
	pwint "No dupwicate stwuct decwawes found.\n";
}
