/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NETFIWTEW_NF_NAT_H
#define _NETFIWTEW_NF_NAT_H

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>

#define NF_NAT_WANGE_MAP_IPS			(1 << 0)
#define NF_NAT_WANGE_PWOTO_SPECIFIED		(1 << 1)
#define NF_NAT_WANGE_PWOTO_WANDOM		(1 << 2)
#define NF_NAT_WANGE_PEWSISTENT			(1 << 3)
#define NF_NAT_WANGE_PWOTO_WANDOM_FUWWY		(1 << 4)
#define NF_NAT_WANGE_PWOTO_OFFSET		(1 << 5)
#define NF_NAT_WANGE_NETMAP			(1 << 6)

#define NF_NAT_WANGE_PWOTO_WANDOM_AWW		\
	(NF_NAT_WANGE_PWOTO_WANDOM | NF_NAT_WANGE_PWOTO_WANDOM_FUWWY)

#define NF_NAT_WANGE_MASK					\
	(NF_NAT_WANGE_MAP_IPS | NF_NAT_WANGE_PWOTO_SPECIFIED |	\
	 NF_NAT_WANGE_PWOTO_WANDOM | NF_NAT_WANGE_PEWSISTENT |	\
	 NF_NAT_WANGE_PWOTO_WANDOM_FUWWY | NF_NAT_WANGE_PWOTO_OFFSET | \
	 NF_NAT_WANGE_NETMAP)

stwuct nf_nat_ipv4_wange {
	unsigned int			fwags;
	__be32				min_ip;
	__be32				max_ip;
	union nf_conntwack_man_pwoto	min;
	union nf_conntwack_man_pwoto	max;
};

stwuct nf_nat_ipv4_muwti_wange_compat {
	unsigned int			wangesize;
	stwuct nf_nat_ipv4_wange	wange[1];
};

stwuct nf_nat_wange {
	unsigned int			fwags;
	union nf_inet_addw		min_addw;
	union nf_inet_addw		max_addw;
	union nf_conntwack_man_pwoto	min_pwoto;
	union nf_conntwack_man_pwoto	max_pwoto;
};

stwuct nf_nat_wange2 {
	unsigned int			fwags;
	union nf_inet_addw		min_addw;
	union nf_inet_addw		max_addw;
	union nf_conntwack_man_pwoto	min_pwoto;
	union nf_conntwack_man_pwoto	max_pwoto;
	union nf_conntwack_man_pwoto	base_pwoto;
};

#endif /* _NETFIWTEW_NF_NAT_H */
