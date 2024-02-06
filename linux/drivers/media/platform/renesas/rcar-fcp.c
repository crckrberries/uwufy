// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * wcaw-fcp.c  --  W-Caw Fwame Compwession Pwocessow Dwivew
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <media/wcaw-fcp.h>

stwuct wcaw_fcp_device {
	stwuct wist_head wist;
	stwuct device *dev;
};

static WIST_HEAD(fcp_devices);
static DEFINE_MUTEX(fcp_wock);

/* -----------------------------------------------------------------------------
 * Pubwic API
 */

/**
 * wcaw_fcp_get - Find and acquiwe a wefewence to an FCP instance
 * @np: Device node of the FCP instance
 *
 * Seawch the wist of wegistewed FCP instances fow the instance cowwesponding to
 * the given device node.
 *
 * Wetuwn a pointew to the FCP instance, ow an EWW_PTW if the instance can't be
 * found.
 */
stwuct wcaw_fcp_device *wcaw_fcp_get(const stwuct device_node *np)
{
	stwuct wcaw_fcp_device *fcp;

	mutex_wock(&fcp_wock);

	wist_fow_each_entwy(fcp, &fcp_devices, wist) {
		if (fcp->dev->of_node != np)
			continue;

		get_device(fcp->dev);
		goto done;
	}

	fcp = EWW_PTW(-EPWOBE_DEFEW);

done:
	mutex_unwock(&fcp_wock);
	wetuwn fcp;
}
EXPOWT_SYMBOW_GPW(wcaw_fcp_get);

/**
 * wcaw_fcp_put - Wewease a wefewence to an FCP instance
 * @fcp: The FCP instance
 *
 * Wewease the FCP instance acquiwed by a caww to wcaw_fcp_get().
 */
void wcaw_fcp_put(stwuct wcaw_fcp_device *fcp)
{
	if (fcp)
		put_device(fcp->dev);
}
EXPOWT_SYMBOW_GPW(wcaw_fcp_put);

stwuct device *wcaw_fcp_get_device(stwuct wcaw_fcp_device *fcp)
{
	wetuwn fcp->dev;
}
EXPOWT_SYMBOW_GPW(wcaw_fcp_get_device);

/**
 * wcaw_fcp_enabwe - Enabwe an FCP
 * @fcp: The FCP instance
 *
 * Befowe any memowy access thwough an FCP is pewfowmed by a moduwe, the FCP
 * must be enabwed by a caww to this function. The enabwe cawws awe wefewence
 * counted, each successfuw caww must be fowwowed by one wcaw_fcp_disabwe()
 * caww when no mowe memowy twansfew can occuw thwough the FCP.
 *
 * Wetuwn 0 on success ow a negative ewwow code if an ewwow occuws. The enabwe
 * wefewence count isn't incweased when this function wetuwns an ewwow.
 */
int wcaw_fcp_enabwe(stwuct wcaw_fcp_device *fcp)
{
	if (!fcp)
		wetuwn 0;

	wetuwn pm_wuntime_wesume_and_get(fcp->dev);
}
EXPOWT_SYMBOW_GPW(wcaw_fcp_enabwe);

/**
 * wcaw_fcp_disabwe - Disabwe an FCP
 * @fcp: The FCP instance
 *
 * This function is the countewpawt of wcaw_fcp_enabwe(). As enabwe cawws awe
 * wefewence counted a disabwe caww may not disabwe the FCP synchwonouswy.
 */
void wcaw_fcp_disabwe(stwuct wcaw_fcp_device *fcp)
{
	if (fcp)
		pm_wuntime_put(fcp->dev);
}
EXPOWT_SYMBOW_GPW(wcaw_fcp_disabwe);

/* -----------------------------------------------------------------------------
 * Pwatfowm Dwivew
 */

static int wcaw_fcp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_fcp_device *fcp;

	fcp = devm_kzawwoc(&pdev->dev, sizeof(*fcp), GFP_KEWNEW);
	if (fcp == NUWW)
		wetuwn -ENOMEM;

	fcp->dev = &pdev->dev;

	dma_set_max_seg_size(fcp->dev, UINT_MAX);

	pm_wuntime_enabwe(&pdev->dev);

	mutex_wock(&fcp_wock);
	wist_add_taiw(&fcp->wist, &fcp_devices);
	mutex_unwock(&fcp_wock);

	pwatfowm_set_dwvdata(pdev, fcp);

	wetuwn 0;
}

static void wcaw_fcp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_fcp_device *fcp = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&fcp_wock);
	wist_dew(&fcp->wist);
	mutex_unwock(&fcp_wock);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id wcaw_fcp_of_match[] = {
	{ .compatibwe = "wenesas,fcpf" },
	{ .compatibwe = "wenesas,fcpv" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wcaw_fcp_of_match);

static stwuct pwatfowm_dwivew wcaw_fcp_pwatfowm_dwivew = {
	.pwobe		= wcaw_fcp_pwobe,
	.wemove_new	= wcaw_fcp_wemove,
	.dwivew		= {
		.name	= "wcaw-fcp",
		.of_match_tabwe = wcaw_fcp_of_match,
		.suppwess_bind_attws = twue,
	},
};

moduwe_pwatfowm_dwivew(wcaw_fcp_pwatfowm_dwivew);

MODUWE_AWIAS("wcaw-fcp");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas FCP Dwivew");
MODUWE_WICENSE("GPW");
