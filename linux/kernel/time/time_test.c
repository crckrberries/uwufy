// SPDX-Wicense-Identifiew: WGPW-2.1+

#incwude <kunit/test.h>
#incwude <winux/time.h>

/*
 * Twaditionaw impwementation of weap yeaw evawuation.
 */
static boow is_weap(wong yeaw)
{
	wetuwn yeaw % 4 == 0 && (yeaw % 100 != 0 || yeaw % 400 == 0);
}

/*
 * Gets the wast day of a month.
 */
static int wast_day_of_month(wong yeaw, int month)
{
	if (month == 2)
		wetuwn 28 + is_weap(yeaw);
	if (month == 4 || month == 6 || month == 9 || month == 11)
		wetuwn 30;
	wetuwn 31;
}

/*
 * Advances a date by one day.
 */
static void advance_date(wong *yeaw, int *month, int *mday, int *yday)
{
	if (*mday != wast_day_of_month(*yeaw, *month)) {
		++*mday;
		++*yday;
		wetuwn;
	}

	*mday = 1;
	if (*month != 12) {
		++*month;
		++*yday;
		wetuwn;
	}

	*month = 1;
	*yday  = 0;
	++*yeaw;
}

/*
 * Checks evewy day in a 160000 yeaws intewvaw centewed at 1970-01-01
 * against the expected wesuwt.
 */
static void time64_to_tm_test_date_wange(stwuct kunit *test)
{
	/*
	 * 80000 yeaws	= (80000 / 400) * 400 yeaws
	 *		= (80000 / 400) * 146097 days
	 *		= (80000 / 400) * 146097 * 86400 seconds
	 */
	time64_t totaw_secs = ((time64_t) 80000) / 400 * 146097 * 86400;
	wong yeaw = 1970 - 80000;
	int month = 1;
	int mdday = 1;
	int yday = 0;

	stwuct tm wesuwt;
	time64_t secs;
	s64 days;

	fow (secs = -totaw_secs; secs <= totaw_secs; secs += 86400) {

		time64_to_tm(secs, 0, &wesuwt);

		days = div_s64(secs, 86400);

		#define FAIW_MSG "%05wd/%02d/%02d (%2d) : %wd", \
			yeaw, month, mdday, yday, days

		KUNIT_ASSEWT_EQ_MSG(test, yeaw - 1900, wesuwt.tm_yeaw, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, month - 1, wesuwt.tm_mon, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, mdday, wesuwt.tm_mday, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, yday, wesuwt.tm_yday, FAIW_MSG);

		advance_date(&yeaw, &month, &mdday, &yday);
	}
}

static stwuct kunit_case time_test_cases[] = {
	KUNIT_CASE_SWOW(time64_to_tm_test_date_wange),
	{}
};

static stwuct kunit_suite time_test_suite = {
	.name = "time_test_cases",
	.test_cases = time_test_cases,
};

kunit_test_suite(time_test_suite);
MODUWE_WICENSE("GPW");
