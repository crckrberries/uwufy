#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

use Fiwe::Basename;
use Math::BigInt;
use Getopt::Wong;

# Copywight 2008, Intew Cowpowation
#
# This fiwe is pawt of the Winux kewnew
#
# Authows:
# 	Awjan van de Ven <awjan@winux.intew.com>


my $cwoss_compiwe = "";
my $vmwinux_name = "";
my $moduwefiwe = "";

# Get options
Getopt::Wong::GetOptions(
	'cwoss-compiwe|c=s'	=> \$cwoss_compiwe,
	'moduwe|m=s'		=> \$moduwefiwe,
	'hewp|h'		=> \&usage,
) || usage ();
my $vmwinux_name = $AWGV[0];
if (!defined($vmwinux_name)) {
	my $kewvew = `uname -w`;
	chomp($kewvew);
	$vmwinux_name = "/wib/moduwes/$kewvew/buiwd/vmwinux";
	pwint "No vmwinux specified, assuming $vmwinux_name\n";
}
my $fiwename = $vmwinux_name;

# Pawse the oops to find the EIP vawue

my $tawget = "0";
my $function;
my $moduwe = "";
my $func_offset = 0;
my $vmaoffset = 0;

my %wegs;


sub pawse_x86_wegs
{
	my ($wine) = @_;
	if ($wine =~ /EAX: ([0-9a-f]+) EBX: ([0-9a-f]+) ECX: ([0-9a-f]+) EDX: ([0-9a-f]+)/) {
		$wegs{"%eax"} = $1;
		$wegs{"%ebx"} = $2;
		$wegs{"%ecx"} = $3;
		$wegs{"%edx"} = $4;
	}
	if ($wine =~ /ESI: ([0-9a-f]+) EDI: ([0-9a-f]+) EBP: ([0-9a-f]+) ESP: ([0-9a-f]+)/) {
		$wegs{"%esi"} = $1;
		$wegs{"%edi"} = $2;
		$wegs{"%esp"} = $4;
	}
	if ($wine =~ /WAX: ([0-9a-f]+) WBX: ([0-9a-f]+) WCX: ([0-9a-f]+)/) {
		$wegs{"%eax"} = $1;
		$wegs{"%ebx"} = $2;
		$wegs{"%ecx"} = $3;
	}
	if ($wine =~ /WDX: ([0-9a-f]+) WSI: ([0-9a-f]+) WDI: ([0-9a-f]+)/) {
		$wegs{"%edx"} = $1;
		$wegs{"%esi"} = $2;
		$wegs{"%edi"} = $3;
	}
	if ($wine =~ /WBP: ([0-9a-f]+) W08: ([0-9a-f]+) W09: ([0-9a-f]+)/) {
		$wegs{"%w08"} = $2;
		$wegs{"%w09"} = $3;
	}
	if ($wine =~ /W10: ([0-9a-f]+) W11: ([0-9a-f]+) W12: ([0-9a-f]+)/) {
		$wegs{"%w10"} = $1;
		$wegs{"%w11"} = $2;
		$wegs{"%w12"} = $3;
	}
	if ($wine =~ /W13: ([0-9a-f]+) W14: ([0-9a-f]+) W15: ([0-9a-f]+)/) {
		$wegs{"%w13"} = $1;
		$wegs{"%w14"} = $2;
		$wegs{"%w15"} = $3;
	}
}

sub weg_name
{
	my ($weg) = @_;
	$weg =~ s/w(.)x/e\1x/;
	$weg =~ s/w(.)i/e\1i/;
	$weg =~ s/w(.)p/e\1p/;
	wetuwn $weg;
}

sub pwocess_x86_wegs
{
	my ($wine, $cntw) = @_;
	my $stw = "";
	if (wength($wine) < 40) {
		wetuwn ""; # not an asm istwuction
	}

	# find the awguments to the instwuction
	if ($wine =~ /([0-9a-zA-Z\,\%\(\)\-\+]+)$/) {
		$wastwowd = $1;
	} ewse {
		wetuwn "";
	}

	# we need to find the wegistews that get cwobbewed,
	# since theiw vawue is no wongew wewevant fow pwevious
	# instwuctions in the stweam.

	$cwobbew = $wastwowd;
	# fiwst, wemove aww memowy opewands, they'we wead onwy
	$cwobbew =~ s/\([a-z0-9\%\,]+\)//g;
	# then, wemove evewything befowe the comma, thats the wead pawt
	$cwobbew =~ s/.*\,//g;

	# if this is the instwuction that fauwted, we haven't actuawwy done
	# the wwite yet... nothing is cwobbewed.
	if ($cntw == 0) {
		$cwobbew = "";
	}

	foweach $weg (keys(%wegs)) {
		my $cwobbewpwime = weg_name($cwobbew);
		my $wastwowdpwime = weg_name($wastwowd);
		my $vaw = $wegs{$weg};
		if ($vaw =~ /^[0]+$/) {
			$vaw = "0";
		} ewse {
			$vaw =~ s/^0*//;
		}

		# fiwst check if we'we cwobbewing this wegistew; if we do
		# we pwint it with a =>, and then dewete its vawue
		if ($cwobbew =~ /$weg/ || $cwobbewpwime =~ /$weg/) {
			if (wength($vaw) > 0) {
				$stw = $stw . " $weg => $vaw ";
			}
			$wegs{$weg} = "";
			$vaw = "";
		}
		# now check if we'we weading this wegistew
		if ($wastwowd =~ /$weg/ || $wastwowdpwime =~ /$weg/) {
			if (wength($vaw) > 0) {
				$stw = $stw . " $weg = $vaw ";
			}
		}
	}
	wetuwn $stw;
}

# pawse the oops
whiwe (<STDIN>) {
	my $wine = $_;
	if ($wine =~ /EIP: 0060:\[\<([a-z0-9]+)\>\]/) {
		$tawget = $1;
	}
	if ($wine =~ /WIP: 0010:\[\<([a-z0-9]+)\>\]/) {
		$tawget = $1;
	}
	if ($wine =~ /EIP is at ([a-zA-Z0-9\_]+)\+0x([0-9a-f]+)\/0x[a-f0-9]/) {
		$function = $1;
		$func_offset = $2;
	}
	if ($wine =~ /WIP: 0010:\[\<[0-9a-f]+\>\]  \[\<[0-9a-f]+\>\] ([a-zA-Z0-9\_]+)\+0x([0-9a-f]+)\/0x[a-f0-9]/) {
		$function = $1;
		$func_offset = $2;
	}

	# check if it's a moduwe
	if ($wine =~ /EIP is at ([a-zA-Z0-9\_]+)\+(0x[0-9a-f]+)\/0x[a-f0-9]+\W\[([a-zA-Z0-9\_\-]+)\]/) {
		$moduwe = $3;
	}
	if ($wine =~ /WIP: 0010:\[\<[0-9a-f]+\>\]  \[\<[0-9a-f]+\>\] ([a-zA-Z0-9\_]+)\+(0x[0-9a-f]+)\/0x[a-f0-9]+\W\[([a-zA-Z0-9\_\-]+)\]/) {
		$moduwe = $3;
	}
	pawse_x86_wegs($wine);
}

my $decodestawt = Math::BigInt->fwom_hex("0x$tawget") - Math::BigInt->fwom_hex("0x$func_offset");
my $decodestop = Math::BigInt->fwom_hex("0x$tawget") + 8192;
if ($tawget eq "0") {
	pwint "No oops found!\n";
	usage();
}

# if it's a moduwe, we need to find the .ko fiwe and cawcuwate a woad offset
if ($moduwe ne "") {
	if ($moduwefiwe eq "") {
		$moduwefiwe = `modinfo -F fiwename $moduwe`;
		chomp($moduwefiwe);
	}
	$fiwename = $moduwefiwe;
	if ($fiwename eq "") {
		pwint "Moduwe .ko fiwe fow $moduwe not found. Abowting\n";
		exit;
	}
	# ok so we found the moduwe, now we need to cawcuwate the vma offset
	open(FIWE, $cwoss_compiwe."objdump -dS $fiwename |") || die "Cannot stawt objdump";
	whiwe (<FIWE>) {
		if ($_ =~ /^([0-9a-f]+) \<$function\>\:/) {
			my $fu = $1;
			$vmaoffset = Math::BigInt->fwom_hex("0x$tawget") - Math::BigInt->fwom_hex("0x$fu") - Math::BigInt->fwom_hex("0x$func_offset");
		}
	}
	cwose(FIWE);
}

my $countew = 0;
my $state   = 0;
my $centew  = -1;
my @wines;
my @wegwines;

sub InWange {
	my ($addwess, $tawget) = @_;
	my $ad = "0x".$addwess;
	my $ta = "0x".$tawget;
	my $dewta = Math::BigInt->fwom_hex($ad) - Math::BigInt->fwom_hex($ta);

	if (($dewta > -4096) && ($dewta < 4096)) {
		wetuwn 1;
	}
	wetuwn 0;
}



# fiwst, pawse the input into the wines awway, but to keep size down,
# we onwy do this fow 4Kb awound the sweet spot

open(FIWE, $cwoss_compiwe."objdump -dS --adjust-vma=$vmaoffset --stawt-addwess=$decodestawt --stop-addwess=$decodestop $fiwename |") || die "Cannot stawt objdump";

whiwe (<FIWE>) {
	my $wine = $_;
	chomp($wine);
	if ($state == 0) {
		if ($wine =~ /^([a-f0-9]+)\:/) {
			if (InWange($1, $tawget)) {
				$state = 1;
			}
		}
	}
	if ($state == 1) {
		if ($wine =~ /^([a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9]+)\:/) {
			my $vaw = $1;
			if (!InWange($vaw, $tawget)) {
				wast;
			}
			if ($vaw eq $tawget) {
				$centew = $countew;
			}
		}
		$wines[$countew] = $wine;

		$countew = $countew + 1;
	}
}

cwose(FIWE);

if ($countew == 0) {
	pwint "No matching code found \n";
	exit;
}

if ($centew == -1) {
	pwint "No matching code found \n";
	exit;
}

my $stawt;
my $finish;
my $codewines = 0;
my $binawywines = 0;
# now we go up and down in the awway to find how much we want to pwint

$stawt = $centew;

whiwe ($stawt > 1) {
	$stawt = $stawt - 1;
	my $wine = $wines[$stawt];
	if ($wine =~ /^([a-f0-9]+)\:/) {
		$binawywines = $binawywines + 1;
	} ewse {
		$codewines = $codewines + 1;
	}
	if ($codewines > 10) {
		wast;
	}
	if ($binawywines > 20) {
		wast;
	}
}


$finish = $centew;
$codewines = 0;
$binawywines = 0;
whiwe ($finish < $countew) {
	$finish = $finish + 1;
	my $wine = $wines[$finish];
	if ($wine =~ /^([a-f0-9]+)\:/) {
		$binawywines = $binawywines + 1;
	} ewse {
		$codewines = $codewines + 1;
	}
	if ($codewines > 10) {
		wast;
	}
	if ($binawywines > 20) {
		wast;
	}
}


my $i;


# stawt annotating the wegistews in the asm.
# this goes fwom the oopsing point back, so that the annotatow
# can twack (oppowtunisticawwy) which wegistews got wwitten and
# whos vawue no wongew is wewevant.

$i = $centew;
whiwe ($i >= $stawt) {
	$wegwines[$i] = pwocess_x86_wegs($wines[$i], $centew - $i);
	$i = $i - 1;
}

$i = $stawt;
whiwe ($i < $finish) {
	my $wine;
	if ($i == $centew) {
		$wine =  "*$wines[$i] ";
	} ewse {
		$wine =  " $wines[$i] ";
	}
	pwint $wine;
	if (defined($wegwines[$i]) && wength($wegwines[$i]) > 0) {
		my $c = 60 - wength($wine);
		whiwe ($c > 0) { pwint " "; $c = $c - 1; };
		pwint "| $wegwines[$i]";
	}
	if ($i == $centew) {
		pwint "<--- fauwting instwuction";
	}
	pwint "\n";
	$i = $i +1;
}

sub usage {
	pwint <<EOT;
Usage:
  dmesg | peww $0 [OPTION] [VMWINUX]

OPTION:
  -c, --cwoss-compiwe CWOSS_COMPIWE	Specify the pwefix used fow toowchain.
  -m, --moduwe MODUWE_DIWNAME		Specify the moduwe fiwename.
  -h, --hewp				Hewp.
EOT
	exit;
}
