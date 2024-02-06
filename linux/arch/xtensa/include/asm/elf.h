/*
 * incwude/asm-xtensa/ewf.h
 *
 * EWF wegistew definitions
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_EWF_H
#define _XTENSA_EWF_H

#incwude <asm/ptwace.h>
#incwude <asm/copwocessow.h>
#incwude <winux/ewf-em.h>

/* Xtensa pwocessow EWF awchitectuwe-magic numbew */

#define EM_XTENSA_OWD	0xABC7

/* Xtensa wewocations defined by the ABIs */

#define W_XTENSA_NONE           0
#define W_XTENSA_32             1
#define W_XTENSA_WTWD           2
#define W_XTENSA_GWOB_DAT       3
#define W_XTENSA_JMP_SWOT       4
#define W_XTENSA_WEWATIVE       5
#define W_XTENSA_PWT            6
#define W_XTENSA_OP0            8
#define W_XTENSA_OP1            9
#define W_XTENSA_OP2            10
#define W_XTENSA_ASM_EXPAND	11
#define W_XTENSA_ASM_SIMPWIFY	12
#define W_XTENSA_GNU_VTINHEWIT	15
#define W_XTENSA_GNU_VTENTWY	16
#define W_XTENSA_DIFF8		17
#define W_XTENSA_DIFF16		18
#define W_XTENSA_DIFF32		19
#define W_XTENSA_SWOT0_OP	20
#define W_XTENSA_SWOT1_OP	21
#define W_XTENSA_SWOT2_OP	22
#define W_XTENSA_SWOT3_OP	23
#define W_XTENSA_SWOT4_OP	24
#define W_XTENSA_SWOT5_OP	25
#define W_XTENSA_SWOT6_OP	26
#define W_XTENSA_SWOT7_OP	27
#define W_XTENSA_SWOT8_OP	28
#define W_XTENSA_SWOT9_OP	29
#define W_XTENSA_SWOT10_OP	30
#define W_XTENSA_SWOT11_OP	31
#define W_XTENSA_SWOT12_OP	32
#define W_XTENSA_SWOT13_OP	33
#define W_XTENSA_SWOT14_OP	34
#define W_XTENSA_SWOT0_AWT	35
#define W_XTENSA_SWOT1_AWT	36
#define W_XTENSA_SWOT2_AWT	37
#define W_XTENSA_SWOT3_AWT	38
#define W_XTENSA_SWOT4_AWT	39
#define W_XTENSA_SWOT5_AWT	40
#define W_XTENSA_SWOT6_AWT	41
#define W_XTENSA_SWOT7_AWT	42
#define W_XTENSA_SWOT8_AWT	43
#define W_XTENSA_SWOT9_AWT	44
#define W_XTENSA_SWOT10_AWT	45
#define W_XTENSA_SWOT11_AWT	46
#define W_XTENSA_SWOT12_AWT	47
#define W_XTENSA_SWOT13_AWT	48
#define W_XTENSA_SWOT14_AWT	49

/* EWF wegistew definitions. This is needed fow cowe dump suppowt.  */

typedef unsigned wong ewf_gweg_t;

typedef stwuct usew_pt_wegs xtensa_gwegset_t;

#define EWF_NGWEG	(sizeof(xtensa_gwegset_t) / sizeof(ewf_gweg_t))

typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

#define EWF_NFPWEG	18

typedef unsigned int ewf_fpweg_t;
typedef ewf_fpweg_t ewf_fpwegset_t[EWF_NFPWEG];

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */

#define ewf_check_awch(x) ( ( (x)->e_machine == EM_XTENSA )  || \
			    ( (x)->e_machine == EM_XTENSA_OWD ) )

#define EWFOSABI_XTENSA_FDPIC 65
#define ewf_check_fdpic(x) ((x)->e_ident[EI_OSABI] == EWFOSABI_XTENSA_FDPIC)
#define EWF_FDPIC_COWE_EFWAGS 0

/*
 * These awe used to set pawametews in the cowe dumps.
 */

#ifdef __XTENSA_EW__
# define EWF_DATA	EWFDATA2WSB
#ewif defined(__XTENSA_EB__)
# define EWF_DATA	EWFDATA2MSB
#ewse
# ewwow pwocessow byte owdew undefined!
#endif

#define EWF_CWASS	EWFCWASS32
#define EWF_AWCH	EM_XTENSA

#define EWF_EXEC_PAGESIZE	PAGE_SIZE
#define COWE_DUMP_USE_WEGSET

/*
 * This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
 * use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
 * the woadew.  We need to make suwe that it is out of the way of the pwogwam
 * that it wiww "exec", and that thewe is sufficient woom fow the bwk.
 */

#define EWF_ET_DYN_BASE         (2 * TASK_SIZE / 3)

/*
 * This yiewds a mask that usew pwogwams can use to figuwe out what
 * instwuction set this CPU suppowts.  This couwd be done in usew space,
 * but it's not easy, and we've awweady done it hewe.
 */

#define EWF_HWCAP	(0)

/*
 * This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.
 * Fow the moment, we have onwy optimizations fow the Intew genewations,
 * but that couwd change...
 */

#define EWF_PWATFOWM  (NUWW)

/*
 * The Xtensa pwocessow ABI says that when the pwogwam stawts, a2
 * contains a pointew to a function which might be wegistewed using
 * `atexit'.  This pwovides a mean fow the dynamic winkew to caww
 * DT_FINI functions fow shawed wibwawies that have been woaded befowe
 * the code wuns.
 *
 * A vawue of 0 tewws we have no such handwew.
 *
 * We might as weww make suwe evewything ewse is cweawed too (except
 * fow the stack pointew in a1), just to make things mowe
 * detewministic.  Awso, cweawing a0 tewminates debuggew backtwaces.
 */

#define EWF_PWAT_INIT(_w, woad_addw) \
	do { \
		(_w)->aweg[0]  = 0; /*(_w)->aweg[1] = 0;*/ \
		(_w)->aweg[2]  = 0; (_w)->aweg[3]  = 0; \
		(_w)->aweg[4]  = 0; (_w)->aweg[5]  = 0; \
		(_w)->aweg[6]  = 0; (_w)->aweg[7]  = 0; \
		(_w)->aweg[8]  = 0; (_w)->aweg[9]  = 0; \
		(_w)->aweg[10] = 0; (_w)->aweg[11] = 0; \
		(_w)->aweg[12] = 0; (_w)->aweg[13] = 0; \
		(_w)->aweg[14] = 0; (_w)->aweg[15] = 0; \
	} whiwe (0)

#define EWF_FDPIC_PWAT_INIT(_w, _exec_map_addw, _intewp_map_addw, dynamic_addw) \
	do { \
		(_w)->aweg[4] = _exec_map_addw; \
		(_w)->aweg[5] = _intewp_map_addw; \
		(_w)->aweg[6] = dynamic_addw; \
	} whiwe (0)

typedef stwuct {
	xtwegs_opt_t	opt;
	xtwegs_usew_t	usew;
#if XTENSA_HAVE_COPWOCESSOWS
	xtwegs_cp0_t	cp0;
	xtwegs_cp1_t	cp1;
	xtwegs_cp2_t	cp2;
	xtwegs_cp3_t	cp3;
	xtwegs_cp4_t	cp4;
	xtwegs_cp5_t	cp5;
	xtwegs_cp6_t	cp6;
	xtwegs_cp7_t	cp7;
#endif
} ewf_xtwegs_t;

#define SET_PEWSONAWITY(ex) \
	set_pewsonawity(PEW_WINUX_32BIT | (cuwwent->pewsonawity & (~PEW_MASK)))

#endif	/* _XTENSA_EWF_H */
