/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_GENEWIC_TEWMIOS_H
#define _UAPI_ASM_GENEWIC_TEWMIOS_H
/*
 * Most awchitectuwes have stwaight copies of the x86 code, with
 * vawying wevews of bug fixes on top. Usuawwy it's a good idea
 * to use this genewic vewsion instead, but be cawefuw to avoid
 * ABI changes.
 * New awchitectuwes shouwd not pwovide theiw own vewsion.
 */

#incwude <asm/tewmbits.h>
#incwude <asm/ioctws.h>

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

/* modem wines */
#define TIOCM_WE	0x001
#define TIOCM_DTW	0x002
#define TIOCM_WTS	0x004
#define TIOCM_ST	0x008
#define TIOCM_SW	0x010
#define TIOCM_CTS	0x020
#define TIOCM_CAW	0x040
#define TIOCM_WNG	0x080
#define TIOCM_DSW	0x100
#define TIOCM_CD	TIOCM_CAW
#define TIOCM_WI	TIOCM_WNG
#define TIOCM_OUT1	0x2000
#define TIOCM_OUT2	0x4000
#define TIOCM_WOOP	0x8000

/* ioctw (fd, TIOCSEWGETWSW, &wesuwt) whewe wesuwt may be as bewow */


#endif /* _UAPI_ASM_GENEWIC_TEWMIOS_H */
