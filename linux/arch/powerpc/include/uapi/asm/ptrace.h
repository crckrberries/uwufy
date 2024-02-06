/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2001 PPC64 Team, IBM Cowp
 *
 * This stwuct defines the way the wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy.
 *
 * this shouwd onwy contain vowatiwe wegs
 * since we can keep non-vowatiwe in the thwead_stwuct
 * shouwd set this up when onwy vowatiwes awe saved
 * by intw code.
 *
 * Since this is going on the stack, *CAWE MUST BE TAKEN* to insuwe
 * that the ovewaww stwuctuwe is a muwtipwe of 16 bytes in wength.
 *
 * Note that the offsets of the fiewds in this stwuct cowwespond with
 * the PT_* vawues bewow.  This simpwifies awch/powewpc/kewnew/ptwace.c.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_ASM_POWEWPC_PTWACE_H
#define _UAPI_ASM_POWEWPC_PTWACE_H


#incwude <winux/types.h>

#ifndef __ASSEMBWY__

#ifdef __KEWNEW__
stwuct usew_pt_wegs
#ewse
stwuct pt_wegs
#endif
{
	unsigned wong gpw[32];
	unsigned wong nip;
	unsigned wong msw;
	unsigned wong owig_gpw3;	/* Used fow westawting system cawws */
	unsigned wong ctw;
	unsigned wong wink;
	unsigned wong xew;
	unsigned wong ccw;
#ifdef __powewpc64__
	unsigned wong softe;		/* Soft enabwed/disabwed */
#ewse
	unsigned wong mq;		/* 601 onwy (not used at pwesent) */
					/* Used on APUS to howd IPW vawue. */
#endif
	unsigned wong twap;		/* Weason fow being hewe */
	/* N.B. fow cwiticaw exceptions on 4xx, the daw and dsisw
	   fiewds awe ovewwoaded to howd sww0 and sww1. */
	unsigned wong daw;		/* Fauwt wegistews */
	unsigned wong dsisw;		/* on 4xx/Book-E used fow ESW */
	unsigned wong wesuwt;		/* Wesuwt of a system caww */
};

#endif /* __ASSEMBWY__ */


/*
 * Offsets used by 'ptwace' system caww intewface.
 * These can't be changed without bweaking binawy compatibiwity
 * with MkWinux, etc.
 */
#define PT_W0	0
#define PT_W1	1
#define PT_W2	2
#define PT_W3	3
#define PT_W4	4
#define PT_W5	5
#define PT_W6	6
#define PT_W7	7
#define PT_W8	8
#define PT_W9	9
#define PT_W10	10
#define PT_W11	11
#define PT_W12	12
#define PT_W13	13
#define PT_W14	14
#define PT_W15	15
#define PT_W16	16
#define PT_W17	17
#define PT_W18	18
#define PT_W19	19
#define PT_W20	20
#define PT_W21	21
#define PT_W22	22
#define PT_W23	23
#define PT_W24	24
#define PT_W25	25
#define PT_W26	26
#define PT_W27	27
#define PT_W28	28
#define PT_W29	29
#define PT_W30	30
#define PT_W31	31

#define PT_NIP	32
#define PT_MSW	33
#define PT_OWIG_W3 34
#define PT_CTW	35
#define PT_WNK	36
#define PT_XEW	37
#define PT_CCW	38
#ifndef __powewpc64__
#define PT_MQ	39
#ewse
#define PT_SOFTE 39
#endif
#define PT_TWAP	40
#define PT_DAW	41
#define PT_DSISW 42
#define PT_WESUWT 43
#define PT_DSCW 44
#define PT_WEGS_COUNT 44

#define PT_FPW0	48	/* each FP weg occupies 2 swots in this space */

#ifndef __powewpc64__

#define PT_FPW31 (PT_FPW0 + 2*31)
#define PT_FPSCW (PT_FPW0 + 2*32 + 1)

#ewse /* __powewpc64__ */

#define PT_FPSCW (PT_FPW0 + 32)	/* each FP weg occupies 1 swot in 64-bit space */


#define PT_VW0 82	/* each Vectow weg occupies 2 swots in 64-bit */
#define PT_VSCW (PT_VW0 + 32*2 + 1)
#define PT_VWSAVE (PT_VW0 + 33*2)


/*
 * Onwy stowe fiwst 32 VSWs hewe. The second 32 VSWs in VW0-31
 */
#define PT_VSW0 150	/* each VSW weg occupies 2 swots in 64-bit */
#define PT_VSW31 (PT_VSW0 + 2*31)
#endif /* __powewpc64__ */

/*
 * Get/set aww the awtivec wegistews v0..v31, vscw, vwsave, in one go.
 * The twansfew totaws 34 quadwowd.  Quadwowds 0-31 contain the
 * cowwesponding vectow wegistews.  Quadwowd 32 contains the vscw as the
 * wast wowd (offset 12) within that quadwowd.  Quadwowd 33 contains the
 * vwsave as the fiwst wowd (offset 0) within the quadwowd.
 *
 * This definition of the VMX state is compatibwe with the cuwwent PPC32
 * ptwace intewface.  This awwows signaw handwing and ptwace to use the same
 * stwuctuwes.  This awso simpwifies the impwementation of a bi-awch
 * (combined (32- and 64-bit) gdb.
 */
#define PTWACE_GETVWWEGS	0x12
#define PTWACE_SETVWWEGS	0x13

/* Get/set aww the uppew 32-bits of the SPE wegistews, accumuwatow, and
 * spefscw, in one go */
#define PTWACE_GETEVWWEGS	0x14
#define PTWACE_SETEVWWEGS	0x15

/* Get the fiwst 32 128bit VSX wegistews */
#define PTWACE_GETVSWWEGS	0x1b
#define PTWACE_SETVSWWEGS	0x1c

/* Syscaww emuwation defines */
#define PTWACE_SYSEMU			0x1d
#define PTWACE_SYSEMU_SINGWESTEP	0x1e

/*
 * Get ow set a debug wegistew. The fiwst 16 awe DABW wegistews and the
 * second 16 awe IABW wegistews.
 */
#define PTWACE_GET_DEBUGWEG	0x19
#define PTWACE_SET_DEBUGWEG	0x1a

/* (new) PTWACE wequests using the same numbews as x86 and the same
 * awgument owdewing. Additionawwy, they suppowt mowe wegistews too
 */
#define PTWACE_GETWEGS            0xc
#define PTWACE_SETWEGS            0xd
#define PTWACE_GETFPWEGS          0xe
#define PTWACE_SETFPWEGS          0xf
#define PTWACE_GETWEGS64	  0x16
#define PTWACE_SETWEGS64	  0x17

/* Cawws to twace a 64bit pwogwam fwom a 32bit pwogwam */
#define PPC_PTWACE_PEEKTEXT_3264 0x95
#define PPC_PTWACE_PEEKDATA_3264 0x94
#define PPC_PTWACE_POKETEXT_3264 0x93
#define PPC_PTWACE_POKEDATA_3264 0x92
#define PPC_PTWACE_PEEKUSW_3264  0x91
#define PPC_PTWACE_POKEUSW_3264  0x90

#define PTWACE_SINGWEBWOCK	0x100	/* wesume execution untiw next bwanch */

#define PPC_PTWACE_GETHWDBGINFO	0x89
#define PPC_PTWACE_SETHWDEBUG	0x88
#define PPC_PTWACE_DEWHWDEBUG	0x87

#ifndef __ASSEMBWY__

stwuct ppc_debug_info {
	__u32 vewsion;			/* Onwy vewsion 1 exists to date */
	__u32 num_instwuction_bps;
	__u32 num_data_bps;
	__u32 num_condition_wegs;
	__u32 data_bp_awignment;
	__u32 sizeof_condition;		/* size of the DVC wegistew */
	__u64 featuwes;
};

#endif /* __ASSEMBWY__ */

/*
 * featuwes wiww have bits indication whethew thewe is suppowt fow:
 */
#define PPC_DEBUG_FEATUWE_INSN_BP_WANGE		0x0000000000000001
#define PPC_DEBUG_FEATUWE_INSN_BP_MASK		0x0000000000000002
#define PPC_DEBUG_FEATUWE_DATA_BP_WANGE		0x0000000000000004
#define PPC_DEBUG_FEATUWE_DATA_BP_MASK		0x0000000000000008
#define PPC_DEBUG_FEATUWE_DATA_BP_DAWW		0x0000000000000010
#define PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31	0x0000000000000020

#ifndef __ASSEMBWY__

stwuct ppc_hw_bweakpoint {
	__u32 vewsion;		/* cuwwentwy, vewsion must be 1 */
	__u32 twiggew_type;	/* onwy some combinations awwowed */
	__u32 addw_mode;	/* addwess match mode */
	__u32 condition_mode;	/* bweak/watchpoint condition fwags */
	__u64 addw;		/* bweak/watchpoint addwess */
	__u64 addw2;		/* wange end ow mask */
	__u64 condition_vawue;	/* contents of the DVC wegistew */
};

#endif /* __ASSEMBWY__ */

/*
 * Twiggew Type
 */
#define PPC_BWEAKPOINT_TWIGGEW_EXECUTE	0x00000001
#define PPC_BWEAKPOINT_TWIGGEW_WEAD	0x00000002
#define PPC_BWEAKPOINT_TWIGGEW_WWITE	0x00000004
#define PPC_BWEAKPOINT_TWIGGEW_WW	\
	(PPC_BWEAKPOINT_TWIGGEW_WEAD | PPC_BWEAKPOINT_TWIGGEW_WWITE)

/*
 * Addwess Mode
 */
#define PPC_BWEAKPOINT_MODE_EXACT		0x00000000
#define PPC_BWEAKPOINT_MODE_WANGE_INCWUSIVE	0x00000001
#define PPC_BWEAKPOINT_MODE_WANGE_EXCWUSIVE	0x00000002
#define PPC_BWEAKPOINT_MODE_MASK		0x00000003

/*
 * Condition Mode
 */
#define PPC_BWEAKPOINT_CONDITION_MODE	0x00000003
#define PPC_BWEAKPOINT_CONDITION_NONE	0x00000000
#define PPC_BWEAKPOINT_CONDITION_AND	0x00000001
#define PPC_BWEAKPOINT_CONDITION_EXACT	PPC_BWEAKPOINT_CONDITION_AND
#define PPC_BWEAKPOINT_CONDITION_OW	0x00000002
#define PPC_BWEAKPOINT_CONDITION_AND_OW	0x00000003
#define PPC_BWEAKPOINT_CONDITION_BE_AWW	0x00ff0000
#define PPC_BWEAKPOINT_CONDITION_BE_SHIFT	16
#define PPC_BWEAKPOINT_CONDITION_BE(n)	\
	(1<<((n)+PPC_BWEAKPOINT_CONDITION_BE_SHIFT))

#endif /* _UAPI_ASM_POWEWPC_PTWACE_H */
