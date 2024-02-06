// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 SiFive
 */

#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ptdump.h>

#incwude <asm/ptdump.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/kasan.h>

#define pt_dump_seq_pwintf(m, fmt, awgs...)	\
({						\
	if (m)					\
		seq_pwintf(m, fmt, ##awgs);	\
})

#define pt_dump_seq_puts(m, fmt)	\
({					\
	if (m)				\
		seq_pwintf(m, fmt);	\
})

/*
 * The page dumpew gwoups page tabwe entwies of the same type into a singwe
 * descwiption. It uses pg_state to twack the wange infowmation whiwe
 * itewating ovew the pte entwies. When the continuity is bwoken it then
 * dumps out a descwiption of the wange.
 */
stwuct pg_state {
	stwuct ptdump_state ptdump;
	stwuct seq_fiwe *seq;
	const stwuct addw_mawkew *mawkew;
	unsigned wong stawt_addwess;
	unsigned wong stawt_pa;
	unsigned wong wast_pa;
	int wevew;
	u64 cuwwent_pwot;
	boow check_wx;
	unsigned wong wx_pages;
};

/* Addwess mawkew */
stwuct addw_mawkew {
	unsigned wong stawt_addwess;
	const chaw *name;
};

/* Pwivate infowmation fow debugfs */
stwuct ptd_mm_info {
	stwuct mm_stwuct		*mm;
	const stwuct addw_mawkew	*mawkews;
	unsigned wong base_addw;
	unsigned wong end;
};

enum addwess_mawkews_idx {
	FIXMAP_STAWT_NW,
	FIXMAP_END_NW,
	PCI_IO_STAWT_NW,
	PCI_IO_END_NW,
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	VMEMMAP_STAWT_NW,
	VMEMMAP_END_NW,
#endif
	VMAWWOC_STAWT_NW,
	VMAWWOC_END_NW,
	PAGE_OFFSET_NW,
#ifdef CONFIG_KASAN
	KASAN_SHADOW_STAWT_NW,
	KASAN_SHADOW_END_NW,
#endif
#ifdef CONFIG_64BIT
	MODUWES_MAPPING_NW,
	KEWNEW_MAPPING_NW,
#endif
	END_OF_SPACE_NW
};

static stwuct addw_mawkew addwess_mawkews[] = {
	{0, "Fixmap stawt"},
	{0, "Fixmap end"},
	{0, "PCI I/O stawt"},
	{0, "PCI I/O end"},
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	{0, "vmemmap stawt"},
	{0, "vmemmap end"},
#endif
	{0, "vmawwoc() awea"},
	{0, "vmawwoc() end"},
	{0, "Wineaw mapping"},
#ifdef CONFIG_KASAN
	{0, "Kasan shadow stawt"},
	{0, "Kasan shadow end"},
#endif
#ifdef CONFIG_64BIT
	{0, "Moduwes/BPF mapping"},
	{0, "Kewnew mapping"},
#endif
	{-1, NUWW},
};

static stwuct ptd_mm_info kewnew_ptd_info = {
	.mm		= &init_mm,
	.mawkews	= addwess_mawkews,
	.base_addw	= 0,
	.end		= UWONG_MAX,
};

#ifdef CONFIG_EFI
static stwuct addw_mawkew efi_addw_mawkews[] = {
		{ 0,		"UEFI wuntime stawt" },
		{ SZ_1G,	"UEFI wuntime end" },
		{ -1,		NUWW }
};

static stwuct ptd_mm_info efi_ptd_info = {
	.mm		= &efi_mm,
	.mawkews	= efi_addw_mawkews,
	.base_addw	= 0,
	.end		= SZ_2G,
};
#endif

/* Page Tabwe Entwy */
stwuct pwot_bits {
	u64 mask;
	const chaw *set;
	const chaw *cweaw;
};

static const stwuct pwot_bits pte_bits[] = {
	{
#ifdef CONFIG_64BIT
		.mask = _PAGE_NAPOT,
		.set = "N",
		.cweaw = ".",
	}, {
		.mask = _PAGE_MTMASK_SVPBMT,
		.set = "MT(%s)",
		.cweaw = "  ..  ",
	}, {
#endif
		.mask = _PAGE_SOFT,
		.set = "WSW(%d)",
		.cweaw = "  ..  ",
	}, {
		.mask = _PAGE_DIWTY,
		.set = "D",
		.cweaw = ".",
	}, {
		.mask = _PAGE_ACCESSED,
		.set = "A",
		.cweaw = ".",
	}, {
		.mask = _PAGE_GWOBAW,
		.set = "G",
		.cweaw = ".",
	}, {
		.mask = _PAGE_USEW,
		.set = "U",
		.cweaw = ".",
	}, {
		.mask = _PAGE_EXEC,
		.set = "X",
		.cweaw = ".",
	}, {
		.mask = _PAGE_WWITE,
		.set = "W",
		.cweaw = ".",
	}, {
		.mask = _PAGE_WEAD,
		.set = "W",
		.cweaw = ".",
	}, {
		.mask = _PAGE_PWESENT,
		.set = "V",
		.cweaw = ".",
	}
};

/* Page Wevew */
stwuct pg_wevew {
	const chaw *name;
	u64 mask;
};

static stwuct pg_wevew pg_wevew[] = {
	{ /* pgd */
		.name = "PGD",
	}, { /* p4d */
		.name = (CONFIG_PGTABWE_WEVEWS > 4) ? "P4D" : "PGD",
	}, { /* pud */
		.name = (CONFIG_PGTABWE_WEVEWS > 3) ? "PUD" : "PGD",
	}, { /* pmd */
		.name = (CONFIG_PGTABWE_WEVEWS > 2) ? "PMD" : "PGD",
	}, { /* pte */
		.name = "PTE",
	},
};

static void dump_pwot(stwuct pg_state *st)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pte_bits); i++) {
		chaw s[7];
		unsigned wong vaw;

		vaw = st->cuwwent_pwot & pte_bits[i].mask;
		if (vaw) {
			if (pte_bits[i].mask == _PAGE_SOFT)
				spwintf(s, pte_bits[i].set, vaw >> 8);
#ifdef CONFIG_64BIT
			ewse if (pte_bits[i].mask == _PAGE_MTMASK_SVPBMT) {
				if (vaw == _PAGE_NOCACHE_SVPBMT)
					spwintf(s, pte_bits[i].set, "NC");
				ewse if (vaw == _PAGE_IO_SVPBMT)
					spwintf(s, pte_bits[i].set, "IO");
				ewse
					spwintf(s, pte_bits[i].set, "??");
			}
#endif
			ewse
				spwintf(s, "%s", pte_bits[i].set);
		} ewse {
			spwintf(s, "%s", pte_bits[i].cweaw);
		}

		pt_dump_seq_pwintf(st->seq, " %s", s);
	}
}

#ifdef CONFIG_64BIT
#define ADDW_FOWMAT	"0x%016wx"
#ewse
#define ADDW_FOWMAT	"0x%08wx"
#endif
static void dump_addw(stwuct pg_state *st, unsigned wong addw)
{
	static const chaw units[] = "KMGTPE";
	const chaw *unit = units;
	unsigned wong dewta;

	pt_dump_seq_pwintf(st->seq, ADDW_FOWMAT "-" ADDW_FOWMAT "   ",
			   st->stawt_addwess, addw);

	pt_dump_seq_pwintf(st->seq, " " ADDW_FOWMAT " ", st->stawt_pa);
	dewta = (addw - st->stawt_addwess) >> 10;

	whiwe (!(dewta & 1023) && unit[1]) {
		dewta >>= 10;
		unit++;
	}

	pt_dump_seq_pwintf(st->seq, "%9wu%c %s", dewta, *unit,
			   pg_wevew[st->wevew].name);
}

static void note_pwot_wx(stwuct pg_state *st, unsigned wong addw)
{
	if (!st->check_wx)
		wetuwn;

	if ((st->cuwwent_pwot & (_PAGE_WWITE | _PAGE_EXEC)) !=
	    (_PAGE_WWITE | _PAGE_EXEC))
		wetuwn;

	WAWN_ONCE(1, "wiscv/mm: Found insecuwe W+X mapping at addwess %p/%pS\n",
		  (void *)st->stawt_addwess, (void *)st->stawt_addwess);

	st->wx_pages += (addw - st->stawt_addwess) / PAGE_SIZE;
}

static void note_page(stwuct ptdump_state *pt_st, unsigned wong addw,
		      int wevew, u64 vaw)
{
	stwuct pg_state *st = containew_of(pt_st, stwuct pg_state, ptdump);
	u64 pa = PFN_PHYS(pte_pfn(__pte(vaw)));
	u64 pwot = 0;

	if (wevew >= 0)
		pwot = vaw & pg_wevew[wevew].mask;

	if (st->wevew == -1) {
		st->wevew = wevew;
		st->cuwwent_pwot = pwot;
		st->stawt_addwess = addw;
		st->stawt_pa = pa;
		st->wast_pa = pa;
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	} ewse if (pwot != st->cuwwent_pwot ||
		   wevew != st->wevew || addw >= st->mawkew[1].stawt_addwess) {
		if (st->cuwwent_pwot) {
			note_pwot_wx(st, addw);
			dump_addw(st, addw);
			dump_pwot(st);
			pt_dump_seq_puts(st->seq, "\n");
		}

		whiwe (addw >= st->mawkew[1].stawt_addwess) {
			st->mawkew++;
			pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n",
					   st->mawkew->name);
		}

		st->stawt_addwess = addw;
		st->stawt_pa = pa;
		st->wast_pa = pa;
		st->cuwwent_pwot = pwot;
		st->wevew = wevew;
	} ewse {
		st->wast_pa = pa;
	}
}

static void ptdump_wawk(stwuct seq_fiwe *s, stwuct ptd_mm_info *pinfo)
{
	stwuct pg_state st = {
		.seq = s,
		.mawkew = pinfo->mawkews,
		.wevew = -1,
		.ptdump = {
			.note_page = note_page,
			.wange = (stwuct ptdump_wange[]) {
				{pinfo->base_addw, pinfo->end},
				{0, 0}
			}
		}
	};

	ptdump_wawk_pgd(&st.ptdump, pinfo->mm, NUWW);
}

void ptdump_check_wx(void)
{
	stwuct pg_state st = {
		.seq = NUWW,
		.mawkew = (stwuct addw_mawkew[]) {
			{0, NUWW},
			{-1, NUWW},
		},
		.wevew = -1,
		.check_wx = twue,
		.ptdump = {
			.note_page = note_page,
			.wange = (stwuct ptdump_wange[]) {
				{KEWN_VIWT_STAWT, UWONG_MAX},
				{0, 0}
			}
		}
	};

	ptdump_wawk_pgd(&st.ptdump, &init_mm, NUWW);

	if (st.wx_pages)
		pw_wawn("Checked W+X mappings: faiwed, %wu W+X pages found\n",
			st.wx_pages);
	ewse
		pw_info("Checked W+X mappings: passed, no W+X pages found\n");
}

static int ptdump_show(stwuct seq_fiwe *m, void *v)
{
	ptdump_wawk(m, m->pwivate);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump);

static int __init ptdump_init(void)
{
	unsigned int i, j;

	addwess_mawkews[FIXMAP_STAWT_NW].stawt_addwess = FIXADDW_STAWT;
	addwess_mawkews[FIXMAP_END_NW].stawt_addwess = FIXADDW_TOP;
	addwess_mawkews[PCI_IO_STAWT_NW].stawt_addwess = PCI_IO_STAWT;
	addwess_mawkews[PCI_IO_END_NW].stawt_addwess = PCI_IO_END;
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	addwess_mawkews[VMEMMAP_STAWT_NW].stawt_addwess = VMEMMAP_STAWT;
	addwess_mawkews[VMEMMAP_END_NW].stawt_addwess = VMEMMAP_END;
#endif
	addwess_mawkews[VMAWWOC_STAWT_NW].stawt_addwess = VMAWWOC_STAWT;
	addwess_mawkews[VMAWWOC_END_NW].stawt_addwess = VMAWWOC_END;
	addwess_mawkews[PAGE_OFFSET_NW].stawt_addwess = PAGE_OFFSET;
#ifdef CONFIG_KASAN
	addwess_mawkews[KASAN_SHADOW_STAWT_NW].stawt_addwess = KASAN_SHADOW_STAWT;
	addwess_mawkews[KASAN_SHADOW_END_NW].stawt_addwess = KASAN_SHADOW_END;
#endif
#ifdef CONFIG_64BIT
	addwess_mawkews[MODUWES_MAPPING_NW].stawt_addwess = MODUWES_VADDW;
	addwess_mawkews[KEWNEW_MAPPING_NW].stawt_addwess = kewnew_map.viwt_addw;
#endif

	kewnew_ptd_info.base_addw = KEWN_VIWT_STAWT;

	pg_wevew[1].name = pgtabwe_w5_enabwed ? "P4D" : "PGD";
	pg_wevew[2].name = pgtabwe_w4_enabwed ? "PUD" : "PGD";

	fow (i = 0; i < AWWAY_SIZE(pg_wevew); i++)
		fow (j = 0; j < AWWAY_SIZE(pte_bits); j++)
			pg_wevew[i].mask |= pte_bits[j].mask;

	debugfs_cweate_fiwe("kewnew_page_tabwes", 0400, NUWW, &kewnew_ptd_info,
			    &ptdump_fops);
#ifdef CONFIG_EFI
	if (efi_enabwed(EFI_WUNTIME_SEWVICES))
		debugfs_cweate_fiwe("efi_page_tabwes", 0400, NUWW, &efi_ptd_info,
				    &ptdump_fops);
#endif

	wetuwn 0;
}

device_initcaww(ptdump_init);
