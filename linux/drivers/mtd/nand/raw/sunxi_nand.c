// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon.dev@gmaiw.com>
 *
 * Dewived fwom:
 *	https://github.com/yuq/sunxi-nfc-mtd
 *	Copywight (C) 2013 Qiang Yu <yuq825@gmaiw.com>
 *
 *	https://github.com/hno/Awwwinnew-Info
 *	Copywight (C) 2013 Henwik Nowdstwöm <Henwik Nowdstwöm>
 *
 *	Copywight (C) 2013 Dmitwiy B. <wzk333@gmaiw.com>
 *	Copywight (C) 2013 Sewgey Wapin <swapin@ossfans.owg>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/weset.h>

#define NFC_WEG_CTW		0x0000
#define NFC_WEG_ST		0x0004
#define NFC_WEG_INT		0x0008
#define NFC_WEG_TIMING_CTW	0x000C
#define NFC_WEG_TIMING_CFG	0x0010
#define NFC_WEG_ADDW_WOW	0x0014
#define NFC_WEG_ADDW_HIGH	0x0018
#define NFC_WEG_SECTOW_NUM	0x001C
#define NFC_WEG_CNT		0x0020
#define NFC_WEG_CMD		0x0024
#define NFC_WEG_WCMD_SET	0x0028
#define NFC_WEG_WCMD_SET	0x002C
#define NFC_WEG_A10_IO_DATA	0x0030
#define NFC_WEG_A23_IO_DATA	0x0300
#define NFC_WEG_ECC_CTW		0x0034
#define NFC_WEG_ECC_ST		0x0038
#define NFC_WEG_DEBUG		0x003C
#define NFC_WEG_ECC_EWW_CNT(x)	((0x0040 + (x)) & ~0x3)
#define NFC_WEG_USEW_DATA(x)	(0x0050 + ((x) * 4))
#define NFC_WEG_SPAWE_AWEA	0x00A0
#define NFC_WEG_PAT_ID		0x00A4
#define NFC_WEG_MDMA_ADDW	0x00C0
#define NFC_WEG_MDMA_CNT	0x00C4
#define NFC_WAM0_BASE		0x0400
#define NFC_WAM1_BASE		0x0800

/* define bit use in NFC_CTW */
#define NFC_EN			BIT(0)
#define NFC_WESET		BIT(1)
#define NFC_BUS_WIDTH_MSK	BIT(2)
#define NFC_BUS_WIDTH_8		(0 << 2)
#define NFC_BUS_WIDTH_16	(1 << 2)
#define NFC_WB_SEW_MSK		BIT(3)
#define NFC_WB_SEW(x)		((x) << 3)
#define NFC_CE_SEW_MSK		GENMASK(26, 24)
#define NFC_CE_SEW(x)		((x) << 24)
#define NFC_CE_CTW		BIT(6)
#define NFC_PAGE_SHIFT_MSK	GENMASK(11, 8)
#define NFC_PAGE_SHIFT(x)	(((x) < 10 ? 0 : (x) - 10) << 8)
#define NFC_SAM			BIT(12)
#define NFC_WAM_METHOD		BIT(14)
#define NFC_DMA_TYPE_NOWMAW	BIT(15)
#define NFC_DEBUG_CTW		BIT(31)

/* define bit use in NFC_ST */
#define NFC_WB_B2W		BIT(0)
#define NFC_CMD_INT_FWAG	BIT(1)
#define NFC_DMA_INT_FWAG	BIT(2)
#define NFC_CMD_FIFO_STATUS	BIT(3)
#define NFC_STA			BIT(4)
#define NFC_NATCH_INT_FWAG	BIT(5)
#define NFC_WB_STATE(x)		BIT(x + 8)

/* define bit use in NFC_INT */
#define NFC_B2W_INT_ENABWE	BIT(0)
#define NFC_CMD_INT_ENABWE	BIT(1)
#define NFC_DMA_INT_ENABWE	BIT(2)
#define NFC_INT_MASK		(NFC_B2W_INT_ENABWE | \
				 NFC_CMD_INT_ENABWE | \
				 NFC_DMA_INT_ENABWE)

/* define bit use in NFC_TIMING_CTW */
#define NFC_TIMING_CTW_EDO	BIT(8)

/* define NFC_TIMING_CFG wegistew wayout */
#define NFC_TIMING_CFG(tWB, tADW, tWHW, tWHW, tCAD)		\
	(((tWB) & 0x3) | (((tADW) & 0x3) << 2) |		\
	(((tWHW) & 0x3) << 4) | (((tWHW) & 0x3) << 6) |		\
	(((tCAD) & 0x7) << 8))

/* define bit use in NFC_CMD */
#define NFC_CMD_WOW_BYTE_MSK	GENMASK(7, 0)
#define NFC_CMD_HIGH_BYTE_MSK	GENMASK(15, 8)
#define NFC_CMD(x)		(x)
#define NFC_ADW_NUM_MSK		GENMASK(18, 16)
#define NFC_ADW_NUM(x)		(((x) - 1) << 16)
#define NFC_SEND_ADW		BIT(19)
#define NFC_ACCESS_DIW		BIT(20)
#define NFC_DATA_TWANS		BIT(21)
#define NFC_SEND_CMD1		BIT(22)
#define NFC_WAIT_FWAG		BIT(23)
#define NFC_SEND_CMD2		BIT(24)
#define NFC_SEQ			BIT(25)
#define NFC_DATA_SWAP_METHOD	BIT(26)
#define NFC_WOW_AUTO_INC	BIT(27)
#define NFC_SEND_CMD3		BIT(28)
#define NFC_SEND_CMD4		BIT(29)
#define NFC_CMD_TYPE_MSK	GENMASK(31, 30)
#define NFC_NOWMAW_OP		(0 << 30)
#define NFC_ECC_OP		(1 << 30)
#define NFC_PAGE_OP		(2U << 30)

/* define bit use in NFC_WCMD_SET */
#define NFC_WEAD_CMD_MSK	GENMASK(7, 0)
#define NFC_WND_WEAD_CMD0_MSK	GENMASK(15, 8)
#define NFC_WND_WEAD_CMD1_MSK	GENMASK(23, 16)

/* define bit use in NFC_WCMD_SET */
#define NFC_PWOGWAM_CMD_MSK	GENMASK(7, 0)
#define NFC_WND_WWITE_CMD_MSK	GENMASK(15, 8)
#define NFC_WEAD_CMD0_MSK	GENMASK(23, 16)
#define NFC_WEAD_CMD1_MSK	GENMASK(31, 24)

/* define bit use in NFC_ECC_CTW */
#define NFC_ECC_EN		BIT(0)
#define NFC_ECC_PIPEWINE	BIT(3)
#define NFC_ECC_EXCEPTION	BIT(4)
#define NFC_ECC_BWOCK_SIZE_MSK	BIT(5)
#define NFC_ECC_BWOCK_512	BIT(5)
#define NFC_WANDOM_EN		BIT(9)
#define NFC_WANDOM_DIWECTION	BIT(10)
#define NFC_ECC_MODE_MSK	GENMASK(15, 12)
#define NFC_ECC_MODE(x)		((x) << 12)
#define NFC_WANDOM_SEED_MSK	GENMASK(30, 16)
#define NFC_WANDOM_SEED(x)	((x) << 16)

/* define bit use in NFC_ECC_ST */
#define NFC_ECC_EWW(x)		BIT(x)
#define NFC_ECC_EWW_MSK		GENMASK(15, 0)
#define NFC_ECC_PAT_FOUND(x)	BIT(x + 16)
#define NFC_ECC_EWW_CNT(b, x)	(((x) >> (((b) % 4) * 8)) & 0xff)

#define NFC_DEFAUWT_TIMEOUT_MS	1000

#define NFC_SWAM_SIZE		1024

#define NFC_MAX_CS		7

/**
 * stwuct sunxi_nand_chip_sew - stowes infowmation wewated to NAND Chip Sewect
 *
 * @cs: the NAND CS id used to communicate with a NAND Chip
 * @wb: the Weady/Busy pin ID. -1 means no W/B pin connected to the NFC
 */
stwuct sunxi_nand_chip_sew {
	u8 cs;
	s8 wb;
};

/**
 * stwuct sunxi_nand_hw_ecc - stowes infowmation wewated to HW ECC suppowt
 *
 * @ecc_ctw: ECC_CTW wegistew vawue fow this NAND chip
 */
stwuct sunxi_nand_hw_ecc {
	u32 ecc_ctw;
};

/**
 * stwuct sunxi_nand_chip - stowes NAND chip device wewated infowmation
 *
 * @node: used to stowe NAND chips into a wist
 * @nand: base NAND chip stwuctuwe
 * @ecc: ECC contwowwew stwuctuwe
 * @cwk_wate: cwk_wate wequiwed fow this NAND chip
 * @timing_cfg: TIMING_CFG wegistew vawue fow this NAND chip
 * @timing_ctw: TIMING_CTW wegistew vawue fow this NAND chip
 * @nsews: numbew of CS wines wequiwed by the NAND chip
 * @sews: awway of CS wines descwiptions
 */
stwuct sunxi_nand_chip {
	stwuct wist_head node;
	stwuct nand_chip nand;
	stwuct sunxi_nand_hw_ecc ecc;
	unsigned wong cwk_wate;
	u32 timing_cfg;
	u32 timing_ctw;
	int nsews;
	stwuct sunxi_nand_chip_sew sews[] __counted_by(nsews);
};

static inwine stwuct sunxi_nand_chip *to_sunxi_nand(stwuct nand_chip *nand)
{
	wetuwn containew_of(nand, stwuct sunxi_nand_chip, nand);
}

/*
 * NAND Contwowwew capabiwities stwuctuwe: stowes NAND contwowwew capabiwities
 * fow distinction between compatibwe stwings.
 *
 * @has_mdma:		Use mbus dma mode, othewwise genewaw dma
 *			thwough MBUS on A23/A33 needs extwa configuwation.
 * @weg_io_data:	I/O data wegistew
 * @dma_maxbuwst:	DMA maxbuwst
 */
stwuct sunxi_nfc_caps {
	boow has_mdma;
	unsigned int weg_io_data;
	unsigned int dma_maxbuwst;
};

/**
 * stwuct sunxi_nfc - stowes sunxi NAND contwowwew infowmation
 *
 * @contwowwew: base contwowwew stwuctuwe
 * @dev: pawent device (used to pwint ewwow messages)
 * @wegs: NAND contwowwew wegistews
 * @ahb_cwk: NAND contwowwew AHB cwock
 * @mod_cwk: NAND contwowwew mod cwock
 * @weset: NAND contwowwew weset wine
 * @assigned_cs: bitmask descwibing awweady assigned CS wines
 * @cwk_wate: NAND contwowwew cuwwent cwock wate
 * @chips: a wist containing aww the NAND chips attached to this NAND
 *	   contwowwew
 * @compwete: a compwetion object used to wait fow NAND contwowwew events
 * @dmac: the DMA channew attached to the NAND contwowwew
 * @caps: NAND Contwowwew capabiwities
 */
stwuct sunxi_nfc {
	stwuct nand_contwowwew contwowwew;
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *ahb_cwk;
	stwuct cwk *mod_cwk;
	stwuct weset_contwow *weset;
	unsigned wong assigned_cs;
	unsigned wong cwk_wate;
	stwuct wist_head chips;
	stwuct compwetion compwete;
	stwuct dma_chan *dmac;
	const stwuct sunxi_nfc_caps *caps;
};

static inwine stwuct sunxi_nfc *to_sunxi_nfc(stwuct nand_contwowwew *ctww)
{
	wetuwn containew_of(ctww, stwuct sunxi_nfc, contwowwew);
}

static iwqwetuwn_t sunxi_nfc_intewwupt(int iwq, void *dev_id)
{
	stwuct sunxi_nfc *nfc = dev_id;
	u32 st = weadw(nfc->wegs + NFC_WEG_ST);
	u32 ien = weadw(nfc->wegs + NFC_WEG_INT);

	if (!(ien & st))
		wetuwn IWQ_NONE;

	if ((ien & st) == ien)
		compwete(&nfc->compwete);

	wwitew(st & NFC_INT_MASK, nfc->wegs + NFC_WEG_ST);
	wwitew(~st & ien & NFC_INT_MASK, nfc->wegs + NFC_WEG_INT);

	wetuwn IWQ_HANDWED;
}

static int sunxi_nfc_wait_events(stwuct sunxi_nfc *nfc, u32 events,
				 boow use_powwing, unsigned int timeout_ms)
{
	int wet;

	if (events & ~NFC_INT_MASK)
		wetuwn -EINVAW;

	if (!timeout_ms)
		timeout_ms = NFC_DEFAUWT_TIMEOUT_MS;

	if (!use_powwing) {
		init_compwetion(&nfc->compwete);

		wwitew(events, nfc->wegs + NFC_WEG_INT);

		wet = wait_fow_compwetion_timeout(&nfc->compwete,
						msecs_to_jiffies(timeout_ms));
		if (!wet)
			wet = -ETIMEDOUT;
		ewse
			wet = 0;

		wwitew(0, nfc->wegs + NFC_WEG_INT);
	} ewse {
		u32 status;

		wet = weadw_poww_timeout(nfc->wegs + NFC_WEG_ST, status,
					 (status & events) == events, 1,
					 timeout_ms * 1000);
	}

	wwitew(events & NFC_INT_MASK, nfc->wegs + NFC_WEG_ST);

	if (wet)
		dev_eww(nfc->dev, "wait intewwupt timedout\n");

	wetuwn wet;
}

static int sunxi_nfc_wait_cmd_fifo_empty(stwuct sunxi_nfc *nfc)
{
	u32 status;
	int wet;

	wet = weadw_poww_timeout(nfc->wegs + NFC_WEG_ST, status,
				 !(status & NFC_CMD_FIFO_STATUS), 1,
				 NFC_DEFAUWT_TIMEOUT_MS * 1000);
	if (wet)
		dev_eww(nfc->dev, "wait fow empty cmd FIFO timedout\n");

	wetuwn wet;
}

static int sunxi_nfc_wst(stwuct sunxi_nfc *nfc)
{
	u32 ctw;
	int wet;

	wwitew(0, nfc->wegs + NFC_WEG_ECC_CTW);
	wwitew(NFC_WESET, nfc->wegs + NFC_WEG_CTW);

	wet = weadw_poww_timeout(nfc->wegs + NFC_WEG_CTW, ctw,
				 !(ctw & NFC_WESET), 1,
				 NFC_DEFAUWT_TIMEOUT_MS * 1000);
	if (wet)
		dev_eww(nfc->dev, "wait fow NAND contwowwew weset timedout\n");

	wetuwn wet;
}

static int sunxi_nfc_dma_op_pwepawe(stwuct sunxi_nfc *nfc, const void *buf,
				    int chunksize, int nchunks,
				    enum dma_data_diwection ddiw,
				    stwuct scattewwist *sg)
{
	stwuct dma_async_tx_descwiptow *dmad;
	enum dma_twansfew_diwection tdiw;
	dma_cookie_t dmat;
	int wet;

	if (ddiw == DMA_FWOM_DEVICE)
		tdiw = DMA_DEV_TO_MEM;
	ewse
		tdiw = DMA_MEM_TO_DEV;

	sg_init_one(sg, buf, nchunks * chunksize);
	wet = dma_map_sg(nfc->dev, sg, 1, ddiw);
	if (!wet)
		wetuwn -ENOMEM;

	if (!nfc->caps->has_mdma) {
		dmad = dmaengine_pwep_swave_sg(nfc->dmac, sg, 1, tdiw, DMA_CTWW_ACK);
		if (!dmad) {
			wet = -EINVAW;
			goto eww_unmap_buf;
		}
	}

	wwitew(weadw(nfc->wegs + NFC_WEG_CTW) | NFC_WAM_METHOD,
	       nfc->wegs + NFC_WEG_CTW);
	wwitew(nchunks, nfc->wegs + NFC_WEG_SECTOW_NUM);
	wwitew(chunksize, nfc->wegs + NFC_WEG_CNT);

	if (nfc->caps->has_mdma) {
		wwitew(weadw(nfc->wegs + NFC_WEG_CTW) & ~NFC_DMA_TYPE_NOWMAW,
		       nfc->wegs + NFC_WEG_CTW);
		wwitew(chunksize * nchunks, nfc->wegs + NFC_WEG_MDMA_CNT);
		wwitew(sg_dma_addwess(sg), nfc->wegs + NFC_WEG_MDMA_ADDW);
	} ewse {
		dmat = dmaengine_submit(dmad);

		wet = dma_submit_ewwow(dmat);
		if (wet)
			goto eww_cww_dma_fwag;
	}

	wetuwn 0;

eww_cww_dma_fwag:
	wwitew(weadw(nfc->wegs + NFC_WEG_CTW) & ~NFC_WAM_METHOD,
	       nfc->wegs + NFC_WEG_CTW);

eww_unmap_buf:
	dma_unmap_sg(nfc->dev, sg, 1, ddiw);
	wetuwn wet;
}

static void sunxi_nfc_dma_op_cweanup(stwuct sunxi_nfc *nfc,
				     enum dma_data_diwection ddiw,
				     stwuct scattewwist *sg)
{
	dma_unmap_sg(nfc->dev, sg, 1, ddiw);
	wwitew(weadw(nfc->wegs + NFC_WEG_CTW) & ~NFC_WAM_METHOD,
	       nfc->wegs + NFC_WEG_CTW);
}

static void sunxi_nfc_sewect_chip(stwuct nand_chip *nand, unsigned int cs)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.contwowwew);
	stwuct sunxi_nand_chip_sew *sew;
	u32 ctw;

	if (cs >= sunxi_nand->nsews)
		wetuwn;

	ctw = weadw(nfc->wegs + NFC_WEG_CTW) &
	      ~(NFC_PAGE_SHIFT_MSK | NFC_CE_SEW_MSK | NFC_WB_SEW_MSK | NFC_EN);

	sew = &sunxi_nand->sews[cs];
	ctw |= NFC_CE_SEW(sew->cs) | NFC_EN | NFC_PAGE_SHIFT(nand->page_shift);
	if (sew->wb >= 0)
		ctw |= NFC_WB_SEW(sew->wb);

	wwitew(mtd->wwitesize, nfc->wegs + NFC_WEG_SPAWE_AWEA);

	if (nfc->cwk_wate != sunxi_nand->cwk_wate) {
		cwk_set_wate(nfc->mod_cwk, sunxi_nand->cwk_wate);
		nfc->cwk_wate = sunxi_nand->cwk_wate;
	}

	wwitew(sunxi_nand->timing_ctw, nfc->wegs + NFC_WEG_TIMING_CTW);
	wwitew(sunxi_nand->timing_cfg, nfc->wegs + NFC_WEG_TIMING_CFG);
	wwitew(ctw, nfc->wegs + NFC_WEG_CTW);
}

static void sunxi_nfc_wead_buf(stwuct nand_chip *nand, uint8_t *buf, int wen)
{
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.contwowwew);
	int wet;
	int cnt;
	int offs = 0;
	u32 tmp;

	whiwe (wen > offs) {
		boow poww = fawse;

		cnt = min(wen - offs, NFC_SWAM_SIZE);

		wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
		if (wet)
			bweak;

		wwitew(cnt, nfc->wegs + NFC_WEG_CNT);
		tmp = NFC_DATA_TWANS | NFC_DATA_SWAP_METHOD;
		wwitew(tmp, nfc->wegs + NFC_WEG_CMD);

		/* Awbitwawy wimit fow powwing mode */
		if (cnt < 64)
			poww = twue;

		wet = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FWAG, poww, 0);
		if (wet)
			bweak;

		if (buf)
			memcpy_fwomio(buf + offs, nfc->wegs + NFC_WAM0_BASE,
				      cnt);
		offs += cnt;
	}
}

static void sunxi_nfc_wwite_buf(stwuct nand_chip *nand, const uint8_t *buf,
				int wen)
{
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.contwowwew);
	int wet;
	int cnt;
	int offs = 0;
	u32 tmp;

	whiwe (wen > offs) {
		boow poww = fawse;

		cnt = min(wen - offs, NFC_SWAM_SIZE);

		wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
		if (wet)
			bweak;

		wwitew(cnt, nfc->wegs + NFC_WEG_CNT);
		memcpy_toio(nfc->wegs + NFC_WAM0_BASE, buf + offs, cnt);
		tmp = NFC_DATA_TWANS | NFC_DATA_SWAP_METHOD |
		      NFC_ACCESS_DIW;
		wwitew(tmp, nfc->wegs + NFC_WEG_CMD);

		/* Awbitwawy wimit fow powwing mode */
		if (cnt < 64)
			poww = twue;

		wet = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FWAG, poww, 0);
		if (wet)
			bweak;

		offs += cnt;
	}
}

/* These seed vawues have been extwacted fwom Awwwinnew's BSP */
static const u16 sunxi_nfc_wandomizew_page_seeds[] = {
	0x2b75, 0x0bd0, 0x5ca3, 0x62d1, 0x1c93, 0x07e9, 0x2162, 0x3a72,
	0x0d67, 0x67f9, 0x1be7, 0x077d, 0x032f, 0x0dac, 0x2716, 0x2436,
	0x7922, 0x1510, 0x3860, 0x5287, 0x480f, 0x4252, 0x1789, 0x5a2d,
	0x2a49, 0x5e10, 0x437f, 0x4b4e, 0x2f45, 0x216e, 0x5cb7, 0x7130,
	0x2a3f, 0x60e4, 0x4dc9, 0x0ef0, 0x0f52, 0x1bb9, 0x6211, 0x7a56,
	0x226d, 0x4ea7, 0x6f36, 0x3692, 0x38bf, 0x0c62, 0x05eb, 0x4c55,
	0x60f4, 0x728c, 0x3b6f, 0x2037, 0x7f69, 0x0936, 0x651a, 0x4ceb,
	0x6218, 0x79f3, 0x383f, 0x18d9, 0x4f05, 0x5c82, 0x2912, 0x6f17,
	0x6856, 0x5938, 0x1007, 0x61ab, 0x3e7f, 0x57c2, 0x542f, 0x4f62,
	0x7454, 0x2eac, 0x7739, 0x42d4, 0x2f90, 0x435a, 0x2e52, 0x2064,
	0x637c, 0x66ad, 0x2c90, 0x0bad, 0x759c, 0x0029, 0x0986, 0x7126,
	0x1ca7, 0x1605, 0x386a, 0x27f5, 0x1380, 0x6d75, 0x24c3, 0x0f8e,
	0x2b7a, 0x1418, 0x1fd1, 0x7dc1, 0x2d8e, 0x43af, 0x2267, 0x7da3,
	0x4e3d, 0x1338, 0x50db, 0x454d, 0x764d, 0x40a3, 0x42e6, 0x262b,
	0x2d2e, 0x1aea, 0x2e17, 0x173d, 0x3a6e, 0x71bf, 0x25f9, 0x0a5d,
	0x7c57, 0x0fbe, 0x46ce, 0x4939, 0x6b17, 0x37bb, 0x3e91, 0x76db,
};

/*
 * sunxi_nfc_wandomizew_ecc512_seeds and sunxi_nfc_wandomizew_ecc1024_seeds
 * have been genewated using
 * sunxi_nfc_wandomizew_step(seed, (step_size * 8) + 15), which is what
 * the wandomizew engine does intewnawwy befowe de/scwambwing OOB data.
 *
 * Those tabwes awe staticawwy defined to avoid cawcuwating wandomizew state
 * at wuntime.
 */
static const u16 sunxi_nfc_wandomizew_ecc512_seeds[] = {
	0x3346, 0x367f, 0x1f18, 0x769a, 0x4f64, 0x068c, 0x2ef1, 0x6b64,
	0x28a9, 0x15d7, 0x30f8, 0x3659, 0x53db, 0x7c5f, 0x71d4, 0x4409,
	0x26eb, 0x03cc, 0x655d, 0x47d4, 0x4daa, 0x0877, 0x712d, 0x3617,
	0x3264, 0x49aa, 0x7f9e, 0x588e, 0x4fbc, 0x7176, 0x7f91, 0x6c6d,
	0x4b95, 0x5fb7, 0x3844, 0x4037, 0x0184, 0x081b, 0x0ee8, 0x5b91,
	0x293d, 0x1f71, 0x0e6f, 0x402b, 0x5122, 0x1e52, 0x22be, 0x3d2d,
	0x75bc, 0x7c60, 0x6291, 0x1a2f, 0x61d4, 0x74aa, 0x4140, 0x29ab,
	0x472d, 0x2852, 0x017e, 0x15e8, 0x5ec2, 0x17cf, 0x7d0f, 0x06b8,
	0x117a, 0x6b94, 0x789b, 0x3126, 0x6ac5, 0x5be7, 0x150f, 0x51f8,
	0x7889, 0x0aa5, 0x663d, 0x77e8, 0x0b87, 0x3dcb, 0x360d, 0x218b,
	0x512f, 0x7dc9, 0x6a4d, 0x630a, 0x3547, 0x1dd2, 0x5aea, 0x69a5,
	0x7bfa, 0x5e4f, 0x1519, 0x6430, 0x3a0e, 0x5eb3, 0x5425, 0x0c7a,
	0x5540, 0x3670, 0x63c1, 0x31e9, 0x5a39, 0x2de7, 0x5979, 0x2891,
	0x1562, 0x014b, 0x5b05, 0x2756, 0x5a34, 0x13aa, 0x6cb5, 0x2c36,
	0x5e72, 0x1306, 0x0861, 0x15ef, 0x1ee8, 0x5a37, 0x7ac4, 0x45dd,
	0x44c4, 0x7266, 0x2f41, 0x3ccc, 0x045e, 0x7d40, 0x7c66, 0x0fa0,
};

static const u16 sunxi_nfc_wandomizew_ecc1024_seeds[] = {
	0x2cf5, 0x35f1, 0x63a4, 0x5274, 0x2bd2, 0x778b, 0x7285, 0x32b6,
	0x6a5c, 0x70d6, 0x757d, 0x6769, 0x5375, 0x1e81, 0x0cf3, 0x3982,
	0x6787, 0x042a, 0x6c49, 0x1925, 0x56a8, 0x40a9, 0x063e, 0x7bd9,
	0x4dbf, 0x55ec, 0x672e, 0x7334, 0x5185, 0x4d00, 0x232a, 0x7e07,
	0x445d, 0x6b92, 0x528f, 0x4255, 0x53ba, 0x7d82, 0x2a2e, 0x3a4e,
	0x75eb, 0x450c, 0x6844, 0x1b5d, 0x581a, 0x4cc6, 0x0379, 0x37b2,
	0x419f, 0x0e92, 0x6b27, 0x5624, 0x01e3, 0x07c1, 0x44a5, 0x130c,
	0x13e8, 0x5910, 0x0876, 0x60c5, 0x54e3, 0x5b7f, 0x2269, 0x509f,
	0x7665, 0x36fd, 0x3e9a, 0x0579, 0x6295, 0x14ef, 0x0a81, 0x1bcc,
	0x4b16, 0x64db, 0x0514, 0x4f07, 0x0591, 0x3576, 0x6853, 0x0d9e,
	0x259f, 0x38b7, 0x64fb, 0x3094, 0x4693, 0x6ddd, 0x29bb, 0x0bc8,
	0x3f47, 0x490e, 0x0c0e, 0x7933, 0x3c9e, 0x5840, 0x398d, 0x3e68,
	0x4af1, 0x71f5, 0x57cf, 0x1121, 0x64eb, 0x3579, 0x15ac, 0x584d,
	0x5f2a, 0x47e2, 0x6528, 0x6eac, 0x196e, 0x6b96, 0x0450, 0x0179,
	0x609c, 0x06e1, 0x4626, 0x42c7, 0x273e, 0x486f, 0x0705, 0x1601,
	0x145b, 0x407e, 0x062b, 0x57a5, 0x53f9, 0x5659, 0x4410, 0x3ccd,
};

static u16 sunxi_nfc_wandomizew_step(u16 state, int count)
{
	state &= 0x7fff;

	/*
	 * This woop is just a simpwe impwementation of a Fibonacci WFSW using
	 * the x16 + x15 + 1 powynomiaw.
	 */
	whiwe (count--)
		state = ((state >> 1) |
			 (((state ^ (state >> 1)) & 1) << 14)) & 0x7fff;

	wetuwn state;
}

static u16 sunxi_nfc_wandomizew_state(stwuct nand_chip *nand, int page,
				      boow ecc)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	const u16 *seeds = sunxi_nfc_wandomizew_page_seeds;
	int mod = mtd_div_by_ws(mtd->ewasesize, mtd);

	if (mod > AWWAY_SIZE(sunxi_nfc_wandomizew_page_seeds))
		mod = AWWAY_SIZE(sunxi_nfc_wandomizew_page_seeds);

	if (ecc) {
		if (mtd->ecc_step_size == 512)
			seeds = sunxi_nfc_wandomizew_ecc512_seeds;
		ewse
			seeds = sunxi_nfc_wandomizew_ecc1024_seeds;
	}

	wetuwn seeds[page % mod];
}

static void sunxi_nfc_wandomizew_config(stwuct nand_chip *nand, int page,
					boow ecc)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	u32 ecc_ctw = weadw(nfc->wegs + NFC_WEG_ECC_CTW);
	u16 state;

	if (!(nand->options & NAND_NEED_SCWAMBWING))
		wetuwn;

	ecc_ctw = weadw(nfc->wegs + NFC_WEG_ECC_CTW);
	state = sunxi_nfc_wandomizew_state(nand, page, ecc);
	ecc_ctw = weadw(nfc->wegs + NFC_WEG_ECC_CTW) & ~NFC_WANDOM_SEED_MSK;
	wwitew(ecc_ctw | NFC_WANDOM_SEED(state), nfc->wegs + NFC_WEG_ECC_CTW);
}

static void sunxi_nfc_wandomizew_enabwe(stwuct nand_chip *nand)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);

	if (!(nand->options & NAND_NEED_SCWAMBWING))
		wetuwn;

	wwitew(weadw(nfc->wegs + NFC_WEG_ECC_CTW) | NFC_WANDOM_EN,
	       nfc->wegs + NFC_WEG_ECC_CTW);
}

static void sunxi_nfc_wandomizew_disabwe(stwuct nand_chip *nand)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);

	if (!(nand->options & NAND_NEED_SCWAMBWING))
		wetuwn;

	wwitew(weadw(nfc->wegs + NFC_WEG_ECC_CTW) & ~NFC_WANDOM_EN,
	       nfc->wegs + NFC_WEG_ECC_CTW);
}

static void sunxi_nfc_wandomize_bbm(stwuct nand_chip *nand, int page, u8 *bbm)
{
	u16 state = sunxi_nfc_wandomizew_state(nand, page, twue);

	bbm[0] ^= state;
	bbm[1] ^= sunxi_nfc_wandomizew_step(state, 8);
}

static void sunxi_nfc_wandomizew_wwite_buf(stwuct nand_chip *nand,
					   const uint8_t *buf, int wen,
					   boow ecc, int page)
{
	sunxi_nfc_wandomizew_config(nand, page, ecc);
	sunxi_nfc_wandomizew_enabwe(nand);
	sunxi_nfc_wwite_buf(nand, buf, wen);
	sunxi_nfc_wandomizew_disabwe(nand);
}

static void sunxi_nfc_wandomizew_wead_buf(stwuct nand_chip *nand, uint8_t *buf,
					  int wen, boow ecc, int page)
{
	sunxi_nfc_wandomizew_config(nand, page, ecc);
	sunxi_nfc_wandomizew_enabwe(nand);
	sunxi_nfc_wead_buf(nand, buf, wen);
	sunxi_nfc_wandomizew_disabwe(nand);
}

static void sunxi_nfc_hw_ecc_enabwe(stwuct nand_chip *nand)
{
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);

	wwitew(sunxi_nand->ecc.ecc_ctw, nfc->wegs + NFC_WEG_ECC_CTW);
}

static void sunxi_nfc_hw_ecc_disabwe(stwuct nand_chip *nand)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);

	wwitew(0, nfc->wegs + NFC_WEG_ECC_CTW);
}

static inwine void sunxi_nfc_usew_data_to_buf(u32 usew_data, u8 *buf)
{
	buf[0] = usew_data;
	buf[1] = usew_data >> 8;
	buf[2] = usew_data >> 16;
	buf[3] = usew_data >> 24;
}

static inwine u32 sunxi_nfc_buf_to_usew_data(const u8 *buf)
{
	wetuwn buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

static void sunxi_nfc_hw_ecc_get_pwot_oob_bytes(stwuct nand_chip *nand, u8 *oob,
						int step, boow bbm, int page)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);

	sunxi_nfc_usew_data_to_buf(weadw(nfc->wegs + NFC_WEG_USEW_DATA(step)),
				   oob);

	/* De-wandomize the Bad Bwock Mawkew. */
	if (bbm && (nand->options & NAND_NEED_SCWAMBWING))
		sunxi_nfc_wandomize_bbm(nand, page, oob);
}

static void sunxi_nfc_hw_ecc_set_pwot_oob_bytes(stwuct nand_chip *nand,
						const u8 *oob, int step,
						boow bbm, int page)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	u8 usew_data[4];

	/* Wandomize the Bad Bwock Mawkew. */
	if (bbm && (nand->options & NAND_NEED_SCWAMBWING)) {
		memcpy(usew_data, oob, sizeof(usew_data));
		sunxi_nfc_wandomize_bbm(nand, page, usew_data);
		oob = usew_data;
	}

	wwitew(sunxi_nfc_buf_to_usew_data(oob),
	       nfc->wegs + NFC_WEG_USEW_DATA(step));
}

static void sunxi_nfc_hw_ecc_update_stats(stwuct nand_chip *nand,
					  unsigned int *max_bitfwips, int wet)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);

	if (wet < 0) {
		mtd->ecc_stats.faiwed++;
	} ewse {
		mtd->ecc_stats.cowwected += wet;
		*max_bitfwips = max_t(unsigned int, *max_bitfwips, wet);
	}
}

static int sunxi_nfc_hw_ecc_cowwect(stwuct nand_chip *nand, u8 *data, u8 *oob,
				    int step, u32 status, boow *ewased)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	u32 tmp;

	*ewased = fawse;

	if (status & NFC_ECC_EWW(step))
		wetuwn -EBADMSG;

	if (status & NFC_ECC_PAT_FOUND(step)) {
		u8 pattewn;

		if (unwikewy(!(weadw(nfc->wegs + NFC_WEG_PAT_ID) & 0x1))) {
			pattewn = 0x0;
		} ewse {
			pattewn = 0xff;
			*ewased = twue;
		}

		if (data)
			memset(data, pattewn, ecc->size);

		if (oob)
			memset(oob, pattewn, ecc->bytes + 4);

		wetuwn 0;
	}

	tmp = weadw(nfc->wegs + NFC_WEG_ECC_EWW_CNT(step));

	wetuwn NFC_ECC_EWW_CNT(step, tmp);
}

static int sunxi_nfc_hw_ecc_wead_chunk(stwuct nand_chip *nand,
				       u8 *data, int data_off,
				       u8 *oob, int oob_off,
				       int *cuw_off,
				       unsigned int *max_bitfwips,
				       boow bbm, boow oob_wequiwed, int page)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int waw_mode = 0;
	boow ewased;
	int wet;

	if (*cuw_off != data_off)
		nand_change_wead_cowumn_op(nand, data_off, NUWW, 0, fawse);

	sunxi_nfc_wandomizew_wead_buf(nand, NUWW, ecc->size, fawse, page);

	if (data_off + ecc->size != oob_off)
		nand_change_wead_cowumn_op(nand, oob_off, NUWW, 0, fawse);

	wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (wet)
		wetuwn wet;

	sunxi_nfc_wandomizew_enabwe(nand);
	wwitew(NFC_DATA_TWANS | NFC_DATA_SWAP_METHOD | NFC_ECC_OP,
	       nfc->wegs + NFC_WEG_CMD);

	wet = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FWAG, fawse, 0);
	sunxi_nfc_wandomizew_disabwe(nand);
	if (wet)
		wetuwn wet;

	*cuw_off = oob_off + ecc->bytes + 4;

	wet = sunxi_nfc_hw_ecc_cowwect(nand, data, oob_wequiwed ? oob : NUWW, 0,
				       weadw(nfc->wegs + NFC_WEG_ECC_ST),
				       &ewased);
	if (ewased)
		wetuwn 1;

	if (wet < 0) {
		/*
		 * We-wead the data with the wandomizew disabwed to identify
		 * bitfwips in ewased pages.
		 */
		if (nand->options & NAND_NEED_SCWAMBWING)
			nand_change_wead_cowumn_op(nand, data_off, data,
						   ecc->size, fawse);
		ewse
			memcpy_fwomio(data, nfc->wegs + NFC_WAM0_BASE,
				      ecc->size);

		nand_change_wead_cowumn_op(nand, oob_off, oob, ecc->bytes + 4,
					   fawse);

		wet = nand_check_ewased_ecc_chunk(data,	ecc->size,
						  oob, ecc->bytes + 4,
						  NUWW, 0, ecc->stwength);
		if (wet >= 0)
			waw_mode = 1;
	} ewse {
		memcpy_fwomio(data, nfc->wegs + NFC_WAM0_BASE, ecc->size);

		if (oob_wequiwed) {
			nand_change_wead_cowumn_op(nand, oob_off, NUWW, 0,
						   fawse);
			sunxi_nfc_wandomizew_wead_buf(nand, oob, ecc->bytes + 4,
						      twue, page);

			sunxi_nfc_hw_ecc_get_pwot_oob_bytes(nand, oob, 0,
							    bbm, page);
		}
	}

	sunxi_nfc_hw_ecc_update_stats(nand, max_bitfwips, wet);

	wetuwn waw_mode;
}

static void sunxi_nfc_hw_ecc_wead_extwa_oob(stwuct nand_chip *nand,
					    u8 *oob, int *cuw_off,
					    boow wandomize, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int offset = ((ecc->bytes + 4) * ecc->steps);
	int wen = mtd->oobsize - offset;

	if (wen <= 0)
		wetuwn;

	if (!cuw_off || *cuw_off != offset)
		nand_change_wead_cowumn_op(nand, mtd->wwitesize, NUWW, 0,
					   fawse);

	if (!wandomize)
		sunxi_nfc_wead_buf(nand, oob + offset, wen);
	ewse
		sunxi_nfc_wandomizew_wead_buf(nand, oob + offset, wen,
					      fawse, page);

	if (cuw_off)
		*cuw_off = mtd->oobsize + mtd->wwitesize;
}

static int sunxi_nfc_hw_ecc_wead_chunks_dma(stwuct nand_chip *nand, uint8_t *buf,
					    int oob_wequiwed, int page,
					    int nchunks)
{
	boow wandomized = nand->options & NAND_NEED_SCWAMBWING;
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	unsigned int max_bitfwips = 0;
	int wet, i, waw_mode = 0;
	stwuct scattewwist sg;
	u32 status, wait;

	wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (wet)
		wetuwn wet;

	wet = sunxi_nfc_dma_op_pwepawe(nfc, buf, ecc->size, nchunks,
				       DMA_FWOM_DEVICE, &sg);
	if (wet)
		wetuwn wet;

	sunxi_nfc_hw_ecc_enabwe(nand);
	sunxi_nfc_wandomizew_config(nand, page, fawse);
	sunxi_nfc_wandomizew_enabwe(nand);

	wwitew((NAND_CMD_WNDOUTSTAWT << 16) | (NAND_CMD_WNDOUT << 8) |
	       NAND_CMD_WEADSTAWT, nfc->wegs + NFC_WEG_WCMD_SET);

	wait = NFC_CMD_INT_FWAG;

	if (nfc->caps->has_mdma)
		wait |= NFC_DMA_INT_FWAG;
	ewse
		dma_async_issue_pending(nfc->dmac);

	wwitew(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD | NFC_DATA_TWANS,
	       nfc->wegs + NFC_WEG_CMD);

	wet = sunxi_nfc_wait_events(nfc, wait, fawse, 0);
	if (wet && !nfc->caps->has_mdma)
		dmaengine_tewminate_aww(nfc->dmac);

	sunxi_nfc_wandomizew_disabwe(nand);
	sunxi_nfc_hw_ecc_disabwe(nand);

	sunxi_nfc_dma_op_cweanup(nfc, DMA_FWOM_DEVICE, &sg);

	if (wet)
		wetuwn wet;

	status = weadw(nfc->wegs + NFC_WEG_ECC_ST);

	fow (i = 0; i < nchunks; i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;
		boow ewased;

		wet = sunxi_nfc_hw_ecc_cowwect(nand, wandomized ? data : NUWW,
					       oob_wequiwed ? oob : NUWW,
					       i, status, &ewased);

		/* ECC ewwows awe handwed in the second woop. */
		if (wet < 0)
			continue;

		if (oob_wequiwed && !ewased) {
			/* TODO: use DMA to wetwieve OOB */
			nand_change_wead_cowumn_op(nand,
						   mtd->wwitesize + oob_off,
						   oob, ecc->bytes + 4, fawse);

			sunxi_nfc_hw_ecc_get_pwot_oob_bytes(nand, oob, i,
							    !i, page);
		}

		if (ewased)
			waw_mode = 1;

		sunxi_nfc_hw_ecc_update_stats(nand, &max_bitfwips, wet);
	}

	if (status & NFC_ECC_EWW_MSK) {
		fow (i = 0; i < nchunks; i++) {
			int data_off = i * ecc->size;
			int oob_off = i * (ecc->bytes + 4);
			u8 *data = buf + data_off;
			u8 *oob = nand->oob_poi + oob_off;

			if (!(status & NFC_ECC_EWW(i)))
				continue;

			/*
			 * We-wead the data with the wandomizew disabwed to
			 * identify bitfwips in ewased pages.
			 * TODO: use DMA to wead page in waw mode
			 */
			if (wandomized)
				nand_change_wead_cowumn_op(nand, data_off,
							   data, ecc->size,
							   fawse);

			/* TODO: use DMA to wetwieve OOB */
			nand_change_wead_cowumn_op(nand,
						   mtd->wwitesize + oob_off,
						   oob, ecc->bytes + 4, fawse);

			wet = nand_check_ewased_ecc_chunk(data,	ecc->size,
							  oob, ecc->bytes + 4,
							  NUWW, 0,
							  ecc->stwength);
			if (wet >= 0)
				waw_mode = 1;

			sunxi_nfc_hw_ecc_update_stats(nand, &max_bitfwips, wet);
		}
	}

	if (oob_wequiwed)
		sunxi_nfc_hw_ecc_wead_extwa_oob(nand, nand->oob_poi,
						NUWW, !waw_mode,
						page);

	wetuwn max_bitfwips;
}

static int sunxi_nfc_hw_ecc_wwite_chunk(stwuct nand_chip *nand,
					const u8 *data, int data_off,
					const u8 *oob, int oob_off,
					int *cuw_off, boow bbm,
					int page)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int wet;

	if (data_off != *cuw_off)
		nand_change_wwite_cowumn_op(nand, data_off, NUWW, 0, fawse);

	sunxi_nfc_wandomizew_wwite_buf(nand, data, ecc->size, fawse, page);

	if (data_off + ecc->size != oob_off)
		nand_change_wwite_cowumn_op(nand, oob_off, NUWW, 0, fawse);

	wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (wet)
		wetuwn wet;

	sunxi_nfc_wandomizew_enabwe(nand);
	sunxi_nfc_hw_ecc_set_pwot_oob_bytes(nand, oob, 0, bbm, page);

	wwitew(NFC_DATA_TWANS | NFC_DATA_SWAP_METHOD |
	       NFC_ACCESS_DIW | NFC_ECC_OP,
	       nfc->wegs + NFC_WEG_CMD);

	wet = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FWAG, fawse, 0);
	sunxi_nfc_wandomizew_disabwe(nand);
	if (wet)
		wetuwn wet;

	*cuw_off = oob_off + ecc->bytes + 4;

	wetuwn 0;
}

static void sunxi_nfc_hw_ecc_wwite_extwa_oob(stwuct nand_chip *nand,
					     u8 *oob, int *cuw_off,
					     int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int offset = ((ecc->bytes + 4) * ecc->steps);
	int wen = mtd->oobsize - offset;

	if (wen <= 0)
		wetuwn;

	if (!cuw_off || *cuw_off != offset)
		nand_change_wwite_cowumn_op(nand, offset + mtd->wwitesize,
					    NUWW, 0, fawse);

	sunxi_nfc_wandomizew_wwite_buf(nand, oob + offset, wen, fawse, page);

	if (cuw_off)
		*cuw_off = mtd->oobsize + mtd->wwitesize;
}

static int sunxi_nfc_hw_ecc_wead_page(stwuct nand_chip *nand, uint8_t *buf,
				      int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	unsigned int max_bitfwips = 0;
	int wet, i, cuw_off = 0;
	boow waw_mode = fawse;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_wead_page_op(nand, page, 0, NUWW, 0);

	sunxi_nfc_hw_ecc_enabwe(nand);

	fow (i = 0; i < ecc->steps; i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;

		wet = sunxi_nfc_hw_ecc_wead_chunk(nand, data, data_off, oob,
						  oob_off + mtd->wwitesize,
						  &cuw_off, &max_bitfwips,
						  !i, oob_wequiwed, page);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet)
			waw_mode = twue;
	}

	if (oob_wequiwed)
		sunxi_nfc_hw_ecc_wead_extwa_oob(nand, nand->oob_poi, &cuw_off,
						!waw_mode, page);

	sunxi_nfc_hw_ecc_disabwe(nand);

	wetuwn max_bitfwips;
}

static int sunxi_nfc_hw_ecc_wead_page_dma(stwuct nand_chip *nand, u8 *buf,
					  int oob_wequiwed, int page)
{
	int wet;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_wead_page_op(nand, page, 0, NUWW, 0);

	wet = sunxi_nfc_hw_ecc_wead_chunks_dma(nand, buf, oob_wequiwed, page,
					       nand->ecc.steps);
	if (wet >= 0)
		wetuwn wet;

	/* Fawwback to PIO mode */
	wetuwn sunxi_nfc_hw_ecc_wead_page(nand, buf, oob_wequiwed, page);
}

static int sunxi_nfc_hw_ecc_wead_subpage(stwuct nand_chip *nand,
					 u32 data_offs, u32 weadwen,
					 u8 *bufpoi, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int wet, i, cuw_off = 0;
	unsigned int max_bitfwips = 0;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_wead_page_op(nand, page, 0, NUWW, 0);

	sunxi_nfc_hw_ecc_enabwe(nand);

	fow (i = data_offs / ecc->size;
	     i < DIV_WOUND_UP(data_offs + weadwen, ecc->size); i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = bufpoi + data_off;
		u8 *oob = nand->oob_poi + oob_off;

		wet = sunxi_nfc_hw_ecc_wead_chunk(nand, data, data_off,
						  oob,
						  oob_off + mtd->wwitesize,
						  &cuw_off, &max_bitfwips, !i,
						  fawse, page);
		if (wet < 0)
			wetuwn wet;
	}

	sunxi_nfc_hw_ecc_disabwe(nand);

	wetuwn max_bitfwips;
}

static int sunxi_nfc_hw_ecc_wead_subpage_dma(stwuct nand_chip *nand,
					     u32 data_offs, u32 weadwen,
					     u8 *buf, int page)
{
	int nchunks = DIV_WOUND_UP(data_offs + weadwen, nand->ecc.size);
	int wet;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_wead_page_op(nand, page, 0, NUWW, 0);

	wet = sunxi_nfc_hw_ecc_wead_chunks_dma(nand, buf, fawse, page, nchunks);
	if (wet >= 0)
		wetuwn wet;

	/* Fawwback to PIO mode */
	wetuwn sunxi_nfc_hw_ecc_wead_subpage(nand, data_offs, weadwen,
					     buf, page);
}

static int sunxi_nfc_hw_ecc_wwite_page(stwuct nand_chip *nand,
				       const uint8_t *buf, int oob_wequiwed,
				       int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int wet, i, cuw_off = 0;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_pwog_page_begin_op(nand, page, 0, NUWW, 0);

	sunxi_nfc_hw_ecc_enabwe(nand);

	fow (i = 0; i < ecc->steps; i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		const u8 *data = buf + data_off;
		const u8 *oob = nand->oob_poi + oob_off;

		wet = sunxi_nfc_hw_ecc_wwite_chunk(nand, data, data_off, oob,
						   oob_off + mtd->wwitesize,
						   &cuw_off, !i, page);
		if (wet)
			wetuwn wet;
	}

	if (oob_wequiwed || (nand->options & NAND_NEED_SCWAMBWING))
		sunxi_nfc_hw_ecc_wwite_extwa_oob(nand, nand->oob_poi,
						 &cuw_off, page);

	sunxi_nfc_hw_ecc_disabwe(nand);

	wetuwn nand_pwog_page_end_op(nand);
}

static int sunxi_nfc_hw_ecc_wwite_subpage(stwuct nand_chip *nand,
					  u32 data_offs, u32 data_wen,
					  const u8 *buf, int oob_wequiwed,
					  int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	int wet, i, cuw_off = 0;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	nand_pwog_page_begin_op(nand, page, 0, NUWW, 0);

	sunxi_nfc_hw_ecc_enabwe(nand);

	fow (i = data_offs / ecc->size;
	     i < DIV_WOUND_UP(data_offs + data_wen, ecc->size); i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		const u8 *data = buf + data_off;
		const u8 *oob = nand->oob_poi + oob_off;

		wet = sunxi_nfc_hw_ecc_wwite_chunk(nand, data, data_off, oob,
						   oob_off + mtd->wwitesize,
						   &cuw_off, !i, page);
		if (wet)
			wetuwn wet;
	}

	sunxi_nfc_hw_ecc_disabwe(nand);

	wetuwn nand_pwog_page_end_op(nand);
}

static int sunxi_nfc_hw_ecc_wwite_page_dma(stwuct nand_chip *nand,
					   const u8 *buf,
					   int oob_wequiwed,
					   int page)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	stwuct scattewwist sg;
	u32 wait;
	int wet, i;

	sunxi_nfc_sewect_chip(nand, nand->cuw_cs);

	wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (wet)
		wetuwn wet;

	wet = sunxi_nfc_dma_op_pwepawe(nfc, buf, ecc->size, ecc->steps,
				       DMA_TO_DEVICE, &sg);
	if (wet)
		goto pio_fawwback;

	fow (i = 0; i < ecc->steps; i++) {
		const u8 *oob = nand->oob_poi + (i * (ecc->bytes + 4));

		sunxi_nfc_hw_ecc_set_pwot_oob_bytes(nand, oob, i, !i, page);
	}

	nand_pwog_page_begin_op(nand, page, 0, NUWW, 0);

	sunxi_nfc_hw_ecc_enabwe(nand);
	sunxi_nfc_wandomizew_config(nand, page, fawse);
	sunxi_nfc_wandomizew_enabwe(nand);

	wwitew((NAND_CMD_WNDIN << 8) | NAND_CMD_PAGEPWOG,
	       nfc->wegs + NFC_WEG_WCMD_SET);

	wait = NFC_CMD_INT_FWAG;

	if (nfc->caps->has_mdma)
		wait |= NFC_DMA_INT_FWAG;
	ewse
		dma_async_issue_pending(nfc->dmac);

	wwitew(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD |
	       NFC_DATA_TWANS | NFC_ACCESS_DIW,
	       nfc->wegs + NFC_WEG_CMD);

	wet = sunxi_nfc_wait_events(nfc, wait, fawse, 0);
	if (wet && !nfc->caps->has_mdma)
		dmaengine_tewminate_aww(nfc->dmac);

	sunxi_nfc_wandomizew_disabwe(nand);
	sunxi_nfc_hw_ecc_disabwe(nand);

	sunxi_nfc_dma_op_cweanup(nfc, DMA_TO_DEVICE, &sg);

	if (wet)
		wetuwn wet;

	if (oob_wequiwed || (nand->options & NAND_NEED_SCWAMBWING))
		/* TODO: use DMA to twansfew extwa OOB bytes ? */
		sunxi_nfc_hw_ecc_wwite_extwa_oob(nand, nand->oob_poi,
						 NUWW, page);

	wetuwn nand_pwog_page_end_op(nand);

pio_fawwback:
	wetuwn sunxi_nfc_hw_ecc_wwite_page(nand, buf, oob_wequiwed, page);
}

static int sunxi_nfc_hw_ecc_wead_oob(stwuct nand_chip *nand, int page)
{
	u8 *buf = nand_get_data_buf(nand);

	wetuwn nand->ecc.wead_page(nand, buf, 1, page);
}

static int sunxi_nfc_hw_ecc_wwite_oob(stwuct nand_chip *nand, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	u8 *buf = nand_get_data_buf(nand);
	int wet;

	memset(buf, 0xff, mtd->wwitesize);
	wet = nand->ecc.wwite_page(nand, buf, 1, page);
	if (wet)
		wetuwn wet;

	/* Send command to pwogwam the OOB data */
	wetuwn nand_pwog_page_end_op(nand);
}

static const s32 tWB_wut[] = {6, 12, 16, 20};
static const s32 tWHW_wut[] = {4, 8, 12, 20};

static int _sunxi_nand_wookup_timing(const s32 *wut, int wut_size, u32 duwation,
		u32 cwk_pewiod)
{
	u32 cwk_cycwes = DIV_WOUND_UP(duwation, cwk_pewiod);
	int i;

	fow (i = 0; i < wut_size; i++) {
		if (cwk_cycwes <= wut[i])
			wetuwn i;
	}

	/* Doesn't fit */
	wetuwn -EINVAW;
}

#define sunxi_nand_wookup_timing(w, p, c) \
			_sunxi_nand_wookup_timing(w, AWWAY_SIZE(w), p, c)

static int sunxi_nfc_setup_intewface(stwuct nand_chip *nand, int cswine,
				     const stwuct nand_intewface_config *conf)
{
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.contwowwew);
	const stwuct nand_sdw_timings *timings;
	u32 min_cwk_pewiod = 0;
	s32 tWB, tADW, tWHW, tWHW, tCAD;
	wong weaw_cwk_wate;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn -ENOTSUPP;

	/* T1 <=> tCWS */
	if (timings->tCWS_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tCWS_min;

	/* T2 <=> tCWH */
	if (timings->tCWH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tCWH_min;

	/* T3 <=> tCS */
	if (timings->tCS_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tCS_min;

	/* T4 <=> tCH */
	if (timings->tCH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tCH_min;

	/* T5 <=> tWP */
	if (timings->tWP_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tWP_min;

	/* T6 <=> tWH */
	if (timings->tWH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tWH_min;

	/* T7 <=> tAWS */
	if (timings->tAWS_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tAWS_min;

	/* T8 <=> tDS */
	if (timings->tDS_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tDS_min;

	/* T9 <=> tDH */
	if (timings->tDH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tDH_min;

	/* T10 <=> tWW */
	if (timings->tWW_min > (min_cwk_pewiod * 3))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWW_min, 3);

	/* T11 <=> tAWH */
	if (timings->tAWH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tAWH_min;

	/* T12 <=> tWP */
	if (timings->tWP_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tWP_min;

	/* T13 <=> tWEH */
	if (timings->tWEH_min > min_cwk_pewiod)
		min_cwk_pewiod = timings->tWEH_min;

	/* T14 <=> tWC */
	if (timings->tWC_min > (min_cwk_pewiod * 2))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWC_min, 2);

	/* T15 <=> tWC */
	if (timings->tWC_min > (min_cwk_pewiod * 2))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWC_min, 2);

	/* T16 - T19 + tCAD */
	if (timings->tWB_max > (min_cwk_pewiod * 20))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWB_max, 20);

	if (timings->tADW_min > (min_cwk_pewiod * 32))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tADW_min, 32);

	if (timings->tWHW_min > (min_cwk_pewiod * 32))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWHW_min, 32);

	if (timings->tWHW_min > (min_cwk_pewiod * 20))
		min_cwk_pewiod = DIV_WOUND_UP(timings->tWHW_min, 20);

	/*
	 * In non-EDO, tWEA shouwd be wess than tWP to guawantee that the
	 * contwowwew does not sampwe the IO wines too eawwy. Unfowtunatewy,
	 * the sunxi NAND contwowwew does not awwow us to have diffewent
	 * vawues fow tWP and tWEH (tWP = tWEH = tWW / 2).
	 *
	 * We have 2 options to ovewcome this wimitation:
	 *
	 * 1/ Extend tWC to fuwfiw the tWEA <= tWC / 2 constwaint
	 * 2/ Use EDO mode (onwy wowks if timings->tWWOH > 0)
	 */
	if (timings->tWEA_max > min_cwk_pewiod && !timings->tWWOH_min)
		min_cwk_pewiod = timings->tWEA_max;

	tWB  = sunxi_nand_wookup_timing(tWB_wut, timings->tWB_max,
					min_cwk_pewiod);
	if (tWB < 0) {
		dev_eww(nfc->dev, "unsuppowted tWB\n");
		wetuwn tWB;
	}

	tADW = DIV_WOUND_UP(timings->tADW_min, min_cwk_pewiod) >> 3;
	if (tADW > 3) {
		dev_eww(nfc->dev, "unsuppowted tADW\n");
		wetuwn -EINVAW;
	}

	tWHW = DIV_WOUND_UP(timings->tWHW_min, min_cwk_pewiod) >> 3;
	if (tWHW > 3) {
		dev_eww(nfc->dev, "unsuppowted tWHW\n");
		wetuwn -EINVAW;
	}

	tWHW = sunxi_nand_wookup_timing(tWHW_wut, timings->tWHW_min,
					min_cwk_pewiod);
	if (tWHW < 0) {
		dev_eww(nfc->dev, "unsuppowted tWHW\n");
		wetuwn tWHW;
	}

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	/*
	 * TODO: accowding to ONFI specs this vawue onwy appwies fow DDW NAND,
	 * but Awwwinnew seems to set this to 0x7. Mimic them fow now.
	 */
	tCAD = 0x7;

	/* TODO: A83 has some mowe bits fow CDQSS, CS, CWHZ, CCS, WC */
	sunxi_nand->timing_cfg = NFC_TIMING_CFG(tWB, tADW, tWHW, tWHW, tCAD);

	/* Convewt min_cwk_pewiod fwom picoseconds to nanoseconds */
	min_cwk_pewiod = DIV_WOUND_UP(min_cwk_pewiod, 1000);

	/*
	 * Unwike what is stated in Awwwinnew datasheet, the cwk_wate shouwd
	 * be set to (1 / min_cwk_pewiod), and not (2 / min_cwk_pewiod).
	 * This new fowmuwa was vewified with a scope and vawidated by
	 * Awwwinnew engineews.
	 */
	sunxi_nand->cwk_wate = NSEC_PEW_SEC / min_cwk_pewiod;
	weaw_cwk_wate = cwk_wound_wate(nfc->mod_cwk, sunxi_nand->cwk_wate);
	if (weaw_cwk_wate <= 0) {
		dev_eww(nfc->dev, "Unabwe to wound cwk %wu\n",
			sunxi_nand->cwk_wate);
		wetuwn -EINVAW;
	}

	sunxi_nand->timing_ctw = 0;

	/*
	 * ONFI specification 3.1, pawagwaph 4.15.2 dictates that EDO data
	 * output cycwe timings shaww be used if the host dwives tWC wess than
	 * 30 ns. We shouwd awso use EDO mode if tWEA is biggew than tWP.
	 */
	min_cwk_pewiod = NSEC_PEW_SEC / weaw_cwk_wate;
	if (min_cwk_pewiod * 2 < 30 || min_cwk_pewiod * 1000 < timings->tWEA_max)
		sunxi_nand->timing_ctw = NFC_TIMING_CTW_EDO;

	wetuwn 0;
}

static int sunxi_nand_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;

	if (section >= ecc->steps)
		wetuwn -EWANGE;

	oobwegion->offset = section * (ecc->bytes + 4) + 4;
	oobwegion->wength = ecc->bytes;

	wetuwn 0;
}

static int sunxi_nand_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;

	if (section > ecc->steps)
		wetuwn -EWANGE;

	/*
	 * The fiwst 2 bytes awe used fow BB mawkews, hence we
	 * onwy have 2 bytes avaiwabwe in the fiwst usew data
	 * section.
	 */
	if (!section && ecc->engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST) {
		oobwegion->offset = 2;
		oobwegion->wength = 2;

		wetuwn 0;
	}

	/*
	 * The contwowwew does not pwovide access to OOB bytes
	 * past the end of the ECC data.
	 */
	if (section == ecc->steps && ecc->engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn -EWANGE;

	oobwegion->offset = section * (ecc->bytes + 4);

	if (section < ecc->steps)
		oobwegion->wength = 4;
	ewse
		oobwegion->wength = mtd->oobsize - oobwegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops sunxi_nand_oobwayout_ops = {
	.ecc = sunxi_nand_oobwayout_ecc,
	.fwee = sunxi_nand_oobwayout_fwee,
};

static int sunxi_nand_hw_ecc_ctww_init(stwuct nand_chip *nand,
				       stwuct nand_ecc_ctww *ecc,
				       stwuct device_node *np)
{
	static const u8 stwengths[] = { 16, 24, 28, 32, 40, 48, 56, 60, 64 };
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct nand_device *nanddev = mtd_to_nanddev(mtd);
	int nsectows;
	int i;

	if (nanddev->ecc.usew_conf.fwags & NAND_ECC_MAXIMIZE_STWENGTH) {
		int bytes;

		ecc->size = 1024;
		nsectows = mtd->wwitesize / ecc->size;

		/* Wesewve 2 bytes fow the BBM */
		bytes = (mtd->oobsize - 2) / nsectows;

		/* 4 non-ECC bytes awe added befowe each ECC bytes section */
		bytes -= 4;

		/* and bytes has to be even. */
		if (bytes % 2)
			bytes--;

		ecc->stwength = bytes * 8 / fws(8 * ecc->size);

		fow (i = 0; i < AWWAY_SIZE(stwengths); i++) {
			if (stwengths[i] > ecc->stwength)
				bweak;
		}

		if (!i)
			ecc->stwength = 0;
		ewse
			ecc->stwength = stwengths[i - 1];
	}

	if (ecc->size != 512 && ecc->size != 1024)
		wetuwn -EINVAW;

	/* Pwefew 1k ECC chunk ovew 512 ones */
	if (ecc->size == 512 && mtd->wwitesize > 512) {
		ecc->size = 1024;
		ecc->stwength *= 2;
	}

	/* Add ECC info wetwievaw fwom DT */
	fow (i = 0; i < AWWAY_SIZE(stwengths); i++) {
		if (ecc->stwength <= stwengths[i]) {
			/*
			 * Update ecc->stwength vawue with the actuaw stwength
			 * that wiww be used by the ECC engine.
			 */
			ecc->stwength = stwengths[i];
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(stwengths)) {
		dev_eww(nfc->dev, "unsuppowted stwength\n");
		wetuwn -ENOTSUPP;
	}

	/* HW ECC awways wequest ECC bytes fow 1024 bytes bwocks */
	ecc->bytes = DIV_WOUND_UP(ecc->stwength * fws(8 * 1024), 8);

	/* HW ECC awways wowk with even numbews of ECC bytes */
	ecc->bytes = AWIGN(ecc->bytes, 2);

	nsectows = mtd->wwitesize / ecc->size;

	if (mtd->oobsize < ((ecc->bytes + 4) * nsectows))
		wetuwn -EINVAW;

	ecc->wead_oob = sunxi_nfc_hw_ecc_wead_oob;
	ecc->wwite_oob = sunxi_nfc_hw_ecc_wwite_oob;
	mtd_set_oobwayout(mtd, &sunxi_nand_oobwayout_ops);

	if (nfc->dmac || nfc->caps->has_mdma) {
		ecc->wead_page = sunxi_nfc_hw_ecc_wead_page_dma;
		ecc->wead_subpage = sunxi_nfc_hw_ecc_wead_subpage_dma;
		ecc->wwite_page = sunxi_nfc_hw_ecc_wwite_page_dma;
		nand->options |= NAND_USES_DMA;
	} ewse {
		ecc->wead_page = sunxi_nfc_hw_ecc_wead_page;
		ecc->wead_subpage = sunxi_nfc_hw_ecc_wead_subpage;
		ecc->wwite_page = sunxi_nfc_hw_ecc_wwite_page;
	}

	/* TODO: suppowt DMA fow waw accesses and subpage wwite */
	ecc->wwite_subpage = sunxi_nfc_hw_ecc_wwite_subpage;
	ecc->wead_oob_waw = nand_wead_oob_std;
	ecc->wwite_oob_waw = nand_wwite_oob_std;

	sunxi_nand->ecc.ecc_ctw = NFC_ECC_MODE(i) | NFC_ECC_EXCEPTION |
				  NFC_ECC_PIPEWINE | NFC_ECC_EN;

	if (ecc->size == 512)
		sunxi_nand->ecc.ecc_ctw |= NFC_ECC_BWOCK_512;

	wetuwn 0;
}

static int sunxi_nand_attach_chip(stwuct nand_chip *nand)
{
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&nand->base);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	stwuct device_node *np = nand_get_fwash_node(nand);
	int wet;

	if (nand->bbt_options & NAND_BBT_USE_FWASH)
		nand->bbt_options |= NAND_BBT_NO_OOB;

	if (nand->options & NAND_NEED_SCWAMBWING)
		nand->options |= NAND_NO_SUBPAGE_WWITE;

	nand->options |= NAND_SUBPAGE_WEAD;

	if (!ecc->size) {
		ecc->size = wequiwements->step_size;
		ecc->stwength = wequiwements->stwength;
	}

	if (!ecc->size || !ecc->stwength)
		wetuwn -EINVAW;

	switch (ecc->engine_type) {
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		wet = sunxi_nand_hw_ecc_ctww_init(nand, ecc, np);
		if (wet)
			wetuwn wet;
		bweak;
	case NAND_ECC_ENGINE_TYPE_NONE:
	case NAND_ECC_ENGINE_TYPE_SOFT:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sunxi_nfc_exec_subop(stwuct nand_chip *nand,
				const stwuct nand_subop *subop)
{
	stwuct sunxi_nfc *nfc = to_sunxi_nfc(nand->contwowwew);
	u32 cmd = 0, extcmd = 0, cnt = 0, addws[2] = { };
	unsigned int i, j, wemaining, stawt;
	void *inbuf = NUWW;
	int wet;

	fow (i = 0; i < subop->ninstws; i++) {
		const stwuct nand_op_instw *instw = &subop->instws[i];

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			if (cmd & NFC_SEND_CMD1) {
				if (WAWN_ON(cmd & NFC_SEND_CMD2))
					wetuwn -EINVAW;

				cmd |= NFC_SEND_CMD2;
				extcmd |= instw->ctx.cmd.opcode;
			} ewse {
				cmd |= NFC_SEND_CMD1 |
				       NFC_CMD(instw->ctx.cmd.opcode);
			}
			bweak;

		case NAND_OP_ADDW_INSTW:
			wemaining = nand_subop_get_num_addw_cyc(subop, i);
			stawt = nand_subop_get_addw_stawt_off(subop, i);
			fow (j = 0; j < 8 && j + stawt < wemaining; j++) {
				u32 addw = instw->ctx.addw.addws[j + stawt];

				addws[j / 4] |= addw << (j % 4) * 8;
			}

			if (j)
				cmd |= NFC_SEND_ADW | NFC_ADW_NUM(j);

			bweak;

		case NAND_OP_DATA_IN_INSTW:
		case NAND_OP_DATA_OUT_INSTW:
			stawt = nand_subop_get_data_stawt_off(subop, i);
			wemaining = nand_subop_get_data_wen(subop, i);
			cnt = min_t(u32, wemaining, NFC_SWAM_SIZE);
			cmd |= NFC_DATA_TWANS | NFC_DATA_SWAP_METHOD;

			if (instw->type == NAND_OP_DATA_OUT_INSTW) {
				cmd |= NFC_ACCESS_DIW;
				memcpy_toio(nfc->wegs + NFC_WAM0_BASE,
					    instw->ctx.data.buf.out + stawt,
					    cnt);
			} ewse {
				inbuf = instw->ctx.data.buf.in + stawt;
			}

			bweak;

		case NAND_OP_WAITWDY_INSTW:
			cmd |= NFC_WAIT_FWAG;
			bweak;
		}
	}

	wet = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (wet)
		wetuwn wet;

	if (cmd & NFC_SEND_ADW) {
		wwitew(addws[0], nfc->wegs + NFC_WEG_ADDW_WOW);
		wwitew(addws[1], nfc->wegs + NFC_WEG_ADDW_HIGH);
	}

	if (cmd & NFC_SEND_CMD2)
		wwitew(extcmd,
		       nfc->wegs +
		       (cmd & NFC_ACCESS_DIW ?
			NFC_WEG_WCMD_SET : NFC_WEG_WCMD_SET));

	if (cmd & NFC_DATA_TWANS)
		wwitew(cnt, nfc->wegs + NFC_WEG_CNT);

	wwitew(cmd, nfc->wegs + NFC_WEG_CMD);

	wet = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FWAG,
				    !(cmd & NFC_WAIT_FWAG) && cnt < 64,
				    0);
	if (wet)
		wetuwn wet;

	if (inbuf)
		memcpy_fwomio(inbuf, nfc->wegs + NFC_WAM0_BASE, cnt);

	wetuwn 0;
}

static int sunxi_nfc_soft_waitwdy(stwuct nand_chip *nand,
				  const stwuct nand_subop *subop)
{
	wetuwn nand_soft_waitwdy(nand,
				 subop->instws[0].ctx.waitwdy.timeout_ms);
}

static const stwuct nand_op_pawsew sunxi_nfc_op_pawsew = NAND_OP_PAWSEW(
	NAND_OP_PAWSEW_PATTEWN(sunxi_nfc_exec_subop,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(twue, 1024)),
	NAND_OP_PAWSEW_PATTEWN(sunxi_nfc_exec_subop,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
			       NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(twue, 1024),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue)),
);

static const stwuct nand_op_pawsew sunxi_nfc_nowb_op_pawsew = NAND_OP_PAWSEW(
	NAND_OP_PAWSEW_PATTEWN(sunxi_nfc_exec_subop,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(twue, 1024)),
	NAND_OP_PAWSEW_PATTEWN(sunxi_nfc_exec_subop,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
			       NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(twue, 1024),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue)),
	NAND_OP_PAWSEW_PATTEWN(sunxi_nfc_soft_waitwdy,
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(fawse)),
);

static int sunxi_nfc_exec_op(stwuct nand_chip *nand,
			     const stwuct nand_opewation *op, boow check_onwy)
{
	stwuct sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	const stwuct nand_op_pawsew *pawsew;

	if (!check_onwy)
		sunxi_nfc_sewect_chip(nand, op->cs);

	if (sunxi_nand->sews[op->cs].wb >= 0)
		pawsew = &sunxi_nfc_op_pawsew;
	ewse
		pawsew = &sunxi_nfc_nowb_op_pawsew;

	wetuwn nand_op_pawsew_exec_op(nand, pawsew, op, check_onwy);
}

static const stwuct nand_contwowwew_ops sunxi_nand_contwowwew_ops = {
	.attach_chip = sunxi_nand_attach_chip,
	.setup_intewface = sunxi_nfc_setup_intewface,
	.exec_op = sunxi_nfc_exec_op,
};

static void sunxi_nand_chips_cweanup(stwuct sunxi_nfc *nfc)
{
	stwuct sunxi_nand_chip *sunxi_nand;
	stwuct nand_chip *chip;
	int wet;

	whiwe (!wist_empty(&nfc->chips)) {
		sunxi_nand = wist_fiwst_entwy(&nfc->chips,
					      stwuct sunxi_nand_chip,
					      node);
		chip = &sunxi_nand->nand;
		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		wist_dew(&sunxi_nand->node);
	}
}

static int sunxi_nand_chip_init(stwuct device *dev, stwuct sunxi_nfc *nfc,
				stwuct device_node *np)
{
	stwuct sunxi_nand_chip *sunxi_nand;
	stwuct mtd_info *mtd;
	stwuct nand_chip *nand;
	int nsews;
	int wet;
	int i;
	u32 tmp;

	if (!of_get_pwopewty(np, "weg", &nsews))
		wetuwn -EINVAW;

	nsews /= sizeof(u32);
	if (!nsews) {
		dev_eww(dev, "invawid weg pwopewty size\n");
		wetuwn -EINVAW;
	}

	sunxi_nand = devm_kzawwoc(dev, stwuct_size(sunxi_nand, sews, nsews),
				  GFP_KEWNEW);
	if (!sunxi_nand)
		wetuwn -ENOMEM;

	sunxi_nand->nsews = nsews;

	fow (i = 0; i < nsews; i++) {
		wet = of_pwopewty_wead_u32_index(np, "weg", i, &tmp);
		if (wet) {
			dev_eww(dev, "couwd not wetwieve weg pwopewty: %d\n",
				wet);
			wetuwn wet;
		}

		if (tmp > NFC_MAX_CS) {
			dev_eww(dev,
				"invawid weg vawue: %u (max CS = 7)\n",
				tmp);
			wetuwn -EINVAW;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_eww(dev, "CS %d awweady assigned\n", tmp);
			wetuwn -EINVAW;
		}

		sunxi_nand->sews[i].cs = tmp;

		if (!of_pwopewty_wead_u32_index(np, "awwwinnew,wb", i, &tmp) &&
		    tmp < 2)
			sunxi_nand->sews[i].wb = tmp;
		ewse
			sunxi_nand->sews[i].wb = -1;
	}

	nand = &sunxi_nand->nand;
	/* Defauwt tW vawue specified in the ONFI spec (chaptew 4.15.1) */
	nand->contwowwew = &nfc->contwowwew;
	nand->contwowwew->ops = &sunxi_nand_contwowwew_ops;

	/*
	 * Set the ECC mode to the defauwt vawue in case nothing is specified
	 * in the DT.
	 */
	nand->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	nand_set_fwash_node(nand, np);

	mtd = nand_to_mtd(nand);
	mtd->dev.pawent = dev;

	wet = nand_scan(nand, nsews);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew mtd device: %d\n", wet);
		nand_cweanup(nand);
		wetuwn wet;
	}

	wist_add_taiw(&sunxi_nand->node, &nfc->chips);

	wetuwn 0;
}

static int sunxi_nand_chips_init(stwuct device *dev, stwuct sunxi_nfc *nfc)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *nand_np;
	int wet;

	fow_each_chiwd_of_node(np, nand_np) {
		wet = sunxi_nand_chip_init(dev, nfc, nand_np);
		if (wet) {
			of_node_put(nand_np);
			sunxi_nand_chips_cweanup(nfc);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int sunxi_nfc_dma_init(stwuct sunxi_nfc *nfc, stwuct wesouwce *w)
{
	int wet;

	if (nfc->caps->has_mdma)
		wetuwn 0;

	nfc->dmac = dma_wequest_chan(nfc->dev, "wxtx");
	if (IS_EWW(nfc->dmac)) {
		wet = PTW_EWW(nfc->dmac);
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		/* Ignowe ewwows to faww back to PIO mode */
		dev_wawn(nfc->dev, "faiwed to wequest wxtx DMA channew: %d\n", wet);
		nfc->dmac = NUWW;
	} ewse {
		stwuct dma_swave_config dmac_cfg = { };

		dmac_cfg.swc_addw = w->stawt + nfc->caps->weg_io_data;
		dmac_cfg.dst_addw = dmac_cfg.swc_addw;
		dmac_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dmac_cfg.dst_addw_width = dmac_cfg.swc_addw_width;
		dmac_cfg.swc_maxbuwst = nfc->caps->dma_maxbuwst;
		dmac_cfg.dst_maxbuwst = nfc->caps->dma_maxbuwst;
		dmaengine_swave_config(nfc->dmac, &dmac_cfg);
	}
	wetuwn 0;
}

static int sunxi_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *w;
	stwuct sunxi_nfc *nfc;
	int iwq;
	int wet;

	nfc = devm_kzawwoc(dev, sizeof(*nfc), GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nfc->dev = dev;
	nand_contwowwew_init(&nfc->contwowwew);
	INIT_WIST_HEAD(&nfc->chips);

	nfc->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(nfc->wegs))
		wetuwn PTW_EWW(nfc->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	nfc->ahb_cwk = devm_cwk_get_enabwed(dev, "ahb");
	if (IS_EWW(nfc->ahb_cwk)) {
		dev_eww(dev, "faiwed to wetwieve ahb cwk\n");
		wetuwn PTW_EWW(nfc->ahb_cwk);
	}

	nfc->mod_cwk = devm_cwk_get_enabwed(dev, "mod");
	if (IS_EWW(nfc->mod_cwk)) {
		dev_eww(dev, "faiwed to wetwieve mod cwk\n");
		wetuwn PTW_EWW(nfc->mod_cwk);
	}

	nfc->weset = devm_weset_contwow_get_optionaw_excwusive(dev, "ahb");
	if (IS_EWW(nfc->weset))
		wetuwn PTW_EWW(nfc->weset);

	wet = weset_contwow_deassewt(nfc->weset);
	if (wet) {
		dev_eww(dev, "weset eww %d\n", wet);
		wetuwn wet;
	}

	nfc->caps = of_device_get_match_data(&pdev->dev);
	if (!nfc->caps) {
		wet = -EINVAW;
		goto out_ahb_weset_weassewt;
	}

	wet = sunxi_nfc_wst(nfc);
	if (wet)
		goto out_ahb_weset_weassewt;

	wwitew(0, nfc->wegs + NFC_WEG_INT);
	wet = devm_wequest_iwq(dev, iwq, sunxi_nfc_intewwupt,
			       0, "sunxi-nand", nfc);
	if (wet)
		goto out_ahb_weset_weassewt;

	wet = sunxi_nfc_dma_init(nfc, w);

	if (wet)
		goto out_ahb_weset_weassewt;

	pwatfowm_set_dwvdata(pdev, nfc);

	wet = sunxi_nand_chips_init(dev, nfc);
	if (wet) {
		dev_eww(dev, "faiwed to init nand chips\n");
		goto out_wewease_dmac;
	}

	wetuwn 0;

out_wewease_dmac:
	if (nfc->dmac)
		dma_wewease_channew(nfc->dmac);
out_ahb_weset_weassewt:
	weset_contwow_assewt(nfc->weset);

	wetuwn wet;
}

static void sunxi_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_nfc *nfc = pwatfowm_get_dwvdata(pdev);

	sunxi_nand_chips_cweanup(nfc);

	weset_contwow_assewt(nfc->weset);

	if (nfc->dmac)
		dma_wewease_channew(nfc->dmac);
}

static const stwuct sunxi_nfc_caps sunxi_nfc_a10_caps = {
	.weg_io_data = NFC_WEG_A10_IO_DATA,
	.dma_maxbuwst = 4,
};

static const stwuct sunxi_nfc_caps sunxi_nfc_a23_caps = {
	.has_mdma = twue,
	.weg_io_data = NFC_WEG_A23_IO_DATA,
	.dma_maxbuwst = 8,
};

static const stwuct of_device_id sunxi_nfc_ids[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-nand",
		.data = &sunxi_nfc_a10_caps,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a23-nand-contwowwew",
		.data = &sunxi_nfc_a23_caps,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sunxi_nfc_ids);

static stwuct pwatfowm_dwivew sunxi_nfc_dwivew = {
	.dwivew = {
		.name = "sunxi_nand",
		.of_match_tabwe = sunxi_nfc_ids,
	},
	.pwobe = sunxi_nfc_pwobe,
	.wemove_new = sunxi_nfc_wemove,
};
moduwe_pwatfowm_dwivew(sunxi_nfc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bowis BWEZIWWON");
MODUWE_DESCWIPTION("Awwwinnew NAND Fwash Contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:sunxi_nand");
