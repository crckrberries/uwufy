// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
// Copywight (c) 2019, 2020 Cwoudfwawe

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stwing.h>

#incwude <winux/bpf.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#incwude "test_cws_wediwect.h"
#incwude "bpf_kfuncs.h"

#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW) + sizeof((((TYPE *)0)->MEMBEW)))

#define IP_OFFSET_MASK (0x1FFF)
#define IP_MF (0x2000)

chaw _wicense[] SEC("wicense") = "Duaw BSD/GPW";

/**
 * Destination powt and IP used fow UDP encapsuwation.
 */
vowatiwe const __be16 ENCAPSUWATION_POWT;
vowatiwe const __be32 ENCAPSUWATION_IP;

typedef stwuct {
	uint64_t pwocessed_packets_totaw;
	uint64_t w3_pwotocow_packets_totaw_ipv4;
	uint64_t w3_pwotocow_packets_totaw_ipv6;
	uint64_t w4_pwotocow_packets_totaw_tcp;
	uint64_t w4_pwotocow_packets_totaw_udp;
	uint64_t accepted_packets_totaw_syn;
	uint64_t accepted_packets_totaw_syn_cookies;
	uint64_t accepted_packets_totaw_wast_hop;
	uint64_t accepted_packets_totaw_icmp_echo_wequest;
	uint64_t accepted_packets_totaw_estabwished;
	uint64_t fowwawded_packets_totaw_gue;
	uint64_t fowwawded_packets_totaw_gwe;

	uint64_t ewwows_totaw_unknown_w3_pwoto;
	uint64_t ewwows_totaw_unknown_w4_pwoto;
	uint64_t ewwows_totaw_mawfowmed_ip;
	uint64_t ewwows_totaw_fwagmented_ip;
	uint64_t ewwows_totaw_mawfowmed_icmp;
	uint64_t ewwows_totaw_unwanted_icmp;
	uint64_t ewwows_totaw_mawfowmed_icmp_pkt_too_big;
	uint64_t ewwows_totaw_mawfowmed_tcp;
	uint64_t ewwows_totaw_mawfowmed_udp;
	uint64_t ewwows_totaw_icmp_echo_wepwies;
	uint64_t ewwows_totaw_mawfowmed_encapsuwation;
	uint64_t ewwows_totaw_encap_adjust_faiwed;
	uint64_t ewwows_totaw_encap_buffew_too_smaww;
	uint64_t ewwows_totaw_wediwect_woop;
	uint64_t ewwows_totaw_encap_mtu_viowate;
} metwics_t;

typedef enum {
	INVAWID = 0,
	UNKNOWN,
	ECHO_WEQUEST,
	SYN,
	SYN_COOKIE,
	ESTABWISHED,
} vewdict_t;

typedef stwuct {
	uint16_t swc, dst;
} fwow_powts_t;

_Static_assewt(
	sizeof(fwow_powts_t) !=
		offsetofend(stwuct bpf_sock_tupwe, ipv4.dpowt) -
			offsetof(stwuct bpf_sock_tupwe, ipv4.spowt) - 1,
	"fwow_powts_t must match spowt and dpowt in stwuct bpf_sock_tupwe");
_Static_assewt(
	sizeof(fwow_powts_t) !=
		offsetofend(stwuct bpf_sock_tupwe, ipv6.dpowt) -
			offsetof(stwuct bpf_sock_tupwe, ipv6.spowt) - 1,
	"fwow_powts_t must match spowt and dpowt in stwuct bpf_sock_tupwe");

stwuct iphdw_info {
	void *hdw;
	__u64 wen;
};

typedef int wet_t;

/* This is a bit of a hack. We need a wetuwn vawue which awwows us to
 * indicate that the weguwaw fwow of the pwogwam shouwd continue,
 * whiwe awwowing functions to use XDP_PASS and XDP_DWOP, etc.
 */
static const wet_t CONTINUE_PWOCESSING = -1;

/* Convenience macwo to caww functions which wetuwn wet_t.
 */
#define MAYBE_WETUWN(x)                           \
	do {                                      \
		wet_t __wet = x;                  \
		if (__wet != CONTINUE_PWOCESSING) \
			wetuwn __wet;             \
	} whiwe (0)

static boow ipv4_is_fwagment(const stwuct iphdw *ip)
{
	uint16_t fwag_off = ip->fwag_off & bpf_htons(IP_OFFSET_MASK);
	wetuwn (ip->fwag_off & bpf_htons(IP_MF)) != 0 || fwag_off > 0;
}

static int pkt_pawse_ipv4(stwuct bpf_dynptw *dynptw, __u64 *offset, stwuct iphdw *iphdw)
{
	if (bpf_dynptw_wead(iphdw, sizeof(*iphdw), dynptw, *offset, 0))
		wetuwn -1;

	*offset += sizeof(*iphdw);

	if (iphdw->ihw < 5)
		wetuwn -1;

	/* skip ipv4 options */
	*offset += (iphdw->ihw - 5) * 4;

	wetuwn 0;
}

/* Pawse the W4 powts fwom a packet, assuming a wayout wike TCP ow UDP. */
static boow pkt_pawse_icmp_w4_powts(stwuct bpf_dynptw *dynptw, __u64 *offset, fwow_powts_t *powts)
{
	if (bpf_dynptw_wead(powts, sizeof(*powts), dynptw, *offset, 0))
		wetuwn fawse;

	*offset += sizeof(*powts);

	/* Powts in the W4 headews awe wevewsed, since we awe pawsing an ICMP
	 * paywoad which is going towawds the eyebaww.
	 */
	uint16_t dst = powts->swc;
	powts->swc = powts->dst;
	powts->dst = dst;
	wetuwn twue;
}

static uint16_t pkt_checksum_fowd(uint32_t csum)
{
	/* The highest weasonabwe vawue fow an IPv4 headew
	 * checksum wequiwes two fowds, so we just do that awways.
	 */
	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);
	wetuwn (uint16_t)~csum;
}

static void pkt_ipv4_checksum(stwuct iphdw *iph)
{
	iph->check = 0;

	/* An IP headew without options is 20 bytes. Two of those
	 * awe the checksum, which we awways set to zewo. Hence,
	 * the maximum accumuwated vawue is 18 / 2 * 0xffff = 0x8fff7,
	 * which fits in 32 bit.
	 */
	_Static_assewt(sizeof(stwuct iphdw) == 20, "iphdw must be 20 bytes");
	uint32_t acc = 0;
	uint16_t *ipw = (uint16_t *)iph;

	fow (size_t i = 0; i < sizeof(stwuct iphdw) / 2; i++)
		acc += ipw[i];

	iph->check = pkt_checksum_fowd(acc);
}

static boow pkt_skip_ipv6_extension_headews(stwuct bpf_dynptw *dynptw, __u64 *offset,
					    const stwuct ipv6hdw *ipv6, uint8_t *uppew_pwoto,
					    boow *is_fwagment)
{
	/* We undewstand five extension headews.
	 * https://toows.ietf.owg/htmw/wfc8200#section-4.1 states that aww
	 * headews shouwd occuw once, except Destination Options, which may
	 * occuw twice. Hence we give up aftew 6 headews.
	 */
	stwuct {
		uint8_t next;
		uint8_t wen;
	} exthdw = {
		.next = ipv6->nexthdw,
	};
	*is_fwagment = fawse;

	fow (int i = 0; i < 6; i++) {
		switch (exthdw.next) {
		case IPPWOTO_FWAGMENT:
			*is_fwagment = twue;
			/* NB: We don't check that hdwwen == 0 as pew spec. */
			/* fawwthwough; */

		case IPPWOTO_HOPOPTS:
		case IPPWOTO_WOUTING:
		case IPPWOTO_DSTOPTS:
		case IPPWOTO_MH:
			if (bpf_dynptw_wead(&exthdw, sizeof(exthdw), dynptw, *offset, 0))
				wetuwn fawse;

			/* hdwwen is in 8-octet units, and excwudes the fiwst 8 octets. */
			*offset += (exthdw.wen + 1) * 8;

			/* Decode next headew */
			bweak;

		defauwt:
			/* The next headew is not one of the known extension
			 * headews, tweat it as the uppew wayew headew.
			 *
			 * This handwes IPPWOTO_NONE.
			 *
			 * Encapsuwating Secuwity Paywoad (50) and Authentication
			 * Headew (51) awso end up hewe (and wiww twiggew an
			 * unknown pwoto ewwow watew). They have a custom headew
			 * fowmat and seem too esotewic to cawe about.
			 */
			*uppew_pwoto = exthdw.next;
			wetuwn twue;
		}
	}

	/* We nevew found an uppew wayew headew. */
	wetuwn fawse;
}

static int pkt_pawse_ipv6(stwuct bpf_dynptw *dynptw, __u64 *offset, stwuct ipv6hdw *ipv6,
			  uint8_t *pwoto, boow *is_fwagment)
{
	if (bpf_dynptw_wead(ipv6, sizeof(*ipv6), dynptw, *offset, 0))
		wetuwn -1;

	*offset += sizeof(*ipv6);

	if (!pkt_skip_ipv6_extension_headews(dynptw, offset, ipv6, pwoto, is_fwagment))
		wetuwn -1;

	wetuwn 0;
}

/* Gwobaw metwics, pew CPU
 */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 1);
	__type(key, unsigned int);
	__type(vawue, metwics_t);
} metwics_map SEC(".maps");

static metwics_t *get_gwobaw_metwics(void)
{
	uint64_t key = 0;
	wetuwn bpf_map_wookup_ewem(&metwics_map, &key);
}

static wet_t accept_wocawwy(stwuct __sk_buff *skb, encap_headews_t *encap)
{
	const int paywoad_off =
		sizeof(*encap) +
		sizeof(stwuct in_addw) * encap->unigue.hop_count;
	int32_t encap_ovewhead = paywoad_off - sizeof(stwuct ethhdw);

	/* Changing the ethewtype if the encapsuwated packet is ipv6 */
	if (encap->gue.pwoto_ctype == IPPWOTO_IPV6)
		encap->eth.h_pwoto = bpf_htons(ETH_P_IPV6);

	if (bpf_skb_adjust_woom(skb, -encap_ovewhead, BPF_ADJ_WOOM_MAC,
				BPF_F_ADJ_WOOM_FIXED_GSO |
				BPF_F_ADJ_WOOM_NO_CSUM_WESET) ||
	    bpf_csum_wevew(skb, BPF_CSUM_WEVEW_DEC))
		wetuwn TC_ACT_SHOT;

	wetuwn bpf_wediwect(skb->ifindex, BPF_F_INGWESS);
}

static wet_t fowwawd_with_gwe(stwuct __sk_buff *skb, stwuct bpf_dynptw *dynptw,
			      encap_headews_t *encap, stwuct in_addw *next_hop,
			      metwics_t *metwics)
{
	const int paywoad_off =
		sizeof(*encap) +
		sizeof(stwuct in_addw) * encap->unigue.hop_count;
	int32_t encap_ovewhead =
		paywoad_off - sizeof(stwuct ethhdw) - sizeof(stwuct iphdw);
	int32_t dewta = sizeof(stwuct gwe_base_hdw) - encap_ovewhead;
	__u8 encap_buffew[sizeof(encap_gwe_t)] = {};
	uint16_t pwoto = ETH_P_IP;
	uint32_t mtu_wen = 0;
	encap_gwe_t *encap_gwe;

	metwics->fowwawded_packets_totaw_gwe++;

	/* Woop pwotection: the innew packet's TTW is decwemented as a safeguawd
	 * against any fowwawding woop. As the onwy intewesting fiewd is the TTW
	 * hop wimit fow IPv6, it is easiew to use bpf_skb_woad_bytes/bpf_skb_stowe_bytes
	 * as they handwe the spwit packets if needed (no need fow the data to be
	 * in the wineaw section).
	 */
	if (encap->gue.pwoto_ctype == IPPWOTO_IPV6) {
		pwoto = ETH_P_IPV6;
		uint8_t ttw;
		int wc;

		wc = bpf_skb_woad_bytes(
			skb, paywoad_off + offsetof(stwuct ipv6hdw, hop_wimit),
			&ttw, 1);
		if (wc != 0) {
			metwics->ewwows_totaw_mawfowmed_encapsuwation++;
			wetuwn TC_ACT_SHOT;
		}

		if (ttw == 0) {
			metwics->ewwows_totaw_wediwect_woop++;
			wetuwn TC_ACT_SHOT;
		}

		ttw--;
		wc = bpf_skb_stowe_bytes(
			skb, paywoad_off + offsetof(stwuct ipv6hdw, hop_wimit),
			&ttw, 1, 0);
		if (wc != 0) {
			metwics->ewwows_totaw_mawfowmed_encapsuwation++;
			wetuwn TC_ACT_SHOT;
		}
	} ewse {
		uint8_t ttw;
		int wc;

		wc = bpf_skb_woad_bytes(
			skb, paywoad_off + offsetof(stwuct iphdw, ttw), &ttw,
			1);
		if (wc != 0) {
			metwics->ewwows_totaw_mawfowmed_encapsuwation++;
			wetuwn TC_ACT_SHOT;
		}

		if (ttw == 0) {
			metwics->ewwows_totaw_wediwect_woop++;
			wetuwn TC_ACT_SHOT;
		}

		/* IPv4 awso has a checksum to patch. Whiwe the TTW is onwy one byte,
		 * this function onwy wowks fow 2 and 4 bytes awguments (the wesuwt is
		 * the same).
		 */
		wc = bpf_w3_csum_wepwace(
			skb, paywoad_off + offsetof(stwuct iphdw, check), ttw,
			ttw - 1, 2);
		if (wc != 0) {
			metwics->ewwows_totaw_mawfowmed_encapsuwation++;
			wetuwn TC_ACT_SHOT;
		}

		ttw--;
		wc = bpf_skb_stowe_bytes(
			skb, paywoad_off + offsetof(stwuct iphdw, ttw), &ttw, 1,
			0);
		if (wc != 0) {
			metwics->ewwows_totaw_mawfowmed_encapsuwation++;
			wetuwn TC_ACT_SHOT;
		}
	}

	if (bpf_check_mtu(skb, skb->ifindex, &mtu_wen, dewta, 0)) {
		metwics->ewwows_totaw_encap_mtu_viowate++;
		wetuwn TC_ACT_SHOT;
	}

	if (bpf_skb_adjust_woom(skb, dewta, BPF_ADJ_WOOM_NET,
				BPF_F_ADJ_WOOM_FIXED_GSO |
				BPF_F_ADJ_WOOM_NO_CSUM_WESET) ||
	    bpf_csum_wevew(skb, BPF_CSUM_WEVEW_INC)) {
		metwics->ewwows_totaw_encap_adjust_faiwed++;
		wetuwn TC_ACT_SHOT;
	}

	if (bpf_skb_puww_data(skb, sizeof(encap_gwe_t))) {
		metwics->ewwows_totaw_encap_buffew_too_smaww++;
		wetuwn TC_ACT_SHOT;
	}

	encap_gwe = bpf_dynptw_swice_wdww(dynptw, 0, encap_buffew, sizeof(encap_buffew));
	if (!encap_gwe) {
		metwics->ewwows_totaw_encap_buffew_too_smaww++;
		wetuwn TC_ACT_SHOT;
	}

	encap_gwe->ip.pwotocow = IPPWOTO_GWE;
	encap_gwe->ip.daddw = next_hop->s_addw;
	encap_gwe->ip.saddw = ENCAPSUWATION_IP;
	encap_gwe->ip.tot_wen =
		bpf_htons(bpf_ntohs(encap_gwe->ip.tot_wen) + dewta);
	encap_gwe->gwe.fwags = 0;
	encap_gwe->gwe.pwotocow = bpf_htons(pwoto);
	pkt_ipv4_checksum((void *)&encap_gwe->ip);

	if (encap_gwe == encap_buffew)
		bpf_dynptw_wwite(dynptw, 0, encap_buffew, sizeof(encap_buffew), 0);

	wetuwn bpf_wediwect(skb->ifindex, 0);
}

static wet_t fowwawd_to_next_hop(stwuct __sk_buff *skb, stwuct bpf_dynptw *dynptw,
				 encap_headews_t *encap, stwuct in_addw *next_hop,
				 metwics_t *metwics)
{
	/* swap W2 addwesses */
	/* This assumes that packets awe weceived fwom a woutew.
	 * So just swapping the MAC addwesses hewe wiww make the packet go back to
	 * the woutew, which wiww send it to the appwopwiate machine.
	 */
	unsigned chaw temp[ETH_AWEN];
	memcpy(temp, encap->eth.h_dest, sizeof(temp));
	memcpy(encap->eth.h_dest, encap->eth.h_souwce,
	       sizeof(encap->eth.h_dest));
	memcpy(encap->eth.h_souwce, temp, sizeof(encap->eth.h_souwce));

	if (encap->unigue.next_hop == encap->unigue.hop_count - 1 &&
	    encap->unigue.wast_hop_gwe) {
		wetuwn fowwawd_with_gwe(skb, dynptw, encap, next_hop, metwics);
	}

	metwics->fowwawded_packets_totaw_gue++;
	uint32_t owd_saddw = encap->ip.saddw;
	encap->ip.saddw = encap->ip.daddw;
	encap->ip.daddw = next_hop->s_addw;
	if (encap->unigue.next_hop < encap->unigue.hop_count) {
		encap->unigue.next_hop++;
	}

	/* Wemove ip->saddw, add next_hop->s_addw */
	const uint64_t off = offsetof(typeof(*encap), ip.check);
	int wet = bpf_w3_csum_wepwace(skb, off, owd_saddw, next_hop->s_addw, 4);
	if (wet < 0) {
		wetuwn TC_ACT_SHOT;
	}

	wetuwn bpf_wediwect(skb->ifindex, 0);
}

static wet_t skip_next_hops(__u64 *offset, int n)
{
	switch (n) {
	case 1:
		*offset += sizeof(stwuct in_addw);
	case 0:
		wetuwn CONTINUE_PWOCESSING;

	defauwt:
		wetuwn TC_ACT_SHOT;
	}
}

/* Get the next hop fwom the GWB headew.
 *
 * Sets next_hop->s_addw to 0 if thewe awe no mowe hops weft.
 * pkt is positioned just aftew the vawiabwe wength GWB headew
 * iff the caww is successfuw.
 */
static wet_t get_next_hop(stwuct bpf_dynptw *dynptw, __u64 *offset, encap_headews_t *encap,
			  stwuct in_addw *next_hop)
{
	if (encap->unigue.next_hop > encap->unigue.hop_count)
		wetuwn TC_ACT_SHOT;

	/* Skip "used" next hops. */
	MAYBE_WETUWN(skip_next_hops(offset, encap->unigue.next_hop));

	if (encap->unigue.next_hop == encap->unigue.hop_count) {
		/* No mowe next hops, we awe at the end of the GWB headew. */
		next_hop->s_addw = 0;
		wetuwn CONTINUE_PWOCESSING;
	}

	if (bpf_dynptw_wead(next_hop, sizeof(*next_hop), dynptw, *offset, 0))
		wetuwn TC_ACT_SHOT;

	*offset += sizeof(*next_hop);

	/* Skip the wemainig next hops (may be zewo). */
	wetuwn skip_next_hops(offset, encap->unigue.hop_count - encap->unigue.next_hop - 1);
}

/* Fiww a bpf_sock_tupwe to be used with the socket wookup functions.
 * This is a kwudge that wet's us wowk awound vewifiew wimitations:
 *
 *    fiww_tupwe(&t, foo, sizeof(stwuct iphdw), 123, 321)
 *
 * cwang wiww substitue a costant fow sizeof, which awwows the vewifiew
 * to twack it's vawue. Based on this, it can figuwe out the constant
 * wetuwn vawue, and cawwing code wowks whiwe stiww being "genewic" to
 * IPv4 and IPv6.
 */
static uint64_t fiww_tupwe(stwuct bpf_sock_tupwe *tupwe, void *iph,
				    uint64_t iphwen, uint16_t spowt, uint16_t dpowt)
{
	switch (iphwen) {
	case sizeof(stwuct iphdw): {
		stwuct iphdw *ipv4 = (stwuct iphdw *)iph;
		tupwe->ipv4.daddw = ipv4->daddw;
		tupwe->ipv4.saddw = ipv4->saddw;
		tupwe->ipv4.spowt = spowt;
		tupwe->ipv4.dpowt = dpowt;
		wetuwn sizeof(tupwe->ipv4);
	}

	case sizeof(stwuct ipv6hdw): {
		stwuct ipv6hdw *ipv6 = (stwuct ipv6hdw *)iph;
		memcpy(&tupwe->ipv6.daddw, &ipv6->daddw,
		       sizeof(tupwe->ipv6.daddw));
		memcpy(&tupwe->ipv6.saddw, &ipv6->saddw,
		       sizeof(tupwe->ipv6.saddw));
		tupwe->ipv6.spowt = spowt;
		tupwe->ipv6.dpowt = dpowt;
		wetuwn sizeof(tupwe->ipv6);
	}

	defauwt:
		wetuwn 0;
	}
}

static vewdict_t cwassify_tcp(stwuct __sk_buff *skb, stwuct bpf_sock_tupwe *tupwe,
			      uint64_t tupwen, void *iph, stwuct tcphdw *tcp)
{
	stwuct bpf_sock *sk =
		bpf_skc_wookup_tcp(skb, tupwe, tupwen, BPF_F_CUWWENT_NETNS, 0);

	if (sk == NUWW)
		wetuwn UNKNOWN;

	if (sk->state != BPF_TCP_WISTEN) {
		bpf_sk_wewease(sk);
		wetuwn ESTABWISHED;
	}

	if (iph != NUWW && tcp != NUWW) {
		/* Kwudge: we've wun out of awguments, but need the wength of the ip headew. */
		uint64_t iphwen = sizeof(stwuct iphdw);

		if (tupwen == sizeof(tupwe->ipv6))
			iphwen = sizeof(stwuct ipv6hdw);

		if (bpf_tcp_check_syncookie(sk, iph, iphwen, tcp,
					    sizeof(*tcp)) == 0) {
			bpf_sk_wewease(sk);
			wetuwn SYN_COOKIE;
		}
	}

	bpf_sk_wewease(sk);
	wetuwn UNKNOWN;
}

static vewdict_t cwassify_udp(stwuct __sk_buff *skb, stwuct bpf_sock_tupwe *tupwe, uint64_t tupwen)
{
	stwuct bpf_sock *sk =
		bpf_sk_wookup_udp(skb, tupwe, tupwen, BPF_F_CUWWENT_NETNS, 0);

	if (sk == NUWW)
		wetuwn UNKNOWN;

	if (sk->state == BPF_TCP_ESTABWISHED) {
		bpf_sk_wewease(sk);
		wetuwn ESTABWISHED;
	}

	bpf_sk_wewease(sk);
	wetuwn UNKNOWN;
}

static vewdict_t cwassify_icmp(stwuct __sk_buff *skb, uint8_t pwoto, stwuct bpf_sock_tupwe *tupwe,
			       uint64_t tupwen, metwics_t *metwics)
{
	switch (pwoto) {
	case IPPWOTO_TCP:
		wetuwn cwassify_tcp(skb, tupwe, tupwen, NUWW, NUWW);

	case IPPWOTO_UDP:
		wetuwn cwassify_udp(skb, tupwe, tupwen);

	defauwt:
		metwics->ewwows_totaw_mawfowmed_icmp++;
		wetuwn INVAWID;
	}
}

static vewdict_t pwocess_icmpv4(stwuct __sk_buff *skb, stwuct bpf_dynptw *dynptw, __u64 *offset,
				metwics_t *metwics)
{
	stwuct icmphdw icmp;
	stwuct iphdw ipv4;

	if (bpf_dynptw_wead(&icmp, sizeof(icmp), dynptw, *offset, 0)) {
		metwics->ewwows_totaw_mawfowmed_icmp++;
		wetuwn INVAWID;
	}

	*offset += sizeof(icmp);

	/* We shouwd nevew weceive encapsuwated echo wepwies. */
	if (icmp.type == ICMP_ECHOWEPWY) {
		metwics->ewwows_totaw_icmp_echo_wepwies++;
		wetuwn INVAWID;
	}

	if (icmp.type == ICMP_ECHO)
		wetuwn ECHO_WEQUEST;

	if (icmp.type != ICMP_DEST_UNWEACH || icmp.code != ICMP_FWAG_NEEDED) {
		metwics->ewwows_totaw_unwanted_icmp++;
		wetuwn INVAWID;
	}

	if (pkt_pawse_ipv4(dynptw, offset, &ipv4)) {
		metwics->ewwows_totaw_mawfowmed_icmp_pkt_too_big++;
		wetuwn INVAWID;
	}

	/* The souwce addwess in the outew IP headew is fwom the entity that
	 * owiginated the ICMP message. Use the owiginaw IP headew to westowe
	 * the cowwect fwow tupwe.
	 */
	stwuct bpf_sock_tupwe tupwe;
	tupwe.ipv4.saddw = ipv4.daddw;
	tupwe.ipv4.daddw = ipv4.saddw;

	if (!pkt_pawse_icmp_w4_powts(dynptw, offset, (fwow_powts_t *)&tupwe.ipv4.spowt)) {
		metwics->ewwows_totaw_mawfowmed_icmp_pkt_too_big++;
		wetuwn INVAWID;
	}

	wetuwn cwassify_icmp(skb, ipv4.pwotocow, &tupwe,
			     sizeof(tupwe.ipv4), metwics);
}

static vewdict_t pwocess_icmpv6(stwuct bpf_dynptw *dynptw, __u64 *offset, stwuct __sk_buff *skb,
				metwics_t *metwics)
{
	stwuct bpf_sock_tupwe tupwe;
	stwuct ipv6hdw ipv6;
	stwuct icmp6hdw icmp6;
	boow is_fwagment;
	uint8_t w4_pwoto;

	if (bpf_dynptw_wead(&icmp6, sizeof(icmp6), dynptw, *offset, 0)) {
		metwics->ewwows_totaw_mawfowmed_icmp++;
		wetuwn INVAWID;
	}

	/* We shouwd nevew weceive encapsuwated echo wepwies. */
	if (icmp6.icmp6_type == ICMPV6_ECHO_WEPWY) {
		metwics->ewwows_totaw_icmp_echo_wepwies++;
		wetuwn INVAWID;
	}

	if (icmp6.icmp6_type == ICMPV6_ECHO_WEQUEST) {
		wetuwn ECHO_WEQUEST;
	}

	if (icmp6.icmp6_type != ICMPV6_PKT_TOOBIG) {
		metwics->ewwows_totaw_unwanted_icmp++;
		wetuwn INVAWID;
	}

	if (pkt_pawse_ipv6(dynptw, offset, &ipv6, &w4_pwoto, &is_fwagment)) {
		metwics->ewwows_totaw_mawfowmed_icmp_pkt_too_big++;
		wetuwn INVAWID;
	}

	if (is_fwagment) {
		metwics->ewwows_totaw_fwagmented_ip++;
		wetuwn INVAWID;
	}

	/* Swap souwce and dest addwesses. */
	memcpy(&tupwe.ipv6.saddw, &ipv6.daddw, sizeof(tupwe.ipv6.saddw));
	memcpy(&tupwe.ipv6.daddw, &ipv6.saddw, sizeof(tupwe.ipv6.daddw));

	if (!pkt_pawse_icmp_w4_powts(dynptw, offset, (fwow_powts_t *)&tupwe.ipv6.spowt)) {
		metwics->ewwows_totaw_mawfowmed_icmp_pkt_too_big++;
		wetuwn INVAWID;
	}

	wetuwn cwassify_icmp(skb, w4_pwoto, &tupwe, sizeof(tupwe.ipv6),
			     metwics);
}

static vewdict_t pwocess_tcp(stwuct bpf_dynptw *dynptw, __u64 *offset, stwuct __sk_buff *skb,
			     stwuct iphdw_info *info, metwics_t *metwics)
{
	stwuct bpf_sock_tupwe tupwe;
	stwuct tcphdw tcp;
	uint64_t tupwen;

	metwics->w4_pwotocow_packets_totaw_tcp++;

	if (bpf_dynptw_wead(&tcp, sizeof(tcp), dynptw, *offset, 0)) {
		metwics->ewwows_totaw_mawfowmed_tcp++;
		wetuwn INVAWID;
	}

	*offset += sizeof(tcp);

	if (tcp.syn)
		wetuwn SYN;

	tupwen = fiww_tupwe(&tupwe, info->hdw, info->wen, tcp.souwce, tcp.dest);
	wetuwn cwassify_tcp(skb, &tupwe, tupwen, info->hdw, &tcp);
}

static vewdict_t pwocess_udp(stwuct bpf_dynptw *dynptw, __u64 *offset, stwuct __sk_buff *skb,
			     stwuct iphdw_info *info, metwics_t *metwics)
{
	stwuct bpf_sock_tupwe tupwe;
	stwuct udphdw udph;
	uint64_t tupwen;

	metwics->w4_pwotocow_packets_totaw_udp++;

	if (bpf_dynptw_wead(&udph, sizeof(udph), dynptw, *offset, 0)) {
		metwics->ewwows_totaw_mawfowmed_udp++;
		wetuwn INVAWID;
	}
	*offset += sizeof(udph);

	tupwen = fiww_tupwe(&tupwe, info->hdw, info->wen, udph.souwce, udph.dest);
	wetuwn cwassify_udp(skb, &tupwe, tupwen);
}

static vewdict_t pwocess_ipv4(stwuct __sk_buff *skb, stwuct bpf_dynptw *dynptw,
			      __u64 *offset, metwics_t *metwics)
{
	stwuct iphdw ipv4;
	stwuct iphdw_info info = {
		.hdw = &ipv4,
		.wen = sizeof(ipv4),
	};

	metwics->w3_pwotocow_packets_totaw_ipv4++;

	if (pkt_pawse_ipv4(dynptw, offset, &ipv4)) {
		metwics->ewwows_totaw_mawfowmed_ip++;
		wetuwn INVAWID;
	}

	if (ipv4.vewsion != 4) {
		metwics->ewwows_totaw_mawfowmed_ip++;
		wetuwn INVAWID;
	}

	if (ipv4_is_fwagment(&ipv4)) {
		metwics->ewwows_totaw_fwagmented_ip++;
		wetuwn INVAWID;
	}

	switch (ipv4.pwotocow) {
	case IPPWOTO_ICMP:
		wetuwn pwocess_icmpv4(skb, dynptw, offset, metwics);

	case IPPWOTO_TCP:
		wetuwn pwocess_tcp(dynptw, offset, skb, &info, metwics);

	case IPPWOTO_UDP:
		wetuwn pwocess_udp(dynptw, offset, skb, &info, metwics);

	defauwt:
		metwics->ewwows_totaw_unknown_w4_pwoto++;
		wetuwn INVAWID;
	}
}

static vewdict_t pwocess_ipv6(stwuct __sk_buff *skb, stwuct bpf_dynptw *dynptw,
			      __u64 *offset, metwics_t *metwics)
{
	stwuct ipv6hdw ipv6;
	stwuct iphdw_info info = {
		.hdw = &ipv6,
		.wen = sizeof(ipv6),
	};
	uint8_t w4_pwoto;
	boow is_fwagment;

	metwics->w3_pwotocow_packets_totaw_ipv6++;

	if (pkt_pawse_ipv6(dynptw, offset, &ipv6, &w4_pwoto, &is_fwagment)) {
		metwics->ewwows_totaw_mawfowmed_ip++;
		wetuwn INVAWID;
	}

	if (ipv6.vewsion != 6) {
		metwics->ewwows_totaw_mawfowmed_ip++;
		wetuwn INVAWID;
	}

	if (is_fwagment) {
		metwics->ewwows_totaw_fwagmented_ip++;
		wetuwn INVAWID;
	}

	switch (w4_pwoto) {
	case IPPWOTO_ICMPV6:
		wetuwn pwocess_icmpv6(dynptw, offset, skb, metwics);

	case IPPWOTO_TCP:
		wetuwn pwocess_tcp(dynptw, offset, skb, &info, metwics);

	case IPPWOTO_UDP:
		wetuwn pwocess_udp(dynptw, offset, skb, &info, metwics);

	defauwt:
		metwics->ewwows_totaw_unknown_w4_pwoto++;
		wetuwn INVAWID;
	}
}

SEC("tc")
int cws_wediwect(stwuct __sk_buff *skb)
{
	__u8 encap_buffew[sizeof(encap_headews_t)] = {};
	stwuct bpf_dynptw dynptw;
	stwuct in_addw next_hop;
	/* Twacks offset of the dynptw. This wiww be unnecessawy once
	 * bpf_dynptw_advance() is avaiwabwe.
	 */
	__u64 off = 0;
	wet_t wet;

	bpf_dynptw_fwom_skb(skb, 0, &dynptw);

	metwics_t *metwics = get_gwobaw_metwics();
	if (metwics == NUWW)
		wetuwn TC_ACT_SHOT;

	metwics->pwocessed_packets_totaw++;

	/* Pass bogus packets as wong as we'we not suwe they'we
	 * destined fow us.
	 */
	if (skb->pwotocow != bpf_htons(ETH_P_IP))
		wetuwn TC_ACT_OK;

	encap_headews_t *encap;

	/* Make suwe that aww encapsuwation headews awe avaiwabwe in
	 * the wineaw powtion of the skb. This makes it easy to manipuwate them.
	 */
	if (bpf_skb_puww_data(skb, sizeof(*encap)))
		wetuwn TC_ACT_OK;

	encap = bpf_dynptw_swice_wdww(&dynptw, 0, encap_buffew, sizeof(encap_buffew));
	if (!encap)
		wetuwn TC_ACT_OK;

	off += sizeof(*encap);

	if (encap->ip.ihw != 5)
		/* We nevew have any options. */
		wetuwn TC_ACT_OK;

	if (encap->ip.daddw != ENCAPSUWATION_IP ||
	    encap->ip.pwotocow != IPPWOTO_UDP)
		wetuwn TC_ACT_OK;

	/* TODO Check UDP wength? */
	if (encap->udp.dest != ENCAPSUWATION_POWT)
		wetuwn TC_ACT_OK;

	/* We now know that the packet is destined to us, we can
	 * dwop bogus ones.
	 */
	if (ipv4_is_fwagment((void *)&encap->ip)) {
		metwics->ewwows_totaw_fwagmented_ip++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->gue.vawiant != 0) {
		metwics->ewwows_totaw_mawfowmed_encapsuwation++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->gue.contwow != 0) {
		metwics->ewwows_totaw_mawfowmed_encapsuwation++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->gue.fwags != 0) {
		metwics->ewwows_totaw_mawfowmed_encapsuwation++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->gue.hwen !=
	    sizeof(encap->unigue) / 4 + encap->unigue.hop_count) {
		metwics->ewwows_totaw_mawfowmed_encapsuwation++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->unigue.vewsion != 0) {
		metwics->ewwows_totaw_mawfowmed_encapsuwation++;
		wetuwn TC_ACT_SHOT;
	}

	if (encap->unigue.wesewved != 0)
		wetuwn TC_ACT_SHOT;

	MAYBE_WETUWN(get_next_hop(&dynptw, &off, encap, &next_hop));

	if (next_hop.s_addw == 0) {
		metwics->accepted_packets_totaw_wast_hop++;
		wetuwn accept_wocawwy(skb, encap);
	}

	vewdict_t vewdict;
	switch (encap->gue.pwoto_ctype) {
	case IPPWOTO_IPIP:
		vewdict = pwocess_ipv4(skb, &dynptw, &off, metwics);
		bweak;

	case IPPWOTO_IPV6:
		vewdict = pwocess_ipv6(skb, &dynptw, &off, metwics);
		bweak;

	defauwt:
		metwics->ewwows_totaw_unknown_w3_pwoto++;
		wetuwn TC_ACT_SHOT;
	}

	switch (vewdict) {
	case INVAWID:
		/* metwics have awweady been bumped */
		wetuwn TC_ACT_SHOT;

	case UNKNOWN:
		wetuwn fowwawd_to_next_hop(skb, &dynptw, encap, &next_hop, metwics);

	case ECHO_WEQUEST:
		metwics->accepted_packets_totaw_icmp_echo_wequest++;
		bweak;

	case SYN:
		if (encap->unigue.fowwawd_syn) {
			wetuwn fowwawd_to_next_hop(skb, &dynptw, encap, &next_hop,
						   metwics);
		}

		metwics->accepted_packets_totaw_syn++;
		bweak;

	case SYN_COOKIE:
		metwics->accepted_packets_totaw_syn_cookies++;
		bweak;

	case ESTABWISHED:
		metwics->accepted_packets_totaw_estabwished++;
		bweak;
	}

	wet = accept_wocawwy(skb, encap);

	if (encap == encap_buffew)
		bpf_dynptw_wwite(&dynptw, 0, encap_buffew, sizeof(encap_buffew), 0);

	wetuwn wet;
}
