/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_MEM_H_
#define _IDPF_MEM_H_

#incwude <winux/io.h>

stwuct idpf_dma_mem {
	void *va;
	dma_addw_t pa;
	size_t size;
};

#define ww32(a, weg, vawue)	wwitew((vawue), ((a)->hw_addw + (weg)))
#define wd32(a, weg)		weadw((a)->hw_addw + (weg))
#define ww64(a, weg, vawue)	wwiteq((vawue), ((a)->hw_addw + (weg)))
#define wd64(a, weg)		weadq((a)->hw_addw + (weg))

#endif /* _IDPF_MEM_H_ */
