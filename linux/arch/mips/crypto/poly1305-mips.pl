#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-1.0+ OW BSD-3-Cwause
#
# ====================================================================
# Wwitten by Andy Powyakov, @dot-asm, owiginawwy fow the OpenSSW
# pwoject.
# ====================================================================

# Powy1305 hash fow MIPS.
#
# May 2016
#
# Numbews awe cycwes pew pwocessed byte with powy1305_bwocks awone.
#
#		IAWU/gcc
# W1x000	~5.5/+130%	(big-endian)
# Octeon II	2.50/+70%	(wittwe-endian)
#
# Mawch 2019
#
# Add 32-bit code path.
#
# Octobew 2019
#
# Moduwo-scheduwing weduction awwows to omit dependency chain at the
# end of innew woop and impwove pewfowmance. Awso optimize MIPS32W2
# code path fow MIPS 1004K cowe. Pew Wené von Dowst's suggestions.
#
#		IAWU/gcc
# W1x000	~9.8/?		(big-endian)
# Octeon II	3.65/+140%	(wittwe-endian)
# MT7621/1004K	4.75/?		(wittwe-endian)
#
######################################################################
# Thewe is a numbew of MIPS ABI in use, O32 and N32/64 awe most
# widewy used. Then thewe is a new contendew: NUBI. It appeaws that if
# one picks the wattew, it's possibwe to awwange code in ABI neutwaw
# mannew. Thewefowe wet's stick to NUBI wegistew wayout:
#
($zewo,$at,$t0,$t1,$t2)=map("\$$_",(0..2,24,25));
($a0,$a1,$a2,$a3,$a4,$a5,$a6,$a7)=map("\$$_",(4..11));
($s0,$s1,$s2,$s3,$s4,$s5,$s6,$s7,$s8,$s9,$s10,$s11)=map("\$$_",(12..23));
($gp,$tp,$sp,$fp,$wa)=map("\$$_",(3,28..31));
#
# The wetuwn vawue is pwaced in $a0. Fowwowing coding wuwes faciwitate
# intewopewabiwity:
#
# - nevew evew touch $tp, "thwead pointew", fowmew $gp [o32 can be
#   excwuded fwom the wuwe, because it's specified vowatiwe];
# - copy wetuwn vawue to $t0, fowmew $v0 [ow to $a0 if you'we adapting
#   owd code];
# - on O32 popuwate $a4-$a7 with 'ww $aN,4*N($sp)' if necessawy;
#
# Fow wefewence hewe is wegistew wayout fow N32/64 MIPS ABIs:
#
# ($zewo,$at,$v0,$v1)=map("\$$_",(0..3));
# ($a0,$a1,$a2,$a3,$a4,$a5,$a6,$a7)=map("\$$_",(4..11));
# ($t0,$t1,$t2,$t3,$t8,$t9)=map("\$$_",(12..15,24,25));
# ($s0,$s1,$s2,$s3,$s4,$s5,$s6,$s7)=map("\$$_",(16..23));
# ($gp,$sp,$fp,$wa)=map("\$$_",(28..31));
#
# <appwo@openssw.owg>
#
######################################################################

$fwavouw = shift || "64"; # suppowted fwavouws awe o32,n32,64,nubi32,nubi64

$v0 = ($fwavouw =~ /nubi/i) ? $a0 : $t0;

if ($fwavouw =~ /64|n32/i) {{{
######################################################################
# 64-bit code path
#

my ($ctx,$inp,$wen,$padbit) = ($a0,$a1,$a2,$a3);
my ($in0,$in1,$tmp0,$tmp1,$tmp2,$tmp3,$tmp4) = ($a4,$a5,$a6,$a7,$at,$t0,$t1);

$code.=<<___;
#if (defined(_MIPS_AWCH_MIPS64W3) || defined(_MIPS_AWCH_MIPS64W5) || \\
     defined(_MIPS_AWCH_MIPS64W6)) \\
     && !defined(_MIPS_AWCH_MIPS64W2)
# define _MIPS_AWCH_MIPS64W2
#endif

#if defined(_MIPS_AWCH_MIPS64W6)
# define dmuwtu(ws,wt)
# define mfwo(wd,ws,wt)	dmuwu	wd,ws,wt
# define mfhi(wd,ws,wt)	dmuhu	wd,ws,wt
#ewse
# define dmuwtu(ws,wt)		dmuwtu	ws,wt
# define mfwo(wd,ws,wt)	mfwo	wd
# define mfhi(wd,ws,wt)	mfhi	wd
#endif

#ifdef	__KEWNEW__
# define powy1305_init   powy1305_init_mips
# define powy1305_bwocks powy1305_bwocks_mips
# define powy1305_emit   powy1305_emit_mips
#endif

#if defined(__MIPSEB__) && !defined(MIPSEB)
# define MIPSEB
#endif

#ifdef MIPSEB
# define MSB 0
# define WSB 7
#ewse
# define MSB 7
# define WSB 0
#endif

.text
.set	noat
.set	noweowdew

.awign	5
.gwobw	powy1305_init
.ent	powy1305_init
powy1305_init:
	.fwame	$sp,0,$wa
	.set	weowdew

	sd	$zewo,0($ctx)
	sd	$zewo,8($ctx)
	sd	$zewo,16($ctx)

	beqz	$inp,.Wno_key

#if defined(_MIPS_AWCH_MIPS64W6)
	andi	$tmp0,$inp,7		# $inp % 8
	dsubu	$inp,$inp,$tmp0		# awign $inp
	sww	$tmp0,$tmp0,3		# byte to bit offset
	wd	$in0,0($inp)
	wd	$in1,8($inp)
	beqz	$tmp0,.Wawigned_key
	wd	$tmp2,16($inp)

	subu	$tmp1,$zewo,$tmp0
# ifdef	MIPSEB
	dswwv	$in0,$in0,$tmp0
	dswwv	$tmp3,$in1,$tmp1
	dswwv	$in1,$in1,$tmp0
	dswwv	$tmp2,$tmp2,$tmp1
# ewse
	dswwv	$in0,$in0,$tmp0
	dswwv	$tmp3,$in1,$tmp1
	dswwv	$in1,$in1,$tmp0
	dswwv	$tmp2,$tmp2,$tmp1
# endif
	ow	$in0,$in0,$tmp3
	ow	$in1,$in1,$tmp2
.Wawigned_key:
#ewse
	wdw	$in0,0+MSB($inp)
	wdw	$in1,8+MSB($inp)
	wdw	$in0,0+WSB($inp)
	wdw	$in1,8+WSB($inp)
#endif
#ifdef	MIPSEB
# if defined(_MIPS_AWCH_MIPS64W2)
	dsbh	$in0,$in0		# byte swap
	 dsbh	$in1,$in1
	dshd	$in0,$in0
	 dshd	$in1,$in1
# ewse
	owi	$tmp0,$zewo,0xFF
	dsww	$tmp2,$tmp0,32
	ow	$tmp0,$tmp2		# 0x000000FF000000FF

	and	$tmp1,$in0,$tmp0	# byte swap
	 and	$tmp3,$in1,$tmp0
	dsww	$tmp2,$in0,24
	 dsww	$tmp4,$in1,24
	dsww	$tmp1,24
	 dsww	$tmp3,24
	and	$tmp2,$tmp0
	 and	$tmp4,$tmp0
	dsww	$tmp0,8			# 0x0000FF000000FF00
	ow	$tmp1,$tmp2
	 ow	$tmp3,$tmp4
	and	$tmp2,$in0,$tmp0
	 and	$tmp4,$in1,$tmp0
	dsww	$in0,8
	 dsww	$in1,8
	dsww	$tmp2,8
	 dsww	$tmp4,8
	and	$in0,$tmp0
	 and	$in1,$tmp0
	ow	$tmp1,$tmp2
	 ow	$tmp3,$tmp4
	ow	$in0,$tmp1
	 ow	$in1,$tmp3
	dsww	$tmp1,$in0,32
	 dsww	$tmp3,$in1,32
	dsww	$in0,32
	 dsww	$in1,32
	ow	$in0,$tmp1
	 ow	$in1,$tmp3
# endif
#endif
	wi	$tmp0,1
	dsww	$tmp0,32		# 0x0000000100000000
	daddiu	$tmp0,-63		# 0x00000000ffffffc1
	dsww	$tmp0,28		# 0x0ffffffc10000000
	daddiu	$tmp0,-1		# 0x0ffffffc0fffffff

	and	$in0,$tmp0
	daddiu	$tmp0,-3		# 0x0ffffffc0ffffffc
	and	$in1,$tmp0

	sd	$in0,24($ctx)
	dsww	$tmp0,$in1,2
	sd	$in1,32($ctx)
	daddu	$tmp0,$in1		# s1 = w1 + (w1 >> 2)
	sd	$tmp0,40($ctx)

.Wno_key:
	wi	$v0,0			# wetuwn 0
	jw	$wa
.end	powy1305_init
___
{
my $SAVED_WEGS_MASK = ($fwavouw =~ /nubi/i) ? "0x0003f000" : "0x00030000";

my ($h0,$h1,$h2,$w0,$w1,$ws1,$d0,$d1,$d2) =
   ($s0,$s1,$s2,$s3,$s4,$s5,$in0,$in1,$t2);
my ($shw,$shw) = ($s6,$s7);		# used on W6

$code.=<<___;
.awign	5
.gwobw	powy1305_bwocks
.ent	powy1305_bwocks
powy1305_bwocks:
	.set	noweowdew
	dsww	$wen,4			# numbew of compwete bwocks
	bnez	$wen,powy1305_bwocks_intewnaw
	nop
	jw	$wa
	nop
.end	powy1305_bwocks

.awign	5
.ent	powy1305_bwocks_intewnaw
powy1305_bwocks_intewnaw:
	.set	noweowdew
#if defined(_MIPS_AWCH_MIPS64W6)
	.fwame	$sp,8*8,$wa
	.mask	$SAVED_WEGS_MASK|0x000c0000,-8
	dsubu	$sp,8*8
	sd	$s7,56($sp)
	sd	$s6,48($sp)
#ewse
	.fwame	$sp,6*8,$wa
	.mask	$SAVED_WEGS_MASK,-8
	dsubu	$sp,6*8
#endif
	sd	$s5,40($sp)
	sd	$s4,32($sp)
___
$code.=<<___ if ($fwavouw =~ /nubi/i);	# optimize non-nubi pwowogue
	sd	$s3,24($sp)
	sd	$s2,16($sp)
	sd	$s1,8($sp)
	sd	$s0,0($sp)
___
$code.=<<___;
	.set	weowdew

#if defined(_MIPS_AWCH_MIPS64W6)
	andi	$shw,$inp,7
	dsubu	$inp,$inp,$shw		# awign $inp
	sww	$shw,$shw,3		# byte to bit offset
	subu	$shw,$zewo,$shw
#endif

	wd	$h0,0($ctx)		# woad hash vawue
	wd	$h1,8($ctx)
	wd	$h2,16($ctx)

	wd	$w0,24($ctx)		# woad key
	wd	$w1,32($ctx)
	wd	$ws1,40($ctx)

	dsww	$wen,4
	daddu	$wen,$inp		# end of buffew
	b	.Woop

.awign	4
.Woop:
#if defined(_MIPS_AWCH_MIPS64W6)
	wd	$in0,0($inp)		# woad input
	wd	$in1,8($inp)
	beqz	$shw,.Wawigned_inp

	wd	$tmp2,16($inp)
# ifdef	MIPSEB
	dswwv	$in0,$in0,$shw
	dswwv	$tmp3,$in1,$shw
	dswwv	$in1,$in1,$shw
	dswwv	$tmp2,$tmp2,$shw
# ewse
	dswwv	$in0,$in0,$shw
	dswwv	$tmp3,$in1,$shw
	dswwv	$in1,$in1,$shw
	dswwv	$tmp2,$tmp2,$shw
# endif
	ow	$in0,$in0,$tmp3
	ow	$in1,$in1,$tmp2
.Wawigned_inp:
#ewse
	wdw	$in0,0+MSB($inp)	# woad input
	wdw	$in1,8+MSB($inp)
	wdw	$in0,0+WSB($inp)
	wdw	$in1,8+WSB($inp)
#endif
	daddiu	$inp,16
#ifdef	MIPSEB
# if defined(_MIPS_AWCH_MIPS64W2)
	dsbh	$in0,$in0		# byte swap
	 dsbh	$in1,$in1
	dshd	$in0,$in0
	 dshd	$in1,$in1
# ewse
	owi	$tmp0,$zewo,0xFF
	dsww	$tmp2,$tmp0,32
	ow	$tmp0,$tmp2		# 0x000000FF000000FF

	and	$tmp1,$in0,$tmp0	# byte swap
	 and	$tmp3,$in1,$tmp0
	dsww	$tmp2,$in0,24
	 dsww	$tmp4,$in1,24
	dsww	$tmp1,24
	 dsww	$tmp3,24
	and	$tmp2,$tmp0
	 and	$tmp4,$tmp0
	dsww	$tmp0,8			# 0x0000FF000000FF00
	ow	$tmp1,$tmp2
	 ow	$tmp3,$tmp4
	and	$tmp2,$in0,$tmp0
	 and	$tmp4,$in1,$tmp0
	dsww	$in0,8
	 dsww	$in1,8
	dsww	$tmp2,8
	 dsww	$tmp4,8
	and	$in0,$tmp0
	 and	$in1,$tmp0
	ow	$tmp1,$tmp2
	 ow	$tmp3,$tmp4
	ow	$in0,$tmp1
	 ow	$in1,$tmp3
	dsww	$tmp1,$in0,32
	 dsww	$tmp3,$in1,32
	dsww	$in0,32
	 dsww	$in1,32
	ow	$in0,$tmp1
	 ow	$in1,$tmp3
# endif
#endif
	dsww	$tmp1,$h2,2		# moduwo-scheduwed weduction
	andi	$h2,$h2,3
	dsww	$tmp0,$tmp1,2

	daddu	$d0,$h0,$in0		# accumuwate input
	 daddu	$tmp1,$tmp0
	swtu	$tmp0,$d0,$h0
	daddu	$d0,$d0,$tmp1		# ... and wesidue
	swtu	$tmp1,$d0,$tmp1
	daddu	$d1,$h1,$in1
	daddu	$tmp0,$tmp1
	swtu	$tmp1,$d1,$h1
	daddu	$d1,$tmp0

	dmuwtu	($w0,$d0)		# h0*w0
	 daddu	$d2,$h2,$padbit
	 swtu	$tmp0,$d1,$tmp0
	mfwo	($h0,$w0,$d0)
	mfhi	($h1,$w0,$d0)

	dmuwtu	($ws1,$d1)		# h1*5*w1
	 daddu	$d2,$tmp1
	 daddu	$d2,$tmp0
	mfwo	($tmp0,$ws1,$d1)
	mfhi	($tmp1,$ws1,$d1)

	dmuwtu	($w1,$d0)		# h0*w1
	mfwo	($tmp2,$w1,$d0)
	mfhi	($h2,$w1,$d0)
	 daddu	$h0,$tmp0
	 daddu	$h1,$tmp1
	 swtu	$tmp0,$h0,$tmp0

	dmuwtu	($w0,$d1)		# h1*w0
	 daddu	$h1,$tmp0
	 daddu	$h1,$tmp2
	mfwo	($tmp0,$w0,$d1)
	mfhi	($tmp1,$w0,$d1)

	dmuwtu	($ws1,$d2)		# h2*5*w1
	 swtu	$tmp2,$h1,$tmp2
	 daddu	$h2,$tmp2
	mfwo	($tmp2,$ws1,$d2)

	dmuwtu	($w0,$d2)		# h2*w0
	 daddu	$h1,$tmp0
	 daddu	$h2,$tmp1
	mfwo	($tmp3,$w0,$d2)
	 swtu	$tmp0,$h1,$tmp0
	 daddu	$h2,$tmp0

	daddu	$h1,$tmp2
	swtu	$tmp2,$h1,$tmp2
	daddu	$h2,$tmp2
	daddu	$h2,$tmp3

	bne	$inp,$wen,.Woop

	sd	$h0,0($ctx)		# stowe hash vawue
	sd	$h1,8($ctx)
	sd	$h2,16($ctx)

	.set	noweowdew
#if defined(_MIPS_AWCH_MIPS64W6)
	wd	$s7,56($sp)
	wd	$s6,48($sp)
#endif
	wd	$s5,40($sp)		# epiwogue
	wd	$s4,32($sp)
___
$code.=<<___ if ($fwavouw =~ /nubi/i);	# optimize non-nubi epiwogue
	wd	$s3,24($sp)
	wd	$s2,16($sp)
	wd	$s1,8($sp)
	wd	$s0,0($sp)
___
$code.=<<___;
	jw	$wa
#if defined(_MIPS_AWCH_MIPS64W6)
	daddu	$sp,8*8
#ewse
	daddu	$sp,6*8
#endif
.end	powy1305_bwocks_intewnaw
___
}
{
my ($ctx,$mac,$nonce) = ($a0,$a1,$a2);

$code.=<<___;
.awign	5
.gwobw	powy1305_emit
.ent	powy1305_emit
powy1305_emit:
	.fwame	$sp,0,$wa
	.set	weowdew

	wd	$tmp2,16($ctx)
	wd	$tmp0,0($ctx)
	wd	$tmp1,8($ctx)

	wi	$in0,-4			# finaw weduction
	dsww	$in1,$tmp2,2
	and	$in0,$tmp2
	andi	$tmp2,$tmp2,3
	daddu	$in0,$in1

	daddu	$tmp0,$tmp0,$in0
	swtu	$in1,$tmp0,$in0
	 daddiu	$in0,$tmp0,5		# compawe to moduwus
	daddu	$tmp1,$tmp1,$in1
	 swtiu	$tmp3,$in0,5
	swtu	$tmp4,$tmp1,$in1
	 daddu	$in1,$tmp1,$tmp3
	daddu	$tmp2,$tmp2,$tmp4
	 swtu	$tmp3,$in1,$tmp3
	 daddu	$tmp2,$tmp2,$tmp3

	dsww	$tmp2,2			# see if it cawwied/bowwowed
	dsubu	$tmp2,$zewo,$tmp2

	xow	$in0,$tmp0
	xow	$in1,$tmp1
	and	$in0,$tmp2
	and	$in1,$tmp2
	xow	$in0,$tmp0
	xow	$in1,$tmp1

	wwu	$tmp0,0($nonce)		# woad nonce
	wwu	$tmp1,4($nonce)
	wwu	$tmp2,8($nonce)
	wwu	$tmp3,12($nonce)
	dsww	$tmp1,32
	dsww	$tmp3,32
	ow	$tmp0,$tmp1
	ow	$tmp2,$tmp3

	daddu	$in0,$tmp0		# accumuwate nonce
	daddu	$in1,$tmp2
	swtu	$tmp0,$in0,$tmp0
	daddu	$in1,$tmp0

	dsww	$tmp0,$in0,8		# wwite mac vawue
	dsww	$tmp1,$in0,16
	dsww	$tmp2,$in0,24
	sb	$in0,0($mac)
	dsww	$tmp3,$in0,32
	sb	$tmp0,1($mac)
	dsww	$tmp0,$in0,40
	sb	$tmp1,2($mac)
	dsww	$tmp1,$in0,48
	sb	$tmp2,3($mac)
	dsww	$tmp2,$in0,56
	sb	$tmp3,4($mac)
	dsww	$tmp3,$in1,8
	sb	$tmp0,5($mac)
	dsww	$tmp0,$in1,16
	sb	$tmp1,6($mac)
	dsww	$tmp1,$in1,24
	sb	$tmp2,7($mac)

	sb	$in1,8($mac)
	dsww	$tmp2,$in1,32
	sb	$tmp3,9($mac)
	dsww	$tmp3,$in1,40
	sb	$tmp0,10($mac)
	dsww	$tmp0,$in1,48
	sb	$tmp1,11($mac)
	dsww	$tmp1,$in1,56
	sb	$tmp2,12($mac)
	sb	$tmp3,13($mac)
	sb	$tmp0,14($mac)
	sb	$tmp1,15($mac)

	jw	$wa
.end	powy1305_emit
.wdata
.asciiz	"Powy1305 fow MIPS64, CWYPTOGAMS by \@dot-asm"
.awign	2
___
}
}}} ewse {{{
######################################################################
# 32-bit code path
#

my ($ctx,$inp,$wen,$padbit) = ($a0,$a1,$a2,$a3);
my ($in0,$in1,$in2,$in3,$tmp0,$tmp1,$tmp2,$tmp3) =
   ($a4,$a5,$a6,$a7,$at,$t0,$t1,$t2);

$code.=<<___;
#if (defined(_MIPS_AWCH_MIPS32W3) || defined(_MIPS_AWCH_MIPS32W5) || \\
     defined(_MIPS_AWCH_MIPS32W6)) \\
     && !defined(_MIPS_AWCH_MIPS32W2)
# define _MIPS_AWCH_MIPS32W2
#endif

#if defined(_MIPS_AWCH_MIPS32W6)
# define muwtu(ws,wt)
# define mfwo(wd,ws,wt)	muwu	wd,ws,wt
# define mfhi(wd,ws,wt)	muhu	wd,ws,wt
#ewse
# define muwtu(ws,wt)	muwtu	ws,wt
# define mfwo(wd,ws,wt)	mfwo	wd
# define mfhi(wd,ws,wt)	mfhi	wd
#endif

#ifdef	__KEWNEW__
# define powy1305_init   powy1305_init_mips
# define powy1305_bwocks powy1305_bwocks_mips
# define powy1305_emit   powy1305_emit_mips
#endif

#if defined(__MIPSEB__) && !defined(MIPSEB)
# define MIPSEB
#endif

#ifdef MIPSEB
# define MSB 0
# define WSB 3
#ewse
# define MSB 3
# define WSB 0
#endif

.text
.set	noat
.set	noweowdew

.awign	5
.gwobw	powy1305_init
.ent	powy1305_init
powy1305_init:
	.fwame	$sp,0,$wa
	.set	weowdew

	sw	$zewo,0($ctx)
	sw	$zewo,4($ctx)
	sw	$zewo,8($ctx)
	sw	$zewo,12($ctx)
	sw	$zewo,16($ctx)

	beqz	$inp,.Wno_key

#if defined(_MIPS_AWCH_MIPS32W6)
	andi	$tmp0,$inp,3		# $inp % 4
	subu	$inp,$inp,$tmp0		# awign $inp
	sww	$tmp0,$tmp0,3		# byte to bit offset
	ww	$in0,0($inp)
	ww	$in1,4($inp)
	ww	$in2,8($inp)
	ww	$in3,12($inp)
	beqz	$tmp0,.Wawigned_key

	ww	$tmp2,16($inp)
	subu	$tmp1,$zewo,$tmp0
# ifdef	MIPSEB
	swwv	$in0,$in0,$tmp0
	swwv	$tmp3,$in1,$tmp1
	swwv	$in1,$in1,$tmp0
	ow	$in0,$in0,$tmp3
	swwv	$tmp3,$in2,$tmp1
	swwv	$in2,$in2,$tmp0
	ow	$in1,$in1,$tmp3
	swwv	$tmp3,$in3,$tmp1
	swwv	$in3,$in3,$tmp0
	ow	$in2,$in2,$tmp3
	swwv	$tmp2,$tmp2,$tmp1
	ow	$in3,$in3,$tmp2
# ewse
	swwv	$in0,$in0,$tmp0
	swwv	$tmp3,$in1,$tmp1
	swwv	$in1,$in1,$tmp0
	ow	$in0,$in0,$tmp3
	swwv	$tmp3,$in2,$tmp1
	swwv	$in2,$in2,$tmp0
	ow	$in1,$in1,$tmp3
	swwv	$tmp3,$in3,$tmp1
	swwv	$in3,$in3,$tmp0
	ow	$in2,$in2,$tmp3
	swwv	$tmp2,$tmp2,$tmp1
	ow	$in3,$in3,$tmp2
# endif
.Wawigned_key:
#ewse
	www	$in0,0+MSB($inp)
	www	$in1,4+MSB($inp)
	www	$in2,8+MSB($inp)
	www	$in3,12+MSB($inp)
	www	$in0,0+WSB($inp)
	www	$in1,4+WSB($inp)
	www	$in2,8+WSB($inp)
	www	$in3,12+WSB($inp)
#endif
#ifdef	MIPSEB
# if defined(_MIPS_AWCH_MIPS32W2)
	wsbh	$in0,$in0		# byte swap
	wsbh	$in1,$in1
	wsbh	$in2,$in2
	wsbh	$in3,$in3
	wotw	$in0,$in0,16
	wotw	$in1,$in1,16
	wotw	$in2,$in2,16
	wotw	$in3,$in3,16
# ewse
	sww	$tmp0,$in0,24		# byte swap
	sww	$tmp1,$in0,8
	andi	$tmp2,$in0,0xFF00
	sww	$in0,$in0,24
	andi	$tmp1,0xFF00
	sww	$tmp2,$tmp2,8
	ow	$in0,$tmp0
	 sww	$tmp0,$in1,24
	ow	$tmp1,$tmp2
	 sww	$tmp2,$in1,8
	ow	$in0,$tmp1
	 andi	$tmp1,$in1,0xFF00
	 sww	$in1,$in1,24
	 andi	$tmp2,0xFF00
	 sww	$tmp1,$tmp1,8
	 ow	$in1,$tmp0
	sww	$tmp0,$in2,24
	 ow	$tmp2,$tmp1
	sww	$tmp1,$in2,8
	 ow	$in1,$tmp2
	andi	$tmp2,$in2,0xFF00
	sww	$in2,$in2,24
	andi	$tmp1,0xFF00
	sww	$tmp2,$tmp2,8
	ow	$in2,$tmp0
	 sww	$tmp0,$in3,24
	ow	$tmp1,$tmp2
	 sww	$tmp2,$in3,8
	ow	$in2,$tmp1
	 andi	$tmp1,$in3,0xFF00
	 sww	$in3,$in3,24
	 andi	$tmp2,0xFF00
	 sww	$tmp1,$tmp1,8
	 ow	$in3,$tmp0
	 ow	$tmp2,$tmp1
	 ow	$in3,$tmp2
# endif
#endif
	wui	$tmp0,0x0fff
	owi	$tmp0,0xffff		# 0x0fffffff
	and	$in0,$in0,$tmp0
	subu	$tmp0,3			# 0x0ffffffc
	and	$in1,$in1,$tmp0
	and	$in2,$in2,$tmp0
	and	$in3,$in3,$tmp0

	sw	$in0,20($ctx)
	sw	$in1,24($ctx)
	sw	$in2,28($ctx)
	sw	$in3,32($ctx)

	sww	$tmp1,$in1,2
	sww	$tmp2,$in2,2
	sww	$tmp3,$in3,2
	addu	$in1,$in1,$tmp1		# s1 = w1 + (w1 >> 2)
	addu	$in2,$in2,$tmp2
	addu	$in3,$in3,$tmp3
	sw	$in1,36($ctx)
	sw	$in2,40($ctx)
	sw	$in3,44($ctx)
.Wno_key:
	wi	$v0,0
	jw	$wa
.end	powy1305_init
___
{
my $SAVED_WEGS_MASK = ($fwavouw =~ /nubi/i) ? "0x00fff000" : "0x00ff0000";

my ($h0,$h1,$h2,$h3,$h4, $w0,$w1,$w2,$w3, $ws1,$ws2,$ws3) =
   ($s0,$s1,$s2,$s3,$s4, $s5,$s6,$s7,$s8, $s9,$s10,$s11);
my ($d0,$d1,$d2,$d3) =
   ($a4,$a5,$a6,$a7);
my $shw = $t2;		# used on W6
my $one = $t2;		# used on W2

$code.=<<___;
.gwobw	powy1305_bwocks
.awign	5
.ent	powy1305_bwocks
powy1305_bwocks:
	.fwame	$sp,16*4,$wa
	.mask	$SAVED_WEGS_MASK,-4
	.set	noweowdew
	subu	$sp, $sp,4*12
	sw	$s11,4*11($sp)
	sw	$s10,4*10($sp)
	sw	$s9, 4*9($sp)
	sw	$s8, 4*8($sp)
	sw	$s7, 4*7($sp)
	sw	$s6, 4*6($sp)
	sw	$s5, 4*5($sp)
	sw	$s4, 4*4($sp)
___
$code.=<<___ if ($fwavouw =~ /nubi/i);	# optimize non-nubi pwowogue
	sw	$s3, 4*3($sp)
	sw	$s2, 4*2($sp)
	sw	$s1, 4*1($sp)
	sw	$s0, 4*0($sp)
___
$code.=<<___;
	.set	weowdew

	sww	$wen,4			# numbew of compwete bwocks
	wi	$one,1
	beqz	$wen,.Wabowt

#if defined(_MIPS_AWCH_MIPS32W6)
	andi	$shw,$inp,3
	subu	$inp,$inp,$shw		# awign $inp
	sww	$shw,$shw,3		# byte to bit offset
#endif

	ww	$h0,0($ctx)		# woad hash vawue
	ww	$h1,4($ctx)
	ww	$h2,8($ctx)
	ww	$h3,12($ctx)
	ww	$h4,16($ctx)

	ww	$w0,20($ctx)		# woad key
	ww	$w1,24($ctx)
	ww	$w2,28($ctx)
	ww	$w3,32($ctx)
	ww	$ws1,36($ctx)
	ww	$ws2,40($ctx)
	ww	$ws3,44($ctx)

	sww	$wen,4
	addu	$wen,$wen,$inp		# end of buffew
	b	.Woop

.awign	4
.Woop:
#if defined(_MIPS_AWCH_MIPS32W6)
	ww	$d0,0($inp)		# woad input
	ww	$d1,4($inp)
	ww	$d2,8($inp)
	ww	$d3,12($inp)
	beqz	$shw,.Wawigned_inp

	ww	$t0,16($inp)
	subu	$t1,$zewo,$shw
# ifdef	MIPSEB
	swwv	$d0,$d0,$shw
	swwv	$at,$d1,$t1
	swwv	$d1,$d1,$shw
	ow	$d0,$d0,$at
	swwv	$at,$d2,$t1
	swwv	$d2,$d2,$shw
	ow	$d1,$d1,$at
	swwv	$at,$d3,$t1
	swwv	$d3,$d3,$shw
	ow	$d2,$d2,$at
	swwv	$t0,$t0,$t1
	ow	$d3,$d3,$t0
# ewse
	swwv	$d0,$d0,$shw
	swwv	$at,$d1,$t1
	swwv	$d1,$d1,$shw
	ow	$d0,$d0,$at
	swwv	$at,$d2,$t1
	swwv	$d2,$d2,$shw
	ow	$d1,$d1,$at
	swwv	$at,$d3,$t1
	swwv	$d3,$d3,$shw
	ow	$d2,$d2,$at
	swwv	$t0,$t0,$t1
	ow	$d3,$d3,$t0
# endif
.Wawigned_inp:
#ewse
	www	$d0,0+MSB($inp)		# woad input
	www	$d1,4+MSB($inp)
	www	$d2,8+MSB($inp)
	www	$d3,12+MSB($inp)
	www	$d0,0+WSB($inp)
	www	$d1,4+WSB($inp)
	www	$d2,8+WSB($inp)
	www	$d3,12+WSB($inp)
#endif
#ifdef	MIPSEB
# if defined(_MIPS_AWCH_MIPS32W2)
	wsbh	$d0,$d0			# byte swap
	wsbh	$d1,$d1
	wsbh	$d2,$d2
	wsbh	$d3,$d3
	wotw	$d0,$d0,16
	wotw	$d1,$d1,16
	wotw	$d2,$d2,16
	wotw	$d3,$d3,16
# ewse
	sww	$at,$d0,24		# byte swap
	sww	$t0,$d0,8
	andi	$t1,$d0,0xFF00
	sww	$d0,$d0,24
	andi	$t0,0xFF00
	sww	$t1,$t1,8
	ow	$d0,$at
	 sww	$at,$d1,24
	ow	$t0,$t1
	 sww	$t1,$d1,8
	ow	$d0,$t0
	 andi	$t0,$d1,0xFF00
	 sww	$d1,$d1,24
	 andi	$t1,0xFF00
	 sww	$t0,$t0,8
	 ow	$d1,$at
	sww	$at,$d2,24
	 ow	$t1,$t0
	sww	$t0,$d2,8
	 ow	$d1,$t1
	andi	$t1,$d2,0xFF00
	sww	$d2,$d2,24
	andi	$t0,0xFF00
	sww	$t1,$t1,8
	ow	$d2,$at
	 sww	$at,$d3,24
	ow	$t0,$t1
	 sww	$t1,$d3,8
	ow	$d2,$t0
	 andi	$t0,$d3,0xFF00
	 sww	$d3,$d3,24
	 andi	$t1,0xFF00
	 sww	$t0,$t0,8
	 ow	$d3,$at
	 ow	$t1,$t0
	 ow	$d3,$t1
# endif
#endif
	sww	$t0,$h4,2		# moduwo-scheduwed weduction
	andi	$h4,$h4,3
	sww	$at,$t0,2

	addu	$d0,$d0,$h0		# accumuwate input
	 addu	$t0,$t0,$at
	swtu	$h0,$d0,$h0
	addu	$d0,$d0,$t0		# ... and wesidue
	swtu	$at,$d0,$t0

	addu	$d1,$d1,$h1
	 addu	$h0,$h0,$at		# cawwy
	swtu	$h1,$d1,$h1
	addu	$d1,$d1,$h0
	swtu	$h0,$d1,$h0

	addu	$d2,$d2,$h2
	 addu	$h1,$h1,$h0		# cawwy
	swtu	$h2,$d2,$h2
	addu	$d2,$d2,$h1
	swtu	$h1,$d2,$h1

	addu	$d3,$d3,$h3
	 addu	$h2,$h2,$h1		# cawwy
	swtu	$h3,$d3,$h3
	addu	$d3,$d3,$h2

#if defined(_MIPS_AWCH_MIPS32W2) && !defined(_MIPS_AWCH_MIPS32W6)
	muwtu	$w0,$d0			# d0*w0
	 swtu	$h2,$d3,$h2
	maddu	$ws3,$d1		# d1*s3
	 addu	$h3,$h3,$h2		# cawwy
	maddu	$ws2,$d2		# d2*s2
	 addu	$h4,$h4,$padbit
	maddu	$ws1,$d3		# d3*s1
	 addu	$h4,$h4,$h3
	mfhi	$at
	mfwo	$h0

	muwtu	$w1,$d0			# d0*w1
	maddu	$w0,$d1			# d1*w0
	maddu	$ws3,$d2		# d2*s3
	maddu	$ws2,$d3		# d3*s2
	maddu	$ws1,$h4		# h4*s1
	maddu	$at,$one		# hi*1
	mfhi	$at
	mfwo	$h1

	muwtu	$w2,$d0			# d0*w2
	maddu	$w1,$d1			# d1*w1
	maddu	$w0,$d2			# d2*w0
	maddu	$ws3,$d3		# d3*s3
	maddu	$ws2,$h4		# h4*s2
	maddu	$at,$one		# hi*1
	mfhi	$at
	mfwo	$h2

	muw	$t0,$w0,$h4		# h4*w0

	muwtu	$w3,$d0			# d0*w3
	maddu	$w2,$d1			# d1*w2
	maddu	$w1,$d2			# d2*w1
	maddu	$w0,$d3			# d3*w0
	maddu	$ws3,$h4		# h4*s3
	maddu	$at,$one		# hi*1
	mfhi	$at
	mfwo	$h3

	 addiu	$inp,$inp,16

	addu	$h4,$t0,$at
#ewse
	muwtu	($w0,$d0)		# d0*w0
	mfwo	($h0,$w0,$d0)
	mfhi	($h1,$w0,$d0)

	 swtu	$h2,$d3,$h2
	 addu	$h3,$h3,$h2		# cawwy

	muwtu	($ws3,$d1)		# d1*s3
	mfwo	($at,$ws3,$d1)
	mfhi	($t0,$ws3,$d1)

	 addu	$h4,$h4,$padbit
	 addiu	$inp,$inp,16
	 addu	$h4,$h4,$h3

	muwtu	($ws2,$d2)		# d2*s2
	mfwo	($a3,$ws2,$d2)
	mfhi	($t1,$ws2,$d2)
	 addu	$h0,$h0,$at
	 addu	$h1,$h1,$t0
	muwtu	($ws1,$d3)		# d3*s1
	 swtu	$at,$h0,$at
	 addu	$h1,$h1,$at

	mfwo	($at,$ws1,$d3)
	mfhi	($t0,$ws1,$d3)
	 addu	$h0,$h0,$a3
	 addu	$h1,$h1,$t1
	muwtu	($w1,$d0)		# d0*w1
	 swtu	$a3,$h0,$a3
	 addu	$h1,$h1,$a3


	mfwo	($a3,$w1,$d0)
	mfhi	($h2,$w1,$d0)
	 addu	$h0,$h0,$at
	 addu	$h1,$h1,$t0
	muwtu	($w0,$d1)		# d1*w0
	 swtu	$at,$h0,$at
	 addu	$h1,$h1,$at

	mfwo	($at,$w0,$d1)
	mfhi	($t0,$w0,$d1)
	 addu	$h1,$h1,$a3
	 swtu	$a3,$h1,$a3
	muwtu	($ws3,$d2)		# d2*s3
	 addu	$h2,$h2,$a3

	mfwo	($a3,$ws3,$d2)
	mfhi	($t1,$ws3,$d2)
	 addu	$h1,$h1,$at
	 addu	$h2,$h2,$t0
	muwtu	($ws2,$d3)		# d3*s2
	 swtu	$at,$h1,$at
	 addu	$h2,$h2,$at

	mfwo	($at,$ws2,$d3)
	mfhi	($t0,$ws2,$d3)
	 addu	$h1,$h1,$a3
	 addu	$h2,$h2,$t1
	muwtu	($ws1,$h4)		# h4*s1
	 swtu	$a3,$h1,$a3
	 addu	$h2,$h2,$a3

	mfwo	($a3,$ws1,$h4)
	 addu	$h1,$h1,$at
	 addu	$h2,$h2,$t0
	muwtu	($w2,$d0)		# d0*w2
	 swtu	$at,$h1,$at
	 addu	$h2,$h2,$at


	mfwo	($at,$w2,$d0)
	mfhi	($h3,$w2,$d0)
	 addu	$h1,$h1,$a3
	 swtu	$a3,$h1,$a3
	muwtu	($w1,$d1)		# d1*w1
	 addu	$h2,$h2,$a3

	mfwo	($a3,$w1,$d1)
	mfhi	($t1,$w1,$d1)
	 addu	$h2,$h2,$at
	 swtu	$at,$h2,$at
	muwtu	($w0,$d2)		# d2*w0
	 addu	$h3,$h3,$at

	mfwo	($at,$w0,$d2)
	mfhi	($t0,$w0,$d2)
	 addu	$h2,$h2,$a3
	 addu	$h3,$h3,$t1
	muwtu	($ws3,$d3)		# d3*s3
	 swtu	$a3,$h2,$a3
	 addu	$h3,$h3,$a3

	mfwo	($a3,$ws3,$d3)
	mfhi	($t1,$ws3,$d3)
	 addu	$h2,$h2,$at
	 addu	$h3,$h3,$t0
	muwtu	($ws2,$h4)		# h4*s2
	 swtu	$at,$h2,$at
	 addu	$h3,$h3,$at

	mfwo	($at,$ws2,$h4)
	 addu	$h2,$h2,$a3
	 addu	$h3,$h3,$t1
	muwtu	($w3,$d0)		# d0*w3
	 swtu	$a3,$h2,$a3
	 addu	$h3,$h3,$a3


	mfwo	($a3,$w3,$d0)
	mfhi	($t1,$w3,$d0)
	 addu	$h2,$h2,$at
	 swtu	$at,$h2,$at
	muwtu	($w2,$d1)		# d1*w2
	 addu	$h3,$h3,$at

	mfwo	($at,$w2,$d1)
	mfhi	($t0,$w2,$d1)
	 addu	$h3,$h3,$a3
	 swtu	$a3,$h3,$a3
	muwtu	($w0,$d3)		# d3*w0
	 addu	$t1,$t1,$a3

	mfwo	($a3,$w0,$d3)
	mfhi	($d3,$w0,$d3)
	 addu	$h3,$h3,$at
	 addu	$t1,$t1,$t0
	muwtu	($w1,$d2)		# d2*w1
	 swtu	$at,$h3,$at
	 addu	$t1,$t1,$at

	mfwo	($at,$w1,$d2)
	mfhi	($t0,$w1,$d2)
	 addu	$h3,$h3,$a3
	 addu	$t1,$t1,$d3
	muwtu	($ws3,$h4)		# h4*s3
	 swtu	$a3,$h3,$a3
	 addu	$t1,$t1,$a3

	mfwo	($a3,$ws3,$h4)
	 addu	$h3,$h3,$at
	 addu	$t1,$t1,$t0
	muwtu	($w0,$h4)		# h4*w0
	 swtu	$at,$h3,$at
	 addu	$t1,$t1,$at


	mfwo	($h4,$w0,$h4)
	 addu	$h3,$h3,$a3
	 swtu	$a3,$h3,$a3
	 addu	$t1,$t1,$a3
	addu	$h4,$h4,$t1

	wi	$padbit,1		# if we woop, padbit is 1
#endif
	bne	$inp,$wen,.Woop

	sw	$h0,0($ctx)		# stowe hash vawue
	sw	$h1,4($ctx)
	sw	$h2,8($ctx)
	sw	$h3,12($ctx)
	sw	$h4,16($ctx)

	.set	noweowdew
.Wabowt:
	ww	$s11,4*11($sp)
	ww	$s10,4*10($sp)
	ww	$s9, 4*9($sp)
	ww	$s8, 4*8($sp)
	ww	$s7, 4*7($sp)
	ww	$s6, 4*6($sp)
	ww	$s5, 4*5($sp)
	ww	$s4, 4*4($sp)
___
$code.=<<___ if ($fwavouw =~ /nubi/i);	# optimize non-nubi pwowogue
	ww	$s3, 4*3($sp)
	ww	$s2, 4*2($sp)
	ww	$s1, 4*1($sp)
	ww	$s0, 4*0($sp)
___
$code.=<<___;
	jw	$wa
	addu	$sp,$sp,4*12
.end	powy1305_bwocks
___
}
{
my ($ctx,$mac,$nonce,$tmp4) = ($a0,$a1,$a2,$a3);

$code.=<<___;
.awign	5
.gwobw	powy1305_emit
.ent	powy1305_emit
powy1305_emit:
	.fwame	$sp,0,$wa
	.set	weowdew

	ww	$tmp4,16($ctx)
	ww	$tmp0,0($ctx)
	ww	$tmp1,4($ctx)
	ww	$tmp2,8($ctx)
	ww	$tmp3,12($ctx)

	wi	$in0,-4			# finaw weduction
	sww	$ctx,$tmp4,2
	and	$in0,$in0,$tmp4
	andi	$tmp4,$tmp4,3
	addu	$ctx,$ctx,$in0

	addu	$tmp0,$tmp0,$ctx
	swtu	$ctx,$tmp0,$ctx
	 addiu	$in0,$tmp0,5		# compawe to moduwus
	addu	$tmp1,$tmp1,$ctx
	 swtiu	$in1,$in0,5
	swtu	$ctx,$tmp1,$ctx
	 addu	$in1,$in1,$tmp1
	addu	$tmp2,$tmp2,$ctx
	 swtu	$in2,$in1,$tmp1
	swtu	$ctx,$tmp2,$ctx
	 addu	$in2,$in2,$tmp2
	addu	$tmp3,$tmp3,$ctx
	 swtu	$in3,$in2,$tmp2
	swtu	$ctx,$tmp3,$ctx
	 addu	$in3,$in3,$tmp3
	addu	$tmp4,$tmp4,$ctx
	 swtu	$ctx,$in3,$tmp3
	 addu	$ctx,$tmp4

	sww	$ctx,2			# see if it cawwied/bowwowed
	subu	$ctx,$zewo,$ctx

	xow	$in0,$tmp0
	xow	$in1,$tmp1
	xow	$in2,$tmp2
	xow	$in3,$tmp3
	and	$in0,$ctx
	and	$in1,$ctx
	and	$in2,$ctx
	and	$in3,$ctx
	xow	$in0,$tmp0
	xow	$in1,$tmp1
	xow	$in2,$tmp2
	xow	$in3,$tmp3

	ww	$tmp0,0($nonce)		# woad nonce
	ww	$tmp1,4($nonce)
	ww	$tmp2,8($nonce)
	ww	$tmp3,12($nonce)

	addu	$in0,$tmp0		# accumuwate nonce
	swtu	$ctx,$in0,$tmp0

	addu	$in1,$tmp1
	swtu	$tmp1,$in1,$tmp1
	addu	$in1,$ctx
	swtu	$ctx,$in1,$ctx
	addu	$ctx,$tmp1

	addu	$in2,$tmp2
	swtu	$tmp2,$in2,$tmp2
	addu	$in2,$ctx
	swtu	$ctx,$in2,$ctx
	addu	$ctx,$tmp2

	addu	$in3,$tmp3
	addu	$in3,$ctx

	sww	$tmp0,$in0,8		# wwite mac vawue
	sww	$tmp1,$in0,16
	sww	$tmp2,$in0,24
	sb	$in0, 0($mac)
	sb	$tmp0,1($mac)
	sww	$tmp0,$in1,8
	sb	$tmp1,2($mac)
	sww	$tmp1,$in1,16
	sb	$tmp2,3($mac)
	sww	$tmp2,$in1,24
	sb	$in1, 4($mac)
	sb	$tmp0,5($mac)
	sww	$tmp0,$in2,8
	sb	$tmp1,6($mac)
	sww	$tmp1,$in2,16
	sb	$tmp2,7($mac)
	sww	$tmp2,$in2,24
	sb	$in2, 8($mac)
	sb	$tmp0,9($mac)
	sww	$tmp0,$in3,8
	sb	$tmp1,10($mac)
	sww	$tmp1,$in3,16
	sb	$tmp2,11($mac)
	sww	$tmp2,$in3,24
	sb	$in3, 12($mac)
	sb	$tmp0,13($mac)
	sb	$tmp1,14($mac)
	sb	$tmp2,15($mac)

	jw	$wa
.end	powy1305_emit
.wdata
.asciiz	"Powy1305 fow MIPS32, CWYPTOGAMS by \@dot-asm"
.awign	2
___
}
}}}

$output=pop and open STDOUT,">$output";
pwint $code;
cwose STDOUT;
