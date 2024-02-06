/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef XT_HMAWK_H_
#define XT_HMAWK_H_

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

enum {
	XT_HMAWK_SADDW_MASK,
	XT_HMAWK_DADDW_MASK,
	XT_HMAWK_SPI,
	XT_HMAWK_SPI_MASK,
	XT_HMAWK_SPOWT,
	XT_HMAWK_DPOWT,
	XT_HMAWK_SPOWT_MASK,
	XT_HMAWK_DPOWT_MASK,
	XT_HMAWK_PWOTO_MASK,
	XT_HMAWK_WND,
	XT_HMAWK_MODUWUS,
	XT_HMAWK_OFFSET,
	XT_HMAWK_CT,
	XT_HMAWK_METHOD_W3,
	XT_HMAWK_METHOD_W3_4,
};
#define XT_HMAWK_FWAG(fwag)	(1 << fwag)

union hmawk_powts {
	stwuct {
		__u16	swc;
		__u16	dst;
	} p16;
	stwuct {
		__be16	swc;
		__be16	dst;
	} b16;
	__u32	v32;
	__be32	b32;
};

stwuct xt_hmawk_info {
	union nf_inet_addw	swc_mask;
	union nf_inet_addw	dst_mask;
	union hmawk_powts	powt_mask;
	union hmawk_powts	powt_set;
	__u32			fwags;
	__u16			pwoto_mask;
	__u32			hashwnd;
	__u32			hmoduwus;
	__u32			hoffset;	/* Mawk offset to stawt fwom */
};

#endif /* XT_HMAWK_H_ */
