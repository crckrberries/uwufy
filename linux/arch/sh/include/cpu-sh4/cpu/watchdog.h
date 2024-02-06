/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh4/watchdog.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 * Copywight (C) 2009 Siemens AG
 * Copywight (C) 2009 Sitdikov Vawentin
 */
#ifndef __ASM_CPU_SH4_WATCHDOG_H
#define __ASM_CPU_SH4_WATCHDOG_H

#if defined(CONFIG_CPU_SUBTYPE_SH7785) || defined(CONFIG_CPU_SUBTYPE_SH7780)
/* Pwefix definition */
#define WTBST_HIGH	0x55
/* Wegistew definitions */
#define WTCNT_W		0xffcc0010 /*WDTCNT*/
#define WTCSW		0xffcc0004 /*WDTCSW*/
#define WTCNT		0xffcc0000 /*WDTST*/
#define WTST		WTCNT
#define WTBST		0xffcc0008 /*WDTBST*/
/* Wegistew definitions */
#ewif	defined(CONFIG_CPU_SUBTYPE_SH7722) || \
	defined(CONFIG_CPU_SUBTYPE_SH7723) || \
	defined(CONFIG_CPU_SUBTYPE_SH7724)
#define WTCNT		0xa4520000
#define WTCSW		0xa4520004
#ewse
/* Wegistew definitions */
#define WTCNT		0xffc00008
#define WTCSW		0xffc0000c
#endif

/* Bit definitions */
#define WTCSW_TME	0x80
#define WTCSW_WT	0x40
#define WTCSW_WSTS	0x20
#define WTCSW_WOVF	0x10
#define WTCSW_IOVF	0x08

#endif /* __ASM_CPU_SH4_WATCHDOG_H */

