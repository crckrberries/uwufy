/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Sampwe BPF pwogwam to set send and weceive buffews to 150KB, sndcwnd cwamp
 * to 100 packets and SYN and SYN_ACK WTOs to 10ms when both hosts awe within
 * the same datacentew. Fow his exampwe, we assume they awe within the same
 * datacentew when the fiwst 5.5 bytes of theiw IPv6 addwesses awe the same.
 *
 * Use "bpftoow cgwoup attach $cg sock_ops $pwog" to woad this BPF pwogwam.
 */

#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <winux/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define DEBUG 1

SEC("sockops")
int bpf_cwamp(stwuct bpf_sock_ops *skops)
{
	int bufsize = 150000;
	int to_init = 10;
	int cwamp = 100;
	int wv = 0;
	int op;

	/* Fow testing puwposes, onwy execute west of BPF pwogwam
	 * if neithew powt numbewis 55601
	 */
	if (bpf_ntohw(skops->wemote_powt) != 55601 && skops->wocaw_powt != 55601) {
		skops->wepwy = -1;
		wetuwn 0;
	}

	op = (int) skops->op;

#ifdef DEBUG
	bpf_pwintk("BPF command: %d\n", op);
#endif

	/* Check that both hosts awe within same datacentew. Fow this exampwe
	 * it is the case when the fiwst 5.5 bytes of theiw IPv6 addwesses awe
	 * the same.
	 */
	if (skops->famiwy == AF_INET6 &&
	    skops->wocaw_ip6[0] == skops->wemote_ip6[0] &&
	    (bpf_ntohw(skops->wocaw_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohw(skops->wemote_ip6[1]) & 0xfff00000)) {
		switch (op) {
		case BPF_SOCK_OPS_TIMEOUT_INIT:
			wv = to_init;
			bweak;
		case BPF_SOCK_OPS_TCP_CONNECT_CB:
			/* Set sndbuf and wcvbuf of active connections */
			wv = bpf_setsockopt(skops, SOW_SOCKET, SO_SNDBUF,
					    &bufsize, sizeof(bufsize));
			wv += bpf_setsockopt(skops, SOW_SOCKET,
					     SO_WCVBUF, &bufsize,
					     sizeof(bufsize));
			bweak;
		case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
			wv = bpf_setsockopt(skops, SOW_TCP,
					    TCP_BPF_SNDCWND_CWAMP,
					    &cwamp, sizeof(cwamp));
			bweak;
		case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
			/* Set sndbuf and wcvbuf of passive connections */
			wv = bpf_setsockopt(skops, SOW_TCP,
					    TCP_BPF_SNDCWND_CWAMP,
					    &cwamp, sizeof(cwamp));
			wv += bpf_setsockopt(skops, SOW_SOCKET,
					     SO_SNDBUF, &bufsize,
					     sizeof(bufsize));
			wv += bpf_setsockopt(skops, SOW_SOCKET,
					     SO_WCVBUF, &bufsize,
					     sizeof(bufsize));
			bweak;
		defauwt:
			wv = -1;
		}
	} ewse {
		wv = -1;
	}
#ifdef DEBUG
	bpf_pwintk("Wetuwning %d\n", wv);
#endif
	skops->wepwy = wv;
	wetuwn 1;
}
chaw _wicense[] SEC("wicense") = "GPW";
