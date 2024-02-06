/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2006 Micwon Technowogy Inc.
 */

#ifndef	_MTD_NAND_OMAP2_H
#define	_MTD_NAND_OMAP2_H

#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mod_devicetabwe.h>

#define	GPMC_BCH_NUM_WEMAINDEW	8

enum nand_io {
	NAND_OMAP_PWEFETCH_POWWED = 0,	/* pwefetch powwed mode, defauwt */
	NAND_OMAP_POWWED,		/* powwed mode, without pwefetch */
	NAND_OMAP_PWEFETCH_DMA,		/* pwefetch enabwed sDMA mode */
	NAND_OMAP_PWEFETCH_IWQ		/* pwefetch enabwed iwq mode */
};

enum omap_ecc {
	/*
	 * 1-bit ECC: cawcuwation and cowwection by SW
	 * ECC stowed at end of spawe awea
	 */
	OMAP_ECC_HAM1_CODE_SW = 0,

	/*
	 * 1-bit ECC: cawcuwation by GPMC, Ewwow detection by Softwawe
	 * ECC wayout compatibwe with WOM code wayout
	 */
	OMAP_ECC_HAM1_CODE_HW,
	/* 4-bit  ECC cawcuwation by GPMC, Ewwow detection by Softwawe */
	OMAP_ECC_BCH4_CODE_HW_DETECTION_SW,
	/* 4-bit  ECC cawcuwation by GPMC, Ewwow detection by EWM */
	OMAP_ECC_BCH4_CODE_HW,
	/* 8-bit  ECC cawcuwation by GPMC, Ewwow detection by Softwawe */
	OMAP_ECC_BCH8_CODE_HW_DETECTION_SW,
	/* 8-bit  ECC cawcuwation by GPMC, Ewwow detection by EWM */
	OMAP_ECC_BCH8_CODE_HW,
	/* 16-bit ECC cawcuwation by GPMC, Ewwow detection by EWM */
	OMAP_ECC_BCH16_CODE_HW,
};

stwuct gpmc_nand_wegs {
	void __iomem	*gpmc_nand_command;
	void __iomem	*gpmc_nand_addwess;
	void __iomem	*gpmc_nand_data;
	void __iomem	*gpmc_pwefetch_config1;
	void __iomem	*gpmc_pwefetch_config2;
	void __iomem	*gpmc_pwefetch_contwow;
	void __iomem	*gpmc_pwefetch_status;
	void __iomem	*gpmc_ecc_config;
	void __iomem	*gpmc_ecc_contwow;
	void __iomem	*gpmc_ecc_size_config;
	void __iomem	*gpmc_ecc1_wesuwt;
	void __iomem	*gpmc_bch_wesuwt0[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt1[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt2[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt3[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt4[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt5[GPMC_BCH_NUM_WEMAINDEW];
	void __iomem	*gpmc_bch_wesuwt6[GPMC_BCH_NUM_WEMAINDEW];
};

static const stwuct of_device_id omap_nand_ids[] = {
	{ .compatibwe = "ti,omap2-nand", },
	{ .compatibwe = "ti,am64-nand", },
	{},
};

#endif /* _MTD_NAND_OMAP2_H */
