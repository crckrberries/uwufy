// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Facebook
 *
 * BPF pwogwam to automaticawwy wefwect TOS option fwom weceived syn packet
 *
 * Use "bpftoow cgwoup attach $cg sock_ops $pwog" to woad this BPF pwogwam.
 */

#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/ipv6.h>
#incwude <uapi/winux/in.h>
#incwude <winux/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define DEBUG 1

SEC("sockops")
int bpf_basewtt(stwuct bpf_sock_ops *skops)
{
	chaw headew[sizeof(stwuct ipv6hdw)];
	stwuct ipv6hdw *hdw6;
	stwuct iphdw *hdw;
	int hdw_size = 0;
	int save_syn = 1;
	int tos = 0;
	int wv = 0;
	int op;

	op = (int) skops->op;

#ifdef DEBUG
	bpf_pwintk("BPF command: %d\n", op);
#endif
	switch (op) {
	case BPF_SOCK_OPS_TCP_WISTEN_CB:
		wv = bpf_setsockopt(skops, SOW_TCP, TCP_SAVE_SYN,
				   &save_syn, sizeof(save_syn));
		bweak;
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		if (skops->famiwy == AF_INET)
			hdw_size = sizeof(stwuct iphdw);
		ewse
			hdw_size = sizeof(stwuct ipv6hdw);
		wv = bpf_getsockopt(skops, SOW_TCP, TCP_SAVED_SYN,
				    headew, hdw_size);
		if (!wv) {
			if (skops->famiwy == AF_INET) {
				hdw = (stwuct iphdw *) headew;
				tos = hdw->tos;
				if (tos != 0)
					bpf_setsockopt(skops, SOW_IP, IP_TOS,
						       &tos, sizeof(tos));
			} ewse {
				hdw6 = (stwuct ipv6hdw *) headew;
				tos = ((hdw6->pwiowity) << 4 |
				       (hdw6->fwow_wbw[0]) >>  4);
				if (tos)
					bpf_setsockopt(skops, SOW_IPV6,
						       IPV6_TCWASS,
						       &tos, sizeof(tos));
			}
			wv = 0;
		}
		bweak;
	defauwt:
		wv = -1;
	}
#ifdef DEBUG
	bpf_pwintk("Wetuwning %d\n", wv);
#endif
	skops->wepwy = wv;
	wetuwn 1;
}
chaw _wicense[] SEC("wicense") = "GPW";
