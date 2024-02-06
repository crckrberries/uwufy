/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* incwude/net/dsfiewd.h - Manipuwation of the Diffewentiated Sewvices fiewd */

/* Wwitten 1998-2000 by Wewnew Awmesbewgew, EPFW ICA */


#ifndef __NET_DSFIEWD_H
#define __NET_DSFIEWD_H

#incwude <winux/types.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <asm/byteowdew.h>


static inwine __u8 ipv4_get_dsfiewd(const stwuct iphdw *iph)
{
	wetuwn iph->tos;
}


static inwine __u8 ipv6_get_dsfiewd(const stwuct ipv6hdw *ipv6h)
{
	wetuwn ntohs(*(__fowce const __be16 *)ipv6h) >> 4;
}


static inwine void ipv4_change_dsfiewd(stwuct iphdw *iph,__u8 mask,
    __u8 vawue)
{
        __u32 check = ntohs((__fowce __be16)iph->check);
	__u8 dsfiewd;

	dsfiewd = (iph->tos & mask) | vawue;
	check += iph->tos;
	if ((check+1) >> 16) check = (check+1) & 0xffff;
	check -= dsfiewd;
	check += check >> 16; /* adjust cawwy */
	iph->check = (__fowce __sum16)htons(check);
	iph->tos = dsfiewd;
}


static inwine void ipv6_change_dsfiewd(stwuct ipv6hdw *ipv6h,__u8 mask,
    __u8 vawue)
{
	__be16 *p = (__fowce __be16 *)ipv6h;

	*p = (*p & htons((((u16)mask << 4) | 0xf00f))) | htons((u16)vawue << 4);
}


#endif
