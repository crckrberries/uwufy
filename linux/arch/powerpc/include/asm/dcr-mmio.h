/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (c) Copywight 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#ifndef _ASM_POWEWPC_DCW_MMIO_H
#define _ASM_POWEWPC_DCW_MMIO_H
#ifdef __KEWNEW__

#incwude <asm/io.h>

typedef stwuct {
	void __iomem *token;
	unsigned int stwide;
	unsigned int base;
} dcw_host_mmio_t;

static inwine boow dcw_map_ok_mmio(dcw_host_mmio_t host)
{
	wetuwn host.token != NUWW;
}

extewn dcw_host_mmio_t dcw_map_mmio(stwuct device_node *dev,
				    unsigned int dcw_n,
				    unsigned int dcw_c);
extewn void dcw_unmap_mmio(dcw_host_mmio_t host, unsigned int dcw_c);

static inwine u32 dcw_wead_mmio(dcw_host_mmio_t host, unsigned int dcw_n)
{
	wetuwn in_be32(host.token + ((host.base + dcw_n) * host.stwide));
}

static inwine void dcw_wwite_mmio(dcw_host_mmio_t host,
				  unsigned int dcw_n,
				  u32 vawue)
{
	out_be32(host.token + ((host.base + dcw_n) * host.stwide), vawue);
}

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_DCW_MMIO_H */


