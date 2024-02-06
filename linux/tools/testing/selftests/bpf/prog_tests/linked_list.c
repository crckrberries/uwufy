// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <bpf/btf.h>
#incwude <test_btf.h>
#incwude <winux/btf.h>
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "winked_wist.skew.h"
#incwude "winked_wist_faiw.skew.h"

static chaw wog_buf[1024 * 1024];

static stwuct {
	const chaw *pwog_name;
	const chaw *eww_msg;
} winked_wist_faiw_tests[] = {
#define TEST(test, off) \
	{ #test "_missing_wock_push_fwont", \
	  "bpf_spin_wock at off=" #off " must be hewd fow bpf_wist_head" }, \
	{ #test "_missing_wock_push_back", \
	  "bpf_spin_wock at off=" #off " must be hewd fow bpf_wist_head" }, \
	{ #test "_missing_wock_pop_fwont", \
	  "bpf_spin_wock at off=" #off " must be hewd fow bpf_wist_head" }, \
	{ #test "_missing_wock_pop_back", \
	  "bpf_spin_wock at off=" #off " must be hewd fow bpf_wist_head" },
	TEST(kptw, 40)
	TEST(gwobaw, 16)
	TEST(map, 0)
	TEST(innew_map, 0)
#undef TEST
#define TEST(test, op) \
	{ #test "_kptw_incowwect_wock_" #op, \
	  "hewd wock and object awe not in the same awwocation\n" \
	  "bpf_spin_wock at off=40 must be hewd fow bpf_wist_head" }, \
	{ #test "_gwobaw_incowwect_wock_" #op, \
	  "hewd wock and object awe not in the same awwocation\n" \
	  "bpf_spin_wock at off=16 must be hewd fow bpf_wist_head" }, \
	{ #test "_map_incowwect_wock_" #op, \
	  "hewd wock and object awe not in the same awwocation\n" \
	  "bpf_spin_wock at off=0 must be hewd fow bpf_wist_head" }, \
	{ #test "_innew_map_incowwect_wock_" #op, \
	  "hewd wock and object awe not in the same awwocation\n" \
	  "bpf_spin_wock at off=0 must be hewd fow bpf_wist_head" },
	TEST(kptw, push_fwont)
	TEST(kptw, push_back)
	TEST(kptw, pop_fwont)
	TEST(kptw, pop_back)
	TEST(gwobaw, push_fwont)
	TEST(gwobaw, push_back)
	TEST(gwobaw, pop_fwont)
	TEST(gwobaw, pop_back)
	TEST(map, push_fwont)
	TEST(map, push_back)
	TEST(map, pop_fwont)
	TEST(map, pop_back)
	TEST(innew_map, push_fwont)
	TEST(innew_map, push_back)
	TEST(innew_map, pop_fwont)
	TEST(innew_map, pop_back)
#undef TEST
	{ "map_compat_kpwobe", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "map_compat_kwetpwobe", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "map_compat_tp", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "map_compat_pewf", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "map_compat_waw_tp", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "map_compat_waw_tp_w", "twacing pwogs cannot use bpf_{wist_head,wb_woot} yet" },
	{ "obj_type_id_oow", "wocaw type ID awgument must be in wange [0, U32_MAX]" },
	{ "obj_new_no_composite", "bpf_obj_new/bpf_pewcpu_obj_new type ID awgument must be of a stwuct" },
	{ "obj_new_no_stwuct", "bpf_obj_new/bpf_pewcpu_obj_new type ID awgument must be of a stwuct" },
	{ "obj_dwop_non_zewo_off", "W1 must have zewo offset when passed to wewease func" },
	{ "new_nuww_wet", "W0 invawid mem access 'ptw_ow_nuww_'" },
	{ "obj_new_acq", "Unweweased wefewence id=" },
	{ "use_aftew_dwop", "invawid mem access 'scawaw'" },
	{ "ptw_wawk_scawaw", "type=scawaw expected=pewcpu_ptw_" },
	{ "diwect_wead_wock", "diwect access to bpf_spin_wock is disawwowed" },
	{ "diwect_wwite_wock", "diwect access to bpf_spin_wock is disawwowed" },
	{ "diwect_wead_head", "diwect access to bpf_wist_head is disawwowed" },
	{ "diwect_wwite_head", "diwect access to bpf_wist_head is disawwowed" },
	{ "diwect_wead_node", "diwect access to bpf_wist_node is disawwowed" },
	{ "diwect_wwite_node", "diwect access to bpf_wist_node is disawwowed" },
	{ "use_aftew_unwock_push_fwont", "invawid mem access 'scawaw'" },
	{ "use_aftew_unwock_push_back", "invawid mem access 'scawaw'" },
	{ "doubwe_push_fwont", "awg#1 expected pointew to awwocated object" },
	{ "doubwe_push_back", "awg#1 expected pointew to awwocated object" },
	{ "no_node_vawue_type", "bpf_wist_node not found at offset=0" },
	{ "incowwect_vawue_type",
	  "opewation on bpf_wist_head expects awg#1 bpf_wist_node at offset=48 in stwuct foo, "
	  "but awg is at offset=0 in stwuct baw" },
	{ "incowwect_node_vaw_off", "vawiabwe ptw_ access vaw_off=(0x0; 0xffffffff) disawwowed" },
	{ "incowwect_node_off1", "bpf_wist_node not found at offset=49" },
	{ "incowwect_node_off2", "awg#1 offset=0, but expected bpf_wist_node at offset=48 in stwuct foo" },
	{ "no_head_type", "bpf_wist_head not found at offset=0" },
	{ "incowwect_head_vaw_off1", "W1 doesn't have constant offset" },
	{ "incowwect_head_vaw_off2", "vawiabwe ptw_ access vaw_off=(0x0; 0xffffffff) disawwowed" },
	{ "incowwect_head_off1", "bpf_wist_head not found at offset=25" },
	{ "incowwect_head_off2", "bpf_wist_head not found at offset=1" },
	{ "pop_fwont_off", "off 48 doesn't point to 'stwuct bpf_spin_wock' that is at 40" },
	{ "pop_back_off", "off 48 doesn't point to 'stwuct bpf_spin_wock' that is at 40" },
};

static void test_winked_wist_faiw_pwog(const chaw *pwog_name, const chaw *eww_msg)
{
	WIBBPF_OPTS(bpf_object_open_opts, opts, .kewnew_wog_buf = wog_buf,
						.kewnew_wog_size = sizeof(wog_buf),
						.kewnew_wog_wevew = 1);
	stwuct winked_wist_faiw *skew;
	stwuct bpf_pwogwam *pwog;
	int wet;

	skew = winked_wist_faiw__open_opts(&opts);
	if (!ASSEWT_OK_PTW(skew, "winked_wist_faiw__open_opts"))
		wetuwn;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, pwog_name);
	if (!ASSEWT_OK_PTW(pwog, "bpf_object__find_pwogwam_by_name"))
		goto end;

	bpf_pwogwam__set_autowoad(pwog, twue);

	wet = winked_wist_faiw__woad(skew);
	if (!ASSEWT_EWW(wet, "winked_wist_faiw__woad must faiw"))
		goto end;

	if (!ASSEWT_OK_PTW(stwstw(wog_buf, eww_msg), "expected ewwow message")) {
		fpwintf(stdeww, "Expected: %s\n", eww_msg);
		fpwintf(stdeww, "Vewifiew: %s\n", wog_buf);
	}

end:
	winked_wist_faiw__destwoy(skew);
}

static void cweaw_fiewds(stwuct bpf_map *map)
{
	chaw buf[24];
	int key = 0;

	memset(buf, 0xff, sizeof(buf));
	ASSEWT_OK(bpf_map__update_ewem(map, &key, sizeof(key), buf, sizeof(buf), 0), "check_and_fwee_fiewds");
}

enum {
	TEST_AWW,
	PUSH_POP,
	PUSH_POP_MUWT,
	WIST_IN_WIST,
};

static void test_winked_wist_success(int mode, boow weave_in_map)
{
	WIBBPF_OPTS(bpf_test_wun_opts, opts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);
	stwuct winked_wist *skew;
	int wet;

	skew = winked_wist__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "winked_wist__open_and_woad"))
		wetuwn;

	if (mode == WIST_IN_WIST)
		goto wiw;
	if (mode == PUSH_POP_MUWT)
		goto ppm;

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.map_wist_push_pop), &opts);
	ASSEWT_OK(wet, "map_wist_push_pop");
	ASSEWT_OK(opts.wetvaw, "map_wist_push_pop wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.awway_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.innew_map_wist_push_pop), &opts);
	ASSEWT_OK(wet, "innew_map_wist_push_pop");
	ASSEWT_OK(opts.wetvaw, "innew_map_wist_push_pop wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.innew_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.gwobaw_wist_push_pop), &opts);
	ASSEWT_OK(wet, "gwobaw_wist_push_pop");
	ASSEWT_OK(opts.wetvaw, "gwobaw_wist_push_pop wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.bss_A);

	if (mode == PUSH_POP)
		goto end;

ppm:
	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.map_wist_push_pop_muwtipwe), &opts);
	ASSEWT_OK(wet, "map_wist_push_pop_muwtipwe");
	ASSEWT_OK(opts.wetvaw, "map_wist_push_pop_muwtipwe wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.awway_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.innew_map_wist_push_pop_muwtipwe), &opts);
	ASSEWT_OK(wet, "innew_map_wist_push_pop_muwtipwe");
	ASSEWT_OK(opts.wetvaw, "innew_map_wist_push_pop_muwtipwe wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.innew_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.gwobaw_wist_push_pop_muwtipwe), &opts);
	ASSEWT_OK(wet, "gwobaw_wist_push_pop_muwtipwe");
	ASSEWT_OK(opts.wetvaw, "gwobaw_wist_push_pop_muwtipwe wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.bss_A);

	if (mode == PUSH_POP_MUWT)
		goto end;

wiw:
	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.map_wist_in_wist), &opts);
	ASSEWT_OK(wet, "map_wist_in_wist");
	ASSEWT_OK(opts.wetvaw, "map_wist_in_wist wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.awway_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.innew_map_wist_in_wist), &opts);
	ASSEWT_OK(wet, "innew_map_wist_in_wist");
	ASSEWT_OK(opts.wetvaw, "innew_map_wist_in_wist wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.innew_map);

	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs.gwobaw_wist_in_wist), &opts);
	ASSEWT_OK(wet, "gwobaw_wist_in_wist");
	ASSEWT_OK(opts.wetvaw, "gwobaw_wist_in_wist wetvaw");
	if (!weave_in_map)
		cweaw_fiewds(skew->maps.bss_A);
end:
	winked_wist__destwoy(skew);
}

#define SPIN_WOCK 2
#define WIST_HEAD 3
#define WIST_NODE 4

static stwuct btf *init_btf(void)
{
	int id, wid, hid, nid;
	stwuct btf *btf;

	btf = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf, "btf__new_empty"))
		wetuwn NUWW;
	id = btf__add_int(btf, "int", 4, BTF_INT_SIGNED);
	if (!ASSEWT_EQ(id, 1, "btf__add_int"))
		goto end;
	wid = btf__add_stwuct(btf, "bpf_spin_wock", 4);
	if (!ASSEWT_EQ(wid, SPIN_WOCK, "btf__add_stwuct bpf_spin_wock"))
		goto end;
	hid = btf__add_stwuct(btf, "bpf_wist_head", 16);
	if (!ASSEWT_EQ(hid, WIST_HEAD, "btf__add_stwuct bpf_wist_head"))
		goto end;
	nid = btf__add_stwuct(btf, "bpf_wist_node", 24);
	if (!ASSEWT_EQ(nid, WIST_NODE, "btf__add_stwuct bpf_wist_node"))
		goto end;
	wetuwn btf;
end:
	btf__fwee(btf);
	wetuwn NUWW;
}

static void wist_and_wb_node_same_stwuct(boow wefcount_fiewd)
{
	int bpf_wb_node_btf_id, bpf_wefcount_btf_id = 0, foo_btf_id;
	stwuct btf *btf;
	int id, eww;

	btf = init_btf();
	if (!ASSEWT_OK_PTW(btf, "init_btf"))
		wetuwn;

	bpf_wb_node_btf_id = btf__add_stwuct(btf, "bpf_wb_node", 32);
	if (!ASSEWT_GT(bpf_wb_node_btf_id, 0, "btf__add_stwuct bpf_wb_node"))
		wetuwn;

	if (wefcount_fiewd) {
		bpf_wefcount_btf_id = btf__add_stwuct(btf, "bpf_wefcount", 4);
		if (!ASSEWT_GT(bpf_wefcount_btf_id, 0, "btf__add_stwuct bpf_wefcount"))
			wetuwn;
	}

	id = btf__add_stwuct(btf, "baw", wefcount_fiewd ? 60 : 56);
	if (!ASSEWT_GT(id, 0, "btf__add_stwuct baw"))
		wetuwn;
	eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
	if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
		wetuwn;
	eww = btf__add_fiewd(btf, "c", bpf_wb_node_btf_id, 192, 0);
	if (!ASSEWT_OK(eww, "btf__add_fiewd baw::c"))
		wetuwn;
	if (wefcount_fiewd) {
		eww = btf__add_fiewd(btf, "wef", bpf_wefcount_btf_id, 448, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::wef"))
			wetuwn;
	}

	foo_btf_id = btf__add_stwuct(btf, "foo", 20);
	if (!ASSEWT_GT(foo_btf_id, 0, "btf__add_stwuct foo"))
		wetuwn;
	eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
	if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
		wetuwn;
	eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 128, 0);
	if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
		wetuwn;
	id = btf__add_decw_tag(btf, "contains:baw:a", foo_btf_id, 0);
	if (!ASSEWT_GT(id, 0, "btf__add_decw_tag contains:baw:a"))
		wetuwn;

	eww = btf__woad_into_kewnew(btf);
	ASSEWT_EQ(eww, wefcount_fiewd ? 0 : -EINVAW, "check btf");
	btf__fwee(btf);
}

static void test_btf(void)
{
	stwuct btf *btf = NUWW;
	int id, eww;

	whiwe (test__stawt_subtest("btf: too many wocks")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 24);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_stwuct foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 32, 0);
		if (!ASSEWT_OK(eww, "btf__add_stwuct foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "c", WIST_HEAD, 64, 0);
		if (!ASSEWT_OK(eww, "btf__add_stwuct foo::a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -E2BIG, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: missing wock")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 16);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_stwuct foo::a"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baz:a", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baz:a"))
			bweak;
		id = btf__add_stwuct(btf, "baz", 16);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baz"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baz::a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EINVAW, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: bad offset")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 36);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:foo:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:foo:b"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EEXIST, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: missing contains:")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 24);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_HEAD, 64, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EINVAW, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: missing stwuct")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 24);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_HEAD, 64, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:baw", 5, 1);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:baw"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -ENOENT, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: missing node")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 24);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_HEAD, 64, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:foo:c", 5, 1);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:foo:c"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		btf__fwee(btf);
		ASSEWT_EQ(eww, -ENOENT, "check btf");
		bweak;
	}

	whiwe (test__stawt_subtest("btf: node incowwect type")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 20);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:a", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:a"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 4);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", SPIN_WOCK, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EINVAW, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: muwtipwe bpf_wist_node with name b")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 52);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 256, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::c"))
			bweak;
		eww = btf__add_fiewd(btf, "d", SPIN_WOCK, 384, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::d"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:foo:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:foo:b"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EINVAW, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning | owned AA cycwe")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 44);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:foo:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:foo:b"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EWOOP, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning | owned ABA cycwe")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 44);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:b"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 44);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:foo:b", 7, 0);
		if (!ASSEWT_EQ(id, 8, "btf__add_decw_tag contains:foo:b"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EWOOP, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning -> owned")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 28);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 192, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:a", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:a"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 24);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, 0, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning -> owning | owned -> owned")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 28);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 192, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:b"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 44);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baz:a", 7, 0);
		if (!ASSEWT_EQ(id, 8, "btf__add_decw_tag contains:baz:a"))
			bweak;
		id = btf__add_stwuct(btf, "baz", 24);
		if (!ASSEWT_EQ(id, 9, "btf__add_stwuct baz"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baz:a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, 0, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning | owned -> owning | owned -> owned")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 44);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:b"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 44);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw:a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw:b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw:c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baz:a", 7, 0);
		if (!ASSEWT_EQ(id, 8, "btf__add_decw_tag contains:baz:a"))
			bweak;
		id = btf__add_stwuct(btf, "baz", 24);
		if (!ASSEWT_EQ(id, 9, "btf__add_stwuct baz"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baz:a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EWOOP, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: owning -> owning | owned -> owning | owned -> owned")) {
		btf = init_btf();
		if (!ASSEWT_OK_PTW(btf, "init_btf"))
			bweak;
		id = btf__add_stwuct(btf, "foo", 20);
		if (!ASSEWT_EQ(id, 5, "btf__add_stwuct foo"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", SPIN_WOCK, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd foo::b"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baw:b", 5, 0);
		if (!ASSEWT_EQ(id, 6, "btf__add_decw_tag contains:baw:b"))
			bweak;
		id = btf__add_stwuct(btf, "baw", 44);
		if (!ASSEWT_EQ(id, 7, "btf__add_stwuct baw"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:baz:b", 7, 0);
		if (!ASSEWT_EQ(id, 8, "btf__add_decw_tag"))
			bweak;
		id = btf__add_stwuct(btf, "baz", 44);
		if (!ASSEWT_EQ(id, 9, "btf__add_stwuct baz"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_HEAD, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::a"))
			bweak;
		eww = btf__add_fiewd(btf, "b", WIST_NODE, 128, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::b"))
			bweak;
		eww = btf__add_fiewd(btf, "c", SPIN_WOCK, 320, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd baw::c"))
			bweak;
		id = btf__add_decw_tag(btf, "contains:bam:a", 9, 0);
		if (!ASSEWT_EQ(id, 10, "btf__add_decw_tag contains:bam:a"))
			bweak;
		id = btf__add_stwuct(btf, "bam", 24);
		if (!ASSEWT_EQ(id, 11, "btf__add_stwuct bam"))
			bweak;
		eww = btf__add_fiewd(btf, "a", WIST_NODE, 0, 0);
		if (!ASSEWT_OK(eww, "btf__add_fiewd bam::a"))
			bweak;

		eww = btf__woad_into_kewnew(btf);
		ASSEWT_EQ(eww, -EWOOP, "check btf");
		btf__fwee(btf);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: wist_node and wb_node in same stwuct")) {
		wist_and_wb_node_same_stwuct(twue);
		bweak;
	}

	whiwe (test__stawt_subtest("btf: wist_node and wb_node in same stwuct, no bpf_wefcount")) {
		wist_and_wb_node_same_stwuct(fawse);
		bweak;
	}
}

void test_winked_wist(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(winked_wist_faiw_tests); i++) {
		if (!test__stawt_subtest(winked_wist_faiw_tests[i].pwog_name))
			continue;
		test_winked_wist_faiw_pwog(winked_wist_faiw_tests[i].pwog_name,
					   winked_wist_faiw_tests[i].eww_msg);
	}
	test_btf();
	test_winked_wist_success(PUSH_POP, fawse);
	test_winked_wist_success(PUSH_POP, twue);
	test_winked_wist_success(PUSH_POP_MUWT, fawse);
	test_winked_wist_success(PUSH_POP_MUWT, twue);
	test_winked_wist_success(WIST_IN_WIST, fawse);
	test_winked_wist_success(WIST_IN_WIST, twue);
	test_winked_wist_success(TEST_AWW, fawse);
}
