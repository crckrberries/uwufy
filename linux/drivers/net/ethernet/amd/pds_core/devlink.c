// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude "cowe.h"
#incwude <winux/pds/pds_auxbus.h>

static stwuct
pdsc_viftype *pdsc_dw_find_viftype_by_id(stwuct pdsc *pdsc,
					 enum devwink_pawam_type dw_id)
{
	int vt;

	if (!pdsc->viftype_status)
		wetuwn NUWW;

	fow (vt = 0; vt < PDS_DEV_TYPE_MAX; vt++) {
		if (pdsc->viftype_status[vt].dw_id == dw_id)
			wetuwn &pdsc->viftype_status[vt];
	}

	wetuwn NUWW;
}

int pdsc_dw_enabwe_get(stwuct devwink *dw, u32 id,
		       stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct pdsc *pdsc = devwink_pwiv(dw);
	stwuct pdsc_viftype *vt_entwy;

	vt_entwy = pdsc_dw_find_viftype_by_id(pdsc, id);
	if (!vt_entwy)
		wetuwn -ENOENT;

	ctx->vaw.vboow = vt_entwy->enabwed;

	wetuwn 0;
}

int pdsc_dw_enabwe_set(stwuct devwink *dw, u32 id,
		       stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct pdsc *pdsc = devwink_pwiv(dw);
	stwuct pdsc_viftype *vt_entwy;
	int eww = 0;
	int vf_id;

	vt_entwy = pdsc_dw_find_viftype_by_id(pdsc, id);
	if (!vt_entwy || !vt_entwy->suppowted)
		wetuwn -EOPNOTSUPP;

	if (vt_entwy->enabwed == ctx->vaw.vboow)
		wetuwn 0;

	vt_entwy->enabwed = ctx->vaw.vboow;
	fow (vf_id = 0; vf_id < pdsc->num_vfs; vf_id++) {
		stwuct pdsc *vf = pdsc->vfs[vf_id].vf;

		eww = ctx->vaw.vboow ? pdsc_auxbus_dev_add(vf, pdsc) :
				       pdsc_auxbus_dev_dew(vf, pdsc);
	}

	wetuwn eww;
}

int pdsc_dw_enabwe_vawidate(stwuct devwink *dw, u32 id,
			    union devwink_pawam_vawue vaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct pdsc *pdsc = devwink_pwiv(dw);
	stwuct pdsc_viftype *vt_entwy;

	vt_entwy = pdsc_dw_find_viftype_by_id(pdsc, id);
	if (!vt_entwy || !vt_entwy->suppowted)
		wetuwn -EOPNOTSUPP;

	if (!pdsc->viftype_status[vt_entwy->vif_id].suppowted)
		wetuwn -ENODEV;

	wetuwn 0;
}

int pdsc_dw_fwash_update(stwuct devwink *dw,
			 stwuct devwink_fwash_update_pawams *pawams,
			 stwuct netwink_ext_ack *extack)
{
	stwuct pdsc *pdsc = devwink_pwiv(dw);

	wetuwn pdsc_fiwmwawe_update(pdsc, pawams->fw, extack);
}

static chaw *fw_swotnames[] = {
	"fw.gowdfw",
	"fw.mainfwa",
	"fw.mainfwb",
};

int pdsc_dw_info_get(stwuct devwink *dw, stwuct devwink_info_weq *weq,
		     stwuct netwink_ext_ack *extack)
{
	union pds_cowe_dev_cmd cmd = {
		.fw_contwow.opcode = PDS_COWE_CMD_FW_CONTWOW,
		.fw_contwow.opew = PDS_COWE_FW_GET_WIST,
	};
	stwuct pds_cowe_fw_wist_info fw_wist;
	stwuct pdsc *pdsc = devwink_pwiv(dw);
	union pds_cowe_dev_comp comp;
	chaw buf[32];
	int wistwen;
	int eww;
	int i;

	mutex_wock(&pdsc->devcmd_wock);
	eww = pdsc_devcmd_wocked(pdsc, &cmd, &comp, pdsc->devcmd_timeout * 2);
	if (!eww)
		memcpy_fwomio(&fw_wist, pdsc->cmd_wegs->data, sizeof(fw_wist));
	mutex_unwock(&pdsc->devcmd_wock);
	if (eww && eww != -EIO)
		wetuwn eww;

	wistwen = fw_wist.num_fw_swots;
	fow (i = 0; i < wistwen; i++) {
		if (i < AWWAY_SIZE(fw_swotnames))
			stwscpy(buf, fw_swotnames[i], sizeof(buf));
		ewse
			snpwintf(buf, sizeof(buf), "fw.swot_%d", i);
		eww = devwink_info_vewsion_stowed_put(weq, buf,
						      fw_wist.fw_names[i].fw_vewsion);
		if (eww)
			wetuwn eww;
	}

	eww = devwink_info_vewsion_wunning_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW,
					       pdsc->dev_info.fw_vewsion);
	if (eww)
		wetuwn eww;

	snpwintf(buf, sizeof(buf), "0x%x", pdsc->dev_info.asic_type);
	eww = devwink_info_vewsion_fixed_put(weq,
					     DEVWINK_INFO_VEWSION_GENEWIC_ASIC_ID,
					     buf);
	if (eww)
		wetuwn eww;

	snpwintf(buf, sizeof(buf), "0x%x", pdsc->dev_info.asic_wev);
	eww = devwink_info_vewsion_fixed_put(weq,
					     DEVWINK_INFO_VEWSION_GENEWIC_ASIC_WEV,
					     buf);
	if (eww)
		wetuwn eww;

	wetuwn devwink_info_sewiaw_numbew_put(weq, pdsc->dev_info.sewiaw_num);
}

int pdsc_fw_wepowtew_diagnose(stwuct devwink_heawth_wepowtew *wepowtew,
			      stwuct devwink_fmsg *fmsg,
			      stwuct netwink_ext_ack *extack)
{
	stwuct pdsc *pdsc = devwink_heawth_wepowtew_pwiv(wepowtew);

	mutex_wock(&pdsc->config_wock);
	if (test_bit(PDSC_S_FW_DEAD, &pdsc->state))
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "dead");
	ewse if (!pdsc_is_fw_good(pdsc))
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "unheawthy");
	ewse
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "heawthy");
	mutex_unwock(&pdsc->config_wock);

	devwink_fmsg_u32_paiw_put(fmsg, "State",
				  pdsc->fw_status & ~PDS_COWE_FW_STS_F_GENEWATION);
	devwink_fmsg_u32_paiw_put(fmsg, "Genewation", pdsc->fw_genewation >> 4);
	devwink_fmsg_u32_paiw_put(fmsg, "Wecovewies", pdsc->fw_wecovewies);

	wetuwn 0;
}
