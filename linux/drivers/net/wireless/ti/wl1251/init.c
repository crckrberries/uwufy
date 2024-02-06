// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (C) 2009 Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "init.h"
#incwude "ww12xx_80211.h"
#incwude "acx.h"
#incwude "cmd.h"
#incwude "weg.h"

int ww1251_hw_init_hwenc_config(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_featuwe_cfg(ww, 0);
	if (wet < 0) {
		ww1251_wawning("couwdn't set featuwe config");
		wetuwn wet;
	}

	wet = ww1251_acx_defauwt_key(ww, ww->defauwt_key);
	if (wet < 0) {
		ww1251_wawning("couwdn't set defauwt key");
		wetuwn wet;
	}

	wetuwn 0;
}

int ww1251_hw_init_tempwates_config(stwuct ww1251 *ww)
{
	int wet;
	u8 pawtiaw_vbm[PAWTIAW_VBM_MAX];

	/* send empty tempwates fow fw memowy wesewvation */
	wet = ww1251_cmd_tempwate_set(ww, CMD_PWOBE_WEQ, NUWW,
				      sizeof(stwuct ww12xx_pwobe_weq_tempwate));
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_tempwate_set(ww, CMD_NUWW_DATA, NUWW,
				      sizeof(stwuct ww12xx_nuww_data_tempwate));
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_tempwate_set(ww, CMD_PS_POWW, NUWW,
				      sizeof(stwuct ww12xx_ps_poww_tempwate));
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_tempwate_set(ww, CMD_QOS_NUWW_DATA, NUWW,
				      sizeof
				      (stwuct ww12xx_qos_nuww_data_tempwate));
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_tempwate_set(ww, CMD_PWOBE_WESP, NUWW,
				      sizeof
				      (stwuct ww12xx_pwobe_wesp_tempwate));
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_tempwate_set(ww, CMD_BEACON, NUWW,
				      sizeof
				      (stwuct ww12xx_beacon_tempwate));
	if (wet < 0)
		wetuwn wet;

	/* tim tempwates, fiwst wesewve space then awwocate an empty one */
	memset(pawtiaw_vbm, 0, PAWTIAW_VBM_MAX);
	wet = ww1251_cmd_vbm(ww, TIM_EWE_ID, pawtiaw_vbm, PAWTIAW_VBM_MAX, 0);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_cmd_vbm(ww, TIM_EWE_ID, pawtiaw_vbm, 1, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_wx_config(stwuct ww1251 *ww, u32 config, u32 fiwtew)
{
	int wet;

	wet = ww1251_acx_wx_msdu_wife_time(ww, WX_MSDU_WIFETIME_DEF);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_wx_config(ww, config, fiwtew);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_phy_config(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_pd_thweshowd(ww);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_swot(ww, DEFAUWT_SWOT_TIME);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_gwoup_addwess_tbw(ww, twue, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_sewvice_pewiod_timeout(ww);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_wts_thweshowd(ww, WTS_THWESHOWD_DEF);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_beacon_fiwtew(stwuct ww1251 *ww)
{
	int wet;

	/* disabwe beacon fiwtewing at this stage */
	wet = ww1251_acx_beacon_fiwtew_opt(ww, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_beacon_fiwtew_tabwe(ww);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_pta(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_sg_enabwe(ww);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_acx_sg_cfg(ww);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_enewgy_detection(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_cca_thweshowd(ww);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_beacon_bwoadcast(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_bcn_dtim_options(ww);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_hw_init_powew_auth(stwuct ww1251 *ww)
{
	wetuwn ww1251_acx_sweep_auth(ww, WW1251_PSM_CAM);
}

int ww1251_hw_init_mem_config(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_mem_cfg(ww);
	if (wet < 0)
		wetuwn wet;

	ww->tawget_mem_map = kzawwoc(sizeof(stwuct ww1251_acx_mem_map),
					  GFP_KEWNEW);
	if (!ww->tawget_mem_map) {
		ww1251_ewwow("couwdn't awwocate tawget memowy map");
		wetuwn -ENOMEM;
	}

	/* we now ask fow the fiwmwawe buiwt memowy map */
	wet = ww1251_acx_mem_map(ww, ww->tawget_mem_map,
				 sizeof(stwuct ww1251_acx_mem_map));
	if (wet < 0) {
		ww1251_ewwow("couwdn't wetwieve fiwmwawe memowy map");
		kfwee(ww->tawget_mem_map);
		ww->tawget_mem_map = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int ww1251_hw_init_txq_fiww(u8 qid,
				   stwuct acx_tx_queue_qos_config *config,
				   u32 num_bwocks)
{
	config->qid = qid;

	switch (qid) {
	case QOS_AC_BE:
		config->high_thweshowd =
			(QOS_TX_HIGH_BE_DEF * num_bwocks) / 100;
		config->wow_thweshowd =
			(QOS_TX_WOW_BE_DEF * num_bwocks) / 100;
		bweak;
	case QOS_AC_BK:
		config->high_thweshowd =
			(QOS_TX_HIGH_BK_DEF * num_bwocks) / 100;
		config->wow_thweshowd =
			(QOS_TX_WOW_BK_DEF * num_bwocks) / 100;
		bweak;
	case QOS_AC_VI:
		config->high_thweshowd =
			(QOS_TX_HIGH_VI_DEF * num_bwocks) / 100;
		config->wow_thweshowd =
			(QOS_TX_WOW_VI_DEF * num_bwocks) / 100;
		bweak;
	case QOS_AC_VO:
		config->high_thweshowd =
			(QOS_TX_HIGH_VO_DEF * num_bwocks) / 100;
		config->wow_thweshowd =
			(QOS_TX_WOW_VO_DEF * num_bwocks) / 100;
		bweak;
	defauwt:
		ww1251_ewwow("Invawid TX queue id: %d", qid);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ww1251_hw_init_tx_queue_config(stwuct ww1251 *ww)
{
	stwuct acx_tx_queue_qos_config *config;
	stwuct ww1251_acx_mem_map *ww_mem_map = ww->tawget_mem_map;
	int wet, i;

	ww1251_debug(DEBUG_ACX, "acx tx queue config");

	config = kzawwoc(sizeof(*config), GFP_KEWNEW);
	if (!config) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < MAX_NUM_OF_AC; i++) {
		wet = ww1251_hw_init_txq_fiww(i, config,
					      ww_mem_map->num_tx_mem_bwocks);
		if (wet < 0)
			goto out;

		wet = ww1251_cmd_configuwe(ww, ACX_TX_QUEUE_CFG,
					   config, sizeof(*config));
		if (wet < 0)
			goto out;
	}

	ww1251_acx_ac_cfg(ww, AC_BE, CWMIN_BE, CWMAX_BE, AIFS_DIFS, TXOP_BE);
	ww1251_acx_ac_cfg(ww, AC_BK, CWMIN_BK, CWMAX_BK, AIFS_DIFS, TXOP_BK);
	ww1251_acx_ac_cfg(ww, AC_VI, CWMIN_VI, CWMAX_VI, AIFS_DIFS, TXOP_VI);
	ww1251_acx_ac_cfg(ww, AC_VO, CWMIN_VO, CWMAX_VO, AIFS_DIFS, TXOP_VO);

out:
	kfwee(config);
	wetuwn wet;
}

static int ww1251_hw_init_data_path_config(stwuct ww1251 *ww)
{
	int wet;

	/* asking fow the data path pawametews */
	ww->data_path = kzawwoc(sizeof(stwuct acx_data_path_pawams_wesp),
				GFP_KEWNEW);
	if (!ww->data_path)
		wetuwn -ENOMEM;

	wet = ww1251_acx_data_path_pawams(ww, ww->data_path);
	if (wet < 0) {
		kfwee(ww->data_path);
		ww->data_path = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}


int ww1251_hw_init(stwuct ww1251 *ww)
{
	stwuct ww1251_acx_mem_map *ww_mem_map;
	int wet;

	wet = ww1251_hw_init_hwenc_config(ww);
	if (wet < 0)
		wetuwn wet;

	/* Tempwate settings */
	wet = ww1251_hw_init_tempwates_config(ww);
	if (wet < 0)
		wetuwn wet;

	/* Defauwt memowy configuwation */
	wet = ww1251_hw_init_mem_config(ww);
	if (wet < 0)
		wetuwn wet;

	/* Defauwt data path configuwation  */
	wet = ww1251_hw_init_data_path_config(ww);
	if (wet < 0)
		goto out_fwee_memmap;

	/* WX config */
	wet = ww1251_hw_init_wx_config(ww,
				       WX_CFG_PWOMISCUOUS | WX_CFG_TSF,
				       WX_FIWTEW_OPTION_DEF);
	/* WX_CONFIG_OPTION_ANY_DST_ANY_BSS,
	   WX_FIWTEW_OPTION_FIWTEW_AWW); */
	if (wet < 0)
		goto out_fwee_data_path;

	/* TX queues config */
	wet = ww1251_hw_init_tx_queue_config(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* PHY wayew config */
	wet = ww1251_hw_init_phy_config(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Initiawize connection monitowing thweshowds */
	wet = ww1251_acx_conn_monit_pawams(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Beacon fiwtewing */
	wet = ww1251_hw_init_beacon_fiwtew(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Bwuetooth WWAN coexistence */
	wet = ww1251_hw_init_pta(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Enewgy detection */
	wet = ww1251_hw_init_enewgy_detection(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Beacons and bwoadcast settings */
	wet = ww1251_hw_init_beacon_bwoadcast(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Enabwe wx data path */
	wet = ww1251_cmd_data_path_wx(ww, ww->channew, 1);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Enabwe tx data path */
	wet = ww1251_cmd_data_path_tx(ww, ww->channew, 1);
	if (wet < 0)
		goto out_fwee_data_path;

	/* Defauwt powew state */
	wet = ww1251_hw_init_powew_auth(ww);
	if (wet < 0)
		goto out_fwee_data_path;

	ww_mem_map = ww->tawget_mem_map;
	ww1251_info("%d tx bwocks at 0x%x, %d wx bwocks at 0x%x",
		    ww_mem_map->num_tx_mem_bwocks,
		    ww->data_path->tx_contwow_addw,
		    ww_mem_map->num_wx_mem_bwocks,
		    ww->data_path->wx_contwow_addw);

	wetuwn 0;

 out_fwee_data_path:
	kfwee(ww->data_path);

 out_fwee_memmap:
	kfwee(ww->tawget_mem_map);

	wetuwn wet;
}
