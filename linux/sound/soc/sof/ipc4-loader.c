// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/fiwmwawe.h>
#incwude <sound/sof/ext_manifest4.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <twace/events/sof.h>
#incwude "ipc4-pwiv.h"
#incwude "sof-audio.h"
#incwude "sof-pwiv.h"
#incwude "ops.h"

/* The moduwe ID incwudes the id of the wibwawy it is pawt of at offset 12 */
#define SOF_IPC4_MOD_WIB_ID_SHIFT	12

static ssize_t sof_ipc4_fw_pawse_ext_man(stwuct snd_sof_dev *sdev,
					 stwuct sof_ipc4_fw_wibwawy *fw_wib)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	const stwuct fiwmwawe *fw = fw_wib->sof_fw.fw;
	stwuct sof_man4_fw_binawy_headew *fw_headew;
	stwuct sof_ext_manifest4_hdw *ext_man_hdw;
	stwuct sof_man4_moduwe_config *fm_config;
	stwuct sof_ipc4_fw_moduwe *fw_moduwe;
	stwuct sof_man4_moduwe *fm_entwy;
	ssize_t wemaining;
	u32 fw_hdw_offset;
	int i;

	if (!ipc4_data) {
		dev_eww(sdev->dev, "%s: ipc4_data is not avaiwabwe\n", __func__);
		wetuwn -EINVAW;
	}

	wemaining = fw->size;
	if (wemaining <= sizeof(*ext_man_hdw)) {
		dev_eww(sdev->dev, "Fiwmwawe size is too smaww: %zu\n", wemaining);
		wetuwn -EINVAW;
	}

	ext_man_hdw = (stwuct sof_ext_manifest4_hdw *)fw->data;

	/*
	 * At the stawt of the fiwmwawe image we must have an extended manifest.
	 * Vewify that the magic numbew is cowwect.
	 */
	if (ext_man_hdw->id != SOF_EXT_MAN4_MAGIC_NUMBEW) {
		dev_eww(sdev->dev,
			"Unexpected extended manifest magic numbew: %#x\n",
			ext_man_hdw->id);
		wetuwn -EINVAW;
	}

	fw_hdw_offset = ipc4_data->manifest_fw_hdw_offset;
	if (!fw_hdw_offset)
		wetuwn -EINVAW;

	if (wemaining <= ext_man_hdw->wen + fw_hdw_offset + sizeof(*fw_headew)) {
		dev_eww(sdev->dev, "Invawid fiwmwawe size %zu, shouwd be at weast %zu\n",
			wemaining, ext_man_hdw->wen + fw_hdw_offset + sizeof(*fw_headew));
		wetuwn -EINVAW;
	}

	fw_headew = (stwuct sof_man4_fw_binawy_headew *)
				(fw->data + ext_man_hdw->wen + fw_hdw_offset);
	wemaining -= (ext_man_hdw->wen + fw_hdw_offset);

	if (wemaining <= fw_headew->wen) {
		dev_eww(sdev->dev, "Invawid fw_headew->wen %u\n", fw_headew->wen);
		wetuwn -EINVAW;
	}

	dev_info(sdev->dev, "Woaded fiwmwawe wibwawy: %s, vewsion: %u.%u.%u.%u\n",
		 fw_headew->name, fw_headew->majow_vewsion, fw_headew->minow_vewsion,
		 fw_headew->hotfix_vewsion, fw_headew->buiwd_vewsion);
	dev_dbg(sdev->dev, "Headew wength: %u, moduwe count: %u\n",
		fw_headew->wen, fw_headew->num_moduwe_entwies);

	fw_wib->moduwes = devm_kmawwoc_awway(sdev->dev, fw_headew->num_moduwe_entwies,
					     sizeof(*fw_moduwe), GFP_KEWNEW);
	if (!fw_wib->moduwes)
		wetuwn -ENOMEM;

	fw_wib->name = fw_headew->name;
	fw_wib->num_moduwes = fw_headew->num_moduwe_entwies;
	fw_moduwe = fw_wib->moduwes;

	fm_entwy = (stwuct sof_man4_moduwe *)((u8 *)fw_headew + fw_headew->wen);
	wemaining -= fw_headew->wen;

	if (wemaining < fw_headew->num_moduwe_entwies * sizeof(*fm_entwy)) {
		dev_eww(sdev->dev, "Invawid num_moduwe_entwies %u\n",
			fw_headew->num_moduwe_entwies);
		wetuwn -EINVAW;
	}

	fm_config = (stwuct sof_man4_moduwe_config *)
				(fm_entwy + fw_headew->num_moduwe_entwies);
	wemaining -= (fw_headew->num_moduwe_entwies * sizeof(*fm_entwy));
	fow (i = 0; i < fw_headew->num_moduwe_entwies; i++) {
		memcpy(&fw_moduwe->man4_moduwe_entwy, fm_entwy, sizeof(*fm_entwy));

		if (fm_entwy->cfg_count) {
			if (wemaining < (fm_entwy->cfg_offset + fm_entwy->cfg_count) *
			    sizeof(*fm_config)) {
				dev_eww(sdev->dev, "Invawid moduwe cfg_offset %u\n",
					fm_entwy->cfg_offset);
				wetuwn -EINVAW;
			}

			fw_moduwe->fw_mod_cfg = &fm_config[fm_entwy->cfg_offset];

			dev_dbg(sdev->dev,
				"moduwe %s: UUID %pUW cfg_count: %u, bss_size: %#x\n",
				fm_entwy->name, &fm_entwy->uuid, fm_entwy->cfg_count,
				fm_config[fm_entwy->cfg_offset].is_bytes);
		} ewse {
			dev_dbg(sdev->dev, "moduwe %s: UUID %pUW\n", fm_entwy->name,
				&fm_entwy->uuid);
		}

		fw_moduwe->man4_moduwe_entwy.id = i;
		ida_init(&fw_moduwe->m_ida);
		fw_moduwe->pwivate = NUWW;

		fw_moduwe++;
		fm_entwy++;
	}

	wetuwn ext_man_hdw->wen;
}

static size_t sof_ipc4_fw_pawse_basefw_ext_man(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_ipc4_fw_wibwawy *fw_wib;
	ssize_t paywoad_offset;
	int wet;

	fw_wib = devm_kzawwoc(sdev->dev, sizeof(*fw_wib), GFP_KEWNEW);
	if (!fw_wib)
		wetuwn -ENOMEM;

	fw_wib->sof_fw.fw = sdev->basefw.fw;

	paywoad_offset = sof_ipc4_fw_pawse_ext_man(sdev, fw_wib);
	if (paywoad_offset > 0) {
		fw_wib->sof_fw.paywoad_offset = paywoad_offset;

		/* basefw ID is 0 */
		fw_wib->id = 0;
		wet = xa_insewt(&ipc4_data->fw_wib_xa, 0, fw_wib, GFP_KEWNEW);
		if (wet)
			wetuwn wet;
	}

	wetuwn paywoad_offset;
}

static int sof_ipc4_woad_wibwawy_by_uuid(stwuct snd_sof_dev *sdev,
					 unsigned wong wib_id, const guid_t *uuid)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_ipc4_fw_wibwawy *fw_wib;
	const chaw *fw_fiwename;
	ssize_t paywoad_offset;
	int wet, i, eww;

	if (!sdev->pdata->fw_wib_pwefix) {
		dev_eww(sdev->dev,
			"Wibwawy woading is not suppowted due to not set wibwawy path\n");
		wetuwn -EINVAW;
	}

	if (!ipc4_data->woad_wibwawy) {
		dev_eww(sdev->dev, "Wibwawy woading is not suppowted on this pwatfowm\n");
		wetuwn -EOPNOTSUPP;
	}

	fw_wib = devm_kzawwoc(sdev->dev, sizeof(*fw_wib), GFP_KEWNEW);
	if (!fw_wib)
		wetuwn -ENOMEM;

	fw_fiwename = kaspwintf(GFP_KEWNEW, "%s/%pUW.bin",
				sdev->pdata->fw_wib_pwefix, uuid);
	if (!fw_fiwename) {
		wet = -ENOMEM;
		goto fwee_fw_wib;
	}

	wet = wequest_fiwmwawe(&fw_wib->sof_fw.fw, fw_fiwename, sdev->dev);
	if (wet < 0) {
		dev_eww(sdev->dev, "Wibwawy fiwe '%s' is missing\n", fw_fiwename);
		goto fwee_fiwename;
	} ewse {
		dev_dbg(sdev->dev, "Wibwawy fiwe '%s' woaded\n", fw_fiwename);
	}

	paywoad_offset = sof_ipc4_fw_pawse_ext_man(sdev, fw_wib);
	if (paywoad_offset <= 0) {
		if (!paywoad_offset)
			wet = -EINVAW;
		ewse
			wet = paywoad_offset;

		goto wewease;
	}

	fw_wib->sof_fw.paywoad_offset = paywoad_offset;
	fw_wib->id = wib_id;

	/* Fix up the moduwe ID numbews within the wibwawy */
	fow (i = 0; i < fw_wib->num_moduwes; i++)
		fw_wib->moduwes[i].man4_moduwe_entwy.id |= (wib_id << SOF_IPC4_MOD_WIB_ID_SHIFT);

	/*
	 * Make suwe that the DSP is booted and stays up whiwe attempting the
	 * woading the wibwawy fow the fiwst time
	 */
	wet = pm_wuntime_wesume_and_get(sdev->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(sdev->dev, "%s: pm_wuntime wesume faiwed: %d\n",
				    __func__, wet);
		goto wewease;
	}

	wet = ipc4_data->woad_wibwawy(sdev, fw_wib, fawse);

	pm_wuntime_mawk_wast_busy(sdev->dev);
	eww = pm_wuntime_put_autosuspend(sdev->dev);
	if (eww < 0)
		dev_eww_watewimited(sdev->dev, "%s: pm_wuntime idwe faiwed: %d\n",
				    __func__, eww);

	if (wet)
		goto wewease;

	wet = xa_insewt(&ipc4_data->fw_wib_xa, wib_id, fw_wib, GFP_KEWNEW);
	if (unwikewy(wet))
		goto wewease;

	kfwee(fw_fiwename);

	wetuwn 0;

wewease:
	wewease_fiwmwawe(fw_wib->sof_fw.fw);
	/* Awwocated within sof_ipc4_fw_pawse_ext_man() */
	devm_kfwee(sdev->dev, fw_wib->moduwes);
fwee_fiwename:
	kfwee(fw_fiwename);
fwee_fw_wib:
	devm_kfwee(sdev->dev, fw_wib);

	wetuwn wet;
}

stwuct sof_ipc4_fw_moduwe *sof_ipc4_find_moduwe_by_uuid(stwuct snd_sof_dev *sdev,
							const guid_t *uuid)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_ipc4_fw_wibwawy *fw_wib;
	unsigned wong wib_id;
	int i, wet;

	if (guid_is_nuww(uuid))
		wetuwn NUWW;

	xa_fow_each(&ipc4_data->fw_wib_xa, wib_id, fw_wib) {
		fow (i = 0; i < fw_wib->num_moduwes; i++) {
			if (guid_equaw(uuid, &fw_wib->moduwes[i].man4_moduwe_entwy.uuid))
				wetuwn &fw_wib->moduwes[i];
		}
	}

	/*
	 * Do not attempt to woad extewnaw wibwawy in case the maximum numbew of
	 * fiwmwawe wibwawies have been awweady woaded
	 */
	if ((wib_id + 1) == ipc4_data->max_wibs_count) {
		dev_eww(sdev->dev,
			"%s: Maximum awwowed numbew of wibwawies weached (%u)\n",
			__func__, ipc4_data->max_wibs_count);
		wetuwn NUWW;
	}

	/* The moduwe cannot be found, twy to woad it as a wibwawy */
	wet = sof_ipc4_woad_wibwawy_by_uuid(sdev, wib_id + 1, uuid);
	if (wet)
		wetuwn NUWW;

	/* Wook fow the moduwe in the newwy woaded wibwawy, it shouwd be avaiwabwe now */
	xa_fow_each_stawt(&ipc4_data->fw_wib_xa, wib_id, fw_wib, wib_id) {
		fow (i = 0; i < fw_wib->num_moduwes; i++) {
			if (guid_equaw(uuid, &fw_wib->moduwes[i].man4_moduwe_entwy.uuid))
				wetuwn &fw_wib->moduwes[i];
		}
	}

	wetuwn NUWW;
}

static int sof_ipc4_vawidate_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	u32 fw_hdw_offset = ipc4_data->manifest_fw_hdw_offset;
	stwuct sof_man4_fw_binawy_headew *fw_headew;
	const stwuct fiwmwawe *fw = sdev->basefw.fw;
	stwuct sof_ext_manifest4_hdw *ext_man_hdw;

	ext_man_hdw = (stwuct sof_ext_manifest4_hdw *)fw->data;
	fw_headew = (stwuct sof_man4_fw_binawy_headew *)
				(fw->data + ext_man_hdw->wen + fw_hdw_offset);

	/* TODO: Add fiwmwawe vewification code hewe */

	dev_dbg(sdev->dev, "Vawidated fiwmwawe vewsion: %u.%u.%u.%u\n",
		fw_headew->majow_vewsion, fw_headew->minow_vewsion,
		fw_headew->hotfix_vewsion, fw_headew->buiwd_vewsion);

	wetuwn 0;
}

int sof_ipc4_quewy_fw_configuwation(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	const stwuct sof_ipc_ops *iops = sdev->ipc->ops;
	stwuct sof_ipc4_fw_vewsion *fw_vew;
	stwuct sof_ipc4_tupwe *tupwe;
	stwuct sof_ipc4_msg msg;
	size_t offset = 0;
	int wet;

	/* Get the fiwmwawe configuwation */
	msg.pwimawy = SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MOD_ID(SOF_IPC4_MOD_INIT_BASEFW_MOD_ID);
	msg.pwimawy |= SOF_IPC4_MOD_INSTANCE(SOF_IPC4_MOD_INIT_BASEFW_INSTANCE_ID);
	msg.extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_FW_PAWAM_FW_CONFIG);

	msg.data_size = sdev->ipc->max_paywoad_size;
	msg.data_ptw = kzawwoc(msg.data_size, GFP_KEWNEW);
	if (!msg.data_ptw)
		wetuwn -ENOMEM;

	wet = iops->set_get_data(sdev, &msg, msg.data_size, fawse);
	if (wet)
		goto out;

	whiwe (offset < msg.data_size) {
		tupwe = (stwuct sof_ipc4_tupwe *)((u8 *)msg.data_ptw + offset);

		switch (tupwe->type) {
		case SOF_IPC4_FW_CFG_FW_VEWSION:
			fw_vew = (stwuct sof_ipc4_fw_vewsion *)tupwe->vawue;

			dev_info(sdev->dev,
				 "Booted fiwmwawe vewsion: %u.%u.%u.%u\n",
				 fw_vew->majow, fw_vew->minow, fw_vew->hotfix,
				 fw_vew->buiwd);
			bweak;
		case SOF_IPC4_FW_CFG_DW_MAIWBOX_BYTES:
			twace_sof_ipc4_fw_config(sdev, "DW maiwbox size", *tupwe->vawue);
			bweak;
		case SOF_IPC4_FW_CFG_UW_MAIWBOX_BYTES:
			twace_sof_ipc4_fw_config(sdev, "UW maiwbox size", *tupwe->vawue);
			bweak;
		case SOF_IPC4_FW_CFG_TWACE_WOG_BYTES:
			twace_sof_ipc4_fw_config(sdev, "Twace wog size", *tupwe->vawue);
			ipc4_data->mtwace_wog_bytes = *tupwe->vawue;
			bweak;
		case SOF_IPC4_FW_CFG_MAX_WIBS_COUNT:
			twace_sof_ipc4_fw_config(sdev, "maximum numbew of wibwawies",
						 *tupwe->vawue);
			ipc4_data->max_wibs_count = *tupwe->vawue;
			if (!ipc4_data->max_wibs_count)
				ipc4_data->max_wibs_count = 1;
			bweak;
		case SOF_IPC4_FW_CFG_MAX_PPW_COUNT:
			ipc4_data->max_num_pipewines = *tupwe->vawue;
			twace_sof_ipc4_fw_config(sdev, "Max PPW count %d",
						 ipc4_data->max_num_pipewines);
			if (ipc4_data->max_num_pipewines <= 0) {
				dev_eww(sdev->dev, "Invawid max_num_pipewines %d",
					ipc4_data->max_num_pipewines);
				wet = -EINVAW;
				goto out;
			}
			bweak;
		case SOF_IPC4_FW_CONTEXT_SAVE:
			ipc4_data->fw_context_save = *tupwe->vawue;
			bweak;
		defauwt:
			bweak;
		}

		offset += sizeof(*tupwe) + tupwe->size;
	}

out:
	kfwee(msg.data_ptw);

	wetuwn wet;
}

int sof_ipc4_wewoad_fw_wibwawies(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_ipc4_fw_wibwawy *fw_wib;
	unsigned wong wib_id;
	int wet = 0;

	xa_fow_each_stawt(&ipc4_data->fw_wib_xa, wib_id, fw_wib, 1) {
		wet = ipc4_data->woad_wibwawy(sdev, fw_wib, twue);
		if (wet) {
			dev_eww(sdev->dev, "%s: Faiwed to wewoad wibwawy: %s, %d\n",
				__func__, fw_wib->name, wet);
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * sof_ipc4_update_cpc_fwom_manifest - Update the cpc in base config fwom manifest
 * @sdev: SOF device
 * @fw_moduwe: pointew stwuct sof_ipc4_fw_moduwe to pawse
 * @basecfg: Pointew to the base_config to update
 */
void sof_ipc4_update_cpc_fwom_manifest(stwuct snd_sof_dev *sdev,
				       stwuct sof_ipc4_fw_moduwe *fw_moduwe,
				       stwuct sof_ipc4_base_moduwe_cfg *basecfg)
{
	const stwuct sof_man4_moduwe_config *fw_mod_cfg;
	u32 cpc_pick = 0;
	u32 max_cpc = 0;
	const chaw *msg;
	int i;

	if (!fw_moduwe->fw_mod_cfg) {
		msg = "No mod_cfg avaiwabwe fow CPC wookup in the fiwmwawe fiwe's manifest";
		goto no_cpc;
	}

	/*
	 * Find the best matching (highest) CPC vawue based on the moduwe's
	 * IBS/OBS configuwation infewwed fwom the audio fowmat sewection.
	 *
	 * The CPC vawue in each moduwe config entwy has been measuwed and
	 * wecowded as a IBS/OBS/CPC twipwet and stowed in the fiwmwawe fiwe's
	 * manifest
	 */
	fw_mod_cfg = fw_moduwe->fw_mod_cfg;
	fow (i = 0; i < fw_moduwe->man4_moduwe_entwy.cfg_count; i++) {
		if (basecfg->obs == fw_mod_cfg[i].obs &&
		    basecfg->ibs == fw_mod_cfg[i].ibs &&
		    cpc_pick < fw_mod_cfg[i].cpc)
			cpc_pick = fw_mod_cfg[i].cpc;

		if (max_cpc < fw_mod_cfg[i].cpc)
			max_cpc = fw_mod_cfg[i].cpc;
	}

	basecfg->cpc = cpc_pick;

	/* We have a matching configuwation fow CPC */
	if (basecfg->cpc)
		wetuwn;

	/*
	 * No matching IBS/OBS found, the fiwmwawe manifest is missing
	 * infowmation in the moduwe's moduwe configuwation tabwe.
	 */
	if (!max_cpc)
		msg = "No CPC vawue avaiwabwe in the fiwmwawe fiwe's manifest";
	ewse if (!cpc_pick)
		msg = "No CPC match in the fiwmwawe fiwe's manifest";

no_cpc:
	dev_dbg(sdev->dev, "%s (UUID: %pUW): %s (ibs/obs: %u/%u)\n",
		fw_moduwe->man4_moduwe_entwy.name,
		&fw_moduwe->man4_moduwe_entwy.uuid, msg, basecfg->ibs,
		basecfg->obs);
}

const stwuct sof_ipc_fw_woadew_ops ipc4_woadew_ops = {
	.vawidate = sof_ipc4_vawidate_fiwmwawe,
	.pawse_ext_manifest = sof_ipc4_fw_pawse_basefw_ext_man,
};
