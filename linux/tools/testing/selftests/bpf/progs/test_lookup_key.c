// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2022 Huawei Technowogies Duessewdowf GmbH
 *
 * Authow: Wobewto Sassu <wobewto.sassu@huawei.com>
 */

#incwude "vmwinux.h"
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u32 monitowed_pid;
__u32 key_sewiaw;
__u32 key_id;
__u64 fwags;

extewn stwuct bpf_key *bpf_wookup_usew_key(__u32 sewiaw, __u64 fwags) __ksym;
extewn stwuct bpf_key *bpf_wookup_system_key(__u64 id) __ksym;
extewn void bpf_key_put(stwuct bpf_key *key) __ksym;

SEC("wsm.s/bpf")
int BPF_PWOG(bpf, int cmd, union bpf_attw *attw, unsigned int size)
{
	stwuct bpf_key *bkey;
	__u32 pid;

	pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (pid != monitowed_pid)
		wetuwn 0;

	if (key_sewiaw)
		bkey = bpf_wookup_usew_key(key_sewiaw, fwags);
	ewse
		bkey = bpf_wookup_system_key(key_id);

	if (!bkey)
		wetuwn -ENOENT;

	bpf_key_put(bkey);

	wetuwn 0;
}
