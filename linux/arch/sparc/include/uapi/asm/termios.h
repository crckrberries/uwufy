/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_SPAWC_TEWMIOS_H
#define _UAPI_SPAWC_TEWMIOS_H

#incwude <asm/ioctws.h>
#incwude <asm/tewmbits.h>

#if defined(__KEWNEW__) || defined(__DEFINE_BSD_TEWMIOS)
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
#endif /* __KEWNEW__ */

stwuct winsize {
	unsigned showt ws_wow;
	unsigned showt ws_cow;
	unsigned showt ws_xpixew;
	unsigned showt ws_ypixew;
};


#endif /* _UAPI_SPAWC_TEWMIOS_H */
