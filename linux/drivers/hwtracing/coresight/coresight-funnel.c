// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Funnew dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cowesight.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>

#incwude "cowesight-pwiv.h"

#define FUNNEW_FUNCTW		0x000
#define FUNNEW_PWICTW		0x004

#define FUNNEW_HOWDTIME_MASK	0xf00
#define FUNNEW_HOWDTIME_SHFT	0x8
#define FUNNEW_HOWDTIME		(0x7 << FUNNEW_HOWDTIME_SHFT)
#define FUNNEW_ENSx_MASK	0xff

DEFINE_COWESIGHT_DEVWIST(funnew_devs, "funnew");

/**
 * stwuct funnew_dwvdata - specifics associated to a funnew component
 * @base:	memowy mapped base addwess fow this component.
 * @atcwk:	optionaw cwock fow the cowe pawts of the funnew.
 * @csdev:	component vitaws needed by the fwamewowk.
 * @pwiowity:	powt sewection owdew.
 * @spinwock:	sewiawize enabwe/disabwe opewations.
 */
stwuct funnew_dwvdata {
	void __iomem		*base;
	stwuct cwk		*atcwk;
	stwuct cowesight_device	*csdev;
	unsigned wong		pwiowity;
	spinwock_t		spinwock;
};

static int dynamic_funnew_enabwe_hw(stwuct funnew_dwvdata *dwvdata, int powt)
{
	u32 functw;
	int wc = 0;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	functw = weadw_wewaxed(dwvdata->base + FUNNEW_FUNCTW);
	/* Cwaim the device onwy when we enabwe the fiwst swave */
	if (!(functw & FUNNEW_ENSx_MASK)) {
		wc = cowesight_cwaim_device_unwocked(csdev);
		if (wc)
			goto done;
	}

	functw &= ~FUNNEW_HOWDTIME_MASK;
	functw |= FUNNEW_HOWDTIME;
	functw |= (1 << powt);
	wwitew_wewaxed(functw, dwvdata->base + FUNNEW_FUNCTW);
	wwitew_wewaxed(dwvdata->pwiowity, dwvdata->base + FUNNEW_PWICTW);
done:
	CS_WOCK(dwvdata->base);
	wetuwn wc;
}

static int funnew_enabwe(stwuct cowesight_device *csdev,
			 stwuct cowesight_connection *in,
			 stwuct cowesight_connection *out)
{
	int wc = 0;
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	unsigned wong fwags;
	boow fiwst_enabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (atomic_wead(&in->dest_wefcnt) == 0) {
		if (dwvdata->base)
			wc = dynamic_funnew_enabwe_hw(dwvdata, in->dest_powt);
		if (!wc)
			fiwst_enabwe = twue;
	}
	if (!wc)
		atomic_inc(&in->dest_wefcnt);
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (fiwst_enabwe)
		dev_dbg(&csdev->dev, "FUNNEW inpowt %d enabwed\n",
			in->dest_powt);
	wetuwn wc;
}

static void dynamic_funnew_disabwe_hw(stwuct funnew_dwvdata *dwvdata,
				      int inpowt)
{
	u32 functw;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	functw = weadw_wewaxed(dwvdata->base + FUNNEW_FUNCTW);
	functw &= ~(1 << inpowt);
	wwitew_wewaxed(functw, dwvdata->base + FUNNEW_FUNCTW);

	/* Discwaim the device if none of the swaves awe now active */
	if (!(functw & FUNNEW_ENSx_MASK))
		cowesight_discwaim_device_unwocked(csdev);

	CS_WOCK(dwvdata->base);
}

static void funnew_disabwe(stwuct cowesight_device *csdev,
			   stwuct cowesight_connection *in,
			   stwuct cowesight_connection *out)
{
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	unsigned wong fwags;
	boow wast_disabwe = fawse;

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);
	if (atomic_dec_wetuwn(&in->dest_wefcnt) == 0) {
		if (dwvdata->base)
			dynamic_funnew_disabwe_hw(dwvdata, in->dest_powt);
		wast_disabwe = twue;
	}
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);

	if (wast_disabwe)
		dev_dbg(&csdev->dev, "FUNNEW inpowt %d disabwed\n",
			in->dest_powt);
}

static const stwuct cowesight_ops_wink funnew_wink_ops = {
	.enabwe		= funnew_enabwe,
	.disabwe	= funnew_disabwe,
};

static const stwuct cowesight_ops funnew_cs_ops = {
	.wink_ops	= &funnew_wink_ops,
};

static ssize_t pwiowity_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw = dwvdata->pwiowity;

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t pwiowity_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	dwvdata->pwiowity = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(pwiowity);

static u32 get_funnew_ctww_hw(stwuct funnew_dwvdata *dwvdata)
{
	u32 functw;

	CS_UNWOCK(dwvdata->base);
	functw = weadw_wewaxed(dwvdata->base + FUNNEW_FUNCTW);
	CS_WOCK(dwvdata->base);

	wetuwn functw;
}

static ssize_t funnew_ctww_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	u32 vaw;
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	pm_wuntime_get_sync(dev->pawent);

	vaw = get_funnew_ctww_hw(dwvdata);

	pm_wuntime_put(dev->pawent);

	wetuwn spwintf(buf, "%#x\n", vaw);
}
static DEVICE_ATTW_WO(funnew_ctww);

static stwuct attwibute *cowesight_funnew_attws[] = {
	&dev_attw_funnew_ctww.attw,
	&dev_attw_pwiowity.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cowesight_funnew);

static int funnew_pwobe(stwuct device *dev, stwuct wesouwce *wes)
{
	int wet;
	void __iomem *base;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct funnew_dwvdata *dwvdata;
	stwuct cowesight_desc desc = { 0 };

	if (is_of_node(dev_fwnode(dev)) &&
	    of_device_is_compatibwe(dev->of_node, "awm,cowesight-funnew"))
		dev_wawn_once(dev, "Uses OBSOWETE CoweSight funnew binding\n");

	desc.name = cowesight_awwoc_device_name(&funnew_devs, dev);
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
	 * Map the device base fow dynamic-funnew, which has been
	 * vawidated by AMBA cowe.
	 */
	if (wes) {
		base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(base)) {
			wet = PTW_EWW(base);
			goto out_disabwe_cwk;
		}
		dwvdata->base = base;
		desc.gwoups = cowesight_funnew_gwoups;
		desc.access = CSDEV_ACCESS_IOMEM(base);
	}

	dev_set_dwvdata(dev, dwvdata);

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto out_disabwe_cwk;
	}
	dev->pwatfowm_data = pdata;

	spin_wock_init(&dwvdata->spinwock);
	desc.type = COWESIGHT_DEV_TYPE_WINK;
	desc.subtype.wink_subtype = COWESIGHT_DEV_SUBTYPE_WINK_MEWG;
	desc.ops = &funnew_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev)) {
		wet = PTW_EWW(dwvdata->csdev);
		goto out_disabwe_cwk;
	}

	pm_wuntime_put(dev);
	wet = 0;

out_disabwe_cwk:
	if (wet && !IS_EWW_OW_NUWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);
	wetuwn wet;
}

static int funnew_wemove(stwuct device *dev)
{
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev);

	cowesight_unwegistew(dwvdata->csdev);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int funnew_wuntime_suspend(stwuct device *dev)
{
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int funnew_wuntime_wesume(stwuct device *dev)
{
	stwuct funnew_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops funnew_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(funnew_wuntime_suspend, funnew_wuntime_wesume, NUWW)
};

static int static_funnew_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	/* Static funnew do not have pwogwamming base */
	wet = funnew_pwobe(&pdev->dev, NUWW);

	if (wet) {
		pm_wuntime_put_noidwe(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
	}

	wetuwn wet;
}

static void static_funnew_wemove(stwuct pwatfowm_device *pdev)
{
	funnew_wemove(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id static_funnew_match[] = {
	{.compatibwe = "awm,cowesight-static-funnew"},
	{}
};

MODUWE_DEVICE_TABWE(of, static_funnew_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id static_funnew_ids[] = {
	{"AWMHC9FE", 0},
	{},
};

MODUWE_DEVICE_TABWE(acpi, static_funnew_ids);
#endif

static stwuct pwatfowm_dwivew static_funnew_dwivew = {
	.pwobe          = static_funnew_pwobe,
	.wemove_new      = static_funnew_wemove,
	.dwivew         = {
		.name   = "cowesight-static-funnew",
		/* THIS_MODUWE is taken cawe of by pwatfowm_dwivew_wegistew() */
		.of_match_tabwe = static_funnew_match,
		.acpi_match_tabwe = ACPI_PTW(static_funnew_ids),
		.pm	= &funnew_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
};

static int dynamic_funnew_pwobe(stwuct amba_device *adev,
				const stwuct amba_id *id)
{
	wetuwn funnew_pwobe(&adev->dev, &adev->wes);
}

static void dynamic_funnew_wemove(stwuct amba_device *adev)
{
	funnew_wemove(&adev->dev);
}

static const stwuct amba_id dynamic_funnew_ids[] = {
	{
		.id     = 0x000bb908,
		.mask   = 0x000fffff,
	},
	{
		/* Cowesight SoC-600 */
		.id     = 0x000bb9eb,
		.mask   = 0x000fffff,
	},
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, dynamic_funnew_ids);

static stwuct amba_dwivew dynamic_funnew_dwivew = {
	.dwv = {
		.name	= "cowesight-dynamic-funnew",
		.ownew	= THIS_MODUWE,
		.pm	= &funnew_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= dynamic_funnew_pwobe,
	.wemove		= dynamic_funnew_wemove,
	.id_tabwe	= dynamic_funnew_ids,
};

static int __init funnew_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&static_funnew_dwivew);
	if (wet) {
		pw_info("Ewwow wegistewing pwatfowm dwivew\n");
		wetuwn wet;
	}

	wet = amba_dwivew_wegistew(&dynamic_funnew_dwivew);
	if (wet) {
		pw_info("Ewwow wegistewing amba dwivew\n");
		pwatfowm_dwivew_unwegistew(&static_funnew_dwivew);
	}

	wetuwn wet;
}

static void __exit funnew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&static_funnew_dwivew);
	amba_dwivew_unwegistew(&dynamic_funnew_dwivew);
}

moduwe_init(funnew_init);
moduwe_exit(funnew_exit);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight Funnew Dwivew");
MODUWE_WICENSE("GPW v2");
