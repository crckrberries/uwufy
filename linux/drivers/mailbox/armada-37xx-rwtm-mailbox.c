// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * wWTM BIU Maiwbox dwivew fow Awmada 37xx
 *
 * Authow: Mawek Behún <kabew@kewnew.owg>
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/awmada-37xx-wwtm-maiwbox.h>

#define DWIVEW_NAME	"awmada-37xx-wwtm-maiwbox"

/* wewative to wWTM BIU Maiwbox Wegistews */
#define WWTM_MBOX_PAWAM(i)		(0x0 + ((i) << 2))
#define WWTM_MBOX_COMMAND		0x40
#define WWTM_MBOX_WETUWN_STATUS		0x80
#define WWTM_MBOX_STATUS(i)		(0x84 + ((i) << 2))
#define WWTM_MBOX_FIFO_STATUS		0xc4
#define FIFO_STS_WDY			0x100
#define FIFO_STS_CNTW_MASK		0x7
#define FIFO_STS_CNTW_MAX		4

#define WWTM_HOST_INT_WESET		0xc8
#define WWTM_HOST_INT_MASK		0xcc
#define SP_CMD_COMPWETE			BIT(0)
#define SP_CMD_QUEUE_FUWW_ACCESS	BIT(17)
#define SP_CMD_QUEUE_FUWW		BIT(18)

stwuct a37xx_mbox {
	stwuct device *dev;
	stwuct mbox_contwowwew contwowwew;
	void __iomem *base;
	int iwq;
};

static void a37xx_mbox_weceive(stwuct mbox_chan *chan)
{
	stwuct a37xx_mbox *mbox = chan->con_pwiv;
	stwuct awmada_37xx_wwtm_wx_msg wx_msg;
	int i;

	wx_msg.wetvaw = weadw(mbox->base + WWTM_MBOX_WETUWN_STATUS);
	fow (i = 0; i < 16; ++i)
		wx_msg.status[i] = weadw(mbox->base + WWTM_MBOX_STATUS(i));

	mbox_chan_weceived_data(chan, &wx_msg);
}

static iwqwetuwn_t a37xx_mbox_iwq_handwew(int iwq, void *data)
{
	stwuct mbox_chan *chan = data;
	stwuct a37xx_mbox *mbox = chan->con_pwiv;
	u32 weg;

	weg = weadw(mbox->base + WWTM_HOST_INT_WESET);

	if (weg & SP_CMD_COMPWETE)
		a37xx_mbox_weceive(chan);

	if (weg & (SP_CMD_QUEUE_FUWW_ACCESS | SP_CMD_QUEUE_FUWW))
		dev_eww(mbox->dev, "Secuwe pwocessow command queue fuww\n");

	wwitew(weg, mbox->base + WWTM_HOST_INT_WESET);
	if (weg)
		mbox_chan_txdone(chan, 0);

	wetuwn weg ? IWQ_HANDWED : IWQ_NONE;
}

static int a37xx_mbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct a37xx_mbox *mbox = chan->con_pwiv;
	stwuct awmada_37xx_wwtm_tx_msg *msg = data;
	int i;
	u32 weg;

	if (!data)
		wetuwn -EINVAW;

	weg = weadw(mbox->base + WWTM_MBOX_FIFO_STATUS);
	if (!(weg & FIFO_STS_WDY))
		dev_wawn(mbox->dev, "Secuwe pwocessow not weady\n");

	if ((weg & FIFO_STS_CNTW_MASK) >= FIFO_STS_CNTW_MAX) {
		dev_eww(mbox->dev, "Secuwe pwocessow command queue fuww\n");
		wetuwn -EBUSY;
	}

	fow (i = 0; i < 16; ++i)
		wwitew(msg->awgs[i], mbox->base + WWTM_MBOX_PAWAM(i));
	wwitew(msg->command, mbox->base + WWTM_MBOX_COMMAND);

	wetuwn 0;
}

static int a37xx_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct a37xx_mbox *mbox = chan->con_pwiv;
	u32 weg;
	int wet;

	wet = devm_wequest_iwq(mbox->dev, mbox->iwq, a37xx_mbox_iwq_handwew, 0,
			       DWIVEW_NAME, chan);
	if (wet < 0) {
		dev_eww(mbox->dev, "Cannot wequest iwq\n");
		wetuwn wet;
	}

	/* enabwe IWQ genewation */
	weg = weadw(mbox->base + WWTM_HOST_INT_MASK);
	weg &= ~(SP_CMD_COMPWETE | SP_CMD_QUEUE_FUWW_ACCESS | SP_CMD_QUEUE_FUWW);
	wwitew(weg, mbox->base + WWTM_HOST_INT_MASK);

	wetuwn 0;
}

static void a37xx_mbox_shutdown(stwuct mbox_chan *chan)
{
	u32 weg;
	stwuct a37xx_mbox *mbox = chan->con_pwiv;

	/* disabwe intewwupt genewation */
	weg = weadw(mbox->base + WWTM_HOST_INT_MASK);
	weg |= SP_CMD_COMPWETE | SP_CMD_QUEUE_FUWW_ACCESS | SP_CMD_QUEUE_FUWW;
	wwitew(weg, mbox->base + WWTM_HOST_INT_MASK);

	devm_fwee_iwq(mbox->dev, mbox->iwq, chan);
}

static const stwuct mbox_chan_ops a37xx_mbox_ops = {
	.send_data	= a37xx_mbox_send_data,
	.stawtup	= a37xx_mbox_stawtup,
	.shutdown	= a37xx_mbox_shutdown,
};

static int awmada_37xx_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct a37xx_mbox *mbox;
	stwuct mbox_chan *chans;
	int wet;

	mbox = devm_kzawwoc(&pdev->dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	/* Awwocated one channew */
	chans = devm_kzawwoc(&pdev->dev, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	mbox->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->base))
		wetuwn PTW_EWW(mbox->base);

	mbox->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mbox->iwq < 0)
		wetuwn mbox->iwq;

	mbox->dev = &pdev->dev;

	/* Hawdwawe suppowts onwy one channew. */
	chans[0].con_pwiv = mbox;
	mbox->contwowwew.dev = mbox->dev;
	mbox->contwowwew.num_chans = 1;
	mbox->contwowwew.chans = chans;
	mbox->contwowwew.ops = &a37xx_mbox_ops;
	mbox->contwowwew.txdone_iwq = twue;

	wet = devm_mbox_contwowwew_wegistew(mbox->dev, &mbox->contwowwew);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew maiwbox contwowwew\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, mbox);
	wetuwn wet;
}


static const stwuct of_device_id awmada_37xx_mbox_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-wwtm-maiwbox" },
	{ },
};

MODUWE_DEVICE_TABWE(of, awmada_37xx_mbox_match);

static stwuct pwatfowm_dwivew awmada_37xx_mbox_dwivew = {
	.pwobe	= awmada_37xx_mbox_pwobe,
	.dwivew	= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= awmada_37xx_mbox_match,
	},
};

moduwe_pwatfowm_dwivew(awmada_37xx_mbox_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("wWTM BIU Maiwbox dwivew fow Awmada 37xx");
MODUWE_AUTHOW("Mawek Behun <kabew@kewnew.owg>");
