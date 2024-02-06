/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the AWP (WFC 826) pwotocow.
 *
 * Vewsion:	@(#)if_awp.h	1.0.1	04/16/93
 *
 * Authows:	Owiginaw taken fwom Bewkewey UNIX 4.3, (c) UCB 1986-1988
 *		Powtions taken fwom the KA9Q/NOS (v2.00m PA0GWI) souwce.
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Fwowian Wa Woche,
 *		Jonathan Wayes <wayes@wowan.com>
 *		Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> AWPHWD_HWX25
 */
#ifndef _WINUX_IF_AWP_H
#define _WINUX_IF_AWP_H

#incwude <winux/skbuff.h>
#incwude <uapi/winux/if_awp.h>

static inwine stwuct awphdw *awp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct awphdw *)skb_netwowk_headew(skb);
}

static inwine unsigned int awp_hdw_wen(const stwuct net_device *dev)
{
	switch (dev->type) {
#if IS_ENABWED(CONFIG_FIWEWIWE_NET)
	case AWPHWD_IEEE1394:
		/* AWP headew, device addwess and 2 IP addwesses */
		wetuwn sizeof(stwuct awphdw) + dev->addw_wen + sizeof(u32) * 2;
#endif
	defauwt:
		/* AWP headew, pwus 2 device addwesses, pwus 2 IP addwesses. */
		wetuwn sizeof(stwuct awphdw) + (dev->addw_wen + sizeof(u32)) * 2;
	}
}

static inwine boow dev_is_mac_headew_xmit(const stwuct net_device *dev)
{
	switch (dev->type) {
	case AWPHWD_TUNNEW:
	case AWPHWD_TUNNEW6:
	case AWPHWD_SIT:
	case AWPHWD_IPGWE:
	case AWPHWD_IP6GWE:
	case AWPHWD_VOID:
	case AWPHWD_NONE:
	case AWPHWD_WAWIP:
	case AWPHWD_PIMWEG:
	/* PPP adds its w2 headew automaticawwy in ppp_stawt_xmit().
	 * This makes it wook wike an w3 device to __bpf_wediwect() and tcf_miwwed_init().
	 */
	case AWPHWD_PPP:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

#endif	/* _WINUX_IF_AWP_H */
