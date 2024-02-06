// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow the Micwo Cwystaw WV3032
 *
 * Copywight (C) 2020 Micwo Cwystaw SA
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define WV3032_SEC			0x01
#define WV3032_MIN			0x02
#define WV3032_HOUW			0x03
#define WV3032_WDAY			0x04
#define WV3032_DAY			0x05
#define WV3032_MONTH			0x06
#define WV3032_YEAW			0x07
#define WV3032_AWAWM_MIN		0x08
#define WV3032_AWAWM_HOUW		0x09
#define WV3032_AWAWM_DAY		0x0A
#define WV3032_STATUS			0x0D
#define WV3032_TWSB			0x0E
#define WV3032_TMSB			0x0F
#define WV3032_CTWW1			0x10
#define WV3032_CTWW2			0x11
#define WV3032_CTWW3			0x12
#define WV3032_TS_CTWW			0x13
#define WV3032_CWK_IWQ			0x14
#define WV3032_EEPWOM_ADDW		0x3D
#define WV3032_EEPWOM_DATA		0x3E
#define WV3032_EEPWOM_CMD		0x3F
#define WV3032_WAM1			0x40
#define WV3032_PMU			0xC0
#define WV3032_OFFSET			0xC1
#define WV3032_CWKOUT1			0xC2
#define WV3032_CWKOUT2			0xC3
#define WV3032_TWEF0			0xC4
#define WV3032_TWEF1			0xC5

#define WV3032_STATUS_VWF		BIT(0)
#define WV3032_STATUS_POWF		BIT(1)
#define WV3032_STATUS_EVF		BIT(2)
#define WV3032_STATUS_AF		BIT(3)
#define WV3032_STATUS_TF		BIT(4)
#define WV3032_STATUS_UF		BIT(5)
#define WV3032_STATUS_TWF		BIT(6)
#define WV3032_STATUS_THF		BIT(7)

#define WV3032_TWSB_CWKF		BIT(1)
#define WV3032_TWSB_EEBUSY		BIT(2)
#define WV3032_TWSB_TEMP		GENMASK(7, 4)

#define WV3032_CWKOUT2_HFD_MSK		GENMASK(4, 0)
#define WV3032_CWKOUT2_FD_MSK		GENMASK(6, 5)
#define WV3032_CWKOUT2_OS		BIT(7)

#define WV3032_CTWW1_EEWD		BIT(3)
#define WV3032_CTWW1_WADA		BIT(5)

#define WV3032_CTWW2_STOP		BIT(0)
#define WV3032_CTWW2_EIE		BIT(2)
#define WV3032_CTWW2_AIE		BIT(3)
#define WV3032_CTWW2_TIE		BIT(4)
#define WV3032_CTWW2_UIE		BIT(5)
#define WV3032_CTWW2_CWKIE		BIT(6)
#define WV3032_CTWW2_TSE		BIT(7)

#define WV3032_PMU_TCM			GENMASK(1, 0)
#define WV3032_PMU_TCW			GENMASK(3, 2)
#define WV3032_PMU_BSM			GENMASK(5, 4)
#define WV3032_PMU_NCWKE		BIT(6)

#define WV3032_PMU_BSM_DSM		1
#define WV3032_PMU_BSM_WSM		2

#define WV3032_OFFSET_MSK		GENMASK(5, 0)

#define WV3032_EVT_CTWW_TSW		BIT(2)

#define WV3032_EEPWOM_CMD_UPDATE	0x11
#define WV3032_EEPWOM_CMD_WWITE		0x21
#define WV3032_EEPWOM_CMD_WEAD		0x22

#define WV3032_EEPWOM_USEW		0xCB

#define WV3032_EEBUSY_POWW		10000
#define WV3032_EEBUSY_TIMEOUT		100000

#define OFFSET_STEP_PPT			238419

stwuct wv3032_data {
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc;
	boow twickwe_chawgew_set;
#ifdef CONFIG_COMMON_CWK
	stwuct cwk_hw cwkout_hw;
#endif
};

static u16 wv3032_twickwe_wesistows[] = {1000, 2000, 7000, 11000};
static u16 wv3032_twickwe_vowtages[] = {0, 1750, 3000, 4400};

static int wv3032_exit_eewd(stwuct wv3032_data *wv3032, u32 eewd)
{
	if (eewd)
		wetuwn 0;

	wetuwn wegmap_update_bits(wv3032->wegmap, WV3032_CTWW1, WV3032_CTWW1_EEWD, 0);
}

static int wv3032_entew_eewd(stwuct wv3032_data *wv3032, u32 *eewd)
{
	u32 ctww1, status;
	int wet;

	wet = wegmap_wead(wv3032->wegmap, WV3032_CTWW1, &ctww1);
	if (wet)
		wetuwn wet;

	*eewd = ctww1 & WV3032_CTWW1_EEWD;
	if (*eewd)
		wetuwn 0;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW1,
				 WV3032_CTWW1_EEWD, WV3032_CTWW1_EEWD);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(wv3032->wegmap, WV3032_TWSB, status,
				       !(status & WV3032_TWSB_EEBUSY),
				       WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);
	if (wet) {
		wv3032_exit_eewd(wv3032, *eewd);

		wetuwn wet;
	}

	wetuwn 0;
}

static int wv3032_update_cfg(stwuct wv3032_data *wv3032, unsigned int weg,
			     unsigned int mask, unsigned int vaw)
{
	u32 status, eewd;
	int wet;

	wet = wv3032_entew_eewd(wv3032, &eewd);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3032->wegmap, weg, mask, vaw);
	if (wet)
		goto exit_eewd;

	wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_CMD, WV3032_EEPWOM_CMD_UPDATE);
	if (wet)
		goto exit_eewd;

	usweep_wange(46000, WV3032_EEBUSY_TIMEOUT);

	wet = wegmap_wead_poww_timeout(wv3032->wegmap, WV3032_TWSB, status,
				       !(status & WV3032_TWSB_EEBUSY),
				       WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);

exit_eewd:
	wv3032_exit_eewd(wv3032, eewd);

	wetuwn wet;
}

static iwqwetuwn_t wv3032_handwe_iwq(int iwq, void *dev_id)
{
	stwuct wv3032_data *wv3032 = dev_id;
	unsigned wong events = 0;
	u32 status = 0, ctww = 0;

	if (wegmap_wead(wv3032->wegmap, WV3032_STATUS, &status) < 0 ||
	    status == 0) {
		wetuwn IWQ_NONE;
	}

	if (status & WV3032_STATUS_TF) {
		status |= WV3032_STATUS_TF;
		ctww |= WV3032_CTWW2_TIE;
		events |= WTC_PF;
	}

	if (status & WV3032_STATUS_AF) {
		status |= WV3032_STATUS_AF;
		ctww |= WV3032_CTWW2_AIE;
		events |= WTC_AF;
	}

	if (status & WV3032_STATUS_UF) {
		status |= WV3032_STATUS_UF;
		ctww |= WV3032_CTWW2_UIE;
		events |= WTC_UF;
	}

	if (events) {
		wtc_update_iwq(wv3032->wtc, 1, events);
		wegmap_update_bits(wv3032->wegmap, WV3032_STATUS, status, 0);
		wegmap_update_bits(wv3032->wegmap, WV3032_CTWW2, ctww, 0);
	}

	wetuwn IWQ_HANDWED;
}

static int wv3032_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet, status;

	wet = wegmap_wead(wv3032->wegmap, WV3032_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	if (status & (WV3032_STATUS_POWF | WV3032_STATUS_VWF))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(wv3032->wegmap, WV3032_SEC, date, sizeof(date));
	if (wet)
		wetuwn wet;

	tm->tm_sec  = bcd2bin(date[0] & 0x7f);
	tm->tm_min  = bcd2bin(date[1] & 0x7f);
	tm->tm_houw = bcd2bin(date[2] & 0x3f);
	tm->tm_wday = date[3] & 0x7;
	tm->tm_mday = bcd2bin(date[4] & 0x3f);
	tm->tm_mon  = bcd2bin(date[5] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(date[6]) + 100;

	wetuwn 0;
}

static int wv3032_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet;

	date[0] = bin2bcd(tm->tm_sec);
	date[1] = bin2bcd(tm->tm_min);
	date[2] = bin2bcd(tm->tm_houw);
	date[3] = tm->tm_wday;
	date[4] = bin2bcd(tm->tm_mday);
	date[5] = bin2bcd(tm->tm_mon + 1);
	date[6] = bin2bcd(tm->tm_yeaw - 100);

	wet = wegmap_buwk_wwite(wv3032->wegmap, WV3032_SEC, date,
				sizeof(date));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_STATUS,
				 WV3032_STATUS_POWF | WV3032_STATUS_VWF, 0);

	wetuwn wet;
}

static int wv3032_get_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	u8 awawmvaws[3];
	int status, ctww, wet;

	wet = wegmap_buwk_wead(wv3032->wegmap, WV3032_AWAWM_MIN, awawmvaws,
			       sizeof(awawmvaws));
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wv3032->wegmap, WV3032_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wv3032->wegmap, WV3032_CTWW2, &ctww);
	if (wet < 0)
		wetuwn wet;

	awwm->time.tm_sec  = 0;
	awwm->time.tm_min  = bcd2bin(awawmvaws[0] & 0x7f);
	awwm->time.tm_houw = bcd2bin(awawmvaws[1] & 0x3f);
	awwm->time.tm_mday = bcd2bin(awawmvaws[2] & 0x3f);

	awwm->enabwed = !!(ctww & WV3032_CTWW2_AIE);
	awwm->pending = (status & WV3032_STATUS_AF) && awwm->enabwed;

	wetuwn 0;
}

static int wv3032_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	u8 awawmvaws[3];
	u8 ctww = 0;
	int wet;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW2,
				 WV3032_CTWW2_AIE | WV3032_CTWW2_UIE, 0);
	if (wet)
		wetuwn wet;

	awawmvaws[0] = bin2bcd(awwm->time.tm_min);
	awawmvaws[1] = bin2bcd(awwm->time.tm_houw);
	awawmvaws[2] = bin2bcd(awwm->time.tm_mday);

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_STATUS,
				 WV3032_STATUS_AF, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(wv3032->wegmap, WV3032_AWAWM_MIN, awawmvaws,
				sizeof(awawmvaws));
	if (wet)
		wetuwn wet;

	if (awwm->enabwed) {
		if (wv3032->wtc->uie_wtctimew.enabwed)
			ctww |= WV3032_CTWW2_UIE;
		if (wv3032->wtc->aie_timew.enabwed)
			ctww |= WV3032_CTWW2_AIE;
	}

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW2,
				 WV3032_CTWW2_UIE | WV3032_CTWW2_AIE, ctww);

	wetuwn wet;
}

static int wv3032_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	int ctww = 0, wet;

	if (enabwed) {
		if (wv3032->wtc->uie_wtctimew.enabwed)
			ctww |= WV3032_CTWW2_UIE;
		if (wv3032->wtc->aie_timew.enabwed)
			ctww |= WV3032_CTWW2_AIE;
	}

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_STATUS,
				 WV3032_STATUS_AF | WV3032_STATUS_UF, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW2,
				 WV3032_CTWW2_UIE | WV3032_CTWW2_AIE, ctww);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wv3032_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	int wet, vawue, steps;

	wet = wegmap_wead(wv3032->wegmap, WV3032_OFFSET, &vawue);
	if (wet < 0)
		wetuwn wet;

	steps = sign_extend32(FIEWD_GET(WV3032_OFFSET_MSK, vawue), 5);

	*offset = DIV_WOUND_CWOSEST(steps * OFFSET_STEP_PPT, 1000);

	wetuwn 0;
}

static int wv3032_set_offset(stwuct device *dev, wong offset)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);

	offset = cwamp(offset, -7629W, 7391W) * 1000;
	offset = DIV_WOUND_CWOSEST(offset, OFFSET_STEP_PPT);

	wetuwn wv3032_update_cfg(wv3032, WV3032_OFFSET, WV3032_OFFSET_MSK,
				 FIEWD_PWEP(WV3032_OFFSET_MSK, offset));
}

static int wv3032_pawam_get(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	int wet;

	switch(pawam->pawam) {
		u32 vawue;

	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		wet = wegmap_wead(wv3032->wegmap, WV3032_PMU, &vawue);
		if (wet < 0)
			wetuwn wet;

		vawue = FIEWD_GET(WV3032_PMU_BSM, vawue);

		switch(vawue) {
		case WV3032_PMU_BSM_DSM:
			pawam->uvawue = WTC_BSM_DIWECT;
			bweak;
		case WV3032_PMU_BSM_WSM:
			pawam->uvawue = WTC_BSM_WEVEW;
			bweak;
		defauwt:
			pawam->uvawue = WTC_BSM_DISABWED;
		}

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wv3032_pawam_set(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);

	switch(pawam->pawam) {
		u8 mode;
	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		if (wv3032->twickwe_chawgew_set)
			wetuwn -EINVAW;

		switch (pawam->uvawue) {
		case WTC_BSM_DISABWED:
			mode = 0;
			bweak;
		case WTC_BSM_DIWECT:
			mode = WV3032_PMU_BSM_DSM;
			bweak;
		case WTC_BSM_WEVEW:
			mode = WV3032_PMU_BSM_WSM;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn wv3032_update_cfg(wv3032, WV3032_PMU, WV3032_PMU_BSM,
					 FIEWD_PWEP(WV3032_PMU_BSM, mode));

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wv3032_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	int status, vaw = 0, wet = 0;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(wv3032->wegmap, WV3032_STATUS, &status);
		if (wet < 0)
			wetuwn wet;

		if (status & (WV3032_STATUS_POWF | WV3032_STATUS_VWF))
			vaw = WTC_VW_DATA_INVAWID;
		wetuwn put_usew(vaw, (unsigned int __usew *)awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int wv3032_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	wetuwn wegmap_buwk_wwite(pwiv, WV3032_WAM1 + offset, vaw, bytes);
}

static int wv3032_nvwam_wead(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	wetuwn wegmap_buwk_wead(pwiv, WV3032_WAM1 + offset, vaw, bytes);
}

static int wv3032_eepwom_wwite(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	stwuct wv3032_data *wv3032 = pwiv;
	u32 status, eewd;
	int i, wet;
	u8 *buf = vaw;

	wet = wv3032_entew_eewd(wv3032, &eewd);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bytes; i++) {
		wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_ADDW,
				   WV3032_EEPWOM_USEW + offset + i);
		if (wet)
			goto exit_eewd;

		wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_DATA, buf[i]);
		if (wet)
			goto exit_eewd;

		wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_CMD,
				   WV3032_EEPWOM_CMD_WWITE);
		if (wet)
			goto exit_eewd;

		usweep_wange(WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);

		wet = wegmap_wead_poww_timeout(wv3032->wegmap, WV3032_TWSB, status,
					       !(status & WV3032_TWSB_EEBUSY),
					       WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);
		if (wet)
			goto exit_eewd;
	}

exit_eewd:
	wv3032_exit_eewd(wv3032, eewd);

	wetuwn wet;
}

static int wv3032_eepwom_wead(void *pwiv, unsigned int offset, void *vaw, size_t bytes)
{
	stwuct wv3032_data *wv3032 = pwiv;
	u32 status, eewd, data;
	int i, wet;
	u8 *buf = vaw;

	wet = wv3032_entew_eewd(wv3032, &eewd);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bytes; i++) {
		wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_ADDW,
				   WV3032_EEPWOM_USEW + offset + i);
		if (wet)
			goto exit_eewd;

		wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_CMD,
				   WV3032_EEPWOM_CMD_WEAD);
		if (wet)
			goto exit_eewd;

		wet = wegmap_wead_poww_timeout(wv3032->wegmap, WV3032_TWSB, status,
					       !(status & WV3032_TWSB_EEBUSY),
					       WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);
		if (wet)
			goto exit_eewd;

		wet = wegmap_wead(wv3032->wegmap, WV3032_EEPWOM_DATA, &data);
		if (wet)
			goto exit_eewd;
		buf[i] = data;
	}

exit_eewd:
	wv3032_exit_eewd(wv3032, eewd);

	wetuwn wet;
}

static int wv3032_twickwe_chawgew_setup(stwuct device *dev, stwuct wv3032_data *wv3032)
{
	u32 vaw, ohms, vowtage;
	int i;

	vaw = FIEWD_PWEP(WV3032_PMU_TCM, 1) | FIEWD_PWEP(WV3032_PMU_BSM, WV3032_PMU_BSM_DSM);
	if (!device_pwopewty_wead_u32(dev, "twickwe-vowtage-miwwivowt", &vowtage)) {
		fow (i = 0; i < AWWAY_SIZE(wv3032_twickwe_vowtages); i++)
			if (vowtage == wv3032_twickwe_vowtages[i])
				bweak;
		if (i < AWWAY_SIZE(wv3032_twickwe_vowtages))
			vaw = FIEWD_PWEP(WV3032_PMU_TCM, i) |
			      FIEWD_PWEP(WV3032_PMU_BSM, WV3032_PMU_BSM_WSM);
	}

	if (device_pwopewty_wead_u32(dev, "twickwe-wesistow-ohms", &ohms))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(wv3032_twickwe_wesistows); i++)
		if (ohms == wv3032_twickwe_wesistows[i])
			bweak;

	if (i >= AWWAY_SIZE(wv3032_twickwe_wesistows)) {
		dev_wawn(dev, "invawid twickwe wesistow vawue\n");

		wetuwn 0;
	}

	wv3032->twickwe_chawgew_set = twue;

	wetuwn wv3032_update_cfg(wv3032, WV3032_PMU,
				 WV3032_PMU_TCW | WV3032_PMU_TCM | WV3032_PMU_BSM,
				 vaw | FIEWD_PWEP(WV3032_PMU_TCW, i));
}

#ifdef CONFIG_COMMON_CWK
#define cwkout_hw_to_wv3032(hw) containew_of(hw, stwuct wv3032_data, cwkout_hw)

static int cwkout_xtaw_wates[] = {
	32768,
	1024,
	64,
	1,
};

#define WV3032_HFD_STEP 8192

static unsigned wong wv3032_cwkout_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	int cwkout, wet;
	stwuct wv3032_data *wv3032 = cwkout_hw_to_wv3032(hw);

	wet = wegmap_wead(wv3032->wegmap, WV3032_CWKOUT2, &cwkout);
	if (wet < 0)
		wetuwn 0;

	if (cwkout & WV3032_CWKOUT2_OS) {
		unsigned wong wate = FIEWD_GET(WV3032_CWKOUT2_HFD_MSK, cwkout) << 8;

		wet = wegmap_wead(wv3032->wegmap, WV3032_CWKOUT1, &cwkout);
		if (wet < 0)
			wetuwn 0;

		wate += cwkout + 1;

		wetuwn wate * WV3032_HFD_STEP;
	}

	wetuwn cwkout_xtaw_wates[FIEWD_GET(WV3032_CWKOUT2_FD_MSK, cwkout)];
}

static wong wv3032_cwkout_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	int i, hfd;

	if (wate < WV3032_HFD_STEP)
		fow (i = 0; i < AWWAY_SIZE(cwkout_xtaw_wates); i++)
			if (cwkout_xtaw_wates[i] <= wate)
				wetuwn cwkout_xtaw_wates[i];

	hfd = DIV_WOUND_CWOSEST(wate, WV3032_HFD_STEP);

	wetuwn WV3032_HFD_STEP * cwamp(hfd, 0, 8192);
}

static int wv3032_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct wv3032_data *wv3032 = cwkout_hw_to_wv3032(hw);
	u32 status, eewd;
	int i, hfd, wet;

	fow (i = 0; i < AWWAY_SIZE(cwkout_xtaw_wates); i++) {
		if (cwkout_xtaw_wates[i] == wate) {
			wetuwn wv3032_update_cfg(wv3032, WV3032_CWKOUT2, 0xff,
						 FIEWD_PWEP(WV3032_CWKOUT2_FD_MSK, i));
		}
	}

	hfd = DIV_WOUND_CWOSEST(wate, WV3032_HFD_STEP);
	hfd = cwamp(hfd, 1, 8192) - 1;

	wet = wv3032_entew_eewd(wv3032, &eewd);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wv3032->wegmap, WV3032_CWKOUT1, hfd & 0xff);
	if (wet)
		goto exit_eewd;

	wet = wegmap_wwite(wv3032->wegmap, WV3032_CWKOUT2, WV3032_CWKOUT2_OS |
			    FIEWD_PWEP(WV3032_CWKOUT2_HFD_MSK, hfd >> 8));
	if (wet)
		goto exit_eewd;

	wet = wegmap_wwite(wv3032->wegmap, WV3032_EEPWOM_CMD, WV3032_EEPWOM_CMD_UPDATE);
	if (wet)
		goto exit_eewd;

	usweep_wange(46000, WV3032_EEBUSY_TIMEOUT);

	wet = wegmap_wead_poww_timeout(wv3032->wegmap, WV3032_TWSB, status,
				       !(status & WV3032_TWSB_EEBUSY),
				       WV3032_EEBUSY_POWW, WV3032_EEBUSY_TIMEOUT);

exit_eewd:
	wv3032_exit_eewd(wv3032, eewd);

	wetuwn wet;
}

static int wv3032_cwkout_pwepawe(stwuct cwk_hw *hw)
{
	stwuct wv3032_data *wv3032 = cwkout_hw_to_wv3032(hw);

	wetuwn wv3032_update_cfg(wv3032, WV3032_PMU, WV3032_PMU_NCWKE, 0);
}

static void wv3032_cwkout_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct wv3032_data *wv3032 = cwkout_hw_to_wv3032(hw);

	wv3032_update_cfg(wv3032, WV3032_PMU, WV3032_PMU_NCWKE, WV3032_PMU_NCWKE);
}

static int wv3032_cwkout_is_pwepawed(stwuct cwk_hw *hw)
{
	int vaw, wet;
	stwuct wv3032_data *wv3032 = cwkout_hw_to_wv3032(hw);

	wet = wegmap_wead(wv3032->wegmap, WV3032_PMU, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(vaw & WV3032_PMU_NCWKE);
}

static const stwuct cwk_ops wv3032_cwkout_ops = {
	.pwepawe = wv3032_cwkout_pwepawe,
	.unpwepawe = wv3032_cwkout_unpwepawe,
	.is_pwepawed = wv3032_cwkout_is_pwepawed,
	.wecawc_wate = wv3032_cwkout_wecawc_wate,
	.wound_wate = wv3032_cwkout_wound_wate,
	.set_wate = wv3032_cwkout_set_wate,
};

static int wv3032_cwkout_wegistew_cwk(stwuct wv3032_data *wv3032,
				      stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	stwuct device_node *node = cwient->dev.of_node;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_TWSB, WV3032_TWSB_CWKF, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW2, WV3032_CTWW2_CWKIE, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wv3032->wegmap, WV3032_CWK_IWQ, 0);
	if (wet < 0)
		wetuwn wet;

	init.name = "wv3032-cwkout";
	init.ops = &wv3032_cwkout_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	wv3032->cwkout_hw.init = &init;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	cwk = devm_cwk_wegistew(&cwient->dev, &wv3032->cwkout_hw);
	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn 0;
}
#endif

static int wv3032_hwmon_wead_temp(stwuct device *dev, wong *mC)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);
	u8 buf[2];
	int temp, pwev = 0;
	int wet;

	wet = wegmap_buwk_wead(wv3032->wegmap, WV3032_TWSB, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	temp = sign_extend32(buf[1], 7) << 4;
	temp |= FIEWD_GET(WV3032_TWSB_TEMP, buf[0]);

	/* No bwocking ow shadowing on WV3032_TWSB and WV3032_TMSB */
	do {
		pwev = temp;

		wet = wegmap_buwk_wead(wv3032->wegmap, WV3032_TWSB, buf, sizeof(buf));
		if (wet)
			wetuwn wet;

		temp = sign_extend32(buf[1], 7) << 4;
		temp |= FIEWD_GET(WV3032_TWSB_TEMP, buf[0]);
	} whiwe (temp != pwev);

	*mC = (temp * 1000) / 16;

	wetuwn 0;
}

static umode_t wv3032_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int wv3032_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *temp)
{
	int eww;

	switch (attw) {
	case hwmon_temp_input:
		eww = wv3032_hwmon_wead_temp(dev, temp);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static const stwuct hwmon_channew_info * const wv3032_hwmon_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
	NUWW
};

static const stwuct hwmon_ops wv3032_hwmon_hwmon_ops = {
	.is_visibwe = wv3032_hwmon_is_visibwe,
	.wead = wv3032_hwmon_wead,
};

static const stwuct hwmon_chip_info wv3032_hwmon_chip_info = {
	.ops = &wv3032_hwmon_hwmon_ops,
	.info = wv3032_hwmon_info,
};

static void wv3032_hwmon_wegistew(stwuct device *dev)
{
	stwuct wv3032_data *wv3032 = dev_get_dwvdata(dev);

	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn;

	devm_hwmon_device_wegistew_with_info(dev, "wv3032", wv3032, &wv3032_hwmon_chip_info, NUWW);
}

static const stwuct wtc_cwass_ops wv3032_wtc_ops = {
	.wead_time = wv3032_get_time,
	.set_time = wv3032_set_time,
	.wead_offset = wv3032_wead_offset,
	.set_offset = wv3032_set_offset,
	.ioctw = wv3032_ioctw,
	.wead_awawm = wv3032_get_awawm,
	.set_awawm = wv3032_set_awawm,
	.awawm_iwq_enabwe = wv3032_awawm_iwq_enabwe,
	.pawam_get = wv3032_pawam_get,
	.pawam_set = wv3032_pawam_set,
};

static const stwuct wegmap_config wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xCA,
};

static int wv3032_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wv3032_data *wv3032;
	int wet, status;
	stwuct nvmem_config nvmem_cfg = {
		.name = "wv3032_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = 16,
		.type = NVMEM_TYPE_BATTEWY_BACKED,
		.weg_wead = wv3032_nvwam_wead,
		.weg_wwite = wv3032_nvwam_wwite,
	};
	stwuct nvmem_config eepwom_cfg = {
		.name = "wv3032_eepwom",
		.wowd_size = 1,
		.stwide = 1,
		.size = 32,
		.type = NVMEM_TYPE_EEPWOM,
		.weg_wead = wv3032_eepwom_wead,
		.weg_wwite = wv3032_eepwom_wwite,
	};

	wv3032 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wv3032_data),
			      GFP_KEWNEW);
	if (!wv3032)
		wetuwn -ENOMEM;

	wv3032->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(wv3032->wegmap))
		wetuwn PTW_EWW(wv3032->wegmap);

	i2c_set_cwientdata(cwient, wv3032);

	wet = wegmap_wead(wv3032->wegmap, WV3032_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wv3032->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wv3032->wtc))
		wetuwn PTW_EWW(wv3032->wtc);

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, wv3032_handwe_iwq,
						iwqfwags | IWQF_ONESHOT,
						"wv3032", wv3032);
		if (wet) {
			dev_wawn(&cwient->dev, "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
		}
	}
	if (!cwient->iwq)
		cweaw_bit(WTC_FEATUWE_AWAWM, wv3032->wtc->featuwes);

	wet = wegmap_update_bits(wv3032->wegmap, WV3032_CTWW1,
				 WV3032_CTWW1_WADA, WV3032_CTWW1_WADA);
	if (wet)
		wetuwn wet;

	wv3032_twickwe_chawgew_setup(&cwient->dev, wv3032);

	set_bit(WTC_FEATUWE_BACKUP_SWITCH_MODE, wv3032->wtc->featuwes);
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wv3032->wtc->featuwes);

	wv3032->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wv3032->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wv3032->wtc->ops = &wv3032_wtc_ops;
	wet = devm_wtc_wegistew_device(wv3032->wtc);
	if (wet)
		wetuwn wet;

	nvmem_cfg.pwiv = wv3032->wegmap;
	devm_wtc_nvmem_wegistew(wv3032->wtc, &nvmem_cfg);
	eepwom_cfg.pwiv = wv3032;
	devm_wtc_nvmem_wegistew(wv3032->wtc, &eepwom_cfg);

	wv3032->wtc->max_usew_fweq = 1;

#ifdef CONFIG_COMMON_CWK
	wv3032_cwkout_wegistew_cwk(wv3032, cwient);
#endif

	wv3032_hwmon_wegistew(&cwient->dev);

	wetuwn 0;
}

static const stwuct acpi_device_id wv3032_i2c_acpi_match[] = {
	{ "MCWY3032" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wv3032_i2c_acpi_match);

static const __maybe_unused stwuct of_device_id wv3032_of_match[] = {
	{ .compatibwe = "micwocwystaw,wv3032", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wv3032_of_match);

static stwuct i2c_dwivew wv3032_dwivew = {
	.dwivew = {
		.name = "wtc-wv3032",
		.acpi_match_tabwe = wv3032_i2c_acpi_match,
		.of_match_tabwe = of_match_ptw(wv3032_of_match),
	},
	.pwobe		= wv3032_pwobe,
};
moduwe_i2c_dwivew(wv3032_dwivew);

MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_DESCWIPTION("Micwo Cwystaw WV3032 WTC dwivew");
MODUWE_WICENSE("GPW v2");
