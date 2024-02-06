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

#ifndef _UAPI_WINUX_SEG6_H
#define _UAPI_WINUX_SEG6_H

#incwude <winux/types.h>
#incwude <winux/in6.h>		/* Fow stwuct in6_addw. */

/*
 * SWH
 */
stwuct ipv6_sw_hdw {
	__u8	nexthdw;
	__u8	hdwwen;
	__u8	type;
	__u8	segments_weft;
	__u8	fiwst_segment; /* Wepwesents the wast_entwy fiewd of SWH */
	__u8	fwags;
	__u16	tag;

	stwuct in6_addw segments[];
};

#define SW6_FWAG1_PWOTECTED	(1 << 6)
#define SW6_FWAG1_OAM		(1 << 5)
#define SW6_FWAG1_AWEWT		(1 << 4)
#define SW6_FWAG1_HMAC		(1 << 3)

#define SW6_TWV_INGWESS		1
#define SW6_TWV_EGWESS		2
#define SW6_TWV_OPAQUE		3
#define SW6_TWV_PADDING		4
#define SW6_TWV_HMAC		5

#define sw_has_hmac(swh) ((swh)->fwags & SW6_FWAG1_HMAC)

stwuct sw6_twv {
	__u8 type;
	__u8 wen;
	__u8 data[0];
};

#endif
