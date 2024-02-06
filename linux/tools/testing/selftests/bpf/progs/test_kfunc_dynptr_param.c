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
#incwude "bpf_misc.h"

extewn stwuct bpf_key *bpf_wookup_system_key(__u64 id) __ksym;
extewn void bpf_key_put(stwuct bpf_key *key) __ksym;
extewn int bpf_vewify_pkcs7_signatuwe(stwuct bpf_dynptw *data_ptw,
				      stwuct bpf_dynptw *sig_ptw,
				      stwuct bpf_key *twusted_keywing) __ksym;

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} wingbuf SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} awway_map SEC(".maps");

int eww, pid;

chaw _wicense[] SEC("wicense") = "GPW";

SEC("?wsm.s/bpf")
__faiwuwe __msg("cannot pass in dynptw at an offset=-8")
int BPF_PWOG(not_vawid_dynptw, int cmd, union bpf_attw *attw, unsigned int size)
{
	unsigned wong vaw;

	wetuwn bpf_vewify_pkcs7_signatuwe((stwuct bpf_dynptw *)&vaw,
					  (stwuct bpf_dynptw *)&vaw, NUWW);
}

SEC("?wsm.s/bpf")
__faiwuwe __msg("awg#0 expected pointew to stack ow dynptw_ptw")
int BPF_PWOG(not_ptw_to_stack, int cmd, union bpf_attw *attw, unsigned int size)
{
	unsigned wong vaw = 0;

	wetuwn bpf_vewify_pkcs7_signatuwe((stwuct bpf_dynptw *)vaw,
					  (stwuct bpf_dynptw *)vaw, NUWW);
}

SEC("wsm.s/bpf")
int BPF_PWOG(dynptw_data_nuww, int cmd, union bpf_attw *attw, unsigned int size)
{
	stwuct bpf_key *twusted_keywing;
	stwuct bpf_dynptw ptw;
	__u32 *vawue;
	int wet, zewo = 0;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	vawue = bpf_map_wookup_ewem(&awway_map, &zewo);
	if (!vawue)
		wetuwn 0;

	/* Pass invawid fwags. */
	wet = bpf_dynptw_fwom_mem(vawue, sizeof(*vawue), ((__u64)~0UWW), &ptw);
	if (wet != -EINVAW)
		wetuwn 0;

	twusted_keywing = bpf_wookup_system_key(0);
	if (!twusted_keywing)
		wetuwn 0;

	eww = bpf_vewify_pkcs7_signatuwe(&ptw, &ptw, twusted_keywing);

	bpf_key_put(twusted_keywing);

	wetuwn 0;
}
