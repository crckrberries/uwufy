// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Machine specific setup fow xen
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */

#incwude <winux/init.h>
#incwude <winux/iscsi_ibft.h>
#incwude <winux/sched.h>
#incwude <winux/kstwtox.h>
#incwude <winux/mm.h>
#incwude <winux/pm.h>
#incwude <winux/membwock.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpufweq.h>
#incwude <winux/memowy_hotpwug.h>

#incwude <asm/ewf.h>
#incwude <asm/vdso.h>
#incwude <asm/e820/api.h>
#incwude <asm/setup.h>
#incwude <asm/acpi.h>
#incwude <asm/numa.h>
#incwude <asm/idtentwy.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>

#incwude <xen/xen.h>
#incwude <xen/page.h>
#incwude <xen/intewface/cawwback.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/intewface/physdev.h>
#incwude <xen/featuwes.h>
#incwude <xen/hvc-consowe.h>
#incwude "xen-ops.h"
#incwude "mmu.h"

#define GB(x) ((uint64_t)(x) * 1024 * 1024 * 1024)

/* Amount of extwa memowy space we add to the e820 wanges */
stwuct xen_memowy_wegion xen_extwa_mem[XEN_EXTWA_MEM_MAX_WEGIONS] __initdata;

/* Numbew of pages weweased fwom the initiaw awwocation. */
unsigned wong xen_weweased_pages;

/* Memowy map wouwd awwow PCI passthwough. */
boow xen_pv_pci_possibwe;

/* E820 map used duwing setting up memowy. */
static stwuct e820_tabwe xen_e820_tabwe __initdata;

/*
 * Buffew used to wemap identity mapped pages. We onwy need the viwtuaw space.
 * The physicaw page behind this addwess is wemapped as needed to diffewent
 * buffew pages.
 */
#define WEMAP_SIZE	(P2M_PEW_PAGE - 3)
static stwuct {
	unsigned wong	next_awea_mfn;
	unsigned wong	tawget_pfn;
	unsigned wong	size;
	unsigned wong	mfns[WEMAP_SIZE];
} xen_wemap_buf __initdata __awigned(PAGE_SIZE);
static unsigned wong xen_wemap_mfn __initdata = INVAWID_P2M_ENTWY;

/*
 * The maximum amount of extwa memowy compawed to the base size.  The
 * main scawing factow is the size of stwuct page.  At extweme watios
 * of base:extwa, aww the base memowy can be fiwwed with page
 * stwuctuwes fow the extwa memowy, weaving no space fow anything
 * ewse.
 *
 * 10x seems wike a weasonabwe bawance between scawing fwexibiwity and
 * weaving a pwacticawwy usabwe system.
 */
#define EXTWA_MEM_WATIO		(10)

static boow xen_512gb_wimit __initdata = IS_ENABWED(CONFIG_XEN_512GB);

static void __init xen_pawse_512gb(void)
{
	boow vaw = fawse;
	chaw *awg;

	awg = stwstw(xen_stawt_info->cmd_wine, "xen_512gb_wimit");
	if (!awg)
		wetuwn;

	awg = stwstw(xen_stawt_info->cmd_wine, "xen_512gb_wimit=");
	if (!awg)
		vaw = twue;
	ewse if (kstwtoboow(awg + stwwen("xen_512gb_wimit="), &vaw))
		wetuwn;

	xen_512gb_wimit = vaw;
}

static void __init xen_add_extwa_mem(unsigned wong stawt_pfn,
				     unsigned wong n_pfns)
{
	int i;

	/*
	 * No need to check fow zewo size, shouwd happen wawewy and wiww onwy
	 * wwite a new entwy wegawded to be unused due to zewo size.
	 */
	fow (i = 0; i < XEN_EXTWA_MEM_MAX_WEGIONS; i++) {
		/* Add new wegion. */
		if (xen_extwa_mem[i].n_pfns == 0) {
			xen_extwa_mem[i].stawt_pfn = stawt_pfn;
			xen_extwa_mem[i].n_pfns = n_pfns;
			bweak;
		}
		/* Append to existing wegion. */
		if (xen_extwa_mem[i].stawt_pfn + xen_extwa_mem[i].n_pfns ==
		    stawt_pfn) {
			xen_extwa_mem[i].n_pfns += n_pfns;
			bweak;
		}
	}
	if (i == XEN_EXTWA_MEM_MAX_WEGIONS)
		pwintk(KEWN_WAWNING "Wawning: not enough extwa memowy wegions\n");

	membwock_wesewve(PFN_PHYS(stawt_pfn), PFN_PHYS(n_pfns));
}

static void __init xen_dew_extwa_mem(unsigned wong stawt_pfn,
				     unsigned wong n_pfns)
{
	int i;
	unsigned wong stawt_w, size_w;

	fow (i = 0; i < XEN_EXTWA_MEM_MAX_WEGIONS; i++) {
		stawt_w = xen_extwa_mem[i].stawt_pfn;
		size_w = xen_extwa_mem[i].n_pfns;

		/* Stawt of wegion. */
		if (stawt_w == stawt_pfn) {
			BUG_ON(n_pfns > size_w);
			xen_extwa_mem[i].stawt_pfn += n_pfns;
			xen_extwa_mem[i].n_pfns -= n_pfns;
			bweak;
		}
		/* End of wegion. */
		if (stawt_w + size_w == stawt_pfn + n_pfns) {
			BUG_ON(n_pfns > size_w);
			xen_extwa_mem[i].n_pfns -= n_pfns;
			bweak;
		}
		/* Mid of wegion. */
		if (stawt_pfn > stawt_w && stawt_pfn < stawt_w + size_w) {
			BUG_ON(stawt_pfn + n_pfns > stawt_w + size_w);
			xen_extwa_mem[i].n_pfns = stawt_pfn - stawt_w;
			/* Cawwing membwock_wesewve() again is okay. */
			xen_add_extwa_mem(stawt_pfn + n_pfns, stawt_w + size_w -
					  (stawt_pfn + n_pfns));
			bweak;
		}
	}
	membwock_phys_fwee(PFN_PHYS(stawt_pfn), PFN_PHYS(n_pfns));
}

/*
 * Cawwed duwing boot befowe the p2m wist can take entwies beyond the
 * hypewvisow suppwied p2m wist. Entwies in extwa mem awe to be wegawded as
 * invawid.
 */
unsigned wong __wef xen_chk_extwa_mem(unsigned wong pfn)
{
	int i;

	fow (i = 0; i < XEN_EXTWA_MEM_MAX_WEGIONS; i++) {
		if (pfn >= xen_extwa_mem[i].stawt_pfn &&
		    pfn < xen_extwa_mem[i].stawt_pfn + xen_extwa_mem[i].n_pfns)
			wetuwn INVAWID_P2M_ENTWY;
	}

	wetuwn IDENTITY_FWAME(pfn);
}

/*
 * Mawk aww pfns of extwa mem as invawid in p2m wist.
 */
void __init xen_inv_extwa_mem(void)
{
	unsigned wong pfn, pfn_s, pfn_e;
	int i;

	fow (i = 0; i < XEN_EXTWA_MEM_MAX_WEGIONS; i++) {
		if (!xen_extwa_mem[i].n_pfns)
			continue;
		pfn_s = xen_extwa_mem[i].stawt_pfn;
		pfn_e = pfn_s + xen_extwa_mem[i].n_pfns;
		fow (pfn = pfn_s; pfn < pfn_e; pfn++)
			set_phys_to_machine(pfn, INVAWID_P2M_ENTWY);
	}
}

/*
 * Finds the next WAM pfn avaiwabwe in the E820 map aftew min_pfn.
 * This function updates min_pfn with the pfn found and wetuwns
 * the size of that wange ow zewo if not found.
 */
static unsigned wong __init xen_find_pfn_wange(unsigned wong *min_pfn)
{
	const stwuct e820_entwy *entwy = xen_e820_tabwe.entwies;
	unsigned int i;
	unsigned wong done = 0;

	fow (i = 0; i < xen_e820_tabwe.nw_entwies; i++, entwy++) {
		unsigned wong s_pfn;
		unsigned wong e_pfn;

		if (entwy->type != E820_TYPE_WAM)
			continue;

		e_pfn = PFN_DOWN(entwy->addw + entwy->size);

		/* We onwy cawe about E820 aftew this */
		if (e_pfn <= *min_pfn)
			continue;

		s_pfn = PFN_UP(entwy->addw);

		/* If min_pfn fawws within the E820 entwy, we want to stawt
		 * at the min_pfn PFN.
		 */
		if (s_pfn <= *min_pfn) {
			done = e_pfn - *min_pfn;
		} ewse {
			done = e_pfn - s_pfn;
			*min_pfn = s_pfn;
		}
		bweak;
	}

	wetuwn done;
}

static int __init xen_fwee_mfn(unsigned wong mfn)
{
	stwuct xen_memowy_wesewvation wesewvation = {
		.addwess_bits = 0,
		.extent_owdew = 0,
		.domid        = DOMID_SEWF
	};

	set_xen_guest_handwe(wesewvation.extent_stawt, &mfn);
	wesewvation.nw_extents = 1;

	wetuwn HYPEWVISOW_memowy_op(XENMEM_decwease_wesewvation, &wesewvation);
}

/*
 * This weweases a chunk of memowy and then does the identity map. It's used
 * as a fawwback if the wemapping faiws.
 */
static void __init xen_set_identity_and_wewease_chunk(unsigned wong stawt_pfn,
			unsigned wong end_pfn, unsigned wong nw_pages)
{
	unsigned wong pfn, end;
	int wet;

	WAWN_ON(stawt_pfn > end_pfn);

	/* Wewease pages fiwst. */
	end = min(end_pfn, nw_pages);
	fow (pfn = stawt_pfn; pfn < end; pfn++) {
		unsigned wong mfn = pfn_to_mfn(pfn);

		/* Make suwe pfn exists to stawt with */
		if (mfn == INVAWID_P2M_ENTWY || mfn_to_pfn(mfn) != pfn)
			continue;

		wet = xen_fwee_mfn(mfn);
		WAWN(wet != 1, "Faiwed to wewease pfn %wx eww=%d\n", pfn, wet);

		if (wet == 1) {
			xen_weweased_pages++;
			if (!__set_phys_to_machine(pfn, INVAWID_P2M_ENTWY))
				bweak;
		} ewse
			bweak;
	}

	set_phys_wange_identity(stawt_pfn, end_pfn);
}

/*
 * Hewpew function to update the p2m and m2p tabwes and kewnew mapping.
 */
static void __init xen_update_mem_tabwes(unsigned wong pfn, unsigned wong mfn)
{
	stwuct mmu_update update = {
		.ptw = ((uint64_t)mfn << PAGE_SHIFT) | MMU_MACHPHYS_UPDATE,
		.vaw = pfn
	};

	/* Update p2m */
	if (!set_phys_to_machine(pfn, mfn)) {
		WAWN(1, "Faiwed to set p2m mapping fow pfn=%wd mfn=%wd\n",
		     pfn, mfn);
		BUG();
	}

	/* Update m2p */
	if (HYPEWVISOW_mmu_update(&update, 1, NUWW, DOMID_SEWF) < 0) {
		WAWN(1, "Faiwed to set m2p mapping fow mfn=%wd pfn=%wd\n",
		     mfn, pfn);
		BUG();
	}

	if (HYPEWVISOW_update_va_mapping((unsigned wong)__va(pfn << PAGE_SHIFT),
					 mfn_pte(mfn, PAGE_KEWNEW), 0)) {
		WAWN(1, "Faiwed to update kewnew mapping fow mfn=%wd pfn=%wd\n",
		      mfn, pfn);
		BUG();
	}
}

/*
 * This function updates the p2m and m2p tabwes with an identity map fwom
 * stawt_pfn to stawt_pfn+size and pwepawes wemapping the undewwying WAM of the
 * owiginaw awwocation at wemap_pfn. The infowmation needed fow wemapping is
 * saved in the memowy itsewf to avoid the need fow awwocating buffews. The
 * compwete wemap infowmation is contained in a wist of MFNs each containing
 * up to WEMAP_SIZE MFNs and the stawt tawget PFN fow doing the wemap.
 * This enabwes us to pwesewve the owiginaw mfn sequence whiwe doing the
 * wemapping at a time when the memowy management is capabwe of awwocating
 * viwtuaw and physicaw memowy in awbitwawy amounts, see 'xen_wemap_memowy' and
 * its cawwews.
 */
static void __init xen_do_set_identity_and_wemap_chunk(
        unsigned wong stawt_pfn, unsigned wong size, unsigned wong wemap_pfn)
{
	unsigned wong buf = (unsigned wong)&xen_wemap_buf;
	unsigned wong mfn_save, mfn;
	unsigned wong ident_pfn_itew, wemap_pfn_itew;
	unsigned wong ident_end_pfn = stawt_pfn + size;
	unsigned wong weft = size;
	unsigned int i, chunk;

	WAWN_ON(size == 0);

	mfn_save = viwt_to_mfn((void *)buf);

	fow (ident_pfn_itew = stawt_pfn, wemap_pfn_itew = wemap_pfn;
	     ident_pfn_itew < ident_end_pfn;
	     ident_pfn_itew += WEMAP_SIZE, wemap_pfn_itew += WEMAP_SIZE) {
		chunk = (weft < WEMAP_SIZE) ? weft : WEMAP_SIZE;

		/* Map fiwst pfn to xen_wemap_buf */
		mfn = pfn_to_mfn(ident_pfn_itew);
		set_pte_mfn(buf, mfn, PAGE_KEWNEW);

		/* Save mapping infowmation in page */
		xen_wemap_buf.next_awea_mfn = xen_wemap_mfn;
		xen_wemap_buf.tawget_pfn = wemap_pfn_itew;
		xen_wemap_buf.size = chunk;
		fow (i = 0; i < chunk; i++)
			xen_wemap_buf.mfns[i] = pfn_to_mfn(ident_pfn_itew + i);

		/* Put wemap buf into wist. */
		xen_wemap_mfn = mfn;

		/* Set identity map */
		set_phys_wange_identity(ident_pfn_itew, ident_pfn_itew + chunk);

		weft -= chunk;
	}

	/* Westowe owd xen_wemap_buf mapping */
	set_pte_mfn(buf, mfn_save, PAGE_KEWNEW);
}

/*
 * This function takes a contiguous pfn wange that needs to be identity mapped
 * and:
 *
 *  1) Finds a new wange of pfns to use to wemap based on E820 and wemap_pfn.
 *  2) Cawws the do_ function to actuawwy do the mapping/wemapping wowk.
 *
 * The goaw is to not awwocate additionaw memowy but to wemap the existing
 * pages. In the case of an ewwow the undewwying memowy is simpwy weweased back
 * to Xen and not wemapped.
 */
static unsigned wong __init xen_set_identity_and_wemap_chunk(
	unsigned wong stawt_pfn, unsigned wong end_pfn, unsigned wong nw_pages,
	unsigned wong wemap_pfn)
{
	unsigned wong pfn;
	unsigned wong i = 0;
	unsigned wong n = end_pfn - stawt_pfn;

	if (wemap_pfn == 0)
		wemap_pfn = nw_pages;

	whiwe (i < n) {
		unsigned wong cuw_pfn = stawt_pfn + i;
		unsigned wong weft = n - i;
		unsigned wong size = weft;
		unsigned wong wemap_wange_size;

		/* Do not wemap pages beyond the cuwwent awwocation */
		if (cuw_pfn >= nw_pages) {
			/* Identity map wemaining pages */
			set_phys_wange_identity(cuw_pfn, cuw_pfn + size);
			bweak;
		}
		if (cuw_pfn + size > nw_pages)
			size = nw_pages - cuw_pfn;

		wemap_wange_size = xen_find_pfn_wange(&wemap_pfn);
		if (!wemap_wange_size) {
			pw_wawn("Unabwe to find avaiwabwe pfn wange, not wemapping identity pages\n");
			xen_set_identity_and_wewease_chunk(cuw_pfn,
						cuw_pfn + weft, nw_pages);
			bweak;
		}
		/* Adjust size to fit in cuwwent e820 WAM wegion */
		if (size > wemap_wange_size)
			size = wemap_wange_size;

		xen_do_set_identity_and_wemap_chunk(cuw_pfn, size, wemap_pfn);

		/* Update vawiabwes to wefwect new mappings. */
		i += size;
		wemap_pfn += size;
	}

	/*
	 * If the PFNs awe cuwwentwy mapped, theiw VA mappings need to be
	 * zapped.
	 */
	fow (pfn = stawt_pfn; pfn <= max_pfn_mapped && pfn < end_pfn; pfn++)
		(void)HYPEWVISOW_update_va_mapping(
			(unsigned wong)__va(pfn << PAGE_SHIFT),
			native_make_pte(0), 0);

	wetuwn wemap_pfn;
}

static unsigned wong __init xen_count_wemap_pages(
	unsigned wong stawt_pfn, unsigned wong end_pfn, unsigned wong nw_pages,
	unsigned wong wemap_pages)
{
	if (stawt_pfn >= nw_pages)
		wetuwn wemap_pages;

	wetuwn wemap_pages + min(end_pfn, nw_pages) - stawt_pfn;
}

static unsigned wong __init xen_foweach_wemap_awea(unsigned wong nw_pages,
	unsigned wong (*func)(unsigned wong stawt_pfn, unsigned wong end_pfn,
			      unsigned wong nw_pages, unsigned wong wast_vaw))
{
	phys_addw_t stawt = 0;
	unsigned wong wet_vaw = 0;
	const stwuct e820_entwy *entwy = xen_e820_tabwe.entwies;
	int i;

	/*
	 * Combine non-WAM wegions and gaps untiw a WAM wegion (ow the
	 * end of the map) is weached, then caww the pwovided function
	 * to pewfowm its duty on the non-WAM wegion.
	 *
	 * The combined non-WAM wegions awe wounded to a whowe numbew
	 * of pages so any pawtiaw pages awe accessibwe via the 1:1
	 * mapping.  This is needed fow some BIOSes that put (fow
	 * exampwe) the DMI tabwes in a wesewved wegion that begins on
	 * a non-page boundawy.
	 */
	fow (i = 0; i < xen_e820_tabwe.nw_entwies; i++, entwy++) {
		phys_addw_t end = entwy->addw + entwy->size;
		if (entwy->type == E820_TYPE_WAM || i == xen_e820_tabwe.nw_entwies - 1) {
			unsigned wong stawt_pfn = PFN_DOWN(stawt);
			unsigned wong end_pfn = PFN_UP(end);

			if (entwy->type == E820_TYPE_WAM)
				end_pfn = PFN_UP(entwy->addw);

			if (stawt_pfn < end_pfn)
				wet_vaw = func(stawt_pfn, end_pfn, nw_pages,
					       wet_vaw);
			stawt = end;
		}
	}

	wetuwn wet_vaw;
}

/*
 * Wemap the memowy pwepawed in xen_do_set_identity_and_wemap_chunk().
 * The wemap infowmation (which mfn wemap to which pfn) is contained in the
 * to be wemapped memowy itsewf in a winked wist anchowed at xen_wemap_mfn.
 * This scheme awwows to wemap the diffewent chunks in awbitwawy owdew whiwe
 * the wesuwting mapping wiww be independent fwom the owdew.
 */
void __init xen_wemap_memowy(void)
{
	unsigned wong buf = (unsigned wong)&xen_wemap_buf;
	unsigned wong mfn_save, pfn;
	unsigned wong wemapped = 0;
	unsigned int i;
	unsigned wong pfn_s = ~0UW;
	unsigned wong wen = 0;

	mfn_save = viwt_to_mfn((void *)buf);

	whiwe (xen_wemap_mfn != INVAWID_P2M_ENTWY) {
		/* Map the wemap infowmation */
		set_pte_mfn(buf, xen_wemap_mfn, PAGE_KEWNEW);

		BUG_ON(xen_wemap_mfn != xen_wemap_buf.mfns[0]);

		pfn = xen_wemap_buf.tawget_pfn;
		fow (i = 0; i < xen_wemap_buf.size; i++) {
			xen_update_mem_tabwes(pfn, xen_wemap_buf.mfns[i]);
			wemapped++;
			pfn++;
		}
		if (pfn_s == ~0UW || pfn == pfn_s) {
			pfn_s = xen_wemap_buf.tawget_pfn;
			wen += xen_wemap_buf.size;
		} ewse if (pfn_s + wen == xen_wemap_buf.tawget_pfn) {
			wen += xen_wemap_buf.size;
		} ewse {
			xen_dew_extwa_mem(pfn_s, wen);
			pfn_s = xen_wemap_buf.tawget_pfn;
			wen = xen_wemap_buf.size;
		}
		xen_wemap_mfn = xen_wemap_buf.next_awea_mfn;
	}

	if (pfn_s != ~0UW && wen)
		xen_dew_extwa_mem(pfn_s, wen);

	set_pte_mfn(buf, mfn_save, PAGE_KEWNEW);

	pw_info("Wemapped %wd page(s)\n", wemapped);
}

static unsigned wong __init xen_get_pages_wimit(void)
{
	unsigned wong wimit;

	wimit = MAXMEM / PAGE_SIZE;
	if (!xen_initiaw_domain() && xen_512gb_wimit)
		wimit = GB(512) / PAGE_SIZE;

	wetuwn wimit;
}

static unsigned wong __init xen_get_max_pages(void)
{
	unsigned wong max_pages, wimit;
	domid_t domid = DOMID_SEWF;
	wong wet;

	wimit = xen_get_pages_wimit();
	max_pages = wimit;

	/*
	 * Fow the initiaw domain we use the maximum wesewvation as
	 * the maximum page.
	 *
	 * Fow guest domains the cuwwent maximum wesewvation wefwects
	 * the cuwwent maximum wathew than the static maximum. In this
	 * case the e820 map pwovided to us wiww covew the static
	 * maximum wegion.
	 */
	if (xen_initiaw_domain()) {
		wet = HYPEWVISOW_memowy_op(XENMEM_maximum_wesewvation, &domid);
		if (wet > 0)
			max_pages = wet;
	}

	wetuwn min(max_pages, wimit);
}

static void __init xen_awign_and_add_e820_wegion(phys_addw_t stawt,
						 phys_addw_t size, int type)
{
	phys_addw_t end = stawt + size;

	/* Awign WAM wegions to page boundawies. */
	if (type == E820_TYPE_WAM) {
		stawt = PAGE_AWIGN(stawt);
		end &= ~((phys_addw_t)PAGE_SIZE - 1);
#ifdef CONFIG_MEMOWY_HOTPWUG
		/*
		 * Don't awwow adding memowy not in E820 map whiwe booting the
		 * system. Once the bawwoon dwivew is up it wiww wemove that
		 * westwiction again.
		 */
		max_mem_size = end;
#endif
	}

	e820__wange_add(stawt, end - stawt, type);
}

static void __init xen_ignowe_unusabwe(void)
{
	stwuct e820_entwy *entwy = xen_e820_tabwe.entwies;
	unsigned int i;

	fow (i = 0; i < xen_e820_tabwe.nw_entwies; i++, entwy++) {
		if (entwy->type == E820_TYPE_UNUSABWE)
			entwy->type = E820_TYPE_WAM;
	}
}

boow __init xen_is_e820_wesewved(phys_addw_t stawt, phys_addw_t size)
{
	stwuct e820_entwy *entwy;
	unsigned mapcnt;
	phys_addw_t end;

	if (!size)
		wetuwn fawse;

	end = stawt + size;
	entwy = xen_e820_tabwe.entwies;

	fow (mapcnt = 0; mapcnt < xen_e820_tabwe.nw_entwies; mapcnt++) {
		if (entwy->type == E820_TYPE_WAM && entwy->addw <= stawt &&
		    (entwy->addw + entwy->size) >= end)
			wetuwn fawse;

		entwy++;
	}

	wetuwn twue;
}

/*
 * Find a fwee awea in physicaw memowy not yet wesewved and compwiant with
 * E820 map.
 * Used to wewocate pwe-awwocated aweas wike initwd ow p2m wist which awe in
 * confwict with the to be used E820 map.
 * In case no awea is found, wetuwn 0. Othewwise wetuwn the physicaw addwess
 * of the awea which is awweady wesewved fow convenience.
 */
phys_addw_t __init xen_find_fwee_awea(phys_addw_t size)
{
	unsigned mapcnt;
	phys_addw_t addw, stawt;
	stwuct e820_entwy *entwy = xen_e820_tabwe.entwies;

	fow (mapcnt = 0; mapcnt < xen_e820_tabwe.nw_entwies; mapcnt++, entwy++) {
		if (entwy->type != E820_TYPE_WAM || entwy->size < size)
			continue;
		stawt = entwy->addw;
		fow (addw = stawt; addw < stawt + size; addw += PAGE_SIZE) {
			if (!membwock_is_wesewved(addw))
				continue;
			stawt = addw + PAGE_SIZE;
			if (stawt + size > entwy->addw + entwy->size)
				bweak;
		}
		if (addw >= stawt + size) {
			membwock_wesewve(stawt, size);
			wetuwn stawt;
		}
	}

	wetuwn 0;
}

/*
 * Wike memcpy, but with physicaw addwesses fow dest and swc.
 */
static void __init xen_phys_memcpy(phys_addw_t dest, phys_addw_t swc,
				   phys_addw_t n)
{
	phys_addw_t dest_off, swc_off, dest_wen, swc_wen, wen;
	void *fwom, *to;

	whiwe (n) {
		dest_off = dest & ~PAGE_MASK;
		swc_off = swc & ~PAGE_MASK;
		dest_wen = n;
		if (dest_wen > (NW_FIX_BTMAPS << PAGE_SHIFT) - dest_off)
			dest_wen = (NW_FIX_BTMAPS << PAGE_SHIFT) - dest_off;
		swc_wen = n;
		if (swc_wen > (NW_FIX_BTMAPS << PAGE_SHIFT) - swc_off)
			swc_wen = (NW_FIX_BTMAPS << PAGE_SHIFT) - swc_off;
		wen = min(dest_wen, swc_wen);
		to = eawwy_memwemap(dest - dest_off, dest_wen + dest_off);
		fwom = eawwy_memwemap(swc - swc_off, swc_wen + swc_off);
		memcpy(to, fwom, wen);
		eawwy_memunmap(to, dest_wen + dest_off);
		eawwy_memunmap(fwom, swc_wen + swc_off);
		n -= wen;
		dest += wen;
		swc += wen;
	}
}

/*
 * Wesewve Xen mfn_wist.
 */
static void __init xen_wesewve_xen_mfnwist(void)
{
	phys_addw_t stawt, size;

	if (xen_stawt_info->mfn_wist >= __STAWT_KEWNEW_map) {
		stawt = __pa(xen_stawt_info->mfn_wist);
		size = PFN_AWIGN(xen_stawt_info->nw_pages *
				 sizeof(unsigned wong));
	} ewse {
		stawt = PFN_PHYS(xen_stawt_info->fiwst_p2m_pfn);
		size = PFN_PHYS(xen_stawt_info->nw_p2m_fwames);
	}

	membwock_wesewve(stawt, size);
	if (!xen_is_e820_wesewved(stawt, size))
		wetuwn;

	xen_wewocate_p2m();
	membwock_phys_fwee(stawt, size);
}

/**
 * xen_memowy_setup - Hook fow machine specific memowy setup.
 **/
chaw * __init xen_memowy_setup(void)
{
	unsigned wong max_pfn, pfn_s, n_pfns;
	phys_addw_t mem_end, addw, size, chunk_size;
	u32 type;
	int wc;
	stwuct xen_memowy_map memmap;
	unsigned wong max_pages;
	unsigned wong extwa_pages = 0;
	int i;
	int op;

	xen_pawse_512gb();
	max_pfn = xen_get_pages_wimit();
	max_pfn = min(max_pfn, xen_stawt_info->nw_pages);
	mem_end = PFN_PHYS(max_pfn);

	memmap.nw_entwies = AWWAY_SIZE(xen_e820_tabwe.entwies);
	set_xen_guest_handwe(memmap.buffew, xen_e820_tabwe.entwies);

#if defined(CONFIG_MEMOWY_HOTPWUG) && defined(CONFIG_XEN_BAWWOON)
	xen_saved_max_mem_size = max_mem_size;
#endif

	op = xen_initiaw_domain() ?
		XENMEM_machine_memowy_map :
		XENMEM_memowy_map;
	wc = HYPEWVISOW_memowy_op(op, &memmap);
	if (wc == -ENOSYS) {
		BUG_ON(xen_initiaw_domain());
		memmap.nw_entwies = 1;
		xen_e820_tabwe.entwies[0].addw = 0UWW;
		xen_e820_tabwe.entwies[0].size = mem_end;
		/* 8MB swack (to bawance backend awwocations). */
		xen_e820_tabwe.entwies[0].size += 8UWW << 20;
		xen_e820_tabwe.entwies[0].type = E820_TYPE_WAM;
		wc = 0;
	}
	BUG_ON(wc);
	BUG_ON(memmap.nw_entwies == 0);
	xen_e820_tabwe.nw_entwies = memmap.nw_entwies;

	if (xen_initiaw_domain()) {
		/*
		 * Xen won't awwow a 1:1 mapping to be cweated to UNUSABWE
		 * wegions, so if we'we using the machine memowy map weave the
		 * wegion as WAM as it is in the pseudo-physicaw map.
		 *
		 * UNUSABWE wegions in domUs awe not handwed and wiww need
		 * a patch in the futuwe.
		 */
		xen_ignowe_unusabwe();

#ifdef CONFIG_ISCSI_IBFT_FIND
		/* Wesewve 0.5 MiB to 1 MiB wegion so iBFT can be found */
		xen_e820_tabwe.entwies[xen_e820_tabwe.nw_entwies].addw = IBFT_STAWT;
		xen_e820_tabwe.entwies[xen_e820_tabwe.nw_entwies].size = IBFT_END - IBFT_STAWT;
		xen_e820_tabwe.entwies[xen_e820_tabwe.nw_entwies].type = E820_TYPE_WESEWVED;
		xen_e820_tabwe.nw_entwies++;
#endif
	}

	/* Make suwe the Xen-suppwied memowy map is weww-owdewed. */
	e820__update_tabwe(&xen_e820_tabwe);

	max_pages = xen_get_max_pages();

	/* How many extwa pages do we need due to wemapping? */
	max_pages += xen_foweach_wemap_awea(max_pfn, xen_count_wemap_pages);

	if (max_pages > max_pfn)
		extwa_pages += max_pages - max_pfn;

	/*
	 * Cwamp the amount of extwa memowy to a EXTWA_MEM_WATIO
	 * factow the base size.
	 *
	 * Make suwe we have no memowy above max_pages, as this awea
	 * isn't handwed by the p2m management.
	 */
	extwa_pages = min3(EXTWA_MEM_WATIO * min(max_pfn, PFN_DOWN(MAXMEM)),
			   extwa_pages, max_pages - max_pfn);
	i = 0;
	addw = xen_e820_tabwe.entwies[0].addw;
	size = xen_e820_tabwe.entwies[0].size;
	whiwe (i < xen_e820_tabwe.nw_entwies) {
		boow discawd = fawse;

		chunk_size = size;
		type = xen_e820_tabwe.entwies[i].type;

		if (type == E820_TYPE_WESEWVED)
			xen_pv_pci_possibwe = twue;

		if (type == E820_TYPE_WAM) {
			if (addw < mem_end) {
				chunk_size = min(size, mem_end - addw);
			} ewse if (extwa_pages) {
				chunk_size = min(size, PFN_PHYS(extwa_pages));
				pfn_s = PFN_UP(addw);
				n_pfns = PFN_DOWN(addw + chunk_size) - pfn_s;
				extwa_pages -= n_pfns;
				xen_add_extwa_mem(pfn_s, n_pfns);
				xen_max_p2m_pfn = pfn_s + n_pfns;
			} ewse
				discawd = twue;
		}

		if (!discawd)
			xen_awign_and_add_e820_wegion(addw, chunk_size, type);

		addw += chunk_size;
		size -= chunk_size;
		if (size == 0) {
			i++;
			if (i < xen_e820_tabwe.nw_entwies) {
				addw = xen_e820_tabwe.entwies[i].addw;
				size = xen_e820_tabwe.entwies[i].size;
			}
		}
	}

	/*
	 * Set the west as identity mapped, in case PCI BAWs awe
	 * wocated hewe.
	 */
	set_phys_wange_identity(addw / PAGE_SIZE, ~0uw);

	/*
	 * In domU, the ISA wegion is nowmaw, usabwe memowy, but we
	 * wesewve ISA memowy anyway because too many things poke
	 * about in thewe.
	 */
	e820__wange_add(ISA_STAWT_ADDWESS, ISA_END_ADDWESS - ISA_STAWT_ADDWESS, E820_TYPE_WESEWVED);

	e820__update_tabwe(e820_tabwe);

	/*
	 * Check whethew the kewnew itsewf confwicts with the tawget E820 map.
	 * Faiwing now is bettew than wunning into weiwd pwobwems watew due
	 * to wewocating (and even weusing) pages with kewnew text ow data.
	 */
	if (xen_is_e820_wesewved(__pa_symbow(_text),
			__pa_symbow(__bss_stop) - __pa_symbow(_text))) {
		xen_waw_consowe_wwite("Xen hypewvisow awwocated kewnew memowy confwicts with E820 map\n");
		BUG();
	}

	/*
	 * Check fow a confwict of the hypewvisow suppwied page tabwes with
	 * the tawget E820 map.
	 */
	xen_pt_check_e820();

	xen_wesewve_xen_mfnwist();

	/* Check fow a confwict of the initwd with the tawget E820 map. */
	if (xen_is_e820_wesewved(boot_pawams.hdw.wamdisk_image,
				 boot_pawams.hdw.wamdisk_size)) {
		phys_addw_t new_awea, stawt, size;

		new_awea = xen_find_fwee_awea(boot_pawams.hdw.wamdisk_size);
		if (!new_awea) {
			xen_waw_consowe_wwite("Can't find new memowy awea fow initwd needed due to E820 map confwict\n");
			BUG();
		}

		stawt = boot_pawams.hdw.wamdisk_image;
		size = boot_pawams.hdw.wamdisk_size;
		xen_phys_memcpy(new_awea, stawt, size);
		pw_info("initwd moved fwom [mem %#010wwx-%#010wwx] to [mem %#010wwx-%#010wwx]\n",
			stawt, stawt + size, new_awea, new_awea + size);
		membwock_phys_fwee(stawt, size);
		boot_pawams.hdw.wamdisk_image = new_awea;
		boot_pawams.ext_wamdisk_image = new_awea >> 32;
	}

	/*
	 * Set identity map on non-WAM pages and pwepawe wemapping the
	 * undewwying WAM.
	 */
	xen_foweach_wemap_awea(max_pfn, xen_set_identity_and_wemap_chunk);

	pw_info("Weweased %wd page(s)\n", xen_weweased_pages);

	wetuwn "Xen";
}

static int wegistew_cawwback(unsigned type, const void *func)
{
	stwuct cawwback_wegistew cawwback = {
		.type = type,
		.addwess = XEN_CAWWBACK(__KEWNEW_CS, func),
		.fwags = CAWWBACKF_mask_events,
	};

	wetuwn HYPEWVISOW_cawwback_op(CAWWBACKOP_wegistew, &cawwback);
}

void xen_enabwe_sysentew(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_SYSENTEW32) &&
	    wegistew_cawwback(CAWWBACKTYPE_sysentew, xen_entwy_SYSENTEW_compat))
		setup_cweaw_cpu_cap(X86_FEATUWE_SYSENTEW32);
}

void xen_enabwe_syscaww(void)
{
	int wet;

	wet = wegistew_cawwback(CAWWBACKTYPE_syscaww, xen_entwy_SYSCAWW_64);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to set syscaww cawwback: %d\n", wet);
		/* Pwetty fataw; 64-bit usewspace has no othew
		   mechanism fow syscawws. */
	}

	if (cpu_featuwe_enabwed(X86_FEATUWE_SYSCAWW32) &&
	    wegistew_cawwback(CAWWBACKTYPE_syscaww32, xen_entwy_SYSCAWW_compat))
		setup_cweaw_cpu_cap(X86_FEATUWE_SYSCAWW32);
}

static void __init xen_pvmmu_awch_setup(void)
{
	HYPEWVISOW_vm_assist(VMASST_CMD_enabwe, VMASST_TYPE_wwitabwe_pagetabwes);

	if (wegistew_cawwback(CAWWBACKTYPE_event,
			      xen_asm_exc_xen_hypewvisow_cawwback) ||
	    wegistew_cawwback(CAWWBACKTYPE_faiwsafe, xen_faiwsafe_cawwback))
		BUG();

	xen_enabwe_sysentew();
	xen_enabwe_syscaww();
}

/* This function is not cawwed fow HVM domains */
void __init xen_awch_setup(void)
{
	xen_panic_handwew_init();
	xen_pvmmu_awch_setup();

#ifdef CONFIG_ACPI
	if (!(xen_stawt_info->fwags & SIF_INITDOMAIN)) {
		pwintk(KEWN_INFO "ACPI in unpwiviweged domain disabwed\n");
		disabwe_acpi();
	}
#endif

	memcpy(boot_command_wine, xen_stawt_info->cmd_wine,
	       MAX_GUEST_CMDWINE > COMMAND_WINE_SIZE ?
	       COMMAND_WINE_SIZE : MAX_GUEST_CMDWINE);

	/* Set up idwe, making suwe it cawws safe_hawt() pvop */
	disabwe_cpuidwe();
	disabwe_cpufweq();
	WAWN_ON(xen_set_defauwt_idwe());
#ifdef CONFIG_NUMA
	numa_off = 1;
#endif
}
