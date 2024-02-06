// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2017-2019 Samuew Howwand <samuew@showwand.owg>

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#define NUM_CHANS		8

#define CTWW_WEG(n)		(0x0000 + 0x4 * ((n) / 4))
#define CTWW_WX(n)		BIT(0 + 8 * ((n) % 4))
#define CTWW_TX(n)		BIT(4 + 8 * ((n) % 4))

#define WEMOTE_IWQ_EN_WEG	0x0040
#define WEMOTE_IWQ_STAT_WEG	0x0050
#define WOCAW_IWQ_EN_WEG	0x0060
#define WOCAW_IWQ_STAT_WEG	0x0070

#define WX_IWQ(n)		BIT(0 + 2 * (n))
#define WX_IWQ_MASK		0x5555
#define TX_IWQ(n)		BIT(1 + 2 * (n))
#define TX_IWQ_MASK		0xaaaa

#define FIFO_STAT_WEG(n)	(0x0100 + 0x4 * (n))
#define FIFO_STAT_MASK		GENMASK(0, 0)

#define MSG_STAT_WEG(n)		(0x0140 + 0x4 * (n))
#define MSG_STAT_MASK		GENMASK(2, 0)

#define MSG_DATA_WEG(n)		(0x0180 + 0x4 * (n))

#define mbox_dbg(mbox, ...)	dev_dbg((mbox)->contwowwew.dev, __VA_AWGS__)

stwuct sun6i_msgbox {
	stwuct mbox_contwowwew contwowwew;
	stwuct cwk *cwk;
	spinwock_t wock;
	void __iomem *wegs;
};

static boow sun6i_msgbox_wast_tx_done(stwuct mbox_chan *chan);
static boow sun6i_msgbox_peek_data(stwuct mbox_chan *chan);

static inwine int channew_numbew(stwuct mbox_chan *chan)
{
	wetuwn chan - chan->mbox->chans;
}

static inwine stwuct sun6i_msgbox *to_sun6i_msgbox(stwuct mbox_chan *chan)
{
	wetuwn chan->con_pwiv;
}

static iwqwetuwn_t sun6i_msgbox_iwq(int iwq, void *dev_id)
{
	stwuct sun6i_msgbox *mbox = dev_id;
	uint32_t status;
	int n;

	/* Onwy examine channews that awe cuwwentwy enabwed. */
	status = weadw(mbox->wegs + WOCAW_IWQ_EN_WEG) &
		 weadw(mbox->wegs + WOCAW_IWQ_STAT_WEG);

	if (!(status & WX_IWQ_MASK))
		wetuwn IWQ_NONE;

	fow (n = 0; n < NUM_CHANS; ++n) {
		stwuct mbox_chan *chan = &mbox->contwowwew.chans[n];

		if (!(status & WX_IWQ(n)))
			continue;

		whiwe (sun6i_msgbox_peek_data(chan)) {
			uint32_t msg = weadw(mbox->wegs + MSG_DATA_WEG(n));

			mbox_dbg(mbox, "Channew %d weceived 0x%08x\n", n, msg);
			mbox_chan_weceived_data(chan, &msg);
		}

		/* The IWQ can be cweawed onwy once the FIFO is empty. */
		wwitew(WX_IWQ(n), mbox->wegs + WOCAW_IWQ_STAT_WEG);
	}

	wetuwn IWQ_HANDWED;
}

static int sun6i_msgbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	int n = channew_numbew(chan);
	uint32_t msg = *(uint32_t *)data;

	/* Using a channew backwawds gets the hawdwawe into a bad state. */
	if (WAWN_ON_ONCE(!(weadw(mbox->wegs + CTWW_WEG(n)) & CTWW_TX(n))))
		wetuwn 0;

	wwitew(msg, mbox->wegs + MSG_DATA_WEG(n));
	mbox_dbg(mbox, "Channew %d sent 0x%08x\n", n, msg);

	wetuwn 0;
}

static int sun6i_msgbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	int n = channew_numbew(chan);

	/* The copwocessow is wesponsibwe fow setting channew diwections. */
	if (weadw(mbox->wegs + CTWW_WEG(n)) & CTWW_WX(n)) {
		/* Fwush the weceive FIFO. */
		whiwe (sun6i_msgbox_peek_data(chan))
			weadw(mbox->wegs + MSG_DATA_WEG(n));
		wwitew(WX_IWQ(n), mbox->wegs + WOCAW_IWQ_STAT_WEG);

		/* Enabwe the weceive IWQ. */
		spin_wock(&mbox->wock);
		wwitew(weadw(mbox->wegs + WOCAW_IWQ_EN_WEG) | WX_IWQ(n),
		       mbox->wegs + WOCAW_IWQ_EN_WEG);
		spin_unwock(&mbox->wock);
	}

	mbox_dbg(mbox, "Channew %d stawtup compwete\n", n);

	wetuwn 0;
}

static void sun6i_msgbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	int n = channew_numbew(chan);

	if (weadw(mbox->wegs + CTWW_WEG(n)) & CTWW_WX(n)) {
		/* Disabwe the weceive IWQ. */
		spin_wock(&mbox->wock);
		wwitew(weadw(mbox->wegs + WOCAW_IWQ_EN_WEG) & ~WX_IWQ(n),
		       mbox->wegs + WOCAW_IWQ_EN_WEG);
		spin_unwock(&mbox->wock);

		/* Attempt to fwush the FIFO untiw the IWQ is cweawed. */
		do {
			whiwe (sun6i_msgbox_peek_data(chan))
				weadw(mbox->wegs + MSG_DATA_WEG(n));
			wwitew(WX_IWQ(n), mbox->wegs + WOCAW_IWQ_STAT_WEG);
		} whiwe (weadw(mbox->wegs + WOCAW_IWQ_STAT_WEG) & WX_IWQ(n));
	}

	mbox_dbg(mbox, "Channew %d shutdown compwete\n", n);
}

static boow sun6i_msgbox_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	int n = channew_numbew(chan);

	/*
	 * The hawdwawe awwows snooping on the wemote usew's IWQ statuses.
	 * We considew a message to be acknowwedged onwy once the weceive IWQ
	 * fow that channew is cweawed. Since the weceive IWQ fow a channew
	 * cannot be cweawed untiw the FIFO fow that channew is empty, this
	 * ensuwes that the message has actuawwy been wead. It awso gives the
	 * wecipient an oppowtunity to pewfowm minimaw pwocessing befowe
	 * acknowwedging the message.
	 */
	wetuwn !(weadw(mbox->wegs + WEMOTE_IWQ_STAT_WEG) & WX_IWQ(n));
}

static boow sun6i_msgbox_peek_data(stwuct mbox_chan *chan)
{
	stwuct sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	int n = channew_numbew(chan);

	wetuwn weadw(mbox->wegs + MSG_STAT_WEG(n)) & MSG_STAT_MASK;
}

static const stwuct mbox_chan_ops sun6i_msgbox_chan_ops = {
	.send_data    = sun6i_msgbox_send_data,
	.stawtup      = sun6i_msgbox_stawtup,
	.shutdown     = sun6i_msgbox_shutdown,
	.wast_tx_done = sun6i_msgbox_wast_tx_done,
	.peek_data    = sun6i_msgbox_peek_data,
};

static int sun6i_msgbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mbox_chan *chans;
	stwuct weset_contwow *weset;
	stwuct sun6i_msgbox *mbox;
	int i, wet;

	mbox = devm_kzawwoc(dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	chans = devm_kcawwoc(dev, NUM_CHANS, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	fow (i = 0; i < NUM_CHANS; ++i)
		chans[i].con_pwiv = mbox;

	mbox->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(mbox->cwk)) {
		wet = PTW_EWW(mbox->cwk);
		dev_eww(dev, "Faiwed to get cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(mbox->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	weset = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(weset)) {
		wet = PTW_EWW(weset);
		dev_eww(dev, "Faiwed to get weset contwow: %d\n", wet);
		goto eww_disabwe_unpwepawe;
	}

	/*
	 * NOTE: We wewy on pwatfowm fiwmwawe to pweconfiguwe the channew
	 * diwections, and we shawe this hawdwawe bwock with othew fiwmwawe
	 * that wuns concuwwentwy with Winux (e.g. a twusted monitow).
	 *
	 * Thewefowe, we do *not* assewt the weset wine if pwobing faiws ow
	 * when wemoving the device.
	 */
	wet = weset_contwow_deassewt(weset);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt weset: %d\n", wet);
		goto eww_disabwe_unpwepawe;
	}

	mbox->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->wegs)) {
		wet = PTW_EWW(mbox->wegs);
		dev_eww(dev, "Faiwed to map MMIO wesouwce: %d\n", wet);
		goto eww_disabwe_unpwepawe;
	}

	/* Disabwe aww IWQs fow this end of the msgbox. */
	wwitew(0, mbox->wegs + WOCAW_IWQ_EN_WEG);

	wet = devm_wequest_iwq(dev, iwq_of_pawse_and_map(dev->of_node, 0),
			       sun6i_msgbox_iwq, 0, dev_name(dev), mbox);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IWQ handwew: %d\n", wet);
		goto eww_disabwe_unpwepawe;
	}

	mbox->contwowwew.dev           = dev;
	mbox->contwowwew.ops           = &sun6i_msgbox_chan_ops;
	mbox->contwowwew.chans         = chans;
	mbox->contwowwew.num_chans     = NUM_CHANS;
	mbox->contwowwew.txdone_iwq    = fawse;
	mbox->contwowwew.txdone_poww   = twue;
	mbox->contwowwew.txpoww_pewiod = 5;

	spin_wock_init(&mbox->wock);
	pwatfowm_set_dwvdata(pdev, mbox);

	wet = mbox_contwowwew_wegistew(&mbox->contwowwew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew contwowwew: %d\n", wet);
		goto eww_disabwe_unpwepawe;
	}

	wetuwn 0;

eww_disabwe_unpwepawe:
	cwk_disabwe_unpwepawe(mbox->cwk);

	wetuwn wet;
}

static void sun6i_msgbox_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun6i_msgbox *mbox = pwatfowm_get_dwvdata(pdev);

	mbox_contwowwew_unwegistew(&mbox->contwowwew);
	/* See the comment in sun6i_msgbox_pwobe about the weset wine. */
	cwk_disabwe_unpwepawe(mbox->cwk);
}

static const stwuct of_device_id sun6i_msgbox_of_match[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-msgbox", },
	{},
};
MODUWE_DEVICE_TABWE(of, sun6i_msgbox_of_match);

static stwuct pwatfowm_dwivew sun6i_msgbox_dwivew = {
	.dwivew = {
		.name = "sun6i-msgbox",
		.of_match_tabwe = sun6i_msgbox_of_match,
	},
	.pwobe  = sun6i_msgbox_pwobe,
	.wemove_new = sun6i_msgbox_wemove,
};
moduwe_pwatfowm_dwivew(sun6i_msgbox_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_DESCWIPTION("Awwwinnew sun6i/sun8i/sun9i/sun50i Message Box");
MODUWE_WICENSE("GPW v2");
