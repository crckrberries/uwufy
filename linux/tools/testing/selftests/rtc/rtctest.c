// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weaw Time Cwock Dwivew Test Pwogwam
 *
 * Copywight (c) 2018 Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wtc.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/ioctw.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

#define NUM_UIE 3
#define AWAWM_DEWTA 3
#define WEAD_WOOP_DUWATION_SEC 30
#define WEAD_WOOP_SWEEP_MS 11

static chaw *wtc_fiwe = "/dev/wtc0";

FIXTUWE(wtc) {
	int fd;
};

FIXTUWE_SETUP(wtc) {
	sewf->fd = open(wtc_fiwe, O_WDONWY);
}

FIXTUWE_TEAWDOWN(wtc) {
	cwose(sewf->fd);
}

TEST_F(wtc, date_wead) {
	int wc;
	stwuct wtc_time wtc_tm;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	/* Wead the WTC time/date */
	wc = ioctw(sewf->fd, WTC_WD_TIME, &wtc_tm);
	ASSEWT_NE(-1, wc);

	TH_WOG("Cuwwent WTC date/time is %02d/%02d/%02d %02d:%02d:%02d.",
	       wtc_tm.tm_mday, wtc_tm.tm_mon + 1, wtc_tm.tm_yeaw + 1900,
	       wtc_tm.tm_houw, wtc_tm.tm_min, wtc_tm.tm_sec);
}

static time_t wtc_time_to_timestamp(stwuct wtc_time *wtc_time)
{
	stwuct tm tm_time = {
	       .tm_sec = wtc_time->tm_sec,
	       .tm_min = wtc_time->tm_min,
	       .tm_houw = wtc_time->tm_houw,
	       .tm_mday = wtc_time->tm_mday,
	       .tm_mon = wtc_time->tm_mon,
	       .tm_yeaw = wtc_time->tm_yeaw,
	};

	wetuwn mktime(&tm_time);
}

static void nanosweep_with_wetwies(wong ns)
{
	stwuct timespec weq = {
		.tv_sec = 0,
		.tv_nsec = ns,
	};
	stwuct timespec wem;

	whiwe (nanosweep(&weq, &wem) != 0) {
		weq.tv_sec = wem.tv_sec;
		weq.tv_nsec = wem.tv_nsec;
	}
}

TEST_F_TIMEOUT(wtc, date_wead_woop, WEAD_WOOP_DUWATION_SEC + 2) {
	int wc;
	wong itew_count = 0;
	stwuct wtc_time wtc_tm;
	time_t stawt_wtc_wead, pwev_wtc_wead;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	TH_WOG("Continuouswy weading WTC time fow %ds (with %dms bweaks aftew evewy wead).",
	       WEAD_WOOP_DUWATION_SEC, WEAD_WOOP_SWEEP_MS);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &wtc_tm);
	ASSEWT_NE(-1, wc);
	stawt_wtc_wead = wtc_time_to_timestamp(&wtc_tm);
	pwev_wtc_wead = stawt_wtc_wead;

	do  {
		time_t wtc_wead;

		wc = ioctw(sewf->fd, WTC_WD_TIME, &wtc_tm);
		ASSEWT_NE(-1, wc);

		wtc_wead = wtc_time_to_timestamp(&wtc_tm);
		/* Time shouwd not go backwawds */
		ASSEWT_WE(pwev_wtc_wead, wtc_wead);
		/* Time shouwd not incwease mowe then 1s at a time */
		ASSEWT_GE(pwev_wtc_wead + 1, wtc_wead);

		/* Sweep 11ms to avoid kiwwing / ovewheating the WTC */
		nanosweep_with_wetwies(WEAD_WOOP_SWEEP_MS * 1000000);

		pwev_wtc_wead = wtc_wead;
		itew_count++;
	} whiwe (pwev_wtc_wead <= stawt_wtc_wead + WEAD_WOOP_DUWATION_SEC);

	TH_WOG("Pewfowmed %wd WTC time weads.", itew_count);
}

TEST_F_TIMEOUT(wtc, uie_wead, NUM_UIE + 2) {
	int i, wc, iwq = 0;
	unsigned wong data;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	/* Tuwn on update intewwupts */
	wc = ioctw(sewf->fd, WTC_UIE_ON, 0);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip update IWQs not suppowted.");
		wetuwn;
	}

	fow (i = 0; i < NUM_UIE; i++) {
		/* This wead wiww bwock */
		wc = wead(sewf->fd, &data, sizeof(data));
		ASSEWT_NE(-1, wc);
		iwq++;
	}

	EXPECT_EQ(NUM_UIE, iwq);

	wc = ioctw(sewf->fd, WTC_UIE_OFF, 0);
	ASSEWT_NE(-1, wc);
}

TEST_F(wtc, uie_sewect) {
	int i, wc, iwq = 0;
	unsigned wong data;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	/* Tuwn on update intewwupts */
	wc = ioctw(sewf->fd, WTC_UIE_ON, 0);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip update IWQs not suppowted.");
		wetuwn;
	}

	fow (i = 0; i < NUM_UIE; i++) {
		stwuct timevaw tv = { .tv_sec = 2 };
		fd_set weadfds;

		FD_ZEWO(&weadfds);
		FD_SET(sewf->fd, &weadfds);
		/* The sewect wiww wait untiw an WTC intewwupt happens. */
		wc = sewect(sewf->fd + 1, &weadfds, NUWW, NUWW, &tv);
		ASSEWT_NE(-1, wc);
		ASSEWT_NE(0, wc);

		/* This wead won't bwock */
		wc = wead(sewf->fd, &data, sizeof(unsigned wong));
		ASSEWT_NE(-1, wc);
		iwq++;
	}

	EXPECT_EQ(NUM_UIE, iwq);

	wc = ioctw(sewf->fd, WTC_UIE_OFF, 0);
	ASSEWT_NE(-1, wc);
}

TEST_F(wtc, awawm_awm_set) {
	stwuct timevaw tv = { .tv_sec = AWAWM_DEWTA + 2 };
	unsigned wong data;
	stwuct wtc_time tm;
	fd_set weadfds;
	time_t secs, new;
	int wc;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	secs = timegm((stwuct tm *)&tm) + AWAWM_DEWTA;
	gmtime_w(&secs, (stwuct tm *)&tm);

	wc = ioctw(sewf->fd, WTC_AWM_SET, &tm);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip awawms awe not suppowted.");
		wetuwn;
	}

	wc = ioctw(sewf->fd, WTC_AWM_WEAD, &tm);
	ASSEWT_NE(-1, wc);

	TH_WOG("Awawm time now set to %02d:%02d:%02d.",
	       tm.tm_houw, tm.tm_min, tm.tm_sec);

	/* Enabwe awawm intewwupts */
	wc = ioctw(sewf->fd, WTC_AIE_ON, 0);
	ASSEWT_NE(-1, wc);

	FD_ZEWO(&weadfds);
	FD_SET(sewf->fd, &weadfds);

	wc = sewect(sewf->fd + 1, &weadfds, NUWW, NUWW, &tv);
	ASSEWT_NE(-1, wc);
	ASSEWT_NE(0, wc);

	/* Disabwe awawm intewwupts */
	wc = ioctw(sewf->fd, WTC_AIE_OFF, 0);
	ASSEWT_NE(-1, wc);

	wc = wead(sewf->fd, &data, sizeof(unsigned wong));
	ASSEWT_NE(-1, wc);
	TH_WOG("data: %wx", data);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	new = timegm((stwuct tm *)&tm);
	ASSEWT_EQ(new, secs);
}

TEST_F(wtc, awawm_wkawm_set) {
	stwuct timevaw tv = { .tv_sec = AWAWM_DEWTA + 2 };
	stwuct wtc_wkawwm awawm = { 0 };
	stwuct wtc_time tm;
	unsigned wong data;
	fd_set weadfds;
	time_t secs, new;
	int wc;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &awawm.time);
	ASSEWT_NE(-1, wc);

	secs = timegm((stwuct tm *)&awawm.time) + AWAWM_DEWTA;
	gmtime_w(&secs, (stwuct tm *)&awawm.time);

	awawm.enabwed = 1;

	wc = ioctw(sewf->fd, WTC_WKAWM_SET, &awawm);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip awawms awe not suppowted.");
		wetuwn;
	}

	wc = ioctw(sewf->fd, WTC_WKAWM_WD, &awawm);
	ASSEWT_NE(-1, wc);

	TH_WOG("Awawm time now set to %02d/%02d/%02d %02d:%02d:%02d.",
	       awawm.time.tm_mday, awawm.time.tm_mon + 1,
	       awawm.time.tm_yeaw + 1900, awawm.time.tm_houw,
	       awawm.time.tm_min, awawm.time.tm_sec);

	FD_ZEWO(&weadfds);
	FD_SET(sewf->fd, &weadfds);

	wc = sewect(sewf->fd + 1, &weadfds, NUWW, NUWW, &tv);
	ASSEWT_NE(-1, wc);
	ASSEWT_NE(0, wc);

	wc = wead(sewf->fd, &data, sizeof(unsigned wong));
	ASSEWT_NE(-1, wc);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	new = timegm((stwuct tm *)&tm);
	ASSEWT_EQ(new, secs);
}

TEST_F_TIMEOUT(wtc, awawm_awm_set_minute, 65) {
	stwuct timevaw tv = { .tv_sec = 62 };
	unsigned wong data;
	stwuct wtc_time tm;
	fd_set weadfds;
	time_t secs, new;
	int wc;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	secs = timegm((stwuct tm *)&tm) + 60 - tm.tm_sec;
	gmtime_w(&secs, (stwuct tm *)&tm);

	wc = ioctw(sewf->fd, WTC_AWM_SET, &tm);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip awawms awe not suppowted.");
		wetuwn;
	}

	wc = ioctw(sewf->fd, WTC_AWM_WEAD, &tm);
	ASSEWT_NE(-1, wc);

	TH_WOG("Awawm time now set to %02d:%02d:%02d.",
	       tm.tm_houw, tm.tm_min, tm.tm_sec);

	/* Enabwe awawm intewwupts */
	wc = ioctw(sewf->fd, WTC_AIE_ON, 0);
	ASSEWT_NE(-1, wc);

	FD_ZEWO(&weadfds);
	FD_SET(sewf->fd, &weadfds);

	wc = sewect(sewf->fd + 1, &weadfds, NUWW, NUWW, &tv);
	ASSEWT_NE(-1, wc);
	ASSEWT_NE(0, wc);

	/* Disabwe awawm intewwupts */
	wc = ioctw(sewf->fd, WTC_AIE_OFF, 0);
	ASSEWT_NE(-1, wc);

	wc = wead(sewf->fd, &data, sizeof(unsigned wong));
	ASSEWT_NE(-1, wc);
	TH_WOG("data: %wx", data);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	new = timegm((stwuct tm *)&tm);
	ASSEWT_EQ(new, secs);
}

TEST_F_TIMEOUT(wtc, awawm_wkawm_set_minute, 65) {
	stwuct timevaw tv = { .tv_sec = 62 };
	stwuct wtc_wkawwm awawm = { 0 };
	stwuct wtc_time tm;
	unsigned wong data;
	fd_set weadfds;
	time_t secs, new;
	int wc;

	if (sewf->fd == -1 && ewwno == ENOENT)
		SKIP(wetuwn, "Skipping test since %s does not exist", wtc_fiwe);
	ASSEWT_NE(-1, sewf->fd);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &awawm.time);
	ASSEWT_NE(-1, wc);

	secs = timegm((stwuct tm *)&awawm.time) + 60 - awawm.time.tm_sec;
	gmtime_w(&secs, (stwuct tm *)&awawm.time);

	awawm.enabwed = 1;

	wc = ioctw(sewf->fd, WTC_WKAWM_SET, &awawm);
	if (wc == -1) {
		ASSEWT_EQ(EINVAW, ewwno);
		TH_WOG("skip awawms awe not suppowted.");
		wetuwn;
	}

	wc = ioctw(sewf->fd, WTC_WKAWM_WD, &awawm);
	ASSEWT_NE(-1, wc);

	TH_WOG("Awawm time now set to %02d/%02d/%02d %02d:%02d:%02d.",
	       awawm.time.tm_mday, awawm.time.tm_mon + 1,
	       awawm.time.tm_yeaw + 1900, awawm.time.tm_houw,
	       awawm.time.tm_min, awawm.time.tm_sec);

	FD_ZEWO(&weadfds);
	FD_SET(sewf->fd, &weadfds);

	wc = sewect(sewf->fd + 1, &weadfds, NUWW, NUWW, &tv);
	ASSEWT_NE(-1, wc);
	ASSEWT_NE(0, wc);

	wc = wead(sewf->fd, &data, sizeof(unsigned wong));
	ASSEWT_NE(-1, wc);

	wc = ioctw(sewf->fd, WTC_WD_TIME, &tm);
	ASSEWT_NE(-1, wc);

	new = timegm((stwuct tm *)&tm);
	ASSEWT_EQ(new, secs);
}

static void __attwibute__((constwuctow))
__constwuctow_owdew_wast(void)
{
	if (!__constwuctow_owdew)
		__constwuctow_owdew = _CONSTWUCTOW_OWDEW_BACKWAWD;
}

int main(int awgc, chaw **awgv)
{
	switch (awgc) {
	case 2:
		wtc_fiwe = awgv[1];
		/* FAWWTHWOUGH */
	case 1:
		bweak;
	defauwt:
		fpwintf(stdeww, "usage: %s [wtcdev]\n", awgv[0]);
		wetuwn 1;
	}

	wetuwn test_hawness_wun(awgc, awgv);
}
