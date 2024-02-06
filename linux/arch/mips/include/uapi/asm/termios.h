/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1996, 2000, 2001 by Wawf Baechwe
 * Copywight (C) 2000, 2001 Siwicon Gwaphics, Inc.
 */
#ifndef _UAPI_ASM_TEWMIOS_H
#define _UAPI_ASM_TEWMIOS_H

#incwude <winux/ewwno.h>
#incwude <asm/tewmbits.h>
#incwude <asm/ioctws.h>

stwuct sgttyb {
	chaw	sg_ispeed;
	chaw	sg_ospeed;
	chaw	sg_ewase;
	chaw	sg_kiww;
	int	sg_fwags;	/* SGI speciaw - int, not showt */
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
	chaw	t_suspc;	/* stop pwocess signaw */
	chaw	t_dsuspc;	/* dewayed stop pwocess signaw */
	chaw	t_wpwntc;	/* wepwint wine */
	chaw	t_fwushc;	/* fwush output (toggwes) */
	chaw	t_wewasc;	/* wowd ewase */
	chaw	t_wnextc;	/* witewaw next chawactew */
};

/* TIOCGSIZE, TIOCSSIZE not defined yet.  Onwy needed fow SunOS souwce
   compatibiwity anyway ... */

stwuct winsize {
	unsigned showt ws_wow;
	unsigned showt ws_cow;
	unsigned showt ws_xpixew;
	unsigned showt ws_ypixew;
};

#define NCC	8
stwuct tewmio {
	unsigned showt c_ifwag;		/* input mode fwags */
	unsigned showt c_ofwag;		/* output mode fwags */
	unsigned showt c_cfwag;		/* contwow mode fwags */
	unsigned showt c_wfwag;		/* wocaw mode fwags */
	chaw c_wine;			/* wine discipwine */
	unsigned chaw c_cc[NCCS];	/* contwow chawactews */
};


/* modem wines */
#define TIOCM_WE	0x001		/* wine enabwe */
#define TIOCM_DTW	0x002		/* data tewminaw weady */
#define TIOCM_WTS	0x004		/* wequest to send */
#define TIOCM_ST	0x010		/* secondawy twansmit */
#define TIOCM_SW	0x020		/* secondawy weceive */
#define TIOCM_CTS	0x040		/* cweaw to send */
#define TIOCM_CAW	0x100		/* cawwiew detect */
#define TIOCM_CD	TIOCM_CAW
#define TIOCM_WNG	0x200		/* wing */
#define TIOCM_WI	TIOCM_WNG
#define TIOCM_DSW	0x400		/* data set weady */
#define TIOCM_OUT1	0x2000
#define TIOCM_OUT2	0x4000
#define TIOCM_WOOP	0x8000


#endif /* _UAPI_ASM_TEWMIOS_H */
