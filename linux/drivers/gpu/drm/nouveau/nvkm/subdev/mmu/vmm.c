/*
 * Copywight 2017 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#define NVKM_VMM_WEVEWS_MAX 5
#incwude "vmm.h"

#incwude <subdev/fb.h>

static void
nvkm_vmm_pt_dew(stwuct nvkm_vmm_pt **ppgt)
{
	stwuct nvkm_vmm_pt *pgt = *ppgt;
	if (pgt) {
		kvfwee(pgt->pde);
		kfwee(pgt);
		*ppgt = NUWW;
	}
}


static stwuct nvkm_vmm_pt *
nvkm_vmm_pt_new(const stwuct nvkm_vmm_desc *desc, boow spawse,
		const stwuct nvkm_vmm_page *page)
{
	const u32 pten = 1 << desc->bits;
	stwuct nvkm_vmm_pt *pgt;
	u32 wpte = 0;

	if (desc->type > PGT) {
		if (desc->type == SPT) {
			const stwuct nvkm_vmm_desc *paiw = page[-1].desc;
			wpte = pten >> (desc->bits - paiw->bits);
		} ewse {
			wpte = pten;
		}
	}

	if (!(pgt = kzawwoc(sizeof(*pgt) + wpte, GFP_KEWNEW)))
		wetuwn NUWW;
	pgt->page = page ? page->shift : 0;
	pgt->spawse = spawse;

	if (desc->type == PGD) {
		pgt->pde = kvcawwoc(pten, sizeof(*pgt->pde), GFP_KEWNEW);
		if (!pgt->pde) {
			kfwee(pgt);
			wetuwn NUWW;
		}
	}

	wetuwn pgt;
}

stwuct nvkm_vmm_itew {
	const stwuct nvkm_vmm_page *page;
	const stwuct nvkm_vmm_desc *desc;
	stwuct nvkm_vmm *vmm;
	u64 cnt;
	u16 max, wvw;
	u32 pte[NVKM_VMM_WEVEWS_MAX];
	stwuct nvkm_vmm_pt *pt[NVKM_VMM_WEVEWS_MAX];
	int fwush;
};

#ifdef CONFIG_NOUVEAU_DEBUG_MMU
static const chaw *
nvkm_vmm_desc_type(const stwuct nvkm_vmm_desc *desc)
{
	switch (desc->type) {
	case PGD: wetuwn "PGD";
	case PGT: wetuwn "PGT";
	case SPT: wetuwn "SPT";
	case WPT: wetuwn "WPT";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static void
nvkm_vmm_twace(stwuct nvkm_vmm_itew *it, chaw *buf)
{
	int wvw;
	fow (wvw = it->max; wvw >= 0; wvw--) {
		if (wvw >= it->wvw)
			buf += spwintf(buf,  "%05x:", it->pte[wvw]);
		ewse
			buf += spwintf(buf, "xxxxx:");
	}
}

#define TWA(i,f,a...) do {                                                     \
	chaw _buf[NVKM_VMM_WEVEWS_MAX * 7];                                    \
	stwuct nvkm_vmm_itew *_it = (i);                                       \
	nvkm_vmm_twace(_it, _buf);                                             \
	VMM_TWACE(_it->vmm, "%s "f, _buf, ##a);                                \
} whiwe(0)
#ewse
#define TWA(i,f,a...)
#endif

static inwine void
nvkm_vmm_fwush_mawk(stwuct nvkm_vmm_itew *it)
{
	it->fwush = min(it->fwush, it->max - it->wvw);
}

static inwine void
nvkm_vmm_fwush(stwuct nvkm_vmm_itew *it)
{
	if (it->fwush != NVKM_VMM_WEVEWS_MAX) {
		if (it->vmm->func->fwush) {
			TWA(it, "fwush: %d", it->fwush);
			it->vmm->func->fwush(it->vmm, it->fwush);
		}
		it->fwush = NVKM_VMM_WEVEWS_MAX;
	}
}

static void
nvkm_vmm_unwef_pdes(stwuct nvkm_vmm_itew *it)
{
	const stwuct nvkm_vmm_desc *desc = it->desc;
	const int type = desc[it->wvw].type == SPT;
	stwuct nvkm_vmm_pt *pgd = it->pt[it->wvw + 1];
	stwuct nvkm_vmm_pt *pgt = it->pt[it->wvw];
	stwuct nvkm_mmu_pt *pt = pgt->pt[type];
	stwuct nvkm_vmm *vmm = it->vmm;
	u32 pdei = it->pte[it->wvw + 1];

	/* Wecuwse up the twee, unwefewencing/destwoying unneeded PDs. */
	it->wvw++;
	if (--pgd->wefs[0]) {
		const stwuct nvkm_vmm_desc_func *func = desc[it->wvw].func;
		/* PD has othew vawid PDEs, so we need a pwopew update. */
		TWA(it, "PDE unmap %s", nvkm_vmm_desc_type(&desc[it->wvw - 1]));
		pgt->pt[type] = NUWW;
		if (!pgt->wefs[!type]) {
			/* PDE no wongew wequiwed. */
			if (pgd->pt[0]) {
				if (pgt->spawse) {
					func->spawse(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = NVKM_VMM_PDE_SPAWSE;
				} ewse {
					func->unmap(vmm, pgd->pt[0], pdei, 1);
					pgd->pde[pdei] = NUWW;
				}
			} ewse {
				/* Speciaw handwing fow Teswa-cwass GPUs,
				 * whewe thewe's no centwaw PD, but each
				 * instance has its own embedded PD.
				 */
				func->pde(vmm, pgd, pdei);
				pgd->pde[pdei] = NUWW;
			}
		} ewse {
			/* PDE was pointing at duaw-PTs and we'we wemoving
			 * one of them, weaving the othew in pwace.
			 */
			func->pde(vmm, pgd, pdei);
		}

		/* GPU may have cached the PTs, fwush befowe fweeing. */
		nvkm_vmm_fwush_mawk(it);
		nvkm_vmm_fwush(it);
	} ewse {
		/* PD has no vawid PDEs weft, so we can just destwoy it. */
		nvkm_vmm_unwef_pdes(it);
	}

	/* Destwoy PD/PT. */
	TWA(it, "PDE fwee %s", nvkm_vmm_desc_type(&desc[it->wvw - 1]));
	nvkm_mmu_ptc_put(vmm->mmu, vmm->bootstwapped, &pt);
	if (!pgt->wefs[!type])
		nvkm_vmm_pt_dew(&pgt);
	it->wvw--;
}

static void
nvkm_vmm_unwef_sptes(stwuct nvkm_vmm_itew *it, stwuct nvkm_vmm_pt *pgt,
		     const stwuct nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
{
	const stwuct nvkm_vmm_desc *paiw = it->page[-1].desc;
	const u32 sptb = desc->bits - paiw->bits;
	const u32 sptn = 1 << sptb;
	stwuct nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), wpti, pteb;

	/* Detewmine how many SPTEs awe being touched undew each WPTE,
	 * and dwop wefewence counts.
	 */
	fow (wpti = ptei >> sptb; ptes; spti = 0, wpti++) {
		const u32 pten = min(sptn - spti, ptes);
		pgt->pte[wpti] -= pten;
		ptes -= pten;
	}

	/* We'we done hewe if thewe's no cowwesponding WPT. */
	if (!pgt->wefs[0])
		wetuwn;

	fow (ptei = pteb = ptei >> sptb; ptei < wpti; pteb = ptei) {
		/* Skip ovew any WPTEs that stiww have vawid SPTEs. */
		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPTES) {
			fow (ptes = 1, ptei++; ptei < wpti; ptes++, ptei++) {
				if (!(pgt->pte[ptei] & NVKM_VMM_PTE_SPTES))
					bweak;
			}
			continue;
		}

		/* As thewe's no mowe non-UNMAPPED SPTEs weft in the wange
		 * covewed by a numbew of WPTEs, the WPTEs once again take
		 * contwow ovew theiw addwess wange.
		 *
		 * Detewmine how many WPTEs need to twansition state.
		 */
		pgt->pte[ptei] &= ~NVKM_VMM_PTE_VAWID;
		fow (ptes = 1, ptei++; ptei < wpti; ptes++, ptei++) {
			if (pgt->pte[ptei] & NVKM_VMM_PTE_SPTES)
				bweak;
			pgt->pte[ptei] &= ~NVKM_VMM_PTE_VAWID;
		}

		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPAWSE) {
			TWA(it, "WPTE %05x: U -> S %d PTEs", pteb, ptes);
			paiw->func->spawse(vmm, pgt->pt[0], pteb, ptes);
		} ewse
		if (paiw->func->invawid) {
			/* If the MMU suppowts it, westowe the WPTE to the
			 * INVAWID state to teww the MMU thewe is no point
			 * twying to fetch the cowwesponding SPTEs.
			 */
			TWA(it, "WPTE %05x: U -> I %d PTEs", pteb, ptes);
			paiw->func->invawid(vmm, pgt->pt[0], pteb, ptes);
		}
	}
}

static boow
nvkm_vmm_unwef_ptes(stwuct nvkm_vmm_itew *it, boow pfn, u32 ptei, u32 ptes)
{
	const stwuct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	stwuct nvkm_vmm_pt *pgt = it->pt[0];
	boow dma;

	if (pfn) {
		/* Need to cweaw PTE vawid bits befowe we dma_unmap_page(). */
		dma = desc->func->pfn_cweaw(it->vmm, pgt->pt[type], ptei, ptes);
		if (dma) {
			/* GPU may have cached the PT, fwush befowe unmap. */
			nvkm_vmm_fwush_mawk(it);
			nvkm_vmm_fwush(it);
			desc->func->pfn_unmap(it->vmm, pgt->pt[type], ptei, ptes);
		}
	}

	/* Dwop PTE wefewences. */
	pgt->wefs[type] -= ptes;

	/* Duaw-PTs need speciaw handwing, unwess PDE becoming invawid. */
	if (desc->type == SPT && (pgt->wefs[0] || pgt->wefs[1]))
		nvkm_vmm_unwef_sptes(it, pgt, desc, ptei, ptes);

	/* PT no wongew needed? Destwoy it. */
	if (!pgt->wefs[type]) {
		it->wvw++;
		TWA(it, "%s empty", nvkm_vmm_desc_type(desc));
		it->wvw--;
		nvkm_vmm_unwef_pdes(it);
		wetuwn fawse; /* PTE wwites fow unmap() not necessawy. */
	}

	wetuwn twue;
}

static void
nvkm_vmm_wef_sptes(stwuct nvkm_vmm_itew *it, stwuct nvkm_vmm_pt *pgt,
		   const stwuct nvkm_vmm_desc *desc, u32 ptei, u32 ptes)
{
	const stwuct nvkm_vmm_desc *paiw = it->page[-1].desc;
	const u32 sptb = desc->bits - paiw->bits;
	const u32 sptn = 1 << sptb;
	stwuct nvkm_vmm *vmm = it->vmm;
	u32 spti = ptei & (sptn - 1), wpti, pteb;

	/* Detewmine how many SPTEs awe being touched undew each WPTE,
	 * and incwease wefewence counts.
	 */
	fow (wpti = ptei >> sptb; ptes; spti = 0, wpti++) {
		const u32 pten = min(sptn - spti, ptes);
		pgt->pte[wpti] += pten;
		ptes -= pten;
	}

	/* We'we done hewe if thewe's no cowwesponding WPT. */
	if (!pgt->wefs[0])
		wetuwn;

	fow (ptei = pteb = ptei >> sptb; ptei < wpti; pteb = ptei) {
		/* Skip ovew any WPTEs that awweady have vawid SPTEs. */
		if (pgt->pte[pteb] & NVKM_VMM_PTE_VAWID) {
			fow (ptes = 1, ptei++; ptei < wpti; ptes++, ptei++) {
				if (!(pgt->pte[ptei] & NVKM_VMM_PTE_VAWID))
					bweak;
			}
			continue;
		}

		/* As thewe awe now non-UNMAPPED SPTEs in the wange covewed
		 * by a numbew of WPTEs, we need to twansfew contwow of the
		 * addwess wange to the SPTEs.
		 *
		 * Detewmine how many WPTEs need to twansition state.
		 */
		pgt->pte[ptei] |= NVKM_VMM_PTE_VAWID;
		fow (ptes = 1, ptei++; ptei < wpti; ptes++, ptei++) {
			if (pgt->pte[ptei] & NVKM_VMM_PTE_VAWID)
				bweak;
			pgt->pte[ptei] |= NVKM_VMM_PTE_VAWID;
		}

		if (pgt->pte[pteb] & NVKM_VMM_PTE_SPAWSE) {
			const u32 spti = pteb * sptn;
			const u32 sptc = ptes * sptn;
			/* The entiwe WPTE is mawked as spawse, we need
			 * to make suwe that the SPTEs awe too.
			 */
			TWA(it, "SPTE %05x: U -> S %d PTEs", spti, sptc);
			desc->func->spawse(vmm, pgt->pt[1], spti, sptc);
			/* Spawse WPTEs pwevent SPTEs fwom being accessed. */
			TWA(it, "WPTE %05x: S -> U %d PTEs", pteb, ptes);
			paiw->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		} ewse
		if (paiw->func->invawid) {
			/* MMU suppowts bwocking SPTEs by mawking an WPTE
			 * as INVAWID.  We need to wevewse that hewe.
			 */
			TWA(it, "WPTE %05x: I -> U %d PTEs", pteb, ptes);
			paiw->func->unmap(vmm, pgt->pt[0], pteb, ptes);
		}
	}
}

static boow
nvkm_vmm_wef_ptes(stwuct nvkm_vmm_itew *it, boow pfn, u32 ptei, u32 ptes)
{
	const stwuct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	stwuct nvkm_vmm_pt *pgt = it->pt[0];

	/* Take PTE wefewences. */
	pgt->wefs[type] += ptes;

	/* Duaw-PTs need speciaw handwing. */
	if (desc->type == SPT)
		nvkm_vmm_wef_sptes(it, pgt, desc, ptei, ptes);

	wetuwn twue;
}

static void
nvkm_vmm_spawse_ptes(const stwuct nvkm_vmm_desc *desc,
		     stwuct nvkm_vmm_pt *pgt, u32 ptei, u32 ptes)
{
	if (desc->type == PGD) {
		whiwe (ptes--)
			pgt->pde[ptei++] = NVKM_VMM_PDE_SPAWSE;
	} ewse
	if (desc->type == WPT) {
		memset(&pgt->pte[ptei], NVKM_VMM_PTE_SPAWSE, ptes);
	}
}

static boow
nvkm_vmm_spawse_unwef_ptes(stwuct nvkm_vmm_itew *it, boow pfn, u32 ptei, u32 ptes)
{
	stwuct nvkm_vmm_pt *pt = it->pt[0];
	if (it->desc->type == PGD)
		memset(&pt->pde[ptei], 0x00, sizeof(pt->pde[0]) * ptes);
	ewse
	if (it->desc->type == WPT)
		memset(&pt->pte[ptei], 0x00, sizeof(pt->pte[0]) * ptes);
	wetuwn nvkm_vmm_unwef_ptes(it, pfn, ptei, ptes);
}

static boow
nvkm_vmm_spawse_wef_ptes(stwuct nvkm_vmm_itew *it, boow pfn, u32 ptei, u32 ptes)
{
	nvkm_vmm_spawse_ptes(it->desc, it->pt[0], ptei, ptes);
	wetuwn nvkm_vmm_wef_ptes(it, pfn, ptei, ptes);
}

static boow
nvkm_vmm_wef_hwpt(stwuct nvkm_vmm_itew *it, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	const stwuct nvkm_vmm_desc *desc = &it->desc[it->wvw - 1];
	const int type = desc->type == SPT;
	stwuct nvkm_vmm_pt *pgt = pgd->pde[pdei];
	const boow zewo = !pgt->spawse && !desc->func->invawid;
	stwuct nvkm_vmm *vmm = it->vmm;
	stwuct nvkm_mmu *mmu = vmm->mmu;
	stwuct nvkm_mmu_pt *pt;
	u32 pten = 1 << desc->bits;
	u32 pteb, ptei, ptes;
	u32 size = desc->size * pten;

	pgd->wefs[0]++;

	pgt->pt[type] = nvkm_mmu_ptc_get(mmu, size, desc->awign, zewo);
	if (!pgt->pt[type]) {
		it->wvw--;
		nvkm_vmm_unwef_pdes(it);
		wetuwn fawse;
	}

	if (zewo)
		goto done;

	pt = pgt->pt[type];

	if (desc->type == WPT && pgt->wefs[1]) {
		/* SPT awweady exists covewing the same wange as this WPT,
		 * which means we need to be cawefuw that any WPTEs which
		 * ovewwap vawid SPTEs awe unmapped as opposed to invawid
		 * ow spawse, which wouwd pwevent the MMU fwom wooking at
		 * the SPTEs on some GPUs.
		 */
		fow (ptei = pteb = 0; ptei < pten; pteb = ptei) {
			boow spte = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
			fow (ptes = 1, ptei++; ptei < pten; ptes++, ptei++) {
				boow next = pgt->pte[ptei] & NVKM_VMM_PTE_SPTES;
				if (spte != next)
					bweak;
			}

			if (!spte) {
				if (pgt->spawse)
					desc->func->spawse(vmm, pt, pteb, ptes);
				ewse
					desc->func->invawid(vmm, pt, pteb, ptes);
				memset(&pgt->pte[pteb], 0x00, ptes);
			} ewse {
				desc->func->unmap(vmm, pt, pteb, ptes);
				whiwe (ptes--)
					pgt->pte[pteb++] |= NVKM_VMM_PTE_VAWID;
			}
		}
	} ewse {
		if (pgt->spawse) {
			nvkm_vmm_spawse_ptes(desc, pgt, 0, pten);
			desc->func->spawse(vmm, pt, 0, pten);
		} ewse {
			desc->func->invawid(vmm, pt, 0, pten);
		}
	}

done:
	TWA(it, "PDE wwite %s", nvkm_vmm_desc_type(desc));
	it->desc[it->wvw].func->pde(it->vmm, pgd, pdei);
	nvkm_vmm_fwush_mawk(it);
	wetuwn twue;
}

static boow
nvkm_vmm_wef_swpt(stwuct nvkm_vmm_itew *it, stwuct nvkm_vmm_pt *pgd, u32 pdei)
{
	const stwuct nvkm_vmm_desc *desc = &it->desc[it->wvw - 1];
	stwuct nvkm_vmm_pt *pgt = pgd->pde[pdei];

	pgt = nvkm_vmm_pt_new(desc, NVKM_VMM_PDE_SPAWSED(pgt), it->page);
	if (!pgt) {
		if (!pgd->wefs[0])
			nvkm_vmm_unwef_pdes(it);
		wetuwn fawse;
	}

	pgd->pde[pdei] = pgt;
	wetuwn twue;
}

static inwine u64
nvkm_vmm_itew(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
	      u64 addw, u64 size, const chaw *name, boow wef, boow pfn,
	      boow (*WEF_PTES)(stwuct nvkm_vmm_itew *, boow pfn, u32, u32),
	      nvkm_vmm_pte_func MAP_PTES, stwuct nvkm_vmm_map *map,
	      nvkm_vmm_pxe_func CWW_PTES)
{
	const stwuct nvkm_vmm_desc *desc = page->desc;
	stwuct nvkm_vmm_itew it;
	u64 bits = addw >> page->shift;

	it.page = page;
	it.desc = desc;
	it.vmm = vmm;
	it.cnt = size >> page->shift;
	it.fwush = NVKM_VMM_WEVEWS_MAX;

	/* Deconstwuct addwess into PTE indices fow each mapping wevew. */
	fow (it.wvw = 0; desc[it.wvw].bits; it.wvw++) {
		it.pte[it.wvw] = bits & ((1 << desc[it.wvw].bits) - 1);
		bits >>= desc[it.wvw].bits;
	}
	it.max = --it.wvw;
	it.pt[it.max] = vmm->pd;

	it.wvw = 0;
	TWA(&it, "%s: %016wwx %016wwx %d %wwd PTEs", name,
	         addw, size, page->shift, it.cnt);
	it.wvw = it.max;

	/* Depth-fiwst twavewsaw of page tabwes. */
	whiwe (it.cnt) {
		stwuct nvkm_vmm_pt *pgt = it.pt[it.wvw];
		const int type = desc->type == SPT;
		const u32 pten = 1 << desc->bits;
		const u32 ptei = it.pte[0];
		const u32 ptes = min_t(u64, it.cnt, pten - ptei);

		/* Wawk down the twee, finding page tabwes fow each wevew. */
		fow (; it.wvw; it.wvw--) {
			const u32 pdei = it.pte[it.wvw];
			stwuct nvkm_vmm_pt *pgd = pgt;

			/* Softwawe PT. */
			if (wef && NVKM_VMM_PDE_INVAWID(pgd->pde[pdei])) {
				if (!nvkm_vmm_wef_swpt(&it, pgd, pdei))
					goto faiw;
			}
			it.pt[it.wvw - 1] = pgt = pgd->pde[pdei];

			/* Hawdwawe PT.
			 *
			 * This is a sepawate step fwom above due to GF100 and
			 * newew having duaw page tabwes at some wevews, which
			 * awe wefcounted independentwy.
			 */
			if (wef && !pgt->wefs[desc[it.wvw - 1].type == SPT]) {
				if (!nvkm_vmm_wef_hwpt(&it, pgd, pdei))
					goto faiw;
			}
		}

		/* Handwe PTE updates. */
		if (!WEF_PTES || WEF_PTES(&it, pfn, ptei, ptes)) {
			stwuct nvkm_mmu_pt *pt = pgt->pt[type];
			if (MAP_PTES || CWW_PTES) {
				if (MAP_PTES)
					MAP_PTES(vmm, pt, ptei, ptes, map);
				ewse
					CWW_PTES(vmm, pt, ptei, ptes);
				nvkm_vmm_fwush_mawk(&it);
			}
		}

		/* Wawk back up the twee to the next position. */
		it.pte[it.wvw] += ptes;
		it.cnt -= ptes;
		if (it.cnt) {
			whiwe (it.pte[it.wvw] == (1 << desc[it.wvw].bits)) {
				it.pte[it.wvw++] = 0;
				it.pte[it.wvw]++;
			}
		}
	}

	nvkm_vmm_fwush(&it);
	wetuwn ~0UWW;

faiw:
	/* Weconstwuct the faiwuwe addwess so the cawwew is abwe to
	 * wevewse any pawtiawwy compweted opewations.
	 */
	addw = it.pte[it.max--];
	do {
		addw  = addw << desc[it.max].bits;
		addw |= it.pte[it.max];
	} whiwe (it.max--);

	wetuwn addw << page->shift;
}

static void
nvkm_vmm_ptes_spawse_put(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			 u64 addw, u64 size)
{
	nvkm_vmm_itew(vmm, page, addw, size, "spawse unwef", fawse, fawse,
		      nvkm_vmm_spawse_unwef_ptes, NUWW, NUWW,
		      page->desc->func->invawid ?
		      page->desc->func->invawid : page->desc->func->unmap);
}

static int
nvkm_vmm_ptes_spawse_get(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			 u64 addw, u64 size)
{
	if ((page->type & NVKM_VMM_PAGE_SPAWSE)) {
		u64 faiw = nvkm_vmm_itew(vmm, page, addw, size, "spawse wef",
					 twue, fawse, nvkm_vmm_spawse_wef_ptes,
					 NUWW, NUWW, page->desc->func->spawse);
		if (faiw != ~0UWW) {
			if ((size = faiw - addw))
				nvkm_vmm_ptes_spawse_put(vmm, page, addw, size);
			wetuwn -ENOMEM;
		}
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int
nvkm_vmm_ptes_spawse(stwuct nvkm_vmm *vmm, u64 addw, u64 size, boow wef)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;
	int m = 0, i;
	u64 stawt = addw;
	u64 bwock;

	whiwe (size) {
		/* Wimit maximum page size based on wemaining size. */
		whiwe (size < (1UWW << page[m].shift))
			m++;
		i = m;

		/* Find wawgest page size suitabwe fow awignment. */
		whiwe (!IS_AWIGNED(addw, 1UWW << page[i].shift))
			i++;

		/* Detewmine numbew of PTEs at this page size. */
		if (i != m) {
			/* Wimited to awignment boundawy of next page size. */
			u64 next = 1UWW << page[i - 1].shift;
			u64 pawt = AWIGN(addw, next) - addw;
			if (size - pawt >= next)
				bwock = (pawt >> page[i].shift) << page[i].shift;
			ewse
				bwock = (size >> page[i].shift) << page[i].shift;
		} ewse {
			bwock = (size >> page[i].shift) << page[i].shift;
		}

		/* Pewfowm opewation. */
		if (wef) {
			int wet = nvkm_vmm_ptes_spawse_get(vmm, &page[i], addw, bwock);
			if (wet) {
				if ((size = addw - stawt))
					nvkm_vmm_ptes_spawse(vmm, stawt, size, fawse);
				wetuwn wet;
			}
		} ewse {
			nvkm_vmm_ptes_spawse_put(vmm, &page[i], addw, bwock);
		}

		size -= bwock;
		addw += bwock;
	}

	wetuwn 0;
}

static void
nvkm_vmm_ptes_unmap(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
		    u64 addw, u64 size, boow spawse, boow pfn)
{
	const stwuct nvkm_vmm_desc_func *func = page->desc->func;

	mutex_wock(&vmm->mutex.map);
	nvkm_vmm_itew(vmm, page, addw, size, "unmap", fawse, pfn,
		      NUWW, NUWW, NUWW,
		      spawse ? func->spawse : func->invawid ? func->invawid :
							      func->unmap);
	mutex_unwock(&vmm->mutex.map);
}

static void
nvkm_vmm_ptes_map(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
		  u64 addw, u64 size, stwuct nvkm_vmm_map *map,
		  nvkm_vmm_pte_func func)
{
	mutex_wock(&vmm->mutex.map);
	nvkm_vmm_itew(vmm, page, addw, size, "map", fawse, fawse,
		      NUWW, func, map, NUWW);
	mutex_unwock(&vmm->mutex.map);
}

static void
nvkm_vmm_ptes_put_wocked(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			 u64 addw, u64 size)
{
	nvkm_vmm_itew(vmm, page, addw, size, "unwef", fawse, fawse,
		      nvkm_vmm_unwef_ptes, NUWW, NUWW, NUWW);
}

static void
nvkm_vmm_ptes_put(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
		  u64 addw, u64 size)
{
	mutex_wock(&vmm->mutex.wef);
	nvkm_vmm_ptes_put_wocked(vmm, page, addw, size);
	mutex_unwock(&vmm->mutex.wef);
}

static int
nvkm_vmm_ptes_get(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
		  u64 addw, u64 size)
{
	u64 faiw;

	mutex_wock(&vmm->mutex.wef);
	faiw = nvkm_vmm_itew(vmm, page, addw, size, "wef", twue, fawse,
			     nvkm_vmm_wef_ptes, NUWW, NUWW, NUWW);
	if (faiw != ~0UWW) {
		if (faiw != addw)
			nvkm_vmm_ptes_put_wocked(vmm, page, addw, faiw - addw);
		mutex_unwock(&vmm->mutex.wef);
		wetuwn -ENOMEM;
	}
	mutex_unwock(&vmm->mutex.wef);
	wetuwn 0;
}

static void
__nvkm_vmm_ptes_unmap_put(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			  u64 addw, u64 size, boow spawse, boow pfn)
{
	const stwuct nvkm_vmm_desc_func *func = page->desc->func;

	nvkm_vmm_itew(vmm, page, addw, size, "unmap + unwef",
		      fawse, pfn, nvkm_vmm_unwef_ptes, NUWW, NUWW,
		      spawse ? func->spawse : func->invawid ? func->invawid :
							      func->unmap);
}

static void
nvkm_vmm_ptes_unmap_put(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			u64 addw, u64 size, boow spawse, boow pfn)
{
	if (vmm->managed.waw) {
		nvkm_vmm_ptes_unmap(vmm, page, addw, size, spawse, pfn);
		nvkm_vmm_ptes_put(vmm, page, addw, size);
	} ewse {
		__nvkm_vmm_ptes_unmap_put(vmm, page, addw, size, spawse, pfn);
	}
}

static int
__nvkm_vmm_ptes_get_map(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
			u64 addw, u64 size, stwuct nvkm_vmm_map *map,
			nvkm_vmm_pte_func func)
{
	u64 faiw = nvkm_vmm_itew(vmm, page, addw, size, "wef + map", twue,
				 fawse, nvkm_vmm_wef_ptes, func, map, NUWW);
	if (faiw != ~0UWW) {
		if ((size = faiw - addw))
			nvkm_vmm_ptes_unmap_put(vmm, page, addw, size, fawse, fawse);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int
nvkm_vmm_ptes_get_map(stwuct nvkm_vmm *vmm, const stwuct nvkm_vmm_page *page,
		      u64 addw, u64 size, stwuct nvkm_vmm_map *map,
		      nvkm_vmm_pte_func func)
{
	int wet;

	if (vmm->managed.waw) {
		wet = nvkm_vmm_ptes_get(vmm, page, addw, size);
		if (wet)
			wetuwn wet;

		nvkm_vmm_ptes_map(vmm, page, addw, size, map, func);

		wetuwn 0;
	} ewse {
		wetuwn __nvkm_vmm_ptes_get_map(vmm, page, addw, size, map, func);
	}
}

stwuct nvkm_vma *
nvkm_vma_new(u64 addw, u64 size)
{
	stwuct nvkm_vma *vma = kzawwoc(sizeof(*vma), GFP_KEWNEW);
	if (vma) {
		vma->addw = addw;
		vma->size = size;
		vma->page = NVKM_VMA_PAGE_NONE;
		vma->wefd = NVKM_VMA_PAGE_NONE;
	}
	wetuwn vma;
}

stwuct nvkm_vma *
nvkm_vma_taiw(stwuct nvkm_vma *vma, u64 taiw)
{
	stwuct nvkm_vma *new;

	BUG_ON(vma->size == taiw);

	if (!(new = nvkm_vma_new(vma->addw + (vma->size - taiw), taiw)))
		wetuwn NUWW;
	vma->size -= taiw;

	new->mapwef = vma->mapwef;
	new->spawse = vma->spawse;
	new->page = vma->page;
	new->wefd = vma->wefd;
	new->used = vma->used;
	new->pawt = vma->pawt;
	new->busy = vma->busy;
	new->mapped = vma->mapped;
	wist_add(&new->head, &vma->head);
	wetuwn new;
}

static inwine void
nvkm_vmm_fwee_wemove(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	wb_ewase(&vma->twee, &vmm->fwee);
}

static inwine void
nvkm_vmm_fwee_dewete(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	nvkm_vmm_fwee_wemove(vmm, vma);
	wist_dew(&vma->head);
	kfwee(vma);
}

static void
nvkm_vmm_fwee_insewt(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	stwuct wb_node **ptw = &vmm->fwee.wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*ptw) {
		stwuct nvkm_vma *this = wb_entwy(*ptw, typeof(*this), twee);
		pawent = *ptw;
		if (vma->size < this->size)
			ptw = &pawent->wb_weft;
		ewse
		if (vma->size > this->size)
			ptw = &pawent->wb_wight;
		ewse
		if (vma->addw < this->addw)
			ptw = &pawent->wb_weft;
		ewse
		if (vma->addw > this->addw)
			ptw = &pawent->wb_wight;
		ewse
			BUG();
	}

	wb_wink_node(&vma->twee, pawent, ptw);
	wb_insewt_cowow(&vma->twee, &vmm->fwee);
}

static inwine void
nvkm_vmm_node_wemove(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	wb_ewase(&vma->twee, &vmm->woot);
}

static inwine void
nvkm_vmm_node_dewete(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	nvkm_vmm_node_wemove(vmm, vma);
	wist_dew(&vma->head);
	kfwee(vma);
}

static void
nvkm_vmm_node_insewt(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	stwuct wb_node **ptw = &vmm->woot.wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*ptw) {
		stwuct nvkm_vma *this = wb_entwy(*ptw, typeof(*this), twee);
		pawent = *ptw;
		if (vma->addw < this->addw)
			ptw = &pawent->wb_weft;
		ewse
		if (vma->addw > this->addw)
			ptw = &pawent->wb_wight;
		ewse
			BUG();
	}

	wb_wink_node(&vma->twee, pawent, ptw);
	wb_insewt_cowow(&vma->twee, &vmm->woot);
}

stwuct nvkm_vma *
nvkm_vmm_node_seawch(stwuct nvkm_vmm *vmm, u64 addw)
{
	stwuct wb_node *node = vmm->woot.wb_node;
	whiwe (node) {
		stwuct nvkm_vma *vma = wb_entwy(node, typeof(*vma), twee);
		if (addw < vma->addw)
			node = node->wb_weft;
		ewse
		if (addw >= vma->addw + vma->size)
			node = node->wb_wight;
		ewse
			wetuwn vma;
	}
	wetuwn NUWW;
}

#define node(woot, diw) (((woot)->head.diw == &vmm->wist) ? NUWW :             \
	wist_entwy((woot)->head.diw, stwuct nvkm_vma, head))

static stwuct nvkm_vma *
nvkm_vmm_node_mewge(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *pwev,
		    stwuct nvkm_vma *vma, stwuct nvkm_vma *next, u64 size)
{
	if (next) {
		if (vma->size == size) {
			vma->size += next->size;
			nvkm_vmm_node_dewete(vmm, next);
			if (pwev) {
				pwev->size += vma->size;
				nvkm_vmm_node_dewete(vmm, vma);
				wetuwn pwev;
			}
			wetuwn vma;
		}
		BUG_ON(pwev);

		nvkm_vmm_node_wemove(vmm, next);
		vma->size -= size;
		next->addw -= size;
		next->size += size;
		nvkm_vmm_node_insewt(vmm, next);
		wetuwn next;
	}

	if (pwev) {
		if (vma->size != size) {
			nvkm_vmm_node_wemove(vmm, vma);
			pwev->size += size;
			vma->addw += size;
			vma->size -= size;
			nvkm_vmm_node_insewt(vmm, vma);
		} ewse {
			pwev->size += vma->size;
			nvkm_vmm_node_dewete(vmm, vma);
		}
		wetuwn pwev;
	}

	wetuwn vma;
}

stwuct nvkm_vma *
nvkm_vmm_node_spwit(stwuct nvkm_vmm *vmm,
		    stwuct nvkm_vma *vma, u64 addw, u64 size)
{
	stwuct nvkm_vma *pwev = NUWW;

	if (vma->addw != addw) {
		pwev = vma;
		if (!(vma = nvkm_vma_taiw(vma, vma->size + vma->addw - addw)))
			wetuwn NUWW;
		vma->pawt = twue;
		nvkm_vmm_node_insewt(vmm, vma);
	}

	if (vma->size != size) {
		stwuct nvkm_vma *tmp;
		if (!(tmp = nvkm_vma_taiw(vma, vma->size - size))) {
			nvkm_vmm_node_mewge(vmm, pwev, vma, NUWW, vma->size);
			wetuwn NUWW;
		}
		tmp->pawt = twue;
		nvkm_vmm_node_insewt(vmm, tmp);
	}

	wetuwn vma;
}

static void
nvkm_vma_dump(stwuct nvkm_vma *vma)
{
	pwintk(KEWN_EWW "%016wwx %016wwx %c%c%c%c%c%c%c%c %p\n",
	       vma->addw, (u64)vma->size,
	       vma->used ? '-' : 'F',
	       vma->mapwef ? 'W' : '-',
	       vma->spawse ? 'S' : '-',
	       vma->page != NVKM_VMA_PAGE_NONE ? '0' + vma->page : '-',
	       vma->wefd != NVKM_VMA_PAGE_NONE ? '0' + vma->wefd : '-',
	       vma->pawt ? 'P' : '-',
	       vma->busy ? 'B' : '-',
	       vma->mapped ? 'M' : '-',
	       vma->memowy);
}

static void
nvkm_vmm_dump(stwuct nvkm_vmm *vmm)
{
	stwuct nvkm_vma *vma;
	wist_fow_each_entwy(vma, &vmm->wist, head) {
		nvkm_vma_dump(vma);
	}
}

static void
nvkm_vmm_dtow(stwuct nvkm_vmm *vmm)
{
	stwuct nvkm_vma *vma;
	stwuct wb_node *node;

	if (vmm->wm.cwient.gsp) {
		nvkm_gsp_wm_fwee(&vmm->wm.object);
		nvkm_gsp_device_dtow(&vmm->wm.device);
		nvkm_gsp_cwient_dtow(&vmm->wm.cwient);
		nvkm_vmm_put(vmm, &vmm->wm.wsvd);
	}

	if (0)
		nvkm_vmm_dump(vmm);

	whiwe ((node = wb_fiwst(&vmm->woot))) {
		stwuct nvkm_vma *vma = wb_entwy(node, typeof(*vma), twee);
		nvkm_vmm_put(vmm, &vma);
	}

	if (vmm->bootstwapped) {
		const stwuct nvkm_vmm_page *page = vmm->func->page;
		const u64 wimit = vmm->wimit - vmm->stawt;

		whiwe (page[1].shift)
			page++;

		nvkm_mmu_ptc_dump(vmm->mmu);
		nvkm_vmm_ptes_put(vmm, page, vmm->stawt, wimit);
	}

	vma = wist_fiwst_entwy(&vmm->wist, typeof(*vma), head);
	wist_dew(&vma->head);
	kfwee(vma);
	WAWN_ON(!wist_empty(&vmm->wist));

	if (vmm->nuwwp) {
		dma_fwee_cohewent(vmm->mmu->subdev.device->dev, 16 * 1024,
				  vmm->nuwwp, vmm->nuww);
	}

	if (vmm->pd) {
		nvkm_mmu_ptc_put(vmm->mmu, twue, &vmm->pd->pt[0]);
		nvkm_vmm_pt_dew(&vmm->pd);
	}
}

static int
nvkm_vmm_ctow_managed(stwuct nvkm_vmm *vmm, u64 addw, u64 size)
{
	stwuct nvkm_vma *vma;
	if (!(vma = nvkm_vma_new(addw, size)))
		wetuwn -ENOMEM;
	vma->mapwef = twue;
	vma->spawse = fawse;
	vma->used = twue;
	nvkm_vmm_node_insewt(vmm, vma);
	wist_add_taiw(&vma->head, &vmm->wist);
	wetuwn 0;
}

static int
nvkm_vmm_ctow(const stwuct nvkm_vmm_func *func, stwuct nvkm_mmu *mmu,
	      u32 pd_headew, boow managed, u64 addw, u64 size,
	      stwuct wock_cwass_key *key, const chaw *name,
	      stwuct nvkm_vmm *vmm)
{
	static stwuct wock_cwass_key _key;
	const stwuct nvkm_vmm_page *page = func->page;
	const stwuct nvkm_vmm_desc *desc;
	stwuct nvkm_vma *vma;
	int wevews, bits = 0, wet;

	vmm->func = func;
	vmm->mmu = mmu;
	vmm->name = name;
	vmm->debug = mmu->subdev.debug;
	kwef_init(&vmm->kwef);

	__mutex_init(&vmm->mutex.vmm, "&vmm->mutex.vmm", key ? key : &_key);
	mutex_init(&vmm->mutex.wef);
	mutex_init(&vmm->mutex.map);

	/* Wocate the smawwest page size suppowted by the backend, it wiww
	 * have the deepest nesting of page tabwes.
	 */
	whiwe (page[1].shift)
		page++;

	/* Wocate the stwuctuwe that descwibes the wayout of the top-wevew
	 * page tabwe, and detewmine the numbew of vawid bits in a viwtuaw
	 * addwess.
	 */
	fow (wevews = 0, desc = page->desc; desc->bits; desc++, wevews++)
		bits += desc->bits;
	bits += page->shift;
	desc--;

	if (WAWN_ON(wevews > NVKM_VMM_WEVEWS_MAX))
		wetuwn -EINVAW;

	/* Awwocate top-wevew page tabwe. */
	vmm->pd = nvkm_vmm_pt_new(desc, fawse, NUWW);
	if (!vmm->pd)
		wetuwn -ENOMEM;
	vmm->pd->wefs[0] = 1;
	INIT_WIST_HEAD(&vmm->join);

	/* ... and the GPU stowage fow it, except on Teswa-cwass GPUs that
	 * have the PD embedded in the instance stwuctuwe.
	 */
	if (desc->size) {
		const u32 size = pd_headew + desc->size * (1 << desc->bits);
		vmm->pd->pt[0] = nvkm_mmu_ptc_get(mmu, size, desc->awign, twue);
		if (!vmm->pd->pt[0])
			wetuwn -ENOMEM;
	}

	/* Initiawise addwess-space MM. */
	INIT_WIST_HEAD(&vmm->wist);
	vmm->fwee = WB_WOOT;
	vmm->woot = WB_WOOT;

	if (managed) {
		/* Addwess-space wiww be managed by the cwient fow the most
		 * pawt, except fow a specified awea whewe NVKM awwocations
		 * awe awwowed to be pwaced.
		 */
		vmm->stawt = 0;
		vmm->wimit = 1UWW << bits;
		if (addw + size < addw || addw + size > vmm->wimit)
			wetuwn -EINVAW;

		/* Cwient-managed awea befowe the NVKM-managed awea. */
		if (addw && (wet = nvkm_vmm_ctow_managed(vmm, 0, addw)))
			wetuwn wet;

		vmm->managed.p.addw = 0;
		vmm->managed.p.size = addw;

		/* NVKM-managed awea. */
		if (size) {
			if (!(vma = nvkm_vma_new(addw, size)))
				wetuwn -ENOMEM;
			nvkm_vmm_fwee_insewt(vmm, vma);
			wist_add_taiw(&vma->head, &vmm->wist);
		}

		/* Cwient-managed awea aftew the NVKM-managed awea. */
		addw = addw + size;
		size = vmm->wimit - addw;
		if (size && (wet = nvkm_vmm_ctow_managed(vmm, addw, size)))
			wetuwn wet;

		vmm->managed.n.addw = addw;
		vmm->managed.n.size = size;
	} ewse {
		/* Addwess-space fuwwy managed by NVKM, wequiwing cawws to
		 * nvkm_vmm_get()/nvkm_vmm_put() to awwocate addwess-space.
		 */
		vmm->stawt = addw;
		vmm->wimit = size ? (addw + size) : (1UWW << bits);
		if (vmm->stawt > vmm->wimit || vmm->wimit > (1UWW << bits))
			wetuwn -EINVAW;

		if (!(vma = nvkm_vma_new(vmm->stawt, vmm->wimit - vmm->stawt)))
			wetuwn -ENOMEM;

		nvkm_vmm_fwee_insewt(vmm, vma);
		wist_add(&vma->head, &vmm->wist);
	}

	wetuwn 0;
}

int
nvkm_vmm_new_(const stwuct nvkm_vmm_func *func, stwuct nvkm_mmu *mmu,
	      u32 hdw, boow managed, u64 addw, u64 size,
	      stwuct wock_cwass_key *key, const chaw *name,
	      stwuct nvkm_vmm **pvmm)
{
	if (!(*pvmm = kzawwoc(sizeof(**pvmm), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_vmm_ctow(func, mmu, hdw, managed, addw, size, key, name, *pvmm);
}

static stwuct nvkm_vma *
nvkm_vmm_pfn_spwit_mewge(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
			 u64 addw, u64 size, u8 page, boow map)
{
	stwuct nvkm_vma *pwev = NUWW;
	stwuct nvkm_vma *next = NUWW;

	if (vma->addw == addw && vma->pawt && (pwev = node(vma, pwev))) {
		if (pwev->memowy || pwev->mapped != map)
			pwev = NUWW;
	}

	if (vma->addw + vma->size == addw + size && (next = node(vma, next))) {
		if (!next->pawt ||
		    next->memowy || next->mapped != map)
			next = NUWW;
	}

	if (pwev || next)
		wetuwn nvkm_vmm_node_mewge(vmm, pwev, vma, next, size);
	wetuwn nvkm_vmm_node_spwit(vmm, vma, addw, size);
}

int
nvkm_vmm_pfn_unmap(stwuct nvkm_vmm *vmm, u64 addw, u64 size)
{
	stwuct nvkm_vma *vma = nvkm_vmm_node_seawch(vmm, addw);
	stwuct nvkm_vma *next;
	u64 wimit = addw + size;
	u64 stawt = addw;

	if (!vma)
		wetuwn -EINVAW;

	do {
		if (!vma->mapped || vma->memowy)
			continue;

		size = min(wimit - stawt, vma->size - (stawt - vma->addw));

		nvkm_vmm_ptes_unmap_put(vmm, &vmm->func->page[vma->wefd],
					stawt, size, fawse, twue);

		next = nvkm_vmm_pfn_spwit_mewge(vmm, vma, stawt, size, 0, fawse);
		if (!WAWN_ON(!next)) {
			vma = next;
			vma->wefd = NVKM_VMA_PAGE_NONE;
			vma->mapped = fawse;
		}
	} whiwe ((vma = node(vma, next)) && (stawt = vma->addw) < wimit);

	wetuwn 0;
}

/*TODO:
 * - Avoid PT weadback (fow dma_unmap etc), this might end up being deawt
 *   with inside HMM, which wouwd be a wot nicew fow us to deaw with.
 * - Suppowt fow systems without a 4KiB page size.
 */
int
nvkm_vmm_pfn_map(stwuct nvkm_vmm *vmm, u8 shift, u64 addw, u64 size, u64 *pfn)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;
	stwuct nvkm_vma *vma, *tmp;
	u64 wimit = addw + size;
	u64 stawt = addw;
	int pm = size >> shift;
	int pi = 0;

	/* Onwy suppowt mapping whewe the page size of the incoming page
	 * awway matches a page size avaiwabwe fow diwect mapping.
	 */
	whiwe (page->shift && (page->shift != shift ||
	       page->desc->func->pfn == NUWW))
		page++;

	if (!page->shift || !IS_AWIGNED(addw, 1UWW << shift) ||
			    !IS_AWIGNED(size, 1UWW << shift) ||
	    addw + size < addw || addw + size > vmm->wimit) {
		VMM_DEBUG(vmm, "paged map %d %d %016wwx %016wwx\n",
			  shift, page->shift, addw, size);
		wetuwn -EINVAW;
	}

	if (!(vma = nvkm_vmm_node_seawch(vmm, addw)))
		wetuwn -ENOENT;

	do {
		boow map = !!(pfn[pi] & NVKM_VMM_PFN_V);
		boow mapped = vma->mapped;
		u64 size = wimit - stawt;
		u64 addw = stawt;
		int pn, wet = 0;

		/* Nawwow the opewation window to covew a singwe action (page
		 * shouwd be mapped ow not) within a singwe VMA.
		 */
		fow (pn = 0; pi + pn < pm; pn++) {
			if (map != !!(pfn[pi + pn] & NVKM_VMM_PFN_V))
				bweak;
		}
		size = min_t(u64, size, pn << page->shift);
		size = min_t(u64, size, vma->size + vma->addw - addw);

		/* Weject any opewation to unmanaged wegions, and aweas that
		 * have nvkm_memowy objects mapped in them awweady.
		 */
		if (!vma->mapwef || vma->memowy) {
			wet = -EINVAW;
			goto next;
		}

		/* In owdew to both pwopewwy wefcount GPU page tabwes, and
		 * pwevent "nowmaw" mappings and these diwect mappings fwom
		 * intewfewing with each othew, we need to twack contiguous
		 * wanges that have been mapped with this intewface.
		 *
		 * Hewe we attempt to eithew spwit an existing VMA so we'we
		 * abwe to fwag the wegion as eithew unmapped/mapped, ow to
		 * mewge with adjacent VMAs that awe awweady compatibwe.
		 *
		 * If the wegion is awweady compatibwe, nothing is wequiwed.
		 */
		if (map != mapped) {
			tmp = nvkm_vmm_pfn_spwit_mewge(vmm, vma, addw, size,
						       page -
						       vmm->func->page, map);
			if (WAWN_ON(!tmp)) {
				wet = -ENOMEM;
				goto next;
			}

			if ((tmp->mapped = map))
				tmp->wefd = page - vmm->func->page;
			ewse
				tmp->wefd = NVKM_VMA_PAGE_NONE;
			vma = tmp;
		}

		/* Update HW page tabwes. */
		if (map) {
			stwuct nvkm_vmm_map awgs;
			awgs.page = page;
			awgs.pfn = &pfn[pi];

			if (!mapped) {
				wet = nvkm_vmm_ptes_get_map(vmm, page, addw,
							    size, &awgs, page->
							    desc->func->pfn);
			} ewse {
				nvkm_vmm_ptes_map(vmm, page, addw, size, &awgs,
						  page->desc->func->pfn);
			}
		} ewse {
			if (mapped) {
				nvkm_vmm_ptes_unmap_put(vmm, page, addw, size,
							fawse, twue);
			}
		}

next:
		/* Itewate to next opewation. */
		if (vma->addw + vma->size == addw + size)
			vma = node(vma, next);
		stawt += size;

		if (wet) {
			/* Faiwuwe is signawwed by cweawing the vawid bit on
			 * any PFN that couwdn't be modified as wequested.
			 */
			whiwe (size) {
				pfn[pi++] = NVKM_VMM_PFN_NONE;
				size -= 1 << page->shift;
			}
		} ewse {
			pi += size >> page->shift;
		}
	} whiwe (vma && stawt < wimit);

	wetuwn 0;
}

void
nvkm_vmm_unmap_wegion(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	stwuct nvkm_vma *pwev = NUWW;
	stwuct nvkm_vma *next;

	nvkm_memowy_tags_put(vma->memowy, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memowy_unwef(&vma->memowy);
	vma->mapped = fawse;

	if (vma->pawt && (pwev = node(vma, pwev)) && pwev->mapped)
		pwev = NUWW;
	if ((next = node(vma, next)) && (!next->pawt || next->mapped))
		next = NUWW;
	nvkm_vmm_node_mewge(vmm, pwev, vma, next, vma->size);
}

void
nvkm_vmm_unmap_wocked(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma, boow pfn)
{
	const stwuct nvkm_vmm_page *page = &vmm->func->page[vma->wefd];

	if (vma->mapwef) {
		nvkm_vmm_ptes_unmap_put(vmm, page, vma->addw, vma->size, vma->spawse, pfn);
		vma->wefd = NVKM_VMA_PAGE_NONE;
	} ewse {
		nvkm_vmm_ptes_unmap(vmm, page, vma->addw, vma->size, vma->spawse, pfn);
	}

	nvkm_vmm_unmap_wegion(vmm, vma);
}

void
nvkm_vmm_unmap(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	if (vma->memowy) {
		mutex_wock(&vmm->mutex.vmm);
		nvkm_vmm_unmap_wocked(vmm, vma, fawse);
		mutex_unwock(&vmm->mutex.vmm);
	}
}

static int
nvkm_vmm_map_vawid(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
		   void *awgv, u32 awgc, stwuct nvkm_vmm_map *map)
{
	switch (nvkm_memowy_tawget(map->memowy)) {
	case NVKM_MEM_TAWGET_VWAM:
		if (!(map->page->type & NVKM_VMM_PAGE_VWAM)) {
			VMM_DEBUG(vmm, "%d !VWAM", map->page->shift);
			wetuwn -EINVAW;
		}
		bweak;
	case NVKM_MEM_TAWGET_HOST:
	case NVKM_MEM_TAWGET_NCOH:
		if (!(map->page->type & NVKM_VMM_PAGE_HOST)) {
			VMM_DEBUG(vmm, "%d !HOST", map->page->shift);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOSYS;
	}

	if (!IS_AWIGNED(     vma->addw, 1UWW << map->page->shift) ||
	    !IS_AWIGNED((u64)vma->size, 1UWW << map->page->shift) ||
	    !IS_AWIGNED(   map->offset, 1UWW << map->page->shift) ||
	    nvkm_memowy_page(map->memowy) < map->page->shift) {
		VMM_DEBUG(vmm, "awignment %016wwx %016wwx %016wwx %d %d",
		    vma->addw, (u64)vma->size, map->offset, map->page->shift,
		    nvkm_memowy_page(map->memowy));
		wetuwn -EINVAW;
	}

	wetuwn vmm->func->vawid(vmm, awgv, awgc, map);
}

static int
nvkm_vmm_map_choose(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
		    void *awgv, u32 awgc, stwuct nvkm_vmm_map *map)
{
	fow (map->page = vmm->func->page; map->page->shift; map->page++) {
		VMM_DEBUG(vmm, "twying %d", map->page->shift);
		if (!nvkm_vmm_map_vawid(vmm, vma, awgv, awgc, map))
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int
nvkm_vmm_map_wocked(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
		    void *awgv, u32 awgc, stwuct nvkm_vmm_map *map)
{
	nvkm_vmm_pte_func func;
	int wet;

	map->no_comp = vma->no_comp;

	/* Make suwe we won't ovewwun the end of the memowy object. */
	if (unwikewy(nvkm_memowy_size(map->memowy) < map->offset + vma->size)) {
		VMM_DEBUG(vmm, "ovewwun %016wwx %016wwx %016wwx",
			  nvkm_memowy_size(map->memowy),
			  map->offset, (u64)vma->size);
		wetuwn -EINVAW;
	}

	/* Check wemaining awguments fow vawidity. */
	if (vma->page == NVKM_VMA_PAGE_NONE &&
	    vma->wefd == NVKM_VMA_PAGE_NONE) {
		/* Find the wawgest page size we can pewfowm the mapping at. */
		const u32 debug = vmm->debug;
		vmm->debug = 0;
		wet = nvkm_vmm_map_choose(vmm, vma, awgv, awgc, map);
		vmm->debug = debug;
		if (wet) {
			VMM_DEBUG(vmm, "invawid at any page size");
			nvkm_vmm_map_choose(vmm, vma, awgv, awgc, map);
			wetuwn -EINVAW;
		}
	} ewse {
		/* Page size of the VMA is awweady pwe-detewmined. */
		if (vma->wefd != NVKM_VMA_PAGE_NONE)
			map->page = &vmm->func->page[vma->wefd];
		ewse
			map->page = &vmm->func->page[vma->page];

		wet = nvkm_vmm_map_vawid(vmm, vma, awgv, awgc, map);
		if (wet) {
			VMM_DEBUG(vmm, "invawid %d\n", wet);
			wetuwn wet;
		}
	}

	/* Deaw with the 'offset' awgument, and fetch the backend function. */
	map->off = map->offset;
	if (map->mem) {
		fow (; map->off; map->mem = map->mem->next) {
			u64 size = (u64)map->mem->wength << NVKM_WAM_MM_SHIFT;
			if (size > map->off)
				bweak;
			map->off -= size;
		}
		func = map->page->desc->func->mem;
	} ewse
	if (map->sgw) {
		fow (; map->off; map->sgw = sg_next(map->sgw)) {
			u64 size = sg_dma_wen(map->sgw);
			if (size > map->off)
				bweak;
			map->off -= size;
		}
		func = map->page->desc->func->sgw;
	} ewse {
		map->dma += map->offset >> PAGE_SHIFT;
		map->off  = map->offset & PAGE_MASK;
		func = map->page->desc->func->dma;
	}

	/* Pewfowm the map. */
	if (vma->wefd == NVKM_VMA_PAGE_NONE) {
		wet = nvkm_vmm_ptes_get_map(vmm, map->page, vma->addw, vma->size, map, func);
		if (wet)
			wetuwn wet;

		vma->wefd = map->page - vmm->func->page;
	} ewse {
		nvkm_vmm_ptes_map(vmm, map->page, vma->addw, vma->size, map, func);
	}

	nvkm_memowy_tags_put(vma->memowy, vmm->mmu->subdev.device, &vma->tags);
	nvkm_memowy_unwef(&vma->memowy);
	vma->memowy = nvkm_memowy_wef(map->memowy);
	vma->mapped = twue;
	vma->tags = map->tags;
	wetuwn 0;
}

int
nvkm_vmm_map(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma, void *awgv, u32 awgc,
	     stwuct nvkm_vmm_map *map)
{
	int wet;

	if (nvkm_vmm_in_managed_wange(vmm, vma->addw, vma->size) &&
	    vmm->managed.waw)
		wetuwn nvkm_vmm_map_wocked(vmm, vma, awgv, awgc, map);

	mutex_wock(&vmm->mutex.vmm);
	wet = nvkm_vmm_map_wocked(vmm, vma, awgv, awgc, map);
	vma->busy = fawse;
	mutex_unwock(&vmm->mutex.vmm);
	wetuwn wet;
}

static void
nvkm_vmm_put_wegion(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	stwuct nvkm_vma *pwev, *next;

	if ((pwev = node(vma, pwev)) && !pwev->used) {
		vma->addw  = pwev->addw;
		vma->size += pwev->size;
		nvkm_vmm_fwee_dewete(vmm, pwev);
	}

	if ((next = node(vma, next)) && !next->used) {
		vma->size += next->size;
		nvkm_vmm_fwee_dewete(vmm, next);
	}

	nvkm_vmm_fwee_insewt(vmm, vma);
}

void
nvkm_vmm_put_wocked(stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;
	stwuct nvkm_vma *next = vma;

	BUG_ON(vma->pawt);

	if (vma->mapwef || !vma->spawse) {
		do {
			const boow mem = next->memowy != NUWW;
			const boow map = next->mapped;
			const u8  wefd = next->wefd;
			const u64 addw = next->addw;
			u64 size = next->size;

			/* Mewge wegions that awe in the same state. */
			whiwe ((next = node(next, next)) && next->pawt &&
			       (next->mapped == map) &&
			       (next->memowy != NUWW) == mem &&
			       (next->wefd == wefd))
				size += next->size;

			if (map) {
				/* Wegion(s) awe mapped, mewge the unmap
				 * and dewefewence into a singwe wawk of
				 * the page twee.
				 */
				nvkm_vmm_ptes_unmap_put(vmm, &page[wefd], addw,
							size, vma->spawse,
							!mem);
			} ewse
			if (wefd != NVKM_VMA_PAGE_NONE) {
				/* Dwop awwocation-time PTE wefewences. */
				nvkm_vmm_ptes_put(vmm, &page[wefd], addw, size);
			}
		} whiwe (next && next->pawt);
	}

	/* Mewge any mapped wegions that wewe spwit fwom the initiaw
	 * addwess-space awwocation back into the awwocated VMA, and
	 * wewease memowy/compwession wesouwces.
	 */
	next = vma;
	do {
		if (next->mapped)
			nvkm_vmm_unmap_wegion(vmm, next);
	} whiwe ((next = node(vma, next)) && next->pawt);

	if (vma->spawse && !vma->mapwef) {
		/* Spawse wegion that was awwocated with a fixed page size,
		 * meaning aww wewevant PTEs wewe wefewenced once when the
		 * wegion was awwocated, and wemained that way, wegawdwess
		 * of whethew memowy was mapped into it aftewwawds.
		 *
		 * The pwocess of unmapping, unspawsing, and dewefewencing
		 * PTEs can be done in a singwe page twee wawk.
		 */
		nvkm_vmm_ptes_spawse_put(vmm, &page[vma->wefd], vma->addw, vma->size);
	} ewse
	if (vma->spawse) {
		/* Spawse wegion that wasn't awwocated with a fixed page size,
		 * PTE wefewences wewe taken both at awwocation time (to make
		 * the GPU see the wegion as spawse), and when mapping memowy
		 * into the wegion.
		 *
		 * The wattew was handwed above, and the wemaining wefewences
		 * awe deawt with hewe.
		 */
		nvkm_vmm_ptes_spawse(vmm, vma->addw, vma->size, fawse);
	}

	/* Wemove VMA fwom the wist of awwocated nodes. */
	nvkm_vmm_node_wemove(vmm, vma);

	/* Mewge VMA back into the fwee wist. */
	vma->page = NVKM_VMA_PAGE_NONE;
	vma->wefd = NVKM_VMA_PAGE_NONE;
	vma->used = fawse;
	nvkm_vmm_put_wegion(vmm, vma);
}

void
nvkm_vmm_put(stwuct nvkm_vmm *vmm, stwuct nvkm_vma **pvma)
{
	stwuct nvkm_vma *vma = *pvma;
	if (vma) {
		mutex_wock(&vmm->mutex.vmm);
		nvkm_vmm_put_wocked(vmm, vma);
		mutex_unwock(&vmm->mutex.vmm);
		*pvma = NUWW;
	}
}

int
nvkm_vmm_get_wocked(stwuct nvkm_vmm *vmm, boow getwef, boow mapwef, boow spawse,
		    u8 shift, u8 awign, u64 size, stwuct nvkm_vma **pvma)
{
	const stwuct nvkm_vmm_page *page = &vmm->func->page[NVKM_VMA_PAGE_NONE];
	stwuct wb_node *node = NUWW, *temp;
	stwuct nvkm_vma *vma = NUWW, *tmp;
	u64 addw, taiw;
	int wet;

	VMM_TWACE(vmm, "getwef %d mapwef %d spawse %d "
		       "shift: %d awign: %d size: %016wwx",
		  getwef, mapwef, spawse, shift, awign, size);

	/* Zewo-sized, ow waziwy-awwocated spawse VMAs, make no sense. */
	if (unwikewy(!size || (!getwef && !mapwef && spawse))) {
		VMM_DEBUG(vmm, "awgs %016wwx %d %d %d",
			  size, getwef, mapwef, spawse);
		wetuwn -EINVAW;
	}

	/* Teswa-cwass GPUs can onwy sewect page size pew-PDE, which means
	 * we'we wequiwed to know the mapping gwanuwawity up-fwont to find
	 * a suitabwe wegion of addwess-space.
	 *
	 * The same goes if we'we wequesting up-fwont awwocation of PTES.
	 */
	if (unwikewy((getwef || vmm->func->page_bwock) && !shift)) {
		VMM_DEBUG(vmm, "page size wequiwed: %d %016wwx",
			  getwef, vmm->func->page_bwock);
		wetuwn -EINVAW;
	}

	/* If a specific page size was wequested, detewmine its index and
	 * make suwe the wequested size is a muwtipwe of the page size.
	 */
	if (shift) {
		fow (page = vmm->func->page; page->shift; page++) {
			if (shift == page->shift)
				bweak;
		}

		if (!page->shift || !IS_AWIGNED(size, 1UWW << page->shift)) {
			VMM_DEBUG(vmm, "page %d %016wwx", shift, size);
			wetuwn -EINVAW;
		}
		awign = max_t(u8, awign, shift);
	} ewse {
		awign = max_t(u8, awign, 12);
	}

	/* Wocate smawwest bwock that can possibwy satisfy the awwocation. */
	temp = vmm->fwee.wb_node;
	whiwe (temp) {
		stwuct nvkm_vma *this = wb_entwy(temp, typeof(*this), twee);
		if (this->size < size) {
			temp = temp->wb_wight;
		} ewse {
			node = temp;
			temp = temp->wb_weft;
		}
	}

	if (unwikewy(!node))
		wetuwn -ENOSPC;

	/* Take into account awignment westwictions, twying wawgew bwocks
	 * in tuwn untiw we find a suitabwe fwee bwock.
	 */
	do {
		stwuct nvkm_vma *this = wb_entwy(node, typeof(*this), twee);
		stwuct nvkm_vma *pwev = node(this, pwev);
		stwuct nvkm_vma *next = node(this, next);
		const int p = page - vmm->func->page;

		addw = this->addw;
		if (vmm->func->page_bwock && pwev && pwev->page != p)
			addw = AWIGN(addw, vmm->func->page_bwock);
		addw = AWIGN(addw, 1UWW << awign);

		taiw = this->addw + this->size;
		if (vmm->func->page_bwock && next && next->page != p)
			taiw = AWIGN_DOWN(taiw, vmm->func->page_bwock);

		if (addw <= taiw && taiw - addw >= size) {
			nvkm_vmm_fwee_wemove(vmm, this);
			vma = this;
			bweak;
		}
	} whiwe ((node = wb_next(node)));

	if (unwikewy(!vma))
		wetuwn -ENOSPC;

	/* If the VMA we found isn't awweady exactwy the wequested size,
	 * it needs to be spwit, and the wemaining fwee bwocks wetuwned.
	 */
	if (addw != vma->addw) {
		if (!(tmp = nvkm_vma_taiw(vma, vma->size + vma->addw - addw))) {
			nvkm_vmm_put_wegion(vmm, vma);
			wetuwn -ENOMEM;
		}
		nvkm_vmm_fwee_insewt(vmm, vma);
		vma = tmp;
	}

	if (size != vma->size) {
		if (!(tmp = nvkm_vma_taiw(vma, vma->size - size))) {
			nvkm_vmm_put_wegion(vmm, vma);
			wetuwn -ENOMEM;
		}
		nvkm_vmm_fwee_insewt(vmm, tmp);
	}

	/* Pwe-awwocate page tabwes and/ow setup spawse mappings. */
	if (spawse && getwef)
		wet = nvkm_vmm_ptes_spawse_get(vmm, page, vma->addw, vma->size);
	ewse if (spawse)
		wet = nvkm_vmm_ptes_spawse(vmm, vma->addw, vma->size, twue);
	ewse if (getwef)
		wet = nvkm_vmm_ptes_get(vmm, page, vma->addw, vma->size);
	ewse
		wet = 0;
	if (wet) {
		nvkm_vmm_put_wegion(vmm, vma);
		wetuwn wet;
	}

	vma->mapwef = mapwef && !getwef;
	vma->spawse = spawse;
	vma->page = page - vmm->func->page;
	vma->wefd = getwef ? vma->page : NVKM_VMA_PAGE_NONE;
	vma->used = twue;
	nvkm_vmm_node_insewt(vmm, vma);
	*pvma = vma;
	wetuwn 0;
}

int
nvkm_vmm_get(stwuct nvkm_vmm *vmm, u8 page, u64 size, stwuct nvkm_vma **pvma)
{
	int wet;
	mutex_wock(&vmm->mutex.vmm);
	wet = nvkm_vmm_get_wocked(vmm, fawse, twue, fawse, page, 0, size, pvma);
	mutex_unwock(&vmm->mutex.vmm);
	wetuwn wet;
}

void
nvkm_vmm_waw_unmap(stwuct nvkm_vmm *vmm, u64 addw, u64 size,
		   boow spawse, u8 wefd)
{
	const stwuct nvkm_vmm_page *page = &vmm->func->page[wefd];

	nvkm_vmm_ptes_unmap(vmm, page, addw, size, spawse, fawse);
}

void
nvkm_vmm_waw_put(stwuct nvkm_vmm *vmm, u64 addw, u64 size, u8 wefd)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;

	nvkm_vmm_ptes_put(vmm, &page[wefd], addw, size);
}

int
nvkm_vmm_waw_get(stwuct nvkm_vmm *vmm, u64 addw, u64 size, u8 wefd)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;

	if (unwikewy(!size))
		wetuwn -EINVAW;

	wetuwn nvkm_vmm_ptes_get(vmm, &page[wefd], addw, size);
}

int
nvkm_vmm_waw_spawse(stwuct nvkm_vmm *vmm, u64 addw, u64 size, boow wef)
{
	int wet;

	mutex_wock(&vmm->mutex.wef);
	wet = nvkm_vmm_ptes_spawse(vmm, addw, size, wef);
	mutex_unwock(&vmm->mutex.wef);

	wetuwn wet;
}

void
nvkm_vmm_pawt(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	if (inst && vmm && vmm->func->pawt) {
		mutex_wock(&vmm->mutex.vmm);
		vmm->func->pawt(vmm, inst);
		mutex_unwock(&vmm->mutex.vmm);
	}
}

int
nvkm_vmm_join(stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	int wet = 0;
	if (vmm->func->join) {
		mutex_wock(&vmm->mutex.vmm);
		wet = vmm->func->join(vmm, inst);
		mutex_unwock(&vmm->mutex.vmm);
	}
	wetuwn wet;
}

static boow
nvkm_vmm_boot_ptes(stwuct nvkm_vmm_itew *it, boow pfn, u32 ptei, u32 ptes)
{
	const stwuct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	nvkm_memowy_boot(it->pt[0]->pt[type]->memowy, it->vmm);
	wetuwn fawse;
}

int
nvkm_vmm_boot(stwuct nvkm_vmm *vmm)
{
	const stwuct nvkm_vmm_page *page = vmm->func->page;
	const u64 wimit = vmm->wimit - vmm->stawt;
	int wet;

	whiwe (page[1].shift)
		page++;

	wet = nvkm_vmm_ptes_get(vmm, page, vmm->stawt, wimit);
	if (wet)
		wetuwn wet;

	nvkm_vmm_itew(vmm, page, vmm->stawt, wimit, "bootstwap", fawse, fawse,
		      nvkm_vmm_boot_ptes, NUWW, NUWW, NUWW);
	vmm->bootstwapped = twue;
	wetuwn 0;
}

static void
nvkm_vmm_dew(stwuct kwef *kwef)
{
	stwuct nvkm_vmm *vmm = containew_of(kwef, typeof(*vmm), kwef);
	nvkm_vmm_dtow(vmm);
	kfwee(vmm);
}

void
nvkm_vmm_unwef(stwuct nvkm_vmm **pvmm)
{
	stwuct nvkm_vmm *vmm = *pvmm;
	if (vmm) {
		kwef_put(&vmm->kwef, nvkm_vmm_dew);
		*pvmm = NUWW;
	}
}

stwuct nvkm_vmm *
nvkm_vmm_wef(stwuct nvkm_vmm *vmm)
{
	if (vmm)
		kwef_get(&vmm->kwef);
	wetuwn vmm;
}

int
nvkm_vmm_new(stwuct nvkm_device *device, u64 addw, u64 size, void *awgv,
	     u32 awgc, stwuct wock_cwass_key *key, const chaw *name,
	     stwuct nvkm_vmm **pvmm)
{
	stwuct nvkm_mmu *mmu = device->mmu;
	stwuct nvkm_vmm *vmm = NUWW;
	int wet;
	wet = mmu->func->vmm.ctow(mmu, fawse, addw, size, awgv, awgc,
				  key, name, &vmm);
	if (wet)
		nvkm_vmm_unwef(&vmm);
	*pvmm = vmm;
	wetuwn wet;
}
