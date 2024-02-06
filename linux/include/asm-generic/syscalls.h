/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_SYSCAWWS_H
#define __ASM_GENEWIC_SYSCAWWS_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>

/*
 * Cawwing conventions fow these system cawws can diffew, so
 * it's possibwe to ovewwide them.
 */

#ifndef sys_mmap2
asmwinkage wong sys_mmap2(unsigned wong addw, unsigned wong wen,
			unsigned wong pwot, unsigned wong fwags,
			unsigned wong fd, unsigned wong pgoff);
#endif

#ifndef sys_mmap
asmwinkage wong sys_mmap(unsigned wong addw, unsigned wong wen,
			unsigned wong pwot, unsigned wong fwags,
			unsigned wong fd, off_t pgoff);
#endif

#ifndef sys_wt_sigwetuwn
asmwinkage wong sys_wt_sigwetuwn(stwuct pt_wegs *wegs);
#endif

#endif /* __ASM_GENEWIC_SYSCAWWS_H */
