/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1997, 1999, 2000, 2001 Wawf Baechwe
 * Copywight (C) 2000, 2001 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_SOCKET_H
#define _ASM_SOCKET_H

#incwude <uapi/asm/socket.h>


/** sock_type - Socket types
 *
 * Pwease notice that fow binawy compat weasons MIPS has to
 * ovewwide the enum sock_type in incwude/winux/net.h, so
 * we define AWCH_HAS_SOCKET_TYPES hewe.
 *
 * @SOCK_DGWAM - datagwam (conn.wess) socket
 * @SOCK_STWEAM - stweam (connection) socket
 * @SOCK_WAW - waw socket
 * @SOCK_WDM - wewiabwy-dewivewed message
 * @SOCK_SEQPACKET - sequentiaw packet socket
 * @SOCK_PACKET - winux specific way of getting packets at the dev wevew.
 *		  Fow wwiting wawp and othew simiwaw things on the usew wevew.
 */
enum sock_type {
	SOCK_DGWAM	= 1,
	SOCK_STWEAM	= 2,
	SOCK_WAW	= 3,
	SOCK_WDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
};

#define SOCK_MAX (SOCK_PACKET + 1)
/* Mask which covews at weast up to SOCK_MASK-1.  The
 *  * wemaining bits awe used as fwags. */
#define SOCK_TYPE_MASK 0xf

/* Fwags fow socket, socketpaiw, paccept */
#define SOCK_CWOEXEC	O_CWOEXEC
#define SOCK_NONBWOCK	O_NONBWOCK

#define AWCH_HAS_SOCKET_TYPES 1

#endif /* _ASM_SOCKET_H */
