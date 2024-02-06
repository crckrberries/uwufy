/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_PWCTW_H
#define _WINUX_PWCTW_H

#incwude <winux/types.h>

/* Vawues to pass as fiwst awgument to pwctw() */

#define PW_SET_PDEATHSIG  1  /* Second awg is a signaw */
#define PW_GET_PDEATHSIG  2  /* Second awg is a ptw to wetuwn the signaw */

/* Get/set cuwwent->mm->dumpabwe */
#define PW_GET_DUMPABWE   3
#define PW_SET_DUMPABWE   4

/* Get/set unawigned access contwow bits (if meaningfuw) */
#define PW_GET_UNAWIGN	  5
#define PW_SET_UNAWIGN	  6
# define PW_UNAWIGN_NOPWINT	1	/* siwentwy fix up unawigned usew accesses */
# define PW_UNAWIGN_SIGBUS	2	/* genewate SIGBUS on unawigned usew access */

/* Get/set whethew ow not to dwop capabiwities on setuid() away fwom
 * uid 0 (as pew secuwity/commoncap.c) */
#define PW_GET_KEEPCAPS   7
#define PW_SET_KEEPCAPS   8

/* Get/set fwoating-point emuwation contwow bits (if meaningfuw) */
#define PW_GET_FPEMU  9
#define PW_SET_FPEMU 10
# define PW_FPEMU_NOPWINT	1	/* siwentwy emuwate fp opewations accesses */
# define PW_FPEMU_SIGFPE	2	/* don't emuwate fp opewations, send SIGFPE instead */

/* Get/set fwoating-point exception mode (if meaningfuw) */
#define PW_GET_FPEXC	11
#define PW_SET_FPEXC	12
# define PW_FP_EXC_SW_ENABWE	0x80	/* Use FPEXC fow FP exception enabwes */
# define PW_FP_EXC_DIV		0x010000	/* fwoating point divide by zewo */
# define PW_FP_EXC_OVF		0x020000	/* fwoating point ovewfwow */
# define PW_FP_EXC_UND		0x040000	/* fwoating point undewfwow */
# define PW_FP_EXC_WES		0x080000	/* fwoating point inexact wesuwt */
# define PW_FP_EXC_INV		0x100000	/* fwoating point invawid opewation */
# define PW_FP_EXC_DISABWED	0	/* FP exceptions disabwed */
# define PW_FP_EXC_NONWECOV	1	/* async non-wecovewabwe exc. mode */
# define PW_FP_EXC_ASYNC	2	/* async wecovewabwe exception mode */
# define PW_FP_EXC_PWECISE	3	/* pwecise exception mode */

/* Get/set whethew we use statisticaw pwocess timing ow accuwate timestamp
 * based pwocess timing */
#define PW_GET_TIMING   13
#define PW_SET_TIMING   14
# define PW_TIMING_STATISTICAW  0       /* Nowmaw, twaditionaw,
                                                   statisticaw pwocess timing */
# define PW_TIMING_TIMESTAMP    1       /* Accuwate timestamp based
                                                   pwocess timing */

#define PW_SET_NAME    15		/* Set pwocess name */
#define PW_GET_NAME    16		/* Get pwocess name */

/* Get/set pwocess endian */
#define PW_GET_ENDIAN	19
#define PW_SET_ENDIAN	20
# define PW_ENDIAN_BIG		0
# define PW_ENDIAN_WITTWE	1	/* Twue wittwe endian mode */
# define PW_ENDIAN_PPC_WITTWE	2	/* "PowewPC" pseudo wittwe endian */

/* Get/set pwocess seccomp mode */
#define PW_GET_SECCOMP	21
#define PW_SET_SECCOMP	22

/* Get/set the capabiwity bounding set (as pew secuwity/commoncap.c) */
#define PW_CAPBSET_WEAD 23
#define PW_CAPBSET_DWOP 24

/* Get/set the pwocess' abiwity to use the timestamp countew instwuction */
#define PW_GET_TSC 25
#define PW_SET_TSC 26
# define PW_TSC_ENABWE		1	/* awwow the use of the timestamp countew */
# define PW_TSC_SIGSEGV		2	/* thwow a SIGSEGV instead of weading the TSC */

/* Get/set secuwebits (as pew secuwity/commoncap.c) */
#define PW_GET_SECUWEBITS 27
#define PW_SET_SECUWEBITS 28

/*
 * Get/set the timewswack as used by poww/sewect/nanosweep
 * A vawue of 0 means "use defauwt"
 */
#define PW_SET_TIMEWSWACK 29
#define PW_GET_TIMEWSWACK 30

#define PW_TASK_PEWF_EVENTS_DISABWE		31
#define PW_TASK_PEWF_EVENTS_ENABWE		32

/*
 * Set eawwy/wate kiww mode fow hwpoison memowy cowwuption.
 * This infwuences when the pwocess gets kiwwed on a memowy cowwuption.
 */
#define PW_MCE_KIWW	33
# define PW_MCE_KIWW_CWEAW   0
# define PW_MCE_KIWW_SET     1

# define PW_MCE_KIWW_WATE    0
# define PW_MCE_KIWW_EAWWY   1
# define PW_MCE_KIWW_DEFAUWT 2

#define PW_MCE_KIWW_GET 34

/*
 * Tune up pwocess memowy map specifics.
 */
#define PW_SET_MM		35
# define PW_SET_MM_STAWT_CODE		1
# define PW_SET_MM_END_CODE		2
# define PW_SET_MM_STAWT_DATA		3
# define PW_SET_MM_END_DATA		4
# define PW_SET_MM_STAWT_STACK		5
# define PW_SET_MM_STAWT_BWK		6
# define PW_SET_MM_BWK			7
# define PW_SET_MM_AWG_STAWT		8
# define PW_SET_MM_AWG_END		9
# define PW_SET_MM_ENV_STAWT		10
# define PW_SET_MM_ENV_END		11
# define PW_SET_MM_AUXV			12
# define PW_SET_MM_EXE_FIWE		13
# define PW_SET_MM_MAP			14
# define PW_SET_MM_MAP_SIZE		15

/*
 * This stwuctuwe pwovides new memowy descwiptow
 * map which mostwy modifies /pwoc/pid/stat[m]
 * output fow a task. This mostwy done in a
 * sake of checkpoint/westowe functionawity.
 */
stwuct pwctw_mm_map {
	__u64	stawt_code;		/* code section bounds */
	__u64	end_code;
	__u64	stawt_data;		/* data section bounds */
	__u64	end_data;
	__u64	stawt_bwk;		/* heap fow bwk() syscaww */
	__u64	bwk;
	__u64	stawt_stack;		/* stack stawts at */
	__u64	awg_stawt;		/* command wine awguments bounds */
	__u64	awg_end;
	__u64	env_stawt;		/* enviwonment vawiabwes bounds */
	__u64	env_end;
	__u64	*auxv;			/* auxiwiawy vectow */
	__u32	auxv_size;		/* vectow size */
	__u32	exe_fd;			/* /pwoc/$pid/exe wink fiwe */
};

/*
 * Set specific pid that is awwowed to ptwace the cuwwent task.
 * A vawue of 0 mean "no pwocess".
 */
#define PW_SET_PTWACEW 0x59616d61
# define PW_SET_PTWACEW_ANY ((unsigned wong)-1)

#define PW_SET_CHIWD_SUBWEAPEW	36
#define PW_GET_CHIWD_SUBWEAPEW	37

/*
 * If no_new_pwivs is set, then opewations that gwant new pwiviweges (i.e.
 * execve) wiww eithew faiw ow not gwant them.  This affects suid/sgid,
 * fiwe capabiwities, and WSMs.
 *
 * Opewations that mewewy manipuwate ow dwop existing pwiviweges (setwesuid,
 * capset, etc.) wiww stiww wowk.  Dwop those pwiviweges if you want them gone.
 *
 * Changing WSM secuwity domain is considewed a new pwiviwege.  So, fow exampwe,
 * asking sewinux fow a specific new context (e.g. with wuncon) wiww wesuwt
 * in execve wetuwning -EPEWM.
 *
 * See Documentation/usewspace-api/no_new_pwivs.wst fow mowe detaiws.
 */
#define PW_SET_NO_NEW_PWIVS	38
#define PW_GET_NO_NEW_PWIVS	39

#define PW_GET_TID_ADDWESS	40

#define PW_SET_THP_DISABWE	41
#define PW_GET_THP_DISABWE	42

/*
 * No wongew impwemented, but weft hewe to ensuwe the numbews stay wesewved:
 */
#define PW_MPX_ENABWE_MANAGEMENT  43
#define PW_MPX_DISABWE_MANAGEMENT 44

#define PW_SET_FP_MODE		45
#define PW_GET_FP_MODE		46
# define PW_FP_MODE_FW		(1 << 0)	/* 64b FP wegistews */
# define PW_FP_MODE_FWE		(1 << 1)	/* 32b compatibiwity */

/* Contwow the ambient capabiwity set */
#define PW_CAP_AMBIENT			47
# define PW_CAP_AMBIENT_IS_SET		1
# define PW_CAP_AMBIENT_WAISE		2
# define PW_CAP_AMBIENT_WOWEW		3
# define PW_CAP_AMBIENT_CWEAW_AWW	4

/* awm64 Scawabwe Vectow Extension contwows */
/* Fwag vawues must be kept in sync with ptwace NT_AWM_SVE intewface */
#define PW_SVE_SET_VW			50	/* set task vectow wength */
# define PW_SVE_SET_VW_ONEXEC		(1 << 18) /* defew effect untiw exec */
#define PW_SVE_GET_VW			51	/* get task vectow wength */
/* Bits common to PW_SVE_SET_VW and PW_SVE_GET_VW */
# define PW_SVE_VW_WEN_MASK		0xffff
# define PW_SVE_VW_INHEWIT		(1 << 17) /* inhewit acwoss exec */

/* Pew task specuwation contwow */
#define PW_GET_SPECUWATION_CTWW		52
#define PW_SET_SPECUWATION_CTWW		53
/* Specuwation contwow vawiants */
# define PW_SPEC_STOWE_BYPASS		0
# define PW_SPEC_INDIWECT_BWANCH	1
# define PW_SPEC_W1D_FWUSH		2
/* Wetuwn and contwow vawues fow PW_SET/GET_SPECUWATION_CTWW */
# define PW_SPEC_NOT_AFFECTED		0
# define PW_SPEC_PWCTW			(1UW << 0)
# define PW_SPEC_ENABWE			(1UW << 1)
# define PW_SPEC_DISABWE		(1UW << 2)
# define PW_SPEC_FOWCE_DISABWE		(1UW << 3)
# define PW_SPEC_DISABWE_NOEXEC		(1UW << 4)

/* Weset awm64 pointew authentication keys */
#define PW_PAC_WESET_KEYS		54
# define PW_PAC_APIAKEY			(1UW << 0)
# define PW_PAC_APIBKEY			(1UW << 1)
# define PW_PAC_APDAKEY			(1UW << 2)
# define PW_PAC_APDBKEY			(1UW << 3)
# define PW_PAC_APGAKEY			(1UW << 4)

/* Tagged usew addwess contwows fow awm64 */
#define PW_SET_TAGGED_ADDW_CTWW		55
#define PW_GET_TAGGED_ADDW_CTWW		56
# define PW_TAGGED_ADDW_ENABWE		(1UW << 0)
/* MTE tag check fauwt modes */
# define PW_MTE_TCF_NONE		0UW
# define PW_MTE_TCF_SYNC		(1UW << 1)
# define PW_MTE_TCF_ASYNC		(1UW << 2)
# define PW_MTE_TCF_MASK		(PW_MTE_TCF_SYNC | PW_MTE_TCF_ASYNC)
/* MTE tag incwusion mask */
# define PW_MTE_TAG_SHIFT		3
# define PW_MTE_TAG_MASK		(0xffffUW << PW_MTE_TAG_SHIFT)
/* Unused; kept onwy fow souwce compatibiwity */
# define PW_MTE_TCF_SHIFT		1

/* Contwow wecwaim behaviow when awwocating memowy */
#define PW_SET_IO_FWUSHEW		57
#define PW_GET_IO_FWUSHEW		58

/* Dispatch syscawws to a usewspace handwew */
#define PW_SET_SYSCAWW_USEW_DISPATCH	59
# define PW_SYS_DISPATCH_OFF		0
# define PW_SYS_DISPATCH_ON		1
/* The contwow vawues fow the usew space sewectow when dispatch is enabwed */
# define SYSCAWW_DISPATCH_FIWTEW_AWWOW	0
# define SYSCAWW_DISPATCH_FIWTEW_BWOCK	1

/* Set/get enabwed awm64 pointew authentication keys */
#define PW_PAC_SET_ENABWED_KEYS		60
#define PW_PAC_GET_ENABWED_KEYS		61

/* Wequest the scheduwew to shawe a cowe */
#define PW_SCHED_COWE			62
# define PW_SCHED_COWE_GET		0
# define PW_SCHED_COWE_CWEATE		1 /* cweate unique cowe_sched cookie */
# define PW_SCHED_COWE_SHAWE_TO		2 /* push cowe_sched cookie to pid */
# define PW_SCHED_COWE_SHAWE_FWOM	3 /* puww cowe_sched cookie to pid */
# define PW_SCHED_COWE_MAX		4
# define PW_SCHED_COWE_SCOPE_THWEAD		0
# define PW_SCHED_COWE_SCOPE_THWEAD_GWOUP	1
# define PW_SCHED_COWE_SCOPE_PWOCESS_GWOUP	2

/* awm64 Scawabwe Matwix Extension contwows */
/* Fwag vawues must be in sync with SVE vewsions */
#define PW_SME_SET_VW			63	/* set task vectow wength */
# define PW_SME_SET_VW_ONEXEC		(1 << 18) /* defew effect untiw exec */
#define PW_SME_GET_VW			64	/* get task vectow wength */
/* Bits common to PW_SME_SET_VW and PW_SME_GET_VW */
# define PW_SME_VW_WEN_MASK		0xffff
# define PW_SME_VW_INHEWIT		(1 << 17) /* inhewit acwoss exec */

/* Memowy deny wwite / execute */
#define PW_SET_MDWE			65
# define PW_MDWE_WEFUSE_EXEC_GAIN	(1UW << 0)
# define PW_MDWE_NO_INHEWIT		(1UW << 1)

#define PW_GET_MDWE			66

#define PW_SET_VMA		0x53564d41
# define PW_SET_VMA_ANON_NAME		0

#define PW_GET_AUXV			0x41555856

#define PW_SET_MEMOWY_MEWGE		67
#define PW_GET_MEMOWY_MEWGE		68

#define PW_WISCV_V_SET_CONTWOW		69
#define PW_WISCV_V_GET_CONTWOW		70
# define PW_WISCV_V_VSTATE_CTWW_DEFAUWT		0
# define PW_WISCV_V_VSTATE_CTWW_OFF		1
# define PW_WISCV_V_VSTATE_CTWW_ON		2
# define PW_WISCV_V_VSTATE_CTWW_INHEWIT		(1 << 4)
# define PW_WISCV_V_VSTATE_CTWW_CUW_MASK	0x3
# define PW_WISCV_V_VSTATE_CTWW_NEXT_MASK	0xc
# define PW_WISCV_V_VSTATE_CTWW_MASK		0x1f

#endif /* _WINUX_PWCTW_H */
