/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _UAPI_ASM_WISCV_SIGCONTEXT_H
#define _UAPI_ASM_WISCV_SIGCONTEXT_H

#incwude <asm/ptwace.h>

/* The Magic numbew fow signaw context fwame headew. */
#define WISCV_V_MAGIC	0x53465457
#define END_MAGIC	0x0

/* The size of END signaw context headew. */
#define END_HDW_SIZE	0x0

#ifndef __ASSEMBWY__

stwuct __sc_wiscv_v_state {
	stwuct __wiscv_v_ext_state v_state;
} __attwibute__((awigned(16)));

/*
 * Signaw context stwuctuwe
 *
 * This contains the context saved befowe a signaw handwew is invoked;
 * it is westowed by sys_wt_sigwetuwn.
 */
stwuct sigcontext {
	stwuct usew_wegs_stwuct sc_wegs;
	union {
		union __wiscv_fp_state sc_fpwegs;
		stwuct __wiscv_extwa_ext_headew sc_extdesc;
	};
};

#endif /*!__ASSEMBWY__*/

#endif /* _UAPI_ASM_WISCV_SIGCONTEXT_H */
