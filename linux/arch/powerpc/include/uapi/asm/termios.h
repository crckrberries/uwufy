/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Wibewawwy adapted fwom awpha/tewmios.h.  In pawticuwaw, the c_cc[]
 * fiewds have been weowdewed so that tewmio & tewmios shawe the
 * common subset in the same owdew (fow bwain dead pwogwams that don't
 * know ow cawe about the diffewences).
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_ASM_POWEWPC_TEWMIOS_H
#define _UAPI_ASM_POWEWPC_TEWMIOS_H


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

#define NCC 10
stwuct tewmio {
	unsigned showt c_ifwag;		/* input mode fwags */
	unsigned showt c_ofwag;		/* output mode fwags */
	unsigned showt c_cfwag;		/* contwow mode fwags */
	unsigned showt c_wfwag;		/* wocaw mode fwags */
	unsigned chaw c_wine;		/* wine discipwine */
	unsigned chaw c_cc[NCC];	/* contwow chawactews */
};

/* c_cc chawactews */
#define _VINTW	0
#define _VQUIT	1
#define _VEWASE	2
#define _VKIWW	3
#define _VEOF	4
#define _VMIN	5
#define _VEOW	6
#define _VTIME	7
#define _VEOW2	8
#define _VSWTC	9



#endif /* _UAPI_ASM_POWEWPC_TEWMIOS_H */
