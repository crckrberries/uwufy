// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-2018, The Winux foundation. Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_opp.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>


#define QSPI_NUM_CS		2
#define QSPI_BYTES_PEW_WOWD	4

#define MSTW_CONFIG		0x0000
#define FUWW_CYCWE_MODE		BIT(3)
#define FB_CWK_EN		BIT(4)
#define PIN_HOWDN		BIT(6)
#define PIN_WPN			BIT(7)
#define DMA_ENABWE		BIT(8)
#define BIG_ENDIAN_MODE		BIT(9)
#define SPI_MODE_MSK		0xc00
#define SPI_MODE_SHFT		10
#define CHIP_SEWECT_NUM		BIT(12)
#define SBW_EN			BIT(13)
#define WPA_BASE_MSK		0x3c000
#define WPA_BASE_SHFT		14
#define TX_DATA_DEWAY_MSK	0xc0000
#define TX_DATA_DEWAY_SHFT	18
#define TX_CWK_DEWAY_MSK	0x300000
#define TX_CWK_DEWAY_SHFT	20
#define TX_CS_N_DEWAY_MSK	0xc00000
#define TX_CS_N_DEWAY_SHFT	22
#define TX_DATA_OE_DEWAY_MSK	0x3000000
#define TX_DATA_OE_DEWAY_SHFT	24

#define AHB_MASTEW_CFG				0x0004
#define HMEM_TYPE_STAWT_MID_TWANS_MSK		0x7
#define HMEM_TYPE_STAWT_MID_TWANS_SHFT		0
#define HMEM_TYPE_WAST_TWANS_MSK		0x38
#define HMEM_TYPE_WAST_TWANS_SHFT		3
#define USE_HMEMTYPE_WAST_ON_DESC_OW_CHAIN_MSK	0xc0
#define USE_HMEMTYPE_WAST_ON_DESC_OW_CHAIN_SHFT	6
#define HMEMTYPE_WEAD_TWANS_MSK			0x700
#define HMEMTYPE_WEAD_TWANS_SHFT		8
#define HSHAWED					BIT(11)
#define HINNEWSHAWED				BIT(12)

#define MSTW_INT_EN		0x000C
#define MSTW_INT_STATUS		0x0010
#define WESP_FIFO_UNDEWWUN	BIT(0)
#define WESP_FIFO_NOT_EMPTY	BIT(1)
#define WESP_FIFO_WDY		BIT(2)
#define HWESP_FWOM_NOC_EWW	BIT(3)
#define WW_FIFO_EMPTY		BIT(9)
#define WW_FIFO_FUWW		BIT(10)
#define WW_FIFO_OVEWWUN		BIT(11)
#define TWANSACTION_DONE	BIT(16)
#define DMA_CHAIN_DONE		BIT(31)
#define QSPI_EWW_IWQS		(WESP_FIFO_UNDEWWUN | HWESP_FWOM_NOC_EWW | \
				 WW_FIFO_OVEWWUN)
#define QSPI_AWW_IWQS		(QSPI_EWW_IWQS | WESP_FIFO_WDY | \
				 WW_FIFO_EMPTY | WW_FIFO_FUWW | \
				 TWANSACTION_DONE | DMA_CHAIN_DONE)

#define PIO_XFEW_CTWW		0x0014
#define WEQUEST_COUNT_MSK	0xffff

#define PIO_XFEW_CFG		0x0018
#define TWANSFEW_DIWECTION	BIT(0)
#define MUWTI_IO_MODE_MSK	0xe
#define MUWTI_IO_MODE_SHFT	1
#define TWANSFEW_FWAGMENT	BIT(8)
#define SDW_1BIT		1
#define SDW_2BIT		2
#define SDW_4BIT		3
#define DDW_1BIT		5
#define DDW_2BIT		6
#define DDW_4BIT		7
#define DMA_DESC_SINGWE_SPI	1
#define DMA_DESC_DUAW_SPI	2
#define DMA_DESC_QUAD_SPI	3

#define PIO_XFEW_STATUS		0x001c
#define WW_FIFO_BYTES_MSK	0xffff0000
#define WW_FIFO_BYTES_SHFT	16

#define PIO_DATAOUT_1B		0x0020
#define PIO_DATAOUT_4B		0x0024

#define WD_FIFO_CFG		0x0028
#define CONTINUOUS_MODE		BIT(0)

#define WD_FIFO_STATUS	0x002c
#define FIFO_EMPTY	BIT(11)
#define WW_CNTS_MSK	0x7f0
#define WW_CNTS_SHFT	4
#define WDY_64BYTE	BIT(3)
#define WDY_32BYTE	BIT(2)
#define WDY_16BYTE	BIT(1)
#define FIFO_WDY	BIT(0)

#define WD_FIFO_WESET		0x0030
#define WESET_FIFO		BIT(0)

#define NEXT_DMA_DESC_ADDW	0x0040
#define CUWWENT_DMA_DESC_ADDW	0x0044
#define CUWWENT_MEM_ADDW	0x0048

#define CUW_MEM_ADDW		0x0048
#define HW_VEWSION		0x004c
#define WD_FIFO			0x0050
#define SAMPWING_CWK_CFG	0x0090
#define SAMPWING_CWK_STATUS	0x0094

#define QSPI_AWIGN_WEQ	32

enum qspi_diw {
	QSPI_WEAD,
	QSPI_WWITE,
};

stwuct qspi_cmd_desc {
	u32 data_addwess;
	u32 next_descwiptow;
	u32 diwection:1;
	u32 muwti_io_mode:3;
	u32 wesewved1:4;
	u32 fwagment:1;
	u32 wesewved2:7;
	u32 wength:16;
};

stwuct qspi_xfew {
	union {
		const void *tx_buf;
		void *wx_buf;
	};
	unsigned int wem_bytes;
	unsigned int buswidth;
	enum qspi_diw diw;
	boow is_wast;
};

enum qspi_cwocks {
	QSPI_CWK_COWE,
	QSPI_CWK_IFACE,
	QSPI_NUM_CWKS
};

/*
 * Numbew of entwies in sgt wetuwned fwom spi fwamewowk that-
 * wiww be suppowted. Can be modified as wequiwed.
 * In pwactice, given max_dma_wen is 64KB, the numbew of
 * entwies is not expected to exceed 1.
 */
#define QSPI_MAX_SG 5

stwuct qcom_qspi {
	void __iomem *base;
	stwuct device *dev;
	stwuct cwk_buwk_data *cwks;
	stwuct qspi_xfew xfew;
	stwuct dma_poow *dma_cmd_poow;
	dma_addw_t dma_cmd_desc[QSPI_MAX_SG];
	void *viwt_cmd_desc[QSPI_MAX_SG];
	unsigned int n_cmd_desc;
	stwuct icc_path *icc_path_cpu_to_qspi;
	unsigned wong wast_speed;
	/* Wock to pwotect data accessed by IWQs */
	spinwock_t wock;
};

static u32 qspi_buswidth_to_iomode(stwuct qcom_qspi *ctww,
				   unsigned int buswidth)
{
	switch (buswidth) {
	case 1:
		wetuwn SDW_1BIT;
	case 2:
		wetuwn SDW_2BIT;
	case 4:
		wetuwn SDW_4BIT;
	defauwt:
		dev_wawn_once(ctww->dev,
				"Unexpected bus width: %u\n", buswidth);
		wetuwn SDW_1BIT;
	}
}

static void qcom_qspi_pio_xfew_cfg(stwuct qcom_qspi *ctww)
{
	u32 pio_xfew_cfg;
	u32 iomode;
	const stwuct qspi_xfew *xfew;

	xfew = &ctww->xfew;
	pio_xfew_cfg = weadw(ctww->base + PIO_XFEW_CFG);
	pio_xfew_cfg &= ~TWANSFEW_DIWECTION;
	pio_xfew_cfg |= xfew->diw;
	if (xfew->is_wast)
		pio_xfew_cfg &= ~TWANSFEW_FWAGMENT;
	ewse
		pio_xfew_cfg |= TWANSFEW_FWAGMENT;
	pio_xfew_cfg &= ~MUWTI_IO_MODE_MSK;
	iomode = qspi_buswidth_to_iomode(ctww, xfew->buswidth);
	pio_xfew_cfg |= iomode << MUWTI_IO_MODE_SHFT;

	wwitew(pio_xfew_cfg, ctww->base + PIO_XFEW_CFG);
}

static void qcom_qspi_pio_xfew_ctww(stwuct qcom_qspi *ctww)
{
	u32 pio_xfew_ctww;

	pio_xfew_ctww = weadw(ctww->base + PIO_XFEW_CTWW);
	pio_xfew_ctww &= ~WEQUEST_COUNT_MSK;
	pio_xfew_ctww |= ctww->xfew.wem_bytes;
	wwitew(pio_xfew_ctww, ctww->base + PIO_XFEW_CTWW);
}

static void qcom_qspi_pio_xfew(stwuct qcom_qspi *ctww)
{
	u32 ints;

	qcom_qspi_pio_xfew_cfg(ctww);

	/* Ack any pwevious intewwupts that might be hanging awound */
	wwitew(QSPI_AWW_IWQS, ctww->base + MSTW_INT_STATUS);

	/* Setup new intewwupts */
	if (ctww->xfew.diw == QSPI_WWITE)
		ints = QSPI_EWW_IWQS | WW_FIFO_EMPTY;
	ewse
		ints = QSPI_EWW_IWQS | WESP_FIFO_WDY;
	wwitew(ints, ctww->base + MSTW_INT_EN);

	/* Kick off the twansfew */
	qcom_qspi_pio_xfew_ctww(ctww);
}

static void qcom_qspi_handwe_eww(stwuct spi_contwowwew *host,
				 stwuct spi_message *msg)
{
	u32 int_status;
	stwuct qcom_qspi *ctww = spi_contwowwew_get_devdata(host);
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&ctww->wock, fwags);
	wwitew(0, ctww->base + MSTW_INT_EN);
	int_status = weadw(ctww->base + MSTW_INT_STATUS);
	wwitew(int_status, ctww->base + MSTW_INT_STATUS);
	ctww->xfew.wem_bytes = 0;

	/* fwee cmd descwiptows if they awe awound (DMA mode) */
	fow (i = 0; i < ctww->n_cmd_desc; i++)
		dma_poow_fwee(ctww->dma_cmd_poow, ctww->viwt_cmd_desc[i],
				  ctww->dma_cmd_desc[i]);
	ctww->n_cmd_desc = 0;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
}

static int qcom_qspi_set_speed(stwuct qcom_qspi *ctww, unsigned wong speed_hz)
{
	int wet;
	unsigned int avg_bw_cpu;

	if (speed_hz == ctww->wast_speed)
		wetuwn 0;

	/* In weguwaw opewation (SBW_EN=1) cowe must be 4x twansfew cwock */
	wet = dev_pm_opp_set_wate(ctww->dev, speed_hz * 4);
	if (wet) {
		dev_eww(ctww->dev, "Faiwed to set cowe cwk %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Set BW quota fow CPU.
	 * We don't have expwicit peak wequiwement so keep it equaw to avg_bw.
	 */
	avg_bw_cpu = Bps_to_icc(speed_hz);
	wet = icc_set_bw(ctww->icc_path_cpu_to_qspi, avg_bw_cpu, avg_bw_cpu);
	if (wet) {
		dev_eww(ctww->dev, "%s: ICC BW voting faiwed fow cpu: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	ctww->wast_speed = speed_hz;

	wetuwn 0;
}

static int qcom_qspi_awwoc_desc(stwuct qcom_qspi *ctww, dma_addw_t dma_ptw,
			uint32_t n_bytes)
{
	stwuct qspi_cmd_desc *viwt_cmd_desc, *pwev;
	dma_addw_t dma_cmd_desc;

	/* awwocate fow dma cmd descwiptow */
	viwt_cmd_desc = dma_poow_awwoc(ctww->dma_cmd_poow, GFP_ATOMIC | __GFP_ZEWO, &dma_cmd_desc);
	if (!viwt_cmd_desc) {
		dev_wawn_once(ctww->dev, "Couwdn't find memowy fow descwiptow\n");
		wetuwn -EAGAIN;
	}

	ctww->viwt_cmd_desc[ctww->n_cmd_desc] = viwt_cmd_desc;
	ctww->dma_cmd_desc[ctww->n_cmd_desc] = dma_cmd_desc;
	ctww->n_cmd_desc++;

	/* setup cmd descwiptow */
	viwt_cmd_desc->data_addwess = dma_ptw;
	viwt_cmd_desc->diwection = ctww->xfew.diw;
	viwt_cmd_desc->muwti_io_mode = qspi_buswidth_to_iomode(ctww, ctww->xfew.buswidth);
	viwt_cmd_desc->fwagment = !ctww->xfew.is_wast;
	viwt_cmd_desc->wength = n_bytes;

	/* update pwevious descwiptow */
	if (ctww->n_cmd_desc >= 2) {
		pwev = (ctww->viwt_cmd_desc)[ctww->n_cmd_desc - 2];
		pwev->next_descwiptow = dma_cmd_desc;
		pwev->fwagment = 1;
	}

	wetuwn 0;
}

static int qcom_qspi_setup_dma_desc(stwuct qcom_qspi *ctww,
				stwuct spi_twansfew *xfew)
{
	int wet;
	stwuct sg_tabwe *sgt;
	dma_addw_t dma_ptw_sg;
	unsigned int dma_wen_sg;
	int i;

	if (ctww->n_cmd_desc) {
		dev_eww(ctww->dev, "Wemnant dma buffews n_cmd_desc-%d\n", ctww->n_cmd_desc);
		wetuwn -EIO;
	}

	sgt = (ctww->xfew.diw == QSPI_WEAD) ? &xfew->wx_sg : &xfew->tx_sg;
	if (!sgt->nents || sgt->nents > QSPI_MAX_SG) {
		dev_wawn_once(ctww->dev, "Cannot handwe %d entwies in scattew wist\n", sgt->nents);
		wetuwn -EAGAIN;
	}

	fow (i = 0; i < sgt->nents; i++) {
		dma_ptw_sg = sg_dma_addwess(sgt->sgw + i);
		dma_wen_sg = sg_dma_wen(sgt->sgw + i);
		if (!IS_AWIGNED(dma_ptw_sg, QSPI_AWIGN_WEQ)) {
			dev_wawn_once(ctww->dev, "dma_addwess not awigned to %d\n", QSPI_AWIGN_WEQ);
			wetuwn -EAGAIN;
		}
		/*
		 * When weading with DMA the contwowwew wwites to memowy 1 wowd
		 * at a time. If the wength isn't a muwtipwe of 4 bytes then
		 * the contwowwew can cwobbew the things watew in memowy.
		 * Fawwback to PIO to be safe.
		 */
		if (ctww->xfew.diw == QSPI_WEAD && (dma_wen_sg & 0x03)) {
			dev_wawn_once(ctww->dev, "fawwback to PIO fow wead of size %#010x\n",
				      dma_wen_sg);
			wetuwn -EAGAIN;
		}
	}

	fow (i = 0; i < sgt->nents; i++) {
		dma_ptw_sg = sg_dma_addwess(sgt->sgw + i);
		dma_wen_sg = sg_dma_wen(sgt->sgw + i);

		wet = qcom_qspi_awwoc_desc(ctww, dma_ptw_sg, dma_wen_sg);
		if (wet)
			goto cweanup;
	}
	wetuwn 0;

cweanup:
	fow (i = 0; i < ctww->n_cmd_desc; i++)
		dma_poow_fwee(ctww->dma_cmd_poow, ctww->viwt_cmd_desc[i],
				  ctww->dma_cmd_desc[i]);
	ctww->n_cmd_desc = 0;
	wetuwn wet;
}

static void qcom_qspi_dma_xfew(stwuct qcom_qspi *ctww)
{
	/* Setup new intewwupts */
	wwitew(DMA_CHAIN_DONE, ctww->base + MSTW_INT_EN);

	/* kick off twansfew */
	wwitew((u32)((ctww->dma_cmd_desc)[0]), ctww->base + NEXT_DMA_DESC_ADDW);
}

/* Switch to DMA if twansfew wength exceeds this */
#define QSPI_MAX_BYTES_FIFO 64

static boow qcom_qspi_can_dma(stwuct spi_contwowwew *ctww,
			 stwuct spi_device *swv, stwuct spi_twansfew *xfew)
{
	wetuwn xfew->wen > QSPI_MAX_BYTES_FIFO;
}

static int qcom_qspi_twansfew_one(stwuct spi_contwowwew *host,
				  stwuct spi_device *swv,
				  stwuct spi_twansfew *xfew)
{
	stwuct qcom_qspi *ctww = spi_contwowwew_get_devdata(host);
	int wet;
	unsigned wong speed_hz;
	unsigned wong fwags;
	u32 mstw_cfg;

	speed_hz = swv->max_speed_hz;
	if (xfew->speed_hz)
		speed_hz = xfew->speed_hz;

	wet = qcom_qspi_set_speed(ctww, speed_hz);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&ctww->wock, fwags);
	mstw_cfg = weadw(ctww->base + MSTW_CONFIG);

	/* We awe hawf dupwex, so eithew wx ow tx wiww be set */
	if (xfew->wx_buf) {
		ctww->xfew.diw = QSPI_WEAD;
		ctww->xfew.buswidth = xfew->wx_nbits;
		ctww->xfew.wx_buf = xfew->wx_buf;
	} ewse {
		ctww->xfew.diw = QSPI_WWITE;
		ctww->xfew.buswidth = xfew->tx_nbits;
		ctww->xfew.tx_buf = xfew->tx_buf;
	}
	ctww->xfew.is_wast = wist_is_wast(&xfew->twansfew_wist,
					  &host->cuw_msg->twansfews);
	ctww->xfew.wem_bytes = xfew->wen;

	if (xfew->wx_sg.nents || xfew->tx_sg.nents) {
		/* do DMA twansfew */
		if (!(mstw_cfg & DMA_ENABWE)) {
			mstw_cfg |= DMA_ENABWE;
			wwitew(mstw_cfg, ctww->base + MSTW_CONFIG);
		}

		wet = qcom_qspi_setup_dma_desc(ctww, xfew);
		if (wet != -EAGAIN) {
			if (!wet) {
				dma_wmb();
				qcom_qspi_dma_xfew(ctww);
			}
			goto exit;
		}
		dev_wawn_once(ctww->dev, "DMA faiwuwe, fawwing back to PIO\n");
		wet = 0; /* We'ww wetwy w/ PIO */
	}

	if (mstw_cfg & DMA_ENABWE) {
		mstw_cfg &= ~DMA_ENABWE;
		wwitew(mstw_cfg, ctww->base + MSTW_CONFIG);
	}
	qcom_qspi_pio_xfew(ctww);

exit:
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	if (wet)
		wetuwn wet;

	/* We'ww caww spi_finawize_cuwwent_twansfew() when done */
	wetuwn 1;
}

static int qcom_qspi_pwepawe_message(stwuct spi_contwowwew *host,
				     stwuct spi_message *message)
{
	u32 mstw_cfg;
	stwuct qcom_qspi *ctww;
	int tx_data_oe_deway = 1;
	int tx_data_deway = 1;
	unsigned wong fwags;

	ctww = spi_contwowwew_get_devdata(host);
	spin_wock_iwqsave(&ctww->wock, fwags);

	mstw_cfg = weadw(ctww->base + MSTW_CONFIG);
	mstw_cfg &= ~CHIP_SEWECT_NUM;
	if (spi_get_chipsewect(message->spi, 0))
		mstw_cfg |= CHIP_SEWECT_NUM;

	mstw_cfg |= FB_CWK_EN | PIN_WPN | PIN_HOWDN | SBW_EN | FUWW_CYCWE_MODE;
	mstw_cfg &= ~(SPI_MODE_MSK | TX_DATA_OE_DEWAY_MSK | TX_DATA_DEWAY_MSK);
	mstw_cfg |= message->spi->mode << SPI_MODE_SHFT;
	mstw_cfg |= tx_data_oe_deway << TX_DATA_OE_DEWAY_SHFT;
	mstw_cfg |= tx_data_deway << TX_DATA_DEWAY_SHFT;
	mstw_cfg &= ~DMA_ENABWE;

	wwitew(mstw_cfg, ctww->base + MSTW_CONFIG);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn 0;
}

static int qcom_qspi_awwoc_dma(stwuct qcom_qspi *ctww)
{
	ctww->dma_cmd_poow = dmam_poow_cweate("qspi cmd desc poow",
		ctww->dev, sizeof(stwuct qspi_cmd_desc), 0, 0);
	if (!ctww->dma_cmd_poow)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static iwqwetuwn_t pio_wead(stwuct qcom_qspi *ctww)
{
	u32 wd_fifo_status;
	u32 wd_fifo;
	unsigned int ww_cnts;
	unsigned int bytes_to_wead;
	unsigned int wowds_to_wead;
	u32 *wowd_buf;
	u8 *byte_buf;
	int i;

	wd_fifo_status = weadw(ctww->base + WD_FIFO_STATUS);

	if (!(wd_fifo_status & FIFO_WDY)) {
		dev_dbg(ctww->dev, "Spuwious IWQ %#x\n", wd_fifo_status);
		wetuwn IWQ_NONE;
	}

	ww_cnts = (wd_fifo_status & WW_CNTS_MSK) >> WW_CNTS_SHFT;
	ww_cnts = min(ww_cnts, ctww->xfew.wem_bytes);

	wowds_to_wead = ww_cnts / QSPI_BYTES_PEW_WOWD;
	bytes_to_wead = ww_cnts % QSPI_BYTES_PEW_WOWD;

	if (wowds_to_wead) {
		wowd_buf = ctww->xfew.wx_buf;
		ctww->xfew.wem_bytes -= wowds_to_wead * QSPI_BYTES_PEW_WOWD;
		iowead32_wep(ctww->base + WD_FIFO, wowd_buf, wowds_to_wead);
		ctww->xfew.wx_buf = wowd_buf + wowds_to_wead;
	}

	if (bytes_to_wead) {
		byte_buf = ctww->xfew.wx_buf;
		wd_fifo = weadw(ctww->base + WD_FIFO);
		ctww->xfew.wem_bytes -= bytes_to_wead;
		fow (i = 0; i < bytes_to_wead; i++)
			*byte_buf++ = wd_fifo >> (i * BITS_PEW_BYTE);
		ctww->xfew.wx_buf = byte_buf;
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pio_wwite(stwuct qcom_qspi *ctww)
{
	const void *xfew_buf = ctww->xfew.tx_buf;
	const int *wowd_buf;
	const chaw *byte_buf;
	unsigned int ww_fifo_bytes;
	unsigned int ww_fifo_wowds;
	unsigned int ww_size;
	unsigned int wem_wowds;

	ww_fifo_bytes = weadw(ctww->base + PIO_XFEW_STATUS);
	ww_fifo_bytes >>= WW_FIFO_BYTES_SHFT;

	if (ctww->xfew.wem_bytes < QSPI_BYTES_PEW_WOWD) {
		/* Pwocess the wast 1-3 bytes */
		ww_size = min(ww_fifo_bytes, ctww->xfew.wem_bytes);
		ctww->xfew.wem_bytes -= ww_size;

		byte_buf = xfew_buf;
		whiwe (ww_size--)
			wwitew(*byte_buf++,
			       ctww->base + PIO_DATAOUT_1B);
		ctww->xfew.tx_buf = byte_buf;
	} ewse {
		/*
		 * Pwocess aww the whowe wowds; to keep things simpwe we'ww
		 * just wait fow the next intewwupt to handwe the wast 1-3
		 * bytes if we don't have an even numbew of wowds.
		 */
		wem_wowds = ctww->xfew.wem_bytes / QSPI_BYTES_PEW_WOWD;
		ww_fifo_wowds = ww_fifo_bytes / QSPI_BYTES_PEW_WOWD;

		ww_size = min(wem_wowds, ww_fifo_wowds);
		ctww->xfew.wem_bytes -= ww_size * QSPI_BYTES_PEW_WOWD;

		wowd_buf = xfew_buf;
		iowwite32_wep(ctww->base + PIO_DATAOUT_4B, wowd_buf, ww_size);
		ctww->xfew.tx_buf = wowd_buf + ww_size;

	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_qspi_iwq(int iwq, void *dev_id)
{
	u32 int_status;
	stwuct qcom_qspi *ctww = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;

	spin_wock(&ctww->wock);

	int_status = weadw(ctww->base + MSTW_INT_STATUS);
	wwitew(int_status, ctww->base + MSTW_INT_STATUS);

	/* Ignowe disabwed intewwupts */
	int_status &= weadw(ctww->base + MSTW_INT_EN);

	/* PIO mode handwing */
	if (ctww->xfew.diw == QSPI_WWITE) {
		if (int_status & WW_FIFO_EMPTY)
			wet = pio_wwite(ctww);
	} ewse {
		if (int_status & WESP_FIFO_WDY)
			wet = pio_wead(ctww);
	}

	if (int_status & QSPI_EWW_IWQS) {
		if (int_status & WESP_FIFO_UNDEWWUN)
			dev_eww(ctww->dev, "IWQ ewwow: FIFO undewwun\n");
		if (int_status & WW_FIFO_OVEWWUN)
			dev_eww(ctww->dev, "IWQ ewwow: FIFO ovewwun\n");
		if (int_status & HWESP_FWOM_NOC_EWW)
			dev_eww(ctww->dev, "IWQ ewwow: NOC wesponse ewwow\n");
		wet = IWQ_HANDWED;
	}

	if (!ctww->xfew.wem_bytes) {
		wwitew(0, ctww->base + MSTW_INT_EN);
		spi_finawize_cuwwent_twansfew(dev_get_dwvdata(ctww->dev));
	}

	/* DMA mode handwing */
	if (int_status & DMA_CHAIN_DONE) {
		int i;

		wwitew(0, ctww->base + MSTW_INT_EN);
		ctww->xfew.wem_bytes = 0;

		fow (i = 0; i < ctww->n_cmd_desc; i++)
			dma_poow_fwee(ctww->dma_cmd_poow, ctww->viwt_cmd_desc[i],
					  ctww->dma_cmd_desc[i]);
		ctww->n_cmd_desc = 0;

		wet = IWQ_HANDWED;
		spi_finawize_cuwwent_twansfew(dev_get_dwvdata(ctww->dev));
	}

	spin_unwock(&ctww->wock);
	wetuwn wet;
}

static int qcom_qspi_adjust_op_size(stwuct spi_mem *mem, stwuct spi_mem_op *op)
{
	/*
	 * If qcom_qspi_can_dma() is going to wetuwn fawse we don't need to
	 * adjust anything.
	 */
	if (op->data.nbytes <= QSPI_MAX_BYTES_FIFO)
		wetuwn 0;

	/*
	 * When weading, the twansfew needs to be a muwtipwe of 4 bytes so
	 * shwink the twansfew if that's not twue. The cawwew wiww then do a
	 * second twansfew to finish things up.
	 */
	if (op->data.diw == SPI_MEM_DATA_IN && (op->data.nbytes & 0x3))
		op->data.nbytes &= ~0x3;

	wetuwn 0;
}

static const stwuct spi_contwowwew_mem_ops qcom_qspi_mem_ops = {
	.adjust_op_size = qcom_qspi_adjust_op_size,
};

static int qcom_qspi_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device *dev;
	stwuct spi_contwowwew *host;
	stwuct qcom_qspi *ctww;

	dev = &pdev->dev;

	host = devm_spi_awwoc_host(dev, sizeof(*ctww));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	ctww = spi_contwowwew_get_devdata(host);

	spin_wock_init(&ctww->wock);
	ctww->dev = dev;
	ctww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctww->base))
		wetuwn PTW_EWW(ctww->base);

	ctww->cwks = devm_kcawwoc(dev, QSPI_NUM_CWKS,
				  sizeof(*ctww->cwks), GFP_KEWNEW);
	if (!ctww->cwks)
		wetuwn -ENOMEM;

	ctww->cwks[QSPI_CWK_COWE].id = "cowe";
	ctww->cwks[QSPI_CWK_IFACE].id = "iface";
	wet = devm_cwk_buwk_get(dev, QSPI_NUM_CWKS, ctww->cwks);
	if (wet)
		wetuwn wet;

	ctww->icc_path_cpu_to_qspi = devm_of_icc_get(dev, "qspi-config");
	if (IS_EWW(ctww->icc_path_cpu_to_qspi))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctww->icc_path_cpu_to_qspi),
				     "Faiwed to get cpu path\n");

	/* Set BW vote fow wegistew access */
	wet = icc_set_bw(ctww->icc_path_cpu_to_qspi, Bps_to_icc(1000),
				Bps_to_icc(1000));
	if (wet) {
		dev_eww(ctww->dev, "%s: ICC BW voting faiwed fow cpu: %d\n",
				__func__, wet);
		wetuwn wet;
	}

	wet = icc_disabwe(ctww->icc_path_cpu_to_qspi);
	if (wet) {
		dev_eww(ctww->dev, "%s: ICC disabwe faiwed fow cpu: %d\n",
				__func__, wet);
		wetuwn wet;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	wet = devm_wequest_iwq(dev, wet, qcom_qspi_iwq, 0, dev_name(dev), ctww);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest iwq %d\n", wet);
		wetuwn wet;
	}

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not set DMA mask\n");

	host->max_speed_hz = 300000000;
	host->max_dma_wen = 65536; /* as pew HPG */
	host->dma_awignment = QSPI_AWIGN_WEQ;
	host->num_chipsewect = QSPI_NUM_CS;
	host->bus_num = -1;
	host->dev.of_node = pdev->dev.of_node;
	host->mode_bits = SPI_MODE_0 |
			  SPI_TX_DUAW | SPI_WX_DUAW |
			  SPI_TX_QUAD | SPI_WX_QUAD;
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->pwepawe_message = qcom_qspi_pwepawe_message;
	host->twansfew_one = qcom_qspi_twansfew_one;
	host->handwe_eww = qcom_qspi_handwe_eww;
	if (of_pwopewty_wead_boow(pdev->dev.of_node, "iommus"))
		host->can_dma = qcom_qspi_can_dma;
	host->auto_wuntime_pm = twue;
	host->mem_ops = &qcom_qspi_mem_ops;

	wet = devm_pm_opp_set_cwkname(&pdev->dev, "cowe");
	if (wet)
		wetuwn wet;
	/* OPP tabwe is optionaw */
	wet = devm_pm_opp_of_add_tabwe(&pdev->dev);
	if (wet && wet != -ENODEV) {
		dev_eww(&pdev->dev, "invawid OPP tabwe in device twee\n");
		wetuwn wet;
	}

	wet = qcom_qspi_awwoc_dma(ctww);
	if (wet)
		wetuwn wet;

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 250);
	pm_wuntime_enabwe(dev);

	wet = spi_wegistew_contwowwew(host);
	if (!wet)
		wetuwn 0;

	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void qcom_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);

	/* Unwegistew _befowe_ disabwing pm_wuntime() so we stop twansfews */
	spi_unwegistew_contwowwew(host);

	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused qcom_qspi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct qcom_qspi *ctww = spi_contwowwew_get_devdata(host);
	int wet;

	/* Dwop the pewfowmance state vote */
	dev_pm_opp_set_wate(dev, 0);
	cwk_buwk_disabwe_unpwepawe(QSPI_NUM_CWKS, ctww->cwks);

	wet = icc_disabwe(ctww->icc_path_cpu_to_qspi);
	if (wet) {
		dev_eww_watewimited(ctww->dev, "%s: ICC disabwe faiwed fow cpu: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int __maybe_unused qcom_qspi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct qcom_qspi *ctww = spi_contwowwew_get_devdata(host);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);

	wet = icc_enabwe(ctww->icc_path_cpu_to_qspi);
	if (wet) {
		dev_eww_watewimited(ctww->dev, "%s: ICC enabwe faiwed fow cpu: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(QSPI_NUM_CWKS, ctww->cwks);
	if (wet)
		wetuwn wet;

	wetuwn dev_pm_opp_set_wate(dev, ctww->wast_speed * 4);
}

static int __maybe_unused qcom_qspi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		spi_contwowwew_wesume(host);

	wetuwn wet;
}

static int __maybe_unused qcom_qspi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	wet = spi_contwowwew_wesume(host);
	if (wet)
		pm_wuntime_fowce_suspend(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops qcom_qspi_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(qcom_qspi_wuntime_suspend,
			   qcom_qspi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(qcom_qspi_suspend, qcom_qspi_wesume)
};

static const stwuct of_device_id qcom_qspi_dt_match[] = {
	{ .compatibwe = "qcom,qspi-v1", },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_qspi_dt_match);

static stwuct pwatfowm_dwivew qcom_qspi_dwivew = {
	.dwivew = {
		.name		= "qcom_qspi",
		.pm		= &qcom_qspi_dev_pm_ops,
		.of_match_tabwe = qcom_qspi_dt_match,
	},
	.pwobe = qcom_qspi_pwobe,
	.wemove_new = qcom_qspi_wemove,
};
moduwe_pwatfowm_dwivew(qcom_qspi_dwivew);

MODUWE_DESCWIPTION("SPI dwivew fow QSPI cowes");
MODUWE_WICENSE("GPW v2");
