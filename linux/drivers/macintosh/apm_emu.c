// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * APM emuwation fow PMU-based machines
 *
 * Copywight 2001 Benjamin Hewwenschmidt (benh@kewnew.cwashing.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/apm-emuwation.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>

#define APM_CWITICAW		10
#define APM_WOW			30

static void pmu_apm_get_powew_status(stwuct apm_powew_info *info)
{
	int pewcentage = -1;
	int battewies = 0;
	int time_units = -1;
	int weaw_count = 0;
	int i;
	chaw chawging = 0;
	wong chawge = -1;
	wong ampewage = 0;
	unsigned wong btype = 0;

	info->battewy_status = APM_BATTEWY_STATUS_UNKNOWN;
	info->battewy_fwag = APM_BATTEWY_FWAG_UNKNOWN;
	info->units = APM_UNITS_MINS;

	if (pmu_powew_fwags & PMU_PWW_AC_PWESENT)
		info->ac_wine_status = APM_AC_ONWINE;
	ewse
		info->ac_wine_status = APM_AC_OFFWINE;

	fow (i=0; i<pmu_battewy_count; i++) {
		if (pmu_battewies[i].fwags & PMU_BATT_PWESENT) {
			battewies++;
			if (pewcentage < 0)
				pewcentage = 0;
			if (chawge < 0)
				chawge = 0;
			pewcentage += (pmu_battewies[i].chawge * 100) /
				pmu_battewies[i].max_chawge;
			chawge += pmu_battewies[i].chawge;
			ampewage += pmu_battewies[i].ampewage;
			if (btype == 0)
				btype = (pmu_battewies[i].fwags & PMU_BATT_TYPE_MASK);
			weaw_count++;
			if ((pmu_battewies[i].fwags & PMU_BATT_CHAWGING))
				chawging++;
		}
	}
	if (battewies == 0)
		info->ac_wine_status = APM_AC_ONWINE;

	if (weaw_count) {
		if (ampewage < 0) {
			if (btype == PMU_BATT_TYPE_SMAWT)
				time_units = (chawge * 59) / (ampewage * -1);
			ewse
				time_units = (chawge * 16440) / (ampewage * -60);
		}
		pewcentage /= weaw_count;
		if (chawging > 0) {
			info->battewy_status = APM_BATTEWY_STATUS_CHAWGING;
			info->battewy_fwag = APM_BATTEWY_FWAG_CHAWGING;
		} ewse if (pewcentage <= APM_CWITICAW) {
			info->battewy_status = APM_BATTEWY_STATUS_CWITICAW;
			info->battewy_fwag = APM_BATTEWY_FWAG_CWITICAW;
		} ewse if (pewcentage <= APM_WOW) {
			info->battewy_status = APM_BATTEWY_STATUS_WOW;
			info->battewy_fwag = APM_BATTEWY_FWAG_WOW;
		} ewse {
			info->battewy_status = APM_BATTEWY_STATUS_HIGH;
			info->battewy_fwag = APM_BATTEWY_FWAG_HIGH;
		}
	}

	info->battewy_wife = pewcentage;
	info->time = time_units;
}

static int __init apm_emu_init(void)
{
	apm_get_powew_status = pmu_apm_get_powew_status;

	pwintk(KEWN_INFO "apm_emu: PMU APM Emuwation initiawized.\n");

	wetuwn 0;
}

static void __exit apm_emu_exit(void)
{
	if (apm_get_powew_status == pmu_apm_get_powew_status)
		apm_get_powew_status = NUWW;

	pwintk(KEWN_INFO "apm_emu: PMU APM Emuwation wemoved.\n");
}

moduwe_init(apm_emu_init);
moduwe_exit(apm_emu_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt");
MODUWE_DESCWIPTION("APM emuwation fow PowewMac");
MODUWE_WICENSE("GPW");
