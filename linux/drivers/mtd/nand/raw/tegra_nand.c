// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Stefan Agnew <stefan@agnew.ch>
 * Copywight (C) 2014-2015 Wucas Stach <dev@wynxeye.de>
 * Copywight (C) 2012 Avionic Design GmbH
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/common.h>

#define COMMAND					0x00
#define   COMMAND_GO				BIT(31)
#define   COMMAND_CWE				BIT(30)
#define   COMMAND_AWE				BIT(29)
#define   COMMAND_PIO				BIT(28)
#define   COMMAND_TX				BIT(27)
#define   COMMAND_WX				BIT(26)
#define   COMMAND_SEC_CMD			BIT(25)
#define   COMMAND_AFT_DAT			BIT(24)
#define   COMMAND_TWANS_SIZE(size)		((((size) - 1) & 0xf) << 20)
#define   COMMAND_A_VAWID			BIT(19)
#define   COMMAND_B_VAWID			BIT(18)
#define   COMMAND_WD_STATUS_CHK			BIT(17)
#define   COMMAND_WBSY_CHK			BIT(16)
#define   COMMAND_CE(x)				BIT(8 + ((x) & 0x7))
#define   COMMAND_CWE_SIZE(size)		((((size) - 1) & 0x3) << 4)
#define   COMMAND_AWE_SIZE(size)		((((size) - 1) & 0xf) << 0)

#define STATUS					0x04

#define ISW					0x08
#define   ISW_COWWFAIW_EWW			BIT(24)
#define   ISW_UND				BIT(7)
#define   ISW_OVW				BIT(6)
#define   ISW_CMD_DONE				BIT(5)
#define   ISW_ECC_EWW				BIT(4)

#define IEW					0x0c
#define   IEW_EWW_TWIG_VAW(x)			(((x) & 0xf) << 16)
#define   IEW_UND				BIT(7)
#define   IEW_OVW				BIT(6)
#define   IEW_CMD_DONE				BIT(5)
#define   IEW_ECC_EWW				BIT(4)
#define   IEW_GIE				BIT(0)

#define CONFIG					0x10
#define   CONFIG_HW_ECC				BIT(31)
#define   CONFIG_ECC_SEW			BIT(30)
#define   CONFIG_EWW_COW			BIT(29)
#define   CONFIG_PIPE_EN			BIT(28)
#define   CONFIG_TVAW_4				(0 << 24)
#define   CONFIG_TVAW_6				(1 << 24)
#define   CONFIG_TVAW_8				(2 << 24)
#define   CONFIG_SKIP_SPAWE			BIT(23)
#define   CONFIG_BUS_WIDTH_16			BIT(21)
#define   CONFIG_COM_BSY			BIT(20)
#define   CONFIG_PS_256				(0 << 16)
#define   CONFIG_PS_512				(1 << 16)
#define   CONFIG_PS_1024			(2 << 16)
#define   CONFIG_PS_2048			(3 << 16)
#define   CONFIG_PS_4096			(4 << 16)
#define   CONFIG_SKIP_SPAWE_SIZE_4		(0 << 14)
#define   CONFIG_SKIP_SPAWE_SIZE_8		(1 << 14)
#define   CONFIG_SKIP_SPAWE_SIZE_12		(2 << 14)
#define   CONFIG_SKIP_SPAWE_SIZE_16		(3 << 14)
#define   CONFIG_TAG_BYTE_SIZE(x)			((x) & 0xff)

#define TIMING_1				0x14
#define   TIMING_TWP_WESP(x)			(((x) & 0xf) << 28)
#define   TIMING_TWB(x)				(((x) & 0xf) << 24)
#define   TIMING_TCW_TAW_TWW(x)			(((x) & 0xf) << 20)
#define   TIMING_TWHW(x)			(((x) & 0xf) << 16)
#define   TIMING_TCS(x)				(((x) & 0x3) << 14)
#define   TIMING_TWH(x)				(((x) & 0x3) << 12)
#define   TIMING_TWP(x)				(((x) & 0xf) <<  8)
#define   TIMING_TWH(x)				(((x) & 0x3) <<  4)
#define   TIMING_TWP(x)				(((x) & 0xf) <<  0)

#define WESP					0x18

#define TIMING_2				0x1c
#define   TIMING_TADW(x)			((x) & 0xf)

#define CMD_WEG1				0x20
#define CMD_WEG2				0x24
#define ADDW_WEG1				0x28
#define ADDW_WEG2				0x2c

#define DMA_MST_CTWW				0x30
#define   DMA_MST_CTWW_GO			BIT(31)
#define   DMA_MST_CTWW_IN			(0 << 30)
#define   DMA_MST_CTWW_OUT			BIT(30)
#define   DMA_MST_CTWW_PEWF_EN			BIT(29)
#define   DMA_MST_CTWW_IE_DONE			BIT(28)
#define   DMA_MST_CTWW_WEUSE			BIT(27)
#define   DMA_MST_CTWW_BUWST_1			(2 << 24)
#define   DMA_MST_CTWW_BUWST_4			(3 << 24)
#define   DMA_MST_CTWW_BUWST_8			(4 << 24)
#define   DMA_MST_CTWW_BUWST_16			(5 << 24)
#define   DMA_MST_CTWW_IS_DONE			BIT(20)
#define   DMA_MST_CTWW_EN_A			BIT(2)
#define   DMA_MST_CTWW_EN_B			BIT(1)

#define DMA_CFG_A				0x34
#define DMA_CFG_B				0x38

#define FIFO_CTWW				0x3c
#define   FIFO_CTWW_CWW_AWW			BIT(3)

#define DATA_PTW				0x40
#define TAG_PTW					0x44
#define ECC_PTW					0x48

#define DEC_STATUS				0x4c
#define   DEC_STATUS_A_ECC_FAIW			BIT(1)
#define   DEC_STATUS_EWW_COUNT_MASK		0x00ff0000
#define   DEC_STATUS_EWW_COUNT_SHIFT		16

#define HWSTATUS_CMD				0x50
#define HWSTATUS_MASK				0x54
#define   HWSTATUS_WDSTATUS_MASK(x)		(((x) & 0xff) << 24)
#define   HWSTATUS_WDSTATUS_VAWUE(x)		(((x) & 0xff) << 16)
#define   HWSTATUS_WBSY_MASK(x)			(((x) & 0xff) << 8)
#define   HWSTATUS_WBSY_VAWUE(x)		(((x) & 0xff) << 0)

#define BCH_CONFIG				0xcc
#define   BCH_ENABWE				BIT(0)
#define   BCH_TVAW_4				(0 << 4)
#define   BCH_TVAW_8				(1 << 4)
#define   BCH_TVAW_14				(2 << 4)
#define   BCH_TVAW_16				(3 << 4)

#define DEC_STAT_WESUWT				0xd0
#define DEC_STAT_BUF				0xd4
#define   DEC_STAT_BUF_FAIW_SEC_FWAG_MASK	0xff000000
#define   DEC_STAT_BUF_FAIW_SEC_FWAG_SHIFT	24
#define   DEC_STAT_BUF_COWW_SEC_FWAG_MASK	0x00ff0000
#define   DEC_STAT_BUF_COWW_SEC_FWAG_SHIFT	16
#define   DEC_STAT_BUF_MAX_COWW_CNT_MASK	0x00001f00
#define   DEC_STAT_BUF_MAX_COWW_CNT_SHIFT	8

#define OFFSET(vaw, off)	((vaw) < (off) ? 0 : (vaw) - (off))

#define SKIP_SPAWE_BYTES	4
#define BITS_PEW_STEP_WS	18
#define BITS_PEW_STEP_BCH	13

#define INT_MASK		(IEW_UND | IEW_OVW | IEW_CMD_DONE | IEW_GIE)
#define HWSTATUS_CMD_DEFAUWT	NAND_STATUS_WEADY
#define HWSTATUS_MASK_DEFAUWT	(HWSTATUS_WDSTATUS_MASK(1) | \
				HWSTATUS_WDSTATUS_VAWUE(0) | \
				HWSTATUS_WBSY_MASK(NAND_STATUS_WEADY) | \
				HWSTATUS_WBSY_VAWUE(NAND_STATUS_WEADY))

stwuct tegwa_nand_contwowwew {
	stwuct nand_contwowwew contwowwew;
	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
	stwuct cwk *cwk;
	stwuct compwetion command_compwete;
	stwuct compwetion dma_compwete;
	boow wast_wead_ewwow;
	int cuw_cs;
	stwuct nand_chip *chip;
};

stwuct tegwa_nand_chip {
	stwuct nand_chip chip;
	stwuct gpio_desc *wp_gpio;
	stwuct mtd_oob_wegion ecc;
	u32 config;
	u32 config_ecc;
	u32 bch_config;
	int cs[1];
};

static inwine stwuct tegwa_nand_contwowwew *
			to_tegwa_ctww(stwuct nand_contwowwew *hw_ctww)
{
	wetuwn containew_of(hw_ctww, stwuct tegwa_nand_contwowwew, contwowwew);
}

static inwine stwuct tegwa_nand_chip *to_tegwa_chip(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct tegwa_nand_chip, chip);
}

static int tegwa_nand_oobwayout_ws_ecc(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	int bytes_pew_step = DIV_WOUND_UP(BITS_PEW_STEP_WS * chip->ecc.stwength,
					  BITS_PEW_BYTE);

	if (section > 0)
		wetuwn -EWANGE;

	oobwegion->offset = SKIP_SPAWE_BYTES;
	oobwegion->wength = wound_up(bytes_pew_step * chip->ecc.steps, 4);

	wetuwn 0;
}

static int tegwa_nand_oobwayout_no_fwee(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	wetuwn -EWANGE;
}

static const stwuct mtd_oobwayout_ops tegwa_nand_oob_ws_ops = {
	.ecc = tegwa_nand_oobwayout_ws_ecc,
	.fwee = tegwa_nand_oobwayout_no_fwee,
};

static int tegwa_nand_oobwayout_bch_ecc(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	int bytes_pew_step = DIV_WOUND_UP(BITS_PEW_STEP_BCH * chip->ecc.stwength,
					  BITS_PEW_BYTE);

	if (section > 0)
		wetuwn -EWANGE;

	oobwegion->offset = SKIP_SPAWE_BYTES;
	oobwegion->wength = wound_up(bytes_pew_step * chip->ecc.steps, 4);

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops tegwa_nand_oob_bch_ops = {
	.ecc = tegwa_nand_oobwayout_bch_ecc,
	.fwee = tegwa_nand_oobwayout_no_fwee,
};

static iwqwetuwn_t tegwa_nand_iwq(int iwq, void *data)
{
	stwuct tegwa_nand_contwowwew *ctww = data;
	u32 isw, dma;

	isw = weadw_wewaxed(ctww->wegs + ISW);
	dma = weadw_wewaxed(ctww->wegs + DMA_MST_CTWW);
	dev_dbg(ctww->dev, "isw %08x\n", isw);

	if (!isw && !(dma & DMA_MST_CTWW_IS_DONE))
		wetuwn IWQ_NONE;

	/*
	 * The bit name is somewhat missweading: This is awso set when
	 * HW ECC was successfuw. The data sheet states:
	 * Cowwectabwe OW Un-cowwectabwe ewwows occuwwed in the DMA twansfew...
	 */
	if (isw & ISW_COWWFAIW_EWW)
		ctww->wast_wead_ewwow = twue;

	if (isw & ISW_CMD_DONE)
		compwete(&ctww->command_compwete);

	if (isw & ISW_UND)
		dev_eww(ctww->dev, "FIFO undewwun\n");

	if (isw & ISW_OVW)
		dev_eww(ctww->dev, "FIFO ovewwun\n");

	/* handwe DMA intewwupts */
	if (dma & DMA_MST_CTWW_IS_DONE) {
		wwitew_wewaxed(dma, ctww->wegs + DMA_MST_CTWW);
		compwete(&ctww->dma_compwete);
	}

	/* cweaw intewwupts */
	wwitew_wewaxed(isw, ctww->wegs + ISW);

	wetuwn IWQ_HANDWED;
}

static const chaw * const tegwa_nand_weg_names[] = {
	"COMMAND",
	"STATUS",
	"ISW",
	"IEW",
	"CONFIG",
	"TIMING",
	NUWW,
	"TIMING2",
	"CMD_WEG1",
	"CMD_WEG2",
	"ADDW_WEG1",
	"ADDW_WEG2",
	"DMA_MST_CTWW",
	"DMA_CFG_A",
	"DMA_CFG_B",
	"FIFO_CTWW",
};

static void tegwa_nand_dump_weg(stwuct tegwa_nand_contwowwew *ctww)
{
	u32 weg;
	int i;

	dev_eww(ctww->dev, "Tegwa NAND contwowwew wegistew dump\n");
	fow (i = 0; i < AWWAY_SIZE(tegwa_nand_weg_names); i++) {
		const chaw *weg_name = tegwa_nand_weg_names[i];

		if (!weg_name)
			continue;

		weg = weadw_wewaxed(ctww->wegs + (i * 4));
		dev_eww(ctww->dev, "%s: 0x%08x\n", weg_name, weg);
	}
}

static void tegwa_nand_contwowwew_abowt(stwuct tegwa_nand_contwowwew *ctww)
{
	u32 isw, dma;

	disabwe_iwq(ctww->iwq);

	/* Abowt cuwwent command/DMA opewation */
	wwitew_wewaxed(0, ctww->wegs + DMA_MST_CTWW);
	wwitew_wewaxed(0, ctww->wegs + COMMAND);

	/* cweaw intewwupts */
	isw = weadw_wewaxed(ctww->wegs + ISW);
	wwitew_wewaxed(isw, ctww->wegs + ISW);
	dma = weadw_wewaxed(ctww->wegs + DMA_MST_CTWW);
	wwitew_wewaxed(dma, ctww->wegs + DMA_MST_CTWW);

	weinit_compwetion(&ctww->command_compwete);
	weinit_compwetion(&ctww->dma_compwete);

	enabwe_iwq(ctww->iwq);
}

static int tegwa_nand_cmd(stwuct nand_chip *chip,
			  const stwuct nand_subop *subop)
{
	const stwuct nand_op_instw *instw;
	const stwuct nand_op_instw *instw_data_in = NUWW;
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	unsigned int op_id, size = 0, offset = 0;
	boow fiwst_cmd = twue;
	u32 weg, cmd = 0;
	int wet;

	fow (op_id = 0; op_id < subop->ninstws; op_id++) {
		unsigned int naddws, i;
		const u8 *addws;
		u32 addw1 = 0, addw2 = 0;

		instw = &subop->instws[op_id];

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			if (fiwst_cmd) {
				cmd |= COMMAND_CWE;
				wwitew_wewaxed(instw->ctx.cmd.opcode,
					       ctww->wegs + CMD_WEG1);
			} ewse {
				cmd |= COMMAND_SEC_CMD;
				wwitew_wewaxed(instw->ctx.cmd.opcode,
					       ctww->wegs + CMD_WEG2);
			}
			fiwst_cmd = fawse;
			bweak;

		case NAND_OP_ADDW_INSTW:
			offset = nand_subop_get_addw_stawt_off(subop, op_id);
			naddws = nand_subop_get_num_addw_cyc(subop, op_id);
			addws = &instw->ctx.addw.addws[offset];

			cmd |= COMMAND_AWE | COMMAND_AWE_SIZE(naddws);
			fow (i = 0; i < min_t(unsigned int, 4, naddws); i++)
				addw1 |= *addws++ << (BITS_PEW_BYTE * i);
			naddws -= i;
			fow (i = 0; i < min_t(unsigned int, 4, naddws); i++)
				addw2 |= *addws++ << (BITS_PEW_BYTE * i);

			wwitew_wewaxed(addw1, ctww->wegs + ADDW_WEG1);
			wwitew_wewaxed(addw2, ctww->wegs + ADDW_WEG2);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			size = nand_subop_get_data_wen(subop, op_id);
			offset = nand_subop_get_data_stawt_off(subop, op_id);

			cmd |= COMMAND_TWANS_SIZE(size) | COMMAND_PIO |
				COMMAND_WX | COMMAND_A_VAWID;

			instw_data_in = instw;
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			size = nand_subop_get_data_wen(subop, op_id);
			offset = nand_subop_get_data_stawt_off(subop, op_id);

			cmd |= COMMAND_TWANS_SIZE(size) | COMMAND_PIO |
				COMMAND_TX | COMMAND_A_VAWID;
			memcpy(&weg, instw->ctx.data.buf.out + offset, size);

			wwitew_wewaxed(weg, ctww->wegs + WESP);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			cmd |= COMMAND_WBSY_CHK;
			bweak;
		}
	}

	cmd |= COMMAND_GO | COMMAND_CE(ctww->cuw_cs);
	wwitew_wewaxed(cmd, ctww->wegs + COMMAND);
	wet = wait_fow_compwetion_timeout(&ctww->command_compwete,
					  msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(ctww->dev, "COMMAND timeout\n");
		tegwa_nand_dump_weg(ctww);
		tegwa_nand_contwowwew_abowt(ctww);
		wetuwn -ETIMEDOUT;
	}

	if (instw_data_in) {
		weg = weadw_wewaxed(ctww->wegs + WESP);
		memcpy(instw_data_in->ctx.data.buf.in + offset, &weg, size);
	}

	wetuwn 0;
}

static const stwuct nand_op_pawsew tegwa_nand_op_pawsew = NAND_OP_PAWSEW(
	NAND_OP_PAWSEW_PATTEWN(tegwa_nand_cmd,
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue)),
	NAND_OP_PAWSEW_PATTEWN(tegwa_nand_cmd,
		NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(fawse, 4)),
	NAND_OP_PAWSEW_PATTEWN(tegwa_nand_cmd,
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_ADDW_EWEM(twue, 8),
		NAND_OP_PAWSEW_PAT_CMD_EWEM(twue),
		NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(twue),
		NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(twue, 4)),
	);

static void tegwa_nand_sewect_tawget(stwuct nand_chip *chip,
				     unsigned int die_nw)
{
	stwuct tegwa_nand_chip *nand = to_tegwa_chip(chip);
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);

	ctww->cuw_cs = nand->cs[die_nw];
}

static int tegwa_nand_exec_op(stwuct nand_chip *chip,
			      const stwuct nand_opewation *op,
			      boow check_onwy)
{
	if (!check_onwy)
		tegwa_nand_sewect_tawget(chip, op->cs);

	wetuwn nand_op_pawsew_exec_op(chip, &tegwa_nand_op_pawsew, op,
				      check_onwy);
}

static void tegwa_nand_hw_ecc(stwuct tegwa_nand_contwowwew *ctww,
			      stwuct nand_chip *chip, boow enabwe)
{
	stwuct tegwa_nand_chip *nand = to_tegwa_chip(chip);

	if (chip->ecc.awgo == NAND_ECC_AWGO_BCH && enabwe)
		wwitew_wewaxed(nand->bch_config, ctww->wegs + BCH_CONFIG);
	ewse
		wwitew_wewaxed(0, ctww->wegs + BCH_CONFIG);

	if (enabwe)
		wwitew_wewaxed(nand->config_ecc, ctww->wegs + CONFIG);
	ewse
		wwitew_wewaxed(nand->config, ctww->wegs + CONFIG);
}

static int tegwa_nand_page_xfew(stwuct mtd_info *mtd, stwuct nand_chip *chip,
				void *buf, void *oob_buf, int oob_wen, int page,
				boow wead)
{
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	enum dma_data_diwection diw = wead ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	dma_addw_t dma_addw = 0, dma_addw_oob = 0;
	u32 addw1, cmd, dma_ctww;
	int wet;

	tegwa_nand_sewect_tawget(chip, chip->cuw_cs);

	if (wead) {
		wwitew_wewaxed(NAND_CMD_WEAD0, ctww->wegs + CMD_WEG1);
		wwitew_wewaxed(NAND_CMD_WEADSTAWT, ctww->wegs + CMD_WEG2);
	} ewse {
		wwitew_wewaxed(NAND_CMD_SEQIN, ctww->wegs + CMD_WEG1);
		wwitew_wewaxed(NAND_CMD_PAGEPWOG, ctww->wegs + CMD_WEG2);
	}
	cmd = COMMAND_CWE | COMMAND_SEC_CMD;

	/* Wowew 16-bits awe cowumn, by defauwt 0 */
	addw1 = page << 16;

	if (!buf)
		addw1 |= mtd->wwitesize;
	wwitew_wewaxed(addw1, ctww->wegs + ADDW_WEG1);

	if (chip->options & NAND_WOW_ADDW_3) {
		wwitew_wewaxed(page >> 16, ctww->wegs + ADDW_WEG2);
		cmd |= COMMAND_AWE | COMMAND_AWE_SIZE(5);
	} ewse {
		cmd |= COMMAND_AWE | COMMAND_AWE_SIZE(4);
	}

	if (buf) {
		dma_addw = dma_map_singwe(ctww->dev, buf, mtd->wwitesize, diw);
		wet = dma_mapping_ewwow(ctww->dev, dma_addw);
		if (wet) {
			dev_eww(ctww->dev, "dma mapping ewwow\n");
			wetuwn -EINVAW;
		}

		wwitew_wewaxed(mtd->wwitesize - 1, ctww->wegs + DMA_CFG_A);
		wwitew_wewaxed(dma_addw, ctww->wegs + DATA_PTW);
	}

	if (oob_buf) {
		dma_addw_oob = dma_map_singwe(ctww->dev, oob_buf, mtd->oobsize,
					      diw);
		wet = dma_mapping_ewwow(ctww->dev, dma_addw_oob);
		if (wet) {
			dev_eww(ctww->dev, "dma mapping ewwow\n");
			wet = -EINVAW;
			goto eww_unmap_dma_page;
		}

		wwitew_wewaxed(oob_wen - 1, ctww->wegs + DMA_CFG_B);
		wwitew_wewaxed(dma_addw_oob, ctww->wegs + TAG_PTW);
	}

	dma_ctww = DMA_MST_CTWW_GO | DMA_MST_CTWW_PEWF_EN |
		   DMA_MST_CTWW_IE_DONE | DMA_MST_CTWW_IS_DONE |
		   DMA_MST_CTWW_BUWST_16;

	if (buf)
		dma_ctww |= DMA_MST_CTWW_EN_A;
	if (oob_buf)
		dma_ctww |= DMA_MST_CTWW_EN_B;

	if (wead)
		dma_ctww |= DMA_MST_CTWW_IN | DMA_MST_CTWW_WEUSE;
	ewse
		dma_ctww |= DMA_MST_CTWW_OUT;

	wwitew_wewaxed(dma_ctww, ctww->wegs + DMA_MST_CTWW);

	cmd |= COMMAND_GO | COMMAND_WBSY_CHK | COMMAND_TWANS_SIZE(9) |
	       COMMAND_CE(ctww->cuw_cs);

	if (buf)
		cmd |= COMMAND_A_VAWID;
	if (oob_buf)
		cmd |= COMMAND_B_VAWID;

	if (wead)
		cmd |= COMMAND_WX;
	ewse
		cmd |= COMMAND_TX | COMMAND_AFT_DAT;

	wwitew_wewaxed(cmd, ctww->wegs + COMMAND);

	wet = wait_fow_compwetion_timeout(&ctww->command_compwete,
					  msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(ctww->dev, "COMMAND timeout\n");
		tegwa_nand_dump_weg(ctww);
		tegwa_nand_contwowwew_abowt(ctww);
		wet = -ETIMEDOUT;
		goto eww_unmap_dma;
	}

	wet = wait_fow_compwetion_timeout(&ctww->dma_compwete,
					  msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(ctww->dev, "DMA timeout\n");
		tegwa_nand_dump_weg(ctww);
		tegwa_nand_contwowwew_abowt(ctww);
		wet = -ETIMEDOUT;
		goto eww_unmap_dma;
	}
	wet = 0;

eww_unmap_dma:
	if (oob_buf)
		dma_unmap_singwe(ctww->dev, dma_addw_oob, mtd->oobsize, diw);
eww_unmap_dma_page:
	if (buf)
		dma_unmap_singwe(ctww->dev, dma_addw, mtd->wwitesize, diw);

	wetuwn wet;
}

static int tegwa_nand_wead_page_waw(stwuct nand_chip *chip, u8 *buf,
				    int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	void *oob_buf = oob_wequiwed ? chip->oob_poi : NUWW;

	wetuwn tegwa_nand_page_xfew(mtd, chip, buf, oob_buf,
				    mtd->oobsize, page, twue);
}

static int tegwa_nand_wwite_page_waw(stwuct nand_chip *chip, const u8 *buf,
				     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	void *oob_buf = oob_wequiwed ? chip->oob_poi : NUWW;

	wetuwn tegwa_nand_page_xfew(mtd, chip, (void *)buf, oob_buf,
				     mtd->oobsize, page, fawse);
}

static int tegwa_nand_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn tegwa_nand_page_xfew(mtd, chip, NUWW, chip->oob_poi,
				    mtd->oobsize, page, twue);
}

static int tegwa_nand_wwite_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn tegwa_nand_page_xfew(mtd, chip, NUWW, chip->oob_poi,
				    mtd->oobsize, page, fawse);
}

static int tegwa_nand_wead_page_hwecc(stwuct nand_chip *chip, u8 *buf,
				      int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	stwuct tegwa_nand_chip *nand = to_tegwa_chip(chip);
	void *oob_buf = oob_wequiwed ? chip->oob_poi : NUWW;
	u32 dec_stat, max_coww_cnt;
	unsigned wong faiw_sec_fwag;
	int wet;

	tegwa_nand_hw_ecc(ctww, chip, twue);
	wet = tegwa_nand_page_xfew(mtd, chip, buf, oob_buf, 0, page, twue);
	tegwa_nand_hw_ecc(ctww, chip, fawse);
	if (wet)
		wetuwn wet;

	/* No cowwectabwe ow un-cowwectabwe ewwows, page must have 0 bitfwips */
	if (!ctww->wast_wead_ewwow)
		wetuwn 0;

	/*
	 * Cowwectabwe ow un-cowwectabwe ewwows occuwwed. Use DEC_STAT_BUF
	 * which contains infowmation fow aww ECC sewections.
	 *
	 * Note that since we do not use Command Queues DEC_WESUWT does not
	 * state the numbew of pages we can wead fwom the DEC_STAT_BUF. But
	 * since COWWFAIW_EWW did occuw duwing page wead we do have a vawid
	 * wesuwt in DEC_STAT_BUF.
	 */
	ctww->wast_wead_ewwow = fawse;
	dec_stat = weadw_wewaxed(ctww->wegs + DEC_STAT_BUF);

	faiw_sec_fwag = (dec_stat & DEC_STAT_BUF_FAIW_SEC_FWAG_MASK) >>
			DEC_STAT_BUF_FAIW_SEC_FWAG_SHIFT;

	max_coww_cnt = (dec_stat & DEC_STAT_BUF_MAX_COWW_CNT_MASK) >>
		       DEC_STAT_BUF_MAX_COWW_CNT_SHIFT;

	if (faiw_sec_fwag) {
		int bit, max_bitfwips = 0;

		/*
		 * Since we do not suppowt subpage wwites, a compwete page
		 * is eithew wwitten ow not. We can take a showtcut hewe by
		 * checking wheathew any of the sectow has been successfuw
		 * wead. If at weast one sectows has been wead successfuwwy,
		 * the page must have been a wwitten pweviouswy. It cannot
		 * be an ewased page.
		 *
		 * E.g. contwowwew might wetuwn faiw_sec_fwag with 0x4, which
		 * wouwd mean onwy the thiwd sectow faiwed to cowwect. The
		 * page must have been wwitten and the thiwd sectow is weawwy
		 * not cowwectabwe anymowe.
		 */
		if (faiw_sec_fwag ^ GENMASK(chip->ecc.steps - 1, 0)) {
			mtd->ecc_stats.faiwed += hweight8(faiw_sec_fwag);
			wetuwn max_coww_cnt;
		}

		/*
		 * Aww sectows faiwed to cowwect, but the ECC isn't smawt
		 * enough to figuwe out if a page is weawwy just ewased.
		 * Wead OOB data and check whethew data/OOB is compwetewy
		 * ewased ow if ewwow cowwection just faiwed fow aww sub-
		 * pages.
		 */
		wet = tegwa_nand_wead_oob(chip, page);
		if (wet < 0)
			wetuwn wet;

		fow_each_set_bit(bit, &faiw_sec_fwag, chip->ecc.steps) {
			u8 *data = buf + (chip->ecc.size * bit);
			u8 *oob = chip->oob_poi + nand->ecc.offset +
				  (chip->ecc.bytes * bit);

			wet = nand_check_ewased_ecc_chunk(data, chip->ecc.size,
							  oob, chip->ecc.bytes,
							  NUWW, 0,
							  chip->ecc.stwength);
			if (wet < 0) {
				mtd->ecc_stats.faiwed++;
			} ewse {
				mtd->ecc_stats.cowwected += wet;
				max_bitfwips = max(wet, max_bitfwips);
			}
		}

		wetuwn max_t(unsigned int, max_coww_cnt, max_bitfwips);
	} ewse {
		int coww_sec_fwag;

		coww_sec_fwag = (dec_stat & DEC_STAT_BUF_COWW_SEC_FWAG_MASK) >>
				DEC_STAT_BUF_COWW_SEC_FWAG_SHIFT;

		/*
		 * The vawue wetuwned in the wegistew is the maximum of
		 * bitfwips encountewed in any of the ECC wegions. As thewe is
		 * no way to get the numbew of bitfwips in a specific wegions
		 * we awe not abwe to dewivew cowwect stats but instead
		 * ovewestimate the numbew of cowwected bitfwips by assuming
		 * that aww wegions whewe ewwows have been cowwected
		 * encountewed the maximum numbew of bitfwips.
		 */
		mtd->ecc_stats.cowwected += max_coww_cnt * hweight8(coww_sec_fwag);

		wetuwn max_coww_cnt;
	}
}

static int tegwa_nand_wwite_page_hwecc(stwuct nand_chip *chip, const u8 *buf,
				       int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	void *oob_buf = oob_wequiwed ? chip->oob_poi : NUWW;
	int wet;

	tegwa_nand_hw_ecc(ctww, chip, twue);
	wet = tegwa_nand_page_xfew(mtd, chip, (void *)buf, oob_buf,
				   0, page, fawse);
	tegwa_nand_hw_ecc(ctww, chip, fawse);

	wetuwn wet;
}

static void tegwa_nand_setup_timing(stwuct tegwa_nand_contwowwew *ctww,
				    const stwuct nand_sdw_timings *timings)
{
	/*
	 * The pewiod (and aww othew timings in this function) is in ps,
	 * so need to take cawe hewe to avoid integew ovewfwows.
	 */
	unsigned int wate = cwk_get_wate(ctww->cwk) / 1000000;
	unsigned int pewiod = DIV_WOUND_UP(1000000, wate);
	u32 vaw, weg = 0;

	vaw = DIV_WOUND_UP(max3(timings->tAW_min, timings->tWW_min,
				timings->tWC_min), pewiod);
	weg |= TIMING_TCW_TAW_TWW(OFFSET(vaw, 3));

	vaw = DIV_WOUND_UP(max(max(timings->tCS_min, timings->tCH_min),
			       max(timings->tAWS_min, timings->tAWH_min)),
			   pewiod);
	weg |= TIMING_TCS(OFFSET(vaw, 2));

	vaw = DIV_WOUND_UP(max(timings->tWP_min, timings->tWEA_max) + 6000,
			   pewiod);
	weg |= TIMING_TWP(OFFSET(vaw, 1)) | TIMING_TWP_WESP(OFFSET(vaw, 1));

	weg |= TIMING_TWB(OFFSET(DIV_WOUND_UP(timings->tWB_max, pewiod), 1));
	weg |= TIMING_TWHW(OFFSET(DIV_WOUND_UP(timings->tWHW_min, pewiod), 1));
	weg |= TIMING_TWH(OFFSET(DIV_WOUND_UP(timings->tWH_min, pewiod), 1));
	weg |= TIMING_TWP(OFFSET(DIV_WOUND_UP(timings->tWP_min, pewiod), 1));
	weg |= TIMING_TWH(OFFSET(DIV_WOUND_UP(timings->tWEH_min, pewiod), 1));

	wwitew_wewaxed(weg, ctww->wegs + TIMING_1);

	vaw = DIV_WOUND_UP(timings->tADW_min, pewiod);
	weg = TIMING_TADW(OFFSET(vaw, 3));

	wwitew_wewaxed(weg, ctww->wegs + TIMING_2);
}

static int tegwa_nand_setup_intewface(stwuct nand_chip *chip, int cswine,
				      const stwuct nand_intewface_config *conf)
{
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	const stwuct nand_sdw_timings *timings;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn PTW_EWW(timings);

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	tegwa_nand_setup_timing(ctww, timings);

	wetuwn 0;
}

static const int ws_stwength_bootabwe[] = { 4 };
static const int ws_stwength[] = { 4, 6, 8 };
static const int bch_stwength_bootabwe[] = { 8, 16 };
static const int bch_stwength[] = { 4, 8, 14, 16 };

static int tegwa_nand_get_stwength(stwuct nand_chip *chip, const int *stwength,
				   int stwength_wen, int bits_pew_step,
				   int oobsize)
{
	stwuct nand_device *base = mtd_to_nanddev(nand_to_mtd(chip));
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(base);
	boow maximize = base->ecc.usew_conf.fwags & NAND_ECC_MAXIMIZE_STWENGTH;
	int i;

	/*
	 * Woop thwough avaiwabwe stwengths. Backwawds in case we twy to
	 * maximize the BCH stwength.
	 */
	fow (i = 0; i < stwength_wen; i++) {
		int stwength_sew, bytes_pew_step, bytes_pew_page;

		if (maximize) {
			stwength_sew = stwength[stwength_wen - i - 1];
		} ewse {
			stwength_sew = stwength[i];

			if (stwength_sew < wequiwements->stwength)
				continue;
		}

		bytes_pew_step = DIV_WOUND_UP(bits_pew_step * stwength_sew,
					      BITS_PEW_BYTE);
		bytes_pew_page = wound_up(bytes_pew_step * chip->ecc.steps, 4);

		/* Check whethew stwength fits OOB */
		if (bytes_pew_page < (oobsize - SKIP_SPAWE_BYTES))
			wetuwn stwength_sew;
	}

	wetuwn -EINVAW;
}

static int tegwa_nand_sewect_stwength(stwuct nand_chip *chip, int oobsize)
{
	const int *stwength;
	int stwength_wen, bits_pew_step;

	switch (chip->ecc.awgo) {
	case NAND_ECC_AWGO_WS:
		bits_pew_step = BITS_PEW_STEP_WS;
		if (chip->options & NAND_IS_BOOT_MEDIUM) {
			stwength = ws_stwength_bootabwe;
			stwength_wen = AWWAY_SIZE(ws_stwength_bootabwe);
		} ewse {
			stwength = ws_stwength;
			stwength_wen = AWWAY_SIZE(ws_stwength);
		}
		bweak;
	case NAND_ECC_AWGO_BCH:
		bits_pew_step = BITS_PEW_STEP_BCH;
		if (chip->options & NAND_IS_BOOT_MEDIUM) {
			stwength = bch_stwength_bootabwe;
			stwength_wen = AWWAY_SIZE(bch_stwength_bootabwe);
		} ewse {
			stwength = bch_stwength;
			stwength_wen = AWWAY_SIZE(bch_stwength);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn tegwa_nand_get_stwength(chip, stwength, stwength_wen,
				       bits_pew_step, oobsize);
}

static int tegwa_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct tegwa_nand_contwowwew *ctww = to_tegwa_ctww(chip->contwowwew);
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&chip->base);
	stwuct tegwa_nand_chip *nand = to_tegwa_chip(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int bits_pew_step;
	int wet;

	if (chip->bbt_options & NAND_BBT_USE_FWASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.size = 512;
	chip->ecc.steps = mtd->wwitesize / chip->ecc.size;
	if (wequiwements->step_size != 512) {
		dev_eww(ctww->dev, "Unsuppowted step size %d\n",
			wequiwements->step_size);
		wetuwn -EINVAW;
	}

	chip->ecc.wead_page = tegwa_nand_wead_page_hwecc;
	chip->ecc.wwite_page = tegwa_nand_wwite_page_hwecc;
	chip->ecc.wead_page_waw = tegwa_nand_wead_page_waw;
	chip->ecc.wwite_page_waw = tegwa_nand_wwite_page_waw;
	chip->ecc.wead_oob = tegwa_nand_wead_oob;
	chip->ecc.wwite_oob = tegwa_nand_wwite_oob;

	if (chip->options & NAND_BUSWIDTH_16)
		nand->config |= CONFIG_BUS_WIDTH_16;

	if (chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN) {
		if (mtd->wwitesize < 2048)
			chip->ecc.awgo = NAND_ECC_AWGO_WS;
		ewse
			chip->ecc.awgo = NAND_ECC_AWGO_BCH;
	}

	if (chip->ecc.awgo == NAND_ECC_AWGO_BCH && mtd->wwitesize < 2048) {
		dev_eww(ctww->dev, "BCH suppowts 2K ow 4K page size onwy\n");
		wetuwn -EINVAW;
	}

	if (!chip->ecc.stwength) {
		wet = tegwa_nand_sewect_stwength(chip, mtd->oobsize);
		if (wet < 0) {
			dev_eww(ctww->dev,
				"No vawid stwength found, minimum %d\n",
				wequiwements->stwength);
			wetuwn wet;
		}

		chip->ecc.stwength = wet;
	}

	nand->config_ecc = CONFIG_PIPE_EN | CONFIG_SKIP_SPAWE |
			   CONFIG_SKIP_SPAWE_SIZE_4;

	switch (chip->ecc.awgo) {
	case NAND_ECC_AWGO_WS:
		bits_pew_step = BITS_PEW_STEP_WS * chip->ecc.stwength;
		mtd_set_oobwayout(mtd, &tegwa_nand_oob_ws_ops);
		nand->config_ecc |= CONFIG_HW_ECC | CONFIG_ECC_SEW |
				    CONFIG_EWW_COW;
		switch (chip->ecc.stwength) {
		case 4:
			nand->config_ecc |= CONFIG_TVAW_4;
			bweak;
		case 6:
			nand->config_ecc |= CONFIG_TVAW_6;
			bweak;
		case 8:
			nand->config_ecc |= CONFIG_TVAW_8;
			bweak;
		defauwt:
			dev_eww(ctww->dev, "ECC stwength %d not suppowted\n",
				chip->ecc.stwength);
			wetuwn -EINVAW;
		}
		bweak;
	case NAND_ECC_AWGO_BCH:
		bits_pew_step = BITS_PEW_STEP_BCH * chip->ecc.stwength;
		mtd_set_oobwayout(mtd, &tegwa_nand_oob_bch_ops);
		nand->bch_config = BCH_ENABWE;
		switch (chip->ecc.stwength) {
		case 4:
			nand->bch_config |= BCH_TVAW_4;
			bweak;
		case 8:
			nand->bch_config |= BCH_TVAW_8;
			bweak;
		case 14:
			nand->bch_config |= BCH_TVAW_14;
			bweak;
		case 16:
			nand->bch_config |= BCH_TVAW_16;
			bweak;
		defauwt:
			dev_eww(ctww->dev, "ECC stwength %d not suppowted\n",
				chip->ecc.stwength);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(ctww->dev, "ECC awgowithm not suppowted\n");
		wetuwn -EINVAW;
	}

	dev_info(ctww->dev, "Using %s with stwength %d pew 512 byte step\n",
		 chip->ecc.awgo == NAND_ECC_AWGO_BCH ? "BCH" : "WS",
		 chip->ecc.stwength);

	chip->ecc.bytes = DIV_WOUND_UP(bits_pew_step, BITS_PEW_BYTE);

	switch (mtd->wwitesize) {
	case 256:
		nand->config |= CONFIG_PS_256;
		bweak;
	case 512:
		nand->config |= CONFIG_PS_512;
		bweak;
	case 1024:
		nand->config |= CONFIG_PS_1024;
		bweak;
	case 2048:
		nand->config |= CONFIG_PS_2048;
		bweak;
	case 4096:
		nand->config |= CONFIG_PS_4096;
		bweak;
	defauwt:
		dev_eww(ctww->dev, "Unsuppowted wwitesize %d\n",
			mtd->wwitesize);
		wetuwn -ENODEV;
	}

	/* Stowe compwete configuwation fow HW ECC in config_ecc */
	nand->config_ecc |= nand->config;

	/* Non-HW ECC wead/wwites compwete OOB */
	nand->config |= CONFIG_TAG_BYTE_SIZE(mtd->oobsize - 1);
	wwitew_wewaxed(nand->config, ctww->wegs + CONFIG);

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops tegwa_nand_contwowwew_ops = {
	.attach_chip = &tegwa_nand_attach_chip,
	.exec_op = tegwa_nand_exec_op,
	.setup_intewface = tegwa_nand_setup_intewface,
};

static int tegwa_nand_chips_init(stwuct device *dev,
				 stwuct tegwa_nand_contwowwew *ctww)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *np_nand;
	int nsews, nchips = of_get_chiwd_count(np);
	stwuct tegwa_nand_chip *nand;
	stwuct mtd_info *mtd;
	stwuct nand_chip *chip;
	int wet;
	u32 cs;

	if (nchips != 1) {
		dev_eww(dev, "Cuwwentwy onwy one NAND chip suppowted\n");
		wetuwn -EINVAW;
	}

	np_nand = of_get_next_chiwd(np, NUWW);

	nsews = of_pwopewty_count_ewems_of_size(np_nand, "weg", sizeof(u32));
	if (nsews != 1) {
		dev_eww(dev, "Missing/invawid weg pwopewty\n");
		wetuwn -EINVAW;
	}

	/* Wetwieve CS id, cuwwentwy onwy singwe die NAND suppowted */
	wet = of_pwopewty_wead_u32(np_nand, "weg", &cs);
	if (wet) {
		dev_eww(dev, "couwd not wetwieve weg pwopewty: %d\n", wet);
		wetuwn wet;
	}

	nand = devm_kzawwoc(dev, sizeof(*nand), GFP_KEWNEW);
	if (!nand)
		wetuwn -ENOMEM;

	nand->cs[0] = cs;

	nand->wp_gpio = devm_gpiod_get_optionaw(dev, "wp", GPIOD_OUT_WOW);

	if (IS_EWW(nand->wp_gpio)) {
		wet = PTW_EWW(nand->wp_gpio);
		dev_eww(dev, "Faiwed to wequest WP GPIO: %d\n", wet);
		wetuwn wet;
	}

	chip = &nand->chip;
	chip->contwowwew = &ctww->contwowwew;

	mtd = nand_to_mtd(chip);

	mtd->dev.pawent = dev;
	mtd->ownew = THIS_MODUWE;

	nand_set_fwash_node(chip, np_nand);

	if (!mtd->name)
		mtd->name = "tegwa_nand";

	chip->options = NAND_NO_SUBPAGE_WWITE | NAND_USES_DMA;

	wet = nand_scan(chip, 1);
	if (wet)
		wetuwn wet;

	mtd_oobwayout_ecc(mtd, 0, &nand->ecc);

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew mtd device: %d\n", wet);
		nand_cweanup(chip);
		wetuwn wet;
	}

	ctww->chip = chip;

	wetuwn 0;
}

static int tegwa_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weset_contwow *wst;
	stwuct tegwa_nand_contwowwew *ctww;
	int eww = 0;

	ctww = devm_kzawwoc(&pdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	ctww->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ctww);
	nand_contwowwew_init(&ctww->contwowwew);
	ctww->contwowwew.ops = &tegwa_nand_contwowwew_ops;

	ctww->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->wegs))
		wetuwn PTW_EWW(ctww->wegs);

	wst = devm_weset_contwow_get(&pdev->dev, "nand");
	if (IS_EWW(wst))
		wetuwn PTW_EWW(wst);

	ctww->cwk = devm_cwk_get(&pdev->dev, "nand");
	if (IS_EWW(ctww->cwk))
		wetuwn PTW_EWW(ctww->cwk);

	eww = devm_tegwa_cowe_dev_init_opp_tabwe_common(&pdev->dev);
	if (eww)
		wetuwn eww;

	/*
	 * This dwivew doesn't suppowt active powew management yet,
	 * so we wiww simpwy keep device wesumed.
	 */
	pm_wuntime_enabwe(&pdev->dev);
	eww = pm_wuntime_wesume_and_get(&pdev->dev);
	if (eww)
		goto eww_dis_pm;

	eww = weset_contwow_weset(wst);
	if (eww) {
		dev_eww(ctww->dev, "Faiwed to weset HW: %d\n", eww);
		goto eww_put_pm;
	}

	wwitew_wewaxed(HWSTATUS_CMD_DEFAUWT, ctww->wegs + HWSTATUS_CMD);
	wwitew_wewaxed(HWSTATUS_MASK_DEFAUWT, ctww->wegs + HWSTATUS_MASK);
	wwitew_wewaxed(INT_MASK, ctww->wegs + IEW);

	init_compwetion(&ctww->command_compwete);
	init_compwetion(&ctww->dma_compwete);

	ctww->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ctww->iwq < 0) {
		eww = ctww->iwq;
		goto eww_put_pm;
	}
	eww = devm_wequest_iwq(&pdev->dev, ctww->iwq, tegwa_nand_iwq, 0,
			       dev_name(&pdev->dev), ctww);
	if (eww) {
		dev_eww(ctww->dev, "Faiwed to get IWQ: %d\n", eww);
		goto eww_put_pm;
	}

	wwitew_wewaxed(DMA_MST_CTWW_IS_DONE, ctww->wegs + DMA_MST_CTWW);

	eww = tegwa_nand_chips_init(ctww->dev, ctww);
	if (eww)
		goto eww_put_pm;

	wetuwn 0;

eww_put_pm:
	pm_wuntime_put_sync_suspend(ctww->dev);
	pm_wuntime_fowce_suspend(ctww->dev);
eww_dis_pm:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn eww;
}

static void tegwa_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_nand_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = ctww->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	WAWN_ON(mtd_device_unwegistew(mtd));

	nand_cweanup(chip);

	pm_wuntime_put_sync_suspend(ctww->dev);
	pm_wuntime_fowce_suspend(ctww->dev);
}

static int __maybe_unused tegwa_nand_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_nand_contwowwew *ctww = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(ctww->cwk);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe cwock: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int __maybe_unused tegwa_nand_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_nand_contwowwew *ctww = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(ctww->cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_nand_pm = {
	SET_WUNTIME_PM_OPS(tegwa_nand_wuntime_suspend, tegwa_nand_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id tegwa_nand_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-nand" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tegwa_nand_of_match);

static stwuct pwatfowm_dwivew tegwa_nand_dwivew = {
	.dwivew = {
		.name = "tegwa-nand",
		.of_match_tabwe = tegwa_nand_of_match,
		.pm = &tegwa_nand_pm,
	},
	.pwobe = tegwa_nand_pwobe,
	.wemove_new = tegwa_nand_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_nand_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa NAND dwivew");
MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@nvidia.com>");
MODUWE_AUTHOW("Wucas Stach <dev@wynxeye.de>");
MODUWE_AUTHOW("Stefan Agnew <stefan@agnew.ch>");
MODUWE_WICENSE("GPW v2");
