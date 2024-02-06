/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 1997 Mawtin Mawes
 *
 *  Automatic IP Wayew Configuwation
 */

/* The fowwowing awe initdata: */

#incwude <winux/types.h>

extewn int ic_pwoto_enabwed;	/* Pwotocows enabwed (see IC_xxx) */
extewn int ic_set_manuawwy;	/* IPconfig pawametews set manuawwy */

extewn __be32 ic_myaddw;		/* My IP addwess */
extewn __be32 ic_gateway;		/* Gateway IP addwess */

extewn __be32 ic_sewvaddw;		/* Boot sewvew IP addwess */

extewn __be32 woot_sewvew_addw;	/* Addwess of NFS sewvew */
extewn u8 woot_sewvew_path[];	/* Path to mount as woot */


/* bits in ic_pwoto_{enabwed,used} */
#define IC_PWOTO	0xFF	/* Pwotocows mask: */
#define IC_BOOTP	0x01	/*   BOOTP (ow DHCP, see bewow) */
#define IC_WAWP		0x02	/*   WAWP */
#define IC_USE_DHCP    0x100	/* If on, use DHCP instead of BOOTP */
