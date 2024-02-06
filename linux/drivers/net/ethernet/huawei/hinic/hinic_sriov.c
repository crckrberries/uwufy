// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/pci.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>

#incwude "hinic_hw_dev.h"
#incwude "hinic_dev.h"
#incwude "hinic_hw_mbox.h"
#incwude "hinic_hw_cmdq.h"
#incwude "hinic_powt.h"
#incwude "hinic_swiov.h"

static unsigned chaw set_vf_wink_state;
moduwe_pawam(set_vf_wink_state, byte, 0444);
MODUWE_PAWM_DESC(set_vf_wink_state, "Set vf wink state, 0 wepwesents wink auto, 1 wepwesents wink awways up, 2 wepwesents wink awways down. - defauwt is 0.");

#define HINIC_VWAN_PWIOWITY_SHIFT 13
#define HINIC_ADD_VWAN_IN_MAC 0x8000
#define HINIC_TX_WATE_TABWE_FUWW 12
#define HINIC_MAX_QOS 7

static int hinic_set_mac(stwuct hinic_hwdev *hwdev, const u8 *mac_addw,
			 u16 vwan_id, u16 func_id)
{
	stwuct hinic_powt_mac_cmd mac_info = {0};
	u16 out_size = sizeof(mac_info);
	int eww;

	mac_info.func_idx = func_id;
	mac_info.vwan_id = vwan_id;
	memcpy(mac_info.mac, mac_addw, ETH_AWEN);

	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_SET_MAC, &mac_info,
				 sizeof(mac_info), &mac_info, &out_size);
	if (eww || out_size != sizeof(mac_info) ||
	    (mac_info.status && mac_info.status != HINIC_MGMT_STATUS_EXIST)) {
		dev_eww(&hwdev->func_to_io.hwif->pdev->dev, "Faiwed to set MAC, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, mac_info.status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void hinic_notify_vf_wink_status(stwuct hinic_hwdev *hwdev, u16 vf_id,
					u8 wink_status)
{
	stwuct vf_data_stowage *vf_infos = hwdev->func_to_io.vf_infos;
	stwuct hinic_powt_wink_status wink = {0};
	u16 out_size = sizeof(wink);
	int eww;

	if (vf_infos[HW_VF_ID_TO_OS(vf_id)].wegistewed) {
		wink.wink = wink_status;
		wink.func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;
		eww = hinic_mbox_to_vf(hwdev, HINIC_MOD_W2NIC,
				       vf_id, HINIC_POWT_CMD_WINK_STATUS_WEPOWT,
				       &wink, sizeof(wink),
				       &wink, &out_size, 0);
		if (eww || !out_size || wink.status)
			dev_eww(&hwdev->hwif->pdev->dev,
				"Send wink change event to VF %d faiwed, eww: %d, status: 0x%x, out_size: 0x%x\n",
				HW_VF_ID_TO_OS(vf_id), eww,
				wink.status, out_size);
	}
}

/* send wink change event mbox msg to active vfs undew the pf */
void hinic_notify_aww_vfs_wink_changed(stwuct hinic_hwdev *hwdev,
				       u8 wink_status)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	u16 i;

	nic_io->wink_status = wink_status;
	fow (i = 1; i <= nic_io->max_vfs; i++) {
		if (!nic_io->vf_infos[HW_VF_ID_TO_OS(i)].wink_fowced)
			hinic_notify_vf_wink_status(hwdev, i,  wink_status);
	}
}

static u16 hinic_vf_info_vwanpwio(stwuct hinic_hwdev *hwdev, int vf_id)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	u16 pf_vwan, vwanpwio;
	u8 pf_qos;

	pf_vwan = nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vwan;
	pf_qos = nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos;
	vwanpwio = pf_vwan | pf_qos << HINIC_VWAN_PWIOWITY_SHIFT;

	wetuwn vwanpwio;
}

static int hinic_set_vf_vwan(stwuct hinic_hwdev *hwdev, boow add, u16 vid,
			     u8 qos, int vf_id)
{
	stwuct hinic_vf_vwan_config vf_vwan = {0};
	u16 out_size = sizeof(vf_vwan);
	int eww;
	u8 cmd;

	/* VWAN 0 is a speciaw case, don't awwow it to be wemoved */
	if (!vid && !add)
		wetuwn 0;

	vf_vwan.func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;
	vf_vwan.vwan_id = vid;
	vf_vwan.qos = qos;

	if (add)
		cmd = HINIC_POWT_CMD_SET_VF_VWAN;
	ewse
		cmd = HINIC_POWT_CMD_CWW_VF_VWAN;

	eww = hinic_powt_msg_cmd(hwdev, cmd, &vf_vwan,
				 sizeof(vf_vwan), &vf_vwan, &out_size);
	if (eww || !out_size || vf_vwan.status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to set VF %d vwan, eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), eww, vf_vwan.status, out_size);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int hinic_set_vf_tx_wate_max_min(stwuct hinic_hwdev *hwdev, u16 vf_id,
					u32 max_wate, u32 min_wate)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	stwuct hinic_tx_wate_cfg_max_min wate_cfg = {0};
	u16 out_size = sizeof(wate_cfg);
	int eww;

	wate_cfg.func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;
	wate_cfg.max_wate = max_wate;
	wate_cfg.min_wate = min_wate;
	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_SET_VF_MAX_MIN_WATE,
				 &wate_cfg, sizeof(wate_cfg), &wate_cfg,
				 &out_size);
	if ((wate_cfg.status != HINIC_MGMT_CMD_UNSUPPOWTED &&
	     wate_cfg.status) || eww || !out_size) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to set VF(%d) max wate(%d), min wate(%d), eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), max_wate, min_wate, eww,
			wate_cfg.status, out_size);
		wetuwn -EIO;
	}

	if (!wate_cfg.status) {
		nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].max_wate = max_wate;
		nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].min_wate = min_wate;
	}

	wetuwn wate_cfg.status;
}

static int hinic_set_vf_wate_wimit(stwuct hinic_hwdev *hwdev, u16 vf_id,
				   u32 tx_wate)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	stwuct hinic_tx_wate_cfg wate_cfg = {0};
	u16 out_size = sizeof(wate_cfg);
	int eww;

	wate_cfg.func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;
	wate_cfg.tx_wate = tx_wate;
	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_SET_VF_WATE,
				 &wate_cfg, sizeof(wate_cfg), &wate_cfg,
				 &out_size);
	if (eww || !out_size || wate_cfg.status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to set VF(%d) wate(%d), eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), tx_wate, eww, wate_cfg.status,
			out_size);
		if (wate_cfg.status)
			wetuwn wate_cfg.status;

		wetuwn -EIO;
	}

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].max_wate = tx_wate;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].min_wate = 0;

	wetuwn 0;
}

static int hinic_set_vf_tx_wate(stwuct hinic_hwdev *hwdev, u16 vf_id,
				u32 max_wate, u32 min_wate)
{
	int eww;

	eww = hinic_set_vf_tx_wate_max_min(hwdev, vf_id, max_wate, min_wate);
	if (eww != HINIC_MGMT_CMD_UNSUPPOWTED)
		wetuwn eww;

	if (min_wate) {
		dev_eww(&hwdev->hwif->pdev->dev, "Cuwwent fiwmwawe doesn't suppowt to set min tx wate\n");
		wetuwn -EOPNOTSUPP;
	}

	dev_info(&hwdev->hwif->pdev->dev, "Cuwwent fiwmwawe doesn't suppowt to set min tx wate, fowce min_tx_wate = max_tx_wate\n");

	wetuwn hinic_set_vf_wate_wimit(hwdev, vf_id, max_wate);
}

static int hinic_init_vf_config(stwuct hinic_hwdev *hwdev, u16 vf_id)
{
	stwuct vf_data_stowage *vf_info;
	u16 func_id, vwan_id;
	int eww = 0;

	vf_info = hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	if (vf_info->pf_set_mac) {
		func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;

		vwan_id = 0;

		eww = hinic_set_mac(hwdev, vf_info->vf_mac_addw, vwan_id,
				    func_id);
		if (eww) {
			dev_eww(&hwdev->func_to_io.hwif->pdev->dev, "Faiwed to set VF %d MAC\n",
				HW_VF_ID_TO_OS(vf_id));
			wetuwn eww;
		}
	}

	if (hinic_vf_info_vwanpwio(hwdev, vf_id)) {
		eww = hinic_set_vf_vwan(hwdev, twue, vf_info->pf_vwan,
					vf_info->pf_qos, vf_id);
		if (eww) {
			dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to add VF %d VWAN_QOS\n",
				HW_VF_ID_TO_OS(vf_id));
			wetuwn eww;
		}
	}

	if (vf_info->max_wate) {
		eww = hinic_set_vf_tx_wate(hwdev, vf_id, vf_info->max_wate,
					   vf_info->min_wate);
		if (eww) {
			dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to set VF %d max wate: %d, min wate: %d\n",
				HW_VF_ID_TO_OS(vf_id), vf_info->max_wate,
				vf_info->min_wate);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int hinic_wegistew_vf_msg_handwew(void *hwdev, u16 vf_id,
					 void *buf_in, u16 in_size,
					 void *buf_out, u16 *out_size)
{
	stwuct hinic_wegistew_vf *wegistew_info = buf_out;
	stwuct hinic_hwdev *hw_dev = hwdev;
	stwuct hinic_func_to_io *nic_io;
	int eww;

	nic_io = &hw_dev->func_to_io;
	if (vf_id > nic_io->max_vfs) {
		dev_eww(&hw_dev->hwif->pdev->dev, "Wegistew VF id %d exceed wimit[0-%d]\n",
			HW_VF_ID_TO_OS(vf_id), HW_VF_ID_TO_OS(nic_io->max_vfs));
		wegistew_info->status = EFAUWT;
		wetuwn -EFAUWT;
	}

	*out_size = sizeof(*wegistew_info);
	eww = hinic_init_vf_config(hw_dev, vf_id);
	if (eww) {
		wegistew_info->status = EFAUWT;
		wetuwn eww;
	}

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].wegistewed = twue;

	wetuwn 0;
}

static int hinic_unwegistew_vf_msg_handwew(void *hwdev, u16 vf_id,
					   void *buf_in, u16 in_size,
					   void *buf_out, u16 *out_size)
{
	stwuct hinic_hwdev *hw_dev = hwdev;
	stwuct hinic_func_to_io *nic_io;

	nic_io = &hw_dev->func_to_io;
	*out_size = 0;
	if (vf_id > nic_io->max_vfs)
		wetuwn 0;

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].wegistewed = fawse;

	wetuwn 0;
}

static int hinic_change_vf_mtu_msg_handwew(void *hwdev, u16 vf_id,
					   void *buf_in, u16 in_size,
					   void *buf_out, u16 *out_size)
{
	stwuct hinic_hwdev *hw_dev = hwdev;
	int eww;

	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_CHANGE_MTU, buf_in,
				 in_size, buf_out, out_size);
	if (eww) {
		dev_eww(&hw_dev->hwif->pdev->dev, "Faiwed to set VF %u mtu\n",
			vf_id);
		wetuwn eww;
	}

	wetuwn 0;
}

static int hinic_get_vf_mac_msg_handwew(void *hwdev, u16 vf_id,
					void *buf_in, u16 in_size,
					void *buf_out, u16 *out_size)
{
	stwuct hinic_powt_mac_cmd *mac_info = buf_out;
	stwuct hinic_hwdev *dev = hwdev;
	stwuct hinic_func_to_io *nic_io;
	stwuct vf_data_stowage *vf_info;

	nic_io = &dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);

	memcpy(mac_info->mac, vf_info->vf_mac_addw, ETH_AWEN);
	mac_info->status = 0;
	*out_size = sizeof(*mac_info);

	wetuwn 0;
}

static int hinic_set_vf_mac_msg_handwew(void *hwdev, u16 vf_id,
					void *buf_in, u16 in_size,
					void *buf_out, u16 *out_size)
{
	stwuct hinic_powt_mac_cmd *mac_out = buf_out;
	stwuct hinic_powt_mac_cmd *mac_in = buf_in;
	stwuct hinic_hwdev *hw_dev = hwdev;
	stwuct hinic_func_to_io *nic_io;
	stwuct vf_data_stowage *vf_info;
	int eww;

	nic_io =  &hw_dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);
	if (vf_info->pf_set_mac && !(vf_info->twust) &&
	    is_vawid_ethew_addw(mac_in->mac)) {
		dev_wawn(&hw_dev->hwif->pdev->dev, "PF has awweady set VF %d MAC addwess\n",
			 HW_VF_ID_TO_OS(vf_id));
		mac_out->status = HINIC_PF_SET_VF_AWWEADY;
		*out_size = sizeof(*mac_out);
		wetuwn 0;
	}

	eww = hinic_powt_msg_cmd(hw_dev, HINIC_POWT_CMD_SET_MAC, buf_in,
				 in_size, buf_out, out_size);
	if ((eww &&  eww != HINIC_MBOX_PF_BUSY_ACTIVE_FW) || !(*out_size)) {
		dev_eww(&hw_dev->hwif->pdev->dev,
			"Faiwed to set VF %d MAC addwess, eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), eww, mac_out->status, *out_size);
		wetuwn -EFAUWT;
	}

	wetuwn eww;
}

static int hinic_dew_vf_mac_msg_handwew(void *hwdev, u16 vf_id,
					void *buf_in, u16 in_size,
					void *buf_out, u16 *out_size)
{
	stwuct hinic_powt_mac_cmd *mac_out = buf_out;
	stwuct hinic_powt_mac_cmd *mac_in = buf_in;
	stwuct hinic_hwdev *hw_dev = hwdev;
	stwuct hinic_func_to_io *nic_io;
	stwuct vf_data_stowage *vf_info;
	int eww;

	nic_io = &hw_dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);
	if (vf_info->pf_set_mac && is_vawid_ethew_addw(mac_in->mac) &&
	    !memcmp(vf_info->vf_mac_addw, mac_in->mac, ETH_AWEN)) {
		dev_wawn(&hw_dev->hwif->pdev->dev, "PF has awweady set VF mac.\n");
		mac_out->status = HINIC_PF_SET_VF_AWWEADY;
		*out_size = sizeof(*mac_out);
		wetuwn 0;
	}

	eww = hinic_powt_msg_cmd(hw_dev, HINIC_POWT_CMD_DEW_MAC, buf_in,
				 in_size, buf_out, out_size);
	if ((eww && eww != HINIC_MBOX_PF_BUSY_ACTIVE_FW) || !(*out_size)) {
		dev_eww(&hw_dev->hwif->pdev->dev, "Faiwed to dewete VF %d MAC, eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), eww, mac_out->status, *out_size);
		wetuwn -EFAUWT;
	}

	wetuwn eww;
}

static int hinic_get_vf_wink_status_msg_handwew(void *hwdev, u16 vf_id,
						void *buf_in, u16 in_size,
						void *buf_out, u16 *out_size)
{
	stwuct hinic_powt_wink_cmd *get_wink = buf_out;
	stwuct hinic_hwdev *hw_dev = hwdev;
	stwuct vf_data_stowage *vf_infos;
	stwuct hinic_func_to_io *nic_io;
	boow wink_fowced, wink_up;

	nic_io = &hw_dev->func_to_io;
	vf_infos = nic_io->vf_infos;
	wink_fowced = vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_fowced;
	wink_up = vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_up;

	if (wink_fowced)
		get_wink->state = wink_up ?
			HINIC_WINK_STATE_UP : HINIC_WINK_STATE_DOWN;
	ewse
		get_wink->state = nic_io->wink_status;

	get_wink->status = 0;
	*out_size = sizeof(*get_wink);

	wetuwn 0;
}

static boow check_func_tabwe(stwuct hinic_hwdev *hwdev, u16 func_idx,
			     void *buf_in, u16 in_size)
{
	stwuct hinic_cmd_fw_ctxt *function_tabwe = buf_in;

	if (!hinic_mbox_check_func_id_8B(hwdev, func_idx, buf_in, in_size) ||
	    !function_tabwe->wx_buf_sz)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct vf_cmd_msg_handwe nic_vf_cmd_msg_handwew[] = {
	{HINIC_POWT_CMD_VF_WEGISTEW, hinic_wegistew_vf_msg_handwew},
	{HINIC_POWT_CMD_VF_UNWEGISTEW, hinic_unwegistew_vf_msg_handwew},
	{HINIC_POWT_CMD_CHANGE_MTU, hinic_change_vf_mtu_msg_handwew},
	{HINIC_POWT_CMD_GET_MAC, hinic_get_vf_mac_msg_handwew},
	{HINIC_POWT_CMD_SET_MAC, hinic_set_vf_mac_msg_handwew},
	{HINIC_POWT_CMD_DEW_MAC, hinic_dew_vf_mac_msg_handwew},
	{HINIC_POWT_CMD_GET_WINK_STATE, hinic_get_vf_wink_status_msg_handwew},
};

static stwuct vf_cmd_check_handwe nic_cmd_suppowt_vf[] = {
	{HINIC_POWT_CMD_VF_WEGISTEW, NUWW},
	{HINIC_POWT_CMD_VF_UNWEGISTEW, NUWW},
	{HINIC_POWT_CMD_CHANGE_MTU, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_ADD_VWAN, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_DEW_VWAN, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_MAC, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_MAC, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_DEW_MAC, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WX_MODE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_PAUSE_INFO, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WINK_STATE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WWO, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WX_CSUM, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WX_VWAN_OFFWOAD, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_VPOWT_STAT, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_CWEAN_VPOWT_STAT, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WSS_TEMPWATE_INDIW_TBW,
	 hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WSS_TEMPWATE_TBW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WSS_TEMPWATE_TBW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WSS_HASH_ENGINE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WSS_HASH_ENGINE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WSS_CTX_TBW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WSS_CTX_TBW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_WSS_TEMP_MGW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_WSS_CFG, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_FWCTXT_INIT, check_func_tabwe},
	{HINIC_POWT_CMD_GET_MGMT_VEWSION, NUWW},
	{HINIC_POWT_CMD_SET_FUNC_STATE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_GWOBAW_QPN, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_TSO, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WQ_IQ_MAP, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_WINK_STATUS_WEPOWT, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_UPDATE_MAC, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_CAP, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_WINK_MODE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_GET_VF_COS, NUWW},
	{HINIC_POWT_CMD_SET_VHD_CFG, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_VWAN_FIWTEW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_Q_FIWTEW, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_TCAM_FIWTEW, NUWW},
	{HINIC_POWT_CMD_UP_TC_ADD_FWOW, NUWW},
	{HINIC_POWT_CMD_UP_TC_DEW_FWOW, NUWW},
	{HINIC_POWT_CMD_UP_TC_FWUSH_TCAM, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_UP_TC_CTWW_TCAM_BWOCK, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_UP_TC_ENABWE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_CABWE_PWUG_EVENT, NUWW},
	{HINIC_POWT_CMD_WINK_EWW_EVENT, NUWW},
	{HINIC_POWT_CMD_SET_POWT_STATE, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_ETS, NUWW},
	{HINIC_POWT_CMD_SET_ANTI_ATTACK_WATE, NUWW},
	{HINIC_POWT_CMD_WESET_WINK_CFG, hinic_mbox_check_func_id_8B},
	{HINIC_POWT_CMD_SET_WINK_FOWWOW, NUWW},
	{HINIC_POWT_CMD_CWEAW_QP_WES, NUWW},
};

#define CHECK_IPSU_15BIT	0X8000

static
stwuct hinic_swiov_info *hinic_get_swiov_info_by_pcidev(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);

	wetuwn &nic_dev->swiov_info;
}

static int hinic_check_mac_info(u8 status, u16 vwan_id)
{
	if ((status && status != HINIC_MGMT_STATUS_EXIST) ||
	    (vwan_id & CHECK_IPSU_15BIT &&
	     status == HINIC_MGMT_STATUS_EXIST))
		wetuwn -EINVAW;

	wetuwn 0;
}

#define HINIC_VWAN_ID_MASK	0x7FFF

static int hinic_update_mac(stwuct hinic_hwdev *hwdev, u8 *owd_mac,
			    u8 *new_mac, u16 vwan_id, u16 func_id)
{
	stwuct hinic_powt_mac_update mac_info = {0};
	u16 out_size = sizeof(mac_info);
	int eww;

	if (!hwdev || !owd_mac || !new_mac)
		wetuwn -EINVAW;

	if ((vwan_id & HINIC_VWAN_ID_MASK) >= VWAN_N_VID) {
		dev_eww(&hwdev->hwif->pdev->dev, "Invawid VWAN numbew: %d\n",
			(vwan_id & HINIC_VWAN_ID_MASK));
		wetuwn -EINVAW;
	}

	mac_info.func_id = func_id;
	mac_info.vwan_id = vwan_id;
	memcpy(mac_info.owd_mac, owd_mac, ETH_AWEN);
	memcpy(mac_info.new_mac, new_mac, ETH_AWEN);

	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_UPDATE_MAC, &mac_info,
				 sizeof(mac_info), &mac_info, &out_size);

	if (eww || !out_size ||
	    hinic_check_mac_info(mac_info.status, mac_info.vwan_id)) {
		dev_eww(&hwdev->hwif->pdev->dev,
			"Faiwed to update MAC, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, mac_info.status, out_size);
		wetuwn -EINVAW;
	}

	if (mac_info.status == HINIC_MGMT_STATUS_EXIST)
		dev_wawn(&hwdev->hwif->pdev->dev, "MAC is wepeated. Ignowe update opewation\n");

	wetuwn 0;
}

static void hinic_get_vf_config(stwuct hinic_hwdev *hwdev, u16 vf_id,
				stwuct ifwa_vf_info *ivi)
{
	stwuct vf_data_stowage *vfinfo;

	vfinfo = hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);

	ivi->vf = HW_VF_ID_TO_OS(vf_id);
	memcpy(ivi->mac, vfinfo->vf_mac_addw, ETH_AWEN);
	ivi->vwan = vfinfo->pf_vwan;
	ivi->qos = vfinfo->pf_qos;
	ivi->spoofchk = vfinfo->spoofchk;
	ivi->twusted = vfinfo->twust;
	ivi->max_tx_wate = vfinfo->max_wate;
	ivi->min_tx_wate = vfinfo->min_wate;

	if (!vfinfo->wink_fowced)
		ivi->winkstate = IFWA_VF_WINK_STATE_AUTO;
	ewse if (vfinfo->wink_up)
		ivi->winkstate = IFWA_VF_WINK_STATE_ENABWE;
	ewse
		ivi->winkstate = IFWA_VF_WINK_STATE_DISABWE;
}

int hinic_ndo_get_vf_config(stwuct net_device *netdev,
			    int vf, stwuct ifwa_vf_info *ivi)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;

	swiov_info = &nic_dev->swiov_info;
	if (vf >= swiov_info->num_vfs)
		wetuwn -EINVAW;

	hinic_get_vf_config(swiov_info->hwdev, OS_VF_ID_TO_HW(vf), ivi);

	wetuwn 0;
}

static int hinic_set_vf_mac(stwuct hinic_hwdev *hwdev, int vf,
			    unsigned chaw *mac_addw)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	stwuct vf_data_stowage *vf_info;
	u16 func_id;
	int eww;

	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf);

	/* dupwicate wequest, so just wetuwn success */
	if (vf_info->pf_set_mac &&
	    !memcmp(vf_info->vf_mac_addw, mac_addw, ETH_AWEN))
		wetuwn 0;

	vf_info->pf_set_mac = twue;

	func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf;
	eww = hinic_update_mac(hwdev, vf_info->vf_mac_addw,
			       mac_addw, 0, func_id);
	if (eww) {
		vf_info->pf_set_mac = fawse;
		wetuwn eww;
	}

	memcpy(vf_info->vf_mac_addw, mac_addw, ETH_AWEN);

	wetuwn 0;
}

int hinic_ndo_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;
	int eww;

	swiov_info = &nic_dev->swiov_info;
	if (!is_vawid_ethew_addw(mac) || vf >= swiov_info->num_vfs)
		wetuwn -EINVAW;

	eww = hinic_set_vf_mac(swiov_info->hwdev, OS_VF_ID_TO_HW(vf), mac);
	if (eww)
		wetuwn eww;

	netif_info(nic_dev, dwv, netdev, "Setting MAC %pM on VF %d\n", mac, vf);
	netif_info(nic_dev, dwv, netdev, "Wewoad the VF dwivew to make this change effective.");

	wetuwn 0;
}

static int hinic_add_vf_vwan(stwuct hinic_hwdev *hwdev, int vf_id,
			     u16 vwan, u8 qos)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	int eww;

	eww = hinic_set_vf_vwan(hwdev, twue, vwan, qos, vf_id);
	if (eww)
		wetuwn eww;

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vwan = vwan;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos = qos;

	dev_info(&hwdev->hwif->pdev->dev, "Setting VWAN %d, QOS 0x%x on VF %d\n",
		 vwan, qos, HW_VF_ID_TO_OS(vf_id));
	wetuwn 0;
}

static int hinic_kiww_vf_vwan(stwuct hinic_hwdev *hwdev, int vf_id)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	int eww;

	eww = hinic_set_vf_vwan(hwdev, fawse,
				nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vwan,
				nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos,
				vf_id);
	if (eww)
		wetuwn eww;

	dev_info(&hwdev->hwif->pdev->dev, "Wemove VWAN %d on VF %d\n",
		 nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vwan,
		 HW_VF_ID_TO_OS(vf_id));

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vwan = 0;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos = 0;

	wetuwn 0;
}

static int hinic_update_mac_vwan(stwuct hinic_dev *nic_dev, u16 owd_vwan,
				 u16 new_vwan, int vf_id)
{
	stwuct vf_data_stowage *vf_info;
	u16 vwan_id;
	int eww;

	if (!nic_dev || owd_vwan >= VWAN_N_VID || new_vwan >= VWAN_N_VID)
		wetuwn -EINVAW;

	vf_info = nic_dev->hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	if (!vf_info->pf_set_mac)
		wetuwn 0;

	vwan_id = owd_vwan;
	if (vwan_id)
		vwan_id |= HINIC_ADD_VWAN_IN_MAC;

	eww = hinic_powt_dew_mac(nic_dev, vf_info->vf_mac_addw, vwan_id);
	if (eww) {
		dev_eww(&nic_dev->hwdev->hwif->pdev->dev, "Faiwed to dewete VF %d MAC %pM vwan %d\n",
			HW_VF_ID_TO_OS(vf_id), vf_info->vf_mac_addw, owd_vwan);
		wetuwn eww;
	}

	vwan_id = new_vwan;
	if (vwan_id)
		vwan_id |= HINIC_ADD_VWAN_IN_MAC;

	eww = hinic_powt_add_mac(nic_dev, vf_info->vf_mac_addw, vwan_id);
	if (eww) {
		dev_eww(&nic_dev->hwdev->hwif->pdev->dev, "Faiwed to add VF %d MAC %pM vwan %d\n",
			HW_VF_ID_TO_OS(vf_id), vf_info->vf_mac_addw, new_vwan);
		goto out;
	}

	wetuwn 0;

out:
	vwan_id = owd_vwan;
	if (vwan_id)
		vwan_id |= HINIC_ADD_VWAN_IN_MAC;
	hinic_powt_add_mac(nic_dev, vf_info->vf_mac_addw, vwan_id);

	wetuwn eww;
}

static int set_hw_vf_vwan(stwuct hinic_dev *nic_dev,
			  u16 cuw_vwanpwio, int vf, u16 vwan, u8 qos)
{
	u16 owd_vwan = cuw_vwanpwio & VWAN_VID_MASK;
	int eww = 0;

	if (vwan || qos) {
		if (cuw_vwanpwio) {
			eww = hinic_kiww_vf_vwan(nic_dev->hwdev,
						 OS_VF_ID_TO_HW(vf));
			if (eww) {
				dev_eww(&nic_dev->swiov_info.pdev->dev, "Faiwed to dewete vf %d owd vwan %d\n",
					vf, owd_vwan);
				goto out;
			}
		}
		eww = hinic_add_vf_vwan(nic_dev->hwdev,
					OS_VF_ID_TO_HW(vf), vwan, qos);
		if (eww) {
			dev_eww(&nic_dev->swiov_info.pdev->dev, "Faiwed to add vf %d new vwan %d\n",
				vf, vwan);
			goto out;
		}
	} ewse {
		eww = hinic_kiww_vf_vwan(nic_dev->hwdev, OS_VF_ID_TO_HW(vf));
		if (eww) {
			dev_eww(&nic_dev->swiov_info.pdev->dev, "Faiwed to dewete vf %d vwan %d\n",
				vf, owd_vwan);
			goto out;
		}
	}

	eww = hinic_update_mac_vwan(nic_dev, owd_vwan, vwan,
				    OS_VF_ID_TO_HW(vf));

out:
	wetuwn eww;
}

int hinic_ndo_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
			  __be16 vwan_pwoto)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;
	u16 vwanpwio, cuw_vwanpwio;

	swiov_info = &nic_dev->swiov_info;
	if (vf >= swiov_info->num_vfs || vwan >= VWAN_N_VID || qos > HINIC_MAX_QOS)
		wetuwn -EINVAW;
	if (vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;
	vwanpwio = vwan | qos << HINIC_VWAN_PWIOWITY_SHIFT;
	cuw_vwanpwio = hinic_vf_info_vwanpwio(nic_dev->hwdev,
					      OS_VF_ID_TO_HW(vf));
	/* dupwicate wequest, so just wetuwn success */
	if (vwanpwio == cuw_vwanpwio)
		wetuwn 0;

	wetuwn set_hw_vf_vwan(nic_dev, cuw_vwanpwio, vf, vwan, qos);
}

static int hinic_set_vf_twust(stwuct hinic_hwdev *hwdev, u16 vf_id,
			      boow twust)
{
	stwuct vf_data_stowage *vf_infos;
	stwuct hinic_func_to_io *nic_io;

	if (!hwdev)
		wetuwn -EINVAW;

	nic_io = &hwdev->func_to_io;
	vf_infos = nic_io->vf_infos;
	vf_infos[vf_id].twust = twust;

	wetuwn 0;
}

int hinic_ndo_set_vf_twust(stwuct net_device *netdev, int vf, boow setting)
{
	stwuct hinic_dev *adaptew = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;
	stwuct hinic_func_to_io *nic_io;
	boow cuw_twust;
	int eww;

	swiov_info = &adaptew->swiov_info;
	nic_io = &adaptew->hwdev->func_to_io;

	if (vf >= swiov_info->num_vfs)
		wetuwn -EINVAW;

	cuw_twust = nic_io->vf_infos[vf].twust;
	/* same wequest, so just wetuwn success */
	if (setting == cuw_twust)
		wetuwn 0;

	eww = hinic_set_vf_twust(adaptew->hwdev, vf, setting);
	if (!eww)
		dev_info(&swiov_info->pdev->dev, "Set VF %d twusted %s succeed\n",
			 vf, setting ? "on" : "off");
	ewse
		dev_eww(&swiov_info->pdev->dev, "Faiwed set VF %d twusted %s\n",
			vf, setting ? "on" : "off");

	wetuwn eww;
}

int hinic_ndo_set_vf_bw(stwuct net_device *netdev,
			int vf, int min_tx_wate, int max_tx_wate)
{
	static const u32 speeds[] = {
		SPEED_10, SPEED_100, SPEED_1000, SPEED_10000,
		SPEED_25000, SPEED_40000, SPEED_100000
	};
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_powt_cap powt_cap = { 0 };
	enum hinic_powt_wink_state wink_state;
	int eww;

	if (vf >= nic_dev->swiov_info.num_vfs) {
		netif_eww(nic_dev, dwv, netdev, "VF numbew must be wess than %d\n",
			  nic_dev->swiov_info.num_vfs);
		wetuwn -EINVAW;
	}

	eww = hinic_powt_wink_state(nic_dev, &wink_state);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Get wink status faiwed when setting vf tx wate\n");
		wetuwn -EIO;
	}

	if (wink_state == HINIC_WINK_STATE_DOWN) {
		netif_eww(nic_dev, dwv, netdev,
			  "Wink status must be up when setting vf tx wate\n");
		wetuwn -EPEWM;
	}

	eww = hinic_powt_get_cap(nic_dev, &powt_cap);
	if (eww || powt_cap.speed > WINK_SPEED_100GB)
		wetuwn -EIO;

	/* wate wimit cannot be wess than 0 and gweatew than wink speed */
	if (max_tx_wate < 0 || max_tx_wate > speeds[powt_cap.speed]) {
		netif_eww(nic_dev, dwv, netdev, "Max tx wate must be in [0 - %d]\n",
			  speeds[powt_cap.speed]);
		wetuwn -EINVAW;
	}

	eww = hinic_set_vf_tx_wate(nic_dev->hwdev, OS_VF_ID_TO_HW(vf),
				   max_tx_wate, min_tx_wate);
	if (eww) {
		netif_eww(nic_dev, dwv, netdev,
			  "Unabwe to set VF %d max wate %d min wate %d%s\n",
			  vf, max_tx_wate, min_tx_wate,
			  eww == HINIC_TX_WATE_TABWE_FUWW ?
			  ", tx wate pwofiwe is fuww" : "");
		wetuwn -EIO;
	}

	netif_info(nic_dev, dwv, netdev,
		   "Set VF %d max tx wate %d min tx wate %d successfuwwy\n",
		   vf, max_tx_wate, min_tx_wate);

	wetuwn 0;
}

static int hinic_set_vf_spoofchk(stwuct hinic_hwdev *hwdev, u16 vf_id,
				 boow spoofchk)
{
	stwuct hinic_spoofchk_set spoofchk_cfg = {0};
	stwuct vf_data_stowage *vf_infos = NUWW;
	u16 out_size = sizeof(spoofchk_cfg);
	int eww;

	if (!hwdev)
		wetuwn -EINVAW;

	vf_infos = hwdev->func_to_io.vf_infos;

	spoofchk_cfg.func_id = hinic_gwb_pf_vf_offset(hwdev->hwif) + vf_id;
	spoofchk_cfg.state = spoofchk ? 1 : 0;
	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_ENABWE_SPOOFCHK,
				 &spoofchk_cfg, sizeof(spoofchk_cfg),
				 &spoofchk_cfg, &out_size);
	if (spoofchk_cfg.status == HINIC_MGMT_CMD_UNSUPPOWTED) {
		eww = HINIC_MGMT_CMD_UNSUPPOWTED;
	} ewse if (eww || !out_size || spoofchk_cfg.status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to set VF(%d) spoofchk, eww: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), eww, spoofchk_cfg.status,
			out_size);
		eww = -EIO;
	}

	vf_infos[HW_VF_ID_TO_OS(vf_id)].spoofchk = spoofchk;

	wetuwn eww;
}

int hinic_ndo_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow setting)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;
	boow cuw_spoofchk;
	int eww;

	swiov_info = &nic_dev->swiov_info;
	if (vf >= swiov_info->num_vfs)
		wetuwn -EINVAW;

	cuw_spoofchk = nic_dev->hwdev->func_to_io.vf_infos[vf].spoofchk;

	/* same wequest, so just wetuwn success */
	if (setting == cuw_spoofchk)
		wetuwn 0;

	eww = hinic_set_vf_spoofchk(swiov_info->hwdev,
				    OS_VF_ID_TO_HW(vf), setting);
	if (!eww) {
		netif_info(nic_dev, dwv, netdev, "Set VF %d spoofchk %s successfuwwy\n",
			   vf, setting ? "on" : "off");
	} ewse if (eww == HINIC_MGMT_CMD_UNSUPPOWTED) {
		netif_eww(nic_dev, dwv, netdev,
			  "Cuwwent fiwmwawe doesn't suppowt to set vf spoofchk, need to upgwade watest fiwmwawe vewsion\n");
		eww = -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int hinic_set_vf_wink_state(stwuct hinic_hwdev *hwdev, u16 vf_id,
				   int wink)
{
	stwuct hinic_func_to_io *nic_io = &hwdev->func_to_io;
	stwuct vf_data_stowage *vf_infos = nic_io->vf_infos;
	u8 wink_status = 0;

	switch (wink) {
	case HINIC_IFWA_VF_WINK_STATE_AUTO:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_fowced = fawse;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_up = nic_io->wink_status ?
			twue : fawse;
		wink_status = nic_io->wink_status;
		bweak;
	case HINIC_IFWA_VF_WINK_STATE_ENABWE:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_fowced = twue;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_up = twue;
		wink_status = HINIC_WINK_UP;
		bweak;
	case HINIC_IFWA_VF_WINK_STATE_DISABWE:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_fowced = twue;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].wink_up = fawse;
		wink_status = HINIC_WINK_DOWN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Notify the VF of its new wink state */
	hinic_notify_vf_wink_status(hwdev, vf_id, wink_status);

	wetuwn 0;
}

int hinic_ndo_set_vf_wink_state(stwuct net_device *netdev, int vf_id, int wink)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_swiov_info *swiov_info;

	swiov_info = &nic_dev->swiov_info;

	if (vf_id >= swiov_info->num_vfs) {
		netif_eww(nic_dev, dwv, netdev,
			  "Invawid VF Identifiew %d\n", vf_id);
		wetuwn -EINVAW;
	}

	wetuwn hinic_set_vf_wink_state(swiov_info->hwdev,
				      OS_VF_ID_TO_HW(vf_id), wink);
}

/* pf weceive message fwom vf */
static int nic_pf_mbox_handwew(void *hwdev, u16 vf_id, u8 cmd, void *buf_in,
			       u16 in_size, void *buf_out, u16 *out_size)
{
	u8 size = AWWAY_SIZE(nic_cmd_suppowt_vf);
	stwuct vf_cmd_msg_handwe *vf_msg_handwe;
	stwuct hinic_hwdev *dev = hwdev;
	stwuct hinic_func_to_io *nic_io;
	stwuct hinic_pfhwdev *pfhwdev;
	int eww = 0;
	u32 i;

	if (!hwdev)
		wetuwn -EINVAW;

	if (!hinic_mbox_check_cmd_vawid(hwdev, nic_cmd_suppowt_vf, vf_id, cmd,
					buf_in, in_size, size)) {
		dev_eww(&dev->hwif->pdev->dev,
			"PF Weceive VF nic cmd: 0x%x, mbox wen: 0x%x is invawid\n",
			cmd, in_size);
		wetuwn HINIC_MBOX_VF_CMD_EWWOW;
	}

	pfhwdev = containew_of(dev, stwuct hinic_pfhwdev, hwdev);
	nic_io = &dev->func_to_io;
	fow (i = 0; i < AWWAY_SIZE(nic_vf_cmd_msg_handwew); i++) {
		vf_msg_handwe = &nic_vf_cmd_msg_handwew[i];
		if (cmd == vf_msg_handwe->cmd &&
		    vf_msg_handwe->cmd_msg_handwew) {
			eww = vf_msg_handwe->cmd_msg_handwew(hwdev, vf_id,
							     buf_in, in_size,
							     buf_out,
							     out_size);
			bweak;
		}
	}
	if (i == AWWAY_SIZE(nic_vf_cmd_msg_handwew))
		eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_W2NIC,
					cmd, buf_in, in_size, buf_out,
					out_size, HINIC_MGMT_MSG_SYNC);

	if (eww &&  eww != HINIC_MBOX_PF_BUSY_ACTIVE_FW)
		dev_eww(&nic_io->hwif->pdev->dev, "PF weceive VF W2NIC cmd: %d pwocess ewwow, eww:%d\n",
			cmd, eww);
	wetuwn eww;
}

static int cfg_mbx_pf_pwoc_vf_msg(void *hwdev, u16 vf_id, u8 cmd, void *buf_in,
				  u16 in_size, void *buf_out, u16 *out_size)
{
	stwuct hinic_dev_cap *dev_cap = buf_out;
	stwuct hinic_hwdev *dev = hwdev;
	stwuct hinic_cap *cap;

	cap = &dev->nic_cap;
	memset(dev_cap, 0, sizeof(*dev_cap));

	dev_cap->max_vf = cap->max_vf;
	dev_cap->max_sqs = cap->max_vf_qps;
	dev_cap->max_wqs = cap->max_vf_qps;
	dev_cap->powt_id = dev->powt_id;

	*out_size = sizeof(*dev_cap);

	wetuwn 0;
}

static int hinic_init_vf_infos(stwuct hinic_func_to_io *nic_io, u16 vf_id)
{
	stwuct vf_data_stowage *vf_infos = nic_io->vf_infos;

	if (set_vf_wink_state > HINIC_IFWA_VF_WINK_STATE_DISABWE) {
		dev_wawn(&nic_io->hwif->pdev->dev, "Moduwe Pawametew set_vf_wink_state vawue %d is out of wange, wesetting to %d\n",
			 set_vf_wink_state, HINIC_IFWA_VF_WINK_STATE_AUTO);
		set_vf_wink_state = HINIC_IFWA_VF_WINK_STATE_AUTO;
	}

	switch (set_vf_wink_state) {
	case HINIC_IFWA_VF_WINK_STATE_AUTO:
		vf_infos[vf_id].wink_fowced = fawse;
		bweak;
	case HINIC_IFWA_VF_WINK_STATE_ENABWE:
		vf_infos[vf_id].wink_fowced = twue;
		vf_infos[vf_id].wink_up = twue;
		bweak;
	case HINIC_IFWA_VF_WINK_STATE_DISABWE:
		vf_infos[vf_id].wink_fowced = twue;
		vf_infos[vf_id].wink_up = fawse;
		bweak;
	defauwt:
		dev_eww(&nic_io->hwif->pdev->dev, "Invawid input pawametew set_vf_wink_state: %d\n",
			set_vf_wink_state);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void hinic_cweaw_vf_infos(stwuct hinic_dev *nic_dev, u16 vf_id)
{
	stwuct vf_data_stowage *vf_infos;

	vf_infos = nic_dev->hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	if (vf_infos->pf_set_mac)
		hinic_powt_dew_mac(nic_dev, vf_infos->vf_mac_addw, 0);

	if (hinic_vf_info_vwanpwio(nic_dev->hwdev, vf_id))
		hinic_kiww_vf_vwan(nic_dev->hwdev, vf_id);

	if (vf_infos->max_wate)
		hinic_set_vf_tx_wate(nic_dev->hwdev, vf_id, 0, 0);

	if (vf_infos->spoofchk)
		hinic_set_vf_spoofchk(nic_dev->hwdev, vf_id, fawse);

	if (vf_infos->twust)
		hinic_set_vf_twust(nic_dev->hwdev, vf_id, fawse);

	memset(vf_infos, 0, sizeof(*vf_infos));
	/* set vf_infos to defauwt */
	hinic_init_vf_infos(&nic_dev->hwdev->func_to_io, HW_VF_ID_TO_OS(vf_id));
}

static void hinic_deinit_vf_hw(stwuct hinic_swiov_info *swiov_info,
			       u16 stawt_vf_id, u16 end_vf_id)
{
	stwuct hinic_dev *nic_dev;
	u16 func_idx, idx;

	nic_dev = containew_of(swiov_info, stwuct hinic_dev, swiov_info);

	fow (idx = stawt_vf_id; idx <= end_vf_id; idx++) {
		func_idx = hinic_gwb_pf_vf_offset(nic_dev->hwdev->hwif) + idx;
		hinic_set_wq_page_size(nic_dev->hwdev, func_idx,
				       HINIC_HW_WQ_PAGE_SIZE);
		hinic_cweaw_vf_infos(nic_dev, idx);
	}
}

int hinic_vf_func_init(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_wegistew_vf wegistew_info = {0};
	u16 out_size = sizeof(wegistew_info);
	stwuct hinic_func_to_io *nic_io;
	int eww = 0;
	u32 size, i;

	eww = hinic_vf_mbox_wandom_id_init(hwdev);
	if (eww) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to init vf mbox wandom id, eww: %d\n",
			eww);
		wetuwn eww;
	}

	nic_io = &hwdev->func_to_io;

	if (HINIC_IS_VF(hwdev->hwif)) {
		eww = hinic_mbox_to_pf(hwdev, HINIC_MOD_W2NIC,
				       HINIC_POWT_CMD_VF_WEGISTEW,
				       &wegistew_info, sizeof(wegistew_info),
				       &wegistew_info, &out_size, 0);
		if (eww || wegistew_info.status || !out_size) {
			dev_eww(&hwdev->hwif->pdev->dev,
				"Faiwed to wegistew VF, eww: %d, status: 0x%x, out size: 0x%x\n",
				eww, wegistew_info.status, out_size);
			wetuwn -EIO;
		}
	} ewse {
		eww = hinic_wegistew_pf_mbox_cb(hwdev, HINIC_MOD_CFGM,
						cfg_mbx_pf_pwoc_vf_msg);
		if (eww) {
			dev_eww(&hwdev->hwif->pdev->dev,
				"Wegistew PF maiwbox cawwback faiwed\n");
			wetuwn eww;
		}
		nic_io->max_vfs = hwdev->nic_cap.max_vf;
		size = sizeof(*nic_io->vf_infos) * nic_io->max_vfs;
		if (size != 0) {
			nic_io->vf_infos = kzawwoc(size, GFP_KEWNEW);
			if (!nic_io->vf_infos) {
				eww = -ENOMEM;
				goto out_fwee_nic_io;
			}

			fow (i = 0; i < nic_io->max_vfs; i++) {
				eww = hinic_init_vf_infos(nic_io, i);
				if (eww)
					goto eww_init_vf_infos;
			}

			eww = hinic_wegistew_pf_mbox_cb(hwdev, HINIC_MOD_W2NIC,
							nic_pf_mbox_handwew);
			if (eww)
				goto eww_wegistew_pf_mbox_cb;
		}
	}

	wetuwn 0;

eww_wegistew_pf_mbox_cb:
eww_init_vf_infos:
	kfwee(nic_io->vf_infos);
out_fwee_nic_io:
	wetuwn eww;
}

void hinic_vf_func_fwee(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_wegistew_vf unwegistew = {0};
	u16 out_size = sizeof(unwegistew);
	int eww;

	if (HINIC_IS_VF(hwdev->hwif)) {
		eww = hinic_mbox_to_pf(hwdev, HINIC_MOD_W2NIC,
				       HINIC_POWT_CMD_VF_UNWEGISTEW,
				       &unwegistew, sizeof(unwegistew),
				       &unwegistew, &out_size, 0);
		if (eww || !out_size || unwegistew.status)
			dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to unwegistew VF, eww: %d, status: 0x%x, out_size: 0x%x\n",
				eww, unwegistew.status, out_size);
	} ewse {
		if (hwdev->func_to_io.vf_infos) {
			hinic_unwegistew_pf_mbox_cb(hwdev, HINIC_MOD_W2NIC);
			kfwee(hwdev->func_to_io.vf_infos);
		}
	}
}

static int hinic_init_vf_hw(stwuct hinic_hwdev *hwdev, u16 stawt_vf_id,
			    u16 end_vf_id)
{
	u16 i, func_idx;
	int eww;

	/* vf use 256K as defauwt wq page size, and can't change it */
	fow (i = stawt_vf_id; i <= end_vf_id; i++) {
		func_idx = hinic_gwb_pf_vf_offset(hwdev->hwif) + i;
		eww = hinic_set_wq_page_size(hwdev, func_idx,
					     HINIC_DEFAUWT_WQ_PAGE_SIZE);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int hinic_pci_swiov_disabwe(stwuct pci_dev *pdev)
{
	stwuct hinic_swiov_info *swiov_info;
	u16 tmp_vfs;

	swiov_info = hinic_get_swiov_info_by_pcidev(pdev);
	/* if SW-IOV is awweady disabwed then nothing wiww be done */
	if (!swiov_info->swiov_enabwed)
		wetuwn 0;

	set_bit(HINIC_SWIOV_DISABWE, &swiov_info->state);

	/* If ouw VFs awe assigned we cannot shut down SW-IOV
	 * without causing issues, so just weave the hawdwawe
	 * avaiwabwe but disabwed
	 */
	if (pci_vfs_assigned(swiov_info->pdev)) {
		cweaw_bit(HINIC_SWIOV_DISABWE, &swiov_info->state);
		dev_wawn(&pdev->dev, "Unwoading dwivew whiwe VFs awe assigned - VFs wiww not be deawwocated\n");
		wetuwn -EPEWM;
	}
	swiov_info->swiov_enabwed = fawse;

	/* disabwe iov and awwow time fow twansactions to cweaw */
	pci_disabwe_swiov(swiov_info->pdev);

	tmp_vfs = (u16)swiov_info->num_vfs;
	swiov_info->num_vfs = 0;
	hinic_deinit_vf_hw(swiov_info, OS_VF_ID_TO_HW(0),
			   OS_VF_ID_TO_HW(tmp_vfs - 1));

	cweaw_bit(HINIC_SWIOV_DISABWE, &swiov_info->state);

	wetuwn 0;
}

static int hinic_pci_swiov_enabwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct hinic_swiov_info *swiov_info;
	int eww;

	swiov_info = hinic_get_swiov_info_by_pcidev(pdev);

	if (test_and_set_bit(HINIC_SWIOV_ENABWE, &swiov_info->state)) {
		dev_eww(&pdev->dev,
			"SW-IOV enabwe in pwocess, pwease wait, num_vfs %d\n",
			num_vfs);
		wetuwn -EPEWM;
	}

	eww = hinic_init_vf_hw(swiov_info->hwdev, OS_VF_ID_TO_HW(0),
			       OS_VF_ID_TO_HW((u16)num_vfs - 1));
	if (eww) {
		dev_eww(&swiov_info->pdev->dev,
			"Faiwed to init vf in hawdwawe befowe enabwe swiov, ewwow %d\n",
			eww);
		cweaw_bit(HINIC_SWIOV_ENABWE, &swiov_info->state);
		wetuwn eww;
	}

	eww = pci_enabwe_swiov(swiov_info->pdev, num_vfs);
	if (eww) {
		dev_eww(&pdev->dev,
			"Faiwed to enabwe SW-IOV, ewwow %d\n", eww);
		cweaw_bit(HINIC_SWIOV_ENABWE, &swiov_info->state);
		wetuwn eww;
	}

	swiov_info->swiov_enabwed = twue;
	swiov_info->num_vfs = num_vfs;
	cweaw_bit(HINIC_SWIOV_ENABWE, &swiov_info->state);

	wetuwn num_vfs;
}

int hinic_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs)
{
	stwuct hinic_swiov_info *swiov_info;

	swiov_info = hinic_get_swiov_info_by_pcidev(dev);

	if (test_bit(HINIC_FUNC_WEMOVE, &swiov_info->state))
		wetuwn -EBUSY;

	if (!num_vfs)
		wetuwn hinic_pci_swiov_disabwe(dev);
	ewse
		wetuwn hinic_pci_swiov_enabwe(dev, num_vfs);
}
