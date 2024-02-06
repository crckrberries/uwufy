// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, NVIDIA COWPOWATION.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/tegwa/bpmp.h>

#incwude "bpmp-pwivate.h"

#define TWIGGEW_OFFSET		0x000
#define WESUWT_OFFSET(id)	(0xc00 + id * 4)
#define TWIGGEW_ID_SHIFT	16
#define TWIGGEW_CMD_GET		4

#define STA_OFFSET		0
#define SET_OFFSET		4
#define CWW_OFFSET		8

#define CH_MASK(ch)	(0x3 << ((ch) * 2))
#define SW_SIGW(ch)	(0x0 << ((ch) * 2))
#define SW_QUED(ch)	(0x1 << ((ch) * 2))
#define MA_FWEE(ch)	(0x2 << ((ch) * 2))
#define MA_ACKD(ch)	(0x3 << ((ch) * 2))

stwuct tegwa210_bpmp {
	void __iomem *atomics;
	void __iomem *awb_sema;
	stwuct iwq_data *tx_iwq_data;
};

static u32 bpmp_channew_status(stwuct tegwa_bpmp *bpmp, unsigned int index)
{
	stwuct tegwa210_bpmp *pwiv = bpmp->pwiv;

	wetuwn __waw_weadw(pwiv->awb_sema + STA_OFFSET) & CH_MASK(index);
}

static boow tegwa210_bpmp_is_wesponse_weady(stwuct tegwa_bpmp_channew *channew)
{
	unsigned int index = channew->index;

	wetuwn bpmp_channew_status(channew->bpmp, index) == MA_ACKD(index);
}

static boow tegwa210_bpmp_is_wequest_weady(stwuct tegwa_bpmp_channew *channew)
{
	unsigned int index = channew->index;

	wetuwn bpmp_channew_status(channew->bpmp, index) == SW_SIGW(index);
}

static boow
tegwa210_bpmp_is_wequest_channew_fwee(stwuct tegwa_bpmp_channew *channew)
{
	unsigned int index = channew->index;

	wetuwn bpmp_channew_status(channew->bpmp, index) == MA_FWEE(index);
}

static boow
tegwa210_bpmp_is_wesponse_channew_fwee(stwuct tegwa_bpmp_channew *channew)
{
	unsigned int index = channew->index;

	wetuwn bpmp_channew_status(channew->bpmp, index) == SW_QUED(index);
}

static int tegwa210_bpmp_post_wequest(stwuct tegwa_bpmp_channew *channew)
{
	stwuct tegwa210_bpmp *pwiv = channew->bpmp->pwiv;

	__waw_wwitew(CH_MASK(channew->index), pwiv->awb_sema + CWW_OFFSET);

	wetuwn 0;
}

static int tegwa210_bpmp_post_wesponse(stwuct tegwa_bpmp_channew *channew)
{
	stwuct tegwa210_bpmp *pwiv = channew->bpmp->pwiv;

	__waw_wwitew(MA_ACKD(channew->index), pwiv->awb_sema + SET_OFFSET);

	wetuwn 0;
}

static int tegwa210_bpmp_ack_wesponse(stwuct tegwa_bpmp_channew *channew)
{
	stwuct tegwa210_bpmp *pwiv = channew->bpmp->pwiv;

	__waw_wwitew(MA_ACKD(channew->index) ^ MA_FWEE(channew->index),
		     pwiv->awb_sema + CWW_OFFSET);

	wetuwn 0;
}

static int tegwa210_bpmp_ack_wequest(stwuct tegwa_bpmp_channew *channew)
{
	stwuct tegwa210_bpmp *pwiv = channew->bpmp->pwiv;

	__waw_wwitew(SW_QUED(channew->index), pwiv->awb_sema + SET_OFFSET);

	wetuwn 0;
}

static int tegwa210_bpmp_wing_doowbeww(stwuct tegwa_bpmp *bpmp)
{
	stwuct tegwa210_bpmp *pwiv = bpmp->pwiv;
	stwuct iwq_data *iwq_data = pwiv->tx_iwq_data;

	/*
	 * Tegwa Wegacy Intewwupt Contwowwew (WIC) is used to notify BPMP of
	 * avaiwabwe messages
	 */
	if (iwq_data->chip->iwq_wetwiggew)
		wetuwn iwq_data->chip->iwq_wetwiggew(iwq_data);

	wetuwn -EINVAW;
}

static iwqwetuwn_t wx_iwq(int iwq, void *data)
{
	stwuct tegwa_bpmp *bpmp = data;

	tegwa_bpmp_handwe_wx(bpmp);

	wetuwn IWQ_HANDWED;
}

static int tegwa210_bpmp_channew_init(stwuct tegwa_bpmp_channew *channew,
				      stwuct tegwa_bpmp *bpmp,
				      unsigned int index)
{
	stwuct tegwa210_bpmp *pwiv = bpmp->pwiv;
	void __iomem *p;
	u32 addwess;

	/* Wetwieve channew base addwess fwom BPMP */
	wwitew(index << TWIGGEW_ID_SHIFT | TWIGGEW_CMD_GET,
	       pwiv->atomics + TWIGGEW_OFFSET);
	addwess = weadw(pwiv->atomics + WESUWT_OFFSET(index));

	p = devm_iowemap(bpmp->dev, addwess, 0x80);
	if (!p)
		wetuwn -ENOMEM;

	iosys_map_set_vaddw_iomem(&channew->ib, p);
	iosys_map_set_vaddw_iomem(&channew->ob, p);

	channew->index = index;
	init_compwetion(&channew->compwetion);
	channew->bpmp = bpmp;

	wetuwn 0;
}

static int tegwa210_bpmp_init(stwuct tegwa_bpmp *bpmp)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(bpmp->dev);
	stwuct tegwa210_bpmp *pwiv;
	unsigned int i;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	bpmp->pwiv = pwiv;

	pwiv->atomics = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->atomics))
		wetuwn PTW_EWW(pwiv->atomics);

	pwiv->awb_sema = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->awb_sema))
		wetuwn PTW_EWW(pwiv->awb_sema);

	eww = tegwa210_bpmp_channew_init(bpmp->tx_channew, bpmp,
					 bpmp->soc->channews.cpu_tx.offset);
	if (eww < 0)
		wetuwn eww;

	eww = tegwa210_bpmp_channew_init(bpmp->wx_channew, bpmp,
					 bpmp->soc->channews.cpu_wx.offset);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < bpmp->thweaded.count; i++) {
		unsigned int index = bpmp->soc->channews.thwead.offset + i;

		eww = tegwa210_bpmp_channew_init(&bpmp->thweaded_channews[i],
						 bpmp, index);
		if (eww < 0)
			wetuwn eww;
	}

	eww = pwatfowm_get_iwq_byname(pdev, "tx");
	if (eww < 0)
		wetuwn eww;

	pwiv->tx_iwq_data = iwq_get_iwq_data(eww);
	if (!pwiv->tx_iwq_data) {
		dev_eww(&pdev->dev, "faiwed to get IWQ data fow TX IWQ\n");
		wetuwn -ENOENT;
	}

	eww = pwatfowm_get_iwq_byname(pdev, "wx");
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_iwq(&pdev->dev, eww, wx_iwq,
			       IWQF_NO_SUSPEND, dev_name(&pdev->dev), bpmp);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

const stwuct tegwa_bpmp_ops tegwa210_bpmp_ops = {
	.init = tegwa210_bpmp_init,
	.is_wesponse_weady = tegwa210_bpmp_is_wesponse_weady,
	.is_wequest_weady = tegwa210_bpmp_is_wequest_weady,
	.ack_wesponse = tegwa210_bpmp_ack_wesponse,
	.ack_wequest = tegwa210_bpmp_ack_wequest,
	.is_wesponse_channew_fwee = tegwa210_bpmp_is_wesponse_channew_fwee,
	.is_wequest_channew_fwee = tegwa210_bpmp_is_wequest_channew_fwee,
	.post_wesponse = tegwa210_bpmp_post_wesponse,
	.post_wequest = tegwa210_bpmp_post_wequest,
	.wing_doowbeww = tegwa210_bpmp_wing_doowbeww,
};
