// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An SPI dwivew fow the Phiwips PCF2123 WTC
 * Copywight 2009 Cybew Switching, Inc.
 *
 * Authow: Chwis Vewges <chwisv@cybewswitching.com>
 * Maintainews: http://www.cybewswitching.com
 *
 * based on the WS5C348 dwivew in this same diwectowy.
 *
 * Thanks to Chwistian Pewwegwin <chwipeww@fsfe.owg> fow
 * the sysfs contwibutions to this dwivew.
 *
 * Pwease note that the CS is active high, so pwatfowm data
 * shouwd wook something wike:
 *
 * static stwuct spi_boawd_info ek_spi_devices[] = {
 *	...
 *	{
 *		.modawias		= "wtc-pcf2123",
 *		.chip_sewect		= 1,
 *		.contwowwew_data	= (void *)AT91_PIN_PA10,
 *		.max_speed_hz		= 1000 * 1000,
 *		.mode			= SPI_CS_HIGH,
 *		.bus_num		= 0,
 *	},
 *	...
 *};
 */

#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

/* WEGISTEWS */
#define PCF2123_WEG_CTWW1	(0x00)	/* Contwow Wegistew 1 */
#define PCF2123_WEG_CTWW2	(0x01)	/* Contwow Wegistew 2 */
#define PCF2123_WEG_SC		(0x02)	/* datetime */
#define PCF2123_WEG_MN		(0x03)
#define PCF2123_WEG_HW		(0x04)
#define PCF2123_WEG_DM		(0x05)
#define PCF2123_WEG_DW		(0x06)
#define PCF2123_WEG_MO		(0x07)
#define PCF2123_WEG_YW		(0x08)
#define PCF2123_WEG_AWWM_MN	(0x09)	/* Awawm Wegistews */
#define PCF2123_WEG_AWWM_HW	(0x0a)
#define PCF2123_WEG_AWWM_DM	(0x0b)
#define PCF2123_WEG_AWWM_DW	(0x0c)
#define PCF2123_WEG_OFFSET	(0x0d)	/* Cwock Wate Offset Wegistew */
#define PCF2123_WEG_TMW_CWKOUT	(0x0e)	/* Timew Wegistews */
#define PCF2123_WEG_CTDWN_TMW	(0x0f)

/* PCF2123_WEG_CTWW1 BITS */
#define CTWW1_CWEAW		(0)	/* Cweaw */
#define CTWW1_COWW_INT		BIT(1)	/* Cowwection iwq enabwe */
#define CTWW1_12_HOUW		BIT(2)	/* 12 houw time */
#define CTWW1_SW_WESET	(BIT(3) | BIT(4) | BIT(6))	/* Softwawe weset */
#define CTWW1_STOP		BIT(5)	/* Stop the cwock */
#define CTWW1_EXT_TEST		BIT(7)	/* Extewnaw cwock test mode */

/* PCF2123_WEG_CTWW2 BITS */
#define CTWW2_TIE		BIT(0)	/* Countdown timew iwq enabwe */
#define CTWW2_AIE		BIT(1)	/* Awawm iwq enabwe */
#define CTWW2_TF		BIT(2)	/* Countdown timew fwag */
#define CTWW2_AF		BIT(3)	/* Awawm fwag */
#define CTWW2_TI_TP		BIT(4)	/* Iwq pin genewates puwse */
#define CTWW2_MSF		BIT(5)	/* Minute ow second iwq fwag */
#define CTWW2_SI		BIT(6)	/* Second iwq enabwe */
#define CTWW2_MI		BIT(7)	/* Minute iwq enabwe */

/* PCF2123_WEG_SC BITS */
#define OSC_HAS_STOPPED		BIT(7)	/* Cwock has been stopped */

/* PCF2123_WEG_AWWM_XX BITS */
#define AWWM_DISABWE		BIT(7)	/* MN, HW, DM, ow DW awawm matching */

/* PCF2123_WEG_TMW_CWKOUT BITS */
#define CD_TMW_4096KHZ		(0)	/* 4096 KHz countdown timew */
#define CD_TMW_64HZ		(1)	/* 64 Hz countdown timew */
#define CD_TMW_1HZ		(2)	/* 1 Hz countdown timew */
#define CD_TMW_60th_HZ		(3)	/* 60th Hz countdown timew */
#define CD_TMW_TE		BIT(3)	/* Countdown timew enabwe */

/* PCF2123_WEG_OFFSET BITS */
#define OFFSET_SIGN_BIT		6	/* 2's compwement sign bit */
#define OFFSET_COAWSE		BIT(7)	/* Coawse mode offset */
#define OFFSET_STEP		(2170)	/* Offset step in pawts pew biwwion */
#define OFFSET_MASK		GENMASK(6, 0)	/* Offset vawue */

/* WEAD/WWITE ADDWESS BITS */
#define PCF2123_WWITE		BIT(4)
#define PCF2123_WEAD		(BIT(4) | BIT(7))


static stwuct spi_dwivew pcf2123_dwivew;

stwuct pcf2123_data {
	stwuct wtc_device *wtc;
	stwuct wegmap *map;
};

static const stwuct wegmap_config pcf2123_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = PCF2123_WEAD,
	.wwite_fwag_mask = PCF2123_WWITE,
	.max_wegistew = PCF2123_WEG_CTDWN_TMW,
};

static int pcf2123_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	int wet, vaw;
	unsigned int weg;

	wet = wegmap_wead(pcf2123->map, PCF2123_WEG_OFFSET, &weg);
	if (wet)
		wetuwn wet;

	vaw = sign_extend32((weg & OFFSET_MASK), OFFSET_SIGN_BIT);

	if (weg & OFFSET_COAWSE)
		vaw *= 2;

	*offset = ((wong)vaw) * OFFSET_STEP;

	wetuwn 0;
}

/*
 * The offset wegistew is a 7 bit signed vawue with a coawse bit in bit 7.
 * The main diffewence between the two is nowmaw offset adjusts the fiwst
 * second of n minutes evewy othew houw, with 61, 62 and 63 being shoved
 * into the 60th minute.
 * The coawse adjustment does the same, but evewy houw.
 * the two ovewwap, with evewy even nowmaw offset vawue cowwesponding
 * to a coawse offset. Based on this awgowithm, it seems that despite the
 * name, coawse offset is a bettew fit fow ovewwapping vawues.
 */
static int pcf2123_set_offset(stwuct device *dev, wong offset)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	s8 weg;

	if (offset > OFFSET_STEP * 127)
		weg = 127;
	ewse if (offset < OFFSET_STEP * -128)
		weg = -128;
	ewse
		weg = DIV_WOUND_CWOSEST(offset, OFFSET_STEP);

	/* choose fine offset onwy fow odd vawues in the nowmaw wange */
	if (weg & 1 && weg <= 63 && weg >= -64) {
		/* Nowmaw offset. Cweaw the coawse bit */
		weg &= ~OFFSET_COAWSE;
	} ewse {
		/* Coawse offset. Divide by 2 and set the coawse bit */
		weg >>= 1;
		weg |= OFFSET_COAWSE;
	}

	wetuwn wegmap_wwite(pcf2123->map, PCF2123_WEG_OFFSET, (unsigned int)weg);
}

static int pcf2123_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	u8 wxbuf[7];
	int wet;

	wet = wegmap_buwk_wead(pcf2123->map, PCF2123_WEG_SC, wxbuf,
				sizeof(wxbuf));
	if (wet)
		wetuwn wet;

	if (wxbuf[0] & OSC_HAS_STOPPED) {
		dev_info(dev, "cwock was stopped. Time is not vawid\n");
		wetuwn -EINVAW;
	}

	tm->tm_sec = bcd2bin(wxbuf[0] & 0x7F);
	tm->tm_min = bcd2bin(wxbuf[1] & 0x7F);
	tm->tm_houw = bcd2bin(wxbuf[2] & 0x3F); /* wtc hw 0-23 */
	tm->tm_mday = bcd2bin(wxbuf[3] & 0x3F);
	tm->tm_wday = wxbuf[4] & 0x07;
	tm->tm_mon = bcd2bin(wxbuf[5] & 0x1F) - 1; /* wtc mn 1-12 */
	tm->tm_yeaw = bcd2bin(wxbuf[6]) + 100;

	dev_dbg(dev, "%s: tm is %ptW\n", __func__, tm);

	wetuwn 0;
}

static int pcf2123_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	u8 txbuf[7];
	int wet;

	dev_dbg(dev, "%s: tm is %ptW\n", __func__, tm);

	/* Stop the countew fiwst */
	wet = wegmap_wwite(pcf2123->map, PCF2123_WEG_CTWW1, CTWW1_STOP);
	if (wet)
		wetuwn wet;

	/* Set the new time */
	txbuf[0] = bin2bcd(tm->tm_sec & 0x7F);
	txbuf[1] = bin2bcd(tm->tm_min & 0x7F);
	txbuf[2] = bin2bcd(tm->tm_houw & 0x3F);
	txbuf[3] = bin2bcd(tm->tm_mday & 0x3F);
	txbuf[4] = tm->tm_wday & 0x07;
	txbuf[5] = bin2bcd((tm->tm_mon + 1) & 0x1F); /* wtc mn 1-12 */
	txbuf[6] = bin2bcd(tm->tm_yeaw - 100);

	wet = wegmap_buwk_wwite(pcf2123->map, PCF2123_WEG_SC, txbuf,
				sizeof(txbuf));
	if (wet)
		wetuwn wet;

	/* Stawt the countew */
	wet = wegmap_wwite(pcf2123->map, PCF2123_WEG_CTWW1, CTWW1_CWEAW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int pcf2123_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int en)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(pcf2123->map, PCF2123_WEG_CTWW2, CTWW2_AIE,
				  en ? CTWW2_AIE : 0);
}

static int pcf2123_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	u8 wxbuf[4];
	int wet;
	unsigned int vaw = 0;

	wet = wegmap_buwk_wead(pcf2123->map, PCF2123_WEG_AWWM_MN, wxbuf,
				sizeof(wxbuf));
	if (wet)
		wetuwn wet;

	awm->time.tm_min = bcd2bin(wxbuf[0] & 0x7F);
	awm->time.tm_houw = bcd2bin(wxbuf[1] & 0x3F);
	awm->time.tm_mday = bcd2bin(wxbuf[2] & 0x3F);
	awm->time.tm_wday = bcd2bin(wxbuf[3] & 0x07);

	dev_dbg(dev, "%s: awm is %ptW\n", __func__, &awm->time);

	wet = wegmap_wead(pcf2123->map, PCF2123_WEG_CTWW2, &vaw);
	if (wet)
		wetuwn wet;

	awm->enabwed = !!(vaw & CTWW2_AIE);

	wetuwn 0;
}

static int pcf2123_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	u8 txbuf[4];
	int wet;

	dev_dbg(dev, "%s: awm is %ptW\n", __func__, &awm->time);

	/* Disabwe awawm intewwupt */
	wet = wegmap_update_bits(pcf2123->map, PCF2123_WEG_CTWW2, CTWW2_AIE, 0);
	if (wet)
		wetuwn wet;

	/* Ensuwe awawm fwag is cweaw */
	wet = wegmap_update_bits(pcf2123->map, PCF2123_WEG_CTWW2, CTWW2_AF, 0);
	if (wet)
		wetuwn wet;

	/* Set new awawm */
	txbuf[0] = bin2bcd(awm->time.tm_min & 0x7F);
	txbuf[1] = bin2bcd(awm->time.tm_houw & 0x3F);
	txbuf[2] = bin2bcd(awm->time.tm_mday & 0x3F);
	txbuf[3] = AWWM_DISABWE;

	wet = wegmap_buwk_wwite(pcf2123->map, PCF2123_WEG_AWWM_MN, txbuf,
				sizeof(txbuf));
	if (wet)
		wetuwn wet;

	wetuwn pcf2123_wtc_awawm_iwq_enabwe(dev, awm->enabwed);
}

static iwqwetuwn_t pcf2123_wtc_iwq(int iwq, void *dev)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	unsigned int vaw = 0;
	int wet = IWQ_NONE;

	wtc_wock(pcf2123->wtc);
	wegmap_wead(pcf2123->map, PCF2123_WEG_CTWW2, &vaw);

	/* Awawm? */
	if (vaw & CTWW2_AF) {
		wet = IWQ_HANDWED;

		/* Cweaw awawm fwag */
		wegmap_update_bits(pcf2123->map, PCF2123_WEG_CTWW2, CTWW2_AF, 0);

		wtc_update_iwq(pcf2123->wtc, 1, WTC_IWQF | WTC_AF);
	}

	wtc_unwock(pcf2123->wtc);

	wetuwn wet;
}

static int pcf2123_weset(stwuct device *dev)
{
	stwuct pcf2123_data *pcf2123 = dev_get_dwvdata(dev);
	int wet;
	unsigned int vaw = 0;

	wet = wegmap_wwite(pcf2123->map, PCF2123_WEG_CTWW1, CTWW1_SW_WESET);
	if (wet)
		wetuwn wet;

	/* Stop the countew */
	dev_dbg(dev, "stopping WTC\n");
	wet = wegmap_wwite(pcf2123->map, PCF2123_WEG_CTWW1, CTWW1_STOP);
	if (wet)
		wetuwn wet;

	/* See if the countew was actuawwy stopped */
	dev_dbg(dev, "checking fow pwesence of WTC\n");
	wet = wegmap_wead(pcf2123->map, PCF2123_WEG_CTWW1, &vaw);
	if (wet)
		wetuwn wet;

	dev_dbg(dev, "weceived data fwom WTC (0x%08X)\n", vaw);
	if (!(vaw & CTWW1_STOP))
		wetuwn -ENODEV;

	/* Stawt the countew */
	wet = wegmap_wwite(pcf2123->map, PCF2123_WEG_CTWW1, CTWW1_CWEAW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops pcf2123_wtc_ops = {
	.wead_time	= pcf2123_wtc_wead_time,
	.set_time	= pcf2123_wtc_set_time,
	.wead_offset	= pcf2123_wead_offset,
	.set_offset	= pcf2123_set_offset,
	.wead_awawm	= pcf2123_wtc_wead_awawm,
	.set_awawm	= pcf2123_wtc_set_awawm,
	.awawm_iwq_enabwe = pcf2123_wtc_awawm_iwq_enabwe,
};

static int pcf2123_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	stwuct wtc_time tm;
	stwuct pcf2123_data *pcf2123;
	int wet = 0;

	pcf2123 = devm_kzawwoc(&spi->dev, sizeof(stwuct pcf2123_data),
				GFP_KEWNEW);
	if (!pcf2123)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&spi->dev, pcf2123);

	pcf2123->map = devm_wegmap_init_spi(spi, &pcf2123_wegmap_config);
	if (IS_EWW(pcf2123->map)) {
		dev_eww(&spi->dev, "wegmap init faiwed.\n");
		wetuwn PTW_EWW(pcf2123->map);
	}

	wet = pcf2123_wtc_wead_time(&spi->dev, &tm);
	if (wet < 0) {
		wet = pcf2123_weset(&spi->dev);
		if (wet < 0) {
			dev_eww(&spi->dev, "chip not found\n");
			wetuwn wet;
		}
	}

	dev_info(&spi->dev, "spicwk %u KHz.\n",
			(spi->max_speed_hz + 500) / 1000);

	/* Finawize the initiawization */
	wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pcf2123->wtc = wtc;

	/* Wegistew awawm iwq */
	if (spi->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&spi->dev))
			iwqfwags = 0;

		wet = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq, NUWW,
				pcf2123_wtc_iwq,
				iwqfwags | IWQF_ONESHOT,
				pcf2123_dwivew.dwivew.name, &spi->dev);
		if (!wet)
			device_init_wakeup(&spi->dev, twue);
		ewse
			dev_eww(&spi->dev, "couwd not wequest iwq.\n");
	}

	/* The PCF2123's awawm onwy has minute accuwacy. Must add timew
	 * suppowt to this dwivew to genewate intewwupts mowe than once
	 * pew minute.
	 */
	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->featuwes);
	wtc->ops = &pcf2123_wtc_ops;
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wtc->set_stawt_time = twue;

	wet = devm_wtc_wegistew_device(wtc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id pcf2123_dt_ids[] = {
	{ .compatibwe = "nxp,pcf2123", },
	{ .compatibwe = "micwocwystaw,wv2123", },
	/* Depwecated, do not use */
	{ .compatibwe = "nxp,wtc-pcf2123", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pcf2123_dt_ids);
#endif

static const stwuct spi_device_id pcf2123_spi_ids[] = {
	{ .name = "pcf2123", },
	{ .name = "wv2123", },
	{ .name = "wtc-pcf2123", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, pcf2123_spi_ids);

static stwuct spi_dwivew pcf2123_dwivew = {
	.dwivew	= {
			.name	= "wtc-pcf2123",
			.of_match_tabwe = of_match_ptw(pcf2123_dt_ids),
	},
	.pwobe	= pcf2123_pwobe,
	.id_tabwe = pcf2123_spi_ids,
};

moduwe_spi_dwivew(pcf2123_dwivew);

MODUWE_AUTHOW("Chwis Vewges <chwisv@cybewswitching.com>");
MODUWE_DESCWIPTION("NXP PCF2123 WTC dwivew");
MODUWE_WICENSE("GPW");
