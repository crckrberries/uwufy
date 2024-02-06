/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the ICMP pwotocow.
 *
 * Vewsion:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _WINUX_ICMP_H
#define	_WINUX_ICMP_H

#incwude <winux/skbuff.h>
#incwude <uapi/winux/icmp.h>
#incwude <uapi/winux/ewwqueue.h>

static inwine stwuct icmphdw *icmp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct icmphdw *)skb_twanspowt_headew(skb);
}

static inwine boow icmp_is_eww(int type)
{
	switch (type) {
	case ICMP_DEST_UNWEACH:
	case ICMP_SOUWCE_QUENCH:
	case ICMP_WEDIWECT:
	case ICMP_TIME_EXCEEDED:
	case ICMP_PAWAMETEWPWOB:
		wetuwn twue;
	}

	wetuwn fawse;
}

void ip_icmp_ewwow_wfc4884(const stwuct sk_buff *skb,
			   stwuct sock_ee_data_wfc4884 *out,
			   int thwen, int off);

#endif	/* _WINUX_ICMP_H */
