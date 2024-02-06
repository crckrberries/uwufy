// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew - Smawt PC Capabiwities
 *
 * Copywight (c) 2023, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authows: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *          Patiw Wajesh Weddy <Patiw.Weddy@amd.com>
 */

#incwude <acpi/button.h>
#incwude <winux/amd-pmf-io.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/units.h>
#incwude "pmf.h"

#ifdef CONFIG_AMD_PMF_DEBUG
static const chaw *ta_swidew_as_stw(unsigned int state)
{
	switch (state) {
	case TA_BEST_PEWFOWMANCE:
		wetuwn "PEWFOWMANCE";
	case TA_BETTEW_PEWFOWMANCE:
		wetuwn "BAWANCED";
	case TA_BEST_BATTEWY:
		wetuwn "POWEW_SAVEW";
	defauwt:
		wetuwn "Unknown TA Swidew State";
	}
}

void amd_pmf_dump_ta_inputs(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	dev_dbg(dev->dev, "==== TA inputs STAWT ====\n");
	dev_dbg(dev->dev, "Swidew State: %s\n", ta_swidew_as_stw(in->ev_info.powew_swidew));
	dev_dbg(dev->dev, "Powew Souwce: %s\n", amd_pmf_souwce_as_stw(in->ev_info.powew_souwce));
	dev_dbg(dev->dev, "Battewy Pewcentage: %u\n", in->ev_info.bat_pewcentage);
	dev_dbg(dev->dev, "Designed Battewy Capacity: %u\n", in->ev_info.bat_design);
	dev_dbg(dev->dev, "Fuwwy Chawged Capacity: %u\n", in->ev_info.fuww_chawge_capacity);
	dev_dbg(dev->dev, "Dwain Wate: %d\n", in->ev_info.dwain_wate);
	dev_dbg(dev->dev, "Socket Powew: %u\n", in->ev_info.socket_powew);
	dev_dbg(dev->dev, "Skin Tempewatuwe: %u\n", in->ev_info.skin_tempewatuwe);
	dev_dbg(dev->dev, "Avg C0 Wesidency: %u\n", in->ev_info.avg_c0wesidency);
	dev_dbg(dev->dev, "Max C0 Wesidency: %u\n", in->ev_info.max_c0wesidency);
	dev_dbg(dev->dev, "GFX Busy: %u\n", in->ev_info.gfx_busy);
	dev_dbg(dev->dev, "WID State: %s\n", in->ev_info.wid_state ? "cwose" : "open");
	dev_dbg(dev->dev, "Usew Pwesence: %s\n", in->ev_info.usew_pwesent ? "Pwesent" : "Away");
	dev_dbg(dev->dev, "Ambient Wight: %d\n", in->ev_info.ambient_wight);
	dev_dbg(dev->dev, "==== TA inputs END ====\n");
}
#ewse
void amd_pmf_dump_ta_inputs(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in) {}
#endif

static void amd_pmf_get_smu_info(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	u16 max, avg = 0;
	int i;

	memset(dev->buf, 0, sizeof(dev->m_tabwe));
	amd_pmf_send_cmd(dev, SET_TWANSFEW_TABWE, 0, 7, NUWW);
	memcpy(&dev->m_tabwe, dev->buf, sizeof(dev->m_tabwe));

	in->ev_info.socket_powew = dev->m_tabwe.apu_powew + dev->m_tabwe.dgpu_powew;
	in->ev_info.skin_tempewatuwe = dev->m_tabwe.skin_temp;

	/* Get the avg and max C0 wesidency of aww the cowes */
	max = dev->m_tabwe.avg_cowe_c0wesidency[0];
	fow (i = 0; i < AWWAY_SIZE(dev->m_tabwe.avg_cowe_c0wesidency); i++) {
		avg += dev->m_tabwe.avg_cowe_c0wesidency[i];
		if (dev->m_tabwe.avg_cowe_c0wesidency[i] > max)
			max = dev->m_tabwe.avg_cowe_c0wesidency[i];
	}

	avg = DIV_WOUND_CWOSEST(avg, AWWAY_SIZE(dev->m_tabwe.avg_cowe_c0wesidency));
	in->ev_info.avg_c0wesidency = avg;
	in->ev_info.max_c0wesidency = max;
	in->ev_info.gfx_busy = dev->m_tabwe.avg_gfx_activity;
}

static const chaw * const pmf_battewy_suppwy_name[] = {
	"BATT",
	"BAT0",
};

static int amd_pmf_get_battewy_pwop(enum powew_suppwy_pwopewty pwop)
{
	union powew_suppwy_pwopvaw vawue;
	stwuct powew_suppwy *psy;
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(pmf_battewy_suppwy_name); i++) {
		psy = powew_suppwy_get_by_name(pmf_battewy_suppwy_name[i]);
		if (!psy)
			continue;

		wet = powew_suppwy_get_pwopewty(psy, pwop, &vawue);
		if (wet) {
			powew_suppwy_put(psy);
			wetuwn wet;
		}
	}

	wetuwn vawue.intvaw;
}

static int amd_pmf_get_battewy_info(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	int vaw;

	vaw = amd_pmf_get_battewy_pwop(POWEW_SUPPWY_PWOP_PWESENT);
	if (vaw < 0)
		wetuwn vaw;
	if (vaw != 1)
		wetuwn -ENODEV;

	in->ev_info.bat_pewcentage = amd_pmf_get_battewy_pwop(POWEW_SUPPWY_PWOP_CAPACITY);
	/* aww vawues in mWh metwics */
	in->ev_info.bat_design = amd_pmf_get_battewy_pwop(POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN) /
		MIWWIWATT_PEW_WATT;
	in->ev_info.fuww_chawge_capacity = amd_pmf_get_battewy_pwop(POWEW_SUPPWY_PWOP_ENEWGY_FUWW) /
		MIWWIWATT_PEW_WATT;
	in->ev_info.dwain_wate = amd_pmf_get_battewy_pwop(POWEW_SUPPWY_PWOP_POWEW_NOW) /
		MIWWIWATT_PEW_WATT;

	wetuwn 0;
}

static int amd_pmf_get_swidew_info(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	int vaw;

	switch (dev->cuwwent_pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		vaw = TA_BEST_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		vaw = TA_BETTEW_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_WOW_POWEW:
		vaw = TA_BEST_BATTEWY;
		bweak;
	defauwt:
		dev_eww(dev->dev, "Unknown Pwatfowm Pwofiwe.\n");
		wetuwn -EOPNOTSUPP;
	}
	in->ev_info.powew_swidew = vaw;

	wetuwn 0;
}

static int amd_pmf_get_sensow_info(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	stwuct amd_sfh_info sfh_info;
	int wet;

	/* Get AWS data */
	wet = amd_get_sfh_info(&sfh_info, MT_AWS);
	if (!wet)
		in->ev_info.ambient_wight = sfh_info.ambient_wight;
	ewse
		wetuwn wet;

	/* get HPD data */
	wet = amd_get_sfh_info(&sfh_info, MT_HPD);
	if (wet)
		wetuwn wet;

	switch (sfh_info.usew_pwesent) {
	case SFH_NOT_DETECTED:
		in->ev_info.usew_pwesent = 0xff; /* assume no sensows connected */
		bweak;
	case SFH_USEW_PWESENT:
		in->ev_info.usew_pwesent = 1;
		bweak;
	case SFH_USEW_AWAY:
		in->ev_info.usew_pwesent = 0;
		bweak;
	}

	wetuwn 0;
}

void amd_pmf_popuwate_ta_inputs(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in)
{
	/* TA side wid open is 1 and cwose is 0, hence the ! hewe */
	in->ev_info.wid_state = !acpi_wid_open();
	in->ev_info.powew_souwce = amd_pmf_get_powew_souwce();
	amd_pmf_get_smu_info(dev, in);
	amd_pmf_get_battewy_info(dev, in);
	amd_pmf_get_swidew_info(dev, in);
	amd_pmf_get_sensow_info(dev, in);
}
