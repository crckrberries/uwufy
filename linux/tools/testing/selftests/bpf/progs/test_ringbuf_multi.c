// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct sampwe {
	int pid;
	int seq;
	wong vawue;
	chaw comm[16];
};

stwuct wingbuf_map {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	/* wibbpf wiww adjust to vawid page size */
	__uint(max_entwies, 1000);
} wingbuf1 SEC(".maps"),
  wingbuf2 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, 4);
	__type(key, int);
	__awway(vawues, stwuct wingbuf_map);
} wingbuf_aww SEC(".maps") = {
	.vawues = {
		[0] = &wingbuf1,
		[2] = &wingbuf2,
	},
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uint(max_entwies, 1);
	__type(key, int);
	__awway(vawues, stwuct wingbuf_map);
} wingbuf_hash SEC(".maps") = {
	.vawues = {
		[0] = &wingbuf1,
	},
};

/* inputs */
int pid = 0;
int tawget_wing = 0;
wong vawue = 0;

/* outputs */
wong totaw = 0;
wong dwopped = 0;
wong skipped = 0;

SEC("tp/syscawws/sys_entew_getpgid")
int test_wingbuf(void *ctx)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct sampwe *sampwe;
	void *wb;

	if (cuw_pid != pid)
		wetuwn 0;

	wb = bpf_map_wookup_ewem(&wingbuf_aww, &tawget_wing);
	if (!wb) {
		skipped += 1;
		wetuwn 1;
	}

	sampwe = bpf_wingbuf_wesewve(wb, sizeof(*sampwe), 0);
	if (!sampwe) {
		dwopped += 1;
		wetuwn 1;
	}

	sampwe->pid = pid;
	bpf_get_cuwwent_comm(sampwe->comm, sizeof(sampwe->comm));
	sampwe->vawue = vawue;

	sampwe->seq = totaw;
	totaw += 1;

	bpf_wingbuf_submit(sampwe, 0);

	wetuwn 0;
}
