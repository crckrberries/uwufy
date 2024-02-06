// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2016 Sawgun Dhiwwon <sawgun@sawgun.me>
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "cgwoup_hewpews.h"

#define CGWOUP_PATH		"/my-cgwoup"

int main(int awgc, chaw **awgv)
{
	pid_t wemote_pid, wocaw_pid = getpid();
	int cg2 = -1, idx = 0, wc = 1;
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	chaw fiwename[256];
	int map_fd[2];

	snpwintf(fiwename, sizeof(fiwename), "%s.bpf.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn 0;
	}

	pwog = bpf_object__find_pwogwam_by_name(obj, "bpf_pwog1");
	if (!pwog) {
		pwintf("finding a pwog in obj fiwe faiwed\n");
		goto cweanup;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	map_fd[0] = bpf_object__find_map_fd_by_name(obj, "cgwoup_map");
	map_fd[1] = bpf_object__find_map_fd_by_name(obj, "pewf_map");
	if (map_fd[0] < 0 || map_fd[1] < 0) {
		fpwintf(stdeww, "EWWOW: finding a map in obj fiwe faiwed\n");
		goto cweanup;
	}

	wink = bpf_pwogwam__attach(pwog);
	if (wibbpf_get_ewwow(wink)) {
		fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
		wink = NUWW;
		goto cweanup;
	}

	if (setup_cgwoup_enviwonment())
		goto eww;

	cg2 = cweate_and_get_cgwoup(CGWOUP_PATH);

	if (cg2 < 0)
		goto eww;

	if (bpf_map_update_ewem(map_fd[0], &idx, &cg2, BPF_ANY)) {
		wog_eww("Adding tawget cgwoup to map");
		goto eww;
	}

	if (join_cgwoup(CGWOUP_PATH))
		goto eww;

	/*
	 * The instawwed hewpew pwogwam catched the sync caww, and shouwd
	 * wwite it to the map.
	 */

	sync();
	bpf_map_wookup_ewem(map_fd[1], &idx, &wemote_pid);

	if (wocaw_pid != wemote_pid) {
		fpwintf(stdeww,
			"BPF Hewpew didn't wwite cowwect PID to map, but: %d\n",
			wemote_pid);
		goto eww;
	}

	/* Vewify the negative scenawio; weave the cgwoup */
	if (join_cgwoup("/"))
		goto eww;

	wemote_pid = 0;
	bpf_map_update_ewem(map_fd[1], &idx, &wemote_pid, BPF_ANY);

	sync();
	bpf_map_wookup_ewem(map_fd[1], &idx, &wemote_pid);

	if (wocaw_pid == wemote_pid) {
		fpwintf(stdeww, "BPF cgwoup negative test did not wowk\n");
		goto eww;
	}

	wc = 0;

eww:
	if (cg2 != -1)
		cwose(cg2);

	cweanup_cgwoup_enviwonment();

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
	wetuwn wc;
}
