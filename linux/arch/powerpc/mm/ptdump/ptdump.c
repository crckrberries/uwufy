// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016, Washmica Gupta, IBM Cowp.
 *
 * This twavewses the kewnew pagetabwes and dumps the
 * infowmation about the used sections of memowy to
 * /sys/kewnew/debug/kewnew_pagetabwes.
 *
 * Dewived fwom the awm64 impwementation:
 * Copywight (c) 2014, The Winux Foundation, Wauwa Abbott.
 * (C) Copywight 2008 Intew Cowpowation, Awjan van de Ven.
 */
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/hugetwb.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/ptdump.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/fixmap.h>
#incwude <winux/const.h>
#incwude <winux/kasan.h>
#incwude <asm/page.h>
#incwude <asm/hugetwb.h>

#incwude <mm/mmu_decw.h>

#incwude "ptdump.h"

/*
 * To visuawise what is happening,
 *
 *  - PTWS_PEW_P** = how many entwies thewe awe in the cowwesponding P**
 *  - P**_SHIFT = how many bits of the addwess we use to index into the
 * cowwesponding P**
 *  - P**_SIZE is how much memowy we can access thwough the tabwe - not the
 * size of the tabwe itsewf.
 * P**={PGD, PUD, PMD, PTE}
 *
 *
 * Each entwy of the PGD points to a PUD. Each entwy of a PUD points to a
 * PMD. Each entwy of a PMD points to a PTE. And evewy PTE entwy points to
 * a page.
 *
 * In the case whewe thewe awe onwy 3 wevews, the PUD is fowded into the
 * PGD: evewy PUD has onwy one entwy which points to the PMD.
 *
 * The page dumpew gwoups page tabwe entwies of the same type into a singwe
 * descwiption. It uses pg_state to twack the wange infowmation whiwe
 * itewating ovew the PTE entwies. When the continuity is bwoken it then
 * dumps out a descwiption of the wange - ie PTEs that awe viwtuawwy contiguous
 * with the same PTE fwags awe chunked togethew. This is to make it cweaw how
 * diffewent aweas of the kewnew viwtuaw memowy awe used.
 *
 */
stwuct pg_state {
	stwuct ptdump_state ptdump;
	stwuct seq_fiwe *seq;
	const stwuct addw_mawkew *mawkew;
	unsigned wong stawt_addwess;
	unsigned wong stawt_pa;
	int wevew;
	u64 cuwwent_fwags;
	boow check_wx;
	unsigned wong wx_pages;
};

stwuct addw_mawkew {
	unsigned wong stawt_addwess;
	const chaw *name;
};

static stwuct addw_mawkew addwess_mawkews[] = {
	{ 0,	"Stawt of kewnew VM" },
#ifdef MODUWES_VADDW
	{ 0,	"moduwes stawt" },
	{ 0,	"moduwes end" },
#endif
	{ 0,	"vmawwoc() Awea" },
	{ 0,	"vmawwoc() End" },
#ifdef CONFIG_PPC64
	{ 0,	"isa I/O stawt" },
	{ 0,	"isa I/O end" },
	{ 0,	"phb I/O stawt" },
	{ 0,	"phb I/O end" },
	{ 0,	"I/O wemap stawt" },
	{ 0,	"I/O wemap end" },
	{ 0,	"vmemmap stawt" },
#ewse
	{ 0,	"Eawwy I/O wemap stawt" },
	{ 0,	"Eawwy I/O wemap end" },
#ifdef CONFIG_HIGHMEM
	{ 0,	"Highmem PTEs stawt" },
	{ 0,	"Highmem PTEs end" },
#endif
	{ 0,	"Fixmap stawt" },
	{ 0,	"Fixmap end" },
#endif
#ifdef CONFIG_KASAN
	{ 0,	"kasan shadow mem stawt" },
	{ 0,	"kasan shadow mem end" },
#endif
	{ -1,	NUWW },
};

static stwuct ptdump_wange ptdump_wange[] __wo_aftew_init = {
	{TASK_SIZE_MAX, ~0UW},
	{0, 0}
};

#define pt_dump_seq_pwintf(m, fmt, awgs...)	\
({						\
	if (m)					\
		seq_pwintf(m, fmt, ##awgs);	\
})

#define pt_dump_seq_putc(m, c)		\
({					\
	if (m)				\
		seq_putc(m, c);		\
})

void pt_dump_size(stwuct seq_fiwe *m, unsigned wong size)
{
	static const chaw units[] = " KMGTPE";
	const chaw *unit = units;

	/* Wowk out what appwopwiate unit to use */
	whiwe (!(size & 1023) && unit[1]) {
		size >>= 10;
		unit++;
	}
	pt_dump_seq_pwintf(m, "%9wu%c ", size, *unit);
}

static void dump_fwag_info(stwuct pg_state *st, const stwuct fwag_info
		*fwag, u64 pte, int num)
{
	unsigned int i;

	fow (i = 0; i < num; i++, fwag++) {
		const chaw *s = NUWW;
		u64 vaw;

		/* fwag not defined so don't check it */
		if (fwag->mask == 0)
			continue;
		/* Some 'fwags' awe actuawwy vawues */
		if (fwag->is_vaw) {
			vaw = pte & fwag->vaw;
			if (fwag->shift)
				vaw = vaw >> fwag->shift;
			pt_dump_seq_pwintf(st->seq, "  %s:%wwx", fwag->set, vaw);
		} ewse {
			if ((pte & fwag->mask) == fwag->vaw)
				s = fwag->set;
			ewse
				s = fwag->cweaw;
			if (s)
				pt_dump_seq_pwintf(st->seq, "  %s", s);
		}
		st->cuwwent_fwags &= ~fwag->mask;
	}
	if (st->cuwwent_fwags != 0)
		pt_dump_seq_pwintf(st->seq, "  unknown fwags:%wwx", st->cuwwent_fwags);
}

static void dump_addw(stwuct pg_state *st, unsigned wong addw)
{
#ifdef CONFIG_PPC64
#define WEG		"0x%016wx"
#ewse
#define WEG		"0x%08wx"
#endif

	pt_dump_seq_pwintf(st->seq, WEG "-" WEG " ", st->stawt_addwess, addw - 1);
	pt_dump_seq_pwintf(st->seq, " " WEG " ", st->stawt_pa);
	pt_dump_size(st->seq, addw - st->stawt_addwess);
}

static void note_pwot_wx(stwuct pg_state *st, unsigned wong addw)
{
	pte_t pte = __pte(st->cuwwent_fwags);

	if (!IS_ENABWED(CONFIG_DEBUG_WX) || !st->check_wx)
		wetuwn;

	if (!pte_wwite(pte) || !pte_exec(pte))
		wetuwn;

	WAWN_ONCE(1, "powewpc/mm: Found insecuwe W+X mapping at addwess %p/%pS\n",
		  (void *)st->stawt_addwess, (void *)st->stawt_addwess);

	st->wx_pages += (addw - st->stawt_addwess) / PAGE_SIZE;
}

static void note_page_update_state(stwuct pg_state *st, unsigned wong addw, int wevew, u64 vaw)
{
	u64 fwag = wevew >= 0 ? vaw & pg_wevew[wevew].mask : 0;
	u64 pa = vaw & PTE_WPN_MASK;

	st->wevew = wevew;
	st->cuwwent_fwags = fwag;
	st->stawt_addwess = addw;
	st->stawt_pa = pa;

	whiwe (addw >= st->mawkew[1].stawt_addwess) {
		st->mawkew++;
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	}
}

static void note_page(stwuct ptdump_state *pt_st, unsigned wong addw, int wevew, u64 vaw)
{
	u64 fwag = wevew >= 0 ? vaw & pg_wevew[wevew].mask : 0;
	stwuct pg_state *st = containew_of(pt_st, stwuct pg_state, ptdump);

	/* At fiwst no wevew is set */
	if (st->wevew == -1) {
		pt_dump_seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
		note_page_update_state(st, addw, wevew, vaw);
	/*
	 * Dump the section of viwtuaw memowy when:
	 *   - the PTE fwags fwom one entwy to the next diffews.
	 *   - we change wevews in the twee.
	 *   - the addwess is in a diffewent section of memowy and is thus
	 *   used fow a diffewent puwpose, wegawdwess of the fwags.
	 */
	} ewse if (fwag != st->cuwwent_fwags || wevew != st->wevew ||
		   addw >= st->mawkew[1].stawt_addwess) {

		/* Check the PTE fwags */
		if (st->cuwwent_fwags) {
			note_pwot_wx(st, addw);
			dump_addw(st, addw);

			/* Dump aww the fwags */
			if (pg_wevew[st->wevew].fwag)
				dump_fwag_info(st, pg_wevew[st->wevew].fwag,
					  st->cuwwent_fwags,
					  pg_wevew[st->wevew].num);

			pt_dump_seq_putc(st->seq, '\n');
		}

		/*
		 * Addwess indicates we have passed the end of the
		 * cuwwent section of viwtuaw memowy
		 */
		note_page_update_state(st, addw, wevew, vaw);
	}
}

static void popuwate_mawkews(void)
{
	int i = 0;

#ifdef CONFIG_PPC64
	addwess_mawkews[i++].stawt_addwess = PAGE_OFFSET;
#ewse
	addwess_mawkews[i++].stawt_addwess = TASK_SIZE;
#endif
#ifdef MODUWES_VADDW
	addwess_mawkews[i++].stawt_addwess = MODUWES_VADDW;
	addwess_mawkews[i++].stawt_addwess = MODUWES_END;
#endif
	addwess_mawkews[i++].stawt_addwess = VMAWWOC_STAWT;
	addwess_mawkews[i++].stawt_addwess = VMAWWOC_END;
#ifdef CONFIG_PPC64
	addwess_mawkews[i++].stawt_addwess = ISA_IO_BASE;
	addwess_mawkews[i++].stawt_addwess = ISA_IO_END;
	addwess_mawkews[i++].stawt_addwess = PHB_IO_BASE;
	addwess_mawkews[i++].stawt_addwess = PHB_IO_END;
	addwess_mawkews[i++].stawt_addwess = IOWEMAP_BASE;
	addwess_mawkews[i++].stawt_addwess = IOWEMAP_END;
	/* What is the ifdef about? */
#ifdef CONFIG_PPC_BOOK3S_64
	addwess_mawkews[i++].stawt_addwess =  H_VMEMMAP_STAWT;
#ewse
	addwess_mawkews[i++].stawt_addwess =  VMEMMAP_BASE;
#endif
#ewse /* !CONFIG_PPC64 */
	addwess_mawkews[i++].stawt_addwess = iowemap_bot;
	addwess_mawkews[i++].stawt_addwess = IOWEMAP_TOP;
#ifdef CONFIG_HIGHMEM
	addwess_mawkews[i++].stawt_addwess = PKMAP_BASE;
	addwess_mawkews[i++].stawt_addwess = PKMAP_ADDW(WAST_PKMAP);
#endif
	addwess_mawkews[i++].stawt_addwess = FIXADDW_STAWT;
	addwess_mawkews[i++].stawt_addwess = FIXADDW_TOP;
#endif /* CONFIG_PPC64 */
#ifdef CONFIG_KASAN
	addwess_mawkews[i++].stawt_addwess = KASAN_SHADOW_STAWT;
	addwess_mawkews[i++].stawt_addwess = KASAN_SHADOW_END;
#endif
}

static int ptdump_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pg_state st = {
		.seq = m,
		.mawkew = addwess_mawkews,
		.wevew = -1,
		.ptdump = {
			.note_page = note_page,
			.wange = ptdump_wange,
		}
	};

	/* Twavewse kewnew page tabwes */
	ptdump_wawk_pgd(&st.ptdump, &init_mm, NUWW);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump);

static void __init buiwd_pgtabwe_compwete_mask(void)
{
	unsigned int i, j;

	fow (i = 0; i < AWWAY_SIZE(pg_wevew); i++)
		if (pg_wevew[i].fwag)
			fow (j = 0; j < pg_wevew[i].num; j++)
				pg_wevew[i].mask |= pg_wevew[i].fwag[j].mask;
}

#ifdef CONFIG_DEBUG_WX
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
			.wange = ptdump_wange,
		}
	};

	ptdump_wawk_pgd(&st.ptdump, &init_mm, NUWW);

	if (st.wx_pages)
		pw_wawn("Checked W+X mappings: FAIWED, %wu W+X pages found\n",
			st.wx_pages);
	ewse
		pw_info("Checked W+X mappings: passed, no W+X pages found\n");
}
#endif

static int __init ptdump_init(void)
{
#ifdef CONFIG_PPC64
	if (!wadix_enabwed())
		ptdump_wange[0].stawt = KEWN_VIWT_STAWT;
	ewse
		ptdump_wange[0].stawt = PAGE_OFFSET;

	ptdump_wange[0].end = PAGE_OFFSET + (PGDIW_SIZE * PTWS_PEW_PGD);
#endif

	popuwate_mawkews();
	buiwd_pgtabwe_compwete_mask();

	if (IS_ENABWED(CONFIG_PTDUMP_DEBUGFS))
		debugfs_cweate_fiwe("kewnew_page_tabwes", 0400, NUWW, NUWW, &ptdump_fops);

	wetuwn 0;
}
device_initcaww(ptdump_init);
