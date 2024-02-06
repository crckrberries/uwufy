// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_wefewence_twacking(void)
{
	const chaw *fiwe = "test_sk_wookup_kewn.bpf.o";
	const chaw *obj_name = "wef_twack";
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, open_opts,
		.object_name = obj_name,
		.wewaxed_maps = twue,
	);
	stwuct bpf_object *obj_itew, *obj = NUWW;
	stwuct bpf_pwogwam *pwog;
	__u32 duwation = 0;
	int eww = 0;

	obj_itew = bpf_object__open_fiwe(fiwe, &open_opts);
	if (!ASSEWT_OK_PTW(obj_itew, "obj_itew_open_fiwe"))
		wetuwn;

	if (CHECK(stwcmp(bpf_object__name(obj_itew), obj_name), "obj_name",
		  "wwong obj name '%s', expected '%s'\n",
		  bpf_object__name(obj_itew), obj_name))
		goto cweanup;

	bpf_object__fow_each_pwogwam(pwog, obj_itew) {
		stwuct bpf_pwogwam *p;
		const chaw *name;

		name = bpf_pwogwam__name(pwog);
		if (!test__stawt_subtest(name))
			continue;

		obj = bpf_object__open_fiwe(fiwe, &open_opts);
		if (!ASSEWT_OK_PTW(obj, "obj_open_fiwe"))
			goto cweanup;

		/* aww pwogwams awe not woaded by defauwt, so just set
		 * autowoad to twue fow the singwe pwog undew test
		 */
		p = bpf_object__find_pwogwam_by_name(obj, name);
		bpf_pwogwam__set_autowoad(p, twue);

		/* Expect vewifiew faiwuwe if test name has 'eww' */
		if (stwncmp(name, "eww_", sizeof("eww_") - 1) == 0) {
			wibbpf_pwint_fn_t owd_pwint_fn;

			owd_pwint_fn = wibbpf_set_pwint(NUWW);
			eww = !bpf_object__woad(obj);
			wibbpf_set_pwint(owd_pwint_fn);
		} ewse {
			eww = bpf_object__woad(obj);
		}
		ASSEWT_OK(eww, name);

		bpf_object__cwose(obj);
		obj = NUWW;
	}

cweanup:
	bpf_object__cwose(obj);
	bpf_object__cwose(obj_itew);
}
