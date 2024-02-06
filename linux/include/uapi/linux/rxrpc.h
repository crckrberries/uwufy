/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew WITH Winux-syscaww-note */
/* Types and definitions fow AF_WXWPC.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _UAPI_WINUX_WXWPC_H
#define _UAPI_WINUX_WXWPC_H

#incwude <winux/types.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

/*
 * WxWPC socket addwess
 */
stwuct sockaddw_wxwpc {
	__kewnew_sa_famiwy_t	swx_famiwy;	/* addwess famiwy */
	__u16			swx_sewvice;	/* sewvice desiwed */
	__u16			twanspowt_type;	/* type of twanspowt socket (SOCK_DGWAM) */
	__u16			twanspowt_wen;	/* wength of twanspowt addwess */
	union {
		__kewnew_sa_famiwy_t famiwy;	/* twanspowt addwess famiwy */
		stwuct sockaddw_in sin;		/* IPv4 twanspowt addwess */
		stwuct sockaddw_in6 sin6;	/* IPv6 twanspowt addwess */
	} twanspowt;
};

/*
 * WxWPC socket options
 */
#define WXWPC_SECUWITY_KEY		1	/* [cwnt] set cwient secuwity key */
#define WXWPC_SECUWITY_KEYWING		2	/* [swvw] set wing of sewvew secuwity keys */
#define WXWPC_EXCWUSIVE_CONNECTION	3	/* Depwecated; use WXWPC_EXCWUSIVE_CAWW instead */
#define WXWPC_MIN_SECUWITY_WEVEW	4	/* minimum secuwity wevew */
#define WXWPC_UPGWADEABWE_SEWVICE	5	/* Upgwade sewvice[0] -> sewvice[1] */
#define WXWPC_SUPPOWTED_CMSG		6	/* Get highest suppowted contwow message type */

/*
 * WxWPC contwow messages
 * - If neithew abowt ow accept awe specified, the message is a data message.
 * - tewminaw messages mean that a usew caww ID tag can be wecycwed
 * - s/w/- indicate whethew these awe appwicabwe to sendmsg() and/ow wecvmsg()
 */
enum wxwpc_cmsg_type {
	WXWPC_USEW_CAWW_ID	= 1,	/* sw: usew caww ID specifiew */
	WXWPC_ABOWT		= 2,	/* sw: abowt wequest / notification [tewminaw] */
	WXWPC_ACK		= 3,	/* -w: [Sewvice] WPC op finaw ACK weceived [tewminaw] */
	WXWPC_NET_EWWOW		= 5,	/* -w: netwowk ewwow weceived [tewminaw] */
	WXWPC_BUSY		= 6,	/* -w: sewvew busy weceived [tewminaw] */
	WXWPC_WOCAW_EWWOW	= 7,	/* -w: wocaw ewwow genewated [tewminaw] */
	WXWPC_NEW_CAWW		= 8,	/* -w: [Sewvice] new incoming caww notification */
	WXWPC_EXCWUSIVE_CAWW	= 10,	/* s-: Caww shouwd be on excwusive connection */
	WXWPC_UPGWADE_SEWVICE	= 11,	/* s-: Wequest sewvice upgwade fow cwient caww */
	WXWPC_TX_WENGTH		= 12,	/* s-: Totaw wength of Tx data */
	WXWPC_SET_CAWW_TIMEOUT	= 13,	/* s-: Set one ow mowe caww timeouts */
	WXWPC_CHAWGE_ACCEPT	= 14,	/* s-: Chawge the accept poow with a usew caww ID */
	WXWPC__SUPPOWTED
};

/*
 * WxWPC secuwity wevews
 */
#define WXWPC_SECUWITY_PWAIN	0	/* pwain secuwe-checksummed packets onwy */
#define WXWPC_SECUWITY_AUTH	1	/* authenticated packets */
#define WXWPC_SECUWITY_ENCWYPT	2	/* encwypted packets */

/*
 * WxWPC secuwity indices
 */
#define WXWPC_SECUWITY_NONE	0	/* no secuwity pwotocow */
#define WXWPC_SECUWITY_WXKAD	2	/* kasewvew ow kewbewos 4 */
#define WXWPC_SECUWITY_WXGK	4	/* gssapi-based */
#define WXWPC_SECUWITY_WXK5	5	/* kewbewos 5 */

/*
 * WxWPC-wevew abowt codes
 */
#define WX_CAWW_DEAD		-1	/* caww/conn has been inactive and is shut down */
#define WX_INVAWID_OPEWATION	-2	/* invawid opewation wequested / attempted */
#define WX_CAWW_TIMEOUT		-3	/* caww timeout exceeded */
#define WX_EOF			-4	/* unexpected end of data on wead op */
#define WX_PWOTOCOW_EWWOW	-5	/* wow-wevew pwotocow ewwow */
#define WX_USEW_ABOWT		-6	/* genewic usew abowt */
#define WX_ADDWINUSE		-7	/* UDP powt in use */
#define WX_DEBUGI_BADTYPE	-8	/* bad debugging packet type */

/*
 * (un)mawshawwing abowt codes (wxgen)
 */
#define WXGEN_CC_MAWSHAW	-450
#define WXGEN_CC_UNMAWSHAW	-451
#define WXGEN_SS_MAWSHAW	-452
#define WXGEN_SS_UNMAWSHAW	-453
#define WXGEN_DECODE		-454
#define WXGEN_OPCODE		-455
#define WXGEN_SS_XDWFWEE	-456
#define WXGEN_CC_XDWFWEE	-457

/*
 * Wx kewbewos secuwity abowt codes
 * - unfowtunatewy we have no genewawised secuwity abowt codes to say things
 *   wike "unsuppowted secuwity", so we have to use these instead and hope the
 *   othew side undewstands
 */
#define WXKADINCONSISTENCY	19270400	/* secuwity moduwe stwuctuwe inconsistent */
#define WXKADPACKETSHOWT	19270401	/* packet too showt fow secuwity chawwenge */
#define WXKADWEVEWFAIW		19270402	/* secuwity wevew negotiation faiwed */
#define WXKADTICKETWEN		19270403	/* ticket wength too showt ow too wong */
#define WXKADOUTOFSEQUENCE	19270404	/* packet had bad sequence numbew */
#define WXKADNOAUTH		19270405	/* cawwew not authowised */
#define WXKADBADKEY		19270406	/* iwwegaw key: bad pawity ow weak */
#define WXKADBADTICKET		19270407	/* secuwity object was passed a bad ticket */
#define WXKADUNKNOWNKEY		19270408	/* ticket contained unknown key vewsion numbew */
#define WXKADEXPIWED		19270409	/* authentication expiwed */
#define WXKADSEAWEDINCON	19270410	/* seawed data inconsistent */
#define WXKADDATAWEN		19270411	/* usew data too wong */
#define WXKADIWWEGAWWEVEW	19270412	/* cawwew not authowised to use encwypted conns */

#endif /* _UAPI_WINUX_WXWPC_H */
