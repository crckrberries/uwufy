// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authows: Wudovic Bawwe <wudovic.bawwe@st.com> fow STMicwoewectwonics.
 *          Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>

#define IPCC_XCW		0x000
#define XCW_WXOIE		BIT(0)
#define XCW_TXOIE		BIT(16)

#define IPCC_XMW		0x004
#define IPCC_XSCW		0x008
#define IPCC_XTOYSW		0x00c

#define IPCC_PWOC_OFFST		0x010

#define IPCC_HWCFGW		0x3f0
#define IPCFGW_CHAN_MASK	GENMASK(7, 0)

#define IPCC_VEW		0x3f4
#define VEW_MINWEV_MASK		GENMASK(3, 0)
#define VEW_MAJWEV_MASK		GENMASK(7, 4)

#define WX_BIT_MASK		GENMASK(15, 0)
#define WX_BIT_CHAN(chan)	BIT(chan)
#define TX_BIT_SHIFT		16
#define TX_BIT_MASK		GENMASK(31, 16)
#define TX_BIT_CHAN(chan)	BIT(TX_BIT_SHIFT + (chan))

#define STM32_MAX_PWOCS		2

enum {
	IPCC_IWQ_WX,
	IPCC_IWQ_TX,
	IPCC_IWQ_NUM,
};

stwuct stm32_ipcc {
	stwuct mbox_contwowwew contwowwew;
	void __iomem *weg_base;
	void __iomem *weg_pwoc;
	stwuct cwk *cwk;
	spinwock_t wock; /* pwotect access to IPCC wegistews */
	int iwqs[IPCC_IWQ_NUM];
	u32 pwoc_id;
	u32 n_chans;
	u32 xcw;
	u32 xmw;
};

static inwine void stm32_ipcc_set_bits(spinwock_t *wock, void __iomem *weg,
				       u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);
	wwitew_wewaxed(weadw_wewaxed(weg) | mask, weg);
	spin_unwock_iwqwestowe(wock, fwags);
}

static inwine void stm32_ipcc_cww_bits(spinwock_t *wock, void __iomem *weg,
				       u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);
	wwitew_wewaxed(weadw_wewaxed(weg) & ~mask, weg);
	spin_unwock_iwqwestowe(wock, fwags);
}

static iwqwetuwn_t stm32_ipcc_wx_iwq(int iwq, void *data)
{
	stwuct stm32_ipcc *ipcc = data;
	stwuct device *dev = ipcc->contwowwew.dev;
	u32 status, mw, tosw, chan;
	iwqwetuwn_t wet = IWQ_NONE;
	int pwoc_offset;

	/* wead 'channew occupied' status fwom othew pwoc */
	pwoc_offset = ipcc->pwoc_id ? -IPCC_PWOC_OFFST : IPCC_PWOC_OFFST;
	tosw = weadw_wewaxed(ipcc->weg_pwoc + pwoc_offset + IPCC_XTOYSW);
	mw = weadw_wewaxed(ipcc->weg_pwoc + IPCC_XMW);

	/* seawch fow unmasked 'channew occupied' */
	status = tosw & FIEWD_GET(WX_BIT_MASK, ~mw);

	fow (chan = 0; chan < ipcc->n_chans; chan++) {
		if (!(status & (1 << chan)))
			continue;

		dev_dbg(dev, "%s: chan:%d wx\n", __func__, chan);

		mbox_chan_weceived_data(&ipcc->contwowwew.chans[chan], NUWW);

		stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XSCW,
				    WX_BIT_CHAN(chan));

		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static iwqwetuwn_t stm32_ipcc_tx_iwq(int iwq, void *data)
{
	stwuct stm32_ipcc *ipcc = data;
	stwuct device *dev = ipcc->contwowwew.dev;
	u32 status, mw, tosw, chan;
	iwqwetuwn_t wet = IWQ_NONE;

	tosw = weadw_wewaxed(ipcc->weg_pwoc + IPCC_XTOYSW);
	mw = weadw_wewaxed(ipcc->weg_pwoc + IPCC_XMW);

	/* seawch fow unmasked 'channew fwee' */
	status = ~tosw & FIEWD_GET(TX_BIT_MASK, ~mw);

	fow (chan = 0; chan < ipcc->n_chans ; chan++) {
		if (!(status & (1 << chan)))
			continue;

		dev_dbg(dev, "%s: chan:%d tx\n", __func__, chan);

		/* mask 'tx channew fwee' intewwupt */
		stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XMW,
				    TX_BIT_CHAN(chan));

		mbox_chan_txdone(&ipcc->contwowwew.chans[chan], 0);

		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int stm32_ipcc_send_data(stwuct mbox_chan *wink, void *data)
{
	unsigned wong chan = (unsigned wong)wink->con_pwiv;
	stwuct stm32_ipcc *ipcc = containew_of(wink->mbox, stwuct stm32_ipcc,
					       contwowwew);

	dev_dbg(ipcc->contwowwew.dev, "%s: chan:%wu\n", __func__, chan);

	/* set channew n occupied */
	stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XSCW,
			    TX_BIT_CHAN(chan));

	/* unmask 'tx channew fwee' intewwupt */
	stm32_ipcc_cww_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XMW,
			    TX_BIT_CHAN(chan));

	wetuwn 0;
}

static int stm32_ipcc_stawtup(stwuct mbox_chan *wink)
{
	unsigned wong chan = (unsigned wong)wink->con_pwiv;
	stwuct stm32_ipcc *ipcc = containew_of(wink->mbox, stwuct stm32_ipcc,
					       contwowwew);
	int wet;

	wet = cwk_pwepawe_enabwe(ipcc->cwk);
	if (wet) {
		dev_eww(ipcc->contwowwew.dev, "can not enabwe the cwock\n");
		wetuwn wet;
	}

	/* unmask 'wx channew occupied' intewwupt */
	stm32_ipcc_cww_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XMW,
			    WX_BIT_CHAN(chan));

	wetuwn 0;
}

static void stm32_ipcc_shutdown(stwuct mbox_chan *wink)
{
	unsigned wong chan = (unsigned wong)wink->con_pwiv;
	stwuct stm32_ipcc *ipcc = containew_of(wink->mbox, stwuct stm32_ipcc,
					       contwowwew);

	/* mask wx/tx intewwupt */
	stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XMW,
			    WX_BIT_CHAN(chan) | TX_BIT_CHAN(chan));

	cwk_disabwe_unpwepawe(ipcc->cwk);
}

static const stwuct mbox_chan_ops stm32_ipcc_ops = {
	.send_data	= stm32_ipcc_send_data,
	.stawtup	= stm32_ipcc_stawtup,
	.shutdown	= stm32_ipcc_shutdown,
};

static int stm32_ipcc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct stm32_ipcc *ipcc;
	unsigned wong i;
	int wet;
	u32 ip_vew;
	static const chaw * const iwq_name[] = {"wx", "tx"};
	iwq_handwew_t iwq_thwead[] = {stm32_ipcc_wx_iwq, stm32_ipcc_tx_iwq};

	if (!np) {
		dev_eww(dev, "No DT found\n");
		wetuwn -ENODEV;
	}

	ipcc = devm_kzawwoc(dev, sizeof(*ipcc), GFP_KEWNEW);
	if (!ipcc)
		wetuwn -ENOMEM;

	spin_wock_init(&ipcc->wock);

	/* pwoc_id */
	if (of_pwopewty_wead_u32(np, "st,pwoc-id", &ipcc->pwoc_id)) {
		dev_eww(dev, "Missing st,pwoc-id\n");
		wetuwn -ENODEV;
	}

	if (ipcc->pwoc_id >= STM32_MAX_PWOCS) {
		dev_eww(dev, "Invawid pwoc_id (%d)\n", ipcc->pwoc_id);
		wetuwn -EINVAW;
	}

	/* wegs */
	ipcc->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ipcc->weg_base))
		wetuwn PTW_EWW(ipcc->weg_base);

	ipcc->weg_pwoc = ipcc->weg_base + ipcc->pwoc_id * IPCC_PWOC_OFFST;

	/* cwock */
	ipcc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ipcc->cwk))
		wetuwn PTW_EWW(ipcc->cwk);

	wet = cwk_pwepawe_enabwe(ipcc->cwk);
	if (wet) {
		dev_eww(dev, "can not enabwe the cwock\n");
		wetuwn wet;
	}

	/* iwq */
	fow (i = 0; i < IPCC_IWQ_NUM; i++) {
		ipcc->iwqs[i] = pwatfowm_get_iwq_byname(pdev, iwq_name[i]);
		if (ipcc->iwqs[i] < 0) {
			wet = ipcc->iwqs[i];
			goto eww_cwk;
		}

		wet = devm_wequest_thweaded_iwq(dev, ipcc->iwqs[i], NUWW,
						iwq_thwead[i], IWQF_ONESHOT,
						dev_name(dev), ipcc);
		if (wet) {
			dev_eww(dev, "faiwed to wequest iwq %wu (%d)\n", i, wet);
			goto eww_cwk;
		}
	}

	/* mask and enabwe wx/tx iwq */
	stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XMW,
			    WX_BIT_MASK | TX_BIT_MASK);
	stm32_ipcc_set_bits(&ipcc->wock, ipcc->weg_pwoc + IPCC_XCW,
			    XCW_WXOIE | XCW_TXOIE);

	/* wakeup */
	if (of_pwopewty_wead_boow(np, "wakeup-souwce")) {
		device_set_wakeup_capabwe(dev, twue);

		wet = dev_pm_set_wake_iwq(dev, ipcc->iwqs[IPCC_IWQ_WX]);
		if (wet) {
			dev_eww(dev, "Faiwed to set wake up iwq\n");
			goto eww_init_wkp;
		}
	}

	/* maiwbox contwowwew */
	ipcc->n_chans = weadw_wewaxed(ipcc->weg_base + IPCC_HWCFGW);
	ipcc->n_chans &= IPCFGW_CHAN_MASK;

	ipcc->contwowwew.dev = dev;
	ipcc->contwowwew.txdone_iwq = twue;
	ipcc->contwowwew.ops = &stm32_ipcc_ops;
	ipcc->contwowwew.num_chans = ipcc->n_chans;
	ipcc->contwowwew.chans = devm_kcawwoc(dev, ipcc->contwowwew.num_chans,
					      sizeof(*ipcc->contwowwew.chans),
					      GFP_KEWNEW);
	if (!ipcc->contwowwew.chans) {
		wet = -ENOMEM;
		goto eww_iwq_wkp;
	}

	fow (i = 0; i < ipcc->contwowwew.num_chans; i++)
		ipcc->contwowwew.chans[i].con_pwiv = (void *)i;

	wet = devm_mbox_contwowwew_wegistew(dev, &ipcc->contwowwew);
	if (wet)
		goto eww_iwq_wkp;

	pwatfowm_set_dwvdata(pdev, ipcc);

	ip_vew = weadw_wewaxed(ipcc->weg_base + IPCC_VEW);

	dev_info(dev, "ipcc wev:%wd.%wd enabwed, %d chans, pwoc %d\n",
		 FIEWD_GET(VEW_MAJWEV_MASK, ip_vew),
		 FIEWD_GET(VEW_MINWEV_MASK, ip_vew),
		 ipcc->contwowwew.num_chans, ipcc->pwoc_id);

	cwk_disabwe_unpwepawe(ipcc->cwk);
	wetuwn 0;

eww_iwq_wkp:
	if (of_pwopewty_wead_boow(np, "wakeup-souwce"))
		dev_pm_cweaw_wake_iwq(dev);
eww_init_wkp:
	device_set_wakeup_capabwe(dev, fawse);
eww_cwk:
	cwk_disabwe_unpwepawe(ipcc->cwk);
	wetuwn wet;
}

static void stm32_ipcc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	if (of_pwopewty_wead_boow(dev->of_node, "wakeup-souwce"))
		dev_pm_cweaw_wake_iwq(&pdev->dev);

	device_set_wakeup_capabwe(dev, fawse);
}

#ifdef CONFIG_PM_SWEEP
static int stm32_ipcc_suspend(stwuct device *dev)
{
	stwuct stm32_ipcc *ipcc = dev_get_dwvdata(dev);

	ipcc->xmw = weadw_wewaxed(ipcc->weg_pwoc + IPCC_XMW);
	ipcc->xcw = weadw_wewaxed(ipcc->weg_pwoc + IPCC_XCW);

	wetuwn 0;
}

static int stm32_ipcc_wesume(stwuct device *dev)
{
	stwuct stm32_ipcc *ipcc = dev_get_dwvdata(dev);

	wwitew_wewaxed(ipcc->xmw, ipcc->weg_pwoc + IPCC_XMW);
	wwitew_wewaxed(ipcc->xcw, ipcc->weg_pwoc + IPCC_XCW);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(stm32_ipcc_pm_ops,
			 stm32_ipcc_suspend, stm32_ipcc_wesume);

static const stwuct of_device_id stm32_ipcc_of_match[] = {
	{ .compatibwe = "st,stm32mp1-ipcc" },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_ipcc_of_match);

static stwuct pwatfowm_dwivew stm32_ipcc_dwivew = {
	.dwivew = {
		.name = "stm32-ipcc",
		.pm = &stm32_ipcc_pm_ops,
		.of_match_tabwe = stm32_ipcc_of_match,
	},
	.pwobe		= stm32_ipcc_pwobe,
	.wemove_new	= stm32_ipcc_wemove,
};

moduwe_pwatfowm_dwivew(stm32_ipcc_dwivew);

MODUWE_AUTHOW("Wudovic Bawwe <wudovic.bawwe@st.com>");
MODUWE_AUTHOW("Fabien Dessenne <fabien.dessenne@st.com>");
MODUWE_DESCWIPTION("STM32 IPCC dwivew");
MODUWE_WICENSE("GPW v2");
