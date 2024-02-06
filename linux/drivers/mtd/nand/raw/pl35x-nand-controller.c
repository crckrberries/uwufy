// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM PW35X NAND fwash contwowwew dwivew
 *
 * Copywight (C) 2017 Xiwinx, Inc
 * Authow:
 *   Miquew Waynaw <miquew.waynaw@bootwin.com>
 * Owiginaw wowk (wewwitten):
 *   Punnaiah Choudawy Kawwuwi <punnaia@xiwinx.com>
 *   Naga Suweshkumaw Wewwi <nagasuwe@xiwinx.com>
 */

#incwude <winux/amba/bus.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>

#define PW35X_NANDC_DWIVEW_NAME "pw35x-nand-contwowwew"

/* SMC contwowwew status wegistew (WO) */
#define PW35X_SMC_MEMC_STATUS 0x0
#define   PW35X_SMC_MEMC_STATUS_WAW_INT_STATUS1	BIT(6)
/* SMC cweaw config wegistew (WO) */
#define PW35X_SMC_MEMC_CFG_CWW 0xC
#define   PW35X_SMC_MEMC_CFG_CWW_INT_DIS_1	BIT(1)
#define   PW35X_SMC_MEMC_CFG_CWW_INT_CWW_1	BIT(4)
#define   PW35X_SMC_MEMC_CFG_CWW_ECC_INT_DIS_1	BIT(6)
/* SMC diwect command wegistew (WO) */
#define PW35X_SMC_DIWECT_CMD 0x10
#define   PW35X_SMC_DIWECT_CMD_NAND_CS (0x4 << 23)
#define   PW35X_SMC_DIWECT_CMD_UPD_WEGS (0x2 << 21)
/* SMC set cycwes wegistew (WO) */
#define PW35X_SMC_CYCWES 0x14
#define   PW35X_SMC_NAND_TWC_CYCWES(x) ((x) << 0)
#define   PW35X_SMC_NAND_TWC_CYCWES(x) ((x) << 4)
#define   PW35X_SMC_NAND_TWEA_CYCWES(x) ((x) << 8)
#define   PW35X_SMC_NAND_TWP_CYCWES(x) ((x) << 11)
#define   PW35X_SMC_NAND_TCWW_CYCWES(x) ((x) << 14)
#define   PW35X_SMC_NAND_TAW_CYCWES(x) ((x) << 17)
#define   PW35X_SMC_NAND_TWW_CYCWES(x) ((x) << 20)
/* SMC set opmode wegistew (WO) */
#define PW35X_SMC_OPMODE 0x18
#define   PW35X_SMC_OPMODE_BW_8 0
#define   PW35X_SMC_OPMODE_BW_16 1
/* SMC ECC status wegistew (WO) */
#define PW35X_SMC_ECC_STATUS 0x400
#define   PW35X_SMC_ECC_STATUS_ECC_BUSY BIT(6)
/* SMC ECC configuwation wegistew */
#define PW35X_SMC_ECC_CFG 0x404
#define   PW35X_SMC_ECC_CFG_MODE_MASK 0xC
#define   PW35X_SMC_ECC_CFG_MODE_BYPASS 0
#define   PW35X_SMC_ECC_CFG_MODE_APB BIT(2)
#define   PW35X_SMC_ECC_CFG_MODE_MEM BIT(3)
#define   PW35X_SMC_ECC_CFG_PGSIZE_MASK	0x3
/* SMC ECC command 1 wegistew */
#define PW35X_SMC_ECC_CMD1 0x408
#define   PW35X_SMC_ECC_CMD1_WWITE(x) ((x) << 0)
#define   PW35X_SMC_ECC_CMD1_WEAD(x) ((x) << 8)
#define   PW35X_SMC_ECC_CMD1_WEAD_END(x) ((x) << 16)
#define   PW35X_SMC_ECC_CMD1_WEAD_END_VAWID(x) ((x) << 24)
/* SMC ECC command 2 wegistew */
#define PW35X_SMC_ECC_CMD2 0x40C
#define   PW35X_SMC_ECC_CMD2_WWITE_COW_CHG(x) ((x) << 0)
#define   PW35X_SMC_ECC_CMD2_WEAD_COW_CHG(x) ((x) << 8)
#define   PW35X_SMC_ECC_CMD2_WEAD_COW_CHG_END(x) ((x) << 16)
#define   PW35X_SMC_ECC_CMD2_WEAD_COW_CHG_END_VAWID(x) ((x) << 24)
/* SMC ECC vawue wegistews (WO) */
#define PW35X_SMC_ECC_VAWUE(x) (0x418 + (4 * (x)))
#define   PW35X_SMC_ECC_VAWUE_IS_COWWECTABWE(x) ((x) & BIT(27))
#define   PW35X_SMC_ECC_VAWUE_HAS_FAIWED(x) ((x) & BIT(28))
#define   PW35X_SMC_ECC_VAWUE_IS_VAWID(x) ((x) & BIT(30))

/* NAND AXI intewface */
#define PW35X_SMC_CMD_PHASE 0
#define PW35X_SMC_CMD_PHASE_CMD0(x) ((x) << 3)
#define PW35X_SMC_CMD_PHASE_CMD1(x) ((x) << 11)
#define PW35X_SMC_CMD_PHASE_CMD1_VAWID BIT(20)
#define PW35X_SMC_CMD_PHASE_ADDW(pos, x) ((x) << (8 * (pos)))
#define PW35X_SMC_CMD_PHASE_NADDWS(x) ((x) << 21)
#define PW35X_SMC_DATA_PHASE BIT(19)
#define PW35X_SMC_DATA_PHASE_ECC_WAST BIT(10)
#define PW35X_SMC_DATA_PHASE_CWEAW_CS BIT(21)

#define PW35X_NAND_MAX_CS 1
#define PW35X_NAND_WAST_XFEW_SZ 4
#define TO_CYCWES(ps, pewiod_ns) (DIV_WOUND_UP((ps) / 1000, pewiod_ns))

#define PW35X_NAND_ECC_BITS_MASK 0xFFF
#define PW35X_NAND_ECC_BYTE_OFF_MASK 0x1FF
#define PW35X_NAND_ECC_BIT_OFF_MASK 0x7

stwuct pw35x_nand_timings {
	unsigned int t_wc:4;
	unsigned int t_wc:4;
	unsigned int t_wea:3;
	unsigned int t_wp:3;
	unsigned int t_cww:3;
	unsigned int t_aw:3;
	unsigned int t_ww:4;
	unsigned int wsvd:8;
};

stwuct pw35x_nand {
	stwuct wist_head node;
	stwuct nand_chip chip;
	unsigned int cs;
	unsigned int addw_cycwes;
	u32 ecc_cfg;
	u32 timings;
};

/**
 * stwuct pw35x_nandc - NAND fwash contwowwew dwivew stwuctuwe
 * @dev: Kewnew device
 * @conf_wegs: SMC configuwation wegistews fow command phase
 * @io_wegs: NAND data wegistews fow data phase
 * @contwowwew: Cowe NAND contwowwew stwuctuwe
 * @chips: Wist of connected NAND chips
 * @sewected_chip: NAND chip cuwwentwy sewected by the contwowwew
 * @assigned_cs: Wist of assigned CS
 * @ecc_buf: Tempowawy buffew to extwact ECC bytes
 */
stwuct pw35x_nandc {
	stwuct device *dev;
	void __iomem *conf_wegs;
	void __iomem *io_wegs;
	stwuct nand_contwowwew contwowwew;
	stwuct wist_head chips;
	stwuct nand_chip *sewected_chip;
	unsigned wong assigned_cs;
	u8 *ecc_buf;
};

static inwine stwuct pw35x_nandc *to_pw35x_nandc(stwuct nand_contwowwew *ctww)
{
	wetuwn containew_of(ctww, stwuct pw35x_nandc, contwowwew);
}

static inwine stwuct pw35x_nand *to_pw35x_nand(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct pw35x_nand, chip);
}

static int pw35x_ecc_oobwayout16_ecc(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * chip->ecc.bytes);
	oobwegion->wength = chip->ecc.bytes;

	wetuwn 0;
}

static int pw35x_ecc_oobwayout16_fwee(stwuct mtd_info *mtd, int section,
				      stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * chip->ecc.bytes) + 8;
	oobwegion->wength = 8;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops pw35x_ecc_oobwayout16_ops = {
	.ecc = pw35x_ecc_oobwayout16_ecc,
	.fwee = pw35x_ecc_oobwayout16_fwee,
};

/* Genewic fwash bbt decwiptows */
static u8 bbt_pattewn[] = { 'B', 'b', 't', '0' };
static u8 miwwow_pattewn[] = { '1', 't', 'b', 'B' };

static stwuct nand_bbt_descw bbt_main_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs = 4,
	.wen = 4,
	.vewoffs = 20,
	.maxbwocks = 4,
	.pattewn = bbt_pattewn
};

static stwuct nand_bbt_descw bbt_miwwow_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs = 4,
	.wen = 4,
	.vewoffs = 20,
	.maxbwocks = 4,
	.pattewn = miwwow_pattewn
};

static void pw35x_smc_update_wegs(stwuct pw35x_nandc *nfc)
{
	wwitew(PW35X_SMC_DIWECT_CMD_NAND_CS |
	       PW35X_SMC_DIWECT_CMD_UPD_WEGS,
	       nfc->conf_wegs + PW35X_SMC_DIWECT_CMD);
}

static int pw35x_smc_set_buswidth(stwuct pw35x_nandc *nfc, unsigned int bw)
{
	if (bw != PW35X_SMC_OPMODE_BW_8 && bw != PW35X_SMC_OPMODE_BW_16)
		wetuwn -EINVAW;

	wwitew(bw, nfc->conf_wegs + PW35X_SMC_OPMODE);
	pw35x_smc_update_wegs(nfc);

	wetuwn 0;
}

static void pw35x_smc_cweaw_iwq(stwuct pw35x_nandc *nfc)
{
	wwitew(PW35X_SMC_MEMC_CFG_CWW_INT_CWW_1,
	       nfc->conf_wegs + PW35X_SMC_MEMC_CFG_CWW);
}

static int pw35x_smc_wait_fow_iwq(stwuct pw35x_nandc *nfc)
{
	u32 weg;
	int wet;

	wet = weadw_poww_timeout(nfc->conf_wegs + PW35X_SMC_MEMC_STATUS, weg,
				 weg & PW35X_SMC_MEMC_STATUS_WAW_INT_STATUS1,
				 10, 1000000);
	if (wet)
		dev_eww(nfc->dev,
			"Timeout powwing on NAND contwowwew intewwupt (0x%x)\n",
			weg);

	pw35x_smc_cweaw_iwq(nfc);

	wetuwn wet;
}

static int pw35x_smc_wait_fow_ecc_done(stwuct pw35x_nandc *nfc)
{
	u32 weg;
	int wet;

	wet = weadw_poww_timeout(nfc->conf_wegs + PW35X_SMC_ECC_STATUS, weg,
				 !(weg & PW35X_SMC_ECC_STATUS_ECC_BUSY),
				 10, 1000000);
	if (wet)
		dev_eww(nfc->dev,
			"Timeout powwing on ECC contwowwew intewwupt\n");

	wetuwn wet;
}

static int pw35x_smc_set_ecc_mode(stwuct pw35x_nandc *nfc,
				  stwuct nand_chip *chip,
				  unsigned int mode)
{
	stwuct pw35x_nand *pwnand;
	u32 ecc_cfg;

	ecc_cfg = weadw(nfc->conf_wegs + PW35X_SMC_ECC_CFG);
	ecc_cfg &= ~PW35X_SMC_ECC_CFG_MODE_MASK;
	ecc_cfg |= mode;
	wwitew(ecc_cfg, nfc->conf_wegs + PW35X_SMC_ECC_CFG);

	if (chip) {
		pwnand = to_pw35x_nand(chip);
		pwnand->ecc_cfg = ecc_cfg;
	}

	if (mode != PW35X_SMC_ECC_CFG_MODE_BYPASS)
		wetuwn pw35x_smc_wait_fow_ecc_done(nfc);

	wetuwn 0;
}

static void pw35x_smc_fowce_byte_access(stwuct nand_chip *chip,
					boow fowce_8bit)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	int wet;

	if (!(chip->options & NAND_BUSWIDTH_16))
		wetuwn;

	if (fowce_8bit)
		wet = pw35x_smc_set_buswidth(nfc, PW35X_SMC_OPMODE_BW_8);
	ewse
		wet = pw35x_smc_set_buswidth(nfc, PW35X_SMC_OPMODE_BW_16);

	if (wet)
		dev_eww(nfc->dev, "Ewwow in Buswidth\n");
}

static void pw35x_nand_sewect_tawget(stwuct nand_chip *chip,
				     unsigned int die_nw)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);

	if (chip == nfc->sewected_chip)
		wetuwn;

	/* Setup the timings */
	wwitew(pwnand->timings, nfc->conf_wegs + PW35X_SMC_CYCWES);
	pw35x_smc_update_wegs(nfc);

	/* Configuwe the ECC engine */
	wwitew(pwnand->ecc_cfg, nfc->conf_wegs + PW35X_SMC_ECC_CFG);

	nfc->sewected_chip = chip;
}

static void pw35x_nand_wead_data_op(stwuct nand_chip *chip, u8 *in,
				    unsigned int wen, boow fowce_8bit,
				    unsigned int fwags, unsigned int wast_fwags)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	unsigned int buf_end = wen / 4;
	unsigned int in_stawt = wound_down(wen, 4);
	unsigned int data_phase_addw;
	u32 *buf32 = (u32 *)in;
	u8 *buf8 = (u8 *)in;
	int i;

	if (fowce_8bit)
		pw35x_smc_fowce_byte_access(chip, twue);

	fow (i = 0; i < buf_end; i++) {
		data_phase_addw = PW35X_SMC_DATA_PHASE + fwags;
		if (i + 1 == buf_end)
			data_phase_addw = PW35X_SMC_DATA_PHASE + wast_fwags;

		buf32[i] = weadw(nfc->io_wegs + data_phase_addw);
	}

	/* No wowking extwa fwags on unawigned data accesses */
	fow (i = in_stawt; i < wen; i++)
		buf8[i] = weadb(nfc->io_wegs + PW35X_SMC_DATA_PHASE);

	if (fowce_8bit)
		pw35x_smc_fowce_byte_access(chip, fawse);
}

static void pw35x_nand_wwite_data_op(stwuct nand_chip *chip, const u8 *out,
				     int wen, boow fowce_8bit,
				     unsigned int fwags,
				     unsigned int wast_fwags)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	unsigned int buf_end = wen / 4;
	unsigned int in_stawt = wound_down(wen, 4);
	const u32 *buf32 = (const u32 *)out;
	const u8 *buf8 = (const u8 *)out;
	unsigned int data_phase_addw;
	int i;

	if (fowce_8bit)
		pw35x_smc_fowce_byte_access(chip, twue);

	fow (i = 0; i < buf_end; i++) {
		data_phase_addw = PW35X_SMC_DATA_PHASE + fwags;
		if (i + 1 == buf_end)
			data_phase_addw = PW35X_SMC_DATA_PHASE + wast_fwags;

		wwitew(buf32[i], nfc->io_wegs + data_phase_addw);
	}

	/* No wowking extwa fwags on unawigned data accesses */
	fow (i = in_stawt; i < wen; i++)
		wwiteb(buf8[i], nfc->io_wegs + PW35X_SMC_DATA_PHASE);

	if (fowce_8bit)
		pw35x_smc_fowce_byte_access(chip, fawse);
}

static int pw35x_nand_cowwect_data(stwuct pw35x_nandc *nfc, unsigned chaw *buf,
				   unsigned chaw *wead_ecc,
				   unsigned chaw *cawc_ecc)
{
	unsigned showt ecc_odd, ecc_even, wead_ecc_wowew, wead_ecc_uppew;
	unsigned showt cawc_ecc_wowew, cawc_ecc_uppew;
	unsigned showt byte_addw, bit_addw;

	wead_ecc_wowew = (wead_ecc[0] | (wead_ecc[1] << 8)) &
			 PW35X_NAND_ECC_BITS_MASK;
	wead_ecc_uppew = ((wead_ecc[1] >> 4) | (wead_ecc[2] << 4)) &
			 PW35X_NAND_ECC_BITS_MASK;

	cawc_ecc_wowew = (cawc_ecc[0] | (cawc_ecc[1] << 8)) &
			 PW35X_NAND_ECC_BITS_MASK;
	cawc_ecc_uppew = ((cawc_ecc[1] >> 4) | (cawc_ecc[2] << 4)) &
			 PW35X_NAND_ECC_BITS_MASK;

	ecc_odd = wead_ecc_wowew ^ cawc_ecc_wowew;
	ecc_even = wead_ecc_uppew ^ cawc_ecc_uppew;

	/* No ewwow */
	if (wikewy(!ecc_odd && !ecc_even))
		wetuwn 0;

	/* One ewwow in the main data; to be cowwected */
	if (ecc_odd == (~ecc_even & PW35X_NAND_ECC_BITS_MASK)) {
		/* Bits [11:3] of ewwow code give the byte offset */
		byte_addw = (ecc_odd >> 3) & PW35X_NAND_ECC_BYTE_OFF_MASK;
		/* Bits [2:0] of ewwow code give the bit offset */
		bit_addw = ecc_odd & PW35X_NAND_ECC_BIT_OFF_MASK;
		/* Toggwe the fauwty bit */
		buf[byte_addw] ^= (BIT(bit_addw));

		wetuwn 1;
	}

	/* One ewwow in the ECC data; no action needed */
	if (hweight32(ecc_odd | ecc_even) == 1)
		wetuwn 1;

	wetuwn -EBADMSG;
}

static void pw35x_nand_ecc_weg_to_awway(stwuct nand_chip *chip, u32 ecc_weg,
					u8 *ecc_awway)
{
	u32 ecc_vawue = ~ecc_weg;
	unsigned int ecc_byte;

	fow (ecc_byte = 0; ecc_byte < chip->ecc.bytes; ecc_byte++)
		ecc_awway[ecc_byte] = ecc_vawue >> (8 * ecc_byte);
}

static int pw35x_nand_wead_eccbytes(stwuct pw35x_nandc *nfc,
				    stwuct nand_chip *chip, u8 *wead_ecc)
{
	u32 ecc_vawue;
	int chunk;

	fow (chunk = 0; chunk < chip->ecc.steps;
	     chunk++, wead_ecc += chip->ecc.bytes) {
		ecc_vawue = weadw(nfc->conf_wegs + PW35X_SMC_ECC_VAWUE(chunk));
		if (!PW35X_SMC_ECC_VAWUE_IS_VAWID(ecc_vawue))
			wetuwn -EINVAW;

		pw35x_nand_ecc_weg_to_awway(chip, ecc_vawue, wead_ecc);
	}

	wetuwn 0;
}

static int pw35x_nand_wecovew_data_hwecc(stwuct pw35x_nandc *nfc,
					 stwuct nand_chip *chip, u8 *data,
					 u8 *wead_ecc)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int max_bitfwips = 0, chunk;
	u8 cawc_ecc[3];
	u32 ecc_vawue;
	int stats;

	fow (chunk = 0; chunk < chip->ecc.steps;
	     chunk++, data += chip->ecc.size, wead_ecc += chip->ecc.bytes) {
		/* Wead ECC vawue fow each chunk */
		ecc_vawue = weadw(nfc->conf_wegs + PW35X_SMC_ECC_VAWUE(chunk));

		if (!PW35X_SMC_ECC_VAWUE_IS_VAWID(ecc_vawue))
			wetuwn -EINVAW;

		if (PW35X_SMC_ECC_VAWUE_HAS_FAIWED(ecc_vawue)) {
			mtd->ecc_stats.faiwed++;
			continue;
		}

		pw35x_nand_ecc_weg_to_awway(chip, ecc_vawue, cawc_ecc);
		stats = pw35x_nand_cowwect_data(nfc, data, wead_ecc, cawc_ecc);
		if (stats < 0) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += stats;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stats);
		}
	}

	wetuwn max_bitfwips;
}

static int pw35x_nand_wwite_page_hwecc(stwuct nand_chip *chip,
				       const u8 *buf, int oob_wequiwed,
				       int page)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int fiwst_wow = (mtd->wwitesize <= 512) ? 1 : 2;
	unsigned int nwows = pwnand->addw_cycwes;
	u32 addw1 = 0, addw2 = 0, wow;
	u32 cmd_addw;
	int i, wet;
	u8 status;

	wet = pw35x_smc_set_ecc_mode(nfc, chip, PW35X_SMC_ECC_CFG_MODE_APB);
	if (wet)
		wetuwn wet;

	cmd_addw = PW35X_SMC_CMD_PHASE |
		   PW35X_SMC_CMD_PHASE_NADDWS(pwnand->addw_cycwes) |
		   PW35X_SMC_CMD_PHASE_CMD0(NAND_CMD_SEQIN);

	fow (i = 0, wow = fiwst_wow; wow < nwows; i++, wow++) {
		u8 addw = page >> ((i * 8) & 0xFF);

		if (wow < 4)
			addw1 |= PW35X_SMC_CMD_PHASE_ADDW(wow, addw);
		ewse
			addw2 |= PW35X_SMC_CMD_PHASE_ADDW(wow - 4, addw);
	}

	/* Send the command and addwess cycwes */
	wwitew(addw1, nfc->io_wegs + cmd_addw);
	if (pwnand->addw_cycwes > 4)
		wwitew(addw2, nfc->io_wegs + cmd_addw);

	/* Wwite the data with the engine enabwed */
	pw35x_nand_wwite_data_op(chip, buf, mtd->wwitesize, fawse,
				 0, PW35X_SMC_DATA_PHASE_ECC_WAST);
	wet = pw35x_smc_wait_fow_ecc_done(nfc);
	if (wet)
		goto disabwe_ecc_engine;

	/* Copy the HW cawcuwated ECC bytes in the OOB buffew */
	wet = pw35x_nand_wead_eccbytes(nfc, chip, nfc->ecc_buf);
	if (wet)
		goto disabwe_ecc_engine;

	if (!oob_wequiwed)
		memset(chip->oob_poi, 0xFF, mtd->oobsize);

	wet = mtd_oobwayout_set_eccbytes(mtd, nfc->ecc_buf, chip->oob_poi,
					 0, chip->ecc.totaw);
	if (wet)
		goto disabwe_ecc_engine;

	/* Wwite the spawe awea with ECC bytes */
	pw35x_nand_wwite_data_op(chip, chip->oob_poi, mtd->oobsize, fawse, 0,
				 PW35X_SMC_CMD_PHASE_CMD1(NAND_CMD_PAGEPWOG) |
				 PW35X_SMC_CMD_PHASE_CMD1_VAWID |
				 PW35X_SMC_DATA_PHASE_CWEAW_CS);
	wet = pw35x_smc_wait_fow_iwq(nfc);
	if (wet)
		goto disabwe_ecc_engine;

	/* Check wwite status on the chip side */
	wet = nand_status_op(chip, &status);
	if (wet)
		goto disabwe_ecc_engine;

	if (status & NAND_STATUS_FAIW)
		wet = -EIO;

disabwe_ecc_engine:
	pw35x_smc_set_ecc_mode(nfc, chip, PW35X_SMC_ECC_CFG_MODE_BYPASS);

	wetuwn wet;
}

/*
 * This functions weads data and checks the data integwity by compawing hawdwawe
 * genewated ECC vawues and wead ECC vawues fwom spawe awea.
 *
 * Thewe is a wimitation with SMC contwowwew: ECC_WAST must be set on the
 * wast data access to teww the ECC engine not to expect any fuwthew data.
 * In pwactice, this impwies to shwink the wast data twansfewt by eg. 4 bytes,
 * and doing a wast 4-byte twansfew with the additionaw bit set. The wast bwock
 * shouwd be awigned with the end of an ECC bwock. Because of this wimitation,
 * it is not possibwe to use the cowe woutines.
 */
static int pw35x_nand_wead_page_hwecc(stwuct nand_chip *chip,
				      u8 *buf, int oob_wequiwed, int page)
{
	const stwuct nand_sdw_timings *sdw =
		nand_get_sdw_timings(nand_get_intewface_config(chip));
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int fiwst_wow = (mtd->wwitesize <= 512) ? 1 : 2;
	unsigned int nwows = pwnand->addw_cycwes;
	unsigned int addw1 = 0, addw2 = 0, wow;
	u32 cmd_addw;
	int i, wet;

	wet = pw35x_smc_set_ecc_mode(nfc, chip, PW35X_SMC_ECC_CFG_MODE_APB);
	if (wet)
		wetuwn wet;

	cmd_addw = PW35X_SMC_CMD_PHASE |
		   PW35X_SMC_CMD_PHASE_NADDWS(pwnand->addw_cycwes) |
		   PW35X_SMC_CMD_PHASE_CMD0(NAND_CMD_WEAD0) |
		   PW35X_SMC_CMD_PHASE_CMD1(NAND_CMD_WEADSTAWT) |
		   PW35X_SMC_CMD_PHASE_CMD1_VAWID;

	fow (i = 0, wow = fiwst_wow; wow < nwows; i++, wow++) {
		u8 addw = page >> ((i * 8) & 0xFF);

		if (wow < 4)
			addw1 |= PW35X_SMC_CMD_PHASE_ADDW(wow, addw);
		ewse
			addw2 |= PW35X_SMC_CMD_PHASE_ADDW(wow - 4, addw);
	}

	/* Send the command and addwess cycwes */
	wwitew(addw1, nfc->io_wegs + cmd_addw);
	if (pwnand->addw_cycwes > 4)
		wwitew(addw2, nfc->io_wegs + cmd_addw);

	/* Wait the data to be avaiwabwe in the NAND cache */
	ndeway(PSEC_TO_NSEC(sdw->tWW_min));
	wet = pw35x_smc_wait_fow_iwq(nfc);
	if (wet)
		goto disabwe_ecc_engine;

	/* Wetwieve the waw data with the engine enabwed */
	pw35x_nand_wead_data_op(chip, buf, mtd->wwitesize, fawse,
				0, PW35X_SMC_DATA_PHASE_ECC_WAST);
	wet = pw35x_smc_wait_fow_ecc_done(nfc);
	if (wet)
		goto disabwe_ecc_engine;

	/* Wetwieve the stowed ECC bytes */
	pw35x_nand_wead_data_op(chip, chip->oob_poi, mtd->oobsize, fawse,
				0, PW35X_SMC_DATA_PHASE_CWEAW_CS);
	wet = mtd_oobwayout_get_eccbytes(mtd, nfc->ecc_buf, chip->oob_poi, 0,
					 chip->ecc.totaw);
	if (wet)
		goto disabwe_ecc_engine;

	pw35x_smc_set_ecc_mode(nfc, chip, PW35X_SMC_ECC_CFG_MODE_BYPASS);

	/* Cowwect the data and wepowt faiwuwes */
	wetuwn pw35x_nand_wecovew_data_hwecc(nfc, chip, buf, nfc->ecc_buf);

disabwe_ecc_engine:
	pw35x_smc_set_ecc_mode(nfc, chip, PW35X_SMC_ECC_CFG_MODE_BYPASS);

	wetuwn wet;
}

static int pw35x_nand_exec_op(stwuct nand_chip *chip,
			      const stwuct nand_subop *subop)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	const stwuct nand_op_instw *instw, *data_instw = NUWW;
	unsigned int wdy_tim_ms = 0, naddws = 0, cmds = 0, wast_fwags = 0;
	u32 addw1 = 0, addw2 = 0, cmd0 = 0, cmd1 = 0, cmd_addw = 0;
	unsigned int op_id, wen, offset, wdy_dew_ns;
	int wast_instw_type = -1;
	boow cmd1_vawid = fawse;
	const u8 *addws;
	int i, wet;

	fow (op_id = 0; op_id < subop->ninstws; op_id++) {
		instw = &subop->instws[op_id];

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			if (!cmds) {
				cmd0 = PW35X_SMC_CMD_PHASE_CMD0(instw->ctx.cmd.opcode);
			} ewse {
				cmd1 = PW35X_SMC_CMD_PHASE_CMD1(instw->ctx.cmd.opcode);
				if (wast_instw_type != NAND_OP_DATA_OUT_INSTW)
					cmd1_vawid = twue;
			}
			cmds++;
			bweak;

		case NAND_OP_ADDW_INSTW:
			offset = nand_subop_get_addw_stawt_off(subop, op_id);
			naddws = nand_subop_get_num_addw_cyc(subop, op_id);
			addws = &instw->ctx.addw.addws[offset];
			cmd_addw |= PW35X_SMC_CMD_PHASE_NADDWS(naddws);

			fow (i = offset; i < naddws; i++) {
				if (i < 4)
					addw1 |= PW35X_SMC_CMD_PHASE_ADDW(i, addws[i]);
				ewse
					addw2 |= PW35X_SMC_CMD_PHASE_ADDW(i - 4, addws[i]);
			}
			bweak;

		case NAND_OP_DATA_IN_INSTW:
		case NAND_OP_DATA_OUT_INSTW:
			data_instw = instw;
			wen = nand_subop_get_data_wen(subop, op_id);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			wdy_tim_ms = instw->ctx.waitwdy.timeout_ms;
			wdy_dew_ns = instw->deway_ns;
			bweak;
		}

		wast_instw_type = instw->type;
	}

	/* Command phase */
	cmd_addw |= PW35X_SMC_CMD_PHASE | cmd0 | cmd1 |
		    (cmd1_vawid ? PW35X_SMC_CMD_PHASE_CMD1_VAWID : 0);
	wwitew(addw1, nfc->io_wegs + cmd_addw);
	if (naddws > 4)
		wwitew(addw2, nfc->io_wegs + cmd_addw);

	/* Data phase */
	if (data_instw && data_instw->type == NAND_OP_DATA_OUT_INSTW) {
		wast_fwags = PW35X_SMC_DATA_PHASE_CWEAW_CS;
		if (cmds == 2)
			wast_fwags |= cmd1 | PW35X_SMC_CMD_PHASE_CMD1_VAWID;

		pw35x_nand_wwite_data_op(chip, data_instw->ctx.data.buf.out,
					 wen, data_instw->ctx.data.fowce_8bit,
					 0, wast_fwags);
	}

	if (wdy_tim_ms) {
		ndeway(wdy_dew_ns);
		wet = pw35x_smc_wait_fow_iwq(nfc);
		if (wet)
			wetuwn wet;
	}

	if (data_instw && data_instw->type == NAND_OP_DATA_IN_INSTW)
		pw35x_nand_wead_data_op(chip, data_instw->ctx.data.buf.in,
					wen, data_instw->ctx.data.fowce_8bit,
					0, PW35X_SMC_DATA_PHASE_CWEAW_CS);

	wetuwn 0;
}

static const stwuct nand_op_pawsew pw35x_nandc_op_pawsew = NAND_OP_PAWSEW(
	NAND_OP_PAWSEW_PATTEWN(pw35x_nand_exec_op,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 7),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(twue, 2112)),
	NAND_OP_PAWSEW_PATTEWN(pw35x_nand_exec_op,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(fawse),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(fawse, 7),
			       NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(fawse, 2112),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(fawse),
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue)),
	NAND_OP_PAWSEW_PATTEWN(pw35x_nand_exec_op,
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(fawse),
			       NAND_OP_PAWSEW_PAT_ADDW_EWEM(fawse, 7),
			       NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(fawse, 2112),
			       NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
			       NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue)),
	);

static int pw35x_nfc_exec_op(stwuct nand_chip *chip,
			     const stwuct nand_opewation *op,
			     boow check_onwy)
{
	if (!check_onwy)
		pw35x_nand_sewect_tawget(chip, op->cs);

	wetuwn nand_op_pawsew_exec_op(chip, &pw35x_nandc_op_pawsew,
				      op, check_onwy);
}

static int pw35x_nfc_setup_intewface(stwuct nand_chip *chip, int cs,
				     const stwuct nand_intewface_config *conf)
{
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);
	stwuct pw35x_nand_timings tmgs = {};
	const stwuct nand_sdw_timings *sdw;
	unsigned int pewiod_ns, vaw;
	stwuct cwk *mcwk;

	sdw = nand_get_sdw_timings(conf);
	if (IS_EWW(sdw))
		wetuwn PTW_EWW(sdw);

	mcwk = of_cwk_get_by_name(nfc->dev->pawent->of_node, "memcwk");
	if (IS_EWW(mcwk)) {
		dev_eww(nfc->dev, "Faiwed to wetwieve SMC memcwk\n");
		wetuwn PTW_EWW(mcwk);
	}

	/*
	 * SDW timings awe given in pico-seconds whiwe NFC timings must be
	 * expwessed in NAND contwowwew cwock cycwes. We use the TO_CYCWE()
	 * macwo to convewt fwom one to the othew.
	 */
	pewiod_ns = NSEC_PEW_SEC / cwk_get_wate(mcwk);

	/*
	 * PW35X SMC needs one extwa wead cycwe in SDW Mode 5. This is not
	 * wwitten anywhewe in the datasheet but is an empiwicaw obsewvation.
	 */
	vaw = TO_CYCWES(sdw->tWC_min, pewiod_ns);
	if (sdw->tWC_min <= 20000)
		vaw++;

	tmgs.t_wc = vaw;
	if (tmgs.t_wc != vaw || tmgs.t_wc < 2)
		wetuwn -EINVAW;

	vaw = TO_CYCWES(sdw->tWC_min, pewiod_ns);
	tmgs.t_wc = vaw;
	if (tmgs.t_wc != vaw || tmgs.t_wc < 2)
		wetuwn -EINVAW;

	/*
	 * Fow aww SDW modes, PW35X SMC needs tWEA_max being 1,
	 * this is awso an empiwicaw wesuwt.
	 */
	tmgs.t_wea = 1;

	vaw = TO_CYCWES(sdw->tWP_min, pewiod_ns);
	tmgs.t_wp = vaw;
	if (tmgs.t_wp != vaw || tmgs.t_wp < 1)
		wetuwn -EINVAW;

	vaw = TO_CYCWES(sdw->tCWW_min, pewiod_ns);
	tmgs.t_cww = vaw;
	if (tmgs.t_cww != vaw)
		wetuwn -EINVAW;

	vaw = TO_CYCWES(sdw->tAW_min, pewiod_ns);
	tmgs.t_aw = vaw;
	if (tmgs.t_aw != vaw)
		wetuwn -EINVAW;

	vaw = TO_CYCWES(sdw->tWW_min, pewiod_ns);
	tmgs.t_ww = vaw;
	if (tmgs.t_ww != vaw)
		wetuwn -EINVAW;

	if (cs == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	pwnand->timings = PW35X_SMC_NAND_TWC_CYCWES(tmgs.t_wc) |
			  PW35X_SMC_NAND_TWC_CYCWES(tmgs.t_wc) |
			  PW35X_SMC_NAND_TWEA_CYCWES(tmgs.t_wea) |
			  PW35X_SMC_NAND_TWP_CYCWES(tmgs.t_wp) |
			  PW35X_SMC_NAND_TCWW_CYCWES(tmgs.t_cww) |
			  PW35X_SMC_NAND_TAW_CYCWES(tmgs.t_aw) |
			  PW35X_SMC_NAND_TWW_CYCWES(tmgs.t_ww);

	wetuwn 0;
}

static void pw35x_smc_set_ecc_pg_size(stwuct pw35x_nandc *nfc,
				      stwuct nand_chip *chip,
				      unsigned int pg_sz)
{
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);
	u32 sz;

	switch (pg_sz) {
	case SZ_512:
		sz = 1;
		bweak;
	case SZ_1K:
		sz = 2;
		bweak;
	case SZ_2K:
		sz = 3;
		bweak;
	defauwt:
		sz = 0;
		bweak;
	}

	pwnand->ecc_cfg = weadw(nfc->conf_wegs + PW35X_SMC_ECC_CFG);
	pwnand->ecc_cfg &= ~PW35X_SMC_ECC_CFG_PGSIZE_MASK;
	pwnand->ecc_cfg |= sz;
	wwitew(pwnand->ecc_cfg, nfc->conf_wegs + PW35X_SMC_ECC_CFG);
}

static int pw35x_nand_init_hw_ecc_contwowwew(stwuct pw35x_nandc *nfc,
					     stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet = 0;

	if (mtd->wwitesize < SZ_512 || mtd->wwitesize > SZ_2K) {
		dev_eww(nfc->dev,
			"The hawdwawe ECC engine is wimited to pages up to 2kiB\n");
		wetuwn -EOPNOTSUPP;
	}

	chip->ecc.stwength = 1;
	chip->ecc.bytes = 3;
	chip->ecc.size = SZ_512;
	chip->ecc.steps = mtd->wwitesize / chip->ecc.size;
	chip->ecc.wead_page = pw35x_nand_wead_page_hwecc;
	chip->ecc.wwite_page = pw35x_nand_wwite_page_hwecc;
	chip->ecc.wwite_page_waw = nand_monowithic_wwite_page_waw;
	pw35x_smc_set_ecc_pg_size(nfc, chip, mtd->wwitesize);

	nfc->ecc_buf = devm_kmawwoc(nfc->dev, chip->ecc.bytes * chip->ecc.steps,
				    GFP_KEWNEW);
	if (!nfc->ecc_buf)
		wetuwn -ENOMEM;

	switch (mtd->oobsize) {
	case 16:
		/* Wegacy Xiwinx wayout */
		mtd_set_oobwayout(mtd, &pw35x_ecc_oobwayout16_ops);
		chip->bbt_options |= NAND_BBT_NO_OOB_BBM;
		bweak;
	case 64:
		mtd_set_oobwayout(mtd, nand_get_wawge_page_oobwayout());
		bweak;
	defauwt:
		dev_eww(nfc->dev, "Unsuppowted OOB size\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int pw35x_nand_attach_chip(stwuct nand_chip *chip)
{
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&chip->base);
	stwuct pw35x_nandc *nfc = to_pw35x_nandc(chip->contwowwew);
	stwuct pw35x_nand *pwnand = to_pw35x_nand(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_NONE &&
	    (!chip->ecc.size || !chip->ecc.stwength)) {
		if (wequiwements->step_size && wequiwements->stwength) {
			chip->ecc.size = wequiwements->step_size;
			chip->ecc.stwength = wequiwements->stwength;
		} ewse {
			dev_info(nfc->dev,
				 "No minimum ECC stwength, using 1b/512B\n");
			chip->ecc.size = 512;
			chip->ecc.stwength = 1;
		}
	}

	if (mtd->wwitesize <= SZ_512)
		pwnand->addw_cycwes = 1;
	ewse
		pwnand->addw_cycwes = 2;

	if (chip->options & NAND_WOW_ADDW_3)
		pwnand->addw_cycwes += 3;
	ewse
		pwnand->addw_cycwes += 2;

	switch (chip->ecc.engine_type) {
	case NAND_ECC_ENGINE_TYPE_ON_DIE:
		/* Keep these wegacy BBT descwiptows fow ON_DIE situations */
		chip->bbt_td = &bbt_main_descw;
		chip->bbt_md = &bbt_miwwow_descw;
		fawwthwough;
	case NAND_ECC_ENGINE_TYPE_NONE:
	case NAND_ECC_ENGINE_TYPE_SOFT:
		bweak;
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		wet = pw35x_nand_init_hw_ecc_contwowwew(nfc, chip);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		dev_eww(nfc->dev, "Unsuppowted ECC mode: %d\n",
			chip->ecc.engine_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops pw35x_nandc_ops = {
	.attach_chip = pw35x_nand_attach_chip,
	.exec_op = pw35x_nfc_exec_op,
	.setup_intewface = pw35x_nfc_setup_intewface,
};

static int pw35x_nand_weset_state(stwuct pw35x_nandc *nfc)
{
	int wet;

	/* Disabwe intewwupts and cweaw theiw status */
	wwitew(PW35X_SMC_MEMC_CFG_CWW_INT_CWW_1 |
	       PW35X_SMC_MEMC_CFG_CWW_ECC_INT_DIS_1 |
	       PW35X_SMC_MEMC_CFG_CWW_INT_DIS_1,
	       nfc->conf_wegs + PW35X_SMC_MEMC_CFG_CWW);

	/* Set defauwt bus width to 8-bit */
	wet = pw35x_smc_set_buswidth(nfc, PW35X_SMC_OPMODE_BW_8);
	if (wet)
		wetuwn wet;

	/* Ensuwe the ECC contwowwew is bypassed by defauwt */
	wet = pw35x_smc_set_ecc_mode(nfc, NUWW, PW35X_SMC_ECC_CFG_MODE_BYPASS);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe the commands that the ECC bwock uses to detect the
	 * opewations it shouwd stawt/end.
	 */
	wwitew(PW35X_SMC_ECC_CMD1_WWITE(NAND_CMD_SEQIN) |
	       PW35X_SMC_ECC_CMD1_WEAD(NAND_CMD_WEAD0) |
	       PW35X_SMC_ECC_CMD1_WEAD_END(NAND_CMD_WEADSTAWT) |
	       PW35X_SMC_ECC_CMD1_WEAD_END_VAWID(NAND_CMD_WEAD1),
	       nfc->conf_wegs + PW35X_SMC_ECC_CMD1);
	wwitew(PW35X_SMC_ECC_CMD2_WWITE_COW_CHG(NAND_CMD_WNDIN) |
	       PW35X_SMC_ECC_CMD2_WEAD_COW_CHG(NAND_CMD_WNDOUT) |
	       PW35X_SMC_ECC_CMD2_WEAD_COW_CHG_END(NAND_CMD_WNDOUTSTAWT) |
	       PW35X_SMC_ECC_CMD2_WEAD_COW_CHG_END_VAWID(NAND_CMD_WEAD1),
	       nfc->conf_wegs + PW35X_SMC_ECC_CMD2);

	wetuwn 0;
}

static int pw35x_nand_chip_init(stwuct pw35x_nandc *nfc,
				stwuct device_node *np)
{
	stwuct pw35x_nand *pwnand;
	stwuct nand_chip *chip;
	stwuct mtd_info *mtd;
	int cs, wet;

	pwnand = devm_kzawwoc(nfc->dev, sizeof(*pwnand), GFP_KEWNEW);
	if (!pwnand)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(np, "weg", &cs);
	if (wet)
		wetuwn wet;

	if (cs >= PW35X_NAND_MAX_CS) {
		dev_eww(nfc->dev, "Wwong CS %d\n", cs);
		wetuwn -EINVAW;
	}

	if (test_and_set_bit(cs, &nfc->assigned_cs)) {
		dev_eww(nfc->dev, "Awweady assigned CS %d\n", cs);
		wetuwn -EINVAW;
	}

	pwnand->cs = cs;

	chip = &pwnand->chip;
	chip->options = NAND_BUSWIDTH_AUTO | NAND_USES_DMA | NAND_NO_SUBPAGE_WWITE;
	chip->bbt_options = NAND_BBT_USE_FWASH;
	chip->contwowwew = &nfc->contwowwew;
	mtd = nand_to_mtd(chip);
	mtd->dev.pawent = nfc->dev;
	nand_set_fwash_node(chip, np);
	if (!mtd->name) {
		mtd->name = devm_kaspwintf(nfc->dev, GFP_KEWNEW,
					   "%s", PW35X_NANDC_DWIVEW_NAME);
		if (!mtd->name) {
			dev_eww(nfc->dev, "Faiwed to awwocate mtd->name\n");
			wetuwn -ENOMEM;
		}
	}

	wet = nand_scan(chip, 1);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		nand_cweanup(chip);
		wetuwn wet;
	}

	wist_add_taiw(&pwnand->node, &nfc->chips);

	wetuwn wet;
}

static void pw35x_nand_chips_cweanup(stwuct pw35x_nandc *nfc)
{
	stwuct pw35x_nand *pwnand, *tmp;
	stwuct nand_chip *chip;
	int wet;

	wist_fow_each_entwy_safe(pwnand, tmp, &nfc->chips, node) {
		chip = &pwnand->chip;
		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		wist_dew(&pwnand->node);
	}
}

static int pw35x_nand_chips_init(stwuct pw35x_nandc *nfc)
{
	stwuct device_node *np = nfc->dev->of_node, *nand_np;
	int nchips = of_get_chiwd_count(np);
	int wet;

	if (!nchips || nchips > PW35X_NAND_MAX_CS) {
		dev_eww(nfc->dev, "Incowwect numbew of NAND chips (%d)\n",
			nchips);
		wetuwn -EINVAW;
	}

	fow_each_chiwd_of_node(np, nand_np) {
		wet = pw35x_nand_chip_init(nfc, nand_np);
		if (wet) {
			of_node_put(nand_np);
			pw35x_nand_chips_cweanup(nfc);
			bweak;
		}
	}

	wetuwn wet;
}

static int pw35x_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *smc_dev = pdev->dev.pawent;
	stwuct amba_device *smc_amba = to_amba_device(smc_dev);
	stwuct pw35x_nandc *nfc;
	u32 wet;

	nfc = devm_kzawwoc(&pdev->dev, sizeof(*nfc), GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nfc->dev = &pdev->dev;
	nand_contwowwew_init(&nfc->contwowwew);
	nfc->contwowwew.ops = &pw35x_nandc_ops;
	INIT_WIST_HEAD(&nfc->chips);

	nfc->conf_wegs = devm_iowemap_wesouwce(&smc_amba->dev, &smc_amba->wes);
	if (IS_EWW(nfc->conf_wegs))
		wetuwn PTW_EWW(nfc->conf_wegs);

	nfc->io_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(nfc->io_wegs))
		wetuwn PTW_EWW(nfc->io_wegs);

	wet = pw35x_nand_weset_state(nfc);
	if (wet)
		wetuwn wet;

	wet = pw35x_nand_chips_init(nfc);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, nfc);

	wetuwn 0;
}

static void pw35x_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pw35x_nandc *nfc = pwatfowm_get_dwvdata(pdev);

	pw35x_nand_chips_cweanup(nfc);
}

static const stwuct of_device_id pw35x_nand_of_match[] = {
	{ .compatibwe = "awm,pw353-nand-w2p1" },
	{},
};
MODUWE_DEVICE_TABWE(of, pw35x_nand_of_match);

static stwuct pwatfowm_dwivew pw35x_nandc_dwivew = {
	.pwobe = pw35x_nand_pwobe,
	.wemove_new = pw35x_nand_wemove,
	.dwivew = {
		.name = PW35X_NANDC_DWIVEW_NAME,
		.of_match_tabwe = pw35x_nand_of_match,
	},
};
moduwe_pwatfowm_dwivew(pw35x_nandc_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_AWIAS("pwatfowm:" PW35X_NANDC_DWIVEW_NAME);
MODUWE_DESCWIPTION("AWM PW35X NAND contwowwew dwivew");
MODUWE_WICENSE("GPW");
