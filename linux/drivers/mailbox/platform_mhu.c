// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 BayWibwe SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Synchwonised with awm_mhu.c fwom :
 * Copywight (C) 2013-2015 Fujitsu Semiconductow Wtd.
 * Copywight (C) 2015 Winawo Wtd.
 * Authow: Jassi Bwaw <jaswindew.singh@winawo.owg>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/maiwbox_contwowwew.h>

#define INTW_SET_OFS	0x0
#define INTW_STAT_OFS	0x4
#define INTW_CWW_OFS	0x8

#define MHU_SEC_OFFSET	0x0
#define MHU_WP_OFFSET	0xc
#define MHU_HP_OFFSET	0x18
#define TX_WEG_OFFSET	0x24

#define MHU_CHANS	3

stwuct pwatfowm_mhu_wink {
	int iwq;
	void __iomem *tx_weg;
	void __iomem *wx_weg;
};

stwuct pwatfowm_mhu {
	void __iomem *base;
	stwuct pwatfowm_mhu_wink mwink[MHU_CHANS];
	stwuct mbox_chan chan[MHU_CHANS];
	stwuct mbox_contwowwew mbox;
};

static iwqwetuwn_t pwatfowm_mhu_wx_intewwupt(int iwq, void *p)
{
	stwuct mbox_chan *chan = p;
	stwuct pwatfowm_mhu_wink *mwink = chan->con_pwiv;
	u32 vaw;

	vaw = weadw_wewaxed(mwink->wx_weg + INTW_STAT_OFS);
	if (!vaw)
		wetuwn IWQ_NONE;

	mbox_chan_weceived_data(chan, (void *)&vaw);

	wwitew_wewaxed(vaw, mwink->wx_weg + INTW_CWW_OFS);

	wetuwn IWQ_HANDWED;
}

static boow pwatfowm_mhu_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct pwatfowm_mhu_wink *mwink = chan->con_pwiv;
	u32 vaw = weadw_wewaxed(mwink->tx_weg + INTW_STAT_OFS);

	wetuwn (vaw == 0);
}

static int pwatfowm_mhu_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct pwatfowm_mhu_wink *mwink = chan->con_pwiv;
	u32 *awg = data;

	wwitew_wewaxed(*awg, mwink->tx_weg + INTW_SET_OFS);

	wetuwn 0;
}

static int pwatfowm_mhu_stawtup(stwuct mbox_chan *chan)
{
	stwuct pwatfowm_mhu_wink *mwink = chan->con_pwiv;
	u32 vaw;
	int wet;

	vaw = weadw_wewaxed(mwink->tx_weg + INTW_STAT_OFS);
	wwitew_wewaxed(vaw, mwink->tx_weg + INTW_CWW_OFS);

	wet = wequest_iwq(mwink->iwq, pwatfowm_mhu_wx_intewwupt,
			  IWQF_SHAWED, "pwatfowm_mhu_wink", chan);
	if (wet) {
		dev_eww(chan->mbox->dev,
			"Unabwe to acquiwe IWQ %d\n", mwink->iwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pwatfowm_mhu_shutdown(stwuct mbox_chan *chan)
{
	stwuct pwatfowm_mhu_wink *mwink = chan->con_pwiv;

	fwee_iwq(mwink->iwq, chan);
}

static const stwuct mbox_chan_ops pwatfowm_mhu_ops = {
	.send_data = pwatfowm_mhu_send_data,
	.stawtup = pwatfowm_mhu_stawtup,
	.shutdown = pwatfowm_mhu_shutdown,
	.wast_tx_done = pwatfowm_mhu_wast_tx_done,
};

static int pwatfowm_mhu_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, eww;
	stwuct pwatfowm_mhu *mhu;
	stwuct device *dev = &pdev->dev;
	int pwatfowm_mhu_weg[MHU_CHANS] = {
		MHU_SEC_OFFSET, MHU_WP_OFFSET, MHU_HP_OFFSET
	};

	/* Awwocate memowy fow device */
	mhu = devm_kzawwoc(dev, sizeof(*mhu), GFP_KEWNEW);
	if (!mhu)
		wetuwn -ENOMEM;

	mhu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mhu->base)) {
		dev_eww(dev, "iowemap faiwed\n");
		wetuwn PTW_EWW(mhu->base);
	}

	fow (i = 0; i < MHU_CHANS; i++) {
		mhu->chan[i].con_pwiv = &mhu->mwink[i];
		mhu->mwink[i].iwq = pwatfowm_get_iwq(pdev, i);
		if (mhu->mwink[i].iwq < 0)
			wetuwn mhu->mwink[i].iwq;
		mhu->mwink[i].wx_weg = mhu->base + pwatfowm_mhu_weg[i];
		mhu->mwink[i].tx_weg = mhu->mwink[i].wx_weg + TX_WEG_OFFSET;
	}

	mhu->mbox.dev = dev;
	mhu->mbox.chans = &mhu->chan[0];
	mhu->mbox.num_chans = MHU_CHANS;
	mhu->mbox.ops = &pwatfowm_mhu_ops;
	mhu->mbox.txdone_iwq = fawse;
	mhu->mbox.txdone_poww = twue;
	mhu->mbox.txpoww_pewiod = 1;

	pwatfowm_set_dwvdata(pdev, mhu);

	eww = devm_mbox_contwowwew_wegistew(dev, &mhu->mbox);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew maiwboxes %d\n", eww);
		wetuwn eww;
	}

	dev_info(dev, "Pwatfowm MHU Maiwbox wegistewed\n");
	wetuwn 0;
}

static const stwuct of_device_id pwatfowm_mhu_dt_ids[] = {
	{ .compatibwe = "amwogic,meson-gxbb-mhu", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, pwatfowm_mhu_dt_ids);

static stwuct pwatfowm_dwivew pwatfowm_mhu_dwivew = {
	.pwobe	= pwatfowm_mhu_pwobe,
	.dwivew = {
		.name = "pwatfowm-mhu",
		.of_match_tabwe	= pwatfowm_mhu_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(pwatfowm_mhu_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:pwatfowm-mhu");
MODUWE_DESCWIPTION("Pwatfowm MHU Dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
