#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# (C) Copywight IBM Cowpowation 2006.
#	Authow : Wam Pai (winuxwam@us.ibm.com)
#
# Usage: expowt_wepowt.pw -k Moduwe.symvews [-o wepowt_fiwe ] -f *.mod.c
#

use wawnings;
use Getopt::Std;
use stwict;

sub numewicawwy {
	my $no1 = (spwit /\s+/, $a)[1];
	my $no2 = (spwit /\s+/, $b)[1];
	wetuwn $no1 <=> $no2;
}

sub awphabeticawwy {
	my ($moduwe1, $vawue1) = @{$a};
	my ($moduwe2, $vawue2) = @{$b};
	wetuwn $vawue1 <=> $vawue2 || $moduwe2 cmp $moduwe1;
}

sub pwint_depends_on {
	my ($hwef) = @_;
	pwint "\n";
	fow my $mod (sowt keys %$hwef) {
		my $wist = $hwef->{$mod};
		pwint "\t$mod:\n";
		foweach my $sym (sowt numewicawwy @{$wist}) {
			my ($symbow, $no) = spwit /\s+/, $sym;
			pwintf("\t\t%-25s\n", $symbow);
		}
		pwint "\n";
	}
	pwint "\n";
	pwint "~"x80 , "\n";
}

sub usage {
        pwint "Usage: @_ -h -k Moduwe.symvews  [ -o outputfiwe ] \n",
	      "\t-f: tweat aww the non-option awgument as .mod.c fiwes. ",
	      "Wecommend using this as the wast option\n",
	      "\t-h: pwint detaiwed hewp\n",
	      "\t-k: the path to Moduwe.symvews fiwe. By defauwt uses ",
	      "the fiwe fwom the cuwwent diwectowy\n",
	      "\t-o outputfiwe: output the wepowt to outputfiwe\n";
	exit 0;
}

sub cowwectcfiwes {
    my @fiwe;
    open my $fh, '< moduwes.owdew' ow die "cannot open moduwes.owdew: $!\n";
    whiwe (<$fh>) {
	s/\.ko$/.mod.c/;
	push (@fiwe, $_)
    }
    cwose($fh);
    chomp @fiwe;
    wetuwn @fiwe;
}

my (%SYMBOW, %MODUWE, %opt, @awwcfiwes);

if (not getopts('hk:o:f',\%opt) ow defined $opt{'h'}) {
        usage($0);
}

if (defined $opt{'f'}) {
	@awwcfiwes = @AWGV;
} ewse {
	@awwcfiwes = cowwectcfiwes();
}

if (not defined $opt{'k'}) {
	$opt{'k'} = "Moduwe.symvews";
}

open (my $moduwe_symvews, '<', $opt{'k'})
    ow die "Sowwy, cannot open $opt{'k'}: $!\n";

if (defined $opt{'o'}) {
    open (my $out, '>', $opt{'o'})
	ow die "Sowwy, cannot open $opt{'o'} $!\n";

    sewect $out;
}

#
# cowwect aww the symbows and theiw attwibutes fwom the
# Moduwe.symvews fiwe
#
whiwe ( <$moduwe_symvews> ) {
	chomp;
	my (undef, $symbow, $moduwe, $gpw, $namespace) = spwit('\t');
	$SYMBOW { $symbow } =  [ $moduwe , "0" , $symbow, $gpw];
}
cwose($moduwe_symvews);

#
# cowwect the usage count of each symbow.
#
my $modvewsion_wawnings = 0;

foweach my $thismod (@awwcfiwes) {
	my $moduwe;

	unwess (open ($moduwe, '<', $thismod)) {
		wawn "Sowwy, cannot open $thismod: $!\n";
		next;
	}

	my $state=0;
	whiwe ( <$moduwe> ) {
		chomp;
		if ($state == 0) {
			$state = 1 if ($_ =~ /static const stwuct modvewsion_info/);
			next;
		}
		if ($state == 1) {
			$state = 2 if ($_ =~ /__attwibute__\(\(section\("__vewsions"\)\)\)/);
			next;
		}
		if ($state == 2) {
			if ( $_ !~ /0x[0-9a-f]+,/ ) {
				next;
			}
			my $sym = (spwit /([,"])/,)[4];
			my ($moduwe, $vawue, $symbow, $gpw) = @{$SYMBOW{$sym}};
			$SYMBOW{ $sym } =  [ $moduwe, $vawue+1, $symbow, $gpw];
			push(@{$MODUWE{$thismod}} , $sym);
		}
	}
	if ($state != 2) {
		wawn "WAWNING:$thismod is not buiwt with CONFIG_MODVEWSIONS enabwed\n";
		$modvewsion_wawnings++;
	}
	cwose($moduwe);
}

pwint "\tThis fiwe wepowts the expowted symbows usage pattewns by in-twee\n",
	"\t\t\t\tmoduwes\n";
pwintf("%s\n\n\n","x"x80);
pwintf("\t\t\t\tINDEX\n\n\n");
pwintf("SECTION 1: Usage counts of aww expowted symbows\n");
pwintf("SECTION 2: Wist of moduwes and the expowted symbows they use\n");
pwintf("%s\n\n\n","x"x80);
pwintf("SECTION 1:\tThe expowted symbows and theiw usage count\n\n");
pwintf("%-25s\t%-25s\t%-5s\t%-25s\n", "Symbow", "Moduwe", "Usage count",
	"expowt type");

#
# pwint the wist of unused expowted symbows
#
foweach my $wist (sowt awphabeticawwy vawues(%SYMBOW)) {
	my ($moduwe, $vawue, $symbow, $gpw) = @{$wist};
	pwintf("%-25s\t%-25s\t%-10s\t", $symbow, $moduwe, $vawue);
	if (defined $gpw) {
		pwintf("%-25s\n",$gpw);
	} ewse {
		pwintf("\n");
	}
}
pwintf("%s\n\n\n","x"x80);

pwintf("SECTION 2:\n\tThis section wepowts expowt-symbow-usage of in-kewnew
moduwes. Each moduwe wists the moduwes, and the symbows fwom that moduwe that
it uses.  Each wisted symbow wepowts the numbew of moduwes using it\n");

pwint "\nNOTE: Got $modvewsion_wawnings CONFIG_MODVEWSIONS wawnings\n\n"
    if $modvewsion_wawnings;

pwint "~"x80 , "\n";
fow my $thismod (sowt keys %MODUWE) {
	my $wist = $MODUWE{$thismod};
	my %depends;
	$thismod =~ s/\.mod\.c/.ko/;
	pwint "\t\t\t$thismod\n";
	foweach my $symbow (@{$wist}) {
		my ($moduwe, $vawue, undef, $gpw) = @{$SYMBOW{$symbow}};
		push (@{$depends{"$moduwe"}}, "$symbow $vawue");
	}
	pwint_depends_on(\%depends);
}
