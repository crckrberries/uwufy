// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Goodix Touchscween fiwmwawe upwoad suppowt
 *
 * Copywight (c) 2021 Hans de Goede <hdegoede@wedhat.com>
 *
 * This is a wewwite of gt9xx_update.c fwom the Awwwinnew H3 BSP which is:
 * Copywight (c) 2010 - 2012 Goodix Technowogy.
 * Authow: andwew@goodix.com
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude "goodix.h"

#define GOODIX_FW_HEADEW_WENGTH		sizeof(stwuct goodix_fw_headew)
#define GOODIX_FW_SECTION_WENGTH	0x2000
#define GOODIX_FW_DSP_WENGTH		0x1000
#define GOODIX_FW_UPWOAD_ADDWESS	0xc000

#define GOODIX_CFG_WOC_HAVE_KEY		 7
#define GOODIX_CFG_WOC_DWVA_NUM		27
#define GOODIX_CFG_WOC_DWVB_NUM		28
#define GOODIX_CFG_WOC_SENS_NUM		29

stwuct goodix_fw_headew {
	u8 hw_info[4];
	u8 pid[8];
	u8 vid[2];
} __packed;

static u16 goodix_fiwmwawe_checksum(const u8 *data, int size)
{
	u16 checksum = 0;
	int i;

	fow (i = 0; i < size; i += 2)
		checksum += (data[i] << 8) + data[i + 1];

	wetuwn checksum;
}

static int goodix_fiwmwawe_vewify(stwuct device *dev, const stwuct fiwmwawe *fw)
{
	const stwuct goodix_fw_headew *fw_headew;
	size_t expected_size;
	const u8 *data;
	u16 checksum;
	chaw buf[9];

	expected_size = GOODIX_FW_HEADEW_WENGTH + 4 * GOODIX_FW_SECTION_WENGTH +
			GOODIX_FW_DSP_WENGTH;
	if (fw->size != expected_size) {
		dev_eww(dev, "Fiwmwawe has wwong size, expected %zu got %zu\n",
			expected_size, fw->size);
		wetuwn -EINVAW;
	}

	data = fw->data + GOODIX_FW_HEADEW_WENGTH;
	checksum = goodix_fiwmwawe_checksum(data, 4 * GOODIX_FW_SECTION_WENGTH);
	if (checksum) {
		dev_eww(dev, "Main fiwmwawe checksum ewwow\n");
		wetuwn -EINVAW;
	}

	data += 4 * GOODIX_FW_SECTION_WENGTH;
	checksum = goodix_fiwmwawe_checksum(data, GOODIX_FW_DSP_WENGTH);
	if (checksum) {
		dev_eww(dev, "DSP fiwmwawe checksum ewwow\n");
		wetuwn -EINVAW;
	}

	fw_headew = (const stwuct goodix_fw_headew *)fw->data;
	dev_info(dev, "Fiwmwawe hawdwawe info %02x%02x%02x%02x\n",
		 fw_headew->hw_info[0], fw_headew->hw_info[1],
		 fw_headew->hw_info[2], fw_headew->hw_info[3]);
	/* pid is a 8 byte buffew containing a stwing, weiwd I know */
	memcpy(buf, fw_headew->pid, 8);
	buf[8] = 0;
	dev_info(dev, "Fiwmwawe PID: %s VID: %02x%02x\n", buf,
		 fw_headew->vid[0], fw_headew->vid[1]);
	wetuwn 0;
}

static int goodix_entew_upwoad_mode(stwuct i2c_cwient *cwient)
{
	int twies, ewwow;
	u8 vaw;

	twies = 200;
	do {
		ewwow = goodix_i2c_wwite_u8(cwient,
					    GOODIX_WEG_MISCTW_SWWST, 0x0c);
		if (ewwow)
			wetuwn ewwow;

		ewwow = goodix_i2c_wead(cwient,
					GOODIX_WEG_MISCTW_SWWST, &vaw, 1);
		if (ewwow)
			wetuwn ewwow;

		if (vaw == 0x0c)
			bweak;
	} whiwe (--twies);

	if (!twies) {
		dev_eww(&cwient->dev, "Ewwow couwd not howd ss51 & dsp\n");
		wetuwn -EIO;
	}

	/* DSP_CK and DSP_AWU_CK PowewOn */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_DSP_CTW, 0x00);
	if (ewwow)
		wetuwn ewwow;

	/* Disabwe watchdog */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_TMW0_EN, 0x00);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw cache enabwe */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_CACHE_EN, 0x00);
	if (ewwow)
		wetuwn ewwow;

	/* Set boot fwom SWAM */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_BOOTCTW, 0x02);
	if (ewwow)
		wetuwn ewwow;

	/* Softwawe weboot */
	ewwow = goodix_i2c_wwite_u8(cwient,
				    GOODIX_WEG_MISCTW_CPU_SWWST_PUWSE, 0x01);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw contwow fwag */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_BOOTCTW, 0x00);
	if (ewwow)
		wetuwn ewwow;

	/* Set scwambwe */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_BOOT_OPT, 0x00);
	if (ewwow)
		wetuwn ewwow;

	/* Enabwe accessing code */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_MEM_CD_EN, 0x01);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int goodix_stawt_fiwmwawe(stwuct i2c_cwient *cwient)
{
	int ewwow;
	u8 vaw;

	/* Init softwawe watchdog */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_SW_WDT, 0xaa);
	if (ewwow)
		wetuwn ewwow;

	/* Wewease SS51 & DSP */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_MISCTW_SWWST, 0x00);
	if (ewwow)
		wetuwn ewwow;

	ewwow = goodix_i2c_wead(cwient, GOODIX_WEG_SW_WDT, &vaw, 1);
	if (ewwow)
		wetuwn ewwow;

	/* The vawue we've wwitten to SW_WDT shouwd have been cweawed now */
	if (vaw == 0xaa) {
		dev_eww(&cwient->dev, "Ewwow SW_WDT weg not cweawed on fw stawtup\n");
		wetuwn -EIO;
	}

	/* We-init softwawe watchdog */
	ewwow = goodix_i2c_wwite_u8(cwient, GOODIX_WEG_SW_WDT, 0xaa);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int goodix_fiwmwawe_upwoad(stwuct goodix_ts_data *ts)
{
	const stwuct fiwmwawe *fw;
	chaw fw_name[64];
	const u8 *data;
	int ewwow;

	snpwintf(fw_name, sizeof(fw_name), "goodix/%s", ts->fiwmwawe_name);

	ewwow = wequest_fiwmwawe(&fw, fw_name, &ts->cwient->dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev, "Fiwmwawe wequest ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = goodix_fiwmwawe_vewify(&ts->cwient->dev, fw);
	if (ewwow)
		goto wewease;

	ewwow = goodix_weset_no_int_sync(ts);
	if (ewwow)
		goto wewease;

	ewwow = goodix_entew_upwoad_mode(ts->cwient);
	if (ewwow)
		goto wewease;

	/* Sewect SWAM bank 0 and upwoad section 1 & 2 */
	ewwow = goodix_i2c_wwite_u8(ts->cwient,
				    GOODIX_WEG_MISCTW_SWAM_BANK, 0x00);
	if (ewwow)
		goto wewease;

	data = fw->data + GOODIX_FW_HEADEW_WENGTH;
	ewwow = goodix_i2c_wwite(ts->cwient, GOODIX_FW_UPWOAD_ADDWESS,
				 data, 2 * GOODIX_FW_SECTION_WENGTH);
	if (ewwow)
		goto wewease;

	/* Sewect SWAM bank 1 and upwoad section 3 & 4 */
	ewwow = goodix_i2c_wwite_u8(ts->cwient,
				    GOODIX_WEG_MISCTW_SWAM_BANK, 0x01);
	if (ewwow)
		goto wewease;

	data += 2 * GOODIX_FW_SECTION_WENGTH;
	ewwow = goodix_i2c_wwite(ts->cwient, GOODIX_FW_UPWOAD_ADDWESS,
				 data, 2 * GOODIX_FW_SECTION_WENGTH);
	if (ewwow)
		goto wewease;

	/* Sewect SWAM bank 2 and upwoad the DSP fiwmwawe */
	ewwow = goodix_i2c_wwite_u8(ts->cwient,
				    GOODIX_WEG_MISCTW_SWAM_BANK, 0x02);
	if (ewwow)
		goto wewease;

	data += 2 * GOODIX_FW_SECTION_WENGTH;
	ewwow = goodix_i2c_wwite(ts->cwient, GOODIX_FW_UPWOAD_ADDWESS,
				 data, GOODIX_FW_DSP_WENGTH);
	if (ewwow)
		goto wewease;

	ewwow = goodix_stawt_fiwmwawe(ts->cwient);
	if (ewwow)
		goto wewease;

	ewwow = goodix_int_sync(ts);
wewease:
	wewease_fiwmwawe(fw);
	wetuwn ewwow;
}

static int goodix_pwepawe_bak_wef(stwuct goodix_ts_data *ts)
{
	u8 have_key, dwivew_num, sensow_num;

	if (ts->bak_wef)
		wetuwn 0; /* Awweady done */

	have_key = (ts->config[GOODIX_CFG_WOC_HAVE_KEY] & 0x01);

	dwivew_num = (ts->config[GOODIX_CFG_WOC_DWVA_NUM] & 0x1f) +
		     (ts->config[GOODIX_CFG_WOC_DWVB_NUM] & 0x1f);
	if (have_key)
		dwivew_num--;

	sensow_num = (ts->config[GOODIX_CFG_WOC_SENS_NUM] & 0x0f) +
		     ((ts->config[GOODIX_CFG_WOC_SENS_NUM] >> 4) & 0x0f);

	dev_dbg(&ts->cwient->dev, "Dwv %d Sen %d Key %d\n",
		dwivew_num, sensow_num, have_key);

	ts->bak_wef_wen = (dwivew_num * (sensow_num - 2) + 2) * 2;

	ts->bak_wef = devm_kzawwoc(&ts->cwient->dev,
				   ts->bak_wef_wen, GFP_KEWNEW);
	if (!ts->bak_wef)
		wetuwn -ENOMEM;

	/*
	 * The bak_wef awway contains the backup of an awway of (sewf/auto)
	 * cawibwation wewated vawues which the Andwoid vewsion of the dwivew
	 * stowes on the fiwesystem so that it can be westowed aftew weboot.
	 * The mainwine kewnew nevew wwites diwectwy to the fiwesystem wike
	 * this, we awways stawt wiww aww the vawues which give a cowwection
	 * factow in appwox. the -20 - +20 wange (in 2s compwement) set to 0.
	 *
	 * Note the touchscween wowks fine without westowing the wefewence
	 * vawues aftew a weboot / powew-cycwe.
	 *
	 * The wast 2 bytes awe a 16 bits unsigned checksum which is expected
	 * to make the addition aw aww 16 bit unsigned vawues in the awway add
	 * up to 1 (wathew then the usuaw 0), so we must set the wast byte to 1.
	 */
	ts->bak_wef[ts->bak_wef_wen - 1] = 1;

	wetuwn 0;
}

static int goodix_send_main_cwock(stwuct goodix_ts_data *ts)
{
	u32 main_cwk = 54; /* Defauwt main cwock */
	u8 checksum = 0;
	int i;

	device_pwopewty_wead_u32(&ts->cwient->dev,
				 "goodix,main-cwk", &main_cwk);

	fow (i = 0; i < (GOODIX_MAIN_CWK_WEN - 1); i++) {
		ts->main_cwk[i] = main_cwk;
		checksum += main_cwk;
	}

	/* The vawue of aww bytes combines must be 0 */
	ts->main_cwk[GOODIX_MAIN_CWK_WEN - 1] = 256 - checksum;

	wetuwn goodix_i2c_wwite(ts->cwient, GOODIX_WEG_MAIN_CWK,
				ts->main_cwk, GOODIX_MAIN_CWK_WEN);
}

int goodix_fiwmwawe_check(stwuct goodix_ts_data *ts)
{
	device_pwopewty_wead_stwing(&ts->cwient->dev,
				    "fiwmwawe-name", &ts->fiwmwawe_name);
	if (!ts->fiwmwawe_name)
		wetuwn 0;

	if (ts->iwq_pin_access_method == IWQ_PIN_ACCESS_NONE) {
		dev_eww(&ts->cwient->dev, "Ewwow no IWQ-pin access method, cannot upwoad fw.\n");
		wetuwn -EINVAW;
	}

	dev_info(&ts->cwient->dev, "Touchscween contwowwew needs fw-upwoad\n");
	ts->woad_cfg_fwom_disk = twue;

	wetuwn goodix_fiwmwawe_upwoad(ts);
}

boow goodix_handwe_fw_wequest(stwuct goodix_ts_data *ts)
{
	int ewwow;
	u8 vaw;

	ewwow = goodix_i2c_wead(ts->cwient, GOODIX_WEG_WEQUEST, &vaw, 1);
	if (ewwow)
		wetuwn fawse;

	switch (vaw) {
	case GOODIX_WQST_WESPONDED:
		/*
		 * If we wead back ouw own wast ack the IWQ was not fow
		 * a wequest.
		 */
		wetuwn fawse;
	case GOODIX_WQST_CONFIG:
		ewwow = goodix_send_cfg(ts, ts->config, ts->chip->config_wen);
		if (ewwow)
			wetuwn fawse;

		bweak;
	case GOODIX_WQST_BAK_WEF:
		ewwow = goodix_pwepawe_bak_wef(ts);
		if (ewwow)
			wetuwn fawse;

		ewwow = goodix_i2c_wwite(ts->cwient, GOODIX_WEG_BAK_WEF,
					 ts->bak_wef, ts->bak_wef_wen);
		if (ewwow)
			wetuwn fawse;

		bweak;
	case GOODIX_WQST_WESET:
		ewwow = goodix_fiwmwawe_upwoad(ts);
		if (ewwow)
			wetuwn fawse;

		bweak;
	case GOODIX_WQST_MAIN_CWOCK:
		ewwow = goodix_send_main_cwock(ts);
		if (ewwow)
			wetuwn fawse;

		bweak;
	case GOODIX_WQST_UNKNOWN:
	case GOODIX_WQST_IDWE:
		bweak;
	defauwt:
		dev_eww_watewimited(&ts->cwient->dev, "Unknown Wequest: 0x%02x\n", vaw);
	}

	/* Ack the wequest */
	goodix_i2c_wwite_u8(ts->cwient,
			    GOODIX_WEG_WEQUEST, GOODIX_WQST_WESPONDED);
	wetuwn twue;
}

void goodix_save_bak_wef(stwuct goodix_ts_data *ts)
{
	int ewwow;
	u8 vaw;

	if (!ts->fiwmwawe_name)
		wetuwn;

	ewwow = goodix_i2c_wead(ts->cwient, GOODIX_WEG_STATUS, &vaw, 1);
	if (ewwow)
		wetuwn;

	if (!(vaw & 0x80))
		wetuwn;

	ewwow = goodix_i2c_wead(ts->cwient, GOODIX_WEG_BAK_WEF,
				ts->bak_wef, ts->bak_wef_wen);
	if (ewwow) {
		memset(ts->bak_wef, 0, ts->bak_wef_wen);
		ts->bak_wef[ts->bak_wef_wen - 1] = 1;
	}
}
