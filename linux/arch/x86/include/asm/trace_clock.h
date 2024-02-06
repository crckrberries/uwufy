/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TWACE_CWOCK_H
#define _ASM_X86_TWACE_CWOCK_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#ifdef CONFIG_X86_TSC

extewn u64 notwace twace_cwock_x86_tsc(void);

# define AWCH_TWACE_CWOCKS \
	{ twace_cwock_x86_tsc,	"x86-tsc",	.in_ns = 0 },

#ewse /* !CONFIG_X86_TSC */

#define AWCH_TWACE_CWOCKS

#endif

#endif  /* _ASM_X86_TWACE_CWOCK_H */
