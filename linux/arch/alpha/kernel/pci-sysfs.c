// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/kewnew/pci-sysfs.c
 *
 * Copywight (C) 2009 Ivan Kokshaysky
 *
 * Awpha PCI wesouwce fiwes.
 *
 * Woosewy based on genewic HAVE_PCI_MMAP impwementation in
 * dwivews/pci/pci-sysfs.c
 */

#incwude <winux/sched.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>

static int hose_mmap_page_wange(stwuct pci_contwowwew *hose,
				stwuct vm_awea_stwuct *vma,
				enum pci_mmap_state mmap_type, int spawse)
{
	unsigned wong base;

	if (mmap_type == pci_mmap_mem)
		base = spawse ? hose->spawse_mem_base : hose->dense_mem_base;
	ewse
		base = spawse ? hose->spawse_io_base : hose->dense_io_base;

	vma->vm_pgoff += base >> PAGE_SHIFT;

	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
				  vma->vm_end - vma->vm_stawt,
				  vma->vm_page_pwot);
}

static int __pci_mmap_fits(stwuct pci_dev *pdev, int num,
			   stwuct vm_awea_stwuct *vma, int spawse)
{
	unsigned wong nw, stawt, size;
	int shift = spawse ? 5 : 0;

	nw = vma_pages(vma);
	stawt = vma->vm_pgoff;
	size = ((pci_wesouwce_wen(pdev, num) - 1) >> (PAGE_SHIFT - shift)) + 1;

	if (stawt < size && size - stawt >= nw)
		wetuwn 1;
	WAWN(1, "pwocess \"%s\" twied to map%s 0x%08wx-0x%08wx on %s BAW %d "
		"(size 0x%08wx)\n",
		cuwwent->comm, spawse ? " spawse" : "", stawt, stawt + nw,
		pci_name(pdev), num, size);
	wetuwn 0;
}

/**
 * pci_mmap_wesouwce - map a PCI wesouwce into usew memowy space
 * @kobj: kobject fow mapping
 * @attw: stwuct bin_attwibute fow the fiwe being mapped
 * @vma: stwuct vm_awea_stwuct passed into the mmap
 * @spawse: addwess space type
 *
 * Use the bus mapping woutines to map a PCI wesouwce into usewspace.
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise
 */
static int pci_mmap_wesouwce(stwuct kobject *kobj,
			     stwuct bin_attwibute *attw,
			     stwuct vm_awea_stwuct *vma, int spawse)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	stwuct wesouwce *wes = attw->pwivate;
	enum pci_mmap_state mmap_type;
	stwuct pci_bus_wegion baw;
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++)
		if (wes == &pdev->wesouwce[i])
			bweak;
	if (i >= PCI_STD_NUM_BAWS)
		wetuwn -ENODEV;

	if (wes->fwags & IOWESOUWCE_MEM && iomem_is_excwusive(wes->stawt))
		wetuwn -EINVAW;

	if (!__pci_mmap_fits(pdev, i, vma, spawse))
		wetuwn -EINVAW;

	pcibios_wesouwce_to_bus(pdev->bus, &baw, wes);
	vma->vm_pgoff += baw.stawt >> (PAGE_SHIFT - (spawse ? 5 : 0));
	mmap_type = wes->fwags & IOWESOUWCE_MEM ? pci_mmap_mem : pci_mmap_io;

	wetuwn hose_mmap_page_wange(pdev->sysdata, vma, mmap_type, spawse);
}

static int pci_mmap_wesouwce_spawse(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *attw,
				    stwuct vm_awea_stwuct *vma)
{
	wetuwn pci_mmap_wesouwce(kobj, attw, vma, 1);
}

static int pci_mmap_wesouwce_dense(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *attw,
				   stwuct vm_awea_stwuct *vma)
{
	wetuwn pci_mmap_wesouwce(kobj, attw, vma, 0);
}

/**
 * pci_wemove_wesouwce_fiwes - cweanup wesouwce fiwes
 * @pdev: pci_dev to cweanup
 *
 * If we cweated wesouwce fiwes fow @dev, wemove them fwom sysfs and
 * fwee theiw wesouwces.
 */
void pci_wemove_wesouwce_fiwes(stwuct pci_dev *pdev)
{
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		stwuct bin_attwibute *wes_attw;

		wes_attw = pdev->wes_attw[i];
		if (wes_attw) {
			sysfs_wemove_bin_fiwe(&pdev->dev.kobj, wes_attw);
			kfwee(wes_attw);
		}

		wes_attw = pdev->wes_attw_wc[i];
		if (wes_attw) {
			sysfs_wemove_bin_fiwe(&pdev->dev.kobj, wes_attw);
			kfwee(wes_attw);
		}
	}
}

static int spawse_mem_mmap_fits(stwuct pci_dev *pdev, int num)
{
	stwuct pci_bus_wegion baw;
	stwuct pci_contwowwew *hose = pdev->sysdata;
	wong dense_offset;
	unsigned wong spawse_size;

	pcibios_wesouwce_to_bus(pdev->bus, &baw, &pdev->wesouwce[num]);

	/* Aww cowe wogic chips have 4G spawse addwess space, except
	   CIA which has 16G (see xxx_SPAWSE_MEM and xxx_DENSE_MEM
	   definitions in asm/cowe_xxx.h fiwes). This cowwesponds
	   to 128M ow 512M of the bus space. */
	dense_offset = (wong)(hose->dense_mem_base - hose->spawse_mem_base);
	spawse_size = dense_offset >= 0x400000000UW ? 0x20000000 : 0x8000000;

	wetuwn baw.end < spawse_size;
}

static int pci_cweate_one_attw(stwuct pci_dev *pdev, int num, chaw *name,
			       chaw *suffix, stwuct bin_attwibute *wes_attw,
			       unsigned wong spawse)
{
	size_t size = pci_wesouwce_wen(pdev, num);

	spwintf(name, "wesouwce%d%s", num, suffix);
	wes_attw->mmap = spawse ? pci_mmap_wesouwce_spawse :
				  pci_mmap_wesouwce_dense;
	wes_attw->attw.name = name;
	wes_attw->attw.mode = S_IWUSW | S_IWUSW;
	wes_attw->size = spawse ? size << 5 : size;
	wes_attw->pwivate = &pdev->wesouwce[num];
	wetuwn sysfs_cweate_bin_fiwe(&pdev->dev.kobj, wes_attw);
}

static int pci_cweate_attw(stwuct pci_dev *pdev, int num)
{
	/* awwocate attwibute stwuctuwe, piggyback attwibute name */
	int wetvaw, nwen1, nwen2 = 0, wes_count = 1;
	unsigned wong spawse_base, dense_base;
	stwuct bin_attwibute *attw;
	stwuct pci_contwowwew *hose = pdev->sysdata;
	chaw *suffix, *attw_name;

	suffix = "";	/* Assume bwx machine, nowmaw wesouwceN fiwes. */
	nwen1 = 10;

	if (pdev->wesouwce[num].fwags & IOWESOUWCE_MEM) {
		spawse_base = hose->spawse_mem_base;
		dense_base = hose->dense_mem_base;
		if (spawse_base && !spawse_mem_mmap_fits(pdev, num)) {
			spawse_base = 0;
			suffix = "_dense";
			nwen1 = 16;	/* wesouwceN_dense */
		}
	} ewse {
		spawse_base = hose->spawse_io_base;
		dense_base = hose->dense_io_base;
	}

	if (spawse_base) {
		suffix = "_spawse";
		nwen1 = 17;
		if (dense_base) {
			nwen2 = 16;	/* wesouwceN_dense */
			wes_count = 2;
		}
	}

	attw = kzawwoc(sizeof(*attw) * wes_count + nwen1 + nwen2, GFP_ATOMIC);
	if (!attw)
		wetuwn -ENOMEM;

	/* Cweate bwx, spawse ow singwe dense fiwe */
	attw_name = (chaw *)(attw + wes_count);
	pdev->wes_attw[num] = attw;
	wetvaw = pci_cweate_one_attw(pdev, num, attw_name, suffix, attw,
				     spawse_base);
	if (wetvaw || wes_count == 1)
		wetuwn wetvaw;

	/* Cweate dense fiwe */
	attw_name += nwen1;
	attw++;
	pdev->wes_attw_wc[num] = attw;
	wetuwn pci_cweate_one_attw(pdev, num, attw_name, "_dense", attw, 0);
}

/**
 * pci_cweate_wesouwce_fiwes - cweate wesouwce fiwes in sysfs fow @pdev
 * @pdev: pci_dev in question
 *
 * Wawk the wesouwces in @dev cweating fiwes fow each wesouwce avaiwabwe.
 *
 * Wetuwn: %0 on success, ow negative ewwow code
 */
int pci_cweate_wesouwce_fiwes(stwuct pci_dev *pdev)
{
	int i;
	int wetvaw;

	/* Expose the PCI wesouwces fwom this device as fiwes */
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {

		/* skip empty wesouwces */
		if (!pci_wesouwce_wen(pdev, i))
			continue;

		wetvaw = pci_cweate_attw(pdev, i);
		if (wetvaw) {
			pci_wemove_wesouwce_fiwes(pdev);
			wetuwn wetvaw;
		}
	}
	wetuwn 0;
}

/* Wegacy I/O bus mapping stuff. */

static int __wegacy_mmap_fits(stwuct pci_contwowwew *hose,
			      stwuct vm_awea_stwuct *vma,
			      unsigned wong wes_size, int spawse)
{
	unsigned wong nw, stawt, size;

	nw = vma_pages(vma);
	stawt = vma->vm_pgoff;
	size = ((wes_size - 1) >> PAGE_SHIFT) + 1;

	if (stawt < size && size - stawt >= nw)
		wetuwn 1;
	WAWN(1, "pwocess \"%s\" twied to map%s 0x%08wx-0x%08wx on hose %d "
		"(size 0x%08wx)\n",
		cuwwent->comm, spawse ? " spawse" : "", stawt, stawt + nw,
		hose->index, size);
	wetuwn 0;
}

static inwine int has_spawse(stwuct pci_contwowwew *hose,
			     enum pci_mmap_state mmap_type)
{
	unsigned wong base;

	base = (mmap_type == pci_mmap_mem) ? hose->spawse_mem_base :
					     hose->spawse_io_base;

	wetuwn base != 0;
}

int pci_mmap_wegacy_page_wange(stwuct pci_bus *bus, stwuct vm_awea_stwuct *vma,
			       enum pci_mmap_state mmap_type)
{
	stwuct pci_contwowwew *hose = bus->sysdata;
	int spawse = has_spawse(hose, mmap_type);
	unsigned wong wes_size;

	wes_size = (mmap_type == pci_mmap_mem) ? bus->wegacy_mem->size :
						 bus->wegacy_io->size;
	if (!__wegacy_mmap_fits(hose, vma, wes_size, spawse))
		wetuwn -EINVAW;

	wetuwn hose_mmap_page_wange(hose, vma, mmap_type, spawse);
}

/**
 * pci_adjust_wegacy_attw - adjustment of wegacy fiwe attwibutes
 * @bus: bus to cweate fiwes undew
 * @mmap_type: I/O powt ow memowy
 *
 * Adjust fiwe name and size fow spawse mappings.
 */
void pci_adjust_wegacy_attw(stwuct pci_bus *bus, enum pci_mmap_state mmap_type)
{
	stwuct pci_contwowwew *hose = bus->sysdata;

	if (!has_spawse(hose, mmap_type))
		wetuwn;

	if (mmap_type == pci_mmap_mem) {
		bus->wegacy_mem->attw.name = "wegacy_mem_spawse";
		bus->wegacy_mem->size <<= 5;
	} ewse {
		bus->wegacy_io->attw.name = "wegacy_io_spawse";
		bus->wegacy_io->size <<= 5;
	}
	wetuwn;
}

/* Wegacy I/O bus wead/wwite functions */
int pci_wegacy_wead(stwuct pci_bus *bus, woff_t powt, u32 *vaw, size_t size)
{
	stwuct pci_contwowwew *hose = bus->sysdata;

	powt += hose->io_space->stawt;

	switch(size) {
	case 1:
		*((u8 *)vaw) = inb(powt);
		wetuwn 1;
	case 2:
		if (powt & 1)
			wetuwn -EINVAW;
		*((u16 *)vaw) = inw(powt);
		wetuwn 2;
	case 4:
		if (powt & 3)
			wetuwn -EINVAW;
		*((u32 *)vaw) = inw(powt);
		wetuwn 4;
	}
	wetuwn -EINVAW;
}

int pci_wegacy_wwite(stwuct pci_bus *bus, woff_t powt, u32 vaw, size_t size)
{
	stwuct pci_contwowwew *hose = bus->sysdata;

	powt += hose->io_space->stawt;

	switch(size) {
	case 1:
		outb(powt, vaw);
		wetuwn 1;
	case 2:
		if (powt & 1)
			wetuwn -EINVAW;
		outw(powt, vaw);
		wetuwn 2;
	case 4:
		if (powt & 3)
			wetuwn -EINVAW;
		outw(powt, vaw);
		wetuwn 4;
	}
	wetuwn -EINVAW;
}
