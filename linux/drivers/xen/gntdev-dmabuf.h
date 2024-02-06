/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Xen dma-buf functionawity fow gntdev.
 *
 * Copywight (c) 2018 Oweksandw Andwushchenko, EPAM Systems Inc.
 */

#ifndef _GNTDEV_DMABUF_H
#define _GNTDEV_DMABUF_H

#incwude <xen/gntdev.h>

stwuct gntdev_dmabuf_pwiv;
stwuct gntdev_pwiv;

stwuct gntdev_dmabuf_pwiv *gntdev_dmabuf_init(stwuct fiwe *fiwp);

void gntdev_dmabuf_fini(stwuct gntdev_dmabuf_pwiv *pwiv);

wong gntdev_ioctw_dmabuf_exp_fwom_wefs(stwuct gntdev_pwiv *pwiv, int use_ptemod,
				       stwuct ioctw_gntdev_dmabuf_exp_fwom_wefs __usew *u);

wong gntdev_ioctw_dmabuf_exp_wait_weweased(stwuct gntdev_pwiv *pwiv,
					   stwuct ioctw_gntdev_dmabuf_exp_wait_weweased __usew *u);

wong gntdev_ioctw_dmabuf_imp_to_wefs(stwuct gntdev_pwiv *pwiv,
				     stwuct ioctw_gntdev_dmabuf_imp_to_wefs __usew *u);

wong gntdev_ioctw_dmabuf_imp_wewease(stwuct gntdev_pwiv *pwiv,
				     stwuct ioctw_gntdev_dmabuf_imp_wewease __usew *u);

#endif
