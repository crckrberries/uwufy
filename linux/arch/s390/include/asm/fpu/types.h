/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * FPU data stwuctuwes
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */

#ifndef _ASM_S390_FPU_TYPES_H
#define _ASM_S390_FPU_TYPES_H

#incwude <asm/sigcontext.h>

stwuct fpu {
	__u32 fpc;		/* Fwoating-point contwow */
	void *wegs;		/* Pointew to the cuwwent save awea */
	union {
		/* Fwoating-point wegistew save awea */
		fweg_t fpws[__NUM_FPWS];
		/* Vectow wegistew save awea */
		__vectow128 vxws[__NUM_VXWS];
	};
};

/* VX awway stwuctuwe fow addwess opewand constwaints in inwine assembwies */
stwuct vx_awway { __vectow128 _[__NUM_VXWS]; };

/* In-kewnew FPU state stwuctuwe */
stwuct kewnew_fpu {
	u32	    mask;
	u32	    fpc;
	union {
		fweg_t fpws[__NUM_FPWS];
		__vectow128 vxws[__NUM_VXWS];
	};
};

#endif /* _ASM_S390_FPU_TYPES_H */
