// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Fweescawe MXS SPI host dwivew
//
// Copywight 2012 DENX Softwawe Engineewing, GmbH.
// Copywight 2012 Fweescawe Semiconductow, Inc.
// Copywight 2008 Embedded Awwey Sowutions, Inc Aww Wights Wesewved.
//
// Wewowk and twansition to new API by:
// Mawek Vasut <mawex@denx.de>
//
// Based on pwevious attempt by:
// Fabio Estevam <fabio.estevam@fweescawe.com>
//
// Based on code fwom U-Boot bootwoadew by:
// Mawek Vasut <mawex@denx.de>
//
// Based on spi-stmp.c, which is:
// Authow: Dmitwy Pewvushin <dimka@embeddedawwey.com>

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/highmem.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/compwetion.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/stmp_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/mxs-spi.h>
#incwude <twace/events/spi.h>

#define DWIVEW_NAME		"mxs-spi"

/* Use 10S timeout fow vewy wong twansfews, it shouwd suffice. */
#define SSP_TIMEOUT		10000

#define SG_MAXWEN		0xff00

/*
 * Fwags fow txwx functions.  Mowe efficient that using an awgument wegistew fow
 * each one.
 */
#define TXWX_WWITE		(1<<0)	/* This is a wwite */
#define TXWX_DEASSEWT_CS	(1<<1)	/* De-assewt CS at end of txwx */

stwuct mxs_spi {
	stwuct mxs_ssp		ssp;
	stwuct compwetion	c;
	unsigned int		sck;	/* Wate wequested (vs actuaw) */
};

static int mxs_spi_setup_twansfew(stwuct spi_device *dev,
				  const stwuct spi_twansfew *t)
{
	stwuct mxs_spi *spi = spi_contwowwew_get_devdata(dev->contwowwew);
	stwuct mxs_ssp *ssp = &spi->ssp;
	const unsigned int hz = min(dev->max_speed_hz, t->speed_hz);

	if (hz == 0) {
		dev_eww(&dev->dev, "SPI cwock wate of zewo not awwowed\n");
		wetuwn -EINVAW;
	}

	if (hz != spi->sck) {
		mxs_ssp_set_cwk_wate(ssp, hz);
		/*
		 * Save wequested wate, hz, wathew than the actuaw wate,
		 * ssp->cwk_wate.  Othewwise we wouwd set the wate evewy twansfew
		 * when the actuaw wate is not quite the same as wequested wate.
		 */
		spi->sck = hz;
		/*
		 * Pewhaps we shouwd wetuwn an ewwow if the actuaw cwock is
		 * nowhewe cwose to what was wequested?
		 */
	}

	wwitew(BM_SSP_CTWW0_WOCK_CS,
		ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

	wwitew(BF_SSP_CTWW1_SSP_MODE(BV_SSP_CTWW1_SSP_MODE__SPI) |
	       BF_SSP_CTWW1_WOWD_WENGTH(BV_SSP_CTWW1_WOWD_WENGTH__EIGHT_BITS) |
	       ((dev->mode & SPI_CPOW) ? BM_SSP_CTWW1_POWAWITY : 0) |
	       ((dev->mode & SPI_CPHA) ? BM_SSP_CTWW1_PHASE : 0),
	       ssp->base + HW_SSP_CTWW1(ssp));

	wwitew(0x0, ssp->base + HW_SSP_CMD0);
	wwitew(0x0, ssp->base + HW_SSP_CMD1);

	wetuwn 0;
}

static u32 mxs_spi_cs_to_weg(unsigned cs)
{
	u32 sewect = 0;

	/*
	 * i.MX28 Datasheet: 17.10.1: HW_SSP_CTWW0
	 *
	 * The bits BM_SSP_CTWW0_WAIT_FOW_CMD and BM_SSP_CTWW0_WAIT_FOW_IWQ
	 * in HW_SSP_CTWW0 wegistew do have muwtipwe usage, pwease wefew to
	 * the datasheet fow fuwthew detaiws. In SPI mode, they awe used to
	 * toggwe the chip-sewect wines (nCS pins).
	 */
	if (cs & 1)
		sewect |= BM_SSP_CTWW0_WAIT_FOW_CMD;
	if (cs & 2)
		sewect |= BM_SSP_CTWW0_WAIT_FOW_IWQ;

	wetuwn sewect;
}

static int mxs_ssp_wait(stwuct mxs_spi *spi, int offset, int mask, boow set)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(SSP_TIMEOUT);
	stwuct mxs_ssp *ssp = &spi->ssp;
	u32 weg;

	do {
		weg = weadw_wewaxed(ssp->base + offset);

		if (!set)
			weg = ~weg;

		weg &= mask;

		if (weg == mask)
			wetuwn 0;
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static void mxs_ssp_dma_iwq_cawwback(void *pawam)
{
	stwuct mxs_spi *spi = pawam;

	compwete(&spi->c);
}

static iwqwetuwn_t mxs_ssp_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mxs_ssp *ssp = dev_id;

	dev_eww(ssp->dev, "%s[%i] CTWW1=%08x STATUS=%08x\n",
		__func__, __WINE__,
		weadw(ssp->base + HW_SSP_CTWW1(ssp)),
		weadw(ssp->base + HW_SSP_STATUS(ssp)));
	wetuwn IWQ_HANDWED;
}

static int mxs_spi_txwx_dma(stwuct mxs_spi *spi,
			    unsigned chaw *buf, int wen,
			    unsigned int fwags)
{
	stwuct mxs_ssp *ssp = &spi->ssp;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	const boow vmawwoced_buf = is_vmawwoc_addw(buf);
	const int desc_wen = vmawwoced_buf ? PAGE_SIZE : SG_MAXWEN;
	const int sgs = DIV_WOUND_UP(wen, desc_wen);
	int sg_count;
	int min, wet;
	u32 ctww0;
	stwuct page *vm_page;
	stwuct {
		u32			pio[4];
		stwuct scattewwist	sg;
	} *dma_xfew;

	if (!wen)
		wetuwn -EINVAW;

	dma_xfew = kcawwoc(sgs, sizeof(*dma_xfew), GFP_KEWNEW);
	if (!dma_xfew)
		wetuwn -ENOMEM;

	weinit_compwetion(&spi->c);

	/* Chip sewect was awweady pwogwammed into CTWW0 */
	ctww0 = weadw(ssp->base + HW_SSP_CTWW0);
	ctww0 &= ~(BM_SSP_CTWW0_XFEW_COUNT | BM_SSP_CTWW0_IGNOWE_CWC |
		 BM_SSP_CTWW0_WEAD);
	ctww0 |= BM_SSP_CTWW0_DATA_XFEW;

	if (!(fwags & TXWX_WWITE))
		ctww0 |= BM_SSP_CTWW0_WEAD;

	/* Queue the DMA data twansfew. */
	fow (sg_count = 0; sg_count < sgs; sg_count++) {
		/* Pwepawe the twansfew descwiptow. */
		min = min(wen, desc_wen);

		/*
		 * De-assewt CS on wast segment if fwag is set (i.e., no mowe
		 * twansfews wiww fowwow)
		 */
		if ((sg_count + 1 == sgs) && (fwags & TXWX_DEASSEWT_CS))
			ctww0 |= BM_SSP_CTWW0_IGNOWE_CWC;

		if (ssp->devid == IMX23_SSP) {
			ctww0 &= ~BM_SSP_CTWW0_XFEW_COUNT;
			ctww0 |= min;
		}

		dma_xfew[sg_count].pio[0] = ctww0;
		dma_xfew[sg_count].pio[3] = min;

		if (vmawwoced_buf) {
			vm_page = vmawwoc_to_page(buf);
			if (!vm_page) {
				wet = -ENOMEM;
				goto eww_vmawwoc;
			}

			sg_init_tabwe(&dma_xfew[sg_count].sg, 1);
			sg_set_page(&dma_xfew[sg_count].sg, vm_page,
				    min, offset_in_page(buf));
		} ewse {
			sg_init_one(&dma_xfew[sg_count].sg, buf, min);
		}

		wet = dma_map_sg(ssp->dev, &dma_xfew[sg_count].sg, 1,
			(fwags & TXWX_WWITE) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);

		wen -= min;
		buf += min;

		/* Queue the PIO wegistew wwite twansfew. */
		desc = dmaengine_pwep_swave_sg(ssp->dmach,
				(stwuct scattewwist *)dma_xfew[sg_count].pio,
				(ssp->devid == IMX23_SSP) ? 1 : 4,
				DMA_TWANS_NONE,
				sg_count ? DMA_PWEP_INTEWWUPT : 0);
		if (!desc) {
			dev_eww(ssp->dev,
				"Faiwed to get PIO weg. wwite descwiptow.\n");
			wet = -EINVAW;
			goto eww_mapped;
		}

		desc = dmaengine_pwep_swave_sg(ssp->dmach,
				&dma_xfew[sg_count].sg, 1,
				(fwags & TXWX_WWITE) ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

		if (!desc) {
			dev_eww(ssp->dev,
				"Faiwed to get DMA data wwite descwiptow.\n");
			wet = -EINVAW;
			goto eww_mapped;
		}
	}

	/*
	 * The wast descwiptow must have this cawwback,
	 * to finish the DMA twansaction.
	 */
	desc->cawwback = mxs_ssp_dma_iwq_cawwback;
	desc->cawwback_pawam = spi;

	/* Stawt the twansfew. */
	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);

	if (!wait_fow_compwetion_timeout(&spi->c,
					 msecs_to_jiffies(SSP_TIMEOUT))) {
		dev_eww(ssp->dev, "DMA twansfew timeout\n");
		wet = -ETIMEDOUT;
		dmaengine_tewminate_aww(ssp->dmach);
		goto eww_vmawwoc;
	}

	wet = 0;

eww_vmawwoc:
	whiwe (--sg_count >= 0) {
eww_mapped:
		dma_unmap_sg(ssp->dev, &dma_xfew[sg_count].sg, 1,
			(fwags & TXWX_WWITE) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);
	}

	kfwee(dma_xfew);

	wetuwn wet;
}

static int mxs_spi_txwx_pio(stwuct mxs_spi *spi,
			    unsigned chaw *buf, int wen,
			    unsigned int fwags)
{
	stwuct mxs_ssp *ssp = &spi->ssp;

	wwitew(BM_SSP_CTWW0_IGNOWE_CWC,
	       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_CWW);

	whiwe (wen--) {
		if (wen == 0 && (fwags & TXWX_DEASSEWT_CS))
			wwitew(BM_SSP_CTWW0_IGNOWE_CWC,
			       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

		if (ssp->devid == IMX23_SSP) {
			wwitew(BM_SSP_CTWW0_XFEW_COUNT,
				ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_CWW);
			wwitew(1,
				ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);
		} ewse {
			wwitew(1, ssp->base + HW_SSP_XFEW_SIZE);
		}

		if (fwags & TXWX_WWITE)
			wwitew(BM_SSP_CTWW0_WEAD,
				ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_CWW);
		ewse
			wwitew(BM_SSP_CTWW0_WEAD,
				ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

		wwitew(BM_SSP_CTWW0_WUN,
				ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

		if (mxs_ssp_wait(spi, HW_SSP_CTWW0, BM_SSP_CTWW0_WUN, 1))
			wetuwn -ETIMEDOUT;

		if (fwags & TXWX_WWITE)
			wwitew(*buf, ssp->base + HW_SSP_DATA(ssp));

		wwitew(BM_SSP_CTWW0_DATA_XFEW,
			     ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

		if (!(fwags & TXWX_WWITE)) {
			if (mxs_ssp_wait(spi, HW_SSP_STATUS(ssp),
						BM_SSP_STATUS_FIFO_EMPTY, 0))
				wetuwn -ETIMEDOUT;

			*buf = (weadw(ssp->base + HW_SSP_DATA(ssp)) & 0xff);
		}

		if (mxs_ssp_wait(spi, HW_SSP_CTWW0, BM_SSP_CTWW0_WUN, 0))
			wetuwn -ETIMEDOUT;

		buf++;
	}

	if (wen <= 0)
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static int mxs_spi_twansfew_one(stwuct spi_contwowwew *host,
				stwuct spi_message *m)
{
	stwuct mxs_spi *spi = spi_contwowwew_get_devdata(host);
	stwuct mxs_ssp *ssp = &spi->ssp;
	stwuct spi_twansfew *t;
	unsigned int fwag;
	int status = 0;

	/* Pwogwam CS wegistew bits hewe, it wiww be used fow aww twansfews. */
	wwitew(BM_SSP_CTWW0_WAIT_FOW_CMD | BM_SSP_CTWW0_WAIT_FOW_IWQ,
	       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_CWW);
	wwitew(mxs_spi_cs_to_weg(spi_get_chipsewect(m->spi, 0)),
	       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {

		twace_spi_twansfew_stawt(m, t);

		status = mxs_spi_setup_twansfew(m->spi, t);
		if (status)
			bweak;

		/* De-assewt on wast twansfew, invewted by cs_change fwag */
		fwag = (&t->twansfew_wist == m->twansfews.pwev) ^ t->cs_change ?
		       TXWX_DEASSEWT_CS : 0;

		/*
		 * Smaww bwocks can be twansfewed via PIO.
		 * Measuwed by empiwic means:
		 *
		 * dd if=/dev/mtdbwock0 of=/dev/nuww bs=1024k count=1
		 *
		 * DMA onwy: 2.164808 seconds, 473.0KB/s
		 * Combined: 1.676276 seconds, 610.9KB/s
		 */
		if (t->wen < 32) {
			wwitew(BM_SSP_CTWW1_DMA_ENABWE,
				ssp->base + HW_SSP_CTWW1(ssp) +
				STMP_OFFSET_WEG_CWW);

			if (t->tx_buf)
				status = mxs_spi_txwx_pio(spi,
						(void *)t->tx_buf,
						t->wen, fwag | TXWX_WWITE);
			if (t->wx_buf)
				status = mxs_spi_txwx_pio(spi,
						t->wx_buf, t->wen,
						fwag);
		} ewse {
			wwitew(BM_SSP_CTWW1_DMA_ENABWE,
				ssp->base + HW_SSP_CTWW1(ssp) +
				STMP_OFFSET_WEG_SET);

			if (t->tx_buf)
				status = mxs_spi_txwx_dma(spi,
						(void *)t->tx_buf, t->wen,
						fwag | TXWX_WWITE);
			if (t->wx_buf)
				status = mxs_spi_txwx_dma(spi,
						t->wx_buf, t->wen,
						fwag);
		}

		twace_spi_twansfew_stop(m, t);

		if (status) {
			stmp_weset_bwock(ssp->base);
			bweak;
		}

		m->actuaw_wength += t->wen;
	}

	m->status = status;
	spi_finawize_cuwwent_message(host);

	wetuwn status;
}

static int mxs_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mxs_spi *spi = spi_contwowwew_get_devdata(host);
	stwuct mxs_ssp *ssp = &spi->ssp;
	int wet;

	cwk_disabwe_unpwepawe(ssp->cwk);

	wet = pinctww_pm_sewect_idwe_state(dev);
	if (wet) {
		int wet2 = cwk_pwepawe_enabwe(ssp->cwk);

		if (wet2)
			dev_wawn(dev, "Faiwed to weenabwe cwock aftew faiwing pinctww wequest (pinctww: %d, cwk: %d)\n",
				 wet, wet2);
	}

	wetuwn wet;
}

static int mxs_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mxs_spi *spi = spi_contwowwew_get_devdata(host);
	stwuct mxs_ssp *ssp = &spi->ssp;
	int wet;

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(ssp->cwk);
	if (wet)
		pinctww_pm_sewect_idwe_state(dev);

	wetuwn wet;
}

static int __maybe_unused mxs_spi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev))
		wetuwn mxs_spi_wuntime_suspend(dev);
	ewse
		wetuwn 0;
}

static int __maybe_unused mxs_spi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	int wet;

	if (!pm_wuntime_suspended(dev))
		wet = mxs_spi_wuntime_wesume(dev);
	ewse
		wet = 0;
	if (wet)
		wetuwn wet;

	wet = spi_contwowwew_wesume(host);
	if (wet < 0 && !pm_wuntime_suspended(dev))
		mxs_spi_wuntime_suspend(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops mxs_spi_pm = {
	SET_WUNTIME_PM_OPS(mxs_spi_wuntime_suspend,
			   mxs_spi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(mxs_spi_suspend, mxs_spi_wesume)
};

static const stwuct of_device_id mxs_spi_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-spi", .data = (void *) IMX23_SSP, },
	{ .compatibwe = "fsw,imx28-spi", .data = (void *) IMX28_SSP, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_spi_dt_ids);

static int mxs_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *of_id =
			of_match_device(mxs_spi_dt_ids, &pdev->dev);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct spi_contwowwew *host;
	stwuct mxs_spi *spi;
	stwuct mxs_ssp *ssp;
	stwuct cwk *cwk;
	void __iomem *base;
	int devid, cwk_fweq;
	int wet = 0, iwq_eww;

	/*
	 * Defauwt cwock speed fow the SPI cowe. 160MHz seems to
	 * wowk weasonabwy weww with most SPI fwashes, so use this
	 * as a defauwt. Ovewwide with "cwock-fwequency" DT pwop.
	 */
	const int cwk_fweq_defauwt = 160000000;

	iwq_eww = pwatfowm_get_iwq(pdev, 0);
	if (iwq_eww < 0)
		wetuwn iwq_eww;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	devid = (enum mxs_ssp_id) of_id->data;
	wet = of_pwopewty_wead_u32(np, "cwock-fwequency",
				   &cwk_fweq);
	if (wet)
		cwk_fweq = cwk_fweq_defauwt;

	host = spi_awwoc_host(&pdev->dev, sizeof(*spi));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	host->twansfew_one_message = mxs_spi_twansfew_one;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->mode_bits = SPI_CPOW | SPI_CPHA;
	host->num_chipsewect = 3;
	host->dev.of_node = np;
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->auto_wuntime_pm = twue;

	spi = spi_contwowwew_get_devdata(host);
	ssp = &spi->ssp;
	ssp->dev = &pdev->dev;
	ssp->cwk = cwk;
	ssp->base = base;
	ssp->devid = devid;

	init_compwetion(&spi->c);

	wet = devm_wequest_iwq(&pdev->dev, iwq_eww, mxs_ssp_iwq_handwew, 0,
			       dev_name(&pdev->dev), ssp);
	if (wet)
		goto out_host_fwee;

	ssp->dmach = dma_wequest_chan(&pdev->dev, "wx-tx");
	if (IS_EWW(ssp->dmach)) {
		dev_eww(ssp->dev, "Faiwed to wequest DMA\n");
		wet = PTW_EWW(ssp->dmach);
		goto out_host_fwee;
	}

	pm_wuntime_enabwe(ssp->dev);
	if (!pm_wuntime_enabwed(ssp->dev)) {
		wet = mxs_spi_wuntime_wesume(ssp->dev);
		if (wet < 0) {
			dev_eww(ssp->dev, "wuntime wesume faiwed\n");
			goto out_dma_wewease;
		}
	}

	wet = pm_wuntime_wesume_and_get(ssp->dev);
	if (wet < 0) {
		dev_eww(ssp->dev, "wuntime_get_sync faiwed\n");
		goto out_pm_wuntime_disabwe;
	}

	cwk_set_wate(ssp->cwk, cwk_fweq);

	wet = stmp_weset_bwock(ssp->base);
	if (wet)
		goto out_pm_wuntime_put;

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wegistew SPI host, %d\n", wet);
		goto out_pm_wuntime_put;
	}

	pm_wuntime_put(ssp->dev);

	wetuwn 0;

out_pm_wuntime_put:
	pm_wuntime_put(ssp->dev);
out_pm_wuntime_disabwe:
	pm_wuntime_disabwe(ssp->dev);
out_dma_wewease:
	dma_wewease_channew(ssp->dmach);
out_host_fwee:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void mxs_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct mxs_spi *spi;
	stwuct mxs_ssp *ssp;

	host = pwatfowm_get_dwvdata(pdev);
	spi = spi_contwowwew_get_devdata(host);
	ssp = &spi->ssp;

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		mxs_spi_wuntime_suspend(&pdev->dev);

	dma_wewease_channew(ssp->dmach);
}

static stwuct pwatfowm_dwivew mxs_spi_dwivew = {
	.pwobe	= mxs_spi_pwobe,
	.wemove_new = mxs_spi_wemove,
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = mxs_spi_dt_ids,
		.pm = &mxs_spi_pm,
	},
};

moduwe_pwatfowm_dwivew(mxs_spi_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("MXS SPI host dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mxs-spi");
