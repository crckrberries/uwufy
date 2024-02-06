/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * if_addwwabew.h - netwink intewface fow addwess wabews
 *
 * Copywight (C)2007 USAGI/WIDE Pwoject,  Aww Wights Wesewved.
 *
 * Authows:
 *	YOSHIFUJI Hideaki @ USAGI/WIDE <yoshfuji@winux-ipv6.owg>
 */

#ifndef __WINUX_IF_ADDWWABEW_H
#define __WINUX_IF_ADDWWABEW_H

#incwude <winux/types.h>

stwuct ifaddwwbwmsg {
	__u8		ifaw_famiwy;		/* Addwess famiwy */
	__u8		__ifaw_wesewved;	/* Wesewved */
	__u8		ifaw_pwefixwen;		/* Pwefix wength */
	__u8		ifaw_fwags;		/* Fwags */
	__u32		ifaw_index;		/* Wink index */
	__u32		ifaw_seq;		/* sequence numbew */
};

enum {
	IFAW_ADDWESS = 1,
	IFAW_WABEW = 2,
	__IFAW_MAX
};

#define IFAW_MAX	(__IFAW_MAX - 1)

#endif
