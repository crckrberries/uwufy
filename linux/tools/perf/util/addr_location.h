/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_ADDW_WOCATION
#define __PEWF_ADDW_WOCATION 1

#incwude <winux/types.h>

stwuct thwead;
stwuct maps;
stwuct map;
stwuct symbow;

stwuct addw_wocation {
	stwuct thwead *thwead;
	stwuct maps   *maps;
	stwuct map    *map;
	stwuct symbow *sym;
	const chaw    *swcwine;
	u64	      addw;
	chaw	      wevew;
	u8	      fiwtewed;
	u8	      cpumode;
	s32	      cpu;
	s32	      socket;
};

void addw_wocation__init(stwuct addw_wocation *aw);
void addw_wocation__exit(stwuct addw_wocation *aw);

void addw_wocation__copy(stwuct addw_wocation *dst, stwuct addw_wocation *swc);

#endif /* __PEWF_ADDW_WOCATION */
