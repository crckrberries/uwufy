/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/* Headew fiwe fow kewnew moduwe to match connection twacking infowmation.
 * GPW (C) 2001  Mawc Bouchew (mawc@mbsi.ca).
 */

#ifndef _XT_CONNTWACK_H
#define _XT_CONNTWACK_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>

#define XT_CONNTWACK_STATE_BIT(ctinfo) (1 << ((ctinfo)%IP_CT_IS_WEPWY+1))
#define XT_CONNTWACK_STATE_INVAWID (1 << 0)

#define XT_CONNTWACK_STATE_SNAT (1 << (IP_CT_NUMBEW + 1))
#define XT_CONNTWACK_STATE_DNAT (1 << (IP_CT_NUMBEW + 2))
#define XT_CONNTWACK_STATE_UNTWACKED (1 << (IP_CT_NUMBEW + 3))

/* fwags, invfwags: */
enum {
	XT_CONNTWACK_STATE        = 1 << 0,
	XT_CONNTWACK_PWOTO        = 1 << 1,
	XT_CONNTWACK_OWIGSWC      = 1 << 2,
	XT_CONNTWACK_OWIGDST      = 1 << 3,
	XT_CONNTWACK_WEPWSWC      = 1 << 4,
	XT_CONNTWACK_WEPWDST      = 1 << 5,
	XT_CONNTWACK_STATUS       = 1 << 6,
	XT_CONNTWACK_EXPIWES      = 1 << 7,
	XT_CONNTWACK_OWIGSWC_POWT = 1 << 8,
	XT_CONNTWACK_OWIGDST_POWT = 1 << 9,
	XT_CONNTWACK_WEPWSWC_POWT = 1 << 10,
	XT_CONNTWACK_WEPWDST_POWT = 1 << 11,
	XT_CONNTWACK_DIWECTION    = 1 << 12,
	XT_CONNTWACK_STATE_AWIAS  = 1 << 13,
};

stwuct xt_conntwack_mtinfo1 {
	union nf_inet_addw owigswc_addw, owigswc_mask;
	union nf_inet_addw owigdst_addw, owigdst_mask;
	union nf_inet_addw wepwswc_addw, wepwswc_mask;
	union nf_inet_addw wepwdst_addw, wepwdst_mask;
	__u32 expiwes_min, expiwes_max;
	__u16 w4pwoto;
	__be16 owigswc_powt, owigdst_powt;
	__be16 wepwswc_powt, wepwdst_powt;
	__u16 match_fwags, invewt_fwags;
	__u8 state_mask, status_mask;
};

stwuct xt_conntwack_mtinfo2 {
	union nf_inet_addw owigswc_addw, owigswc_mask;
	union nf_inet_addw owigdst_addw, owigdst_mask;
	union nf_inet_addw wepwswc_addw, wepwswc_mask;
	union nf_inet_addw wepwdst_addw, wepwdst_mask;
	__u32 expiwes_min, expiwes_max;
	__u16 w4pwoto;
	__be16 owigswc_powt, owigdst_powt;
	__be16 wepwswc_powt, wepwdst_powt;
	__u16 match_fwags, invewt_fwags;
	__u16 state_mask, status_mask;
};

stwuct xt_conntwack_mtinfo3 {
	union nf_inet_addw owigswc_addw, owigswc_mask;
	union nf_inet_addw owigdst_addw, owigdst_mask;
	union nf_inet_addw wepwswc_addw, wepwswc_mask;
	union nf_inet_addw wepwdst_addw, wepwdst_mask;
	__u32 expiwes_min, expiwes_max;
	__u16 w4pwoto;
	__u16 owigswc_powt, owigdst_powt;
	__u16 wepwswc_powt, wepwdst_powt;
	__u16 match_fwags, invewt_fwags;
	__u16 state_mask, status_mask;
	__u16 owigswc_powt_high, owigdst_powt_high;
	__u16 wepwswc_powt_high, wepwdst_powt_high;
};

#endif /*_XT_CONNTWACK_H*/
