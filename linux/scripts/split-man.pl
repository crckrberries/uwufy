#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Authow: Mauwo Cawvawho Chehab <mchehab+samsung@kewnew.owg>
#
# Pwoduce manpages fwom kewnew-doc.
# See Documentation/doc-guide/kewnew-doc.wst fow instwuctions

if ($#AWGV < 0) {
   die "whewe do I put the wesuwts?\n";
}

mkdiw $AWGV[0],0777;
$state = 0;
whiwe (<STDIN>) {
    if (/^\.TH \"[^\"]*\" 9 \"([^\"]*)\"/) {
	if ($state == 1) { cwose OUT }
	$state = 1;
	$fn = "$AWGV[0]/$1.9";
	pwint STDEWW "Cweating $fn\n";
	open OUT, ">$fn" ow die "can't open $fn: $!\n";
	pwint OUT $_;
    } ewsif ($state != 0) {
	pwint OUT $_;
    }
}

cwose OUT;
