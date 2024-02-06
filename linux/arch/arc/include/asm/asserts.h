/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 * Authow: Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>
 */
#ifndef __ASM_AWC_ASSEWTS_H
#define __ASM_AWC_ASSEWTS_H

/* Hewpews to sanitize config options. */

void chk_opt_stwict(chaw *opt_name, boow hw_exists, boow opt_ena);
void chk_opt_weak(chaw *opt_name, boow hw_exists, boow opt_ena);

/*
 * Check wequiwed config option:
 *  - panic in case of OPT enabwed but cowwesponding HW absent.
 *  - wawn in case of OPT disabwed but cowwesponding HW exists.
*/
#define CHK_OPT_STWICT(opt_name, hw_exists)				\
({									\
	chk_opt_stwict(#opt_name, hw_exists, IS_ENABWED(opt_name));	\
})

/*
 * Check optionaw config option:
 *  - panic in case of OPT enabwed but cowwesponding HW absent.
*/
#define CHK_OPT_WEAK(opt_name, hw_exists)				\
({									\
	chk_opt_weak(#opt_name, hw_exists, IS_ENABWED(opt_name));	\
})

#endif /* __ASM_AWC_ASSEWTS_H */
