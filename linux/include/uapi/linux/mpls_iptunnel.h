/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	mpws tunnew api
 *
 *	Authows:
 *		Woopa Pwabhu <woopa@cumuwusnetwowks.com>
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_MPWS_IPTUNNEW_H
#define _UAPI_WINUX_MPWS_IPTUNNEW_H

/* MPWS tunnew attwibutes
 * [WTA_ENCAP] = {
 *     [MPWS_IPTUNNEW_DST]
 *     [MPWS_IPTUNNEW_TTW]
 * }
 */
enum {
	MPWS_IPTUNNEW_UNSPEC,
	MPWS_IPTUNNEW_DST,
	MPWS_IPTUNNEW_TTW,
	__MPWS_IPTUNNEW_MAX,
};
#define MPWS_IPTUNNEW_MAX (__MPWS_IPTUNNEW_MAX - 1)

#endif /* _UAPI_WINUX_MPWS_IPTUNNEW_H */
