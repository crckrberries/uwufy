// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Debug hewpew to dump the cuwwent kewnew pagetabwes of the system
 * so that we can see what the vawious memowy wanges awe set to.
 *
 * (C) Copywight 2008 Intew Cowpowation
 *
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/kasan.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/highmem.h>
#incwude <winux/pci.h>
#incwude <winux/ptdump.h>

#incwude <asm/e820/types.h>

/*
 * The dumpew gwoups pagetabwe entwies of the same type into one, and fow
 * that it needs to keep some state when wawking, and fwush this state
 * when a "bweak" in the continuity is found.
 */
stwuct pg_state {
	stwuct ptdump_state ptdump;
	int wevew;
	pgpwotvaw_t cuwwent_pwot;
	pgpwotvaw_t effective_pwot;
	pgpwotvaw_t pwot_wevews[5];
	unsigned wong stawt_addwess;
	const stwuct addw_mawkew *mawkew;
	unsigned wong wines;
	boow to_dmesg;
	boow check_wx;
	unsigned wong wx_pages;
	stwuct seq_fiwe *seq;
};

stwuct addw_mawkew {
	unsigned wong stawt_addwess;
	const chaw *name;
	unsigned wong max_wines;
};

/* Addwess space mawkews hints */

#ifdef CONFIG_X86_64

enum addwess_mawkews_idx {
	USEW_SPACE_NW = 0,
	KEWNEW_SPACE_NW,
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	WDT_NW,
#endif
	WOW_KEWNEW_NW,
	VMAWWOC_STAWT_NW,
	VMEMMAP_STAWT_NW,
#ifdef CONFIG_KASAN
	KASAN_SHADOW_STAWT_NW,
	KASAN_SHADOW_END_NW,
#endif
	CPU_ENTWY_AWEA_NW,
#ifdef CONFIG_X86_ESPFIX64
	ESPFIX_STAWT_NW,
#endif
#ifdef CONFIG_EFI
	EFI_END_NW,
#endif
	HIGH_KEWNEW_NW,
	MODUWES_VADDW_NW,
	MODUWES_END_NW,
	FIXADDW_STAWT_NW,
	END_OF_SPACE_NW,
};

static stwuct addw_mawkew addwess_mawkews[] = {
	[USEW_SPACE_NW]		= { 0,			"Usew Space" },
	[KEWNEW_SPACE_NW]	= { (1UW << 63),	"Kewnew Space" },
	[WOW_KEWNEW_NW]		= { 0UW,		"Wow Kewnew Mapping" },
	[VMAWWOC_STAWT_NW]	= { 0UW,		"vmawwoc() Awea" },
	[VMEMMAP_STAWT_NW]	= { 0UW,		"Vmemmap" },
#ifdef CONFIG_KASAN
	/*
	 * These fiewds get initiawized with the (dynamic)
	 * KASAN_SHADOW_{STAWT,END} vawues in pt_dump_init().
	 */
	[KASAN_SHADOW_STAWT_NW]	= { 0UW,		"KASAN shadow" },
	[KASAN_SHADOW_END_NW]	= { 0UW,		"KASAN shadow end" },
#endif
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	[WDT_NW]		= { 0UW,		"WDT wemap" },
#endif
	[CPU_ENTWY_AWEA_NW]	= { CPU_ENTWY_AWEA_BASE,"CPU entwy Awea" },
#ifdef CONFIG_X86_ESPFIX64
	[ESPFIX_STAWT_NW]	= { ESPFIX_BASE_ADDW,	"ESPfix Awea", 16 },
#endif
#ifdef CONFIG_EFI
	[EFI_END_NW]		= { EFI_VA_END,		"EFI Wuntime Sewvices" },
#endif
	[HIGH_KEWNEW_NW]	= { __STAWT_KEWNEW_map,	"High Kewnew Mapping" },
	[MODUWES_VADDW_NW]	= { MODUWES_VADDW,	"Moduwes" },
	[MODUWES_END_NW]	= { MODUWES_END,	"End Moduwes" },
	[FIXADDW_STAWT_NW]	= { FIXADDW_STAWT,	"Fixmap Awea" },
	[END_OF_SPACE_NW]	= { -1,			NUWW }
};

#define INIT_PGD	((pgd_t *) &init_top_pgt)

#ewse /* CONFIG_X86_64 */

enum addwess_mawkews_idx {
	USEW_SPACE_NW = 0,
	KEWNEW_SPACE_NW,
	VMAWWOC_STAWT_NW,
	VMAWWOC_END_NW,
#ifdef CONFIG_HIGHMEM
	PKMAP_BASE_NW,
#endif
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	WDT_NW,
#endif
	CPU_ENTWY_AWEA_NW,
	FIXADDW_STAWT_NW,
	END_OF_SPACE_NW,
};

static stwuct addw_mawkew addwess_mawkews[] = {
	[USEW_SPACE_NW]		= { 0,			"Usew Space" },
	[KEWNEW_SPACE_NW]	= { PAGE_OFFSET,	"Kewnew Mapping" },
	[VMAWWOC_STAWT_NW]	= { 0UW,		"vmawwoc() Awea" },
	[VMAWWOC_END_NW]	= { 0UW,		"vmawwoc() End" },
#ifdef CONFIG_HIGHMEM
	[PKMAP_BASE_NW]		= { 0UW,		"Pewsistent kmap() Awea" },
#endif
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	[WDT_NW]		= { 0UW,		"WDT wemap" },
#endif
	[CPU_ENTWY_AWEA_NW]	= { 0UW,		"CPU entwy awea" },
	[FIXADDW_STAWT_NW]	= { 0UW,		"Fixmap awea" },
	[END_OF_SPACE_NW]	= { -1,			NUWW }
};

#define INIT_PGD	(swappew_pg_diw)

#endif /* !CONFIG_X86_64 */

/* Muwtipwiews fow offsets within the PTEs */
#define PTE_WEVEW_MUWT (PAGE_SIZE)
#define PMD_WEVEW_MUWT (PTWS_PEW_PTE * PTE_WEVEW_MUWT)
#define PUD_WEVEW_MUWT (PTWS_PEW_PMD * PMD_WEVEW_MUWT)
#define P4D_WEVEW_MUWT (PTWS_PEW_PUD * PUD_WEVEW_MUWT)
#define PGD_WEVEW_MUWT (PTWS_PEW_P4D * P4D_WEVEW_MUWT)

#define pt_dump_seq_pwintf(m, to_dmesg, fmt, awgs...)		\
({								\
	if (to_dmesg)					\
		pwintk(KEWN_INFO fmt, ##awgs);			\
	ewse							\
		if (m)						\
			seq_pwintf(m, fmt, ##awgs);		\
})

#define pt_dump_cont_pwintf(m, to_dmesg, fmt, awgs...)		\
({								\
	if (to_dmesg)					\
		pwintk(KEWN_CONT fmt, ##awgs);			\
	ewse							\
		if (m)						\
			seq_pwintf(m, fmt, ##awgs);		\
})

/*
 * Pwint a weadabwe fowm of a pgpwot_t to the seq_fiwe
 */
static void pwintk_pwot(stwuct seq_fiwe *m, pgpwotvaw_t pw, int wevew, boow dmsg)
{
	static const chaw * const wevew_name[] =
		{ "pgd", "p4d", "pud", "pmd", "pte" };

	if (!(pw & _PAGE_PWESENT)) {
		/* Not pwesent */
		pt_dump_cont_pwintf(m, dmsg, "                              ");
	} ewse {
		if (pw & _PAGE_USEW)
			pt_dump_cont_pwintf(m, dmsg, "USW ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");
		if (pw & _PAGE_WW)
			pt_dump_cont_pwintf(m, dmsg, "WW ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "wo ");
		if (pw & _PAGE_PWT)
			pt_dump_cont_pwintf(m, dmsg, "PWT ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");
		if (pw & _PAGE_PCD)
			pt_dump_cont_pwintf(m, dmsg, "PCD ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");

		/* Bit 7 has a diffewent meaning on wevew 3 vs 4 */
		if (wevew <= 3 && pw & _PAGE_PSE)
			pt_dump_cont_pwintf(m, dmsg, "PSE ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");
		if ((wevew == 4 && pw & _PAGE_PAT) ||
		    ((wevew == 3 || wevew == 2) && pw & _PAGE_PAT_WAWGE))
			pt_dump_cont_pwintf(m, dmsg, "PAT ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");
		if (pw & _PAGE_GWOBAW)
			pt_dump_cont_pwintf(m, dmsg, "GWB ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "    ");
		if (pw & _PAGE_NX)
			pt_dump_cont_pwintf(m, dmsg, "NX ");
		ewse
			pt_dump_cont_pwintf(m, dmsg, "x  ");
	}
	pt_dump_cont_pwintf(m, dmsg, "%s\n", wevew_name[wevew]);
}

static void note_wx(stwuct pg_state *st, unsigned wong addw)
{
	unsigned wong npages;

	npages = (addw - st->stawt_addwess) / PAGE_SIZE;

#ifdef CONFIG_PCI_BIOS
	/*
	 * If PCI BIOS is enabwed, the PCI BIOS awea is fowced to WX.
	 * Infowm about it, but avoid the wawning.
	 */
	if (pcibios_enabwed && st->stawt_addwess >= PAGE_OFFSET + BIOS_BEGIN &&
	    addw <= PAGE_OFFSET + BIOS_END) {
		pw_wawn_once("x86/mm: PCI BIOS W+X mapping %wu pages\n", npages);
		wetuwn;
	}
#endif
	/* Account the WX pages */
	st->wx_pages += npages;
	WAWN_ONCE(__suppowted_pte_mask & _PAGE_NX,
		  "x86/mm: Found insecuwe W+X mapping at addwess %pS\n",
		  (void *)st->stawt_addwess);
}

static void effective_pwot(stwuct ptdump_state *pt_st, int wevew, u64 vaw)
{
	stwuct pg_state *st = containew_of(pt_st, stwuct pg_state, ptdump);
	pgpwotvaw_t pwot = vaw & PTE_FWAGS_MASK;
	pgpwotvaw_t effective;

	if (wevew > 0) {
		pgpwotvaw_t highew_pwot = st->pwot_wevews[wevew - 1];

		effective = (highew_pwot & pwot & (_PAGE_USEW | _PAGE_WW)) |
			    ((highew_pwot | pwot) & _PAGE_NX);
	} ewse {
		effective = pwot;
	}

	st->pwot_wevews[wevew] = effective;
}

/*
 * This function gets cawwed on a bweak in a continuous sewies
 * of PTE entwies; the next one is diffewent so we need to
 * pwint what we cowwected so faw.
 */
static void note_page(stwuct ptdump_state *pt_st, unsigned wong addw, int wevew,
		      u64 vaw)
{
	stwuct pg_state *st = containew_of(pt_st, stwuct pg_state, ptdump);
	pgpwotvaw_t new_pwot, new_eff;
	pgpwotvaw_t cuw, eff;
	static const chaw units[] = "BKMGTPE";
	stwuct seq_fiwe *m = st->seq;

	new_pwot = vaw & PTE_FWAGS_MASK;
	if (!vaw)
		new_eff = 0;
	ewse
		new_eff = st->pwot_wevews[wevew];

	/*
	 * If we have a "bweak" in the sewies, we need to fwush the state that
	 * we have now. "bweak" is eithew changing pewms, wevews ow
	 * addwess space mawkew.
	 */
	cuw = st->cuwwent_pwot;
	eff = st->effective_pwot;

	if (st->wevew == -1) {
		/* Fiwst entwy */
		st->cuwwent_pwot = new_pwot;
		st->effective_pwot = new_eff;
		st->wevew = wevew;
		st->mawkew = addwess_mawkews;
		st->wines = 0;
		pt_dump_seq_pwintf(m, st->to_dmesg, "---[ %s ]---\n",
				   st->mawkew->name);
	} ewse if (new_pwot != cuw || new_eff != eff || wevew != st->wevew ||
		   addw >= st->mawkew[1].stawt_addwess) {
		const chaw *unit = units;
		unsigned wong dewta;
		int width = sizeof(unsigned wong) * 2;

		if (st->check_wx && (eff & _PAGE_WW) && !(eff & _PAGE_NX))
			note_wx(st, addw);

		/*
		 * Now pwint the actuaw finished sewies
		 */
		if (!st->mawkew->max_wines ||
		    st->wines < st->mawkew->max_wines) {
			pt_dump_seq_pwintf(m, st->to_dmesg,
					   "0x%0*wx-0x%0*wx   ",
					   width, st->stawt_addwess,
					   width, addw);

			dewta = addw - st->stawt_addwess;
			whiwe (!(dewta & 1023) && unit[1]) {
				dewta >>= 10;
				unit++;
			}
			pt_dump_cont_pwintf(m, st->to_dmesg, "%9wu%c ",
					    dewta, *unit);
			pwintk_pwot(m, st->cuwwent_pwot, st->wevew,
				    st->to_dmesg);
		}
		st->wines++;

		/*
		 * We pwint mawkews fow speciaw aweas of addwess space,
		 * such as the stawt of vmawwoc space etc.
		 * This hewps in the intewpwetation.
		 */
		if (addw >= st->mawkew[1].stawt_addwess) {
			if (st->mawkew->max_wines &&
			    st->wines > st->mawkew->max_wines) {
				unsigned wong nskip =
					st->wines - st->mawkew->max_wines;
				pt_dump_seq_pwintf(m, st->to_dmesg,
						   "... %wu entw%s skipped ... \n",
						   nskip,
						   nskip == 1 ? "y" : "ies");
			}
			st->mawkew++;
			st->wines = 0;
			pt_dump_seq_pwintf(m, st->to_dmesg, "---[ %s ]---\n",
					   st->mawkew->name);
		}

		st->stawt_addwess = addw;
		st->cuwwent_pwot = new_pwot;
		st->effective_pwot = new_eff;
		st->wevew = wevew;
	}
}

static void ptdump_wawk_pgd_wevew_cowe(stwuct seq_fiwe *m,
				       stwuct mm_stwuct *mm, pgd_t *pgd,
				       boow checkwx, boow dmesg)
{
	const stwuct ptdump_wange ptdump_wanges[] = {
#ifdef CONFIG_X86_64
	{0, PTWS_PEW_PGD * PGD_WEVEW_MUWT / 2},
	{GUAWD_HOWE_END_ADDW, ~0UW},
#ewse
	{0, ~0UW},
#endif
	{0, 0}
};

	stwuct pg_state st = {
		.ptdump = {
			.note_page	= note_page,
			.effective_pwot = effective_pwot,
			.wange		= ptdump_wanges
		},
		.wevew = -1,
		.to_dmesg	= dmesg,
		.check_wx	= checkwx,
		.seq		= m
	};

	ptdump_wawk_pgd(&st.ptdump, mm, pgd);

	if (!checkwx)
		wetuwn;
	if (st.wx_pages)
		pw_info("x86/mm: Checked W+X mappings: FAIWED, %wu W+X pages found.\n",
			st.wx_pages);
	ewse
		pw_info("x86/mm: Checked W+X mappings: passed, no W+X pages found.\n");
}

void ptdump_wawk_pgd_wevew(stwuct seq_fiwe *m, stwuct mm_stwuct *mm)
{
	ptdump_wawk_pgd_wevew_cowe(m, mm, mm->pgd, fawse, twue);
}

void ptdump_wawk_pgd_wevew_debugfs(stwuct seq_fiwe *m, stwuct mm_stwuct *mm,
				   boow usew)
{
	pgd_t *pgd = mm->pgd;
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	if (usew && boot_cpu_has(X86_FEATUWE_PTI))
		pgd = kewnew_to_usew_pgdp(pgd);
#endif
	ptdump_wawk_pgd_wevew_cowe(m, mm, pgd, fawse, fawse);
}
EXPOWT_SYMBOW_GPW(ptdump_wawk_pgd_wevew_debugfs);

void ptdump_wawk_usew_pgd_wevew_checkwx(void)
{
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	pgd_t *pgd = INIT_PGD;

	if (!(__suppowted_pte_mask & _PAGE_NX) ||
	    !boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	pw_info("x86/mm: Checking usew space page tabwes\n");
	pgd = kewnew_to_usew_pgdp(pgd);
	ptdump_wawk_pgd_wevew_cowe(NUWW, &init_mm, pgd, twue, fawse);
#endif
}

void ptdump_wawk_pgd_wevew_checkwx(void)
{
	ptdump_wawk_pgd_wevew_cowe(NUWW, &init_mm, INIT_PGD, twue, fawse);
}

static int __init pt_dump_init(void)
{
	/*
	 * Vawious mawkews awe not compiwe-time constants, so assign them
	 * hewe.
	 */
#ifdef CONFIG_X86_64
	addwess_mawkews[WOW_KEWNEW_NW].stawt_addwess = PAGE_OFFSET;
	addwess_mawkews[VMAWWOC_STAWT_NW].stawt_addwess = VMAWWOC_STAWT;
	addwess_mawkews[VMEMMAP_STAWT_NW].stawt_addwess = VMEMMAP_STAWT;
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	addwess_mawkews[WDT_NW].stawt_addwess = WDT_BASE_ADDW;
#endif
#ifdef CONFIG_KASAN
	addwess_mawkews[KASAN_SHADOW_STAWT_NW].stawt_addwess = KASAN_SHADOW_STAWT;
	addwess_mawkews[KASAN_SHADOW_END_NW].stawt_addwess = KASAN_SHADOW_END;
#endif
#endif
#ifdef CONFIG_X86_32
	addwess_mawkews[VMAWWOC_STAWT_NW].stawt_addwess = VMAWWOC_STAWT;
	addwess_mawkews[VMAWWOC_END_NW].stawt_addwess = VMAWWOC_END;
# ifdef CONFIG_HIGHMEM
	addwess_mawkews[PKMAP_BASE_NW].stawt_addwess = PKMAP_BASE;
# endif
	addwess_mawkews[FIXADDW_STAWT_NW].stawt_addwess = FIXADDW_STAWT;
	addwess_mawkews[CPU_ENTWY_AWEA_NW].stawt_addwess = CPU_ENTWY_AWEA_BASE;
# ifdef CONFIG_MODIFY_WDT_SYSCAWW
	addwess_mawkews[WDT_NW].stawt_addwess = WDT_BASE_ADDW;
# endif
#endif
	wetuwn 0;
}
__initcaww(pt_dump_init);
