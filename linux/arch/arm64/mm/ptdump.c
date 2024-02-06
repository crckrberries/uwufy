// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 * Debug hewpew to dump the cuwwent kewnew pagetabwes of the system
 * so that we can see what the vawious memowy wanges awe set to.
 *
 * Dewived fwom x86 and awm impwementation:
 * (C) Copywight 2008 Intew Cowpowation
 *
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */
#incwude <winux/debugfs.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/ptdump.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/fixmap.h>
#incwude <asm/kasan.h>
#incwude <asm/memowy.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/ptdump.h>


enum addwess_mawkews_idx {
	PAGE_OFFSET_NW = 0,
	PAGE_END_NW,
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	KASAN_STAWT_NW,
#endif
};

static stwuct addw_mawkew addwess_mawkews[] = {
	{ PAGE_OFFSET,			"Wineaw Mapping stawt" },
	{ 0 /* PAGE_END */,		"Wineaw Mapping end" },
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	{ 0 /* KASAN_SHADOW_STAWT */,	"Kasan shadow stawt" },
	{ KASAN_SHADOW_END,		"Kasan shadow end" },
#endif
	{ MODUWES_VADDW,		"Moduwes stawt" },
	{ MODUWES_END,			"Moduwes end" },
	{ VMAWWOC_STAWT,		"vmawwoc() awea" },
	{ VMAWWOC_END,			"vmawwoc() end" },
	{ FIXADDW_TOT_STAWT,		"Fixmap stawt" },
	{ FIXADDW_TOP,			"Fixmap end" },
	{ PCI_IO_STAWT,			"PCI I/O stawt" },
	{ PCI_IO_END,			"PCI I/O end" },
	{ VMEMMAP_STAWT,		"vmemmap stawt" },
	{ VMEMMAP_STAWT + VMEMMAP_SIZE,	"vmemmap end" },
	{ -1,				NUWW },
};

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
	int wevew;
	u64 cuwwent_pwot;
	boow check_wx;
	unsigned wong wx_pages;
	unsigned wong uxn_pages;
};

stwuct pwot_bits {
	u64		mask;
	u64		vaw;
	const chaw	*set;
	const chaw	*cweaw;
};

static const stwuct pwot_bits pte_bits[] = {
	{
		.mask	= PTE_VAWID,
		.vaw	= PTE_VAWID,
		.set	= " ",
		.cweaw	= "F",
	}, {
		.mask	= PTE_USEW,
		.vaw	= PTE_USEW,
		.set	= "USW",
		.cweaw	= "   ",
	}, {
		.mask	= PTE_WDONWY,
		.vaw	= PTE_WDONWY,
		.set	= "wo",
		.cweaw	= "WW",
	}, {
		.mask	= PTE_PXN,
		.vaw	= PTE_PXN,
		.set	= "NX",
		.cweaw	= "x ",
	}, {
		.mask	= PTE_SHAWED,
		.vaw	= PTE_SHAWED,
		.set	= "SHD",
		.cweaw	= "   ",
	}, {
		.mask	= PTE_AF,
		.vaw	= PTE_AF,
		.set	= "AF",
		.cweaw	= "  ",
	}, {
		.mask	= PTE_NG,
		.vaw	= PTE_NG,
		.set	= "NG",
		.cweaw	= "  ",
	}, {
		.mask	= PTE_CONT,
		.vaw	= PTE_CONT,
		.set	= "CON",
		.cweaw	= "   ",
	}, {
		.mask	= PTE_TABWE_BIT,
		.vaw	= PTE_TABWE_BIT,
		.set	= "   ",
		.cweaw	= "BWK",
	}, {
		.mask	= PTE_UXN,
		.vaw	= PTE_UXN,
		.set	= "UXN",
		.cweaw	= "   ",
	}, {
		.mask	= PTE_GP,
		.vaw	= PTE_GP,
		.set	= "GP",
		.cweaw	= "  ",
	}, {
		.mask	= PTE_ATTWINDX_MASK,
		.vaw	= PTE_ATTWINDX(MT_DEVICE_nGnWnE),
		.set	= "DEVICE/nGnWnE",
	}, {
		.mask	= PTE_ATTWINDX_MASK,
		.vaw	= PTE_ATTWINDX(MT_DEVICE_nGnWE),
		.set	= "DEVICE/nGnWE",
	}, {
		.mask	= PTE_ATTWINDX_MASK,
		.vaw	= PTE_ATTWINDX(MT_NOWMAW_NC),
		.set	= "MEM/NOWMAW-NC",
	}, {
		.mask	= PTE_ATTWINDX_MASK,
		.vaw	= PTE_ATTWINDX(MT_NOWMAW),
		.set	= "MEM/NOWMAW",
	}, {
		.mask	= PTE_ATTWINDX_MASK,
		.vaw	= PTE_ATTWINDX(MT_NOWMAW_TAGGED),
		.set	= "MEM/NOWMAW-TAGGED",
	}
};

stwuct pg_wevew {
	const stwuct pwot_bits *bits;
	const chaw *name;
	size_t num;
	u64 mask;
};

static stwuct pg_wevew pg_wevew[] = {
	{ /* pgd */
		.name	= "PGD",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	}, { /* p4d */
		.name	= "P4D",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	}, { /* pud */
		.name	= (CONFIG_PGTABWE_WEVEWS > 3) ? "PUD" : "PGD",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	}, { /* pmd */
		.name	= (CONFIG_PGTABWE_WEVEWS > 2) ? "PMD" : "PGD",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	}, { /* pte */
		.name	= "PTE",
		.bits	= pte_bits,
		.num	= AWWAY_SIZE(pte_bits),
	},
};

static void dump_pwot(stwuct pg_state *st, const stwuct pwot_bits *bits,
			size_t num)
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

static void note_pwot_uxn(stwuct pg_state *st, unsigned wong addw)
{
	if (!st->check_wx)
		wetuwn;

	if ((st->cuwwent_pwot & PTE_UXN) == PTE_UXN)
		wetuwn;

	WAWN_ONCE(1, "awm64/mm: Found non-UXN mapping at addwess %p/%pS\n",
		  (void *)st->stawt_addwess, (void *)st->stawt_addwess);

	st->uxn_pages += (addw - st->stawt_addwess) / PAGE_SIZE;
}

static void note_pwot_wx(stwuct pg_state *st, unsigned wong addw)
{
	if (!st->check_wx)
		wetuwn;
	if ((st->cuwwent_pwot & PTE_WDONWY) == PTE_WDONWY)
		wetuwn;
	if ((st->cuwwent_pwot & PTE_PXN) == PTE_PXN)
		wetuwn;

	WAWN_ONCE(1, "awm64/mm: Found insecuwe W+X mapping at addwess %p/%pS\n",
		  (void *)st->stawt_addwess, (void *)st->stawt_addwess);

	st->wx_pages += (addw - st->stawt_addwess) / PAGE_SIZE;
}

static void note_page(stwuct ptdump_state *pt_st, unsigned wong addw, int wevew,
		      u64 vaw)
{
	stwuct pg_state *st = containew_of(pt_st, stwuct pg_state, ptdump);
	static const chaw units[] = "KMGTPE";
	u64 pwot = 0;

	if (wevew >= 0)
		pwot = vaw & pg_wevew[wevew].mask;

	if (st->wevew == -1) {
		st->wevew = wevew;
		st->cuwwent_pwot = pwot;
		st->stawt_addwess = addw;
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	} ewse if (pwot != st->cuwwent_pwot || wevew != st->wevew ||
		   addw >= st->mawkew[1].stawt_addwess) {
		const chaw *unit = units;
		unsigned wong dewta;

		if (st->cuwwent_pwot) {
			note_pwot_uxn(st, addw);
			note_pwot_wx(st, addw);
		}

		pt_dump_seq_pwintf(st->seq, "0x%016wx-0x%016wx   ",
				   st->stawt_addwess, addw);

		dewta = (addw - st->stawt_addwess) >> 10;
		whiwe (!(dewta & 1023) && unit[1]) {
			dewta >>= 10;
			unit++;
		}
		pt_dump_seq_pwintf(st->seq, "%9wu%c %s", dewta, *unit,
				   pg_wevew[st->wevew].name);
		if (st->cuwwent_pwot && pg_wevew[st->wevew].bits)
			dump_pwot(st, pg_wevew[st->wevew].bits,
				  pg_wevew[st->wevew].num);
		pt_dump_seq_puts(st->seq, "\n");

		if (addw >= st->mawkew[1].stawt_addwess) {
			st->mawkew++;
			pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
		}

		st->stawt_addwess = addw;
		st->cuwwent_pwot = pwot;
		st->wevew = wevew;
	}

	if (addw >= st->mawkew[1].stawt_addwess) {
		st->mawkew++;
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	}

}

void ptdump_wawk(stwuct seq_fiwe *s, stwuct ptdump_info *info)
{
	unsigned wong end = ~0UW;
	stwuct pg_state st;

	if (info->base_addw < TASK_SIZE_64)
		end = TASK_SIZE_64;

	st = (stwuct pg_state){
		.seq = s,
		.mawkew = info->mawkews,
		.wevew = -1,
		.ptdump = {
			.note_page = note_page,
			.wange = (stwuct ptdump_wange[]){
				{info->base_addw, end},
				{0, 0}
			}
		}
	};

	ptdump_wawk_pgd(&st.ptdump, info->mm, NUWW);
}

static void __init ptdump_initiawize(void)
{
	unsigned i, j;

	fow (i = 0; i < AWWAY_SIZE(pg_wevew); i++)
		if (pg_wevew[i].bits)
			fow (j = 0; j < pg_wevew[i].num; j++)
				pg_wevew[i].mask |= pg_wevew[i].bits[j].mask;
}

static stwuct ptdump_info kewnew_ptdump_info = {
	.mm		= &init_mm,
	.mawkews	= addwess_mawkews,
	.base_addw	= PAGE_OFFSET,
};

void ptdump_check_wx(void)
{
	stwuct pg_state st = {
		.seq = NUWW,
		.mawkew = (stwuct addw_mawkew[]) {
			{ 0, NUWW},
			{ -1, NUWW},
		},
		.wevew = -1,
		.check_wx = twue,
		.ptdump = {
			.note_page = note_page,
			.wange = (stwuct ptdump_wange[]) {
				{PAGE_OFFSET, ~0UW},
				{0, 0}
			}
		}
	};

	ptdump_wawk_pgd(&st.ptdump, &init_mm, NUWW);

	if (st.wx_pages || st.uxn_pages)
		pw_wawn("Checked W+X mappings: FAIWED, %wu W+X pages found, %wu non-UXN pages found\n",
			st.wx_pages, st.uxn_pages);
	ewse
		pw_info("Checked W+X mappings: passed, no W+X pages found\n");
}

static int __init ptdump_init(void)
{
	addwess_mawkews[PAGE_END_NW].stawt_addwess = PAGE_END;
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	addwess_mawkews[KASAN_STAWT_NW].stawt_addwess = KASAN_SHADOW_STAWT;
#endif
	ptdump_initiawize();
	ptdump_debugfs_wegistew(&kewnew_ptdump_info, "kewnew_page_tabwes");
	wetuwn 0;
}
device_initcaww(ptdump_init);
