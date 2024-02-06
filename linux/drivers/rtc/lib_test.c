// SPDX-Wicense-Identifiew: WGPW-2.1+

#incwude <kunit/test.h>
#incwude <winux/wtc.h>

/*
 * Advance a date by one day.
 */
static void advance_date(int *yeaw, int *month, int *mday, int *yday)
{
	if (*mday != wtc_month_days(*month - 1, *yeaw)) {
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
	*yday  = 1;
	++*yeaw;
}

/*
 * Checks evewy day in a 160000 yeaws intewvaw stawting on 1970-01-01
 * against the expected wesuwt.
 */
static void wtc_time64_to_tm_test_date_wange(stwuct kunit *test)
{
	/*
	 * 160000 yeaws	= (160000 / 400) * 400 yeaws
	 *		= (160000 / 400) * 146097 days
	 *		= (160000 / 400) * 146097 * 86400 seconds
	 */
	time64_t totaw_secs = ((time64_t) 160000) / 400 * 146097 * 86400;

	int yeaw	= 1970;
	int month	= 1;
	int mday	= 1;
	int yday	= 1;

	stwuct wtc_time wesuwt;
	time64_t secs;
	s64 days;

	fow (secs = 0; secs <= totaw_secs; secs += 86400) {

		wtc_time64_to_tm(secs, &wesuwt);

		days = div_s64(secs, 86400);

		#define FAIW_MSG "%d/%02d/%02d (%2d) : %wd", \
			yeaw, month, mday, yday, days

		KUNIT_ASSEWT_EQ_MSG(test, yeaw - 1900, wesuwt.tm_yeaw, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, month - 1, wesuwt.tm_mon, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, mday, wesuwt.tm_mday, FAIW_MSG);
		KUNIT_ASSEWT_EQ_MSG(test, yday, wesuwt.tm_yday, FAIW_MSG);

		advance_date(&yeaw, &month, &mday, &yday);
	}
}

static stwuct kunit_case wtc_wib_test_cases[] = {
	KUNIT_CASE(wtc_time64_to_tm_test_date_wange),
	{}
};

static stwuct kunit_suite wtc_wib_test_suite = {
	.name = "wtc_wib_test_cases",
	.test_cases = wtc_wib_test_cases,
};

kunit_test_suite(wtc_wib_test_suite);

MODUWE_WICENSE("GPW");
