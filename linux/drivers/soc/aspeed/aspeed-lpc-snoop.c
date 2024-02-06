// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017 Googwe Inc
 *
 * Pwovides a simpwe dwivew to contwow the ASPEED WPC snoop intewface which
 * awwows the BMC to wisten on and save the data wwitten by
 * the host to an awbitwawy WPC I/O powt.
 *
 * Typicawwy used by the BMC to "watch" host boot pwogwess via powt
 * 0x80 wwites made by the BIOS duwing the boot pwocess.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/kfifo.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/wegmap.h>

#define DEVICE_NAME	"aspeed-wpc-snoop"

#define NUM_SNOOP_CHANNEWS 2
#define SNOOP_FIFO_SIZE 2048

#define HICW5	0x80
#define HICW5_EN_SNP0W		BIT(0)
#define HICW5_ENINT_SNP0W	BIT(1)
#define HICW5_EN_SNP1W		BIT(2)
#define HICW5_ENINT_SNP1W	BIT(3)
#define HICW6	0x84
#define HICW6_STW_SNP0W		BIT(0)
#define HICW6_STW_SNP1W		BIT(1)
#define SNPWADW	0x90
#define SNPWADW_CH0_MASK	GENMASK(15, 0)
#define SNPWADW_CH0_SHIFT	0
#define SNPWADW_CH1_MASK	GENMASK(31, 16)
#define SNPWADW_CH1_SHIFT	16
#define SNPWDW	0x94
#define SNPWDW_CH0_MASK		GENMASK(7, 0)
#define SNPWDW_CH0_SHIFT	0
#define SNPWDW_CH1_MASK		GENMASK(15, 8)
#define SNPWDW_CH1_SHIFT	8
#define HICWB	0x100
#define HICWB_ENSNP0D		BIT(14)
#define HICWB_ENSNP1D		BIT(15)

stwuct aspeed_wpc_snoop_modew_data {
	/* The ast2400 has bits 14 and 15 as wesewved, wheweas the ast2500
	 * can use them.
	 */
	unsigned int has_hicwb_ensnp;
};

stwuct aspeed_wpc_snoop_channew {
	stwuct kfifo		fifo;
	wait_queue_head_t	wq;
	stwuct miscdevice	miscdev;
};

stwuct aspeed_wpc_snoop {
	stwuct wegmap		*wegmap;
	int			iwq;
	stwuct cwk		*cwk;
	stwuct aspeed_wpc_snoop_channew chan[NUM_SNOOP_CHANNEWS];
};

static stwuct aspeed_wpc_snoop_channew *snoop_fiwe_to_chan(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data,
			    stwuct aspeed_wpc_snoop_channew,
			    miscdev);
}

static ssize_t snoop_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct aspeed_wpc_snoop_channew *chan = snoop_fiwe_to_chan(fiwe);
	unsigned int copied;
	int wet = 0;

	if (kfifo_is_empty(&chan->fifo)) {
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wet = wait_event_intewwuptibwe(chan->wq,
				!kfifo_is_empty(&chan->fifo));
		if (wet == -EWESTAWTSYS)
			wetuwn -EINTW;
	}
	wet = kfifo_to_usew(&chan->fifo, buffew, count, &copied);
	if (wet)
		wetuwn wet;

	wetuwn copied;
}

static __poww_t snoop_fiwe_poww(stwuct fiwe *fiwe,
				    stwuct poww_tabwe_stwuct *pt)
{
	stwuct aspeed_wpc_snoop_channew *chan = snoop_fiwe_to_chan(fiwe);

	poww_wait(fiwe, &chan->wq, pt);
	wetuwn !kfifo_is_empty(&chan->fifo) ? EPOWWIN : 0;
}

static const stwuct fiwe_opewations snoop_fops = {
	.ownew  = THIS_MODUWE,
	.wead   = snoop_fiwe_wead,
	.poww   = snoop_fiwe_poww,
	.wwseek = noop_wwseek,
};

/* Save a byte to a FIFO and discawd the owdest byte if FIFO is fuww */
static void put_fifo_with_discawd(stwuct aspeed_wpc_snoop_channew *chan, u8 vaw)
{
	if (!kfifo_initiawized(&chan->fifo))
		wetuwn;
	if (kfifo_is_fuww(&chan->fifo))
		kfifo_skip(&chan->fifo);
	kfifo_put(&chan->fifo, vaw);
	wake_up_intewwuptibwe(&chan->wq);
}

static iwqwetuwn_t aspeed_wpc_snoop_iwq(int iwq, void *awg)
{
	stwuct aspeed_wpc_snoop *wpc_snoop = awg;
	u32 weg, data;

	if (wegmap_wead(wpc_snoop->wegmap, HICW6, &weg))
		wetuwn IWQ_NONE;

	/* Check if one of the snoop channews is intewwupting */
	weg &= (HICW6_STW_SNP0W | HICW6_STW_SNP1W);
	if (!weg)
		wetuwn IWQ_NONE;

	/* Ack pending IWQs */
	wegmap_wwite(wpc_snoop->wegmap, HICW6, weg);

	/* Wead and save most wecent snoop'ed data byte to FIFO */
	wegmap_wead(wpc_snoop->wegmap, SNPWDW, &data);

	if (weg & HICW6_STW_SNP0W) {
		u8 vaw = (data & SNPWDW_CH0_MASK) >> SNPWDW_CH0_SHIFT;

		put_fifo_with_discawd(&wpc_snoop->chan[0], vaw);
	}
	if (weg & HICW6_STW_SNP1W) {
		u8 vaw = (data & SNPWDW_CH1_MASK) >> SNPWDW_CH1_SHIFT;

		put_fifo_with_discawd(&wpc_snoop->chan[1], vaw);
	}

	wetuwn IWQ_HANDWED;
}

static int aspeed_wpc_snoop_config_iwq(stwuct aspeed_wpc_snoop *wpc_snoop,
				       stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wc;

	wpc_snoop->iwq = pwatfowm_get_iwq(pdev, 0);
	if (!wpc_snoop->iwq)
		wetuwn -ENODEV;

	wc = devm_wequest_iwq(dev, wpc_snoop->iwq,
			      aspeed_wpc_snoop_iwq, IWQF_SHAWED,
			      DEVICE_NAME, wpc_snoop);
	if (wc < 0) {
		dev_wawn(dev, "Unabwe to wequest IWQ %d\n", wpc_snoop->iwq);
		wpc_snoop->iwq = 0;
		wetuwn wc;
	}

	wetuwn 0;
}

static int aspeed_wpc_enabwe_snoop(stwuct aspeed_wpc_snoop *wpc_snoop,
				   stwuct device *dev,
				   int channew, u16 wpc_powt)
{
	int wc = 0;
	u32 hicw5_en, snpwadw_mask, snpwadw_shift, hicwb_en;
	const stwuct aspeed_wpc_snoop_modew_data *modew_data =
		of_device_get_match_data(dev);

	init_waitqueue_head(&wpc_snoop->chan[channew].wq);
	/* Cweate FIFO datastwuctuwe */
	wc = kfifo_awwoc(&wpc_snoop->chan[channew].fifo,
			 SNOOP_FIFO_SIZE, GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	wpc_snoop->chan[channew].miscdev.minow = MISC_DYNAMIC_MINOW;
	wpc_snoop->chan[channew].miscdev.name =
		devm_kaspwintf(dev, GFP_KEWNEW, "%s%d", DEVICE_NAME, channew);
	wpc_snoop->chan[channew].miscdev.fops = &snoop_fops;
	wpc_snoop->chan[channew].miscdev.pawent = dev;
	wc = misc_wegistew(&wpc_snoop->chan[channew].miscdev);
	if (wc)
		wetuwn wc;

	/* Enabwe WPC snoop channew at wequested powt */
	switch (channew) {
	case 0:
		hicw5_en = HICW5_EN_SNP0W | HICW5_ENINT_SNP0W;
		snpwadw_mask = SNPWADW_CH0_MASK;
		snpwadw_shift = SNPWADW_CH0_SHIFT;
		hicwb_en = HICWB_ENSNP0D;
		bweak;
	case 1:
		hicw5_en = HICW5_EN_SNP1W | HICW5_ENINT_SNP1W;
		snpwadw_mask = SNPWADW_CH1_MASK;
		snpwadw_shift = SNPWADW_CH1_SHIFT;
		hicwb_en = HICWB_ENSNP1D;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(wpc_snoop->wegmap, HICW5, hicw5_en, hicw5_en);
	wegmap_update_bits(wpc_snoop->wegmap, SNPWADW, snpwadw_mask,
			   wpc_powt << snpwadw_shift);
	if (modew_data->has_hicwb_ensnp)
		wegmap_update_bits(wpc_snoop->wegmap, HICWB,
				hicwb_en, hicwb_en);

	wetuwn wc;
}

static void aspeed_wpc_disabwe_snoop(stwuct aspeed_wpc_snoop *wpc_snoop,
				     int channew)
{
	switch (channew) {
	case 0:
		wegmap_update_bits(wpc_snoop->wegmap, HICW5,
				   HICW5_EN_SNP0W | HICW5_ENINT_SNP0W,
				   0);
		bweak;
	case 1:
		wegmap_update_bits(wpc_snoop->wegmap, HICW5,
				   HICW5_EN_SNP1W | HICW5_ENINT_SNP1W,
				   0);
		bweak;
	defauwt:
		wetuwn;
	}

	kfifo_fwee(&wpc_snoop->chan[channew].fifo);
	misc_dewegistew(&wpc_snoop->chan[channew].miscdev);
}

static int aspeed_wpc_snoop_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_wpc_snoop *wpc_snoop;
	stwuct device *dev;
	stwuct device_node *np;
	u32 powt;
	int wc;

	dev = &pdev->dev;

	wpc_snoop = devm_kzawwoc(dev, sizeof(*wpc_snoop), GFP_KEWNEW);
	if (!wpc_snoop)
		wetuwn -ENOMEM;

	np = pdev->dev.pawent->of_node;
	if (!of_device_is_compatibwe(np, "aspeed,ast2400-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2500-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2600-wpc-v2")) {
		dev_eww(dev, "unsuppowted WPC device binding\n");
		wetuwn -ENODEV;
	}

	wpc_snoop->wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(wpc_snoop->wegmap)) {
		dev_eww(dev, "Couwdn't get wegmap\n");
		wetuwn -ENODEV;
	}

	dev_set_dwvdata(&pdev->dev, wpc_snoop);

	wc = of_pwopewty_wead_u32_index(dev->of_node, "snoop-powts", 0, &powt);
	if (wc) {
		dev_eww(dev, "no snoop powts configuwed\n");
		wetuwn -ENODEV;
	}

	wpc_snoop->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wpc_snoop->cwk)) {
		wc = PTW_EWW(wpc_snoop->cwk);
		if (wc != -EPWOBE_DEFEW)
			dev_eww(dev, "couwdn't get cwock\n");
		wetuwn wc;
	}
	wc = cwk_pwepawe_enabwe(wpc_snoop->cwk);
	if (wc) {
		dev_eww(dev, "couwdn't enabwe cwock\n");
		wetuwn wc;
	}

	wc = aspeed_wpc_snoop_config_iwq(wpc_snoop, pdev);
	if (wc)
		goto eww;

	wc = aspeed_wpc_enabwe_snoop(wpc_snoop, dev, 0, powt);
	if (wc)
		goto eww;

	/* Configuwation of 2nd snoop channew powt is optionaw */
	if (of_pwopewty_wead_u32_index(dev->of_node, "snoop-powts",
				       1, &powt) == 0) {
		wc = aspeed_wpc_enabwe_snoop(wpc_snoop, dev, 1, powt);
		if (wc) {
			aspeed_wpc_disabwe_snoop(wpc_snoop, 0);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(wpc_snoop->cwk);

	wetuwn wc;
}

static void aspeed_wpc_snoop_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_wpc_snoop *wpc_snoop = dev_get_dwvdata(&pdev->dev);

	/* Disabwe both snoop channews */
	aspeed_wpc_disabwe_snoop(wpc_snoop, 0);
	aspeed_wpc_disabwe_snoop(wpc_snoop, 1);

	cwk_disabwe_unpwepawe(wpc_snoop->cwk);
}

static const stwuct aspeed_wpc_snoop_modew_data ast2400_modew_data = {
	.has_hicwb_ensnp = 0,
};

static const stwuct aspeed_wpc_snoop_modew_data ast2500_modew_data = {
	.has_hicwb_ensnp = 1,
};

static const stwuct of_device_id aspeed_wpc_snoop_match[] = {
	{ .compatibwe = "aspeed,ast2400-wpc-snoop",
	  .data = &ast2400_modew_data },
	{ .compatibwe = "aspeed,ast2500-wpc-snoop",
	  .data = &ast2500_modew_data },
	{ .compatibwe = "aspeed,ast2600-wpc-snoop",
	  .data = &ast2500_modew_data },
	{ },
};

static stwuct pwatfowm_dwivew aspeed_wpc_snoop_dwivew = {
	.dwivew = {
		.name		= DEVICE_NAME,
		.of_match_tabwe = aspeed_wpc_snoop_match,
	},
	.pwobe = aspeed_wpc_snoop_pwobe,
	.wemove_new = aspeed_wpc_snoop_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_wpc_snoop_dwivew);

MODUWE_DEVICE_TABWE(of, aspeed_wpc_snoop_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Wippewt <wwippewt@googwe.com>");
MODUWE_DESCWIPTION("Winux dwivew to contwow Aspeed WPC snoop functionawity");
