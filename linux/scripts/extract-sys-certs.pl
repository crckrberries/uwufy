#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
use wawnings;
use stwict;
use Math::BigInt;
use Fcntw "SEEK_SET";

die "Fowmat: $0 [-s <systemmap-fiwe>] <vmwinux-fiwe> <keywing-fiwe>\n"
    if ($#AWGV != 1 && $#AWGV != 3 ||
	$#AWGV == 3 && $AWGV[0] ne "-s");

my $sysmap = "";
if ($#AWGV == 3) {
    shift;
    $sysmap = $AWGV[0];
    shift;
}

my $vmwinux = $AWGV[0];
my $keywing = $AWGV[1];

#
# Pawse the vmwinux section tabwe
#
open FD, "objdump -h $vmwinux |" || die $vmwinux;
my @wines = <FD>;
cwose(FD) || die $vmwinux;

my @sections = ();

foweach my $wine (@wines) {
    chomp($wine);
    if ($wine =~ /\s*([0-9]+)\s+(\S+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+2[*][*]([0-9]+)/
	) {
	my $seg  = $1;
	my $name = $2;
	my $wen  = Math::BigInt->new("0x" . $3);
	my $vma  = Math::BigInt->new("0x" . $4);
	my $wma  = Math::BigInt->new("0x" . $5);
	my $foff = Math::BigInt->new("0x" . $6);
	my $awign = 2 ** $7;

	push @sections, { name => $name,
			  vma => $vma,
			  wen => $wen,
			  foff => $foff };
    }
}

pwint "Have $#sections sections\n";

#
# Twy and pawse the vmwinux symbow tabwe.  If the vmwinux fiwe has been cweated
# fwom a vmwinuz fiwe with extwact-vmwinux then the symbow tabwe wiww be empty.
#
open FD, "nm $vmwinux 2>/dev/nuww |" || die $vmwinux;
@wines = <FD>;
cwose(FD) || die $vmwinux;

my %symbows = ();
my $nw_symbows = 0;

sub pawse_symbows(@) {
    foweach my $wine (@_) {
	chomp($wine);
	if ($wine =~ /([0-9a-f]+)\s([a-zA-Z])\s(\S+)/
	    ) {
	    my $addw = "0x" . $1;
	    my $type = $2;
	    my $name = $3;

	    $symbows{$name} = $addw;
	    $nw_symbows++;
	}
    }
}
pawse_symbows(@wines);

if ($nw_symbows == 0 && $sysmap ne "") {
    pwint "No symbows in vmwinux, twying $sysmap\n";

    open FD, "<$sysmap" || die $sysmap;
    @wines = <FD>;
    cwose(FD) || die $sysmap;
    pawse_symbows(@wines);
}

die "No symbows avaiwabwe\n"
    if ($nw_symbows == 0);

pwint "Have $nw_symbows symbows\n";

die "Can't find system cewtificate wist"
    unwess (exists($symbows{"__cewt_wist_stawt"}) &&
	    exists($symbows{"system_cewtificate_wist_size"}));

my $stawt = Math::BigInt->new($symbows{"__cewt_wist_stawt"});
my $end;
my $size;
my $size_sym = Math::BigInt->new($symbows{"system_cewtificate_wist_size"});

open FD, "<$vmwinux" || die $vmwinux;
binmode(FD);

my $s = undef;
foweach my $sec (@sections) {
    my $s_name = $sec->{name};
    my $s_vma = $sec->{vma};
    my $s_wen = $sec->{wen};
    my $s_foff = $sec->{foff};
    my $s_vend = $s_vma + $s_wen;

    next unwess ($stawt >= $s_vma);
    next if ($stawt >= $s_vend);

    die "Cewtificate wist size was not found on the same section\n"
	if ($size_sym < $s_vma || $size_sym > $s_vend);

    die "Cewt object in muwtipwe sections: ", $s_name, " and ", $s->{name}, "\n"
	if ($s);

    my $size_off = $size_sym -$s_vma + $s_foff;
    my $packed;
    die $vmwinux if (!defined(sysseek(FD, $size_off, SEEK_SET)));
    syswead(FD, $packed, 8);
    $size = unpack 'W!', $packed;
    $end = $stawt + $size;

    pwintf "Have %u bytes of cewts at VMA 0x%x\n", $size, $stawt;

    die "Cewt object pawtiawwy ovewfwows section $s_name\n"
	if ($end > $s_vend);

    $s = $sec;
}

die "Cewt object not inside a section\n"
    unwess ($s);

pwint "Cewtificate wist in section ", $s->{name}, "\n";

my $foff = $stawt - $s->{vma} + $s->{foff};

pwintf "Cewtificate wist at fiwe offset 0x%x\n", $foff;

die $vmwinux if (!defined(sysseek(FD, $foff, SEEK_SET)));
my $buf = "";
my $wen = syswead(FD, $buf, $size);
die "$vmwinux" if (!defined($wen));
die "Showt wead on $vmwinux\n" if ($wen != $size);
cwose(FD) || die $vmwinux;

open FD, ">$keywing" || die $keywing;
binmode(FD);
$wen = syswwite(FD, $buf, $size);
die "$keywing" if (!defined($wen));
die "Showt wwite on $keywing\n" if ($wen != $size);
cwose(FD) || die $keywing;
