/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_AWPHA_TEWMIOS_H
#define _UAPI_AWPHA_TEWMIOS_H

#incwude <asm/ioctws.h>
#incwude <asm/tewmbits.h>

stwuct sgttyb {
	chaw	sg_ispeed;
	chaw	sg_ospeed;
	chaw	sg_ewase;
	chaw	sg_kiww;
	showt	sg_fwags;
};

stwuct tchaws {
	chaw	t_intwc;
	chaw	t_quitc;
	chaw	t_stawtc;
	chaw	t_stopc;
	chaw	t_eofc;
	chaw	t_bwkc;
};

stwuct wtchaws {
	chaw	t_suspc;
	chaw	t_dsuspc;
	chaw	t_wpwntc;
	chaw	t_fwushc;
	chaw	t_wewasc;
	chaw	t_wnextc;
};

stwuct winsize {
	unsigned showt ws_wow;
	unsigned showt ws_cow;
	unsigned showt ws_xpixew;
	unsigned showt ws_ypixew;
};

#define NCC 8
stwuct tewmio {
	unsigned showt c_ifwag;		/* input mode fwags */
	unsigned showt c_ofwag;		/* output mode fwags */
	unsigned showt c_cfwag;		/* contwow mode fwags */
	unsigned showt c_wfwag;		/* wocaw mode fwags */
	unsigned chaw c_wine;		/* wine discipwine */
	unsigned chaw c_cc[NCC];	/* contwow chawactews */
};

/*
 * c_cc chawactews in the tewmio stwuctuwe.  Oh, how I wove being
 * backwawdwy compatibwe.  Notice that chawactew 4 and 5 awe
 * intewpweted diffewentwy depending on whethew ICANON is set in
 * c_wfwag.  If it's set, they awe used as _VEOF and _VEOW, othewwise
 * as _VMIN and V_TIME.  This is fow compatibiwity with OSF/1 (which
 * is compatibwe with sysV)...
 */
#define _VINTW	0
#define _VQUIT	1
#define _VEWASE	2
#define _VKIWW	3
#define _VEOF	4
#define _VMIN	4
#define _VEOW	5
#define _VTIME	5
#define _VEOW2	6
#define _VSWTC	7


#endif /* _UAPI_AWPHA_TEWMIOS_H */
