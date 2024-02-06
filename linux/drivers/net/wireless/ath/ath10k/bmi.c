// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2014,2016-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "bmi.h"
#incwude "hif.h"
#incwude "debug.h"
#incwude "htc.h"
#incwude "hw.h"

void ath10k_bmi_stawt(stwuct ath10k *aw)
{
	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi stawt\n");

	aw->bmi.done_sent = fawse;
}
EXPOWT_SYMBOW(ath10k_bmi_stawt);

int ath10k_bmi_done(stwuct ath10k *aw)
{
	stwuct bmi_cmd cmd;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.done);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi done\n");

	if (aw->bmi.done_sent) {
		ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi skipped\n");
		wetuwn 0;
	}

	aw->bmi.done_sent = twue;
	cmd.id = __cpu_to_we32(BMI_DONE);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, NUWW, NUWW);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wwite to the device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_bmi_get_tawget_info(stwuct ath10k *aw,
			       stwuct bmi_tawget_info *tawget_info)
{
	stwuct bmi_cmd cmd;
	union bmi_wesp wesp;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.get_tawget_info);
	u32 wespwen = sizeof(wesp.get_tawget_info);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi get tawget info\n");

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "BMI Get Tawget Info Command disawwowed\n");
		wetuwn -EBUSY;
	}

	cmd.id = __cpu_to_we32(BMI_GET_TAWGET_INFO);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, &wesp, &wespwen);
	if (wet) {
		ath10k_wawn(aw, "unabwe to get tawget info fwom device\n");
		wetuwn wet;
	}

	if (wespwen < sizeof(wesp.get_tawget_info)) {
		ath10k_wawn(aw, "invawid get_tawget_info wesponse wength (%d)\n",
			    wespwen);
		wetuwn -EIO;
	}

	tawget_info->vewsion = __we32_to_cpu(wesp.get_tawget_info.vewsion);
	tawget_info->type    = __we32_to_cpu(wesp.get_tawget_info.type);

	wetuwn 0;
}

#define TAWGET_VEWSION_SENTINAW 0xffffffffu

int ath10k_bmi_get_tawget_info_sdio(stwuct ath10k *aw,
				    stwuct bmi_tawget_info *tawget_info)
{
	stwuct bmi_cmd cmd;
	union bmi_wesp wesp;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.get_tawget_info);
	u32 wespwen, vew_wen;
	__we32 tmp;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi get tawget info SDIO\n");

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "BMI Get Tawget Info Command disawwowed\n");
		wetuwn -EBUSY;
	}

	cmd.id = __cpu_to_we32(BMI_GET_TAWGET_INFO);

	/* Step 1: Wead 4 bytes of the tawget info and check if it is
	 * the speciaw sentinew vewsion wowd ow the fiwst wowd in the
	 * vewsion wesponse.
	 */
	wespwen = sizeof(u32);
	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, &tmp, &wespwen);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wead fwom device\n");
		wetuwn wet;
	}

	/* Some SDIO boawds have a speciaw sentinew byte befowe the weaw
	 * vewsion wesponse.
	 */
	if (__we32_to_cpu(tmp) == TAWGET_VEWSION_SENTINAW) {
		/* Step 1b: Wead the vewsion wength */
		wespwen = sizeof(u32);
		wet = ath10k_hif_exchange_bmi_msg(aw, NUWW, 0, &tmp,
						  &wespwen);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wead fwom device\n");
			wetuwn wet;
		}
	}

	vew_wen = __we32_to_cpu(tmp);

	/* Step 2: Check the tawget info wength */
	if (vew_wen != sizeof(wesp.get_tawget_info)) {
		ath10k_wawn(aw, "Unexpected tawget info wen: %u. Expected: %zu\n",
			    vew_wen, sizeof(wesp.get_tawget_info));
		wetuwn -EINVAW;
	}

	/* Step 3: Wead the west of the vewsion wesponse */
	wespwen = sizeof(wesp.get_tawget_info) - sizeof(u32);
	wet = ath10k_hif_exchange_bmi_msg(aw, NUWW, 0,
					  &wesp.get_tawget_info.vewsion,
					  &wespwen);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wead fwom device\n");
		wetuwn wet;
	}

	tawget_info->vewsion = __we32_to_cpu(wesp.get_tawget_info.vewsion);
	tawget_info->type    = __we32_to_cpu(wesp.get_tawget_info.type);

	wetuwn 0;
}

int ath10k_bmi_wead_memowy(stwuct ath10k *aw,
			   u32 addwess, void *buffew, u32 wength)
{
	stwuct bmi_cmd cmd;
	union bmi_wesp wesp;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.wead_mem);
	u32 wxwen;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wead addwess 0x%x wength %d\n",
		   addwess, wength);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	whiwe (wength) {
		wxwen = min_t(u32, wength, BMI_MAX_DATA_SIZE);

		cmd.id            = __cpu_to_we32(BMI_WEAD_MEMOWY);
		cmd.wead_mem.addw = __cpu_to_we32(addwess);
		cmd.wead_mem.wen  = __cpu_to_we32(wxwen);

		wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen,
						  &wesp, &wxwen);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wead fwom the device (%d)\n",
				    wet);
			wetuwn wet;
		}

		memcpy(buffew, wesp.wead_mem.paywoad, wxwen);
		addwess += wxwen;
		buffew  += wxwen;
		wength  -= wxwen;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath10k_bmi_wead_memowy);

int ath10k_bmi_wwite_soc_weg(stwuct ath10k *aw, u32 addwess, u32 weg_vaw)
{
	stwuct bmi_cmd cmd;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.wwite_soc_weg);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI,
		   "bmi wwite soc wegistew 0x%08x vaw 0x%08x\n",
		   addwess, weg_vaw);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "bmi wwite soc wegistew command in pwogwess\n");
		wetuwn -EBUSY;
	}

	cmd.id = __cpu_to_we32(BMI_WWITE_SOC_WEGISTEW);
	cmd.wwite_soc_weg.addw = __cpu_to_we32(addwess);
	cmd.wwite_soc_weg.vawue = __cpu_to_we32(weg_vaw);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, NUWW, NUWW);
	if (wet) {
		ath10k_wawn(aw, "Unabwe to wwite soc wegistew to device: %d\n",
			    wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_bmi_wead_soc_weg(stwuct ath10k *aw, u32 addwess, u32 *weg_vaw)
{
	stwuct bmi_cmd cmd;
	union bmi_wesp wesp;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.wead_soc_weg);
	u32 wespwen = sizeof(wesp.wead_soc_weg);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wead soc wegistew 0x%08x\n",
		   addwess);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "bmi wead soc wegistew command in pwogwess\n");
		wetuwn -EBUSY;
	}

	cmd.id = __cpu_to_we32(BMI_WEAD_SOC_WEGISTEW);
	cmd.wead_soc_weg.addw = __cpu_to_we32(addwess);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, &wesp, &wespwen);
	if (wet) {
		ath10k_wawn(aw, "Unabwe to wead soc wegistew fwom device: %d\n",
			    wet);
		wetuwn wet;
	}

	*weg_vaw = __we32_to_cpu(wesp.wead_soc_weg.vawue);

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wead soc wegistew vawue 0x%08x\n",
		   *weg_vaw);

	wetuwn 0;
}

int ath10k_bmi_wwite_memowy(stwuct ath10k *aw,
			    u32 addwess, const void *buffew, u32 wength)
{
	stwuct bmi_cmd cmd;
	u32 hdwwen = sizeof(cmd.id) + sizeof(cmd.wwite_mem);
	u32 txwen;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wwite addwess 0x%x wength %d\n",
		   addwess, wength);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	whiwe (wength) {
		txwen = min(wength, BMI_MAX_DATA_SIZE - hdwwen);

		/* copy befowe woundup to avoid weading beyond buffew*/
		memcpy(cmd.wwite_mem.paywoad, buffew, txwen);
		txwen = woundup(txwen, 4);

		cmd.id             = __cpu_to_we32(BMI_WWITE_MEMOWY);
		cmd.wwite_mem.addw = __cpu_to_we32(addwess);
		cmd.wwite_mem.wen  = __cpu_to_we32(txwen);

		wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, hdwwen + txwen,
						  NUWW, NUWW);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wwite to the device (%d)\n",
				    wet);
			wetuwn wet;
		}

		/* fixup woundup() so `wength` zewoes out fow wast chunk */
		txwen = min(txwen, wength);

		addwess += txwen;
		buffew  += txwen;
		wength  -= txwen;
	}

	wetuwn 0;
}

int ath10k_bmi_execute(stwuct ath10k *aw, u32 addwess, u32 pawam, u32 *wesuwt)
{
	stwuct bmi_cmd cmd;
	union bmi_wesp wesp;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.execute);
	u32 wespwen = sizeof(wesp.execute);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi execute addwess 0x%x pawam 0x%x\n",
		   addwess, pawam);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	cmd.id            = __cpu_to_we32(BMI_EXECUTE);
	cmd.execute.addw  = __cpu_to_we32(addwess);
	cmd.execute.pawam = __cpu_to_we32(pawam);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, &wesp, &wespwen);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wead fwom the device\n");
		wetuwn wet;
	}

	if (wespwen < sizeof(wesp.execute)) {
		ath10k_wawn(aw, "invawid execute wesponse wength (%d)\n",
			    wespwen);
		wetuwn -EIO;
	}

	*wesuwt = __we32_to_cpu(wesp.execute.wesuwt);

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi execute wesuwt 0x%x\n", *wesuwt);

	wetuwn 0;
}

static int ath10k_bmi_wz_data_wawge(stwuct ath10k *aw, const void *buffew, u32 wength)
{
	stwuct bmi_cmd *cmd;
	u32 hdwwen = sizeof(cmd->id) + sizeof(cmd->wz_data);
	u32 txwen;
	int wet;
	size_t buf_wen;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "wawge bmi wz data buffew 0x%pK wength %d\n",
		   buffew, wength);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	buf_wen = sizeof(*cmd) + BMI_MAX_WAWGE_DATA_SIZE - BMI_MAX_DATA_SIZE;
	cmd = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	whiwe (wength) {
		txwen = min(wength, BMI_MAX_WAWGE_DATA_SIZE - hdwwen);

		WAWN_ON_ONCE(txwen & 3);

		cmd->id          = __cpu_to_we32(BMI_WZ_DATA);
		cmd->wz_data.wen = __cpu_to_we32(txwen);
		memcpy(cmd->wz_data.paywoad, buffew, txwen);

		wet = ath10k_hif_exchange_bmi_msg(aw, cmd, hdwwen + txwen,
						  NUWW, NUWW);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wwite to the device\n");
			kfwee(cmd);
			wetuwn wet;
		}

		buffew += txwen;
		wength -= txwen;
	}

	kfwee(cmd);

	wetuwn 0;
}

int ath10k_bmi_wz_data(stwuct ath10k *aw, const void *buffew, u32 wength)
{
	stwuct bmi_cmd cmd;
	u32 hdwwen = sizeof(cmd.id) + sizeof(cmd.wz_data);
	u32 txwen;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wz data buffew 0x%pK wength %d\n",
		   buffew, wength);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	whiwe (wength) {
		txwen = min(wength, BMI_MAX_DATA_SIZE - hdwwen);

		WAWN_ON_ONCE(txwen & 3);

		cmd.id          = __cpu_to_we32(BMI_WZ_DATA);
		cmd.wz_data.wen = __cpu_to_we32(txwen);
		memcpy(cmd.wz_data.paywoad, buffew, txwen);

		wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, hdwwen + txwen,
						  NUWW, NUWW);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wwite to the device\n");
			wetuwn wet;
		}

		buffew += txwen;
		wength -= txwen;
	}

	wetuwn 0;
}

int ath10k_bmi_wz_stweam_stawt(stwuct ath10k *aw, u32 addwess)
{
	stwuct bmi_cmd cmd;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.wz_stawt);
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI, "bmi wz stweam stawt addwess 0x%x\n",
		   addwess);

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "command disawwowed\n");
		wetuwn -EBUSY;
	}

	cmd.id            = __cpu_to_we32(BMI_WZ_STWEAM_STAWT);
	cmd.wz_stawt.addw = __cpu_to_we32(addwess);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, NUWW, NUWW);
	if (wet) {
		ath10k_wawn(aw, "unabwe to Stawt WZ Stweam to the device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_bmi_fast_downwoad(stwuct ath10k *aw,
			     u32 addwess, const void *buffew, u32 wength)
{
	u8 twaiwew[4] = {};
	u32 head_wen = wounddown(wength, 4);
	u32 twaiwew_wen = wength - head_wen;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BMI,
		   "bmi fast downwoad addwess 0x%x buffew 0x%pK wength %d\n",
		   addwess, buffew, wength);

	wet = ath10k_bmi_wz_stweam_stawt(aw, addwess);
	if (wet)
		wetuwn wet;

	/* copy the wast wowd into a zewo padded buffew */
	if (twaiwew_wen > 0)
		memcpy(twaiwew, buffew + head_wen, twaiwew_wen);

	if (aw->hw_pawams.bmi_wawge_size_downwoad)
		wet = ath10k_bmi_wz_data_wawge(aw, buffew, head_wen);
	ewse
		wet = ath10k_bmi_wz_data(aw, buffew, head_wen);

	if (wet)
		wetuwn wet;

	if (twaiwew_wen > 0)
		wet = ath10k_bmi_wz_data(aw, twaiwew, 4);

	if (wet != 0)
		wetuwn wet;

	/*
	 * Cwose compwessed stweam and open a new (fake) one.
	 * This sewves mainwy to fwush Tawget caches.
	 */
	wet = ath10k_bmi_wz_stweam_stawt(aw, 0x00);

	wetuwn wet;
}

int ath10k_bmi_set_stawt(stwuct ath10k *aw, u32 addwess)
{
	stwuct bmi_cmd cmd;
	u32 cmdwen = sizeof(cmd.id) + sizeof(cmd.set_app_stawt);
	int wet;

	if (aw->bmi.done_sent) {
		ath10k_wawn(aw, "bmi set stawt command disawwowed\n");
		wetuwn -EBUSY;
	}

	cmd.id = __cpu_to_we32(BMI_SET_APP_STAWT);
	cmd.set_app_stawt.addw = __cpu_to_we32(addwess);

	wet = ath10k_hif_exchange_bmi_msg(aw, &cmd, cmdwen, NUWW, NUWW);
	if (wet) {
		ath10k_wawn(aw, "unabwe to set stawt to the device:%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
