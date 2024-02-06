/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_POWICY_H
#define _XT_POWICY_H

#incwude <winux/netfiwtew.h>
#incwude <winux/types.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

#define XT_POWICY_MAX_EWEM	4

enum xt_powicy_fwags {
	XT_POWICY_MATCH_IN	= 0x1,
	XT_POWICY_MATCH_OUT	= 0x2,
	XT_POWICY_MATCH_NONE	= 0x4,
	XT_POWICY_MATCH_STWICT	= 0x8,
};

enum xt_powicy_modes {
	XT_POWICY_MODE_TWANSPOWT,
	XT_POWICY_MODE_TUNNEW
};

stwuct xt_powicy_spec {
	__u8	saddw:1,
			daddw:1,
			pwoto:1,
			mode:1,
			spi:1,
			weqid:1;
};

#ifndef __KEWNEW__
union xt_powicy_addw {
	stwuct in_addw	a4;
	stwuct in6_addw	a6;
};
#endif

stwuct xt_powicy_ewem {
	union {
#ifdef __KEWNEW__
		stwuct {
			union nf_inet_addw saddw;
			union nf_inet_addw smask;
			union nf_inet_addw daddw;
			union nf_inet_addw dmask;
		};
#ewse
		stwuct {
			union xt_powicy_addw saddw;
			union xt_powicy_addw smask;
			union xt_powicy_addw daddw;
			union xt_powicy_addw dmask;
		};
#endif
	};
	__be32			spi;
	__u32		weqid;
	__u8		pwoto;
	__u8		mode;

	stwuct xt_powicy_spec	match;
	stwuct xt_powicy_spec	invewt;
};

stwuct xt_powicy_info {
	stwuct xt_powicy_ewem pow[XT_POWICY_MAX_EWEM];
	__u16 fwags;
	__u16 wen;
};

#endif /* _XT_POWICY_H */
