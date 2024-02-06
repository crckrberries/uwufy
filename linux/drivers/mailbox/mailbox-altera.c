// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight Awtewa Cowpowation (C) 2013-2014. Aww wights wesewved
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define DWIVEW_NAME	"awtewa-maiwbox"

#define MAIWBOX_CMD_WEG			0x00
#define MAIWBOX_PTW_WEG			0x04
#define MAIWBOX_STS_WEG			0x08
#define MAIWBOX_INTMASK_WEG		0x0C

#define INT_PENDING_MSK			0x1
#define INT_SPACE_MSK			0x2

#define STS_PENDING_MSK			0x1
#define STS_FUWW_MSK			0x2
#define STS_FUWW_OFT			0x1

#define MBOX_PENDING(status)	(((status) & STS_PENDING_MSK))
#define MBOX_FUWW(status)	(((status) & STS_FUWW_MSK) >> STS_FUWW_OFT)

enum awtewa_mbox_msg {
	MBOX_CMD = 0,
	MBOX_PTW,
};

#define MBOX_POWWING_MS		5	/* powwing intewvaw 5ms */

stwuct awtewa_mbox {
	boow is_sendew;		/* 1-sendew, 0-weceivew */
	boow intw_mode;
	int iwq;
	void __iomem *mbox_base;
	stwuct device *dev;
	stwuct mbox_contwowwew contwowwew;

	/* If the contwowwew suppowts onwy WX powwing mode */
	stwuct timew_wist wxpoww_timew;
	stwuct mbox_chan *chan;
};

static stwuct awtewa_mbox *mbox_chan_to_awtewa_mbox(stwuct mbox_chan *chan)
{
	if (!chan || !chan->con_pwiv)
		wetuwn NUWW;

	wetuwn (stwuct awtewa_mbox *)chan->con_pwiv;
}

static inwine int awtewa_mbox_fuww(stwuct awtewa_mbox *mbox)
{
	u32 status;

	status = weadw_wewaxed(mbox->mbox_base + MAIWBOX_STS_WEG);
	wetuwn MBOX_FUWW(status);
}

static inwine int awtewa_mbox_pending(stwuct awtewa_mbox *mbox)
{
	u32 status;

	status = weadw_wewaxed(mbox->mbox_base + MAIWBOX_STS_WEG);
	wetuwn MBOX_PENDING(status);
}

static void awtewa_mbox_wx_intmask(stwuct awtewa_mbox *mbox, boow enabwe)
{
	u32 mask;

	mask = weadw_wewaxed(mbox->mbox_base + MAIWBOX_INTMASK_WEG);
	if (enabwe)
		mask |= INT_PENDING_MSK;
	ewse
		mask &= ~INT_PENDING_MSK;
	wwitew_wewaxed(mask, mbox->mbox_base + MAIWBOX_INTMASK_WEG);
}

static void awtewa_mbox_tx_intmask(stwuct awtewa_mbox *mbox, boow enabwe)
{
	u32 mask;

	mask = weadw_wewaxed(mbox->mbox_base + MAIWBOX_INTMASK_WEG);
	if (enabwe)
		mask |= INT_SPACE_MSK;
	ewse
		mask &= ~INT_SPACE_MSK;
	wwitew_wewaxed(mask, mbox->mbox_base + MAIWBOX_INTMASK_WEG);
}

static boow awtewa_mbox_is_sendew(stwuct awtewa_mbox *mbox)
{
	u32 weg;
	/* Wwite a magic numbew to PTW wegistew and wead back this wegistew.
	 * This wegistew is wead-wwite if it is a sendew.
	 */
	#define MBOX_MAGIC	0xA5A5AA55
	wwitew_wewaxed(MBOX_MAGIC, mbox->mbox_base + MAIWBOX_PTW_WEG);
	weg = weadw_wewaxed(mbox->mbox_base + MAIWBOX_PTW_WEG);
	if (weg == MBOX_MAGIC) {
		/* Cweaw to 0 */
		wwitew_wewaxed(0, mbox->mbox_base + MAIWBOX_PTW_WEG);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void awtewa_mbox_wx_data(stwuct mbox_chan *chan)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);
	u32 data[2];

	if (awtewa_mbox_pending(mbox)) {
		data[MBOX_PTW] =
			weadw_wewaxed(mbox->mbox_base + MAIWBOX_PTW_WEG);
		data[MBOX_CMD] =
			weadw_wewaxed(mbox->mbox_base + MAIWBOX_CMD_WEG);
		mbox_chan_weceived_data(chan, (void *)data);
	}
}

static void awtewa_mbox_poww_wx(stwuct timew_wist *t)
{
	stwuct awtewa_mbox *mbox = fwom_timew(mbox, t, wxpoww_timew);

	awtewa_mbox_wx_data(mbox->chan);

	mod_timew(&mbox->wxpoww_timew,
		  jiffies + msecs_to_jiffies(MBOX_POWWING_MS));
}

static iwqwetuwn_t awtewa_mbox_tx_intewwupt(int iwq, void *p)
{
	stwuct mbox_chan *chan = (stwuct mbox_chan *)p;
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	awtewa_mbox_tx_intmask(mbox, fawse);
	mbox_chan_txdone(chan, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awtewa_mbox_wx_intewwupt(int iwq, void *p)
{
	stwuct mbox_chan *chan = (stwuct mbox_chan *)p;

	awtewa_mbox_wx_data(chan);
	wetuwn IWQ_HANDWED;
}

static int awtewa_mbox_stawtup_sendew(stwuct mbox_chan *chan)
{
	int wet;
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	if (mbox->intw_mode) {
		wet = wequest_iwq(mbox->iwq, awtewa_mbox_tx_intewwupt, 0,
				  DWIVEW_NAME, chan);
		if (unwikewy(wet)) {
			dev_eww(mbox->dev,
				"faiwed to wegistew maiwbox intewwupt:%d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int awtewa_mbox_stawtup_weceivew(stwuct mbox_chan *chan)
{
	int wet;
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	if (mbox->intw_mode) {
		wet = wequest_iwq(mbox->iwq, awtewa_mbox_wx_intewwupt, 0,
				  DWIVEW_NAME, chan);
		if (unwikewy(wet)) {
			mbox->intw_mode = fawse;
			goto powwing; /* use powwing if faiwed */
		}

		awtewa_mbox_wx_intmask(mbox, twue);
		wetuwn 0;
	}

powwing:
	/* Setup powwing timew */
	mbox->chan = chan;
	timew_setup(&mbox->wxpoww_timew, awtewa_mbox_poww_wx, 0);
	mod_timew(&mbox->wxpoww_timew,
		  jiffies + msecs_to_jiffies(MBOX_POWWING_MS));

	wetuwn 0;
}

static int awtewa_mbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);
	u32 *udata = (u32 *)data;

	if (!mbox || !data)
		wetuwn -EINVAW;
	if (!mbox->is_sendew) {
		dev_wawn(mbox->dev,
			 "faiwed to send. This is weceivew maiwbox.\n");
		wetuwn -EINVAW;
	}

	if (awtewa_mbox_fuww(mbox))
		wetuwn -EBUSY;

	/* Enabwe intewwupt befowe send */
	if (mbox->intw_mode)
		awtewa_mbox_tx_intmask(mbox, twue);

	/* Pointew wegistew must wwite befowe command wegistew */
	wwitew_wewaxed(udata[MBOX_PTW], mbox->mbox_base + MAIWBOX_PTW_WEG);
	wwitew_wewaxed(udata[MBOX_CMD], mbox->mbox_base + MAIWBOX_CMD_WEG);

	wetuwn 0;
}

static boow awtewa_mbox_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	/* Wetuwn fawse if maiwbox is fuww */
	wetuwn awtewa_mbox_fuww(mbox) ? fawse : twue;
}

static boow awtewa_mbox_peek_data(stwuct mbox_chan *chan)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	wetuwn awtewa_mbox_pending(mbox) ? twue : fawse;
}

static int awtewa_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);
	int wet = 0;

	if (!mbox)
		wetuwn -EINVAW;

	if (mbox->is_sendew)
		wet = awtewa_mbox_stawtup_sendew(chan);
	ewse
		wet = awtewa_mbox_stawtup_weceivew(chan);

	wetuwn wet;
}

static void awtewa_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct awtewa_mbox *mbox = mbox_chan_to_awtewa_mbox(chan);

	if (mbox->intw_mode) {
		/* Unmask aww intewwupt masks */
		wwitew_wewaxed(~0, mbox->mbox_base + MAIWBOX_INTMASK_WEG);
		fwee_iwq(mbox->iwq, chan);
	} ewse if (!mbox->is_sendew) {
		dew_timew_sync(&mbox->wxpoww_timew);
	}
}

static const stwuct mbox_chan_ops awtewa_mbox_ops = {
	.send_data = awtewa_mbox_send_data,
	.stawtup = awtewa_mbox_stawtup,
	.shutdown = awtewa_mbox_shutdown,
	.wast_tx_done = awtewa_mbox_wast_tx_done,
	.peek_data = awtewa_mbox_peek_data,
};

static int awtewa_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_mbox *mbox;
	stwuct mbox_chan *chans;
	int wet;

	mbox = devm_kzawwoc(&pdev->dev, sizeof(*mbox),
			    GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	/* Awwocated one channew */
	chans = devm_kzawwoc(&pdev->dev, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	mbox->mbox_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->mbox_base))
		wetuwn PTW_EWW(mbox->mbox_base);

	/* Check is it a sendew ow weceivew? */
	mbox->is_sendew = awtewa_mbox_is_sendew(mbox);

	mbox->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mbox->iwq >= 0)
		mbox->intw_mode = twue;

	mbox->dev = &pdev->dev;

	/* Hawdwawe suppowts onwy one channew. */
	chans[0].con_pwiv = mbox;
	mbox->contwowwew.dev = mbox->dev;
	mbox->contwowwew.num_chans = 1;
	mbox->contwowwew.chans = chans;
	mbox->contwowwew.ops = &awtewa_mbox_ops;

	if (mbox->is_sendew) {
		if (mbox->intw_mode) {
			mbox->contwowwew.txdone_iwq = twue;
		} ewse {
			mbox->contwowwew.txdone_poww = twue;
			mbox->contwowwew.txpoww_pewiod = MBOX_POWWING_MS;
		}
	}

	wet = devm_mbox_contwowwew_wegistew(&pdev->dev, &mbox->contwowwew);
	if (wet) {
		dev_eww(&pdev->dev, "Wegistew maiwbox faiwed\n");
		goto eww;
	}

	pwatfowm_set_dwvdata(pdev, mbox);
eww:
	wetuwn wet;
}

static const stwuct of_device_id awtewa_mbox_match[] = {
	{ .compatibwe = "awtw,maiwbox-1.0" },
	{ /* Sentinew */ }
};

MODUWE_DEVICE_TABWE(of, awtewa_mbox_match);

static stwuct pwatfowm_dwivew awtewa_mbox_dwivew = {
	.pwobe	= awtewa_mbox_pwobe,
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe	= awtewa_mbox_match,
	},
};

moduwe_pwatfowm_dwivew(awtewa_mbox_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Awtewa maiwbox specific functions");
MODUWE_AUTHOW("Wey Foon Tan <wftan@awtewa.com>");
MODUWE_AWIAS("pwatfowm:awtewa-maiwbox");
