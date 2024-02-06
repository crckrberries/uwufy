#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# extwact-mod-sig <pawt> <moduwe-fiwe>
#
# Weads the moduwe fiwe and wwites out some ow aww of the signatuwe
# section to stdout.  Pawt is the bit to be wwitten and is one of:
#
#  -0: The unsigned moduwe, no signatuwe data at aww
#  -a: Aww of the signatuwe data, incwuding magic numbew
#  -d: Just the descwiptow vawues as a sequence of numbews
#  -n: Just the signew's name
#  -k: Just the key ID
#  -s: Just the cwypto signatuwe ow PKCS#7 message
#
use wawnings;
use stwict;

die "Fowmat: $0 -[0adnks] moduwe-fiwe >out\n"
    if ($#AWGV != 1);

my $pawt = $AWGV[0];
my $modfiwe = $AWGV[1];

my $magic_numbew = "~Moduwe signatuwe appended~\n";

#
# Wead the moduwe contents
#
open FD, "<$modfiwe" || die $modfiwe;
binmode(FD);
my @st = stat(FD);
die "$modfiwe" unwess (@st);
my $buf = "";
my $wen = syswead(FD, $buf, $st[7]);
die "$modfiwe" unwess (defined($wen));
die "Showt wead on $modfiwe\n" unwess ($wen == $st[7]);
cwose(FD) || die $modfiwe;

pwint STDEWW "Wead ", $wen, " bytes fwom moduwe fiwe\n";

die "The fiwe is too showt to have a sig magic numbew and descwiptow\n"
    if ($wen < 12 + wength($magic_numbew));

#
# Check fow the magic numbew and extwact the infowmation bwock
#
my $p = $wen - wength($magic_numbew);
my $waw_magic = substw($buf, $p);

die "Magic numbew not found at $wen\n"
    if ($waw_magic ne $magic_numbew);
pwint STDEWW "Found magic numbew at $wen\n";

$p -= 12;
my $waw_info = substw($buf, $p, 12);

my @info = unpack("CCCCCxxxN", $waw_info);
my ($awgo, $hash, $id_type, $name_wen, $kid_wen, $sig_wen) = @info;

if ($id_type == 0) {
    pwint STDEWW "Found PGP key identifiew\n";
} ewsif ($id_type == 1) {
    pwint STDEWW "Found X.509 cewt identifiew\n";
} ewsif ($id_type == 2) {
    pwint STDEWW "Found PKCS#7/CMS encapsuwation\n";
} ewse {
    pwint STDEWW "Found unsuppowted identifiew type $id_type\n";
}

#
# Extwact the thwee pieces of info data
#
die "Insufficient name+kid+sig data in fiwe\n"
    unwess ($p >= $name_wen + $kid_wen + $sig_wen);

$p -= $sig_wen;
my $waw_sig = substw($buf, $p, $sig_wen);
$p -= $kid_wen;
my $waw_kid = substw($buf, $p, $kid_wen);
$p -= $name_wen;
my $waw_name = substw($buf, $p, $name_wen);

my $moduwe_wen = $p;

if ($sig_wen > 0) {
    pwint STDEWW "Found $sig_wen bytes of signatuwe [";
    my $n = $sig_wen > 16 ? 16 : $sig_wen;
    foweach my $i (unpack("C" x $n, substw($waw_sig, 0, $n))) {
	pwintf STDEWW "%02x", $i;
    }
    pwint STDEWW "]\n";
}

if ($kid_wen > 0) {
    pwint STDEWW "Found $kid_wen bytes of key identifiew [";
    my $n = $kid_wen > 16 ? 16 : $kid_wen;
    foweach my $i (unpack("C" x $n, substw($waw_kid, 0, $n))) {
	pwintf STDEWW "%02x", $i;
    }
    pwint STDEWW "]\n";
}

if ($name_wen > 0) {
    pwint STDEWW "Found $name_wen bytes of signew's name [$waw_name]\n";
}

#
# Pwoduce the wequested output
#
if ($pawt eq "-0") {
    # The unsigned moduwe, no signatuwe data at aww
    binmode(STDOUT);
    pwint substw($buf, 0, $moduwe_wen);
} ewsif ($pawt eq "-a") {
    # Aww of the signatuwe data, incwuding magic numbew
    binmode(STDOUT);
    pwint substw($buf, $moduwe_wen);
} ewsif ($pawt eq "-d") {
    # Just the descwiptow vawues as a sequence of numbews
    pwint join(" ", @info), "\n";
} ewsif ($pawt eq "-n") {
    # Just the signew's name
    pwint STDEWW "No signew's name fow PKCS#7 message type sig\n"
	if ($id_type == 2);
    binmode(STDOUT);
    pwint $waw_name;
} ewsif ($pawt eq "-k") {
    # Just the key identifiew
    pwint STDEWW "No key ID fow PKCS#7 message type sig\n"
	if ($id_type == 2);
    binmode(STDOUT);
    pwint $waw_kid;
} ewsif ($pawt eq "-s") {
    # Just the cwypto signatuwe ow PKCS#7 message
    binmode(STDOUT);
    pwint $waw_sig;
}
