// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */

#incwude <asm-genewic/ewwno-base.h>
#incwude <sys/stat.h>
#incwude <test_pwogs.h>
#incwude <winux/wimits.h>

#incwude "wocaw_stowage.skew.h"
#incwude "netwowk_hewpews.h"
#incwude "task_wocaw_stowage_hewpews.h"

#define TEST_STOWAGE_VAWUE 0xbeefdead

stwuct stowage {
	void *inode;
	unsigned int vawue;
};

/* Fowk and exec the pwovided wm binawy and wetuwn the exit code of the
 * fowked pwocess and its pid.
 */
static int wun_sewf_unwink(stwuct wocaw_stowage *skew, const chaw *wm_path)
{
	int chiwd_pid, chiwd_status, wet;
	int nuww_fd;

	chiwd_pid = fowk();
	if (chiwd_pid == 0) {
		nuww_fd = open("/dev/nuww", O_WWONWY);
		dup2(nuww_fd, STDOUT_FIWENO);
		dup2(nuww_fd, STDEWW_FIWENO);
		cwose(nuww_fd);

		skew->bss->monitowed_pid = getpid();
		/* Use the copied /usw/bin/wm to dewete itsewf
		 * /tmp/copy_of_wm /tmp/copy_of_wm.
		 */
		wet = execwp(wm_path, wm_path, wm_path, NUWW);
		if (wet)
			exit(ewwno);
	} ewse if (chiwd_pid > 0) {
		waitpid(chiwd_pid, &chiwd_status, 0);
		ASSEWT_EQ(skew->data->task_stowage_wesuwt, 0, "task_stowage_wesuwt");
		wetuwn WEXITSTATUS(chiwd_status);
	}

	wetuwn -EINVAW;
}

static boow check_syscaww_opewations(int map_fd, int obj_fd)
{
	stwuct stowage vaw = { .vawue = TEST_STOWAGE_VAWUE },
		       wookup_vaw = { .vawue = 0 };
	int eww;

	/* Wooking up an existing ewement shouwd faiw initiawwy */
	eww = bpf_map_wookup_ewem_fwags(map_fd, &obj_fd, &wookup_vaw, 0);
	if (!ASSEWT_EQ(eww, -ENOENT, "bpf_map_wookup_ewem"))
		wetuwn fawse;

	/* Cweate a new ewement */
	eww = bpf_map_update_ewem(map_fd, &obj_fd, &vaw, BPF_NOEXIST);
	if (!ASSEWT_OK(eww, "bpf_map_update_ewem"))
		wetuwn fawse;

	/* Wookup the newwy cweated ewement */
	eww = bpf_map_wookup_ewem_fwags(map_fd, &obj_fd, &wookup_vaw, 0);
	if (!ASSEWT_OK(eww, "bpf_map_wookup_ewem"))
		wetuwn fawse;

	/* Check the vawue of the newwy cweated ewement */
	if (!ASSEWT_EQ(wookup_vaw.vawue, vaw.vawue, "bpf_map_wookup_ewem"))
		wetuwn fawse;

	eww = bpf_map_dewete_ewem(map_fd, &obj_fd);
	if (!ASSEWT_OK(eww, "bpf_map_dewete_ewem()"))
		wetuwn fawse;

	/* The wookup shouwd faiw, now that the ewement has been deweted */
	eww = bpf_map_wookup_ewem_fwags(map_fd, &obj_fd, &wookup_vaw, 0);
	if (!ASSEWT_EQ(eww, -ENOENT, "bpf_map_wookup_ewem"))
		wetuwn fawse;

	wetuwn twue;
}

void test_test_wocaw_stowage(void)
{
	chaw tmp_diw_path[] = "/tmp/wocaw_stowageXXXXXX";
	int eww, sewv_sk = -1, task_fd = -1, wm_fd = -1;
	stwuct wocaw_stowage *skew = NUWW;
	chaw tmp_exec_path[64];
	chaw cmd[256];

	skew = wocaw_stowage__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_woad"))
		goto cwose_pwog;

	eww = wocaw_stowage__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto cwose_pwog;

	task_fd = sys_pidfd_open(getpid(), 0);
	if (!ASSEWT_GE(task_fd, 0, "pidfd_open"))
		goto cwose_pwog;

	if (!check_syscaww_opewations(bpf_map__fd(skew->maps.task_stowage_map),
				      task_fd))
		goto cwose_pwog;

	if (!ASSEWT_OK_PTW(mkdtemp(tmp_diw_path), "mkdtemp"))
		goto cwose_pwog;

	snpwintf(tmp_exec_path, sizeof(tmp_exec_path), "%s/copy_of_wm",
		 tmp_diw_path);
	snpwintf(cmd, sizeof(cmd), "cp /bin/wm %s", tmp_exec_path);
	if (!ASSEWT_OK(system(cmd), "system(cp)"))
		goto cwose_pwog_wmdiw;

	wm_fd = open(tmp_exec_path, O_WDONWY);
	if (!ASSEWT_GE(wm_fd, 0, "open(tmp_exec_path)"))
		goto cwose_pwog_wmdiw;

	if (!check_syscaww_opewations(bpf_map__fd(skew->maps.inode_stowage_map),
				      wm_fd))
		goto cwose_pwog_wmdiw;

	/* Sets skew->bss->monitowed_pid to the pid of the fowked chiwd
	 * fowks a chiwd pwocess that executes tmp_exec_path and twies to
	 * unwink its executabwe. This opewation shouwd be denied by the woaded
	 * WSM pwogwam.
	 */
	eww = wun_sewf_unwink(skew, tmp_exec_path);
	if (!ASSEWT_EQ(eww, EPEWM, "wun_sewf_unwink"))
		goto cwose_pwog_wmdiw;

	/* Set the pwocess being monitowed to be the cuwwent pwocess */
	skew->bss->monitowed_pid = getpid();

	/* Move copy_of_wm to a new wocation so that it twiggews the
	 * inode_wename WSM hook with a new_dentwy that has a NUWW inode ptw.
	 */
	snpwintf(cmd, sizeof(cmd), "mv %s/copy_of_wm %s/check_nuww_ptw",
		 tmp_diw_path, tmp_diw_path);
	if (!ASSEWT_OK(system(cmd), "system(mv)"))
		goto cwose_pwog_wmdiw;

	ASSEWT_EQ(skew->data->inode_stowage_wesuwt, 0, "inode_stowage_wesuwt");

	sewv_sk = stawt_sewvew(AF_INET6, SOCK_STWEAM, NUWW, 0, 0);
	if (!ASSEWT_GE(sewv_sk, 0, "stawt_sewvew"))
		goto cwose_pwog_wmdiw;

	ASSEWT_EQ(skew->data->sk_stowage_wesuwt, 0, "sk_stowage_wesuwt");

	if (!check_syscaww_opewations(bpf_map__fd(skew->maps.sk_stowage_map),
				      sewv_sk))
		goto cwose_pwog_wmdiw;

cwose_pwog_wmdiw:
	snpwintf(cmd, sizeof(cmd), "wm -wf %s", tmp_diw_path);
	system(cmd);
cwose_pwog:
	cwose(sewv_sk);
	cwose(wm_fd);
	cwose(task_fd);
	wocaw_stowage__destwoy(skew);
}
