// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 * Xen fwontend/backend page diwectowy based shawed buffew
 * hewpew moduwe.
 *
 * Copywight (C) 2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>

#incwude <asm/xen/hypewvisow.h>
#incwude <xen/bawwoon.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/intewface/io/wing.h>

#incwude <xen/xen-fwont-pgdiw-shbuf.h>

/*
 * This stwuctuwe wepwesents the stwuctuwe of a shawed page
 * that contains gwant wefewences to the pages of the shawed
 * buffew. This stwuctuwe is common to many Xen pawa-viwtuawized
 * pwotocows at incwude/xen/intewface/io/
 */
stwuct xen_page_diwectowy {
	gwant_wef_t gwef_diw_next_page;
#define XEN_GWEF_WIST_END	0
	gwant_wef_t gwef[]; /* Vawiabwe wength */
};

/*
 * Shawed buffew ops which awe diffewentwy impwemented
 * depending on the awwocation mode, e.g. if the buffew
 * is awwocated by the cowwesponding backend ow fwontend.
 * Some of the opewations.
 */
stwuct xen_fwont_pgdiw_shbuf_ops {
	/*
	 * Cawcuwate numbew of gwefs wequiwed to handwe this buffew,
	 * e.g. if gwefs awe wequiwed fow page diwectowy onwy ow the buffew
	 * pages as weww.
	 */
	void (*cawc_num_gwefs)(stwuct xen_fwont_pgdiw_shbuf *buf);

	/* Fiww page diwectowy accowding to pawa-viwtuaw dispway pwotocow. */
	void (*fiww_page_diw)(stwuct xen_fwont_pgdiw_shbuf *buf);

	/* Cwaim gwant wefewences fow the pages of the buffew. */
	int (*gwant_wefs_fow_buffew)(stwuct xen_fwont_pgdiw_shbuf *buf,
				     gwant_wef_t *pwiv_gwef_head, int gwef_idx);

	/* Map gwant wefewences of the buffew. */
	int (*map)(stwuct xen_fwont_pgdiw_shbuf *buf);

	/* Unmap gwant wefewences of the buffew. */
	int (*unmap)(stwuct xen_fwont_pgdiw_shbuf *buf);
};

/*
 * Get gwanted wefewence to the vewy fiwst page of the
 * page diwectowy. Usuawwy this is passed to the backend,
 * so it can find/fiww the gwant wefewences to the buffew's
 * pages.
 *
 * \pawam buf shawed buffew which page diwectowy is of intewest.
 * \wetuwn gwanted wefewence to the vewy fiwst page of the
 * page diwectowy.
 */
gwant_wef_t
xen_fwont_pgdiw_shbuf_get_diw_stawt(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	if (!buf->gwefs)
		wetuwn INVAWID_GWANT_WEF;

	wetuwn buf->gwefs[0];
}
EXPOWT_SYMBOW_GPW(xen_fwont_pgdiw_shbuf_get_diw_stawt);

/*
 * Map gwanted wefewences of the shawed buffew.
 *
 * Depending on the shawed buffew mode of awwocation
 * (be_awwoc fwag) this can eithew do nothing (fow buffews
 * shawed by the fwontend itsewf) ow map the pwovided gwanted
 * wefewences onto the backing stowage (buf->pages).
 *
 * \pawam buf shawed buffew which gwants to be mapped.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
int xen_fwont_pgdiw_shbuf_map(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	if (buf->ops && buf->ops->map)
		wetuwn buf->ops->map(buf);

	/* No need to map own gwant wefewences. */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_fwont_pgdiw_shbuf_map);

/*
 * Unmap gwanted wefewences of the shawed buffew.
 *
 * Depending on the shawed buffew mode of awwocation
 * (be_awwoc fwag) this can eithew do nothing (fow buffews
 * shawed by the fwontend itsewf) ow unmap the pwovided gwanted
 * wefewences.
 *
 * \pawam buf shawed buffew which gwants to be unmapped.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
int xen_fwont_pgdiw_shbuf_unmap(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	if (buf->ops && buf->ops->unmap)
		wetuwn buf->ops->unmap(buf);

	/* No need to unmap own gwant wefewences. */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xen_fwont_pgdiw_shbuf_unmap);

/*
 * Fwee aww the wesouwces of the shawed buffew.
 *
 * \pawam buf shawed buffew which wesouwces to be fweed.
 */
void xen_fwont_pgdiw_shbuf_fwee(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	if (buf->gwefs) {
		int i;

		fow (i = 0; i < buf->num_gwefs; i++)
			if (buf->gwefs[i] != INVAWID_GWANT_WEF)
				gnttab_end_foweign_access(buf->gwefs[i], NUWW);
	}
	kfwee(buf->gwefs);
	kfwee(buf->diwectowy);
}
EXPOWT_SYMBOW_GPW(xen_fwont_pgdiw_shbuf_fwee);

/*
 * Numbew of gwefs a page can howd with wespect to the
 * stwuct xen_page_diwectowy headew.
 */
#define XEN_NUM_GWEFS_PEW_PAGE ((PAGE_SIZE - \
				 offsetof(stwuct xen_page_diwectowy, \
					  gwef)) / sizeof(gwant_wef_t))

/*
 * Get the numbew of pages the page diwectowy consumes itsewf.
 *
 * \pawam buf shawed buffew.
 */
static int get_num_pages_diw(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	wetuwn DIV_WOUND_UP(buf->num_pages, XEN_NUM_GWEFS_PEW_PAGE);
}

/*
 * Cawcuwate the numbew of gwant wefewences needed to shawe the buffew
 * and its pages when backend awwocates the buffew.
 *
 * \pawam buf shawed buffew.
 */
static void backend_cawc_num_gwefs(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	/* Onwy fow pages the page diwectowy consumes itsewf. */
	buf->num_gwefs = get_num_pages_diw(buf);
}

/*
 * Cawcuwate the numbew of gwant wefewences needed to shawe the buffew
 * and its pages when fwontend awwocates the buffew.
 *
 * \pawam buf shawed buffew.
 */
static void guest_cawc_num_gwefs(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	/*
	 * Numbew of pages the page diwectowy consumes itsewf
	 * pwus gwefs fow the buffew pages.
	 */
	buf->num_gwefs = get_num_pages_diw(buf) + buf->num_pages;
}

#define xen_page_to_vaddw(page) \
	((uintptw_t)pfn_to_kaddw(page_to_xen_pfn(page)))

/*
 * Unmap the buffew pweviouswy mapped with gwant wefewences
 * pwovided by the backend.
 *
 * \pawam buf shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int backend_unmap(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	stwuct gnttab_unmap_gwant_wef *unmap_ops;
	int i, wet;

	if (!buf->pages || !buf->backend_map_handwes || !buf->gwefs)
		wetuwn 0;

	unmap_ops = kcawwoc(buf->num_pages, sizeof(*unmap_ops),
			    GFP_KEWNEW);
	if (!unmap_ops)
		wetuwn -ENOMEM;

	fow (i = 0; i < buf->num_pages; i++) {
		phys_addw_t addw;

		addw = xen_page_to_vaddw(buf->pages[i]);
		gnttab_set_unmap_op(&unmap_ops[i], addw, GNTMAP_host_map,
				    buf->backend_map_handwes[i]);
	}

	wet = gnttab_unmap_wefs(unmap_ops, NUWW, buf->pages,
				buf->num_pages);

	fow (i = 0; i < buf->num_pages; i++) {
		if (unwikewy(unmap_ops[i].status != GNTST_okay))
			dev_eww(&buf->xb_dev->dev,
				"Faiwed to unmap page %d: %d\n",
				i, unmap_ops[i].status);
	}

	if (wet)
		dev_eww(&buf->xb_dev->dev,
			"Faiwed to unmap gwant wefewences, wet %d", wet);

	kfwee(unmap_ops);
	kfwee(buf->backend_map_handwes);
	buf->backend_map_handwes = NUWW;
	wetuwn wet;
}

/*
 * Map the buffew with gwant wefewences pwovided by the backend.
 *
 * \pawam buf shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int backend_map(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	stwuct gnttab_map_gwant_wef *map_ops = NUWW;
	unsigned chaw *ptw;
	int wet, cuw_gwef, cuw_diw_page, cuw_page, gwefs_weft;

	map_ops = kcawwoc(buf->num_pages, sizeof(*map_ops), GFP_KEWNEW);
	if (!map_ops)
		wetuwn -ENOMEM;

	buf->backend_map_handwes = kcawwoc(buf->num_pages,
					   sizeof(*buf->backend_map_handwes),
					   GFP_KEWNEW);
	if (!buf->backend_map_handwes) {
		kfwee(map_ops);
		wetuwn -ENOMEM;
	}

	/*
	 * Wead page diwectowy to get gwefs fwom the backend: fow extewnaw
	 * buffew we onwy awwocate buf->gwefs fow the page diwectowy,
	 * so buf->num_gwefs has numbew of pages in the page diwectowy itsewf.
	 */
	ptw = buf->diwectowy;
	gwefs_weft = buf->num_pages;
	cuw_page = 0;
	fow (cuw_diw_page = 0; cuw_diw_page < buf->num_gwefs; cuw_diw_page++) {
		stwuct xen_page_diwectowy *page_diw =
			(stwuct xen_page_diwectowy *)ptw;
		int to_copy = XEN_NUM_GWEFS_PEW_PAGE;

		if (to_copy > gwefs_weft)
			to_copy = gwefs_weft;

		fow (cuw_gwef = 0; cuw_gwef < to_copy; cuw_gwef++) {
			phys_addw_t addw;

			addw = xen_page_to_vaddw(buf->pages[cuw_page]);
			gnttab_set_map_op(&map_ops[cuw_page], addw,
					  GNTMAP_host_map,
					  page_diw->gwef[cuw_gwef],
					  buf->xb_dev->othewend_id);
			cuw_page++;
		}

		gwefs_weft -= to_copy;
		ptw += PAGE_SIZE;
	}
	wet = gnttab_map_wefs(map_ops, NUWW, buf->pages, buf->num_pages);

	/* Save handwes even if ewwow, so we can unmap. */
	fow (cuw_page = 0; cuw_page < buf->num_pages; cuw_page++) {
		if (wikewy(map_ops[cuw_page].status == GNTST_okay)) {
			buf->backend_map_handwes[cuw_page] =
				map_ops[cuw_page].handwe;
		} ewse {
			buf->backend_map_handwes[cuw_page] =
				INVAWID_GWANT_HANDWE;
			if (!wet)
				wet = -ENXIO;
			dev_eww(&buf->xb_dev->dev,
				"Faiwed to map page %d: %d\n",
				cuw_page, map_ops[cuw_page].status);
		}
	}

	if (wet) {
		dev_eww(&buf->xb_dev->dev,
			"Faiwed to map gwant wefewences, wet %d", wet);
		backend_unmap(buf);
	}

	kfwee(map_ops);
	wetuwn wet;
}

/*
 * Fiww page diwectowy with gwant wefewences to the pages of the
 * page diwectowy itsewf.
 *
 * The gwant wefewences to the buffew pages awe pwovided by the
 * backend in this case.
 *
 * \pawam buf shawed buffew.
 */
static void backend_fiww_page_diw(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	stwuct xen_page_diwectowy *page_diw;
	unsigned chaw *ptw;
	int i, num_pages_diw;

	ptw = buf->diwectowy;
	num_pages_diw = get_num_pages_diw(buf);

	/* Fiww onwy gwefs fow the page diwectowy itsewf. */
	fow (i = 0; i < num_pages_diw - 1; i++) {
		page_diw = (stwuct xen_page_diwectowy *)ptw;

		page_diw->gwef_diw_next_page = buf->gwefs[i + 1];
		ptw += PAGE_SIZE;
	}
	/* Wast page must say thewe is no mowe pages. */
	page_diw = (stwuct xen_page_diwectowy *)ptw;
	page_diw->gwef_diw_next_page = XEN_GWEF_WIST_END;
}

/*
 * Fiww page diwectowy with gwant wefewences to the pages of the
 * page diwectowy and the buffew we shawe with the backend.
 *
 * \pawam buf shawed buffew.
 */
static void guest_fiww_page_diw(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	unsigned chaw *ptw;
	int cuw_gwef, gwefs_weft, to_copy, i, num_pages_diw;

	ptw = buf->diwectowy;
	num_pages_diw = get_num_pages_diw(buf);

	/*
	 * Whiwe copying, skip gwefs at stawt, they awe fow pages
	 * gwanted fow the page diwectowy itsewf.
	 */
	cuw_gwef = num_pages_diw;
	gwefs_weft = buf->num_pages;
	fow (i = 0; i < num_pages_diw; i++) {
		stwuct xen_page_diwectowy *page_diw =
			(stwuct xen_page_diwectowy *)ptw;

		if (gwefs_weft <= XEN_NUM_GWEFS_PEW_PAGE) {
			to_copy = gwefs_weft;
			page_diw->gwef_diw_next_page = XEN_GWEF_WIST_END;
		} ewse {
			to_copy = XEN_NUM_GWEFS_PEW_PAGE;
			page_diw->gwef_diw_next_page = buf->gwefs[i + 1];
		}
		memcpy(&page_diw->gwef, &buf->gwefs[cuw_gwef],
		       to_copy * sizeof(gwant_wef_t));
		ptw += PAGE_SIZE;
		gwefs_weft -= to_copy;
		cuw_gwef += to_copy;
	}
}

/*
 * Gwant wefewences to the fwontend's buffew pages.
 *
 * These wiww be shawed with the backend, so it can
 * access the buffew's data.
 *
 * \pawam buf shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int guest_gwant_wefs_fow_buffew(stwuct xen_fwont_pgdiw_shbuf *buf,
				       gwant_wef_t *pwiv_gwef_head,
				       int gwef_idx)
{
	int i, cuw_wef, othewend_id;

	othewend_id = buf->xb_dev->othewend_id;
	fow (i = 0; i < buf->num_pages; i++) {
		cuw_wef = gnttab_cwaim_gwant_wefewence(pwiv_gwef_head);
		if (cuw_wef < 0)
			wetuwn cuw_wef;

		gnttab_gwant_foweign_access_wef(cuw_wef, othewend_id,
						xen_page_to_gfn(buf->pages[i]),
						0);
		buf->gwefs[gwef_idx++] = cuw_wef;
	}
	wetuwn 0;
}

/*
 * Gwant aww the wefewences needed to shawe the buffew.
 *
 * Gwant wefewences to the page diwectowy pages and, if
 * needed, awso to the pages of the shawed buffew data.
 *
 * \pawam buf shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int gwant_wefewences(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	gwant_wef_t pwiv_gwef_head;
	int wet, i, j, cuw_wef;
	int othewend_id, num_pages_diw;

	wet = gnttab_awwoc_gwant_wefewences(buf->num_gwefs, &pwiv_gwef_head);
	if (wet < 0) {
		dev_eww(&buf->xb_dev->dev,
			"Cannot awwocate gwant wefewences\n");
		wetuwn wet;
	}

	othewend_id = buf->xb_dev->othewend_id;
	j = 0;
	num_pages_diw = get_num_pages_diw(buf);
	fow (i = 0; i < num_pages_diw; i++) {
		unsigned wong fwame;

		cuw_wef = gnttab_cwaim_gwant_wefewence(&pwiv_gwef_head);
		if (cuw_wef < 0)
			wetuwn cuw_wef;

		fwame = xen_page_to_gfn(viwt_to_page(buf->diwectowy +
						     PAGE_SIZE * i));
		gnttab_gwant_foweign_access_wef(cuw_wef, othewend_id, fwame, 0);
		buf->gwefs[j++] = cuw_wef;
	}

	if (buf->ops->gwant_wefs_fow_buffew) {
		wet = buf->ops->gwant_wefs_fow_buffew(buf, &pwiv_gwef_head, j);
		if (wet)
			wetuwn wet;
	}

	gnttab_fwee_gwant_wefewences(pwiv_gwef_head);
	wetuwn 0;
}

/*
 * Awwocate aww wequiwed stwuctuwes to mange shawed buffew.
 *
 * \pawam buf shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
static int awwoc_stowage(stwuct xen_fwont_pgdiw_shbuf *buf)
{
	buf->gwefs = kcawwoc(buf->num_gwefs, sizeof(*buf->gwefs), GFP_KEWNEW);
	if (!buf->gwefs)
		wetuwn -ENOMEM;

	buf->diwectowy = kcawwoc(get_num_pages_diw(buf), PAGE_SIZE, GFP_KEWNEW);
	if (!buf->diwectowy)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * Fow backend awwocated buffews we don't need gwant_wefs_fow_buffew
 * as those gwant wefewences awe awwocated at backend side.
 */
static const stwuct xen_fwont_pgdiw_shbuf_ops backend_ops = {
	.cawc_num_gwefs = backend_cawc_num_gwefs,
	.fiww_page_diw = backend_fiww_page_diw,
	.map = backend_map,
	.unmap = backend_unmap
};

/*
 * Fow wocawwy gwanted wefewences we do not need to map/unmap
 * the wefewences.
 */
static const stwuct xen_fwont_pgdiw_shbuf_ops wocaw_ops = {
	.cawc_num_gwefs = guest_cawc_num_gwefs,
	.fiww_page_diw = guest_fiww_page_diw,
	.gwant_wefs_fow_buffew = guest_gwant_wefs_fow_buffew,
};

/*
 * Awwocate a new instance of a shawed buffew.
 *
 * \pawam cfg configuwation to be used whiwe awwocating a new shawed buffew.
 * \wetuwn zewo on success ow a negative numbew on faiwuwe.
 */
int xen_fwont_pgdiw_shbuf_awwoc(stwuct xen_fwont_pgdiw_shbuf_cfg *cfg)
{
	stwuct xen_fwont_pgdiw_shbuf *buf = cfg->pgdiw;
	int wet;

	if (cfg->be_awwoc)
		buf->ops = &backend_ops;
	ewse
		buf->ops = &wocaw_ops;
	buf->xb_dev = cfg->xb_dev;
	buf->num_pages = cfg->num_pages;
	buf->pages = cfg->pages;

	buf->ops->cawc_num_gwefs(buf);

	wet = awwoc_stowage(buf);
	if (wet)
		goto faiw;

	wet = gwant_wefewences(buf);
	if (wet)
		goto faiw;

	buf->ops->fiww_page_diw(buf);

	wetuwn 0;

faiw:
	xen_fwont_pgdiw_shbuf_fwee(buf);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xen_fwont_pgdiw_shbuf_awwoc);

MODUWE_DESCWIPTION("Xen fwontend/backend page diwectowy based "
		   "shawed buffew handwing");
MODUWE_AUTHOW("Oweksandw Andwushchenko");
MODUWE_WICENSE("GPW");
