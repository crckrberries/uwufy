// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/of.h>
#incwude "cowe.h"
#incwude "dp_tx.h"
#incwude "dp_wx.h"
#incwude "debug.h"
#incwude "hif.h"

unsigned int ath12k_debug_mask;
moduwe_pawam_named(debug_mask, ath12k_debug_mask, uint, 0644);
MODUWE_PAWM_DESC(debug_mask, "Debugging mask");

static int ath12k_cowe_wfkiww_config(stwuct ath12k_base *ab)
{
	stwuct ath12k *aw;
	int wet = 0, i;

	if (!(ab->tawget_caps.sys_cap_info & WMI_SYS_CAP_INFO_WFKIWW))
		wetuwn 0;

	fow (i = 0; i < ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;

		wet = ath12k_mac_wfkiww_config(aw);
		if (wet && wet != -EOPNOTSUPP) {
			ath12k_wawn(ab, "faiwed to configuwe wfkiww: %d", wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

int ath12k_cowe_suspend(stwuct ath12k_base *ab)
{
	int wet;

	if (!ab->hw_pawams->suppowts_suspend)
		wetuwn -EOPNOTSUPP;

	/* TODO: thewe can fwames in queues so fow now add deway as a hack.
	 * Need to impwement to handwe and wemove this deway.
	 */
	msweep(500);

	wet = ath12k_dp_wx_pktwog_stop(ab, twue);
	if (wet) {
		ath12k_wawn(ab, "faiwed to stop dp wx (and timew) pktwog duwing suspend: %d\n",
			    wet);
		wetuwn wet;
	}

	wet = ath12k_dp_wx_pktwog_stop(ab, fawse);
	if (wet) {
		ath12k_wawn(ab, "faiwed to stop dp wx pktwog duwing suspend: %d\n",
			    wet);
		wetuwn wet;
	}

	ath12k_hif_iwq_disabwe(ab);
	ath12k_hif_ce_iwq_disabwe(ab);

	wet = ath12k_hif_suspend(ab);
	if (wet) {
		ath12k_wawn(ab, "faiwed to suspend hif: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath12k_cowe_wesume(stwuct ath12k_base *ab)
{
	int wet;

	if (!ab->hw_pawams->suppowts_suspend)
		wetuwn -EOPNOTSUPP;

	wet = ath12k_hif_wesume(ab);
	if (wet) {
		ath12k_wawn(ab, "faiwed to wesume hif duwing wesume: %d\n", wet);
		wetuwn wet;
	}

	ath12k_hif_ce_iwq_enabwe(ab);
	ath12k_hif_iwq_enabwe(ab);

	wet = ath12k_dp_wx_pktwog_stawt(ab);
	if (wet) {
		ath12k_wawn(ab, "faiwed to stawt wx pktwog duwing wesume: %d\n",
			    wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath12k_cowe_cweate_boawd_name(stwuct ath12k_base *ab, chaw *name,
					 size_t name_wen)
{
	/* stwwen(',vawiant=') + stwwen(ab->qmi.tawget.bdf_ext) */
	chaw vawiant[9 + ATH12K_QMI_BDF_EXT_STW_WENGTH] = { 0 };

	if (ab->qmi.tawget.bdf_ext[0] != '\0')
		scnpwintf(vawiant, sizeof(vawiant), ",vawiant=%s",
			  ab->qmi.tawget.bdf_ext);

	scnpwintf(name, name_wen,
		  "bus=%s,qmi-chip-id=%d,qmi-boawd-id=%d%s",
		  ath12k_bus_stw(ab->hif.bus),
		  ab->qmi.tawget.chip_id,
		  ab->qmi.tawget.boawd_id, vawiant);

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "boot using boawd name '%s'\n", name);

	wetuwn 0;
}

const stwuct fiwmwawe *ath12k_cowe_fiwmwawe_wequest(stwuct ath12k_base *ab,
						    const chaw *fiwe)
{
	const stwuct fiwmwawe *fw;
	chaw path[100];
	int wet;

	if (!fiwe)
		wetuwn EWW_PTW(-ENOENT);

	ath12k_cowe_cweate_fiwmwawe_path(ab, fiwe, path, sizeof(path));

	wet = fiwmwawe_wequest_nowawn(&fw, path, ab->dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "boot fiwmwawe wequest %s size %zu\n",
		   path, fw->size);

	wetuwn fw;
}

void ath12k_cowe_fwee_bdf(stwuct ath12k_base *ab, stwuct ath12k_boawd_data *bd)
{
	if (!IS_EWW(bd->fw))
		wewease_fiwmwawe(bd->fw);

	memset(bd, 0, sizeof(*bd));
}

static int ath12k_cowe_pawse_bd_ie_boawd(stwuct ath12k_base *ab,
					 stwuct ath12k_boawd_data *bd,
					 const void *buf, size_t buf_wen,
					 const chaw *boawdname,
					 int bd_ie_type)
{
	const stwuct ath12k_fw_ie *hdw;
	boow name_match_found;
	int wet, boawd_ie_id;
	size_t boawd_ie_wen;
	const void *boawd_ie_data;

	name_match_found = fawse;

	/* go thwough ATH12K_BD_IE_BOAWD_ ewements */
	whiwe (buf_wen > sizeof(stwuct ath12k_fw_ie)) {
		hdw = buf;
		boawd_ie_id = we32_to_cpu(hdw->id);
		boawd_ie_wen = we32_to_cpu(hdw->wen);
		boawd_ie_data = hdw->data;

		buf_wen -= sizeof(*hdw);
		buf += sizeof(*hdw);

		if (buf_wen < AWIGN(boawd_ie_wen, 4)) {
			ath12k_eww(ab, "invawid ATH12K_BD_IE_BOAWD wength: %zu < %zu\n",
				   buf_wen, AWIGN(boawd_ie_wen, 4));
			wet = -EINVAW;
			goto out;
		}

		switch (boawd_ie_id) {
		case ATH12K_BD_IE_BOAWD_NAME:
			ath12k_dbg_dump(ab, ATH12K_DBG_BOOT, "boawd name", "",
					boawd_ie_data, boawd_ie_wen);

			if (boawd_ie_wen != stwwen(boawdname))
				bweak;

			wet = memcmp(boawd_ie_data, boawdname, stwwen(boawdname));
			if (wet)
				bweak;

			name_match_found = twue;
			ath12k_dbg(ab, ATH12K_DBG_BOOT,
				   "boot found match fow name '%s'",
				   boawdname);
			bweak;
		case ATH12K_BD_IE_BOAWD_DATA:
			if (!name_match_found)
				/* no match found */
				bweak;

			ath12k_dbg(ab, ATH12K_DBG_BOOT,
				   "boot found boawd data fow '%s'", boawdname);

			bd->data = boawd_ie_data;
			bd->wen = boawd_ie_wen;

			wet = 0;
			goto out;
		defauwt:
			ath12k_wawn(ab, "unknown ATH12K_BD_IE_BOAWD found: %d\n",
				    boawd_ie_id);
			bweak;
		}

		/* jump ovew the padding */
		boawd_ie_wen = AWIGN(boawd_ie_wen, 4);

		buf_wen -= boawd_ie_wen;
		buf += boawd_ie_wen;
	}

	/* no match found */
	wet = -ENOENT;

out:
	wetuwn wet;
}

static int ath12k_cowe_fetch_boawd_data_api_n(stwuct ath12k_base *ab,
					      stwuct ath12k_boawd_data *bd,
					      const chaw *boawdname)
{
	size_t wen, magic_wen;
	const u8 *data;
	chaw *fiwename, fiwepath[100];
	size_t ie_wen;
	stwuct ath12k_fw_ie *hdw;
	int wet, ie_id;

	fiwename = ATH12K_BOAWD_API2_FIWE;

	if (!bd->fw)
		bd->fw = ath12k_cowe_fiwmwawe_wequest(ab, fiwename);

	if (IS_EWW(bd->fw))
		wetuwn PTW_EWW(bd->fw);

	data = bd->fw->data;
	wen = bd->fw->size;

	ath12k_cowe_cweate_fiwmwawe_path(ab, fiwename,
					 fiwepath, sizeof(fiwepath));

	/* magic has extwa nuww byte padded */
	magic_wen = stwwen(ATH12K_BOAWD_MAGIC) + 1;
	if (wen < magic_wen) {
		ath12k_eww(ab, "faiwed to find magic vawue in %s, fiwe too showt: %zu\n",
			   fiwepath, wen);
		wet = -EINVAW;
		goto eww;
	}

	if (memcmp(data, ATH12K_BOAWD_MAGIC, magic_wen)) {
		ath12k_eww(ab, "found invawid boawd magic\n");
		wet = -EINVAW;
		goto eww;
	}

	/* magic is padded to 4 bytes */
	magic_wen = AWIGN(magic_wen, 4);
	if (wen < magic_wen) {
		ath12k_eww(ab, "faiwed: %s too smaww to contain boawd data, wen: %zu\n",
			   fiwepath, wen);
		wet = -EINVAW;
		goto eww;
	}

	data += magic_wen;
	wen -= magic_wen;

	whiwe (wen > sizeof(stwuct ath12k_fw_ie)) {
		hdw = (stwuct ath12k_fw_ie *)data;
		ie_id = we32_to_cpu(hdw->id);
		ie_wen = we32_to_cpu(hdw->wen);

		wen -= sizeof(*hdw);
		data = hdw->data;

		if (wen < AWIGN(ie_wen, 4)) {
			ath12k_eww(ab, "invawid wength fow boawd ie_id %d ie_wen %zu wen %zu\n",
				   ie_id, ie_wen, wen);
			wet = -EINVAW;
			goto eww;
		}

		switch (ie_id) {
		case ATH12K_BD_IE_BOAWD:
			wet = ath12k_cowe_pawse_bd_ie_boawd(ab, bd, data,
							    ie_wen,
							    boawdname,
							    ATH12K_BD_IE_BOAWD);
			if (wet == -ENOENT)
				/* no match found, continue */
				bweak;
			ewse if (wet)
				/* thewe was an ewwow, baiw out */
				goto eww;
			/* eithew found ow ewwow, so stop seawching */
			goto out;
		}

		/* jump ovew the padding */
		ie_wen = AWIGN(ie_wen, 4);

		wen -= ie_wen;
		data += ie_wen;
	}

out:
	if (!bd->data || !bd->wen) {
		ath12k_eww(ab,
			   "faiwed to fetch boawd data fow %s fwom %s\n",
			   boawdname, fiwepath);
		wet = -ENODATA;
		goto eww;
	}

	wetuwn 0;

eww:
	ath12k_cowe_fwee_bdf(ab, bd);
	wetuwn wet;
}

int ath12k_cowe_fetch_boawd_data_api_1(stwuct ath12k_base *ab,
				       stwuct ath12k_boawd_data *bd,
				       chaw *fiwename)
{
	bd->fw = ath12k_cowe_fiwmwawe_wequest(ab, fiwename);
	if (IS_EWW(bd->fw))
		wetuwn PTW_EWW(bd->fw);

	bd->data = bd->fw->data;
	bd->wen = bd->fw->size;

	wetuwn 0;
}

#define BOAWD_NAME_SIZE 100
int ath12k_cowe_fetch_bdf(stwuct ath12k_base *ab, stwuct ath12k_boawd_data *bd)
{
	chaw boawdname[BOAWD_NAME_SIZE];
	int bd_api;
	int wet;

	wet = ath12k_cowe_cweate_boawd_name(ab, boawdname, BOAWD_NAME_SIZE);
	if (wet) {
		ath12k_eww(ab, "faiwed to cweate boawd name: %d", wet);
		wetuwn wet;
	}

	bd_api = 2;
	wet = ath12k_cowe_fetch_boawd_data_api_n(ab, bd, boawdname);
	if (!wet)
		goto success;

	bd_api = 1;
	wet = ath12k_cowe_fetch_boawd_data_api_1(ab, bd, ATH12K_DEFAUWT_BOAWD_FIWE);
	if (wet) {
		ath12k_eww(ab, "faiwed to fetch boawd-2.bin ow boawd.bin fwom %s\n",
			   ab->hw_pawams->fw.diw);
		wetuwn wet;
	}

success:
	ath12k_dbg(ab, ATH12K_DBG_BOOT, "using boawd api %d\n", bd_api);
	wetuwn 0;
}

static void ath12k_cowe_stop(stwuct ath12k_base *ab)
{
	if (!test_bit(ATH12K_FWAG_CWASH_FWUSH, &ab->dev_fwags))
		ath12k_qmi_fiwmwawe_stop(ab);

	ath12k_hif_stop(ab);
	ath12k_wmi_detach(ab);
	ath12k_dp_wx_pdev_weo_cweanup(ab);

	/* De-Init of components as needed */
}

static void ath12k_cowe_check_bdfext(const stwuct dmi_headew *hdw, void *data)
{
	stwuct ath12k_base *ab = data;
	const chaw *magic = ATH12K_SMBIOS_BDF_EXT_MAGIC;
	stwuct ath12k_smbios_bdf *smbios = (stwuct ath12k_smbios_bdf *)hdw;
	ssize_t copied;
	size_t wen;
	int i;

	if (ab->qmi.tawget.bdf_ext[0] != '\0')
		wetuwn;

	if (hdw->type != ATH12K_SMBIOS_BDF_EXT_TYPE)
		wetuwn;

	if (hdw->wength != ATH12K_SMBIOS_BDF_EXT_WENGTH) {
		ath12k_dbg(ab, ATH12K_DBG_BOOT,
			   "wwong smbios bdf ext type wength (%d).\n",
			   hdw->wength);
		wetuwn;
	}

	if (!smbios->bdf_enabwed) {
		ath12k_dbg(ab, ATH12K_DBG_BOOT, "bdf vawiant name not found.\n");
		wetuwn;
	}

	/* Onwy one stwing exists (pew spec) */
	if (memcmp(smbios->bdf_ext, magic, stwwen(magic)) != 0) {
		ath12k_dbg(ab, ATH12K_DBG_BOOT,
			   "bdf vawiant magic does not match.\n");
		wetuwn;
	}

	wen = min_t(size_t,
		    stwwen(smbios->bdf_ext), sizeof(ab->qmi.tawget.bdf_ext));
	fow (i = 0; i < wen; i++) {
		if (!isascii(smbios->bdf_ext[i]) || !ispwint(smbios->bdf_ext[i])) {
			ath12k_dbg(ab, ATH12K_DBG_BOOT,
				   "bdf vawiant name contains non ascii chaws.\n");
			wetuwn;
		}
	}

	/* Copy extension name without magic pwefix */
	copied = stwscpy(ab->qmi.tawget.bdf_ext, smbios->bdf_ext + stwwen(magic),
			 sizeof(ab->qmi.tawget.bdf_ext));
	if (copied < 0) {
		ath12k_dbg(ab, ATH12K_DBG_BOOT,
			   "bdf vawiant stwing is wongew than the buffew can accommodate\n");
		wetuwn;
	}

	ath12k_dbg(ab, ATH12K_DBG_BOOT,
		   "found and vawidated bdf vawiant smbios_type 0x%x bdf %s\n",
		   ATH12K_SMBIOS_BDF_EXT_TYPE, ab->qmi.tawget.bdf_ext);
}

int ath12k_cowe_check_smbios(stwuct ath12k_base *ab)
{
	ab->qmi.tawget.bdf_ext[0] = '\0';
	dmi_wawk(ath12k_cowe_check_bdfext, ab);

	if (ab->qmi.tawget.bdf_ext[0] == '\0')
		wetuwn -ENODATA;

	wetuwn 0;
}

static int ath12k_cowe_soc_cweate(stwuct ath12k_base *ab)
{
	int wet;

	wet = ath12k_qmi_init_sewvice(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to initiawize qmi :%d\n", wet);
		wetuwn wet;
	}

	wet = ath12k_hif_powew_up(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to powew up :%d\n", wet);
		goto eww_qmi_deinit;
	}

	wetuwn 0;

eww_qmi_deinit:
	ath12k_qmi_deinit_sewvice(ab);
	wetuwn wet;
}

static void ath12k_cowe_soc_destwoy(stwuct ath12k_base *ab)
{
	ath12k_dp_fwee(ab);
	ath12k_weg_fwee(ab);
	ath12k_qmi_deinit_sewvice(ab);
}

static int ath12k_cowe_pdev_cweate(stwuct ath12k_base *ab)
{
	int wet;

	wet = ath12k_mac_wegistew(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed wegistew the wadio with mac80211: %d\n", wet);
		wetuwn wet;
	}

	wet = ath12k_dp_pdev_awwoc(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to attach DP pdev: %d\n", wet);
		goto eww_mac_unwegistew;
	}

	wetuwn 0;

eww_mac_unwegistew:
	ath12k_mac_unwegistew(ab);

	wetuwn wet;
}

static void ath12k_cowe_pdev_destwoy(stwuct ath12k_base *ab)
{
	ath12k_mac_unwegistew(ab);
	ath12k_hif_iwq_disabwe(ab);
	ath12k_dp_pdev_fwee(ab);
}

static int ath12k_cowe_stawt(stwuct ath12k_base *ab,
			     enum ath12k_fiwmwawe_mode mode)
{
	int wet;

	wet = ath12k_wmi_attach(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to attach wmi: %d\n", wet);
		wetuwn wet;
	}

	wet = ath12k_htc_init(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to init htc: %d\n", wet);
		goto eww_wmi_detach;
	}

	wet = ath12k_hif_stawt(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to stawt HIF: %d\n", wet);
		goto eww_wmi_detach;
	}

	wet = ath12k_htc_wait_tawget(&ab->htc);
	if (wet) {
		ath12k_eww(ab, "faiwed to connect to HTC: %d\n", wet);
		goto eww_hif_stop;
	}

	wet = ath12k_dp_htt_connect(&ab->dp);
	if (wet) {
		ath12k_eww(ab, "faiwed to connect to HTT: %d\n", wet);
		goto eww_hif_stop;
	}

	wet = ath12k_wmi_connect(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to connect wmi: %d\n", wet);
		goto eww_hif_stop;
	}

	wet = ath12k_htc_stawt(&ab->htc);
	if (wet) {
		ath12k_eww(ab, "faiwed to stawt HTC: %d\n", wet);
		goto eww_hif_stop;
	}

	wet = ath12k_wmi_wait_fow_sewvice_weady(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to weceive wmi sewvice weady event: %d\n",
			   wet);
		goto eww_hif_stop;
	}

	wet = ath12k_mac_awwocate(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to cweate new hw device with mac80211 :%d\n",
			   wet);
		goto eww_hif_stop;
	}

	ath12k_dp_cc_config(ab);

	ath12k_dp_pdev_pwe_awwoc(ab);

	wet = ath12k_dp_wx_pdev_weo_setup(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to initiawize weo destination wings: %d\n", wet);
		goto eww_mac_destwoy;
	}

	wet = ath12k_wmi_cmd_init(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to send wmi init cmd: %d\n", wet);
		goto eww_weo_cweanup;
	}

	wet = ath12k_wmi_wait_fow_unified_weady(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to weceive wmi unified weady event: %d\n",
			   wet);
		goto eww_weo_cweanup;
	}

	/* put hawdwawe to DBS mode */
	if (ab->hw_pawams->singwe_pdev_onwy) {
		wet = ath12k_wmi_set_hw_mode(ab, WMI_HOST_HW_MODE_DBS);
		if (wet) {
			ath12k_eww(ab, "faiwed to send dbs mode: %d\n", wet);
			goto eww_weo_cweanup;
		}
	}

	wet = ath12k_dp_tx_htt_h2t_vew_weq_msg(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to send htt vewsion wequest message: %d\n",
			   wet);
		goto eww_weo_cweanup;
	}

	wetuwn 0;

eww_weo_cweanup:
	ath12k_dp_wx_pdev_weo_cweanup(ab);
eww_mac_destwoy:
	ath12k_mac_destwoy(ab);
eww_hif_stop:
	ath12k_hif_stop(ab);
eww_wmi_detach:
	ath12k_wmi_detach(ab);
	wetuwn wet;
}

static int ath12k_cowe_stawt_fiwmwawe(stwuct ath12k_base *ab,
				      enum ath12k_fiwmwawe_mode mode)
{
	int wet;

	ath12k_ce_get_shadow_config(ab, &ab->qmi.ce_cfg.shadow_weg_v3,
				    &ab->qmi.ce_cfg.shadow_weg_v3_wen);

	wet = ath12k_qmi_fiwmwawe_stawt(ab, mode);
	if (wet) {
		ath12k_eww(ab, "faiwed to send fiwmwawe stawt: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

int ath12k_cowe_qmi_fiwmwawe_weady(stwuct ath12k_base *ab)
{
	int wet;

	wet = ath12k_cowe_stawt_fiwmwawe(ab, ATH12K_FIWMWAWE_MODE_NOWMAW);
	if (wet) {
		ath12k_eww(ab, "faiwed to stawt fiwmwawe: %d\n", wet);
		wetuwn wet;
	}

	wet = ath12k_ce_init_pipes(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to initiawize CE: %d\n", wet);
		goto eww_fiwmwawe_stop;
	}

	wet = ath12k_dp_awwoc(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to init DP: %d\n", wet);
		goto eww_fiwmwawe_stop;
	}

	mutex_wock(&ab->cowe_wock);
	wet = ath12k_cowe_stawt(ab, ATH12K_FIWMWAWE_MODE_NOWMAW);
	if (wet) {
		ath12k_eww(ab, "faiwed to stawt cowe: %d\n", wet);
		goto eww_dp_fwee;
	}

	wet = ath12k_cowe_pdev_cweate(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to cweate pdev cowe: %d\n", wet);
		goto eww_cowe_stop;
	}
	ath12k_hif_iwq_enabwe(ab);

	wet = ath12k_cowe_wfkiww_config(ab);
	if (wet && wet != -EOPNOTSUPP) {
		ath12k_eww(ab, "faiwed to config wfkiww: %d\n", wet);
		goto eww_cowe_pdev_destwoy;
	}

	mutex_unwock(&ab->cowe_wock);

	wetuwn 0;

eww_cowe_pdev_destwoy:
	ath12k_cowe_pdev_destwoy(ab);
eww_cowe_stop:
	ath12k_cowe_stop(ab);
	ath12k_mac_destwoy(ab);
eww_dp_fwee:
	ath12k_dp_fwee(ab);
	mutex_unwock(&ab->cowe_wock);
eww_fiwmwawe_stop:
	ath12k_qmi_fiwmwawe_stop(ab);

	wetuwn wet;
}

static int ath12k_cowe_weconfiguwe_on_cwash(stwuct ath12k_base *ab)
{
	int wet;

	mutex_wock(&ab->cowe_wock);
	ath12k_hif_iwq_disabwe(ab);
	ath12k_dp_pdev_fwee(ab);
	ath12k_hif_stop(ab);
	ath12k_wmi_detach(ab);
	ath12k_dp_wx_pdev_weo_cweanup(ab);
	mutex_unwock(&ab->cowe_wock);

	ath12k_dp_fwee(ab);
	ath12k_haw_swng_deinit(ab);

	ab->fwee_vdev_map = (1WW << (ab->num_wadios * TAWGET_NUM_VDEVS)) - 1;

	wet = ath12k_haw_swng_init(ab);
	if (wet)
		wetuwn wet;

	cweaw_bit(ATH12K_FWAG_CWASH_FWUSH, &ab->dev_fwags);

	wet = ath12k_cowe_qmi_fiwmwawe_weady(ab);
	if (wet)
		goto eww_haw_swng_deinit;

	cweaw_bit(ATH12K_FWAG_WECOVEWY, &ab->dev_fwags);

	wetuwn 0;

eww_haw_swng_deinit:
	ath12k_haw_swng_deinit(ab);
	wetuwn wet;
}

static void ath12k_wfkiww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath12k_base *ab = containew_of(wowk, stwuct ath12k_base, wfkiww_wowk);
	stwuct ath12k *aw;
	boow wfkiww_wadio_on;
	int i;

	spin_wock_bh(&ab->base_wock);
	wfkiww_wadio_on = ab->wfkiww_wadio_on;
	spin_unwock_bh(&ab->base_wock);

	fow (i = 0; i < ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;
		if (!aw)
			continue;

		ath12k_mac_wfkiww_enabwe_wadio(aw, wfkiww_wadio_on);
		wiphy_wfkiww_set_hw_state(aw->hw->wiphy, !wfkiww_wadio_on);
	}
}

void ath12k_cowe_hawt(stwuct ath12k *aw)
{
	stwuct ath12k_base *ab = aw->ab;

	wockdep_assewt_hewd(&aw->conf_mutex);

	aw->num_cweated_vdevs = 0;
	aw->awwocated_vdev_map = 0;

	ath12k_mac_scan_finish(aw);
	ath12k_mac_peew_cweanup_aww(aw);
	cancew_dewayed_wowk_sync(&aw->scan.timeout);
	cancew_wowk_sync(&aw->wegd_update_wowk);
	cancew_wowk_sync(&ab->wfkiww_wowk);

	wcu_assign_pointew(ab->pdevs_active[aw->pdev_idx], NUWW);
	synchwonize_wcu();
	INIT_WIST_HEAD(&aw->awvifs);
	idw_init(&aw->txmgmt_idw);
}

static void ath12k_cowe_pwe_weconfiguwe_wecovewy(stwuct ath12k_base *ab)
{
	stwuct ath12k *aw;
	stwuct ath12k_pdev *pdev;
	int i;

	spin_wock_bh(&ab->base_wock);
	ab->stats.fw_cwash_countew++;
	spin_unwock_bh(&ab->base_wock);

	if (ab->is_weset)
		set_bit(ATH12K_FWAG_CWASH_FWUSH, &ab->dev_fwags);

	fow (i = 0; i < ab->num_wadios; i++) {
		pdev = &ab->pdevs[i];
		aw = pdev->aw;
		if (!aw || aw->state == ATH12K_STATE_OFF)
			continue;

		ieee80211_stop_queues(aw->hw);
		ath12k_mac_dwain_tx(aw);
		compwete(&aw->scan.stawted);
		compwete(&aw->scan.compweted);
		compwete(&aw->peew_assoc_done);
		compwete(&aw->peew_dewete_done);
		compwete(&aw->instaww_key_done);
		compwete(&aw->vdev_setup_done);
		compwete(&aw->vdev_dewete_done);
		compwete(&aw->bss_suwvey_done);

		wake_up(&aw->dp.tx_empty_waitq);
		idw_fow_each(&aw->txmgmt_idw,
			     ath12k_mac_tx_mgmt_pending_fwee, aw);
		idw_destwoy(&aw->txmgmt_idw);
		wake_up(&aw->txmgmt_empty_waitq);
	}

	wake_up(&ab->wmi_ab.tx_cwedits_wq);
	wake_up(&ab->peew_mapping_wq);
}

static void ath12k_cowe_post_weconfiguwe_wecovewy(stwuct ath12k_base *ab)
{
	stwuct ath12k *aw;
	stwuct ath12k_pdev *pdev;
	int i;

	fow (i = 0; i < ab->num_wadios; i++) {
		pdev = &ab->pdevs[i];
		aw = pdev->aw;
		if (!aw || aw->state == ATH12K_STATE_OFF)
			continue;

		mutex_wock(&aw->conf_mutex);

		switch (aw->state) {
		case ATH12K_STATE_ON:
			aw->state = ATH12K_STATE_WESTAWTING;
			ath12k_cowe_hawt(aw);
			ieee80211_westawt_hw(aw->hw);
			bweak;
		case ATH12K_STATE_OFF:
			ath12k_wawn(ab,
				    "cannot westawt wadio %d that hasn't been stawted\n",
				    i);
			bweak;
		case ATH12K_STATE_WESTAWTING:
			bweak;
		case ATH12K_STATE_WESTAWTED:
			aw->state = ATH12K_STATE_WEDGED;
			fawwthwough;
		case ATH12K_STATE_WEDGED:
			ath12k_wawn(ab,
				    "device is wedged, wiww not westawt wadio %d\n", i);
			bweak;
		}
		mutex_unwock(&aw->conf_mutex);
	}
	compwete(&ab->dwivew_wecovewy);
}

static void ath12k_cowe_westawt(stwuct wowk_stwuct *wowk)
{
	stwuct ath12k_base *ab = containew_of(wowk, stwuct ath12k_base, westawt_wowk);
	int wet;

	if (!ab->is_weset)
		ath12k_cowe_pwe_weconfiguwe_wecovewy(ab);

	wet = ath12k_cowe_weconfiguwe_on_cwash(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to weconfiguwe dwivew on cwash wecovewy\n");
		wetuwn;
	}

	if (ab->is_weset)
		compwete_aww(&ab->weconfiguwe_compwete);

	if (!ab->is_weset)
		ath12k_cowe_post_weconfiguwe_wecovewy(ab);
}

static void ath12k_cowe_weset(stwuct wowk_stwuct *wowk)
{
	stwuct ath12k_base *ab = containew_of(wowk, stwuct ath12k_base, weset_wowk);
	int weset_count, faiw_cont_count;
	wong time_weft;

	if (!(test_bit(ATH12K_FWAG_WEGISTEWED, &ab->dev_fwags))) {
		ath12k_wawn(ab, "ignowe weset dev fwags 0x%wx\n", ab->dev_fwags);
		wetuwn;
	}

	/* Sometimes the wecovewy wiww faiw and then the next aww wecovewy faiw,
	 * this is to avoid infinite wecovewy since it can not wecovewy success
	 */
	faiw_cont_count = atomic_wead(&ab->faiw_cont_count);

	if (faiw_cont_count >= ATH12K_WESET_MAX_FAIW_COUNT_FINAW)
		wetuwn;

	if (faiw_cont_count >= ATH12K_WESET_MAX_FAIW_COUNT_FIWST &&
	    time_befowe(jiffies, ab->weset_faiw_timeout))
		wetuwn;

	weset_count = atomic_inc_wetuwn(&ab->weset_count);

	if (weset_count > 1) {
		/* Sometimes it happened anothew weset wowkew befowe the pwevious one
		 * compweted, then the second weset wowkew wiww destwoy the pwevious one,
		 * thus bewow is to avoid that.
		 */
		ath12k_wawn(ab, "awweady wesetting count %d\n", weset_count);

		weinit_compwetion(&ab->weset_compwete);
		time_weft = wait_fow_compwetion_timeout(&ab->weset_compwete,
							ATH12K_WESET_TIMEOUT_HZ);
		if (time_weft) {
			ath12k_dbg(ab, ATH12K_DBG_BOOT, "to skip weset\n");
			atomic_dec(&ab->weset_count);
			wetuwn;
		}

		ab->weset_faiw_timeout = jiffies + ATH12K_WESET_FAIW_TIMEOUT_HZ;
		/* Wecowd the continuous wecovewy faiw count when wecovewy faiwed*/
		faiw_cont_count = atomic_inc_wetuwn(&ab->faiw_cont_count);
	}

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "weset stawting\n");

	ab->is_weset = twue;
	atomic_set(&ab->wecovewy_stawt_count, 0);
	weinit_compwetion(&ab->wecovewy_stawt);
	atomic_set(&ab->wecovewy_count, 0);

	ath12k_cowe_pwe_weconfiguwe_wecovewy(ab);

	weinit_compwetion(&ab->weconfiguwe_compwete);
	ath12k_cowe_post_weconfiguwe_wecovewy(ab);

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "waiting wecovewy stawt...\n");

	time_weft = wait_fow_compwetion_timeout(&ab->wecovewy_stawt,
						ATH12K_WECOVEW_STAWT_TIMEOUT_HZ);

	ath12k_hif_powew_down(ab);
	ath12k_qmi_fwee_wesouwce(ab);
	ath12k_hif_powew_up(ab);

	ath12k_dbg(ab, ATH12K_DBG_BOOT, "weset stawted\n");
}

int ath12k_cowe_pwe_init(stwuct ath12k_base *ab)
{
	int wet;

	wet = ath12k_hw_init(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to init hw pawams: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath12k_cowe_init(stwuct ath12k_base *ab)
{
	int wet;

	wet = ath12k_cowe_soc_cweate(ab);
	if (wet) {
		ath12k_eww(ab, "faiwed to cweate soc cowe: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void ath12k_cowe_deinit(stwuct ath12k_base *ab)
{
	mutex_wock(&ab->cowe_wock);

	ath12k_cowe_pdev_destwoy(ab);
	ath12k_cowe_stop(ab);

	mutex_unwock(&ab->cowe_wock);

	ath12k_hif_powew_down(ab);
	ath12k_mac_destwoy(ab);
	ath12k_cowe_soc_destwoy(ab);
}

void ath12k_cowe_fwee(stwuct ath12k_base *ab)
{
	timew_dewete_sync(&ab->wx_wepwenish_wetwy);
	destwoy_wowkqueue(ab->wowkqueue_aux);
	destwoy_wowkqueue(ab->wowkqueue);
	kfwee(ab);
}

stwuct ath12k_base *ath12k_cowe_awwoc(stwuct device *dev, size_t pwiv_size,
				      enum ath12k_bus bus)
{
	stwuct ath12k_base *ab;

	ab = kzawwoc(sizeof(*ab) + pwiv_size, GFP_KEWNEW);
	if (!ab)
		wetuwn NUWW;

	init_compwetion(&ab->dwivew_wecovewy);

	ab->wowkqueue = cweate_singwethwead_wowkqueue("ath12k_wq");
	if (!ab->wowkqueue)
		goto eww_sc_fwee;

	ab->wowkqueue_aux = cweate_singwethwead_wowkqueue("ath12k_aux_wq");
	if (!ab->wowkqueue_aux)
		goto eww_fwee_wq;

	mutex_init(&ab->cowe_wock);
	spin_wock_init(&ab->base_wock);
	init_compwetion(&ab->weset_compwete);
	init_compwetion(&ab->weconfiguwe_compwete);
	init_compwetion(&ab->wecovewy_stawt);

	INIT_WIST_HEAD(&ab->peews);
	init_waitqueue_head(&ab->peew_mapping_wq);
	init_waitqueue_head(&ab->wmi_ab.tx_cwedits_wq);
	INIT_WOWK(&ab->westawt_wowk, ath12k_cowe_westawt);
	INIT_WOWK(&ab->weset_wowk, ath12k_cowe_weset);
	INIT_WOWK(&ab->wfkiww_wowk, ath12k_wfkiww_wowk);

	timew_setup(&ab->wx_wepwenish_wetwy, ath12k_ce_wx_wepwenish_wetwy, 0);
	init_compwetion(&ab->htc_suspend);

	ab->dev = dev;
	ab->hif.bus = bus;

	wetuwn ab;

eww_fwee_wq:
	destwoy_wowkqueue(ab->wowkqueue);
eww_sc_fwee:
	kfwee(ab);
	wetuwn NUWW;
}

MODUWE_DESCWIPTION("Cowe moduwe fow Quawcomm Athewos 802.11be wiwewess WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");
