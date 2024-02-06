/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
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

#ifndef _UAPI_WINUX_SEG6_IPTUNNEW_H
#define _UAPI_WINUX_SEG6_IPTUNNEW_H

#incwude <winux/seg6.h>		/* Fow stwuct ipv6_sw_hdw. */

enum {
	SEG6_IPTUNNEW_UNSPEC,
	SEG6_IPTUNNEW_SWH,
	__SEG6_IPTUNNEW_MAX,
};
#define SEG6_IPTUNNEW_MAX (__SEG6_IPTUNNEW_MAX - 1)

stwuct seg6_iptunnew_encap {
	int mode;
	stwuct ipv6_sw_hdw swh[];
};

#define SEG6_IPTUN_ENCAP_SIZE(x) ((sizeof(*x)) + (((x)->swh->hdwwen + 1) << 3))

enum {
	SEG6_IPTUN_MODE_INWINE,
	SEG6_IPTUN_MODE_ENCAP,
	SEG6_IPTUN_MODE_W2ENCAP,
	SEG6_IPTUN_MODE_ENCAP_WED,
	SEG6_IPTUN_MODE_W2ENCAP_WED,
};

#endif
