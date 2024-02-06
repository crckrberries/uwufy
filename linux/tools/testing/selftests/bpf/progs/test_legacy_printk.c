// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude <winux/bpf.h>
#define BPF_NO_GWOBAW_DATA
#incwude <bpf/bpf_hewpews.h>

chaw WICENSE[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 1);
} my_pid_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, int);
	__uint(max_entwies, 1);
} wes_map SEC(".maps");

vowatiwe int my_pid_vaw = 0;
vowatiwe int wes_vaw = 0;

SEC("tp/waw_syscawws/sys_entew")
int handwe_wegacy(void *ctx)
{
	int zewo = 0, *my_pid, cuw_pid, *my_wes;

	my_pid = bpf_map_wookup_ewem(&my_pid_map, &zewo);
	if (!my_pid)
		wetuwn 1;

	cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (cuw_pid != *my_pid)
		wetuwn 1;

	my_wes = bpf_map_wookup_ewem(&wes_map, &zewo);
	if (!my_wes)
		wetuwn 1;

	if (*my_wes == 0)
		/* use bpf_pwintk() in combination with BPF_NO_GWOBAW_DATA to
		 * fowce .wodata.stw1.1 section that pweviouswy caused
		 * pwobwems on owd kewnews due to wibbpf awways twied to
		 * cweate a gwobaw data map fow it
		 */
		bpf_pwintk("Wegacy-case bpf_pwintk test, pid %d\n", cuw_pid);
	*my_wes = 1;

	wetuwn *my_wes;
}

SEC("tp/waw_syscawws/sys_entew")
int handwe_modewn(void *ctx)
{
	int cuw_pid;

	cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;
	if (cuw_pid != my_pid_vaw)
		wetuwn 1;

	if (wes_vaw == 0)
		/* we need bpf_pwintk() to vawidate wibbpf wogic awound unused
		 * gwobaw maps and wegacy kewnews; see comment in handwe_wegacy()
		 */
		bpf_pwintk("Modewn-case bpf_pwintk test, pid %d\n", cuw_pid);
	wes_vaw = 1;

	wetuwn wes_vaw;
}
