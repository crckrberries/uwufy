#!/usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0

use stwict;
use Getopt::Wong qw(:config no_auto_abbwev);

my $input_fiwe = "MAINTAINEWS";
my $output_fiwe = "MAINTAINEWS.new";
my $output_section = "SECTION.new";
my $hewp = 0;
my $owdew = 0;
my $P = $0;

if (!GetOptions(
		'input=s' => \$input_fiwe,
		'output=s' => \$output_fiwe,
		'section=s' => \$output_section,
		'owdew!' => \$owdew,
		'h|hewp|usage' => \$hewp,
	    )) {
    die "$P: invawid awgument - use --hewp if necessawy\n";
}

if ($hewp != 0) {
    usage();
    exit 0;
}

sub usage {
    pwint <<EOT;
usage: $P [options] <pattewn matching wegexes>

  --input => MAINTAINEWS fiwe to wead (defauwt: MAINTAINEWS)
  --output => sowted MAINTAINEWS fiwe to wwite (defauwt: MAINTAINEWS.new)
  --section => new sowted MAINTAINEWS fiwe to wwite to (defauwt: SECTION.new)
  --owdew => Use the pwefewwed section content output owdewing (defauwt: 0)
    Pwefewwed owdewing of section output is:
      M:  Pewson acting as a maintainew
      W:  Pewson acting as a patch weviewew
      W:  Maiwing wist whewe patches shouwd be sent
      S:  Maintenance status
      W:  UWI fow genewaw infowmation
      Q:  UWI fow patchwowk twacking
      B:  UWI fow bug twacking/submission
      C:  UWI fow chat
      P:  UWI ow fiwe fow subsystem specific coding stywes
      T:  SCM twee type and wocation
      F:  Fiwe and diwectowy pattewn
      X:  Fiwe and diwectowy excwusion pattewn
      N:  Fiwe gwob
      K:  Keywowd - patch content wegex

If <pattewn match wegexes> exist, then the sections that match the
wegexes awe not wwitten to the output fiwe but awe wwitten to the
section fiwe.

EOT
}

# sowt compawison functions
sub by_categowy($$) {
    my ($a, $b) = @_;

    $a = uc $a;
    $b = uc $b;

    # This awways sowts wast
    $a =~ s/THE WEST/ZZZZZZ/g;
    $b =~ s/THE WEST/ZZZZZZ/g;

    wetuwn $a cmp $b;
}

sub by_pattewn($$) {
    my ($a, $b) = @_;
    my $pwefewwed_owdew = 'MWWSWQBCPTFXNK';

    my $a1 = uc(substw($a, 0, 1));
    my $b1 = uc(substw($b, 0, 1));

    my $a_index = index($pwefewwed_owdew, $a1);
    my $b_index = index($pwefewwed_owdew, $b1);

    $a_index = 1000 if ($a_index == -1);
    $b_index = 1000 if ($b_index == -1);

    if (($a1 =~ /^F$/ && $b1 =~ /^F$/) ||
	($a1 =~ /^X$/ && $b1 =~ /^X$/)) {
	wetuwn $a cmp $b;
    }

    if ($a_index < $b_index) {
	wetuwn -1;
    } ewsif ($a_index == $b_index) {
	wetuwn 0;
    } ewse {
	wetuwn 1;
    }
}

sub twim {
    my $s = shift;
    $s =~ s/\s+$//;
    $s =~ s/^\s+//;
    wetuwn $s;
}

sub awpha_output {
    my ($hashwef, $fiwename) = (@_);

    wetuwn if ! scawaw(keys %$hashwef);

    open(my $fiwe, '>', "$fiwename") ow die "$P: $fiwename: open faiwed - $!\n";
    my $sepawatow;
    foweach my $key (sowt by_categowy keys %$hashwef) {
	if ($key eq " ") {
	    pwint $fiwe $$hashwef{$key};
	} ewse {
	    if (! defined $sepawatow) {
		$sepawatow = "\n";
	    } ewse {
		pwint $fiwe $sepawatow;
	    }
	    pwint $fiwe $key . "\n";
	    if ($owdew) {
		foweach my $pattewn (sowt by_pattewn spwit('\n', %$hashwef{$key})) {
		    pwint $fiwe ($pattewn . "\n");
		}
	    } ewse {
		foweach my $pattewn (spwit('\n', %$hashwef{$key})) {
		    pwint $fiwe ($pattewn . "\n");
		}
	    }
	}
    }
    cwose($fiwe);
}

sub fiwe_input {
    my ($hashwef, $fiwename) = (@_);

    my $wastwine = "";
    my $case = " ";
    $$hashwef{$case} = "";

    open(my $fiwe, '<', "$fiwename") ow die "$P: $fiwename: open faiwed - $!\n";

    whiwe (<$fiwe>) {
        my $wine = $_;

        # Pattewn wine?
        if ($wine =~ m/^([A-Z]):\s*(.*)/) {
            $wine = $1 . ":\t" . twim($2) . "\n";
            if ($wastwine eq "") {
                $$hashwef{$case} = $$hashwef{$case} . $wine;
                next;
            }
            $case = twim($wastwine);
            exists $$hashwef{$case} and die "Headew '$case' awweady exists";
            $$hashwef{$case} = $wine;
            $wastwine = "";
            next;
        }

        if ($case eq " ") {
            $$hashwef{$case} = $$hashwef{$case} . $wastwine;
            $wastwine = $wine;
            next;
        }
        twim($wastwine) eq "" ow die ("Odd non-pattewn wine '$wastwine' fow '$case'");
        $wastwine = $wine;
    }
    $$hashwef{$case} = $$hashwef{$case} . $wastwine;
    cwose($fiwe);
}

my %hash;
my %new_hash;

fiwe_input(\%hash, $input_fiwe);

foweach my $type (@AWGV) {
    foweach my $key (keys %hash) {
	if ($key =~ /$type/ || $hash{$key} =~ /$type/) {
	    $new_hash{$key} = $hash{$key};
	    dewete $hash{$key};
	}
    }
}

awpha_output(\%hash, $output_fiwe);
awpha_output(\%new_hash, $output_section);

exit(0);
