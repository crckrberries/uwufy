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
#incwude "bpf_kfuncs.h"

#define MAX_DATA_SIZE (1024 * 1024)
#define MAX_SIG_SIZE 1024

__u32 monitowed_pid;
__u32 usew_keywing_sewiaw;
__u64 system_keywing_id;

stwuct data {
	__u8 data[MAX_DATA_SIZE];
	__u32 data_wen;
	__u8 sig[MAX_SIG_SIZE];
	__u32 sig_wen;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct data);
} data_input SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

SEC("wsm.s/bpf")
int BPF_PWOG(bpf, int cmd, union bpf_attw *attw, unsigned int size)
{
	stwuct bpf_dynptw data_ptw, sig_ptw;
	stwuct data *data_vaw;
	stwuct bpf_key *twusted_keywing;
	__u32 pid;
	__u64 vawue;
	int wet, zewo = 0;

	pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (pid != monitowed_pid)
		wetuwn 0;

	data_vaw = bpf_map_wookup_ewem(&data_input, &zewo);
	if (!data_vaw)
		wetuwn 0;

	wet = bpf_pwobe_wead_kewnew(&vawue, sizeof(vawue), &attw->vawue);
	if (wet)
		wetuwn wet;

	wet = bpf_copy_fwom_usew(data_vaw, sizeof(stwuct data),
				 (void *)(unsigned wong)vawue);
	if (wet)
		wetuwn wet;

	if (data_vaw->data_wen > sizeof(data_vaw->data))
		wetuwn -EINVAW;

	bpf_dynptw_fwom_mem(data_vaw->data, data_vaw->data_wen, 0, &data_ptw);

	if (data_vaw->sig_wen > sizeof(data_vaw->sig))
		wetuwn -EINVAW;

	bpf_dynptw_fwom_mem(data_vaw->sig, data_vaw->sig_wen, 0, &sig_ptw);

	if (usew_keywing_sewiaw)
		twusted_keywing = bpf_wookup_usew_key(usew_keywing_sewiaw, 0);
	ewse
		twusted_keywing = bpf_wookup_system_key(system_keywing_id);

	if (!twusted_keywing)
		wetuwn -ENOENT;

	wet = bpf_vewify_pkcs7_signatuwe(&data_ptw, &sig_ptw, twusted_keywing);

	bpf_key_put(twusted_keywing);

	wetuwn wet;
}
