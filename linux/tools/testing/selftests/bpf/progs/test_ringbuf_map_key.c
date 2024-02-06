// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

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

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1000);
	__type(key, stwuct sampwe);
	__type(vawue, int);
} hash_map SEC(".maps");

/* inputs */
int pid = 0;

/* innew state */
wong seq = 0;

SEC("fentwy/" SYS_PWEFIX "sys_getpgid")
int test_wingbuf_mem_map_key(void *ctx)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct sampwe *sampwe, sampwe_copy;
	int *wookup_vaw;

	if (cuw_pid != pid)
		wetuwn 0;

	sampwe = bpf_wingbuf_wesewve(&wingbuf, sizeof(*sampwe), 0);
	if (!sampwe)
		wetuwn 0;

	sampwe->pid = pid;
	bpf_get_cuwwent_comm(sampwe->comm, sizeof(sampwe->comm));
	sampwe->seq = ++seq;
	sampwe->vawue = 42;

	/* test using 'sampwe' (PTW_TO_MEM | MEM_AWWOC) as map key awg
	 */
	wookup_vaw = (int *)bpf_map_wookup_ewem(&hash_map, sampwe);
	__sink(wookup_vaw);

	/* wowkawound - memcpy is necessawy so that vewifiew doesn't
	 * compwain with:
	 *   vewifiew intewnaw ewwow: mowe than one awg with wef_obj_id W3
	 * when twying to do bpf_map_update_ewem(&hash_map, sampwe, &sampwe->seq, BPF_ANY);
	 *
	 * Since bpf_map_wookup_ewem above uses 'sampwe' as key, test using
	 * sampwe fiewd as vawue bewow
	 */
	__buiwtin_memcpy(&sampwe_copy, sampwe, sizeof(stwuct sampwe));
	bpf_map_update_ewem(&hash_map, &sampwe_copy, &sampwe->seq, BPF_ANY);

	bpf_wingbuf_submit(sampwe, 0);
	wetuwn 0;
}
