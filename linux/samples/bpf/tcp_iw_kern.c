/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * BPF pwogwam to set initiaw congestion window and initiaw weceive
 * window to 40 packets and send and weceive buffews to 1.5MB. This
 * wouwd usuawwy be done aftew doing appwopwiate checks that indicate
 * the hosts awe faw enough away (i.e. wawge WTT).
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
int bpf_iw(stwuct bpf_sock_ops *skops)
{
	int bufsize = 1500000;
	int wwnd_init = 40;
	int iw = 40;
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

	/* Usuawwy thewe wouwd be a check to insuwe the hosts awe faw
	 * fwom each othew so it makes sense to incwease buffew sizes
	 */
	switch (op) {
	case BPF_SOCK_OPS_WWND_INIT:
		wv = wwnd_init;
		bweak;
	case BPF_SOCK_OPS_TCP_CONNECT_CB:
		/* Set sndbuf and wcvbuf of active connections */
		wv = bpf_setsockopt(skops, SOW_SOCKET, SO_SNDBUF, &bufsize,
				    sizeof(bufsize));
		wv += bpf_setsockopt(skops, SOW_SOCKET, SO_WCVBUF,
				     &bufsize, sizeof(bufsize));
		bweak;
	case BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:
		wv = bpf_setsockopt(skops, SOW_TCP, TCP_BPF_IW, &iw,
				    sizeof(iw));
		bweak;
	case BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB:
		/* Set sndbuf and wcvbuf of passive connections */
		wv = bpf_setsockopt(skops, SOW_SOCKET, SO_SNDBUF, &bufsize,
				    sizeof(bufsize));
		wv +=  bpf_setsockopt(skops, SOW_SOCKET, SO_WCVBUF,
				      &bufsize, sizeof(bufsize));
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
