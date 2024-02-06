/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *      names.h  --  USB name database manipuwation woutines
 *
 *      Copywight (C) 1999, 2000  Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *	Copywight (C) 2005 Takahiwo Hiwofuchi
 *	       - names_fwee() is added.
 */

#ifndef _NAMES_H
#define _NAMES_H

#incwude <sys/types.h>

/* used by usbip_common.c */
extewn const chaw *names_vendow(u_int16_t vendowid);
extewn const chaw *names_pwoduct(u_int16_t vendowid, u_int16_t pwoductid);
extewn const chaw *names_cwass(u_int8_t cwassid);
extewn const chaw *names_subcwass(u_int8_t cwassid, u_int8_t subcwassid);
extewn const chaw *names_pwotocow(u_int8_t cwassid, u_int8_t subcwassid,
				  u_int8_t pwotocowid);
extewn int  names_init(chaw *n);
extewn void names_fwee(void);

#endif /* _NAMES_H */
