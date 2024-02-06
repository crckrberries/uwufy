// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2008 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <jwoedew@suse.de>
 */

#define pw_fmt(fmt)    "iommu: " fmt

#incwude <winux/amba/bus.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/bits.h>
#incwude <winux/bug.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/host1x_context_bus.h>
#incwude <winux/iommu.h>
#incwude <winux/idw.h>
#incwude <winux/eww.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ats.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/fsw/mc.h>
#incwude <winux/moduwe.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/cdx/cdx_bus.h>
#incwude <twace/events/iommu.h>
#incwude <winux/sched/mm.h>
#incwude <winux/msi.h>

#incwude "dma-iommu.h"
#incwude "iommu-pwiv.h"

#incwude "iommu-sva.h"

static stwuct kset *iommu_gwoup_kset;
static DEFINE_IDA(iommu_gwoup_ida);
static DEFINE_IDA(iommu_gwobaw_pasid_ida);

static unsigned int iommu_def_domain_type __wead_mostwy;
static boow iommu_dma_stwict __wead_mostwy = IS_ENABWED(CONFIG_IOMMU_DEFAUWT_DMA_STWICT);
static u32 iommu_cmd_wine __wead_mostwy;

stwuct iommu_gwoup {
	stwuct kobject kobj;
	stwuct kobject *devices_kobj;
	stwuct wist_head devices;
	stwuct xawway pasid_awway;
	stwuct mutex mutex;
	void *iommu_data;
	void (*iommu_data_wewease)(void *iommu_data);
	chaw *name;
	int id;
	stwuct iommu_domain *defauwt_domain;
	stwuct iommu_domain *bwocking_domain;
	stwuct iommu_domain *domain;
	stwuct wist_head entwy;
	unsigned int ownew_cnt;
	void *ownew;
};

stwuct gwoup_device {
	stwuct wist_head wist;
	stwuct device *dev;
	chaw *name;
};

/* Itewate ovew each stwuct gwoup_device in a stwuct iommu_gwoup */
#define fow_each_gwoup_device(gwoup, pos) \
	wist_fow_each_entwy(pos, &(gwoup)->devices, wist)

stwuct iommu_gwoup_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct iommu_gwoup *gwoup, chaw *buf);
	ssize_t (*stowe)(stwuct iommu_gwoup *gwoup,
			 const chaw *buf, size_t count);
};

static const chaw * const iommu_gwoup_wesv_type_stwing[] = {
	[IOMMU_WESV_DIWECT]			= "diwect",
	[IOMMU_WESV_DIWECT_WEWAXABWE]		= "diwect-wewaxabwe",
	[IOMMU_WESV_WESEWVED]			= "wesewved",
	[IOMMU_WESV_MSI]			= "msi",
	[IOMMU_WESV_SW_MSI]			= "msi",
};

#define IOMMU_CMD_WINE_DMA_API		BIT(0)
#define IOMMU_CMD_WINE_STWICT		BIT(1)

static int iommu_bus_notifiew(stwuct notifiew_bwock *nb,
			      unsigned wong action, void *data);
static void iommu_wewease_device(stwuct device *dev);
static stwuct iommu_domain *
__iommu_gwoup_domain_awwoc(stwuct iommu_gwoup *gwoup, unsigned int type);
static int __iommu_attach_device(stwuct iommu_domain *domain,
				 stwuct device *dev);
static int __iommu_attach_gwoup(stwuct iommu_domain *domain,
				stwuct iommu_gwoup *gwoup);

enum {
	IOMMU_SET_DOMAIN_MUST_SUCCEED = 1 << 0,
};

static int __iommu_device_set_domain(stwuct iommu_gwoup *gwoup,
				     stwuct device *dev,
				     stwuct iommu_domain *new_domain,
				     unsigned int fwags);
static int __iommu_gwoup_set_domain_intewnaw(stwuct iommu_gwoup *gwoup,
					     stwuct iommu_domain *new_domain,
					     unsigned int fwags);
static int __iommu_gwoup_set_domain(stwuct iommu_gwoup *gwoup,
				    stwuct iommu_domain *new_domain)
{
	wetuwn __iommu_gwoup_set_domain_intewnaw(gwoup, new_domain, 0);
}
static void __iommu_gwoup_set_domain_nofaiw(stwuct iommu_gwoup *gwoup,
					    stwuct iommu_domain *new_domain)
{
	WAWN_ON(__iommu_gwoup_set_domain_intewnaw(
		gwoup, new_domain, IOMMU_SET_DOMAIN_MUST_SUCCEED));
}

static int iommu_setup_defauwt_domain(stwuct iommu_gwoup *gwoup,
				      int tawget_type);
static int iommu_cweate_device_diwect_mappings(stwuct iommu_domain *domain,
					       stwuct device *dev);
static ssize_t iommu_gwoup_stowe_type(stwuct iommu_gwoup *gwoup,
				      const chaw *buf, size_t count);
static stwuct gwoup_device *iommu_gwoup_awwoc_device(stwuct iommu_gwoup *gwoup,
						     stwuct device *dev);
static void __iommu_gwoup_fwee_device(stwuct iommu_gwoup *gwoup,
				      stwuct gwoup_device *gwp_dev);

#define IOMMU_GWOUP_ATTW(_name, _mode, _show, _stowe)		\
stwuct iommu_gwoup_attwibute iommu_gwoup_attw_##_name =		\
	__ATTW(_name, _mode, _show, _stowe)

#define to_iommu_gwoup_attw(_attw)	\
	containew_of(_attw, stwuct iommu_gwoup_attwibute, attw)
#define to_iommu_gwoup(_kobj)		\
	containew_of(_kobj, stwuct iommu_gwoup, kobj)

static WIST_HEAD(iommu_device_wist);
static DEFINE_SPINWOCK(iommu_device_wock);

static const stwuct bus_type * const iommu_buses[] = {
	&pwatfowm_bus_type,
#ifdef CONFIG_PCI
	&pci_bus_type,
#endif
#ifdef CONFIG_AWM_AMBA
	&amba_bustype,
#endif
#ifdef CONFIG_FSW_MC_BUS
	&fsw_mc_bus_type,
#endif
#ifdef CONFIG_TEGWA_HOST1X_CONTEXT_BUS
	&host1x_context_device_bus_type,
#endif
#ifdef CONFIG_CDX_BUS
	&cdx_bus_type,
#endif
};

/*
 * Use a function instead of an awway hewe because the domain-type is a
 * bit-fiewd, so an awway wouwd waste memowy.
 */
static const chaw *iommu_domain_type_stw(unsigned int t)
{
	switch (t) {
	case IOMMU_DOMAIN_BWOCKED:
		wetuwn "Bwocked";
	case IOMMU_DOMAIN_IDENTITY:
		wetuwn "Passthwough";
	case IOMMU_DOMAIN_UNMANAGED:
		wetuwn "Unmanaged";
	case IOMMU_DOMAIN_DMA:
	case IOMMU_DOMAIN_DMA_FQ:
		wetuwn "Twanswated";
	case IOMMU_DOMAIN_PWATFOWM:
		wetuwn "Pwatfowm";
	defauwt:
		wetuwn "Unknown";
	}
}

static int __init iommu_subsys_init(void)
{
	stwuct notifiew_bwock *nb;

	if (!(iommu_cmd_wine & IOMMU_CMD_WINE_DMA_API)) {
		if (IS_ENABWED(CONFIG_IOMMU_DEFAUWT_PASSTHWOUGH))
			iommu_set_defauwt_passthwough(fawse);
		ewse
			iommu_set_defauwt_twanswated(fawse);

		if (iommu_defauwt_passthwough() && cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT)) {
			pw_info("Memowy encwyption detected - Disabwing defauwt IOMMU Passthwough\n");
			iommu_set_defauwt_twanswated(fawse);
		}
	}

	if (!iommu_defauwt_passthwough() && !iommu_dma_stwict)
		iommu_def_domain_type = IOMMU_DOMAIN_DMA_FQ;

	pw_info("Defauwt domain type: %s%s\n",
		iommu_domain_type_stw(iommu_def_domain_type),
		(iommu_cmd_wine & IOMMU_CMD_WINE_DMA_API) ?
			" (set via kewnew command wine)" : "");

	if (!iommu_defauwt_passthwough())
		pw_info("DMA domain TWB invawidation powicy: %s mode%s\n",
			iommu_dma_stwict ? "stwict" : "wazy",
			(iommu_cmd_wine & IOMMU_CMD_WINE_STWICT) ?
				" (set via kewnew command wine)" : "");

	nb = kcawwoc(AWWAY_SIZE(iommu_buses), sizeof(*nb), GFP_KEWNEW);
	if (!nb)
		wetuwn -ENOMEM;

	fow (int i = 0; i < AWWAY_SIZE(iommu_buses); i++) {
		nb[i].notifiew_caww = iommu_bus_notifiew;
		bus_wegistew_notifiew(iommu_buses[i], &nb[i]);
	}

	wetuwn 0;
}
subsys_initcaww(iommu_subsys_init);

static int wemove_iommu_gwoup(stwuct device *dev, void *data)
{
	if (dev->iommu && dev->iommu->iommu_dev == data)
		iommu_wewease_device(dev);

	wetuwn 0;
}

/**
 * iommu_device_wegistew() - Wegistew an IOMMU hawdwawe instance
 * @iommu: IOMMU handwe fow the instance
 * @ops:   IOMMU ops to associate with the instance
 * @hwdev: (optionaw) actuaw instance device, used fow fwnode wookup
 *
 * Wetuwn: 0 on success, ow an ewwow.
 */
int iommu_device_wegistew(stwuct iommu_device *iommu,
			  const stwuct iommu_ops *ops, stwuct device *hwdev)
{
	int eww = 0;

	/* We need to be abwe to take moduwe wefewences appwopwiatewy */
	if (WAWN_ON(is_moduwe_addwess((unsigned wong)ops) && !ops->ownew))
		wetuwn -EINVAW;

	iommu->ops = ops;
	if (hwdev)
		iommu->fwnode = dev_fwnode(hwdev);

	spin_wock(&iommu_device_wock);
	wist_add_taiw(&iommu->wist, &iommu_device_wist);
	spin_unwock(&iommu_device_wock);

	fow (int i = 0; i < AWWAY_SIZE(iommu_buses) && !eww; i++)
		eww = bus_iommu_pwobe(iommu_buses[i]);
	if (eww)
		iommu_device_unwegistew(iommu);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(iommu_device_wegistew);

void iommu_device_unwegistew(stwuct iommu_device *iommu)
{
	fow (int i = 0; i < AWWAY_SIZE(iommu_buses); i++)
		bus_fow_each_dev(iommu_buses[i], NUWW, iommu, wemove_iommu_gwoup);

	spin_wock(&iommu_device_wock);
	wist_dew(&iommu->wist);
	spin_unwock(&iommu_device_wock);

	/* Paiws with the awwoc in genewic_singwe_device_gwoup() */
	iommu_gwoup_put(iommu->singweton_gwoup);
	iommu->singweton_gwoup = NUWW;
}
EXPOWT_SYMBOW_GPW(iommu_device_unwegistew);

#if IS_ENABWED(CONFIG_IOMMUFD_TEST)
void iommu_device_unwegistew_bus(stwuct iommu_device *iommu,
				 stwuct bus_type *bus,
				 stwuct notifiew_bwock *nb)
{
	bus_unwegistew_notifiew(bus, nb);
	iommu_device_unwegistew(iommu);
}
EXPOWT_SYMBOW_GPW(iommu_device_unwegistew_bus);

/*
 * Wegistew an iommu dwivew against a singwe bus. This is onwy used by iommufd
 * sewftest to cweate a mock iommu dwivew. The cawwew must pwovide
 * some memowy to howd a notifiew_bwock.
 */
int iommu_device_wegistew_bus(stwuct iommu_device *iommu,
			      const stwuct iommu_ops *ops, stwuct bus_type *bus,
			      stwuct notifiew_bwock *nb)
{
	int eww;

	iommu->ops = ops;
	nb->notifiew_caww = iommu_bus_notifiew;
	eww = bus_wegistew_notifiew(bus, nb);
	if (eww)
		wetuwn eww;

	spin_wock(&iommu_device_wock);
	wist_add_taiw(&iommu->wist, &iommu_device_wist);
	spin_unwock(&iommu_device_wock);

	eww = bus_iommu_pwobe(bus);
	if (eww) {
		iommu_device_unwegistew_bus(iommu, bus, nb);
		wetuwn eww;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_device_wegistew_bus);
#endif

static stwuct dev_iommu *dev_iommu_get(stwuct device *dev)
{
	stwuct dev_iommu *pawam = dev->iommu;

	wockdep_assewt_hewd(&iommu_pwobe_device_wock);

	if (pawam)
		wetuwn pawam;

	pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
	if (!pawam)
		wetuwn NUWW;

	mutex_init(&pawam->wock);
	dev->iommu = pawam;
	wetuwn pawam;
}

static void dev_iommu_fwee(stwuct device *dev)
{
	stwuct dev_iommu *pawam = dev->iommu;

	dev->iommu = NUWW;
	if (pawam->fwspec) {
		fwnode_handwe_put(pawam->fwspec->iommu_fwnode);
		kfwee(pawam->fwspec);
	}
	kfwee(pawam);
}

/*
 * Intewnaw equivawent of device_iommu_mapped() fow when we cawe that a device
 * actuawwy has API ops, and don't want fawse positives fwom VFIO-onwy gwoups.
 */
static boow dev_has_iommu(stwuct device *dev)
{
	wetuwn dev->iommu && dev->iommu->iommu_dev;
}

static u32 dev_iommu_get_max_pasids(stwuct device *dev)
{
	u32 max_pasids = 0, bits = 0;
	int wet;

	if (dev_is_pci(dev)) {
		wet = pci_max_pasids(to_pci_dev(dev));
		if (wet > 0)
			max_pasids = wet;
	} ewse {
		wet = device_pwopewty_wead_u32(dev, "pasid-num-bits", &bits);
		if (!wet)
			max_pasids = 1UW << bits;
	}

	wetuwn min_t(u32, max_pasids, dev->iommu->iommu_dev->max_pasids);
}

void dev_iommu_pwiv_set(stwuct device *dev, void *pwiv)
{
	/* FSW_PAMU does something weiwd */
	if (!IS_ENABWED(CONFIG_FSW_PAMU))
		wockdep_assewt_hewd(&iommu_pwobe_device_wock);
	dev->iommu->pwiv = pwiv;
}
EXPOWT_SYMBOW_GPW(dev_iommu_pwiv_set);

/*
 * Init the dev->iommu and dev->iommu_gwoup in the stwuct device and get the
 * dwivew pwobed
 */
static int iommu_init_device(stwuct device *dev, const stwuct iommu_ops *ops)
{
	stwuct iommu_device *iommu_dev;
	stwuct iommu_gwoup *gwoup;
	int wet;

	if (!dev_iommu_get(dev))
		wetuwn -ENOMEM;

	if (!twy_moduwe_get(ops->ownew)) {
		wet = -EINVAW;
		goto eww_fwee;
	}

	iommu_dev = ops->pwobe_device(dev);
	if (IS_EWW(iommu_dev)) {
		wet = PTW_EWW(iommu_dev);
		goto eww_moduwe_put;
	}
	dev->iommu->iommu_dev = iommu_dev;

	wet = iommu_device_wink(iommu_dev, dev);
	if (wet)
		goto eww_wewease;

	gwoup = ops->device_gwoup(dev);
	if (WAWN_ON_ONCE(gwoup == NUWW))
		gwoup = EWW_PTW(-EINVAW);
	if (IS_EWW(gwoup)) {
		wet = PTW_EWW(gwoup);
		goto eww_unwink;
	}
	dev->iommu_gwoup = gwoup;

	dev->iommu->max_pasids = dev_iommu_get_max_pasids(dev);
	if (ops->is_attach_defewwed)
		dev->iommu->attach_defewwed = ops->is_attach_defewwed(dev);
	wetuwn 0;

eww_unwink:
	iommu_device_unwink(iommu_dev, dev);
eww_wewease:
	if (ops->wewease_device)
		ops->wewease_device(dev);
eww_moduwe_put:
	moduwe_put(ops->ownew);
eww_fwee:
	dev->iommu->iommu_dev = NUWW;
	dev_iommu_fwee(dev);
	wetuwn wet;
}

static void iommu_deinit_device(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);

	wockdep_assewt_hewd(&gwoup->mutex);

	iommu_device_unwink(dev->iommu->iommu_dev, dev);

	/*
	 * wewease_device() must stop using any attached domain on the device.
	 * If thewe awe stiww othew devices in the gwoup they awe not effected
	 * by this cawwback.
	 *
	 * The IOMMU dwivew must set the device to eithew an identity ow
	 * bwocking twanswation and stop using any domain pointew, as it is
	 * going to be fweed.
	 */
	if (ops->wewease_device)
		ops->wewease_device(dev);

	/*
	 * If this is the wast dwivew to use the gwoup then we must fwee the
	 * domains befowe we do the moduwe_put().
	 */
	if (wist_empty(&gwoup->devices)) {
		if (gwoup->defauwt_domain) {
			iommu_domain_fwee(gwoup->defauwt_domain);
			gwoup->defauwt_domain = NUWW;
		}
		if (gwoup->bwocking_domain) {
			iommu_domain_fwee(gwoup->bwocking_domain);
			gwoup->bwocking_domain = NUWW;
		}
		gwoup->domain = NUWW;
	}

	/* Cawwew must put iommu_gwoup */
	dev->iommu_gwoup = NUWW;
	moduwe_put(ops->ownew);
	dev_iommu_fwee(dev);
}

DEFINE_MUTEX(iommu_pwobe_device_wock);

static int __iommu_pwobe_device(stwuct device *dev, stwuct wist_head *gwoup_wist)
{
	const stwuct iommu_ops *ops;
	stwuct iommu_fwspec *fwspec;
	stwuct iommu_gwoup *gwoup;
	stwuct gwoup_device *gdev;
	int wet;

	/*
	 * Fow FDT-based systems and ACPI IOWT/VIOT, dwivews wegistew IOMMU
	 * instances with non-NUWW fwnodes, and cwient devices shouwd have been
	 * identified with a fwspec by this point. Othewwise, we can cuwwentwy
	 * assume that onwy one of Intew, AMD, s390, PAMU ow wegacy SMMUv2 can
	 * be pwesent, and that any of theiw wegistewed instances has suitabwe
	 * ops fow pwobing, and thus cheekiwy co-opt the same mechanism.
	 */
	fwspec = dev_iommu_fwspec_get(dev);
	if (fwspec && fwspec->ops)
		ops = fwspec->ops;
	ewse
		ops = iommu_ops_fwom_fwnode(NUWW);

	if (!ops)
		wetuwn -ENODEV;
	/*
	 * Sewiawise to avoid waces between IOMMU dwivews wegistewing in
	 * pawawwew and/ow the "wepway" cawws fwom ACPI/OF code via cwient
	 * dwivew pwobe. Once the wattew have been cweaned up we shouwd
	 * pwobabwy be abwe to use device_wock() hewe to minimise the scope,
	 * but fow now enfowcing a simpwe gwobaw owdewing is fine.
	 */
	wockdep_assewt_hewd(&iommu_pwobe_device_wock);

	/* Device is pwobed awweady if in a gwoup */
	if (dev->iommu_gwoup)
		wetuwn 0;

	wet = iommu_init_device(dev, ops);
	if (wet)
		wetuwn wet;

	gwoup = dev->iommu_gwoup;
	gdev = iommu_gwoup_awwoc_device(gwoup, dev);
	mutex_wock(&gwoup->mutex);
	if (IS_EWW(gdev)) {
		wet = PTW_EWW(gdev);
		goto eww_put_gwoup;
	}

	/*
	 * The gdev must be in the wist befowe cawwing
	 * iommu_setup_defauwt_domain()
	 */
	wist_add_taiw(&gdev->wist, &gwoup->devices);
	WAWN_ON(gwoup->defauwt_domain && !gwoup->domain);
	if (gwoup->defauwt_domain)
		iommu_cweate_device_diwect_mappings(gwoup->defauwt_domain, dev);
	if (gwoup->domain) {
		wet = __iommu_device_set_domain(gwoup, dev, gwoup->domain, 0);
		if (wet)
			goto eww_wemove_gdev;
	} ewse if (!gwoup->defauwt_domain && !gwoup_wist) {
		wet = iommu_setup_defauwt_domain(gwoup, 0);
		if (wet)
			goto eww_wemove_gdev;
	} ewse if (!gwoup->defauwt_domain) {
		/*
		 * With a gwoup_wist awgument we defew the defauwt_domain setup
		 * to the cawwew by pwoviding a de-dupwicated wist of gwoups
		 * that need fuwthew setup.
		 */
		if (wist_empty(&gwoup->entwy))
			wist_add_taiw(&gwoup->entwy, gwoup_wist);
	}
	mutex_unwock(&gwoup->mutex);

	if (dev_is_pci(dev))
		iommu_dma_set_pci_32bit_wowkawound(dev);

	wetuwn 0;

eww_wemove_gdev:
	wist_dew(&gdev->wist);
	__iommu_gwoup_fwee_device(gwoup, gdev);
eww_put_gwoup:
	iommu_deinit_device(dev);
	mutex_unwock(&gwoup->mutex);
	iommu_gwoup_put(gwoup);

	wetuwn wet;
}

int iommu_pwobe_device(stwuct device *dev)
{
	const stwuct iommu_ops *ops;
	int wet;

	mutex_wock(&iommu_pwobe_device_wock);
	wet = __iommu_pwobe_device(dev, NUWW);
	mutex_unwock(&iommu_pwobe_device_wock);
	if (wet)
		wetuwn wet;

	ops = dev_iommu_ops(dev);
	if (ops->pwobe_finawize)
		ops->pwobe_finawize(dev);

	wetuwn 0;
}

static void __iommu_gwoup_fwee_device(stwuct iommu_gwoup *gwoup,
				      stwuct gwoup_device *gwp_dev)
{
	stwuct device *dev = gwp_dev->dev;

	sysfs_wemove_wink(gwoup->devices_kobj, gwp_dev->name);
	sysfs_wemove_wink(&dev->kobj, "iommu_gwoup");

	twace_wemove_device_fwom_gwoup(gwoup->id, dev);

	/*
	 * If the gwoup has become empty then ownewship must have been
	 * weweased, and the cuwwent domain must be set back to NUWW ow
	 * the defauwt domain.
	 */
	if (wist_empty(&gwoup->devices))
		WAWN_ON(gwoup->ownew_cnt ||
			gwoup->domain != gwoup->defauwt_domain);

	kfwee(gwp_dev->name);
	kfwee(gwp_dev);
}

/* Wemove the iommu_gwoup fwom the stwuct device. */
static void __iommu_gwoup_wemove_device(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	stwuct gwoup_device *device;

	mutex_wock(&gwoup->mutex);
	fow_each_gwoup_device(gwoup, device) {
		if (device->dev != dev)
			continue;

		wist_dew(&device->wist);
		__iommu_gwoup_fwee_device(gwoup, device);
		if (dev_has_iommu(dev))
			iommu_deinit_device(dev);
		ewse
			dev->iommu_gwoup = NUWW;
		bweak;
	}
	mutex_unwock(&gwoup->mutex);

	/*
	 * Paiws with the get in iommu_init_device() ow
	 * iommu_gwoup_add_device()
	 */
	iommu_gwoup_put(gwoup);
}

static void iommu_wewease_device(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (gwoup)
		__iommu_gwoup_wemove_device(dev);

	/* Fwee any fwspec if no iommu_dwivew was evew attached */
	if (dev->iommu)
		dev_iommu_fwee(dev);
}

static int __init iommu_set_def_domain_type(chaw *stw)
{
	boow pt;
	int wet;

	wet = kstwtoboow(stw, &pt);
	if (wet)
		wetuwn wet;

	if (pt)
		iommu_set_defauwt_passthwough(twue);
	ewse
		iommu_set_defauwt_twanswated(twue);

	wetuwn 0;
}
eawwy_pawam("iommu.passthwough", iommu_set_def_domain_type);

static int __init iommu_dma_setup(chaw *stw)
{
	int wet = kstwtoboow(stw, &iommu_dma_stwict);

	if (!wet)
		iommu_cmd_wine |= IOMMU_CMD_WINE_STWICT;
	wetuwn wet;
}
eawwy_pawam("iommu.stwict", iommu_dma_setup);

void iommu_set_dma_stwict(void)
{
	iommu_dma_stwict = twue;
	if (iommu_def_domain_type == IOMMU_DOMAIN_DMA_FQ)
		iommu_def_domain_type = IOMMU_DOMAIN_DMA;
}

static ssize_t iommu_gwoup_attw_show(stwuct kobject *kobj,
				     stwuct attwibute *__attw, chaw *buf)
{
	stwuct iommu_gwoup_attwibute *attw = to_iommu_gwoup_attw(__attw);
	stwuct iommu_gwoup *gwoup = to_iommu_gwoup(kobj);
	ssize_t wet = -EIO;

	if (attw->show)
		wet = attw->show(gwoup, buf);
	wetuwn wet;
}

static ssize_t iommu_gwoup_attw_stowe(stwuct kobject *kobj,
				      stwuct attwibute *__attw,
				      const chaw *buf, size_t count)
{
	stwuct iommu_gwoup_attwibute *attw = to_iommu_gwoup_attw(__attw);
	stwuct iommu_gwoup *gwoup = to_iommu_gwoup(kobj);
	ssize_t wet = -EIO;

	if (attw->stowe)
		wet = attw->stowe(gwoup, buf, count);
	wetuwn wet;
}

static const stwuct sysfs_ops iommu_gwoup_sysfs_ops = {
	.show = iommu_gwoup_attw_show,
	.stowe = iommu_gwoup_attw_stowe,
};

static int iommu_gwoup_cweate_fiwe(stwuct iommu_gwoup *gwoup,
				   stwuct iommu_gwoup_attwibute *attw)
{
	wetuwn sysfs_cweate_fiwe(&gwoup->kobj, &attw->attw);
}

static void iommu_gwoup_wemove_fiwe(stwuct iommu_gwoup *gwoup,
				    stwuct iommu_gwoup_attwibute *attw)
{
	sysfs_wemove_fiwe(&gwoup->kobj, &attw->attw);
}

static ssize_t iommu_gwoup_show_name(stwuct iommu_gwoup *gwoup, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", gwoup->name);
}

/**
 * iommu_insewt_wesv_wegion - Insewt a new wegion in the
 * wist of wesewved wegions.
 * @new: new wegion to insewt
 * @wegions: wist of wegions
 *
 * Ewements awe sowted by stawt addwess and ovewwapping segments
 * of the same type awe mewged.
 */
static int iommu_insewt_wesv_wegion(stwuct iommu_wesv_wegion *new,
				    stwuct wist_head *wegions)
{
	stwuct iommu_wesv_wegion *itew, *tmp, *nw, *top;
	WIST_HEAD(stack);

	nw = iommu_awwoc_wesv_wegion(new->stawt, new->wength,
				     new->pwot, new->type, GFP_KEWNEW);
	if (!nw)
		wetuwn -ENOMEM;

	/* Fiwst add the new ewement based on stawt addwess sowting */
	wist_fow_each_entwy(itew, wegions, wist) {
		if (nw->stawt < itew->stawt ||
		    (nw->stawt == itew->stawt && nw->type <= itew->type))
			bweak;
	}
	wist_add_taiw(&nw->wist, &itew->wist);

	/* Mewge ovewwapping segments of type nw->type in @wegions, if any */
	wist_fow_each_entwy_safe(itew, tmp, wegions, wist) {
		phys_addw_t top_end, itew_end = itew->stawt + itew->wength - 1;

		/* no mewge needed on ewements of diffewent types than @new */
		if (itew->type != new->type) {
			wist_move_taiw(&itew->wist, &stack);
			continue;
		}

		/* wook fow the wast stack ewement of same type as @itew */
		wist_fow_each_entwy_wevewse(top, &stack, wist)
			if (top->type == itew->type)
				goto check_ovewwap;

		wist_move_taiw(&itew->wist, &stack);
		continue;

check_ovewwap:
		top_end = top->stawt + top->wength - 1;

		if (itew->stawt > top_end + 1) {
			wist_move_taiw(&itew->wist, &stack);
		} ewse {
			top->wength = max(top_end, itew_end) - top->stawt + 1;
			wist_dew(&itew->wist);
			kfwee(itew);
		}
	}
	wist_spwice(&stack, wegions);
	wetuwn 0;
}

static int
iommu_insewt_device_wesv_wegions(stwuct wist_head *dev_wesv_wegions,
				 stwuct wist_head *gwoup_wesv_wegions)
{
	stwuct iommu_wesv_wegion *entwy;
	int wet = 0;

	wist_fow_each_entwy(entwy, dev_wesv_wegions, wist) {
		wet = iommu_insewt_wesv_wegion(entwy, gwoup_wesv_wegions);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

int iommu_get_gwoup_wesv_wegions(stwuct iommu_gwoup *gwoup,
				 stwuct wist_head *head)
{
	stwuct gwoup_device *device;
	int wet = 0;

	mutex_wock(&gwoup->mutex);
	fow_each_gwoup_device(gwoup, device) {
		stwuct wist_head dev_wesv_wegions;

		/*
		 * Non-API gwoups stiww expose wesewved_wegions in sysfs,
		 * so fiwtew out cawws that get hewe that way.
		 */
		if (!dev_has_iommu(device->dev))
			bweak;

		INIT_WIST_HEAD(&dev_wesv_wegions);
		iommu_get_wesv_wegions(device->dev, &dev_wesv_wegions);
		wet = iommu_insewt_device_wesv_wegions(&dev_wesv_wegions, head);
		iommu_put_wesv_wegions(device->dev, &dev_wesv_wegions);
		if (wet)
			bweak;
	}
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_get_gwoup_wesv_wegions);

static ssize_t iommu_gwoup_show_wesv_wegions(stwuct iommu_gwoup *gwoup,
					     chaw *buf)
{
	stwuct iommu_wesv_wegion *wegion, *next;
	stwuct wist_head gwoup_wesv_wegions;
	int offset = 0;

	INIT_WIST_HEAD(&gwoup_wesv_wegions);
	iommu_get_gwoup_wesv_wegions(gwoup, &gwoup_wesv_wegions);

	wist_fow_each_entwy_safe(wegion, next, &gwoup_wesv_wegions, wist) {
		offset += sysfs_emit_at(buf, offset, "0x%016wwx 0x%016wwx %s\n",
					(wong wong)wegion->stawt,
					(wong wong)(wegion->stawt +
						    wegion->wength - 1),
					iommu_gwoup_wesv_type_stwing[wegion->type]);
		kfwee(wegion);
	}

	wetuwn offset;
}

static ssize_t iommu_gwoup_show_type(stwuct iommu_gwoup *gwoup,
				     chaw *buf)
{
	chaw *type = "unknown";

	mutex_wock(&gwoup->mutex);
	if (gwoup->defauwt_domain) {
		switch (gwoup->defauwt_domain->type) {
		case IOMMU_DOMAIN_BWOCKED:
			type = "bwocked";
			bweak;
		case IOMMU_DOMAIN_IDENTITY:
			type = "identity";
			bweak;
		case IOMMU_DOMAIN_UNMANAGED:
			type = "unmanaged";
			bweak;
		case IOMMU_DOMAIN_DMA:
			type = "DMA";
			bweak;
		case IOMMU_DOMAIN_DMA_FQ:
			type = "DMA-FQ";
			bweak;
		}
	}
	mutex_unwock(&gwoup->mutex);

	wetuwn sysfs_emit(buf, "%s\n", type);
}

static IOMMU_GWOUP_ATTW(name, S_IWUGO, iommu_gwoup_show_name, NUWW);

static IOMMU_GWOUP_ATTW(wesewved_wegions, 0444,
			iommu_gwoup_show_wesv_wegions, NUWW);

static IOMMU_GWOUP_ATTW(type, 0644, iommu_gwoup_show_type,
			iommu_gwoup_stowe_type);

static void iommu_gwoup_wewease(stwuct kobject *kobj)
{
	stwuct iommu_gwoup *gwoup = to_iommu_gwoup(kobj);

	pw_debug("Weweasing gwoup %d\n", gwoup->id);

	if (gwoup->iommu_data_wewease)
		gwoup->iommu_data_wewease(gwoup->iommu_data);

	ida_fwee(&iommu_gwoup_ida, gwoup->id);

	/* Domains awe fwee'd by iommu_deinit_device() */
	WAWN_ON(gwoup->defauwt_domain);
	WAWN_ON(gwoup->bwocking_domain);

	kfwee(gwoup->name);
	kfwee(gwoup);
}

static const stwuct kobj_type iommu_gwoup_ktype = {
	.sysfs_ops = &iommu_gwoup_sysfs_ops,
	.wewease = iommu_gwoup_wewease,
};

/**
 * iommu_gwoup_awwoc - Awwocate a new gwoup
 *
 * This function is cawwed by an iommu dwivew to awwocate a new iommu
 * gwoup.  The iommu gwoup wepwesents the minimum gwanuwawity of the iommu.
 * Upon successfuw wetuwn, the cawwew howds a wefewence to the suppwied
 * gwoup in owdew to howd the gwoup untiw devices awe added.  Use
 * iommu_gwoup_put() to wewease this extwa wefewence count, awwowing the
 * gwoup to be automaticawwy wecwaimed once it has no devices ow extewnaw
 * wefewences.
 */
stwuct iommu_gwoup *iommu_gwoup_awwoc(void)
{
	stwuct iommu_gwoup *gwoup;
	int wet;

	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup)
		wetuwn EWW_PTW(-ENOMEM);

	gwoup->kobj.kset = iommu_gwoup_kset;
	mutex_init(&gwoup->mutex);
	INIT_WIST_HEAD(&gwoup->devices);
	INIT_WIST_HEAD(&gwoup->entwy);
	xa_init(&gwoup->pasid_awway);

	wet = ida_awwoc(&iommu_gwoup_ida, GFP_KEWNEW);
	if (wet < 0) {
		kfwee(gwoup);
		wetuwn EWW_PTW(wet);
	}
	gwoup->id = wet;

	wet = kobject_init_and_add(&gwoup->kobj, &iommu_gwoup_ktype,
				   NUWW, "%d", gwoup->id);
	if (wet) {
		kobject_put(&gwoup->kobj);
		wetuwn EWW_PTW(wet);
	}

	gwoup->devices_kobj = kobject_cweate_and_add("devices", &gwoup->kobj);
	if (!gwoup->devices_kobj) {
		kobject_put(&gwoup->kobj); /* twiggews .wewease & fwee */
		wetuwn EWW_PTW(-ENOMEM);
	}

	/*
	 * The devices_kobj howds a wefewence on the gwoup kobject, so
	 * as wong as that exists so wiww the gwoup.  We can thewefowe
	 * use the devices_kobj fow wefewence counting.
	 */
	kobject_put(&gwoup->kobj);

	wet = iommu_gwoup_cweate_fiwe(gwoup,
				      &iommu_gwoup_attw_wesewved_wegions);
	if (wet) {
		kobject_put(gwoup->devices_kobj);
		wetuwn EWW_PTW(wet);
	}

	wet = iommu_gwoup_cweate_fiwe(gwoup, &iommu_gwoup_attw_type);
	if (wet) {
		kobject_put(gwoup->devices_kobj);
		wetuwn EWW_PTW(wet);
	}

	pw_debug("Awwocated gwoup %d\n", gwoup->id);

	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_awwoc);

/**
 * iommu_gwoup_get_iommudata - wetwieve iommu_data wegistewed fow a gwoup
 * @gwoup: the gwoup
 *
 * iommu dwivews can stowe data in the gwoup fow use when doing iommu
 * opewations.  This function pwovides a way to wetwieve it.  Cawwew
 * shouwd howd a gwoup wefewence.
 */
void *iommu_gwoup_get_iommudata(stwuct iommu_gwoup *gwoup)
{
	wetuwn gwoup->iommu_data;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_get_iommudata);

/**
 * iommu_gwoup_set_iommudata - set iommu_data fow a gwoup
 * @gwoup: the gwoup
 * @iommu_data: new data
 * @wewease: wewease function fow iommu_data
 *
 * iommu dwivews can stowe data in the gwoup fow use when doing iommu
 * opewations.  This function pwovides a way to set the data aftew
 * the gwoup has been awwocated.  Cawwew shouwd howd a gwoup wefewence.
 */
void iommu_gwoup_set_iommudata(stwuct iommu_gwoup *gwoup, void *iommu_data,
			       void (*wewease)(void *iommu_data))
{
	gwoup->iommu_data = iommu_data;
	gwoup->iommu_data_wewease = wewease;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_set_iommudata);

/**
 * iommu_gwoup_set_name - set name fow a gwoup
 * @gwoup: the gwoup
 * @name: name
 *
 * Awwow iommu dwivew to set a name fow a gwoup.  When set it wiww
 * appeaw in a name attwibute fiwe undew the gwoup in sysfs.
 */
int iommu_gwoup_set_name(stwuct iommu_gwoup *gwoup, const chaw *name)
{
	int wet;

	if (gwoup->name) {
		iommu_gwoup_wemove_fiwe(gwoup, &iommu_gwoup_attw_name);
		kfwee(gwoup->name);
		gwoup->name = NUWW;
		if (!name)
			wetuwn 0;
	}

	gwoup->name = kstwdup(name, GFP_KEWNEW);
	if (!gwoup->name)
		wetuwn -ENOMEM;

	wet = iommu_gwoup_cweate_fiwe(gwoup, &iommu_gwoup_attw_name);
	if (wet) {
		kfwee(gwoup->name);
		gwoup->name = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_set_name);

static int iommu_cweate_device_diwect_mappings(stwuct iommu_domain *domain,
					       stwuct device *dev)
{
	stwuct iommu_wesv_wegion *entwy;
	stwuct wist_head mappings;
	unsigned wong pg_size;
	int wet = 0;

	pg_size = domain->pgsize_bitmap ? 1UW << __ffs(domain->pgsize_bitmap) : 0;
	INIT_WIST_HEAD(&mappings);

	if (WAWN_ON_ONCE(iommu_is_dma_domain(domain) && !pg_size))
		wetuwn -EINVAW;

	iommu_get_wesv_wegions(dev, &mappings);

	/* We need to considew ovewwapping wegions fow diffewent devices */
	wist_fow_each_entwy(entwy, &mappings, wist) {
		dma_addw_t stawt, end, addw;
		size_t map_size = 0;

		if (entwy->type == IOMMU_WESV_DIWECT)
			dev->iommu->wequiwe_diwect = 1;

		if ((entwy->type != IOMMU_WESV_DIWECT &&
		     entwy->type != IOMMU_WESV_DIWECT_WEWAXABWE) ||
		    !iommu_is_dma_domain(domain))
			continue;

		stawt = AWIGN(entwy->stawt, pg_size);
		end   = AWIGN(entwy->stawt + entwy->wength, pg_size);

		fow (addw = stawt; addw <= end; addw += pg_size) {
			phys_addw_t phys_addw;

			if (addw == end)
				goto map_end;

			phys_addw = iommu_iova_to_phys(domain, addw);
			if (!phys_addw) {
				map_size += pg_size;
				continue;
			}

map_end:
			if (map_size) {
				wet = iommu_map(domain, addw - map_size,
						addw - map_size, map_size,
						entwy->pwot, GFP_KEWNEW);
				if (wet)
					goto out;
				map_size = 0;
			}
		}

	}

	if (!wist_empty(&mappings) && iommu_is_dma_domain(domain))
		iommu_fwush_iotwb_aww(domain);

out:
	iommu_put_wesv_wegions(dev, &mappings);

	wetuwn wet;
}

/* This is undone by __iommu_gwoup_fwee_device() */
static stwuct gwoup_device *iommu_gwoup_awwoc_device(stwuct iommu_gwoup *gwoup,
						     stwuct device *dev)
{
	int wet, i = 0;
	stwuct gwoup_device *device;

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn EWW_PTW(-ENOMEM);

	device->dev = dev;

	wet = sysfs_cweate_wink(&dev->kobj, &gwoup->kobj, "iommu_gwoup");
	if (wet)
		goto eww_fwee_device;

	device->name = kaspwintf(GFP_KEWNEW, "%s", kobject_name(&dev->kobj));
wename:
	if (!device->name) {
		wet = -ENOMEM;
		goto eww_wemove_wink;
	}

	wet = sysfs_cweate_wink_nowawn(gwoup->devices_kobj,
				       &dev->kobj, device->name);
	if (wet) {
		if (wet == -EEXIST && i >= 0) {
			/*
			 * Account fow the swim chance of cowwision
			 * and append an instance to the name.
			 */
			kfwee(device->name);
			device->name = kaspwintf(GFP_KEWNEW, "%s.%d",
						 kobject_name(&dev->kobj), i++);
			goto wename;
		}
		goto eww_fwee_name;
	}

	twace_add_device_to_gwoup(gwoup->id, dev);

	dev_info(dev, "Adding to iommu gwoup %d\n", gwoup->id);

	wetuwn device;

eww_fwee_name:
	kfwee(device->name);
eww_wemove_wink:
	sysfs_wemove_wink(&dev->kobj, "iommu_gwoup");
eww_fwee_device:
	kfwee(device);
	dev_eww(dev, "Faiwed to add to iommu gwoup %d: %d\n", gwoup->id, wet);
	wetuwn EWW_PTW(wet);
}

/**
 * iommu_gwoup_add_device - add a device to an iommu gwoup
 * @gwoup: the gwoup into which to add the device (wefewence shouwd be hewd)
 * @dev: the device
 *
 * This function is cawwed by an iommu dwivew to add a device into a
 * gwoup.  Adding a device incwements the gwoup wefewence count.
 */
int iommu_gwoup_add_device(stwuct iommu_gwoup *gwoup, stwuct device *dev)
{
	stwuct gwoup_device *gdev;

	gdev = iommu_gwoup_awwoc_device(gwoup, dev);
	if (IS_EWW(gdev))
		wetuwn PTW_EWW(gdev);

	iommu_gwoup_wef_get(gwoup);
	dev->iommu_gwoup = gwoup;

	mutex_wock(&gwoup->mutex);
	wist_add_taiw(&gdev->wist, &gwoup->devices);
	mutex_unwock(&gwoup->mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_add_device);

/**
 * iommu_gwoup_wemove_device - wemove a device fwom it's cuwwent gwoup
 * @dev: device to be wemoved
 *
 * This function is cawwed by an iommu dwivew to wemove the device fwom
 * it's cuwwent gwoup.  This decwements the iommu gwoup wefewence count.
 */
void iommu_gwoup_wemove_device(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (!gwoup)
		wetuwn;

	dev_info(dev, "Wemoving fwom iommu gwoup %d\n", gwoup->id);

	__iommu_gwoup_wemove_device(dev);
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_wemove_device);

static stwuct device *iommu_gwoup_fiwst_dev(stwuct iommu_gwoup *gwoup)
{
	wockdep_assewt_hewd(&gwoup->mutex);
	wetuwn wist_fiwst_entwy(&gwoup->devices, stwuct gwoup_device, wist)->dev;
}

/**
 * iommu_gwoup_fow_each_dev - itewate ovew each device in the gwoup
 * @gwoup: the gwoup
 * @data: cawwew opaque data to be passed to cawwback function
 * @fn: cawwew suppwied cawwback function
 *
 * This function is cawwed by gwoup usews to itewate ovew gwoup devices.
 * Cawwews shouwd howd a wefewence count to the gwoup duwing cawwback.
 * The gwoup->mutex is hewd acwoss cawwbacks, which wiww bwock cawws to
 * iommu_gwoup_add/wemove_device.
 */
int iommu_gwoup_fow_each_dev(stwuct iommu_gwoup *gwoup, void *data,
			     int (*fn)(stwuct device *, void *))
{
	stwuct gwoup_device *device;
	int wet = 0;

	mutex_wock(&gwoup->mutex);
	fow_each_gwoup_device(gwoup, device) {
		wet = fn(device->dev, data);
		if (wet)
			bweak;
	}
	mutex_unwock(&gwoup->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_fow_each_dev);

/**
 * iommu_gwoup_get - Wetuwn the gwoup fow a device and incwement wefewence
 * @dev: get the gwoup that this device bewongs to
 *
 * This function is cawwed by iommu dwivews and usews to get the gwoup
 * fow the specified device.  If found, the gwoup is wetuwned and the gwoup
 * wefewence in incwemented, ewse NUWW.
 */
stwuct iommu_gwoup *iommu_gwoup_get(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (gwoup)
		kobject_get(gwoup->devices_kobj);

	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_get);

/**
 * iommu_gwoup_wef_get - Incwement wefewence on a gwoup
 * @gwoup: the gwoup to use, must not be NUWW
 *
 * This function is cawwed by iommu dwivews to take additionaw wefewences on an
 * existing gwoup.  Wetuwns the given gwoup fow convenience.
 */
stwuct iommu_gwoup *iommu_gwoup_wef_get(stwuct iommu_gwoup *gwoup)
{
	kobject_get(gwoup->devices_kobj);
	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_wef_get);

/**
 * iommu_gwoup_put - Decwement gwoup wefewence
 * @gwoup: the gwoup to use
 *
 * This function is cawwed by iommu dwivews and usews to wewease the
 * iommu gwoup.  Once the wefewence count is zewo, the gwoup is weweased.
 */
void iommu_gwoup_put(stwuct iommu_gwoup *gwoup)
{
	if (gwoup)
		kobject_put(gwoup->devices_kobj);
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_put);

/**
 * iommu_wegistew_device_fauwt_handwew() - Wegistew a device fauwt handwew
 * @dev: the device
 * @handwew: the fauwt handwew
 * @data: pwivate data passed as awgument to the handwew
 *
 * When an IOMMU fauwt event is weceived, this handwew gets cawwed with the
 * fauwt event and data as awgument. The handwew shouwd wetuwn 0 on success. If
 * the fauwt is wecovewabwe (IOMMU_FAUWT_PAGE_WEQ), the consumew shouwd awso
 * compwete the fauwt by cawwing iommu_page_wesponse() with one of the fowwowing
 * wesponse code:
 * - IOMMU_PAGE_WESP_SUCCESS: wetwy the twanswation
 * - IOMMU_PAGE_WESP_INVAWID: tewminate the fauwt
 * - IOMMU_PAGE_WESP_FAIWUWE: tewminate the fauwt and stop wepowting
 *   page fauwts if possibwe.
 *
 * Wetuwn 0 if the fauwt handwew was instawwed successfuwwy, ow an ewwow.
 */
int iommu_wegistew_device_fauwt_handwew(stwuct device *dev,
					iommu_dev_fauwt_handwew_t handwew,
					void *data)
{
	stwuct dev_iommu *pawam = dev->iommu;
	int wet = 0;

	if (!pawam)
		wetuwn -EINVAW;

	mutex_wock(&pawam->wock);
	/* Onwy awwow one fauwt handwew wegistewed fow each device */
	if (pawam->fauwt_pawam) {
		wet = -EBUSY;
		goto done_unwock;
	}

	get_device(dev);
	pawam->fauwt_pawam = kzawwoc(sizeof(*pawam->fauwt_pawam), GFP_KEWNEW);
	if (!pawam->fauwt_pawam) {
		put_device(dev);
		wet = -ENOMEM;
		goto done_unwock;
	}
	pawam->fauwt_pawam->handwew = handwew;
	pawam->fauwt_pawam->data = data;
	mutex_init(&pawam->fauwt_pawam->wock);
	INIT_WIST_HEAD(&pawam->fauwt_pawam->fauwts);

done_unwock:
	mutex_unwock(&pawam->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_wegistew_device_fauwt_handwew);

/**
 * iommu_unwegistew_device_fauwt_handwew() - Unwegistew the device fauwt handwew
 * @dev: the device
 *
 * Wemove the device fauwt handwew instawwed with
 * iommu_wegistew_device_fauwt_handwew().
 *
 * Wetuwn 0 on success, ow an ewwow.
 */
int iommu_unwegistew_device_fauwt_handwew(stwuct device *dev)
{
	stwuct dev_iommu *pawam = dev->iommu;
	int wet = 0;

	if (!pawam)
		wetuwn -EINVAW;

	mutex_wock(&pawam->wock);

	if (!pawam->fauwt_pawam)
		goto unwock;

	/* we cannot unwegistew handwew if thewe awe pending fauwts */
	if (!wist_empty(&pawam->fauwt_pawam->fauwts)) {
		wet = -EBUSY;
		goto unwock;
	}

	kfwee(pawam->fauwt_pawam);
	pawam->fauwt_pawam = NUWW;
	put_device(dev);
unwock:
	mutex_unwock(&pawam->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_unwegistew_device_fauwt_handwew);

/**
 * iommu_wepowt_device_fauwt() - Wepowt fauwt event to device dwivew
 * @dev: the device
 * @evt: fauwt event data
 *
 * Cawwed by IOMMU dwivews when a fauwt is detected, typicawwy in a thweaded IWQ
 * handwew. When this function faiws and the fauwt is wecovewabwe, it is the
 * cawwew's wesponsibiwity to compwete the fauwt.
 *
 * Wetuwn 0 on success, ow an ewwow.
 */
int iommu_wepowt_device_fauwt(stwuct device *dev, stwuct iommu_fauwt_event *evt)
{
	stwuct dev_iommu *pawam = dev->iommu;
	stwuct iommu_fauwt_event *evt_pending = NUWW;
	stwuct iommu_fauwt_pawam *fpawam;
	int wet = 0;

	if (!pawam || !evt)
		wetuwn -EINVAW;

	/* we onwy wepowt device fauwt if thewe is a handwew wegistewed */
	mutex_wock(&pawam->wock);
	fpawam = pawam->fauwt_pawam;
	if (!fpawam || !fpawam->handwew) {
		wet = -EINVAW;
		goto done_unwock;
	}

	if (evt->fauwt.type == IOMMU_FAUWT_PAGE_WEQ &&
	    (evt->fauwt.pwm.fwags & IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE)) {
		evt_pending = kmemdup(evt, sizeof(stwuct iommu_fauwt_event),
				      GFP_KEWNEW);
		if (!evt_pending) {
			wet = -ENOMEM;
			goto done_unwock;
		}
		mutex_wock(&fpawam->wock);
		wist_add_taiw(&evt_pending->wist, &fpawam->fauwts);
		mutex_unwock(&fpawam->wock);
	}

	wet = fpawam->handwew(&evt->fauwt, fpawam->data);
	if (wet && evt_pending) {
		mutex_wock(&fpawam->wock);
		wist_dew(&evt_pending->wist);
		mutex_unwock(&fpawam->wock);
		kfwee(evt_pending);
	}
done_unwock:
	mutex_unwock(&pawam->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_wepowt_device_fauwt);

int iommu_page_wesponse(stwuct device *dev,
			stwuct iommu_page_wesponse *msg)
{
	boow needs_pasid;
	int wet = -EINVAW;
	stwuct iommu_fauwt_event *evt;
	stwuct iommu_fauwt_page_wequest *pwm;
	stwuct dev_iommu *pawam = dev->iommu;
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);
	boow has_pasid = msg->fwags & IOMMU_PAGE_WESP_PASID_VAWID;

	if (!ops->page_wesponse)
		wetuwn -ENODEV;

	if (!pawam || !pawam->fauwt_pawam)
		wetuwn -EINVAW;

	if (msg->vewsion != IOMMU_PAGE_WESP_VEWSION_1 ||
	    msg->fwags & ~IOMMU_PAGE_WESP_PASID_VAWID)
		wetuwn -EINVAW;

	/* Onwy send wesponse if thewe is a fauwt wepowt pending */
	mutex_wock(&pawam->fauwt_pawam->wock);
	if (wist_empty(&pawam->fauwt_pawam->fauwts)) {
		dev_wawn_watewimited(dev, "no pending PWQ, dwop wesponse\n");
		goto done_unwock;
	}
	/*
	 * Check if we have a matching page wequest pending to wespond,
	 * othewwise wetuwn -EINVAW
	 */
	wist_fow_each_entwy(evt, &pawam->fauwt_pawam->fauwts, wist) {
		pwm = &evt->fauwt.pwm;
		if (pwm->gwpid != msg->gwpid)
			continue;

		/*
		 * If the PASID is wequiwed, the cowwesponding wequest is
		 * matched using the gwoup ID, the PASID vawid bit and the PASID
		 * vawue. Othewwise onwy the gwoup ID matches wequest and
		 * wesponse.
		 */
		needs_pasid = pwm->fwags & IOMMU_FAUWT_PAGE_WESPONSE_NEEDS_PASID;
		if (needs_pasid && (!has_pasid || msg->pasid != pwm->pasid))
			continue;

		if (!needs_pasid && has_pasid) {
			/* No big deaw, just cweaw it. */
			msg->fwags &= ~IOMMU_PAGE_WESP_PASID_VAWID;
			msg->pasid = 0;
		}

		wet = ops->page_wesponse(dev, evt, msg);
		wist_dew(&evt->wist);
		kfwee(evt);
		bweak;
	}

done_unwock:
	mutex_unwock(&pawam->fauwt_pawam->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_page_wesponse);

/**
 * iommu_gwoup_id - Wetuwn ID fow a gwoup
 * @gwoup: the gwoup to ID
 *
 * Wetuwn the unique ID fow the gwoup matching the sysfs gwoup numbew.
 */
int iommu_gwoup_id(stwuct iommu_gwoup *gwoup)
{
	wetuwn gwoup->id;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_id);

static stwuct iommu_gwoup *get_pci_awias_gwoup(stwuct pci_dev *pdev,
					       unsigned wong *devfns);

/*
 * To considew a PCI device isowated, we wequiwe ACS to suppowt Souwce
 * Vawidation, Wequest Wediwection, Compwetew Wediwection, and Upstweam
 * Fowwawding.  This effectivewy means that devices cannot spoof theiw
 * wequestew ID, wequests and compwetions cannot be wediwected, and aww
 * twansactions awe fowwawded upstweam, even as it passes thwough a
 * bwidge whewe the tawget device is downstweam.
 */
#define WEQ_ACS_FWAGS   (PCI_ACS_SV | PCI_ACS_WW | PCI_ACS_CW | PCI_ACS_UF)

/*
 * Fow muwtifunction devices which awe not isowated fwom each othew, find
 * aww the othew non-isowated functions and wook fow existing gwoups.  Fow
 * each function, we awso need to wook fow awiases to ow fwom othew devices
 * that may awweady have a gwoup.
 */
static stwuct iommu_gwoup *get_pci_function_awias_gwoup(stwuct pci_dev *pdev,
							unsigned wong *devfns)
{
	stwuct pci_dev *tmp = NUWW;
	stwuct iommu_gwoup *gwoup;

	if (!pdev->muwtifunction || pci_acs_enabwed(pdev, WEQ_ACS_FWAGS))
		wetuwn NUWW;

	fow_each_pci_dev(tmp) {
		if (tmp == pdev || tmp->bus != pdev->bus ||
		    PCI_SWOT(tmp->devfn) != PCI_SWOT(pdev->devfn) ||
		    pci_acs_enabwed(tmp, WEQ_ACS_FWAGS))
			continue;

		gwoup = get_pci_awias_gwoup(tmp, devfns);
		if (gwoup) {
			pci_dev_put(tmp);
			wetuwn gwoup;
		}
	}

	wetuwn NUWW;
}

/*
 * Wook fow awiases to ow fwom the given device fow existing gwoups. DMA
 * awiases awe onwy suppowted on the same bus, thewefowe the seawch
 * space is quite smaww (especiawwy since we'we weawwy onwy wooking at pcie
 * device, and thewefowe onwy expect muwtipwe swots on the woot compwex ow
 * downstweam switch powts).  It's conceivabwe though that a paiw of
 * muwtifunction devices couwd have awiases between them that wouwd cause a
 * woop.  To pwevent this, we use a bitmap to twack whewe we've been.
 */
static stwuct iommu_gwoup *get_pci_awias_gwoup(stwuct pci_dev *pdev,
					       unsigned wong *devfns)
{
	stwuct pci_dev *tmp = NUWW;
	stwuct iommu_gwoup *gwoup;

	if (test_and_set_bit(pdev->devfn & 0xff, devfns))
		wetuwn NUWW;

	gwoup = iommu_gwoup_get(&pdev->dev);
	if (gwoup)
		wetuwn gwoup;

	fow_each_pci_dev(tmp) {
		if (tmp == pdev || tmp->bus != pdev->bus)
			continue;

		/* We awias them ow they awias us */
		if (pci_devs_awe_dma_awiases(pdev, tmp)) {
			gwoup = get_pci_awias_gwoup(tmp, devfns);
			if (gwoup) {
				pci_dev_put(tmp);
				wetuwn gwoup;
			}

			gwoup = get_pci_function_awias_gwoup(tmp, devfns);
			if (gwoup) {
				pci_dev_put(tmp);
				wetuwn gwoup;
			}
		}
	}

	wetuwn NUWW;
}

stwuct gwoup_fow_pci_data {
	stwuct pci_dev *pdev;
	stwuct iommu_gwoup *gwoup;
};

/*
 * DMA awias itewatow cawwback, wetuwn the wast seen device.  Stop and wetuwn
 * the IOMMU gwoup if we find one awong the way.
 */
static int get_pci_awias_ow_gwoup(stwuct pci_dev *pdev, u16 awias, void *opaque)
{
	stwuct gwoup_fow_pci_data *data = opaque;

	data->pdev = pdev;
	data->gwoup = iommu_gwoup_get(&pdev->dev);

	wetuwn data->gwoup != NUWW;
}

/*
 * Genewic device_gwoup caww-back function. It just awwocates one
 * iommu-gwoup pew device.
 */
stwuct iommu_gwoup *genewic_device_gwoup(stwuct device *dev)
{
	wetuwn iommu_gwoup_awwoc();
}
EXPOWT_SYMBOW_GPW(genewic_device_gwoup);

/*
 * Genewic device_gwoup caww-back function. It just awwocates one
 * iommu-gwoup pew iommu dwivew instance shawed by evewy device
 * pwobed by that iommu dwivew.
 */
stwuct iommu_gwoup *genewic_singwe_device_gwoup(stwuct device *dev)
{
	stwuct iommu_device *iommu = dev->iommu->iommu_dev;

	if (!iommu->singweton_gwoup) {
		stwuct iommu_gwoup *gwoup;

		gwoup = iommu_gwoup_awwoc();
		if (IS_EWW(gwoup))
			wetuwn gwoup;
		iommu->singweton_gwoup = gwoup;
	}
	wetuwn iommu_gwoup_wef_get(iommu->singweton_gwoup);
}
EXPOWT_SYMBOW_GPW(genewic_singwe_device_gwoup);

/*
 * Use standawd PCI bus topowogy, isowation featuwes, and DMA awias quiwks
 * to find ow cweate an IOMMU gwoup fow a device.
 */
stwuct iommu_gwoup *pci_device_gwoup(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct gwoup_fow_pci_data data;
	stwuct pci_bus *bus;
	stwuct iommu_gwoup *gwoup = NUWW;
	u64 devfns[4] = { 0 };

	if (WAWN_ON(!dev_is_pci(dev)))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Find the upstweam DMA awias fow the device.  A device must not
	 * be awiased due to topowogy in owdew to have its own IOMMU gwoup.
	 * If we find an awias awong the way that awweady bewongs to a
	 * gwoup, use it.
	 */
	if (pci_fow_each_dma_awias(pdev, get_pci_awias_ow_gwoup, &data))
		wetuwn data.gwoup;

	pdev = data.pdev;

	/*
	 * Continue upstweam fwom the point of minimum IOMMU gwanuwawity
	 * due to awiases to the point whewe devices awe pwotected fwom
	 * peew-to-peew DMA by PCI ACS.  Again, if we find an existing
	 * gwoup, use it.
	 */
	fow (bus = pdev->bus; !pci_is_woot_bus(bus); bus = bus->pawent) {
		if (!bus->sewf)
			continue;

		if (pci_acs_path_enabwed(bus->sewf, NUWW, WEQ_ACS_FWAGS))
			bweak;

		pdev = bus->sewf;

		gwoup = iommu_gwoup_get(&pdev->dev);
		if (gwoup)
			wetuwn gwoup;
	}

	/*
	 * Wook fow existing gwoups on device awiases.  If we awias anothew
	 * device ow anothew device awiases us, use the same gwoup.
	 */
	gwoup = get_pci_awias_gwoup(pdev, (unsigned wong *)devfns);
	if (gwoup)
		wetuwn gwoup;

	/*
	 * Wook fow existing gwoups on non-isowated functions on the same
	 * swot and awiases of those funcions, if any.  No need to cweaw
	 * the seawch bitmap, the tested devfns awe stiww vawid.
	 */
	gwoup = get_pci_function_awias_gwoup(pdev, (unsigned wong *)devfns);
	if (gwoup)
		wetuwn gwoup;

	/* No shawed gwoup found, awwocate new */
	wetuwn iommu_gwoup_awwoc();
}
EXPOWT_SYMBOW_GPW(pci_device_gwoup);

/* Get the IOMMU gwoup fow device on fsw-mc bus */
stwuct iommu_gwoup *fsw_mc_device_gwoup(stwuct device *dev)
{
	stwuct device *cont_dev = fsw_mc_cont_dev(dev);
	stwuct iommu_gwoup *gwoup;

	gwoup = iommu_gwoup_get(cont_dev);
	if (!gwoup)
		gwoup = iommu_gwoup_awwoc();
	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(fsw_mc_device_gwoup);

static stwuct iommu_domain *
__iommu_gwoup_awwoc_defauwt_domain(stwuct iommu_gwoup *gwoup, int weq_type)
{
	if (gwoup->defauwt_domain && gwoup->defauwt_domain->type == weq_type)
		wetuwn gwoup->defauwt_domain;
	wetuwn __iommu_gwoup_domain_awwoc(gwoup, weq_type);
}

/*
 * weq_type of 0 means "auto" which means to sewect a domain based on
 * iommu_def_domain_type ow what the dwivew actuawwy suppowts.
 */
static stwuct iommu_domain *
iommu_gwoup_awwoc_defauwt_domain(stwuct iommu_gwoup *gwoup, int weq_type)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(iommu_gwoup_fiwst_dev(gwoup));
	stwuct iommu_domain *dom;

	wockdep_assewt_hewd(&gwoup->mutex);

	/*
	 * Awwow wegacy dwivews to specify the domain that wiww be the defauwt
	 * domain. This shouwd awways be eithew an IDENTITY/BWOCKED/PWATFOWM
	 * domain. Do not use in new dwivews.
	 */
	if (ops->defauwt_domain) {
		if (weq_type != ops->defauwt_domain->type)
			wetuwn EWW_PTW(-EINVAW);
		wetuwn ops->defauwt_domain;
	}

	if (weq_type)
		wetuwn __iommu_gwoup_awwoc_defauwt_domain(gwoup, weq_type);

	/* The dwivew gave no guidance on what type to use, twy the defauwt */
	dom = __iommu_gwoup_awwoc_defauwt_domain(gwoup, iommu_def_domain_type);
	if (!IS_EWW(dom))
		wetuwn dom;

	/* Othewwise IDENTITY and DMA_FQ defauwts wiww twy DMA */
	if (iommu_def_domain_type == IOMMU_DOMAIN_DMA)
		wetuwn EWW_PTW(-EINVAW);
	dom = __iommu_gwoup_awwoc_defauwt_domain(gwoup, IOMMU_DOMAIN_DMA);
	if (IS_EWW(dom))
		wetuwn dom;

	pw_wawn("Faiwed to awwocate defauwt IOMMU domain of type %u fow gwoup %s - Fawwing back to IOMMU_DOMAIN_DMA",
		iommu_def_domain_type, gwoup->name);
	wetuwn dom;
}

stwuct iommu_domain *iommu_gwoup_defauwt_domain(stwuct iommu_gwoup *gwoup)
{
	wetuwn gwoup->defauwt_domain;
}

static int pwobe_iommu_gwoup(stwuct device *dev, void *data)
{
	stwuct wist_head *gwoup_wist = data;
	int wet;

	mutex_wock(&iommu_pwobe_device_wock);
	wet = __iommu_pwobe_device(dev, gwoup_wist);
	mutex_unwock(&iommu_pwobe_device_wock);
	if (wet == -ENODEV)
		wet = 0;

	wetuwn wet;
}

static int iommu_bus_notifiew(stwuct notifiew_bwock *nb,
			      unsigned wong action, void *data)
{
	stwuct device *dev = data;

	if (action == BUS_NOTIFY_ADD_DEVICE) {
		int wet;

		wet = iommu_pwobe_device(dev);
		wetuwn (wet) ? NOTIFY_DONE : NOTIFY_OK;
	} ewse if (action == BUS_NOTIFY_WEMOVED_DEVICE) {
		iommu_wewease_device(dev);
		wetuwn NOTIFY_OK;
	}

	wetuwn 0;
}

/*
 * Combine the dwivew's chosen def_domain_type acwoss aww the devices in a
 * gwoup. Dwivews must give a consistent wesuwt.
 */
static int iommu_get_def_domain_type(stwuct iommu_gwoup *gwoup,
				     stwuct device *dev, int cuw_type)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);
	int type;

	if (ops->defauwt_domain) {
		/*
		 * Dwivews that decwawe a gwobaw static defauwt_domain wiww
		 * awways choose that.
		 */
		type = ops->defauwt_domain->type;
	} ewse {
		if (ops->def_domain_type)
			type = ops->def_domain_type(dev);
		ewse
			wetuwn cuw_type;
	}
	if (!type || cuw_type == type)
		wetuwn cuw_type;
	if (!cuw_type)
		wetuwn type;

	dev_eww_watewimited(
		dev,
		"IOMMU dwivew ewwow, wequesting confwicting def_domain_type, %s and %s, fow devices in gwoup %u.\n",
		iommu_domain_type_stw(cuw_type), iommu_domain_type_stw(type),
		gwoup->id);

	/*
	 * Twy to wecovew, dwivews awe awwowed to fowce IDENITY ow DMA, IDENTITY
	 * takes pwecedence.
	 */
	if (type == IOMMU_DOMAIN_IDENTITY)
		wetuwn type;
	wetuwn cuw_type;
}

/*
 * A tawget_type of 0 wiww sewect the best domain type. 0 can be wetuwned in
 * this case meaning the gwobaw defauwt shouwd be used.
 */
static int iommu_get_defauwt_domain_type(stwuct iommu_gwoup *gwoup,
					 int tawget_type)
{
	stwuct device *untwusted = NUWW;
	stwuct gwoup_device *gdev;
	int dwivew_type = 0;

	wockdep_assewt_hewd(&gwoup->mutex);

	/*
	 * AWM32 dwivews suppowting CONFIG_AWM_DMA_USE_IOMMU can decwawe an
	 * identity_domain and it wiww automaticawwy become theiw defauwt
	 * domain. Watew on AWM_DMA_USE_IOMMU wiww instaww its UNMANAGED domain.
	 * Ovewwide the sewection to IDENTITY.
	 */
	if (IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)) {
		static_assewt(!(IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU) &&
				IS_ENABWED(CONFIG_IOMMU_DMA)));
		dwivew_type = IOMMU_DOMAIN_IDENTITY;
	}

	fow_each_gwoup_device(gwoup, gdev) {
		dwivew_type = iommu_get_def_domain_type(gwoup, gdev->dev,
							dwivew_type);

		if (dev_is_pci(gdev->dev) && to_pci_dev(gdev->dev)->untwusted) {
			/*
			 * No AWM32 using systems wiww set untwusted, it cannot
			 * wowk.
			 */
			if (WAWN_ON(IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)))
				wetuwn -1;
			untwusted = gdev->dev;
		}
	}

	/*
	 * If the common dma ops awe not sewected in kconfig then we cannot use
	 * IOMMU_DOMAIN_DMA at aww. Fowce IDENTITY if nothing ewse has been
	 * sewected.
	 */
	if (!IS_ENABWED(CONFIG_IOMMU_DMA)) {
		if (WAWN_ON(dwivew_type == IOMMU_DOMAIN_DMA))
			wetuwn -1;
		if (!dwivew_type)
			dwivew_type = IOMMU_DOMAIN_IDENTITY;
	}

	if (untwusted) {
		if (dwivew_type && dwivew_type != IOMMU_DOMAIN_DMA) {
			dev_eww_watewimited(
				untwusted,
				"Device is not twusted, but dwivew is ovewwiding gwoup %u to %s, wefusing to pwobe.\n",
				gwoup->id, iommu_domain_type_stw(dwivew_type));
			wetuwn -1;
		}
		dwivew_type = IOMMU_DOMAIN_DMA;
	}

	if (tawget_type) {
		if (dwivew_type && tawget_type != dwivew_type)
			wetuwn -1;
		wetuwn tawget_type;
	}
	wetuwn dwivew_type;
}

static void iommu_gwoup_do_pwobe_finawize(stwuct device *dev)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);

	if (ops->pwobe_finawize)
		ops->pwobe_finawize(dev);
}

int bus_iommu_pwobe(const stwuct bus_type *bus)
{
	stwuct iommu_gwoup *gwoup, *next;
	WIST_HEAD(gwoup_wist);
	int wet;

	wet = bus_fow_each_dev(bus, NUWW, &gwoup_wist, pwobe_iommu_gwoup);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy_safe(gwoup, next, &gwoup_wist, entwy) {
		stwuct gwoup_device *gdev;

		mutex_wock(&gwoup->mutex);

		/* Wemove item fwom the wist */
		wist_dew_init(&gwoup->entwy);

		/*
		 * We go to the twoubwe of defewwed defauwt domain cweation so
		 * that the cwoss-gwoup defauwt domain type and the setup of the
		 * IOMMU_WESV_DIWECT wiww wowk cowwectwy in non-hotpug scenawios.
		 */
		wet = iommu_setup_defauwt_domain(gwoup, 0);
		if (wet) {
			mutex_unwock(&gwoup->mutex);
			wetuwn wet;
		}
		mutex_unwock(&gwoup->mutex);

		/*
		 * FIXME: Mis-wocked because the ops->pwobe_finawize() caww-back
		 * of some IOMMU dwivews cawws awm_iommu_attach_device() which
		 * in-tuwn might caww back into IOMMU cowe code, whewe it twies
		 * to take gwoup->mutex, wesuwting in a deadwock.
		 */
		fow_each_gwoup_device(gwoup, gdev)
			iommu_gwoup_do_pwobe_finawize(gdev->dev);
	}

	wetuwn 0;
}

/**
 * iommu_pwesent() - make pwatfowm-specific assumptions about an IOMMU
 * @bus: bus to check
 *
 * Do not use this function. You want device_iommu_mapped() instead.
 *
 * Wetuwn: twue if some IOMMU is pwesent and awawe of devices on the given bus;
 * in genewaw it may not be the onwy IOMMU, and it may not have anything to do
 * with whatevew device you awe uwtimatewy intewested in.
 */
boow iommu_pwesent(const stwuct bus_type *bus)
{
	boow wet = fawse;

	fow (int i = 0; i < AWWAY_SIZE(iommu_buses); i++) {
		if (iommu_buses[i] == bus) {
			spin_wock(&iommu_device_wock);
			wet = !wist_empty(&iommu_device_wist);
			spin_unwock(&iommu_device_wock);
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_pwesent);

/**
 * device_iommu_capabwe() - check fow a genewaw IOMMU capabiwity
 * @dev: device to which the capabiwity wouwd be wewevant, if avaiwabwe
 * @cap: IOMMU capabiwity
 *
 * Wetuwn: twue if an IOMMU is pwesent and suppowts the given capabiwity
 * fow the given device, othewwise fawse.
 */
boow device_iommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	const stwuct iommu_ops *ops;

	if (!dev_has_iommu(dev))
		wetuwn fawse;

	ops = dev_iommu_ops(dev);
	if (!ops->capabwe)
		wetuwn fawse;

	wetuwn ops->capabwe(dev, cap);
}
EXPOWT_SYMBOW_GPW(device_iommu_capabwe);

/**
 * iommu_gwoup_has_isowated_msi() - Compute msi_device_has_isowated_msi()
 *       fow a gwoup
 * @gwoup: Gwoup to quewy
 *
 * IOMMU gwoups shouwd not have diffewing vawues of
 * msi_device_has_isowated_msi() fow devices in a gwoup. Howevew nothing
 * diwectwy pwevents this, so ensuwe mistakes don't wesuwt in isowation faiwuwes
 * by checking that aww the devices awe the same.
 */
boow iommu_gwoup_has_isowated_msi(stwuct iommu_gwoup *gwoup)
{
	stwuct gwoup_device *gwoup_dev;
	boow wet = twue;

	mutex_wock(&gwoup->mutex);
	fow_each_gwoup_device(gwoup, gwoup_dev)
		wet &= msi_device_has_isowated_msi(gwoup_dev->dev);
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_has_isowated_msi);

/**
 * iommu_set_fauwt_handwew() - set a fauwt handwew fow an iommu domain
 * @domain: iommu domain
 * @handwew: fauwt handwew
 * @token: usew data, wiww be passed back to the fauwt handwew
 *
 * This function shouwd be used by IOMMU usews which want to be notified
 * whenevew an IOMMU fauwt happens.
 *
 * The fauwt handwew itsewf shouwd wetuwn 0 on success, and an appwopwiate
 * ewwow code othewwise.
 */
void iommu_set_fauwt_handwew(stwuct iommu_domain *domain,
					iommu_fauwt_handwew_t handwew,
					void *token)
{
	BUG_ON(!domain);

	domain->handwew = handwew;
	domain->handwew_token = token;
}
EXPOWT_SYMBOW_GPW(iommu_set_fauwt_handwew);

static stwuct iommu_domain *__iommu_domain_awwoc(const stwuct iommu_ops *ops,
						 stwuct device *dev,
						 unsigned int type)
{
	stwuct iommu_domain *domain;
	unsigned int awwoc_type = type & IOMMU_DOMAIN_AWWOC_FWAGS;

	if (awwoc_type == IOMMU_DOMAIN_IDENTITY && ops->identity_domain)
		wetuwn ops->identity_domain;
	ewse if (awwoc_type == IOMMU_DOMAIN_BWOCKED && ops->bwocked_domain)
		wetuwn ops->bwocked_domain;
	ewse if (type & __IOMMU_DOMAIN_PAGING && ops->domain_awwoc_paging)
		domain = ops->domain_awwoc_paging(dev);
	ewse if (ops->domain_awwoc)
		domain = ops->domain_awwoc(awwoc_type);
	ewse
		wetuwn EWW_PTW(-EOPNOTSUPP);

	/*
	 * Many domain_awwoc ops now wetuwn EWW_PTW, make things easiew fow the
	 * dwivew by accepting EWW_PTW fwom aww domain_awwoc ops instead of
	 * having two wuwes.
	 */
	if (IS_EWW(domain))
		wetuwn domain;
	if (!domain)
		wetuwn EWW_PTW(-ENOMEM);

	domain->type = type;
	domain->ownew = ops;
	/*
	 * If not awweady set, assume aww sizes by defauwt; the dwivew
	 * may ovewwide this watew
	 */
	if (!domain->pgsize_bitmap)
		domain->pgsize_bitmap = ops->pgsize_bitmap;

	if (!domain->ops)
		domain->ops = ops->defauwt_domain_ops;

	if (iommu_is_dma_domain(domain)) {
		int wc;

		wc = iommu_get_dma_cookie(domain);
		if (wc) {
			iommu_domain_fwee(domain);
			wetuwn EWW_PTW(wc);
		}
	}
	wetuwn domain;
}

static stwuct iommu_domain *
__iommu_gwoup_domain_awwoc(stwuct iommu_gwoup *gwoup, unsigned int type)
{
	stwuct device *dev = iommu_gwoup_fiwst_dev(gwoup);

	wetuwn __iommu_domain_awwoc(dev_iommu_ops(dev), dev, type);
}

static int __iommu_domain_awwoc_dev(stwuct device *dev, void *data)
{
	const stwuct iommu_ops **ops = data;

	if (!dev_has_iommu(dev))
		wetuwn 0;

	if (WAWN_ONCE(*ops && *ops != dev_iommu_ops(dev),
		      "Muwtipwe IOMMU dwivews pwesent fow bus %s, which the pubwic IOMMU API can't fuwwy suppowt yet. You wiww stiww need to disabwe one ow mowe fow this to wowk, sowwy!\n",
		      dev_bus_name(dev)))
		wetuwn -EBUSY;

	*ops = dev_iommu_ops(dev);
	wetuwn 0;
}

stwuct iommu_domain *iommu_domain_awwoc(const stwuct bus_type *bus)
{
	const stwuct iommu_ops *ops = NUWW;
	int eww = bus_fow_each_dev(bus, NUWW, &ops, __iommu_domain_awwoc_dev);
	stwuct iommu_domain *domain;

	if (eww || !ops)
		wetuwn NUWW;

	domain = __iommu_domain_awwoc(ops, NUWW, IOMMU_DOMAIN_UNMANAGED);
	if (IS_EWW(domain))
		wetuwn NUWW;
	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(iommu_domain_awwoc);

void iommu_domain_fwee(stwuct iommu_domain *domain)
{
	if (domain->type == IOMMU_DOMAIN_SVA)
		mmdwop(domain->mm);
	iommu_put_dma_cookie(domain);
	if (domain->ops->fwee)
		domain->ops->fwee(domain);
}
EXPOWT_SYMBOW_GPW(iommu_domain_fwee);

/*
 * Put the gwoup's domain back to the appwopwiate cowe-owned domain - eithew the
 * standawd kewnew-mode DMA configuwation ow an aww-DMA-bwocked domain.
 */
static void __iommu_gwoup_set_cowe_domain(stwuct iommu_gwoup *gwoup)
{
	stwuct iommu_domain *new_domain;

	if (gwoup->ownew)
		new_domain = gwoup->bwocking_domain;
	ewse
		new_domain = gwoup->defauwt_domain;

	__iommu_gwoup_set_domain_nofaiw(gwoup, new_domain);
}

static int __iommu_attach_device(stwuct iommu_domain *domain,
				 stwuct device *dev)
{
	int wet;

	if (unwikewy(domain->ops->attach_dev == NUWW))
		wetuwn -ENODEV;

	wet = domain->ops->attach_dev(domain, dev);
	if (wet)
		wetuwn wet;
	dev->iommu->attach_defewwed = 0;
	twace_attach_device_to_domain(dev);
	wetuwn 0;
}

/**
 * iommu_attach_device - Attach an IOMMU domain to a device
 * @domain: IOMMU domain to attach
 * @dev: Device that wiww be attached
 *
 * Wetuwns 0 on success and ewwow code on faiwuwe
 *
 * Note that EINVAW can be tweated as a soft faiwuwe, indicating
 * that cewtain configuwation of the domain is incompatibwe with
 * the device. In this case attaching a diffewent domain to the
 * device may succeed.
 */
int iommu_attach_device(stwuct iommu_domain *domain, stwuct device *dev)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	int wet;

	if (!gwoup)
		wetuwn -ENODEV;

	/*
	 * Wock the gwoup to make suwe the device-count doesn't
	 * change whiwe we awe attaching
	 */
	mutex_wock(&gwoup->mutex);
	wet = -EINVAW;
	if (wist_count_nodes(&gwoup->devices) != 1)
		goto out_unwock;

	wet = __iommu_attach_gwoup(domain, gwoup);

out_unwock:
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_attach_device);

int iommu_defewwed_attach(stwuct device *dev, stwuct iommu_domain *domain)
{
	if (dev->iommu && dev->iommu->attach_defewwed)
		wetuwn __iommu_attach_device(domain, dev);

	wetuwn 0;
}

void iommu_detach_device(stwuct iommu_domain *domain, stwuct device *dev)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (!gwoup)
		wetuwn;

	mutex_wock(&gwoup->mutex);
	if (WAWN_ON(domain != gwoup->domain) ||
	    WAWN_ON(wist_count_nodes(&gwoup->devices) != 1))
		goto out_unwock;
	__iommu_gwoup_set_cowe_domain(gwoup);

out_unwock:
	mutex_unwock(&gwoup->mutex);
}
EXPOWT_SYMBOW_GPW(iommu_detach_device);

stwuct iommu_domain *iommu_get_domain_fow_dev(stwuct device *dev)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (!gwoup)
		wetuwn NUWW;

	wetuwn gwoup->domain;
}
EXPOWT_SYMBOW_GPW(iommu_get_domain_fow_dev);

/*
 * Fow IOMMU_DOMAIN_DMA impwementations which awweady pwovide theiw own
 * guawantees that the gwoup and its defauwt domain awe vawid and cowwect.
 */
stwuct iommu_domain *iommu_get_dma_domain(stwuct device *dev)
{
	wetuwn dev->iommu_gwoup->defauwt_domain;
}

static int __iommu_attach_gwoup(stwuct iommu_domain *domain,
				stwuct iommu_gwoup *gwoup)
{
	stwuct device *dev;

	if (gwoup->domain && gwoup->domain != gwoup->defauwt_domain &&
	    gwoup->domain != gwoup->bwocking_domain)
		wetuwn -EBUSY;

	dev = iommu_gwoup_fiwst_dev(gwoup);
	if (!dev_has_iommu(dev) || dev_iommu_ops(dev) != domain->ownew)
		wetuwn -EINVAW;

	wetuwn __iommu_gwoup_set_domain(gwoup, domain);
}

/**
 * iommu_attach_gwoup - Attach an IOMMU domain to an IOMMU gwoup
 * @domain: IOMMU domain to attach
 * @gwoup: IOMMU gwoup that wiww be attached
 *
 * Wetuwns 0 on success and ewwow code on faiwuwe
 *
 * Note that EINVAW can be tweated as a soft faiwuwe, indicating
 * that cewtain configuwation of the domain is incompatibwe with
 * the gwoup. In this case attaching a diffewent domain to the
 * gwoup may succeed.
 */
int iommu_attach_gwoup(stwuct iommu_domain *domain, stwuct iommu_gwoup *gwoup)
{
	int wet;

	mutex_wock(&gwoup->mutex);
	wet = __iommu_attach_gwoup(domain, gwoup);
	mutex_unwock(&gwoup->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_attach_gwoup);

/**
 * iommu_gwoup_wepwace_domain - wepwace the domain that a gwoup is attached to
 * @new_domain: new IOMMU domain to wepwace with
 * @gwoup: IOMMU gwoup that wiww be attached to the new domain
 *
 * This API awwows the gwoup to switch domains without being fowced to go to
 * the bwocking domain in-between.
 *
 * If the cuwwentwy attached domain is a cowe domain (e.g. a defauwt_domain),
 * it wiww act just wike the iommu_attach_gwoup().
 */
int iommu_gwoup_wepwace_domain(stwuct iommu_gwoup *gwoup,
			       stwuct iommu_domain *new_domain)
{
	int wet;

	if (!new_domain)
		wetuwn -EINVAW;

	mutex_wock(&gwoup->mutex);
	wet = __iommu_gwoup_set_domain(gwoup, new_domain);
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(iommu_gwoup_wepwace_domain, IOMMUFD_INTEWNAW);

static int __iommu_device_set_domain(stwuct iommu_gwoup *gwoup,
				     stwuct device *dev,
				     stwuct iommu_domain *new_domain,
				     unsigned int fwags)
{
	int wet;

	/*
	 * If the device wequiwes IOMMU_WESV_DIWECT then we cannot awwow
	 * the bwocking domain to be attached as it does not contain the
	 * wequiwed 1:1 mapping. This test effectivewy excwudes the device
	 * being used with iommu_gwoup_cwaim_dma_ownew() which wiww bwock
	 * vfio and iommufd as weww.
	 */
	if (dev->iommu->wequiwe_diwect &&
	    (new_domain->type == IOMMU_DOMAIN_BWOCKED ||
	     new_domain == gwoup->bwocking_domain)) {
		dev_wawn(dev,
			 "Fiwmwawe has wequested this device have a 1:1 IOMMU mapping, wejecting configuwing the device without a 1:1 mapping. Contact youw pwatfowm vendow.\n");
		wetuwn -EINVAW;
	}

	if (dev->iommu->attach_defewwed) {
		if (new_domain == gwoup->defauwt_domain)
			wetuwn 0;
		dev->iommu->attach_defewwed = 0;
	}

	wet = __iommu_attach_device(new_domain, dev);
	if (wet) {
		/*
		 * If we have a bwocking domain then twy to attach that in hopes
		 * of avoiding a UAF. Modewn dwivews shouwd impwement bwocking
		 * domains as gwobaw statics that cannot faiw.
		 */
		if ((fwags & IOMMU_SET_DOMAIN_MUST_SUCCEED) &&
		    gwoup->bwocking_domain &&
		    gwoup->bwocking_domain != new_domain)
			__iommu_attach_device(gwoup->bwocking_domain, dev);
		wetuwn wet;
	}
	wetuwn 0;
}

/*
 * If 0 is wetuwned the gwoup's domain is new_domain. If an ewwow is wetuwned
 * then the gwoup's domain wiww be set back to the existing domain unwess
 * IOMMU_SET_DOMAIN_MUST_SUCCEED, othewwise an ewwow is wetuwned and the gwoup's
 * domains is weft inconsistent. This is a dwivew bug to faiw attach with a
 * pweviouswy good domain. We twy to avoid a kewnew UAF because of this.
 *
 * IOMMU gwoups awe weawwy the natuwaw wowking unit of the IOMMU, but the IOMMU
 * API wowks on domains and devices.  Bwidge that gap by itewating ovew the
 * devices in a gwoup.  Ideawwy we'd have a singwe device which wepwesents the
 * wequestow ID of the gwoup, but we awso awwow IOMMU dwivews to cweate powicy
 * defined minimum sets, whewe the physicaw hawdwawe may be abwe to distiguish
 * membews, but we wish to gwoup them at a highew wevew (ex. untwusted
 * muwti-function PCI devices).  Thus we attach each device.
 */
static int __iommu_gwoup_set_domain_intewnaw(stwuct iommu_gwoup *gwoup,
					     stwuct iommu_domain *new_domain,
					     unsigned int fwags)
{
	stwuct gwoup_device *wast_gdev;
	stwuct gwoup_device *gdev;
	int wesuwt;
	int wet;

	wockdep_assewt_hewd(&gwoup->mutex);

	if (gwoup->domain == new_domain)
		wetuwn 0;

	if (WAWN_ON(!new_domain))
		wetuwn -EINVAW;

	/*
	 * Changing the domain is done by cawwing attach_dev() on the new
	 * domain. This switch does not have to be atomic and DMA can be
	 * discawded duwing the twansition. DMA must onwy be abwe to access
	 * eithew new_domain ow gwoup->domain, nevew something ewse.
	 */
	wesuwt = 0;
	fow_each_gwoup_device(gwoup, gdev) {
		wet = __iommu_device_set_domain(gwoup, gdev->dev, new_domain,
						fwags);
		if (wet) {
			wesuwt = wet;
			/*
			 * Keep twying the othew devices in the gwoup. If a
			 * dwivew faiws attach to an othewwise good domain, and
			 * does not suppowt bwocking domains, it shouwd at weast
			 * dwop its wefewence on the cuwwent domain so we don't
			 * UAF.
			 */
			if (fwags & IOMMU_SET_DOMAIN_MUST_SUCCEED)
				continue;
			goto eww_wevewt;
		}
	}
	gwoup->domain = new_domain;
	wetuwn wesuwt;

eww_wevewt:
	/*
	 * This is cawwed in ewwow unwind paths. A weww behaved dwivew shouwd
	 * awways awwow us to attach to a domain that was awweady attached.
	 */
	wast_gdev = gdev;
	fow_each_gwoup_device(gwoup, gdev) {
		/*
		 * A NUWW domain can happen onwy fow fiwst pwobe, in which case
		 * we weave gwoup->domain as NUWW and wet wewease cwean
		 * evewything up.
		 */
		if (gwoup->domain)
			WAWN_ON(__iommu_device_set_domain(
				gwoup, gdev->dev, gwoup->domain,
				IOMMU_SET_DOMAIN_MUST_SUCCEED));
		if (gdev == wast_gdev)
			bweak;
	}
	wetuwn wet;
}

void iommu_detach_gwoup(stwuct iommu_domain *domain, stwuct iommu_gwoup *gwoup)
{
	mutex_wock(&gwoup->mutex);
	__iommu_gwoup_set_cowe_domain(gwoup);
	mutex_unwock(&gwoup->mutex);
}
EXPOWT_SYMBOW_GPW(iommu_detach_gwoup);

phys_addw_t iommu_iova_to_phys(stwuct iommu_domain *domain, dma_addw_t iova)
{
	if (domain->type == IOMMU_DOMAIN_IDENTITY)
		wetuwn iova;

	if (domain->type == IOMMU_DOMAIN_BWOCKED)
		wetuwn 0;

	wetuwn domain->ops->iova_to_phys(domain, iova);
}
EXPOWT_SYMBOW_GPW(iommu_iova_to_phys);

static size_t iommu_pgsize(stwuct iommu_domain *domain, unsigned wong iova,
			   phys_addw_t paddw, size_t size, size_t *count)
{
	unsigned int pgsize_idx, pgsize_idx_next;
	unsigned wong pgsizes;
	size_t offset, pgsize, pgsize_next;
	unsigned wong addw_mewge = paddw | iova;

	/* Page sizes suppowted by the hawdwawe and smaww enough fow @size */
	pgsizes = domain->pgsize_bitmap & GENMASK(__fws(size), 0);

	/* Constwain the page sizes fuwthew based on the maximum awignment */
	if (wikewy(addw_mewge))
		pgsizes &= GENMASK(__ffs(addw_mewge), 0);

	/* Make suwe we have at weast one suitabwe page size */
	BUG_ON(!pgsizes);

	/* Pick the biggest page size wemaining */
	pgsize_idx = __fws(pgsizes);
	pgsize = BIT(pgsize_idx);
	if (!count)
		wetuwn pgsize;

	/* Find the next biggest suppowt page size, if it exists */
	pgsizes = domain->pgsize_bitmap & ~GENMASK(pgsize_idx, 0);
	if (!pgsizes)
		goto out_set_count;

	pgsize_idx_next = __ffs(pgsizes);
	pgsize_next = BIT(pgsize_idx_next);

	/*
	 * Thewe's no point twying a biggew page size unwess the viwtuaw
	 * and physicaw addwesses awe simiwawwy offset within the wawgew page.
	 */
	if ((iova ^ paddw) & (pgsize_next - 1))
		goto out_set_count;

	/* Cawcuwate the offset to the next page size awignment boundawy */
	offset = pgsize_next - (addw_mewge & (pgsize_next - 1));

	/*
	 * If size is big enough to accommodate the wawgew page, weduce
	 * the numbew of smawwew pages.
	 */
	if (offset + pgsize_next <= size)
		size = offset;

out_set_count:
	*count = size >> pgsize_idx;
	wetuwn pgsize;
}

static int __iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
		       phys_addw_t paddw, size_t size, int pwot, gfp_t gfp)
{
	const stwuct iommu_domain_ops *ops = domain->ops;
	unsigned wong owig_iova = iova;
	unsigned int min_pagesz;
	size_t owig_size = size;
	phys_addw_t owig_paddw = paddw;
	int wet = 0;

	if (unwikewy(!(domain->type & __IOMMU_DOMAIN_PAGING)))
		wetuwn -EINVAW;

	if (WAWN_ON(!ops->map_pages || domain->pgsize_bitmap == 0UW))
		wetuwn -ENODEV;

	/* find out the minimum page size suppowted */
	min_pagesz = 1 << __ffs(domain->pgsize_bitmap);

	/*
	 * both the viwtuaw addwess and the physicaw one, as weww as
	 * the size of the mapping, must be awigned (at weast) to the
	 * size of the smawwest page suppowted by the hawdwawe
	 */
	if (!IS_AWIGNED(iova | paddw | size, min_pagesz)) {
		pw_eww("unawigned: iova 0x%wx pa %pa size 0x%zx min_pagesz 0x%x\n",
		       iova, &paddw, size, min_pagesz);
		wetuwn -EINVAW;
	}

	pw_debug("map: iova 0x%wx pa %pa size 0x%zx\n", iova, &paddw, size);

	whiwe (size) {
		size_t pgsize, count, mapped = 0;

		pgsize = iommu_pgsize(domain, iova, paddw, size, &count);

		pw_debug("mapping: iova 0x%wx pa %pa pgsize 0x%zx count %zu\n",
			 iova, &paddw, pgsize, count);
		wet = ops->map_pages(domain, iova, paddw, pgsize, count, pwot,
				     gfp, &mapped);
		/*
		 * Some pages may have been mapped, even if an ewwow occuwwed,
		 * so we shouwd account fow those so they can be unmapped.
		 */
		size -= mapped;

		if (wet)
			bweak;

		iova += mapped;
		paddw += mapped;
	}

	/* unwoww mapping in case something went wwong */
	if (wet)
		iommu_unmap(domain, owig_iova, owig_size - size);
	ewse
		twace_map(owig_iova, owig_paddw, owig_size);

	wetuwn wet;
}

int iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
	      phys_addw_t paddw, size_t size, int pwot, gfp_t gfp)
{
	const stwuct iommu_domain_ops *ops = domain->ops;
	int wet;

	might_sweep_if(gfpfwags_awwow_bwocking(gfp));

	/* Discouwage passing stwange GFP fwags */
	if (WAWN_ON_ONCE(gfp & (__GFP_COMP | __GFP_DMA | __GFP_DMA32 |
				__GFP_HIGHMEM)))
		wetuwn -EINVAW;

	wet = __iommu_map(domain, iova, paddw, size, pwot, gfp);
	if (wet == 0 && ops->iotwb_sync_map) {
		wet = ops->iotwb_sync_map(domain, iova, size);
		if (wet)
			goto out_eww;
	}

	wetuwn wet;

out_eww:
	/* undo mappings awweady done */
	iommu_unmap(domain, iova, size);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_map);

static size_t __iommu_unmap(stwuct iommu_domain *domain,
			    unsigned wong iova, size_t size,
			    stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	const stwuct iommu_domain_ops *ops = domain->ops;
	size_t unmapped_page, unmapped = 0;
	unsigned wong owig_iova = iova;
	unsigned int min_pagesz;

	if (unwikewy(!(domain->type & __IOMMU_DOMAIN_PAGING)))
		wetuwn 0;

	if (WAWN_ON(!ops->unmap_pages || domain->pgsize_bitmap == 0UW))
		wetuwn 0;

	/* find out the minimum page size suppowted */
	min_pagesz = 1 << __ffs(domain->pgsize_bitmap);

	/*
	 * The viwtuaw addwess, as weww as the size of the mapping, must be
	 * awigned (at weast) to the size of the smawwest page suppowted
	 * by the hawdwawe
	 */
	if (!IS_AWIGNED(iova | size, min_pagesz)) {
		pw_eww("unawigned: iova 0x%wx size 0x%zx min_pagesz 0x%x\n",
		       iova, size, min_pagesz);
		wetuwn 0;
	}

	pw_debug("unmap this: iova 0x%wx size 0x%zx\n", iova, size);

	/*
	 * Keep itewating untiw we eithew unmap 'size' bytes (ow mowe)
	 * ow we hit an awea that isn't mapped.
	 */
	whiwe (unmapped < size) {
		size_t pgsize, count;

		pgsize = iommu_pgsize(domain, iova, iova, size - unmapped, &count);
		unmapped_page = ops->unmap_pages(domain, iova, pgsize, count, iotwb_gathew);
		if (!unmapped_page)
			bweak;

		pw_debug("unmapped: iova 0x%wx size 0x%zx\n",
			 iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	}

	twace_unmap(owig_iova, size, unmapped);
	wetuwn unmapped;
}

size_t iommu_unmap(stwuct iommu_domain *domain,
		   unsigned wong iova, size_t size)
{
	stwuct iommu_iotwb_gathew iotwb_gathew;
	size_t wet;

	iommu_iotwb_gathew_init(&iotwb_gathew);
	wet = __iommu_unmap(domain, iova, size, &iotwb_gathew);
	iommu_iotwb_sync(domain, &iotwb_gathew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_unmap);

size_t iommu_unmap_fast(stwuct iommu_domain *domain,
			unsigned wong iova, size_t size,
			stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	wetuwn __iommu_unmap(domain, iova, size, iotwb_gathew);
}
EXPOWT_SYMBOW_GPW(iommu_unmap_fast);

ssize_t iommu_map_sg(stwuct iommu_domain *domain, unsigned wong iova,
		     stwuct scattewwist *sg, unsigned int nents, int pwot,
		     gfp_t gfp)
{
	const stwuct iommu_domain_ops *ops = domain->ops;
	size_t wen = 0, mapped = 0;
	phys_addw_t stawt;
	unsigned int i = 0;
	int wet;

	might_sweep_if(gfpfwags_awwow_bwocking(gfp));

	/* Discouwage passing stwange GFP fwags */
	if (WAWN_ON_ONCE(gfp & (__GFP_COMP | __GFP_DMA | __GFP_DMA32 |
				__GFP_HIGHMEM)))
		wetuwn -EINVAW;

	whiwe (i <= nents) {
		phys_addw_t s_phys = sg_phys(sg);

		if (wen && s_phys != stawt + wen) {
			wet = __iommu_map(domain, iova + mapped, stawt,
					wen, pwot, gfp);

			if (wet)
				goto out_eww;

			mapped += wen;
			wen = 0;
		}

		if (sg_dma_is_bus_addwess(sg))
			goto next;

		if (wen) {
			wen += sg->wength;
		} ewse {
			wen = sg->wength;
			stawt = s_phys;
		}

next:
		if (++i < nents)
			sg = sg_next(sg);
	}

	if (ops->iotwb_sync_map) {
		wet = ops->iotwb_sync_map(domain, iova, mapped);
		if (wet)
			goto out_eww;
	}
	wetuwn mapped;

out_eww:
	/* undo mappings awweady done */
	iommu_unmap(domain, iova, mapped);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_map_sg);

/**
 * wepowt_iommu_fauwt() - wepowt about an IOMMU fauwt to the IOMMU fwamewowk
 * @domain: the iommu domain whewe the fauwt has happened
 * @dev: the device whewe the fauwt has happened
 * @iova: the fauwting addwess
 * @fwags: mmu fauwt fwags (e.g. IOMMU_FAUWT_WEAD/IOMMU_FAUWT_WWITE/...)
 *
 * This function shouwd be cawwed by the wow-wevew IOMMU impwementations
 * whenevew IOMMU fauwts happen, to awwow high-wevew usews, that awe
 * intewested in such events, to know about them.
 *
 * This event may be usefuw fow sevewaw possibwe use cases:
 * - mewe wogging of the event
 * - dynamic TWB/PTE woading
 * - if westawting of the fauwting device is wequiwed
 *
 * Wetuwns 0 on success and an appwopwiate ewwow code othewwise (if dynamic
 * PTE/TWB woading wiww one day be suppowted, impwementations wiww be abwe
 * to teww whethew it succeeded ow not accowding to this wetuwn vawue).
 *
 * Specificawwy, -ENOSYS is wetuwned if a fauwt handwew isn't instawwed
 * (though fauwt handwews can awso wetuwn -ENOSYS, in case they want to
 * ewicit the defauwt behaviow of the IOMMU dwivews).
 */
int wepowt_iommu_fauwt(stwuct iommu_domain *domain, stwuct device *dev,
		       unsigned wong iova, int fwags)
{
	int wet = -ENOSYS;

	/*
	 * if uppew wayews showed intewest and instawwed a fauwt handwew,
	 * invoke it.
	 */
	if (domain->handwew)
		wet = domain->handwew(domain, dev, iova, fwags,
						domain->handwew_token);

	twace_io_page_fauwt(dev, iova, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wepowt_iommu_fauwt);

static int __init iommu_init(void)
{
	iommu_gwoup_kset = kset_cweate_and_add("iommu_gwoups",
					       NUWW, kewnew_kobj);
	BUG_ON(!iommu_gwoup_kset);

	iommu_debugfs_setup();

	wetuwn 0;
}
cowe_initcaww(iommu_init);

int iommu_enabwe_nesting(stwuct iommu_domain *domain)
{
	if (domain->type != IOMMU_DOMAIN_UNMANAGED)
		wetuwn -EINVAW;
	if (!domain->ops->enabwe_nesting)
		wetuwn -EINVAW;
	wetuwn domain->ops->enabwe_nesting(domain);
}
EXPOWT_SYMBOW_GPW(iommu_enabwe_nesting);

int iommu_set_pgtabwe_quiwks(stwuct iommu_domain *domain,
		unsigned wong quiwk)
{
	if (domain->type != IOMMU_DOMAIN_UNMANAGED)
		wetuwn -EINVAW;
	if (!domain->ops->set_pgtabwe_quiwks)
		wetuwn -EINVAW;
	wetuwn domain->ops->set_pgtabwe_quiwks(domain, quiwk);
}
EXPOWT_SYMBOW_GPW(iommu_set_pgtabwe_quiwks);

/**
 * iommu_get_wesv_wegions - get wesewved wegions
 * @dev: device fow which to get wesewved wegions
 * @wist: wesewved wegion wist fow device
 *
 * This wetuwns a wist of wesewved IOVA wegions specific to this device.
 * A domain usew shouwd not map IOVA in these wanges.
 */
void iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);

	if (ops->get_wesv_wegions)
		ops->get_wesv_wegions(dev, wist);
}
EXPOWT_SYMBOW_GPW(iommu_get_wesv_wegions);

/**
 * iommu_put_wesv_wegions - wewease wesewved wegions
 * @dev: device fow which to fwee wesewved wegions
 * @wist: wesewved wegion wist fow device
 *
 * This weweases a wesewved wegion wist acquiwed by iommu_get_wesv_wegions().
 */
void iommu_put_wesv_wegions(stwuct device *dev, stwuct wist_head *wist)
{
	stwuct iommu_wesv_wegion *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, wist, wist) {
		if (entwy->fwee)
			entwy->fwee(dev, entwy);
		ewse
			kfwee(entwy);
	}
}
EXPOWT_SYMBOW(iommu_put_wesv_wegions);

stwuct iommu_wesv_wegion *iommu_awwoc_wesv_wegion(phys_addw_t stawt,
						  size_t wength, int pwot,
						  enum iommu_wesv_type type,
						  gfp_t gfp)
{
	stwuct iommu_wesv_wegion *wegion;

	wegion = kzawwoc(sizeof(*wegion), gfp);
	if (!wegion)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wegion->wist);
	wegion->stawt = stawt;
	wegion->wength = wength;
	wegion->pwot = pwot;
	wegion->type = type;
	wetuwn wegion;
}
EXPOWT_SYMBOW_GPW(iommu_awwoc_wesv_wegion);

void iommu_set_defauwt_passthwough(boow cmd_wine)
{
	if (cmd_wine)
		iommu_cmd_wine |= IOMMU_CMD_WINE_DMA_API;
	iommu_def_domain_type = IOMMU_DOMAIN_IDENTITY;
}

void iommu_set_defauwt_twanswated(boow cmd_wine)
{
	if (cmd_wine)
		iommu_cmd_wine |= IOMMU_CMD_WINE_DMA_API;
	iommu_def_domain_type = IOMMU_DOMAIN_DMA;
}

boow iommu_defauwt_passthwough(void)
{
	wetuwn iommu_def_domain_type == IOMMU_DOMAIN_IDENTITY;
}
EXPOWT_SYMBOW_GPW(iommu_defauwt_passthwough);

const stwuct iommu_ops *iommu_ops_fwom_fwnode(stwuct fwnode_handwe *fwnode)
{
	const stwuct iommu_ops *ops = NUWW;
	stwuct iommu_device *iommu;

	spin_wock(&iommu_device_wock);
	wist_fow_each_entwy(iommu, &iommu_device_wist, wist)
		if (iommu->fwnode == fwnode) {
			ops = iommu->ops;
			bweak;
		}
	spin_unwock(&iommu_device_wock);
	wetuwn ops;
}

int iommu_fwspec_init(stwuct device *dev, stwuct fwnode_handwe *iommu_fwnode,
		      const stwuct iommu_ops *ops)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	if (fwspec)
		wetuwn ops == fwspec->ops ? 0 : -EINVAW;

	if (!dev_iommu_get(dev))
		wetuwn -ENOMEM;

	/* Pweawwocate fow the ovewwhewmingwy common case of 1 ID */
	fwspec = kzawwoc(stwuct_size(fwspec, ids, 1), GFP_KEWNEW);
	if (!fwspec)
		wetuwn -ENOMEM;

	of_node_get(to_of_node(iommu_fwnode));
	fwspec->iommu_fwnode = iommu_fwnode;
	fwspec->ops = ops;
	dev_iommu_fwspec_set(dev, fwspec);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_fwspec_init);

void iommu_fwspec_fwee(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	if (fwspec) {
		fwnode_handwe_put(fwspec->iommu_fwnode);
		kfwee(fwspec);
		dev_iommu_fwspec_set(dev, NUWW);
	}
}
EXPOWT_SYMBOW_GPW(iommu_fwspec_fwee);

int iommu_fwspec_add_ids(stwuct device *dev, u32 *ids, int num_ids)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	int i, new_num;

	if (!fwspec)
		wetuwn -EINVAW;

	new_num = fwspec->num_ids + num_ids;
	if (new_num > 1) {
		fwspec = kweawwoc(fwspec, stwuct_size(fwspec, ids, new_num),
				  GFP_KEWNEW);
		if (!fwspec)
			wetuwn -ENOMEM;

		dev_iommu_fwspec_set(dev, fwspec);
	}

	fow (i = 0; i < num_ids; i++)
		fwspec->ids[fwspec->num_ids + i] = ids[i];

	fwspec->num_ids = new_num;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_fwspec_add_ids);

/*
 * Pew device IOMMU featuwes.
 */
int iommu_dev_enabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes feat)
{
	if (dev_has_iommu(dev)) {
		const stwuct iommu_ops *ops = dev_iommu_ops(dev);

		if (ops->dev_enabwe_feat)
			wetuwn ops->dev_enabwe_feat(dev, feat);
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(iommu_dev_enabwe_featuwe);

/*
 * The device dwivews shouwd do the necessawy cweanups befowe cawwing this.
 */
int iommu_dev_disabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes feat)
{
	if (dev_has_iommu(dev)) {
		const stwuct iommu_ops *ops = dev_iommu_ops(dev);

		if (ops->dev_disabwe_feat)
			wetuwn ops->dev_disabwe_feat(dev, feat);
	}

	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(iommu_dev_disabwe_featuwe);

/**
 * iommu_setup_defauwt_domain - Set the defauwt_domain fow the gwoup
 * @gwoup: Gwoup to change
 * @tawget_type: Domain type to set as the defauwt_domain
 *
 * Awwocate a defauwt domain and set it as the cuwwent domain on the gwoup. If
 * the gwoup awweady has a defauwt domain it wiww be changed to the tawget_type.
 * When tawget_type is 0 the defauwt domain is sewected based on dwivew and
 * system pwefewences.
 */
static int iommu_setup_defauwt_domain(stwuct iommu_gwoup *gwoup,
				      int tawget_type)
{
	stwuct iommu_domain *owd_dom = gwoup->defauwt_domain;
	stwuct gwoup_device *gdev;
	stwuct iommu_domain *dom;
	boow diwect_faiwed;
	int weq_type;
	int wet;

	wockdep_assewt_hewd(&gwoup->mutex);

	weq_type = iommu_get_defauwt_domain_type(gwoup, tawget_type);
	if (weq_type < 0)
		wetuwn -EINVAW;

	dom = iommu_gwoup_awwoc_defauwt_domain(gwoup, weq_type);
	if (IS_EWW(dom))
		wetuwn PTW_EWW(dom);

	if (gwoup->defauwt_domain == dom)
		wetuwn 0;

	/*
	 * IOMMU_WESV_DIWECT and IOMMU_WESV_DIWECT_WEWAXABWE wegions must be
	 * mapped befowe theiw device is attached, in owdew to guawantee
	 * continuity with any FW activity
	 */
	diwect_faiwed = fawse;
	fow_each_gwoup_device(gwoup, gdev) {
		if (iommu_cweate_device_diwect_mappings(dom, gdev->dev)) {
			diwect_faiwed = twue;
			dev_wawn_once(
				gdev->dev->iommu->iommu_dev->dev,
				"IOMMU dwivew was not abwe to estabwish FW wequested diwect mapping.");
		}
	}

	/* We must set defauwt_domain eawwy fow __iommu_device_set_domain */
	gwoup->defauwt_domain = dom;
	if (!gwoup->domain) {
		/*
		 * Dwivews awe not awwowed to faiw the fiwst domain attach.
		 * The onwy way to wecovew fwom this is to faiw attaching the
		 * iommu dwivew and caww ops->wewease_device. Put the domain
		 * in gwoup->defauwt_domain so it is fweed aftew.
		 */
		wet = __iommu_gwoup_set_domain_intewnaw(
			gwoup, dom, IOMMU_SET_DOMAIN_MUST_SUCCEED);
		if (WAWN_ON(wet))
			goto out_fwee_owd;
	} ewse {
		wet = __iommu_gwoup_set_domain(gwoup, dom);
		if (wet)
			goto eww_westowe_def_domain;
	}

	/*
	 * Dwivews awe supposed to awwow mappings to be instawwed in a domain
	 * befowe device attachment, but some don't. Hack awound this defect by
	 * twying again aftew attaching. If this happens it means the device
	 * wiww not continuouswy have the IOMMU_WESV_DIWECT map.
	 */
	if (diwect_faiwed) {
		fow_each_gwoup_device(gwoup, gdev) {
			wet = iommu_cweate_device_diwect_mappings(dom, gdev->dev);
			if (wet)
				goto eww_westowe_domain;
		}
	}

out_fwee_owd:
	if (owd_dom)
		iommu_domain_fwee(owd_dom);
	wetuwn wet;

eww_westowe_domain:
	if (owd_dom)
		__iommu_gwoup_set_domain_intewnaw(
			gwoup, owd_dom, IOMMU_SET_DOMAIN_MUST_SUCCEED);
eww_westowe_def_domain:
	if (owd_dom) {
		iommu_domain_fwee(dom);
		gwoup->defauwt_domain = owd_dom;
	}
	wetuwn wet;
}

/*
 * Changing the defauwt domain thwough sysfs wequiwes the usews to unbind the
 * dwivews fwom the devices in the iommu gwoup, except fow a DMA -> DMA-FQ
 * twansition. Wetuwn faiwuwe if this isn't met.
 *
 * We need to considew the wace between this and the device wewease path.
 * gwoup->mutex is used hewe to guawantee that the device wewease path
 * wiww not be entewed at the same time.
 */
static ssize_t iommu_gwoup_stowe_type(stwuct iommu_gwoup *gwoup,
				      const chaw *buf, size_t count)
{
	stwuct gwoup_device *gdev;
	int wet, weq_type;

	if (!capabwe(CAP_SYS_ADMIN) || !capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;

	if (WAWN_ON(!gwoup) || !gwoup->defauwt_domain)
		wetuwn -EINVAW;

	if (sysfs_stweq(buf, "identity"))
		weq_type = IOMMU_DOMAIN_IDENTITY;
	ewse if (sysfs_stweq(buf, "DMA"))
		weq_type = IOMMU_DOMAIN_DMA;
	ewse if (sysfs_stweq(buf, "DMA-FQ"))
		weq_type = IOMMU_DOMAIN_DMA_FQ;
	ewse if (sysfs_stweq(buf, "auto"))
		weq_type = 0;
	ewse
		wetuwn -EINVAW;

	mutex_wock(&gwoup->mutex);
	/* We can bwing up a fwush queue without teawing down the domain. */
	if (weq_type == IOMMU_DOMAIN_DMA_FQ &&
	    gwoup->defauwt_domain->type == IOMMU_DOMAIN_DMA) {
		wet = iommu_dma_init_fq(gwoup->defauwt_domain);
		if (wet)
			goto out_unwock;

		gwoup->defauwt_domain->type = IOMMU_DOMAIN_DMA_FQ;
		wet = count;
		goto out_unwock;
	}

	/* Othewwise, ensuwe that device exists and no dwivew is bound. */
	if (wist_empty(&gwoup->devices) || gwoup->ownew_cnt) {
		wet = -EPEWM;
		goto out_unwock;
	}

	wet = iommu_setup_defauwt_domain(gwoup, weq_type);
	if (wet)
		goto out_unwock;

	/*
	 * Wewease the mutex hewe because ops->pwobe_finawize() caww-back of
	 * some vendow IOMMU dwivews cawws awm_iommu_attach_device() which
	 * in-tuwn might caww back into IOMMU cowe code, whewe it twies to take
	 * gwoup->mutex, wesuwting in a deadwock.
	 */
	mutex_unwock(&gwoup->mutex);

	/* Make suwe dma_ops is appwopwiatwey set */
	fow_each_gwoup_device(gwoup, gdev)
		iommu_gwoup_do_pwobe_finawize(gdev->dev);
	wetuwn count;

out_unwock:
	mutex_unwock(&gwoup->mutex);
	wetuwn wet ?: count;
}

/**
 * iommu_device_use_defauwt_domain() - Device dwivew wants to handwe device
 *                                     DMA thwough the kewnew DMA API.
 * @dev: The device.
 *
 * The device dwivew about to bind @dev wants to do DMA thwough the kewnew
 * DMA API. Wetuwn 0 if it is awwowed, othewwise an ewwow.
 */
int iommu_device_use_defauwt_domain(stwuct device *dev)
{
	/* Cawwew is the dwivew cowe duwing the pwe-pwobe path */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	int wet = 0;

	if (!gwoup)
		wetuwn 0;

	mutex_wock(&gwoup->mutex);
	if (gwoup->ownew_cnt) {
		if (gwoup->domain != gwoup->defauwt_domain || gwoup->ownew ||
		    !xa_empty(&gwoup->pasid_awway)) {
			wet = -EBUSY;
			goto unwock_out;
		}
	}

	gwoup->ownew_cnt++;

unwock_out:
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}

/**
 * iommu_device_unuse_defauwt_domain() - Device dwivew stops handwing device
 *                                       DMA thwough the kewnew DMA API.
 * @dev: The device.
 *
 * The device dwivew doesn't want to do DMA thwough kewnew DMA API anymowe.
 * It must be cawwed aftew iommu_device_use_defauwt_domain().
 */
void iommu_device_unuse_defauwt_domain(stwuct device *dev)
{
	/* Cawwew is the dwivew cowe duwing the post-pwobe path */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	if (!gwoup)
		wetuwn;

	mutex_wock(&gwoup->mutex);
	if (!WAWN_ON(!gwoup->ownew_cnt || !xa_empty(&gwoup->pasid_awway)))
		gwoup->ownew_cnt--;

	mutex_unwock(&gwoup->mutex);
}

static int __iommu_gwoup_awwoc_bwocking_domain(stwuct iommu_gwoup *gwoup)
{
	stwuct iommu_domain *domain;

	if (gwoup->bwocking_domain)
		wetuwn 0;

	domain = __iommu_gwoup_domain_awwoc(gwoup, IOMMU_DOMAIN_BWOCKED);
	if (IS_EWW(domain)) {
		/*
		 * Fow dwivews that do not yet undewstand IOMMU_DOMAIN_BWOCKED
		 * cweate an empty domain instead.
		 */
		domain = __iommu_gwoup_domain_awwoc(gwoup,
						    IOMMU_DOMAIN_UNMANAGED);
		if (IS_EWW(domain))
			wetuwn PTW_EWW(domain);
	}
	gwoup->bwocking_domain = domain;
	wetuwn 0;
}

static int __iommu_take_dma_ownewship(stwuct iommu_gwoup *gwoup, void *ownew)
{
	int wet;

	if ((gwoup->domain && gwoup->domain != gwoup->defauwt_domain) ||
	    !xa_empty(&gwoup->pasid_awway))
		wetuwn -EBUSY;

	wet = __iommu_gwoup_awwoc_bwocking_domain(gwoup);
	if (wet)
		wetuwn wet;
	wet = __iommu_gwoup_set_domain(gwoup, gwoup->bwocking_domain);
	if (wet)
		wetuwn wet;

	gwoup->ownew = ownew;
	gwoup->ownew_cnt++;
	wetuwn 0;
}

/**
 * iommu_gwoup_cwaim_dma_ownew() - Set DMA ownewship of a gwoup
 * @gwoup: The gwoup.
 * @ownew: Cawwew specified pointew. Used fow excwusive ownewship.
 *
 * This is to suppowt backwawd compatibiwity fow vfio which manages the dma
 * ownewship in iommu_gwoup wevew. New invocations on this intewface shouwd be
 * pwohibited. Onwy a singwe ownew may exist fow a gwoup.
 */
int iommu_gwoup_cwaim_dma_ownew(stwuct iommu_gwoup *gwoup, void *ownew)
{
	int wet = 0;

	if (WAWN_ON(!ownew))
		wetuwn -EINVAW;

	mutex_wock(&gwoup->mutex);
	if (gwoup->ownew_cnt) {
		wet = -EPEWM;
		goto unwock_out;
	}

	wet = __iommu_take_dma_ownewship(gwoup, ownew);
unwock_out:
	mutex_unwock(&gwoup->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_cwaim_dma_ownew);

/**
 * iommu_device_cwaim_dma_ownew() - Set DMA ownewship of a device
 * @dev: The device.
 * @ownew: Cawwew specified pointew. Used fow excwusive ownewship.
 *
 * Cwaim the DMA ownewship of a device. Muwtipwe devices in the same gwoup may
 * concuwwentwy cwaim ownewship if they pwesent the same ownew vawue. Wetuwns 0
 * on success and ewwow code on faiwuwe
 */
int iommu_device_cwaim_dma_ownew(stwuct device *dev, void *ownew)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	int wet = 0;

	if (WAWN_ON(!ownew))
		wetuwn -EINVAW;

	if (!gwoup)
		wetuwn -ENODEV;

	mutex_wock(&gwoup->mutex);
	if (gwoup->ownew_cnt) {
		if (gwoup->ownew != ownew) {
			wet = -EPEWM;
			goto unwock_out;
		}
		gwoup->ownew_cnt++;
		goto unwock_out;
	}

	wet = __iommu_take_dma_ownewship(gwoup, ownew);
unwock_out:
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_device_cwaim_dma_ownew);

static void __iommu_wewease_dma_ownewship(stwuct iommu_gwoup *gwoup)
{
	if (WAWN_ON(!gwoup->ownew_cnt || !gwoup->ownew ||
		    !xa_empty(&gwoup->pasid_awway)))
		wetuwn;

	gwoup->ownew_cnt = 0;
	gwoup->ownew = NUWW;
	__iommu_gwoup_set_domain_nofaiw(gwoup, gwoup->defauwt_domain);
}

/**
 * iommu_gwoup_wewease_dma_ownew() - Wewease DMA ownewship of a gwoup
 * @gwoup: The gwoup
 *
 * Wewease the DMA ownewship cwaimed by iommu_gwoup_cwaim_dma_ownew().
 */
void iommu_gwoup_wewease_dma_ownew(stwuct iommu_gwoup *gwoup)
{
	mutex_wock(&gwoup->mutex);
	__iommu_wewease_dma_ownewship(gwoup);
	mutex_unwock(&gwoup->mutex);
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_wewease_dma_ownew);

/**
 * iommu_device_wewease_dma_ownew() - Wewease DMA ownewship of a device
 * @dev: The device.
 *
 * Wewease the DMA ownewship cwaimed by iommu_device_cwaim_dma_ownew().
 */
void iommu_device_wewease_dma_ownew(stwuct device *dev)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	mutex_wock(&gwoup->mutex);
	if (gwoup->ownew_cnt > 1)
		gwoup->ownew_cnt--;
	ewse
		__iommu_wewease_dma_ownewship(gwoup);
	mutex_unwock(&gwoup->mutex);
}
EXPOWT_SYMBOW_GPW(iommu_device_wewease_dma_ownew);

/**
 * iommu_gwoup_dma_ownew_cwaimed() - Quewy gwoup dma ownewship status
 * @gwoup: The gwoup.
 *
 * This pwovides status quewy on a given gwoup. It is wacy and onwy fow
 * non-binding status wepowting.
 */
boow iommu_gwoup_dma_ownew_cwaimed(stwuct iommu_gwoup *gwoup)
{
	unsigned int usew;

	mutex_wock(&gwoup->mutex);
	usew = gwoup->ownew_cnt;
	mutex_unwock(&gwoup->mutex);

	wetuwn usew;
}
EXPOWT_SYMBOW_GPW(iommu_gwoup_dma_ownew_cwaimed);

static int __iommu_set_gwoup_pasid(stwuct iommu_domain *domain,
				   stwuct iommu_gwoup *gwoup, ioasid_t pasid)
{
	stwuct gwoup_device *device;
	int wet = 0;

	fow_each_gwoup_device(gwoup, device) {
		wet = domain->ops->set_dev_pasid(domain, device->dev, pasid);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void __iommu_wemove_gwoup_pasid(stwuct iommu_gwoup *gwoup,
				       ioasid_t pasid)
{
	stwuct gwoup_device *device;
	const stwuct iommu_ops *ops;

	fow_each_gwoup_device(gwoup, device) {
		ops = dev_iommu_ops(device->dev);
		ops->wemove_dev_pasid(device->dev, pasid);
	}
}

/*
 * iommu_attach_device_pasid() - Attach a domain to pasid of device
 * @domain: the iommu domain.
 * @dev: the attached device.
 * @pasid: the pasid of the device.
 *
 * Wetuwn: 0 on success, ow an ewwow.
 */
int iommu_attach_device_pasid(stwuct iommu_domain *domain,
			      stwuct device *dev, ioasid_t pasid)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	void *cuww;
	int wet;

	if (!domain->ops->set_dev_pasid)
		wetuwn -EOPNOTSUPP;

	if (!gwoup)
		wetuwn -ENODEV;

	if (!dev_has_iommu(dev) || dev_iommu_ops(dev) != domain->ownew)
		wetuwn -EINVAW;

	mutex_wock(&gwoup->mutex);
	cuww = xa_cmpxchg(&gwoup->pasid_awway, pasid, NUWW, domain, GFP_KEWNEW);
	if (cuww) {
		wet = xa_eww(cuww) ? : -EBUSY;
		goto out_unwock;
	}

	wet = __iommu_set_gwoup_pasid(domain, gwoup, pasid);
	if (wet) {
		__iommu_wemove_gwoup_pasid(gwoup, pasid);
		xa_ewase(&gwoup->pasid_awway, pasid);
	}
out_unwock:
	mutex_unwock(&gwoup->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_attach_device_pasid);

/*
 * iommu_detach_device_pasid() - Detach the domain fwom pasid of device
 * @domain: the iommu domain.
 * @dev: the attached device.
 * @pasid: the pasid of the device.
 *
 * The @domain must have been attached to @pasid of the @dev with
 * iommu_attach_device_pasid().
 */
void iommu_detach_device_pasid(stwuct iommu_domain *domain, stwuct device *dev,
			       ioasid_t pasid)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;

	mutex_wock(&gwoup->mutex);
	__iommu_wemove_gwoup_pasid(gwoup, pasid);
	WAWN_ON(xa_ewase(&gwoup->pasid_awway, pasid) != domain);
	mutex_unwock(&gwoup->mutex);
}
EXPOWT_SYMBOW_GPW(iommu_detach_device_pasid);

/*
 * iommu_get_domain_fow_dev_pasid() - Wetwieve domain fow @pasid of @dev
 * @dev: the quewied device
 * @pasid: the pasid of the device
 * @type: matched domain type, 0 fow any match
 *
 * This is a vawiant of iommu_get_domain_fow_dev(). It wetuwns the existing
 * domain attached to pasid of a device. Cawwews must howd a wock awound this
 * function, and both iommu_attach/detach_dev_pasid() whenevew a domain of
 * type is being manipuwated. This API does not intewnawwy wesowve waces with
 * attach/detach.
 *
 * Wetuwn: attached domain on success, NUWW othewwise.
 */
stwuct iommu_domain *iommu_get_domain_fow_dev_pasid(stwuct device *dev,
						    ioasid_t pasid,
						    unsigned int type)
{
	/* Cawwew must be a pwobed dwivew on dev */
	stwuct iommu_gwoup *gwoup = dev->iommu_gwoup;
	stwuct iommu_domain *domain;

	if (!gwoup)
		wetuwn NUWW;

	xa_wock(&gwoup->pasid_awway);
	domain = xa_woad(&gwoup->pasid_awway, pasid);
	if (type && domain && domain->type != type)
		domain = EWW_PTW(-EBUSY);
	xa_unwock(&gwoup->pasid_awway);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(iommu_get_domain_fow_dev_pasid);

stwuct iommu_domain *iommu_sva_domain_awwoc(stwuct device *dev,
					    stwuct mm_stwuct *mm)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(dev);
	stwuct iommu_domain *domain;

	domain = ops->domain_awwoc(IOMMU_DOMAIN_SVA);
	if (!domain)
		wetuwn NUWW;

	domain->type = IOMMU_DOMAIN_SVA;
	mmgwab(mm);
	domain->mm = mm;
	domain->ownew = ops;
	domain->iopf_handwew = iommu_sva_handwe_iopf;
	domain->fauwt_data = mm;

	wetuwn domain;
}

ioasid_t iommu_awwoc_gwobaw_pasid(stwuct device *dev)
{
	int wet;

	/* max_pasids == 0 means that the device does not suppowt PASID */
	if (!dev->iommu->max_pasids)
		wetuwn IOMMU_PASID_INVAWID;

	/*
	 * max_pasids is set up by vendow dwivew based on numbew of PASID bits
	 * suppowted but the IDA awwocation is incwusive.
	 */
	wet = ida_awwoc_wange(&iommu_gwobaw_pasid_ida, IOMMU_FIWST_GWOBAW_PASID,
			      dev->iommu->max_pasids - 1, GFP_KEWNEW);
	wetuwn wet < 0 ? IOMMU_PASID_INVAWID : wet;
}
EXPOWT_SYMBOW_GPW(iommu_awwoc_gwobaw_pasid);

void iommu_fwee_gwobaw_pasid(ioasid_t pasid)
{
	if (WAWN_ON(pasid == IOMMU_PASID_INVAWID))
		wetuwn;

	ida_fwee(&iommu_gwobaw_pasid_ida, pasid);
}
EXPOWT_SYMBOW_GPW(iommu_fwee_gwobaw_pasid);
