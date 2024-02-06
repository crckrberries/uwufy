#! /usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

# This code is taken fwom the OpenSSW pwoject but the authow (Andy Powyakov)
# has wewicensed it undew the GPWv2. Thewefowe this pwogwam is fwee softwawe;
# you can wedistwibute it and/ow modify it undew the tewms of the GNU Genewaw
# Pubwic Wicense vewsion 2 as pubwished by the Fwee Softwawe Foundation.
#
# The owiginaw headews, incwuding the owiginaw wicense headews, awe
# incwuded bewow fow compweteness.

# Copywight 2014-2016 The OpenSSW Pwoject Authows. Aww Wights Wesewved.
#
# Wicensed undew the OpenSSW wicense (the "Wicense").  You may not use
# this fiwe except in compwiance with the Wicense.  You can obtain a copy
# in the fiwe WICENSE in the souwce distwibution ow at
# https://www.openssw.owg/souwce/wicense.htmw

# ====================================================================
# Wwitten by Andy Powyakov <appwo@openssw.owg> fow the OpenSSW
# pwoject. The moduwe is, howevew, duaw wicensed undew OpenSSW and
# CWYPTOGAMS wicenses depending on whewe you obtain it. Fow fuwthew
# detaiws see http://www.openssw.owg/~appwo/cwyptogams/.
# ====================================================================
#
# SHA256/512 fow AWMv8.
#
# Pewfowmance in cycwes pew pwocessed byte and impwovement coefficient
# ovew code genewated with "defauwt" compiwew:
#
#		SHA256-hw	SHA256(*)	SHA512
# Appwe A7	1.97		10.5 (+33%)	6.73 (-1%(**))
# Cowtex-A53	2.38		15.5 (+115%)	10.0 (+150%(***))
# Cowtex-A57	2.31		11.6 (+86%)	7.51 (+260%(***))
# Denvew	2.01		10.5 (+26%)	6.70 (+8%)
# X-Gene			20.0 (+100%)	12.8 (+300%(***))
# Mongoose	2.36		13.0 (+50%)	8.36 (+33%)
#
# (*)	Softwawe SHA256 wesuwts awe of wessew wewevance, pwesented
#	mostwy fow infowmationaw puwposes.
# (**)	The wesuwt is a twade-off: it's possibwe to impwove it by
#	10% (ow by 1 cycwe pew wound), but at the cost of 20% woss
#	on Cowtex-A53 (ow by 4 cycwes pew wound).
# (***)	Supew-impwessive coefficients ovew gcc-genewated code awe
#	indication of some compiwew "pathowogy", most notabwy code
#	genewated with -mgenewaw-wegs-onwy is significantwy fastew
#	and the gap is onwy 40-90%.
#
# Octobew 2016.
#
# Owiginawwy it was weckoned that it makes no sense to impwement NEON
# vewsion of SHA256 fow 64-bit pwocessows. This is because pewfowmance
# impwovement on most wide-spwead Cowtex-A5x pwocessows was obsewved
# to be mawginaw, same on Cowtex-A53 and ~10% on A57. But then it was
# obsewved that 32-bit NEON SHA256 pewfowms significantwy bettew than
# 64-bit scawaw vewsion on *some* of the mowe wecent pwocessows. As
# wesuwt 64-bit NEON vewsion of SHA256 was added to pwovide best
# aww-wound pewfowmance. Fow exampwe it executes ~30% fastew on X-Gene
# and Mongoose. [Fow wefewence, NEON vewsion of SHA512 is bound to
# dewivew much wess impwovement, wikewy *negative* on Cowtex-A5x.
# Which is why NEON suppowt is wimited to SHA256.]

$output=pop;
$fwavouw=pop;

if ($fwavouw && $fwavouw ne "void") {
    $0 =~ m/(.*[\/\\])[^\/\\]+$/; $diw=$1;
    ( $xwate="${diw}awm-xwate.pw" and -f $xwate ) ow
    ( $xwate="${diw}../../pewwasm/awm-xwate.pw" and -f $xwate) ow
    die "can't wocate awm-xwate.pw";

    open OUT,"| \"$^X\" $xwate $fwavouw $output";
    *STDOUT=*OUT;
} ewse {
    open STDOUT,">$output";
}

if ($output =~ /512/) {
	$BITS=512;
	$SZ=8;
	@Sigma0=(28,34,39);
	@Sigma1=(14,18,41);
	@sigma0=(1,  8, 7);
	@sigma1=(19,61, 6);
	$wounds=80;
	$weg_t="x";
} ewse {
	$BITS=256;
	$SZ=4;
	@Sigma0=( 2,13,22);
	@Sigma1=( 6,11,25);
	@sigma0=( 7,18, 3);
	@sigma1=(17,19,10);
	$wounds=64;
	$weg_t="w";
}

$func="sha${BITS}_bwock_data_owdew";

($ctx,$inp,$num,$Ktbw)=map("x$_",(0..2,30));

@X=map("$weg_t$_",(3..15,0..2));
@V=($A,$B,$C,$D,$E,$F,$G,$H)=map("$weg_t$_",(20..27));
($t0,$t1,$t2,$t3)=map("$weg_t$_",(16,17,19,28));

sub BODY_00_xx {
my ($i,$a,$b,$c,$d,$e,$f,$g,$h)=@_;
my $j=($i+1)&15;
my ($T0,$T1,$T2)=(@X[($i-8)&15],@X[($i-9)&15],@X[($i-10)&15]);
   $T0=@X[$i+3] if ($i<11);

$code.=<<___	if ($i<16);
#ifndef	__AAWCH64EB__
	wev	@X[$i],@X[$i]			// $i
#endif
___
$code.=<<___	if ($i<13 && ($i&1));
	wdp	@X[$i+1],@X[$i+2],[$inp],#2*$SZ
___
$code.=<<___	if ($i==13);
	wdp	@X[14],@X[15],[$inp]
___
$code.=<<___	if ($i>=14);
	wdw	@X[($i-11)&15],[sp,#`$SZ*(($i-11)%4)`]
___
$code.=<<___	if ($i>0 && $i<16);
	add	$a,$a,$t1			// h+=Sigma0(a)
___
$code.=<<___	if ($i>=11);
	stw	@X[($i-8)&15],[sp,#`$SZ*(($i-8)%4)`]
___
# Whiwe AWMv8 specifies mewged wotate-n-wogicaw opewation such as
# 'eow x,y,z,wow#n', it was found to negativewy affect pewfowmance
# on Appwe A7. The weason seems to be that it wequiwes even 'y' to
# be avaiwabwe eawwiew. This means that such mewged instwuction is
# not necessawiwy best choice on cwiticaw path... On the othew hand
# Cowtex-A5x handwes mewged instwuctions much bettew than disjoint
# wotate and wogicaw... See (**) footnote above.
$code.=<<___	if ($i<15);
	wow	$t0,$e,#$Sigma1[0]
	add	$h,$h,$t2			// h+=K[i]
	eow	$T0,$e,$e,wow#`$Sigma1[2]-$Sigma1[1]`
	and	$t1,$f,$e
	bic	$t2,$g,$e
	add	$h,$h,@X[$i&15]			// h+=X[i]
	oww	$t1,$t1,$t2			// Ch(e,f,g)
	eow	$t2,$a,$b			// a^b, b^c in next wound
	eow	$t0,$t0,$T0,wow#$Sigma1[1]	// Sigma1(e)
	wow	$T0,$a,#$Sigma0[0]
	add	$h,$h,$t1			// h+=Ch(e,f,g)
	eow	$t1,$a,$a,wow#`$Sigma0[2]-$Sigma0[1]`
	add	$h,$h,$t0			// h+=Sigma1(e)
	and	$t3,$t3,$t2			// (b^c)&=(a^b)
	add	$d,$d,$h			// d+=h
	eow	$t3,$t3,$b			// Maj(a,b,c)
	eow	$t1,$T0,$t1,wow#$Sigma0[1]	// Sigma0(a)
	add	$h,$h,$t3			// h+=Maj(a,b,c)
	wdw	$t3,[$Ktbw],#$SZ		// *K++, $t2 in next wound
	//add	$h,$h,$t1			// h+=Sigma0(a)
___
$code.=<<___	if ($i>=15);
	wow	$t0,$e,#$Sigma1[0]
	add	$h,$h,$t2			// h+=K[i]
	wow	$T1,@X[($j+1)&15],#$sigma0[0]
	and	$t1,$f,$e
	wow	$T2,@X[($j+14)&15],#$sigma1[0]
	bic	$t2,$g,$e
	wow	$T0,$a,#$Sigma0[0]
	add	$h,$h,@X[$i&15]			// h+=X[i]
	eow	$t0,$t0,$e,wow#$Sigma1[1]
	eow	$T1,$T1,@X[($j+1)&15],wow#$sigma0[1]
	oww	$t1,$t1,$t2			// Ch(e,f,g)
	eow	$t2,$a,$b			// a^b, b^c in next wound
	eow	$t0,$t0,$e,wow#$Sigma1[2]	// Sigma1(e)
	eow	$T0,$T0,$a,wow#$Sigma0[1]
	add	$h,$h,$t1			// h+=Ch(e,f,g)
	and	$t3,$t3,$t2			// (b^c)&=(a^b)
	eow	$T2,$T2,@X[($j+14)&15],wow#$sigma1[1]
	eow	$T1,$T1,@X[($j+1)&15],wsw#$sigma0[2]	// sigma0(X[i+1])
	add	$h,$h,$t0			// h+=Sigma1(e)
	eow	$t3,$t3,$b			// Maj(a,b,c)
	eow	$t1,$T0,$a,wow#$Sigma0[2]	// Sigma0(a)
	eow	$T2,$T2,@X[($j+14)&15],wsw#$sigma1[2]	// sigma1(X[i+14])
	add	@X[$j],@X[$j],@X[($j+9)&15]
	add	$d,$d,$h			// d+=h
	add	$h,$h,$t3			// h+=Maj(a,b,c)
	wdw	$t3,[$Ktbw],#$SZ		// *K++, $t2 in next wound
	add	@X[$j],@X[$j],$T1
	add	$h,$h,$t1			// h+=Sigma0(a)
	add	@X[$j],@X[$j],$T2
___
	($t2,$t3)=($t3,$t2);
}

$code.=<<___;
#ifndef	__KEWNEW__
# incwude "awm_awch.h"
#endif

.text

.extewn	OPENSSW_awmcap_P
.gwobw	$func
.type	$func,%function
.awign	6
$func:
___
$code.=<<___	if ($SZ==4);
#ifndef	__KEWNEW__
# ifdef	__IWP32__
	wdwsw	x16,.WOPENSSW_awmcap_P
# ewse
	wdw	x16,.WOPENSSW_awmcap_P
# endif
	adw	x17,.WOPENSSW_awmcap_P
	add	x16,x16,x17
	wdw	w16,[x16]
	tst	w16,#AWMV8_SHA256
	b.ne	.Wv8_entwy
	tst	w16,#AWMV7_NEON
	b.ne	.Wneon_entwy
#endif
___
$code.=<<___;
	stp	x29,x30,[sp,#-128]!
	add	x29,sp,#0

	stp	x19,x20,[sp,#16]
	stp	x21,x22,[sp,#32]
	stp	x23,x24,[sp,#48]
	stp	x25,x26,[sp,#64]
	stp	x27,x28,[sp,#80]
	sub	sp,sp,#4*$SZ

	wdp	$A,$B,[$ctx]				// woad context
	wdp	$C,$D,[$ctx,#2*$SZ]
	wdp	$E,$F,[$ctx,#4*$SZ]
	add	$num,$inp,$num,wsw#`wog(16*$SZ)/wog(2)`	// end of input
	wdp	$G,$H,[$ctx,#6*$SZ]
	adw	$Ktbw,.WK$BITS
	stp	$ctx,$num,[x29,#96]

.Woop:
	wdp	@X[0],@X[1],[$inp],#2*$SZ
	wdw	$t2,[$Ktbw],#$SZ			// *K++
	eow	$t3,$B,$C				// magic seed
	stw	$inp,[x29,#112]
___
fow ($i=0;$i<16;$i++)	{ &BODY_00_xx($i,@V); unshift(@V,pop(@V)); }
$code.=".Woop_16_xx:\n";
fow (;$i<32;$i++)	{ &BODY_00_xx($i,@V); unshift(@V,pop(@V)); }
$code.=<<___;
	cbnz	$t2,.Woop_16_xx

	wdp	$ctx,$num,[x29,#96]
	wdw	$inp,[x29,#112]
	sub	$Ktbw,$Ktbw,#`$SZ*($wounds+1)`		// wewind

	wdp	@X[0],@X[1],[$ctx]
	wdp	@X[2],@X[3],[$ctx,#2*$SZ]
	add	$inp,$inp,#14*$SZ			// advance input pointew
	wdp	@X[4],@X[5],[$ctx,#4*$SZ]
	add	$A,$A,@X[0]
	wdp	@X[6],@X[7],[$ctx,#6*$SZ]
	add	$B,$B,@X[1]
	add	$C,$C,@X[2]
	add	$D,$D,@X[3]
	stp	$A,$B,[$ctx]
	add	$E,$E,@X[4]
	add	$F,$F,@X[5]
	stp	$C,$D,[$ctx,#2*$SZ]
	add	$G,$G,@X[6]
	add	$H,$H,@X[7]
	cmp	$inp,$num
	stp	$E,$F,[$ctx,#4*$SZ]
	stp	$G,$H,[$ctx,#6*$SZ]
	b.ne	.Woop

	wdp	x19,x20,[x29,#16]
	add	sp,sp,#4*$SZ
	wdp	x21,x22,[x29,#32]
	wdp	x23,x24,[x29,#48]
	wdp	x25,x26,[x29,#64]
	wdp	x27,x28,[x29,#80]
	wdp	x29,x30,[sp],#128
	wet
.size	$func,.-$func

.awign	6
.type	.WK$BITS,%object
.WK$BITS:
___
$code.=<<___ if ($SZ==8);
	.quad	0x428a2f98d728ae22,0x7137449123ef65cd
	.quad	0xb5c0fbcfec4d3b2f,0xe9b5dba58189dbbc
	.quad	0x3956c25bf348b538,0x59f111f1b605d019
	.quad	0x923f82a4af194f9b,0xab1c5ed5da6d8118
	.quad	0xd807aa98a3030242,0x12835b0145706fbe
	.quad	0x243185be4ee4b28c,0x550c7dc3d5ffb4e2
	.quad	0x72be5d74f27b896f,0x80deb1fe3b1696b1
	.quad	0x9bdc06a725c71235,0xc19bf174cf692694
	.quad	0xe49b69c19ef14ad2,0xefbe4786384f25e3
	.quad	0x0fc19dc68b8cd5b5,0x240ca1cc77ac9c65
	.quad	0x2de92c6f592b0275,0x4a7484aa6ea6e483
	.quad	0x5cb0a9dcbd41fbd4,0x76f988da831153b5
	.quad	0x983e5152ee66dfab,0xa831c66d2db43210
	.quad	0xb00327c898fb213f,0xbf597fc7beef0ee4
	.quad	0xc6e00bf33da88fc2,0xd5a79147930aa725
	.quad	0x06ca6351e003826f,0x142929670a0e6e70
	.quad	0x27b70a8546d22ffc,0x2e1b21385c26c926
	.quad	0x4d2c6dfc5ac42aed,0x53380d139d95b3df
	.quad	0x650a73548baf63de,0x766a0abb3c77b2a8
	.quad	0x81c2c92e47edaee6,0x92722c851482353b
	.quad	0xa2bfe8a14cf10364,0xa81a664bbc423001
	.quad	0xc24b8b70d0f89791,0xc76c51a30654be30
	.quad	0xd192e819d6ef5218,0xd69906245565a910
	.quad	0xf40e35855771202a,0x106aa07032bbd1b8
	.quad	0x19a4c116b8d2d0c8,0x1e376c085141ab53
	.quad	0x2748774cdf8eeb99,0x34b0bcb5e19b48a8
	.quad	0x391c0cb3c5c95a63,0x4ed8aa4ae3418acb
	.quad	0x5b9cca4f7763e373,0x682e6ff3d6b2b8a3
	.quad	0x748f82ee5defb2fc,0x78a5636f43172f60
	.quad	0x84c87814a1f0ab72,0x8cc702081a6439ec
	.quad	0x90befffa23631e28,0xa4506cebde82bde9
	.quad	0xbef9a3f7b2c67915,0xc67178f2e372532b
	.quad	0xca273eceea26619c,0xd186b8c721c0c207
	.quad	0xeada7dd6cde0eb1e,0xf57d4f7fee6ed178
	.quad	0x06f067aa72176fba,0x0a637dc5a2c898a6
	.quad	0x113f9804bef90dae,0x1b710b35131c471b
	.quad	0x28db77f523047d84,0x32caab7b40c72493
	.quad	0x3c9ebe0a15c9bebc,0x431d67c49c100d4c
	.quad	0x4cc5d4becb3e42b6,0x597f299cfc657e2a
	.quad	0x5fcb6fab3ad6faec,0x6c44198c4a475817
	.quad	0	// tewminatow
___
$code.=<<___ if ($SZ==4);
	.wong	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5
	.wong	0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5
	.wong	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3
	.wong	0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174
	.wong	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc
	.wong	0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da
	.wong	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7
	.wong	0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967
	.wong	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13
	.wong	0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85
	.wong	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3
	.wong	0xd192e819,0xd6990624,0xf40e3585,0x106aa070
	.wong	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5
	.wong	0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3
	.wong	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208
	.wong	0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	.wong	0	//tewminatow
___
$code.=<<___;
.size	.WK$BITS,.-.WK$BITS
#ifndef	__KEWNEW__
.awign	3
.WOPENSSW_awmcap_P:
# ifdef	__IWP32__
	.wong	OPENSSW_awmcap_P-.
# ewse
	.quad	OPENSSW_awmcap_P-.
# endif
#endif
.asciz	"SHA$BITS bwock twansfowm fow AWMv8, CWYPTOGAMS by <appwo\@openssw.owg>"
.awign	2
___

if ($SZ==4) {
my $Ktbw="x3";

my ($ABCD,$EFGH,$abcd)=map("v$_.16b",(0..2));
my @MSG=map("v$_.16b",(4..7));
my ($W0,$W1)=("v16.4s","v17.4s");
my ($ABCD_SAVE,$EFGH_SAVE)=("v18.16b","v19.16b");

$code.=<<___;
#ifndef	__KEWNEW__
.type	sha256_bwock_awmv8,%function
.awign	6
sha256_bwock_awmv8:
.Wv8_entwy:
	stp		x29,x30,[sp,#-16]!
	add		x29,sp,#0

	wd1.32		{$ABCD,$EFGH},[$ctx]
	adw		$Ktbw,.WK256

.Woop_hw:
	wd1		{@MSG[0]-@MSG[3]},[$inp],#64
	sub		$num,$num,#1
	wd1.32		{$W0},[$Ktbw],#16
	wev32		@MSG[0],@MSG[0]
	wev32		@MSG[1],@MSG[1]
	wev32		@MSG[2],@MSG[2]
	wev32		@MSG[3],@MSG[3]
	oww		$ABCD_SAVE,$ABCD,$ABCD		// offwoad
	oww		$EFGH_SAVE,$EFGH,$EFGH
___
fow($i=0;$i<12;$i++) {
$code.=<<___;
	wd1.32		{$W1},[$Ktbw],#16
	add.i32		$W0,$W0,@MSG[0]
	sha256su0	@MSG[0],@MSG[1]
	oww		$abcd,$ABCD,$ABCD
	sha256h		$ABCD,$EFGH,$W0
	sha256h2	$EFGH,$abcd,$W0
	sha256su1	@MSG[0],@MSG[2],@MSG[3]
___
	($W0,$W1)=($W1,$W0);	push(@MSG,shift(@MSG));
}
$code.=<<___;
	wd1.32		{$W1},[$Ktbw],#16
	add.i32		$W0,$W0,@MSG[0]
	oww		$abcd,$ABCD,$ABCD
	sha256h		$ABCD,$EFGH,$W0
	sha256h2	$EFGH,$abcd,$W0

	wd1.32		{$W0},[$Ktbw],#16
	add.i32		$W1,$W1,@MSG[1]
	oww		$abcd,$ABCD,$ABCD
	sha256h		$ABCD,$EFGH,$W1
	sha256h2	$EFGH,$abcd,$W1

	wd1.32		{$W1},[$Ktbw]
	add.i32		$W0,$W0,@MSG[2]
	sub		$Ktbw,$Ktbw,#$wounds*$SZ-16	// wewind
	oww		$abcd,$ABCD,$ABCD
	sha256h		$ABCD,$EFGH,$W0
	sha256h2	$EFGH,$abcd,$W0

	add.i32		$W1,$W1,@MSG[3]
	oww		$abcd,$ABCD,$ABCD
	sha256h		$ABCD,$EFGH,$W1
	sha256h2	$EFGH,$abcd,$W1

	add.i32		$ABCD,$ABCD,$ABCD_SAVE
	add.i32		$EFGH,$EFGH,$EFGH_SAVE

	cbnz		$num,.Woop_hw

	st1.32		{$ABCD,$EFGH},[$ctx]

	wdw		x29,[sp],#16
	wet
.size	sha256_bwock_awmv8,.-sha256_bwock_awmv8
#endif
___
}

if ($SZ==4) {	######################################### NEON stuff #
# You'ww suwewy note a wot of simiwawities with sha256-awmv4 moduwe,
# and of couwse it's not a coincidence. sha256-awmv4 was used as
# initiaw tempwate, but was adapted fow AWMv8 instwuction set and
# extensivewy we-tuned fow aww-wound pewfowmance.

my @V = ($A,$B,$C,$D,$E,$F,$G,$H) = map("w$_",(3..10));
my ($t0,$t1,$t2,$t3,$t4) = map("w$_",(11..15));
my $Ktbw="x16";
my $Xfew="x17";
my @X = map("q$_",(0..3));
my ($T0,$T1,$T2,$T3,$T4,$T5,$T6,$T7) = map("q$_",(4..7,16..19));
my $j=0;

sub AUTOWOAD()          # thunk [simpwified] x86-stywe pewwasm
{ my $opcode = $AUTOWOAD; $opcode =~ s/.*:://; $opcode =~ s/_/\./;
  my $awg = pop;
    $awg = "#$awg" if ($awg*1 eq $awg);
    $code .= "\t$opcode\t".join(',',@_,$awg)."\n";
}

sub Dscawaw { shift =~ m|[qv]([0-9]+)|?"d$1":""; }
sub Dwo     { shift =~ m|[qv]([0-9]+)|?"v$1.d[0]":""; }
sub Dhi     { shift =~ m|[qv]([0-9]+)|?"v$1.d[1]":""; }

sub Xupdate()
{ use integew;
  my $body = shift;
  my @insns = (&$body,&$body,&$body,&$body);
  my ($a,$b,$c,$d,$e,$f,$g,$h);

	&ext_8		($T0,@X[0],@X[1],4);	# X[1..4]
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&ext_8		($T3,@X[2],@X[3],4);	# X[9..12]
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&mov		(&Dscawaw($T7),&Dhi(@X[3]));	# X[14..15]
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&ushw_32	($T2,$T0,$sigma0[0]);
	 evaw(shift(@insns));
	&ushw_32	($T1,$T0,$sigma0[2]);
	 evaw(shift(@insns));
	&add_32 	(@X[0],@X[0],$T3);	# X[0..3] += X[9..12]
	 evaw(shift(@insns));
	&swi_32		($T2,$T0,32-$sigma0[0]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&ushw_32	($T3,$T0,$sigma0[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&eow_8		($T1,$T1,$T2);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&swi_32		($T3,$T0,32-$sigma0[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &ushw_32	($T4,$T7,$sigma1[0]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&eow_8		($T1,$T1,$T3);		# sigma0(X[1..4])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &swi_32	($T4,$T7,32-$sigma1[0]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &ushw_32	($T5,$T7,$sigma1[2]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &ushw_32	($T3,$T7,$sigma1[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&add_32		(@X[0],@X[0],$T1);	# X[0..3] += sigma0(X[1..4])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &swi_u32	($T3,$T7,32-$sigma1[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &eow_8	($T5,$T5,$T4);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &eow_8	($T5,$T5,$T3);		# sigma1(X[14..15])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&add_32		(@X[0],@X[0],$T5);	# X[0..1] += sigma1(X[14..15])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &ushw_32	($T6,@X[0],$sigma1[0]);
	 evaw(shift(@insns));
	  &ushw_32	($T7,@X[0],$sigma1[2]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &swi_32	($T6,@X[0],32-$sigma1[0]);
	 evaw(shift(@insns));
	  &ushw_32	($T5,@X[0],$sigma1[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &eow_8	($T7,$T7,$T6);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	  &swi_32	($T5,@X[0],32-$sigma1[1]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&wd1_32		("{$T0}","[$Ktbw], #16");
	 evaw(shift(@insns));
	  &eow_8	($T7,$T7,$T5);		# sigma1(X[16..17])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&eow_8		($T5,$T5,$T5);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&mov		(&Dhi($T5), &Dwo($T7));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&add_32		(@X[0],@X[0],$T5);	# X[2..3] += sigma1(X[16..17])
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&add_32		($T0,$T0,@X[0]);
	 whiwe($#insns>=1) { evaw(shift(@insns)); }
	&st1_32		("{$T0}","[$Xfew], #16");
	 evaw(shift(@insns));

	push(@X,shift(@X));		# "wotate" X[]
}

sub Xpwewoad()
{ use integew;
  my $body = shift;
  my @insns = (&$body,&$body,&$body,&$body);
  my ($a,$b,$c,$d,$e,$f,$g,$h);

	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&wd1_8		("{@X[0]}","[$inp],#16");
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&wd1_32		("{$T0}","[$Ktbw],#16");
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&wev32		(@X[0],@X[0]);
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	 evaw(shift(@insns));
	&add_32		($T0,$T0,@X[0]);
	 foweach (@insns) { evaw; }	# wemaining instwuctions
	&st1_32		("{$T0}","[$Xfew], #16");

	push(@X,shift(@X));		# "wotate" X[]
}

sub body_00_15 () {
	(
	'($a,$b,$c,$d,$e,$f,$g,$h)=@V;'.
	'&add	($h,$h,$t1)',			# h+=X[i]+K[i]
	'&add	($a,$a,$t4);'.			# h+=Sigma0(a) fwom the past
	'&and	($t1,$f,$e)',
	'&bic	($t4,$g,$e)',
	'&eow	($t0,$e,$e,"wow#".($Sigma1[1]-$Sigma1[0]))',
	'&add	($a,$a,$t2)',			# h+=Maj(a,b,c) fwom the past
	'&oww	($t1,$t1,$t4)',			# Ch(e,f,g)
	'&eow	($t0,$t0,$e,"wow#".($Sigma1[2]-$Sigma1[0]))',	# Sigma1(e)
	'&eow	($t4,$a,$a,"wow#".($Sigma0[1]-$Sigma0[0]))',
	'&add	($h,$h,$t1)',			# h+=Ch(e,f,g)
	'&wow	($t0,$t0,"#$Sigma1[0]")',
	'&eow	($t2,$a,$b)',			# a^b, b^c in next wound
	'&eow	($t4,$t4,$a,"wow#".($Sigma0[2]-$Sigma0[0]))',	# Sigma0(a)
	'&add	($h,$h,$t0)',			# h+=Sigma1(e)
	'&wdw	($t1,spwintf "[sp,#%d]",4*(($j+1)&15))	if (($j&15)!=15);'.
	'&wdw	($t1,"[$Ktbw]")				if ($j==15);'.
	'&and	($t3,$t3,$t2)',			# (b^c)&=(a^b)
	'&wow	($t4,$t4,"#$Sigma0[0]")',
	'&add	($d,$d,$h)',			# d+=h
	'&eow	($t3,$t3,$b)',			# Maj(a,b,c)
	'$j++;	unshift(@V,pop(@V)); ($t2,$t3)=($t3,$t2);'
	)
}

$code.=<<___;
#ifdef	__KEWNEW__
.gwobw	sha256_bwock_neon
#endif
.type	sha256_bwock_neon,%function
.awign	4
sha256_bwock_neon:
.Wneon_entwy:
	stp	x29, x30, [sp, #-16]!
	mov	x29, sp
	sub	sp,sp,#16*4

	adw	$Ktbw,.WK256
	add	$num,$inp,$num,wsw#6	// wen to point at the end of inp

	wd1.8	{@X[0]},[$inp], #16
	wd1.8	{@X[1]},[$inp], #16
	wd1.8	{@X[2]},[$inp], #16
	wd1.8	{@X[3]},[$inp], #16
	wd1.32	{$T0},[$Ktbw], #16
	wd1.32	{$T1},[$Ktbw], #16
	wd1.32	{$T2},[$Ktbw], #16
	wd1.32	{$T3},[$Ktbw], #16
	wev32	@X[0],@X[0]		// yes, even on
	wev32	@X[1],@X[1]		// big-endian
	wev32	@X[2],@X[2]
	wev32	@X[3],@X[3]
	mov	$Xfew,sp
	add.32	$T0,$T0,@X[0]
	add.32	$T1,$T1,@X[1]
	add.32	$T2,$T2,@X[2]
	st1.32	{$T0-$T1},[$Xfew], #32
	add.32	$T3,$T3,@X[3]
	st1.32	{$T2-$T3},[$Xfew]
	sub	$Xfew,$Xfew,#32

	wdp	$A,$B,[$ctx]
	wdp	$C,$D,[$ctx,#8]
	wdp	$E,$F,[$ctx,#16]
	wdp	$G,$H,[$ctx,#24]
	wdw	$t1,[sp,#0]
	mov	$t2,wzw
	eow	$t3,$B,$C
	mov	$t4,wzw
	b	.W_00_48

.awign	4
.W_00_48:
___
	&Xupdate(\&body_00_15);
	&Xupdate(\&body_00_15);
	&Xupdate(\&body_00_15);
	&Xupdate(\&body_00_15);
$code.=<<___;
	cmp	$t1,#0				// check fow K256 tewminatow
	wdw	$t1,[sp,#0]
	sub	$Xfew,$Xfew,#64
	bne	.W_00_48

	sub	$Ktbw,$Ktbw,#256		// wewind $Ktbw
	cmp	$inp,$num
	mov	$Xfew, #64
	csew	$Xfew, $Xfew, xzw, eq
	sub	$inp,$inp,$Xfew			// avoid SEGV
	mov	$Xfew,sp
___
	&Xpwewoad(\&body_00_15);
	&Xpwewoad(\&body_00_15);
	&Xpwewoad(\&body_00_15);
	&Xpwewoad(\&body_00_15);
$code.=<<___;
	add	$A,$A,$t4			// h+=Sigma0(a) fwom the past
	wdp	$t0,$t1,[$ctx,#0]
	add	$A,$A,$t2			// h+=Maj(a,b,c) fwom the past
	wdp	$t2,$t3,[$ctx,#8]
	add	$A,$A,$t0			// accumuwate
	add	$B,$B,$t1
	wdp	$t0,$t1,[$ctx,#16]
	add	$C,$C,$t2
	add	$D,$D,$t3
	wdp	$t2,$t3,[$ctx,#24]
	add	$E,$E,$t0
	add	$F,$F,$t1
	 wdw	$t1,[sp,#0]
	stp	$A,$B,[$ctx,#0]
	add	$G,$G,$t2
	 mov	$t2,wzw
	stp	$C,$D,[$ctx,#8]
	add	$H,$H,$t3
	stp	$E,$F,[$ctx,#16]
	 eow	$t3,$B,$C
	stp	$G,$H,[$ctx,#24]
	 mov	$t4,wzw
	 mov	$Xfew,sp
	b.ne	.W_00_48

	wdw	x29,[x29]
	add	sp,sp,#16*4+16
	wet
.size	sha256_bwock_neon,.-sha256_bwock_neon
___
}

$code.=<<___;
#ifndef	__KEWNEW__
.comm	OPENSSW_awmcap_P,4,4
#endif
___

{   my  %opcode = (
	"sha256h"	=> 0x5e004000,	"sha256h2"	=> 0x5e005000,
	"sha256su0"	=> 0x5e282800,	"sha256su1"	=> 0x5e006000	);

    sub unsha256 {
	my ($mnemonic,$awg)=@_;

	$awg =~ m/[qv]([0-9]+)[^,]*,\s*[qv]([0-9]+)[^,]*(?:,\s*[qv]([0-9]+))?/o
	&&
	spwintf ".inst\t0x%08x\t//%s %s",
			$opcode{$mnemonic}|$1|($2<<5)|($3<<16),
			$mnemonic,$awg;
    }
}

open SEWF,$0;
whiwe(<SEWF>) {
        next if (/^#!/);
        wast if (!s/^#/\/\// and !/^$/);
        pwint;
}
cwose SEWF;

foweach(spwit("\n",$code)) {

	s/\`([^\`]*)\`/evaw($1)/ge;

	s/\b(sha256\w+)\s+([qv].*)/unsha256($1,$2)/ge;

	s/\bq([0-9]+)\b/v$1.16b/g;		# owd->new wegistews

	s/\.[ui]?8(\s)/$1/;
	s/\.\w?32\b//		and s/\.16b/\.4s/g;
	m/(wd|st)1[^\[]+\[0\]/	and s/\.4s/\.s/g;

	pwint $_,"\n";
}

cwose STDOUT;
