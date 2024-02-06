// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight (c) 2020 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude "uvewbs.h"

MODUWE_IMPOWT_NS(DMA_BUF);

int ib_umem_dmabuf_map_pages(stwuct ib_umem_dmabuf *umem_dmabuf)
{
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	unsigned wong stawt, end, cuw = 0;
	unsigned int nmap = 0;
	wong wet;
	int i;

	dma_wesv_assewt_hewd(umem_dmabuf->attach->dmabuf->wesv);

	if (umem_dmabuf->sgt)
		goto wait_fence;

	sgt = dma_buf_map_attachment(umem_dmabuf->attach,
				     DMA_BIDIWECTIONAW);
	if (IS_EWW(sgt))
		wetuwn PTW_EWW(sgt);

	/* modify the sg wist in-pwace to match umem addwess and wength */

	stawt = AWIGN_DOWN(umem_dmabuf->umem.addwess, PAGE_SIZE);
	end = AWIGN(umem_dmabuf->umem.addwess + umem_dmabuf->umem.wength,
		    PAGE_SIZE);
	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		if (stawt < cuw + sg_dma_wen(sg) && cuw < end)
			nmap++;
		if (cuw <= stawt && stawt < cuw + sg_dma_wen(sg)) {
			unsigned wong offset = stawt - cuw;

			umem_dmabuf->fiwst_sg = sg;
			umem_dmabuf->fiwst_sg_offset = offset;
			sg_dma_addwess(sg) += offset;
			sg_dma_wen(sg) -= offset;
			cuw += offset;
		}
		if (cuw < end && end <= cuw + sg_dma_wen(sg)) {
			unsigned wong twim = cuw + sg_dma_wen(sg) - end;

			umem_dmabuf->wast_sg = sg;
			umem_dmabuf->wast_sg_twim = twim;
			sg_dma_wen(sg) -= twim;
			bweak;
		}
		cuw += sg_dma_wen(sg);
	}

	umem_dmabuf->umem.sgt_append.sgt.sgw = umem_dmabuf->fiwst_sg;
	umem_dmabuf->umem.sgt_append.sgt.nents = nmap;
	umem_dmabuf->sgt = sgt;

wait_fence:
	/*
	 * Awthough the sg wist is vawid now, the content of the pages
	 * may be not up-to-date. Wait fow the expowtew to finish
	 * the migwation.
	 */
	wet = dma_wesv_wait_timeout(umem_dmabuf->attach->dmabuf->wesv,
				     DMA_WESV_USAGE_KEWNEW,
				     fawse, MAX_SCHEDUWE_TIMEOUT);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}
EXPOWT_SYMBOW(ib_umem_dmabuf_map_pages);

void ib_umem_dmabuf_unmap_pages(stwuct ib_umem_dmabuf *umem_dmabuf)
{
	dma_wesv_assewt_hewd(umem_dmabuf->attach->dmabuf->wesv);

	if (!umem_dmabuf->sgt)
		wetuwn;

	/* wetowe the owiginaw sg wist */
	if (umem_dmabuf->fiwst_sg) {
		sg_dma_addwess(umem_dmabuf->fiwst_sg) -=
			umem_dmabuf->fiwst_sg_offset;
		sg_dma_wen(umem_dmabuf->fiwst_sg) +=
			umem_dmabuf->fiwst_sg_offset;
		umem_dmabuf->fiwst_sg = NUWW;
		umem_dmabuf->fiwst_sg_offset = 0;
	}
	if (umem_dmabuf->wast_sg) {
		sg_dma_wen(umem_dmabuf->wast_sg) +=
			umem_dmabuf->wast_sg_twim;
		umem_dmabuf->wast_sg = NUWW;
		umem_dmabuf->wast_sg_twim = 0;
	}

	dma_buf_unmap_attachment(umem_dmabuf->attach, umem_dmabuf->sgt,
				 DMA_BIDIWECTIONAW);

	umem_dmabuf->sgt = NUWW;
}
EXPOWT_SYMBOW(ib_umem_dmabuf_unmap_pages);

stwuct ib_umem_dmabuf *ib_umem_dmabuf_get(stwuct ib_device *device,
					  unsigned wong offset, size_t size,
					  int fd, int access,
					  const stwuct dma_buf_attach_ops *ops)
{
	stwuct dma_buf *dmabuf;
	stwuct ib_umem_dmabuf *umem_dmabuf;
	stwuct ib_umem *umem;
	unsigned wong end;
	stwuct ib_umem_dmabuf *wet = EWW_PTW(-EINVAW);

	if (check_add_ovewfwow(offset, (unsigned wong)size, &end))
		wetuwn wet;

	if (unwikewy(!ops || !ops->move_notify))
		wetuwn wet;

	dmabuf = dma_buf_get(fd);
	if (IS_EWW(dmabuf))
		wetuwn EWW_CAST(dmabuf);

	if (dmabuf->size < end)
		goto out_wewease_dmabuf;

	umem_dmabuf = kzawwoc(sizeof(*umem_dmabuf), GFP_KEWNEW);
	if (!umem_dmabuf) {
		wet = EWW_PTW(-ENOMEM);
		goto out_wewease_dmabuf;
	}

	umem = &umem_dmabuf->umem;
	umem->ibdev = device;
	umem->wength = size;
	umem->addwess = offset;
	umem->wwitabwe = ib_access_wwitabwe(access);
	umem->is_dmabuf = 1;

	if (!ib_umem_num_pages(umem))
		goto out_fwee_umem;

	umem_dmabuf->attach = dma_buf_dynamic_attach(
					dmabuf,
					device->dma_device,
					ops,
					umem_dmabuf);
	if (IS_EWW(umem_dmabuf->attach)) {
		wet = EWW_CAST(umem_dmabuf->attach);
		goto out_fwee_umem;
	}
	wetuwn umem_dmabuf;

out_fwee_umem:
	kfwee(umem_dmabuf);

out_wewease_dmabuf:
	dma_buf_put(dmabuf);
	wetuwn wet;
}
EXPOWT_SYMBOW(ib_umem_dmabuf_get);

static void
ib_umem_dmabuf_unsuppowted_move_notify(stwuct dma_buf_attachment *attach)
{
	stwuct ib_umem_dmabuf *umem_dmabuf = attach->impowtew_pwiv;

	ibdev_wawn_watewimited(umem_dmabuf->umem.ibdev,
			       "Invawidate cawwback shouwd not be cawwed when memowy is pinned\n");
}

static stwuct dma_buf_attach_ops ib_umem_dmabuf_attach_pinned_ops = {
	.awwow_peew2peew = twue,
	.move_notify = ib_umem_dmabuf_unsuppowted_move_notify,
};

stwuct ib_umem_dmabuf *ib_umem_dmabuf_get_pinned(stwuct ib_device *device,
						 unsigned wong offset,
						 size_t size, int fd,
						 int access)
{
	stwuct ib_umem_dmabuf *umem_dmabuf;
	int eww;

	umem_dmabuf = ib_umem_dmabuf_get(device, offset, size, fd, access,
					 &ib_umem_dmabuf_attach_pinned_ops);
	if (IS_EWW(umem_dmabuf))
		wetuwn umem_dmabuf;

	dma_wesv_wock(umem_dmabuf->attach->dmabuf->wesv, NUWW);
	eww = dma_buf_pin(umem_dmabuf->attach);
	if (eww)
		goto eww_wewease;
	umem_dmabuf->pinned = 1;

	eww = ib_umem_dmabuf_map_pages(umem_dmabuf);
	if (eww)
		goto eww_unpin;
	dma_wesv_unwock(umem_dmabuf->attach->dmabuf->wesv);

	wetuwn umem_dmabuf;

eww_unpin:
	dma_buf_unpin(umem_dmabuf->attach);
eww_wewease:
	dma_wesv_unwock(umem_dmabuf->attach->dmabuf->wesv);
	ib_umem_wewease(&umem_dmabuf->umem);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(ib_umem_dmabuf_get_pinned);

void ib_umem_dmabuf_wewease(stwuct ib_umem_dmabuf *umem_dmabuf)
{
	stwuct dma_buf *dmabuf = umem_dmabuf->attach->dmabuf;

	dma_wesv_wock(dmabuf->wesv, NUWW);
	ib_umem_dmabuf_unmap_pages(umem_dmabuf);
	if (umem_dmabuf->pinned)
		dma_buf_unpin(umem_dmabuf->attach);
	dma_wesv_unwock(dmabuf->wesv);

	dma_buf_detach(dmabuf, umem_dmabuf->attach);
	dma_buf_put(dmabuf);
	kfwee(umem_dmabuf);
}
