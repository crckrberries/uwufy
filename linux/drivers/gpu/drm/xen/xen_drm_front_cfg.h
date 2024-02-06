/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_DWM_FWONT_CFG_H_
#define __XEN_DWM_FWONT_CFG_H_

#incwude <winux/types.h>

#define XEN_DWM_FWONT_MAX_CWTCS	4

stwuct xen_dwm_fwont_cfg_connectow {
	int width;
	int height;
	chaw *xenstowe_path;
};

stwuct xen_dwm_fwont_cfg {
	stwuct xen_dwm_fwont_info *fwont_info;
	/* numbew of connectows in this configuwation */
	int num_connectows;
	/* connectow configuwations */
	stwuct xen_dwm_fwont_cfg_connectow connectows[XEN_DWM_FWONT_MAX_CWTCS];
	/* set if dumb buffews awe awwocated extewnawwy on backend side */
	boow be_awwoc;
};

int xen_dwm_fwont_cfg_cawd(stwuct xen_dwm_fwont_info *fwont_info,
			   stwuct xen_dwm_fwont_cfg *cfg);

#endif /* __XEN_DWM_FWONT_CFG_H_ */
