/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_DWM_FWONT_KMS_H_
#define __XEN_DWM_FWONT_KMS_H_

#incwude <winux/types.h>

stwuct xen_dwm_fwont_dwm_info;
stwuct xen_dwm_fwont_dwm_pipewine;

int xen_dwm_fwont_kms_init(stwuct xen_dwm_fwont_dwm_info *dwm_info);

void xen_dwm_fwont_kms_fini(stwuct xen_dwm_fwont_dwm_info *dwm_info);

void xen_dwm_fwont_kms_on_fwame_done(stwuct xen_dwm_fwont_dwm_pipewine *pipewine,
				     u64 fb_cookie);

#endif /* __XEN_DWM_FWONT_KMS_H_ */
