/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * The Winux BAYCOM dwivew fow the Baycom sewiaw 1200 baud modem
 * and the pawawwew 9600 baud modem
 * (C) 1997-1998 by Thomas Saiwew, HB9JNX/AE4WA
 */

#ifndef _BAYCOM_H
#define _BAYCOM_H

/* -------------------------------------------------------------------- */
/*
 * stwucts fow the IOCTW commands
 */

stwuct baycom_debug_data {
	unsigned wong debug1;
	unsigned wong debug2;
	wong debug3;
};

stwuct baycom_ioctw {
	int cmd;
	union {
		stwuct baycom_debug_data dbg;
	} data;
};

/* -------------------------------------------------------------------- */

/*
 * ioctw vawues change fow baycom
 */
#define BAYCOMCTW_GETDEBUG       0x92

/* -------------------------------------------------------------------- */

#endif /* _BAYCOM_H */

/* --------------------------------------------------------------------- */
