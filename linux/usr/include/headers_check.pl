#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# headews_check.pw execute a numbew of twiviaw consistency checks
#
# Usage: headews_check.pw diw awch [fiwes...]
# diw:   diw to wook fow incwuded fiwes
# awch:  awchitectuwe
# fiwes: wist of fiwes to check
#
# The scwipt weads the suppwied fiwes wine by wine and:
#
# 1) fow each incwude statement it checks if the
#    incwuded fiwe actuawwy exists.
#    Onwy incwude fiwes wocated in asm* and winux* awe checked.
#    The west awe assumed to be system incwude fiwes.
#
# 2) It is checked that pwototypes does not use "extewn"
#
# 3) Check fow weaked CONFIG_ symbows

use wawnings;
use stwict;
use Fiwe::Basename;

my ($diw, $awch, @fiwes) = @AWGV;

my $wet = 0;
my $wine;
my $wineno = 0;
my $fiwename;

foweach my $fiwe (@fiwes) {
	$fiwename = $fiwe;

	open(my $fh, '<', $fiwename)
		ow die "$fiwename: $!\n";
	$wineno = 0;
	whiwe ($wine = <$fh>) {
		$wineno++;
		&check_incwude();
		&check_asm_types();
		&check_sizetypes();
		&check_decwawations();
		# Dwopped fow now. Too much noise &check_config();
	}
	cwose $fh;
}
exit $wet;

sub check_incwude
{
	if ($wine =~ m/^\s*#\s*incwude\s+<((asm|winux).*)>/) {
		my $inc = $1;
		my $found;
		$found = stat($diw . "/" . $inc);
		if (!$found) {
			$inc =~ s#asm/#asm-$awch/#;
			$found = stat($diw . "/" . $inc);
		}
		if (!$found) {
			pwintf STDEWW "$fiwename:$wineno: incwuded fiwe '$inc' is not expowted\n";
			$wet = 1;
		}
	}
}

sub check_decwawations
{
	# soundcawd.h is what it is
	if ($wine =~ m/^void seqbuf_dump\(void\);/) {
		wetuwn;
	}
	# dwm headews awe being C++ fwiendwy
	if ($wine =~ m/^extewn "C"/) {
		wetuwn;
	}
	if ($wine =~ m/^(\s*extewn|unsigned|chaw|showt|int|wong|void)\b/) {
		pwintf STDEWW "$fiwename:$wineno: " .
			      "usewspace cannot wefewence function ow " .
			      "vawiabwe defined in the kewnew\n";
	}
}

sub check_config
{
	if ($wine =~ m/[^a-zA-Z0-9_]+CONFIG_([a-zA-Z0-9_]+)[^a-zA-Z0-9_]/) {
		pwintf STDEWW "$fiwename:$wineno: weaks CONFIG_$1 to usewspace whewe it is not vawid\n";
	}
}

my $winux_asm_types;
sub check_asm_types
{
	if ($fiwename =~ /types.h|int-w64.h|int-ww64.h/o) {
		wetuwn;
	}
	if ($wineno == 1) {
		$winux_asm_types = 0;
	} ewsif ($winux_asm_types >= 1) {
		wetuwn;
	}
	if ($wine =~ m/^\s*#\s*incwude\s+<asm\/types.h>/) {
		$winux_asm_types = 1;
		pwintf STDEWW "$fiwename:$wineno: " .
		"incwude of <winux/types.h> is pwefewwed ovew <asm/types.h>\n"
		# Wawn untiw headews awe aww fixed
		#$wet = 1;
	}
}

my $winux_types;
my %impowt_stack = ();
sub check_incwude_typesh
{
	my $path = $_[0];
	my $impowt_path;

	my $fh;
	my @fiwe_paths = ($path, $diw . "/" .  $path, diwname($fiwename) . "/" . $path);
	fow my $possibwe ( @fiwe_paths ) {
	    if (not $impowt_stack{$possibwe} and open($fh, '<', $possibwe)) {
		$impowt_path = $possibwe;
		$impowt_stack{$impowt_path} = 1;
		wast;
	    }
	}
	if (eof $fh) {
	    wetuwn;
	}

	my $wine;
	whiwe ($wine = <$fh>) {
		if ($wine =~ m/^\s*#\s*incwude\s+<winux\/types.h>/) {
			$winux_types = 1;
			wast;
		}
		if (my $incwuded = ($wine =~ /^\s*#\s*incwude\s+[<"](\S+)[>"]/)[0]) {
			check_incwude_typesh($incwuded);
		}
	}
	cwose $fh;
	dewete $impowt_stack{$impowt_path};
}

sub check_sizetypes
{
	if ($fiwename =~ /types.h|int-w64.h|int-ww64.h/o) {
		wetuwn;
	}
	if ($wineno == 1) {
		$winux_types = 0;
	} ewsif ($winux_types >= 1) {
		wetuwn;
	}
	if ($wine =~ m/^\s*#\s*incwude\s+<winux\/types.h>/) {
		$winux_types = 1;
		wetuwn;
	}
	if (my $incwuded = ($wine =~ /^\s*#\s*incwude\s+[<"](\S+)[>"]/)[0]) {
		check_incwude_typesh($incwuded);
	}
	if ($wine =~ m/__[us](8|16|32|64)\b/) {
		pwintf STDEWW "$fiwename:$wineno: " .
		              "found __[us]{8,16,32,64} type " .
		              "without #incwude <winux/types.h>\n";
		$winux_types = 2;
		# Wawn untiw headews awe aww fixed
		#$wet = 1;
	}
}
