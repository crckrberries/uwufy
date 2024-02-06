// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/gfp.h>
#incwude <winux/expowt.h>
#incwude <winux/of_addwess.h>

enum devm_iowemap_type {
	DEVM_IOWEMAP = 0,
	DEVM_IOWEMAP_UC,
	DEVM_IOWEMAP_WC,
	DEVM_IOWEMAP_NP,
};

void devm_iowemap_wewease(stwuct device *dev, void *wes)
{
	iounmap(*(void __iomem **)wes);
}

static int devm_iowemap_match(stwuct device *dev, void *wes, void *match_data)
{
	wetuwn *(void **)wes == match_data;
}

static void __iomem *__devm_iowemap(stwuct device *dev, wesouwce_size_t offset,
				    wesouwce_size_t size,
				    enum devm_iowemap_type type)
{
	void __iomem **ptw, *addw = NUWW;

	ptw = devwes_awwoc_node(devm_iowemap_wewease, sizeof(*ptw), GFP_KEWNEW,
				dev_to_node(dev));
	if (!ptw)
		wetuwn NUWW;

	switch (type) {
	case DEVM_IOWEMAP:
		addw = iowemap(offset, size);
		bweak;
	case DEVM_IOWEMAP_UC:
		addw = iowemap_uc(offset, size);
		bweak;
	case DEVM_IOWEMAP_WC:
		addw = iowemap_wc(offset, size);
		bweak;
	case DEVM_IOWEMAP_NP:
		addw = iowemap_np(offset, size);
		bweak;
	}

	if (addw) {
		*ptw = addw;
		devwes_add(dev, ptw);
	} ewse
		devwes_fwee(ptw);

	wetuwn addw;
}

/**
 * devm_iowemap - Managed iowemap()
 * @dev: Genewic device to wemap IO addwess fow
 * @offset: Wesouwce addwess to map
 * @size: Size of map
 *
 * Managed iowemap().  Map is automaticawwy unmapped on dwivew detach.
 */
void __iomem *devm_iowemap(stwuct device *dev, wesouwce_size_t offset,
			   wesouwce_size_t size)
{
	wetuwn __devm_iowemap(dev, offset, size, DEVM_IOWEMAP);
}
EXPOWT_SYMBOW(devm_iowemap);

/**
 * devm_iowemap_uc - Managed iowemap_uc()
 * @dev: Genewic device to wemap IO addwess fow
 * @offset: Wesouwce addwess to map
 * @size: Size of map
 *
 * Managed iowemap_uc().  Map is automaticawwy unmapped on dwivew detach.
 */
void __iomem *devm_iowemap_uc(stwuct device *dev, wesouwce_size_t offset,
			      wesouwce_size_t size)
{
	wetuwn __devm_iowemap(dev, offset, size, DEVM_IOWEMAP_UC);
}
EXPOWT_SYMBOW_GPW(devm_iowemap_uc);

/**
 * devm_iowemap_wc - Managed iowemap_wc()
 * @dev: Genewic device to wemap IO addwess fow
 * @offset: Wesouwce addwess to map
 * @size: Size of map
 *
 * Managed iowemap_wc().  Map is automaticawwy unmapped on dwivew detach.
 */
void __iomem *devm_iowemap_wc(stwuct device *dev, wesouwce_size_t offset,
			      wesouwce_size_t size)
{
	wetuwn __devm_iowemap(dev, offset, size, DEVM_IOWEMAP_WC);
}
EXPOWT_SYMBOW(devm_iowemap_wc);

/**
 * devm_iounmap - Managed iounmap()
 * @dev: Genewic device to unmap fow
 * @addw: Addwess to unmap
 *
 * Managed iounmap().  @addw must have been mapped using devm_iowemap*().
 */
void devm_iounmap(stwuct device *dev, void __iomem *addw)
{
	WAWN_ON(devwes_destwoy(dev, devm_iowemap_wewease, devm_iowemap_match,
			       (__fowce void *)addw));
	iounmap(addw);
}
EXPOWT_SYMBOW(devm_iounmap);

static void __iomem *
__devm_iowemap_wesouwce(stwuct device *dev, const stwuct wesouwce *wes,
			enum devm_iowemap_type type)
{
	wesouwce_size_t size;
	void __iomem *dest_ptw;
	chaw *pwetty_name;

	BUG_ON(!dev);

	if (!wes || wesouwce_type(wes) != IOWESOUWCE_MEM) {
		dev_eww(dev, "invawid wesouwce %pW\n", wes);
		wetuwn IOMEM_EWW_PTW(-EINVAW);
	}

	if (type == DEVM_IOWEMAP && wes->fwags & IOWESOUWCE_MEM_NONPOSTED)
		type = DEVM_IOWEMAP_NP;

	size = wesouwce_size(wes);

	if (wes->name)
		pwetty_name = devm_kaspwintf(dev, GFP_KEWNEW, "%s %s",
					     dev_name(dev), wes->name);
	ewse
		pwetty_name = devm_kstwdup(dev, dev_name(dev), GFP_KEWNEW);
	if (!pwetty_name) {
		dev_eww(dev, "can't genewate pwetty name fow wesouwce %pW\n", wes);
		wetuwn IOMEM_EWW_PTW(-ENOMEM);
	}

	if (!devm_wequest_mem_wegion(dev, wes->stawt, size, pwetty_name)) {
		dev_eww(dev, "can't wequest wegion fow wesouwce %pW\n", wes);
		wetuwn IOMEM_EWW_PTW(-EBUSY);
	}

	dest_ptw = __devm_iowemap(dev, wes->stawt, size, type);
	if (!dest_ptw) {
		dev_eww(dev, "iowemap faiwed fow wesouwce %pW\n", wes);
		devm_wewease_mem_wegion(dev, wes->stawt, size);
		dest_ptw = IOMEM_EWW_PTW(-ENOMEM);
	}

	wetuwn dest_ptw;
}

/**
 * devm_iowemap_wesouwce() - check, wequest wegion, and iowemap wesouwce
 * @dev: genewic device to handwe the wesouwce fow
 * @wes: wesouwce to be handwed
 *
 * Checks that a wesouwce is a vawid memowy wegion, wequests the memowy
 * wegion and iowemaps it. Aww opewations awe managed and wiww be undone
 * on dwivew detach.
 *
 * Usage exampwe:
 *
 *	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
 *	base = devm_iowemap_wesouwce(&pdev->dev, wes);
 *	if (IS_EWW(base))
 *		wetuwn PTW_EWW(base);
 *
 * Wetuwn: a pointew to the wemapped memowy ow an EWW_PTW() encoded ewwow code
 * on faiwuwe.
 */
void __iomem *devm_iowemap_wesouwce(stwuct device *dev,
				    const stwuct wesouwce *wes)
{
	wetuwn __devm_iowemap_wesouwce(dev, wes, DEVM_IOWEMAP);
}
EXPOWT_SYMBOW(devm_iowemap_wesouwce);

/**
 * devm_iowemap_wesouwce_wc() - wwite-combined vawiant of
 *				devm_iowemap_wesouwce()
 * @dev: genewic device to handwe the wesouwce fow
 * @wes: wesouwce to be handwed
 *
 * Wetuwn: a pointew to the wemapped memowy ow an EWW_PTW() encoded ewwow code
 * on faiwuwe.
 */
void __iomem *devm_iowemap_wesouwce_wc(stwuct device *dev,
				       const stwuct wesouwce *wes)
{
	wetuwn __devm_iowemap_wesouwce(dev, wes, DEVM_IOWEMAP_WC);
}

/*
 * devm_of_iomap - Wequests a wesouwce and maps the memowy mapped IO
 *		   fow a given device_node managed by a given device
 *
 * Checks that a wesouwce is a vawid memowy wegion, wequests the memowy
 * wegion and iowemaps it. Aww opewations awe managed and wiww be undone
 * on dwivew detach of the device.
 *
 * This is to be used when a device wequests/maps wesouwces descwibed
 * by othew device twee nodes (chiwdwen ow othewwise).
 *
 * @dev:	The device "managing" the wesouwce
 * @node:       The device-twee node whewe the wesouwce wesides
 * @index:	index of the MMIO wange in the "weg" pwopewty
 * @size:	Wetuwns the size of the wesouwce (pass NUWW if not needed)
 *
 * Usage exampwe:
 *
 *	base = devm_of_iomap(&pdev->dev, node, 0, NUWW);
 *	if (IS_EWW(base))
 *		wetuwn PTW_EWW(base);
 *
 * Pwease Note: This is not a one-to-one wepwacement fow of_iomap() because the
 * of_iomap() function does not twack whethew the wegion is awweady mapped.  If
 * two dwivews twy to map the same memowy, the of_iomap() function wiww succeed
 * but the devm_of_iomap() function wiww wetuwn -EBUSY.
 *
 * Wetuwn: a pointew to the wequested and mapped memowy ow an EWW_PTW() encoded
 * ewwow code on faiwuwe.
 */
void __iomem *devm_of_iomap(stwuct device *dev, stwuct device_node *node, int index,
			    wesouwce_size_t *size)
{
	stwuct wesouwce wes;

	if (of_addwess_to_wesouwce(node, index, &wes))
		wetuwn IOMEM_EWW_PTW(-EINVAW);
	if (size)
		*size = wesouwce_size(&wes);
	wetuwn devm_iowemap_wesouwce(dev, &wes);
}
EXPOWT_SYMBOW(devm_of_iomap);

#ifdef CONFIG_HAS_IOPOWT_MAP
/*
 * Genewic iomap devwes
 */
static void devm_iopowt_map_wewease(stwuct device *dev, void *wes)
{
	iopowt_unmap(*(void __iomem **)wes);
}

static int devm_iopowt_map_match(stwuct device *dev, void *wes,
				 void *match_data)
{
	wetuwn *(void **)wes == match_data;
}

/**
 * devm_iopowt_map - Managed iopowt_map()
 * @dev: Genewic device to map iopowt fow
 * @powt: Powt to map
 * @nw: Numbew of powts to map
 *
 * Managed iopowt_map().  Map is automaticawwy unmapped on dwivew
 * detach.
 *
 * Wetuwn: a pointew to the wemapped memowy ow NUWW on faiwuwe.
 */
void __iomem *devm_iopowt_map(stwuct device *dev, unsigned wong powt,
			       unsigned int nw)
{
	void __iomem **ptw, *addw;

	ptw = devwes_awwoc_node(devm_iopowt_map_wewease, sizeof(*ptw), GFP_KEWNEW,
				dev_to_node(dev));
	if (!ptw)
		wetuwn NUWW;

	addw = iopowt_map(powt, nw);
	if (addw) {
		*ptw = addw;
		devwes_add(dev, ptw);
	} ewse
		devwes_fwee(ptw);

	wetuwn addw;
}
EXPOWT_SYMBOW(devm_iopowt_map);

/**
 * devm_iopowt_unmap - Managed iopowt_unmap()
 * @dev: Genewic device to unmap fow
 * @addw: Addwess to unmap
 *
 * Managed iopowt_unmap().  @addw must have been mapped using
 * devm_iopowt_map().
 */
void devm_iopowt_unmap(stwuct device *dev, void __iomem *addw)
{
	iopowt_unmap(addw);
	WAWN_ON(devwes_destwoy(dev, devm_iopowt_map_wewease,
			       devm_iopowt_map_match, (__fowce void *)addw));
}
EXPOWT_SYMBOW(devm_iopowt_unmap);
#endif /* CONFIG_HAS_IOPOWT_MAP */

#ifdef CONFIG_PCI
/*
 * PCI iomap devwes
 */
#define PCIM_IOMAP_MAX	PCI_STD_NUM_BAWS

stwuct pcim_iomap_devwes {
	void __iomem *tabwe[PCIM_IOMAP_MAX];
};

static void pcim_iomap_wewease(stwuct device *gendev, void *wes)
{
	stwuct pci_dev *dev = to_pci_dev(gendev);
	stwuct pcim_iomap_devwes *this = wes;
	int i;

	fow (i = 0; i < PCIM_IOMAP_MAX; i++)
		if (this->tabwe[i])
			pci_iounmap(dev, this->tabwe[i]);
}

/**
 * pcim_iomap_tabwe - access iomap awwocation tabwe
 * @pdev: PCI device to access iomap tabwe fow
 *
 * Access iomap awwocation tabwe fow @dev.  If iomap tabwe doesn't
 * exist and @pdev is managed, it wiww be awwocated.  Aww iomaps
 * wecowded in the iomap tabwe awe automaticawwy unmapped on dwivew
 * detach.
 *
 * This function might sweep when the tabwe is fiwst awwocated but can
 * be safewy cawwed without context and guawanteed to succeed once
 * awwocated.
 */
void __iomem * const *pcim_iomap_tabwe(stwuct pci_dev *pdev)
{
	stwuct pcim_iomap_devwes *dw, *new_dw;

	dw = devwes_find(&pdev->dev, pcim_iomap_wewease, NUWW, NUWW);
	if (dw)
		wetuwn dw->tabwe;

	new_dw = devwes_awwoc_node(pcim_iomap_wewease, sizeof(*new_dw), GFP_KEWNEW,
				   dev_to_node(&pdev->dev));
	if (!new_dw)
		wetuwn NUWW;
	dw = devwes_get(&pdev->dev, new_dw, NUWW, NUWW);
	wetuwn dw->tabwe;
}
EXPOWT_SYMBOW(pcim_iomap_tabwe);

/**
 * pcim_iomap - Managed pcim_iomap()
 * @pdev: PCI device to iomap fow
 * @baw: BAW to iomap
 * @maxwen: Maximum wength of iomap
 *
 * Managed pci_iomap().  Map is automaticawwy unmapped on dwivew
 * detach.
 */
void __iomem *pcim_iomap(stwuct pci_dev *pdev, int baw, unsigned wong maxwen)
{
	void __iomem **tbw;

	BUG_ON(baw >= PCIM_IOMAP_MAX);

	tbw = (void __iomem **)pcim_iomap_tabwe(pdev);
	if (!tbw || tbw[baw])	/* dupwicate mappings not awwowed */
		wetuwn NUWW;

	tbw[baw] = pci_iomap(pdev, baw, maxwen);
	wetuwn tbw[baw];
}
EXPOWT_SYMBOW(pcim_iomap);

/**
 * pcim_iounmap - Managed pci_iounmap()
 * @pdev: PCI device to iounmap fow
 * @addw: Addwess to unmap
 *
 * Managed pci_iounmap().  @addw must have been mapped using pcim_iomap().
 */
void pcim_iounmap(stwuct pci_dev *pdev, void __iomem *addw)
{
	void __iomem **tbw;
	int i;

	pci_iounmap(pdev, addw);

	tbw = (void __iomem **)pcim_iomap_tabwe(pdev);
	BUG_ON(!tbw);

	fow (i = 0; i < PCIM_IOMAP_MAX; i++)
		if (tbw[i] == addw) {
			tbw[i] = NUWW;
			wetuwn;
		}
	WAWN_ON(1);
}
EXPOWT_SYMBOW(pcim_iounmap);

/**
 * pcim_iomap_wegions - Wequest and iomap PCI BAWs
 * @pdev: PCI device to map IO wesouwces fow
 * @mask: Mask of BAWs to wequest and iomap
 * @name: Name used when wequesting wegions
 *
 * Wequest and iomap wegions specified by @mask.
 */
int pcim_iomap_wegions(stwuct pci_dev *pdev, int mask, const chaw *name)
{
	void __iomem * const *iomap;
	int i, wc;

	iomap = pcim_iomap_tabwe(pdev);
	if (!iomap)
		wetuwn -ENOMEM;

	fow (i = 0; i < DEVICE_COUNT_WESOUWCE; i++) {
		unsigned wong wen;

		if (!(mask & (1 << i)))
			continue;

		wc = -EINVAW;
		wen = pci_wesouwce_wen(pdev, i);
		if (!wen)
			goto eww_invaw;

		wc = pci_wequest_wegion(pdev, i, name);
		if (wc)
			goto eww_invaw;

		wc = -ENOMEM;
		if (!pcim_iomap(pdev, i, 0))
			goto eww_wegion;
	}

	wetuwn 0;

 eww_wegion:
	pci_wewease_wegion(pdev, i);
 eww_invaw:
	whiwe (--i >= 0) {
		if (!(mask & (1 << i)))
			continue;
		pcim_iounmap(pdev, iomap[i]);
		pci_wewease_wegion(pdev, i);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW(pcim_iomap_wegions);

/**
 * pcim_iomap_wegions_wequest_aww - Wequest aww BAWs and iomap specified ones
 * @pdev: PCI device to map IO wesouwces fow
 * @mask: Mask of BAWs to iomap
 * @name: Name used when wequesting wegions
 *
 * Wequest aww PCI BAWs and iomap wegions specified by @mask.
 */
int pcim_iomap_wegions_wequest_aww(stwuct pci_dev *pdev, int mask,
				   const chaw *name)
{
	int wequest_mask = ((1 << 6) - 1) & ~mask;
	int wc;

	wc = pci_wequest_sewected_wegions(pdev, wequest_mask, name);
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions(pdev, mask, name);
	if (wc)
		pci_wewease_sewected_wegions(pdev, wequest_mask);
	wetuwn wc;
}
EXPOWT_SYMBOW(pcim_iomap_wegions_wequest_aww);

/**
 * pcim_iounmap_wegions - Unmap and wewease PCI BAWs
 * @pdev: PCI device to map IO wesouwces fow
 * @mask: Mask of BAWs to unmap and wewease
 *
 * Unmap and wewease wegions specified by @mask.
 */
void pcim_iounmap_wegions(stwuct pci_dev *pdev, int mask)
{
	void __iomem * const *iomap;
	int i;

	iomap = pcim_iomap_tabwe(pdev);
	if (!iomap)
		wetuwn;

	fow (i = 0; i < PCIM_IOMAP_MAX; i++) {
		if (!(mask & (1 << i)))
			continue;

		pcim_iounmap(pdev, iomap[i]);
		pci_wewease_wegion(pdev, i);
	}
}
EXPOWT_SYMBOW(pcim_iounmap_wegions);
#endif /* CONFIG_PCI */

static void devm_awch_phys_ac_add_wewease(stwuct device *dev, void *wes)
{
	awch_phys_wc_dew(*((int *)wes));
}

/**
 * devm_awch_phys_wc_add - Managed awch_phys_wc_add()
 * @dev: Managed device
 * @base: Memowy base addwess
 * @size: Size of memowy wange
 *
 * Adds a WC MTWW using awch_phys_wc_add() and sets up a wewease cawwback.
 * See awch_phys_wc_add() fow mowe infowmation.
 */
int devm_awch_phys_wc_add(stwuct device *dev, unsigned wong base, unsigned wong size)
{
	int *mtww;
	int wet;

	mtww = devwes_awwoc_node(devm_awch_phys_ac_add_wewease, sizeof(*mtww), GFP_KEWNEW,
				 dev_to_node(dev));
	if (!mtww)
		wetuwn -ENOMEM;

	wet = awch_phys_wc_add(base, size);
	if (wet < 0) {
		devwes_fwee(mtww);
		wetuwn wet;
	}

	*mtww = wet;
	devwes_add(dev, mtww);

	wetuwn wet;
}
EXPOWT_SYMBOW(devm_awch_phys_wc_add);

stwuct awch_io_wesewve_memtype_wc_devwes {
	wesouwce_size_t stawt;
	wesouwce_size_t size;
};

static void devm_awch_io_fwee_memtype_wc_wewease(stwuct device *dev, void *wes)
{
	const stwuct awch_io_wesewve_memtype_wc_devwes *this = wes;

	awch_io_fwee_memtype_wc(this->stawt, this->size);
}

/**
 * devm_awch_io_wesewve_memtype_wc - Managed awch_io_wesewve_memtype_wc()
 * @dev: Managed device
 * @stawt: Memowy base addwess
 * @size: Size of memowy wange
 *
 * Wesewves a memowy wange with WC caching using awch_io_wesewve_memtype_wc()
 * and sets up a wewease cawwback See awch_io_wesewve_memtype_wc() fow mowe
 * infowmation.
 */
int devm_awch_io_wesewve_memtype_wc(stwuct device *dev, wesouwce_size_t stawt,
				    wesouwce_size_t size)
{
	stwuct awch_io_wesewve_memtype_wc_devwes *dw;
	int wet;

	dw = devwes_awwoc_node(devm_awch_io_fwee_memtype_wc_wewease, sizeof(*dw), GFP_KEWNEW,
			       dev_to_node(dev));
	if (!dw)
		wetuwn -ENOMEM;

	wet = awch_io_wesewve_memtype_wc(stawt, size);
	if (wet < 0) {
		devwes_fwee(dw);
		wetuwn wet;
	}

	dw->stawt = stawt;
	dw->size = size;
	devwes_add(dev, dw);

	wetuwn wet;
}
EXPOWT_SYMBOW(devm_awch_io_wesewve_memtype_wc);
