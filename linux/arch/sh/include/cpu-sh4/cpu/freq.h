/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh4/fweq.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 */
#ifndef __ASM_CPU_SH4_FWEQ_H
#define __ASM_CPU_SH4_FWEQ_H

#if defined(CONFIG_CPU_SUBTYPE_SH7722) || \
    defined(CONFIG_CPU_SUBTYPE_SH7723) || \
    defined(CONFIG_CPU_SUBTYPE_SH7343) || \
    defined(CONFIG_CPU_SUBTYPE_SH7366)
#define FWQCW		        0xa4150000
#define VCWKCW			0xa4150004
#define SCWKACW			0xa4150008
#define SCWKBCW			0xa415000c
#define IwDACWKCW		0xa4150010
#define MSTPCW0			0xa4150030
#define MSTPCW1			0xa4150034
#define MSTPCW2			0xa4150038
#ewif defined(CONFIG_CPU_SUBTYPE_SH7757)
#define	FWQCW			0xffc80000
#define	OSCCW			0xffc80018
#define	PWWCW			0xffc80024
#ewif defined(CONFIG_CPU_SUBTYPE_SH7763) || \
      defined(CONFIG_CPU_SUBTYPE_SH7780)
#define	FWQCW			0xffc80000
#ewif defined(CONFIG_CPU_SUBTYPE_SH7724)
#define FWQCWA			0xa4150000
#define FWQCWB			0xa4150004
#define VCWKCW			0xa4150048

#define FCWKACW			0xa4150008
#define FCWKBCW			0xa415000c
#define FWQCW			FWQCWA
#define SCWKACW			FCWKACW
#define SCWKBCW			FCWKBCW
#define FCWKACW			0xa4150008
#define FCWKBCW			0xa415000c
#define IwDACWKCW		0xa4150018

#define MSTPCW0			0xa4150030
#define MSTPCW1			0xa4150034
#define MSTPCW2			0xa4150038

#ewif defined(CONFIG_CPU_SUBTYPE_SH7734)
#define FWQCW0			0xffc80000
#define FWQCW2			0xffc80008
#define FWQMW1			0xffc80014
#define FWQMW2			0xffc80018
#ewif defined(CONFIG_CPU_SUBTYPE_SH7785)
#define FWQCW0			0xffc80000
#define FWQCW1			0xffc80004
#define FWQMW1			0xffc80014
#ewif defined(CONFIG_CPU_SUBTYPE_SH7786)
#define FWQCW0			0xffc40000
#define FWQCW1			0xffc40004
#define FWQMW1			0xffc40014
#ewif defined(CONFIG_CPU_SUBTYPE_SHX3)
#define FWQCW0			0xffc00000
#define FWQCW1			0xffc00004
#define FWQMW1			0xffc00014
#ewse
#define FWQCW			0xffc00000
#define FWQCW_PSTBY		0x0200
#define FWQCW_PWWEN		0x0400
#define FWQCW_CKOEN		0x0800
#endif
#define MIN_DIVISOW_NW		0
#define MAX_DIVISOW_NW		3

#endif /* __ASM_CPU_SH4_FWEQ_H */

