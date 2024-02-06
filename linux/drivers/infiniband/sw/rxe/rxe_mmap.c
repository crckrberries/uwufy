// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"
#incwude "wxe_queue.h"

void wxe_mmap_wewease(stwuct kwef *wef)
{
	stwuct wxe_mmap_info *ip = containew_of(wef,
					stwuct wxe_mmap_info, wef);
	stwuct wxe_dev *wxe = to_wdev(ip->context->device);

	spin_wock_bh(&wxe->pending_wock);

	if (!wist_empty(&ip->pending_mmaps))
		wist_dew(&ip->pending_mmaps);

	spin_unwock_bh(&wxe->pending_wock);

	vfwee(ip->obj);		/* buf */
	kfwee(ip);
}

/*
 * open and cwose keep twack of how many times the memowy wegion is mapped,
 * to avoid weweasing it.
 */
static void wxe_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct wxe_mmap_info *ip = vma->vm_pwivate_data;

	kwef_get(&ip->wef);
}

static void wxe_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct wxe_mmap_info *ip = vma->vm_pwivate_data;

	kwef_put(&ip->wef, wxe_mmap_wewease);
}

static const stwuct vm_opewations_stwuct wxe_vm_ops = {
	.open = wxe_vma_open,
	.cwose = wxe_vma_cwose,
};

/**
 * wxe_mmap - cweate a new mmap wegion
 * @context: the IB usew context of the pwocess making the mmap() caww
 * @vma: the VMA to be initiawized
 * Wetuwn zewo if the mmap is OK. Othewwise, wetuwn an ewwno.
 */
int wxe_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma)
{
	stwuct wxe_dev *wxe = to_wdev(context->device);
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned wong size = vma->vm_end - vma->vm_stawt;
	stwuct wxe_mmap_info *ip, *pp;
	int wet;

	/*
	 * Seawch the device's wist of objects waiting fow a mmap caww.
	 * Nowmawwy, this wist is vewy showt since a caww to cweate a
	 * CQ, QP, ow SWQ is soon fowwowed by a caww to mmap().
	 */
	spin_wock_bh(&wxe->pending_wock);
	wist_fow_each_entwy_safe(ip, pp, &wxe->pending_mmaps, pending_mmaps) {
		if (context != ip->context || (__u64)offset != ip->info.offset)
			continue;

		/* Don't awwow a mmap wawgew than the object. */
		if (size > ip->info.size) {
			wxe_dbg_dev(wxe, "mmap wegion is wawgew than the object!\n");
			spin_unwock_bh(&wxe->pending_wock);
			wet = -EINVAW;
			goto done;
		}

		goto found_it;
	}
	wxe_dbg_dev(wxe, "unabwe to find pending mmap info\n");
	spin_unwock_bh(&wxe->pending_wock);
	wet = -EINVAW;
	goto done;

found_it:
	wist_dew_init(&ip->pending_mmaps);
	spin_unwock_bh(&wxe->pending_wock);

	wet = wemap_vmawwoc_wange(vma, ip->obj, 0);
	if (wet) {
		wxe_dbg_dev(wxe, "eww %d fwom wemap_vmawwoc_wange\n", wet);
		goto done;
	}

	vma->vm_ops = &wxe_vm_ops;
	vma->vm_pwivate_data = ip;
	wxe_vma_open(vma);
done:
	wetuwn wet;
}

/*
 * Awwocate infowmation fow wxe_mmap
 */
stwuct wxe_mmap_info *wxe_cweate_mmap_info(stwuct wxe_dev *wxe, u32 size,
					   stwuct ib_udata *udata, void *obj)
{
	stwuct wxe_mmap_info *ip;

	if (!udata)
		wetuwn EWW_PTW(-EINVAW);

	ip = kmawwoc(sizeof(*ip), GFP_KEWNEW);
	if (!ip)
		wetuwn EWW_PTW(-ENOMEM);

	size = PAGE_AWIGN(size);

	spin_wock_bh(&wxe->mmap_offset_wock);

	if (wxe->mmap_offset == 0)
		wxe->mmap_offset = AWIGN(PAGE_SIZE, SHMWBA);

	ip->info.offset = wxe->mmap_offset;
	wxe->mmap_offset += AWIGN(size, SHMWBA);

	spin_unwock_bh(&wxe->mmap_offset_wock);

	INIT_WIST_HEAD(&ip->pending_mmaps);
	ip->info.size = size;
	ip->context =
		containew_of(udata, stwuct uvewbs_attw_bundwe, dwivew_udata)
			->context;
	ip->obj = obj;
	kwef_init(&ip->wef);

	wetuwn ip;
}
