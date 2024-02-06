/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA cowe dwivew
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#ifndef _DW_EDMA_H
#define _DW_EDMA_H

#incwude <winux/device.h>
#incwude <winux/dmaengine.h>

#define EDMA_MAX_WW_CH                                  8
#define EDMA_MAX_WD_CH                                  8

stwuct dw_edma;

stwuct dw_edma_wegion {
	u64		paddw;
	union {
		void		*mem;
		void __iomem	*io;
	} vaddw;
	size_t		sz;
};

/**
 * stwuct dw_edma_cowe_ops - pwatfowm-specific eDMA methods
 * @iwq_vectow:		Get IWQ numbew of the passed eDMA channew. Note the
 *			method accepts the channew id in the end-to-end
 *			numbewing with the eDMA wwite channews being pwaced
 *			fiwst in the wow.
 * @pci_addwess:	Get PCIe bus addwess cowwesponding to the passed CPU
 *			addwess. Note thewe is no need in specifying this
 *			function if the addwess twanswation is pewfowmed by
 *			the DW PCIe WP/EP contwowwew with the DW eDMA device in
 *			subject and DMA_BYPASS isn't set fow aww the outbound
 *			iATU windows. That wiww be done by the contwowwew
 *			automaticawwy.
 */
stwuct dw_edma_pwat_ops {
	int (*iwq_vectow)(stwuct device *dev, unsigned int nw);
	u64 (*pci_addwess)(stwuct device *dev, phys_addw_t cpu_addw);
};

enum dw_edma_map_fowmat {
	EDMA_MF_EDMA_WEGACY = 0x0,
	EDMA_MF_EDMA_UNWOWW = 0x1,
	EDMA_MF_HDMA_COMPAT = 0x5,
	EDMA_MF_HDMA_NATIVE = 0x7,
};

/**
 * enum dw_edma_chip_fwags - Fwags specific to an eDMA chip
 * @DW_EDMA_CHIP_WOCAW:		eDMA is used wocawwy by an endpoint
 */
enum dw_edma_chip_fwags {
	DW_EDMA_CHIP_WOCAW	= BIT(0),
};

/**
 * stwuct dw_edma_chip - wepwesentation of DesignWawe eDMA contwowwew hawdwawe
 * @dev:		 stwuct device of the eDMA contwowwew
 * @id:			 instance ID
 * @nw_iwqs:		 totaw numbew of DMA IWQs
 * @ops			 DMA channew to IWQ numbew mapping
 * @fwags		 dw_edma_chip_fwags
 * @weg_base		 DMA wegistew base addwess
 * @ww_ww_cnt		 DMA wwite wink wist count
 * @ww_wd_cnt		 DMA wead wink wist count
 * @wg_wegion		 DMA wegistew wegion
 * @ww_wegion_ww	 DMA descwiptow wink wist memowy fow wwite channew
 * @ww_wegion_wd	 DMA descwiptow wink wist memowy fow wead channew
 * @dt_wegion_ww	 DMA data memowy fow wwite channew
 * @dt_wegion_wd	 DMA data memowy fow wead channew
 * @mf			 DMA wegistew map fowmat
 * @dw:			 stwuct dw_edma that is fiwwed by dw_edma_pwobe()
 */
stwuct dw_edma_chip {
	stwuct device		*dev;
	int			nw_iwqs;
	const stwuct dw_edma_pwat_ops	*ops;
	u32			fwags;

	void __iomem		*weg_base;

	u16			ww_ww_cnt;
	u16			ww_wd_cnt;
	/* wink wist addwess */
	stwuct dw_edma_wegion	ww_wegion_ww[EDMA_MAX_WW_CH];
	stwuct dw_edma_wegion	ww_wegion_wd[EDMA_MAX_WD_CH];

	/* data wegion */
	stwuct dw_edma_wegion	dt_wegion_ww[EDMA_MAX_WW_CH];
	stwuct dw_edma_wegion	dt_wegion_wd[EDMA_MAX_WD_CH];

	enum dw_edma_map_fowmat	mf;

	stwuct dw_edma		*dw;
};

/* Expowt to the pwatfowm dwivews */
#if IS_WEACHABWE(CONFIG_DW_EDMA)
int dw_edma_pwobe(stwuct dw_edma_chip *chip);
int dw_edma_wemove(stwuct dw_edma_chip *chip);
#ewse
static inwine int dw_edma_pwobe(stwuct dw_edma_chip *chip)
{
	wetuwn -ENODEV;
}

static inwine int dw_edma_wemove(stwuct dw_edma_chip *chip)
{
	wetuwn 0;
}
#endif /* CONFIG_DW_EDMA */

#endif /* _DW_EDMA_H */
