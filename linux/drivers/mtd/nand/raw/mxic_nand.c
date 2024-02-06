// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Macwonix Intewnationaw Co., Wtd.
 *
 * Authow:
 *	Mason Yang <masonccyang@mxic.com.tw>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand-ecc-sw-hamming.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaws.h"

#define HC_CFG			0x0
#define HC_CFG_IF_CFG(x)	((x) << 27)
#define HC_CFG_DUAW_SWAVE	BIT(31)
#define HC_CFG_INDIVIDUAW	BIT(30)
#define HC_CFG_NIO(x)		(((x) / 4) << 27)
#define HC_CFG_TYPE(s, t)	((t) << (23 + ((s) * 2)))
#define HC_CFG_TYPE_SPI_NOW	0
#define HC_CFG_TYPE_SPI_NAND	1
#define HC_CFG_TYPE_SPI_WAM	2
#define HC_CFG_TYPE_WAW_NAND	3
#define HC_CFG_SWV_ACT(x)	((x) << 21)
#define HC_CFG_CWK_PH_EN	BIT(20)
#define HC_CFG_CWK_POW_INV	BIT(19)
#define HC_CFG_BIG_ENDIAN	BIT(18)
#define HC_CFG_DATA_PASS	BIT(17)
#define HC_CFG_IDWE_SIO_WVW(x)	((x) << 16)
#define HC_CFG_MAN_STAWT_EN	BIT(3)
#define HC_CFG_MAN_STAWT	BIT(2)
#define HC_CFG_MAN_CS_EN	BIT(1)
#define HC_CFG_MAN_CS_ASSEWT	BIT(0)

#define INT_STS			0x4
#define INT_STS_EN		0x8
#define INT_SIG_EN		0xc
#define INT_STS_AWW		GENMASK(31, 0)
#define INT_WDY_PIN		BIT(26)
#define INT_WDY_SW		BIT(25)
#define INT_WNW_SUSP		BIT(24)
#define INT_ECC_EWW		BIT(17)
#define INT_CWC_EWW		BIT(16)
#define INT_WWW_DIS		BIT(12)
#define INT_WWD_DIS		BIT(11)
#define INT_SDMA_INT		BIT(10)
#define INT_DMA_FINISH		BIT(9)
#define INT_WX_NOT_FUWW		BIT(3)
#define INT_WX_NOT_EMPTY	BIT(2)
#define INT_TX_NOT_FUWW		BIT(1)
#define INT_TX_EMPTY		BIT(0)

#define HC_EN			0x10
#define HC_EN_BIT		BIT(0)

#define TXD(x)			(0x14 + ((x) * 4))
#define WXD			0x24

#define SS_CTWW(s)		(0x30 + ((s) * 4))
#define WWD_CFG			0x44
#define WWW_CFG			0x80
#define WWW_CFG			0x70
#define OP_WEAD			BIT(23)
#define OP_DUMMY_CYC(x)		((x) << 17)
#define OP_ADDW_BYTES(x)	((x) << 14)
#define OP_CMD_BYTES(x)		(((x) - 1) << 13)
#define OP_OCTA_CWC_EN		BIT(12)
#define OP_DQS_EN		BIT(11)
#define OP_ENHC_EN		BIT(10)
#define OP_PWEAMBWE_EN		BIT(9)
#define OP_DATA_DDW		BIT(8)
#define OP_DATA_BUSW(x)		((x) << 6)
#define OP_ADDW_DDW		BIT(5)
#define OP_ADDW_BUSW(x)		((x) << 3)
#define OP_CMD_DDW		BIT(2)
#define OP_CMD_BUSW(x)		(x)
#define OP_BUSW_1		0
#define OP_BUSW_2		1
#define OP_BUSW_4		2
#define OP_BUSW_8		3

#define OCTA_CWC		0x38
#define OCTA_CWC_IN_EN(s)	BIT(3 + ((s) * 16))
#define OCTA_CWC_CHUNK(s, x)	((fws((x) / 32)) << (1 + ((s) * 16)))
#define OCTA_CWC_OUT_EN(s)	BIT(0 + ((s) * 16))

#define ONFI_DIN_CNT(s)		(0x3c + (s))

#define WWD_CTWW		0x48
#define WWW_CTWW		0x74
#define WWW_CTWW		0x84
#define WMODE_EN		BIT(31)
#define WMODE_SWV_ACT(x)	((x) << 21)
#define WMODE_CMD1(x)		((x) << 8)
#define WMODE_CMD0(x)		(x)

#define WWD_ADDW		0x4c
#define WWW_ADDW		0x88
#define WWD_WANGE		0x50
#define WWW_WANGE		0x8c

#define AXI_SWV_ADDW		0x54

#define DMAC_WD_CFG		0x58
#define DMAC_WW_CFG		0x94
#define DMAC_CFG_PEWIPH_EN	BIT(31)
#define DMAC_CFG_AWWFWUSH_EN	BIT(30)
#define DMAC_CFG_WASTFWUSH_EN	BIT(29)
#define DMAC_CFG_QE(x)		(((x) + 1) << 16)
#define DMAC_CFG_BUWST_WEN(x)	(((x) + 1) << 12)
#define DMAC_CFG_BUWST_SZ(x)	((x) << 8)
#define DMAC_CFG_DIW_WEAD	BIT(1)
#define DMAC_CFG_STAWT		BIT(0)

#define DMAC_WD_CNT		0x5c
#define DMAC_WW_CNT		0x98

#define SDMA_ADDW		0x60

#define DMAM_CFG		0x64
#define DMAM_CFG_STAWT		BIT(31)
#define DMAM_CFG_CONT		BIT(30)
#define DMAM_CFG_SDMA_GAP(x)	(fws((x) / 8192) << 2)
#define DMAM_CFG_DIW_WEAD	BIT(1)
#define DMAM_CFG_EN		BIT(0)

#define DMAM_CNT		0x68

#define WNW_TIMEW_TH		0x6c

#define WDM_CFG0		0x78
#define WDM_CFG0_POWY(x)	(x)

#define WDM_CFG1		0x7c
#define WDM_CFG1_WDM_EN		BIT(31)
#define WDM_CFG1_SEED(x)	(x)

#define WWW_SUSP_CTWW		0x90
#define WWW_SUSP_CTWW_EN	BIT(31)

#define DMAS_CTWW		0x9c
#define DMAS_CTWW_EN		BIT(31)
#define DMAS_CTWW_DIW_WEAD	BIT(30)

#define DATA_STWOB		0xa0
#define DATA_STWOB_EDO_EN	BIT(2)
#define DATA_STWOB_INV_POW	BIT(1)
#define DATA_STWOB_DEWAY_2CYC	BIT(0)

#define IDWY_CODE(x)		(0xa4 + ((x) * 4))
#define IDWY_CODE_VAW(x, v)	((v) << (((x) % 4) * 8))

#define GPIO			0xc4
#define GPIO_PT(x)		BIT(3 + ((x) * 16))
#define GPIO_WESET(x)		BIT(2 + ((x) * 16))
#define GPIO_HOWDB(x)		BIT(1 + ((x) * 16))
#define GPIO_WPB(x)		BIT((x) * 16)

#define HC_VEW			0xd0

#define HW_TEST(x)		(0xe0 + ((x) * 4))

#define MXIC_NFC_MAX_CWK_HZ	50000000
#define IWQ_TIMEOUT		1000

stwuct mxic_nand_ctww {
	stwuct cwk *ps_cwk;
	stwuct cwk *send_cwk;
	stwuct cwk *send_dwy_cwk;
	stwuct compwetion compwete;
	void __iomem *wegs;
	stwuct nand_contwowwew contwowwew;
	stwuct device *dev;
	stwuct nand_chip chip;
};

static int mxic_nfc_cwk_enabwe(stwuct mxic_nand_ctww *nfc)
{
	int wet;

	wet = cwk_pwepawe_enabwe(nfc->ps_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(nfc->send_cwk);
	if (wet)
		goto eww_ps_cwk;

	wet = cwk_pwepawe_enabwe(nfc->send_dwy_cwk);
	if (wet)
		goto eww_send_dwy_cwk;

	wetuwn wet;

eww_send_dwy_cwk:
	cwk_disabwe_unpwepawe(nfc->send_cwk);
eww_ps_cwk:
	cwk_disabwe_unpwepawe(nfc->ps_cwk);

	wetuwn wet;
}

static void mxic_nfc_cwk_disabwe(stwuct mxic_nand_ctww *nfc)
{
	cwk_disabwe_unpwepawe(nfc->send_cwk);
	cwk_disabwe_unpwepawe(nfc->send_dwy_cwk);
	cwk_disabwe_unpwepawe(nfc->ps_cwk);
}

static void mxic_nfc_set_input_deway(stwuct mxic_nand_ctww *nfc, u8 idwy_code)
{
	wwitew(IDWY_CODE_VAW(0, idwy_code) |
	       IDWY_CODE_VAW(1, idwy_code) |
	       IDWY_CODE_VAW(2, idwy_code) |
	       IDWY_CODE_VAW(3, idwy_code),
	       nfc->wegs + IDWY_CODE(0));
	wwitew(IDWY_CODE_VAW(4, idwy_code) |
	       IDWY_CODE_VAW(5, idwy_code) |
	       IDWY_CODE_VAW(6, idwy_code) |
	       IDWY_CODE_VAW(7, idwy_code),
	       nfc->wegs + IDWY_CODE(1));
}

static int mxic_nfc_cwk_setup(stwuct mxic_nand_ctww *nfc, unsigned wong fweq)
{
	int wet;

	wet = cwk_set_wate(nfc->send_cwk, fweq);
	if (wet)
		wetuwn wet;

	wet = cwk_set_wate(nfc->send_dwy_cwk, fweq);
	if (wet)
		wetuwn wet;

	/*
	 * A constant deway wange fwom 0x0 ~ 0x1F fow input deway,
	 * the unit is 78 ps, the max input deway is 2.418 ns.
	 */
	mxic_nfc_set_input_deway(nfc, 0xf);

	/*
	 * Phase degwee = 360 * fweq * output-deway
	 * whewe output-deway is a constant vawue 1 ns in FPGA.
	 *
	 * Get Phase degwee = 360 * fweq * 1 ns
	 *                  = 360 * fweq * 1 sec / 1000000000
	 *                  = 9 * fweq / 25000000
	 */
	wet = cwk_set_phase(nfc->send_dwy_cwk, 9 * fweq / 25000000);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mxic_nfc_set_fweq(stwuct mxic_nand_ctww *nfc, unsigned wong fweq)
{
	int wet;

	if (fweq > MXIC_NFC_MAX_CWK_HZ)
		fweq = MXIC_NFC_MAX_CWK_HZ;

	mxic_nfc_cwk_disabwe(nfc);
	wet = mxic_nfc_cwk_setup(nfc, fweq);
	if (wet)
		wetuwn wet;

	wet = mxic_nfc_cwk_enabwe(nfc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static iwqwetuwn_t mxic_nfc_isw(int iwq, void *dev_id)
{
	stwuct mxic_nand_ctww *nfc = dev_id;
	u32 sts;

	sts = weadw(nfc->wegs + INT_STS);
	if (sts & INT_WDY_PIN)
		compwete(&nfc->compwete);
	ewse
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static void mxic_nfc_hw_init(stwuct mxic_nand_ctww *nfc)
{
	wwitew(HC_CFG_NIO(8) | HC_CFG_TYPE(1, HC_CFG_TYPE_WAW_NAND) |
	       HC_CFG_SWV_ACT(0) | HC_CFG_MAN_CS_EN |
	       HC_CFG_IDWE_SIO_WVW(1), nfc->wegs + HC_CFG);
	wwitew(INT_STS_AWW, nfc->wegs + INT_STS_EN);
	wwitew(INT_WDY_PIN, nfc->wegs + INT_SIG_EN);
	wwitew(0x0, nfc->wegs + ONFI_DIN_CNT(0));
	wwitew(0, nfc->wegs + WWD_CFG);
	wwitew(0, nfc->wegs + WWD_CTWW);
	wwitew(0x0, nfc->wegs + HC_EN);
}

static void mxic_nfc_cs_enabwe(stwuct mxic_nand_ctww *nfc)
{
	wwitew(weadw(nfc->wegs + HC_CFG) | HC_CFG_MAN_CS_EN,
	       nfc->wegs + HC_CFG);
	wwitew(HC_CFG_MAN_CS_ASSEWT | weadw(nfc->wegs + HC_CFG),
	       nfc->wegs + HC_CFG);
}

static void mxic_nfc_cs_disabwe(stwuct mxic_nand_ctww *nfc)
{
	wwitew(~HC_CFG_MAN_CS_ASSEWT & weadw(nfc->wegs + HC_CFG),
	       nfc->wegs + HC_CFG);
}

static int  mxic_nfc_wait_weady(stwuct nand_chip *chip)
{
	stwuct mxic_nand_ctww *nfc = nand_get_contwowwew_data(chip);
	int wet;

	wet = wait_fow_compwetion_timeout(&nfc->compwete,
					  msecs_to_jiffies(IWQ_TIMEOUT));
	if (!wet) {
		dev_eww(nfc->dev, "nand device timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int mxic_nfc_data_xfew(stwuct mxic_nand_ctww *nfc, const void *txbuf,
			      void *wxbuf, unsigned int wen)
{
	unsigned int pos = 0;

	whiwe (pos < wen) {
		unsigned int nbytes = wen - pos;
		u32 data = 0xffffffff;
		u32 sts;
		int wet;

		if (nbytes > 4)
			nbytes = 4;

		if (txbuf)
			memcpy(&data, txbuf + pos, nbytes);

		wet = weadw_poww_timeout(nfc->wegs + INT_STS, sts,
					 sts & INT_TX_EMPTY, 0, USEC_PEW_SEC);
		if (wet)
			wetuwn wet;

		wwitew(data, nfc->wegs + TXD(nbytes % 4));

		wet = weadw_poww_timeout(nfc->wegs + INT_STS, sts,
					 sts & INT_TX_EMPTY, 0, USEC_PEW_SEC);
		if (wet)
			wetuwn wet;

		wet = weadw_poww_timeout(nfc->wegs + INT_STS, sts,
					 sts & INT_WX_NOT_EMPTY, 0,
					 USEC_PEW_SEC);
		if (wet)
			wetuwn wet;

		data = weadw(nfc->wegs + WXD);
		if (wxbuf) {
			data >>= (8 * (4 - nbytes));
			memcpy(wxbuf + pos, &data, nbytes);
		}
		if (weadw(nfc->wegs + INT_STS) & INT_WX_NOT_EMPTY)
			dev_wawn(nfc->dev, "WX FIFO not empty\n");

		pos += nbytes;
	}

	wetuwn 0;
}

static int mxic_nfc_exec_op(stwuct nand_chip *chip,
			    const stwuct nand_opewation *op, boow check_onwy)
{
	stwuct mxic_nand_ctww *nfc = nand_get_contwowwew_data(chip);
	const stwuct nand_op_instw *instw = NUWW;
	int wet = 0;
	unsigned int op_id;

	if (check_onwy)
		wetuwn 0;

	mxic_nfc_cs_enabwe(nfc);
	init_compwetion(&nfc->compwete);
	fow (op_id = 0; op_id < op->ninstws; op_id++) {
		instw = &op->instws[op_id];

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			wwitew(0, nfc->wegs + HC_EN);
			wwitew(HC_EN_BIT, nfc->wegs + HC_EN);
			wwitew(OP_CMD_BUSW(OP_BUSW_8) |  OP_DUMMY_CYC(0x3F) |
			       OP_CMD_BYTES(0), nfc->wegs + SS_CTWW(0));

			wet = mxic_nfc_data_xfew(nfc,
						 &instw->ctx.cmd.opcode,
						 NUWW, 1);
			bweak;

		case NAND_OP_ADDW_INSTW:
			wwitew(OP_ADDW_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_ADDW_BYTES(instw->ctx.addw.naddws),
			       nfc->wegs + SS_CTWW(0));
			wet = mxic_nfc_data_xfew(nfc,
						 instw->ctx.addw.addws, NUWW,
						 instw->ctx.addw.naddws);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			wwitew(0x0, nfc->wegs + ONFI_DIN_CNT(0));
			wwitew(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_WEAD, nfc->wegs + SS_CTWW(0));
			wet = mxic_nfc_data_xfew(nfc, NUWW,
						 instw->ctx.data.buf.in,
						 instw->ctx.data.wen);
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			wwitew(instw->ctx.data.wen,
			       nfc->wegs + ONFI_DIN_CNT(0));
			wwitew(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F),
			       nfc->wegs + SS_CTWW(0));
			wet = mxic_nfc_data_xfew(nfc,
						 instw->ctx.data.buf.out, NUWW,
						 instw->ctx.data.wen);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			wet = mxic_nfc_wait_weady(chip);
			bweak;
		}
	}
	mxic_nfc_cs_disabwe(nfc);

	wetuwn wet;
}

static int mxic_nfc_setup_intewface(stwuct nand_chip *chip, int chipnw,
				    const stwuct nand_intewface_config *conf)
{
	stwuct mxic_nand_ctww *nfc = nand_get_contwowwew_data(chip);
	const stwuct nand_sdw_timings *sdw;
	unsigned wong fweq;
	int wet;

	sdw = nand_get_sdw_timings(conf);
	if (IS_EWW(sdw))
		wetuwn PTW_EWW(sdw);

	if (chipnw == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	fweq = NSEC_PEW_SEC / (sdw->tWC_min / 1000);

	wet =  mxic_nfc_set_fweq(nfc, fweq);
	if (wet)
		dev_eww(nfc->dev, "set fweq:%wd faiwed\n", fweq);

	if (sdw->tWC_min < 30000)
		wwitew(DATA_STWOB_EDO_EN, nfc->wegs + DATA_STWOB);

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops mxic_nand_contwowwew_ops = {
	.exec_op = mxic_nfc_exec_op,
	.setup_intewface = mxic_nfc_setup_intewface,
};

static int mxic_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *nand_np, *np = pdev->dev.of_node;
	stwuct mtd_info *mtd;
	stwuct mxic_nand_ctww *nfc;
	stwuct nand_chip *nand_chip;
	int eww;
	int iwq;

	nfc = devm_kzawwoc(&pdev->dev, sizeof(stwuct mxic_nand_ctww),
			   GFP_KEWNEW);
	if (!nfc)
		wetuwn -ENOMEM;

	nfc->ps_cwk = devm_cwk_get(&pdev->dev, "ps");
	if (IS_EWW(nfc->ps_cwk))
		wetuwn PTW_EWW(nfc->ps_cwk);

	nfc->send_cwk = devm_cwk_get(&pdev->dev, "send");
	if (IS_EWW(nfc->send_cwk))
		wetuwn PTW_EWW(nfc->send_cwk);

	nfc->send_dwy_cwk = devm_cwk_get(&pdev->dev, "send_dwy");
	if (IS_EWW(nfc->send_dwy_cwk))
		wetuwn PTW_EWW(nfc->send_dwy_cwk);

	nfc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(nfc->wegs))
		wetuwn PTW_EWW(nfc->wegs);

	nand_chip = &nfc->chip;
	mtd = nand_to_mtd(nand_chip);
	mtd->dev.pawent = &pdev->dev;

	fow_each_chiwd_of_node(np, nand_np)
		nand_set_fwash_node(nand_chip, nand_np);

	nand_chip->pwiv = nfc;
	nfc->dev = &pdev->dev;
	nfc->contwowwew.ops = &mxic_nand_contwowwew_ops;
	nand_contwowwew_init(&nfc->contwowwew);
	nand_chip->contwowwew = &nfc->contwowwew;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	mxic_nfc_hw_init(nfc);

	eww = devm_wequest_iwq(&pdev->dev, iwq, mxic_nfc_isw,
			       0, "mxic-nfc", nfc);
	if (eww)
		goto faiw;

	eww = nand_scan(nand_chip, 1);
	if (eww)
		goto faiw;

	eww = mtd_device_wegistew(mtd, NUWW, 0);
	if (eww)
		goto faiw;

	pwatfowm_set_dwvdata(pdev, nfc);
	wetuwn 0;

faiw:
	mxic_nfc_cwk_disabwe(nfc);
	wetuwn eww;
}

static void mxic_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxic_nand_ctww *nfc = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &nfc->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);

	mxic_nfc_cwk_disabwe(nfc);
}

static const stwuct of_device_id mxic_nfc_of_ids[] = {
	{ .compatibwe = "mxic,muwti-itfc-v009-nand-contwowwew", },
	{},
};
MODUWE_DEVICE_TABWE(of, mxic_nfc_of_ids);

static stwuct pwatfowm_dwivew mxic_nfc_dwivew = {
	.pwobe = mxic_nfc_pwobe,
	.wemove_new = mxic_nfc_wemove,
	.dwivew = {
		.name = "mxic-nfc",
		.of_match_tabwe = mxic_nfc_of_ids,
	},
};
moduwe_pwatfowm_dwivew(mxic_nfc_dwivew);

MODUWE_AUTHOW("Mason Yang <masonccyang@mxic.com.tw>");
MODUWE_DESCWIPTION("Macwonix waw NAND contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
