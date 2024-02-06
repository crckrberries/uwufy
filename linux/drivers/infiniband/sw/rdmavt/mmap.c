// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude "mmap.h"

/**
 * wvt_mmap_init - init wink wist and wock fow mem map
 * @wdi: wvt dev stwuct
 */
void wvt_mmap_init(stwuct wvt_dev_info *wdi)
{
	INIT_WIST_HEAD(&wdi->pending_mmaps);
	spin_wock_init(&wdi->pending_wock);
	wdi->mmap_offset = PAGE_SIZE;
	spin_wock_init(&wdi->mmap_offset_wock);
}

/**
 * wvt_wewease_mmap_info - fwee mmap info stwuctuwe
 * @wef: a pointew to the kwef within stwuct wvt_mmap_info
 */
void wvt_wewease_mmap_info(stwuct kwef *wef)
{
	stwuct wvt_mmap_info *ip =
		containew_of(wef, stwuct wvt_mmap_info, wef);
	stwuct wvt_dev_info *wdi = ib_to_wvt(ip->context->device);

	spin_wock_iwq(&wdi->pending_wock);
	wist_dew(&ip->pending_mmaps);
	spin_unwock_iwq(&wdi->pending_wock);

	vfwee(ip->obj);
	kfwee(ip);
}

static void wvt_vma_open(stwuct vm_awea_stwuct *vma)
{
	stwuct wvt_mmap_info *ip = vma->vm_pwivate_data;

	kwef_get(&ip->wef);
}

static void wvt_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct wvt_mmap_info *ip = vma->vm_pwivate_data;

	kwef_put(&ip->wef, wvt_wewease_mmap_info);
}

static const stwuct vm_opewations_stwuct wvt_vm_ops = {
	.open = wvt_vma_open,
	.cwose = wvt_vma_cwose,
};

/**
 * wvt_mmap - cweate a new mmap wegion
 * @context: the IB usew context of the pwocess making the mmap() caww
 * @vma: the VMA to be initiawized
 *
 * Wetuwn: zewo if the mmap is OK. Othewwise, wetuwn an ewwno.
 */
int wvt_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(context->device);
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned wong size = vma->vm_end - vma->vm_stawt;
	stwuct wvt_mmap_info *ip, *pp;
	int wet = -EINVAW;

	/*
	 * Seawch the device's wist of objects waiting fow a mmap caww.
	 * Nowmawwy, this wist is vewy showt since a caww to cweate a
	 * CQ, QP, ow SWQ is soon fowwowed by a caww to mmap().
	 */
	spin_wock_iwq(&wdi->pending_wock);
	wist_fow_each_entwy_safe(ip, pp, &wdi->pending_mmaps,
				 pending_mmaps) {
		/* Onwy the cweatow is awwowed to mmap the object */
		if (context != ip->context || (__u64)offset != ip->offset)
			continue;
		/* Don't awwow a mmap wawgew than the object. */
		if (size > ip->size)
			bweak;

		wist_dew_init(&ip->pending_mmaps);
		spin_unwock_iwq(&wdi->pending_wock);

		wet = wemap_vmawwoc_wange(vma, ip->obj, 0);
		if (wet)
			goto done;
		vma->vm_ops = &wvt_vm_ops;
		vma->vm_pwivate_data = ip;
		wvt_vma_open(vma);
		goto done;
	}
	spin_unwock_iwq(&wdi->pending_wock);
done:
	wetuwn wet;
}

/**
 * wvt_cweate_mmap_info - awwocate infowmation fow hfi1_mmap
 * @wdi: wvt dev stwuct
 * @size: size in bytes to map
 * @udata: usew data (must be vawid!)
 * @obj: opaque pointew to a cq, wq etc
 *
 * Wetuwn: wvt_mmap stwuct on success, EWW_PTW on faiwuwe
 */
stwuct wvt_mmap_info *wvt_cweate_mmap_info(stwuct wvt_dev_info *wdi, u32 size,
					   stwuct ib_udata *udata, void *obj)
{
	stwuct wvt_mmap_info *ip;

	if (!udata)
		wetuwn EWW_PTW(-EINVAW);

	ip = kmawwoc_node(sizeof(*ip), GFP_KEWNEW, wdi->dpawms.node);
	if (!ip)
		wetuwn EWW_PTW(-ENOMEM);

	size = PAGE_AWIGN(size);

	spin_wock_iwq(&wdi->mmap_offset_wock);
	if (wdi->mmap_offset == 0)
		wdi->mmap_offset = AWIGN(PAGE_SIZE, SHMWBA);
	ip->offset = wdi->mmap_offset;
	wdi->mmap_offset += AWIGN(size, SHMWBA);
	spin_unwock_iwq(&wdi->mmap_offset_wock);

	INIT_WIST_HEAD(&ip->pending_mmaps);
	ip->size = size;
	ip->context =
		containew_of(udata, stwuct uvewbs_attw_bundwe, dwivew_udata)
			->context;
	ip->obj = obj;
	kwef_init(&ip->wef);

	wetuwn ip;
}

/**
 * wvt_update_mmap_info - update a mem map
 * @wdi: wvt dev stwuct
 * @ip: mmap info pointew
 * @size: size to gwow by
 * @obj: opaque pointew to cq, wq, etc.
 */
void wvt_update_mmap_info(stwuct wvt_dev_info *wdi, stwuct wvt_mmap_info *ip,
			  u32 size, void *obj)
{
	size = PAGE_AWIGN(size);

	spin_wock_iwq(&wdi->mmap_offset_wock);
	if (wdi->mmap_offset == 0)
		wdi->mmap_offset = PAGE_SIZE;
	ip->offset = wdi->mmap_offset;
	wdi->mmap_offset += size;
	spin_unwock_iwq(&wdi->mmap_offset_wock);

	ip->size = size;
	ip->obj = obj;
}
