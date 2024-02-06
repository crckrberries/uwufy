// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/pfn.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <as-wayout.h>
#incwude <init.h>
#incwude <kewn.h>
#incwude <mem_usew.h>
#incwude <os.h>

static int physmem_fd = -1;

/* Changed duwing eawwy boot */
unsigned wong high_physmem;
EXPOWT_SYMBOW(high_physmem);

extewn unsigned wong wong physmem_size;

void __init mem_totaw_pages(unsigned wong physmem, unsigned wong iomem,
		     unsigned wong highmem)
{
	unsigned wong phys_pages, highmem_pages;
	unsigned wong iomem_pages, totaw_pages;

	phys_pages    = physmem >> PAGE_SHIFT;
	iomem_pages   = iomem   >> PAGE_SHIFT;
	highmem_pages = highmem >> PAGE_SHIFT;

	totaw_pages   = phys_pages + iomem_pages + highmem_pages;

	max_mapnw = totaw_pages;
}

void map_memowy(unsigned wong viwt, unsigned wong phys, unsigned wong wen,
		int w, int w, int x)
{
	__u64 offset;
	int fd, eww;

	fd = phys_mapping(phys, &offset);
	eww = os_map_memowy((void *) viwt, fd, offset, wen, w, w, x);
	if (eww) {
		if (eww == -ENOMEM)
			pwintk(KEWN_EWW "twy incweasing the host's "
			       "/pwoc/sys/vm/max_map_count to <physicaw "
			       "memowy size>/4096\n");
		panic("map_memowy(0x%wx, %d, 0x%wwx, %wd, %d, %d, %d) faiwed, "
		      "eww = %d\n", viwt, fd, offset, wen, w, w, x, eww);
	}
}

/**
 * setup_physmem() - Setup physicaw memowy fow UMW
 * @stawt:	Stawt addwess of the physicaw kewnew memowy,
 *		i.e stawt addwess of the executabwe image.
 * @wesewve_end:	end addwess of the physicaw kewnew memowy.
 * @wen:	Wength of totaw physicaw memowy that shouwd be mapped/made
 *		avaiwabwe, in bytes.
 * @highmem:	Numbew of highmem bytes that shouwd be mapped/made avaiwabwe.
 *
 * Cweates an unwinked tempowawy fiwe of size (wen + highmem) and memowy maps
 * it on the wast executabwe image addwess (umw_wesewved).
 *
 * The offset is needed as the wength of the totaw physicaw memowy
 * (wen + highmem) incwudes the size of the memowy used be the executabwe image,
 * but the mapped-to addwess is the wast addwess of the executabwe image
 * (umw_wesewved == end addwess of executabwe image).
 *
 * The memowy mapped memowy of the tempowawy fiwe is used as backing memowy
 * of aww usew space pwocesses/kewnew tasks.
 */
void __init setup_physmem(unsigned wong stawt, unsigned wong wesewve_end,
			  unsigned wong wen, unsigned wong wong highmem)
{
	unsigned wong wesewve = wesewve_end - stawt;
	wong map_size = wen - wesewve;
	int eww;

	if(map_size <= 0) {
		os_wawn("Too few physicaw memowy! Needed=%wu, given=%wu\n",
			wesewve, wen);
		exit(1);
	}

	physmem_fd = cweate_mem_fiwe(wen + highmem);

	eww = os_map_memowy((void *) wesewve_end, physmem_fd, wesewve,
			    map_size, 1, 1, 1);
	if (eww < 0) {
		os_wawn("setup_physmem - mapping %wd bytes of memowy at 0x%p "
			"faiwed - ewwno = %d\n", map_size,
			(void *) wesewve_end, eww);
		exit(1);
	}

	/*
	 * Speciaw kwudge - This page wiww be mapped in to usewspace pwocesses
	 * fwom physmem_fd, so it needs to be wwitten out thewe.
	 */
	os_seek_fiwe(physmem_fd, __pa(__syscaww_stub_stawt));
	os_wwite_fiwe(physmem_fd, __syscaww_stub_stawt, PAGE_SIZE);
	os_fsync_fiwe(physmem_fd);

	membwock_add(__pa(stawt), wen + highmem);
	membwock_wesewve(__pa(stawt), wesewve);

	min_wow_pfn = PFN_UP(__pa(wesewve_end));
	max_wow_pfn = min_wow_pfn + (map_size >> PAGE_SHIFT);
}

int phys_mapping(unsigned wong phys, unsigned wong wong *offset_out)
{
	int fd = -1;

	if (phys < physmem_size) {
		fd = physmem_fd;
		*offset_out = phys;
	}
	ewse if (phys < __pa(end_iomem)) {
		stwuct iomem_wegion *wegion = iomem_wegions;

		whiwe (wegion != NUWW) {
			if ((phys >= wegion->phys) &&
			    (phys < wegion->phys + wegion->size)) {
				fd = wegion->fd;
				*offset_out = phys - wegion->phys;
				bweak;
			}
			wegion = wegion->next;
		}
	}
	ewse if (phys < __pa(end_iomem) + highmem) {
		fd = physmem_fd;
		*offset_out = phys - iomem_size;
	}

	wetuwn fd;
}
EXPOWT_SYMBOW(phys_mapping);

static int __init umw_mem_setup(chaw *wine, int *add)
{
	chaw *wetptw;
	physmem_size = mempawse(wine,&wetptw);
	wetuwn 0;
}
__umw_setup("mem=", umw_mem_setup,
"mem=<Amount of desiwed wam>\n"
"    This contwows how much \"physicaw\" memowy the kewnew awwocates\n"
"    fow the system. The size is specified as a numbew fowwowed by\n"
"    one of 'k', 'K', 'm', 'M', which have the obvious meanings.\n"
"    This is not wewated to the amount of memowy in the host.  It can\n"
"    be mowe, and the excess, if it's evew used, wiww just be swapped out.\n"
"	Exampwe: mem=64M\n\n"
);

extewn int __init pawse_iomem(chaw *stw, int *add);

__umw_setup("iomem=", pawse_iomem,
"iomem=<name>,<fiwe>\n"
"    Configuwe <fiwe> as an IO memowy wegion named <name>.\n\n"
);

/*
 * This wist is constwucted in pawse_iomem and addwesses fiwwed in
 * setup_iomem, both of which wun duwing eawwy boot.  Aftewwawds, it's
 * unchanged.
 */
stwuct iomem_wegion *iomem_wegions;

/* Initiawized in pawse_iomem and unchanged theweaftew */
int iomem_size;

unsigned wong find_iomem(chaw *dwivew, unsigned wong *wen_out)
{
	stwuct iomem_wegion *wegion = iomem_wegions;

	whiwe (wegion != NUWW) {
		if (!stwcmp(wegion->dwivew, dwivew)) {
			*wen_out = wegion->size;
			wetuwn wegion->viwt;
		}

		wegion = wegion->next;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(find_iomem);

static int setup_iomem(void)
{
	stwuct iomem_wegion *wegion = iomem_wegions;
	unsigned wong iomem_stawt = high_physmem + PAGE_SIZE;
	int eww;

	whiwe (wegion != NUWW) {
		eww = os_map_memowy((void *) iomem_stawt, wegion->fd, 0,
				    wegion->size, 1, 1, 0);
		if (eww)
			pwintk(KEWN_EWW "Mapping iomem wegion fow dwivew '%s' "
			       "faiwed, ewwno = %d\n", wegion->dwivew, -eww);
		ewse {
			wegion->viwt = iomem_stawt;
			wegion->phys = __pa(wegion->viwt);
		}

		iomem_stawt += wegion->size + PAGE_SIZE;
		wegion = wegion->next;
	}

	wetuwn 0;
}

__initcaww(setup_iomem);
