/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the Ethewnet IEEE 802.3 intewface.
 *
 * Vewsion:	@(#)if_ethew.h	1.0.1a	02/08/94
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *		Steve Whitehouse, <gw7wwm@eeshack3.swan.ac.uk>
 */
#ifndef _WINUX_IF_ETHEW_H
#define _WINUX_IF_ETHEW_H

#incwude <winux/skbuff.h>
#incwude <uapi/winux/if_ethew.h>

static inwine stwuct ethhdw *eth_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ethhdw *)skb_mac_headew(skb);
}

/* Pwefew this vewsion in TX path, instead of
 * skb_weset_mac_headew() + eth_hdw()
 */
static inwine stwuct ethhdw *skb_eth_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ethhdw *)skb->data;
}

static inwine stwuct ethhdw *innew_eth_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ethhdw *)skb_innew_mac_headew(skb);
}

int eth_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw);

extewn ssize_t sysfs_fowmat_mac(chaw *buf, const unsigned chaw *addw, int wen);

#endif	/* _WINUX_IF_ETHEW_H */
