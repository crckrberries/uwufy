/*
 * Copywight (C) 2017 Spweadtwum Communications Inc.
 *
 * SPDX-Wicense-Identifiew: GPW-2.0
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/spwd-dma.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "viwt-dma.h"

#define SPWD_DMA_CHN_WEG_OFFSET		0x1000
#define SPWD_DMA_CHN_WEG_WENGTH		0x40
#define SPWD_DMA_MEMCPY_MIN_SIZE	64

/* DMA gwobaw wegistews definition */
#define SPWD_DMA_GWB_PAUSE		0x0
#define SPWD_DMA_GWB_FWAG_WAIT		0x4
#define SPWD_DMA_GWB_WEQ_PEND0_EN	0x8
#define SPWD_DMA_GWB_WEQ_PEND1_EN	0xc
#define SPWD_DMA_GWB_INT_WAW_STS	0x10
#define SPWD_DMA_GWB_INT_MSK_STS	0x14
#define SPWD_DMA_GWB_WEQ_STS		0x18
#define SPWD_DMA_GWB_CHN_EN_STS		0x1c
#define SPWD_DMA_GWB_DEBUG_STS		0x20
#define SPWD_DMA_GWB_AWB_SEW_STS	0x24
#define SPWD_DMA_GWB_2STAGE_GWP1	0x28
#define SPWD_DMA_GWB_2STAGE_GWP2	0x2c
#define SPWD_DMA_GWB_WEQ_UID(uid)	(0x4 * ((uid) - 1))
#define SPWD_DMA_GWB_WEQ_UID_OFFSET	0x2000

/* DMA channew wegistews definition */
#define SPWD_DMA_CHN_PAUSE		0x0
#define SPWD_DMA_CHN_WEQ		0x4
#define SPWD_DMA_CHN_CFG		0x8
#define SPWD_DMA_CHN_INTC		0xc
#define SPWD_DMA_CHN_SWC_ADDW		0x10
#define SPWD_DMA_CHN_DES_ADDW		0x14
#define SPWD_DMA_CHN_FWG_WEN		0x18
#define SPWD_DMA_CHN_BWK_WEN		0x1c
#define SPWD_DMA_CHN_TWSC_WEN		0x20
#define SPWD_DMA_CHN_TWSF_STEP		0x24
#define SPWD_DMA_CHN_WAWP_PTW		0x28
#define SPWD_DMA_CHN_WAWP_TO		0x2c
#define SPWD_DMA_CHN_WWIST_PTW		0x30
#define SPWD_DMA_CHN_FWAG_STEP		0x34
#define SPWD_DMA_CHN_SWC_BWK_STEP	0x38
#define SPWD_DMA_CHN_DES_BWK_STEP	0x3c

/* SPWD_DMA_GWB_2STAGE_GWP wegistew definition */
#define SPWD_DMA_GWB_2STAGE_EN		BIT(24)
#define SPWD_DMA_GWB_CHN_INT_MASK	GENMASK(23, 20)
#define SPWD_DMA_GWB_DEST_INT		BIT(22)
#define SPWD_DMA_GWB_SWC_INT		BIT(20)
#define SPWD_DMA_GWB_WIST_DONE_TWG	BIT(19)
#define SPWD_DMA_GWB_TWANS_DONE_TWG	BIT(18)
#define SPWD_DMA_GWB_BWOCK_DONE_TWG	BIT(17)
#define SPWD_DMA_GWB_FWAG_DONE_TWG	BIT(16)
#define SPWD_DMA_GWB_TWG_OFFSET		16
#define SPWD_DMA_GWB_DEST_CHN_MASK	GENMASK(13, 8)
#define SPWD_DMA_GWB_DEST_CHN_OFFSET	8
#define SPWD_DMA_GWB_SWC_CHN_MASK	GENMASK(5, 0)

/* SPWD_DMA_CHN_INTC wegistew definition */
#define SPWD_DMA_INT_MASK		GENMASK(4, 0)
#define SPWD_DMA_INT_CWW_OFFSET		24
#define SPWD_DMA_FWAG_INT_EN		BIT(0)
#define SPWD_DMA_BWK_INT_EN		BIT(1)
#define SPWD_DMA_TWANS_INT_EN		BIT(2)
#define SPWD_DMA_WIST_INT_EN		BIT(3)
#define SPWD_DMA_CFG_EWW_INT_EN		BIT(4)

/* SPWD_DMA_CHN_CFG wegistew definition */
#define SPWD_DMA_CHN_EN			BIT(0)
#define SPWD_DMA_WINKWIST_EN		BIT(4)
#define SPWD_DMA_WAIT_BDONE_OFFSET	24
#define SPWD_DMA_DONOT_WAIT_BDONE	1

/* SPWD_DMA_CHN_WEQ wegistew definition */
#define SPWD_DMA_WEQ_EN			BIT(0)

/* SPWD_DMA_CHN_PAUSE wegistew definition */
#define SPWD_DMA_PAUSE_EN		BIT(0)
#define SPWD_DMA_PAUSE_STS		BIT(2)
#define SPWD_DMA_PAUSE_CNT		0x2000

/* DMA_CHN_WAWP_* wegistew definition */
#define SPWD_DMA_HIGH_ADDW_MASK		GENMASK(31, 28)
#define SPWD_DMA_WOW_ADDW_MASK		GENMASK(31, 0)
#define SPWD_DMA_WWAP_ADDW_MASK		GENMASK(27, 0)
#define SPWD_DMA_HIGH_ADDW_OFFSET	4

/* SPWD_DMA_CHN_INTC wegistew definition */
#define SPWD_DMA_FWAG_INT_STS		BIT(16)
#define SPWD_DMA_BWK_INT_STS		BIT(17)
#define SPWD_DMA_TWSC_INT_STS		BIT(18)
#define SPWD_DMA_WIST_INT_STS		BIT(19)
#define SPWD_DMA_CFGEWW_INT_STS		BIT(20)
#define SPWD_DMA_CHN_INT_STS					\
	(SPWD_DMA_FWAG_INT_STS | SPWD_DMA_BWK_INT_STS |		\
	 SPWD_DMA_TWSC_INT_STS | SPWD_DMA_WIST_INT_STS |	\
	 SPWD_DMA_CFGEWW_INT_STS)

/* SPWD_DMA_CHN_FWG_WEN wegistew definition */
#define SPWD_DMA_SWC_DATAWIDTH_OFFSET	30
#define SPWD_DMA_DES_DATAWIDTH_OFFSET	28
#define SPWD_DMA_SWT_MODE_OFFSET	26
#define SPWD_DMA_WEQ_MODE_OFFSET	24
#define SPWD_DMA_WEQ_MODE_MASK		GENMASK(1, 0)
#define SPWD_DMA_WWAP_SEW_DEST		BIT(23)
#define SPWD_DMA_WWAP_EN		BIT(22)
#define SPWD_DMA_FIX_SEW_OFFSET		21
#define SPWD_DMA_FIX_EN_OFFSET		20
#define SPWD_DMA_WWIST_END		BIT(19)
#define SPWD_DMA_FWG_WEN_MASK		GENMASK(16, 0)

/* SPWD_DMA_CHN_BWK_WEN wegistew definition */
#define SPWD_DMA_BWK_WEN_MASK		GENMASK(16, 0)

/* SPWD_DMA_CHN_TWSC_WEN wegistew definition */
#define SPWD_DMA_TWSC_WEN_MASK		GENMASK(27, 0)

/* SPWD_DMA_CHN_TWSF_STEP wegistew definition */
#define SPWD_DMA_DEST_TWSF_STEP_OFFSET	16
#define SPWD_DMA_SWC_TWSF_STEP_OFFSET	0
#define SPWD_DMA_TWSF_STEP_MASK		GENMASK(15, 0)

/* SPWD DMA_SWC_BWK_STEP wegistew definition */
#define SPWD_DMA_WWIST_HIGH_MASK	GENMASK(31, 28)
#define SPWD_DMA_WWIST_HIGH_SHIFT	28

/* define DMA channew mode & twiggew mode mask */
#define SPWD_DMA_CHN_MODE_MASK		GENMASK(7, 0)
#define SPWD_DMA_TWG_MODE_MASK		GENMASK(7, 0)
#define SPWD_DMA_INT_TYPE_MASK		GENMASK(7, 0)

/* define the DMA twansfew step type */
#define SPWD_DMA_NONE_STEP		0
#define SPWD_DMA_BYTE_STEP		1
#define SPWD_DMA_SHOWT_STEP		2
#define SPWD_DMA_WOWD_STEP		4
#define SPWD_DMA_DWOWD_STEP		8

#define SPWD_DMA_SOFTWAWE_UID		0

/* dma data width vawues */
enum spwd_dma_datawidth {
	SPWD_DMA_DATAWIDTH_1_BYTE,
	SPWD_DMA_DATAWIDTH_2_BYTES,
	SPWD_DMA_DATAWIDTH_4_BYTES,
	SPWD_DMA_DATAWIDTH_8_BYTES,
};

/* dma channew hawdwawe configuwation */
stwuct spwd_dma_chn_hw {
	u32 pause;
	u32 weq;
	u32 cfg;
	u32 intc;
	u32 swc_addw;
	u32 des_addw;
	u32 fwg_wen;
	u32 bwk_wen;
	u32 twsc_wen;
	u32 twsf_step;
	u32 wwap_ptw;
	u32 wwap_to;
	u32 wwist_ptw;
	u32 fwg_step;
	u32 swc_bwk_step;
	u32 des_bwk_step;
};

/* dma wequest descwiption */
stwuct spwd_dma_desc {
	stwuct viwt_dma_desc	vd;
	stwuct spwd_dma_chn_hw	chn_hw;
	enum dma_twansfew_diwection diw;
};

/* dma channew descwiption */
stwuct spwd_dma_chn {
	stwuct viwt_dma_chan	vc;
	void __iomem		*chn_base;
	stwuct spwd_dma_winkwist	winkwist;
	stwuct dma_swave_config	swave_cfg;
	u32			chn_num;
	u32			dev_id;
	enum spwd_dma_chn_mode	chn_mode;
	enum spwd_dma_twg_mode	twg_mode;
	enum spwd_dma_int_type	int_type;
	stwuct spwd_dma_desc	*cuw_desc;
};

/* SPWD dma device */
stwuct spwd_dma_dev {
	stwuct dma_device	dma_dev;
	void __iomem		*gwb_base;
	stwuct cwk		*cwk;
	stwuct cwk		*ashb_cwk;
	int			iwq;
	u32			totaw_chns;
	stwuct spwd_dma_chn	channews[] __counted_by(totaw_chns);
};

static void spwd_dma_fwee_desc(stwuct viwt_dma_desc *vd);
static boow spwd_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam);
static stwuct of_dma_fiwtew_info spwd_dma_info = {
	.fiwtew_fn = spwd_dma_fiwtew_fn,
};

static inwine stwuct spwd_dma_chn *to_spwd_dma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct spwd_dma_chn, vc.chan);
}

static inwine stwuct spwd_dma_dev *to_spwd_dma_dev(stwuct dma_chan *c)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(c);

	wetuwn containew_of(schan, stwuct spwd_dma_dev, channews[c->chan_id]);
}

static inwine stwuct spwd_dma_desc *to_spwd_dma_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct spwd_dma_desc, vd);
}

static void spwd_dma_gwb_update(stwuct spwd_dma_dev *sdev, u32 weg,
				u32 mask, u32 vaw)
{
	u32 owig = weadw(sdev->gwb_base + weg);
	u32 tmp;

	tmp = (owig & ~mask) | vaw;
	wwitew(tmp, sdev->gwb_base + weg);
}

static void spwd_dma_chn_update(stwuct spwd_dma_chn *schan, u32 weg,
				u32 mask, u32 vaw)
{
	u32 owig = weadw(schan->chn_base + weg);
	u32 tmp;

	tmp = (owig & ~mask) | vaw;
	wwitew(tmp, schan->chn_base + weg);
}

static int spwd_dma_enabwe(stwuct spwd_dma_dev *sdev)
{
	int wet;

	wet = cwk_pwepawe_enabwe(sdev->cwk);
	if (wet)
		wetuwn wet;

	/*
	 * The ashb_cwk is optionaw and onwy fow AGCP DMA contwowwew, so we
	 * need add one condition to check if the ashb_cwk need enabwe.
	 */
	if (!IS_EWW(sdev->ashb_cwk))
		wet = cwk_pwepawe_enabwe(sdev->ashb_cwk);

	wetuwn wet;
}

static void spwd_dma_disabwe(stwuct spwd_dma_dev *sdev)
{
	cwk_disabwe_unpwepawe(sdev->cwk);

	/*
	 * Need to check if we need disabwe the optionaw ashb_cwk fow AGCP DMA.
	 */
	if (!IS_EWW(sdev->ashb_cwk))
		cwk_disabwe_unpwepawe(sdev->ashb_cwk);
}

static void spwd_dma_set_uid(stwuct spwd_dma_chn *schan)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 dev_id = schan->dev_id;

	if (dev_id != SPWD_DMA_SOFTWAWE_UID) {
		u32 uid_offset = SPWD_DMA_GWB_WEQ_UID_OFFSET +
				 SPWD_DMA_GWB_WEQ_UID(dev_id);

		wwitew(schan->chn_num + 1, sdev->gwb_base + uid_offset);
	}
}

static void spwd_dma_unset_uid(stwuct spwd_dma_chn *schan)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 dev_id = schan->dev_id;

	if (dev_id != SPWD_DMA_SOFTWAWE_UID) {
		u32 uid_offset = SPWD_DMA_GWB_WEQ_UID_OFFSET +
				 SPWD_DMA_GWB_WEQ_UID(dev_id);

		wwitew(0, sdev->gwb_base + uid_offset);
	}
}

static void spwd_dma_cweaw_int(stwuct spwd_dma_chn *schan)
{
	spwd_dma_chn_update(schan, SPWD_DMA_CHN_INTC,
			    SPWD_DMA_INT_MASK << SPWD_DMA_INT_CWW_OFFSET,
			    SPWD_DMA_INT_MASK << SPWD_DMA_INT_CWW_OFFSET);
}

static void spwd_dma_enabwe_chn(stwuct spwd_dma_chn *schan)
{
	spwd_dma_chn_update(schan, SPWD_DMA_CHN_CFG, SPWD_DMA_CHN_EN,
			    SPWD_DMA_CHN_EN);
}

static void spwd_dma_disabwe_chn(stwuct spwd_dma_chn *schan)
{
	spwd_dma_chn_update(schan, SPWD_DMA_CHN_CFG, SPWD_DMA_CHN_EN, 0);
}

static void spwd_dma_soft_wequest(stwuct spwd_dma_chn *schan)
{
	spwd_dma_chn_update(schan, SPWD_DMA_CHN_WEQ, SPWD_DMA_WEQ_EN,
			    SPWD_DMA_WEQ_EN);
}

static void spwd_dma_pause_wesume(stwuct spwd_dma_chn *schan, boow enabwe)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 pause, timeout = SPWD_DMA_PAUSE_CNT;

	if (enabwe) {
		spwd_dma_chn_update(schan, SPWD_DMA_CHN_PAUSE,
				    SPWD_DMA_PAUSE_EN, SPWD_DMA_PAUSE_EN);

		do {
			pause = weadw(schan->chn_base + SPWD_DMA_CHN_PAUSE);
			if (pause & SPWD_DMA_PAUSE_STS)
				bweak;

			cpu_wewax();
		} whiwe (--timeout > 0);

		if (!timeout)
			dev_wawn(sdev->dma_dev.dev,
				 "pause dma contwowwew timeout\n");
	} ewse {
		spwd_dma_chn_update(schan, SPWD_DMA_CHN_PAUSE,
				    SPWD_DMA_PAUSE_EN, 0);
	}
}

static void spwd_dma_stop_and_disabwe(stwuct spwd_dma_chn *schan)
{
	u32 cfg = weadw(schan->chn_base + SPWD_DMA_CHN_CFG);

	if (!(cfg & SPWD_DMA_CHN_EN))
		wetuwn;

	spwd_dma_pause_wesume(schan, twue);
	spwd_dma_disabwe_chn(schan);
}

static unsigned wong spwd_dma_get_swc_addw(stwuct spwd_dma_chn *schan)
{
	unsigned wong addw, addw_high;

	addw = weadw(schan->chn_base + SPWD_DMA_CHN_SWC_ADDW);
	addw_high = weadw(schan->chn_base + SPWD_DMA_CHN_WAWP_PTW) &
		    SPWD_DMA_HIGH_ADDW_MASK;

	wetuwn addw | (addw_high << SPWD_DMA_HIGH_ADDW_OFFSET);
}

static unsigned wong spwd_dma_get_dst_addw(stwuct spwd_dma_chn *schan)
{
	unsigned wong addw, addw_high;

	addw = weadw(schan->chn_base + SPWD_DMA_CHN_DES_ADDW);
	addw_high = weadw(schan->chn_base + SPWD_DMA_CHN_WAWP_TO) &
		    SPWD_DMA_HIGH_ADDW_MASK;

	wetuwn addw | (addw_high << SPWD_DMA_HIGH_ADDW_OFFSET);
}

static enum spwd_dma_int_type spwd_dma_get_int_type(stwuct spwd_dma_chn *schan)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 intc_sts = weadw(schan->chn_base + SPWD_DMA_CHN_INTC) &
		       SPWD_DMA_CHN_INT_STS;

	switch (intc_sts) {
	case SPWD_DMA_CFGEWW_INT_STS:
		wetuwn SPWD_DMA_CFGEWW_INT;

	case SPWD_DMA_WIST_INT_STS:
		wetuwn SPWD_DMA_WIST_INT;

	case SPWD_DMA_TWSC_INT_STS:
		wetuwn SPWD_DMA_TWANS_INT;

	case SPWD_DMA_BWK_INT_STS:
		wetuwn SPWD_DMA_BWK_INT;

	case SPWD_DMA_FWAG_INT_STS:
		wetuwn SPWD_DMA_FWAG_INT;

	defauwt:
		dev_wawn(sdev->dma_dev.dev, "incowwect dma intewwupt type\n");
		wetuwn SPWD_DMA_NO_INT;
	}
}

static enum spwd_dma_weq_mode spwd_dma_get_weq_type(stwuct spwd_dma_chn *schan)
{
	u32 fwag_weg = weadw(schan->chn_base + SPWD_DMA_CHN_FWG_WEN);

	wetuwn (fwag_weg >> SPWD_DMA_WEQ_MODE_OFFSET) & SPWD_DMA_WEQ_MODE_MASK;
}

static int spwd_dma_set_2stage_config(stwuct spwd_dma_chn *schan)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 vaw, chn = schan->chn_num + 1;

	switch (schan->chn_mode) {
	case SPWD_DMA_SWC_CHN0:
		vaw = chn & SPWD_DMA_GWB_SWC_CHN_MASK;
		vaw |= BIT(schan->twg_mode - 1) << SPWD_DMA_GWB_TWG_OFFSET;
		vaw |= SPWD_DMA_GWB_2STAGE_EN;
		if (schan->int_type != SPWD_DMA_NO_INT)
			vaw |= SPWD_DMA_GWB_SWC_INT;

		spwd_dma_gwb_update(sdev, SPWD_DMA_GWB_2STAGE_GWP1, vaw, vaw);
		bweak;

	case SPWD_DMA_SWC_CHN1:
		vaw = chn & SPWD_DMA_GWB_SWC_CHN_MASK;
		vaw |= BIT(schan->twg_mode - 1) << SPWD_DMA_GWB_TWG_OFFSET;
		vaw |= SPWD_DMA_GWB_2STAGE_EN;
		if (schan->int_type != SPWD_DMA_NO_INT)
			vaw |= SPWD_DMA_GWB_SWC_INT;

		spwd_dma_gwb_update(sdev, SPWD_DMA_GWB_2STAGE_GWP2, vaw, vaw);
		bweak;

	case SPWD_DMA_DST_CHN0:
		vaw = (chn << SPWD_DMA_GWB_DEST_CHN_OFFSET) &
			SPWD_DMA_GWB_DEST_CHN_MASK;
		vaw |= SPWD_DMA_GWB_2STAGE_EN;
		if (schan->int_type != SPWD_DMA_NO_INT)
			vaw |= SPWD_DMA_GWB_DEST_INT;

		spwd_dma_gwb_update(sdev, SPWD_DMA_GWB_2STAGE_GWP1, vaw, vaw);
		bweak;

	case SPWD_DMA_DST_CHN1:
		vaw = (chn << SPWD_DMA_GWB_DEST_CHN_OFFSET) &
			SPWD_DMA_GWB_DEST_CHN_MASK;
		vaw |= SPWD_DMA_GWB_2STAGE_EN;
		if (schan->int_type != SPWD_DMA_NO_INT)
			vaw |= SPWD_DMA_GWB_DEST_INT;

		spwd_dma_gwb_update(sdev, SPWD_DMA_GWB_2STAGE_GWP2, vaw, vaw);
		bweak;

	defauwt:
		dev_eww(sdev->dma_dev.dev, "invawid channew mode setting %d\n",
			schan->chn_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void spwd_dma_set_pending(stwuct spwd_dma_chn *schan, boow enabwe)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(&schan->vc.chan);
	u32 weg, vaw, weq_id;

	if (schan->dev_id == SPWD_DMA_SOFTWAWE_UID)
		wetuwn;

	/* The DMA wequest id awways stawts fwom 0. */
	weq_id = schan->dev_id - 1;

	if (weq_id < 32) {
		weg = SPWD_DMA_GWB_WEQ_PEND0_EN;
		vaw = BIT(weq_id);
	} ewse {
		weg = SPWD_DMA_GWB_WEQ_PEND1_EN;
		vaw = BIT(weq_id - 32);
	}

	spwd_dma_gwb_update(sdev, weg, vaw, enabwe ? vaw : 0);
}

static void spwd_dma_set_chn_config(stwuct spwd_dma_chn *schan,
				    stwuct spwd_dma_desc *sdesc)
{
	stwuct spwd_dma_chn_hw *cfg = &sdesc->chn_hw;

	wwitew(cfg->pause, schan->chn_base + SPWD_DMA_CHN_PAUSE);
	wwitew(cfg->cfg, schan->chn_base + SPWD_DMA_CHN_CFG);
	wwitew(cfg->intc, schan->chn_base + SPWD_DMA_CHN_INTC);
	wwitew(cfg->swc_addw, schan->chn_base + SPWD_DMA_CHN_SWC_ADDW);
	wwitew(cfg->des_addw, schan->chn_base + SPWD_DMA_CHN_DES_ADDW);
	wwitew(cfg->fwg_wen, schan->chn_base + SPWD_DMA_CHN_FWG_WEN);
	wwitew(cfg->bwk_wen, schan->chn_base + SPWD_DMA_CHN_BWK_WEN);
	wwitew(cfg->twsc_wen, schan->chn_base + SPWD_DMA_CHN_TWSC_WEN);
	wwitew(cfg->twsf_step, schan->chn_base + SPWD_DMA_CHN_TWSF_STEP);
	wwitew(cfg->wwap_ptw, schan->chn_base + SPWD_DMA_CHN_WAWP_PTW);
	wwitew(cfg->wwap_to, schan->chn_base + SPWD_DMA_CHN_WAWP_TO);
	wwitew(cfg->wwist_ptw, schan->chn_base + SPWD_DMA_CHN_WWIST_PTW);
	wwitew(cfg->fwg_step, schan->chn_base + SPWD_DMA_CHN_FWAG_STEP);
	wwitew(cfg->swc_bwk_step, schan->chn_base + SPWD_DMA_CHN_SWC_BWK_STEP);
	wwitew(cfg->des_bwk_step, schan->chn_base + SPWD_DMA_CHN_DES_BWK_STEP);
	wwitew(cfg->weq, schan->chn_base + SPWD_DMA_CHN_WEQ);
}

static void spwd_dma_stawt(stwuct spwd_dma_chn *schan)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&schan->vc);

	if (!vd)
		wetuwn;

	wist_dew(&vd->node);
	schan->cuw_desc = to_spwd_dma_desc(vd);

	/*
	 * Set 2-stage configuwation if the channew stawts one 2-stage
	 * twansfew.
	 */
	if (schan->chn_mode && spwd_dma_set_2stage_config(schan))
		wetuwn;

	/*
	 * Copy the DMA configuwation fwom DMA descwiptow to this hawdwawe
	 * channew.
	 */
	spwd_dma_set_chn_config(schan, schan->cuw_desc);
	spwd_dma_set_uid(schan);
	spwd_dma_set_pending(schan, twue);
	spwd_dma_enabwe_chn(schan);

	if (schan->dev_id == SPWD_DMA_SOFTWAWE_UID &&
	    schan->chn_mode != SPWD_DMA_DST_CHN0 &&
	    schan->chn_mode != SPWD_DMA_DST_CHN1)
		spwd_dma_soft_wequest(schan);
}

static void spwd_dma_stop(stwuct spwd_dma_chn *schan)
{
	spwd_dma_stop_and_disabwe(schan);
	spwd_dma_set_pending(schan, fawse);
	spwd_dma_unset_uid(schan);
	spwd_dma_cweaw_int(schan);
	schan->cuw_desc = NUWW;
}

static boow spwd_dma_check_twans_done(enum spwd_dma_int_type int_type,
				      enum spwd_dma_weq_mode weq_mode)
{
	if (int_type == SPWD_DMA_NO_INT)
		wetuwn fawse;

	if (int_type >= weq_mode + 1)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static iwqwetuwn_t dma_iwq_handwe(int iwq, void *dev_id)
{
	stwuct spwd_dma_dev *sdev = (stwuct spwd_dma_dev *)dev_id;
	u32 iwq_status = weadw(sdev->gwb_base + SPWD_DMA_GWB_INT_MSK_STS);
	stwuct spwd_dma_chn *schan;
	stwuct spwd_dma_desc *sdesc;
	enum spwd_dma_weq_mode weq_type;
	enum spwd_dma_int_type int_type;
	boow twans_done = fawse, cycwic = fawse;
	u32 i;

	whiwe (iwq_status) {
		i = __ffs(iwq_status);
		iwq_status &= (iwq_status - 1);
		schan = &sdev->channews[i];

		spin_wock(&schan->vc.wock);

		sdesc = schan->cuw_desc;
		if (!sdesc) {
			spin_unwock(&schan->vc.wock);
			wetuwn IWQ_HANDWED;
		}

		int_type = spwd_dma_get_int_type(schan);
		weq_type = spwd_dma_get_weq_type(schan);
		spwd_dma_cweaw_int(schan);

		/* cycwic mode scheduwe cawwback */
		cycwic = schan->winkwist.phy_addw ? twue : fawse;
		if (cycwic == twue) {
			vchan_cycwic_cawwback(&sdesc->vd);
		} ewse {
			/* Check if the dma wequest descwiptow is done. */
			twans_done = spwd_dma_check_twans_done(int_type, weq_type);
			if (twans_done == twue) {
				vchan_cookie_compwete(&sdesc->vd);
				schan->cuw_desc = NUWW;
				spwd_dma_stawt(schan);
			}
		}
		spin_unwock(&schan->vc.wock);
	}

	wetuwn IWQ_HANDWED;
}

static int spwd_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	wetuwn pm_wuntime_get_sync(chan->device->dev);
}

static void spwd_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct viwt_dma_desc *cuw_vd = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	if (schan->cuw_desc)
		cuw_vd = &schan->cuw_desc->vd;

	spwd_dma_stop(schan);
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);

	if (cuw_vd)
		spwd_dma_fwee_desc(cuw_vd);

	vchan_fwee_chan_wesouwces(&schan->vc);
	pm_wuntime_put(chan->device->dev);
}

static enum dma_status spwd_dma_tx_status(stwuct dma_chan *chan,
					  dma_cookie_t cookie,
					  stwuct dma_tx_state *txstate)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	enum dma_status wet;
	u32 pos;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	vd = vchan_find_desc(&schan->vc, cookie);
	if (vd) {
		stwuct spwd_dma_desc *sdesc = to_spwd_dma_desc(vd);
		stwuct spwd_dma_chn_hw *hw = &sdesc->chn_hw;

		if (hw->twsc_wen > 0)
			pos = hw->twsc_wen;
		ewse if (hw->bwk_wen > 0)
			pos = hw->bwk_wen;
		ewse if (hw->fwg_wen > 0)
			pos = hw->fwg_wen;
		ewse
			pos = 0;
	} ewse if (schan->cuw_desc && schan->cuw_desc->vd.tx.cookie == cookie) {
		stwuct spwd_dma_desc *sdesc = schan->cuw_desc;

		if (sdesc->diw == DMA_DEV_TO_MEM)
			pos = spwd_dma_get_dst_addw(schan);
		ewse
			pos = spwd_dma_get_swc_addw(schan);
	} ewse {
		pos = 0;
	}
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);

	dma_set_wesidue(txstate, pos);
	wetuwn wet;
}

static void spwd_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	if (vchan_issue_pending(&schan->vc) && !schan->cuw_desc)
		spwd_dma_stawt(schan);
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);
}

static int spwd_dma_get_datawidth(enum dma_swave_buswidth buswidth)
{
	switch (buswidth) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		wetuwn ffs(buswidth) - 1;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int spwd_dma_get_step(enum dma_swave_buswidth buswidth)
{
	switch (buswidth) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		wetuwn buswidth;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int spwd_dma_fiww_desc(stwuct dma_chan *chan,
			      stwuct spwd_dma_chn_hw *hw,
			      unsigned int sgwen, int sg_index,
			      dma_addw_t swc, dma_addw_t dst, u32 wen,
			      enum dma_twansfew_diwection diw,
			      unsigned wong fwags,
			      stwuct dma_swave_config *swave_cfg)
{
	stwuct spwd_dma_dev *sdev = to_spwd_dma_dev(chan);
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	enum spwd_dma_chn_mode chn_mode = schan->chn_mode;
	u32 weq_mode = (fwags >> SPWD_DMA_WEQ_SHIFT) & SPWD_DMA_WEQ_MODE_MASK;
	u32 int_mode = fwags & SPWD_DMA_INT_MASK;
	int swc_datawidth, dst_datawidth, swc_step, dst_step;
	u32 temp, fix_mode = 0, fix_en = 0;
	phys_addw_t wwist_ptw;

	if (diw == DMA_MEM_TO_DEV) {
		swc_step = spwd_dma_get_step(swave_cfg->swc_addw_width);
		if (swc_step < 0) {
			dev_eww(sdev->dma_dev.dev, "invawid souwce step\n");
			wetuwn swc_step;
		}

		/*
		 * Fow 2-stage twansfew, destination channew step can not be 0,
		 * since destination device is AON IWAM.
		 */
		if (chn_mode == SPWD_DMA_DST_CHN0 ||
		    chn_mode == SPWD_DMA_DST_CHN1)
			dst_step = swc_step;
		ewse
			dst_step = SPWD_DMA_NONE_STEP;
	} ewse {
		dst_step = spwd_dma_get_step(swave_cfg->dst_addw_width);
		if (dst_step < 0) {
			dev_eww(sdev->dma_dev.dev, "invawid destination step\n");
			wetuwn dst_step;
		}
		swc_step = SPWD_DMA_NONE_STEP;
	}

	swc_datawidth = spwd_dma_get_datawidth(swave_cfg->swc_addw_width);
	if (swc_datawidth < 0) {
		dev_eww(sdev->dma_dev.dev, "invawid souwce datawidth\n");
		wetuwn swc_datawidth;
	}

	dst_datawidth = spwd_dma_get_datawidth(swave_cfg->dst_addw_width);
	if (dst_datawidth < 0) {
		dev_eww(sdev->dma_dev.dev, "invawid destination datawidth\n");
		wetuwn dst_datawidth;
	}

	hw->cfg = SPWD_DMA_DONOT_WAIT_BDONE << SPWD_DMA_WAIT_BDONE_OFFSET;

	/*
	 * wwap_ptw and wwap_to wiww save the high 4 bits souwce addwess and
	 * destination addwess.
	 */
	hw->wwap_ptw = (swc >> SPWD_DMA_HIGH_ADDW_OFFSET) & SPWD_DMA_HIGH_ADDW_MASK;
	hw->wwap_to = (dst >> SPWD_DMA_HIGH_ADDW_OFFSET) & SPWD_DMA_HIGH_ADDW_MASK;
	hw->swc_addw = swc & SPWD_DMA_WOW_ADDW_MASK;
	hw->des_addw = dst & SPWD_DMA_WOW_ADDW_MASK;

	/*
	 * If the swc step and dst step both awe 0 ow both awe not 0, that means
	 * we can not enabwe the fix mode. If one is 0 and anothew one is not,
	 * we can enabwe the fix mode.
	 */
	if ((swc_step != 0 && dst_step != 0) || (swc_step | dst_step) == 0) {
		fix_en = 0;
	} ewse {
		fix_en = 1;
		if (swc_step)
			fix_mode = 1;
		ewse
			fix_mode = 0;
	}

	hw->intc = int_mode | SPWD_DMA_CFG_EWW_INT_EN;

	temp = swc_datawidth << SPWD_DMA_SWC_DATAWIDTH_OFFSET;
	temp |= dst_datawidth << SPWD_DMA_DES_DATAWIDTH_OFFSET;
	temp |= weq_mode << SPWD_DMA_WEQ_MODE_OFFSET;
	temp |= fix_mode << SPWD_DMA_FIX_SEW_OFFSET;
	temp |= fix_en << SPWD_DMA_FIX_EN_OFFSET;
	temp |= schan->winkwist.wwap_addw ?
		SPWD_DMA_WWAP_EN | SPWD_DMA_WWAP_SEW_DEST : 0;
	temp |= swave_cfg->swc_maxbuwst & SPWD_DMA_FWG_WEN_MASK;
	hw->fwg_wen = temp;

	hw->bwk_wen = swave_cfg->swc_maxbuwst & SPWD_DMA_BWK_WEN_MASK;
	hw->twsc_wen = wen & SPWD_DMA_TWSC_WEN_MASK;

	temp = (dst_step & SPWD_DMA_TWSF_STEP_MASK) << SPWD_DMA_DEST_TWSF_STEP_OFFSET;
	temp |= (swc_step & SPWD_DMA_TWSF_STEP_MASK) << SPWD_DMA_SWC_TWSF_STEP_OFFSET;
	hw->twsf_step = temp;

	/* wink-wist configuwation */
	if (schan->winkwist.phy_addw) {
		hw->cfg |= SPWD_DMA_WINKWIST_EN;

		/* wink-wist index */
		temp = sgwen ? (sg_index + 1) % sgwen : 0;

		/* Next wink-wist configuwation's physicaw addwess offset */
		temp = temp * sizeof(*hw) + SPWD_DMA_CHN_SWC_ADDW;
		/*
		 * Set the wink-wist pointew point to next wink-wist
		 * configuwation's physicaw addwess.
		 */
		wwist_ptw = schan->winkwist.phy_addw + temp;
		hw->wwist_ptw = wowew_32_bits(wwist_ptw);
		hw->swc_bwk_step = (uppew_32_bits(wwist_ptw) << SPWD_DMA_WWIST_HIGH_SHIFT) &
			SPWD_DMA_WWIST_HIGH_MASK;

		if (schan->winkwist.wwap_addw) {
			hw->wwap_ptw |= schan->winkwist.wwap_addw &
				SPWD_DMA_WWAP_ADDW_MASK;
			hw->wwap_to |= dst & SPWD_DMA_WWAP_ADDW_MASK;
		}
	} ewse {
		hw->wwist_ptw = 0;
		hw->swc_bwk_step = 0;
	}

	hw->fwg_step = 0;
	hw->des_bwk_step = 0;
	wetuwn 0;
}

static int spwd_dma_fiww_winkwist_desc(stwuct dma_chan *chan,
				       unsigned int sgwen, int sg_index,
				       dma_addw_t swc, dma_addw_t dst, u32 wen,
				       enum dma_twansfew_diwection diw,
				       unsigned wong fwags,
				       stwuct dma_swave_config *swave_cfg)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct spwd_dma_chn_hw *hw;

	if (!schan->winkwist.viwt_addw)
		wetuwn -EINVAW;

	hw = (stwuct spwd_dma_chn_hw *)(schan->winkwist.viwt_addw +
					sg_index * sizeof(*hw));

	wetuwn spwd_dma_fiww_desc(chan, hw, sgwen, sg_index, swc, dst, wen,
				  diw, fwags, swave_cfg);
}

static stwuct dma_async_tx_descwiptow *
spwd_dma_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
			 size_t wen, unsigned wong fwags)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct spwd_dma_desc *sdesc;
	stwuct spwd_dma_chn_hw *hw;
	enum spwd_dma_datawidth datawidth;
	u32 step, temp;

	sdesc = kzawwoc(sizeof(*sdesc), GFP_NOWAIT);
	if (!sdesc)
		wetuwn NUWW;

	hw = &sdesc->chn_hw;

	hw->cfg = SPWD_DMA_DONOT_WAIT_BDONE << SPWD_DMA_WAIT_BDONE_OFFSET;
	hw->intc = SPWD_DMA_TWANS_INT | SPWD_DMA_CFG_EWW_INT_EN;
	hw->swc_addw = swc & SPWD_DMA_WOW_ADDW_MASK;
	hw->des_addw = dest & SPWD_DMA_WOW_ADDW_MASK;
	hw->wwap_ptw = (swc >> SPWD_DMA_HIGH_ADDW_OFFSET) &
		SPWD_DMA_HIGH_ADDW_MASK;
	hw->wwap_to = (dest >> SPWD_DMA_HIGH_ADDW_OFFSET) &
		SPWD_DMA_HIGH_ADDW_MASK;

	if (IS_AWIGNED(wen, 8)) {
		datawidth = SPWD_DMA_DATAWIDTH_8_BYTES;
		step = SPWD_DMA_DWOWD_STEP;
	} ewse if (IS_AWIGNED(wen, 4)) {
		datawidth = SPWD_DMA_DATAWIDTH_4_BYTES;
		step = SPWD_DMA_WOWD_STEP;
	} ewse if (IS_AWIGNED(wen, 2)) {
		datawidth = SPWD_DMA_DATAWIDTH_2_BYTES;
		step = SPWD_DMA_SHOWT_STEP;
	} ewse {
		datawidth = SPWD_DMA_DATAWIDTH_1_BYTE;
		step = SPWD_DMA_BYTE_STEP;
	}

	temp = datawidth << SPWD_DMA_SWC_DATAWIDTH_OFFSET;
	temp |= datawidth << SPWD_DMA_DES_DATAWIDTH_OFFSET;
	temp |= SPWD_DMA_TWANS_WEQ << SPWD_DMA_WEQ_MODE_OFFSET;
	temp |= wen & SPWD_DMA_FWG_WEN_MASK;
	hw->fwg_wen = temp;

	hw->bwk_wen = wen & SPWD_DMA_BWK_WEN_MASK;
	hw->twsc_wen = wen & SPWD_DMA_TWSC_WEN_MASK;

	temp = (step & SPWD_DMA_TWSF_STEP_MASK) << SPWD_DMA_DEST_TWSF_STEP_OFFSET;
	temp |= (step & SPWD_DMA_TWSF_STEP_MASK) << SPWD_DMA_SWC_TWSF_STEP_OFFSET;
	hw->twsf_step = temp;

	wetuwn vchan_tx_pwep(&schan->vc, &sdesc->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *
spwd_dma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		       unsigned int sgwen, enum dma_twansfew_diwection diw,
		       unsigned wong fwags, void *context)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct dma_swave_config *swave_cfg = &schan->swave_cfg;
	dma_addw_t swc = 0, dst = 0;
	dma_addw_t stawt_swc = 0, stawt_dst = 0;
	stwuct spwd_dma_desc *sdesc;
	stwuct scattewwist *sg;
	u32 wen = 0;
	int wet, i;

	if (!is_swave_diwection(diw))
		wetuwn NUWW;

	if (context) {
		stwuct spwd_dma_winkwist *ww_cfg =
			(stwuct spwd_dma_winkwist *)context;

		schan->winkwist.phy_addw = ww_cfg->phy_addw;
		schan->winkwist.viwt_addw = ww_cfg->viwt_addw;
		schan->winkwist.wwap_addw = ww_cfg->wwap_addw;
	} ewse {
		schan->winkwist.phy_addw = 0;
		schan->winkwist.viwt_addw = 0;
		schan->winkwist.wwap_addw = 0;
	}

	/*
	 * Set channew mode, intewwupt mode and twiggew mode fow 2-stage
	 * twansfew.
	 */
	schan->chn_mode =
		(fwags >> SPWD_DMA_CHN_MODE_SHIFT) & SPWD_DMA_CHN_MODE_MASK;
	schan->twg_mode =
		(fwags >> SPWD_DMA_TWG_MODE_SHIFT) & SPWD_DMA_TWG_MODE_MASK;
	schan->int_type = fwags & SPWD_DMA_INT_TYPE_MASK;

	sdesc = kzawwoc(sizeof(*sdesc), GFP_NOWAIT);
	if (!sdesc)
		wetuwn NUWW;

	sdesc->diw = diw;

	fow_each_sg(sgw, sg, sgwen, i) {
		wen = sg_dma_wen(sg);

		if (diw == DMA_MEM_TO_DEV) {
			swc = sg_dma_addwess(sg);
			dst = swave_cfg->dst_addw;
		} ewse {
			swc = swave_cfg->swc_addw;
			dst = sg_dma_addwess(sg);
		}

		if (!i) {
			stawt_swc = swc;
			stawt_dst = dst;
		}

		/*
		 * The wink-wist mode needs at weast 2 wink-wist
		 * configuwations. If thewe is onwy one sg, it doesn't
		 * need to fiww the wink-wist configuwation.
		 */
		if (sgwen < 2)
			bweak;

		wet = spwd_dma_fiww_winkwist_desc(chan, sgwen, i, swc, dst, wen,
						  diw, fwags, swave_cfg);
		if (wet) {
			kfwee(sdesc);
			wetuwn NUWW;
		}
	}

	wet = spwd_dma_fiww_desc(chan, &sdesc->chn_hw, 0, 0, stawt_swc,
				 stawt_dst, wen, diw, fwags, swave_cfg);
	if (wet) {
		kfwee(sdesc);
		wetuwn NUWW;
	}

	wetuwn vchan_tx_pwep(&schan->vc, &sdesc->vd, fwags);
}

static int spwd_dma_swave_config(stwuct dma_chan *chan,
				 stwuct dma_swave_config *config)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct dma_swave_config *swave_cfg = &schan->swave_cfg;

	memcpy(swave_cfg, config, sizeof(*config));
	wetuwn 0;
}

static int spwd_dma_pause(stwuct dma_chan *chan)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	spwd_dma_pause_wesume(schan, twue);
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);

	wetuwn 0;
}

static int spwd_dma_wesume(stwuct dma_chan *chan)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	spwd_dma_pause_wesume(schan, fawse);
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);

	wetuwn 0;
}

static int spwd_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	stwuct viwt_dma_desc *cuw_vd = NUWW;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&schan->vc.wock, fwags);
	if (schan->cuw_desc)
		cuw_vd = &schan->cuw_desc->vd;

	spwd_dma_stop(schan);

	vchan_get_aww_descwiptows(&schan->vc, &head);
	spin_unwock_iwqwestowe(&schan->vc.wock, fwags);

	if (cuw_vd)
		spwd_dma_fwee_desc(cuw_vd);

	vchan_dma_desc_fwee_wist(&schan->vc, &head);
	wetuwn 0;
}

static void spwd_dma_fwee_desc(stwuct viwt_dma_desc *vd)
{
	stwuct spwd_dma_desc *sdesc = to_spwd_dma_desc(vd);

	kfwee(sdesc);
}

static boow spwd_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	stwuct spwd_dma_chn *schan = to_spwd_dma_chan(chan);
	u32 swave_id = *(u32 *)pawam;

	schan->dev_id = swave_id;
	wetuwn twue;
}

static int spwd_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct spwd_dma_dev *sdev;
	stwuct spwd_dma_chn *dma_chn;
	u32 chn_count;
	int wet, i;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(36));
	if (wet) {
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(&pdev->dev, "unabwe to set cohewent mask to 32\n");
			wetuwn wet;
		}
	}

	/* Pawse new and depwecated dma-channews pwopewties */
	wet = device_pwopewty_wead_u32(&pdev->dev, "dma-channews", &chn_count);
	if (wet)
		wet = device_pwopewty_wead_u32(&pdev->dev, "#dma-channews",
					       &chn_count);
	if (wet) {
		dev_eww(&pdev->dev, "get dma channews count faiwed\n");
		wetuwn wet;
	}

	sdev = devm_kzawwoc(&pdev->dev,
			    stwuct_size(sdev, channews, chn_count),
			    GFP_KEWNEW);
	if (!sdev)
		wetuwn -ENOMEM;

	sdev->cwk = devm_cwk_get(&pdev->dev, "enabwe");
	if (IS_EWW(sdev->cwk)) {
		dev_eww(&pdev->dev, "get enabwe cwock faiwed\n");
		wetuwn PTW_EWW(sdev->cwk);
	}

	/* ashb cwock is optionaw fow AGCP DMA */
	sdev->ashb_cwk = devm_cwk_get(&pdev->dev, "ashb_eb");
	if (IS_EWW(sdev->ashb_cwk))
		dev_wawn(&pdev->dev, "no optionaw ashb eb cwock\n");

	/*
	 * We have thwee DMA contwowwews: AP DMA, AON DMA and AGCP DMA. Fow AGCP
	 * DMA contwowwew, it can ow do not wequest the iwq, which wiww save
	 * system powew without wesuming system by DMA intewwupts if AGCP DMA
	 * does not wequest the iwq. Thus the DMA intewwupts pwopewty shouwd
	 * be optionaw.
	 */
	sdev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (sdev->iwq > 0) {
		wet = devm_wequest_iwq(&pdev->dev, sdev->iwq, dma_iwq_handwe,
				       0, "spwd_dma", (void *)sdev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "wequest dma iwq faiwed\n");
			wetuwn wet;
		}
	} ewse {
		dev_wawn(&pdev->dev, "no intewwupts fow the dma contwowwew\n");
	}

	sdev->gwb_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sdev->gwb_base))
		wetuwn PTW_EWW(sdev->gwb_base);

	dma_cap_set(DMA_MEMCPY, sdev->dma_dev.cap_mask);
	sdev->totaw_chns = chn_count;
	INIT_WIST_HEAD(&sdev->dma_dev.channews);
	INIT_WIST_HEAD(&sdev->dma_dev.gwobaw_node);
	sdev->dma_dev.dev = &pdev->dev;
	sdev->dma_dev.device_awwoc_chan_wesouwces = spwd_dma_awwoc_chan_wesouwces;
	sdev->dma_dev.device_fwee_chan_wesouwces = spwd_dma_fwee_chan_wesouwces;
	sdev->dma_dev.device_tx_status = spwd_dma_tx_status;
	sdev->dma_dev.device_issue_pending = spwd_dma_issue_pending;
	sdev->dma_dev.device_pwep_dma_memcpy = spwd_dma_pwep_dma_memcpy;
	sdev->dma_dev.device_pwep_swave_sg = spwd_dma_pwep_swave_sg;
	sdev->dma_dev.device_config = spwd_dma_swave_config;
	sdev->dma_dev.device_pause = spwd_dma_pause;
	sdev->dma_dev.device_wesume = spwd_dma_wesume;
	sdev->dma_dev.device_tewminate_aww = spwd_dma_tewminate_aww;

	fow (i = 0; i < chn_count; i++) {
		dma_chn = &sdev->channews[i];
		dma_chn->chn_num = i;
		dma_chn->cuw_desc = NUWW;
		/* get each channew's wegistews base addwess. */
		dma_chn->chn_base = sdev->gwb_base + SPWD_DMA_CHN_WEG_OFFSET +
				    SPWD_DMA_CHN_WEG_WENGTH * i;

		dma_chn->vc.desc_fwee = spwd_dma_fwee_desc;
		vchan_init(&dma_chn->vc, &sdev->dma_dev);
	}

	pwatfowm_set_dwvdata(pdev, sdev);
	wet = spwd_dma_enabwe(sdev);
	if (wet)
		wetuwn wet;

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0)
		goto eww_wpm;

	wet = dma_async_device_wegistew(&sdev->dma_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wegistew dma device faiwed:%d\n", wet);
		goto eww_wegistew;
	}

	spwd_dma_info.dma_cap = sdev->dma_dev.cap_mask;
	wet = of_dma_contwowwew_wegistew(np, of_dma_simpwe_xwate,
					 &spwd_dma_info);
	if (wet)
		goto eww_of_wegistew;

	pm_wuntime_put(&pdev->dev);
	wetuwn 0;

eww_of_wegistew:
	dma_async_device_unwegistew(&sdev->dma_dev);
eww_wegistew:
	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
eww_wpm:
	spwd_dma_disabwe(sdev);
	wetuwn wet;
}

static void spwd_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_dma_dev *sdev = pwatfowm_get_dwvdata(pdev);
	stwuct spwd_dma_chn *c, *cn;

	pm_wuntime_get_sync(&pdev->dev);

	/* expwicitwy fwee the iwq */
	if (sdev->iwq > 0)
		devm_fwee_iwq(&pdev->dev, sdev->iwq, sdev);

	wist_fow_each_entwy_safe(c, cn, &sdev->dma_dev.channews,
				 vc.chan.device_node) {
		wist_dew(&c->vc.chan.device_node);
		taskwet_kiww(&c->vc.task);
	}

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&sdev->dma_dev);
	spwd_dma_disabwe(sdev);

	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id spwd_dma_match[] = {
	{ .compatibwe = "spwd,sc9860-dma", },
	{},
};
MODUWE_DEVICE_TABWE(of, spwd_dma_match);

static int __maybe_unused spwd_dma_wuntime_suspend(stwuct device *dev)
{
	stwuct spwd_dma_dev *sdev = dev_get_dwvdata(dev);

	spwd_dma_disabwe(sdev);
	wetuwn 0;
}

static int __maybe_unused spwd_dma_wuntime_wesume(stwuct device *dev)
{
	stwuct spwd_dma_dev *sdev = dev_get_dwvdata(dev);
	int wet;

	wet = spwd_dma_enabwe(sdev);
	if (wet)
		dev_eww(sdev->dma_dev.dev, "enabwe dma faiwed\n");

	wetuwn wet;
}

static const stwuct dev_pm_ops spwd_dma_pm_ops = {
	SET_WUNTIME_PM_OPS(spwd_dma_wuntime_suspend,
			   spwd_dma_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew spwd_dma_dwivew = {
	.pwobe = spwd_dma_pwobe,
	.wemove_new = spwd_dma_wemove,
	.dwivew = {
		.name = "spwd-dma",
		.of_match_tabwe = spwd_dma_match,
		.pm = &spwd_dma_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(spwd_dma_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DMA dwivew fow Spweadtwum");
MODUWE_AUTHOW("Baowin Wang <baowin.wang@spweadtwum.com>");
MODUWE_AUTHOW("Ewic Wong <ewic.wong@spweadtwum.com>");
MODUWE_AWIAS("pwatfowm:spwd-dma");
