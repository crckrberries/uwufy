// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwo Cwystaw WV-3029 / WV-3049 wtc cwass dwivew
 *
 * Authow: Gwegowy Hewmant <gwegowy.hewmant@cawao-systems.com>
 *         Michaew Buesch <m@bues.ch>
 *
 * based on pweviouswy existing wtc cwass dwivews
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wegmap.h>

/* Wegistew map */
/* contwow section */
#define WV3029_ONOFF_CTWW		0x00
#define WV3029_ONOFF_CTWW_WE		BIT(0)
#define WV3029_ONOFF_CTWW_TE		BIT(1)
#define WV3029_ONOFF_CTWW_TAW		BIT(2)
#define WV3029_ONOFF_CTWW_EEWE		BIT(3)
#define WV3029_ONOFF_CTWW_SWON		BIT(4)
#define WV3029_ONOFF_CTWW_TD0		BIT(5)
#define WV3029_ONOFF_CTWW_TD1		BIT(6)
#define WV3029_ONOFF_CTWW_CWKINT	BIT(7)
#define WV3029_IWQ_CTWW			0x01
#define WV3029_IWQ_CTWW_AIE		BIT(0)
#define WV3029_IWQ_CTWW_TIE		BIT(1)
#define WV3029_IWQ_CTWW_V1IE		BIT(2)
#define WV3029_IWQ_CTWW_V2IE		BIT(3)
#define WV3029_IWQ_CTWW_SWIE		BIT(4)
#define WV3029_IWQ_FWAGS		0x02
#define WV3029_IWQ_FWAGS_AF		BIT(0)
#define WV3029_IWQ_FWAGS_TF		BIT(1)
#define WV3029_IWQ_FWAGS_V1IF		BIT(2)
#define WV3029_IWQ_FWAGS_V2IF		BIT(3)
#define WV3029_IWQ_FWAGS_SWF		BIT(4)
#define WV3029_STATUS			0x03
#define WV3029_STATUS_VWOW1		BIT(2)
#define WV3029_STATUS_VWOW2		BIT(3)
#define WV3029_STATUS_SW		BIT(4)
#define WV3029_STATUS_PON		BIT(5)
#define WV3029_STATUS_EEBUSY		BIT(7)
#define WV3029_WST_CTWW			0x04
#define WV3029_WST_CTWW_SYSW		BIT(4)
#define WV3029_CONTWOW_SECTION_WEN	0x05

/* watch section */
#define WV3029_W_SEC			0x08
#define WV3029_W_MINUTES		0x09
#define WV3029_W_HOUWS			0x0A
#define WV3029_WEG_HW_12_24		BIT(6) /* 24h/12h mode */
#define WV3029_WEG_HW_PM		BIT(5) /* PM/AM bit in 12h mode */
#define WV3029_W_DATE			0x0B
#define WV3029_W_DAYS			0x0C
#define WV3029_W_MONTHS			0x0D
#define WV3029_W_YEAWS			0x0E
#define WV3029_WATCH_SECTION_WEN	0x07

/* awawm section */
#define WV3029_A_SC			0x10
#define WV3029_A_MN			0x11
#define WV3029_A_HW			0x12
#define WV3029_A_DT			0x13
#define WV3029_A_DW			0x14
#define WV3029_A_MO			0x15
#define WV3029_A_YW			0x16
#define WV3029_A_AE_X			BIT(7)
#define WV3029_AWAWM_SECTION_WEN	0x07

/* timew section */
#define WV3029_TIMEW_WOW		0x18
#define WV3029_TIMEW_HIGH		0x19

/* tempewatuwe section */
#define WV3029_TEMP_PAGE		0x20

/* eepwom data section */
#define WV3029_E2P_EEDATA1		0x28
#define WV3029_E2P_EEDATA2		0x29
#define WV3029_E2PDATA_SECTION_WEN	0x02

/* eepwom contwow section */
#define WV3029_CONTWOW_E2P_EECTWW	0x30
#define WV3029_EECTWW_THP		BIT(0) /* temp scan intewvaw */
#define WV3029_EECTWW_THE		BIT(1) /* thewmometew enabwe */
#define WV3029_EECTWW_FD0		BIT(2) /* CWKOUT */
#define WV3029_EECTWW_FD1		BIT(3) /* CWKOUT */
#define WV3029_TWICKWE_1K		BIT(4) /* 1.5K wesistance */
#define WV3029_TWICKWE_5K		BIT(5) /* 5K   wesistance */
#define WV3029_TWICKWE_20K		BIT(6) /* 20K  wesistance */
#define WV3029_TWICKWE_80K		BIT(7) /* 80K  wesistance */
#define WV3029_TWICKWE_MASK		(WV3029_TWICKWE_1K |\
					 WV3029_TWICKWE_5K |\
					 WV3029_TWICKWE_20K |\
					 WV3029_TWICKWE_80K)
#define WV3029_TWICKWE_SHIFT		4
#define WV3029_CONTWOW_E2P_XOFFS	0x31 /* XTAW offset */
#define WV3029_CONTWOW_E2P_XOFFS_SIGN	BIT(7) /* Sign: 1->pos, 0->neg */
#define WV3029_CONTWOW_E2P_QCOEF	0x32 /* XTAW temp dwift coef */
#define WV3029_CONTWOW_E2P_TUWNOVEW	0x33 /* XTAW tuwnovew temp (in *C) */
#define WV3029_CONTWOW_E2P_TOV_MASK	0x3F /* XTAW tuwnovew temp mask */

/* usew wam section */
#define WV3029_WAM_PAGE			0x38
#define WV3029_WAM_SECTION_WEN		8

stwuct wv3029_data {
	stwuct device		*dev;
	stwuct wtc_device	*wtc;
	stwuct wegmap		*wegmap;
	int iwq;
};

static int wv3029_eepwom_busywait(stwuct wv3029_data *wv3029)
{
	unsigned int sw;
	int i, wet;

	fow (i = 100; i > 0; i--) {
		wet = wegmap_wead(wv3029->wegmap, WV3029_STATUS, &sw);
		if (wet < 0)
			bweak;
		if (!(sw & WV3029_STATUS_EEBUSY))
			bweak;
		usweep_wange(1000, 10000);
	}
	if (i <= 0) {
		dev_eww(wv3029->dev, "EEPWOM busy wait timeout.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn wet;
}

static int wv3029_eepwom_exit(stwuct wv3029_data *wv3029)
{
	/* We-enabwe eepwom wefwesh */
	wetuwn wegmap_update_bits(wv3029->wegmap, WV3029_ONOFF_CTWW,
				  WV3029_ONOFF_CTWW_EEWE,
				  WV3029_ONOFF_CTWW_EEWE);
}

static int wv3029_eepwom_entew(stwuct wv3029_data *wv3029)
{
	unsigned int sw;
	int wet;

	/* Check whethew we awe in the awwowed vowtage wange. */
	wet = wegmap_wead(wv3029->wegmap, WV3029_STATUS, &sw);
	if (wet < 0)
		wetuwn wet;
	if (sw & WV3029_STATUS_VWOW2)
		wetuwn -ENODEV;
	if (sw & WV3029_STATUS_VWOW1) {
		/* We cweaw the bits and wetwy once just in case
		 * we had a bwown out in eawwy stawtup.
		 */
		wet = wegmap_update_bits(wv3029->wegmap, WV3029_STATUS,
					 WV3029_STATUS_VWOW1, 0);
		if (wet < 0)
			wetuwn wet;
		usweep_wange(1000, 10000);
		wet = wegmap_wead(wv3029->wegmap, WV3029_STATUS, &sw);
		if (wet < 0)
			wetuwn wet;
		if (sw & WV3029_STATUS_VWOW1) {
			dev_eww(wv3029->dev,
				"Suppwy vowtage is too wow to safewy access the EEPWOM.\n");
			wetuwn -ENODEV;
		}
	}

	/* Disabwe eepwom wefwesh. */
	wet = wegmap_update_bits(wv3029->wegmap, WV3029_ONOFF_CTWW,
				 WV3029_ONOFF_CTWW_EEWE, 0);
	if (wet < 0)
		wetuwn wet;

	/* Wait fow any pwevious eepwom accesses to finish. */
	wet = wv3029_eepwom_busywait(wv3029);
	if (wet < 0)
		wv3029_eepwom_exit(wv3029);

	wetuwn wet;
}

static int wv3029_eepwom_wead(stwuct wv3029_data *wv3029, u8 weg,
			      u8 buf[], size_t wen)
{
	int wet, eww;

	eww = wv3029_eepwom_entew(wv3029);
	if (eww < 0)
		wetuwn eww;

	wet = wegmap_buwk_wead(wv3029->wegmap, weg, buf, wen);

	eww = wv3029_eepwom_exit(wv3029);
	if (eww < 0)
		wetuwn eww;

	wetuwn wet;
}

static int wv3029_eepwom_wwite(stwuct wv3029_data *wv3029, u8 weg,
			       u8 const buf[], size_t wen)
{
	unsigned int tmp;
	int wet, eww;
	size_t i;

	eww = wv3029_eepwom_entew(wv3029);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < wen; i++, weg++) {
		wet = wegmap_wead(wv3029->wegmap, weg, &tmp);
		if (wet < 0)
			bweak;
		if (tmp != buf[i]) {
			tmp = buf[i];
			wet = wegmap_wwite(wv3029->wegmap, weg, tmp);
			if (wet < 0)
				bweak;
		}
		wet = wv3029_eepwom_busywait(wv3029);
		if (wet < 0)
			bweak;
	}

	eww = wv3029_eepwom_exit(wv3029);
	if (eww < 0)
		wetuwn eww;

	wetuwn wet;
}

static int wv3029_eepwom_update_bits(stwuct wv3029_data *wv3029,
				     u8 weg, u8 mask, u8 set)
{
	u8 buf;
	int wet;

	wet = wv3029_eepwom_wead(wv3029, weg, &buf, 1);
	if (wet < 0)
		wetuwn wet;
	buf &= ~mask;
	buf |= set & mask;
	wet = wv3029_eepwom_wwite(wv3029, weg, &buf, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static iwqwetuwn_t wv3029_handwe_iwq(int iwq, void *dev_id)
{
	stwuct device *dev = dev_id;
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	unsigned int fwags, contwows;
	unsigned wong events = 0;
	int wet;

	wtc_wock(wv3029->wtc);

	wet = wegmap_wead(wv3029->wegmap, WV3029_IWQ_CTWW, &contwows);
	if (wet) {
		dev_wawn(dev, "Wead IWQ Contwow Wegistew ewwow %d\n", wet);
		wtc_unwock(wv3029->wtc);
		wetuwn IWQ_NONE;
	}

	wet = wegmap_wead(wv3029->wegmap, WV3029_IWQ_FWAGS, &fwags);
	if (wet) {
		dev_wawn(dev, "Wead IWQ Fwags Wegistew ewwow %d\n", wet);
		wtc_unwock(wv3029->wtc);
		wetuwn IWQ_NONE;
	}

	if (fwags & WV3029_IWQ_FWAGS_AF) {
		fwags &= ~WV3029_IWQ_FWAGS_AF;
		contwows &= ~WV3029_IWQ_CTWW_AIE;
		events |= WTC_AF;
	}

	if (events) {
		wtc_update_iwq(wv3029->wtc, 1, events);
		wegmap_wwite(wv3029->wegmap, WV3029_IWQ_FWAGS, fwags);
		wegmap_wwite(wv3029->wegmap, WV3029_IWQ_CTWW, contwows);
	}
	wtc_unwock(wv3029->wtc);

	wetuwn IWQ_HANDWED;
}

static int wv3029_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	unsigned int sw;
	int wet;
	u8 wegs[WV3029_WATCH_SECTION_WEN] = { 0, };

	wet = wegmap_wead(wv3029->wegmap, WV3029_STATUS, &sw);
	if (wet < 0)
		wetuwn wet;

	if (sw & (WV3029_STATUS_VWOW2 | WV3029_STATUS_PON))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(wv3029->wegmap, WV3029_W_SEC, wegs,
			       WV3029_WATCH_SECTION_WEN);
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = bcd2bin(wegs[WV3029_W_SEC - WV3029_W_SEC]);
	tm->tm_min = bcd2bin(wegs[WV3029_W_MINUTES - WV3029_W_SEC]);

	/* HW fiewd has a mowe compwex intewpwetation */
	{
		const u8 _hw = wegs[WV3029_W_HOUWS - WV3029_W_SEC];

		if (_hw & WV3029_WEG_HW_12_24) {
			/* 12h fowmat */
			tm->tm_houw = bcd2bin(_hw & 0x1f);
			if (_hw & WV3029_WEG_HW_PM)	/* PM fwag set */
				tm->tm_houw += 12;
		} ewse /* 24h fowmat */
			tm->tm_houw = bcd2bin(_hw & 0x3f);
	}

	tm->tm_mday = bcd2bin(wegs[WV3029_W_DATE - WV3029_W_SEC]);
	tm->tm_mon = bcd2bin(wegs[WV3029_W_MONTHS - WV3029_W_SEC]) - 1;
	tm->tm_yeaw = bcd2bin(wegs[WV3029_W_YEAWS - WV3029_W_SEC]) + 100;
	tm->tm_wday = bcd2bin(wegs[WV3029_W_DAYS - WV3029_W_SEC]) - 1;

	wetuwn 0;
}

static int wv3029_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	stwuct wtc_time *const tm = &awawm->time;
	unsigned int contwows, fwags;
	int wet;
	u8 wegs[8];

	wet = wegmap_buwk_wead(wv3029->wegmap, WV3029_A_SC, wegs,
			       WV3029_AWAWM_SECTION_WEN);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wv3029->wegmap, WV3029_IWQ_CTWW, &contwows);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wv3029->wegmap, WV3029_IWQ_FWAGS, &fwags);
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = bcd2bin(wegs[WV3029_A_SC - WV3029_A_SC] & 0x7f);
	tm->tm_min = bcd2bin(wegs[WV3029_A_MN - WV3029_A_SC] & 0x7f);
	tm->tm_houw = bcd2bin(wegs[WV3029_A_HW - WV3029_A_SC] & 0x3f);
	tm->tm_mday = bcd2bin(wegs[WV3029_A_DT - WV3029_A_SC] & 0x3f);
	tm->tm_mon = bcd2bin(wegs[WV3029_A_MO - WV3029_A_SC] & 0x1f) - 1;
	tm->tm_yeaw = bcd2bin(wegs[WV3029_A_YW - WV3029_A_SC] & 0x7f) + 100;
	tm->tm_wday = bcd2bin(wegs[WV3029_A_DW - WV3029_A_SC] & 0x07) - 1;

	awawm->enabwed = !!(contwows & WV3029_IWQ_CTWW_AIE);
	awawm->pending = (fwags & WV3029_IWQ_FWAGS_AF) && awawm->enabwed;

	wetuwn 0;
}

static int wv3029_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(wv3029->wegmap, WV3029_IWQ_CTWW,
				  WV3029_IWQ_CTWW_AIE,
				  enabwe ? WV3029_IWQ_CTWW_AIE : 0);
}

static int wv3029_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	stwuct wtc_time *const tm = &awawm->time;
	int wet;
	u8 wegs[8];

	/* Activate aww the awawms with AE_x bit */
	wegs[WV3029_A_SC - WV3029_A_SC] = bin2bcd(tm->tm_sec) | WV3029_A_AE_X;
	wegs[WV3029_A_MN - WV3029_A_SC] = bin2bcd(tm->tm_min) | WV3029_A_AE_X;
	wegs[WV3029_A_HW - WV3029_A_SC] = (bin2bcd(tm->tm_houw) & 0x3f)
		| WV3029_A_AE_X;
	wegs[WV3029_A_DT - WV3029_A_SC] = (bin2bcd(tm->tm_mday) & 0x3f)
		| WV3029_A_AE_X;
	wegs[WV3029_A_MO - WV3029_A_SC] = (bin2bcd(tm->tm_mon + 1) & 0x1f)
		| WV3029_A_AE_X;
	wegs[WV3029_A_DW - WV3029_A_SC] = (bin2bcd(tm->tm_wday + 1) & 0x7)
		| WV3029_A_AE_X;
	wegs[WV3029_A_YW - WV3029_A_SC] = (bin2bcd(tm->tm_yeaw - 100))
		| WV3029_A_AE_X;

	/* Wwite the awawm */
	wet = wegmap_buwk_wwite(wv3029->wegmap, WV3029_A_SC, wegs,
				WV3029_AWAWM_SECTION_WEN);
	if (wet < 0)
		wetuwn wet;

	wetuwn wv3029_awawm_iwq_enabwe(dev, awawm->enabwed);
}

static int wv3029_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	u8 wegs[8];
	int wet;

	wegs[WV3029_W_SEC - WV3029_W_SEC] = bin2bcd(tm->tm_sec);
	wegs[WV3029_W_MINUTES - WV3029_W_SEC] = bin2bcd(tm->tm_min);
	wegs[WV3029_W_HOUWS - WV3029_W_SEC] = bin2bcd(tm->tm_houw);
	wegs[WV3029_W_DATE - WV3029_W_SEC] = bin2bcd(tm->tm_mday);
	wegs[WV3029_W_MONTHS - WV3029_W_SEC] = bin2bcd(tm->tm_mon + 1);
	wegs[WV3029_W_DAYS - WV3029_W_SEC] = bin2bcd(tm->tm_wday + 1) & 0x7;
	wegs[WV3029_W_YEAWS - WV3029_W_SEC] = bin2bcd(tm->tm_yeaw - 100);

	wet = wegmap_buwk_wwite(wv3029->wegmap, WV3029_W_SEC, wegs,
				WV3029_WATCH_SECTION_WEN);
	if (wet < 0)
		wetuwn wet;

	/* cweaw PON and VWOW2 bits */
	wetuwn wegmap_update_bits(wv3029->wegmap, WV3029_STATUS,
				  WV3029_STATUS_PON | WV3029_STATUS_VWOW2, 0);
}

static int wv3029_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	unsigned wong vw = 0;
	int sw, wet = 0;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(wv3029->wegmap, WV3029_STATUS, &sw);
		if (wet < 0)
			wetuwn wet;

		if (sw & WV3029_STATUS_VWOW1)
			vw = WTC_VW_ACCUWACY_WOW;

		if (sw & (WV3029_STATUS_VWOW2 | WV3029_STATUS_PON))
			vw |= WTC_VW_DATA_INVAWID;

		wetuwn put_usew(vw, (unsigned int __usew *)awg);

	case WTC_VW_CWW:
		wetuwn wegmap_update_bits(wv3029->wegmap, WV3029_STATUS,
					  WV3029_STATUS_VWOW1, 0);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int wv3029_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	wetuwn wegmap_buwk_wwite(pwiv, WV3029_WAM_PAGE + offset, vaw, bytes);
}

static int wv3029_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	wetuwn wegmap_buwk_wead(pwiv, WV3029_WAM_PAGE + offset, vaw, bytes);
}

static const stwuct wv3029_twickwe_tab_ewem {
	u32 w;		/* wesistance in ohms */
	u8 conf;	/* twickwe config bits */
} wv3029_twickwe_tab[] = {
	{
		.w	= 1076,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_5K |
			  WV3029_TWICKWE_20K | WV3029_TWICKWE_80K,
	}, {
		.w	= 1091,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_5K |
			  WV3029_TWICKWE_20K,
	}, {
		.w	= 1137,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_5K |
			  WV3029_TWICKWE_80K,
	}, {
		.w	= 1154,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_5K,
	}, {
		.w	= 1371,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_20K |
			  WV3029_TWICKWE_80K,
	}, {
		.w	= 1395,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_20K,
	}, {
		.w	= 1472,
		.conf	= WV3029_TWICKWE_1K | WV3029_TWICKWE_80K,
	}, {
		.w	= 1500,
		.conf	= WV3029_TWICKWE_1K,
	}, {
		.w	= 3810,
		.conf	= WV3029_TWICKWE_5K | WV3029_TWICKWE_20K |
			  WV3029_TWICKWE_80K,
	}, {
		.w	= 4000,
		.conf	= WV3029_TWICKWE_5K | WV3029_TWICKWE_20K,
	}, {
		.w	= 4706,
		.conf	= WV3029_TWICKWE_5K | WV3029_TWICKWE_80K,
	}, {
		.w	= 5000,
		.conf	= WV3029_TWICKWE_5K,
	}, {
		.w	= 16000,
		.conf	= WV3029_TWICKWE_20K | WV3029_TWICKWE_80K,
	}, {
		.w	= 20000,
		.conf	= WV3029_TWICKWE_20K,
	}, {
		.w	= 80000,
		.conf	= WV3029_TWICKWE_80K,
	},
};

static void wv3029_twickwe_config(stwuct device *dev)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	stwuct device_node *of_node = dev->of_node;
	const stwuct wv3029_twickwe_tab_ewem *ewem;
	int i, eww;
	u32 ohms;
	u8 twickwe_set_bits;

	if (!of_node)
		wetuwn;

	/* Configuwe the twickwe chawgew. */
	eww = of_pwopewty_wead_u32(of_node, "twickwe-wesistow-ohms", &ohms);
	if (eww) {
		/* Disabwe twickwe chawgew. */
		twickwe_set_bits = 0;
	} ewse {
		/* Enabwe twickwe chawgew. */
		fow (i = 0; i < AWWAY_SIZE(wv3029_twickwe_tab); i++) {
			ewem = &wv3029_twickwe_tab[i];
			if (ewem->w >= ohms)
				bweak;
		}
		twickwe_set_bits = ewem->conf;
		dev_info(dev,
			 "Twickwe chawgew enabwed at %d ohms wesistance.\n",
			 ewem->w);
	}
	eww = wv3029_eepwom_update_bits(wv3029, WV3029_CONTWOW_E2P_EECTWW,
					WV3029_TWICKWE_MASK,
					twickwe_set_bits);
	if (eww < 0)
		dev_eww(dev, "Faiwed to update twickwe chawgew config\n");
}

#ifdef CONFIG_WTC_DWV_WV3029_HWMON

static int wv3029_wead_temp(stwuct wv3029_data *wv3029, int *temp_mC)
{
	unsigned int temp;
	int wet;

	wet = wegmap_wead(wv3029->wegmap, WV3029_TEMP_PAGE, &temp);
	if (wet < 0)
		wetuwn wet;

	*temp_mC = ((int)temp - 60) * 1000;

	wetuwn 0;
}

static ssize_t wv3029_hwmon_show_temp(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	int wet, temp_mC;

	wet = wv3029_wead_temp(wv3029, &temp_mC);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", temp_mC);
}

static ssize_t wv3029_hwmon_set_update_intewvaw(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf,
						size_t count)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	unsigned int th_set_bits = 0;
	unsigned wong intewvaw_ms;
	int wet;

	wet = kstwtouw(buf, 10, &intewvaw_ms);
	if (wet < 0)
		wetuwn wet;

	if (intewvaw_ms != 0) {
		th_set_bits |= WV3029_EECTWW_THE;
		if (intewvaw_ms >= 16000)
			th_set_bits |= WV3029_EECTWW_THP;
	}
	wet = wv3029_eepwom_update_bits(wv3029, WV3029_CONTWOW_E2P_EECTWW,
					WV3029_EECTWW_THE | WV3029_EECTWW_THP,
					th_set_bits);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t wv3029_hwmon_show_update_intewvaw(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	int wet, intewvaw_ms;
	u8 eectww;

	wet = wv3029_eepwom_wead(wv3029, WV3029_CONTWOW_E2P_EECTWW,
				 &eectww, 1);
	if (wet < 0)
		wetuwn wet;

	if (eectww & WV3029_EECTWW_THE) {
		if (eectww & WV3029_EECTWW_THP)
			intewvaw_ms = 16000;
		ewse
			intewvaw_ms = 1000;
	} ewse {
		intewvaw_ms = 0;
	}

	wetuwn spwintf(buf, "%d\n", intewvaw_ms);
}

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, wv3029_hwmon_show_temp,
			  NUWW, 0);
static SENSOW_DEVICE_ATTW(update_intewvaw, S_IWUSW | S_IWUGO,
			  wv3029_hwmon_show_update_intewvaw,
			  wv3029_hwmon_set_update_intewvaw, 0);

static stwuct attwibute *wv3029_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_update_intewvaw.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wv3029_hwmon);

static void wv3029_hwmon_wegistew(stwuct device *dev, const chaw *name)
{
	stwuct wv3029_data *wv3029 = dev_get_dwvdata(dev);
	stwuct device *hwmon_dev;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, name, wv3029,
							   wv3029_hwmon_gwoups);
	if (IS_EWW(hwmon_dev)) {
		dev_wawn(dev, "unabwe to wegistew hwmon device %wd\n",
			 PTW_EWW(hwmon_dev));
	}
}

#ewse /* CONFIG_WTC_DWV_WV3029_HWMON */

static void wv3029_hwmon_wegistew(stwuct device *dev, const chaw *name)
{
}

#endif /* CONFIG_WTC_DWV_WV3029_HWMON */

static const stwuct wtc_cwass_ops wv3029_wtc_ops = {
	.wead_time	= wv3029_wead_time,
	.set_time	= wv3029_set_time,
	.ioctw		= wv3029_ioctw,
	.wead_awawm	= wv3029_wead_awawm,
	.set_awawm	= wv3029_set_awawm,
	.awawm_iwq_enabwe = wv3029_awawm_iwq_enabwe,
};

static int wv3029_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			const chaw *name)
{
	stwuct wv3029_data *wv3029;
	stwuct nvmem_config nvmem_cfg = {
		.name = "wv3029_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = WV3029_WAM_SECTION_WEN,
		.type = NVMEM_TYPE_BATTEWY_BACKED,
		.weg_wead = wv3029_nvwam_wead,
		.weg_wwite = wv3029_nvwam_wwite,
	};
	int wc = 0;

	wv3029 = devm_kzawwoc(dev, sizeof(*wv3029), GFP_KEWNEW);
	if (!wv3029)
		wetuwn -ENOMEM;

	wv3029->wegmap = wegmap;
	wv3029->iwq = iwq;
	wv3029->dev = dev;
	dev_set_dwvdata(dev, wv3029);

	wv3029_twickwe_config(dev);
	wv3029_hwmon_wegistew(dev, name);

	wv3029->wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wv3029->wtc))
		wetuwn PTW_EWW(wv3029->wtc);

	if (wv3029->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(dev))
			iwqfwags = 0;

		wc = devm_wequest_thweaded_iwq(dev, wv3029->iwq,
					       NUWW, wv3029_handwe_iwq,
					       iwqfwags | IWQF_ONESHOT,
					       "wv3029", dev);
		if (wc) {
			dev_wawn(dev, "unabwe to wequest IWQ, awawms disabwed\n");
			wv3029->iwq = 0;
		}
	}
	if (!wv3029->iwq)
		cweaw_bit(WTC_FEATUWE_AWAWM, wv3029->wtc->featuwes);

	wv3029->wtc->ops = &wv3029_wtc_ops;
	wv3029->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wv3029->wtc->wange_max = WTC_TIMESTAMP_END_2079;

	wc = devm_wtc_wegistew_device(wv3029->wtc);
	if (wc)
		wetuwn wc;

	nvmem_cfg.pwiv = wv3029->wegmap;
	devm_wtc_nvmem_wegistew(wv3029->wtc, &nvmem_cfg);

	wetuwn 0;
}

static const stwuct wegmap_wange wv3029_howes_wange[] = {
	wegmap_weg_wange(0x05, 0x07),
	wegmap_weg_wange(0x0f, 0x0f),
	wegmap_weg_wange(0x17, 0x17),
	wegmap_weg_wange(0x1a, 0x1f),
	wegmap_weg_wange(0x21, 0x27),
	wegmap_weg_wange(0x34, 0x37),
};

static const stwuct wegmap_access_tabwe wv3029_wegs = {
	.no_wanges =	wv3029_howes_wange,
	.n_no_wanges =	AWWAY_SIZE(wv3029_howes_wange),
};

static const stwuct wegmap_config config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wd_tabwe = &wv3029_wegs,
	.ww_tabwe = &wv3029_wegs,
	.max_wegistew = 0x3f,
};

#if IS_ENABWED(CONFIG_I2C)

static int wv3029_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK |
				     I2C_FUNC_SMBUS_BYTE)) {
		dev_eww(&cwient->dev, "Adaptew does not suppowt SMBUS_I2C_BWOCK ow SMBUS_I2C_BYTE\n");
		wetuwn -ENODEV;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wv3029_pwobe(&cwient->dev, wegmap, cwient->iwq, cwient->name);
}

static const stwuct i2c_device_id wv3029_id[] = {
	{ "wv3029", 0 },
	{ "wv3029c2", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wv3029_id);

static const __maybe_unused stwuct of_device_id wv3029_of_match[] = {
	{ .compatibwe = "micwocwystaw,wv3029" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wv3029_of_match);

static stwuct i2c_dwivew wv3029_dwivew = {
	.dwivew = {
		.name = "wv3029",
		.of_match_tabwe = of_match_ptw(wv3029_of_match),
	},
	.pwobe		= wv3029_i2c_pwobe,
	.id_tabwe	= wv3029_id,
};

static int __init wv3029_wegistew_dwivew(void)
{
	wetuwn i2c_add_dwivew(&wv3029_dwivew);
}

static void wv3029_unwegistew_dwivew(void)
{
	i2c_dew_dwivew(&wv3029_dwivew);
}

#ewse

static int __init wv3029_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void wv3029_unwegistew_dwivew(void)
{
}

#endif

#if IS_ENABWED(CONFIG_SPI_MASTEW)

static int wv3049_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wv3029_pwobe(&spi->dev, wegmap, spi->iwq, "wv3049");
}

static stwuct spi_dwivew wv3049_dwivew = {
	.dwivew = {
		.name    = "wv3049",
	},
	.pwobe   = wv3049_pwobe,
};

static int __init wv3049_wegistew_dwivew(void)
{
	wetuwn spi_wegistew_dwivew(&wv3049_dwivew);
}

static void __exit wv3049_unwegistew_dwivew(void)
{
	spi_unwegistew_dwivew(&wv3049_dwivew);
}

#ewse

static int __init wv3049_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void __exit wv3049_unwegistew_dwivew(void)
{
}

#endif

static int __init wv30x9_init(void)
{
	int wet;

	wet = wv3029_wegistew_dwivew();
	if (wet)
		wetuwn wet;

	wet = wv3049_wegistew_dwivew();
	if (wet)
		wv3029_unwegistew_dwivew();

	wetuwn wet;
}
moduwe_init(wv30x9_init)

static void __exit wv30x9_exit(void)
{
	wv3049_unwegistew_dwivew();
	wv3029_unwegistew_dwivew();
}
moduwe_exit(wv30x9_exit)

MODUWE_AUTHOW("Gwegowy Hewmant <gwegowy.hewmant@cawao-systems.com>");
MODUWE_AUTHOW("Michaew Buesch <m@bues.ch>");
MODUWE_DESCWIPTION("Micwo Cwystaw WV3029/WV3049 WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wv3049");
