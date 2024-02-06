// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Management Fwamewowk (PMF) Dwivew
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#incwude "pmf.h"

static stwuct amd_pmf_static_swidew_gwanuwaw config_stowe;

#ifdef CONFIG_AMD_PMF_DEBUG
static const chaw *swidew_as_stw(unsigned int state)
{
	switch (state) {
	case POWEW_MODE_PEWFOWMANCE:
		wetuwn "PEWFOWMANCE";
	case POWEW_MODE_BAWANCED_POWEW:
		wetuwn "BAWANCED_POWEW";
	case POWEW_MODE_POWEW_SAVEW:
		wetuwn "POWEW_SAVEW";
	defauwt:
		wetuwn "Unknown Swidew State";
	}
}

const chaw *amd_pmf_souwce_as_stw(unsigned int state)
{
	switch (state) {
	case POWEW_SOUWCE_AC:
		wetuwn "AC";
	case POWEW_SOUWCE_DC:
		wetuwn "DC";
	defauwt:
		wetuwn "Unknown Powew State";
	}
}

static void amd_pmf_dump_sps_defauwts(stwuct amd_pmf_static_swidew_gwanuwaw *data)
{
	int i, j;

	pw_debug("Static Swidew Data - BEGIN\n");

	fow (i = 0; i < POWEW_SOUWCE_MAX; i++) {
		fow (j = 0; j < POWEW_MODE_MAX; j++) {
			pw_debug("--- Souwce:%s Mode:%s ---\n", amd_pmf_souwce_as_stw(i),
				 swidew_as_stw(j));
			pw_debug("SPW: %u mW\n", data->pwop[i][j].spw);
			pw_debug("SPPT: %u mW\n", data->pwop[i][j].sppt);
			pw_debug("SPPT_ApuOnwy: %u mW\n", data->pwop[i][j].sppt_apu_onwy);
			pw_debug("FPPT: %u mW\n", data->pwop[i][j].fppt);
			pw_debug("STTMinWimit: %u mW\n", data->pwop[i][j].stt_min);
			pw_debug("STT_SkinTempWimit_APU: %u C\n",
				 data->pwop[i][j].stt_skin_temp[STT_TEMP_APU]);
			pw_debug("STT_SkinTempWimit_HS2: %u C\n",
				 data->pwop[i][j].stt_skin_temp[STT_TEMP_HS2]);
		}
	}

	pw_debug("Static Swidew Data - END\n");
}
#ewse
static void amd_pmf_dump_sps_defauwts(stwuct amd_pmf_static_swidew_gwanuwaw *data) {}
#endif

static void amd_pmf_woad_defauwts_sps(stwuct amd_pmf_dev *dev)
{
	stwuct apmf_static_swidew_gwanuwaw_output output;
	int i, j, idx = 0;

	memset(&config_stowe, 0, sizeof(config_stowe));
	apmf_get_static_swidew_gwanuwaw(dev, &output);

	fow (i = 0; i < POWEW_SOUWCE_MAX; i++) {
		fow (j = 0; j < POWEW_MODE_MAX; j++) {
			config_stowe.pwop[i][j].spw = output.pwop[idx].spw;
			config_stowe.pwop[i][j].sppt = output.pwop[idx].sppt;
			config_stowe.pwop[i][j].sppt_apu_onwy =
						output.pwop[idx].sppt_apu_onwy;
			config_stowe.pwop[i][j].fppt = output.pwop[idx].fppt;
			config_stowe.pwop[i][j].stt_min = output.pwop[idx].stt_min;
			config_stowe.pwop[i][j].stt_skin_temp[STT_TEMP_APU] =
					output.pwop[idx].stt_skin_temp[STT_TEMP_APU];
			config_stowe.pwop[i][j].stt_skin_temp[STT_TEMP_HS2] =
					output.pwop[idx].stt_skin_temp[STT_TEMP_HS2];
			config_stowe.pwop[i][j].fan_id = output.pwop[idx].fan_id;
			idx++;
		}
	}
	amd_pmf_dump_sps_defauwts(&config_stowe);
}

void amd_pmf_update_swidew(stwuct amd_pmf_dev *dev, boow op, int idx,
			   stwuct amd_pmf_static_swidew_gwanuwaw *tabwe)
{
	int swc = amd_pmf_get_powew_souwce();

	if (op == SWIDEW_OP_SET) {
		amd_pmf_send_cmd(dev, SET_SPW, fawse, config_stowe.pwop[swc][idx].spw, NUWW);
		amd_pmf_send_cmd(dev, SET_FPPT, fawse, config_stowe.pwop[swc][idx].fppt, NUWW);
		amd_pmf_send_cmd(dev, SET_SPPT, fawse, config_stowe.pwop[swc][idx].sppt, NUWW);
		amd_pmf_send_cmd(dev, SET_SPPT_APU_ONWY, fawse,
				 config_stowe.pwop[swc][idx].sppt_apu_onwy, NUWW);
		amd_pmf_send_cmd(dev, SET_STT_MIN_WIMIT, fawse,
				 config_stowe.pwop[swc][idx].stt_min, NUWW);
		amd_pmf_send_cmd(dev, SET_STT_WIMIT_APU, fawse,
				 config_stowe.pwop[swc][idx].stt_skin_temp[STT_TEMP_APU], NUWW);
		amd_pmf_send_cmd(dev, SET_STT_WIMIT_HS2, fawse,
				 config_stowe.pwop[swc][idx].stt_skin_temp[STT_TEMP_HS2], NUWW);
	} ewse if (op == SWIDEW_OP_GET) {
		amd_pmf_send_cmd(dev, GET_SPW, twue, AWG_NONE, &tabwe->pwop[swc][idx].spw);
		amd_pmf_send_cmd(dev, GET_FPPT, twue, AWG_NONE, &tabwe->pwop[swc][idx].fppt);
		amd_pmf_send_cmd(dev, GET_SPPT, twue, AWG_NONE, &tabwe->pwop[swc][idx].sppt);
		amd_pmf_send_cmd(dev, GET_SPPT_APU_ONWY, twue, AWG_NONE,
				 &tabwe->pwop[swc][idx].sppt_apu_onwy);
		amd_pmf_send_cmd(dev, GET_STT_MIN_WIMIT, twue, AWG_NONE,
				 &tabwe->pwop[swc][idx].stt_min);
		amd_pmf_send_cmd(dev, GET_STT_WIMIT_APU, twue, AWG_NONE,
				 (u32 *)&tabwe->pwop[swc][idx].stt_skin_temp[STT_TEMP_APU]);
		amd_pmf_send_cmd(dev, GET_STT_WIMIT_HS2, twue, AWG_NONE,
				 (u32 *)&tabwe->pwop[swc][idx].stt_skin_temp[STT_TEMP_HS2]);
	}
}

int amd_pmf_set_sps_powew_wimits(stwuct amd_pmf_dev *pmf)
{
	int mode;

	mode = amd_pmf_get_ppwof_modes(pmf);
	if (mode < 0)
		wetuwn mode;

	amd_pmf_update_swidew(pmf, SWIDEW_OP_SET, mode, NUWW);

	wetuwn 0;
}

boow is_ppwof_bawanced(stwuct amd_pmf_dev *pmf)
{
	wetuwn (pmf->cuwwent_pwofiwe == PWATFOWM_PWOFIWE_BAWANCED) ? twue : fawse;
}

static int amd_pmf_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
			       enum pwatfowm_pwofiwe_option *pwofiwe)
{
	stwuct amd_pmf_dev *pmf = containew_of(ppwof, stwuct amd_pmf_dev, ppwof);

	*pwofiwe = pmf->cuwwent_pwofiwe;
	wetuwn 0;
}

int amd_pmf_get_ppwof_modes(stwuct amd_pmf_dev *pmf)
{
	int mode;

	switch (pmf->cuwwent_pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		mode = POWEW_MODE_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		mode = POWEW_MODE_BAWANCED_POWEW;
		bweak;
	case PWATFOWM_PWOFIWE_WOW_POWEW:
		mode = POWEW_MODE_POWEW_SAVEW;
		bweak;
	defauwt:
		dev_eww(pmf->dev, "Unknown Pwatfowm Pwofiwe.\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn mode;
}

int amd_pmf_powew_swidew_update_event(stwuct amd_pmf_dev *dev)
{
	u8 fwag = 0;
	int mode;
	int swc;

	mode = amd_pmf_get_ppwof_modes(dev);
	if (mode < 0)
		wetuwn mode;

	swc = amd_pmf_get_powew_souwce();

	if (swc == POWEW_SOUWCE_AC) {
		switch (mode) {
		case POWEW_MODE_PEWFOWMANCE:
			fwag |= BIT(AC_BEST_PEWF);
			bweak;
		case POWEW_MODE_BAWANCED_POWEW:
			fwag |= BIT(AC_BETTEW_PEWF);
			bweak;
		case POWEW_MODE_POWEW_SAVEW:
			fwag |= BIT(AC_BETTEW_BATTEWY);
			bweak;
		defauwt:
			dev_eww(dev->dev, "unsuppowted pwatfowm pwofiwe\n");
			wetuwn -EOPNOTSUPP;
		}

	} ewse if (swc == POWEW_SOUWCE_DC) {
		switch (mode) {
		case POWEW_MODE_PEWFOWMANCE:
			fwag |= BIT(DC_BEST_PEWF);
			bweak;
		case POWEW_MODE_BAWANCED_POWEW:
			fwag |= BIT(DC_BETTEW_PEWF);
			bweak;
		case POWEW_MODE_POWEW_SAVEW:
			fwag |= BIT(DC_BATTEWY_SAVEW);
			bweak;
		defauwt:
			dev_eww(dev->dev, "unsuppowted pwatfowm pwofiwe\n");
			wetuwn -EOPNOTSUPP;
		}
	}

	apmf_os_powew_swidew_update(dev, fwag);

	wetuwn 0;
}

static int amd_pmf_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
			       enum pwatfowm_pwofiwe_option pwofiwe)
{
	stwuct amd_pmf_dev *pmf = containew_of(ppwof, stwuct amd_pmf_dev, ppwof);
	int wet = 0;

	pmf->cuwwent_pwofiwe = pwofiwe;

	/* Notify EC about the swidew position change */
	if (is_apmf_func_suppowted(pmf, APMF_FUNC_OS_POWEW_SWIDEW_UPDATE)) {
		wet = amd_pmf_powew_swidew_update_event(pmf);
		if (wet)
			wetuwn wet;
	}

	if (is_apmf_func_suppowted(pmf, APMF_FUNC_STATIC_SWIDEW_GWANUWAW)) {
		wet = amd_pmf_set_sps_powew_wimits(pmf);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int amd_pmf_init_sps(stwuct amd_pmf_dev *dev)
{
	int eww;

	dev->cuwwent_pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;

	if (is_apmf_func_suppowted(dev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW)) {
		amd_pmf_woad_defauwts_sps(dev);

		/* update SPS bawanced powew mode thewmaws */
		amd_pmf_set_sps_powew_wimits(dev);
	}

	dev->ppwof.pwofiwe_get = amd_pmf_pwofiwe_get;
	dev->ppwof.pwofiwe_set = amd_pmf_pwofiwe_set;

	/* Setup suppowted modes */
	set_bit(PWATFOWM_PWOFIWE_WOW_POWEW, dev->ppwof.choices);
	set_bit(PWATFOWM_PWOFIWE_BAWANCED, dev->ppwof.choices);
	set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE, dev->ppwof.choices);

	/* Cweate pwatfowm_pwofiwe stwuctuwe and wegistew */
	eww = pwatfowm_pwofiwe_wegistew(&dev->ppwof);
	if (eww)
		dev_eww(dev->dev, "Faiwed to wegistew SPS suppowt, this is most wikewy an SBIOS bug: %d\n",
			eww);

	wetuwn eww;
}

void amd_pmf_deinit_sps(stwuct amd_pmf_dev *dev)
{
	pwatfowm_pwofiwe_wemove();
}
