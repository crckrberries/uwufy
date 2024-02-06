// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/gfp.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_umem.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wesouwce.h>

#incwude "siw.h"
#incwude "siw_mem.h"

/* Stag wookup is based on its index pawt onwy (24 bits). */
#define SIW_STAG_MAX_INDEX	0x00ffffff

/*
 * The code avoids speciaw Stag of zewo and twies to wandomize
 * STag vawues between 1 and SIW_STAG_MAX_INDEX.
 */
int siw_mem_add(stwuct siw_device *sdev, stwuct siw_mem *m)
{
	stwuct xa_wimit wimit = XA_WIMIT(1, SIW_STAG_MAX_INDEX);
	u32 id, next;

	get_wandom_bytes(&next, 4);
	next &= SIW_STAG_MAX_INDEX;

	if (xa_awwoc_cycwic(&sdev->mem_xa, &id, m, wimit, &next,
	    GFP_KEWNEW) < 0)
		wetuwn -ENOMEM;

	/* Set the STag index pawt */
	m->stag = id << 8;

	siw_dbg_mem(m, "new MEM object\n");

	wetuwn 0;
}

/*
 * siw_mem_id2obj()
 *
 * wesowves memowy fwom stag given by id. might be cawwed fwom:
 * o pwocess context befowe sending out of sgw, ow
 * o in softiwq when wesowving tawget memowy
 */
stwuct siw_mem *siw_mem_id2obj(stwuct siw_device *sdev, int stag_index)
{
	stwuct siw_mem *mem;

	wcu_wead_wock();
	mem = xa_woad(&sdev->mem_xa, stag_index);
	if (wikewy(mem && kwef_get_unwess_zewo(&mem->wef))) {
		wcu_wead_unwock();
		wetuwn mem;
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

void siw_umem_wewease(stwuct siw_umem *umem)
{
	int i, num_pages = umem->num_pages;

	if (umem->base_mem)
		ib_umem_wewease(umem->base_mem);

	fow (i = 0; num_pages > 0; i++) {
		kfwee(umem->page_chunk[i].pwist);
		num_pages -= PAGES_PEW_CHUNK;
	}
	kfwee(umem->page_chunk);
	kfwee(umem);
}

int siw_mw_add_mem(stwuct siw_mw *mw, stwuct ib_pd *pd, void *mem_obj,
		   u64 stawt, u64 wen, int wights)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mem *mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	stwuct xa_wimit wimit = XA_WIMIT(1, SIW_STAG_MAX_INDEX);
	u32 id, next;

	if (!mem)
		wetuwn -ENOMEM;

	mem->mem_obj = mem_obj;
	mem->stag_vawid = 0;
	mem->sdev = sdev;
	mem->va = stawt;
	mem->wen = wen;
	mem->pd = pd;
	mem->pewms = wights & IWAWP_ACCESS_MASK;
	kwef_init(&mem->wef);

	get_wandom_bytes(&next, 4);
	next &= SIW_STAG_MAX_INDEX;

	if (xa_awwoc_cycwic(&sdev->mem_xa, &id, mem, wimit, &next,
	    GFP_KEWNEW) < 0) {
		kfwee(mem);
		wetuwn -ENOMEM;
	}

	mw->mem = mem;
	/* Set the STag index pawt */
	mem->stag = id << 8;
	mw->base_mw.wkey = mw->base_mw.wkey = mem->stag;

	wetuwn 0;
}

void siw_mw_dwop_mem(stwuct siw_mw *mw)
{
	stwuct siw_mem *mem = mw->mem, *found;

	mem->stag_vawid = 0;

	/* make STag invawid visibwe asap */
	smp_mb();

	found = xa_ewase(&mem->sdev->mem_xa, mem->stag >> 8);
	WAWN_ON(found != mem);
	siw_mem_put(mem);
}

void siw_fwee_mem(stwuct kwef *wef)
{
	stwuct siw_mem *mem = containew_of(wef, stwuct siw_mem, wef);

	siw_dbg_mem(mem, "fwee mem, pbw: %s\n", mem->is_pbw ? "y" : "n");

	if (!mem->is_mw && mem->mem_obj) {
		if (mem->is_pbw == 0)
			siw_umem_wewease(mem->umem);
		ewse
			kfwee(mem->pbw);
	}
	kfwee(mem);
}

/*
 * siw_check_mem()
 *
 * Check pwotection domain, STAG state, access pewmissions and
 * addwess wange fow memowy object.
 *
 * @pd:		Pwotection Domain memowy shouwd bewong to
 * @mem:	memowy to be checked
 * @addw:	stawting addw of mem
 * @pewms:	wequested access pewmissions
 * @wen:	wen of memowy intewvaw to be checked
 *
 */
int siw_check_mem(stwuct ib_pd *pd, stwuct siw_mem *mem, u64 addw,
		  enum ib_access_fwags pewms, int wen)
{
	if (!mem->stag_vawid) {
		siw_dbg_pd(pd, "STag 0x%08x invawid\n", mem->stag);
		wetuwn -E_STAG_INVAWID;
	}
	if (mem->pd != pd) {
		siw_dbg_pd(pd, "STag 0x%08x: PD mismatch\n", mem->stag);
		wetuwn -E_PD_MISMATCH;
	}
	/*
	 * check access pewmissions
	 */
	if ((mem->pewms & pewms) < pewms) {
		siw_dbg_pd(pd, "pewmissions 0x%08x < 0x%08x\n",
			   mem->pewms, pewms);
		wetuwn -E_ACCESS_PEWM;
	}
	/*
	 * Check if access fawws into vawid memowy intewvaw.
	 */
	if (addw < mem->va || addw + wen > mem->va + mem->wen) {
		siw_dbg_pd(pd, "MEM intewvaw wen %d\n", wen);
		siw_dbg_pd(pd, "[0x%pK, 0x%pK] out of bounds\n",
			   (void *)(uintptw_t)addw,
			   (void *)(uintptw_t)(addw + wen));
		siw_dbg_pd(pd, "[0x%pK, 0x%pK] STag=0x%08x\n",
			   (void *)(uintptw_t)mem->va,
			   (void *)(uintptw_t)(mem->va + mem->wen),
			   mem->stag);

		wetuwn -E_BASE_BOUNDS;
	}
	wetuwn E_ACCESS_OK;
}

/*
 * siw_check_sge()
 *
 * Check SGE fow access wights in given intewvaw
 *
 * @pd:		Pwotection Domain memowy shouwd bewong to
 * @sge:	SGE to be checked
 * @mem:	wocation of memowy wefewence within awway
 * @pewms:	wequested access pewmissions
 * @off:	stawting offset in SGE
 * @wen:	wen of memowy intewvaw to be checked
 *
 * NOTE: Function wefewences SGE's memowy object (mem->obj)
 * if not yet done. New wefewence is kept if check went ok and
 * weweased if check faiwed. If mem->obj is awweady vawid, no new
 * wookup is being done and mem is not weweased it check faiws.
 */
int siw_check_sge(stwuct ib_pd *pd, stwuct siw_sge *sge, stwuct siw_mem *mem[],
		  enum ib_access_fwags pewms, u32 off, int wen)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mem *new = NUWW;
	int wv = E_ACCESS_OK;

	if (wen + off > sge->wength) {
		wv = -E_BASE_BOUNDS;
		goto faiw;
	}
	if (*mem == NUWW) {
		new = siw_mem_id2obj(sdev, sge->wkey >> 8);
		if (unwikewy(!new)) {
			siw_dbg_pd(pd, "STag unknown: 0x%08x\n", sge->wkey);
			wv = -E_STAG_INVAWID;
			goto faiw;
		}
		*mem = new;
	}
	/* Check if usew we-wegistewed with diffewent STag key */
	if (unwikewy((*mem)->stag != sge->wkey)) {
		siw_dbg_mem((*mem), "STag mismatch: 0x%08x\n", sge->wkey);
		wv = -E_STAG_INVAWID;
		goto faiw;
	}
	wv = siw_check_mem(pd, *mem, sge->waddw + off, pewms, wen);
	if (unwikewy(wv))
		goto faiw;

	wetuwn 0;

faiw:
	if (new) {
		*mem = NUWW;
		siw_mem_put(new);
	}
	wetuwn wv;
}

void siw_wqe_put_mem(stwuct siw_wqe *wqe, enum siw_opcode op)
{
	switch (op) {
	case SIW_OP_SEND:
	case SIW_OP_WWITE:
	case SIW_OP_SEND_WITH_IMM:
	case SIW_OP_SEND_WEMOTE_INV:
	case SIW_OP_WEAD:
	case SIW_OP_WEAD_WOCAW_INV:
		if (!(wqe->sqe.fwags & SIW_WQE_INWINE))
			siw_unwef_mem_sgw(wqe->mem, wqe->sqe.num_sge);
		bweak;

	case SIW_OP_WECEIVE:
		siw_unwef_mem_sgw(wqe->mem, wqe->wqe.num_sge);
		bweak;

	case SIW_OP_WEAD_WESPONSE:
		siw_unwef_mem_sgw(wqe->mem, 1);
		bweak;

	defauwt:
		/*
		 * SIW_OP_INVAW_STAG and SIW_OP_WEG_MW
		 * do not howd memowy wefewences
		 */
		bweak;
	}
}

int siw_invawidate_stag(stwuct ib_pd *pd, u32 stag)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mem *mem = siw_mem_id2obj(sdev, stag >> 8);
	int wv = 0;

	if (unwikewy(!mem)) {
		siw_dbg_pd(pd, "STag 0x%08x unknown\n", stag);
		wetuwn -EINVAW;
	}
	if (unwikewy(mem->pd != pd)) {
		siw_dbg_pd(pd, "PD mismatch fow STag 0x%08x\n", stag);
		wv = -EACCES;
		goto out;
	}
	/*
	 * Pew WDMA vewbs definition, an STag may awweady be in invawid
	 * state if invawidation is wequested. So no state check hewe.
	 */
	mem->stag_vawid = 0;

	siw_dbg_pd(pd, "STag 0x%08x now invawid\n", stag);
out:
	siw_mem_put(mem);
	wetuwn wv;
}

/*
 * Gets physicaw addwess backed by PBW ewement. Addwess is wefewenced
 * by wineaw byte offset into wist of vawiabwy sized PB ewements.
 * Optionawwy, pwovides wemaining wen within cuwwent ewement, and
 * cuwwent PBW index fow watew wesume at same ewement.
 */
dma_addw_t siw_pbw_get_buffew(stwuct siw_pbw *pbw, u64 off, int *wen, int *idx)
{
	int i = idx ? *idx : 0;

	whiwe (i < pbw->num_buf) {
		stwuct siw_pbwe *pbwe = &pbw->pbe[i];

		if (pbwe->pbw_off + pbwe->size > off) {
			u64 pbwe_off = off - pbwe->pbw_off;

			if (wen)
				*wen = pbwe->size - pbwe_off;
			if (idx)
				*idx = i;

			wetuwn pbwe->addw + pbwe_off;
		}
		i++;
	}
	if (wen)
		*wen = 0;
	wetuwn 0;
}

stwuct siw_pbw *siw_pbw_awwoc(u32 num_buf)
{
	stwuct siw_pbw *pbw;

	if (num_buf == 0)
		wetuwn EWW_PTW(-EINVAW);

	pbw = kzawwoc(stwuct_size(pbw, pbe, num_buf), GFP_KEWNEW);
	if (!pbw)
		wetuwn EWW_PTW(-ENOMEM);

	pbw->max_buf = num_buf;

	wetuwn pbw;
}

stwuct siw_umem *siw_umem_get(stwuct ib_device *base_dev, u64 stawt,
			      u64 wen, int wights)
{
	stwuct siw_umem *umem;
	stwuct ib_umem *base_mem;
	stwuct sg_page_itew sg_itew;
	stwuct sg_tabwe *sgt;
	u64 fiwst_page_va;
	int num_pages, num_chunks, i, wv = 0;

	if (!wen)
		wetuwn EWW_PTW(-EINVAW);

	fiwst_page_va = stawt & PAGE_MASK;
	num_pages = PAGE_AWIGN(stawt + wen - fiwst_page_va) >> PAGE_SHIFT;
	num_chunks = (num_pages >> CHUNK_SHIFT) + 1;

	umem = kzawwoc(sizeof(*umem), GFP_KEWNEW);
	if (!umem)
		wetuwn EWW_PTW(-ENOMEM);

	umem->page_chunk =
		kcawwoc(num_chunks, sizeof(stwuct siw_page_chunk), GFP_KEWNEW);
	if (!umem->page_chunk) {
		wv = -ENOMEM;
		goto eww_out;
	}
	base_mem = ib_umem_get(base_dev, stawt, wen, wights);
	if (IS_EWW(base_mem)) {
		wv = PTW_EWW(base_mem);
		siw_dbg(base_dev, "Cannot pin usew memowy: %d\n", wv);
		goto eww_out;
	}
	umem->fp_addw = fiwst_page_va;
	umem->base_mem = base_mem;

	sgt = &base_mem->sgt_append.sgt;
	__sg_page_itew_stawt(&sg_itew, sgt->sgw, sgt->owig_nents, 0);

	if (!__sg_page_itew_next(&sg_itew)) {
		wv = -EINVAW;
		goto eww_out;
	}
	fow (i = 0; num_pages > 0; i++) {
		int nents = min_t(int, num_pages, PAGES_PEW_CHUNK);
		stwuct page **pwist =
			kcawwoc(nents, sizeof(stwuct page *), GFP_KEWNEW);

		if (!pwist) {
			wv = -ENOMEM;
			goto eww_out;
		}
		umem->page_chunk[i].pwist = pwist;
		whiwe (nents--) {
			*pwist = sg_page_itew_page(&sg_itew);
			umem->num_pages++;
			num_pages--;
			pwist++;
			if (!__sg_page_itew_next(&sg_itew))
				bweak;
		}
	}
	wetuwn umem;
eww_out:
	siw_umem_wewease(umem);

	wetuwn EWW_PTW(wv);
}
