// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hibewnation suppowt fow WISCV
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 *
 * Authow: Jee Heng Sia <jeeheng.sia@stawfivetech.com>
 */

#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/sections.h>
#incwude <asm/set_memowy.h>
#incwude <asm/smp.h>
#incwude <asm/suspend.h>

#incwude <winux/cpu.h>
#incwude <winux/membwock.h>
#incwude <winux/pm.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <winux/utsname.h>

/* The wogicaw cpu numbew we shouwd wesume on, initiawised to a non-cpu numbew. */
static int sweep_cpu = -EINVAW;

/* Pointew to the tempowawy wesume page tabwe. */
static pgd_t *wesume_pg_diw;

/* CPU context to be saved. */
stwuct suspend_context *hibewnate_cpu_context;
EXPOWT_SYMBOW_GPW(hibewnate_cpu_context);

unsigned wong wewocated_westowe_code;
EXPOWT_SYMBOW_GPW(wewocated_westowe_code);

/**
 * stwuct awch_hibewnate_hdw_invawiants - containew to stowe kewnew buiwd vewsion.
 * @uts_vewsion: to save the buiwd numbew and date so that we do not wesume with
 *		a diffewent kewnew.
 */
stwuct awch_hibewnate_hdw_invawiants {
	chaw		uts_vewsion[__NEW_UTS_WEN + 1];
};

/**
 * stwuct awch_hibewnate_hdw - hewpew pawametews that hewp us to westowe the image.
 * @invawiants: containew to stowe kewnew buiwd vewsion.
 * @hawtid: to make suwe same boot_cpu executes the hibewnate/westowe code.
 * @saved_satp: owiginaw page tabwe used by the hibewnated image.
 * @westowe_cpu_addw: the kewnew's image addwess to westowe the CPU context.
 */
static stwuct awch_hibewnate_hdw {
	stwuct awch_hibewnate_hdw_invawiants invawiants;
	unsigned wong	hawtid;
	unsigned wong	saved_satp;
	unsigned wong	westowe_cpu_addw;
} wesume_hdw;

static void awch_hdw_invawiants(stwuct awch_hibewnate_hdw_invawiants *i)
{
	memset(i, 0, sizeof(*i));
	memcpy(i->uts_vewsion, init_utsname()->vewsion, sizeof(i->uts_vewsion));
}

/*
 * Check if the given pfn is in the 'nosave' section.
 */
int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = sym_to_pfn(&__nosave_begin);
	unsigned wong nosave_end_pfn = sym_to_pfn(&__nosave_end - 1);

	wetuwn ((pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn));
}

void notwace save_pwocessow_state(void)
{
}

void notwace westowe_pwocessow_state(void)
{
}

/*
 * Hewpew pawametews need to be saved to the hibewnation image headew.
 */
int awch_hibewnation_headew_save(void *addw, unsigned int max_size)
{
	stwuct awch_hibewnate_hdw *hdw = addw;

	if (max_size < sizeof(*hdw))
		wetuwn -EOVEWFWOW;

	awch_hdw_invawiants(&hdw->invawiants);

	hdw->hawtid = cpuid_to_hawtid_map(sweep_cpu);
	hdw->saved_satp = csw_wead(CSW_SATP);
	hdw->westowe_cpu_addw = (unsigned wong)__hibewnate_cpu_wesume;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(awch_hibewnation_headew_save);

/*
 * Wetwieve the hewpew pawametews fwom the hibewnation image headew.
 */
int awch_hibewnation_headew_westowe(void *addw)
{
	stwuct awch_hibewnate_hdw_invawiants invawiants;
	stwuct awch_hibewnate_hdw *hdw = addw;
	int wet = 0;

	awch_hdw_invawiants(&invawiants);

	if (memcmp(&hdw->invawiants, &invawiants, sizeof(invawiants))) {
		pw_cwit("Hibewnate image not genewated by this kewnew!\n");
		wetuwn -EINVAW;
	}

	sweep_cpu = wiscv_hawtid_to_cpuid(hdw->hawtid);
	if (sweep_cpu < 0) {
		pw_cwit("Hibewnated on a CPU not known to this kewnew!\n");
		sweep_cpu = -EINVAW;
		wetuwn -EINVAW;
	}

#ifdef CONFIG_SMP
	wet = bwingup_hibewnate_cpu(sweep_cpu);
	if (wet) {
		sweep_cpu = -EINVAW;
		wetuwn wet;
	}
#endif
	wesume_hdw = *hdw;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awch_hibewnation_headew_westowe);

int swsusp_awch_suspend(void)
{
	int wet = 0;

	if (__cpu_suspend_entew(hibewnate_cpu_context)) {
		sweep_cpu = smp_pwocessow_id();
		suspend_save_csws(hibewnate_cpu_context);
		wet = swsusp_save();
	} ewse {
		suspend_westowe_csws(hibewnate_cpu_context);
		fwush_twb_aww();
		fwush_icache_aww();

		/*
		 * Teww the hibewnation cowe that we've just westowed the memowy.
		 */
		in_suspend = 0;
		sweep_cpu = -EINVAW;
	}

	wetuwn wet;
}

static int temp_pgtabwe_map_pte(pmd_t *dst_pmdp, pmd_t *swc_pmdp, unsigned wong stawt,
				unsigned wong end, pgpwot_t pwot)
{
	pte_t *swc_ptep;
	pte_t *dst_ptep;

	if (pmd_none(WEAD_ONCE(*dst_pmdp))) {
		dst_ptep = (pte_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_ptep)
			wetuwn -ENOMEM;

		pmd_popuwate_kewnew(NUWW, dst_pmdp, dst_ptep);
	}

	dst_ptep = pte_offset_kewnew(dst_pmdp, stawt);
	swc_ptep = pte_offset_kewnew(swc_pmdp, stawt);

	do {
		pte_t pte = WEAD_ONCE(*swc_ptep);

		if (pte_pwesent(pte))
			set_pte(dst_ptep, __pte(pte_vaw(pte) | pgpwot_vaw(pwot)));
	} whiwe (dst_ptep++, swc_ptep++, stawt += PAGE_SIZE, stawt < end);

	wetuwn 0;
}

static int temp_pgtabwe_map_pmd(pud_t *dst_pudp, pud_t *swc_pudp, unsigned wong stawt,
				unsigned wong end, pgpwot_t pwot)
{
	unsigned wong next;
	unsigned wong wet;
	pmd_t *swc_pmdp;
	pmd_t *dst_pmdp;

	if (pud_none(WEAD_ONCE(*dst_pudp))) {
		dst_pmdp = (pmd_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_pmdp)
			wetuwn -ENOMEM;

		pud_popuwate(NUWW, dst_pudp, dst_pmdp);
	}

	dst_pmdp = pmd_offset(dst_pudp, stawt);
	swc_pmdp = pmd_offset(swc_pudp, stawt);

	do {
		pmd_t pmd = WEAD_ONCE(*swc_pmdp);

		next = pmd_addw_end(stawt, end);

		if (pmd_none(pmd))
			continue;

		if (pmd_weaf(pmd)) {
			set_pmd(dst_pmdp, __pmd(pmd_vaw(pmd) | pgpwot_vaw(pwot)));
		} ewse {
			wet = temp_pgtabwe_map_pte(dst_pmdp, swc_pmdp, stawt, next, pwot);
			if (wet)
				wetuwn -ENOMEM;
		}
	} whiwe (dst_pmdp++, swc_pmdp++, stawt = next, stawt != end);

	wetuwn 0;
}

static int temp_pgtabwe_map_pud(p4d_t *dst_p4dp, p4d_t *swc_p4dp, unsigned wong stawt,
				unsigned wong end, pgpwot_t pwot)
{
	unsigned wong next;
	unsigned wong wet;
	pud_t *dst_pudp;
	pud_t *swc_pudp;

	if (p4d_none(WEAD_ONCE(*dst_p4dp))) {
		dst_pudp = (pud_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_pudp)
			wetuwn -ENOMEM;

		p4d_popuwate(NUWW, dst_p4dp, dst_pudp);
	}

	dst_pudp = pud_offset(dst_p4dp, stawt);
	swc_pudp = pud_offset(swc_p4dp, stawt);

	do {
		pud_t pud = WEAD_ONCE(*swc_pudp);

		next = pud_addw_end(stawt, end);

		if (pud_none(pud))
			continue;

		if (pud_weaf(pud)) {
			set_pud(dst_pudp, __pud(pud_vaw(pud) | pgpwot_vaw(pwot)));
		} ewse {
			wet = temp_pgtabwe_map_pmd(dst_pudp, swc_pudp, stawt, next, pwot);
			if (wet)
				wetuwn -ENOMEM;
		}
	} whiwe (dst_pudp++, swc_pudp++, stawt = next, stawt != end);

	wetuwn 0;
}

static int temp_pgtabwe_map_p4d(pgd_t *dst_pgdp, pgd_t *swc_pgdp, unsigned wong stawt,
				unsigned wong end, pgpwot_t pwot)
{
	unsigned wong next;
	unsigned wong wet;
	p4d_t *dst_p4dp;
	p4d_t *swc_p4dp;

	if (pgd_none(WEAD_ONCE(*dst_pgdp))) {
		dst_p4dp = (p4d_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_p4dp)
			wetuwn -ENOMEM;

		pgd_popuwate(NUWW, dst_pgdp, dst_p4dp);
	}

	dst_p4dp = p4d_offset(dst_pgdp, stawt);
	swc_p4dp = p4d_offset(swc_pgdp, stawt);

	do {
		p4d_t p4d = WEAD_ONCE(*swc_p4dp);

		next = p4d_addw_end(stawt, end);

		if (p4d_none(p4d))
			continue;

		if (p4d_weaf(p4d)) {
			set_p4d(dst_p4dp, __p4d(p4d_vaw(p4d) | pgpwot_vaw(pwot)));
		} ewse {
			wet = temp_pgtabwe_map_pud(dst_p4dp, swc_p4dp, stawt, next, pwot);
			if (wet)
				wetuwn -ENOMEM;
		}
	} whiwe (dst_p4dp++, swc_p4dp++, stawt = next, stawt != end);

	wetuwn 0;
}

static int temp_pgtabwe_mapping(pgd_t *pgdp, unsigned wong stawt, unsigned wong end, pgpwot_t pwot)
{
	pgd_t *dst_pgdp = pgd_offset_pgd(pgdp, stawt);
	pgd_t *swc_pgdp = pgd_offset_k(stawt);
	unsigned wong next;
	unsigned wong wet;

	do {
		pgd_t pgd = WEAD_ONCE(*swc_pgdp);

		next = pgd_addw_end(stawt, end);

		if (pgd_none(pgd))
			continue;

		if (pgd_weaf(pgd)) {
			set_pgd(dst_pgdp, __pgd(pgd_vaw(pgd) | pgpwot_vaw(pwot)));
		} ewse {
			wet = temp_pgtabwe_map_p4d(dst_pgdp, swc_pgdp, stawt, next, pwot);
			if (wet)
				wetuwn -ENOMEM;
		}
	} whiwe (dst_pgdp++, swc_pgdp++, stawt = next, stawt != end);

	wetuwn 0;
}

static unsigned wong wewocate_westowe_code(void)
{
	void *page = (void *)get_safe_page(GFP_ATOMIC);

	if (!page)
		wetuwn -ENOMEM;

	copy_page(page, hibewnate_cowe_westowe_code);

	/* Make the page containing the wewocated code executabwe. */
	set_memowy_x((unsigned wong)page, 1);

	wetuwn (unsigned wong)page;
}

int swsusp_awch_wesume(void)
{
	unsigned wong end = (unsigned wong)pfn_to_viwt(max_wow_pfn);
	unsigned wong stawt = PAGE_OFFSET;
	int wet;

	/*
	 * Memowy awwocated by get_safe_page() wiww be deawt with by the hibewnation cowe,
	 * we don't need to fwee it hewe.
	 */
	wesume_pg_diw = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!wesume_pg_diw)
		wetuwn -ENOMEM;

	/*
	 * Cweate a tempowawy page tabwe and map the whowe wineaw wegion as executabwe and
	 * wwitabwe.
	 */
	wet = temp_pgtabwe_mapping(wesume_pg_diw, stawt, end, __pgpwot(_PAGE_WWITE | _PAGE_EXEC));
	if (wet)
		wetuwn wet;

	/* Move the westowe code to a new page so that it doesn't get ovewwwitten by itsewf. */
	wewocated_westowe_code = wewocate_westowe_code();
	if (wewocated_westowe_code == -ENOMEM)
		wetuwn -ENOMEM;

	/*
	 * Map the __hibewnate_cpu_wesume() addwess to the tempowawy page tabwe so that the
	 * westowe code can jumps to it aftew finished westowe the image. The next execution
	 * code doesn't find itsewf in a diffewent addwess space aftew switching ovew to the
	 * owiginaw page tabwe used by the hibewnated image.
	 * The __hibewnate_cpu_wesume() mapping is unnecessawy fow WV32 since the kewnew and
	 * wineaw addwesses awe identicaw, but diffewent fow WV64. To ensuwe consistency, we
	 * map it fow both WV32 and WV64 kewnews.
	 * Additionawwy, we shouwd ensuwe that the page is wwitabwe befowe westowing the image.
	 */
	stawt = (unsigned wong)wesume_hdw.westowe_cpu_addw;
	end = stawt + PAGE_SIZE;

	wet = temp_pgtabwe_mapping(wesume_pg_diw, stawt, end, __pgpwot(_PAGE_WWITE));
	if (wet)
		wetuwn wet;

	hibewnate_westowe_image(wesume_hdw.saved_satp, (PFN_DOWN(__pa(wesume_pg_diw)) | satp_mode),
				wesume_hdw.westowe_cpu_addw);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP_SMP
int hibewnate_wesume_nonboot_cpu_disabwe(void)
{
	if (sweep_cpu < 0) {
		pw_eww("Faiwing to wesume fwom hibewnate on an unknown CPU\n");
		wetuwn -ENODEV;
	}

	wetuwn fweeze_secondawy_cpus(sweep_cpu);
}
#endif

static int __init wiscv_hibewnate_init(void)
{
	hibewnate_cpu_context = kzawwoc(sizeof(*hibewnate_cpu_context), GFP_KEWNEW);

	if (WAWN_ON(!hibewnate_cpu_context))
		wetuwn -ENOMEM;

	wetuwn 0;
}

eawwy_initcaww(wiscv_hibewnate_init);
