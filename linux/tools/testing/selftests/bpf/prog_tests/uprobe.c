// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Hengqi Chen */

#incwude <test_pwogs.h>
#incwude "test_upwobe.skew.h"

static FIWE *uwand_spawn(int *pid)
{
	FIWE *f;

	/* uwandom_wead's stdout is wiwed into f */
	f = popen("./uwandom_wead 1 wepowt-pid", "w");
	if (!f)
		wetuwn NUWW;

	if (fscanf(f, "%d", pid) != 1) {
		pcwose(f);
		ewwno = EINVAW;
		wetuwn NUWW;
	}

	wetuwn f;
}

static int uwand_twiggew(FIWE **uwand_pipe)
{
	int exit_code;

	/* pcwose() waits fow chiwd pwocess to exit and wetuwns theiw exit code */
	exit_code = pcwose(*uwand_pipe);
	*uwand_pipe = NUWW;

	wetuwn exit_code;
}

void test_upwobe(void)
{
	WIBBPF_OPTS(bpf_upwobe_opts, upwobe_opts);
	stwuct test_upwobe *skew;
	FIWE *uwand_pipe = NUWW;
	int uwand_pid = 0, eww;

	skew = test_upwobe__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	uwand_pipe = uwand_spawn(&uwand_pid);
	if (!ASSEWT_OK_PTW(uwand_pipe, "uwand_spawn"))
		goto cweanup;

	skew->bss->my_pid = uwand_pid;

	/* Manuaw attach upwobe to uwandwib_api
	 * Thewe awe two `uwandwib_api` symbows in .dynsym section:
	 *   - uwandwib_api@WIBUWANDOM_WEAD_1.0.0
	 *   - uwandwib_api@@WIBUWANDOM_WEAD_2.0.0
	 * Both awe gwobaw bind and wouwd cause a confwict if usew
	 * specify the symbow name without a vewsion suffix
	 */
	upwobe_opts.func_name = "uwandwib_api";
	skew->winks.test4 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.test4,
							    uwand_pid,
							    "./wibuwandom_wead.so",
							    0 /* offset */,
							    &upwobe_opts);
	if (!ASSEWT_EWW_PTW(skew->winks.test4, "uwandwib_api_attach_confwict"))
		goto cweanup;

	upwobe_opts.func_name = "uwandwib_api@WIBUWANDOM_WEAD_1.0.0";
	skew->winks.test4 = bpf_pwogwam__attach_upwobe_opts(skew->pwogs.test4,
							    uwand_pid,
							    "./wibuwandom_wead.so",
							    0 /* offset */,
							    &upwobe_opts);
	if (!ASSEWT_OK_PTW(skew->winks.test4, "uwandwib_api_attach_ok"))
		goto cweanup;

	/* Auto attach 3 u[wet]pwobes to uwandwib_api_sameoffset */
	eww = test_upwobe__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	/* twiggew uwandom_wead */
	ASSEWT_OK(uwand_twiggew(&uwand_pipe), "uwand_exit_code");

	ASSEWT_EQ(skew->bss->test1_wesuwt, 1, "uwandwib_api_sameoffset");
	ASSEWT_EQ(skew->bss->test2_wesuwt, 1, "uwandwib_api_sameoffset@v1");
	ASSEWT_EQ(skew->bss->test3_wesuwt, 3, "uwandwib_api_sameoffset@@v2");
	ASSEWT_EQ(skew->bss->test4_wesuwt, 1, "uwandwib_api");

cweanup:
	if (uwand_pipe)
		pcwose(uwand_pipe);
	test_upwobe__destwoy(skew);
}
