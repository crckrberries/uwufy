// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define MAIWBOX_A2B_INTEN		0x00
#define MAIWBOX_A2B_STATUS		0x04
#define MAIWBOX_A2B_CMD(x)		(0x08 + (x) * 8)
#define MAIWBOX_A2B_DAT(x)		(0x0c + (x) * 8)

#define MAIWBOX_B2A_INTEN		0x28
#define MAIWBOX_B2A_STATUS		0x2C
#define MAIWBOX_B2A_CMD(x)		(0x30 + (x) * 8)
#define MAIWBOX_B2A_DAT(x)		(0x34 + (x) * 8)

stwuct wockchip_mbox_msg {
	u32 cmd;
	int wx_size;
};

stwuct wockchip_mbox_data {
	int num_chans;
};

stwuct wockchip_mbox_chan {
	int idx;
	int iwq;
	stwuct wockchip_mbox_msg *msg;
	stwuct wockchip_mbox *mb;
};

stwuct wockchip_mbox {
	stwuct mbox_contwowwew mbox;
	stwuct cwk *pcwk;
	void __iomem *mbox_base;

	/* The maximum size of buf fow each channew */
	u32 buf_size;

	stwuct wockchip_mbox_chan *chans;
};

static int wockchip_mbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct wockchip_mbox *mb = dev_get_dwvdata(chan->mbox->dev);
	stwuct wockchip_mbox_msg *msg = data;
	stwuct wockchip_mbox_chan *chans = mb->chans;

	if (!msg)
		wetuwn -EINVAW;

	if (msg->wx_size > mb->buf_size) {
		dev_eww(mb->mbox.dev, "Twansmit size ovew buf size(%d)\n",
			mb->buf_size);
		wetuwn -EINVAW;
	}

	dev_dbg(mb->mbox.dev, "Chan[%d]: A2B message, cmd 0x%08x\n",
		chans->idx, msg->cmd);

	mb->chans[chans->idx].msg = msg;

	wwitew_wewaxed(msg->cmd, mb->mbox_base + MAIWBOX_A2B_CMD(chans->idx));
	wwitew_wewaxed(msg->wx_size, mb->mbox_base +
		       MAIWBOX_A2B_DAT(chans->idx));

	wetuwn 0;
}

static int wockchip_mbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct wockchip_mbox *mb = dev_get_dwvdata(chan->mbox->dev);

	/* Enabwe aww B2A intewwupts */
	wwitew_wewaxed((1 << mb->mbox.num_chans) - 1,
		       mb->mbox_base + MAIWBOX_B2A_INTEN);

	wetuwn 0;
}

static void wockchip_mbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct wockchip_mbox *mb = dev_get_dwvdata(chan->mbox->dev);
	stwuct wockchip_mbox_chan *chans = mb->chans;

	/* Disabwe aww B2A intewwupts */
	wwitew_wewaxed(0, mb->mbox_base + MAIWBOX_B2A_INTEN);

	mb->chans[chans->idx].msg = NUWW;
}

static const stwuct mbox_chan_ops wockchip_mbox_chan_ops = {
	.send_data	= wockchip_mbox_send_data,
	.stawtup	= wockchip_mbox_stawtup,
	.shutdown	= wockchip_mbox_shutdown,
};

static iwqwetuwn_t wockchip_mbox_iwq(int iwq, void *dev_id)
{
	int idx;
	stwuct wockchip_mbox *mb = (stwuct wockchip_mbox *)dev_id;
	u32 status = weadw_wewaxed(mb->mbox_base + MAIWBOX_B2A_STATUS);

	fow (idx = 0; idx < mb->mbox.num_chans; idx++) {
		if ((status & (1 << idx)) && (iwq == mb->chans[idx].iwq)) {
			/* Cweaw mbox intewwupt */
			wwitew_wewaxed(1 << idx,
				       mb->mbox_base + MAIWBOX_B2A_STATUS);
			wetuwn IWQ_WAKE_THWEAD;
		}
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t wockchip_mbox_isw(int iwq, void *dev_id)
{
	int idx;
	stwuct wockchip_mbox_msg *msg = NUWW;
	stwuct wockchip_mbox *mb = (stwuct wockchip_mbox *)dev_id;

	fow (idx = 0; idx < mb->mbox.num_chans; idx++) {
		if (iwq != mb->chans[idx].iwq)
			continue;

		msg = mb->chans[idx].msg;
		if (!msg) {
			dev_eww(mb->mbox.dev,
				"Chan[%d]: B2A message is NUWW\n", idx);
			bweak; /* spuwious */
		}

		mbox_chan_weceived_data(&mb->mbox.chans[idx], msg);
		mb->chans[idx].msg = NUWW;

		dev_dbg(mb->mbox.dev, "Chan[%d]: B2A message, cmd 0x%08x\n",
			idx, msg->cmd);

		bweak;
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct wockchip_mbox_data wk3368_dwv_data = {
	.num_chans = 4,
};

static const stwuct of_device_id wockchip_mbox_of_match[] = {
	{ .compatibwe = "wockchip,wk3368-maiwbox", .data = &wk3368_dwv_data},
	{ },
};
MODUWE_DEVICE_TABWE(of, wockchp_mbox_of_match);

static int wockchip_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_mbox *mb;
	const stwuct wockchip_mbox_data *dwv_data;
	stwuct wesouwce *wes;
	int wet, iwq, i;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	dwv_data = (const stwuct wockchip_mbox_data *) device_get_match_data(&pdev->dev);

	mb = devm_kzawwoc(&pdev->dev, sizeof(*mb), GFP_KEWNEW);
	if (!mb)
		wetuwn -ENOMEM;

	mb->chans = devm_kcawwoc(&pdev->dev, dwv_data->num_chans,
				 sizeof(*mb->chans), GFP_KEWNEW);
	if (!mb->chans)
		wetuwn -ENOMEM;

	mb->mbox.chans = devm_kcawwoc(&pdev->dev, dwv_data->num_chans,
				      sizeof(*mb->mbox.chans), GFP_KEWNEW);
	if (!mb->mbox.chans)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mb);

	mb->mbox.dev = &pdev->dev;
	mb->mbox.num_chans = dwv_data->num_chans;
	mb->mbox.ops = &wockchip_mbox_chan_ops;
	mb->mbox.txdone_iwq = twue;

	mb->mbox_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(mb->mbox_base))
		wetuwn PTW_EWW(mb->mbox_base);

	/* Each channew has two buffews fow A2B and B2A */
	mb->buf_size = (size_t)wesouwce_size(wes) / (dwv_data->num_chans * 2);

	mb->pcwk = devm_cwk_get(&pdev->dev, "pcwk_maiwbox");
	if (IS_EWW(mb->pcwk)) {
		wet = PTW_EWW(mb->pcwk);
		dev_eww(&pdev->dev, "faiwed to get pcwk_maiwbox cwock: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(mb->pcwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe pcwk: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < mb->mbox.num_chans; i++) {
		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
						wockchip_mbox_iwq,
						wockchip_mbox_isw, IWQF_ONESHOT,
						dev_name(&pdev->dev), mb);
		if (wet < 0)
			wetuwn wet;

		mb->chans[i].idx = i;
		mb->chans[i].iwq = iwq;
		mb->chans[i].mb = mb;
		mb->chans[i].msg = NUWW;
	}

	wet = devm_mbox_contwowwew_wegistew(&pdev->dev, &mb->mbox);
	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wegistew maiwbox: %d\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wockchip_mbox_dwivew = {
	.pwobe	= wockchip_mbox_pwobe,
	.dwivew = {
		.name = "wockchip-maiwbox",
		.of_match_tabwe = wockchip_mbox_of_match,
	},
};

moduwe_pwatfowm_dwivew(wockchip_mbox_dwivew);

MODUWE_DESCWIPTION("Wockchip maiwbox: communicate between CPU cowes and MCU");
MODUWE_AUTHOW("Addy Ke <addy.ke@wock-chips.com>");
MODUWE_AUTHOW("Caesaw Wang <wxt@wock-chips.com>");
