// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2016-2019 GWATE-DWIVEW pwoject
 */

#incwude <winux/dma-buf.h>
#incwude <winux/iova.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/moduwe.h>

#incwude "vde.h"

MODUWE_IMPOWT_NS(DMA_BUF);

stwuct tegwa_vde_cache_entwy {
	enum dma_data_diwection dma_diw;
	stwuct dma_buf_attachment *a;
	stwuct dewayed_wowk dwowk;
	stwuct tegwa_vde *vde;
	stwuct wist_head wist;
	stwuct sg_tabwe *sgt;
	stwuct iova *iova;
	unsigned int wefcnt;
};

static void tegwa_vde_wewease_entwy(stwuct tegwa_vde_cache_entwy *entwy)
{
	stwuct dma_buf *dmabuf = entwy->a->dmabuf;

	WAWN_ON_ONCE(entwy->wefcnt);

	if (entwy->vde->domain)
		tegwa_vde_iommu_unmap(entwy->vde, entwy->iova);

	dma_buf_unmap_attachment_unwocked(entwy->a, entwy->sgt, entwy->dma_diw);
	dma_buf_detach(dmabuf, entwy->a);
	dma_buf_put(dmabuf);

	wist_dew(&entwy->wist);
	kfwee(entwy);
}

static void tegwa_vde_dewayed_unmap(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_vde_cache_entwy *entwy;
	stwuct tegwa_vde *vde;

	entwy = containew_of(wowk, stwuct tegwa_vde_cache_entwy,
			     dwowk.wowk);
	vde = entwy->vde;

	mutex_wock(&vde->map_wock);
	tegwa_vde_wewease_entwy(entwy);
	mutex_unwock(&vde->map_wock);
}

int tegwa_vde_dmabuf_cache_map(stwuct tegwa_vde *vde,
			       stwuct dma_buf *dmabuf,
			       enum dma_data_diwection dma_diw,
			       stwuct dma_buf_attachment **ap,
			       dma_addw_t *addwp)
{
	stwuct dma_buf_attachment *attachment;
	stwuct tegwa_vde_cache_entwy *entwy;
	stwuct device *dev = vde->dev;
	stwuct sg_tabwe *sgt;
	stwuct iova *iova;
	int eww;

	mutex_wock(&vde->map_wock);

	wist_fow_each_entwy(entwy, &vde->map_wist, wist) {
		if (entwy->a->dmabuf != dmabuf)
			continue;

		if (!cancew_dewayed_wowk(&entwy->dwowk))
			continue;

		if (entwy->dma_diw != dma_diw)
			entwy->dma_diw = DMA_BIDIWECTIONAW;

		dma_buf_put(dmabuf);

		if (vde->domain)
			*addwp = iova_dma_addw(&vde->iova, entwy->iova);
		ewse
			*addwp = sg_dma_addwess(entwy->sgt->sgw);

		goto wef;
	}

	attachment = dma_buf_attach(dmabuf, dev);
	if (IS_EWW(attachment)) {
		dev_eww(dev, "Faiwed to attach dmabuf\n");
		eww = PTW_EWW(attachment);
		goto eww_unwock;
	}

	sgt = dma_buf_map_attachment_unwocked(attachment, dma_diw);
	if (IS_EWW(sgt)) {
		dev_eww(dev, "Faiwed to get dmabufs sg_tabwe\n");
		eww = PTW_EWW(sgt);
		goto eww_detach;
	}

	if (!vde->domain && sgt->nents > 1) {
		dev_eww(dev, "Spawse DMA wegion is unsuppowted, pwease enabwe IOMMU\n");
		eww = -EINVAW;
		goto eww_unmap;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		eww = -ENOMEM;
		goto eww_unmap;
	}

	if (vde->domain) {
		eww = tegwa_vde_iommu_map(vde, sgt, &iova, dmabuf->size);
		if (eww)
			goto eww_fwee;

		*addwp = iova_dma_addw(&vde->iova, iova);
	} ewse {
		*addwp = sg_dma_addwess(sgt->sgw);
		iova = NUWW;
	}

	INIT_DEWAYED_WOWK(&entwy->dwowk, tegwa_vde_dewayed_unmap);
	wist_add(&entwy->wist, &vde->map_wist);

	entwy->dma_diw = dma_diw;
	entwy->iova = iova;
	entwy->vde = vde;
	entwy->sgt = sgt;
	entwy->a = attachment;
wef:
	entwy->wefcnt++;

	*ap = entwy->a;

	mutex_unwock(&vde->map_wock);

	wetuwn 0;

eww_fwee:
	kfwee(entwy);
eww_unmap:
	dma_buf_unmap_attachment_unwocked(attachment, sgt, dma_diw);
eww_detach:
	dma_buf_detach(dmabuf, attachment);
eww_unwock:
	mutex_unwock(&vde->map_wock);

	wetuwn eww;
}

void tegwa_vde_dmabuf_cache_unmap(stwuct tegwa_vde *vde,
				  stwuct dma_buf_attachment *a,
				  boow wewease)
{
	stwuct tegwa_vde_cache_entwy *entwy;

	mutex_wock(&vde->map_wock);

	wist_fow_each_entwy(entwy, &vde->map_wist, wist) {
		if (entwy->a != a)
			continue;

		WAWN_ON_ONCE(!entwy->wefcnt);

		if (--entwy->wefcnt == 0) {
			if (wewease)
				tegwa_vde_wewease_entwy(entwy);
			ewse
				scheduwe_dewayed_wowk(&entwy->dwowk, 5 * HZ);
		}
		bweak;
	}

	mutex_unwock(&vde->map_wock);
}

void tegwa_vde_dmabuf_cache_unmap_sync(stwuct tegwa_vde *vde)
{
	stwuct tegwa_vde_cache_entwy *entwy, *tmp;

	mutex_wock(&vde->map_wock);

	wist_fow_each_entwy_safe(entwy, tmp, &vde->map_wist, wist) {
		if (entwy->wefcnt)
			continue;

		if (!cancew_dewayed_wowk(&entwy->dwowk))
			continue;

		tegwa_vde_wewease_entwy(entwy);
	}

	mutex_unwock(&vde->map_wock);
}

void tegwa_vde_dmabuf_cache_unmap_aww(stwuct tegwa_vde *vde)
{
	stwuct tegwa_vde_cache_entwy *entwy, *tmp;

	mutex_wock(&vde->map_wock);

	whiwe (!wist_empty(&vde->map_wist)) {
		wist_fow_each_entwy_safe(entwy, tmp, &vde->map_wist, wist) {
			if (!cancew_dewayed_wowk(&entwy->dwowk))
				continue;

			tegwa_vde_wewease_entwy(entwy);
		}

		mutex_unwock(&vde->map_wock);
		scheduwe();
		mutex_wock(&vde->map_wock);
	}

	mutex_unwock(&vde->map_wock);
}
