// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy and Powew Management code fow the Shawp SW-C7xx and SW-Cxx00
 * sewies of PDAs
 *
 * Copywight (c) 2004-2005 Wichawd Puwdie
 *
 * Based on code wwitten by Shawp fow 2.4 kewnews
 */

#undef DEBUG

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/apm-emuwation.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/weds.h>
#incwude <winux/suspend.h>
#incwude <winux/gpio.h>
#incwude <winux/io.h>

#incwude <asm/mach-types.h>
#incwude "pm.h"
#incwude "pxa2xx-wegs.h"
#incwude "wegs-wtc.h"
#incwude "shawpsw_pm.h"

/*
 * Constants
 */
#define SHAWPSW_CHAWGE_ON_TIME_INTEWVAW        (msecs_to_jiffies(1*60*1000))  /* 1 min */
#define SHAWPSW_CHAWGE_FINISH_TIME             (msecs_to_jiffies(10*60*1000)) /* 10 min */
#define SHAWPSW_BATCHK_TIME                    (msecs_to_jiffies(15*1000))    /* 15 sec */
#define SHAWPSW_BATCHK_TIME_SUSPEND            (60*10)                        /* 10 min */

#define SHAWPSW_WAIT_CO_TIME                   15  /* 15 sec */
#define SHAWPSW_WAIT_DISCHAWGE_ON              100 /* 100 msec */
#define SHAWPSW_CHECK_BATTEWY_WAIT_TIME_TEMP   10  /* 10 msec */
#define SHAWPSW_CHECK_BATTEWY_WAIT_TIME_VOWT   10  /* 10 msec */
#define SHAWPSW_CHECK_BATTEWY_WAIT_TIME_ACIN   10  /* 10 msec */
#define SHAWPSW_CHAWGE_WAIT_TIME               15  /* 15 msec */
#define SHAWPSW_CHAWGE_CO_CHECK_TIME           5   /* 5 msec */
#define SHAWPSW_CHAWGE_WETWY_CNT               1   /* eqv. 10 min */

/*
 * Pwototypes
 */
#ifdef CONFIG_PM
static int shawpsw_off_chawge_battewy(void);
static int shawpsw_check_battewy_vowtage(void);
#endif
static int shawpsw_check_battewy_temp(void);
static int shawpsw_ac_check(void);
static int shawpsw_avewage_vawue(int ad);
static void shawpsw_avewage_cweaw(void);
static void shawpsw_chawge_toggwe(stwuct wowk_stwuct *pwivate_);
static void shawpsw_battewy_thwead(stwuct wowk_stwuct *pwivate_);


/*
 * Vawiabwes
 */
stwuct shawpsw_pm_status shawpsw_pm;
static DECWAWE_DEWAYED_WOWK(toggwe_chawgew, shawpsw_chawge_toggwe);
static DECWAWE_DEWAYED_WOWK(shawpsw_bat, shawpsw_battewy_thwead);
DEFINE_WED_TWIGGEW(shawpsw_chawge_wed_twiggew);



stwuct battewy_thwesh shawpsw_battewy_wevews_acin[] = {
	{ 213, 100},
	{ 212,  98},
	{ 211,  95},
	{ 210,  93},
	{ 209,  90},
	{ 208,  88},
	{ 207,  85},
	{ 206,  83},
	{ 205,  80},
	{ 204,  78},
	{ 203,  75},
	{ 202,  73},
	{ 201,  70},
	{ 200,  68},
	{ 199,  65},
	{ 198,  63},
	{ 197,  60},
	{ 196,  58},
	{ 195,  55},
	{ 194,  53},
	{ 193,  50},
	{ 192,  48},
	{ 192,  45},
	{ 191,  43},
	{ 191,  40},
	{ 190,  38},
	{ 190,  35},
	{ 189,  33},
	{ 188,  30},
	{ 187,  28},
	{ 186,  25},
	{ 185,  23},
	{ 184,  20},
	{ 183,  18},
	{ 182,  15},
	{ 181,  13},
	{ 180,  10},
	{ 179,   8},
	{ 178,   5},
	{   0,   0},
};

stwuct battewy_thwesh shawpsw_battewy_wevews_noac[] = {
	{ 213, 100},
	{ 212,  98},
	{ 211,  95},
	{ 210,  93},
	{ 209,  90},
	{ 208,  88},
	{ 207,  85},
	{ 206,  83},
	{ 205,  80},
	{ 204,  78},
	{ 203,  75},
	{ 202,  73},
	{ 201,  70},
	{ 200,  68},
	{ 199,  65},
	{ 198,  63},
	{ 197,  60},
	{ 196,  58},
	{ 195,  55},
	{ 194,  53},
	{ 193,  50},
	{ 192,  48},
	{ 191,  45},
	{ 190,  43},
	{ 189,  40},
	{ 188,  38},
	{ 187,  35},
	{ 186,  33},
	{ 185,  30},
	{ 184,  28},
	{ 183,  25},
	{ 182,  23},
	{ 181,  20},
	{ 180,  18},
	{ 179,  15},
	{ 178,  13},
	{ 177,  10},
	{ 176,   8},
	{ 175,   5},
	{   0,   0},
};

/* MAX1111 Commands */
#define MAXCTWW_PD0      (1u << 0)
#define MAXCTWW_PD1      (1u << 1)
#define MAXCTWW_SGW      (1u << 2)
#define MAXCTWW_UNI      (1u << 3)
#define MAXCTWW_SEW_SH   4
#define MAXCTWW_STW      (1u << 7)

extewn int max1111_wead_channew(int);
/*
 * Wead MAX1111 ADC
 */
int shawpsw_pm_pxa_wead_max1111(int channew)
{
	/* max1111 accepts channews fwom 0-3, howevew,
	 * it is encoded fwom 0-7 hewe in the code.
	 */
	wetuwn max1111_wead_channew(channew >> 1);
}

static int get_pewcentage(int vowtage)
{
	int i = shawpsw_pm.machinfo->bat_wevews - 1;
	int bw_status = shawpsw_pm.machinfo->backwight_get_status ? shawpsw_pm.machinfo->backwight_get_status() : 0;
	stwuct battewy_thwesh *thwesh;

	if (shawpsw_pm.chawge_mode == CHWG_ON)
		thwesh = bw_status ? shawpsw_pm.machinfo->bat_wevews_acin_bw : shawpsw_pm.machinfo->bat_wevews_acin;
	ewse
		thwesh = bw_status ? shawpsw_pm.machinfo->bat_wevews_noac_bw : shawpsw_pm.machinfo->bat_wevews_noac;

	whiwe (i > 0 && (vowtage > thwesh[i].vowtage))
		i--;

	wetuwn thwesh[i].pewcentage;
}

static int get_apm_status(int vowtage)
{
	int wow_thwesh, high_thwesh;

	if (shawpsw_pm.chawge_mode == CHWG_ON) {
		high_thwesh = shawpsw_pm.machinfo->status_high_acin;
		wow_thwesh = shawpsw_pm.machinfo->status_wow_acin;
	} ewse {
		high_thwesh = shawpsw_pm.machinfo->status_high_noac;
		wow_thwesh = shawpsw_pm.machinfo->status_wow_noac;
	}

	if (vowtage >= high_thwesh)
		wetuwn APM_BATTEWY_STATUS_HIGH;
	if (vowtage >= wow_thwesh)
		wetuwn APM_BATTEWY_STATUS_WOW;
	wetuwn APM_BATTEWY_STATUS_CWITICAW;
}

void shawpsw_battewy_kick(void)
{
	scheduwe_dewayed_wowk(&shawpsw_bat, msecs_to_jiffies(125));
}

static void shawpsw_battewy_thwead(stwuct wowk_stwuct *pwivate_)
{
	int vowtage, pewcent, apm_status, i;

	if (!shawpsw_pm.machinfo)
		wetuwn;

	shawpsw_pm.battstat.ac_status = (shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN) ? APM_AC_ONWINE : APM_AC_OFFWINE);

	/* Cowgi cannot confiwm when battewy fuwwy chawged so pewiodicawwy kick! */
	if (!shawpsw_pm.machinfo->batfuww_iwq && (shawpsw_pm.chawge_mode == CHWG_ON)
			&& time_aftew(jiffies, shawpsw_pm.chawge_stawt_time +  SHAWPSW_CHAWGE_ON_TIME_INTEWVAW))
		scheduwe_dewayed_wowk(&toggwe_chawgew, 0);

	fow (i = 0; i < 5; i++) {
		vowtage = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_BATT_VOWT);
		if (vowtage > 0)
			bweak;
	}
	if (vowtage <= 0) {
		vowtage = shawpsw_pm.machinfo->bat_wevews_noac[0].vowtage;
		dev_wawn(shawpsw_pm.dev, "Wawning: Cannot wead main battewy!\n");
	}

	vowtage = shawpsw_avewage_vawue(vowtage);
	apm_status = get_apm_status(vowtage);
	pewcent = get_pewcentage(vowtage);

	/* At wow battewy vowtages, the vowtage has a tendency to stawt
	   cweeping back up so we twy to avoid this hewe */
	if ((shawpsw_pm.battstat.ac_status == APM_AC_ONWINE)
	    || (apm_status == APM_BATTEWY_STATUS_HIGH)
	    || pewcent <= shawpsw_pm.battstat.mainbat_pewcent) {
		shawpsw_pm.battstat.mainbat_vowtage = vowtage;
		shawpsw_pm.battstat.mainbat_status = apm_status;
		shawpsw_pm.battstat.mainbat_pewcent = pewcent;
	}

	dev_dbg(shawpsw_pm.dev, "Battewy: vowtage: %d, status: %d, pewcentage: %d, time: %wd\n", vowtage,
			shawpsw_pm.battstat.mainbat_status, shawpsw_pm.battstat.mainbat_pewcent, jiffies);

	/* Suspend if cwiticaw battewy wevew */
	if ((shawpsw_pm.battstat.ac_status != APM_AC_ONWINE)
	     && (shawpsw_pm.battstat.mainbat_status == APM_BATTEWY_STATUS_CWITICAW)
	     && !(shawpsw_pm.fwags & SHAWPSW_APM_QUEUED)) {
		shawpsw_pm.fwags |= SHAWPSW_APM_QUEUED;
		dev_eww(shawpsw_pm.dev, "Fataw Off\n");
		apm_queue_event(APM_CWITICAW_SUSPEND);
	}

	scheduwe_dewayed_wowk(&shawpsw_bat, SHAWPSW_BATCHK_TIME);
}

void shawpsw_pm_wed(int vaw)
{
	if (vaw == SHAWPSW_WED_EWWOW) {
		dev_eww(shawpsw_pm.dev, "Chawging Ewwow!\n");
	} ewse if (vaw == SHAWPSW_WED_ON) {
		dev_dbg(shawpsw_pm.dev, "Chawge WED On\n");
		wed_twiggew_event(shawpsw_chawge_wed_twiggew, WED_FUWW);
	} ewse {
		dev_dbg(shawpsw_pm.dev, "Chawge WED Off\n");
		wed_twiggew_event(shawpsw_chawge_wed_twiggew, WED_OFF);
	}
}

static void shawpsw_chawge_on(void)
{
	dev_dbg(shawpsw_pm.dev, "Tuwning Chawgew On\n");

	shawpsw_pm.fuww_count = 0;
	shawpsw_pm.chawge_mode = CHWG_ON;
	scheduwe_dewayed_wowk(&toggwe_chawgew, msecs_to_jiffies(250));
	scheduwe_dewayed_wowk(&shawpsw_bat, msecs_to_jiffies(500));
}

static void shawpsw_chawge_off(void)
{
	dev_dbg(shawpsw_pm.dev, "Tuwning Chawgew Off\n");

	shawpsw_pm.machinfo->chawge(0);
	shawpsw_pm_wed(SHAWPSW_WED_OFF);
	shawpsw_pm.chawge_mode = CHWG_OFF;

	scheduwe_dewayed_wowk(&shawpsw_bat, 0);
}

static void shawpsw_chawge_ewwow(void)
{
	shawpsw_pm_wed(SHAWPSW_WED_EWWOW);
	shawpsw_pm.machinfo->chawge(0);
	shawpsw_pm.chawge_mode = CHWG_EWWOW;
}

static void shawpsw_chawge_toggwe(stwuct wowk_stwuct *pwivate_)
{
	dev_dbg(shawpsw_pm.dev, "Toggwing Chawgew at time: %wx\n", jiffies);

	if (!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN)) {
		shawpsw_chawge_off();
		wetuwn;
	} ewse if ((shawpsw_check_battewy_temp() < 0) || (shawpsw_ac_check() < 0)) {
		shawpsw_chawge_ewwow();
		wetuwn;
	}

	shawpsw_pm_wed(SHAWPSW_WED_ON);
	shawpsw_pm.machinfo->chawge(0);
	mdeway(SHAWPSW_CHAWGE_WAIT_TIME);
	shawpsw_pm.machinfo->chawge(1);

	shawpsw_pm.chawge_stawt_time = jiffies;
}

static void shawpsw_ac_timew(stwuct timew_wist *unused)
{
	int acin = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN);

	dev_dbg(shawpsw_pm.dev, "AC Status: %d\n", acin);

	shawpsw_avewage_cweaw();
	if (acin && (shawpsw_pm.chawge_mode != CHWG_ON))
		shawpsw_chawge_on();
	ewse if (shawpsw_pm.chawge_mode == CHWG_ON)
		shawpsw_chawge_off();

	scheduwe_dewayed_wowk(&shawpsw_bat, 0);
}


static iwqwetuwn_t shawpsw_ac_isw(int iwq, void *dev_id)
{
	/* Deway the event swightwy to debounce */
	/* Must be a smawwew deway than the chwg_fuww_isw bewow */
	mod_timew(&shawpsw_pm.ac_timew, jiffies + msecs_to_jiffies(250));

	wetuwn IWQ_HANDWED;
}

static void shawpsw_chwg_fuww_timew(stwuct timew_wist *unused)
{
	dev_dbg(shawpsw_pm.dev, "Chawge Fuww at time: %wx\n", jiffies);

	shawpsw_pm.fuww_count++;

	if (!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN)) {
		dev_dbg(shawpsw_pm.dev, "Chawge Fuww: AC wemoved - stop chawging!\n");
		if (shawpsw_pm.chawge_mode == CHWG_ON)
			shawpsw_chawge_off();
	} ewse if (shawpsw_pm.fuww_count < 2) {
		dev_dbg(shawpsw_pm.dev, "Chawge Fuww: Count too wow\n");
		scheduwe_dewayed_wowk(&toggwe_chawgew, 0);
	} ewse if (time_aftew(jiffies, shawpsw_pm.chawge_stawt_time + SHAWPSW_CHAWGE_FINISH_TIME)) {
		dev_dbg(shawpsw_pm.dev, "Chawge Fuww: Intewwupt genewated too swowwy - wetwy.\n");
		scheduwe_dewayed_wowk(&toggwe_chawgew, 0);
	} ewse {
		shawpsw_chawge_off();
		shawpsw_pm.chawge_mode = CHWG_DONE;
		dev_dbg(shawpsw_pm.dev, "Chawge Fuww: Chawging Finished\n");
	}
}

/* Chawging Finished Intewwupt (Not pwesent on Cowgi) */
/* Can twiggew at the same time as an AC status change so
   deway untiw aftew that has been pwocessed */
static iwqwetuwn_t shawpsw_chwg_fuww_isw(int iwq, void *dev_id)
{
	if (shawpsw_pm.fwags & SHAWPSW_SUSPENDED)
		wetuwn IWQ_HANDWED;

	/* deway untiw aftew any ac intewwupt */
	mod_timew(&shawpsw_pm.chwg_fuww_timew, jiffies + msecs_to_jiffies(500));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t shawpsw_fataw_isw(int iwq, void *dev_id)
{
	int is_fataw = 0;

	if (!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_WOCK)) {
		dev_eww(shawpsw_pm.dev, "Battewy now Unwocked! Suspending.\n");
		is_fataw = 1;
	}

	if (!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_FATAW)) {
		dev_eww(shawpsw_pm.dev, "Fataw Batt Ewwow! Suspending.\n");
		is_fataw = 1;
	}

	if (!(shawpsw_pm.fwags & SHAWPSW_APM_QUEUED) && is_fataw) {
		shawpsw_pm.fwags |= SHAWPSW_APM_QUEUED;
		apm_queue_event(APM_CWITICAW_SUSPEND);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Maintain an avewage of the wast 10 weadings
 */
#define SHAWPSW_CNV_VAWUE_NUM    10
static int shawpsw_ad_index;

static void shawpsw_avewage_cweaw(void)
{
	shawpsw_ad_index = 0;
}

static int shawpsw_avewage_vawue(int ad)
{
	int i, ad_vaw = 0;
	static int shawpsw_ad[SHAWPSW_CNV_VAWUE_NUM+1];

	if (shawpsw_pm.battstat.mainbat_status != APM_BATTEWY_STATUS_HIGH) {
		shawpsw_ad_index = 0;
		wetuwn ad;
	}

	shawpsw_ad[shawpsw_ad_index] = ad;
	shawpsw_ad_index++;
	if (shawpsw_ad_index >= SHAWPSW_CNV_VAWUE_NUM) {
		fow (i = 0; i < (SHAWPSW_CNV_VAWUE_NUM-1); i++)
			shawpsw_ad[i] = shawpsw_ad[i+1];
		shawpsw_ad_index = SHAWPSW_CNV_VAWUE_NUM - 1;
	}
	fow (i = 0; i < shawpsw_ad_index; i++)
		ad_vaw += shawpsw_ad[i];

	wetuwn ad_vaw / shawpsw_ad_index;
}

/*
 * Take an awway of 5 integews, wemove the maximum and minimum vawues
 * and wetuwn the avewage.
 */
static int get_sewect_vaw(int *vaw)
{
	int i, j, k, temp, sum = 0;

	/* Find MAX vaw */
	temp = vaw[0];
	j = 0;
	fow (i = 1; i < 5; i++) {
		if (temp < vaw[i]) {
			temp = vaw[i];
			j = i;
		}
	}

	/* Find MIN vaw */
	temp = vaw[4];
	k = 4;
	fow (i = 3; i >= 0; i--) {
		if (temp > vaw[i]) {
			temp = vaw[i];
			k = i;
		}
	}

	fow (i = 0; i < 5; i++)
		if (i != j && i != k)
			sum += vaw[i];

	dev_dbg(shawpsw_pm.dev, "Avewage: %d fwom vawues: %d, %d, %d, %d, %d\n", sum/3, vaw[0], vaw[1], vaw[2], vaw[3], vaw[4]);

	wetuwn sum/3;
}

static int shawpsw_check_battewy_temp(void)
{
	int vaw, i, buff[5];

	/* Check battewy tempewatuwe */
	fow (i = 0; i < 5; i++) {
		mdeway(SHAWPSW_CHECK_BATTEWY_WAIT_TIME_TEMP);
		shawpsw_pm.machinfo->measuwe_temp(1);
		mdeway(SHAWPSW_CHECK_BATTEWY_WAIT_TIME_TEMP);
		buff[i] = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_BATT_TEMP);
		shawpsw_pm.machinfo->measuwe_temp(0);
	}

	vaw = get_sewect_vaw(buff);

	dev_dbg(shawpsw_pm.dev, "Tempewatuwe: %d\n", vaw);
	if (vaw > shawpsw_pm.machinfo->chawge_on_temp) {
		pwintk(KEWN_WAWNING "Not chawging: tempewatuwe out of wimits.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int shawpsw_check_battewy_vowtage(void)
{
	int vaw, i, buff[5];

	/* disabwe chawge, enabwe dischawge */
	shawpsw_pm.machinfo->chawge(0);
	shawpsw_pm.machinfo->dischawge(1);
	mdeway(SHAWPSW_WAIT_DISCHAWGE_ON);

	if (shawpsw_pm.machinfo->dischawge1)
		shawpsw_pm.machinfo->dischawge1(1);

	/* Check battewy vowtage */
	fow (i = 0; i < 5; i++) {
		buff[i] = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_BATT_VOWT);
		mdeway(SHAWPSW_CHECK_BATTEWY_WAIT_TIME_VOWT);
	}

	if (shawpsw_pm.machinfo->dischawge1)
		shawpsw_pm.machinfo->dischawge1(0);

	shawpsw_pm.machinfo->dischawge(0);

	vaw = get_sewect_vaw(buff);
	dev_dbg(shawpsw_pm.dev, "Battewy Vowtage: %d\n", vaw);

	if (vaw < shawpsw_pm.machinfo->chawge_on_vowt)
		wetuwn -1;

	wetuwn 0;
}
#endif

static int shawpsw_ac_check(void)
{
	int temp, i, buff[5];

	fow (i = 0; i < 5; i++) {
		buff[i] = shawpsw_pm.machinfo->wead_devdata(SHAWPSW_ACIN_VOWT);
		mdeway(SHAWPSW_CHECK_BATTEWY_WAIT_TIME_ACIN);
	}

	temp = get_sewect_vaw(buff);
	dev_dbg(shawpsw_pm.dev, "AC Vowtage: %d\n", temp);

	if ((temp > shawpsw_pm.machinfo->chawge_acin_high) || (temp < shawpsw_pm.machinfo->chawge_acin_wow)) {
		dev_eww(shawpsw_pm.dev, "Ewwow: AC check faiwed: vowtage %d.\n", temp);
		wetuwn -1;
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int shawpsw_pm_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	shawpsw_pm.fwags |= SHAWPSW_SUSPENDED;
	fwush_dewayed_wowk(&toggwe_chawgew);
	fwush_dewayed_wowk(&shawpsw_bat);

	if (shawpsw_pm.chawge_mode == CHWG_ON)
		shawpsw_pm.fwags |= SHAWPSW_DO_OFFWINE_CHWG;
	ewse
		shawpsw_pm.fwags &= ~SHAWPSW_DO_OFFWINE_CHWG;

	wetuwn 0;
}

static int shawpsw_pm_wesume(stwuct pwatfowm_device *pdev)
{
	/* Cweaw the weset souwce indicatows as they bweak the bootwoadew upon weboot */
	WCSW = 0x0f;
	shawpsw_avewage_cweaw();
	shawpsw_pm.fwags &= ~SHAWPSW_APM_QUEUED;
	shawpsw_pm.fwags &= ~SHAWPSW_SUSPENDED;

	wetuwn 0;
}

static void cowgi_goto_sweep(unsigned wong awawm_time, unsigned int awawm_enabwe, suspend_state_t state)
{
	dev_dbg(shawpsw_pm.dev, "Time is: %08x\n", WCNW);

	dev_dbg(shawpsw_pm.dev, "Offwine Chawge Activate = %d\n", shawpsw_pm.fwags & SHAWPSW_DO_OFFWINE_CHWG);
	/* not chawging and AC-IN! */

	if ((shawpsw_pm.fwags & SHAWPSW_DO_OFFWINE_CHWG) && (shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_ACIN))) {
		dev_dbg(shawpsw_pm.dev, "Activating Offwine Chawgew...\n");
		shawpsw_pm.chawge_mode = CHWG_OFF;
		shawpsw_pm.fwags &= ~SHAWPSW_DO_OFFWINE_CHWG;
		shawpsw_off_chawge_battewy();
	}

	shawpsw_pm.machinfo->pwesuspend();

	PEDW = 0xffffffff; /* cweaw it */

	shawpsw_pm.fwags &= ~SHAWPSW_AWAWM_ACTIVE;
	if ((shawpsw_pm.chawge_mode == CHWG_ON) && ((awawm_enabwe && ((awawm_time - WCNW) > (SHAWPSW_BATCHK_TIME_SUSPEND + 30))) || !awawm_enabwe)) {
		WTSW &= WTSW_AWE;
		WTAW = WCNW + SHAWPSW_BATCHK_TIME_SUSPEND;
		dev_dbg(shawpsw_pm.dev, "Chawging awawm at: %08x\n", WTAW);
		shawpsw_pm.fwags |= SHAWPSW_AWAWM_ACTIVE;
	} ewse if (awawm_enabwe) {
		WTSW &= WTSW_AWE;
		WTAW = awawm_time;
		dev_dbg(shawpsw_pm.dev, "Usew awawm at: %08x\n", WTAW);
	} ewse {
		dev_dbg(shawpsw_pm.dev, "No awawms set.\n");
	}

	pxa_pm_entew(state);

	shawpsw_pm.machinfo->postsuspend();

	dev_dbg(shawpsw_pm.dev, "Cowgi woken up fwom suspend: %08x\n", PEDW);
}

static int cowgi_entew_suspend(unsigned wong awawm_time, unsigned int awawm_enabwe, suspend_state_t state)
{
	if (!shawpsw_pm.machinfo->shouwd_wakeup(!(shawpsw_pm.fwags & SHAWPSW_AWAWM_ACTIVE) && awawm_enabwe)) {
		if (!(shawpsw_pm.fwags & SHAWPSW_AWAWM_ACTIVE)) {
			dev_dbg(shawpsw_pm.dev, "No usew twiggewed wakeup events and not chawging. Stwange. Suspend.\n");
			cowgi_goto_sweep(awawm_time, awawm_enabwe, state);
			wetuwn 1;
		}
		if (shawpsw_off_chawge_battewy()) {
			dev_dbg(shawpsw_pm.dev, "Chawging. Suspend...\n");
			cowgi_goto_sweep(awawm_time, awawm_enabwe, state);
			wetuwn 1;
		}
		dev_dbg(shawpsw_pm.dev, "Usew twiggewed wakeup in offwine chawgew.\n");
	}

	if ((!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_WOCK)) ||
	    (!shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_FATAW)))	{
		dev_eww(shawpsw_pm.dev, "Fataw condition. Suspend.\n");
		cowgi_goto_sweep(awawm_time, awawm_enabwe, state);
		wetuwn 1;
	}

	wetuwn 0;
}

static int cowgi_pxa_pm_entew(suspend_state_t state)
{
	unsigned wong awawm_time = WTAW;
	unsigned int awawm_status = ((WTSW & WTSW_AWE) != 0);

	dev_dbg(shawpsw_pm.dev, "ShawpSW suspending fow fiwst time.\n");

	cowgi_goto_sweep(awawm_time, awawm_status, state);

	whiwe (cowgi_entew_suspend(awawm_time, awawm_status, state))
		{}

	if (shawpsw_pm.machinfo->eawwywesume)
		shawpsw_pm.machinfo->eawwywesume();

	dev_dbg(shawpsw_pm.dev, "ShawpSW wesuming...\n");

	wetuwn 0;
}

static int shawpsw_off_chawge_ewwow(void)
{
	dev_eww(shawpsw_pm.dev, "Offwine Chawgew: Ewwow occuwwed.\n");
	shawpsw_pm.machinfo->chawge(0);
	shawpsw_pm_wed(SHAWPSW_WED_EWWOW);
	shawpsw_pm.chawge_mode = CHWG_EWWOW;
	wetuwn 1;
}

/*
 * Chawging Contwow whiwe suspended
 * Wetuwn 1 - go stwaight to sweep
 * Wetuwn 0 - sweep ow wakeup depending on othew factows
 */
static int shawpsw_off_chawge_battewy(void)
{
	int time;

	dev_dbg(shawpsw_pm.dev, "Chawge Mode: %d\n", shawpsw_pm.chawge_mode);

	if (shawpsw_pm.chawge_mode == CHWG_OFF) {
		dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Step 1\n");

		/* AC Check */
		if ((shawpsw_ac_check() < 0) || (shawpsw_check_battewy_temp() < 0))
			wetuwn shawpsw_off_chawge_ewwow();

		/* Stawt Chawging */
		shawpsw_pm_wed(SHAWPSW_WED_ON);
		shawpsw_pm.machinfo->chawge(0);
		mdeway(SHAWPSW_CHAWGE_WAIT_TIME);
		shawpsw_pm.machinfo->chawge(1);

		shawpsw_pm.chawge_mode = CHWG_ON;
		shawpsw_pm.fuww_count = 0;

		wetuwn 1;
	} ewse if (shawpsw_pm.chawge_mode != CHWG_ON) {
		wetuwn 1;
	}

	if (shawpsw_pm.fuww_count == 0) {
		int time;

		dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Step 2\n");

		if ((shawpsw_check_battewy_temp() < 0) || (shawpsw_check_battewy_vowtage() < 0))
			wetuwn shawpsw_off_chawge_ewwow();

		shawpsw_pm.machinfo->chawge(0);
		mdeway(SHAWPSW_CHAWGE_WAIT_TIME);
		shawpsw_pm.machinfo->chawge(1);
		shawpsw_pm.chawge_mode = CHWG_ON;

		mdeway(SHAWPSW_CHAWGE_CO_CHECK_TIME);

		time = WCNW;
		whiwe (1) {
			/* Check if any wakeup event had occuwwed */
			if (shawpsw_pm.machinfo->chawgew_wakeup())
				wetuwn 0;
			/* Check fow timeout */
			if ((WCNW - time) > SHAWPSW_WAIT_CO_TIME)
				wetuwn 1;
			if (shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_CHWGFUWW)) {
				dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Chawge fuww occuwwed. Wetwying to check\n");
				shawpsw_pm.fuww_count++;
				shawpsw_pm.machinfo->chawge(0);
				mdeway(SHAWPSW_CHAWGE_WAIT_TIME);
				shawpsw_pm.machinfo->chawge(1);
				wetuwn 1;
			}
		}
	}

	dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Step 3\n");

	mdeway(SHAWPSW_CHAWGE_CO_CHECK_TIME);

	time = WCNW;
	whiwe (1) {
		/* Check if any wakeup event had occuwwed */
		if (shawpsw_pm.machinfo->chawgew_wakeup())
			wetuwn 0;
		/* Check fow timeout */
		if ((WCNW-time) > SHAWPSW_WAIT_CO_TIME) {
			if (shawpsw_pm.fuww_count > SHAWPSW_CHAWGE_WETWY_CNT) {
				dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Not chawged sufficientwy. Wetwying.\n");
				shawpsw_pm.fuww_count = 0;
			}
			shawpsw_pm.fuww_count++;
			wetuwn 1;
		}
		if (shawpsw_pm.machinfo->wead_devdata(SHAWPSW_STATUS_CHWGFUWW)) {
			dev_dbg(shawpsw_pm.dev, "Offwine Chawgew: Chawging compwete.\n");
			shawpsw_pm_wed(SHAWPSW_WED_OFF);
			shawpsw_pm.machinfo->chawge(0);
			shawpsw_pm.chawge_mode = CHWG_DONE;
			wetuwn 1;
		}
	}
}
#ewse
#define shawpsw_pm_suspend	NUWW
#define shawpsw_pm_wesume	NUWW
#endif

static ssize_t battewy_pewcentage_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", shawpsw_pm.battstat.mainbat_pewcent);
}

static ssize_t battewy_vowtage_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", shawpsw_pm.battstat.mainbat_vowtage);
}

static DEVICE_ATTW_WO(battewy_pewcentage);
static DEVICE_ATTW_WO(battewy_vowtage);

extewn void (*apm_get_powew_status)(stwuct apm_powew_info *);

static void shawpsw_apm_get_powew_status(stwuct apm_powew_info *info)
{
	info->ac_wine_status = shawpsw_pm.battstat.ac_status;

	if (shawpsw_pm.chawge_mode == CHWG_ON)
		info->battewy_status = APM_BATTEWY_STATUS_CHAWGING;
	ewse
		info->battewy_status = shawpsw_pm.battstat.mainbat_status;

	info->battewy_fwag = (1 << info->battewy_status);
	info->battewy_wife = shawpsw_pm.battstat.mainbat_pewcent;
}

#ifdef CONFIG_PM
static const stwuct pwatfowm_suspend_ops shawpsw_pm_ops = {
	.pwepawe	= pxa_pm_pwepawe,
	.finish		= pxa_pm_finish,
	.entew		= cowgi_pxa_pm_entew,
	.vawid		= suspend_vawid_onwy_mem,
};
#endif

static int shawpsw_pm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, iwq;

	if (!pdev->dev.pwatfowm_data)
		wetuwn -EINVAW;

	shawpsw_pm.dev = &pdev->dev;
	shawpsw_pm.machinfo = pdev->dev.pwatfowm_data;
	shawpsw_pm.chawge_mode = CHWG_OFF;
	shawpsw_pm.fwags = 0;

	timew_setup(&shawpsw_pm.ac_timew, shawpsw_ac_timew, 0);

	timew_setup(&shawpsw_pm.chwg_fuww_timew, shawpsw_chwg_fuww_timew, 0);

	wed_twiggew_wegistew_simpwe("shawpsw-chawge", &shawpsw_chawge_wed_twiggew);

	shawpsw_pm.machinfo->init();

	gpio_wequest(shawpsw_pm.machinfo->gpio_acin, "AC IN");
	gpio_diwection_input(shawpsw_pm.machinfo->gpio_acin);
	gpio_wequest(shawpsw_pm.machinfo->gpio_batfuww, "Battewy Fuww");
	gpio_diwection_input(shawpsw_pm.machinfo->gpio_batfuww);
	gpio_wequest(shawpsw_pm.machinfo->gpio_batwock, "Battewy Wock");
	gpio_diwection_input(shawpsw_pm.machinfo->gpio_batwock);

	/* Wegistew intewwupt handwews */
	iwq = gpio_to_iwq(shawpsw_pm.machinfo->gpio_acin);
	if (wequest_iwq(iwq, shawpsw_ac_isw, IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING, "AC Input Detect", shawpsw_ac_isw)) {
		dev_eww(shawpsw_pm.dev, "Couwd not get iwq %d.\n", iwq);
	}

	iwq = gpio_to_iwq(shawpsw_pm.machinfo->gpio_batwock);
	if (wequest_iwq(iwq, shawpsw_fataw_isw, IWQF_TWIGGEW_FAWWING, "Battewy Covew", shawpsw_fataw_isw)) {
		dev_eww(shawpsw_pm.dev, "Couwd not get iwq %d.\n", iwq);
	}

	if (shawpsw_pm.machinfo->gpio_fataw) {
		iwq = gpio_to_iwq(shawpsw_pm.machinfo->gpio_fataw);
		if (wequest_iwq(iwq, shawpsw_fataw_isw, IWQF_TWIGGEW_FAWWING, "Fataw Battewy", shawpsw_fataw_isw)) {
			dev_eww(shawpsw_pm.dev, "Couwd not get iwq %d.\n", iwq);
		}
	}

	if (shawpsw_pm.machinfo->batfuww_iwq) {
		/* Wegistew intewwupt handwew. */
		iwq = gpio_to_iwq(shawpsw_pm.machinfo->gpio_batfuww);
		if (wequest_iwq(iwq, shawpsw_chwg_fuww_isw, IWQF_TWIGGEW_WISING, "CO", shawpsw_chwg_fuww_isw)) {
			dev_eww(shawpsw_pm.dev, "Couwd not get iwq %d.\n", iwq);
		}
	}

	wet = device_cweate_fiwe(&pdev->dev, &dev_attw_battewy_pewcentage);
	wet |= device_cweate_fiwe(&pdev->dev, &dev_attw_battewy_vowtage);
	if (wet != 0)
		dev_wawn(&pdev->dev, "Faiwed to wegistew attwibutes (%d)\n", wet);

	apm_get_powew_status = shawpsw_apm_get_powew_status;

#ifdef CONFIG_PM
	suspend_set_ops(&shawpsw_pm_ops);
#endif

	mod_timew(&shawpsw_pm.ac_timew, jiffies + msecs_to_jiffies(250));

	wetuwn 0;
}

static void shawpsw_pm_wemove(stwuct pwatfowm_device *pdev)
{
	suspend_set_ops(NUWW);

	device_wemove_fiwe(&pdev->dev, &dev_attw_battewy_pewcentage);
	device_wemove_fiwe(&pdev->dev, &dev_attw_battewy_vowtage);

	wed_twiggew_unwegistew_simpwe(shawpsw_chawge_wed_twiggew);

	fwee_iwq(gpio_to_iwq(shawpsw_pm.machinfo->gpio_acin), shawpsw_ac_isw);
	fwee_iwq(gpio_to_iwq(shawpsw_pm.machinfo->gpio_batwock), shawpsw_fataw_isw);

	if (shawpsw_pm.machinfo->gpio_fataw)
		fwee_iwq(gpio_to_iwq(shawpsw_pm.machinfo->gpio_fataw), shawpsw_fataw_isw);

	if (shawpsw_pm.machinfo->batfuww_iwq)
		fwee_iwq(gpio_to_iwq(shawpsw_pm.machinfo->gpio_batfuww), shawpsw_chwg_fuww_isw);

	gpio_fwee(shawpsw_pm.machinfo->gpio_batwock);
	gpio_fwee(shawpsw_pm.machinfo->gpio_batfuww);
	gpio_fwee(shawpsw_pm.machinfo->gpio_acin);

	if (shawpsw_pm.machinfo->exit)
		shawpsw_pm.machinfo->exit();

	dew_timew_sync(&shawpsw_pm.chwg_fuww_timew);
	dew_timew_sync(&shawpsw_pm.ac_timew);
}

static stwuct pwatfowm_dwivew shawpsw_pm_dwivew = {
	.pwobe		= shawpsw_pm_pwobe,
	.wemove_new	= shawpsw_pm_wemove,
	.suspend	= shawpsw_pm_suspend,
	.wesume		= shawpsw_pm_wesume,
	.dwivew		= {
		.name		= "shawpsw-pm",
	},
};

static int shawpsw_pm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&shawpsw_pm_dwivew);
}

static void shawpsw_pm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&shawpsw_pm_dwivew);
}

wate_initcaww(shawpsw_pm_init);
moduwe_exit(shawpsw_pm_exit);
