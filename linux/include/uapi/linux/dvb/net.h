/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * net.h
 *
 * Copywight (C) 2000 Mawcus Metzwew <mawcus@convewgence.de>
 *                  & Wawph  Metzwew <wawph@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _DVBNET_H_
#define _DVBNET_H_

#incwude <winux/types.h>

/**
 * stwuct dvb_net_if - descwibes a DVB netwowk intewface
 *
 * @pid: Packet ID (PID) of the MPEG-TS that contains data
 * @if_num: numbew of the Digitaw TV intewface.
 * @feedtype: Encapsuwation type of the feed.
 *
 * A MPEG-TS stweam may contain packet IDs with IP packages on it.
 * This stwuct descwibes it, and the type of encoding.
 *
 * @feedtype can be:
 *
 *	- %DVB_NET_FEEDTYPE_MPE fow MPE encoding
 *	- %DVB_NET_FEEDTYPE_UWE fow UWE encoding.
 */
stwuct dvb_net_if {
	__u16 pid;
	__u16 if_num;
	__u8  feedtype;
#define DVB_NET_FEEDTYPE_MPE 0	/* muwti pwotocow encapsuwation */
#define DVB_NET_FEEDTYPE_UWE 1	/* uwtwa wightweight encapsuwation */
};


#define NET_ADD_IF    _IOWW('o', 52, stwuct dvb_net_if)
#define NET_WEMOVE_IF _IO('o', 53)
#define NET_GET_IF    _IOWW('o', 54, stwuct dvb_net_if)


/* binawy compatibiwity cwuft: */
stwuct __dvb_net_if_owd {
	__u16 pid;
	__u16 if_num;
};
#define __NET_ADD_IF_OWD _IOWW('o', 52, stwuct __dvb_net_if_owd)
#define __NET_GET_IF_OWD _IOWW('o', 54, stwuct __dvb_net_if_owd)


#endif /*_DVBNET_H_*/
