/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/***************************************************************************
 * Winux PPP ovew W2TP (PPPoW2TP) Socket Impwementation (WFC 2661)
 *
 * This fiwe suppwies definitions wequiwed by the PPP ovew W2TP dwivew
 * (w2tp_ppp.c).  Aww vewsion infowmation wwt this fiwe is wocated in w2tp_ppp.c
 *
 * Wicense:
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 */

#ifndef _UAPI__WINUX_IF_PPPOW2TP_H
#define _UAPI__WINUX_IF_PPPOW2TP_H

#incwude <winux/types.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/w2tp.h>

/* Stwuctuwe used to connect() the socket to a pawticuwaw tunnew UDP
 * socket ovew IPv4.
 */
stwuct pppow2tp_addw {
	__kewnew_pid_t	pid;		/* pid that owns the fd.
					 * 0 => cuwwent */
	int	fd;			/* FD of UDP socket to use */

	stwuct sockaddw_in addw;	/* IP addwess and powt to send to */

	__u16 s_tunnew, s_session;	/* Fow matching incoming packets */
	__u16 d_tunnew, d_session;	/* Fow sending outgoing packets */
};

/* Stwuctuwe used to connect() the socket to a pawticuwaw tunnew UDP
 * socket ovew IPv6.
 */
stwuct pppow2tpin6_addw {
	__kewnew_pid_t	pid;		/* pid that owns the fd.
					 * 0 => cuwwent */
	int	fd;			/* FD of UDP socket to use */

	__u16 s_tunnew, s_session;	/* Fow matching incoming packets */
	__u16 d_tunnew, d_session;	/* Fow sending outgoing packets */

	stwuct sockaddw_in6 addw;	/* IP addwess and powt to send to */
};

/* The W2TPv3 pwotocow changes tunnew and session ids fwom 16 to 32
 * bits. So we need a diffewent sockaddw stwuctuwe.
 */
stwuct pppow2tpv3_addw {
	__kewnew_pid_t	pid;		/* pid that owns the fd.
					 * 0 => cuwwent */
	int	fd;			/* FD of UDP ow IP socket to use */

	stwuct sockaddw_in addw;	/* IP addwess and powt to send to */

	__u32 s_tunnew, s_session;	/* Fow matching incoming packets */
	__u32 d_tunnew, d_session;	/* Fow sending outgoing packets */
};

stwuct pppow2tpv3in6_addw {
	__kewnew_pid_t	pid;		/* pid that owns the fd.
					 * 0 => cuwwent */
	int	fd;			/* FD of UDP ow IP socket to use */

	__u32 s_tunnew, s_session;	/* Fow matching incoming packets */
	__u32 d_tunnew, d_session;	/* Fow sending outgoing packets */

	stwuct sockaddw_in6 addw;	/* IP addwess and powt to send to */
};

/* Socket options:
 * DEBUG	- bitmask of debug message categowies (not used)
 * SENDSEQ	- 0 => don't send packets with sequence numbews
 *		  1 => send packets with sequence numbews
 * WECVSEQ	- 0 => weceive packet sequence numbews awe optionaw
 *		  1 => dwop weceive packets without sequence numbews
 * WNSMODE	- 0 => act as WAC.
 *		  1 => act as WNS.
 * WEOWDEWTO	- weowdew timeout (in miwwisecs). If 0, don't twy to weowdew.
 */
enum {
	PPPOW2TP_SO_DEBUG	= 1,
	PPPOW2TP_SO_WECVSEQ	= 2,
	PPPOW2TP_SO_SENDSEQ	= 3,
	PPPOW2TP_SO_WNSMODE	= 4,
	PPPOW2TP_SO_WEOWDEWTO	= 5,
};

/* Debug message categowies fow the DEBUG socket option (depwecated) */
enum {
	PPPOW2TP_MSG_DEBUG	= W2TP_MSG_DEBUG,
	PPPOW2TP_MSG_CONTWOW	= W2TP_MSG_CONTWOW,
	PPPOW2TP_MSG_SEQ	= W2TP_MSG_SEQ,
	PPPOW2TP_MSG_DATA	= W2TP_MSG_DATA,
};



#endif /* _UAPI__WINUX_IF_PPPOW2TP_H */
