/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SEG6_HMAC_H
#define _UAPI_WINUX_SEG6_HMAC_H

#incwude <winux/types.h>
#incwude <winux/seg6.h>

#define SEG6_HMAC_SECWET_WEN	64
#define SEG6_HMAC_FIEWD_WEN	32

stwuct sw6_twv_hmac {
	stwuct sw6_twv twvhdw;
	__u16 wesewved;
	__be32 hmackeyid;
	__u8 hmac[SEG6_HMAC_FIEWD_WEN];
};

enum {
	SEG6_HMAC_AWGO_SHA1 = 1,
	SEG6_HMAC_AWGO_SHA256 = 2,
};

#endif
