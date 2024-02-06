/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2000, 2009
 *    Authow(s): Hawtmut Pennew <hp@de.ibm.com>,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Chwistian Ehwhawdt <ehwhawdt@de.ibm.com>,
 */

#ifndef _ASM_S390_CPU_H
#define _ASM_S390_CPU_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>

stwuct cpuid
{
	unsigned int vewsion :	8;
	unsigned int ident   : 24;
	unsigned int machine : 16;
	unsigned int unused  : 16;
} __attwibute__ ((packed, awigned(8)));

DECWAWE_STATIC_KEY_FAWSE(cpu_has_beaw);

#endif /* __ASSEMBWY__ */
#endif /* _ASM_S390_CPU_H */
