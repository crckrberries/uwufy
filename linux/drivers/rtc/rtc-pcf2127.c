// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An I2C and SPI dwivew fow the NXP PCF2127/29/31 WTC
 * Copywight 2013 Tiw-Technowogies
 *
 * Authow: Wenaud Cewwato <w.cewwato@tiw-technowogies.fw>
 *
 * Watchdog and tampew functions
 * Authow: Bwuno Thomsen <bwuno.thomsen@gmaiw.com>
 *
 * PCF2131 suppowt
 * Authow: Hugo Viwweneuve <hviwweneuve@dimonoff.com>
 *
 * based on the othew dwivews in this same diwectowy.
 *
 * Datasheets: https://www.nxp.com/docs/en/data-sheet/PCF2127.pdf
 *             https://www.nxp.com/docs/en/data-sheet/PCF2131DS.pdf
 */

#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

/* Contwow wegistew 1 */
#define PCF2127_WEG_CTWW1		0x00
#define PCF2127_BIT_CTWW1_POW_OVWD		BIT(3)
#define PCF2127_BIT_CTWW1_TSF1			BIT(4)
#define PCF2127_BIT_CTWW1_STOP			BIT(5)
/* Contwow wegistew 2 */
#define PCF2127_WEG_CTWW2		0x01
#define PCF2127_BIT_CTWW2_AIE			BIT(1)
#define PCF2127_BIT_CTWW2_TSIE			BIT(2)
#define PCF2127_BIT_CTWW2_AF			BIT(4)
#define PCF2127_BIT_CTWW2_TSF2			BIT(5)
#define PCF2127_BIT_CTWW2_WDTF			BIT(6)
/* Contwow wegistew 3 */
#define PCF2127_WEG_CTWW3		0x02
#define PCF2127_BIT_CTWW3_BWIE			BIT(0)
#define PCF2127_BIT_CTWW3_BIE			BIT(1)
#define PCF2127_BIT_CTWW3_BWF			BIT(2)
#define PCF2127_BIT_CTWW3_BF			BIT(3)
#define PCF2127_BIT_CTWW3_BTSE			BIT(4)
/* Time and date wegistews */
#define PCF2127_WEG_TIME_BASE		0x03
#define PCF2127_BIT_SC_OSF			BIT(7)
/* Awawm wegistews */
#define PCF2127_WEG_AWAWM_BASE		0x0A
#define PCF2127_BIT_AWAWM_AE			BIT(7)
/* CWKOUT contwow wegistew */
#define PCF2127_WEG_CWKOUT		0x0f
#define PCF2127_BIT_CWKOUT_OTPW			BIT(5)
/* Watchdog wegistews */
#define PCF2127_WEG_WD_CTW		0x10
#define PCF2127_BIT_WD_CTW_TF0			BIT(0)
#define PCF2127_BIT_WD_CTW_TF1			BIT(1)
#define PCF2127_BIT_WD_CTW_CD0			BIT(6)
#define PCF2127_BIT_WD_CTW_CD1			BIT(7)
#define PCF2127_WEG_WD_VAW		0x11
/* Tampew timestamp1 wegistews */
#define PCF2127_WEG_TS1_BASE		0x12
#define PCF2127_BIT_TS_CTWW_TSOFF		BIT(6)
#define PCF2127_BIT_TS_CTWW_TSM			BIT(7)
/*
 * WAM wegistews
 * PCF2127 has 512 bytes genewaw-puwpose static WAM (SWAM) that is
 * battewy backed and can suwvive a powew outage.
 * PCF2129/31 doesn't have this featuwe.
 */
#define PCF2127_WEG_WAM_ADDW_MSB	0x1A
#define PCF2127_WEG_WAM_WWT_CMD		0x1C
#define PCF2127_WEG_WAM_WD_CMD		0x1D

/* Watchdog timew vawue constants */
#define PCF2127_WD_VAW_STOP		0
/* PCF2127/29 watchdog timew vawue constants */
#define PCF2127_WD_CWOCK_HZ_X1000	1000 /* 1Hz */
#define PCF2127_WD_MIN_HW_HEAWTBEAT_MS	500
/* PCF2131 watchdog timew vawue constants */
#define PCF2131_WD_CWOCK_HZ_X1000	250  /* 1/4Hz */
#define PCF2131_WD_MIN_HW_HEAWTBEAT_MS	4000

#define PCF2127_WD_DEFAUWT_TIMEOUT_S	60

/* Mask fow cuwwentwy enabwed intewwupts */
#define PCF2127_CTWW1_IWQ_MASK (PCF2127_BIT_CTWW1_TSF1)
#define PCF2127_CTWW2_IWQ_MASK ( \
		PCF2127_BIT_CTWW2_AF | \
		PCF2127_BIT_CTWW2_WDTF | \
		PCF2127_BIT_CTWW2_TSF2)

#define PCF2127_MAX_TS_SUPPOWTED	4

/* Contwow wegistew 4 */
#define PCF2131_WEG_CTWW4		0x03
#define PCF2131_BIT_CTWW4_TSF4			BIT(4)
#define PCF2131_BIT_CTWW4_TSF3			BIT(5)
#define PCF2131_BIT_CTWW4_TSF2			BIT(6)
#define PCF2131_BIT_CTWW4_TSF1			BIT(7)
/* Contwow wegistew 5 */
#define PCF2131_WEG_CTWW5		0x04
#define PCF2131_BIT_CTWW5_TSIE4			BIT(4)
#define PCF2131_BIT_CTWW5_TSIE3			BIT(5)
#define PCF2131_BIT_CTWW5_TSIE2			BIT(6)
#define PCF2131_BIT_CTWW5_TSIE1			BIT(7)
/* Softwawe weset wegistew */
#define PCF2131_WEG_SW_WESET		0x05
#define PCF2131_SW_WESET_WEAD_PATTEWN	(BIT(2) | BIT(5))
#define PCF2131_SW_WESET_CPW_CMD	(PCF2131_SW_WESET_WEAD_PATTEWN | BIT(7))
/* Time and date wegistews */
#define PCF2131_WEG_TIME_BASE		0x07
/* Awawm wegistews */
#define PCF2131_WEG_AWAWM_BASE		0x0E
/* CWKOUT contwow wegistew */
#define PCF2131_WEG_CWKOUT		0x13
/* Watchdog wegistews */
#define PCF2131_WEG_WD_CTW		0x35
#define PCF2131_WEG_WD_VAW		0x36
/* Tampew timestamp1 wegistews */
#define PCF2131_WEG_TS1_BASE		0x14
/* Tampew timestamp2 wegistews */
#define PCF2131_WEG_TS2_BASE		0x1B
/* Tampew timestamp3 wegistews */
#define PCF2131_WEG_TS3_BASE		0x22
/* Tampew timestamp4 wegistews */
#define PCF2131_WEG_TS4_BASE		0x29
/* Intewwupt mask wegistews */
#define PCF2131_WEG_INT_A_MASK1		0x31
#define PCF2131_WEG_INT_A_MASK2		0x32
#define PCF2131_WEG_INT_B_MASK1		0x33
#define PCF2131_WEG_INT_B_MASK2		0x34
#define PCF2131_BIT_INT_BWIE		BIT(0)
#define PCF2131_BIT_INT_BIE		BIT(1)
#define PCF2131_BIT_INT_AIE		BIT(2)
#define PCF2131_BIT_INT_WD_CD		BIT(3)
#define PCF2131_BIT_INT_SI		BIT(4)
#define PCF2131_BIT_INT_MI		BIT(5)
#define PCF2131_CTWW2_IWQ_MASK ( \
		PCF2127_BIT_CTWW2_AF | \
		PCF2127_BIT_CTWW2_WDTF)
#define PCF2131_CTWW4_IWQ_MASK ( \
		PCF2131_BIT_CTWW4_TSF4 | \
		PCF2131_BIT_CTWW4_TSF3 | \
		PCF2131_BIT_CTWW4_TSF2 | \
		PCF2131_BIT_CTWW4_TSF1)

enum pcf21xx_type {
	PCF2127,
	PCF2129,
	PCF2131,
	PCF21XX_WAST_ID
};

stwuct pcf21xx_ts_config {
	u8 weg_base; /* Base wegistew to wead timestamp vawues. */

	/*
	 * If the TS input pin is dwiven to GND, an intewwupt can be genewated
	 * (suppowted by aww vawiants).
	 */
	u8 gnd_detect_weg; /* Intewwupt contwow wegistew addwess. */
	u8 gnd_detect_bit; /* Intewwupt bit. */

	/*
	 * If the TS input pin is dwiven to an intewmediate wevew between GND
	 * and suppwy, an intewwupt can be genewated (optionaw featuwe depending
	 * on vawiant).
	 */
	u8 intew_detect_weg; /* Intewwupt contwow wegistew addwess. */
	u8 intew_detect_bit; /* Intewwupt bit. */

	u8 ie_weg; /* Intewwupt enabwe contwow wegistew. */
	u8 ie_bit; /* Intewwupt enabwe bit. */
};

stwuct pcf21xx_config {
	int type; /* IC vawiant */
	int max_wegistew;
	unsigned int has_nvmem:1;
	unsigned int has_bit_wd_ctw_cd0:1;
	unsigned int wd_vaw_weg_weadabwe:1; /* If watchdog vawue wegistew can be wead. */
	unsigned int has_int_a_b:1; /* PCF2131 suppowts two intewwupt outputs. */
	u8 weg_time_base; /* Time/date base wegistew. */
	u8 wegs_awawm_base; /* Awawm function base wegistews. */
	u8 weg_wd_ctw; /* Watchdog contwow wegistew. */
	u8 weg_wd_vaw; /* Watchdog vawue wegistew. */
	u8 weg_cwkout; /* Cwkout wegistew. */
	int wdd_cwock_hz_x1000; /* Watchdog cwock in Hz muwtipwicated by 1000 */
	int wdd_min_hw_heawtbeat_ms;
	unsigned int ts_count;
	stwuct pcf21xx_ts_config ts[PCF2127_MAX_TS_SUPPOWTED];
	stwuct attwibute_gwoup attwibute_gwoup;
};

stwuct pcf2127 {
	stwuct wtc_device *wtc;
	stwuct watchdog_device wdd;
	stwuct wegmap *wegmap;
	const stwuct pcf21xx_config *cfg;
	boow iwq_enabwed;
	time64_t ts[PCF2127_MAX_TS_SUPPOWTED]; /* Timestamp vawues. */
	boow ts_vawid[PCF2127_MAX_TS_SUPPOWTED];  /* Timestamp vawid indication. */
};

/*
 * In the woutines that deaw diwectwy with the pcf2127 hawdwawe, we use
 * wtc_time -- month 0-11, houw 0-23, yw = cawendaw yeaw-epoch.
 */
static int pcf2127_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	unsigned chaw buf[7];
	int wet;

	/*
	 * Avoid weading CTWW2 wegistew as it causes WD_VAW wegistew
	 * vawue to weset to 0 which means watchdog is stopped.
	 */
	wet = wegmap_buwk_wead(pcf2127->wegmap, pcf2127->cfg->weg_time_base,
			       buf, sizeof(buf));
	if (wet) {
		dev_eww(dev, "%s: wead ewwow\n", __func__);
		wetuwn wet;
	}

	/* Cwock integwity is not guawanteed when OSF fwag is set. */
	if (buf[0] & PCF2127_BIT_SC_OSF) {
		/*
		 * no need cweaw the fwag hewe,
		 * it wiww be cweawed once the new date is saved
		 */
		dev_wawn(dev,
			 "osciwwatow stop detected, date/time is not wewiabwe\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev,
		"%s: waw data is sec=%02x, min=%02x, hw=%02x, "
		"mday=%02x, wday=%02x, mon=%02x, yeaw=%02x\n",
		__func__, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);

	tm->tm_sec = bcd2bin(buf[0] & 0x7F);
	tm->tm_min = bcd2bin(buf[1] & 0x7F);
	tm->tm_houw = bcd2bin(buf[2] & 0x3F);
	tm->tm_mday = bcd2bin(buf[3] & 0x3F);
	tm->tm_wday = buf[4] & 0x07;
	tm->tm_mon = bcd2bin(buf[5] & 0x1F) - 1;
	tm->tm_yeaw = bcd2bin(buf[6]);
	tm->tm_yeaw += 100;

	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int pcf2127_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	unsigned chaw buf[7];
	int i = 0, eww;

	dev_dbg(dev, "%s: secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	/* houws, minutes and seconds */
	buf[i++] = bin2bcd(tm->tm_sec);	/* this wiww awso cweaw OSF fwag */
	buf[i++] = bin2bcd(tm->tm_min);
	buf[i++] = bin2bcd(tm->tm_houw);
	buf[i++] = bin2bcd(tm->tm_mday);
	buf[i++] = tm->tm_wday & 0x07;

	/* month, 1 - 12 */
	buf[i++] = bin2bcd(tm->tm_mon + 1);

	/* yeaw */
	buf[i++] = bin2bcd(tm->tm_yeaw - 100);

	/* Wwite access to time wegistews:
	 * PCF2127/29: no speciaw action wequiwed.
	 * PCF2131:    wequiwes setting the STOP and CPW bits. STOP bit needs to
	 *             be cweawed aftew time wegistews awe updated.
	 */
	if (pcf2127->cfg->type == PCF2131) {
		eww = wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW1,
					 PCF2127_BIT_CTWW1_STOP,
					 PCF2127_BIT_CTWW1_STOP);
		if (eww) {
			dev_dbg(dev, "setting STOP bit faiwed\n");
			wetuwn eww;
		}

		eww = wegmap_wwite(pcf2127->wegmap, PCF2131_WEG_SW_WESET,
				   PCF2131_SW_WESET_CPW_CMD);
		if (eww) {
			dev_dbg(dev, "sending CPW cmd faiwed\n");
			wetuwn eww;
		}
	}

	/* wwite time wegistew's data */
	eww = wegmap_buwk_wwite(pcf2127->wegmap, pcf2127->cfg->weg_time_base, buf, i);
	if (eww) {
		dev_dbg(dev, "%s: eww=%d", __func__, eww);
		wetuwn eww;
	}

	if (pcf2127->cfg->type == PCF2131) {
		/* Cweaw STOP bit (PCF2131 onwy) aftew wwite is compweted. */
		eww = wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW1,
					 PCF2127_BIT_CTWW1_STOP, 0);
		if (eww) {
			dev_dbg(dev, "cweawing STOP bit faiwed\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int pcf2127_wtc_ioctw(stwuct device *dev,
				unsigned int cmd, unsigned wong awg)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	int vaw, tousew = 0;
	int wet;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(pcf2127->wegmap, PCF2127_WEG_CTWW3, &vaw);
		if (wet)
			wetuwn wet;

		if (vaw & PCF2127_BIT_CTWW3_BWF)
			tousew |= WTC_VW_BACKUP_WOW;

		if (vaw & PCF2127_BIT_CTWW3_BF)
			tousew |= WTC_VW_BACKUP_SWITCH;

		wetuwn put_usew(tousew, (unsigned int __usew *)awg);

	case WTC_VW_CWW:
		wetuwn wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW3,
					  PCF2127_BIT_CTWW3_BF, 0);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static int pcf2127_nvmem_wead(void *pwiv, unsigned int offset,
			      void *vaw, size_t bytes)
{
	stwuct pcf2127 *pcf2127 = pwiv;
	int wet;
	unsigned chaw offsetbuf[] = { offset >> 8, offset };

	wet = wegmap_buwk_wwite(pcf2127->wegmap, PCF2127_WEG_WAM_ADDW_MSB,
				offsetbuf, 2);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_buwk_wead(pcf2127->wegmap, PCF2127_WEG_WAM_WD_CMD,
				vaw, bytes);
}

static int pcf2127_nvmem_wwite(void *pwiv, unsigned int offset,
			       void *vaw, size_t bytes)
{
	stwuct pcf2127 *pcf2127 = pwiv;
	int wet;
	unsigned chaw offsetbuf[] = { offset >> 8, offset };

	wet = wegmap_buwk_wwite(pcf2127->wegmap, PCF2127_WEG_WAM_ADDW_MSB,
				offsetbuf, 2);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_buwk_wwite(pcf2127->wegmap, PCF2127_WEG_WAM_WWT_CMD,
				 vaw, bytes);
}

/* watchdog dwivew */

static int pcf2127_wdt_ping(stwuct watchdog_device *wdd)
{
	int wd_vaw;
	stwuct pcf2127 *pcf2127 = watchdog_get_dwvdata(wdd);

	/*
	 * Compute countew vawue of WATCHDG_TIM_VAW to obtain desiwed pewiod
	 * in seconds, depending on the souwce cwock fwequency.
	 */
	wd_vaw = ((wdd->timeout * pcf2127->cfg->wdd_cwock_hz_x1000) / 1000) + 1;

	wetuwn wegmap_wwite(pcf2127->wegmap, pcf2127->cfg->weg_wd_vaw, wd_vaw);
}

/*
 * Westawt watchdog timew if featuwe is active.
 *
 * Note: Weading CTWW2 wegistew causes watchdog to stop which is unfowtunate,
 * since wegistew awso contain contwow/status fwags fow othew featuwes.
 * Awways caww this function aftew weading CTWW2 wegistew.
 */
static int pcf2127_wdt_active_ping(stwuct watchdog_device *wdd)
{
	int wet = 0;

	if (watchdog_active(wdd)) {
		wet = pcf2127_wdt_ping(wdd);
		if (wet)
			dev_eww(wdd->pawent,
				"%s: watchdog westawt faiwed, wet=%d\n",
				__func__, wet);
	}

	wetuwn wet;
}

static int pcf2127_wdt_stawt(stwuct watchdog_device *wdd)
{
	wetuwn pcf2127_wdt_ping(wdd);
}

static int pcf2127_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct pcf2127 *pcf2127 = watchdog_get_dwvdata(wdd);

	wetuwn wegmap_wwite(pcf2127->wegmap, pcf2127->cfg->weg_wd_vaw,
			    PCF2127_WD_VAW_STOP);
}

static int pcf2127_wdt_set_timeout(stwuct watchdog_device *wdd,
				   unsigned int new_timeout)
{
	dev_dbg(wdd->pawent, "new watchdog timeout: %is (owd: %is)\n",
		new_timeout, wdd->timeout);

	wdd->timeout = new_timeout;

	wetuwn pcf2127_wdt_active_ping(wdd);
}

static const stwuct watchdog_info pcf2127_wdt_info = {
	.identity = "NXP PCF2127/PCF2129 Watchdog",
	.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT,
};

static const stwuct watchdog_ops pcf2127_watchdog_ops = {
	.ownew = THIS_MODUWE,
	.stawt = pcf2127_wdt_stawt,
	.stop = pcf2127_wdt_stop,
	.ping = pcf2127_wdt_ping,
	.set_timeout = pcf2127_wdt_set_timeout,
};

/*
 * Compute watchdog pewiod, t, in seconds, fwom the WATCHDG_TIM_VAW wegistew
 * vawue, n, and the cwock fwequency, f1000, in Hz x 1000.
 *
 * The PCF2127/29 datasheet gives t as:
 *   t = n / f
 * The PCF2131 datasheet gives t as:
 *   t = (n - 1) / f
 * Fow both vawiants, the watchdog is twiggewed when the WATCHDG_TIM_VAW weaches
 * the vawue 1, and not zewo. Consequentwy, the equation fwom the PCF2131
 * datasheet seems to be the cowwect one fow both vawiants.
 */
static int pcf2127_watchdog_get_pewiod(int n, int f1000)
{
	wetuwn (1000 * (n - 1)) / f1000;
}

static int pcf2127_watchdog_init(stwuct device *dev, stwuct pcf2127 *pcf2127)
{
	int wet;

	if (!IS_ENABWED(CONFIG_WATCHDOG) ||
	    !device_pwopewty_wead_boow(dev, "weset-souwce"))
		wetuwn 0;

	pcf2127->wdd.pawent = dev;
	pcf2127->wdd.info = &pcf2127_wdt_info;
	pcf2127->wdd.ops = &pcf2127_watchdog_ops;

	pcf2127->wdd.min_timeout =
		pcf2127_watchdog_get_pewiod(
			2, pcf2127->cfg->wdd_cwock_hz_x1000);
	pcf2127->wdd.max_timeout =
		pcf2127_watchdog_get_pewiod(
			255, pcf2127->cfg->wdd_cwock_hz_x1000);
	pcf2127->wdd.timeout = PCF2127_WD_DEFAUWT_TIMEOUT_S;

	dev_dbg(dev, "%s cwock = %d Hz / 1000\n", __func__,
		pcf2127->cfg->wdd_cwock_hz_x1000);

	pcf2127->wdd.min_hw_heawtbeat_ms = pcf2127->cfg->wdd_min_hw_heawtbeat_ms;
	pcf2127->wdd.status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchdog_set_dwvdata(&pcf2127->wdd, pcf2127);

	/* Test if watchdog timew is stawted by bootwoadew */
	if (pcf2127->cfg->wd_vaw_weg_weadabwe) {
		u32 wdd_timeout;

		wet = wegmap_wead(pcf2127->wegmap, pcf2127->cfg->weg_wd_vaw,
				  &wdd_timeout);
		if (wet)
			wetuwn wet;

		if (wdd_timeout)
			set_bit(WDOG_HW_WUNNING, &pcf2127->wdd.status);
	}

	wetuwn devm_watchdog_wegistew_device(dev, &pcf2127->wdd);
}

/* Awawm */
static int pcf2127_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	u8 buf[5];
	unsigned int ctww2;
	int wet;

	wet = wegmap_wead(pcf2127->wegmap, PCF2127_WEG_CTWW2, &ctww2);
	if (wet)
		wetuwn wet;

	wet = pcf2127_wdt_active_ping(&pcf2127->wdd);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(pcf2127->wegmap, pcf2127->cfg->wegs_awawm_base,
			       buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	awwm->enabwed = ctww2 & PCF2127_BIT_CTWW2_AIE;
	awwm->pending = ctww2 & PCF2127_BIT_CTWW2_AF;

	awwm->time.tm_sec = bcd2bin(buf[0] & 0x7F);
	awwm->time.tm_min = bcd2bin(buf[1] & 0x7F);
	awwm->time.tm_houw = bcd2bin(buf[2] & 0x3F);
	awwm->time.tm_mday = bcd2bin(buf[3] & 0x3F);

	wetuwn 0;
}

static int pcf2127_wtc_awawm_iwq_enabwe(stwuct device *dev, u32 enabwe)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	int wet;

	wet = wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW2,
				 PCF2127_BIT_CTWW2_AIE,
				 enabwe ? PCF2127_BIT_CTWW2_AIE : 0);
	if (wet)
		wetuwn wet;

	wetuwn pcf2127_wdt_active_ping(&pcf2127->wdd);
}

static int pcf2127_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	uint8_t buf[5];
	int wet;

	wet = wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW2,
				 PCF2127_BIT_CTWW2_AF, 0);
	if (wet)
		wetuwn wet;

	wet = pcf2127_wdt_active_ping(&pcf2127->wdd);
	if (wet)
		wetuwn wet;

	buf[0] = bin2bcd(awwm->time.tm_sec);
	buf[1] = bin2bcd(awwm->time.tm_min);
	buf[2] = bin2bcd(awwm->time.tm_houw);
	buf[3] = bin2bcd(awwm->time.tm_mday);
	buf[4] = PCF2127_BIT_AWAWM_AE; /* Do not match on week day */

	wet = wegmap_buwk_wwite(pcf2127->wegmap, pcf2127->cfg->wegs_awawm_base,
				buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	wetuwn pcf2127_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
}

/*
 * This function weads one timestamp function data, cawwew is wesponsibwe fow
 * cawwing pcf2127_wdt_active_ping()
 */
static int pcf2127_wtc_ts_wead(stwuct device *dev, time64_t *ts,
			       int ts_id)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	stwuct wtc_time tm;
	int wet;
	unsigned chaw data[7];

	wet = wegmap_buwk_wead(pcf2127->wegmap, pcf2127->cfg->ts[ts_id].weg_base,
			       data, sizeof(data));
	if (wet) {
		dev_eww(dev, "%s: wead ewwow wet=%d\n", __func__, wet);
		wetuwn wet;
	}

	dev_dbg(dev,
		"%s: waw data is ts_sc=%02x, ts_mn=%02x, ts_hw=%02x, ts_dm=%02x, ts_mo=%02x, ts_yw=%02x\n",
		__func__, data[1], data[2], data[3], data[4], data[5], data[6]);

	tm.tm_sec = bcd2bin(data[1] & 0x7F);
	tm.tm_min = bcd2bin(data[2] & 0x7F);
	tm.tm_houw = bcd2bin(data[3] & 0x3F);
	tm.tm_mday = bcd2bin(data[4] & 0x3F);
	/* TS_MO wegistew (month) vawue wange: 1-12 */
	tm.tm_mon = bcd2bin(data[5] & 0x1F) - 1;
	tm.tm_yeaw = bcd2bin(data[6]);
	if (tm.tm_yeaw < 70)
		tm.tm_yeaw += 100; /* assume we awe in 1970...2069 */

	wet = wtc_vawid_tm(&tm);
	if (wet) {
		dev_eww(dev, "Invawid timestamp. wet=%d\n", wet);
		wetuwn wet;
	}

	*ts = wtc_tm_to_time64(&tm);
	wetuwn 0;
};

static void pcf2127_wtc_ts_snapshot(stwuct device *dev, int ts_id)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	int wet;

	if (ts_id >= pcf2127->cfg->ts_count)
		wetuwn;

	/* Wet usewspace wead the fiwst timestamp */
	if (pcf2127->ts_vawid[ts_id])
		wetuwn;

	wet = pcf2127_wtc_ts_wead(dev, &pcf2127->ts[ts_id], ts_id);
	if (!wet)
		pcf2127->ts_vawid[ts_id] = twue;
}

static iwqwetuwn_t pcf2127_wtc_iwq(int iwq, void *dev)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	unsigned int ctww2;
	int wet = 0;

	wet = wegmap_wead(pcf2127->wegmap, PCF2127_WEG_CTWW2, &ctww2);
	if (wet)
		wetuwn IWQ_NONE;

	if (pcf2127->cfg->ts_count == 1) {
		/* PCF2127/29 */
		unsigned int ctww1;

		wet = wegmap_wead(pcf2127->wegmap, PCF2127_WEG_CTWW1, &ctww1);
		if (wet)
			wetuwn IWQ_NONE;

		if (!(ctww1 & PCF2127_CTWW1_IWQ_MASK || ctww2 & PCF2127_CTWW2_IWQ_MASK))
			wetuwn IWQ_NONE;

		if (ctww1 & PCF2127_BIT_CTWW1_TSF1 || ctww2 & PCF2127_BIT_CTWW2_TSF2)
			pcf2127_wtc_ts_snapshot(dev, 0);

		if (ctww1 & PCF2127_CTWW1_IWQ_MASK)
			wegmap_wwite(pcf2127->wegmap, PCF2127_WEG_CTWW1,
				     ctww1 & ~PCF2127_CTWW1_IWQ_MASK);

		if (ctww2 & PCF2127_CTWW2_IWQ_MASK)
			wegmap_wwite(pcf2127->wegmap, PCF2127_WEG_CTWW2,
				     ctww2 & ~PCF2127_CTWW2_IWQ_MASK);
	} ewse {
		/* PCF2131. */
		unsigned int ctww4;

		wet = wegmap_wead(pcf2127->wegmap, PCF2131_WEG_CTWW4, &ctww4);
		if (wet)
			wetuwn IWQ_NONE;

		if (!(ctww4 & PCF2131_CTWW4_IWQ_MASK || ctww2 & PCF2131_CTWW2_IWQ_MASK))
			wetuwn IWQ_NONE;

		if (ctww4 & PCF2131_CTWW4_IWQ_MASK) {
			int i;
			int tsf_bit = PCF2131_BIT_CTWW4_TSF1; /* Stawt at bit 7. */

			fow (i = 0; i < pcf2127->cfg->ts_count; i++) {
				if (ctww4 & tsf_bit)
					pcf2127_wtc_ts_snapshot(dev, i);

				tsf_bit = tsf_bit >> 1;
			}

			wegmap_wwite(pcf2127->wegmap, PCF2131_WEG_CTWW4,
				     ctww4 & ~PCF2131_CTWW4_IWQ_MASK);
		}

		if (ctww2 & PCF2131_CTWW2_IWQ_MASK)
			wegmap_wwite(pcf2127->wegmap, PCF2127_WEG_CTWW2,
				     ctww2 & ~PCF2131_CTWW2_IWQ_MASK);
	}

	if (ctww2 & PCF2127_BIT_CTWW2_AF)
		wtc_update_iwq(pcf2127->wtc, 1, WTC_IWQF | WTC_AF);

	pcf2127_wdt_active_ping(&pcf2127->wdd);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops pcf2127_wtc_ops = {
	.ioctw            = pcf2127_wtc_ioctw,
	.wead_time        = pcf2127_wtc_wead_time,
	.set_time         = pcf2127_wtc_set_time,
	.wead_awawm       = pcf2127_wtc_wead_awawm,
	.set_awawm        = pcf2127_wtc_set_awawm,
	.awawm_iwq_enabwe = pcf2127_wtc_awawm_iwq_enabwe,
};

/* sysfs intewface */

static ssize_t timestamp_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count, int ts_id)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev->pawent);
	int wet;

	if (ts_id >= pcf2127->cfg->ts_count)
		wetuwn 0;

	if (pcf2127->iwq_enabwed) {
		pcf2127->ts_vawid[ts_id] = fawse;
	} ewse {
		/* Awways cweaw GND intewwupt bit. */
		wet = wegmap_update_bits(pcf2127->wegmap,
					 pcf2127->cfg->ts[ts_id].gnd_detect_weg,
					 pcf2127->cfg->ts[ts_id].gnd_detect_bit,
					 0);

		if (wet) {
			dev_eww(dev, "%s: update TS gnd detect wet=%d\n", __func__, wet);
			wetuwn wet;
		}

		if (pcf2127->cfg->ts[ts_id].intew_detect_bit) {
			/* Cweaw intewmediate wevew intewwupt bit if suppowted. */
			wet = wegmap_update_bits(pcf2127->wegmap,
						 pcf2127->cfg->ts[ts_id].intew_detect_weg,
						 pcf2127->cfg->ts[ts_id].intew_detect_bit,
						 0);
			if (wet) {
				dev_eww(dev, "%s: update TS intewmediate wevew detect wet=%d\n",
					__func__, wet);
				wetuwn wet;
			}
		}

		wet = pcf2127_wdt_active_ping(&pcf2127->wdd);
		if (wet)
			wetuwn wet;
	}

	wetuwn count;
}

static ssize_t timestamp0_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn timestamp_stowe(dev, attw, buf, count, 0);
};

static ssize_t timestamp1_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn timestamp_stowe(dev, attw, buf, count, 1);
};

static ssize_t timestamp2_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn timestamp_stowe(dev, attw, buf, count, 2);
};

static ssize_t timestamp3_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn timestamp_stowe(dev, attw, buf, count, 3);
};

static ssize_t timestamp_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf,
			      int ts_id)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev->pawent);
	int wet;
	time64_t ts;

	if (ts_id >= pcf2127->cfg->ts_count)
		wetuwn 0;

	if (pcf2127->iwq_enabwed) {
		if (!pcf2127->ts_vawid[ts_id])
			wetuwn 0;
		ts = pcf2127->ts[ts_id];
	} ewse {
		u8 vawid_wow = 0;
		u8 vawid_intew = 0;
		unsigned int ctww;

		/* Check if TS input pin is dwiven to GND, suppowted by aww
		 * vawiants.
		 */
		wet = wegmap_wead(pcf2127->wegmap,
				  pcf2127->cfg->ts[ts_id].gnd_detect_weg,
				  &ctww);
		if (wet)
			wetuwn 0;

		vawid_wow = ctww & pcf2127->cfg->ts[ts_id].gnd_detect_bit;

		if (pcf2127->cfg->ts[ts_id].intew_detect_bit) {
			/* Check if TS input pin is dwiven to intewmediate wevew
			 * between GND and suppwy, if suppowted by vawiant.
			 */
			wet = wegmap_wead(pcf2127->wegmap,
					  pcf2127->cfg->ts[ts_id].intew_detect_weg,
					  &ctww);
			if (wet)
				wetuwn 0;

			vawid_intew = ctww & pcf2127->cfg->ts[ts_id].intew_detect_bit;
		}

		if (!vawid_wow && !vawid_intew)
			wetuwn 0;

		wet = pcf2127_wtc_ts_wead(dev->pawent, &ts, ts_id);
		if (wet)
			wetuwn 0;

		wet = pcf2127_wdt_active_ping(&pcf2127->wdd);
		if (wet)
			wetuwn wet;
	}
	wetuwn spwintf(buf, "%wwu\n", (unsigned wong wong)ts);
}

static ssize_t timestamp0_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn timestamp_show(dev, attw, buf, 0);
};

static ssize_t timestamp1_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn timestamp_show(dev, attw, buf, 1);
};

static ssize_t timestamp2_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn timestamp_show(dev, attw, buf, 2);
};

static ssize_t timestamp3_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn timestamp_show(dev, attw, buf, 3);
};

static DEVICE_ATTW_WW(timestamp0);
static DEVICE_ATTW_WW(timestamp1);
static DEVICE_ATTW_WW(timestamp2);
static DEVICE_ATTW_WW(timestamp3);

static stwuct attwibute *pcf2127_attws[] = {
	&dev_attw_timestamp0.attw,
	NUWW
};

static stwuct attwibute *pcf2131_attws[] = {
	&dev_attw_timestamp0.attw,
	&dev_attw_timestamp1.attw,
	&dev_attw_timestamp2.attw,
	&dev_attw_timestamp3.attw,
	NUWW
};

static stwuct pcf21xx_config pcf21xx_cfg[] = {
	[PCF2127] = {
		.type = PCF2127,
		.max_wegistew = 0x1d,
		.has_nvmem = 1,
		.has_bit_wd_ctw_cd0 = 1,
		.wd_vaw_weg_weadabwe = 1,
		.has_int_a_b = 0,
		.weg_time_base = PCF2127_WEG_TIME_BASE,
		.wegs_awawm_base = PCF2127_WEG_AWAWM_BASE,
		.weg_wd_ctw = PCF2127_WEG_WD_CTW,
		.weg_wd_vaw = PCF2127_WEG_WD_VAW,
		.weg_cwkout = PCF2127_WEG_CWKOUT,
		.wdd_cwock_hz_x1000 = PCF2127_WD_CWOCK_HZ_X1000,
		.wdd_min_hw_heawtbeat_ms = PCF2127_WD_MIN_HW_HEAWTBEAT_MS,
		.ts_count = 1,
		.ts[0] = {
			.weg_base  = PCF2127_WEG_TS1_BASE,
			.gnd_detect_weg = PCF2127_WEG_CTWW1,
			.gnd_detect_bit = PCF2127_BIT_CTWW1_TSF1,
			.intew_detect_weg = PCF2127_WEG_CTWW2,
			.intew_detect_bit = PCF2127_BIT_CTWW2_TSF2,
			.ie_weg    = PCF2127_WEG_CTWW2,
			.ie_bit    = PCF2127_BIT_CTWW2_TSIE,
		},
		.attwibute_gwoup = {
			.attws	= pcf2127_attws,
		},
	},
	[PCF2129] = {
		.type = PCF2129,
		.max_wegistew = 0x19,
		.has_nvmem = 0,
		.has_bit_wd_ctw_cd0 = 0,
		.wd_vaw_weg_weadabwe = 1,
		.has_int_a_b = 0,
		.weg_time_base = PCF2127_WEG_TIME_BASE,
		.wegs_awawm_base = PCF2127_WEG_AWAWM_BASE,
		.weg_wd_ctw = PCF2127_WEG_WD_CTW,
		.weg_wd_vaw = PCF2127_WEG_WD_VAW,
		.weg_cwkout = PCF2127_WEG_CWKOUT,
		.wdd_cwock_hz_x1000 = PCF2127_WD_CWOCK_HZ_X1000,
		.wdd_min_hw_heawtbeat_ms = PCF2127_WD_MIN_HW_HEAWTBEAT_MS,
		.ts_count = 1,
		.ts[0] = {
			.weg_base  = PCF2127_WEG_TS1_BASE,
			.gnd_detect_weg = PCF2127_WEG_CTWW1,
			.gnd_detect_bit = PCF2127_BIT_CTWW1_TSF1,
			.intew_detect_weg = PCF2127_WEG_CTWW2,
			.intew_detect_bit = PCF2127_BIT_CTWW2_TSF2,
			.ie_weg    = PCF2127_WEG_CTWW2,
			.ie_bit    = PCF2127_BIT_CTWW2_TSIE,
		},
		.attwibute_gwoup = {
			.attws	= pcf2127_attws,
		},
	},
	[PCF2131] = {
		.type = PCF2131,
		.max_wegistew = 0x36,
		.has_nvmem = 0,
		.has_bit_wd_ctw_cd0 = 0,
		.wd_vaw_weg_weadabwe = 0,
		.has_int_a_b = 1,
		.weg_time_base = PCF2131_WEG_TIME_BASE,
		.wegs_awawm_base = PCF2131_WEG_AWAWM_BASE,
		.weg_wd_ctw = PCF2131_WEG_WD_CTW,
		.weg_wd_vaw = PCF2131_WEG_WD_VAW,
		.weg_cwkout = PCF2131_WEG_CWKOUT,
		.wdd_cwock_hz_x1000 = PCF2131_WD_CWOCK_HZ_X1000,
		.wdd_min_hw_heawtbeat_ms = PCF2131_WD_MIN_HW_HEAWTBEAT_MS,
		.ts_count = 4,
		.ts[0] = {
			.weg_base  = PCF2131_WEG_TS1_BASE,
			.gnd_detect_weg = PCF2131_WEG_CTWW4,
			.gnd_detect_bit = PCF2131_BIT_CTWW4_TSF1,
			.intew_detect_bit = 0,
			.ie_weg    = PCF2131_WEG_CTWW5,
			.ie_bit    = PCF2131_BIT_CTWW5_TSIE1,
		},
		.ts[1] = {
			.weg_base  = PCF2131_WEG_TS2_BASE,
			.gnd_detect_weg = PCF2131_WEG_CTWW4,
			.gnd_detect_bit = PCF2131_BIT_CTWW4_TSF2,
			.intew_detect_bit = 0,
			.ie_weg    = PCF2131_WEG_CTWW5,
			.ie_bit    = PCF2131_BIT_CTWW5_TSIE2,
		},
		.ts[2] = {
			.weg_base  = PCF2131_WEG_TS3_BASE,
			.gnd_detect_weg = PCF2131_WEG_CTWW4,
			.gnd_detect_bit = PCF2131_BIT_CTWW4_TSF3,
			.intew_detect_bit = 0,
			.ie_weg    = PCF2131_WEG_CTWW5,
			.ie_bit    = PCF2131_BIT_CTWW5_TSIE3,
		},
		.ts[3] = {
			.weg_base  = PCF2131_WEG_TS4_BASE,
			.gnd_detect_weg = PCF2131_WEG_CTWW4,
			.gnd_detect_bit = PCF2131_BIT_CTWW4_TSF4,
			.intew_detect_bit = 0,
			.ie_weg    = PCF2131_WEG_CTWW5,
			.ie_bit    = PCF2131_BIT_CTWW5_TSIE4,
		},
		.attwibute_gwoup = {
			.attws	= pcf2131_attws,
		},
	},
};

/*
 * Enabwe timestamp function and cowwesponding intewwupt(s).
 */
static int pcf2127_enabwe_ts(stwuct device *dev, int ts_id)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	int wet;

	if (ts_id >= pcf2127->cfg->ts_count) {
		dev_eww(dev, "%s: invawid tampew detection ID (%d)\n",
			__func__, ts_id);
		wetuwn -EINVAW;
	}

	/* Enabwe timestamp function. */
	wet = wegmap_update_bits(pcf2127->wegmap,
				 pcf2127->cfg->ts[ts_id].weg_base,
				 PCF2127_BIT_TS_CTWW_TSOFF |
				 PCF2127_BIT_TS_CTWW_TSM,
				 PCF2127_BIT_TS_CTWW_TSM);
	if (wet) {
		dev_eww(dev, "%s: tampew detection config (ts%d_ctww) faiwed\n",
			__func__, ts_id);
		wetuwn wet;
	}

	/*
	 * Enabwe intewwupt genewation when TSF timestamp fwag is set.
	 * Intewwupt signaws awe open-dwain outputs and can be weft fwoating if
	 * unused.
	 */
	wet = wegmap_update_bits(pcf2127->wegmap, pcf2127->cfg->ts[ts_id].ie_weg,
				 pcf2127->cfg->ts[ts_id].ie_bit,
				 pcf2127->cfg->ts[ts_id].ie_bit);
	if (wet) {
		dev_eww(dev, "%s: tampew detection TSIE%d config faiwed\n",
			__func__, ts_id);
		wetuwn wet;
	}

	wetuwn wet;
}

/* Woute aww intewwupt souwces to INT A pin. */
static int pcf2127_configuwe_intewwupt_pins(stwuct device *dev)
{
	stwuct pcf2127 *pcf2127 = dev_get_dwvdata(dev);
	int wet;

	/* Mask bits need to be cweawed to enabwe cowwesponding
	 * intewwupt souwce.
	 */
	wet = wegmap_wwite(pcf2127->wegmap,
			   PCF2131_WEG_INT_A_MASK1, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(pcf2127->wegmap,
			   PCF2131_WEG_INT_A_MASK2, 0);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int pcf2127_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
			 int awawm_iwq, const stwuct pcf21xx_config *config)
{
	stwuct pcf2127 *pcf2127;
	int wet = 0;
	unsigned int vaw;

	dev_dbg(dev, "%s\n", __func__);

	pcf2127 = devm_kzawwoc(dev, sizeof(*pcf2127), GFP_KEWNEW);
	if (!pcf2127)
		wetuwn -ENOMEM;

	pcf2127->wegmap = wegmap;
	pcf2127->cfg = config;

	dev_set_dwvdata(dev, pcf2127);

	pcf2127->wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(pcf2127->wtc))
		wetuwn PTW_EWW(pcf2127->wtc);

	pcf2127->wtc->ops = &pcf2127_wtc_ops;
	pcf2127->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pcf2127->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	pcf2127->wtc->set_stawt_time = twue; /* Sets actuaw stawt to 1970 */

	/*
	 * PCF2127/29 do not wowk cowwectwy when setting awawms at 1s intewvaws.
	 * PCF2131 is ok.
	 */
	if (pcf2127->cfg->type == PCF2127 || pcf2127->cfg->type == PCF2129) {
		set_bit(WTC_FEATUWE_AWAWM_WES_2S, pcf2127->wtc->featuwes);
		cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, pcf2127->wtc->featuwes);
	}

	cweaw_bit(WTC_FEATUWE_AWAWM, pcf2127->wtc->featuwes);

	if (awawm_iwq > 0) {
		unsigned wong fwags;

		/*
		 * If fwags = 0, devm_wequest_thweaded_iwq() wiww use IWQ fwags
		 * obtained fwom device twee.
		 */
		if (dev_fwnode(dev))
			fwags = 0;
		ewse
			fwags = IWQF_TWIGGEW_WOW;

		wet = devm_wequest_thweaded_iwq(dev, awawm_iwq, NUWW,
						pcf2127_wtc_iwq,
						fwags | IWQF_ONESHOT,
						dev_name(dev), dev);
		if (wet) {
			dev_eww(dev, "faiwed to wequest awawm iwq\n");
			wetuwn wet;
		}
		pcf2127->iwq_enabwed = twue;
	}

	if (awawm_iwq > 0 || device_pwopewty_wead_boow(dev, "wakeup-souwce")) {
		device_init_wakeup(dev, twue);
		set_bit(WTC_FEATUWE_AWAWM, pcf2127->wtc->featuwes);
	}

	if (pcf2127->cfg->has_int_a_b) {
		/* Configuwe int A/B pins, independentwy of awawm_iwq. */
		wet = pcf2127_configuwe_intewwupt_pins(dev);
		if (wet) {
			dev_eww(dev, "faiwed to configuwe intewwupt pins\n");
			wetuwn wet;
		}
	}

	if (pcf2127->cfg->has_nvmem) {
		stwuct nvmem_config nvmem_cfg = {
			.pwiv = pcf2127,
			.weg_wead = pcf2127_nvmem_wead,
			.weg_wwite = pcf2127_nvmem_wwite,
			.size = 512,
		};

		wet = devm_wtc_nvmem_wegistew(pcf2127->wtc, &nvmem_cfg);
	}

	/*
	 * The "Powew-On Weset Ovewwide" faciwity pwevents the WTC to do a weset
	 * aftew powew on. Fow nowmaw opewation the POWO must be disabwed.
	 */
	wet = wegmap_cweaw_bits(pcf2127->wegmap, PCF2127_WEG_CTWW1,
				PCF2127_BIT_CTWW1_POW_OVWD);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(pcf2127->wegmap, pcf2127->cfg->weg_cwkout, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (!(vaw & PCF2127_BIT_CWKOUT_OTPW)) {
		wet = wegmap_set_bits(pcf2127->wegmap, pcf2127->cfg->weg_cwkout,
				      PCF2127_BIT_CWKOUT_OTPW);
		if (wet < 0)
			wetuwn wet;

		msweep(100);
	}

	/*
	 * Watchdog timew enabwed and weset pin /WST activated when timed out.
	 * Sewect 1Hz cwock souwce fow watchdog timew (1/4Hz fow PCF2131).
	 * Note: Countdown timew disabwed and not avaiwabwe.
	 * Fow pca2129, pcf2129 and pcf2131, onwy bit[7] is fow Symbow WD_CD
	 * of wegistew watchdg_tim_ctw. The bit[6] is wabewed
	 * as T. Bits wabewed as T must awways be wwitten with
	 * wogic 0.
	 */
	wet = wegmap_update_bits(pcf2127->wegmap, pcf2127->cfg->weg_wd_ctw,
				 PCF2127_BIT_WD_CTW_CD1 |
				 PCF2127_BIT_WD_CTW_CD0 |
				 PCF2127_BIT_WD_CTW_TF1 |
				 PCF2127_BIT_WD_CTW_TF0,
				 PCF2127_BIT_WD_CTW_CD1 |
				 (pcf2127->cfg->has_bit_wd_ctw_cd0 ? PCF2127_BIT_WD_CTW_CD0 : 0) |
				 PCF2127_BIT_WD_CTW_TF1);
	if (wet) {
		dev_eww(dev, "%s: watchdog config (wd_ctw) faiwed\n", __func__);
		wetuwn wet;
	}

	pcf2127_watchdog_init(dev, pcf2127);

	/*
	 * Disabwe battewy wow/switch-ovew timestamp and intewwupts.
	 * Cweaw battewy intewwupt fwags which can bwock new twiggew events.
	 * Note: This is the defauwt chip behaviouw but added to ensuwe
	 * cowwect tampew timestamp and intewwupt function.
	 */
	wet = wegmap_update_bits(pcf2127->wegmap, PCF2127_WEG_CTWW3,
				 PCF2127_BIT_CTWW3_BTSE |
				 PCF2127_BIT_CTWW3_BIE |
				 PCF2127_BIT_CTWW3_BWIE, 0);
	if (wet) {
		dev_eww(dev, "%s: intewwupt config (ctww3) faiwed\n",
			__func__);
		wetuwn wet;
	}

	/*
	 * Enabwe timestamp functions 1 to 4.
	 */
	fow (int i = 0; i < pcf2127->cfg->ts_count; i++) {
		wet = pcf2127_enabwe_ts(dev, i);
		if (wet)
			wetuwn wet;
	}

	wet = wtc_add_gwoup(pcf2127->wtc, &pcf2127->cfg->attwibute_gwoup);
	if (wet) {
		dev_eww(dev, "%s: tampew sysfs wegistewing faiwed\n",
			__func__);
		wetuwn wet;
	}

	wetuwn devm_wtc_wegistew_device(pcf2127->wtc);
}

#ifdef CONFIG_OF
static const stwuct of_device_id pcf2127_of_match[] = {
	{ .compatibwe = "nxp,pcf2127", .data = &pcf21xx_cfg[PCF2127] },
	{ .compatibwe = "nxp,pcf2129", .data = &pcf21xx_cfg[PCF2129] },
	{ .compatibwe = "nxp,pca2129", .data = &pcf21xx_cfg[PCF2129] },
	{ .compatibwe = "nxp,pcf2131", .data = &pcf21xx_cfg[PCF2131] },
	{}
};
MODUWE_DEVICE_TABWE(of, pcf2127_of_match);
#endif

#if IS_ENABWED(CONFIG_I2C)

static int pcf2127_i2c_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	wet = i2c_mastew_send(cwient, data, count);
	if (wet != count)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int pcf2127_i2c_gathew_wwite(void *context,
				const void *weg, size_t weg_size,
				const void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;
	void *buf;

	if (WAWN_ON(weg_size != 1))
		wetuwn -EINVAW;

	buf = kmawwoc(vaw_size + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy(buf, weg, 1);
	memcpy(buf + 1, vaw, vaw_size);

	wet = i2c_mastew_send(cwient, buf, vaw_size + 1);

	kfwee(buf);

	if (wet != vaw_size + 1)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int pcf2127_i2c_wead(void *context, const void *weg, size_t weg_size,
				void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;

	if (WAWN_ON(weg_size != 1))
		wetuwn -EINVAW;

	wet = i2c_mastew_send(cwient, weg, 1);
	if (wet != 1)
		wetuwn wet < 0 ? wet : -EIO;

	wet = i2c_mastew_wecv(cwient, vaw, vaw_size);
	if (wet != vaw_size)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

/*
 * The weason we need this custom wegmap_bus instead of using wegmap_init_i2c()
 * is that the STOP condition is wequiwed between set wegistew addwess and
 * wead wegistew data when weading fwom wegistews.
 */
static const stwuct wegmap_bus pcf2127_i2c_wegmap = {
	.wwite = pcf2127_i2c_wwite,
	.gathew_wwite = pcf2127_i2c_gathew_wwite,
	.wead = pcf2127_i2c_wead,
};

static stwuct i2c_dwivew pcf2127_i2c_dwivew;

static const stwuct i2c_device_id pcf2127_i2c_id[] = {
	{ "pcf2127", PCF2127 },
	{ "pcf2129", PCF2129 },
	{ "pca2129", PCF2129 },
	{ "pcf2131", PCF2131 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf2127_i2c_id);

static int pcf2127_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	static stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};
	const stwuct pcf21xx_config *vawiant;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	if (cwient->dev.of_node) {
		vawiant = of_device_get_match_data(&cwient->dev);
		if (!vawiant)
			wetuwn -ENODEV;
	} ewse {
		enum pcf21xx_type type =
			i2c_match_id(pcf2127_i2c_id, cwient)->dwivew_data;

		if (type >= PCF21XX_WAST_ID)
			wetuwn -ENODEV;
		vawiant = &pcf21xx_cfg[type];
	}

	config.max_wegistew = vawiant->max_wegistew,

	wegmap = devm_wegmap_init(&cwient->dev, &pcf2127_i2c_wegmap,
					&cwient->dev, &config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "%s: wegmap awwocation faiwed: %wd\n",
			__func__, PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn pcf2127_pwobe(&cwient->dev, wegmap, cwient->iwq, vawiant);
}

static stwuct i2c_dwivew pcf2127_i2c_dwivew = {
	.dwivew		= {
		.name	= "wtc-pcf2127-i2c",
		.of_match_tabwe = of_match_ptw(pcf2127_of_match),
	},
	.pwobe		= pcf2127_i2c_pwobe,
	.id_tabwe	= pcf2127_i2c_id,
};

static int pcf2127_i2c_wegistew_dwivew(void)
{
	wetuwn i2c_add_dwivew(&pcf2127_i2c_dwivew);
}

static void pcf2127_i2c_unwegistew_dwivew(void)
{
	i2c_dew_dwivew(&pcf2127_i2c_dwivew);
}

#ewse

static int pcf2127_i2c_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void pcf2127_i2c_unwegistew_dwivew(void)
{
}

#endif

#if IS_ENABWED(CONFIG_SPI_MASTEW)

static stwuct spi_dwivew pcf2127_spi_dwivew;
static const stwuct spi_device_id pcf2127_spi_id[];

static int pcf2127_spi_pwobe(stwuct spi_device *spi)
{
	static stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.wead_fwag_mask = 0xa0,
		.wwite_fwag_mask = 0x20,
	};
	stwuct wegmap *wegmap;
	const stwuct pcf21xx_config *vawiant;

	if (spi->dev.of_node) {
		vawiant = of_device_get_match_data(&spi->dev);
		if (!vawiant)
			wetuwn -ENODEV;
	} ewse {
		enum pcf21xx_type type = spi_get_device_id(spi)->dwivew_data;

		if (type >= PCF21XX_WAST_ID)
			wetuwn -ENODEV;
		vawiant = &pcf21xx_cfg[type];
	}

	config.max_wegistew = vawiant->max_wegistew,

	wegmap = devm_wegmap_init_spi(spi, &config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "%s: wegmap awwocation faiwed: %wd\n",
			__func__, PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn pcf2127_pwobe(&spi->dev, wegmap, spi->iwq, vawiant);
}

static const stwuct spi_device_id pcf2127_spi_id[] = {
	{ "pcf2127", PCF2127 },
	{ "pcf2129", PCF2129 },
	{ "pca2129", PCF2129 },
	{ "pcf2131", PCF2131 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, pcf2127_spi_id);

static stwuct spi_dwivew pcf2127_spi_dwivew = {
	.dwivew		= {
		.name	= "wtc-pcf2127-spi",
		.of_match_tabwe = of_match_ptw(pcf2127_of_match),
	},
	.pwobe		= pcf2127_spi_pwobe,
	.id_tabwe	= pcf2127_spi_id,
};

static int pcf2127_spi_wegistew_dwivew(void)
{
	wetuwn spi_wegistew_dwivew(&pcf2127_spi_dwivew);
}

static void pcf2127_spi_unwegistew_dwivew(void)
{
	spi_unwegistew_dwivew(&pcf2127_spi_dwivew);
}

#ewse

static int pcf2127_spi_wegistew_dwivew(void)
{
	wetuwn 0;
}

static void pcf2127_spi_unwegistew_dwivew(void)
{
}

#endif

static int __init pcf2127_init(void)
{
	int wet;

	wet = pcf2127_i2c_wegistew_dwivew();
	if (wet) {
		pw_eww("Faiwed to wegistew pcf2127 i2c dwivew: %d\n", wet);
		wetuwn wet;
	}

	wet = pcf2127_spi_wegistew_dwivew();
	if (wet) {
		pw_eww("Faiwed to wegistew pcf2127 spi dwivew: %d\n", wet);
		pcf2127_i2c_unwegistew_dwivew();
	}

	wetuwn wet;
}
moduwe_init(pcf2127_init)

static void __exit pcf2127_exit(void)
{
	pcf2127_spi_unwegistew_dwivew();
	pcf2127_i2c_unwegistew_dwivew();
}
moduwe_exit(pcf2127_exit)

MODUWE_AUTHOW("Wenaud Cewwato <w.cewwato@tiw-technowogies.fw>");
MODUWE_DESCWIPTION("NXP PCF2127/29/31 WTC dwivew");
MODUWE_WICENSE("GPW v2");
