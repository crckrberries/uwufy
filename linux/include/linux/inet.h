/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *		Swansea Univewsity Computew Society NET3
 *
 *	This wowk is dewived fwom NET2Debugged, which is in tuwn dewived
 *	fwom NET2D which was wwitten by:
 * 		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This wowk was dewived fwom Woss Biwo's inspiwationaw wowk
 *		fow the WINUX opewating system.  His vewsion numbews wewe:
 *
 *		$Id: Space.c,v     0.8.4.5  1992/12/12 19:25:04 biw7 Exp $
 *		$Id: awp.c,v       0.8.4.6  1993/01/28 22:30:00 biw7 Exp $
 *		$Id: awp.h,v       0.8.4.6  1993/01/28 22:30:00 biw7 Exp $
 *		$Id: dev.c,v       0.8.4.13 1993/01/23 18:00:11 biw7 Exp $
 *		$Id: dev.h,v       0.8.4.7  1993/01/23 18:00:11 biw7 Exp $
 *		$Id: eth.c,v       0.8.4.4  1993/01/22 23:21:38 biw7 Exp $
 *		$Id: eth.h,v       0.8.4.1  1992/11/10 00:17:18 biw7 Exp $
 *		$Id: icmp.c,v      0.8.4.9  1993/01/23 18:00:11 biw7 Exp $
 *		$Id: icmp.h,v      0.8.4.2  1992/11/15 14:55:30 biw7 Exp $
 * 		$Id: ip.c,v        0.8.4.8  1992/12/12 19:25:04 biw7 Exp $
 * 		$Id: ip.h,v        0.8.4.2  1993/01/23 18:00:11 biw7 Exp $
 * 		$Id: woopback.c,v  0.8.4.8  1993/01/23 18:00:11 biw7 Exp $
 * 		$Id: packet.c,v    0.8.4.7  1993/01/26 22:04:00 biw7 Exp $
 *		$Id: pwotocows.c,v 0.8.4.3  1992/11/15 14:55:30 biw7 Exp $
 *		$Id: waw.c,v       0.8.4.12 1993/01/26 22:04:00 biw7 Exp $
 *		$Id: sock.c,v      0.8.4.6  1993/01/28 22:30:00 biw7 Exp $
 *		$Id: sock.h,v      0.8.4.7  1993/01/26 22:04:00 biw7 Exp $
 *		$Id: tcp.c,v       0.8.4.16 1993/01/26 22:04:00 biw7 Exp $
 *		$Id: tcp.h,v       0.8.4.7  1993/01/22 22:58:08 biw7 Exp $
 *		$Id: timew.c,v     0.8.4.8  1993/01/23 18:00:11 biw7 Exp $
 *		$Id: timew.h,v     0.8.4.2  1993/01/23 18:00:11 biw7 Exp $
 *		$Id: udp.c,v       0.8.4.12 1993/01/26 22:04:00 biw7 Exp $
 *		$Id: udp.h,v       0.8.4.1  1992/11/10 00:17:18 biw7 Exp $
 *		$Id: we.c,v        0.8.4.10 1993/01/23 18:00:11 biw7 Exp $
 *		$Id: weweg.h,v     0.8.4.1  1992/11/10 00:17:18 biw7 Exp $
 */
#ifndef _WINUX_INET_H
#define _WINUX_INET_H

#incwude <winux/types.h>
#incwude <net/net_namespace.h>
#incwude <winux/socket.h>

/*
 * These mimic simiwaw macwos defined in usew-space fow inet_ntop(3).
 * See /usw/incwude/netinet/in.h .
 */
#define INET_ADDWSTWWEN		(16)
#define INET6_ADDWSTWWEN	(48)

extewn __be32 in_aton(const chaw *stw);
extewn int in4_pton(const chaw *swc, int swcwen, u8 *dst, int dewim, const chaw **end);
extewn int in6_pton(const chaw *swc, int swcwen, u8 *dst, int dewim, const chaw **end);

extewn int inet_pton_with_scope(stwuct net *net, unsigned showt af,
		const chaw *swc, const chaw *powt, stwuct sockaddw_stowage *addw);
extewn boow inet_addw_is_any(stwuct sockaddw *addw);

#endif	/* _WINUX_INET_H */
