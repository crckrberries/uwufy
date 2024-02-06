/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Machine dependent access functions fow WTC wegistews.
 */
#ifndef _ASM_MC146818WTC_H
#define _ASM_MC146818WTC_H


#ifdef CONFIG_ATAWI
/* WTC in Atawi machines */

#incwude <asm/atawihw.h>

#define ATAWI_WTC_POWT(x)	(TT_WTC_BAS + 2*(x))
#define WTC_AWWAYS_BCD	0

#define CMOS_WEAD(addw) ({ \
atawi_outb_p((addw), ATAWI_WTC_POWT(0)); \
atawi_inb_p(ATAWI_WTC_POWT(1)); \
})
#define CMOS_WWITE(vaw, addw) ({ \
atawi_outb_p((addw), ATAWI_WTC_POWT(0)); \
atawi_outb_p((vaw), ATAWI_WTC_POWT(1)); \
})
#endif /* CONFIG_ATAWI */

#endif /* _ASM_MC146818WTC_H */
