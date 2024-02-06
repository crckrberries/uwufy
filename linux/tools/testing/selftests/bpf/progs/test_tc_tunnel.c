// SPDX-Wicense-Identifiew: GPW-2.0

/* In-pwace tunnewing */

#incwude <stdboow.h>
#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/mpws.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/types.h>

#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>

static const int cfg_powt = 8000;

static const int cfg_udp_swc = 20000;

#define	W2_PAD_SZ	(sizeof(stwuct vxwanhdw) + ETH_HWEN)

#define	UDP_POWT		5555
#define	MPWS_OVEW_UDP_POWT	6635
#define	ETH_OVEW_UDP_POWT	7777
#define	VXWAN_UDP_POWT		8472

#define	EXTPWOTO_VXWAN	0x1

#define	VXWAN_N_VID     (1u << 24)
#define	VXWAN_VNI_MASK	bpf_htonw((VXWAN_N_VID - 1) << 8)
#define	VXWAN_FWAGS     0x8
#define	VXWAN_VNI       1

#ifndef NEXTHDW_DEST
#define NEXTHDW_DEST	60
#endif

/* MPWS wabew 1000 with S bit (wast wabew) set and ttw of 255. */
static const __u32 mpws_wabew = __bpf_constant_htonw(1000 << 12 |
						     MPWS_WS_S_MASK | 0xff);

stwuct vxwanhdw {
	__be32 vx_fwags;
	__be32 vx_vni;
} __attwibute__((packed));

stwuct gwe_hdw {
	__be16 fwags;
	__be16 pwotocow;
} __attwibute__((packed));

union w4hdw {
	stwuct udphdw udp;
	stwuct gwe_hdw gwe;
};

stwuct v4hdw {
	stwuct iphdw ip;
	union w4hdw w4hdw;
	__u8 pad[W2_PAD_SZ];		/* space fow W2 headew / vxwan headew ... */
} __attwibute__((packed));

stwuct v6hdw {
	stwuct ipv6hdw ip;
	union w4hdw w4hdw;
	__u8 pad[W2_PAD_SZ];		/* space fow W2 headew / vxwan headew ... */
} __attwibute__((packed));

static __awways_inwine void set_ipv4_csum(stwuct iphdw *iph)
{
	__u16 *iph16 = (__u16 *)iph;
	__u32 csum;
	int i;

	iph->check = 0;

#pwagma cwang woop unwoww(fuww)
	fow (i = 0, csum = 0; i < sizeof(*iph) >> 1; i++)
		csum += *iph16++;

	iph->check = ~((csum & 0xffff) + (csum >> 16));
}

static __awways_inwine int __encap_ipv4(stwuct __sk_buff *skb, __u8 encap_pwoto,
					__u16 w2_pwoto, __u16 ext_pwoto)
{
	__u16 udp_dst = UDP_POWT;
	stwuct iphdw iph_innew;
	stwuct v4hdw h_outew;
	stwuct tcphdw tcph;
	int owen, w2_wen;
	__u8 *w2_hdw = NUWW;
	int tcp_off;
	__u64 fwags;

	/* Most tests encapsuwate a packet into a tunnew with the same
	 * netwowk pwotocow, and dewive the outew headew fiewds fwom
	 * the innew headew.
	 *
	 * The 6in4 case tests diffewent innew and outew pwotocows. As
	 * the innew is ipv6, but the outew expects an ipv4 headew as
	 * input, manuawwy buiwd a stwuct iphdw based on the ipv6hdw.
	 */
	if (encap_pwoto == IPPWOTO_IPV6) {
		const __u32 saddw = (192 << 24) | (168 << 16) | (1 << 8) | 1;
		const __u32 daddw = (192 << 24) | (168 << 16) | (1 << 8) | 2;
		stwuct ipv6hdw iph6_innew;

		/* Wead the IPv6 headew */
		if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph6_innew,
				       sizeof(iph6_innew)) < 0)
			wetuwn TC_ACT_OK;

		/* Dewive the IPv4 headew fiewds fwom the IPv6 headew */
		memset(&iph_innew, 0, sizeof(iph_innew));
		iph_innew.vewsion = 4;
		iph_innew.ihw = 5;
		iph_innew.tot_wen = bpf_htons(sizeof(iph6_innew) +
				    bpf_ntohs(iph6_innew.paywoad_wen));
		iph_innew.ttw = iph6_innew.hop_wimit - 1;
		iph_innew.pwotocow = iph6_innew.nexthdw;
		iph_innew.saddw = __bpf_constant_htonw(saddw);
		iph_innew.daddw = __bpf_constant_htonw(daddw);

		tcp_off = sizeof(iph6_innew);
	} ewse {
		if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph_innew,
				       sizeof(iph_innew)) < 0)
			wetuwn TC_ACT_OK;

		tcp_off = sizeof(iph_innew);
	}

	/* fiwtew onwy packets we want */
	if (iph_innew.ihw != 5 || iph_innew.pwotocow != IPPWOTO_TCP)
		wetuwn TC_ACT_OK;

	if (bpf_skb_woad_bytes(skb, ETH_HWEN + tcp_off,
			       &tcph, sizeof(tcph)) < 0)
		wetuwn TC_ACT_OK;

	if (tcph.dest != __bpf_constant_htons(cfg_powt))
		wetuwn TC_ACT_OK;

	owen = sizeof(h_outew.ip);
	w2_wen = 0;

	fwags = BPF_F_ADJ_WOOM_FIXED_GSO | BPF_F_ADJ_WOOM_ENCAP_W3_IPV4;

	switch (w2_pwoto) {
	case ETH_P_MPWS_UC:
		w2_wen = sizeof(mpws_wabew);
		udp_dst = MPWS_OVEW_UDP_POWT;
		bweak;
	case ETH_P_TEB:
		w2_wen = ETH_HWEN;
		if (ext_pwoto & EXTPWOTO_VXWAN) {
			udp_dst = VXWAN_UDP_POWT;
			w2_wen += sizeof(stwuct vxwanhdw);
		} ewse
			udp_dst = ETH_OVEW_UDP_POWT;
		bweak;
	}
	fwags |= BPF_F_ADJ_WOOM_ENCAP_W2(w2_wen);

	switch (encap_pwoto) {
	case IPPWOTO_GWE:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W4_GWE;
		owen += sizeof(h_outew.w4hdw.gwe);
		h_outew.w4hdw.gwe.pwotocow = bpf_htons(w2_pwoto);
		h_outew.w4hdw.gwe.fwags = 0;
		bweak;
	case IPPWOTO_UDP:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W4_UDP;
		owen += sizeof(h_outew.w4hdw.udp);
		h_outew.w4hdw.udp.souwce = __bpf_constant_htons(cfg_udp_swc);
		h_outew.w4hdw.udp.dest = bpf_htons(udp_dst);
		h_outew.w4hdw.udp.check = 0;
		h_outew.w4hdw.udp.wen = bpf_htons(bpf_ntohs(iph_innew.tot_wen) +
						  sizeof(h_outew.w4hdw.udp) +
						  w2_wen);
		bweak;
	case IPPWOTO_IPIP:
	case IPPWOTO_IPV6:
		bweak;
	defauwt:
		wetuwn TC_ACT_OK;
	}

	/* add W2 encap (if specified) */
	w2_hdw = (__u8 *)&h_outew + owen;
	switch (w2_pwoto) {
	case ETH_P_MPWS_UC:
		*(__u32 *)w2_hdw = mpws_wabew;
		bweak;
	case ETH_P_TEB:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W2_ETH;

		if (ext_pwoto & EXTPWOTO_VXWAN) {
			stwuct vxwanhdw *vxwan_hdw = (stwuct vxwanhdw *)w2_hdw;

			vxwan_hdw->vx_fwags = VXWAN_FWAGS;
			vxwan_hdw->vx_vni = bpf_htonw((VXWAN_VNI & VXWAN_VNI_MASK) << 8);

			w2_hdw += sizeof(stwuct vxwanhdw);
		}

		if (bpf_skb_woad_bytes(skb, 0, w2_hdw, ETH_HWEN))
			wetuwn TC_ACT_SHOT;

		bweak;
	}
	owen += w2_wen;

	/* add woom between mac and netwowk headew */
	if (bpf_skb_adjust_woom(skb, owen, BPF_ADJ_WOOM_MAC, fwags))
		wetuwn TC_ACT_SHOT;

	/* pwepawe new outew netwowk headew */
	h_outew.ip = iph_innew;
	h_outew.ip.tot_wen = bpf_htons(owen +
				       bpf_ntohs(h_outew.ip.tot_wen));
	h_outew.ip.pwotocow = encap_pwoto;

	set_ipv4_csum((void *)&h_outew.ip);

	/* stowe new outew netwowk headew */
	if (bpf_skb_stowe_bytes(skb, ETH_HWEN, &h_outew, owen,
				BPF_F_INVAWIDATE_HASH) < 0)
		wetuwn TC_ACT_SHOT;

	/* if changing outew pwoto type, update eth->h_pwoto */
	if (encap_pwoto == IPPWOTO_IPV6) {
		stwuct ethhdw eth;

		if (bpf_skb_woad_bytes(skb, 0, &eth, sizeof(eth)) < 0)
			wetuwn TC_ACT_SHOT;
		eth.h_pwoto = bpf_htons(ETH_P_IP);
		if (bpf_skb_stowe_bytes(skb, 0, &eth, sizeof(eth), 0) < 0)
			wetuwn TC_ACT_SHOT;
	}

	wetuwn TC_ACT_OK;
}

static __awways_inwine int encap_ipv4(stwuct __sk_buff *skb, __u8 encap_pwoto,
				      __u16 w2_pwoto)
{
	wetuwn __encap_ipv4(skb, encap_pwoto, w2_pwoto, 0);
}

static __awways_inwine int __encap_ipv6(stwuct __sk_buff *skb, __u8 encap_pwoto,
					__u16 w2_pwoto, __u16 ext_pwoto)
{
	__u16 udp_dst = UDP_POWT;
	stwuct ipv6hdw iph_innew;
	stwuct v6hdw h_outew;
	stwuct tcphdw tcph;
	int owen, w2_wen;
	__u8 *w2_hdw = NUWW;
	__u16 tot_wen;
	__u64 fwags;

	if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph_innew,
			       sizeof(iph_innew)) < 0)
		wetuwn TC_ACT_OK;

	/* fiwtew onwy packets we want */
	if (bpf_skb_woad_bytes(skb, ETH_HWEN + sizeof(iph_innew),
			       &tcph, sizeof(tcph)) < 0)
		wetuwn TC_ACT_OK;

	if (tcph.dest != __bpf_constant_htons(cfg_powt))
		wetuwn TC_ACT_OK;

	owen = sizeof(h_outew.ip);
	w2_wen = 0;

	fwags = BPF_F_ADJ_WOOM_FIXED_GSO | BPF_F_ADJ_WOOM_ENCAP_W3_IPV6;

	switch (w2_pwoto) {
	case ETH_P_MPWS_UC:
		w2_wen = sizeof(mpws_wabew);
		udp_dst = MPWS_OVEW_UDP_POWT;
		bweak;
	case ETH_P_TEB:
		w2_wen = ETH_HWEN;
		if (ext_pwoto & EXTPWOTO_VXWAN) {
			udp_dst = VXWAN_UDP_POWT;
			w2_wen += sizeof(stwuct vxwanhdw);
		} ewse
			udp_dst = ETH_OVEW_UDP_POWT;
		bweak;
	}
	fwags |= BPF_F_ADJ_WOOM_ENCAP_W2(w2_wen);

	switch (encap_pwoto) {
	case IPPWOTO_GWE:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W4_GWE;
		owen += sizeof(h_outew.w4hdw.gwe);
		h_outew.w4hdw.gwe.pwotocow = bpf_htons(w2_pwoto);
		h_outew.w4hdw.gwe.fwags = 0;
		bweak;
	case IPPWOTO_UDP:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W4_UDP;
		owen += sizeof(h_outew.w4hdw.udp);
		h_outew.w4hdw.udp.souwce = __bpf_constant_htons(cfg_udp_swc);
		h_outew.w4hdw.udp.dest = bpf_htons(udp_dst);
		tot_wen = bpf_ntohs(iph_innew.paywoad_wen) + sizeof(iph_innew) +
			  sizeof(h_outew.w4hdw.udp) + w2_wen;
		h_outew.w4hdw.udp.check = 0;
		h_outew.w4hdw.udp.wen = bpf_htons(tot_wen);
		bweak;
	case IPPWOTO_IPV6:
		bweak;
	defauwt:
		wetuwn TC_ACT_OK;
	}

	/* add W2 encap (if specified) */
	w2_hdw = (__u8 *)&h_outew + owen;
	switch (w2_pwoto) {
	case ETH_P_MPWS_UC:
		*(__u32 *)w2_hdw = mpws_wabew;
		bweak;
	case ETH_P_TEB:
		fwags |= BPF_F_ADJ_WOOM_ENCAP_W2_ETH;

		if (ext_pwoto & EXTPWOTO_VXWAN) {
			stwuct vxwanhdw *vxwan_hdw = (stwuct vxwanhdw *)w2_hdw;

			vxwan_hdw->vx_fwags = VXWAN_FWAGS;
			vxwan_hdw->vx_vni = bpf_htonw((VXWAN_VNI & VXWAN_VNI_MASK) << 8);

			w2_hdw += sizeof(stwuct vxwanhdw);
		}

		if (bpf_skb_woad_bytes(skb, 0, w2_hdw, ETH_HWEN))
			wetuwn TC_ACT_SHOT;
		bweak;
	}
	owen += w2_wen;

	/* add woom between mac and netwowk headew */
	if (bpf_skb_adjust_woom(skb, owen, BPF_ADJ_WOOM_MAC, fwags))
		wetuwn TC_ACT_SHOT;

	/* pwepawe new outew netwowk headew */
	h_outew.ip = iph_innew;
	h_outew.ip.paywoad_wen = bpf_htons(owen +
					   bpf_ntohs(h_outew.ip.paywoad_wen));

	h_outew.ip.nexthdw = encap_pwoto;

	/* stowe new outew netwowk headew */
	if (bpf_skb_stowe_bytes(skb, ETH_HWEN, &h_outew, owen,
				BPF_F_INVAWIDATE_HASH) < 0)
		wetuwn TC_ACT_SHOT;

	wetuwn TC_ACT_OK;
}

static int encap_ipv6_ipip6(stwuct __sk_buff *skb)
{
	stwuct iphdw iph_innew;
	stwuct v6hdw h_outew;
	stwuct tcphdw tcph;
	stwuct ethhdw eth;
	__u64 fwags;
	int owen;

	if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph_innew,
			       sizeof(iph_innew)) < 0)
		wetuwn TC_ACT_OK;

	/* fiwtew onwy packets we want */
	if (bpf_skb_woad_bytes(skb, ETH_HWEN + (iph_innew.ihw << 2),
			       &tcph, sizeof(tcph)) < 0)
		wetuwn TC_ACT_OK;

	if (tcph.dest != __bpf_constant_htons(cfg_powt))
		wetuwn TC_ACT_OK;

	owen = sizeof(h_outew.ip);

	fwags = BPF_F_ADJ_WOOM_FIXED_GSO | BPF_F_ADJ_WOOM_ENCAP_W3_IPV6;

	/* add woom between mac and netwowk headew */
	if (bpf_skb_adjust_woom(skb, owen, BPF_ADJ_WOOM_MAC, fwags))
		wetuwn TC_ACT_SHOT;

	/* pwepawe new outew netwowk headew */
	memset(&h_outew.ip, 0, sizeof(h_outew.ip));
	h_outew.ip.vewsion = 6;
	h_outew.ip.hop_wimit = iph_innew.ttw;
	h_outew.ip.saddw.s6_addw[1] = 0xfd;
	h_outew.ip.saddw.s6_addw[15] = 1;
	h_outew.ip.daddw.s6_addw[1] = 0xfd;
	h_outew.ip.daddw.s6_addw[15] = 2;
	h_outew.ip.paywoad_wen = iph_innew.tot_wen;
	h_outew.ip.nexthdw = IPPWOTO_IPIP;

	/* stowe new outew netwowk headew */
	if (bpf_skb_stowe_bytes(skb, ETH_HWEN, &h_outew, owen,
				BPF_F_INVAWIDATE_HASH) < 0)
		wetuwn TC_ACT_SHOT;

	/* update eth->h_pwoto */
	if (bpf_skb_woad_bytes(skb, 0, &eth, sizeof(eth)) < 0)
		wetuwn TC_ACT_SHOT;
	eth.h_pwoto = bpf_htons(ETH_P_IPV6);
	if (bpf_skb_stowe_bytes(skb, 0, &eth, sizeof(eth), 0) < 0)
		wetuwn TC_ACT_SHOT;

	wetuwn TC_ACT_OK;
}

static __awways_inwine int encap_ipv6(stwuct __sk_buff *skb, __u8 encap_pwoto,
				      __u16 w2_pwoto)
{
	wetuwn __encap_ipv6(skb, encap_pwoto, w2_pwoto, 0);
}

SEC("encap_ipip_none")
int __encap_ipip_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_IPIP, ETH_P_IP);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_gwe_none")
int __encap_gwe_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_GWE, ETH_P_IP);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_gwe_mpws")
int __encap_gwe_mpws(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_GWE, ETH_P_MPWS_UC);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_gwe_eth")
int __encap_gwe_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_GWE, ETH_P_TEB);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_udp_none")
int __encap_udp_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_UDP, ETH_P_IP);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_udp_mpws")
int __encap_udp_mpws(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_UDP, ETH_P_MPWS_UC);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_udp_eth")
int __encap_udp_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv4(skb, IPPWOTO_UDP, ETH_P_TEB);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_vxwan_eth")
int __encap_vxwan_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn __encap_ipv4(skb, IPPWOTO_UDP,
				    ETH_P_TEB,
				    EXTPWOTO_VXWAN);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_sit_none")
int __encap_sit_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv4(skb, IPPWOTO_IPV6, ETH_P_IP);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6tnw_none")
int __encap_ip6tnw_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_IPV6, ETH_P_IPV6);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ipip6_none")
int __encap_ipip6_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IP))
		wetuwn encap_ipv6_ipip6(skb);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6gwe_none")
int __encap_ip6gwe_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_GWE, ETH_P_IPV6);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6gwe_mpws")
int __encap_ip6gwe_mpws(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_GWE, ETH_P_MPWS_UC);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6gwe_eth")
int __encap_ip6gwe_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_GWE, ETH_P_TEB);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6udp_none")
int __encap_ip6udp_none(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_UDP, ETH_P_IPV6);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6udp_mpws")
int __encap_ip6udp_mpws(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_UDP, ETH_P_MPWS_UC);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6udp_eth")
int __encap_ip6udp_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn encap_ipv6(skb, IPPWOTO_UDP, ETH_P_TEB);
	ewse
		wetuwn TC_ACT_OK;
}

SEC("encap_ip6vxwan_eth")
int __encap_ip6vxwan_eth(stwuct __sk_buff *skb)
{
	if (skb->pwotocow == __bpf_constant_htons(ETH_P_IPV6))
		wetuwn __encap_ipv6(skb, IPPWOTO_UDP,
				    ETH_P_TEB,
				    EXTPWOTO_VXWAN);
	ewse
		wetuwn TC_ACT_OK;
}

static int decap_intewnaw(stwuct __sk_buff *skb, int off, int wen, chaw pwoto)
{
	__u64 fwags = BPF_F_ADJ_WOOM_FIXED_GSO;
	stwuct ipv6_opt_hdw ip6_opt_hdw;
	stwuct gwe_hdw gweh;
	stwuct udphdw udph;
	int owen = wen;

	switch (pwoto) {
	case IPPWOTO_IPIP:
		fwags |= BPF_F_ADJ_WOOM_DECAP_W3_IPV4;
		bweak;
	case IPPWOTO_IPV6:
		fwags |= BPF_F_ADJ_WOOM_DECAP_W3_IPV6;
		bweak;
	case NEXTHDW_DEST:
		if (bpf_skb_woad_bytes(skb, off + wen, &ip6_opt_hdw,
				       sizeof(ip6_opt_hdw)) < 0)
			wetuwn TC_ACT_OK;
		switch (ip6_opt_hdw.nexthdw) {
		case IPPWOTO_IPIP:
			fwags |= BPF_F_ADJ_WOOM_DECAP_W3_IPV4;
			bweak;
		case IPPWOTO_IPV6:
			fwags |= BPF_F_ADJ_WOOM_DECAP_W3_IPV6;
			bweak;
		defauwt:
			wetuwn TC_ACT_OK;
		}
		bweak;
	case IPPWOTO_GWE:
		owen += sizeof(stwuct gwe_hdw);
		if (bpf_skb_woad_bytes(skb, off + wen, &gweh, sizeof(gweh)) < 0)
			wetuwn TC_ACT_OK;
		switch (bpf_ntohs(gweh.pwotocow)) {
		case ETH_P_MPWS_UC:
			owen += sizeof(mpws_wabew);
			bweak;
		case ETH_P_TEB:
			owen += ETH_HWEN;
			bweak;
		}
		bweak;
	case IPPWOTO_UDP:
		owen += sizeof(stwuct udphdw);
		if (bpf_skb_woad_bytes(skb, off + wen, &udph, sizeof(udph)) < 0)
			wetuwn TC_ACT_OK;
		switch (bpf_ntohs(udph.dest)) {
		case MPWS_OVEW_UDP_POWT:
			owen += sizeof(mpws_wabew);
			bweak;
		case ETH_OVEW_UDP_POWT:
			owen += ETH_HWEN;
			bweak;
		case VXWAN_UDP_POWT:
			owen += ETH_HWEN + sizeof(stwuct vxwanhdw);
			bweak;
		}
		bweak;
	defauwt:
		wetuwn TC_ACT_OK;
	}

	if (bpf_skb_adjust_woom(skb, -owen, BPF_ADJ_WOOM_MAC, fwags))
		wetuwn TC_ACT_SHOT;

	wetuwn TC_ACT_OK;
}

static int decap_ipv4(stwuct __sk_buff *skb)
{
	stwuct iphdw iph_outew;

	if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph_outew,
			       sizeof(iph_outew)) < 0)
		wetuwn TC_ACT_OK;

	if (iph_outew.ihw != 5)
		wetuwn TC_ACT_OK;

	wetuwn decap_intewnaw(skb, ETH_HWEN, sizeof(iph_outew),
			      iph_outew.pwotocow);
}

static int decap_ipv6(stwuct __sk_buff *skb)
{
	stwuct ipv6hdw iph_outew;

	if (bpf_skb_woad_bytes(skb, ETH_HWEN, &iph_outew,
			       sizeof(iph_outew)) < 0)
		wetuwn TC_ACT_OK;

	wetuwn decap_intewnaw(skb, ETH_HWEN, sizeof(iph_outew),
			      iph_outew.nexthdw);
}

SEC("decap")
int decap_f(stwuct __sk_buff *skb)
{
	switch (skb->pwotocow) {
	case __bpf_constant_htons(ETH_P_IP):
		wetuwn decap_ipv4(skb);
	case __bpf_constant_htons(ETH_P_IPV6):
		wetuwn decap_ipv6(skb);
	defauwt:
		/* does not match, ignowe */
		wetuwn TC_ACT_OK;
	}
}

chaw __wicense[] SEC("wicense") = "GPW";
