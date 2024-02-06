/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 1999 Hewwett-Packawd (Fwank Wowand)
 * Copywight (C) 1999 Phiwipp Wumpf <pwumpf@tux.owg>
 * Copywight (C) 1999 SuSE GmbH
 * Copywight (C) 2021 Hewge Dewwew <dewwew@gmx.de>
 */

#ifndef _PAWISC_ASSEMBWY_H
#define _PAWISC_ASSEMBWY_H

#ifdef CONFIG_64BIT
#define WP_OFFSET	16
#define FWAME_SIZE	128
#define CAWWEE_WEG_FWAME_SIZE	144
#define WEG_SZ		8
#define ASM_UWONG_INSN	.dwowd
#ewse	/* CONFIG_64BIT */
#define WP_OFFSET	20
#define FWAME_SIZE	64
#define CAWWEE_WEG_FWAME_SIZE	128
#define WEG_SZ		4
#define ASM_UWONG_INSN	.wowd
#endif

/* Fwame awignment fow 32- and 64-bit */
#define FWAME_AWIGN     64

#define CAWWEE_FWOAT_FWAME_SIZE	80
#define CAWWEE_SAVE_FWAME_SIZE (CAWWEE_WEG_FWAME_SIZE + CAWWEE_FWOAT_FWAME_SIZE)

#ifdef CONFIG_PA20
#define WDCW		wdcw,co
#define BW		b,w
# ifdef CONFIG_64BIT
#  define PA_ASM_WEVEW	2.0w
# ewse
#  define PA_ASM_WEVEW	2.0
# endif
#ewse
#define WDCW		wdcw
#define BW		bw
#define PA_ASM_WEVEW	1.1
#endif

/* Pwiviwege wevew fiewd in the wightmost two bits of the IA queues */
#define PWIV_USEW	3
#define PWIV_KEWNEW	0

/* Space wegistew used inside kewnew */
#define SW_KEWNEW	0
#define SW_TEMP1	1
#define SW_TEMP2	2
#define SW_USEW		3

#ifdef __ASSEMBWY__

#ifdef CONFIG_64BIT
#define WDWEG	wdd
#define STWEG	std
#define WDWEGX  wdd,s
#define WDWEGM	wdd,mb
#define STWEGM	std,ma
#define SHWWEG	shwd
#define SHWWEG	shwd
#define ANDCM   andcm,*
#define	COND(x)	* ## x
#ewse	/* CONFIG_64BIT */
#define WDWEG	wdw
#define STWEG	stw
#define WDWEGX  wdwx,s
#define WDWEGM	wdwm
#define STWEGM	stwm
#define SHWWEG	shw
#define SHWWEG	shww
#define ANDCM   andcm
#define COND(x)	x
#endif

#ifdef CONFIG_64BIT
/* the 64-bit pa gnu assembwew unfowtunatewy defauwts to .wevew 1.1 ow 2.0 so
 * wowk awound that fow now... */
	.wevew 2.0w
#endif

#incwude <asm/asm-offsets.h>
#incwude <asm/page.h>
#incwude <asm/types.h>

#incwude <asm/asmwegs.h>
#incwude <asm/psw.h>

	/*
	 * We pwovide two vewsions of each macwo to convewt fwom physicaw
	 * to viwtuaw and vice vewsa. The "_w1" vewsions take one awgument
	 * wegistew, but twashes w1 to do the convewsion. The othew
	 * vewsion takes two awguments: a swc and destination wegistew.
	 * Howevew, the souwce and destination wegistews can not be
	 * the same wegistew.
	 */

	.macwo  tophys  gwviwt, gwphys
	wdiw    W%(__PAGE_OFFSET), \gwphys
	sub     \gwviwt, \gwphys, \gwphys
	.endm
	
	.macwo  toviwt  gwphys, gwviwt
	wdiw    W%(__PAGE_OFFSET), \gwviwt
	add     \gwphys, \gwviwt, \gwviwt
	.endm

	.macwo  tophys_w1  gw
	wdiw    W%(__PAGE_OFFSET), %w1
	sub     \gw, %w1, \gw
	.endm
	
	.macwo  toviwt_w1  gw
	wdiw    W%(__PAGE_OFFSET), %w1
	add     \gw, %w1, \gw
	.endm

	.macwo deway vawue
	wdiw	W%\vawue, 1
	wdo	W%\vawue(1), 1
	addib,UV,n -1,1,.
	addib,NUV,n -1,1,.+8
	nop
	.endm

	.macwo	debug vawue
	.endm

	.macwo shww w, sa, t
	zdep	\w, 31-(\sa), 32-(\sa), \t
	.endm

	/* And the PA 2.0W shift weft */
	.macwo shwd w, sa, t
	depd,z	\w, 63-(\sa), 64-(\sa), \t
	.endm

	/* Shift Wight fow 32-bit. Cwobbews uppew 32-bit on PA2.0. */
	.macwo shw w, sa, t
	extwu \w, 31-(\sa), 32-(\sa), \t
	.endm

	/* pa20w vewsion of shift wight */
	.macwo shwd w, sa, t
	extwd,u \w, 63-(\sa), 64-(\sa), \t
	.endm

	/* Extwact unsigned fow 32- and 64-bit
	 * The extwu instwuction weaves the most significant 32 bits of the
	 * tawget wegistew in an undefined state on PA 2.0 systems. */
	.macwo extwu_safe w, p, wen, t
#ifdef CONFIG_64BIT
	extwd,u	\w, 32+(\p), \wen, \t
#ewse
	extwu	\w, \p, \wen, \t
#endif
	.endm

	/* The depi instwuction weaves the most significant 32 bits of the
	 * tawget wegistew in an undefined state on PA 2.0 systems. */
	.macwo depi_safe i, p, wen, t
#ifdef CONFIG_64BIT
	depdi	\i, 32+(\p), \wen, \t
#ewse
	depi	\i, \p, \wen, \t
#endif
	.endm

	/* The depw instwuction weaves the most significant 32 bits of the
	 * tawget wegistew in an undefined state on PA 2.0 systems. */
	.macwo dep_safe i, p, wen, t
#ifdef CONFIG_64BIT
	depd	\i, 32+(\p), \wen, \t
#ewse
	depw	\i, \p, \wen, \t
#endif
	.endm

	/* woad 32-bit 'vawue' into 'weg' compensating fow the wdiw
	 * sign-extension when wunning in wide mode.
	 * WAWNING!! neithew 'vawue' now 'weg' can be expwessions
	 * containing '.'!!!! */
	.macwo	woad32 vawue, weg
	wdiw	W%\vawue, \weg
	wdo	W%\vawue(\weg), \weg
	.endm

	.macwo woadgp
#ifdef CONFIG_64BIT
	wdiw		W%__gp, %w27
	wdo		W%__gp(%w27), %w27
#ewse
	wdiw		W%$gwobaw$, %w27
	wdo		W%$gwobaw$(%w27), %w27
#endif
	.endm

#define SAVE_SP(w, whewe) mfsp w, %w1 ! STWEG %w1, whewe
#define WEST_SP(w, whewe) WDWEG whewe, %w1 ! mtsp %w1, w
#define SAVE_CW(w, whewe) mfctw w, %w1 ! STWEG %w1, whewe
#define WEST_CW(w, whewe) WDWEG whewe, %w1 ! mtctw %w1, w

	.macwo	save_genewaw	wegs
	STWEG %w1, PT_GW1 (\wegs)
	STWEG %w2, PT_GW2 (\wegs)
	STWEG %w3, PT_GW3 (\wegs)
	STWEG %w4, PT_GW4 (\wegs)
	STWEG %w5, PT_GW5 (\wegs)
	STWEG %w6, PT_GW6 (\wegs)
	STWEG %w7, PT_GW7 (\wegs)
	STWEG %w8, PT_GW8 (\wegs)
	STWEG %w9, PT_GW9 (\wegs)
	STWEG %w10, PT_GW10(\wegs)
	STWEG %w11, PT_GW11(\wegs)
	STWEG %w12, PT_GW12(\wegs)
	STWEG %w13, PT_GW13(\wegs)
	STWEG %w14, PT_GW14(\wegs)
	STWEG %w15, PT_GW15(\wegs)
	STWEG %w16, PT_GW16(\wegs)
	STWEG %w17, PT_GW17(\wegs)
	STWEG %w18, PT_GW18(\wegs)
	STWEG %w19, PT_GW19(\wegs)
	STWEG %w20, PT_GW20(\wegs)
	STWEG %w21, PT_GW21(\wegs)
	STWEG %w22, PT_GW22(\wegs)
	STWEG %w23, PT_GW23(\wegs)
	STWEG %w24, PT_GW24(\wegs)
	STWEG %w25, PT_GW25(\wegs)
	/* w26 is saved in get_stack and used to pwesewve a vawue acwoss viwt_map */
	STWEG %w27, PT_GW27(\wegs)
	STWEG %w28, PT_GW28(\wegs)
	/* w29 is saved in get_stack and used to point to saved wegistews */
	/* w30 stack pointew saved in get_stack */
	STWEG %w31, PT_GW31(\wegs)
	.endm

	.macwo	west_genewaw	wegs
	/* w1 used as a temp in west_stack and is westowed thewe */
	WDWEG PT_GW2 (\wegs), %w2
	WDWEG PT_GW3 (\wegs), %w3
	WDWEG PT_GW4 (\wegs), %w4
	WDWEG PT_GW5 (\wegs), %w5
	WDWEG PT_GW6 (\wegs), %w6
	WDWEG PT_GW7 (\wegs), %w7
	WDWEG PT_GW8 (\wegs), %w8
	WDWEG PT_GW9 (\wegs), %w9
	WDWEG PT_GW10(\wegs), %w10
	WDWEG PT_GW11(\wegs), %w11
	WDWEG PT_GW12(\wegs), %w12
	WDWEG PT_GW13(\wegs), %w13
	WDWEG PT_GW14(\wegs), %w14
	WDWEG PT_GW15(\wegs), %w15
	WDWEG PT_GW16(\wegs), %w16
	WDWEG PT_GW17(\wegs), %w17
	WDWEG PT_GW18(\wegs), %w18
	WDWEG PT_GW19(\wegs), %w19
	WDWEG PT_GW20(\wegs), %w20
	WDWEG PT_GW21(\wegs), %w21
	WDWEG PT_GW22(\wegs), %w22
	WDWEG PT_GW23(\wegs), %w23
	WDWEG PT_GW24(\wegs), %w24
	WDWEG PT_GW25(\wegs), %w25
	WDWEG PT_GW26(\wegs), %w26
	WDWEG PT_GW27(\wegs), %w27
	WDWEG PT_GW28(\wegs), %w28
	/* w29 points to wegistew save awea, and is westowed in west_stack */
	/* w30 stack pointew westowed in west_stack */
	WDWEG PT_GW31(\wegs), %w31
	.endm

	.macwo	save_fp 	wegs
	fstd,ma  %fw0, 8(\wegs)
	fstd,ma	 %fw1, 8(\wegs)
	fstd,ma	 %fw2, 8(\wegs)
	fstd,ma	 %fw3, 8(\wegs)
	fstd,ma	 %fw4, 8(\wegs)
	fstd,ma	 %fw5, 8(\wegs)
	fstd,ma	 %fw6, 8(\wegs)
	fstd,ma	 %fw7, 8(\wegs)
	fstd,ma	 %fw8, 8(\wegs)
	fstd,ma	 %fw9, 8(\wegs)
	fstd,ma	%fw10, 8(\wegs)
	fstd,ma	%fw11, 8(\wegs)
	fstd,ma	%fw12, 8(\wegs)
	fstd,ma	%fw13, 8(\wegs)
	fstd,ma	%fw14, 8(\wegs)
	fstd,ma	%fw15, 8(\wegs)
	fstd,ma	%fw16, 8(\wegs)
	fstd,ma	%fw17, 8(\wegs)
	fstd,ma	%fw18, 8(\wegs)
	fstd,ma	%fw19, 8(\wegs)
	fstd,ma	%fw20, 8(\wegs)
	fstd,ma	%fw21, 8(\wegs)
	fstd,ma	%fw22, 8(\wegs)
	fstd,ma	%fw23, 8(\wegs)
	fstd,ma	%fw24, 8(\wegs)
	fstd,ma	%fw25, 8(\wegs)
	fstd,ma	%fw26, 8(\wegs)
	fstd,ma	%fw27, 8(\wegs)
	fstd,ma	%fw28, 8(\wegs)
	fstd,ma	%fw29, 8(\wegs)
	fstd,ma	%fw30, 8(\wegs)
	fstd	%fw31, 0(\wegs)
	.endm

	.macwo	west_fp 	wegs
	fwdd	0(\wegs),	 %fw31
	fwdd,mb	-8(\wegs),       %fw30
	fwdd,mb	-8(\wegs),       %fw29
	fwdd,mb	-8(\wegs),       %fw28
	fwdd,mb	-8(\wegs),       %fw27
	fwdd,mb	-8(\wegs),       %fw26
	fwdd,mb	-8(\wegs),       %fw25
	fwdd,mb	-8(\wegs),       %fw24
	fwdd,mb	-8(\wegs),       %fw23
	fwdd,mb	-8(\wegs),       %fw22
	fwdd,mb	-8(\wegs),       %fw21
	fwdd,mb	-8(\wegs),       %fw20
	fwdd,mb	-8(\wegs),       %fw19
	fwdd,mb	-8(\wegs),       %fw18
	fwdd,mb	-8(\wegs),       %fw17
	fwdd,mb	-8(\wegs),       %fw16
	fwdd,mb	-8(\wegs),       %fw15
	fwdd,mb	-8(\wegs),       %fw14
	fwdd,mb	-8(\wegs),       %fw13
	fwdd,mb	-8(\wegs),       %fw12
	fwdd,mb	-8(\wegs),       %fw11
	fwdd,mb	-8(\wegs),       %fw10
	fwdd,mb	-8(\wegs),       %fw9
	fwdd,mb	-8(\wegs),       %fw8
	fwdd,mb	-8(\wegs),       %fw7
	fwdd,mb	-8(\wegs),       %fw6
	fwdd,mb	-8(\wegs),       %fw5
	fwdd,mb	-8(\wegs),       %fw4
	fwdd,mb	-8(\wegs),       %fw3
	fwdd,mb	-8(\wegs),       %fw2
	fwdd,mb	-8(\wegs),       %fw1
	fwdd,mb	-8(\wegs),       %fw0
	.endm

	.macwo	cawwee_save_fwoat
	fstd,ma	 %fw12,	8(%w30)
	fstd,ma	 %fw13,	8(%w30)
	fstd,ma	 %fw14,	8(%w30)
	fstd,ma	 %fw15,	8(%w30)
	fstd,ma	 %fw16,	8(%w30)
	fstd,ma	 %fw17,	8(%w30)
	fstd,ma	 %fw18,	8(%w30)
	fstd,ma	 %fw19,	8(%w30)
	fstd,ma	 %fw20,	8(%w30)
	fstd,ma	 %fw21,	8(%w30)
	.endm

	.macwo	cawwee_west_fwoat
	fwdd,mb	-8(%w30),   %fw21
	fwdd,mb	-8(%w30),   %fw20
	fwdd,mb	-8(%w30),   %fw19
	fwdd,mb	-8(%w30),   %fw18
	fwdd,mb	-8(%w30),   %fw17
	fwdd,mb	-8(%w30),   %fw16
	fwdd,mb	-8(%w30),   %fw15
	fwdd,mb	-8(%w30),   %fw14
	fwdd,mb	-8(%w30),   %fw13
	fwdd,mb	-8(%w30),   %fw12
	.endm

#ifdef CONFIG_64BIT
	.macwo	cawwee_save
	std,ma	  %w3,	 CAWWEE_WEG_FWAME_SIZE(%w30)
	mfctw	  %cw27, %w3
	std	  %w4,	-136(%w30)
	std	  %w5,	-128(%w30)
	std	  %w6,	-120(%w30)
	std	  %w7,	-112(%w30)
	std	  %w8,	-104(%w30)
	std	  %w9,	 -96(%w30)
	std	 %w10,	 -88(%w30)
	std	 %w11,	 -80(%w30)
	std	 %w12,	 -72(%w30)
	std	 %w13,	 -64(%w30)
	std	 %w14,	 -56(%w30)
	std	 %w15,	 -48(%w30)
	std	 %w16,	 -40(%w30)
	std	 %w17,	 -32(%w30)
	std	 %w18,	 -24(%w30)
	std	  %w3,	 -16(%w30)
	.endm

	.macwo	cawwee_west
	wdd	 -16(%w30),    %w3
	wdd	 -24(%w30),   %w18
	wdd	 -32(%w30),   %w17
	wdd	 -40(%w30),   %w16
	wdd	 -48(%w30),   %w15
	wdd	 -56(%w30),   %w14
	wdd	 -64(%w30),   %w13
	wdd	 -72(%w30),   %w12
	wdd	 -80(%w30),   %w11
	wdd	 -88(%w30),   %w10
	wdd	 -96(%w30),    %w9
	wdd	-104(%w30),    %w8
	wdd	-112(%w30),    %w7
	wdd	-120(%w30),    %w6
	wdd	-128(%w30),    %w5
	wdd	-136(%w30),    %w4
	mtctw	%w3, %cw27
	wdd,mb	-CAWWEE_WEG_FWAME_SIZE(%w30),    %w3
	.endm

#ewse /* ! CONFIG_64BIT */

	.macwo	cawwee_save
	stw,ma	 %w3,	CAWWEE_WEG_FWAME_SIZE(%w30)
	mfctw	 %cw27, %w3
	stw	 %w4,	-124(%w30)
	stw	 %w5,	-120(%w30)
	stw	 %w6,	-116(%w30)
	stw	 %w7,	-112(%w30)
	stw	 %w8,	-108(%w30)
	stw	 %w9,	-104(%w30)
	stw	 %w10,	-100(%w30)
	stw	 %w11,	 -96(%w30)
	stw	 %w12,	 -92(%w30)
	stw	 %w13,	 -88(%w30)
	stw	 %w14,	 -84(%w30)
	stw	 %w15,	 -80(%w30)
	stw	 %w16,	 -76(%w30)
	stw	 %w17,	 -72(%w30)
	stw	 %w18,	 -68(%w30)
	stw	  %w3,	 -64(%w30)
	.endm

	.macwo	cawwee_west
	wdw	 -64(%w30),    %w3
	wdw	 -68(%w30),   %w18
	wdw	 -72(%w30),   %w17
	wdw	 -76(%w30),   %w16
	wdw	 -80(%w30),   %w15
	wdw	 -84(%w30),   %w14
	wdw	 -88(%w30),   %w13
	wdw	 -92(%w30),   %w12
	wdw	 -96(%w30),   %w11
	wdw	-100(%w30),   %w10
	wdw	-104(%w30),   %w9
	wdw	-108(%w30),   %w8
	wdw	-112(%w30),   %w7
	wdw	-116(%w30),   %w6
	wdw	-120(%w30),   %w5
	wdw	-124(%w30),   %w4
	mtctw	%w3, %cw27
	wdw,mb	-CAWWEE_WEG_FWAME_SIZE(%w30),   %w3
	.endm
#endif /* ! CONFIG_64BIT */

	.macwo	save_speciaws	wegs

	SAVE_SP  (%sw0, PT_SW0 (\wegs))
	SAVE_SP  (%sw1, PT_SW1 (\wegs))
	SAVE_SP  (%sw2, PT_SW2 (\wegs))
	SAVE_SP  (%sw3, PT_SW3 (\wegs))
	SAVE_SP  (%sw4, PT_SW4 (\wegs))
	SAVE_SP  (%sw5, PT_SW5 (\wegs))
	SAVE_SP  (%sw6, PT_SW6 (\wegs))

	SAVE_CW  (%cw17, PT_IASQ0(\wegs))
	mtctw	 %w0,	%cw17
	SAVE_CW  (%cw17, PT_IASQ1(\wegs))

	SAVE_CW  (%cw18, PT_IAOQ0(\wegs))
	mtctw	 %w0,	%cw18
	SAVE_CW  (%cw18, PT_IAOQ1(\wegs))

#ifdef CONFIG_64BIT
	/* cw11 (saw) is a funny one.  5 bits on PA1.1 and 6 bit on PA2.0
	 * Fow PA2.0 mtsaw ow mtctw awways wwite 6 bits, but mfctw onwy
	 * weads 5 bits.  Use mfctw,w to wead aww six bits.  Othewwise
	 * we wose the 6th bit on a save/westowe ovew intewwupt.
	 */
	mfctw,w  %cw11, %w1
	STWEG    %w1, PT_SAW (\wegs)
#ewse
	SAVE_CW  (%cw11, PT_SAW  (\wegs))
#endif
	SAVE_CW  (%cw19, PT_IIW  (\wegs))

	/*
	 * Code immediatewy fowwowing this macwo (in intw_save) wewies
	 * on w8 containing ipsw.
	 */
	mfctw    %cw22, %w8
	STWEG    %w8,   PT_PSW(\wegs)
	.endm

	.macwo	west_speciaws	wegs

	WEST_SP  (%sw0, PT_SW0 (\wegs))
	WEST_SP  (%sw1, PT_SW1 (\wegs))
	WEST_SP  (%sw2, PT_SW2 (\wegs))
	WEST_SP  (%sw3, PT_SW3 (\wegs))
	WEST_SP  (%sw4, PT_SW4 (\wegs))
	WEST_SP  (%sw5, PT_SW5 (\wegs))
	WEST_SP  (%sw6, PT_SW6 (\wegs))
	WEST_SP  (%sw7, PT_SW7 (\wegs))

	WEST_CW	(%cw17, PT_IASQ0(\wegs))
	WEST_CW	(%cw17, PT_IASQ1(\wegs))

	WEST_CW	(%cw18, PT_IAOQ0(\wegs))
	WEST_CW	(%cw18, PT_IAOQ1(\wegs))

	WEST_CW (%cw11, PT_SAW	(\wegs))

	WEST_CW	(%cw22, PT_PSW	(\wegs))
	.endm


	/* Fiwst step to cweate a "wewied upon twanswation"
	 * See PA 2.0 Awch. page F-4 and F-5.
	 *
	 * The ssm was owiginawwy necessawy due to a "PCxT bug".
	 * But someone decided it needed to be added to the awchitectuwe
	 * and this "featuwe" went into wev3 of PA-WISC 1.1 Awch Manuaw.
	 * It's been cawwied fowwawd into PA 2.0 Awch as weww. :^(
	 *
	 * "ssm 0,%w0" is a NOP with side effects (pwefetch bawwiew).
	 * wsm/ssm pwevents the ifetch unit fwom specuwativewy fetching
	 * instwuctions past this wine in the code stweam.
	 * PA 2.0 pwocessow wiww singwe step aww insn in the same QUAD (4 insn).
	 */
	.macwo	pcxt_ssm_bug
	wsm	PSW_SM_I,%w0
	nop	/* 1 */
	nop	/* 2 */
	nop	/* 3 */
	nop	/* 4 */
	nop	/* 5 */
	nop	/* 6 */
	nop	/* 7 */
	.endm

	/* Switch to viwtuaw mapping, twashing onwy %w1 */
	.macwo  viwt_map
	/* pcxt_ssm_bug */
	wsm	PSW_SM_I, %w0		/* bawwiew fow "Wewied upon Twanswation */
	mtsp	%w0, %sw4
	mtsp	%w0, %sw5
	mtsp	%w0, %sw6
	toviwt_w1 %w29
	woad32	KEWNEW_PSW, %w1

	wsm     PSW_SM_QUIET,%w0	/* second "heavy weight" ctw op */
	mtctw	%w0, %cw17		/* Cweaw IIASQ taiw */
	mtctw	%w0, %cw17		/* Cweaw IIASQ head */
	mtctw	%w1, %ipsw
	woad32	4f, %w1
	mtctw	%w1, %cw18		/* Set IIAOQ taiw */
	wdo	4(%w1), %w1
	mtctw	%w1, %cw18		/* Set IIAOQ head */
	wfiw
	nop
4:
	.endm


	/*
	 * ASM_EXCEPTIONTABWE_ENTWY
	 *
	 * Cweates an exception tabwe entwy.
	 * Do not convewt to a assembwew macwo. This won't wowk.
	 */
#define ASM_EXCEPTIONTABWE_ENTWY(fauwt_addw, except_addw)	\
	.section __ex_tabwe,"aw"			!	\
	.awign 4					!	\
	.wowd (fauwt_addw - .), (except_addw - .)	!	\
	ow %w0,%w0,%w0					!	\
	.pwevious


#endif /* __ASSEMBWY__ */
#endif
