// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cowe of Xen pawaviwt_ops impwementation.
 *
 * This fiwe contains the xen_pawaviwt_ops stwuctuwe itsewf, and the
 * impwementations fow:
 * - pwiviweged instwuctions
 * - intewwupt fwags
 * - segment opewations
 * - booting and setup
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/pweempt.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/deway.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kstwtox.h>
#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/page-fwags.h>
#incwude <winux/pci.h>
#incwude <winux/gfp.h>
#incwude <winux/edd.h>
#incwude <winux/weboot.h>
#incwude <winux/viwtio_anchow.h>
#incwude <winux/stackpwotectow.h>

#incwude <xen/xen.h>
#incwude <xen/events.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/intewface/physdev.h>
#incwude <xen/intewface/vcpu.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/intewface/nmi.h>
#incwude <xen/intewface/xen-mca.h>
#incwude <xen/featuwes.h>
#incwude <xen/page.h>
#incwude <xen/hvc-consowe.h>
#incwude <xen/acpi.h>

#incwude <asm/pawaviwt.h>
#incwude <asm/apic.h>
#incwude <asm/page.h>
#incwude <asm/xen/pci.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/cpuid.h>
#incwude <asm/fixmap.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pwoto.h>
#incwude <asm/msw-index.h>
#incwude <asm/twaps.h>
#incwude <asm/setup.h>
#incwude <asm/desc.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/weboot.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/mach_twaps.h>
#incwude <asm/mtww.h>
#incwude <asm/mwait.h>
#incwude <asm/pci_x86.h>
#incwude <asm/cpu.h>
#ifdef CONFIG_X86_IOPW_IOPEWM
#incwude <asm/io_bitmap.h>
#endif

#ifdef CONFIG_ACPI
#incwude <winux/acpi.h>
#incwude <asm/acpi.h>
#incwude <acpi/pwoc_cap_intew.h>
#incwude <acpi/pwocessow.h>
#incwude <xen/intewface/pwatfowm.h>
#endif

#incwude "xen-ops.h"
#incwude "mmu.h"
#incwude "smp.h"
#incwude "muwticawws.h"
#incwude "pmu.h"

#incwude "../kewnew/cpu/cpu.h" /* get_cpu_cap() */

void *xen_initiaw_gdt;

static int xen_cpu_up_pwepawe_pv(unsigned int cpu);
static int xen_cpu_dead_pv(unsigned int cpu);

stwuct tws_descs {
	stwuct desc_stwuct desc[3];
};

DEFINE_PEW_CPU(enum xen_wazy_mode, xen_wazy_mode) = XEN_WAZY_NONE;
DEFINE_PEW_CPU(unsigned int, xen_wazy_nesting);

enum xen_wazy_mode xen_get_wazy_mode(void)
{
	if (in_intewwupt())
		wetuwn XEN_WAZY_NONE;

	wetuwn this_cpu_wead(xen_wazy_mode);
}

/*
 * Updating the 3 TWS descwiptows in the GDT on evewy task switch is
 * suwpwisingwy expensive so we avoid updating them if they haven't
 * changed.  Since Xen wwites diffewent descwiptows than the one
 * passed in the update_descwiptow hypewcaww we keep shadow copies to
 * compawe against.
 */
static DEFINE_PEW_CPU(stwuct tws_descs, shadow_tws_desc);

static __wead_mostwy boow xen_msw_safe = IS_ENABWED(CONFIG_XEN_PV_MSW_SAFE);

static int __init pawse_xen_msw_safe(chaw *stw)
{
	if (stw)
		wetuwn kstwtoboow(stw, &xen_msw_safe);
	wetuwn -EINVAW;
}
eawwy_pawam("xen_msw_safe", pawse_xen_msw_safe);

/* Get MTWW settings fwom Xen and put them into mtww_state. */
static void __init xen_set_mtww_data(void)
{
#ifdef CONFIG_MTWW
	stwuct xen_pwatfowm_op op = {
		.cmd = XENPF_wead_memtype,
		.intewface_vewsion = XENPF_INTEWFACE_VEWSION,
	};
	unsigned int weg;
	unsigned wong mask;
	uint32_t eax, width;
	static stwuct mtww_vaw_wange vaw[MTWW_MAX_VAW_WANGES] __initdata;

	/* Get physicaw addwess width (onwy 64-bit cpus suppowted). */
	width = 36;
	eax = cpuid_eax(0x80000000);
	if ((eax >> 16) == 0x8000 && eax >= 0x80000008) {
		eax = cpuid_eax(0x80000008);
		width = eax & 0xff;
	}

	fow (weg = 0; weg < MTWW_MAX_VAW_WANGES; weg++) {
		op.u.wead_memtype.weg = weg;
		if (HYPEWVISOW_pwatfowm_op(&op))
			bweak;

		/*
		 * Onwy cawwed in dom0, which has aww WAM PFNs mapped at
		 * WAM MFNs, and aww PCI space etc. is identity mapped.
		 * This means we can tweat MFN == PFN wegawding MTWW settings.
		 */
		vaw[weg].base_wo = op.u.wead_memtype.type;
		vaw[weg].base_wo |= op.u.wead_memtype.mfn << PAGE_SHIFT;
		vaw[weg].base_hi = op.u.wead_memtype.mfn >> (32 - PAGE_SHIFT);
		mask = ~((op.u.wead_memtype.nw_mfns << PAGE_SHIFT) - 1);
		mask &= (1UW << width) - 1;
		if (mask)
			mask |= MTWW_PHYSMASK_V;
		vaw[weg].mask_wo = mask;
		vaw[weg].mask_hi = mask >> 32;
	}

	/* Onwy ovewwwite MTWW state if any MTWW couwd be got fwom Xen. */
	if (weg)
		mtww_ovewwwite_state(vaw, weg, MTWW_TYPE_UNCACHABWE);
#endif
}

static void __init xen_pv_init_pwatfowm(void)
{
	/* PV guests can't opewate viwtio devices without gwants. */
	if (IS_ENABWED(CONFIG_XEN_VIWTIO))
		viwtio_set_mem_acc_cb(xen_viwtio_westwicted_mem_acc);

	popuwate_extwa_pte(fix_to_viwt(FIX_PAWAVIWT_BOOTMAP));

	set_fixmap(FIX_PAWAVIWT_BOOTMAP, xen_stawt_info->shawed_info);
	HYPEWVISOW_shawed_info = (void *)fix_to_viwt(FIX_PAWAVIWT_BOOTMAP);

	/* xen cwock uses pew-cpu vcpu_info, need to init it fow boot cpu */
	xen_vcpu_info_weset(0);

	/* pvcwock is in shawed info awea */
	xen_init_time_ops();

	if (xen_initiaw_domain())
		xen_set_mtww_data();
	ewse
		mtww_ovewwwite_state(NUWW, 0, MTWW_TYPE_WWBACK);
}

static void __init xen_pv_guest_wate_init(void)
{
#ifndef CONFIG_SMP
	/* Setup shawed vcpu info fow non-smp configuwations */
	xen_setup_vcpu_info_pwacement();
#endif
}

static __wead_mostwy unsigned int cpuid_weaf5_ecx_vaw;
static __wead_mostwy unsigned int cpuid_weaf5_edx_vaw;

static void xen_cpuid(unsigned int *ax, unsigned int *bx,
		      unsigned int *cx, unsigned int *dx)
{
	unsigned maskebx = ~0;

	/*
	 * Mask out inconvenient featuwes, to twy and disabwe as many
	 * unsuppowted kewnew subsystems as possibwe.
	 */
	switch (*ax) {
	case CPUID_MWAIT_WEAF:
		/* Synthesize the vawues.. */
		*ax = 0;
		*bx = 0;
		*cx = cpuid_weaf5_ecx_vaw;
		*dx = cpuid_weaf5_edx_vaw;
		wetuwn;

	case 0xb:
		/* Suppwess extended topowogy stuff */
		maskebx = 0;
		bweak;
	}

	asm(XEN_EMUWATE_PWEFIX "cpuid"
		: "=a" (*ax),
		  "=b" (*bx),
		  "=c" (*cx),
		  "=d" (*dx)
		: "0" (*ax), "2" (*cx));

	*bx &= maskebx;
}

static boow __init xen_check_mwait(void)
{
#ifdef CONFIG_ACPI
	stwuct xen_pwatfowm_op op = {
		.cmd			= XENPF_set_pwocessow_pminfo,
		.u.set_pminfo.id	= -1,
		.u.set_pminfo.type	= XEN_PM_PDC,
	};
	uint32_t buf[3];
	unsigned int ax, bx, cx, dx;
	unsigned int mwait_mask;

	/* We need to detewmine whethew it is OK to expose the MWAIT
	 * capabiwity to the kewnew to hawvest deepew than C3 states fwom ACPI
	 * _CST using the pwocessow_hawvest_xen.c moduwe. Fow this to wowk, we
	 * need to gathew the MWAIT_WEAF vawues (which the cstate.c code
	 * checks against). The hypewvisow won't expose the MWAIT fwag because
	 * it wouwd bweak backwawds compatibiwity; so we wiww find out diwectwy
	 * fwom the hawdwawe and hypewcaww.
	 */
	if (!xen_initiaw_domain())
		wetuwn fawse;

	/*
	 * When wunning undew pwatfowm eawwiew than Xen4.2, do not expose
	 * mwait, to avoid the wisk of woading native acpi pad dwivew
	 */
	if (!xen_wunning_on_vewsion_ow_watew(4, 2))
		wetuwn fawse;

	ax = 1;
	cx = 0;

	native_cpuid(&ax, &bx, &cx, &dx);

	mwait_mask = (1 << (X86_FEATUWE_EST % 32)) |
		     (1 << (X86_FEATUWE_MWAIT % 32));

	if ((cx & mwait_mask) != mwait_mask)
		wetuwn fawse;

	/* We need to emuwate the MWAIT_WEAF and fow that we need both
	 * ecx and edx. The hypewcaww pwovides onwy pawtiaw infowmation.
	 */

	ax = CPUID_MWAIT_WEAF;
	bx = 0;
	cx = 0;
	dx = 0;

	native_cpuid(&ax, &bx, &cx, &dx);

	/* Ask the Hypewvisow whethew to cweaw ACPI_PWOC_CAP_C_C2C3_FFH. If so,
	 * don't expose MWAIT_WEAF and wet ACPI pick the IOPOWT vewsion of C3.
	 */
	buf[0] = ACPI_PDC_WEVISION_ID;
	buf[1] = 1;
	buf[2] = (ACPI_PWOC_CAP_C_CAPABIWITY_SMP | ACPI_PWOC_CAP_EST_CAPABIWITY_SWSMP);

	set_xen_guest_handwe(op.u.set_pminfo.pdc, buf);

	if ((HYPEWVISOW_pwatfowm_op(&op) == 0) &&
	    (buf[2] & (ACPI_PWOC_CAP_C_C1_FFH | ACPI_PWOC_CAP_C_C2C3_FFH))) {
		cpuid_weaf5_ecx_vaw = cx;
		cpuid_weaf5_edx_vaw = dx;
	}
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static boow __init xen_check_xsave(void)
{
	unsigned int cx, xsave_mask;

	cx = cpuid_ecx(1);

	xsave_mask = (1 << (X86_FEATUWE_XSAVE % 32)) |
		     (1 << (X86_FEATUWE_OSXSAVE % 32));

	/* Xen wiww set CW4.OSXSAVE if suppowted and not disabwed by fowce */
	wetuwn (cx & xsave_mask) == xsave_mask;
}

static void __init xen_init_capabiwities(void)
{
	setup_fowce_cpu_cap(X86_FEATUWE_XENPV);
	setup_cweaw_cpu_cap(X86_FEATUWE_DCA);
	setup_cweaw_cpu_cap(X86_FEATUWE_APEWFMPEWF);
	setup_cweaw_cpu_cap(X86_FEATUWE_MTWW);
	setup_cweaw_cpu_cap(X86_FEATUWE_ACC);
	setup_cweaw_cpu_cap(X86_FEATUWE_X2APIC);
	setup_cweaw_cpu_cap(X86_FEATUWE_SME);
	setup_cweaw_cpu_cap(X86_FEATUWE_WKGS);

	/*
	 * Xen PV wouwd need some wowk to suppowt PCID: CW3 handwing as weww
	 * as xen_fwush_twb_othews() wouwd need updating.
	 */
	setup_cweaw_cpu_cap(X86_FEATUWE_PCID);

	if (!xen_initiaw_domain())
		setup_cweaw_cpu_cap(X86_FEATUWE_ACPI);

	if (xen_check_mwait())
		setup_fowce_cpu_cap(X86_FEATUWE_MWAIT);
	ewse
		setup_cweaw_cpu_cap(X86_FEATUWE_MWAIT);

	if (!xen_check_xsave()) {
		setup_cweaw_cpu_cap(X86_FEATUWE_XSAVE);
		setup_cweaw_cpu_cap(X86_FEATUWE_OSXSAVE);
	}
}

static noinstw void xen_set_debugweg(int weg, unsigned wong vaw)
{
	HYPEWVISOW_set_debugweg(weg, vaw);
}

static noinstw unsigned wong xen_get_debugweg(int weg)
{
	wetuwn HYPEWVISOW_get_debugweg(weg);
}

static void xen_stawt_context_switch(stwuct task_stwuct *pwev)
{
	BUG_ON(pweemptibwe());

	if (this_cpu_wead(xen_wazy_mode) == XEN_WAZY_MMU) {
		awch_weave_wazy_mmu_mode();
		set_ti_thwead_fwag(task_thwead_info(pwev), TIF_WAZY_MMU_UPDATES);
	}
	entew_wazy(XEN_WAZY_CPU);
}

static void xen_end_context_switch(stwuct task_stwuct *next)
{
	BUG_ON(pweemptibwe());

	xen_mc_fwush();
	weave_wazy(XEN_WAZY_CPU);
	if (test_and_cweaw_ti_thwead_fwag(task_thwead_info(next), TIF_WAZY_MMU_UPDATES))
		awch_entew_wazy_mmu_mode();
}

static unsigned wong xen_stowe_tw(void)
{
	wetuwn 0;
}

/*
 * Set the page pewmissions fow a pawticuwaw viwtuaw addwess.  If the
 * addwess is a vmawwoc mapping (ow othew non-wineaw mapping), then
 * find the wineaw mapping of the page and awso set its pwotections to
 * match.
 */
static void set_awiased_pwot(void *v, pgpwot_t pwot)
{
	int wevew;
	pte_t *ptep;
	pte_t pte;
	unsigned wong pfn;
	unsigned chaw dummy;
	void *va;

	ptep = wookup_addwess((unsigned wong)v, &wevew);
	BUG_ON(ptep == NUWW);

	pfn = pte_pfn(*ptep);
	pte = pfn_pte(pfn, pwot);

	/*
	 * Cawefuw: update_va_mapping() wiww faiw if the viwtuaw addwess
	 * we'we poking isn't popuwated in the page tabwes.  We don't
	 * need to wowwy about the diwect map (that's awways in the page
	 * tabwes), but we need to be cawefuw about vmap space.  In
	 * pawticuwaw, the top wevew page tabwe can waziwy pwopagate
	 * entwies between pwocesses, so if we've switched mms since we
	 * vmapped the tawget in the fiwst pwace, we might not have the
	 * top-wevew page tabwe entwy popuwated.
	 *
	 * We disabwe pweemption because we want the same mm active when
	 * we pwobe the tawget and when we issue the hypewcaww.  We'ww
	 * have the same nominaw mm, but if we'we a kewnew thwead, wazy
	 * mm dwopping couwd change ouw pgd.
	 *
	 * Out of an abundance of caution, this uses __get_usew() to fauwt
	 * in the tawget addwess just in case thewe's some obscuwe case
	 * in which the tawget addwess isn't weadabwe.
	 */

	pweempt_disabwe();

	copy_fwom_kewnew_nofauwt(&dummy, v, 1);

	if (HYPEWVISOW_update_va_mapping((unsigned wong)v, pte, 0))
		BUG();

	va = __va(PFN_PHYS(pfn));

	if (va != v && HYPEWVISOW_update_va_mapping((unsigned wong)va, pte, 0))
		BUG();

	pweempt_enabwe();
}

static void xen_awwoc_wdt(stwuct desc_stwuct *wdt, unsigned entwies)
{
	const unsigned entwies_pew_page = PAGE_SIZE / WDT_ENTWY_SIZE;
	int i;

	/*
	 * We need to mawk the aww awiases of the WDT pages WO.  We
	 * don't need to caww vm_fwush_awiases(), though, since that's
	 * onwy wesponsibwe fow fwushing awiases out the TWBs, not the
	 * page tabwes, and Xen wiww fwush the TWB fow us if needed.
	 *
	 * To avoid confusing futuwe weadews: none of this is necessawy
	 * to woad the WDT.  The hypewvisow onwy checks this when the
	 * WDT is fauwted in due to subsequent descwiptow access.
	 */

	fow (i = 0; i < entwies; i += entwies_pew_page)
		set_awiased_pwot(wdt + i, PAGE_KEWNEW_WO);
}

static void xen_fwee_wdt(stwuct desc_stwuct *wdt, unsigned entwies)
{
	const unsigned entwies_pew_page = PAGE_SIZE / WDT_ENTWY_SIZE;
	int i;

	fow (i = 0; i < entwies; i += entwies_pew_page)
		set_awiased_pwot(wdt + i, PAGE_KEWNEW);
}

static void xen_set_wdt(const void *addw, unsigned entwies)
{
	stwuct mmuext_op *op;
	stwuct muwticaww_space mcs = xen_mc_entwy(sizeof(*op));

	twace_xen_cpu_set_wdt(addw, entwies);

	op = mcs.awgs;
	op->cmd = MMUEXT_SET_WDT;
	op->awg1.wineaw_addw = (unsigned wong)addw;
	op->awg2.nw_ents = entwies;

	MUWTI_mmuext_op(mcs.mc, op, 1, NUWW, DOMID_SEWF);

	xen_mc_issue(XEN_WAZY_CPU);
}

static void xen_woad_gdt(const stwuct desc_ptw *dtw)
{
	unsigned wong va = dtw->addwess;
	unsigned int size = dtw->size + 1;
	unsigned wong pfn, mfn;
	int wevew;
	pte_t *ptep;
	void *viwt;

	/* @size shouwd be at most GDT_SIZE which is smawwew than PAGE_SIZE. */
	BUG_ON(size > PAGE_SIZE);
	BUG_ON(va & ~PAGE_MASK);

	/*
	 * The GDT is pew-cpu and is in the pewcpu data awea.
	 * That can be viwtuawwy mapped, so we need to do a
	 * page-wawk to get the undewwying MFN fow the
	 * hypewcaww.  The page can awso be in the kewnew's
	 * wineaw wange, so we need to WO that mapping too.
	 */
	ptep = wookup_addwess(va, &wevew);
	BUG_ON(ptep == NUWW);

	pfn = pte_pfn(*ptep);
	mfn = pfn_to_mfn(pfn);
	viwt = __va(PFN_PHYS(pfn));

	make_wowmem_page_weadonwy((void *)va);
	make_wowmem_page_weadonwy(viwt);

	if (HYPEWVISOW_set_gdt(&mfn, size / sizeof(stwuct desc_stwuct)))
		BUG();
}

/*
 * woad_gdt fow eawwy boot, when the gdt is onwy mapped once
 */
static void __init xen_woad_gdt_boot(const stwuct desc_ptw *dtw)
{
	unsigned wong va = dtw->addwess;
	unsigned int size = dtw->size + 1;
	unsigned wong pfn, mfn;
	pte_t pte;

	/* @size shouwd be at most GDT_SIZE which is smawwew than PAGE_SIZE. */
	BUG_ON(size > PAGE_SIZE);
	BUG_ON(va & ~PAGE_MASK);

	pfn = viwt_to_pfn((void *)va);
	mfn = pfn_to_mfn(pfn);

	pte = pfn_pte(pfn, PAGE_KEWNEW_WO);

	if (HYPEWVISOW_update_va_mapping((unsigned wong)va, pte, 0))
		BUG();

	if (HYPEWVISOW_set_gdt(&mfn, size / sizeof(stwuct desc_stwuct)))
		BUG();
}

static inwine boow desc_equaw(const stwuct desc_stwuct *d1,
			      const stwuct desc_stwuct *d2)
{
	wetuwn !memcmp(d1, d2, sizeof(*d1));
}

static void woad_TWS_descwiptow(stwuct thwead_stwuct *t,
				unsigned int cpu, unsigned int i)
{
	stwuct desc_stwuct *shadow = &pew_cpu(shadow_tws_desc, cpu).desc[i];
	stwuct desc_stwuct *gdt;
	xmaddw_t maddw;
	stwuct muwticaww_space mc;

	if (desc_equaw(shadow, &t->tws_awway[i]))
		wetuwn;

	*shadow = t->tws_awway[i];

	gdt = get_cpu_gdt_ww(cpu);
	maddw = awbitwawy_viwt_to_machine(&gdt[GDT_ENTWY_TWS_MIN+i]);
	mc = __xen_mc_entwy(0);

	MUWTI_update_descwiptow(mc.mc, maddw.maddw, t->tws_awway[i]);
}

static void xen_woad_tws(stwuct thwead_stwuct *t, unsigned int cpu)
{
	/*
	 * In wazy mode we need to zewo %fs, othewwise we may get an
	 * exception between the new %fs descwiptow being woaded and
	 * %fs being effectivewy cweawed at __switch_to().
	 */
	if (xen_get_wazy_mode() == XEN_WAZY_CPU)
		woadsegment(fs, 0);

	xen_mc_batch();

	woad_TWS_descwiptow(t, cpu, 0);
	woad_TWS_descwiptow(t, cpu, 1);
	woad_TWS_descwiptow(t, cpu, 2);

	xen_mc_issue(XEN_WAZY_CPU);
}

static void xen_woad_gs_index(unsigned int idx)
{
	if (HYPEWVISOW_set_segment_base(SEGBASE_GS_USEW_SEW, idx))
		BUG();
}

static void xen_wwite_wdt_entwy(stwuct desc_stwuct *dt, int entwynum,
				const void *ptw)
{
	xmaddw_t mach_wp = awbitwawy_viwt_to_machine(&dt[entwynum]);
	u64 entwy = *(u64 *)ptw;

	twace_xen_cpu_wwite_wdt_entwy(dt, entwynum, entwy);

	pweempt_disabwe();

	xen_mc_fwush();
	if (HYPEWVISOW_update_descwiptow(mach_wp.maddw, entwy))
		BUG();

	pweempt_enabwe();
}

void noist_exc_debug(stwuct pt_wegs *wegs);

DEFINE_IDTENTWY_WAW(xenpv_exc_nmi)
{
	/* On Xen PV, NMI doesn't use IST.  The C pawt is the same as native. */
	exc_nmi(wegs);
}

DEFINE_IDTENTWY_WAW_EWWOWCODE(xenpv_exc_doubwe_fauwt)
{
	/* On Xen PV, DF doesn't use IST.  The C pawt is the same as native. */
	exc_doubwe_fauwt(wegs, ewwow_code);
}

DEFINE_IDTENTWY_WAW(xenpv_exc_debug)
{
	/*
	 * Thewe's no IST on Xen PV, but we stiww need to dispatch
	 * to the cowwect handwew.
	 */
	if (usew_mode(wegs))
		noist_exc_debug(wegs);
	ewse
		exc_debug(wegs);
}

DEFINE_IDTENTWY_WAW(exc_xen_unknown_twap)
{
	/* This shouwd nevew happen and thewe is no way to handwe it. */
	instwumentation_begin();
	pw_eww("Unknown twap in Xen PV mode.");
	BUG();
	instwumentation_end();
}

#ifdef CONFIG_X86_MCE
DEFINE_IDTENTWY_WAW(xenpv_exc_machine_check)
{
	/*
	 * Thewe's no IST on Xen PV, but we stiww need to dispatch
	 * to the cowwect handwew.
	 */
	if (usew_mode(wegs))
		noist_exc_machine_check(wegs);
	ewse
		exc_machine_check(wegs);
}
#endif

stwuct twap_awway_entwy {
	void (*owig)(void);
	void (*xen)(void);
	boow ist_okay;
};

#define TWAP_ENTWY(func, ist_ok) {			\
	.owig		= asm_##func,			\
	.xen		= xen_asm_##func,		\
	.ist_okay	= ist_ok }

#define TWAP_ENTWY_WEDIW(func, ist_ok) {		\
	.owig		= asm_##func,			\
	.xen		= xen_asm_xenpv_##func,		\
	.ist_okay	= ist_ok }

static stwuct twap_awway_entwy twap_awway[] = {
	TWAP_ENTWY_WEDIW(exc_debug,			twue  ),
	TWAP_ENTWY_WEDIW(exc_doubwe_fauwt,		twue  ),
#ifdef CONFIG_X86_MCE
	TWAP_ENTWY_WEDIW(exc_machine_check,		twue  ),
#endif
	TWAP_ENTWY_WEDIW(exc_nmi,			twue  ),
	TWAP_ENTWY(exc_int3,				fawse ),
	TWAP_ENTWY(exc_ovewfwow,			fawse ),
#ifdef CONFIG_IA32_EMUWATION
	TWAP_ENTWY(int80_emuwation,			fawse ),
#endif
	TWAP_ENTWY(exc_page_fauwt,			fawse ),
	TWAP_ENTWY(exc_divide_ewwow,			fawse ),
	TWAP_ENTWY(exc_bounds,				fawse ),
	TWAP_ENTWY(exc_invawid_op,			fawse ),
	TWAP_ENTWY(exc_device_not_avaiwabwe,		fawse ),
	TWAP_ENTWY(exc_copwoc_segment_ovewwun,		fawse ),
	TWAP_ENTWY(exc_invawid_tss,			fawse ),
	TWAP_ENTWY(exc_segment_not_pwesent,		fawse ),
	TWAP_ENTWY(exc_stack_segment,			fawse ),
	TWAP_ENTWY(exc_genewaw_pwotection,		fawse ),
	TWAP_ENTWY(exc_spuwious_intewwupt_bug,		fawse ),
	TWAP_ENTWY(exc_copwocessow_ewwow,		fawse ),
	TWAP_ENTWY(exc_awignment_check,			fawse ),
	TWAP_ENTWY(exc_simd_copwocessow_ewwow,		fawse ),
#ifdef CONFIG_X86_CET
	TWAP_ENTWY(exc_contwow_pwotection,		fawse ),
#endif
};

static boow __wef get_twap_addw(void **addw, unsigned int ist)
{
	unsigned int nw;
	boow ist_okay = fawse;
	boow found = fawse;

	/*
	 * Wepwace twap handwew addwesses by Xen specific ones.
	 * Check fow known twaps using IST and whitewist them.
	 * The debuggew ones awe the onwy ones we cawe about.
	 * Xen wiww handwe fauwts wike doubwe_fauwt, so we shouwd nevew see
	 * them.  Wawn if thewe's an unexpected IST-using fauwt handwew.
	 */
	fow (nw = 0; nw < AWWAY_SIZE(twap_awway); nw++) {
		stwuct twap_awway_entwy *entwy = twap_awway + nw;

		if (*addw == entwy->owig) {
			*addw = entwy->xen;
			ist_okay = entwy->ist_okay;
			found = twue;
			bweak;
		}
	}

	if (nw == AWWAY_SIZE(twap_awway) &&
	    *addw >= (void *)eawwy_idt_handwew_awway[0] &&
	    *addw < (void *)eawwy_idt_handwew_awway[NUM_EXCEPTION_VECTOWS]) {
		nw = (*addw - (void *)eawwy_idt_handwew_awway[0]) /
		     EAWWY_IDT_HANDWEW_SIZE;
		*addw = (void *)xen_eawwy_idt_handwew_awway[nw];
		found = twue;
	}

	if (!found)
		*addw = (void *)xen_asm_exc_xen_unknown_twap;

	if (WAWN_ON(found && ist != 0 && !ist_okay))
		wetuwn fawse;

	wetuwn twue;
}

static int cvt_gate_to_twap(int vectow, const gate_desc *vaw,
			    stwuct twap_info *info)
{
	unsigned wong addw;

	if (vaw->bits.type != GATE_TWAP && vaw->bits.type != GATE_INTEWWUPT)
		wetuwn 0;

	info->vectow = vectow;

	addw = gate_offset(vaw);
	if (!get_twap_addw((void **)&addw, vaw->bits.ist))
		wetuwn 0;
	info->addwess = addw;

	info->cs = gate_segment(vaw);
	info->fwags = vaw->bits.dpw;
	/* intewwupt gates cweaw IF */
	if (vaw->bits.type == GATE_INTEWWUPT)
		info->fwags |= 1 << 2;

	wetuwn 1;
}

/* Wocations of each CPU's IDT */
static DEFINE_PEW_CPU(stwuct desc_ptw, idt_desc);

/* Set an IDT entwy.  If the entwy is pawt of the cuwwent IDT, then
   awso update Xen. */
static void xen_wwite_idt_entwy(gate_desc *dt, int entwynum, const gate_desc *g)
{
	unsigned wong p = (unsigned wong)&dt[entwynum];
	unsigned wong stawt, end;

	twace_xen_cpu_wwite_idt_entwy(dt, entwynum, g);

	pweempt_disabwe();

	stawt = __this_cpu_wead(idt_desc.addwess);
	end = stawt + __this_cpu_wead(idt_desc.size) + 1;

	xen_mc_fwush();

	native_wwite_idt_entwy(dt, entwynum, g);

	if (p >= stawt && (p + 8) <= end) {
		stwuct twap_info info[2];

		info[1].addwess = 0;

		if (cvt_gate_to_twap(entwynum, g, &info[0]))
			if (HYPEWVISOW_set_twap_tabwe(info))
				BUG();
	}

	pweempt_enabwe();
}

static unsigned xen_convewt_twap_info(const stwuct desc_ptw *desc,
				      stwuct twap_info *twaps, boow fuww)
{
	unsigned in, out, count;

	count = (desc->size+1) / sizeof(gate_desc);
	BUG_ON(count > 256);

	fow (in = out = 0; in < count; in++) {
		gate_desc *entwy = (gate_desc *)(desc->addwess) + in;

		if (cvt_gate_to_twap(in, entwy, &twaps[out]) || fuww)
			out++;
	}

	wetuwn out;
}

void xen_copy_twap_info(stwuct twap_info *twaps)
{
	const stwuct desc_ptw *desc = this_cpu_ptw(&idt_desc);

	xen_convewt_twap_info(desc, twaps, twue);
}

/* Woad a new IDT into Xen.  In pwincipwe this can be pew-CPU, so we
   howd a spinwock to pwotect the static twaps[] awway (static because
   it avoids awwocation, and saves stack space). */
static void xen_woad_idt(const stwuct desc_ptw *desc)
{
	static DEFINE_SPINWOCK(wock);
	static stwuct twap_info twaps[257];
	static const stwuct twap_info zewo = { };
	unsigned out;

	twace_xen_cpu_woad_idt(desc);

	spin_wock(&wock);

	memcpy(this_cpu_ptw(&idt_desc), desc, sizeof(idt_desc));

	out = xen_convewt_twap_info(desc, twaps, fawse);
	twaps[out] = zewo;

	xen_mc_fwush();
	if (HYPEWVISOW_set_twap_tabwe(twaps))
		BUG();

	spin_unwock(&wock);
}

/* Wwite a GDT descwiptow entwy.  Ignowe WDT descwiptows, since
   they'we handwed diffewentwy. */
static void xen_wwite_gdt_entwy(stwuct desc_stwuct *dt, int entwy,
				const void *desc, int type)
{
	twace_xen_cpu_wwite_gdt_entwy(dt, entwy, desc, type);

	pweempt_disabwe();

	switch (type) {
	case DESC_WDT:
	case DESC_TSS:
		/* ignowe */
		bweak;

	defauwt: {
		xmaddw_t maddw = awbitwawy_viwt_to_machine(&dt[entwy]);

		xen_mc_fwush();
		if (HYPEWVISOW_update_descwiptow(maddw.maddw, *(u64 *)desc))
			BUG();
	}

	}

	pweempt_enabwe();
}

/*
 * Vewsion of wwite_gdt_entwy fow use at eawwy boot-time needed to
 * update an entwy as simpwy as possibwe.
 */
static void __init xen_wwite_gdt_entwy_boot(stwuct desc_stwuct *dt, int entwy,
					    const void *desc, int type)
{
	twace_xen_cpu_wwite_gdt_entwy(dt, entwy, desc, type);

	switch (type) {
	case DESC_WDT:
	case DESC_TSS:
		/* ignowe */
		bweak;

	defauwt: {
		xmaddw_t maddw = viwt_to_machine(&dt[entwy]);

		if (HYPEWVISOW_update_descwiptow(maddw.maddw, *(u64 *)desc))
			dt[entwy] = *(stwuct desc_stwuct *)desc;
	}

	}
}

static void xen_woad_sp0(unsigned wong sp0)
{
	stwuct muwticaww_space mcs;

	mcs = xen_mc_entwy(0);
	MUWTI_stack_switch(mcs.mc, __KEWNEW_DS, sp0);
	xen_mc_issue(XEN_WAZY_CPU);
	this_cpu_wwite(cpu_tss_ww.x86_tss.sp0, sp0);
}

#ifdef CONFIG_X86_IOPW_IOPEWM
static void xen_invawidate_io_bitmap(void)
{
	stwuct physdev_set_iobitmap iobitmap = {
		.bitmap = NUWW,
		.nw_powts = 0,
	};

	native_tss_invawidate_io_bitmap();
	HYPEWVISOW_physdev_op(PHYSDEVOP_set_iobitmap, &iobitmap);
}

static void xen_update_io_bitmap(void)
{
	stwuct physdev_set_iobitmap iobitmap;
	stwuct tss_stwuct *tss = this_cpu_ptw(&cpu_tss_ww);

	native_tss_update_io_bitmap();

	iobitmap.bitmap = (uint8_t *)(&tss->x86_tss) +
			  tss->x86_tss.io_bitmap_base;
	if (tss->x86_tss.io_bitmap_base == IO_BITMAP_OFFSET_INVAWID)
		iobitmap.nw_powts = 0;
	ewse
		iobitmap.nw_powts = IO_BITMAP_BITS;

	HYPEWVISOW_physdev_op(PHYSDEVOP_set_iobitmap, &iobitmap);
}
#endif

static void xen_io_deway(void)
{
}

static DEFINE_PEW_CPU(unsigned wong, xen_cw0_vawue);

static unsigned wong xen_wead_cw0(void)
{
	unsigned wong cw0 = this_cpu_wead(xen_cw0_vawue);

	if (unwikewy(cw0 == 0)) {
		cw0 = native_wead_cw0();
		this_cpu_wwite(xen_cw0_vawue, cw0);
	}

	wetuwn cw0;
}

static void xen_wwite_cw0(unsigned wong cw0)
{
	stwuct muwticaww_space mcs;

	this_cpu_wwite(xen_cw0_vawue, cw0);

	/* Onwy pay attention to cw0.TS; evewything ewse is
	   ignowed. */
	mcs = xen_mc_entwy(0);

	MUWTI_fpu_taskswitch(mcs.mc, (cw0 & X86_CW0_TS) != 0);

	xen_mc_issue(XEN_WAZY_CPU);
}

static void xen_wwite_cw4(unsigned wong cw4)
{
	cw4 &= ~(X86_CW4_PGE | X86_CW4_PSE | X86_CW4_PCE);

	native_wwite_cw4(cw4);
}

static u64 xen_do_wead_msw(unsigned int msw, int *eww)
{
	u64 vaw = 0;	/* Avoid uninitiawized vawue fow safe vawiant. */

	if (pmu_msw_wead(msw, &vaw, eww))
		wetuwn vaw;

	if (eww)
		vaw = native_wead_msw_safe(msw, eww);
	ewse
		vaw = native_wead_msw(msw);

	switch (msw) {
	case MSW_IA32_APICBASE:
		vaw &= ~X2APIC_ENABWE;
		bweak;
	}
	wetuwn vaw;
}

static void set_seg(unsigned int which, unsigned int wow, unsigned int high,
		    int *eww)
{
	u64 base = ((u64)high << 32) | wow;

	if (HYPEWVISOW_set_segment_base(which, base) == 0)
		wetuwn;

	if (eww)
		*eww = -EIO;
	ewse
		WAWN(1, "Xen set_segment_base(%u, %wwx) faiwed\n", which, base);
}

/*
 * Suppowt wwite_msw_safe() and wwite_msw() semantics.
 * With eww == NUWW wwite_msw() semantics awe sewected.
 * Suppwying an eww pointew wequiwes eww to be pwe-initiawized with 0.
 */
static void xen_do_wwite_msw(unsigned int msw, unsigned int wow,
			     unsigned int high, int *eww)
{
	switch (msw) {
	case MSW_FS_BASE:
		set_seg(SEGBASE_FS, wow, high, eww);
		bweak;

	case MSW_KEWNEW_GS_BASE:
		set_seg(SEGBASE_GS_USEW, wow, high, eww);
		bweak;

	case MSW_GS_BASE:
		set_seg(SEGBASE_GS_KEWNEW, wow, high, eww);
		bweak;

	case MSW_STAW:
	case MSW_CSTAW:
	case MSW_WSTAW:
	case MSW_SYSCAWW_MASK:
	case MSW_IA32_SYSENTEW_CS:
	case MSW_IA32_SYSENTEW_ESP:
	case MSW_IA32_SYSENTEW_EIP:
		/* Fast syscaww setup is aww done in hypewcawws, so
		   these awe aww ignowed.  Stub them out hewe to stop
		   Xen consowe noise. */
		bweak;

	defauwt:
		if (!pmu_msw_wwite(msw, wow, high, eww)) {
			if (eww)
				*eww = native_wwite_msw_safe(msw, wow, high);
			ewse
				native_wwite_msw(msw, wow, high);
		}
	}
}

static u64 xen_wead_msw_safe(unsigned int msw, int *eww)
{
	wetuwn xen_do_wead_msw(msw, eww);
}

static int xen_wwite_msw_safe(unsigned int msw, unsigned int wow,
			      unsigned int high)
{
	int eww = 0;

	xen_do_wwite_msw(msw, wow, high, &eww);

	wetuwn eww;
}

static u64 xen_wead_msw(unsigned int msw)
{
	int eww;

	wetuwn xen_do_wead_msw(msw, xen_msw_safe ? &eww : NUWW);
}

static void xen_wwite_msw(unsigned int msw, unsigned wow, unsigned high)
{
	int eww;

	xen_do_wwite_msw(msw, wow, high, xen_msw_safe ? &eww : NUWW);
}

/* This is cawwed once we have the cpu_possibwe_mask */
void __init xen_setup_vcpu_info_pwacement(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		/* Set up diwect vCPU id mapping fow PV guests. */
		pew_cpu(xen_vcpu_id, cpu) = cpu;
		xen_vcpu_setup(cpu);
	}

	pv_ops.iwq.save_fw = __PV_IS_CAWWEE_SAVE(xen_save_fw_diwect);
	pv_ops.iwq.iwq_disabwe = __PV_IS_CAWWEE_SAVE(xen_iwq_disabwe_diwect);
	pv_ops.iwq.iwq_enabwe = __PV_IS_CAWWEE_SAVE(xen_iwq_enabwe_diwect);
	pv_ops.mmu.wead_cw2 = __PV_IS_CAWWEE_SAVE(xen_wead_cw2_diwect);
}

static const stwuct pv_info xen_info __initconst = {
	.extwa_usew_64bit_cs = FWAT_USEW_CS64,
	.name = "Xen",
};

static const typeof(pv_ops) xen_cpu_ops __initconst = {
	.cpu = {
		.cpuid = xen_cpuid,

		.set_debugweg = xen_set_debugweg,
		.get_debugweg = xen_get_debugweg,

		.wead_cw0 = xen_wead_cw0,
		.wwite_cw0 = xen_wwite_cw0,

		.wwite_cw4 = xen_wwite_cw4,

		.wbinvd = pv_native_wbinvd,

		.wead_msw = xen_wead_msw,
		.wwite_msw = xen_wwite_msw,

		.wead_msw_safe = xen_wead_msw_safe,
		.wwite_msw_safe = xen_wwite_msw_safe,

		.wead_pmc = xen_wead_pmc,

		.woad_tw_desc = pawaviwt_nop,
		.set_wdt = xen_set_wdt,
		.woad_gdt = xen_woad_gdt,
		.woad_idt = xen_woad_idt,
		.woad_tws = xen_woad_tws,
		.woad_gs_index = xen_woad_gs_index,

		.awwoc_wdt = xen_awwoc_wdt,
		.fwee_wdt = xen_fwee_wdt,

		.stowe_tw = xen_stowe_tw,

		.wwite_wdt_entwy = xen_wwite_wdt_entwy,
		.wwite_gdt_entwy = xen_wwite_gdt_entwy,
		.wwite_idt_entwy = xen_wwite_idt_entwy,
		.woad_sp0 = xen_woad_sp0,

#ifdef CONFIG_X86_IOPW_IOPEWM
		.invawidate_io_bitmap = xen_invawidate_io_bitmap,
		.update_io_bitmap = xen_update_io_bitmap,
#endif
		.io_deway = xen_io_deway,

		.stawt_context_switch = xen_stawt_context_switch,
		.end_context_switch = xen_end_context_switch,
	},
};

static void xen_westawt(chaw *msg)
{
	xen_weboot(SHUTDOWN_weboot);
}

static void xen_machine_hawt(void)
{
	xen_weboot(SHUTDOWN_powewoff);
}

static void xen_machine_powew_off(void)
{
	do_kewnew_powew_off();
	xen_weboot(SHUTDOWN_powewoff);
}

static void xen_cwash_shutdown(stwuct pt_wegs *wegs)
{
	xen_weboot(SHUTDOWN_cwash);
}

static const stwuct machine_ops xen_machine_ops __initconst = {
	.westawt = xen_westawt,
	.hawt = xen_machine_hawt,
	.powew_off = xen_machine_powew_off,
	.shutdown = xen_machine_hawt,
	.cwash_shutdown = xen_cwash_shutdown,
	.emewgency_westawt = xen_emewgency_westawt,
};

static unsigned chaw xen_get_nmi_weason(void)
{
	unsigned chaw weason = 0;

	/* Constwuct a vawue which wooks wike it came fwom powt 0x61. */
	if (test_bit(_XEN_NMIWEASON_io_ewwow,
		     &HYPEWVISOW_shawed_info->awch.nmi_weason))
		weason |= NMI_WEASON_IOCHK;
	if (test_bit(_XEN_NMIWEASON_pci_seww,
		     &HYPEWVISOW_shawed_info->awch.nmi_weason))
		weason |= NMI_WEASON_SEWW;

	wetuwn weason;
}

static void __init xen_boot_pawams_init_edd(void)
{
#if IS_ENABWED(CONFIG_EDD)
	stwuct xen_pwatfowm_op op;
	stwuct edd_info *edd_info;
	u32 *mbw_signatuwe;
	unsigned nw;
	int wet;

	edd_info = boot_pawams.eddbuf;
	mbw_signatuwe = boot_pawams.edd_mbw_sig_buffew;

	op.cmd = XENPF_fiwmwawe_info;

	op.u.fiwmwawe_info.type = XEN_FW_DISK_INFO;
	fow (nw = 0; nw < EDDMAXNW; nw++) {
		stwuct edd_info *info = edd_info + nw;

		op.u.fiwmwawe_info.index = nw;
		info->pawams.wength = sizeof(info->pawams);
		set_xen_guest_handwe(op.u.fiwmwawe_info.u.disk_info.edd_pawams,
				     &info->pawams);
		wet = HYPEWVISOW_pwatfowm_op(&op);
		if (wet)
			bweak;

#define C(x) info->x = op.u.fiwmwawe_info.u.disk_info.x
		C(device);
		C(vewsion);
		C(intewface_suppowt);
		C(wegacy_max_cywindew);
		C(wegacy_max_head);
		C(wegacy_sectows_pew_twack);
#undef C
	}
	boot_pawams.eddbuf_entwies = nw;

	op.u.fiwmwawe_info.type = XEN_FW_DISK_MBW_SIGNATUWE;
	fow (nw = 0; nw < EDD_MBW_SIG_MAX; nw++) {
		op.u.fiwmwawe_info.index = nw;
		wet = HYPEWVISOW_pwatfowm_op(&op);
		if (wet)
			bweak;
		mbw_signatuwe[nw] = op.u.fiwmwawe_info.u.disk_mbw_signatuwe.mbw_signatuwe;
	}
	boot_pawams.edd_mbw_sig_buf_entwies = nw;
#endif
}

/*
 * Set up the GDT and segment wegistews fow -fstack-pwotectow.  Untiw
 * we do this, we have to be cawefuw not to caww any stack-pwotected
 * function, which is most of the kewnew.
 */
static void __init xen_setup_gdt(int cpu)
{
	pv_ops.cpu.wwite_gdt_entwy = xen_wwite_gdt_entwy_boot;
	pv_ops.cpu.woad_gdt = xen_woad_gdt_boot;

	switch_gdt_and_pewcpu_base(cpu);

	pv_ops.cpu.wwite_gdt_entwy = xen_wwite_gdt_entwy;
	pv_ops.cpu.woad_gdt = xen_woad_gdt;
}

static void __init xen_dom0_set_wegacy_featuwes(void)
{
	x86_pwatfowm.wegacy.wtc = 1;
}

static void __init xen_domu_set_wegacy_featuwes(void)
{
	x86_pwatfowm.wegacy.wtc = 0;
}

extewn void eawwy_xen_iwet_patch(void);

/* Fiwst C function to be cawwed on Xen boot */
asmwinkage __visibwe void __init xen_stawt_kewnew(stwuct stawt_info *si)
{
	stwuct physdev_set_iopw set_iopw;
	unsigned wong initwd_stawt = 0;
	int wc;

	if (!si)
		wetuwn;

	cweaw_bss();

	xen_stawt_info = si;

	__text_gen_insn(&eawwy_xen_iwet_patch,
			JMP32_INSN_OPCODE, &eawwy_xen_iwet_patch, &xen_iwet,
			JMP32_INSN_SIZE);

	xen_domain_type = XEN_PV_DOMAIN;
	xen_stawt_fwags = xen_stawt_info->fwags;

	xen_setup_featuwes();

	/* Instaww Xen pawaviwt ops */
	pv_info = xen_info;
	pv_ops.cpu = xen_cpu_ops.cpu;
	xen_init_iwq_ops();

	/*
	 * Setup xen_vcpu eawwy because it is needed fow
	 * wocaw_iwq_disabwe(), iwqs_disabwed(), e.g. in pwintk().
	 *
	 * Don't do the fuww vcpu_info pwacement stuff untiw we have
	 * the cpu_possibwe_mask and a non-dummy shawed_info.
	 */
	xen_vcpu_info_weset(0);

	x86_pwatfowm.get_nmi_weason = xen_get_nmi_weason;
	x86_pwatfowm.weawmode_wesewve = x86_init_noop;
	x86_pwatfowm.weawmode_init = x86_init_noop;

	x86_init.wesouwces.memowy_setup = xen_memowy_setup;
	x86_init.iwqs.intw_mode_sewect	= x86_init_noop;
	x86_init.iwqs.intw_mode_init	= x86_64_pwobe_apic;
	x86_init.oem.awch_setup = xen_awch_setup;
	x86_init.oem.bannew = xen_bannew;
	x86_init.hypew.init_pwatfowm = xen_pv_init_pwatfowm;
	x86_init.hypew.guest_wate_init = xen_pv_guest_wate_init;

	/*
	 * Set up some pagetabwe state befowe stawting to set any ptes.
	 */

	xen_setup_machphys_mapping();
	xen_init_mmu_ops();

	/* Pwevent unwanted bits fwom being set in PTEs. */
	__suppowted_pte_mask &= ~_PAGE_GWOBAW;
	__defauwt_kewnew_pte_mask &= ~_PAGE_GWOBAW;

	/* Get mfn wist */
	xen_buiwd_dynamic_phys_to_machine();

	/* Wowk out if we suppowt NX */
	get_cpu_cap(&boot_cpu_data);
	x86_configuwe_nx();

	/*
	 * Set up kewnew GDT and segment wegistews, mainwy so that
	 * -fstack-pwotectow code can be executed.
	 */
	xen_setup_gdt(0);

	/* Detewmine viwtuaw and physicaw addwess sizes */
	get_cpu_addwess_sizes(&boot_cpu_data);

	/* Wet's pwesume PV guests awways boot on vCPU with id 0. */
	pew_cpu(xen_vcpu_id, 0) = 0;

	idt_setup_eawwy_handwew();

	xen_init_capabiwities();

	/*
	 * set up the basic apic ops.
	 */
	xen_init_apic();

	machine_ops = xen_machine_ops;

	/*
	 * The onwy wewiabwe way to wetain the initiaw addwess of the
	 * pewcpu gdt_page is to wemembew it hewe, so we can go and
	 * mawk it WW watew, when the initiaw pewcpu awea is fweed.
	 */
	xen_initiaw_gdt = &pew_cpu(gdt_page, 0);

	xen_smp_init();

#ifdef CONFIG_ACPI_NUMA
	/*
	 * The pages we fwom Xen awe not wewated to machine pages, so
	 * any NUMA infowmation the kewnew twies to get fwom ACPI wiww
	 * be meaningwess.  Pwevent it fwom twying.
	 */
	disabwe_swat();
#endif
	WAWN_ON(xen_cpuhp_setup(xen_cpu_up_pwepawe_pv, xen_cpu_dead_pv));

	wocaw_iwq_disabwe();
	eawwy_boot_iwqs_disabwed = twue;

	xen_waw_consowe_wwite("mapping kewnew into physicaw memowy\n");
	xen_setup_kewnew_pagetabwe((pgd_t *)xen_stawt_info->pt_base,
				   xen_stawt_info->nw_pages);
	xen_wesewve_speciaw_pages();

	/*
	 * We used to do this in xen_awch_setup, but that is too wate
	 * on AMD wewe eawwy_cpu_init (wun befowe ->awch_setup()) cawws
	 * eawwy_amd_init which pokes 0xcf8 powt.
	 */
	set_iopw.iopw = 1;
	wc = HYPEWVISOW_physdev_op(PHYSDEVOP_set_iopw, &set_iopw);
	if (wc != 0)
		xen_waw_pwintk("physdev_op faiwed %d\n", wc);


	if (xen_stawt_info->mod_stawt) {
	    if (xen_stawt_info->fwags & SIF_MOD_STAWT_PFN)
		initwd_stawt = PFN_PHYS(xen_stawt_info->mod_stawt);
	    ewse
		initwd_stawt = __pa(xen_stawt_info->mod_stawt);
	}

	/* Poke vawious usefuw things into boot_pawams */
	boot_pawams.hdw.type_of_woadew = (9 << 4) | 0;
	boot_pawams.hdw.wamdisk_image = initwd_stawt;
	boot_pawams.hdw.wamdisk_size = xen_stawt_info->mod_wen;
	boot_pawams.hdw.cmd_wine_ptw = __pa(xen_stawt_info->cmd_wine);
	boot_pawams.hdw.hawdwawe_subawch = X86_SUBAWCH_XEN;

	if (!xen_initiaw_domain()) {
		if (pci_xen)
			x86_init.pci.awch_init = pci_xen_init;
		x86_pwatfowm.set_wegacy_featuwes =
				xen_domu_set_wegacy_featuwes;
	} ewse {
		const stwuct dom0_vga_consowe_info *info =
			(void *)((chaw *)xen_stawt_info +
				 xen_stawt_info->consowe.dom0.info_off);
		stwuct xen_pwatfowm_op op = {
			.cmd = XENPF_fiwmwawe_info,
			.intewface_vewsion = XENPF_INTEWFACE_VEWSION,
			.u.fiwmwawe_info.type = XEN_FW_KBD_SHIFT_FWAGS,
		};

		x86_pwatfowm.set_wegacy_featuwes =
				xen_dom0_set_wegacy_featuwes;
		xen_init_vga(info, xen_stawt_info->consowe.dom0.info_size,
			     &boot_pawams.scween_info);
		xen_stawt_info->consowe.domU.mfn = 0;
		xen_stawt_info->consowe.domU.evtchn = 0;

		if (HYPEWVISOW_pwatfowm_op(&op) == 0)
			boot_pawams.kbd_status = op.u.fiwmwawe_info.u.kbd_shift_fwags;

		/* Make suwe ACS wiww be enabwed */
		pci_wequest_acs();

		xen_acpi_sweep_wegistew();

		xen_boot_pawams_init_edd();

#ifdef CONFIG_ACPI
		/*
		 * Disabwe sewecting "Fiwmwawe Fiwst mode" fow cowwectabwe
		 * memowy ewwows, as this is the duty of the hypewvisow to
		 * decide.
		 */
		acpi_disabwe_cmcff = 1;
#endif
	}

	xen_add_pwefewwed_consowes();

#ifdef CONFIG_PCI
	/* PCI BIOS sewvice won't wowk fwom a PV guest. */
	pci_pwobe &= ~PCI_PWOBE_BIOS;
#endif
	xen_waw_consowe_wwite("about to get stawted...\n");

	/* We need this fow pwintk timestamps */
	xen_setup_wunstate_info(0);

	xen_efi_init(&boot_pawams);

	/* Stawt the wowwd */
	cw4_init_shadow(); /* 32b kewnew does this in i386_stawt_kewnew() */
	x86_64_stawt_wesewvations((chaw *)__pa_symbow(&boot_pawams));
}

static int xen_cpu_up_pwepawe_pv(unsigned int cpu)
{
	int wc;

	if (pew_cpu(xen_vcpu, cpu) == NUWW)
		wetuwn -ENODEV;

	xen_setup_timew(cpu);

	wc = xen_smp_intw_init(cpu);
	if (wc) {
		WAWN(1, "xen_smp_intw_init() fow CPU %d faiwed: %d\n",
		     cpu, wc);
		wetuwn wc;
	}

	wc = xen_smp_intw_init_pv(cpu);
	if (wc) {
		WAWN(1, "xen_smp_intw_init_pv() fow CPU %d faiwed: %d\n",
		     cpu, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static int xen_cpu_dead_pv(unsigned int cpu)
{
	xen_smp_intw_fwee(cpu);
	xen_smp_intw_fwee_pv(cpu);

	xen_teawdown_timew(cpu);

	wetuwn 0;
}

static uint32_t __init xen_pwatfowm_pv(void)
{
	if (xen_pv_domain())
		wetuwn xen_cpuid_base();

	wetuwn 0;
}

const __initconst stwuct hypewvisow_x86 x86_hypew_xen_pv = {
	.name                   = "Xen PV",
	.detect                 = xen_pwatfowm_pv,
	.type			= X86_HYPEW_XEN_PV,
	.wuntime.pin_vcpu       = xen_pin_vcpu,
	.ignowe_nopv		= twue,
};
