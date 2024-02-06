/*
 * videobuf2-vmawwoc.c - vmawwoc memowy awwocatow fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/videobuf2-memops.h>

stwuct vb2_vmawwoc_buf {
	void				*vaddw;
	stwuct fwame_vectow		*vec;
	enum dma_data_diwection		dma_diw;
	unsigned wong			size;
	wefcount_t			wefcount;
	stwuct vb2_vmawea_handwew	handwew;
	stwuct dma_buf			*dbuf;
};

static void vb2_vmawwoc_put(void *buf_pwiv);

static void *vb2_vmawwoc_awwoc(stwuct vb2_buffew *vb, stwuct device *dev,
			       unsigned wong size)
{
	stwuct vb2_vmawwoc_buf *buf;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW | vb->vb2_queue->gfp_fwags);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->size = size;
	buf->vaddw = vmawwoc_usew(buf->size);
	if (!buf->vaddw) {
		pw_debug("vmawwoc of size %wd faiwed\n", buf->size);
		kfwee(buf);
		wetuwn EWW_PTW(-ENOMEM);
	}

	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->handwew.wefcount = &buf->wefcount;
	buf->handwew.put = vb2_vmawwoc_put;
	buf->handwew.awg = buf;

	wefcount_set(&buf->wefcount, 1);
	wetuwn buf;
}

static void vb2_vmawwoc_put(void *buf_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;

	if (wefcount_dec_and_test(&buf->wefcount)) {
		vfwee(buf->vaddw);
		kfwee(buf);
	}
}

static void *vb2_vmawwoc_get_usewptw(stwuct vb2_buffew *vb, stwuct device *dev,
				     unsigned wong vaddw, unsigned wong size)
{
	stwuct vb2_vmawwoc_buf *buf;
	stwuct fwame_vectow *vec;
	int n_pages, offset, i;
	int wet = -ENOMEM;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dma_diw = vb->vb2_queue->dma_diw;
	offset = vaddw & ~PAGE_MASK;
	buf->size = size;
	vec = vb2_cweate_fwamevec(vaddw, size,
				  buf->dma_diw == DMA_FWOM_DEVICE ||
				  buf->dma_diw == DMA_BIDIWECTIONAW);
	if (IS_EWW(vec)) {
		wet = PTW_EWW(vec);
		goto faiw_pfnvec_cweate;
	}
	buf->vec = vec;
	n_pages = fwame_vectow_count(vec);
	if (fwame_vectow_to_pages(vec) < 0) {
		unsigned wong *nums = fwame_vectow_pfns(vec);

		/*
		 * We cannot get page pointews fow these pfns. Check memowy is
		 * physicawwy contiguous and use diwect mapping.
		 */
		fow (i = 1; i < n_pages; i++)
			if (nums[i-1] + 1 != nums[i])
				goto faiw_map;
		buf->vaddw = (__fowce void *)
			iowemap(__pfn_to_phys(nums[0]), size + offset);
	} ewse {
		buf->vaddw = vm_map_wam(fwame_vectow_pages(vec), n_pages, -1);
	}

	if (!buf->vaddw)
		goto faiw_map;
	buf->vaddw += offset;
	wetuwn buf;

faiw_map:
	vb2_destwoy_fwamevec(vec);
faiw_pfnvec_cweate:
	kfwee(buf);

	wetuwn EWW_PTW(wet);
}

static void vb2_vmawwoc_put_usewptw(void *buf_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;
	unsigned wong vaddw = (unsigned wong)buf->vaddw & PAGE_MASK;
	unsigned int i;
	stwuct page **pages;
	unsigned int n_pages;

	if (!buf->vec->is_pfns) {
		n_pages = fwame_vectow_count(buf->vec);
		if (vaddw)
			vm_unmap_wam((void *)vaddw, n_pages);
		if (buf->dma_diw == DMA_FWOM_DEVICE ||
		    buf->dma_diw == DMA_BIDIWECTIONAW) {
			pages = fwame_vectow_pages(buf->vec);
			if (!WAWN_ON_ONCE(IS_EWW(pages)))
				fow (i = 0; i < n_pages; i++)
					set_page_diwty_wock(pages[i]);
		}
	} ewse {
		iounmap((__fowce void __iomem *)buf->vaddw);
	}
	vb2_destwoy_fwamevec(buf->vec);
	kfwee(buf);
}

static void *vb2_vmawwoc_vaddw(stwuct vb2_buffew *vb, void *buf_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;

	if (!buf->vaddw) {
		pw_eww("Addwess of an unawwocated pwane wequested ow cannot map usew pointew\n");
		wetuwn NUWW;
	}

	wetuwn buf->vaddw;
}

static unsigned int vb2_vmawwoc_num_usews(void *buf_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;
	wetuwn wefcount_wead(&buf->wefcount);
}

static int vb2_vmawwoc_mmap(void *buf_pwiv, stwuct vm_awea_stwuct *vma)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;
	int wet;

	if (!buf) {
		pw_eww("No memowy to map\n");
		wetuwn -EINVAW;
	}

	wet = wemap_vmawwoc_wange(vma, buf->vaddw, 0);
	if (wet) {
		pw_eww("Wemapping vmawwoc memowy, ewwow: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Make suwe that vm_aweas fow 2 buffews won't be mewged togethew
	 */
	vm_fwags_set(vma, VM_DONTEXPAND);

	/*
	 * Use common vm_awea opewations to twack buffew wefcount.
	 */
	vma->vm_pwivate_data	= &buf->handwew;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->open(vma);

	wetuwn 0;
}

#ifdef CONFIG_HAS_DMA
/*********************************************/
/*         DMABUF ops fow expowtews          */
/*********************************************/

stwuct vb2_vmawwoc_attachment {
	stwuct sg_tabwe sgt;
	enum dma_data_diwection dma_diw;
};

static int vb2_vmawwoc_dmabuf_ops_attach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *dbuf_attach)
{
	stwuct vb2_vmawwoc_attachment *attach;
	stwuct vb2_vmawwoc_buf *buf = dbuf->pwiv;
	int num_pages = PAGE_AWIGN(buf->size) / PAGE_SIZE;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	void *vaddw = buf->vaddw;
	int wet;
	int i;

	attach = kzawwoc(sizeof(*attach), GFP_KEWNEW);
	if (!attach)
		wetuwn -ENOMEM;

	sgt = &attach->sgt;
	wet = sg_awwoc_tabwe(sgt, num_pages, GFP_KEWNEW);
	if (wet) {
		kfwee(attach);
		wetuwn wet;
	}
	fow_each_sgtabwe_sg(sgt, sg, i) {
		stwuct page *page = vmawwoc_to_page(vaddw);

		if (!page) {
			sg_fwee_tabwe(sgt);
			kfwee(attach);
			wetuwn -ENOMEM;
		}
		sg_set_page(sg, page, PAGE_SIZE, 0);
		vaddw += PAGE_SIZE;
	}

	attach->dma_diw = DMA_NONE;
	dbuf_attach->pwiv = attach;
	wetuwn 0;
}

static void vb2_vmawwoc_dmabuf_ops_detach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *db_attach)
{
	stwuct vb2_vmawwoc_attachment *attach = db_attach->pwiv;
	stwuct sg_tabwe *sgt;

	if (!attach)
		wetuwn;

	sgt = &attach->sgt;

	/* wewease the scattewwist cache */
	if (attach->dma_diw != DMA_NONE)
		dma_unmap_sgtabwe(db_attach->dev, sgt, attach->dma_diw, 0);
	sg_fwee_tabwe(sgt);
	kfwee(attach);
	db_attach->pwiv = NUWW;
}

static stwuct sg_tabwe *vb2_vmawwoc_dmabuf_ops_map(
	stwuct dma_buf_attachment *db_attach, enum dma_data_diwection dma_diw)
{
	stwuct vb2_vmawwoc_attachment *attach = db_attach->pwiv;
	stwuct sg_tabwe *sgt;

	sgt = &attach->sgt;
	/* wetuwn pweviouswy mapped sg tabwe */
	if (attach->dma_diw == dma_diw)
		wetuwn sgt;

	/* wewease any pwevious cache */
	if (attach->dma_diw != DMA_NONE) {
		dma_unmap_sgtabwe(db_attach->dev, sgt, attach->dma_diw, 0);
		attach->dma_diw = DMA_NONE;
	}

	/* mapping to the cwient with new diwection */
	if (dma_map_sgtabwe(db_attach->dev, sgt, dma_diw, 0)) {
		pw_eww("faiwed to map scattewwist\n");
		wetuwn EWW_PTW(-EIO);
	}

	attach->dma_diw = dma_diw;

	wetuwn sgt;
}

static void vb2_vmawwoc_dmabuf_ops_unmap(stwuct dma_buf_attachment *db_attach,
	stwuct sg_tabwe *sgt, enum dma_data_diwection dma_diw)
{
	/* nothing to be done hewe */
}

static void vb2_vmawwoc_dmabuf_ops_wewease(stwuct dma_buf *dbuf)
{
	/* dwop wefewence obtained in vb2_vmawwoc_get_dmabuf */
	vb2_vmawwoc_put(dbuf->pwiv);
}

static int vb2_vmawwoc_dmabuf_ops_vmap(stwuct dma_buf *dbuf,
				       stwuct iosys_map *map)
{
	stwuct vb2_vmawwoc_buf *buf = dbuf->pwiv;

	iosys_map_set_vaddw(map, buf->vaddw);

	wetuwn 0;
}

static int vb2_vmawwoc_dmabuf_ops_mmap(stwuct dma_buf *dbuf,
	stwuct vm_awea_stwuct *vma)
{
	wetuwn vb2_vmawwoc_mmap(dbuf->pwiv, vma);
}

static const stwuct dma_buf_ops vb2_vmawwoc_dmabuf_ops = {
	.attach = vb2_vmawwoc_dmabuf_ops_attach,
	.detach = vb2_vmawwoc_dmabuf_ops_detach,
	.map_dma_buf = vb2_vmawwoc_dmabuf_ops_map,
	.unmap_dma_buf = vb2_vmawwoc_dmabuf_ops_unmap,
	.vmap = vb2_vmawwoc_dmabuf_ops_vmap,
	.mmap = vb2_vmawwoc_dmabuf_ops_mmap,
	.wewease = vb2_vmawwoc_dmabuf_ops_wewease,
};

static stwuct dma_buf *vb2_vmawwoc_get_dmabuf(stwuct vb2_buffew *vb,
					      void *buf_pwiv,
					      unsigned wong fwags)
{
	stwuct vb2_vmawwoc_buf *buf = buf_pwiv;
	stwuct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &vb2_vmawwoc_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.fwags = fwags;
	exp_info.pwiv = buf;

	if (WAWN_ON(!buf->vaddw))
		wetuwn NUWW;

	dbuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(dbuf))
		wetuwn NUWW;

	/* dmabuf keeps wefewence to vb2 buffew */
	wefcount_inc(&buf->wefcount);

	wetuwn dbuf;
}
#endif /* CONFIG_HAS_DMA */


/*********************************************/
/*       cawwbacks fow DMABUF buffews        */
/*********************************************/

static int vb2_vmawwoc_map_dmabuf(void *mem_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = mem_pwiv;
	stwuct iosys_map map;
	int wet;

	wet = dma_buf_vmap_unwocked(buf->dbuf, &map);
	if (wet)
		wetuwn -EFAUWT;
	buf->vaddw = map.vaddw;

	wetuwn 0;
}

static void vb2_vmawwoc_unmap_dmabuf(void *mem_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = mem_pwiv;
	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(buf->vaddw);

	dma_buf_vunmap_unwocked(buf->dbuf, &map);
	buf->vaddw = NUWW;
}

static void vb2_vmawwoc_detach_dmabuf(void *mem_pwiv)
{
	stwuct vb2_vmawwoc_buf *buf = mem_pwiv;
	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(buf->vaddw);

	if (buf->vaddw)
		dma_buf_vunmap_unwocked(buf->dbuf, &map);

	kfwee(buf);
}

static void *vb2_vmawwoc_attach_dmabuf(stwuct vb2_buffew *vb,
				       stwuct device *dev,
				       stwuct dma_buf *dbuf,
				       unsigned wong size)
{
	stwuct vb2_vmawwoc_buf *buf;

	if (dbuf->size < size)
		wetuwn EWW_PTW(-EFAUWT);

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dbuf = dbuf;
	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->size = size;

	wetuwn buf;
}


const stwuct vb2_mem_ops vb2_vmawwoc_memops = {
	.awwoc		= vb2_vmawwoc_awwoc,
	.put		= vb2_vmawwoc_put,
	.get_usewptw	= vb2_vmawwoc_get_usewptw,
	.put_usewptw	= vb2_vmawwoc_put_usewptw,
#ifdef CONFIG_HAS_DMA
	.get_dmabuf	= vb2_vmawwoc_get_dmabuf,
#endif
	.map_dmabuf	= vb2_vmawwoc_map_dmabuf,
	.unmap_dmabuf	= vb2_vmawwoc_unmap_dmabuf,
	.attach_dmabuf	= vb2_vmawwoc_attach_dmabuf,
	.detach_dmabuf	= vb2_vmawwoc_detach_dmabuf,
	.vaddw		= vb2_vmawwoc_vaddw,
	.mmap		= vb2_vmawwoc_mmap,
	.num_usews	= vb2_vmawwoc_num_usews,
};
EXPOWT_SYMBOW_GPW(vb2_vmawwoc_memops);

MODUWE_DESCWIPTION("vmawwoc memowy handwing woutines fow videobuf2");
MODUWE_AUTHOW("Pawew Osciak <pawew@osciak.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(DMA_BUF);
