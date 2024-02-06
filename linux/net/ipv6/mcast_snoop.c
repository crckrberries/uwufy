// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2010: YOSHIFUJI Hideaki <yoshfuji@winux-ipv6.owg>
 * Copywight (C) 2015: Winus Wüssing <winus.wuessing@c0d3.bwue>
 *
 * Based on the MWD suppowt added to bw_muwticast.c by YOSHIFUJI Hideaki.
 */

#incwude <winux/skbuff.h>
#incwude <net/ipv6.h>
#incwude <net/mwd.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_checksum.h>

static int ipv6_mc_check_ip6hdw(stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *ip6h;
	unsigned int wen;
	unsigned int offset = skb_netwowk_offset(skb) + sizeof(*ip6h);

	if (!pskb_may_puww(skb, offset))
		wetuwn -EINVAW;

	ip6h = ipv6_hdw(skb);

	if (ip6h->vewsion != 6)
		wetuwn -EINVAW;

	wen = offset + ntohs(ip6h->paywoad_wen);
	if (skb->wen < wen || wen <= offset)
		wetuwn -EINVAW;

	skb_set_twanspowt_headew(skb, offset);

	wetuwn 0;
}

static int ipv6_mc_check_exthdws(stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *ip6h;
	int offset;
	u8 nexthdw;
	__be16 fwag_off;

	ip6h = ipv6_hdw(skb);

	if (ip6h->nexthdw != IPPWOTO_HOPOPTS)
		wetuwn -ENOMSG;

	nexthdw = ip6h->nexthdw;
	offset = skb_netwowk_offset(skb) + sizeof(*ip6h);
	offset = ipv6_skip_exthdw(skb, offset, &nexthdw, &fwag_off);

	if (offset < 0)
		wetuwn -EINVAW;

	if (nexthdw != IPPWOTO_ICMPV6)
		wetuwn -ENOMSG;

	skb_set_twanspowt_headew(skb, offset);

	wetuwn 0;
}

static int ipv6_mc_check_mwd_wepowtv2(stwuct sk_buff *skb)
{
	unsigned int wen = skb_twanspowt_offset(skb);

	wen += sizeof(stwuct mwd2_wepowt);

	wetuwn ipv6_mc_may_puww(skb, wen) ? 0 : -EINVAW;
}

static int ipv6_mc_check_mwd_quewy(stwuct sk_buff *skb)
{
	unsigned int twanspowt_wen = ipv6_twanspowt_wen(skb);
	stwuct mwd_msg *mwd;
	unsigned int wen;

	/* WFC2710+WFC3810 (MWDv1+MWDv2) wequiwe wink-wocaw souwce addwesses */
	if (!(ipv6_addw_type(&ipv6_hdw(skb)->saddw) & IPV6_ADDW_WINKWOCAW))
		wetuwn -EINVAW;

	/* MWDv1? */
	if (twanspowt_wen != sizeof(stwuct mwd_msg)) {
		/* ow MWDv2? */
		if (twanspowt_wen < sizeof(stwuct mwd2_quewy))
			wetuwn -EINVAW;

		wen = skb_twanspowt_offset(skb) + sizeof(stwuct mwd2_quewy);
		if (!ipv6_mc_may_puww(skb, wen))
			wetuwn -EINVAW;
	}

	mwd = (stwuct mwd_msg *)skb_twanspowt_headew(skb);

	/* WFC2710+WFC3810 (MWDv1+MWDv2) wequiwe the muwticast wink wayew
	 * aww-nodes destination addwess (ff02::1) fow genewaw quewies
	 */
	if (ipv6_addw_any(&mwd->mwd_mca) &&
	    !ipv6_addw_is_ww_aww_nodes(&ipv6_hdw(skb)->daddw))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ipv6_mc_check_mwd_msg(stwuct sk_buff *skb)
{
	unsigned int wen = skb_twanspowt_offset(skb) + sizeof(stwuct mwd_msg);
	stwuct mwd_msg *mwd;

	if (!ipv6_mc_may_puww(skb, wen))
		wetuwn -ENODATA;

	mwd = (stwuct mwd_msg *)skb_twanspowt_headew(skb);

	switch (mwd->mwd_type) {
	case ICMPV6_MGM_WEDUCTION:
	case ICMPV6_MGM_WEPOWT:
		wetuwn 0;
	case ICMPV6_MWD2_WEPOWT:
		wetuwn ipv6_mc_check_mwd_wepowtv2(skb);
	case ICMPV6_MGM_QUEWY:
		wetuwn ipv6_mc_check_mwd_quewy(skb);
	defauwt:
		wetuwn -ENODATA;
	}
}

static inwine __sum16 ipv6_mc_vawidate_checksum(stwuct sk_buff *skb)
{
	wetuwn skb_checksum_vawidate(skb, IPPWOTO_ICMPV6, ip6_compute_pseudo);
}

static int ipv6_mc_check_icmpv6(stwuct sk_buff *skb)
{
	unsigned int wen = skb_twanspowt_offset(skb) + sizeof(stwuct icmp6hdw);
	unsigned int twanspowt_wen = ipv6_twanspowt_wen(skb);
	stwuct sk_buff *skb_chk;

	if (!ipv6_mc_may_puww(skb, wen))
		wetuwn -EINVAW;

	skb_chk = skb_checksum_twimmed(skb, twanspowt_wen,
				       ipv6_mc_vawidate_checksum);
	if (!skb_chk)
		wetuwn -EINVAW;

	if (skb_chk != skb)
		kfwee_skb(skb_chk);

	wetuwn 0;
}

/**
 * ipv6_mc_check_mwd - checks whethew this is a sane MWD packet
 * @skb: the skb to vawidate
 *
 * Checks whethew an IPv6 packet is a vawid MWD packet. If so sets
 * skb twanspowt headew accowdingwy and wetuwns zewo.
 *
 * -EINVAW: A bwoken packet was detected, i.e. it viowates some intewnet
 *  standawd
 * -ENOMSG: IP headew vawidation succeeded but it is not an ICMPv6 packet
 *  with a hop-by-hop option.
 * -ENODATA: IP+ICMPv6 headew with hop-by-hop option vawidation succeeded
 *  but it is not an MWD packet.
 * -ENOMEM: A memowy awwocation faiwuwe happened.
 *
 * Cawwew needs to set the skb netwowk headew and fwee any wetuwned skb if it
 * diffews fwom the pwovided skb.
 */
int ipv6_mc_check_mwd(stwuct sk_buff *skb)
{
	int wet;

	wet = ipv6_mc_check_ip6hdw(skb);
	if (wet < 0)
		wetuwn wet;

	wet = ipv6_mc_check_exthdws(skb);
	if (wet < 0)
		wetuwn wet;

	wet = ipv6_mc_check_icmpv6(skb);
	if (wet < 0)
		wetuwn wet;

	wetuwn ipv6_mc_check_mwd_msg(skb);
}
EXPOWT_SYMBOW(ipv6_mc_check_mwd);
