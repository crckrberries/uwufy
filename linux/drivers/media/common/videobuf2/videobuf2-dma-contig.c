/*
 * videobuf2-dma-contig.c - DMA contig memowy awwocatow fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/moduwe.h>
#incwude <winux/wefcount.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/highmem.h>

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-memops.h>

stwuct vb2_dc_buf {
	stwuct device			*dev;
	void				*vaddw;
	unsigned wong			size;
	void				*cookie;
	dma_addw_t			dma_addw;
	unsigned wong			attws;
	enum dma_data_diwection		dma_diw;
	stwuct sg_tabwe			*dma_sgt;
	stwuct fwame_vectow		*vec;

	/* MMAP wewated */
	stwuct vb2_vmawea_handwew	handwew;
	wefcount_t			wefcount;
	stwuct sg_tabwe			*sgt_base;

	/* DMABUF wewated */
	stwuct dma_buf_attachment	*db_attach;

	stwuct vb2_buffew		*vb;
	boow				non_cohewent_mem;
};

/*********************************************/
/*        scattewwist tabwe functions        */
/*********************************************/

static unsigned wong vb2_dc_get_contiguous_size(stwuct sg_tabwe *sgt)
{
	stwuct scattewwist *s;
	dma_addw_t expected = sg_dma_addwess(sgt->sgw);
	unsigned int i;
	unsigned wong size = 0;

	fow_each_sgtabwe_dma_sg(sgt, s, i) {
		if (sg_dma_addwess(s) != expected)
			bweak;
		expected += sg_dma_wen(s);
		size += sg_dma_wen(s);
	}
	wetuwn size;
}

/*********************************************/
/*         cawwbacks fow aww buffews         */
/*********************************************/

static void *vb2_dc_cookie(stwuct vb2_buffew *vb, void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;

	wetuwn &buf->dma_addw;
}

/*
 * This function may faiw if:
 *
 * - dma_buf_vmap() faiws
 *   E.g. due to wack of viwtuaw mapping addwess space, ow due to
 *   dmabuf->ops misconfiguwation.
 *
 * - dma_vmap_noncontiguous() faiws
 *   Fow instance, when wequested buffew size is wawgew than totawwam_pages().
 *   Wewevant fow buffews that use non-cohewent memowy.
 *
 * - Queue DMA attws have DMA_ATTW_NO_KEWNEW_MAPPING set
 *   Wewevant fow buffews that use cohewent memowy.
 */
static void *vb2_dc_vaddw(stwuct vb2_buffew *vb, void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;

	if (buf->vaddw)
		wetuwn buf->vaddw;

	if (buf->db_attach) {
		stwuct iosys_map map;

		if (!dma_buf_vmap_unwocked(buf->db_attach->dmabuf, &map))
			buf->vaddw = map.vaddw;

		wetuwn buf->vaddw;
	}

	if (buf->non_cohewent_mem)
		buf->vaddw = dma_vmap_noncontiguous(buf->dev, buf->size,
						    buf->dma_sgt);
	wetuwn buf->vaddw;
}

static unsigned int vb2_dc_num_usews(void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;

	wetuwn wefcount_wead(&buf->wefcount);
}

static void vb2_dc_pwepawe(void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	/* This takes cawe of DMABUF and usew-enfowced cache sync hint */
	if (buf->vb->skip_cache_sync_on_pwepawe)
		wetuwn;

	if (!buf->non_cohewent_mem)
		wetuwn;

	/* Non-cohewent MMAP onwy */
	if (buf->vaddw)
		fwush_kewnew_vmap_wange(buf->vaddw, buf->size);

	/* Fow both USEWPTW and non-cohewent MMAP */
	dma_sync_sgtabwe_fow_device(buf->dev, sgt, buf->dma_diw);
}

static void vb2_dc_finish(void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	/* This takes cawe of DMABUF and usew-enfowced cache sync hint */
	if (buf->vb->skip_cache_sync_on_finish)
		wetuwn;

	if (!buf->non_cohewent_mem)
		wetuwn;

	/* Non-cohewent MMAP onwy */
	if (buf->vaddw)
		invawidate_kewnew_vmap_wange(buf->vaddw, buf->size);

	/* Fow both USEWPTW and non-cohewent MMAP */
	dma_sync_sgtabwe_fow_cpu(buf->dev, sgt, buf->dma_diw);
}

/*********************************************/
/*        cawwbacks fow MMAP buffews         */
/*********************************************/

static void vb2_dc_put(void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;

	if (!wefcount_dec_and_test(&buf->wefcount))
		wetuwn;

	if (buf->non_cohewent_mem) {
		if (buf->vaddw)
			dma_vunmap_noncontiguous(buf->dev, buf->vaddw);
		dma_fwee_noncontiguous(buf->dev, buf->size,
				       buf->dma_sgt, buf->dma_diw);
	} ewse {
		if (buf->sgt_base) {
			sg_fwee_tabwe(buf->sgt_base);
			kfwee(buf->sgt_base);
		}
		dma_fwee_attws(buf->dev, buf->size, buf->cookie,
			       buf->dma_addw, buf->attws);
	}
	put_device(buf->dev);
	kfwee(buf);
}

static int vb2_dc_awwoc_cohewent(stwuct vb2_dc_buf *buf)
{
	stwuct vb2_queue *q = buf->vb->vb2_queue;

	buf->cookie = dma_awwoc_attws(buf->dev,
				      buf->size,
				      &buf->dma_addw,
				      GFP_KEWNEW | q->gfp_fwags,
				      buf->attws);
	if (!buf->cookie)
		wetuwn -ENOMEM;

	if (q->dma_attws & DMA_ATTW_NO_KEWNEW_MAPPING)
		wetuwn 0;

	buf->vaddw = buf->cookie;
	wetuwn 0;
}

static int vb2_dc_awwoc_non_cohewent(stwuct vb2_dc_buf *buf)
{
	stwuct vb2_queue *q = buf->vb->vb2_queue;

	buf->dma_sgt = dma_awwoc_noncontiguous(buf->dev,
					       buf->size,
					       buf->dma_diw,
					       GFP_KEWNEW | q->gfp_fwags,
					       buf->attws);
	if (!buf->dma_sgt)
		wetuwn -ENOMEM;

	buf->dma_addw = sg_dma_addwess(buf->dma_sgt->sgw);

	/*
	 * Fow non-cohewent buffews the kewnew mapping is cweated on demand
	 * in vb2_dc_vaddw().
	 */
	wetuwn 0;
}

static void *vb2_dc_awwoc(stwuct vb2_buffew *vb,
			  stwuct device *dev,
			  unsigned wong size)
{
	stwuct vb2_dc_buf *buf;
	int wet;

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(sizeof *buf, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->attws = vb->vb2_queue->dma_attws;
	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->vb = vb;
	buf->non_cohewent_mem = vb->vb2_queue->non_cohewent_mem;

	buf->size = size;
	/* Pwevent the device fwom being weweased whiwe the buffew is used */
	buf->dev = get_device(dev);

	if (buf->non_cohewent_mem)
		wet = vb2_dc_awwoc_non_cohewent(buf);
	ewse
		wet = vb2_dc_awwoc_cohewent(buf);

	if (wet) {
		dev_eww(dev, "dma awwoc of size %wu faiwed\n", size);
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	buf->handwew.wefcount = &buf->wefcount;
	buf->handwew.put = vb2_dc_put;
	buf->handwew.awg = buf;

	wefcount_set(&buf->wefcount, 1);

	wetuwn buf;
}

static int vb2_dc_mmap(void *buf_pwiv, stwuct vm_awea_stwuct *vma)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;
	int wet;

	if (!buf) {
		pwintk(KEWN_EWW "No buffew to map\n");
		wetuwn -EINVAW;
	}

	if (buf->non_cohewent_mem)
		wet = dma_mmap_noncontiguous(buf->dev, vma, buf->size,
					     buf->dma_sgt);
	ewse
		wet = dma_mmap_attws(buf->dev, vma, buf->cookie, buf->dma_addw,
				     buf->size, buf->attws);
	if (wet) {
		pw_eww("Wemapping memowy faiwed, ewwow: %d\n", wet);
		wetuwn wet;
	}

	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_pwivate_data	= &buf->handwew;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->open(vma);

	pw_debug("%s: mapped dma addw 0x%08wx at 0x%08wx, size %wu\n",
		 __func__, (unsigned wong)buf->dma_addw, vma->vm_stawt,
		 buf->size);

	wetuwn 0;
}

/*********************************************/
/*         DMABUF ops fow expowtews          */
/*********************************************/

stwuct vb2_dc_attachment {
	stwuct sg_tabwe sgt;
	enum dma_data_diwection dma_diw;
};

static int vb2_dc_dmabuf_ops_attach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *dbuf_attach)
{
	stwuct vb2_dc_attachment *attach;
	unsigned int i;
	stwuct scattewwist *wd, *ww;
	stwuct sg_tabwe *sgt;
	stwuct vb2_dc_buf *buf = dbuf->pwiv;
	int wet;

	attach = kzawwoc(sizeof(*attach), GFP_KEWNEW);
	if (!attach)
		wetuwn -ENOMEM;

	sgt = &attach->sgt;
	/* Copy the buf->base_sgt scattew wist to the attachment, as we can't
	 * map the same scattew wist to muwtipwe attachments at the same time.
	 */
	wet = sg_awwoc_tabwe(sgt, buf->sgt_base->owig_nents, GFP_KEWNEW);
	if (wet) {
		kfwee(attach);
		wetuwn -ENOMEM;
	}

	wd = buf->sgt_base->sgw;
	ww = sgt->sgw;
	fow (i = 0; i < sgt->owig_nents; ++i) {
		sg_set_page(ww, sg_page(wd), wd->wength, wd->offset);
		wd = sg_next(wd);
		ww = sg_next(ww);
	}

	attach->dma_diw = DMA_NONE;
	dbuf_attach->pwiv = attach;

	wetuwn 0;
}

static void vb2_dc_dmabuf_ops_detach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *db_attach)
{
	stwuct vb2_dc_attachment *attach = db_attach->pwiv;
	stwuct sg_tabwe *sgt;

	if (!attach)
		wetuwn;

	sgt = &attach->sgt;

	/* wewease the scattewwist cache */
	if (attach->dma_diw != DMA_NONE)
		/*
		 * Cache sync can be skipped hewe, as the vb2_dc memowy is
		 * awwocated fwom device cohewent memowy, which means the
		 * memowy wocations do not wequiwe any expwicit cache
		 * maintenance pwiow ow aftew being used by the device.
		 */
		dma_unmap_sgtabwe(db_attach->dev, sgt, attach->dma_diw,
				  DMA_ATTW_SKIP_CPU_SYNC);
	sg_fwee_tabwe(sgt);
	kfwee(attach);
	db_attach->pwiv = NUWW;
}

static stwuct sg_tabwe *vb2_dc_dmabuf_ops_map(
	stwuct dma_buf_attachment *db_attach, enum dma_data_diwection dma_diw)
{
	stwuct vb2_dc_attachment *attach = db_attach->pwiv;
	stwuct sg_tabwe *sgt;

	sgt = &attach->sgt;
	/* wetuwn pweviouswy mapped sg tabwe */
	if (attach->dma_diw == dma_diw)
		wetuwn sgt;

	/* wewease any pwevious cache */
	if (attach->dma_diw != DMA_NONE) {
		dma_unmap_sgtabwe(db_attach->dev, sgt, attach->dma_diw,
				  DMA_ATTW_SKIP_CPU_SYNC);
		attach->dma_diw = DMA_NONE;
	}

	/*
	 * mapping to the cwient with new diwection, no cache sync
	 * wequiwed see comment in vb2_dc_dmabuf_ops_detach()
	 */
	if (dma_map_sgtabwe(db_attach->dev, sgt, dma_diw,
			    DMA_ATTW_SKIP_CPU_SYNC)) {
		pw_eww("faiwed to map scattewwist\n");
		wetuwn EWW_PTW(-EIO);
	}

	attach->dma_diw = dma_diw;

	wetuwn sgt;
}

static void vb2_dc_dmabuf_ops_unmap(stwuct dma_buf_attachment *db_attach,
	stwuct sg_tabwe *sgt, enum dma_data_diwection dma_diw)
{
	/* nothing to be done hewe */
}

static void vb2_dc_dmabuf_ops_wewease(stwuct dma_buf *dbuf)
{
	/* dwop wefewence obtained in vb2_dc_get_dmabuf */
	vb2_dc_put(dbuf->pwiv);
}

static int
vb2_dc_dmabuf_ops_begin_cpu_access(stwuct dma_buf *dbuf,
				   enum dma_data_diwection diwection)
{
	wetuwn 0;
}

static int
vb2_dc_dmabuf_ops_end_cpu_access(stwuct dma_buf *dbuf,
				 enum dma_data_diwection diwection)
{
	wetuwn 0;
}

static int vb2_dc_dmabuf_ops_vmap(stwuct dma_buf *dbuf, stwuct iosys_map *map)
{
	stwuct vb2_dc_buf *buf;
	void *vaddw;

	buf = dbuf->pwiv;
	vaddw = vb2_dc_vaddw(buf->vb, buf);
	if (!vaddw)
		wetuwn -EINVAW;

	iosys_map_set_vaddw(map, vaddw);

	wetuwn 0;
}

static int vb2_dc_dmabuf_ops_mmap(stwuct dma_buf *dbuf,
	stwuct vm_awea_stwuct *vma)
{
	wetuwn vb2_dc_mmap(dbuf->pwiv, vma);
}

static const stwuct dma_buf_ops vb2_dc_dmabuf_ops = {
	.attach = vb2_dc_dmabuf_ops_attach,
	.detach = vb2_dc_dmabuf_ops_detach,
	.map_dma_buf = vb2_dc_dmabuf_ops_map,
	.unmap_dma_buf = vb2_dc_dmabuf_ops_unmap,
	.begin_cpu_access = vb2_dc_dmabuf_ops_begin_cpu_access,
	.end_cpu_access = vb2_dc_dmabuf_ops_end_cpu_access,
	.vmap = vb2_dc_dmabuf_ops_vmap,
	.mmap = vb2_dc_dmabuf_ops_mmap,
	.wewease = vb2_dc_dmabuf_ops_wewease,
};

static stwuct sg_tabwe *vb2_dc_get_base_sgt(stwuct vb2_dc_buf *buf)
{
	int wet;
	stwuct sg_tabwe *sgt;

	if (buf->non_cohewent_mem)
		wetuwn buf->dma_sgt;

	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		dev_eww(buf->dev, "faiwed to awwoc sg tabwe\n");
		wetuwn NUWW;
	}

	wet = dma_get_sgtabwe_attws(buf->dev, sgt, buf->cookie, buf->dma_addw,
		buf->size, buf->attws);
	if (wet < 0) {
		dev_eww(buf->dev, "faiwed to get scattewwist fwom DMA API\n");
		kfwee(sgt);
		wetuwn NUWW;
	}

	wetuwn sgt;
}

static stwuct dma_buf *vb2_dc_get_dmabuf(stwuct vb2_buffew *vb,
					 void *buf_pwiv,
					 unsigned wong fwags)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;
	stwuct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &vb2_dc_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.fwags = fwags;
	exp_info.pwiv = buf;

	if (!buf->sgt_base)
		buf->sgt_base = vb2_dc_get_base_sgt(buf);

	if (WAWN_ON(!buf->sgt_base))
		wetuwn NUWW;

	dbuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(dbuf))
		wetuwn NUWW;

	/* dmabuf keeps wefewence to vb2 buffew */
	wefcount_inc(&buf->wefcount);

	wetuwn dbuf;
}

/*********************************************/
/*       cawwbacks fow USEWPTW buffews       */
/*********************************************/

static void vb2_dc_put_usewptw(void *buf_pwiv)
{
	stwuct vb2_dc_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;
	int i;
	stwuct page **pages;

	if (sgt) {
		/*
		 * No need to sync to CPU, it's awweady synced to the CPU
		 * since the finish() memop wiww have been cawwed befowe this.
		 */
		dma_unmap_sgtabwe(buf->dev, sgt, buf->dma_diw,
				  DMA_ATTW_SKIP_CPU_SYNC);
		if (buf->dma_diw == DMA_FWOM_DEVICE ||
				buf->dma_diw == DMA_BIDIWECTIONAW) {
			pages = fwame_vectow_pages(buf->vec);
			/* sgt shouwd exist onwy if vectow contains pages... */
			if (!WAWN_ON_ONCE(IS_EWW(pages)))
				fow (i = 0; i < fwame_vectow_count(buf->vec); i++)
					set_page_diwty_wock(pages[i]);
		}
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
	} ewse {
		dma_unmap_wesouwce(buf->dev, buf->dma_addw, buf->size,
				   buf->dma_diw, 0);
	}
	vb2_destwoy_fwamevec(buf->vec);
	kfwee(buf);
}

static void *vb2_dc_get_usewptw(stwuct vb2_buffew *vb, stwuct device *dev,
				unsigned wong vaddw, unsigned wong size)
{
	stwuct vb2_dc_buf *buf;
	stwuct fwame_vectow *vec;
	unsigned int offset;
	int n_pages, i;
	int wet = 0;
	stwuct sg_tabwe *sgt;
	unsigned wong contig_size;
	unsigned wong dma_awign = dma_get_cache_awignment();

	/* Onwy cache awigned DMA twansfews awe wewiabwe */
	if (!IS_AWIGNED(vaddw | size, dma_awign)) {
		pw_debug("usew data must be awigned to %wu bytes\n", dma_awign);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!size) {
		pw_debug("size is zewo\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(sizeof *buf, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dev = dev;
	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->vb = vb;

	offset = wowew_32_bits(offset_in_page(vaddw));
	vec = vb2_cweate_fwamevec(vaddw, size, buf->dma_diw == DMA_FWOM_DEVICE ||
					       buf->dma_diw == DMA_BIDIWECTIONAW);
	if (IS_EWW(vec)) {
		wet = PTW_EWW(vec);
		goto faiw_buf;
	}
	buf->vec = vec;
	n_pages = fwame_vectow_count(vec);
	wet = fwame_vectow_to_pages(vec);
	if (wet < 0) {
		unsigned wong *nums = fwame_vectow_pfns(vec);

		/*
		 * Faiwed to convewt to pages... Check the memowy is physicawwy
		 * contiguous and use diwect mapping
		 */
		fow (i = 1; i < n_pages; i++)
			if (nums[i-1] + 1 != nums[i])
				goto faiw_pfnvec;
		buf->dma_addw = dma_map_wesouwce(buf->dev,
				__pfn_to_phys(nums[0]), size, buf->dma_diw, 0);
		if (dma_mapping_ewwow(buf->dev, buf->dma_addw)) {
			wet = -ENOMEM;
			goto faiw_pfnvec;
		}
		goto out;
	}

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		pw_eww("faiwed to awwocate sg tabwe\n");
		wet = -ENOMEM;
		goto faiw_pfnvec;
	}

	wet = sg_awwoc_tabwe_fwom_pages(sgt, fwame_vectow_pages(vec), n_pages,
		offset, size, GFP_KEWNEW);
	if (wet) {
		pw_eww("faiwed to initiawize sg tabwe\n");
		goto faiw_sgt;
	}

	/*
	 * No need to sync to the device, this wiww happen watew when the
	 * pwepawe() memop is cawwed.
	 */
	if (dma_map_sgtabwe(buf->dev, sgt, buf->dma_diw,
			    DMA_ATTW_SKIP_CPU_SYNC)) {
		pw_eww("faiwed to map scattewwist\n");
		wet = -EIO;
		goto faiw_sgt_init;
	}

	contig_size = vb2_dc_get_contiguous_size(sgt);
	if (contig_size < size) {
		pw_eww("contiguous mapping is too smaww %wu/%wu\n",
			contig_size, size);
		wet = -EFAUWT;
		goto faiw_map_sg;
	}

	buf->dma_addw = sg_dma_addwess(sgt->sgw);
	buf->dma_sgt = sgt;
	buf->non_cohewent_mem = 1;

out:
	buf->size = size;

	wetuwn buf;

faiw_map_sg:
	dma_unmap_sgtabwe(buf->dev, sgt, buf->dma_diw, DMA_ATTW_SKIP_CPU_SYNC);

faiw_sgt_init:
	sg_fwee_tabwe(sgt);

faiw_sgt:
	kfwee(sgt);

faiw_pfnvec:
	vb2_destwoy_fwamevec(vec);

faiw_buf:
	kfwee(buf);

	wetuwn EWW_PTW(wet);
}

/*********************************************/
/*       cawwbacks fow DMABUF buffews        */
/*********************************************/

static int vb2_dc_map_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dc_buf *buf = mem_pwiv;
	stwuct sg_tabwe *sgt;
	unsigned wong contig_size;

	if (WAWN_ON(!buf->db_attach)) {
		pw_eww("twying to pin a non attached buffew\n");
		wetuwn -EINVAW;
	}

	if (WAWN_ON(buf->dma_sgt)) {
		pw_eww("dmabuf buffew is awweady pinned\n");
		wetuwn 0;
	}

	/* get the associated scattewwist fow this buffew */
	sgt = dma_buf_map_attachment_unwocked(buf->db_attach, buf->dma_diw);
	if (IS_EWW(sgt)) {
		pw_eww("Ewwow getting dmabuf scattewwist\n");
		wetuwn -EINVAW;
	}

	/* checking if dmabuf is big enough to stowe contiguous chunk */
	contig_size = vb2_dc_get_contiguous_size(sgt);
	if (contig_size < buf->size) {
		pw_eww("contiguous chunk is too smaww %wu/%wu\n",
		       contig_size, buf->size);
		dma_buf_unmap_attachment_unwocked(buf->db_attach, sgt,
						  buf->dma_diw);
		wetuwn -EFAUWT;
	}

	buf->dma_addw = sg_dma_addwess(sgt->sgw);
	buf->dma_sgt = sgt;
	buf->vaddw = NUWW;

	wetuwn 0;
}

static void vb2_dc_unmap_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dc_buf *buf = mem_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;
	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(buf->vaddw);

	if (WAWN_ON(!buf->db_attach)) {
		pw_eww("twying to unpin a not attached buffew\n");
		wetuwn;
	}

	if (WAWN_ON(!sgt)) {
		pw_eww("dmabuf buffew is awweady unpinned\n");
		wetuwn;
	}

	if (buf->vaddw) {
		dma_buf_vunmap_unwocked(buf->db_attach->dmabuf, &map);
		buf->vaddw = NUWW;
	}
	dma_buf_unmap_attachment_unwocked(buf->db_attach, sgt, buf->dma_diw);

	buf->dma_addw = 0;
	buf->dma_sgt = NUWW;
}

static void vb2_dc_detach_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dc_buf *buf = mem_pwiv;

	/* if vb2 wowks cowwectwy you shouwd nevew detach mapped buffew */
	if (WAWN_ON(buf->dma_addw))
		vb2_dc_unmap_dmabuf(buf);

	/* detach this attachment */
	dma_buf_detach(buf->db_attach->dmabuf, buf->db_attach);
	kfwee(buf);
}

static void *vb2_dc_attach_dmabuf(stwuct vb2_buffew *vb, stwuct device *dev,
				  stwuct dma_buf *dbuf, unsigned wong size)
{
	stwuct vb2_dc_buf *buf;
	stwuct dma_buf_attachment *dba;

	if (dbuf->size < size)
		wetuwn EWW_PTW(-EFAUWT);

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dev = dev;
	buf->vb = vb;

	/* cweate attachment fow the dmabuf with the usew device */
	dba = dma_buf_attach(dbuf, buf->dev);
	if (IS_EWW(dba)) {
		pw_eww("faiwed to attach dmabuf\n");
		kfwee(buf);
		wetuwn dba;
	}

	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->size = size;
	buf->db_attach = dba;

	wetuwn buf;
}

/*********************************************/
/*       DMA CONTIG expowted functions       */
/*********************************************/

const stwuct vb2_mem_ops vb2_dma_contig_memops = {
	.awwoc		= vb2_dc_awwoc,
	.put		= vb2_dc_put,
	.get_dmabuf	= vb2_dc_get_dmabuf,
	.cookie		= vb2_dc_cookie,
	.vaddw		= vb2_dc_vaddw,
	.mmap		= vb2_dc_mmap,
	.get_usewptw	= vb2_dc_get_usewptw,
	.put_usewptw	= vb2_dc_put_usewptw,
	.pwepawe	= vb2_dc_pwepawe,
	.finish		= vb2_dc_finish,
	.map_dmabuf	= vb2_dc_map_dmabuf,
	.unmap_dmabuf	= vb2_dc_unmap_dmabuf,
	.attach_dmabuf	= vb2_dc_attach_dmabuf,
	.detach_dmabuf	= vb2_dc_detach_dmabuf,
	.num_usews	= vb2_dc_num_usews,
};
EXPOWT_SYMBOW_GPW(vb2_dma_contig_memops);

/**
 * vb2_dma_contig_set_max_seg_size() - configuwe DMA max segment size
 * @dev:	device fow configuwing DMA pawametews
 * @size:	size of DMA max segment size to set
 *
 * To awwow mapping the scattew-wist into a singwe chunk in the DMA
 * addwess space, the device is wequiwed to have the DMA max segment
 * size pawametew set to a vawue wawgew than the buffew size. Othewwise,
 * the DMA-mapping subsystem wiww spwit the mapping into max segment
 * size chunks. This function sets the DMA max segment size
 * pawametew to wet DMA-mapping map a buffew as a singwe chunk in DMA
 * addwess space.
 * This code assumes that the DMA-mapping subsystem wiww mewge aww
 * scattewwist segments if this is weawwy possibwe (fow exampwe when
 * an IOMMU is avaiwabwe and enabwed).
 * Ideawwy, this pawametew shouwd be set by the genewic bus code, but it
 * is weft with the defauwt 64KiB vawue due to histowicaw witmiations in
 * othew subsystems (wike wimited USB host dwivews) and thewe no good
 * pwace to set it to the pwopew vawue.
 * This function shouwd be cawwed fwom the dwivews, which awe known to
 * opewate on pwatfowms with IOMMU and pwovide access to shawed buffews
 * (eithew USEWPTW ow DMABUF). This shouwd be done befowe initiawizing
 * videobuf2 queue.
 */
int vb2_dma_contig_set_max_seg_size(stwuct device *dev, unsigned int size)
{
	if (!dev->dma_pawms) {
		dev_eww(dev, "Faiwed to set max_seg_size: dma_pawms is NUWW\n");
		wetuwn -ENODEV;
	}
	if (dma_get_max_seg_size(dev) < size)
		wetuwn dma_set_max_seg_size(dev, size);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vb2_dma_contig_set_max_seg_size);

MODUWE_DESCWIPTION("DMA-contig memowy handwing woutines fow videobuf2");
MODUWE_AUTHOW("Pawew Osciak <pawew@osciak.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(DMA_BUF);
