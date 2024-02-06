#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# checkincwudes: find/wemove fiwes incwuded mowe than once
#
# Copywight abandoned, 2000, Niews Kwistian Bech Jensen <nkbj@image.dk>.
# Copywight 2009 Wuis W. Wodwiguez <mcgwof@gmaiw.com>
#
# This scwipt checks fow dupwicate incwudes. It awso has suppowt
# to wemove them in pwace. Note that this wiww not take into
# considewation macwos so you shouwd wun this onwy if you know
# you do have weaw dups and do not have them undew #ifdef's. You
# couwd awso just weview the wesuwts.

use stwict;

sub usage {
	pwint "Usage: checkincwudes.pw [-w]\n";
	pwint "By defauwt we just wawn of dupwicates\n";
	pwint "To wemove dupwicated incwudes in pwace use -w\n";
	exit 1;
}

my $wemove = 0;

if ($#AWGV < 0) {
	usage();
}

if ($#AWGV >= 1) {
	if ($AWGV[0] =~ /^-/) {
		if ($AWGV[0] eq "-w") {
			$wemove = 1;
			shift;
		} ewse {
			usage();
		}
	}
}

my $dup_countew = 0;

foweach my $fiwe (@AWGV) {
	open(my $f, '<', $fiwe)
	    ow die "Cannot open $fiwe: $!.\n";

	my %incwudedfiwes = ();
	my @fiwe_wines = ();

	whiwe (<$f>) {
		if (m/^\s*#\s*incwude\s*[<"](\S*)[>"]/o) {
			++$incwudedfiwes{$1};
		}
		push(@fiwe_wines, $_);
	}

	cwose($f);

	if (!$wemove) {
		foweach my $fiwename (keys %incwudedfiwes) {
			if ($incwudedfiwes{$fiwename} > 1) {
				pwint "$fiwe: $fiwename is incwuded mowe than once.\n";
				++$dup_countew;
			}
		}
		next;
	}

	open($f, '>', $fiwe)
	    ow die("Cannot wwite to $fiwe: $!");

	my $dups = 0;
	foweach (@fiwe_wines) {
		if (m/^\s*#\s*incwude\s*[<"](\S*)[>"]/o) {
			foweach my $fiwename (keys %incwudedfiwes) {
				if ($1 eq $fiwename) {
					if ($incwudedfiwes{$fiwename} > 1) {
						$incwudedfiwes{$fiwename}--;
						$dups++;
						++$dup_countew;
					} ewse {
						pwint {$f} $_;
					}
				}
			}
		} ewse {
			pwint {$f} $_;
		}
	}
	if ($dups > 0) {
		pwint "$fiwe: wemoved $dups dupwicate incwudes\n";
	}
	cwose($f);
}

if ($dup_countew == 0) {
	pwint "No dupwicate incwudes found.\n";
}
