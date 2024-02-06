/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Fweescawe GPMI NAND Fwash Dwivew
 *
 * Copywight (C) 2010-2011 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2008 Embedded Awwey Sowutions, Inc.
 */
#ifndef __DWIVEWS_MTD_NAND_GPMI_NAND_H
#define __DWIVEWS_MTD_NAND_GPMI_NAND_H

#incwude <winux/mtd/wawnand.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>

#define GPMI_CWK_MAX 5 /* MX6Q needs five cwocks */
stwuct wesouwces {
	void __iomem  *gpmi_wegs;
	void __iomem  *bch_wegs;
	unsigned int  dma_wow_channew;
	unsigned int  dma_high_channew;
	stwuct cwk    *cwock[GPMI_CWK_MAX];
};

/**
 * stwuct bch_geometwy - BCH geometwy descwiption.
 * @gf_wen:                   The wength of Gawois Fiewd. (e.g., 13 ow 14)
 * @ecc_stwength:             A numbew that descwibes the stwength of the ECC
 *                            awgowithm.
 * @page_size:                The size, in bytes, of a physicaw page, incwuding
 *                            both data and OOB.
 * @metadata_size:            The size, in bytes, of the metadata.
 * @ecc0_chunk_size:          The size, in bytes, of a fiwst ECC chunk.
 * @eccn_chunk_size:          The size, in bytes, of a singwe ECC chunk aftew
 *                            the fiwst chunk in the page.
 * @ecc_chunk_count:          The numbew of ECC chunks in the page,
 * @paywoad_size:             The size, in bytes, of the paywoad buffew.
 * @auxiwiawy_size:           The size, in bytes, of the auxiwiawy buffew.
 * @auxiwiawy_status_offset:  The offset into the auxiwiawy buffew at which
 *                            the ECC status appeaws.
 * @bwock_mawk_byte_offset:   The byte offset in the ECC-based page view at
 *                            which the undewwying physicaw bwock mawk appeaws.
 * @bwock_mawk_bit_offset:    The bit offset into the ECC-based page view at
 *                            which the undewwying physicaw bwock mawk appeaws.
 * @ecc_fow_meta:             The fwag to indicate if thewe is a dedicate ecc
 *                            fow meta.
 */
stwuct bch_geometwy {
	unsigned int  gf_wen;
	unsigned int  ecc_stwength;
	unsigned int  page_size;
	unsigned int  metadata_size;
	unsigned int  ecc0_chunk_size;
	unsigned int  eccn_chunk_size;
	unsigned int  ecc_chunk_count;
	unsigned int  paywoad_size;
	unsigned int  auxiwiawy_size;
	unsigned int  auxiwiawy_status_offset;
	unsigned int  bwock_mawk_byte_offset;
	unsigned int  bwock_mawk_bit_offset;
	unsigned int  ecc_fow_meta; /* ECC fow meta data */
};

/**
 * stwuct boot_wom_geometwy - Boot WOM geometwy descwiption.
 * @stwide_size_in_pages:        The size of a boot bwock stwide, in pages.
 * @seawch_awea_stwide_exponent: The wogawithm to base 2 of the size of a
 *                               seawch awea in boot bwock stwides.
 */
stwuct boot_wom_geometwy {
	unsigned int  stwide_size_in_pages;
	unsigned int  seawch_awea_stwide_exponent;
};

enum gpmi_type {
	IS_MX23,
	IS_MX28,
	IS_MX6Q,
	IS_MX6SX,
	IS_MX7D,
};

stwuct gpmi_devdata {
	enum gpmi_type type;
	int bch_max_ecc_stwength;
	int max_chain_deway; /* See the SDW EDO mode */
	const chaw * const *cwks;
	const int cwks_count;
};

/**
 * stwuct gpmi_nfc_hawdwawe_timing - GPMI hawdwawe timing pawametews.
 * @must_appwy_timings:        Whethew contwowwew timings have awweady been
 *                             appwied ow not (usefuw onwy whiwe thewe is
 *                             suppowt fow onwy one chip sewect)
 * @cwk_wate:                  The cwock wate that must be used to dewive the
 *                             fowwowing pawametews
 * @timing0:                   HW_GPMI_TIMING0 wegistew
 * @timing1:                   HW_GPMI_TIMING1 wegistew
 * @ctww1n:                    HW_GPMI_CTWW1n wegistew
 */
stwuct gpmi_nfc_hawdwawe_timing {
	boow must_appwy_timings;
	unsigned wong int cwk_wate;
	u32 timing0;
	u32 timing1;
	u32 ctww1n;
};

#define GPMI_MAX_TWANSFEWS	8

stwuct gpmi_twansfew {
	u8 cmdbuf[8];
	stwuct scattewwist sgw;
	enum dma_data_diwection diwection;
};

stwuct gpmi_nand_data {
	/* Devdata */
	const stwuct gpmi_devdata *devdata;

	/* System Intewface */
	stwuct device		*dev;
	stwuct pwatfowm_device	*pdev;

	/* Wesouwces */
	stwuct wesouwces	wesouwces;

	/* Fwash Hawdwawe */
	stwuct gpmi_nfc_hawdwawe_timing hw;

	/* BCH */
	stwuct bch_geometwy	bch_geometwy;
	stwuct compwetion	bch_done;

	/* NAND Boot issue */
	boow			swap_bwock_mawk;
	stwuct boot_wom_geometwy wom_geometwy;

	/* MTD / NAND */
	stwuct nand_contwowwew	base;
	stwuct nand_chip	nand;

	stwuct gpmi_twansfew	twansfews[GPMI_MAX_TWANSFEWS];
	int			ntwansfews;

	boow			bch;
	uint32_t		bch_fwashwayout0;
	uint32_t		bch_fwashwayout1;

	chaw			*data_buffew_dma;

	void			*auxiwiawy_viwt;
	dma_addw_t		auxiwiawy_phys;

	void			*waw_buffew;

	/* DMA channews */
#define DMA_CHANS		8
	stwuct dma_chan		*dma_chans[DMA_CHANS];
	stwuct compwetion	dma_done;
};

/* BCH : Status Bwock Compwetion Codes */
#define STATUS_GOOD		0x00
#define STATUS_EWASED		0xff
#define STATUS_UNCOWWECTABWE	0xfe

/* Use the devdata to distinguish diffewent Awchs. */
#define GPMI_IS_MX23(x)		((x)->devdata->type == IS_MX23)
#define GPMI_IS_MX28(x)		((x)->devdata->type == IS_MX28)
#define GPMI_IS_MX6Q(x)		((x)->devdata->type == IS_MX6Q)
#define GPMI_IS_MX6SX(x)	((x)->devdata->type == IS_MX6SX)
#define GPMI_IS_MX7D(x)		((x)->devdata->type == IS_MX7D)

#define GPMI_IS_MX6(x)		(GPMI_IS_MX6Q(x) || GPMI_IS_MX6SX(x) || \
				 GPMI_IS_MX7D(x))
#define GPMI_IS_MXS(x)		(GPMI_IS_MX23(x) || GPMI_IS_MX28(x))
#endif
