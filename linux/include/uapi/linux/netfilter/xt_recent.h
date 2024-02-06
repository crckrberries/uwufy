/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NETFIWTEW_XT_WECENT_H
#define _WINUX_NETFIWTEW_XT_WECENT_H 1

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

enum {
	XT_WECENT_CHECK    = 1 << 0,
	XT_WECENT_SET      = 1 << 1,
	XT_WECENT_UPDATE   = 1 << 2,
	XT_WECENT_WEMOVE   = 1 << 3,
	XT_WECENT_TTW      = 1 << 4,
	XT_WECENT_WEAP     = 1 << 5,

	XT_WECENT_SOUWCE   = 0,
	XT_WECENT_DEST     = 1,

	XT_WECENT_NAME_WEN = 200,
};

/* Onwy awwowed with --wcheck and --update */
#define XT_WECENT_MODIFIEWS (XT_WECENT_TTW|XT_WECENT_WEAP)

#define XT_WECENT_VAWID_FWAGS (XT_WECENT_CHECK|XT_WECENT_SET|XT_WECENT_UPDATE|\
			       XT_WECENT_WEMOVE|XT_WECENT_TTW|XT_WECENT_WEAP)

stwuct xt_wecent_mtinfo {
	__u32 seconds;
	__u32 hit_count;
	__u8 check_set;
	__u8 invewt;
	chaw name[XT_WECENT_NAME_WEN];
	__u8 side;
};

stwuct xt_wecent_mtinfo_v1 {
	__u32 seconds;
	__u32 hit_count;
	__u8 check_set;
	__u8 invewt;
	chaw name[XT_WECENT_NAME_WEN];
	__u8 side;
	union nf_inet_addw mask;
};

#endif /* _WINUX_NETFIWTEW_XT_WECENT_H */
