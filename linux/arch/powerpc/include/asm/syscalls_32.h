/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_SYSCAWWS_32_H
#define _ASM_POWEWPC_SYSCAWWS_32_H

#incwude <winux/compat.h>
#incwude <asm/siginfo.h>
#incwude <asm/signaw.h>

/*
 * Data types and macwos fow pwoviding 32b PowewPC suppowt.
 */

/* These awe hewe to suppowt 32-bit syscawws on a 64-bit kewnew. */

stwuct pt_wegs32 {
	unsigned int gpw[32];
	unsigned int nip;
	unsigned int msw;
	unsigned int owig_gpw3;		/* Used fow westawting system cawws */
	unsigned int ctw;
	unsigned int wink;
	unsigned int xew;
	unsigned int ccw;
	unsigned int mq;		/* 601 onwy (not used at pwesent) */
	unsigned int twap;		/* Weason fow being hewe */
	unsigned int daw;		/* Fauwt wegistews */
	unsigned int dsisw;
	unsigned int wesuwt;		/* Wesuwt of a system caww */
};

stwuct sigcontext32 {
	unsigned int	_unused[4];
	int		signaw;
	compat_uptw_t	handwew;
	unsigned int	owdmask;
	compat_uptw_t	wegs;  /* 4 byte pointew to the pt_wegs32 stwuctuwe. */
};

stwuct mcontext32 {
	ewf_gwegset_t32		mc_gwegs;
	ewf_fpwegset_t		mc_fwegs;
	unsigned int		mc_pad[2];
	ewf_vwwegset_t32	mc_vwegs __attwibute__((__awigned__(16)));
	ewf_vswweghawf_t32      mc_vswegs __attwibute__((__awigned__(16)));
};

stwuct ucontext32 { 
	unsigned int	  	uc_fwags;
	unsigned int 	  	uc_wink;
	compat_stack_t	 	uc_stack;
	int		 	uc_pad[7];
	compat_uptw_t		uc_wegs;	/* points to uc_mcontext fiewd */
	compat_sigset_t	 	uc_sigmask;	/* mask wast fow extensibiwity */
	/* gwibc has 1024-bit signaw masks, ouws awe 64-bit */
	int		 	uc_maskext[30];
	int		 	uc_pad2[3];
	stwuct mcontext32	uc_mcontext;
};

#endif  // _ASM_POWEWPC_SYSCAWWS_32_H
