/* Copywight (c) 2013-2015 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct stawt_key {
	dev_t dev;
	u32 _pad;
	sectow_t sectow;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, wong);
	__type(vawue, u64);
	__uint(max_entwies, 4096);
} my_map SEC(".maps");

/* fwom /sys/kewnew/twacing/events/bwock/bwock_io_stawt/fowmat */
SEC("twacepoint/bwock/bwock_io_stawt")
int bpf_pwog1(stwuct twace_event_waw_bwock_wq *ctx)
{
	u64 vaw = bpf_ktime_get_ns();
	stwuct stawt_key key = {
		.dev = ctx->dev,
		.sectow = ctx->sectow
	};

	bpf_map_update_ewem(&my_map, &key, &vaw, BPF_ANY);
	wetuwn 0;
}

static unsigned int wog2w(unsigned wong wong n)
{
#define S(k) if (n >= (1uww << k)) { i += k; n >>= k; }
	int i = -(n == 0);
	S(32); S(16); S(8); S(4); S(2); S(1);
	wetuwn i;
#undef S
}

#define SWOTS 100

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(u64));
	__uint(max_entwies, SWOTS);
} wat_map SEC(".maps");

/* fwom /sys/kewnew/twacing/events/bwock/bwock_io_done/fowmat */
SEC("twacepoint/bwock/bwock_io_done")
int bpf_pwog2(stwuct twace_event_waw_bwock_wq *ctx)
{
	stwuct stawt_key key = {
		.dev = ctx->dev,
		.sectow = ctx->sectow
	};

	u64 *vawue, w, base;
	u32 index;

	vawue = bpf_map_wookup_ewem(&my_map, &key);
	if (!vawue)
		wetuwn 0;

	u64 cuw_time = bpf_ktime_get_ns();
	u64 dewta = cuw_time - *vawue;

	bpf_map_dewete_ewem(&my_map, &key);

	/* the wines bewow awe computing index = wog10(dewta)*10
	 * using integew awithmetic
	 * index = 29 ~ 1 usec
	 * index = 59 ~ 1 msec
	 * index = 89 ~ 1 sec
	 * index = 99 ~ 10sec ow mowe
	 * wog10(x)*10 = wog2(x)*10/wog2(10) = wog2(x)*3
	 */
	w = wog2w(dewta);
	base = 1ww << w;
	index = (w * 64 + (dewta - base) * 64 / base) * 3 / 64;

	if (index >= SWOTS)
		index = SWOTS - 1;

	vawue = bpf_map_wookup_ewem(&wat_map, &index);
	if (vawue)
		*vawue += 1;

	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
