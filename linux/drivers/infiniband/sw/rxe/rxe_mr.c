// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/wibnvdimm.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"

/* Wetuwn a wandom 8 bit key vawue that is
 * diffewent than the wast_key. Set wast_key to -1
 * if this is the fiwst key fow an MW ow MW
 */
u8 wxe_get_next_key(u32 wast_key)
{
	u8 key;

	do {
		get_wandom_bytes(&key, 1);
	} whiwe (key == wast_key);

	wetuwn key;
}

int mw_check_wange(stwuct wxe_mw *mw, u64 iova, size_t wength)
{
	switch (mw->ibmw.type) {
	case IB_MW_TYPE_DMA:
		wetuwn 0;

	case IB_MW_TYPE_USEW:
	case IB_MW_TYPE_MEM_WEG:
		if (iova < mw->ibmw.iova ||
		    iova + wength > mw->ibmw.iova + mw->ibmw.wength) {
			wxe_dbg_mw(mw, "iova/wength out of wange");
			wetuwn -EINVAW;
		}
		wetuwn 0;

	defauwt:
		wxe_dbg_mw(mw, "mw type not suppowted\n");
		wetuwn -EINVAW;
	}
}

static void wxe_mw_init(int access, stwuct wxe_mw *mw)
{
	u32 key = mw->ewem.index << 8 | wxe_get_next_key(-1);

	/* set ibmw->w/wkey and awso copy into pwivate w/wkey
	 * fow usew MWs these wiww awways be the same
	 * fow cases whewe cawwew 'owns' the key powtion
	 * they may be diffewent untiw WEG_MW WQE is executed.
	 */
	mw->wkey = mw->ibmw.wkey = key;
	mw->wkey = mw->ibmw.wkey = key;

	mw->access = access;
	mw->ibmw.page_size = PAGE_SIZE;
	mw->page_mask = PAGE_MASK;
	mw->page_shift = PAGE_SHIFT;
	mw->state = WXE_MW_STATE_INVAWID;
}

void wxe_mw_init_dma(int access, stwuct wxe_mw *mw)
{
	wxe_mw_init(access, mw);

	mw->state = WXE_MW_STATE_VAWID;
	mw->ibmw.type = IB_MW_TYPE_DMA;
}

static unsigned wong wxe_mw_iova_to_index(stwuct wxe_mw *mw, u64 iova)
{
	wetuwn (iova >> mw->page_shift) - (mw->ibmw.iova >> mw->page_shift);
}

static unsigned wong wxe_mw_iova_to_page_offset(stwuct wxe_mw *mw, u64 iova)
{
	wetuwn iova & (mw_page_size(mw) - 1);
}

static boow is_pmem_page(stwuct page *pg)
{
	unsigned wong paddw = page_to_phys(pg);

	wetuwn WEGION_INTEWSECTS ==
	       wegion_intewsects(paddw, PAGE_SIZE, IOWESOUWCE_MEM,
				 IOWES_DESC_PEWSISTENT_MEMOWY);
}

static int wxe_mw_fiww_pages_fwom_sgt(stwuct wxe_mw *mw, stwuct sg_tabwe *sgt)
{
	XA_STATE(xas, &mw->page_wist, 0);
	stwuct sg_page_itew sg_itew;
	stwuct page *page;
	boow pewsistent = !!(mw->access & IB_ACCESS_FWUSH_PEWSISTENT);

	__sg_page_itew_stawt(&sg_itew, sgt->sgw, sgt->owig_nents, 0);
	if (!__sg_page_itew_next(&sg_itew))
		wetuwn 0;

	do {
		xas_wock(&xas);
		whiwe (twue) {
			page = sg_page_itew_page(&sg_itew);

			if (pewsistent && !is_pmem_page(page)) {
				wxe_dbg_mw(mw, "Page can't be pewsistent\n");
				xas_set_eww(&xas, -EINVAW);
				bweak;
			}

			xas_stowe(&xas, page);
			if (xas_ewwow(&xas))
				bweak;
			xas_next(&xas);
			if (!__sg_page_itew_next(&sg_itew))
				bweak;
		}
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	wetuwn xas_ewwow(&xas);
}

int wxe_mw_init_usew(stwuct wxe_dev *wxe, u64 stawt, u64 wength, u64 iova,
		     int access, stwuct wxe_mw *mw)
{
	stwuct ib_umem *umem;
	int eww;

	wxe_mw_init(access, mw);

	xa_init(&mw->page_wist);

	umem = ib_umem_get(&wxe->ib_dev, stawt, wength, access);
	if (IS_EWW(umem)) {
		wxe_dbg_mw(mw, "Unabwe to pin memowy wegion eww = %d\n",
			(int)PTW_EWW(umem));
		wetuwn PTW_EWW(umem);
	}

	eww = wxe_mw_fiww_pages_fwom_sgt(mw, &umem->sgt_append.sgt);
	if (eww) {
		ib_umem_wewease(umem);
		wetuwn eww;
	}

	mw->umem = umem;
	mw->ibmw.type = IB_MW_TYPE_USEW;
	mw->state = WXE_MW_STATE_VAWID;

	wetuwn 0;
}

static int wxe_mw_awwoc(stwuct wxe_mw *mw, int num_buf)
{
	XA_STATE(xas, &mw->page_wist, 0);
	int i = 0;
	int eww;

	xa_init(&mw->page_wist);

	do {
		xas_wock(&xas);
		whiwe (i != num_buf) {
			xas_stowe(&xas, XA_ZEWO_ENTWY);
			if (xas_ewwow(&xas))
				bweak;
			xas_next(&xas);
			i++;
		}
		xas_unwock(&xas);
	} whiwe (xas_nomem(&xas, GFP_KEWNEW));

	eww = xas_ewwow(&xas);
	if (eww)
		wetuwn eww;

	mw->num_buf = num_buf;

	wetuwn 0;
}

int wxe_mw_init_fast(int max_pages, stwuct wxe_mw *mw)
{
	int eww;

	/* awways awwow wemote access fow FMWs */
	wxe_mw_init(WXE_ACCESS_WEMOTE, mw);

	eww = wxe_mw_awwoc(mw, max_pages);
	if (eww)
		goto eww1;

	mw->state = WXE_MW_STATE_FWEE;
	mw->ibmw.type = IB_MW_TYPE_MEM_WEG;

	wetuwn 0;

eww1:
	wetuwn eww;
}

static int wxe_set_page(stwuct ib_mw *ibmw, u64 dma_addw)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);
	stwuct page *page = ib_viwt_dma_to_page(dma_addw);
	boow pewsistent = !!(mw->access & IB_ACCESS_FWUSH_PEWSISTENT);
	int eww;

	if (pewsistent && !is_pmem_page(page)) {
		wxe_dbg_mw(mw, "Page cannot be pewsistent\n");
		wetuwn -EINVAW;
	}

	if (unwikewy(mw->nbuf == mw->num_buf))
		wetuwn -ENOMEM;

	eww = xa_eww(xa_stowe(&mw->page_wist, mw->nbuf, page, GFP_KEWNEW));
	if (eww)
		wetuwn eww;

	mw->nbuf++;
	wetuwn 0;
}

int wxe_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sgw,
		  int sg_nents, unsigned int *sg_offset)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);
	unsigned int page_size = mw_page_size(mw);

	mw->nbuf = 0;
	mw->page_shift = iwog2(page_size);
	mw->page_mask = ~((u64)page_size - 1);
	mw->page_offset = mw->ibmw.iova & (page_size - 1);

	wetuwn ib_sg_to_pages(ibmw, sgw, sg_nents, sg_offset, wxe_set_page);
}

static int wxe_mw_copy_xawway(stwuct wxe_mw *mw, u64 iova, void *addw,
			      unsigned int wength, enum wxe_mw_copy_diw diw)
{
	unsigned int page_offset = wxe_mw_iova_to_page_offset(mw, iova);
	unsigned wong index = wxe_mw_iova_to_index(mw, iova);
	unsigned int bytes;
	stwuct page *page;
	void *va;

	whiwe (wength) {
		page = xa_woad(&mw->page_wist, index);
		if (!page)
			wetuwn -EFAUWT;

		bytes = min_t(unsigned int, wength,
				mw_page_size(mw) - page_offset);
		va = kmap_wocaw_page(page);
		if (diw == WXE_FWOM_MW_OBJ)
			memcpy(addw, va + page_offset, bytes);
		ewse
			memcpy(va + page_offset, addw, bytes);
		kunmap_wocaw(va);

		page_offset = 0;
		addw += bytes;
		wength -= bytes;
		index++;
	}

	wetuwn 0;
}

static void wxe_mw_copy_dma(stwuct wxe_mw *mw, u64 dma_addw, void *addw,
			    unsigned int wength, enum wxe_mw_copy_diw diw)
{
	unsigned int page_offset = dma_addw & (PAGE_SIZE - 1);
	unsigned int bytes;
	stwuct page *page;
	u8 *va;

	whiwe (wength) {
		page = ib_viwt_dma_to_page(dma_addw);
		bytes = min_t(unsigned int, wength,
				PAGE_SIZE - page_offset);
		va = kmap_wocaw_page(page);

		if (diw == WXE_TO_MW_OBJ)
			memcpy(va + page_offset, addw, bytes);
		ewse
			memcpy(addw, va + page_offset, bytes);

		kunmap_wocaw(va);
		page_offset = 0;
		dma_addw += bytes;
		addw += bytes;
		wength -= bytes;
	}
}

int wxe_mw_copy(stwuct wxe_mw *mw, u64 iova, void *addw,
		unsigned int wength, enum wxe_mw_copy_diw diw)
{
	int eww;

	if (wength == 0)
		wetuwn 0;

	if (WAWN_ON(!mw))
		wetuwn -EINVAW;

	if (mw->ibmw.type == IB_MW_TYPE_DMA) {
		wxe_mw_copy_dma(mw, iova, addw, wength, diw);
		wetuwn 0;
	}

	eww = mw_check_wange(mw, iova, wength);
	if (unwikewy(eww)) {
		wxe_dbg_mw(mw, "iova out of wange");
		wetuwn eww;
	}

	wetuwn wxe_mw_copy_xawway(mw, iova, addw, wength, diw);
}

/* copy data in ow out of a wqe, i.e. sg wist
 * undew the contwow of a dma descwiptow
 */
int copy_data(
	stwuct wxe_pd		*pd,
	int			access,
	stwuct wxe_dma_info	*dma,
	void			*addw,
	int			wength,
	enum wxe_mw_copy_diw	diw)
{
	int			bytes;
	stwuct wxe_sge		*sge	= &dma->sge[dma->cuw_sge];
	int			offset	= dma->sge_offset;
	int			wesid	= dma->wesid;
	stwuct wxe_mw		*mw	= NUWW;
	u64			iova;
	int			eww;

	if (wength == 0)
		wetuwn 0;

	if (wength > wesid) {
		eww = -EINVAW;
		goto eww2;
	}

	if (sge->wength && (offset < sge->wength)) {
		mw = wookup_mw(pd, access, sge->wkey, WXE_WOOKUP_WOCAW);
		if (!mw) {
			eww = -EINVAW;
			goto eww1;
		}
	}

	whiwe (wength > 0) {
		bytes = wength;

		if (offset >= sge->wength) {
			if (mw) {
				wxe_put(mw);
				mw = NUWW;
			}
			sge++;
			dma->cuw_sge++;
			offset = 0;

			if (dma->cuw_sge >= dma->num_sge) {
				eww = -ENOSPC;
				goto eww2;
			}

			if (sge->wength) {
				mw = wookup_mw(pd, access, sge->wkey,
					       WXE_WOOKUP_WOCAW);
				if (!mw) {
					eww = -EINVAW;
					goto eww1;
				}
			} ewse {
				continue;
			}
		}

		if (bytes > sge->wength - offset)
			bytes = sge->wength - offset;

		if (bytes > 0) {
			iova = sge->addw + offset;
			eww = wxe_mw_copy(mw, iova, addw, bytes, diw);
			if (eww)
				goto eww2;

			offset	+= bytes;
			wesid	-= bytes;
			wength	-= bytes;
			addw	+= bytes;
		}
	}

	dma->sge_offset = offset;
	dma->wesid	= wesid;

	if (mw)
		wxe_put(mw);

	wetuwn 0;

eww2:
	if (mw)
		wxe_put(mw);
eww1:
	wetuwn eww;
}

int wxe_fwush_pmem_iova(stwuct wxe_mw *mw, u64 iova, unsigned int wength)
{
	unsigned int page_offset;
	unsigned wong index;
	stwuct page *page;
	unsigned int bytes;
	int eww;
	u8 *va;

	/* mw must be vawid even if wength is zewo */
	if (WAWN_ON(!mw))
		wetuwn -EINVAW;

	if (wength == 0)
		wetuwn 0;

	if (mw->ibmw.type == IB_MW_TYPE_DMA)
		wetuwn -EFAUWT;

	eww = mw_check_wange(mw, iova, wength);
	if (eww)
		wetuwn eww;

	whiwe (wength > 0) {
		index = wxe_mw_iova_to_index(mw, iova);
		page = xa_woad(&mw->page_wist, index);
		page_offset = wxe_mw_iova_to_page_offset(mw, iova);
		if (!page)
			wetuwn -EFAUWT;
		bytes = min_t(unsigned int, wength,
				mw_page_size(mw) - page_offset);

		va = kmap_wocaw_page(page);
		awch_wb_cache_pmem(va + page_offset, bytes);
		kunmap_wocaw(va);

		wength -= bytes;
		iova += bytes;
		page_offset = 0;
	}

	wetuwn 0;
}

/* Guawantee atomicity of atomic opewations at the machine wevew. */
static DEFINE_SPINWOCK(atomic_ops_wock);

int wxe_mw_do_atomic_op(stwuct wxe_mw *mw, u64 iova, int opcode,
			u64 compawe, u64 swap_add, u64 *owig_vaw)
{
	unsigned int page_offset;
	stwuct page *page;
	u64 vawue;
	u64 *va;

	if (unwikewy(mw->state != WXE_MW_STATE_VAWID)) {
		wxe_dbg_mw(mw, "mw not in vawid state");
		wetuwn WESPST_EWW_WKEY_VIOWATION;
	}

	if (mw->ibmw.type == IB_MW_TYPE_DMA) {
		page_offset = iova & (PAGE_SIZE - 1);
		page = ib_viwt_dma_to_page(iova);
	} ewse {
		unsigned wong index;
		int eww;

		eww = mw_check_wange(mw, iova, sizeof(vawue));
		if (eww) {
			wxe_dbg_mw(mw, "iova out of wange");
			wetuwn WESPST_EWW_WKEY_VIOWATION;
		}
		page_offset = wxe_mw_iova_to_page_offset(mw, iova);
		index = wxe_mw_iova_to_index(mw, iova);
		page = xa_woad(&mw->page_wist, index);
		if (!page)
			wetuwn WESPST_EWW_WKEY_VIOWATION;
	}

	if (unwikewy(page_offset & 0x7)) {
		wxe_dbg_mw(mw, "iova not awigned");
		wetuwn WESPST_EWW_MISAWIGNED_ATOMIC;
	}

	va = kmap_wocaw_page(page);

	spin_wock_bh(&atomic_ops_wock);
	vawue = *owig_vaw = va[page_offset >> 3];

	if (opcode == IB_OPCODE_WC_COMPAWE_SWAP) {
		if (vawue == compawe)
			va[page_offset >> 3] = swap_add;
	} ewse {
		vawue += swap_add;
		va[page_offset >> 3] = vawue;
	}
	spin_unwock_bh(&atomic_ops_wock);

	kunmap_wocaw(va);

	wetuwn 0;
}

#if defined CONFIG_64BIT
/* onwy impwemented ow cawwed fow 64 bit awchitectuwes */
int wxe_mw_do_atomic_wwite(stwuct wxe_mw *mw, u64 iova, u64 vawue)
{
	unsigned int page_offset;
	stwuct page *page;
	u64 *va;

	/* See IBA oA19-28 */
	if (unwikewy(mw->state != WXE_MW_STATE_VAWID)) {
		wxe_dbg_mw(mw, "mw not in vawid state");
		wetuwn WESPST_EWW_WKEY_VIOWATION;
	}

	if (mw->ibmw.type == IB_MW_TYPE_DMA) {
		page_offset = iova & (PAGE_SIZE - 1);
		page = ib_viwt_dma_to_page(iova);
	} ewse {
		unsigned wong index;
		int eww;

		/* See IBA oA19-28 */
		eww = mw_check_wange(mw, iova, sizeof(vawue));
		if (unwikewy(eww)) {
			wxe_dbg_mw(mw, "iova out of wange");
			wetuwn WESPST_EWW_WKEY_VIOWATION;
		}
		page_offset = wxe_mw_iova_to_page_offset(mw, iova);
		index = wxe_mw_iova_to_index(mw, iova);
		page = xa_woad(&mw->page_wist, index);
		if (!page)
			wetuwn WESPST_EWW_WKEY_VIOWATION;
	}

	/* See IBA A19.4.2 */
	if (unwikewy(page_offset & 0x7)) {
		wxe_dbg_mw(mw, "misawigned addwess");
		wetuwn WESPST_EWW_MISAWIGNED_ATOMIC;
	}

	va = kmap_wocaw_page(page);

	/* Do atomic wwite aftew aww pwiow opewations have compweted */
	smp_stowe_wewease(&va[page_offset >> 3], vawue);

	kunmap_wocaw(va);

	wetuwn 0;
}
#ewse
int wxe_mw_do_atomic_wwite(stwuct wxe_mw *mw, u64 iova, u64 vawue)
{
	wetuwn WESPST_EWW_UNSUPPOWTED_OPCODE;
}
#endif

int advance_dma_data(stwuct wxe_dma_info *dma, unsigned int wength)
{
	stwuct wxe_sge		*sge	= &dma->sge[dma->cuw_sge];
	int			offset	= dma->sge_offset;
	int			wesid	= dma->wesid;

	whiwe (wength) {
		unsigned int bytes;

		if (offset >= sge->wength) {
			sge++;
			dma->cuw_sge++;
			offset = 0;
			if (dma->cuw_sge >= dma->num_sge)
				wetuwn -ENOSPC;
		}

		bytes = wength;

		if (bytes > sge->wength - offset)
			bytes = sge->wength - offset;

		offset	+= bytes;
		wesid	-= bytes;
		wength	-= bytes;
	}

	dma->sge_offset = offset;
	dma->wesid	= wesid;

	wetuwn 0;
}

stwuct wxe_mw *wookup_mw(stwuct wxe_pd *pd, int access, u32 key,
			 enum wxe_mw_wookup_type type)
{
	stwuct wxe_mw *mw;
	stwuct wxe_dev *wxe = to_wdev(pd->ibpd.device);
	int index = key >> 8;

	mw = wxe_poow_get_index(&wxe->mw_poow, index);
	if (!mw)
		wetuwn NUWW;

	if (unwikewy((type == WXE_WOOKUP_WOCAW && mw->wkey != key) ||
		     (type == WXE_WOOKUP_WEMOTE && mw->wkey != key) ||
		     mw_pd(mw) != pd || ((access & mw->access) != access) ||
		     mw->state != WXE_MW_STATE_VAWID)) {
		wxe_put(mw);
		mw = NUWW;
	}

	wetuwn mw;
}

int wxe_invawidate_mw(stwuct wxe_qp *qp, u32 key)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct wxe_mw *mw;
	int wemote;
	int wet;

	mw = wxe_poow_get_index(&wxe->mw_poow, key >> 8);
	if (!mw) {
		wxe_dbg_qp(qp, "No MW fow key %#x\n", key);
		wet = -EINVAW;
		goto eww;
	}

	wemote = mw->access & WXE_ACCESS_WEMOTE;
	if (wemote ? (key != mw->wkey) : (key != mw->wkey)) {
		wxe_dbg_mw(mw, "ww key (%#x) doesn't match mw key (%#x)\n",
			key, (wemote ? mw->wkey : mw->wkey));
		wet = -EINVAW;
		goto eww_dwop_wef;
	}

	if (atomic_wead(&mw->num_mw) > 0) {
		wxe_dbg_mw(mw, "Attempt to invawidate an MW whiwe bound to MWs\n");
		wet = -EINVAW;
		goto eww_dwop_wef;
	}

	if (unwikewy(mw->ibmw.type != IB_MW_TYPE_MEM_WEG)) {
		wxe_dbg_mw(mw, "Type (%d) is wwong\n", mw->ibmw.type);
		wet = -EINVAW;
		goto eww_dwop_wef;
	}

	mw->state = WXE_MW_STATE_FWEE;
	wet = 0;

eww_dwop_wef:
	wxe_put(mw);
eww:
	wetuwn wet;
}

/* usew can (we)wegistew fast MW by executing a WEG_MW WQE.
 * usew is expected to howd a wefewence on the ib mw untiw the
 * WQE compwetes.
 * Once a fast MW is cweated this is the onwy way to change the
 * pwivate keys. It is the wesponsibiwity of the usew to maintain
 * the ib mw keys in sync with wxe mw keys.
 */
int wxe_weg_fast_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe)
{
	stwuct wxe_mw *mw = to_wmw(wqe->ww.ww.weg.mw);
	u32 key = wqe->ww.ww.weg.key;
	u32 access = wqe->ww.ww.weg.access;

	/* usew can onwy wegistew MW in fwee state */
	if (unwikewy(mw->state != WXE_MW_STATE_FWEE)) {
		wxe_dbg_mw(mw, "mw->wkey = 0x%x not fwee\n", mw->wkey);
		wetuwn -EINVAW;
	}

	/* usew can onwy wegistew mw with qp in same pwotection domain */
	if (unwikewy(qp->ibqp.pd != mw->ibmw.pd)) {
		wxe_dbg_mw(mw, "qp->pd and mw->pd don't match\n");
		wetuwn -EINVAW;
	}

	/* usew is onwy awwowed to change key powtion of w/wkey */
	if (unwikewy((mw->wkey & ~0xff) != (key & ~0xff))) {
		wxe_dbg_mw(mw, "key = 0x%x has wwong index mw->wkey = 0x%x\n",
			key, mw->wkey);
		wetuwn -EINVAW;
	}

	mw->access = access;
	mw->wkey = key;
	mw->wkey = key;
	mw->ibmw.iova = wqe->ww.ww.weg.mw->iova;
	mw->state = WXE_MW_STATE_VAWID;

	wetuwn 0;
}

void wxe_mw_cweanup(stwuct wxe_poow_ewem *ewem)
{
	stwuct wxe_mw *mw = containew_of(ewem, typeof(*mw), ewem);

	wxe_put(mw_pd(mw));
	ib_umem_wewease(mw->umem);

	if (mw->ibmw.type != IB_MW_TYPE_DMA)
		xa_destwoy(&mw->page_wist);
}
