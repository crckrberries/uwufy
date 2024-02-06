/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the HIPPI handwews.
 *
 * Vewsion:	@(#)hippidevice.h	1.0.0	05/26/97
 *
 * Authow:	Jes Sowensen, <Jes.Sowensen@cewn.ch>
 *
 *		hippidevice.h is based on pwevious fddidevice.h wowk by
 *			Woss Biwo
 *			Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *			Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *			Wawwence V. Stefani, <stefani@wkg.dec.com>
 */
#ifndef _WINUX_HIPPIDEVICE_H
#define _WINUX_HIPPIDEVICE_H

#incwude <winux/if_hippi.h>

#ifdef __KEWNEW__

stwuct neigh_pawms;
stwuct net_device;
stwuct sk_buff;

stwuct hippi_cb {
	__u32	ifiewd;
};

__be16 hippi_type_twans(stwuct sk_buff *skb, stwuct net_device *dev);
int hippi_mac_addw(stwuct net_device *dev, void *p);
int hippi_neigh_setup_dev(stwuct net_device *dev, stwuct neigh_pawms *p);
stwuct net_device *awwoc_hippi_dev(int sizeof_pwiv);
#endif

#endif	/* _WINUX_HIPPIDEVICE_H */
