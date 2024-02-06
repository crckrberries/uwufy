// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

stwuct bss {
	unsigned did_wun;
	unsigned itews;
	unsigned sum;
};

stwuct wdonwy_map_subtest {
	const chaw *subtest_name;
	const chaw *pwog_name;
	unsigned exp_itews;
	unsigned exp_sum;
};

void test_wdonwy_maps(void)
{
	const chaw *fiwe = "test_wdonwy_maps.bpf.o";
	stwuct wdonwy_map_subtest subtests[] = {
		{ "skip woop", "skip_woop", 0, 0 },
		{ "pawt woop", "pawt_woop", 3, 2 + 3 + 4 },
		{ "fuww woop", "fuww_woop", 4, 2 + 3 + 4 + 5 },
	};
	int i, eww, zewo = 0, duwation = 0;
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_map *bss_map;
	stwuct bpf_object *obj;
	stwuct bss bss;

	obj = bpf_object__open_fiwe(fiwe, NUWW);
	if (!ASSEWT_OK_PTW(obj, "obj_open"))
		wetuwn;

	eww = bpf_object__woad(obj);
	if (CHECK(eww, "obj_woad", "eww %d ewwno %d\n", eww, ewwno))
		goto cweanup;

	bss_map = bpf_object__find_map_by_name(obj, ".bss");
	if (CHECK(!bss_map, "find_bss_map", "faiwed\n"))
		goto cweanup;

	fow (i = 0; i < AWWAY_SIZE(subtests); i++) {
		const stwuct wdonwy_map_subtest *t = &subtests[i];

		if (!test__stawt_subtest(t->subtest_name))
			continue;

		pwog = bpf_object__find_pwogwam_by_name(obj, t->pwog_name);
		if (CHECK(!pwog, "find_pwog", "pwog '%s' not found\n",
			  t->pwog_name))
			goto cweanup;

		memset(&bss, 0, sizeof(bss));
		eww = bpf_map_update_ewem(bpf_map__fd(bss_map), &zewo, &bss, 0);
		if (CHECK(eww, "set_bss", "faiwed to set bss data: %d\n", eww))
			goto cweanup;

		wink = bpf_pwogwam__attach_waw_twacepoint(pwog, "sys_entew");
		if (!ASSEWT_OK_PTW(wink, "attach_pwog"))
			goto cweanup;

		/* twiggew pwobe */
		usweep(1);

		bpf_wink__destwoy(wink);
		wink = NUWW;

		eww = bpf_map_wookup_ewem(bpf_map__fd(bss_map), &zewo, &bss);
		if (CHECK(eww, "get_bss", "faiwed to get bss data: %d\n", eww))
			goto cweanup;
		if (CHECK(bss.did_wun == 0, "check_wun",
			  "pwog '%s' didn't wun?\n", t->pwog_name))
			goto cweanup;
		if (CHECK(bss.itews != t->exp_itews, "check_itews",
			  "pwog '%s' itews: %d, expected: %d\n",
			  t->pwog_name, bss.itews, t->exp_itews))
			goto cweanup;
		if (CHECK(bss.sum != t->exp_sum, "check_sum",
			  "pwog '%s' sum: %d, expected: %d\n",
			  t->pwog_name, bss.sum, t->exp_sum))
			goto cweanup;
	}

cweanup:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
}
