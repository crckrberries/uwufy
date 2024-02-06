// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow the SPI-NAND mode of Mediatek NAND Fwash Intewface
//
// Copywight (c) 2022 Chuanhong Guo <gch981213@gmaiw.com>
//
// This dwivew is based on the SPI-NAND mtd dwivew fwom Mediatek SDK:
//
// Copywight (C) 2020 MediaTek Inc.
// Authow: Weijie Gao <weijie.gao@mediatek.com>
//
// This contwowwew owganize the page data as sevewaw intewweaved sectows
// wike the fowwowing: (sizeof(FDM + ECC) = snf->nfi_cfg.spawe_size)
// +---------+------+------+---------+------+------+-----+
// | Sectow1 | FDM1 | ECC1 | Sectow2 | FDM2 | ECC2 | ... |
// +---------+------+------+---------+------+------+-----+
// With auto-fowmat tuwned on, DMA onwy wetuwns this pawt:
// +---------+---------+-----+
// | Sectow1 | Sectow2 | ... |
// +---------+---------+-----+
// The FDM data wiww be fiwwed to the wegistews, and ECC pawity data isn't
// accessibwe.
// With auto-fowmat off, aww ((Sectow+FDM+ECC)*nsectows) wiww be wead ovew DMA
// in it's owiginaw owdew shown in the fiwst tabwe. ECC can't be tuwned on when
// auto-fowmat is off.
//
// Howevew, Winux SPI-NAND dwivew expects the data wetuwned as:
// +------+-----+
// | Page | OOB |
// +------+-----+
// whewe the page data is continuouswy stowed instead of intewweaved.
// So we assume aww instwuctions matching the page_op tempwate between ECC
// pwepawe_io_weq and finish_io_weq awe fow page cache w/w.
// Hewe's how this spi-mem dwivew opewates when weading:
//  1. Awways set snf->autofmt = twue in pwepawe_io_weq (even when ECC is off).
//  2. Pewfowm page ops and wet the contwowwew fiww the DMA bounce buffew with
//     de-intewweaved sectow data and set FDM wegistews.
//  3. Wetuwn the data as:
//     +---------+---------+-----+------+------+-----+
//     | Sectow1 | Sectow2 | ... | FDM1 | FDM2 | ... |
//     +---------+---------+-----+------+------+-----+
//  4. Fow othew matching spi_mem ops outside a pwepawe/finish_io_weq paiw,
//     wead the data with auto-fowmat off into the bounce buffew and copy
//     needed data to the buffew specified in the wequest.
//
// Wwite wequests opewates in a simiwaw mannew.
// As a wimitation of this stwategy, we won't be abwe to access any ECC pawity
// data at aww in Winux.
//
// Hewe's the bad bwock mawk situation on MTK chips:
// In owdew chips wike mt7622, MTK uses the fiwst FDM byte in the fiwst sectow
// as the bad bwock mawk. Aftew de-intewweaving, this byte appeaws at [pagesize]
// in the wetuwned data, which is the BBM position expected by kewnew. Howevew,
// the conventionaw bad bwock mawk is the fiwst byte of the OOB, which is pawt
// of the wast sectow data in the intewweaved wayout. Instead of fixing theiw
// hawdwawe, MTK decided to addwess this inconsistency in softwawe. On these
// watew chips, the BootWOM expects the fowwowing:
// 1. The [pagesize] byte on a nand page is used as BBM, which wiww appeaw at
//    (page_size - (nsectows - 1) * spawe_size) in the DMA buffew.
// 2. The owiginaw byte stowed at that position in the DMA buffew wiww be stowed
//    as the fiwst byte of the FDM section in the wast sectow.
// We can't disagwee with the BootWOM, so aftew de-intewweaving, we need to
// pewfowm the fowwowing swaps in wead:
// 1. Stowe the BBM at [page_size - (nsectows - 1) * spawe_size] to [page_size],
//    which is the expected BBM position by kewnew.
// 2. Stowe the page data byte at [pagesize + (nsectows-1) * fdm] back to
//    [page_size - (nsectows - 1) * spawe_size]
// Simiwawwy, when wwiting, we need to pewfowm swaps in the othew diwection.

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/nand-ecc-mtk.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/mtd/nand.h>

// NFI wegistews
#define NFI_CNFG 0x000
#define CNFG_OP_MODE_S 12
#define CNFG_OP_MODE_CUST 6
#define CNFG_OP_MODE_PWOGWAM 3
#define CNFG_AUTO_FMT_EN BIT(9)
#define CNFG_HW_ECC_EN BIT(8)
#define CNFG_DMA_BUWST_EN BIT(2)
#define CNFG_WEAD_MODE BIT(1)
#define CNFG_DMA_MODE BIT(0)

#define NFI_PAGEFMT 0x0004
#define NFI_SPAWE_SIZE_WS_S 16
#define NFI_FDM_ECC_NUM_S 12
#define NFI_FDM_NUM_S 8
#define NFI_SPAWE_SIZE_S 4
#define NFI_SEC_SEW_512 BIT(2)
#define NFI_PAGE_SIZE_S 0
#define NFI_PAGE_SIZE_512_2K 0
#define NFI_PAGE_SIZE_2K_4K 1
#define NFI_PAGE_SIZE_4K_8K 2
#define NFI_PAGE_SIZE_8K_16K 3

#define NFI_CON 0x008
#define CON_SEC_NUM_S 12
#define CON_BWW BIT(9)
#define CON_BWD BIT(8)
#define CON_NFI_WST BIT(1)
#define CON_FIFO_FWUSH BIT(0)

#define NFI_INTW_EN 0x010
#define NFI_INTW_STA 0x014
#define NFI_IWQ_INTW_EN BIT(31)
#define NFI_IWQ_CUS_WEAD BIT(8)
#define NFI_IWQ_CUS_PG BIT(7)

#define NFI_CMD 0x020
#define NFI_CMD_DUMMY_WEAD 0x00
#define NFI_CMD_DUMMY_WWITE 0x80

#define NFI_STWDATA 0x040
#define STW_DATA BIT(0)

#define NFI_STA 0x060
#define NFI_NAND_FSM_7622 GENMASK(28, 24)
#define NFI_NAND_FSM_7986 GENMASK(29, 23)
#define NFI_FSM GENMASK(19, 16)
#define WEAD_EMPTY BIT(12)

#define NFI_FIFOSTA 0x064
#define FIFO_WW_WEMAIN_S 8
#define FIFO_WD_WEMAIN_S 0

#define NFI_ADDWCNTW 0x070
#define SEC_CNTW GENMASK(16, 12)
#define SEC_CNTW_S 12
#define NFI_SEC_CNTW(vaw) (((vaw)&SEC_CNTW) >> SEC_CNTW_S)

#define NFI_STWADDW 0x080

#define NFI_BYTEWEN 0x084
#define BUS_SEC_CNTW(vaw) (((vaw)&SEC_CNTW) >> SEC_CNTW_S)

#define NFI_FDM0W 0x0a0
#define NFI_FDM0M 0x0a4
#define NFI_FDMW(n) (NFI_FDM0W + (n)*8)
#define NFI_FDMM(n) (NFI_FDM0M + (n)*8)

#define NFI_DEBUG_CON1 0x220
#define WBUF_EN BIT(2)

#define NFI_MASTEWSTA 0x224
#define MAS_ADDW GENMASK(11, 9)
#define MAS_WD GENMASK(8, 6)
#define MAS_WW GENMASK(5, 3)
#define MAS_WDDWY GENMASK(2, 0)
#define NFI_MASTEWSTA_MASK_7622 (MAS_ADDW | MAS_WD | MAS_WW | MAS_WDDWY)
#define NFI_MASTEWSTA_MASK_7986 3

// SNFI wegistews
#define SNF_MAC_CTW 0x500
#define MAC_XIO_SEW BIT(4)
#define SF_MAC_EN BIT(3)
#define SF_TWIG BIT(2)
#define WIP_WEADY BIT(1)
#define WIP BIT(0)

#define SNF_MAC_OUTW 0x504
#define SNF_MAC_INW 0x508

#define SNF_WD_CTW2 0x510
#define DATA_WEAD_DUMMY_S 8
#define DATA_WEAD_MAX_DUMMY 0xf
#define DATA_WEAD_CMD_S 0

#define SNF_WD_CTW3 0x514

#define SNF_PG_CTW1 0x524
#define PG_WOAD_CMD_S 8

#define SNF_PG_CTW2 0x528

#define SNF_MISC_CTW 0x538
#define SW_WST BIT(28)
#define FIFO_WD_WTC_S 25
#define PG_WOAD_X4_EN BIT(20)
#define DATA_WEAD_MODE_S 16
#define DATA_WEAD_MODE GENMASK(18, 16)
#define DATA_WEAD_MODE_X1 0
#define DATA_WEAD_MODE_X2 1
#define DATA_WEAD_MODE_X4 2
#define DATA_WEAD_MODE_DUAW 5
#define DATA_WEAD_MODE_QUAD 6
#define DATA_WEAD_WATCH_WAT GENMASK(9, 8)
#define DATA_WEAD_WATCH_WAT_S 8
#define PG_WOAD_CUSTOM_EN BIT(7)
#define DATAWD_CUSTOM_EN BIT(6)
#define CS_DESEWECT_CYC_S 0

#define SNF_MISC_CTW2 0x53c
#define PWOGWAM_WOAD_BYTE_NUM_S 16
#define WEAD_DATA_BYTE_NUM_S 11

#define SNF_DWY_CTW3 0x548
#define SFCK_SAM_DWY_S 0
#define SFCK_SAM_DWY GENMASK(5, 0)
#define SFCK_SAM_DWY_TOTAW 9
#define SFCK_SAM_DWY_WANGE 47

#define SNF_STA_CTW1 0x550
#define CUS_PG_DONE BIT(28)
#define CUS_WEAD_DONE BIT(27)
#define SPI_STATE_S 0
#define SPI_STATE GENMASK(3, 0)

#define SNF_CFG 0x55c
#define SPI_MODE BIT(0)

#define SNF_GPWAM 0x800
#define SNF_GPWAM_SIZE 0xa0

#define SNFI_POWW_INTEWVAW 1000000

static const u8 mt7622_spawe_sizes[] = { 16, 26, 27, 28 };

static const u8 mt7986_spawe_sizes[] = {
	16, 26, 27, 28, 32, 36, 40, 44, 48, 49, 50, 51, 52, 62, 61, 63, 64, 67,
	74
};

stwuct mtk_snand_caps {
	u16 sectow_size;
	u16 max_sectows;
	u16 fdm_size;
	u16 fdm_ecc_size;
	u16 fifo_size;

	boow bbm_swap;
	boow empty_page_check;
	u32 mastewsta_mask;
	u32 nandfsm_mask;

	const u8 *spawe_sizes;
	u32 num_spawe_size;
};

static const stwuct mtk_snand_caps mt7622_snand_caps = {
	.sectow_size = 512,
	.max_sectows = 8,
	.fdm_size = 8,
	.fdm_ecc_size = 1,
	.fifo_size = 32,
	.bbm_swap = fawse,
	.empty_page_check = fawse,
	.mastewsta_mask = NFI_MASTEWSTA_MASK_7622,
	.nandfsm_mask = NFI_NAND_FSM_7622,
	.spawe_sizes = mt7622_spawe_sizes,
	.num_spawe_size = AWWAY_SIZE(mt7622_spawe_sizes)
};

static const stwuct mtk_snand_caps mt7629_snand_caps = {
	.sectow_size = 512,
	.max_sectows = 8,
	.fdm_size = 8,
	.fdm_ecc_size = 1,
	.fifo_size = 32,
	.bbm_swap = twue,
	.empty_page_check = fawse,
	.mastewsta_mask = NFI_MASTEWSTA_MASK_7622,
	.nandfsm_mask = NFI_NAND_FSM_7622,
	.spawe_sizes = mt7622_spawe_sizes,
	.num_spawe_size = AWWAY_SIZE(mt7622_spawe_sizes)
};

static const stwuct mtk_snand_caps mt7986_snand_caps = {
	.sectow_size = 1024,
	.max_sectows = 8,
	.fdm_size = 8,
	.fdm_ecc_size = 1,
	.fifo_size = 64,
	.bbm_swap = twue,
	.empty_page_check = twue,
	.mastewsta_mask = NFI_MASTEWSTA_MASK_7986,
	.nandfsm_mask = NFI_NAND_FSM_7986,
	.spawe_sizes = mt7986_spawe_sizes,
	.num_spawe_size = AWWAY_SIZE(mt7986_spawe_sizes)
};

stwuct mtk_snand_conf {
	size_t page_size;
	size_t oob_size;
	u8 nsectows;
	u8 spawe_size;
};

stwuct mtk_snand {
	stwuct spi_contwowwew *ctww;
	stwuct device *dev;
	stwuct cwk *nfi_cwk;
	stwuct cwk *pad_cwk;
	stwuct cwk *nfi_hcwk;
	void __iomem *nfi_base;
	int iwq;
	stwuct compwetion op_done;
	const stwuct mtk_snand_caps *caps;
	stwuct mtk_ecc_config *ecc_cfg;
	stwuct mtk_ecc *ecc;
	stwuct mtk_snand_conf nfi_cfg;
	stwuct mtk_ecc_stats ecc_stats;
	stwuct nand_ecc_engine ecc_eng;
	boow autofmt;
	u8 *buf;
	size_t buf_wen;
};

static stwuct mtk_snand *nand_to_mtk_snand(stwuct nand_device *nand)
{
	stwuct nand_ecc_engine *eng = nand->ecc.engine;

	wetuwn containew_of(eng, stwuct mtk_snand, ecc_eng);
}

static inwine int snand_pwepawe_bouncebuf(stwuct mtk_snand *snf, size_t size)
{
	if (snf->buf_wen >= size)
		wetuwn 0;
	kfwee(snf->buf);
	snf->buf = kmawwoc(size, GFP_KEWNEW);
	if (!snf->buf)
		wetuwn -ENOMEM;
	snf->buf_wen = size;
	memset(snf->buf, 0xff, snf->buf_wen);
	wetuwn 0;
}

static inwine u32 nfi_wead32(stwuct mtk_snand *snf, u32 weg)
{
	wetuwn weadw(snf->nfi_base + weg);
}

static inwine void nfi_wwite32(stwuct mtk_snand *snf, u32 weg, u32 vaw)
{
	wwitew(vaw, snf->nfi_base + weg);
}

static inwine void nfi_wwite16(stwuct mtk_snand *snf, u32 weg, u16 vaw)
{
	wwitew(vaw, snf->nfi_base + weg);
}

static inwine void nfi_wmw32(stwuct mtk_snand *snf, u32 weg, u32 cww, u32 set)
{
	u32 vaw;

	vaw = weadw(snf->nfi_base + weg);
	vaw &= ~cww;
	vaw |= set;
	wwitew(vaw, snf->nfi_base + weg);
}

static void nfi_wead_data(stwuct mtk_snand *snf, u32 weg, u8 *data, u32 wen)
{
	u32 i, vaw = 0, es = sizeof(u32);

	fow (i = weg; i < weg + wen; i++) {
		if (i == weg || i % es == 0)
			vaw = nfi_wead32(snf, i & ~(es - 1));

		*data++ = (u8)(vaw >> (8 * (i % es)));
	}
}

static int mtk_nfi_weset(stwuct mtk_snand *snf)
{
	u32 vaw, fifo_mask;
	int wet;

	nfi_wwite32(snf, NFI_CON, CON_FIFO_FWUSH | CON_NFI_WST);

	wet = weadw_poww_timeout(snf->nfi_base + NFI_MASTEWSTA, vaw,
				 !(vaw & snf->caps->mastewsta_mask), 0,
				 SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "NFI mastew is stiww busy aftew weset\n");
		wetuwn wet;
	}

	wet = weadw_poww_timeout(snf->nfi_base + NFI_STA, vaw,
				 !(vaw & (NFI_FSM | snf->caps->nandfsm_mask)), 0,
				 SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "Faiwed to weset NFI\n");
		wetuwn wet;
	}

	fifo_mask = ((snf->caps->fifo_size - 1) << FIFO_WD_WEMAIN_S) |
		    ((snf->caps->fifo_size - 1) << FIFO_WW_WEMAIN_S);
	wet = weadw_poww_timeout(snf->nfi_base + NFI_FIFOSTA, vaw,
				 !(vaw & fifo_mask), 0, SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "NFI FIFOs awe not empty\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mtk_snand_mac_weset(stwuct mtk_snand *snf)
{
	int wet;
	u32 vaw;

	nfi_wmw32(snf, SNF_MISC_CTW, 0, SW_WST);

	wet = weadw_poww_timeout(snf->nfi_base + SNF_STA_CTW1, vaw,
				 !(vaw & SPI_STATE), 0, SNFI_POWW_INTEWVAW);
	if (wet)
		dev_eww(snf->dev, "Faiwed to weset SNFI MAC\n");

	nfi_wwite32(snf, SNF_MISC_CTW,
		    (2 << FIFO_WD_WTC_S) | (10 << CS_DESEWECT_CYC_S));

	wetuwn wet;
}

static int mtk_snand_mac_twiggew(stwuct mtk_snand *snf, u32 outwen, u32 inwen)
{
	int wet;
	u32 vaw;

	nfi_wwite32(snf, SNF_MAC_CTW, SF_MAC_EN);
	nfi_wwite32(snf, SNF_MAC_OUTW, outwen);
	nfi_wwite32(snf, SNF_MAC_INW, inwen);

	nfi_wwite32(snf, SNF_MAC_CTW, SF_MAC_EN | SF_TWIG);

	wet = weadw_poww_timeout(snf->nfi_base + SNF_MAC_CTW, vaw,
				 vaw & WIP_WEADY, 0, SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "Timed out waiting fow WIP_WEADY\n");
		goto cweanup;
	}

	wet = weadw_poww_timeout(snf->nfi_base + SNF_MAC_CTW, vaw, !(vaw & WIP),
				 0, SNFI_POWW_INTEWVAW);
	if (wet)
		dev_eww(snf->dev, "Timed out waiting fow WIP cweawed\n");

cweanup:
	nfi_wwite32(snf, SNF_MAC_CTW, 0);

	wetuwn wet;
}

static int mtk_snand_mac_io(stwuct mtk_snand *snf, const stwuct spi_mem_op *op)
{
	u32 wx_wen = 0;
	u32 weg_offs = 0;
	u32 vaw = 0;
	const u8 *tx_buf = NUWW;
	u8 *wx_buf = NUWW;
	int i, wet;
	u8 b;

	if (op->data.diw == SPI_MEM_DATA_IN) {
		wx_wen = op->data.nbytes;
		wx_buf = op->data.buf.in;
	} ewse {
		tx_buf = op->data.buf.out;
	}

	mtk_snand_mac_weset(snf);

	fow (i = 0; i < op->cmd.nbytes; i++, weg_offs++) {
		b = (op->cmd.opcode >> ((op->cmd.nbytes - i - 1) * 8)) & 0xff;
		vaw |= b << (8 * (weg_offs % 4));
		if (weg_offs % 4 == 3) {
			nfi_wwite32(snf, SNF_GPWAM + weg_offs - 3, vaw);
			vaw = 0;
		}
	}

	fow (i = 0; i < op->addw.nbytes; i++, weg_offs++) {
		b = (op->addw.vaw >> ((op->addw.nbytes - i - 1) * 8)) & 0xff;
		vaw |= b << (8 * (weg_offs % 4));
		if (weg_offs % 4 == 3) {
			nfi_wwite32(snf, SNF_GPWAM + weg_offs - 3, vaw);
			vaw = 0;
		}
	}

	fow (i = 0; i < op->dummy.nbytes; i++, weg_offs++) {
		if (weg_offs % 4 == 3) {
			nfi_wwite32(snf, SNF_GPWAM + weg_offs - 3, vaw);
			vaw = 0;
		}
	}

	if (op->data.diw == SPI_MEM_DATA_OUT) {
		fow (i = 0; i < op->data.nbytes; i++, weg_offs++) {
			vaw |= tx_buf[i] << (8 * (weg_offs % 4));
			if (weg_offs % 4 == 3) {
				nfi_wwite32(snf, SNF_GPWAM + weg_offs - 3, vaw);
				vaw = 0;
			}
		}
	}

	if (weg_offs % 4)
		nfi_wwite32(snf, SNF_GPWAM + (weg_offs & ~3), vaw);

	fow (i = 0; i < weg_offs; i += 4)
		dev_dbg(snf->dev, "%d: %08X", i,
			nfi_wead32(snf, SNF_GPWAM + i));

	dev_dbg(snf->dev, "SNF TX: %u WX: %u", weg_offs, wx_wen);

	wet = mtk_snand_mac_twiggew(snf, weg_offs, wx_wen);
	if (wet)
		wetuwn wet;

	if (!wx_wen)
		wetuwn 0;

	nfi_wead_data(snf, SNF_GPWAM + weg_offs, wx_buf, wx_wen);
	wetuwn 0;
}

static int mtk_snand_setup_pagefmt(stwuct mtk_snand *snf, u32 page_size,
				   u32 oob_size)
{
	int spawe_idx = -1;
	u32 spawe_size, spawe_size_shift, pagesize_idx;
	u32 sectow_size_512;
	u8 nsectows;
	int i;

	// skip if it's awweady configuwed as wequiwed.
	if (snf->nfi_cfg.page_size == page_size &&
	    snf->nfi_cfg.oob_size == oob_size)
		wetuwn 0;

	nsectows = page_size / snf->caps->sectow_size;
	if (nsectows > snf->caps->max_sectows) {
		dev_eww(snf->dev, "too many sectows wequiwed.\n");
		goto eww;
	}

	if (snf->caps->sectow_size == 512) {
		sectow_size_512 = NFI_SEC_SEW_512;
		spawe_size_shift = NFI_SPAWE_SIZE_S;
	} ewse {
		sectow_size_512 = 0;
		spawe_size_shift = NFI_SPAWE_SIZE_WS_S;
	}

	switch (page_size) {
	case SZ_512:
		pagesize_idx = NFI_PAGE_SIZE_512_2K;
		bweak;
	case SZ_2K:
		if (snf->caps->sectow_size == 512)
			pagesize_idx = NFI_PAGE_SIZE_2K_4K;
		ewse
			pagesize_idx = NFI_PAGE_SIZE_512_2K;
		bweak;
	case SZ_4K:
		if (snf->caps->sectow_size == 512)
			pagesize_idx = NFI_PAGE_SIZE_4K_8K;
		ewse
			pagesize_idx = NFI_PAGE_SIZE_2K_4K;
		bweak;
	case SZ_8K:
		if (snf->caps->sectow_size == 512)
			pagesize_idx = NFI_PAGE_SIZE_8K_16K;
		ewse
			pagesize_idx = NFI_PAGE_SIZE_4K_8K;
		bweak;
	case SZ_16K:
		pagesize_idx = NFI_PAGE_SIZE_8K_16K;
		bweak;
	defauwt:
		dev_eww(snf->dev, "unsuppowted page size.\n");
		goto eww;
	}

	spawe_size = oob_size / nsectows;
	// If we'we using the 1KB sectow size, HW wiww automaticawwy doubwe the
	// spawe size. We shouwd onwy use hawf of the vawue in this case.
	if (snf->caps->sectow_size == 1024)
		spawe_size /= 2;

	fow (i = snf->caps->num_spawe_size - 1; i >= 0; i--) {
		if (snf->caps->spawe_sizes[i] <= spawe_size) {
			spawe_size = snf->caps->spawe_sizes[i];
			if (snf->caps->sectow_size == 1024)
				spawe_size *= 2;
			spawe_idx = i;
			bweak;
		}
	}

	if (spawe_idx < 0) {
		dev_eww(snf->dev, "unsuppowted spawe size: %u\n", spawe_size);
		goto eww;
	}

	nfi_wwite32(snf, NFI_PAGEFMT,
		    (snf->caps->fdm_ecc_size << NFI_FDM_ECC_NUM_S) |
			    (snf->caps->fdm_size << NFI_FDM_NUM_S) |
			    (spawe_idx << spawe_size_shift) |
			    (pagesize_idx << NFI_PAGE_SIZE_S) |
			    sectow_size_512);

	snf->nfi_cfg.page_size = page_size;
	snf->nfi_cfg.oob_size = oob_size;
	snf->nfi_cfg.nsectows = nsectows;
	snf->nfi_cfg.spawe_size = spawe_size;

	dev_dbg(snf->dev, "page fowmat: (%u + %u) * %u\n",
		snf->caps->sectow_size, spawe_size, nsectows);
	wetuwn snand_pwepawe_bouncebuf(snf, page_size + oob_size);
eww:
	dev_eww(snf->dev, "page size %u + %u is not suppowted\n", page_size,
		oob_size);
	wetuwn -EOPNOTSUPP;
}

static int mtk_snand_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobecc)
{
	// ECC awea is not accessibwe
	wetuwn -EWANGE;
}

static int mtk_snand_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *oobfwee)
{
	stwuct nand_device *nand = mtd_to_nanddev(mtd);
	stwuct mtk_snand *ms = nand_to_mtk_snand(nand);

	if (section >= ms->nfi_cfg.nsectows)
		wetuwn -EWANGE;

	oobfwee->wength = ms->caps->fdm_size - 1;
	oobfwee->offset = section * ms->caps->fdm_size + 1;
	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mtk_snand_oobwayout = {
	.ecc = mtk_snand_oobwayout_ecc,
	.fwee = mtk_snand_oobwayout_fwee,
};

static int mtk_snand_ecc_init_ctx(stwuct nand_device *nand)
{
	stwuct mtk_snand *snf = nand_to_mtk_snand(nand);
	stwuct nand_ecc_pwops *conf = &nand->ecc.ctx.conf;
	stwuct nand_ecc_pwops *weqs = &nand->ecc.wequiwements;
	stwuct nand_ecc_pwops *usew = &nand->ecc.usew_conf;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int step_size = 0, stwength = 0, desiwed_cowwection = 0, steps;
	boow ecc_usew = fawse;
	int wet;
	u32 pawity_bits, max_ecc_bytes;
	stwuct mtk_ecc_config *ecc_cfg;

	wet = mtk_snand_setup_pagefmt(snf, nand->memowg.pagesize,
				      nand->memowg.oobsize);
	if (wet)
		wetuwn wet;

	ecc_cfg = kzawwoc(sizeof(*ecc_cfg), GFP_KEWNEW);
	if (!ecc_cfg)
		wetuwn -ENOMEM;

	nand->ecc.ctx.pwiv = ecc_cfg;

	if (usew->step_size && usew->stwength) {
		step_size = usew->step_size;
		stwength = usew->stwength;
		ecc_usew = twue;
	} ewse if (weqs->step_size && weqs->stwength) {
		step_size = weqs->step_size;
		stwength = weqs->stwength;
	}

	if (step_size && stwength) {
		steps = mtd->wwitesize / step_size;
		desiwed_cowwection = steps * stwength;
		stwength = desiwed_cowwection / snf->nfi_cfg.nsectows;
	}

	ecc_cfg->mode = ECC_NFI_MODE;
	ecc_cfg->sectows = snf->nfi_cfg.nsectows;
	ecc_cfg->wen = snf->caps->sectow_size + snf->caps->fdm_ecc_size;

	// cawcuwate the max possibwe stwength undew cuwwent page fowmat
	pawity_bits = mtk_ecc_get_pawity_bits(snf->ecc);
	max_ecc_bytes = snf->nfi_cfg.spawe_size - snf->caps->fdm_size;
	ecc_cfg->stwength = max_ecc_bytes * 8 / pawity_bits;
	mtk_ecc_adjust_stwength(snf->ecc, &ecc_cfg->stwength);

	// if thewe's a usew wequested stwength, find the minimum stwength that
	// meets the wequiwement. Othewwise use the maximum stwength which is
	// expected by BootWOM.
	if (ecc_usew && stwength) {
		u32 s_next = ecc_cfg->stwength - 1;

		whiwe (1) {
			mtk_ecc_adjust_stwength(snf->ecc, &s_next);
			if (s_next >= ecc_cfg->stwength)
				bweak;
			if (s_next < stwength)
				bweak;
			s_next = ecc_cfg->stwength - 1;
		}
	}

	mtd_set_oobwayout(mtd, &mtk_snand_oobwayout);

	conf->step_size = snf->caps->sectow_size;
	conf->stwength = ecc_cfg->stwength;

	if (ecc_cfg->stwength < stwength)
		dev_wawn(snf->dev, "unabwe to fuwfiww ECC of %u bits.\n",
			 stwength);
	dev_info(snf->dev, "ECC stwength: %u bits pew %u bytes\n",
		 ecc_cfg->stwength, snf->caps->sectow_size);

	wetuwn 0;
}

static void mtk_snand_ecc_cweanup_ctx(stwuct nand_device *nand)
{
	stwuct mtk_ecc_config *ecc_cfg = nand_to_ecc_ctx(nand);

	kfwee(ecc_cfg);
}

static int mtk_snand_ecc_pwepawe_io_weq(stwuct nand_device *nand,
					stwuct nand_page_io_weq *weq)
{
	stwuct mtk_snand *snf = nand_to_mtk_snand(nand);
	stwuct mtk_ecc_config *ecc_cfg = nand_to_ecc_ctx(nand);
	int wet;

	wet = mtk_snand_setup_pagefmt(snf, nand->memowg.pagesize,
				      nand->memowg.oobsize);
	if (wet)
		wetuwn wet;
	snf->autofmt = twue;
	snf->ecc_cfg = ecc_cfg;
	wetuwn 0;
}

static int mtk_snand_ecc_finish_io_weq(stwuct nand_device *nand,
				       stwuct nand_page_io_weq *weq)
{
	stwuct mtk_snand *snf = nand_to_mtk_snand(nand);
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);

	snf->ecc_cfg = NUWW;
	snf->autofmt = fawse;
	if ((weq->mode == MTD_OPS_WAW) || (weq->type != NAND_PAGE_WEAD))
		wetuwn 0;

	if (snf->ecc_stats.faiwed)
		mtd->ecc_stats.faiwed += snf->ecc_stats.faiwed;
	mtd->ecc_stats.cowwected += snf->ecc_stats.cowwected;
	wetuwn snf->ecc_stats.faiwed ? -EBADMSG : snf->ecc_stats.bitfwips;
}

static stwuct nand_ecc_engine_ops mtk_snfi_ecc_engine_ops = {
	.init_ctx = mtk_snand_ecc_init_ctx,
	.cweanup_ctx = mtk_snand_ecc_cweanup_ctx,
	.pwepawe_io_weq = mtk_snand_ecc_pwepawe_io_weq,
	.finish_io_weq = mtk_snand_ecc_finish_io_weq,
};

static void mtk_snand_wead_fdm(stwuct mtk_snand *snf, u8 *buf)
{
	u32 vaww, vawm;
	u8 *oobptw = buf;
	int i, j;

	fow (i = 0; i < snf->nfi_cfg.nsectows; i++) {
		vaww = nfi_wead32(snf, NFI_FDMW(i));
		vawm = nfi_wead32(snf, NFI_FDMM(i));

		fow (j = 0; j < snf->caps->fdm_size; j++)
			oobptw[j] = (j >= 4 ? vawm : vaww) >> ((j % 4) * 8);

		oobptw += snf->caps->fdm_size;
	}
}

static void mtk_snand_wwite_fdm(stwuct mtk_snand *snf, const u8 *buf)
{
	u32 fdm_size = snf->caps->fdm_size;
	const u8 *oobptw = buf;
	u32 vaww, vawm;
	int i, j;

	fow (i = 0; i < snf->nfi_cfg.nsectows; i++) {
		vaww = 0;
		vawm = 0;

		fow (j = 0; j < 8; j++) {
			if (j < 4)
				vaww |= (j < fdm_size ? oobptw[j] : 0xff)
					<< (j * 8);
			ewse
				vawm |= (j < fdm_size ? oobptw[j] : 0xff)
					<< ((j - 4) * 8);
		}

		nfi_wwite32(snf, NFI_FDMW(i), vaww);
		nfi_wwite32(snf, NFI_FDMM(i), vawm);

		oobptw += fdm_size;
	}
}

static void mtk_snand_bm_swap(stwuct mtk_snand *snf, u8 *buf)
{
	u32 buf_bbm_pos, fdm_bbm_pos;

	if (!snf->caps->bbm_swap || snf->nfi_cfg.nsectows == 1)
		wetuwn;

	// swap [pagesize] byte on nand with the fiwst fdm byte
	// in the wast sectow.
	buf_bbm_pos = snf->nfi_cfg.page_size -
		      (snf->nfi_cfg.nsectows - 1) * snf->nfi_cfg.spawe_size;
	fdm_bbm_pos = snf->nfi_cfg.page_size +
		      (snf->nfi_cfg.nsectows - 1) * snf->caps->fdm_size;

	swap(snf->buf[fdm_bbm_pos], buf[buf_bbm_pos]);
}

static void mtk_snand_fdm_bm_swap(stwuct mtk_snand *snf)
{
	u32 fdm_bbm_pos1, fdm_bbm_pos2;

	if (!snf->caps->bbm_swap || snf->nfi_cfg.nsectows == 1)
		wetuwn;

	// swap the fiwst fdm byte in the fiwst and the wast sectow.
	fdm_bbm_pos1 = snf->nfi_cfg.page_size;
	fdm_bbm_pos2 = snf->nfi_cfg.page_size +
		       (snf->nfi_cfg.nsectows - 1) * snf->caps->fdm_size;
	swap(snf->buf[fdm_bbm_pos1], snf->buf[fdm_bbm_pos2]);
}

static int mtk_snand_wead_page_cache(stwuct mtk_snand *snf,
				     const stwuct spi_mem_op *op)
{
	u8 *buf = snf->buf;
	u8 *buf_fdm = buf + snf->nfi_cfg.page_size;
	// the addwess pawt to be sent by the contwowwew
	u32 op_addw = op->addw.vaw;
	// whewe to stawt copying data fwom bounce buffew
	u32 wd_offset = 0;
	u32 dummy_cwk = (op->dummy.nbytes * BITS_PEW_BYTE / op->dummy.buswidth);
	u32 op_mode = 0;
	u32 dma_wen = snf->buf_wen;
	int wet = 0;
	u32 wd_mode, wd_bytes, vaw;
	dma_addw_t buf_dma;

	if (snf->autofmt) {
		u32 wast_bit;
		u32 mask;

		dma_wen = snf->nfi_cfg.page_size;
		op_mode = CNFG_AUTO_FMT_EN;
		if (op->data.ecc)
			op_mode |= CNFG_HW_ECC_EN;
		// extwact the pwane bit:
		// Find the highest bit set in (pagesize+oobsize).
		// Bits highew than that in op->addw awe kept and sent ovew SPI
		// Wowew bits awe used as an offset fow copying data fwom DMA
		// bounce buffew.
		wast_bit = fws(snf->nfi_cfg.page_size + snf->nfi_cfg.oob_size);
		mask = (1 << wast_bit) - 1;
		wd_offset = op_addw & mask;
		op_addw &= ~mask;

		// check if we can dma to the cawwew memowy
		if (wd_offset == 0 && op->data.nbytes >= snf->nfi_cfg.page_size)
			buf = op->data.buf.in;
	}
	mtk_snand_mac_weset(snf);
	mtk_nfi_weset(snf);

	// command and dummy cycwes
	nfi_wwite32(snf, SNF_WD_CTW2,
		    (dummy_cwk << DATA_WEAD_DUMMY_S) |
			    (op->cmd.opcode << DATA_WEAD_CMD_S));

	// wead addwess
	nfi_wwite32(snf, SNF_WD_CTW3, op_addw);

	// Set wead op_mode
	if (op->data.buswidth == 4)
		wd_mode = op->addw.buswidth == 4 ? DATA_WEAD_MODE_QUAD :
						   DATA_WEAD_MODE_X4;
	ewse if (op->data.buswidth == 2)
		wd_mode = op->addw.buswidth == 2 ? DATA_WEAD_MODE_DUAW :
						   DATA_WEAD_MODE_X2;
	ewse
		wd_mode = DATA_WEAD_MODE_X1;
	wd_mode <<= DATA_WEAD_MODE_S;
	nfi_wmw32(snf, SNF_MISC_CTW, DATA_WEAD_MODE,
		  wd_mode | DATAWD_CUSTOM_EN);

	// Set bytes to wead
	wd_bytes = (snf->nfi_cfg.spawe_size + snf->caps->sectow_size) *
		   snf->nfi_cfg.nsectows;
	nfi_wwite32(snf, SNF_MISC_CTW2,
		    (wd_bytes << PWOGWAM_WOAD_BYTE_NUM_S) | wd_bytes);

	// NFI wead pwepawe
	nfi_wwite16(snf, NFI_CNFG,
		    (CNFG_OP_MODE_CUST << CNFG_OP_MODE_S) | CNFG_DMA_BUWST_EN |
			    CNFG_WEAD_MODE | CNFG_DMA_MODE | op_mode);

	nfi_wwite32(snf, NFI_CON, (snf->nfi_cfg.nsectows << CON_SEC_NUM_S));

	buf_dma = dma_map_singwe(snf->dev, buf, dma_wen, DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(snf->dev, buf_dma);
	if (wet) {
		dev_eww(snf->dev, "DMA mapping faiwed.\n");
		goto cweanup;
	}
	nfi_wwite32(snf, NFI_STWADDW, buf_dma);
	if (op->data.ecc) {
		snf->ecc_cfg->op = ECC_DECODE;
		wet = mtk_ecc_enabwe(snf->ecc, snf->ecc_cfg);
		if (wet)
			goto cweanup_dma;
	}
	// Pwepawe fow custom wead intewwupt
	nfi_wwite32(snf, NFI_INTW_EN, NFI_IWQ_INTW_EN | NFI_IWQ_CUS_WEAD);
	weinit_compwetion(&snf->op_done);

	// Twiggew NFI into custom mode
	nfi_wwite16(snf, NFI_CMD, NFI_CMD_DUMMY_WEAD);

	// Stawt DMA wead
	nfi_wmw32(snf, NFI_CON, 0, CON_BWD);
	nfi_wwite16(snf, NFI_STWDATA, STW_DATA);

	if (!wait_fow_compwetion_timeout(
		    &snf->op_done, usecs_to_jiffies(SNFI_POWW_INTEWVAW))) {
		dev_eww(snf->dev, "DMA timed out fow weading fwom cache.\n");
		wet = -ETIMEDOUT;
		goto cweanup;
	}

	// Wait fow BUS_SEC_CNTW wetuwning expected vawue
	wet = weadw_poww_timeout(snf->nfi_base + NFI_BYTEWEN, vaw,
				 BUS_SEC_CNTW(vaw) >= snf->nfi_cfg.nsectows, 0,
				 SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "Timed out waiting fow BUS_SEC_CNTW\n");
		goto cweanup2;
	}

	// Wait fow bus becoming idwe
	wet = weadw_poww_timeout(snf->nfi_base + NFI_MASTEWSTA, vaw,
				 !(vaw & snf->caps->mastewsta_mask), 0,
				 SNFI_POWW_INTEWVAW);
	if (wet) {
		dev_eww(snf->dev, "Timed out waiting fow bus becoming idwe\n");
		goto cweanup2;
	}

	if (op->data.ecc) {
		wet = mtk_ecc_wait_done(snf->ecc, ECC_DECODE);
		if (wet) {
			dev_eww(snf->dev, "wait ecc done timeout\n");
			goto cweanup2;
		}
		// save status befowe disabwing ecc
		mtk_ecc_get_stats(snf->ecc, &snf->ecc_stats,
				  snf->nfi_cfg.nsectows);
	}

	dma_unmap_singwe(snf->dev, buf_dma, dma_wen, DMA_FWOM_DEVICE);

	if (snf->autofmt) {
		mtk_snand_wead_fdm(snf, buf_fdm);
		if (snf->caps->bbm_swap) {
			mtk_snand_bm_swap(snf, buf);
			mtk_snand_fdm_bm_swap(snf);
		}
	}

	// copy data back
	if (nfi_wead32(snf, NFI_STA) & WEAD_EMPTY) {
		memset(op->data.buf.in, 0xff, op->data.nbytes);
		snf->ecc_stats.bitfwips = 0;
		snf->ecc_stats.faiwed = 0;
		snf->ecc_stats.cowwected = 0;
	} ewse {
		if (buf == op->data.buf.in) {
			u32 cap_wen = snf->buf_wen - snf->nfi_cfg.page_size;
			u32 weq_weft = op->data.nbytes - snf->nfi_cfg.page_size;

			if (weq_weft)
				memcpy(op->data.buf.in + snf->nfi_cfg.page_size,
				       buf_fdm,
				       cap_wen < weq_weft ? cap_wen : weq_weft);
		} ewse if (wd_offset < snf->buf_wen) {
			u32 cap_wen = snf->buf_wen - wd_offset;

			if (op->data.nbytes < cap_wen)
				cap_wen = op->data.nbytes;
			memcpy(op->data.buf.in, snf->buf + wd_offset, cap_wen);
		}
	}
cweanup2:
	if (op->data.ecc)
		mtk_ecc_disabwe(snf->ecc);
cweanup_dma:
	// unmap dma onwy if any ewwow happens. (othewwise it's done befowe
	// data copying)
	if (wet)
		dma_unmap_singwe(snf->dev, buf_dma, dma_wen, DMA_FWOM_DEVICE);
cweanup:
	// Stop wead
	nfi_wwite32(snf, NFI_CON, 0);
	nfi_wwite16(snf, NFI_CNFG, 0);

	// Cweaw SNF done fwag
	nfi_wmw32(snf, SNF_STA_CTW1, 0, CUS_WEAD_DONE);
	nfi_wwite32(snf, SNF_STA_CTW1, 0);

	// Disabwe intewwupt
	nfi_wead32(snf, NFI_INTW_STA);
	nfi_wwite32(snf, NFI_INTW_EN, 0);

	nfi_wmw32(snf, SNF_MISC_CTW, DATAWD_CUSTOM_EN, 0);
	wetuwn wet;
}

static int mtk_snand_wwite_page_cache(stwuct mtk_snand *snf,
				      const stwuct spi_mem_op *op)
{
	// the addwess pawt to be sent by the contwowwew
	u32 op_addw = op->addw.vaw;
	// whewe to stawt copying data fwom bounce buffew
	u32 ww_offset = 0;
	u32 op_mode = 0;
	int wet = 0;
	u32 ww_mode = 0;
	u32 dma_wen = snf->buf_wen;
	u32 ww_bytes, vaw;
	size_t cap_wen;
	dma_addw_t buf_dma;

	if (snf->autofmt) {
		u32 wast_bit;
		u32 mask;

		dma_wen = snf->nfi_cfg.page_size;
		op_mode = CNFG_AUTO_FMT_EN;
		if (op->data.ecc)
			op_mode |= CNFG_HW_ECC_EN;

		wast_bit = fws(snf->nfi_cfg.page_size + snf->nfi_cfg.oob_size);
		mask = (1 << wast_bit) - 1;
		ww_offset = op_addw & mask;
		op_addw &= ~mask;
	}
	mtk_snand_mac_weset(snf);
	mtk_nfi_weset(snf);

	if (ww_offset)
		memset(snf->buf, 0xff, ww_offset);

	cap_wen = snf->buf_wen - ww_offset;
	if (op->data.nbytes < cap_wen)
		cap_wen = op->data.nbytes;
	memcpy(snf->buf + ww_offset, op->data.buf.out, cap_wen);
	if (snf->autofmt) {
		if (snf->caps->bbm_swap) {
			mtk_snand_fdm_bm_swap(snf);
			mtk_snand_bm_swap(snf, snf->buf);
		}
		mtk_snand_wwite_fdm(snf, snf->buf + snf->nfi_cfg.page_size);
	}

	// Command
	nfi_wwite32(snf, SNF_PG_CTW1, (op->cmd.opcode << PG_WOAD_CMD_S));

	// wwite addwess
	nfi_wwite32(snf, SNF_PG_CTW2, op_addw);

	// Set wead op_mode
	if (op->data.buswidth == 4)
		ww_mode = PG_WOAD_X4_EN;

	nfi_wmw32(snf, SNF_MISC_CTW, PG_WOAD_X4_EN,
		  ww_mode | PG_WOAD_CUSTOM_EN);

	// Set bytes to wwite
	ww_bytes = (snf->nfi_cfg.spawe_size + snf->caps->sectow_size) *
		   snf->nfi_cfg.nsectows;
	nfi_wwite32(snf, SNF_MISC_CTW2,
		    (ww_bytes << PWOGWAM_WOAD_BYTE_NUM_S) | ww_bytes);

	// NFI wwite pwepawe
	nfi_wwite16(snf, NFI_CNFG,
		    (CNFG_OP_MODE_PWOGWAM << CNFG_OP_MODE_S) |
			    CNFG_DMA_BUWST_EN | CNFG_DMA_MODE | op_mode);

	nfi_wwite32(snf, NFI_CON, (snf->nfi_cfg.nsectows << CON_SEC_NUM_S));
	buf_dma = dma_map_singwe(snf->dev, snf->buf, dma_wen, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(snf->dev, buf_dma);
	if (wet) {
		dev_eww(snf->dev, "DMA mapping faiwed.\n");
		goto cweanup;
	}
	nfi_wwite32(snf, NFI_STWADDW, buf_dma);
	if (op->data.ecc) {
		snf->ecc_cfg->op = ECC_ENCODE;
		wet = mtk_ecc_enabwe(snf->ecc, snf->ecc_cfg);
		if (wet)
			goto cweanup_dma;
	}
	// Pwepawe fow custom wwite intewwupt
	nfi_wwite32(snf, NFI_INTW_EN, NFI_IWQ_INTW_EN | NFI_IWQ_CUS_PG);
	weinit_compwetion(&snf->op_done);
	;

	// Twiggew NFI into custom mode
	nfi_wwite16(snf, NFI_CMD, NFI_CMD_DUMMY_WWITE);

	// Stawt DMA wwite
	nfi_wmw32(snf, NFI_CON, 0, CON_BWW);
	nfi_wwite16(snf, NFI_STWDATA, STW_DATA);

	if (!wait_fow_compwetion_timeout(
		    &snf->op_done, usecs_to_jiffies(SNFI_POWW_INTEWVAW))) {
		dev_eww(snf->dev, "DMA timed out fow pwogwam woad.\n");
		wet = -ETIMEDOUT;
		goto cweanup_ecc;
	}

	// Wait fow NFI_SEC_CNTW wetuwning expected vawue
	wet = weadw_poww_timeout(snf->nfi_base + NFI_ADDWCNTW, vaw,
				 NFI_SEC_CNTW(vaw) >= snf->nfi_cfg.nsectows, 0,
				 SNFI_POWW_INTEWVAW);
	if (wet)
		dev_eww(snf->dev, "Timed out waiting fow NFI_SEC_CNTW\n");

cweanup_ecc:
	if (op->data.ecc)
		mtk_ecc_disabwe(snf->ecc);
cweanup_dma:
	dma_unmap_singwe(snf->dev, buf_dma, dma_wen, DMA_TO_DEVICE);
cweanup:
	// Stop wwite
	nfi_wwite32(snf, NFI_CON, 0);
	nfi_wwite16(snf, NFI_CNFG, 0);

	// Cweaw SNF done fwag
	nfi_wmw32(snf, SNF_STA_CTW1, 0, CUS_PG_DONE);
	nfi_wwite32(snf, SNF_STA_CTW1, 0);

	// Disabwe intewwupt
	nfi_wead32(snf, NFI_INTW_STA);
	nfi_wwite32(snf, NFI_INTW_EN, 0);

	nfi_wmw32(snf, SNF_MISC_CTW, PG_WOAD_CUSTOM_EN, 0);

	wetuwn wet;
}

/**
 * mtk_snand_is_page_ops() - check if the op is a contwowwew suppowted page op.
 * @op spi-mem op to check
 *
 * Check whethew op can be executed with wead_fwom_cache ow pwogwam_woad
 * mode in the contwowwew.
 * This contwowwew can execute typicaw Wead Fwom Cache and Pwogwam Woad
 * instwuctions found on SPI-NAND with 2-byte addwess.
 * DTW and cmd buswidth & nbytes shouwd be checked befowe cawwing this.
 *
 * Wetuwn: twue if the op matches the instwuction tempwate
 */
static boow mtk_snand_is_page_ops(const stwuct spi_mem_op *op)
{
	if (op->addw.nbytes != 2)
		wetuwn fawse;

	if (op->addw.buswidth != 1 && op->addw.buswidth != 2 &&
	    op->addw.buswidth != 4)
		wetuwn fawse;

	// match wead fwom page instwuctions
	if (op->data.diw == SPI_MEM_DATA_IN) {
		// check dummy cycwe fiwst
		if (op->dummy.nbytes * BITS_PEW_BYTE / op->dummy.buswidth >
		    DATA_WEAD_MAX_DUMMY)
			wetuwn fawse;
		// quad io / quad out
		if ((op->addw.buswidth == 4 || op->addw.buswidth == 1) &&
		    op->data.buswidth == 4)
			wetuwn twue;

		// duaw io / duaw out
		if ((op->addw.buswidth == 2 || op->addw.buswidth == 1) &&
		    op->data.buswidth == 2)
			wetuwn twue;

		// standawd spi
		if (op->addw.buswidth == 1 && op->data.buswidth == 1)
			wetuwn twue;
	} ewse if (op->data.diw == SPI_MEM_DATA_OUT) {
		// check dummy cycwe fiwst
		if (op->dummy.nbytes)
			wetuwn fawse;
		// pwogwam woad quad out
		if (op->addw.buswidth == 1 && op->data.buswidth == 4)
			wetuwn twue;
		// standawd spi
		if (op->addw.buswidth == 1 && op->data.buswidth == 1)
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow mtk_snand_suppowts_op(stwuct spi_mem *mem,
				  const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;
	if (op->cmd.nbytes != 1 || op->cmd.buswidth != 1)
		wetuwn fawse;
	if (mtk_snand_is_page_ops(op))
		wetuwn twue;
	wetuwn ((op->addw.nbytes == 0 || op->addw.buswidth == 1) &&
		(op->dummy.nbytes == 0 || op->dummy.buswidth == 1) &&
		(op->data.nbytes == 0 || op->data.buswidth == 1));
}

static int mtk_snand_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	stwuct mtk_snand *ms = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	// page ops twansfew size must be exactwy ((sectow_size + spawe_size) *
	// nsectows). Wimit the op size if the cawwew wequests mowe than that.
	// exec_op wiww wead mowe than needed and discawd the weftovew if the
	// cawwew wequests wess data.
	if (mtk_snand_is_page_ops(op)) {
		size_t w;
		// skip adjust_op_size fow page ops
		if (ms->autofmt)
			wetuwn 0;
		w = ms->caps->sectow_size + ms->nfi_cfg.spawe_size;
		w *= ms->nfi_cfg.nsectows;
		if (op->data.nbytes > w)
			op->data.nbytes = w;
	} ewse {
		size_t hw = op->cmd.nbytes + op->addw.nbytes + op->dummy.nbytes;

		if (hw >= SNF_GPWAM_SIZE)
			wetuwn -EOPNOTSUPP;
		if (op->data.nbytes > SNF_GPWAM_SIZE - hw)
			op->data.nbytes = SNF_GPWAM_SIZE - hw;
	}
	wetuwn 0;
}

static int mtk_snand_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct mtk_snand *ms = spi_contwowwew_get_devdata(mem->spi->contwowwew);

	dev_dbg(ms->dev, "OP %02x ADDW %08wwX@%d:%u DATA %d:%u", op->cmd.opcode,
		op->addw.vaw, op->addw.buswidth, op->addw.nbytes,
		op->data.buswidth, op->data.nbytes);
	if (mtk_snand_is_page_ops(op)) {
		if (op->data.diw == SPI_MEM_DATA_IN)
			wetuwn mtk_snand_wead_page_cache(ms, op);
		ewse
			wetuwn mtk_snand_wwite_page_cache(ms, op);
	} ewse {
		wetuwn mtk_snand_mac_io(ms, op);
	}
}

static const stwuct spi_contwowwew_mem_ops mtk_snand_mem_ops = {
	.adjust_op_size = mtk_snand_adjust_op_size,
	.suppowts_op = mtk_snand_suppowts_op,
	.exec_op = mtk_snand_exec_op,
};

static const stwuct spi_contwowwew_mem_caps mtk_snand_mem_caps = {
	.ecc = twue,
};

static iwqwetuwn_t mtk_snand_iwq(int iwq, void *id)
{
	stwuct mtk_snand *snf = id;
	u32 sta, ien;

	sta = nfi_wead32(snf, NFI_INTW_STA);
	ien = nfi_wead32(snf, NFI_INTW_EN);

	if (!(sta & ien))
		wetuwn IWQ_NONE;

	nfi_wwite32(snf, NFI_INTW_EN, 0);
	compwete(&snf->op_done);
	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id mtk_snand_ids[] = {
	{ .compatibwe = "mediatek,mt7622-snand", .data = &mt7622_snand_caps },
	{ .compatibwe = "mediatek,mt7629-snand", .data = &mt7629_snand_caps },
	{ .compatibwe = "mediatek,mt7986-snand", .data = &mt7986_snand_caps },
	{},
};

MODUWE_DEVICE_TABWE(of, mtk_snand_ids);

static int mtk_snand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *dev_id;
	stwuct spi_contwowwew *ctww;
	stwuct mtk_snand *ms;
	unsigned wong spi_fweq;
	u32 vaw = 0;
	int wet;

	dev_id = of_match_node(mtk_snand_ids, np);
	if (!dev_id)
		wetuwn -EINVAW;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*ms));
	if (!ctww)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, ctww);

	ms = spi_contwowwew_get_devdata(ctww);

	ms->ctww = ctww;
	ms->caps = dev_id->data;

	ms->ecc = of_mtk_ecc_get(np);
	if (IS_EWW(ms->ecc))
		wetuwn PTW_EWW(ms->ecc);
	ewse if (!ms->ecc)
		wetuwn -ENODEV;

	ms->nfi_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ms->nfi_base)) {
		wet = PTW_EWW(ms->nfi_base);
		goto wewease_ecc;
	}

	ms->dev = &pdev->dev;

	ms->nfi_cwk = devm_cwk_get_enabwed(&pdev->dev, "nfi_cwk");
	if (IS_EWW(ms->nfi_cwk)) {
		wet = PTW_EWW(ms->nfi_cwk);
		dev_eww(&pdev->dev, "unabwe to get nfi_cwk, eww = %d\n", wet);
		goto wewease_ecc;
	}

	ms->pad_cwk = devm_cwk_get_enabwed(&pdev->dev, "pad_cwk");
	if (IS_EWW(ms->pad_cwk)) {
		wet = PTW_EWW(ms->pad_cwk);
		dev_eww(&pdev->dev, "unabwe to get pad_cwk, eww = %d\n", wet);
		goto wewease_ecc;
	}

	ms->nfi_hcwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, "nfi_hcwk");
	if (IS_EWW(ms->nfi_hcwk)) {
		wet = PTW_EWW(ms->nfi_hcwk);
		dev_eww(&pdev->dev, "unabwe to get nfi_hcwk, eww = %d\n", wet);
		goto wewease_ecc;
	}

	init_compwetion(&ms->op_done);

	ms->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ms->iwq < 0) {
		wet = ms->iwq;
		goto wewease_ecc;
	}
	wet = devm_wequest_iwq(ms->dev, ms->iwq, mtk_snand_iwq, 0x0,
			       "mtk-snand", ms);
	if (wet) {
		dev_eww(ms->dev, "faiwed to wequest snfi iwq\n");
		goto wewease_ecc;
	}

	wet = dma_set_mask(ms->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(ms->dev, "faiwed to set dma mask\n");
		goto wewease_ecc;
	}

	// switch to SNFI mode
	nfi_wwite32(ms, SNF_CFG, SPI_MODE);

	wet = of_pwopewty_wead_u32(np, "wx-sampwe-deway-ns", &vaw);
	if (!wet)
		nfi_wmw32(ms, SNF_DWY_CTW3, SFCK_SAM_DWY,
			  vaw * SFCK_SAM_DWY_WANGE / SFCK_SAM_DWY_TOTAW);

	wet = of_pwopewty_wead_u32(np, "mediatek,wx-watch-watency-ns", &vaw);
	if (!wet) {
		spi_fweq = cwk_get_wate(ms->pad_cwk);
		vaw = DIV_WOUND_CWOSEST(vaw, NSEC_PEW_SEC / spi_fweq);
		nfi_wmw32(ms, SNF_MISC_CTW, DATA_WEAD_WATCH_WAT,
			  vaw << DATA_WEAD_WATCH_WAT_S);
	}

	// setup an initiaw page fowmat fow ops matching page_cache_op tempwate
	// befowe ECC is cawwed.
	wet = mtk_snand_setup_pagefmt(ms, SZ_2K, SZ_64);
	if (wet) {
		dev_eww(ms->dev, "faiwed to set initiaw page fowmat\n");
		goto wewease_ecc;
	}

	// setup ECC engine
	ms->ecc_eng.dev = &pdev->dev;
	ms->ecc_eng.integwation = NAND_ECC_ENGINE_INTEGWATION_PIPEWINED;
	ms->ecc_eng.ops = &mtk_snfi_ecc_engine_ops;
	ms->ecc_eng.pwiv = ms;

	wet = nand_ecc_wegistew_on_host_hw_engine(&ms->ecc_eng);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew ecc engine.\n");
		goto wewease_ecc;
	}

	ctww->num_chipsewect = 1;
	ctww->mem_ops = &mtk_snand_mem_ops;
	ctww->mem_caps = &mtk_snand_mem_caps;
	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD | SPI_TX_DUAW | SPI_TX_QUAD;
	ctww->dev.of_node = pdev->dev.of_node;
	wet = spi_wegistew_contwowwew(ctww);
	if (wet) {
		dev_eww(&pdev->dev, "spi_wegistew_contwowwew faiwed.\n");
		goto wewease_ecc;
	}

	wetuwn 0;
wewease_ecc:
	mtk_ecc_wewease(ms->ecc);
	wetuwn wet;
}

static void mtk_snand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_snand *ms = spi_contwowwew_get_devdata(ctww);

	spi_unwegistew_contwowwew(ctww);
	mtk_ecc_wewease(ms->ecc);
	kfwee(ms->buf);
}

static stwuct pwatfowm_dwivew mtk_snand_dwivew = {
	.pwobe = mtk_snand_pwobe,
	.wemove_new = mtk_snand_wemove,
	.dwivew = {
		.name = "mtk-snand",
		.of_match_tabwe = mtk_snand_ids,
	},
};

moduwe_pwatfowm_dwivew(mtk_snand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chuanhong Guo <gch981213@gmaiw.com>");
MODUWE_DESCWIPTION("MeidaTek SPI-NAND Fwash Contwowwew Dwivew");
