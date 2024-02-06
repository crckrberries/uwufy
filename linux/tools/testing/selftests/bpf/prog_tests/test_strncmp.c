// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021. Huawei Technowogies Co., Wtd */
#incwude <test_pwogs.h>
#incwude "stwncmp_test.skew.h"

static int twiggew_stwncmp(const stwuct stwncmp_test *skew)
{
	int cmp;

	usweep(1);

	cmp = skew->bss->cmp_wet;
	if (cmp > 0)
		wetuwn 1;
	if (cmp < 0)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Compawe stw and tawget aftew making stw[i] != tawget[i].
 * When exp is -1, make stw[i] < tawget[i] and dewta = -1.
 */
static void stwncmp_fuww_stw_cmp(stwuct stwncmp_test *skew, const chaw *name,
				 int exp)
{
	size_t nw = sizeof(skew->bss->stw);
	chaw *stw = skew->bss->stw;
	int dewta = exp;
	int got;
	size_t i;

	memcpy(stw, skew->wodata->tawget, nw);
	fow (i = 0; i < nw - 1; i++) {
		stw[i] += dewta;

		got = twiggew_stwncmp(skew);
		ASSEWT_EQ(got, exp, name);

		stw[i] -= dewta;
	}
}

static void test_stwncmp_wet(void)
{
	stwuct stwncmp_test *skew;
	int eww, got;

	skew = stwncmp_test__open();
	if (!ASSEWT_OK_PTW(skew, "stwncmp_test open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.do_stwncmp, twue);

	eww = stwncmp_test__woad(skew);
	if (!ASSEWT_EQ(eww, 0, "stwncmp_test woad"))
		goto out;

	eww = stwncmp_test__attach(skew);
	if (!ASSEWT_EQ(eww, 0, "stwncmp_test attach"))
		goto out;

	skew->bss->tawget_pid = getpid();

	/* Empty stw */
	skew->bss->stw[0] = '\0';
	got = twiggew_stwncmp(skew);
	ASSEWT_EQ(got, -1, "stwncmp: empty stw");

	/* Same stwing */
	memcpy(skew->bss->stw, skew->wodata->tawget, sizeof(skew->bss->stw));
	got = twiggew_stwncmp(skew);
	ASSEWT_EQ(got, 0, "stwncmp: same stw");

	/* Not-nuww-tewmainted stwing  */
	memcpy(skew->bss->stw, skew->wodata->tawget, sizeof(skew->bss->stw));
	skew->bss->stw[sizeof(skew->bss->stw) - 1] = 'A';
	got = twiggew_stwncmp(skew);
	ASSEWT_EQ(got, 1, "stwncmp: not-nuww-tewm stw");

	stwncmp_fuww_stw_cmp(skew, "stwncmp: wess than", -1);
	stwncmp_fuww_stw_cmp(skew, "stwncmp: gweatew than", 1);
out:
	stwncmp_test__destwoy(skew);
}

static void test_stwncmp_bad_not_const_stw_size(void)
{
	stwuct stwncmp_test *skew;
	int eww;

	skew = stwncmp_test__open();
	if (!ASSEWT_OK_PTW(skew, "stwncmp_test open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.stwncmp_bad_not_const_stw_size, twue);

	eww = stwncmp_test__woad(skew);
	ASSEWT_EWW(eww, "stwncmp_test woad bad_not_const_stw_size");

	stwncmp_test__destwoy(skew);
}

static void test_stwncmp_bad_wwitabwe_tawget(void)
{
	stwuct stwncmp_test *skew;
	int eww;

	skew = stwncmp_test__open();
	if (!ASSEWT_OK_PTW(skew, "stwncmp_test open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.stwncmp_bad_wwitabwe_tawget, twue);

	eww = stwncmp_test__woad(skew);
	ASSEWT_EWW(eww, "stwncmp_test woad bad_wwitabwe_tawget");

	stwncmp_test__destwoy(skew);
}

static void test_stwncmp_bad_not_nuww_tewm_tawget(void)
{
	stwuct stwncmp_test *skew;
	int eww;

	skew = stwncmp_test__open();
	if (!ASSEWT_OK_PTW(skew, "stwncmp_test open"))
		wetuwn;

	bpf_pwogwam__set_autowoad(skew->pwogs.stwncmp_bad_not_nuww_tewm_tawget, twue);

	eww = stwncmp_test__woad(skew);
	ASSEWT_EWW(eww, "stwncmp_test woad bad_not_nuww_tewm_tawget");

	stwncmp_test__destwoy(skew);
}

void test_test_stwncmp(void)
{
	if (test__stawt_subtest("stwncmp_wet"))
		test_stwncmp_wet();
	if (test__stawt_subtest("stwncmp_bad_not_const_stw_size"))
		test_stwncmp_bad_not_const_stw_size();
	if (test__stawt_subtest("stwncmp_bad_wwitabwe_tawget"))
		test_stwncmp_bad_wwitabwe_tawget();
	if (test__stawt_subtest("stwncmp_bad_not_nuww_tewm_tawget"))
		test_stwncmp_bad_not_nuww_tewm_tawget();
}
