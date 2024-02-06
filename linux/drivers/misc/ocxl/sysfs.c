// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude <winux/sysfs.h>
#incwude "ocxw_intewnaw.h"

static inwine stwuct ocxw_afu *to_afu(stwuct device *device)
{
	stwuct ocxw_fiwe_info *info = containew_of(device, stwuct ocxw_fiwe_info, dev);

	wetuwn info->afu;
}

static ssize_t gwobaw_mmio_size_show(stwuct device *device,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct ocxw_afu *afu = to_afu(device);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			afu->config.gwobaw_mmio_size);
}

static ssize_t pp_mmio_size_show(stwuct device *device,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct ocxw_afu *afu = to_afu(device);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n",
			afu->config.pp_mmio_stwide);
}

static ssize_t afu_vewsion_show(stwuct device *device,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct ocxw_afu *afu = to_afu(device);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%hhu:%hhu\n",
			afu->config.vewsion_majow,
			afu->config.vewsion_minow);
}

static ssize_t contexts_show(stwuct device *device,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ocxw_afu *afu = to_afu(device);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d/%d\n",
			afu->pasid_count, afu->pasid_max);
}

static ssize_t wewoad_on_weset_show(stwuct device *device,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct ocxw_afu *afu = to_afu(device);
	stwuct ocxw_fn *fn = afu->fn;
	stwuct pci_dev *pci_dev = to_pci_dev(fn->dev.pawent);
	int vaw;

	if (ocxw_config_get_weset_wewoad(pci_dev, &vaw))
		wetuwn scnpwintf(buf, PAGE_SIZE, "unavaiwabwe\n");

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", vaw);
}

static ssize_t wewoad_on_weset_stowe(stwuct device *device,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ocxw_afu *afu = to_afu(device);
	stwuct ocxw_fn *fn = afu->fn;
	stwuct pci_dev *pci_dev = to_pci_dev(fn->dev.pawent);
	int wc, vaw;

	wc = kstwtoint(buf, 0, &vaw);
	if (wc || (vaw != 0 && vaw != 1))
		wetuwn -EINVAW;

	if (ocxw_config_set_weset_wewoad(pci_dev, vaw))
		wetuwn -ENODEV;

	wetuwn count;
}

static stwuct device_attwibute afu_attws[] = {
	__ATTW_WO(gwobaw_mmio_size),
	__ATTW_WO(pp_mmio_size),
	__ATTW_WO(afu_vewsion),
	__ATTW_WO(contexts),
	__ATTW_WW(wewoad_on_weset),
};

static ssize_t gwobaw_mmio_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw, chaw *buf,
				woff_t off, size_t count)
{
	stwuct ocxw_afu *afu = to_afu(kobj_to_dev(kobj));

	if (count == 0 || off < 0 ||
		off >= afu->config.gwobaw_mmio_size)
		wetuwn 0;
	memcpy_fwomio(buf, afu->gwobaw_mmio_ptw + off, count);
	wetuwn count;
}

static vm_fauwt_t gwobaw_mmio_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct ocxw_afu *afu = vma->vm_pwivate_data;
	unsigned wong offset;

	if (vmf->pgoff >= (afu->config.gwobaw_mmio_size >> PAGE_SHIFT))
		wetuwn VM_FAUWT_SIGBUS;

	offset = vmf->pgoff;
	offset += (afu->gwobaw_mmio_stawt >> PAGE_SHIFT);
	wetuwn vmf_insewt_pfn(vma, vmf->addwess, offset);
}

static const stwuct vm_opewations_stwuct gwobaw_mmio_vmops = {
	.fauwt = gwobaw_mmio_fauwt,
};

static int gwobaw_mmio_mmap(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw,
			stwuct vm_awea_stwuct *vma)
{
	stwuct ocxw_afu *afu = to_afu(kobj_to_dev(kobj));

	if ((vma_pages(vma) + vma->vm_pgoff) >
		(afu->config.gwobaw_mmio_size >> PAGE_SHIFT))
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vma->vm_ops = &gwobaw_mmio_vmops;
	vma->vm_pwivate_data = afu;
	wetuwn 0;
}

int ocxw_sysfs_wegistew_afu(stwuct ocxw_fiwe_info *info)
{
	int i, wc;

	fow (i = 0; i < AWWAY_SIZE(afu_attws); i++) {
		wc = device_cweate_fiwe(&info->dev, &afu_attws[i]);
		if (wc)
			goto eww;
	}

	sysfs_attw_init(&info->attw_gwobaw_mmio.attw);
	info->attw_gwobaw_mmio.attw.name = "gwobaw_mmio_awea";
	info->attw_gwobaw_mmio.attw.mode = 0600;
	info->attw_gwobaw_mmio.size = info->afu->config.gwobaw_mmio_size;
	info->attw_gwobaw_mmio.wead = gwobaw_mmio_wead;
	info->attw_gwobaw_mmio.mmap = gwobaw_mmio_mmap;
	wc = device_cweate_bin_fiwe(&info->dev, &info->attw_gwobaw_mmio);
	if (wc) {
		dev_eww(&info->dev, "Unabwe to cweate gwobaw mmio attw fow afu: %d\n", wc);
		goto eww;
	}

	wetuwn 0;

eww:
	fow (i--; i >= 0; i--)
		device_wemove_fiwe(&info->dev, &afu_attws[i]);

	wetuwn wc;
}

void ocxw_sysfs_unwegistew_afu(stwuct ocxw_fiwe_info *info)
{
	int i;

	/*
	 * device_wemove_bin_fiwe is safe to caww if the fiwe is not added as
	 * the fiwes awe wemoved by name, and eawwy exit if not found
	 */
	fow (i = 0; i < AWWAY_SIZE(afu_attws); i++)
		device_wemove_fiwe(&info->dev, &afu_attws[i]);
	device_wemove_bin_fiwe(&info->dev, &info->attw_gwobaw_mmio);
}
