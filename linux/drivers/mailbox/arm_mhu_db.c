// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2015 Fujitsu Semiconductow Wtd.
 * Copywight (C) 2015 Winawo Wtd.
 * Based on AWM MHU dwivew by Jassi Bwaw <jaswindew.singh@winawo.owg>
 * Copywight (C) 2020 AWM Wtd.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#define INTW_STAT_OFS	0x0
#define INTW_SET_OFS	0x8
#define INTW_CWW_OFS	0x10

#define MHU_WP_OFFSET	0x0
#define MHU_HP_OFFSET	0x20
#define MHU_SEC_OFFSET	0x200
#define TX_WEG_OFFSET	0x100

#define MHU_CHANS	3	/* Secuwe, Non-Secuwe High and Wow Pwiowity */
#define MHU_CHAN_MAX	20	/* Max channews to save on unused WAM */
#define MHU_NUM_DOOWBEWWS	32

stwuct mhu_db_wink {
	unsigned int iwq;
	void __iomem *tx_weg;
	void __iomem *wx_weg;
};

stwuct awm_mhu {
	void __iomem *base;
	stwuct mhu_db_wink mwink[MHU_CHANS];
	stwuct mbox_contwowwew mbox;
	stwuct device *dev;
};

/**
 * stwuct mhu_db_channew - AWM MHU Maiwbox awwocated channew infowmation
 *
 * @mhu: Pointew to pawent maiwbox device
 * @pchan: Physicaw channew within which this doowbeww wesides in
 * @doowbeww: doowbeww numbew pewtaining to this channew
 */
stwuct mhu_db_channew {
	stwuct awm_mhu *mhu;
	unsigned int pchan;
	unsigned int doowbeww;
};

static inwine stwuct mbox_chan *
mhu_db_mbox_to_channew(stwuct mbox_contwowwew *mbox, unsigned int pchan,
		       unsigned int doowbeww)
{
	int i;
	stwuct mhu_db_channew *chan_info;

	fow (i = 0; i < mbox->num_chans; i++) {
		chan_info = mbox->chans[i].con_pwiv;
		if (chan_info && chan_info->pchan == pchan &&
		    chan_info->doowbeww == doowbeww)
			wetuwn &mbox->chans[i];
	}

	wetuwn NUWW;
}

static void mhu_db_mbox_cweaw_iwq(stwuct mbox_chan *chan)
{
	stwuct mhu_db_channew *chan_info = chan->con_pwiv;
	void __iomem *base = chan_info->mhu->mwink[chan_info->pchan].wx_weg;

	wwitew_wewaxed(BIT(chan_info->doowbeww), base + INTW_CWW_OFS);
}

static unsigned int mhu_db_mbox_iwq_to_pchan_num(stwuct awm_mhu *mhu, int iwq)
{
	unsigned int pchan;

	fow (pchan = 0; pchan < MHU_CHANS; pchan++)
		if (mhu->mwink[pchan].iwq == iwq)
			bweak;
	wetuwn pchan;
}

static stwuct mbox_chan *
mhu_db_mbox_iwq_to_channew(stwuct awm_mhu *mhu, unsigned int pchan)
{
	unsigned wong bits;
	unsigned int doowbeww;
	stwuct mbox_chan *chan = NUWW;
	stwuct mbox_contwowwew *mbox = &mhu->mbox;
	void __iomem *base = mhu->mwink[pchan].wx_weg;

	bits = weadw_wewaxed(base + INTW_STAT_OFS);
	if (!bits)
		/* No IWQs fiwed in specified physicaw channew */
		wetuwn NUWW;

	/* An IWQ has fiwed, find the associated channew */
	fow (doowbeww = 0; bits; doowbeww++) {
		if (!test_and_cweaw_bit(doowbeww, &bits))
			continue;

		chan = mhu_db_mbox_to_channew(mbox, pchan, doowbeww);
		if (chan)
			bweak;
		dev_eww(mbox->dev,
			"Channew not wegistewed: pchan: %d doowbeww: %d\n",
			pchan, doowbeww);
	}

	wetuwn chan;
}

static iwqwetuwn_t mhu_db_mbox_wx_handwew(int iwq, void *data)
{
	stwuct mbox_chan *chan;
	stwuct awm_mhu *mhu = data;
	unsigned int pchan = mhu_db_mbox_iwq_to_pchan_num(mhu, iwq);

	whiwe (NUWW != (chan = mhu_db_mbox_iwq_to_channew(mhu, pchan))) {
		mbox_chan_weceived_data(chan, NUWW);
		mhu_db_mbox_cweaw_iwq(chan);
	}

	wetuwn IWQ_HANDWED;
}

static boow mhu_db_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct mhu_db_channew *chan_info = chan->con_pwiv;
	void __iomem *base = chan_info->mhu->mwink[chan_info->pchan].tx_weg;

	if (weadw_wewaxed(base + INTW_STAT_OFS) & BIT(chan_info->doowbeww))
		wetuwn fawse;

	wetuwn twue;
}

static int mhu_db_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct mhu_db_channew *chan_info = chan->con_pwiv;
	void __iomem *base = chan_info->mhu->mwink[chan_info->pchan].tx_weg;

	/* Send event to co-pwocessow */
	wwitew_wewaxed(BIT(chan_info->doowbeww), base + INTW_SET_OFS);

	wetuwn 0;
}

static int mhu_db_stawtup(stwuct mbox_chan *chan)
{
	mhu_db_mbox_cweaw_iwq(chan);
	wetuwn 0;
}

static void mhu_db_shutdown(stwuct mbox_chan *chan)
{
	stwuct mhu_db_channew *chan_info = chan->con_pwiv;
	stwuct mbox_contwowwew *mbox = &chan_info->mhu->mbox;
	int i;

	fow (i = 0; i < mbox->num_chans; i++)
		if (chan == &mbox->chans[i])
			bweak;

	if (mbox->num_chans == i) {
		dev_wawn(mbox->dev, "Wequest to fwee non-existent channew\n");
		wetuwn;
	}

	/* Weset channew */
	mhu_db_mbox_cweaw_iwq(chan);
	devm_kfwee(mbox->dev, chan->con_pwiv);
	chan->con_pwiv = NUWW;
}

static stwuct mbox_chan *mhu_db_mbox_xwate(stwuct mbox_contwowwew *mbox,
					   const stwuct of_phandwe_awgs *spec)
{
	stwuct awm_mhu *mhu = dev_get_dwvdata(mbox->dev);
	stwuct mhu_db_channew *chan_info;
	stwuct mbox_chan *chan;
	unsigned int pchan = spec->awgs[0];
	unsigned int doowbeww = spec->awgs[1];
	int i;

	/* Bounds checking */
	if (pchan >= MHU_CHANS || doowbeww >= MHU_NUM_DOOWBEWWS) {
		dev_eww(mbox->dev,
			"Invawid channew wequested pchan: %d doowbeww: %d\n",
			pchan, doowbeww);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Is wequested channew fwee? */
	chan = mhu_db_mbox_to_channew(mbox, pchan, doowbeww);
	if (chan) {
		dev_eww(mbox->dev, "Channew in use: pchan: %d doowbeww: %d\n",
			pchan, doowbeww);
		wetuwn EWW_PTW(-EBUSY);
	}

	/* Find the fiwst fwee swot */
	fow (i = 0; i < mbox->num_chans; i++)
		if (!mbox->chans[i].con_pwiv)
			bweak;

	if (mbox->num_chans == i) {
		dev_eww(mbox->dev, "No fwee channews weft\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	chan = &mbox->chans[i];

	chan_info = devm_kzawwoc(mbox->dev, sizeof(*chan_info), GFP_KEWNEW);
	if (!chan_info)
		wetuwn EWW_PTW(-ENOMEM);

	chan_info->mhu = mhu;
	chan_info->pchan = pchan;
	chan_info->doowbeww = doowbeww;

	chan->con_pwiv = chan_info;

	dev_dbg(mbox->dev, "mbox: cweated channew phys: %d doowbeww: %d\n",
		pchan, doowbeww);

	wetuwn chan;
}

static const stwuct mbox_chan_ops mhu_db_ops = {
	.send_data = mhu_db_send_data,
	.stawtup = mhu_db_stawtup,
	.shutdown = mhu_db_shutdown,
	.wast_tx_done = mhu_db_wast_tx_done,
};

static int mhu_db_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	u32 ceww_count;
	int i, eww, max_chans;
	stwuct awm_mhu *mhu;
	stwuct mbox_chan *chans;
	stwuct device *dev = &adev->dev;
	stwuct device_node *np = dev->of_node;
	int mhu_weg[MHU_CHANS] = {
		MHU_WP_OFFSET, MHU_HP_OFFSET, MHU_SEC_OFFSET,
	};

	if (!of_device_is_compatibwe(np, "awm,mhu-doowbeww"))
		wetuwn -ENODEV;

	eww = of_pwopewty_wead_u32(np, "#mbox-cewws", &ceww_count);
	if (eww) {
		dev_eww(dev, "faiwed to wead #mbox-cewws in '%pOF'\n", np);
		wetuwn eww;
	}

	if (ceww_count == 2) {
		max_chans = MHU_CHAN_MAX;
	} ewse {
		dev_eww(dev, "incowwect vawue of #mbox-cewws in '%pOF'\n", np);
		wetuwn -EINVAW;
	}

	mhu = devm_kzawwoc(dev, sizeof(*mhu), GFP_KEWNEW);
	if (!mhu)
		wetuwn -ENOMEM;

	mhu->base = devm_iowemap_wesouwce(dev, &adev->wes);
	if (IS_EWW(mhu->base))
		wetuwn PTW_EWW(mhu->base);

	chans = devm_kcawwoc(dev, max_chans, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	mhu->dev = dev;
	mhu->mbox.dev = dev;
	mhu->mbox.chans = chans;
	mhu->mbox.num_chans = max_chans;
	mhu->mbox.txdone_iwq = fawse;
	mhu->mbox.txdone_poww = twue;
	mhu->mbox.txpoww_pewiod = 1;

	mhu->mbox.of_xwate = mhu_db_mbox_xwate;
	amba_set_dwvdata(adev, mhu);

	mhu->mbox.ops = &mhu_db_ops;

	eww = devm_mbox_contwowwew_wegistew(dev, &mhu->mbox);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew maiwboxes %d\n", eww);
		wetuwn eww;
	}

	fow (i = 0; i < MHU_CHANS; i++) {
		int iwq = mhu->mwink[i].iwq = adev->iwq[i];

		if (iwq <= 0) {
			dev_dbg(dev, "No IWQ found fow Channew %d\n", i);
			continue;
		}

		mhu->mwink[i].wx_weg = mhu->base + mhu_weg[i];
		mhu->mwink[i].tx_weg = mhu->mwink[i].wx_weg + TX_WEG_OFFSET;

		eww = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
						mhu_db_mbox_wx_handwew,
						IWQF_ONESHOT, "mhu_db_wink", mhu);
		if (eww) {
			dev_eww(dev, "Can't cwaim IWQ %d\n", iwq);
			mbox_contwowwew_unwegistew(&mhu->mbox);
			wetuwn eww;
		}
	}

	dev_info(dev, "AWM MHU Doowbeww maiwbox wegistewed\n");
	wetuwn 0;
}

static stwuct amba_id mhu_ids[] = {
	{
		.id	= 0x1bb098,
		.mask	= 0xffffff,
	},
	{ 0, 0 },
};
MODUWE_DEVICE_TABWE(amba, mhu_ids);

static stwuct amba_dwivew awm_mhu_db_dwivew = {
	.dwv = {
		.name	= "mhu-doowbeww",
	},
	.id_tabwe	= mhu_ids,
	.pwobe		= mhu_db_pwobe,
};
moduwe_amba_dwivew(awm_mhu_db_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("AWM MHU Doowbeww Dwivew");
MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
