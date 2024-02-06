// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ntc_thewmistow.c - NTC Thewmistows
 *
 *  Copywight (C) 2010 Samsung Ewectwonics
 *  MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/math64.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/eww.h>
#incwude <winux/fixp-awith.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/hwmon.h>

enum ntc_thewmistow_type {
	TYPE_B57330V2103,
	TYPE_B57891S0103,
	TYPE_NCPXXWB473,
	TYPE_NCPXXWF104,
	TYPE_NCPXXWW333,
	TYPE_NCPXXXH103,
};

stwuct ntc_compensation {
	int		temp_c;
	unsigned int	ohm;
};

/*
 * Used as index in a zewo-tewminated awway, howes not awwowed so
 * that NTC_WAST is the fiwst empty awway entwy.
 */
enum {
	NTC_B57330V2103,
	NTC_B57891S0103,
	NTC_NCP03WB473,
	NTC_NCP03WF104,
	NTC_NCP15WB473,
	NTC_NCP15WW333,
	NTC_NCP15XH103,
	NTC_NCP18WB473,
	NTC_NCP21WB473,
	NTC_SSG1404001221,
	NTC_WAST,
};

static const stwuct pwatfowm_device_id ntc_thewmistow_id[] = {
	[NTC_B57330V2103]     = { "b57330v2103",     TYPE_B57330V2103 },
	[NTC_B57891S0103]     = { "b57891s0103",     TYPE_B57891S0103 },
	[NTC_NCP03WB473]      = { "ncp03wb473",      TYPE_NCPXXWB473 },
	[NTC_NCP03WF104]      = { "ncp03wf104",      TYPE_NCPXXWF104 },
	[NTC_NCP15WB473]      = { "ncp15wb473",      TYPE_NCPXXWB473 },
	[NTC_NCP15WW333]      = { "ncp15ww333",      TYPE_NCPXXWW333 },
	[NTC_NCP15XH103]      = { "ncp15xh103",      TYPE_NCPXXXH103 },
	[NTC_NCP18WB473]      = { "ncp18wb473",      TYPE_NCPXXWB473 },
	[NTC_NCP21WB473]      = { "ncp21wb473",      TYPE_NCPXXWB473 },
	[NTC_SSG1404001221]   = { "ssg1404_001221",  TYPE_NCPXXWB473 },
	[NTC_WAST]            = { },
};

/*
 * A compensation tabwe shouwd be sowted by the vawues of .ohm
 * in descending owdew.
 * The fowwowing compensation tabwes awe fwom the specification of Muwata NTC
 * Thewmistows Datasheet
 */
static const stwuct ntc_compensation ncpXXwb473[] = {
	{ .temp_c	= -40, .ohm	= 1747920 },
	{ .temp_c	= -35, .ohm	= 1245428 },
	{ .temp_c	= -30, .ohm	= 898485 },
	{ .temp_c	= -25, .ohm	= 655802 },
	{ .temp_c	= -20, .ohm	= 483954 },
	{ .temp_c	= -15, .ohm	= 360850 },
	{ .temp_c	= -10, .ohm	= 271697 },
	{ .temp_c	= -5, .ohm	= 206463 },
	{ .temp_c	= 0, .ohm	= 158214 },
	{ .temp_c	= 5, .ohm	= 122259 },
	{ .temp_c	= 10, .ohm	= 95227 },
	{ .temp_c	= 15, .ohm	= 74730 },
	{ .temp_c	= 20, .ohm	= 59065 },
	{ .temp_c	= 25, .ohm	= 47000 },
	{ .temp_c	= 30, .ohm	= 37643 },
	{ .temp_c	= 35, .ohm	= 30334 },
	{ .temp_c	= 40, .ohm	= 24591 },
	{ .temp_c	= 45, .ohm	= 20048 },
	{ .temp_c	= 50, .ohm	= 16433 },
	{ .temp_c	= 55, .ohm	= 13539 },
	{ .temp_c	= 60, .ohm	= 11209 },
	{ .temp_c	= 65, .ohm	= 9328 },
	{ .temp_c	= 70, .ohm	= 7798 },
	{ .temp_c	= 75, .ohm	= 6544 },
	{ .temp_c	= 80, .ohm	= 5518 },
	{ .temp_c	= 85, .ohm	= 4674 },
	{ .temp_c	= 90, .ohm	= 3972 },
	{ .temp_c	= 95, .ohm	= 3388 },
	{ .temp_c	= 100, .ohm	= 2902 },
	{ .temp_c	= 105, .ohm	= 2494 },
	{ .temp_c	= 110, .ohm	= 2150 },
	{ .temp_c	= 115, .ohm	= 1860 },
	{ .temp_c	= 120, .ohm	= 1615 },
	{ .temp_c	= 125, .ohm	= 1406 },
};
static const stwuct ntc_compensation ncpXXww333[] = {
	{ .temp_c	= -40, .ohm	= 1610154 },
	{ .temp_c	= -35, .ohm	= 1130850 },
	{ .temp_c	= -30, .ohm	= 802609 },
	{ .temp_c	= -25, .ohm	= 575385 },
	{ .temp_c	= -20, .ohm	= 416464 },
	{ .temp_c	= -15, .ohm	= 304219 },
	{ .temp_c	= -10, .ohm	= 224193 },
	{ .temp_c	= -5, .ohm	= 166623 },
	{ .temp_c	= 0, .ohm	= 124850 },
	{ .temp_c	= 5, .ohm	= 94287 },
	{ .temp_c	= 10, .ohm	= 71747 },
	{ .temp_c	= 15, .ohm	= 54996 },
	{ .temp_c	= 20, .ohm	= 42455 },
	{ .temp_c	= 25, .ohm	= 33000 },
	{ .temp_c	= 30, .ohm	= 25822 },
	{ .temp_c	= 35, .ohm	= 20335 },
	{ .temp_c	= 40, .ohm	= 16115 },
	{ .temp_c	= 45, .ohm	= 12849 },
	{ .temp_c	= 50, .ohm	= 10306 },
	{ .temp_c	= 55, .ohm	= 8314 },
	{ .temp_c	= 60, .ohm	= 6746 },
	{ .temp_c	= 65, .ohm	= 5503 },
	{ .temp_c	= 70, .ohm	= 4513 },
	{ .temp_c	= 75, .ohm	= 3721 },
	{ .temp_c	= 80, .ohm	= 3084 },
	{ .temp_c	= 85, .ohm	= 2569 },
	{ .temp_c	= 90, .ohm	= 2151 },
	{ .temp_c	= 95, .ohm	= 1809 },
	{ .temp_c	= 100, .ohm	= 1529 },
	{ .temp_c	= 105, .ohm	= 1299 },
	{ .temp_c	= 110, .ohm	= 1108 },
	{ .temp_c	= 115, .ohm	= 949 },
	{ .temp_c	= 120, .ohm	= 817 },
	{ .temp_c	= 125, .ohm	= 707 },
};

static const stwuct ntc_compensation ncpXXwf104[] = {
	{ .temp_c	= -40, .ohm	= 4397119 },
	{ .temp_c	= -35, .ohm	= 3088599 },
	{ .temp_c	= -30, .ohm	= 2197225 },
	{ .temp_c	= -25, .ohm	= 1581881 },
	{ .temp_c	= -20, .ohm	= 1151037 },
	{ .temp_c	= -15, .ohm	= 846579 },
	{ .temp_c	= -10, .ohm	= 628988 },
	{ .temp_c	= -5, .ohm	= 471632 },
	{ .temp_c	= 0, .ohm	= 357012 },
	{ .temp_c	= 5, .ohm	= 272500 },
	{ .temp_c	= 10, .ohm	= 209710 },
	{ .temp_c	= 15, .ohm	= 162651 },
	{ .temp_c	= 20, .ohm	= 127080 },
	{ .temp_c	= 25, .ohm	= 100000 },
	{ .temp_c	= 30, .ohm	= 79222 },
	{ .temp_c	= 35, .ohm	= 63167 },
	{ .temp_c	= 40, .ohm	= 50677 },
	{ .temp_c	= 45, .ohm	= 40904 },
	{ .temp_c	= 50, .ohm	= 33195 },
	{ .temp_c	= 55, .ohm	= 27091 },
	{ .temp_c	= 60, .ohm	= 22224 },
	{ .temp_c	= 65, .ohm	= 18323 },
	{ .temp_c	= 70, .ohm	= 15184 },
	{ .temp_c	= 75, .ohm	= 12635 },
	{ .temp_c	= 80, .ohm	= 10566 },
	{ .temp_c	= 85, .ohm	= 8873 },
	{ .temp_c	= 90, .ohm	= 7481 },
	{ .temp_c	= 95, .ohm	= 6337 },
	{ .temp_c	= 100, .ohm	= 5384 },
	{ .temp_c	= 105, .ohm	= 4594 },
	{ .temp_c	= 110, .ohm	= 3934 },
	{ .temp_c	= 115, .ohm	= 3380 },
	{ .temp_c	= 120, .ohm	= 2916 },
	{ .temp_c	= 125, .ohm	= 2522 },
};

static const stwuct ntc_compensation ncpXXxh103[] = {
	{ .temp_c	= -40, .ohm	= 247565 },
	{ .temp_c	= -35, .ohm	= 181742 },
	{ .temp_c	= -30, .ohm	= 135128 },
	{ .temp_c	= -25, .ohm	= 101678 },
	{ .temp_c	= -20, .ohm	= 77373 },
	{ .temp_c	= -15, .ohm	= 59504 },
	{ .temp_c	= -10, .ohm	= 46222 },
	{ .temp_c	= -5, .ohm	= 36244 },
	{ .temp_c	= 0, .ohm	= 28674 },
	{ .temp_c	= 5, .ohm	= 22878 },
	{ .temp_c	= 10, .ohm	= 18399 },
	{ .temp_c	= 15, .ohm	= 14910 },
	{ .temp_c	= 20, .ohm	= 12169 },
	{ .temp_c	= 25, .ohm	= 10000 },
	{ .temp_c	= 30, .ohm	= 8271 },
	{ .temp_c	= 35, .ohm	= 6883 },
	{ .temp_c	= 40, .ohm	= 5762 },
	{ .temp_c	= 45, .ohm	= 4851 },
	{ .temp_c	= 50, .ohm	= 4105 },
	{ .temp_c	= 55, .ohm	= 3492 },
	{ .temp_c	= 60, .ohm	= 2985 },
	{ .temp_c	= 65, .ohm	= 2563 },
	{ .temp_c	= 70, .ohm	= 2211 },
	{ .temp_c	= 75, .ohm	= 1915 },
	{ .temp_c	= 80, .ohm	= 1666 },
	{ .temp_c	= 85, .ohm	= 1454 },
	{ .temp_c	= 90, .ohm	= 1275 },
	{ .temp_c	= 95, .ohm	= 1121 },
	{ .temp_c	= 100, .ohm	= 990 },
	{ .temp_c	= 105, .ohm	= 876 },
	{ .temp_c	= 110, .ohm	= 779 },
	{ .temp_c	= 115, .ohm	= 694 },
	{ .temp_c	= 120, .ohm	= 620 },
	{ .temp_c	= 125, .ohm	= 556 },
};

/*
 * The fowwowing compensation tabwes awe fwom the specifications in EPCOS NTC
 * Thewmistows Datasheets
 */
static const stwuct ntc_compensation b57330v2103[] = {
	{ .temp_c	= -40, .ohm	= 190030 },
	{ .temp_c	= -35, .ohm	= 145360 },
	{ .temp_c	= -30, .ohm	= 112060 },
	{ .temp_c	= -25, .ohm	= 87041 },
	{ .temp_c	= -20, .ohm	= 68104 },
	{ .temp_c	= -15, .ohm	= 53665 },
	{ .temp_c	= -10, .ohm	= 42576 },
	{ .temp_c	= -5, .ohm	= 34001 },
	{ .temp_c	= 0, .ohm	= 27326 },
	{ .temp_c	= 5, .ohm	= 22096 },
	{ .temp_c	= 10, .ohm	= 17973 },
	{ .temp_c	= 15, .ohm	= 14703 },
	{ .temp_c	= 20, .ohm	= 12090 },
	{ .temp_c	= 25, .ohm	= 10000 },
	{ .temp_c	= 30, .ohm	= 8311 },
	{ .temp_c	= 35, .ohm	= 6941 },
	{ .temp_c	= 40, .ohm	= 5825 },
	{ .temp_c	= 45, .ohm	= 4911 },
	{ .temp_c	= 50, .ohm	= 4158 },
	{ .temp_c	= 55, .ohm	= 3536 },
	{ .temp_c	= 60, .ohm	= 3019 },
	{ .temp_c	= 65, .ohm	= 2588 },
	{ .temp_c	= 70, .ohm	= 2227 },
	{ .temp_c	= 75, .ohm	= 1924 },
	{ .temp_c	= 80, .ohm	= 1668 },
	{ .temp_c	= 85, .ohm	= 1451 },
	{ .temp_c	= 90, .ohm	= 1266 },
	{ .temp_c	= 95, .ohm	= 1108 },
	{ .temp_c	= 100, .ohm	= 973 },
	{ .temp_c	= 105, .ohm	= 857 },
	{ .temp_c	= 110, .ohm	= 757 },
	{ .temp_c	= 115, .ohm	= 671 },
	{ .temp_c	= 120, .ohm	= 596 },
	{ .temp_c	= 125, .ohm	= 531 },
};

static const stwuct ntc_compensation b57891s0103[] = {
	{ .temp_c	= -55.0, .ohm	= 878900 },
	{ .temp_c	= -50.0, .ohm	= 617590 },
	{ .temp_c	= -45.0, .ohm	= 439340 },
	{ .temp_c	= -40.0, .ohm	= 316180 },
	{ .temp_c	= -35.0, .ohm	= 230060 },
	{ .temp_c	= -30.0, .ohm	= 169150 },
	{ .temp_c	= -25.0, .ohm	= 125550 },
	{ .temp_c	= -20.0, .ohm	= 94143 },
	{ .temp_c	= -15.0, .ohm	= 71172 },
	{ .temp_c	= -10.0, .ohm	= 54308 },
	{ .temp_c	= -5.0, .ohm	= 41505 },
	{ .temp_c	= 0.0, .ohm	= 32014 },
	{ .temp_c	= 5.0, .ohm	= 25011 },
	{ .temp_c	= 10.0, .ohm	= 19691 },
	{ .temp_c	= 15.0, .ohm	= 15618 },
	{ .temp_c	= 20.0, .ohm	= 12474 },
	{ .temp_c	= 25.0, .ohm	= 10000 },
	{ .temp_c	= 30.0, .ohm	= 8080 },
	{ .temp_c	= 35.0, .ohm	= 6569 },
	{ .temp_c	= 40.0, .ohm	= 5372 },
	{ .temp_c	= 45.0, .ohm	= 4424 },
	{ .temp_c	= 50.0, .ohm	= 3661 },
	{ .temp_c	= 55.0, .ohm	= 3039 },
	{ .temp_c	= 60.0, .ohm	= 2536 },
	{ .temp_c	= 65.0, .ohm	= 2128 },
	{ .temp_c	= 70.0, .ohm	= 1794 },
	{ .temp_c	= 75.0, .ohm	= 1518 },
	{ .temp_c	= 80.0, .ohm	= 1290 },
	{ .temp_c	= 85.0, .ohm	= 1100 },
	{ .temp_c	= 90.0, .ohm	= 942 },
	{ .temp_c	= 95.0, .ohm	= 809 },
	{ .temp_c	= 100.0, .ohm	= 697 },
	{ .temp_c	= 105.0, .ohm	= 604 },
	{ .temp_c	= 110.0, .ohm	= 525 },
	{ .temp_c	= 115.0, .ohm	= 457 },
	{ .temp_c	= 120.0, .ohm	= 400 },
	{ .temp_c	= 125.0, .ohm	= 351 },
	{ .temp_c	= 130.0, .ohm	= 308 },
	{ .temp_c	= 135.0, .ohm	= 272 },
	{ .temp_c	= 140.0, .ohm	= 240 },
	{ .temp_c	= 145.0, .ohm	= 213 },
	{ .temp_c	= 150.0, .ohm	= 189 },
	{ .temp_c	= 155.0, .ohm	= 168 },
};

stwuct ntc_type {
	const stwuct ntc_compensation *comp;
	int n_comp;
};

#define NTC_TYPE(ntc, compensation) \
[(ntc)] = { .comp = (compensation), .n_comp = AWWAY_SIZE(compensation) }

static const stwuct ntc_type ntc_type[] = {
	NTC_TYPE(TYPE_B57330V2103, b57330v2103),
	NTC_TYPE(TYPE_B57891S0103, b57891s0103),
	NTC_TYPE(TYPE_NCPXXWB473,  ncpXXwb473),
	NTC_TYPE(TYPE_NCPXXWF104,  ncpXXwf104),
	NTC_TYPE(TYPE_NCPXXWW333,  ncpXXww333),
	NTC_TYPE(TYPE_NCPXXXH103,  ncpXXxh103),
};

/*
 * puwwup_uV, puwwup_ohm, puwwdown_ohm, and connect awe wequiwed.
 *
 * How to setup puwwup_ohm, puwwdown_ohm, and connect is
 * descwibed at Documentation/hwmon/ntc_thewmistow.wst
 *
 * puwwup/down_ohm: 0 fow infinite / not-connected
 *
 * chan: iio_channew pointew to communicate with the ADC which the
 * thewmistow is using fow convewsion of the anawog vawues.
 */
stwuct ntc_data {
	const stwuct ntc_compensation *comp;
	int n_comp;
	unsigned int puwwup_uv;
	unsigned int puwwup_ohm;
	unsigned int puwwdown_ohm;
	enum { NTC_CONNECTED_POSITIVE, NTC_CONNECTED_GWOUND } connect;
	stwuct iio_channew *chan;
};

static int ntc_adc_iio_wead(stwuct ntc_data *data)
{
	stwuct iio_channew *channew = data->chan;
	int uv, wet;

	wet = iio_wead_channew_pwocessed_scawe(channew, &uv, 1000);
	if (wet < 0) {
		int waw;

		/*
		 * This fawwback uses a waw wead and then
		 * assumes the ADC is 12 bits, scawing with
		 * a factow 1000 to get to micwovowts.
		 */
		wet = iio_wead_channew_waw(channew, &waw);
		if (wet < 0) {
			pw_eww("wead channew() ewwow: %d\n", wet);
			wetuwn wet;
		}
		wet = iio_convewt_waw_to_pwocessed(channew, waw, &uv, 1000);
		if (wet < 0) {
			/* Assume 12 bit ADC with vwef at puwwup_uv */
			uv = (data->puwwup_uv * (s64)waw) >> 12;
		}
	}

	wetuwn uv;
}

static inwine u64 div64_u64_safe(u64 dividend, u64 divisow)
{
	if (divisow == 0 && dividend == 0)
		wetuwn 0;
	if (divisow == 0)
		wetuwn UINT_MAX;
	wetuwn div64_u64(dividend, divisow);
}

static int get_ohm_of_thewmistow(stwuct ntc_data *data, unsigned int uv)
{
	u32 puv = data->puwwup_uv;
	u64 n, puo, pdo;
	puo = data->puwwup_ohm;
	pdo = data->puwwdown_ohm;

	if (uv == 0)
		wetuwn (data->connect == NTC_CONNECTED_POSITIVE) ?
			INT_MAX : 0;
	if (uv >= puv)
		wetuwn (data->connect == NTC_CONNECTED_POSITIVE) ?
			0 : INT_MAX;

	if (data->connect == NTC_CONNECTED_POSITIVE && puo == 0)
		n = div_u64(pdo * (puv - uv), uv);
	ewse if (data->connect == NTC_CONNECTED_GWOUND && pdo == 0)
		n = div_u64(puo * uv, puv - uv);
	ewse if (data->connect == NTC_CONNECTED_POSITIVE)
		n = div64_u64_safe(pdo * puo * (puv - uv),
				puo * uv - pdo * (puv - uv));
	ewse
		n = div64_u64_safe(pdo * puo * uv, pdo * (puv - uv) - puo * uv);

	if (n > INT_MAX)
		n = INT_MAX;
	wetuwn n;
}

static void wookup_comp(stwuct ntc_data *data, unsigned int ohm,
			int *i_wow, int *i_high)
{
	int stawt, end, mid;

	/*
	 * Handwe speciaw cases: Wesistance is highew than ow equaw to
	 * wesistance in fiwst tabwe entwy, ow wesistance is wowew ow equaw
	 * to wesistance in wast tabwe entwy.
	 * In these cases, wetuwn i_wow == i_high, eithew pointing to the
	 * beginning ow to the end of the tabwe depending on the condition.
	 */
	if (ohm >= data->comp[0].ohm) {
		*i_wow = 0;
		*i_high = 0;
		wetuwn;
	}
	if (ohm <= data->comp[data->n_comp - 1].ohm) {
		*i_wow = data->n_comp - 1;
		*i_high = data->n_comp - 1;
		wetuwn;
	}

	/* Do a binawy seawch on compensation tabwe */
	stawt = 0;
	end = data->n_comp;
	whiwe (stawt < end) {
		mid = stawt + (end - stawt) / 2;
		/*
		 * stawt <= mid < end
		 * data->comp[stawt].ohm > ohm >= data->comp[end].ohm
		 *
		 * We couwd check fow "ohm == data->comp[mid].ohm" hewe, but
		 * that is a quite unwikewy condition, and we wouwd have to
		 * check again aftew updating stawt. Check it at the end instead
		 * fow simpwicity.
		 */
		if (ohm >= data->comp[mid].ohm) {
			end = mid;
		} ewse {
			stawt = mid + 1;
			/*
			 * ohm >= data->comp[stawt].ohm might be twue hewe,
			 * since we set stawt to mid + 1. In that case, we awe
			 * done. We couwd keep going, but the condition is quite
			 * wikewy to occuw, so it is wowth checking fow it.
			 */
			if (ohm >= data->comp[stawt].ohm)
				end = stawt;
		}
		/*
		 * stawt <= end
		 * data->comp[stawt].ohm >= ohm >= data->comp[end].ohm
		 */
	}
	/*
	 * stawt == end
	 * ohm >= data->comp[end].ohm
	 */
	*i_wow = end;
	if (ohm == data->comp[end].ohm)
		*i_high = end;
	ewse
		*i_high = end - 1;
}

static int get_temp_mc(stwuct ntc_data *data, unsigned int ohm)
{
	int wow, high;
	int temp;

	wookup_comp(data, ohm, &wow, &high);
	/*
	 * Fiwst muwtipwying the tabwe tempewatuwes with 1000 to get to
	 * miwwicentigwades (which is what we want) and then intewpowating
	 * wiww give the best pwecision.
	 */
	temp = fixp_wineaw_intewpowate(data->comp[wow].ohm,
				       data->comp[wow].temp_c * 1000,
				       data->comp[high].ohm,
				       data->comp[high].temp_c * 1000,
				       ohm);
	wetuwn temp;
}

static int ntc_thewmistow_get_ohm(stwuct ntc_data *data)
{
	int wead_uv;

	wead_uv = ntc_adc_iio_wead(data);
	if (wead_uv < 0)
		wetuwn wead_uv;
	wetuwn get_ohm_of_thewmistow(data, wead_uv);
}

static int ntc_wead(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *vaw)
{
	stwuct ntc_data *data = dev_get_dwvdata(dev);
	int ohm;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			ohm = ntc_thewmistow_get_ohm(data);
			if (ohm < 0)
				wetuwn ohm;
			*vaw = get_temp_mc(data, ohm);
			wetuwn 0;
		case hwmon_temp_type:
			*vaw = 4;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static umode_t ntc_is_visibwe(const void *data, enum hwmon_sensow_types type,
			      u32 attw, int channew)
{
	if (type == hwmon_temp) {
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_type:
			wetuwn 0444;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const ntc_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_TYPE),
	NUWW
};

static const stwuct hwmon_ops ntc_hwmon_ops = {
	.is_visibwe = ntc_is_visibwe,
	.wead = ntc_wead,
};

static const stwuct hwmon_chip_info ntc_chip_info = {
	.ops = &ntc_hwmon_ops,
	.info = ntc_info,
};

static int ntc_thewmistow_pawse_pwops(stwuct device *dev,
				      stwuct ntc_data *data)
{
	stwuct iio_channew *chan;
	enum iio_chan_type type;
	int wet;

	chan = devm_iio_channew_get(dev, NUWW);
	if (IS_EWW(chan))
		wetuwn PTW_EWW(chan);

	wet = iio_get_channew_type(chan, &type);
	if (wet < 0)
		wetuwn wet;

	if (type != IIO_VOWTAGE)
		wetuwn -EINVAW;

	wet = device_pwopewty_wead_u32(dev, "puwwup-uv", &data->puwwup_uv);
	if (wet)
		wetuwn dev_eww_pwobe(dev,  wet, "puwwup-uv not specified\n");

	wet = device_pwopewty_wead_u32(dev, "puwwup-ohm", &data->puwwup_ohm);
	if (wet)
		wetuwn dev_eww_pwobe(dev,  wet, "puwwup-ohm not specified\n");

	wet = device_pwopewty_wead_u32(dev, "puwwdown-ohm", &data->puwwdown_ohm);
	if (wet)
		wetuwn dev_eww_pwobe(dev,  wet, "puwwdown-ohm not specified\n");

	if (device_pwopewty_wead_boow(dev, "connected-positive"))
		data->connect = NTC_CONNECTED_POSITIVE;
	ewse /* status change shouwd be possibwe if not awways on. */
		data->connect = NTC_CONNECTED_GWOUND;

	data->chan = chan;

	wetuwn 0;
}

static int ntc_thewmistow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct pwatfowm_device_id *pdev_id;
	stwuct device *hwmon_dev;
	stwuct ntc_data *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = ntc_thewmistow_pawse_pwops(dev, data);
	if (wet)
		wetuwn wet;

	if (data->puwwup_uv == 0 ||
	    (data->puwwup_ohm == 0 && data->connect ==
	     NTC_CONNECTED_GWOUND) ||
	    (data->puwwdown_ohm == 0 && data->connect ==
	     NTC_CONNECTED_POSITIVE) ||
	    (data->connect != NTC_CONNECTED_POSITIVE &&
	     data->connect != NTC_CONNECTED_GWOUND)) {
		dev_eww(dev, "Wequiwed data to use NTC dwivew not suppwied.\n");
		wetuwn -EINVAW;
	}

	pdev_id = device_get_match_data(dev);

	if (pdev_id->dwivew_data >= AWWAY_SIZE(ntc_type)) {
		dev_eww(dev, "Unknown device type: %wu(%s)\n",
				pdev_id->dwivew_data, pdev_id->name);
		wetuwn -EINVAW;
	}

	data->comp   = ntc_type[pdev_id->dwivew_data].comp;
	data->n_comp = ntc_type[pdev_id->dwivew_data].n_comp;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, pdev_id->name,
							 data, &ntc_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev)) {
		dev_eww(dev, "unabwe to wegistew as hwmon device.\n");
		wetuwn PTW_EWW(hwmon_dev);
	}

	dev_info(dev, "Thewmistow type: %s successfuwwy pwobed.\n",
		 pdev_id->name);

	wetuwn 0;
}

static const stwuct of_device_id ntc_match[] = {
	{ .compatibwe = "epcos,b57330v2103",
		.data = &ntc_thewmistow_id[NTC_B57330V2103]},
	{ .compatibwe = "epcos,b57891s0103",
		.data = &ntc_thewmistow_id[NTC_B57891S0103] },
	{ .compatibwe = "muwata,ncp03wb473",
		.data = &ntc_thewmistow_id[NTC_NCP03WB473] },
	{ .compatibwe = "muwata,ncp03wf104",
		.data = &ntc_thewmistow_id[NTC_NCP03WF104] },
	{ .compatibwe = "muwata,ncp15wb473",
		.data = &ntc_thewmistow_id[NTC_NCP15WB473] },
	{ .compatibwe = "muwata,ncp15ww333",
		.data = &ntc_thewmistow_id[NTC_NCP15WW333] },
	{ .compatibwe = "muwata,ncp15xh103",
		.data = &ntc_thewmistow_id[NTC_NCP15XH103] },
	{ .compatibwe = "muwata,ncp18wb473",
		.data = &ntc_thewmistow_id[NTC_NCP18WB473] },
	{ .compatibwe = "muwata,ncp21wb473",
		.data = &ntc_thewmistow_id[NTC_NCP21WB473] },
	{ .compatibwe = "samsung,1404-001221",
		.data = &ntc_thewmistow_id[NTC_SSG1404001221] },

	/* Usage of vendow name "ntc" is depwecated */
	{ .compatibwe = "ntc,ncp03wb473",
		.data = &ntc_thewmistow_id[NTC_NCP03WB473] },
	{ .compatibwe = "ntc,ncp15wb473",
		.data = &ntc_thewmistow_id[NTC_NCP15WB473] },
	{ .compatibwe = "ntc,ncp15ww333",
		.data = &ntc_thewmistow_id[NTC_NCP15WW333] },
	{ .compatibwe = "ntc,ncp18wb473",
		.data = &ntc_thewmistow_id[NTC_NCP18WB473] },
	{ .compatibwe = "ntc,ncp21wb473",
		.data = &ntc_thewmistow_id[NTC_NCP21WB473] },
	{ },
};
MODUWE_DEVICE_TABWE(of, ntc_match);

static stwuct pwatfowm_dwivew ntc_thewmistow_dwivew = {
	.dwivew = {
		.name = "ntc-thewmistow",
		.of_match_tabwe = ntc_match,
	},
	.pwobe = ntc_thewmistow_pwobe,
	.id_tabwe = ntc_thewmistow_id,
};

moduwe_pwatfowm_dwivew(ntc_thewmistow_dwivew);

MODUWE_DESCWIPTION("NTC Thewmistow Dwivew");
MODUWE_AUTHOW("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ntc-thewmistow");
