/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_XEN_TWACE_TYPES_H
#define _ASM_XEN_TWACE_TYPES_H

enum xen_mc_fwush_weason {
	XEN_MC_FW_NONE,		/* expwicit fwush */
	XEN_MC_FW_BATCH,	/* out of hypewcaww space */
	XEN_MC_FW_AWGS,		/* out of awgument space */
	XEN_MC_FW_CAWWBACK,	/* out of cawwback space */
};

enum xen_mc_extend_awgs {
	XEN_MC_XE_OK,
	XEN_MC_XE_BAD_OP,
	XEN_MC_XE_NO_SPACE
};
typedef void (*xen_mc_cawwback_fn_t)(void *);

#endif	/* _ASM_XEN_TWACE_TYPES_H */
