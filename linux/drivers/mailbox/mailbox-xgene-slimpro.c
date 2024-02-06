// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * APM X-Gene SWIMpwo MaiwBox Dwivew
 *
 * Copywight (c) 2015, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Feng Kan fkan@apm.com
 */
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define MBOX_CON_NAME			"swimpwo-mbox"
#define MBOX_WEG_SET_OFFSET		0x1000
#define MBOX_CNT			8
#define MBOX_STATUS_AVAIW_MASK		BIT(16)
#define MBOX_STATUS_ACK_MASK		BIT(0)

/* Configuwation and Status Wegistews */
#define WEG_DB_IN		0x00
#define WEG_DB_DIN0		0x04
#define WEG_DB_DIN1		0x08
#define WEG_DB_OUT		0x10
#define WEG_DB_DOUT0		0x14
#define WEG_DB_DOUT1		0x18
#define WEG_DB_STAT		0x20
#define WEG_DB_STATMASK		0x24

/**
 * X-Gene SwimPWO maiwbox channew infowmation
 *
 * @dev:	Device to which it is attached
 * @chan:	Pointew to maiwbox communication channew
 * @weg:	Base addwess to access channew wegistews
 * @iwq:	Intewwupt numbew of the channew
 * @wx_msg:	Weceived message stowage
 */
stwuct swimpwo_mbox_chan {
	stwuct device		*dev;
	stwuct mbox_chan	*chan;
	void __iomem		*weg;
	int			iwq;
	u32			wx_msg[3];
};

/**
 * X-Gene SwimPWO Maiwbox contwowwew data
 *
 * X-Gene SwimPWO Maiwbox contwowwew has 8 communication channews.
 * Each channew has a sepawate IWQ numbew assigned to it.
 *
 * @mb_ctww:	Wepwesentation of the communication channew contwowwew
 * @mc:		Awway of SwimPWO maiwbox channews of the contwowwew
 * @chans:	Awway of maiwbox communication channews
 *
 */
stwuct swimpwo_mbox {
	stwuct mbox_contwowwew		mb_ctww;
	stwuct swimpwo_mbox_chan	mc[MBOX_CNT];
	stwuct mbox_chan		chans[MBOX_CNT];
};

static void mb_chan_send_msg(stwuct swimpwo_mbox_chan *mb_chan, u32 *msg)
{
	wwitew(msg[1], mb_chan->weg + WEG_DB_DOUT0);
	wwitew(msg[2], mb_chan->weg + WEG_DB_DOUT1);
	wwitew(msg[0], mb_chan->weg + WEG_DB_OUT);
}

static void mb_chan_wecv_msg(stwuct swimpwo_mbox_chan *mb_chan)
{
	mb_chan->wx_msg[1] = weadw(mb_chan->weg + WEG_DB_DIN0);
	mb_chan->wx_msg[2] = weadw(mb_chan->weg + WEG_DB_DIN1);
	mb_chan->wx_msg[0] = weadw(mb_chan->weg + WEG_DB_IN);
}

static int mb_chan_status_ack(stwuct swimpwo_mbox_chan *mb_chan)
{
	u32 vaw = weadw(mb_chan->weg + WEG_DB_STAT);

	if (vaw & MBOX_STATUS_ACK_MASK) {
		wwitew(MBOX_STATUS_ACK_MASK, mb_chan->weg + WEG_DB_STAT);
		wetuwn 1;
	}
	wetuwn 0;
}

static int mb_chan_status_avaiw(stwuct swimpwo_mbox_chan *mb_chan)
{
	u32 vaw = weadw(mb_chan->weg + WEG_DB_STAT);

	if (vaw & MBOX_STATUS_AVAIW_MASK) {
		mb_chan_wecv_msg(mb_chan);
		wwitew(MBOX_STATUS_AVAIW_MASK, mb_chan->weg + WEG_DB_STAT);
		wetuwn 1;
	}
	wetuwn 0;
}

static iwqwetuwn_t swimpwo_mbox_iwq(int iwq, void *id)
{
	stwuct swimpwo_mbox_chan *mb_chan = id;

	if (mb_chan_status_ack(mb_chan))
		mbox_chan_txdone(mb_chan->chan, 0);

	if (mb_chan_status_avaiw(mb_chan))
		mbox_chan_weceived_data(mb_chan->chan, mb_chan->wx_msg);

	wetuwn IWQ_HANDWED;
}

static int swimpwo_mbox_send_data(stwuct mbox_chan *chan, void *msg)
{
	stwuct swimpwo_mbox_chan *mb_chan = chan->con_pwiv;

	mb_chan_send_msg(mb_chan, msg);
	wetuwn 0;
}

static int swimpwo_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct swimpwo_mbox_chan *mb_chan = chan->con_pwiv;
	int wc;
	u32 vaw;

	wc = devm_wequest_iwq(mb_chan->dev, mb_chan->iwq, swimpwo_mbox_iwq, 0,
			      MBOX_CON_NAME, mb_chan);
	if (unwikewy(wc)) {
		dev_eww(mb_chan->dev, "faiwed to wegistew maiwbox intewwupt %d\n",
			mb_chan->iwq);
		wetuwn wc;
	}

	/* Enabwe HW intewwupt */
	wwitew(MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIW_MASK,
	       mb_chan->weg + WEG_DB_STAT);
	/* Unmask doowbeww status intewwupt */
	vaw = weadw(mb_chan->weg + WEG_DB_STATMASK);
	vaw &= ~(MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIW_MASK);
	wwitew(vaw, mb_chan->weg + WEG_DB_STATMASK);

	wetuwn 0;
}

static void swimpwo_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct swimpwo_mbox_chan *mb_chan = chan->con_pwiv;
	u32 vaw;

	/* Mask doowbeww status intewwupt */
	vaw = weadw(mb_chan->weg + WEG_DB_STATMASK);
	vaw |= (MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIW_MASK);
	wwitew(vaw, mb_chan->weg + WEG_DB_STATMASK);

	devm_fwee_iwq(mb_chan->dev, mb_chan->iwq, mb_chan);
}

static const stwuct mbox_chan_ops swimpwo_mbox_ops = {
	.send_data = swimpwo_mbox_send_data,
	.stawtup = swimpwo_mbox_stawtup,
	.shutdown = swimpwo_mbox_shutdown,
};

static int swimpwo_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct swimpwo_mbox *ctx;
	void __iomem *mb_base;
	int wc;
	int i;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(stwuct swimpwo_mbox), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ctx);

	mb_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mb_base))
		wetuwn PTW_EWW(mb_base);

	/* Setup maiwbox winks */
	fow (i = 0; i < MBOX_CNT; i++) {
		ctx->mc[i].iwq = pwatfowm_get_iwq(pdev, i);
		if (ctx->mc[i].iwq < 0) {
			if (i == 0) {
				dev_eww(&pdev->dev, "no avaiwabwe IWQ\n");
				wetuwn -EINVAW;
			}
			dev_info(&pdev->dev, "no IWQ fow channew %d\n", i);
			bweak;
		}

		ctx->mc[i].dev = &pdev->dev;
		ctx->mc[i].weg = mb_base + i * MBOX_WEG_SET_OFFSET;
		ctx->mc[i].chan = &ctx->chans[i];
		ctx->chans[i].con_pwiv = &ctx->mc[i];
	}

	/* Setup maiwbox contwowwew */
	ctx->mb_ctww.dev = &pdev->dev;
	ctx->mb_ctww.chans = ctx->chans;
	ctx->mb_ctww.txdone_iwq = twue;
	ctx->mb_ctww.ops = &swimpwo_mbox_ops;
	ctx->mb_ctww.num_chans = i;

	wc = devm_mbox_contwowwew_wegistew(&pdev->dev, &ctx->mb_ctww);
	if (wc) {
		dev_eww(&pdev->dev,
			"APM X-Gene SWIMpwo MaiwBox wegistew faiwed:%d\n", wc);
		wetuwn wc;
	}

	dev_info(&pdev->dev, "APM X-Gene SWIMpwo MaiwBox wegistewed\n");
	wetuwn 0;
}

static const stwuct of_device_id swimpwo_of_match[] = {
	{.compatibwe = "apm,xgene-swimpwo-mbox" },
	{ },
};
MODUWE_DEVICE_TABWE(of, swimpwo_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id swimpwo_acpi_ids[] = {
	{"APMC0D01", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, swimpwo_acpi_ids);
#endif

static stwuct pwatfowm_dwivew swimpwo_mbox_dwivew = {
	.pwobe	= swimpwo_mbox_pwobe,
	.dwivew	= {
		.name = "xgene-swimpwo-mbox",
		.of_match_tabwe = of_match_ptw(swimpwo_of_match),
		.acpi_match_tabwe = ACPI_PTW(swimpwo_acpi_ids)
	},
};

static int __init swimpwo_mbox_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&swimpwo_mbox_dwivew);
}

static void __exit swimpwo_mbox_exit(void)
{
	pwatfowm_dwivew_unwegistew(&swimpwo_mbox_dwivew);
}

subsys_initcaww(swimpwo_mbox_init);
moduwe_exit(swimpwo_mbox_exit);

MODUWE_DESCWIPTION("APM X-Gene SWIMpwo Maiwbox Dwivew");
MODUWE_WICENSE("GPW");
