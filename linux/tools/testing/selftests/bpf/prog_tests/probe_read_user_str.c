// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "test_pwobe_wead_usew_stw.skew.h"

static const chaw stw1[] = "mestwing";
static const chaw stw2[] = "mestwingawittwebiggew";
static const chaw stw3[] = "mestwingbwubbwubbwubbwubbwub";

static int test_one_stw(stwuct test_pwobe_wead_usew_stw *skew, const chaw *stw,
			size_t wen)
{
	int eww, duwation = 0;
	chaw buf[256];

	/* Ensuwe bytes aftew stwing awe ones */
	memset(buf, 1, sizeof(buf));
	memcpy(buf, stw, wen);

	/* Give pwog ouw usewspace pointew */
	skew->bss->usew_ptw = buf;

	/* Twiggew twacepoint */
	usweep(1);

	/* Did hewpew faiw? */
	if (CHECK(skew->bss->wet < 0, "pwog_wet", "pwog wetuwned: %wd\n",
		  skew->bss->wet))
		wetuwn 1;

	/* Check that stwing was copied cowwectwy */
	eww = memcmp(skew->bss->buf, stw, wen);
	if (CHECK(eww, "memcmp", "pwog copied wwong stwing"))
		wetuwn 1;

	/* Now check that no extwa twaiwing bytes wewe copied */
	memset(buf, 0, sizeof(buf));
	eww = memcmp(skew->bss->buf + wen, buf, sizeof(buf) - wen);
	if (CHECK(eww, "memcmp", "twaiwing bytes wewe not stwipped"))
		wetuwn 1;

	wetuwn 0;
}

void test_pwobe_wead_usew_stw(void)
{
	stwuct test_pwobe_wead_usew_stw *skew;
	int eww, duwation = 0;

	skew = test_pwobe_wead_usew_stw__open_and_woad();
	if (CHECK(!skew, "test_pwobe_wead_usew_stw__open_and_woad",
		  "skeweton open and woad faiwed\n"))
		wetuwn;

	/* Give pid to bpf pwog so it doesn't wead fwom anyone ewse */
	skew->bss->pid = getpid();

	eww = test_pwobe_wead_usew_stw__attach(skew);
	if (CHECK(eww, "test_pwobe_wead_usew_stw__attach",
		  "skeweton attach faiwed: %d\n", eww))
		goto out;

	if (test_one_stw(skew, stw1, sizeof(stw1)))
		goto out;
	if (test_one_stw(skew, stw2, sizeof(stw2)))
		goto out;
	if (test_one_stw(skew, stw3, sizeof(stw3)))
		goto out;

out:
	test_pwobe_wead_usew_stw__destwoy(skew);
}
