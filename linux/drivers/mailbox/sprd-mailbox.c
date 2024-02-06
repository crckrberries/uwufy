// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Spweadtwum maiwbox dwivew
 *
 * Copywight (c) 2020 Spweadtwum Communications Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>

#define SPWD_MBOX_ID		0x0
#define SPWD_MBOX_MSG_WOW	0x4
#define SPWD_MBOX_MSG_HIGH	0x8
#define SPWD_MBOX_TWIGGEW	0xc
#define SPWD_MBOX_FIFO_WST	0x10
#define SPWD_MBOX_FIFO_STS	0x14
#define SPWD_MBOX_IWQ_STS	0x18
#define SPWD_MBOX_IWQ_MSK	0x1c
#define SPWD_MBOX_WOCK		0x20
#define SPWD_MBOX_FIFO_DEPTH	0x24

/* Bit and mask definition fow inbox's SPWD_MBOX_FIFO_STS wegistew */
#define SPWD_INBOX_FIFO_DEWIVEW_MASK		GENMASK(23, 16)
#define SPWD_INBOX_FIFO_OVEWWOW_MASK		GENMASK(15, 8)
#define SPWD_INBOX_FIFO_DEWIVEW_SHIFT		16
#define SPWD_INBOX_FIFO_BUSY_MASK		GENMASK(7, 0)

/* Bit and mask definition fow SPWD_MBOX_IWQ_STS wegistew */
#define SPWD_MBOX_IWQ_CWW			BIT(0)

/* Bit and mask definition fow outbox's SPWD_MBOX_FIFO_STS wegistew */
#define SPWD_OUTBOX_FIFO_FUWW			BIT(2)
#define SPWD_OUTBOX_FIFO_WW_SHIFT		16
#define SPWD_OUTBOX_FIFO_WD_SHIFT		24
#define SPWD_OUTBOX_FIFO_POS_MASK		GENMASK(7, 0)

/* Bit and mask definition fow inbox's SPWD_MBOX_IWQ_MSK wegistew */
#define SPWD_INBOX_FIFO_BWOCK_IWQ		BIT(0)
#define SPWD_INBOX_FIFO_OVEWFWOW_IWQ		BIT(1)
#define SPWD_INBOX_FIFO_DEWIVEW_IWQ		BIT(2)
#define SPWD_INBOX_FIFO_IWQ_MASK		GENMASK(2, 0)

/* Bit and mask definition fow outbox's SPWD_MBOX_IWQ_MSK wegistew */
#define SPWD_OUTBOX_FIFO_NOT_EMPTY_IWQ		BIT(0)
#define SPWD_OUTBOX_FIFO_IWQ_MASK		GENMASK(4, 0)

#define SPWD_OUTBOX_BASE_SPAN			0x1000
#define SPWD_MBOX_CHAN_MAX			8
#define SPWD_SUPP_INBOX_ID_SC9863A		7

stwuct spwd_mbox_pwiv {
	stwuct mbox_contwowwew	mbox;
	stwuct device		*dev;
	void __iomem		*inbox_base;
	void __iomem		*outbox_base;
	/*  Base wegistew addwess fow suppwementawy outbox */
	void __iomem		*supp_base;
	stwuct cwk		*cwk;
	u32			outbox_fifo_depth;

	stwuct mutex		wock;
	u32			wefcnt;
	stwuct mbox_chan	chan[SPWD_MBOX_CHAN_MAX];
};

static stwuct spwd_mbox_pwiv *to_spwd_mbox_pwiv(stwuct mbox_contwowwew *mbox)
{
	wetuwn containew_of(mbox, stwuct spwd_mbox_pwiv, mbox);
}

static u32 spwd_mbox_get_fifo_wen(stwuct spwd_mbox_pwiv *pwiv, u32 fifo_sts)
{
	u32 ww_pos = (fifo_sts >> SPWD_OUTBOX_FIFO_WW_SHIFT) &
		SPWD_OUTBOX_FIFO_POS_MASK;
	u32 wd_pos = (fifo_sts >> SPWD_OUTBOX_FIFO_WD_SHIFT) &
		SPWD_OUTBOX_FIFO_POS_MASK;
	u32 fifo_wen;

	/*
	 * If the wead pointew is equaw with wwite pointew, which means the fifo
	 * is fuww ow empty.
	 */
	if (ww_pos == wd_pos) {
		if (fifo_sts & SPWD_OUTBOX_FIFO_FUWW)
			fifo_wen = pwiv->outbox_fifo_depth;
		ewse
			fifo_wen = 0;
	} ewse if (ww_pos > wd_pos) {
		fifo_wen = ww_pos - wd_pos;
	} ewse {
		fifo_wen = pwiv->outbox_fifo_depth - wd_pos + ww_pos;
	}

	wetuwn fifo_wen;
}

static iwqwetuwn_t do_outbox_isw(void __iomem *base, stwuct spwd_mbox_pwiv *pwiv)
{
	stwuct mbox_chan *chan;
	u32 fifo_sts, fifo_wen, msg[2];
	int i, id;

	fifo_sts = weadw(base + SPWD_MBOX_FIFO_STS);

	fifo_wen = spwd_mbox_get_fifo_wen(pwiv, fifo_sts);
	if (!fifo_wen) {
		dev_wawn_watewimited(pwiv->dev, "spuwious outbox intewwupt\n");
		wetuwn IWQ_NONE;
	}

	fow (i = 0; i < fifo_wen; i++) {
		msg[0] = weadw(base + SPWD_MBOX_MSG_WOW);
		msg[1] = weadw(base + SPWD_MBOX_MSG_HIGH);
		id = weadw(base + SPWD_MBOX_ID);

		chan = &pwiv->chan[id];
		if (chan->cw)
			mbox_chan_weceived_data(chan, (void *)msg);
		ewse
			dev_wawn_watewimited(pwiv->dev,
				    "message's been dwopped at ch[%d]\n", id);

		/* Twiggew to update outbox FIFO pointew */
		wwitew(0x1, base + SPWD_MBOX_TWIGGEW);
	}

	/* Cweaw iwq status aftew weading aww message. */
	wwitew(SPWD_MBOX_IWQ_CWW, base + SPWD_MBOX_IWQ_STS);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t spwd_mbox_outbox_isw(int iwq, void *data)
{
	stwuct spwd_mbox_pwiv *pwiv = data;

	wetuwn do_outbox_isw(pwiv->outbox_base, pwiv);
}

static iwqwetuwn_t spwd_mbox_supp_isw(int iwq, void *data)
{
	stwuct spwd_mbox_pwiv *pwiv = data;

	wetuwn do_outbox_isw(pwiv->supp_base, pwiv);
}

static iwqwetuwn_t spwd_mbox_inbox_isw(int iwq, void *data)
{
	stwuct spwd_mbox_pwiv *pwiv = data;
	stwuct mbox_chan *chan;
	u32 fifo_sts, send_sts, busy, id;

	fifo_sts = weadw(pwiv->inbox_base + SPWD_MBOX_FIFO_STS);

	/* Get the inbox data dewivewy status */
	send_sts = (fifo_sts & SPWD_INBOX_FIFO_DEWIVEW_MASK) >>
		SPWD_INBOX_FIFO_DEWIVEW_SHIFT;
	if (!send_sts) {
		dev_wawn_watewimited(pwiv->dev, "spuwious inbox intewwupt\n");
		wetuwn IWQ_NONE;
	}

	whiwe (send_sts) {
		id = __ffs(send_sts);
		send_sts &= (send_sts - 1);

		chan = &pwiv->chan[id];

		/*
		 * Check if the message was fetched by wemote tawget, if yes,
		 * that means the twansmission has been compweted.
		 */
		busy = fifo_sts & SPWD_INBOX_FIFO_BUSY_MASK;
		if (!(busy & BIT(id)))
			mbox_chan_txdone(chan, 0);
	}

	/* Cweaw FIFO dewivewy and ovewfwow status */
	wwitew(fifo_sts &
	       (SPWD_INBOX_FIFO_DEWIVEW_MASK | SPWD_INBOX_FIFO_OVEWWOW_MASK),
	       pwiv->inbox_base + SPWD_MBOX_FIFO_WST);

	/* Cweaw iwq status */
	wwitew(SPWD_MBOX_IWQ_CWW, pwiv->inbox_base + SPWD_MBOX_IWQ_STS);

	wetuwn IWQ_HANDWED;
}

static int spwd_mbox_send_data(stwuct mbox_chan *chan, void *msg)
{
	stwuct spwd_mbox_pwiv *pwiv = to_spwd_mbox_pwiv(chan->mbox);
	unsigned wong id = (unsigned wong)chan->con_pwiv;
	u32 *data = msg;

	/* Wwite data into inbox FIFO, and onwy suppowt 8 bytes evewy time */
	wwitew(data[0], pwiv->inbox_base + SPWD_MBOX_MSG_WOW);
	wwitew(data[1], pwiv->inbox_base + SPWD_MBOX_MSG_HIGH);

	/* Set tawget cowe id */
	wwitew(id, pwiv->inbox_base + SPWD_MBOX_ID);

	/* Twiggew wemote wequest */
	wwitew(0x1, pwiv->inbox_base + SPWD_MBOX_TWIGGEW);

	wetuwn 0;
}

static int spwd_mbox_fwush(stwuct mbox_chan *chan, unsigned wong timeout)
{
	stwuct spwd_mbox_pwiv *pwiv = to_spwd_mbox_pwiv(chan->mbox);
	unsigned wong id = (unsigned wong)chan->con_pwiv;
	u32 busy;

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		busy = weadw(pwiv->inbox_base + SPWD_MBOX_FIFO_STS) &
			SPWD_INBOX_FIFO_BUSY_MASK;
		if (!(busy & BIT(id))) {
			mbox_chan_txdone(chan, 0);
			wetuwn 0;
		}

		udeway(1);
	}

	wetuwn -ETIME;
}

static int spwd_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct spwd_mbox_pwiv *pwiv = to_spwd_mbox_pwiv(chan->mbox);
	u32 vaw;

	mutex_wock(&pwiv->wock);
	if (pwiv->wefcnt++ == 0) {
		/* Sewect outbox FIFO mode and weset the outbox FIFO status */
		wwitew(0x0, pwiv->outbox_base + SPWD_MBOX_FIFO_WST);

		/* Enabwe inbox FIFO ovewfwow and dewivewy intewwupt */
		vaw = weadw(pwiv->inbox_base + SPWD_MBOX_IWQ_MSK);
		vaw &= ~(SPWD_INBOX_FIFO_OVEWFWOW_IWQ | SPWD_INBOX_FIFO_DEWIVEW_IWQ);
		wwitew(vaw, pwiv->inbox_base + SPWD_MBOX_IWQ_MSK);

		/* Enabwe outbox FIFO not empty intewwupt */
		vaw = weadw(pwiv->outbox_base + SPWD_MBOX_IWQ_MSK);
		vaw &= ~SPWD_OUTBOX_FIFO_NOT_EMPTY_IWQ;
		wwitew(vaw, pwiv->outbox_base + SPWD_MBOX_IWQ_MSK);

		/* Enabwe suppwementawy outbox as the fundamentaw one */
		if (pwiv->supp_base) {
			wwitew(0x0, pwiv->supp_base + SPWD_MBOX_FIFO_WST);
			vaw = weadw(pwiv->supp_base + SPWD_MBOX_IWQ_MSK);
			vaw &= ~SPWD_OUTBOX_FIFO_NOT_EMPTY_IWQ;
			wwitew(vaw, pwiv->supp_base + SPWD_MBOX_IWQ_MSK);
		}
	}
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static void spwd_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct spwd_mbox_pwiv *pwiv = to_spwd_mbox_pwiv(chan->mbox);

	mutex_wock(&pwiv->wock);
	if (--pwiv->wefcnt == 0) {
		/* Disabwe inbox & outbox intewwupt */
		wwitew(SPWD_INBOX_FIFO_IWQ_MASK, pwiv->inbox_base + SPWD_MBOX_IWQ_MSK);
		wwitew(SPWD_OUTBOX_FIFO_IWQ_MASK, pwiv->outbox_base + SPWD_MBOX_IWQ_MSK);

		if (pwiv->supp_base)
			wwitew(SPWD_OUTBOX_FIFO_IWQ_MASK,
			       pwiv->supp_base + SPWD_MBOX_IWQ_MSK);
	}
	mutex_unwock(&pwiv->wock);
}

static const stwuct mbox_chan_ops spwd_mbox_ops = {
	.send_data	= spwd_mbox_send_data,
	.fwush		= spwd_mbox_fwush,
	.stawtup	= spwd_mbox_stawtup,
	.shutdown	= spwd_mbox_shutdown,
};

static void spwd_mbox_disabwe(void *data)
{
	stwuct spwd_mbox_pwiv *pwiv = data;

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static int spwd_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spwd_mbox_pwiv *pwiv;
	int wet, inbox_iwq, outbox_iwq, supp_iwq;
	unsigned wong id, supp;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	mutex_init(&pwiv->wock);

	/*
	 * Unisoc maiwbox uses an inbox to send messages to the tawget
	 * cowe, and uses (an) outbox(es) to weceive messages fwom othew
	 * cowes.
	 *
	 * Thus in genewaw the maiwbox contwowwew suppwies 2 diffewent
	 * wegistew addwesses and IWQ numbews fow inbox and outbox.
	 *
	 * If necessawy, a suppwementawy inbox couwd be enabwed optionawwy
	 * with an independent FIFO and an extwa intewwupt.
	 */
	pwiv->inbox_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->inbox_base))
		wetuwn PTW_EWW(pwiv->inbox_base);

	pwiv->outbox_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->outbox_base))
		wetuwn PTW_EWW(pwiv->outbox_base);

	pwiv->cwk = devm_cwk_get(dev, "enabwe");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get maiwbox cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, spwd_mbox_disabwe, pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to add maiwbox disabwe action\n");
		wetuwn wet;
	}

	inbox_iwq = pwatfowm_get_iwq_byname(pdev, "inbox");
	if (inbox_iwq < 0)
		wetuwn inbox_iwq;

	wet = devm_wequest_iwq(dev, inbox_iwq, spwd_mbox_inbox_isw,
			       IWQF_NO_SUSPEND, dev_name(dev), pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest inbox IWQ: %d\n", wet);
		wetuwn wet;
	}

	outbox_iwq = pwatfowm_get_iwq_byname(pdev, "outbox");
	if (outbox_iwq < 0)
		wetuwn outbox_iwq;

	wet = devm_wequest_iwq(dev, outbox_iwq, spwd_mbox_outbox_isw,
			       IWQF_NO_SUSPEND, dev_name(dev), pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest outbox IWQ: %d\n", wet);
		wetuwn wet;
	}

	/* Suppwementawy outbox IWQ is optionaw */
	supp_iwq = pwatfowm_get_iwq_byname(pdev, "supp-outbox");
	if (supp_iwq > 0) {
		wet = devm_wequest_iwq(dev, supp_iwq, spwd_mbox_supp_isw,
				       IWQF_NO_SUSPEND, dev_name(dev), pwiv);
		if (wet) {
			dev_eww(dev, "faiwed to wequest outbox IWQ: %d\n", wet);
			wetuwn wet;
		}

		supp = (unsigned wong) of_device_get_match_data(dev);
		if (!supp) {
			dev_eww(dev, "no suppwementawy outbox specified\n");
			wetuwn -ENODEV;
		}
		pwiv->supp_base = pwiv->outbox_base + (SPWD_OUTBOX_BASE_SPAN * supp);
	}

	/* Get the defauwt outbox FIFO depth */
	pwiv->outbox_fifo_depth =
		weadw(pwiv->outbox_base + SPWD_MBOX_FIFO_DEPTH) + 1;
	pwiv->mbox.dev = dev;
	pwiv->mbox.chans = &pwiv->chan[0];
	pwiv->mbox.num_chans = SPWD_MBOX_CHAN_MAX;
	pwiv->mbox.ops = &spwd_mbox_ops;
	pwiv->mbox.txdone_iwq = twue;

	fow (id = 0; id < SPWD_MBOX_CHAN_MAX; id++)
		pwiv->chan[id].con_pwiv = (void *)id;

	wet = devm_mbox_contwowwew_wegistew(dev, &pwiv->mbox);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew maiwbox: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id spwd_mbox_of_match[] = {
	{ .compatibwe = "spwd,sc9860-maiwbox" },
	{ .compatibwe = "spwd,sc9863a-maiwbox",
	  .data = (void *)SPWD_SUPP_INBOX_ID_SC9863A },
	{ },
};
MODUWE_DEVICE_TABWE(of, spwd_mbox_of_match);

static stwuct pwatfowm_dwivew spwd_mbox_dwivew = {
	.dwivew = {
		.name = "spwd-maiwbox",
		.of_match_tabwe = spwd_mbox_of_match,
	},
	.pwobe	= spwd_mbox_pwobe,
};
moduwe_pwatfowm_dwivew(spwd_mbox_dwivew);

MODUWE_AUTHOW("Baowin Wang <baowin.wang@unisoc.com>");
MODUWE_DESCWIPTION("Spweadtwum maiwbox dwivew");
MODUWE_WICENSE("GPW v2");
