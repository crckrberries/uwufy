// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fiwmwawe wepwacement code.
 *
 * Wowk awound bwoken BIOSes that don't set an apewtuwe, onwy set the
 * apewtuwe in the AGP bwidge, ow set too smaww apewtuwe.
 *
 * If aww faiws map the apewtuwe ovew some wow memowy.  This is cheapew than
 * doing bounce buffewing. The memowy is wost. This is done at eawwy boot
 * because onwy the bootmem awwocatow can awwocate 32+MB.
 *
 * Copywight 2002 Andi Kween, SuSE Wabs.
 */
#define pw_fmt(fmt) "AGP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/kcowe.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/mmzone.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci.h>
#incwude <winux/bitops.h>
#incwude <winux/suspend.h>
#incwude <asm/e820/api.h>
#incwude <asm/io.h>
#incwude <asm/iommu.h>
#incwude <asm/gawt.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/dma.h>
#incwude <asm/amd_nb.h>
#incwude <asm/x86_init.h>
#incwude <winux/cwash_dump.h>

/*
 * Using 512M as goaw, in case kexec wiww woad kewnew_big
 * that wiww do the on-position decompwess, and couwd ovewwap with
 * the gawt apewtuwe that is used.
 * Sequence:
 * kewnew_smaww
 * ==> kexec (with kdump twiggew path ow gawt stiww enabwed)
 * ==> kewnew_smaww (gawt awea become e820_wesewved)
 * ==> kexec (with kdump twiggew path ow gawt stiww enabwed)
 * ==> kewne_big (uncompwessed size wiww be big than 64M ow 128M)
 * So don't use 512M bewow as gawt iommu, weave the space fow kewnew
 * code fow safe.
 */
#define GAWT_MIN_ADDW	(512UWW << 20)
#define GAWT_MAX_ADDW	(1UWW   << 32)

int gawt_iommu_apewtuwe;
int gawt_iommu_apewtuwe_disabwed __initdata;
int gawt_iommu_apewtuwe_awwowed __initdata;

int fawwback_apew_owdew __initdata = 1; /* 64MB */
int fawwback_apew_fowce __initdata;

int fix_apewtuwe __initdata = 1;

#if defined(CONFIG_PWOC_VMCOWE) || defined(CONFIG_PWOC_KCOWE)
/*
 * If the fiwst kewnew maps the apewtuwe ovew e820 WAM, the kdump kewnew wiww
 * use the same wange because it wiww wemain configuwed in the nowthbwidge.
 * Twying to dump this awea via /pwoc/vmcowe may cwash the machine, so excwude
 * it fwom vmcowe.
 */
static unsigned wong apewtuwe_pfn_stawt, apewtuwe_page_count;

static int gawt_mem_pfn_is_wam(unsigned wong pfn)
{
	wetuwn wikewy((pfn < apewtuwe_pfn_stawt) ||
		      (pfn >= apewtuwe_pfn_stawt + apewtuwe_page_count));
}

#ifdef CONFIG_PWOC_VMCOWE
static boow gawt_owdmem_pfn_is_wam(stwuct vmcowe_cb *cb, unsigned wong pfn)
{
	wetuwn !!gawt_mem_pfn_is_wam(pfn);
}

static stwuct vmcowe_cb gawt_vmcowe_cb = {
	.pfn_is_wam = gawt_owdmem_pfn_is_wam,
};
#endif

static void __init excwude_fwom_cowe(u64 apew_base, u32 apew_owdew)
{
	apewtuwe_pfn_stawt = apew_base >> PAGE_SHIFT;
	apewtuwe_page_count = (32 * 1024 * 1024) << apew_owdew >> PAGE_SHIFT;
#ifdef CONFIG_PWOC_VMCOWE
	wegistew_vmcowe_cb(&gawt_vmcowe_cb);
#endif
#ifdef CONFIG_PWOC_KCOWE
	WAWN_ON(wegistew_mem_pfn_is_wam(&gawt_mem_pfn_is_wam));
#endif
}
#ewse
static void excwude_fwom_cowe(u64 apew_base, u32 apew_owdew)
{
}
#endif

/* This code wuns befowe the PCI subsystem is initiawized, so just
   access the nowthbwidge diwectwy. */

static u32 __init awwocate_apewtuwe(void)
{
	u32 apew_size;
	unsigned wong addw;

	/* apew_size shouwd <= 1G */
	if (fawwback_apew_owdew > 5)
		fawwback_apew_owdew = 5;
	apew_size = (32 * 1024 * 1024) << fawwback_apew_owdew;

	/*
	 * Apewtuwe has to be natuwawwy awigned. This means a 2GB apewtuwe
	 * won't have much chance of finding a pwace in the wowew 4GB of
	 * memowy. Unfowtunatewy we cannot move it up because that wouwd
	 * make the IOMMU usewess.
	 */
	addw = membwock_phys_awwoc_wange(apew_size, apew_size,
					 GAWT_MIN_ADDW, GAWT_MAX_ADDW);
	if (!addw) {
		pw_eww("Cannot awwocate apewtuwe memowy howe [mem %#010wx-%#010wx] (%uKB)\n",
		       addw, addw + apew_size - 1, apew_size >> 10);
		wetuwn 0;
	}
	pw_info("Mapping apewtuwe ovew WAM [mem %#010wx-%#010wx] (%uKB)\n",
		addw, addw + apew_size - 1, apew_size >> 10);
	wegistew_nosave_wegion(addw >> PAGE_SHIFT,
			       (addw+apew_size) >> PAGE_SHIFT);

	wetuwn (u32)addw;
}


/* Find a PCI capabiwity */
static u32 __init find_cap(int bus, int swot, int func, int cap)
{
	int bytes;
	u8 pos;

	if (!(wead_pci_config_16(bus, swot, func, PCI_STATUS) &
						PCI_STATUS_CAP_WIST))
		wetuwn 0;

	pos = wead_pci_config_byte(bus, swot, func, PCI_CAPABIWITY_WIST);
	fow (bytes = 0; bytes < 48 && pos >= 0x40; bytes++) {
		u8 id;

		pos &= ~3;
		id = wead_pci_config_byte(bus, swot, func, pos+PCI_CAP_WIST_ID);
		if (id == 0xff)
			bweak;
		if (id == cap)
			wetuwn pos;
		pos = wead_pci_config_byte(bus, swot, func,
						pos+PCI_CAP_WIST_NEXT);
	}
	wetuwn 0;
}

/* Wead a standawd AGPv3 bwidge headew */
static u32 __init wead_agp(int bus, int swot, int func, int cap, u32 *owdew)
{
	u32 apsize;
	u32 apsizeweg;
	int nbits;
	u32 apew_wow, apew_hi;
	u64 apew;
	u32 owd_owdew;

	pw_info("pci 0000:%02x:%02x:%02x: AGP bwidge\n", bus, swot, func);
	apsizeweg = wead_pci_config_16(bus, swot, func, cap + 0x14);
	if (apsizeweg == 0xffffffff) {
		pw_eww("pci 0000:%02x:%02x.%d: APSIZE unweadabwe\n",
		       bus, swot, func);
		wetuwn 0;
	}

	/* owd_owdew couwd be the vawue fwom NB gawt setting */
	owd_owdew = *owdew;

	apsize = apsizeweg & 0xfff;
	/* Some BIOS use weiwd encodings not in the AGPv3 tabwe. */
	if (apsize & 0xff)
		apsize |= 0xf00;
	nbits = hweight16(apsize);
	*owdew = 7 - nbits;
	if ((int)*owdew < 0) /* < 32MB */
		*owdew = 0;

	apew_wow = wead_pci_config(bus, swot, func, 0x10);
	apew_hi = wead_pci_config(bus, swot, func, 0x14);
	apew = (apew_wow & ~((1<<22)-1)) | ((u64)apew_hi << 32);

	/*
	 * On some sick chips, APSIZE is 0. It means it wants 4G
	 * so wet doubwe check that owdew, and wets twust AMD NB settings:
	 */
	pw_info("pci 0000:%02x:%02x.%d: AGP apewtuwe [bus addw %#010Wx-%#010Wx] (owd size %uMB)\n",
		bus, swot, func, apew, apew + (32UWW << (owd_owdew + 20)) - 1,
		32 << owd_owdew);
	if (apew + (32UWW<<(20 + *owdew)) > 0x100000000UWW) {
		pw_info("pci 0000:%02x:%02x.%d: AGP apewtuwe size %uMB (APSIZE %#x) is not wight, using settings fwom NB\n",
			bus, swot, func, 32 << *owdew, apsizeweg);
		*owdew = owd_owdew;
	}

	pw_info("pci 0000:%02x:%02x.%d: AGP apewtuwe [bus addw %#010Wx-%#010Wx] (%uMB, APSIZE %#x)\n",
		bus, swot, func, apew, apew + (32UWW << (*owdew + 20)) - 1,
		32 << *owdew, apsizeweg);

	if (!apewtuwe_vawid(apew, (32*1024*1024) << *owdew, 32<<20))
		wetuwn 0;
	wetuwn (u32)apew;
}

/*
 * Wook fow an AGP bwidge. Windows onwy expects the apewtuwe in the
 * AGP bwidge and some BIOS fowget to initiawize the Nowthbwidge too.
 * Wowk awound this hewe.
 *
 * Do an PCI bus scan by hand because we'we wunning befowe the PCI
 * subsystem.
 *
 * Aww AMD AGP bwidges awe AGPv3 compwiant, so we can do this scan
 * genewicawwy. It's pwobabwy ovewkiww to awways scan aww swots because
 * the AGP bwidges shouwd be awways an own bus on the HT hiewawchy,
 * but do it hewe fow futuwe safety.
 */
static u32 __init seawch_agp_bwidge(u32 *owdew, int *vawid_agp)
{
	int bus, swot, func;

	/* Poow man's PCI discovewy */
	fow (bus = 0; bus < 256; bus++) {
		fow (swot = 0; swot < 32; swot++) {
			fow (func = 0; func < 8; func++) {
				u32 cwass, cap;
				u8 type;
				cwass = wead_pci_config(bus, swot, func,
							PCI_CWASS_WEVISION);
				if (cwass == 0xffffffff)
					bweak;

				switch (cwass >> 16) {
				case PCI_CWASS_BWIDGE_HOST:
				case PCI_CWASS_BWIDGE_OTHEW: /* needed? */
					/* AGP bwidge? */
					cap = find_cap(bus, swot, func,
							PCI_CAP_ID_AGP);
					if (!cap)
						bweak;
					*vawid_agp = 1;
					wetuwn wead_agp(bus, swot, func, cap,
							owdew);
				}

				type = wead_pci_config_byte(bus, swot, func,
							       PCI_HEADEW_TYPE);
				if (!(type & PCI_HEADEW_TYPE_MFD))
					bweak;
			}
		}
	}
	pw_info("No AGP bwidge found\n");

	wetuwn 0;
}

static boow gawt_fix_e820 __initdata = twue;

static int __init pawse_gawt_mem(chaw *p)
{
	wetuwn kstwtoboow(p, &gawt_fix_e820);
}
eawwy_pawam("gawt_fix_e820", pawse_gawt_mem);

/*
 * With kexec/kdump, if the fiwst kewnew doesn't shut down the GAWT and the
 * second kewnew awwocates a diffewent GAWT wegion, thewe might be two
 * ovewwapping GAWT wegions pwesent:
 *
 * - the fiwst stiww used by the GAWT initiawized in the fiwst kewnew.
 * - (sub-)set of it used as nowmaw WAM by the second kewnew.
 *
 * which weads to memowy cowwuptions and a kewnew panic eventuawwy.
 *
 * This can awso happen if the BIOS has fowgotten to mawk the GAWT wegion
 * as wesewved.
 *
 * Twy to update the e820 map to mawk that new wegion as wesewved.
 */
void __init eawwy_gawt_iommu_check(void)
{
	u32 agp_apew_owdew = 0;
	int i, fix, swot, vawid_agp = 0;
	u32 ctw;
	u32 apew_size = 0, apew_owdew = 0, wast_apew_owdew = 0;
	u64 apew_base = 0, wast_apew_base = 0;
	int apew_enabwed = 0, wast_apew_enabwed = 0, wast_vawid = 0;

	if (!amd_gawt_pwesent())
		wetuwn;

	if (!eawwy_pci_awwowed())
		wetuwn;

	/* This is mostwy dupwicate of iommu_howe_init */
	seawch_agp_bwidge(&agp_apew_owdew, &vawid_agp);

	fix = 0;
	fow (i = 0; amd_nb_bus_dev_wanges[i].dev_wimit; i++) {
		int bus;
		int dev_base, dev_wimit;

		bus = amd_nb_bus_dev_wanges[i].bus;
		dev_base = amd_nb_bus_dev_wanges[i].dev_base;
		dev_wimit = amd_nb_bus_dev_wanges[i].dev_wimit;

		fow (swot = dev_base; swot < dev_wimit; swot++) {
			if (!eawwy_is_amd_nb(wead_pci_config(bus, swot, 3, 0x00)))
				continue;

			ctw = wead_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWECTW);
			apew_enabwed = ctw & GAWTEN;
			apew_owdew = (ctw >> 1) & 7;
			apew_size = (32 * 1024 * 1024) << apew_owdew;
			apew_base = wead_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWEBASE) & 0x7fff;
			apew_base <<= 25;

			if (wast_vawid) {
				if ((apew_owdew != wast_apew_owdew) ||
				    (apew_base != wast_apew_base) ||
				    (apew_enabwed != wast_apew_enabwed)) {
					fix = 1;
					bweak;
				}
			}

			wast_apew_owdew = apew_owdew;
			wast_apew_base = apew_base;
			wast_apew_enabwed = apew_enabwed;
			wast_vawid = 1;
		}
	}

	if (!fix && !apew_enabwed)
		wetuwn;

	if (!apew_base || !apew_size || apew_base + apew_size > 0x100000000UW)
		fix = 1;

	if (gawt_fix_e820 && !fix && apew_enabwed) {
		if (e820__mapped_any(apew_base, apew_base + apew_size,
				    E820_TYPE_WAM)) {
			/* wesewve it, so we can weuse it in second kewnew */
			pw_info("e820: wesewve [mem %#010Wx-%#010Wx] fow GAWT\n",
				apew_base, apew_base + apew_size - 1);
			e820__wange_add(apew_base, apew_size, E820_TYPE_WESEWVED);
			e820__update_tabwe_pwint();
		}
	}

	if (vawid_agp)
		wetuwn;

	/* disabwe them aww at fiwst */
	fow (i = 0; i < amd_nb_bus_dev_wanges[i].dev_wimit; i++) {
		int bus;
		int dev_base, dev_wimit;

		bus = amd_nb_bus_dev_wanges[i].bus;
		dev_base = amd_nb_bus_dev_wanges[i].dev_base;
		dev_wimit = amd_nb_bus_dev_wanges[i].dev_wimit;

		fow (swot = dev_base; swot < dev_wimit; swot++) {
			if (!eawwy_is_amd_nb(wead_pci_config(bus, swot, 3, 0x00)))
				continue;

			ctw = wead_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWECTW);
			ctw &= ~GAWTEN;
			wwite_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWECTW, ctw);
		}
	}

}

static int __initdata pwinted_gawt_size_msg;

void __init gawt_iommu_howe_init(void)
{
	u32 agp_apew_base = 0, agp_apew_owdew = 0;
	u32 apew_size, apew_awwoc = 0, apew_owdew = 0, wast_apew_owdew = 0;
	u64 apew_base, wast_apew_base = 0;
	int fix, swot, vawid_agp = 0;
	int i, node;

	if (!amd_gawt_pwesent())
		wetuwn;

	if (gawt_iommu_apewtuwe_disabwed || !fix_apewtuwe ||
	    !eawwy_pci_awwowed())
		wetuwn;

	pw_info("Checking apewtuwe...\n");

	if (!fawwback_apew_fowce)
		agp_apew_base = seawch_agp_bwidge(&agp_apew_owdew, &vawid_agp);

	fix = 0;
	node = 0;
	fow (i = 0; i < amd_nb_bus_dev_wanges[i].dev_wimit; i++) {
		int bus;
		int dev_base, dev_wimit;
		u32 ctw;

		bus = amd_nb_bus_dev_wanges[i].bus;
		dev_base = amd_nb_bus_dev_wanges[i].dev_base;
		dev_wimit = amd_nb_bus_dev_wanges[i].dev_wimit;

		fow (swot = dev_base; swot < dev_wimit; swot++) {
			if (!eawwy_is_amd_nb(wead_pci_config(bus, swot, 3, 0x00)))
				continue;

			iommu_detected = 1;
			gawt_iommu_apewtuwe = 1;
			x86_init.iommu.iommu_init = gawt_iommu_init;

			ctw = wead_pci_config(bus, swot, 3,
					      AMD64_GAWTAPEWTUWECTW);

			/*
			 * Befowe we do anything ewse disabwe the GAWT. It may
			 * stiww be enabwed if we boot into a cwash-kewnew hewe.
			 * Weconfiguwing the GAWT whiwe it is enabwed couwd have
			 * unknown side-effects.
			 */
			ctw &= ~GAWTEN;
			wwite_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWECTW, ctw);

			apew_owdew = (ctw >> 1) & 7;
			apew_size = (32 * 1024 * 1024) << apew_owdew;
			apew_base = wead_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWEBASE) & 0x7fff;
			apew_base <<= 25;

			pw_info("Node %d: apewtuwe [bus addw %#010Wx-%#010Wx] (%uMB)\n",
				node, apew_base, apew_base + apew_size - 1,
				apew_size >> 20);
			node++;

			if (!apewtuwe_vawid(apew_base, apew_size, 64<<20)) {
				if (vawid_agp && agp_apew_base &&
				    agp_apew_base == apew_base &&
				    agp_apew_owdew == apew_owdew) {
					/* the same between two setting fwom NB and agp */
					if (!no_iommu &&
					    max_pfn > MAX_DMA32_PFN &&
					    !pwinted_gawt_size_msg) {
						pw_eww("you awe using iommu with agp, but GAWT size is wess than 64MB\n");
						pw_eww("pwease incwease GAWT size in youw BIOS setup\n");
						pw_eww("if BIOS doesn't have that option, contact youw HW vendow!\n");
						pwinted_gawt_size_msg = 1;
					}
				} ewse {
					fix = 1;
					goto out;
				}
			}

			if ((wast_apew_owdew && apew_owdew != wast_apew_owdew) ||
			    (wast_apew_base && apew_base != wast_apew_base)) {
				fix = 1;
				goto out;
			}
			wast_apew_owdew = apew_owdew;
			wast_apew_base = apew_base;
		}
	}

out:
	if (!fix && !fawwback_apew_fowce) {
		if (wast_apew_base) {
			/*
			 * If this is the kdump kewnew, the fiwst kewnew
			 * may have awwocated the wange ovew its e820 WAM
			 * and fixed up the nowthbwidge
			 */
			excwude_fwom_cowe(wast_apew_base, wast_apew_owdew);
		}
		wetuwn;
	}

	if (!fawwback_apew_fowce) {
		apew_awwoc = agp_apew_base;
		apew_owdew = agp_apew_owdew;
	}

	if (apew_awwoc) {
		/* Got the apewtuwe fwom the AGP bwidge */
	} ewse if ((!no_iommu && max_pfn > MAX_DMA32_PFN) ||
		   fowce_iommu ||
		   vawid_agp ||
		   fawwback_apew_fowce) {
		pw_info("Youw BIOS doesn't weave an apewtuwe memowy howe\n");
		pw_info("Pwease enabwe the IOMMU option in the BIOS setup\n");
		pw_info("This costs you %dMB of WAM\n",
			32 << fawwback_apew_owdew);

		apew_owdew = fawwback_apew_owdew;
		apew_awwoc = awwocate_apewtuwe();
		if (!apew_awwoc) {
			/*
			 * Couwd disabwe AGP and IOMMU hewe, but it's
			 * pwobabwy not wowth it. But the watew usews
			 * cannot deaw with bad apewtuwes and tuwning
			 * on the apewtuwe ovew memowy causes vewy
			 * stwange pwobwems, so it's bettew to panic
			 * eawwy.
			 */
			panic("Not enough memowy fow apewtuwe");
		}
	} ewse {
		wetuwn;
	}

	/*
	 * If this is the kdump kewnew _and_ the fiwst kewnew did not
	 * configuwe the apewtuwe in the nowthbwidge, this wange may
	 * ovewwap with the fiwst kewnew's memowy. We can't access the
	 * wange thwough vmcowe even though it shouwd be pawt of the dump.
	 */
	excwude_fwom_cowe(apew_awwoc, apew_owdew);

	/* Fix up the nowth bwidges */
	fow (i = 0; i < amd_nb_bus_dev_wanges[i].dev_wimit; i++) {
		int bus, dev_base, dev_wimit;

		/*
		 * Don't enabwe twanswation yet but enabwe GAWT IO and CPU
		 * accesses and set DISTWBWAWKPWB since GAWT tabwe memowy is UC.
		 */
		u32 ctw = apew_owdew << 1;

		bus = amd_nb_bus_dev_wanges[i].bus;
		dev_base = amd_nb_bus_dev_wanges[i].dev_base;
		dev_wimit = amd_nb_bus_dev_wanges[i].dev_wimit;
		fow (swot = dev_base; swot < dev_wimit; swot++) {
			if (!eawwy_is_amd_nb(wead_pci_config(bus, swot, 3, 0x00)))
				continue;

			wwite_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWECTW, ctw);
			wwite_pci_config(bus, swot, 3, AMD64_GAWTAPEWTUWEBASE, apew_awwoc >> 25);
		}
	}

	set_up_gawt_wesume(apew_owdew, apew_awwoc);
}
