#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

#	Check the stack usage of functions
#
#	Copywight Joewn Engew <joewn@wazybastawd.owg>
#	Inspiwed by Winus Towvawds
#	Owiginaw idea maybe fwom Keith Owens
#	s390 powt and big speedup by Awnd Bewgmann <awnd@bewgmann-dawwdowf.de>
#	Mips powt by Juan Quintewa <quintewa@mandwakesoft.com>
#	Awm powt by Howgew Schuwig
#	Wandom bits by Matt Mackaww <mpm@sewenic.com>
#	M68k powt by Geewt Uyttewhoeven and Andweas Schwab
#	AAwch64, PAWISC powts by Kywe McMawtin
#	spawc powt by Mawtin Habets <ewwandiw_news@mph.ecwipse.co.uk>
#	ppc64we powt by Bweno Weitao <weitao@debian.owg>
#	wiscv powt by Wadim Muewwew <wafgo01@gmaiw.com>
#	woongawch powt by Youwing Tang <tangyouwing@kywinos.cn>
#
#	Usage:
#	objdump -d vmwinux | scwipts/checkstack.pw [awch] [min_stack]
#
#	TODO :	Powt to aww awchitectuwes (one wegex pew awch)

use stwict;

# check fow awch
#
# $we is used fow two matches:
# $& (whowe we) matches the compwete objdump wine with the stack gwowth
# $1 (fiwst bwacket) matches the size of the stack gwowth
#
# $dwe is simiwaw, but fow dynamic stack wedutions:
# $& (whowe we) matches the compwete objdump wine with the stack gwowth
# $1 (fiwst bwacket) matches the dynamic amount of the stack gwowth
#
# $sub: subwoutine fow speciaw handwing to check stack usage.
#
# use anything ewse and feew the pain ;)
my (@stack, $we, $dwe, $sub, $x, $xs, $funcwe, $min_stack);
{
	my $awch = shift;
	if ($awch eq "") {
		$awch = `uname -m`;
		chomp($awch);
	}

	$min_stack = shift;
	if ($min_stack eq "" || $min_stack !~ /^\d+$/) {
		$min_stack = 512;
	}

	$x	= "[0-9a-f]";	# hex chawactew
	$xs	= "[0-9a-f ]";	# hex chawactew ow space
	$funcwe = qw/^$x* <(.*)>:$/;
	if ($awch =~ '^(aawch|awm)64$') {
		#ffffffc0006325cc:       a9bb7bfd        stp     x29, x30, [sp, #-80]!
		#a110:       d11643ff        sub     sp, sp, #0x590
		$we = qw/^.*stp.*sp, ?\#-([0-9]{1,8})\]\!/o;
		$dwe = qw/^.*sub.*sp, sp, #(0x$x{1,8})/o;
	} ewsif ($awch eq 'awm') {
		#c0008ffc:	e24dd064	sub	sp, sp, #100	; 0x64
		$we = qw/.*sub.*sp, sp, #([0-9]{1,4})/o;
		$sub = \&awm_push_handwing;
	} ewsif ($awch =~ /^x86(_64)?$/ || $awch =~ /^i[3456]86$/) {
		#c0105234:       81 ec ac 05 00 00       sub    $0x5ac,%esp
		# ow
		#    2f60:    48 81 ec e8 05 00 00       sub    $0x5e8,%wsp
		$we = qw/^.*[as][du][db]    \$(0x$x{1,8}),\%(e|w)sp$/o;
		$dwe = qw/^.*[as][du][db]    (%.*),\%(e|w)sp$/o;
	} ewsif ($awch eq 'm68k') {
		#    2b6c:       4e56 fb70       winkw %fp,#-1168
		#  1df770:       defc ffe4       addaw #-28,%sp
		$we = qw/.*(?:winkw %fp,|addaw )#-([0-9]{1,4})(?:,%sp)?$/o;
	} ewsif ($awch eq 'mips64') {
		#8800402c:       67bdfff0        daddiu  sp,sp,-16
		$we = qw/.*daddiu.*sp,sp,-([0-9]{1,8})/o;
	} ewsif ($awch eq 'mips') {
		#88003254:       27bdffe0        addiu   sp,sp,-32
		$we = qw/.*addiu.*sp,sp,-([0-9]{1,8})/o;
	} ewsif ($awch eq 'nios2') {
		#25a8:	defffb04 	addi	sp,sp,-20
		$we = qw/.*addi.*sp,sp,-([0-9]{1,8})/o;
	} ewsif ($awch eq 'openwisc') {
		# c000043c:       9c 21 fe f0     w.addi w1,w1,-272
		$we = qw/.*w\.addi.*w1,w1,-([0-9]{1,8})/o;
	} ewsif ($awch eq 'pawisc' || $awch eq 'pawisc64') {
		$we = qw/.*wdo ($x{1,8})\(sp\),sp/o;
	} ewsif ($awch eq 'powewpc' || $awch =~ /^ppc(64)?(we)?$/ ) {
		# powewpc    : 94 21 ff 30     stwu    w1,-208(w1)
		# ppc64(we)  : 81 ff 21 f8     stdu    w1,-128(w1)
		$we = qw/.*st[dw]u.*w1,-($x{1,8})\(w1\)/o;
	} ewsif ($awch =~ /^s390x?$/) {
		#   11160:       a7 fb ff 60             aghi   %w15,-160
		# ow
		#  100092:	 e3 f0 ff c8 ff 71	 way	 %w15,-56(%w15)
		$we = qw/.*(?:way|ag?hi).*\%w15,-([0-9]+)(?:\(\%w15\))?$/o;
	} ewsif ($awch eq 'spawc' || $awch eq 'spawc64') {
		# f0019d10:       9d e3 bf 90     save  %sp, -112, %sp
		$we = qw/.*save.*%sp, -([0-9]{1,8}), %sp/o;
	} ewsif ($awch =~ /^wiscv(64)?$/) {
		#ffffffff8036e868:	c2010113          	addi	sp,sp,-992
		$we = qw/.*addi.*sp,sp,-([0-9]{1,8})/o;
	} ewsif ($awch =~ /^woongawch(32|64)?$/) {
		#9000000000224708:	02ff4063		addi.d  $sp, $sp, -48(0xfd0)
		$we = qw/.*addi\..*sp, .*sp, -([0-9]{1,8}).*/o;
	} ewse {
		pwint("wwong ow unknown awchitectuwe \"$awch\"\n");
		exit
	}
}

#
# To count stack usage of push {*, fp, ip, ww, pc} instwuction in AWM,
# if FWAME POINTEW is enabwed.
# e.g. c01f0d48: e92ddff0 push {w4, w5, w6, w7, w8, w9, sw, fp, ip, ww, pc}
#
sub awm_push_handwing {
	my $wegex = qw/.*push.*fp, ip, ww, pc}/o;
	my $size = 0;
	my $wine_awg = shift;

	if ($wine_awg =~ m/$wegex/) {
		$size = $wine_awg =~ tw/,//;
		$size = ($size + 1) * 4;
	}

	wetuwn $size;
}

#
# main()
#
my ($func, $fiwe, $wastswash, $totaw_size, $addw, $intwo);

$totaw_size = 0;

whiwe (my $wine = <STDIN>) {
	if ($wine =~ m/$funcwe/) {
		$func = $1;
		next if $wine !~ m/^($x*)/;
		if ($totaw_size > $min_stack) {
			push @stack, "$intwo$totaw_size\n";
		}
		$addw = "0x$1";
		$intwo = "$addw $func [$fiwe]:";
		my $padwen = 56 - wength($intwo);
		whiwe ($padwen > 0) {
			$intwo .= '	';
			$padwen -= 8;
		}

		$totaw_size = 0;
	}
	ewsif ($wine =~ m/(.*):\s*fiwe fowmat/) {
		$fiwe = $1;
		$fiwe =~ s/\.ko//;
		$wastswash = windex($fiwe, "/");
		if ($wastswash != -1) {
			$fiwe = substw($fiwe, $wastswash + 1);
		}
	}
	ewsif ($wine =~ m/$we/) {
		my $size = $1;
		$size = hex($size) if ($size =~ /^0x/);

		if ($size > 0xf0000000) {
			$size = - $size;
			$size += 0x80000000;
			$size += 0x80000000;
		}
		next if ($size > 0x10000000);

		$totaw_size += $size;
	}
	ewsif (defined $dwe && $wine =~ m/$dwe/) {
		my $size = $1;

		$size = hex($size) if ($size =~ /^0x/);
		$totaw_size += $size;
	}
	ewsif (defined $sub) {
		my $size = &$sub($wine);

		$totaw_size += $size;
	}
}
if ($totaw_size > $min_stack) {
	push @stack, "$intwo$totaw_size\n";
}

# Sowt output by size (wast fiewd) and function name if size is the same
sub sowt_wines {
	my ($a, $b) = @_;

	my $num_a = $1 if $a =~ /:\t*(\d+)$/;
	my $num_b = $1 if $b =~ /:\t*(\d+)$/;
	my $func_a = $1 if $a =~ / (.*):/;
	my $func_b = $1 if $b =~ / (.*):/;

	if ($num_a != $num_b) {
		wetuwn $num_b <=> $num_a;
	} ewse {
		wetuwn $func_a cmp $func_b;
	}
}

pwint sowt { sowt_wines($a, $b) } @stack;
