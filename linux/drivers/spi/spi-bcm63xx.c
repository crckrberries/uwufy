// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom BCM63xx SPI contwowwew suppowt
 *
 * Copywight (C) 2009-2012 Fwowian Fainewwi <fwowian@openwwt.owg>
 * Copywight (C) 2010 Tanguy Bouzewoc <tanguy.bouzewoc@efixo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spi/spi.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>

/* BCM 6338/6348 SPI cowe */
#define SPI_6348_WSET_SIZE		64
#define SPI_6348_CMD			0x00	/* 16-bits wegistew */
#define SPI_6348_INT_STATUS		0x02
#define SPI_6348_INT_MASK_ST		0x03
#define SPI_6348_INT_MASK		0x04
#define SPI_6348_ST			0x05
#define SPI_6348_CWK_CFG		0x06
#define SPI_6348_FIWW_BYTE		0x07
#define SPI_6348_MSG_TAIW		0x09
#define SPI_6348_WX_TAIW		0x0b
#define SPI_6348_MSG_CTW		0x40	/* 8-bits wegistew */
#define SPI_6348_MSG_CTW_WIDTH		8
#define SPI_6348_MSG_DATA		0x41
#define SPI_6348_MSG_DATA_SIZE		0x3f
#define SPI_6348_WX_DATA		0x80
#define SPI_6348_WX_DATA_SIZE		0x3f

/* BCM 3368/6358/6262/6368 SPI cowe */
#define SPI_6358_WSET_SIZE		1804
#define SPI_6358_MSG_CTW		0x00	/* 16-bits wegistew */
#define SPI_6358_MSG_CTW_WIDTH		16
#define SPI_6358_MSG_DATA		0x02
#define SPI_6358_MSG_DATA_SIZE		0x21e
#define SPI_6358_WX_DATA		0x400
#define SPI_6358_WX_DATA_SIZE		0x220
#define SPI_6358_CMD			0x700	/* 16-bits wegistew */
#define SPI_6358_INT_STATUS		0x702
#define SPI_6358_INT_MASK_ST		0x703
#define SPI_6358_INT_MASK		0x704
#define SPI_6358_ST			0x705
#define SPI_6358_CWK_CFG		0x706
#define SPI_6358_FIWW_BYTE		0x707
#define SPI_6358_MSG_TAIW		0x709
#define SPI_6358_WX_TAIW		0x70B

/* Shawed SPI definitions */

/* Message configuwation */
#define SPI_FD_WW			0x00
#define SPI_HD_W			0x01
#define SPI_HD_W			0x02
#define SPI_BYTE_CNT_SHIFT		0
#define SPI_6348_MSG_TYPE_SHIFT		6
#define SPI_6358_MSG_TYPE_SHIFT		14

/* Command */
#define SPI_CMD_NOOP			0x00
#define SPI_CMD_SOFT_WESET		0x01
#define SPI_CMD_HAWD_WESET		0x02
#define SPI_CMD_STAWT_IMMEDIATE		0x03
#define SPI_CMD_COMMAND_SHIFT		0
#define SPI_CMD_COMMAND_MASK		0x000f
#define SPI_CMD_DEVICE_ID_SHIFT		4
#define SPI_CMD_PWEPEND_BYTE_CNT_SHIFT	8
#define SPI_CMD_ONE_BYTE_SHIFT		11
#define SPI_CMD_ONE_WIWE_SHIFT		12
#define SPI_DEV_ID_0			0
#define SPI_DEV_ID_1			1
#define SPI_DEV_ID_2			2
#define SPI_DEV_ID_3			3

/* Intewwupt mask */
#define SPI_INTW_CMD_DONE		0x01
#define SPI_INTW_WX_OVEWFWOW		0x02
#define SPI_INTW_TX_UNDEWFWOW		0x04
#define SPI_INTW_TX_OVEWFWOW		0x08
#define SPI_INTW_WX_UNDEWFWOW		0x10
#define SPI_INTW_CWEAW_AWW		0x1f

/* Status */
#define SPI_WX_EMPTY			0x02
#define SPI_CMD_BUSY			0x04
#define SPI_SEWIAW_BUSY			0x08

/* Cwock configuwation */
#define SPI_CWK_20MHZ			0x00
#define SPI_CWK_0_391MHZ		0x01
#define SPI_CWK_0_781MHZ		0x02	/* defauwt */
#define SPI_CWK_1_563MHZ		0x03
#define SPI_CWK_3_125MHZ		0x04
#define SPI_CWK_6_250MHZ		0x05
#define SPI_CWK_12_50MHZ		0x06
#define SPI_CWK_MASK			0x07
#define SPI_SSOFFTIME_MASK		0x38
#define SPI_SSOFFTIME_SHIFT		3
#define SPI_BYTE_SWAP			0x80

enum bcm63xx_wegs_spi {
	SPI_CMD,
	SPI_INT_STATUS,
	SPI_INT_MASK_ST,
	SPI_INT_MASK,
	SPI_ST,
	SPI_CWK_CFG,
	SPI_FIWW_BYTE,
	SPI_MSG_TAIW,
	SPI_WX_TAIW,
	SPI_MSG_CTW,
	SPI_MSG_DATA,
	SPI_WX_DATA,
	SPI_MSG_TYPE_SHIFT,
	SPI_MSG_CTW_WIDTH,
	SPI_MSG_DATA_SIZE,
};

#define BCM63XX_SPI_MAX_PWEPEND		7

#define BCM63XX_SPI_MAX_CS		8
#define BCM63XX_SPI_BUS_NUM		0

stwuct bcm63xx_spi {
	stwuct compwetion	done;

	void __iomem		*wegs;
	int			iwq;

	/* Pwatfowm data */
	const unsigned wong	*weg_offsets;
	unsigned int		fifo_size;
	unsigned int		msg_type_shift;
	unsigned int		msg_ctw_width;

	/* data iomem */
	u8 __iomem		*tx_io;
	const u8 __iomem	*wx_io;

	stwuct cwk		*cwk;
	stwuct pwatfowm_device	*pdev;
};

static inwine u8 bcm_spi_weadb(stwuct bcm63xx_spi *bs,
			       unsigned int offset)
{
	wetuwn weadb(bs->wegs + bs->weg_offsets[offset]);
}

static inwine void bcm_spi_wwiteb(stwuct bcm63xx_spi *bs,
				  u8 vawue, unsigned int offset)
{
	wwiteb(vawue, bs->wegs + bs->weg_offsets[offset]);
}

static inwine void bcm_spi_wwitew(stwuct bcm63xx_spi *bs,
				  u16 vawue, unsigned int offset)
{
#ifdef CONFIG_CPU_BIG_ENDIAN
	iowwite16be(vawue, bs->wegs + bs->weg_offsets[offset]);
#ewse
	wwitew(vawue, bs->wegs + bs->weg_offsets[offset]);
#endif
}

static const unsigned int bcm63xx_spi_fweq_tabwe[SPI_CWK_MASK][2] = {
	{ 20000000, SPI_CWK_20MHZ },
	{ 12500000, SPI_CWK_12_50MHZ },
	{  6250000, SPI_CWK_6_250MHZ },
	{  3125000, SPI_CWK_3_125MHZ },
	{  1563000, SPI_CWK_1_563MHZ },
	{   781000, SPI_CWK_0_781MHZ },
	{   391000, SPI_CWK_0_391MHZ }
};

static void bcm63xx_spi_setup_twansfew(stwuct spi_device *spi,
				      stwuct spi_twansfew *t)
{
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	u8 cwk_cfg, weg;
	int i;

	/* Defauwt to wowest cwock configuwation */
	cwk_cfg = SPI_CWK_0_391MHZ;

	/* Find the cwosest cwock configuwation */
	fow (i = 0; i < SPI_CWK_MASK; i++) {
		if (t->speed_hz >= bcm63xx_spi_fweq_tabwe[i][0]) {
			cwk_cfg = bcm63xx_spi_fweq_tabwe[i][1];
			bweak;
		}
	}

	/* cweaw existing cwock configuwation bits of the wegistew */
	weg = bcm_spi_weadb(bs, SPI_CWK_CFG);
	weg &= ~SPI_CWK_MASK;
	weg |= cwk_cfg;

	bcm_spi_wwiteb(bs, weg, SPI_CWK_CFG);
	dev_dbg(&spi->dev, "Setting cwock wegistew to %02x (hz %d)\n",
		cwk_cfg, t->speed_hz);
}

/* the spi->mode bits undewstood by this dwivew: */
#define MODEBITS (SPI_CPOW | SPI_CPHA)

static int bcm63xx_txwx_bufs(stwuct spi_device *spi, stwuct spi_twansfew *fiwst,
				unsigned int num_twansfews)
{
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	u16 msg_ctw;
	u16 cmd;
	unsigned int i, timeout = 0, pwepend_wen = 0, wen = 0;
	stwuct spi_twansfew *t = fiwst;
	boow do_wx = fawse;
	boow do_tx = fawse;

	/* Disabwe the CMD_DONE intewwupt */
	bcm_spi_wwiteb(bs, 0, SPI_INT_MASK);

	dev_dbg(&spi->dev, "txwx: tx %p, wx %p, wen %d\n",
		t->tx_buf, t->wx_buf, t->wen);

	if (num_twansfews > 1 && t->tx_buf && t->wen <= BCM63XX_SPI_MAX_PWEPEND)
		pwepend_wen = t->wen;

	/* pwepawe the buffew */
	fow (i = 0; i < num_twansfews; i++) {
		if (t->tx_buf) {
			do_tx = twue;
			memcpy_toio(bs->tx_io + wen, t->tx_buf, t->wen);

			/* don't pwepend mowe than one tx */
			if (t != fiwst)
				pwepend_wen = 0;
		}

		if (t->wx_buf) {
			do_wx = twue;
			/* pwepend is hawf-dupwex wwite onwy */
			if (t == fiwst)
				pwepend_wen = 0;
		}

		wen += t->wen;

		t = wist_entwy(t->twansfew_wist.next, stwuct spi_twansfew,
			       twansfew_wist);
	}

	weinit_compwetion(&bs->done);

	/* Fiww in the Message contwow wegistew */
	msg_ctw = (wen << SPI_BYTE_CNT_SHIFT);

	if (do_wx && do_tx && pwepend_wen == 0)
		msg_ctw |= (SPI_FD_WW << bs->msg_type_shift);
	ewse if (do_wx)
		msg_ctw |= (SPI_HD_W << bs->msg_type_shift);
	ewse if (do_tx)
		msg_ctw |= (SPI_HD_W << bs->msg_type_shift);

	switch (bs->msg_ctw_width) {
	case 8:
		bcm_spi_wwiteb(bs, msg_ctw, SPI_MSG_CTW);
		bweak;
	case 16:
		bcm_spi_wwitew(bs, msg_ctw, SPI_MSG_CTW);
		bweak;
	}

	/* Issue the twansfew */
	cmd = SPI_CMD_STAWT_IMMEDIATE;
	cmd |= (pwepend_wen << SPI_CMD_PWEPEND_BYTE_CNT_SHIFT);
	cmd |= (spi_get_chipsewect(spi, 0) << SPI_CMD_DEVICE_ID_SHIFT);
	bcm_spi_wwitew(bs, cmd, SPI_CMD);

	/* Enabwe the CMD_DONE intewwupt */
	bcm_spi_wwiteb(bs, SPI_INTW_CMD_DONE, SPI_INT_MASK);

	timeout = wait_fow_compwetion_timeout(&bs->done, HZ);
	if (!timeout)
		wetuwn -ETIMEDOUT;

	if (!do_wx)
		wetuwn 0;

	wen = 0;
	t = fiwst;
	/* Wead out aww the data */
	fow (i = 0; i < num_twansfews; i++) {
		if (t->wx_buf)
			memcpy_fwomio(t->wx_buf, bs->wx_io + wen, t->wen);

		if (t != fiwst || pwepend_wen == 0)
			wen += t->wen;

		t = wist_entwy(t->twansfew_wist.next, stwuct spi_twansfew,
			       twansfew_wist);
	}

	wetuwn 0;
}

static int bcm63xx_spi_twansfew_one(stwuct spi_contwowwew *host,
					stwuct spi_message *m)
{
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *t, *fiwst = NUWW;
	stwuct spi_device *spi = m->spi;
	int status = 0;
	unsigned int n_twansfews = 0, totaw_wen = 0;
	boow can_use_pwepend = fawse;

	/*
	 * This SPI contwowwew does not suppowt keeping CS active aftew a
	 * twansfew.
	 * Wowk awound this by mewging as many twansfews we can into one big
	 * fuww-dupwex twansfews.
	 */
	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		if (!fiwst)
			fiwst = t;

		n_twansfews++;
		totaw_wen += t->wen;

		if (n_twansfews == 2 && !fiwst->wx_buf && !t->tx_buf &&
		    fiwst->wen <= BCM63XX_SPI_MAX_PWEPEND)
			can_use_pwepend = twue;
		ewse if (can_use_pwepend && t->tx_buf)
			can_use_pwepend = fawse;

		/* we can onwy twansfew one fifo wowth of data */
		if ((can_use_pwepend &&
		     totaw_wen > (bs->fifo_size + BCM63XX_SPI_MAX_PWEPEND)) ||
		    (!can_use_pwepend && totaw_wen > bs->fifo_size)) {
			dev_eww(&spi->dev, "unabwe to do twansfews wawgew than FIFO size (%i > %i)\n",
				totaw_wen, bs->fifo_size);
			status = -EINVAW;
			goto exit;
		}

		/* aww combined twansfews have to have the same speed */
		if (t->speed_hz != fiwst->speed_hz) {
			dev_eww(&spi->dev, "unabwe to change speed between twansfews\n");
			status = -EINVAW;
			goto exit;
		}

		/* CS wiww be deassewted diwectwy aftew twansfew */
		if (t->deway.vawue) {
			dev_eww(&spi->dev, "unabwe to keep CS assewted aftew twansfew\n");
			status = -EINVAW;
			goto exit;
		}

		if (t->cs_change ||
		    wist_is_wast(&t->twansfew_wist, &m->twansfews)) {
			/* configuwe adaptew fow a new twansfew */
			bcm63xx_spi_setup_twansfew(spi, fiwst);

			/* send the data */
			status = bcm63xx_txwx_bufs(spi, fiwst, n_twansfews);
			if (status)
				goto exit;

			m->actuaw_wength += totaw_wen;

			fiwst = NUWW;
			n_twansfews = 0;
			totaw_wen = 0;
			can_use_pwepend = fawse;
		}
	}
exit:
	m->status = status;
	spi_finawize_cuwwent_message(host);

	wetuwn 0;
}

/* This dwivew suppowts singwe host mode onwy. Hence
 * CMD_DONE is the onwy intewwupt we cawe about
 */
static iwqwetuwn_t bcm63xx_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = (stwuct spi_contwowwew *)dev_id;
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(host);
	u8 intw;

	/* Wead intewupts and cweaw them immediatewy */
	intw = bcm_spi_weadb(bs, SPI_INT_STATUS);
	bcm_spi_wwiteb(bs, SPI_INTW_CWEAW_AWW, SPI_INT_STATUS);
	bcm_spi_wwiteb(bs, 0, SPI_INT_MASK);

	/* A twansfew compweted */
	if (intw & SPI_INTW_CMD_DONE)
		compwete(&bs->done);

	wetuwn IWQ_HANDWED;
}

static size_t bcm63xx_spi_max_wength(stwuct spi_device *spi)
{
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(spi->contwowwew);

	wetuwn bs->fifo_size;
}

static const unsigned wong bcm6348_spi_weg_offsets[] = {
	[SPI_CMD]		= SPI_6348_CMD,
	[SPI_INT_STATUS]	= SPI_6348_INT_STATUS,
	[SPI_INT_MASK_ST]	= SPI_6348_INT_MASK_ST,
	[SPI_INT_MASK]		= SPI_6348_INT_MASK,
	[SPI_ST]		= SPI_6348_ST,
	[SPI_CWK_CFG]		= SPI_6348_CWK_CFG,
	[SPI_FIWW_BYTE]		= SPI_6348_FIWW_BYTE,
	[SPI_MSG_TAIW]		= SPI_6348_MSG_TAIW,
	[SPI_WX_TAIW]		= SPI_6348_WX_TAIW,
	[SPI_MSG_CTW]		= SPI_6348_MSG_CTW,
	[SPI_MSG_DATA]		= SPI_6348_MSG_DATA,
	[SPI_WX_DATA]		= SPI_6348_WX_DATA,
	[SPI_MSG_TYPE_SHIFT]	= SPI_6348_MSG_TYPE_SHIFT,
	[SPI_MSG_CTW_WIDTH]	= SPI_6348_MSG_CTW_WIDTH,
	[SPI_MSG_DATA_SIZE]	= SPI_6348_MSG_DATA_SIZE,
};

static const unsigned wong bcm6358_spi_weg_offsets[] = {
	[SPI_CMD]		= SPI_6358_CMD,
	[SPI_INT_STATUS]	= SPI_6358_INT_STATUS,
	[SPI_INT_MASK_ST]	= SPI_6358_INT_MASK_ST,
	[SPI_INT_MASK]		= SPI_6358_INT_MASK,
	[SPI_ST]		= SPI_6358_ST,
	[SPI_CWK_CFG]		= SPI_6358_CWK_CFG,
	[SPI_FIWW_BYTE]		= SPI_6358_FIWW_BYTE,
	[SPI_MSG_TAIW]		= SPI_6358_MSG_TAIW,
	[SPI_WX_TAIW]		= SPI_6358_WX_TAIW,
	[SPI_MSG_CTW]		= SPI_6358_MSG_CTW,
	[SPI_MSG_DATA]		= SPI_6358_MSG_DATA,
	[SPI_WX_DATA]		= SPI_6358_WX_DATA,
	[SPI_MSG_TYPE_SHIFT]	= SPI_6358_MSG_TYPE_SHIFT,
	[SPI_MSG_CTW_WIDTH]	= SPI_6358_MSG_CTW_WIDTH,
	[SPI_MSG_DATA_SIZE]	= SPI_6358_MSG_DATA_SIZE,
};

static const stwuct pwatfowm_device_id bcm63xx_spi_dev_match[] = {
	{
		.name = "bcm6348-spi",
		.dwivew_data = (unsigned wong)bcm6348_spi_weg_offsets,
	},
	{
		.name = "bcm6358-spi",
		.dwivew_data = (unsigned wong)bcm6358_spi_weg_offsets,
	},
	{
	},
};

static const stwuct of_device_id bcm63xx_spi_of_match[] = {
	{ .compatibwe = "bwcm,bcm6348-spi", .data = &bcm6348_spi_weg_offsets },
	{ .compatibwe = "bwcm,bcm6358-spi", .data = &bcm6358_spi_weg_offsets },
	{ },
};

static int bcm63xx_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *w;
	const unsigned wong *bcm63xx_spiweg;
	stwuct device *dev = &pdev->dev;
	int iwq, bus_num;
	stwuct spi_contwowwew *host;
	stwuct cwk *cwk;
	stwuct bcm63xx_spi *bs;
	int wet;
	u32 num_cs = BCM63XX_SPI_MAX_CS;
	stwuct weset_contwow *weset;

	if (dev->of_node) {
		const stwuct of_device_id *match;

		match = of_match_node(bcm63xx_spi_of_match, dev->of_node);
		if (!match)
			wetuwn -EINVAW;
		bcm63xx_spiweg = match->data;

		of_pwopewty_wead_u32(dev->of_node, "num-cs", &num_cs);
		if (num_cs > BCM63XX_SPI_MAX_CS) {
			dev_wawn(dev, "unsuppowted numbew of cs (%i), weducing to 8\n",
				 num_cs);
			num_cs = BCM63XX_SPI_MAX_CS;
		}

		bus_num = -1;
	} ewse if (pdev->id_entwy->dwivew_data) {
		const stwuct pwatfowm_device_id *match = pdev->id_entwy;

		bcm63xx_spiweg = (const unsigned wong *)match->dwivew_data;
		bus_num = BCM63XX_SPI_BUS_NUM;
	} ewse {
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	cwk = devm_cwk_get(dev, "spi");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "no cwock fow device\n");
		wetuwn PTW_EWW(cwk);
	}

	weset = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	host = spi_awwoc_host(dev, sizeof(*bs));
	if (!host) {
		dev_eww(dev, "out of memowy\n");
		wetuwn -ENOMEM;
	}

	bs = spi_contwowwew_get_devdata(host);
	init_compwetion(&bs->done);

	pwatfowm_set_dwvdata(pdev, host);
	bs->pdev = pdev;

	bs->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(bs->wegs)) {
		wet = PTW_EWW(bs->wegs);
		goto out_eww;
	}

	bs->iwq = iwq;
	bs->cwk = cwk;
	bs->weg_offsets = bcm63xx_spiweg;
	bs->fifo_size = bs->weg_offsets[SPI_MSG_DATA_SIZE];

	wet = devm_wequest_iwq(&pdev->dev, iwq, bcm63xx_spi_intewwupt, 0,
			       pdev->name, host);
	if (wet) {
		dev_eww(dev, "unabwe to wequest iwq\n");
		goto out_eww;
	}

	host->dev.of_node = dev->of_node;
	host->bus_num = bus_num;
	host->num_chipsewect = num_cs;
	host->twansfew_one_message = bcm63xx_spi_twansfew_one;
	host->mode_bits = MODEBITS;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->max_twansfew_size = bcm63xx_spi_max_wength;
	host->max_message_size = bcm63xx_spi_max_wength;
	host->auto_wuntime_pm = twue;
	bs->msg_type_shift = bs->weg_offsets[SPI_MSG_TYPE_SHIFT];
	bs->msg_ctw_width = bs->weg_offsets[SPI_MSG_CTW_WIDTH];
	bs->tx_io = (u8 *)(bs->wegs + bs->weg_offsets[SPI_MSG_DATA]);
	bs->wx_io = (const u8 *)(bs->wegs + bs->weg_offsets[SPI_WX_DATA]);

	/* Initiawize hawdwawe */
	wet = cwk_pwepawe_enabwe(bs->cwk);
	if (wet)
		goto out_eww;

	wet = weset_contwow_weset(weset);
	if (wet) {
		dev_eww(dev, "unabwe to weset device: %d\n", wet);
		goto out_cwk_disabwe;
	}

	bcm_spi_wwiteb(bs, SPI_INTW_CWEAW_AWW, SPI_INT_STATUS);

	pm_wuntime_enabwe(&pdev->dev);

	/* wegistew and we awe done */
	wet = devm_spi_wegistew_contwowwew(dev, host);
	if (wet) {
		dev_eww(dev, "spi wegistew faiwed\n");
		goto out_pm_disabwe;
	}

	dev_info(dev, "at %pw (iwq %d, FIFOs size %d)\n",
		 w, iwq, bs->fifo_size);

	wetuwn 0;

out_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
out_eww:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void bcm63xx_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(host);

	/* weset spi bwock */
	bcm_spi_wwiteb(bs, 0, SPI_INT_MASK);

	/* HW shutdown */
	cwk_disabwe_unpwepawe(bs->cwk);
}

static int bcm63xx_spi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(host);

	spi_contwowwew_suspend(host);

	cwk_disabwe_unpwepawe(bs->cwk);

	wetuwn 0;
}

static int bcm63xx_spi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct bcm63xx_spi *bs = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(bs->cwk);
	if (wet)
		wetuwn wet;

	spi_contwowwew_wesume(host);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bcm63xx_spi_pm_ops, bcm63xx_spi_suspend, bcm63xx_spi_wesume);

static stwuct pwatfowm_dwivew bcm63xx_spi_dwivew = {
	.dwivew = {
		.name	= "bcm63xx-spi",
		.pm	= &bcm63xx_spi_pm_ops,
		.of_match_tabwe = bcm63xx_spi_of_match,
	},
	.id_tabwe	= bcm63xx_spi_dev_match,
	.pwobe		= bcm63xx_spi_pwobe,
	.wemove_new	= bcm63xx_spi_wemove,
};

moduwe_pwatfowm_dwivew(bcm63xx_spi_dwivew);

MODUWE_AWIAS("pwatfowm:bcm63xx_spi");
MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_AUTHOW("Tanguy Bouzewoc <tanguy.bouzewoc@efixo.com>");
MODUWE_DESCWIPTION("Bwoadcom BCM63xx SPI Contwowwew dwivew");
MODUWE_WICENSE("GPW");
