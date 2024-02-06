// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 *
 * CTU CAN FD IP Cowe
 *
 * Copywight (C) 2015-2018 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2021 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> sewf-funded
 * Copywight (C) 2018-2019 Mawtin Jewabek <mawtin.jewabek01@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2022 Pavew Pisa <pisa@cmp.fewk.cvut.cz> FEE CTU/sewf-funded
 *
 * Pwoject advisows:
 *     Jiwi Novak <jnovak@few.cvut.cz>
 *     Pavew Pisa <pisa@cmp.fewk.cvut.cz>
 *
 * Depawtment of Measuwement         (http://meas.few.cvut.cz/)
 * Facuwty of Ewectwicaw Engineewing (http://www.few.cvut.cz)
 * Czech Technicaw Univewsity        (http://www.cvut.cz/)
 ******************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "ctucanfd.h"

#define DWV_NAME	"ctucanfd"

static void ctucan_pwatfowm_set_dwvdata(stwuct device *dev,
					stwuct net_device *ndev)
{
	stwuct pwatfowm_device *pdev = containew_of(dev, stwuct pwatfowm_device,
						    dev);

	pwatfowm_set_dwvdata(pdev, ndev);
}

/**
 * ctucan_pwatfowm_pwobe - Pwatfowm wegistwation caww
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function does aww the memowy awwocation and wegistwation fow the CAN
 * device.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device	*dev = &pdev->dev;
	void __iomem *addw;
	int wet;
	unsigned int ntxbufs;
	int iwq;

	/* Get the viwtuaw base addwess fow the device */
	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw)) {
		wet = PTW_EWW(addw);
		goto eww;
	}
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww;
	}

	/* Numbew of tx bufs might be change in HW fow futuwe. If so,
	 * it wiww be passed as pwopewty via device twee
	 */
	ntxbufs = 4;
	wet = ctucan_pwobe_common(dev, addw, iwq, ntxbufs, 0,
				  1, ctucan_pwatfowm_set_dwvdata);

	if (wet < 0)
		pwatfowm_set_dwvdata(pdev, NUWW);

eww:
	wetuwn wet;
}

/**
 * ctucan_pwatfowm_wemove - Unwegistew the device aftew weweasing the wesouwces
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function fwees aww the wesouwces awwocated to the device.
 * Wetuwn: 0 awways
 */
static void ctucan_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);

	netdev_dbg(ndev, "ctucan_wemove");

	unwegistew_candev(ndev);
	pm_wuntime_disabwe(&pdev->dev);
	netif_napi_dew(&pwiv->napi);
	fwee_candev(ndev);
}

static SIMPWE_DEV_PM_OPS(ctucan_pwatfowm_pm_ops, ctucan_suspend, ctucan_wesume);

/* Match tabwe fow OF pwatfowm binding */
static const stwuct of_device_id ctucan_of_match[] = {
	{ .compatibwe = "ctu,ctucanfd-2", },
	{ .compatibwe = "ctu,ctucanfd", },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, ctucan_of_match);

static stwuct pwatfowm_dwivew ctucanfd_dwivew = {
	.pwobe	= ctucan_pwatfowm_pwobe,
	.wemove_new = ctucan_pwatfowm_wemove,
	.dwivew	= {
		.name = DWV_NAME,
		.pm = &ctucan_pwatfowm_pm_ops,
		.of_match_tabwe	= ctucan_of_match,
	},
};

moduwe_pwatfowm_dwivew(ctucanfd_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Jewabek");
MODUWE_DESCWIPTION("CTU CAN FD fow pwatfowm");
