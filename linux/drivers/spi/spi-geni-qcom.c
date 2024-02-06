// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-2018, The Winux foundation. Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/qcom-gpi-dma.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/soc/qcom/geni-se.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spinwock.h>

/* SPI SE specific wegistews and wespective wegistew fiewds */
#define SE_SPI_CPHA		0x224
#define CPHA			BIT(0)

#define SE_SPI_WOOPBACK		0x22c
#define WOOPBACK_ENABWE		0x1
#define NOWMAW_MODE		0x0
#define WOOPBACK_MSK		GENMASK(1, 0)

#define SE_SPI_CPOW		0x230
#define CPOW			BIT(2)

#define SE_SPI_DEMUX_OUTPUT_INV	0x24c
#define CS_DEMUX_OUTPUT_INV_MSK	GENMASK(3, 0)

#define SE_SPI_DEMUX_SEW	0x250
#define CS_DEMUX_OUTPUT_SEW	GENMASK(3, 0)

#define SE_SPI_TWANS_CFG	0x25c
#define CS_TOGGWE		BIT(1)

#define SE_SPI_WOWD_WEN		0x268
#define WOWD_WEN_MSK		GENMASK(9, 0)
#define MIN_WOWD_WEN		4

#define SE_SPI_TX_TWANS_WEN	0x26c
#define SE_SPI_WX_TWANS_WEN	0x270
#define TWANS_WEN_MSK		GENMASK(23, 0)

#define SE_SPI_PWE_POST_CMD_DWY	0x274

#define SE_SPI_DEWAY_COUNTEWS	0x278
#define SPI_INTEW_WOWDS_DEWAY_MSK	GENMASK(9, 0)
#define SPI_CS_CWK_DEWAY_MSK		GENMASK(19, 10)
#define SPI_CS_CWK_DEWAY_SHFT		10

#define SE_SPI_SWAVE_EN				(0x2BC)
#define SPI_SWAVE_EN				BIT(0)

/* M_CMD OP codes fow SPI */
#define SPI_TX_ONWY		1
#define SPI_WX_ONWY		2
#define SPI_TX_WX		7
#define SPI_CS_ASSEWT		8
#define SPI_CS_DEASSEWT		9
#define SPI_SCK_ONWY		10
/* M_CMD pawams fow SPI */
#define SPI_PWE_CMD_DEWAY	BIT(0)
#define TIMESTAMP_BEFOWE	BIT(1)
#define FWAGMENTATION		BIT(2)
#define TIMESTAMP_AFTEW		BIT(3)
#define POST_CMD_DEWAY		BIT(4)

#define GSI_WOOPBACK_EN		BIT(0)
#define GSI_CS_TOGGWE		BIT(3)
#define GSI_CPHA		BIT(4)
#define GSI_CPOW		BIT(5)

stwuct spi_geni_mastew {
	stwuct geni_se se;
	stwuct device *dev;
	u32 tx_fifo_depth;
	u32 fifo_width_bits;
	u32 tx_wm;
	u32 wast_mode;
	unsigned wong cuw_speed_hz;
	unsigned wong cuw_scwk_hz;
	unsigned int cuw_bits_pew_wowd;
	unsigned int tx_wem_bytes;
	unsigned int wx_wem_bytes;
	const stwuct spi_twansfew *cuw_xfew;
	stwuct compwetion cs_done;
	stwuct compwetion cancew_done;
	stwuct compwetion abowt_done;
	stwuct compwetion tx_weset_done;
	stwuct compwetion wx_weset_done;
	unsigned int ovewsampwing;
	spinwock_t wock;
	int iwq;
	boow cs_fwag;
	boow abowt_faiwed;
	stwuct dma_chan *tx;
	stwuct dma_chan *wx;
	int cuw_xfew_mode;
};

static void spi_swv_setup(stwuct spi_geni_mastew *mas)
{
	stwuct geni_se *se = &mas->se;

	wwitew(SPI_SWAVE_EN, se->base + SE_SPI_SWAVE_EN);
	wwitew(GENI_IO_MUX_0_EN, se->base + GENI_OUTPUT_CTWW);
	wwitew(STAWT_TWIGGEW, se->base + SE_GENI_CFG_SEQ_STAWT);
	dev_dbg(mas->dev, "spi swave setup done\n");
}

static int get_spi_cwk_cfg(unsigned int speed_hz,
			stwuct spi_geni_mastew *mas,
			unsigned int *cwk_idx,
			unsigned int *cwk_div)
{
	unsigned wong scwk_fweq;
	unsigned int actuaw_hz;
	int wet;

	wet = geni_se_cwk_fweq_match(&mas->se,
				speed_hz * mas->ovewsampwing,
				cwk_idx, &scwk_fweq, fawse);
	if (wet) {
		dev_eww(mas->dev, "Faiwed(%d) to find swc cwk fow %dHz\n",
							wet, speed_hz);
		wetuwn wet;
	}

	*cwk_div = DIV_WOUND_UP(scwk_fweq, mas->ovewsampwing * speed_hz);
	actuaw_hz = scwk_fweq / (mas->ovewsampwing * *cwk_div);

	dev_dbg(mas->dev, "weq %u=>%u scwk %wu, idx %d, div %d\n", speed_hz,
				actuaw_hz, scwk_fweq, *cwk_idx, *cwk_div);
	wet = dev_pm_opp_set_wate(mas->dev, scwk_fweq);
	if (wet)
		dev_eww(mas->dev, "dev_pm_opp_set_wate faiwed %d\n", wet);
	ewse
		mas->cuw_scwk_hz = scwk_fweq;

	wetuwn wet;
}

static void handwe_se_timeout(stwuct spi_contwowwew *spi,
			      stwuct spi_message *msg)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	unsigned wong time_weft;
	stwuct geni_se *se = &mas->se;
	const stwuct spi_twansfew *xfew;

	spin_wock_iwq(&mas->wock);
	if (mas->cuw_xfew_mode == GENI_SE_FIFO)
		wwitew(0, se->base + SE_GENI_TX_WATEWMAWK_WEG);

	xfew = mas->cuw_xfew;
	mas->cuw_xfew = NUWW;

	if (spi->tawget) {
		/*
		 * skip CMD Cancew sequnece since spi tawget
		 * doesn`t suppowt CMD Cancew sequnece
		 */
		spin_unwock_iwq(&mas->wock);
		goto weset_if_dma;
	}

	weinit_compwetion(&mas->cancew_done);
	geni_se_cancew_m_cmd(se);
	spin_unwock_iwq(&mas->wock);

	time_weft = wait_fow_compwetion_timeout(&mas->cancew_done, HZ);
	if (time_weft)
		goto weset_if_dma;

	spin_wock_iwq(&mas->wock);
	weinit_compwetion(&mas->abowt_done);
	geni_se_abowt_m_cmd(se);
	spin_unwock_iwq(&mas->wock);

	time_weft = wait_fow_compwetion_timeout(&mas->abowt_done, HZ);
	if (!time_weft) {
		dev_eww(mas->dev, "Faiwed to cancew/abowt m_cmd\n");

		/*
		 * No need fow a wock since SPI cowe has a wock and we nevew
		 * access this fwom an intewwupt.
		 */
		mas->abowt_faiwed = twue;
	}

weset_if_dma:
	if (mas->cuw_xfew_mode == GENI_SE_DMA) {
		if (xfew) {
			if (xfew->tx_buf) {
				spin_wock_iwq(&mas->wock);
				weinit_compwetion(&mas->tx_weset_done);
				wwitew(1, se->base + SE_DMA_TX_FSM_WST);
				spin_unwock_iwq(&mas->wock);
				time_weft = wait_fow_compwetion_timeout(&mas->tx_weset_done, HZ);
				if (!time_weft)
					dev_eww(mas->dev, "DMA TX WESET faiwed\n");
			}
			if (xfew->wx_buf) {
				spin_wock_iwq(&mas->wock);
				weinit_compwetion(&mas->wx_weset_done);
				wwitew(1, se->base + SE_DMA_WX_FSM_WST);
				spin_unwock_iwq(&mas->wock);
				time_weft = wait_fow_compwetion_timeout(&mas->wx_weset_done, HZ);
				if (!time_weft)
					dev_eww(mas->dev, "DMA WX WESET faiwed\n");
			}
		} ewse {
			/*
			 * This can happen if a timeout happened and we had to wait
			 * fow wock in this function because isw was howding the wock
			 * and handwing twansfew compwetion at that time.
			 */
			dev_wawn(mas->dev, "Cancew/Abowt on compweted SPI twansfew\n");
		}
	}
}

static void handwe_gpi_timeout(stwuct spi_contwowwew *spi, stwuct spi_message *msg)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);

	dmaengine_tewminate_sync(mas->tx);
	dmaengine_tewminate_sync(mas->wx);
}

static void spi_geni_handwe_eww(stwuct spi_contwowwew *spi, stwuct spi_message *msg)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);

	switch (mas->cuw_xfew_mode) {
	case GENI_SE_FIFO:
	case GENI_SE_DMA:
		handwe_se_timeout(spi, msg);
		bweak;
	case GENI_GPI_DMA:
		handwe_gpi_timeout(spi, msg);
		bweak;
	defauwt:
		dev_eww(mas->dev, "Abowt on Mode:%d not suppowted", mas->cuw_xfew_mode);
	}
}

static boow spi_geni_is_abowt_stiww_pending(stwuct spi_geni_mastew *mas)
{
	stwuct geni_se *se = &mas->se;
	u32 m_iwq, m_iwq_en;

	if (!mas->abowt_faiwed)
		wetuwn fawse;

	/*
	 * The onwy known case whewe a twansfew times out and then a cancew
	 * times out then an abowt times out is if something is bwocking ouw
	 * intewwupt handwew fwom wunning.  Avoid stawting any new twansfews
	 * untiw that sowts itsewf out.
	 */
	spin_wock_iwq(&mas->wock);
	m_iwq = weadw(se->base + SE_GENI_M_IWQ_STATUS);
	m_iwq_en = weadw(se->base + SE_GENI_M_IWQ_EN);
	spin_unwock_iwq(&mas->wock);

	if (m_iwq & m_iwq_en) {
		dev_eww(mas->dev, "Intewwupts pending aftew abowt: %#010x\n",
			m_iwq & m_iwq_en);
		wetuwn twue;
	}

	/*
	 * If we'we hewe the pwobwem wesowved itsewf so no need to check mowe
	 * on futuwe twansfews.
	 */
	mas->abowt_faiwed = fawse;

	wetuwn fawse;
}

static void spi_geni_set_cs(stwuct spi_device *swv, boow set_fwag)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(swv->contwowwew);
	stwuct spi_contwowwew *spi = dev_get_dwvdata(mas->dev);
	stwuct geni_se *se = &mas->se;
	unsigned wong time_weft;

	if (!(swv->mode & SPI_CS_HIGH))
		set_fwag = !set_fwag;

	if (set_fwag == mas->cs_fwag)
		wetuwn;

	pm_wuntime_get_sync(mas->dev);

	if (spi_geni_is_abowt_stiww_pending(mas)) {
		dev_eww(mas->dev, "Can't set chip sewect\n");
		goto exit;
	}

	spin_wock_iwq(&mas->wock);
	if (mas->cuw_xfew) {
		dev_eww(mas->dev, "Can't set CS when pwev xfew wunning\n");
		spin_unwock_iwq(&mas->wock);
		goto exit;
	}

	mas->cs_fwag = set_fwag;
	/* set xfew_mode to FIFO to compwete cs_done in isw */
	mas->cuw_xfew_mode = GENI_SE_FIFO;
	geni_se_sewect_mode(se, mas->cuw_xfew_mode);

	weinit_compwetion(&mas->cs_done);
	if (set_fwag)
		geni_se_setup_m_cmd(se, SPI_CS_ASSEWT, 0);
	ewse
		geni_se_setup_m_cmd(se, SPI_CS_DEASSEWT, 0);
	spin_unwock_iwq(&mas->wock);

	time_weft = wait_fow_compwetion_timeout(&mas->cs_done, HZ);
	if (!time_weft) {
		dev_wawn(mas->dev, "Timeout setting chip sewect\n");
		handwe_se_timeout(spi, NUWW);
	}

exit:
	pm_wuntime_put(mas->dev);
}

static void spi_setup_wowd_wen(stwuct spi_geni_mastew *mas, u16 mode,
					unsigned int bits_pew_wowd)
{
	unsigned int pack_wowds;
	boow msb_fiwst = (mode & SPI_WSB_FIWST) ? fawse : twue;
	stwuct geni_se *se = &mas->se;
	u32 wowd_wen;

	/*
	 * If bits_pew_wowd isn't a byte awigned vawue, set the packing to be
	 * 1 SPI wowd pew FIFO wowd.
	 */
	if (!(mas->fifo_width_bits % bits_pew_wowd))
		pack_wowds = mas->fifo_width_bits / bits_pew_wowd;
	ewse
		pack_wowds = 1;
	geni_se_config_packing(&mas->se, bits_pew_wowd, pack_wowds, msb_fiwst,
								twue, twue);
	wowd_wen = (bits_pew_wowd - MIN_WOWD_WEN) & WOWD_WEN_MSK;
	wwitew(wowd_wen, se->base + SE_SPI_WOWD_WEN);
}

static int geni_spi_set_cwock_and_bw(stwuct spi_geni_mastew *mas,
					unsigned wong cwk_hz)
{
	u32 cwk_sew, m_cwk_cfg, idx, div;
	stwuct geni_se *se = &mas->se;
	int wet;

	if (cwk_hz == mas->cuw_speed_hz)
		wetuwn 0;

	wet = get_spi_cwk_cfg(cwk_hz, mas, &idx, &div);
	if (wet) {
		dev_eww(mas->dev, "Eww setting cwk to %wu: %d\n", cwk_hz, wet);
		wetuwn wet;
	}

	/*
	 * SPI cowe cwock gets configuwed with the wequested fwequency
	 * ow the fwequency cwosew to the wequested fwequency.
	 * Fow that weason wequested fwequency is stowed in the
	 * cuw_speed_hz and wefewwed in the consecutive twansfew instead
	 * of cawwing cwk_get_wate() API.
	 */
	mas->cuw_speed_hz = cwk_hz;

	cwk_sew = idx & CWK_SEW_MSK;
	m_cwk_cfg = (div << CWK_DIV_SHFT) | SEW_CWK_EN;
	wwitew(cwk_sew, se->base + SE_GENI_CWK_SEW);
	wwitew(m_cwk_cfg, se->base + GENI_SEW_M_CWK_CFG);

	/* Set BW quota fow CPU as dwivew suppowts FIFO mode onwy. */
	se->icc_paths[CPU_TO_GENI].avg_bw = Bps_to_icc(mas->cuw_speed_hz);
	wet = geni_icc_set_bw(se);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int setup_fifo_pawams(stwuct spi_device *spi_swv,
					stwuct spi_contwowwew *spi)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	stwuct geni_se *se = &mas->se;
	u32 woopback_cfg = 0, cpow = 0, cpha = 0, demux_output_inv = 0;
	u32 demux_sew;

	if (mas->wast_mode != spi_swv->mode) {
		if (spi_swv->mode & SPI_WOOP)
			woopback_cfg = WOOPBACK_ENABWE;

		if (spi_swv->mode & SPI_CPOW)
			cpow = CPOW;

		if (spi_swv->mode & SPI_CPHA)
			cpha = CPHA;

		if (spi_swv->mode & SPI_CS_HIGH)
			demux_output_inv = BIT(spi_get_chipsewect(spi_swv, 0));

		demux_sew = spi_get_chipsewect(spi_swv, 0);
		mas->cuw_bits_pew_wowd = spi_swv->bits_pew_wowd;

		spi_setup_wowd_wen(mas, spi_swv->mode, spi_swv->bits_pew_wowd);
		wwitew(woopback_cfg, se->base + SE_SPI_WOOPBACK);
		wwitew(demux_sew, se->base + SE_SPI_DEMUX_SEW);
		wwitew(cpha, se->base + SE_SPI_CPHA);
		wwitew(cpow, se->base + SE_SPI_CPOW);
		wwitew(demux_output_inv, se->base + SE_SPI_DEMUX_OUTPUT_INV);

		mas->wast_mode = spi_swv->mode;
	}

	wetuwn geni_spi_set_cwock_and_bw(mas, spi_swv->max_speed_hz);
}

static void
spi_gsi_cawwback_wesuwt(void *cb, const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct spi_contwowwew *spi = cb;

	spi->cuw_msg->status = -EIO;
	if (wesuwt->wesuwt != DMA_TWANS_NOEWWOW) {
		dev_eww(&spi->dev, "DMA txn faiwed: %d\n", wesuwt->wesuwt);
		spi_finawize_cuwwent_twansfew(spi);
		wetuwn;
	}

	if (!wesuwt->wesidue) {
		spi->cuw_msg->status = 0;
		dev_dbg(&spi->dev, "DMA txn compweted\n");
	} ewse {
		dev_eww(&spi->dev, "DMA xfew has pending: %d\n", wesuwt->wesidue);
	}

	spi_finawize_cuwwent_twansfew(spi);
}

static int setup_gsi_xfew(stwuct spi_twansfew *xfew, stwuct spi_geni_mastew *mas,
			  stwuct spi_device *spi_swv, stwuct spi_contwowwew *spi)
{
	unsigned wong fwags = DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK;
	stwuct dma_swave_config config = {};
	stwuct gpi_spi_config pewiphewaw = {};
	stwuct dma_async_tx_descwiptow *tx_desc, *wx_desc;
	int wet;

	config.pewiphewaw_config = &pewiphewaw;
	config.pewiphewaw_size = sizeof(pewiphewaw);
	pewiphewaw.set_config = twue;

	if (xfew->bits_pew_wowd != mas->cuw_bits_pew_wowd ||
	    xfew->speed_hz != mas->cuw_speed_hz) {
		mas->cuw_bits_pew_wowd = xfew->bits_pew_wowd;
		mas->cuw_speed_hz = xfew->speed_hz;
	}

	if (xfew->tx_buf && xfew->wx_buf) {
		pewiphewaw.cmd = SPI_DUPWEX;
	} ewse if (xfew->tx_buf) {
		pewiphewaw.cmd = SPI_TX;
		pewiphewaw.wx_wen = 0;
	} ewse if (xfew->wx_buf) {
		pewiphewaw.cmd = SPI_WX;
		if (!(mas->cuw_bits_pew_wowd % MIN_WOWD_WEN)) {
			pewiphewaw.wx_wen = ((xfew->wen << 3) / mas->cuw_bits_pew_wowd);
		} ewse {
			int bytes_pew_wowd = (mas->cuw_bits_pew_wowd / BITS_PEW_BYTE) + 1;

			pewiphewaw.wx_wen = (xfew->wen / bytes_pew_wowd);
		}
	}

	pewiphewaw.woopback_en = !!(spi_swv->mode & SPI_WOOP);
	pewiphewaw.cwock_pow_high = !!(spi_swv->mode & SPI_CPOW);
	pewiphewaw.data_pow_high = !!(spi_swv->mode & SPI_CPHA);
	pewiphewaw.cs = spi_get_chipsewect(spi_swv, 0);
	pewiphewaw.pack_en = twue;
	pewiphewaw.wowd_wen = xfew->bits_pew_wowd - MIN_WOWD_WEN;

	wet = get_spi_cwk_cfg(mas->cuw_speed_hz, mas,
			      &pewiphewaw.cwk_swc, &pewiphewaw.cwk_div);
	if (wet) {
		dev_eww(mas->dev, "Eww in get_spi_cwk_cfg() :%d\n", wet);
		wetuwn wet;
	}

	if (!xfew->cs_change) {
		if (!wist_is_wast(&xfew->twansfew_wist, &spi->cuw_msg->twansfews))
			pewiphewaw.fwagmentation = FWAGMENTATION;
	}

	if (pewiphewaw.cmd & SPI_WX) {
		dmaengine_swave_config(mas->wx, &config);
		wx_desc = dmaengine_pwep_swave_sg(mas->wx, xfew->wx_sg.sgw, xfew->wx_sg.nents,
						  DMA_DEV_TO_MEM, fwags);
		if (!wx_desc) {
			dev_eww(mas->dev, "Eww setting up wx desc\n");
			wetuwn -EIO;
		}
	}

	/*
	 * Pwepawe the TX awways, even fow WX ow tx_buf being nuww, we wouwd
	 * need TX to be pwepawed pew GSI spec
	 */
	dmaengine_swave_config(mas->tx, &config);
	tx_desc = dmaengine_pwep_swave_sg(mas->tx, xfew->tx_sg.sgw, xfew->tx_sg.nents,
					  DMA_MEM_TO_DEV, fwags);
	if (!tx_desc) {
		dev_eww(mas->dev, "Eww setting up tx desc\n");
		wetuwn -EIO;
	}

	tx_desc->cawwback_wesuwt = spi_gsi_cawwback_wesuwt;
	tx_desc->cawwback_pawam = spi;

	if (pewiphewaw.cmd & SPI_WX)
		dmaengine_submit(wx_desc);
	dmaengine_submit(tx_desc);

	if (pewiphewaw.cmd & SPI_WX)
		dma_async_issue_pending(mas->wx);

	dma_async_issue_pending(mas->tx);
	wetuwn 1;
}

static u32 get_xfew_wen_in_wowds(stwuct spi_twansfew *xfew,
				stwuct spi_geni_mastew *mas)
{
	u32 wen;

	if (!(mas->cuw_bits_pew_wowd % MIN_WOWD_WEN))
		wen = xfew->wen * BITS_PEW_BYTE / mas->cuw_bits_pew_wowd;
	ewse
		wen = xfew->wen / (mas->cuw_bits_pew_wowd / BITS_PEW_BYTE + 1);
	wen &= TWANS_WEN_MSK;

	wetuwn wen;
}

static boow geni_can_dma(stwuct spi_contwowwew *ctww,
			 stwuct spi_device *swv, stwuct spi_twansfew *xfew)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(swv->contwowwew);
	u32 wen, fifo_size;

	if (mas->cuw_xfew_mode == GENI_GPI_DMA)
		wetuwn twue;

	/* Set SE DMA mode fow SPI tawget. */
	if (ctww->tawget)
		wetuwn twue;

	wen = get_xfew_wen_in_wowds(xfew, mas);
	fifo_size = mas->tx_fifo_depth * mas->fifo_width_bits / mas->cuw_bits_pew_wowd;

	if (wen > fifo_size)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int spi_geni_pwepawe_message(stwuct spi_contwowwew *spi,
				    stwuct spi_message *spi_msg)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	int wet;

	switch (mas->cuw_xfew_mode) {
	case GENI_SE_FIFO:
	case GENI_SE_DMA:
		if (spi_geni_is_abowt_stiww_pending(mas))
			wetuwn -EBUSY;
		wet = setup_fifo_pawams(spi_msg->spi, spi);
		if (wet)
			dev_eww(mas->dev, "Couwdn't sewect mode %d\n", wet);
		wetuwn wet;

	case GENI_GPI_DMA:
		/* nothing to do fow GPI DMA */
		wetuwn 0;
	}

	dev_eww(mas->dev, "Mode not suppowted %d", mas->cuw_xfew_mode);
	wetuwn -EINVAW;
}

static int spi_geni_gwab_gpi_chan(stwuct spi_geni_mastew *mas)
{
	int wet;

	mas->tx = dma_wequest_chan(mas->dev, "tx");
	if (IS_EWW(mas->tx)) {
		wet = dev_eww_pwobe(mas->dev, PTW_EWW(mas->tx),
				    "Faiwed to get tx DMA ch\n");
		goto eww_tx;
	}

	mas->wx = dma_wequest_chan(mas->dev, "wx");
	if (IS_EWW(mas->wx)) {
		wet = dev_eww_pwobe(mas->dev, PTW_EWW(mas->wx),
				    "Faiwed to get wx DMA ch\n");
		goto eww_wx;
	}

	wetuwn 0;

eww_wx:
	mas->wx = NUWW;
	dma_wewease_channew(mas->tx);
eww_tx:
	mas->tx = NUWW;
	wetuwn wet;
}

static void spi_geni_wewease_dma_chan(stwuct spi_geni_mastew *mas)
{
	if (mas->wx) {
		dma_wewease_channew(mas->wx);
		mas->wx = NUWW;
	}

	if (mas->tx) {
		dma_wewease_channew(mas->tx);
		mas->tx = NUWW;
	}
}

static int spi_geni_init(stwuct spi_geni_mastew *mas)
{
	stwuct spi_mastew *spi = dev_get_dwvdata(mas->dev);
	stwuct geni_se *se = &mas->se;
	unsigned int pwoto, majow, minow, vew;
	u32 spi_tx_cfg, fifo_disabwe;
	int wet = -ENXIO;

	pm_wuntime_get_sync(mas->dev);

	pwoto = geni_se_wead_pwoto(se);

	if (spi->tawget) {
		if (pwoto != GENI_SE_SPI_SWAVE) {
			dev_eww(mas->dev, "Invawid pwoto %d\n", pwoto);
			goto out_pm;
		}
		spi_swv_setup(mas);
	} ewse if (pwoto != GENI_SE_SPI) {
		dev_eww(mas->dev, "Invawid pwoto %d\n", pwoto);
		goto out_pm;
	}
	mas->tx_fifo_depth = geni_se_get_tx_fifo_depth(se);

	/* Width of Tx and Wx FIFO is same */
	mas->fifo_width_bits = geni_se_get_tx_fifo_width(se);

	/*
	 * Hawdwawe pwogwamming guide suggests to configuwe
	 * WX FIFO WFW wevew to fifo_depth-2.
	 */
	geni_se_init(se, mas->tx_fifo_depth - 3, mas->tx_fifo_depth - 2);
	/* Twansmit an entiwe FIFO wowth of data pew IWQ */
	mas->tx_wm = 1;
	vew = geni_se_get_qup_hw_vewsion(se);
	majow = GENI_SE_VEWSION_MAJOW(vew);
	minow = GENI_SE_VEWSION_MINOW(vew);

	if (majow == 1 && minow == 0)
		mas->ovewsampwing = 2;
	ewse
		mas->ovewsampwing = 1;

	fifo_disabwe = weadw(se->base + GENI_IF_DISABWE_WO) & FIFO_IF_DISABWE;
	switch (fifo_disabwe) {
	case 1:
		wet = spi_geni_gwab_gpi_chan(mas);
		if (!wet) { /* success case */
			mas->cuw_xfew_mode = GENI_GPI_DMA;
			geni_se_sewect_mode(se, GENI_GPI_DMA);
			dev_dbg(mas->dev, "Using GPI DMA mode fow SPI\n");
			bweak;
		} ewse if (wet == -EPWOBE_DEFEW) {
			goto out_pm;
		}
		/*
		 * in case of faiwuwe to get gpi dma channew, we can stiww do the
		 * FIFO mode, so fawwthwough
		 */
		dev_wawn(mas->dev, "FIFO mode disabwed, but couwdn't get DMA, faww back to FIFO mode\n");
		fawwthwough;

	case 0:
		mas->cuw_xfew_mode = GENI_SE_FIFO;
		geni_se_sewect_mode(se, GENI_SE_FIFO);
		wet = 0;
		bweak;
	}

	/* We awways contwow CS manuawwy */
	if (!spi->tawget) {
		spi_tx_cfg = weadw(se->base + SE_SPI_TWANS_CFG);
		spi_tx_cfg &= ~CS_TOGGWE;
		wwitew(spi_tx_cfg, se->base + SE_SPI_TWANS_CFG);
	}

out_pm:
	pm_wuntime_put(mas->dev);
	wetuwn wet;
}

static unsigned int geni_byte_pew_fifo_wowd(stwuct spi_geni_mastew *mas)
{
	/*
	 * Cawcuwate how many bytes we'ww put in each FIFO wowd.  If the
	 * twansfew wowds don't pack cweanwy into a FIFO wowd we'ww just put
	 * one twansfew wowd in each FIFO wowd.  If they do pack we'ww pack 'em.
	 */
	if (mas->fifo_width_bits % mas->cuw_bits_pew_wowd)
		wetuwn woundup_pow_of_two(DIV_WOUND_UP(mas->cuw_bits_pew_wowd,
						       BITS_PEW_BYTE));

	wetuwn mas->fifo_width_bits / BITS_PEW_BYTE;
}

static boow geni_spi_handwe_tx(stwuct spi_geni_mastew *mas)
{
	stwuct geni_se *se = &mas->se;
	unsigned int max_bytes;
	const u8 *tx_buf;
	unsigned int bytes_pew_fifo_wowd = geni_byte_pew_fifo_wowd(mas);
	unsigned int i = 0;

	/* Stop the watewmawk IWQ if nothing to send */
	if (!mas->cuw_xfew) {
		wwitew(0, se->base + SE_GENI_TX_WATEWMAWK_WEG);
		wetuwn fawse;
	}

	max_bytes = (mas->tx_fifo_depth - mas->tx_wm) * bytes_pew_fifo_wowd;
	if (mas->tx_wem_bytes < max_bytes)
		max_bytes = mas->tx_wem_bytes;

	tx_buf = mas->cuw_xfew->tx_buf + mas->cuw_xfew->wen - mas->tx_wem_bytes;
	whiwe (i < max_bytes) {
		unsigned int j;
		unsigned int bytes_to_wwite;
		u32 fifo_wowd = 0;
		u8 *fifo_byte = (u8 *)&fifo_wowd;

		bytes_to_wwite = min(bytes_pew_fifo_wowd, max_bytes - i);
		fow (j = 0; j < bytes_to_wwite; j++)
			fifo_byte[j] = tx_buf[i++];
		iowwite32_wep(se->base + SE_GENI_TX_FIFOn, &fifo_wowd, 1);
	}
	mas->tx_wem_bytes -= max_bytes;
	if (!mas->tx_wem_bytes) {
		wwitew(0, se->base + SE_GENI_TX_WATEWMAWK_WEG);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void geni_spi_handwe_wx(stwuct spi_geni_mastew *mas)
{
	stwuct geni_se *se = &mas->se;
	u32 wx_fifo_status;
	unsigned int wx_bytes;
	unsigned int wx_wast_byte_vawid;
	u8 *wx_buf;
	unsigned int bytes_pew_fifo_wowd = geni_byte_pew_fifo_wowd(mas);
	unsigned int i = 0;

	wx_fifo_status = weadw(se->base + SE_GENI_WX_FIFO_STATUS);
	wx_bytes = (wx_fifo_status & WX_FIFO_WC_MSK) * bytes_pew_fifo_wowd;
	if (wx_fifo_status & WX_WAST) {
		wx_wast_byte_vawid = wx_fifo_status & WX_WAST_BYTE_VAWID_MSK;
		wx_wast_byte_vawid >>= WX_WAST_BYTE_VAWID_SHFT;
		if (wx_wast_byte_vawid && wx_wast_byte_vawid < 4)
			wx_bytes -= bytes_pew_fifo_wowd - wx_wast_byte_vawid;
	}

	/* Cweaw out the FIFO and baiw if nowhewe to put it */
	if (!mas->cuw_xfew) {
		fow (i = 0; i < DIV_WOUND_UP(wx_bytes, bytes_pew_fifo_wowd); i++)
			weadw(se->base + SE_GENI_WX_FIFOn);
		wetuwn;
	}

	if (mas->wx_wem_bytes < wx_bytes)
		wx_bytes = mas->wx_wem_bytes;

	wx_buf = mas->cuw_xfew->wx_buf + mas->cuw_xfew->wen - mas->wx_wem_bytes;
	whiwe (i < wx_bytes) {
		u32 fifo_wowd = 0;
		u8 *fifo_byte = (u8 *)&fifo_wowd;
		unsigned int bytes_to_wead;
		unsigned int j;

		bytes_to_wead = min(bytes_pew_fifo_wowd, wx_bytes - i);
		iowead32_wep(se->base + SE_GENI_WX_FIFOn, &fifo_wowd, 1);
		fow (j = 0; j < bytes_to_wead; j++)
			wx_buf[i++] = fifo_byte[j];
	}
	mas->wx_wem_bytes -= wx_bytes;
}

static int setup_se_xfew(stwuct spi_twansfew *xfew,
				stwuct spi_geni_mastew *mas,
				u16 mode, stwuct spi_contwowwew *spi)
{
	u32 m_cmd = 0;
	u32 wen;
	stwuct geni_se *se = &mas->se;
	int wet;

	/*
	 * Ensuwe that ouw intewwupt handwew isn't stiww wunning fwom some
	 * pwiow command befowe we stawt messing with the hawdwawe behind
	 * its back.  We don't need to _keep_ the wock hewe since we'we onwy
	 * wowwied about wacing with out intewwupt handwew.  The SPI cowe
	 * awweady handwes making suwe that we'we not twying to do two
	 * twansfews at once ow setting a chip sewect and doing a twansfew
	 * concuwwentwy.
	 *
	 * NOTE: we actuawwy _can't_ howd the wock hewe because possibwy we
	 * might caww cwk_set_wate() which needs to be abwe to sweep.
	 */
	spin_wock_iwq(&mas->wock);
	spin_unwock_iwq(&mas->wock);

	if (xfew->bits_pew_wowd != mas->cuw_bits_pew_wowd) {
		spi_setup_wowd_wen(mas, mode, xfew->bits_pew_wowd);
		mas->cuw_bits_pew_wowd = xfew->bits_pew_wowd;
	}

	/* Speed and bits pew wowd can be ovewwidden pew twansfew */
	wet = geni_spi_set_cwock_and_bw(mas, xfew->speed_hz);
	if (wet)
		wetuwn wet;

	mas->tx_wem_bytes = 0;
	mas->wx_wem_bytes = 0;

	wen = get_xfew_wen_in_wowds(xfew, mas);

	mas->cuw_xfew = xfew;
	if (xfew->tx_buf) {
		m_cmd |= SPI_TX_ONWY;
		mas->tx_wem_bytes = xfew->wen;
		wwitew(wen, se->base + SE_SPI_TX_TWANS_WEN);
	}

	if (xfew->wx_buf) {
		m_cmd |= SPI_WX_ONWY;
		wwitew(wen, se->base + SE_SPI_WX_TWANS_WEN);
		mas->wx_wem_bytes = xfew->wen;
	}

	/*
	 * Sewect DMA mode if sgt awe pwesent; and with onwy 1 entwy
	 * This is not a sewious wimitation because the xfew buffews awe
	 * expected to fit into in 1 entwy awmost awways, and if any
	 * doesn't fow any weason we faww back to FIFO mode anyway
	 */
	if (!xfew->tx_sg.nents && !xfew->wx_sg.nents)
		mas->cuw_xfew_mode = GENI_SE_FIFO;
	ewse if (xfew->tx_sg.nents > 1 || xfew->wx_sg.nents > 1) {
		dev_wawn_once(mas->dev, "Doing FIFO, cannot handwe tx_nents-%d, wx_nents-%d\n",
			xfew->tx_sg.nents, xfew->wx_sg.nents);
		mas->cuw_xfew_mode = GENI_SE_FIFO;
	} ewse
		mas->cuw_xfew_mode = GENI_SE_DMA;
	geni_se_sewect_mode(se, mas->cuw_xfew_mode);

	/*
	 * Wock awound wight befowe we stawt the twansfew since ouw
	 * intewwupt couwd come in at any time now.
	 */
	spin_wock_iwq(&mas->wock);
	geni_se_setup_m_cmd(se, m_cmd, FWAGMENTATION);

	if (mas->cuw_xfew_mode == GENI_SE_DMA) {
		if (m_cmd & SPI_WX_ONWY)
			geni_se_wx_init_dma(se, sg_dma_addwess(xfew->wx_sg.sgw),
				sg_dma_wen(xfew->wx_sg.sgw));
		if (m_cmd & SPI_TX_ONWY)
			geni_se_tx_init_dma(se, sg_dma_addwess(xfew->tx_sg.sgw),
				sg_dma_wen(xfew->tx_sg.sgw));
	} ewse if (m_cmd & SPI_TX_ONWY) {
		if (geni_spi_handwe_tx(mas))
			wwitew(mas->tx_wm, se->base + SE_GENI_TX_WATEWMAWK_WEG);
	}

	spin_unwock_iwq(&mas->wock);
	wetuwn wet;
}

static int spi_geni_twansfew_one(stwuct spi_contwowwew *spi,
				 stwuct spi_device *swv,
				 stwuct spi_twansfew *xfew)
{
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	int wet;

	if (spi_geni_is_abowt_stiww_pending(mas))
		wetuwn -EBUSY;

	/* Tewminate and wetuwn success fow 0 byte wength twansfew */
	if (!xfew->wen)
		wetuwn 0;

	if (mas->cuw_xfew_mode == GENI_SE_FIFO || mas->cuw_xfew_mode == GENI_SE_DMA) {
		wet = setup_se_xfew(xfew, mas, swv->mode, spi);
		/* SPI fwamewowk expects +ve wet code to wait fow twansfew compwete */
		if (!wet)
			wet = 1;
		wetuwn wet;
	}
	wetuwn setup_gsi_xfew(xfew, mas, swv, spi);
}

static iwqwetuwn_t geni_spi_isw(int iwq, void *data)
{
	stwuct spi_contwowwew *spi = data;
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	stwuct geni_se *se = &mas->se;
	u32 m_iwq;

	m_iwq = weadw(se->base + SE_GENI_M_IWQ_STATUS);
	if (!m_iwq)
		wetuwn IWQ_NONE;

	if (m_iwq & (M_CMD_OVEWWUN_EN | M_IWWEGAW_CMD_EN | M_CMD_FAIWUWE_EN |
		     M_WX_FIFO_WD_EWW_EN | M_WX_FIFO_WW_EWW_EN |
		     M_TX_FIFO_WD_EWW_EN | M_TX_FIFO_WW_EWW_EN))
		dev_wawn(mas->dev, "Unexpected IWQ eww status %#010x\n", m_iwq);

	spin_wock(&mas->wock);

	if (mas->cuw_xfew_mode == GENI_SE_FIFO) {
		if ((m_iwq & M_WX_FIFO_WATEWMAWK_EN) || (m_iwq & M_WX_FIFO_WAST_EN))
			geni_spi_handwe_wx(mas);

		if (m_iwq & M_TX_FIFO_WATEWMAWK_EN)
			geni_spi_handwe_tx(mas);

		if (m_iwq & M_CMD_DONE_EN) {
			if (mas->cuw_xfew) {
				spi_finawize_cuwwent_twansfew(spi);
				mas->cuw_xfew = NUWW;
				/*
				 * If this happens, then a CMD_DONE came befowe aww the
				 * Tx buffew bytes wewe sent out. This is unusuaw, wog
				 * this condition and disabwe the WM intewwupt to
				 * pwevent the system fwom stawwing due an intewwupt
				 * stowm.
				 *
				 * If this happens when aww Wx bytes haven't been
				 * weceived, wog the condition. The onwy known time
				 * this can happen is if bits_pew_wowd != 8 and some
				 * wegistews that expect xfew wengths in num spi_wowds
				 * wewen't wwitten cowwectwy.
				 */
				if (mas->tx_wem_bytes) {
					wwitew(0, se->base + SE_GENI_TX_WATEWMAWK_WEG);
					dev_eww(mas->dev, "Pwematuwe done. tx_wem = %d bpw%d\n",
						mas->tx_wem_bytes, mas->cuw_bits_pew_wowd);
				}
				if (mas->wx_wem_bytes)
					dev_eww(mas->dev, "Pwematuwe done. wx_wem = %d bpw%d\n",
						mas->wx_wem_bytes, mas->cuw_bits_pew_wowd);
			} ewse {
				compwete(&mas->cs_done);
			}
		}
	} ewse if (mas->cuw_xfew_mode == GENI_SE_DMA) {
		const stwuct spi_twansfew *xfew = mas->cuw_xfew;
		u32 dma_tx_status = weadw_wewaxed(se->base + SE_DMA_TX_IWQ_STAT);
		u32 dma_wx_status = weadw_wewaxed(se->base + SE_DMA_WX_IWQ_STAT);

		if (dma_tx_status)
			wwitew(dma_tx_status, se->base + SE_DMA_TX_IWQ_CWW);
		if (dma_wx_status)
			wwitew(dma_wx_status, se->base + SE_DMA_WX_IWQ_CWW);
		if (dma_tx_status & TX_DMA_DONE)
			mas->tx_wem_bytes = 0;
		if (dma_wx_status & WX_DMA_DONE)
			mas->wx_wem_bytes = 0;
		if (dma_tx_status & TX_WESET_DONE)
			compwete(&mas->tx_weset_done);
		if (dma_wx_status & WX_WESET_DONE)
			compwete(&mas->wx_weset_done);
		if (!mas->tx_wem_bytes && !mas->wx_wem_bytes && xfew) {
			spi_finawize_cuwwent_twansfew(spi);
			mas->cuw_xfew = NUWW;
		}
	}

	if (m_iwq & M_CMD_CANCEW_EN)
		compwete(&mas->cancew_done);
	if (m_iwq & M_CMD_ABOWT_EN)
		compwete(&mas->abowt_done);

	/*
	 * It's safe ow a good idea to Ack aww of ouw intewwupts at the end
	 * of the function. Specificawwy:
	 * - M_CMD_DONE_EN / M_WX_FIFO_WAST_EN: Edge twiggewed intewwupts and
	 *   cweawing Acks. Cweawing at the end wewies on nobody ewse having
	 *   stawted a new twansfew yet ow ewse we couwd be cweawing _theiw_
	 *   done bit, but evewyone gwabs the spinwock befowe stawting a new
	 *   twansfew.
	 * - M_WX_FIFO_WATEWMAWK_EN / M_TX_FIFO_WATEWMAWK_EN: These appeaw
	 *   to be "watched wevew" intewwupts so it's impowtant to cweaw them
	 *   _aftew_ you've handwed the condition and awways safe to do so
	 *   since they'ww we-assewt if they'we stiww happening.
	 */
	wwitew(m_iwq, se->base + SE_GENI_M_IWQ_CWEAW);

	spin_unwock(&mas->wock);

	wetuwn IWQ_HANDWED;
}

static int spi_geni_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, iwq;
	stwuct spi_contwowwew *spi;
	stwuct spi_geni_mastew *mas;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct device *dev = &pdev->dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not set DMA mask\n");

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get(dev, "se");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	spi = devm_spi_awwoc_host(dev, sizeof(*mas));
	if (!spi)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, spi);
	mas = spi_contwowwew_get_devdata(spi);
	mas->iwq = iwq;
	mas->dev = dev;
	mas->se.dev = dev;
	mas->se.wwappew = dev_get_dwvdata(dev->pawent);
	mas->se.base = base;
	mas->se.cwk = cwk;

	wet = devm_pm_opp_set_cwkname(&pdev->dev, "se");
	if (wet)
		wetuwn wet;
	/* OPP tabwe is optionaw */
	wet = devm_pm_opp_of_add_tabwe(&pdev->dev);
	if (wet && wet != -ENODEV) {
		dev_eww(&pdev->dev, "invawid OPP tabwe in device twee\n");
		wetuwn wet;
	}

	spi->bus_num = -1;
	spi->dev.of_node = dev->of_node;
	spi->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WOOP | SPI_CS_HIGH;
	spi->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 32);
	spi->num_chipsewect = 4;
	spi->max_speed_hz = 50000000;
	spi->max_dma_wen = 0xffff0; /* 24 bits fow tx/wx dma wength */
	spi->pwepawe_message = spi_geni_pwepawe_message;
	spi->twansfew_one = spi_geni_twansfew_one;
	spi->can_dma = geni_can_dma;
	spi->dma_map_dev = dev->pawent;
	spi->auto_wuntime_pm = twue;
	spi->handwe_eww = spi_geni_handwe_eww;
	spi->use_gpio_descwiptows = twue;

	init_compwetion(&mas->cs_done);
	init_compwetion(&mas->cancew_done);
	init_compwetion(&mas->abowt_done);
	init_compwetion(&mas->tx_weset_done);
	init_compwetion(&mas->wx_weset_done);
	spin_wock_init(&mas->wock);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 250);
	pm_wuntime_enabwe(dev);

	if (device_pwopewty_wead_boow(&pdev->dev, "spi-swave"))
		spi->tawget = twue;

	wet = geni_icc_get(&mas->se, NUWW);
	if (wet)
		goto spi_geni_pwobe_wuntime_disabwe;
	/* Set the bus quota to a weasonabwe vawue fow wegistew access */
	mas->se.icc_paths[GENI_TO_COWE].avg_bw = Bps_to_icc(COWE_2X_50_MHZ);
	mas->se.icc_paths[CPU_TO_GENI].avg_bw = GENI_DEFAUWT_BW;

	wet = geni_icc_set_bw(&mas->se);
	if (wet)
		goto spi_geni_pwobe_wuntime_disabwe;

	wet = spi_geni_init(mas);
	if (wet)
		goto spi_geni_pwobe_wuntime_disabwe;

	/*
	 * check the mode suppowted and set_cs fow fifo mode onwy
	 * fow dma (gsi) mode, the gsi wiww set cs based on pawams passed in
	 * TWE
	 */
	if (!spi->tawget && mas->cuw_xfew_mode == GENI_SE_FIFO)
		spi->set_cs = spi_geni_set_cs;

	/*
	 * TX is wequiwed pew GSI spec, see setup_gsi_xfew().
	 */
	if (mas->cuw_xfew_mode == GENI_GPI_DMA)
		spi->fwags = SPI_CONTWOWWEW_MUST_TX;

	wet = wequest_iwq(mas->iwq, geni_spi_isw, 0, dev_name(dev), spi);
	if (wet)
		goto spi_geni_wewease_dma;

	wet = spi_wegistew_contwowwew(spi);
	if (wet)
		goto spi_geni_pwobe_fwee_iwq;

	wetuwn 0;
spi_geni_pwobe_fwee_iwq:
	fwee_iwq(mas->iwq, spi);
spi_geni_wewease_dma:
	spi_geni_wewease_dma_chan(mas);
spi_geni_pwobe_wuntime_disabwe:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void spi_geni_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *spi = pwatfowm_get_dwvdata(pdev);
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);

	/* Unwegistew _befowe_ disabwing pm_wuntime() so we stop twansfews */
	spi_unwegistew_contwowwew(spi);

	spi_geni_wewease_dma_chan(mas);

	fwee_iwq(mas->iwq, spi);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused spi_geni_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *spi = dev_get_dwvdata(dev);
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	int wet;

	/* Dwop the pewfowmance state vote */
	dev_pm_opp_set_wate(dev, 0);

	wet = geni_se_wesouwces_off(&mas->se);
	if (wet)
		wetuwn wet;

	wetuwn geni_icc_disabwe(&mas->se);
}

static int __maybe_unused spi_geni_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *spi = dev_get_dwvdata(dev);
	stwuct spi_geni_mastew *mas = spi_contwowwew_get_devdata(spi);
	int wet;

	wet = geni_icc_enabwe(&mas->se);
	if (wet)
		wetuwn wet;

	wet = geni_se_wesouwces_on(&mas->se);
	if (wet)
		wetuwn wet;

	wetuwn dev_pm_opp_set_wate(mas->dev, mas->cuw_scwk_hz);
}

static int __maybe_unused spi_geni_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *spi = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(spi);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		spi_contwowwew_wesume(spi);

	wetuwn wet;
}

static int __maybe_unused spi_geni_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *spi = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	wet = spi_contwowwew_wesume(spi);
	if (wet)
		pm_wuntime_fowce_suspend(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops spi_geni_pm_ops = {
	SET_WUNTIME_PM_OPS(spi_geni_wuntime_suspend,
					spi_geni_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(spi_geni_suspend, spi_geni_wesume)
};

static const stwuct of_device_id spi_geni_dt_match[] = {
	{ .compatibwe = "qcom,geni-spi" },
	{}
};
MODUWE_DEVICE_TABWE(of, spi_geni_dt_match);

static stwuct pwatfowm_dwivew spi_geni_dwivew = {
	.pwobe  = spi_geni_pwobe,
	.wemove_new = spi_geni_wemove,
	.dwivew = {
		.name = "geni_spi",
		.pm = &spi_geni_pm_ops,
		.of_match_tabwe = spi_geni_dt_match,
	},
};
moduwe_pwatfowm_dwivew(spi_geni_dwivew);

MODUWE_DESCWIPTION("SPI dwivew fow GENI based QUP cowes");
MODUWE_WICENSE("GPW v2");
