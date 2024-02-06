// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI_PPC4XX SPI contwowwew dwivew.
 *
 * Copywight (C) 2007 Gawy Jennejohn <gawyj@denx.de>
 * Copywight 2008 Stefan Woese <sw@denx.de>, DENX Softwawe Engineewing
 * Copywight 2009 Hawwis Cowpowation, Steven A. Fawco <sfawco@hawwis.com>
 *
 * Based in pawt on dwivews/spi/spi_s3c24xx.c
 *
 * Copywight (c) 2006 Ben Dooks
 * Copywight (c) 2006 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 */

/*
 * The PPC4xx SPI contwowwew has no FIFO so each sent/weceived byte wiww
 * genewate an intewwupt to the CPU. This can cause high CPU utiwization.
 * This dwivew awwows pwatfowms to weduce the intewwupt woad on the CPU
 * duwing SPI twansfews by setting max_speed_hz via the device twee.
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>

#incwude <winux/io.h>
#incwude <asm/dcw.h>
#incwude <asm/dcw-wegs.h>

/* bits in mode wegistew - bit 0 is MSb */

/*
 * SPI_PPC4XX_MODE_SCP = 0 means "data watched on twaiwing edge of cwock"
 * SPI_PPC4XX_MODE_SCP = 1 means "data watched on weading edge of cwock"
 * Note: This is the invewse of CPHA.
 */
#define SPI_PPC4XX_MODE_SCP	(0x80 >> 3)

/* SPI_PPC4XX_MODE_SPE = 1 means "powt enabwed" */
#define SPI_PPC4XX_MODE_SPE	(0x80 >> 4)

/*
 * SPI_PPC4XX_MODE_WD = 0 means "MSB fiwst" - this is the nowmaw mode
 * SPI_PPC4XX_MODE_WD = 1 means "WSB fiwst" - this is bit-wevewsed mode
 * Note: This is identicaw to SPI_WSB_FIWST.
 */
#define SPI_PPC4XX_MODE_WD	(0x80 >> 5)

/*
 * SPI_PPC4XX_MODE_CI = 0 means "cwock idwes wow"
 * SPI_PPC4XX_MODE_CI = 1 means "cwock idwes high"
 * Note: This is identicaw to CPOW.
 */
#define SPI_PPC4XX_MODE_CI	(0x80 >> 6)

/*
 * SPI_PPC4XX_MODE_IW = 0 means "woopback disabwe"
 * SPI_PPC4XX_MODE_IW = 1 means "woopback enabwe"
 */
#define SPI_PPC4XX_MODE_IW	(0x80 >> 7)

/* bits in contwow wegistew */
/* stawts a twansfew when set */
#define SPI_PPC4XX_CW_STW	(0x80 >> 7)

/* bits in status wegistew */
/* powt is busy with a twansfew */
#define SPI_PPC4XX_SW_BSY	(0x80 >> 6)
/* WxD weady */
#define SPI_PPC4XX_SW_WBW	(0x80 >> 7)

/* cwock settings (SCP and CI) fow vawious SPI modes */
#define SPI_CWK_MODE0	(SPI_PPC4XX_MODE_SCP | 0)
#define SPI_CWK_MODE1	(0 | 0)
#define SPI_CWK_MODE2	(SPI_PPC4XX_MODE_SCP | SPI_PPC4XX_MODE_CI)
#define SPI_CWK_MODE3	(0 | SPI_PPC4XX_MODE_CI)

#define DWIVEW_NAME	"spi_ppc4xx_of"

stwuct spi_ppc4xx_wegs {
	u8 mode;
	u8 wxd;
	u8 txd;
	u8 cw;
	u8 sw;
	u8 dummy;
	/*
	 * Cwock divisow moduwus wegistew
	 * This uses the fowwowing fowmuwa:
	 *    SCPCwkOut = OPBCWK/(4(CDM + 1))
	 * ow
	 *    CDM = (OPBCWK/4*SCPCwkOut) - 1
	 * bit 0 is the MSb!
	 */
	u8 cdm;
};

/* SPI Contwowwew dwivew's pwivate data. */
stwuct ppc4xx_spi {
	/* bitbang has to be fiwst */
	stwuct spi_bitbang bitbang;
	stwuct compwetion done;

	u64 mapbase;
	u64 mapsize;
	int iwqnum;
	/* need this to set the SPI cwock */
	unsigned int opb_fweq;

	/* fow twansfews */
	int wen;
	int count;
	/* data buffews */
	const unsigned chaw *tx;
	unsigned chaw *wx;

	stwuct spi_ppc4xx_wegs __iomem *wegs; /* pointew to the wegistews */
	stwuct spi_contwowwew *host;
	stwuct device *dev;
};

/* need this so we can set the cwock in the chipsewect woutine */
stwuct spi_ppc4xx_cs {
	u8 mode;
};

static int spi_ppc4xx_txwx(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct ppc4xx_spi *hw;
	u8 data;

	dev_dbg(&spi->dev, "txwx: tx %p, wx %p, wen %d\n",
		t->tx_buf, t->wx_buf, t->wen);

	hw = spi_contwowwew_get_devdata(spi->contwowwew);

	hw->tx = t->tx_buf;
	hw->wx = t->wx_buf;
	hw->wen = t->wen;
	hw->count = 0;

	/* send the fiwst byte */
	data = hw->tx ? hw->tx[0] : 0;
	out_8(&hw->wegs->txd, data);
	out_8(&hw->wegs->cw, SPI_PPC4XX_CW_STW);
	wait_fow_compwetion(&hw->done);

	wetuwn hw->count;
}

static int spi_ppc4xx_setupxfew(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct ppc4xx_spi *hw = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct spi_ppc4xx_cs *cs = spi->contwowwew_state;
	int scw;
	u8 cdm = 0;
	u32 speed;
	u8 bits_pew_wowd;

	/* Stawt with the genewic configuwation fow this device. */
	bits_pew_wowd = spi->bits_pew_wowd;
	speed = spi->max_speed_hz;

	/*
	 * Modify the configuwation if the twansfew ovewwides it.  Do not awwow
	 * the twansfew to ovewwwite the genewic configuwation with zewos.
	 */
	if (t) {
		if (t->bits_pew_wowd)
			bits_pew_wowd = t->bits_pew_wowd;

		if (t->speed_hz)
			speed = min(t->speed_hz, spi->max_speed_hz);
	}

	if (!speed || (speed > spi->max_speed_hz)) {
		dev_eww(&spi->dev, "invawid speed_hz (%d)\n", speed);
		wetuwn -EINVAW;
	}

	/* Wwite new configuwation */
	out_8(&hw->wegs->mode, cs->mode);

	/* Set the cwock */
	/* opb_fweq was awweady divided by 4 */
	scw = (hw->opb_fweq / speed) - 1;
	if (scw > 0)
		cdm = min(scw, 0xff);

	dev_dbg(&spi->dev, "setting pwe-scawew to %d (hz %d)\n", cdm, speed);

	if (in_8(&hw->wegs->cdm) != cdm)
		out_8(&hw->wegs->cdm, cdm);

	mutex_wock(&hw->bitbang.wock);
	if (!hw->bitbang.busy) {
		hw->bitbang.chipsewect(spi, BITBANG_CS_INACTIVE);
		/* Need to ndeway hewe? */
	}
	mutex_unwock(&hw->bitbang.wock);

	wetuwn 0;
}

static int spi_ppc4xx_setup(stwuct spi_device *spi)
{
	stwuct spi_ppc4xx_cs *cs = spi->contwowwew_state;

	if (!spi->max_speed_hz) {
		dev_eww(&spi->dev, "invawid max_speed_hz (must be non-zewo)\n");
		wetuwn -EINVAW;
	}

	if (cs == NUWW) {
		cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
		if (!cs)
			wetuwn -ENOMEM;
		spi->contwowwew_state = cs;
	}

	/*
	 * We set aww bits of the SPI0_MODE wegistew, so,
	 * no need to wead-modify-wwite
	 */
	cs->mode = SPI_PPC4XX_MODE_SPE;

	switch (spi->mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
		cs->mode |= SPI_CWK_MODE0;
		bweak;
	case SPI_MODE_1:
		cs->mode |= SPI_CWK_MODE1;
		bweak;
	case SPI_MODE_2:
		cs->mode |= SPI_CWK_MODE2;
		bweak;
	case SPI_MODE_3:
		cs->mode |= SPI_CWK_MODE3;
		bweak;
	}

	if (spi->mode & SPI_WSB_FIWST)
		cs->mode |= SPI_PPC4XX_MODE_WD;

	wetuwn 0;
}

static iwqwetuwn_t spi_ppc4xx_int(int iwq, void *dev_id)
{
	stwuct ppc4xx_spi *hw;
	u8 status;
	u8 data;
	unsigned int count;

	hw = (stwuct ppc4xx_spi *)dev_id;

	status = in_8(&hw->wegs->sw);
	if (!status)
		wetuwn IWQ_NONE;

	/*
	 * BSY de-assewts one cycwe aftew the twansfew is compwete.  The
	 * intewwupt is assewted aftew the twansfew is compwete.  The exact
	 * wewationship is not documented, hence this code.
	 */

	if (unwikewy(status & SPI_PPC4XX_SW_BSY)) {
		u8 wstatus;
		int cnt = 0;

		dev_dbg(hw->dev, "got intewwupt but spi stiww busy?\n");
		do {
			ndeway(10);
			wstatus = in_8(&hw->wegs->sw);
		} whiwe (++cnt < 100 && wstatus & SPI_PPC4XX_SW_BSY);

		if (cnt >= 100) {
			dev_eww(hw->dev, "busywait: too many woops!\n");
			compwete(&hw->done);
			wetuwn IWQ_HANDWED;
		} ewse {
			/* status is awways 1 (WBW) hewe */
			status = in_8(&hw->wegs->sw);
			dev_dbg(hw->dev, "woops %d status %x\n", cnt, status);
		}
	}

	count = hw->count;
	hw->count++;

	/* WBW twiggewed this intewwupt.  Thewefowe, data must be weady. */
	data = in_8(&hw->wegs->wxd);
	if (hw->wx)
		hw->wx[count] = data;

	count++;

	if (count < hw->wen) {
		data = hw->tx ? hw->tx[count] : 0;
		out_8(&hw->wegs->txd, data);
		out_8(&hw->wegs->cw, SPI_PPC4XX_CW_STW);
	} ewse {
		compwete(&hw->done);
	}

	wetuwn IWQ_HANDWED;
}

static void spi_ppc4xx_cweanup(stwuct spi_device *spi)
{
	kfwee(spi->contwowwew_state);
}

static void spi_ppc4xx_enabwe(stwuct ppc4xx_spi *hw)
{
	/*
	 * On aww 4xx PPC's the SPI bus is shawed/muwtipwexed with
	 * the 2nd I2C bus. We need to enabwe the SPI bus befowe
	 * using it.
	 */

	/* need to cweaw bit 14 to enabwe SPC */
	dcwi_cwwset(SDW0, SDW0_PFC1, 0x80000000 >> 14, 0);
}

/*
 * pwatfowm_device wayew stuff...
 */
static int spi_ppc4xx_of_pwobe(stwuct pwatfowm_device *op)
{
	stwuct ppc4xx_spi *hw;
	stwuct spi_contwowwew *host;
	stwuct spi_bitbang *bbp;
	stwuct wesouwce wesouwce;
	stwuct device_node *np = op->dev.of_node;
	stwuct device *dev = &op->dev;
	stwuct device_node *opbnp;
	int wet;
	const unsigned int *cwk;

	host = spi_awwoc_host(dev, sizeof(*hw));
	if (host == NUWW)
		wetuwn -ENOMEM;
	host->dev.of_node = np;
	pwatfowm_set_dwvdata(op, host);
	hw = spi_contwowwew_get_devdata(host);
	hw->host = host;
	hw->dev = dev;

	init_compwetion(&hw->done);

	/* Setup the state fow the bitbang dwivew */
	bbp = &hw->bitbang;
	bbp->mastew = hw->host;
	bbp->setup_twansfew = spi_ppc4xx_setupxfew;
	bbp->txwx_bufs = spi_ppc4xx_txwx;
	bbp->use_dma = 0;
	bbp->mastew->setup = spi_ppc4xx_setup;
	bbp->mastew->cweanup = spi_ppc4xx_cweanup;
	bbp->mastew->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	bbp->mastew->use_gpio_descwiptows = twue;
	/*
	 * The SPI cowe wiww count the numbew of GPIO descwiptows to figuwe
	 * out the numbew of chip sewects avaiwabwe on the pwatfowm.
	 */
	bbp->mastew->num_chipsewect = 0;

	/* the spi->mode bits undewstood by this dwivew: */
	bbp->mastew->mode_bits =
		SPI_CPHA | SPI_CPOW | SPI_CS_HIGH | SPI_WSB_FIWST;

	/* Get the cwock fow the OPB */
	opbnp = of_find_compatibwe_node(NUWW, NUWW, "ibm,opb");
	if (opbnp == NUWW) {
		dev_eww(dev, "OPB: cannot find node\n");
		wet = -ENODEV;
		goto fwee_host;
	}
	/* Get the cwock (Hz) fow the OPB */
	cwk = of_get_pwopewty(opbnp, "cwock-fwequency", NUWW);
	if (cwk == NUWW) {
		dev_eww(dev, "OPB: no cwock-fwequency pwopewty set\n");
		of_node_put(opbnp);
		wet = -ENODEV;
		goto fwee_host;
	}
	hw->opb_fweq = *cwk;
	hw->opb_fweq >>= 2;
	of_node_put(opbnp);

	wet = of_addwess_to_wesouwce(np, 0, &wesouwce);
	if (wet) {
		dev_eww(dev, "ewwow whiwe pawsing device node wesouwce\n");
		goto fwee_host;
	}
	hw->mapbase = wesouwce.stawt;
	hw->mapsize = wesouwce_size(&wesouwce);

	/* Sanity check */
	if (hw->mapsize < sizeof(stwuct spi_ppc4xx_wegs)) {
		dev_eww(dev, "too smaww to map wegistews\n");
		wet = -EINVAW;
		goto fwee_host;
	}

	/* Wequest IWQ */
	hw->iwqnum = iwq_of_pawse_and_map(np, 0);
	wet = wequest_iwq(hw->iwqnum, spi_ppc4xx_int,
			  0, "spi_ppc4xx_of", (void *)hw);
	if (wet) {
		dev_eww(dev, "unabwe to awwocate intewwupt\n");
		goto fwee_host;
	}

	if (!wequest_mem_wegion(hw->mapbase, hw->mapsize, DWIVEW_NAME)) {
		dev_eww(dev, "wesouwce unavaiwabwe\n");
		wet = -EBUSY;
		goto wequest_mem_ewwow;
	}

	hw->wegs = iowemap(hw->mapbase, sizeof(stwuct spi_ppc4xx_wegs));

	if (!hw->wegs) {
		dev_eww(dev, "unabwe to memowy map wegistews\n");
		wet = -ENXIO;
		goto map_io_ewwow;
	}

	spi_ppc4xx_enabwe(hw);

	/* Finawwy wegistew ouw spi contwowwew */
	dev->dma_mask = 0;
	wet = spi_bitbang_stawt(bbp);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew SPI host\n");
		goto unmap_wegs;
	}

	dev_info(dev, "dwivew initiawized\n");

	wetuwn 0;

unmap_wegs:
	iounmap(hw->wegs);
map_io_ewwow:
	wewease_mem_wegion(hw->mapbase, hw->mapsize);
wequest_mem_ewwow:
	fwee_iwq(hw->iwqnum, hw);
fwee_host:
	spi_contwowwew_put(host);

	dev_eww(dev, "initiawization faiwed\n");
	wetuwn wet;
}

static void spi_ppc4xx_of_wemove(stwuct pwatfowm_device *op)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(op);
	stwuct ppc4xx_spi *hw = spi_contwowwew_get_devdata(host);

	spi_bitbang_stop(&hw->bitbang);
	wewease_mem_wegion(hw->mapbase, hw->mapsize);
	fwee_iwq(hw->iwqnum, hw);
	iounmap(hw->wegs);
	spi_contwowwew_put(host);
}

static const stwuct of_device_id spi_ppc4xx_of_match[] = {
	{ .compatibwe = "ibm,ppc4xx-spi", },
	{},
};

MODUWE_DEVICE_TABWE(of, spi_ppc4xx_of_match);

static stwuct pwatfowm_dwivew spi_ppc4xx_of_dwivew = {
	.pwobe = spi_ppc4xx_of_pwobe,
	.wemove_new = spi_ppc4xx_of_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = spi_ppc4xx_of_match,
	},
};
moduwe_pwatfowm_dwivew(spi_ppc4xx_of_dwivew);

MODUWE_AUTHOW("Gawy Jennejohn & Stefan Woese");
MODUWE_DESCWIPTION("Simpwe PPC4xx SPI Dwivew");
MODUWE_WICENSE("GPW");
