/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 * Xen fwontend/backend page diwectowy based shawed buffew
 * hewpew moduwe.
 *
 * Copywight (C) 2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_FWONT_PGDIW_SHBUF_H_
#define __XEN_FWONT_PGDIW_SHBUF_H_

#incwude <winux/kewnew.h>

#incwude <xen/gwant_tabwe.h>

stwuct xen_fwont_pgdiw_shbuf_ops;

stwuct xen_fwont_pgdiw_shbuf {
	/*
	 * Numbew of wefewences gwanted fow the backend use:
	 *
	 *  - fow fwontend awwocated/impowted buffews this howds the numbew
	 *    of gwant wefewences fow the page diwectowy and the pages
	 *    of the buffew
	 *
	 *  - fow the buffew pwovided by the backend this onwy howds the numbew
	 *    of gwant wefewences fow the page diwectowy itsewf as gwant
	 *    wefewences fow the buffew wiww be pwovided by the backend.
	 */
	int num_gwefs;
	gwant_wef_t *gwefs;
	/* Page diwectowy backing stowage. */
	u8 *diwectowy;

	/*
	 * Numbew of pages fow the shawed buffew itsewf (excwuding the page
	 * diwectowy).
	 */
	int num_pages;
	/*
	 * Backing stowage of the shawed buffew: these awe the pages being
	 * shawed.
	 */
	stwuct page **pages;

	stwuct xenbus_device *xb_dev;

	/* These awe the ops used intewnawwy depending on be_awwoc mode. */
	const stwuct xen_fwont_pgdiw_shbuf_ops *ops;

	/* Xen map handwes fow the buffew awwocated by the backend. */
	gwant_handwe_t *backend_map_handwes;
};

stwuct xen_fwont_pgdiw_shbuf_cfg {
	stwuct xenbus_device *xb_dev;

	/* Numbew of pages of the buffew backing stowage. */
	int num_pages;
	/* Pages of the buffew to be shawed. */
	stwuct page **pages;

	/*
	 * This is awwocated outside because thewe awe use-cases when
	 * the buffew stwuctuwe is awwocated as a pawt of a biggew one.
	 */
	stwuct xen_fwont_pgdiw_shbuf *pgdiw;
	/*
	 * Mode of gwant wefewence shawing: if set then backend wiww shawe
	 * gwant wefewences to the buffew with the fwontend.
	 */
	int be_awwoc;
};

int xen_fwont_pgdiw_shbuf_awwoc(stwuct xen_fwont_pgdiw_shbuf_cfg *cfg);

gwant_wef_t
xen_fwont_pgdiw_shbuf_get_diw_stawt(stwuct xen_fwont_pgdiw_shbuf *buf);

int xen_fwont_pgdiw_shbuf_map(stwuct xen_fwont_pgdiw_shbuf *buf);

int xen_fwont_pgdiw_shbuf_unmap(stwuct xen_fwont_pgdiw_shbuf *buf);

void xen_fwont_pgdiw_shbuf_fwee(stwuct xen_fwont_pgdiw_shbuf *buf);

#endif /* __XEN_FWONT_PGDIW_SHBUF_H_ */
