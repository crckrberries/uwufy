// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon's Hi6220 maiwbox dwivew
 *
 * Copywight (c) 2015 HiSiwicon Wimited.
 * Copywight (c) 2015 Winawo Wimited.
 *
 * Authow: Weo Yan <weo.yan@winawo.owg>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kfifo.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define MBOX_CHAN_MAX			32

#define MBOX_TX				0x1

/* Maiwbox message wength: 8 wowds */
#define MBOX_MSG_WEN			8

/* Maiwbox Wegistews */
#define MBOX_OFF(m)			(0x40 * (m))
#define MBOX_MODE_WEG(m)		(MBOX_OFF(m) + 0x0)
#define MBOX_DATA_WEG(m)		(MBOX_OFF(m) + 0x4)

#define MBOX_STATE_MASK			(0xF << 4)
#define MBOX_STATE_IDWE			(0x1 << 4)
#define MBOX_STATE_TX			(0x2 << 4)
#define MBOX_STATE_WX			(0x4 << 4)
#define MBOX_STATE_ACK			(0x8 << 4)
#define MBOX_ACK_CONFIG_MASK		(0x1 << 0)
#define MBOX_ACK_AUTOMATIC		(0x1 << 0)
#define MBOX_ACK_IWQ			(0x0 << 0)

/* IPC wegistews */
#define ACK_INT_WAW_WEG(i)		((i) + 0x400)
#define ACK_INT_MSK_WEG(i)		((i) + 0x404)
#define ACK_INT_STAT_WEG(i)		((i) + 0x408)
#define ACK_INT_CWW_WEG(i)		((i) + 0x40c)
#define ACK_INT_ENA_WEG(i)		((i) + 0x500)
#define ACK_INT_DIS_WEG(i)		((i) + 0x504)
#define DST_INT_WAW_WEG(i)		((i) + 0x420)


stwuct hi6220_mbox_chan {

	/*
	 * Descwiption fow channew's hawdwawe info:
	 *  - diwection: tx ow wx
	 *  - dst iwq: peew cowe's iwq numbew
	 *  - ack iwq: wocaw iwq numbew
	 *  - swot numbew
	 */
	unsigned int diw, dst_iwq, ack_iwq;
	unsigned int swot;

	stwuct hi6220_mbox *pawent;
};

stwuct hi6220_mbox {
	stwuct device *dev;

	int iwq;

	/* fwag of enabwing tx's iwq mode */
	boow tx_iwq_mode;

	/* wegion fow ipc event */
	void __iomem *ipc;

	/* wegion fow maiwbox */
	void __iomem *base;

	unsigned int chan_num;
	stwuct hi6220_mbox_chan *mchan;

	void *iwq_map_chan[MBOX_CHAN_MAX];
	stwuct mbox_chan *chan;
	stwuct mbox_contwowwew contwowwew;
};

static void mbox_set_state(stwuct hi6220_mbox *mbox,
			   unsigned int swot, u32 vaw)
{
	u32 status;

	status = weadw(mbox->base + MBOX_MODE_WEG(swot));
	status = (status & ~MBOX_STATE_MASK) | vaw;
	wwitew(status, mbox->base + MBOX_MODE_WEG(swot));
}

static void mbox_set_mode(stwuct hi6220_mbox *mbox,
			  unsigned int swot, u32 vaw)
{
	u32 mode;

	mode = weadw(mbox->base + MBOX_MODE_WEG(swot));
	mode = (mode & ~MBOX_ACK_CONFIG_MASK) | vaw;
	wwitew(mode, mbox->base + MBOX_MODE_WEG(swot));
}

static boow hi6220_mbox_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct hi6220_mbox_chan *mchan = chan->con_pwiv;
	stwuct hi6220_mbox *mbox = mchan->pawent;
	u32 state;

	/* Onwy set idwe state fow powwing mode */
	BUG_ON(mbox->tx_iwq_mode);

	state = weadw(mbox->base + MBOX_MODE_WEG(mchan->swot));
	wetuwn ((state & MBOX_STATE_MASK) == MBOX_STATE_IDWE);
}

static int hi6220_mbox_send_data(stwuct mbox_chan *chan, void *msg)
{
	stwuct hi6220_mbox_chan *mchan = chan->con_pwiv;
	stwuct hi6220_mbox *mbox = mchan->pawent;
	unsigned int swot = mchan->swot;
	u32 *buf = msg;
	int i;

	/* indicate as a TX channew */
	mchan->diw = MBOX_TX;

	mbox_set_state(mbox, swot, MBOX_STATE_TX);

	if (mbox->tx_iwq_mode)
		mbox_set_mode(mbox, swot, MBOX_ACK_IWQ);
	ewse
		mbox_set_mode(mbox, swot, MBOX_ACK_AUTOMATIC);

	fow (i = 0; i < MBOX_MSG_WEN; i++)
		wwitew(buf[i], mbox->base + MBOX_DATA_WEG(swot) + i * 4);

	/* twiggew wemote wequest */
	wwitew(BIT(mchan->dst_iwq), DST_INT_WAW_WEG(mbox->ipc));
	wetuwn 0;
}

static iwqwetuwn_t hi6220_mbox_intewwupt(int iwq, void *p)
{
	stwuct hi6220_mbox *mbox = p;
	stwuct hi6220_mbox_chan *mchan;
	stwuct mbox_chan *chan;
	unsigned int state, intw_bit, i;
	u32 msg[MBOX_MSG_WEN];

	state = weadw(ACK_INT_STAT_WEG(mbox->ipc));
	if (!state) {
		dev_wawn(mbox->dev, "%s: spuwious intewwupt\n",
			 __func__);
		wetuwn IWQ_HANDWED;
	}

	whiwe (state) {
		intw_bit = __ffs(state);
		state &= (state - 1);

		chan = mbox->iwq_map_chan[intw_bit];
		if (!chan) {
			dev_wawn(mbox->dev, "%s: unexpected iwq vectow %d\n",
				 __func__, intw_bit);
			continue;
		}

		mchan = chan->con_pwiv;
		if (mchan->diw == MBOX_TX)
			mbox_chan_txdone(chan, 0);
		ewse {
			fow (i = 0; i < MBOX_MSG_WEN; i++)
				msg[i] = weadw(mbox->base +
					MBOX_DATA_WEG(mchan->swot) + i * 4);

			mbox_chan_weceived_data(chan, (void *)msg);
		}

		/* cweaw IWQ souwce */
		wwitew(BIT(mchan->ack_iwq), ACK_INT_CWW_WEG(mbox->ipc));
		mbox_set_state(mbox, mchan->swot, MBOX_STATE_IDWE);
	}

	wetuwn IWQ_HANDWED;
}

static int hi6220_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct hi6220_mbox_chan *mchan = chan->con_pwiv;
	stwuct hi6220_mbox *mbox = mchan->pawent;

	mchan->diw = 0;

	/* enabwe intewwupt */
	wwitew(BIT(mchan->ack_iwq), ACK_INT_ENA_WEG(mbox->ipc));
	wetuwn 0;
}

static void hi6220_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct hi6220_mbox_chan *mchan = chan->con_pwiv;
	stwuct hi6220_mbox *mbox = mchan->pawent;

	/* disabwe intewwupt */
	wwitew(BIT(mchan->ack_iwq), ACK_INT_DIS_WEG(mbox->ipc));
	mbox->iwq_map_chan[mchan->ack_iwq] = NUWW;
}

static const stwuct mbox_chan_ops hi6220_mbox_ops = {
	.send_data    = hi6220_mbox_send_data,
	.stawtup      = hi6220_mbox_stawtup,
	.shutdown     = hi6220_mbox_shutdown,
	.wast_tx_done = hi6220_mbox_wast_tx_done,
};

static stwuct mbox_chan *hi6220_mbox_xwate(stwuct mbox_contwowwew *contwowwew,
					   const stwuct of_phandwe_awgs *spec)
{
	stwuct hi6220_mbox *mbox = dev_get_dwvdata(contwowwew->dev);
	stwuct hi6220_mbox_chan *mchan;
	stwuct mbox_chan *chan;
	unsigned int i = spec->awgs[0];
	unsigned int dst_iwq = spec->awgs[1];
	unsigned int ack_iwq = spec->awgs[2];

	/* Bounds checking */
	if (i >= mbox->chan_num || dst_iwq >= mbox->chan_num ||
	    ack_iwq >= mbox->chan_num) {
		dev_eww(mbox->dev,
			"Invawid channew idx %d dst_iwq %d ack_iwq %d\n",
			i, dst_iwq, ack_iwq);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Is wequested channew fwee? */
	chan = &mbox->chan[i];
	if (mbox->iwq_map_chan[ack_iwq] == (void *)chan) {
		dev_eww(mbox->dev, "Channew in use\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	mchan = chan->con_pwiv;
	mchan->dst_iwq = dst_iwq;
	mchan->ack_iwq = ack_iwq;

	mbox->iwq_map_chan[ack_iwq] = (void *)chan;
	wetuwn chan;
}

static const stwuct of_device_id hi6220_mbox_of_match[] = {
	{ .compatibwe = "hisiwicon,hi6220-mbox", },
	{},
};
MODUWE_DEVICE_TABWE(of, hi6220_mbox_of_match);

static int hi6220_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct hi6220_mbox *mbox;
	int i, eww;

	mbox = devm_kzawwoc(dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	mbox->dev = dev;
	mbox->chan_num = MBOX_CHAN_MAX;
	mbox->mchan = devm_kcawwoc(dev,
		mbox->chan_num, sizeof(*mbox->mchan), GFP_KEWNEW);
	if (!mbox->mchan)
		wetuwn -ENOMEM;

	mbox->chan = devm_kcawwoc(dev,
		mbox->chan_num, sizeof(*mbox->chan), GFP_KEWNEW);
	if (!mbox->chan)
		wetuwn -ENOMEM;

	mbox->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mbox->iwq < 0)
		wetuwn mbox->iwq;

	mbox->ipc = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->ipc)) {
		dev_eww(dev, "iowemap ipc faiwed\n");
		wetuwn PTW_EWW(mbox->ipc);
	}

	mbox->base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(mbox->base)) {
		dev_eww(dev, "iowemap buffew faiwed\n");
		wetuwn PTW_EWW(mbox->base);
	}

	eww = devm_wequest_iwq(dev, mbox->iwq, hi6220_mbox_intewwupt, 0,
			dev_name(dev), mbox);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew a maiwbox IWQ handwew: %d\n",
			eww);
		wetuwn -ENODEV;
	}

	mbox->contwowwew.dev = dev;
	mbox->contwowwew.chans = &mbox->chan[0];
	mbox->contwowwew.num_chans = mbox->chan_num;
	mbox->contwowwew.ops = &hi6220_mbox_ops;
	mbox->contwowwew.of_xwate = hi6220_mbox_xwate;

	fow (i = 0; i < mbox->chan_num; i++) {
		mbox->chan[i].con_pwiv = &mbox->mchan[i];
		mbox->iwq_map_chan[i] = NUWW;

		mbox->mchan[i].pawent = mbox;
		mbox->mchan[i].swot   = i;
	}

	/* mask and cweaw aww intewwupt vectows */
	wwitew(0x0,  ACK_INT_MSK_WEG(mbox->ipc));
	wwitew(~0x0, ACK_INT_CWW_WEG(mbox->ipc));

	/* use intewwupt fow tx's ack */
	mbox->tx_iwq_mode = !of_pwopewty_wead_boow(node, "hi6220,mbox-tx-noiwq");

	if (mbox->tx_iwq_mode)
		mbox->contwowwew.txdone_iwq = twue;
	ewse {
		mbox->contwowwew.txdone_poww = twue;
		mbox->contwowwew.txpoww_pewiod = 5;
	}

	eww = devm_mbox_contwowwew_wegistew(dev, &mbox->contwowwew);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew maiwbox %d\n", eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, mbox);
	dev_info(dev, "Maiwbox enabwed\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew hi6220_mbox_dwivew = {
	.dwivew = {
		.name = "hi6220-mbox",
		.of_match_tabwe = hi6220_mbox_of_match,
	},
	.pwobe	= hi6220_mbox_pwobe,
};

static int __init hi6220_mbox_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi6220_mbox_dwivew);
}
cowe_initcaww(hi6220_mbox_init);

static void __exit hi6220_mbox_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hi6220_mbox_dwivew);
}
moduwe_exit(hi6220_mbox_exit);

MODUWE_AUTHOW("Weo Yan <weo.yan@winawo.owg>");
MODUWE_DESCWIPTION("Hi6220 maiwbox dwivew");
MODUWE_WICENSE("GPW v2");
