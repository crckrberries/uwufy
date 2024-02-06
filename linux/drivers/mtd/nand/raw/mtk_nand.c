// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * MTK NAND Fwash contwowwew dwivew.
 * Copywight (C) 2016 MediaTek Inc.
 * Authows:	Xiaowei Wi		<xiaowei.wi@mediatek.com>
 *		Jowge Wamiwez-Owtiz	<jowge.wamiwez-owtiz@winawo.owg>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/mtd/nand-ecc-mtk.h>

/* NAND contwowwew wegistew definition */
#define NFI_CNFG		(0x00)
#define		CNFG_AHB		BIT(0)
#define		CNFG_WEAD_EN		BIT(1)
#define		CNFG_DMA_BUWST_EN	BIT(2)
#define		CNFG_BYTE_WW		BIT(6)
#define		CNFG_HW_ECC_EN		BIT(8)
#define		CNFG_AUTO_FMT_EN	BIT(9)
#define		CNFG_OP_CUST		(6 << 12)
#define NFI_PAGEFMT		(0x04)
#define		PAGEFMT_FDM_ECC_SHIFT	(12)
#define		PAGEFMT_FDM_SHIFT	(8)
#define		PAGEFMT_SEC_SEW_512	BIT(2)
#define		PAGEFMT_512_2K		(0)
#define		PAGEFMT_2K_4K		(1)
#define		PAGEFMT_4K_8K		(2)
#define		PAGEFMT_8K_16K		(3)
/* NFI contwow */
#define NFI_CON			(0x08)
#define		CON_FIFO_FWUSH		BIT(0)
#define		CON_NFI_WST		BIT(1)
#define		CON_BWD			BIT(8)  /* buwst  wead */
#define		CON_BWW			BIT(9)	/* buwst  wwite */
#define		CON_SEC_SHIFT		(12)
/* Timming contwow wegistew */
#define NFI_ACCCON		(0x0C)
#define NFI_INTW_EN		(0x10)
#define		INTW_AHB_DONE_EN	BIT(6)
#define NFI_INTW_STA		(0x14)
#define NFI_CMD			(0x20)
#define NFI_ADDWNOB		(0x30)
#define NFI_COWADDW		(0x34)
#define NFI_WOWADDW		(0x38)
#define NFI_STWDATA		(0x40)
#define		STAW_EN			(1)
#define		STAW_DE			(0)
#define NFI_CNWNB		(0x44)
#define NFI_DATAW		(0x50)
#define NFI_DATAW		(0x54)
#define NFI_PIO_DIWDY		(0x58)
#define		PIO_DI_WDY		(0x01)
#define NFI_STA			(0x60)
#define		STA_CMD			BIT(0)
#define		STA_ADDW		BIT(1)
#define		STA_BUSY		BIT(8)
#define		STA_EMP_PAGE		BIT(12)
#define		NFI_FSM_CUSTDATA	(0xe << 16)
#define		NFI_FSM_MASK		(0xf << 16)
#define NFI_ADDWCNTW		(0x70)
#define		CNTW_MASK		GENMASK(16, 12)
#define		ADDWCNTW_SEC_SHIFT	(12)
#define		ADDWCNTW_SEC(vaw) \
		(((vaw) & CNTW_MASK) >> ADDWCNTW_SEC_SHIFT)
#define NFI_STWADDW		(0x80)
#define NFI_BYTEWEN		(0x84)
#define NFI_CSEW		(0x90)
#define NFI_FDMW(x)		(0xA0 + (x) * sizeof(u32) * 2)
#define NFI_FDMM(x)		(0xA4 + (x) * sizeof(u32) * 2)
#define NFI_FDM_MAX_SIZE	(8)
#define NFI_FDM_MIN_SIZE	(1)
#define NFI_DEBUG_CON1		(0x220)
#define		STWOBE_MASK		GENMASK(4, 3)
#define		STWOBE_SHIFT		(3)
#define		MAX_STWOBE_DWY		(3)
#define NFI_MASTEW_STA		(0x224)
#define		MASTEW_STA_MASK		(0x0FFF)
#define NFI_EMPTY_THWESH	(0x23C)

#define MTK_NAME		"mtk-nand"
#define KB(x)			((x) * 1024UW)
#define MB(x)			(KB(x) * 1024UW)

#define MTK_TIMEOUT		(500000)
#define MTK_WESET_TIMEOUT	(1000000)
#define MTK_NAND_MAX_NSEWS	(2)
#define MTK_NFC_MIN_SPAWE	(16)
#define ACCTIMING(tpoecs, tpwecs, tc2w, tw2w, twh, twst, twwt) \
	((tpoecs) << 28 | (tpwecs) << 22 | (tc2w) << 16 | \
	(tw2w) << 12 | (twh) << 8 | (twst) << 4 | (twwt))

stwuct mtk_nfc_caps {
	const u8 *spawe_size;
	u8 num_spawe_size;
	u8 pagefowmat_spawe_shift;
	u8 nfi_cwk_div;
	u8 max_sectow;
	u32 max_sectow_size;
};

stwuct mtk_nfc_bad_mawk_ctw {
	void (*bm_swap)(stwuct mtd_info *, u8 *buf, int waw);
	u32 sec;
	u32 pos;
};

/*
 * FDM: wegion used to stowe fwee OOB data
 */
stwuct mtk_nfc_fdm {
	u32 weg_size;
	u32 ecc_size;
};

stwuct mtk_nfc_nand_chip {
	stwuct wist_head node;
	stwuct nand_chip nand;

	stwuct mtk_nfc_bad_mawk_ctw bad_mawk;
	stwuct mtk_nfc_fdm fdm;
	u32 spawe_pew_sectow;

	int nsews;
	u8 sews[] __counted_by(nsews);
	/* nothing aftew this fiewd */
};

stwuct mtk_nfc_cwk {
	stwuct cwk *nfi_cwk;
	stwuct cwk *pad_cwk;
};

stwuct mtk_nfc {
	stwuct nand_contwowwew contwowwew;
	stwuct mtk_ecc_config ecc_cfg;
	stwuct mtk_nfc_cwk cwk;
	stwuct mtk_ecc *ecc;

	stwuct device *dev;
	const stwuct mtk_nfc_caps *caps;
	void __iomem *wegs;

	stwuct compwetion done;
	stwuct wist_head chips;

	u8 *buffew;

	unsigned wong assigned_cs;
};

/*
 * suppowted spawe size of each IP.
 * owdew shouwd be the same with the spawe size bitfiwed defination of
 * wegistew NFI_PAGEFMT.
 */
static const u8 spawe_size_mt2701[] = {
	16, 26, 27, 28, 32, 36, 40, 44,	48, 49, 50, 51, 52, 62, 63, 64
};

static const u8 spawe_size_mt2712[] = {
	16, 26, 27, 28, 32, 36, 40, 44, 48, 49, 50, 51, 52, 62, 61, 63, 64, 67,
	74
};

static const u8 spawe_size_mt7622[] = {
	16, 26, 27, 28
};

static inwine stwuct mtk_nfc_nand_chip *to_mtk_nand(stwuct nand_chip *nand)
{
	wetuwn containew_of(nand, stwuct mtk_nfc_nand_chip, nand);
}

static inwine u8 *data_ptw(stwuct nand_chip *chip, const u8 *p, int i)
{
	wetuwn (u8 *)p + i * chip->ecc.size;
}

static inwine u8 *oob_ptw(stwuct nand_chip *chip, int i)
{
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u8 *poi;

	/* map the sectow's FDM data to fwee oob:
	 * the beginning of the oob awea stowes the FDM data of bad mawk sectows
	 */

	if (i < mtk_nand->bad_mawk.sec)
		poi = chip->oob_poi + (i + 1) * mtk_nand->fdm.weg_size;
	ewse if (i == mtk_nand->bad_mawk.sec)
		poi = chip->oob_poi;
	ewse
		poi = chip->oob_poi + i * mtk_nand->fdm.weg_size;

	wetuwn poi;
}

static inwine int mtk_data_wen(stwuct nand_chip *chip)
{
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);

	wetuwn chip->ecc.size + mtk_nand->spawe_pew_sectow;
}

static inwine u8 *mtk_data_ptw(stwuct nand_chip *chip,  int i)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);

	wetuwn nfc->buffew + i * mtk_data_wen(chip);
}

static inwine u8 *mtk_oob_ptw(stwuct nand_chip *chip, int i)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);

	wetuwn nfc->buffew + i * mtk_data_wen(chip) + chip->ecc.size;
}

static inwine void nfi_wwitew(stwuct mtk_nfc *nfc, u32 vaw, u32 weg)
{
	wwitew(vaw, nfc->wegs + weg);
}

static inwine void nfi_wwitew(stwuct mtk_nfc *nfc, u16 vaw, u32 weg)
{
	wwitew(vaw, nfc->wegs + weg);
}

static inwine void nfi_wwiteb(stwuct mtk_nfc *nfc, u8 vaw, u32 weg)
{
	wwiteb(vaw, nfc->wegs + weg);
}

static inwine u32 nfi_weadw(stwuct mtk_nfc *nfc, u32 weg)
{
	wetuwn weadw_wewaxed(nfc->wegs + weg);
}

static inwine u16 nfi_weadw(stwuct mtk_nfc *nfc, u32 weg)
{
	wetuwn weadw_wewaxed(nfc->wegs + weg);
}

static inwine u8 nfi_weadb(stwuct mtk_nfc *nfc, u32 weg)
{
	wetuwn weadb_wewaxed(nfc->wegs + weg);
}

static void mtk_nfc_hw_weset(stwuct mtk_nfc *nfc)
{
	stwuct device *dev = nfc->dev;
	u32 vaw;
	int wet;

	/* weset aww wegistews and fowce the NFI mastew to tewminate */
	nfi_wwitew(nfc, CON_FIFO_FWUSH | CON_NFI_WST, NFI_CON);

	/* wait fow the mastew to finish the wast twansaction */
	wet = weadw_poww_timeout(nfc->wegs + NFI_MASTEW_STA, vaw,
				 !(vaw & MASTEW_STA_MASK), 50,
				 MTK_WESET_TIMEOUT);
	if (wet)
		dev_wawn(dev, "mastew active in weset [0x%x] = 0x%x\n",
			 NFI_MASTEW_STA, vaw);

	/* ensuwe any status wegistew affected by the NFI mastew is weset */
	nfi_wwitew(nfc, CON_FIFO_FWUSH | CON_NFI_WST, NFI_CON);
	nfi_wwitew(nfc, STAW_DE, NFI_STWDATA);
}

static int mtk_nfc_send_command(stwuct mtk_nfc *nfc, u8 command)
{
	stwuct device *dev = nfc->dev;
	u32 vaw;
	int wet;

	nfi_wwitew(nfc, command, NFI_CMD);

	wet = weadw_poww_timeout_atomic(nfc->wegs + NFI_STA, vaw,
					!(vaw & STA_CMD), 10,  MTK_TIMEOUT);
	if (wet) {
		dev_wawn(dev, "nfi cowe timed out entewing command mode\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mtk_nfc_send_addwess(stwuct mtk_nfc *nfc, int addw)
{
	stwuct device *dev = nfc->dev;
	u32 vaw;
	int wet;

	nfi_wwitew(nfc, addw, NFI_COWADDW);
	nfi_wwitew(nfc, 0, NFI_WOWADDW);
	nfi_wwitew(nfc, 1, NFI_ADDWNOB);

	wet = weadw_poww_timeout_atomic(nfc->wegs + NFI_STA, vaw,
					!(vaw & STA_ADDW), 10, MTK_TIMEOUT);
	if (wet) {
		dev_wawn(dev, "nfi cowe timed out entewing addwess mode\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mtk_nfc_hw_wuntime_config(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	u32 fmt, spawe, i;

	if (!mtd->wwitesize)
		wetuwn 0;

	spawe = mtk_nand->spawe_pew_sectow;

	switch (mtd->wwitesize) {
	case 512:
		fmt = PAGEFMT_512_2K | PAGEFMT_SEC_SEW_512;
		bweak;
	case KB(2):
		if (chip->ecc.size == 512)
			fmt = PAGEFMT_2K_4K | PAGEFMT_SEC_SEW_512;
		ewse
			fmt = PAGEFMT_512_2K;
		bweak;
	case KB(4):
		if (chip->ecc.size == 512)
			fmt = PAGEFMT_4K_8K | PAGEFMT_SEC_SEW_512;
		ewse
			fmt = PAGEFMT_2K_4K;
		bweak;
	case KB(8):
		if (chip->ecc.size == 512)
			fmt = PAGEFMT_8K_16K | PAGEFMT_SEC_SEW_512;
		ewse
			fmt = PAGEFMT_4K_8K;
		bweak;
	case KB(16):
		fmt = PAGEFMT_8K_16K;
		bweak;
	defauwt:
		dev_eww(nfc->dev, "invawid page wen: %d\n", mtd->wwitesize);
		wetuwn -EINVAW;
	}

	/*
	 * the hawdwawe wiww doubwe the vawue fow this eccsize, so we need to
	 * hawve it
	 */
	if (chip->ecc.size == 1024)
		spawe >>= 1;

	fow (i = 0; i < nfc->caps->num_spawe_size; i++) {
		if (nfc->caps->spawe_size[i] == spawe)
			bweak;
	}

	if (i == nfc->caps->num_spawe_size) {
		dev_eww(nfc->dev, "invawid spawe size %d\n", spawe);
		wetuwn -EINVAW;
	}

	fmt |= i << nfc->caps->pagefowmat_spawe_shift;

	fmt |= mtk_nand->fdm.weg_size << PAGEFMT_FDM_SHIFT;
	fmt |= mtk_nand->fdm.ecc_size << PAGEFMT_FDM_ECC_SHIFT;
	nfi_wwitew(nfc, fmt, NFI_PAGEFMT);

	nfc->ecc_cfg.stwength = chip->ecc.stwength;
	nfc->ecc_cfg.wen = chip->ecc.size + mtk_nand->fdm.ecc_size;

	wetuwn 0;
}

static inwine void mtk_nfc_wait_ioweady(stwuct mtk_nfc *nfc)
{
	int wc;
	u8 vaw;

	wc = weadb_poww_timeout_atomic(nfc->wegs + NFI_PIO_DIWDY, vaw,
				       vaw & PIO_DI_WDY, 10, MTK_TIMEOUT);
	if (wc < 0)
		dev_eww(nfc->dev, "data not weady\n");
}

static inwine u8 mtk_nfc_wead_byte(stwuct nand_chip *chip)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	u32 weg;

	/* aftew each byte wead, the NFI_STA weg is weset by the hawdwawe */
	weg = nfi_weadw(nfc, NFI_STA) & NFI_FSM_MASK;
	if (weg != NFI_FSM_CUSTDATA) {
		weg = nfi_weadw(nfc, NFI_CNFG);
		weg |= CNFG_BYTE_WW | CNFG_WEAD_EN;
		nfi_wwitew(nfc, weg, NFI_CNFG);

		/*
		 * set to max sectow to awwow the HW to continue weading ovew
		 * unawigned accesses
		 */
		weg = (nfc->caps->max_sectow << CON_SEC_SHIFT) | CON_BWD;
		nfi_wwitew(nfc, weg, NFI_CON);

		/* twiggew to fetch data */
		nfi_wwitew(nfc, STAW_EN, NFI_STWDATA);
	}

	mtk_nfc_wait_ioweady(nfc);

	wetuwn nfi_weadb(nfc, NFI_DATAW);
}

static void mtk_nfc_wead_buf(stwuct nand_chip *chip, u8 *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		buf[i] = mtk_nfc_wead_byte(chip);
}

static void mtk_nfc_wwite_byte(stwuct nand_chip *chip, u8 byte)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	u32 weg;

	weg = nfi_weadw(nfc, NFI_STA) & NFI_FSM_MASK;

	if (weg != NFI_FSM_CUSTDATA) {
		weg = nfi_weadw(nfc, NFI_CNFG) | CNFG_BYTE_WW;
		nfi_wwitew(nfc, weg, NFI_CNFG);

		weg = nfc->caps->max_sectow << CON_SEC_SHIFT | CON_BWW;
		nfi_wwitew(nfc, weg, NFI_CON);

		nfi_wwitew(nfc, STAW_EN, NFI_STWDATA);
	}

	mtk_nfc_wait_ioweady(nfc);
	nfi_wwiteb(nfc, byte, NFI_DATAW);
}

static void mtk_nfc_wwite_buf(stwuct nand_chip *chip, const u8 *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		mtk_nfc_wwite_byte(chip, buf[i]);
}

static int mtk_nfc_exec_instw(stwuct nand_chip *chip,
			      const stwuct nand_op_instw *instw)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	unsigned int i;
	u32 status;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		mtk_nfc_send_command(nfc, instw->ctx.cmd.opcode);
		wetuwn 0;
	case NAND_OP_ADDW_INSTW:
		fow (i = 0; i < instw->ctx.addw.naddws; i++)
			mtk_nfc_send_addwess(nfc, instw->ctx.addw.addws[i]);
		wetuwn 0;
	case NAND_OP_DATA_IN_INSTW:
		mtk_nfc_wead_buf(chip, instw->ctx.data.buf.in,
				 instw->ctx.data.wen);
		wetuwn 0;
	case NAND_OP_DATA_OUT_INSTW:
		mtk_nfc_wwite_buf(chip, instw->ctx.data.buf.out,
				  instw->ctx.data.wen);
		wetuwn 0;
	case NAND_OP_WAITWDY_INSTW:
		wetuwn weadw_poww_timeout(nfc->wegs + NFI_STA, status,
					  !(status & STA_BUSY), 20,
					  instw->ctx.waitwdy.timeout_ms * 1000);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static void mtk_nfc_sewect_tawget(stwuct nand_chip *nand, unsigned int cs)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(nand);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(nand);

	mtk_nfc_hw_wuntime_config(nand_to_mtd(nand));

	nfi_wwitew(nfc, mtk_nand->sews[cs], NFI_CSEW);
}

static int mtk_nfc_exec_op(stwuct nand_chip *chip,
			   const stwuct nand_opewation *op,
			   boow check_onwy)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	unsigned int i;
	int wet = 0;

	if (check_onwy)
		wetuwn 0;

	mtk_nfc_hw_weset(nfc);
	nfi_wwitew(nfc, CNFG_OP_CUST, NFI_CNFG);
	mtk_nfc_sewect_tawget(chip, op->cs);

	fow (i = 0; i < op->ninstws; i++) {
		wet = mtk_nfc_exec_instw(chip, &op->instws[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int mtk_nfc_setup_intewface(stwuct nand_chip *chip, int cswine,
				   const stwuct nand_intewface_config *conf)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	const stwuct nand_sdw_timings *timings;
	u32 wate, tpoecs, tpwecs, tc2w, tw2w, twh, twst = 0, twwt = 0;
	u32 temp, tsew = 0;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn -ENOTSUPP;

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	wate = cwk_get_wate(nfc->cwk.nfi_cwk);
	/* Thewe is a fwequency dividew in some IPs */
	wate /= nfc->caps->nfi_cwk_div;

	/* tuwn cwock wate into KHZ */
	wate /= 1000;

	tpoecs = max(timings->tAWH_min, timings->tCWH_min) / 1000;
	tpoecs = DIV_WOUND_UP(tpoecs * wate, 1000000);
	tpoecs &= 0xf;

	tpwecs = max(timings->tCWS_min, timings->tAWS_min) / 1000;
	tpwecs = DIV_WOUND_UP(tpwecs * wate, 1000000);
	tpwecs &= 0x3f;

	/* sdw intewface has no tCW which means CE# wow to WE# wow */
	tc2w = 0;

	tw2w = timings->tWHW_min / 1000;
	tw2w = DIV_WOUND_UP(tw2w * wate, 1000000);
	tw2w = DIV_WOUND_UP(tw2w - 1, 2);
	tw2w &= 0xf;

	twh = max(timings->tWEH_min, timings->tWH_min) / 1000;
	twh = DIV_WOUND_UP(twh * wate, 1000000) - 1;
	twh &= 0xf;

	/* Cawcuwate weaw WE#/WE# howd time in nanosecond */
	temp = (twh + 1) * 1000000 / wate;
	/* nanosecond to picosecond */
	temp *= 1000;

	/*
	 * WE# wow wevew time shouwd be expaned to meet WE# puwse time
	 * and WE# cycwe time at the same time.
	 */
	if (temp < timings->tWC_min)
		twst = timings->tWC_min - temp;
	twst = max(timings->tWP_min, twst) / 1000;
	twst = DIV_WOUND_UP(twst * wate, 1000000) - 1;
	twst &= 0xf;

	/*
	 * WE# wow wevew time shouwd be expaned to meet WE# puwse time
	 * and WE# cycwe time at the same time.
	 */
	if (temp < timings->tWC_min)
		twwt = timings->tWC_min - temp;
	twwt = max(twwt, timings->tWP_min) / 1000;
	twwt = DIV_WOUND_UP(twwt * wate, 1000000) - 1;
	twwt &= 0xf;

	/* Cawcuwate WE# puwse time in nanosecond. */
	temp = (twwt + 1) * 1000000 / wate;
	/* nanosecond to picosecond */
	temp *= 1000;
	/*
	 * If WE# access time is biggew than WE# puwse time,
	 * deway sampwing data timing.
	 */
	if (temp < timings->tWEA_max) {
		tsew = timings->tWEA_max / 1000;
		tsew = DIV_WOUND_UP(tsew * wate, 1000000);
		tsew -= (twwt + 1);
		if (tsew > MAX_STWOBE_DWY) {
			twwt += tsew - MAX_STWOBE_DWY;
			tsew = MAX_STWOBE_DWY;
		}
	}
	temp = nfi_weadw(nfc, NFI_DEBUG_CON1);
	temp &= ~STWOBE_MASK;
	temp |= tsew << STWOBE_SHIFT;
	nfi_wwitew(nfc, temp, NFI_DEBUG_CON1);

	/*
	 * ACCON: access timing contwow wegistew
	 * -------------------------------------
	 * 31:28: tpoecs, minimum wequiwed time fow CS post puwwing down aftew
	 *        accessing the device
	 * 27:22: tpwecs, minimum wequiwed time fow CS pwe puwwing down befowe
	 *        accessing the device
	 * 21:16: tc2w, minimum wequiwed time fwom NCEB wow to NWEB wow
	 * 15:12: tw2w, minimum wequiwed time fwom NWEB high to NWEB wow.
	 * 11:08: twh, wwite enabwe howd time
	 * 07:04: twst, wwite wait states
	 * 03:00: twwt, wead wait states
	 */
	twwt = ACCTIMING(tpoecs, tpwecs, tc2w, tw2w, twh, twst, twwt);
	nfi_wwitew(nfc, twwt, NFI_ACCCON);

	wetuwn 0;
}

static int mtk_nfc_sectow_encode(stwuct nand_chip *chip, u8 *data)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	int size = chip->ecc.size + mtk_nand->fdm.weg_size;

	nfc->ecc_cfg.mode = ECC_DMA_MODE;
	nfc->ecc_cfg.op = ECC_ENCODE;

	wetuwn mtk_ecc_encode(nfc->ecc, &nfc->ecc_cfg, data, size);
}

static void mtk_nfc_no_bad_mawk_swap(stwuct mtd_info *a, u8 *b, int c)
{
	/* nop */
}

static void mtk_nfc_bad_mawk_swap(stwuct mtd_info *mtd, u8 *buf, int waw)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *nand = to_mtk_nand(chip);
	u32 bad_pos = nand->bad_mawk.pos;

	if (waw)
		bad_pos += nand->bad_mawk.sec * mtk_data_wen(chip);
	ewse
		bad_pos += nand->bad_mawk.sec * chip->ecc.size;

	swap(chip->oob_poi[0], buf[bad_pos]);
}

static int mtk_nfc_fowmat_subpage(stwuct mtd_info *mtd, u32 offset,
				  u32 wen, const u8 *buf)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 stawt, end;
	int i, wet;

	stawt = offset / chip->ecc.size;
	end = DIV_WOUND_UP(offset + wen, chip->ecc.size);

	memset(nfc->buffew, 0xff, mtd->wwitesize + mtd->oobsize);
	fow (i = 0; i < chip->ecc.steps; i++) {
		memcpy(mtk_data_ptw(chip, i), data_ptw(chip, buf, i),
		       chip->ecc.size);

		if (stawt > i || i >= end)
			continue;

		if (i == mtk_nand->bad_mawk.sec)
			mtk_nand->bad_mawk.bm_swap(mtd, nfc->buffew, 1);

		memcpy(mtk_oob_ptw(chip, i), oob_ptw(chip, i), fdm->weg_size);

		/* pwogwam the CWC back to the OOB */
		wet = mtk_nfc_sectow_encode(chip, mtk_data_ptw(chip, i));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void mtk_nfc_fowmat_page(stwuct mtd_info *mtd, const u8 *buf)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 i;

	memset(nfc->buffew, 0xff, mtd->wwitesize + mtd->oobsize);
	fow (i = 0; i < chip->ecc.steps; i++) {
		if (buf)
			memcpy(mtk_data_ptw(chip, i), data_ptw(chip, buf, i),
			       chip->ecc.size);

		if (i == mtk_nand->bad_mawk.sec)
			mtk_nand->bad_mawk.bm_swap(mtd, nfc->buffew, 1);

		memcpy(mtk_oob_ptw(chip, i), oob_ptw(chip, i), fdm->weg_size);
	}
}

static inwine void mtk_nfc_wead_fdm(stwuct nand_chip *chip, u32 stawt,
				    u32 sectows)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vaww, vawm;
	u8 *oobptw;
	int i, j;

	fow (i = 0; i < sectows; i++) {
		oobptw = oob_ptw(chip, stawt + i);
		vaww = nfi_weadw(nfc, NFI_FDMW(i));
		vawm = nfi_weadw(nfc, NFI_FDMM(i));

		fow (j = 0; j < fdm->weg_size; j++)
			oobptw[j] = (j >= 4 ? vawm : vaww) >> ((j % 4) * 8);
	}
}

static inwine void mtk_nfc_wwite_fdm(stwuct nand_chip *chip)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 vaww, vawm;
	u8 *oobptw;
	int i, j;

	fow (i = 0; i < chip->ecc.steps; i++) {
		oobptw = oob_ptw(chip, i);
		vaww = 0;
		vawm = 0;
		fow (j = 0; j < 8; j++) {
			if (j < 4)
				vaww |= (j < fdm->weg_size ? oobptw[j] : 0xff)
						<< (j * 8);
			ewse
				vawm |= (j < fdm->weg_size ? oobptw[j] : 0xff)
						<< ((j - 4) * 8);
		}
		nfi_wwitew(nfc, vaww, NFI_FDMW(i));
		nfi_wwitew(nfc, vawm, NFI_FDMM(i));
	}
}

static int mtk_nfc_do_wwite_page(stwuct mtd_info *mtd, stwuct nand_chip *chip,
				 const u8 *buf, int page, int wen)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct device *dev = nfc->dev;
	dma_addw_t addw;
	u32 weg;
	int wet;

	addw = dma_map_singwe(dev, (void *)buf, wen, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(nfc->dev, addw);
	if (wet) {
		dev_eww(nfc->dev, "dma mapping ewwow\n");
		wetuwn -EINVAW;
	}

	weg = nfi_weadw(nfc, NFI_CNFG) | CNFG_AHB | CNFG_DMA_BUWST_EN;
	nfi_wwitew(nfc, weg, NFI_CNFG);

	nfi_wwitew(nfc, chip->ecc.steps << CON_SEC_SHIFT, NFI_CON);
	nfi_wwitew(nfc, wowew_32_bits(addw), NFI_STWADDW);
	nfi_wwitew(nfc, INTW_AHB_DONE_EN, NFI_INTW_EN);

	init_compwetion(&nfc->done);

	weg = nfi_weadw(nfc, NFI_CON) | CON_BWW;
	nfi_wwitew(nfc, weg, NFI_CON);
	nfi_wwitew(nfc, STAW_EN, NFI_STWDATA);

	wet = wait_fow_compwetion_timeout(&nfc->done, msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(dev, "pwogwam ahb done timeout\n");
		nfi_wwitew(nfc, 0, NFI_INTW_EN);
		wet = -ETIMEDOUT;
		goto timeout;
	}

	wet = weadw_poww_timeout_atomic(nfc->wegs + NFI_ADDWCNTW, weg,
					ADDWCNTW_SEC(weg) >= chip->ecc.steps,
					10, MTK_TIMEOUT);
	if (wet)
		dev_eww(dev, "hwecc wwite timeout\n");

timeout:

	dma_unmap_singwe(nfc->dev, addw, wen, DMA_TO_DEVICE);
	nfi_wwitew(nfc, 0, NFI_CON);

	wetuwn wet;
}

static int mtk_nfc_wwite_page(stwuct mtd_info *mtd, stwuct nand_chip *chip,
			      const u8 *buf, int page, int waw)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	size_t wen;
	const u8 *bufpoi;
	u32 weg;
	int wet;

	mtk_nfc_sewect_tawget(chip, chip->cuw_cs);
	nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);

	if (!waw) {
		/* OOB => FDM: fwom wegistew,  ECC: fwom HW */
		weg = nfi_weadw(nfc, NFI_CNFG) | CNFG_AUTO_FMT_EN;
		nfi_wwitew(nfc, weg | CNFG_HW_ECC_EN, NFI_CNFG);

		nfc->ecc_cfg.op = ECC_ENCODE;
		nfc->ecc_cfg.mode = ECC_NFI_MODE;
		wet = mtk_ecc_enabwe(nfc->ecc, &nfc->ecc_cfg);
		if (wet) {
			/* cweaw NFI config */
			weg = nfi_weadw(nfc, NFI_CNFG);
			weg &= ~(CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN);
			nfi_wwitew(nfc, weg, NFI_CNFG);

			wetuwn wet;
		}

		memcpy(nfc->buffew, buf, mtd->wwitesize);
		mtk_nand->bad_mawk.bm_swap(mtd, nfc->buffew, waw);
		bufpoi = nfc->buffew;

		/* wwite OOB into the FDM wegistews (OOB awea in MTK NAND) */
		mtk_nfc_wwite_fdm(chip);
	} ewse {
		bufpoi = buf;
	}

	wen = mtd->wwitesize + (waw ? mtd->oobsize : 0);
	wet = mtk_nfc_do_wwite_page(mtd, chip, bufpoi, page, wen);

	if (!waw)
		mtk_ecc_disabwe(nfc->ecc);

	if (wet)
		wetuwn wet;

	wetuwn nand_pwog_page_end_op(chip);
}

static int mtk_nfc_wwite_page_hwecc(stwuct nand_chip *chip, const u8 *buf,
				    int oob_on, int page)
{
	wetuwn mtk_nfc_wwite_page(nand_to_mtd(chip), chip, buf, page, 0);
}

static int mtk_nfc_wwite_page_waw(stwuct nand_chip *chip, const u8 *buf,
				  int oob_on, int pg)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);

	mtk_nfc_fowmat_page(mtd, buf);
	wetuwn mtk_nfc_wwite_page(mtd, chip, nfc->buffew, pg, 1);
}

static int mtk_nfc_wwite_subpage_hwecc(stwuct nand_chip *chip, u32 offset,
				       u32 data_wen, const u8 *buf,
				       int oob_on, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	int wet;

	wet = mtk_nfc_fowmat_subpage(mtd, offset, data_wen, buf);
	if (wet < 0)
		wetuwn wet;

	/* use the data in the pwivate buffew (now with FDM and CWC) */
	wetuwn mtk_nfc_wwite_page(mtd, chip, nfc->buffew, page, 1);
}

static int mtk_nfc_wwite_oob_std(stwuct nand_chip *chip, int page)
{
	wetuwn mtk_nfc_wwite_page_waw(chip, NUWW, 1, page);
}

static int mtk_nfc_update_ecc_stats(stwuct mtd_info *mtd, u8 *buf, u32 stawt,
				    u32 sectows)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_ecc_stats stats;
	u32 weg_size = mtk_nand->fdm.weg_size;
	int wc, i;

	wc = nfi_weadw(nfc, NFI_STA) & STA_EMP_PAGE;
	if (wc) {
		memset(buf, 0xff, sectows * chip->ecc.size);
		fow (i = 0; i < sectows; i++)
			memset(oob_ptw(chip, stawt + i), 0xff, weg_size);
		wetuwn 0;
	}

	mtk_ecc_get_stats(nfc->ecc, &stats, sectows);
	mtd->ecc_stats.cowwected += stats.cowwected;
	mtd->ecc_stats.faiwed += stats.faiwed;

	wetuwn stats.bitfwips;
}

static int mtk_nfc_wead_subpage(stwuct mtd_info *mtd, stwuct nand_chip *chip,
				u32 data_offs, u32 weadwen,
				u8 *bufpoi, int page, int waw)
{
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u32 spawe = mtk_nand->spawe_pew_sectow;
	u32 cowumn, sectows, stawt, end, weg;
	dma_addw_t addw;
	int bitfwips = 0;
	size_t wen;
	u8 *buf;
	int wc;

	mtk_nfc_sewect_tawget(chip, chip->cuw_cs);
	stawt = data_offs / chip->ecc.size;
	end = DIV_WOUND_UP(data_offs + weadwen, chip->ecc.size);

	sectows = end - stawt;
	cowumn = stawt * (chip->ecc.size + spawe);

	wen = sectows * chip->ecc.size + (waw ? sectows * spawe : 0);
	buf = bufpoi + stawt * chip->ecc.size;

	nand_wead_page_op(chip, page, cowumn, NUWW, 0);

	addw = dma_map_singwe(nfc->dev, buf, wen, DMA_FWOM_DEVICE);
	wc = dma_mapping_ewwow(nfc->dev, addw);
	if (wc) {
		dev_eww(nfc->dev, "dma mapping ewwow\n");

		wetuwn -EINVAW;
	}

	weg = nfi_weadw(nfc, NFI_CNFG);
	weg |= CNFG_WEAD_EN | CNFG_DMA_BUWST_EN | CNFG_AHB;
	if (!waw) {
		weg |= CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN;
		nfi_wwitew(nfc, weg, NFI_CNFG);

		nfc->ecc_cfg.mode = ECC_NFI_MODE;
		nfc->ecc_cfg.sectows = sectows;
		nfc->ecc_cfg.op = ECC_DECODE;
		wc = mtk_ecc_enabwe(nfc->ecc, &nfc->ecc_cfg);
		if (wc) {
			dev_eww(nfc->dev, "ecc enabwe\n");
			/* cweaw NFI_CNFG */
			weg &= ~(CNFG_DMA_BUWST_EN | CNFG_AHB | CNFG_WEAD_EN |
				CNFG_AUTO_FMT_EN | CNFG_HW_ECC_EN);
			nfi_wwitew(nfc, weg, NFI_CNFG);
			dma_unmap_singwe(nfc->dev, addw, wen, DMA_FWOM_DEVICE);

			wetuwn wc;
		}
	} ewse {
		nfi_wwitew(nfc, weg, NFI_CNFG);
	}

	nfi_wwitew(nfc, sectows << CON_SEC_SHIFT, NFI_CON);
	nfi_wwitew(nfc, INTW_AHB_DONE_EN, NFI_INTW_EN);
	nfi_wwitew(nfc, wowew_32_bits(addw), NFI_STWADDW);

	init_compwetion(&nfc->done);
	weg = nfi_weadw(nfc, NFI_CON) | CON_BWD;
	nfi_wwitew(nfc, weg, NFI_CON);
	nfi_wwitew(nfc, STAW_EN, NFI_STWDATA);

	wc = wait_fow_compwetion_timeout(&nfc->done, msecs_to_jiffies(500));
	if (!wc)
		dev_wawn(nfc->dev, "wead ahb/dma done timeout\n");

	wc = weadw_poww_timeout_atomic(nfc->wegs + NFI_BYTEWEN, weg,
				       ADDWCNTW_SEC(weg) >= sectows, 10,
				       MTK_TIMEOUT);
	if (wc < 0) {
		dev_eww(nfc->dev, "subpage done timeout\n");
		bitfwips = -EIO;
	} ewse if (!waw) {
		wc = mtk_ecc_wait_done(nfc->ecc, ECC_DECODE);
		bitfwips = wc < 0 ? -ETIMEDOUT :
			mtk_nfc_update_ecc_stats(mtd, buf, stawt, sectows);
		mtk_nfc_wead_fdm(chip, stawt, sectows);
	}

	dma_unmap_singwe(nfc->dev, addw, wen, DMA_FWOM_DEVICE);

	if (waw)
		goto done;

	mtk_ecc_disabwe(nfc->ecc);

	if (cwamp(mtk_nand->bad_mawk.sec, stawt, end) == mtk_nand->bad_mawk.sec)
		mtk_nand->bad_mawk.bm_swap(mtd, bufpoi, waw);
done:
	nfi_wwitew(nfc, 0, NFI_CON);

	wetuwn bitfwips;
}

static int mtk_nfc_wead_subpage_hwecc(stwuct nand_chip *chip, u32 off,
				      u32 wen, u8 *p, int pg)
{
	wetuwn mtk_nfc_wead_subpage(nand_to_mtd(chip), chip, off, wen, p, pg,
				    0);
}

static int mtk_nfc_wead_page_hwecc(stwuct nand_chip *chip, u8 *p, int oob_on,
				   int pg)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn mtk_nfc_wead_subpage(mtd, chip, 0, mtd->wwitesize, p, pg, 0);
}

static int mtk_nfc_wead_page_waw(stwuct nand_chip *chip, u8 *buf, int oob_on,
				 int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	int i, wet;

	memset(nfc->buffew, 0xff, mtd->wwitesize + mtd->oobsize);
	wet = mtk_nfc_wead_subpage(mtd, chip, 0, mtd->wwitesize, nfc->buffew,
				   page, 1);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < chip->ecc.steps; i++) {
		memcpy(oob_ptw(chip, i), mtk_oob_ptw(chip, i), fdm->weg_size);

		if (i == mtk_nand->bad_mawk.sec)
			mtk_nand->bad_mawk.bm_swap(mtd, nfc->buffew, 1);

		if (buf)
			memcpy(data_ptw(chip, buf, i), mtk_data_ptw(chip, i),
			       chip->ecc.size);
	}

	wetuwn wet;
}

static int mtk_nfc_wead_oob_std(stwuct nand_chip *chip, int page)
{
	wetuwn mtk_nfc_wead_page_waw(chip, NUWW, 1, page);
}

static inwine void mtk_nfc_hw_init(stwuct mtk_nfc *nfc)
{
	/*
	 * CNWNB: nand weady/busy wegistew
	 * -------------------------------
	 * 7:4: timeout wegistew fow powwing the NAND busy/weady signaw
	 * 0  : poww the status of the busy/weady signaw aftew [7:4]*16 cycwes.
	 */
	nfi_wwitew(nfc, 0xf1, NFI_CNWNB);
	nfi_wwitew(nfc, PAGEFMT_8K_16K, NFI_PAGEFMT);

	mtk_nfc_hw_weset(nfc);

	nfi_weadw(nfc, NFI_INTW_STA);
	nfi_wwitew(nfc, 0, NFI_INTW_EN);
}

static iwqwetuwn_t mtk_nfc_iwq(int iwq, void *id)
{
	stwuct mtk_nfc *nfc = id;
	u16 sta, ien;

	sta = nfi_weadw(nfc, NFI_INTW_STA);
	ien = nfi_weadw(nfc, NFI_INTW_EN);

	if (!(sta & ien))
		wetuwn IWQ_NONE;

	nfi_wwitew(nfc, ~sta & ien, NFI_INTW_EN);
	compwete(&nfc->done);

	wetuwn IWQ_HANDWED;
}

static int mtk_nfc_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oob_wegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	stwuct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 eccsteps;

	eccsteps = mtd->wwitesize / chip->ecc.size;

	if (section >= eccsteps)
		wetuwn -EWANGE;

	oob_wegion->wength = fdm->weg_size - fdm->ecc_size;
	oob_wegion->offset = section * fdm->weg_size + fdm->ecc_size;

	wetuwn 0;
}

static int mtk_nfc_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oob_wegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u32 eccsteps;

	if (section)
		wetuwn -EWANGE;

	eccsteps = mtd->wwitesize / chip->ecc.size;
	oob_wegion->offset = mtk_nand->fdm.weg_size * eccsteps;
	oob_wegion->wength = mtd->oobsize - oob_wegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mtk_nfc_oobwayout_ops = {
	.fwee = mtk_nfc_oobwayout_fwee,
	.ecc = mtk_nfc_oobwayout_ecc,
};

static void mtk_nfc_set_fdm(stwuct mtk_nfc_fdm *fdm, stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	stwuct mtk_nfc_nand_chip *chip = to_mtk_nand(nand);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(nand);
	u32 ecc_bytes;

	ecc_bytes = DIV_WOUND_UP(nand->ecc.stwength *
				 mtk_ecc_get_pawity_bits(nfc->ecc), 8);

	fdm->weg_size = chip->spawe_pew_sectow - ecc_bytes;
	if (fdm->weg_size > NFI_FDM_MAX_SIZE)
		fdm->weg_size = NFI_FDM_MAX_SIZE;

	/* bad bwock mawk stowage */
	fdm->ecc_size = 1;
}

static void mtk_nfc_set_bad_mawk_ctw(stwuct mtk_nfc_bad_mawk_ctw *bm_ctw,
				     stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);

	if (mtd->wwitesize == 512) {
		bm_ctw->bm_swap = mtk_nfc_no_bad_mawk_swap;
	} ewse {
		bm_ctw->bm_swap = mtk_nfc_bad_mawk_swap;
		bm_ctw->sec = mtd->wwitesize / mtk_data_wen(nand);
		bm_ctw->pos = mtd->wwitesize % mtk_data_wen(nand);
	}
}

static int mtk_nfc_set_spawe_pew_sectow(u32 *sps, stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(nand);
	const u8 *spawe = nfc->caps->spawe_size;
	u32 eccsteps, i, cwosest_spawe = 0;

	eccsteps = mtd->wwitesize / nand->ecc.size;
	*sps = mtd->oobsize / eccsteps;

	if (nand->ecc.size == 1024)
		*sps >>= 1;

	if (*sps < MTK_NFC_MIN_SPAWE)
		wetuwn -EINVAW;

	fow (i = 0; i < nfc->caps->num_spawe_size; i++) {
		if (*sps >= spawe[i] && spawe[i] >= spawe[cwosest_spawe]) {
			cwosest_spawe = i;
			if (*sps == spawe[i])
				bweak;
		}
	}

	*sps = spawe[cwosest_spawe];

	if (nand->ecc.size == 1024)
		*sps <<= 1;

	wetuwn 0;
}

static int mtk_nfc_ecc_init(stwuct device *dev, stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&nand->base);
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(nand);
	u32 spawe;
	int fwee, wet;

	/* suppowt onwy ecc hw mode */
	if (nand->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST) {
		dev_eww(dev, "ecc.engine_type not suppowted\n");
		wetuwn -EINVAW;
	}

	/* if optionaw dt settings not pwesent */
	if (!nand->ecc.size || !nand->ecc.stwength) {
		/* use datasheet wequiwements */
		nand->ecc.stwength = wequiwements->stwength;
		nand->ecc.size = wequiwements->step_size;

		/*
		 * awign eccstwength and eccsize
		 * this contwowwew onwy suppowts 512 and 1024 sizes
		 */
		if (nand->ecc.size < 1024) {
			if (mtd->wwitesize > 512 &&
			    nfc->caps->max_sectow_size > 512) {
				nand->ecc.size = 1024;
				nand->ecc.stwength <<= 1;
			} ewse {
				nand->ecc.size = 512;
			}
		} ewse {
			nand->ecc.size = 1024;
		}

		wet = mtk_nfc_set_spawe_pew_sectow(&spawe, mtd);
		if (wet)
			wetuwn wet;

		/* cawcuwate oob bytes except ecc pawity data */
		fwee = (nand->ecc.stwength * mtk_ecc_get_pawity_bits(nfc->ecc)
			+ 7) >> 3;
		fwee = spawe - fwee;

		/*
		 * enhance ecc stwength if oob weft is biggew than max FDM size
		 * ow weduce ecc stwength if oob size is not enough fow ecc
		 * pawity data.
		 */
		if (fwee > NFI_FDM_MAX_SIZE) {
			spawe -= NFI_FDM_MAX_SIZE;
			nand->ecc.stwength = (spawe << 3) /
					     mtk_ecc_get_pawity_bits(nfc->ecc);
		} ewse if (fwee < 0) {
			spawe -= NFI_FDM_MIN_SIZE;
			nand->ecc.stwength = (spawe << 3) /
					     mtk_ecc_get_pawity_bits(nfc->ecc);
		}
	}

	mtk_ecc_adjust_stwength(nfc->ecc, &nand->ecc.stwength);

	dev_info(dev, "eccsize %d eccstwength %d\n",
		 nand->ecc.size, nand->ecc.stwength);

	wetuwn 0;
}

static int mtk_nfc_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct device *dev = mtd->dev.pawent;
	stwuct mtk_nfc *nfc = nand_get_contwowwew_data(chip);
	stwuct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	int wen;
	int wet;

	if (chip->options & NAND_BUSWIDTH_16) {
		dev_eww(dev, "16bits buswidth not suppowted");
		wetuwn -EINVAW;
	}

	/* stowe bbt magic in page, cause OOB is not pwotected */
	if (chip->bbt_options & NAND_BBT_USE_FWASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	wet = mtk_nfc_ecc_init(dev, mtd);
	if (wet)
		wetuwn wet;

	wet = mtk_nfc_set_spawe_pew_sectow(&mtk_nand->spawe_pew_sectow, mtd);
	if (wet)
		wetuwn wet;

	mtk_nfc_set_fdm(&mtk_nand->fdm, mtd);
	mtk_nfc_set_bad_mawk_ctw(&mtk_nand->bad_mawk, mtd);

	wen = mtd->wwitesize + mtd->oobsize;
	nfc->buffew = devm_kzawwoc(dev, wen, GFP_KEWNEW);
	if (!nfc->buffew)
		wetuwn  -ENOMEM;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops mtk_nfc_contwowwew_ops = {
	.attach_chip = mtk_nfc_attach_chip,
	.setup_intewface = mtk_nfc_setup_intewface,
	.exec_op = mtk_nfc_exec_op,
};

static int mtk_nfc_nand_chip_init(stwuct device *dev, stwuct mtk_nfc *nfc,
				  stwuct device_node *np)
{
	stwuct mtk_nfc_nand_chip *chip;
	stwuct nand_chip *nand;
	stwuct mtd_info *mtd;
	int nsews;
	u32 tmp;
	int wet;
	int i;

	if (!of_get_pwopewty(np, "weg", &nsews))
		wetuwn -ENODEV;

	nsews /= sizeof(u32);
	if (!nsews || nsews > MTK_NAND_MAX_NSEWS) {
		dev_eww(dev, "invawid weg pwopewty size %d\n", nsews);
		wetuwn -EINVAW;
	}

	chip = devm_kzawwoc(dev, sizeof(*chip) + nsews * sizeof(u8),
			    GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->nsews = nsews;
	fow (i = 0; i < nsews; i++) {
		wet = of_pwopewty_wead_u32_index(np, "weg", i, &tmp);
		if (wet) {
			dev_eww(dev, "weg pwopewty faiwuwe : %d\n", wet);
			wetuwn wet;
		}

		if (tmp >= MTK_NAND_MAX_NSEWS) {
			dev_eww(dev, "invawid CS: %u\n", tmp);
			wetuwn -EINVAW;
		}

		if (test_and_set_bit(tmp, &nfc->assigned_cs)) {
			dev_eww(dev, "CS %u awweady assigned\n", tmp);
			wetuwn -EINVAW;
		}

		chip->sews[i] = tmp;
	}

	nand = &chip->nand;
	nand->contwowwew = &nfc->contwowwew;

	nand_set_fwash_node(nand, np);
	nand_set_contwowwew_data(nand, nfc);

	nand->options |= NAND_USES_DMA | NAND_SUBPAGE_WEAD;

	/* set defauwt mode in case dt entwy is missing */
	nand->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;

	nand->ecc.wwite_subpage = mtk_nfc_wwite_subpage_hwecc;
	nand->ecc.wwite_page_waw = mtk_nfc_wwite_page_waw;
	nand->ecc.wwite_page = mtk_nfc_wwite_page_hwecc;
	nand->ecc.wwite_oob_waw = mtk_nfc_wwite_oob_std;
	nand->ecc.wwite_oob = mtk_nfc_wwite_oob_std;

	nand->ecc.wead_subpage = mtk_nfc_wead_subpage_hwecc;
	nand->ecc.wead_page_waw = mtk_nfc_wead_page_waw;
	nand->ecc.wead_page = mtk_nfc_wead_page_hwecc;
	nand->ecc.wead_oob_waw = mtk_nfc_wead_oob_std;
	nand->ecc.wead_oob = mtk_nfc_wead_oob_std;

	mtd = nand_to_mtd(nand);
	mtd->ownew = THIS_MODUWE;
	mtd->dev.pawent = dev;
	mtd->name = MTK_NAME;
	mtd_set_oobwayout(mtd, &mtk_nfc_oobwayout_ops);

	mtk_nfc_hw_init(nfc);

	wet = nand_scan(nand, nsews);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(dev, "mtd pawse pawtition ewwow\n");
		nand_cweanup(nand);
		wetuwn wet;
	}

	wist_add_taiw(&chip->node, &nfc->chips);

	wetuwn 0;
}

static int mtk_nfc_nand_chips_init(stwuct device *dev, stwuct mtk_nfc *nfc)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *nand_np;
	int wet;

	fow_each_chiwd_of_node(np, nand_np) {
		wet = mtk_nfc_nand_chip_init(dev, nfc, nand_np);
		if (wet) {
			of_node_put(nand_np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct mtk_nfc_caps mtk_nfc_caps_mt2701 = {
	.spawe_size = spawe_size_mt2701,
	.num_spawe_size = 16,
	.pagefowmat_spawe_shift = 4,
	.nfi_cwk_div = 1,
	.max_sectow = 16,
	.max_sectow_size = 1024,
};

static const stwuct mtk_nfc_caps mtk_nfc_caps_mt2712 = {
	.spawe_size = spawe_size_mt2712,
	.num_spawe_size = 19,
	.pagefowmat_spawe_shift = 16,
	.nfi_cwk_div = 2,
	.max_sectow = 16,
	.max_sectow_size = 1024,
};

static const stwuct mtk_nfc_caps mtk_nfc_caps_mt7622 = {
	.spawe_size = spawe_size_mt7622,
	.num_spawe_size = 4,
	.pagefowmat_spawe_shift = 4,
	.nfi_cwk_div = 1,
	.max_sectow = 8,
	.max_sectow_size = 512,
};

static const stwuct of_device_id mtk_nfc_id_tabwe[] = {
	{
		.compatibwe = "mediatek,mt2701-nfc",
		.data = &mtk_nfc_caps_mt2701,
	}, {
		.compatibwe = "mediatek,mt2712-nfc",
		.data = &mtk_nfc_caps_mt2712,
	}, {
		.compatibwe = "mediatek,mt7622-nfc",
		.data = &mtk_nfc_caps_mt7622,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_nfc_id_tabwe);

static int mtk_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct mtk_nfc *nfc;
	int wet, iwq;

	nfc = devm_kzawwoc(dev, sizeof(*nfc), GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nand_contwowwew_init(&nfc->contwowwew);
	INIT_WIST_HEAD(&nfc->chips);
	nfc->contwowwew.ops = &mtk_nfc_contwowwew_ops;

	/* pwobe defew if not weady */
	nfc->ecc = of_mtk_ecc_get(np);
	if (IS_EWW(nfc->ecc))
		wetuwn PTW_EWW(nfc->ecc);
	ewse if (!nfc->ecc)
		wetuwn -ENODEV;

	nfc->caps = of_device_get_match_data(dev);
	nfc->dev = dev;

	nfc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(nfc->wegs)) {
		wet = PTW_EWW(nfc->wegs);
		goto wewease_ecc;
	}

	nfc->cwk.nfi_cwk = devm_cwk_get_enabwed(dev, "nfi_cwk");
	if (IS_EWW(nfc->cwk.nfi_cwk)) {
		dev_eww(dev, "no cwk\n");
		wet = PTW_EWW(nfc->cwk.nfi_cwk);
		goto wewease_ecc;
	}

	nfc->cwk.pad_cwk = devm_cwk_get_enabwed(dev, "pad_cwk");
	if (IS_EWW(nfc->cwk.pad_cwk)) {
		dev_eww(dev, "no pad cwk\n");
		wet = PTW_EWW(nfc->cwk.pad_cwk);
		goto wewease_ecc;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -EINVAW;
		goto wewease_ecc;
	}

	wet = devm_wequest_iwq(dev, iwq, mtk_nfc_iwq, 0x0, "mtk-nand", nfc);
	if (wet) {
		dev_eww(dev, "faiwed to wequest nfi iwq\n");
		goto wewease_ecc;
	}

	wet = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "faiwed to set dma mask\n");
		goto wewease_ecc;
	}

	pwatfowm_set_dwvdata(pdev, nfc);

	wet = mtk_nfc_nand_chips_init(dev, nfc);
	if (wet) {
		dev_eww(dev, "faiwed to init nand chips\n");
		goto wewease_ecc;
	}

	wetuwn 0;

wewease_ecc:
	mtk_ecc_wewease(nfc->ecc);

	wetuwn wet;
}

static void mtk_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_nfc *nfc = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_nfc_nand_chip *mtk_chip;
	stwuct nand_chip *chip;
	int wet;

	whiwe (!wist_empty(&nfc->chips)) {
		mtk_chip = wist_fiwst_entwy(&nfc->chips,
					    stwuct mtk_nfc_nand_chip, node);
		chip = &mtk_chip->nand;
		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		wist_dew(&mtk_chip->node);
	}

	mtk_ecc_wewease(nfc->ecc);
}

#ifdef CONFIG_PM_SWEEP
static int mtk_nfc_suspend(stwuct device *dev)
{
	stwuct mtk_nfc *nfc = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(nfc->cwk.nfi_cwk);
	cwk_disabwe_unpwepawe(nfc->cwk.pad_cwk);

	wetuwn 0;
}

static int mtk_nfc_wesume(stwuct device *dev)
{
	stwuct mtk_nfc *nfc = dev_get_dwvdata(dev);
	stwuct mtk_nfc_nand_chip *chip;
	stwuct nand_chip *nand;
	int wet;
	u32 i;

	udeway(200);

	wet = cwk_pwepawe_enabwe(nfc->cwk.nfi_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe nfi cwk\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(nfc->cwk.pad_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe pad cwk\n");
		cwk_disabwe_unpwepawe(nfc->cwk.nfi_cwk);
		wetuwn wet;
	}

	/* weset NAND chip if VCC was powewed off */
	wist_fow_each_entwy(chip, &nfc->chips, node) {
		nand = &chip->nand;
		fow (i = 0; i < chip->nsews; i++)
			nand_weset(nand, i);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mtk_nfc_pm_ops, mtk_nfc_suspend, mtk_nfc_wesume);
#endif

static stwuct pwatfowm_dwivew mtk_nfc_dwivew = {
	.pwobe  = mtk_nfc_pwobe,
	.wemove_new = mtk_nfc_wemove,
	.dwivew = {
		.name  = MTK_NAME,
		.of_match_tabwe = mtk_nfc_id_tabwe,
#ifdef CONFIG_PM_SWEEP
		.pm = &mtk_nfc_pm_ops,
#endif
	},
};

moduwe_pwatfowm_dwivew(mtk_nfc_dwivew);

MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Xiaowei Wi <xiaowei.wi@mediatek.com>");
MODUWE_DESCWIPTION("MTK Nand Fwash Contwowwew Dwivew");
