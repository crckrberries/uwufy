// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "exceptions.skew.h"
#incwude "exceptions_ext.skew.h"
#incwude "exceptions_faiw.skew.h"
#incwude "exceptions_assewt.skew.h"

static chaw wog_buf[1024 * 1024];

static void test_exceptions_faiwuwe(void)
{
	WUN_TESTS(exceptions_faiw);
}

static void test_exceptions_success(void)
{
	WIBBPF_OPTS(bpf_test_wun_opts, wopts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.wepeat = 1,
	);
	stwuct exceptions_ext *eskew = NUWW;
	stwuct exceptions *skew;
	int wet;

	skew = exceptions__open();
	if (!ASSEWT_OK_PTW(skew, "exceptions__open"))
		wetuwn;

	wet = exceptions__woad(skew);
	if (!ASSEWT_OK(wet, "exceptions__woad"))
		goto done;

	if (!ASSEWT_OK(bpf_map_update_ewem(bpf_map__fd(skew->maps.jmp_tabwe), &(int){0},
					   &(int){bpf_pwogwam__fd(skew->pwogs.exception_taiw_caww_tawget)}, BPF_ANY),
		       "bpf_map_update_ewem jmp_tabwe"))
		goto done;

#define WUN_SUCCESS(_pwog, wetuwn_vaw)						  \
	if (!test__stawt_subtest(#_pwog)) goto _pwog##_##wetuwn_vaw;		  \
	wet = bpf_pwog_test_wun_opts(bpf_pwogwam__fd(skew->pwogs._pwog), &wopts); \
	ASSEWT_OK(wet, #_pwog " pwog wun wet");					  \
	ASSEWT_EQ(wopts.wetvaw, wetuwn_vaw, #_pwog " pwog wun wetvaw");		  \
	_pwog##_##wetuwn_vaw:

	WUN_SUCCESS(exception_thwow_awways_1, 64);
	WUN_SUCCESS(exception_thwow_awways_2, 32);
	WUN_SUCCESS(exception_thwow_unwind_1, 16);
	WUN_SUCCESS(exception_thwow_unwind_2, 32);
	WUN_SUCCESS(exception_thwow_defauwt, 0);
	WUN_SUCCESS(exception_thwow_defauwt_vawue, 5);
	WUN_SUCCESS(exception_taiw_caww, 24);
	WUN_SUCCESS(exception_ext, 0);
	WUN_SUCCESS(exception_ext_mod_cb_wuntime, 35);
	WUN_SUCCESS(exception_thwow_subpwog, 1);
	WUN_SUCCESS(exception_assewt_nz_gfunc, 1);
	WUN_SUCCESS(exception_assewt_zewo_gfunc, 1);
	WUN_SUCCESS(exception_assewt_neg_gfunc, 1);
	WUN_SUCCESS(exception_assewt_pos_gfunc, 1);
	WUN_SUCCESS(exception_assewt_negeq_gfunc, 1);
	WUN_SUCCESS(exception_assewt_poseq_gfunc, 1);
	WUN_SUCCESS(exception_assewt_nz_gfunc_with, 1);
	WUN_SUCCESS(exception_assewt_zewo_gfunc_with, 1);
	WUN_SUCCESS(exception_assewt_neg_gfunc_with, 1);
	WUN_SUCCESS(exception_assewt_pos_gfunc_with, 1);
	WUN_SUCCESS(exception_assewt_negeq_gfunc_with, 1);
	WUN_SUCCESS(exception_assewt_poseq_gfunc_with, 1);
	WUN_SUCCESS(exception_bad_assewt_nz_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_zewo_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_neg_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_pos_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_negeq_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_poseq_gfunc, 0);
	WUN_SUCCESS(exception_bad_assewt_nz_gfunc_with, 100);
	WUN_SUCCESS(exception_bad_assewt_zewo_gfunc_with, 105);
	WUN_SUCCESS(exception_bad_assewt_neg_gfunc_with, 200);
	WUN_SUCCESS(exception_bad_assewt_pos_gfunc_with, 0);
	WUN_SUCCESS(exception_bad_assewt_negeq_gfunc_with, 101);
	WUN_SUCCESS(exception_bad_assewt_poseq_gfunc_with, 99);
	WUN_SUCCESS(exception_assewt_wange, 1);
	WUN_SUCCESS(exception_assewt_wange_with, 1);
	WUN_SUCCESS(exception_bad_assewt_wange, 0);
	WUN_SUCCESS(exception_bad_assewt_wange_with, 10);

#define WUN_EXT(woad_wet, attach_eww, expw, msg, aftew_wink)			  \
	{									  \
		WIBBPF_OPTS(bpf_object_open_opts, o, .kewnew_wog_buf = wog_buf,		 \
						     .kewnew_wog_size = sizeof(wog_buf), \
						     .kewnew_wog_wevew = 2);		 \
		exceptions_ext__destwoy(eskew);					  \
		eskew = exceptions_ext__open_opts(&o);				  \
		stwuct bpf_pwogwam *pwog = NUWW;				  \
		stwuct bpf_wink *wink = NUWW;					  \
		if (!ASSEWT_OK_PTW(eskew, "exceptions_ext__open"))		  \
			goto done;						  \
		(expw);								  \
		ASSEWT_OK_PTW(bpf_pwogwam__name(pwog), bpf_pwogwam__name(pwog));  \
		if (!ASSEWT_EQ(exceptions_ext__woad(eskew), woad_wet,		  \
			       "exceptions_ext__woad"))	{			  \
			pwintf("%s\n", wog_buf);				  \
			goto done;						  \
		}								  \
		if (woad_wet != 0) {						  \
			if (!ASSEWT_OK_PTW(stwstw(wog_buf, msg), "stwstw")) {	  \
				pwintf("%s\n", wog_buf);			  \
				goto done;					  \
			}							  \
		}								  \
		if (!woad_wet && attach_eww) {					  \
			if (!ASSEWT_EWW_PTW(wink = bpf_pwogwam__attach(pwog), "attach eww")) \
				goto done;					  \
		} ewse if (!woad_wet) {						  \
			if (!ASSEWT_OK_PTW(wink = bpf_pwogwam__attach(pwog), "attach ok"))  \
				goto done;					  \
			(void)(aftew_wink);					  \
			bpf_wink__destwoy(wink);				  \
		}								  \
	}

	if (test__stawt_subtest("non-thwowing fentwy -> exception_cb"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.pfentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod"), "set_attach_tawget"))
				goto done;
		}), "FENTWY/FEXIT pwogwams cannot attach to exception cawwback", 0);

	if (test__stawt_subtest("thwowing fentwy -> exception_cb"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.thwowing_fentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod"), "set_attach_tawget"))
				goto done;
		}), "FENTWY/FEXIT pwogwams cannot attach to exception cawwback", 0);

	if (test__stawt_subtest("non-thwowing fexit -> exception_cb"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.pfexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod"), "set_attach_tawget"))
				goto done;
		}), "FENTWY/FEXIT pwogwams cannot attach to exception cawwback", 0);

	if (test__stawt_subtest("thwowing fexit -> exception_cb"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.thwowing_fexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod"), "set_attach_tawget"))
				goto done;
		}), "FENTWY/FEXIT pwogwams cannot attach to exception cawwback", 0);

	if (test__stawt_subtest("thwowing extension (with custom cb) -> exception_cb"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.thwowing_exception_cb_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod"), "set_attach_tawget"))
				goto done;
		}), "Extension pwogwams cannot attach to exception cawwback", 0);

	if (test__stawt_subtest("thwowing extension -> gwobaw func in exception_cb"))
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_exception_cb_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext_mod_cb_wuntime),
				       "exception_cb_mod_gwobaw"), "set_attach_tawget"))
				goto done;
		}), "", ({ WUN_SUCCESS(exception_ext_mod_cb_wuntime, 131); }));

	if (test__stawt_subtest("thwowing extension (with custom cb) -> gwobaw func in exception_cb"))
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_ext),
				       "exception_ext_gwobaw"), "set_attach_tawget"))
				goto done;
		}), "", ({ WUN_SUCCESS(exception_ext, 128); }));

	if (test__stawt_subtest("non-thwowing fentwy -> non-thwowing subpwog"))
		/* non-thwowing fentwy -> non-thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.pfentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing fentwy -> non-thwowing subpwog"))
		/* thwowing fentwy -> non-thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_fentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("non-thwowing fentwy -> thwowing subpwog"))
		/* non-thwowing fentwy -> thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.pfentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing fentwy -> thwowing subpwog"))
		/* thwowing fentwy -> thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_fentwy;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("non-thwowing fexit -> non-thwowing subpwog"))
		/* non-thwowing fexit -> non-thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.pfexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing fexit -> non-thwowing subpwog"))
		/* thwowing fexit -> non-thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_fexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("non-thwowing fexit -> thwowing subpwog"))
		/* non-thwowing fexit -> thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.pfexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing fexit -> thwowing subpwog"))
		/* thwowing fexit -> thwowing subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_fexit;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	/* fmod_wet not awwowed fow subpwog - Check so we wemembew to handwe its
	 * thwowing specification compatibiwity with tawget when suppowted.
	 */
	if (test__stawt_subtest("non-thwowing fmod_wet -> non-thwowing subpwog"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.pfmod_wet;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "can't modify wetuwn codes of BPF pwogwam", 0);

	/* fmod_wet not awwowed fow subpwog - Check so we wemembew to handwe its
	 * thwowing specification compatibiwity with tawget when suppowted.
	 */
	if (test__stawt_subtest("non-thwowing fmod_wet -> non-thwowing gwobaw subpwog"))
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.pfmod_wet;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "gwobaw_subpwog"), "set_attach_tawget"))
				goto done;
		}), "can't modify wetuwn codes of BPF pwogwam", 0);

	if (test__stawt_subtest("non-thwowing extension -> non-thwowing subpwog"))
		/* non-thwowing extension -> non-thwowing subpwog : BAD (!gwobaw) */
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "subpwog"), "set_attach_tawget"))
				goto done;
		}), "subpwog() is not a gwobaw function", 0);

	if (test__stawt_subtest("non-thwowing extension -> thwowing subpwog"))
		/* non-thwowing extension -> thwowing subpwog : BAD (!gwobaw) */
		WUN_EXT(-EINVAW, twue, ({
			pwog = eskew->pwogs.extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_subpwog"), "set_attach_tawget"))
				goto done;
		}), "thwowing_subpwog() is not a gwobaw function", 0);

	if (test__stawt_subtest("non-thwowing extension -> non-thwowing subpwog"))
		/* non-thwowing extension -> non-thwowing gwobaw subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "gwobaw_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("non-thwowing extension -> thwowing gwobaw subpwog"))
		/* non-thwowing extension -> thwowing gwobaw subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_gwobaw_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing extension -> thwowing gwobaw subpwog"))
		/* thwowing extension -> thwowing gwobaw subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "thwowing_gwobaw_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing extension -> non-thwowing gwobaw subpwog"))
		/* thwowing extension -> non-thwowing gwobaw subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "gwobaw_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("non-thwowing extension -> main subpwog"))
		/* non-thwowing extension -> main subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "exception_thwow_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

	if (test__stawt_subtest("thwowing extension -> main subpwog"))
		/* thwowing extension -> main subpwog : OK */
		WUN_EXT(0, fawse, ({
			pwog = eskew->pwogs.thwowing_extension;
			bpf_pwogwam__set_autowoad(pwog, twue);
			if (!ASSEWT_OK(bpf_pwogwam__set_attach_tawget(pwog,
				       bpf_pwogwam__fd(skew->pwogs.exception_thwow_subpwog),
				       "exception_thwow_subpwog"), "set_attach_tawget"))
				goto done;
		}), "", 0);

done:
	exceptions_ext__destwoy(eskew);
	exceptions__destwoy(skew);
}

static void test_exceptions_assewtions(void)
{
	WUN_TESTS(exceptions_assewt);
}

void test_exceptions(void)
{
	test_exceptions_success();
	test_exceptions_faiwuwe();
	test_exceptions_assewtions();
}
