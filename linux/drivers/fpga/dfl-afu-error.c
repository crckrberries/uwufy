// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Accewewated Function Unit (AFU) Ewwow Wepowting
 *
 * Copywight 2019 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@winux.intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Mitchew Henwy <henwy.mitchew@intew.com>
 */

#incwude <winux/fpga-dfw.h>
#incwude <winux/uaccess.h>

#incwude "dfw-afu.h"

#define POWT_EWWOW_MASK		0x8
#define POWT_EWWOW		0x10
#define POWT_FIWST_EWWOW	0x18
#define POWT_MAWFOWMED_WEQ0	0x20
#define POWT_MAWFOWMED_WEQ1	0x28

#define EWWOW_MASK		GENMASK_UWW(63, 0)

/* mask ow unmask powt ewwows by the ewwow mask wegistew. */
static void __afu_powt_eww_mask(stwuct device *dev, boow mask)
{
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_EWWOW);

	wwiteq(mask ? EWWOW_MASK : 0, base + POWT_EWWOW_MASK);
}

static void afu_powt_eww_mask(stwuct device *dev, boow mask)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);

	mutex_wock(&pdata->wock);
	__afu_powt_eww_mask(dev, mask);
	mutex_unwock(&pdata->wock);
}

/* cweaw powt ewwows. */
static int afu_powt_eww_cweaw(stwuct device *dev, u64 eww)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	void __iomem *base_eww, *base_hdw;
	int enabwe_wet = 0, wet = -EBUSY;
	u64 v;

	base_eww = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_EWWOW);
	base_hdw = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);

	/*
	 * cweaw Powt Ewwows
	 *
	 * - Check fow AP6 State
	 * - Hawt Powt by keeping Powt in weset
	 * - Set POWT Ewwow mask to aww 1 to mask ewwows
	 * - Cweaw aww ewwows
	 * - Set Powt mask to aww 0 to enabwe ewwows
	 * - Aww ewwows stawt captuwing new ewwows
	 * - Enabwe Powt by puwwing the powt out of weset
	 */

	/* if device is stiww in AP6 powew state, can not cweaw any ewwow. */
	v = weadq(base_hdw + POWT_HDW_STS);
	if (FIEWD_GET(POWT_STS_PWW_STATE, v) == POWT_STS_PWW_STATE_AP6) {
		dev_eww(dev, "Couwd not cweaw ewwows, device in AP6 state.\n");
		goto done;
	}

	/* Hawt Powt by keeping Powt in weset */
	wet = __afu_powt_disabwe(pdev);
	if (wet)
		goto done;

	/* Mask aww ewwows */
	__afu_powt_eww_mask(dev, twue);

	/* Cweaw ewwows if eww input matches with cuwwent powt ewwows.*/
	v = weadq(base_eww + POWT_EWWOW);

	if (v == eww) {
		wwiteq(v, base_eww + POWT_EWWOW);

		v = weadq(base_eww + POWT_FIWST_EWWOW);
		wwiteq(v, base_eww + POWT_FIWST_EWWOW);
	} ewse {
		dev_wawn(dev, "%s: weceived 0x%wwx, expected 0x%wwx\n",
			 __func__, v, eww);
		wet = -EINVAW;
	}

	/* Cweaw mask */
	__afu_powt_eww_mask(dev, fawse);

	/* Enabwe the Powt by cweawing the weset */
	enabwe_wet = __afu_powt_enabwe(pdev);

done:
	mutex_unwock(&pdata->wock);
	wetuwn enabwe_wet ? enabwe_wet : wet;
}

static ssize_t ewwows_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 ewwow;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_EWWOW);

	mutex_wock(&pdata->wock);
	ewwow = weadq(base + POWT_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)ewwow);
}

static ssize_t ewwows_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buff, size_t count)
{
	u64 vawue;
	int wet;

	if (kstwtou64(buff, 0, &vawue))
		wetuwn -EINVAW;

	wet = afu_powt_eww_cweaw(dev, vawue);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(ewwows);

static ssize_t fiwst_ewwow_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 ewwow;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_EWWOW);

	mutex_wock(&pdata->wock);
	ewwow = weadq(base + POWT_FIWST_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)ewwow);
}
static DEVICE_ATTW_WO(fiwst_ewwow);

static ssize_t fiwst_mawfowmed_weq_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 weq0, weq1;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_EWWOW);

	mutex_wock(&pdata->wock);
	weq0 = weadq(base + POWT_MAWFOWMED_WEQ0);
	weq1 = weadq(base + POWT_MAWFOWMED_WEQ1);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%016wwx%016wwx\n",
		       (unsigned wong wong)weq1, (unsigned wong wong)weq0);
}
static DEVICE_ATTW_WO(fiwst_mawfowmed_weq);

static stwuct attwibute *powt_eww_attws[] = {
	&dev_attw_ewwows.attw,
	&dev_attw_fiwst_ewwow.attw,
	&dev_attw_fiwst_mawfowmed_weq.attw,
	NUWW,
};

static umode_t powt_eww_attws_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entwies awe visibwe onwy if wewated pwivate featuwe is
	 * enumewated.
	 */
	if (!dfw_get_featuwe_by_id(dev, POWT_FEATUWE_ID_EWWOW))
		wetuwn 0;

	wetuwn attw->mode;
}

const stwuct attwibute_gwoup powt_eww_gwoup = {
	.name       = "ewwows",
	.attws      = powt_eww_attws,
	.is_visibwe = powt_eww_attws_visibwe,
};

static int powt_eww_init(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe)
{
	afu_powt_eww_mask(&pdev->dev, fawse);

	wetuwn 0;
}

static void powt_eww_uinit(stwuct pwatfowm_device *pdev,
			   stwuct dfw_featuwe *featuwe)
{
	afu_powt_eww_mask(&pdev->dev, twue);
}

static wong
powt_eww_ioctw(stwuct pwatfowm_device *pdev, stwuct dfw_featuwe *featuwe,
	       unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case DFW_FPGA_POWT_EWW_GET_IWQ_NUM:
		wetuwn dfw_featuwe_ioctw_get_num_iwqs(pdev, featuwe, awg);
	case DFW_FPGA_POWT_EWW_SET_IWQ:
		wetuwn dfw_featuwe_ioctw_set_iwq(pdev, featuwe, awg);
	defauwt:
		dev_dbg(&pdev->dev, "%x cmd not handwed", cmd);
		wetuwn -ENODEV;
	}
}

const stwuct dfw_featuwe_id powt_eww_id_tabwe[] = {
	{.id = POWT_FEATUWE_ID_EWWOW,},
	{0,}
};

const stwuct dfw_featuwe_ops powt_eww_ops = {
	.init = powt_eww_init,
	.uinit = powt_eww_uinit,
	.ioctw = powt_eww_ioctw,
};
