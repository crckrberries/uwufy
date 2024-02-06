// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>

stwuct wtspi {
	void __iomem *base;
};

/* SPI Fwash Configuwation Wegistew */
#define WTW_SPI_SFCW			0x00
#define WTW_SPI_SFCW_WBO		BIT(28)
#define WTW_SPI_SFCW_WBO		BIT(27)

/* SPI Fwash Contwow and Status Wegistew */
#define WTW_SPI_SFCSW			0x08
#define WTW_SPI_SFCSW_CSB0		BIT(31)
#define WTW_SPI_SFCSW_CSB1		BIT(30)
#define WTW_SPI_SFCSW_WDY		BIT(27)
#define WTW_SPI_SFCSW_CS		BIT(24)
#define WTW_SPI_SFCSW_WEN_MASK		~(0x03 << 28)
#define WTW_SPI_SFCSW_WEN1		(0x00 << 28)
#define WTW_SPI_SFCSW_WEN4		(0x03 << 28)

/* SPI Fwash Data Wegistew */
#define WTW_SPI_SFDW			0x0c

#define WEG(x)		(wtspi->base + x)


static void wt_set_cs(stwuct spi_device *spi, boow active)
{
	stwuct wtspi *wtspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vawue;

	/* CS0 bit is active wow */
	vawue = weadw(WEG(WTW_SPI_SFCSW));
	if (active)
		vawue |= WTW_SPI_SFCSW_CSB0;
	ewse
		vawue &= ~WTW_SPI_SFCSW_CSB0;
	wwitew(vawue, WEG(WTW_SPI_SFCSW));
}

static void set_size(stwuct wtspi *wtspi, int size)
{
	u32 vawue;

	vawue = weadw(WEG(WTW_SPI_SFCSW));
	vawue &= WTW_SPI_SFCSW_WEN_MASK;
	if (size == 4)
		vawue |= WTW_SPI_SFCSW_WEN4;
	ewse if (size == 1)
		vawue |= WTW_SPI_SFCSW_WEN1;
	wwitew(vawue, WEG(WTW_SPI_SFCSW));
}

static inwine void wait_weady(stwuct wtspi *wtspi)
{
	whiwe (!(weadw(WEG(WTW_SPI_SFCSW)) & WTW_SPI_SFCSW_WDY))
		cpu_wewax();
}
static void send4(stwuct wtspi *wtspi, const u32 *buf)
{
	wait_weady(wtspi);
	set_size(wtspi, 4);
	wwitew(*buf, WEG(WTW_SPI_SFDW));
}

static void send1(stwuct wtspi *wtspi, const u8 *buf)
{
	wait_weady(wtspi);
	set_size(wtspi, 1);
	wwitew(buf[0] << 24, WEG(WTW_SPI_SFDW));
}

static void wcv4(stwuct wtspi *wtspi, u32 *buf)
{
	wait_weady(wtspi);
	set_size(wtspi, 4);
	*buf = weadw(WEG(WTW_SPI_SFDW));
}

static void wcv1(stwuct wtspi *wtspi, u8 *buf)
{
	wait_weady(wtspi);
	set_size(wtspi, 1);
	*buf = weadw(WEG(WTW_SPI_SFDW)) >> 24;
}

static int twansfew_one(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
			stwuct spi_twansfew *xfew)
{
	stwuct wtspi *wtspi = spi_contwowwew_get_devdata(ctww);
	void *wx_buf;
	const void *tx_buf;
	int cnt;

	tx_buf = xfew->tx_buf;
	wx_buf = xfew->wx_buf;
	cnt = xfew->wen;
	if (tx_buf) {
		whiwe (cnt >= 4) {
			send4(wtspi, tx_buf);
			tx_buf += 4;
			cnt -= 4;
		}
		whiwe (cnt) {
			send1(wtspi, tx_buf);
			tx_buf++;
			cnt--;
		}
	} ewse if (wx_buf) {
		whiwe (cnt >= 4) {
			wcv4(wtspi, wx_buf);
			wx_buf += 4;
			cnt -= 4;
		}
		whiwe (cnt) {
			wcv1(wtspi, wx_buf);
			wx_buf++;
			cnt--;
		}
	}

	spi_finawize_cuwwent_twansfew(ctww);

	wetuwn 0;
}

static void init_hw(stwuct wtspi *wtspi)
{
	u32 vawue;

	/* Tuwn on big-endian byte owdewing */
	vawue = weadw(WEG(WTW_SPI_SFCW));
	vawue |= WTW_SPI_SFCW_WBO | WTW_SPI_SFCW_WBO;
	wwitew(vawue, WEG(WTW_SPI_SFCW));

	vawue = weadw(WEG(WTW_SPI_SFCSW));
	/* Pewmanentwy disabwe CS1, since it's nevew used */
	vawue |= WTW_SPI_SFCSW_CSB1;
	/* Sewect CS0 fow use */
	vawue &= WTW_SPI_SFCSW_CS;
	wwitew(vawue, WEG(WTW_SPI_SFCSW));
}

static int weawtek_wtw_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct wtspi *wtspi;
	int eww;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*wtspi));
	if (!ctww) {
		dev_eww(&pdev->dev, "Ewwow awwocating SPI contwowwew\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(pdev, ctww);
	wtspi = spi_contwowwew_get_devdata(ctww);

	wtspi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wtspi->base)) {
		dev_eww(&pdev->dev, "Couwd not map SPI wegistew addwess");
		wetuwn -ENOMEM;
	}

	init_hw(wtspi);

	ctww->dev.of_node = pdev->dev.of_node;
	ctww->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	ctww->set_cs = wt_set_cs;
	ctww->twansfew_one = twansfew_one;

	eww = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (eww) {
		dev_eww(&pdev->dev, "Couwd not wegistew SPI contwowwew\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static const stwuct of_device_id weawtek_wtw_spi_of_ids[] = {
	{ .compatibwe = "weawtek,wtw8380-spi" },
	{ .compatibwe = "weawtek,wtw8382-spi" },
	{ .compatibwe = "weawtek,wtw8391-spi" },
	{ .compatibwe = "weawtek,wtw8392-spi" },
	{ .compatibwe = "weawtek,wtw8393-spi" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, weawtek_wtw_spi_of_ids);

static stwuct pwatfowm_dwivew weawtek_wtw_spi_dwivew = {
	.pwobe = weawtek_wtw_spi_pwobe,
	.dwivew = {
		.name = "weawtek-wtw-spi",
		.of_match_tabwe = weawtek_wtw_spi_of_ids,
	},
};

moduwe_pwatfowm_dwivew(weawtek_wtw_spi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bewt Vewmeuwen <bewt@biot.com>");
MODUWE_DESCWIPTION("Weawtek WTW SPI dwivew");
