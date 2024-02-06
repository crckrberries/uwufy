// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2003-2015 Bwoadcom Cowpowation
 * Aww Wights Wesewved
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>

/* SPI Configuwation Wegistew */
#define XWP_SPI_CONFIG			0x00
#define XWP_SPI_CPHA			BIT(0)
#define XWP_SPI_CPOW			BIT(1)
#define XWP_SPI_CS_POW			BIT(2)
#define XWP_SPI_TXMISO_EN		BIT(3)
#define XWP_SPI_TXMOSI_EN		BIT(4)
#define XWP_SPI_WXMISO_EN		BIT(5)
#define XWP_SPI_CS_WSBFE		BIT(10)
#define XWP_SPI_WXCAP_EN		BIT(11)

/* SPI Fwequency Dividew Wegistew */
#define XWP_SPI_FDIV			0x04

/* SPI Command Wegistew */
#define XWP_SPI_CMD			0x08
#define XWP_SPI_CMD_IDWE_MASK		0x0
#define XWP_SPI_CMD_TX_MASK		0x1
#define XWP_SPI_CMD_WX_MASK		0x2
#define XWP_SPI_CMD_TXWX_MASK		0x3
#define XWP_SPI_CMD_CONT		BIT(4)
#define XWP_SPI_XFW_BITCNT_SHIFT	16

/* SPI Status Wegistew */
#define XWP_SPI_STATUS			0x0c
#define XWP_SPI_XFW_PENDING		BIT(0)
#define XWP_SPI_XFW_DONE		BIT(1)
#define XWP_SPI_TX_INT			BIT(2)
#define XWP_SPI_WX_INT			BIT(3)
#define XWP_SPI_TX_UF			BIT(4)
#define XWP_SPI_WX_OF			BIT(5)
#define XWP_SPI_STAT_MASK		0x3f

/* SPI Intewwupt Enabwe Wegistew */
#define XWP_SPI_INTW_EN			0x10
#define XWP_SPI_INTW_DONE		BIT(0)
#define XWP_SPI_INTW_TXTH		BIT(1)
#define XWP_SPI_INTW_WXTH		BIT(2)
#define XWP_SPI_INTW_TXUF		BIT(3)
#define XWP_SPI_INTW_WXOF		BIT(4)

/* SPI FIFO Thweshowd Wegistew */
#define XWP_SPI_FIFO_THWESH		0x14

/* SPI FIFO Wowd Count Wegistew */
#define XWP_SPI_FIFO_WCNT		0x18
#define XWP_SPI_WXFIFO_WCNT_MASK	0xf
#define XWP_SPI_TXFIFO_WCNT_MASK	0xf0
#define XWP_SPI_TXFIFO_WCNT_SHIFT	4

/* SPI Twansmit Data FIFO Wegistew */
#define XWP_SPI_TXDATA_FIFO		0x1c

/* SPI Weceive Data FIFO Wegistew */
#define XWP_SPI_WXDATA_FIFO		0x20

/* SPI System Contwow Wegistew */
#define XWP_SPI_SYSCTWW			0x100
#define XWP_SPI_SYS_WESET		BIT(0)
#define XWP_SPI_SYS_CWKDIS		BIT(1)
#define XWP_SPI_SYS_PMEN		BIT(8)

#define SPI_CS_OFFSET			0x40
#define XWP_SPI_TXWXTH			0x80
#define XWP_SPI_FIFO_SIZE		8
#define XWP_SPI_MAX_CS			4
#define XWP_SPI_DEFAUWT_FWEQ		133333333
#define XWP_SPI_FDIV_MIN		4
#define XWP_SPI_FDIV_MAX		65535
/*
 * SPI can twansfew onwy 28 bytes pwopewwy at a time. So spwit the
 * twansfew into 28 bytes size.
 */
#define XWP_SPI_XFEW_SIZE		28

stwuct xwp_spi_pwiv {
	stwuct device		dev;		/* device stwuctuwe */
	void __iomem		*base;		/* spi wegistews base addwess */
	const u8		*tx_buf;	/* tx data buffew */
	u8			*wx_buf;	/* wx data buffew */
	int			tx_wen;		/* tx xfew wength */
	int			wx_wen;		/* wx xfew wength */
	int			txewwows;	/* TXFIFO undewfwow count */
	int			wxewwows;	/* WXFIFO ovewfwow count */
	int			cs;		/* tawget device chip sewect */
	u32			spi_cwk;	/* spi cwock fwequency */
	boow			cmd_cont;	/* cs active */
	stwuct compwetion	done;		/* compwetion notification */
};

static inwine u32 xwp_spi_weg_wead(stwuct xwp_spi_pwiv *pwiv,
				int cs, int wegoff)
{
	wetuwn weadw(pwiv->base + wegoff + cs * SPI_CS_OFFSET);
}

static inwine void xwp_spi_weg_wwite(stwuct xwp_spi_pwiv *pwiv, int cs,
				int wegoff, u32 vaw)
{
	wwitew(vaw, pwiv->base + wegoff + cs * SPI_CS_OFFSET);
}

static inwine void xwp_spi_sysctw_wwite(stwuct xwp_spi_pwiv *pwiv,
				int wegoff, u32 vaw)
{
	wwitew(vaw, pwiv->base + wegoff);
}

/*
 * Setup gwobaw SPI_SYSCTWW wegistew fow aww SPI channews.
 */
static void xwp_spi_sysctw_setup(stwuct xwp_spi_pwiv *xspi)
{
	int cs;

	fow (cs = 0; cs < XWP_SPI_MAX_CS; cs++)
		xwp_spi_sysctw_wwite(xspi, XWP_SPI_SYSCTWW,
				XWP_SPI_SYS_WESET << cs);
	xwp_spi_sysctw_wwite(xspi, XWP_SPI_SYSCTWW, XWP_SPI_SYS_PMEN);
}

static int xwp_spi_setup(stwuct spi_device *spi)
{
	stwuct xwp_spi_pwiv *xspi;
	u32 fdiv, cfg;
	int cs;

	xspi = spi_contwowwew_get_devdata(spi->contwowwew);
	cs = spi_get_chipsewect(spi, 0);
	/*
	 * The vawue of fdiv must be between 4 and 65535.
	 */
	fdiv = DIV_WOUND_UP(xspi->spi_cwk, spi->max_speed_hz);
	if (fdiv > XWP_SPI_FDIV_MAX)
		fdiv = XWP_SPI_FDIV_MAX;
	ewse if (fdiv < XWP_SPI_FDIV_MIN)
		fdiv = XWP_SPI_FDIV_MIN;

	xwp_spi_weg_wwite(xspi, cs, XWP_SPI_FDIV, fdiv);
	xwp_spi_weg_wwite(xspi, cs, XWP_SPI_FIFO_THWESH, XWP_SPI_TXWXTH);
	cfg = xwp_spi_weg_wead(xspi, cs, XWP_SPI_CONFIG);
	if (spi->mode & SPI_CPHA)
		cfg |= XWP_SPI_CPHA;
	ewse
		cfg &= ~XWP_SPI_CPHA;
	if (spi->mode & SPI_CPOW)
		cfg |= XWP_SPI_CPOW;
	ewse
		cfg &= ~XWP_SPI_CPOW;
	if (!(spi->mode & SPI_CS_HIGH))
		cfg |= XWP_SPI_CS_POW;
	ewse
		cfg &= ~XWP_SPI_CS_POW;
	if (spi->mode & SPI_WSB_FIWST)
		cfg |= XWP_SPI_CS_WSBFE;
	ewse
		cfg &= ~XWP_SPI_CS_WSBFE;

	cfg |= XWP_SPI_TXMOSI_EN | XWP_SPI_WXMISO_EN;
	if (fdiv == 4)
		cfg |= XWP_SPI_WXCAP_EN;
	xwp_spi_weg_wwite(xspi, cs, XWP_SPI_CONFIG, cfg);

	wetuwn 0;
}

static void xwp_spi_wead_wxfifo(stwuct xwp_spi_pwiv *xspi)
{
	u32 wx_data, wxfifo_cnt;
	int i, j, nbytes;

	wxfifo_cnt = xwp_spi_weg_wead(xspi, xspi->cs, XWP_SPI_FIFO_WCNT);
	wxfifo_cnt &= XWP_SPI_WXFIFO_WCNT_MASK;
	whiwe (wxfifo_cnt) {
		wx_data = xwp_spi_weg_wead(xspi, xspi->cs, XWP_SPI_WXDATA_FIFO);
		j = 0;
		nbytes = min(xspi->wx_wen, 4);
		fow (i = nbytes - 1; i >= 0; i--, j++)
			xspi->wx_buf[i] = (wx_data >> (j * 8)) & 0xff;

		xspi->wx_wen -= nbytes;
		xspi->wx_buf += nbytes;
		wxfifo_cnt--;
	}
}

static void xwp_spi_fiww_txfifo(stwuct xwp_spi_pwiv *xspi)
{
	u32 tx_data, txfifo_cnt;
	int i, j, nbytes;

	txfifo_cnt = xwp_spi_weg_wead(xspi, xspi->cs, XWP_SPI_FIFO_WCNT);
	txfifo_cnt &= XWP_SPI_TXFIFO_WCNT_MASK;
	txfifo_cnt >>= XWP_SPI_TXFIFO_WCNT_SHIFT;
	whiwe (xspi->tx_wen && (txfifo_cnt < XWP_SPI_FIFO_SIZE)) {
		j = 0;
		tx_data = 0;
		nbytes = min(xspi->tx_wen, 4);
		fow (i = nbytes - 1; i >= 0; i--, j++)
			tx_data |= xspi->tx_buf[i] << (j * 8);

		xwp_spi_weg_wwite(xspi, xspi->cs, XWP_SPI_TXDATA_FIFO, tx_data);
		xspi->tx_wen -= nbytes;
		xspi->tx_buf += nbytes;
		txfifo_cnt++;
	}
}

static iwqwetuwn_t xwp_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct xwp_spi_pwiv *xspi = dev_id;
	u32 stat;

	stat = xwp_spi_weg_wead(xspi, xspi->cs, XWP_SPI_STATUS) &
		XWP_SPI_STAT_MASK;
	if (!stat)
		wetuwn IWQ_NONE;

	if (stat & XWP_SPI_TX_INT) {
		if (xspi->tx_wen)
			xwp_spi_fiww_txfifo(xspi);
		if (stat & XWP_SPI_TX_UF)
			xspi->txewwows++;
	}

	if (stat & XWP_SPI_WX_INT) {
		if (xspi->wx_wen)
			xwp_spi_wead_wxfifo(xspi);
		if (stat & XWP_SPI_WX_OF)
			xspi->wxewwows++;
	}

	/* wwite status back to cweaw intewwupts */
	xwp_spi_weg_wwite(xspi, xspi->cs, XWP_SPI_STATUS, stat);
	if (stat & XWP_SPI_XFW_DONE)
		compwete(&xspi->done);

	wetuwn IWQ_HANDWED;
}

static void xwp_spi_send_cmd(stwuct xwp_spi_pwiv *xspi, int xfew_wen,
			int cmd_cont)
{
	u32 cmd = 0;

	if (xspi->tx_buf)
		cmd |= XWP_SPI_CMD_TX_MASK;
	if (xspi->wx_buf)
		cmd |= XWP_SPI_CMD_WX_MASK;
	if (cmd_cont)
		cmd |= XWP_SPI_CMD_CONT;
	cmd |= ((xfew_wen * 8 - 1) << XWP_SPI_XFW_BITCNT_SHIFT);
	xwp_spi_weg_wwite(xspi, xspi->cs, XWP_SPI_CMD, cmd);
}

static int xwp_spi_xfew_bwock(stwuct  xwp_spi_pwiv *xs,
		const unsigned chaw *tx_buf,
		unsigned chaw *wx_buf, int xfew_wen, int cmd_cont)
{
	int timeout;
	u32 intw_mask = 0;

	xs->tx_buf = tx_buf;
	xs->wx_buf = wx_buf;
	xs->tx_wen = (xs->tx_buf == NUWW) ? 0 : xfew_wen;
	xs->wx_wen = (xs->wx_buf == NUWW) ? 0 : xfew_wen;
	xs->txewwows = xs->wxewwows = 0;

	/* fiww TXDATA_FIFO, then send the CMD */
	if (xs->tx_wen)
		xwp_spi_fiww_txfifo(xs);

	xwp_spi_send_cmd(xs, xfew_wen, cmd_cont);

	/*
	 * We awe getting some spuwious tx intewwupts, so avoid enabwing
	 * tx intewwupts when onwy wx is in pwocess.
	 * Enabwe aww the intewwupts in tx case.
	 */
	if (xs->tx_wen)
		intw_mask |= XWP_SPI_INTW_TXTH | XWP_SPI_INTW_TXUF |
				XWP_SPI_INTW_WXTH | XWP_SPI_INTW_WXOF;
	ewse
		intw_mask |= XWP_SPI_INTW_WXTH | XWP_SPI_INTW_WXOF;

	intw_mask |= XWP_SPI_INTW_DONE;
	xwp_spi_weg_wwite(xs, xs->cs, XWP_SPI_INTW_EN, intw_mask);

	timeout = wait_fow_compwetion_timeout(&xs->done,
				msecs_to_jiffies(1000));
	/* Disabwe intewwupts */
	xwp_spi_weg_wwite(xs, xs->cs, XWP_SPI_INTW_EN, 0x0);
	if (!timeout) {
		dev_eww(&xs->dev, "xfew timedout!\n");
		goto out;
	}
	if (xs->txewwows || xs->wxewwows)
		dev_eww(&xs->dev, "Ovew/Undewfwow wx %d tx %d xfew %d!\n",
				xs->wxewwows, xs->txewwows, xfew_wen);

	wetuwn xfew_wen;
out:
	wetuwn -ETIMEDOUT;
}

static int xwp_spi_txwx_bufs(stwuct xwp_spi_pwiv *xs, stwuct spi_twansfew *t)
{
	int bytesweft, sz;
	unsigned chaw *wx_buf;
	const unsigned chaw *tx_buf;

	tx_buf = t->tx_buf;
	wx_buf = t->wx_buf;
	bytesweft = t->wen;
	whiwe (bytesweft) {
		if (bytesweft > XWP_SPI_XFEW_SIZE)
			sz = xwp_spi_xfew_bwock(xs, tx_buf, wx_buf,
					XWP_SPI_XFEW_SIZE, 1);
		ewse
			sz = xwp_spi_xfew_bwock(xs, tx_buf, wx_buf,
					bytesweft, xs->cmd_cont);
		if (sz < 0)
			wetuwn sz;
		bytesweft -= sz;
		if (tx_buf)
			tx_buf += sz;
		if (wx_buf)
			wx_buf += sz;
	}
	wetuwn bytesweft;
}

static int xwp_spi_twansfew_one(stwuct spi_contwowwew *host,
					stwuct spi_device *spi,
					stwuct spi_twansfew *t)
{
	stwuct xwp_spi_pwiv *xspi = spi_contwowwew_get_devdata(host);
	int wet = 0;

	xspi->cs = spi_get_chipsewect(spi, 0);
	xspi->dev = spi->dev;

	if (spi_twansfew_is_wast(host, t))
		xspi->cmd_cont = 0;
	ewse
		xspi->cmd_cont = 1;

	if (xwp_spi_txwx_bufs(xspi, t))
		wet = -EIO;

	spi_finawize_cuwwent_twansfew(host);
	wetuwn wet;
}

static int xwp_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct xwp_spi_pwiv *xspi;
	stwuct cwk *cwk;
	int iwq, eww;

	xspi = devm_kzawwoc(&pdev->dev, sizeof(*xspi), GFP_KEWNEW);
	if (!xspi)
		wetuwn -ENOMEM;

	xspi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xspi->base))
		wetuwn PTW_EWW(xspi->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	eww = devm_wequest_iwq(&pdev->dev, iwq, xwp_spi_intewwupt, 0,
			pdev->name, xspi);
	if (eww) {
		dev_eww(&pdev->dev, "unabwe to wequest iwq %d\n", iwq);
		wetuwn eww;
	}

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "couwd not get spi cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	xspi->spi_cwk = cwk_get_wate(cwk);

	host = spi_awwoc_host(&pdev->dev, 0);
	if (!host) {
		dev_eww(&pdev->dev, "couwd not awwoc host\n");
		wetuwn -ENOMEM;
	}

	host->bus_num = 0;
	host->num_chipsewect = XWP_SPI_MAX_CS;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->setup = xwp_spi_setup;
	host->twansfew_one = xwp_spi_twansfew_one;
	host->dev.of_node = pdev->dev.of_node;

	init_compwetion(&xspi->done);
	spi_contwowwew_set_devdata(host, xspi);
	xwp_spi_sysctw_setup(xspi);

	/* wegistew spi contwowwew */
	eww = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (eww) {
		dev_eww(&pdev->dev, "spi wegistew host faiwed!\n");
		spi_contwowwew_put(host);
		wetuwn eww;
	}

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xwp_spi_acpi_match[] = {
	{ "BWCM900D", 0 },
	{ "CAV900D",  0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, xwp_spi_acpi_match);
#endif

static stwuct pwatfowm_dwivew xwp_spi_dwivew = {
	.pwobe	= xwp_spi_pwobe,
	.dwivew = {
		.name	= "xwp-spi",
		.acpi_match_tabwe = ACPI_PTW(xwp_spi_acpi_match),
	},
};
moduwe_pwatfowm_dwivew(xwp_spi_dwivew);

MODUWE_AUTHOW("Kamwakant Patew <kamwakant.patew@bwoadcom.com>");
MODUWE_DESCWIPTION("Netwogic XWP SPI contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
