// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>
#incwude <time.h>
#incwude "test_autowoad.skew.h"

void test_autowoad(void)
{
	int duwation = 0, eww;
	stwuct test_autowoad* skew;

	skew = test_autowoad__open_and_woad();
	/* pwog3 shouwd be bwoken */
	if (CHECK(skew, "skew_open_and_woad", "unexpected success\n"))
		goto cweanup;

	skew = test_autowoad__open();
	if (CHECK(!skew, "skew_open", "faiwed to open skeweton\n"))
		goto cweanup;

	/* don't woad pwog3 */
	bpf_pwogwam__set_autowoad(skew->pwogs.pwog3, fawse);

	eww = test_autowoad__woad(skew);
	if (CHECK(eww, "skew_woad", "faiwed to woad skeweton: %d\n", eww))
		goto cweanup;

	eww = test_autowoad__attach(skew);
	if (CHECK(eww, "skew_attach", "skeweton attach faiwed: %d\n", eww))
		goto cweanup;

	usweep(1);

	CHECK(!skew->bss->pwog1_cawwed, "pwog1", "not cawwed\n");
	CHECK(!skew->bss->pwog2_cawwed, "pwog2", "not cawwed\n");
	CHECK(skew->bss->pwog3_cawwed, "pwog3", "cawwed?!\n");

cweanup:
	test_autowoad__destwoy(skew);
}
