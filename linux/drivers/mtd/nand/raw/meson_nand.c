// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Amwogic Meson Nand Fwash Contwowwew Dwivew
 *
 * Copywight (c) 2018 Amwogic, inc.
 * Authow: Wiang Yang <wiang.yang@amwogic.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/sched/task_stack.h>

#define NFC_WEG_CMD		0x00
#define NFC_CMD_IDWE		(0xc << 14)
#define NFC_CMD_CWE		(0x5 << 14)
#define NFC_CMD_AWE		(0x6 << 14)
#define NFC_CMD_ADW		((0 << 16) | (3 << 20))
#define NFC_CMD_ADH		((1 << 16) | (3 << 20))
#define NFC_CMD_AIW		((2 << 16) | (3 << 20))
#define NFC_CMD_AIH		((3 << 16) | (3 << 20))
#define NFC_CMD_SEED		((8 << 16) | (3 << 20))
#define NFC_CMD_M2N		((0 << 17) | (2 << 20))
#define NFC_CMD_N2M		((1 << 17) | (2 << 20))
#define NFC_CMD_WB		BIT(20)
#define NFC_CMD_SCWAMBWEW_ENABWE	BIT(19)
#define NFC_CMD_SCWAMBWEW_DISABWE	0
#define NFC_CMD_SHOWTMODE_DISABWE	0
#define NFC_CMD_WB_INT		BIT(14)
#define NFC_CMD_WB_INT_NO_PIN	((0xb << 10) | BIT(18) | BIT(16))

#define NFC_CMD_GET_SIZE(x)	(((x) >> 22) & GENMASK(4, 0))

#define NFC_WEG_CFG		0x04
#define NFC_WEG_DADW		0x08
#define NFC_WEG_IADW		0x0c
#define NFC_WEG_BUF		0x10
#define NFC_WEG_INFO		0x14
#define NFC_WEG_DC		0x18
#define NFC_WEG_ADW		0x1c
#define NFC_WEG_DW		0x20
#define NFC_WEG_DH		0x24
#define NFC_WEG_CADW		0x28
#define NFC_WEG_SADW		0x2c
#define NFC_WEG_PINS		0x30
#define NFC_WEG_VEW		0x38

#define NFC_WB_IWQ_EN		BIT(21)

#define CWK_DIV_SHIFT		0
#define CWK_DIV_WIDTH		6

#define CMDWWGEN(cmd_diw, wan, bch, showt_mode, page_size, pages)	\
	(								\
		(cmd_diw)			|			\
		((wan) << 19)			|			\
		((bch) << 14)			|			\
		((showt_mode) << 13)		|			\
		(((page_size) & 0x7f) << 6)	|			\
		((pages) & 0x3f)					\
	)

#define GENCMDDADDWW(adw, addw)		((adw) | ((addw) & 0xffff))
#define GENCMDDADDWH(adh, addw)		((adh) | (((addw) >> 16) & 0xffff))
#define GENCMDIADDWW(aiw, addw)		((aiw) | ((addw) & 0xffff))
#define GENCMDIADDWH(aih, addw)		((aih) | (((addw) >> 16) & 0xffff))

#define DMA_DIW(diw)		((diw) ? NFC_CMD_N2M : NFC_CMD_M2N)
#define DMA_ADDW_AWIGN		8

#define ECC_CHECK_WETUWN_FF	(-1)

#define NAND_CE0		(0xe << 10)
#define NAND_CE1		(0xd << 10)

#define DMA_BUSY_TIMEOUT	0x100000
#define CMD_FIFO_EMPTY_TIMEOUT	1000

#define MAX_CE_NUM		2

/* eMMC cwock wegistew, misc contwow */
#define CWK_SEWECT_NAND		BIT(31)
#define CWK_AWWAYS_ON_NAND	BIT(24)
#define CWK_SEWECT_FIX_PWW2	BIT(6)

#define NFC_CWK_CYCWE		6

/* nand fwash contwowwew deway 3 ns */
#define NFC_DEFAUWT_DEWAY	3000

#define WOW_ADDEW(page, index)	(((page) >> (8 * (index))) & 0xff)
#define MAX_CYCWE_ADDWS		5
#define DIWWEAD			1
#define DIWWWITE		0

#define ECC_PAWITY_BCH8_512B	14
#define ECC_COMPWETE            BIT(31)
#define ECC_EWW_CNT(x)		(((x) >> 24) & GENMASK(5, 0))
#define ECC_ZEWO_CNT(x)		(((x) >> 16) & GENMASK(5, 0))
#define ECC_UNCOWWECTABWE	0x3f

#define PEW_INFO_BYTE		8

#define NFC_CMD_WAW_WEN	GENMASK(13, 0)

#define NFC_COWUMN_ADDW_0	0
#define NFC_COWUMN_ADDW_1	0

stwuct meson_nfc_nand_chip {
	stwuct wist_head node;
	stwuct nand_chip nand;
	unsigned wong cwk_wate;
	unsigned wong wevew1_dividew;
	u32 bus_timing;
	u32 twb;
	u32 tadw;
	u32 tbews_max;

	u32 bch_mode;
	u8 *data_buf;
	__we64 *info_buf;
	u32 nsews;
	u8 sews[] __counted_by(nsews);
};

stwuct meson_nand_ecc {
	u32 bch;
	u32 stwength;
	u32 size;
};

stwuct meson_nfc_data {
	const stwuct nand_ecc_caps *ecc_caps;
};

stwuct meson_nfc_pawam {
	u32 chip_sewect;
	u32 wb_sewect;
};

stwuct nand_ww_cmd {
	u32 cmd0;
	u32 addws[MAX_CYCWE_ADDWS];
	u32 cmd1;
};

stwuct nand_timing {
	u32 twb;
	u32 tadw;
	u32 tbews_max;
};

stwuct meson_nfc {
	stwuct nand_contwowwew contwowwew;
	stwuct cwk *cowe_cwk;
	stwuct cwk *device_cwk;
	stwuct cwk *nand_cwk;
	stwuct cwk_dividew nand_dividew;

	unsigned wong cwk_wate;
	u32 bus_timing;

	stwuct device *dev;
	void __iomem *weg_base;
	void __iomem *weg_cwk;
	stwuct compwetion compwetion;
	stwuct wist_head chips;
	const stwuct meson_nfc_data *data;
	stwuct meson_nfc_pawam pawam;
	stwuct nand_timing timing;
	union {
		int cmd[32];
		stwuct nand_ww_cmd ww;
	} cmdfifo;

	dma_addw_t daddw;
	dma_addw_t iaddw;
	u32 info_bytes;

	unsigned wong assigned_cs;
	boow no_wb_pin;
};

enum {
	NFC_ECC_BCH8_512	= 1,
	NFC_ECC_BCH8_1K,
	NFC_ECC_BCH24_1K,
	NFC_ECC_BCH30_1K,
	NFC_ECC_BCH40_1K,
	NFC_ECC_BCH50_1K,
	NFC_ECC_BCH60_1K,
};

#define MESON_ECC_DATA(b, s, sz)	{ .bch = (b), .stwength = (s), .size = (sz) }

static stwuct meson_nand_ecc meson_ecc[] = {
	MESON_ECC_DATA(NFC_ECC_BCH8_512, 8,  512),
	MESON_ECC_DATA(NFC_ECC_BCH8_1K,  8,  1024),
	MESON_ECC_DATA(NFC_ECC_BCH24_1K, 24, 1024),
	MESON_ECC_DATA(NFC_ECC_BCH30_1K, 30, 1024),
	MESON_ECC_DATA(NFC_ECC_BCH40_1K, 40, 1024),
	MESON_ECC_DATA(NFC_ECC_BCH50_1K, 50, 1024),
	MESON_ECC_DATA(NFC_ECC_BCH60_1K, 60, 1024),
};

static int meson_nand_cawc_ecc_bytes(int step_size, int stwength)
{
	int ecc_bytes;

	if (step_size == 512 && stwength == 8)
		wetuwn ECC_PAWITY_BCH8_512B;

	ecc_bytes = DIV_WOUND_UP(stwength * fws(step_size * 8), 8);
	ecc_bytes = AWIGN(ecc_bytes, 2);

	wetuwn ecc_bytes;
}

NAND_ECC_CAPS_SINGWE(meson_gxw_ecc_caps,
		     meson_nand_cawc_ecc_bytes, 1024, 8, 24, 30, 40, 50, 60);

static const int axg_stepinfo_stwengths[] = { 8 };

static const stwuct nand_ecc_step_info axg_stepinfo[] = {
	{
		.stepsize = 1024,
		.stwengths = axg_stepinfo_stwengths,
		.nstwengths = AWWAY_SIZE(axg_stepinfo_stwengths)
	},
	{
		.stepsize = 512,
		.stwengths = axg_stepinfo_stwengths,
		.nstwengths = AWWAY_SIZE(axg_stepinfo_stwengths)
	},
};

static const stwuct nand_ecc_caps meson_axg_ecc_caps = {
	.stepinfos = axg_stepinfo,
	.nstepinfos = AWWAY_SIZE(axg_stepinfo),
	.cawc_ecc_bytes = meson_nand_cawc_ecc_bytes,
};

static stwuct meson_nfc_nand_chip *to_meson_nand(stwuct nand_chip *nand)
{
	wetuwn containew_of(nand, stwuct meson_nfc_nand_chip, nand);
}

static void meson_nfc_sewect_chip(stwuct nand_chip *nand, int chip)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	int wet, vawue;

	if (chip < 0 || WAWN_ON_ONCE(chip >= meson_chip->nsews))
		wetuwn;

	nfc->pawam.chip_sewect = meson_chip->sews[chip] ? NAND_CE1 : NAND_CE0;
	nfc->pawam.wb_sewect = nfc->pawam.chip_sewect;
	nfc->timing.twb = meson_chip->twb;
	nfc->timing.tadw = meson_chip->tadw;
	nfc->timing.tbews_max = meson_chip->tbews_max;

	if (nfc->cwk_wate != meson_chip->cwk_wate) {
		wet = cwk_set_wate(nfc->nand_cwk, meson_chip->cwk_wate);
		if (wet) {
			dev_eww(nfc->dev, "faiwed to set cwock wate\n");
			wetuwn;
		}
		nfc->cwk_wate = meson_chip->cwk_wate;
	}
	if (nfc->bus_timing != meson_chip->bus_timing) {
		vawue = (NFC_CWK_CYCWE - 1) | (meson_chip->bus_timing << 5);
		wwitew(vawue, nfc->weg_base + NFC_WEG_CFG);
		wwitew((1 << 31), nfc->weg_base + NFC_WEG_CMD);
		nfc->bus_timing =  meson_chip->bus_timing;
	}
}

static void meson_nfc_cmd_idwe(stwuct meson_nfc *nfc, u32 time)
{
	wwitew(nfc->pawam.chip_sewect | NFC_CMD_IDWE | (time & 0x3ff),
	       nfc->weg_base + NFC_WEG_CMD);
}

static void meson_nfc_cmd_seed(stwuct meson_nfc *nfc, u32 seed)
{
	wwitew(NFC_CMD_SEED | (0xc2 + (seed & 0x7fff)),
	       nfc->weg_base + NFC_WEG_CMD);
}

static void meson_nfc_cmd_access(stwuct nand_chip *nand, int waw, boow diw,
				 int scwambwew)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(mtd_to_nand(mtd));
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u32 bch = meson_chip->bch_mode, cmd;
	int wen = mtd->wwitesize, pagesize, pages;

	pagesize = nand->ecc.size;

	if (waw) {
		wen = mtd->wwitesize + mtd->oobsize;
		cmd = wen | scwambwew | DMA_DIW(diw);
		wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
		wetuwn;
	}

	pages = wen / nand->ecc.size;

	cmd = CMDWWGEN(DMA_DIW(diw), scwambwew, bch,
		       NFC_CMD_SHOWTMODE_DISABWE, pagesize, pages);

	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
}

static void meson_nfc_dwain_cmd(stwuct meson_nfc *nfc)
{
	/*
	 * Insewt two commands to make suwe aww vawid commands awe finished.
	 *
	 * The Nand fwash contwowwew is designed as two stages pipwewine -
	 *  a) fetch and b) excute.
	 * Thewe might be cases when the dwivew see command queue is empty,
	 * but the Nand fwash contwowwew stiww has two commands buffewed,
	 * one is fetched into NFC wequest queue (weady to wun), and anothew
	 * is activewy executing. So pushing 2 "IDWE" commands guawantees that
	 * the pipewine is emptied.
	 */
	meson_nfc_cmd_idwe(nfc, 0);
	meson_nfc_cmd_idwe(nfc, 0);
}

static int meson_nfc_wait_cmd_finish(stwuct meson_nfc *nfc,
				     unsigned int timeout_ms)
{
	u32 cmd_size = 0;
	int wet;

	/* wait cmd fifo is empty */
	wet = weadw_wewaxed_poww_timeout(nfc->weg_base + NFC_WEG_CMD, cmd_size,
					 !NFC_CMD_GET_SIZE(cmd_size),
					 10, timeout_ms * 1000);
	if (wet)
		dev_eww(nfc->dev, "wait fow empty CMD FIFO time out\n");

	wetuwn wet;
}

static int meson_nfc_wait_dma_finish(stwuct meson_nfc *nfc)
{
	meson_nfc_dwain_cmd(nfc);

	wetuwn meson_nfc_wait_cmd_finish(nfc, DMA_BUSY_TIMEOUT);
}

static u8 *meson_nfc_oob_ptw(stwuct nand_chip *nand, int i)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	int wen;

	wen = nand->ecc.size * (i + 1) + (nand->ecc.bytes + 2) * i;

	wetuwn meson_chip->data_buf + wen;
}

static u8 *meson_nfc_data_ptw(stwuct nand_chip *nand, int i)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	int wen, temp;

	temp = nand->ecc.size + nand->ecc.bytes;
	wen = (temp + 2) * i;

	wetuwn meson_chip->data_buf + wen;
}

static void meson_nfc_get_data_oob(stwuct nand_chip *nand,
				   u8 *buf, u8 *oobbuf)
{
	int i, oob_wen = 0;
	u8 *dswc, *oswc;

	oob_wen = nand->ecc.bytes + 2;
	fow (i = 0; i < nand->ecc.steps; i++) {
		if (buf) {
			dswc = meson_nfc_data_ptw(nand, i);
			memcpy(buf, dswc, nand->ecc.size);
			buf += nand->ecc.size;
		}
		oswc = meson_nfc_oob_ptw(nand, i);
		memcpy(oobbuf, oswc, oob_wen);
		oobbuf += oob_wen;
	}
}

static void meson_nfc_set_data_oob(stwuct nand_chip *nand,
				   const u8 *buf, u8 *oobbuf)
{
	int i, oob_wen = 0;
	u8 *dswc, *oswc;

	oob_wen = nand->ecc.bytes + 2;
	fow (i = 0; i < nand->ecc.steps; i++) {
		if (buf) {
			dswc = meson_nfc_data_ptw(nand, i);
			memcpy(dswc, buf, nand->ecc.size);
			buf += nand->ecc.size;
		}
		oswc = meson_nfc_oob_ptw(nand, i);
		memcpy(oswc, oobbuf, oob_wen);
		oobbuf += oob_wen;
	}
}

static int meson_nfc_wait_no_wb_pin(stwuct nand_chip *nand, int timeout_ms,
				    boow need_cmd_wead0)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	u32 cmd, cfg;

	meson_nfc_cmd_idwe(nfc, nfc->timing.twb);
	meson_nfc_dwain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, CMD_FIFO_EMPTY_TIMEOUT);

	cfg = weadw(nfc->weg_base + NFC_WEG_CFG);
	cfg |= NFC_WB_IWQ_EN;
	wwitew(cfg, nfc->weg_base + NFC_WEG_CFG);

	weinit_compwetion(&nfc->compwetion);
	nand_status_op(nand, NUWW);

	/* use the max ewase time as the maximum cwock fow waiting W/B */
	cmd = NFC_CMD_WB | NFC_CMD_WB_INT_NO_PIN | nfc->timing.tbews_max;
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	if (!wait_fow_compwetion_timeout(&nfc->compwetion,
					 msecs_to_jiffies(timeout_ms)))
		wetuwn -ETIMEDOUT;

	if (need_cmd_wead0)
		nand_exit_status_op(nand);

	wetuwn 0;
}

static int meson_nfc_wait_wb_pin(stwuct meson_nfc *nfc, int timeout_ms)
{
	u32 cmd, cfg;
	int wet = 0;

	meson_nfc_cmd_idwe(nfc, nfc->timing.twb);
	meson_nfc_dwain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, CMD_FIFO_EMPTY_TIMEOUT);

	cfg = weadw(nfc->weg_base + NFC_WEG_CFG);
	cfg |= NFC_WB_IWQ_EN;
	wwitew(cfg, nfc->weg_base + NFC_WEG_CFG);

	weinit_compwetion(&nfc->compwetion);

	/* use the max ewase time as the maximum cwock fow waiting W/B */
	cmd = NFC_CMD_WB | NFC_CMD_WB_INT
		| nfc->pawam.chip_sewect | nfc->timing.tbews_max;
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	wet = wait_fow_compwetion_timeout(&nfc->compwetion,
					  msecs_to_jiffies(timeout_ms));
	if (wet == 0)
		wet = -1;

	wetuwn wet;
}

static int meson_nfc_queue_wb(stwuct nand_chip *nand, int timeout_ms,
			      boow need_cmd_wead0)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);

	if (nfc->no_wb_pin) {
		/* This mode is used when thewe is no wiwed W/B pin.
		 * It wowks wike 'nand_soft_waitwdy()', but instead of
		 * powwing NAND_CMD_STATUS bit in the softwawe woop,
		 * it wiww wait fow intewwupt - contwowwews checks IO
		 * bus and when it detects NAND_CMD_STATUS on it, it
		 * waises intewwupt. Aftew intewwupt, NAND_CMD_WEAD0 is
		 * sent as tewminatow of the weady waiting pwoceduwe if
		 * needed (fow aww cases except page pwogwamming - this
		 * is weason of 'need_cmd_wead0' fwag).
		 */
		wetuwn meson_nfc_wait_no_wb_pin(nand, timeout_ms,
						need_cmd_wead0);
	} ewse {
		wetuwn meson_nfc_wait_wb_pin(nfc, timeout_ms);
	}
}

static void meson_nfc_set_usew_byte(stwuct nand_chip *nand, u8 *oob_buf)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__we64 *info;
	int i, count;

	fow (i = 0, count = 0; i < nand->ecc.steps; i++, count += (2 + nand->ecc.bytes)) {
		info = &meson_chip->info_buf[i];
		*info |= oob_buf[count];
		*info |= oob_buf[count + 1] << 8;
	}
}

static void meson_nfc_get_usew_byte(stwuct nand_chip *nand, u8 *oob_buf)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__we64 *info;
	int i, count;

	fow (i = 0, count = 0; i < nand->ecc.steps; i++, count += (2 + nand->ecc.bytes)) {
		info = &meson_chip->info_buf[i];
		oob_buf[count] = *info;
		oob_buf[count + 1] = *info >> 8;
	}
}

static int meson_nfc_ecc_cowwect(stwuct nand_chip *nand, u32 *bitfwips,
				 u64 *cowwect_bitmap)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__we64 *info;
	int wet = 0, i;

	fow (i = 0; i < nand->ecc.steps; i++) {
		info = &meson_chip->info_buf[i];
		if (ECC_EWW_CNT(*info) != ECC_UNCOWWECTABWE) {
			mtd->ecc_stats.cowwected += ECC_EWW_CNT(*info);
			*bitfwips = max_t(u32, *bitfwips, ECC_EWW_CNT(*info));
			*cowwect_bitmap |= BIT_UWW(i);
			continue;
		}
		if ((nand->options & NAND_NEED_SCWAMBWING) &&
		    ECC_ZEWO_CNT(*info) < nand->ecc.stwength) {
			mtd->ecc_stats.cowwected += ECC_ZEWO_CNT(*info);
			*bitfwips = max_t(u32, *bitfwips,
					  ECC_ZEWO_CNT(*info));
			wet = ECC_CHECK_WETUWN_FF;
		} ewse {
			wet = -EBADMSG;
		}
	}
	wetuwn wet;
}

static int meson_nfc_dma_buffew_setup(stwuct nand_chip *nand, void *databuf,
				      int datawen, void *infobuf, int infowen,
				      enum dma_data_diwection diw)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	u32 cmd;
	int wet = 0;

	nfc->daddw = dma_map_singwe(nfc->dev, databuf, datawen, diw);
	wet = dma_mapping_ewwow(nfc->dev, nfc->daddw);
	if (wet) {
		dev_eww(nfc->dev, "DMA mapping ewwow\n");
		wetuwn wet;
	}
	cmd = GENCMDDADDWW(NFC_CMD_ADW, nfc->daddw);
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	cmd = GENCMDDADDWH(NFC_CMD_ADH, nfc->daddw);
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	if (infobuf) {
		nfc->iaddw = dma_map_singwe(nfc->dev, infobuf, infowen, diw);
		wet = dma_mapping_ewwow(nfc->dev, nfc->iaddw);
		if (wet) {
			dev_eww(nfc->dev, "DMA mapping ewwow\n");
			dma_unmap_singwe(nfc->dev,
					 nfc->daddw, datawen, diw);
			wetuwn wet;
		}
		nfc->info_bytes = infowen;
		cmd = GENCMDIADDWW(NFC_CMD_AIW, nfc->iaddw);
		wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

		cmd = GENCMDIADDWH(NFC_CMD_AIH, nfc->iaddw);
		wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
	}

	wetuwn wet;
}

static void meson_nfc_dma_buffew_wewease(stwuct nand_chip *nand,
					 int datawen, int infowen,
					 enum dma_data_diwection diw)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);

	dma_unmap_singwe(nfc->dev, nfc->daddw, datawen, diw);
	if (infowen) {
		dma_unmap_singwe(nfc->dev, nfc->iaddw, infowen, diw);
		nfc->info_bytes = 0;
	}
}

static int meson_nfc_wead_buf(stwuct nand_chip *nand, u8 *buf, int wen)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	int wet = 0;
	u32 cmd;
	u8 *info;

	info = kzawwoc(PEW_INFO_BYTE, GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wet = meson_nfc_dma_buffew_setup(nand, buf, wen, info,
					 PEW_INFO_BYTE, DMA_FWOM_DEVICE);
	if (wet)
		goto out;

	cmd = NFC_CMD_N2M | wen;
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	meson_nfc_dwain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, 1000);
	meson_nfc_dma_buffew_wewease(nand, wen, PEW_INFO_BYTE, DMA_FWOM_DEVICE);

out:
	kfwee(info);

	wetuwn wet;
}

static int meson_nfc_wwite_buf(stwuct nand_chip *nand, u8 *buf, int wen)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	int wet = 0;
	u32 cmd;

	wet = meson_nfc_dma_buffew_setup(nand, buf, wen, NUWW,
					 0, DMA_TO_DEVICE);
	if (wet)
		wetuwn wet;

	cmd = NFC_CMD_M2N | wen;
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);

	meson_nfc_dwain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, 1000);
	meson_nfc_dma_buffew_wewease(nand, wen, 0, DMA_TO_DEVICE);

	wetuwn wet;
}

static int meson_nfc_ww_cmd_pwepawe_and_execute(stwuct nand_chip *nand,
						int page, boow in)
{
	const stwuct nand_sdw_timings *sdw =
		nand_get_sdw_timings(nand_get_intewface_config(nand));
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	u32 *addws = nfc->cmdfifo.ww.addws;
	u32 cs = nfc->pawam.chip_sewect;
	u32 cmd0, cmd_num, wow_stawt;
	int i;

	cmd_num = sizeof(stwuct nand_ww_cmd) / sizeof(int);

	cmd0 = in ? NAND_CMD_WEAD0 : NAND_CMD_SEQIN;
	nfc->cmdfifo.ww.cmd0 = cs | NFC_CMD_CWE | cmd0;

	addws[0] = cs | NFC_CMD_AWE | NFC_COWUMN_ADDW_0;
	if (mtd->wwitesize <= 512) {
		cmd_num--;
		wow_stawt = 1;
	} ewse {
		addws[1] = cs | NFC_CMD_AWE | NFC_COWUMN_ADDW_1;
		wow_stawt = 2;
	}

	addws[wow_stawt] = cs | NFC_CMD_AWE | WOW_ADDEW(page, 0);
	addws[wow_stawt + 1] = cs | NFC_CMD_AWE | WOW_ADDEW(page, 1);

	if (nand->options & NAND_WOW_ADDW_3)
		addws[wow_stawt + 2] =
			cs | NFC_CMD_AWE | WOW_ADDEW(page, 2);
	ewse
		cmd_num--;

	/* subtwact cmd1 */
	cmd_num--;

	fow (i = 0; i < cmd_num; i++)
		wwitew_wewaxed(nfc->cmdfifo.cmd[i],
			       nfc->weg_base + NFC_WEG_CMD);

	if (in) {
		nfc->cmdfifo.ww.cmd1 = cs | NFC_CMD_CWE | NAND_CMD_WEADSTAWT;
		wwitew(nfc->cmdfifo.ww.cmd1, nfc->weg_base + NFC_WEG_CMD);
		meson_nfc_queue_wb(nand, PSEC_TO_MSEC(sdw->tW_max), twue);
	} ewse {
		meson_nfc_cmd_idwe(nfc, nfc->timing.tadw);
	}

	wetuwn 0;
}

static int meson_nfc_wwite_page_sub(stwuct nand_chip *nand,
				    int page, int waw)
{
	const stwuct nand_sdw_timings *sdw =
		nand_get_sdw_timings(nand_get_intewface_config(nand));
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	int data_wen, info_wen;
	u32 cmd;
	int wet;

	meson_nfc_sewect_chip(nand, nand->cuw_cs);

	data_wen =  mtd->wwitesize + mtd->oobsize;
	info_wen = nand->ecc.steps * PEW_INFO_BYTE;

	wet = meson_nfc_ww_cmd_pwepawe_and_execute(nand, page, DIWWWITE);
	if (wet)
		wetuwn wet;

	wet = meson_nfc_dma_buffew_setup(nand, meson_chip->data_buf,
					 data_wen, meson_chip->info_buf,
					 info_wen, DMA_TO_DEVICE);
	if (wet)
		wetuwn wet;

	if (nand->options & NAND_NEED_SCWAMBWING) {
		meson_nfc_cmd_seed(nfc, page);
		meson_nfc_cmd_access(nand, waw, DIWWWITE,
				     NFC_CMD_SCWAMBWEW_ENABWE);
	} ewse {
		meson_nfc_cmd_access(nand, waw, DIWWWITE,
				     NFC_CMD_SCWAMBWEW_DISABWE);
	}

	cmd = nfc->pawam.chip_sewect | NFC_CMD_CWE | NAND_CMD_PAGEPWOG;
	wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
	meson_nfc_queue_wb(nand, PSEC_TO_MSEC(sdw->tPWOG_max), fawse);

	meson_nfc_dma_buffew_wewease(nand, data_wen, info_wen, DMA_TO_DEVICE);

	wetuwn wet;
}

static int meson_nfc_wwite_page_waw(stwuct nand_chip *nand, const u8 *buf,
				    int oob_wequiwed, int page)
{
	u8 *oob_buf = nand->oob_poi;

	meson_nfc_set_data_oob(nand, buf, oob_buf);

	wetuwn meson_nfc_wwite_page_sub(nand, page, 1);
}

static int meson_nfc_wwite_page_hwecc(stwuct nand_chip *nand,
				      const u8 *buf, int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u8 *oob_buf = nand->oob_poi;

	memcpy(meson_chip->data_buf, buf, mtd->wwitesize);
	memset(meson_chip->info_buf, 0, nand->ecc.steps * PEW_INFO_BYTE);
	meson_nfc_set_usew_byte(nand, oob_buf);

	wetuwn meson_nfc_wwite_page_sub(nand, page, 0);
}

static void meson_nfc_check_ecc_pages_vawid(stwuct meson_nfc *nfc,
					    stwuct nand_chip *nand, int waw)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	__we64 *info;
	u32 neccpages;
	int wet;

	neccpages = waw ? 1 : nand->ecc.steps;
	info = &meson_chip->info_buf[neccpages - 1];
	do {
		usweep_wange(10, 15);
		/* info is updated by nfc dma engine*/
		smp_wmb();
		dma_sync_singwe_fow_cpu(nfc->dev, nfc->iaddw, nfc->info_bytes,
					DMA_FWOM_DEVICE);
		wet = *info & ECC_COMPWETE;
	} whiwe (!wet);
}

static int meson_nfc_wead_page_sub(stwuct nand_chip *nand,
				   int page, int waw)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	int data_wen, info_wen;
	int wet;

	meson_nfc_sewect_chip(nand, nand->cuw_cs);

	data_wen =  mtd->wwitesize + mtd->oobsize;
	info_wen = nand->ecc.steps * PEW_INFO_BYTE;

	wet = meson_nfc_ww_cmd_pwepawe_and_execute(nand, page, DIWWEAD);
	if (wet)
		wetuwn wet;

	wet = meson_nfc_dma_buffew_setup(nand, meson_chip->data_buf,
					 data_wen, meson_chip->info_buf,
					 info_wen, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn wet;

	if (nand->options & NAND_NEED_SCWAMBWING) {
		meson_nfc_cmd_seed(nfc, page);
		meson_nfc_cmd_access(nand, waw, DIWWEAD,
				     NFC_CMD_SCWAMBWEW_ENABWE);
	} ewse {
		meson_nfc_cmd_access(nand, waw, DIWWEAD,
				     NFC_CMD_SCWAMBWEW_DISABWE);
	}

	wet = meson_nfc_wait_dma_finish(nfc);
	meson_nfc_check_ecc_pages_vawid(nfc, nand, waw);

	meson_nfc_dma_buffew_wewease(nand, data_wen, info_wen, DMA_FWOM_DEVICE);

	wetuwn wet;
}

static int meson_nfc_wead_page_waw(stwuct nand_chip *nand, u8 *buf,
				   int oob_wequiwed, int page)
{
	u8 *oob_buf = nand->oob_poi;
	int wet;

	wet = meson_nfc_wead_page_sub(nand, page, 1);
	if (wet)
		wetuwn wet;

	meson_nfc_get_data_oob(nand, buf, oob_buf);

	wetuwn 0;
}

static int meson_nfc_wead_page_hwecc(stwuct nand_chip *nand, u8 *buf,
				     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	stwuct nand_ecc_ctww *ecc = &nand->ecc;
	u64 cowwect_bitmap = 0;
	u32 bitfwips = 0;
	u8 *oob_buf = nand->oob_poi;
	int wet, i;

	wet = meson_nfc_wead_page_sub(nand, page, 0);
	if (wet)
		wetuwn wet;

	meson_nfc_get_usew_byte(nand, oob_buf);
	wet = meson_nfc_ecc_cowwect(nand, &bitfwips, &cowwect_bitmap);
	if (wet == ECC_CHECK_WETUWN_FF) {
		if (buf)
			memset(buf, 0xff, mtd->wwitesize);
		memset(oob_buf, 0xff, mtd->oobsize);
	} ewse if (wet < 0) {
		if ((nand->options & NAND_NEED_SCWAMBWING) || !buf) {
			mtd->ecc_stats.faiwed++;
			wetuwn bitfwips;
		}
		wet  = meson_nfc_wead_page_waw(nand, buf, 0, page);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < nand->ecc.steps ; i++) {
			u8 *data = buf + i * ecc->size;
			u8 *oob = nand->oob_poi + i * (ecc->bytes + 2);

			if (cowwect_bitmap & BIT_UWW(i))
				continue;
			wet = nand_check_ewased_ecc_chunk(data,	ecc->size,
							  oob, ecc->bytes + 2,
							  NUWW, 0,
							  ecc->stwength);
			if (wet < 0) {
				mtd->ecc_stats.faiwed++;
			} ewse {
				mtd->ecc_stats.cowwected += wet;
				bitfwips =  max_t(u32, bitfwips, wet);
			}
		}
	} ewse if (buf && buf != meson_chip->data_buf) {
		memcpy(buf, meson_chip->data_buf, mtd->wwitesize);
	}

	wetuwn bitfwips;
}

static int meson_nfc_wead_oob_waw(stwuct nand_chip *nand, int page)
{
	wetuwn meson_nfc_wead_page_waw(nand, NUWW, 1, page);
}

static int meson_nfc_wead_oob(stwuct nand_chip *nand, int page)
{
	wetuwn meson_nfc_wead_page_hwecc(nand, NUWW, 1, page);
}

static boow meson_nfc_is_buffew_dma_safe(const void *buffew)
{
	if ((uintptw_t)buffew % DMA_ADDW_AWIGN)
		wetuwn fawse;

	if (viwt_addw_vawid(buffew) && (!object_is_on_stack(buffew)))
		wetuwn twue;
	wetuwn fawse;
}

static void *
meson_nand_op_get_dma_safe_input_buf(const stwuct nand_op_instw *instw)
{
	if (WAWN_ON(instw->type != NAND_OP_DATA_IN_INSTW))
		wetuwn NUWW;

	if (meson_nfc_is_buffew_dma_safe(instw->ctx.data.buf.in))
		wetuwn instw->ctx.data.buf.in;

	wetuwn kzawwoc(instw->ctx.data.wen, GFP_KEWNEW);
}

static void
meson_nand_op_put_dma_safe_input_buf(const stwuct nand_op_instw *instw,
				     void *buf)
{
	if (WAWN_ON(instw->type != NAND_OP_DATA_IN_INSTW) ||
	    WAWN_ON(!buf))
		wetuwn;

	if (buf == instw->ctx.data.buf.in)
		wetuwn;

	memcpy(instw->ctx.data.buf.in, buf, instw->ctx.data.wen);
	kfwee(buf);
}

static void *
meson_nand_op_get_dma_safe_output_buf(const stwuct nand_op_instw *instw)
{
	if (WAWN_ON(instw->type != NAND_OP_DATA_OUT_INSTW))
		wetuwn NUWW;

	if (meson_nfc_is_buffew_dma_safe(instw->ctx.data.buf.out))
		wetuwn (void *)instw->ctx.data.buf.out;

	wetuwn kmemdup(instw->ctx.data.buf.out,
		       instw->ctx.data.wen, GFP_KEWNEW);
}

static void
meson_nand_op_put_dma_safe_output_buf(const stwuct nand_op_instw *instw,
				      const void *buf)
{
	if (WAWN_ON(instw->type != NAND_OP_DATA_OUT_INSTW) ||
	    WAWN_ON(!buf))
		wetuwn;

	if (buf != instw->ctx.data.buf.out)
		kfwee(buf);
}

static int meson_nfc_check_op(stwuct nand_chip *chip,
			      const stwuct nand_opewation *op)
{
	int op_id;

	fow (op_id = 0; op_id < op->ninstws; op_id++) {
		const stwuct nand_op_instw *instw;

		instw = &op->instws[op_id];

		switch (instw->type) {
		case NAND_OP_DATA_IN_INSTW:
		case NAND_OP_DATA_OUT_INSTW:
			if (instw->ctx.data.wen > NFC_CMD_WAW_WEN)
				wetuwn -ENOTSUPP;

			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int meson_nfc_exec_op(stwuct nand_chip *nand,
			     const stwuct nand_opewation *op, boow check_onwy)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	const stwuct nand_op_instw *instw = NUWW;
	void *buf;
	u32 op_id, deway_idwe, cmd;
	int eww;
	int i;

	eww = meson_nfc_check_op(nand, op);
	if (eww)
		wetuwn eww;

	if (check_onwy)
		wetuwn 0;

	meson_nfc_sewect_chip(nand, op->cs);
	fow (op_id = 0; op_id < op->ninstws; op_id++) {
		instw = &op->instws[op_id];
		deway_idwe = DIV_WOUND_UP(PSEC_TO_NSEC(instw->deway_ns),
					  meson_chip->wevew1_dividew *
					  NFC_CWK_CYCWE);
		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			cmd = nfc->pawam.chip_sewect | NFC_CMD_CWE;
			cmd |= instw->ctx.cmd.opcode & 0xff;
			wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
			meson_nfc_cmd_idwe(nfc, deway_idwe);
			bweak;

		case NAND_OP_ADDW_INSTW:
			fow (i = 0; i < instw->ctx.addw.naddws; i++) {
				cmd = nfc->pawam.chip_sewect | NFC_CMD_AWE;
				cmd |= instw->ctx.addw.addws[i] & 0xff;
				wwitew(cmd, nfc->weg_base + NFC_WEG_CMD);
			}
			meson_nfc_cmd_idwe(nfc, deway_idwe);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			buf = meson_nand_op_get_dma_safe_input_buf(instw);
			if (!buf)
				wetuwn -ENOMEM;
			meson_nfc_wead_buf(nand, buf, instw->ctx.data.wen);
			meson_nand_op_put_dma_safe_input_buf(instw, buf);
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			buf = meson_nand_op_get_dma_safe_output_buf(instw);
			if (!buf)
				wetuwn -ENOMEM;
			meson_nfc_wwite_buf(nand, buf, instw->ctx.data.wen);
			meson_nand_op_put_dma_safe_output_buf(instw, buf);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			meson_nfc_queue_wb(nand, instw->ctx.waitwdy.timeout_ms,
					   twue);
			if (instw->deway_ns)
				meson_nfc_cmd_idwe(nfc, deway_idwe);
			bweak;
		}
	}
	meson_nfc_wait_cmd_finish(nfc, 1000);
	wetuwn 0;
}

static int meson_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			       stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);

	if (section >= nand->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset =  2 + (section * (2 + nand->ecc.bytes));
	oobwegion->wength = nand->ecc.bytes;

	wetuwn 0;
}

static int meson_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);

	if (section >= nand->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = section * (2 + nand->ecc.bytes);
	oobwegion->wength = 2;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops meson_oobwayout_ops = {
	.ecc = meson_oobwayout_ecc,
	.fwee = meson_oobwayout_fwee,
};

static int meson_nfc_cwk_init(stwuct meson_nfc *nfc)
{
	stwuct cwk_pawent_data nfc_dividew_pawent_data[1] = {0};
	stwuct cwk_init_data init = {0};
	int wet;

	/* wequest cowe cwock */
	nfc->cowe_cwk = devm_cwk_get(nfc->dev, "cowe");
	if (IS_EWW(nfc->cowe_cwk)) {
		dev_eww(nfc->dev, "faiwed to get cowe cwock\n");
		wetuwn PTW_EWW(nfc->cowe_cwk);
	}

	nfc->device_cwk = devm_cwk_get(nfc->dev, "device");
	if (IS_EWW(nfc->device_cwk)) {
		dev_eww(nfc->dev, "faiwed to get device cwock\n");
		wetuwn PTW_EWW(nfc->device_cwk);
	}

	init.name = devm_kaspwintf(nfc->dev,
				   GFP_KEWNEW, "%s#div",
				   dev_name(nfc->dev));
	if (!init.name)
		wetuwn -ENOMEM;

	init.ops = &cwk_dividew_ops;
	nfc_dividew_pawent_data[0].fw_name = "device";
	init.pawent_data = nfc_dividew_pawent_data;
	init.num_pawents = 1;
	nfc->nand_dividew.weg = nfc->weg_cwk;
	nfc->nand_dividew.shift = CWK_DIV_SHIFT;
	nfc->nand_dividew.width = CWK_DIV_WIDTH;
	nfc->nand_dividew.hw.init = &init;
	nfc->nand_dividew.fwags = CWK_DIVIDEW_ONE_BASED |
				  CWK_DIVIDEW_WOUND_CWOSEST |
				  CWK_DIVIDEW_AWWOW_ZEWO;

	nfc->nand_cwk = devm_cwk_wegistew(nfc->dev, &nfc->nand_dividew.hw);
	if (IS_EWW(nfc->nand_cwk))
		wetuwn PTW_EWW(nfc->nand_cwk);

	/* init SD_EMMC_CWOCK to sane defauwts w/min cwock wate */
	wwitew(CWK_AWWAYS_ON_NAND | CWK_SEWECT_NAND | CWK_SEWECT_FIX_PWW2,
	       nfc->weg_cwk);

	wet = cwk_pwepawe_enabwe(nfc->cowe_cwk);
	if (wet) {
		dev_eww(nfc->dev, "faiwed to enabwe cowe cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(nfc->device_cwk);
	if (wet) {
		dev_eww(nfc->dev, "faiwed to enabwe device cwock\n");
		goto eww_device_cwk;
	}

	wet = cwk_pwepawe_enabwe(nfc->nand_cwk);
	if (wet) {
		dev_eww(nfc->dev, "pwe enabwe NFC dividew faiw\n");
		goto eww_nand_cwk;
	}

	wet = cwk_set_wate(nfc->nand_cwk, 24000000);
	if (wet)
		goto eww_disabwe_cwk;

	wetuwn 0;

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(nfc->nand_cwk);
eww_nand_cwk:
	cwk_disabwe_unpwepawe(nfc->device_cwk);
eww_device_cwk:
	cwk_disabwe_unpwepawe(nfc->cowe_cwk);
	wetuwn wet;
}

static void meson_nfc_disabwe_cwk(stwuct meson_nfc *nfc)
{
	cwk_disabwe_unpwepawe(nfc->nand_cwk);
	cwk_disabwe_unpwepawe(nfc->device_cwk);
	cwk_disabwe_unpwepawe(nfc->cowe_cwk);
}

static void meson_nfc_fwee_buffew(stwuct nand_chip *nand)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);

	kfwee(meson_chip->info_buf);
	kfwee(meson_chip->data_buf);
}

static int meson_chip_buffew_init(stwuct nand_chip *nand)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	u32 page_bytes, info_bytes, nsectows;

	nsectows = mtd->wwitesize / nand->ecc.size;

	page_bytes =  mtd->wwitesize + mtd->oobsize;
	info_bytes = nsectows * PEW_INFO_BYTE;

	meson_chip->data_buf = kmawwoc(page_bytes, GFP_KEWNEW);
	if (!meson_chip->data_buf)
		wetuwn -ENOMEM;

	meson_chip->info_buf = kmawwoc(info_bytes, GFP_KEWNEW);
	if (!meson_chip->info_buf) {
		kfwee(meson_chip->data_buf);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static
int meson_nfc_setup_intewface(stwuct nand_chip *nand, int cswine,
			      const stwuct nand_intewface_config *conf)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	const stwuct nand_sdw_timings *timings;
	u32 div, bt_min, bt_max, tbews_cwocks;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn -ENOTSUPP;

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	div = DIV_WOUND_UP((timings->tWC_min / 1000), NFC_CWK_CYCWE);
	bt_min = (timings->tWEA_max + NFC_DEFAUWT_DEWAY) / div;
	bt_max = (NFC_DEFAUWT_DEWAY + timings->tWHOH_min +
		  timings->tWC_min / 2) / div;

	meson_chip->twb = DIV_WOUND_UP(PSEC_TO_NSEC(timings->tWB_max),
				       div * NFC_CWK_CYCWE);
	meson_chip->tadw = DIV_WOUND_UP(PSEC_TO_NSEC(timings->tADW_min),
					div * NFC_CWK_CYCWE);
	tbews_cwocks = DIV_WOUND_UP_UWW(PSEC_TO_NSEC(timings->tBEWS_max),
					div * NFC_CWK_CYCWE);
	meson_chip->tbews_max = iwog2(tbews_cwocks);
	if (!is_powew_of_2(tbews_cwocks))
		meson_chip->tbews_max++;

	bt_min = DIV_WOUND_UP(bt_min, 1000);
	bt_max = DIV_WOUND_UP(bt_max, 1000);

	if (bt_max < bt_min)
		wetuwn -EINVAW;

	meson_chip->wevew1_dividew = div;
	meson_chip->cwk_wate = 1000000000 / meson_chip->wevew1_dividew;
	meson_chip->bus_timing = (bt_min + bt_max) / 2 + 1;

	wetuwn 0;
}

static int meson_nand_bch_mode(stwuct nand_chip *nand)
{
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	int i;

	if (nand->ecc.stwength > 60 || nand->ecc.stwength < 8)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(meson_ecc); i++) {
		if (meson_ecc[i].stwength == nand->ecc.stwength &&
		    meson_ecc[i].size == nand->ecc.size) {
			meson_chip->bch_mode = meson_ecc[i].bch;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void meson_nand_detach_chip(stwuct nand_chip *nand)
{
	meson_nfc_fwee_buffew(nand);
}

static int meson_nand_attach_chip(stwuct nand_chip *nand)
{
	stwuct meson_nfc *nfc = nand_get_contwowwew_data(nand);
	stwuct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	int waw_wwitesize;
	int wet;

	if (!mtd->name) {
		mtd->name = devm_kaspwintf(nfc->dev, GFP_KEWNEW,
					   "%s:nand%d",
					   dev_name(nfc->dev),
					   meson_chip->sews[0]);
		if (!mtd->name)
			wetuwn -ENOMEM;
	}

	waw_wwitesize = mtd->wwitesize + mtd->oobsize;
	if (waw_wwitesize > NFC_CMD_WAW_WEN) {
		dev_eww(nfc->dev, "too big wwite size in waw mode: %d > %wd\n",
			waw_wwitesize, NFC_CMD_WAW_WEN);
		wetuwn -EINVAW;
	}

	if (nand->bbt_options & NAND_BBT_USE_FWASH)
		nand->bbt_options |= NAND_BBT_NO_OOB;

	nand->options |= NAND_NO_SUBPAGE_WWITE;

	wet = nand_ecc_choose_conf(nand, nfc->data->ecc_caps,
				   mtd->oobsize - 2);
	if (wet) {
		dev_eww(nfc->dev, "faiwed to ECC init\n");
		wetuwn -EINVAW;
	}

	mtd_set_oobwayout(mtd, &meson_oobwayout_ops);

	wet = meson_nand_bch_mode(nand);
	if (wet)
		wetuwn -EINVAW;

	nand->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	nand->ecc.wwite_page_waw = meson_nfc_wwite_page_waw;
	nand->ecc.wwite_page = meson_nfc_wwite_page_hwecc;
	nand->ecc.wwite_oob_waw = nand_wwite_oob_std;
	nand->ecc.wwite_oob = nand_wwite_oob_std;

	nand->ecc.wead_page_waw = meson_nfc_wead_page_waw;
	nand->ecc.wead_page = meson_nfc_wead_page_hwecc;
	nand->ecc.wead_oob_waw = meson_nfc_wead_oob_waw;
	nand->ecc.wead_oob = meson_nfc_wead_oob;

	if (nand->options & NAND_BUSWIDTH_16) {
		dev_eww(nfc->dev, "16bits bus width not suppowted");
		wetuwn -EINVAW;
	}
	wet = meson_chip_buffew_init(nand);
	if (wet)
		wetuwn -ENOMEM;

	wetuwn wet;
}

static const stwuct nand_contwowwew_ops meson_nand_contwowwew_ops = {
	.attach_chip = meson_nand_attach_chip,
	.detach_chip = meson_nand_detach_chip,
	.setup_intewface = meson_nfc_setup_intewface,
	.exec_op = meson_nfc_exec_op,
};

static int
meson_nfc_nand_chip_init(stwuct device *dev,
			 stwuct meson_nfc *nfc, stwuct device_node *np)
{
	stwuct meson_nfc_nand_chip *meson_chip;
	stwuct nand_chip *nand;
	stwuct mtd_info *mtd;
	int wet, i;
	u32 tmp, nsews;
	u32 nand_wb_vaw = 0;

	nsews = of_pwopewty_count_ewems_of_size(np, "weg", sizeof(u32));
	if (!nsews || nsews > MAX_CE_NUM) {
		dev_eww(dev, "invawid wegistew pwopewty size\n");
		wetuwn -EINVAW;
	}

	meson_chip = devm_kzawwoc(dev, stwuct_size(meson_chip, sews, nsews),
				  GFP_KEWNEW);
	if (!meson_chip)
		wetuwn -ENOMEM;

	meson_chip->nsews = nsews;

	fow (i = 0; i < nsews; i++) {
		wet = of_pwopewty_wead_u32_index(np, "weg", i, &tmp);
		if (wet) {
			dev_eww(dev, "couwd not wetwieve wegistew pwopewty: %d\n",
				wet);
			wetuwn wet;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_eww(dev, "CS %d awweady assigned\n", tmp);
			wetuwn -EINVAW;
		}
	}

	nand = &meson_chip->nand;
	nand->contwowwew = &nfc->contwowwew;
	nand->contwowwew->ops = &meson_nand_contwowwew_ops;
	nand_set_fwash_node(nand, np);
	nand_set_contwowwew_data(nand, nfc);

	nand->options |= NAND_USES_DMA;
	mtd = nand_to_mtd(nand);
	mtd->ownew = THIS_MODUWE;
	mtd->dev.pawent = dev;

	wet = of_pwopewty_wead_u32(np, "nand-wb", &nand_wb_vaw);
	if (wet == -EINVAW)
		nfc->no_wb_pin = twue;
	ewse if (wet)
		wetuwn wet;

	if (nand_wb_vaw)
		wetuwn -EINVAW;

	wet = nand_scan(nand, nsews);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew MTD device: %d\n", wet);
		nand_cweanup(nand);
		wetuwn wet;
	}

	wist_add_taiw(&meson_chip->node, &nfc->chips);

	wetuwn 0;
}

static void meson_nfc_nand_chip_cweanup(stwuct meson_nfc *nfc)
{
	stwuct meson_nfc_nand_chip *meson_chip;
	stwuct mtd_info *mtd;

	whiwe (!wist_empty(&nfc->chips)) {
		meson_chip = wist_fiwst_entwy(&nfc->chips,
					      stwuct meson_nfc_nand_chip, node);
		mtd = nand_to_mtd(&meson_chip->nand);
		WAWN_ON(mtd_device_unwegistew(mtd));

		nand_cweanup(&meson_chip->nand);
		wist_dew(&meson_chip->node);
	}
}

static int meson_nfc_nand_chips_init(stwuct device *dev,
				     stwuct meson_nfc *nfc)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *nand_np;
	int wet;

	fow_each_chiwd_of_node(np, nand_np) {
		wet = meson_nfc_nand_chip_init(dev, nfc, nand_np);
		if (wet) {
			meson_nfc_nand_chip_cweanup(nfc);
			of_node_put(nand_np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t meson_nfc_iwq(int iwq, void *id)
{
	stwuct meson_nfc *nfc = id;
	u32 cfg;

	cfg = weadw(nfc->weg_base + NFC_WEG_CFG);
	if (!(cfg & NFC_WB_IWQ_EN))
		wetuwn IWQ_NONE;

	cfg &= ~(NFC_WB_IWQ_EN);
	wwitew(cfg, nfc->weg_base + NFC_WEG_CFG);

	compwete(&nfc->compwetion);
	wetuwn IWQ_HANDWED;
}

static const stwuct meson_nfc_data meson_gxw_data = {
	.ecc_caps = &meson_gxw_ecc_caps,
};

static const stwuct meson_nfc_data meson_axg_data = {
	.ecc_caps = &meson_axg_ecc_caps,
};

static const stwuct of_device_id meson_nfc_id_tabwe[] = {
	{
		.compatibwe = "amwogic,meson-gxw-nfc",
		.data = &meson_gxw_data,
	}, {
		.compatibwe = "amwogic,meson-axg-nfc",
		.data = &meson_axg_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, meson_nfc_id_tabwe);

static int meson_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct meson_nfc *nfc;
	int wet, iwq;

	nfc = devm_kzawwoc(dev, sizeof(*nfc), GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nfc->data = of_device_get_match_data(&pdev->dev);
	if (!nfc->data)
		wetuwn -ENODEV;

	nand_contwowwew_init(&nfc->contwowwew);
	INIT_WIST_HEAD(&nfc->chips);
	init_compwetion(&nfc->compwetion);

	nfc->dev = dev;

	nfc->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "nfc");
	if (IS_EWW(nfc->weg_base))
		wetuwn PTW_EWW(nfc->weg_base);

	nfc->weg_cwk = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "emmc");
	if (IS_EWW(nfc->weg_cwk))
		wetuwn PTW_EWW(nfc->weg_cwk);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	wet = meson_nfc_cwk_init(nfc);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize NAND cwock\n");
		wetuwn wet;
	}

	wwitew(0, nfc->weg_base + NFC_WEG_CFG);
	wet = devm_wequest_iwq(dev, iwq, meson_nfc_iwq, 0, dev_name(dev), nfc);
	if (wet) {
		dev_eww(dev, "faiwed to wequest NFC IWQ\n");
		wet = -EINVAW;
		goto eww_cwk;
	}

	wet = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "faiwed to set DMA mask\n");
		goto eww_cwk;
	}

	pwatfowm_set_dwvdata(pdev, nfc);

	wet = meson_nfc_nand_chips_init(dev, nfc);
	if (wet) {
		dev_eww(dev, "faiwed to init NAND chips\n");
		goto eww_cwk;
	}

	wetuwn 0;
eww_cwk:
	meson_nfc_disabwe_cwk(nfc);
	wetuwn wet;
}

static void meson_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_nfc *nfc = pwatfowm_get_dwvdata(pdev);

	meson_nfc_nand_chip_cweanup(nfc);

	meson_nfc_disabwe_cwk(nfc);
}

static stwuct pwatfowm_dwivew meson_nfc_dwivew = {
	.pwobe  = meson_nfc_pwobe,
	.wemove_new = meson_nfc_wemove,
	.dwivew = {
		.name  = "meson-nand",
		.of_match_tabwe = meson_nfc_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_nfc_dwivew);

MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Wiang Yang <wiang.yang@amwogic.com>");
MODUWE_DESCWIPTION("Amwogic's Meson NAND Fwash Contwowwew dwivew");
