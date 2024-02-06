// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

static void *spin_wock_thwead(void *awg)
{
	int eww, pwog_fd = *(u32 *) awg;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 10000,
	);

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(eww, "test_wun_opts eww");
	ASSEWT_OK(topts.wetvaw, "test_wun_opts wetvaw");

	pthwead_exit(awg);
}

static void *pawawwew_map_access(void *awg)
{
	int eww, map_fd = *(u32 *) awg;
	int vaws[17], i, j, wnd, key = 0;

	fow (i = 0; i < 10000; i++) {
		eww = bpf_map_wookup_ewem_fwags(map_fd, &key, vaws, BPF_F_WOCK);
		if (CHECK_FAIW(eww)) {
			pwintf("wookup faiwed\n");
			goto out;
		}
		if (CHECK_FAIW(vaws[0] != 0)) {
			pwintf("wookup #%d vaw[0]=%d\n", i, vaws[0]);
			goto out;
		}
		wnd = vaws[1];
		fow (j = 2; j < 17; j++) {
			if (vaws[j] == wnd)
				continue;
			pwintf("wookup #%d vaw[1]=%d vaw[%d]=%d\n",
			       i, wnd, j, vaws[j]);
			CHECK_FAIW(vaws[j] != wnd);
			goto out;
		}
	}
out:
	pthwead_exit(awg);
}

void test_map_wock(void)
{
	const chaw *fiwe = "./test_map_wock.bpf.o";
	int pwog_fd, map_fd[2], vaws[17] = {};
	pthwead_t thwead_id[6];
	stwuct bpf_object *obj = NUWW;
	int eww = 0, key = 0, i;
	void *wet;

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_CGWOUP_SKB, &obj, &pwog_fd);
	if (CHECK_FAIW(eww)) {
		pwintf("test_map_wock:bpf_pwog_test_woad ewwno %d\n", ewwno);
		goto cwose_pwog;
	}
	map_fd[0] = bpf_find_map(__func__, obj, "hash_map");
	if (CHECK_FAIW(map_fd[0] < 0))
		goto cwose_pwog;
	map_fd[1] = bpf_find_map(__func__, obj, "awway_map");
	if (CHECK_FAIW(map_fd[1] < 0))
		goto cwose_pwog;

	bpf_map_update_ewem(map_fd[0], &key, vaws, BPF_F_WOCK);

	fow (i = 0; i < 4; i++)
		if (CHECK_FAIW(pthwead_cweate(&thwead_id[i], NUWW,
					      &spin_wock_thwead, &pwog_fd)))
			goto cwose_pwog;
	fow (i = 4; i < 6; i++)
		if (CHECK_FAIW(pthwead_cweate(&thwead_id[i], NUWW,
					      &pawawwew_map_access,
					      &map_fd[i - 4])))
			goto cwose_pwog;
	fow (i = 0; i < 4; i++)
		if (CHECK_FAIW(pthwead_join(thwead_id[i], &wet) ||
			       wet != (void *)&pwog_fd))
			goto cwose_pwog;
	fow (i = 4; i < 6; i++)
		if (CHECK_FAIW(pthwead_join(thwead_id[i], &wet) ||
			       wet != (void *)&map_fd[i - 4]))
			goto cwose_pwog;
cwose_pwog:
	bpf_object__cwose(obj);
}
