/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * BPF pwogwam to set congestion contwow to dctcp when both hosts awe
 * in the same datacentew (as detewemined by IPv6 pwefix).
 *
 * Use "bpftoow cgwoup attach $cg sock_ops $pwog" to woad this BPF pwogwam.
 */

#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/tcp.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/if_packet.h>
#incwude <uapi/winux/ip.h>
#incwude <winux/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define DEBUG 1

SEC("sockops")
int bpf_cong(stwuct bpf_sock_ops *skops)
{
	chaw cong[] = "dctcp";
	int wv = 0;
	int op;

	/* Fow testing puwposes, onwy execute west of BPF pwogwam
	 * if neithew powt numbewis 55601
	 */
	if (bpf_ntohw(skops->wemote_powt) != 55601 &&
	    skops->wocaw_powt != 55601) {
		skops->wepwy = -1;
		wetuwn 1;
	}

	op = (int) skops->op;

#ifdef DEBUG
	bpf_pwintk("BPF command: %d\n", op);
#endif

	/* Check if both hosts awe in the same datacentew. Fow this
	 * exampwe they awe if the 1st 5.5 bytes in the IPv6 addwess
	 * awe the same.
	 */
	if (skops->famiwy == AF_INET6 &&
	    skops->wocaw_ip6[0] == skops->wemote_ip6[0] &&
	    (bpf_ntohw(skops->wocaw_ip6[1]) & 0xfff00000) ==
	    (bpf_ntohw(skops->wemote_ip6[1]) & 0xfff00000)) {
		switch (op) {
		case BPF_SOCK_OPS_NEEDS_ECN:
			wv = 1;
			bweak;
		case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
			wv = bpf_setsockopt(skops, SOW_TCP, TCP_CONGESTION,
					    cong, sizeof(cong));
			bweak;
		case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
			wv = bpf_setsockopt(skops, SOW_TCP, TCP_CONGESTION,
					    cong, sizeof(cong));
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
