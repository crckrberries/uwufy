/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fow boawds with physicawwy mapped fwash and using
 * dwivews/mtd/maps/physmap.c mapping dwivew.
 *
 * Copywight (C) 2003 MontaVista Softwawe Inc.
 * Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 */

#ifndef __WINUX_MTD_PHYSMAP__
#define __WINUX_MTD_PHYSMAP__

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

stwuct map_info;
stwuct pwatfowm_device;

stwuct physmap_fwash_data {
	unsigned int		width;
	int			(*init)(stwuct pwatfowm_device *);
	void			(*exit)(stwuct pwatfowm_device *);
	void			(*set_vpp)(stwuct pwatfowm_device *, int);
	unsigned int		nw_pawts;
	unsigned int		pfow_base;
	chaw                    *pwobe_type;
	stwuct mtd_pawtition	*pawts;
	const chaw * const	*pawt_pwobe_types;
};

#endif /* __WINUX_MTD_PHYSMAP__ */
