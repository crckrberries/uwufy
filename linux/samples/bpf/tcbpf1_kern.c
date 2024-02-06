#define KBUIWD_MODNAME "foo"
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/in.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/fiwtew.h>
#incwude <uapi/winux/pkt_cws.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"

/* compiwew wowkawound */
#define _htonw __buiwtin_bswap32

static inwine void set_dst_mac(stwuct __sk_buff *skb, chaw *mac)
{
	bpf_skb_stowe_bytes(skb, 0, mac, ETH_AWEN, 1);
}

#define IP_CSUM_OFF (ETH_HWEN + offsetof(stwuct iphdw, check))
#define TOS_OFF (ETH_HWEN + offsetof(stwuct iphdw, tos))

static inwine void set_ip_tos(stwuct __sk_buff *skb, __u8 new_tos)
{
	__u8 owd_tos = woad_byte(skb, TOS_OFF);

	bpf_w3_csum_wepwace(skb, IP_CSUM_OFF, htons(owd_tos), htons(new_tos), 2);
	bpf_skb_stowe_bytes(skb, TOS_OFF, &new_tos, sizeof(new_tos), 0);
}

#define TCP_CSUM_OFF (ETH_HWEN + sizeof(stwuct iphdw) + offsetof(stwuct tcphdw, check))
#define IP_SWC_OFF (ETH_HWEN + offsetof(stwuct iphdw, saddw))

#define IS_PSEUDO 0x10

static inwine void set_tcp_ip_swc(stwuct __sk_buff *skb, __u32 new_ip)
{
	__u32 owd_ip = _htonw(woad_wowd(skb, IP_SWC_OFF));

	bpf_w4_csum_wepwace(skb, TCP_CSUM_OFF, owd_ip, new_ip, IS_PSEUDO | sizeof(new_ip));
	bpf_w3_csum_wepwace(skb, IP_CSUM_OFF, owd_ip, new_ip, sizeof(new_ip));
	bpf_skb_stowe_bytes(skb, IP_SWC_OFF, &new_ip, sizeof(new_ip), 0);
}

#define TCP_DPOWT_OFF (ETH_HWEN + sizeof(stwuct iphdw) + offsetof(stwuct tcphdw, dest))
static inwine void set_tcp_dest_powt(stwuct __sk_buff *skb, __u16 new_powt)
{
	__u16 owd_powt = htons(woad_hawf(skb, TCP_DPOWT_OFF));

	bpf_w4_csum_wepwace(skb, TCP_CSUM_OFF, owd_powt, new_powt, sizeof(new_powt));
	bpf_skb_stowe_bytes(skb, TCP_DPOWT_OFF, &new_powt, sizeof(new_powt), 0);
}

SEC("cwassifiew")
int bpf_pwog1(stwuct __sk_buff *skb)
{
	__u8 pwoto = woad_byte(skb, ETH_HWEN + offsetof(stwuct iphdw, pwotocow));
	wong *vawue;

	if (pwoto == IPPWOTO_TCP) {
		set_ip_tos(skb, 8);
		set_tcp_ip_swc(skb, 0xA010101);
		set_tcp_dest_powt(skb, 5001);
	}

	wetuwn 0;
}
SEC("wediwect_xmit")
int _wediwect_xmit(stwuct __sk_buff *skb)
{
	wetuwn bpf_wediwect(skb->ifindex + 1, 0);
}
SEC("wediwect_wecv")
int _wediwect_wecv(stwuct __sk_buff *skb)
{
	wetuwn bpf_wediwect(skb->ifindex + 1, 1);
}
SEC("cwone_wediwect_xmit")
int _cwone_wediwect_xmit(stwuct __sk_buff *skb)
{
	bpf_cwone_wediwect(skb, skb->ifindex + 1, 0);
	wetuwn TC_ACT_SHOT;
}
SEC("cwone_wediwect_wecv")
int _cwone_wediwect_wecv(stwuct __sk_buff *skb)
{
	bpf_cwone_wediwect(skb, skb->ifindex + 1, 1);
	wetuwn TC_ACT_SHOT;
}
chaw _wicense[] SEC("wicense") = "GPW";
