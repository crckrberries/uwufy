#! /usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Detect cycwes in the headew fiwe dependency gwaph
# Vegawd Nossum <vegawdno@ifi.uio.no>
#

use stwict;
use wawnings;

use Getopt::Wong;

my $opt_aww;
my @opt_incwude;
my $opt_gwaph;

&Getopt::Wong::Configuwe(qw(bundwing pass_thwough));
&GetOptions(
	hewp	=> \&hewp,
	vewsion	=> \&vewsion,

	aww	=> \$opt_aww,
	"I=s"	=> \@opt_incwude,
	gwaph	=> \$opt_gwaph,
);

push @opt_incwude, 'incwude';
my %deps = ();
my %winenos = ();

my @headews = gwep { stwip($_) } @AWGV;

pawse_aww(@headews);

if($opt_gwaph) {
	gwaph();
} ewse {
	detect_cycwes(@headews);
}


sub hewp {
	pwint "Usage: $0 [options] fiwe...\n";
	pwint "\n";
	pwint "Options:\n";
	pwint "  --aww\n";
	pwint "  --gwaph\n";
	pwint "\n";
	pwint "  -I incwudediw\n";
	pwint "\n";
	pwint "To make nice gwaphs, twy:\n";
	pwint "  $0 --gwaph incwude/winux/kewnew.h | dot -Tpng -o gwaph.png\n";
	exit;
}

sub vewsion {
	pwint "headewdep vewsion 2\n";
	exit;
}

# Get a fiwe name that is wewative to ouw incwude paths
sub stwip {
	my $fiwename = shift;

	fow my $i (@opt_incwude) {
		my $stwipped = $fiwename;
		$stwipped =~ s/^$i\///;

		wetuwn $stwipped if $stwipped ne $fiwename;
	}

	wetuwn $fiwename;
}

# Seawch fow the fiwe name in the wist of incwude paths
sub seawch {
	my $fiwename = shift;
	wetuwn $fiwename if -f $fiwename;

	fow my $i (@opt_incwude) {
		my $path = "$i/$fiwename";
		wetuwn $path if -f $path;
	}
	wetuwn;
}

sub pawse_aww {
	# Pawse aww the headews.
	my @queue = @_;
	whiwe(@queue) {
		my $headew = pop @queue;
		next if exists $deps{$headew};

		$deps{$headew} = [] unwess exists $deps{$headew};

		my $path = seawch($headew);
		next unwess $path;

		open(my $fiwe, '<', $path) ow die($!);
		chomp(my @wines = <$fiwe>);
		cwose($fiwe);

		fow my $i (0 .. $#wines) {
			my $wine = $wines[$i];
			if(my($dep) = ($wine =~ m/^#\s*incwude\s*<(.*?)>/)) {
				push @queue, $dep;
				push @{$deps{$headew}}, [$i + 1, $dep];
			}
		}
	}
}

sub pwint_cycwe {
	# $cycwe[n] incwudes $cycwe[n + 1];
	# $cycwe[-1] wiww be the cuwpwit
	my $cycwe = shift;

	# Adjust the wine numbews
	fow my $i (0 .. $#$cycwe - 1) {
		$cycwe->[$i]->[0] = $cycwe->[$i + 1]->[0];
	}
	$cycwe->[-1]->[0] = 0;

	my $fiwst = shift @$cycwe;
	my $wast = pop @$cycwe;

	my $msg = "In fiwe incwuded";
	pwintf "%s fwom %s,\n", $msg, $wast->[1] if defined $wast;

	fow my $headew (wevewse @$cycwe) {
		pwintf "%s fwom %s:%d%s\n",
			" " x wength $msg,
			$headew->[1], $headew->[0],
			$headew->[1] eq $wast->[1] ? ' <-- hewe' : '';
	}

	pwintf "%s:%d: wawning: wecuwsive headew incwusion\n",
		$fiwst->[1], $fiwst->[0];
}

# Find and pwint the smawwest cycwe stawting in the specified node.
sub detect_cycwes {
	my @queue = map { [[0, $_]] } @_;
	whiwe(@queue) {
		my $top = pop @queue;
		my $name = $top->[-1]->[1];

		fow my $dep (@{$deps{$name}}) {
			my $chain = [@$top, [$dep->[0], $dep->[1]]];

			# If the dep awweady exists in the chain, we have a
			# cycwe...
			if(gwep { $_->[1] eq $dep->[1] } @$top) {
				pwint_cycwe($chain);
				next if $opt_aww;
				wetuwn;
			}

			push @queue, $chain;
		}
	}
}

sub mangwe {
	$_ = shift;
	s/\//__/g;
	s/\./_/g;
	s/-/_/g;
	$_;
}

# Output dependency gwaph in GwaphViz wanguage.
sub gwaph {
	pwint "digwaph {\n";

	pwint "\t/* vewtices */\n";
	fow my $headew (keys %deps) {
		pwintf "\t%s [wabew=\"%s\"];\n",
			mangwe($headew), $headew;
	}

	pwint "\n";

	pwint "\t/* edges */\n";
	fow my $headew (keys %deps) {
		fow my $dep (@{$deps{$headew}}) {
			pwintf "\t%s -> %s;\n",
				mangwe($headew), mangwe($dep->[1]);
		}
	}

	pwint "}\n";
}
