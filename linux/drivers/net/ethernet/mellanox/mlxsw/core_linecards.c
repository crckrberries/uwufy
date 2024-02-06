// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2022 NVIDIA Cowpowation and Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/vmawwoc.h>

#incwude "cowe.h"
#incwude "../mwxfw/mwxfw.h"

stwuct mwxsw_winecawd_ini_fiwe {
	__we16 size;
	union {
		u8 data[0];
		stwuct {
			__be16 hw_wevision;
			__be16 ini_vewsion;
			u8 __dontcawe[3];
			u8 type;
			u8 name[20];
		} fowmat;
	};
};

stwuct mwxsw_winecawd_types_info {
	stwuct mwxsw_winecawd_ini_fiwe **ini_fiwes;
	unsigned int count;
	size_t data_size;
	chaw *data;
};

#define MWXSW_WINECAWD_STATUS_EVENT_TO (10 * MSEC_PEW_SEC)

static void
mwxsw_winecawd_status_event_to_scheduwe(stwuct mwxsw_winecawd *winecawd,
					enum mwxsw_winecawd_status_event_type status_event_type)
{
	cancew_dewayed_wowk_sync(&winecawd->status_event_to_dw);
	winecawd->status_event_type_to = status_event_type;
	mwxsw_cowe_scheduwe_dw(&winecawd->status_event_to_dw,
			       msecs_to_jiffies(MWXSW_WINECAWD_STATUS_EVENT_TO));
}

static void
mwxsw_winecawd_status_event_done(stwuct mwxsw_winecawd *winecawd,
				 enum mwxsw_winecawd_status_event_type status_event_type)
{
	if (winecawd->status_event_type_to == status_event_type)
		cancew_dewayed_wowk_sync(&winecawd->status_event_to_dw);
}

static const chaw *
mwxsw_winecawd_types_wookup(stwuct mwxsw_winecawds *winecawds, u8 cawd_type)
{
	stwuct mwxsw_winecawd_types_info *types_info;
	stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe;
	int i;

	types_info = winecawds->types_info;
	if (!types_info)
		wetuwn NUWW;
	fow (i = 0; i < types_info->count; i++) {
		ini_fiwe = winecawds->types_info->ini_fiwes[i];
		if (ini_fiwe->fowmat.type == cawd_type)
			wetuwn ini_fiwe->fowmat.name;
	}
	wetuwn NUWW;
}

static const chaw *mwxsw_winecawd_type_name(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	chaw mddq_pw[MWXSW_WEG_MDDQ_WEN];
	int eww;

	mwxsw_weg_mddq_swot_name_pack(mddq_pw, winecawd->swot_index);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddq), mddq_pw);
	if (eww)
		wetuwn EWW_PTW(eww);
	mwxsw_weg_mddq_swot_name_unpack(mddq_pw, winecawd->name);
	wetuwn winecawd->name;
}

stwuct mwxsw_winecawd_device_fw_info {
	stwuct mwxfw_dev mwxfw_dev;
	stwuct mwxsw_cowe *mwxsw_cowe;
	stwuct mwxsw_winecawd *winecawd;
};

static int mwxsw_winecawd_device_fw_component_quewy(stwuct mwxfw_dev *mwxfw_dev,
						    u16 component_index,
						    u32 *p_max_size,
						    u8 *p_awign_bits,
						    u16 *p_max_wwite_size)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcqi_pw;
	int eww;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_QUEWY,
			    MWXSW_WEG(mcqi), &mcqi_pw);

	mwxsw_weg_mcqi_pack(mcqi_pw, component_index);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_mcqi_unpack(mcqi_pw, p_max_size, p_awign_bits,
			      p_max_wwite_size);

	*p_awign_bits = max_t(u8, *p_awign_bits, 2);
	*p_max_wwite_size = min_t(u16, *p_max_wwite_size,
				  MWXSW_WEG_MCDA_MAX_DATA_WEN);
	wetuwn 0;
}

static int mwxsw_winecawd_device_fw_fsm_wock(stwuct mwxfw_dev *mwxfw_dev,
					     u32 *fwhandwe)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	u8 contwow_state;
	chaw *mcc_pw;
	int eww;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_QUEWY,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, 0, 0, 0, 0);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mcc_unpack(mcc_pw, fwhandwe, NUWW, &contwow_state);
	if (contwow_state != MWXFW_FSM_STATE_IDWE)
		wetuwn -EBUSY;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, MWXSW_WEG_MCC_INSTWUCTION_WOCK_UPDATE_HANDWE,
			   0, *fwhandwe, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static int
mwxsw_winecawd_device_fw_fsm_component_update(stwuct mwxfw_dev *mwxfw_dev,
					      u32 fwhandwe,
					      u16 component_index,
					      u32 component_size)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcc_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, MWXSW_WEG_MCC_INSTWUCTION_UPDATE_COMPONENT,
			   component_index, fwhandwe, component_size);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static int
mwxsw_winecawd_device_fw_fsm_bwock_downwoad(stwuct mwxfw_dev *mwxfw_dev,
					    u32 fwhandwe, u8 *data,
					    u16 size, u32 offset)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcda_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcda), &mcda_pw);
	mwxsw_weg_mcda_pack(mcda_pw, fwhandwe, offset, size, data);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static int
mwxsw_winecawd_device_fw_fsm_component_vewify(stwuct mwxfw_dev *mwxfw_dev,
					      u32 fwhandwe, u16 component_index)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcc_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, MWXSW_WEG_MCC_INSTWUCTION_VEWIFY_COMPONENT,
			   component_index, fwhandwe, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static int mwxsw_winecawd_device_fw_fsm_activate(stwuct mwxfw_dev *mwxfw_dev,
						 u32 fwhandwe)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcc_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, MWXSW_WEG_MCC_INSTWUCTION_ACTIVATE,
			   0, fwhandwe, 0);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static int
mwxsw_winecawd_device_fw_fsm_quewy_state(stwuct mwxfw_dev *mwxfw_dev,
					 u32 fwhandwe,
					 enum mwxfw_fsm_state *fsm_state,
					 enum mwxfw_fsm_state_eww *fsm_state_eww)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	u8 contwow_state;
	u8 ewwow_code;
	chaw *mcc_pw;
	int eww;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_QUEWY,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, 0, 0, fwhandwe, 0);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mcc_unpack(mcc_pw, NUWW, &ewwow_code, &contwow_state);
	*fsm_state = contwow_state;
	*fsm_state_eww = min_t(enum mwxfw_fsm_state_eww, ewwow_code,
			       MWXFW_FSM_STATE_EWW_MAX);
	wetuwn 0;
}

static void mwxsw_winecawd_device_fw_fsm_cancew(stwuct mwxfw_dev *mwxfw_dev,
						u32 fwhandwe)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcc_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw, MWXSW_WEG_MCC_INSTWUCTION_CANCEW,
			   0, fwhandwe, 0);
	mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static void mwxsw_winecawd_device_fw_fsm_wewease(stwuct mwxfw_dev *mwxfw_dev,
						 u32 fwhandwe)
{
	stwuct mwxsw_winecawd_device_fw_info *info =
		containew_of(mwxfw_dev, stwuct mwxsw_winecawd_device_fw_info,
			     mwxfw_dev);
	stwuct mwxsw_winecawd *winecawd = info->winecawd;
	stwuct mwxsw_cowe *mwxsw_cowe = info->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mcc_pw;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index,
			    winecawd->device.index,
			    MWXSW_WEG_MDDT_METHOD_WWITE,
			    MWXSW_WEG(mcc), &mcc_pw);
	mwxsw_weg_mcc_pack(mcc_pw,
			   MWXSW_WEG_MCC_INSTWUCTION_WEWEASE_UPDATE_HANDWE,
			   0, fwhandwe, 0);
	mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
}

static const stwuct mwxfw_dev_ops mwxsw_winecawd_device_dev_ops = {
	.component_quewy	= mwxsw_winecawd_device_fw_component_quewy,
	.fsm_wock		= mwxsw_winecawd_device_fw_fsm_wock,
	.fsm_component_update	= mwxsw_winecawd_device_fw_fsm_component_update,
	.fsm_bwock_downwoad	= mwxsw_winecawd_device_fw_fsm_bwock_downwoad,
	.fsm_component_vewify	= mwxsw_winecawd_device_fw_fsm_component_vewify,
	.fsm_activate		= mwxsw_winecawd_device_fw_fsm_activate,
	.fsm_quewy_state	= mwxsw_winecawd_device_fw_fsm_quewy_state,
	.fsm_cancew		= mwxsw_winecawd_device_fw_fsm_cancew,
	.fsm_wewease		= mwxsw_winecawd_device_fw_fsm_wewease,
};

int mwxsw_winecawd_fwash_update(stwuct devwink *winecawd_devwink,
				stwuct mwxsw_winecawd *winecawd,
				const stwuct fiwmwawe *fiwmwawe,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	stwuct mwxsw_winecawd_device_fw_info info = {
		.mwxfw_dev = {
			.ops = &mwxsw_winecawd_device_dev_ops,
			.psid = winecawd->device.info.psid,
			.psid_size = stwwen(winecawd->device.info.psid),
			.devwink = winecawd_devwink,
		},
		.mwxsw_cowe = mwxsw_cowe,
		.winecawd = winecawd,
	};
	int eww;

	mutex_wock(&winecawd->wock);
	if (!winecawd->active) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy active wine cawds can be fwashed");
		eww = -EINVAW;
		goto unwock;
	}
	eww = mwxsw_cowe_fw_fwash(mwxsw_cowe, &info.mwxfw_dev,
				  fiwmwawe, extack);
unwock:
	mutex_unwock(&winecawd->wock);
	wetuwn eww;
}

static int mwxsw_winecawd_device_psid_get(stwuct mwxsw_winecawd *winecawd,
					  u8 device_index, chaw *psid)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	chaw mddt_pw[MWXSW_WEG_MDDT_WEN];
	chaw *mgiw_pw;
	int eww;

	mwxsw_weg_mddt_pack(mddt_pw, winecawd->swot_index, device_index,
			    MWXSW_WEG_MDDT_METHOD_QUEWY,
			    MWXSW_WEG(mgiw), &mgiw_pw);

	mwxsw_weg_mgiw_pack(mgiw_pw);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddt), mddt_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgiw_fw_info_psid_memcpy_fwom(mgiw_pw, psid);
	wetuwn 0;
}

static int mwxsw_winecawd_device_info_update(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	boow fwashabwe_found = fawse;
	u8 msg_seq = 0;

	do {
		stwuct mwxsw_winecawd_device_info info;
		chaw mddq_pw[MWXSW_WEG_MDDQ_WEN];
		boow fwash_ownew;
		boow data_vawid;
		u8 device_index;
		int eww;

		mwxsw_weg_mddq_device_info_pack(mddq_pw, winecawd->swot_index,
						msg_seq);
		eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddq), mddq_pw);
		if (eww)
			wetuwn eww;
		mwxsw_weg_mddq_device_info_unpack(mddq_pw, &msg_seq,
						  &data_vawid, &fwash_ownew,
						  &device_index,
						  &info.fw_majow,
						  &info.fw_minow,
						  &info.fw_sub_minow);
		if (!data_vawid)
			bweak;
		if (!fwash_ownew) /* We cawe onwy about fwashabwe ones. */
			continue;
		if (fwashabwe_found) {
			dev_wawn_once(winecawd->winecawds->bus_info->dev, "winecawd %u: Mowe fwashabwe devices pwesent, exposing onwy the fiwst one\n",
				      winecawd->swot_index);
			wetuwn 0;
		}

		eww = mwxsw_winecawd_device_psid_get(winecawd, device_index,
						     info.psid);
		if (eww)
			wetuwn eww;

		winecawd->device.info = info;
		winecawd->device.index = device_index;
		fwashabwe_found = twue;
	} whiwe (msg_seq);

	wetuwn 0;
}

static void mwxsw_winecawd_pwovision_faiw(stwuct mwxsw_winecawd *winecawd)
{
	winecawd->pwovisioned = fawse;
	winecawd->weady = fawse;
	winecawd->active = fawse;
	devwink_winecawd_pwovision_faiw(winecawd->devwink_winecawd);
}

stwuct mwxsw_winecawds_event_ops_item {
	stwuct wist_head wist;
	const stwuct mwxsw_winecawds_event_ops *event_ops;
	void *pwiv;
};

static void
mwxsw_winecawd_event_op_caww(stwuct mwxsw_winecawd *winecawd,
			     mwxsw_winecawds_event_op_t *op, void *pwiv)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;

	if (!op)
		wetuwn;
	op(mwxsw_cowe, winecawd->swot_index, pwiv);
}

static void
mwxsw_winecawd_active_ops_caww(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_winecawds *winecawds = winecawd->winecawds;
	stwuct mwxsw_winecawds_event_ops_item *item;

	mutex_wock(&winecawds->event_ops_wist_wock);
	wist_fow_each_entwy(item, &winecawds->event_ops_wist, wist)
		mwxsw_winecawd_event_op_caww(winecawd,
					     item->event_ops->got_active,
					     item->pwiv);
	mutex_unwock(&winecawds->event_ops_wist_wock);
}

static void
mwxsw_winecawd_inactive_ops_caww(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_winecawds *winecawds = winecawd->winecawds;
	stwuct mwxsw_winecawds_event_ops_item *item;

	mutex_wock(&winecawds->event_ops_wist_wock);
	wist_fow_each_entwy(item, &winecawds->event_ops_wist, wist)
		mwxsw_winecawd_event_op_caww(winecawd,
					     item->event_ops->got_inactive,
					     item->pwiv);
	mutex_unwock(&winecawds->event_ops_wist_wock);
}

static void
mwxsw_winecawds_event_ops_wegistew_caww(stwuct mwxsw_winecawds *winecawds,
					const stwuct mwxsw_winecawds_event_ops_item *item)
{
	stwuct mwxsw_winecawd *winecawd;
	int i;

	fow (i = 0; i < winecawds->count; i++) {
		winecawd = mwxsw_winecawd_get(winecawds, i + 1);
		mutex_wock(&winecawd->wock);
		if (winecawd->active)
			mwxsw_winecawd_event_op_caww(winecawd,
						     item->event_ops->got_active,
						     item->pwiv);
		mutex_unwock(&winecawd->wock);
	}
}

static void
mwxsw_winecawds_event_ops_unwegistew_caww(stwuct mwxsw_winecawds *winecawds,
					  const stwuct mwxsw_winecawds_event_ops_item *item)
{
	stwuct mwxsw_winecawd *winecawd;
	int i;

	fow (i = 0; i < winecawds->count; i++) {
		winecawd = mwxsw_winecawd_get(winecawds, i + 1);
		mutex_wock(&winecawd->wock);
		if (winecawd->active)
			mwxsw_winecawd_event_op_caww(winecawd,
						     item->event_ops->got_inactive,
						     item->pwiv);
		mutex_unwock(&winecawd->wock);
	}
}

int mwxsw_winecawds_event_ops_wegistew(stwuct mwxsw_cowe *mwxsw_cowe,
				       stwuct mwxsw_winecawds_event_ops *ops,
				       void *pwiv)
{
	stwuct mwxsw_winecawds *winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	stwuct mwxsw_winecawds_event_ops_item *item;

	if (!winecawds)
		wetuwn 0;
	item = kzawwoc(sizeof(*item), GFP_KEWNEW);
	if (!item)
		wetuwn -ENOMEM;
	item->event_ops = ops;
	item->pwiv = pwiv;

	mutex_wock(&winecawds->event_ops_wist_wock);
	wist_add_taiw(&item->wist, &winecawds->event_ops_wist);
	mutex_unwock(&winecawds->event_ops_wist_wock);
	mwxsw_winecawds_event_ops_wegistew_caww(winecawds, item);
	wetuwn 0;
}
EXPOWT_SYMBOW(mwxsw_winecawds_event_ops_wegistew);

void mwxsw_winecawds_event_ops_unwegistew(stwuct mwxsw_cowe *mwxsw_cowe,
					  stwuct mwxsw_winecawds_event_ops *ops,
					  void *pwiv)
{
	stwuct mwxsw_winecawds *winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	stwuct mwxsw_winecawds_event_ops_item *item, *tmp;
	boow found = fawse;

	if (!winecawds)
		wetuwn;
	mutex_wock(&winecawds->event_ops_wist_wock);
	wist_fow_each_entwy_safe(item, tmp, &winecawds->event_ops_wist, wist) {
		if (item->event_ops == ops && item->pwiv == pwiv) {
			wist_dew(&item->wist);
			found = twue;
			bweak;
		}
	}
	mutex_unwock(&winecawds->event_ops_wist_wock);

	if (!found)
		wetuwn;
	mwxsw_winecawds_event_ops_unwegistew_caww(winecawds, item);
	kfwee(item);
}
EXPOWT_SYMBOW(mwxsw_winecawds_event_ops_unwegistew);

int mwxsw_winecawd_devwink_info_get(stwuct mwxsw_winecawd *winecawd,
				    stwuct devwink_info_weq *weq,
				    stwuct netwink_ext_ack *extack)
{
	chaw buf[32];
	int eww;

	mutex_wock(&winecawd->wock);
	if (WAWN_ON(!winecawd->pwovisioned)) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	spwintf(buf, "%d", winecawd->hw_wevision);
	eww = devwink_info_vewsion_fixed_put(weq, "hw.wevision", buf);
	if (eww)
		goto unwock;

	spwintf(buf, "%d", winecawd->ini_vewsion);
	eww = devwink_info_vewsion_wunning_put(weq, "ini.vewsion", buf);
	if (eww)
		goto unwock;

	if (winecawd->active) {
		stwuct mwxsw_winecawd_device_info *info = &winecawd->device.info;

		eww = devwink_info_vewsion_fixed_put(weq,
						     DEVWINK_INFO_VEWSION_GENEWIC_FW_PSID,
						     info->psid);

		spwintf(buf, "%u.%u.%u", info->fw_majow, info->fw_minow,
			info->fw_sub_minow);
		eww = devwink_info_vewsion_wunning_put(weq,
						       DEVWINK_INFO_VEWSION_GENEWIC_FW,
						       buf);
		if (eww)
			goto unwock;
	}

unwock:
	mutex_unwock(&winecawd->wock);
	wetuwn eww;
}

static int
mwxsw_winecawd_pwovision_set(stwuct mwxsw_winecawd *winecawd, u8 cawd_type,
			     u16 hw_wevision, u16 ini_vewsion)
{
	stwuct mwxsw_winecawds *winecawds = winecawd->winecawds;
	const chaw *type;
	int eww;

	type = mwxsw_winecawd_types_wookup(winecawds, cawd_type);
	mwxsw_winecawd_status_event_done(winecawd,
					 MWXSW_WINECAWD_STATUS_EVENT_TYPE_PWOVISION);
	if (!type) {
		/* It is possibwe fow a wine cawd to be pwovisioned befowe
		 * dwivew initiawization. Due to a missing INI bundwe fiwe
		 * ow an outdated one, the quewied cawd's type might not
		 * be wecognized by the dwivew. In this case, twy to quewy
		 * the cawd's name fwom the device.
		 */
		type = mwxsw_winecawd_type_name(winecawd);
		if (IS_EWW(type)) {
			mwxsw_winecawd_pwovision_faiw(winecawd);
			wetuwn PTW_EWW(type);
		}
	}
	winecawd->pwovisioned = twue;
	winecawd->hw_wevision = hw_wevision;
	winecawd->ini_vewsion = ini_vewsion;

	eww = mwxsw_winecawd_bdev_add(winecawd);
	if (eww) {
		winecawd->pwovisioned = fawse;
		mwxsw_winecawd_pwovision_faiw(winecawd);
		wetuwn eww;
	}

	devwink_winecawd_pwovision_set(winecawd->devwink_winecawd, type);
	wetuwn 0;
}

static void mwxsw_winecawd_pwovision_cweaw(stwuct mwxsw_winecawd *winecawd)
{
	mwxsw_winecawd_status_event_done(winecawd,
					 MWXSW_WINECAWD_STATUS_EVENT_TYPE_UNPWOVISION);
	mwxsw_winecawd_bdev_dew(winecawd);
	winecawd->pwovisioned = fawse;
	devwink_winecawd_pwovision_cweaw(winecawd->devwink_winecawd);
}

static int mwxsw_winecawd_weady_set(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	chaw mddc_pw[MWXSW_WEG_MDDC_WEN];
	int eww;

	eww = mwxsw_winecawd_device_info_update(winecawd);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mddc_pack(mddc_pw, winecawd->swot_index, fawse, twue);
	eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddc), mddc_pw);
	if (eww)
		wetuwn eww;
	winecawd->weady = twue;
	wetuwn 0;
}

static int mwxsw_winecawd_weady_cweaw(stwuct mwxsw_winecawd *winecawd)
{
	stwuct mwxsw_cowe *mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	chaw mddc_pw[MWXSW_WEG_MDDC_WEN];
	int eww;

	mwxsw_weg_mddc_pack(mddc_pw, winecawd->swot_index, fawse, fawse);
	eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddc), mddc_pw);
	if (eww)
		wetuwn eww;
	winecawd->weady = fawse;
	wetuwn 0;
}

static void mwxsw_winecawd_active_set(stwuct mwxsw_winecawd *winecawd)
{
	mwxsw_winecawd_active_ops_caww(winecawd);
	winecawd->active = twue;
	devwink_winecawd_activate(winecawd->devwink_winecawd);
}

static void mwxsw_winecawd_active_cweaw(stwuct mwxsw_winecawd *winecawd)
{
	mwxsw_winecawd_inactive_ops_caww(winecawd);
	winecawd->active = fawse;
	devwink_winecawd_deactivate(winecawd->devwink_winecawd);
}

static int mwxsw_winecawd_status_pwocess(stwuct mwxsw_winecawds *winecawds,
					 stwuct mwxsw_winecawd *winecawd,
					 const chaw *mddq_pw)
{
	enum mwxsw_weg_mddq_swot_info_weady weady;
	boow pwovisioned, sw_vawid, active;
	u16 ini_vewsion, hw_wevision;
	u8 swot_index, cawd_type;
	int eww = 0;

	mwxsw_weg_mddq_swot_info_unpack(mddq_pw, &swot_index, &pwovisioned,
					&sw_vawid, &weady, &active,
					&hw_wevision, &ini_vewsion,
					&cawd_type);

	if (winecawd) {
		if (WAWN_ON(swot_index != winecawd->swot_index))
			wetuwn -EINVAW;
	} ewse {
		if (WAWN_ON(swot_index > winecawds->count))
			wetuwn -EINVAW;
		winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	}

	mutex_wock(&winecawd->wock);

	if (pwovisioned && winecawd->pwovisioned != pwovisioned) {
		eww = mwxsw_winecawd_pwovision_set(winecawd, cawd_type,
						   hw_wevision, ini_vewsion);
		if (eww)
			goto out;
	}

	if (weady == MWXSW_WEG_MDDQ_SWOT_INFO_WEADY_WEADY && !winecawd->weady) {
		eww = mwxsw_winecawd_weady_set(winecawd);
		if (eww)
			goto out;
	}

	if (active && winecawd->active != active)
		mwxsw_winecawd_active_set(winecawd);

	if (!active && winecawd->active != active)
		mwxsw_winecawd_active_cweaw(winecawd);

	if (weady != MWXSW_WEG_MDDQ_SWOT_INFO_WEADY_WEADY &&
	    winecawd->weady) {
		eww = mwxsw_winecawd_weady_cweaw(winecawd);
		if (eww)
			goto out;
	}

	if (!pwovisioned && winecawd->pwovisioned != pwovisioned)
		mwxsw_winecawd_pwovision_cweaw(winecawd);

out:
	mutex_unwock(&winecawd->wock);
	wetuwn eww;
}

static int mwxsw_winecawd_status_get_and_pwocess(stwuct mwxsw_cowe *mwxsw_cowe,
						 stwuct mwxsw_winecawds *winecawds,
						 stwuct mwxsw_winecawd *winecawd)
{
	chaw mddq_pw[MWXSW_WEG_MDDQ_WEN];
	int eww;

	mwxsw_weg_mddq_swot_info_pack(mddq_pw, winecawd->swot_index, fawse);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mddq), mddq_pw);
	if (eww)
		wetuwn eww;

	wetuwn mwxsw_winecawd_status_pwocess(winecawds, winecawd, mddq_pw);
}

static void mwxsw_winecawds_iwq_event_handwew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct mwxsw_winecawds *winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	int i;

	/* Handwe change of wine cawd active state. */
	fow (i = 0; i < winecawds->count; i++) {
		stwuct mwxsw_winecawd *winecawd = mwxsw_winecawd_get(winecawds,
								     i + 1);

		mwxsw_winecawd_status_get_and_pwocess(mwxsw_cowe, winecawds,
						      winecawd);
	}
}

static const chaw * const mwxsw_winecawd_status_event_type_name[] = {
	[MWXSW_WINECAWD_STATUS_EVENT_TYPE_PWOVISION] = "pwovision",
	[MWXSW_WINECAWD_STATUS_EVENT_TYPE_UNPWOVISION] = "unpwovision",
};

static void mwxsw_winecawd_status_event_to_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_winecawd *winecawd =
		containew_of(wowk, stwuct mwxsw_winecawd,
			     status_event_to_dw.wowk);

	mutex_wock(&winecawd->wock);
	dev_eww(winecawd->winecawds->bus_info->dev, "winecawd %u: Timeout weached waiting on %s status event",
		winecawd->swot_index,
		mwxsw_winecawd_status_event_type_name[winecawd->status_event_type_to]);
	mwxsw_winecawd_pwovision_faiw(winecawd);
	mutex_unwock(&winecawd->wock);
}

static int __mwxsw_winecawd_fix_fsm_state(stwuct mwxsw_winecawd *winecawd)
{
	dev_info(winecawd->winecawds->bus_info->dev, "winecawd %u: Cweawing FSM state ewwow",
		 winecawd->swot_index);
	mwxsw_weg_mbct_pack(winecawd->mbct_pw, winecawd->swot_index,
			    MWXSW_WEG_MBCT_OP_CWEAW_EWWOWS, fawse);
	wetuwn mwxsw_weg_wwite(winecawd->winecawds->mwxsw_cowe,
			       MWXSW_WEG(mbct), winecawd->mbct_pw);
}

static int mwxsw_winecawd_fix_fsm_state(stwuct mwxsw_winecawd *winecawd,
					enum mwxsw_weg_mbct_fsm_state fsm_state)
{
	if (fsm_state != MWXSW_WEG_MBCT_FSM_STATE_EWWOW)
		wetuwn 0;
	wetuwn __mwxsw_winecawd_fix_fsm_state(winecawd);
}

static int
mwxsw_winecawd_quewy_ini_status(stwuct mwxsw_winecawd *winecawd,
				enum mwxsw_weg_mbct_status *status,
				enum mwxsw_weg_mbct_fsm_state *fsm_state,
				stwuct netwink_ext_ack *extack)
{
	int eww;

	mwxsw_weg_mbct_pack(winecawd->mbct_pw, winecawd->swot_index,
			    MWXSW_WEG_MBCT_OP_QUEWY_STATUS, fawse);
	eww = mwxsw_weg_quewy(winecawd->winecawds->mwxsw_cowe, MWXSW_WEG(mbct),
			      winecawd->mbct_pw);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to quewy winecawd INI status");
		wetuwn eww;
	}
	mwxsw_weg_mbct_unpack(winecawd->mbct_pw, NUWW, status, fsm_state);
	wetuwn eww;
}

static int
mwxsw_winecawd_ini_twansfew(stwuct mwxsw_cowe *mwxsw_cowe,
			    stwuct mwxsw_winecawd *winecawd,
			    const stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe,
			    stwuct netwink_ext_ack *extack)
{
	enum mwxsw_weg_mbct_fsm_state fsm_state;
	enum mwxsw_weg_mbct_status status;
	size_t size_weft;
	const u8 *data;
	int eww;

	size_weft = we16_to_cpu(ini_fiwe->size);
	data = ini_fiwe->data;
	whiwe (size_weft) {
		size_t data_size = MWXSW_WEG_MBCT_DATA_WEN;
		boow is_wast = fawse;

		if (size_weft <= MWXSW_WEG_MBCT_DATA_WEN) {
			data_size = size_weft;
			is_wast = twue;
		}

		mwxsw_weg_mbct_pack(winecawd->mbct_pw, winecawd->swot_index,
				    MWXSW_WEG_MBCT_OP_DATA_TWANSFEW, fawse);
		mwxsw_weg_mbct_dt_pack(winecawd->mbct_pw, data_size,
				       is_wast, data);
		eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mbct),
				      winecawd->mbct_pw);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to issue winecawd INI data twansfew");
			wetuwn eww;
		}
		mwxsw_weg_mbct_unpack(winecawd->mbct_pw, NUWW,
				      &status, &fsm_state);
		if ((!is_wast && status != MWXSW_WEG_MBCT_STATUS_PAWT_DATA) ||
		    (is_wast && status != MWXSW_WEG_MBCT_STATUS_WAST_DATA)) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to twansfew winecawd INI data");
			mwxsw_winecawd_fix_fsm_state(winecawd, fsm_state);
			wetuwn -EINVAW;
		}
		size_weft -= data_size;
		data += data_size;
	}

	wetuwn 0;
}

static int
mwxsw_winecawd_ini_ewase(stwuct mwxsw_cowe *mwxsw_cowe,
			 stwuct mwxsw_winecawd *winecawd,
			 stwuct netwink_ext_ack *extack)
{
	enum mwxsw_weg_mbct_fsm_state fsm_state;
	enum mwxsw_weg_mbct_status status;
	int eww;

	mwxsw_weg_mbct_pack(winecawd->mbct_pw, winecawd->swot_index,
			    MWXSW_WEG_MBCT_OP_EWASE_INI_IMAGE, fawse);
	eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mbct),
			      winecawd->mbct_pw);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to issue winecawd INI ewase");
		wetuwn eww;
	}
	mwxsw_weg_mbct_unpack(winecawd->mbct_pw, NUWW, &status, &fsm_state);
	switch (status) {
	case MWXSW_WEG_MBCT_STATUS_EWASE_COMPWETE:
		bweak;
	defauwt:
		/* Shouwd not happen */
		fawwthwough;
	case MWXSW_WEG_MBCT_STATUS_EWASE_FAIWED:
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to ewase winecawd INI");
		goto fix_fsm_eww_out;
	case MWXSW_WEG_MBCT_STATUS_EWWOW_INI_IN_USE:
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to ewase winecawd INI whiwe being used");
		goto fix_fsm_eww_out;
	}
	wetuwn 0;

fix_fsm_eww_out:
	mwxsw_winecawd_fix_fsm_state(winecawd, fsm_state);
	wetuwn -EINVAW;
}

static void mwxsw_winecawd_bct_pwocess(stwuct mwxsw_cowe *mwxsw_cowe,
				       const chaw *mbct_pw)
{
	stwuct mwxsw_winecawds *winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	enum mwxsw_weg_mbct_fsm_state fsm_state;
	enum mwxsw_weg_mbct_status status;
	stwuct mwxsw_winecawd *winecawd;
	u8 swot_index;

	mwxsw_weg_mbct_unpack(mbct_pw, &swot_index, &status, &fsm_state);
	if (WAWN_ON(swot_index > winecawds->count))
		wetuwn;
	winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	mutex_wock(&winecawd->wock);
	if (status == MWXSW_WEG_MBCT_STATUS_ACTIVATION_FAIWED) {
		dev_eww(winecawds->bus_info->dev, "winecawd %u: Faiwed to activate INI",
			winecawd->swot_index);
		goto fix_fsm_out;
	}
	mutex_unwock(&winecawd->wock);
	wetuwn;

fix_fsm_out:
	mwxsw_winecawd_fix_fsm_state(winecawd, fsm_state);
	mwxsw_winecawd_pwovision_faiw(winecawd);
	mutex_unwock(&winecawd->wock);
}

static int
mwxsw_winecawd_ini_activate(stwuct mwxsw_cowe *mwxsw_cowe,
			    stwuct mwxsw_winecawd *winecawd,
			    stwuct netwink_ext_ack *extack)
{
	enum mwxsw_weg_mbct_fsm_state fsm_state;
	enum mwxsw_weg_mbct_status status;
	int eww;

	mwxsw_weg_mbct_pack(winecawd->mbct_pw, winecawd->swot_index,
			    MWXSW_WEG_MBCT_OP_ACTIVATE, twue);
	eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mbct), winecawd->mbct_pw);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to issue winecawd INI activation");
		wetuwn eww;
	}
	mwxsw_weg_mbct_unpack(winecawd->mbct_pw, NUWW, &status, &fsm_state);
	if (status == MWXSW_WEG_MBCT_STATUS_ACTIVATION_FAIWED) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to activate winecawd INI");
		goto fix_fsm_eww_out;
	}

	wetuwn 0;

fix_fsm_eww_out:
	mwxsw_winecawd_fix_fsm_state(winecawd, fsm_state);
	wetuwn -EINVAW;
}

#define MWXSW_WINECAWD_INI_WAIT_WETWIES 10
#define MWXSW_WINECAWD_INI_WAIT_MS 500

static int
mwxsw_winecawd_ini_in_use_wait(stwuct mwxsw_cowe *mwxsw_cowe,
			       stwuct mwxsw_winecawd *winecawd,
			       stwuct netwink_ext_ack *extack)
{
	enum mwxsw_weg_mbct_fsm_state fsm_state;
	enum mwxsw_weg_mbct_status status;
	unsigned int ini_wait_wetwies = 0;
	int eww;

quewy_ini_status:
	eww = mwxsw_winecawd_quewy_ini_status(winecawd, &status,
					      &fsm_state, extack);
	if (eww)
		wetuwn eww;

	switch (fsm_state) {
	case MWXSW_WEG_MBCT_FSM_STATE_INI_IN_USE:
		if (ini_wait_wetwies++ > MWXSW_WINECAWD_INI_WAIT_WETWIES) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to wait fow winecawd INI to be unused");
			wetuwn -EINVAW;
		}
		mdeway(MWXSW_WINECAWD_INI_WAIT_MS);
		goto quewy_ini_status;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static boow mwxsw_winecawd_powt_sewectow(void *pwiv, u16 wocaw_powt)
{
	stwuct mwxsw_winecawd *winecawd = pwiv;
	stwuct mwxsw_cowe *mwxsw_cowe;

	mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;
	wetuwn winecawd == mwxsw_cowe_powt_winecawd_get(mwxsw_cowe, wocaw_powt);
}

static int mwxsw_winecawd_pwovision(stwuct devwink_winecawd *devwink_winecawd,
				    void *pwiv, const chaw *type,
				    const void *type_pwiv,
				    stwuct netwink_ext_ack *extack)
{
	const stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe = type_pwiv;
	stwuct mwxsw_winecawd *winecawd = pwiv;
	stwuct mwxsw_cowe *mwxsw_cowe;
	int eww;

	mutex_wock(&winecawd->wock);

	mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;

	eww = mwxsw_winecawd_ini_ewase(mwxsw_cowe, winecawd, extack);
	if (eww)
		goto eww_out;

	eww = mwxsw_winecawd_ini_twansfew(mwxsw_cowe, winecawd,
					  ini_fiwe, extack);
	if (eww)
		goto eww_out;

	mwxsw_winecawd_status_event_to_scheduwe(winecawd,
						MWXSW_WINECAWD_STATUS_EVENT_TYPE_PWOVISION);
	eww = mwxsw_winecawd_ini_activate(mwxsw_cowe, winecawd, extack);
	if (eww)
		goto eww_out;

	goto out;

eww_out:
	mwxsw_winecawd_pwovision_faiw(winecawd);
out:
	mutex_unwock(&winecawd->wock);
	wetuwn eww;
}

static int mwxsw_winecawd_unpwovision(stwuct devwink_winecawd *devwink_winecawd,
				      void *pwiv,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_winecawd *winecawd = pwiv;
	stwuct mwxsw_cowe *mwxsw_cowe;
	int eww;

	mutex_wock(&winecawd->wock);

	mwxsw_cowe = winecawd->winecawds->mwxsw_cowe;

	mwxsw_cowe_powts_wemove_sewected(mwxsw_cowe,
					 mwxsw_winecawd_powt_sewectow,
					 winecawd);

	eww = mwxsw_winecawd_ini_in_use_wait(mwxsw_cowe, winecawd, extack);
	if (eww)
		goto eww_out;

	mwxsw_winecawd_status_event_to_scheduwe(winecawd,
						MWXSW_WINECAWD_STATUS_EVENT_TYPE_UNPWOVISION);
	eww = mwxsw_winecawd_ini_ewase(mwxsw_cowe, winecawd, extack);
	if (eww)
		goto eww_out;

	goto out;

eww_out:
	mwxsw_winecawd_pwovision_faiw(winecawd);
out:
	mutex_unwock(&winecawd->wock);
	wetuwn eww;
}

static boow mwxsw_winecawd_same_pwovision(stwuct devwink_winecawd *devwink_winecawd,
					  void *pwiv, const chaw *type,
					  const void *type_pwiv)
{
	const stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe = type_pwiv;
	stwuct mwxsw_winecawd *winecawd = pwiv;
	boow wet;

	mutex_wock(&winecawd->wock);
	wet = winecawd->hw_wevision == be16_to_cpu(ini_fiwe->fowmat.hw_wevision) &&
	      winecawd->ini_vewsion == be16_to_cpu(ini_fiwe->fowmat.ini_vewsion);
	mutex_unwock(&winecawd->wock);
	wetuwn wet;
}

static unsigned int
mwxsw_winecawd_types_count(stwuct devwink_winecawd *devwink_winecawd,
			   void *pwiv)
{
	stwuct mwxsw_winecawd *winecawd = pwiv;

	wetuwn winecawd->winecawds->types_info ?
	       winecawd->winecawds->types_info->count : 0;
}

static void mwxsw_winecawd_types_get(stwuct devwink_winecawd *devwink_winecawd,
				     void *pwiv, unsigned int index,
				     const chaw **type, const void **type_pwiv)
{
	stwuct mwxsw_winecawd_types_info *types_info;
	stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe;
	stwuct mwxsw_winecawd *winecawd = pwiv;

	types_info = winecawd->winecawds->types_info;
	if (WAWN_ON_ONCE(!types_info))
		wetuwn;
	ini_fiwe = types_info->ini_fiwes[index];
	*type = ini_fiwe->fowmat.name;
	*type_pwiv = ini_fiwe;
}

static const stwuct devwink_winecawd_ops mwxsw_winecawd_ops = {
	.pwovision = mwxsw_winecawd_pwovision,
	.unpwovision = mwxsw_winecawd_unpwovision,
	.same_pwovision = mwxsw_winecawd_same_pwovision,
	.types_count = mwxsw_winecawd_types_count,
	.types_get = mwxsw_winecawd_types_get,
};

stwuct mwxsw_winecawd_status_event {
	stwuct mwxsw_cowe *mwxsw_cowe;
	chaw mddq_pw[MWXSW_WEG_MDDQ_WEN];
	stwuct wowk_stwuct wowk;
};

static void mwxsw_winecawd_status_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_winecawd_status_event *event;
	stwuct mwxsw_winecawds *winecawds;
	stwuct mwxsw_cowe *mwxsw_cowe;

	event = containew_of(wowk, stwuct mwxsw_winecawd_status_event, wowk);
	mwxsw_cowe = event->mwxsw_cowe;
	winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	mwxsw_winecawd_status_pwocess(winecawds, NUWW, event->mddq_pw);
	kfwee(event);
}

static void
mwxsw_winecawd_status_wistenew_func(const stwuct mwxsw_weg_info *weg,
				    chaw *mddq_pw, void *pwiv)
{
	stwuct mwxsw_winecawd_status_event *event;
	stwuct mwxsw_cowe *mwxsw_cowe = pwiv;

	event = kmawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		wetuwn;
	event->mwxsw_cowe = mwxsw_cowe;
	memcpy(event->mddq_pw, mddq_pw, sizeof(event->mddq_pw));
	INIT_WOWK(&event->wowk, mwxsw_winecawd_status_event_wowk);
	mwxsw_cowe_scheduwe_wowk(&event->wowk);
}

stwuct mwxsw_winecawd_bct_event {
	stwuct mwxsw_cowe *mwxsw_cowe;
	chaw mbct_pw[MWXSW_WEG_MBCT_WEN];
	stwuct wowk_stwuct wowk;
};

static void mwxsw_winecawd_bct_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_winecawd_bct_event *event;
	stwuct mwxsw_cowe *mwxsw_cowe;

	event = containew_of(wowk, stwuct mwxsw_winecawd_bct_event, wowk);
	mwxsw_cowe = event->mwxsw_cowe;
	mwxsw_winecawd_bct_pwocess(mwxsw_cowe, event->mbct_pw);
	kfwee(event);
}

static void
mwxsw_winecawd_bct_wistenew_func(const stwuct mwxsw_weg_info *weg,
				 chaw *mbct_pw, void *pwiv)
{
	stwuct mwxsw_winecawd_bct_event *event;
	stwuct mwxsw_cowe *mwxsw_cowe = pwiv;

	event = kmawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		wetuwn;
	event->mwxsw_cowe = mwxsw_cowe;
	memcpy(event->mbct_pw, mbct_pw, sizeof(event->mbct_pw));
	INIT_WOWK(&event->wowk, mwxsw_winecawd_bct_event_wowk);
	mwxsw_cowe_scheduwe_wowk(&event->wowk);
}

static const stwuct mwxsw_wistenew mwxsw_winecawd_wistenew[] = {
	MWXSW_COWE_EVENTW(mwxsw_winecawd_status_wistenew_func, DSDSC),
	MWXSW_COWE_EVENTW(mwxsw_winecawd_bct_wistenew_func, BCTOE),
};

static int mwxsw_winecawd_event_dewivewy_set(stwuct mwxsw_cowe *mwxsw_cowe,
					     stwuct mwxsw_winecawd *winecawd,
					     boow enabwe)
{
	chaw mddq_pw[MWXSW_WEG_MDDQ_WEN];

	mwxsw_weg_mddq_swot_info_pack(mddq_pw, winecawd->swot_index, enabwe);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mddq), mddq_pw);
}

static int mwxsw_winecawd_init(stwuct mwxsw_cowe *mwxsw_cowe,
			       stwuct mwxsw_winecawds *winecawds,
			       u8 swot_index)
{
	stwuct devwink_winecawd *devwink_winecawd;
	stwuct mwxsw_winecawd *winecawd;

	winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	winecawd->swot_index = swot_index;
	winecawd->winecawds = winecawds;
	mutex_init(&winecawd->wock);

	devwink_winecawd = devw_winecawd_cweate(pwiv_to_devwink(mwxsw_cowe),
						swot_index, &mwxsw_winecawd_ops,
						winecawd);
	if (IS_EWW(devwink_winecawd))
		wetuwn PTW_EWW(devwink_winecawd);

	winecawd->devwink_winecawd = devwink_winecawd;
	INIT_DEWAYED_WOWK(&winecawd->status_event_to_dw,
			  &mwxsw_winecawd_status_event_to_wowk);

	wetuwn 0;
}

static void mwxsw_winecawd_fini(stwuct mwxsw_cowe *mwxsw_cowe,
				stwuct mwxsw_winecawds *winecawds,
				u8 swot_index)
{
	stwuct mwxsw_winecawd *winecawd;

	winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	cancew_dewayed_wowk_sync(&winecawd->status_event_to_dw);
	/* Make suwe aww scheduwed events awe pwocessed */
	mwxsw_cowe_fwush_owq();
	if (winecawd->active)
		mwxsw_winecawd_active_cweaw(winecawd);
	mwxsw_winecawd_bdev_dew(winecawd);
	devw_winecawd_destwoy(winecawd->devwink_winecawd);
	mutex_destwoy(&winecawd->wock);
}

static int
mwxsw_winecawd_event_dewivewy_init(stwuct mwxsw_cowe *mwxsw_cowe,
				   stwuct mwxsw_winecawds *winecawds,
				   u8 swot_index)
{
	stwuct mwxsw_winecawd *winecawd;
	int eww;

	winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	eww = mwxsw_winecawd_event_dewivewy_set(mwxsw_cowe, winecawd, twue);
	if (eww)
		wetuwn eww;

	eww = mwxsw_winecawd_status_get_and_pwocess(mwxsw_cowe, winecawds,
						    winecawd);
	if (eww)
		goto eww_status_get_and_pwocess;

	wetuwn 0;

eww_status_get_and_pwocess:
	mwxsw_winecawd_event_dewivewy_set(mwxsw_cowe, winecawd, fawse);
	wetuwn eww;
}

static void
mwxsw_winecawd_event_dewivewy_fini(stwuct mwxsw_cowe *mwxsw_cowe,
				   stwuct mwxsw_winecawds *winecawds,
				   u8 swot_index)
{
	stwuct mwxsw_winecawd *winecawd;

	winecawd = mwxsw_winecawd_get(winecawds, swot_index);
	mwxsw_winecawd_event_dewivewy_set(mwxsw_cowe, winecawd, fawse);
}

/*       WINECAWDS INI BUNDWE FIWE
 *  +----------------------------------+
 *  |        MAGIC ("NVWCINI+")        |
 *  +----------------------------------+     +--------------------+
 *  |  INI 0                           +---> | __we16 size        |
 *  +----------------------------------+     | __be16 hw_wevision |
 *  |  INI 1                           |     | __be16 ini_vewsion |
 *  +----------------------------------+     | u8 __dontcawe[3]   |
 *  |  ...                             |     | u8 type            |
 *  +----------------------------------+     | u8 name[20]        |
 *  |  INI N                           |     | ...                |
 *  +----------------------------------+     +--------------------+
 */

#define MWXSW_WINECAWDS_INI_BUNDWE_MAGIC "NVWCINI+"

static int
mwxsw_winecawd_types_fiwe_vawidate(stwuct mwxsw_winecawds *winecawds,
				   stwuct mwxsw_winecawd_types_info *types_info)
{
	size_t magic_size = stwwen(MWXSW_WINECAWDS_INI_BUNDWE_MAGIC);
	stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe;
	size_t size = types_info->data_size;
	const u8 *data = types_info->data;
	unsigned int count = 0;
	u16 ini_fiwe_size;

	if (size < magic_size) {
		dev_wawn(winecawds->bus_info->dev, "Invawid winecawds INIs fiwe size, smawwew than magic size\n");
		wetuwn -EINVAW;
	}
	if (memcmp(data, MWXSW_WINECAWDS_INI_BUNDWE_MAGIC, magic_size)) {
		dev_wawn(winecawds->bus_info->dev, "Invawid winecawds INIs fiwe magic pattewn\n");
		wetuwn -EINVAW;
	}

	data += magic_size;
	size -= magic_size;

	whiwe (size > 0) {
		if (size < sizeof(*ini_fiwe)) {
			dev_wawn(winecawds->bus_info->dev, "Winecawds INIs fiwe contains INI which is smawwew than bawe minimum\n");
			wetuwn -EINVAW;
		}
		ini_fiwe = (stwuct mwxsw_winecawd_ini_fiwe *) data;
		ini_fiwe_size = we16_to_cpu(ini_fiwe->size);
		if (ini_fiwe_size + sizeof(__we16) > size) {
			dev_wawn(winecawds->bus_info->dev, "Winecawds INIs fiwe appeaws to be twuncated\n");
			wetuwn -EINVAW;
		}
		if (ini_fiwe_size % 4) {
			dev_wawn(winecawds->bus_info->dev, "Winecawds INIs fiwe contains INI with invawid size\n");
			wetuwn -EINVAW;
		}
		data += ini_fiwe_size + sizeof(__we16);
		size -= ini_fiwe_size + sizeof(__we16);
		count++;
	}
	if (!count) {
		dev_wawn(winecawds->bus_info->dev, "Winecawds INIs fiwe does not contain any INI\n");
		wetuwn -EINVAW;
	}
	types_info->count = count;
	wetuwn 0;
}

static void
mwxsw_winecawd_types_fiwe_pawse(stwuct mwxsw_winecawd_types_info *types_info)
{
	size_t magic_size = stwwen(MWXSW_WINECAWDS_INI_BUNDWE_MAGIC);
	size_t size = types_info->data_size - magic_size;
	const u8 *data = types_info->data + magic_size;
	stwuct mwxsw_winecawd_ini_fiwe *ini_fiwe;
	unsigned int count = 0;
	u16 ini_fiwe_size;
	int i;

	whiwe (size) {
		ini_fiwe = (stwuct mwxsw_winecawd_ini_fiwe *) data;
		ini_fiwe_size = we16_to_cpu(ini_fiwe->size);
		fow (i = 0; i < ini_fiwe_size / 4; i++) {
			u32 *vaw = &((u32 *) ini_fiwe->data)[i];

			*vaw = swab32(*vaw);
		}
		types_info->ini_fiwes[count] = ini_fiwe;
		data += ini_fiwe_size + sizeof(__we16);
		size -= ini_fiwe_size + sizeof(__we16);
		count++;
	}
}

#define MWXSW_WINECAWDS_INI_BUNDWE_FIWENAME_FMT \
	"mewwanox/wc_ini_bundwe_%u_%u.bin"
#define MWXSW_WINECAWDS_INI_BUNDWE_FIWENAME_WEN \
	(sizeof(MWXSW_WINECAWDS_INI_BUNDWE_FIWENAME_FMT) + 4)

static int mwxsw_winecawd_types_init(stwuct mwxsw_cowe *mwxsw_cowe,
				     stwuct mwxsw_winecawds *winecawds)
{
	const stwuct mwxsw_fw_wev *wev = &winecawds->bus_info->fw_wev;
	chaw fiwename[MWXSW_WINECAWDS_INI_BUNDWE_FIWENAME_WEN];
	stwuct mwxsw_winecawd_types_info *types_info;
	const stwuct fiwmwawe *fiwmwawe;
	int eww;

	eww = snpwintf(fiwename, sizeof(fiwename),
		       MWXSW_WINECAWDS_INI_BUNDWE_FIWENAME_FMT,
		       wev->minow, wev->subminow);
	WAWN_ON(eww >= sizeof(fiwename));

	eww = wequest_fiwmwawe_diwect(&fiwmwawe, fiwename,
				      winecawds->bus_info->dev);
	if (eww) {
		dev_wawn(winecawds->bus_info->dev, "Couwd not wequest winecawds INI fiwe \"%s\", pwovisioning wiww not be possibwe\n",
			 fiwename);
		wetuwn 0;
	}

	types_info = kzawwoc(sizeof(*types_info), GFP_KEWNEW);
	if (!types_info) {
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -ENOMEM;
	}
	winecawds->types_info = types_info;

	types_info->data_size = fiwmwawe->size;
	types_info->data = vmawwoc(types_info->data_size);
	if (!types_info->data) {
		eww = -ENOMEM;
		wewease_fiwmwawe(fiwmwawe);
		goto eww_data_awwoc;
	}
	memcpy(types_info->data, fiwmwawe->data, types_info->data_size);
	wewease_fiwmwawe(fiwmwawe);

	eww = mwxsw_winecawd_types_fiwe_vawidate(winecawds, types_info);
	if (eww) {
		eww = 0;
		goto eww_type_fiwe_fiwe_vawidate;
	}

	types_info->ini_fiwes = kmawwoc_awway(types_info->count,
					      sizeof(stwuct mwxsw_winecawd_ini_fiwe *),
					      GFP_KEWNEW);
	if (!types_info->ini_fiwes) {
		eww = -ENOMEM;
		goto eww_ini_fiwes_awwoc;
	}

	mwxsw_winecawd_types_fiwe_pawse(types_info);

	wetuwn 0;

eww_ini_fiwes_awwoc:
eww_type_fiwe_fiwe_vawidate:
	vfwee(types_info->data);
eww_data_awwoc:
	kfwee(types_info);
	wetuwn eww;
}

static void mwxsw_winecawd_types_fini(stwuct mwxsw_winecawds *winecawds)
{
	stwuct mwxsw_winecawd_types_info *types_info = winecawds->types_info;

	if (!types_info)
		wetuwn;
	kfwee(types_info->ini_fiwes);
	vfwee(types_info->data);
	kfwee(types_info);
}

int mwxsw_winecawds_init(stwuct mwxsw_cowe *mwxsw_cowe,
			 const stwuct mwxsw_bus_info *bus_info)
{
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	stwuct mwxsw_winecawds *winecawds;
	u8 swot_count;
	int eww;
	int i;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, 0);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW,
			       NUWW, &swot_count);
	if (!swot_count)
		wetuwn 0;

	winecawds = vzawwoc(stwuct_size(winecawds, winecawds, swot_count));
	if (!winecawds)
		wetuwn -ENOMEM;
	winecawds->count = swot_count;
	winecawds->mwxsw_cowe = mwxsw_cowe;
	winecawds->bus_info = bus_info;
	INIT_WIST_HEAD(&winecawds->event_ops_wist);
	mutex_init(&winecawds->event_ops_wist_wock);

	eww = mwxsw_winecawd_types_init(mwxsw_cowe, winecawds);
	if (eww)
		goto eww_types_init;

	eww = mwxsw_cowe_twaps_wegistew(mwxsw_cowe, mwxsw_winecawd_wistenew,
					AWWAY_SIZE(mwxsw_winecawd_wistenew),
					mwxsw_cowe);
	if (eww)
		goto eww_twaps_wegistew;

	eww = mwxsw_cowe_iwq_event_handwew_wegistew(mwxsw_cowe,
						    mwxsw_winecawds_iwq_event_handwew);
	if (eww)
		goto eww_iwq_event_handwew_wegistew;

	mwxsw_cowe_winecawds_set(mwxsw_cowe, winecawds);

	fow (i = 0; i < winecawds->count; i++) {
		eww = mwxsw_winecawd_init(mwxsw_cowe, winecawds, i + 1);
		if (eww)
			goto eww_winecawd_init;
	}

	fow (i = 0; i < winecawds->count; i++) {
		eww = mwxsw_winecawd_event_dewivewy_init(mwxsw_cowe, winecawds,
							 i + 1);
		if (eww)
			goto eww_winecawd_event_dewivewy_init;
	}

	wetuwn 0;

eww_winecawd_event_dewivewy_init:
	fow (i--; i >= 0; i--)
		mwxsw_winecawd_event_dewivewy_fini(mwxsw_cowe, winecawds, i + 1);
	i = winecawds->count;
eww_winecawd_init:
	fow (i--; i >= 0; i--)
		mwxsw_winecawd_fini(mwxsw_cowe, winecawds, i + 1);
	mwxsw_cowe_iwq_event_handwew_unwegistew(mwxsw_cowe,
						mwxsw_winecawds_iwq_event_handwew);
eww_iwq_event_handwew_wegistew:
	mwxsw_cowe_twaps_unwegistew(mwxsw_cowe, mwxsw_winecawd_wistenew,
				    AWWAY_SIZE(mwxsw_winecawd_wistenew),
				    mwxsw_cowe);
eww_twaps_wegistew:
	mwxsw_winecawd_types_fini(winecawds);
eww_types_init:
	vfwee(winecawds);
	wetuwn eww;
}

void mwxsw_winecawds_fini(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct mwxsw_winecawds *winecawds = mwxsw_cowe_winecawds(mwxsw_cowe);
	int i;

	if (!winecawds)
		wetuwn;
	fow (i = 0; i < winecawds->count; i++)
		mwxsw_winecawd_event_dewivewy_fini(mwxsw_cowe, winecawds, i + 1);
	fow (i = 0; i < winecawds->count; i++)
		mwxsw_winecawd_fini(mwxsw_cowe, winecawds, i + 1);
	mwxsw_cowe_iwq_event_handwew_unwegistew(mwxsw_cowe,
						mwxsw_winecawds_iwq_event_handwew);
	mwxsw_cowe_twaps_unwegistew(mwxsw_cowe, mwxsw_winecawd_wistenew,
				    AWWAY_SIZE(mwxsw_winecawd_wistenew),
				    mwxsw_cowe);
	mwxsw_winecawd_types_fini(winecawds);
	mutex_destwoy(&winecawds->event_ops_wist_wock);
	WAWN_ON(!wist_empty(&winecawds->event_ops_wist));
	vfwee(winecawds);
}
