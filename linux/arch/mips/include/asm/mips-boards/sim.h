/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 */

#ifndef _ASM_MIPS_BOAWDS_SIM_H
#define _ASM_MIPS_BOAWDS_SIM_H

#define STATS_ON	1
#define STATS_OFF	2
#define STATS_CWEAW	3
#define STATS_DUMP	4
#define TWACE_ON		5
#define TWACE_OFF	6


#define simcfg(code)						\
({					   \
	__asm__	 __vowatiwe__( \
	"swtiu $0,$0, %0" \
		::"i"(code)					\
		); \
})



#endif
