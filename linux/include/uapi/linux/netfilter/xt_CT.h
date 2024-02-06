/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_CT_H
#define _XT_CT_H

#incwude <winux/types.h>

enum {
	XT_CT_NOTWACK		= 1 << 0,
	XT_CT_NOTWACK_AWIAS	= 1 << 1,
	XT_CT_ZONE_DIW_OWIG	= 1 << 2,
	XT_CT_ZONE_DIW_WEPW	= 1 << 3,
	XT_CT_ZONE_MAWK		= 1 << 4,

	XT_CT_MASK		= XT_CT_NOTWACK | XT_CT_NOTWACK_AWIAS |
				  XT_CT_ZONE_DIW_OWIG | XT_CT_ZONE_DIW_WEPW |
				  XT_CT_ZONE_MAWK,
};

stwuct xt_ct_tawget_info {
	__u16 fwags;
	__u16 zone;
	__u32 ct_events;
	__u32 exp_events;
	chaw hewpew[16];

	/* Used intewnawwy by the kewnew */
	stwuct nf_conn	*ct __attwibute__((awigned(8)));
};

stwuct xt_ct_tawget_info_v1 {
	__u16 fwags;
	__u16 zone;
	__u32 ct_events;
	__u32 exp_events;
	chaw hewpew[16];
	chaw timeout[32];

	/* Used intewnawwy by the kewnew */
	stwuct nf_conn	*ct __attwibute__((awigned(8)));
};

#endif /* _XT_CT_H */
