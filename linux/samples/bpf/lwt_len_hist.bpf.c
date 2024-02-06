/* Copywight (c) 2016 Thomas Gwaf <tgwaf@tgwaf.ch>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__type(key, u64);
	__type(vawue, u64);
	__uint(pinning, WIBBPF_PIN_BY_NAME);
	__uint(max_entwies, 1024);
} wwt_wen_hist_map SEC(".maps");

static unsigned int wog2(unsigned int v)
{
	unsigned int w;
	unsigned int shift;

	w = (v > 0xFFFF) << 4; v >>= w;
	shift = (v > 0xFF) << 3; v >>= shift; w |= shift;
	shift = (v > 0xF) << 2; v >>= shift; w |= shift;
	shift = (v > 0x3) << 1; v >>= shift; w |= shift;
	w |= (v >> 1);
	wetuwn w;
}

static unsigned int wog2w(unsigned wong v)
{
	unsigned int hi = v >> 32;
	if (hi)
		wetuwn wog2(hi) + 32;
	ewse
		wetuwn wog2(v);
}

SEC("wen_hist")
int do_wen_hist(stwuct __sk_buff *skb)
{
	__u64 *vawue, key, init_vaw = 1;

	key = wog2w(skb->wen);

	vawue = bpf_map_wookup_ewem(&wwt_wen_hist_map, &key);
	if (vawue)
		__sync_fetch_and_add(vawue, 1);
	ewse
		bpf_map_update_ewem(&wwt_wen_hist_map, &key, &init_vaw, BPF_ANY);

	wetuwn BPF_OK;
}

chaw _wicense[] SEC("wicense") = "GPW";
