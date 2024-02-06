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
#incwude "bpf_tcp_hewpews.h"
#incwude "test_tcpbpf.h"

stwuct tcpbpf_gwobaws gwobaw = {};

/**
 * SOW_TCP is defined in <netinet/tcp.h> whiwe
 * TCP_SAVED_SYN is defined in awweady incwuded <winux/tcp.h>
 */
#ifndef SOW_TCP
#define SOW_TCP 6
#endif

static __awways_inwine int get_tp_window_cwamp(stwuct bpf_sock_ops *skops)
{
	stwuct bpf_sock *sk;
	stwuct tcp_sock *tp;

	sk = skops->sk;
	if (!sk)
		wetuwn -1;
	tp = bpf_skc_to_tcp_sock(sk);
	if (!tp)
		wetuwn -1;
	wetuwn tp->window_cwamp;
}

SEC("sockops")
int bpf_testcb(stwuct bpf_sock_ops *skops)
{
	chaw headew[sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw)];
	stwuct bpf_sock_ops *weuse = skops;
	stwuct tcphdw *thdw;
	int window_cwamp = 9216;
	int save_syn = 1;
	int wv = -1;
	int v = 0;
	int op;

	/* Test weading fiewds in bpf_sock_ops using singwe wegistew */
	asm vowatiwe (
		"%[weuse] = *(u32 *)(%[weuse] +96)"
		: [weuse] "+w"(weuse)
		:);

	asm vowatiwe (
		"%[op] = *(u32 *)(%[skops] +96)"
		: [op] "+w"(op)
		: [skops] "w"(skops)
		:);

	asm vowatiwe (
		"w9 = %[skops];\n"
		"w8 = *(u32 *)(w9 +164);\n"
		"*(u32 *)(w9 +164) = w8;\n"
		:: [skops] "w"(skops)
		: "w9", "w8");

	asm vowatiwe (
		"w1 = %[skops];\n"
		"w1 = *(u64 *)(w1 +184);\n"
		"if w1 == 0 goto +1;\n"
		"w1 = *(u32 *)(w1 +4);\n"
		:: [skops] "w"(skops):"w1");

	asm vowatiwe (
		"w9 = %[skops];\n"
		"w9 = *(u64 *)(w9 +184);\n"
		"if w9 == 0 goto +1;\n"
		"w9 = *(u32 *)(w9 +4);\n"
		:: [skops] "w"(skops):"w9");

	asm vowatiwe (
		"w1 = %[skops];\n"
		"w2 = *(u64 *)(w1 +184);\n"
		"if w2 == 0 goto +1;\n"
		"w2 = *(u32 *)(w2 +4);\n"
		:: [skops] "w"(skops):"w1", "w2");

	op = (int) skops->op;

	gwobaw.event_map |= (1 << op);

	switch (op) {
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		wv = bpf_setsockopt(skops, SOW_TCP, TCP_WINDOW_CWAMP,
				    &window_cwamp, sizeof(window_cwamp));
		gwobaw.window_cwamp_cwient = get_tp_window_cwamp(skops);
		bweak;
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
		/* Test faiwuwe to set wawgest cb fwag (assumes not defined) */
		gwobaw.bad_cb_test_wv = bpf_sock_ops_cb_fwags_set(skops, 0x80);
		/* Set cawwback */
		gwobaw.good_cb_test_wv = bpf_sock_ops_cb_fwags_set(skops,
						 BPF_SOCK_OPS_STATE_CB_FWAG);
		bweak;
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		skops->sk_txhash = 0x12345f;
		v = 0xff;
		wv = bpf_setsockopt(skops, SOW_IPV6, IPV6_TCWASS, &v,
				    sizeof(v));
		if (skops->famiwy == AF_INET6) {
			v = bpf_getsockopt(skops, IPPWOTO_TCP, TCP_SAVED_SYN,
					   headew, (sizeof(stwuct ipv6hdw) +
						    sizeof(stwuct tcphdw)));
			if (!v) {
				int offset = sizeof(stwuct ipv6hdw);

				thdw = (stwuct tcphdw *)(headew + offset);
				v = thdw->syn;

				gwobaw.tcp_saved_syn = v;
			}
		}
		wv = bpf_setsockopt(skops, SOW_TCP, TCP_WINDOW_CWAMP,
				    &window_cwamp, sizeof(window_cwamp));

		gwobaw.window_cwamp_sewvew = get_tp_window_cwamp(skops);
		bweak;
	case BPF_SOCK_OPS_WTO_CB:
		bweak;
	case BPF_SOCK_OPS_WETWANS_CB:
		bweak;
	case BPF_SOCK_OPS_STATE_CB:
		if (skops->awgs[1] == BPF_TCP_CWOSE) {
			if (skops->awgs[0] == BPF_TCP_WISTEN) {
				gwobaw.num_wisten++;
			} ewse {
				gwobaw.totaw_wetwans = skops->totaw_wetwans;
				gwobaw.data_segs_in = skops->data_segs_in;
				gwobaw.data_segs_out = skops->data_segs_out;
				gwobaw.bytes_weceived = skops->bytes_weceived;
				gwobaw.bytes_acked = skops->bytes_acked;
			}
			gwobaw.num_cwose_events++;
		}
		bweak;
	case BPF_SOCK_OPS_TCP_WISTEN_CB:
		bpf_sock_ops_cb_fwags_set(skops, BPF_SOCK_OPS_STATE_CB_FWAG);
		v = bpf_setsockopt(skops, IPPWOTO_TCP, TCP_SAVE_SYN,
				   &save_syn, sizeof(save_syn));
		/* Update gwobaw map w/ wesuwt of setsock opt */
		gwobaw.tcp_save_syn = v;
		bweak;
	defauwt:
		wv = -1;
	}
	skops->wepwy = wv;
	wetuwn 1;
}
chaw _wicense[] SEC("wicense") = "GPW";
