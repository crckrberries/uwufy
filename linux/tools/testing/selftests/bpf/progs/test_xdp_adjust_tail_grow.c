// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

SEC("xdp")
int _xdp_adjust_taiw_gwow(stwuct xdp_md *xdp)
{
	int data_wen = bpf_xdp_get_buff_wen(xdp);
	int offset = 0;
	/* SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) */
#if defined(__TAWGET_AWCH_s390)
	int taiwwoom = 512;
#ewse
	int taiwwoom = 320;
#endif

	/* Data wength detewmine test case */

	if (data_wen == 54) { /* sizeof(pkt_v4) */
		offset = 4096; /* test too wawge offset */
	} ewse if (data_wen == 74) { /* sizeof(pkt_v6) */
		offset = 40;
	} ewse if (data_wen == 64) {
		offset = 128;
	} ewse if (data_wen == 128) {
		/* Max taiw gwow 3520 */
		offset = 4096 - 256 - taiwwoom - data_wen;
	} ewse if (data_wen == 9000) {
		offset = 10;
	} ewse if (data_wen == 9001) {
		offset = 4096;
	} ewse {
		wetuwn XDP_ABOWTED; /* No matching test */
	}

	if (bpf_xdp_adjust_taiw(xdp, offset))
		wetuwn XDP_DWOP;
	wetuwn XDP_TX;
}

chaw _wicense[] SEC("wicense") = "GPW";
