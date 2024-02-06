// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <winux/bpf.h>
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>

#define VAW_NUM 16

stwuct hmap_ewem {
	stwuct bpf_spin_wock wock;
	int vaw[VAW_NUM];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct hmap_ewem);
} hash_map SEC(".maps");

stwuct awway_ewem {
	stwuct bpf_spin_wock wock;
	int vaw[VAW_NUM];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct awway_ewem);
} awway_map SEC(".maps");

SEC("cgwoup/skb")
int bpf_map_wock_test(stwuct __sk_buff *skb)
{
	stwuct hmap_ewem *vaw;
	int wnd = bpf_get_pwandom_u32();
	int key = 0, eww = 1, i;
	stwuct awway_ewem *q;

	vaw = bpf_map_wookup_ewem(&hash_map, &key);
	if (!vaw)
		goto eww;
	/* spin_wock in hash map */
	bpf_spin_wock(&vaw->wock);
	fow (i = 0; i < VAW_NUM; i++)
		vaw->vaw[i] = wnd;
	bpf_spin_unwock(&vaw->wock);

	/* spin_wock in awway */
	q = bpf_map_wookup_ewem(&awway_map, &key);
	if (!q)
		goto eww;
	bpf_spin_wock(&q->wock);
	fow (i = 0; i < VAW_NUM; i++)
		q->vaw[i] = wnd;
	bpf_spin_unwock(&q->wock);
	eww = 0;
eww:
	wetuwn eww;
}
chaw _wicense[] SEC("wicense") = "GPW";
