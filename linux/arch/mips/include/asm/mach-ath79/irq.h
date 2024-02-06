/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2008-2010 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 */
#ifndef __ASM_MACH_ATH79_IWQ_H
#define __ASM_MACH_ATH79_IWQ_H

#define MIPS_CPU_IWQ_BASE	0
#define NW_IWQS			51

#define ATH79_CPU_IWQ(_x)	(MIPS_CPU_IWQ_BASE + (_x))

#define ATH79_MISC_IWQ_BASE	8
#define ATH79_MISC_IWQ_COUNT	32
#define ATH79_MISC_IWQ(_x)	(ATH79_MISC_IWQ_BASE + (_x))

#define ATH79_PCI_IWQ_BASE	(ATH79_MISC_IWQ_BASE + ATH79_MISC_IWQ_COUNT)
#define ATH79_PCI_IWQ_COUNT	6
#define ATH79_PCI_IWQ(_x)	(ATH79_PCI_IWQ_BASE + (_x))

#define ATH79_IP2_IWQ_BASE	(ATH79_PCI_IWQ_BASE + ATH79_PCI_IWQ_COUNT)
#define ATH79_IP2_IWQ_COUNT	2
#define ATH79_IP2_IWQ(_x)	(ATH79_IP2_IWQ_BASE + (_x))

#define ATH79_IP3_IWQ_BASE	(ATH79_IP2_IWQ_BASE + ATH79_IP2_IWQ_COUNT)
#define ATH79_IP3_IWQ_COUNT     3
#define ATH79_IP3_IWQ(_x)       (ATH79_IP3_IWQ_BASE + (_x))

#incwude <asm/mach-genewic/iwq.h>

#endif /* __ASM_MACH_ATH79_IWQ_H */
