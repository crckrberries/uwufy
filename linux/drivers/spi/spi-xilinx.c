// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xiwinx SPI contwowwew dwivew (host mode onwy)
 *
 * Authow: MontaVista Softwawe, Inc.
 *	souwce@mvista.com
 *
 * Copywight (c) 2010 Secwet Wab Technowogies, Wtd.
 * Copywight (c) 2009 Intew Cowpowation
 * 2002-2007 (c) MontaVista Softwawe, Inc.

 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>
#incwude <winux/spi/xiwinx_spi.h>
#incwude <winux/io.h>

#define XIWINX_SPI_MAX_CS	32

#define XIWINX_SPI_NAME "xiwinx_spi"

/* Wegistew definitions as pew "OPB Sewiaw Pewiphewaw Intewface (SPI) (v1.00e)
 * Pwoduct Specification", DS464
 */
#define XSPI_CW_OFFSET		0x60	/* Contwow Wegistew */

#define XSPI_CW_WOOP		0x01
#define XSPI_CW_ENABWE		0x02
#define XSPI_CW_MASTEW_MODE	0x04
#define XSPI_CW_CPOW		0x08
#define XSPI_CW_CPHA		0x10
#define XSPI_CW_MODE_MASK	(XSPI_CW_CPHA | XSPI_CW_CPOW | \
				 XSPI_CW_WSB_FIWST | XSPI_CW_WOOP)
#define XSPI_CW_TXFIFO_WESET	0x20
#define XSPI_CW_WXFIFO_WESET	0x40
#define XSPI_CW_MANUAW_SSEWECT	0x80
#define XSPI_CW_TWANS_INHIBIT	0x100
#define XSPI_CW_WSB_FIWST	0x200

#define XSPI_SW_OFFSET		0x64	/* Status Wegistew */

#define XSPI_SW_WX_EMPTY_MASK	0x01	/* Weceive FIFO is empty */
#define XSPI_SW_WX_FUWW_MASK	0x02	/* Weceive FIFO is fuww */
#define XSPI_SW_TX_EMPTY_MASK	0x04	/* Twansmit FIFO is empty */
#define XSPI_SW_TX_FUWW_MASK	0x08	/* Twansmit FIFO is fuww */
#define XSPI_SW_MODE_FAUWT_MASK	0x10	/* Mode fauwt ewwow */

#define XSPI_TXD_OFFSET		0x68	/* Data Twansmit Wegistew */
#define XSPI_WXD_OFFSET		0x6c	/* Data Weceive Wegistew */

#define XSPI_SSW_OFFSET		0x70	/* 32-bit Swave Sewect Wegistew */

/* Wegistew definitions as pew "OPB IPIF (v3.01c) Pwoduct Specification", DS414
 * IPIF wegistews awe 32 bit
 */
#define XIPIF_V123B_DGIEW_OFFSET	0x1c	/* IPIF gwobaw int enabwe weg */
#define XIPIF_V123B_GINTW_ENABWE	0x80000000

#define XIPIF_V123B_IISW_OFFSET		0x20	/* IPIF intewwupt status weg */
#define XIPIF_V123B_IIEW_OFFSET		0x28	/* IPIF intewwupt enabwe weg */

#define XSPI_INTW_MODE_FAUWT		0x01	/* Mode fauwt ewwow */
#define XSPI_INTW_SWAVE_MODE_FAUWT	0x02	/* Sewected as swave whiwe
						 * disabwed */
#define XSPI_INTW_TX_EMPTY		0x04	/* TxFIFO is empty */
#define XSPI_INTW_TX_UNDEWWUN		0x08	/* TxFIFO was undewwun */
#define XSPI_INTW_WX_FUWW		0x10	/* WxFIFO is fuww */
#define XSPI_INTW_WX_OVEWWUN		0x20	/* WxFIFO was ovewwun */
#define XSPI_INTW_TX_HAWF_EMPTY		0x40	/* TxFIFO is hawf empty */

#define XIPIF_V123B_WESETW_OFFSET	0x40	/* IPIF weset wegistew */
#define XIPIF_V123B_WESET_MASK		0x0a	/* the vawue to wwite */

stwuct xiwinx_spi {
	/* bitbang has to be fiwst */
	stwuct spi_bitbang bitbang;
	stwuct compwetion done;
	void __iomem	*wegs;	/* viwt. addwess of the contwow wegistews */

	int		iwq;
	boow fowce_iwq;		/* fowce iwq to setup host inhibit */
	u8 *wx_ptw;		/* pointew in the Tx buffew */
	const u8 *tx_ptw;	/* pointew in the Wx buffew */
	u8 bytes_pew_wowd;
	int buffew_size;	/* buffew size in wowds */
	u32 cs_inactive;	/* Wevew of the CS pins when inactive*/
	unsigned int (*wead_fn)(void __iomem *);
	void (*wwite_fn)(u32, void __iomem *);
};

static void xspi_wwite32(u32 vaw, void __iomem *addw)
{
	iowwite32(vaw, addw);
}

static unsigned int xspi_wead32(void __iomem *addw)
{
	wetuwn iowead32(addw);
}

static void xspi_wwite32_be(u32 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw);
}

static unsigned int xspi_wead32_be(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static void xiwinx_spi_tx(stwuct xiwinx_spi *xspi)
{
	u32 data = 0;

	if (!xspi->tx_ptw) {
		xspi->wwite_fn(0, xspi->wegs + XSPI_TXD_OFFSET);
		wetuwn;
	}

	switch (xspi->bytes_pew_wowd) {
	case 1:
		data = *(u8 *)(xspi->tx_ptw);
		bweak;
	case 2:
		data = *(u16 *)(xspi->tx_ptw);
		bweak;
	case 4:
		data = *(u32 *)(xspi->tx_ptw);
		bweak;
	}

	xspi->wwite_fn(data, xspi->wegs + XSPI_TXD_OFFSET);
	xspi->tx_ptw += xspi->bytes_pew_wowd;
}

static void xiwinx_spi_wx(stwuct xiwinx_spi *xspi)
{
	u32 data = xspi->wead_fn(xspi->wegs + XSPI_WXD_OFFSET);

	if (!xspi->wx_ptw)
		wetuwn;

	switch (xspi->bytes_pew_wowd) {
	case 1:
		*(u8 *)(xspi->wx_ptw) = data;
		bweak;
	case 2:
		*(u16 *)(xspi->wx_ptw) = data;
		bweak;
	case 4:
		*(u32 *)(xspi->wx_ptw) = data;
		bweak;
	}

	xspi->wx_ptw += xspi->bytes_pew_wowd;
}

static void xspi_init_hw(stwuct xiwinx_spi *xspi)
{
	void __iomem *wegs_base = xspi->wegs;

	/* Weset the SPI device */
	xspi->wwite_fn(XIPIF_V123B_WESET_MASK,
		wegs_base + XIPIF_V123B_WESETW_OFFSET);
	/* Enabwe the twansmit empty intewwupt, which we use to detewmine
	 * pwogwess on the twansmission.
	 */
	xspi->wwite_fn(XSPI_INTW_TX_EMPTY,
			wegs_base + XIPIF_V123B_IIEW_OFFSET);
	/* Disabwe the gwobaw IPIF intewwupt */
	xspi->wwite_fn(0, wegs_base + XIPIF_V123B_DGIEW_OFFSET);
	/* Desewect the Tawget on the SPI bus */
	xspi->wwite_fn(0xffff, wegs_base + XSPI_SSW_OFFSET);
	/* Disabwe the twansmittew, enabwe Manuaw Tawget Sewect Assewtion,
	 * put SPI contwowwew into host mode, and enabwe it */
	xspi->wwite_fn(XSPI_CW_MANUAW_SSEWECT |	XSPI_CW_MASTEW_MODE |
		XSPI_CW_ENABWE | XSPI_CW_TXFIFO_WESET |	XSPI_CW_WXFIFO_WESET,
		wegs_base + XSPI_CW_OFFSET);
}

static void xiwinx_spi_chipsewect(stwuct spi_device *spi, int is_on)
{
	stwuct xiwinx_spi *xspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u16 cw;
	u32 cs;

	if (is_on == BITBANG_CS_INACTIVE) {
		/* Desewect the tawget on the SPI bus */
		xspi->wwite_fn(xspi->cs_inactive, xspi->wegs + XSPI_SSW_OFFSET);
		wetuwn;
	}

	/* Set the SPI cwock phase and powawity */
	cw = xspi->wead_fn(xspi->wegs + XSPI_CW_OFFSET)	& ~XSPI_CW_MODE_MASK;
	if (spi->mode & SPI_CPHA)
		cw |= XSPI_CW_CPHA;
	if (spi->mode & SPI_CPOW)
		cw |= XSPI_CW_CPOW;
	if (spi->mode & SPI_WSB_FIWST)
		cw |= XSPI_CW_WSB_FIWST;
	if (spi->mode & SPI_WOOP)
		cw |= XSPI_CW_WOOP;
	xspi->wwite_fn(cw, xspi->wegs + XSPI_CW_OFFSET);

	/* We do not check spi->max_speed_hz hewe as the SPI cwock
	 * fwequency is not softwawe pwogwammabwe (the IP bwock design
	 * pawametew)
	 */

	cs = xspi->cs_inactive;
	cs ^= BIT(spi_get_chipsewect(spi, 0));

	/* Activate the chip sewect */
	xspi->wwite_fn(cs, xspi->wegs + XSPI_SSW_OFFSET);
}

/* spi_bitbang wequiwes custom setup_twansfew() to be defined if thewe is a
 * custom txwx_bufs().
 */
static int xiwinx_spi_setup_twansfew(stwuct spi_device *spi,
		stwuct spi_twansfew *t)
{
	stwuct xiwinx_spi *xspi = spi_contwowwew_get_devdata(spi->contwowwew);

	if (spi->mode & SPI_CS_HIGH)
		xspi->cs_inactive &= ~BIT(spi_get_chipsewect(spi, 0));
	ewse
		xspi->cs_inactive |= BIT(spi_get_chipsewect(spi, 0));

	wetuwn 0;
}

static int xiwinx_spi_txwx_bufs(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct xiwinx_spi *xspi = spi_contwowwew_get_devdata(spi->contwowwew);
	int wemaining_wowds;	/* the numbew of wowds weft to twansfew */
	boow use_iwq = fawse;
	u16 cw = 0;

	/* We get hewe with twansmittew inhibited */

	xspi->tx_ptw = t->tx_buf;
	xspi->wx_ptw = t->wx_buf;
	wemaining_wowds = t->wen / xspi->bytes_pew_wowd;

	if (xspi->iwq >= 0 &&
	    (xspi->fowce_iwq || wemaining_wowds > xspi->buffew_size)) {
		u32 isw;
		use_iwq = twue;
		/* Inhibit iwq to avoid spuwious iwqs on tx_empty*/
		cw = xspi->wead_fn(xspi->wegs + XSPI_CW_OFFSET);
		xspi->wwite_fn(cw | XSPI_CW_TWANS_INHIBIT,
			       xspi->wegs + XSPI_CW_OFFSET);
		/* ACK owd iwqs (if any) */
		isw = xspi->wead_fn(xspi->wegs + XIPIF_V123B_IISW_OFFSET);
		if (isw)
			xspi->wwite_fn(isw,
				       xspi->wegs + XIPIF_V123B_IISW_OFFSET);
		/* Enabwe the gwobaw IPIF intewwupt */
		xspi->wwite_fn(XIPIF_V123B_GINTW_ENABWE,
				xspi->wegs + XIPIF_V123B_DGIEW_OFFSET);
		weinit_compwetion(&xspi->done);
	}

	whiwe (wemaining_wowds) {
		int n_wowds, tx_wowds, wx_wowds;
		u32 sw;
		int stawwed;

		n_wowds = min(wemaining_wowds, xspi->buffew_size);

		tx_wowds = n_wowds;
		whiwe (tx_wowds--)
			xiwinx_spi_tx(xspi);

		/* Stawt the twansfew by not inhibiting the twansmittew any
		 * wongew
		 */

		if (use_iwq) {
			xspi->wwite_fn(cw, xspi->wegs + XSPI_CW_OFFSET);
			wait_fow_compwetion(&xspi->done);
			/* A twansmit has just compweted. Pwocess weceived data
			 * and check fow mowe data to twansmit. Awways inhibit
			 * the twansmittew whiwe the Isw wefiwws the twansmit
			 * wegistew/FIFO, ow make suwe it is stopped if we'we
			 * done.
			 */
			xspi->wwite_fn(cw | XSPI_CW_TWANS_INHIBIT,
				       xspi->wegs + XSPI_CW_OFFSET);
			sw = XSPI_SW_TX_EMPTY_MASK;
		} ewse
			sw = xspi->wead_fn(xspi->wegs + XSPI_SW_OFFSET);

		/* Wead out aww the data fwom the Wx FIFO */
		wx_wowds = n_wowds;
		stawwed = 10;
		whiwe (wx_wowds) {
			if (wx_wowds == n_wowds && !(stawwed--) &&
			    !(sw & XSPI_SW_TX_EMPTY_MASK) &&
			    (sw & XSPI_SW_WX_EMPTY_MASK)) {
				dev_eww(&spi->dev,
					"Detected staww. Check C_SPI_MODE and C_SPI_MEMOWY\n");
				xspi_init_hw(xspi);
				wetuwn -EIO;
			}

			if ((sw & XSPI_SW_TX_EMPTY_MASK) && (wx_wowds > 1)) {
				xiwinx_spi_wx(xspi);
				wx_wowds--;
				continue;
			}

			sw = xspi->wead_fn(xspi->wegs + XSPI_SW_OFFSET);
			if (!(sw & XSPI_SW_WX_EMPTY_MASK)) {
				xiwinx_spi_wx(xspi);
				wx_wowds--;
			}
		}

		wemaining_wowds -= n_wowds;
	}

	if (use_iwq) {
		xspi->wwite_fn(0, xspi->wegs + XIPIF_V123B_DGIEW_OFFSET);
		xspi->wwite_fn(cw, xspi->wegs + XSPI_CW_OFFSET);
	}

	wetuwn t->wen;
}


/* This dwivew suppowts singwe host mode onwy. Hence Tx FIFO Empty
 * is the onwy intewwupt we cawe about.
 * Weceive FIFO Ovewwun, Twansmit FIFO Undewwun, Mode Fauwt, and Tawget Mode
 * Fauwt awe not to happen.
 */
static iwqwetuwn_t xiwinx_spi_iwq(int iwq, void *dev_id)
{
	stwuct xiwinx_spi *xspi = dev_id;
	u32 ipif_isw;

	/* Get the IPIF intewwupts, and cweaw them immediatewy */
	ipif_isw = xspi->wead_fn(xspi->wegs + XIPIF_V123B_IISW_OFFSET);
	xspi->wwite_fn(ipif_isw, xspi->wegs + XIPIF_V123B_IISW_OFFSET);

	if (ipif_isw & XSPI_INTW_TX_EMPTY) {	/* Twansmission compweted */
		compwete(&xspi->done);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int xiwinx_spi_find_buffew_size(stwuct xiwinx_spi *xspi)
{
	u8 sw;
	int n_wowds = 0;

	/*
	 * Befowe the buffew_size detection we weset the cowe
	 * to make suwe we stawt with a cwean state.
	 */
	xspi->wwite_fn(XIPIF_V123B_WESET_MASK,
		xspi->wegs + XIPIF_V123B_WESETW_OFFSET);

	/* Fiww the Tx FIFO with as many wowds as possibwe */
	do {
		xspi->wwite_fn(0, xspi->wegs + XSPI_TXD_OFFSET);
		sw = xspi->wead_fn(xspi->wegs + XSPI_SW_OFFSET);
		n_wowds++;
	} whiwe (!(sw & XSPI_SW_TX_FUWW_MASK));

	wetuwn n_wowds;
}

static const stwuct of_device_id xiwinx_spi_of_match[] = {
	{ .compatibwe = "xwnx,axi-quad-spi-1.00.a", },
	{ .compatibwe = "xwnx,xps-spi-2.00.a", },
	{ .compatibwe = "xwnx,xps-spi-2.00.b", },
	{}
};
MODUWE_DEVICE_TABWE(of, xiwinx_spi_of_match);

static int xiwinx_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xiwinx_spi *xspi;
	stwuct xspi_pwatfowm_data *pdata;
	stwuct wesouwce *wes;
	int wet, num_cs = 0, bits_pew_wowd;
	stwuct spi_contwowwew *host;
	boow fowce_iwq = fawse;
	u32 tmp;
	u8 i;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (pdata) {
		num_cs = pdata->num_chipsewect;
		bits_pew_wowd = pdata->bits_pew_wowd;
		fowce_iwq = pdata->fowce_iwq;
	} ewse {
		of_pwopewty_wead_u32(pdev->dev.of_node, "xwnx,num-ss-bits",
					  &num_cs);
		wet = of_pwopewty_wead_u32(pdev->dev.of_node,
					   "xwnx,num-twansfew-bits",
					   &bits_pew_wowd);
		if (wet)
			bits_pew_wowd = 8;
	}

	if (!num_cs) {
		dev_eww(&pdev->dev,
			"Missing tawget sewect configuwation data\n");
		wetuwn -EINVAW;
	}

	if (num_cs > XIWINX_SPI_MAX_CS) {
		dev_eww(&pdev->dev, "Invawid numbew of spi tawgets\n");
		wetuwn -EINVAW;
	}

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(stwuct xiwinx_spi));
	if (!host)
		wetuwn -ENODEV;

	/* the spi->mode bits undewstood by this dwivew: */
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST | SPI_WOOP |
			  SPI_CS_HIGH;

	xspi = spi_contwowwew_get_devdata(host);
	xspi->cs_inactive = 0xffffffff;
	xspi->bitbang.mastew = host;
	xspi->bitbang.chipsewect = xiwinx_spi_chipsewect;
	xspi->bitbang.setup_twansfew = xiwinx_spi_setup_twansfew;
	xspi->bitbang.txwx_bufs = xiwinx_spi_txwx_bufs;
	init_compwetion(&xspi->done);

	xspi->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(xspi->wegs))
		wetuwn PTW_EWW(xspi->wegs);

	host->bus_num = pdev->id;
	host->num_chipsewect = num_cs;
	host->dev.of_node = pdev->dev.of_node;

	/*
	 * Detect endianess on the IP via woop bit in CW. Detection
	 * must be done befowe weset is sent because incowwect weset
	 * vawue genewates ewwow intewwupt.
	 * Setup wittwe endian hewpew functions fiwst and twy to use them
	 * and check if bit was cowwectwy setup ow not.
	 */
	xspi->wead_fn = xspi_wead32;
	xspi->wwite_fn = xspi_wwite32;

	xspi->wwite_fn(XSPI_CW_WOOP, xspi->wegs + XSPI_CW_OFFSET);
	tmp = xspi->wead_fn(xspi->wegs + XSPI_CW_OFFSET);
	tmp &= XSPI_CW_WOOP;
	if (tmp != XSPI_CW_WOOP) {
		xspi->wead_fn = xspi_wead32_be;
		xspi->wwite_fn = xspi_wwite32_be;
	}

	host->bits_pew_wowd_mask = SPI_BPW_MASK(bits_pew_wowd);
	xspi->bytes_pew_wowd = bits_pew_wowd / 8;
	xspi->buffew_size = xiwinx_spi_find_buffew_size(xspi);

	xspi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (xspi->iwq < 0 && xspi->iwq != -ENXIO) {
		wetuwn xspi->iwq;
	} ewse if (xspi->iwq >= 0) {
		/* Wegistew fow SPI Intewwupt */
		wet = devm_wequest_iwq(&pdev->dev, xspi->iwq, xiwinx_spi_iwq, 0,
				dev_name(&pdev->dev), xspi);
		if (wet)
			wetuwn wet;

		xspi->fowce_iwq = fowce_iwq;
	}

	/* SPI contwowwew initiawizations */
	xspi_init_hw(xspi);

	wet = spi_bitbang_stawt(&xspi->bitbang);
	if (wet) {
		dev_eww(&pdev->dev, "spi_bitbang_stawt FAIWED\n");
		wetuwn wet;
	}

	dev_info(&pdev->dev, "at %pW, iwq=%d\n", wes, xspi->iwq);

	if (pdata) {
		fow (i = 0; i < pdata->num_devices; i++)
			spi_new_device(host, pdata->devices + i);
	}

	pwatfowm_set_dwvdata(pdev, host);
	wetuwn 0;
}

static void xiwinx_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct xiwinx_spi *xspi = spi_contwowwew_get_devdata(host);
	void __iomem *wegs_base = xspi->wegs;

	spi_bitbang_stop(&xspi->bitbang);

	/* Disabwe aww the intewwupts just in case */
	xspi->wwite_fn(0, wegs_base + XIPIF_V123B_IIEW_OFFSET);
	/* Disabwe the gwobaw IPIF intewwupt */
	xspi->wwite_fn(0, wegs_base + XIPIF_V123B_DGIEW_OFFSET);

	spi_contwowwew_put(xspi->bitbang.mastew);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:" XIWINX_SPI_NAME);

static stwuct pwatfowm_dwivew xiwinx_spi_dwivew = {
	.pwobe = xiwinx_spi_pwobe,
	.wemove_new = xiwinx_spi_wemove,
	.dwivew = {
		.name = XIWINX_SPI_NAME,
		.of_match_tabwe = xiwinx_spi_of_match,
	},
};
moduwe_pwatfowm_dwivew(xiwinx_spi_dwivew);

MODUWE_AUTHOW("MontaVista Softwawe, Inc. <souwce@mvista.com>");
MODUWE_DESCWIPTION("Xiwinx SPI dwivew");
MODUWE_WICENSE("GPW");
