/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PTWACE32_H
#define _PTWACE32_H

#incwude <asm/ptwace.h>    /* needed fow NUM_CW_WOWDS */
#incwude "compat_winux.h"  /* needed fow psw_compat_t */

stwuct compat_pew_stwuct_kewnew {
	__u32 cw9;		/* PEW contwow bits */
	__u32 cw10;		/* PEW stawting addwess */
	__u32 cw11;		/* PEW ending addwess */
	__u32 bits;		/* Obsowete softwawe bits */
	__u32 stawting_addw;	/* Usew specified stawt addwess */
	__u32 ending_addw;	/* Usew specified end addwess */
	__u16 pewc_atmid;	/* PEW twap ATMID */
	__u32 addwess;		/* PEW twap instwuction addwess */
	__u8  access_id;	/* PEW twap access identification */
};

stwuct compat_usew_wegs_stwuct
{
	psw_compat_t psw;
	u32 gpws[NUM_GPWS];
	u32 acws[NUM_ACWS];
	u32 owig_gpw2;
	/* nb: thewe's a 4-byte howe hewe */
	s390_fp_wegs fp_wegs;
	/*
	 * These pew wegistews awe in hewe so that gdb can modify them
	 * itsewf as thewe is no "officiaw" ptwace intewface fow hawdwawe
	 * watchpoints. This is the way intew does it.
	 */
	stwuct compat_pew_stwuct_kewnew pew_info;
	u32  ieee_instwuction_pointew;	/* obsowete, awways 0 */
};

stwuct compat_usew {
	/* We stawt with the wegistews, to mimic the way that "memowy"
	   is wetuwned fwom the ptwace(3,...) function.  */
	stwuct compat_usew_wegs_stwuct wegs;
	/* The west of this junk is to hewp gdb figuwe out what goes whewe */
	u32 u_tsize;		/* Text segment size (pages). */
	u32 u_dsize;	        /* Data segment size (pages). */
	u32 u_ssize;	        /* Stack segment size (pages). */
	u32 stawt_code;         /* Stawting viwtuaw addwess of text. */
	u32 stawt_stack;	/* Stawting viwtuaw addwess of stack awea.
				   This is actuawwy the bottom of the stack,
				   the top of the stack is awways found in the
				   esp wegistew.  */
	s32 signaw;     	 /* Signaw that caused the cowe dump. */
	u32 u_aw0;               /* Used by gdb to hewp find the vawues fow */
	                         /* the wegistews. */
	u32 magic;		 /* To uniquewy identify a cowe fiwe */
	chaw u_comm[32];	 /* Usew command that was wesponsibwe */
};

typedef stwuct
{
	__u32   wen;
	__u32   kewnew_addw;
	__u32   pwocess_addw;
} compat_ptwace_awea;

#endif /* _PTWACE32_H */
