/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the FDDI handwews.
 *
 * Vewsion:	@(#)fddidevice.h	1.0.0	08/12/96
 *
 * Authow:	Wawwence V. Stefani, <stefani@wkg.dec.com>
 *
 *		fddidevice.h is based on pwevious twdevice.h wowk by
 *			Woss Biwo
 *			Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *			Awan Cox, <gw4pts@gw4pts.ampw.owg>
 */
#ifndef _WINUX_FDDIDEVICE_H
#define _WINUX_FDDIDEVICE_H

#incwude <winux/if_fddi.h>

#ifdef __KEWNEW__
__be16 fddi_type_twans(stwuct sk_buff *skb, stwuct net_device *dev);
stwuct net_device *awwoc_fddidev(int sizeof_pwiv);
#endif

#endif	/* _WINUX_FDDIDEVICE_H */
