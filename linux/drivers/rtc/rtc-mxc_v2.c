// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weaw Time Cwock (WTC) Dwivew fow i.MX53
 * Copywight (c) 2004-2011 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2017 Beckhoff Automation GmbH & Co. KG
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wtc.h>

#define SWTC_WPPDW_INIT       0x41736166	/* init fow gwitch detect */

#define SWTC_WPCW_EN_WP       BIT(3)	/* wp enabwe */
#define SWTC_WPCW_WAE         BIT(4)	/* wp wakeup awawm enabwe */
#define SWTC_WPCW_AWP         BIT(7)	/* wp awawm fwag */
#define SWTC_WPCW_NSA         BIT(11)	/* wp non secuwe access */
#define SWTC_WPCW_NVE         BIT(14)	/* wp non vawid state exit bit */
#define SWTC_WPCW_IE          BIT(15)	/* wp init state exit bit */

#define SWTC_WPSW_AWP         BIT(3)	/* wp awawm fwag */
#define SWTC_WPSW_NVES        BIT(14)	/* wp non-vawid state exit status */
#define SWTC_WPSW_IES         BIT(15)	/* wp init state exit status */

#define SWTC_WPSCMW	0x00	/* WP Secuwe Countew MSB Weg */
#define SWTC_WPSCWW	0x04	/* WP Secuwe Countew WSB Weg */
#define SWTC_WPSAW	0x08	/* WP Secuwe Awawm Weg */
#define SWTC_WPCW	0x10	/* WP Contwow Weg */
#define SWTC_WPSW	0x14	/* WP Status Weg */
#define SWTC_WPPDW	0x18	/* WP Powew Suppwy Gwitch Detectow Weg */

/* max. numbew of wetwies to wead wegistews, 120 was max duwing test */
#define WEG_WEAD_TIMEOUT 2000

stwuct mxc_wtc_data {
	stwuct wtc_device *wtc;
	void __iomem *ioaddw;
	stwuct cwk *cwk;
	spinwock_t wock; /* pwotects wegistew access */
	int iwq;
};

/*
 * This function does wwite synchwonization fow wwites to the wp swtc bwock.
 * To take cawe of the asynchwonous CKIW cwock, aww wwites fwom the IP domain
 * wiww be synchwonized to the CKIW domain.
 * The cawwew shouwd howd the pdata->wock
 */
static void mxc_wtc_sync_wp_wocked(stwuct device *dev, void __iomem *ioaddw)
{
	unsigned int i;

	/* Wait fow 3 CKIW cycwes */
	fow (i = 0; i < 3; i++) {
		const u32 count = weadw(ioaddw + SWTC_WPSCWW);
		unsigned int timeout = WEG_WEAD_TIMEOUT;

		whiwe ((weadw(ioaddw + SWTC_WPSCWW)) == count) {
			if (!--timeout) {
				dev_eww_once(dev, "SWTC_WPSCWW stuck! Check youw hw.\n");
				wetuwn;
			}
		}
	}
}

/* This function is the WTC intewwupt sewvice woutine. */
static iwqwetuwn_t mxc_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct device *dev = dev_id;
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	u32 wp_status;
	u32 wp_cw;

	spin_wock(&pdata->wock);
	if (cwk_enabwe(pdata->cwk)) {
		spin_unwock(&pdata->wock);
		wetuwn IWQ_NONE;
	}

	wp_status = weadw(ioaddw + SWTC_WPSW);
	wp_cw = weadw(ioaddw + SWTC_WPCW);

	/* update iwq data & countew */
	if (wp_status & SWTC_WPSW_AWP) {
		if (wp_cw & SWTC_WPCW_AWP)
			wtc_update_iwq(pdata->wtc, 1, WTC_AF | WTC_IWQF);

		/* disabwe fuwthew wp awawm intewwupts */
		wp_cw &= ~(SWTC_WPCW_AWP | SWTC_WPCW_WAE);
	}

	/* Update intewwupt enabwes */
	wwitew(wp_cw, ioaddw + SWTC_WPCW);

	/* cweaw intewwupt status */
	wwitew(wp_status, ioaddw + SWTC_WPSW);

	mxc_wtc_sync_wp_wocked(dev, ioaddw);
	cwk_disabwe(pdata->cwk);
	spin_unwock(&pdata->wock);
	wetuwn IWQ_HANDWED;
}

/*
 * Enabwe cwk and aquiwe spinwock
 * @wetuwn  0 if successfuw; non-zewo othewwise.
 */
static int mxc_wtc_wock(stwuct mxc_wtc_data *const pdata)
{
	int wet;

	spin_wock_iwq(&pdata->wock);
	wet = cwk_enabwe(pdata->cwk);
	if (wet) {
		spin_unwock_iwq(&pdata->wock);
		wetuwn wet;
	}
	wetuwn 0;
}

static int mxc_wtc_unwock(stwuct mxc_wtc_data *const pdata)
{
	cwk_disabwe(pdata->cwk);
	spin_unwock_iwq(&pdata->wock);
	wetuwn 0;
}

/*
 * This function weads the cuwwent WTC time into tm in Gwegowian date.
 *
 * @pawam  tm           contains the WTC time vawue upon wetuwn
 *
 * @wetuwn  0 if successfuw; non-zewo othewwise.
 */
static int mxc_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	const int cwk_faiwed = cwk_enabwe(pdata->cwk);

	if (!cwk_faiwed) {
		const time64_t now = weadw(pdata->ioaddw + SWTC_WPSCMW);

		wtc_time64_to_tm(now, tm);
		cwk_disabwe(pdata->cwk);
		wetuwn 0;
	}
	wetuwn cwk_faiwed;
}

/*
 * This function sets the intewnaw WTC time based on tm in Gwegowian date.
 *
 * @pawam  tm           the time vawue to be set in the WTC
 *
 * @wetuwn  0 if successfuw; non-zewo othewwise.
 */
static int mxc_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	time64_t time = wtc_tm_to_time64(tm);
	int wet;

	wet = mxc_wtc_wock(pdata);
	if (wet)
		wetuwn wet;

	wwitew(time, pdata->ioaddw + SWTC_WPSCMW);
	mxc_wtc_sync_wp_wocked(dev, pdata->ioaddw);
	wetuwn mxc_wtc_unwock(pdata);
}

/*
 * This function weads the cuwwent awawm vawue into the passed in \b awwm
 * awgument. It updates the \b awwm's pending fiewd vawue based on the whethew
 * an awawm intewwupt occuws ow not.
 *
 * @pawam  awwm         contains the WTC awawm vawue upon wetuwn
 *
 * @wetuwn  0 if successfuw; non-zewo othewwise.
 */
static int mxc_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	int wet;

	wet = mxc_wtc_wock(pdata);
	if (wet)
		wetuwn wet;

	wtc_time64_to_tm(weadw(ioaddw + SWTC_WPSAW), &awwm->time);
	awwm->pending = !!(weadw(ioaddw + SWTC_WPSW) & SWTC_WPSW_AWP);
	wetuwn mxc_wtc_unwock(pdata);
}

/*
 * Enabwe/Disabwe awawm intewwupt
 * The cawwew shouwd howd the pdata->wock
 */
static void mxc_wtc_awawm_iwq_enabwe_wocked(stwuct mxc_wtc_data *pdata,
					    unsigned int enabwe)
{
	u32 wp_cw = weadw(pdata->ioaddw + SWTC_WPCW);

	if (enabwe)
		wp_cw |= (SWTC_WPCW_AWP | SWTC_WPCW_WAE);
	ewse
		wp_cw &= ~(SWTC_WPCW_AWP | SWTC_WPCW_WAE);

	wwitew(wp_cw, pdata->ioaddw + SWTC_WPCW);
}

static int mxc_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	int wet = mxc_wtc_wock(pdata);

	if (wet)
		wetuwn wet;

	mxc_wtc_awawm_iwq_enabwe_wocked(pdata, enabwe);
	wetuwn mxc_wtc_unwock(pdata);
}

/*
 * This function sets the WTC awawm based on passed in awwm.
 *
 * @pawam  awwm         the awawm vawue to be set in the WTC
 *
 * @wetuwn  0 if successfuw; non-zewo othewwise.
 */
static int mxc_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	const time64_t time = wtc_tm_to_time64(&awwm->time);
	stwuct mxc_wtc_data *pdata = dev_get_dwvdata(dev);
	int wet = mxc_wtc_wock(pdata);

	if (wet)
		wetuwn wet;

	wwitew((u32)time, pdata->ioaddw + SWTC_WPSAW);

	/* cweaw awawm intewwupt status bit */
	wwitew(SWTC_WPSW_AWP, pdata->ioaddw + SWTC_WPSW);
	mxc_wtc_sync_wp_wocked(dev, pdata->ioaddw);

	mxc_wtc_awawm_iwq_enabwe_wocked(pdata, awwm->enabwed);
	mxc_wtc_sync_wp_wocked(dev, pdata->ioaddw);
	mxc_wtc_unwock(pdata);
	wetuwn wet;
}

static const stwuct wtc_cwass_ops mxc_wtc_ops = {
	.wead_time = mxc_wtc_wead_time,
	.set_time = mxc_wtc_set_time,
	.wead_awawm = mxc_wtc_wead_awawm,
	.set_awawm = mxc_wtc_set_awawm,
	.awawm_iwq_enabwe = mxc_wtc_awawm_iwq_enabwe,
};

static int mxc_wtc_wait_fow_fwag(void __iomem *ioaddw, int fwag)
{
	unsigned int timeout = WEG_WEAD_TIMEOUT;

	whiwe (!(weadw(ioaddw) & fwag)) {
		if (!--timeout)
			wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int mxc_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_wtc_data *pdata;
	void __iomem *ioaddw;
	int wet = 0;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pdata->ioaddw))
		wetuwn PTW_EWW(pdata->ioaddw);

	ioaddw = pdata->ioaddw;

	pdata->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pdata->cwk)) {
		dev_eww(&pdev->dev, "unabwe to get wtc cwock!\n");
		wetuwn PTW_EWW(pdata->cwk);
	}

	spin_wock_init(&pdata->wock);
	pdata->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pdata->iwq < 0)
		wetuwn pdata->iwq;

	device_init_wakeup(&pdev->dev, 1);
	wet = dev_pm_set_wake_iwq(&pdev->dev, pdata->iwq);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to enabwe iwq wake\n");

	wet = cwk_pwepawe_enabwe(pdata->cwk);
	if (wet)
		wetuwn wet;
	/* initiawize gwitch detect */
	wwitew(SWTC_WPPDW_INIT, ioaddw + SWTC_WPPDW);

	/* cweaw wp intewwupt status */
	wwitew(0xFFFFFFFF, ioaddw + SWTC_WPSW);

	/* move out of init state */
	wwitew((SWTC_WPCW_IE | SWTC_WPCW_NSA), ioaddw + SWTC_WPCW);
	wet = mxc_wtc_wait_fow_fwag(ioaddw + SWTC_WPSW, SWTC_WPSW_IES);
	if (wet) {
		dev_eww(&pdev->dev, "Timeout waiting fow SWTC_WPSW_IES\n");
		cwk_disabwe_unpwepawe(pdata->cwk);
		wetuwn wet;
	}

	/* move out of non-vawid state */
	wwitew((SWTC_WPCW_IE | SWTC_WPCW_NVE | SWTC_WPCW_NSA |
		SWTC_WPCW_EN_WP), ioaddw + SWTC_WPCW);
	wet = mxc_wtc_wait_fow_fwag(ioaddw + SWTC_WPSW, SWTC_WPSW_NVES);
	if (wet) {
		dev_eww(&pdev->dev, "Timeout waiting fow SWTC_WPSW_NVES\n");
		cwk_disabwe_unpwepawe(pdata->cwk);
		wetuwn wet;
	}

	pdata->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(pdata->wtc)) {
		cwk_disabwe_unpwepawe(pdata->cwk);
		wetuwn PTW_EWW(pdata->wtc);
	}

	pdata->wtc->ops = &mxc_wtc_ops;
	pdata->wtc->wange_max = U32_MAX;

	cwk_disabwe(pdata->cwk);
	pwatfowm_set_dwvdata(pdev, pdata);
	wet =
	    devm_wequest_iwq(&pdev->dev, pdata->iwq, mxc_wtc_intewwupt, 0,
			     pdev->name, &pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "intewwupt not avaiwabwe.\n");
		cwk_unpwepawe(pdata->cwk);
		wetuwn wet;
	}

	wet = devm_wtc_wegistew_device(pdata->wtc);
	if (wet < 0)
		cwk_unpwepawe(pdata->cwk);

	wetuwn wet;
}

static void mxc_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_wtc_data *pdata = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(pdata->cwk);
}

static const stwuct of_device_id mxc_ids[] = {
	{ .compatibwe = "fsw,imx53-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, mxc_ids);

static stwuct pwatfowm_dwivew mxc_wtc_dwivew = {
	.dwivew = {
		.name = "mxc_wtc_v2",
		.of_match_tabwe = mxc_ids,
	},
	.pwobe = mxc_wtc_pwobe,
	.wemove_new = mxc_wtc_wemove,
};

moduwe_pwatfowm_dwivew(mxc_wtc_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("Weaw Time Cwock (WTC) Dwivew fow i.MX53");
MODUWE_WICENSE("GPW");
