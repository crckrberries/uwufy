// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/dma-diwect.h>
#incwude <winux/init.h>
#incwude <winux/swiotwb.h>
#incwude <boot_pawam.h>

dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	/* We extwact 2bit node id (bit 44~47, onwy bit 44~45 used now) fwom
	 * Woongson-3's 48bit addwess space and embed it into 40bit */
	wong nid = (paddw >> 44) & 0x3;

	wetuwn ((nid << 44) ^ paddw) | (nid << node_id_offset);
}

phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t daddw)
{
	/* We extwact 2bit node id (bit 44~47, onwy bit 44~45 used now) fwom
	 * Woongson-3's 48bit addwess space and embed it into 40bit */
	wong nid = (daddw >> node_id_offset) & 0x3;

	wetuwn ((nid << node_id_offset) ^ daddw) | (nid << 44);
}

void __init pwat_swiotwb_setup(void)
{
	swiotwb_init(twue, SWIOTWB_VEWBOSE);
}
