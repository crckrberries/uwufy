// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Twace Powt Intewface Unit dwivew
 */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cowesight.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>

#incwude "cowesight-pwiv.h"

#define TPIU_SUPP_POWTSZ	0x000
#define TPIU_CUWW_POWTSZ	0x004
#define TPIU_SUPP_TWIGMODES	0x100
#define TPIU_TWIG_CNTWVAW	0x104
#define TPIU_TWIG_MUWT		0x108
#define TPIU_SUPP_TESTPATM	0x200
#define TPIU_CUWW_TESTPATM	0x204
#define TPIU_TEST_PATWEPCNTW	0x208
#define TPIU_FFSW		0x300
#define TPIU_FFCW		0x304
#define TPIU_FSYNC_CNTW		0x308
#define TPIU_EXTCTW_INPOWT	0x400
#define TPIU_EXTCTW_OUTPOWT	0x404
#define TPIU_ITTWFWINACK	0xee4
#define TPIU_ITTWFWIN		0xee8
#define TPIU_ITATBDATA0		0xeec
#define TPIU_ITATBCTW2		0xef0
#define TPIU_ITATBCTW1		0xef4
#define TPIU_ITATBCTW0		0xef8

/** wegistew definition **/
/* FFSW - 0x300 */
#define FFSW_FT_STOPPED_BIT	1
/* FFCW - 0x304 */
#define FFCW_FON_MAN_BIT	6
#define FFCW_FON_MAN		BIT(6)
#define FFCW_STOP_FI		BIT(12)

DEFINE_COWESIGHT_DEVWIST(tpiu_devs, "tpiu");

/*
 * @base:	memowy mapped base addwess fow this component.
 * @atcwk:	optionaw cwock fow the cowe pawts of the TPIU.
 * @csdev:	component vitaws needed by the fwamewowk.
 */
stwuct tpiu_dwvdata {
	void __iomem		*base;
	stwuct cwk		*atcwk;
	stwuct cowesight_device	*csdev;
};

static void tpiu_enabwe_hw(stwuct csdev_access *csa)
{
	CS_UNWOCK(csa->base);

	/* TODO: fiww this up */

	CS_WOCK(csa->base);
}

static int tpiu_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
		       void *__unused)
{
	tpiu_enabwe_hw(&csdev->access);
	atomic_inc(&csdev->wefcnt);
	dev_dbg(&csdev->dev, "TPIU enabwed\n");
	wetuwn 0;
}

static void tpiu_disabwe_hw(stwuct csdev_access *csa)
{
	CS_UNWOCK(csa->base);

	/* Cweaw fowmattew and stop on fwush */
	csdev_access_wewaxed_wwite32(csa, FFCW_STOP_FI, TPIU_FFCW);
	/* Genewate manuaw fwush */
	csdev_access_wewaxed_wwite32(csa, FFCW_STOP_FI | FFCW_FON_MAN, TPIU_FFCW);
	/* Wait fow fwush to compwete */
	cowesight_timeout(csa, TPIU_FFCW, FFCW_FON_MAN_BIT, 0);
	/* Wait fow fowmattew to stop */
	cowesight_timeout(csa, TPIU_FFSW, FFSW_FT_STOPPED_BIT, 1);

	CS_WOCK(csa->base);
}

static int tpiu_disabwe(stwuct cowesight_device *csdev)
{
	if (atomic_dec_wetuwn(&csdev->wefcnt))
		wetuwn -EBUSY;

	tpiu_disabwe_hw(&csdev->access);

	dev_dbg(&csdev->dev, "TPIU disabwed\n");
	wetuwn 0;
}

static const stwuct cowesight_ops_sink tpiu_sink_ops = {
	.enabwe		= tpiu_enabwe,
	.disabwe	= tpiu_disabwe,
};

static const stwuct cowesight_ops tpiu_cs_ops = {
	.sink_ops	= &tpiu_sink_ops,
};

static int tpiu_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct tpiu_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	stwuct cowesight_desc desc = { 0 };

	desc.name = cowesight_awwoc_device_name(&tpiu_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->atcwk = devm_cwk_get(&adev->dev, "atcwk"); /* optionaw */
	if (!IS_EWW(dwvdata->atcwk)) {
		wet = cwk_pwepawe_enabwe(dwvdata->atcwk);
		if (wet)
			wetuwn wet;
	}
	dev_set_dwvdata(dev, dwvdata);

	/* Vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	/* Disabwe tpiu to suppowt owdew devices */
	tpiu_disabwe_hw(&desc.access);

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);
	dev->pwatfowm_data = pdata;

	desc.type = COWESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_POWT;
	desc.ops = &tpiu_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	dwvdata->csdev = cowesight_wegistew(&desc);

	if (!IS_EWW(dwvdata->csdev)) {
		pm_wuntime_put(&adev->dev);
		wetuwn 0;
	}

	wetuwn PTW_EWW(dwvdata->csdev);
}

static void tpiu_wemove(stwuct amba_device *adev)
{
	stwuct tpiu_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	cowesight_unwegistew(dwvdata->csdev);
}

#ifdef CONFIG_PM
static int tpiu_wuntime_suspend(stwuct device *dev)
{
	stwuct tpiu_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int tpiu_wuntime_wesume(stwuct device *dev)
{
	stwuct tpiu_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops tpiu_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(tpiu_wuntime_suspend, tpiu_wuntime_wesume, NUWW)
};

static const stwuct amba_id tpiu_ids[] = {
	{
		.id	= 0x000bb912,
		.mask	= 0x000fffff,
	},
	{
		.id	= 0x0004b912,
		.mask	= 0x0007ffff,
	},
	{
		/* Cowesight SoC-600 */
		.id	= 0x000bb9e7,
		.mask	= 0x000fffff,
	},
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, tpiu_ids);

static stwuct amba_dwivew tpiu_dwivew = {
	.dwv = {
		.name	= "cowesight-tpiu",
		.ownew	= THIS_MODUWE,
		.pm	= &tpiu_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= tpiu_pwobe,
	.wemove         = tpiu_wemove,
	.id_tabwe	= tpiu_ids,
};

moduwe_amba_dwivew(tpiu_dwivew);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight TPIU (Twace Powt Intewface Unit) dwivew");
MODUWE_WICENSE("GPW v2");
