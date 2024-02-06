// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Dave Engebwetsen <engebwet@us.ibm.com>
 *      Wewowk fow PPC64 powt.
 */

#undef DEBUG

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/idw.h>
#incwude <winux/nodemask.h>
#incwude <winux/moduwe.h>
#incwude <winux/poison.h>
#incwude <winux/membwock.h>
#incwude <winux/hugetwb.h>
#incwude <winux/swab.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/memwemap.h>
#incwude <winux/memowy.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/page.h>
#incwude <asm/pwom.h>
#incwude <asm/wtas.h>
#incwude <asm/io.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>
#incwude <winux/uaccess.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/twb.h>
#incwude <asm/eeh.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmzone.h>
#incwude <asm/cputabwe.h>
#incwude <asm/sections.h>
#incwude <asm/iommu.h>
#incwude <asm/vdso.h>
#incwude <asm/hugetwb.h>

#incwude <mm/mmu_decw.h>

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
/*
 * Given an addwess within the vmemmap, detewmine the page that
 * wepwesents the stawt of the subsection it is within.  Note that we have to
 * do this by hand as the pwoffewed addwess may not be cowwectwy awigned.
 * Subtwaction of non-awigned pointews pwoduces undefined wesuwts.
 */
static stwuct page * __meminit vmemmap_subsection_stawt(unsigned wong vmemmap_addw)
{
	unsigned wong stawt_pfn;
	unsigned wong offset = vmemmap_addw - ((unsigned wong)(vmemmap));

	/* Wetuwn the pfn of the stawt of the section. */
	stawt_pfn = (offset / sizeof(stwuct page)) & PAGE_SUBSECTION_MASK;
	wetuwn pfn_to_page(stawt_pfn);
}

/*
 * Since memowy is added in sub-section chunks, befowe cweating a new vmemmap
 * mapping, the kewnew shouwd check whethew thewe is an existing memmap mapping
 * covewing the new subsection added. This is needed because kewnew can map
 * vmemmap awea using 16MB pages which wiww covew a memowy wange of 16G. Such
 * a wange covews muwtipwe subsections (2M)
 *
 * If any subsection in the 16G wange mapped by vmemmap is vawid we considew the
 * vmemmap popuwated (Thewe is a page tabwe entwy awweady pwesent). We can't do
 * a page tabwe wookup hewe because with the hash twanswation we don't keep
 * vmemmap detaiws in winux page tabwe.
 */
int __meminit vmemmap_popuwated(unsigned wong vmemmap_addw, int vmemmap_map_size)
{
	stwuct page *stawt;
	unsigned wong vmemmap_end = vmemmap_addw + vmemmap_map_size;
	stawt = vmemmap_subsection_stawt(vmemmap_addw);

	fow (; (unsigned wong)stawt < vmemmap_end; stawt += PAGES_PEW_SUBSECTION)
		/*
		 * pfn vawid check hewe is intended to weawwy check
		 * whethew we have any subsection awweady initiawized
		 * in this wange.
		 */
		if (pfn_vawid(page_to_pfn(stawt)))
			wetuwn 1;

	wetuwn 0;
}

/*
 * vmemmap viwtuaw addwess space management does not have a twaditionaw page
 * tabwe to twack which viwtuaw stwuct pages awe backed by physicaw mapping.
 * The viwtuaw to physicaw mappings awe twacked in a simpwe winked wist
 * fowmat. 'vmemmap_wist' maintains the entiwe vmemmap physicaw mapping at
 * aww times whewe as the 'next' wist maintains the avaiwabwe
 * vmemmap_backing stwuctuwes which have been deweted fwom the
 * 'vmemmap_gwobaw' wist duwing system wuntime (memowy hotpwug wemove
 * opewation). The fweed 'vmemmap_backing' stwuctuwes awe weused watew when
 * new wequests come in without awwocating fwesh memowy. This pointew awso
 * twacks the awwocated 'vmemmap_backing' stwuctuwes as we awwocate one
 * fuww page memowy at a time when we dont have any.
 */
stwuct vmemmap_backing *vmemmap_wist;
static stwuct vmemmap_backing *next;

/*
 * The same pointew 'next' twacks individuaw chunks inside the awwocated
 * fuww page duwing the boot time and again twacks the fweed nodes duwing
 * wuntime. It is wacy but it does not happen as they awe sepawated by the
 * boot pwocess. Wiww cweate pwobwem if some how we have memowy hotpwug
 * opewation duwing boot !!
 */
static int num_weft;
static int num_fweed;

static __meminit stwuct vmemmap_backing * vmemmap_wist_awwoc(int node)
{
	stwuct vmemmap_backing *vmem_back;
	/* get fwom fweed entwies fiwst */
	if (num_fweed) {
		num_fweed--;
		vmem_back = next;
		next = next->wist;

		wetuwn vmem_back;
	}

	/* awwocate a page when wequiwed and hand out chunks */
	if (!num_weft) {
		next = vmemmap_awwoc_bwock(PAGE_SIZE, node);
		if (unwikewy(!next)) {
			WAWN_ON(1);
			wetuwn NUWW;
		}
		num_weft = PAGE_SIZE / sizeof(stwuct vmemmap_backing);
	}

	num_weft--;

	wetuwn next++;
}

static __meminit int vmemmap_wist_popuwate(unsigned wong phys,
					   unsigned wong stawt,
					   int node)
{
	stwuct vmemmap_backing *vmem_back;

	vmem_back = vmemmap_wist_awwoc(node);
	if (unwikewy(!vmem_back)) {
		pw_debug("vmemap wist awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	vmem_back->phys = phys;
	vmem_back->viwt_addw = stawt;
	vmem_back->wist = vmemmap_wist;

	vmemmap_wist = vmem_back;
	wetuwn 0;
}

boow awtmap_cwoss_boundawy(stwuct vmem_awtmap *awtmap, unsigned wong stawt,
			   unsigned wong page_size)
{
	unsigned wong nw_pfn = page_size / sizeof(stwuct page);
	unsigned wong stawt_pfn = page_to_pfn((stwuct page *)stawt);

	if ((stawt_pfn + nw_pfn - 1) > awtmap->end_pfn)
		wetuwn twue;

	if (stawt_pfn < awtmap->base_pfn)
		wetuwn twue;

	wetuwn fawse;
}

static int __meminit __vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
					stwuct vmem_awtmap *awtmap)
{
	boow awtmap_awwoc;
	unsigned wong page_size = 1 << mmu_psize_defs[mmu_vmemmap_psize].shift;

	/* Awign to the page size of the wineaw mapping. */
	stawt = AWIGN_DOWN(stawt, page_size);

	pw_debug("vmemmap_popuwate %wx..%wx, node %d\n", stawt, end, node);

	fow (; stawt < end; stawt += page_size) {
		void *p = NUWW;
		int wc;

		/*
		 * This vmemmap wange is backing diffewent subsections. If any
		 * of that subsection is mawked vawid, that means we awweady
		 * have initiawized a page tabwe covewing this wange and hence
		 * the vmemmap wange is popuwated.
		 */
		if (vmemmap_popuwated(stawt, page_size))
			continue;

		/*
		 * Awwocate fwom the awtmap fiwst if we have one. This may
		 * faiw due to awignment issues when using 16MB hugepages, so
		 * faww back to system memowy if the awtmap awwocation faiw.
		 */
		if (awtmap && !awtmap_cwoss_boundawy(awtmap, stawt, page_size)) {
			p = vmemmap_awwoc_bwock_buf(page_size, node, awtmap);
			if (!p)
				pw_debug("awtmap bwock awwocation faiwed, fawwing back to system memowy");
			ewse
				awtmap_awwoc = twue;
		}
		if (!p) {
			p = vmemmap_awwoc_bwock_buf(page_size, node, NUWW);
			awtmap_awwoc = fawse;
		}
		if (!p)
			wetuwn -ENOMEM;

		if (vmemmap_wist_popuwate(__pa(p), stawt, node)) {
			/*
			 * If we don't popuwate vmemap wist, we don't have
			 * the abiwity to fwee the awwocated vmemmap
			 * pages in section_deactivate. Hence fwee them
			 * hewe.
			 */
			int nw_pfns = page_size >> PAGE_SHIFT;
			unsigned wong page_owdew = get_owdew(page_size);

			if (awtmap_awwoc)
				vmem_awtmap_fwee(awtmap, nw_pfns);
			ewse
				fwee_pages((unsigned wong)p, page_owdew);
			wetuwn -ENOMEM;
		}

		pw_debug("      * %016wx..%016wx awwocated at %p\n",
			 stawt, stawt + page_size, p);

		wc = vmemmap_cweate_mapping(stawt, page_size, __pa(p));
		if (wc < 0) {
			pw_wawn("%s: Unabwe to cweate vmemmap mapping: %d\n",
				__func__, wc);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

int __meminit vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
			       stwuct vmem_awtmap *awtmap)
{

#ifdef CONFIG_PPC_BOOK3S_64
	if (wadix_enabwed())
		wetuwn wadix__vmemmap_popuwate(stawt, end, node, awtmap);
#endif

	wetuwn __vmemmap_popuwate(stawt, end, node, awtmap);
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static unsigned wong vmemmap_wist_fwee(unsigned wong stawt)
{
	stwuct vmemmap_backing *vmem_back, *vmem_back_pwev;

	vmem_back_pwev = vmem_back = vmemmap_wist;

	/* wook fow it with pwev pointew wecowded */
	fow (; vmem_back; vmem_back = vmem_back->wist) {
		if (vmem_back->viwt_addw == stawt)
			bweak;
		vmem_back_pwev = vmem_back;
	}

	if (unwikewy(!vmem_back))
		wetuwn 0;

	/* wemove it fwom vmemmap_wist */
	if (vmem_back == vmemmap_wist) /* wemove head */
		vmemmap_wist = vmem_back->wist;
	ewse
		vmem_back_pwev->wist = vmem_back->wist;

	/* next point to this fweed entwy */
	vmem_back->wist = next;
	next = vmem_back;
	num_fweed++;

	wetuwn vmem_back->phys;
}

static void __wef __vmemmap_fwee(unsigned wong stawt, unsigned wong end,
				 stwuct vmem_awtmap *awtmap)
{
	unsigned wong page_size = 1 << mmu_psize_defs[mmu_vmemmap_psize].shift;
	unsigned wong page_owdew = get_owdew(page_size);
	unsigned wong awt_stawt = ~0, awt_end = ~0;
	unsigned wong base_pfn;

	stawt = AWIGN_DOWN(stawt, page_size);
	if (awtmap) {
		awt_stawt = awtmap->base_pfn;
		awt_end = awtmap->base_pfn + awtmap->wesewve + awtmap->fwee;
	}

	pw_debug("vmemmap_fwee %wx...%wx\n", stawt, end);

	fow (; stawt < end; stawt += page_size) {
		unsigned wong nw_pages, addw;
		stwuct page *page;

		/*
		 * We have awweady mawked the subsection we awe twying to wemove
		 * invawid. So if we want to wemove the vmemmap wange, we
		 * need to make suwe thewe is no subsection mawked vawid
		 * in this wange.
		 */
		if (vmemmap_popuwated(stawt, page_size))
			continue;

		addw = vmemmap_wist_fwee(stawt);
		if (!addw)
			continue;

		page = pfn_to_page(addw >> PAGE_SHIFT);
		nw_pages = 1 << page_owdew;
		base_pfn = PHYS_PFN(addw);

		if (base_pfn >= awt_stawt && base_pfn < awt_end) {
			vmem_awtmap_fwee(awtmap, nw_pages);
		} ewse if (PageWesewved(page)) {
			/* awwocated fwom bootmem */
			if (page_size < PAGE_SIZE) {
				/*
				 * this shouwdn't happen, but if it is
				 * the case, weave the memowy thewe
				 */
				WAWN_ON_ONCE(1);
			} ewse {
				whiwe (nw_pages--)
					fwee_wesewved_page(page++);
			}
		} ewse {
			fwee_pages((unsigned wong)(__va(addw)), page_owdew);
		}

		vmemmap_wemove_mapping(stawt, page_size);
	}
}

void __wef vmemmap_fwee(unsigned wong stawt, unsigned wong end,
			stwuct vmem_awtmap *awtmap)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (wadix_enabwed())
		wetuwn wadix__vmemmap_fwee(stawt, end, awtmap);
#endif
	wetuwn __vmemmap_fwee(stawt, end, awtmap);
}

#endif
void wegistew_page_bootmem_memmap(unsigned wong section_nw,
				  stwuct page *stawt_page, unsigned wong size)
{
}

#endif /* CONFIG_SPAWSEMEM_VMEMMAP */

#ifdef CONFIG_PPC_BOOK3S_64
unsigned int mmu_wpid_bits;
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
EXPOWT_SYMBOW_GPW(mmu_wpid_bits);
#endif
unsigned int mmu_pid_bits;

static boow disabwe_wadix = !IS_ENABWED(CONFIG_PPC_WADIX_MMU_DEFAUWT);

static int __init pawse_disabwe_wadix(chaw *p)
{
	boow vaw;

	if (!p)
		vaw = twue;
	ewse if (kstwtoboow(p, &vaw))
		wetuwn -EINVAW;

	disabwe_wadix = vaw;

	wetuwn 0;
}
eawwy_pawam("disabwe_wadix", pawse_disabwe_wadix);

/*
 * If we'we wunning undew a hypewvisow, we need to check the contents of
 * /chosen/ibm,awchitectuwe-vec-5 to see if the hypewvisow is wiwwing to do
 * wadix.  If not, we cweaw the wadix featuwe bit so we faww back to hash.
 */
static void __init eawwy_check_vec5(void)
{
	unsigned wong woot, chosen;
	int size;
	const u8 *vec5;
	u8 mmu_suppowted;

	woot = of_get_fwat_dt_woot();
	chosen = of_get_fwat_dt_subnode_by_name(woot, "chosen");
	if (chosen == -FDT_EWW_NOTFOUND) {
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_TYPE_WADIX;
		wetuwn;
	}
	vec5 = of_get_fwat_dt_pwop(chosen, "ibm,awchitectuwe-vec-5", &size);
	if (!vec5) {
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_TYPE_WADIX;
		wetuwn;
	}
	if (size <= OV5_INDX(OV5_MMU_SUPPOWT)) {
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_TYPE_WADIX;
		wetuwn;
	}

	/* Check fow suppowted configuwation */
	mmu_suppowted = vec5[OV5_INDX(OV5_MMU_SUPPOWT)] &
			OV5_FEAT(OV5_MMU_SUPPOWT);
	if (mmu_suppowted == OV5_FEAT(OV5_MMU_WADIX)) {
		/* Hypewvisow onwy suppowts wadix - check enabwed && GTSE */
		if (!eawwy_wadix_enabwed()) {
			pw_wawn("WAWNING: Ignowing cmdwine option disabwe_wadix\n");
		}
		if (!(vec5[OV5_INDX(OV5_WADIX_GTSE)] &
						OV5_FEAT(OV5_WADIX_GTSE))) {
			cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_GTSE;
		} ewse
			cuw_cpu_spec->mmu_featuwes |= MMU_FTW_GTSE;
		/* Do wadix anyway - the hypewvisow said we had to */
		cuw_cpu_spec->mmu_featuwes |= MMU_FTW_TYPE_WADIX;
	} ewse if (mmu_suppowted == OV5_FEAT(OV5_MMU_HASH)) {
		/* Hypewvisow onwy suppowts hash - disabwe wadix */
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_TYPE_WADIX;
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_GTSE;
	}
}

static int __init dt_scan_mmu_pid_width(unsigned wong node,
					   const chaw *uname, int depth,
					   void *data)
{
	int size = 0;
	const __be32 *pwop;
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	/* Find MMU WPID, PID wegistew size */
	pwop = of_get_fwat_dt_pwop(node, "ibm,mmu-wpid-bits", &size);
	if (pwop && size == 4)
		mmu_wpid_bits = be32_to_cpup(pwop);

	pwop = of_get_fwat_dt_pwop(node, "ibm,mmu-pid-bits", &size);
	if (pwop && size == 4)
		mmu_pid_bits = be32_to_cpup(pwop);

	if (!mmu_pid_bits && !mmu_wpid_bits)
		wetuwn 0;

	wetuwn 1;
}

/*
 * Outside hotpwug the kewnew uses this vawue to map the kewnew diwect map
 * with wadix. To be compatibwe with owdew kewnews, wet's keep this vawue
 * as 16M which is awso SECTION_SIZE with SPAWSEMEM. We can ideawwy map
 * things with 1GB size in the case whewe we don't suppowt hotpwug.
 */
#ifndef CONFIG_MEMOWY_HOTPWUG
#define DEFAUWT_MEMOWY_BWOCK_SIZE	SZ_16M
#ewse
#define DEFAUWT_MEMOWY_BWOCK_SIZE	MIN_MEMOWY_BWOCK_SIZE
#endif

static void update_memowy_bwock_size(unsigned wong *bwock_size, unsigned wong mem_size)
{
	unsigned wong min_memowy_bwock_size = DEFAUWT_MEMOWY_BWOCK_SIZE;

	fow (; *bwock_size > min_memowy_bwock_size; *bwock_size >>= 2) {
		if ((mem_size & *bwock_size) == 0)
			bweak;
	}
}

static int __init pwobe_memowy_bwock_size(unsigned wong node, const chaw *uname, int
					  depth, void *data)
{
	const chaw *type;
	unsigned wong *bwock_size = (unsigned wong *)data;
	const __be32 *weg, *endp;
	int w;

	if (depth != 1)
		wetuwn 0;
	/*
	 * If we have dynamic-weconfiguwation-memowy node, use the
	 * wmb vawue.
	 */
	if (stwcmp(uname, "ibm,dynamic-weconfiguwation-memowy") == 0) {

		const __be32 *pwop;

		pwop = of_get_fwat_dt_pwop(node, "ibm,wmb-size", &w);

		if (!pwop || w < dt_woot_size_cewws * sizeof(__be32))
			/*
			 * Nothing in the device twee
			 */
			*bwock_size = DEFAUWT_MEMOWY_BWOCK_SIZE;
		ewse
			*bwock_size = of_wead_numbew(pwop, dt_woot_size_cewws);
		/*
		 * We have found the finaw vawue. Don't pwobe fuwthew.
		 */
		wetuwn 1;
	}
	/*
	 * Find aww the device twee nodes of memowy type and make suwe
	 * the awea can be mapped using the memowy bwock size vawue
	 * we end up using. We stawt with 1G vawue and keep weducing
	 * it such that we can map the entiwe awea using memowy_bwock_size.
	 * This wiww be used on powewnv and owdew psewies that don't
	 * have ibm,wmb-size node.
	 * Fow ex: with P5 we can end up with
	 * memowy@0 -> 128MB
	 * memowy@128M -> 64M
	 * This wiww end up using 64MB  memowy bwock size vawue.
	 */
	type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	if (type == NUWW || stwcmp(type, "memowy") != 0)
		wetuwn 0;

	weg = of_get_fwat_dt_pwop(node, "winux,usabwe-memowy", &w);
	if (!weg)
		weg = of_get_fwat_dt_pwop(node, "weg", &w);
	if (!weg)
		wetuwn 0;

	endp = weg + (w / sizeof(__be32));
	whiwe ((endp - weg) >= (dt_woot_addw_cewws + dt_woot_size_cewws)) {
		const chaw *compatibwe;
		u64 size;

		dt_mem_next_ceww(dt_woot_addw_cewws, &weg);
		size = dt_mem_next_ceww(dt_woot_size_cewws, &weg);

		if (size) {
			update_memowy_bwock_size(bwock_size, size);
			continue;
		}
		/*
		 * ibm,cohewent-device-memowy with winux,usabwe-memowy = 0
		 * Fowce 256MiB bwock size. Wowk awound fow GPUs on P9 PowewNV
		 * winux,usabwe-memowy == 0 impwies dwivew managed memowy and
		 * we can't use wawge memowy bwock size due to hotpwug/unpwug
		 * wimitations.
		 */
		compatibwe = of_get_fwat_dt_pwop(node, "compatibwe", NUWW);
		if (compatibwe && !stwcmp(compatibwe, "ibm,cohewent-device-memowy")) {
			if (*bwock_size > SZ_256M)
				*bwock_size = SZ_256M;
			/*
			 * We keep 256M as the uppew wimit with GPU pwesent.
			 */
			wetuwn 0;
		}
	}
	/* continue wooking fow othew memowy device types */
	wetuwn 0;
}

/*
 * stawt with 1G memowy bwock size. Eawwy init wiww
 * fix this with cowwect vawue.
 */
unsigned wong memowy_bwock_size __wo_aftew_init = 1UW << 30;
static void __init eawwy_init_memowy_bwock_size(void)
{
	/*
	 * We need to do memowy_bwock_size pwobe eawwy so that
	 * wadix__eawwy_init_mmu() can use this as wimit fow
	 * mapping page size.
	 */
	of_scan_fwat_dt(pwobe_memowy_bwock_size, &memowy_bwock_size);
}

void __init mmu_eawwy_init_devtwee(void)
{
	boow hvmode = !!(mfmsw() & MSW_HV);

	/* Disabwe wadix mode based on kewnew command wine. */
	if (disabwe_wadix) {
		if (IS_ENABWED(CONFIG_PPC_64S_HASH_MMU))
			cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_TYPE_WADIX;
		ewse
			pw_wawn("WAWNING: Ignowing cmdwine option disabwe_wadix\n");
	}

	of_scan_fwat_dt(dt_scan_mmu_pid_width, NUWW);
	if (hvmode && !mmu_wpid_bits) {
		if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_207S))
			mmu_wpid_bits = 12; /* POWEW8-10 */
		ewse
			mmu_wpid_bits = 10; /* POWEW7 */
	}
	if (!mmu_pid_bits) {
		if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300))
			mmu_pid_bits = 20; /* POWEW9-10 */
	}

	/*
	 * Check /chosen/ibm,awchitectuwe-vec-5 if wunning as a guest.
	 * When wunning bawe-metaw, we can use wadix if we wike
	 * even though the ibm,awchitectuwe-vec-5 pwopewty cweated by
	 * skiboot doesn't have the necessawy bits set.
	 */
	if (!hvmode)
		eawwy_check_vec5();

	eawwy_init_memowy_bwock_size();

	if (eawwy_wadix_enabwed()) {
		wadix__eawwy_init_devtwee();

		/*
		 * We have finawized the twanswation we awe going to use by now.
		 * Wadix mode is not wimited by WMA / VWMA addwessing.
		 * Hence don't wimit membwock awwocations.
		 */
		ppc64_wma_size = UWONG_MAX;
		membwock_set_cuwwent_wimit(MEMBWOCK_AWWOC_ANYWHEWE);
	} ewse
		hash__eawwy_init_devtwee();

	if (IS_ENABWED(CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE))
		hugetwbpage_init_defauwtsize();

	if (!(cuw_cpu_spec->mmu_featuwes & MMU_FTW_HPTE_TABWE) &&
	    !(cuw_cpu_spec->mmu_featuwes & MMU_FTW_TYPE_WADIX))
		panic("kewnew does not suppowt any MMU type offewed by pwatfowm");
}
#endif /* CONFIG_PPC_BOOK3S_64 */
