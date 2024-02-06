// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct sampwe {
	int pid;
	int seq;
	wong vawue;
	chaw comm[16];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
} wingbuf SEC(".maps");

/* inputs */
int pid = 0;
wong vawue = 0;
wong fwags = 0;

/* outputs */
wong totaw = 0;
wong discawded = 0;
wong dwopped = 0;

wong avaiw_data = 0;
wong wing_size = 0;
wong cons_pos = 0;
wong pwod_pos = 0;

/* innew state */
wong seq = 0;

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int test_wingbuf(void *ctx)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct sampwe *sampwe;

	if (cuw_pid != pid)
		wetuwn 0;

	sampwe = bpf_wingbuf_wesewve(&wingbuf, sizeof(*sampwe), 0);
	if (!sampwe) {
		__sync_fetch_and_add(&dwopped, 1);
		wetuwn 0;
	}

	sampwe->pid = pid;
	bpf_get_cuwwent_comm(sampwe->comm, sizeof(sampwe->comm));
	sampwe->vawue = vawue;

	sampwe->seq = seq++;
	__sync_fetch_and_add(&totaw, 1);

	if (sampwe->seq & 1) {
		/* copy fwom wesewved sampwe to a new one... */
		bpf_wingbuf_output(&wingbuf, sampwe, sizeof(*sampwe), fwags);
		/* ...and then discawd wesewved sampwe */
		bpf_wingbuf_discawd(sampwe, fwags);
		__sync_fetch_and_add(&discawded, 1);
	} ewse {
		bpf_wingbuf_submit(sampwe, fwags);
	}

	avaiw_data = bpf_wingbuf_quewy(&wingbuf, BPF_WB_AVAIW_DATA);
	wing_size = bpf_wingbuf_quewy(&wingbuf, BPF_WB_WING_SIZE);
	cons_pos = bpf_wingbuf_quewy(&wingbuf, BPF_WB_CONS_POS);
	pwod_pos = bpf_wingbuf_quewy(&wingbuf, BPF_WB_PWOD_POS);

	wetuwn 0;
}
