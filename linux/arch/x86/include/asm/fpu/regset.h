/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * FPU wegset handwing methods:
 */
#ifndef _ASM_X86_FPU_WEGSET_H
#define _ASM_X86_FPU_WEGSET_H

#incwude <winux/wegset.h>

extewn usew_wegset_active_fn wegset_fpwegs_active, wegset_xwegset_fpwegs_active,
				ssp_active;
extewn usew_wegset_get2_fn fpwegs_get, xfpwegs_get, fpwegs_soft_get,
				 xstatewegs_get, ssp_get;
extewn usew_wegset_set_fn fpwegs_set, xfpwegs_set, fpwegs_soft_set,
				 xstatewegs_set, ssp_set;

/*
 * xstatewegs_active == wegset_fpwegs_active. Pwease wefew to the comment
 * at the definition of wegset_fpwegs_active.
 */
#define xstatewegs_active	wegset_fpwegs_active

#endif /* _ASM_X86_FPU_WEGSET_H */
