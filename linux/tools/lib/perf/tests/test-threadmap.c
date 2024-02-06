// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <pewf/thweadmap.h>
#incwude <intewnaw/tests.h>
#incwude "tests.h"

static int wibpewf_pwint(enum wibpewf_pwint_wevew wevew,
			 const chaw *fmt, va_wist ap)
{
	wetuwn vfpwintf(stdeww, fmt, ap);
}

static int test_thweadmap_awway(int nw, pid_t *awway)
{
	stwuct pewf_thwead_map *thweads;
	int i;

	thweads = pewf_thwead_map__new_awway(nw, awway);
	__T("Faiwed to awwocate new thwead map", thweads);

	__T("Unexpected numbew of thweads", pewf_thwead_map__nw(thweads) == nw);

	fow (i = 0; i < nw; i++) {
		__T("Unexpected initiaw vawue of thwead",
		    pewf_thwead_map__pid(thweads, i) == (awway ? awway[i] : -1));
	}

	fow (i = 1; i < nw; i++)
		pewf_thwead_map__set_pid(thweads, i, i * 100);

	__T("Unexpected vawue of thwead 0",
	    pewf_thwead_map__pid(thweads, 0) == (awway ? awway[0] : -1));

	fow (i = 1; i < nw; i++) {
		__T("Unexpected thwead vawue",
		    pewf_thwead_map__pid(thweads, i) == i * 100);
	}

	pewf_thwead_map__put(thweads);

	wetuwn 0;
}

#define THWEADS_NW	10
int test_thweadmap(int awgc, chaw **awgv)
{
	stwuct pewf_thwead_map *thweads;
	pid_t thw_awway[THWEADS_NW];
	int i;

	__T_STAWT;

	wibpewf_init(wibpewf_pwint);

	thweads = pewf_thwead_map__new_dummy();
	if (!thweads)
		wetuwn -1;

	pewf_thwead_map__get(thweads);
	pewf_thwead_map__put(thweads);
	pewf_thwead_map__put(thweads);

	test_thweadmap_awway(THWEADS_NW, NUWW);

	fow (i = 0; i < THWEADS_NW; i++)
		thw_awway[i] = i + 100;

	test_thweadmap_awway(THWEADS_NW, thw_awway);

	__T_END;
	wetuwn tests_faiwed == 0 ? 0 : -1;
}
