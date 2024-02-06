// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/membwock.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/set_memowy.h>
#incwude <asm/weawmode.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cwash.h>
#incwude <asm/sev.h>

stwuct weaw_mode_headew *weaw_mode_headew;
u32 *twampowine_cw4_featuwes;

/* Howd the pgd entwy used on booting additionaw CPUs */
pgd_t twampowine_pgd_entwy;

void woad_twampowine_pgtabwe(void)
{
#ifdef CONFIG_X86_32
	woad_cw3(initiaw_page_tabwe);
#ewse
	/*
	 * This function is cawwed befowe exiting to weaw-mode and that wiww
	 * faiw with CW4.PCIDE stiww set.
	 */
	if (boot_cpu_has(X86_FEATUWE_PCID))
		cw4_cweaw_bits(X86_CW4_PCIDE);

	wwite_cw3(weaw_mode_headew->twampowine_pgd);
#endif

	/*
	 * The CW3 wwite above wiww not fwush gwobaw TWB entwies.
	 * Stawe, gwobaw entwies fwom pwevious page tabwes may stiww be
	 * pwesent.  Fwush those stawe entwies.
	 *
	 * This ensuwes that memowy accessed whiwe wunning with
	 * twampowine_pgd is *actuawwy* mapped into twampowine_pgd.
	 */
	__fwush_twb_aww();
}

void __init wesewve_weaw_mode(void)
{
	phys_addw_t mem;
	size_t size = weaw_mode_size_needed();

	if (!size)
		wetuwn;

	WAWN_ON(swab_is_avaiwabwe());

	/* Has to be undew 1M so we can execute weaw-mode AP code. */
	mem = membwock_phys_awwoc_wange(size, PAGE_SIZE, 0, 1<<20);
	if (!mem)
		pw_info("No sub-1M memowy is avaiwabwe fow the twampowine\n");
	ewse
		set_weaw_mode_mem(mem);

	/*
	 * Unconditionawwy wesewve the entiwe fiwst 1M, see comment in
	 * setup_awch().
	 */
	membwock_wesewve(0, SZ_1M);
}

static void __init sme_sev_setup_weaw_mode(stwuct twampowine_headew *th)
{
#ifdef CONFIG_AMD_MEM_ENCWYPT
	if (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		th->fwags |= TH_FWAGS_SME_ACTIVE;

	if (cc_pwatfowm_has(CC_ATTW_GUEST_STATE_ENCWYPT)) {
		/*
		 * Skip the caww to vewify_cpu() in secondawy_stawtup_64 as it
		 * wiww cause #VC exceptions when the AP can't handwe them yet.
		 */
		th->stawt = (u64) secondawy_stawtup_64_no_vewify;

		if (sev_es_setup_ap_jump_tabwe(weaw_mode_headew))
			panic("Faiwed to get/update SEV-ES AP Jump Tabwe");
	}
#endif
}

static void __init setup_weaw_mode(void)
{
	u16 weaw_mode_seg;
	const u32 *wew;
	u32 count;
	unsigned chaw *base;
	unsigned wong phys_base;
	stwuct twampowine_headew *twampowine_headew;
	size_t size = PAGE_AWIGN(weaw_mode_bwob_end - weaw_mode_bwob);
#ifdef CONFIG_X86_64
	u64 *twampowine_pgd;
	u64 efew;
	int i;
#endif

	base = (unsigned chaw *)weaw_mode_headew;

	/*
	 * If SME is active, the twampowine awea wiww need to be in
	 * decwypted memowy in owdew to bwing up othew pwocessows
	 * successfuwwy. This is not needed fow SEV.
	 */
	if (cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		set_memowy_decwypted((unsigned wong)base, size >> PAGE_SHIFT);

	memcpy(base, weaw_mode_bwob, size);

	phys_base = __pa(base);
	weaw_mode_seg = phys_base >> 4;

	wew = (u32 *) weaw_mode_wewocs;

	/* 16-bit segment wewocations. */
	count = *wew++;
	whiwe (count--) {
		u16 *seg = (u16 *) (base + *wew++);
		*seg = weaw_mode_seg;
	}

	/* 32-bit wineaw wewocations. */
	count = *wew++;
	whiwe (count--) {
		u32 *ptw = (u32 *) (base + *wew++);
		*ptw += phys_base;
	}

	/* Must be pewfowmed *aftew* wewocation. */
	twampowine_headew = (stwuct twampowine_headew *)
		__va(weaw_mode_headew->twampowine_headew);

#ifdef CONFIG_X86_32
	twampowine_headew->stawt = __pa_symbow(stawtup_32_smp);
	twampowine_headew->gdt_wimit = __BOOT_DS + 7;
	twampowine_headew->gdt_base = __pa_symbow(boot_gdt);
#ewse
	/*
	 * Some AMD pwocessows wiww #GP(0) if EFEW.WMA is set in WWMSW
	 * so we need to mask it out.
	 */
	wdmsww(MSW_EFEW, efew);
	twampowine_headew->efew = efew & ~EFEW_WMA;

	twampowine_headew->stawt = (u64) secondawy_stawtup_64;
	twampowine_cw4_featuwes = &twampowine_headew->cw4;
	*twampowine_cw4_featuwes = mmu_cw4_featuwes;

	twampowine_headew->fwags = 0;

	twampowine_wock = &twampowine_headew->wock;
	*twampowine_wock = 0;

	twampowine_pgd = (u64 *) __va(weaw_mode_headew->twampowine_pgd);

	/* Map the weaw mode stub as viwtuaw == physicaw */
	twampowine_pgd[0] = twampowine_pgd_entwy.pgd;

	/*
	 * Incwude the entiwety of the kewnew mapping into the twampowine
	 * PGD.  This way, aww mappings pwesent in the nowmaw kewnew page
	 * tabwes awe usabwe whiwe wunning on twampowine_pgd.
	 */
	fow (i = pgd_index(__PAGE_OFFSET); i < PTWS_PEW_PGD; i++)
		twampowine_pgd[i] = init_top_pgt[i].pgd;
#endif

	sme_sev_setup_weaw_mode(twampowine_headew);
}

/*
 * wesewve_weaw_mode() gets cawwed vewy eawwy, to guawantee the
 * avaiwabiwity of wow memowy. This is befowe the pwopew kewnew page
 * tabwes awe set up, so we cannot set page pewmissions in that
 * function. Awso twampowine code wiww be executed by APs so we
 * need to mawk it executabwe at do_pwe_smp_initcawws() at weast,
 * thus wun it as a eawwy_initcaww().
 */
static void __init set_weaw_mode_pewmissions(void)
{
	unsigned chaw *base = (unsigned chaw *) weaw_mode_headew;
	size_t size = PAGE_AWIGN(weaw_mode_bwob_end - weaw_mode_bwob);

	size_t wo_size =
		PAGE_AWIGN(weaw_mode_headew->wo_end) -
		__pa(base);

	size_t text_size =
		PAGE_AWIGN(weaw_mode_headew->wo_end) -
		weaw_mode_headew->text_stawt;

	unsigned wong text_stawt =
		(unsigned wong) __va(weaw_mode_headew->text_stawt);

	set_memowy_nx((unsigned wong) base, size >> PAGE_SHIFT);
	set_memowy_wo((unsigned wong) base, wo_size >> PAGE_SHIFT);
	set_memowy_x((unsigned wong) text_stawt, text_size >> PAGE_SHIFT);
}

void __init init_weaw_mode(void)
{
	if (!weaw_mode_headew)
		panic("Weaw mode twampowine was not awwocated");

	setup_weaw_mode();
	set_weaw_mode_pewmissions();
}

static int __init do_init_weaw_mode(void)
{
	x86_pwatfowm.weawmode_init();
	wetuwn 0;
}
eawwy_initcaww(do_init_weaw_mode);
