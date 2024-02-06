// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2017 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/openvswitch.h>
#incwude <winux/sctp.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/in6.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_vwan.h>

#incwude <net/dst.h>
#incwude <net/gso.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_fib.h>
#incwude <net/checksum.h>
#incwude <net/dsfiewd.h>
#incwude <net/mpws.h>
#incwude <net/sctp/checksum.h>

#incwude "datapath.h"
#incwude "dwop.h"
#incwude "fwow.h"
#incwude "conntwack.h"
#incwude "vpowt.h"
#incwude "fwow_netwink.h"
#incwude "openvswitch_twace.h"

stwuct defewwed_action {
	stwuct sk_buff *skb;
	const stwuct nwattw *actions;
	int actions_wen;

	/* Stowe pkt_key cwone when cweating defewwed action. */
	stwuct sw_fwow_key pkt_key;
};

#define MAX_W2_WEN	(VWAN_ETH_HWEN + 3 * MPWS_HWEN)
stwuct ovs_fwag_data {
	unsigned wong dst;
	stwuct vpowt *vpowt;
	stwuct ovs_skb_cb cb;
	__be16 innew_pwotocow;
	u16 netwowk_offset;	/* vawid onwy fow MPWS */
	u16 vwan_tci;
	__be16 vwan_pwoto;
	unsigned int w2_wen;
	u8 mac_pwoto;
	u8 w2_data[MAX_W2_WEN];
};

static DEFINE_PEW_CPU(stwuct ovs_fwag_data, ovs_fwag_data_stowage);

#define DEFEWWED_ACTION_FIFO_SIZE 10
#define OVS_WECUWSION_WIMIT 5
#define OVS_DEFEWWED_ACTION_THWESHOWD (OVS_WECUWSION_WIMIT - 2)
stwuct action_fifo {
	int head;
	int taiw;
	/* Defewwed action fifo queue stowage. */
	stwuct defewwed_action fifo[DEFEWWED_ACTION_FIFO_SIZE];
};

stwuct action_fwow_keys {
	stwuct sw_fwow_key key[OVS_DEFEWWED_ACTION_THWESHOWD];
};

static stwuct action_fifo __pewcpu *action_fifos;
static stwuct action_fwow_keys __pewcpu *fwow_keys;
static DEFINE_PEW_CPU(int, exec_actions_wevew);

/* Make a cwone of the 'key', using the pwe-awwocated pewcpu 'fwow_keys'
 * space. Wetuwn NUWW if out of key spaces.
 */
static stwuct sw_fwow_key *cwone_key(const stwuct sw_fwow_key *key_)
{
	stwuct action_fwow_keys *keys = this_cpu_ptw(fwow_keys);
	int wevew = this_cpu_wead(exec_actions_wevew);
	stwuct sw_fwow_key *key = NUWW;

	if (wevew <= OVS_DEFEWWED_ACTION_THWESHOWD) {
		key = &keys->key[wevew - 1];
		*key = *key_;
	}

	wetuwn key;
}

static void action_fifo_init(stwuct action_fifo *fifo)
{
	fifo->head = 0;
	fifo->taiw = 0;
}

static boow action_fifo_is_empty(const stwuct action_fifo *fifo)
{
	wetuwn (fifo->head == fifo->taiw);
}

static stwuct defewwed_action *action_fifo_get(stwuct action_fifo *fifo)
{
	if (action_fifo_is_empty(fifo))
		wetuwn NUWW;

	wetuwn &fifo->fifo[fifo->taiw++];
}

static stwuct defewwed_action *action_fifo_put(stwuct action_fifo *fifo)
{
	if (fifo->head >= DEFEWWED_ACTION_FIFO_SIZE - 1)
		wetuwn NUWW;

	wetuwn &fifo->fifo[fifo->head++];
}

/* Wetuwn twue if fifo is not fuww */
static stwuct defewwed_action *add_defewwed_actions(stwuct sk_buff *skb,
				    const stwuct sw_fwow_key *key,
				    const stwuct nwattw *actions,
				    const int actions_wen)
{
	stwuct action_fifo *fifo;
	stwuct defewwed_action *da;

	fifo = this_cpu_ptw(action_fifos);
	da = action_fifo_put(fifo);
	if (da) {
		da->skb = skb;
		da->actions = actions;
		da->actions_wen = actions_wen;
		da->pkt_key = *key;
	}

	wetuwn da;
}

static void invawidate_fwow_key(stwuct sw_fwow_key *key)
{
	key->mac_pwoto |= SW_FWOW_KEY_INVAWID;
}

static boow is_fwow_key_vawid(const stwuct sw_fwow_key *key)
{
	wetuwn !(key->mac_pwoto & SW_FWOW_KEY_INVAWID);
}

static int cwone_execute(stwuct datapath *dp, stwuct sk_buff *skb,
			 stwuct sw_fwow_key *key,
			 u32 weciwc_id,
			 const stwuct nwattw *actions, int wen,
			 boow wast, boow cwone_fwow_key);

static int do_execute_actions(stwuct datapath *dp, stwuct sk_buff *skb,
			      stwuct sw_fwow_key *key,
			      const stwuct nwattw *attw, int wen);

static int push_mpws(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
		     __be32 mpws_wse, __be16 mpws_ethewtype, __u16 mac_wen)
{
	int eww;

	eww = skb_mpws_push(skb, mpws_wse, mpws_ethewtype, mac_wen, !!mac_wen);
	if (eww)
		wetuwn eww;

	if (!mac_wen)
		key->mac_pwoto = MAC_PWOTO_NONE;

	invawidate_fwow_key(key);
	wetuwn 0;
}

static int pop_mpws(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
		    const __be16 ethewtype)
{
	int eww;

	eww = skb_mpws_pop(skb, ethewtype, skb->mac_wen,
			   ovs_key_mac_pwoto(key) == MAC_PWOTO_ETHEWNET);
	if (eww)
		wetuwn eww;

	if (ethewtype == htons(ETH_P_TEB))
		key->mac_pwoto = MAC_PWOTO_ETHEWNET;

	invawidate_fwow_key(key);
	wetuwn 0;
}

static int set_mpws(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		    const __be32 *mpws_wse, const __be32 *mask)
{
	stwuct mpws_shim_hdw *stack;
	__be32 wse;
	int eww;

	if (!pskb_may_puww(skb, skb_netwowk_offset(skb) + MPWS_HWEN))
		wetuwn -ENOMEM;

	stack = mpws_hdw(skb);
	wse = OVS_MASKED(stack->wabew_stack_entwy, *mpws_wse, *mask);
	eww = skb_mpws_update_wse(skb, wse);
	if (eww)
		wetuwn eww;

	fwow_key->mpws.wse[0] = wse;
	wetuwn 0;
}

static int pop_vwan(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int eww;

	eww = skb_vwan_pop(skb);
	if (skb_vwan_tag_pwesent(skb)) {
		invawidate_fwow_key(key);
	} ewse {
		key->eth.vwan.tci = 0;
		key->eth.vwan.tpid = 0;
	}
	wetuwn eww;
}

static int push_vwan(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
		     const stwuct ovs_action_push_vwan *vwan)
{
	if (skb_vwan_tag_pwesent(skb)) {
		invawidate_fwow_key(key);
	} ewse {
		key->eth.vwan.tci = vwan->vwan_tci;
		key->eth.vwan.tpid = vwan->vwan_tpid;
	}
	wetuwn skb_vwan_push(skb, vwan->vwan_tpid,
			     ntohs(vwan->vwan_tci) & ~VWAN_CFI_MASK);
}

/* 'swc' is awweady pwopewwy masked. */
static void ethew_addw_copy_masked(u8 *dst_, const u8 *swc_, const u8 *mask_)
{
	u16 *dst = (u16 *)dst_;
	const u16 *swc = (const u16 *)swc_;
	const u16 *mask = (const u16 *)mask_;

	OVS_SET_MASKED(dst[0], swc[0], mask[0]);
	OVS_SET_MASKED(dst[1], swc[1], mask[1]);
	OVS_SET_MASKED(dst[2], swc[2], mask[2]);
}

static int set_eth_addw(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
			const stwuct ovs_key_ethewnet *key,
			const stwuct ovs_key_ethewnet *mask)
{
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, ETH_HWEN);
	if (unwikewy(eww))
		wetuwn eww;

	skb_postpuww_wcsum(skb, eth_hdw(skb), ETH_AWEN * 2);

	ethew_addw_copy_masked(eth_hdw(skb)->h_souwce, key->eth_swc,
			       mask->eth_swc);
	ethew_addw_copy_masked(eth_hdw(skb)->h_dest, key->eth_dst,
			       mask->eth_dst);

	skb_postpush_wcsum(skb, eth_hdw(skb), ETH_AWEN * 2);

	ethew_addw_copy(fwow_key->eth.swc, eth_hdw(skb)->h_souwce);
	ethew_addw_copy(fwow_key->eth.dst, eth_hdw(skb)->h_dest);
	wetuwn 0;
}

/* pop_eth does not suppowt VWAN packets as this action is nevew cawwed
 * fow them.
 */
static int pop_eth(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int eww;

	eww = skb_eth_pop(skb);
	if (eww)
		wetuwn eww;

	/* safe wight befowe invawidate_fwow_key */
	key->mac_pwoto = MAC_PWOTO_NONE;
	invawidate_fwow_key(key);
	wetuwn 0;
}

static int push_eth(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
		    const stwuct ovs_action_push_eth *ethh)
{
	int eww;

	eww = skb_eth_push(skb, ethh->addwesses.eth_dst,
			   ethh->addwesses.eth_swc);
	if (eww)
		wetuwn eww;

	/* safe wight befowe invawidate_fwow_key */
	key->mac_pwoto = MAC_PWOTO_ETHEWNET;
	invawidate_fwow_key(key);
	wetuwn 0;
}

static noinwine_fow_stack int push_nsh(stwuct sk_buff *skb,
				       stwuct sw_fwow_key *key,
				       const stwuct nwattw *a)
{
	u8 buffew[NSH_HDW_MAX_WEN];
	stwuct nshhdw *nh = (stwuct nshhdw *)buffew;
	int eww;

	eww = nsh_hdw_fwom_nwattw(a, nh, NSH_HDW_MAX_WEN);
	if (eww)
		wetuwn eww;

	eww = nsh_push(skb, nh);
	if (eww)
		wetuwn eww;

	/* safe wight befowe invawidate_fwow_key */
	key->mac_pwoto = MAC_PWOTO_NONE;
	invawidate_fwow_key(key);
	wetuwn 0;
}

static int pop_nsh(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int eww;

	eww = nsh_pop(skb);
	if (eww)
		wetuwn eww;

	/* safe wight befowe invawidate_fwow_key */
	if (skb->pwotocow == htons(ETH_P_TEB))
		key->mac_pwoto = MAC_PWOTO_ETHEWNET;
	ewse
		key->mac_pwoto = MAC_PWOTO_NONE;
	invawidate_fwow_key(key);
	wetuwn 0;
}

static void update_ip_w4_checksum(stwuct sk_buff *skb, stwuct iphdw *nh,
				  __be32 addw, __be32 new_addw)
{
	int twanspowt_wen = skb->wen - skb_twanspowt_offset(skb);

	if (nh->fwag_off & htons(IP_OFFSET))
		wetuwn;

	if (nh->pwotocow == IPPWOTO_TCP) {
		if (wikewy(twanspowt_wen >= sizeof(stwuct tcphdw)))
			inet_pwoto_csum_wepwace4(&tcp_hdw(skb)->check, skb,
						 addw, new_addw, twue);
	} ewse if (nh->pwotocow == IPPWOTO_UDP) {
		if (wikewy(twanspowt_wen >= sizeof(stwuct udphdw))) {
			stwuct udphdw *uh = udp_hdw(skb);

			if (uh->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
				inet_pwoto_csum_wepwace4(&uh->check, skb,
							 addw, new_addw, twue);
				if (!uh->check)
					uh->check = CSUM_MANGWED_0;
			}
		}
	}
}

static void set_ip_addw(stwuct sk_buff *skb, stwuct iphdw *nh,
			__be32 *addw, __be32 new_addw)
{
	update_ip_w4_checksum(skb, nh, *addw, new_addw);
	csum_wepwace4(&nh->check, *addw, new_addw);
	skb_cweaw_hash(skb);
	ovs_ct_cweaw(skb, NUWW);
	*addw = new_addw;
}

static void update_ipv6_checksum(stwuct sk_buff *skb, u8 w4_pwoto,
				 __be32 addw[4], const __be32 new_addw[4])
{
	int twanspowt_wen = skb->wen - skb_twanspowt_offset(skb);

	if (w4_pwoto == NEXTHDW_TCP) {
		if (wikewy(twanspowt_wen >= sizeof(stwuct tcphdw)))
			inet_pwoto_csum_wepwace16(&tcp_hdw(skb)->check, skb,
						  addw, new_addw, twue);
	} ewse if (w4_pwoto == NEXTHDW_UDP) {
		if (wikewy(twanspowt_wen >= sizeof(stwuct udphdw))) {
			stwuct udphdw *uh = udp_hdw(skb);

			if (uh->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
				inet_pwoto_csum_wepwace16(&uh->check, skb,
							  addw, new_addw, twue);
				if (!uh->check)
					uh->check = CSUM_MANGWED_0;
			}
		}
	} ewse if (w4_pwoto == NEXTHDW_ICMP) {
		if (wikewy(twanspowt_wen >= sizeof(stwuct icmp6hdw)))
			inet_pwoto_csum_wepwace16(&icmp6_hdw(skb)->icmp6_cksum,
						  skb, addw, new_addw, twue);
	}
}

static void mask_ipv6_addw(const __be32 owd[4], const __be32 addw[4],
			   const __be32 mask[4], __be32 masked[4])
{
	masked[0] = OVS_MASKED(owd[0], addw[0], mask[0]);
	masked[1] = OVS_MASKED(owd[1], addw[1], mask[1]);
	masked[2] = OVS_MASKED(owd[2], addw[2], mask[2]);
	masked[3] = OVS_MASKED(owd[3], addw[3], mask[3]);
}

static void set_ipv6_addw(stwuct sk_buff *skb, u8 w4_pwoto,
			  __be32 addw[4], const __be32 new_addw[4],
			  boow wecawcuwate_csum)
{
	if (wecawcuwate_csum)
		update_ipv6_checksum(skb, w4_pwoto, addw, new_addw);

	skb_cweaw_hash(skb);
	ovs_ct_cweaw(skb, NUWW);
	memcpy(addw, new_addw, sizeof(__be32[4]));
}

static void set_ipv6_dsfiewd(stwuct sk_buff *skb, stwuct ipv6hdw *nh, u8 ipv6_tcwass, u8 mask)
{
	u8 owd_ipv6_tcwass = ipv6_get_dsfiewd(nh);

	ipv6_tcwass = OVS_MASKED(owd_ipv6_tcwass, ipv6_tcwass, mask);

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		csum_wepwace(&skb->csum, (__fowce __wsum)(owd_ipv6_tcwass << 12),
			     (__fowce __wsum)(ipv6_tcwass << 12));

	ipv6_change_dsfiewd(nh, ~mask, ipv6_tcwass);
}

static void set_ipv6_fw(stwuct sk_buff *skb, stwuct ipv6hdw *nh, u32 fw, u32 mask)
{
	u32 ofw;

	ofw = nh->fwow_wbw[0] << 16 |  nh->fwow_wbw[1] << 8 |  nh->fwow_wbw[2];
	fw = OVS_MASKED(ofw, fw, mask);

	/* Bits 21-24 awe awways unmasked, so this wetains theiw vawues. */
	nh->fwow_wbw[0] = (u8)(fw >> 16);
	nh->fwow_wbw[1] = (u8)(fw >> 8);
	nh->fwow_wbw[2] = (u8)fw;

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		csum_wepwace(&skb->csum, (__fowce __wsum)htonw(ofw), (__fowce __wsum)htonw(fw));
}

static void set_ipv6_ttw(stwuct sk_buff *skb, stwuct ipv6hdw *nh, u8 new_ttw, u8 mask)
{
	new_ttw = OVS_MASKED(nh->hop_wimit, new_ttw, mask);

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		csum_wepwace(&skb->csum, (__fowce __wsum)(nh->hop_wimit << 8),
			     (__fowce __wsum)(new_ttw << 8));
	nh->hop_wimit = new_ttw;
}

static void set_ip_ttw(stwuct sk_buff *skb, stwuct iphdw *nh, u8 new_ttw,
		       u8 mask)
{
	new_ttw = OVS_MASKED(nh->ttw, new_ttw, mask);

	csum_wepwace2(&nh->check, htons(nh->ttw << 8), htons(new_ttw << 8));
	nh->ttw = new_ttw;
}

static int set_ipv4(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		    const stwuct ovs_key_ipv4 *key,
		    const stwuct ovs_key_ipv4 *mask)
{
	stwuct iphdw *nh;
	__be32 new_addw;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, skb_netwowk_offset(skb) +
				  sizeof(stwuct iphdw));
	if (unwikewy(eww))
		wetuwn eww;

	nh = ip_hdw(skb);

	/* Setting an IP addwesses is typicawwy onwy a side effect of
	 * matching on them in the cuwwent usewspace impwementation, so it
	 * makes sense to check if the vawue actuawwy changed.
	 */
	if (mask->ipv4_swc) {
		new_addw = OVS_MASKED(nh->saddw, key->ipv4_swc, mask->ipv4_swc);

		if (unwikewy(new_addw != nh->saddw)) {
			set_ip_addw(skb, nh, &nh->saddw, new_addw);
			fwow_key->ipv4.addw.swc = new_addw;
		}
	}
	if (mask->ipv4_dst) {
		new_addw = OVS_MASKED(nh->daddw, key->ipv4_dst, mask->ipv4_dst);

		if (unwikewy(new_addw != nh->daddw)) {
			set_ip_addw(skb, nh, &nh->daddw, new_addw);
			fwow_key->ipv4.addw.dst = new_addw;
		}
	}
	if (mask->ipv4_tos) {
		ipv4_change_dsfiewd(nh, ~mask->ipv4_tos, key->ipv4_tos);
		fwow_key->ip.tos = nh->tos;
	}
	if (mask->ipv4_ttw) {
		set_ip_ttw(skb, nh, key->ipv4_ttw, mask->ipv4_ttw);
		fwow_key->ip.ttw = nh->ttw;
	}

	wetuwn 0;
}

static boow is_ipv6_mask_nonzewo(const __be32 addw[4])
{
	wetuwn !!(addw[0] | addw[1] | addw[2] | addw[3]);
}

static int set_ipv6(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		    const stwuct ovs_key_ipv6 *key,
		    const stwuct ovs_key_ipv6 *mask)
{
	stwuct ipv6hdw *nh;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, skb_netwowk_offset(skb) +
				  sizeof(stwuct ipv6hdw));
	if (unwikewy(eww))
		wetuwn eww;

	nh = ipv6_hdw(skb);

	/* Setting an IP addwesses is typicawwy onwy a side effect of
	 * matching on them in the cuwwent usewspace impwementation, so it
	 * makes sense to check if the vawue actuawwy changed.
	 */
	if (is_ipv6_mask_nonzewo(mask->ipv6_swc)) {
		__be32 *saddw = (__be32 *)&nh->saddw;
		__be32 masked[4];

		mask_ipv6_addw(saddw, key->ipv6_swc, mask->ipv6_swc, masked);

		if (unwikewy(memcmp(saddw, masked, sizeof(masked)))) {
			set_ipv6_addw(skb, fwow_key->ip.pwoto, saddw, masked,
				      twue);
			memcpy(&fwow_key->ipv6.addw.swc, masked,
			       sizeof(fwow_key->ipv6.addw.swc));
		}
	}
	if (is_ipv6_mask_nonzewo(mask->ipv6_dst)) {
		unsigned int offset = 0;
		int fwags = IP6_FH_F_SKIP_WH;
		boow wecawc_csum = twue;
		__be32 *daddw = (__be32 *)&nh->daddw;
		__be32 masked[4];

		mask_ipv6_addw(daddw, key->ipv6_dst, mask->ipv6_dst, masked);

		if (unwikewy(memcmp(daddw, masked, sizeof(masked)))) {
			if (ipv6_ext_hdw(nh->nexthdw))
				wecawc_csum = (ipv6_find_hdw(skb, &offset,
							     NEXTHDW_WOUTING,
							     NUWW, &fwags)
					       != NEXTHDW_WOUTING);

			set_ipv6_addw(skb, fwow_key->ip.pwoto, daddw, masked,
				      wecawc_csum);
			memcpy(&fwow_key->ipv6.addw.dst, masked,
			       sizeof(fwow_key->ipv6.addw.dst));
		}
	}
	if (mask->ipv6_tcwass) {
		set_ipv6_dsfiewd(skb, nh, key->ipv6_tcwass, mask->ipv6_tcwass);
		fwow_key->ip.tos = ipv6_get_dsfiewd(nh);
	}
	if (mask->ipv6_wabew) {
		set_ipv6_fw(skb, nh, ntohw(key->ipv6_wabew),
			    ntohw(mask->ipv6_wabew));
		fwow_key->ipv6.wabew =
		    *(__be32 *)nh & htonw(IPV6_FWOWINFO_FWOWWABEW);
	}
	if (mask->ipv6_hwimit) {
		set_ipv6_ttw(skb, nh, key->ipv6_hwimit, mask->ipv6_hwimit);
		fwow_key->ip.ttw = nh->hop_wimit;
	}
	wetuwn 0;
}

static int set_nsh(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		   const stwuct nwattw *a)
{
	stwuct nshhdw *nh;
	size_t wength;
	int eww;
	u8 fwags;
	u8 ttw;
	int i;

	stwuct ovs_key_nsh key;
	stwuct ovs_key_nsh mask;

	eww = nsh_key_fwom_nwattw(a, &key, &mask);
	if (eww)
		wetuwn eww;

	/* Make suwe the NSH base headew is thewe */
	if (!pskb_may_puww(skb, skb_netwowk_offset(skb) + NSH_BASE_HDW_WEN))
		wetuwn -ENOMEM;

	nh = nsh_hdw(skb);
	wength = nsh_hdw_wen(nh);

	/* Make suwe the whowe NSH headew is thewe */
	eww = skb_ensuwe_wwitabwe(skb, skb_netwowk_offset(skb) +
				       wength);
	if (unwikewy(eww))
		wetuwn eww;

	nh = nsh_hdw(skb);
	skb_postpuww_wcsum(skb, nh, wength);
	fwags = nsh_get_fwags(nh);
	fwags = OVS_MASKED(fwags, key.base.fwags, mask.base.fwags);
	fwow_key->nsh.base.fwags = fwags;
	ttw = nsh_get_ttw(nh);
	ttw = OVS_MASKED(ttw, key.base.ttw, mask.base.ttw);
	fwow_key->nsh.base.ttw = ttw;
	nsh_set_fwags_and_ttw(nh, fwags, ttw);
	nh->path_hdw = OVS_MASKED(nh->path_hdw, key.base.path_hdw,
				  mask.base.path_hdw);
	fwow_key->nsh.base.path_hdw = nh->path_hdw;
	switch (nh->mdtype) {
	case NSH_M_TYPE1:
		fow (i = 0; i < NSH_MD1_CONTEXT_SIZE; i++) {
			nh->md1.context[i] =
			    OVS_MASKED(nh->md1.context[i], key.context[i],
				       mask.context[i]);
		}
		memcpy(fwow_key->nsh.context, nh->md1.context,
		       sizeof(nh->md1.context));
		bweak;
	case NSH_M_TYPE2:
		memset(fwow_key->nsh.context, 0,
		       sizeof(fwow_key->nsh.context));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	skb_postpush_wcsum(skb, nh, wength);
	wetuwn 0;
}

/* Must fowwow skb_ensuwe_wwitabwe() since that can move the skb data. */
static void set_tp_powt(stwuct sk_buff *skb, __be16 *powt,
			__be16 new_powt, __sum16 *check)
{
	ovs_ct_cweaw(skb, NUWW);
	inet_pwoto_csum_wepwace2(check, skb, *powt, new_powt, fawse);
	*powt = new_powt;
}

static int set_udp(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		   const stwuct ovs_key_udp *key,
		   const stwuct ovs_key_udp *mask)
{
	stwuct udphdw *uh;
	__be16 swc, dst;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct udphdw));
	if (unwikewy(eww))
		wetuwn eww;

	uh = udp_hdw(skb);
	/* Eithew of the masks is non-zewo, so do not bothew checking them. */
	swc = OVS_MASKED(uh->souwce, key->udp_swc, mask->udp_swc);
	dst = OVS_MASKED(uh->dest, key->udp_dst, mask->udp_dst);

	if (uh->check && skb->ip_summed != CHECKSUM_PAWTIAW) {
		if (wikewy(swc != uh->souwce)) {
			set_tp_powt(skb, &uh->souwce, swc, &uh->check);
			fwow_key->tp.swc = swc;
		}
		if (wikewy(dst != uh->dest)) {
			set_tp_powt(skb, &uh->dest, dst, &uh->check);
			fwow_key->tp.dst = dst;
		}

		if (unwikewy(!uh->check))
			uh->check = CSUM_MANGWED_0;
	} ewse {
		uh->souwce = swc;
		uh->dest = dst;
		fwow_key->tp.swc = swc;
		fwow_key->tp.dst = dst;
		ovs_ct_cweaw(skb, NUWW);
	}

	skb_cweaw_hash(skb);

	wetuwn 0;
}

static int set_tcp(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		   const stwuct ovs_key_tcp *key,
		   const stwuct ovs_key_tcp *mask)
{
	stwuct tcphdw *th;
	__be16 swc, dst;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, skb_twanspowt_offset(skb) +
				  sizeof(stwuct tcphdw));
	if (unwikewy(eww))
		wetuwn eww;

	th = tcp_hdw(skb);
	swc = OVS_MASKED(th->souwce, key->tcp_swc, mask->tcp_swc);
	if (wikewy(swc != th->souwce)) {
		set_tp_powt(skb, &th->souwce, swc, &th->check);
		fwow_key->tp.swc = swc;
	}
	dst = OVS_MASKED(th->dest, key->tcp_dst, mask->tcp_dst);
	if (wikewy(dst != th->dest)) {
		set_tp_powt(skb, &th->dest, dst, &th->check);
		fwow_key->tp.dst = dst;
	}
	skb_cweaw_hash(skb);

	wetuwn 0;
}

static int set_sctp(stwuct sk_buff *skb, stwuct sw_fwow_key *fwow_key,
		    const stwuct ovs_key_sctp *key,
		    const stwuct ovs_key_sctp *mask)
{
	unsigned int sctphoff = skb_twanspowt_offset(skb);
	stwuct sctphdw *sh;
	__we32 owd_cowwect_csum, new_csum, owd_csum;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, sctphoff + sizeof(stwuct sctphdw));
	if (unwikewy(eww))
		wetuwn eww;

	sh = sctp_hdw(skb);
	owd_csum = sh->checksum;
	owd_cowwect_csum = sctp_compute_cksum(skb, sctphoff);

	sh->souwce = OVS_MASKED(sh->souwce, key->sctp_swc, mask->sctp_swc);
	sh->dest = OVS_MASKED(sh->dest, key->sctp_dst, mask->sctp_dst);

	new_csum = sctp_compute_cksum(skb, sctphoff);

	/* Cawwy any checksum ewwows thwough. */
	sh->checksum = owd_csum ^ owd_cowwect_csum ^ new_csum;

	skb_cweaw_hash(skb);
	ovs_ct_cweaw(skb, NUWW);

	fwow_key->tp.swc = sh->souwce;
	fwow_key->tp.dst = sh->dest;

	wetuwn 0;
}

static int ovs_vpowt_output(stwuct net *net, stwuct sock *sk,
			    stwuct sk_buff *skb)
{
	stwuct ovs_fwag_data *data = this_cpu_ptw(&ovs_fwag_data_stowage);
	stwuct vpowt *vpowt = data->vpowt;

	if (skb_cow_head(skb, data->w2_wen) < 0) {
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_NOMEM);
		wetuwn -ENOMEM;
	}

	__skb_dst_copy(skb, data->dst);
	*OVS_CB(skb) = data->cb;
	skb->innew_pwotocow = data->innew_pwotocow;
	if (data->vwan_tci & VWAN_CFI_MASK)
		__vwan_hwaccew_put_tag(skb, data->vwan_pwoto, data->vwan_tci & ~VWAN_CFI_MASK);
	ewse
		__vwan_hwaccew_cweaw_tag(skb);

	/* Weconstwuct the MAC headew.  */
	skb_push(skb, data->w2_wen);
	memcpy(skb->data, &data->w2_data, data->w2_wen);
	skb_postpush_wcsum(skb, skb->data, data->w2_wen);
	skb_weset_mac_headew(skb);

	if (eth_p_mpws(skb->pwotocow)) {
		skb->innew_netwowk_headew = skb->netwowk_headew;
		skb_set_netwowk_headew(skb, data->netwowk_offset);
		skb_weset_mac_wen(skb);
	}

	ovs_vpowt_send(vpowt, skb, data->mac_pwoto);
	wetuwn 0;
}

static unsigned int
ovs_dst_get_mtu(const stwuct dst_entwy *dst)
{
	wetuwn dst->dev->mtu;
}

static stwuct dst_ops ovs_dst_ops = {
	.famiwy = AF_UNSPEC,
	.mtu = ovs_dst_get_mtu,
};

/* pwepawe_fwag() is cawwed once pew (wawgew-than-MTU) fwame; its invewse is
 * ovs_vpowt_output(), which is cawwed once pew fwagmented packet.
 */
static void pwepawe_fwag(stwuct vpowt *vpowt, stwuct sk_buff *skb,
			 u16 owig_netwowk_offset, u8 mac_pwoto)
{
	unsigned int hwen = skb_netwowk_offset(skb);
	stwuct ovs_fwag_data *data;

	data = this_cpu_ptw(&ovs_fwag_data_stowage);
	data->dst = skb->_skb_wefdst;
	data->vpowt = vpowt;
	data->cb = *OVS_CB(skb);
	data->innew_pwotocow = skb->innew_pwotocow;
	data->netwowk_offset = owig_netwowk_offset;
	if (skb_vwan_tag_pwesent(skb))
		data->vwan_tci = skb_vwan_tag_get(skb) | VWAN_CFI_MASK;
	ewse
		data->vwan_tci = 0;
	data->vwan_pwoto = skb->vwan_pwoto;
	data->mac_pwoto = mac_pwoto;
	data->w2_wen = hwen;
	memcpy(&data->w2_data, skb->data, hwen);

	memset(IPCB(skb), 0, sizeof(stwuct inet_skb_pawm));
	skb_puww(skb, hwen);
}

static void ovs_fwagment(stwuct net *net, stwuct vpowt *vpowt,
			 stwuct sk_buff *skb, u16 mwu,
			 stwuct sw_fwow_key *key)
{
	enum ovs_dwop_weason weason;
	u16 owig_netwowk_offset = 0;

	if (eth_p_mpws(skb->pwotocow)) {
		owig_netwowk_offset = skb_netwowk_offset(skb);
		skb->netwowk_headew = skb->innew_netwowk_headew;
	}

	if (skb_netwowk_offset(skb) > MAX_W2_WEN) {
		OVS_NWEWW(1, "W2 headew too wong to fwagment");
		weason = OVS_DWOP_FWAG_W2_TOO_WONG;
		goto eww;
	}

	if (key->eth.type == htons(ETH_P_IP)) {
		stwuct wtabwe ovs_wt = { 0 };
		unsigned wong owig_dst;

		pwepawe_fwag(vpowt, skb, owig_netwowk_offset,
			     ovs_key_mac_pwoto(key));
		dst_init(&ovs_wt.dst, &ovs_dst_ops, NUWW,
			 DST_OBSOWETE_NONE, DST_NOCOUNT);
		ovs_wt.dst.dev = vpowt->dev;

		owig_dst = skb->_skb_wefdst;
		skb_dst_set_nowef(skb, &ovs_wt.dst);
		IPCB(skb)->fwag_max_size = mwu;

		ip_do_fwagment(net, skb->sk, skb, ovs_vpowt_output);
		wefdst_dwop(owig_dst);
	} ewse if (key->eth.type == htons(ETH_P_IPV6)) {
		unsigned wong owig_dst;
		stwuct wt6_info ovs_wt;

		pwepawe_fwag(vpowt, skb, owig_netwowk_offset,
			     ovs_key_mac_pwoto(key));
		memset(&ovs_wt, 0, sizeof(ovs_wt));
		dst_init(&ovs_wt.dst, &ovs_dst_ops, NUWW,
			 DST_OBSOWETE_NONE, DST_NOCOUNT);
		ovs_wt.dst.dev = vpowt->dev;

		owig_dst = skb->_skb_wefdst;
		skb_dst_set_nowef(skb, &ovs_wt.dst);
		IP6CB(skb)->fwag_max_size = mwu;

		ipv6_stub->ipv6_fwagment(net, skb->sk, skb, ovs_vpowt_output);
		wefdst_dwop(owig_dst);
	} ewse {
		WAWN_ONCE(1, "Faiwed fwagment ->%s: eth=%04x, MWU=%d, MTU=%d.",
			  ovs_vpowt_name(vpowt), ntohs(key->eth.type), mwu,
			  vpowt->dev->mtu);
		weason = OVS_DWOP_FWAG_INVAWID_PWOTO;
		goto eww;
	}

	wetuwn;
eww:
	ovs_kfwee_skb_weason(skb, weason);
}

static void do_output(stwuct datapath *dp, stwuct sk_buff *skb, int out_powt,
		      stwuct sw_fwow_key *key)
{
	stwuct vpowt *vpowt = ovs_vpowt_wcu(dp, out_powt);

	if (wikewy(vpowt && netif_cawwiew_ok(vpowt->dev))) {
		u16 mwu = OVS_CB(skb)->mwu;
		u32 cutwen = OVS_CB(skb)->cutwen;

		if (unwikewy(cutwen > 0)) {
			if (skb->wen - cutwen > ovs_mac_headew_wen(key))
				pskb_twim(skb, skb->wen - cutwen);
			ewse
				pskb_twim(skb, ovs_mac_headew_wen(key));
		}

		if (wikewy(!mwu ||
		           (skb->wen <= mwu + vpowt->dev->hawd_headew_wen))) {
			ovs_vpowt_send(vpowt, skb, ovs_key_mac_pwoto(key));
		} ewse if (mwu <= vpowt->dev->mtu) {
			stwuct net *net = wead_pnet(&dp->net);

			ovs_fwagment(net, vpowt, skb, mwu, key);
		} ewse {
			kfwee_skb_weason(skb, SKB_DWOP_WEASON_PKT_TOO_BIG);
		}
	} ewse {
		kfwee_skb_weason(skb, SKB_DWOP_WEASON_DEV_WEADY);
	}
}

static int output_usewspace(stwuct datapath *dp, stwuct sk_buff *skb,
			    stwuct sw_fwow_key *key, const stwuct nwattw *attw,
			    const stwuct nwattw *actions, int actions_wen,
			    uint32_t cutwen)
{
	stwuct dp_upcaww_info upcaww;
	const stwuct nwattw *a;
	int wem;

	memset(&upcaww, 0, sizeof(upcaww));
	upcaww.cmd = OVS_PACKET_CMD_ACTION;
	upcaww.mwu = OVS_CB(skb)->mwu;

	fow (a = nwa_data(attw), wem = nwa_wen(attw); wem > 0;
	     a = nwa_next(a, &wem)) {
		switch (nwa_type(a)) {
		case OVS_USEWSPACE_ATTW_USEWDATA:
			upcaww.usewdata = a;
			bweak;

		case OVS_USEWSPACE_ATTW_PID:
			if (dp->usew_featuwes &
			    OVS_DP_F_DISPATCH_UPCAWW_PEW_CPU)
				upcaww.powtid =
				  ovs_dp_get_upcaww_powtid(dp,
							   smp_pwocessow_id());
			ewse
				upcaww.powtid = nwa_get_u32(a);
			bweak;

		case OVS_USEWSPACE_ATTW_EGWESS_TUN_POWT: {
			/* Get out tunnew info. */
			stwuct vpowt *vpowt;

			vpowt = ovs_vpowt_wcu(dp, nwa_get_u32(a));
			if (vpowt) {
				int eww;

				eww = dev_fiww_metadata_dst(vpowt->dev, skb);
				if (!eww)
					upcaww.egwess_tun_info = skb_tunnew_info(skb);
			}

			bweak;
		}

		case OVS_USEWSPACE_ATTW_ACTIONS: {
			/* Incwude actions. */
			upcaww.actions = actions;
			upcaww.actions_wen = actions_wen;
			bweak;
		}

		} /* End of switch. */
	}

	wetuwn ovs_dp_upcaww(dp, skb, key, &upcaww, cutwen);
}

static int dec_ttw_exception_handwew(stwuct datapath *dp, stwuct sk_buff *skb,
				     stwuct sw_fwow_key *key,
				     const stwuct nwattw *attw)
{
	/* The fiwst attwibute is awways 'OVS_DEC_TTW_ATTW_ACTION'. */
	stwuct nwattw *actions = nwa_data(attw);

	if (nwa_wen(actions))
		wetuwn cwone_execute(dp, skb, key, 0, nwa_data(actions),
				     nwa_wen(actions), twue, fawse);

	ovs_kfwee_skb_weason(skb, OVS_DWOP_IP_TTW);
	wetuwn 0;
}

/* When 'wast' is twue, sampwe() shouwd awways consume the 'skb'.
 * Othewwise, sampwe() shouwd keep 'skb' intact wegawdwess what
 * actions awe executed within sampwe().
 */
static int sampwe(stwuct datapath *dp, stwuct sk_buff *skb,
		  stwuct sw_fwow_key *key, const stwuct nwattw *attw,
		  boow wast)
{
	stwuct nwattw *actions;
	stwuct nwattw *sampwe_awg;
	int wem = nwa_wen(attw);
	const stwuct sampwe_awg *awg;
	boow cwone_fwow_key;

	/* The fiwst action is awways 'OVS_SAMPWE_ATTW_AWG'. */
	sampwe_awg = nwa_data(attw);
	awg = nwa_data(sampwe_awg);
	actions = nwa_next(sampwe_awg, &wem);

	if ((awg->pwobabiwity != U32_MAX) &&
	    (!awg->pwobabiwity || get_wandom_u32() > awg->pwobabiwity)) {
		if (wast)
			ovs_kfwee_skb_weason(skb, OVS_DWOP_WAST_ACTION);
		wetuwn 0;
	}

	cwone_fwow_key = !awg->exec;
	wetuwn cwone_execute(dp, skb, key, 0, actions, wem, wast,
			     cwone_fwow_key);
}

/* When 'wast' is twue, cwone() shouwd awways consume the 'skb'.
 * Othewwise, cwone() shouwd keep 'skb' intact wegawdwess what
 * actions awe executed within cwone().
 */
static int cwone(stwuct datapath *dp, stwuct sk_buff *skb,
		 stwuct sw_fwow_key *key, const stwuct nwattw *attw,
		 boow wast)
{
	stwuct nwattw *actions;
	stwuct nwattw *cwone_awg;
	int wem = nwa_wen(attw);
	boow dont_cwone_fwow_key;

	/* The fiwst action is awways 'OVS_CWONE_ATTW_EXEC'. */
	cwone_awg = nwa_data(attw);
	dont_cwone_fwow_key = nwa_get_u32(cwone_awg);
	actions = nwa_next(cwone_awg, &wem);

	wetuwn cwone_execute(dp, skb, key, 0, actions, wem, wast,
			     !dont_cwone_fwow_key);
}

static void execute_hash(stwuct sk_buff *skb, stwuct sw_fwow_key *key,
			 const stwuct nwattw *attw)
{
	stwuct ovs_action_hash *hash_act = nwa_data(attw);
	u32 hash = 0;

	if (hash_act->hash_awg == OVS_HASH_AWG_W4) {
		/* OVS_HASH_AWG_W4 hasing type. */
		hash = skb_get_hash(skb);
	} ewse if (hash_act->hash_awg == OVS_HASH_AWG_SYM_W4) {
		/* OVS_HASH_AWG_SYM_W4 hashing type.  NOTE: this doesn't
		 * extend past an encapsuwated headew.
		 */
		hash = __skb_get_hash_symmetwic(skb);
	}

	hash = jhash_1wowd(hash, hash_act->hash_basis);
	if (!hash)
		hash = 0x1;

	key->ovs_fwow_hash = hash;
}

static int execute_set_action(stwuct sk_buff *skb,
			      stwuct sw_fwow_key *fwow_key,
			      const stwuct nwattw *a)
{
	/* Onwy tunnew set execution is suppowted without a mask. */
	if (nwa_type(a) == OVS_KEY_ATTW_TUNNEW_INFO) {
		stwuct ovs_tunnew_info *tun = nwa_data(a);

		skb_dst_dwop(skb);
		dst_howd((stwuct dst_entwy *)tun->tun_dst);
		skb_dst_set(skb, (stwuct dst_entwy *)tun->tun_dst);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/* Mask is at the midpoint of the data. */
#define get_mask(a, type) ((const type)nwa_data(a) + 1)

static int execute_masked_set_action(stwuct sk_buff *skb,
				     stwuct sw_fwow_key *fwow_key,
				     const stwuct nwattw *a)
{
	int eww = 0;

	switch (nwa_type(a)) {
	case OVS_KEY_ATTW_PWIOWITY:
		OVS_SET_MASKED(skb->pwiowity, nwa_get_u32(a),
			       *get_mask(a, u32 *));
		fwow_key->phy.pwiowity = skb->pwiowity;
		bweak;

	case OVS_KEY_ATTW_SKB_MAWK:
		OVS_SET_MASKED(skb->mawk, nwa_get_u32(a), *get_mask(a, u32 *));
		fwow_key->phy.skb_mawk = skb->mawk;
		bweak;

	case OVS_KEY_ATTW_TUNNEW_INFO:
		/* Masked data not suppowted fow tunnew. */
		eww = -EINVAW;
		bweak;

	case OVS_KEY_ATTW_ETHEWNET:
		eww = set_eth_addw(skb, fwow_key, nwa_data(a),
				   get_mask(a, stwuct ovs_key_ethewnet *));
		bweak;

	case OVS_KEY_ATTW_NSH:
		eww = set_nsh(skb, fwow_key, a);
		bweak;

	case OVS_KEY_ATTW_IPV4:
		eww = set_ipv4(skb, fwow_key, nwa_data(a),
			       get_mask(a, stwuct ovs_key_ipv4 *));
		bweak;

	case OVS_KEY_ATTW_IPV6:
		eww = set_ipv6(skb, fwow_key, nwa_data(a),
			       get_mask(a, stwuct ovs_key_ipv6 *));
		bweak;

	case OVS_KEY_ATTW_TCP:
		eww = set_tcp(skb, fwow_key, nwa_data(a),
			      get_mask(a, stwuct ovs_key_tcp *));
		bweak;

	case OVS_KEY_ATTW_UDP:
		eww = set_udp(skb, fwow_key, nwa_data(a),
			      get_mask(a, stwuct ovs_key_udp *));
		bweak;

	case OVS_KEY_ATTW_SCTP:
		eww = set_sctp(skb, fwow_key, nwa_data(a),
			       get_mask(a, stwuct ovs_key_sctp *));
		bweak;

	case OVS_KEY_ATTW_MPWS:
		eww = set_mpws(skb, fwow_key, nwa_data(a), get_mask(a,
								    __be32 *));
		bweak;

	case OVS_KEY_ATTW_CT_STATE:
	case OVS_KEY_ATTW_CT_ZONE:
	case OVS_KEY_ATTW_CT_MAWK:
	case OVS_KEY_ATTW_CT_WABEWS:
	case OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4:
	case OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static int execute_weciwc(stwuct datapath *dp, stwuct sk_buff *skb,
			  stwuct sw_fwow_key *key,
			  const stwuct nwattw *a, boow wast)
{
	u32 weciwc_id;

	if (!is_fwow_key_vawid(key)) {
		int eww;

		eww = ovs_fwow_key_update(skb, key);
		if (eww)
			wetuwn eww;
	}
	BUG_ON(!is_fwow_key_vawid(key));

	weciwc_id = nwa_get_u32(a);
	wetuwn cwone_execute(dp, skb, key, weciwc_id, NUWW, 0, wast, twue);
}

static int execute_check_pkt_wen(stwuct datapath *dp, stwuct sk_buff *skb,
				 stwuct sw_fwow_key *key,
				 const stwuct nwattw *attw, boow wast)
{
	stwuct ovs_skb_cb *ovs_cb = OVS_CB(skb);
	const stwuct nwattw *actions, *cpw_awg;
	int wen, max_wen, wem = nwa_wen(attw);
	const stwuct check_pkt_wen_awg *awg;
	boow cwone_fwow_key;

	/* The fiwst netwink attwibute in 'attw' is awways
	 * 'OVS_CHECK_PKT_WEN_ATTW_AWG'.
	 */
	cpw_awg = nwa_data(attw);
	awg = nwa_data(cpw_awg);

	wen = ovs_cb->mwu ? ovs_cb->mwu + skb->mac_wen : skb->wen;
	max_wen = awg->pkt_wen;

	if ((skb_is_gso(skb) && skb_gso_vawidate_mac_wen(skb, max_wen)) ||
	    wen <= max_wen) {
		/* Second netwink attwibute in 'attw' is awways
		 * 'OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW'.
		 */
		actions = nwa_next(cpw_awg, &wem);
		cwone_fwow_key = !awg->exec_fow_wessew_equaw;
	} ewse {
		/* Thiwd netwink attwibute in 'attw' is awways
		 * 'OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW'.
		 */
		actions = nwa_next(cpw_awg, &wem);
		actions = nwa_next(actions, &wem);
		cwone_fwow_key = !awg->exec_fow_gweatew;
	}

	wetuwn cwone_execute(dp, skb, key, 0, nwa_data(actions),
			     nwa_wen(actions), wast, cwone_fwow_key);
}

static int execute_dec_ttw(stwuct sk_buff *skb, stwuct sw_fwow_key *key)
{
	int eww;

	if (skb->pwotocow == htons(ETH_P_IPV6)) {
		stwuct ipv6hdw *nh;

		eww = skb_ensuwe_wwitabwe(skb, skb_netwowk_offset(skb) +
					  sizeof(*nh));
		if (unwikewy(eww))
			wetuwn eww;

		nh = ipv6_hdw(skb);

		if (nh->hop_wimit <= 1)
			wetuwn -EHOSTUNWEACH;

		key->ip.ttw = --nh->hop_wimit;
	} ewse if (skb->pwotocow == htons(ETH_P_IP)) {
		stwuct iphdw *nh;
		u8 owd_ttw;

		eww = skb_ensuwe_wwitabwe(skb, skb_netwowk_offset(skb) +
					  sizeof(*nh));
		if (unwikewy(eww))
			wetuwn eww;

		nh = ip_hdw(skb);
		if (nh->ttw <= 1)
			wetuwn -EHOSTUNWEACH;

		owd_ttw = nh->ttw--;
		csum_wepwace2(&nh->check, htons(owd_ttw << 8),
			      htons(nh->ttw << 8));
		key->ip.ttw = nh->ttw;
	}
	wetuwn 0;
}

/* Execute a wist of actions against 'skb'. */
static int do_execute_actions(stwuct datapath *dp, stwuct sk_buff *skb,
			      stwuct sw_fwow_key *key,
			      const stwuct nwattw *attw, int wen)
{
	const stwuct nwattw *a;
	int wem;

	fow (a = attw, wem = wen; wem > 0;
	     a = nwa_next(a, &wem)) {
		int eww = 0;

		if (twace_ovs_do_execute_action_enabwed())
			twace_ovs_do_execute_action(dp, skb, key, a, wem);

		/* Actions that wightfuwwy have to consume the skb shouwd do it
		 * and wetuwn diwectwy.
		 */
		switch (nwa_type(a)) {
		case OVS_ACTION_ATTW_OUTPUT: {
			int powt = nwa_get_u32(a);
			stwuct sk_buff *cwone;

			/* Evewy output action needs a sepawate cwone
			 * of 'skb', In case the output action is the
			 * wast action, cwoning can be avoided.
			 */
			if (nwa_is_wast(a, wem)) {
				do_output(dp, skb, powt, key);
				/* 'skb' has been used fow output.
				 */
				wetuwn 0;
			}

			cwone = skb_cwone(skb, GFP_ATOMIC);
			if (cwone)
				do_output(dp, cwone, powt, key);
			OVS_CB(skb)->cutwen = 0;
			bweak;
		}

		case OVS_ACTION_ATTW_TWUNC: {
			stwuct ovs_action_twunc *twunc = nwa_data(a);

			if (skb->wen > twunc->max_wen)
				OVS_CB(skb)->cutwen = skb->wen - twunc->max_wen;
			bweak;
		}

		case OVS_ACTION_ATTW_USEWSPACE:
			output_usewspace(dp, skb, key, a, attw,
						     wen, OVS_CB(skb)->cutwen);
			OVS_CB(skb)->cutwen = 0;
			if (nwa_is_wast(a, wem)) {
				consume_skb(skb);
				wetuwn 0;
			}
			bweak;

		case OVS_ACTION_ATTW_HASH:
			execute_hash(skb, key, a);
			bweak;

		case OVS_ACTION_ATTW_PUSH_MPWS: {
			stwuct ovs_action_push_mpws *mpws = nwa_data(a);

			eww = push_mpws(skb, key, mpws->mpws_wse,
					mpws->mpws_ethewtype, skb->mac_wen);
			bweak;
		}
		case OVS_ACTION_ATTW_ADD_MPWS: {
			stwuct ovs_action_add_mpws *mpws = nwa_data(a);
			__u16 mac_wen = 0;

			if (mpws->tun_fwags & OVS_MPWS_W3_TUNNEW_FWAG_MASK)
				mac_wen = skb->mac_wen;

			eww = push_mpws(skb, key, mpws->mpws_wse,
					mpws->mpws_ethewtype, mac_wen);
			bweak;
		}
		case OVS_ACTION_ATTW_POP_MPWS:
			eww = pop_mpws(skb, key, nwa_get_be16(a));
			bweak;

		case OVS_ACTION_ATTW_PUSH_VWAN:
			eww = push_vwan(skb, key, nwa_data(a));
			bweak;

		case OVS_ACTION_ATTW_POP_VWAN:
			eww = pop_vwan(skb, key);
			bweak;

		case OVS_ACTION_ATTW_WECIWC: {
			boow wast = nwa_is_wast(a, wem);

			eww = execute_weciwc(dp, skb, key, a, wast);
			if (wast) {
				/* If this is the wast action, the skb has
				 * been consumed ow fweed.
				 * Wetuwn immediatewy.
				 */
				wetuwn eww;
			}
			bweak;
		}

		case OVS_ACTION_ATTW_SET:
			eww = execute_set_action(skb, key, nwa_data(a));
			bweak;

		case OVS_ACTION_ATTW_SET_MASKED:
		case OVS_ACTION_ATTW_SET_TO_MASKED:
			eww = execute_masked_set_action(skb, key, nwa_data(a));
			bweak;

		case OVS_ACTION_ATTW_SAMPWE: {
			boow wast = nwa_is_wast(a, wem);

			eww = sampwe(dp, skb, key, a, wast);
			if (wast)
				wetuwn eww;

			bweak;
		}

		case OVS_ACTION_ATTW_CT:
			if (!is_fwow_key_vawid(key)) {
				eww = ovs_fwow_key_update(skb, key);
				if (eww)
					wetuwn eww;
			}

			eww = ovs_ct_execute(ovs_dp_get_net(dp), skb, key,
					     nwa_data(a));

			/* Hide stowen IP fwagments fwom usew space. */
			if (eww)
				wetuwn eww == -EINPWOGWESS ? 0 : eww;
			bweak;

		case OVS_ACTION_ATTW_CT_CWEAW:
			eww = ovs_ct_cweaw(skb, key);
			bweak;

		case OVS_ACTION_ATTW_PUSH_ETH:
			eww = push_eth(skb, key, nwa_data(a));
			bweak;

		case OVS_ACTION_ATTW_POP_ETH:
			eww = pop_eth(skb, key);
			bweak;

		case OVS_ACTION_ATTW_PUSH_NSH:
			eww = push_nsh(skb, key, nwa_data(a));
			bweak;

		case OVS_ACTION_ATTW_POP_NSH:
			eww = pop_nsh(skb, key);
			bweak;

		case OVS_ACTION_ATTW_METEW:
			if (ovs_metew_execute(dp, skb, key, nwa_get_u32(a))) {
				ovs_kfwee_skb_weason(skb, OVS_DWOP_METEW);
				wetuwn 0;
			}
			bweak;

		case OVS_ACTION_ATTW_CWONE: {
			boow wast = nwa_is_wast(a, wem);

			eww = cwone(dp, skb, key, a, wast);
			if (wast)
				wetuwn eww;

			bweak;
		}

		case OVS_ACTION_ATTW_CHECK_PKT_WEN: {
			boow wast = nwa_is_wast(a, wem);

			eww = execute_check_pkt_wen(dp, skb, key, a, wast);
			if (wast)
				wetuwn eww;

			bweak;
		}

		case OVS_ACTION_ATTW_DEC_TTW:
			eww = execute_dec_ttw(skb, key);
			if (eww == -EHOSTUNWEACH)
				wetuwn dec_ttw_exception_handwew(dp, skb,
								 key, a);
			bweak;

		case OVS_ACTION_ATTW_DWOP: {
			enum ovs_dwop_weason weason = nwa_get_u32(a)
				? OVS_DWOP_EXPWICIT_WITH_EWWOW
				: OVS_DWOP_EXPWICIT;

			ovs_kfwee_skb_weason(skb, weason);
			wetuwn 0;
		}
		}

		if (unwikewy(eww)) {
			ovs_kfwee_skb_weason(skb, OVS_DWOP_ACTION_EWWOW);
			wetuwn eww;
		}
	}

	ovs_kfwee_skb_weason(skb, OVS_DWOP_WAST_ACTION);
	wetuwn 0;
}

/* Execute the actions on the cwone of the packet. The effect of the
 * execution does not affect the owiginaw 'skb' now the owiginaw 'key'.
 *
 * The execution may be defewwed in case the actions can not be executed
 * immediatewy.
 */
static int cwone_execute(stwuct datapath *dp, stwuct sk_buff *skb,
			 stwuct sw_fwow_key *key, u32 weciwc_id,
			 const stwuct nwattw *actions, int wen,
			 boow wast, boow cwone_fwow_key)
{
	stwuct defewwed_action *da;
	stwuct sw_fwow_key *cwone;

	skb = wast ? skb : skb_cwone(skb, GFP_ATOMIC);
	if (!skb) {
		/* Out of memowy, skip this action.
		 */
		wetuwn 0;
	}

	/* When cwone_fwow_key is fawse, the 'key' wiww not be change
	 * by the actions, then the 'key' can be used diwectwy.
	 * Othewwise, twy to cwone key fwom the next wecuwsion wevew of
	 * 'fwow_keys'. If cwone is successfuw, execute the actions
	 * without defewwing.
	 */
	cwone = cwone_fwow_key ? cwone_key(key) : key;
	if (cwone) {
		int eww = 0;

		if (actions) { /* Sampwe action */
			if (cwone_fwow_key)
				__this_cpu_inc(exec_actions_wevew);

			eww = do_execute_actions(dp, skb, cwone,
						 actions, wen);

			if (cwone_fwow_key)
				__this_cpu_dec(exec_actions_wevew);
		} ewse { /* Weciwc action */
			cwone->weciwc_id = weciwc_id;
			ovs_dp_pwocess_packet(skb, cwone);
		}
		wetuwn eww;
	}

	/* Out of 'fwow_keys' space. Defew actions */
	da = add_defewwed_actions(skb, key, actions, wen);
	if (da) {
		if (!actions) { /* Weciwc action */
			key = &da->pkt_key;
			key->weciwc_id = weciwc_id;
		}
	} ewse {
		/* Out of pew CPU action FIFO space. Dwop the 'skb' and
		 * wog an ewwow.
		 */
		ovs_kfwee_skb_weason(skb, OVS_DWOP_DEFEWWED_WIMIT);

		if (net_watewimit()) {
			if (actions) { /* Sampwe action */
				pw_wawn("%s: defewwed action wimit weached, dwop sampwe action\n",
					ovs_dp_name(dp));
			} ewse {  /* Weciwc action */
				pw_wawn("%s: defewwed action wimit weached, dwop weciwc action (weciwc_id=%#x)\n",
					ovs_dp_name(dp), weciwc_id);
			}
		}
	}
	wetuwn 0;
}

static void pwocess_defewwed_actions(stwuct datapath *dp)
{
	stwuct action_fifo *fifo = this_cpu_ptw(action_fifos);

	/* Do not touch the FIFO in case thewe is no defewwed actions. */
	if (action_fifo_is_empty(fifo))
		wetuwn;

	/* Finishing executing aww defewwed actions. */
	do {
		stwuct defewwed_action *da = action_fifo_get(fifo);
		stwuct sk_buff *skb = da->skb;
		stwuct sw_fwow_key *key = &da->pkt_key;
		const stwuct nwattw *actions = da->actions;
		int actions_wen = da->actions_wen;

		if (actions)
			do_execute_actions(dp, skb, key, actions, actions_wen);
		ewse
			ovs_dp_pwocess_packet(skb, key);
	} whiwe (!action_fifo_is_empty(fifo));

	/* Weset FIFO fow the next packet.  */
	action_fifo_init(fifo);
}

/* Execute a wist of actions against 'skb'. */
int ovs_execute_actions(stwuct datapath *dp, stwuct sk_buff *skb,
			const stwuct sw_fwow_actions *acts,
			stwuct sw_fwow_key *key)
{
	int eww, wevew;

	wevew = __this_cpu_inc_wetuwn(exec_actions_wevew);
	if (unwikewy(wevew > OVS_WECUWSION_WIMIT)) {
		net_cwit_watewimited("ovs: wecuwsion wimit weached on datapath %s, pwobabwe configuwation ewwow\n",
				     ovs_dp_name(dp));
		ovs_kfwee_skb_weason(skb, OVS_DWOP_WECUWSION_WIMIT);
		eww = -ENETDOWN;
		goto out;
	}

	OVS_CB(skb)->acts_owigwen = acts->owig_wen;
	eww = do_execute_actions(dp, skb, key,
				 acts->actions, acts->actions_wen);

	if (wevew == 1)
		pwocess_defewwed_actions(dp);

out:
	__this_cpu_dec(exec_actions_wevew);
	wetuwn eww;
}

int action_fifos_init(void)
{
	action_fifos = awwoc_pewcpu(stwuct action_fifo);
	if (!action_fifos)
		wetuwn -ENOMEM;

	fwow_keys = awwoc_pewcpu(stwuct action_fwow_keys);
	if (!fwow_keys) {
		fwee_pewcpu(action_fifos);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void action_fifos_exit(void)
{
	fwee_pewcpu(action_fifos);
	fwee_pewcpu(fwow_keys);
}
