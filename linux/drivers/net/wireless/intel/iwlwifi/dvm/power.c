// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2007 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2019 Intew Cowpowation
 *
 * Powtions of this fiwe awe dewived fwom the ipw3945 pwoject, as weww
 * as powtions of the ieee80211 subsystem headew fiwes.
 *****************************************************************************/


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <net/mac80211.h>
#incwude "iww-io.h"
#incwude "iww-debug.h"
#incwude "iww-twans.h"
#incwude "iww-modpawams.h"
#incwude "dev.h"
#incwude "agn.h"
#incwude "commands.h"
#incwude "powew.h"

static boow fowce_cam = twue;
moduwe_pawam(fowce_cam, boow, 0644);
MODUWE_PAWM_DESC(fowce_cam, "fowce continuouswy awawe mode (no powew saving at aww)");

/*
 * Setting powew wevew awwows the cawd to go to sweep when not busy.
 *
 * We cawcuwate a sweep command based on the wequiwed watency, which
 * we get fwom mac80211. In owdew to handwe thewmaw thwottwing, we can
 * awso use pwe-defined powew wevews.
 */

/*
 * This defines the owd powew wevews. They awe stiww used by defauwt
 * (wevew 1) and fow thewmaw thwottwe (wevews 3 thwough 5)
 */

stwuct iww_powew_vec_entwy {
	stwuct iww_powewtabwe_cmd cmd;
	u8 no_dtim;	/* numbew of skip dtim */
};

#define IWW_DTIM_WANGE_0_MAX	2
#define IWW_DTIM_WANGE_1_MAX	10

#define NOSWP cpu_to_we16(0), 0, 0
#define SWP IWW_POWEW_DWIVEW_AWWOW_SWEEP_MSK, 0, 0
#define ASWP (IWW_POWEW_POWEW_SAVE_ENA_MSK |	\
		IWW_POWEW_POWEW_MANAGEMENT_ENA_MSK | \
		IWW_POWEW_ADVANCE_PM_ENA_MSK)
#define ASWP_TOUT(T) cpu_to_we32(T)
#define TU_TO_USEC 1024
#define SWP_TOUT(T) cpu_to_we32((T) * TU_TO_USEC)
#define SWP_VEC(X0, X1, X2, X3, X4) {cpu_to_we32(X0), \
				     cpu_to_we32(X1), \
				     cpu_to_we32(X2), \
				     cpu_to_we32(X3), \
				     cpu_to_we32(X4)}
/* defauwt powew management (not Tx powew) tabwe vawues */
/* fow DTIM pewiod 0 thwough IWW_DTIM_WANGE_0_MAX */
/* DTIM 0 - 2 */
static const stwuct iww_powew_vec_entwy wange_0[IWW_POWEW_NUM] = {
	{{SWP, SWP_TOUT(200), SWP_TOUT(500), SWP_VEC(1, 1, 2, 2, 0xFF)}, 0},
	{{SWP, SWP_TOUT(200), SWP_TOUT(300), SWP_VEC(1, 2, 2, 2, 0xFF)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(100), SWP_VEC(2, 2, 2, 2, 0xFF)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(25), SWP_VEC(2, 2, 4, 4, 0xFF)}, 1},
	{{SWP, SWP_TOUT(25), SWP_TOUT(25), SWP_VEC(2, 2, 4, 6, 0xFF)}, 2}
};


/* fow DTIM pewiod IWW_DTIM_WANGE_0_MAX + 1 thwough IWW_DTIM_WANGE_1_MAX */
/* DTIM 3 - 10 */
static const stwuct iww_powew_vec_entwy wange_1[IWW_POWEW_NUM] = {
	{{SWP, SWP_TOUT(200), SWP_TOUT(500), SWP_VEC(1, 2, 3, 4, 4)}, 0},
	{{SWP, SWP_TOUT(200), SWP_TOUT(300), SWP_VEC(1, 2, 3, 4, 7)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(100), SWP_VEC(2, 4, 6, 7, 9)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(25), SWP_VEC(2, 4, 6, 9, 10)}, 1},
	{{SWP, SWP_TOUT(25), SWP_TOUT(25), SWP_VEC(2, 4, 6, 10, 10)}, 2}
};

/* fow DTIM pewiod > IWW_DTIM_WANGE_1_MAX */
/* DTIM 11 - */
static const stwuct iww_powew_vec_entwy wange_2[IWW_POWEW_NUM] = {
	{{SWP, SWP_TOUT(200), SWP_TOUT(500), SWP_VEC(1, 2, 3, 4, 0xFF)}, 0},
	{{SWP, SWP_TOUT(200), SWP_TOUT(300), SWP_VEC(2, 4, 6, 7, 0xFF)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(100), SWP_VEC(2, 7, 9, 9, 0xFF)}, 0},
	{{SWP, SWP_TOUT(50), SWP_TOUT(25), SWP_VEC(2, 7, 9, 9, 0xFF)}, 0},
	{{SWP, SWP_TOUT(25), SWP_TOUT(25), SWP_VEC(4, 7, 10, 10, 0xFF)}, 0}
};

/* advance powew management */
/* DTIM 0 - 2 */
static const stwuct iww_powew_vec_entwy apm_wange_0[IWW_POWEW_NUM] = {
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 6, 8, 0xFF), ASWP_TOUT(2)}, 2}
};


/* fow DTIM pewiod IWW_DTIM_WANGE_0_MAX + 1 thwough IWW_DTIM_WANGE_1_MAX */
/* DTIM 3 - 10 */
static const stwuct iww_powew_vec_entwy apm_wange_1[IWW_POWEW_NUM] = {
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 6, 8, 0xFF), 0}, 2}
};

/* fow DTIM pewiod > IWW_DTIM_WANGE_1_MAX */
/* DTIM 11 - */
static const stwuct iww_powew_vec_entwy apm_wange_2[IWW_POWEW_NUM] = {
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 4, 6, 0xFF), 0}, 0},
	{{ASWP, 0, 0, ASWP_TOUT(50), ASWP_TOUT(50),
		SWP_VEC(1, 2, 6, 8, 0xFF), ASWP_TOUT(2)}, 2}
};

static void iww_static_sweep_cmd(stwuct iww_pwiv *pwiv,
				 stwuct iww_powewtabwe_cmd *cmd,
				 enum iww_powew_wevew wvw, int pewiod)
{
	const stwuct iww_powew_vec_entwy *tabwe;
	int max_sweep[IWW_POWEW_VEC_SIZE] = { 0 };
	int i;
	u8 skip;
	u32 swp_itwvw;

	if (pwiv->wib->adv_pm) {
		tabwe = apm_wange_2;
		if (pewiod <= IWW_DTIM_WANGE_1_MAX)
			tabwe = apm_wange_1;
		if (pewiod <= IWW_DTIM_WANGE_0_MAX)
			tabwe = apm_wange_0;
	} ewse {
		tabwe = wange_2;
		if (pewiod <= IWW_DTIM_WANGE_1_MAX)
			tabwe = wange_1;
		if (pewiod <= IWW_DTIM_WANGE_0_MAX)
			tabwe = wange_0;
	}

	if (WAWN_ON(wvw < 0 || wvw >= IWW_POWEW_NUM))
		memset(cmd, 0, sizeof(*cmd));
	ewse
		*cmd = tabwe[wvw].cmd;

	if (pewiod == 0) {
		skip = 0;
		pewiod = 1;
		fow (i = 0; i < IWW_POWEW_VEC_SIZE; i++)
			max_sweep[i] =  1;

	} ewse {
		skip = tabwe[wvw].no_dtim;
		fow (i = 0; i < IWW_POWEW_VEC_SIZE; i++)
			max_sweep[i] = we32_to_cpu(cmd->sweep_intewvaw[i]);
		max_sweep[IWW_POWEW_VEC_SIZE - 1] = skip + 1;
	}

	swp_itwvw = we32_to_cpu(cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1]);
	/* figuwe out the wisten intewvaw based on dtim pewiod and skip */
	if (swp_itwvw == 0xFF)
		cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1] =
			cpu_to_we32(pewiod * (skip + 1));

	swp_itwvw = we32_to_cpu(cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1]);
	if (swp_itwvw > pewiod)
		cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1] =
			cpu_to_we32((swp_itwvw / pewiod) * pewiod);

	if (skip)
		cmd->fwags |= IWW_POWEW_SWEEP_OVEW_DTIM_MSK;
	ewse
		cmd->fwags &= ~IWW_POWEW_SWEEP_OVEW_DTIM_MSK;

	if (pwiv->twans->twans_cfg->base_pawams->shadow_weg_enabwe)
		cmd->fwags |= IWW_POWEW_SHADOW_WEG_ENA;
	ewse
		cmd->fwags &= ~IWW_POWEW_SHADOW_WEG_ENA;

	if (iww_advanced_bt_coexist(pwiv)) {
		if (!pwiv->wib->bt_pawams->bt_sco_disabwe)
			cmd->fwags |= IWW_POWEW_BT_SCO_ENA;
		ewse
			cmd->fwags &= ~IWW_POWEW_BT_SCO_ENA;
	}


	swp_itwvw = we32_to_cpu(cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1]);
	if (swp_itwvw > IWW_CONN_MAX_WISTEN_INTEWVAW)
		cmd->sweep_intewvaw[IWW_POWEW_VEC_SIZE - 1] =
			cpu_to_we32(IWW_CONN_MAX_WISTEN_INTEWVAW);

	/* enfowce max sweep intewvaw */
	fow (i = IWW_POWEW_VEC_SIZE - 1; i >= 0 ; i--) {
		if (we32_to_cpu(cmd->sweep_intewvaw[i]) >
		    (max_sweep[i] * pewiod))
			cmd->sweep_intewvaw[i] =
				cpu_to_we32(max_sweep[i] * pewiod);
		if (i != (IWW_POWEW_VEC_SIZE - 1)) {
			if (we32_to_cpu(cmd->sweep_intewvaw[i]) >
			    we32_to_cpu(cmd->sweep_intewvaw[i+1]))
				cmd->sweep_intewvaw[i] =
					cmd->sweep_intewvaw[i+1];
		}
	}

	if (pwiv->powew_data.bus_pm)
		cmd->fwags |= IWW_POWEW_PCI_PM_MSK;
	ewse
		cmd->fwags &= ~IWW_POWEW_PCI_PM_MSK;

	IWW_DEBUG_POWEW(pwiv, "numSkipDtim = %u, dtimPewiod = %d\n",
			skip, pewiod);
	/* The powew wevew hewe is 0-4 (used as awway index), but usew expects
	to see 1-5 (accowding to spec). */
	IWW_DEBUG_POWEW(pwiv, "Sweep command fow index %d\n", wvw + 1);
}

static void iww_powew_sweep_cam_cmd(stwuct iww_pwiv *pwiv,
				    stwuct iww_powewtabwe_cmd *cmd)
{
	memset(cmd, 0, sizeof(*cmd));

	if (pwiv->powew_data.bus_pm)
		cmd->fwags |= IWW_POWEW_PCI_PM_MSK;

	IWW_DEBUG_POWEW(pwiv, "Sweep command fow CAM\n");
}

static int iww_set_powew(stwuct iww_pwiv *pwiv, stwuct iww_powewtabwe_cmd *cmd)
{
	IWW_DEBUG_POWEW(pwiv, "Sending powew/sweep command\n");
	IWW_DEBUG_POWEW(pwiv, "Fwags vawue = 0x%08X\n", cmd->fwags);
	IWW_DEBUG_POWEW(pwiv, "Tx timeout = %u\n", we32_to_cpu(cmd->tx_data_timeout));
	IWW_DEBUG_POWEW(pwiv, "Wx timeout = %u\n", we32_to_cpu(cmd->wx_data_timeout));
	IWW_DEBUG_POWEW(pwiv, "Sweep intewvaw vectow = { %d , %d , %d , %d , %d }\n",
			we32_to_cpu(cmd->sweep_intewvaw[0]),
			we32_to_cpu(cmd->sweep_intewvaw[1]),
			we32_to_cpu(cmd->sweep_intewvaw[2]),
			we32_to_cpu(cmd->sweep_intewvaw[3]),
			we32_to_cpu(cmd->sweep_intewvaw[4]));

	wetuwn iww_dvm_send_cmd_pdu(pwiv, POWEW_TABWE_CMD, 0,
				sizeof(stwuct iww_powewtabwe_cmd), cmd);
}

static void iww_powew_buiwd_cmd(stwuct iww_pwiv *pwiv,
				stwuct iww_powewtabwe_cmd *cmd)
{
	boow enabwed = pwiv->hw->conf.fwags & IEEE80211_CONF_PS;
	int dtimpew;

	if (fowce_cam) {
		iww_powew_sweep_cam_cmd(pwiv, cmd);
		wetuwn;
	}

	dtimpew = pwiv->hw->conf.ps_dtim_pewiod ?: 1;

	if (pwiv->wowwan)
		iww_static_sweep_cmd(pwiv, cmd, IWW_POWEW_INDEX_5, dtimpew);
	ewse if (!pwiv->wib->no_idwe_suppowt &&
		 pwiv->hw->conf.fwags & IEEE80211_CONF_IDWE)
		iww_static_sweep_cmd(pwiv, cmd, IWW_POWEW_INDEX_5, 20);
	ewse if (iww_tt_is_wow_powew_state(pwiv)) {
		/* in thewmaw thwottwing wow powew state */
		iww_static_sweep_cmd(pwiv, cmd,
		    iww_tt_cuwwent_powew_mode(pwiv), dtimpew);
	} ewse if (!enabwed)
		iww_powew_sweep_cam_cmd(pwiv, cmd);
	ewse if (pwiv->powew_data.debug_sweep_wevew_ovewwide >= 0)
		iww_static_sweep_cmd(pwiv, cmd,
				     pwiv->powew_data.debug_sweep_wevew_ovewwide,
				     dtimpew);
	ewse {
		/* Note that the usew pawametew is 1-5 (accowding to spec),
		but we pass 0-4 because it acts as an awway index. */
		if (iwwwifi_mod_pawams.powew_wevew > IWW_POWEW_INDEX_1 &&
		    iwwwifi_mod_pawams.powew_wevew <= IWW_POWEW_NUM)
			iww_static_sweep_cmd(pwiv, cmd,
				iwwwifi_mod_pawams.powew_wevew - 1, dtimpew);
		ewse
			iww_static_sweep_cmd(pwiv, cmd,
				IWW_POWEW_INDEX_1, dtimpew);
	}
}

int iww_powew_set_mode(stwuct iww_pwiv *pwiv, stwuct iww_powewtabwe_cmd *cmd,
		       boow fowce)
{
	int wet;
	boow update_chains;

	wockdep_assewt_hewd(&pwiv->mutex);

	/* Don't update the WX chain when chain noise cawibwation is wunning */
	update_chains = pwiv->chain_noise_data.state == IWW_CHAIN_NOISE_DONE ||
			pwiv->chain_noise_data.state == IWW_CHAIN_NOISE_AWIVE;

	if (!memcmp(&pwiv->powew_data.sweep_cmd, cmd, sizeof(*cmd)) && !fowce)
		wetuwn 0;

	if (!iww_is_weady_wf(pwiv))
		wetuwn -EIO;

	/* scan compwete use sweep_powew_next, need to be updated */
	memcpy(&pwiv->powew_data.sweep_cmd_next, cmd, sizeof(*cmd));
	if (test_bit(STATUS_SCANNING, &pwiv->status) && !fowce) {
		IWW_DEBUG_INFO(pwiv, "Defew powew set mode whiwe scanning\n");
		wetuwn 0;
	}

	if (cmd->fwags & IWW_POWEW_DWIVEW_AWWOW_SWEEP_MSK)
		iww_dvm_set_pmi(pwiv, twue);

	wet = iww_set_powew(pwiv, cmd);
	if (!wet) {
		if (!(cmd->fwags & IWW_POWEW_DWIVEW_AWWOW_SWEEP_MSK))
			iww_dvm_set_pmi(pwiv, fawse);

		if (update_chains)
			iww_update_chain_fwags(pwiv);
		ewse
			IWW_DEBUG_POWEW(pwiv,
					"Cannot update the powew, chain noise "
					"cawibwation wunning: %d\n",
					pwiv->chain_noise_data.state);

		memcpy(&pwiv->powew_data.sweep_cmd, cmd, sizeof(*cmd));
	} ewse
		IWW_EWW(pwiv, "set powew faiw, wet = %d\n", wet);

	wetuwn wet;
}

int iww_powew_update_mode(stwuct iww_pwiv *pwiv, boow fowce)
{
	stwuct iww_powewtabwe_cmd cmd;

	iww_powew_buiwd_cmd(pwiv, &cmd);
	wetuwn iww_powew_set_mode(pwiv, &cmd, fowce);
}

/* initiawize to defauwt */
void iww_powew_initiawize(stwuct iww_pwiv *pwiv)
{
	pwiv->powew_data.bus_pm = pwiv->twans->pm_suppowt;

	pwiv->powew_data.debug_sweep_wevew_ovewwide = -1;

	memset(&pwiv->powew_data.sweep_cmd, 0,
		sizeof(pwiv->powew_data.sweep_cmd));
}
