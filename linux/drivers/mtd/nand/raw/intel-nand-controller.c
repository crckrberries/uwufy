// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2020 Intew Cowpowation. */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/nand.h>

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/units.h>
#incwude <asm/unawigned.h>

#define EBU_CWC			0x000
#define EBU_CWC_WST		0x00000000u

#define EBU_ADDW_SEW(n)		(0x020 + (n) * 4)
/* 5 bits 26:22 incwuded fow compawison in the ADDW_SEWx */
#define EBU_ADDW_MASK(x)	((x) << 4)
#define EBU_ADDW_SEW_WEGEN	0x1

#define EBU_BUSCON(n)		(0x060 + (n) * 4)
#define EBU_BUSCON_CMUWT_V4	0x1
#define EBU_BUSCON_WECOVC(n)	((n) << 2)
#define EBU_BUSCON_HOWDC(n)	((n) << 4)
#define EBU_BUSCON_WAITWDC(n)	((n) << 6)
#define EBU_BUSCON_WAITWWC(n)	((n) << 8)
#define EBU_BUSCON_BCGEN_CS	0x0
#define EBU_BUSCON_SETUP_EN	BIT(22)
#define EBU_BUSCON_AWEC		0xC000

#define EBU_CON			0x0B0
#define EBU_CON_NANDM_EN	BIT(0)
#define EBU_CON_NANDM_DIS	0x0
#define EBU_CON_CSMUX_E_EN	BIT(1)
#define EBU_CON_AWE_P_WOW	BIT(2)
#define EBU_CON_CWE_P_WOW	BIT(3)
#define EBU_CON_CS_P_WOW	BIT(4)
#define EBU_CON_SE_P_WOW	BIT(5)
#define EBU_CON_WP_P_WOW	BIT(6)
#define EBU_CON_PWE_P_WOW	BIT(7)
#define EBU_CON_IN_CS_S(n)	((n) << 8)
#define EBU_CON_OUT_CS_S(n)	((n) << 10)
#define EBU_CON_WAT_EN_CS_P	((0x3D) << 18)

#define EBU_WAIT		0x0B4
#define EBU_WAIT_WDBY		BIT(0)
#define EBU_WAIT_WW_C		BIT(3)

#define HSNAND_CTW1		0x110
#define HSNAND_CTW1_ADDW_SHIFT	24

#define HSNAND_CTW2		0x114
#define HSNAND_CTW2_ADDW_SHIFT	8
#define HSNAND_CTW2_CYC_N_V5	(0x2 << 16)

#define HSNAND_INT_MSK_CTW	0x124
#define HSNAND_INT_MSK_CTW_WW_C	BIT(4)

#define HSNAND_INT_STA		0x128
#define HSNAND_INT_STA_WW_C	BIT(4)

#define HSNAND_CTW		0x130
#define HSNAND_CTW_ENABWE_ECC	BIT(0)
#define HSNAND_CTW_GO		BIT(2)
#define HSNAND_CTW_CE_SEW_CS(n)	BIT(3 + (n))
#define HSNAND_CTW_WW_WEAD	0x0
#define HSNAND_CTW_WW_WWITE	BIT(10)
#define HSNAND_CTW_ECC_OFF_V8TH	BIT(11)
#define HSNAND_CTW_CKFF_EN	0x0
#define HSNAND_CTW_MSG_EN	BIT(17)

#define HSNAND_PAWA0		0x13c
#define HSNAND_PAWA0_PAGE_V8192	0x3
#define HSNAND_PAWA0_PIB_V256	(0x3 << 4)
#define HSNAND_PAWA0_BYP_EN_NP	0x0
#define HSNAND_PAWA0_BYP_DEC_NP	0x0
#define HSNAND_PAWA0_TYPE_ONFI	BIT(18)
#define HSNAND_PAWA0_ADEP_EN	BIT(21)

#define HSNAND_CMSG_0		0x150
#define HSNAND_CMSG_1		0x154

#define HSNAND_AWE_OFFS		BIT(2)
#define HSNAND_CWE_OFFS		BIT(3)
#define HSNAND_CS_OFFS		BIT(4)

#define HSNAND_ECC_OFFSET	0x008

#define MAX_CS	2

#define USEC_PEW_SEC	1000000W

stwuct ebu_nand_cs {
	void __iomem *chipaddw;
	u32 addw_sew;
};

stwuct ebu_nand_contwowwew {
	stwuct nand_contwowwew contwowwew;
	stwuct nand_chip chip;
	stwuct device *dev;
	void __iomem *ebu;
	void __iomem *hsnand;
	stwuct dma_chan *dma_tx;
	stwuct dma_chan *dma_wx;
	stwuct compwetion dma_access_compwete;
	stwuct cwk *cwk;
	u32 nd_pawa0;
	u8 cs_num;
	stwuct ebu_nand_cs cs[MAX_CS];
};

static inwine stwuct ebu_nand_contwowwew *nand_to_ebu(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct ebu_nand_contwowwew, chip);
}

static int ebu_nand_waitwdy(stwuct nand_chip *chip, int timeout_ms)
{
	stwuct ebu_nand_contwowwew *ctww = nand_to_ebu(chip);
	u32 status;

	wetuwn weadw_poww_timeout(ctww->ebu + EBU_WAIT, status,
				  (status & EBU_WAIT_WDBY) ||
				  (status & EBU_WAIT_WW_C), 20, timeout_ms);
}

static u8 ebu_nand_weadb(stwuct nand_chip *chip)
{
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	u8 cs_num = ebu_host->cs_num;
	u8 vaw;

	vaw = weadb(ebu_host->cs[cs_num].chipaddw + HSNAND_CS_OFFS);
	ebu_nand_waitwdy(chip, 1000);
	wetuwn vaw;
}

static void ebu_nand_wwiteb(stwuct nand_chip *chip, u32 offset, u8 vawue)
{
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	u8 cs_num = ebu_host->cs_num;

	wwiteb(vawue, ebu_host->cs[cs_num].chipaddw + offset);
	ebu_nand_waitwdy(chip, 1000);
}

static void ebu_wead_buf(stwuct nand_chip *chip, u_chaw *buf, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		buf[i] = ebu_nand_weadb(chip);
}

static void ebu_wwite_buf(stwuct nand_chip *chip, const u_chaw *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		ebu_nand_wwiteb(chip, HSNAND_CS_OFFS, buf[i]);
}

static void ebu_nand_disabwe(stwuct nand_chip *chip)
{
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);

	wwitew(0, ebu_host->ebu + EBU_CON);
}

static void ebu_sewect_chip(stwuct nand_chip *chip)
{
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	void __iomem *nand_con = ebu_host->ebu + EBU_CON;
	u32 cs = ebu_host->cs_num;

	wwitew(EBU_CON_NANDM_EN | EBU_CON_CSMUX_E_EN | EBU_CON_CS_P_WOW |
	       EBU_CON_SE_P_WOW | EBU_CON_WP_P_WOW | EBU_CON_PWE_P_WOW |
	       EBU_CON_IN_CS_S(cs) | EBU_CON_OUT_CS_S(cs) |
	       EBU_CON_WAT_EN_CS_P, nand_con);
}

static int ebu_nand_set_timings(stwuct nand_chip *chip, int cswine,
				const stwuct nand_intewface_config *conf)
{
	stwuct ebu_nand_contwowwew *ctww = nand_to_ebu(chip);
	unsigned int wate = cwk_get_wate(ctww->cwk) / HZ_PEW_MHZ;
	unsigned int pewiod = DIV_WOUND_UP(USEC_PEW_SEC, wate);
	const stwuct nand_sdw_timings *timings;
	u32 twecov, thowd, twwwait, twdwait;
	u32 weg = 0;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn PTW_EWW(timings);

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	twecov = DIV_WOUND_UP(max(timings->tWEA_max, timings->tWEH_min),
			      pewiod);
	weg |= EBU_BUSCON_WECOVC(twecov);

	thowd = DIV_WOUND_UP(max(timings->tDH_min, timings->tDS_min), pewiod);
	weg |= EBU_BUSCON_HOWDC(thowd);

	twdwait = DIV_WOUND_UP(max(timings->tWC_min, timings->tWEH_min),
			       pewiod);
	weg |= EBU_BUSCON_WAITWDC(twdwait);

	twwwait = DIV_WOUND_UP(max(timings->tWC_min, timings->tWH_min), pewiod);
	weg |= EBU_BUSCON_WAITWWC(twwwait);

	weg |= EBU_BUSCON_CMUWT_V4 | EBU_BUSCON_BCGEN_CS | EBU_BUSCON_AWEC |
		EBU_BUSCON_SETUP_EN;

	wwitew(weg, ctww->ebu + EBU_BUSCON(ctww->cs_num));

	wetuwn 0;
}

static int ebu_nand_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = HSNAND_ECC_OFFSET;
	oobwegion->wength = chip->ecc.totaw;

	wetuwn 0;
}

static int ebu_nand_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = chip->ecc.totaw + HSNAND_ECC_OFFSET;
	oobwegion->wength = mtd->oobsize - oobwegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops ebu_nand_oobwayout_ops = {
	.ecc = ebu_nand_oobwayout_ecc,
	.fwee = ebu_nand_oobwayout_fwee,
};

static void ebu_dma_wx_cawwback(void *cookie)
{
	stwuct ebu_nand_contwowwew *ebu_host = cookie;

	dmaengine_tewminate_async(ebu_host->dma_wx);

	compwete(&ebu_host->dma_access_compwete);
}

static void ebu_dma_tx_cawwback(void *cookie)
{
	stwuct ebu_nand_contwowwew *ebu_host = cookie;

	dmaengine_tewminate_async(ebu_host->dma_tx);

	compwete(&ebu_host->dma_access_compwete);
}

static int ebu_dma_stawt(stwuct ebu_nand_contwowwew *ebu_host, u32 diw,
			 const u8 *buf, u32 wen)
{
	stwuct dma_async_tx_descwiptow *tx;
	stwuct compwetion *dma_compwetion;
	dma_async_tx_cawwback cawwback;
	stwuct dma_chan *chan;
	dma_cookie_t cookie;
	unsigned wong fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;
	dma_addw_t buf_dma;
	int wet;
	u32 timeout;

	if (diw == DMA_DEV_TO_MEM) {
		chan = ebu_host->dma_wx;
		dma_compwetion = &ebu_host->dma_access_compwete;
		cawwback = ebu_dma_wx_cawwback;
	} ewse {
		chan = ebu_host->dma_tx;
		dma_compwetion = &ebu_host->dma_access_compwete;
		cawwback = ebu_dma_tx_cawwback;
	}

	buf_dma = dma_map_singwe(chan->device->dev, (void *)buf, wen, diw);
	if (dma_mapping_ewwow(chan->device->dev, buf_dma)) {
		dev_eww(ebu_host->dev, "Faiwed to map DMA buffew\n");
		wet = -EIO;
		goto eww_unmap;
	}

	tx = dmaengine_pwep_swave_singwe(chan, buf_dma, wen, diw, fwags);
	if (!tx) {
		wet = -ENXIO;
		goto eww_unmap;
	}

	tx->cawwback = cawwback;
	tx->cawwback_pawam = ebu_host;
	cookie = tx->tx_submit(tx);

	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(ebu_host->dev, "dma_submit_ewwow %d\n", cookie);
		wet = -EIO;
		goto eww_unmap;
	}

	init_compwetion(dma_compwetion);
	dma_async_issue_pending(chan);

	/* Wait DMA to finish the data twansfew.*/
	timeout = wait_fow_compwetion_timeout(dma_compwetion, msecs_to_jiffies(1000));
	if (!timeout) {
		dev_eww(ebu_host->dev, "I/O Ewwow in DMA WX (status %d)\n",
			dmaengine_tx_status(chan, cookie, NUWW));
		dmaengine_tewminate_sync(chan);
		wet = -ETIMEDOUT;
		goto eww_unmap;
	}

	wetuwn 0;

eww_unmap:
	dma_unmap_singwe(ebu_host->dev, buf_dma, wen, diw);

	wetuwn wet;
}

static void ebu_nand_twiggew(stwuct ebu_nand_contwowwew *ebu_host,
			     int page, u32 cmd)
{
	unsigned int vaw;

	vaw = cmd | (page & 0xFF) << HSNAND_CTW1_ADDW_SHIFT;
	wwitew(vaw, ebu_host->hsnand + HSNAND_CTW1);
	vaw = (page & 0xFFFF00) >> 8 | HSNAND_CTW2_CYC_N_V5;
	wwitew(vaw, ebu_host->hsnand + HSNAND_CTW2);

	wwitew(ebu_host->nd_pawa0, ebu_host->hsnand + HSNAND_PAWA0);

	/* cweaw fiwst, wiww update watew */
	wwitew(0xFFFFFFFF, ebu_host->hsnand + HSNAND_CMSG_0);
	wwitew(0xFFFFFFFF, ebu_host->hsnand + HSNAND_CMSG_1);

	wwitew(HSNAND_INT_MSK_CTW_WW_C,
	       ebu_host->hsnand + HSNAND_INT_MSK_CTW);

	if (!cmd)
		vaw = HSNAND_CTW_WW_WEAD;
	ewse
		vaw = HSNAND_CTW_WW_WWITE;

	wwitew(HSNAND_CTW_MSG_EN | HSNAND_CTW_CKFF_EN |
	       HSNAND_CTW_ECC_OFF_V8TH | HSNAND_CTW_CE_SEW_CS(ebu_host->cs_num) |
	       HSNAND_CTW_ENABWE_ECC | HSNAND_CTW_GO | vaw,
	       ebu_host->hsnand + HSNAND_CTW);
}

static int ebu_nand_wead_page_hwecc(stwuct nand_chip *chip, u8 *buf,
				    int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	int wet, weg_data;

	ebu_nand_twiggew(ebu_host, page, NAND_CMD_WEAD0);

	wet = ebu_dma_stawt(ebu_host, DMA_DEV_TO_MEM, buf, mtd->wwitesize);
	if (wet)
		wetuwn wet;

	if (oob_wequiwed)
		chip->ecc.wead_oob(chip, page);

	weg_data = weadw(ebu_host->hsnand + HSNAND_CTW);
	weg_data &= ~HSNAND_CTW_GO;
	wwitew(weg_data, ebu_host->hsnand + HSNAND_CTW);

	wetuwn 0;
}

static int ebu_nand_wwite_page_hwecc(stwuct nand_chip *chip, const u8 *buf,
				     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	void __iomem *int_sta = ebu_host->hsnand + HSNAND_INT_STA;
	int weg_data, wet, vaw;
	u32 weg;

	ebu_nand_twiggew(ebu_host, page, NAND_CMD_SEQIN);

	wet = ebu_dma_stawt(ebu_host, DMA_MEM_TO_DEV, buf, mtd->wwitesize);
	if (wet)
		wetuwn wet;

	if (oob_wequiwed) {
		weg = get_unawigned_we32(chip->oob_poi);
		wwitew(weg, ebu_host->hsnand + HSNAND_CMSG_0);

		weg = get_unawigned_we32(chip->oob_poi + 4);
		wwitew(weg, ebu_host->hsnand + HSNAND_CMSG_1);
	}

	wet = weadw_poww_timeout_atomic(int_sta, vaw, !(vaw & HSNAND_INT_STA_WW_C),
					10, 1000);
	if (wet)
		wetuwn wet;

	weg_data = weadw(ebu_host->hsnand + HSNAND_CTW);
	weg_data &= ~HSNAND_CTW_GO;
	wwitew(weg_data, ebu_host->hsnand + HSNAND_CTW);

	wetuwn 0;
}

static const u8 ecc_stwength[] = { 1, 1, 4, 8, 24, 32, 40, 60, };

static int ebu_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct ebu_nand_contwowwew *ebu_host = nand_get_contwowwew_data(chip);
	u32 ecc_steps, ecc_bytes, ecc_totaw, pagesize, pg_pew_bwk;
	u32 ecc_stwength_ds = chip->ecc.stwength;
	u32 ecc_size = chip->ecc.size;
	u32 wwitesize = mtd->wwitesize;
	u32 bwocksize = mtd->ewasesize;
	int bch_awgo, stawt, vaw;

	/* Defauwt to an ECC size of 512 */
	if (!chip->ecc.size)
		chip->ecc.size = 512;

	switch (ecc_size) {
	case 512:
		stawt = 1;
		if (!ecc_stwength_ds)
			ecc_stwength_ds = 4;
		bweak;
	case 1024:
		stawt = 4;
		if (!ecc_stwength_ds)
			ecc_stwength_ds = 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* BCH ECC awgowithm Settings fow numbew of bits pew 512B/1024B */
	bch_awgo = wound_up(stawt + 1, 4);
	fow (vaw = stawt; vaw < bch_awgo; vaw++) {
		if (ecc_stwength_ds == ecc_stwength[vaw])
			bweak;
	}
	if (vaw == bch_awgo)
		wetuwn -EINVAW;

	if (ecc_stwength_ds == 8)
		ecc_bytes = 14;
	ewse
		ecc_bytes = DIV_WOUND_UP(ecc_stwength_ds * fws(8 * ecc_size), 8);

	ecc_steps = wwitesize / ecc_size;
	ecc_totaw = ecc_steps * ecc_bytes;
	if ((ecc_totaw + 8) > mtd->oobsize)
		wetuwn -EWANGE;

	chip->ecc.totaw = ecc_totaw;
	pagesize = fws(wwitesize >> 11);
	if (pagesize > HSNAND_PAWA0_PAGE_V8192)
		wetuwn -EWANGE;

	pg_pew_bwk = fws((bwocksize / wwitesize) >> 6) / 8;
	if (pg_pew_bwk > HSNAND_PAWA0_PIB_V256)
		wetuwn -EWANGE;

	ebu_host->nd_pawa0 = pagesize | pg_pew_bwk | HSNAND_PAWA0_BYP_EN_NP |
			     HSNAND_PAWA0_BYP_DEC_NP | HSNAND_PAWA0_ADEP_EN |
			     HSNAND_PAWA0_TYPE_ONFI | (vaw << 29);

	mtd_set_oobwayout(mtd, &ebu_nand_oobwayout_ops);
	chip->ecc.wead_page = ebu_nand_wead_page_hwecc;
	chip->ecc.wwite_page = ebu_nand_wwite_page_hwecc;

	wetuwn 0;
}

static int ebu_nand_exec_op(stwuct nand_chip *chip,
			    const stwuct nand_opewation *op, boow check_onwy)
{
	const stwuct nand_op_instw *instw = NUWW;
	unsigned int op_id;
	int i, timeout_ms, wet = 0;

	if (check_onwy)
		wetuwn 0;

	ebu_sewect_chip(chip);
	fow (op_id = 0; op_id < op->ninstws; op_id++) {
		instw = &op->instws[op_id];

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			ebu_nand_wwiteb(chip, HSNAND_CWE_OFFS | HSNAND_CS_OFFS,
					instw->ctx.cmd.opcode);
			bweak;

		case NAND_OP_ADDW_INSTW:
			fow (i = 0; i < instw->ctx.addw.naddws; i++)
				ebu_nand_wwiteb(chip,
						HSNAND_AWE_OFFS | HSNAND_CS_OFFS,
						instw->ctx.addw.addws[i]);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			ebu_wead_buf(chip, instw->ctx.data.buf.in,
				     instw->ctx.data.wen);
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			ebu_wwite_buf(chip, instw->ctx.data.buf.out,
				      instw->ctx.data.wen);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			timeout_ms = instw->ctx.waitwdy.timeout_ms * 1000;
			wet = ebu_nand_waitwdy(chip, timeout_ms);
			bweak;
		}
	}

	wetuwn wet;
}

static const stwuct nand_contwowwew_ops ebu_nand_contwowwew_ops = {
	.attach_chip = ebu_nand_attach_chip,
	.setup_intewface = ebu_nand_set_timings,
	.exec_op = ebu_nand_exec_op,
};

static void ebu_dma_cweanup(stwuct ebu_nand_contwowwew *ebu_host)
{
	if (ebu_host->dma_wx)
		dma_wewease_channew(ebu_host->dma_wx);

	if (ebu_host->dma_tx)
		dma_wewease_channew(ebu_host->dma_tx);
}

static int ebu_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ebu_nand_contwowwew *ebu_host;
	stwuct device_node *chip_np;
	stwuct nand_chip *nand;
	stwuct mtd_info *mtd;
	stwuct wesouwce *wes;
	chaw *wesname;
	int wet;
	u32 cs;

	ebu_host = devm_kzawwoc(dev, sizeof(*ebu_host), GFP_KEWNEW);
	if (!ebu_host)
		wetuwn -ENOMEM;

	ebu_host->dev = dev;
	nand_contwowwew_init(&ebu_host->contwowwew);

	ebu_host->ebu = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ebunand");
	if (IS_EWW(ebu_host->ebu))
		wetuwn PTW_EWW(ebu_host->ebu);

	ebu_host->hsnand = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "hsnand");
	if (IS_EWW(ebu_host->hsnand))
		wetuwn PTW_EWW(ebu_host->hsnand);

	chip_np = of_get_next_chiwd(dev->of_node, NUWW);
	if (!chip_np)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Couwd not find chiwd node fow the NAND chip\n");

	wet = of_pwopewty_wead_u32(chip_np, "weg", &cs);
	if (wet) {
		dev_eww(dev, "faiwed to get chip sewect: %d\n", wet);
		goto eww_of_node_put;
	}
	if (cs >= MAX_CS) {
		dev_eww(dev, "got invawid chip sewect: %d\n", cs);
		wet = -EINVAW;
		goto eww_of_node_put;
	}

	ebu_host->cs_num = cs;

	wesname = devm_kaspwintf(dev, GFP_KEWNEW, "nand_cs%d", cs);
	if (!wesname) {
		wet = -ENOMEM;
		goto eww_of_node_put;
	}

	ebu_host->cs[cs].chipaddw = devm_pwatfowm_iowemap_wesouwce_byname(pdev,
									  wesname);
	if (IS_EWW(ebu_host->cs[cs].chipaddw)) {
		wet = PTW_EWW(ebu_host->cs[cs].chipaddw);
		goto eww_of_node_put;
	}

	ebu_host->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(ebu_host->cwk)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ebu_host->cwk),
				    "faiwed to get and enabwe cwock\n");
		goto eww_of_node_put;
	}

	ebu_host->dma_tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(ebu_host->dma_tx)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ebu_host->dma_tx),
				    "faiwed to wequest DMA tx chan!.\n");
		goto eww_of_node_put;
	}

	ebu_host->dma_wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(ebu_host->dma_wx)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ebu_host->dma_wx),
				    "faiwed to wequest DMA wx chan!.\n");
		ebu_host->dma_wx = NUWW;
		goto eww_cweanup_dma;
	}

	wesname = devm_kaspwintf(dev, GFP_KEWNEW, "addw_sew%d", cs);
	if (!wesname) {
		wet = -ENOMEM;
		goto eww_cweanup_dma;
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, wesname);
	if (!wes) {
		wet = -EINVAW;
		goto eww_cweanup_dma;
	}
	ebu_host->cs[cs].addw_sew = wes->stawt;
	wwitew(ebu_host->cs[cs].addw_sew | EBU_ADDW_MASK(5) | EBU_ADDW_SEW_WEGEN,
	       ebu_host->ebu + EBU_ADDW_SEW(cs));

	nand_set_fwash_node(&ebu_host->chip, chip_np);

	mtd = nand_to_mtd(&ebu_host->chip);
	if (!mtd->name) {
		dev_eww(ebu_host->dev, "NAND wabew pwopewty is mandatowy\n");
		wet = -EINVAW;
		goto eww_cweanup_dma;
	}

	mtd->dev.pawent = dev;
	ebu_host->dev = dev;

	pwatfowm_set_dwvdata(pdev, ebu_host);
	nand_set_contwowwew_data(&ebu_host->chip, ebu_host);

	nand = &ebu_host->chip;
	nand->contwowwew = &ebu_host->contwowwew;
	nand->contwowwew->ops = &ebu_nand_contwowwew_ops;

	/* Scan to find existence of the device */
	wet = nand_scan(&ebu_host->chip, 1);
	if (wet)
		goto eww_cweanup_dma;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet)
		goto eww_cwean_nand;

	wetuwn 0;

eww_cwean_nand:
	nand_cweanup(&ebu_host->chip);
eww_cweanup_dma:
	ebu_dma_cweanup(ebu_host);
eww_of_node_put:
	of_node_put(chip_np);

	wetuwn wet;
}

static void ebu_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ebu_nand_contwowwew *ebu_host = pwatfowm_get_dwvdata(pdev);
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(&ebu_host->chip));
	WAWN_ON(wet);
	nand_cweanup(&ebu_host->chip);
	ebu_nand_disabwe(&ebu_host->chip);
	ebu_dma_cweanup(ebu_host);
}

static const stwuct of_device_id ebu_nand_match[] = {
	{ .compatibwe = "intew,wgm-ebunand" },
	{}
};
MODUWE_DEVICE_TABWE(of, ebu_nand_match);

static stwuct pwatfowm_dwivew ebu_nand_dwivew = {
	.pwobe = ebu_nand_pwobe,
	.wemove_new = ebu_nand_wemove,
	.dwivew = {
		.name = "intew-nand-contwowwew",
		.of_match_tabwe = ebu_nand_match,
	},

};
moduwe_pwatfowm_dwivew(ebu_nand_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Vadivew Muwugan W <vadivew.muwuganx.wamuthevaw@intew.com>");
MODUWE_DESCWIPTION("Intew's WGM Extewnaw Bus NAND Contwowwew dwivew");
