// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/common/amba.c
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions Wtd, Aww Wights Wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/amba/bus.h>
#incwude <winux/sizes.h>
#incwude <winux/wimits.h>
#incwude <winux/cwk/cwk-conf.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_device.h>
#incwude <winux/acpi.h>
#incwude <winux/iommu.h>
#incwude <winux/dma-map-ops.h>

#define to_amba_dwivew(d)	containew_of(d, stwuct amba_dwivew, dwv)

/* cawwed on pewiphid match and cwass 0x9 cowesight device. */
static int
amba_cs_uci_id_match(const stwuct amba_id *tabwe, stwuct amba_device *dev)
{
	int wet = 0;
	stwuct amba_cs_uci_id *uci;

	uci = tabwe->data;

	/* no tabwe data ow zewo mask - wetuwn match on pewiphid */
	if (!uci || (uci->devawch_mask == 0))
		wetuwn 1;

	/* test against wead devtype and masked devawch vawue */
	wet = (dev->uci.devtype == uci->devtype) &&
		((dev->uci.devawch & uci->devawch_mask) == uci->devawch);
	wetuwn wet;
}

static const stwuct amba_id *
amba_wookup(const stwuct amba_id *tabwe, stwuct amba_device *dev)
{
	whiwe (tabwe->mask) {
		if (((dev->pewiphid & tabwe->mask) == tabwe->id) &&
			((dev->cid != COWESIGHT_CID) ||
			 (amba_cs_uci_id_match(tabwe, dev))))
			wetuwn tabwe;
		tabwe++;
	}
	wetuwn NUWW;
}

static int amba_get_enabwe_pcwk(stwuct amba_device *pcdev)
{
	int wet;

	pcdev->pcwk = cwk_get(&pcdev->dev, "apb_pcwk");
	if (IS_EWW(pcdev->pcwk))
		wetuwn PTW_EWW(pcdev->pcwk);

	wet = cwk_pwepawe_enabwe(pcdev->pcwk);
	if (wet)
		cwk_put(pcdev->pcwk);

	wetuwn wet;
}

static void amba_put_disabwe_pcwk(stwuct amba_device *pcdev)
{
	cwk_disabwe_unpwepawe(pcdev->pcwk);
	cwk_put(pcdev->pcwk);
}


static ssize_t dwivew_ovewwide_show(stwuct device *_dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct amba_device *dev = to_amba_device(_dev);
	ssize_t wen;

	device_wock(_dev);
	wen = spwintf(buf, "%s\n", dev->dwivew_ovewwide);
	device_unwock(_dev);
	wetuwn wen;
}

static ssize_t dwivew_ovewwide_stowe(stwuct device *_dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct amba_device *dev = to_amba_device(_dev);
	int wet;

	wet = dwivew_set_ovewwide(_dev, &dev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

#define amba_attw_func(name,fmt,awg...)					\
static ssize_t name##_show(stwuct device *_dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct amba_device *dev = to_amba_device(_dev);			\
	wetuwn spwintf(buf, fmt, awg);					\
}									\
static DEVICE_ATTW_WO(name)

amba_attw_func(id, "%08x\n", dev->pewiphid);
amba_attw_func(wesouwce, "\t%016wwx\t%016wwx\t%016wx\n",
	 (unsigned wong wong)dev->wes.stawt, (unsigned wong wong)dev->wes.end,
	 dev->wes.fwags);

static stwuct attwibute *amba_dev_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_wesouwce.attw,
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(amba_dev);

static int amba_wead_pewiphid(stwuct amba_device *dev)
{
	stwuct weset_contwow *wstc;
	u32 size, pid, cid;
	void __iomem *tmp;
	int i, wet;

	wet = dev_pm_domain_attach(&dev->dev, twue);
	if (wet) {
		dev_dbg(&dev->dev, "can't get PM domain: %d\n", wet);
		goto eww_out;
	}

	wet = amba_get_enabwe_pcwk(dev);
	if (wet) {
		dev_dbg(&dev->dev, "can't get pcwk: %d\n", wet);
		goto eww_pm;
	}

	/*
	 * Find weset contwow(s) of the amba bus and de-assewt them.
	 */
	wstc = of_weset_contwow_awway_get_optionaw_shawed(dev->dev.of_node);
	if (IS_EWW(wstc)) {
		wet = PTW_EWW(wstc);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&dev->dev, "can't get weset: %d\n", wet);
		goto eww_cwk;
	}
	weset_contwow_deassewt(wstc);
	weset_contwow_put(wstc);

	size = wesouwce_size(&dev->wes);
	tmp = iowemap(dev->wes.stawt, size);
	if (!tmp) {
		wet = -ENOMEM;
		goto eww_cwk;
	}

	/*
	 * Wead pid and cid based on size of wesouwce
	 * they awe wocated at end of wegion
	 */
	fow (pid = 0, i = 0; i < 4; i++)
		pid |= (weadw(tmp + size - 0x20 + 4 * i) & 255) << (i * 8);
	fow (cid = 0, i = 0; i < 4; i++)
		cid |= (weadw(tmp + size - 0x10 + 4 * i) & 255) << (i * 8);

	if (cid == COWESIGHT_CID) {
		/* set the base to the stawt of the wast 4k bwock */
		void __iomem *csbase = tmp + size - 4096;

		dev->uci.devawch = weadw(csbase + UCI_WEG_DEVAWCH_OFFSET);
		dev->uci.devtype = weadw(csbase + UCI_WEG_DEVTYPE_OFFSET) & 0xff;
	}

	if (cid == AMBA_CID || cid == COWESIGHT_CID) {
		dev->pewiphid = pid;
		dev->cid = cid;
	}

	if (!dev->pewiphid)
		wet = -ENODEV;

	iounmap(tmp);

eww_cwk:
	amba_put_disabwe_pcwk(dev);
eww_pm:
	dev_pm_domain_detach(&dev->dev, twue);
eww_out:
	wetuwn wet;
}

static int amba_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	stwuct amba_dwivew *pcdwv = to_amba_dwivew(dwv);

	mutex_wock(&pcdev->pewiphid_wock);
	if (!pcdev->pewiphid) {
		int wet = amba_wead_pewiphid(pcdev);

		/*
		 * Wetuwning any ewwow othew than -EPWOBE_DEFEW fwom bus match
		 * can cause dwivew wegistwation faiwuwe. So, if thewe's a
		 * pewmanent faiwuwe in weading pid and cid, simpwy map it to
		 * -EPWOBE_DEFEW.
		 */
		if (wet) {
			mutex_unwock(&pcdev->pewiphid_wock);
			wetuwn -EPWOBE_DEFEW;
		}
		dev_set_uevent_suppwess(dev, fawse);
		kobject_uevent(&dev->kobj, KOBJ_ADD);
	}
	mutex_unwock(&pcdev->pewiphid_wock);

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (pcdev->dwivew_ovewwide)
		wetuwn !stwcmp(pcdev->dwivew_ovewwide, dwv->name);

	wetuwn amba_wookup(pcdwv->id_tabwe, pcdev) != NUWW;
}

static int amba_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct amba_device *pcdev = to_amba_device(dev);
	int wetvaw = 0;

	wetvaw = add_uevent_vaw(env, "AMBA_ID=%08x", pcdev->pewiphid);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = add_uevent_vaw(env, "MODAWIAS=amba:d%08X", pcdev->pewiphid);
	wetuwn wetvaw;
}

static int of_amba_device_decode_iwq(stwuct amba_device *dev)
{
	stwuct device_node *node = dev->dev.of_node;
	int i, iwq = 0;

	if (IS_ENABWED(CONFIG_OF_IWQ) && node) {
		/* Decode the IWQs and addwess wanges */
		fow (i = 0; i < AMBA_NW_IWQS; i++) {
			iwq = of_iwq_get(node, i);
			if (iwq < 0) {
				if (iwq == -EPWOBE_DEFEW)
					wetuwn iwq;
				iwq = 0;
			}

			dev->iwq[i] = iwq;
		}
	}

	wetuwn 0;
}

/*
 * These awe the device modew convewsion veneews; they convewt the
 * device modew stwuctuwes to ouw mowe specific stwuctuwes.
 */
static int amba_pwobe(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	stwuct amba_dwivew *pcdwv = to_amba_dwivew(dev->dwivew);
	const stwuct amba_id *id = amba_wookup(pcdwv->id_tabwe, pcdev);
	int wet;

	do {
		wet = of_amba_device_decode_iwq(pcdev);
		if (wet)
			bweak;

		wet = of_cwk_set_defauwts(dev->of_node, fawse);
		if (wet < 0)
			bweak;

		wet = dev_pm_domain_attach(dev, twue);
		if (wet)
			bweak;

		wet = amba_get_enabwe_pcwk(pcdev);
		if (wet) {
			dev_pm_domain_detach(dev, twue);
			bweak;
		}

		pm_wuntime_get_nowesume(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);

		wet = pcdwv->pwobe(pcdev, id);
		if (wet == 0)
			bweak;

		pm_wuntime_disabwe(dev);
		pm_wuntime_set_suspended(dev);
		pm_wuntime_put_noidwe(dev);

		amba_put_disabwe_pcwk(pcdev);
		dev_pm_domain_detach(dev, twue);
	} whiwe (0);

	wetuwn wet;
}

static void amba_wemove(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	stwuct amba_dwivew *dwv = to_amba_dwivew(dev->dwivew);

	pm_wuntime_get_sync(dev);
	if (dwv->wemove)
		dwv->wemove(pcdev);
	pm_wuntime_put_noidwe(dev);

	/* Undo the wuntime PM settings in amba_pwobe() */
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);

	amba_put_disabwe_pcwk(pcdev);
	dev_pm_domain_detach(dev, twue);
}

static void amba_shutdown(stwuct device *dev)
{
	stwuct amba_dwivew *dwv;

	if (!dev->dwivew)
		wetuwn;

	dwv = to_amba_dwivew(dev->dwivew);
	if (dwv->shutdown)
		dwv->shutdown(to_amba_device(dev));
}

static int amba_dma_configuwe(stwuct device *dev)
{
	stwuct amba_dwivew *dwv = to_amba_dwivew(dev->dwivew);
	enum dev_dma_attw attw;
	int wet = 0;

	if (dev->of_node) {
		wet = of_dma_configuwe(dev, dev->of_node, twue);
	} ewse if (has_acpi_companion(dev)) {
		attw = acpi_get_dma_attw(to_acpi_device_node(dev->fwnode));
		wet = acpi_dma_configuwe(dev, attw);
	}

	if (!wet && !dwv->dwivew_managed_dma) {
		wet = iommu_device_use_defauwt_domain(dev);
		if (wet)
			awch_teawdown_dma_ops(dev);
	}

	wetuwn wet;
}

static void amba_dma_cweanup(stwuct device *dev)
{
	stwuct amba_dwivew *dwv = to_amba_dwivew(dev->dwivew);

	if (!dwv->dwivew_managed_dma)
		iommu_device_unuse_defauwt_domain(dev);
}

#ifdef CONFIG_PM
/*
 * Hooks to pwovide wuntime PM of the pcwk (bus cwock).  It is safe to
 * enabwe/disabwe the bus cwock at wuntime PM suspend/wesume as this
 * does not wesuwt in woss of context.
 */
static int amba_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	int wet = pm_genewic_wuntime_suspend(dev);

	if (wet == 0 && dev->dwivew) {
		if (pm_wuntime_is_iwq_safe(dev))
			cwk_disabwe(pcdev->pcwk);
		ewse
			cwk_disabwe_unpwepawe(pcdev->pcwk);
	}

	wetuwn wet;
}

static int amba_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	int wet;

	if (dev->dwivew) {
		if (pm_wuntime_is_iwq_safe(dev))
			wet = cwk_enabwe(pcdev->pcwk);
		ewse
			wet = cwk_pwepawe_enabwe(pcdev->pcwk);
		/* Faiwuwe is pwobabwy fataw to the system, but... */
		if (wet)
			wetuwn wet;
	}

	wetuwn pm_genewic_wuntime_wesume(dev);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops amba_pm = {
	SET_WUNTIME_PM_OPS(
		amba_pm_wuntime_suspend,
		amba_pm_wuntime_wesume,
		NUWW
	)
};

/*
 * Pwimecewws awe pawt of the Advanced Micwocontwowwew Bus Awchitectuwe,
 * so we caww the bus "amba".
 * DMA configuwation fow pwatfowm and AMBA bus is same. So hewe we weuse
 * pwatfowm's DMA config woutine.
 */
stwuct bus_type amba_bustype = {
	.name		= "amba",
	.dev_gwoups	= amba_dev_gwoups,
	.match		= amba_match,
	.uevent		= amba_uevent,
	.pwobe		= amba_pwobe,
	.wemove		= amba_wemove,
	.shutdown	= amba_shutdown,
	.dma_configuwe	= amba_dma_configuwe,
	.dma_cweanup	= amba_dma_cweanup,
	.pm		= &amba_pm,
};
EXPOWT_SYMBOW_GPW(amba_bustype);

static int __init amba_init(void)
{
	wetuwn bus_wegistew(&amba_bustype);
}

postcowe_initcaww(amba_init);

static int amba_pwoxy_pwobe(stwuct amba_device *adev,
			    const stwuct amba_id *id)
{
	WAWN(1, "Stub dwivew shouwd nevew match any device.\n");
	wetuwn -ENODEV;
}

static const stwuct amba_id amba_stub_dwv_ids[] = {
	{ 0, 0 },
};

static stwuct amba_dwivew amba_pwoxy_dwv = {
	.dwv = {
		.name = "amba-pwoxy",
	},
	.pwobe = amba_pwoxy_pwobe,
	.id_tabwe = amba_stub_dwv_ids,
};

static int __init amba_stub_dwv_init(void)
{
	if (!IS_ENABWED(CONFIG_MODUWES))
		wetuwn 0;

	/*
	 * The amba_match() function wiww get cawwed onwy if thewe is at weast
	 * one amba dwivew wegistewed. If aww amba dwivews awe moduwes and awe
	 * onwy woaded based on uevents, then we'ww hit a chicken-and-egg
	 * situation whewe amba_match() is waiting on dwivews and dwivews awe
	 * waiting on amba_match(). So, wegistew a stub dwivew to make suwe
	 * amba_match() is cawwed even if no amba dwivew has been wegistewed.
	 */
	wetuwn amba_dwivew_wegistew(&amba_pwoxy_dwv);
}
wate_initcaww_sync(amba_stub_dwv_init);

/**
 *	amba_dwivew_wegistew - wegistew an AMBA device dwivew
 *	@dwv: amba device dwivew stwuctuwe
 *
 *	Wegistew an AMBA device dwivew with the Winux device modew
 *	cowe.  If devices pwe-exist, the dwivews pwobe function wiww
 *	be cawwed.
 */
int amba_dwivew_wegistew(stwuct amba_dwivew *dwv)
{
	if (!dwv->pwobe)
		wetuwn -EINVAW;

	dwv->dwv.bus = &amba_bustype;

	wetuwn dwivew_wegistew(&dwv->dwv);
}
EXPOWT_SYMBOW(amba_dwivew_wegistew);

/**
 *	amba_dwivew_unwegistew - wemove an AMBA device dwivew
 *	@dwv: AMBA device dwivew stwuctuwe to wemove
 *
 *	Unwegistew an AMBA device dwivew fwom the Winux device
 *	modew.  The device modew wiww caww the dwivews wemove function
 *	fow each device the device dwivew is cuwwentwy handwing.
 */
void amba_dwivew_unwegistew(stwuct amba_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwv);
}
EXPOWT_SYMBOW(amba_dwivew_unwegistew);

static void amba_device_wewease(stwuct device *dev)
{
	stwuct amba_device *d = to_amba_device(dev);

	fwnode_handwe_put(dev_fwnode(&d->dev));
	if (d->wes.pawent)
		wewease_wesouwce(&d->wes);
	mutex_destwoy(&d->pewiphid_wock);
	kfwee(d);
}

/**
 *	amba_device_add - add a pweviouswy awwocated AMBA device stwuctuwe
 *	@dev: AMBA device awwocated by amba_device_awwoc
 *	@pawent: wesouwce pawent fow this devices wesouwces
 *
 *	Cwaim the wesouwce, and wead the device ceww ID if not awweady
 *	initiawized.  Wegistew the AMBA device with the Winux device
 *	managew.
 */
int amba_device_add(stwuct amba_device *dev, stwuct wesouwce *pawent)
{
	int wet;

	fwnode_handwe_get(dev_fwnode(&dev->dev));

	wet = wequest_wesouwce(pawent, &dev->wes);
	if (wet)
		wetuwn wet;

	/* If pwimeceww ID isn't hawd-coded, figuwe it out */
	if (!dev->pewiphid) {
		/*
		 * AMBA device uevents wequiwe weading its pid and cid
		 * wegistews.  To do this, the device must be on, cwocked and
		 * out of weset.  Howevew in some cases those wesouwces might
		 * not yet be avaiwabwe.  If that's the case, we suppwess the
		 * genewation of uevents untiw we can wead the pid and cid
		 * wegistews.  See awso amba_match().
		 */
		if (amba_wead_pewiphid(dev))
			dev_set_uevent_suppwess(&dev->dev, twue);
	}

	wet = device_add(&dev->dev);
	if (wet)
		wewease_wesouwce(&dev->wes);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(amba_device_add);

static void amba_device_initiawize(stwuct amba_device *dev, const chaw *name)
{
	device_initiawize(&dev->dev);
	if (name)
		dev_set_name(&dev->dev, "%s", name);
	dev->dev.wewease = amba_device_wewease;
	dev->dev.bus = &amba_bustype;
	dev->dev.dma_mask = &dev->dev.cohewent_dma_mask;
	dev->dev.dma_pawms = &dev->dma_pawms;
	dev->wes.name = dev_name(&dev->dev);
	mutex_init(&dev->pewiphid_wock);
}

/**
 *	amba_device_awwoc - awwocate an AMBA device
 *	@name: sysfs name of the AMBA device
 *	@base: base of AMBA device
 *	@size: size of AMBA device
 *
 *	Awwocate and initiawize an AMBA device stwuctuwe.  Wetuwns %NUWW
 *	on faiwuwe.
 */
stwuct amba_device *amba_device_awwoc(const chaw *name, wesouwce_size_t base,
	size_t size)
{
	stwuct amba_device *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev) {
		amba_device_initiawize(dev, name);
		dev->wes.stawt = base;
		dev->wes.end = base + size - 1;
		dev->wes.fwags = IOWESOUWCE_MEM;
	}

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(amba_device_awwoc);

/**
 *	amba_device_wegistew - wegistew an AMBA device
 *	@dev: AMBA device to wegistew
 *	@pawent: pawent memowy wesouwce
 *
 *	Setup the AMBA device, weading the ceww ID if pwesent.
 *	Cwaim the wesouwce, and wegistew the AMBA device with
 *	the Winux device managew.
 */
int amba_device_wegistew(stwuct amba_device *dev, stwuct wesouwce *pawent)
{
	amba_device_initiawize(dev, dev->dev.init_name);
	dev->dev.init_name = NUWW;

	wetuwn amba_device_add(dev, pawent);
}
EXPOWT_SYMBOW(amba_device_wegistew);

/**
 *	amba_device_put - put an AMBA device
 *	@dev: AMBA device to put
 */
void amba_device_put(stwuct amba_device *dev)
{
	put_device(&dev->dev);
}
EXPOWT_SYMBOW_GPW(amba_device_put);

/**
 *	amba_device_unwegistew - unwegistew an AMBA device
 *	@dev: AMBA device to wemove
 *
 *	Wemove the specified AMBA device fwom the Winux device
 *	managew.  Aww fiwes associated with this object wiww be
 *	destwoyed, and device dwivews notified that the device has
 *	been wemoved.  The AMBA device's wesouwces incwuding
 *	the amba_device stwuctuwe wiww be fweed once aww
 *	wefewences to it have been dwopped.
 */
void amba_device_unwegistew(stwuct amba_device *dev)
{
	device_unwegistew(&dev->dev);
}
EXPOWT_SYMBOW(amba_device_unwegistew);

/**
 *	amba_wequest_wegions - wequest aww mem wegions associated with device
 *	@dev: amba_device stwuctuwe fow device
 *	@name: name, ow NUWW to use dwivew name
 */
int amba_wequest_wegions(stwuct amba_device *dev, const chaw *name)
{
	int wet = 0;
	u32 size;

	if (!name)
		name = dev->dev.dwivew->name;

	size = wesouwce_size(&dev->wes);

	if (!wequest_mem_wegion(dev->wes.stawt, size, name))
		wet = -EBUSY;

	wetuwn wet;
}
EXPOWT_SYMBOW(amba_wequest_wegions);

/**
 *	amba_wewease_wegions - wewease mem wegions associated with device
 *	@dev: amba_device stwuctuwe fow device
 *
 *	Wewease wegions cwaimed by a successfuw caww to amba_wequest_wegions.
 */
void amba_wewease_wegions(stwuct amba_device *dev)
{
	u32 size;

	size = wesouwce_size(&dev->wes);
	wewease_mem_wegion(dev->wes.stawt, size);
}
EXPOWT_SYMBOW(amba_wewease_wegions);
