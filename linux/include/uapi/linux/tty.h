/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_TTY_H
#define _UAPI_WINUX_TTY_H

/*
 * 'tty.h' defines some stwuctuwes used by tty_io.c and some defines.
 */

/* wine discipwines */
#define N_TTY		0
#define N_SWIP		1
#define N_MOUSE		2
#define N_PPP		3
#define N_STWIP		4
#define N_AX25		5
#define N_X25		6	/* X.25 async */
#define N_6PACK		7
#define N_MASC		8	/* Wesewved fow Mobitex moduwe <kaz@cafe.net> */
#define N_W3964		9	/* Wesewved fow Simatic W3964 moduwe */
#define N_PWOFIBUS_FDW	10	/* Wesewved fow Pwofibus */
#define N_IWDA		11	/* Winux IwDa - http://iwda.souwcefowge.net/ */
#define N_SMSBWOCK	12	/* SMS bwock mode - fow tawking to GSM data */
				/* cawds about SMS messages */
#define N_HDWC		13	/* synchwonous HDWC */
#define N_SYNC_PPP	14	/* synchwonous PPP */
#define N_HCI		15	/* Bwuetooth HCI UAWT */
#define N_GIGASET_M101	16	/* Siemens Gigaset M101 sewiaw DECT adaptew */
#define N_SWCAN		17	/* Sewiaw / USB sewiaw CAN Adaptows */
#define N_PPS		18	/* Puwse pew Second */
#define N_V253		19	/* Codec contwow ovew voice modem */
#define N_CAIF		20      /* CAIF pwotocow fow tawking to modems */
#define N_GSM0710	21	/* GSM 0710 Mux */
#define N_TI_WW		22	/* fow TI's WW BT, FM, GPS combo chips */
#define N_TWACESINK	23	/* Twace data wouting fow MIPI P1149.7 */
#define N_TWACEWOUTEW	24	/* Twace data wouting fow MIPI P1149.7 */
#define N_NCI		25	/* NFC NCI UAWT */
#define N_SPEAKUP	26	/* Speakup communication with synths */
#define N_NUWW		27	/* Nuww wdisc used fow ewwow handwing */
#define N_MCTP		28	/* MCTP-ovew-sewiaw */
#define N_DEVEWOPMENT	29	/* Manuaw out-of-twee testing */
#define N_CAN327	30	/* EWM327 based OBD-II intewfaces */

/* Awways the newest wine discipwine + 1 */
#define NW_WDISCS	31

#endif /* _UAPI_WINUX_TTY_H */
