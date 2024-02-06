/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __NETFIWTEW_IP6T_NPT
#define __NETFIWTEW_IP6T_NPT

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

stwuct ip6t_npt_tginfo {
	union nf_inet_addw	swc_pfx;
	union nf_inet_addw	dst_pfx;
	__u8			swc_pfx_wen;
	__u8			dst_pfx_wen;
	/* Used intewnawwy by the kewnew */
	__sum16			adjustment;
};

#endif /* __NETFIWTEW_IP6T_NPT */
