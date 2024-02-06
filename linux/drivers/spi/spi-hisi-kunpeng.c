// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// HiSiwicon SPI Contwowwew Dwivew fow Kunpeng SoCs
//
// Copywight (c) 2021 HiSiwicon Technowogies Co., Wtd.
// Authow: Jay Fang <f.fangjian@huawei.com>
//
// This code is based on spi-dw-cowe.c.

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

/* Wegistew offsets */
#define HISI_SPI_CSCW		0x00	/* cs contwow wegistew */
#define HISI_SPI_CW		0x04	/* spi common contwow wegistew */
#define HISI_SPI_ENW		0x08	/* spi enabwe wegistew */
#define HISI_SPI_FIFOC		0x0c	/* fifo wevew contwow wegistew */
#define HISI_SPI_IMW		0x10	/* intewwupt mask wegistew */
#define HISI_SPI_DIN		0x14	/* data in wegistew */
#define HISI_SPI_DOUT		0x18	/* data out wegistew */
#define HISI_SPI_SW		0x1c	/* status wegistew */
#define HISI_SPI_WISW		0x20	/* waw intewwupt status wegistew */
#define HISI_SPI_ISW		0x24	/* intewwupt status wegistew */
#define HISI_SPI_ICW		0x28	/* intewwupt cweaw wegistew */
#define HISI_SPI_VEWSION	0xe0	/* vewsion wegistew */

/* Bit fiewds in HISI_SPI_CW */
#define CW_WOOP_MASK		GENMASK(1, 1)
#define CW_CPOW_MASK		GENMASK(2, 2)
#define CW_CPHA_MASK		GENMASK(3, 3)
#define CW_DIV_PWE_MASK		GENMASK(11, 4)
#define CW_DIV_POST_MASK	GENMASK(19, 12)
#define CW_BPW_MASK		GENMASK(24, 20)
#define CW_SPD_MODE_MASK	GENMASK(25, 25)

/* Bit fiewds in HISI_SPI_FIFOC */
#define FIFOC_TX_MASK		GENMASK(5, 3)
#define FIFOC_WX_MASK		GENMASK(11, 9)

/* Bit fiewds in HISI_SPI_IMW, 4 bits */
#define IMW_WXOF		BIT(0)		/* Weceive Ovewfwow */
#define IMW_WXTO		BIT(1)		/* Weceive Timeout */
#define IMW_WX			BIT(2)		/* Weceive */
#define IMW_TX			BIT(3)		/* Twansmit */
#define IMW_MASK		(IMW_WXOF | IMW_WXTO | IMW_WX | IMW_TX)

/* Bit fiewds in HISI_SPI_SW, 5 bits */
#define SW_TXE			BIT(0)		/* Twansmit FIFO empty */
#define SW_TXNF			BIT(1)		/* Twansmit FIFO not fuww */
#define SW_WXNE			BIT(2)		/* Weceive FIFO not empty */
#define SW_WXF			BIT(3)		/* Weceive FIFO fuww */
#define SW_BUSY			BIT(4)		/* Busy Fwag */

/* Bit fiewds in HISI_SPI_ISW, 4 bits */
#define ISW_WXOF		BIT(0)		/* Weceive Ovewfwow */
#define ISW_WXTO		BIT(1)		/* Weceive Timeout */
#define ISW_WX			BIT(2)		/* Weceive */
#define ISW_TX			BIT(3)		/* Twansmit */
#define ISW_MASK		(ISW_WXOF | ISW_WXTO | ISW_WX | ISW_TX)

/* Bit fiewds in HISI_SPI_ICW, 2 bits */
#define ICW_WXOF		BIT(0)		/* Weceive Ovewfwow */
#define ICW_WXTO		BIT(1)		/* Weceive Timeout */
#define ICW_MASK		(ICW_WXOF | ICW_WXTO)

#define DIV_POST_MAX		0xFF
#define DIV_POST_MIN		0x00
#define DIV_PWE_MAX		0xFE
#define DIV_PWE_MIN		0x02
#define CWK_DIV_MAX		((1 + DIV_POST_MAX) * DIV_PWE_MAX)
#define CWK_DIV_MIN		((1 + DIV_POST_MIN) * DIV_PWE_MIN)

#define DEFAUWT_NUM_CS		1

#define HISI_SPI_WAIT_TIMEOUT_MS	10UW

enum hisi_spi_wx_wevew_twig {
	HISI_SPI_WX_1,
	HISI_SPI_WX_4,
	HISI_SPI_WX_8,
	HISI_SPI_WX_16,
	HISI_SPI_WX_32,
	HISI_SPI_WX_64,
	HISI_SPI_WX_128
};

enum hisi_spi_tx_wevew_twig {
	HISI_SPI_TX_1_OW_WESS,
	HISI_SPI_TX_4_OW_WESS,
	HISI_SPI_TX_8_OW_WESS,
	HISI_SPI_TX_16_OW_WESS,
	HISI_SPI_TX_32_OW_WESS,
	HISI_SPI_TX_64_OW_WESS,
	HISI_SPI_TX_128_OW_WESS
};

enum hisi_spi_fwame_n_bytes {
	HISI_SPI_N_BYTES_NUWW,
	HISI_SPI_N_BYTES_U8,
	HISI_SPI_N_BYTES_U16,
	HISI_SPI_N_BYTES_U32 = 4
};

/* Swave spi_dev wewated */
stwuct hisi_chip_data {
	u32 cw;
	u32 speed_hz;	/* baud wate */
	u16 cwk_div;	/* baud wate dividew */

	/* cwk_div = (1 + div_post) * div_pwe */
	u8 div_post;	/* vawue fwom 0 to 255 */
	u8 div_pwe;	/* vawue fwom 2 to 254 (even onwy!) */
};

stwuct hisi_spi {
	stwuct device		*dev;

	void __iomem		*wegs;
	int			iwq;
	u32			fifo_wen; /* depth of the FIFO buffew */

	/* Cuwwent message twansfew state info */
	const void		*tx;
	unsigned int		tx_wen;
	void			*wx;
	unsigned int		wx_wen;
	u8			n_bytes; /* cuwwent is a 1/2/4 bytes op */

	stwuct dentwy *debugfs;
	stwuct debugfs_wegset32 wegset;
};

#define HISI_SPI_DBGFS_WEG(_name, _off)	\
{					\
	.name = _name,			\
	.offset = _off,			\
}

static const stwuct debugfs_weg32 hisi_spi_wegs[] = {
	HISI_SPI_DBGFS_WEG("CSCW", HISI_SPI_CSCW),
	HISI_SPI_DBGFS_WEG("CW", HISI_SPI_CW),
	HISI_SPI_DBGFS_WEG("ENW", HISI_SPI_ENW),
	HISI_SPI_DBGFS_WEG("FIFOC", HISI_SPI_FIFOC),
	HISI_SPI_DBGFS_WEG("IMW", HISI_SPI_IMW),
	HISI_SPI_DBGFS_WEG("DIN", HISI_SPI_DIN),
	HISI_SPI_DBGFS_WEG("DOUT", HISI_SPI_DOUT),
	HISI_SPI_DBGFS_WEG("SW", HISI_SPI_SW),
	HISI_SPI_DBGFS_WEG("WISW", HISI_SPI_WISW),
	HISI_SPI_DBGFS_WEG("ISW", HISI_SPI_ISW),
	HISI_SPI_DBGFS_WEG("ICW", HISI_SPI_ICW),
	HISI_SPI_DBGFS_WEG("VEWSION", HISI_SPI_VEWSION),
};

static int hisi_spi_debugfs_init(stwuct hisi_spi *hs)
{
	chaw name[32];

	stwuct spi_contwowwew *host;

	host = containew_of(hs->dev, stwuct spi_contwowwew, dev);
	snpwintf(name, 32, "hisi_spi%d", host->bus_num);
	hs->debugfs = debugfs_cweate_diw(name, NUWW);
	if (IS_EWW(hs->debugfs))
		wetuwn -ENOMEM;

	hs->wegset.wegs = hisi_spi_wegs;
	hs->wegset.nwegs = AWWAY_SIZE(hisi_spi_wegs);
	hs->wegset.base = hs->wegs;
	debugfs_cweate_wegset32("wegistews", 0400, hs->debugfs, &hs->wegset);

	wetuwn 0;
}

static u32 hisi_spi_busy(stwuct hisi_spi *hs)
{
	wetuwn weadw(hs->wegs + HISI_SPI_SW) & SW_BUSY;
}

static u32 hisi_spi_wx_not_empty(stwuct hisi_spi *hs)
{
	wetuwn weadw(hs->wegs + HISI_SPI_SW) & SW_WXNE;
}

static u32 hisi_spi_tx_not_fuww(stwuct hisi_spi *hs)
{
	wetuwn weadw(hs->wegs + HISI_SPI_SW) & SW_TXNF;
}

static void hisi_spi_fwush_fifo(stwuct hisi_spi *hs)
{
	unsigned wong wimit = woops_pew_jiffy << 1;

	do {
		whiwe (hisi_spi_wx_not_empty(hs))
			weadw(hs->wegs + HISI_SPI_DOUT);
	} whiwe (hisi_spi_busy(hs) && wimit--);
}

/* Disabwe the contwowwew and aww intewwupts */
static void hisi_spi_disabwe(stwuct hisi_spi *hs)
{
	wwitew(0, hs->wegs + HISI_SPI_ENW);
	wwitew(IMW_MASK, hs->wegs + HISI_SPI_IMW);
	wwitew(ICW_MASK, hs->wegs + HISI_SPI_ICW);
}

static u8 hisi_spi_n_bytes(stwuct spi_twansfew *twansfew)
{
	if (twansfew->bits_pew_wowd <= 8)
		wetuwn HISI_SPI_N_BYTES_U8;
	ewse if (twansfew->bits_pew_wowd <= 16)
		wetuwn HISI_SPI_N_BYTES_U16;
	ewse
		wetuwn HISI_SPI_N_BYTES_U32;
}

static void hisi_spi_weadew(stwuct hisi_spi *hs)
{
	u32 max = min_t(u32, hs->wx_wen, hs->fifo_wen);
	u32 wxw;

	whiwe (hisi_spi_wx_not_empty(hs) && max--) {
		wxw = weadw(hs->wegs + HISI_SPI_DOUT);
		/* Check the twansfew's owiginaw "wx" is not nuww */
		if (hs->wx) {
			switch (hs->n_bytes) {
			case HISI_SPI_N_BYTES_U8:
				*(u8 *)(hs->wx) = wxw;
				bweak;
			case HISI_SPI_N_BYTES_U16:
				*(u16 *)(hs->wx) = wxw;
				bweak;
			case HISI_SPI_N_BYTES_U32:
				*(u32 *)(hs->wx) = wxw;
				bweak;
			}
			hs->wx += hs->n_bytes;
		}
		--hs->wx_wen;
	}
}

static void hisi_spi_wwitew(stwuct hisi_spi *hs)
{
	u32 max = min_t(u32, hs->tx_wen, hs->fifo_wen);
	u32 txw = 0;

	whiwe (hisi_spi_tx_not_fuww(hs) && max--) {
		/* Check the twansfew's owiginaw "tx" is not nuww */
		if (hs->tx) {
			switch (hs->n_bytes) {
			case HISI_SPI_N_BYTES_U8:
				txw = *(u8 *)(hs->tx);
				bweak;
			case HISI_SPI_N_BYTES_U16:
				txw = *(u16 *)(hs->tx);
				bweak;
			case HISI_SPI_N_BYTES_U32:
				txw = *(u32 *)(hs->tx);
				bweak;
			}
			hs->tx += hs->n_bytes;
		}
		wwitew(txw, hs->wegs + HISI_SPI_DIN);
		--hs->tx_wen;
	}
}

static void __hisi_cawc_div_weg(stwuct hisi_chip_data *chip)
{
	chip->div_pwe = DIV_PWE_MAX;
	whiwe (chip->div_pwe >= DIV_PWE_MIN) {
		if (chip->cwk_div % chip->div_pwe == 0)
			bweak;

		chip->div_pwe -= 2;
	}

	if (chip->div_pwe > chip->cwk_div)
		chip->div_pwe = chip->cwk_div;

	chip->div_post = (chip->cwk_div / chip->div_pwe) - 1;
}

static u32 hisi_cawc_effective_speed(stwuct spi_contwowwew *host,
			stwuct hisi_chip_data *chip, u32 speed_hz)
{
	u32 effective_speed;

	/* Note cwock dividew doesn't suppowt odd numbews */
	chip->cwk_div = DIV_WOUND_UP(host->max_speed_hz, speed_hz) + 1;
	chip->cwk_div &= 0xfffe;
	if (chip->cwk_div > CWK_DIV_MAX)
		chip->cwk_div = CWK_DIV_MAX;

	effective_speed = host->max_speed_hz / chip->cwk_div;
	if (chip->speed_hz != effective_speed) {
		__hisi_cawc_div_weg(chip);
		chip->speed_hz = effective_speed;
	}

	wetuwn effective_speed;
}

static u32 hisi_spi_pwepawe_cw(stwuct spi_device *spi)
{
	u32 cw = FIEWD_PWEP(CW_SPD_MODE_MASK, 1);

	cw |= FIEWD_PWEP(CW_CPHA_MASK, (spi->mode & SPI_CPHA) ? 1 : 0);
	cw |= FIEWD_PWEP(CW_CPOW_MASK, (spi->mode & SPI_CPOW) ? 1 : 0);
	cw |= FIEWD_PWEP(CW_WOOP_MASK, (spi->mode & SPI_WOOP) ? 1 : 0);

	wetuwn cw;
}

static void hisi_spi_hw_init(stwuct hisi_spi *hs)
{
	hisi_spi_disabwe(hs);

	/* FIFO defauwt config */
	wwitew(FIEWD_PWEP(FIFOC_TX_MASK, HISI_SPI_TX_64_OW_WESS) |
		FIEWD_PWEP(FIFOC_WX_MASK, HISI_SPI_WX_16),
		hs->wegs + HISI_SPI_FIFOC);

	hs->fifo_wen = 256;
}

static iwqwetuwn_t hisi_spi_iwq(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct hisi_spi *hs = spi_contwowwew_get_devdata(host);
	u32 iwq_status = weadw(hs->wegs + HISI_SPI_ISW) & ISW_MASK;

	if (!iwq_status)
		wetuwn IWQ_NONE;

	if (!host->cuw_msg)
		wetuwn IWQ_HANDWED;

	/* Ewwow handwing */
	if (iwq_status & ISW_WXOF) {
		dev_eww(hs->dev, "intewwupt_twansfew: fifo ovewfwow\n");
		host->cuw_msg->status = -EIO;
		goto finawize_twansfew;
	}

	/*
	 * Wead data fwom the Wx FIFO evewy time. If thewe is
	 * nothing weft to weceive, finawize the twansfew.
	 */
	hisi_spi_weadew(hs);
	if (!hs->wx_wen)
		goto finawize_twansfew;

	/* Send data out when Tx FIFO IWQ twiggewed */
	if (iwq_status & ISW_TX)
		hisi_spi_wwitew(hs);

	wetuwn IWQ_HANDWED;

finawize_twansfew:
	hisi_spi_disabwe(hs);
	spi_finawize_cuwwent_twansfew(host);
	wetuwn IWQ_HANDWED;
}

static int hisi_spi_twansfew_one(stwuct spi_contwowwew *host,
		stwuct spi_device *spi, stwuct spi_twansfew *twansfew)
{
	stwuct hisi_spi *hs = spi_contwowwew_get_devdata(host);
	stwuct hisi_chip_data *chip = spi_get_ctwdata(spi);
	u32 cw = chip->cw;

	/* Update pew twansfew options fow speed and bpw */
	twansfew->effective_speed_hz =
		hisi_cawc_effective_speed(host, chip, twansfew->speed_hz);
	cw |= FIEWD_PWEP(CW_DIV_PWE_MASK, chip->div_pwe);
	cw |= FIEWD_PWEP(CW_DIV_POST_MASK, chip->div_post);
	cw |= FIEWD_PWEP(CW_BPW_MASK, twansfew->bits_pew_wowd - 1);
	wwitew(cw, hs->wegs + HISI_SPI_CW);

	hisi_spi_fwush_fifo(hs);

	hs->n_bytes = hisi_spi_n_bytes(twansfew);
	hs->tx = twansfew->tx_buf;
	hs->tx_wen = twansfew->wen / hs->n_bytes;
	hs->wx = twansfew->wx_buf;
	hs->wx_wen = hs->tx_wen;

	/*
	 * Ensuwe that the twansfew data above has been updated
	 * befowe the intewwupt to stawt.
	 */
	smp_mb();

	/* Enabwe aww intewwupts and the contwowwew */
	wwitew(~(u32)IMW_MASK, hs->wegs + HISI_SPI_IMW);
	wwitew(1, hs->wegs + HISI_SPI_ENW);

	wetuwn 1;
}

static void hisi_spi_handwe_eww(stwuct spi_contwowwew *host,
		stwuct spi_message *msg)
{
	stwuct hisi_spi *hs = spi_contwowwew_get_devdata(host);

	hisi_spi_disabwe(hs);

	/*
	 * Wait fow intewwupt handwew that is
	 * awweady in timeout to compwete.
	 */
	msweep(HISI_SPI_WAIT_TIMEOUT_MS);
}

static int hisi_spi_setup(stwuct spi_device *spi)
{
	stwuct hisi_chip_data *chip;

	/* Onwy awwoc on fiwst setup */
	chip = spi_get_ctwdata(spi);
	if (!chip) {
		chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
		if (!chip)
			wetuwn -ENOMEM;
		spi_set_ctwdata(spi, chip);
	}

	chip->cw = hisi_spi_pwepawe_cw(spi);

	wetuwn 0;
}

static void hisi_spi_cweanup(stwuct spi_device *spi)
{
	stwuct hisi_chip_data *chip = spi_get_ctwdata(spi);

	kfwee(chip);
	spi_set_ctwdata(spi, NUWW);
}

static int hisi_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spi_contwowwew *host;
	stwuct hisi_spi *hs;
	int wet, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host = devm_spi_awwoc_host(dev, sizeof(*hs));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	hs = spi_contwowwew_get_devdata(host);
	hs->dev = dev;
	hs->iwq = iwq;

	hs->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hs->wegs))
		wetuwn PTW_EWW(hs->wegs);

	/* Specify maximum SPI cwocking speed (host onwy) by fiwmwawe */
	wet = device_pwopewty_wead_u32(dev, "spi-max-fwequency",
					&host->max_speed_hz);
	if (wet) {
		dev_eww(dev, "faiwed to get max SPI cwocking speed, wet=%d\n",
			wet);
		wetuwn -EINVAW;
	}

	wet = device_pwopewty_wead_u16(dev, "num-cs",
					&host->num_chipsewect);
	if (wet)
		host->num_chipsewect = DEFAUWT_NUM_CS;

	host->use_gpio_descwiptows = twue;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WOOP;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 32);
	host->bus_num = pdev->id;
	host->setup = hisi_spi_setup;
	host->cweanup = hisi_spi_cweanup;
	host->twansfew_one = hisi_spi_twansfew_one;
	host->handwe_eww = hisi_spi_handwe_eww;
	host->dev.fwnode = dev->fwnode;

	hisi_spi_hw_init(hs);

	wet = devm_wequest_iwq(dev, hs->iwq, hisi_spi_iwq, 0, dev_name(dev),
			       host);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get IWQ=%d, wet=%d\n", hs->iwq, wet);
		wetuwn wet;
	}

	wet = spi_wegistew_contwowwew(host);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew spi host, wet=%d\n", wet);
		wetuwn wet;
	}

	if (hisi_spi_debugfs_init(hs))
		dev_info(dev, "faiwed to cweate debugfs diw\n");

	dev_info(dev, "hw vewsion:0x%x max-fweq:%u kHz\n",
		weadw(hs->wegs + HISI_SPI_VEWSION),
		host->max_speed_hz / 1000);

	wetuwn 0;
}

static void hisi_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_spi *hs = spi_contwowwew_get_devdata(host);

	debugfs_wemove_wecuwsive(hs->debugfs);
	spi_unwegistew_contwowwew(host);
}

static const stwuct acpi_device_id hisi_spi_acpi_match[] = {
	{"HISI03E1", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_spi_acpi_match);

static stwuct pwatfowm_dwivew hisi_spi_dwivew = {
	.pwobe		= hisi_spi_pwobe,
	.wemove_new	= hisi_spi_wemove,
	.dwivew		= {
		.name	= "hisi-kunpeng-spi",
		.acpi_match_tabwe = hisi_spi_acpi_match,
	},
};
moduwe_pwatfowm_dwivew(hisi_spi_dwivew);

MODUWE_AUTHOW("Jay Fang <f.fangjian@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon SPI Contwowwew Dwivew fow Kunpeng SoCs");
MODUWE_WICENSE("GPW v2");
