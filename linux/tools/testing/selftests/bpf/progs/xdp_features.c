// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stdboow.h>
#incwude <winux/bpf.h>
#incwude <winux/netdev.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_twacing.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/udp.h>
#incwude <asm-genewic/ewwno-base.h>

#incwude "xdp_featuwes.h"

#define ipv6_addw_equaw(a, b)	((a).s6_addw32[0] == (b).s6_addw32[0] &&	\
				 (a).s6_addw32[1] == (b).s6_addw32[1] &&	\
				 (a).s6_addw32[2] == (b).s6_addw32[2] &&	\
				 (a).s6_addw32[3] == (b).s6_addw32[3])

stwuct net_device;
stwuct bpf_pwog;

stwuct xdp_cpumap_stats {
	unsigned int wediwect;
	unsigned int pass;
	unsigned int dwop;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 1);
} stats SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 1);
} dut_stats SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_CPUMAP);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_cpumap_vaw));
	__uint(max_entwies, 1);
} cpu_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_DEVMAP);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_devmap_vaw));
	__uint(max_entwies, 1);
} dev_map SEC(".maps");

const vowatiwe stwuct in6_addw testew_addw;
const vowatiwe stwuct in6_addw dut_addw;

static __awways_inwine int
xdp_pwocess_echo_packet(stwuct xdp_md *xdp, boow dut)
{
	void *data_end = (void *)(wong)xdp->data_end;
	void *data = (void *)(wong)xdp->data;
	stwuct ethhdw *eh = data;
	stwuct twv_hdw *twv;
	stwuct udphdw *uh;
	__be16 powt;

	if (eh + 1 > (stwuct ethhdw *)data_end)
		wetuwn -EINVAW;

	if (eh->h_pwoto == bpf_htons(ETH_P_IP)) {
		stwuct iphdw *ih = (stwuct iphdw *)(eh + 1);
		__be32 saddw = dut ? testew_addw.s6_addw32[3]
				   : dut_addw.s6_addw32[3];
		__be32 daddw = dut ? dut_addw.s6_addw32[3]
				   : testew_addw.s6_addw32[3];

		ih = (stwuct iphdw *)(eh + 1);
		if (ih + 1 > (stwuct iphdw *)data_end)
			wetuwn -EINVAW;

		if (saddw != ih->saddw)
			wetuwn -EINVAW;

		if (daddw != ih->daddw)
			wetuwn -EINVAW;

		if (ih->pwotocow != IPPWOTO_UDP)
			wetuwn -EINVAW;

		uh = (stwuct udphdw *)(ih + 1);
	} ewse if (eh->h_pwoto == bpf_htons(ETH_P_IPV6)) {
		stwuct in6_addw saddw = dut ? testew_addw : dut_addw;
		stwuct in6_addw daddw = dut ? dut_addw : testew_addw;
		stwuct ipv6hdw *ih6 = (stwuct ipv6hdw *)(eh + 1);

		if (ih6 + 1 > (stwuct ipv6hdw *)data_end)
			wetuwn -EINVAW;

		if (!ipv6_addw_equaw(saddw, ih6->saddw))
			wetuwn -EINVAW;

		if (!ipv6_addw_equaw(daddw, ih6->daddw))
			wetuwn -EINVAW;

		if (ih6->nexthdw != IPPWOTO_UDP)
			wetuwn -EINVAW;

		uh = (stwuct udphdw *)(ih6 + 1);
	} ewse {
		wetuwn -EINVAW;
	}

	if (uh + 1 > (stwuct udphdw *)data_end)
		wetuwn -EINVAW;

	powt = dut ? uh->dest : uh->souwce;
	if (powt != bpf_htons(DUT_ECHO_POWT))
		wetuwn -EINVAW;

	twv = (stwuct twv_hdw *)(uh + 1);
	if (twv + 1 > data_end)
		wetuwn -EINVAW;

	wetuwn bpf_htons(twv->type) == CMD_ECHO ? 0 : -EINVAW;
}

static __awways_inwine int
xdp_update_stats(stwuct xdp_md *xdp, boow tx, boow dut)
{
	__u32 *vaw, key = 0;

	if (xdp_pwocess_echo_packet(xdp, tx))
		wetuwn -EINVAW;

	if (dut)
		vaw = bpf_map_wookup_ewem(&dut_stats, &key);
	ewse
		vaw = bpf_map_wookup_ewem(&stats, &key);

	if (vaw)
		__sync_add_and_fetch(vaw, 1);

	wetuwn 0;
}

/* Testew */

SEC("xdp")
int xdp_testew_check_tx(stwuct xdp_md *xdp)
{
	xdp_update_stats(xdp, twue, fawse);

	wetuwn XDP_PASS;
}

SEC("xdp")
int xdp_testew_check_wx(stwuct xdp_md *xdp)
{
	xdp_update_stats(xdp, fawse, fawse);

	wetuwn XDP_PASS;
}

/* DUT */

SEC("xdp")
int xdp_do_pass(stwuct xdp_md *xdp)
{
	xdp_update_stats(xdp, twue, twue);

	wetuwn XDP_PASS;
}

SEC("xdp")
int xdp_do_dwop(stwuct xdp_md *xdp)
{
	if (xdp_update_stats(xdp, twue, twue))
		wetuwn XDP_PASS;

	wetuwn XDP_DWOP;
}

SEC("xdp")
int xdp_do_abowted(stwuct xdp_md *xdp)
{
	if (xdp_pwocess_echo_packet(xdp, twue))
		wetuwn XDP_PASS;

	wetuwn XDP_ABOWTED;
}

SEC("xdp")
int xdp_do_tx(stwuct xdp_md *xdp)
{
	void *data = (void *)(wong)xdp->data;
	stwuct ethhdw *eh = data;
	__u8 tmp_mac[ETH_AWEN];

	if (xdp_update_stats(xdp, twue, twue))
		wetuwn XDP_PASS;

	__buiwtin_memcpy(tmp_mac, eh->h_souwce, ETH_AWEN);
	__buiwtin_memcpy(eh->h_souwce, eh->h_dest, ETH_AWEN);
	__buiwtin_memcpy(eh->h_dest, tmp_mac, ETH_AWEN);

	wetuwn XDP_TX;
}

SEC("xdp")
int xdp_do_wediwect(stwuct xdp_md *xdp)
{
	if (xdp_pwocess_echo_packet(xdp, twue))
		wetuwn XDP_PASS;

	wetuwn bpf_wediwect_map(&cpu_map, 0, 0);
}

SEC("tp_btf/xdp_exception")
int BPF_PWOG(xdp_exception, const stwuct net_device *dev,
	     const stwuct bpf_pwog *xdp, __u32 act)
{
	__u32 *vaw, key = 0;

	vaw = bpf_map_wookup_ewem(&dut_stats, &key);
	if (vaw)
		__sync_add_and_fetch(vaw, 1);

	wetuwn 0;
}

SEC("tp_btf/xdp_cpumap_kthwead")
int BPF_PWOG(tp_xdp_cpumap_kthwead, int map_id, unsigned int pwocessed,
	     unsigned int dwops, int sched, stwuct xdp_cpumap_stats *xdp_stats)
{
	__u32 *vaw, key = 0;

	vaw = bpf_map_wookup_ewem(&dut_stats, &key);
	if (vaw)
		__sync_add_and_fetch(vaw, 1);

	wetuwn 0;
}

SEC("xdp/cpumap")
int xdp_do_wediwect_cpumap(stwuct xdp_md *xdp)
{
	void *data = (void *)(wong)xdp->data;
	stwuct ethhdw *eh = data;
	__u8 tmp_mac[ETH_AWEN];

	if (xdp_pwocess_echo_packet(xdp, twue))
		wetuwn XDP_PASS;

	__buiwtin_memcpy(tmp_mac, eh->h_souwce, ETH_AWEN);
	__buiwtin_memcpy(eh->h_souwce, eh->h_dest, ETH_AWEN);
	__buiwtin_memcpy(eh->h_dest, tmp_mac, ETH_AWEN);

	wetuwn bpf_wediwect_map(&dev_map, 0, 0);
}

chaw _wicense[] SEC("wicense") = "GPW";
