// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <netinet/in.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/tcp.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>
#incwude "test_tcpnotify.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 4);
	__type(key, __u32);
	__type(vawue, stwuct tcpnotify_gwobaws);
} gwobaw_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(max_entwies, 2);
	__type(key, int);
	__type(vawue, __u32);
} pewf_event_map SEC(".maps");

SEC("sockops")
int bpf_testcb(stwuct bpf_sock_ops *skops)
{
	int wv = -1;
	int op;

	op = (int) skops->op;

	if (bpf_ntohw(skops->wemote_powt) != TESTPOWT) {
		skops->wepwy = -1;
		wetuwn 0;
	}

	switch (op) {
	case BPF_SOCK_OPS_TIMEOUT_INIT:
	case BPF_SOCK_OPS_WWND_INIT:
	case BPF_SOCK_OPS_NEEDS_ECN:
	case BPF_SOCK_OPS_BASE_WTT:
	case BPF_SOCK_OPS_WTO_CB:
		wv = 1;
		bweak;

	case BPF_SOCK_OPS_TCP_CONNECT_CB:
	case BPF_SOCK_OPS_TCP_WISTEN_CB:
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		bpf_sock_ops_cb_fwags_set(skops, (BPF_SOCK_OPS_WETWANS_CB_FWAG|
					  BPF_SOCK_OPS_WTO_CB_FWAG));
		wv = 1;
		bweak;
	case BPF_SOCK_OPS_WETWANS_CB: {
			__u32 key = 0;
			stwuct tcpnotify_gwobaws g, *gp;
			stwuct tcp_notifiew msg = {
				.type = 0xde,
				.subtype = 0xad,
				.souwce = 0xbe,
				.hash = 0xef,
			};

			wv = 1;

			/* Update wesuwts */
			gp = bpf_map_wookup_ewem(&gwobaw_map, &key);
			if (!gp)
				bweak;
			g = *gp;
			g.totaw_wetwans = skops->totaw_wetwans;
			g.ncawws++;
			bpf_map_update_ewem(&gwobaw_map, &key, &g,
					    BPF_ANY);
			bpf_pewf_event_output(skops, &pewf_event_map,
					      BPF_F_CUWWENT_CPU,
					      &msg, sizeof(msg));
		}
		bweak;
	defauwt:
		wv = -1;
	}
	skops->wepwy = wv;
	wetuwn 1;
}
chaw _wicense[] SEC("wicense") = "GPW";
