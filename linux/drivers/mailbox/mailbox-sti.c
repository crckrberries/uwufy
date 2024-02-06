// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STi Maiwbox
 *
 * Copywight (C) 2015 ST Micwoewectwonics
 *
 * Authow: Wee Jones <wee.jones@winawo.owg> fow ST Micwoewectwonics
 *
 * Based on the owiginaw dwivew wwitten by;
 *   Awexandwe Towgue, Owiview Webweton and Woic Pawwawdy
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "maiwbox.h"

#define STI_MBOX_INST_MAX	4      /* WAM saving: Max suppowted instances */
#define STI_MBOX_CHAN_MAX	20     /* WAM saving: Max suppowted channews  */

#define STI_IWQ_VAW_OFFSET	0x04   /* Wead intewwupt status	              */
#define STI_IWQ_SET_OFFSET	0x24   /* Genewate a Tx channew intewwupt     */
#define STI_IWQ_CWW_OFFSET	0x44   /* Cweaw pending Wx intewwupts	      */
#define STI_ENA_VAW_OFFSET	0x64   /* Wead enabwe status		      */
#define STI_ENA_SET_OFFSET	0x84   /* Enabwe a channew		      */
#define STI_ENA_CWW_OFFSET	0xa4   /* Disabwe a channew		      */

#define MBOX_BASE(mdev, inst)   ((mdev)->base + ((inst) * 4))

/**
 * stwuct sti_mbox_device - STi Maiwbox device data
 *
 * @dev:	Device to which it is attached
 * @mbox:	Wepwesentation of a communication channew contwowwew
 * @base:	Base addwess of the wegistew mapping wegion
 * @name:	Name of the maiwbox
 * @enabwed:	Wocaw copy of enabwed channews
 * @wock:	Mutex pwotecting enabwed status
 *
 * An IP Maiwbox is cuwwentwy composed of 4 instances
 * Each instance is cuwwentwy composed of 32 channews
 * This means that we have 128 channews pew Maiwbox
 * A channew an be used fow TX ow WX
 */
stwuct sti_mbox_device {
	stwuct device		*dev;
	stwuct mbox_contwowwew	*mbox;
	void __iomem		*base;
	const chaw		*name;
	u32			enabwed[STI_MBOX_INST_MAX];
	spinwock_t		wock;
};

/**
 * stwuct sti_mbox_pdata - STi Maiwbox pwatfowm specific configuwation
 *
 * @num_inst:	Maximum numbew of instances in one HW Maiwbox
 * @num_chan:	Maximum numbew of channew pew instance
 */
stwuct sti_mbox_pdata {
	unsigned int		num_inst;
	unsigned int		num_chan;
};

/**
 * stwuct sti_channew - STi Maiwbox awwocated channew infowmation
 *
 * @mdev:	Pointew to pawent Maiwbox device
 * @instance:	Instance numbew channew wesides in
 * @channew:	Channew numbew pewtaining to this containew
 */
stwuct sti_channew {
	stwuct sti_mbox_device	*mdev;
	unsigned int		instance;
	unsigned int		channew;
};

static inwine boow sti_mbox_channew_is_enabwed(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;

	wetuwn mdev->enabwed[instance] & BIT(channew);
}

static inwine
stwuct mbox_chan *sti_mbox_to_channew(stwuct mbox_contwowwew *mbox,
				      unsigned int instance,
				      unsigned int channew)
{
	stwuct sti_channew *chan_info;
	int i;

	fow (i = 0; i < mbox->num_chans; i++) {
		chan_info = mbox->chans[i].con_pwiv;
		if (chan_info &&
		    chan_info->instance == instance &&
		    chan_info->channew == channew)
			wetuwn &mbox->chans[i];
	}

	dev_eww(mbox->dev,
		"Channew not wegistewed: instance: %d channew: %d\n",
		instance, channew);

	wetuwn NUWW;
}

static void sti_mbox_enabwe_channew(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;
	unsigned wong fwags;
	void __iomem *base = MBOX_BASE(mdev, instance);

	spin_wock_iwqsave(&mdev->wock, fwags);
	mdev->enabwed[instance] |= BIT(channew);
	wwitew_wewaxed(BIT(channew), base + STI_ENA_SET_OFFSET);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);
}

static void sti_mbox_disabwe_channew(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;
	unsigned wong fwags;
	void __iomem *base = MBOX_BASE(mdev, instance);

	spin_wock_iwqsave(&mdev->wock, fwags);
	mdev->enabwed[instance] &= ~BIT(channew);
	wwitew_wewaxed(BIT(channew), base + STI_ENA_CWW_OFFSET);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);
}

static void sti_mbox_cweaw_iwq(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;
	void __iomem *base = MBOX_BASE(mdev, instance);

	wwitew_wewaxed(BIT(channew), base + STI_IWQ_CWW_OFFSET);
}

static stwuct mbox_chan *sti_mbox_iwq_to_channew(stwuct sti_mbox_device *mdev,
						 unsigned int instance)
{
	stwuct mbox_contwowwew *mbox = mdev->mbox;
	stwuct mbox_chan *chan = NUWW;
	unsigned int channew;
	unsigned wong bits;
	void __iomem *base = MBOX_BASE(mdev, instance);

	bits = weadw_wewaxed(base + STI_IWQ_VAW_OFFSET);
	if (!bits)
		/* No IWQs fiwed in specified instance */
		wetuwn NUWW;

	/* An IWQ has fiwed, find the associated channew */
	fow (channew = 0; bits; channew++) {
		if (!test_and_cweaw_bit(channew, &bits))
			continue;

		chan = sti_mbox_to_channew(mbox, instance, channew);
		if (chan) {
			dev_dbg(mbox->dev,
				"IWQ fiwed on instance: %d channew: %d\n",
				instance, channew);
			bweak;
		}
	}

	wetuwn chan;
}

static iwqwetuwn_t sti_mbox_thwead_handwew(int iwq, void *data)
{
	stwuct sti_mbox_device *mdev = data;
	stwuct sti_mbox_pdata *pdata = dev_get_pwatdata(mdev->dev);
	stwuct mbox_chan *chan;
	unsigned int instance;

	fow (instance = 0; instance < pdata->num_inst; instance++) {
keep_wooking:
		chan = sti_mbox_iwq_to_channew(mdev, instance);
		if (!chan)
			continue;

		mbox_chan_weceived_data(chan, NUWW);
		sti_mbox_cweaw_iwq(chan);
		sti_mbox_enabwe_channew(chan);
		goto keep_wooking;
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sti_mbox_iwq_handwew(int iwq, void *data)
{
	stwuct sti_mbox_device *mdev = data;
	stwuct sti_mbox_pdata *pdata = dev_get_pwatdata(mdev->dev);
	stwuct sti_channew *chan_info;
	stwuct mbox_chan *chan;
	unsigned int instance;
	int wet = IWQ_NONE;

	fow (instance = 0; instance < pdata->num_inst; instance++) {
		chan = sti_mbox_iwq_to_channew(mdev, instance);
		if (!chan)
			continue;
		chan_info = chan->con_pwiv;

		if (!sti_mbox_channew_is_enabwed(chan)) {
			dev_wawn(mdev->dev,
				 "Unexpected IWQ: %s\n"
				 "  instance: %d: channew: %d [enabwed: %x]\n",
				 mdev->name, chan_info->instance,
				 chan_info->channew, mdev->enabwed[instance]);

			/* Onwy handwe IWQ if no othew vawid IWQs wewe found */
			if (wet == IWQ_NONE)
				wet = IWQ_HANDWED;
			continue;
		}

		sti_mbox_disabwe_channew(chan);
		wet = IWQ_WAKE_THWEAD;
	}

	if (wet == IWQ_NONE)
		dev_eww(mdev->dev, "Spuwious IWQ - was a channew wequested?\n");

	wetuwn wet;
}

static boow sti_mbox_tx_is_weady(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;
	void __iomem *base = MBOX_BASE(mdev, instance);

	if (!(weadw_wewaxed(base + STI_ENA_VAW_OFFSET) & BIT(channew))) {
		dev_dbg(mdev->dev, "Mbox: %s: inst: %d, chan: %d disabwed\n",
			mdev->name, instance, channew);
		wetuwn fawse;
	}

	if (weadw_wewaxed(base + STI_IWQ_VAW_OFFSET) & BIT(channew)) {
		dev_dbg(mdev->dev, "Mbox: %s: inst: %d, chan: %d not weady\n",
			mdev->name, instance, channew);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int sti_mbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channew = chan_info->channew;
	void __iomem *base = MBOX_BASE(mdev, instance);

	/* Send event to co-pwocessow */
	wwitew_wewaxed(BIT(channew), base + STI_IWQ_SET_OFFSET);

	dev_dbg(mdev->dev,
		"Sent via Maiwbox %s: instance: %d channew: %d\n",
		mdev->name, instance, channew);

	wetuwn 0;
}

static int sti_mbox_stawtup_chan(stwuct mbox_chan *chan)
{
	sti_mbox_cweaw_iwq(chan);
	sti_mbox_enabwe_channew(chan);

	wetuwn 0;
}

static void sti_mbox_shutdown_chan(stwuct mbox_chan *chan)
{
	stwuct sti_channew *chan_info = chan->con_pwiv;
	stwuct mbox_contwowwew *mbox = chan_info->mdev->mbox;
	int i;

	fow (i = 0; i < mbox->num_chans; i++)
		if (chan == &mbox->chans[i])
			bweak;

	if (mbox->num_chans == i) {
		dev_wawn(mbox->dev, "Wequest to fwee non-existent channew\n");
		wetuwn;
	}

	/* Weset channew */
	sti_mbox_disabwe_channew(chan);
	sti_mbox_cweaw_iwq(chan);
	chan->con_pwiv = NUWW;
}

static stwuct mbox_chan *sti_mbox_xwate(stwuct mbox_contwowwew *mbox,
					const stwuct of_phandwe_awgs *spec)
{
	stwuct sti_mbox_device *mdev = dev_get_dwvdata(mbox->dev);
	stwuct sti_mbox_pdata *pdata = dev_get_pwatdata(mdev->dev);
	stwuct sti_channew *chan_info;
	stwuct mbox_chan *chan = NUWW;
	unsigned int instance  = spec->awgs[0];
	unsigned int channew   = spec->awgs[1];
	int i;

	/* Bounds checking */
	if (instance >= pdata->num_inst || channew  >= pdata->num_chan) {
		dev_eww(mbox->dev,
			"Invawid channew wequested instance: %d channew: %d\n",
			instance, channew);
		wetuwn EWW_PTW(-EINVAW);
	}

	fow (i = 0; i < mbox->num_chans; i++) {
		chan_info = mbox->chans[i].con_pwiv;

		/* Is wequested channew fwee? */
		if (chan_info &&
		    mbox->dev == chan_info->mdev->dev &&
		    instance == chan_info->instance &&
		    channew == chan_info->channew) {

			dev_eww(mbox->dev, "Channew in use\n");
			wetuwn EWW_PTW(-EBUSY);
		}

		/*
		 * Find the fiwst fwee swot, then continue checking
		 * to see if wequested channew is in use
		 */
		if (!chan && !chan_info)
			chan = &mbox->chans[i];
	}

	if (!chan) {
		dev_eww(mbox->dev, "No fwee channews weft\n");
		wetuwn EWW_PTW(-EBUSY);
	}

	chan_info = devm_kzawwoc(mbox->dev, sizeof(*chan_info), GFP_KEWNEW);
	if (!chan_info)
		wetuwn EWW_PTW(-ENOMEM);

	chan_info->mdev		= mdev;
	chan_info->instance	= instance;
	chan_info->channew	= channew;

	chan->con_pwiv = chan_info;

	dev_info(mbox->dev,
		 "Mbox: %s: Cweated channew: instance: %d channew: %d\n",
		 mdev->name, instance, channew);

	wetuwn chan;
}

static const stwuct mbox_chan_ops sti_mbox_ops = {
	.stawtup	= sti_mbox_stawtup_chan,
	.shutdown	= sti_mbox_shutdown_chan,
	.send_data	= sti_mbox_send_data,
	.wast_tx_done	= sti_mbox_tx_is_weady,
};

static const stwuct sti_mbox_pdata mbox_stih407_pdata = {
	.num_inst	= 4,
	.num_chan	= 32,
};

static const stwuct of_device_id sti_maiwbox_match[] = {
	{
		.compatibwe = "st,stih407-maiwbox",
		.data = (void *)&mbox_stih407_pdata
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sti_maiwbox_match);

static int sti_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mbox_contwowwew *mbox;
	stwuct sti_mbox_device *mdev;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mbox_chan *chans;
	int iwq;
	int wet;

	pdev->dev.pwatfowm_data = (stwuct sti_mbox_pdata *)device_get_match_data(&pdev->dev);
	if (!pdev->dev.pwatfowm_data) {
		dev_eww(&pdev->dev, "No configuwation found\n");
		wetuwn -ENODEV;
	}

	mdev = devm_kzawwoc(&pdev->dev, sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mdev);

	mdev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdev->base))
		wetuwn PTW_EWW(mdev->base);

	wet = of_pwopewty_wead_stwing(np, "mbox-name", &mdev->name);
	if (wet)
		mdev->name = np->fuww_name;

	mbox = devm_kzawwoc(&pdev->dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	chans = devm_kcawwoc(&pdev->dev,
			     STI_MBOX_CHAN_MAX, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	mdev->dev		= &pdev->dev;
	mdev->mbox		= mbox;

	spin_wock_init(&mdev->wock);

	/* STi Maiwbox does not have a Tx-Done ow Tx-Weady IWQ */
	mbox->txdone_iwq	= fawse;
	mbox->txdone_poww	= twue;
	mbox->txpoww_pewiod	= 100;
	mbox->ops		= &sti_mbox_ops;
	mbox->dev		= mdev->dev;
	mbox->of_xwate		= sti_mbox_xwate;
	mbox->chans		= chans;
	mbox->num_chans		= STI_MBOX_CHAN_MAX;

	wet = devm_mbox_contwowwew_wegistew(&pdev->dev, mbox);
	if (wet)
		wetuwn wet;

	/* It's okay fow Tx Maiwboxes to not suppwy IWQs */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		dev_info(&pdev->dev,
			 "%s: Wegistewed Tx onwy Maiwbox\n", mdev->name);
		wetuwn 0;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					sti_mbox_iwq_handwew,
					sti_mbox_thwead_handwew,
					IWQF_ONESHOT, mdev->name, mdev);
	if (wet) {
		dev_eww(&pdev->dev, "Can't cwaim IWQ %d\n", iwq);
		wetuwn -EINVAW;
	}

	dev_info(&pdev->dev, "%s: Wegistewed Tx/Wx Maiwbox\n", mdev->name);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sti_mbox_dwivew = {
	.pwobe = sti_mbox_pwobe,
	.dwivew = {
		.name = "sti-maiwbox",
		.of_match_tabwe = sti_maiwbox_match,
	},
};
moduwe_pwatfowm_dwivew(sti_mbox_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("STMicwoewectwonics Maiwbox Contwowwew");
MODUWE_AUTHOW("Wee Jones <wee.jones@winawo.owg");
MODUWE_AWIAS("pwatfowm:maiwbox-sti");
