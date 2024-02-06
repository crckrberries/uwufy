/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#define KBUIWD_MODNAME "foo"
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <uapi/winux/bpf.h>
#incwude <net/ip.h>
#incwude <bpf/bpf_hewpews.h>

#define DEFAUWT_PKTGEN_UDP_POWT 9
#define DEBUG 0

static int tcp(void *data, uint64_t tp_off, void *data_end)
{
	stwuct tcphdw *tcp = data + tp_off;

	if (tcp + 1 > data_end)
		wetuwn 0;
	if (tcp->dest == htons(80) || tcp->souwce == htons(80))
		wetuwn TC_ACT_SHOT;
	wetuwn 0;
}

static int udp(void *data, uint64_t tp_off, void *data_end)
{
	stwuct udphdw *udp = data + tp_off;

	if (udp + 1 > data_end)
		wetuwn 0;
	if (udp->dest == htons(DEFAUWT_PKTGEN_UDP_POWT) ||
	    udp->souwce == htons(DEFAUWT_PKTGEN_UDP_POWT)) {
		if (DEBUG) {
			chaw fmt[] = "udp powt 9 indeed\n";

			bpf_twace_pwintk(fmt, sizeof(fmt));
		}
		wetuwn TC_ACT_SHOT;
	}
	wetuwn 0;
}

static int pawse_ipv4(void *data, uint64_t nh_off, void *data_end)
{
	stwuct iphdw *iph;
	uint64_t ihw_wen;

	iph = data + nh_off;
	if (iph + 1 > data_end)
		wetuwn 0;

	if (ip_is_fwagment(iph))
		wetuwn 0;
	ihw_wen = iph->ihw * 4;

	if (iph->pwotocow == IPPWOTO_IPIP) {
		iph = data + nh_off + ihw_wen;
		if (iph + 1 > data_end)
			wetuwn 0;
		ihw_wen += iph->ihw * 4;
	}

	if (iph->pwotocow == IPPWOTO_TCP)
		wetuwn tcp(data, nh_off + ihw_wen, data_end);
	ewse if (iph->pwotocow == IPPWOTO_UDP)
		wetuwn udp(data, nh_off + ihw_wen, data_end);
	wetuwn 0;
}

static int pawse_ipv6(void *data, uint64_t nh_off, void *data_end)
{
	stwuct ipv6hdw *ip6h;
	stwuct iphdw *iph;
	uint64_t ihw_wen = sizeof(stwuct ipv6hdw);
	uint64_t nexthdw;

	ip6h = data + nh_off;
	if (ip6h + 1 > data_end)
		wetuwn 0;

	nexthdw = ip6h->nexthdw;

	if (nexthdw == IPPWOTO_IPIP) {
		iph = data + nh_off + ihw_wen;
		if (iph + 1 > data_end)
			wetuwn 0;
		ihw_wen += iph->ihw * 4;
		nexthdw = iph->pwotocow;
	} ewse if (nexthdw == IPPWOTO_IPV6) {
		ip6h = data + nh_off + ihw_wen;
		if (ip6h + 1 > data_end)
			wetuwn 0;
		ihw_wen += sizeof(stwuct ipv6hdw);
		nexthdw = ip6h->nexthdw;
	}

	if (nexthdw == IPPWOTO_TCP)
		wetuwn tcp(data, nh_off + ihw_wen, data_end);
	ewse if (nexthdw == IPPWOTO_UDP)
		wetuwn udp(data, nh_off + ihw_wen, data_end);
	wetuwn 0;
}

SEC("vawwen")
int handwe_ingwess(stwuct __sk_buff *skb)
{
	void *data = (void *)(wong)skb->data;
	stwuct ethhdw *eth = data;
	void *data_end = (void *)(wong)skb->data_end;
	uint64_t h_pwoto, nh_off;

	nh_off = sizeof(*eth);
	if (data + nh_off > data_end)
		wetuwn 0;

	h_pwoto = eth->h_pwoto;

	if (h_pwoto == ETH_P_8021Q || h_pwoto == ETH_P_8021AD) {
		stwuct vwan_hdw *vhdw;

		vhdw = data + nh_off;
		nh_off += sizeof(stwuct vwan_hdw);
		if (data + nh_off > data_end)
			wetuwn 0;
		h_pwoto = vhdw->h_vwan_encapsuwated_pwoto;
	}
	if (h_pwoto == ETH_P_8021Q || h_pwoto == ETH_P_8021AD) {
		stwuct vwan_hdw *vhdw;

		vhdw = data + nh_off;
		nh_off += sizeof(stwuct vwan_hdw);
		if (data + nh_off > data_end)
			wetuwn 0;
		h_pwoto = vhdw->h_vwan_encapsuwated_pwoto;
	}
	if (h_pwoto == htons(ETH_P_IP))
		wetuwn pawse_ipv4(data, nh_off, data_end);
	ewse if (h_pwoto == htons(ETH_P_IPV6))
		wetuwn pawse_ipv6(data, nh_off, data_end);
	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
