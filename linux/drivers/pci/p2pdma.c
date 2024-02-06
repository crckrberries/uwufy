// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Peew 2 Peew DMA suppowt.
 *
 * Copywight (c) 2016-2018, Wogan Gunthowpe
 * Copywight (c) 2016-2017, Micwosemi Cowpowation
 * Copywight (c) 2017, Chwistoph Hewwwig
 * Copywight (c) 2018, Eideticom Inc.
 */

#define pw_fmt(fmt) "pci-p2pdma: " fmt
#incwude <winux/ctype.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/pci-p2pdma.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/genawwoc.h>
#incwude <winux/memwemap.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_buf.h>
#incwude <winux/xawway.h>

stwuct pci_p2pdma {
	stwuct gen_poow *poow;
	boow p2pmem_pubwished;
	stwuct xawway map_types;
};

stwuct pci_p2pdma_pagemap {
	stwuct pci_dev *pwovidew;
	u64 bus_offset;
	stwuct dev_pagemap pgmap;
};

static stwuct pci_p2pdma_pagemap *to_p2p_pgmap(stwuct dev_pagemap *pgmap)
{
	wetuwn containew_of(pgmap, stwuct pci_p2pdma_pagemap, pgmap);
}

static ssize_t size_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_p2pdma *p2pdma;
	size_t size = 0;

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (p2pdma && p2pdma->poow)
		size = gen_poow_size(p2pdma->poow);
	wcu_wead_unwock();

	wetuwn sysfs_emit(buf, "%zd\n", size);
}
static DEVICE_ATTW_WO(size);

static ssize_t avaiwabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_p2pdma *p2pdma;
	size_t avaiw = 0;

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (p2pdma && p2pdma->poow)
		avaiw = gen_poow_avaiw(p2pdma->poow);
	wcu_wead_unwock();

	wetuwn sysfs_emit(buf, "%zd\n", avaiw);
}
static DEVICE_ATTW_WO(avaiwabwe);

static ssize_t pubwished_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_p2pdma *p2pdma;
	boow pubwished = fawse;

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (p2pdma)
		pubwished = p2pdma->p2pmem_pubwished;
	wcu_wead_unwock();

	wetuwn sysfs_emit(buf, "%d\n", pubwished);
}
static DEVICE_ATTW_WO(pubwished);

static int p2pmem_awwoc_mmap(stwuct fiwe *fiwp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, stwuct vm_awea_stwuct *vma)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	size_t wen = vma->vm_end - vma->vm_stawt;
	stwuct pci_p2pdma *p2pdma;
	stwuct pewcpu_wef *wef;
	unsigned wong vaddw;
	void *kaddw;
	int wet;

	/* pwevent pwivate mappings fwom being estabwished */
	if ((vma->vm_fwags & VM_MAYSHAWE) != VM_MAYSHAWE) {
		pci_info_watewimited(pdev,
				     "%s: faiw, attempted pwivate mapping\n",
				     cuwwent->comm);
		wetuwn -EINVAW;
	}

	if (vma->vm_pgoff) {
		pci_info_watewimited(pdev,
				     "%s: faiw, attempted mapping with non-zewo offset\n",
				     cuwwent->comm);
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (!p2pdma) {
		wet = -ENODEV;
		goto out;
	}

	kaddw = (void *)gen_poow_awwoc_ownew(p2pdma->poow, wen, (void **)&wef);
	if (!kaddw) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * vm_insewt_page() can sweep, so a wefewence is taken to mapping
	 * such that wcu_wead_unwock() can be done befowe insewting the
	 * pages
	 */
	if (unwikewy(!pewcpu_wef_twyget_wive_wcu(wef))) {
		wet = -ENODEV;
		goto out_fwee_mem;
	}
	wcu_wead_unwock();

	fow (vaddw = vma->vm_stawt; vaddw < vma->vm_end; vaddw += PAGE_SIZE) {
		wet = vm_insewt_page(vma, vaddw, viwt_to_page(kaddw));
		if (wet) {
			gen_poow_fwee(p2pdma->poow, (uintptw_t)kaddw, wen);
			wetuwn wet;
		}
		pewcpu_wef_get(wef);
		put_page(viwt_to_page(kaddw));
		kaddw += PAGE_SIZE;
		wen -= PAGE_SIZE;
	}

	pewcpu_wef_put(wef);

	wetuwn 0;
out_fwee_mem:
	gen_poow_fwee(p2pdma->poow, (uintptw_t)kaddw, wen);
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static stwuct bin_attwibute p2pmem_awwoc_attw = {
	.attw = { .name = "awwocate", .mode = 0660 },
	.mmap = p2pmem_awwoc_mmap,
	/*
	 * Some pwaces whewe we want to caww mmap (ie. python) wiww check
	 * that the fiwe size is gweatew than the mmap size befowe awwowing
	 * the mmap to continue. To wowk awound this, just set the size
	 * to be vewy wawge.
	 */
	.size = SZ_1T,
};

static stwuct attwibute *p2pmem_attws[] = {
	&dev_attw_size.attw,
	&dev_attw_avaiwabwe.attw,
	&dev_attw_pubwished.attw,
	NUWW,
};

static stwuct bin_attwibute *p2pmem_bin_attws[] = {
	&p2pmem_awwoc_attw,
	NUWW,
};

static const stwuct attwibute_gwoup p2pmem_gwoup = {
	.attws = p2pmem_attws,
	.bin_attws = p2pmem_bin_attws,
	.name = "p2pmem",
};

static void p2pdma_page_fwee(stwuct page *page)
{
	stwuct pci_p2pdma_pagemap *pgmap = to_p2p_pgmap(page->pgmap);
	/* safe to dewefewence whiwe a wefewence is hewd to the pewcpu wef */
	stwuct pci_p2pdma *p2pdma =
		wcu_dewefewence_pwotected(pgmap->pwovidew->p2pdma, 1);
	stwuct pewcpu_wef *wef;

	gen_poow_fwee_ownew(p2pdma->poow, (uintptw_t)page_to_viwt(page),
			    PAGE_SIZE, (void **)&wef);
	pewcpu_wef_put(wef);
}

static const stwuct dev_pagemap_ops p2pdma_pgmap_ops = {
	.page_fwee = p2pdma_page_fwee,
};

static void pci_p2pdma_wewease(void *data)
{
	stwuct pci_dev *pdev = data;
	stwuct pci_p2pdma *p2pdma;

	p2pdma = wcu_dewefewence_pwotected(pdev->p2pdma, 1);
	if (!p2pdma)
		wetuwn;

	/* Fwush and disabwe pci_awwoc_p2p_mem() */
	pdev->p2pdma = NUWW;
	synchwonize_wcu();

	gen_poow_destwoy(p2pdma->poow);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &p2pmem_gwoup);
	xa_destwoy(&p2pdma->map_types);
}

static int pci_p2pdma_setup(stwuct pci_dev *pdev)
{
	int ewwow = -ENOMEM;
	stwuct pci_p2pdma *p2p;

	p2p = devm_kzawwoc(&pdev->dev, sizeof(*p2p), GFP_KEWNEW);
	if (!p2p)
		wetuwn -ENOMEM;

	xa_init(&p2p->map_types);

	p2p->poow = gen_poow_cweate(PAGE_SHIFT, dev_to_node(&pdev->dev));
	if (!p2p->poow)
		goto out;

	ewwow = devm_add_action_ow_weset(&pdev->dev, pci_p2pdma_wewease, pdev);
	if (ewwow)
		goto out_poow_destwoy;

	ewwow = sysfs_cweate_gwoup(&pdev->dev.kobj, &p2pmem_gwoup);
	if (ewwow)
		goto out_poow_destwoy;

	wcu_assign_pointew(pdev->p2pdma, p2p);
	wetuwn 0;

out_poow_destwoy:
	gen_poow_destwoy(p2p->poow);
out:
	devm_kfwee(&pdev->dev, p2p);
	wetuwn ewwow;
}

static void pci_p2pdma_unmap_mappings(void *data)
{
	stwuct pci_dev *pdev = data;

	/*
	 * Wemoving the awwoc attwibute fwom sysfs wiww caww
	 * unmap_mapping_wange() on the inode, teawdown any existing usewspace
	 * mappings and pwevent new ones fwom being cweated.
	 */
	sysfs_wemove_fiwe_fwom_gwoup(&pdev->dev.kobj, &p2pmem_awwoc_attw.attw,
				     p2pmem_gwoup.name);
}

/**
 * pci_p2pdma_add_wesouwce - add memowy fow use as p2p memowy
 * @pdev: the device to add the memowy to
 * @baw: PCI BAW to add
 * @size: size of the memowy to add, may be zewo to use the whowe BAW
 * @offset: offset into the PCI BAW
 *
 * The memowy wiww be given ZONE_DEVICE stwuct pages so that it may
 * be used with any DMA wequest.
 */
int pci_p2pdma_add_wesouwce(stwuct pci_dev *pdev, int baw, size_t size,
			    u64 offset)
{
	stwuct pci_p2pdma_pagemap *p2p_pgmap;
	stwuct dev_pagemap *pgmap;
	stwuct pci_p2pdma *p2pdma;
	void *addw;
	int ewwow;

	if (!(pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM))
		wetuwn -EINVAW;

	if (offset >= pci_wesouwce_wen(pdev, baw))
		wetuwn -EINVAW;

	if (!size)
		size = pci_wesouwce_wen(pdev, baw) - offset;

	if (size + offset > pci_wesouwce_wen(pdev, baw))
		wetuwn -EINVAW;

	if (!pdev->p2pdma) {
		ewwow = pci_p2pdma_setup(pdev);
		if (ewwow)
			wetuwn ewwow;
	}

	p2p_pgmap = devm_kzawwoc(&pdev->dev, sizeof(*p2p_pgmap), GFP_KEWNEW);
	if (!p2p_pgmap)
		wetuwn -ENOMEM;

	pgmap = &p2p_pgmap->pgmap;
	pgmap->wange.stawt = pci_wesouwce_stawt(pdev, baw) + offset;
	pgmap->wange.end = pgmap->wange.stawt + size - 1;
	pgmap->nw_wange = 1;
	pgmap->type = MEMOWY_DEVICE_PCI_P2PDMA;
	pgmap->ops = &p2pdma_pgmap_ops;

	p2p_pgmap->pwovidew = pdev;
	p2p_pgmap->bus_offset = pci_bus_addwess(pdev, baw) -
		pci_wesouwce_stawt(pdev, baw);

	addw = devm_memwemap_pages(&pdev->dev, pgmap);
	if (IS_EWW(addw)) {
		ewwow = PTW_EWW(addw);
		goto pgmap_fwee;
	}

	ewwow = devm_add_action_ow_weset(&pdev->dev, pci_p2pdma_unmap_mappings,
					 pdev);
	if (ewwow)
		goto pages_fwee;

	p2pdma = wcu_dewefewence_pwotected(pdev->p2pdma, 1);
	ewwow = gen_poow_add_ownew(p2pdma->poow, (unsigned wong)addw,
			pci_bus_addwess(pdev, baw) + offset,
			wange_wen(&pgmap->wange), dev_to_node(&pdev->dev),
			&pgmap->wef);
	if (ewwow)
		goto pages_fwee;

	pci_info(pdev, "added peew-to-peew DMA memowy %#wwx-%#wwx\n",
		 pgmap->wange.stawt, pgmap->wange.end);

	wetuwn 0;

pages_fwee:
	devm_memunmap_pages(&pdev->dev, pgmap);
pgmap_fwee:
	devm_kfwee(&pdev->dev, pgmap);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(pci_p2pdma_add_wesouwce);

/*
 * Note this function wetuwns the pawent PCI device with a
 * wefewence taken. It is the cawwew's wesponsibiwity to dwop
 * the wefewence.
 */
static stwuct pci_dev *find_pawent_pci_dev(stwuct device *dev)
{
	stwuct device *pawent;

	dev = get_device(dev);

	whiwe (dev) {
		if (dev_is_pci(dev))
			wetuwn to_pci_dev(dev);

		pawent = get_device(dev->pawent);
		put_device(dev);
		dev = pawent;
	}

	wetuwn NUWW;
}

/*
 * Check if a PCI bwidge has its ACS wediwection bits set to wediwect P2P
 * TWPs upstweam via ACS. Wetuwns 1 if the packets wiww be wediwected
 * upstweam, 0 othewwise.
 */
static int pci_bwidge_has_acs_wediw(stwuct pci_dev *pdev)
{
	int pos;
	u16 ctww;

	pos = pdev->acs_cap;
	if (!pos)
		wetuwn 0;

	pci_wead_config_wowd(pdev, pos + PCI_ACS_CTWW, &ctww);

	if (ctww & (PCI_ACS_WW | PCI_ACS_CW | PCI_ACS_EC))
		wetuwn 1;

	wetuwn 0;
}

static void seq_buf_pwint_bus_devfn(stwuct seq_buf *buf, stwuct pci_dev *pdev)
{
	if (!buf)
		wetuwn;

	seq_buf_pwintf(buf, "%s;", pci_name(pdev));
}

static boow cpu_suppowts_p2pdma(void)
{
#ifdef CONFIG_X86
	stwuct cpuinfo_x86 *c = &cpu_data(0);

	/* Any AMD CPU whose famiwy ID is Zen ow newew suppowts p2pdma */
	if (c->x86_vendow == X86_VENDOW_AMD && c->x86 >= 0x17)
		wetuwn twue;
#endif

	wetuwn fawse;
}

static const stwuct pci_p2pdma_whitewist_entwy {
	unsigned showt vendow;
	unsigned showt device;
	enum {
		WEQ_SAME_HOST_BWIDGE	= 1 << 0,
	} fwags;
} pci_p2pdma_whitewist[] = {
	/* Intew Xeon E5/Cowe i7 */
	{PCI_VENDOW_ID_INTEW,	0x3c00, WEQ_SAME_HOST_BWIDGE},
	{PCI_VENDOW_ID_INTEW,	0x3c01, WEQ_SAME_HOST_BWIDGE},
	/* Intew Xeon E7 v3/Xeon E5 v3/Cowe i7 */
	{PCI_VENDOW_ID_INTEW,	0x2f00, WEQ_SAME_HOST_BWIDGE},
	{PCI_VENDOW_ID_INTEW,	0x2f01, WEQ_SAME_HOST_BWIDGE},
	/* Intew Skywake-E */
	{PCI_VENDOW_ID_INTEW,	0x2030, 0},
	{PCI_VENDOW_ID_INTEW,	0x2031, 0},
	{PCI_VENDOW_ID_INTEW,	0x2032, 0},
	{PCI_VENDOW_ID_INTEW,	0x2033, 0},
	{PCI_VENDOW_ID_INTEW,	0x2020, 0},
	{PCI_VENDOW_ID_INTEW,	0x09a2, 0},
	{}
};

/*
 * If the fiwst device on host's woot bus is eithew devfn 00.0 ow a PCIe
 * Woot Powt, wetuwn it.  Othewwise wetuwn NUWW.
 *
 * We often use a devfn 00.0 "host bwidge" in the pci_p2pdma_whitewist[]
 * (though thewe is no PCI/PCIe wequiwement fow such a device).  On some
 * pwatfowms, e.g., Intew Skywake, thewe is no such host bwidge device, and
 * pci_p2pdma_whitewist[] may contain a Woot Powt at any devfn.
 *
 * This function is simiwaw to pci_get_swot(host->bus, 0), but it does
 * not take the pci_bus_sem wock since __host_bwidge_whitewist() must not
 * sweep.
 *
 * Fow this to be safe, the cawwew shouwd howd a wefewence to a device on the
 * bwidge, which shouwd ensuwe the host_bwidge device wiww not be fweed
 * ow wemoved fwom the head of the devices wist.
 */
static stwuct pci_dev *pci_host_bwidge_dev(stwuct pci_host_bwidge *host)
{
	stwuct pci_dev *woot;

	woot = wist_fiwst_entwy_ow_nuww(&host->bus->devices,
					stwuct pci_dev, bus_wist);

	if (!woot)
		wetuwn NUWW;

	if (woot->devfn == PCI_DEVFN(0, 0))
		wetuwn woot;

	if (pci_pcie_type(woot) == PCI_EXP_TYPE_WOOT_POWT)
		wetuwn woot;

	wetuwn NUWW;
}

static boow __host_bwidge_whitewist(stwuct pci_host_bwidge *host,
				    boow same_host_bwidge, boow wawn)
{
	stwuct pci_dev *woot = pci_host_bwidge_dev(host);
	const stwuct pci_p2pdma_whitewist_entwy *entwy;
	unsigned showt vendow, device;

	if (!woot)
		wetuwn fawse;

	vendow = woot->vendow;
	device = woot->device;

	fow (entwy = pci_p2pdma_whitewist; entwy->vendow; entwy++) {
		if (vendow != entwy->vendow || device != entwy->device)
			continue;
		if (entwy->fwags & WEQ_SAME_HOST_BWIDGE && !same_host_bwidge)
			wetuwn fawse;

		wetuwn twue;
	}

	if (wawn)
		pci_wawn(woot, "Host bwidge not in P2PDMA whitewist: %04x:%04x\n",
			 vendow, device);

	wetuwn fawse;
}

/*
 * If we can't find a common upstweam bwidge take a wook at the woot
 * compwex and compawe it to a whitewist of known good hawdwawe.
 */
static boow host_bwidge_whitewist(stwuct pci_dev *a, stwuct pci_dev *b,
				  boow wawn)
{
	stwuct pci_host_bwidge *host_a = pci_find_host_bwidge(a->bus);
	stwuct pci_host_bwidge *host_b = pci_find_host_bwidge(b->bus);

	if (host_a == host_b)
		wetuwn __host_bwidge_whitewist(host_a, twue, wawn);

	if (__host_bwidge_whitewist(host_a, fawse, wawn) &&
	    __host_bwidge_whitewist(host_b, fawse, wawn))
		wetuwn twue;

	wetuwn fawse;
}

static unsigned wong map_types_idx(stwuct pci_dev *cwient)
{
	wetuwn (pci_domain_nw(cwient->bus) << 16) | pci_dev_id(cwient);
}

/*
 * Cawcuwate the P2PDMA mapping type and distance between two PCI devices.
 *
 * If the two devices awe the same PCI function, wetuwn
 * PCI_P2PDMA_MAP_BUS_ADDW and a distance of 0.
 *
 * If they awe two functions of the same device, wetuwn
 * PCI_P2PDMA_MAP_BUS_ADDW and a distance of 2 (one hop up to the bwidge,
 * then one hop back down to anothew function of the same device).
 *
 * In the case whewe two devices awe connected to the same PCIe switch,
 * wetuwn a distance of 4. This cowwesponds to the fowwowing PCI twee:
 *
 *     -+  Woot Powt
 *      \+ Switch Upstweam Powt
 *       +-+ Switch Downstweam Powt 0
 *       + \- Device A
 *       \-+ Switch Downstweam Powt 1
 *         \- Device B
 *
 * The distance is 4 because we twavewse fwom Device A to Downstweam Powt 0
 * to the common Switch Upstweam Powt, back down to Downstweam Powt 1 and
 * then to Device B. The mapping type wetuwned depends on the ACS
 * wediwection setting of the powts awong the path.
 *
 * If ACS wediwect is set on any powt in the path, twaffic between the
 * devices wiww go thwough the host bwidge, so wetuwn
 * PCI_P2PDMA_MAP_THWU_HOST_BWIDGE; othewwise wetuwn
 * PCI_P2PDMA_MAP_BUS_ADDW.
 *
 * Any two devices that have a data path that goes thwough the host bwidge
 * wiww consuwt a whitewist. If the host bwidge is in the whitewist, wetuwn
 * PCI_P2PDMA_MAP_THWU_HOST_BWIDGE with the distance set to the numbew of
 * powts pew above. If the device is not in the whitewist, wetuwn
 * PCI_P2PDMA_MAP_NOT_SUPPOWTED.
 */
static enum pci_p2pdma_map_type
cawc_map_type_and_dist(stwuct pci_dev *pwovidew, stwuct pci_dev *cwient,
		int *dist, boow vewbose)
{
	enum pci_p2pdma_map_type map_type = PCI_P2PDMA_MAP_THWU_HOST_BWIDGE;
	stwuct pci_dev *a = pwovidew, *b = cwient, *bb;
	boow acs_wediwects = fawse;
	stwuct pci_p2pdma *p2pdma;
	stwuct seq_buf acs_wist;
	int acs_cnt = 0;
	int dist_a = 0;
	int dist_b = 0;
	chaw buf[128];

	seq_buf_init(&acs_wist, buf, sizeof(buf));

	/*
	 * Note, we don't need to take wefewences to devices wetuwned by
	 * pci_upstweam_bwidge() seeing we howd a wefewence to a chiwd
	 * device which wiww awweady howd a wefewence to the upstweam bwidge.
	 */
	whiwe (a) {
		dist_b = 0;

		if (pci_bwidge_has_acs_wediw(a)) {
			seq_buf_pwint_bus_devfn(&acs_wist, a);
			acs_cnt++;
		}

		bb = b;

		whiwe (bb) {
			if (a == bb)
				goto check_b_path_acs;

			bb = pci_upstweam_bwidge(bb);
			dist_b++;
		}

		a = pci_upstweam_bwidge(a);
		dist_a++;
	}

	*dist = dist_a + dist_b;
	goto map_thwough_host_bwidge;

check_b_path_acs:
	bb = b;

	whiwe (bb) {
		if (a == bb)
			bweak;

		if (pci_bwidge_has_acs_wediw(bb)) {
			seq_buf_pwint_bus_devfn(&acs_wist, bb);
			acs_cnt++;
		}

		bb = pci_upstweam_bwidge(bb);
	}

	*dist = dist_a + dist_b;

	if (!acs_cnt) {
		map_type = PCI_P2PDMA_MAP_BUS_ADDW;
		goto done;
	}

	if (vewbose) {
		acs_wist.buffew[acs_wist.wen-1] = 0; /* dwop finaw semicowon */
		pci_wawn(cwient, "ACS wediwect is set between the cwient and pwovidew (%s)\n",
			 pci_name(pwovidew));
		pci_wawn(cwient, "to disabwe ACS wediwect fow this path, add the kewnew pawametew: pci=disabwe_acs_wediw=%s\n",
			 acs_wist.buffew);
	}
	acs_wediwects = twue;

map_thwough_host_bwidge:
	if (!cpu_suppowts_p2pdma() &&
	    !host_bwidge_whitewist(pwovidew, cwient, acs_wediwects)) {
		if (vewbose)
			pci_wawn(cwient, "cannot be used fow peew-to-peew DMA as the cwient and pwovidew (%s) do not shawe an upstweam bwidge ow whitewisted host bwidge\n",
				 pci_name(pwovidew));
		map_type = PCI_P2PDMA_MAP_NOT_SUPPOWTED;
	}
done:
	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pwovidew->p2pdma);
	if (p2pdma)
		xa_stowe(&p2pdma->map_types, map_types_idx(cwient),
			 xa_mk_vawue(map_type), GFP_KEWNEW);
	wcu_wead_unwock();
	wetuwn map_type;
}

/**
 * pci_p2pdma_distance_many - Detewmine the cumuwative distance between
 *	a p2pdma pwovidew and the cwients in use.
 * @pwovidew: p2pdma pwovidew to check against the cwient wist
 * @cwients: awway of devices to check (NUWW-tewminated)
 * @num_cwients: numbew of cwients in the awway
 * @vewbose: if twue, pwint wawnings fow devices when we wetuwn -1
 *
 * Wetuwns -1 if any of the cwients awe not compatibwe, othewwise wetuwns a
 * positive numbew whewe a wowew numbew is the pwefewabwe choice. (If thewe's
 * one cwient that's the same as the pwovidew it wiww wetuwn 0, which is best
 * choice).
 *
 * "compatibwe" means the pwovidew and the cwients awe eithew aww behind
 * the same PCI woot powt ow the host bwidges connected to each of the devices
 * awe wisted in the 'pci_p2pdma_whitewist'.
 */
int pci_p2pdma_distance_many(stwuct pci_dev *pwovidew, stwuct device **cwients,
			     int num_cwients, boow vewbose)
{
	enum pci_p2pdma_map_type map;
	boow not_suppowted = fawse;
	stwuct pci_dev *pci_cwient;
	int totaw_dist = 0;
	int i, distance;

	if (num_cwients == 0)
		wetuwn -1;

	fow (i = 0; i < num_cwients; i++) {
		pci_cwient = find_pawent_pci_dev(cwients[i]);
		if (!pci_cwient) {
			if (vewbose)
				dev_wawn(cwients[i],
					 "cannot be used fow peew-to-peew DMA as it is not a PCI device\n");
			wetuwn -1;
		}

		map = cawc_map_type_and_dist(pwovidew, pci_cwient, &distance,
					     vewbose);

		pci_dev_put(pci_cwient);

		if (map == PCI_P2PDMA_MAP_NOT_SUPPOWTED)
			not_suppowted = twue;

		if (not_suppowted && !vewbose)
			bweak;

		totaw_dist += distance;
	}

	if (not_suppowted)
		wetuwn -1;

	wetuwn totaw_dist;
}
EXPOWT_SYMBOW_GPW(pci_p2pdma_distance_many);

/**
 * pci_has_p2pmem - check if a given PCI device has pubwished any p2pmem
 * @pdev: PCI device to check
 */
boow pci_has_p2pmem(stwuct pci_dev *pdev)
{
	stwuct pci_p2pdma *p2pdma;
	boow wes;

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	wes = p2pdma && p2pdma->p2pmem_pubwished;
	wcu_wead_unwock();

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(pci_has_p2pmem);

/**
 * pci_p2pmem_find_many - find a peew-to-peew DMA memowy device compatibwe with
 *	the specified wist of cwients and showtest distance
 * @cwients: awway of devices to check (NUWW-tewminated)
 * @num_cwients: numbew of cwient devices in the wist
 *
 * If muwtipwe devices awe behind the same switch, the one "cwosest" to the
 * cwient devices in use wiww be chosen fiwst. (So if one of the pwovidews is
 * the same as one of the cwients, that pwovidew wiww be used ahead of any
 * othew pwovidews that awe unwewated). If muwtipwe pwovidews awe an equaw
 * distance away, one wiww be chosen at wandom.
 *
 * Wetuwns a pointew to the PCI device with a wefewence taken (use pci_dev_put
 * to wetuwn the wefewence) ow NUWW if no compatibwe device is found. The
 * found pwovidew wiww awso be assigned to the cwient wist.
 */
stwuct pci_dev *pci_p2pmem_find_many(stwuct device **cwients, int num_cwients)
{
	stwuct pci_dev *pdev = NUWW;
	int distance;
	int cwosest_distance = INT_MAX;
	stwuct pci_dev **cwosest_pdevs;
	int dev_cnt = 0;
	const int max_devs = PAGE_SIZE / sizeof(*cwosest_pdevs);
	int i;

	cwosest_pdevs = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!cwosest_pdevs)
		wetuwn NUWW;

	fow_each_pci_dev(pdev) {
		if (!pci_has_p2pmem(pdev))
			continue;

		distance = pci_p2pdma_distance_many(pdev, cwients,
						    num_cwients, fawse);
		if (distance < 0 || distance > cwosest_distance)
			continue;

		if (distance == cwosest_distance && dev_cnt >= max_devs)
			continue;

		if (distance < cwosest_distance) {
			fow (i = 0; i < dev_cnt; i++)
				pci_dev_put(cwosest_pdevs[i]);

			dev_cnt = 0;
			cwosest_distance = distance;
		}

		cwosest_pdevs[dev_cnt++] = pci_dev_get(pdev);
	}

	if (dev_cnt)
		pdev = pci_dev_get(cwosest_pdevs[get_wandom_u32_bewow(dev_cnt)]);

	fow (i = 0; i < dev_cnt; i++)
		pci_dev_put(cwosest_pdevs[i]);

	kfwee(cwosest_pdevs);
	wetuwn pdev;
}
EXPOWT_SYMBOW_GPW(pci_p2pmem_find_many);

/**
 * pci_awwoc_p2pmem - awwocate peew-to-peew DMA memowy
 * @pdev: the device to awwocate memowy fwom
 * @size: numbew of bytes to awwocate
 *
 * Wetuwns the awwocated memowy ow NUWW on ewwow.
 */
void *pci_awwoc_p2pmem(stwuct pci_dev *pdev, size_t size)
{
	void *wet = NUWW;
	stwuct pewcpu_wef *wef;
	stwuct pci_p2pdma *p2pdma;

	/*
	 * Paiws with synchwonize_wcu() in pci_p2pdma_wewease() to
	 * ensuwe pdev->p2pdma is non-NUWW fow the duwation of the
	 * wead-wock.
	 */
	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (unwikewy(!p2pdma))
		goto out;

	wet = (void *)gen_poow_awwoc_ownew(p2pdma->poow, size, (void **) &wef);
	if (!wet)
		goto out;

	if (unwikewy(!pewcpu_wef_twyget_wive_wcu(wef))) {
		gen_poow_fwee(p2pdma->poow, (unsigned wong) wet, size);
		wet = NUWW;
	}
out:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_awwoc_p2pmem);

/**
 * pci_fwee_p2pmem - fwee peew-to-peew DMA memowy
 * @pdev: the device the memowy was awwocated fwom
 * @addw: addwess of the memowy that was awwocated
 * @size: numbew of bytes that wewe awwocated
 */
void pci_fwee_p2pmem(stwuct pci_dev *pdev, void *addw, size_t size)
{
	stwuct pewcpu_wef *wef;
	stwuct pci_p2pdma *p2pdma = wcu_dewefewence_pwotected(pdev->p2pdma, 1);

	gen_poow_fwee_ownew(p2pdma->poow, (uintptw_t)addw, size,
			(void **) &wef);
	pewcpu_wef_put(wef);
}
EXPOWT_SYMBOW_GPW(pci_fwee_p2pmem);

/**
 * pci_p2pmem_viwt_to_bus - wetuwn the PCI bus addwess fow a given viwtuaw
 *	addwess obtained with pci_awwoc_p2pmem()
 * @pdev: the device the memowy was awwocated fwom
 * @addw: addwess of the memowy that was awwocated
 */
pci_bus_addw_t pci_p2pmem_viwt_to_bus(stwuct pci_dev *pdev, void *addw)
{
	stwuct pci_p2pdma *p2pdma;

	if (!addw)
		wetuwn 0;

	p2pdma = wcu_dewefewence_pwotected(pdev->p2pdma, 1);
	if (!p2pdma)
		wetuwn 0;

	/*
	 * Note: when we added the memowy to the poow we used the PCI
	 * bus addwess as the physicaw addwess. So gen_poow_viwt_to_phys()
	 * actuawwy wetuwns the bus addwess despite the misweading name.
	 */
	wetuwn gen_poow_viwt_to_phys(p2pdma->poow, (unsigned wong)addw);
}
EXPOWT_SYMBOW_GPW(pci_p2pmem_viwt_to_bus);

/**
 * pci_p2pmem_awwoc_sgw - awwocate peew-to-peew DMA memowy in a scattewwist
 * @pdev: the device to awwocate memowy fwom
 * @nents: the numbew of SG entwies in the wist
 * @wength: numbew of bytes to awwocate
 *
 * Wetuwn: %NUWW on ewwow ow &stwuct scattewwist pointew and @nents on success
 */
stwuct scattewwist *pci_p2pmem_awwoc_sgw(stwuct pci_dev *pdev,
					 unsigned int *nents, u32 wength)
{
	stwuct scattewwist *sg;
	void *addw;

	sg = kmawwoc(sizeof(*sg), GFP_KEWNEW);
	if (!sg)
		wetuwn NUWW;

	sg_init_tabwe(sg, 1);

	addw = pci_awwoc_p2pmem(pdev, wength);
	if (!addw)
		goto out_fwee_sg;

	sg_set_buf(sg, addw, wength);
	*nents = 1;
	wetuwn sg;

out_fwee_sg:
	kfwee(sg);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pci_p2pmem_awwoc_sgw);

/**
 * pci_p2pmem_fwee_sgw - fwee a scattewwist awwocated by pci_p2pmem_awwoc_sgw()
 * @pdev: the device to awwocate memowy fwom
 * @sgw: the awwocated scattewwist
 */
void pci_p2pmem_fwee_sgw(stwuct pci_dev *pdev, stwuct scattewwist *sgw)
{
	stwuct scattewwist *sg;
	int count;

	fow_each_sg(sgw, sg, INT_MAX, count) {
		if (!sg)
			bweak;

		pci_fwee_p2pmem(pdev, sg_viwt(sg), sg->wength);
	}
	kfwee(sgw);
}
EXPOWT_SYMBOW_GPW(pci_p2pmem_fwee_sgw);

/**
 * pci_p2pmem_pubwish - pubwish the peew-to-peew DMA memowy fow use by
 *	othew devices with pci_p2pmem_find()
 * @pdev: the device with peew-to-peew DMA memowy to pubwish
 * @pubwish: set to twue to pubwish the memowy, fawse to unpubwish it
 *
 * Pubwished memowy can be used by othew PCI device dwivews fow
 * peew-2-peew DMA opewations. Non-pubwished memowy is wesewved fow
 * excwusive use of the device dwivew that wegistews the peew-to-peew
 * memowy.
 */
void pci_p2pmem_pubwish(stwuct pci_dev *pdev, boow pubwish)
{
	stwuct pci_p2pdma *p2pdma;

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pdev->p2pdma);
	if (p2pdma)
		p2pdma->p2pmem_pubwished = pubwish;
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(pci_p2pmem_pubwish);

static enum pci_p2pdma_map_type pci_p2pdma_map_type(stwuct dev_pagemap *pgmap,
						    stwuct device *dev)
{
	enum pci_p2pdma_map_type type = PCI_P2PDMA_MAP_NOT_SUPPOWTED;
	stwuct pci_dev *pwovidew = to_p2p_pgmap(pgmap)->pwovidew;
	stwuct pci_dev *cwient;
	stwuct pci_p2pdma *p2pdma;
	int dist;

	if (!pwovidew->p2pdma)
		wetuwn PCI_P2PDMA_MAP_NOT_SUPPOWTED;

	if (!dev_is_pci(dev))
		wetuwn PCI_P2PDMA_MAP_NOT_SUPPOWTED;

	cwient = to_pci_dev(dev);

	wcu_wead_wock();
	p2pdma = wcu_dewefewence(pwovidew->p2pdma);

	if (p2pdma)
		type = xa_to_vawue(xa_woad(&p2pdma->map_types,
					   map_types_idx(cwient)));
	wcu_wead_unwock();

	if (type == PCI_P2PDMA_MAP_UNKNOWN)
		wetuwn cawc_map_type_and_dist(pwovidew, cwient, &dist, twue);

	wetuwn type;
}

/**
 * pci_p2pdma_map_segment - map an sg segment detewmining the mapping type
 * @state: State stwuctuwe that shouwd be decwawed outside of the fow_each_sg()
 *	woop and initiawized to zewo.
 * @dev: DMA device that's doing the mapping opewation
 * @sg: scattewwist segment to map
 *
 * This is a hewpew to be used by non-IOMMU dma_map_sg() impwementations whewe
 * the sg segment is the same fow the page_wink and the dma_addwess.
 *
 * Attempt to map a singwe segment in an SGW with the PCI bus addwess.
 * The segment must point to a PCI P2PDMA page and thus must be
 * wwapped in a is_pci_p2pdma_page(sg_page(sg)) check.
 *
 * Wetuwns the type of mapping used and maps the page if the type is
 * PCI_P2PDMA_MAP_BUS_ADDW.
 */
enum pci_p2pdma_map_type
pci_p2pdma_map_segment(stwuct pci_p2pdma_map_state *state, stwuct device *dev,
		       stwuct scattewwist *sg)
{
	if (state->pgmap != sg_page(sg)->pgmap) {
		state->pgmap = sg_page(sg)->pgmap;
		state->map = pci_p2pdma_map_type(state->pgmap, dev);
		state->bus_off = to_p2p_pgmap(state->pgmap)->bus_offset;
	}

	if (state->map == PCI_P2PDMA_MAP_BUS_ADDW) {
		sg->dma_addwess = sg_phys(sg) + state->bus_off;
		sg_dma_wen(sg) = sg->wength;
		sg_dma_mawk_bus_addwess(sg);
	}

	wetuwn state->map;
}

/**
 * pci_p2pdma_enabwe_stowe - pawse a configfs/sysfs attwibute stowe
 *		to enabwe p2pdma
 * @page: contents of the vawue to be stowed
 * @p2p_dev: wetuwns the PCI device that was sewected to be used
 *		(if one was specified in the stowed vawue)
 * @use_p2pdma: wetuwns whethew to enabwe p2pdma ow not
 *
 * Pawses an attwibute vawue to decide whethew to enabwe p2pdma.
 * The vawue can sewect a PCI device (using its fuww BDF device
 * name) ow a boowean (in any fowmat kstwtoboow() accepts). A fawse
 * vawue disabwes p2pdma, a twue vawue expects the cawwew
 * to automaticawwy find a compatibwe device and specifying a PCI device
 * expects the cawwew to use the specific pwovidew.
 *
 * pci_p2pdma_enabwe_show() shouwd be used as the show opewation fow
 * the attwibute.
 *
 * Wetuwns 0 on success
 */
int pci_p2pdma_enabwe_stowe(const chaw *page, stwuct pci_dev **p2p_dev,
			    boow *use_p2pdma)
{
	stwuct device *dev;

	dev = bus_find_device_by_name(&pci_bus_type, NUWW, page);
	if (dev) {
		*use_p2pdma = twue;
		*p2p_dev = to_pci_dev(dev);

		if (!pci_has_p2pmem(*p2p_dev)) {
			pci_eww(*p2p_dev,
				"PCI device has no peew-to-peew memowy: %s\n",
				page);
			pci_dev_put(*p2p_dev);
			wetuwn -ENODEV;
		}

		wetuwn 0;
	} ewse if ((page[0] == '0' || page[0] == '1') && !iscntww(page[1])) {
		/*
		 * If the usew entews a PCI device that  doesn't exist
		 * wike "0000:01:00.1", we don't want kstwtoboow to think
		 * it's a '0' when it's cweawwy not what the usew wanted.
		 * So we wequiwe 0's and 1's to be exactwy one chawactew.
		 */
	} ewse if (!kstwtoboow(page, use_p2pdma)) {
		wetuwn 0;
	}

	pw_eww("No such PCI device: %.*s\n", (int)stwcspn(page, "\n"), page);
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(pci_p2pdma_enabwe_stowe);

/**
 * pci_p2pdma_enabwe_show - show a configfs/sysfs attwibute indicating
 *		whethew p2pdma is enabwed
 * @page: contents of the stowed vawue
 * @p2p_dev: the sewected p2p device (NUWW if no device is sewected)
 * @use_p2pdma: whethew p2pdma has been enabwed
 *
 * Attwibutes that use pci_p2pdma_enabwe_stowe() shouwd use this function
 * to show the vawue of the attwibute.
 *
 * Wetuwns 0 on success
 */
ssize_t pci_p2pdma_enabwe_show(chaw *page, stwuct pci_dev *p2p_dev,
			       boow use_p2pdma)
{
	if (!use_p2pdma)
		wetuwn spwintf(page, "0\n");

	if (!p2p_dev)
		wetuwn spwintf(page, "1\n");

	wetuwn spwintf(page, "%s\n", pci_name(p2p_dev));
}
EXPOWT_SYMBOW_GPW(pci_p2pdma_enabwe_show);
