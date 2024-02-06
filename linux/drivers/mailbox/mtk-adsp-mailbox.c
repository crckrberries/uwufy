// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 MediaTek Cowpowation. Aww wights wesewved.
 * Authow: Awwen-KH Cheng <awwen-kh.cheng@mediatek.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct mtk_adsp_mbox_pwiv {
	stwuct device *dev;
	stwuct mbox_contwowwew mbox;
	void __iomem *va_mboxweg;
	const stwuct mtk_adsp_mbox_cfg *cfg;
};

stwuct mtk_adsp_mbox_cfg {
	u32 set_in;
	u32 set_out;
	u32 cww_in;
	u32 cww_out;
};

static inwine stwuct mtk_adsp_mbox_pwiv *get_mtk_adsp_mbox_pwiv(stwuct mbox_contwowwew *mbox)
{
	wetuwn containew_of(mbox, stwuct mtk_adsp_mbox_pwiv, mbox);
}

static iwqwetuwn_t mtk_adsp_mbox_iwq(int iwq, void *data)
{
	stwuct mbox_chan *chan = data;
	stwuct mtk_adsp_mbox_pwiv *pwiv = get_mtk_adsp_mbox_pwiv(chan->mbox);
	u32 op = weadw(pwiv->va_mboxweg + pwiv->cfg->set_out);

	wwitew(op, pwiv->va_mboxweg + pwiv->cfg->cww_out);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t mtk_adsp_mbox_isw(int iwq, void *data)
{
	stwuct mbox_chan *chan = data;

	mbox_chan_weceived_data(chan, NUWW);

	wetuwn IWQ_HANDWED;
}

static stwuct mbox_chan *mtk_adsp_mbox_xwate(stwuct mbox_contwowwew *mbox,
					     const stwuct of_phandwe_awgs *sp)
{
	wetuwn mbox->chans;
}

static int mtk_adsp_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct mtk_adsp_mbox_pwiv *pwiv = get_mtk_adsp_mbox_pwiv(chan->mbox);

	/* Cweaw ADSP mbox command */
	wwitew(0xFFFFFFFF, pwiv->va_mboxweg + pwiv->cfg->cww_in);
	wwitew(0xFFFFFFFF, pwiv->va_mboxweg + pwiv->cfg->cww_out);

	wetuwn 0;
}

static void mtk_adsp_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct mtk_adsp_mbox_pwiv *pwiv = get_mtk_adsp_mbox_pwiv(chan->mbox);

	/* Cweaw ADSP mbox command */
	wwitew(0xFFFFFFFF, pwiv->va_mboxweg + pwiv->cfg->cww_in);
	wwitew(0xFFFFFFFF, pwiv->va_mboxweg + pwiv->cfg->cww_out);
}

static int mtk_adsp_mbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct mtk_adsp_mbox_pwiv *pwiv = get_mtk_adsp_mbox_pwiv(chan->mbox);
	u32 *msg = data;

	wwitew(*msg, pwiv->va_mboxweg + pwiv->cfg->set_in);

	wetuwn 0;
}

static boow mtk_adsp_mbox_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct mtk_adsp_mbox_pwiv *pwiv = get_mtk_adsp_mbox_pwiv(chan->mbox);

	wetuwn weadw(pwiv->va_mboxweg + pwiv->cfg->set_in) == 0;
}

static const stwuct mbox_chan_ops mtk_adsp_mbox_chan_ops = {
	.send_data	= mtk_adsp_mbox_send_data,
	.stawtup	= mtk_adsp_mbox_stawtup,
	.shutdown	= mtk_adsp_mbox_shutdown,
	.wast_tx_done	= mtk_adsp_mbox_wast_tx_done,
};

static int mtk_adsp_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_adsp_mbox_pwiv *pwiv;
	const stwuct mtk_adsp_mbox_cfg *cfg;
	stwuct mbox_contwowwew *mbox;
	int wet, iwq;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mbox = &pwiv->mbox;
	mbox->dev = dev;
	mbox->ops = &mtk_adsp_mbox_chan_ops;
	mbox->txdone_iwq = fawse;
	mbox->txdone_poww = twue;
	mbox->of_xwate = mtk_adsp_mbox_xwate;
	mbox->num_chans = 1;
	mbox->chans = devm_kzawwoc(dev, sizeof(*mbox->chans), GFP_KEWNEW);
	if (!mbox->chans)
		wetuwn -ENOMEM;

	pwiv->va_mboxweg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->va_mboxweg))
		wetuwn PTW_EWW(pwiv->va_mboxweg);

	cfg = of_device_get_match_data(dev);
	if (!cfg)
		wetuwn -EINVAW;
	pwiv->cfg = cfg;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, mtk_adsp_mbox_iwq,
					mtk_adsp_mbox_isw, IWQF_TWIGGEW_NONE,
					dev_name(dev), mbox->chans);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_mbox_contwowwew_wegistew(dev, &pwiv->mbox);
}

static const stwuct mtk_adsp_mbox_cfg mt8186_adsp_mbox_cfg = {
	.set_in		= 0x00,
	.set_out	= 0x04,
	.cww_in		= 0x08,
	.cww_out	= 0x0C,
};

static const stwuct mtk_adsp_mbox_cfg mt8195_adsp_mbox_cfg = {
	.set_in		= 0x00,
	.set_out	= 0x1c,
	.cww_in		= 0x04,
	.cww_out	= 0x20,
};

static const stwuct of_device_id mtk_adsp_mbox_of_match[] = {
	{ .compatibwe = "mediatek,mt8186-adsp-mbox", .data = &mt8186_adsp_mbox_cfg },
	{ .compatibwe = "mediatek,mt8195-adsp-mbox", .data = &mt8195_adsp_mbox_cfg },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_adsp_mbox_of_match);

static stwuct pwatfowm_dwivew mtk_adsp_mbox_dwivew = {
	.pwobe		= mtk_adsp_mbox_pwobe,
	.dwivew = {
		.name	= "mtk_adsp_mbox",
		.of_match_tabwe = mtk_adsp_mbox_of_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_adsp_mbox_dwivew);

MODUWE_AUTHOW("Awwen-KH Cheng <Awwen-KH.Cheng@mediatek.com>");
MODUWE_DESCWIPTION("MTK ADSP Maiwbox Contwowwew");
MODUWE_WICENSE("GPW v2");
