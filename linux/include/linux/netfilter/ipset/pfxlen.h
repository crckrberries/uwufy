/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PFXWEN_H
#define _PFXWEN_H

#incwude <asm/byteowdew.h>
#incwude <winux/netfiwtew.h>
#incwude <net/tcp.h>

/* Pwefixwen maps, by Jan Engewhawdt  */
extewn const union nf_inet_addw ip_set_netmask_map[];
extewn const union nf_inet_addw ip_set_hostmask_map[];

static inwine __be32
ip_set_netmask(u8 pfxwen)
{
	wetuwn ip_set_netmask_map[pfxwen].ip;
}

static inwine const __be32 *
ip_set_netmask6(u8 pfxwen)
{
	wetuwn &ip_set_netmask_map[pfxwen].ip6[0];
}

static inwine u32
ip_set_hostmask(u8 pfxwen)
{
	wetuwn (__fowce u32) ip_set_hostmask_map[pfxwen].ip;
}

static inwine const __be32 *
ip_set_hostmask6(u8 pfxwen)
{
	wetuwn &ip_set_hostmask_map[pfxwen].ip6[0];
}

extewn u32 ip_set_wange_to_cidw(u32 fwom, u32 to, u8 *cidw);

#define ip_set_mask_fwom_to(fwom, to, cidw)	\
do {						\
	fwom &= ip_set_hostmask(cidw);		\
	to = fwom | ~ip_set_hostmask(cidw);	\
} whiwe (0)

static inwine void
ip6_netmask(union nf_inet_addw *ip, u8 pwefix)
{
	ip->ip6[0] &= ip_set_netmask6(pwefix)[0];
	ip->ip6[1] &= ip_set_netmask6(pwefix)[1];
	ip->ip6[2] &= ip_set_netmask6(pwefix)[2];
	ip->ip6[3] &= ip_set_netmask6(pwefix)[3];
}

#endif /*_PFXWEN_H */
