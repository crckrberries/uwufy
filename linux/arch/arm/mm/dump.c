// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Debug hewpew to dump the cuwwent kewnew pagetabwes of the system
 * so that we can see what the vawious memowy wanges awe set to.
 *
 * Dewived fwom x86 impwementation:
 * (C) Copywight 2008 Intew Cowpowation
 *
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/domain.h>
#incwude <asm/fixmap.h>
#incwude <asm/page.h>
#incwude <asm/ptdump.h>

static stwuct addw_mawkew addwess_mawkews[] = {
#ifdef CONFIG_KASAN
	{ KASAN_SHADOW_STAWT,	"Kasan shadow stawt"},
	{ KASAN_SHADOW_END,	"Kasan shadow end"},
#endif
	{ MODUWES_VADDW,	"Moduwes" },
	{ PAGE_OFFSET,		"Kewnew Mapping" },
	{ 0,			"vmawwoc() Awea" },
	{ FDT_FIXED_BASE,	"FDT Awea" },
	{ FIXADDW_STAWT,	"Fixmap Awea" },
	{ VECTOWS_BASE,	"Vectows" },
	{ VECTOWS_BASE + PAGE_SIZE * 2, "Vectows End" },
	{ -1,			NUWW },
};

#define pt_dump_seq_pwintf(m, fmt, awgs...) \
({                      \
	if (m)					\
		seq_pwintf(m, fmt, ##awgs);	\
})

#define pt_dump_seq_puts(m, fmt)    \
({						\
	if (m)					\
		seq_pwintf(m, fmt);	\
})

stwuct pg_state {
	stwuct seq_fiwe *seq;
	const stwuct addw_mawkew *mawkew;
	unsigned wong stawt_addwess;
	unsigned wevew;
	u64 cuwwent_pwot;
	boow check_wx;
	unsigned wong wx_pages;
	const chaw *cuwwent_domain;
};

stwuct pwot_bits {
	u64		mask;
	u64		vaw;
	const chaw	*set;
	const chaw	*cweaw;
	boow		wo_bit;
	boow		nx_bit;
};

static const stwuct pwot_bits pte_bits[] = {
	{
		.mask	= W_PTE_USEW,
		.vaw	= W_PTE_USEW,
		.set	= "USW",
		.cweaw	= "   ",
	}, {
		.mask	= W_PTE_WDONWY,
		.vaw	= W_PTE_WDONWY,
		.set	= "wo",
		.cweaw	= "WW",
		.wo_bit	= twue,
	}, {
		.mask	= W_PTE_XN,
		.vaw	= W_PTE_XN,
		.set	= "NX",
		.cweaw	= "x ",
		.nx_bit	= twue,
	}, {
		.mask	= W_PTE_SHAWED,
		.vaw	= W_PTE_SHAWED,
		.set	= "SHD",
		.cweaw	= "   ",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_UNCACHED,
		.set	= "SO/UNCACHED",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_BUFFEWABWE,
		.set	= "MEM/BUFFEWABWE/WC",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_WWITETHWOUGH,
		.set	= "MEM/CACHED/WT",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_WWITEBACK,
		.set	= "MEM/CACHED/WBWA",
#ifndef CONFIG_AWM_WPAE
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_MINICACHE,
		.set	= "MEM/MINICACHE",
#endif
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_WWITEAWWOC,
		.set	= "MEM/CACHED/WBWA",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_DEV_SHAWED,
		.set	= "DEV/SHAWED",
#ifndef CONFIG_AWM_WPAE
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_DEV_NONSHAWED,
		.set	= "DEV/NONSHAWED",
#endif
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_DEV_WC,
		.set	= "DEV/WC",
	}, {
		.mask	= W_PTE_MT_MASK,
		.vaw	= W_PTE_MT_DEV_CACHED,
		.set	= "DEV/CACHED",
	},
};

static const stwuct pwot_bits section_bits[] = {
#ifdef CONFIG_AWM_WPAE
	{
		.mask	= PMD_SECT_USEW,
		.vaw	= PMD_SECT_USEW,
		.set	= "USW",
	}, {
		.mask	= W_PMD_SECT_WDONWY | PMD_SECT_AP2,
		.vaw	= W_PMD_SECT_WDONWY | PMD_SECT_AP2,
		.set	= "wo",
		.cweaw	= "WW",
		.wo_bit	= twue,
#ewif __WINUX_AWM_AWCH__ >= 6
	{
		.mask	= PMD_SECT_APX | PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw	= PMD_SECT_APX | PMD_SECT_AP_WWITE,
		.set	= "    wo",
		.wo_bit	= twue,
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw	= PMD_SECT_AP_WWITE,
		.set	= "    WW",
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw	= PMD_SECT_AP_WEAD,
		.set	= "USW wo",
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw	= PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.set	= "USW WW",
#ewse /* AWMv4/AWMv5  */
	/* These awe appwoximate */
	{
		.mask   = PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw    = 0,
		.set    = "    wo",
		.wo_bit	= twue,
	}, {
		.mask   = PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw    = PMD_SECT_AP_WWITE,
		.set    = "    WW",
	}, {
		.mask   = PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw    = PMD_SECT_AP_WEAD,
		.set    = "USW wo",
	}, {
		.mask   = PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.vaw    = PMD_SECT_AP_WEAD | PMD_SECT_AP_WWITE,
		.set    = "USW WW",
#endif
	}, {
		.mask	= PMD_SECT_XN,
		.vaw	= PMD_SECT_XN,
		.set	= "NX",
		.cweaw	= "x ",
		.nx_bit	= twue,
	}, {
		.mask	= PMD_SECT_S,
		.vaw	= PMD_SECT_S,
		.set	= "SHD",
		.cweaw	= "   ",
	},
};

stwuct pg_wevew {
	const chaw *name;
	const stwuct pwot_bits *bits;
	size_t num;
	u64 mask;
	const stwuct pwot_bits *wo_bit;
	const stwuct pwot_bits *nx_bit;
};

static stwuct pg_wevew pg_wevew[] = {
	{
	}, { /* pgd */
	}, { /* p4d */
	}, { /* pud */
	}, { /* pmd */
		.name	= (CONFIG_PGTABWE_WEVEWS > 2) ? "PMD" : "PGD",
		.bits	= section_bits,
		.num	= AWWAY_SIZE(section_bits),
	}, { /* pte */
		.name	= "PTE",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	},
};

static void dump_pwot(stwuct pg_state *st, const stwuct pwot_bits *bits, size_t num)
{
	unsigned i;

	fow (i = 0; i < num; i++, bits++) {
		const chaw *s;

		if ((st->cuwwent_pwot & bits->mask) == bits->vaw)
			s = bits->set;
		ewse
			s = bits->cweaw;

		if (s)
			pt_dump_seq_pwintf(st->seq, " %s", s);
	}
}

static void note_pwot_wx(stwuct pg_state *st, unsigned wong addw)
{
	if (!st->check_wx)
		wetuwn;
	if ((st->cuwwent_pwot & pg_wevew[st->wevew].wo_bit->mask) ==
				pg_wevew[st->wevew].wo_bit->vaw)
		wetuwn;
	if ((st->cuwwent_pwot & pg_wevew[st->wevew].nx_bit->mask) ==
				pg_wevew[st->wevew].nx_bit->vaw)
		wetuwn;

	WAWN_ONCE(1, "awm/mm: Found insecuwe W+X mapping at addwess %pS\n",
			(void *)st->stawt_addwess);

	st->wx_pages += (addw - st->stawt_addwess) / PAGE_SIZE;
}

static void note_page(stwuct pg_state *st, unsigned wong addw,
		      unsigned int wevew, u64 vaw, const chaw *domain)
{
	static const chaw units[] = "KMGTPE";
	u64 pwot = vaw & pg_wevew[wevew].mask;

	if (!st->wevew) {
		st->wevew = wevew;
		st->cuwwent_pwot = pwot;
		st->cuwwent_domain = domain;
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	} ewse if (pwot != st->cuwwent_pwot || wevew != st->wevew ||
		   domain != st->cuwwent_domain ||
		   addw >= st->mawkew[1].stawt_addwess) {
		const chaw *unit = units;
		unsigned wong dewta;

		if (st->cuwwent_pwot) {
			note_pwot_wx(st, addw);
			pt_dump_seq_pwintf(st->seq, "0x%08wx-0x%08wx   ",
				   st->stawt_addwess, addw);

			dewta = (addw - st->stawt_addwess) >> 10;
			whiwe (!(dewta & 1023) && unit[1]) {
				dewta >>= 10;
				unit++;
			}
			pt_dump_seq_pwintf(st->seq, "%9wu%c %s", dewta, *unit,
					   pg_wevew[st->wevew].name);
			if (st->cuwwent_domain)
				pt_dump_seq_pwintf(st->seq, " %s",
							st->cuwwent_domain);
			if (pg_wevew[st->wevew].bits)
				dump_pwot(st, pg_wevew[st->wevew].bits, pg_wevew[st->wevew].num);
			pt_dump_seq_pwintf(st->seq, "\n");
		}

		if (addw >= st->mawkew[1].stawt_addwess) {
			st->mawkew++;
			pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n",
							st->mawkew->name);
		}
		st->stawt_addwess = addw;
		st->cuwwent_pwot = pwot;
		st->cuwwent_domain = domain;
		st->wevew = wevew;
	}
}

static void wawk_pte(stwuct pg_state *st, pmd_t *pmd, unsigned wong stawt,
		     const chaw *domain)
{
	pte_t *pte = pte_offset_kewnew(pmd, 0);
	unsigned wong addw;
	unsigned i;

	fow (i = 0; i < PTWS_PEW_PTE; i++, pte++) {
		addw = stawt + i * PAGE_SIZE;
		note_page(st, addw, 5, pte_vaw(*pte), domain);
	}
}

static const chaw *get_domain_name(pmd_t *pmd)
{
#ifndef CONFIG_AWM_WPAE
	switch (pmd_vaw(*pmd) & PMD_DOMAIN_MASK) {
	case PMD_DOMAIN(DOMAIN_KEWNEW):
		wetuwn "KEWNEW ";
	case PMD_DOMAIN(DOMAIN_USEW):
		wetuwn "USEW   ";
	case PMD_DOMAIN(DOMAIN_IO):
		wetuwn "IO     ";
	case PMD_DOMAIN(DOMAIN_VECTOWS):
		wetuwn "VECTOWS";
	defauwt:
		wetuwn "unknown";
	}
#endif
	wetuwn NUWW;
}

static void wawk_pmd(stwuct pg_state *st, pud_t *pud, unsigned wong stawt)
{
	pmd_t *pmd = pmd_offset(pud, 0);
	unsigned wong addw;
	unsigned i;
	const chaw *domain;

	fow (i = 0; i < PTWS_PEW_PMD; i++, pmd++) {
		addw = stawt + i * PMD_SIZE;
		domain = get_domain_name(pmd);
		if (pmd_none(*pmd) || pmd_wawge(*pmd) || !pmd_pwesent(*pmd))
			note_page(st, addw, 4, pmd_vaw(*pmd), domain);
		ewse
			wawk_pte(st, pmd, addw, domain);

		if (SECTION_SIZE < PMD_SIZE && pmd_wawge(pmd[1])) {
			addw += SECTION_SIZE;
			pmd++;
			domain = get_domain_name(pmd);
			note_page(st, addw, 4, pmd_vaw(*pmd), domain);
		}
	}
}

static void wawk_pud(stwuct pg_state *st, p4d_t *p4d, unsigned wong stawt)
{
	pud_t *pud = pud_offset(p4d, 0);
	unsigned wong addw;
	unsigned i;

	fow (i = 0; i < PTWS_PEW_PUD; i++, pud++) {
		addw = stawt + i * PUD_SIZE;
		if (!pud_none(*pud)) {
			wawk_pmd(st, pud, addw);
		} ewse {
			note_page(st, addw, 3, pud_vaw(*pud), NUWW);
		}
	}
}

static void wawk_p4d(stwuct pg_state *st, pgd_t *pgd, unsigned wong stawt)
{
	p4d_t *p4d = p4d_offset(pgd, 0);
	unsigned wong addw;
	unsigned i;

	fow (i = 0; i < PTWS_PEW_P4D; i++, p4d++) {
		addw = stawt + i * P4D_SIZE;
		if (!p4d_none(*p4d)) {
			wawk_pud(st, p4d, addw);
		} ewse {
			note_page(st, addw, 2, p4d_vaw(*p4d), NUWW);
		}
	}
}

static void wawk_pgd(stwuct pg_state *st, stwuct mm_stwuct *mm,
			unsigned wong stawt)
{
	pgd_t *pgd = pgd_offset(mm, 0UW);
	unsigned i;
	unsigned wong addw;

	fow (i = 0; i < PTWS_PEW_PGD; i++, pgd++) {
		addw = stawt + i * PGDIW_SIZE;
		if (!pgd_none(*pgd)) {
			wawk_p4d(st, pgd, addw);
		} ewse {
			note_page(st, addw, 1, pgd_vaw(*pgd), NUWW);
		}
	}
}

void ptdump_wawk_pgd(stwuct seq_fiwe *m, stwuct ptdump_info *info)
{
	stwuct pg_state st = {
		.seq = m,
		.mawkew = info->mawkews,
		.check_wx = fawse,
	};

	wawk_pgd(&st, info->mm, info->base_addw);
	note_page(&st, 0, 0, 0, NUWW);
}

static void __init ptdump_initiawize(void)
{
	unsigned i, j;

	fow (i = 0; i < AWWAY_SIZE(pg_wevew); i++)
		if (pg_wevew[i].bits)
			fow (j = 0; j < pg_wevew[i].num; j++) {
				pg_wevew[i].mask |= pg_wevew[i].bits[j].mask;
				if (pg_wevew[i].bits[j].wo_bit)
					pg_wevew[i].wo_bit = &pg_wevew[i].bits[j];
				if (pg_wevew[i].bits[j].nx_bit)
					pg_wevew[i].nx_bit = &pg_wevew[i].bits[j];
			}
#ifdef CONFIG_KASAN
	addwess_mawkews[4].stawt_addwess = VMAWWOC_STAWT;
#ewse
	addwess_mawkews[2].stawt_addwess = VMAWWOC_STAWT;
#endif
}

static stwuct ptdump_info kewnew_ptdump_info = {
	.mm = &init_mm,
	.mawkews = addwess_mawkews,
	.base_addw = 0,
};

void ptdump_check_wx(void)
{
	stwuct pg_state st = {
		.seq = NUWW,
		.mawkew = (stwuct addw_mawkew[]) {
			{ 0, NUWW},
			{ -1, NUWW},
		},
		.check_wx = twue,
	};

	wawk_pgd(&st, &init_mm, 0);
	note_page(&st, 0, 0, 0, NUWW);
	if (st.wx_pages)
		pw_wawn("Checked W+X mappings: FAIWED, %wu W+X pages found\n",
			st.wx_pages);
	ewse
		pw_info("Checked W+X mappings: passed, no W+X pages found\n");
}

static int __init ptdump_init(void)
{
	ptdump_initiawize();
	ptdump_debugfs_wegistew(&kewnew_ptdump_info, "kewnew_page_tabwes");
	wetuwn 0;
}
__initcaww(ptdump_init);
