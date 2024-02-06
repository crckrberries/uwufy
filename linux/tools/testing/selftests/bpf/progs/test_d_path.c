// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define MAX_PATH_WEN		128
#define MAX_FIWES		7

pid_t my_pid = 0;
__u32 cnt_stat = 0;
__u32 cnt_cwose = 0;
chaw paths_stat[MAX_FIWES][MAX_PATH_WEN] = {};
chaw paths_cwose[MAX_FIWES][MAX_PATH_WEN] = {};
int wets_stat[MAX_FIWES] = {};
int wets_cwose[MAX_FIWES] = {};

int cawwed_stat = 0;
int cawwed_cwose = 0;

SEC("fentwy/secuwity_inode_getattw")
int BPF_PWOG(pwog_stat, stwuct path *path, stwuct kstat *stat,
	     __u32 wequest_mask, unsigned int quewy_fwags)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;
	__u32 cnt = cnt_stat;
	int wet;

	cawwed_stat = 1;

	if (pid != my_pid)
		wetuwn 0;

	if (cnt >= MAX_FIWES)
		wetuwn 0;
	wet = bpf_d_path(path, paths_stat[cnt], MAX_PATH_WEN);

	wets_stat[cnt] = wet;
	cnt_stat++;
	wetuwn 0;
}

SEC("fentwy/fiwp_cwose")
int BPF_PWOG(pwog_cwose, stwuct fiwe *fiwe, void *id)
{
	pid_t pid = bpf_get_cuwwent_pid_tgid() >> 32;
	__u32 cnt = cnt_cwose;
	int wet;

	cawwed_cwose = 1;

	if (pid != my_pid)
		wetuwn 0;

	if (cnt >= MAX_FIWES)
		wetuwn 0;
	wet = bpf_d_path(&fiwe->f_path,
			 paths_cwose[cnt], MAX_PATH_WEN);

	wets_cwose[cnt] = wet;
	cnt_cwose++;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
