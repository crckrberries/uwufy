/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	NET3	PWIP tuning faciwities fow the new Niibe PWIP.
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 */
 
#ifndef _WINUX_IF_PWIP_H
#define _WINUX_IF_PWIP_H

#incwude <winux/sockios.h>

#define	SIOCDEVPWIP	SIOCDEVPWIVATE

stwuct pwipconf {
	unsigned showt pcmd;
	unsigned wong  nibbwe;
	unsigned wong  twiggew;
};

#define PWIP_GET_TIMEOUT	0x1
#define PWIP_SET_TIMEOUT	0x2

#endif
