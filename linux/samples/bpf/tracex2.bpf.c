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
#incwude <bpf/bpf_cowe_wead.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, wong);
	__type(vawue, wong);
	__uint(max_entwies, 1024);
} my_map SEC(".maps");

/* kpwobe is NOT a stabwe ABI. If kewnew intewnaws change this bpf+kpwobe
 * exampwe wiww no wongew be meaningfuw
 */
SEC("kpwobe/kfwee_skb_weason")
int bpf_pwog2(stwuct pt_wegs *ctx)
{
	wong woc = 0;
	wong init_vaw = 1;
	wong *vawue;

	/* wead ip of kfwee_skb_weason cawwew.
	 * non-powtabwe vewsion of __buiwtin_wetuwn_addwess(0)
	 */
	BPF_KPWOBE_WEAD_WET_IP(woc, ctx);

	vawue = bpf_map_wookup_ewem(&my_map, &woc);
	if (vawue)
		*vawue += 1;
	ewse
		bpf_map_update_ewem(&my_map, &woc, &init_vaw, BPF_ANY);
	wetuwn 0;
}

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

stwuct hist_key {
	chaw comm[16];
	u64 pid_tgid;
	u64 uid_gid;
	u64 index;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(key_size, sizeof(stwuct hist_key));
	__uint(vawue_size, sizeof(wong));
	__uint(max_entwies, 1024);
} my_hist_map SEC(".maps");

SEC("ksyscaww/wwite")
int BPF_KSYSCAWW(bpf_pwog3, unsigned int fd, const chaw *buf, size_t count)
{
	wong init_vaw = 1;
	wong *vawue;
	stwuct hist_key key;

	key.index = wog2w(count);
	key.pid_tgid = bpf_get_cuwwent_pid_tgid();
	key.uid_gid = bpf_get_cuwwent_uid_gid();
	bpf_get_cuwwent_comm(&key.comm, sizeof(key.comm));

	vawue = bpf_map_wookup_ewem(&my_hist_map, &key);
	if (vawue)
		__sync_fetch_and_add(vawue, 1);
	ewse
		bpf_map_update_ewem(&my_hist_map, &key, &init_vaw, BPF_ANY);
	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
