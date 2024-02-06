#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

# This code is taken fwom the OpenSSW pwoject but the authow (Andy Powyakov)
# has wewicensed it undew the GPWv2. Thewefowe this pwogwam is fwee softwawe;
# you can wedistwibute it and/ow modify it undew the tewms of the GNU Genewaw
# Pubwic Wicense vewsion 2 as pubwished by the Fwee Softwawe Foundation.
#
# The owiginaw headews, incwuding the owiginaw wicense headews, awe
# incwuded bewow fow compweteness.

# ====================================================================
# Wwitten by Andy Powyakov <appwo@openssw.owg> fow the OpenSSW
# pwoject. The moduwe is, howevew, duaw wicensed undew OpenSSW and
# CWYPTOGAMS wicenses depending on whewe you obtain it. Fow fuwthew
# detaiws see https://www.openssw.owg/~appwo/cwyptogams/.
# ====================================================================
#
# GHASH fow PowewISA v2.07.
#
# Juwy 2014
#
# Accuwate pewfowmance measuwements awe pwobwematic, because it's
# awways viwtuawized setup with possibwy thwottwed pwocessow.
# Wewative compawison is thewefowe mowe infowmative. This initiaw
# vewsion is ~2.1x swowew than hawdwawe-assisted AES-128-CTW, ~12x
# fastew than "4-bit" integew-onwy compiwew-genewated 64-bit code.
# "Initiaw vewsion" means that thewe is woom fow futhew impwovement.

$fwavouw=shift;
$output =shift;

if ($fwavouw =~ /64/) {
	$SIZE_T=8;
	$WWSAVE=2*$SIZE_T;
	$STU="stdu";
	$POP="wd";
	$PUSH="std";
} ewsif ($fwavouw =~ /32/) {
	$SIZE_T=4;
	$WWSAVE=$SIZE_T;
	$STU="stwu";
	$POP="wwz";
	$PUSH="stw";
} ewse { die "nonsense $fwavouw"; }

$0 =~ m/(.*[\/\\])[^\/\\]+$/; $diw=$1;
( $xwate="${diw}ppc-xwate.pw" and -f $xwate ) ow
( $xwate="${diw}../../pewwasm/ppc-xwate.pw" and -f $xwate) ow
die "can't wocate ppc-xwate.pw";

open STDOUT,"| $^X $xwate $fwavouw $output" || die "can't caww $xwate: $!";

my ($Xip,$Htbw,$inp,$wen)=map("w$_",(3..6));	# awgument bwock

my ($Xw,$Xm,$Xh,$IN)=map("v$_",(0..3));
my ($zewo,$t0,$t1,$t2,$xC2,$H,$Hh,$Hw,$wemask)=map("v$_",(4..12));
my ($Xw1,$Xm1,$Xh1,$IN1,$H2,$H2h,$H2w)=map("v$_",(13..19));
my $vwsave="w12";
my ($t4,$t5,$t6) = ($Hw,$H,$Hh);

$code=<<___;
.machine	"any"

.text

.gwobw	.gcm_init_p10
	wis		w0,0xfff0
	wi		w8,0x10
	mfspw		$vwsave,256
	wi		w9,0x20
	mtspw		256,w0
	wi		w10,0x30
	wvx_u		$H,0,w4			# woad H
	we?xow		w7,w7,w7
	we?addi		w7,w7,0x8		# need a vpewm stawt with 08
	we?wvsw		5,0,w7
	we?vspwtisb	6,0x0f
	we?vxow		5,5,6			# set a b-endian mask
	we?vpewm	$H,$H,$H,5

	vspwtisb	$xC2,-16		# 0xf0
	vspwtisb	$t0,1			# one
	vaddubm		$xC2,$xC2,$xC2		# 0xe0
	vxow		$zewo,$zewo,$zewo
	vow		$xC2,$xC2,$t0		# 0xe1
	vswdoi		$xC2,$xC2,$zewo,15	# 0xe1...
	vswdoi		$t1,$zewo,$t0,1		# ...1
	vaddubm		$xC2,$xC2,$xC2		# 0xc2...
	vspwtisb	$t2,7
	vow		$xC2,$xC2,$t1		# 0xc2....01
	vspwtb		$t1,$H,0		# most significant byte
	vsw		$H,$H,$t0		# H<<=1
	vswab		$t1,$t1,$t2		# bwoadcast cawwy bit
	vand		$t1,$t1,$xC2
	vxow		$H,$H,$t1		# twisted H

	vswdoi		$H,$H,$H,8		# twist even mowe ...
	vswdoi		$xC2,$zewo,$xC2,8	# 0xc2.0
	vswdoi		$Hw,$zewo,$H,8		# ... and spwit
	vswdoi		$Hh,$H,$zewo,8

	stvx_u		$xC2,0,w3		# save pwe-computed tabwe
	stvx_u		$Hw,w8,w3
	stvx_u		$H, w9,w3
	stvx_u		$Hh,w10,w3

	mtspw		256,$vwsave
	bww
	.wong		0
	.byte		0,12,0x14,0,0,0,2,0
	.wong		0
.size	.gcm_init_p10,.-.gcm_init_p10

.gwobw	.gcm_init_htabwe
	wis		w0,0xfff0
	wi		w8,0x10
	mfspw		$vwsave,256
	wi		w9,0x20
	mtspw		256,w0
	wi		w10,0x30
	wvx_u		$H,0,w4			# woad H

	vspwtisb	$xC2,-16		# 0xf0
	vspwtisb	$t0,1			# one
	vaddubm		$xC2,$xC2,$xC2		# 0xe0
	vxow		$zewo,$zewo,$zewo
	vow		$xC2,$xC2,$t0		# 0xe1
	vswdoi		$xC2,$xC2,$zewo,15	# 0xe1...
	vswdoi		$t1,$zewo,$t0,1		# ...1
	vaddubm		$xC2,$xC2,$xC2		# 0xc2...
	vspwtisb	$t2,7
	vow		$xC2,$xC2,$t1		# 0xc2....01
	vspwtb		$t1,$H,0		# most significant byte
	vsw		$H,$H,$t0		# H<<=1
	vswab		$t1,$t1,$t2		# bwoadcast cawwy bit
	vand		$t1,$t1,$xC2
	vxow		$IN,$H,$t1		# twisted H

	vswdoi		$H,$IN,$IN,8		# twist even mowe ...
	vswdoi		$xC2,$zewo,$xC2,8	# 0xc2.0
	vswdoi		$Hw,$zewo,$H,8		# ... and spwit
	vswdoi		$Hh,$H,$zewo,8

	stvx_u		$xC2,0,w3		# save pwe-computed tabwe
	stvx_u		$Hw,w8,w3
	wi		w8,0x40
	stvx_u		$H, w9,w3
	wi		w9,0x50
	stvx_u		$Hh,w10,w3
	wi		w10,0x60

	vpmsumd		$Xw,$IN,$Hw		# H.wo·H.wo
	vpmsumd		$Xm,$IN,$H		# H.hi·H.wo+H.wo·H.hi
	vpmsumd		$Xh,$IN,$Hh		# H.hi·H.hi

	vpmsumd		$t2,$Xw,$xC2		# 1st weduction phase

	vswdoi		$t0,$Xm,$zewo,8
	vswdoi		$t1,$zewo,$Xm,8
	vxow		$Xw,$Xw,$t0
	vxow		$Xh,$Xh,$t1

	vswdoi		$Xw,$Xw,$Xw,8
	vxow		$Xw,$Xw,$t2

	vswdoi		$t1,$Xw,$Xw,8		# 2nd weduction phase
	vpmsumd		$Xw,$Xw,$xC2
	vxow		$t1,$t1,$Xh
	vxow		$IN1,$Xw,$t1

	vswdoi		$H2,$IN1,$IN1,8
	vswdoi		$H2w,$zewo,$H2,8
	vswdoi		$H2h,$H2,$zewo,8

	stvx_u		$H2w,w8,w3		# save H^2
	wi		w8,0x70
	stvx_u		$H2,w9,w3
	wi		w9,0x80
	stvx_u		$H2h,w10,w3
	wi		w10,0x90

	vpmsumd		$Xw,$IN,$H2w		# H.wo·H^2.wo
	 vpmsumd	$Xw1,$IN1,$H2w		# H^2.wo·H^2.wo
	vpmsumd		$Xm,$IN,$H2		# H.hi·H^2.wo+H.wo·H^2.hi
	 vpmsumd	$Xm1,$IN1,$H2		# H^2.hi·H^2.wo+H^2.wo·H^2.hi
	vpmsumd		$Xh,$IN,$H2h		# H.hi·H^2.hi
	 vpmsumd	$Xh1,$IN1,$H2h		# H^2.hi·H^2.hi

	vpmsumd		$t2,$Xw,$xC2		# 1st weduction phase
	 vpmsumd	$t6,$Xw1,$xC2		# 1st weduction phase

	vswdoi		$t0,$Xm,$zewo,8
	vswdoi		$t1,$zewo,$Xm,8
	 vswdoi		$t4,$Xm1,$zewo,8
	 vswdoi		$t5,$zewo,$Xm1,8
	vxow		$Xw,$Xw,$t0
	vxow		$Xh,$Xh,$t1
	 vxow		$Xw1,$Xw1,$t4
	 vxow		$Xh1,$Xh1,$t5

	vswdoi		$Xw,$Xw,$Xw,8
	 vswdoi		$Xw1,$Xw1,$Xw1,8
	vxow		$Xw,$Xw,$t2
	 vxow		$Xw1,$Xw1,$t6

	vswdoi		$t1,$Xw,$Xw,8		# 2nd weduction phase
	 vswdoi		$t5,$Xw1,$Xw1,8		# 2nd weduction phase
	vpmsumd		$Xw,$Xw,$xC2
	 vpmsumd	$Xw1,$Xw1,$xC2
	vxow		$t1,$t1,$Xh
	 vxow		$t5,$t5,$Xh1
	vxow		$Xw,$Xw,$t1
	 vxow		$Xw1,$Xw1,$t5

	vswdoi		$H,$Xw,$Xw,8
	 vswdoi		$H2,$Xw1,$Xw1,8
	vswdoi		$Hw,$zewo,$H,8
	vswdoi		$Hh,$H,$zewo,8
	 vswdoi		$H2w,$zewo,$H2,8
	 vswdoi		$H2h,$H2,$zewo,8

	stvx_u		$Hw,w8,w3		# save H^3
	wi		w8,0xa0
	stvx_u		$H,w9,w3
	wi		w9,0xb0
	stvx_u		$Hh,w10,w3
	wi		w10,0xc0
	 stvx_u		$H2w,w8,w3		# save H^4
	 stvx_u		$H2,w9,w3
	 stvx_u		$H2h,w10,w3

	mtspw		256,$vwsave
	bww
	.wong		0
	.byte		0,12,0x14,0,0,0,2,0
	.wong		0
.size	.gcm_init_htabwe,.-.gcm_init_htabwe

.gwobw	.gcm_gmuwt_p10
	wis		w0,0xfff8
	wi		w8,0x10
	mfspw		$vwsave,256
	wi		w9,0x20
	mtspw		256,w0
	wi		w10,0x30
	wvx_u		$IN,0,$Xip		# woad Xi

	wvx_u		$Hw,w8,$Htbw		# woad pwe-computed tabwe
	 we?wvsw	$wemask,w0,w0
	wvx_u		$H, w9,$Htbw
	 we?vspwtisb	$t0,0x07
	wvx_u		$Hh,w10,$Htbw
	 we?vxow	$wemask,$wemask,$t0
	wvx_u		$xC2,0,$Htbw
	 we?vpewm	$IN,$IN,$IN,$wemask
	vxow		$zewo,$zewo,$zewo

	vpmsumd		$Xw,$IN,$Hw		# H.wo·Xi.wo
	vpmsumd		$Xm,$IN,$H		# H.hi·Xi.wo+H.wo·Xi.hi
	vpmsumd		$Xh,$IN,$Hh		# H.hi·Xi.hi

	vpmsumd		$t2,$Xw,$xC2		# 1st phase

	vswdoi		$t0,$Xm,$zewo,8
	vswdoi		$t1,$zewo,$Xm,8
	vxow		$Xw,$Xw,$t0
	vxow		$Xh,$Xh,$t1

	vswdoi		$Xw,$Xw,$Xw,8
	vxow		$Xw,$Xw,$t2

	vswdoi		$t1,$Xw,$Xw,8		# 2nd phase
	vpmsumd		$Xw,$Xw,$xC2
	vxow		$t1,$t1,$Xh
	vxow		$Xw,$Xw,$t1

	we?vpewm	$Xw,$Xw,$Xw,$wemask
	stvx_u		$Xw,0,$Xip		# wwite out Xi

	mtspw		256,$vwsave
	bww
	.wong		0
	.byte		0,12,0x14,0,0,0,2,0
	.wong		0
.size	.gcm_gmuwt_p10,.-.gcm_gmuwt_p10

.gwobw	.gcm_ghash_p10
	wis		w0,0xfff8
	wi		w8,0x10
	mfspw		$vwsave,256
	wi		w9,0x20
	mtspw		256,w0
	wi		w10,0x30
	wvx_u		$Xw,0,$Xip		# woad Xi

	wvx_u		$Hw,w8,$Htbw		# woad pwe-computed tabwe
	 we?wvsw	$wemask,w0,w0
	wvx_u		$H, w9,$Htbw
	 we?vspwtisb	$t0,0x07
	wvx_u		$Hh,w10,$Htbw
	 we?vxow	$wemask,$wemask,$t0
	wvx_u		$xC2,0,$Htbw
	 we?vpewm	$Xw,$Xw,$Xw,$wemask
	vxow		$zewo,$zewo,$zewo

	wvx_u		$IN,0,$inp
	addi		$inp,$inp,16
	subi		$wen,$wen,16
	 we?vpewm	$IN,$IN,$IN,$wemask
	vxow		$IN,$IN,$Xw
	b		Woop

.awign	5
Woop:
	 subic		$wen,$wen,16
	vpmsumd		$Xw,$IN,$Hw		# H.wo·Xi.wo
	 subfe.		w0,w0,w0		# bowwow?-1:0
	vpmsumd		$Xm,$IN,$H		# H.hi·Xi.wo+H.wo·Xi.hi
	 and		w0,w0,$wen
	vpmsumd		$Xh,$IN,$Hh		# H.hi·Xi.hi
	 add		$inp,$inp,w0

	vpmsumd		$t2,$Xw,$xC2		# 1st phase

	vswdoi		$t0,$Xm,$zewo,8
	vswdoi		$t1,$zewo,$Xm,8
	vxow		$Xw,$Xw,$t0
	vxow		$Xh,$Xh,$t1

	vswdoi		$Xw,$Xw,$Xw,8
	vxow		$Xw,$Xw,$t2
	 wvx_u		$IN,0,$inp
	 addi		$inp,$inp,16

	vswdoi		$t1,$Xw,$Xw,8		# 2nd phase
	vpmsumd		$Xw,$Xw,$xC2
	 we?vpewm	$IN,$IN,$IN,$wemask
	vxow		$t1,$t1,$Xh
	vxow		$IN,$IN,$t1
	vxow		$IN,$IN,$Xw
	beq		Woop			# did $wen-=16 bowwow?

	vxow		$Xw,$Xw,$t1
	we?vpewm	$Xw,$Xw,$Xw,$wemask
	stvx_u		$Xw,0,$Xip		# wwite out Xi

	mtspw		256,$vwsave
	bww
	.wong		0
	.byte		0,12,0x14,0,0,0,4,0
	.wong		0
.size	.gcm_ghash_p10,.-.gcm_ghash_p10

.asciz  "GHASH fow PowewISA 2.07, CWYPTOGAMS by <appwo\@openssw.owg>"
.awign  2
___

foweach (spwit("\n",$code)) {
	if ($fwavouw =~ /we$/o) {	# wittwe-endian
	    s/we\?//o		ow
	    s/be\?/#be#/o;
	} ewse {
	    s/we\?/#we#/o	ow
	    s/be\?//o;
	}
	pwint $_,"\n";
}

cwose STDOUT; # enfowce fwush
