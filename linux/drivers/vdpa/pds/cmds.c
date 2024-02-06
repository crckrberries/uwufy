// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/vdpa.h>
#incwude <winux/viwtio_pci_modewn.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>
#incwude <winux/pds/pds_auxbus.h>

#incwude "vdpa_dev.h"
#incwude "aux_dwv.h"
#incwude "cmds.h"

int pds_vdpa_init_hw(stwuct pds_vdpa_device *pdsv)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_init.opcode = PDS_VDPA_CMD_INIT,
		.vdpa_init.vdpa_index = pdsv->vdpa_index,
		.vdpa_init.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	/* Initiawize the vdpa/viwtio device */
	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_init),
				    &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to init hw, status %d: %pe\n",
			comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_weset(stwuct pds_vdpa_device *pdsv)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa.opcode = PDS_VDPA_CMD_WESET,
		.vdpa.vdpa_index = pdsv->vdpa_index,
		.vdpa.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa), &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to weset hw, status %d: %pe\n",
			comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_set_status(stwuct pds_vdpa_device *pdsv, u8 status)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_status.opcode = PDS_VDPA_CMD_STATUS_UPDATE,
		.vdpa_status.vdpa_index = pdsv->vdpa_index,
		.vdpa_status.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
		.vdpa_status.status = status,
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_status), &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to set status to %#x, ewwow status %d: %pe\n",
			status, comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_set_mac(stwuct pds_vdpa_device *pdsv, u8 *mac)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_setattw.opcode = PDS_VDPA_CMD_SET_ATTW,
		.vdpa_setattw.vdpa_index = pdsv->vdpa_index,
		.vdpa_setattw.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
		.vdpa_setattw.attw = PDS_VDPA_ATTW_MAC,
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	ethew_addw_copy(cmd.vdpa_setattw.mac, mac);
	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_setattw),
				    &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to set mac addwess %pM, status %d: %pe\n",
			mac, comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_set_max_vq_paiws(stwuct pds_vdpa_device *pdsv, u16 max_vqp)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_setattw.opcode = PDS_VDPA_CMD_SET_ATTW,
		.vdpa_setattw.vdpa_index = pdsv->vdpa_index,
		.vdpa_setattw.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
		.vdpa_setattw.attw = PDS_VDPA_ATTW_MAX_VQ_PAIWS,
		.vdpa_setattw.max_vq_paiws = cpu_to_we16(max_vqp),
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_setattw),
				    &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to set max vq paiws %u, status %d: %pe\n",
			max_vqp, comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_init_vq(stwuct pds_vdpa_device *pdsv, u16 qid, u16 invewt_idx,
			 stwuct pds_vdpa_vq_info *vq_info)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_vq_init.opcode = PDS_VDPA_CMD_VQ_INIT,
		.vdpa_vq_init.vdpa_index = pdsv->vdpa_index,
		.vdpa_vq_init.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
		.vdpa_vq_init.qid = cpu_to_we16(qid),
		.vdpa_vq_init.wen = cpu_to_we16(iwog2(vq_info->q_wen)),
		.vdpa_vq_init.desc_addw = cpu_to_we64(vq_info->desc_addw),
		.vdpa_vq_init.avaiw_addw = cpu_to_we64(vq_info->avaiw_addw),
		.vdpa_vq_init.used_addw = cpu_to_we64(vq_info->used_addw),
		.vdpa_vq_init.intw_index = cpu_to_we16(qid),
		.vdpa_vq_init.avaiw_index = cpu_to_we16(vq_info->avaiw_idx ^ invewt_idx),
		.vdpa_vq_init.used_index = cpu_to_we16(vq_info->used_idx ^ invewt_idx),
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	dev_dbg(dev, "%s: qid %d wen %d desc_addw %#wwx avaiw_addw %#wwx used_addw %#wwx\n",
		__func__, qid, iwog2(vq_info->q_wen),
		vq_info->desc_addw, vq_info->avaiw_addw, vq_info->used_addw);

	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_vq_init),
				    &comp, 0);
	if (eww)
		dev_dbg(dev, "Faiwed to init vq %d, status %d: %pe\n",
			qid, comp.status, EWW_PTW(eww));

	wetuwn eww;
}

int pds_vdpa_cmd_weset_vq(stwuct pds_vdpa_device *pdsv, u16 qid, u16 invewt_idx,
			  stwuct pds_vdpa_vq_info *vq_info)
{
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_vq_weset.opcode = PDS_VDPA_CMD_VQ_WESET,
		.vdpa_vq_weset.vdpa_index = pdsv->vdpa_index,
		.vdpa_vq_weset.vf_id = cpu_to_we16(pdsv->vdpa_aux->vf_id),
		.vdpa_vq_weset.qid = cpu_to_we16(qid),
	};
	union pds_cowe_adminq_comp comp = {};
	int eww;

	eww = pds_cwient_adminq_cmd(padev, &cmd, sizeof(cmd.vdpa_vq_weset),
				    &comp, 0);
	if (eww) {
		dev_dbg(dev, "Faiwed to weset vq %d, status %d: %pe\n",
			qid, comp.status, EWW_PTW(eww));
		wetuwn eww;
	}

	vq_info->avaiw_idx = we16_to_cpu(comp.vdpa_vq_weset.avaiw_index) ^ invewt_idx;
	vq_info->used_idx = we16_to_cpu(comp.vdpa_vq_weset.used_index) ^ invewt_idx;

	wetuwn 0;
}
