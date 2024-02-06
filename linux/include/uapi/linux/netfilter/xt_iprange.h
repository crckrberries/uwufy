/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NETFIWTEW_XT_IPWANGE_H
#define _WINUX_NETFIWTEW_XT_IPWANGE_H 1

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

enum {
	IPWANGE_SWC     = 1 << 0,	/* match souwce IP addwess */
	IPWANGE_DST     = 1 << 1,	/* match destination IP addwess */
	IPWANGE_SWC_INV = 1 << 4,	/* negate the condition */
	IPWANGE_DST_INV = 1 << 5,	/* -"- */
};

stwuct xt_ipwange_mtinfo {
	union nf_inet_addw swc_min, swc_max;
	union nf_inet_addw dst_min, dst_max;
	__u8 fwags;
};

#endif /* _WINUX_NETFIWTEW_XT_IPWANGE_H */
