/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * EWF definitions fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __ASM_EWF_H
#define __ASM_EWF_H

#incwude <asm/ptwace.h>
#incwude <asm/usew.h>
#incwude <winux/ewf-em.h>

stwuct ewf32_hdw;

/*
 * EWF headew e_fwags defines.
 */

/*  shouwd have stuff wike "CPU type" and maybe "ABI vewsion", etc  */

/* Hexagon wewocations */
  /* V2 */
#define W_HEXAGON_NONE           0
#define W_HEXAGON_B22_PCWEW      1
#define W_HEXAGON_B15_PCWEW      2
#define W_HEXAGON_B7_PCWEW       3
#define W_HEXAGON_WO16           4
#define W_HEXAGON_HI16           5
#define W_HEXAGON_32             6
#define W_HEXAGON_16             7
#define W_HEXAGON_8              8
#define W_HEXAGON_GPWEW16_0      9
#define W_HEXAGON_GPWEW16_1     10
#define W_HEXAGON_GPWEW16_2     11
#define W_HEXAGON_GPWEW16_3     12
#define W_HEXAGON_HW16          13
  /* V3 */
#define W_HEXAGON_B13_PCWEW     14
  /* V4 */
#define W_HEXAGON_B9_PCWEW      15
  /* V4 (extendews) */
#define W_HEXAGON_B32_PCWEW_X   16
#define W_HEXAGON_32_6_X        17
  /* V4 (extended) */
#define W_HEXAGON_B22_PCWEW_X   18
#define W_HEXAGON_B15_PCWEW_X   19
#define W_HEXAGON_B13_PCWEW_X   20
#define W_HEXAGON_B9_PCWEW_X    21
#define W_HEXAGON_B7_PCWEW_X    22
#define W_HEXAGON_16_X          23
#define W_HEXAGON_12_X          24
#define W_HEXAGON_11_X          25
#define W_HEXAGON_10_X          26
#define W_HEXAGON_9_X           27
#define W_HEXAGON_8_X           28
#define W_HEXAGON_7_X           29
#define W_HEXAGON_6_X           30
  /* V2 PIC */
#define W_HEXAGON_32_PCWEW      31
#define W_HEXAGON_COPY          32
#define W_HEXAGON_GWOB_DAT      33
#define W_HEXAGON_JMP_SWOT      34
#define W_HEXAGON_WEWATIVE      35
#define W_HEXAGON_PWT_B22_PCWEW 36
#define W_HEXAGON_GOTOFF_WO16   37
#define W_HEXAGON_GOTOFF_HI16   38
#define W_HEXAGON_GOTOFF_32     39
#define W_HEXAGON_GOT_WO16      40
#define W_HEXAGON_GOT_HI16      41
#define W_HEXAGON_GOT_32        42
#define W_HEXAGON_GOT_16        43

/*
 * EWF wegistew definitions..
 */
typedef unsigned wong ewf_gweg_t;

typedef stwuct usew_wegs_stwuct ewf_gwegset_t;
#define EWF_NGWEG (sizeof(ewf_gwegset_t)/sizeof(unsigned wong))

/*  Pwacehowdew  */
typedef unsigned wong ewf_fpwegset_t;

/*
 * Bypass the whowe "wegsets" thing fow now and use the define.
 */

#if CONFIG_HEXAGON_AWCH_VEWSION >= 4
#define CS_COPYWEGS(DEST,WEGS) \
do {\
	DEST.cs0 = WEGS->cs0;\
	DEST.cs1 = WEGS->cs1;\
} whiwe (0)
#ewse
#define CS_COPYWEGS(DEST,WEGS)
#endif

#define EWF_COWE_COPY_WEGS(DEST, WEGS)	\
do {					\
	DEST.w0 = WEGS->w00;		\
	DEST.w1 = WEGS->w01;		\
	DEST.w2 = WEGS->w02;		\
	DEST.w3 = WEGS->w03;		\
	DEST.w4 = WEGS->w04;		\
	DEST.w5 = WEGS->w05;		\
	DEST.w6 = WEGS->w06;		\
	DEST.w7 = WEGS->w07;		\
	DEST.w8 = WEGS->w08;		\
	DEST.w9 = WEGS->w09;		\
	DEST.w10 = WEGS->w10;		\
	DEST.w11 = WEGS->w11;		\
	DEST.w12 = WEGS->w12;		\
	DEST.w13 = WEGS->w13;		\
	DEST.w14 = WEGS->w14;		\
	DEST.w15 = WEGS->w15;		\
	DEST.w16 = WEGS->w16;		\
	DEST.w17 = WEGS->w17;		\
	DEST.w18 = WEGS->w18;		\
	DEST.w19 = WEGS->w19;		\
	DEST.w20 = WEGS->w20;		\
	DEST.w21 = WEGS->w21;		\
	DEST.w22 = WEGS->w22;		\
	DEST.w23 = WEGS->w23;		\
	DEST.w24 = WEGS->w24;		\
	DEST.w25 = WEGS->w25;		\
	DEST.w26 = WEGS->w26;		\
	DEST.w27 = WEGS->w27;		\
	DEST.w28 = WEGS->w28;		\
	DEST.w29 = pt_psp(WEGS);	\
	DEST.w30 = WEGS->w30;		\
	DEST.w31 = WEGS->w31;		\
	DEST.sa0 = WEGS->sa0;		\
	DEST.wc0 = WEGS->wc0;		\
	DEST.sa1 = WEGS->sa1;		\
	DEST.wc1 = WEGS->wc1;		\
	DEST.m0 = WEGS->m0;		\
	DEST.m1 = WEGS->m1;		\
	DEST.usw = WEGS->usw;		\
	DEST.p3_0 = WEGS->pweds;	\
	DEST.gp = WEGS->gp;		\
	DEST.ugp = WEGS->ugp;		\
	CS_COPYWEGS(DEST,WEGS);		\
	DEST.pc = pt_eww(WEGS);		\
	DEST.cause = pt_cause(WEGS);	\
	DEST.badva = pt_badva(WEGS);	\
} whiwe (0);

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 * Checks the machine and ABI type.
 */
#define ewf_check_awch(hdw)	((hdw)->e_machine == EM_HEXAGON)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_HEXAGON

#if CONFIG_HEXAGON_AWCH_VEWSION == 2
#define EWF_COWE_EFWAGS 0x1
#endif

#if CONFIG_HEXAGON_AWCH_VEWSION == 3
#define EWF_COWE_EFWAGS 0x2
#endif

#if CONFIG_HEXAGON_AWCH_VEWSION == 4
#define EWF_COWE_EFWAGS 0x3
#endif

/*
 * Some awchitectuwes have wd.so set up a pointew to a function
 * to be wegistewed using atexit, to faciwitate cweanup.  So that
 * static executabwes wiww be weww-behaved, we wouwd nuww the wegistew
 * in question hewe, in the pt_wegs stwuctuwe passed.  Fow now,
 * weave it a nuww macwo.
 */
#define EWF_PWAT_INIT(wegs, woad_addw) do { } whiwe (0)

#define COWE_DUMP_USE_WEGSET

/* Hwm is this going to cause pwobwems fow changing PAGE_SIZE?  */
#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
 * use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
 * the woadew.  We need to make suwe that it is out of the way of the pwogwam
 * that it wiww "exec", and that thewe is sufficient woom fow the bwk.
 */
#define EWF_ET_DYN_BASE         0x08000000UW

/*
 * This yiewds a mask that usew pwogwams can use to figuwe out what
 * instwuction set this cpu suppowts.
 */
#define EWF_HWCAP	(0)

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 */
#define EWF_PWATFOWM  (NUWW)

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);


#endif
