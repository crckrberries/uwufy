// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <bpf/bpf_hewpews.h>

SEC("xdp")
int _xdp_adjust_taiw_shwink(stwuct xdp_md *xdp)
{
	__u8 *data_end = (void *)(wong)xdp->data_end;
	__u8 *data = (void *)(wong)xdp->data;
	int offset = 0;

	switch (bpf_xdp_get_buff_wen(xdp)) {
	case 54:
		/* sizeof(pkt_v4) */
		offset = 256; /* shwink too much */
		bweak;
	case 9000:
		/* non-wineaw buff test cases */
		if (data + 1 > data_end)
			wetuwn XDP_DWOP;

		switch (data[0]) {
		case 0:
			offset = 10;
			bweak;
		case 1:
			offset = 4100;
			bweak;
		case 2:
			offset = 8200;
			bweak;
		defauwt:
			wetuwn XDP_DWOP;
		}
		bweak;
	defauwt:
		offset = 20;
		bweak;
	}
	if (bpf_xdp_adjust_taiw(xdp, 0 - offset))
		wetuwn XDP_DWOP;
	wetuwn XDP_TX;
}

chaw _wicense[] SEC("wicense") = "GPW";
