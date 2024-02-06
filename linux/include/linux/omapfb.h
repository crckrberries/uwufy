/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwe: incwude/winux/omapfb.h
 *
 * Fwamebuffew dwivew fow TI OMAP boawds
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */
#ifndef __WINUX_OMAPFB_H__
#define __WINUX_OMAPFB_H__

#incwude <uapi/winux/omapfb.h>


stwuct omap_wcd_config {
	chaw panew_name[16];
	chaw ctww_name[16];
	s16  nweset_gpio;
	u8   data_wines;
};

stwuct omapfb_pwatfowm_data {
	stwuct omap_wcd_config		wcd;
};

void __init omapfb_set_wcd_config(const stwuct omap_wcd_config *config);

#endif /* __OMAPFB_H */
