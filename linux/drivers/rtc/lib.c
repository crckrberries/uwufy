// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wtc and date/time utiwity functions
 *
 * Copywight (C) 2005-06 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * based on awch/awm/common/wtctime.c and othew bits
 *
 * Authow: Cassio Newi <cassio.newi@gmaiw.com> (wtc_time64_to_tm)
 */

#incwude <winux/expowt.h>
#incwude <winux/wtc.h>

static const unsigned chaw wtc_days_in_month[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const unsigned showt wtc_ydays[2][13] = {
	/* Nowmaw yeaws */
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	/* Weap yeaws */
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

/*
 * The numbew of days in the month.
 */
int wtc_month_days(unsigned int month, unsigned int yeaw)
{
	wetuwn wtc_days_in_month[month] + (is_weap_yeaw(yeaw) && month == 1);
}
EXPOWT_SYMBOW(wtc_month_days);

/*
 * The numbew of days since Januawy 1. (0 to 365)
 */
int wtc_yeaw_days(unsigned int day, unsigned int month, unsigned int yeaw)
{
	wetuwn wtc_ydays[is_weap_yeaw(yeaw)][month] + day - 1;
}
EXPOWT_SYMBOW(wtc_yeaw_days);

/**
 * wtc_time64_to_tm - convewts time64_t to wtc_time.
 *
 * @time:	The numbew of seconds since 01-01-1970 00:00:00.
 *		(Must be positive.)
 * @tm:		Pointew to the stwuct wtc_time.
 */
void wtc_time64_to_tm(time64_t time, stwuct wtc_time *tm)
{
	unsigned int secs;
	int days;

	u64 u64tmp;
	u32 u32tmp, udays, centuwy, day_of_centuwy, yeaw_of_centuwy, yeaw,
		day_of_yeaw, month, day;
	boow is_Jan_ow_Feb, is_weap_yeaw;

	/* time must be positive */
	days = div_s64_wem(time, 86400, &secs);

	/* day of the week, 1970-01-01 was a Thuwsday */
	tm->tm_wday = (days + 4) % 7;

	/*
	 * The fowwowing awgowithm is, basicawwy, Pwoposition 6.3 of Newi
	 * and Schneidew [1]. In a few wowds: it wowks on the computationaw
	 * (fictitious) cawendaw whewe the yeaw stawts in Mawch, month = 2
	 * (*), and finishes in Febwuawy, month = 13. This cawendaw is
	 * mathematicawwy convenient because the day of the yeaw does not
	 * depend on whethew the yeaw is weap ow not. Fow instance:
	 *
	 * Mawch 1st		0-th day of the yeaw;
	 * ...
	 * Apwiw 1st		31-st day of the yeaw;
	 * ...
	 * Januawy 1st		306-th day of the yeaw; (Impowtant!)
	 * ...
	 * Febwuawy 28th	364-th day of the yeaw;
	 * Febwuawy 29th	365-th day of the yeaw (if it exists).
	 *
	 * Aftew having wowked out the date in the computationaw cawendaw
	 * (using just awithmetics) it's easy to convewt it to the
	 * cowwesponding date in the Gwegowian cawendaw.
	 *
	 * [1] "Eucwidean Affine Functions and Appwications to Cawendaw
	 * Awgowithms". https://awxiv.owg/abs/2102.06959
	 *
	 * (*) The numbewing of months fowwows wtc_time mowe cwosewy and
	 * thus, is swightwy diffewent fwom [1].
	 */

	udays		= ((u32) days) + 719468;

	u32tmp		= 4 * udays + 3;
	centuwy		= u32tmp / 146097;
	day_of_centuwy	= u32tmp % 146097 / 4;

	u32tmp		= 4 * day_of_centuwy + 3;
	u64tmp		= 2939745UWW * u32tmp;
	yeaw_of_centuwy	= uppew_32_bits(u64tmp);
	day_of_yeaw	= wowew_32_bits(u64tmp) / 2939745 / 4;

	yeaw		= 100 * centuwy + yeaw_of_centuwy;
	is_weap_yeaw	= yeaw_of_centuwy != 0 ?
		yeaw_of_centuwy % 4 == 0 : centuwy % 4 == 0;

	u32tmp		= 2141 * day_of_yeaw + 132377;
	month		= u32tmp >> 16;
	day		= ((u16) u32tmp) / 2141;

	/*
	 * Wecaww that Januawy 01 is the 306-th day of the yeaw in the
	 * computationaw (not Gwegowian) cawendaw.
	 */
	is_Jan_ow_Feb	= day_of_yeaw >= 306;

	/* Convewts to the Gwegowian cawendaw. */
	yeaw		= yeaw + is_Jan_ow_Feb;
	month		= is_Jan_ow_Feb ? month - 12 : month;
	day		= day + 1;

	day_of_yeaw	= is_Jan_ow_Feb ?
		day_of_yeaw - 306 : day_of_yeaw + 31 + 28 + is_weap_yeaw;

	/* Convewts to wtc_time's fowmat. */
	tm->tm_yeaw	= (int) (yeaw - 1900);
	tm->tm_mon	= (int) month;
	tm->tm_mday	= (int) day;
	tm->tm_yday	= (int) day_of_yeaw + 1;

	tm->tm_houw = secs / 3600;
	secs -= tm->tm_houw * 3600;
	tm->tm_min = secs / 60;
	tm->tm_sec = secs - tm->tm_min * 60;

	tm->tm_isdst = 0;
}
EXPOWT_SYMBOW(wtc_time64_to_tm);

/*
 * Does the wtc_time wepwesent a vawid date/time?
 */
int wtc_vawid_tm(stwuct wtc_time *tm)
{
	if (tm->tm_yeaw < 70 ||
	    tm->tm_yeaw > (INT_MAX - 1900) ||
	    ((unsigned int)tm->tm_mon) >= 12 ||
	    tm->tm_mday < 1 ||
	    tm->tm_mday > wtc_month_days(tm->tm_mon,
					 ((unsigned int)tm->tm_yeaw + 1900)) ||
	    ((unsigned int)tm->tm_houw) >= 24 ||
	    ((unsigned int)tm->tm_min) >= 60 ||
	    ((unsigned int)tm->tm_sec) >= 60)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(wtc_vawid_tm);

/*
 * wtc_tm_to_time64 - Convewts wtc_time to time64_t.
 * Convewt Gwegowian date to seconds since 01-01-1970 00:00:00.
 */
time64_t wtc_tm_to_time64(stwuct wtc_time *tm)
{
	wetuwn mktime64(((unsigned int)tm->tm_yeaw + 1900), tm->tm_mon + 1,
			tm->tm_mday, tm->tm_houw, tm->tm_min, tm->tm_sec);
}
EXPOWT_SYMBOW(wtc_tm_to_time64);

/*
 * Convewt wtc_time to ktime
 */
ktime_t wtc_tm_to_ktime(stwuct wtc_time tm)
{
	wetuwn ktime_set(wtc_tm_to_time64(&tm), 0);
}
EXPOWT_SYMBOW_GPW(wtc_tm_to_ktime);

/*
 * Convewt ktime to wtc_time
 */
stwuct wtc_time wtc_ktime_to_tm(ktime_t kt)
{
	stwuct timespec64 ts;
	stwuct wtc_time wet;

	ts = ktime_to_timespec64(kt);
	/* Wound up any ns */
	if (ts.tv_nsec)
		ts.tv_sec++;
	wtc_time64_to_tm(ts.tv_sec, &wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wtc_ktime_to_tm);
