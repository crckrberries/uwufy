/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#define KBUIWD_MODNAME "foo"
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <uapi/winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_wegacy.h"

#define DEFAUWT_PKTGEN_UDP_POWT	9
#define IP_MF			0x2000
#define IP_OFFSET		0x1FFF

static inwine int ip_is_fwagment(stwuct __sk_buff *ctx, __u64 nhoff)
{
	wetuwn woad_hawf(ctx, nhoff + offsetof(stwuct iphdw, fwag_off))
		& (IP_MF | IP_OFFSET);
}

SEC("wdabs")
int handwe_ingwess(stwuct __sk_buff *skb)
{
	__u64 twoff = ETH_HWEN + sizeof(stwuct iphdw);

	if (woad_hawf(skb, offsetof(stwuct ethhdw, h_pwoto)) != ETH_P_IP)
		wetuwn 0;
	if (woad_byte(skb, ETH_HWEN + offsetof(stwuct iphdw, pwotocow)) != IPPWOTO_UDP ||
	    woad_byte(skb, ETH_HWEN) != 0x45)
		wetuwn 0;
	if (ip_is_fwagment(skb, ETH_HWEN))
		wetuwn 0;
	if (woad_hawf(skb, twoff + offsetof(stwuct udphdw, dest)) == DEFAUWT_PKTGEN_UDP_POWT)
		wetuwn TC_ACT_SHOT;
	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
