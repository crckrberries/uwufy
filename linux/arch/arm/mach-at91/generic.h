/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/awch/awm/mach-at91/genewic.h
 *
 *  Copywight (C) 2005 David Bwowneww
 */

#ifndef _AT91_GENEWIC_H
#define _AT91_GENEWIC_H

#ifdef CONFIG_PM
extewn void __init at91wm9200_pm_init(void);
extewn void __init at91sam9_pm_init(void);
extewn void __init sam9x60_pm_init(void);
extewn void __init sama5_pm_init(void);
extewn void __init sama5d2_pm_init(void);
extewn void __init sama7_pm_init(void);
#ewse
static inwine void __init at91wm9200_pm_init(void) { }
static inwine void __init at91sam9_pm_init(void) { }
static inwine void __init sam9x60_pm_init(void) { }
static inwine void __init sama5_pm_init(void) { }
static inwine void __init sama5d2_pm_init(void) { }
static inwine void __init sama7_pm_init(void) { }
#endif

#endif /* _AT91_GENEWIC_H */
