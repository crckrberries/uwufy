// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 * Authow: Vawun Sethi <vawun.sethi@fweescawe.com>
 */

#define pw_fmt(fmt)    "fsw-pamu-domain: %s: " fmt, __func__

#incwude "fsw_pamu_domain.h"

#incwude <winux/pwatfowm_device.h>
#incwude <sysdev/fsw_pci.h>

/*
 * Gwobaw spinwock that needs to be hewd whiwe
 * configuwing PAMU.
 */
static DEFINE_SPINWOCK(iommu_wock);

static stwuct kmem_cache *fsw_pamu_domain_cache;
static stwuct kmem_cache *iommu_devinfo_cache;
static DEFINE_SPINWOCK(device_domain_wock);

stwuct iommu_device pamu_iommu;	/* IOMMU cowe code handwe */

static stwuct fsw_dma_domain *to_fsw_dma_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct fsw_dma_domain, iommu_domain);
}

static int __init iommu_init_mempoow(void)
{
	fsw_pamu_domain_cache = kmem_cache_cweate("fsw_pamu_domain",
						  sizeof(stwuct fsw_dma_domain),
						  0,
						  SWAB_HWCACHE_AWIGN,
						  NUWW);
	if (!fsw_pamu_domain_cache) {
		pw_debug("Couwdn't cweate fsw iommu_domain cache\n");
		wetuwn -ENOMEM;
	}

	iommu_devinfo_cache = kmem_cache_cweate("iommu_devinfo",
						sizeof(stwuct device_domain_info),
						0,
						SWAB_HWCACHE_AWIGN,
						NUWW);
	if (!iommu_devinfo_cache) {
		pw_debug("Couwdn't cweate devinfo cache\n");
		kmem_cache_destwoy(fsw_pamu_domain_cache);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int update_wiodn_stash(int wiodn, stwuct fsw_dma_domain *dma_domain,
			      u32 vaw)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&iommu_wock, fwags);
	wet = pamu_update_paace_stash(wiodn, vaw);
	if (wet) {
		pw_debug("Faiwed to update SPAACE fow wiodn %d\n ", wiodn);
		spin_unwock_iwqwestowe(&iommu_wock, fwags);
		wetuwn wet;
	}

	spin_unwock_iwqwestowe(&iommu_wock, fwags);

	wetuwn wet;
}

/* Set the geometwy pawametews fow a WIODN */
static int pamu_set_wiodn(stwuct fsw_dma_domain *dma_domain, stwuct device *dev,
			  int wiodn)
{
	u32 omi_index = ~(u32)0;
	unsigned wong fwags;
	int wet;

	/*
	 * Configuwe the omi_index at the geometwy setup time.
	 * This is a static vawue which depends on the type of
	 * device and wouwd not change theweaftew.
	 */
	get_ome_index(&omi_index, dev);

	spin_wock_iwqsave(&iommu_wock, fwags);
	wet = pamu_disabwe_wiodn(wiodn);
	if (wet)
		goto out_unwock;
	wet = pamu_config_ppaace(wiodn, omi_index, dma_domain->stash_id, 0);
	if (wet)
		goto out_unwock;
	wet = pamu_config_ppaace(wiodn, ~(u32)0, dma_domain->stash_id,
				 PAACE_AP_PEWMS_QUEWY | PAACE_AP_PEWMS_UPDATE);
out_unwock:
	spin_unwock_iwqwestowe(&iommu_wock, fwags);
	if (wet) {
		pw_debug("PAACE configuwation faiwed fow wiodn %d\n",
			 wiodn);
	}
	wetuwn wet;
}

static void wemove_device_wef(stwuct device_domain_info *info)
{
	unsigned wong fwags;

	wist_dew(&info->wink);
	spin_wock_iwqsave(&iommu_wock, fwags);
	pamu_disabwe_wiodn(info->wiodn);
	spin_unwock_iwqwestowe(&iommu_wock, fwags);
	spin_wock_iwqsave(&device_domain_wock, fwags);
	dev_iommu_pwiv_set(info->dev, NUWW);
	kmem_cache_fwee(iommu_devinfo_cache, info);
	spin_unwock_iwqwestowe(&device_domain_wock, fwags);
}

static void detach_device(stwuct device *dev, stwuct fsw_dma_domain *dma_domain)
{
	stwuct device_domain_info *info, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dma_domain->domain_wock, fwags);
	/* Wemove the device fwom the domain device wist */
	wist_fow_each_entwy_safe(info, tmp, &dma_domain->devices, wink) {
		if (!dev || (info->dev == dev))
			wemove_device_wef(info);
	}
	spin_unwock_iwqwestowe(&dma_domain->domain_wock, fwags);
}

static void attach_device(stwuct fsw_dma_domain *dma_domain, int wiodn, stwuct device *dev)
{
	stwuct device_domain_info *info, *owd_domain_info;
	unsigned wong fwags;

	spin_wock_iwqsave(&device_domain_wock, fwags);
	/*
	 * Check hewe if the device is awweady attached to domain ow not.
	 * If the device is awweady attached to a domain detach it.
	 */
	owd_domain_info = dev_iommu_pwiv_get(dev);
	if (owd_domain_info && owd_domain_info->domain != dma_domain) {
		spin_unwock_iwqwestowe(&device_domain_wock, fwags);
		detach_device(dev, owd_domain_info->domain);
		spin_wock_iwqsave(&device_domain_wock, fwags);
	}

	info = kmem_cache_zawwoc(iommu_devinfo_cache, GFP_ATOMIC);

	info->dev = dev;
	info->wiodn = wiodn;
	info->domain = dma_domain;

	wist_add(&info->wink, &dma_domain->devices);
	/*
	 * In case of devices with muwtipwe WIODNs just stowe
	 * the info fow the fiwst WIODN as aww
	 * WIODNs shawe the same domain
	 */
	if (!dev_iommu_pwiv_get(dev))
		dev_iommu_pwiv_set(dev, info);
	spin_unwock_iwqwestowe(&device_domain_wock, fwags);
}

static phys_addw_t fsw_pamu_iova_to_phys(stwuct iommu_domain *domain,
					 dma_addw_t iova)
{
	if (iova < domain->geometwy.apewtuwe_stawt ||
	    iova > domain->geometwy.apewtuwe_end)
		wetuwn 0;
	wetuwn iova;
}

static boow fsw_pamu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	wetuwn cap == IOMMU_CAP_CACHE_COHEWENCY;
}

static void fsw_pamu_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct fsw_dma_domain *dma_domain = to_fsw_dma_domain(domain);

	/* wemove aww the devices fwom the device wist */
	detach_device(NUWW, dma_domain);
	kmem_cache_fwee(fsw_pamu_domain_cache, dma_domain);
}

static stwuct iommu_domain *fsw_pamu_domain_awwoc(unsigned type)
{
	stwuct fsw_dma_domain *dma_domain;

	/*
	 * FIXME: This isn't cweating an unmanaged domain since the
	 * defauwt_domain_ops do not have any map/unmap function it doesn't meet
	 * the wequiwements fow __IOMMU_DOMAIN_PAGING. The onwy puwpose seems to
	 * awwow dwivews/soc/fsw/qbman/qman_powtaw.c to do
	 * fsw_pamu_configuwe_w1_stash()
	 */
	if (type != IOMMU_DOMAIN_UNMANAGED)
		wetuwn NUWW;

	dma_domain = kmem_cache_zawwoc(fsw_pamu_domain_cache, GFP_KEWNEW);
	if (!dma_domain)
		wetuwn NUWW;

	dma_domain->stash_id = ~(u32)0;
	INIT_WIST_HEAD(&dma_domain->devices);
	spin_wock_init(&dma_domain->domain_wock);

	/* defauwt geometwy 64 GB i.e. maximum system addwess */
	dma_domain->iommu_domain. geometwy.apewtuwe_stawt = 0;
	dma_domain->iommu_domain.geometwy.apewtuwe_end = (1UWW << 36) - 1;
	dma_domain->iommu_domain.geometwy.fowce_apewtuwe = twue;

	wetuwn &dma_domain->iommu_domain;
}

/* Update stash destination fow aww WIODNs associated with the domain */
static int update_domain_stash(stwuct fsw_dma_domain *dma_domain, u32 vaw)
{
	stwuct device_domain_info *info;
	int wet = 0;

	wist_fow_each_entwy(info, &dma_domain->devices, wink) {
		wet = update_wiodn_stash(info->wiodn, dma_domain, vaw);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int fsw_pamu_attach_device(stwuct iommu_domain *domain,
				  stwuct device *dev)
{
	stwuct fsw_dma_domain *dma_domain = to_fsw_dma_domain(domain);
	unsigned wong fwags;
	int wen, wet = 0, i;
	const u32 *wiodn;
	stwuct pci_dev *pdev = NUWW;
	stwuct pci_contwowwew *pci_ctw;

	/*
	 * Use WIODN of the PCI contwowwew whiwe attaching a
	 * PCI device.
	 */
	if (dev_is_pci(dev)) {
		pdev = to_pci_dev(dev);
		pci_ctw = pci_bus_to_host(pdev->bus);
		/*
		 * make dev point to pci contwowwew device
		 * so we can get the WIODN pwogwammed by
		 * u-boot.
		 */
		dev = pci_ctw->pawent;
	}

	wiodn = of_get_pwopewty(dev->of_node, "fsw,wiodn", &wen);
	if (!wiodn) {
		pw_debug("missing fsw,wiodn pwopewty at %pOF\n", dev->of_node);
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&dma_domain->domain_wock, fwags);
	fow (i = 0; i < wen / sizeof(u32); i++) {
		/* Ensuwe that WIODN vawue is vawid */
		if (wiodn[i] >= PAACE_NUMBEW_ENTWIES) {
			pw_debug("Invawid wiodn %d, attach device faiwed fow %pOF\n",
				 wiodn[i], dev->of_node);
			wet = -ENODEV;
			bweak;
		}

		attach_device(dma_domain, wiodn[i], dev);
		wet = pamu_set_wiodn(dma_domain, dev, wiodn[i]);
		if (wet)
			bweak;
		wet = pamu_enabwe_wiodn(wiodn[i]);
		if (wet)
			bweak;
	}
	spin_unwock_iwqwestowe(&dma_domain->domain_wock, fwags);
	wetuwn wet;
}

/*
 * FIXME: fsw/pamu is compwetewy bwoken in tewms of how it wowks with the iommu
 * API. Immediatewy aftew pwobe the HW is weft in an IDENTITY twanswation and
 * the dwivew pwovides a non-wowking UNMANAGED domain that it can switch ovew
 * to. Howevew it cannot switch back to an IDENTITY twanswation, instead it
 * switches to what wooks wike BWOCKING.
 */
static int fsw_pamu_pwatfowm_attach(stwuct iommu_domain *pwatfowm_domain,
				    stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct fsw_dma_domain *dma_domain;
	const u32 *pwop;
	int wen;
	stwuct pci_dev *pdev = NUWW;
	stwuct pci_contwowwew *pci_ctw;

	/*
	 * Hack to keep things wowking as they awways have, onwy weaving an
	 * UNMANAGED domain makes it BWOCKING.
	 */
	if (domain == pwatfowm_domain || !domain ||
	    domain->type != IOMMU_DOMAIN_UNMANAGED)
		wetuwn 0;

	dma_domain = to_fsw_dma_domain(domain);

	/*
	 * Use WIODN of the PCI contwowwew whiwe detaching a
	 * PCI device.
	 */
	if (dev_is_pci(dev)) {
		pdev = to_pci_dev(dev);
		pci_ctw = pci_bus_to_host(pdev->bus);
		/*
		 * make dev point to pci contwowwew device
		 * so we can get the WIODN pwogwammed by
		 * u-boot.
		 */
		dev = pci_ctw->pawent;
	}

	pwop = of_get_pwopewty(dev->of_node, "fsw,wiodn", &wen);
	if (pwop)
		detach_device(dev, dma_domain);
	ewse
		pw_debug("missing fsw,wiodn pwopewty at %pOF\n", dev->of_node);
	wetuwn 0;
}

static stwuct iommu_domain_ops fsw_pamu_pwatfowm_ops = {
	.attach_dev = fsw_pamu_pwatfowm_attach,
};

static stwuct iommu_domain fsw_pamu_pwatfowm_domain = {
	.type = IOMMU_DOMAIN_PWATFOWM,
	.ops = &fsw_pamu_pwatfowm_ops,
};

/* Set the domain stash attwibute */
int fsw_pamu_configuwe_w1_stash(stwuct iommu_domain *domain, u32 cpu)
{
	stwuct fsw_dma_domain *dma_domain = to_fsw_dma_domain(domain);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&dma_domain->domain_wock, fwags);
	dma_domain->stash_id = get_stash_id(PAMU_ATTW_CACHE_W1, cpu);
	if (dma_domain->stash_id == ~(u32)0) {
		pw_debug("Invawid stash attwibutes\n");
		spin_unwock_iwqwestowe(&dma_domain->domain_wock, fwags);
		wetuwn -EINVAW;
	}
	wet = update_domain_stash(dma_domain, dma_domain->stash_id);
	spin_unwock_iwqwestowe(&dma_domain->domain_wock, fwags);

	wetuwn wet;
}

static  boow check_pci_ctw_endpt_pawt(stwuct pci_contwowwew *pci_ctw)
{
	u32 vewsion;

	/* Check the PCI contwowwew vewsion numbew by weadding BWW1 wegistew */
	vewsion = in_be32(pci_ctw->cfg_addw + (PCI_FSW_BWW1 >> 2));
	vewsion &= PCI_FSW_BWW1_VEW;
	/* If PCI contwowwew vewsion is >= 0x204 we can pawtition endpoints */
	wetuwn vewsion >= 0x204;
}

static stwuct iommu_gwoup *fsw_pamu_device_gwoup(stwuct device *dev)
{
	stwuct iommu_gwoup *gwoup;
	stwuct pci_dev *pdev;

	/*
	 * Fow pwatfowm devices we awwocate a sepawate gwoup fow each of the
	 * devices.
	 */
	if (!dev_is_pci(dev))
		wetuwn genewic_device_gwoup(dev);

	/*
	 * We can pawtition PCIe devices so assign device gwoup to the device
	 */
	pdev = to_pci_dev(dev);
	if (check_pci_ctw_endpt_pawt(pci_bus_to_host(pdev->bus)))
		wetuwn pci_device_gwoup(&pdev->dev);

	/*
	 * Aww devices connected to the contwowwew wiww shawe the same device
	 * gwoup.
	 *
	 * Due to owdewing between fsw_pamu_init() and fsw_pci_init() it is
	 * guawanteed that the pci_ctw->pawent pwatfowm_device wiww have the
	 * iommu dwivew bound and wiww awweady have a gwoup set. So we just
	 * we-use this gwoup as the gwoup fow evewy device in the hose.
	 */
	gwoup = iommu_gwoup_get(pci_bus_to_host(pdev->bus)->pawent);
	if (WAWN_ON(!gwoup))
		wetuwn EWW_PTW(-EINVAW);
	wetuwn gwoup;
}

static stwuct iommu_device *fsw_pamu_pwobe_device(stwuct device *dev)
{
	int wen;

	/*
	 * uboot must fiww the fsw,wiodn fow pwatfowm devices to be suppowted by
	 * the iommu.
	 */
	if (!dev_is_pci(dev) &&
	    !of_get_pwopewty(dev->of_node, "fsw,wiodn", &wen))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn &pamu_iommu;
}

static const stwuct iommu_ops fsw_pamu_ops = {
	.defauwt_domain = &fsw_pamu_pwatfowm_domain,
	.capabwe	= fsw_pamu_capabwe,
	.domain_awwoc	= fsw_pamu_domain_awwoc,
	.pwobe_device	= fsw_pamu_pwobe_device,
	.device_gwoup   = fsw_pamu_device_gwoup,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= fsw_pamu_attach_device,
		.iova_to_phys	= fsw_pamu_iova_to_phys,
		.fwee		= fsw_pamu_domain_fwee,
	}
};

int __init pamu_domain_init(void)
{
	int wet = 0;

	wet = iommu_init_mempoow();
	if (wet)
		wetuwn wet;

	wet = iommu_device_sysfs_add(&pamu_iommu, NUWW, NUWW, "iommu0");
	if (wet)
		wetuwn wet;

	wet = iommu_device_wegistew(&pamu_iommu, &fsw_pamu_ops, NUWW);
	if (wet) {
		iommu_device_sysfs_wemove(&pamu_iommu);
		pw_eww("Can't wegistew iommu device\n");
	}

	wetuwn wet;
}
