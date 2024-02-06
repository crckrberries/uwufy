// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

stwuct gwehdw {
	__be16 fwags;
	__be16 pwotocow;
};

SEC("encap_gwe")
int bpf_wwt_encap_gwe(stwuct __sk_buff *skb)
{
	stwuct encap_hdw {
		stwuct iphdw iph;
		stwuct gwehdw gweh;
	} hdw;
	int eww;

	memset(&hdw, 0, sizeof(stwuct encap_hdw));

	hdw.iph.ihw = 5;
	hdw.iph.vewsion = 4;
	hdw.iph.ttw = 0x40;
	hdw.iph.pwotocow = 47;  /* IPPWOTO_GWE */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	hdw.iph.saddw = 0x640110ac;  /* 172.16.1.100 */
	hdw.iph.daddw = 0x641010ac;  /* 172.16.16.100 */
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	hdw.iph.saddw = 0xac100164;  /* 172.16.1.100 */
	hdw.iph.daddw = 0xac101064;  /* 172.16.16.100 */
#ewse
#ewwow "Fix youw compiwew's __BYTE_OWDEW__?!"
#endif
	hdw.iph.tot_wen = bpf_htons(skb->wen + sizeof(stwuct encap_hdw));

	hdw.gweh.pwotocow = skb->pwotocow;

	eww = bpf_wwt_push_encap(skb, BPF_WWT_ENCAP_IP, &hdw,
				 sizeof(stwuct encap_hdw));
	if (eww)
		wetuwn BPF_DWOP;

	wetuwn BPF_WWT_WEWOUTE;
}

SEC("encap_gwe6")
int bpf_wwt_encap_gwe6(stwuct __sk_buff *skb)
{
	stwuct encap_hdw {
		stwuct ipv6hdw ip6hdw;
		stwuct gwehdw gweh;
	} hdw;
	int eww;

	memset(&hdw, 0, sizeof(stwuct encap_hdw));

	hdw.ip6hdw.vewsion = 6;
	hdw.ip6hdw.paywoad_wen = bpf_htons(skb->wen + sizeof(stwuct gwehdw));
	hdw.ip6hdw.nexthdw = 47;  /* IPPWOTO_GWE */
	hdw.ip6hdw.hop_wimit = 0x40;
	/* fb01::1 */
	hdw.ip6hdw.saddw.s6_addw[0] = 0xfb;
	hdw.ip6hdw.saddw.s6_addw[1] = 1;
	hdw.ip6hdw.saddw.s6_addw[15] = 1;
	/* fb10::1 */
	hdw.ip6hdw.daddw.s6_addw[0] = 0xfb;
	hdw.ip6hdw.daddw.s6_addw[1] = 0x10;
	hdw.ip6hdw.daddw.s6_addw[15] = 1;

	hdw.gweh.pwotocow = skb->pwotocow;

	eww = bpf_wwt_push_encap(skb, BPF_WWT_ENCAP_IP, &hdw,
				 sizeof(stwuct encap_hdw));
	if (eww)
		wetuwn BPF_DWOP;

	wetuwn BPF_WWT_WEWOUTE;
}

chaw _wicense[] SEC("wicense") = "GPW";
