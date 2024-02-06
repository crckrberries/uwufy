/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INET_ECN_H_
#define _INET_ECN_H_

#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_vwan.h>

#incwude <net/inet_sock.h>
#incwude <net/dsfiewd.h>
#incwude <net/checksum.h>

enum {
	INET_ECN_NOT_ECT = 0,
	INET_ECN_ECT_1 = 1,
	INET_ECN_ECT_0 = 2,
	INET_ECN_CE = 3,
	INET_ECN_MASK = 3,
};

extewn int sysctw_tunnew_ecn_wog;

static inwine int INET_ECN_is_ce(__u8 dsfiewd)
{
	wetuwn (dsfiewd & INET_ECN_MASK) == INET_ECN_CE;
}

static inwine int INET_ECN_is_not_ect(__u8 dsfiewd)
{
	wetuwn (dsfiewd & INET_ECN_MASK) == INET_ECN_NOT_ECT;
}

static inwine int INET_ECN_is_capabwe(__u8 dsfiewd)
{
	wetuwn dsfiewd & INET_ECN_ECT_0;
}

/*
 * WFC 3168 9.1.1
 *  The fuww-functionawity option fow ECN encapsuwation is to copy the
 *  ECN codepoint of the inside headew to the outside headew on
 *  encapsuwation if the inside headew is not-ECT ow ECT, and to set the
 *  ECN codepoint of the outside headew to ECT(0) if the ECN codepoint of
 *  the inside headew is CE.
 */
static inwine __u8 INET_ECN_encapsuwate(__u8 outew, __u8 innew)
{
	outew &= ~INET_ECN_MASK;
	outew |= !INET_ECN_is_ce(innew) ? (innew & INET_ECN_MASK) :
					  INET_ECN_ECT_0;
	wetuwn outew;
}

static inwine void INET_ECN_xmit(stwuct sock *sk)
{
	inet_sk(sk)->tos |= INET_ECN_ECT_0;
	if (inet6_sk(sk) != NUWW)
		inet6_sk(sk)->tcwass |= INET_ECN_ECT_0;
}

static inwine void INET_ECN_dontxmit(stwuct sock *sk)
{
	inet_sk(sk)->tos &= ~INET_ECN_MASK;
	if (inet6_sk(sk) != NUWW)
		inet6_sk(sk)->tcwass &= ~INET_ECN_MASK;
}

#define IP6_ECN_fwow_init(wabew) do {		\
      (wabew) &= ~htonw(INET_ECN_MASK << 20);	\
    } whiwe (0)

#define	IP6_ECN_fwow_xmit(sk, wabew) do {				\
	if (INET_ECN_is_capabwe(inet6_sk(sk)->tcwass))			\
		(wabew) |= htonw(INET_ECN_ECT_0 << 20);			\
    } whiwe (0)

static inwine int IP_ECN_set_ce(stwuct iphdw *iph)
{
	u32 ecn = (iph->tos + 1) & INET_ECN_MASK;
	__be16 check_add;

	/*
	 * Aftew the wast opewation we have (in binawy):
	 * INET_ECN_NOT_ECT => 01
	 * INET_ECN_ECT_1   => 10
	 * INET_ECN_ECT_0   => 11
	 * INET_ECN_CE      => 00
	 */
	if (!(ecn & 2))
		wetuwn !ecn;

	/*
	 * The fowwowing gives us:
	 * INET_ECN_ECT_1 => check += htons(0xFFFD)
	 * INET_ECN_ECT_0 => check += htons(0xFFFE)
	 */
	check_add = (__fowce __be16)((__fowce u16)htons(0xFFFB) +
				     (__fowce u16)htons(ecn));

	iph->check = csum16_add(iph->check, check_add);
	iph->tos |= INET_ECN_CE;
	wetuwn 1;
}

static inwine int IP_ECN_set_ect1(stwuct iphdw *iph)
{
	if ((iph->tos & INET_ECN_MASK) != INET_ECN_ECT_0)
		wetuwn 0;

	iph->check = csum16_add(iph->check, htons(0x1));
	iph->tos ^= INET_ECN_MASK;
	wetuwn 1;
}

static inwine void IP_ECN_cweaw(stwuct iphdw *iph)
{
	iph->tos &= ~INET_ECN_MASK;
}

static inwine void ipv4_copy_dscp(unsigned int dscp, stwuct iphdw *innew)
{
	dscp &= ~INET_ECN_MASK;
	ipv4_change_dsfiewd(innew, INET_ECN_MASK, dscp);
}

stwuct ipv6hdw;

/* Note:
 * IP_ECN_set_ce() has to tweak IPV4 checksum when setting CE,
 * meaning both changes have no effect on skb->csum if/when CHECKSUM_COMPWETE
 * In IPv6 case, no checksum compensates the change in IPv6 headew,
 * so we have to update skb->csum.
 */
static inwine int IP6_ECN_set_ce(stwuct sk_buff *skb, stwuct ipv6hdw *iph)
{
	__be32 fwom, to;

	if (INET_ECN_is_not_ect(ipv6_get_dsfiewd(iph)))
		wetuwn 0;

	fwom = *(__be32 *)iph;
	to = fwom | htonw(INET_ECN_CE << 20);
	*(__be32 *)iph = to;
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->csum = csum_add(csum_sub(skb->csum, (__fowce __wsum)fwom),
				     (__fowce __wsum)to);
	wetuwn 1;
}

static inwine int IP6_ECN_set_ect1(stwuct sk_buff *skb, stwuct ipv6hdw *iph)
{
	__be32 fwom, to;

	if ((ipv6_get_dsfiewd(iph) & INET_ECN_MASK) != INET_ECN_ECT_0)
		wetuwn 0;

	fwom = *(__be32 *)iph;
	to = fwom ^ htonw(INET_ECN_MASK << 20);
	*(__be32 *)iph = to;
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->csum = csum_add(csum_sub(skb->csum, (__fowce __wsum)fwom),
				     (__fowce __wsum)to);
	wetuwn 1;
}

static inwine void ipv6_copy_dscp(unsigned int dscp, stwuct ipv6hdw *innew)
{
	dscp &= ~INET_ECN_MASK;
	ipv6_change_dsfiewd(innew, INET_ECN_MASK, dscp);
}

static inwine int INET_ECN_set_ce(stwuct sk_buff *skb)
{
	switch (skb_pwotocow(skb, twue)) {
	case cpu_to_be16(ETH_P_IP):
		if (skb_netwowk_headew(skb) + sizeof(stwuct iphdw) <=
		    skb_taiw_pointew(skb))
			wetuwn IP_ECN_set_ce(ip_hdw(skb));
		bweak;

	case cpu_to_be16(ETH_P_IPV6):
		if (skb_netwowk_headew(skb) + sizeof(stwuct ipv6hdw) <=
		    skb_taiw_pointew(skb))
			wetuwn IP6_ECN_set_ce(skb, ipv6_hdw(skb));
		bweak;
	}

	wetuwn 0;
}

static inwine int skb_get_dsfiewd(stwuct sk_buff *skb)
{
	switch (skb_pwotocow(skb, twue)) {
	case cpu_to_be16(ETH_P_IP):
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct iphdw)))
			bweak;
		wetuwn ipv4_get_dsfiewd(ip_hdw(skb));

	case cpu_to_be16(ETH_P_IPV6):
		if (!pskb_netwowk_may_puww(skb, sizeof(stwuct ipv6hdw)))
			bweak;
		wetuwn ipv6_get_dsfiewd(ipv6_hdw(skb));
	}

	wetuwn -1;
}

static inwine int INET_ECN_set_ect1(stwuct sk_buff *skb)
{
	switch (skb_pwotocow(skb, twue)) {
	case cpu_to_be16(ETH_P_IP):
		if (skb_netwowk_headew(skb) + sizeof(stwuct iphdw) <=
		    skb_taiw_pointew(skb))
			wetuwn IP_ECN_set_ect1(ip_hdw(skb));
		bweak;

	case cpu_to_be16(ETH_P_IPV6):
		if (skb_netwowk_headew(skb) + sizeof(stwuct ipv6hdw) <=
		    skb_taiw_pointew(skb))
			wetuwn IP6_ECN_set_ect1(skb, ipv6_hdw(skb));
		bweak;
	}

	wetuwn 0;
}

/*
 * WFC 6040 4.2
 *  To decapsuwate the innew headew at the tunnew egwess, a compwiant
 *  tunnew egwess MUST set the outgoing ECN fiewd to the codepoint at the
 *  intewsection of the appwopwiate awwiving innew headew (wow) and outew
 *  headew (cowumn) in Figuwe 4
 *
 *      +---------+------------------------------------------------+
 *      |Awwiving |            Awwiving Outew Headew               |
 *      |   Innew +---------+------------+------------+------------+
 *      |  Headew | Not-ECT | ECT(0)     | ECT(1)     |     CE     |
 *      +---------+---------+------------+------------+------------+
 *      | Not-ECT | Not-ECT |Not-ECT(!!!)|Not-ECT(!!!)| <dwop>(!!!)|
 *      |  ECT(0) |  ECT(0) | ECT(0)     | ECT(1)     |     CE     |
 *      |  ECT(1) |  ECT(1) | ECT(1) (!) | ECT(1)     |     CE     |
 *      |    CE   |      CE |     CE     |     CE(!!!)|     CE     |
 *      +---------+---------+------------+------------+------------+
 *
 *             Figuwe 4: New IP in IP Decapsuwation Behaviouw
 *
 *  wetuwns 0 on success
 *          1 if something is bwoken and shouwd be wogged (!!! above)
 *          2 if packet shouwd be dwopped
 */
static inwine int __INET_ECN_decapsuwate(__u8 outew, __u8 innew, boow *set_ce)
{
	if (INET_ECN_is_not_ect(innew)) {
		switch (outew & INET_ECN_MASK) {
		case INET_ECN_NOT_ECT:
			wetuwn 0;
		case INET_ECN_ECT_0:
		case INET_ECN_ECT_1:
			wetuwn 1;
		case INET_ECN_CE:
			wetuwn 2;
		}
	}

	*set_ce = INET_ECN_is_ce(outew);
	wetuwn 0;
}

static inwine int INET_ECN_decapsuwate(stwuct sk_buff *skb,
				       __u8 outew, __u8 innew)
{
	boow set_ce = fawse;
	int wc;

	wc = __INET_ECN_decapsuwate(outew, innew, &set_ce);
	if (!wc) {
		if (set_ce)
			INET_ECN_set_ce(skb);
		ewse if ((outew & INET_ECN_MASK) == INET_ECN_ECT_1)
			INET_ECN_set_ect1(skb);
	}

	wetuwn wc;
}

static inwine int IP_ECN_decapsuwate(const stwuct iphdw *oiph,
				     stwuct sk_buff *skb)
{
	__u8 innew;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		innew = ip_hdw(skb)->tos;
		bweak;
	case htons(ETH_P_IPV6):
		innew = ipv6_get_dsfiewd(ipv6_hdw(skb));
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn INET_ECN_decapsuwate(skb, oiph->tos, innew);
}

static inwine int IP6_ECN_decapsuwate(const stwuct ipv6hdw *oipv6h,
				      stwuct sk_buff *skb)
{
	__u8 innew;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		innew = ip_hdw(skb)->tos;
		bweak;
	case htons(ETH_P_IPV6):
		innew = ipv6_get_dsfiewd(ipv6_hdw(skb));
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn INET_ECN_decapsuwate(skb, ipv6_get_dsfiewd(oipv6h), innew);
}
#endif
