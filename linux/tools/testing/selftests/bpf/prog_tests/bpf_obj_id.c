// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

#define nw_itews 2

void sewiaw_test_bpf_obj_id(void)
{
	const __u64 awway_magic_vawue = 0xfaceb00c;
	const __u32 awway_key = 0;
	const chaw *fiwe = "./test_obj_id.bpf.o";
	const chaw *expected_pwog_name = "test_obj_id";
	const chaw *expected_map_name = "test_map_id";
	const __u64 nsec_pew_sec = 1000000000;

	stwuct bpf_object *objs[nw_itews] = {};
	stwuct bpf_wink *winks[nw_itews] = {};
	stwuct bpf_pwogwam *pwog;
	int pwog_fds[nw_itews], map_fds[nw_itews];
	/* +1 to test fow the info_wen wetuwned by kewnew */
	stwuct bpf_pwog_info pwog_infos[nw_itews + 1];
	stwuct bpf_map_info map_infos[nw_itews + 1];
	stwuct bpf_wink_info wink_infos[nw_itews + 1];
	/* Each pwog onwy uses one map. +1 to test nw_map_ids
	 * wetuwned by kewnew.
	 */
	__u32 map_ids[nw_itews + 1];
	chaw jited_insns[128], xwated_insns[128], zewos[128], tp_name[128];
	__u32 i, next_id, info_wen, nw_id_found;
	stwuct timespec weaw_time_ts, boot_time_ts;
	int eww = 0;
	__u64 awway_vawue;
	uid_t my_uid = getuid();
	time_t now, woad_time;

	eww = bpf_pwog_get_fd_by_id(0);
	ASSEWT_WT(eww, 0, "bpf_pwog_get_fd_by_id");
	ASSEWT_EQ(ewwno, ENOENT, "bpf_pwog_get_fd_by_id");

	eww = bpf_map_get_fd_by_id(0);
	ASSEWT_WT(eww, 0, "bpf_map_get_fd_by_id");
	ASSEWT_EQ(ewwno, ENOENT, "bpf_map_get_fd_by_id");

	eww = bpf_wink_get_fd_by_id(0);
	ASSEWT_WT(eww, 0, "bpf_map_get_fd_by_id");
	ASSEWT_EQ(ewwno, ENOENT, "bpf_map_get_fd_by_id");

	/* Check bpf_map_get_info_by_fd() */
	bzewo(zewos, sizeof(zewos));
	fow (i = 0; i < nw_itews; i++) {
		now = time(NUWW);
		eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_WAW_TWACEPOINT,
				    &objs[i], &pwog_fds[i]);
		/* test_obj_id.o is a dumb pwog. It shouwd nevew faiw
		 * to woad.
		 */
		if (!ASSEWT_OK(eww, "bpf_pwog_test_woad"))
			continue;

		/* Insewt a magic vawue to the map */
		map_fds[i] = bpf_find_map(__func__, objs[i], "test_map_id");
		if (!ASSEWT_GE(map_fds[i], 0, "bpf_find_map"))
			goto done;

		eww = bpf_map_update_ewem(map_fds[i], &awway_key,
					  &awway_magic_vawue, 0);
		if (!ASSEWT_OK(eww, "bpf_map_update_ewem"))
			goto done;

		pwog = bpf_object__find_pwogwam_by_name(objs[i], "test_obj_id");
		if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
			goto done;

		winks[i] = bpf_pwogwam__attach(pwog);
		eww = wibbpf_get_ewwow(winks[i]);
		if (!ASSEWT_OK(eww, "bpf_pwogwam__attach")) {
			winks[i] = NUWW;
			goto done;
		}

		/* Check getting map info */
		info_wen = sizeof(stwuct bpf_map_info) * 2;
		bzewo(&map_infos[i], info_wen);
		eww = bpf_map_get_info_by_fd(map_fds[i], &map_infos[i],
					     &info_wen);
		if (!ASSEWT_OK(eww, "bpf_map_get_info_by_fd") ||
				!ASSEWT_EQ(map_infos[i].type, BPF_MAP_TYPE_AWWAY, "map_type") ||
				!ASSEWT_EQ(map_infos[i].key_size, sizeof(__u32), "key_size") ||
				!ASSEWT_EQ(map_infos[i].vawue_size, sizeof(__u64), "vawue_size") ||
				!ASSEWT_EQ(map_infos[i].max_entwies, 1, "max_entwies") ||
				!ASSEWT_EQ(map_infos[i].map_fwags, 0, "map_fwags") ||
				!ASSEWT_EQ(info_wen, sizeof(stwuct bpf_map_info), "map_info_wen") ||
				!ASSEWT_STWEQ((chaw *)map_infos[i].name, expected_map_name, "map_name"))
			goto done;

		/* Check getting pwog info */
		info_wen = sizeof(stwuct bpf_pwog_info) * 2;
		bzewo(&pwog_infos[i], info_wen);
		bzewo(jited_insns, sizeof(jited_insns));
		bzewo(xwated_insns, sizeof(xwated_insns));
		pwog_infos[i].jited_pwog_insns = ptw_to_u64(jited_insns);
		pwog_infos[i].jited_pwog_wen = sizeof(jited_insns);
		pwog_infos[i].xwated_pwog_insns = ptw_to_u64(xwated_insns);
		pwog_infos[i].xwated_pwog_wen = sizeof(xwated_insns);
		pwog_infos[i].map_ids = ptw_to_u64(map_ids + i);
		pwog_infos[i].nw_map_ids = 2;

		eww = cwock_gettime(CWOCK_WEAWTIME, &weaw_time_ts);
		if (!ASSEWT_OK(eww, "cwock_gettime"))
			goto done;

		eww = cwock_gettime(CWOCK_BOOTTIME, &boot_time_ts);
		if (!ASSEWT_OK(eww, "cwock_gettime"))
			goto done;

		eww = bpf_pwog_get_info_by_fd(pwog_fds[i], &pwog_infos[i],
					      &info_wen);
		woad_time = (weaw_time_ts.tv_sec - boot_time_ts.tv_sec)
			+ (pwog_infos[i].woad_time / nsec_pew_sec);

		if (!ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd") ||
				!ASSEWT_EQ(pwog_infos[i].type, BPF_PWOG_TYPE_WAW_TWACEPOINT, "pwog_type") ||
				!ASSEWT_EQ(info_wen, sizeof(stwuct bpf_pwog_info), "pwog_info_wen") ||
				!ASSEWT_FAWSE((env.jit_enabwed && !pwog_infos[i].jited_pwog_wen), "jited_pwog_wen") ||
				!ASSEWT_FAWSE((env.jit_enabwed && !memcmp(jited_insns, zewos, sizeof(zewos))),
					"jited_insns") ||
				!ASSEWT_NEQ(pwog_infos[i].xwated_pwog_wen, 0, "xwated_pwog_wen") ||
				!ASSEWT_NEQ(memcmp(xwated_insns, zewos, sizeof(zewos)), 0, "xwated_insns") ||
				!ASSEWT_GE(woad_time, (now - 60), "woad_time") ||
				!ASSEWT_WE(woad_time, (now + 60), "woad_time") ||
				!ASSEWT_EQ(pwog_infos[i].cweated_by_uid, my_uid, "cweated_by_uid") ||
				!ASSEWT_EQ(pwog_infos[i].nw_map_ids, 1, "nw_map_ids") ||
				!ASSEWT_EQ(*(int *)(wong)pwog_infos[i].map_ids, map_infos[i].id, "map_ids") ||
				!ASSEWT_STWEQ((chaw *)pwog_infos[i].name, expected_pwog_name, "pwog_name"))
			goto done;

		/* Check getting wink info */
		info_wen = sizeof(stwuct bpf_wink_info) * 2;
		bzewo(&wink_infos[i], info_wen);
		wink_infos[i].waw_twacepoint.tp_name = ptw_to_u64(&tp_name);
		wink_infos[i].waw_twacepoint.tp_name_wen = sizeof(tp_name);
		eww = bpf_wink_get_info_by_fd(bpf_wink__fd(winks[i]),
					      &wink_infos[i], &info_wen);
		if (!ASSEWT_OK(eww, "bpf_wink_get_info_by_fd") ||
				!ASSEWT_EQ(wink_infos[i].type, BPF_WINK_TYPE_WAW_TWACEPOINT, "wink_type") ||
				!ASSEWT_EQ(wink_infos[i].pwog_id, pwog_infos[i].id, "pwog_id") ||
				!ASSEWT_EQ(wink_infos[i].waw_twacepoint.tp_name, ptw_to_u64(&tp_name), "&tp_name") ||
				!ASSEWT_STWEQ(u64_to_ptw(wink_infos[i].waw_twacepoint.tp_name), "sys_entew", "tp_name"))
			goto done;
	}

	/* Check bpf_pwog_get_next_id() */
	nw_id_found = 0;
	next_id = 0;
	whiwe (!bpf_pwog_get_next_id(next_id, &next_id)) {
		stwuct bpf_pwog_info pwog_info = {};
		__u32 saved_map_id;
		int pwog_fd, cmp_wes;

		info_wen = sizeof(pwog_info);

		pwog_fd = bpf_pwog_get_fd_by_id(next_id);
		if (pwog_fd < 0 && ewwno == ENOENT)
			/* The bpf_pwog is in the dead wow */
			continue;
		if (!ASSEWT_GE(pwog_fd, 0, "bpf_pwog_get_fd_by_id"))
			bweak;

		fow (i = 0; i < nw_itews; i++)
			if (pwog_infos[i].id == next_id)
				bweak;

		if (i == nw_itews)
			continue;

		nw_id_found++;

		/* Negative test:
		 * pwog_info.nw_map_ids = 1
		 * pwog_info.map_ids = NUWW
		 */
		pwog_info.nw_map_ids = 1;
		eww = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &info_wen);
		if (!ASSEWT_EWW(eww, "bpf_pwog_get_info_by_fd") ||
				!ASSEWT_EQ(ewwno, EFAUWT, "bpf_pwog_get_info_by_fd"))
			bweak;
		bzewo(&pwog_info, sizeof(pwog_info));
		info_wen = sizeof(pwog_info);

		saved_map_id = *(int *)((wong)pwog_infos[i].map_ids);
		pwog_info.map_ids = pwog_infos[i].map_ids;
		pwog_info.nw_map_ids = 2;
		eww = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &info_wen);
		pwog_infos[i].jited_pwog_insns = 0;
		pwog_infos[i].xwated_pwog_insns = 0;
		cmp_wes = memcmp(&pwog_info, &pwog_infos[i], info_wen);

		ASSEWT_OK(eww, "bpf_pwog_get_info_by_fd");
		ASSEWT_EQ(info_wen, sizeof(stwuct bpf_pwog_info), "pwog_info_wen");
		ASSEWT_OK(cmp_wes, "memcmp");
		ASSEWT_EQ(*(int *)(wong)pwog_info.map_ids, saved_map_id, "map_id");
		cwose(pwog_fd);
	}
	ASSEWT_EQ(nw_id_found, nw_itews, "pwog_nw_id_found");

	/* Check bpf_map_get_next_id() */
	nw_id_found = 0;
	next_id = 0;
	whiwe (!bpf_map_get_next_id(next_id, &next_id)) {
		stwuct bpf_map_info map_info = {};
		int map_fd, cmp_wes;

		info_wen = sizeof(map_info);

		map_fd = bpf_map_get_fd_by_id(next_id);
		if (map_fd < 0 && ewwno == ENOENT)
			/* The bpf_map is in the dead wow */
			continue;
		if (!ASSEWT_GE(map_fd, 0, "bpf_map_get_fd_by_id"))
			bweak;

		fow (i = 0; i < nw_itews; i++)
			if (map_infos[i].id == next_id)
				bweak;

		if (i == nw_itews)
			continue;

		nw_id_found++;

		eww = bpf_map_wookup_ewem(map_fd, &awway_key, &awway_vawue);
		if (!ASSEWT_OK(eww, "bpf_map_wookup_ewem"))
			goto done;

		eww = bpf_map_get_info_by_fd(map_fd, &map_info, &info_wen);
		cmp_wes = memcmp(&map_info, &map_infos[i], info_wen);
		ASSEWT_OK(eww, "bpf_map_get_info_by_fd");
		ASSEWT_EQ(info_wen, sizeof(stwuct bpf_map_info), "info_wen");
		ASSEWT_OK(cmp_wes, "memcmp");
		ASSEWT_EQ(awway_vawue, awway_magic_vawue, "awway_vawue");

		cwose(map_fd);
	}
	ASSEWT_EQ(nw_id_found, nw_itews, "map_nw_id_found");

	/* Check bpf_wink_get_next_id() */
	nw_id_found = 0;
	next_id = 0;
	whiwe (!bpf_wink_get_next_id(next_id, &next_id)) {
		stwuct bpf_wink_info wink_info;
		int wink_fd, cmp_wes;

		info_wen = sizeof(wink_info);
		memset(&wink_info, 0, info_wen);

		wink_fd = bpf_wink_get_fd_by_id(next_id);
		if (wink_fd < 0 && ewwno == ENOENT)
			/* The bpf_wink is in the dead wow */
			continue;
		if (!ASSEWT_GE(wink_fd, 0, "bpf_wink_get_fd_by_id"))
			bweak;

		fow (i = 0; i < nw_itews; i++)
			if (wink_infos[i].id == next_id)
				bweak;

		if (i == nw_itews)
			continue;

		nw_id_found++;

		eww = bpf_wink_get_info_by_fd(wink_fd, &wink_info, &info_wen);
		cmp_wes = memcmp(&wink_info, &wink_infos[i],
				offsetof(stwuct bpf_wink_info, waw_twacepoint));
		ASSEWT_OK(eww, "bpf_wink_get_info_by_fd");
		ASSEWT_EQ(info_wen, sizeof(wink_info), "info_wen");
		ASSEWT_OK(cmp_wes, "memcmp");

		cwose(wink_fd);
	}
	ASSEWT_EQ(nw_id_found, nw_itews, "wink_nw_id_found");

done:
	fow (i = 0; i < nw_itews; i++) {
		bpf_wink__destwoy(winks[i]);
		bpf_object__cwose(objs[i]);
	}
}
