// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2006  Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/dma-diwect.h>
#incwude <asm/ip32/cwime.h>

/*
 * Few notes.
 * 1. CPU sees memowy as two chunks: 0-256M@0x0, and the west @0x40000000+256M
 * 2. PCI sees memowy as one big chunk @0x0 (ow we couwd use 0x40000000 fow
 *    native-endian)
 * 3. Aww othew devices see memowy as one big chunk at 0x40000000
 * 4. Non-PCI devices wiww pass NUWW as stwuct device*
 *
 * Thus we twanswate diffewentwy, depending on device.
 */

#define WAM_OFFSET_MASK 0x3fffffffUW

dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	dma_addw_t dma_addw = paddw & WAM_OFFSET_MASK;

	if (!dev)
		dma_addw += CWIME_HI_MEM_BASE;
	wetuwn dma_addw;
}

phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t dma_addw)
{
	phys_addw_t paddw = dma_addw & WAM_OFFSET_MASK;

	if (dma_addw >= 256*1024*1024)
		paddw += CWIME_HI_MEM_BASE;
	wetuwn paddw;
}
