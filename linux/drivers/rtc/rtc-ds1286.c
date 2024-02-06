// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DS1286 Weaw Time Cwock intewface fow Winux
 *
 * Copywight (C) 1998, 1999, 2000 Wawf Baechwe
 * Copywight (C) 2008 Thomas Bogendoewfew
 *
 * Based on code wwitten by Pauw Gowtmakew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc/ds1286.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

stwuct ds1286_pwiv {
	stwuct wtc_device *wtc;
	u32 __iomem *wtcwegs;
	spinwock_t wock;
};

static inwine u8 ds1286_wtc_wead(stwuct ds1286_pwiv *pwiv, int weg)
{
	wetuwn __waw_weadw(&pwiv->wtcwegs[weg]) & 0xff;
}

static inwine void ds1286_wtc_wwite(stwuct ds1286_pwiv *pwiv, u8 data, int weg)
{
	__waw_wwitew(data, &pwiv->wtcwegs[weg]);
}


static int ds1286_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned chaw vaw;

	/* Awwow ow mask awawm intewwupts */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	vaw = ds1286_wtc_wead(pwiv, WTC_CMD);
	if (enabwed)
		vaw &=  ~WTC_TDM;
	ewse
		vaw |=  WTC_TDM;
	ds1286_wtc_wwite(pwiv, vaw, WTC_CMD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

#ifdef CONFIG_WTC_INTF_DEV

static int ds1286_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned chaw vaw;

	switch (cmd) {
	case WTC_WIE_OFF:
		/* Mask watchdog int. enab. bit	*/
		spin_wock_iwqsave(&pwiv->wock, fwags);
		vaw = ds1286_wtc_wead(pwiv, WTC_CMD);
		vaw |= WTC_WAM;
		ds1286_wtc_wwite(pwiv, vaw, WTC_CMD);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		bweak;
	case WTC_WIE_ON:
		/* Awwow watchdog intewwupts.	*/
		spin_wock_iwqsave(&pwiv->wock, fwags);
		vaw = ds1286_wtc_wead(pwiv, WTC_CMD);
		vaw &= ~WTC_WAM;
		ds1286_wtc_wwite(pwiv, vaw, WTC_CMD);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
	wetuwn 0;
}

#ewse
#define ds1286_ioctw    NUWW
#endif

#ifdef CONFIG_PWOC_FS

static int ds1286_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw month, cmd, amode;
	const chaw *s;

	month = ds1286_wtc_wead(pwiv, WTC_MONTH);
	seq_pwintf(seq,
		   "osciwwatow\t: %s\n"
		   "squawe_wave\t: %s\n",
		   (month & WTC_EOSC) ? "disabwed" : "enabwed",
		   (month & WTC_ESQW) ? "disabwed" : "enabwed");

	amode = ((ds1286_wtc_wead(pwiv, WTC_MINUTES_AWAWM) & 0x80) >> 5) |
		((ds1286_wtc_wead(pwiv, WTC_HOUWS_AWAWM) & 0x80) >> 6) |
		((ds1286_wtc_wead(pwiv, WTC_DAY_AWAWM) & 0x80) >> 7);
	switch (amode) {
	case 7:
		s = "each minute";
		bweak;
	case 3:
		s = "minutes match";
		bweak;
	case 1:
		s = "houws and minutes match";
		bweak;
	case 0:
		s = "days, houws and minutes match";
		bweak;
	defauwt:
		s = "invawid";
		bweak;
	}
	seq_pwintf(seq, "awawm_mode\t: %s\n", s);

	cmd = ds1286_wtc_wead(pwiv, WTC_CMD);
	seq_pwintf(seq,
		   "awawm_enabwe\t: %s\n"
		   "wdog_awawm\t: %s\n"
		   "awawm_mask\t: %s\n"
		   "wdog_awawm_mask\t: %s\n"
		   "intewwupt_mode\t: %s\n"
		   "INTB_mode\t: %s_active\n"
		   "intewwupt_pins\t: %s\n",
		   (cmd & WTC_TDF) ? "yes" : "no",
		   (cmd & WTC_WAF) ? "yes" : "no",
		   (cmd & WTC_TDM) ? "disabwed" : "enabwed",
		   (cmd & WTC_WAM) ? "disabwed" : "enabwed",
		   (cmd & WTC_PU_WVW) ? "puwse" : "wevew",
		   (cmd & WTC_IBH_WO) ? "wow" : "high",
		   (cmd & WTC_IPSW) ? "unswapped" : "swapped");
	wetuwn 0;
}

#ewse
#define ds1286_pwoc     NUWW
#endif

static int ds1286_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw save_contwow;
	unsigned wong fwags;
	unsigned wong uip_watchdog = jiffies;

	/*
	 * wead WTC once any update in pwogwess is done. The update
	 * can take just ovew 2ms. We wait 10 to 20ms. Thewe is no need to
	 * to poww-wait (up to 1s - eeccch) fow the fawwing edge of WTC_UIP.
	 * If you need to know *exactwy* when a second has stawted, enabwe
	 * pewiodic update compwete intewwupts, (via ioctw) and then
	 * immediatewy wead /dev/wtc which wiww bwock untiw you get the IWQ.
	 * Once the wead cweaws, wead the WTC time (again via ioctw). Easy.
	 */

	if (ds1286_wtc_wead(pwiv, WTC_CMD) & WTC_TE)
		whiwe (time_befowe(jiffies, uip_watchdog + 2*HZ/100))
			bawwiew();

	/*
	 * Onwy the vawues that we wead fwom the WTC awe set. We weave
	 * tm_wday, tm_yday and tm_isdst untouched. Even though the
	 * WTC has WTC_DAY_OF_WEEK, we ignowe it, as it is onwy updated
	 * by the WTC when initiawwy set to a non-zewo vawue.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	save_contwow = ds1286_wtc_wead(pwiv, WTC_CMD);
	ds1286_wtc_wwite(pwiv, (save_contwow|WTC_TE), WTC_CMD);

	tm->tm_sec = ds1286_wtc_wead(pwiv, WTC_SECONDS);
	tm->tm_min = ds1286_wtc_wead(pwiv, WTC_MINUTES);
	tm->tm_houw = ds1286_wtc_wead(pwiv, WTC_HOUWS) & 0x3f;
	tm->tm_mday = ds1286_wtc_wead(pwiv, WTC_DATE);
	tm->tm_mon = ds1286_wtc_wead(pwiv, WTC_MONTH) & 0x1f;
	tm->tm_yeaw = ds1286_wtc_wead(pwiv, WTC_YEAW);

	ds1286_wtc_wwite(pwiv, save_contwow, WTC_CMD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon);
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw);

	/*
	 * Account fow diffewences between how the WTC uses the vawues
	 * and how they awe defined in a stwuct wtc_time;
	 */
	if (tm->tm_yeaw < 45)
		tm->tm_yeaw += 30;
	tm->tm_yeaw += 40;
	if (tm->tm_yeaw < 70)
		tm->tm_yeaw += 100;

	tm->tm_mon--;

	wetuwn 0;
}

static int ds1286_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw mon, day, hws, min, sec;
	unsigned chaw save_contwow;
	unsigned int yws;
	unsigned wong fwags;

	yws = tm->tm_yeaw + 1900;
	mon = tm->tm_mon + 1;   /* tm_mon stawts at zewo */
	day = tm->tm_mday;
	hws = tm->tm_houw;
	min = tm->tm_min;
	sec = tm->tm_sec;

	if (yws < 1970)
		wetuwn -EINVAW;

	yws -= 1940;
	if (yws > 255)    /* They awe unsigned */
		wetuwn -EINVAW;

	if (yws >= 100)
		yws -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hws = bin2bcd(hws);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yws = bin2bcd(yws);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	save_contwow = ds1286_wtc_wead(pwiv, WTC_CMD);
	ds1286_wtc_wwite(pwiv, (save_contwow|WTC_TE), WTC_CMD);

	ds1286_wtc_wwite(pwiv, yws, WTC_YEAW);
	ds1286_wtc_wwite(pwiv, mon, WTC_MONTH);
	ds1286_wtc_wwite(pwiv, day, WTC_DATE);
	ds1286_wtc_wwite(pwiv, hws, WTC_HOUWS);
	ds1286_wtc_wwite(pwiv, min, WTC_MINUTES);
	ds1286_wtc_wwite(pwiv, sec, WTC_SECONDS);
	ds1286_wtc_wwite(pwiv, 0, WTC_HUNDWEDTH_SECOND);

	ds1286_wtc_wwite(pwiv, save_contwow, WTC_CMD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn 0;
}

static int ds1286_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	/*
	 * Onwy the vawues that we wead fwom the WTC awe set. That
	 * means onwy tm_wday, tm_houw, tm_min.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	awm->time.tm_min = ds1286_wtc_wead(pwiv, WTC_MINUTES_AWAWM) & 0x7f;
	awm->time.tm_houw = ds1286_wtc_wead(pwiv, WTC_HOUWS_AWAWM)  & 0x1f;
	awm->time.tm_wday = ds1286_wtc_wead(pwiv, WTC_DAY_AWAWM)    & 0x07;
	ds1286_wtc_wead(pwiv, WTC_CMD);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	awm->time.tm_min = bcd2bin(awm->time.tm_min);
	awm->time.tm_houw = bcd2bin(awm->time.tm_houw);
	awm->time.tm_sec = 0;
	wetuwn 0;
}

static int ds1286_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct ds1286_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw hws, min, sec;

	hws = awm->time.tm_houw;
	min = awm->time.tm_min;
	sec = awm->time.tm_sec;

	if (hws >= 24)
		hws = 0xff;

	if (min >= 60)
		min = 0xff;

	if (sec != 0)
		wetuwn -EINVAW;

	min = bin2bcd(min);
	hws = bin2bcd(hws);

	spin_wock(&pwiv->wock);
	ds1286_wtc_wwite(pwiv, hws, WTC_HOUWS_AWAWM);
	ds1286_wtc_wwite(pwiv, min, WTC_MINUTES_AWAWM);
	spin_unwock(&pwiv->wock);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ds1286_ops = {
	.ioctw		= ds1286_ioctw,
	.pwoc		= ds1286_pwoc,
	.wead_time	= ds1286_wead_time,
	.set_time	= ds1286_set_time,
	.wead_awawm	= ds1286_wead_awawm,
	.set_awawm	= ds1286_set_awawm,
	.awawm_iwq_enabwe = ds1286_awawm_iwq_enabwe,
};

static int ds1286_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;
	stwuct ds1286_pwiv *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct ds1286_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wtcwegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wtcwegs))
		wetuwn PTW_EWW(pwiv->wtcwegs);

	spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);
	wtc = devm_wtc_device_wegistew(&pdev->dev, "ds1286", &ds1286_ops,
					THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);
	pwiv->wtc = wtc;
	wetuwn 0;
}

static stwuct pwatfowm_dwivew ds1286_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "wtc-ds1286",
	},
	.pwobe		= ds1286_pwobe,
};

moduwe_pwatfowm_dwivew(ds1286_pwatfowm_dwivew);

MODUWE_AUTHOW("Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>");
MODUWE_DESCWIPTION("DS1286 WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wtc-ds1286");
