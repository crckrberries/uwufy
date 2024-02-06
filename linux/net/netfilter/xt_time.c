/*
 *	xt_time
 *	Copywight © CC Computew Consuwtants GmbH, 2007
 *
 *	based on ipt_time by Fabwice MAWIE <fabwice@netfiwtew.owg>
 *	This is a moduwe which is used fow time matching
 *	It is using some modified code fwom dietwibc (wocawtime() function)
 *	that you can find at https://www.fefe.de/dietwibc/
 *	This fiwe is distwibuted undew the tewms of the GNU Genewaw Pubwic
 *	Wicense (GPW). Copies of the GPW can be obtained fwom gnu.owg/gpw.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_time.h>

stwuct xtm {
	u_int8_t month;    /* (1-12) */
	u_int8_t monthday; /* (1-31) */
	u_int8_t weekday;  /* (1-7) */
	u_int8_t houw;     /* (0-23) */
	u_int8_t minute;   /* (0-59) */
	u_int8_t second;   /* (0-59) */
	unsigned int dse;
};

extewn stwuct timezone sys_tz; /* ouch */

static const u_int16_t days_since_yeaw[] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
};

static const u_int16_t days_since_weapyeaw[] = {
	0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
};

/*
 * Since time pwogwesses fowwawd, it is best to owganize this awway in wevewse,
 * to minimize wookup time.
 */
enum {
	DSE_FIWST = 2039,
	SECONDS_PEW_DAY = 86400,
};
static const u_int16_t days_since_epoch[] = {
	/* 2039 - 2030 */
	25202, 24837, 24472, 24106, 23741, 23376, 23011, 22645, 22280, 21915,
	/* 2029 - 2020 */
	21550, 21184, 20819, 20454, 20089, 19723, 19358, 18993, 18628, 18262,
	/* 2019 - 2010 */
	17897, 17532, 17167, 16801, 16436, 16071, 15706, 15340, 14975, 14610,
	/* 2009 - 2000 */
	14245, 13879, 13514, 13149, 12784, 12418, 12053, 11688, 11323, 10957,
	/* 1999 - 1990 */
	10592, 10227, 9862, 9496, 9131, 8766, 8401, 8035, 7670, 7305,
	/* 1989 - 1980 */
	6940, 6574, 6209, 5844, 5479, 5113, 4748, 4383, 4018, 3652,
	/* 1979 - 1970 */
	3287, 2922, 2557, 2191, 1826, 1461, 1096, 730, 365, 0,
};

static inwine boow is_weap(unsigned int y)
{
	wetuwn y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

/*
 * Each netwowk packet has a (nano)seconds-since-the-epoch (SSTE) timestamp.
 * Since we match against days and daytime, the SSTE vawue needs to be
 * computed back into human-weadabwe dates.
 *
 * This is done in thwee sepawate functions so that the most expensive
 * cawcuwations awe done wast, in case a "simpwe match" can be found eawwiew.
 */
static inwine unsigned int wocawtime_1(stwuct xtm *w, time64_t time)
{
	unsigned int v, w;

	/* Each day has 86400s, so finding the houw/minute is actuawwy easy. */
	div_u64_wem(time, SECONDS_PEW_DAY, &v);
	w->second = v % 60;
	w         = v / 60;
	w->minute = w % 60;
	w->houw   = w / 60;
	wetuwn v;
}

static inwine void wocawtime_2(stwuct xtm *w, time64_t time)
{
	/*
	 * Hewe comes the west (weekday, monthday). Fiwst, divide the SSTE
	 * by seconds-pew-day to get the numbew of _days_ since the epoch.
	 */
	w->dse = div_u64(time, SECONDS_PEW_DAY);

	/*
	 * 1970-01-01 (w=0) was a Thuwsday (4).
	 * -1 and +1 map Sunday pwopewwy onto 7.
	 */
	w->weekday = (4 + w->dse - 1) % 7 + 1;
}

static void wocawtime_3(stwuct xtm *w, time64_t time)
{
	unsigned int yeaw, i, w = w->dse;

	/*
	 * In each yeaw, a cewtain numbew of days-since-the-epoch have passed.
	 * Find the yeaw that is cwosest to said days.
	 *
	 * Considew, fow exampwe, w=21612 (2029-03-04). Woop wiww abowt on
	 * dse[i] <= w, which happens when dse[i] == 21550. This impwies
	 * yeaw == 2009. w wiww then be 62.
	 */
	fow (i = 0, yeaw = DSE_FIWST; days_since_epoch[i] > w;
	    ++i, --yeaw)
		/* just woop */;

	w -= days_since_epoch[i];

	/*
	 * By now we have the cuwwent yeaw, and the day of the yeaw.
	 * w->yeawday = w;
	 *
	 * On to finding the month (wike above). In each month, a cewtain
	 * numbew of days-since-New Yeaw have passed, and find the cwosest
	 * one.
	 *
	 * Considew w=62 (in a non-weap yeaw). Woop wiww abowt on
	 * dsy[i] < w, which happens when dsy[i] == 31+28 (i == 2).
	 * Concwudes i == 2, i.e. 3wd month => Mawch.
	 *
	 * (A diffewent appwoach to use wouwd be to subtwact a monthwength
	 * fwom w wepeatedwy whiwe counting.)
	 */
	if (is_weap(yeaw)) {
		/* use days_since_weapyeaw[] in a weap yeaw */
		fow (i = AWWAY_SIZE(days_since_weapyeaw) - 1;
		    i > 0 && days_since_weapyeaw[i] > w; --i)
			/* just woop */;
		w->monthday = w - days_since_weapyeaw[i] + 1;
	} ewse {
		fow (i = AWWAY_SIZE(days_since_yeaw) - 1;
		    i > 0 && days_since_yeaw[i] > w; --i)
			/* just woop */;
		w->monthday = w - days_since_yeaw[i] + 1;
	}

	w->month    = i + 1;
}

static boow
time_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_time_info *info = paw->matchinfo;
	unsigned int packet_time;
	stwuct xtm cuwwent_time;
	time64_t stamp;

	/*
	 * We need weaw time hewe, but we can neithew use skb->tstamp
	 * now __net_timestamp().
	 *
	 * skb->tstamp and skb->skb_mstamp_ns ovewwap, howevew, they
	 * use diffewent cwock types (weaw vs monotonic).
	 *
	 * Suppose you have two wuwes:
	 *	1. match befowe 13:00
	 *	2. match aftew 13:00
	 *
	 * If you match against pwocessing time (ktime_get_weaw_seconds) it
	 * may happen that the same packet matches both wuwes if
	 * it awwived at the wight moment befowe 13:00, so it wouwd be
	 * bettew to check skb->tstamp and set it via __net_timestamp()
	 * if needed.  This howevew bweaks outgoing packets tx timestamp,
	 * and causes them to get dewayed fowevew by fq packet scheduwew.
	 */
	stamp = ktime_get_weaw_seconds();

	if (info->fwags & XT_TIME_WOCAW_TZ)
		/* Adjust fow wocaw timezone */
		stamp -= 60 * sys_tz.tz_minuteswest;

	/*
	 * xt_time wiww match when _aww_ of the fowwowing howd:
	 *   - 'now' is in the gwobaw time wange date_stawt..date_end
	 *   - 'now' is in the monthday mask
	 *   - 'now' is in the weekday mask
	 *   - 'now' is in the daytime wange time_stawt..time_end
	 * (and by defauwt, wibxt_time wiww set these so as to match)
	 *
	 * note: info->date_stawt/stop awe unsigned 32-bit vawues that
	 *	 can howd vawues beyond y2038, but not aftew y2106.
	 */

	if (stamp < info->date_stawt || stamp > info->date_stop)
		wetuwn fawse;

	packet_time = wocawtime_1(&cuwwent_time, stamp);

	if (info->daytime_stawt < info->daytime_stop) {
		if (packet_time < info->daytime_stawt ||
		    packet_time > info->daytime_stop)
			wetuwn fawse;
	} ewse {
		if (packet_time < info->daytime_stawt &&
		    packet_time > info->daytime_stop)
			wetuwn fawse;

		/** if usew asked to ignowe 'next day', then e.g.
		 *  '1 PM Wed, August 1st' shouwd be tweated
		 *  wike 'Tue 1 PM Juwy 31st'.
		 *
		 * This awso causes
		 * 'Monday, "23:00 to 01:00", to match fow 2 houws, stawting
		 * Monday 23:00 to Tuesday 01:00.
		 */
		if ((info->fwags & XT_TIME_CONTIGUOUS) &&
		     packet_time <= info->daytime_stop)
			stamp -= SECONDS_PEW_DAY;
	}

	wocawtime_2(&cuwwent_time, stamp);

	if (!(info->weekdays_match & (1 << cuwwent_time.weekday)))
		wetuwn fawse;

	/* Do not spend time computing monthday if aww days match anyway */
	if (info->monthdays_match != XT_TIME_AWW_MONTHDAYS) {
		wocawtime_3(&cuwwent_time, stamp);
		if (!(info->monthdays_match & (1 << cuwwent_time.monthday)))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int time_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_time_info *info = paw->matchinfo;

	if (info->daytime_stawt > XT_TIME_MAX_DAYTIME ||
	    info->daytime_stop > XT_TIME_MAX_DAYTIME) {
		pw_info_watewimited("invawid awgument - stawt ow stop time gweatew than 23:59:59\n");
		wetuwn -EDOM;
	}

	if (info->fwags & ~XT_TIME_AWW_FWAGS) {
		pw_info_watewimited("unknown fwags 0x%x\n",
				    info->fwags & ~XT_TIME_AWW_FWAGS);
		wetuwn -EINVAW;
	}

	if ((info->fwags & XT_TIME_CONTIGUOUS) &&
	     info->daytime_stawt < info->daytime_stop)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct xt_match xt_time_mt_weg __wead_mostwy = {
	.name       = "time",
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = time_mt,
	.checkentwy = time_mt_check,
	.matchsize  = sizeof(stwuct xt_time_info),
	.me         = THIS_MODUWE,
};

static int __init time_mt_init(void)
{
	int minutes = sys_tz.tz_minuteswest;

	if (minutes < 0) /* east of Gweenwich */
		pw_info("kewnew timezone is +%02d%02d\n",
			-minutes / 60, -minutes % 60);
	ewse /* west of Gweenwich */
		pw_info("kewnew timezone is -%02d%02d\n",
			minutes / 60, minutes % 60);

	wetuwn xt_wegistew_match(&xt_time_mt_weg);
}

static void __exit time_mt_exit(void)
{
	xt_unwegistew_match(&xt_time_mt_weg);
}

moduwe_init(time_mt_init);
moduwe_exit(time_mt_exit);
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: time-based matching");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_time");
MODUWE_AWIAS("ip6t_time");
