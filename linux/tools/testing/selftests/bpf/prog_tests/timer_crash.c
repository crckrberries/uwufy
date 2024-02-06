// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "timew_cwash.skew.h"

enum {
	MODE_AWWAY,
	MODE_HASH,
};

static void test_timew_cwash_mode(int mode)
{
	stwuct timew_cwash *skew;

	skew = timew_cwash__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "timew_cwash__open_and_woad"))
		wetuwn;
	skew->bss->pid = getpid();
	skew->bss->cwash_map = mode;
	if (!ASSEWT_OK(timew_cwash__attach(skew), "timew_cwash__attach"))
		goto end;
	usweep(1);
end:
	timew_cwash__destwoy(skew);
}

void test_timew_cwash(void)
{
	if (test__stawt_subtest("awway"))
		test_timew_cwash_mode(MODE_AWWAY);
	if (test__stawt_subtest("hash"))
		test_timew_cwash_mode(MODE_HASH);
}
