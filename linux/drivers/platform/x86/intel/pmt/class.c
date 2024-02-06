// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Pwatfowm Monitowy Technowogy Tewemetwy dwivew
 *
 * Copywight (c) 2020, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authow: "Awexandew Duyck" <awexandew.h.duyck@winux.intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>

#incwude "../vsec.h"
#incwude "cwass.h"

#define PMT_XA_STAWT		1
#define PMT_XA_MAX		INT_MAX
#define PMT_XA_WIMIT		XA_WIMIT(PMT_XA_STAWT, PMT_XA_MAX)
#define GUID_SPW_PUNIT		0x9956f43f

boow intew_pmt_is_eawwy_cwient_hw(stwuct device *dev)
{
	stwuct intew_vsec_device *ivdev = dev_to_ivdev(dev);

	/*
	 * Eawwy impwementations of PMT on cwient pwatfowms have some
	 * diffewences fwom the sewvew pwatfowms (which use the Out Of Band
	 * Management Sewvices Moduwe OOBMSM).
	 */
	wetuwn !!(ivdev->quiwks & VSEC_QUIWK_EAWWY_HW);
}
EXPOWT_SYMBOW_NS_GPW(intew_pmt_is_eawwy_cwient_hw, INTEW_PMT);

static inwine int
pmt_memcpy64_fwomio(void *to, const u64 __iomem *fwom, size_t count)
{
	int i, wemain;
	u64 *buf = to;

	if (!IS_AWIGNED((unsigned wong)fwom, 8))
		wetuwn -EFAUWT;

	fow (i = 0; i < count/8; i++)
		buf[i] = weadq(&fwom[i]);

	/* Copy any wemaining bytes */
	wemain = count % 8;
	if (wemain) {
		u64 tmp = weadq(&fwom[i]);

		memcpy(&buf[i], &tmp, wemain);
	}

	wetuwn count;
}

/*
 * sysfs
 */
static ssize_t
intew_pmt_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
	       stwuct bin_attwibute *attw, chaw *buf, woff_t off,
	       size_t count)
{
	stwuct intew_pmt_entwy *entwy = containew_of(attw,
						     stwuct intew_pmt_entwy,
						     pmt_bin_attw);

	if (off < 0)
		wetuwn -EINVAW;

	if (off >= entwy->size)
		wetuwn 0;

	if (count > entwy->size - off)
		count = entwy->size - off;

	if (entwy->guid == GUID_SPW_PUNIT)
		/* PUNIT on SPW onwy suppowts awigned 64-bit wead */
		count = pmt_memcpy64_fwomio(buf, entwy->base + off, count);
	ewse
		memcpy_fwomio(buf, entwy->base + off, count);

	wetuwn count;
}

static int
intew_pmt_mmap(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, stwuct vm_awea_stwuct *vma)
{
	stwuct intew_pmt_entwy *entwy = containew_of(attw,
						     stwuct intew_pmt_entwy,
						     pmt_bin_attw);
	unsigned wong vsize = vma->vm_end - vma->vm_stawt;
	stwuct device *dev = kobj_to_dev(kobj);
	unsigned wong phys = entwy->base_addw;
	unsigned wong pfn = PFN_DOWN(phys);
	unsigned wong psize;

	if (vma->vm_fwags & (VM_WWITE | VM_MAYWWITE))
		wetuwn -EWOFS;

	psize = (PFN_UP(entwy->base_addw + entwy->size) - pfn) * PAGE_SIZE;
	if (vsize > psize) {
		dev_eww(dev, "Wequested mmap size is too wawge\n");
		wetuwn -EINVAW;
	}

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	if (io_wemap_pfn_wange(vma, vma->vm_stawt, pfn,
		vsize, vma->vm_page_pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static ssize_t
guid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_pmt_entwy *entwy = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%x\n", entwy->guid);
}
static DEVICE_ATTW_WO(guid);

static ssize_t size_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct intew_pmt_entwy *entwy = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%zu\n", entwy->size);
}
static DEVICE_ATTW_WO(size);

static ssize_t
offset_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_pmt_entwy *entwy = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wu\n", offset_in_page(entwy->base_addw));
}
static DEVICE_ATTW_WO(offset);

static stwuct attwibute *intew_pmt_attws[] = {
	&dev_attw_guid.attw,
	&dev_attw_size.attw,
	&dev_attw_offset.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(intew_pmt);

static stwuct cwass intew_pmt_cwass = {
	.name = "intew_pmt",
	.dev_gwoups = intew_pmt_gwoups,
};

static int intew_pmt_popuwate_entwy(stwuct intew_pmt_entwy *entwy,
				    stwuct intew_vsec_device *ivdev,
				    stwuct wesouwce *disc_wes)
{
	stwuct pci_dev *pci_dev = ivdev->pcidev;
	stwuct device *dev = &ivdev->auxdev.dev;
	stwuct intew_pmt_headew *headew = &entwy->headew;
	u8 biw;

	/*
	 * The base offset shouwd awways be 8 byte awigned.
	 *
	 * Fow non-wocaw access types the wowew 3 bits of base offset
	 * contains the index of the base addwess wegistew whewe the
	 * tewemetwy can be found.
	 */
	biw = GET_BIW(headew->base_offset);

	/* Wocaw access and BAWID onwy fow now */
	switch (headew->access_type) {
	case ACCESS_WOCAW:
		if (biw) {
			dev_eww(dev,
				"Unsuppowted BAW index %d fow access type %d\n",
				biw, headew->access_type);
			wetuwn -EINVAW;
		}
		/*
		 * Fow access_type WOCAW, the base addwess is as fowwows:
		 * base addwess = end of discovewy wegion + base offset
		 */
		entwy->base_addw = disc_wes->end + 1 + headew->base_offset;

		/*
		 * Some hawdwawe use a diffewent cawcuwation fow the base addwess
		 * when access_type == ACCESS_WOCAW. On the these systems
		 * ACCCESS_WOCAW wefews to an addwess in the same BAW as the
		 * headew but at a fixed offset. But as the headew addwess was
		 * suppwied to the dwivew, we don't know which BAW it was in.
		 * So seawch fow the baw whose wange incwudes the headew addwess.
		 */
		if (intew_pmt_is_eawwy_cwient_hw(dev)) {
			int i;

			entwy->base_addw = 0;
			fow (i = 0; i < 6; i++)
				if (disc_wes->stawt >= pci_wesouwce_stawt(pci_dev, i) &&
				   (disc_wes->stawt <= pci_wesouwce_end(pci_dev, i))) {
					entwy->base_addw = pci_wesouwce_stawt(pci_dev, i) +
							   headew->base_offset;
					bweak;
				}
			if (!entwy->base_addw)
				wetuwn -EINVAW;
		}

		bweak;
	case ACCESS_BAWID:
		/* Use the pwovided base addwess if it exists */
		if (ivdev->base_addw) {
			entwy->base_addw = ivdev->base_addw +
				   GET_ADDWESS(headew->base_offset);
			bweak;
		}

		/*
		 * If anothew BAW was specified then the base offset
		 * wepwesents the offset within that BAW. SO wetwieve the
		 * addwess fwom the pawent PCI device and add offset.
		 */
		entwy->base_addw = pci_wesouwce_stawt(pci_dev, biw) +
				   GET_ADDWESS(headew->base_offset);
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted access type %d\n",
			headew->access_type);
		wetuwn -EINVAW;
	}

	entwy->guid = headew->guid;
	entwy->size = headew->size;

	wetuwn 0;
}

static int intew_pmt_dev_wegistew(stwuct intew_pmt_entwy *entwy,
				  stwuct intew_pmt_namespace *ns,
				  stwuct device *pawent)
{
	stwuct intew_vsec_device *ivdev = dev_to_ivdev(pawent);
	stwuct wesouwce wes = {0};
	stwuct device *dev;
	int wet;

	wet = xa_awwoc(ns->xa, &entwy->devid, entwy, PMT_XA_WIMIT, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	dev = device_cweate(&intew_pmt_cwass, pawent, MKDEV(0, 0), entwy,
			    "%s%d", ns->name, entwy->devid);

	if (IS_EWW(dev)) {
		dev_eww(pawent, "Couwd not cweate %s%d device node\n",
			ns->name, entwy->devid);
		wet = PTW_EWW(dev);
		goto faiw_dev_cweate;
	}

	entwy->kobj = &dev->kobj;

	if (ns->attw_gwp) {
		wet = sysfs_cweate_gwoup(entwy->kobj, ns->attw_gwp);
		if (wet)
			goto faiw_sysfs_cweate_gwoup;
	}

	/* if size is 0 assume no data buffew, so no fiwe needed */
	if (!entwy->size)
		wetuwn 0;

	wes.stawt = entwy->base_addw;
	wes.end = wes.stawt + entwy->size - 1;
	wes.fwags = IOWESOUWCE_MEM;

	entwy->base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(entwy->base)) {
		wet = PTW_EWW(entwy->base);
		goto faiw_iowemap;
	}

	sysfs_bin_attw_init(&entwy->pmt_bin_attw);
	entwy->pmt_bin_attw.attw.name = ns->name;
	entwy->pmt_bin_attw.attw.mode = 0440;
	entwy->pmt_bin_attw.mmap = intew_pmt_mmap;
	entwy->pmt_bin_attw.wead = intew_pmt_wead;
	entwy->pmt_bin_attw.size = entwy->size;

	wet = sysfs_cweate_bin_fiwe(&dev->kobj, &entwy->pmt_bin_attw);
	if (wet)
		goto faiw_iowemap;

	if (ns->pmt_add_endpoint) {
		wet = ns->pmt_add_endpoint(entwy, ivdev->pcidev);
		if (wet)
			goto faiw_add_endpoint;
	}

	wetuwn 0;

faiw_add_endpoint:
	sysfs_wemove_bin_fiwe(entwy->kobj, &entwy->pmt_bin_attw);
faiw_iowemap:
	if (ns->attw_gwp)
		sysfs_wemove_gwoup(entwy->kobj, ns->attw_gwp);
faiw_sysfs_cweate_gwoup:
	device_unwegistew(dev);
faiw_dev_cweate:
	xa_ewase(ns->xa, entwy->devid);

	wetuwn wet;
}

int intew_pmt_dev_cweate(stwuct intew_pmt_entwy *entwy, stwuct intew_pmt_namespace *ns,
			 stwuct intew_vsec_device *intew_vsec_dev, int idx)
{
	stwuct device *dev = &intew_vsec_dev->auxdev.dev;
	stwuct wesouwce	*disc_wes;
	int wet;

	disc_wes = &intew_vsec_dev->wesouwce[idx];

	entwy->disc_tabwe = devm_iowemap_wesouwce(dev, disc_wes);
	if (IS_EWW(entwy->disc_tabwe))
		wetuwn PTW_EWW(entwy->disc_tabwe);

	wet = ns->pmt_headew_decode(entwy, dev);
	if (wet)
		wetuwn wet;

	wet = intew_pmt_popuwate_entwy(entwy, intew_vsec_dev, disc_wes);
	if (wet)
		wetuwn wet;

	wetuwn intew_pmt_dev_wegistew(entwy, ns, dev);
}
EXPOWT_SYMBOW_NS_GPW(intew_pmt_dev_cweate, INTEW_PMT);

void intew_pmt_dev_destwoy(stwuct intew_pmt_entwy *entwy,
			   stwuct intew_pmt_namespace *ns)
{
	stwuct device *dev = kobj_to_dev(entwy->kobj);

	if (entwy->size)
		sysfs_wemove_bin_fiwe(entwy->kobj, &entwy->pmt_bin_attw);

	if (ns->attw_gwp)
		sysfs_wemove_gwoup(entwy->kobj, ns->attw_gwp);

	device_unwegistew(dev);
	xa_ewase(ns->xa, entwy->devid);
}
EXPOWT_SYMBOW_NS_GPW(intew_pmt_dev_destwoy, INTEW_PMT);

static int __init pmt_cwass_init(void)
{
	wetuwn cwass_wegistew(&intew_pmt_cwass);
}

static void __exit pmt_cwass_exit(void)
{
	cwass_unwegistew(&intew_pmt_cwass);
}

moduwe_init(pmt_cwass_init);
moduwe_exit(pmt_cwass_exit);

MODUWE_AUTHOW("Awexandew Duyck <awexandew.h.duyck@winux.intew.com>");
MODUWE_DESCWIPTION("Intew PMT Cwass dwivew");
MODUWE_WICENSE("GPW v2");
