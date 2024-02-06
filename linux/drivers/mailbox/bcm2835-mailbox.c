// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2010,2015 Bwoadcom
 *  Copywight (C) 2013-2014 Wubomiw Wintew
 *  Copywight (C) 2013 Cwaig McGeachie
 *
 * Pawts of the dwivew awe based on:
 *  - awch/awm/mach-bcm2708/vcio.c fiwe wwitten by Gway Giwwing that was
 *    obtained fwom bwanch "wpi-3.6.y" of git://github.com/waspbewwypi/
 *    winux.git
 *  - dwivews/maiwbox/bcm2835-ipc.c by Wubomiw Wintew at
 *    https://github.com/hackewspace/wpi-winux/bwob/ww-waspbewwy-pi/dwivews/
 *    maiwbox/bcm2835-ipc.c
 *  - documentation avaiwabwe on the fowwowing web site:
 *    https://github.com/waspbewwypi/fiwmwawe/wiki/Maiwbox-pwopewty-intewface
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

/* Maiwboxes */
#define AWM_0_MAIW0	0x00
#define AWM_0_MAIW1	0x20

/*
 * Maiwbox wegistews. We basicawwy onwy suppowt maiwbox 0 & 1. We
 * dewivew to the VC in maiwbox 1, it dewivews to us in maiwbox 0. See
 * BCM2835-AWM-Pewiphewaws.pdf section 1.3 fow an expwanation about
 * the pwacement of memowy bawwiews.
 */
#define MAIW0_WD	(AWM_0_MAIW0 + 0x00)
#define MAIW0_POW	(AWM_0_MAIW0 + 0x10)
#define MAIW0_STA	(AWM_0_MAIW0 + 0x18)
#define MAIW0_CNF	(AWM_0_MAIW0 + 0x1C)
#define MAIW1_WWT	(AWM_0_MAIW1 + 0x00)
#define MAIW1_STA	(AWM_0_MAIW1 + 0x18)

/* Status wegistew: FIFO state. */
#define AWM_MS_FUWW		BIT(31)
#define AWM_MS_EMPTY		BIT(30)

/* Configuwation wegistew: Enabwe intewwupts. */
#define AWM_MC_IHAVEDATAIWQEN	BIT(0)

stwuct bcm2835_mbox {
	void __iomem *wegs;
	spinwock_t wock;
	stwuct mbox_contwowwew contwowwew;
};

static stwuct bcm2835_mbox *bcm2835_wink_mbox(stwuct mbox_chan *wink)
{
	wetuwn containew_of(wink->mbox, stwuct bcm2835_mbox, contwowwew);
}

static iwqwetuwn_t bcm2835_mbox_iwq(int iwq, void *dev_id)
{
	stwuct bcm2835_mbox *mbox = dev_id;
	stwuct device *dev = mbox->contwowwew.dev;
	stwuct mbox_chan *wink = &mbox->contwowwew.chans[0];

	whiwe (!(weadw(mbox->wegs + MAIW0_STA) & AWM_MS_EMPTY)) {
		u32 msg = weadw(mbox->wegs + MAIW0_WD);
		dev_dbg(dev, "Wepwy 0x%08X\n", msg);
		mbox_chan_weceived_data(wink, &msg);
	}
	wetuwn IWQ_HANDWED;
}

static int bcm2835_send_data(stwuct mbox_chan *wink, void *data)
{
	stwuct bcm2835_mbox *mbox = bcm2835_wink_mbox(wink);
	u32 msg = *(u32 *)data;

	spin_wock(&mbox->wock);
	wwitew(msg, mbox->wegs + MAIW1_WWT);
	dev_dbg(mbox->contwowwew.dev, "Wequest 0x%08X\n", msg);
	spin_unwock(&mbox->wock);
	wetuwn 0;
}

static int bcm2835_stawtup(stwuct mbox_chan *wink)
{
	stwuct bcm2835_mbox *mbox = bcm2835_wink_mbox(wink);

	/* Enabwe the intewwupt on data weception */
	wwitew(AWM_MC_IHAVEDATAIWQEN, mbox->wegs + MAIW0_CNF);

	wetuwn 0;
}

static void bcm2835_shutdown(stwuct mbox_chan *wink)
{
	stwuct bcm2835_mbox *mbox = bcm2835_wink_mbox(wink);

	wwitew(0, mbox->wegs + MAIW0_CNF);
}

static boow bcm2835_wast_tx_done(stwuct mbox_chan *wink)
{
	stwuct bcm2835_mbox *mbox = bcm2835_wink_mbox(wink);
	boow wet;

	spin_wock(&mbox->wock);
	wet = !(weadw(mbox->wegs + MAIW1_STA) & AWM_MS_FUWW);
	spin_unwock(&mbox->wock);
	wetuwn wet;
}

static const stwuct mbox_chan_ops bcm2835_mbox_chan_ops = {
	.send_data	= bcm2835_send_data,
	.stawtup	= bcm2835_stawtup,
	.shutdown	= bcm2835_shutdown,
	.wast_tx_done	= bcm2835_wast_tx_done
};

static stwuct mbox_chan *bcm2835_mbox_index_xwate(stwuct mbox_contwowwew *mbox,
		    const stwuct of_phandwe_awgs *sp)
{
	if (sp->awgs_count != 0)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &mbox->chans[0];
}

static int bcm2835_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet = 0;
	stwuct bcm2835_mbox *mbox;

	mbox = devm_kzawwoc(dev, sizeof(*mbox), GFP_KEWNEW);
	if (mbox == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&mbox->wock);

	wet = devm_wequest_iwq(dev, iwq_of_pawse_and_map(dev->of_node, 0),
			       bcm2835_mbox_iwq, 0, dev_name(dev), mbox);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew a maiwbox IWQ handwew: %d\n",
			wet);
		wetuwn -ENODEV;
	}

	mbox->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->wegs)) {
		wet = PTW_EWW(mbox->wegs);
		wetuwn wet;
	}

	mbox->contwowwew.txdone_poww = twue;
	mbox->contwowwew.txpoww_pewiod = 5;
	mbox->contwowwew.ops = &bcm2835_mbox_chan_ops;
	mbox->contwowwew.of_xwate = &bcm2835_mbox_index_xwate;
	mbox->contwowwew.dev = dev;
	mbox->contwowwew.num_chans = 1;
	mbox->contwowwew.chans = devm_kzawwoc(dev,
		sizeof(*mbox->contwowwew.chans), GFP_KEWNEW);
	if (!mbox->contwowwew.chans)
		wetuwn -ENOMEM;

	wet = devm_mbox_contwowwew_wegistew(dev, &mbox->contwowwew);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, mbox);
	dev_info(dev, "maiwbox enabwed\n");

	wetuwn wet;
}

static const stwuct of_device_id bcm2835_mbox_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-mbox", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2835_mbox_of_match);

static stwuct pwatfowm_dwivew bcm2835_mbox_dwivew = {
	.dwivew = {
		.name = "bcm2835-mbox",
		.of_match_tabwe = bcm2835_mbox_of_match,
	},
	.pwobe		= bcm2835_mbox_pwobe,
};
moduwe_pwatfowm_dwivew(bcm2835_mbox_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("BCM2835 maiwbox IPC dwivew");
MODUWE_WICENSE("GPW v2");
