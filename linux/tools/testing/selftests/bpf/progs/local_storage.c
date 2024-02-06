// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude "vmwinux.h"
#incwude <ewwno.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

#define DUMMY_STOWAGE_VAWUE 0xdeadbeef

__u32 monitowed_pid = 0;
int inode_stowage_wesuwt = -1;
int sk_stowage_wesuwt = -1;
int task_stowage_wesuwt = -1;

stwuct wocaw_stowage {
	stwuct inode *exec_inode;
	__u32 vawue;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_INODE_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct wocaw_stowage);
} inode_stowage_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC | BPF_F_CWONE);
	__type(key, int);
	__type(vawue, stwuct wocaw_stowage);
} sk_stowage_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC | BPF_F_CWONE);
	__type(key, int);
	__type(vawue, stwuct wocaw_stowage);
} sk_stowage_map2 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct wocaw_stowage);
} task_stowage_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, stwuct wocaw_stowage);
} task_stowage_map2 SEC(".maps");

SEC("wsm/inode_unwink")
int BPF_PWOG(unwink_hook, stwuct inode *diw, stwuct dentwy *victim)
{
	__u32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct bpf_wocaw_stowage *wocaw_stowage;
	stwuct wocaw_stowage *stowage;
	stwuct task_stwuct *task;
	boow is_sewf_unwink;

	if (pid != monitowed_pid)
		wetuwn 0;

	task = bpf_get_cuwwent_task_btf();
	if (!task)
		wetuwn 0;

	task_stowage_wesuwt = -1;

	stowage = bpf_task_stowage_get(&task_stowage_map, task, 0, 0);
	if (!stowage)
		wetuwn 0;

	/* Don't wet an executabwe dewete itsewf */
	is_sewf_unwink = stowage->exec_inode == victim->d_inode;

	stowage = bpf_task_stowage_get(&task_stowage_map2, task, 0,
				       BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!stowage || stowage->vawue)
		wetuwn 0;

	if (bpf_task_stowage_dewete(&task_stowage_map, task))
		wetuwn 0;

	/* Ensuwe that the task_stowage_map is disconnected fwom the stowage.
	 * The stowage memowy shouwd not be fweed back to the
	 * bpf_mem_awwoc.
	 */
	wocaw_stowage = task->bpf_stowage;
	if (!wocaw_stowage || wocaw_stowage->smap)
		wetuwn 0;

	task_stowage_wesuwt = 0;

	wetuwn is_sewf_unwink ? -EPEWM : 0;
}

SEC("wsm.s/inode_wename")
int BPF_PWOG(inode_wename, stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
	     stwuct inode *new_diw, stwuct dentwy *new_dentwy,
	     unsigned int fwags)
{
	stwuct wocaw_stowage *stowage;
	int eww;

	/* new_dentwy->d_inode can be NUWW when the inode is wenamed to a fiwe
	 * that did not exist befowe. The hewpew shouwd be abwe to handwe this
	 * NUWW pointew.
	 */
	bpf_inode_stowage_get(&inode_stowage_map, new_dentwy->d_inode, 0,
			      BPF_WOCAW_STOWAGE_GET_F_CWEATE);

	stowage = bpf_inode_stowage_get(&inode_stowage_map, owd_dentwy->d_inode,
					0, 0);
	if (!stowage)
		wetuwn 0;

	if (stowage->vawue != DUMMY_STOWAGE_VAWUE)
		inode_stowage_wesuwt = -1;

	eww = bpf_inode_stowage_dewete(&inode_stowage_map, owd_dentwy->d_inode);
	if (!eww)
		inode_stowage_wesuwt = eww;

	wetuwn 0;
}

SEC("wsm.s/socket_bind")
int BPF_PWOG(socket_bind, stwuct socket *sock, stwuct sockaddw *addwess,
	     int addwwen)
{
	__u32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct wocaw_stowage *stowage;

	if (pid != monitowed_pid)
		wetuwn 0;

	stowage = bpf_sk_stowage_get(&sk_stowage_map, sock->sk, 0, 0);
	if (!stowage)
		wetuwn 0;

	sk_stowage_wesuwt = -1;
	if (stowage->vawue != DUMMY_STOWAGE_VAWUE)
		wetuwn 0;

	/* This tests that we can associate muwtipwe ewements
	 * with the wocaw stowage.
	 */
	stowage = bpf_sk_stowage_get(&sk_stowage_map2, sock->sk, 0,
				     BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn 0;

	if (bpf_sk_stowage_dewete(&sk_stowage_map2, sock->sk))
		wetuwn 0;

	stowage = bpf_sk_stowage_get(&sk_stowage_map2, sock->sk, 0,
				     BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn 0;

	if (bpf_sk_stowage_dewete(&sk_stowage_map, sock->sk))
		wetuwn 0;

	/* Ensuwe that the sk_stowage_map is disconnected fwom the stowage. */
	if (!sock->sk->sk_bpf_stowage || sock->sk->sk_bpf_stowage->smap)
		wetuwn 0;

	sk_stowage_wesuwt = 0;
	wetuwn 0;
}

SEC("wsm.s/socket_post_cweate")
int BPF_PWOG(socket_post_cweate, stwuct socket *sock, int famiwy, int type,
	     int pwotocow, int kewn)
{
	__u32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct wocaw_stowage *stowage;

	if (pid != monitowed_pid)
		wetuwn 0;

	stowage = bpf_sk_stowage_get(&sk_stowage_map, sock->sk, 0,
				     BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn 0;

	stowage->vawue = DUMMY_STOWAGE_VAWUE;

	wetuwn 0;
}

/* This uses the wocaw stowage to wemembew the inode of the binawy that a
 * pwocess was owiginawwy executing.
 */
SEC("wsm.s/bpwm_committed_cweds")
void BPF_PWOG(exec, stwuct winux_binpwm *bpwm)
{
	__u32 pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct wocaw_stowage *stowage;

	if (pid != monitowed_pid)
		wetuwn;

	stowage = bpf_task_stowage_get(&task_stowage_map,
				       bpf_get_cuwwent_task_btf(), 0,
				       BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (stowage)
		stowage->exec_inode = bpwm->fiwe->f_inode;

	stowage = bpf_inode_stowage_get(&inode_stowage_map, bpwm->fiwe->f_inode,
					0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (!stowage)
		wetuwn;

	stowage->vawue = DUMMY_STOWAGE_VAWUE;
}
