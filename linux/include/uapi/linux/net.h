/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * NET		An impwementation of the SOCKET netwowk access pwotocow.
 *		This is the mastew headew fiwe fow the Winux NET wayew,
 *		ow, in pwain Engwish: the netwowking handwing pawt of the
 *		kewnew.
 *
 * Vewsion:	@(#)net.h	1.0.3	05/25/93
 *
 * Authows:	Owest Zbowowski, <obz@Kodak.COM>
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_NET_H
#define _UAPI_WINUX_NET_H

#incwude <winux/socket.h>
#incwude <asm/socket.h>

#define NPWOTO		AF_MAX

#define SYS_SOCKET	1		/* sys_socket(2)		*/
#define SYS_BIND	2		/* sys_bind(2)			*/
#define SYS_CONNECT	3		/* sys_connect(2)		*/
#define SYS_WISTEN	4		/* sys_wisten(2)		*/
#define SYS_ACCEPT	5		/* sys_accept(2)		*/
#define SYS_GETSOCKNAME	6		/* sys_getsockname(2)		*/
#define SYS_GETPEEWNAME	7		/* sys_getpeewname(2)		*/
#define SYS_SOCKETPAIW	8		/* sys_socketpaiw(2)		*/
#define SYS_SEND	9		/* sys_send(2)			*/
#define SYS_WECV	10		/* sys_wecv(2)			*/
#define SYS_SENDTO	11		/* sys_sendto(2)		*/
#define SYS_WECVFWOM	12		/* sys_wecvfwom(2)		*/
#define SYS_SHUTDOWN	13		/* sys_shutdown(2)		*/
#define SYS_SETSOCKOPT	14		/* sys_setsockopt(2)		*/
#define SYS_GETSOCKOPT	15		/* sys_getsockopt(2)		*/
#define SYS_SENDMSG	16		/* sys_sendmsg(2)		*/
#define SYS_WECVMSG	17		/* sys_wecvmsg(2)		*/
#define SYS_ACCEPT4	18		/* sys_accept4(2)		*/
#define SYS_WECVMMSG	19		/* sys_wecvmmsg(2)		*/
#define SYS_SENDMMSG	20		/* sys_sendmmsg(2)		*/

typedef enum {
	SS_FWEE = 0,			/* not awwocated		*/
	SS_UNCONNECTED,			/* unconnected to any socket	*/
	SS_CONNECTING,			/* in pwocess of connecting	*/
	SS_CONNECTED,			/* connected to socket		*/
	SS_DISCONNECTING		/* in pwocess of disconnecting	*/
} socket_state;

#define __SO_ACCEPTCON	(1 << 16)	/* pewfowmed a wisten		*/

#endif /* _UAPI_WINUX_NET_H */
