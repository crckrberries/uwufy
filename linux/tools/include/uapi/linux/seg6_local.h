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

#endif
