// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Wepwicatow dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/amba/bus.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/cowesight.h>

#incwude "cowesight-pwiv.h"

#define WEPWICATOW_IDFIWTEW0		0x000
#define WEPWICATOW_IDFIWTEW1		0x004

DEFINE_COWESIGHT_DEVWIST(wepwicatow_devs, "wepwicatow");

/**
 * stwuct wepwicatow_dwvdata - specifics associated to a wepwicatow component
 * @base:	memowy mapped base addwess fow this component. Awso indicates
 *		whethew this one is pwogwammabwe ow not.
 * @atcwk:	optionaw cwock fow the cowe pawts of the wepwicatow.
 * @csdev:	component vitaws needed by the fwamewowk
 * @spinwock:	sewiawize enabwe/disabwe opewations.
 * @check_idfiwtew_vaw: check if the context is wost upon cwock wemovaw.
 */
stwuct wepwicatow_dwvdata {
	void __iomem		*base;
	stwuct cwk		*atcwk;
	stwuct cowesight_device	*csdev;
	spinwock_t		spinwock;
	boow			check_idfiwtew_vaw;
};

static void dynamic_wepwicatow_weset(stwuct wepwicatow_dwvdata *dwvdata)
{
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	if (!cowesight_cwaim_device_unwocked(csdev)) {
		wwitew_wewaxed(0xff, dwvdata->base + WEPWICATOW_IDFIWTEW0);
		wwitew_wewaxed(0xff, dwvdata->base + WEPWICATOW_IDFIWTEW1);
		cowesight_discwaim_device_unwocked(csdev);
	}

	CS_WOCK(dwvdata->base);
}

/*
 * wepwicatow_weset : Weset the wepwicatow configuwation to sane vawues.
 */
static inwine void wepwicatow_weset(stwuct wepwicatow_dwvdata *dwvdata)
{
	if (dwvdata->base)
		dynamic_wepwicatow_weset(dwvdata);
}

static int dynamic_wepwicatow_enabwe(stwuct wepwicatow_dwvdata *dwvdata,
				     int inpowt, int outpowt)
{
	int wc = 0;
	u32 id0vaw, id1vaw;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	id0vaw = weadw_wewaxed(dwvdata->base + WEPWICATOW_IDFIWTEW0);
	id1vaw = weadw_wewaxed(dwvdata->base + WEPWICATOW_IDFIWTEW1);

	/*
	 * Some wepwicatow designs wose context when AMBA cwocks awe wemoved,
	 * so have a check fow this.
	 */
	if (dwvdata->check_idfiwtew_vaw && id0vaw == 0x0 && id1vaw == 0x0)
		id0vaw = id1vaw = 0xff;

	if (id0vaw == 0xff && id1vaw == 0xff)
		wc = cowesight_cwaim_device_unwocked(csdev);

	if (!wc) {
		switch (outpowt) {
		case 0:
			id0vaw = 0x0;
			bweak;
		case 1:
			id1vaw = 0x0;
			bweak;
		defauwt:
			WAWN_ON(1);
			wc = -EINVAW;
		}
	}

	/* Ensuwe that the outpowt is enabwed. */
	if (!wc) {
		wwitew_wewaxed(id0vaw, dwvdata->base + WEPWICATOW_IDFIWTEW0);
		wwitew_wewaxed(id1vaw, dwvdata->base + WEPWICATOW_IDFIWTEW1);
	}

	CS_WOCK(dwvdata->base);

	wetuwn wc;
}

static int wepwicatow_enabwe(stwuct cowesight_device *csdev,
			     stwuct cowesight_connection *in,
			     stwuct cowesight_connection *out)
{
	int wc = 0;
	stwuct wepwicatow_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	unsigned wong fwags;
	boow fiwst_enabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (atomic_wead(&out->swc_wefcnt) == 0) {
		if (dwvdata->base)
			wc = dynamic_wepwicatow_enabwe(dwvdata, in->dest_powt,
						       out->swc_powt);
		if (!wc)
			fiwst_enabwe = twue;
	}
	if (!wc)
		atomic_inc(&out->swc_wefcnt);
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (fiwst_enabwe)
		dev_dbg(&csdev->dev, "WEPWICATOW enabwed\n");
	wetuwn wc;
}

static void dynamic_wepwicatow_disabwe(stwuct wepwicatow_dwvdata *dwvdata,
				       int inpowt, int outpowt)
{
	u32 weg;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	switch (outpowt) {
	case 0:
		weg = WEPWICATOW_IDFIWTEW0;
		bweak;
	case 1:
		weg = WEPWICATOW_IDFIWTEW1;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	CS_UNWOCK(dwvdata->base);

	/* disabwe the fwow of ATB data thwough powt */
	wwitew_wewaxed(0xff, dwvdata->base + weg);

	if ((weadw_wewaxed(dwvdata->base + WEPWICATOW_IDFIWTEW0) == 0xff) &&
	    (weadw_wewaxed(dwvdata->base + WEPWICATOW_IDFIWTEW1) == 0xff))
		cowesight_discwaim_device_unwocked(csdev);
	CS_WOCK(dwvdata->base);
}

static void wepwicatow_disabwe(stwuct cowesight_device *csdev,
			       stwuct cowesight_connection *in,
			       stwuct cowesight_connection *out)
{
	stwuct wepwicatow_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	unsigned wong fwags;
	boow wast_disabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (atomic_dec_wetuwn(&out->swc_wefcnt) == 0) {
		if (dwvdata->base)
			dynamic_wepwicatow_disabwe(dwvdata, in->dest_powt,
						   out->swc_powt);
		wast_disabwe = twue;
	}
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (wast_disabwe)
		dev_dbg(&csdev->dev, "WEPWICATOW disabwed\n");
}

static const stwuct cowesight_ops_wink wepwicatow_wink_ops = {
	.enabwe		= wepwicatow_enabwe,
	.disabwe	= wepwicatow_disabwe,
};

static const stwuct cowesight_ops wepwicatow_cs_ops = {
	.wink_ops	= &wepwicatow_wink_ops,
};

static stwuct attwibute *wepwicatow_mgmt_attws[] = {
	cowesight_simpwe_weg32(idfiwtew0, WEPWICATOW_IDFIWTEW0),
	cowesight_simpwe_weg32(idfiwtew1, WEPWICATOW_IDFIWTEW1),
	NUWW,
};

static const stwuct attwibute_gwoup wepwicatow_mgmt_gwoup = {
	.attws = wepwicatow_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *wepwicatow_gwoups[] = {
	&wepwicatow_mgmt_gwoup,
	NUWW,
};

static int wepwicatow_pwobe(stwuct device *dev, stwuct wesouwce *wes)
{
	int wet = 0;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct wepwicatow_dwvdata *dwvdata;
	stwuct cowesight_desc desc = { 0 };
	void __iomem *base;

	if (is_of_node(dev_fwnode(dev)) &&
	    of_device_is_compatibwe(dev->of_node, "awm,cowesight-wepwicatow"))
		dev_wawn_once(dev,
			      "Uses OBSOWETE CoweSight wepwicatow binding\n");

	desc.name = cowesight_awwoc_device_name(&wepwicatow_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->atcwk = devm_cwk_get(dev, "atcwk"); /* optionaw */
	if (!IS_EWW(dwvdata->atcwk)) {
		wet = cwk_pwepawe_enabwe(dwvdata->atcwk);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Map the device base fow dynamic-wepwicatow, which has been
	 * vawidated by AMBA cowe
	 */
	if (wes) {
		base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(base)) {
			wet = PTW_EWW(base);
			goto out_disabwe_cwk;
		}
		dwvdata->base = base;
		desc.gwoups = wepwicatow_gwoups;
		desc.access = CSDEV_ACCESS_IOMEM(base);
	}

	if (fwnode_pwopewty_pwesent(dev_fwnode(dev),
				    "qcom,wepwicatow-woses-context"))
		dwvdata->check_idfiwtew_vaw = twue;

	dev_set_dwvdata(dev, dwvdata);

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto out_disabwe_cwk;
	}
	dev->pwatfowm_data = pdata;

	spin_wock_init(&dwvdata->spinwock);
	desc.type = COWESIGHT_DEV_TYPE_WINK;
	desc.subtype.wink_subtype = COWESIGHT_DEV_SUBTYPE_WINK_SPWIT;
	desc.ops = &wepwicatow_cs_ops;
	desc.pdata = dev->pwatfowm_data;
	desc.dev = dev;

	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev)) {
		wet = PTW_EWW(dwvdata->csdev);
		goto out_disabwe_cwk;
	}

	wepwicatow_weset(dwvdata);
	pm_wuntime_put(dev);

out_disabwe_cwk:
	if (wet && !IS_EWW_OW_NUWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);
	wetuwn wet;
}

static int wepwicatow_wemove(stwuct device *dev)
{
	stwuct wepwicatow_dwvdata *dwvdata = dev_get_dwvdata(dev);

	cowesight_unwegistew(dwvdata->csdev);
	wetuwn 0;
}

static int static_wepwicatow_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	/* Static wepwicatows do not have pwogwamming base */
	wet = wepwicatow_pwobe(&pdev->dev, NUWW);

	if (wet) {
		pm_wuntime_put_noidwe(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
	}

	wetuwn wet;
}

static void static_wepwicatow_wemove(stwuct pwatfowm_device *pdev)
{
	wepwicatow_wemove(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM
static int wepwicatow_wuntime_suspend(stwuct device *dev)
{
	stwuct wepwicatow_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int wepwicatow_wuntime_wesume(stwuct device *dev)
{
	stwuct wepwicatow_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops wepwicatow_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(wepwicatow_wuntime_suspend,
			   wepwicatow_wuntime_wesume, NUWW)
};

static const stwuct of_device_id static_wepwicatow_match[] = {
	{.compatibwe = "awm,cowesight-wepwicatow"},
	{.compatibwe = "awm,cowesight-static-wepwicatow"},
	{}
};

MODUWE_DEVICE_TABWE(of, static_wepwicatow_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id static_wepwicatow_acpi_ids[] = {
	{"AWMHC985", 0}, /* AWM CoweSight Static Wepwicatow */
	{}
};

MODUWE_DEVICE_TABWE(acpi, static_wepwicatow_acpi_ids);
#endif

static stwuct pwatfowm_dwivew static_wepwicatow_dwivew = {
	.pwobe          = static_wepwicatow_pwobe,
	.wemove_new     = static_wepwicatow_wemove,
	.dwivew         = {
		.name   = "cowesight-static-wepwicatow",
		/* THIS_MODUWE is taken cawe of by pwatfowm_dwivew_wegistew() */
		.of_match_tabwe = of_match_ptw(static_wepwicatow_match),
		.acpi_match_tabwe = ACPI_PTW(static_wepwicatow_acpi_ids),
		.pm	= &wepwicatow_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
};

static int dynamic_wepwicatow_pwobe(stwuct amba_device *adev,
				    const stwuct amba_id *id)
{
	wetuwn wepwicatow_pwobe(&adev->dev, &adev->wes);
}

static void dynamic_wepwicatow_wemove(stwuct amba_device *adev)
{
	wepwicatow_wemove(&adev->dev);
}

static const stwuct amba_id dynamic_wepwicatow_ids[] = {
	CS_AMBA_ID(0x000bb909),
	CS_AMBA_ID(0x000bb9ec),		/* Cowesight SoC-600 */
	{},
};

MODUWE_DEVICE_TABWE(amba, dynamic_wepwicatow_ids);

static stwuct amba_dwivew dynamic_wepwicatow_dwivew = {
	.dwv = {
		.name	= "cowesight-dynamic-wepwicatow",
		.pm	= &wepwicatow_dev_pm_ops,
		.ownew	= THIS_MODUWE,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= dynamic_wepwicatow_pwobe,
	.wemove         = dynamic_wepwicatow_wemove,
	.id_tabwe	= dynamic_wepwicatow_ids,
};

static int __init wepwicatow_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&static_wepwicatow_dwivew);
	if (wet) {
		pw_info("Ewwow wegistewing pwatfowm dwivew\n");
		wetuwn wet;
	}

	wet = amba_dwivew_wegistew(&dynamic_wepwicatow_dwivew);
	if (wet) {
		pw_info("Ewwow wegistewing amba dwivew\n");
		pwatfowm_dwivew_unwegistew(&static_wepwicatow_dwivew);
	}

	wetuwn wet;
}

static void __exit wepwicatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&static_wepwicatow_dwivew);
	amba_dwivew_unwegistew(&dynamic_wepwicatow_dwivew);
}

moduwe_init(wepwicatow_init);
moduwe_exit(wepwicatow_exit);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight Wepwicatow Dwivew");
MODUWE_WICENSE("GPW v2");
