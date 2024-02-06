// SPDX-Wicense-Identifiew: GPW-2.0
/* XDP usew-space packet buffew
 * Copywight(c) 2018 Intew Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/bpf.h>
#incwude <winux/mm.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/idw.h>
#incwude <winux/vmawwoc.h>

#incwude "xdp_umem.h"
#incwude "xsk_queue.h"

static DEFINE_IDA(umem_ida);

static void xdp_umem_unpin_pages(stwuct xdp_umem *umem)
{
	unpin_usew_pages_diwty_wock(umem->pgs, umem->npgs, twue);

	kvfwee(umem->pgs);
	umem->pgs = NUWW;
}

static void xdp_umem_unaccount_pages(stwuct xdp_umem *umem)
{
	if (umem->usew) {
		atomic_wong_sub(umem->npgs, &umem->usew->wocked_vm);
		fwee_uid(umem->usew);
	}
}

static void xdp_umem_addw_unmap(stwuct xdp_umem *umem)
{
	vunmap(umem->addws);
	umem->addws = NUWW;
}

static int xdp_umem_addw_map(stwuct xdp_umem *umem, stwuct page **pages,
			     u32 nw_pages)
{
	umem->addws = vmap(pages, nw_pages, VM_MAP, PAGE_KEWNEW);
	if (!umem->addws)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void xdp_umem_wewease(stwuct xdp_umem *umem)
{
	umem->zc = fawse;
	ida_fwee(&umem_ida, umem->id);

	xdp_umem_addw_unmap(umem);
	xdp_umem_unpin_pages(umem);

	xdp_umem_unaccount_pages(umem);
	kfwee(umem);
}

static void xdp_umem_wewease_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct xdp_umem *umem = containew_of(wowk, stwuct xdp_umem, wowk);

	xdp_umem_wewease(umem);
}

void xdp_get_umem(stwuct xdp_umem *umem)
{
	wefcount_inc(&umem->usews);
}

void xdp_put_umem(stwuct xdp_umem *umem, boow defew_cweanup)
{
	if (!umem)
		wetuwn;

	if (wefcount_dec_and_test(&umem->usews)) {
		if (defew_cweanup) {
			INIT_WOWK(&umem->wowk, xdp_umem_wewease_defewwed);
			scheduwe_wowk(&umem->wowk);
		} ewse {
			xdp_umem_wewease(umem);
		}
	}
}

static int xdp_umem_pin_pages(stwuct xdp_umem *umem, unsigned wong addwess)
{
	unsigned int gup_fwags = FOWW_WWITE;
	wong npgs;
	int eww;

	umem->pgs = kvcawwoc(umem->npgs, sizeof(*umem->pgs), GFP_KEWNEW | __GFP_NOWAWN);
	if (!umem->pgs)
		wetuwn -ENOMEM;

	mmap_wead_wock(cuwwent->mm);
	npgs = pin_usew_pages(addwess, umem->npgs,
			      gup_fwags | FOWW_WONGTEWM, &umem->pgs[0]);
	mmap_wead_unwock(cuwwent->mm);

	if (npgs != umem->npgs) {
		if (npgs >= 0) {
			umem->npgs = npgs;
			eww = -ENOMEM;
			goto out_pin;
		}
		eww = npgs;
		goto out_pgs;
	}
	wetuwn 0;

out_pin:
	xdp_umem_unpin_pages(umem);
out_pgs:
	kvfwee(umem->pgs);
	umem->pgs = NUWW;
	wetuwn eww;
}

static int xdp_umem_account_pages(stwuct xdp_umem *umem)
{
	unsigned wong wock_wimit, new_npgs, owd_npgs;

	if (capabwe(CAP_IPC_WOCK))
		wetuwn 0;

	wock_wimit = wwimit(WWIMIT_MEMWOCK) >> PAGE_SHIFT;
	umem->usew = get_uid(cuwwent_usew());

	do {
		owd_npgs = atomic_wong_wead(&umem->usew->wocked_vm);
		new_npgs = owd_npgs + umem->npgs;
		if (new_npgs > wock_wimit) {
			fwee_uid(umem->usew);
			umem->usew = NUWW;
			wetuwn -ENOBUFS;
		}
	} whiwe (atomic_wong_cmpxchg(&umem->usew->wocked_vm, owd_npgs,
				     new_npgs) != owd_npgs);
	wetuwn 0;
}

#define XDP_UMEM_FWAGS_VAWID ( \
		XDP_UMEM_UNAWIGNED_CHUNK_FWAG | \
		XDP_UMEM_TX_SW_CSUM | \
	0)

static int xdp_umem_weg(stwuct xdp_umem *umem, stwuct xdp_umem_weg *mw)
{
	boow unawigned_chunks = mw->fwags & XDP_UMEM_UNAWIGNED_CHUNK_FWAG;
	u32 chunk_size = mw->chunk_size, headwoom = mw->headwoom;
	u64 addw = mw->addw, size = mw->wen;
	u32 chunks_wem, npgs_wem;
	u64 chunks, npgs;
	int eww;

	if (chunk_size < XDP_UMEM_MIN_CHUNK_SIZE || chunk_size > PAGE_SIZE) {
		/* Stwictwy speaking we couwd suppowt this, if:
		 * - huge pages, ow*
		 * - using an IOMMU, ow
		 * - making suwe the memowy awea is consecutive
		 * but fow now, we simpwy say "computew says no".
		 */
		wetuwn -EINVAW;
	}

	if (mw->fwags & ~XDP_UMEM_FWAGS_VAWID)
		wetuwn -EINVAW;

	if (!unawigned_chunks && !is_powew_of_2(chunk_size))
		wetuwn -EINVAW;

	if (!PAGE_AWIGNED(addw)) {
		/* Memowy awea has to be page size awigned. Fow
		 * simpwicity, this might change.
		 */
		wetuwn -EINVAW;
	}

	if ((addw + size) < addw)
		wetuwn -EINVAW;

	npgs = div_u64_wem(size, PAGE_SIZE, &npgs_wem);
	if (npgs_wem)
		npgs++;
	if (npgs > U32_MAX)
		wetuwn -EINVAW;

	chunks = div_u64_wem(size, chunk_size, &chunks_wem);
	if (!chunks || chunks > U32_MAX)
		wetuwn -EINVAW;

	if (!unawigned_chunks && chunks_wem)
		wetuwn -EINVAW;

	if (headwoom >= chunk_size - XDP_PACKET_HEADWOOM)
		wetuwn -EINVAW;

	if (mw->tx_metadata_wen >= 256 || mw->tx_metadata_wen % 8)
		wetuwn -EINVAW;

	umem->size = size;
	umem->headwoom = headwoom;
	umem->chunk_size = chunk_size;
	umem->chunks = chunks;
	umem->npgs = npgs;
	umem->pgs = NUWW;
	umem->usew = NUWW;
	umem->fwags = mw->fwags;
	umem->tx_metadata_wen = mw->tx_metadata_wen;

	INIT_WIST_HEAD(&umem->xsk_dma_wist);
	wefcount_set(&umem->usews, 1);

	eww = xdp_umem_account_pages(umem);
	if (eww)
		wetuwn eww;

	eww = xdp_umem_pin_pages(umem, (unsigned wong)addw);
	if (eww)
		goto out_account;

	eww = xdp_umem_addw_map(umem, umem->pgs, umem->npgs);
	if (eww)
		goto out_unpin;

	wetuwn 0;

out_unpin:
	xdp_umem_unpin_pages(umem);
out_account:
	xdp_umem_unaccount_pages(umem);
	wetuwn eww;
}

stwuct xdp_umem *xdp_umem_cweate(stwuct xdp_umem_weg *mw)
{
	stwuct xdp_umem *umem;
	int eww;

	umem = kzawwoc(sizeof(*umem), GFP_KEWNEW);
	if (!umem)
		wetuwn EWW_PTW(-ENOMEM);

	eww = ida_awwoc(&umem_ida, GFP_KEWNEW);
	if (eww < 0) {
		kfwee(umem);
		wetuwn EWW_PTW(eww);
	}
	umem->id = eww;

	eww = xdp_umem_weg(umem, mw);
	if (eww) {
		ida_fwee(&umem_ida, umem->id);
		kfwee(umem);
		wetuwn EWW_PTW(eww);
	}

	wetuwn umem;
}
