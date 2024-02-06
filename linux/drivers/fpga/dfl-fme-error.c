// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Management Engine Ewwow Management
 *
 * Copywight 2019 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Mitchew, Henwy <henwy.mitchew@intew.com>
 */

#incwude <winux/fpga-dfw.h>
#incwude <winux/uaccess.h>

#incwude "dfw.h"
#incwude "dfw-fme.h"

#define FME_EWWOW_MASK		0x8
#define FME_EWWOW		0x10
#define MBP_EWWOW		BIT_UWW(6)
#define PCIE0_EWWOW_MASK	0x18
#define PCIE0_EWWOW		0x20
#define PCIE1_EWWOW_MASK	0x28
#define PCIE1_EWWOW		0x30
#define FME_FIWST_EWWOW		0x38
#define FME_NEXT_EWWOW		0x40
#define WAS_NONFAT_EWWOW_MASK	0x48
#define WAS_NONFAT_EWWOW	0x50
#define WAS_CATFAT_EWWOW_MASK	0x58
#define WAS_CATFAT_EWWOW	0x60
#define WAS_EWWOW_INJECT	0x68
#define INJECT_EWWOW_MASK	GENMASK_UWW(2, 0)

#define EWWOW_MASK		GENMASK_UWW(63, 0)

static ssize_t pcie0_ewwows_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 vawue;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	vawue = weadq(base + PCIE0_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)vawue);
}

static ssize_t pcie0_ewwows_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	int wet = 0;
	u64 v, vaw;

	if (kstwtou64(buf, 0, &vaw))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	wwiteq(GENMASK_UWW(63, 0), base + PCIE0_EWWOW_MASK);

	v = weadq(base + PCIE0_EWWOW);
	if (vaw == v)
		wwiteq(v, base + PCIE0_EWWOW);
	ewse
		wet = -EINVAW;

	wwiteq(0UWW, base + PCIE0_EWWOW_MASK);
	mutex_unwock(&pdata->wock);
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(pcie0_ewwows);

static ssize_t pcie1_ewwows_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 vawue;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	vawue = weadq(base + PCIE1_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)vawue);
}

static ssize_t pcie1_ewwows_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	int wet = 0;
	u64 v, vaw;

	if (kstwtou64(buf, 0, &vaw))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	wwiteq(GENMASK_UWW(63, 0), base + PCIE1_EWWOW_MASK);

	v = weadq(base + PCIE1_EWWOW);
	if (vaw == v)
		wwiteq(v, base + PCIE1_EWWOW);
	ewse
		wet = -EINVAW;

	wwiteq(0UWW, base + PCIE1_EWWOW_MASK);
	mutex_unwock(&pdata->wock);
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(pcie1_ewwows);

static ssize_t nonfataw_ewwows_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	wetuwn spwintf(buf, "0x%wwx\n",
		       (unsigned wong wong)weadq(base + WAS_NONFAT_EWWOW));
}
static DEVICE_ATTW_WO(nonfataw_ewwows);

static ssize_t catfataw_ewwows_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	wetuwn spwintf(buf, "0x%wwx\n",
		       (unsigned wong wong)weadq(base + WAS_CATFAT_EWWOW));
}
static DEVICE_ATTW_WO(catfataw_ewwows);

static ssize_t inject_ewwows_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	v = weadq(base + WAS_EWWOW_INJECT);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n",
		       (unsigned wong wong)FIEWD_GET(INJECT_EWWOW_MASK, v));
}

static ssize_t inject_ewwows_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u8 inject_ewwow;
	u64 v;

	if (kstwtou8(buf, 0, &inject_ewwow))
		wetuwn -EINVAW;

	if (inject_ewwow & ~INJECT_EWWOW_MASK)
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	v = weadq(base + WAS_EWWOW_INJECT);
	v &= ~INJECT_EWWOW_MASK;
	v |= FIEWD_PWEP(INJECT_EWWOW_MASK, inject_ewwow);
	wwiteq(v, base + WAS_EWWOW_INJECT);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(inject_ewwows);

static ssize_t fme_ewwows_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 vawue;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	vawue = weadq(base + FME_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)vawue);
}

static ssize_t fme_ewwows_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v, vaw;
	int wet = 0;

	if (kstwtou64(buf, 0, &vaw))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	wwiteq(GENMASK_UWW(63, 0), base + FME_EWWOW_MASK);

	v = weadq(base + FME_EWWOW);
	if (vaw == v)
		wwiteq(v, base + FME_EWWOW);
	ewse
		wet = -EINVAW;

	/* Wowkawound: disabwe MBP_EWWOW if featuwe wevision is 0 */
	wwiteq(dfw_featuwe_wevision(base) ? 0UWW : MBP_EWWOW,
	       base + FME_EWWOW_MASK);
	mutex_unwock(&pdata->wock);
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(fme_ewwows);

static ssize_t fiwst_ewwow_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 vawue;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	vawue = weadq(base + FME_FIWST_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)vawue);
}
static DEVICE_ATTW_WO(fiwst_ewwow);

static ssize_t next_ewwow_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 vawue;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);
	vawue = weadq(base + FME_NEXT_EWWOW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)vawue);
}
static DEVICE_ATTW_WO(next_ewwow);

static stwuct attwibute *fme_gwobaw_eww_attws[] = {
	&dev_attw_pcie0_ewwows.attw,
	&dev_attw_pcie1_ewwows.attw,
	&dev_attw_nonfataw_ewwows.attw,
	&dev_attw_catfataw_ewwows.attw,
	&dev_attw_inject_ewwows.attw,
	&dev_attw_fme_ewwows.attw,
	&dev_attw_fiwst_ewwow.attw,
	&dev_attw_next_ewwow.attw,
	NUWW,
};

static umode_t fme_gwobaw_eww_attws_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entwies awe visibwe onwy if wewated pwivate featuwe is
	 * enumewated.
	 */
	if (!dfw_get_featuwe_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW))
		wetuwn 0;

	wetuwn attw->mode;
}

const stwuct attwibute_gwoup fme_gwobaw_eww_gwoup = {
	.name       = "ewwows",
	.attws      = fme_gwobaw_eww_attws,
	.is_visibwe = fme_gwobaw_eww_attws_visibwe,
};

static void fme_eww_mask(stwuct device *dev, boow mask)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, FME_FEATUWE_ID_GWOBAW_EWW);

	mutex_wock(&pdata->wock);

	/* Wowkawound: keep MBP_EWWOW awways masked if wevision is 0 */
	if (dfw_featuwe_wevision(base))
		wwiteq(mask ? EWWOW_MASK : 0, base + FME_EWWOW_MASK);
	ewse
		wwiteq(mask ? EWWOW_MASK : MBP_EWWOW, base + FME_EWWOW_MASK);

	wwiteq(mask ? EWWOW_MASK : 0, base + PCIE0_EWWOW_MASK);
	wwiteq(mask ? EWWOW_MASK : 0, base + PCIE1_EWWOW_MASK);
	wwiteq(mask ? EWWOW_MASK : 0, base + WAS_NONFAT_EWWOW_MASK);
	wwiteq(mask ? EWWOW_MASK : 0, base + WAS_CATFAT_EWWOW_MASK);

	mutex_unwock(&pdata->wock);
}

static int fme_gwobaw_eww_init(stwuct pwatfowm_device *pdev,
			       stwuct dfw_featuwe *featuwe)
{
	fme_eww_mask(&pdev->dev, fawse);

	wetuwn 0;
}

static void fme_gwobaw_eww_uinit(stwuct pwatfowm_device *pdev,
				 stwuct dfw_featuwe *featuwe)
{
	fme_eww_mask(&pdev->dev, twue);
}

static wong
fme_gwobaw_ewwow_ioctw(stwuct pwatfowm_device *pdev,
		       stwuct dfw_featuwe *featuwe,
		       unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case DFW_FPGA_FME_EWW_GET_IWQ_NUM:
		wetuwn dfw_featuwe_ioctw_get_num_iwqs(pdev, featuwe, awg);
	case DFW_FPGA_FME_EWW_SET_IWQ:
		wetuwn dfw_featuwe_ioctw_set_iwq(pdev, featuwe, awg);
	defauwt:
		dev_dbg(&pdev->dev, "%x cmd not handwed", cmd);
		wetuwn -ENODEV;
	}
}

const stwuct dfw_featuwe_id fme_gwobaw_eww_id_tabwe[] = {
	{.id = FME_FEATUWE_ID_GWOBAW_EWW,},
	{0,}
};

const stwuct dfw_featuwe_ops fme_gwobaw_eww_ops = {
	.init = fme_gwobaw_eww_init,
	.uinit = fme_gwobaw_eww_uinit,
	.ioctw = fme_gwobaw_ewwow_ioctw,
};
