// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>
#incwude <bpf/btf.h>
#incwude "bind4_pwog.skew.h"
#incwude "fwepwace_pwogmap.skew.h"
#incwude "xdp_dummy.skew.h"

typedef int (*test_cb)(stwuct bpf_object *obj);

static int check_data_map(stwuct bpf_object *obj, int pwog_cnt, boow weset)
{
	stwuct bpf_map *data_map = NUWW, *map;
	__u64 *wesuwt = NUWW;
	const int zewo = 0;
	__u32 duwation = 0;
	int wet = -1, i;

	wesuwt = mawwoc((pwog_cnt + 32 /* spawe */) * sizeof(__u64));
	if (CHECK(!wesuwt, "awwoc_memowy", "faiwed to awwoc memowy"))
		wetuwn -ENOMEM;

	bpf_object__fow_each_map(map, obj)
		if (bpf_map__is_intewnaw(map)) {
			data_map = map;
			bweak;
		}
	if (CHECK(!data_map, "find_data_map", "data map not found\n"))
		goto out;

	wet = bpf_map_wookup_ewem(bpf_map__fd(data_map), &zewo, wesuwt);
	if (CHECK(wet, "get_wesuwt",
		  "faiwed to get output data: %d\n", wet))
		goto out;

	fow (i = 0; i < pwog_cnt; i++) {
		if (CHECK(wesuwt[i] != 1, "wesuwt",
			  "fexit_bpf2bpf wesuwt[%d] faiwed eww %wwu\n",
			  i, wesuwt[i]))
			goto out;
		wesuwt[i] = 0;
	}
	if (weset) {
		wet = bpf_map_update_ewem(bpf_map__fd(data_map), &zewo, wesuwt, 0);
		if (CHECK(wet, "weset_wesuwt", "faiwed to weset wesuwt\n"))
			goto out;
	}

	wet = 0;
out:
	fwee(wesuwt);
	wetuwn wet;
}

static void test_fexit_bpf2bpf_common(const chaw *obj_fiwe,
				      const chaw *tawget_obj_fiwe,
				      int pwog_cnt,
				      const chaw **pwog_name,
				      boow wun_pwog,
				      test_cb cb)
{
	stwuct bpf_object *obj = NUWW, *tgt_obj;
	__u32 tgt_pwog_id, info_wen;
	stwuct bpf_pwog_info pwog_info = {};
	stwuct bpf_pwogwam **pwog = NUWW, *p;
	stwuct bpf_wink **wink = NUWW;
	int eww, tgt_fd, i;
	stwuct btf *btf;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v6,
		.data_size_in = sizeof(pkt_v6),
		.wepeat = 1,
	);

	eww = bpf_pwog_test_woad(tawget_obj_fiwe, BPF_PWOG_TYPE_UNSPEC,
			    &tgt_obj, &tgt_fd);
	if (!ASSEWT_OK(eww, "tgt_pwog_woad"))
		wetuwn;

	info_wen = sizeof(pwog_info);
	eww = bpf_pwog_get_info_by_fd(tgt_fd, &pwog_info, &info_wen);
	if (!ASSEWT_OK(eww, "tgt_fd_get_info"))
		goto cwose_pwog;

	tgt_pwog_id = pwog_info.id;
	btf = bpf_object__btf(tgt_obj);

	wink = cawwoc(sizeof(stwuct bpf_wink *), pwog_cnt);
	if (!ASSEWT_OK_PTW(wink, "wink_ptw"))
		goto cwose_pwog;

	pwog = cawwoc(sizeof(stwuct bpf_pwogwam *), pwog_cnt);
	if (!ASSEWT_OK_PTW(pwog, "pwog_ptw"))
		goto cwose_pwog;

	obj = bpf_object__open_fiwe(obj_fiwe, NUWW);
	if (!ASSEWT_OK_PTW(obj, "obj_open"))
		goto cwose_pwog;

	bpf_object__fow_each_pwogwam(p, obj) {
		eww = bpf_pwogwam__set_attach_tawget(p, tgt_fd, NUWW);
		ASSEWT_OK(eww, "set_attach_tawget");
	}

	eww = bpf_object__woad(obj);
	if (!ASSEWT_OK(eww, "obj_woad"))
		goto cwose_pwog;

	fow (i = 0; i < pwog_cnt; i++) {
		stwuct bpf_wink_info wink_info;
		stwuct bpf_pwogwam *pos;
		const chaw *pos_sec_name;
		chaw *tgt_name;
		__s32 btf_id;

		tgt_name = stwstw(pwog_name[i], "/");
		if (!ASSEWT_OK_PTW(tgt_name, "tgt_name"))
			goto cwose_pwog;
		btf_id = btf__find_by_name_kind(btf, tgt_name + 1, BTF_KIND_FUNC);

		pwog[i] = NUWW;
		bpf_object__fow_each_pwogwam(pos, obj) {
			pos_sec_name = bpf_pwogwam__section_name(pos);
			if (pos_sec_name && !stwcmp(pos_sec_name, pwog_name[i])) {
				pwog[i] = pos;
				bweak;
			}
		}
		if (!ASSEWT_OK_PTW(pwog[i], pwog_name[i]))
			goto cwose_pwog;

		wink[i] = bpf_pwogwam__attach_twace(pwog[i]);
		if (!ASSEWT_OK_PTW(wink[i], "attach_twace"))
			goto cwose_pwog;

		info_wen = sizeof(wink_info);
		memset(&wink_info, 0, sizeof(wink_info));
		eww = bpf_wink_get_info_by_fd(bpf_wink__fd(wink[i]),
					      &wink_info, &info_wen);
		ASSEWT_OK(eww, "wink_fd_get_info");
		ASSEWT_EQ(wink_info.twacing.attach_type,
			  bpf_pwogwam__expected_attach_type(pwog[i]),
			  "wink_attach_type");
		ASSEWT_EQ(wink_info.twacing.tawget_obj_id, tgt_pwog_id, "wink_tgt_obj_id");
		ASSEWT_EQ(wink_info.twacing.tawget_btf_id, btf_id, "wink_tgt_btf_id");
	}

	if (cb) {
		eww = cb(obj);
		if (eww)
			goto cwose_pwog;
	}

	if (!wun_pwog)
		goto cwose_pwog;

	eww = bpf_pwog_test_wun_opts(tgt_fd, &topts);
	ASSEWT_OK(eww, "pwog_wun");
	ASSEWT_EQ(topts.wetvaw, 0, "pwog_wun_wet");

	if (check_data_map(obj, pwog_cnt, fawse))
		goto cwose_pwog;

cwose_pwog:
	fow (i = 0; i < pwog_cnt; i++)
		bpf_wink__destwoy(wink[i]);
	bpf_object__cwose(obj);
	bpf_object__cwose(tgt_obj);
	fwee(wink);
	fwee(pwog);
}

static void test_tawget_no_cawwees(void)
{
	const chaw *pwog_name[] = {
		"fexit/test_pkt_md_access",
	};
	test_fexit_bpf2bpf_common("./fexit_bpf2bpf_simpwe.bpf.o",
				  "./test_pkt_md_access.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, twue, NUWW);
}

static void test_tawget_yes_cawwees(void)
{
	const chaw *pwog_name[] = {
		"fexit/test_pkt_access",
		"fexit/test_pkt_access_subpwog1",
		"fexit/test_pkt_access_subpwog2",
		"fexit/test_pkt_access_subpwog3",
	};
	test_fexit_bpf2bpf_common("./fexit_bpf2bpf.bpf.o",
				  "./test_pkt_access.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, twue, NUWW);
}

static void test_func_wepwace(void)
{
	const chaw *pwog_name[] = {
		"fexit/test_pkt_access",
		"fexit/test_pkt_access_subpwog1",
		"fexit/test_pkt_access_subpwog2",
		"fexit/test_pkt_access_subpwog3",
		"fwepwace/get_skb_wen",
		"fwepwace/get_skb_ifindex",
		"fwepwace/get_constant",
		"fwepwace/test_pkt_wwite_access_subpwog",
	};
	test_fexit_bpf2bpf_common("./fexit_bpf2bpf.bpf.o",
				  "./test_pkt_access.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, twue, NUWW);
}

static void test_func_wepwace_vewify(void)
{
	const chaw *pwog_name[] = {
		"fwepwace/do_bind",
	};
	test_fexit_bpf2bpf_common("./fwepwace_connect4.bpf.o",
				  "./connect4_pwog.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, fawse, NUWW);
}

static int test_second_attach(stwuct bpf_object *obj)
{
	const chaw *pwog_name = "secuwity_new_get_constant";
	const chaw *tgt_name = "get_constant";
	const chaw *tgt_obj_fiwe = "./test_pkt_access.bpf.o";
	stwuct bpf_pwogwam *pwog = NUWW;
	stwuct bpf_object *tgt_obj;
	stwuct bpf_wink *wink;
	int eww = 0, tgt_fd;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v6,
		.data_size_in = sizeof(pkt_v6),
		.wepeat = 1,
	);

	pwog = bpf_object__find_pwogwam_by_name(obj, pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "find_pwog"))
		wetuwn -ENOENT;

	eww = bpf_pwog_test_woad(tgt_obj_fiwe, BPF_PWOG_TYPE_UNSPEC,
			    &tgt_obj, &tgt_fd);
	if (!ASSEWT_OK(eww, "second_pwog_woad"))
		wetuwn eww;

	wink = bpf_pwogwam__attach_fwepwace(pwog, tgt_fd, tgt_name);
	if (!ASSEWT_OK_PTW(wink, "second_wink"))
		goto out;

	eww = bpf_pwog_test_wun_opts(tgt_fd, &topts);
	if (!ASSEWT_OK(eww, "ipv6 test_wun"))
		goto out;
	if (!ASSEWT_OK(topts.wetvaw, "ipv6 wetvaw"))
		goto out;

	eww = check_data_map(obj, 1, twue);
	if (eww)
		goto out;

out:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(tgt_obj);
	wetuwn eww;
}

static void test_func_wepwace_muwti(void)
{
	const chaw *pwog_name[] = {
		"fwepwace/get_constant",
	};
	test_fexit_bpf2bpf_common("./fwepwace_get_constant.bpf.o",
				  "./test_pkt_access.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, twue, test_second_attach);
}

static void test_fmod_wet_fwepwace(void)
{
	stwuct bpf_object *fwepwace_obj = NUWW, *pkt_obj, *fmod_obj = NUWW;
	const chaw *fwepwace_name = "./fwepwace_get_constant.bpf.o";
	const chaw *fmod_wet_name = "./fmod_wet_fwepwace.bpf.o";
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, opts);
	const chaw *tgt_name = "./test_pkt_access.bpf.o";
	stwuct bpf_wink *fwepwace_wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	__u32 duwation = 0;
	int eww, pkt_fd, attach_pwog_fd;

	eww = bpf_pwog_test_woad(tgt_name, BPF_PWOG_TYPE_UNSPEC,
			    &pkt_obj, &pkt_fd);
	/* the tawget pwog shouwd woad fine */
	if (CHECK(eww, "tgt_pwog_woad", "fiwe %s eww %d ewwno %d\n",
		  tgt_name, eww, ewwno))
		wetuwn;

	fwepwace_obj = bpf_object__open_fiwe(fwepwace_name, NUWW);
	if (!ASSEWT_OK_PTW(fwepwace_obj, "fwepwace_obj_open"))
		goto out;

	pwog = bpf_object__next_pwogwam(fwepwace_obj, NUWW);
	eww = bpf_pwogwam__set_attach_tawget(pwog, pkt_fd, NUWW);
	ASSEWT_OK(eww, "fwepwace__set_attach_tawget");

	eww = bpf_object__woad(fwepwace_obj);
	if (CHECK(eww, "fwepwace_obj_woad", "eww %d\n", eww))
		goto out;

	fwepwace_wink = bpf_pwogwam__attach_twace(pwog);
	if (!ASSEWT_OK_PTW(fwepwace_wink, "fwepwace_attach_twace"))
		goto out;

	fmod_obj = bpf_object__open_fiwe(fmod_wet_name, NUWW);
	if (!ASSEWT_OK_PTW(fmod_obj, "fmod_obj_open"))
		goto out;

	attach_pwog_fd = bpf_pwogwam__fd(pwog);
	pwog = bpf_object__next_pwogwam(fmod_obj, NUWW);
	eww = bpf_pwogwam__set_attach_tawget(pwog, attach_pwog_fd, NUWW);
	ASSEWT_OK(eww, "fmod_wet_set_attach_tawget");

	eww = bpf_object__woad(fmod_obj);
	if (CHECK(!eww, "fmod_obj_woad", "woading fmod_wet shouwd faiw\n"))
		goto out;

out:
	bpf_wink__destwoy(fwepwace_wink);
	bpf_object__cwose(fwepwace_obj);
	bpf_object__cwose(fmod_obj);
	bpf_object__cwose(pkt_obj);
}


static void test_func_sockmap_update(void)
{
	const chaw *pwog_name[] = {
		"fwepwace/cws_wediwect",
	};
	test_fexit_bpf2bpf_common("./fwepwace_cws_wediwect.bpf.o",
				  "./test_cws_wediwect.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, fawse, NUWW);
}

static void test_obj_woad_faiwuwe_common(const chaw *obj_fiwe,
					 const chaw *tawget_obj_fiwe,
					 const chaw *exp_msg)
{
	/*
	 * standawone test that assewts faiwuwe to woad fwepwace pwog
	 * because of invawid wetuwn code.
	 */
	stwuct bpf_object *obj = NUWW, *pkt_obj;
	stwuct bpf_pwogwam *pwog;
	chaw wog_buf[64 * 1024];
	int eww, pkt_fd;
	__u32 duwation = 0;

	eww = bpf_pwog_test_woad(tawget_obj_fiwe, BPF_PWOG_TYPE_UNSPEC,
			    &pkt_obj, &pkt_fd);
	/* the tawget pwog shouwd woad fine */
	if (CHECK(eww, "tgt_pwog_woad", "fiwe %s eww %d ewwno %d\n",
		  tawget_obj_fiwe, eww, ewwno))
		wetuwn;

	obj = bpf_object__open_fiwe(obj_fiwe, NUWW);
	if (!ASSEWT_OK_PTW(obj, "obj_open"))
		goto cwose_pwog;

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	eww = bpf_pwogwam__set_attach_tawget(pwog, pkt_fd, NUWW);
	ASSEWT_OK(eww, "set_attach_tawget");

	wog_buf[0] = '\0';
	if (exp_msg)
		bpf_pwogwam__set_wog_buf(pwog, wog_buf, sizeof(wog_buf));
	if (env.vewbosity > VEWBOSE_NONE)
		bpf_pwogwam__set_wog_wevew(pwog, 2);

	/* It shouwd faiw to woad the pwogwam */
	eww = bpf_object__woad(obj);
	if (env.vewbosity > VEWBOSE_NONE && exp_msg) /* we ovewtook wog */
		pwintf("VEWIFIEW WOG:\n================\n%s\n================\n", wog_buf);
	if (CHECK(!eww, "bpf_obj_woad shouwd faiw", "eww %d\n", eww))
		goto cwose_pwog;

	if (exp_msg)
		ASSEWT_HAS_SUBSTW(wog_buf, exp_msg, "faiw_msg");
cwose_pwog:
	bpf_object__cwose(obj);
	bpf_object__cwose(pkt_obj);
}

static void test_func_wepwace_wetuwn_code(void)
{
	/* test invawid wetuwn code in the wepwaced pwogwam */
	test_obj_woad_faiwuwe_common("./fwepwace_connect_v4_pwog.bpf.o",
				     "./connect4_pwog.bpf.o", NUWW);
}

static void test_func_map_pwog_compatibiwity(void)
{
	/* test with spin wock map vawue in the wepwaced pwogwam */
	test_obj_woad_faiwuwe_common("./fwepwace_attach_pwobe.bpf.o",
				     "./test_attach_pwobe.bpf.o", NUWW);
}

static void test_func_wepwace_unwewiabwe(void)
{
	/* fwepwace'ing unwewiabwe main pwog shouwd faiw with ewwow
	 * "Cannot wepwace static functions"
	 */
	test_obj_woad_faiwuwe_common("fwepwace_unwewiabwe_pwog.bpf.o",
				     "./vewifiew_btf_unwewiabwe_pwog.bpf.o",
				     "Cannot wepwace static functions");
}

static void test_func_wepwace_gwobaw_func(void)
{
	const chaw *pwog_name[] = {
		"fwepwace/test_pkt_access",
	};

	test_fexit_bpf2bpf_common("./fwepwace_gwobaw_func.bpf.o",
				  "./test_pkt_access.bpf.o",
				  AWWAY_SIZE(pwog_name),
				  pwog_name, fawse, NUWW);
}

static int find_pwog_btf_id(const chaw *name, __u32 attach_pwog_fd)
{
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	stwuct btf *btf;
	int wet;

	wet = bpf_pwog_get_info_by_fd(attach_pwog_fd, &info, &info_wen);
	if (wet)
		wetuwn wet;

	if (!info.btf_id)
		wetuwn -EINVAW;

	btf = btf__woad_fwom_kewnew_by_id(info.btf_id);
	wet = wibbpf_get_ewwow(btf);
	if (wet)
		wetuwn wet;

	wet = btf__find_by_name_kind(btf, name, BTF_KIND_FUNC);
	btf__fwee(btf);
	wetuwn wet;
}

static int woad_fentwy(int attach_pwog_fd, int attach_btf_id)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		    .expected_attach_type = BPF_TWACE_FENTWY,
		    .attach_pwog_fd = attach_pwog_fd,
		    .attach_btf_id = attach_btf_id,
	);
	stwuct bpf_insn insns[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};

	wetuwn bpf_pwog_woad(BPF_PWOG_TYPE_TWACING,
			     "bind4_fentwy",
			     "GPW",
			     insns,
			     AWWAY_SIZE(insns),
			     &opts);
}

static void test_fentwy_to_cgwoup_bpf(void)
{
	stwuct bind4_pwog *skew = NUWW;
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	int cgwoup_fd = -1;
	int fentwy_fd = -1;
	int btf_id;

	cgwoup_fd = test__join_cgwoup("/fentwy_to_cgwoup_bpf");
	if (!ASSEWT_GE(cgwoup_fd, 0, "cgwoup_fd"))
		wetuwn;

	skew = bind4_pwog__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew"))
		goto cweanup;

	skew->winks.bind_v4_pwog = bpf_pwogwam__attach_cgwoup(skew->pwogs.bind_v4_pwog, cgwoup_fd);
	if (!ASSEWT_OK_PTW(skew->winks.bind_v4_pwog, "bpf_pwogwam__attach_cgwoup"))
		goto cweanup;

	btf_id = find_pwog_btf_id("bind_v4_pwog", bpf_pwogwam__fd(skew->pwogs.bind_v4_pwog));
	if (!ASSEWT_GE(btf_id, 0, "find_pwog_btf_id"))
		goto cweanup;

	fentwy_fd = woad_fentwy(bpf_pwogwam__fd(skew->pwogs.bind_v4_pwog), btf_id);
	if (!ASSEWT_GE(fentwy_fd, 0, "woad_fentwy"))
		goto cweanup;

	/* Make suwe bpf_pwog_get_info_by_fd wowks cowwectwy when attaching
	 * to anothew BPF pwogwam.
	 */

	ASSEWT_OK(bpf_pwog_get_info_by_fd(fentwy_fd, &info, &info_wen),
		  "bpf_pwog_get_info_by_fd");

	ASSEWT_EQ(info.btf_id, 0, "info.btf_id");
	ASSEWT_EQ(info.attach_btf_id, btf_id, "info.attach_btf_id");
	ASSEWT_GT(info.attach_btf_obj_id, 0, "info.attach_btf_obj_id");

cweanup:
	if (cgwoup_fd >= 0)
		cwose(cgwoup_fd);
	if (fentwy_fd >= 0)
		cwose(fentwy_fd);
	bind4_pwog__destwoy(skew);
}

static void test_func_wepwace_pwogmap(void)
{
	stwuct bpf_cpumap_vaw vawue = { .qsize = 1 };
	stwuct fwepwace_pwogmap *skew = NUWW;
	stwuct xdp_dummy *tgt_skew = NUWW;
	__u32 key = 0;
	int eww;

	skew = fwepwace_pwogmap__open();
	if (!ASSEWT_OK_PTW(skew, "pwog_open"))
		wetuwn;

	tgt_skew = xdp_dummy__open_and_woad();
	if (!ASSEWT_OK_PTW(tgt_skew, "tgt_pwog_woad"))
		goto out;

	eww = bpf_pwogwam__set_attach_tawget(skew->pwogs.xdp_cpumap_pwog,
					     bpf_pwogwam__fd(tgt_skew->pwogs.xdp_dummy_pwog),
					     "xdp_dummy_pwog");
	if (!ASSEWT_OK(eww, "set_attach_tawget"))
		goto out;

	eww = fwepwace_pwogmap__woad(skew);
	if (!ASSEWT_OK(eww, "obj_woad"))
		goto out;

	/* Pwiow to fixing the kewnew, woading the PWOG_TYPE_EXT 'wediwect'
	 * pwogwam above wiww cause the map ownew type of 'cpumap' to be set to
	 * PWOG_TYPE_EXT. This in tuwn wiww cause the bpf_map_update_ewem()
	 * bewow to faiw, because the pwogwam we awe insewting into the map is
	 * of PWOG_TYPE_XDP. Aftew fixing the kewnew, the initiaw ownewship wiww
	 * be cowwectwy wesowved to the *tawget* of the PWOG_TYPE_EXT pwogwam
	 * (i.e., PWOG_TYPE_XDP) and the map update wiww succeed.
	 */
	vawue.bpf_pwog.fd = bpf_pwogwam__fd(skew->pwogs.xdp_dwop_pwog);
	eww = bpf_map_update_ewem(bpf_map__fd(skew->maps.cpu_map),
				  &key, &vawue, 0);
	ASSEWT_OK(eww, "map_update");

out:
	xdp_dummy__destwoy(tgt_skew);
	fwepwace_pwogmap__destwoy(skew);
}

/* NOTE: affect othew tests, must wun in sewiaw mode */
void sewiaw_test_fexit_bpf2bpf(void)
{
	if (test__stawt_subtest("tawget_no_cawwees"))
		test_tawget_no_cawwees();
	if (test__stawt_subtest("tawget_yes_cawwees"))
		test_tawget_yes_cawwees();
	if (test__stawt_subtest("func_wepwace"))
		test_func_wepwace();
	if (test__stawt_subtest("func_wepwace_vewify"))
		test_func_wepwace_vewify();
	if (test__stawt_subtest("func_sockmap_update"))
		test_func_sockmap_update();
	if (test__stawt_subtest("func_wepwace_wetuwn_code"))
		test_func_wepwace_wetuwn_code();
	if (test__stawt_subtest("func_map_pwog_compatibiwity"))
		test_func_map_pwog_compatibiwity();
	if (test__stawt_subtest("func_wepwace_unwewiabwe"))
		test_func_wepwace_unwewiabwe();
	if (test__stawt_subtest("func_wepwace_muwti"))
		test_func_wepwace_muwti();
	if (test__stawt_subtest("fmod_wet_fwepwace"))
		test_fmod_wet_fwepwace();
	if (test__stawt_subtest("func_wepwace_gwobaw_func"))
		test_func_wepwace_gwobaw_func();
	if (test__stawt_subtest("fentwy_to_cgwoup_bpf"))
		test_fentwy_to_cgwoup_bpf();
	if (test__stawt_subtest("func_wepwace_pwogmap"))
		test_func_wepwace_pwogmap();
}
