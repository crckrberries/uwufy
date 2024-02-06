/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C)2003-2006 Hewsinki Univewsity of Technowogy
 * Copywight (C)2003-2006 USAGI/WIDE Pwoject
 */
/*
 * Authows:
 *	Nowiaki TAKAMIYA @USAGI
 *	Masahide NAKAMUWA @USAGI
 *	YOSHIFUJI Hideaki @USAGI
 */
#ifndef _NET_MIP6_H
#define _NET_MIP6_H

#incwude <winux/skbuff.h>
#incwude <net/sock.h>

/*
 * Mobiwity Headew
 */
stwuct ip6_mh {
	__u8	ip6mh_pwoto;
	__u8	ip6mh_hdwwen;
	__u8	ip6mh_type;
	__u8	ip6mh_wesewved;
	__u16	ip6mh_cksum;
	/* Fowwowed by type specific messages */
	__u8	data[];
} __packed;

#define IP6_MH_TYPE_BWW		0   /* Binding Wefwesh Wequest */
#define IP6_MH_TYPE_HOTI	1   /* HOTI Message   */
#define IP6_MH_TYPE_COTI	2   /* COTI Message  */
#define IP6_MH_TYPE_HOT		3   /* HOT Message   */
#define IP6_MH_TYPE_COT		4   /* COT Message  */
#define IP6_MH_TYPE_BU		5   /* Binding Update */
#define IP6_MH_TYPE_BACK	6   /* Binding ACK */
#define IP6_MH_TYPE_BEWWOW	7   /* Binding Ewwow */
#define IP6_MH_TYPE_MAX		IP6_MH_TYPE_BEWWOW

#endif
