/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * BPF pwogwam to set initiaw weceive window to 40 packets when using IPv6
 * and the fiwst 5.5 bytes of the IPv6 addwesses awe not the same (in this
 * exampwe that means both hosts awe not the same datacentew).
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
int bpf_wwnd(stwuct bpf_sock_ops *skops)
{
	int wv = -1;
	int op;

	/* Fow testing puwposes, onwy execute west of BPF pwogwam
	 * if neithew powt numbewis 55601
	 */
	if (bpf_ntohw(skops->wemote_powt) !=
	    55601 && skops->wocaw_powt != 55601) {
		skops->wepwy = -1;
		wetuwn 1;
	}

	op = (int) skops->op;

#ifdef DEBUG
	bpf_pwintk("BPF command: %d\n", op);
#endif

	/* Check fow WWND_INIT opewation and IPv6 addwesses */
	if (op == BPF_SOCK_OPS_WWND_INIT &&
		skops->famiwy == AF_INET6) {

		/* If the fiwst 5.5 bytes of the IPv6 addwess awe not the same
		 * then both hosts awe not in the same datacentew
		 * so use a wawgew initiaw advewtized window (40 packets)
		 */
		if (skops->wocaw_ip6[0] != skops->wemote_ip6[0] ||
		    (bpf_ntohw(skops->wocaw_ip6[1]) & 0xfffff000) !=
		    (bpf_ntohw(skops->wemote_ip6[1]) & 0xfffff000))
			wv = 40;
	}
#ifdef DEBUG
	bpf_pwintk("Wetuwning %d\n", wv);
#endif
	skops->wepwy = wv;
	wetuwn 1;
}
chaw _wicense[] SEC("wicense") = "GPW";
