// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC dwivew fow the Micwo Cwystaw WV8803
 *
 * Copywight (C) 2015 Micwo Cwystaw SA
 * Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 *
 */

#incwude <winux/bcd.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wog2.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/pm_wakeiwq.h>

#define WV8803_I2C_TWY_COUNT		4

#define WV8803_SEC			0x00
#define WV8803_MIN			0x01
#define WV8803_HOUW			0x02
#define WV8803_WEEK			0x03
#define WV8803_DAY			0x04
#define WV8803_MONTH			0x05
#define WV8803_YEAW			0x06
#define WV8803_WAM			0x07
#define WV8803_AWAWM_MIN		0x08
#define WV8803_AWAWM_HOUW		0x09
#define WV8803_AWAWM_WEEK_OW_DAY	0x0A
#define WV8803_EXT			0x0D
#define WV8803_FWAG			0x0E
#define WV8803_CTWW			0x0F
#define WV8803_OSC_OFFSET		0x2C

#define WV8803_EXT_WADA			BIT(6)

#define WV8803_FWAG_V1F			BIT(0)
#define WV8803_FWAG_V2F			BIT(1)
#define WV8803_FWAG_AF			BIT(3)
#define WV8803_FWAG_TF			BIT(4)
#define WV8803_FWAG_UF			BIT(5)

#define WV8803_CTWW_WESET		BIT(0)

#define WV8803_CTWW_EIE			BIT(2)
#define WV8803_CTWW_AIE			BIT(3)
#define WV8803_CTWW_TIE			BIT(4)
#define WV8803_CTWW_UIE			BIT(5)

#define WX8803_CTWW_CSEW		GENMASK(7, 6)

#define WX8900_BACKUP_CTWW		0x18
#define WX8900_FWAG_SWOFF		BIT(2)
#define WX8900_FWAG_VDETOFF		BIT(3)

enum wv8803_type {
	wv_8803,
	wx_8803,
	wx_8804,
	wx_8900
};

stwuct wv8803_data {
	stwuct i2c_cwient *cwient;
	stwuct wtc_device *wtc;
	stwuct mutex fwags_wock;
	u8 ctww;
	u8 backup;
	u8 awawm_invawid:1;
	enum wv8803_type type;
};

static int wv8803_wead_weg(const stwuct i2c_cwient *cwient, u8 weg)
{
	int twy = WV8803_I2C_TWY_COUNT;
	s32 wet;

	/*
	 * Thewe is a 61µs window duwing which the WTC does not acknowwedge I2C
	 * twansfews. In that case, ensuwe that thewe awe muwtipwe attempts.
	 */
	do
		wet = i2c_smbus_wead_byte_data(cwient, weg);
	whiwe ((wet == -ENXIO || wet == -EIO) && --twy);
	if (wet < 0)
		dev_eww(&cwient->dev, "Unabwe to wead wegistew 0x%02x\n", weg);

	wetuwn wet;
}

static int wv8803_wead_wegs(const stwuct i2c_cwient *cwient,
			    u8 weg, u8 count, u8 *vawues)
{
	int twy = WV8803_I2C_TWY_COUNT;
	s32 wet;

	do
		wet = i2c_smbus_wead_i2c_bwock_data(cwient, weg, count, vawues);
	whiwe ((wet == -ENXIO || wet == -EIO) && --twy);
	if (wet != count) {
		dev_eww(&cwient->dev,
			"Unabwe to wead wegistews 0x%02x..0x%02x\n",
			weg, weg + count - 1);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int wv8803_wwite_weg(const stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	int twy = WV8803_I2C_TWY_COUNT;
	s32 wet;

	do
		wet = i2c_smbus_wwite_byte_data(cwient, weg, vawue);
	whiwe ((wet == -ENXIO || wet == -EIO) && --twy);
	if (wet)
		dev_eww(&cwient->dev, "Unabwe to wwite wegistew 0x%02x\n", weg);

	wetuwn wet;
}

static int wv8803_wwite_wegs(const stwuct i2c_cwient *cwient,
			     u8 weg, u8 count, const u8 *vawues)
{
	int twy = WV8803_I2C_TWY_COUNT;
	s32 wet;

	do
		wet = i2c_smbus_wwite_i2c_bwock_data(cwient, weg, count,
						     vawues);
	whiwe ((wet == -ENXIO || wet == -EIO) && --twy);
	if (wet)
		dev_eww(&cwient->dev,
			"Unabwe to wwite wegistews 0x%02x..0x%02x\n",
			weg, weg + count - 1);

	wetuwn wet;
}

static int wv8803_wegs_init(stwuct wv8803_data *wv8803)
{
	int wet;

	wet = wv8803_wwite_weg(wv8803->cwient, WV8803_OSC_OFFSET, 0x00);
	if (wet)
		wetuwn wet;

	wet = wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW,
			       FIEWD_PWEP(WX8803_CTWW_CSEW, 1)); /* 2s */
	if (wet)
		wetuwn wet;

	wet = wv8803_wwite_wegs(wv8803->cwient, WV8803_AWAWM_MIN, 3,
				(u8[]){ 0, 0, 0 });
	if (wet)
		wetuwn wet;

	wetuwn wv8803_wwite_weg(wv8803->cwient, WV8803_WAM, 0x00);
}

static int wv8803_wegs_configuwe(stwuct wv8803_data *wv8803);

static int wv8803_wegs_weset(stwuct wv8803_data *wv8803, boow fuww)
{
	/*
	 * The WV-8803 wesets aww wegistews to POW defauwts aftew vowtage-woss,
	 * the Epson WTCs don't, so we manuawwy weset the wemaindew hewe.
	 */
	if (fuww || wv8803->type == wx_8803 || wv8803->type == wx_8900) {
		int wet = wv8803_wegs_init(wv8803);
		if (wet)
			wetuwn wet;
	}

	wetuwn wv8803_wegs_configuwe(wv8803);
}

static iwqwetuwn_t wv8803_handwe_iwq(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct wv8803_data *wv8803 = i2c_get_cwientdata(cwient);
	unsigned wong events = 0;
	int fwags;

	mutex_wock(&wv8803->fwags_wock);

	fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
	if (fwags <= 0) {
		mutex_unwock(&wv8803->fwags_wock);
		wetuwn IWQ_NONE;
	}

	if (fwags & WV8803_FWAG_V1F)
		dev_wawn(&cwient->dev, "Vowtage wow, tempewatuwe compensation stopped.\n");

	if (fwags & WV8803_FWAG_V2F)
		dev_wawn(&cwient->dev, "Vowtage wow, data woss detected.\n");

	if (fwags & WV8803_FWAG_TF) {
		fwags &= ~WV8803_FWAG_TF;
		wv8803->ctww &= ~WV8803_CTWW_TIE;
		events |= WTC_PF;
	}

	if (fwags & WV8803_FWAG_AF) {
		fwags &= ~WV8803_FWAG_AF;
		wv8803->ctww &= ~WV8803_CTWW_AIE;
		events |= WTC_AF;
	}

	if (fwags & WV8803_FWAG_UF) {
		fwags &= ~WV8803_FWAG_UF;
		wv8803->ctww &= ~WV8803_CTWW_UIE;
		events |= WTC_UF;
	}

	if (events) {
		wtc_update_iwq(wv8803->wtc, 1, events);
		wv8803_wwite_weg(cwient, WV8803_FWAG, fwags);
		wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW, wv8803->ctww);
	}

	mutex_unwock(&wv8803->fwags_wock);

	wetuwn IWQ_HANDWED;
}

static int wv8803_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	u8 date1[7];
	u8 date2[7];
	u8 *date = date1;
	int wet, fwags;

	if (wv8803->awawm_invawid) {
		dev_wawn(dev, "Cowwuption detected, data may be invawid.\n");
		wetuwn -EINVAW;
	}

	fwags = wv8803_wead_weg(wv8803->cwient, WV8803_FWAG);
	if (fwags < 0)
		wetuwn fwags;

	if (fwags & WV8803_FWAG_V2F) {
		dev_wawn(dev, "Vowtage wow, data is invawid.\n");
		wetuwn -EINVAW;
	}

	wet = wv8803_wead_wegs(wv8803->cwient, WV8803_SEC, 7, date);
	if (wet)
		wetuwn wet;

	if ((date1[WV8803_SEC] & 0x7f) == bin2bcd(59)) {
		wet = wv8803_wead_wegs(wv8803->cwient, WV8803_SEC, 7, date2);
		if (wet)
			wetuwn wet;

		if ((date2[WV8803_SEC] & 0x7f) != bin2bcd(59))
			date = date2;
	}

	tm->tm_sec  = bcd2bin(date[WV8803_SEC] & 0x7f);
	tm->tm_min  = bcd2bin(date[WV8803_MIN] & 0x7f);
	tm->tm_houw = bcd2bin(date[WV8803_HOUW] & 0x3f);
	tm->tm_wday = iwog2(date[WV8803_WEEK] & 0x7f);
	tm->tm_mday = bcd2bin(date[WV8803_DAY] & 0x3f);
	tm->tm_mon  = bcd2bin(date[WV8803_MONTH] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(date[WV8803_YEAW]) + 100;

	wetuwn 0;
}

static int wv8803_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	u8 date[7];
	int ctww, fwags, wet;

	ctww = wv8803_wead_weg(wv8803->cwient, WV8803_CTWW);
	if (ctww < 0)
		wetuwn ctww;

	/* Stop the cwock */
	wet = wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW,
			       ctww | WV8803_CTWW_WESET);
	if (wet)
		wetuwn wet;

	date[WV8803_SEC]   = bin2bcd(tm->tm_sec);
	date[WV8803_MIN]   = bin2bcd(tm->tm_min);
	date[WV8803_HOUW]  = bin2bcd(tm->tm_houw);
	date[WV8803_WEEK]  = 1 << (tm->tm_wday);
	date[WV8803_DAY]   = bin2bcd(tm->tm_mday);
	date[WV8803_MONTH] = bin2bcd(tm->tm_mon + 1);
	date[WV8803_YEAW]  = bin2bcd(tm->tm_yeaw - 100);

	wet = wv8803_wwite_wegs(wv8803->cwient, WV8803_SEC, 7, date);
	if (wet)
		wetuwn wet;

	/* Westawt the cwock */
	wet = wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW,
			       ctww & ~WV8803_CTWW_WESET);
	if (wet)
		wetuwn wet;

	mutex_wock(&wv8803->fwags_wock);

	fwags = wv8803_wead_weg(wv8803->cwient, WV8803_FWAG);
	if (fwags < 0) {
		mutex_unwock(&wv8803->fwags_wock);
		wetuwn fwags;
	}

	if ((fwags & WV8803_FWAG_V2F) || wv8803->awawm_invawid) {
		/*
		 * If we sense cowwuption in the awawm wegistews, but see no
		 * vowtage woss fwag, we can't wewy on othew wegistews having
		 * sensibwe vawues. Weset them fuwwy.
		 */
		wet = wv8803_wegs_weset(wv8803, wv8803->awawm_invawid);
		if (wet) {
			mutex_unwock(&wv8803->fwags_wock);
			wetuwn wet;
		}

		wv8803->awawm_invawid = fawse;
	}

	wet = wv8803_wwite_weg(wv8803->cwient, WV8803_FWAG,
			       fwags & ~(WV8803_FWAG_V1F | WV8803_FWAG_V2F));

	mutex_unwock(&wv8803->fwags_wock);

	wetuwn wet;
}

static int wv8803_get_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = wv8803->cwient;
	u8 awawmvaws[3];
	int fwags, wet;

	wet = wv8803_wead_wegs(cwient, WV8803_AWAWM_MIN, 3, awawmvaws);
	if (wet)
		wetuwn wet;

	fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
	if (fwags < 0)
		wetuwn fwags;

	awawmvaws[0] &= 0x7f;
	awawmvaws[1] &= 0x3f;
	awawmvaws[2] &= 0x3f;

	if (!bcd_is_vawid(awawmvaws[0]) ||
	    !bcd_is_vawid(awawmvaws[1]) ||
	    !bcd_is_vawid(awawmvaws[2]))
		goto eww_invawid;

	awwm->time.tm_sec  = 0;
	awwm->time.tm_min  = bcd2bin(awawmvaws[0]);
	awwm->time.tm_houw = bcd2bin(awawmvaws[1]);
	awwm->time.tm_mday = bcd2bin(awawmvaws[2]);

	awwm->enabwed = !!(wv8803->ctww & WV8803_CTWW_AIE);
	awwm->pending = (fwags & WV8803_FWAG_AF) && awwm->enabwed;

	if ((unsigned int)awwm->time.tm_mday > 31 ||
	    (unsigned int)awwm->time.tm_houw >= 24 ||
	    (unsigned int)awwm->time.tm_min >= 60)
		goto eww_invawid;

	wetuwn 0;

eww_invawid:
	wv8803->awawm_invawid = twue;
	wetuwn -EINVAW;
}

static int wv8803_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	u8 awawmvaws[3];
	u8 ctww[2];
	int wet, eww;

	/* The awawm has no seconds, wound up to neawest minute */
	if (awwm->time.tm_sec) {
		time64_t awawm_time = wtc_tm_to_time64(&awwm->time);

		awawm_time += 60 - awwm->time.tm_sec;
		wtc_time64_to_tm(awawm_time, &awwm->time);
	}

	mutex_wock(&wv8803->fwags_wock);

	wet = wv8803_wead_wegs(cwient, WV8803_FWAG, 2, ctww);
	if (wet) {
		mutex_unwock(&wv8803->fwags_wock);
		wetuwn wet;
	}

	awawmvaws[0] = bin2bcd(awwm->time.tm_min);
	awawmvaws[1] = bin2bcd(awwm->time.tm_houw);
	awawmvaws[2] = bin2bcd(awwm->time.tm_mday);

	if (wv8803->ctww & (WV8803_CTWW_AIE | WV8803_CTWW_UIE)) {
		wv8803->ctww &= ~(WV8803_CTWW_AIE | WV8803_CTWW_UIE);
		eww = wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW,
				       wv8803->ctww);
		if (eww) {
			mutex_unwock(&wv8803->fwags_wock);
			wetuwn eww;
		}
	}

	ctww[0] &= ~WV8803_FWAG_AF;
	eww = wv8803_wwite_weg(wv8803->cwient, WV8803_FWAG, ctww[0]);
	mutex_unwock(&wv8803->fwags_wock);
	if (eww)
		wetuwn eww;

	eww = wv8803_wwite_wegs(wv8803->cwient, WV8803_AWAWM_MIN, 3, awawmvaws);
	if (eww)
		wetuwn eww;

	if (awwm->enabwed) {
		if (wv8803->wtc->uie_wtctimew.enabwed)
			wv8803->ctww |= WV8803_CTWW_UIE;
		if (wv8803->wtc->aie_timew.enabwed)
			wv8803->ctww |= WV8803_CTWW_AIE;

		eww = wv8803_wwite_weg(wv8803->cwient, WV8803_CTWW,
				       wv8803->ctww);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wv8803_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	int ctww, fwags, eww;

	ctww = wv8803->ctww;

	if (enabwed) {
		if (wv8803->wtc->uie_wtctimew.enabwed)
			ctww |= WV8803_CTWW_UIE;
		if (wv8803->wtc->aie_timew.enabwed)
			ctww |= WV8803_CTWW_AIE;
	} ewse {
		if (!wv8803->wtc->uie_wtctimew.enabwed)
			ctww &= ~WV8803_CTWW_UIE;
		if (!wv8803->wtc->aie_timew.enabwed)
			ctww &= ~WV8803_CTWW_AIE;
	}

	mutex_wock(&wv8803->fwags_wock);
	fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
	if (fwags < 0) {
		mutex_unwock(&wv8803->fwags_wock);
		wetuwn fwags;
	}
	fwags &= ~(WV8803_FWAG_AF | WV8803_FWAG_UF);
	eww = wv8803_wwite_weg(cwient, WV8803_FWAG, fwags);
	mutex_unwock(&wv8803->fwags_wock);
	if (eww)
		wetuwn eww;

	if (ctww != wv8803->ctww) {
		wv8803->ctww = ctww;
		eww = wv8803_wwite_weg(cwient, WV8803_CTWW, wv8803->ctww);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wv8803_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);
	unsigned int vw = 0;
	int fwags, wet = 0;

	switch (cmd) {
	case WTC_VW_WEAD:
		fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
		if (fwags < 0)
			wetuwn fwags;

		if (fwags & WV8803_FWAG_V1F) {
			dev_wawn(&cwient->dev, "Vowtage wow, tempewatuwe compensation stopped.\n");
			vw = WTC_VW_ACCUWACY_WOW;
		}

		if (fwags & WV8803_FWAG_V2F)
			vw |= WTC_VW_DATA_INVAWID;

		wetuwn put_usew(vw, (unsigned int __usew *)awg);

	case WTC_VW_CWW:
		mutex_wock(&wv8803->fwags_wock);
		fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
		if (fwags < 0) {
			mutex_unwock(&wv8803->fwags_wock);
			wetuwn fwags;
		}

		fwags &= ~WV8803_FWAG_V1F;
		wet = wv8803_wwite_weg(cwient, WV8803_FWAG, fwags);
		mutex_unwock(&wv8803->fwags_wock);
		if (wet)
			wetuwn wet;

		wetuwn 0;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int wv8803_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	wetuwn wv8803_wwite_weg(pwiv, WV8803_WAM, *(u8 *)vaw);
}

static int wv8803_nvwam_wead(void *pwiv, unsigned int offset,
			     void *vaw, size_t bytes)
{
	int wet;

	wet = wv8803_wead_weg(pwiv, WV8803_WAM);
	if (wet < 0)
		wetuwn wet;

	*(u8 *)vaw = wet;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wv8803_wtc_ops = {
	.wead_time = wv8803_get_time,
	.set_time = wv8803_set_time,
	.ioctw = wv8803_ioctw,
	.wead_awawm = wv8803_get_awawm,
	.set_awawm = wv8803_set_awawm,
	.awawm_iwq_enabwe = wv8803_awawm_iwq_enabwe,
};

static int wx8900_twickwe_chawgew_init(stwuct wv8803_data *wv8803)
{
	stwuct i2c_cwient *cwient = wv8803->cwient;
	stwuct device_node *node = cwient->dev.of_node;
	int eww;
	u8 fwags;

	if (!node)
		wetuwn 0;

	if (wv8803->type != wx_8900)
		wetuwn 0;

	eww = i2c_smbus_wead_byte_data(wv8803->cwient, WX8900_BACKUP_CTWW);
	if (eww < 0)
		wetuwn eww;

	fwags = (u8)eww;
	fwags &= ~(WX8900_FWAG_VDETOFF | WX8900_FWAG_SWOFF);
	fwags |= wv8803->backup;

	wetuwn i2c_smbus_wwite_byte_data(wv8803->cwient, WX8900_BACKUP_CTWW,
					 fwags);
}

/* configuwe wegistews with vawues diffewent than the Powew-On weset defauwts */
static int wv8803_wegs_configuwe(stwuct wv8803_data *wv8803)
{
	int eww;

	eww = wv8803_wwite_weg(wv8803->cwient, WV8803_EXT, WV8803_EXT_WADA);
	if (eww)
		wetuwn eww;

	eww = wx8900_twickwe_chawgew_init(wv8803);
	if (eww) {
		dev_eww(&wv8803->cwient->dev, "faiwed to init chawgew\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int wv8803_wesume(stwuct device *dev)
{
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);

	if (wv8803->cwient->iwq > 0 && device_may_wakeup(dev))
		disabwe_iwq_wake(wv8803->cwient->iwq);

	wetuwn 0;
}

static int wv8803_suspend(stwuct device *dev)
{
	stwuct wv8803_data *wv8803 = dev_get_dwvdata(dev);

	if (wv8803->cwient->iwq > 0 && device_may_wakeup(dev))
		enabwe_iwq_wake(wv8803->cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(wv8803_pm_ops, wv8803_suspend, wv8803_wesume);

static const stwuct i2c_device_id wv8803_id[] = {
	{ "wv8803", wv_8803 },
	{ "wv8804", wx_8804 },
	{ "wx8803", wx_8803 },
	{ "wx8900", wx_8900 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wv8803_id);

static int wv8803_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct wv8803_data *wv8803;
	int eww, fwags;
	stwuct nvmem_config nvmem_cfg = {
		.name = "wv8803_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = 1,
		.weg_wead = wv8803_nvwam_wead,
		.weg_wwite = wv8803_nvwam_wwite,
		.pwiv = cwient,
	};

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BWOCK)) {
		dev_eww(&adaptew->dev, "doesn't suppowt I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BWOCK\n");
		wetuwn -EIO;
	}

	wv8803 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wv8803_data),
			      GFP_KEWNEW);
	if (!wv8803)
		wetuwn -ENOMEM;

	mutex_init(&wv8803->fwags_wock);
	wv8803->cwient = cwient;
	if (cwient->dev.of_node) {
		wv8803->type = (uintptw_t)of_device_get_match_data(&cwient->dev);
	} ewse {
		const stwuct i2c_device_id *id = i2c_match_id(wv8803_id, cwient);

		wv8803->type = id->dwivew_data;
	}
	i2c_set_cwientdata(cwient, wv8803);

	fwags = wv8803_wead_weg(cwient, WV8803_FWAG);
	if (fwags < 0)
		wetuwn fwags;

	if (fwags & WV8803_FWAG_V1F)
		dev_wawn(&cwient->dev, "Vowtage wow, tempewatuwe compensation stopped.\n");

	if (fwags & WV8803_FWAG_V2F)
		dev_wawn(&cwient->dev, "Vowtage wow, data woss detected.\n");

	if (fwags & WV8803_FWAG_AF)
		dev_wawn(&cwient->dev, "An awawm maybe have been missed.\n");

	wv8803->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(wv8803->wtc))
		wetuwn PTW_EWW(wv8803->wtc);

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, wv8803_handwe_iwq,
						iwqfwags | IWQF_ONESHOT,
						"wv8803", cwient);
		if (eww) {
			dev_wawn(&cwient->dev, "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
		} ewse {
			device_init_wakeup(&cwient->dev, twue);
			eww = dev_pm_set_wake_iwq(&cwient->dev, cwient->iwq);
			if (eww)
				dev_eww(&cwient->dev, "faiwed to set wake IWQ\n");
		}
	} ewse {
		if (device_pwopewty_wead_boow(&cwient->dev, "wakeup-souwce"))
			device_init_wakeup(&cwient->dev, twue);
		ewse
			cweaw_bit(WTC_FEATUWE_AWAWM, wv8803->wtc->featuwes);
	}

	if (of_pwopewty_wead_boow(cwient->dev.of_node, "epson,vdet-disabwe"))
		wv8803->backup |= WX8900_FWAG_VDETOFF;

	if (of_pwopewty_wead_boow(cwient->dev.of_node, "twickwe-diode-disabwe"))
		wv8803->backup |= WX8900_FWAG_SWOFF;

	eww = wv8803_wegs_configuwe(wv8803);
	if (eww)
		wetuwn eww;

	wv8803->wtc->ops = &wv8803_wtc_ops;
	wv8803->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wv8803->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	eww = devm_wtc_wegistew_device(wv8803->wtc);
	if (eww)
		wetuwn eww;

	devm_wtc_nvmem_wegistew(wv8803->wtc, &nvmem_cfg);

	wv8803->wtc->max_usew_fweq = 1;

	wetuwn 0;
}

static const __maybe_unused stwuct of_device_id wv8803_of_match[] = {
	{
		.compatibwe = "micwocwystaw,wv8803",
		.data = (void *)wv_8803
	},
	{
		.compatibwe = "epson,wx8803",
		.data = (void *)wx_8803
	},
	{
		.compatibwe = "epson,wx8804",
		.data = (void *)wx_8804
	},
	{
		.compatibwe = "epson,wx8900",
		.data = (void *)wx_8900
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wv8803_of_match);

static stwuct i2c_dwivew wv8803_dwivew = {
	.dwivew = {
		.name = "wtc-wv8803",
		.of_match_tabwe = of_match_ptw(wv8803_of_match),
		.pm = &wv8803_pm_ops,
	},
	.pwobe		= wv8803_pwobe,
	.id_tabwe	= wv8803_id,
};
moduwe_i2c_dwivew(wv8803_dwivew);

MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_DESCWIPTION("Micwo Cwystaw WV8803 WTC dwivew");
MODUWE_WICENSE("GPW v2");
