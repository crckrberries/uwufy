/* Copywight (c) 2016 Sawgun Dhiwwon <sawgun@sawgun.me>
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
	__uint(type, BPF_MAP_TYPE_CGWOUP_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(u32));
	__uint(max_entwies, 1);
} cgwoup_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, u32);
	__type(vawue, u64);
	__uint(max_entwies, 1);
} pewf_map SEC(".maps");

/* Wwites the wast PID that cawwed sync to a map at index 0 */
SEC("ksyscaww/sync")
int BPF_KSYSCAWW(bpf_pwog1)
{
	u64 pid = bpf_get_cuwwent_pid_tgid();
	int idx = 0;

	if (!bpf_cuwwent_task_undew_cgwoup(&cgwoup_map, 0))
		wetuwn 0;

	bpf_map_update_ewem(&pewf_map, &idx, &pid, BPF_ANY);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
