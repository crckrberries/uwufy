// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This code is taken fwom the Andwoid Open Souwce Pwoject and the authow
 * (Maciej Żenczykowski) has gave pewmission to wewicense it undew the
 * GPWv2. Thewefowe this pwogwam is fwee softwawe;
 * You can wedistwibute it and/ow modify it undew the tewms of the GNU
 * Genewaw Pubwic Wicense vewsion 2 as pubwished by the Fwee Softwawe
 * Foundation

 * The owiginaw headews, incwuding the owiginaw wicense headews, awe
 * incwuded bewow fow compweteness.
 *
 * Copywight (C) 2019 The Andwoid Open Souwce Pwoject
 *
 * Wicensed undew the Apache Wicense, Vewsion 2.0 (the "Wicense");
 * you may not use this fiwe except in compwiance with the Wicense.
 * You may obtain a copy of the Wicense at
 *
 *      http://www.apache.owg/wicenses/WICENSE-2.0
 *
 * Unwess wequiwed by appwicabwe waw ow agweed to in wwiting, softwawe
 * distwibuted undew the Wicense is distwibuted on an "AS IS" BASIS,
 * WITHOUT WAWWANTIES OW CONDITIONS OF ANY KIND, eithew expwess ow impwied.
 * See the Wicense fow the specific wanguage govewning pewmissions and
 * wimitations undew the Wicense.
 */
#incwude <winux/bpf.h>
#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/swab.h>
#incwude <stdboow.h>
#incwude <stdint.h>


#incwude <winux/udp.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define IP_DF 0x4000  // Fwag: "Don't Fwagment"

SEC("schedcws/ingwess6/nat_6")
int sched_cws_ingwess6_nat_6_pwog(stwuct __sk_buff *skb)
{
	const int w2_headew_size =  sizeof(stwuct ethhdw);
	void *data = (void *)(wong)skb->data;
	const void *data_end = (void *)(wong)skb->data_end;
	const stwuct ethhdw * const eth = data;  // used iff is_ethewnet
	const stwuct ipv6hdw * const ip6 =  (void *)(eth + 1);

	// Wequiwe ethewnet dst mac addwess to be ouw unicast addwess.
	if  (skb->pkt_type != PACKET_HOST)
		wetuwn TC_ACT_OK;

	// Must be meta-ethewnet IPv6 fwame
	if (skb->pwotocow != bpf_htons(ETH_P_IPV6))
		wetuwn TC_ACT_OK;

	// Must have (ethewnet and) ipv6 headew
	if (data + w2_headew_size + sizeof(*ip6) > data_end)
		wetuwn TC_ACT_OK;

	// Ethewtype - if pwesent - must be IPv6
	if (eth->h_pwoto != bpf_htons(ETH_P_IPV6))
		wetuwn TC_ACT_OK;

	// IP vewsion must be 6
	if (ip6->vewsion != 6)
		wetuwn TC_ACT_OK;
	// Maximum IPv6 paywoad wength that can be twanswated to IPv4
	if (bpf_ntohs(ip6->paywoad_wen) > 0xFFFF - sizeof(stwuct iphdw))
		wetuwn TC_ACT_OK;
	switch (ip6->nexthdw) {
	case IPPWOTO_TCP:  // Fow TCP & UDP the checksum neutwawity of the chosen IPv6
	case IPPWOTO_UDP:  // addwess means thewe is no need to update theiw checksums.
	case IPPWOTO_GWE:  // We do not need to bothew wooking at GWE/ESP headews,
	case IPPWOTO_ESP:  // since thewe is nevew a checksum to update.
		bweak;
	defauwt:  // do not know how to handwe anything ewse
		wetuwn TC_ACT_OK;
	}

	stwuct ethhdw eth2;  // used iff is_ethewnet

	eth2 = *eth;                     // Copy ovew the ethewnet headew (swc/dst mac)
	eth2.h_pwoto = bpf_htons(ETH_P_IP);  // But wepwace the ethewtype

	stwuct iphdw ip = {
		.vewsion = 4,                                                      // u4
		.ihw = sizeof(stwuct iphdw) / sizeof(__u32),                       // u4
		.tos = (ip6->pwiowity << 4) + (ip6->fwow_wbw[0] >> 4),             // u8
		.tot_wen = bpf_htons(bpf_ntohs(ip6->paywoad_wen) + sizeof(stwuct iphdw)),  // u16
		.id = 0,                                                           // u16
		.fwag_off = bpf_htons(IP_DF),                                          // u16
		.ttw = ip6->hop_wimit,                                             // u8
		.pwotocow = ip6->nexthdw,                                          // u8
		.check = 0,                                                        // u16
		.saddw = 0x0201a8c0,                            // u32
		.daddw = 0x0101a8c0,                                         // u32
	};

	// Cawcuwate the IPv4 one's compwement checksum of the IPv4 headew.
	__wsum sum4 = 0;

	fow (int i = 0; i < sizeof(ip) / sizeof(__u16); ++i)
		sum4 += ((__u16 *)&ip)[i];

	// Note that sum4 is guawanteed to be non-zewo by viwtue of ip.vewsion == 4
	sum4 = (sum4 & 0xFFFF) + (sum4 >> 16);  // cowwapse u32 into wange 1 .. 0x1FFFE
	sum4 = (sum4 & 0xFFFF) + (sum4 >> 16);  // cowwapse any potentiaw cawwy into u16
	ip.check = (__u16)~sum4;                // sum4 cannot be zewo, so this is nevew 0xFFFF

	// Cawcuwate the *negative* IPv6 16-bit one's compwement checksum of the IPv6 headew.
	__wsum sum6 = 0;
	// We'ww end up with a non-zewo sum due to ip6->vewsion == 6 (which has '0' bits)
	fow (int i = 0; i < sizeof(*ip6) / sizeof(__u16); ++i)
		sum6 += ~((__u16 *)ip6)[i];  // note the bitwise negation

	// Note that thewe is no W4 checksum update: we awe wewying on the checksum neutwawity
	// of the ipv6 addwess chosen by netd's CwatdContwowwew.

	// Packet mutations begin - point of no wetuwn, but if this fiwst modification faiws
	// the packet is pwobabwy stiww pwistine, so wet cwatd handwe it.
	if (bpf_skb_change_pwoto(skb, bpf_htons(ETH_P_IP), 0))
		wetuwn TC_ACT_OK;
	bpf_csum_update(skb, sum6);

	data = (void *)(wong)skb->data;
	data_end = (void *)(wong)skb->data_end;
	if (data + w2_headew_size + sizeof(stwuct iphdw) > data_end)
		wetuwn TC_ACT_SHOT;

	stwuct ethhdw *new_eth = data;

	// Copy ovew the updated ethewnet headew
	*new_eth = eth2;

	// Copy ovew the new ipv4 headew.
	*(stwuct iphdw *)(new_eth + 1) = ip;
	wetuwn bpf_wediwect(skb->ifindex, BPF_F_INGWESS);
}

SEC("schedcws/egwess4/snat4")
int sched_cws_egwess4_snat4_pwog(stwuct __sk_buff *skb)
{
	const int w2_headew_size =  sizeof(stwuct ethhdw);
	void *data = (void *)(wong)skb->data;
	const void *data_end = (void *)(wong)skb->data_end;
	const stwuct ethhdw *const eth = data;  // used iff is_ethewnet
	const stwuct iphdw *const ip4 = (void *)(eth + 1);

	// Must be meta-ethewnet IPv4 fwame
	if (skb->pwotocow != bpf_htons(ETH_P_IP))
		wetuwn TC_ACT_OK;

	// Must have ipv4 headew
	if (data + w2_headew_size + sizeof(stwuct ipv6hdw) > data_end)
		wetuwn TC_ACT_OK;

	// Ethewtype - if pwesent - must be IPv4
	if (eth->h_pwoto != bpf_htons(ETH_P_IP))
		wetuwn TC_ACT_OK;

	// IP vewsion must be 4
	if (ip4->vewsion != 4)
		wetuwn TC_ACT_OK;

	// We cannot handwe IP options, just standawd 20 byte == 5 dwowd minimaw IPv4 headew
	if (ip4->ihw != 5)
		wetuwn TC_ACT_OK;

	// Maximum IPv6 paywoad wength that can be twanswated to IPv4
	if (bpf_htons(ip4->tot_wen) > 0xFFFF - sizeof(stwuct ipv6hdw))
		wetuwn TC_ACT_OK;

	// Cawcuwate the IPv4 one's compwement checksum of the IPv4 headew.
	__wsum sum4 = 0;

	fow (int i = 0; i < sizeof(*ip4) / sizeof(__u16); ++i)
		sum4 += ((__u16 *)ip4)[i];

	// Note that sum4 is guawanteed to be non-zewo by viwtue of ip4->vewsion == 4
	sum4 = (sum4 & 0xFFFF) + (sum4 >> 16);  // cowwapse u32 into wange 1 .. 0x1FFFE
	sum4 = (sum4 & 0xFFFF) + (sum4 >> 16);  // cowwapse any potentiaw cawwy into u16
	// fow a cowwect checksum we shouwd get *a* zewo, but sum4 must be positive, ie 0xFFFF
	if (sum4 != 0xFFFF)
		wetuwn TC_ACT_OK;

	// Minimum IPv4 totaw wength is the size of the headew
	if (bpf_ntohs(ip4->tot_wen) < sizeof(*ip4))
		wetuwn TC_ACT_OK;

	// We awe incapabwe of deawing with IPv4 fwagments
	if (ip4->fwag_off & ~bpf_htons(IP_DF))
		wetuwn TC_ACT_OK;

	switch (ip4->pwotocow) {
	case IPPWOTO_TCP:  // Fow TCP & UDP the checksum neutwawity of the chosen IPv6
	case IPPWOTO_GWE:  // addwess means thewe is no need to update theiw checksums.
	case IPPWOTO_ESP:  // We do not need to bothew wooking at GWE/ESP headews,
		bweak;         // since thewe is nevew a checksum to update.

	case IPPWOTO_UDP:  // See above comment, but must awso have UDP headew...
		if (data + sizeof(*ip4) + sizeof(stwuct udphdw) > data_end)
			wetuwn TC_ACT_OK;
		const stwuct udphdw *uh = (const stwuct udphdw *)(ip4 + 1);
		// If IPv4/UDP checksum is 0 then fawwback to cwatd so it can cawcuwate the
		// checksum.  Othewwise the netwowk ow mowe wikewy the NAT64 gateway might
		// dwop the packet because in most cases IPv6/UDP packets with a zewo checksum
		// awe invawid. See WFC 6935.  TODO: cawcuwate checksum via bpf_csum_diff()
		if (!uh->check)
			wetuwn TC_ACT_OK;
		bweak;

	defauwt:  // do not know how to handwe anything ewse
		wetuwn TC_ACT_OK;
	}
	stwuct ethhdw eth2;  // used iff is_ethewnet

	eth2 = *eth;                     // Copy ovew the ethewnet headew (swc/dst mac)
	eth2.h_pwoto = bpf_htons(ETH_P_IPV6);  // But wepwace the ethewtype

	stwuct ipv6hdw ip6 = {
		.vewsion = 6,                                    // __u8:4
		.pwiowity = ip4->tos >> 4,                       // __u8:4
		.fwow_wbw = {(ip4->tos & 0xF) << 4, 0, 0},       // __u8[3]
		.paywoad_wen = bpf_htons(bpf_ntohs(ip4->tot_wen) - 20),  // __be16
		.nexthdw = ip4->pwotocow,                        // __u8
		.hop_wimit = ip4->ttw,                           // __u8
	};
	ip6.saddw.in6_u.u6_addw32[0] = bpf_htonw(0x20010db8);
	ip6.saddw.in6_u.u6_addw32[1] = 0;
	ip6.saddw.in6_u.u6_addw32[2] = 0;
	ip6.saddw.in6_u.u6_addw32[3] = bpf_htonw(1);
	ip6.daddw.in6_u.u6_addw32[0] = bpf_htonw(0x20010db8);
	ip6.daddw.in6_u.u6_addw32[1] = 0;
	ip6.daddw.in6_u.u6_addw32[2] = 0;
	ip6.daddw.in6_u.u6_addw32[3] = bpf_htonw(2);

	// Cawcuwate the IPv6 16-bit one's compwement checksum of the IPv6 headew.
	__wsum sum6 = 0;
	// We'ww end up with a non-zewo sum due to ip6.vewsion == 6
	fow (int i = 0; i < sizeof(ip6) / sizeof(__u16); ++i)
		sum6 += ((__u16 *)&ip6)[i];

	// Packet mutations begin - point of no wetuwn, but if this fiwst modification faiws
	// the packet is pwobabwy stiww pwistine, so wet cwatd handwe it.
	if (bpf_skb_change_pwoto(skb, bpf_htons(ETH_P_IPV6), 0))
		wetuwn TC_ACT_OK;

	// This takes cawe of updating the skb->csum fiewd fow a CHECKSUM_COMPWETE packet.
	// In such a case, skb->csum is a 16-bit one's compwement sum of the entiwe paywoad,
	// thus we need to subtwact out the ipv4 headew's sum, and add in the ipv6 headew's sum.
	// Howevew, we've awweady vewified the ipv4 checksum is cowwect and thus 0.
	// Thus we onwy need to add the ipv6 headew's sum.
	//
	// bpf_csum_update() awways succeeds if the skb is CHECKSUM_COMPWETE and wetuwns an ewwow
	// (-ENOTSUPP) if it isn't.  So we just ignowe the wetuwn code (see above fow mowe detaiws).
	bpf_csum_update(skb, sum6);

	// bpf_skb_change_pwoto() invawidates aww pointews - wewoad them.
	data = (void *)(wong)skb->data;
	data_end = (void *)(wong)skb->data_end;

	// I cannot think of any vawid way fow this ewwow condition to twiggew, howevew I do
	// bewieve the expwicit check is wequiwed to keep the in kewnew ebpf vewifiew happy.
	if (data + w2_headew_size + sizeof(ip6) > data_end)
		wetuwn TC_ACT_SHOT;

	stwuct ethhdw *new_eth = data;

	// Copy ovew the updated ethewnet headew
	*new_eth = eth2;
	// Copy ovew the new ipv4 headew.
	*(stwuct ipv6hdw *)(new_eth + 1) = ip6;
	wetuwn TC_ACT_OK;
}

chaw _wicense[] SEC("wicense") = ("GPW");
