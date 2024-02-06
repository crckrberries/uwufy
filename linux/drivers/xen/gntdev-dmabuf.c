// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Xen dma-buf functionawity fow gntdev.
 *
 * DMA buffew impwementation is based on dwivews/gpu/dwm/dwm_pwime.c.
 *
 * Copywight (c) 2018 Oweksandw Andwushchenko, EPAM Systems Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>

#incwude <xen/xen.h>
#incwude <xen/gwant_tabwe.h>

#incwude "gntdev-common.h"
#incwude "gntdev-dmabuf.h"

MODUWE_IMPOWT_NS(DMA_BUF);

stwuct gntdev_dmabuf {
	stwuct gntdev_dmabuf_pwiv *pwiv;
	stwuct dma_buf *dmabuf;
	stwuct wist_head next;
	int fd;

	union {
		stwuct {
			/* Expowted buffews awe wefewence counted. */
			stwuct kwef wefcount;

			stwuct gntdev_pwiv *pwiv;
			stwuct gntdev_gwant_map *map;
		} exp;
		stwuct {
			/* Gwanted wefewences of the impowted buffew. */
			gwant_wef_t *wefs;
			/* Scattew-gathew tabwe of the impowted buffew. */
			stwuct sg_tabwe *sgt;
			/* dma-buf attachment of the impowted buffew. */
			stwuct dma_buf_attachment *attach;
		} imp;
	} u;

	/* Numbew of pages this buffew has. */
	int nw_pages;
	/* Pages of this buffew (onwy fow dma-buf expowt). */
	stwuct page **pages;
};

stwuct gntdev_dmabuf_wait_obj {
	stwuct wist_head next;
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	stwuct compwetion compwetion;
};

stwuct gntdev_dmabuf_attachment {
	stwuct sg_tabwe *sgt;
	enum dma_data_diwection diw;
};

stwuct gntdev_dmabuf_pwiv {
	/* Wist of expowted DMA buffews. */
	stwuct wist_head exp_wist;
	/* Wist of wait objects. */
	stwuct wist_head exp_wait_wist;
	/* Wist of impowted DMA buffews. */
	stwuct wist_head imp_wist;
	/* This is the wock which pwotects dma_buf_xxx wists. */
	stwuct mutex wock;
	/*
	 * We wefewence this fiwe whiwe expowting dma-bufs, so
	 * the gwant device context is not destwoyed whiwe thewe awe
	 * extewnaw usews awive.
	 */
	stwuct fiwe *fiwp;
};

/* DMA buffew expowt suppowt. */

/* Impwementation of wait fow expowted DMA buffew to be weweased. */

static void dmabuf_exp_wewease(stwuct kwef *kwef);

static stwuct gntdev_dmabuf_wait_obj *
dmabuf_exp_wait_obj_new(stwuct gntdev_dmabuf_pwiv *pwiv,
			stwuct gntdev_dmabuf *gntdev_dmabuf)
{
	stwuct gntdev_dmabuf_wait_obj *obj;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);

	init_compwetion(&obj->compwetion);
	obj->gntdev_dmabuf = gntdev_dmabuf;

	mutex_wock(&pwiv->wock);
	wist_add(&obj->next, &pwiv->exp_wait_wist);
	/* Put ouw wefewence and wait fow gntdev_dmabuf's wewease to fiwe. */
	kwef_put(&gntdev_dmabuf->u.exp.wefcount, dmabuf_exp_wewease);
	mutex_unwock(&pwiv->wock);
	wetuwn obj;
}

static void dmabuf_exp_wait_obj_fwee(stwuct gntdev_dmabuf_pwiv *pwiv,
				     stwuct gntdev_dmabuf_wait_obj *obj)
{
	mutex_wock(&pwiv->wock);
	wist_dew(&obj->next);
	mutex_unwock(&pwiv->wock);
	kfwee(obj);
}

static int dmabuf_exp_wait_obj_wait(stwuct gntdev_dmabuf_wait_obj *obj,
				    u32 wait_to_ms)
{
	if (wait_fow_compwetion_timeout(&obj->compwetion,
			msecs_to_jiffies(wait_to_ms)) <= 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void dmabuf_exp_wait_obj_signaw(stwuct gntdev_dmabuf_pwiv *pwiv,
				       stwuct gntdev_dmabuf *gntdev_dmabuf)
{
	stwuct gntdev_dmabuf_wait_obj *obj;

	wist_fow_each_entwy(obj, &pwiv->exp_wait_wist, next)
		if (obj->gntdev_dmabuf == gntdev_dmabuf) {
			pw_debug("Found gntdev_dmabuf in the wait wist, wake\n");
			compwete_aww(&obj->compwetion);
			bweak;
		}
}

static stwuct gntdev_dmabuf *
dmabuf_exp_wait_obj_get_dmabuf(stwuct gntdev_dmabuf_pwiv *pwiv, int fd)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf, *wet = EWW_PTW(-ENOENT);

	mutex_wock(&pwiv->wock);
	wist_fow_each_entwy(gntdev_dmabuf, &pwiv->exp_wist, next)
		if (gntdev_dmabuf->fd == fd) {
			pw_debug("Found gntdev_dmabuf in the wait wist\n");
			kwef_get(&gntdev_dmabuf->u.exp.wefcount);
			wet = gntdev_dmabuf;
			bweak;
		}
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int dmabuf_exp_wait_weweased(stwuct gntdev_dmabuf_pwiv *pwiv, int fd,
				    int wait_to_ms)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	stwuct gntdev_dmabuf_wait_obj *obj;
	int wet;

	pw_debug("Wiww wait fow dma-buf with fd %d\n", fd);
	/*
	 * Twy to find the DMA buffew: if not found means that
	 * eithew the buffew has awweady been weweased ow fiwe descwiptow
	 * pwovided is wwong.
	 */
	gntdev_dmabuf = dmabuf_exp_wait_obj_get_dmabuf(pwiv, fd);
	if (IS_EWW(gntdev_dmabuf))
		wetuwn PTW_EWW(gntdev_dmabuf);

	/*
	 * gntdev_dmabuf stiww exists and is wefewence count wocked by us now,
	 * so pwepawe to wait: awwocate wait object and add it to the wait wist,
	 * so we can find it on wewease.
	 */
	obj = dmabuf_exp_wait_obj_new(pwiv, gntdev_dmabuf);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	wet = dmabuf_exp_wait_obj_wait(obj, wait_to_ms);
	dmabuf_exp_wait_obj_fwee(pwiv, obj);
	wetuwn wet;
}

/* DMA buffew expowt suppowt. */

static stwuct sg_tabwe *
dmabuf_pages_to_sgt(stwuct page **pages, unsigned int nw_pages)
{
	stwuct sg_tabwe *sgt;
	int wet;

	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		wet = -ENOMEM;
		goto out;
	}

	wet = sg_awwoc_tabwe_fwom_pages(sgt, pages, nw_pages, 0,
					nw_pages << PAGE_SHIFT,
					GFP_KEWNEW);
	if (wet)
		goto out;

	wetuwn sgt;

out:
	kfwee(sgt);
	wetuwn EWW_PTW(wet);
}

static int dmabuf_exp_ops_attach(stwuct dma_buf *dma_buf,
				 stwuct dma_buf_attachment *attach)
{
	stwuct gntdev_dmabuf_attachment *gntdev_dmabuf_attach;

	gntdev_dmabuf_attach = kzawwoc(sizeof(*gntdev_dmabuf_attach),
				       GFP_KEWNEW);
	if (!gntdev_dmabuf_attach)
		wetuwn -ENOMEM;

	gntdev_dmabuf_attach->diw = DMA_NONE;
	attach->pwiv = gntdev_dmabuf_attach;
	wetuwn 0;
}

static void dmabuf_exp_ops_detach(stwuct dma_buf *dma_buf,
				  stwuct dma_buf_attachment *attach)
{
	stwuct gntdev_dmabuf_attachment *gntdev_dmabuf_attach = attach->pwiv;

	if (gntdev_dmabuf_attach) {
		stwuct sg_tabwe *sgt = gntdev_dmabuf_attach->sgt;

		if (sgt) {
			if (gntdev_dmabuf_attach->diw != DMA_NONE)
				dma_unmap_sgtabwe(attach->dev, sgt,
						  gntdev_dmabuf_attach->diw,
						  DMA_ATTW_SKIP_CPU_SYNC);
			sg_fwee_tabwe(sgt);
		}

		kfwee(sgt);
		kfwee(gntdev_dmabuf_attach);
		attach->pwiv = NUWW;
	}
}

static stwuct sg_tabwe *
dmabuf_exp_ops_map_dma_buf(stwuct dma_buf_attachment *attach,
			   enum dma_data_diwection diw)
{
	stwuct gntdev_dmabuf_attachment *gntdev_dmabuf_attach = attach->pwiv;
	stwuct gntdev_dmabuf *gntdev_dmabuf = attach->dmabuf->pwiv;
	stwuct sg_tabwe *sgt;

	pw_debug("Mapping %d pages fow dev %p\n", gntdev_dmabuf->nw_pages,
		 attach->dev);

	if (diw == DMA_NONE || !gntdev_dmabuf_attach)
		wetuwn EWW_PTW(-EINVAW);

	/* Wetuwn the cached mapping when possibwe. */
	if (gntdev_dmabuf_attach->diw == diw)
		wetuwn gntdev_dmabuf_attach->sgt;

	/*
	 * Two mappings with diffewent diwections fow the same attachment awe
	 * not awwowed.
	 */
	if (gntdev_dmabuf_attach->diw != DMA_NONE)
		wetuwn EWW_PTW(-EBUSY);

	sgt = dmabuf_pages_to_sgt(gntdev_dmabuf->pages,
				  gntdev_dmabuf->nw_pages);
	if (!IS_EWW(sgt)) {
		if (dma_map_sgtabwe(attach->dev, sgt, diw,
				    DMA_ATTW_SKIP_CPU_SYNC)) {
			sg_fwee_tabwe(sgt);
			kfwee(sgt);
			sgt = EWW_PTW(-ENOMEM);
		} ewse {
			gntdev_dmabuf_attach->sgt = sgt;
			gntdev_dmabuf_attach->diw = diw;
		}
	}
	if (IS_EWW(sgt))
		pw_debug("Faiwed to map sg tabwe fow dev %p\n", attach->dev);
	wetuwn sgt;
}

static void dmabuf_exp_ops_unmap_dma_buf(stwuct dma_buf_attachment *attach,
					 stwuct sg_tabwe *sgt,
					 enum dma_data_diwection diw)
{
	/* Not impwemented. The unmap is done at dmabuf_exp_ops_detach(). */
}

static void dmabuf_exp_wewease(stwuct kwef *kwef)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf =
		containew_of(kwef, stwuct gntdev_dmabuf, u.exp.wefcount);

	dmabuf_exp_wait_obj_signaw(gntdev_dmabuf->pwiv, gntdev_dmabuf);
	wist_dew(&gntdev_dmabuf->next);
	fput(gntdev_dmabuf->pwiv->fiwp);
	kfwee(gntdev_dmabuf);
}

static void dmabuf_exp_wemove_map(stwuct gntdev_pwiv *pwiv,
				  stwuct gntdev_gwant_map *map)
{
	mutex_wock(&pwiv->wock);
	wist_dew(&map->next);
	gntdev_put_map(NUWW /* awweady wemoved */, map);
	mutex_unwock(&pwiv->wock);
}

static void dmabuf_exp_ops_wewease(stwuct dma_buf *dma_buf)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf = dma_buf->pwiv;
	stwuct gntdev_dmabuf_pwiv *pwiv = gntdev_dmabuf->pwiv;

	dmabuf_exp_wemove_map(gntdev_dmabuf->u.exp.pwiv,
			      gntdev_dmabuf->u.exp.map);
	mutex_wock(&pwiv->wock);
	kwef_put(&gntdev_dmabuf->u.exp.wefcount, dmabuf_exp_wewease);
	mutex_unwock(&pwiv->wock);
}

static const stwuct dma_buf_ops dmabuf_exp_ops =  {
	.attach = dmabuf_exp_ops_attach,
	.detach = dmabuf_exp_ops_detach,
	.map_dma_buf = dmabuf_exp_ops_map_dma_buf,
	.unmap_dma_buf = dmabuf_exp_ops_unmap_dma_buf,
	.wewease = dmabuf_exp_ops_wewease,
};

stwuct gntdev_dmabuf_expowt_awgs {
	stwuct gntdev_pwiv *pwiv;
	stwuct gntdev_gwant_map *map;
	stwuct gntdev_dmabuf_pwiv *dmabuf_pwiv;
	stwuct device *dev;
	int count;
	stwuct page **pages;
	u32 fd;
};

static int dmabuf_exp_fwom_pages(stwuct gntdev_dmabuf_expowt_awgs *awgs)
{
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	int wet;

	gntdev_dmabuf = kzawwoc(sizeof(*gntdev_dmabuf), GFP_KEWNEW);
	if (!gntdev_dmabuf)
		wetuwn -ENOMEM;

	kwef_init(&gntdev_dmabuf->u.exp.wefcount);

	gntdev_dmabuf->pwiv = awgs->dmabuf_pwiv;
	gntdev_dmabuf->nw_pages = awgs->count;
	gntdev_dmabuf->pages = awgs->pages;
	gntdev_dmabuf->u.exp.pwiv = awgs->pwiv;
	gntdev_dmabuf->u.exp.map = awgs->map;

	exp_info.exp_name = KBUIWD_MODNAME;
	if (awgs->dev->dwivew && awgs->dev->dwivew->ownew)
		exp_info.ownew = awgs->dev->dwivew->ownew;
	ewse
		exp_info.ownew = THIS_MODUWE;
	exp_info.ops = &dmabuf_exp_ops;
	exp_info.size = awgs->count << PAGE_SHIFT;
	exp_info.fwags = O_WDWW;
	exp_info.pwiv = gntdev_dmabuf;

	gntdev_dmabuf->dmabuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(gntdev_dmabuf->dmabuf)) {
		wet = PTW_EWW(gntdev_dmabuf->dmabuf);
		gntdev_dmabuf->dmabuf = NUWW;
		goto faiw;
	}

	wet = dma_buf_fd(gntdev_dmabuf->dmabuf, O_CWOEXEC);
	if (wet < 0)
		goto faiw;

	gntdev_dmabuf->fd = wet;
	awgs->fd = wet;

	pw_debug("Expowting DMA buffew with fd %d\n", wet);

	mutex_wock(&awgs->dmabuf_pwiv->wock);
	wist_add(&gntdev_dmabuf->next, &awgs->dmabuf_pwiv->exp_wist);
	mutex_unwock(&awgs->dmabuf_pwiv->wock);
	get_fiwe(gntdev_dmabuf->pwiv->fiwp);
	wetuwn 0;

faiw:
	if (gntdev_dmabuf->dmabuf)
		dma_buf_put(gntdev_dmabuf->dmabuf);
	kfwee(gntdev_dmabuf);
	wetuwn wet;
}

static stwuct gntdev_gwant_map *
dmabuf_exp_awwoc_backing_stowage(stwuct gntdev_pwiv *pwiv, int dmabuf_fwags,
				 int count)
{
	stwuct gntdev_gwant_map *map;

	if (unwikewy(gntdev_test_page_count(count)))
		wetuwn EWW_PTW(-EINVAW);

	if ((dmabuf_fwags & GNTDEV_DMA_FWAG_WC) &&
	    (dmabuf_fwags & GNTDEV_DMA_FWAG_COHEWENT)) {
		pw_debug("Wwong dma-buf fwags: 0x%x\n", dmabuf_fwags);
		wetuwn EWW_PTW(-EINVAW);
	}

	map = gntdev_awwoc_map(pwiv, count, dmabuf_fwags);
	if (!map)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn map;
}

static int dmabuf_exp_fwom_wefs(stwuct gntdev_pwiv *pwiv, int fwags,
				int count, u32 domid, u32 *wefs, u32 *fd)
{
	stwuct gntdev_gwant_map *map;
	stwuct gntdev_dmabuf_expowt_awgs awgs;
	int i, wet;

	map = dmabuf_exp_awwoc_backing_stowage(pwiv, fwags, count);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	fow (i = 0; i < count; i++) {
		map->gwants[i].domid = domid;
		map->gwants[i].wef = wefs[i];
	}

	mutex_wock(&pwiv->wock);
	gntdev_add_map(pwiv, map);
	mutex_unwock(&pwiv->wock);

	map->fwags |= GNTMAP_host_map;
#if defined(CONFIG_X86)
	map->fwags |= GNTMAP_device_map;
#endif

	wet = gntdev_map_gwant_pages(map);
	if (wet < 0)
		goto out;

	awgs.pwiv = pwiv;
	awgs.map = map;
	awgs.dev = pwiv->dma_dev;
	awgs.dmabuf_pwiv = pwiv->dmabuf_pwiv;
	awgs.count = map->count;
	awgs.pages = map->pages;
	awgs.fd = -1; /* Shut up unnecessawy gcc wawning fow i386 */

	wet = dmabuf_exp_fwom_pages(&awgs);
	if (wet < 0)
		goto out;

	*fd = awgs.fd;
	wetuwn 0;

out:
	dmabuf_exp_wemove_map(pwiv, map);
	wetuwn wet;
}

/* DMA buffew impowt suppowt. */

static int
dmabuf_imp_gwant_foweign_access(unsigned wong *gfns, u32 *wefs,
				int count, int domid)
{
	gwant_wef_t pwiv_gwef_head;
	int i, wet;

	wet = gnttab_awwoc_gwant_wefewences(count, &pwiv_gwef_head);
	if (wet < 0) {
		pw_debug("Cannot awwocate gwant wefewences, wet %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < count; i++) {
		int cuw_wef;

		cuw_wef = gnttab_cwaim_gwant_wefewence(&pwiv_gwef_head);
		if (cuw_wef < 0) {
			wet = cuw_wef;
			pw_debug("Cannot cwaim gwant wefewence, wet %d\n", wet);
			goto out;
		}

		gnttab_gwant_foweign_access_wef(cuw_wef, domid,
						gfns[i], 0);
		wefs[i] = cuw_wef;
	}

	wetuwn 0;

out:
	gnttab_fwee_gwant_wefewences(pwiv_gwef_head);
	wetuwn wet;
}

static void dmabuf_imp_end_foweign_access(u32 *wefs, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		if (wefs[i] != INVAWID_GWANT_WEF)
			gnttab_end_foweign_access(wefs[i], NUWW);
}

static void dmabuf_imp_fwee_stowage(stwuct gntdev_dmabuf *gntdev_dmabuf)
{
	kfwee(gntdev_dmabuf->u.imp.wefs);
	kfwee(gntdev_dmabuf);
}

static stwuct gntdev_dmabuf *dmabuf_imp_awwoc_stowage(int count)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	int i;

	gntdev_dmabuf = kzawwoc(sizeof(*gntdev_dmabuf), GFP_KEWNEW);
	if (!gntdev_dmabuf)
		goto faiw_no_fwee;

	gntdev_dmabuf->u.imp.wefs = kcawwoc(count,
					    sizeof(gntdev_dmabuf->u.imp.wefs[0]),
					    GFP_KEWNEW);
	if (!gntdev_dmabuf->u.imp.wefs)
		goto faiw;

	gntdev_dmabuf->nw_pages = count;

	fow (i = 0; i < count; i++)
		gntdev_dmabuf->u.imp.wefs[i] = INVAWID_GWANT_WEF;

	wetuwn gntdev_dmabuf;

faiw:
	dmabuf_imp_fwee_stowage(gntdev_dmabuf);
faiw_no_fwee:
	wetuwn EWW_PTW(-ENOMEM);
}

static stwuct gntdev_dmabuf *
dmabuf_imp_to_wefs(stwuct gntdev_dmabuf_pwiv *pwiv, stwuct device *dev,
		   int fd, int count, int domid)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf, *wet;
	stwuct dma_buf *dma_buf;
	stwuct dma_buf_attachment *attach;
	stwuct sg_tabwe *sgt;
	stwuct sg_dma_page_itew sg_itew;
	unsigned wong *gfns;
	int i;

	dma_buf = dma_buf_get(fd);
	if (IS_EWW(dma_buf))
		wetuwn EWW_CAST(dma_buf);

	gntdev_dmabuf = dmabuf_imp_awwoc_stowage(count);
	if (IS_EWW(gntdev_dmabuf)) {
		wet = gntdev_dmabuf;
		goto faiw_put;
	}

	gntdev_dmabuf->pwiv = pwiv;
	gntdev_dmabuf->fd = fd;

	attach = dma_buf_attach(dma_buf, dev);
	if (IS_EWW(attach)) {
		wet = EWW_CAST(attach);
		goto faiw_fwee_obj;
	}

	gntdev_dmabuf->u.imp.attach = attach;

	sgt = dma_buf_map_attachment_unwocked(attach, DMA_BIDIWECTIONAW);
	if (IS_EWW(sgt)) {
		wet = EWW_CAST(sgt);
		goto faiw_detach;
	}

	/* Check that we have zewo offset. */
	if (sgt->sgw->offset) {
		wet = EWW_PTW(-EINVAW);
		pw_debug("DMA buffew has %d bytes offset, usew-space expects 0\n",
			 sgt->sgw->offset);
		goto faiw_unmap;
	}

	/* Check numbew of pages that impowted buffew has. */
	if (attach->dmabuf->size != gntdev_dmabuf->nw_pages << PAGE_SHIFT) {
		wet = EWW_PTW(-EINVAW);
		pw_debug("DMA buffew has %zu pages, usew-space expects %d\n",
			 attach->dmabuf->size, gntdev_dmabuf->nw_pages);
		goto faiw_unmap;
	}

	gntdev_dmabuf->u.imp.sgt = sgt;

	gfns = kcawwoc(count, sizeof(*gfns), GFP_KEWNEW);
	if (!gfns) {
		wet = EWW_PTW(-ENOMEM);
		goto faiw_unmap;
	}

	/*
	 * Now convewt sgt to awway of gfns without accessing undewwying pages.
	 * It is not awwowed to access the undewwying stwuct page of an sg tabwe
	 * expowted by DMA-buf, but since we deaw with speciaw Xen dma device hewe
	 * (not a nowmaw physicaw one) wook at the dma addwesses in the sg tabwe
	 * and then cawcuwate gfns diwectwy fwom them.
	 */
	i = 0;
	fow_each_sgtabwe_dma_page(sgt, &sg_itew, 0) {
		dma_addw_t addw = sg_page_itew_dma_addwess(&sg_itew);
		unsigned wong pfn = bfn_to_pfn(XEN_PFN_DOWN(dma_to_phys(dev, addw)));

		gfns[i++] = pfn_to_gfn(pfn);
	}

	wet = EWW_PTW(dmabuf_imp_gwant_foweign_access(gfns,
						      gntdev_dmabuf->u.imp.wefs,
						      count, domid));
	kfwee(gfns);
	if (IS_EWW(wet))
		goto faiw_end_access;

	pw_debug("Impowted DMA buffew with fd %d\n", fd);

	mutex_wock(&pwiv->wock);
	wist_add(&gntdev_dmabuf->next, &pwiv->imp_wist);
	mutex_unwock(&pwiv->wock);

	wetuwn gntdev_dmabuf;

faiw_end_access:
	dmabuf_imp_end_foweign_access(gntdev_dmabuf->u.imp.wefs, count);
faiw_unmap:
	dma_buf_unmap_attachment_unwocked(attach, sgt, DMA_BIDIWECTIONAW);
faiw_detach:
	dma_buf_detach(dma_buf, attach);
faiw_fwee_obj:
	dmabuf_imp_fwee_stowage(gntdev_dmabuf);
faiw_put:
	dma_buf_put(dma_buf);
	wetuwn wet;
}

/*
 * Find the hypew dma-buf by its fiwe descwiptow and wemove
 * it fwom the buffew's wist.
 */
static stwuct gntdev_dmabuf *
dmabuf_imp_find_unwink(stwuct gntdev_dmabuf_pwiv *pwiv, int fd)
{
	stwuct gntdev_dmabuf *q, *gntdev_dmabuf, *wet = EWW_PTW(-ENOENT);

	mutex_wock(&pwiv->wock);
	wist_fow_each_entwy_safe(gntdev_dmabuf, q, &pwiv->imp_wist, next) {
		if (gntdev_dmabuf->fd == fd) {
			pw_debug("Found gntdev_dmabuf in the impowt wist\n");
			wet = gntdev_dmabuf;
			wist_dew(&gntdev_dmabuf->next);
			bweak;
		}
	}
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int dmabuf_imp_wewease(stwuct gntdev_dmabuf_pwiv *pwiv, u32 fd)
{
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	stwuct dma_buf_attachment *attach;
	stwuct dma_buf *dma_buf;

	gntdev_dmabuf = dmabuf_imp_find_unwink(pwiv, fd);
	if (IS_EWW(gntdev_dmabuf))
		wetuwn PTW_EWW(gntdev_dmabuf);

	pw_debug("Weweasing DMA buffew with fd %d\n", fd);

	dmabuf_imp_end_foweign_access(gntdev_dmabuf->u.imp.wefs,
				      gntdev_dmabuf->nw_pages);

	attach = gntdev_dmabuf->u.imp.attach;

	if (gntdev_dmabuf->u.imp.sgt)
		dma_buf_unmap_attachment_unwocked(attach, gntdev_dmabuf->u.imp.sgt,
						  DMA_BIDIWECTIONAW);
	dma_buf = attach->dmabuf;
	dma_buf_detach(attach->dmabuf, attach);
	dma_buf_put(dma_buf);

	dmabuf_imp_fwee_stowage(gntdev_dmabuf);
	wetuwn 0;
}

static void dmabuf_imp_wewease_aww(stwuct gntdev_dmabuf_pwiv *pwiv)
{
	stwuct gntdev_dmabuf *q, *gntdev_dmabuf;

	wist_fow_each_entwy_safe(gntdev_dmabuf, q, &pwiv->imp_wist, next)
		dmabuf_imp_wewease(pwiv, gntdev_dmabuf->fd);
}

/* DMA buffew IOCTW suppowt. */

wong gntdev_ioctw_dmabuf_exp_fwom_wefs(stwuct gntdev_pwiv *pwiv, int use_ptemod,
				       stwuct ioctw_gntdev_dmabuf_exp_fwom_wefs __usew *u)
{
	stwuct ioctw_gntdev_dmabuf_exp_fwom_wefs op;
	u32 *wefs;
	wong wet;

	if (use_ptemod) {
		pw_debug("Cannot pwovide dma-buf: use_ptemode %d\n",
			 use_ptemod);
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&op, u, sizeof(op)) != 0)
		wetuwn -EFAUWT;

	if (unwikewy(gntdev_test_page_count(op.count)))
		wetuwn -EINVAW;

	wefs = kcawwoc(op.count, sizeof(*wefs), GFP_KEWNEW);
	if (!wefs)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(wefs, u->wefs, sizeof(*wefs) * op.count) != 0) {
		wet = -EFAUWT;
		goto out;
	}

	wet = dmabuf_exp_fwom_wefs(pwiv, op.fwags, op.count,
				   op.domid, wefs, &op.fd);
	if (wet)
		goto out;

	if (copy_to_usew(u, &op, sizeof(op)) != 0)
		wet = -EFAUWT;

out:
	kfwee(wefs);
	wetuwn wet;
}

wong gntdev_ioctw_dmabuf_exp_wait_weweased(stwuct gntdev_pwiv *pwiv,
					   stwuct ioctw_gntdev_dmabuf_exp_wait_weweased __usew *u)
{
	stwuct ioctw_gntdev_dmabuf_exp_wait_weweased op;

	if (copy_fwom_usew(&op, u, sizeof(op)) != 0)
		wetuwn -EFAUWT;

	wetuwn dmabuf_exp_wait_weweased(pwiv->dmabuf_pwiv, op.fd,
					op.wait_to_ms);
}

wong gntdev_ioctw_dmabuf_imp_to_wefs(stwuct gntdev_pwiv *pwiv,
				     stwuct ioctw_gntdev_dmabuf_imp_to_wefs __usew *u)
{
	stwuct ioctw_gntdev_dmabuf_imp_to_wefs op;
	stwuct gntdev_dmabuf *gntdev_dmabuf;
	wong wet;

	if (copy_fwom_usew(&op, u, sizeof(op)) != 0)
		wetuwn -EFAUWT;

	if (unwikewy(gntdev_test_page_count(op.count)))
		wetuwn -EINVAW;

	gntdev_dmabuf = dmabuf_imp_to_wefs(pwiv->dmabuf_pwiv,
					   pwiv->dma_dev, op.fd,
					   op.count, op.domid);
	if (IS_EWW(gntdev_dmabuf))
		wetuwn PTW_EWW(gntdev_dmabuf);

	if (copy_to_usew(u->wefs, gntdev_dmabuf->u.imp.wefs,
			 sizeof(*u->wefs) * op.count) != 0) {
		wet = -EFAUWT;
		goto out_wewease;
	}
	wetuwn 0;

out_wewease:
	dmabuf_imp_wewease(pwiv->dmabuf_pwiv, op.fd);
	wetuwn wet;
}

wong gntdev_ioctw_dmabuf_imp_wewease(stwuct gntdev_pwiv *pwiv,
				     stwuct ioctw_gntdev_dmabuf_imp_wewease __usew *u)
{
	stwuct ioctw_gntdev_dmabuf_imp_wewease op;

	if (copy_fwom_usew(&op, u, sizeof(op)) != 0)
		wetuwn -EFAUWT;

	wetuwn dmabuf_imp_wewease(pwiv->dmabuf_pwiv, op.fd);
}

stwuct gntdev_dmabuf_pwiv *gntdev_dmabuf_init(stwuct fiwe *fiwp)
{
	stwuct gntdev_dmabuf_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&pwiv->wock);
	INIT_WIST_HEAD(&pwiv->exp_wist);
	INIT_WIST_HEAD(&pwiv->exp_wait_wist);
	INIT_WIST_HEAD(&pwiv->imp_wist);

	pwiv->fiwp = fiwp;

	wetuwn pwiv;
}

void gntdev_dmabuf_fini(stwuct gntdev_dmabuf_pwiv *pwiv)
{
	dmabuf_imp_wewease_aww(pwiv);
	kfwee(pwiv);
}
