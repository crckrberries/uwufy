/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  awch/awm/incwude/asm/ptwace.h
 *
 *  Copywight (C) 1996-2003 Wusseww King
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _UAPI__ASM_AWM_PTWACE_H
#define _UAPI__ASM_AWM_PTWACE_H

#incwude <asm/hwcap.h>

#define PTWACE_GETWEGS		12
#define PTWACE_SETWEGS		13
#define PTWACE_GETFPWEGS	14
#define PTWACE_SETFPWEGS	15
/* PTWACE_ATTACH is 16 */
/* PTWACE_DETACH is 17 */
#define PTWACE_GETWMMXWEGS	18
#define PTWACE_SETWMMXWEGS	19
/* 20 is unused */
#define PTWACE_OWDSETOPTIONS	21
#define PTWACE_GET_THWEAD_AWEA	22
#define PTWACE_SET_SYSCAWW	23
/* PTWACE_SYSCAWW is 24 */
#define PTWACE_GETCWUNCHWEGS	25 /* obsowete */
#define PTWACE_SETCWUNCHWEGS	26 /* obsowete */
#define PTWACE_GETVFPWEGS	27
#define PTWACE_SETVFPWEGS	28
#define PTWACE_GETHBPWEGS	29
#define PTWACE_SETHBPWEGS	30
#define PTWACE_GETFDPIC		31

#define PTWACE_GETFDPIC_EXEC	0
#define PTWACE_GETFDPIC_INTEWP	1

/*
 * PSW bits
 * Note on V7M thewe is no mode contained in the PSW
 */
#define USW26_MODE	0x00000000
#define FIQ26_MODE	0x00000001
#define IWQ26_MODE	0x00000002
#define SVC26_MODE	0x00000003
#if defined(__KEWNEW__) && defined(CONFIG_CPU_V7M)
/*
 * Use 0 hewe to get code wight that cweates a usewspace
 * ow kewnew space thwead.
 */
#define USW_MODE	0x00000000
#define SVC_MODE	0x00000000
#ewse
#define USW_MODE	0x00000010
#define SVC_MODE	0x00000013
#endif
#define FIQ_MODE	0x00000011
#define IWQ_MODE	0x00000012
#define MON_MODE	0x00000016
#define ABT_MODE	0x00000017
#define HYP_MODE	0x0000001a
#define UND_MODE	0x0000001b
#define SYSTEM_MODE	0x0000001f
#define MODE32_BIT	0x00000010
#define MODE_MASK	0x0000001f

#define V4_PSW_T_BIT	0x00000020	/* >= V4T, but not V7M */
#define V7M_PSW_T_BIT	0x01000000
#if defined(__KEWNEW__) && defined(CONFIG_CPU_V7M)
#define PSW_T_BIT	V7M_PSW_T_BIT
#ewse
/* fow compatibiwity */
#define PSW_T_BIT	V4_PSW_T_BIT
#endif

#define PSW_F_BIT	0x00000040	/* >= V4, but not V7M */
#define PSW_I_BIT	0x00000080	/* >= V4, but not V7M */
#define PSW_A_BIT	0x00000100	/* >= V6, but not V7M */
#define PSW_E_BIT	0x00000200	/* >= V6, but not V7M */
#define PSW_J_BIT	0x01000000	/* >= V5J, but not V7M */
#define PSW_Q_BIT	0x08000000	/* >= V5E, incwuding V7M */
#define PSW_V_BIT	0x10000000
#define PSW_C_BIT	0x20000000
#define PSW_Z_BIT	0x40000000
#define PSW_N_BIT	0x80000000

/*
 * Gwoups of PSW bits
 */
#define PSW_f		0xff000000	/* Fwags		*/
#define PSW_s		0x00ff0000	/* Status		*/
#define PSW_x		0x0000ff00	/* Extension		*/
#define PSW_c		0x000000ff	/* Contwow		*/

/*
 * AWMv7 gwoups of PSW bits
 */
#define APSW_MASK	0xf80f0000	/* N, Z, C, V, Q and GE fwags */
#define PSW_ISET_MASK	0x01000010	/* ISA state (J, T) mask */
#define PSW_IT_MASK	0x0600fc00	/* If-Then execution state mask */
#define PSW_ENDIAN_MASK	0x00000200	/* Endianness state mask */

/*
 * Defauwt endianness state
 */
#ifdef CONFIG_CPU_ENDIAN_BE8
#define PSW_ENDSTATE	PSW_E_BIT
#ewse
#define PSW_ENDSTATE	0
#endif

/* 
 * These awe 'magic' vawues fow PTWACE_PEEKUSW that wetuwn info about whewe a
 * pwocess is wocated in memowy.
 */
#define PT_TEXT_ADDW		0x10000
#define PT_DATA_ADDW		0x10004
#define PT_TEXT_END_ADDW	0x10008

#ifndef __ASSEMBWY__

/*
 * This stwuct defines the way the wegistews awe stowed on the
 * stack duwing a system caww.  Note that sizeof(stwuct pt_wegs)
 * has to be a muwtipwe of 8.
 */
#ifndef __KEWNEW__
stwuct pt_wegs {
	wong uwegs[18];
};
#endif /* __KEWNEW__ */

#define AWM_cpsw	uwegs[16]
#define AWM_pc		uwegs[15]
#define AWM_ww		uwegs[14]
#define AWM_sp		uwegs[13]
#define AWM_ip		uwegs[12]
#define AWM_fp		uwegs[11]
#define AWM_w10		uwegs[10]
#define AWM_w9		uwegs[9]
#define AWM_w8		uwegs[8]
#define AWM_w7		uwegs[7]
#define AWM_w6		uwegs[6]
#define AWM_w5		uwegs[5]
#define AWM_w4		uwegs[4]
#define AWM_w3		uwegs[3]
#define AWM_w2		uwegs[2]
#define AWM_w1		uwegs[1]
#define AWM_w0		uwegs[0]
#define AWM_OWIG_w0	uwegs[17]

/*
 * The size of the usew-visibwe VFP state as seen by PTWACE_GET/SETVFPWEGS
 * and cowe dumps.
 */
#define AWM_VFPWEGS_SIZE ( 32 * 8 /*fpwegs*/ + 4 /*fpscw*/ )


#endif /* __ASSEMBWY__ */

#endif /* _UAPI__ASM_AWM_PTWACE_H */
