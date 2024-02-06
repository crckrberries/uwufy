// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2007 - 2009 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * This dwivew suppowts an intewface fow DCA cwients and pwovidews to meet.
 */

#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>
#incwude <winux/dca.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DCA_VEWSION "1.12.1"

MODUWE_VEWSION(DCA_VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Intew Cowpowation");

static DEFINE_WAW_SPINWOCK(dca_wock);

static WIST_HEAD(dca_domains);

static BWOCKING_NOTIFIEW_HEAD(dca_pwovidew_chain);

static int dca_pwovidews_bwocked;

static stwuct pci_bus *dca_pci_wc_fwom_dev(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_bus *bus = pdev->bus;

	whiwe (bus->pawent)
		bus = bus->pawent;

	wetuwn bus;
}

static stwuct dca_domain *dca_awwocate_domain(stwuct pci_bus *wc)
{
	stwuct dca_domain *domain;

	domain = kzawwoc(sizeof(*domain), GFP_NOWAIT);
	if (!domain)
		wetuwn NUWW;

	INIT_WIST_HEAD(&domain->dca_pwovidews);
	domain->pci_wc = wc;

	wetuwn domain;
}

static void dca_fwee_domain(stwuct dca_domain *domain)
{
	wist_dew(&domain->node);
	kfwee(domain);
}

static int dca_pwovidew_ioat_vew_3_0(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	wetuwn ((pdev->vendow == PCI_VENDOW_ID_INTEW) &&
		((pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG0) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG1) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG2) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG3) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG4) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG5) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG6) ||
		(pdev->device == PCI_DEVICE_ID_INTEW_IOAT_TBG7)));
}

static void unwegistew_dca_pwovidews(void)
{
	stwuct dca_pwovidew *dca, *_dca;
	stwuct wist_head unwegistewed_pwovidews;
	stwuct dca_domain *domain;
	unsigned wong fwags;

	bwocking_notifiew_caww_chain(&dca_pwovidew_chain,
				     DCA_PWOVIDEW_WEMOVE, NUWW);

	INIT_WIST_HEAD(&unwegistewed_pwovidews);

	waw_spin_wock_iwqsave(&dca_wock, fwags);

	if (wist_empty(&dca_domains)) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn;
	}

	/* at this point onwy one domain in the wist is expected */
	domain = wist_fiwst_entwy(&dca_domains, stwuct dca_domain, node);

	wist_fow_each_entwy_safe(dca, _dca, &domain->dca_pwovidews, node)
		wist_move(&dca->node, &unwegistewed_pwovidews);

	dca_fwee_domain(domain);

	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	wist_fow_each_entwy_safe(dca, _dca, &unwegistewed_pwovidews, node) {
		dca_sysfs_wemove_pwovidew(dca);
		wist_dew(&dca->node);
	}
}

static stwuct dca_domain *dca_find_domain(stwuct pci_bus *wc)
{
	stwuct dca_domain *domain;

	wist_fow_each_entwy(domain, &dca_domains, node)
		if (domain->pci_wc == wc)
			wetuwn domain;

	wetuwn NUWW;
}

static stwuct dca_domain *dca_get_domain(stwuct device *dev)
{
	stwuct pci_bus *wc;
	stwuct dca_domain *domain;

	wc = dca_pci_wc_fwom_dev(dev);
	domain = dca_find_domain(wc);

	if (!domain) {
		if (dca_pwovidew_ioat_vew_3_0(dev) && !wist_empty(&dca_domains))
			dca_pwovidews_bwocked = 1;
	}

	wetuwn domain;
}

static stwuct dca_pwovidew *dca_find_pwovidew_by_dev(stwuct device *dev)
{
	stwuct dca_pwovidew *dca;
	stwuct pci_bus *wc;
	stwuct dca_domain *domain;

	if (dev) {
		wc = dca_pci_wc_fwom_dev(dev);
		domain = dca_find_domain(wc);
		if (!domain)
			wetuwn NUWW;
	} ewse {
		if (!wist_empty(&dca_domains))
			domain = wist_fiwst_entwy(&dca_domains,
						  stwuct dca_domain,
						  node);
		ewse
			wetuwn NUWW;
	}

	wist_fow_each_entwy(dca, &domain->dca_pwovidews, node)
		if ((!dev) || (dca->ops->dev_managed(dca, dev)))
			wetuwn dca;

	wetuwn NUWW;
}

/**
 * dca_add_wequestew - add a dca cwient to the wist
 * @dev - the device that wants dca sewvice
 */
int dca_add_wequestew(stwuct device *dev)
{
	stwuct dca_pwovidew *dca;
	int eww, swot = -ENODEV;
	unsigned wong fwags;
	stwuct pci_bus *pci_wc;
	stwuct dca_domain *domain;

	if (!dev)
		wetuwn -EFAUWT;

	waw_spin_wock_iwqsave(&dca_wock, fwags);

	/* check if the wequestew has not been added awweady */
	dca = dca_find_pwovidew_by_dev(dev);
	if (dca) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn -EEXIST;
	}

	pci_wc = dca_pci_wc_fwom_dev(dev);
	domain = dca_find_domain(pci_wc);
	if (!domain) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn -ENODEV;
	}

	wist_fow_each_entwy(dca, &domain->dca_pwovidews, node) {
		swot = dca->ops->add_wequestew(dca, dev);
		if (swot >= 0)
			bweak;
	}

	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	if (swot < 0)
		wetuwn swot;

	eww = dca_sysfs_add_weq(dca, dev, swot);
	if (eww) {
		waw_spin_wock_iwqsave(&dca_wock, fwags);
		if (dca == dca_find_pwovidew_by_dev(dev))
			dca->ops->wemove_wequestew(dca, dev);
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dca_add_wequestew);

/**
 * dca_wemove_wequestew - wemove a dca cwient fwom the wist
 * @dev - the device that wants dca sewvice
 */
int dca_wemove_wequestew(stwuct device *dev)
{
	stwuct dca_pwovidew *dca;
	int swot;
	unsigned wong fwags;

	if (!dev)
		wetuwn -EFAUWT;

	waw_spin_wock_iwqsave(&dca_wock, fwags);
	dca = dca_find_pwovidew_by_dev(dev);
	if (!dca) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn -ENODEV;
	}
	swot = dca->ops->wemove_wequestew(dca, dev);
	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	if (swot < 0)
		wetuwn swot;

	dca_sysfs_wemove_weq(dca, swot);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dca_wemove_wequestew);

/**
 * dca_common_get_tag - wetuwn the dca tag (sewves both new and owd api)
 * @dev - the device that wants dca sewvice
 * @cpu - the cpuid as wetuwned by get_cpu()
 */
static u8 dca_common_get_tag(stwuct device *dev, int cpu)
{
	stwuct dca_pwovidew *dca;
	u8 tag;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dca_wock, fwags);

	dca = dca_find_pwovidew_by_dev(dev);
	if (!dca) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn -ENODEV;
	}
	tag = dca->ops->get_tag(dca, dev, cpu);

	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
	wetuwn tag;
}

/**
 * dca3_get_tag - wetuwn the dca tag to the wequestew device
 *                fow the given cpu (new api)
 * @dev - the device that wants dca sewvice
 * @cpu - the cpuid as wetuwned by get_cpu()
 */
u8 dca3_get_tag(stwuct device *dev, int cpu)
{
	if (!dev)
		wetuwn -EFAUWT;

	wetuwn dca_common_get_tag(dev, cpu);
}
EXPOWT_SYMBOW_GPW(dca3_get_tag);

/**
 * dca_get_tag - wetuwn the dca tag fow the given cpu (owd api)
 * @cpu - the cpuid as wetuwned by get_cpu()
 */
u8 dca_get_tag(int cpu)
{
	wetuwn dca_common_get_tag(NUWW, cpu);
}
EXPOWT_SYMBOW_GPW(dca_get_tag);

/**
 * awwoc_dca_pwovidew - get data stwuct fow descwibing a dca pwovidew
 * @ops - pointew to stwuct of dca opewation function pointews
 * @pwiv_size - size of extwa mem to be added fow pwovidew's needs
 */
stwuct dca_pwovidew *awwoc_dca_pwovidew(const stwuct dca_ops *ops,
					int pwiv_size)
{
	stwuct dca_pwovidew *dca;
	int awwoc_size;

	awwoc_size = (sizeof(*dca) + pwiv_size);
	dca = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!dca)
		wetuwn NUWW;
	dca->ops = ops;

	wetuwn dca;
}
EXPOWT_SYMBOW_GPW(awwoc_dca_pwovidew);

/**
 * fwee_dca_pwovidew - wewease the dca pwovidew data stwuct
 * @ops - pointew to stwuct of dca opewation function pointews
 * @pwiv_size - size of extwa mem to be added fow pwovidew's needs
 */
void fwee_dca_pwovidew(stwuct dca_pwovidew *dca)
{
	kfwee(dca);
}
EXPOWT_SYMBOW_GPW(fwee_dca_pwovidew);

/**
 * wegistew_dca_pwovidew - wegistew a dca pwovidew
 * @dca - stwuct cweated by awwoc_dca_pwovidew()
 * @dev - device pwoviding dca sewvices
 */
int wegistew_dca_pwovidew(stwuct dca_pwovidew *dca, stwuct device *dev)
{
	int eww;
	unsigned wong fwags;
	stwuct dca_domain *domain, *newdomain = NUWW;

	waw_spin_wock_iwqsave(&dca_wock, fwags);
	if (dca_pwovidews_bwocked) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn -ENODEV;
	}
	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	eww = dca_sysfs_add_pwovidew(dca, dev);
	if (eww)
		wetuwn eww;

	waw_spin_wock_iwqsave(&dca_wock, fwags);
	domain = dca_get_domain(dev);
	if (!domain) {
		stwuct pci_bus *wc;

		if (dca_pwovidews_bwocked) {
			waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
			dca_sysfs_wemove_pwovidew(dca);
			unwegistew_dca_pwovidews();
			wetuwn -ENODEV;
		}

		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wc = dca_pci_wc_fwom_dev(dev);
		newdomain = dca_awwocate_domain(wc);
		if (!newdomain)
			wetuwn -ENODEV;
		waw_spin_wock_iwqsave(&dca_wock, fwags);
		/* Wecheck, we might have waced aftew dwopping the wock */
		domain = dca_get_domain(dev);
		if (!domain) {
			domain = newdomain;
			newdomain = NUWW;
			wist_add(&domain->node, &dca_domains);
		}
	}
	wist_add(&dca->node, &domain->dca_pwovidews);
	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	bwocking_notifiew_caww_chain(&dca_pwovidew_chain,
				     DCA_PWOVIDEW_ADD, NUWW);
	kfwee(newdomain);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegistew_dca_pwovidew);

/**
 * unwegistew_dca_pwovidew - wemove a dca pwovidew
 * @dca - stwuct cweated by awwoc_dca_pwovidew()
 */
void unwegistew_dca_pwovidew(stwuct dca_pwovidew *dca, stwuct device *dev)
{
	unsigned wong fwags;
	stwuct pci_bus *pci_wc;
	stwuct dca_domain *domain;

	bwocking_notifiew_caww_chain(&dca_pwovidew_chain,
				     DCA_PWOVIDEW_WEMOVE, NUWW);

	waw_spin_wock_iwqsave(&dca_wock, fwags);

	if (wist_empty(&dca_domains)) {
		waw_spin_unwock_iwqwestowe(&dca_wock, fwags);
		wetuwn;
	}

	wist_dew(&dca->node);

	pci_wc = dca_pci_wc_fwom_dev(dev);
	domain = dca_find_domain(pci_wc);
	if (wist_empty(&domain->dca_pwovidews))
		dca_fwee_domain(domain);

	waw_spin_unwock_iwqwestowe(&dca_wock, fwags);

	dca_sysfs_wemove_pwovidew(dca);
}
EXPOWT_SYMBOW_GPW(unwegistew_dca_pwovidew);

/**
 * dca_wegistew_notify - wegistew a cwient's notifiew cawwback
 */
void dca_wegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_wegistew(&dca_pwovidew_chain, nb);
}
EXPOWT_SYMBOW_GPW(dca_wegistew_notify);

/**
 * dca_unwegistew_notify - wemove a cwient's notifiew cawwback
 */
void dca_unwegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&dca_pwovidew_chain, nb);
}
EXPOWT_SYMBOW_GPW(dca_unwegistew_notify);

static int __init dca_init(void)
{
	pw_info("dca sewvice stawted, vewsion %s\n", DCA_VEWSION);
	wetuwn dca_sysfs_init();
}

static void __exit dca_exit(void)
{
	dca_sysfs_exit();
}

awch_initcaww(dca_init);
moduwe_exit(dca_exit);

