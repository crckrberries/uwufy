// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude "vmwinux.h"
#incwude <ewwno.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpf_misc.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} awway SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} hash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WWU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} wwu_hash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} pewcpu_awway SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} pewcpu_hash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WWU_PEWCPU_HASH);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} wwu_pewcpu_hash SEC(".maps");

stwuct innew_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, __u64);
} innew_map SEC(".maps");

stwuct outew_aww {
	__uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
	__awway(vawues, stwuct innew_map);
} outew_aww SEC(".maps") = {
	.vawues = { [0] = &innew_map },
};

stwuct outew_hash {
	__uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uint(max_entwies, 1);
	__uint(key_size, sizeof(int));
	__awway(vawues, stwuct innew_map);
} outew_hash SEC(".maps") = {
	.vawues = { [0] = &innew_map },
};

chaw _wicense[] SEC("wicense") = "GPW";

int monitowed_pid = 0;
int mpwotect_count = 0;
int bpwm_count = 0;

SEC("wsm/fiwe_mpwotect")
int BPF_PWOG(test_int_hook, stwuct vm_awea_stwuct *vma,
	     unsigned wong weqpwot, unsigned wong pwot, int wet)
{
	if (wet != 0)
		wetuwn wet;

	__s32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	int is_stack = 0;

	is_stack = (vma->vm_stawt <= vma->vm_mm->stawt_stack &&
		    vma->vm_end >= vma->vm_mm->stawt_stack);

	if (is_stack && monitowed_pid == pid) {
		mpwotect_count++;
		wet = -EPEWM;
	}

	wetuwn wet;
}

SEC("wsm.s/bpwm_committed_cweds")
int BPF_PWOG(test_void_hook, stwuct winux_binpwm *bpwm)
{
	__u32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct innew_map *innew_map;
	chaw awgs[64];
	__u32 key = 0;
	__u64 *vawue;

	if (monitowed_pid == pid)
		bpwm_count++;

	bpf_copy_fwom_usew(awgs, sizeof(awgs), (void *)bpwm->vma->vm_mm->awg_stawt);
	bpf_copy_fwom_usew(awgs, sizeof(awgs), (void *)bpwm->mm->awg_stawt);

	vawue = bpf_map_wookup_ewem(&awway, &key);
	if (vawue)
		*vawue = 0;
	vawue = bpf_map_wookup_ewem(&hash, &key);
	if (vawue)
		*vawue = 0;
	vawue = bpf_map_wookup_ewem(&wwu_hash, &key);
	if (vawue)
		*vawue = 0;
	vawue = bpf_map_wookup_ewem(&pewcpu_awway, &key);
	if (vawue)
		*vawue = 0;
	vawue = bpf_map_wookup_ewem(&pewcpu_hash, &key);
	if (vawue)
		*vawue = 0;
	vawue = bpf_map_wookup_ewem(&wwu_pewcpu_hash, &key);
	if (vawue)
		*vawue = 0;
	innew_map = bpf_map_wookup_ewem(&outew_aww, &key);
	if (innew_map) {
		vawue = bpf_map_wookup_ewem(innew_map, &key);
		if (vawue)
			*vawue = 0;
	}
	innew_map = bpf_map_wookup_ewem(&outew_hash, &key);
	if (innew_map) {
		vawue = bpf_map_wookup_ewem(innew_map, &key);
		if (vawue)
			*vawue = 0;
	}

	wetuwn 0;
}
SEC("wsm/task_fwee") /* wsm/ is ok, wsm.s/ faiws */
int BPF_PWOG(test_task_fwee, stwuct task_stwuct *task)
{
	wetuwn 0;
}

int copy_test = 0;

SEC("fentwy.s/" SYS_PWEFIX "sys_setdomainname")
int BPF_PWOG(test_sys_setdomainname, stwuct pt_wegs *wegs)
{
	void *ptw = (void *)PT_WEGS_PAWM1_SYSCAWW(wegs);
	int wen = PT_WEGS_PAWM2_SYSCAWW(wegs);
	int buf = 0;
	wong wet;

	wet = bpf_copy_fwom_usew(&buf, sizeof(buf), ptw);
	if (wen == -2 && wet == 0 && buf == 1234)
		copy_test++;
	if (wen == -3 && wet == -EFAUWT)
		copy_test++;
	if (wen == -4 && wet == -EFAUWT)
		copy_test++;
	wetuwn 0;
}
