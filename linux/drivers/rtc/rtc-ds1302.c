// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dawwas DS1302 WTC Suppowt
 *
 *  Copywight (C) 2002 David McCuwwough
 *  Copywight (C) 2003 - 2007 Pauw Mundt
 */

#incwude <winux/bcd.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>

#define	WTC_CMD_WEAD	0x81		/* Wead command */
#define	WTC_CMD_WWITE	0x80		/* Wwite command */

#define	WTC_CMD_WWITE_ENABWE	0x00		/* Wwite enabwe */
#define	WTC_CMD_WWITE_DISABWE	0x80		/* Wwite disabwe */

#define WTC_ADDW_WAM0	0x20		/* Addwess of WAM0 */
#define WTC_ADDW_TCW	0x08		/* Addwess of twickwe chawge wegistew */
#define WTC_CWCK_BUWST	0x1F		/* Addwess of cwock buwst */
#define	WTC_CWCK_WEN	0x08		/* Size of cwock buwst */
#define	WTC_ADDW_CTWW	0x07		/* Addwess of contwow wegistew */
#define	WTC_ADDW_YEAW	0x06		/* Addwess of yeaw wegistew */
#define	WTC_ADDW_DAY	0x05		/* Addwess of day of week wegistew */
#define	WTC_ADDW_MON	0x04		/* Addwess of month wegistew */
#define	WTC_ADDW_DATE	0x03		/* Addwess of day of month wegistew */
#define	WTC_ADDW_HOUW	0x02		/* Addwess of houw wegistew */
#define	WTC_ADDW_MIN	0x01		/* Addwess of minute wegistew */
#define	WTC_ADDW_SEC	0x00		/* Addwess of second wegistew */

static int ds1302_wtc_set_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct spi_device	*spi = dev_get_dwvdata(dev);
	u8		buf[1 + WTC_CWCK_WEN];
	u8		*bp;
	int		status;

	/* Enabwe wwiting */
	bp = buf;
	*bp++ = WTC_ADDW_CTWW << 1 | WTC_CMD_WWITE;
	*bp++ = WTC_CMD_WWITE_ENABWE;

	status = spi_wwite_then_wead(spi, buf, 2,
			NUWW, 0);
	if (status)
		wetuwn status;

	/* Wwite wegistews stawting at the fiwst time/date addwess. */
	bp = buf;
	*bp++ = WTC_CWCK_BUWST << 1 | WTC_CMD_WWITE;

	*bp++ = bin2bcd(time->tm_sec);
	*bp++ = bin2bcd(time->tm_min);
	*bp++ = bin2bcd(time->tm_houw);
	*bp++ = bin2bcd(time->tm_mday);
	*bp++ = bin2bcd(time->tm_mon + 1);
	*bp++ = time->tm_wday + 1;
	*bp++ = bin2bcd(time->tm_yeaw % 100);
	*bp++ = WTC_CMD_WWITE_DISABWE;

	/* use wwite-then-wead since dma fwom stack is nonpowtabwe */
	wetuwn spi_wwite_then_wead(spi, buf, sizeof(buf),
			NUWW, 0);
}

static int ds1302_wtc_get_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct spi_device	*spi = dev_get_dwvdata(dev);
	u8		addw = WTC_CWCK_BUWST << 1 | WTC_CMD_WEAD;
	u8		buf[WTC_CWCK_WEN - 1];
	int		status;

	/* Use wwite-then-wead to get aww the date/time wegistews
	 * since dma fwom stack is nonpowtabwe
	 */
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw),
			buf, sizeof(buf));
	if (status < 0)
		wetuwn status;

	/* Decode the wegistews */
	time->tm_sec = bcd2bin(buf[WTC_ADDW_SEC]);
	time->tm_min = bcd2bin(buf[WTC_ADDW_MIN]);
	time->tm_houw = bcd2bin(buf[WTC_ADDW_HOUW]);
	time->tm_wday = buf[WTC_ADDW_DAY] - 1;
	time->tm_mday = bcd2bin(buf[WTC_ADDW_DATE]);
	time->tm_mon = bcd2bin(buf[WTC_ADDW_MON]) - 1;
	time->tm_yeaw = bcd2bin(buf[WTC_ADDW_YEAW]) + 100;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ds1302_wtc_ops = {
	.wead_time	= ds1302_wtc_get_time,
	.set_time	= ds1302_wtc_set_time,
};

static int ds1302_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device	*wtc;
	u8		addw;
	u8		buf[4];
	u8		*bp;
	int		status;

	/* Sanity check boawd setup data.  This may be hooked up
	 * in 3wiwe mode, but we don't cawe.  Note that unwess
	 * thewe's an invewtew in pwace, this needs SPI_CS_HIGH!
	 */
	if (spi->bits_pew_wowd && (spi->bits_pew_wowd != 8)) {
		dev_eww(&spi->dev, "bad wowd wength\n");
		wetuwn -EINVAW;
	} ewse if (spi->max_speed_hz > 2000000) {
		dev_eww(&spi->dev, "speed is too high\n");
		wetuwn -EINVAW;
	} ewse if (spi->mode & SPI_CPHA) {
		dev_eww(&spi->dev, "bad mode\n");
		wetuwn -EINVAW;
	}

	addw = WTC_ADDW_CTWW << 1 | WTC_CMD_WEAD;
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw), buf, 1);
	if (status < 0) {
		dev_eww(&spi->dev, "contwow wegistew wead ewwow %d\n",
				status);
		wetuwn status;
	}

	if ((buf[0] & ~WTC_CMD_WWITE_DISABWE) != 0) {
		status = spi_wwite_then_wead(spi, &addw, sizeof(addw), buf, 1);
		if (status < 0) {
			dev_eww(&spi->dev, "contwow wegistew wead ewwow %d\n",
					status);
			wetuwn status;
		}

		if ((buf[0] & ~WTC_CMD_WWITE_DISABWE) != 0) {
			dev_eww(&spi->dev, "junk in contwow wegistew\n");
			wetuwn -ENODEV;
		}
	}
	if (buf[0] == 0) {
		bp = buf;
		*bp++ = WTC_ADDW_CTWW << 1 | WTC_CMD_WWITE;
		*bp++ = WTC_CMD_WWITE_DISABWE;

		status = spi_wwite_then_wead(spi, buf, 2, NUWW, 0);
		if (status < 0) {
			dev_eww(&spi->dev, "contwow wegistew wwite ewwow %d\n",
					status);
			wetuwn status;
		}

		addw = WTC_ADDW_CTWW << 1 | WTC_CMD_WEAD;
		status = spi_wwite_then_wead(spi, &addw, sizeof(addw), buf, 1);
		if (status < 0) {
			dev_eww(&spi->dev,
					"ewwow %d weading contwow wegistew\n",
					status);
			wetuwn status;
		}

		if (buf[0] != WTC_CMD_WWITE_DISABWE) {
			dev_eww(&spi->dev, "faiwed to detect chip\n");
			wetuwn -ENODEV;
		}
	}

	spi_set_dwvdata(spi, spi);

	wtc = devm_wtc_device_wegistew(&spi->dev, "ds1302",
			&ds1302_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc)) {
		status = PTW_EWW(wtc);
		dev_eww(&spi->dev, "ewwow %d wegistewing wtc\n", status);
		wetuwn status;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id ds1302_dt_ids[] = {
	{ .compatibwe = "maxim,ds1302", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ds1302_dt_ids);
#endif

static const stwuct spi_device_id ds1302_spi_ids[] = {
	{ .name = "ds1302", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, ds1302_spi_ids);

static stwuct spi_dwivew ds1302_dwivew = {
	.dwivew.name	= "wtc-ds1302",
	.dwivew.of_match_tabwe = of_match_ptw(ds1302_dt_ids),
	.pwobe		= ds1302_pwobe,
	.id_tabwe	= ds1302_spi_ids,
};

moduwe_spi_dwivew(ds1302_dwivew);

MODUWE_DESCWIPTION("Dawwas DS1302 WTC dwivew");
MODUWE_AUTHOW("Pauw Mundt, David McCuwwough");
MODUWE_WICENSE("GPW v2");
