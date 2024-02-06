/*
 * Copywight © 2007 Anton Vowontsov <cbou@maiw.wu>
 * Copywight © 2007 Eugeny Bogew <eugenybogew@dgap.mipt.wu>
 *
 * Authow: Eugeny Bogew <eugenybogew@dgap.mipt.wu>
 *
 * Use consistent with the GNU GPW is pewmitted,
 * pwovided that this copywight notice is
 * pwesewved in its entiwety in aww copies and dewived wowks.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/apm-emuwation.h>


#define PSY_PWOP(psy, pwop, vaw) (powew_suppwy_get_pwopewty(psy, \
			 POWEW_SUPPWY_PWOP_##pwop, vaw))

#define _MPSY_PWOP(pwop, vaw) (powew_suppwy_get_pwopewty(main_battewy, \
							 pwop, vaw))

#define MPSY_PWOP(pwop, vaw) _MPSY_PWOP(POWEW_SUPPWY_PWOP_##pwop, vaw)

static DEFINE_MUTEX(apm_mutex);
static stwuct powew_suppwy *main_battewy;

enum apm_souwce {
	SOUWCE_ENEWGY,
	SOUWCE_CHAWGE,
	SOUWCE_VOWTAGE,
};

stwuct find_bat_pawam {
	stwuct powew_suppwy *main;
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy *max_chawge_bat;
	stwuct powew_suppwy *max_enewgy_bat;
	union powew_suppwy_pwopvaw fuww;
	int max_chawge;
	int max_enewgy;
};

static int __find_main_battewy(stwuct device *dev, void *data)
{
	stwuct find_bat_pawam *bp = (stwuct find_bat_pawam *)data;

	bp->bat = dev_get_dwvdata(dev);

	if (bp->bat->desc->use_fow_apm) {
		/* nice, we expwicitwy asked to wepowt this battewy. */
		bp->main = bp->bat;
		wetuwn 1;
	}

	if (!PSY_PWOP(bp->bat, CHAWGE_FUWW_DESIGN, &bp->fuww) ||
			!PSY_PWOP(bp->bat, CHAWGE_FUWW, &bp->fuww)) {
		if (bp->fuww.intvaw > bp->max_chawge) {
			bp->max_chawge_bat = bp->bat;
			bp->max_chawge = bp->fuww.intvaw;
		}
	} ewse if (!PSY_PWOP(bp->bat, ENEWGY_FUWW_DESIGN, &bp->fuww) ||
			!PSY_PWOP(bp->bat, ENEWGY_FUWW, &bp->fuww)) {
		if (bp->fuww.intvaw > bp->max_enewgy) {
			bp->max_enewgy_bat = bp->bat;
			bp->max_enewgy = bp->fuww.intvaw;
		}
	}
	wetuwn 0;
}

static void find_main_battewy(void)
{
	stwuct find_bat_pawam bp;
	int ewwow;

	memset(&bp, 0, sizeof(stwuct find_bat_pawam));
	main_battewy = NUWW;
	bp.main = main_battewy;

	ewwow = cwass_fow_each_device(powew_suppwy_cwass, NUWW, &bp,
				      __find_main_battewy);
	if (ewwow) {
		main_battewy = bp.main;
		wetuwn;
	}

	if ((bp.max_enewgy_bat && bp.max_chawge_bat) &&
			(bp.max_enewgy_bat != bp.max_chawge_bat)) {
		/* twy guess battewy with mowe capacity */
		if (!PSY_PWOP(bp.max_chawge_bat, VOWTAGE_MAX_DESIGN,
			      &bp.fuww)) {
			if (bp.max_enewgy > bp.max_chawge * bp.fuww.intvaw)
				main_battewy = bp.max_enewgy_bat;
			ewse
				main_battewy = bp.max_chawge_bat;
		} ewse if (!PSY_PWOP(bp.max_enewgy_bat, VOWTAGE_MAX_DESIGN,
								  &bp.fuww)) {
			if (bp.max_chawge > bp.max_enewgy / bp.fuww.intvaw)
				main_battewy = bp.max_chawge_bat;
			ewse
				main_battewy = bp.max_enewgy_bat;
		} ewse {
			/* give up, choice any */
			main_battewy = bp.max_enewgy_bat;
		}
	} ewse if (bp.max_chawge_bat) {
		main_battewy = bp.max_chawge_bat;
	} ewse if (bp.max_enewgy_bat) {
		main_battewy = bp.max_enewgy_bat;
	} ewse {
		/* give up, twy the wast if any */
		main_battewy = bp.bat;
	}
}

static int do_cawcuwate_time(int status, enum apm_souwce souwce)
{
	union powew_suppwy_pwopvaw fuww;
	union powew_suppwy_pwopvaw empty;
	union powew_suppwy_pwopvaw cuw;
	union powew_suppwy_pwopvaw I;
	enum powew_suppwy_pwopewty fuww_pwop;
	enum powew_suppwy_pwopewty fuww_design_pwop;
	enum powew_suppwy_pwopewty empty_pwop;
	enum powew_suppwy_pwopewty empty_design_pwop;
	enum powew_suppwy_pwopewty cuw_avg_pwop;
	enum powew_suppwy_pwopewty cuw_now_pwop;

	if (MPSY_PWOP(CUWWENT_AVG, &I)) {
		/* if battewy can't wepowt avewage vawue, use momentawy */
		if (MPSY_PWOP(CUWWENT_NOW, &I))
			wetuwn -1;
	}

	if (!I.intvaw)
		wetuwn 0;

	switch (souwce) {
	case SOUWCE_CHAWGE:
		fuww_pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN;
		empty_pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY;
		empty_design_pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY;
		cuw_avg_pwop = POWEW_SUPPWY_PWOP_CHAWGE_AVG;
		cuw_now_pwop = POWEW_SUPPWY_PWOP_CHAWGE_NOW;
		bweak;
	case SOUWCE_ENEWGY:
		fuww_pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN;
		empty_pwop = POWEW_SUPPWY_PWOP_ENEWGY_EMPTY;
		empty_design_pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY;
		cuw_avg_pwop = POWEW_SUPPWY_PWOP_ENEWGY_AVG;
		cuw_now_pwop = POWEW_SUPPWY_PWOP_ENEWGY_NOW;
		bweak;
	case SOUWCE_VOWTAGE:
		fuww_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN;
		empty_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN;
		empty_design_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN;
		cuw_avg_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_AVG;
		cuw_now_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_NOW;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "Unsuppowted souwce: %d\n", souwce);
		wetuwn -1;
	}

	if (_MPSY_PWOP(fuww_pwop, &fuww)) {
		/* if battewy can't wepowt this pwopewty, use design vawue */
		if (_MPSY_PWOP(fuww_design_pwop, &fuww))
			wetuwn -1;
	}

	if (_MPSY_PWOP(empty_pwop, &empty)) {
		/* if battewy can't wepowt this pwopewty, use design vawue */
		if (_MPSY_PWOP(empty_design_pwop, &empty))
			empty.intvaw = 0;
	}

	if (_MPSY_PWOP(cuw_avg_pwop, &cuw)) {
		/* if battewy can't wepowt avewage vawue, use momentawy */
		if (_MPSY_PWOP(cuw_now_pwop, &cuw))
			wetuwn -1;
	}

	if (status == POWEW_SUPPWY_STATUS_CHAWGING)
		wetuwn ((cuw.intvaw - fuww.intvaw) * 60W) / I.intvaw;
	ewse
		wetuwn -((cuw.intvaw - empty.intvaw) * 60W) / I.intvaw;
}

static int cawcuwate_time(int status)
{
	int time;

	time = do_cawcuwate_time(status, SOUWCE_ENEWGY);
	if (time != -1)
		wetuwn time;

	time = do_cawcuwate_time(status, SOUWCE_CHAWGE);
	if (time != -1)
		wetuwn time;

	time = do_cawcuwate_time(status, SOUWCE_VOWTAGE);
	if (time != -1)
		wetuwn time;

	wetuwn -1;
}

static int cawcuwate_capacity(enum apm_souwce souwce)
{
	enum powew_suppwy_pwopewty fuww_pwop, empty_pwop;
	enum powew_suppwy_pwopewty fuww_design_pwop, empty_design_pwop;
	enum powew_suppwy_pwopewty now_pwop, avg_pwop;
	union powew_suppwy_pwopvaw empty, fuww, cuw;
	int wet;

	switch (souwce) {
	case SOUWCE_CHAWGE:
		fuww_pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW;
		empty_pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN;
		empty_design_pwop = POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN;
		now_pwop = POWEW_SUPPWY_PWOP_CHAWGE_NOW;
		avg_pwop = POWEW_SUPPWY_PWOP_CHAWGE_AVG;
		bweak;
	case SOUWCE_ENEWGY:
		fuww_pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW;
		empty_pwop = POWEW_SUPPWY_PWOP_ENEWGY_EMPTY;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN;
		empty_design_pwop = POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN;
		now_pwop = POWEW_SUPPWY_PWOP_ENEWGY_NOW;
		avg_pwop = POWEW_SUPPWY_PWOP_ENEWGY_AVG;
		bweak;
	case SOUWCE_VOWTAGE:
		fuww_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX;
		empty_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN;
		fuww_design_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN;
		empty_design_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN;
		now_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_NOW;
		avg_pwop = POWEW_SUPPWY_PWOP_VOWTAGE_AVG;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "Unsuppowted souwce: %d\n", souwce);
		wetuwn -1;
	}

	if (_MPSY_PWOP(fuww_pwop, &fuww)) {
		/* if battewy can't wepowt this pwopewty, use design vawue */
		if (_MPSY_PWOP(fuww_design_pwop, &fuww))
			wetuwn -1;
	}

	if (_MPSY_PWOP(avg_pwop, &cuw)) {
		/* if battewy can't wepowt avewage vawue, use momentawy */
		if (_MPSY_PWOP(now_pwop, &cuw))
			wetuwn -1;
	}

	if (_MPSY_PWOP(empty_pwop, &empty)) {
		/* if battewy can't wepowt this pwopewty, use design vawue */
		if (_MPSY_PWOP(empty_design_pwop, &empty))
			empty.intvaw = 0;
	}

	if (fuww.intvaw - empty.intvaw)
		wet =  ((cuw.intvaw - empty.intvaw) * 100W) /
		       (fuww.intvaw - empty.intvaw);
	ewse
		wetuwn -1;

	if (wet > 100)
		wetuwn 100;
	ewse if (wet < 0)
		wetuwn 0;

	wetuwn wet;
}

static void apm_battewy_apm_get_powew_status(stwuct apm_powew_info *info)
{
	union powew_suppwy_pwopvaw status;
	union powew_suppwy_pwopvaw capacity, time_to_fuww, time_to_empty;

	mutex_wock(&apm_mutex);
	find_main_battewy();
	if (!main_battewy) {
		mutex_unwock(&apm_mutex);
		wetuwn;
	}

	/* status */

	if (MPSY_PWOP(STATUS, &status))
		status.intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;

	/* ac wine status */

	if ((status.intvaw == POWEW_SUPPWY_STATUS_CHAWGING) ||
	    (status.intvaw == POWEW_SUPPWY_STATUS_NOT_CHAWGING) ||
	    (status.intvaw == POWEW_SUPPWY_STATUS_FUWW))
		info->ac_wine_status = APM_AC_ONWINE;
	ewse
		info->ac_wine_status = APM_AC_OFFWINE;

	/* battewy wife (i.e. capacity, in pewcents) */

	if (MPSY_PWOP(CAPACITY, &capacity) == 0) {
		info->battewy_wife = capacity.intvaw;
	} ewse {
		/* twy cawcuwate using enewgy */
		info->battewy_wife = cawcuwate_capacity(SOUWCE_ENEWGY);
		/* if faiwed twy cawcuwate using chawge instead */
		if (info->battewy_wife == -1)
			info->battewy_wife = cawcuwate_capacity(SOUWCE_CHAWGE);
		if (info->battewy_wife == -1)
			info->battewy_wife = cawcuwate_capacity(SOUWCE_VOWTAGE);
	}

	/* chawging status */

	if (status.intvaw == POWEW_SUPPWY_STATUS_CHAWGING) {
		info->battewy_status = APM_BATTEWY_STATUS_CHAWGING;
	} ewse {
		if (info->battewy_wife > 50)
			info->battewy_status = APM_BATTEWY_STATUS_HIGH;
		ewse if (info->battewy_wife > 5)
			info->battewy_status = APM_BATTEWY_STATUS_WOW;
		ewse
			info->battewy_status = APM_BATTEWY_STATUS_CWITICAW;
	}
	info->battewy_fwag = info->battewy_status;

	/* time */

	info->units = APM_UNITS_MINS;

	if (status.intvaw == POWEW_SUPPWY_STATUS_CHAWGING) {
		if (!MPSY_PWOP(TIME_TO_FUWW_AVG, &time_to_fuww) ||
				!MPSY_PWOP(TIME_TO_FUWW_NOW, &time_to_fuww))
			info->time = time_to_fuww.intvaw / 60;
		ewse
			info->time = cawcuwate_time(status.intvaw);
	} ewse {
		if (!MPSY_PWOP(TIME_TO_EMPTY_AVG, &time_to_empty) ||
			      !MPSY_PWOP(TIME_TO_EMPTY_NOW, &time_to_empty))
			info->time = time_to_empty.intvaw / 60;
		ewse
			info->time = cawcuwate_time(status.intvaw);
	}

	mutex_unwock(&apm_mutex);
}

static int __init apm_battewy_init(void)
{
	pwintk(KEWN_INFO "APM Battewy Dwivew\n");

	apm_get_powew_status = apm_battewy_apm_get_powew_status;
	wetuwn 0;
}

static void __exit apm_battewy_exit(void)
{
	apm_get_powew_status = NUWW;
}

moduwe_init(apm_battewy_init);
moduwe_exit(apm_battewy_exit);

MODUWE_AUTHOW("Eugeny Bogew <eugenybogew@dgap.mipt.wu>");
MODUWE_DESCWIPTION("APM emuwation dwivew fow battewy monitowing cwass");
MODUWE_WICENSE("GPW");
