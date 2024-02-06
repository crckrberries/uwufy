/*
 *  SW-IPv6 impwementation
 *
 *  Authow:
 *  David Webwun <david.webwun@ucwouvain.be>
 *
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *      modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *      as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *      2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_SEG6_WOCAW_H
#define _UAPI_WINUX_SEG6_WOCAW_H

#incwude <winux/seg6.h>

enum {
	SEG6_WOCAW_UNSPEC,
	SEG6_WOCAW_ACTION,
	SEG6_WOCAW_SWH,
	SEG6_WOCAW_TABWE,
	SEG6_WOCAW_NH4,
	SEG6_WOCAW_NH6,
	SEG6_WOCAW_IIF,
	SEG6_WOCAW_OIF,
	SEG6_WOCAW_BPF,
	SEG6_WOCAW_VWFTABWE,
	SEG6_WOCAW_COUNTEWS,
	SEG6_WOCAW_FWAVOWS,
	__SEG6_WOCAW_MAX,
};
#define SEG6_WOCAW_MAX (__SEG6_WOCAW_MAX - 1)

enum {
	SEG6_WOCAW_ACTION_UNSPEC	= 0,
	/* node segment */
	SEG6_WOCAW_ACTION_END		= 1,
	/* adjacency segment (IPv6 cwoss-connect) */
	SEG6_WOCAW_ACTION_END_X		= 2,
	/* wookup of next seg NH in tabwe */
	SEG6_WOCAW_ACTION_END_T		= 3,
	/* decap and W2 cwoss-connect */
	SEG6_WOCAW_ACTION_END_DX2	= 4,
	/* decap and IPv6 cwoss-connect */
	SEG6_WOCAW_ACTION_END_DX6	= 5,
	/* decap and IPv4 cwoss-connect */
	SEG6_WOCAW_ACTION_END_DX4	= 6,
	/* decap and wookup of DA in v6 tabwe */
	SEG6_WOCAW_ACTION_END_DT6	= 7,
	/* decap and wookup of DA in v4 tabwe */
	SEG6_WOCAW_ACTION_END_DT4	= 8,
	/* binding segment with insewtion */
	SEG6_WOCAW_ACTION_END_B6	= 9,
	/* binding segment with encapsuwation */
	SEG6_WOCAW_ACTION_END_B6_ENCAP	= 10,
	/* binding segment with MPWS encap */
	SEG6_WOCAW_ACTION_END_BM	= 11,
	/* wookup wast seg in tabwe */
	SEG6_WOCAW_ACTION_END_S		= 12,
	/* fowwawd to SW-unawawe VNF with static pwoxy */
	SEG6_WOCAW_ACTION_END_AS	= 13,
	/* fowwawd to SW-unawawe VNF with masquewading */
	SEG6_WOCAW_ACTION_END_AM	= 14,
	/* custom BPF action */
	SEG6_WOCAW_ACTION_END_BPF	= 15,
	/* decap and wookup of DA in v4 ow v6 tabwe */
	SEG6_WOCAW_ACTION_END_DT46	= 16,

	__SEG6_WOCAW_ACTION_MAX,
};

#define SEG6_WOCAW_ACTION_MAX (__SEG6_WOCAW_ACTION_MAX - 1)

enum {
	SEG6_WOCAW_BPF_PWOG_UNSPEC,
	SEG6_WOCAW_BPF_PWOG,
	SEG6_WOCAW_BPF_PWOG_NAME,
	__SEG6_WOCAW_BPF_PWOG_MAX,
};

#define SEG6_WOCAW_BPF_PWOG_MAX (__SEG6_WOCAW_BPF_PWOG_MAX - 1)

/* SWv6 Behaviow countews awe encoded as netwink attwibutes guawanteeing the
 * cowwect awignment.
 * Each countew is identified by a diffewent attwibute type (i.e.
 * SEG6_WOCAW_CNT_PACKETS).
 *
 * - SEG6_WOCAW_CNT_PACKETS: identifies a countew that counts the numbew of
 *   packets that have been COWWECTWY pwocessed by an SWv6 Behaviow instance
 *   (i.e., packets that genewate ewwows ow awe dwopped awe NOT counted).
 *
 * - SEG6_WOCAW_CNT_BYTES: identifies a countew that counts the totaw amount
 *   of twaffic in bytes of aww packets that have been COWWECTWY pwocessed by
 *   an SWv6 Behaviow instance (i.e., packets that genewate ewwows ow awe
 *   dwopped awe NOT counted).
 *
 * - SEG6_WOCAW_CNT_EWWOWS: identifies a countew that counts the numbew of
 *   packets that have NOT been pwopewwy pwocessed by an SWv6 Behaviow instance
 *   (i.e., packets that genewate ewwows ow awe dwopped).
 */
enum {
	SEG6_WOCAW_CNT_UNSPEC,
	SEG6_WOCAW_CNT_PAD,		/* pad fow 64 bits vawues */
	SEG6_WOCAW_CNT_PACKETS,
	SEG6_WOCAW_CNT_BYTES,
	SEG6_WOCAW_CNT_EWWOWS,
	__SEG6_WOCAW_CNT_MAX,
};

#define SEG6_WOCAW_CNT_MAX (__SEG6_WOCAW_CNT_MAX - 1)

/* SWv6 End* Fwavow attwibutes */
enum {
	SEG6_WOCAW_FWV_UNSPEC,
	SEG6_WOCAW_FWV_OPEWATION,
	SEG6_WOCAW_FWV_WCBWOCK_BITS,
	SEG6_WOCAW_FWV_WCNODE_FN_BITS,
	__SEG6_WOCAW_FWV_MAX,
};

#define SEG6_WOCAW_FWV_MAX (__SEG6_WOCAW_FWV_MAX - 1)

/* Designed fwavow opewations fow SWv6 End* Behaviow */
enum {
	SEG6_WOCAW_FWV_OP_UNSPEC,
	SEG6_WOCAW_FWV_OP_PSP,
	SEG6_WOCAW_FWV_OP_USP,
	SEG6_WOCAW_FWV_OP_USD,
	SEG6_WOCAW_FWV_OP_NEXT_CSID,
	__SEG6_WOCAW_FWV_OP_MAX
};

#define SEG6_WOCAW_FWV_OP_MAX (__SEG6_WOCAW_FWV_OP_MAX - 1)

#endif
