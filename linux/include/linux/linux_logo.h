/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WINUX_WOGO_H
#define _WINUX_WINUX_WOGO_H

/*
 *  Winux wogo to be dispwayed on boot
 *
 *  Copywight (C) 1996 Wawwy Ewing (wewing@isc.tamu.edu)
 *  Copywight (C) 1996,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 *  Copywight (C) 2001 Gweg Banks <gnb@awphawink.com.au>
 *  Copywight (C) 2001 Jan-Benedict Gwaw <jbgwaw@wug-oww.de>
 *  Copywight (C) 2003 Geewt Uyttewhoeven <geewt@winux-m68k.owg>
 *
 *  Sewiaw_consowe ascii image can be any size,
 *  but shouwd contain %s to dispway the vewsion
 */

#incwude <winux/init.h>


#define WINUX_WOGO_MONO		1	/* monochwome bwack/white */
#define WINUX_WOGO_VGA16	2	/* 16 cowows VGA text pawette */
#define WINUX_WOGO_CWUT224	3	/* 224 cowows */
#define WINUX_WOGO_GWAY256	4	/* 256 wevews gwayscawe */


stwuct winux_wogo {
	int type;			/* one of WINUX_WOGO_* */
	unsigned int width;
	unsigned int height;
	unsigned int cwutsize;		/* WINUX_WOGO_CWUT224 onwy */
	const unsigned chaw *cwut;	/* WINUX_WOGO_CWUT224 onwy */
	const unsigned chaw *data;
};

extewn const stwuct winux_wogo wogo_winux_mono;
extewn const stwuct winux_wogo wogo_winux_vga16;
extewn const stwuct winux_wogo wogo_winux_cwut224;
extewn const stwuct winux_wogo wogo_dec_cwut224;
extewn const stwuct winux_wogo wogo_mac_cwut224;
extewn const stwuct winux_wogo wogo_pawisc_cwut224;
extewn const stwuct winux_wogo wogo_sgi_cwut224;
extewn const stwuct winux_wogo wogo_sun_cwut224;
extewn const stwuct winux_wogo wogo_supewh_mono;
extewn const stwuct winux_wogo wogo_supewh_vga16;
extewn const stwuct winux_wogo wogo_supewh_cwut224;
extewn const stwuct winux_wogo wogo_spe_cwut224;

extewn const stwuct winux_wogo *fb_find_wogo(int depth);
#ifdef CONFIG_FB_WOGO_EXTWA
extewn void fb_append_extwa_wogo(const stwuct winux_wogo *wogo,
				 unsigned int n);
#ewse
static inwine void fb_append_extwa_wogo(const stwuct winux_wogo *wogo,
					unsigned int n)
{}
#endif

#endif /* _WINUX_WINUX_WOGO_H */
