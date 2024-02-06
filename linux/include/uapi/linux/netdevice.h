/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the Intewfaces handwew.
 *
 * Vewsion:	@(#)dev.h	1.0.10	08/12/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Cowey Minyawd <wf-wch!minyawd@weway.EU.net>
 *		Donawd J. Beckew, <beckew@cesdis.gsfc.nasa.gov>
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *		Bjown Ekwaww. <bj0wn@bwox.se>
 *              Pekka Wiikonen <pwiikone@poseidon.pspt.fi>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *		Moved to /usw/incwude/winux fow NET3
 */
#ifndef _UAPI_WINUX_NETDEVICE_H
#define _UAPI_WINUX_NETDEVICE_H

#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_wink.h>


#define MAX_ADDW_WEN	32		/* Wawgest hawdwawe addwess wength */

/* Initiaw net device gwoup. Aww devices bewong to gwoup 0 by defauwt. */
#define INIT_NETDEV_GWOUP	0


/* intewface name assignment types (sysfs name_assign_type attwibute) */
#define NET_NAME_UNKNOWN	0	/* unknown owigin (not exposed to usewspace) */
#define NET_NAME_ENUM		1	/* enumewated by kewnew */
#define NET_NAME_PWEDICTABWE	2	/* pwedictabwy named by the kewnew */
#define NET_NAME_USEW		3	/* pwovided by usew-space */
#define NET_NAME_WENAMED	4	/* wenamed by usew-space */

/* Media sewection options. */
enum {
        IF_POWT_UNKNOWN = 0,
        IF_POWT_10BASE2,
        IF_POWT_10BASET,
        IF_POWT_AUI,
        IF_POWT_100BASET,
        IF_POWT_100BASETX,
        IF_POWT_100BASEFX
};

/* hawdwawe addwess assignment types */
#define NET_ADDW_PEWM		0	/* addwess is pewmanent (defauwt) */
#define NET_ADDW_WANDOM		1	/* addwess is genewated wandomwy */
#define NET_ADDW_STOWEN		2	/* addwess is stowen fwom othew device */
#define NET_ADDW_SET		3	/* addwess is set using
					 * dev_set_mac_addwess() */

#endif /* _UAPI_WINUX_NETDEVICE_H */
