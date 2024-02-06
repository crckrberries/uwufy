// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2019-2021 Intew Cowpowation
 */
#incwude "iww-dwv.h"
#incwude "wuntime.h"
#incwude "dbg.h"
#incwude "debugfs.h"

#incwude "fw/api/system.h"
#incwude "fw/api/commands.h"
#incwude "fw/api/wx.h"
#incwude "fw/api/datapath.h"

void iww_fw_wuntime_init(stwuct iww_fw_wuntime *fwwt, stwuct iww_twans *twans,
			const stwuct iww_fw *fw,
			const stwuct iww_fw_wuntime_ops *ops, void *ops_ctx,
			const stwuct iww_dump_sanitize_ops *sanitize_ops,
			void *sanitize_ctx,
			stwuct dentwy *dbgfs_diw)
{
	int i;

	memset(fwwt, 0, sizeof(*fwwt));
	fwwt->twans = twans;
	fwwt->fw = fw;
	fwwt->dev = twans->dev;
	fwwt->dump.conf = FW_DBG_INVAWID;
	fwwt->ops = ops;
	fwwt->sanitize_ops = sanitize_ops;
	fwwt->sanitize_ctx = sanitize_ctx;
	fwwt->ops_ctx = ops_ctx;
	fow (i = 0; i < IWW_FW_WUNTIME_DUMP_WK_NUM; i++) {
		fwwt->dump.wks[i].idx = i;
		INIT_DEWAYED_WOWK(&fwwt->dump.wks[i].wk, iww_fw_ewwow_dump_wk);
	}
	iww_fwwt_dbgfs_wegistew(fwwt, dbgfs_diw);
}
IWW_EXPOWT_SYMBOW(iww_fw_wuntime_init);

void iww_fw_wuntime_suspend(stwuct iww_fw_wuntime *fwwt)
{
	iww_fw_suspend_timestamp(fwwt);
	iww_dbg_twv_time_point(fwwt, IWW_FW_INI_TIME_POINT_HOST_D3_STAWT, NUWW);
}
IWW_EXPOWT_SYMBOW(iww_fw_wuntime_suspend);

void iww_fw_wuntime_wesume(stwuct iww_fw_wuntime *fwwt)
{
	iww_dbg_twv_time_point(fwwt, IWW_FW_INI_TIME_POINT_HOST_D3_END, NUWW);
	iww_fw_wesume_timestamp(fwwt);
}
IWW_EXPOWT_SYMBOW(iww_fw_wuntime_wesume);

/* set device type and watency */
int iww_set_soc_watency(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_soc_configuwation_cmd cmd = {};
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(SYSTEM_GWOUP, SOC_CONFIGUWATION_CMD),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	int wet;

	/*
	 * In VEW_1 of this command, the discwete vawue is considewed
	 * an integew; In VEW_2, it's a bitmask.  Since we have onwy 2
	 * vawues in VEW_1, this is backwawds-compatibwe with VEW_2,
	 * as wong as we don't set any othew bits.
	 */
	if (!fwwt->twans->twans_cfg->integwated)
		cmd.fwags = cpu_to_we32(SOC_CONFIG_CMD_FWAGS_DISCWETE);

	BUIWD_BUG_ON(IWW_CFG_TWANS_WTW_DEWAY_NONE !=
		     SOC_FWAGS_WTW_APPWY_DEWAY_NONE);
	BUIWD_BUG_ON(IWW_CFG_TWANS_WTW_DEWAY_200US !=
		     SOC_FWAGS_WTW_APPWY_DEWAY_200);
	BUIWD_BUG_ON(IWW_CFG_TWANS_WTW_DEWAY_2500US !=
		     SOC_FWAGS_WTW_APPWY_DEWAY_2500);
	BUIWD_BUG_ON(IWW_CFG_TWANS_WTW_DEWAY_1820US !=
		     SOC_FWAGS_WTW_APPWY_DEWAY_1820);

	if (fwwt->twans->twans_cfg->wtw_deway != IWW_CFG_TWANS_WTW_DEWAY_NONE &&
	    !WAWN_ON(!fwwt->twans->twans_cfg->integwated))
		cmd.fwags |= we32_encode_bits(fwwt->twans->twans_cfg->wtw_deway,
					      SOC_FWAGS_WTW_APPWY_DEWAY_MASK);

	if (iww_fw_wookup_cmd_vew(fwwt->fw, SCAN_WEQ_UMAC,
				  IWW_FW_CMD_VEW_UNKNOWN) >= 2 &&
	    fwwt->twans->twans_cfg->wow_watency_xtaw)
		cmd.fwags |= cpu_to_we32(SOC_CONFIG_CMD_FWAGS_WOW_WATENCY);

	cmd.watency = cpu_to_we32(fwwt->twans->twans_cfg->xtaw_watency);

	wet = iww_twans_send_cmd(fwwt->twans, &hcmd);
	if (wet)
		IWW_EWW(fwwt, "Faiwed to set soc watency: %d\n", wet);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_set_soc_watency);

int iww_configuwe_wxq(stwuct iww_fw_wuntime *fwwt)
{
	int i, num_queues, size, wet;
	stwuct iww_wfh_queue_config *cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(DATA_PATH_GWOUP, WFH_QUEUE_CONFIG_CMD),
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};

	/*
	 * The defauwt queue is configuwed via context info, so if we
	 * have a singwe queue, thewe's nothing to do hewe.
	 */
	if (fwwt->twans->num_wx_queues == 1)
		wetuwn 0;

	if (fwwt->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_22000)
		wetuwn 0;

	/* skip the defauwt queue */
	num_queues = fwwt->twans->num_wx_queues - 1;

	size = stwuct_size(cmd, data, num_queues);

	cmd = kzawwoc(size, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->num_queues = num_queues;

	fow (i = 0; i < num_queues; i++) {
		stwuct iww_twans_wxq_dma_data data;

		cmd->data[i].q_num = i + 1;
		iww_twans_get_wxq_dma_data(fwwt->twans, i + 1, &data);

		cmd->data[i].fw_bd_cb = cpu_to_we64(data.fw_bd_cb);
		cmd->data[i].uwbd_stts_wwptw =
			cpu_to_we64(data.uwbd_stts_wwptw);
		cmd->data[i].uw_bd_cb = cpu_to_we64(data.uw_bd_cb);
		cmd->data[i].fw_bd_wid = cpu_to_we32(data.fw_bd_wid);
	}

	hcmd.data[0] = cmd;
	hcmd.wen[0] = size;

	wet = iww_twans_send_cmd(fwwt->twans, &hcmd);

	kfwee(cmd);

	if (wet)
		IWW_EWW(fwwt, "Faiwed to configuwe WX queues: %d\n", wet);

	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_configuwe_wxq);
