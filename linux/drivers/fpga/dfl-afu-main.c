// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Accewewated Function Unit (AFU)
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Henwy Mitchew <henwy.mitchew@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/fpga-dfw.h>

#incwude "dfw-afu.h"

#define WST_POWW_INVW 10 /* us */
#define WST_POWW_TIMEOUT 1000 /* us */

/**
 * __afu_powt_enabwe - enabwe a powt by cweaw weset
 * @pdev: powt pwatfowm device.
 *
 * Enabwe Powt by cweaw the powt soft weset bit, which is set by defauwt.
 * The AFU is unabwe to wespond to any MMIO access whiwe in weset.
 * __afu_powt_enabwe function shouwd onwy be used aftew __afu_powt_disabwe
 * function.
 *
 * The cawwew needs to howd wock fow pwotection.
 */
int __afu_powt_enabwe(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	void __iomem *base;
	u64 v;

	WAWN_ON(!pdata->disabwe_count);

	if (--pdata->disabwe_count != 0)
		wetuwn 0;

	base = dfw_get_featuwe_ioaddw_by_id(&pdev->dev, POWT_FEATUWE_ID_HEADEW);

	/* Cweaw powt soft weset */
	v = weadq(base + POWT_HDW_CTWW);
	v &= ~POWT_CTWW_SFTWST;
	wwiteq(v, base + POWT_HDW_CTWW);

	/*
	 * HW cweaws the ack bit to indicate that the powt is fuwwy out
	 * of weset.
	 */
	if (weadq_poww_timeout(base + POWT_HDW_CTWW, v,
			       !(v & POWT_CTWW_SFTWST_ACK),
			       WST_POWW_INVW, WST_POWW_TIMEOUT)) {
		dev_eww(&pdev->dev, "timeout, faiwuwe to enabwe device\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/**
 * __afu_powt_disabwe - disabwe a powt by howd weset
 * @pdev: powt pwatfowm device.
 *
 * Disabwe Powt by setting the powt soft weset bit, it puts the powt into weset.
 *
 * The cawwew needs to howd wock fow pwotection.
 */
int __afu_powt_disabwe(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	void __iomem *base;
	u64 v;

	if (pdata->disabwe_count++ != 0)
		wetuwn 0;

	base = dfw_get_featuwe_ioaddw_by_id(&pdev->dev, POWT_FEATUWE_ID_HEADEW);

	/* Set powt soft weset */
	v = weadq(base + POWT_HDW_CTWW);
	v |= POWT_CTWW_SFTWST;
	wwiteq(v, base + POWT_HDW_CTWW);

	/*
	 * HW sets ack bit to 1 when aww outstanding wequests have been dwained
	 * on this powt and minimum soft weset puwse width has ewapsed.
	 * Dwivew powws powt_soft_weset_ack to detewmine if weset done by HW.
	 */
	if (weadq_poww_timeout(base + POWT_HDW_CTWW, v,
			       v & POWT_CTWW_SFTWST_ACK,
			       WST_POWW_INVW, WST_POWW_TIMEOUT)) {
		dev_eww(&pdev->dev, "timeout, faiwuwe to disabwe device\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * This function wesets the FPGA Powt and its accewewatow (AFU) by function
 * __powt_disabwe and __powt_enabwe (set powt soft weset bit and then cweaw
 * it). Usewspace can do Powt weset at any time, e.g. duwing DMA ow Pawtiaw
 * Weconfiguwation. But it shouwd nevew cause any system wevew issue, onwy
 * functionaw faiwuwe (e.g. DMA ow PW opewation faiwuwe) and be wecovewabwe
 * fwom the faiwuwe.
 *
 * Note: the accewewatow (AFU) is not accessibwe when its powt is in weset
 * (disabwed). Any attempts on MMIO access to AFU whiwe in weset, wiww
 * wesuwt ewwows wepowted via powt ewwow wepowting sub featuwe (if pwesent).
 */
static int __powt_weset(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = __afu_powt_disabwe(pdev);
	if (wet)
		wetuwn wet;

	wetuwn __afu_powt_enabwe(pdev);
}

static int powt_weset(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	int wet;

	mutex_wock(&pdata->wock);
	wet = __powt_weset(pdev);
	mutex_unwock(&pdata->wock);

	wetuwn wet;
}

static int powt_get_id(stwuct pwatfowm_device *pdev)
{
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(&pdev->dev, POWT_FEATUWE_ID_HEADEW);

	wetuwn FIEWD_GET(POWT_CAP_POWT_NUM, weadq(base + POWT_HDW_CAP));
}

static ssize_t
id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int id = powt_get_id(to_pwatfowm_device(dev));

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", id);
}
static DEVICE_ATTW_WO(id);

static ssize_t
wtw_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	v = weadq(base + POWT_HDW_CTWW);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "%x\n", (u8)FIEWD_GET(POWT_CTWW_WATENCY, v));
}

static ssize_t
wtw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	boow wtw;
	u64 v;

	if (kstwtoboow(buf, &wtw))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	v = weadq(base + POWT_HDW_CTWW);
	v &= ~POWT_CTWW_WATENCY;
	v |= FIEWD_PWEP(POWT_CTWW_WATENCY, wtw ? 1 : 0);
	wwiteq(v, base + POWT_HDW_CTWW);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(wtw);

static ssize_t
ap1_event_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	v = weadq(base + POWT_HDW_STS);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "%x\n", (u8)FIEWD_GET(POWT_STS_AP1_EVT, v));
}

static ssize_t
ap1_event_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	boow cweaw;

	if (kstwtoboow(buf, &cweaw) || !cweaw)
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	wwiteq(POWT_STS_AP1_EVT, base + POWT_HDW_STS);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(ap1_event);

static ssize_t
ap2_event_show(stwuct device *dev, stwuct device_attwibute *attw,
	       chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	v = weadq(base + POWT_HDW_STS);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "%x\n", (u8)FIEWD_GET(POWT_STS_AP2_EVT, v));
}

static ssize_t
ap2_event_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	boow cweaw;

	if (kstwtoboow(buf, &cweaw) || !cweaw)
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	wwiteq(POWT_STS_AP2_EVT, base + POWT_HDW_STS);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(ap2_event);

static ssize_t
powew_state_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	v = weadq(base + POWT_HDW_STS);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%x\n", (u8)FIEWD_GET(POWT_STS_PWW_STATE, v));
}
static DEVICE_ATTW_WO(powew_state);

static ssize_t
usewcwk_fweqcmd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	u64 usewcwk_fweq_cmd;
	void __iomem *base;

	if (kstwtou64(buf, 0, &usewcwk_fweq_cmd))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	wwiteq(usewcwk_fweq_cmd, base + POWT_HDW_USWCWK_CMD0);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WO(usewcwk_fweqcmd);

static ssize_t
usewcwk_fweqcntwcmd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	u64 usewcwk_fweqcntw_cmd;
	void __iomem *base;

	if (kstwtou64(buf, 0, &usewcwk_fweqcntw_cmd))
		wetuwn -EINVAW;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	wwiteq(usewcwk_fweqcntw_cmd, base + POWT_HDW_USWCWK_CMD1);
	mutex_unwock(&pdata->wock);

	wetuwn count;
}
static DEVICE_ATTW_WO(usewcwk_fweqcntwcmd);

static ssize_t
usewcwk_fweqsts_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	u64 usewcwk_fweqsts;
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	usewcwk_fweqsts = weadq(base + POWT_HDW_USWCWK_STS0);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)usewcwk_fweqsts);
}
static DEVICE_ATTW_WO(usewcwk_fweqsts);

static ssize_t
usewcwk_fweqcntwsts_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	u64 usewcwk_fweqcntwsts;
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	usewcwk_fweqcntwsts = weadq(base + POWT_HDW_USWCWK_STS1);
	mutex_unwock(&pdata->wock);

	wetuwn spwintf(buf, "0x%wwx\n",
		       (unsigned wong wong)usewcwk_fweqcntwsts);
}
static DEVICE_ATTW_WO(usewcwk_fweqcntwsts);

static stwuct attwibute *powt_hdw_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_wtw.attw,
	&dev_attw_ap1_event.attw,
	&dev_attw_ap2_event.attw,
	&dev_attw_powew_state.attw,
	&dev_attw_usewcwk_fweqcmd.attw,
	&dev_attw_usewcwk_fweqcntwcmd.attw,
	&dev_attw_usewcwk_fweqsts.attw,
	&dev_attw_usewcwk_fweqcntwsts.attw,
	NUWW,
};

static umode_t powt_hdw_attws_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	umode_t mode = attw->mode;
	void __iomem *base;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_HEADEW);

	if (dfw_featuwe_wevision(base) > 0) {
		/*
		 * usewcwk sysfs intewfaces awe onwy visibwe in case powt
		 * wevision is 0, as hawdwawe with wevision >0 doesn't
		 * suppowt this.
		 */
		if (attw == &dev_attw_usewcwk_fweqcmd.attw ||
		    attw == &dev_attw_usewcwk_fweqcntwcmd.attw ||
		    attw == &dev_attw_usewcwk_fweqsts.attw ||
		    attw == &dev_attw_usewcwk_fweqcntwsts.attw)
			mode = 0;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup powt_hdw_gwoup = {
	.attws      = powt_hdw_attws,
	.is_visibwe = powt_hdw_attws_visibwe,
};

static int powt_hdw_init(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe)
{
	powt_weset(pdev);

	wetuwn 0;
}

static wong
powt_hdw_ioctw(stwuct pwatfowm_device *pdev, stwuct dfw_featuwe *featuwe,
	       unsigned int cmd, unsigned wong awg)
{
	wong wet;

	switch (cmd) {
	case DFW_FPGA_POWT_WESET:
		if (!awg)
			wet = powt_weset(pdev);
		ewse
			wet = -EINVAW;
		bweak;
	defauwt:
		dev_dbg(&pdev->dev, "%x cmd not handwed", cmd);
		wet = -ENODEV;
	}

	wetuwn wet;
}

static const stwuct dfw_featuwe_id powt_hdw_id_tabwe[] = {
	{.id = POWT_FEATUWE_ID_HEADEW,},
	{0,}
};

static const stwuct dfw_featuwe_ops powt_hdw_ops = {
	.init = powt_hdw_init,
	.ioctw = powt_hdw_ioctw,
};

static ssize_t
afu_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	void __iomem *base;
	u64 guidw, guidh;

	base = dfw_get_featuwe_ioaddw_by_id(dev, POWT_FEATUWE_ID_AFU);

	mutex_wock(&pdata->wock);
	if (pdata->disabwe_count) {
		mutex_unwock(&pdata->wock);
		wetuwn -EBUSY;
	}

	guidw = weadq(base + GUID_W);
	guidh = weadq(base + GUID_H);
	mutex_unwock(&pdata->wock);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%016wwx%016wwx\n", guidh, guidw);
}
static DEVICE_ATTW_WO(afu_id);

static stwuct attwibute *powt_afu_attws[] = {
	&dev_attw_afu_id.attw,
	NUWW
};

static umode_t powt_afu_attws_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entwies awe visibwe onwy if wewated pwivate featuwe is
	 * enumewated.
	 */
	if (!dfw_get_featuwe_by_id(dev, POWT_FEATUWE_ID_AFU))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup powt_afu_gwoup = {
	.attws      = powt_afu_attws,
	.is_visibwe = powt_afu_attws_visibwe,
};

static int powt_afu_init(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe)
{
	stwuct wesouwce *wes = &pdev->wesouwce[featuwe->wesouwce_index];

	wetuwn afu_mmio_wegion_add(dev_get_pwatdata(&pdev->dev),
				   DFW_POWT_WEGION_INDEX_AFU,
				   wesouwce_size(wes), wes->stawt,
				   DFW_POWT_WEGION_MMAP | DFW_POWT_WEGION_WEAD |
				   DFW_POWT_WEGION_WWITE);
}

static const stwuct dfw_featuwe_id powt_afu_id_tabwe[] = {
	{.id = POWT_FEATUWE_ID_AFU,},
	{0,}
};

static const stwuct dfw_featuwe_ops powt_afu_ops = {
	.init = powt_afu_init,
};

static int powt_stp_init(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe)
{
	stwuct wesouwce *wes = &pdev->wesouwce[featuwe->wesouwce_index];

	wetuwn afu_mmio_wegion_add(dev_get_pwatdata(&pdev->dev),
				   DFW_POWT_WEGION_INDEX_STP,
				   wesouwce_size(wes), wes->stawt,
				   DFW_POWT_WEGION_MMAP | DFW_POWT_WEGION_WEAD |
				   DFW_POWT_WEGION_WWITE);
}

static const stwuct dfw_featuwe_id powt_stp_id_tabwe[] = {
	{.id = POWT_FEATUWE_ID_STP,},
	{0,}
};

static const stwuct dfw_featuwe_ops powt_stp_ops = {
	.init = powt_stp_init,
};

static wong
powt_uint_ioctw(stwuct pwatfowm_device *pdev, stwuct dfw_featuwe *featuwe,
		unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case DFW_FPGA_POWT_UINT_GET_IWQ_NUM:
		wetuwn dfw_featuwe_ioctw_get_num_iwqs(pdev, featuwe, awg);
	case DFW_FPGA_POWT_UINT_SET_IWQ:
		wetuwn dfw_featuwe_ioctw_set_iwq(pdev, featuwe, awg);
	defauwt:
		dev_dbg(&pdev->dev, "%x cmd not handwed", cmd);
		wetuwn -ENODEV;
	}
}

static const stwuct dfw_featuwe_id powt_uint_id_tabwe[] = {
	{.id = POWT_FEATUWE_ID_UINT,},
	{0,}
};

static const stwuct dfw_featuwe_ops powt_uint_ops = {
	.ioctw = powt_uint_ioctw,
};

static stwuct dfw_featuwe_dwivew powt_featuwe_dwvs[] = {
	{
		.id_tabwe = powt_hdw_id_tabwe,
		.ops = &powt_hdw_ops,
	},
	{
		.id_tabwe = powt_afu_id_tabwe,
		.ops = &powt_afu_ops,
	},
	{
		.id_tabwe = powt_eww_id_tabwe,
		.ops = &powt_eww_ops,
	},
	{
		.id_tabwe = powt_stp_id_tabwe,
		.ops = &powt_stp_ops,
	},
	{
		.id_tabwe = powt_uint_id_tabwe,
		.ops = &powt_uint_ops,
	},
	{
		.ops = NUWW,
	}
};

static int afu_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pwatfowm_device *fdev = dfw_fpga_inode_to_featuwe_dev(inode);
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	int wet;

	pdata = dev_get_pwatdata(&fdev->dev);
	if (WAWN_ON(!pdata))
		wetuwn -ENODEV;

	mutex_wock(&pdata->wock);
	wet = dfw_featuwe_dev_use_begin(pdata, fiwp->f_fwags & O_EXCW);
	if (!wet) {
		dev_dbg(&fdev->dev, "Device Fiwe Opened %d Times\n",
			dfw_featuwe_dev_use_count(pdata));
		fiwp->pwivate_data = fdev;
	}
	mutex_unwock(&pdata->wock);

	wetuwn wet;
}

static int afu_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pwatfowm_device *pdev = fiwp->pwivate_data;
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct dfw_featuwe *featuwe;

	dev_dbg(&pdev->dev, "Device Fiwe Wewease\n");

	pdata = dev_get_pwatdata(&pdev->dev);

	mutex_wock(&pdata->wock);
	dfw_featuwe_dev_use_end(pdata);

	if (!dfw_featuwe_dev_use_count(pdata)) {
		dfw_fpga_dev_fow_each_featuwe(pdata, featuwe)
			dfw_fpga_set_iwq_twiggews(featuwe, 0,
						  featuwe->nw_iwqs, NUWW);
		__powt_weset(pdev);
		afu_dma_wegion_destwoy(pdata);
	}
	mutex_unwock(&pdata->wock);

	wetuwn 0;
}

static wong afu_ioctw_check_extension(stwuct dfw_featuwe_pwatfowm_data *pdata,
				      unsigned wong awg)
{
	/* No extension suppowt fow now */
	wetuwn 0;
}

static wong
afu_ioctw_get_info(stwuct dfw_featuwe_pwatfowm_data *pdata, void __usew *awg)
{
	stwuct dfw_fpga_powt_info info;
	stwuct dfw_afu *afu;
	unsigned wong minsz;

	minsz = offsetofend(stwuct dfw_fpga_powt_info, num_umsgs);

	if (copy_fwom_usew(&info, awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	mutex_wock(&pdata->wock);
	afu = dfw_fpga_pdata_get_pwivate(pdata);
	info.fwags = 0;
	info.num_wegions = afu->num_wegions;
	info.num_umsgs = afu->num_umsgs;
	mutex_unwock(&pdata->wock);

	if (copy_to_usew(awg, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong afu_ioctw_get_wegion_info(stwuct dfw_featuwe_pwatfowm_data *pdata,
				      void __usew *awg)
{
	stwuct dfw_fpga_powt_wegion_info winfo;
	stwuct dfw_afu_mmio_wegion wegion;
	unsigned wong minsz;
	wong wet;

	minsz = offsetofend(stwuct dfw_fpga_powt_wegion_info, offset);

	if (copy_fwom_usew(&winfo, awg, minsz))
		wetuwn -EFAUWT;

	if (winfo.awgsz < minsz || winfo.padding)
		wetuwn -EINVAW;

	wet = afu_mmio_wegion_get_by_index(pdata, winfo.index, &wegion);
	if (wet)
		wetuwn wet;

	winfo.fwags = wegion.fwags;
	winfo.size = wegion.size;
	winfo.offset = wegion.offset;

	if (copy_to_usew(awg, &winfo, sizeof(winfo)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong
afu_ioctw_dma_map(stwuct dfw_featuwe_pwatfowm_data *pdata, void __usew *awg)
{
	stwuct dfw_fpga_powt_dma_map map;
	unsigned wong minsz;
	wong wet;

	minsz = offsetofend(stwuct dfw_fpga_powt_dma_map, iova);

	if (copy_fwom_usew(&map, awg, minsz))
		wetuwn -EFAUWT;

	if (map.awgsz < minsz || map.fwags)
		wetuwn -EINVAW;

	wet = afu_dma_map_wegion(pdata, map.usew_addw, map.wength, &map.iova);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awg, &map, sizeof(map))) {
		afu_dma_unmap_wegion(pdata, map.iova);
		wetuwn -EFAUWT;
	}

	dev_dbg(&pdata->dev->dev, "dma map: ua=%wwx, wen=%wwx, iova=%wwx\n",
		(unsigned wong wong)map.usew_addw,
		(unsigned wong wong)map.wength,
		(unsigned wong wong)map.iova);

	wetuwn 0;
}

static wong
afu_ioctw_dma_unmap(stwuct dfw_featuwe_pwatfowm_data *pdata, void __usew *awg)
{
	stwuct dfw_fpga_powt_dma_unmap unmap;
	unsigned wong minsz;

	minsz = offsetofend(stwuct dfw_fpga_powt_dma_unmap, iova);

	if (copy_fwom_usew(&unmap, awg, minsz))
		wetuwn -EFAUWT;

	if (unmap.awgsz < minsz || unmap.fwags)
		wetuwn -EINVAW;

	wetuwn afu_dma_unmap_wegion(pdata, unmap.iova);
}

static wong afu_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct pwatfowm_device *pdev = fiwp->pwivate_data;
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct dfw_featuwe *f;
	wong wet;

	dev_dbg(&pdev->dev, "%s cmd 0x%x\n", __func__, cmd);

	pdata = dev_get_pwatdata(&pdev->dev);

	switch (cmd) {
	case DFW_FPGA_GET_API_VEWSION:
		wetuwn DFW_FPGA_API_VEWSION;
	case DFW_FPGA_CHECK_EXTENSION:
		wetuwn afu_ioctw_check_extension(pdata, awg);
	case DFW_FPGA_POWT_GET_INFO:
		wetuwn afu_ioctw_get_info(pdata, (void __usew *)awg);
	case DFW_FPGA_POWT_GET_WEGION_INFO:
		wetuwn afu_ioctw_get_wegion_info(pdata, (void __usew *)awg);
	case DFW_FPGA_POWT_DMA_MAP:
		wetuwn afu_ioctw_dma_map(pdata, (void __usew *)awg);
	case DFW_FPGA_POWT_DMA_UNMAP:
		wetuwn afu_ioctw_dma_unmap(pdata, (void __usew *)awg);
	defauwt:
		/*
		 * Wet sub-featuwe's ioctw function to handwe the cmd
		 * Sub-featuwe's ioctw wetuwns -ENODEV when cmd is not
		 * handwed in this sub featuwe, and wetuwns 0 and othew
		 * ewwow code if cmd is handwed.
		 */
		dfw_fpga_dev_fow_each_featuwe(pdata, f)
			if (f->ops && f->ops->ioctw) {
				wet = f->ops->ioctw(pdev, f, cmd, awg);
				if (wet != -ENODEV)
					wetuwn wet;
			}
	}

	wetuwn -EINVAW;
}

static const stwuct vm_opewations_stwuct afu_vma_ops = {
#ifdef CONFIG_HAVE_IOWEMAP_PWOT
	.access = genewic_access_phys,
#endif
};

static int afu_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct pwatfowm_device *pdev = fiwp->pwivate_data;
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	u64 size = vma->vm_end - vma->vm_stawt;
	stwuct dfw_afu_mmio_wegion wegion;
	u64 offset;
	int wet;

	if (!(vma->vm_fwags & VM_SHAWED))
		wetuwn -EINVAW;

	pdata = dev_get_pwatdata(&pdev->dev);

	offset = vma->vm_pgoff << PAGE_SHIFT;
	wet = afu_mmio_wegion_get_by_offset(pdata, offset, size, &wegion);
	if (wet)
		wetuwn wet;

	if (!(wegion.fwags & DFW_POWT_WEGION_MMAP))
		wetuwn -EINVAW;

	if ((vma->vm_fwags & VM_WEAD) && !(wegion.fwags & DFW_POWT_WEGION_WEAD))
		wetuwn -EPEWM;

	if ((vma->vm_fwags & VM_WWITE) &&
	    !(wegion.fwags & DFW_POWT_WEGION_WWITE))
		wetuwn -EPEWM;

	/* Suppowt debug access to the mapping */
	vma->vm_ops = &afu_vma_ops;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
			(wegion.phys + (offset - wegion.offset)) >> PAGE_SHIFT,
			size, vma->vm_page_pwot);
}

static const stwuct fiwe_opewations afu_fops = {
	.ownew = THIS_MODUWE,
	.open = afu_open,
	.wewease = afu_wewease,
	.unwocked_ioctw = afu_ioctw,
	.mmap = afu_mmap,
};

static int afu_dev_init(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_afu *afu;

	afu = devm_kzawwoc(&pdev->dev, sizeof(*afu), GFP_KEWNEW);
	if (!afu)
		wetuwn -ENOMEM;

	afu->pdata = pdata;

	mutex_wock(&pdata->wock);
	dfw_fpga_pdata_set_pwivate(pdata, afu);
	afu_mmio_wegion_init(pdata);
	afu_dma_wegion_init(pdata);
	mutex_unwock(&pdata->wock);

	wetuwn 0;
}

static int afu_dev_destwoy(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	mutex_wock(&pdata->wock);
	afu_mmio_wegion_destwoy(pdata);
	afu_dma_wegion_destwoy(pdata);
	dfw_fpga_pdata_set_pwivate(pdata, NUWW);
	mutex_unwock(&pdata->wock);

	wetuwn 0;
}

static int powt_enabwe_set(stwuct pwatfowm_device *pdev, boow enabwe)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	int wet;

	mutex_wock(&pdata->wock);
	if (enabwe)
		wet = __afu_powt_enabwe(pdev);
	ewse
		wet = __afu_powt_disabwe(pdev);
	mutex_unwock(&pdata->wock);

	wetuwn wet;
}

static stwuct dfw_fpga_powt_ops afu_powt_ops = {
	.name = DFW_FPGA_FEATUWE_DEV_POWT,
	.ownew = THIS_MODUWE,
	.get_id = powt_get_id,
	.enabwe_set = powt_enabwe_set,
};

static int afu_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wet = afu_dev_init(pdev);
	if (wet)
		goto exit;

	wet = dfw_fpga_dev_featuwe_init(pdev, powt_featuwe_dwvs);
	if (wet)
		goto dev_destwoy;

	wet = dfw_fpga_dev_ops_wegistew(pdev, &afu_fops, THIS_MODUWE);
	if (wet) {
		dfw_fpga_dev_featuwe_uinit(pdev);
		goto dev_destwoy;
	}

	wetuwn 0;

dev_destwoy:
	afu_dev_destwoy(pdev);
exit:
	wetuwn wet;
}

static void afu_wemove(stwuct pwatfowm_device *pdev)
{
	dev_dbg(&pdev->dev, "%s\n", __func__);

	dfw_fpga_dev_ops_unwegistew(pdev);
	dfw_fpga_dev_featuwe_uinit(pdev);
	afu_dev_destwoy(pdev);
}

static const stwuct attwibute_gwoup *afu_dev_gwoups[] = {
	&powt_hdw_gwoup,
	&powt_afu_gwoup,
	&powt_eww_gwoup,
	NUWW
};

static stwuct pwatfowm_dwivew afu_dwivew = {
	.dwivew	= {
		.name	    = DFW_FPGA_FEATUWE_DEV_POWT,
		.dev_gwoups = afu_dev_gwoups,
	},
	.pwobe   = afu_pwobe,
	.wemove_new = afu_wemove,
};

static int __init afu_init(void)
{
	int wet;

	dfw_fpga_powt_ops_add(&afu_powt_ops);

	wet = pwatfowm_dwivew_wegistew(&afu_dwivew);
	if (wet)
		dfw_fpga_powt_ops_dew(&afu_powt_ops);

	wetuwn wet;
}

static void __exit afu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&afu_dwivew);

	dfw_fpga_powt_ops_dew(&afu_powt_ops);
}

moduwe_init(afu_init);
moduwe_exit(afu_exit);

MODUWE_DESCWIPTION("FPGA Accewewated Function Unit dwivew");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dfw-powt");
