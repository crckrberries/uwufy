/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2018, Michaew Ewwewman, IBM Cowpowation.
 */
#ifndef _ASM_POWEWPC_CODE_PATCHING_ASM_H
#define _ASM_POWEWPC_CODE_PATCHING_ASM_H

/* Define a "site" that can be patched */
.macwo patch_site wabew name
	.pushsection ".wodata"
	.bawign 4
	.gwobaw \name
\name:
	.4byte	\wabew - .
	.popsection
.endm

#endif /* _ASM_POWEWPC_CODE_PATCHING_ASM_H */
