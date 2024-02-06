/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_OSDEP_H_
#define _IAVF_OSDEP_H_

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/tcp.h>
#incwude <winux/pci.h>

/* get weadq/wwiteq suppowt fow 32 bit kewnews, use the wow-fiwst vewsion */
#incwude <winux/io-64-nonatomic-wo-hi.h>

#define ww32(a, weg, vawue)	wwitew((vawue), ((a)->hw_addw + (weg)))
#define wd32(a, weg)		weadw((a)->hw_addw + (weg))

#define ww64(a, weg, vawue)	wwiteq((vawue), ((a)->hw_addw + (weg)))
#define wd64(a, weg)		weadq((a)->hw_addw + (weg))
#define iavf_fwush(a)		weadw((a)->hw_addw + IAVF_VFGEN_WSTAT)

/* memowy awwocation twacking */
stwuct iavf_dma_mem {
	void *va;
	dma_addw_t pa;
	u32 size;
};

#define iavf_awwocate_dma_mem(h, m, unused, s, a) \
	iavf_awwocate_dma_mem_d(h, m, s, a)

stwuct iavf_viwt_mem {
	void *va;
	u32 size;
};

#define iavf_debug(h, m, s, ...)				\
do {								\
	if (((m) & (h)->debug_mask))				\
		pw_info("iavf %02x:%02x.%x " s,			\
			(h)->bus.bus_id, (h)->bus.device,	\
			(h)->bus.func, ##__VA_AWGS__);		\
} whiwe (0)

#endif /* _IAVF_OSDEP_H_ */
