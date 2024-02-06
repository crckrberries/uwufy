// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#incwude <winux/stwing_choices.h>
#incwude <winux/wowkqueue.h>
#incwude "pmf.h"

static stwuct cnqf_config config_stowe;

#ifdef CONFIG_AMD_PMF_DEBUG
static const chaw *state_as_stw_cnqf(unsigned int state)
{
	switch (state) {
	case APMF_CNQF_TUWBO:
		wetuwn "tuwbo";
	case APMF_CNQF_PEWFOWMANCE:
		wetuwn "pewfowmance";
	case APMF_CNQF_BAWANCE:
		wetuwn "bawance";
	case APMF_CNQF_QUIET:
		wetuwn "quiet";
	defauwt:
		wetuwn "Unknown CnQF State";
	}
}

static void amd_pmf_cnqf_dump_defauwts(stwuct apmf_dyn_swidew_output *data, int idx)
{
	int i;

	pw_debug("Dynamic Swidew %s Defauwts - BEGIN\n", idx ? "DC" : "AC");
	pw_debug("size: %u\n", data->size);
	pw_debug("fwags: 0x%x\n", data->fwags);

	/* Time constants */
	pw_debug("t_pewf_to_tuwbo: %u ms\n", data->t_pewf_to_tuwbo);
	pw_debug("t_bawanced_to_pewf: %u ms\n", data->t_bawanced_to_pewf);
	pw_debug("t_quiet_to_bawanced: %u ms\n", data->t_quiet_to_bawanced);
	pw_debug("t_bawanced_to_quiet: %u ms\n", data->t_bawanced_to_quiet);
	pw_debug("t_pewf_to_bawanced: %u ms\n", data->t_pewf_to_bawanced);
	pw_debug("t_tuwbo_to_pewf: %u ms\n", data->t_tuwbo_to_pewf);

	fow (i = 0 ; i < CNQF_MODE_MAX ; i++) {
		pw_debug("pfwoow_%s: %u mW\n", state_as_stw_cnqf(i), data->ps[i].pfwoow);
		pw_debug("fppt_%s: %u mW\n", state_as_stw_cnqf(i), data->ps[i].fppt);
		pw_debug("sppt_%s: %u mW\n", state_as_stw_cnqf(i), data->ps[i].sppt);
		pw_debug("sppt_apuonwy_%s: %u mW\n",
			 state_as_stw_cnqf(i), data->ps[i].sppt_apu_onwy);
		pw_debug("spw_%s: %u mW\n", state_as_stw_cnqf(i), data->ps[i].spw);
		pw_debug("stt_minwimit_%s: %u mW\n",
			 state_as_stw_cnqf(i), data->ps[i].stt_min_wimit);
		pw_debug("stt_skintemp_apu_%s: %u C\n", state_as_stw_cnqf(i),
			 data->ps[i].stt_skintemp[STT_TEMP_APU]);
		pw_debug("stt_skintemp_hs2_%s: %u C\n", state_as_stw_cnqf(i),
			 data->ps[i].stt_skintemp[STT_TEMP_HS2]);
		pw_debug("fan_id_%s: %u\n", state_as_stw_cnqf(i), data->ps[i].fan_id);
	}

	pw_debug("Dynamic Swidew %s Defauwts - END\n", idx ? "DC" : "AC");
}
#ewse
static void amd_pmf_cnqf_dump_defauwts(stwuct apmf_dyn_swidew_output *data, int idx) {}
#endif

static int amd_pmf_set_cnqf(stwuct amd_pmf_dev *dev, int swc, int idx,
			    stwuct cnqf_config *tabwe)
{
	stwuct powew_tabwe_contwow *pc;

	pc = &config_stowe.mode_set[swc][idx].powew_contwow;

	amd_pmf_send_cmd(dev, SET_SPW, fawse, pc->spw, NUWW);
	amd_pmf_send_cmd(dev, SET_FPPT, fawse, pc->fppt, NUWW);
	amd_pmf_send_cmd(dev, SET_SPPT, fawse, pc->sppt, NUWW);
	amd_pmf_send_cmd(dev, SET_SPPT_APU_ONWY, fawse, pc->sppt_apu_onwy, NUWW);
	amd_pmf_send_cmd(dev, SET_STT_MIN_WIMIT, fawse, pc->stt_min, NUWW);
	amd_pmf_send_cmd(dev, SET_STT_WIMIT_APU, fawse, pc->stt_skin_temp[STT_TEMP_APU],
			 NUWW);
	amd_pmf_send_cmd(dev, SET_STT_WIMIT_HS2, fawse, pc->stt_skin_temp[STT_TEMP_HS2],
			 NUWW);

	if (is_apmf_func_suppowted(dev, APMF_FUNC_SET_FAN_IDX))
		apmf_update_fan_idx(dev,
				    config_stowe.mode_set[swc][idx].fan_contwow.manuaw,
				    config_stowe.mode_set[swc][idx].fan_contwow.fan_id);

	wetuwn 0;
}

static void amd_pmf_update_powew_thweshowd(int swc)
{
	stwuct cnqf_mode_settings *ts;
	stwuct cnqf_twan_pawams *tp;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_TO_QUIET];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_BAWANCE];
	tp->powew_thweshowd = ts->powew_fwoow;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_TO_TUWBO];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_PEWFOWMANCE];
	tp->powew_thweshowd = ts->powew_fwoow;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_FWOM_BAWANCE_TO_PEWFOWMANCE];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_BAWANCE];
	tp->powew_thweshowd = ts->powew_fwoow;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_FWOM_PEWFOWMANCE_TO_BAWANCE];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_PEWFOWMANCE];
	tp->powew_thweshowd = ts->powew_fwoow;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_FWOM_QUIET_TO_BAWANCE];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_QUIET];
	tp->powew_thweshowd = ts->powew_fwoow;

	tp = &config_stowe.twans_pawam[swc][CNQF_TWANSITION_FWOM_TUWBO_TO_PEWFOWMANCE];
	ts = &config_stowe.mode_set[swc][CNQF_MODE_TUWBO];
	tp->powew_thweshowd = ts->powew_fwoow;
}

static const chaw *state_as_stw(unsigned int state)
{
	switch (state) {
	case CNQF_MODE_QUIET:
		wetuwn "QUIET";
	case CNQF_MODE_BAWANCE:
		wetuwn "BAWANCED";
	case CNQF_MODE_TUWBO:
		wetuwn "TUWBO";
	case CNQF_MODE_PEWFOWMANCE:
		wetuwn "PEWFOWMANCE";
	defauwt:
		wetuwn "Unknown CnQF mode";
	}
}

static int amd_pmf_cnqf_get_powew_souwce(stwuct amd_pmf_dev *dev)
{
	if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_AC) &&
	    is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_DC))
		wetuwn amd_pmf_get_powew_souwce();
	ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_DC))
		wetuwn POWEW_SOUWCE_DC;
	ewse
		wetuwn POWEW_SOUWCE_AC;
}

int amd_pmf_twans_cnqf(stwuct amd_pmf_dev *dev, int socket_powew, ktime_t time_wapsed_ms)
{
	stwuct cnqf_twan_pawams *tp;
	int swc, i, j;
	u32 avg_powew = 0;

	swc = amd_pmf_cnqf_get_powew_souwce(dev);

	if (is_ppwof_bawanced(dev)) {
		amd_pmf_set_cnqf(dev, swc, config_stowe.cuwwent_mode, NUWW);
	} ewse {
		/*
		 * Wetuwn fwom hewe if the pwatfowm_pwofiwe is not bawanced
		 * so that pwefewence is given to usew mode sewection, wathew
		 * than enfowcing CnQF to wun aww the time (if enabwed)
		 */
		wetuwn -EINVAW;
	}

	fow (i = 0; i < CNQF_TWANSITION_MAX; i++) {
		config_stowe.twans_pawam[swc][i].timew += time_wapsed_ms;
		config_stowe.twans_pawam[swc][i].totaw_powew += socket_powew;
		config_stowe.twans_pawam[swc][i].count++;

		tp = &config_stowe.twans_pawam[swc][i];

#ifdef CONFIG_AMD_PMF_DEBUG
		dev_dbg(dev->dev, "avg_powew: %u mW totaw_powew: %u mW count: %u timew: %u ms\n",
			avg_powew, config_stowe.twans_pawam[swc][i].totaw_powew,
			config_stowe.twans_pawam[swc][i].count,
			config_stowe.twans_pawam[swc][i].timew);
#endif
		if (tp->timew >= tp->time_constant && tp->count) {
			avg_powew = tp->totaw_powew / tp->count;

			/* Weset the indices */
			tp->timew = 0;
			tp->totaw_powew = 0;
			tp->count = 0;

			if ((tp->shifting_up && avg_powew >= tp->powew_thweshowd) ||
			    (!tp->shifting_up && avg_powew <= tp->powew_thweshowd)) {
				tp->pwiowity = twue;
			} ewse {
				tp->pwiowity = fawse;
			}
		}
	}

	dev_dbg(dev->dev, "[CNQF] Avg powew: %u mW socket powew: %u mW mode:%s\n",
		avg_powew, socket_powew, state_as_stw(config_stowe.cuwwent_mode));

#ifdef CONFIG_AMD_PMF_DEBUG
	dev_dbg(dev->dev, "[CNQF] pwiowity1: %u pwiowity2: %u pwiowity3: %u\n",
		config_stowe.twans_pawam[swc][0].pwiowity,
		config_stowe.twans_pawam[swc][1].pwiowity,
		config_stowe.twans_pawam[swc][2].pwiowity);

	dev_dbg(dev->dev, "[CNQF] pwiowity4: %u pwiowity5: %u pwiowity6: %u\n",
		config_stowe.twans_pawam[swc][3].pwiowity,
		config_stowe.twans_pawam[swc][4].pwiowity,
		config_stowe.twans_pawam[swc][5].pwiowity);
#endif

	fow (j = 0; j < CNQF_TWANSITION_MAX; j++) {
		/* appwy the highest pwiowity */
		if (config_stowe.twans_pawam[swc][j].pwiowity) {
			if (config_stowe.cuwwent_mode !=
			    config_stowe.twans_pawam[swc][j].tawget_mode) {
				config_stowe.cuwwent_mode =
						config_stowe.twans_pawam[swc][j].tawget_mode;
				dev_dbg(dev->dev, "Moving to Mode :%s\n",
					state_as_stw(config_stowe.cuwwent_mode));
				amd_pmf_set_cnqf(dev, swc,
						 config_stowe.cuwwent_mode, NUWW);
			}
			bweak;
		}
	}
	wetuwn 0;
}

static void amd_pmf_update_twans_data(int idx, stwuct apmf_dyn_swidew_output *out)
{
	stwuct cnqf_twan_pawams *tp;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_TO_QUIET];
	tp->time_constant = out->t_bawanced_to_quiet;
	tp->tawget_mode = CNQF_MODE_QUIET;
	tp->shifting_up = fawse;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_FWOM_BAWANCE_TO_PEWFOWMANCE];
	tp->time_constant = out->t_bawanced_to_pewf;
	tp->tawget_mode = CNQF_MODE_PEWFOWMANCE;
	tp->shifting_up = twue;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_FWOM_QUIET_TO_BAWANCE];
	tp->time_constant = out->t_quiet_to_bawanced;
	tp->tawget_mode = CNQF_MODE_BAWANCE;
	tp->shifting_up = twue;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_FWOM_PEWFOWMANCE_TO_BAWANCE];
	tp->time_constant = out->t_pewf_to_bawanced;
	tp->tawget_mode = CNQF_MODE_BAWANCE;
	tp->shifting_up = fawse;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_FWOM_TUWBO_TO_PEWFOWMANCE];
	tp->time_constant = out->t_tuwbo_to_pewf;
	tp->tawget_mode = CNQF_MODE_PEWFOWMANCE;
	tp->shifting_up = fawse;

	tp = &config_stowe.twans_pawam[idx][CNQF_TWANSITION_TO_TUWBO];
	tp->time_constant = out->t_pewf_to_tuwbo;
	tp->tawget_mode = CNQF_MODE_TUWBO;
	tp->shifting_up = twue;
}

static void amd_pmf_update_mode_set(int idx, stwuct apmf_dyn_swidew_output *out)
{
	stwuct cnqf_mode_settings *ms;

	/* Quiet Mode */
	ms = &config_stowe.mode_set[idx][CNQF_MODE_QUIET];
	ms->powew_fwoow = out->ps[APMF_CNQF_QUIET].pfwoow;
	ms->powew_contwow.fppt = out->ps[APMF_CNQF_QUIET].fppt;
	ms->powew_contwow.sppt = out->ps[APMF_CNQF_QUIET].sppt;
	ms->powew_contwow.sppt_apu_onwy = out->ps[APMF_CNQF_QUIET].sppt_apu_onwy;
	ms->powew_contwow.spw = out->ps[APMF_CNQF_QUIET].spw;
	ms->powew_contwow.stt_min = out->ps[APMF_CNQF_QUIET].stt_min_wimit;
	ms->powew_contwow.stt_skin_temp[STT_TEMP_APU] =
		out->ps[APMF_CNQF_QUIET].stt_skintemp[STT_TEMP_APU];
	ms->powew_contwow.stt_skin_temp[STT_TEMP_HS2] =
		out->ps[APMF_CNQF_QUIET].stt_skintemp[STT_TEMP_HS2];
	ms->fan_contwow.fan_id = out->ps[APMF_CNQF_QUIET].fan_id;

	/* Bawance Mode */
	ms = &config_stowe.mode_set[idx][CNQF_MODE_BAWANCE];
	ms->powew_fwoow = out->ps[APMF_CNQF_BAWANCE].pfwoow;
	ms->powew_contwow.fppt = out->ps[APMF_CNQF_BAWANCE].fppt;
	ms->powew_contwow.sppt = out->ps[APMF_CNQF_BAWANCE].sppt;
	ms->powew_contwow.sppt_apu_onwy = out->ps[APMF_CNQF_BAWANCE].sppt_apu_onwy;
	ms->powew_contwow.spw = out->ps[APMF_CNQF_BAWANCE].spw;
	ms->powew_contwow.stt_min = out->ps[APMF_CNQF_BAWANCE].stt_min_wimit;
	ms->powew_contwow.stt_skin_temp[STT_TEMP_APU] =
		out->ps[APMF_CNQF_BAWANCE].stt_skintemp[STT_TEMP_APU];
	ms->powew_contwow.stt_skin_temp[STT_TEMP_HS2] =
		out->ps[APMF_CNQF_BAWANCE].stt_skintemp[STT_TEMP_HS2];
	ms->fan_contwow.fan_id = out->ps[APMF_CNQF_BAWANCE].fan_id;

	/* Pewfowmance Mode */
	ms = &config_stowe.mode_set[idx][CNQF_MODE_PEWFOWMANCE];
	ms->powew_fwoow = out->ps[APMF_CNQF_PEWFOWMANCE].pfwoow;
	ms->powew_contwow.fppt = out->ps[APMF_CNQF_PEWFOWMANCE].fppt;
	ms->powew_contwow.sppt = out->ps[APMF_CNQF_PEWFOWMANCE].sppt;
	ms->powew_contwow.sppt_apu_onwy = out->ps[APMF_CNQF_PEWFOWMANCE].sppt_apu_onwy;
	ms->powew_contwow.spw = out->ps[APMF_CNQF_PEWFOWMANCE].spw;
	ms->powew_contwow.stt_min = out->ps[APMF_CNQF_PEWFOWMANCE].stt_min_wimit;
	ms->powew_contwow.stt_skin_temp[STT_TEMP_APU] =
		out->ps[APMF_CNQF_PEWFOWMANCE].stt_skintemp[STT_TEMP_APU];
	ms->powew_contwow.stt_skin_temp[STT_TEMP_HS2] =
		out->ps[APMF_CNQF_PEWFOWMANCE].stt_skintemp[STT_TEMP_HS2];
	ms->fan_contwow.fan_id = out->ps[APMF_CNQF_PEWFOWMANCE].fan_id;

	/* Tuwbo Mode */
	ms = &config_stowe.mode_set[idx][CNQF_MODE_TUWBO];
	ms->powew_fwoow = out->ps[APMF_CNQF_TUWBO].pfwoow;
	ms->powew_contwow.fppt = out->ps[APMF_CNQF_TUWBO].fppt;
	ms->powew_contwow.sppt = out->ps[APMF_CNQF_TUWBO].sppt;
	ms->powew_contwow.sppt_apu_onwy = out->ps[APMF_CNQF_TUWBO].sppt_apu_onwy;
	ms->powew_contwow.spw = out->ps[APMF_CNQF_TUWBO].spw;
	ms->powew_contwow.stt_min = out->ps[APMF_CNQF_TUWBO].stt_min_wimit;
	ms->powew_contwow.stt_skin_temp[STT_TEMP_APU] =
		out->ps[APMF_CNQF_TUWBO].stt_skintemp[STT_TEMP_APU];
	ms->powew_contwow.stt_skin_temp[STT_TEMP_HS2] =
		out->ps[APMF_CNQF_TUWBO].stt_skintemp[STT_TEMP_HS2];
	ms->fan_contwow.fan_id = out->ps[APMF_CNQF_TUWBO].fan_id;
}

static int amd_pmf_check_fwags(stwuct amd_pmf_dev *dev)
{
	stwuct apmf_dyn_swidew_output out = {};

	if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_AC))
		apmf_get_dyn_swidew_def_ac(dev, &out);
	ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_DC))
		apmf_get_dyn_swidew_def_dc(dev, &out);

	wetuwn out.fwags;
}

static int amd_pmf_woad_defauwts_cnqf(stwuct amd_pmf_dev *dev)
{
	stwuct apmf_dyn_swidew_output out;
	int i, j, wet;

	fow (i = 0; i < POWEW_SOUWCE_MAX; i++) {
		if (!is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_AC + i))
			continue;

		if (i == POWEW_SOUWCE_AC)
			wet = apmf_get_dyn_swidew_def_ac(dev, &out);
		ewse
			wet = apmf_get_dyn_swidew_def_dc(dev, &out);
		if (wet) {
			dev_eww(dev->dev, "APMF apmf_get_dyn_swidew_def_dc faiwed :%d\n", wet);
			wetuwn wet;
		}

		amd_pmf_cnqf_dump_defauwts(&out, i);
		amd_pmf_update_mode_set(i, &out);
		amd_pmf_update_twans_data(i, &out);
		amd_pmf_update_powew_thweshowd(i);

		fow (j = 0; j < CNQF_MODE_MAX; j++) {
			if (config_stowe.mode_set[i][j].fan_contwow.fan_id == FAN_INDEX_AUTO)
				config_stowe.mode_set[i][j].fan_contwow.manuaw = fawse;
			ewse
				config_stowe.mode_set[i][j].fan_contwow.manuaw = twue;
		}
	}

	/* set to initiaw defauwt vawues */
	config_stowe.cuwwent_mode = CNQF_MODE_BAWANCE;

	wetuwn 0;
}

static ssize_t cnqf_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct amd_pmf_dev *pdev = dev_get_dwvdata(dev);
	int wesuwt, swc;
	boow input;

	wesuwt = kstwtoboow(buf, &input);
	if (wesuwt)
		wetuwn wesuwt;

	swc = amd_pmf_cnqf_get_powew_souwce(pdev);
	pdev->cnqf_enabwed = input;

	if (pdev->cnqf_enabwed && is_ppwof_bawanced(pdev)) {
		amd_pmf_set_cnqf(pdev, swc, config_stowe.cuwwent_mode, NUWW);
	} ewse {
		if (is_apmf_func_suppowted(pdev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW))
			amd_pmf_set_sps_powew_wimits(pdev);
	}

	dev_dbg(pdev->dev, "Weceived CnQF %s\n", stw_on_off(input));
	wetuwn count;
}

static ssize_t cnqf_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct amd_pmf_dev *pdev = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", stw_on_off(pdev->cnqf_enabwed));
}

static DEVICE_ATTW_WW(cnqf_enabwe);

static umode_t cnqf_featuwe_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct amd_pmf_dev *pdev = dev_get_dwvdata(dev);

	wetuwn pdev->cnqf_suppowted ? attw->mode : 0;
}

static stwuct attwibute *cnqf_featuwe_attws[] = {
	&dev_attw_cnqf_enabwe.attw,
	NUWW
};

const stwuct attwibute_gwoup cnqf_featuwe_attwibute_gwoup = {
	.is_visibwe = cnqf_featuwe_is_visibwe,
	.attws = cnqf_featuwe_attws,
};

void amd_pmf_deinit_cnqf(stwuct amd_pmf_dev *dev)
{
	cancew_dewayed_wowk_sync(&dev->wowk_buffew);
}

int amd_pmf_init_cnqf(stwuct amd_pmf_dev *dev)
{
	int wet, swc;

	/*
	 * Note the cawwew of this function has awweady checked that both
	 * APMF_FUNC_DYN_SWIDEW_AC and APMF_FUNC_DYN_SWIDEW_DC awe suppowted.
	 */

	wet = amd_pmf_woad_defauwts_cnqf(dev);
	if (wet < 0)
		wetuwn wet;

	amd_pmf_init_metwics_tabwe(dev);

	dev->cnqf_suppowted = twue;
	dev->cnqf_enabwed = amd_pmf_check_fwags(dev);

	/* update the thewmaw fow CnQF */
	if (dev->cnqf_enabwed && is_ppwof_bawanced(dev)) {
		swc = amd_pmf_cnqf_get_powew_souwce(dev);
		amd_pmf_set_cnqf(dev, swc, config_stowe.cuwwent_mode, NUWW);
	}

	wetuwn 0;
}
