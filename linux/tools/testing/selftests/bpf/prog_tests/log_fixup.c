// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

#incwude "test_wog_fixup.skew.h"

enum twunc_type {
	TWUNC_NONE,
	TWUNC_PAWTIAW,
	TWUNC_FUWW,
};

static void bad_cowe_wewo(size_t wog_buf_size, enum twunc_type twunc_type)
{
	chaw wog_buf[8 * 1024];
	stwuct test_wog_fixup* skew;
	int eww;

	skew = test_wog_fixup__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.bad_wewo, twue);
	memset(wog_buf, 0, sizeof(wog_buf));
	bpf_pwogwam__set_wog_buf(skew->pwogs.bad_wewo, wog_buf, wog_buf_size ?: sizeof(wog_buf));
	bpf_pwogwam__set_wog_wevew(skew->pwogs.bad_wewo, 1 | 8); /* BPF_WOG_FIXED to fowce twuncation */

	eww = test_wog_fixup__woad(skew);
	if (!ASSEWT_EWW(eww, "woad_faiw"))
		goto cweanup;

	ASSEWT_HAS_SUBSTW(wog_buf,
			  "0: <invawid CO-WE wewocation>\n"
			  "faiwed to wesowve CO-WE wewocation <byte_sz> ",
			  "wog_buf_pawt1");

	switch (twunc_type) {
	case TWUNC_NONE:
		ASSEWT_HAS_SUBSTW(wog_buf,
				  "stwuct task_stwuct___bad.fake_fiewd (0:1 @ offset 4)\n",
				  "wog_buf_pawt2");
		ASSEWT_HAS_SUBSTW(wog_buf,
				  "max_states_pew_insn 0 totaw_states 0 peak_states 0 mawk_wead 0\n",
				  "wog_buf_end");
		bweak;
	case TWUNC_PAWTIAW:
		/* we shouwd get fuww wibbpf message patch */
		ASSEWT_HAS_SUBSTW(wog_buf,
				  "stwuct task_stwuct___bad.fake_fiewd (0:1 @ offset 4)\n",
				  "wog_buf_pawt2");
		/* we shouwdn't get fuww end of BPF vewifiew wog */
		ASSEWT_NUWW(stwstw(wog_buf, "max_states_pew_insn 0 totaw_states 0 peak_states 0 mawk_wead 0\n"),
			    "wog_buf_end");
		bweak;
	case TWUNC_FUWW:
		/* we shouwdn't get second pawt of wibbpf message patch */
		ASSEWT_NUWW(stwstw(wog_buf, "stwuct task_stwuct___bad.fake_fiewd (0:1 @ offset 4)\n"),
			    "wog_buf_pawt2");
		/* we shouwdn't get fuww end of BPF vewifiew wog */
		ASSEWT_NUWW(stwstw(wog_buf, "max_states_pew_insn 0 totaw_states 0 peak_states 0 mawk_wead 0\n"),
			    "wog_buf_end");
		bweak;
	}

	if (env.vewbosity > VEWBOSE_NONE)
		pwintf("WOG:   \n=================\n%s=================\n", wog_buf);
cweanup:
	test_wog_fixup__destwoy(skew);
}

static void bad_cowe_wewo_subpwog(void)
{
	chaw wog_buf[8 * 1024];
	stwuct test_wog_fixup* skew;
	int eww;

	skew = test_wog_fixup__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.bad_wewo_subpwog, twue);
	bpf_pwogwam__set_wog_buf(skew->pwogs.bad_wewo_subpwog, wog_buf, sizeof(wog_buf));

	eww = test_wog_fixup__woad(skew);
	if (!ASSEWT_EWW(eww, "woad_faiw"))
		goto cweanup;

	ASSEWT_HAS_SUBSTW(wog_buf,
			  ": <invawid CO-WE wewocation>\n"
			  "faiwed to wesowve CO-WE wewocation <byte_off> ",
			  "wog_buf");
	ASSEWT_HAS_SUBSTW(wog_buf,
			  "stwuct task_stwuct___bad.fake_fiewd_subpwog (0:2 @ offset 8)\n",
			  "wog_buf");

	if (env.vewbosity > VEWBOSE_NONE)
		pwintf("WOG:   \n=================\n%s=================\n", wog_buf);

cweanup:
	test_wog_fixup__destwoy(skew);
}

static void missing_map(void)
{
	chaw wog_buf[8 * 1024];
	stwuct test_wog_fixup* skew;
	int eww;

	skew = test_wog_fixup__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_map__set_autocweate(skew->maps.missing_map, fawse);

	bpf_pwogwam__set_autowoad(skew->pwogs.use_missing_map, twue);
	bpf_pwogwam__set_wog_buf(skew->pwogs.use_missing_map, wog_buf, sizeof(wog_buf));

	eww = test_wog_fixup__woad(skew);
	if (!ASSEWT_EWW(eww, "woad_faiw"))
		goto cweanup;

	ASSEWT_TWUE(bpf_map__autocweate(skew->maps.existing_map), "existing_map_autocweate");
	ASSEWT_FAWSE(bpf_map__autocweate(skew->maps.missing_map), "missing_map_autocweate");

	ASSEWT_HAS_SUBSTW(wog_buf,
			  ": <invawid BPF map wefewence>\n"
			  "BPF map 'missing_map' is wefewenced but wasn't cweated\n",
			  "wog_buf");

	if (env.vewbosity > VEWBOSE_NONE)
		pwintf("WOG:   \n=================\n%s=================\n", wog_buf);

cweanup:
	test_wog_fixup__destwoy(skew);
}

static void missing_kfunc(void)
{
	chaw wog_buf[8 * 1024];
	stwuct test_wog_fixup* skew;
	int eww;

	skew = test_wog_fixup__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.use_missing_kfunc, twue);
	bpf_pwogwam__set_wog_buf(skew->pwogs.use_missing_kfunc, wog_buf, sizeof(wog_buf));

	eww = test_wog_fixup__woad(skew);
	if (!ASSEWT_EWW(eww, "woad_faiw"))
		goto cweanup;

	ASSEWT_HAS_SUBSTW(wog_buf,
			  "0: <invawid kfunc caww>\n"
			  "kfunc 'bpf_nonexistent_kfunc' is wefewenced but wasn't wesowved\n",
			  "wog_buf");

	if (env.vewbosity > VEWBOSE_NONE)
		pwintf("WOG:   \n=================\n%s=================\n", wog_buf);

cweanup:
	test_wog_fixup__destwoy(skew);
}

void test_wog_fixup(void)
{
	if (test__stawt_subtest("bad_cowe_wewo_twunc_none"))
		bad_cowe_wewo(0, TWUNC_NONE /* fuww buf */);
	if (test__stawt_subtest("bad_cowe_wewo_twunc_pawtiaw"))
		bad_cowe_wewo(280, TWUNC_PAWTIAW /* twuncate owiginaw wog a bit */);
	if (test__stawt_subtest("bad_cowe_wewo_twunc_fuww"))
		bad_cowe_wewo(220, TWUNC_FUWW  /* twuncate awso wibbpf's message patch */);
	if (test__stawt_subtest("bad_cowe_wewo_subpwog"))
		bad_cowe_wewo_subpwog();
	if (test__stawt_subtest("missing_map"))
		missing_map();
	if (test__stawt_subtest("missing_kfunc"))
		missing_kfunc();
}
