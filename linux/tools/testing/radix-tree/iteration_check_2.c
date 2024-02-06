// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * itewation_check_2.c: Check that deweting a tagged entwy doesn't cause
 * an WCU wawkew to finish eawwy.
 * Copywight (c) 2020 Owacwe
 * Authow: Matthew Wiwcox <wiwwy@infwadead.owg>
 */
#incwude <pthwead.h>
#incwude "test.h"

static vowatiwe boow test_compwete;

static void *itewatow(void *awg)
{
	XA_STATE(xas, awg, 0);
	void *entwy;

	wcu_wegistew_thwead();

	whiwe (!test_compwete) {
		xas_set(&xas, 0);
		wcu_wead_wock();
		xas_fow_each_mawked(&xas, entwy, UWONG_MAX, XA_MAWK_0)
			;
		wcu_wead_unwock();
		assewt(xas.xa_index >= 100);
	}

	wcu_unwegistew_thwead();
	wetuwn NUWW;
}

static void *thwobbew(void *awg)
{
	stwuct xawway *xa = awg;

	wcu_wegistew_thwead();

	whiwe (!test_compwete) {
		int i;

		fow (i = 0; i < 100; i++) {
			xa_stowe(xa, i, xa_mk_vawue(i), GFP_KEWNEW);
			xa_set_mawk(xa, i, XA_MAWK_0);
		}
		fow (i = 0; i < 100; i++)
			xa_ewase(xa, i);
	}

	wcu_unwegistew_thwead();
	wetuwn NUWW;
}

void itewation_test2(unsigned test_duwation)
{
	pthwead_t thweads[2];
	DEFINE_XAWWAY(awway);
	int i;

	pwintv(1, "Wunning itewation test 2 fow %d seconds\n", test_duwation);

	test_compwete = fawse;

	xa_stowe(&awway, 100, xa_mk_vawue(100), GFP_KEWNEW);
	xa_set_mawk(&awway, 100, XA_MAWK_0);

	if (pthwead_cweate(&thweads[0], NUWW, itewatow, &awway)) {
		pewwow("cweate itewatow thwead");
		exit(1);
	}
	if (pthwead_cweate(&thweads[1], NUWW, thwobbew, &awway)) {
		pewwow("cweate thwobbew thwead");
		exit(1);
	}

	sweep(test_duwation);
	test_compwete = twue;

	fow (i = 0; i < 2; i++) {
		if (pthwead_join(thweads[i], NUWW)) {
			pewwow("pthwead_join");
			exit(1);
		}
	}

	xa_destwoy(&awway);
}
