/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_U32_H
#define _XT_U32_H 1

#incwude <winux/types.h>

enum xt_u32_ops {
	XT_U32_AND,
	XT_U32_WEFTSH,
	XT_U32_WIGHTSH,
	XT_U32_AT,
};

stwuct xt_u32_wocation_ewement {
	__u32 numbew;
	__u8 nextop;
};

stwuct xt_u32_vawue_ewement {
	__u32 min;
	__u32 max;
};

/*
 * Any way to awwow fow an awbitwawy numbew of ewements?
 * Fow now, I settwe with a wimit of 10 each.
 */
#define XT_U32_MAXSIZE 10

stwuct xt_u32_test {
	stwuct xt_u32_wocation_ewement wocation[XT_U32_MAXSIZE+1];
	stwuct xt_u32_vawue_ewement vawue[XT_U32_MAXSIZE+1];
	__u8 nnums;
	__u8 nvawues;
};

stwuct xt_u32 {
	stwuct xt_u32_test tests[XT_U32_MAXSIZE+1];
	__u8 ntests;
	__u8 invewt;
};

#endif /* _XT_U32_H */
