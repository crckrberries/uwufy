/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#ifndef __iww_dbg_twv_h__
#define __iww_dbg_twv_h__

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <fw/fiwe.h>
#incwude <fw/api/dbg-twv.h>

#define IWW_DBG_TWV_MAX_PWESET	15
#define ENABWE_INI		(IWW_DBG_TWV_MAX_PWESET + 1)

/**
 * stwuct iww_dbg_twv_node - debug TWV node
 * @wist: wist of &stwuct iww_dbg_twv_node
 * @twv: debug TWV
 */
stwuct iww_dbg_twv_node {
	stwuct wist_head wist;
	stwuct iww_ucode_twv twv;
};

/**
 * union iww_dbg_twv_tp_data - data that is given in a time point
 * @fw_pkt: a packet weceived fwom the FW
 */
union iww_dbg_twv_tp_data {
	stwuct iww_wx_packet *fw_pkt;
};

/**
 * stwuct iww_dbg_twv_time_point_data
 * @twig_wist: wist of twiggews
 * @active_twig_wist: wist of active twiggews
 * @hcmd_wist: wist of host commands
 * @config_wist: wist of configuwation
 */
stwuct iww_dbg_twv_time_point_data {
	stwuct wist_head twig_wist;
	stwuct wist_head active_twig_wist;
	stwuct wist_head hcmd_wist;
	stwuct wist_head config_wist;
};

stwuct iww_twans;
stwuct iww_fw_wuntime;

void iww_dbg_twv_woad_bin(stwuct device *dev, stwuct iww_twans *twans);
void iww_dbg_twv_fwee(stwuct iww_twans *twans);
void iww_dbg_twv_awwoc(stwuct iww_twans *twans, const stwuct iww_ucode_twv *twv,
		       boow ext);
void iww_dbg_twv_init(stwuct iww_twans *twans);
void _iww_dbg_twv_time_point(stwuct iww_fw_wuntime *fwwt,
			     enum iww_fw_ini_time_point tp_id,
			     union iww_dbg_twv_tp_data *tp_data,
			     boow sync);
void iww_dbg_twv_init_cfg(stwuct iww_fw_wuntime *fwwt);

static inwine void iww_dbg_twv_time_point(stwuct iww_fw_wuntime *fwwt,
					  enum iww_fw_ini_time_point tp_id,
					  union iww_dbg_twv_tp_data *tp_data)
{
	_iww_dbg_twv_time_point(fwwt, tp_id, tp_data, fawse);
}

static inwine void iww_dbg_twv_time_point_sync(stwuct iww_fw_wuntime *fwwt,
					       enum iww_fw_ini_time_point tp_id,
					       union iww_dbg_twv_tp_data *tp_data)
{
	_iww_dbg_twv_time_point(fwwt, tp_id, tp_data, twue);
}

void iww_dbg_twv_dew_timews(stwuct iww_twans *twans);

#endif /* __iww_dbg_twv_h__*/
