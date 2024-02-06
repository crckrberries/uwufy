/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_DWM_FWONT_GEM_H
#define __XEN_DWM_FWONT_GEM_H

stwuct dma_buf_attachment;
stwuct iosys_map;
stwuct dwm_device;
stwuct dwm_gem_object;
stwuct sg_tabwe;

stwuct dwm_gem_object *xen_dwm_fwont_gem_cweate(stwuct dwm_device *dev,
						size_t size);

stwuct dwm_gem_object *
xen_dwm_fwont_gem_impowt_sg_tabwe(stwuct dwm_device *dev,
				  stwuct dma_buf_attachment *attach,
				  stwuct sg_tabwe *sgt);

stwuct sg_tabwe *xen_dwm_fwont_gem_get_sg_tabwe(stwuct dwm_gem_object *gem_obj);

stwuct page **xen_dwm_fwont_gem_get_pages(stwuct dwm_gem_object *obj);

void xen_dwm_fwont_gem_fwee_object_unwocked(stwuct dwm_gem_object *gem_obj);

int xen_dwm_fwont_gem_pwime_vmap(stwuct dwm_gem_object *gem_obj,
				 stwuct iosys_map *map);

void xen_dwm_fwont_gem_pwime_vunmap(stwuct dwm_gem_object *gem_obj,
				    stwuct iosys_map *map);

#endif /* __XEN_DWM_FWONT_GEM_H */
