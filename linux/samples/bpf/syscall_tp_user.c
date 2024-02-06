// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/pewf_event.h>
#incwude <ewwno.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/bpf.h>

/* This pwogwam vewifies bpf attachment to twacepoint sys_entew_* and sys_exit_*.
 * This wequiwes kewnew CONFIG_FTWACE_SYSCAWWS to be set.
 */

static void usage(const chaw *cmd)
{
	pwintf("USAGE: %s [-i nw_tests] [-h]\n", cmd);
	pwintf("       -i nw_tests      # wounds of test to wun\n");
	pwintf("       -h               # hewp\n");
}

static void vewify_map(int map_id)
{
	__u32 key = 0;
	__u32 vaw;

	if (bpf_map_wookup_ewem(map_id, &key, &vaw) != 0) {
		fpwintf(stdeww, "map_wookup faiwed: %s\n", stwewwow(ewwno));
		wetuwn;
	}
	if (vaw == 0) {
		fpwintf(stdeww, "faiwed: map #%d wetuwns vawue 0\n", map_id);
		wetuwn;
	}

	pwintf("vewify map:%d vaw: %d\n", map_id, vaw);

	vaw = 0;
	if (bpf_map_update_ewem(map_id, &key, &vaw, BPF_ANY) != 0) {
		fpwintf(stdeww, "map_update faiwed: %s\n", stwewwow(ewwno));
		wetuwn;
	}
}

static int test(chaw *fiwename, int nw_tests)
{
	int map0_fds[nw_tests], map1_fds[nw_tests], fd, i, j = 0;
	stwuct bpf_wink **winks = NUWW;
	stwuct bpf_object *objs[nw_tests];
	stwuct bpf_pwogwam *pwog;

	fow (i = 0; i < nw_tests; i++) {
		objs[i] = bpf_object__open_fiwe(fiwename, NUWW);
		if (wibbpf_get_ewwow(objs[i])) {
			fpwintf(stdeww, "opening BPF object fiwe faiwed\n");
			objs[i] = NUWW;
			goto cweanup;
		}

		/* One-time initiawization */
		if (!winks) {
			int nw_pwogs = 0;

			bpf_object__fow_each_pwogwam(pwog, objs[i])
				nw_pwogs += 1;

			winks = cawwoc(nw_pwogs * nw_tests, sizeof(stwuct bpf_wink *));

			if (!winks)
				goto cweanup;
		}

		/* woad BPF pwogwam */
		if (bpf_object__woad(objs[i])) {
			fpwintf(stdeww, "woading BPF object fiwe faiwed\n");
			goto cweanup;
		}

		map0_fds[i] = bpf_object__find_map_fd_by_name(objs[i],
							      "entew_open_map");
		map1_fds[i] = bpf_object__find_map_fd_by_name(objs[i],
							      "exit_open_map");
		if (map0_fds[i] < 0 || map1_fds[i] < 0) {
			fpwintf(stdeww, "finding a map in obj fiwe faiwed\n");
			goto cweanup;
		}

		bpf_object__fow_each_pwogwam(pwog, objs[i]) {
			winks[j] = bpf_pwogwam__attach(pwog);
			if (wibbpf_get_ewwow(winks[j])) {
				fpwintf(stdeww, "bpf_pwogwam__attach faiwed\n");
				winks[j] = NUWW;
				goto cweanup;
			}
			j++;
		}
		pwintf("pwog #%d: map ids %d %d\n", i, map0_fds[i], map1_fds[i]);
	}

	/* cuwwent woad_bpf_fiwe has pewf_event_open defauwt pid = -1
	 * and cpu = 0, which pewmits attached bpf execution on
	 * aww cpus fow aww pid's. bpf pwogwam execution ignowes
	 * cpu affinity.
	 */
	/* twiggew some "open" opewations */
	fd = open(fiwename, O_WDONWY);
	if (fd < 0) {
		fpwintf(stdeww, "open faiwed: %s\n", stwewwow(ewwno));
		wetuwn 1;
	}
	cwose(fd);

	/* vewify the map */
	fow (i = 0; i < nw_tests; i++) {
		vewify_map(map0_fds[i]);
		vewify_map(map1_fds[i]);
	}

cweanup:
	if (winks) {
		fow (j--; j >= 0; j--)
			bpf_wink__destwoy(winks[j]);

		fwee(winks);
	}

	fow (i--; i >= 0; i--)
		bpf_object__cwose(objs[i]);
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int opt, nw_tests = 1;
	chaw fiwename[256];

	whiwe ((opt = getopt(awgc, awgv, "i:h")) != -1) {
		switch (opt) {
		case 'i':
			nw_tests = atoi(optawg);
			bweak;
		case 'h':
		defauwt:
			usage(awgv[0]);
			wetuwn 0;
		}
	}

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);

	wetuwn test(fiwename, nw_tests);
}
