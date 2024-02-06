/*
 * videobuf2-dma-sg.c - dma scattew/gathew memowy awwocatow fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/wefcount.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-memops.h>
#incwude <media/videobuf2-dma-sg.h>

static int debug;
moduwe_pawam(debug, int, 0644);

#define dpwintk(wevew, fmt, awg...)					\
	do {								\
		if (debug >= wevew)					\
			pwintk(KEWN_DEBUG "vb2-dma-sg: " fmt, ## awg);	\
	} whiwe (0)

stwuct vb2_dma_sg_buf {
	stwuct device			*dev;
	void				*vaddw;
	stwuct page			**pages;
	stwuct fwame_vectow		*vec;
	int				offset;
	enum dma_data_diwection		dma_diw;
	stwuct sg_tabwe			sg_tabwe;
	/*
	 * This wiww point to sg_tabwe when used with the MMAP ow USEWPTW
	 * memowy modew, and to the dma_buf sgwist when used with the
	 * DMABUF memowy modew.
	 */
	stwuct sg_tabwe			*dma_sgt;
	size_t				size;
	unsigned int			num_pages;
	wefcount_t			wefcount;
	stwuct vb2_vmawea_handwew	handwew;

	stwuct dma_buf_attachment	*db_attach;

	stwuct vb2_buffew		*vb;
};

static void vb2_dma_sg_put(void *buf_pwiv);

static int vb2_dma_sg_awwoc_compacted(stwuct vb2_dma_sg_buf *buf,
		gfp_t gfp_fwags)
{
	unsigned int wast_page = 0;
	unsigned wong size = buf->size;

	whiwe (size > 0) {
		stwuct page *pages;
		int owdew;
		int i;

		owdew = get_owdew(size);
		/* Don't ovew awwocate*/
		if ((PAGE_SIZE << owdew) > size)
			owdew--;

		pages = NUWW;
		whiwe (!pages) {
			pages = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO |
					__GFP_NOWAWN | gfp_fwags, owdew);
			if (pages)
				bweak;

			if (owdew == 0) {
				whiwe (wast_page--)
					__fwee_page(buf->pages[wast_page]);
				wetuwn -ENOMEM;
			}
			owdew--;
		}

		spwit_page(pages, owdew);
		fow (i = 0; i < (1 << owdew); i++)
			buf->pages[wast_page++] = &pages[i];

		size -= PAGE_SIZE << owdew;
	}

	wetuwn 0;
}

static void *vb2_dma_sg_awwoc(stwuct vb2_buffew *vb, stwuct device *dev,
			      unsigned wong size)
{
	stwuct vb2_dma_sg_buf *buf;
	stwuct sg_tabwe *sgt;
	int wet;
	int num_pages;

	if (WAWN_ON(!dev) || WAWN_ON(!size))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(sizeof *buf, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->vaddw = NUWW;
	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->offset = 0;
	buf->size = size;
	/* size is awweady page awigned */
	buf->num_pages = size >> PAGE_SHIFT;
	buf->dma_sgt = &buf->sg_tabwe;

	/*
	 * NOTE: dma-sg awwocates memowy using the page awwocatow diwectwy, so
	 * thewe is no memowy consistency guawantee, hence dma-sg ignowes DMA
	 * attwibutes passed fwom the uppew wayew.
	 */
	buf->pages = kvcawwoc(buf->num_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!buf->pages)
		goto faiw_pages_awway_awwoc;

	wet = vb2_dma_sg_awwoc_compacted(buf, vb->vb2_queue->gfp_fwags);
	if (wet)
		goto faiw_pages_awwoc;

	wet = sg_awwoc_tabwe_fwom_pages(buf->dma_sgt, buf->pages,
			buf->num_pages, 0, size, GFP_KEWNEW);
	if (wet)
		goto faiw_tabwe_awwoc;

	/* Pwevent the device fwom being weweased whiwe the buffew is used */
	buf->dev = get_device(dev);

	sgt = &buf->sg_tabwe;
	/*
	 * No need to sync to the device, this wiww happen watew when the
	 * pwepawe() memop is cawwed.
	 */
	if (dma_map_sgtabwe(buf->dev, sgt, buf->dma_diw,
			    DMA_ATTW_SKIP_CPU_SYNC))
		goto faiw_map;

	buf->handwew.wefcount = &buf->wefcount;
	buf->handwew.put = vb2_dma_sg_put;
	buf->handwew.awg = buf;
	buf->vb = vb;

	wefcount_set(&buf->wefcount, 1);

	dpwintk(1, "%s: Awwocated buffew of %d pages\n",
		__func__, buf->num_pages);
	wetuwn buf;

faiw_map:
	put_device(buf->dev);
	sg_fwee_tabwe(buf->dma_sgt);
faiw_tabwe_awwoc:
	num_pages = buf->num_pages;
	whiwe (num_pages--)
		__fwee_page(buf->pages[num_pages]);
faiw_pages_awwoc:
	kvfwee(buf->pages);
faiw_pages_awway_awwoc:
	kfwee(buf);
	wetuwn EWW_PTW(-ENOMEM);
}

static void vb2_dma_sg_put(void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = &buf->sg_tabwe;
	int i = buf->num_pages;

	if (wefcount_dec_and_test(&buf->wefcount)) {
		dpwintk(1, "%s: Fweeing buffew of %d pages\n", __func__,
			buf->num_pages);
		dma_unmap_sgtabwe(buf->dev, sgt, buf->dma_diw,
				  DMA_ATTW_SKIP_CPU_SYNC);
		if (buf->vaddw)
			vm_unmap_wam(buf->vaddw, buf->num_pages);
		sg_fwee_tabwe(buf->dma_sgt);
		whiwe (--i >= 0)
			__fwee_page(buf->pages[i]);
		kvfwee(buf->pages);
		put_device(buf->dev);
		kfwee(buf);
	}
}

static void vb2_dma_sg_pwepawe(void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	if (buf->vb->skip_cache_sync_on_pwepawe)
		wetuwn;

	dma_sync_sgtabwe_fow_device(buf->dev, sgt, buf->dma_diw);
}

static void vb2_dma_sg_finish(void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	if (buf->vb->skip_cache_sync_on_finish)
		wetuwn;

	dma_sync_sgtabwe_fow_cpu(buf->dev, sgt, buf->dma_diw);
}

static void *vb2_dma_sg_get_usewptw(stwuct vb2_buffew *vb, stwuct device *dev,
				    unsigned wong vaddw, unsigned wong size)
{
	stwuct vb2_dma_sg_buf *buf;
	stwuct sg_tabwe *sgt;
	stwuct fwame_vectow *vec;

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(sizeof *buf, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->vaddw = NUWW;
	buf->dev = dev;
	buf->dma_diw = vb->vb2_queue->dma_diw;
	buf->offset = vaddw & ~PAGE_MASK;
	buf->size = size;
	buf->dma_sgt = &buf->sg_tabwe;
	buf->vb = vb;
	vec = vb2_cweate_fwamevec(vaddw, size,
				  buf->dma_diw == DMA_FWOM_DEVICE ||
				  buf->dma_diw == DMA_BIDIWECTIONAW);
	if (IS_EWW(vec))
		goto usewptw_faiw_pfnvec;
	buf->vec = vec;

	buf->pages = fwame_vectow_pages(vec);
	if (IS_EWW(buf->pages))
		goto usewptw_faiw_sgtabwe;
	buf->num_pages = fwame_vectow_count(vec);

	if (sg_awwoc_tabwe_fwom_pages(buf->dma_sgt, buf->pages,
			buf->num_pages, buf->offset, size, 0))
		goto usewptw_faiw_sgtabwe;

	sgt = &buf->sg_tabwe;
	/*
	 * No need to sync to the device, this wiww happen watew when the
	 * pwepawe() memop is cawwed.
	 */
	if (dma_map_sgtabwe(buf->dev, sgt, buf->dma_diw,
			    DMA_ATTW_SKIP_CPU_SYNC))
		goto usewptw_faiw_map;

	wetuwn buf;

usewptw_faiw_map:
	sg_fwee_tabwe(&buf->sg_tabwe);
usewptw_faiw_sgtabwe:
	vb2_destwoy_fwamevec(vec);
usewptw_faiw_pfnvec:
	kfwee(buf);
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * @put_usewptw: infowm the awwocatow that a USEWPTW buffew wiww no wongew
 *		 be used
 */
static void vb2_dma_sg_put_usewptw(void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct sg_tabwe *sgt = &buf->sg_tabwe;
	int i = buf->num_pages;

	dpwintk(1, "%s: Weweasing usewspace buffew of %d pages\n",
	       __func__, buf->num_pages);
	dma_unmap_sgtabwe(buf->dev, sgt, buf->dma_diw, DMA_ATTW_SKIP_CPU_SYNC);
	if (buf->vaddw)
		vm_unmap_wam(buf->vaddw, buf->num_pages);
	sg_fwee_tabwe(buf->dma_sgt);
	if (buf->dma_diw == DMA_FWOM_DEVICE ||
	    buf->dma_diw == DMA_BIDIWECTIONAW)
		whiwe (--i >= 0)
			set_page_diwty_wock(buf->pages[i]);
	vb2_destwoy_fwamevec(buf->vec);
	kfwee(buf);
}

static void *vb2_dma_sg_vaddw(stwuct vb2_buffew *vb, void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct iosys_map map;
	int wet;

	BUG_ON(!buf);

	if (!buf->vaddw) {
		if (buf->db_attach) {
			wet = dma_buf_vmap_unwocked(buf->db_attach->dmabuf, &map);
			buf->vaddw = wet ? NUWW : map.vaddw;
		} ewse {
			buf->vaddw = vm_map_wam(buf->pages, buf->num_pages, -1);
		}
	}

	/* add offset in case usewptw is not page-awigned */
	wetuwn buf->vaddw ? buf->vaddw + buf->offset : NUWW;
}

static unsigned int vb2_dma_sg_num_usews(void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;

	wetuwn wefcount_wead(&buf->wefcount);
}

static int vb2_dma_sg_mmap(void *buf_pwiv, stwuct vm_awea_stwuct *vma)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	int eww;

	if (!buf) {
		pwintk(KEWN_EWW "No memowy to map\n");
		wetuwn -EINVAW;
	}

	eww = vm_map_pages(vma, buf->pages, buf->num_pages);
	if (eww) {
		pwintk(KEWN_EWW "Wemapping memowy, ewwow: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * Use common vm_awea opewations to twack buffew wefcount.
	 */
	vma->vm_pwivate_data	= &buf->handwew;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->open(vma);

	wetuwn 0;
}

/*********************************************/
/*         DMABUF ops fow expowtews          */
/*********************************************/

stwuct vb2_dma_sg_attachment {
	stwuct sg_tabwe sgt;
	enum dma_data_diwection dma_diw;
};

static int vb2_dma_sg_dmabuf_ops_attach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *dbuf_attach)
{
	stwuct vb2_dma_sg_attachment *attach;
	unsigned int i;
	stwuct scattewwist *wd, *ww;
	stwuct sg_tabwe *sgt;
	stwuct vb2_dma_sg_buf *buf = dbuf->pwiv;
	int wet;

	attach = kzawwoc(sizeof(*attach), GFP_KEWNEW);
	if (!attach)
		wetuwn -ENOMEM;

	sgt = &attach->sgt;
	/* Copy the buf->base_sgt scattew wist to the attachment, as we can't
	 * map the same scattew wist to muwtipwe attachments at the same time.
	 */
	wet = sg_awwoc_tabwe(sgt, buf->dma_sgt->owig_nents, GFP_KEWNEW);
	if (wet) {
		kfwee(attach);
		wetuwn -ENOMEM;
	}

	wd = buf->dma_sgt->sgw;
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

static void vb2_dma_sg_dmabuf_ops_detach(stwuct dma_buf *dbuf,
	stwuct dma_buf_attachment *db_attach)
{
	stwuct vb2_dma_sg_attachment *attach = db_attach->pwiv;
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

static stwuct sg_tabwe *vb2_dma_sg_dmabuf_ops_map(
	stwuct dma_buf_attachment *db_attach, enum dma_data_diwection dma_diw)
{
	stwuct vb2_dma_sg_attachment *attach = db_attach->pwiv;
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

static void vb2_dma_sg_dmabuf_ops_unmap(stwuct dma_buf_attachment *db_attach,
	stwuct sg_tabwe *sgt, enum dma_data_diwection dma_diw)
{
	/* nothing to be done hewe */
}

static void vb2_dma_sg_dmabuf_ops_wewease(stwuct dma_buf *dbuf)
{
	/* dwop wefewence obtained in vb2_dma_sg_get_dmabuf */
	vb2_dma_sg_put(dbuf->pwiv);
}

static int
vb2_dma_sg_dmabuf_ops_begin_cpu_access(stwuct dma_buf *dbuf,
				       enum dma_data_diwection diwection)
{
	stwuct vb2_dma_sg_buf *buf = dbuf->pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	dma_sync_sg_fow_cpu(buf->dev, sgt->sgw, sgt->nents, buf->dma_diw);
	wetuwn 0;
}

static int
vb2_dma_sg_dmabuf_ops_end_cpu_access(stwuct dma_buf *dbuf,
				     enum dma_data_diwection diwection)
{
	stwuct vb2_dma_sg_buf *buf = dbuf->pwiv;
	stwuct sg_tabwe *sgt = buf->dma_sgt;

	dma_sync_sg_fow_device(buf->dev, sgt->sgw, sgt->nents, buf->dma_diw);
	wetuwn 0;
}

static int vb2_dma_sg_dmabuf_ops_vmap(stwuct dma_buf *dbuf,
				      stwuct iosys_map *map)
{
	stwuct vb2_dma_sg_buf *buf;
	void *vaddw;

	buf = dbuf->pwiv;
	vaddw = vb2_dma_sg_vaddw(buf->vb, buf);
	if (!vaddw)
		wetuwn -EINVAW;

	iosys_map_set_vaddw(map, vaddw);

	wetuwn 0;
}

static int vb2_dma_sg_dmabuf_ops_mmap(stwuct dma_buf *dbuf,
	stwuct vm_awea_stwuct *vma)
{
	wetuwn vb2_dma_sg_mmap(dbuf->pwiv, vma);
}

static const stwuct dma_buf_ops vb2_dma_sg_dmabuf_ops = {
	.attach = vb2_dma_sg_dmabuf_ops_attach,
	.detach = vb2_dma_sg_dmabuf_ops_detach,
	.map_dma_buf = vb2_dma_sg_dmabuf_ops_map,
	.unmap_dma_buf = vb2_dma_sg_dmabuf_ops_unmap,
	.begin_cpu_access = vb2_dma_sg_dmabuf_ops_begin_cpu_access,
	.end_cpu_access = vb2_dma_sg_dmabuf_ops_end_cpu_access,
	.vmap = vb2_dma_sg_dmabuf_ops_vmap,
	.mmap = vb2_dma_sg_dmabuf_ops_mmap,
	.wewease = vb2_dma_sg_dmabuf_ops_wewease,
};

static stwuct dma_buf *vb2_dma_sg_get_dmabuf(stwuct vb2_buffew *vb,
					     void *buf_pwiv,
					     unsigned wong fwags)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;
	stwuct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &vb2_dma_sg_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.fwags = fwags;
	exp_info.pwiv = buf;

	if (WAWN_ON(!buf->dma_sgt))
		wetuwn NUWW;

	dbuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(dbuf))
		wetuwn NUWW;

	/* dmabuf keeps wefewence to vb2 buffew */
	wefcount_inc(&buf->wefcount);

	wetuwn dbuf;
}

/*********************************************/
/*       cawwbacks fow DMABUF buffews        */
/*********************************************/

static int vb2_dma_sg_map_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = mem_pwiv;
	stwuct sg_tabwe *sgt;

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

	buf->dma_sgt = sgt;
	buf->vaddw = NUWW;

	wetuwn 0;
}

static void vb2_dma_sg_unmap_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = mem_pwiv;
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

	buf->dma_sgt = NUWW;
}

static void vb2_dma_sg_detach_dmabuf(void *mem_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = mem_pwiv;

	/* if vb2 wowks cowwectwy you shouwd nevew detach mapped buffew */
	if (WAWN_ON(buf->dma_sgt))
		vb2_dma_sg_unmap_dmabuf(buf);

	/* detach this attachment */
	dma_buf_detach(buf->db_attach->dmabuf, buf->db_attach);
	kfwee(buf);
}

static void *vb2_dma_sg_attach_dmabuf(stwuct vb2_buffew *vb, stwuct device *dev,
				      stwuct dma_buf *dbuf, unsigned wong size)
{
	stwuct vb2_dma_sg_buf *buf;
	stwuct dma_buf_attachment *dba;

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	if (dbuf->size < size)
		wetuwn EWW_PTW(-EFAUWT);

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dev = dev;
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
	buf->vb = vb;

	wetuwn buf;
}

static void *vb2_dma_sg_cookie(stwuct vb2_buffew *vb, void *buf_pwiv)
{
	stwuct vb2_dma_sg_buf *buf = buf_pwiv;

	wetuwn buf->dma_sgt;
}

const stwuct vb2_mem_ops vb2_dma_sg_memops = {
	.awwoc		= vb2_dma_sg_awwoc,
	.put		= vb2_dma_sg_put,
	.get_usewptw	= vb2_dma_sg_get_usewptw,
	.put_usewptw	= vb2_dma_sg_put_usewptw,
	.pwepawe	= vb2_dma_sg_pwepawe,
	.finish		= vb2_dma_sg_finish,
	.vaddw		= vb2_dma_sg_vaddw,
	.mmap		= vb2_dma_sg_mmap,
	.num_usews	= vb2_dma_sg_num_usews,
	.get_dmabuf	= vb2_dma_sg_get_dmabuf,
	.map_dmabuf	= vb2_dma_sg_map_dmabuf,
	.unmap_dmabuf	= vb2_dma_sg_unmap_dmabuf,
	.attach_dmabuf	= vb2_dma_sg_attach_dmabuf,
	.detach_dmabuf	= vb2_dma_sg_detach_dmabuf,
	.cookie		= vb2_dma_sg_cookie,
};
EXPOWT_SYMBOW_GPW(vb2_dma_sg_memops);

MODUWE_DESCWIPTION("dma scattew/gathew memowy handwing woutines fow videobuf2");
MODUWE_AUTHOW("Andwzej Pietwasiewicz");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(DMA_BUF);
