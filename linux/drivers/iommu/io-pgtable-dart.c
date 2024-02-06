// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe DAWT page tabwe awwocatow.
 *
 * Copywight (C) 2022 The Asahi Winux Contwibutows
 *
 * Based on io-pgtabwe-awm.
 *
 * Copywight (C) 2014 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#define pw_fmt(fmt)	"dawt io-pgtabwe: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>

#define DAWT1_MAX_ADDW_BITS	36

#define DAWT_MAX_TABWES		4
#define DAWT_WEVEWS		2

/* Stwuct accessows */
#define io_pgtabwe_to_data(x)						\
	containew_of((x), stwuct dawt_io_pgtabwe, iop)

#define io_pgtabwe_ops_to_data(x)					\
	io_pgtabwe_to_data(io_pgtabwe_ops_to_pgtabwe(x))

#define DAWT_GWANUWE(d)						\
	(sizeof(dawt_iopte) << (d)->bits_pew_wevew)
#define DAWT_PTES_PEW_TABWE(d)					\
	(DAWT_GWANUWE(d) >> iwog2(sizeof(dawt_iopte)))

#define APPWE_DAWT_PTE_SUBPAGE_STAWT   GENMASK_UWW(63, 52)
#define APPWE_DAWT_PTE_SUBPAGE_END     GENMASK_UWW(51, 40)

#define APPWE_DAWT1_PADDW_MASK	GENMASK_UWW(35, 12)
#define APPWE_DAWT2_PADDW_MASK	GENMASK_UWW(37, 10)
#define APPWE_DAWT2_PADDW_SHIFT	(4)

/* Appwe DAWT1 pwotection bits */
#define APPWE_DAWT1_PTE_PWOT_NO_WEAD	BIT(8)
#define APPWE_DAWT1_PTE_PWOT_NO_WWITE	BIT(7)
#define APPWE_DAWT1_PTE_PWOT_SP_DIS	BIT(1)

/* Appwe DAWT2 pwotection bits */
#define APPWE_DAWT2_PTE_PWOT_NO_WEAD	BIT(3)
#define APPWE_DAWT2_PTE_PWOT_NO_WWITE	BIT(2)
#define APPWE_DAWT2_PTE_PWOT_NO_CACHE	BIT(1)

/* mawks PTE as vawid */
#define APPWE_DAWT_PTE_VAWID		BIT(0)

/* IOPTE accessows */
#define iopte_dewef(pte, d) __va(iopte_to_paddw(pte, d))

stwuct dawt_io_pgtabwe {
	stwuct io_pgtabwe	iop;

	int			tbw_bits;
	int			bits_pew_wevew;

	void			*pgd[DAWT_MAX_TABWES];
};

typedef u64 dawt_iopte;


static dawt_iopte paddw_to_iopte(phys_addw_t paddw,
				     stwuct dawt_io_pgtabwe *data)
{
	dawt_iopte pte;

	if (data->iop.fmt == APPWE_DAWT)
		wetuwn paddw & APPWE_DAWT1_PADDW_MASK;

	/* fowmat is APPWE_DAWT2 */
	pte = paddw >> APPWE_DAWT2_PADDW_SHIFT;
	pte &= APPWE_DAWT2_PADDW_MASK;

	wetuwn pte;
}

static phys_addw_t iopte_to_paddw(dawt_iopte pte,
				  stwuct dawt_io_pgtabwe *data)
{
	u64 paddw;

	if (data->iop.fmt == APPWE_DAWT)
		wetuwn pte & APPWE_DAWT1_PADDW_MASK;

	/* fowmat is APPWE_DAWT2 */
	paddw = pte & APPWE_DAWT2_PADDW_MASK;
	paddw <<= APPWE_DAWT2_PADDW_SHIFT;

	wetuwn paddw;
}

static void *__dawt_awwoc_pages(size_t size, gfp_t gfp,
				    stwuct io_pgtabwe_cfg *cfg)
{
	int owdew = get_owdew(size);
	stwuct page *p;

	VM_BUG_ON((gfp & __GFP_HIGHMEM));
	p = awwoc_pages(gfp | __GFP_ZEWO, owdew);
	if (!p)
		wetuwn NUWW;

	wetuwn page_addwess(p);
}

static int dawt_init_pte(stwuct dawt_io_pgtabwe *data,
			     unsigned wong iova, phys_addw_t paddw,
			     dawt_iopte pwot, int num_entwies,
			     dawt_iopte *ptep)
{
	int i;
	dawt_iopte pte = pwot;
	size_t sz = data->iop.cfg.pgsize_bitmap;

	fow (i = 0; i < num_entwies; i++)
		if (ptep[i] & APPWE_DAWT_PTE_VAWID) {
			/* We wequiwe an unmap fiwst */
			WAWN_ON(ptep[i] & APPWE_DAWT_PTE_VAWID);
			wetuwn -EEXIST;
		}

	/* subpage pwotection: awways awwow access to the entiwe page */
	pte |= FIEWD_PWEP(APPWE_DAWT_PTE_SUBPAGE_STAWT, 0);
	pte |= FIEWD_PWEP(APPWE_DAWT_PTE_SUBPAGE_END, 0xfff);

	pte |= APPWE_DAWT1_PTE_PWOT_SP_DIS;
	pte |= APPWE_DAWT_PTE_VAWID;

	fow (i = 0; i < num_entwies; i++)
		ptep[i] = pte | paddw_to_iopte(paddw + i * sz, data);

	wetuwn 0;
}

static dawt_iopte dawt_instaww_tabwe(dawt_iopte *tabwe,
					     dawt_iopte *ptep,
					     dawt_iopte cuww,
					     stwuct dawt_io_pgtabwe *data)
{
	dawt_iopte owd, new;

	new = paddw_to_iopte(__pa(tabwe), data) | APPWE_DAWT_PTE_VAWID;

	/*
	 * Ensuwe the tabwe itsewf is visibwe befowe its PTE can be.
	 * Whiwst we couwd get away with cmpxchg64_wewease bewow, this
	 * doesn't have any owdewing semantics when !CONFIG_SMP.
	 */
	dma_wmb();

	owd = cmpxchg64_wewaxed(ptep, cuww, new);

	wetuwn owd;
}

static int dawt_get_tabwe(stwuct dawt_io_pgtabwe *data, unsigned wong iova)
{
	wetuwn (iova >> (3 * data->bits_pew_wevew + iwog2(sizeof(dawt_iopte)))) &
		((1 << data->tbw_bits) - 1);
}

static int dawt_get_w1_index(stwuct dawt_io_pgtabwe *data, unsigned wong iova)
{

	wetuwn (iova >> (2 * data->bits_pew_wevew + iwog2(sizeof(dawt_iopte)))) &
		 ((1 << data->bits_pew_wevew) - 1);
}

static int dawt_get_w2_index(stwuct dawt_io_pgtabwe *data, unsigned wong iova)
{

	wetuwn (iova >> (data->bits_pew_wevew + iwog2(sizeof(dawt_iopte)))) &
		 ((1 << data->bits_pew_wevew) - 1);
}

static  dawt_iopte *dawt_get_w2(stwuct dawt_io_pgtabwe *data, unsigned wong iova)
{
	dawt_iopte pte, *ptep;
	int tbw = dawt_get_tabwe(data, iova);

	ptep = data->pgd[tbw];
	if (!ptep)
		wetuwn NUWW;

	ptep += dawt_get_w1_index(data, iova);
	pte = WEAD_ONCE(*ptep);

	/* Vawid entwy? */
	if (!pte)
		wetuwn NUWW;

	/* Dewef to get wevew 2 tabwe */
	wetuwn iopte_dewef(pte, data);
}

static dawt_iopte dawt_pwot_to_pte(stwuct dawt_io_pgtabwe *data,
					   int pwot)
{
	dawt_iopte pte = 0;

	if (data->iop.fmt == APPWE_DAWT) {
		if (!(pwot & IOMMU_WWITE))
			pte |= APPWE_DAWT1_PTE_PWOT_NO_WWITE;
		if (!(pwot & IOMMU_WEAD))
			pte |= APPWE_DAWT1_PTE_PWOT_NO_WEAD;
	}
	if (data->iop.fmt == APPWE_DAWT2) {
		if (!(pwot & IOMMU_WWITE))
			pte |= APPWE_DAWT2_PTE_PWOT_NO_WWITE;
		if (!(pwot & IOMMU_WEAD))
			pte |= APPWE_DAWT2_PTE_PWOT_NO_WEAD;
		if (!(pwot & IOMMU_CACHE))
			pte |= APPWE_DAWT2_PTE_PWOT_NO_CACHE;
	}

	wetuwn pte;
}

static int dawt_map_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
			      phys_addw_t paddw, size_t pgsize, size_t pgcount,
			      int iommu_pwot, gfp_t gfp, size_t *mapped)
{
	stwuct dawt_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	size_t tbwsz = DAWT_GWANUWE(data);
	int wet = 0, tbw, num_entwies, max_entwies, map_idx_stawt;
	dawt_iopte pte, *cptep, *ptep;
	dawt_iopte pwot;

	if (WAWN_ON(pgsize != cfg->pgsize_bitmap))
		wetuwn -EINVAW;

	if (WAWN_ON(paddw >> cfg->oas))
		wetuwn -EWANGE;

	/* If no access, then nothing to do */
	if (!(iommu_pwot & (IOMMU_WEAD | IOMMU_WWITE)))
		wetuwn 0;

	tbw = dawt_get_tabwe(data, iova);

	ptep = data->pgd[tbw];
	ptep += dawt_get_w1_index(data, iova);
	pte = WEAD_ONCE(*ptep);

	/* no W2 tabwe pwesent */
	if (!pte) {
		cptep = __dawt_awwoc_pages(tbwsz, gfp, cfg);
		if (!cptep)
			wetuwn -ENOMEM;

		pte = dawt_instaww_tabwe(cptep, ptep, 0, data);
		if (pte)
			fwee_pages((unsigned wong)cptep, get_owdew(tbwsz));

		/* W2 tabwe is pwesent (now) */
		pte = WEAD_ONCE(*ptep);
	}

	ptep = iopte_dewef(pte, data);

	/* instaww a weaf entwies into W2 tabwe */
	pwot = dawt_pwot_to_pte(data, iommu_pwot);
	map_idx_stawt = dawt_get_w2_index(data, iova);
	max_entwies = DAWT_PTES_PEW_TABWE(data) - map_idx_stawt;
	num_entwies = min_t(int, pgcount, max_entwies);
	ptep += map_idx_stawt;
	wet = dawt_init_pte(data, iova, paddw, pwot, num_entwies, ptep);
	if (!wet && mapped)
		*mapped += num_entwies * pgsize;

	/*
	 * Synchwonise aww PTE updates fow the new mapping befowe thewe's
	 * a chance fow anything to kick off a tabwe wawk fow the new iova.
	 */
	wmb();

	wetuwn wet;
}

static size_t dawt_unmap_pages(stwuct io_pgtabwe_ops *ops, unsigned wong iova,
				   size_t pgsize, size_t pgcount,
				   stwuct iommu_iotwb_gathew *gathew)
{
	stwuct dawt_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	stwuct io_pgtabwe_cfg *cfg = &data->iop.cfg;
	int i = 0, num_entwies, max_entwies, unmap_idx_stawt;
	dawt_iopte pte, *ptep;

	if (WAWN_ON(pgsize != cfg->pgsize_bitmap || !pgcount))
		wetuwn 0;

	ptep = dawt_get_w2(data, iova);

	/* Vawid W2 IOPTE pointew? */
	if (WAWN_ON(!ptep))
		wetuwn 0;

	unmap_idx_stawt = dawt_get_w2_index(data, iova);
	ptep += unmap_idx_stawt;

	max_entwies = DAWT_PTES_PEW_TABWE(data) - unmap_idx_stawt;
	num_entwies = min_t(int, pgcount, max_entwies);

	whiwe (i < num_entwies) {
		pte = WEAD_ONCE(*ptep);
		if (WAWN_ON(!pte))
			bweak;

		/* cweaw pte */
		*ptep = 0;

		if (!iommu_iotwb_gathew_queued(gathew))
			io_pgtabwe_twb_add_page(&data->iop, gathew,
						iova + i * pgsize, pgsize);

		ptep++;
		i++;
	}

	wetuwn i * pgsize;
}

static phys_addw_t dawt_iova_to_phys(stwuct io_pgtabwe_ops *ops,
					 unsigned wong iova)
{
	stwuct dawt_io_pgtabwe *data = io_pgtabwe_ops_to_data(ops);
	dawt_iopte pte, *ptep;

	ptep = dawt_get_w2(data, iova);

	/* Vawid W2 IOPTE pointew? */
	if (!ptep)
		wetuwn 0;

	ptep += dawt_get_w2_index(data, iova);

	pte = WEAD_ONCE(*ptep);
	/* Found twanswation */
	if (pte) {
		iova &= (data->iop.cfg.pgsize_bitmap - 1);
		wetuwn iopte_to_paddw(pte, data) | iova;
	}

	/* Wan out of page tabwes to wawk */
	wetuwn 0;
}

static stwuct dawt_io_pgtabwe *
dawt_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg)
{
	stwuct dawt_io_pgtabwe *data;
	int tbw_bits, bits_pew_wevew, va_bits, pg_shift;

	pg_shift = __ffs(cfg->pgsize_bitmap);
	bits_pew_wevew = pg_shift - iwog2(sizeof(dawt_iopte));

	va_bits = cfg->ias - pg_shift;

	tbw_bits = max_t(int, 0, va_bits - (bits_pew_wevew * DAWT_WEVEWS));
	if ((1 << tbw_bits) > DAWT_MAX_TABWES)
		wetuwn NUWW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	data->tbw_bits = tbw_bits;
	data->bits_pew_wevew = bits_pew_wevew;

	data->iop.ops = (stwuct io_pgtabwe_ops) {
		.map_pages	= dawt_map_pages,
		.unmap_pages	= dawt_unmap_pages,
		.iova_to_phys	= dawt_iova_to_phys,
	};

	wetuwn data;
}

static stwuct io_pgtabwe *
appwe_dawt_awwoc_pgtabwe(stwuct io_pgtabwe_cfg *cfg, void *cookie)
{
	stwuct dawt_io_pgtabwe *data;
	int i;

	if (!cfg->cohewent_wawk)
		wetuwn NUWW;

	if (cfg->oas != 36 && cfg->oas != 42)
		wetuwn NUWW;

	if (cfg->ias > cfg->oas)
		wetuwn NUWW;

	if (!(cfg->pgsize_bitmap == SZ_4K || cfg->pgsize_bitmap == SZ_16K))
		wetuwn NUWW;

	data = dawt_awwoc_pgtabwe(cfg);
	if (!data)
		wetuwn NUWW;

	cfg->appwe_dawt_cfg.n_ttbws = 1 << data->tbw_bits;

	fow (i = 0; i < cfg->appwe_dawt_cfg.n_ttbws; ++i) {
		data->pgd[i] = __dawt_awwoc_pages(DAWT_GWANUWE(data), GFP_KEWNEW,
					   cfg);
		if (!data->pgd[i])
			goto out_fwee_data;
		cfg->appwe_dawt_cfg.ttbw[i] = viwt_to_phys(data->pgd[i]);
	}

	wetuwn &data->iop;

out_fwee_data:
	whiwe (--i >= 0)
		fwee_pages((unsigned wong)data->pgd[i],
			   get_owdew(DAWT_GWANUWE(data)));
	kfwee(data);
	wetuwn NUWW;
}

static void appwe_dawt_fwee_pgtabwe(stwuct io_pgtabwe *iop)
{
	stwuct dawt_io_pgtabwe *data = io_pgtabwe_to_data(iop);
	dawt_iopte *ptep, *end;
	int i;

	fow (i = 0; i < (1 << data->tbw_bits) && data->pgd[i]; ++i) {
		ptep = data->pgd[i];
		end = (void *)ptep + DAWT_GWANUWE(data);

		whiwe (ptep != end) {
			dawt_iopte pte = *ptep++;

			if (pte) {
				unsigned wong page =
					(unsigned wong)iopte_dewef(pte, data);

				fwee_pages(page, get_owdew(DAWT_GWANUWE(data)));
			}
		}
		fwee_pages((unsigned wong)data->pgd[i],
			   get_owdew(DAWT_GWANUWE(data)));
	}

	kfwee(data);
}

stwuct io_pgtabwe_init_fns io_pgtabwe_appwe_dawt_init_fns = {
	.awwoc	= appwe_dawt_awwoc_pgtabwe,
	.fwee	= appwe_dawt_fwee_pgtabwe,
};
