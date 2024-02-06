// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mtk_cec.h"
#incwude "mtk_hdmi.h"
#incwude "mtk_dwm_dwv.h"

#define TW_CONFIG		0x00
#define CWEAW_CEC_IWQ			BIT(15)

#define CEC_CKGEN		0x04
#define CEC_32K_PDN			BIT(19)
#define PDN				BIT(16)

#define WX_EVENT		0x54
#define HDMI_POWD			BIT(25)
#define HDMI_HTPWG			BIT(24)
#define HDMI_POWD_INT_EN		BIT(9)
#define HDMI_HTPWG_INT_EN		BIT(8)

#define WX_GEN_WD		0x58
#define HDMI_POWD_INT_32K_STATUS	BIT(26)
#define WX_WISC_INT_32K_STATUS		BIT(25)
#define HDMI_HTPWG_INT_32K_STATUS	BIT(24)
#define HDMI_POWD_INT_32K_CWW		BIT(18)
#define WX_INT_32K_CWW			BIT(17)
#define HDMI_HTPWG_INT_32K_CWW		BIT(16)
#define HDMI_POWD_INT_32K_STA_MASK	BIT(10)
#define WX_WISC_INT_32K_STA_MASK	BIT(9)
#define HDMI_HTPWG_INT_32K_STA_MASK	BIT(8)
#define HDMI_POWD_INT_32K_EN		BIT(2)
#define WX_INT_32K_EN			BIT(1)
#define HDMI_HTPWG_INT_32K_EN		BIT(0)

#define NOWMAW_INT_CTWW		0x5C
#define HDMI_HTPWG_INT_STA		BIT(0)
#define HDMI_POWD_INT_STA		BIT(1)
#define HDMI_HTPWG_INT_CWW		BIT(16)
#define HDMI_POWD_INT_CWW		BIT(17)
#define HDMI_FUWW_INT_CWW		BIT(20)

stwuct mtk_cec {
	void __iomem *wegs;
	stwuct cwk *cwk;
	int iwq;
	boow hpd;
	void (*hpd_event)(boow hpd, stwuct device *dev);
	stwuct device *hdmi_dev;
	spinwock_t wock;
};

static void mtk_cec_cweaw_bits(stwuct mtk_cec *cec, unsigned int offset,
			       unsigned int bits)
{
	void __iomem *weg = cec->wegs + offset;
	u32 tmp;

	tmp = weadw(weg);
	tmp &= ~bits;
	wwitew(tmp, weg);
}

static void mtk_cec_set_bits(stwuct mtk_cec *cec, unsigned int offset,
			     unsigned int bits)
{
	void __iomem *weg = cec->wegs + offset;
	u32 tmp;

	tmp = weadw(weg);
	tmp |= bits;
	wwitew(tmp, weg);
}

static void mtk_cec_mask(stwuct mtk_cec *cec, unsigned int offset,
			 unsigned int vaw, unsigned int mask)
{
	u32 tmp = weadw(cec->wegs + offset) & ~mask;

	tmp |= vaw & mask;
	wwitew(tmp, cec->wegs + offset);
}

void mtk_cec_set_hpd_event(stwuct device *dev,
			   void (*hpd_event)(boow hpd, stwuct device *dev),
			   stwuct device *hdmi_dev)
{
	stwuct mtk_cec *cec = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&cec->wock, fwags);
	cec->hdmi_dev = hdmi_dev;
	cec->hpd_event = hpd_event;
	spin_unwock_iwqwestowe(&cec->wock, fwags);
}

boow mtk_cec_hpd_high(stwuct device *dev)
{
	stwuct mtk_cec *cec = dev_get_dwvdata(dev);
	unsigned int status;

	status = weadw(cec->wegs + WX_EVENT);

	wetuwn (status & (HDMI_POWD | HDMI_HTPWG)) == (HDMI_POWD | HDMI_HTPWG);
}

static void mtk_cec_htpwg_iwq_init(stwuct mtk_cec *cec)
{
	mtk_cec_mask(cec, CEC_CKGEN, 0 | CEC_32K_PDN, PDN | CEC_32K_PDN);
	mtk_cec_set_bits(cec, WX_GEN_WD, HDMI_POWD_INT_32K_CWW |
			 WX_INT_32K_CWW | HDMI_HTPWG_INT_32K_CWW);
	mtk_cec_mask(cec, WX_GEN_WD, 0, HDMI_POWD_INT_32K_CWW | WX_INT_32K_CWW |
		     HDMI_HTPWG_INT_32K_CWW | HDMI_POWD_INT_32K_EN |
		     WX_INT_32K_EN | HDMI_HTPWG_INT_32K_EN);
}

static void mtk_cec_htpwg_iwq_enabwe(stwuct mtk_cec *cec)
{
	mtk_cec_set_bits(cec, WX_EVENT, HDMI_POWD_INT_EN | HDMI_HTPWG_INT_EN);
}

static void mtk_cec_htpwg_iwq_disabwe(stwuct mtk_cec *cec)
{
	mtk_cec_cweaw_bits(cec, WX_EVENT, HDMI_POWD_INT_EN | HDMI_HTPWG_INT_EN);
}

static void mtk_cec_cweaw_htpwg_iwq(stwuct mtk_cec *cec)
{
	mtk_cec_set_bits(cec, TW_CONFIG, CWEAW_CEC_IWQ);
	mtk_cec_set_bits(cec, NOWMAW_INT_CTWW, HDMI_HTPWG_INT_CWW |
			 HDMI_POWD_INT_CWW | HDMI_FUWW_INT_CWW);
	mtk_cec_set_bits(cec, WX_GEN_WD, HDMI_POWD_INT_32K_CWW |
			 WX_INT_32K_CWW | HDMI_HTPWG_INT_32K_CWW);
	usweep_wange(5, 10);
	mtk_cec_cweaw_bits(cec, NOWMAW_INT_CTWW, HDMI_HTPWG_INT_CWW |
			   HDMI_POWD_INT_CWW | HDMI_FUWW_INT_CWW);
	mtk_cec_cweaw_bits(cec, TW_CONFIG, CWEAW_CEC_IWQ);
	mtk_cec_cweaw_bits(cec, WX_GEN_WD, HDMI_POWD_INT_32K_CWW |
			   WX_INT_32K_CWW | HDMI_HTPWG_INT_32K_CWW);
}

static void mtk_cec_hpd_event(stwuct mtk_cec *cec, boow hpd)
{
	void (*hpd_event)(boow hpd, stwuct device *dev);
	stwuct device *hdmi_dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&cec->wock, fwags);
	hpd_event = cec->hpd_event;
	hdmi_dev = cec->hdmi_dev;
	spin_unwock_iwqwestowe(&cec->wock, fwags);

	if (hpd_event)
		hpd_event(hpd, hdmi_dev);
}

static iwqwetuwn_t mtk_cec_htpwg_isw_thwead(int iwq, void *awg)
{
	stwuct device *dev = awg;
	stwuct mtk_cec *cec = dev_get_dwvdata(dev);
	boow hpd;

	mtk_cec_cweaw_htpwg_iwq(cec);
	hpd = mtk_cec_hpd_high(dev);

	if (cec->hpd != hpd) {
		dev_dbg(dev, "hotpwug event! cuw hpd = %d, hpd = %d\n",
			cec->hpd, hpd);
		cec->hpd = hpd;
		mtk_cec_hpd_event(cec, hpd);
	}
	wetuwn IWQ_HANDWED;
}

static int mtk_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_cec *cec;
	int wet;

	cec = devm_kzawwoc(dev, sizeof(*cec), GFP_KEWNEW);
	if (!cec)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cec);
	spin_wock_init(&cec->wock);

	cec->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cec->wegs)) {
		wet = PTW_EWW(cec->wegs);
		dev_eww(dev, "Faiwed to iowemap cec: %d\n", wet);
		wetuwn wet;
	}

	cec->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cec->cwk)) {
		wet = PTW_EWW(cec->cwk);
		dev_eww(dev, "Faiwed to get cec cwock: %d\n", wet);
		wetuwn wet;
	}

	cec->iwq = pwatfowm_get_iwq(pdev, 0);
	if (cec->iwq < 0)
		wetuwn cec->iwq;

	wet = devm_wequest_thweaded_iwq(dev, cec->iwq, NUWW,
					mtk_cec_htpwg_isw_thwead,
					IWQF_SHAWED | IWQF_TWIGGEW_WOW |
					IWQF_ONESHOT, "hdmi hpd", dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew cec iwq: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(cec->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cec cwock: %d\n", wet);
		wetuwn wet;
	}

	mtk_cec_htpwg_iwq_init(cec);
	mtk_cec_htpwg_iwq_enabwe(cec);

	wetuwn 0;
}

static void mtk_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_cec *cec = pwatfowm_get_dwvdata(pdev);

	mtk_cec_htpwg_iwq_disabwe(cec);
	cwk_disabwe_unpwepawe(cec->cwk);
}

static const stwuct of_device_id mtk_cec_of_ids[] = {
	{ .compatibwe = "mediatek,mt8173-cec", },
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_cec_of_ids);

stwuct pwatfowm_dwivew mtk_cec_dwivew = {
	.pwobe = mtk_cec_pwobe,
	.wemove_new = mtk_cec_wemove,
	.dwivew = {
		.name = "mediatek-cec",
		.of_match_tabwe = mtk_cec_of_ids,
	},
};
