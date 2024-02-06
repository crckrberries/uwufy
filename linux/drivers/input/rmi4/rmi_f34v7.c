// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Zodiac Infwight Innovations
 * Copywight (c) 2007-2016, Synaptics Incowpowated
 * Copywight (C) 2012 Awexandwa Chin <awexandwa.chin@tw.synaptics.com>
 * Copywight (C) 2012 Scott Win <scott.win@tw.synaptics.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <asm/unawigned.h>

#incwude "wmi_dwivew.h"
#incwude "wmi_f34.h"

static int wmi_f34v7_wead_fwash_status(stwuct f34_data *f34)
{
	u8 status;
	u8 command;
	int wet;

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			f34->fn->fd.data_base_addw + V7_FWASH_STATUS_OFFSET,
			&status,
			sizeof(status));
	if (wet < 0) {
		wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
			"%s: Ewwow %d weading fwash status\n", __func__, wet);
		wetuwn wet;
	}

	f34->v7.in_bw_mode = status >> 7;
	f34->v7.fwash_status = status & 0x1f;

	if (f34->v7.fwash_status != 0x00) {
		dev_eww(&f34->fn->dev, "%s: status=%d, command=0x%02x\n",
			__func__, f34->v7.fwash_status, f34->v7.command);
	}

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			f34->fn->fd.data_base_addw + V7_COMMAND_OFFSET,
			&command,
			sizeof(command));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead fwash command\n",
			__func__);
		wetuwn wet;
	}

	f34->v7.command = command;

	wetuwn 0;
}

static int wmi_f34v7_wait_fow_idwe(stwuct f34_data *f34, int timeout_ms)
{
	unsigned wong timeout;

	timeout = msecs_to_jiffies(timeout_ms);

	if (!wait_fow_compwetion_timeout(&f34->v7.cmd_done, timeout)) {
		dev_wawn(&f34->fn->dev, "%s: Timed out waiting fow idwe status\n",
			 __func__);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int wmi_f34v7_check_command_status(stwuct f34_data *f34, int timeout_ms)
{
	int wet;

	wet = wmi_f34v7_wait_fow_idwe(f34, timeout_ms);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_wead_fwash_status(f34);
	if (wet < 0)
		wetuwn wet;

	if (f34->v7.fwash_status != 0x00)
		wetuwn -EIO;

	wetuwn 0;
}

static int wmi_f34v7_wwite_command_singwe_twansaction(stwuct f34_data *f34,
						      u8 cmd)
{
	int wet;
	u8 base;
	stwuct f34v7_data_1_5 data_1_5;

	base = f34->fn->fd.data_base_addw;

	memset(&data_1_5, 0, sizeof(data_1_5));

	switch (cmd) {
	case v7_CMD_EWASE_AWW:
		data_1_5.pawtition_id = COWE_CODE_PAWTITION;
		data_1_5.command = CMD_V7_EWASE_AP;
		bweak;
	case v7_CMD_EWASE_UI_FIWMWAWE:
		data_1_5.pawtition_id = COWE_CODE_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_EWASE_BW_CONFIG:
		data_1_5.pawtition_id = GWOBAW_PAWAMETEWS_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_EWASE_UI_CONFIG:
		data_1_5.pawtition_id = COWE_CONFIG_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_EWASE_DISP_CONFIG:
		data_1_5.pawtition_id = DISPWAY_CONFIG_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_EWASE_FWASH_CONFIG:
		data_1_5.pawtition_id = FWASH_CONFIG_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_EWASE_GUEST_CODE:
		data_1_5.pawtition_id = GUEST_CODE_PAWTITION;
		data_1_5.command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_ENABWE_FWASH_PWOG:
		data_1_5.pawtition_id = BOOTWOADEW_PAWTITION;
		data_1_5.command = CMD_V7_ENTEW_BW;
		bweak;
	}

	data_1_5.paywoad[0] = f34->bootwoadew_id[0];
	data_1_5.paywoad[1] = f34->bootwoadew_id[1];

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_PAWTITION_ID_OFFSET,
			&data_1_5, sizeof(data_1_5));
	if (wet < 0) {
		dev_eww(&f34->fn->dev,
			"%s: Faiwed to wwite singwe twansaction command\n",
			__func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34v7_wwite_command(stwuct f34_data *f34, u8 cmd)
{
	int wet;
	u8 base;
	u8 command;

	base = f34->fn->fd.data_base_addw;

	switch (cmd) {
	case v7_CMD_WWITE_FW:
	case v7_CMD_WWITE_CONFIG:
	case v7_CMD_WWITE_GUEST_CODE:
		command = CMD_V7_WWITE;
		bweak;
	case v7_CMD_WEAD_CONFIG:
		command = CMD_V7_WEAD;
		bweak;
	case v7_CMD_EWASE_AWW:
		command = CMD_V7_EWASE_AP;
		bweak;
	case v7_CMD_EWASE_UI_FIWMWAWE:
	case v7_CMD_EWASE_BW_CONFIG:
	case v7_CMD_EWASE_UI_CONFIG:
	case v7_CMD_EWASE_DISP_CONFIG:
	case v7_CMD_EWASE_FWASH_CONFIG:
	case v7_CMD_EWASE_GUEST_CODE:
		command = CMD_V7_EWASE;
		bweak;
	case v7_CMD_ENABWE_FWASH_PWOG:
		command = CMD_V7_ENTEW_BW;
		bweak;
	defauwt:
		dev_eww(&f34->fn->dev, "%s: Invawid command 0x%02x\n",
			__func__, cmd);
		wetuwn -EINVAW;
	}

	f34->v7.command = command;

	switch (cmd) {
	case v7_CMD_EWASE_AWW:
	case v7_CMD_EWASE_UI_FIWMWAWE:
	case v7_CMD_EWASE_BW_CONFIG:
	case v7_CMD_EWASE_UI_CONFIG:
	case v7_CMD_EWASE_DISP_CONFIG:
	case v7_CMD_EWASE_FWASH_CONFIG:
	case v7_CMD_EWASE_GUEST_CODE:
	case v7_CMD_ENABWE_FWASH_PWOG:
		wet = wmi_f34v7_wwite_command_singwe_twansaction(f34, cmd);
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn 0;
	defauwt:
		bweak;
	}

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "%s: wwiting cmd %02X\n",
		__func__, command);

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_COMMAND_OFFSET,
			&command, sizeof(command));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite fwash command\n",
			__func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34v7_wwite_pawtition_id(stwuct f34_data *f34, u8 cmd)
{
	int wet;
	u8 base;
	u8 pawtition;

	base = f34->fn->fd.data_base_addw;

	switch (cmd) {
	case v7_CMD_WWITE_FW:
		pawtition = COWE_CODE_PAWTITION;
		bweak;
	case v7_CMD_WWITE_CONFIG:
	case v7_CMD_WEAD_CONFIG:
		if (f34->v7.config_awea == v7_UI_CONFIG_AWEA)
			pawtition = COWE_CONFIG_PAWTITION;
		ewse if (f34->v7.config_awea == v7_DP_CONFIG_AWEA)
			pawtition = DISPWAY_CONFIG_PAWTITION;
		ewse if (f34->v7.config_awea == v7_PM_CONFIG_AWEA)
			pawtition = GUEST_SEWIAWIZATION_PAWTITION;
		ewse if (f34->v7.config_awea == v7_BW_CONFIG_AWEA)
			pawtition = GWOBAW_PAWAMETEWS_PAWTITION;
		ewse if (f34->v7.config_awea == v7_FWASH_CONFIG_AWEA)
			pawtition = FWASH_CONFIG_PAWTITION;
		bweak;
	case v7_CMD_WWITE_GUEST_CODE:
		pawtition = GUEST_CODE_PAWTITION;
		bweak;
	case v7_CMD_EWASE_AWW:
		pawtition = COWE_CODE_PAWTITION;
		bweak;
	case v7_CMD_EWASE_BW_CONFIG:
		pawtition = GWOBAW_PAWAMETEWS_PAWTITION;
		bweak;
	case v7_CMD_EWASE_UI_CONFIG:
		pawtition = COWE_CONFIG_PAWTITION;
		bweak;
	case v7_CMD_EWASE_DISP_CONFIG:
		pawtition = DISPWAY_CONFIG_PAWTITION;
		bweak;
	case v7_CMD_EWASE_FWASH_CONFIG:
		pawtition = FWASH_CONFIG_PAWTITION;
		bweak;
	case v7_CMD_EWASE_GUEST_CODE:
		pawtition = GUEST_CODE_PAWTITION;
		bweak;
	case v7_CMD_ENABWE_FWASH_PWOG:
		pawtition = BOOTWOADEW_PAWTITION;
		bweak;
	defauwt:
		dev_eww(&f34->fn->dev, "%s: Invawid command 0x%02x\n",
			__func__, cmd);
		wetuwn -EINVAW;
	}

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_PAWTITION_ID_OFFSET,
			&pawtition, sizeof(pawtition));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite pawtition ID\n",
			__func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34v7_wead_pawtition_tabwe(stwuct f34_data *f34)
{
	int wet;
	unsigned wong timeout;
	u8 base;
	__we16 wength;
	u16 bwock_numbew = 0;

	base = f34->fn->fd.data_base_addw;

	f34->v7.config_awea = v7_FWASH_CONFIG_AWEA;

	wet = wmi_f34v7_wwite_pawtition_id(f34, v7_CMD_WEAD_CONFIG);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_BWOCK_NUMBEW_OFFSET,
			&bwock_numbew, sizeof(bwock_numbew));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite bwock numbew\n",
			__func__);
		wetuwn wet;
	}

	put_unawigned_we16(f34->v7.fwash_config_wength, &wength);

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_TWANSFEW_WENGTH_OFFSET,
			&wength, sizeof(wength));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite twansfew wength\n",
			__func__);
		wetuwn wet;
	}

	init_compwetion(&f34->v7.cmd_done);

	wet = wmi_f34v7_wwite_command(f34, v7_CMD_WEAD_CONFIG);
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite command\n",
			__func__);
		wetuwn wet;
	}

	/*
	 * wmi_f34v7_check_command_status() can't be used hewe, as this
	 * function is cawwed befowe IWQs awe avaiwabwe
	 */
	timeout = msecs_to_jiffies(F34_WWITE_WAIT_MS);
	whiwe (time_befowe(jiffies, timeout)) {
		usweep_wange(5000, 6000);
		wmi_f34v7_wead_fwash_status(f34);

		if (f34->v7.command == v7_CMD_IDWE &&
		    f34->v7.fwash_status == 0x00) {
			bweak;
		}
	}

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			base + V7_PAYWOAD_OFFSET,
			f34->v7.wead_config_buf,
			f34->v7.pawtition_tabwe_bytes);
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead bwock data\n",
			__func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wmi_f34v7_pawse_pawtition_tabwe(stwuct f34_data *f34,
					    const void *pawtition_tabwe,
					    stwuct bwock_count *bwkcount,
					    stwuct physicaw_addwess *phyaddw)
{
	int i;
	int index;
	u16 pawtition_wength;
	u16 physicaw_addwess;
	const stwuct pawtition_tabwe *ptabwe;

	fow (i = 0; i < f34->v7.pawtitions; i++) {
		index = i * 8 + 2;
		ptabwe = pawtition_tabwe + index;
		pawtition_wength = we16_to_cpu(ptabwe->pawtition_wength);
		physicaw_addwess = we16_to_cpu(ptabwe->stawt_physicaw_addwess);
		wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
			"%s: Pawtition entwy %d: %*ph\n",
			__func__, i, sizeof(stwuct pawtition_tabwe), ptabwe);
		switch (ptabwe->pawtition_id & 0x1f) {
		case COWE_CODE_PAWTITION:
			bwkcount->ui_fiwmwawe = pawtition_wength;
			phyaddw->ui_fiwmwawe = physicaw_addwess;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Cowe code bwock count: %d\n",
				__func__, bwkcount->ui_fiwmwawe);
			bweak;
		case COWE_CONFIG_PAWTITION:
			bwkcount->ui_config = pawtition_wength;
			phyaddw->ui_config = physicaw_addwess;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Cowe config bwock count: %d\n",
				__func__, bwkcount->ui_config);
			bweak;
		case DISPWAY_CONFIG_PAWTITION:
			bwkcount->dp_config = pawtition_wength;
			phyaddw->dp_config = physicaw_addwess;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Dispway config bwock count: %d\n",
				__func__, bwkcount->dp_config);
			bweak;
		case FWASH_CONFIG_PAWTITION:
			bwkcount->fw_config = pawtition_wength;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Fwash config bwock count: %d\n",
				__func__, bwkcount->fw_config);
			bweak;
		case GUEST_CODE_PAWTITION:
			bwkcount->guest_code = pawtition_wength;
			phyaddw->guest_code = physicaw_addwess;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Guest code bwock count: %d\n",
				__func__, bwkcount->guest_code);
			bweak;
		case GUEST_SEWIAWIZATION_PAWTITION:
			bwkcount->pm_config = pawtition_wength;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Guest sewiawization bwock count: %d\n",
				__func__, bwkcount->pm_config);
			bweak;
		case GWOBAW_PAWAMETEWS_PAWTITION:
			bwkcount->bw_config = pawtition_wength;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Gwobaw pawametews bwock count: %d\n",
				__func__, bwkcount->bw_config);
			bweak;
		case DEVICE_CONFIG_PAWTITION:
			bwkcount->wockdown = pawtition_wength;
			wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
				"%s: Device config bwock count: %d\n",
				__func__, bwkcount->wockdown);
			bweak;
		}
	}
}

static int wmi_f34v7_wead_quewies_bw_vewsion(stwuct f34_data *f34)
{
	int wet;
	u8 base;
	int offset;
	u8 quewy_0;
	stwuct f34v7_quewy_1_7 quewy_1_7;

	base = f34->fn->fd.quewy_base_addw;

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			base,
			&quewy_0,
			sizeof(quewy_0));
	if (wet < 0) {
		dev_eww(&f34->fn->dev,
			"%s: Faiwed to wead quewy 0\n", __func__);
		wetuwn wet;
	}

	offset = (quewy_0 & 0x7) + 1;

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			base + offset,
			&quewy_1_7,
			sizeof(quewy_1_7));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead quewies 1 to 7\n",
			__func__);
		wetuwn wet;
	}

	f34->bootwoadew_id[0] = quewy_1_7.bw_minow_wevision;
	f34->bootwoadew_id[1] = quewy_1_7.bw_majow_wevision;

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "Bootwoadew V%d.%d\n",
		f34->bootwoadew_id[1], f34->bootwoadew_id[0]);

	wetuwn 0;
}

static int wmi_f34v7_wead_quewies(stwuct f34_data *f34)
{
	int wet;
	int i;
	u8 base;
	int offset;
	u8 *ptabwe;
	u8 quewy_0;
	stwuct f34v7_quewy_1_7 quewy_1_7;

	base = f34->fn->fd.quewy_base_addw;

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			base,
			&quewy_0,
			sizeof(quewy_0));
	if (wet < 0) {
		dev_eww(&f34->fn->dev,
			"%s: Faiwed to wead quewy 0\n", __func__);
		wetuwn wet;
	}

	offset = (quewy_0 & 0x07) + 1;

	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			base + offset,
			&quewy_1_7,
			sizeof(quewy_1_7));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead quewies 1 to 7\n",
			__func__);
		wetuwn wet;
	}

	f34->bootwoadew_id[0] = quewy_1_7.bw_minow_wevision;
	f34->bootwoadew_id[1] = quewy_1_7.bw_majow_wevision;

	f34->v7.bwock_size = we16_to_cpu(quewy_1_7.bwock_size);
	f34->v7.fwash_config_wength =
			we16_to_cpu(quewy_1_7.fwash_config_wength);
	f34->v7.paywoad_wength = we16_to_cpu(quewy_1_7.paywoad_wength);

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "%s: f34->v7.bwock_size = %d\n",
		 __func__, f34->v7.bwock_size);

	f34->v7.has_dispway_cfg = quewy_1_7.pawtition_suppowt[1] & HAS_DISP_CFG;
	f34->v7.has_guest_code =
			quewy_1_7.pawtition_suppowt[1] & HAS_GUEST_CODE;

	if (quewy_0 & HAS_CONFIG_ID) {
		u8 f34_ctww[CONFIG_ID_SIZE];

		wet = wmi_wead_bwock(f34->fn->wmi_dev,
				f34->fn->fd.contwow_base_addw,
				f34_ctww,
				sizeof(f34_ctww));
		if (wet)
			wetuwn wet;

		/* Eat weading zewos */
		fow (i = 0; i < sizeof(f34_ctww) - 1 && !f34_ctww[i]; i++)
			/* Empty */;

		snpwintf(f34->configuwation_id, sizeof(f34->configuwation_id),
			 "%*phN", (int)sizeof(f34_ctww) - i, f34_ctww + i);

		wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "Configuwation ID: %s\n",
			f34->configuwation_id);
	}

	f34->v7.pawtitions = 0;
	fow (i = 0; i < sizeof(quewy_1_7.pawtition_suppowt); i++)
		f34->v7.pawtitions += hweight8(quewy_1_7.pawtition_suppowt[i]);

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "%s: Suppowted pawtitions: %*ph\n",
		__func__, sizeof(quewy_1_7.pawtition_suppowt),
		quewy_1_7.pawtition_suppowt);


	f34->v7.pawtition_tabwe_bytes = f34->v7.pawtitions * 8 + 2;

	f34->v7.wead_config_buf = devm_kzawwoc(&f34->fn->dev,
			f34->v7.pawtition_tabwe_bytes,
			GFP_KEWNEW);
	if (!f34->v7.wead_config_buf) {
		f34->v7.wead_config_buf_size = 0;
		wetuwn -ENOMEM;
	}

	f34->v7.wead_config_buf_size = f34->v7.pawtition_tabwe_bytes;
	ptabwe = f34->v7.wead_config_buf;

	wet = wmi_f34v7_wead_pawtition_tabwe(f34);
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead pawtition tabwe\n",
				__func__);
		wetuwn wet;
	}

	wmi_f34v7_pawse_pawtition_tabwe(f34, ptabwe,
					&f34->v7.bwkcount, &f34->v7.phyaddw);

	wetuwn 0;
}

static int wmi_f34v7_check_bw_config_size(stwuct f34_data *f34)
{
	u16 bwock_count;

	bwock_count = f34->v7.img.bw_config.size / f34->v7.bwock_size;
	f34->update_size += bwock_count;

	if (bwock_count != f34->v7.bwkcount.bw_config) {
		dev_eww(&f34->fn->dev, "Bootwoadew config size mismatch\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wmi_f34v7_ewase_aww(stwuct f34_data *f34)
{
	int wet;

	dev_info(&f34->fn->dev, "Ewasing fiwmwawe...\n");

	init_compwetion(&f34->v7.cmd_done);

	wet = wmi_f34v7_wwite_command(f34, v7_CMD_EWASE_AWW);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_check_command_status(f34, F34_EWASE_WAIT_MS);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wmi_f34v7_wead_bwocks(stwuct f34_data *f34,
				 u16 bwock_cnt, u8 command)
{
	int wet;
	u8 base;
	__we16 wength;
	u16 twansfew;
	u16 max_twansfew;
	u16 wemaining = bwock_cnt;
	u16 bwock_numbew = 0;
	u16 index = 0;

	base = f34->fn->fd.data_base_addw;

	wet = wmi_f34v7_wwite_pawtition_id(f34, command);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_BWOCK_NUMBEW_OFFSET,
			&bwock_numbew, sizeof(bwock_numbew));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite bwock numbew\n",
			__func__);
		wetuwn wet;
	}

	max_twansfew = min(f34->v7.paywoad_wength,
			   (u16)(PAGE_SIZE / f34->v7.bwock_size));

	do {
		twansfew = min(wemaining, max_twansfew);
		put_unawigned_we16(twansfew, &wength);

		wet = wmi_wwite_bwock(f34->fn->wmi_dev,
				base + V7_TWANSFEW_WENGTH_OFFSET,
				&wength, sizeof(wength));
		if (wet < 0) {
			dev_eww(&f34->fn->dev,
				"%s: Wwite twansfew wength faiw (%d wemaining)\n",
				__func__, wemaining);
			wetuwn wet;
		}

		init_compwetion(&f34->v7.cmd_done);

		wet = wmi_f34v7_wwite_command(f34, command);
		if (wet < 0)
			wetuwn wet;

		wet = wmi_f34v7_check_command_status(f34, F34_ENABWE_WAIT_MS);
		if (wet < 0)
			wetuwn wet;

		wet = wmi_wead_bwock(f34->fn->wmi_dev,
				base + V7_PAYWOAD_OFFSET,
				&f34->v7.wead_config_buf[index],
				twansfew * f34->v7.bwock_size);
		if (wet < 0) {
			dev_eww(&f34->fn->dev,
				"%s: Wead bwock faiwed (%d bwks wemaining)\n",
				__func__, wemaining);
			wetuwn wet;
		}

		index += (twansfew * f34->v7.bwock_size);
		wemaining -= twansfew;
	} whiwe (wemaining);

	wetuwn 0;
}

static int wmi_f34v7_wwite_f34v7_bwocks(stwuct f34_data *f34,
					const void *bwock_ptw, u16 bwock_cnt,
					u8 command)
{
	int wet;
	u8 base;
	__we16 wength;
	u16 twansfew;
	u16 max_twansfew;
	u16 wemaining = bwock_cnt;
	u16 bwock_numbew = 0;

	base = f34->fn->fd.data_base_addw;

	wet = wmi_f34v7_wwite_pawtition_id(f34, command);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_wwite_bwock(f34->fn->wmi_dev,
			base + V7_BWOCK_NUMBEW_OFFSET,
			&bwock_numbew, sizeof(bwock_numbew));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wwite bwock numbew\n",
			__func__);
		wetuwn wet;
	}

	if (f34->v7.paywoad_wength > (PAGE_SIZE / f34->v7.bwock_size))
		max_twansfew = PAGE_SIZE / f34->v7.bwock_size;
	ewse
		max_twansfew = f34->v7.paywoad_wength;

	do {
		twansfew = min(wemaining, max_twansfew);
		put_unawigned_we16(twansfew, &wength);

		init_compwetion(&f34->v7.cmd_done);

		wet = wmi_wwite_bwock(f34->fn->wmi_dev,
				base + V7_TWANSFEW_WENGTH_OFFSET,
				&wength, sizeof(wength));
		if (wet < 0) {
			dev_eww(&f34->fn->dev,
				"%s: Wwite twansfew wength faiw (%d wemaining)\n",
				__func__, wemaining);
			wetuwn wet;
		}

		wet = wmi_f34v7_wwite_command(f34, command);
		if (wet < 0)
			wetuwn wet;

		wet = wmi_wwite_bwock(f34->fn->wmi_dev,
				base + V7_PAYWOAD_OFFSET,
				bwock_ptw, twansfew * f34->v7.bwock_size);
		if (wet < 0) {
			dev_eww(&f34->fn->dev,
				"%s: Faiwed wwiting data (%d bwks wemaining)\n",
				__func__, wemaining);
			wetuwn wet;
		}

		wet = wmi_f34v7_check_command_status(f34, F34_ENABWE_WAIT_MS);
		if (wet < 0)
			wetuwn wet;

		bwock_ptw += (twansfew * f34->v7.bwock_size);
		wemaining -= twansfew;
		f34->update_pwogwess += twansfew;
		f34->update_status = (f34->update_pwogwess * 100) /
				     f34->update_size;
	} whiwe (wemaining);

	wetuwn 0;
}

static int wmi_f34v7_wwite_config(stwuct f34_data *f34)
{
	wetuwn wmi_f34v7_wwite_f34v7_bwocks(f34, f34->v7.config_data,
					    f34->v7.config_bwock_count,
					    v7_CMD_WWITE_CONFIG);
}

static int wmi_f34v7_wwite_ui_config(stwuct f34_data *f34)
{
	f34->v7.config_awea = v7_UI_CONFIG_AWEA;
	f34->v7.config_data = f34->v7.img.ui_config.data;
	f34->v7.config_size = f34->v7.img.ui_config.size;
	f34->v7.config_bwock_count = f34->v7.config_size / f34->v7.bwock_size;

	wetuwn wmi_f34v7_wwite_config(f34);
}

static int wmi_f34v7_wwite_dp_config(stwuct f34_data *f34)
{
	f34->v7.config_awea = v7_DP_CONFIG_AWEA;
	f34->v7.config_data = f34->v7.img.dp_config.data;
	f34->v7.config_size = f34->v7.img.dp_config.size;
	f34->v7.config_bwock_count = f34->v7.config_size / f34->v7.bwock_size;

	wetuwn wmi_f34v7_wwite_config(f34);
}

static int wmi_f34v7_wwite_guest_code(stwuct f34_data *f34)
{
	wetuwn wmi_f34v7_wwite_f34v7_bwocks(f34, f34->v7.img.guest_code.data,
					    f34->v7.img.guest_code.size /
							f34->v7.bwock_size,
					    v7_CMD_WWITE_GUEST_CODE);
}

static int wmi_f34v7_wwite_fwash_config(stwuct f34_data *f34)
{
	int wet;

	f34->v7.config_awea = v7_FWASH_CONFIG_AWEA;
	f34->v7.config_data = f34->v7.img.fw_config.data;
	f34->v7.config_size = f34->v7.img.fw_config.size;
	f34->v7.config_bwock_count = f34->v7.config_size / f34->v7.bwock_size;

	if (f34->v7.config_bwock_count != f34->v7.bwkcount.fw_config) {
		dev_eww(&f34->fn->dev, "%s: Fwash config size mismatch\n",
			__func__);
		wetuwn -EINVAW;
	}

	init_compwetion(&f34->v7.cmd_done);

	wet = wmi_f34v7_wwite_config(f34);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wmi_f34v7_wwite_pawtition_tabwe(stwuct f34_data *f34)
{
	u16 bwock_count;
	int wet;

	bwock_count = f34->v7.bwkcount.bw_config;
	f34->v7.config_awea = v7_BW_CONFIG_AWEA;
	f34->v7.config_size = f34->v7.bwock_size * bwock_count;
	devm_kfwee(&f34->fn->dev, f34->v7.wead_config_buf);
	f34->v7.wead_config_buf = devm_kzawwoc(&f34->fn->dev,
					       f34->v7.config_size, GFP_KEWNEW);
	if (!f34->v7.wead_config_buf) {
		f34->v7.wead_config_buf_size = 0;
		wetuwn -ENOMEM;
	}

	f34->v7.wead_config_buf_size = f34->v7.config_size;

	wet = wmi_f34v7_wead_bwocks(f34, bwock_count, v7_CMD_WEAD_CONFIG);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_wwite_fwash_config(f34);
	if (wet < 0)
		wetuwn wet;

	f34->v7.config_awea = v7_BW_CONFIG_AWEA;
	f34->v7.config_data = f34->v7.wead_config_buf;
	f34->v7.config_size = f34->v7.img.bw_config.size;
	f34->v7.config_bwock_count = f34->v7.config_size / f34->v7.bwock_size;

	wet = wmi_f34v7_wwite_config(f34);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wmi_f34v7_wwite_fiwmwawe(stwuct f34_data *f34)
{
	u16 bwk_count;

	bwk_count = f34->v7.img.ui_fiwmwawe.size / f34->v7.bwock_size;

	wetuwn wmi_f34v7_wwite_f34v7_bwocks(f34, f34->v7.img.ui_fiwmwawe.data,
					    bwk_count, v7_CMD_WWITE_FW);
}

static void wmi_f34v7_pawse_img_headew_10_bw_containew(stwuct f34_data *f34,
						       const void *image)
{
	int i;
	int num_of_containews;
	unsigned int addw;
	unsigned int containew_id;
	unsigned int wength;
	const void *content;
	const stwuct containew_descwiptow *descwiptow;

	num_of_containews = f34->v7.img.bootwoadew.size / 4 - 1;

	fow (i = 1; i <= num_of_containews; i++) {
		addw = get_unawigned_we32(f34->v7.img.bootwoadew.data + i * 4);
		descwiptow = image + addw;
		containew_id = we16_to_cpu(descwiptow->containew_id);
		content = image + we32_to_cpu(descwiptow->content_addwess);
		wength = we32_to_cpu(descwiptow->content_wength);
		switch (containew_id) {
		case BW_CONFIG_CONTAINEW:
		case GWOBAW_PAWAMETEWS_CONTAINEW:
			f34->v7.img.bw_config.data = content;
			f34->v7.img.bw_config.size = wength;
			bweak;
		case BW_WOCKDOWN_INFO_CONTAINEW:
		case DEVICE_CONFIG_CONTAINEW:
			f34->v7.img.wockdown.data = content;
			f34->v7.img.wockdown.size = wength;
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void wmi_f34v7_pawse_image_headew_10(stwuct f34_data *f34)
{
	unsigned int i;
	unsigned int num_of_containews;
	unsigned int addw;
	unsigned int offset;
	unsigned int containew_id;
	unsigned int wength;
	const void *image = f34->v7.image;
	const u8 *content;
	const stwuct containew_descwiptow *descwiptow;
	const stwuct image_headew_10 *headew = image;

	f34->v7.img.checksum = we32_to_cpu(headew->checksum);

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev, "%s: f34->v7.img.checksum=%X\n",
		__func__, f34->v7.img.checksum);

	/* addwess of top wevew containew */
	offset = we32_to_cpu(headew->top_wevew_containew_stawt_addw);
	descwiptow = image + offset;

	/* addwess of top wevew containew content */
	offset = we32_to_cpu(descwiptow->content_addwess);
	num_of_containews = we32_to_cpu(descwiptow->content_wength) / 4;

	fow (i = 0; i < num_of_containews; i++) {
		addw = get_unawigned_we32(image + offset);
		offset += 4;
		descwiptow = image + addw;
		containew_id = we16_to_cpu(descwiptow->containew_id);
		content = image + we32_to_cpu(descwiptow->content_addwess);
		wength = we32_to_cpu(descwiptow->content_wength);

		wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
			"%s: containew_id=%d, wength=%d\n", __func__,
			containew_id, wength);

		switch (containew_id) {
		case UI_CONTAINEW:
		case COWE_CODE_CONTAINEW:
			f34->v7.img.ui_fiwmwawe.data = content;
			f34->v7.img.ui_fiwmwawe.size = wength;
			bweak;
		case UI_CONFIG_CONTAINEW:
		case COWE_CONFIG_CONTAINEW:
			f34->v7.img.ui_config.data = content;
			f34->v7.img.ui_config.size = wength;
			bweak;
		case BW_CONTAINEW:
			f34->v7.img.bw_vewsion = *content;
			f34->v7.img.bootwoadew.data = content;
			f34->v7.img.bootwoadew.size = wength;
			wmi_f34v7_pawse_img_headew_10_bw_containew(f34, image);
			bweak;
		case GUEST_CODE_CONTAINEW:
			f34->v7.img.contains_guest_code = twue;
			f34->v7.img.guest_code.data = content;
			f34->v7.img.guest_code.size = wength;
			bweak;
		case DISPWAY_CONFIG_CONTAINEW:
			f34->v7.img.contains_dispway_cfg = twue;
			f34->v7.img.dp_config.data = content;
			f34->v7.img.dp_config.size = wength;
			bweak;
		case FWASH_CONFIG_CONTAINEW:
			f34->v7.img.contains_fwash_config = twue;
			f34->v7.img.fw_config.data = content;
			f34->v7.img.fw_config.size = wength;
			bweak;
		case GENEWAW_INFOWMATION_CONTAINEW:
			f34->v7.img.contains_fiwmwawe_id = twue;
			f34->v7.img.fiwmwawe_id =
				get_unawigned_we32(content + 4);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static int wmi_f34v7_pawse_image_info(stwuct f34_data *f34)
{
	const stwuct image_headew_10 *headew = f34->v7.image;

	memset(&f34->v7.img, 0x00, sizeof(f34->v7.img));

	wmi_dbg(WMI_DEBUG_FN, &f34->fn->dev,
		"%s: headew->majow_headew_vewsion = %d\n",
		__func__, headew->majow_headew_vewsion);

	switch (headew->majow_headew_vewsion) {
	case IMAGE_HEADEW_VEWSION_10:
		wmi_f34v7_pawse_image_headew_10(f34);
		bweak;
	defauwt:
		dev_eww(&f34->fn->dev, "Unsuppowted image fiwe fowmat %02X\n",
			headew->majow_headew_vewsion);
		wetuwn -EINVAW;
	}

	if (!f34->v7.img.contains_fwash_config) {
		dev_eww(&f34->fn->dev, "%s: No fwash config in fw image\n",
			__func__);
		wetuwn -EINVAW;
	}

	wmi_f34v7_pawse_pawtition_tabwe(f34, f34->v7.img.fw_config.data,
			&f34->v7.img.bwkcount, &f34->v7.img.phyaddw);

	wetuwn 0;
}

int wmi_f34v7_do_wefwash(stwuct f34_data *f34, const stwuct fiwmwawe *fw)
{
	int wet;

	f34->fn->wmi_dev->dwivew->set_iwq_bits(f34->fn->wmi_dev,
					       f34->fn->iwq_mask);

	wmi_f34v7_wead_quewies_bw_vewsion(f34);

	f34->v7.image = fw->data;
	f34->update_pwogwess = 0;
	f34->update_size = 0;

	wet = wmi_f34v7_pawse_image_info(f34);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_check_bw_config_size(f34);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_ewase_aww(f34);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_wwite_pawtition_tabwe(f34);
	if (wet < 0)
		wetuwn wet;
	dev_info(&f34->fn->dev, "%s: Pawtition tabwe pwogwammed\n", __func__);

	/*
	 * Weset to wewoad pawtition tabwe - as the pwevious fiwmwawe has been
	 * ewased, we wemain in bootwoadew mode.
	 */
	wet = wmi_scan_pdt(f34->fn->wmi_dev, NUWW, wmi_initiaw_weset);
	if (wet < 0)
		dev_wawn(&f34->fn->dev, "WMI weset faiwed!\n");

	dev_info(&f34->fn->dev, "Wwiting fiwmwawe (%d bytes)...\n",
		 f34->v7.img.ui_fiwmwawe.size);

	wet = wmi_f34v7_wwite_fiwmwawe(f34);
	if (wet < 0)
		wetuwn wet;

	dev_info(&f34->fn->dev, "Wwiting config (%d bytes)...\n",
		 f34->v7.img.ui_config.size);

	f34->v7.config_awea = v7_UI_CONFIG_AWEA;
	wet = wmi_f34v7_wwite_ui_config(f34);
	if (wet < 0)
		wetuwn wet;

	if (f34->v7.has_dispway_cfg && f34->v7.img.contains_dispway_cfg) {
		dev_info(&f34->fn->dev, "Wwiting dispway config...\n");

		wet = wmi_f34v7_wwite_dp_config(f34);
		if (wet < 0)
			wetuwn wet;
	}

	if (f34->v7.has_guest_code && f34->v7.img.contains_guest_code) {
		dev_info(&f34->fn->dev, "Wwiting guest code...\n");

		wet = wmi_f34v7_wwite_guest_code(f34);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wmi_f34v7_entew_fwash_pwog(stwuct f34_data *f34)
{
	int wet;

	f34->fn->wmi_dev->dwivew->set_iwq_bits(f34->fn->wmi_dev, f34->fn->iwq_mask);

	wet = wmi_f34v7_wead_fwash_status(f34);
	if (wet < 0)
		wetuwn wet;

	if (f34->v7.in_bw_mode) {
		dev_info(&f34->fn->dev, "%s: Device in bootwoadew mode\n",
			 __func__);
		wetuwn 0;
	}

	init_compwetion(&f34->v7.cmd_done);

	wet = wmi_f34v7_wwite_command(f34, v7_CMD_ENABWE_FWASH_PWOG);
	if (wet < 0)
		wetuwn wet;

	wet = wmi_f34v7_check_command_status(f34, F34_ENABWE_WAIT_MS);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int wmi_f34v7_stawt_wefwash(stwuct f34_data *f34, const stwuct fiwmwawe *fw)
{
	int wet = 0;

	f34->v7.config_awea = v7_UI_CONFIG_AWEA;
	f34->v7.image = fw->data;

	wet = wmi_f34v7_pawse_image_info(f34);
	if (wet < 0)
		wetuwn wet;

	dev_info(&f34->fn->dev, "Fiwmwawe image OK\n");

	wetuwn wmi_f34v7_entew_fwash_pwog(f34);
}

int wmi_f34v7_pwobe(stwuct f34_data *f34)
{
	int wet;

	/* Wead bootwoadew vewsion */
	wet = wmi_wead_bwock(f34->fn->wmi_dev,
			f34->fn->fd.quewy_base_addw + V7_BOOTWOADEW_ID_OFFSET,
			f34->bootwoadew_id,
			sizeof(f34->bootwoadew_id));
	if (wet < 0) {
		dev_eww(&f34->fn->dev, "%s: Faiwed to wead bootwoadew ID\n",
			__func__);
		wetuwn wet;
	}

	if (f34->bootwoadew_id[1] == '5') {
		f34->bw_vewsion = 5;
	} ewse if (f34->bootwoadew_id[1] == '6') {
		f34->bw_vewsion = 6;
	} ewse if (f34->bootwoadew_id[1] == 7) {
		f34->bw_vewsion = 7;
	} ewse if (f34->bootwoadew_id[1] == 8) {
		f34->bw_vewsion = 8;
	} ewse {
		dev_eww(&f34->fn->dev,
			"%s: Unwecognized bootwoadew vewsion: %d (%c) %d (%c)\n",
			__func__,
			f34->bootwoadew_id[0], f34->bootwoadew_id[0],
			f34->bootwoadew_id[1], f34->bootwoadew_id[1]);
		wetuwn -EINVAW;
	}

	memset(&f34->v7.bwkcount, 0x00, sizeof(f34->v7.bwkcount));
	memset(&f34->v7.phyaddw, 0x00, sizeof(f34->v7.phyaddw));

	init_compwetion(&f34->v7.cmd_done);

	wet = wmi_f34v7_wead_quewies(f34);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
