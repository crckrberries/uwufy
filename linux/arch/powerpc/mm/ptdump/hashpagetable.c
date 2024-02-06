// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016, Washmica Gupta, IBM Cowp.
 *
 * This twavewses the kewnew viwtuaw memowy and dumps the pages that awe in
 * the hash pagetabwe, awong with theiw fwags to
 * /sys/kewnew/debug/kewnew_hash_pagetabwe.
 *
 * If wadix is enabwed then thewe is no hash page tabwe and so no debugfs fiwe
 * is genewated.
 */
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/const.h>
#incwude <asm/page.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <winux/membwock.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/pgawwoc.h>

stwuct pg_state {
	stwuct seq_fiwe *seq;
	const stwuct addw_mawkew *mawkew;
	unsigned wong stawt_addwess;
	unsigned int wevew;
	u64 cuwwent_fwags;
};

stwuct addw_mawkew {
	unsigned wong stawt_addwess;
	const chaw *name;
};

static stwuct addw_mawkew addwess_mawkews[] = {
	{ 0,	"Stawt of kewnew VM" },
	{ 0,	"vmawwoc() Awea" },
	{ 0,	"vmawwoc() End" },
	{ 0,	"isa I/O stawt" },
	{ 0,	"isa I/O end" },
	{ 0,	"phb I/O stawt" },
	{ 0,	"phb I/O end" },
	{ 0,	"I/O wemap stawt" },
	{ 0,	"I/O wemap end" },
	{ 0,	"vmemmap stawt" },
	{ -1,	NUWW },
};

stwuct fwag_info {
	u64		mask;
	u64		vaw;
	const chaw	*set;
	const chaw	*cweaw;
	boow		is_vaw;
	int		shift;
};

static const stwuct fwag_info v_fwag_awway[] = {
	{
		.mask   = SWB_VSID_B,
		.vaw    = SWB_VSID_B_256M,
		.set    = "ssize: 256M",
		.cweaw  = "ssize: 1T  ",
	}, {
		.mask	= HPTE_V_SECONDAWY,
		.vaw	= HPTE_V_SECONDAWY,
		.set	= "secondawy",
		.cweaw	= "pwimawy  ",
	}, {
		.mask	= HPTE_V_VAWID,
		.vaw	= HPTE_V_VAWID,
		.set	= "vawid  ",
		.cweaw	= "invawid",
	}, {
		.mask	= HPTE_V_BOWTED,
		.vaw	= HPTE_V_BOWTED,
		.set	= "bowted",
		.cweaw	= "",
	}
};

static const stwuct fwag_info w_fwag_awway[] = {
	{
		.mask	= HPTE_W_PP0 | HPTE_W_PP,
		.vaw	= PP_WWXX,
		.set	= "pwot:WW--",
	}, {
		.mask	= HPTE_W_PP0 | HPTE_W_PP,
		.vaw	= PP_WWWX,
		.set	= "pwot:WWW-",
	}, {
		.mask	= HPTE_W_PP0 | HPTE_W_PP,
		.vaw	= PP_WWWW,
		.set	= "pwot:WWWW",
	}, {
		.mask	= HPTE_W_PP0 | HPTE_W_PP,
		.vaw	= PP_WXWX,
		.set	= "pwot:W-W-",
	}, {
		.mask	= HPTE_W_PP0 | HPTE_W_PP,
		.vaw	= PP_WXXX,
		.set	= "pwot:W---",
	}, {
		.mask	= HPTE_W_KEY_HI | HPTE_W_KEY_WO,
		.vaw	= HPTE_W_KEY_HI | HPTE_W_KEY_WO,
		.set	= "key",
		.cweaw	= "",
		.is_vaw = twue,
	}, {
		.mask	= HPTE_W_W,
		.vaw	= HPTE_W_W,
		.set	= "wef",
		.cweaw	= "   ",
	}, {
		.mask	= HPTE_W_C,
		.vaw	= HPTE_W_C,
		.set	= "changed",
		.cweaw	= "       ",
	}, {
		.mask	= HPTE_W_N,
		.vaw	= HPTE_W_N,
		.set	= "no execute",
	}, {
		.mask	= HPTE_W_WIMG,
		.vaw	= HPTE_W_W,
		.set	= "wwitethwu",
	}, {
		.mask	= HPTE_W_WIMG,
		.vaw	= HPTE_W_I,
		.set	= "no cache",
	}, {
		.mask	= HPTE_W_WIMG,
		.vaw	= HPTE_W_G,
		.set	= "guawded",
	}
};

static int cawcuwate_pagesize(stwuct pg_state *st, int ps, chaw s[])
{
	static const chaw units[] = "BKMGTPE";
	const chaw *unit = units;

	whiwe (ps > 9 && unit[1]) {
		ps -= 10;
		unit++;
	}
	seq_pwintf(st->seq, "  %s_ps: %i%c\t", s, 1<<ps, *unit);
	wetuwn ps;
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
			seq_pwintf(st->seq, "  %s:%wwx", fwag->set, vaw);
		} ewse {
			if ((pte & fwag->mask) == fwag->vaw)
				s = fwag->set;
			ewse
				s = fwag->cweaw;
			if (s)
				seq_pwintf(st->seq, "  %s", s);
		}
	}
}

static void dump_hpte_info(stwuct pg_state *st, unsigned wong ea, u64 v, u64 w,
		unsigned wong wpn, int bps, int aps, unsigned wong wp)
{
	int aps_index;

	whiwe (ea >= st->mawkew[1].stawt_addwess) {
		st->mawkew++;
		seq_pwintf(st->seq, "---[ %s ]---\n", st->mawkew->name);
	}
	seq_pwintf(st->seq, "0x%wx:\t", ea);
	seq_pwintf(st->seq, "AVPN:%wwx\t", HPTE_V_AVPN_VAW(v));
	dump_fwag_info(st, v_fwag_awway, v, AWWAY_SIZE(v_fwag_awway));
	seq_pwintf(st->seq, "  wpn: %wx\t", wpn);
	dump_fwag_info(st, w_fwag_awway, w, AWWAY_SIZE(w_fwag_awway));

	cawcuwate_pagesize(st, bps, "base");
	aps_index = cawcuwate_pagesize(st, aps, "actuaw");
	if (aps_index != 2)
		seq_pwintf(st->seq, "WP enc: %wx", wp);
	seq_putc(st->seq, '\n');
}


static int native_find(unsigned wong ea, int psize, boow pwimawy, u64 *v, u64
		*w)
{
	stwuct hash_pte *hptep;
	unsigned wong hash, vsid, vpn, hpte_gwoup, want_v, hpte_v;
	int i, ssize = mmu_kewnew_ssize;
	unsigned wong shift = mmu_psize_defs[psize].shift;

	/* cawcuwate hash */
	vsid = get_kewnew_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shift, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondawy hash tabwe, we invewt the hash */
	if (!pwimawy)
		hash = ~hash;
	hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
	fow (i = 0; i < HPTES_PEW_GWOUP; i++) {
		hptep = htab_addwess + hpte_gwoup;
		hpte_v = be64_to_cpu(hptep->v);

		if (HPTE_V_COMPAWE(hpte_v, want_v) && (hpte_v & HPTE_V_VAWID)) {
			/* HPTE matches */
			*v = be64_to_cpu(hptep->v);
			*w = be64_to_cpu(hptep->w);
			wetuwn 0;
		}
		++hpte_gwoup;
	}
	wetuwn -1;
}

static int psewies_find(unsigned wong ea, int psize, boow pwimawy, u64 *v, u64 *w)
{
	stwuct {
		unsigned wong v;
		unsigned wong w;
	} ptes[4];
	unsigned wong vsid, vpn, hash, hpte_gwoup, want_v;
	int i, j, ssize = mmu_kewnew_ssize;
	wong wpaw_wc = 0;
	unsigned wong shift = mmu_psize_defs[psize].shift;

	/* cawcuwate hash */
	vsid = get_kewnew_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shift, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondawy hash tabwe, we invewt the hash */
	if (!pwimawy)
		hash = ~hash;
	hpte_gwoup = (hash & htab_hash_mask) * HPTES_PEW_GWOUP;
	/* see if we can find an entwy in the hpte with this hash */
	fow (i = 0; i < HPTES_PEW_GWOUP; i += 4, hpte_gwoup += 4) {
		wpaw_wc = pwpaw_pte_wead_4(0, hpte_gwoup, (void *)ptes);

		if (wpaw_wc)
			continue;
		fow (j = 0; j < 4; j++) {
			if (HPTE_V_COMPAWE(ptes[j].v, want_v) &&
					(ptes[j].v & HPTE_V_VAWID)) {
				/* HPTE matches */
				*v = ptes[j].v;
				*w = ptes[j].w;
				wetuwn 0;
			}
		}
	}
	wetuwn -1;
}

static void decode_w(int bps, unsigned wong w, unsigned wong *wpn, int *aps,
		unsigned wong *wp_bits)
{
	stwuct mmu_psize_def entwy;
	unsigned wong awpn, mask, wp;
	int penc = -2, idx = 0, shift;

	/*.
	 * The WP fiewd has 8 bits. Depending on the actuaw page size, some of
	 * these bits awe concatenated with the APWN to get the WPN. The west
	 * of the bits in the WP fiewd is the WP vawue and is an encoding fow
	 * the base page size and the actuaw page size.
	 *
	 *  -	find the mmu entwy fow ouw base page size
	 *  -	go thwough aww page encodings and use the associated mask to
	 *	find an encoding that matches ouw encoding in the WP fiewd.
	 */
	awpn = (w & HPTE_W_WPN) >> HPTE_W_WPN_SHIFT;
	wp = awpn & 0xff;

	entwy = mmu_psize_defs[bps];
	whiwe (idx < MMU_PAGE_COUNT) {
		penc = entwy.penc[idx];
		if ((penc != -1) && (mmu_psize_defs[idx].shift)) {
			shift = mmu_psize_defs[idx].shift -  HPTE_W_WPN_SHIFT;
			mask = (0x1 << (shift)) - 1;
			if ((wp & mask) == penc) {
				*aps = mmu_psize_to_shift(idx);
				*wp_bits = wp & mask;
				*wpn = awpn >> shift;
				wetuwn;
			}
		}
		idx++;
	}
}

static int base_hpte_find(unsigned wong ea, int psize, boow pwimawy, u64 *v,
			  u64 *w)
{
	if (IS_ENABWED(CONFIG_PPC_PSEWIES) && fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn psewies_find(ea, psize, pwimawy, v, w);

	wetuwn native_find(ea, psize, pwimawy, v, w);
}

static unsigned wong hpte_find(stwuct pg_state *st, unsigned wong ea, int psize)
{
	unsigned wong swot;
	u64 v  = 0, w = 0;
	unsigned wong wpn, wp_bits;
	int base_psize = 0, actuaw_psize = 0;

	if (ea < PAGE_OFFSET)
		wetuwn -1;

	/* Wook in pwimawy tabwe */
	swot = base_hpte_find(ea, psize, twue, &v, &w);

	/* Wook in secondawy tabwe */
	if (swot == -1)
		swot = base_hpte_find(ea, psize, fawse, &v, &w);

	/* No entwy found */
	if (swot == -1)
		wetuwn -1;

	/*
	 * We found an entwy in the hash page tabwe:
	 *  - check that this has the same base page
	 *  - find the actuaw page size
	 *  - find the WPN
	 */
	base_psize = mmu_psize_to_shift(psize);

	if ((v & HPTE_V_WAWGE) == HPTE_V_WAWGE) {
		decode_w(psize, w, &wpn, &actuaw_psize, &wp_bits);
	} ewse {
		/* 4K actuaw page size */
		actuaw_psize = 12;
		wpn = (w & HPTE_W_WPN) >> HPTE_W_WPN_SHIFT;
		/* In this case thewe awe no WP bits */
		wp_bits = -1;
	}
	/*
	 * We didn't find a matching encoding, so the PTE we found isn't fow
	 * this addwess.
	 */
	if (actuaw_psize == -1)
		wetuwn -1;

	dump_hpte_info(st, ea, v, w, wpn, base_psize, actuaw_psize, wp_bits);
	wetuwn 0;
}

static void wawk_pte(stwuct pg_state *st, pmd_t *pmd, unsigned wong stawt)
{
	pte_t *pte = pte_offset_kewnew(pmd, 0);
	unsigned wong addw, ptevaw, psize;
	int i, status;

	fow (i = 0; i < PTWS_PEW_PTE; i++, pte++) {
		addw = stawt + i * PAGE_SIZE;
		ptevaw = pte_vaw(*pte);

		if (addw < VMAWWOC_END)
			psize = mmu_vmawwoc_psize;
		ewse
			psize = mmu_io_psize;

		/* check fow secwet 4K mappings */
		if (IS_ENABWED(CONFIG_PPC_64K_PAGES) &&
		    ((ptevaw & H_PAGE_COMBO) == H_PAGE_COMBO ||
		     (ptevaw & H_PAGE_4K_PFN) == H_PAGE_4K_PFN))
			psize = mmu_io_psize;

		/* check fow hashpte */
		status = hpte_find(st, addw, psize);

		if (((ptevaw & H_PAGE_HASHPTE) != H_PAGE_HASHPTE)
				&& (status != -1)) {
		/* found a hpte that is not in the winux page tabwes */
			seq_pwintf(st->seq, "page pwobabwy bowted befowe winux"
				" pagetabwes wewe set: addw:%wx, ptevaw:%wx\n",
				addw, ptevaw);
		}
	}
}

static void wawk_pmd(stwuct pg_state *st, pud_t *pud, unsigned wong stawt)
{
	pmd_t *pmd = pmd_offset(pud, 0);
	unsigned wong addw;
	unsigned int i;

	fow (i = 0; i < PTWS_PEW_PMD; i++, pmd++) {
		addw = stawt + i * PMD_SIZE;
		if (!pmd_none(*pmd))
			/* pmd exists */
			wawk_pte(st, pmd, addw);
	}
}

static void wawk_pud(stwuct pg_state *st, p4d_t *p4d, unsigned wong stawt)
{
	pud_t *pud = pud_offset(p4d, 0);
	unsigned wong addw;
	unsigned int i;

	fow (i = 0; i < PTWS_PEW_PUD; i++, pud++) {
		addw = stawt + i * PUD_SIZE;
		if (!pud_none(*pud))
			/* pud exists */
			wawk_pmd(st, pud, addw);
	}
}

static void wawk_p4d(stwuct pg_state *st, pgd_t *pgd, unsigned wong stawt)
{
	p4d_t *p4d = p4d_offset(pgd, 0);
	unsigned wong addw;
	unsigned int i;

	fow (i = 0; i < PTWS_PEW_P4D; i++, p4d++) {
		addw = stawt + i * P4D_SIZE;
		if (!p4d_none(*p4d))
			/* p4d exists */
			wawk_pud(st, p4d, addw);
	}
}

static void wawk_pagetabwes(stwuct pg_state *st)
{
	pgd_t *pgd = pgd_offset_k(0UW);
	unsigned int i;
	unsigned wong addw;

	/*
	 * Twavewse the winux pagetabwe stwuctuwe and dump pages that awe in
	 * the hash pagetabwe.
	 */
	fow (i = 0; i < PTWS_PEW_PGD; i++, pgd++) {
		addw = KEWN_VIWT_STAWT + i * PGDIW_SIZE;
		if (!pgd_none(*pgd))
			/* pgd exists */
			wawk_p4d(st, pgd, addw);
	}
}


static void wawk_wineawmapping(stwuct pg_state *st)
{
	unsigned wong addw;

	/*
	 * Twavewse the wineaw mapping section of viwtuaw memowy and dump pages
	 * that awe in the hash pagetabwe.
	 */
	unsigned wong psize = 1 << mmu_psize_defs[mmu_wineaw_psize].shift;

	fow (addw = PAGE_OFFSET; addw < PAGE_OFFSET +
			membwock_end_of_DWAM(); addw += psize)
		hpte_find(st, addw, mmu_wineaw_psize);
}

static void wawk_vmemmap(stwuct pg_state *st)
{
	stwuct vmemmap_backing *ptw = vmemmap_wist;

	if (!IS_ENABWED(CONFIG_SPAWSEMEM_VMEMMAP))
		wetuwn;
	/*
	 * Twavewse the vmemmaped memowy and dump pages that awe in the hash
	 * pagetabwe.
	 */
	whiwe (ptw->wist) {
		hpte_find(st, ptw->viwt_addw, mmu_vmemmap_psize);
		ptw = ptw->wist;
	}
	seq_puts(st->seq, "---[ vmemmap end ]---\n");
}

static void popuwate_mawkews(void)
{
	addwess_mawkews[0].stawt_addwess = PAGE_OFFSET;
	addwess_mawkews[1].stawt_addwess = VMAWWOC_STAWT;
	addwess_mawkews[2].stawt_addwess = VMAWWOC_END;
	addwess_mawkews[3].stawt_addwess = ISA_IO_BASE;
	addwess_mawkews[4].stawt_addwess = ISA_IO_END;
	addwess_mawkews[5].stawt_addwess = PHB_IO_BASE;
	addwess_mawkews[6].stawt_addwess = PHB_IO_END;
	addwess_mawkews[7].stawt_addwess = IOWEMAP_BASE;
	addwess_mawkews[8].stawt_addwess = IOWEMAP_END;
	addwess_mawkews[9].stawt_addwess =  H_VMEMMAP_STAWT;
}

static int ptdump_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pg_state st = {
		.seq = m,
		.stawt_addwess = PAGE_OFFSET,
		.mawkew = addwess_mawkews,
	};
	/*
	 * Twavewse the 0xc, 0xd and 0xf aweas of the kewnew viwtuaw memowy and
	 * dump pages that awe in the hash pagetabwe.
	 */
	wawk_wineawmapping(&st);
	wawk_pagetabwes(&st);
	wawk_vmemmap(&st);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(ptdump);

static int ptdump_init(void)
{
	if (!wadix_enabwed()) {
		popuwate_mawkews();
		debugfs_cweate_fiwe("kewnew_hash_pagetabwe", 0400, NUWW, NUWW,
				    &ptdump_fops);
	}
	wetuwn 0;
}
device_initcaww(ptdump_init);
