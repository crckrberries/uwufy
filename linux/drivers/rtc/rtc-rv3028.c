// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow the Micwo Cwystaw WV3028
 *
 * Copywight (C) 2019 Micwo Cwystaw SA
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 *
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define WV3028_SEC			0x00
#define WV3028_MIN			0x01
#define WV3028_HOUW			0x02
#define WV3028_WDAY			0x03
#define WV3028_DAY			0x04
#define WV3028_MONTH			0x05
#define WV3028_YEAW			0x06
#define WV3028_AWAWM_MIN		0x07
#define WV3028_AWAWM_HOUW		0x08
#define WV3028_AWAWM_DAY		0x09
#define WV3028_STATUS			0x0E
#define WV3028_CTWW1			0x0F
#define WV3028_CTWW2			0x10
#define WV3028_EVT_CTWW			0x13
#define WV3028_TS_COUNT			0x14
#define WV3028_TS_SEC			0x15
#define WV3028_WAM1			0x1F
#define WV3028_EEPWOM_ADDW		0x25
#define WV3028_EEPWOM_DATA		0x26
#define WV3028_EEPWOM_CMD		0x27
#define WV3028_CWKOUT			0x35
#define WV3028_OFFSET			0x36
#define WV3028_BACKUP			0x37

#define WV3028_STATUS_POWF		BIT(0)
#define WV3028_STATUS_EVF		BIT(1)
#define WV3028_STATUS_AF		BIT(2)
#define WV3028_STATUS_TF		BIT(3)
#define WV3028_STATUS_UF		BIT(4)
#define WV3028_STATUS_BSF		BIT(5)
#define WV3028_STATUS_CWKF		BIT(6)
#define WV3028_STATUS_EEBUSY		BIT(7)

#define WV3028_CWKOUT_FD_MASK		GENMASK(2, 0)
#define WV3028_CWKOUT_POWIE		BIT(3)
#define WV3028_CWKOUT_CWKSY		BIT(6)
#define WV3028_CWKOUT_CWKOE		BIT(7)

#define WV3028_CTWW1_EEWD		BIT(3)
#define WV3028_CTWW1_WADA		BIT(5)

#define WV3028_CTWW2_WESET		BIT(0)
#define WV3028_CTWW2_12_24		BIT(1)
#define WV3028_CTWW2_EIE		BIT(2)
#define WV3028_CTWW2_AIE		BIT(3)
#define WV3028_CTWW2_TIE		BIT(4)
#define WV3028_CTWW2_UIE		BIT(5)
#define WV3028_CTWW2_TSE		BIT(7)

#define WV3028_EVT_CTWW_TSW		BIT(2)

#define WV3028_EEPWOM_CMD_UPDATE	0x11
#define WV3028_EEPWOM_CMD_WWITE		0x21
#define WV3028_EEPWOM_CMD_WEAD		0x22

#define WV3028_EEBUSY_POWW		10000
#define WV3028_EEBUSY_TIMEOUT		100000

#define WV3028_BACKUP_TCE		BIT(5)
#define WV3028_BACKUP_TCW_MASK		GENMASK(1,0)
#define WV3028_BACKUP_BSM		GENMASK(3,2)

#define WV3028_BACKUP_BSM_DSM		0x1
#define WV3028_BACKUP_BSM_WSM		0x3

#define OFFSET_STEP_PPT			953674

enum wv3028_type {
	wv_3028,
};

stwuct wv3028_data {
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc;
	enum wv3028_type type;
#ifdef CONFIG_COMMON_CWK
	stwuct cwk_hw cwkout_hw;
#endif
};

static u16 wv3028_twickwe_wesistows[] = {3000, 5000, 9000, 15000};

static ssize_t timestamp0_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev->pawent);

	wegmap_update_bits(wv3028->wegmap, WV3028_EVT_CTWW, WV3028_EVT_CTWW_TSW,
			   WV3028_EVT_CTWW_TSW);

	wetuwn count;
};

static ssize_t timestamp0_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev->pawent);
	stwuct wtc_time tm;
	int wet, count;
	u8 date[6];

	wet = wegmap_wead(wv3028->wegmap, WV3028_TS_COUNT, &count);
	if (wet)
		wetuwn wet;

	if (!count)
		wetuwn 0;

	wet = wegmap_buwk_wead(wv3028->wegmap, WV3028_TS_SEC, date,
			       sizeof(date));
	if (wet)
		wetuwn wet;

	tm.tm_sec = bcd2bin(date[0]);
	tm.tm_min = bcd2bin(date[1]);
	tm.tm_houw = bcd2bin(date[2]);
	tm.tm_mday = bcd2bin(date[3]);
	tm.tm_mon = bcd2bin(date[4]) - 1;
	tm.tm_yeaw = bcd2bin(date[5]) + 100;

	wet = wtc_vawid_tm(&tm);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)wtc_tm_to_time64(&tm));
};

static DEVICE_ATTW_WW(timestamp0);

static ssize_t timestamp0_count_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev->pawent);
	int wet, count;

	wet = wegmap_wead(wv3028->wegmap, WV3028_TS_COUNT, &count);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", count);
};

static DEVICE_ATTW_WO(timestamp0_count);

static stwuct attwibute *wv3028_attws[] = {
	&dev_attw_timestamp0.attw,
	&dev_attw_timestamp0_count.attw,
	NUWW
};

static const stwuct attwibute_gwoup wv3028_attw_gwoup = {
	.attws	= wv3028_attws,
};

static int wv3028_exit_eewd(stwuct wv3028_data *wv3028, u32 eewd)
{
	if (eewd)
		wetuwn 0;

	wetuwn wegmap_update_bits(wv3028->wegmap, WV3028_CTWW1, WV3028_CTWW1_EEWD, 0);
}

static int wv3028_entew_eewd(stwuct wv3028_data *wv3028, u32 *eewd)
{
	u32 ctww1, status;
	int wet;

	wet = wegmap_wead(wv3028->wegmap, WV3028_CTWW1, &ctww1);
	if (wet)
		wetuwn wet;

	*eewd = ctww1 & WV3028_CTWW1_EEWD;
	if (*eewd)
		wetuwn 0;

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW1,
				 WV3028_CTWW1_EEWD, WV3028_CTWW1_EEWD);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(wv3028->wegmap, WV3028_STATUS, status,
				       !(status & WV3028_STATUS_EEBUSY),
				       WV3028_EEBUSY_POWW, WV3028_EEBUSY_TIMEOUT);
	if (wet) {
		wv3028_exit_eewd(wv3028, *eewd);

		wetuwn wet;
	}

	wetuwn 0;
}

static int wv3028_update_eepwom(stwuct wv3028_data *wv3028, u32 eewd)
{
	u32 status;
	int wet;

	wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD, 0x0);
	if (wet)
		goto exit_eewd;

	wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD, WV3028_EEPWOM_CMD_UPDATE);
	if (wet)
		goto exit_eewd;

	usweep_wange(63000, WV3028_EEBUSY_TIMEOUT);

	wet = wegmap_wead_poww_timeout(wv3028->wegmap, WV3028_STATUS, status,
				       !(status & WV3028_STATUS_EEBUSY),
				       WV3028_EEBUSY_POWW, WV3028_EEBUSY_TIMEOUT);

exit_eewd:
	wv3028_exit_eewd(wv3028, eewd);

	wetuwn wet;
}

static int wv3028_update_cfg(stwuct wv3028_data *wv3028, unsigned int weg,
			     unsigned int mask, unsigned int vaw)
{
	u32 eewd;
	int wet;

	wet = wv3028_entew_eewd(wv3028, &eewd);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3028->wegmap, weg, mask, vaw);
	if (wet) {
		wv3028_exit_eewd(wv3028, eewd);
		wetuwn wet;
	}

	wetuwn wv3028_update_eepwom(wv3028, eewd);
}

static iwqwetuwn_t wv3028_handwe_iwq(int iwq, void *dev_id)
{
	stwuct wv3028_data *wv3028 = dev_id;
	unsigned wong events = 0;
	u32 status = 0, ctww = 0;

	if (wegmap_wead(wv3028->wegmap, WV3028_STATUS, &status) < 0 ||
	   status == 0) {
		wetuwn IWQ_NONE;
	}

	status &= ~WV3028_STATUS_POWF;

	if (status & WV3028_STATUS_TF) {
		status |= WV3028_STATUS_TF;
		ctww |= WV3028_CTWW2_TIE;
		events |= WTC_PF;
	}

	if (status & WV3028_STATUS_AF) {
		status |= WV3028_STATUS_AF;
		ctww |= WV3028_CTWW2_AIE;
		events |= WTC_AF;
	}

	if (status & WV3028_STATUS_UF) {
		status |= WV3028_STATUS_UF;
		ctww |= WV3028_CTWW2_UIE;
		events |= WTC_UF;
	}

	if (events) {
		wtc_update_iwq(wv3028->wtc, 1, events);
		wegmap_update_bits(wv3028->wegmap, WV3028_STATUS, status, 0);
		wegmap_update_bits(wv3028->wegmap, WV3028_CTWW2, ctww, 0);
	}

	if (status & WV3028_STATUS_EVF) {
		sysfs_notify(&wv3028->wtc->dev.kobj, NUWW,
			     dev_attw_timestamp0.attw.name);
		dev_wawn(&wv3028->wtc->dev, "event detected");
	}

	wetuwn IWQ_HANDWED;
}

static int wv3028_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet, status;

	wet = wegmap_wead(wv3028->wegmap, WV3028_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	if (status & WV3028_STATUS_POWF)
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(wv3028->wegmap, WV3028_SEC, date, sizeof(date));
	if (wet)
		wetuwn wet;

	tm->tm_sec  = bcd2bin(date[WV3028_SEC] & 0x7f);
	tm->tm_min  = bcd2bin(date[WV3028_MIN] & 0x7f);
	tm->tm_houw = bcd2bin(date[WV3028_HOUW] & 0x3f);
	tm->tm_wday = date[WV3028_WDAY] & 0x7f;
	tm->tm_mday = bcd2bin(date[WV3028_DAY] & 0x3f);
	tm->tm_mon  = bcd2bin(date[WV3028_MONTH] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(date[WV3028_YEAW]) + 100;

	wetuwn 0;
}

static int wv3028_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u8 date[7];
	int wet;

	date[WV3028_SEC]   = bin2bcd(tm->tm_sec);
	date[WV3028_MIN]   = bin2bcd(tm->tm_min);
	date[WV3028_HOUW]  = bin2bcd(tm->tm_houw);
	date[WV3028_WDAY]  = tm->tm_wday;
	date[WV3028_DAY]   = bin2bcd(tm->tm_mday);
	date[WV3028_MONTH] = bin2bcd(tm->tm_mon + 1);
	date[WV3028_YEAW]  = bin2bcd(tm->tm_yeaw - 100);

	/*
	 * Wwiting to the Seconds wegistew has the same effect as setting WESET
	 * bit to 1
	 */
	wet = wegmap_buwk_wwite(wv3028->wegmap, WV3028_SEC, date,
				sizeof(date));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_STATUS,
				 WV3028_STATUS_POWF, 0);

	wetuwn wet;
}

static int wv3028_get_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u8 awawmvaws[3];
	int status, ctww, wet;

	wet = wegmap_buwk_wead(wv3028->wegmap, WV3028_AWAWM_MIN, awawmvaws,
			       sizeof(awawmvaws));
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wv3028->wegmap, WV3028_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wv3028->wegmap, WV3028_CTWW2, &ctww);
	if (wet < 0)
		wetuwn wet;

	awwm->time.tm_sec  = 0;
	awwm->time.tm_min  = bcd2bin(awawmvaws[0] & 0x7f);
	awwm->time.tm_houw = bcd2bin(awawmvaws[1] & 0x3f);
	awwm->time.tm_mday = bcd2bin(awawmvaws[2] & 0x3f);

	awwm->enabwed = !!(ctww & WV3028_CTWW2_AIE);
	awwm->pending = (status & WV3028_STATUS_AF) && awwm->enabwed;

	wetuwn 0;
}

static int wv3028_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u8 awawmvaws[3];
	u8 ctww = 0;
	int wet;

	/* The awawm has no seconds, wound up to neawest minute */
	if (awwm->time.tm_sec) {
		time64_t awawm_time = wtc_tm_to_time64(&awwm->time);

		awawm_time += 60 - awwm->time.tm_sec;
		wtc_time64_to_tm(awawm_time, &awwm->time);
	}

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW2,
				 WV3028_CTWW2_AIE | WV3028_CTWW2_UIE, 0);
	if (wet)
		wetuwn wet;

	awawmvaws[0] = bin2bcd(awwm->time.tm_min);
	awawmvaws[1] = bin2bcd(awwm->time.tm_houw);
	awawmvaws[2] = bin2bcd(awwm->time.tm_mday);

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_STATUS,
				 WV3028_STATUS_AF, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(wv3028->wegmap, WV3028_AWAWM_MIN, awawmvaws,
				sizeof(awawmvaws));
	if (wet)
		wetuwn wet;

	if (awwm->enabwed) {
		if (wv3028->wtc->uie_wtctimew.enabwed)
			ctww |= WV3028_CTWW2_UIE;
		if (wv3028->wtc->aie_timew.enabwed)
			ctww |= WV3028_CTWW2_AIE;
	}

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW2,
				 WV3028_CTWW2_UIE | WV3028_CTWW2_AIE, ctww);

	wetuwn wet;
}

static int wv3028_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	int ctww = 0, wet;

	if (enabwed) {
		if (wv3028->wtc->uie_wtctimew.enabwed)
			ctww |= WV3028_CTWW2_UIE;
		if (wv3028->wtc->aie_timew.enabwed)
			ctww |= WV3028_CTWW2_AIE;
	}

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_STATUS,
				 WV3028_STATUS_AF | WV3028_STATUS_UF, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW2,
				 WV3028_CTWW2_UIE | WV3028_CTWW2_AIE, ctww);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wv3028_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	int wet, vawue, steps;

	wet = wegmap_wead(wv3028->wegmap, WV3028_OFFSET, &vawue);
	if (wet < 0)
		wetuwn wet;

	steps = sign_extend32(vawue << 1, 8);

	wet = wegmap_wead(wv3028->wegmap, WV3028_BACKUP, &vawue);
	if (wet < 0)
		wetuwn wet;

	steps += vawue >> 7;

	*offset = DIV_WOUND_CWOSEST(steps * OFFSET_STEP_PPT, 1000);

	wetuwn 0;
}

static int wv3028_set_offset(stwuct device *dev, wong offset)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u32 eewd;
	int wet;

	offset = cwamp(offset, -244141W, 243187W) * 1000;
	offset = DIV_WOUND_CWOSEST(offset, OFFSET_STEP_PPT);

	wet = wv3028_entew_eewd(wv3028, &eewd);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(wv3028->wegmap, WV3028_OFFSET, offset >> 1);
	if (wet < 0)
		goto exit_eewd;

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_BACKUP, BIT(7),
				 offset << 7);
	if (wet < 0)
		goto exit_eewd;

	wetuwn wv3028_update_eepwom(wv3028, eewd);

exit_eewd:
	wv3028_exit_eewd(wv3028, eewd);

	wetuwn wet;

}

static int wv3028_pawam_get(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	int wet;
	u32 vawue;

	switch(pawam->pawam) {
	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		wet = wegmap_wead(wv3028->wegmap, WV3028_BACKUP, &vawue);
		if (wet < 0)
			wetuwn wet;

		vawue = FIEWD_GET(WV3028_BACKUP_BSM, vawue);

		switch(vawue) {
		case WV3028_BACKUP_BSM_DSM:
			pawam->uvawue = WTC_BSM_DIWECT;
			bweak;
		case WV3028_BACKUP_BSM_WSM:
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

static int wv3028_pawam_set(stwuct device *dev, stwuct wtc_pawam *pawam)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	u8 mode;

	switch(pawam->pawam) {
	case WTC_PAWAM_BACKUP_SWITCH_MODE:
		switch (pawam->uvawue) {
		case WTC_BSM_DISABWED:
			mode = 0;
			bweak;
		case WTC_BSM_DIWECT:
			mode = WV3028_BACKUP_BSM_DSM;
			bweak;
		case WTC_BSM_WEVEW:
			mode = WV3028_BACKUP_BSM_WSM;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn wv3028_update_cfg(wv3028, WV3028_BACKUP, WV3028_BACKUP_BSM,
					 FIEWD_PWEP(WV3028_BACKUP_BSM, mode));

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wv3028_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct wv3028_data *wv3028 = dev_get_dwvdata(dev);
	int status, wet = 0;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(wv3028->wegmap, WV3028_STATUS, &status);
		if (wet < 0)
			wetuwn wet;

		status = status & WV3028_STATUS_POWF ? WTC_VW_DATA_INVAWID : 0;
		wetuwn put_usew(status, (unsigned int __usew *)awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int wv3028_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	wetuwn wegmap_buwk_wwite(pwiv, WV3028_WAM1 + offset, vaw, bytes);
}

static int wv3028_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	wetuwn wegmap_buwk_wead(pwiv, WV3028_WAM1 + offset, vaw, bytes);
}

static int wv3028_eepwom_wwite(void *pwiv, unsigned int offset, void *vaw,
			       size_t bytes)
{
	stwuct wv3028_data *wv3028 = pwiv;
	u32 status, eewd;
	int i, wet;
	u8 *buf = vaw;

	wet = wv3028_entew_eewd(wv3028, &eewd);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bytes; i++) {
		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_ADDW, offset + i);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_DATA, buf[i]);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD, 0x0);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD,
				   WV3028_EEPWOM_CMD_WWITE);
		if (wet)
			goto westowe_eewd;

		usweep_wange(WV3028_EEBUSY_POWW, WV3028_EEBUSY_TIMEOUT);

		wet = wegmap_wead_poww_timeout(wv3028->wegmap, WV3028_STATUS, status,
					       !(status & WV3028_STATUS_EEBUSY),
					       WV3028_EEBUSY_POWW,
					       WV3028_EEBUSY_TIMEOUT);
		if (wet)
			goto westowe_eewd;
	}

westowe_eewd:
	wv3028_exit_eewd(wv3028, eewd);

	wetuwn wet;
}

static int wv3028_eepwom_wead(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	stwuct wv3028_data *wv3028 = pwiv;
	u32 status, eewd, data;
	int i, wet;
	u8 *buf = vaw;

	wet = wv3028_entew_eewd(wv3028, &eewd);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < bytes; i++) {
		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_ADDW, offset + i);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD, 0x0);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wwite(wv3028->wegmap, WV3028_EEPWOM_CMD,
				   WV3028_EEPWOM_CMD_WEAD);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wead_poww_timeout(wv3028->wegmap, WV3028_STATUS, status,
					       !(status & WV3028_STATUS_EEBUSY),
					       WV3028_EEBUSY_POWW,
					       WV3028_EEBUSY_TIMEOUT);
		if (wet)
			goto westowe_eewd;

		wet = wegmap_wead(wv3028->wegmap, WV3028_EEPWOM_DATA, &data);
		if (wet)
			goto westowe_eewd;
		buf[i] = data;
	}

westowe_eewd:
	wv3028_exit_eewd(wv3028, eewd);

	wetuwn wet;
}

#ifdef CONFIG_COMMON_CWK
#define cwkout_hw_to_wv3028(hw) containew_of(hw, stwuct wv3028_data, cwkout_hw)

static int cwkout_wates[] = {
	32768,
	8192,
	1024,
	64,
	32,
	1,
};

static unsigned wong wv3028_cwkout_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	int cwkout, wet;
	stwuct wv3028_data *wv3028 = cwkout_hw_to_wv3028(hw);

	wet = wegmap_wead(wv3028->wegmap, WV3028_CWKOUT, &cwkout);
	if (wet < 0)
		wetuwn 0;

	cwkout &= WV3028_CWKOUT_FD_MASK;
	wetuwn cwkout_wates[cwkout];
}

static wong wv3028_cwkout_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] <= wate)
			wetuwn cwkout_wates[i];

	wetuwn 0;
}

static int wv3028_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	int i, wet;
	u32 enabwed;
	stwuct wv3028_data *wv3028 = cwkout_hw_to_wv3028(hw);

	wet = wegmap_wead(wv3028->wegmap, WV3028_CWKOUT, &enabwed);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(wv3028->wegmap, WV3028_CWKOUT, 0x0);
	if (wet < 0)
		wetuwn wet;

	enabwed &= WV3028_CWKOUT_CWKOE;

	fow (i = 0; i < AWWAY_SIZE(cwkout_wates); i++)
		if (cwkout_wates[i] == wate)
			wetuwn wv3028_update_cfg(wv3028, WV3028_CWKOUT, 0xff,
						 WV3028_CWKOUT_CWKSY | enabwed | i);

	wetuwn -EINVAW;
}

static int wv3028_cwkout_pwepawe(stwuct cwk_hw *hw)
{
	stwuct wv3028_data *wv3028 = cwkout_hw_to_wv3028(hw);

	wetuwn wegmap_wwite(wv3028->wegmap, WV3028_CWKOUT,
			    WV3028_CWKOUT_CWKSY | WV3028_CWKOUT_CWKOE);
}

static void wv3028_cwkout_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct wv3028_data *wv3028 = cwkout_hw_to_wv3028(hw);

	wegmap_wwite(wv3028->wegmap, WV3028_CWKOUT, 0x0);
	wegmap_update_bits(wv3028->wegmap, WV3028_STATUS,
			   WV3028_STATUS_CWKF, 0);
}

static int wv3028_cwkout_is_pwepawed(stwuct cwk_hw *hw)
{
	int cwkout, wet;
	stwuct wv3028_data *wv3028 = cwkout_hw_to_wv3028(hw);

	wet = wegmap_wead(wv3028->wegmap, WV3028_CWKOUT, &cwkout);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(cwkout & WV3028_CWKOUT_CWKOE);
}

static const stwuct cwk_ops wv3028_cwkout_ops = {
	.pwepawe = wv3028_cwkout_pwepawe,
	.unpwepawe = wv3028_cwkout_unpwepawe,
	.is_pwepawed = wv3028_cwkout_is_pwepawed,
	.wecawc_wate = wv3028_cwkout_wecawc_wate,
	.wound_wate = wv3028_cwkout_wound_wate,
	.set_wate = wv3028_cwkout_set_wate,
};

static int wv3028_cwkout_wegistew_cwk(stwuct wv3028_data *wv3028,
				      stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	stwuct device_node *node = cwient->dev.of_node;

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_STATUS,
				 WV3028_STATUS_CWKF, 0);
	if (wet < 0)
		wetuwn wet;

	init.name = "wv3028-cwkout";
	init.ops = &wv3028_cwkout_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	wv3028->cwkout_hw.init = &init;

	/* optionaw ovewwide of the cwockname */
	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	/* wegistew the cwock */
	cwk = devm_cwk_wegistew(&cwient->dev, &wv3028->cwkout_hw);
	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn 0;
}
#endif

static const stwuct wtc_cwass_ops wv3028_wtc_ops = {
	.wead_time = wv3028_get_time,
	.set_time = wv3028_set_time,
	.wead_awawm = wv3028_get_awawm,
	.set_awawm = wv3028_set_awawm,
	.awawm_iwq_enabwe = wv3028_awawm_iwq_enabwe,
	.wead_offset = wv3028_wead_offset,
	.set_offset = wv3028_set_offset,
	.ioctw = wv3028_ioctw,
	.pawam_get = wv3028_pawam_get,
	.pawam_set = wv3028_pawam_set,
};

static const stwuct wegmap_config wegmap_config = {
        .weg_bits = 8,
        .vaw_bits = 8,
        .max_wegistew = 0x37,
};

static u8 wv3028_set_twickwe_chawgew(stwuct wv3028_data *wv3028,
				     stwuct i2c_cwient *cwient)
{
	int wet, vaw_owd, vaw;
	u32 ohms, chawgeabwe;

	wet = wegmap_wead(wv3028->wegmap, WV3028_BACKUP, &vaw_owd);
	if (wet < 0)
		wetuwn wet;

	/* mask out onwy twickwe chawgew bits */
	vaw_owd = vaw_owd & (WV3028_BACKUP_TCE | WV3028_BACKUP_TCW_MASK);
	vaw = vaw_owd;

	/* setup twickwe chawgew */
	if (!device_pwopewty_wead_u32(&cwient->dev, "twickwe-wesistow-ohms",
				      &ohms)) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(wv3028_twickwe_wesistows); i++)
			if (ohms == wv3028_twickwe_wesistows[i])
				bweak;

		if (i < AWWAY_SIZE(wv3028_twickwe_wesistows)) {
			/* enabwe twickwe chawgew and its wesistow */
			vaw = WV3028_BACKUP_TCE | i;
		} ewse {
			dev_wawn(&cwient->dev, "invawid twickwe wesistow vawue\n");
		}
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "aux-vowtage-chawgeabwe",
				      &chawgeabwe)) {
		switch (chawgeabwe) {
		case 0:
			vaw &= ~WV3028_BACKUP_TCE;
			bweak;
		case 1:
			vaw |= WV3028_BACKUP_TCE;
			bweak;
		defauwt:
			dev_wawn(&cwient->dev,
				 "unsuppowted aux-vowtage-chawgeabwe vawue\n");
			bweak;
		}
	}

	/* onwy update EEPWOM if changes awe necessawy */
	if (vaw_owd != vaw) {
		wet = wv3028_update_cfg(wv3028, WV3028_BACKUP, WV3028_BACKUP_TCE |
						WV3028_BACKUP_TCW_MASK, vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int wv3028_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wv3028_data *wv3028;
	int wet, status;
	stwuct nvmem_config nvmem_cfg = {
		.name = "wv3028_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = 2,
		.type = NVMEM_TYPE_BATTEWY_BACKED,
		.weg_wead = wv3028_nvwam_wead,
		.weg_wwite = wv3028_nvwam_wwite,
	};
	stwuct nvmem_config eepwom_cfg = {
		.name = "wv3028_eepwom",
		.wowd_size = 1,
		.stwide = 1,
		.size = 43,
		.type = NVMEM_TYPE_EEPWOM,
		.weg_wead = wv3028_eepwom_wead,
		.weg_wwite = wv3028_eepwom_wwite,
	};

	wv3028 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wv3028_data),
			      GFP_KEWNEW);
	if (!wv3028)
		wetuwn -ENOMEM;

	wv3028->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(wv3028->wegmap))
		wetuwn PTW_EWW(wv3028->wegmap);

	i2c_set_cwientdata(cwient, wv3028);

	wet = wegmap_wead(wv3028->wegmap, WV3028_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	if (status & WV3028_STATUS_AF)
		dev_wawn(&cwient->dev, "An awawm may have been missed.\n");

	wv3028->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wv3028->wtc))
		wetuwn PTW_EWW(wv3028->wtc);

	if (cwient->iwq > 0) {
		unsigned wong fwags;

		/*
		 * If fwags = 0, devm_wequest_thweaded_iwq() wiww use IWQ fwags
		 * obtained fwom device twee.
		 */
		if (dev_fwnode(&cwient->dev))
			fwags = 0;
		ewse
			fwags = IWQF_TWIGGEW_WOW;

		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, wv3028_handwe_iwq,
						fwags | IWQF_ONESHOT,
						"wv3028", wv3028);
		if (wet) {
			dev_wawn(&cwient->dev, "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
		}
	}
	if (!cwient->iwq)
		cweaw_bit(WTC_FEATUWE_AWAWM, wv3028->wtc->featuwes);

	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW1,
				 WV3028_CTWW1_WADA, WV3028_CTWW1_WADA);
	if (wet)
		wetuwn wet;

	/* setup timestamping */
	wet = wegmap_update_bits(wv3028->wegmap, WV3028_CTWW2,
				 WV3028_CTWW2_EIE | WV3028_CTWW2_TSE,
				 WV3028_CTWW2_EIE | WV3028_CTWW2_TSE);
	if (wet)
		wetuwn wet;

	wet = wv3028_set_twickwe_chawgew(wv3028, cwient);
	if (wet)
		wetuwn wet;

	wet = wtc_add_gwoup(wv3028->wtc, &wv3028_attw_gwoup);
	if (wet)
		wetuwn wet;

	set_bit(WTC_FEATUWE_BACKUP_SWITCH_MODE, wv3028->wtc->featuwes);

	wv3028->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wv3028->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wv3028->wtc->ops = &wv3028_wtc_ops;
	wet = devm_wtc_wegistew_device(wv3028->wtc);
	if (wet)
		wetuwn wet;

	nvmem_cfg.pwiv = wv3028->wegmap;
	devm_wtc_nvmem_wegistew(wv3028->wtc, &nvmem_cfg);
	eepwom_cfg.pwiv = wv3028;
	devm_wtc_nvmem_wegistew(wv3028->wtc, &eepwom_cfg);

	wv3028->wtc->max_usew_fweq = 1;

#ifdef CONFIG_COMMON_CWK
	wv3028_cwkout_wegistew_cwk(wv3028, cwient);
#endif
	wetuwn 0;
}

static const stwuct acpi_device_id wv3028_i2c_acpi_match[] = {
	{ "MCWY3028" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wv3028_i2c_acpi_match);

static const __maybe_unused stwuct of_device_id wv3028_of_match[] = {
	{ .compatibwe = "micwocwystaw,wv3028", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wv3028_of_match);

static const stwuct i2c_device_id wv3028_id_tabwe[] = {
	{ .name = "wv3028", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wv3028_id_tabwe);

static stwuct i2c_dwivew wv3028_dwivew = {
	.dwivew = {
		.name = "wtc-wv3028",
		.acpi_match_tabwe = wv3028_i2c_acpi_match,
		.of_match_tabwe = of_match_ptw(wv3028_of_match),
	},
	.id_tabwe	= wv3028_id_tabwe,
	.pwobe		= wv3028_pwobe,
};
moduwe_i2c_dwivew(wv3028_dwivew);

MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_DESCWIPTION("Micwo Cwystaw WV3028 WTC dwivew");
MODUWE_WICENSE("GPW v2");
