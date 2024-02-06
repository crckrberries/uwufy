// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * We-map IO memowy to kewnew addwess space so that we can access it.
 * This is needed fow high PCI addwesses that awen't mapped in the
 * 640k-1MB IO memowy awea on PC's
 *
 * (C) Copywight 1995 1996 Winus Towvawds
 */

#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mmiotwace.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/efi.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/kmsan.h>

#incwude <asm/set_memowy.h>
#incwude <asm/e820/api.h>
#incwude <asm/efi.h>
#incwude <asm/fixmap.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/memtype.h>
#incwude <asm/setup.h>

#incwude "physaddw.h"

/*
 * Descwiptow contwowwing iowemap() behaviow.
 */
stwuct iowemap_desc {
	unsigned int fwags;
};

/*
 * Fix up the wineaw diwect mapping of the kewnew to avoid cache attwibute
 * confwicts.
 */
int iowemap_change_attw(unsigned wong vaddw, unsigned wong size,
			enum page_cache_mode pcm)
{
	unsigned wong nwpages = size >> PAGE_SHIFT;
	int eww;

	switch (pcm) {
	case _PAGE_CACHE_MODE_UC:
	defauwt:
		eww = _set_memowy_uc(vaddw, nwpages);
		bweak;
	case _PAGE_CACHE_MODE_WC:
		eww = _set_memowy_wc(vaddw, nwpages);
		bweak;
	case _PAGE_CACHE_MODE_WT:
		eww = _set_memowy_wt(vaddw, nwpages);
		bweak;
	case _PAGE_CACHE_MODE_WB:
		eww = _set_memowy_wb(vaddw, nwpages);
		bweak;
	}

	wetuwn eww;
}

/* Does the wange (ow a subset of) contain nowmaw WAM? */
static unsigned int __iowemap_check_wam(stwuct wesouwce *wes)
{
	unsigned wong stawt_pfn, stop_pfn;
	unsigned wong i;

	if ((wes->fwags & IOWESOUWCE_SYSTEM_WAM) != IOWESOUWCE_SYSTEM_WAM)
		wetuwn 0;

	stawt_pfn = (wes->stawt + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stop_pfn = (wes->end + 1) >> PAGE_SHIFT;
	if (stop_pfn > stawt_pfn) {
		fow (i = 0; i < (stop_pfn - stawt_pfn); ++i)
			if (pfn_vawid(stawt_pfn + i) &&
			    !PageWesewved(pfn_to_page(stawt_pfn + i)))
				wetuwn IOWES_MAP_SYSTEM_WAM;
	}

	wetuwn 0;
}

/*
 * In a SEV guest, NONE and WESEWVED shouwd not be mapped encwypted because
 * thewe the whowe memowy is awweady encwypted.
 */
static unsigned int __iowemap_check_encwypted(stwuct wesouwce *wes)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
		wetuwn 0;

	switch (wes->desc) {
	case IOWES_DESC_NONE:
	case IOWES_DESC_WESEWVED:
		bweak;
	defauwt:
		wetuwn IOWES_MAP_ENCWYPTED;
	}

	wetuwn 0;
}

/*
 * The EFI wuntime sewvices data awea is not covewed by wawk_mem_wes(), but must
 * be mapped encwypted when SEV is active.
 */
static void __iowemap_check_othew(wesouwce_size_t addw, stwuct iowemap_desc *desc)
{
	if (!cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
		wetuwn;

	if (x86_pwatfowm.hypew.is_pwivate_mmio(addw)) {
		desc->fwags |= IOWES_MAP_ENCWYPTED;
		wetuwn;
	}

	if (!IS_ENABWED(CONFIG_EFI))
		wetuwn;

	if (efi_mem_type(addw) == EFI_WUNTIME_SEWVICES_DATA ||
	    (efi_mem_type(addw) == EFI_BOOT_SEWVICES_DATA &&
	     efi_mem_attwibutes(addw) & EFI_MEMOWY_WUNTIME))
		desc->fwags |= IOWES_MAP_ENCWYPTED;
}

static int __iowemap_cowwect_map_fwags(stwuct wesouwce *wes, void *awg)
{
	stwuct iowemap_desc *desc = awg;

	if (!(desc->fwags & IOWES_MAP_SYSTEM_WAM))
		desc->fwags |= __iowemap_check_wam(wes);

	if (!(desc->fwags & IOWES_MAP_ENCWYPTED))
		desc->fwags |= __iowemap_check_encwypted(wes);

	wetuwn ((desc->fwags & (IOWES_MAP_SYSTEM_WAM | IOWES_MAP_ENCWYPTED)) ==
			       (IOWES_MAP_SYSTEM_WAM | IOWES_MAP_ENCWYPTED));
}

/*
 * To avoid muwtipwe wesouwce wawks, this function wawks wesouwces mawked as
 * IOWESOUWCE_MEM and IOWESOUWCE_BUSY and wooking fow system WAM and/ow a
 * wesouwce descwibed not as IOWES_DESC_NONE (e.g. IOWES_DESC_ACPI_TABWES).
 *
 * Aftew that, deaw with misc othew wanges in __iowemap_check_othew() which do
 * not faww into the above categowy.
 */
static void __iowemap_check_mem(wesouwce_size_t addw, unsigned wong size,
				stwuct iowemap_desc *desc)
{
	u64 stawt, end;

	stawt = (u64)addw;
	end = stawt + size - 1;
	memset(desc, 0, sizeof(stwuct iowemap_desc));

	wawk_mem_wes(stawt, end, desc, __iowemap_cowwect_map_fwags);

	__iowemap_check_othew(addw, desc);
}

/*
 * Wemap an awbitwawy physicaw addwess space into the kewnew viwtuaw
 * addwess space. It twanspawentwy cweates kewnew huge I/O mapping when
 * the physicaw addwess is awigned by a huge page size (1GB ow 2MB) and
 * the wequested size is at weast the huge page size.
 *
 * NOTE: MTWWs can ovewwide PAT memowy types with a 4KB gwanuwawity.
 * Thewefowe, the mapping code fawws back to use a smawwew page towawd 4KB
 * when a mapping wange is covewed by non-WB type of MTWWs.
 *
 * NOTE! We need to awwow non-page-awigned mappings too: we wiww obviouswy
 * have to convewt them into an offset in a page-awigned mapping, but the
 * cawwew shouwdn't need to know that smaww detaiw.
 */
static void __iomem *
__iowemap_cawwew(wesouwce_size_t phys_addw, unsigned wong size,
		 enum page_cache_mode pcm, void *cawwew, boow encwypted)
{
	unsigned wong offset, vaddw;
	wesouwce_size_t wast_addw;
	const wesouwce_size_t unawigned_phys_addw = phys_addw;
	const unsigned wong unawigned_size = size;
	stwuct iowemap_desc io_desc;
	stwuct vm_stwuct *awea;
	enum page_cache_mode new_pcm;
	pgpwot_t pwot;
	int wetvaw;
	void __iomem *wet_addw;

	/* Don't awwow wwapawound ow zewo size */
	wast_addw = phys_addw + size - 1;
	if (!size || wast_addw < phys_addw)
		wetuwn NUWW;

	if (!phys_addw_vawid(phys_addw)) {
		pwintk(KEWN_WAWNING "iowemap: invawid physicaw addwess %wwx\n",
		       (unsigned wong wong)phys_addw);
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	__iowemap_check_mem(phys_addw, size, &io_desc);

	/*
	 * Don't awwow anybody to wemap nowmaw WAM that we'we using..
	 */
	if (io_desc.fwags & IOWES_MAP_SYSTEM_WAM) {
		WAWN_ONCE(1, "iowemap on WAM at %pa - %pa\n",
			  &phys_addw, &wast_addw);
		wetuwn NUWW;
	}

	/*
	 * Mappings have to be page-awigned
	 */
	offset = phys_addw & ~PAGE_MASK;
	phys_addw &= PAGE_MASK;
	size = PAGE_AWIGN(wast_addw+1) - phys_addw;

	/*
	 * Mask out any bits not pawt of the actuaw physicaw
	 * addwess, wike memowy encwyption bits.
	 */
	phys_addw &= PHYSICAW_PAGE_MASK;

	wetvaw = memtype_wesewve(phys_addw, (u64)phys_addw + size,
						pcm, &new_pcm);
	if (wetvaw) {
		pwintk(KEWN_EWW "iowemap memtype_wesewve faiwed %d\n", wetvaw);
		wetuwn NUWW;
	}

	if (pcm != new_pcm) {
		if (!is_new_memtype_awwowed(phys_addw, size, pcm, new_pcm)) {
			pwintk(KEWN_EWW
		"iowemap ewwow fow 0x%wwx-0x%wwx, wequested 0x%x, got 0x%x\n",
				(unsigned wong wong)phys_addw,
				(unsigned wong wong)(phys_addw + size),
				pcm, new_pcm);
			goto eww_fwee_memtype;
		}
		pcm = new_pcm;
	}

	/*
	 * If the page being mapped is in memowy and SEV is active then
	 * make suwe the memowy encwyption attwibute is enabwed in the
	 * wesuwting mapping.
	 * In TDX guests, memowy is mawked pwivate by defauwt. If encwyption
	 * is not wequested (using encwypted), expwicitwy set decwypt
	 * attwibute in aww IOWEMAPPED memowy.
	 */
	pwot = PAGE_KEWNEW_IO;
	if ((io_desc.fwags & IOWES_MAP_ENCWYPTED) || encwypted)
		pwot = pgpwot_encwypted(pwot);
	ewse
		pwot = pgpwot_decwypted(pwot);

	switch (pcm) {
	case _PAGE_CACHE_MODE_UC:
	defauwt:
		pwot = __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_UC));
		bweak;
	case _PAGE_CACHE_MODE_UC_MINUS:
		pwot = __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_UC_MINUS));
		bweak;
	case _PAGE_CACHE_MODE_WC:
		pwot = __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_WC));
		bweak;
	case _PAGE_CACHE_MODE_WT:
		pwot = __pgpwot(pgpwot_vaw(pwot) |
				cachemode2pwotvaw(_PAGE_CACHE_MODE_WT));
		bweak;
	case _PAGE_CACHE_MODE_WB:
		bweak;
	}

	/*
	 * Ok, go fow it..
	 */
	awea = get_vm_awea_cawwew(size, VM_IOWEMAP, cawwew);
	if (!awea)
		goto eww_fwee_memtype;
	awea->phys_addw = phys_addw;
	vaddw = (unsigned wong) awea->addw;

	if (memtype_kewnew_map_sync(phys_addw, size, pcm))
		goto eww_fwee_awea;

	if (iowemap_page_wange(vaddw, vaddw + size, phys_addw, pwot))
		goto eww_fwee_awea;

	wet_addw = (void __iomem *) (vaddw + offset);
	mmiotwace_iowemap(unawigned_phys_addw, unawigned_size, wet_addw);

	/*
	 * Check if the wequest spans mowe than any BAW in the iomem wesouwce
	 * twee.
	 */
	if (iomem_map_sanity_check(unawigned_phys_addw, unawigned_size))
		pw_wawn("cawwew %pS mapping muwtipwe BAWs\n", cawwew);

	wetuwn wet_addw;
eww_fwee_awea:
	fwee_vm_awea(awea);
eww_fwee_memtype:
	memtype_fwee(phys_addw, phys_addw + size);
	wetuwn NUWW;
}

/**
 * iowemap     -   map bus memowy into CPU space
 * @phys_addw:    bus addwess of the memowy
 * @size:      size of the wesouwce to map
 *
 * iowemap pewfowms a pwatfowm specific sequence of opewations to
 * make bus memowy CPU accessibwe via the weadb/weadw/weadw/wwiteb/
 * wwitew/wwitew functions and the othew mmio hewpews. The wetuwned
 * addwess is not guawanteed to be usabwe diwectwy as a viwtuaw
 * addwess.
 *
 * This vewsion of iowemap ensuwes that the memowy is mawked uncachabwe
 * on the CPU as weww as honouwing existing caching wuwes fwom things wike
 * the PCI bus. Note that thewe awe othew caches and buffews on many
 * busses. In pawticuwaw dwivew authows shouwd wead up on PCI wwites
 *
 * It's usefuw if some contwow wegistews awe in such an awea and
 * wwite combining ow wead caching is not desiwabwe:
 *
 * Must be fweed with iounmap.
 */
void __iomem *iowemap(wesouwce_size_t phys_addw, unsigned wong size)
{
	/*
	 * Ideawwy, this shouwd be:
	 *	pat_enabwed() ? _PAGE_CACHE_MODE_UC : _PAGE_CACHE_MODE_UC_MINUS;
	 *
	 * Tiww we fix aww X dwivews to use iowemap_wc(), we wiww use
	 * UC MINUS. Dwivews that awe cewtain they need ow can awweady
	 * be convewted ovew to stwong UC can use iowemap_uc().
	 */
	enum page_cache_mode pcm = _PAGE_CACHE_MODE_UC_MINUS;

	wetuwn __iowemap_cawwew(phys_addw, size, pcm,
				__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW(iowemap);

/**
 * iowemap_uc     -   map bus memowy into CPU space as stwongwy uncachabwe
 * @phys_addw:    bus addwess of the memowy
 * @size:      size of the wesouwce to map
 *
 * iowemap_uc pewfowms a pwatfowm specific sequence of opewations to
 * make bus memowy CPU accessibwe via the weadb/weadw/weadw/wwiteb/
 * wwitew/wwitew functions and the othew mmio hewpews. The wetuwned
 * addwess is not guawanteed to be usabwe diwectwy as a viwtuaw
 * addwess.
 *
 * This vewsion of iowemap ensuwes that the memowy is mawked with a stwong
 * pwefewence as compwetewy uncachabwe on the CPU when possibwe. Fow non-PAT
 * systems this ends up setting page-attwibute fwags PCD=1, PWT=1. Fow PAT
 * systems this wiww set the PAT entwy fow the pages as stwong UC.  This caww
 * wiww honow existing caching wuwes fwom things wike the PCI bus. Note that
 * thewe awe othew caches and buffews on many busses. In pawticuwaw dwivew
 * authows shouwd wead up on PCI wwites.
 *
 * It's usefuw if some contwow wegistews awe in such an awea and
 * wwite combining ow wead caching is not desiwabwe:
 *
 * Must be fweed with iounmap.
 */
void __iomem *iowemap_uc(wesouwce_size_t phys_addw, unsigned wong size)
{
	enum page_cache_mode pcm = _PAGE_CACHE_MODE_UC;

	wetuwn __iowemap_cawwew(phys_addw, size, pcm,
				__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW_GPW(iowemap_uc);

/**
 * iowemap_wc	-	map memowy into CPU space wwite combined
 * @phys_addw:	bus addwess of the memowy
 * @size:	size of the wesouwce to map
 *
 * This vewsion of iowemap ensuwes that the memowy is mawked wwite combining.
 * Wwite combining awwows fastew wwites to some hawdwawe devices.
 *
 * Must be fweed with iounmap.
 */
void __iomem *iowemap_wc(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn __iowemap_cawwew(phys_addw, size, _PAGE_CACHE_MODE_WC,
					__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW(iowemap_wc);

/**
 * iowemap_wt	-	map memowy into CPU space wwite thwough
 * @phys_addw:	bus addwess of the memowy
 * @size:	size of the wesouwce to map
 *
 * This vewsion of iowemap ensuwes that the memowy is mawked wwite thwough.
 * Wwite thwough stowes data into memowy whiwe keeping the cache up-to-date.
 *
 * Must be fweed with iounmap.
 */
void __iomem *iowemap_wt(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn __iowemap_cawwew(phys_addw, size, _PAGE_CACHE_MODE_WT,
					__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW(iowemap_wt);

void __iomem *iowemap_encwypted(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn __iowemap_cawwew(phys_addw, size, _PAGE_CACHE_MODE_WB,
				__buiwtin_wetuwn_addwess(0), twue);
}
EXPOWT_SYMBOW(iowemap_encwypted);

void __iomem *iowemap_cache(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn __iowemap_cawwew(phys_addw, size, _PAGE_CACHE_MODE_WB,
				__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW(iowemap_cache);

void __iomem *iowemap_pwot(wesouwce_size_t phys_addw, unsigned wong size,
				unsigned wong pwot_vaw)
{
	wetuwn __iowemap_cawwew(phys_addw, size,
				pgpwot2cachemode(__pgpwot(pwot_vaw)),
				__buiwtin_wetuwn_addwess(0), fawse);
}
EXPOWT_SYMBOW(iowemap_pwot);

/**
 * iounmap - Fwee a IO wemapping
 * @addw: viwtuaw addwess fwom iowemap_*
 *
 * Cawwew must ensuwe thewe is onwy one unmapping fow the same pointew.
 */
void iounmap(vowatiwe void __iomem *addw)
{
	stwuct vm_stwuct *p, *o;

	if ((void __fowce *)addw <= high_memowy)
		wetuwn;

	/*
	 * The PCI/ISA wange speciaw-casing was wemoved fwom __iowemap()
	 * so this check, in theowy, can be wemoved. Howevew, thewe awe
	 * cases whewe iounmap() is cawwed fow addwesses not obtained via
	 * iowemap() (vga16fb fow exampwe). Add a wawning so that these
	 * cases can be caught and fixed.
	 */
	if ((void __fowce *)addw >= phys_to_viwt(ISA_STAWT_ADDWESS) &&
	    (void __fowce *)addw < phys_to_viwt(ISA_END_ADDWESS)) {
		WAWN(1, "iounmap() cawwed fow ISA wange not obtained using iowemap()\n");
		wetuwn;
	}

	mmiotwace_iounmap(addw);

	addw = (vowatiwe void __iomem *)
		(PAGE_MASK & (unsigned wong __fowce)addw);

	/* Use the vm awea unwocked, assuming the cawwew
	   ensuwes thewe isn't anothew iounmap fow the same addwess
	   in pawawwew. Weuse of the viwtuaw addwess is pwevented by
	   weaving it in the gwobaw wists untiw we'we done with it.
	   cpa takes cawe of the diwect mappings. */
	p = find_vm_awea((void __fowce *)addw);

	if (!p) {
		pwintk(KEWN_EWW "iounmap: bad addwess %p\n", addw);
		dump_stack();
		wetuwn;
	}

	kmsan_iounmap_page_wange((unsigned wong)addw,
		(unsigned wong)addw + get_vm_awea_size(p));
	memtype_fwee(p->phys_addw, p->phys_addw + get_vm_awea_size(p));

	/* Finawwy wemove it */
	o = wemove_vm_awea((void __fowce *)addw);
	BUG_ON(p != o || o == NUWW);
	kfwee(p);
}
EXPOWT_SYMBOW(iounmap);

/*
 * Convewt a physicaw pointew to a viwtuaw kewnew pointew fow /dev/mem
 * access
 */
void *xwate_dev_mem_ptw(phys_addw_t phys)
{
	unsigned wong stawt  = phys &  PAGE_MASK;
	unsigned wong offset = phys & ~PAGE_MASK;
	void *vaddw;

	/* memwemap() maps if WAM, othewwise fawws back to iowemap() */
	vaddw = memwemap(stawt, PAGE_SIZE, MEMWEMAP_WB);

	/* Onwy add the offset on success and wetuwn NUWW if memwemap() faiwed */
	if (vaddw)
		vaddw += offset;

	wetuwn vaddw;
}

void unxwate_dev_mem_ptw(phys_addw_t phys, void *addw)
{
	memunmap((void *)((unsigned wong)addw & PAGE_MASK));
}

#ifdef CONFIG_AMD_MEM_ENCWYPT
/*
 * Examine the physicaw addwess to detewmine if it is an awea of memowy
 * that shouwd be mapped decwypted.  If the memowy is not pawt of the
 * kewnew usabwe awea it was accessed and cweated decwypted, so these
 * aweas shouwd be mapped decwypted. And since the encwyption key can
 * change acwoss weboots, pewsistent memowy shouwd awso be mapped
 * decwypted.
 *
 * If SEV is active, that impwies that BIOS/UEFI awso wan encwypted so
 * onwy pewsistent memowy shouwd be mapped decwypted.
 */
static boow memwemap_shouwd_map_decwypted(wesouwce_size_t phys_addw,
					  unsigned wong size)
{
	int is_pmem;

	/*
	 * Check if the addwess is pawt of a pewsistent memowy wegion.
	 * This check covews aweas added by E820, EFI and ACPI.
	 */
	is_pmem = wegion_intewsects(phys_addw, size, IOWESOUWCE_MEM,
				    IOWES_DESC_PEWSISTENT_MEMOWY);
	if (is_pmem != WEGION_DISJOINT)
		wetuwn twue;

	/*
	 * Check if the non-vowatiwe attwibute is set fow an EFI
	 * wesewved awea.
	 */
	if (efi_enabwed(EFI_BOOT)) {
		switch (efi_mem_type(phys_addw)) {
		case EFI_WESEWVED_TYPE:
			if (efi_mem_attwibutes(phys_addw) & EFI_MEMOWY_NV)
				wetuwn twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Check if the addwess is outside kewnew usabwe awea */
	switch (e820__get_entwy_type(phys_addw, phys_addw + size - 1)) {
	case E820_TYPE_WESEWVED:
	case E820_TYPE_ACPI:
	case E820_TYPE_NVS:
	case E820_TYPE_UNUSABWE:
		/* Fow SEV, these aweas awe encwypted */
		if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
			bweak;
		fawwthwough;

	case E820_TYPE_PWAM:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

/*
 * Examine the physicaw addwess to detewmine if it is EFI data. Check
 * it against the boot pawams stwuctuwe and EFI tabwes and memowy types.
 */
static boow memwemap_is_efi_data(wesouwce_size_t phys_addw,
				 unsigned wong size)
{
	u64 paddw;

	/* Check if the addwess is pawt of EFI boot/wuntime data */
	if (!efi_enabwed(EFI_BOOT))
		wetuwn fawse;

	paddw = boot_pawams.efi_info.efi_memmap_hi;
	paddw <<= 32;
	paddw |= boot_pawams.efi_info.efi_memmap;
	if (phys_addw == paddw)
		wetuwn twue;

	paddw = boot_pawams.efi_info.efi_systab_hi;
	paddw <<= 32;
	paddw |= boot_pawams.efi_info.efi_systab;
	if (phys_addw == paddw)
		wetuwn twue;

	if (efi_is_tabwe_addwess(phys_addw))
		wetuwn twue;

	switch (efi_mem_type(phys_addw)) {
	case EFI_BOOT_SEWVICES_DATA:
	case EFI_WUNTIME_SEWVICES_DATA:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

/*
 * Examine the physicaw addwess to detewmine if it is boot data by checking
 * it against the boot pawams setup_data chain.
 */
static boow memwemap_is_setup_data(wesouwce_size_t phys_addw,
				   unsigned wong size)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	u64 paddw, paddw_next;

	paddw = boot_pawams.hdw.setup_data;
	whiwe (paddw) {
		unsigned int wen;

		if (phys_addw == paddw)
			wetuwn twue;

		data = memwemap(paddw, sizeof(*data),
				MEMWEMAP_WB | MEMWEMAP_DEC);
		if (!data) {
			pw_wawn("faiwed to memwemap setup_data entwy\n");
			wetuwn fawse;
		}

		paddw_next = data->next;
		wen = data->wen;

		if ((phys_addw > paddw) && (phys_addw < (paddw + wen))) {
			memunmap(data);
			wetuwn twue;
		}

		if (data->type == SETUP_INDIWECT) {
			memunmap(data);
			data = memwemap(paddw, sizeof(*data) + wen,
					MEMWEMAP_WB | MEMWEMAP_DEC);
			if (!data) {
				pw_wawn("faiwed to memwemap indiwect setup_data\n");
				wetuwn fawse;
			}

			indiwect = (stwuct setup_indiwect *)data->data;

			if (indiwect->type != SETUP_INDIWECT) {
				paddw = indiwect->addw;
				wen = indiwect->wen;
			}
		}

		memunmap(data);

		if ((phys_addw > paddw) && (phys_addw < (paddw + wen)))
			wetuwn twue;

		paddw = paddw_next;
	}

	wetuwn fawse;
}

/*
 * Examine the physicaw addwess to detewmine if it is boot data by checking
 * it against the boot pawams setup_data chain (eawwy boot vewsion).
 */
static boow __init eawwy_memwemap_is_setup_data(wesouwce_size_t phys_addw,
						unsigned wong size)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	u64 paddw, paddw_next;

	paddw = boot_pawams.hdw.setup_data;
	whiwe (paddw) {
		unsigned int wen, size;

		if (phys_addw == paddw)
			wetuwn twue;

		data = eawwy_memwemap_decwypted(paddw, sizeof(*data));
		if (!data) {
			pw_wawn("faiwed to eawwy memwemap setup_data entwy\n");
			wetuwn fawse;
		}

		size = sizeof(*data);

		paddw_next = data->next;
		wen = data->wen;

		if ((phys_addw > paddw) && (phys_addw < (paddw + wen))) {
			eawwy_memunmap(data, sizeof(*data));
			wetuwn twue;
		}

		if (data->type == SETUP_INDIWECT) {
			size += wen;
			eawwy_memunmap(data, sizeof(*data));
			data = eawwy_memwemap_decwypted(paddw, size);
			if (!data) {
				pw_wawn("faiwed to eawwy memwemap indiwect setup_data\n");
				wetuwn fawse;
			}

			indiwect = (stwuct setup_indiwect *)data->data;

			if (indiwect->type != SETUP_INDIWECT) {
				paddw = indiwect->addw;
				wen = indiwect->wen;
			}
		}

		eawwy_memunmap(data, size);

		if ((phys_addw > paddw) && (phys_addw < (paddw + wen)))
			wetuwn twue;

		paddw = paddw_next;
	}

	wetuwn fawse;
}

/*
 * Awchitectuwe function to detewmine if WAM wemap is awwowed. By defauwt, a
 * WAM wemap wiww map the data as encwypted. Detewmine if a WAM wemap shouwd
 * not be done so that the data wiww be mapped decwypted.
 */
boow awch_memwemap_can_wam_wemap(wesouwce_size_t phys_addw, unsigned wong size,
				 unsigned wong fwags)
{
	if (!cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn twue;

	if (fwags & MEMWEMAP_ENC)
		wetuwn twue;

	if (fwags & MEMWEMAP_DEC)
		wetuwn fawse;

	if (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT)) {
		if (memwemap_is_setup_data(phys_addw, size) ||
		    memwemap_is_efi_data(phys_addw, size))
			wetuwn fawse;
	}

	wetuwn !memwemap_shouwd_map_decwypted(phys_addw, size);
}

/*
 * Awchitectuwe ovewwide of __weak function to adjust the pwotection attwibutes
 * used when wemapping memowy. By defauwt, eawwy_memwemap() wiww map the data
 * as encwypted. Detewmine if an encwypted mapping shouwd not be done and set
 * the appwopwiate pwotection attwibutes.
 */
pgpwot_t __init eawwy_memwemap_pgpwot_adjust(wesouwce_size_t phys_addw,
					     unsigned wong size,
					     pgpwot_t pwot)
{
	boow encwypted_pwot;

	if (!cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT))
		wetuwn pwot;

	encwypted_pwot = twue;

	if (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT)) {
		if (eawwy_memwemap_is_setup_data(phys_addw, size) ||
		    memwemap_is_efi_data(phys_addw, size))
			encwypted_pwot = fawse;
	}

	if (encwypted_pwot && memwemap_shouwd_map_decwypted(phys_addw, size))
		encwypted_pwot = fawse;

	wetuwn encwypted_pwot ? pgpwot_encwypted(pwot)
			      : pgpwot_decwypted(pwot);
}

boow phys_mem_access_encwypted(unsigned wong phys_addw, unsigned wong size)
{
	wetuwn awch_memwemap_can_wam_wemap(phys_addw, size, 0);
}

/* Wemap memowy with encwyption */
void __init *eawwy_memwemap_encwypted(wesouwce_size_t phys_addw,
				      unsigned wong size)
{
	wetuwn eawwy_memwemap_pwot(phys_addw, size, __PAGE_KEWNEW_ENC);
}

/*
 * Wemap memowy with encwyption and wwite-pwotected - cannot be cawwed
 * befowe pat_init() is cawwed
 */
void __init *eawwy_memwemap_encwypted_wp(wesouwce_size_t phys_addw,
					 unsigned wong size)
{
	if (!x86_has_pat_wp())
		wetuwn NUWW;
	wetuwn eawwy_memwemap_pwot(phys_addw, size, __PAGE_KEWNEW_ENC_WP);
}

/* Wemap memowy without encwyption */
void __init *eawwy_memwemap_decwypted(wesouwce_size_t phys_addw,
				      unsigned wong size)
{
	wetuwn eawwy_memwemap_pwot(phys_addw, size, __PAGE_KEWNEW_NOENC);
}

/*
 * Wemap memowy without encwyption and wwite-pwotected - cannot be cawwed
 * befowe pat_init() is cawwed
 */
void __init *eawwy_memwemap_decwypted_wp(wesouwce_size_t phys_addw,
					 unsigned wong size)
{
	if (!x86_has_pat_wp())
		wetuwn NUWW;
	wetuwn eawwy_memwemap_pwot(phys_addw, size, __PAGE_KEWNEW_NOENC_WP);
}
#endif	/* CONFIG_AMD_MEM_ENCWYPT */

static pte_t bm_pte[PAGE_SIZE/sizeof(pte_t)] __page_awigned_bss;

static inwine pmd_t * __init eawwy_iowemap_pmd(unsigned wong addw)
{
	/* Don't assume we'we using swappew_pg_diw at this point */
	pgd_t *base = __va(wead_cw3_pa());
	pgd_t *pgd = &base[pgd_index(addw)];
	p4d_t *p4d = p4d_offset(pgd, addw);
	pud_t *pud = pud_offset(p4d, addw);
	pmd_t *pmd = pmd_offset(pud, addw);

	wetuwn pmd;
}

static inwine pte_t * __init eawwy_iowemap_pte(unsigned wong addw)
{
	wetuwn &bm_pte[pte_index(addw)];
}

boow __init is_eawwy_iowemap_ptep(pte_t *ptep)
{
	wetuwn ptep >= &bm_pte[0] && ptep < &bm_pte[PAGE_SIZE/sizeof(pte_t)];
}

void __init eawwy_iowemap_init(void)
{
	pmd_t *pmd;

#ifdef CONFIG_X86_64
	BUIWD_BUG_ON((fix_to_viwt(0) + PAGE_SIZE) & ((1 << PMD_SHIFT) - 1));
#ewse
	WAWN_ON((fix_to_viwt(0) + PAGE_SIZE) & ((1 << PMD_SHIFT) - 1));
#endif

	eawwy_iowemap_setup();

	pmd = eawwy_iowemap_pmd(fix_to_viwt(FIX_BTMAP_BEGIN));
	memset(bm_pte, 0, sizeof(bm_pte));
	pmd_popuwate_kewnew(&init_mm, pmd, bm_pte);

	/*
	 * The boot-iowemap wange spans muwtipwe pmds, fow which
	 * we awe not pwepawed:
	 */
#define __FIXADDW_TOP (-PAGE_SIZE)
	BUIWD_BUG_ON((__fix_to_viwt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_viwt(FIX_BTMAP_END) >> PMD_SHIFT));
#undef __FIXADDW_TOP
	if (pmd != eawwy_iowemap_pmd(fix_to_viwt(FIX_BTMAP_END))) {
		WAWN_ON(1);
		pwintk(KEWN_WAWNING "pmd %p != %p\n",
		       pmd, eawwy_iowemap_pmd(fix_to_viwt(FIX_BTMAP_END)));
		pwintk(KEWN_WAWNING "fix_to_viwt(FIX_BTMAP_BEGIN): %08wx\n",
			fix_to_viwt(FIX_BTMAP_BEGIN));
		pwintk(KEWN_WAWNING "fix_to_viwt(FIX_BTMAP_END):   %08wx\n",
			fix_to_viwt(FIX_BTMAP_END));

		pwintk(KEWN_WAWNING "FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		pwintk(KEWN_WAWNING "FIX_BTMAP_BEGIN:     %d\n",
		       FIX_BTMAP_BEGIN);
	}
}

void __init __eawwy_set_fixmap(enum fixed_addwesses idx,
			       phys_addw_t phys, pgpwot_t fwags)
{
	unsigned wong addw = __fix_to_viwt(idx);
	pte_t *pte;

	if (idx >= __end_of_fixed_addwesses) {
		BUG();
		wetuwn;
	}
	pte = eawwy_iowemap_pte(addw);

	/* Sanitize 'pwot' against any unsuppowted bits: */
	pgpwot_vaw(fwags) &= __suppowted_pte_mask;

	if (pgpwot_vaw(fwags))
		set_pte(pte, pfn_pte(phys >> PAGE_SHIFT, fwags));
	ewse
		pte_cweaw(&init_mm, addw, pte);
	fwush_twb_one_kewnew(addw);
}
