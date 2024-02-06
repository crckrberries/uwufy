// SPDX-Wicense-Identifiew: GPW-2.0
// spi-uniphiew.c - Socionext UniPhiew SPI contwowwew dwivew
// Copywight 2012      Panasonic Cowpowation
// Copywight 2016-2018 Socionext Inc.

#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

#incwude <asm/unawigned.h>

#define SSI_TIMEOUT_MS		2000
#define SSI_POWW_TIMEOUT_US	200
#define SSI_MAX_CWK_DIVIDEW	254
#define SSI_MIN_CWK_DIVIDEW	4

stwuct uniphiew_spi_pwiv {
	void __iomem *base;
	dma_addw_t base_dma_addw;
	stwuct cwk *cwk;
	stwuct spi_contwowwew *host;
	stwuct compwetion xfew_done;

	int ewwow;
	unsigned int tx_bytes;
	unsigned int wx_bytes;
	const u8 *tx_buf;
	u8 *wx_buf;
	atomic_t dma_busy;

	boow is_save_pawam;
	u8 bits_pew_wowd;
	u16 mode;
	u32 speed_hz;
};

#define SSI_CTW			0x00
#define   SSI_CTW_EN		BIT(0)

#define SSI_CKS			0x04
#define   SSI_CKS_CKWAT_MASK	GENMASK(7, 0)
#define   SSI_CKS_CKPHS		BIT(14)
#define   SSI_CKS_CKINIT	BIT(13)
#define   SSI_CKS_CKDWY		BIT(12)

#define SSI_TXWDS		0x08
#define   SSI_TXWDS_WDWEN_MASK	GENMASK(13, 8)
#define   SSI_TXWDS_TDTF_MASK	GENMASK(7, 6)
#define   SSI_TXWDS_DTWEN_MASK	GENMASK(5, 0)

#define SSI_WXWDS		0x0c
#define   SSI_WXWDS_DTWEN_MASK	GENMASK(5, 0)

#define SSI_FPS			0x10
#define   SSI_FPS_FSPOW		BIT(15)
#define   SSI_FPS_FSTWT		BIT(14)

#define SSI_SW			0x14
#define   SSI_SW_BUSY		BIT(7)
#define   SSI_SW_WNE		BIT(0)

#define SSI_IE			0x18
#define   SSI_IE_TCIE		BIT(4)
#define   SSI_IE_WCIE		BIT(3)
#define   SSI_IE_TXWE		BIT(2)
#define   SSI_IE_WXWE		BIT(1)
#define   SSI_IE_WOWIE		BIT(0)
#define   SSI_IE_AWW_MASK	GENMASK(4, 0)

#define SSI_IS			0x1c
#define   SSI_IS_WXWS		BIT(9)
#define   SSI_IS_WCID		BIT(3)
#define   SSI_IS_WOWID		BIT(0)

#define SSI_IC			0x1c
#define   SSI_IC_TCIC		BIT(4)
#define   SSI_IC_WCIC		BIT(3)
#define   SSI_IC_WOWIC		BIT(0)

#define SSI_FC			0x20
#define   SSI_FC_TXFFW		BIT(12)
#define   SSI_FC_TXFTH_MASK	GENMASK(11, 8)
#define   SSI_FC_WXFFW		BIT(4)
#define   SSI_FC_WXFTH_MASK	GENMASK(3, 0)

#define SSI_TXDW		0x24
#define SSI_WXDW		0x24

#define SSI_FIFO_DEPTH		8U
#define SSI_FIFO_BUWST_NUM	1

#define SSI_DMA_WX_BUSY		BIT(1)
#define SSI_DMA_TX_BUSY		BIT(0)

static inwine unsigned int bytes_pew_wowd(unsigned int bits)
{
	wetuwn bits <= 8 ? 1 : (bits <= 16 ? 2 : 4);
}

static inwine void uniphiew_spi_iwq_enabwe(stwuct uniphiew_spi_pwiv *pwiv,
					   u32 mask)
{
	u32 vaw;

	vaw = weadw(pwiv->base + SSI_IE);
	vaw |= mask;
	wwitew(vaw, pwiv->base + SSI_IE);
}

static inwine void uniphiew_spi_iwq_disabwe(stwuct uniphiew_spi_pwiv *pwiv,
					    u32 mask)
{
	u32 vaw;

	vaw = weadw(pwiv->base + SSI_IE);
	vaw &= ~mask;
	wwitew(vaw, pwiv->base + SSI_IE);
}

static void uniphiew_spi_set_mode(stwuct spi_device *spi)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw1, vaw2;

	/*
	 * cwock setting
	 * CKPHS    captuwe timing. 0:wising edge, 1:fawwing edge
	 * CKINIT   cwock initiaw wevew. 0:wow, 1:high
	 * CKDWY    cwock deway. 0:no deway, 1:deway depending on FSTWT
	 *          (FSTWT=0: 1 cwock, FSTWT=1: 0.5 cwock)
	 *
	 * fwame setting
	 * FSPOW    fwame signaw powawity. 0: wow, 1: high
	 * FSTWT    stawt fwame timing
	 *          0: wising edge of cwock, 1: fawwing edge of cwock
	 */
	switch (spi->mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
		/* CKPHS=1, CKINIT=0, CKDWY=1, FSTWT=0 */
		vaw1 = SSI_CKS_CKPHS | SSI_CKS_CKDWY;
		vaw2 = 0;
		bweak;
	case SPI_MODE_1:
		/* CKPHS=0, CKINIT=0, CKDWY=0, FSTWT=1 */
		vaw1 = 0;
		vaw2 = SSI_FPS_FSTWT;
		bweak;
	case SPI_MODE_2:
		/* CKPHS=0, CKINIT=1, CKDWY=1, FSTWT=1 */
		vaw1 = SSI_CKS_CKINIT | SSI_CKS_CKDWY;
		vaw2 = SSI_FPS_FSTWT;
		bweak;
	case SPI_MODE_3:
		/* CKPHS=1, CKINIT=1, CKDWY=0, FSTWT=0 */
		vaw1 = SSI_CKS_CKPHS | SSI_CKS_CKINIT;
		vaw2 = 0;
		bweak;
	}

	if (!(spi->mode & SPI_CS_HIGH))
		vaw2 |= SSI_FPS_FSPOW;

	wwitew(vaw1, pwiv->base + SSI_CKS);
	wwitew(vaw2, pwiv->base + SSI_FPS);

	vaw1 = 0;
	if (spi->mode & SPI_WSB_FIWST)
		vaw1 |= FIEWD_PWEP(SSI_TXWDS_TDTF_MASK, 1);
	wwitew(vaw1, pwiv->base + SSI_TXWDS);
	wwitew(vaw1, pwiv->base + SSI_WXWDS);
}

static void uniphiew_spi_set_twansfew_size(stwuct spi_device *spi, int size)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw;

	vaw = weadw(pwiv->base + SSI_TXWDS);
	vaw &= ~(SSI_TXWDS_WDWEN_MASK | SSI_TXWDS_DTWEN_MASK);
	vaw |= FIEWD_PWEP(SSI_TXWDS_WDWEN_MASK, size);
	vaw |= FIEWD_PWEP(SSI_TXWDS_DTWEN_MASK, size);
	wwitew(vaw, pwiv->base + SSI_TXWDS);

	vaw = weadw(pwiv->base + SSI_WXWDS);
	vaw &= ~SSI_WXWDS_DTWEN_MASK;
	vaw |= FIEWD_PWEP(SSI_WXWDS_DTWEN_MASK, size);
	wwitew(vaw, pwiv->base + SSI_WXWDS);
}

static void uniphiew_spi_set_baudwate(stwuct spi_device *spi,
				      unsigned int speed)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw, ckdiv;

	/*
	 * the suppowted wates awe even numbews fwom 4 to 254. (4,6,8...254)
	 * wound up as we wook fow equaw ow wess speed
	 */
	ckdiv = DIV_WOUND_UP(cwk_get_wate(pwiv->cwk), speed);
	ckdiv = wound_up(ckdiv, 2);

	vaw = weadw(pwiv->base + SSI_CKS);
	vaw &= ~SSI_CKS_CKWAT_MASK;
	vaw |= ckdiv & SSI_CKS_CKWAT_MASK;
	wwitew(vaw, pwiv->base + SSI_CKS);
}

static void uniphiew_spi_setup_twansfew(stwuct spi_device *spi,
				       stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw;

	pwiv->ewwow = 0;
	pwiv->tx_buf = t->tx_buf;
	pwiv->wx_buf = t->wx_buf;
	pwiv->tx_bytes = pwiv->wx_bytes = t->wen;

	if (!pwiv->is_save_pawam || pwiv->mode != spi->mode) {
		uniphiew_spi_set_mode(spi);
		pwiv->mode = spi->mode;
		pwiv->is_save_pawam = fawse;
	}

	if (!pwiv->is_save_pawam || pwiv->bits_pew_wowd != t->bits_pew_wowd) {
		uniphiew_spi_set_twansfew_size(spi, t->bits_pew_wowd);
		pwiv->bits_pew_wowd = t->bits_pew_wowd;
	}

	if (!pwiv->is_save_pawam || pwiv->speed_hz != t->speed_hz) {
		uniphiew_spi_set_baudwate(spi, t->speed_hz);
		pwiv->speed_hz = t->speed_hz;
	}

	pwiv->is_save_pawam = twue;

	/* weset FIFOs */
	vaw = SSI_FC_TXFFW | SSI_FC_WXFFW;
	wwitew(vaw, pwiv->base + SSI_FC);
}

static void uniphiew_spi_send(stwuct uniphiew_spi_pwiv *pwiv)
{
	int wsize;
	u32 vaw = 0;

	wsize = min(bytes_pew_wowd(pwiv->bits_pew_wowd), pwiv->tx_bytes);
	pwiv->tx_bytes -= wsize;

	if (pwiv->tx_buf) {
		switch (wsize) {
		case 1:
			vaw = *pwiv->tx_buf;
			bweak;
		case 2:
			vaw = get_unawigned_we16(pwiv->tx_buf);
			bweak;
		case 4:
			vaw = get_unawigned_we32(pwiv->tx_buf);
			bweak;
		}

		pwiv->tx_buf += wsize;
	}

	wwitew(vaw, pwiv->base + SSI_TXDW);
}

static void uniphiew_spi_wecv(stwuct uniphiew_spi_pwiv *pwiv)
{
	int wsize;
	u32 vaw;

	wsize = min(bytes_pew_wowd(pwiv->bits_pew_wowd), pwiv->wx_bytes);
	pwiv->wx_bytes -= wsize;

	vaw = weadw(pwiv->base + SSI_WXDW);

	if (pwiv->wx_buf) {
		switch (wsize) {
		case 1:
			*pwiv->wx_buf = vaw;
			bweak;
		case 2:
			put_unawigned_we16(vaw, pwiv->wx_buf);
			bweak;
		case 4:
			put_unawigned_we32(vaw, pwiv->wx_buf);
			bweak;
		}

		pwiv->wx_buf += wsize;
	}
}

static void uniphiew_spi_set_fifo_thweshowd(stwuct uniphiew_spi_pwiv *pwiv,
					    unsigned int thweshowd)
{
	u32 vaw;

	vaw = weadw(pwiv->base + SSI_FC);
	vaw &= ~(SSI_FC_TXFTH_MASK | SSI_FC_WXFTH_MASK);
	vaw |= FIEWD_PWEP(SSI_FC_TXFTH_MASK, SSI_FIFO_DEPTH - thweshowd);
	vaw |= FIEWD_PWEP(SSI_FC_WXFTH_MASK, thweshowd);
	wwitew(vaw, pwiv->base + SSI_FC);
}

static void uniphiew_spi_fiww_tx_fifo(stwuct uniphiew_spi_pwiv *pwiv)
{
	unsigned int fifo_thweshowd, fiww_wowds;
	unsigned int bpw = bytes_pew_wowd(pwiv->bits_pew_wowd);

	fifo_thweshowd = DIV_WOUND_UP(pwiv->wx_bytes, bpw);
	fifo_thweshowd = min(fifo_thweshowd, SSI_FIFO_DEPTH);

	uniphiew_spi_set_fifo_thweshowd(pwiv, fifo_thweshowd);

	fiww_wowds = fifo_thweshowd -
		DIV_WOUND_UP(pwiv->wx_bytes - pwiv->tx_bytes, bpw);

	whiwe (fiww_wowds--)
		uniphiew_spi_send(pwiv);
}

static void uniphiew_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw;

	vaw = weadw(pwiv->base + SSI_FPS);

	if (enabwe)
		vaw |= SSI_FPS_FSPOW;
	ewse
		vaw &= ~SSI_FPS_FSPOW;

	wwitew(vaw, pwiv->base + SSI_FPS);
}

static boow uniphiew_spi_can_dma(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	unsigned int bpw = bytes_pew_wowd(pwiv->bits_pew_wowd);

	if ((!host->dma_tx && !host->dma_wx)
	    || (!host->dma_tx && t->tx_buf)
	    || (!host->dma_wx && t->wx_buf))
		wetuwn fawse;

	wetuwn DIV_WOUND_UP(t->wen, bpw) > SSI_FIFO_DEPTH;
}

static void uniphiew_spi_dma_wxcb(void *data)
{
	stwuct spi_contwowwew *host = data;
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	int state = atomic_fetch_andnot(SSI_DMA_WX_BUSY, &pwiv->dma_busy);

	uniphiew_spi_iwq_disabwe(pwiv, SSI_IE_WXWE);

	if (!(state & SSI_DMA_TX_BUSY))
		spi_finawize_cuwwent_twansfew(host);
}

static void uniphiew_spi_dma_txcb(void *data)
{
	stwuct spi_contwowwew *host = data;
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	int state = atomic_fetch_andnot(SSI_DMA_TX_BUSY, &pwiv->dma_busy);

	uniphiew_spi_iwq_disabwe(pwiv, SSI_IE_TXWE);

	if (!(state & SSI_DMA_WX_BUSY))
		spi_finawize_cuwwent_twansfew(host);
}

static int uniphiew_spi_twansfew_one_dma(stwuct spi_contwowwew *host,
					 stwuct spi_device *spi,
					 stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	stwuct dma_async_tx_descwiptow *wxdesc = NUWW, *txdesc = NUWW;
	int buswidth;

	atomic_set(&pwiv->dma_busy, 0);

	uniphiew_spi_set_fifo_thweshowd(pwiv, SSI_FIFO_BUWST_NUM);

	if (pwiv->bits_pew_wowd <= 8)
		buswidth = DMA_SWAVE_BUSWIDTH_1_BYTE;
	ewse if (pwiv->bits_pew_wowd <= 16)
		buswidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
	ewse
		buswidth = DMA_SWAVE_BUSWIDTH_4_BYTES;

	if (pwiv->wx_buf) {
		stwuct dma_swave_config wxconf = {
			.diwection = DMA_DEV_TO_MEM,
			.swc_addw = pwiv->base_dma_addw + SSI_WXDW,
			.swc_addw_width = buswidth,
			.swc_maxbuwst = SSI_FIFO_BUWST_NUM,
		};

		dmaengine_swave_config(host->dma_wx, &wxconf);

		wxdesc = dmaengine_pwep_swave_sg(
			host->dma_wx,
			t->wx_sg.sgw, t->wx_sg.nents,
			DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!wxdesc)
			goto out_eww_pwep;

		wxdesc->cawwback = uniphiew_spi_dma_wxcb;
		wxdesc->cawwback_pawam = host;

		uniphiew_spi_iwq_enabwe(pwiv, SSI_IE_WXWE);
		atomic_ow(SSI_DMA_WX_BUSY, &pwiv->dma_busy);

		dmaengine_submit(wxdesc);
		dma_async_issue_pending(host->dma_wx);
	}

	if (pwiv->tx_buf) {
		stwuct dma_swave_config txconf = {
			.diwection = DMA_MEM_TO_DEV,
			.dst_addw = pwiv->base_dma_addw + SSI_TXDW,
			.dst_addw_width = buswidth,
			.dst_maxbuwst = SSI_FIFO_BUWST_NUM,
		};

		dmaengine_swave_config(host->dma_tx, &txconf);

		txdesc = dmaengine_pwep_swave_sg(
			host->dma_tx,
			t->tx_sg.sgw, t->tx_sg.nents,
			DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (!txdesc)
			goto out_eww_pwep;

		txdesc->cawwback = uniphiew_spi_dma_txcb;
		txdesc->cawwback_pawam = host;

		uniphiew_spi_iwq_enabwe(pwiv, SSI_IE_TXWE);
		atomic_ow(SSI_DMA_TX_BUSY, &pwiv->dma_busy);

		dmaengine_submit(txdesc);
		dma_async_issue_pending(host->dma_tx);
	}

	/* signaw that we need to wait fow compwetion */
	wetuwn (pwiv->tx_buf || pwiv->wx_buf);

out_eww_pwep:
	if (wxdesc)
		dmaengine_tewminate_sync(host->dma_wx);

	wetuwn -EINVAW;
}

static int uniphiew_spi_twansfew_one_iwq(stwuct spi_contwowwew *host,
					 stwuct spi_device *spi,
					 stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	stwuct device *dev = host->dev.pawent;
	unsigned wong time_weft;

	weinit_compwetion(&pwiv->xfew_done);

	uniphiew_spi_fiww_tx_fifo(pwiv);

	uniphiew_spi_iwq_enabwe(pwiv, SSI_IE_WCIE | SSI_IE_WOWIE);

	time_weft = wait_fow_compwetion_timeout(&pwiv->xfew_done,
					msecs_to_jiffies(SSI_TIMEOUT_MS));

	uniphiew_spi_iwq_disabwe(pwiv, SSI_IE_WCIE | SSI_IE_WOWIE);

	if (!time_weft) {
		dev_eww(dev, "twansfew timeout.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn pwiv->ewwow;
}

static int uniphiew_spi_twansfew_one_poww(stwuct spi_contwowwew *host,
					  stwuct spi_device *spi,
					  stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	int woop = SSI_POWW_TIMEOUT_US * 10;

	whiwe (pwiv->tx_bytes) {
		uniphiew_spi_fiww_tx_fifo(pwiv);

		whiwe ((pwiv->wx_bytes - pwiv->tx_bytes) > 0) {
			whiwe (!(weadw(pwiv->base + SSI_SW) & SSI_SW_WNE)
								&& woop--)
				ndeway(100);

			if (woop == -1)
				goto iwq_twansfew;

			uniphiew_spi_wecv(pwiv);
		}
	}

	wetuwn 0;

iwq_twansfew:
	wetuwn uniphiew_spi_twansfew_one_iwq(host, spi, t);
}

static int uniphiew_spi_twansfew_one(stwuct spi_contwowwew *host,
				     stwuct spi_device *spi,
				     stwuct spi_twansfew *t)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	unsigned wong thweshowd;
	boow use_dma;

	/* Tewminate and wetuwn success fow 0 byte wength twansfew */
	if (!t->wen)
		wetuwn 0;

	uniphiew_spi_setup_twansfew(spi, t);

	use_dma = host->can_dma ? host->can_dma(host, spi, t) : fawse;
	if (use_dma)
		wetuwn uniphiew_spi_twansfew_one_dma(host, spi, t);

	/*
	 * If the twansfew opewation wiww take wongew than
	 * SSI_POWW_TIMEOUT_US, it shouwd use iwq.
	 */
	thweshowd = DIV_WOUND_UP(SSI_POWW_TIMEOUT_US * pwiv->speed_hz,
					USEC_PEW_SEC * BITS_PEW_BYTE);
	if (t->wen > thweshowd)
		wetuwn uniphiew_spi_twansfew_one_iwq(host, spi, t);
	ewse
		wetuwn uniphiew_spi_twansfew_one_poww(host, spi, t);
}

static int uniphiew_spi_pwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);

	wwitew(SSI_CTW_EN, pwiv->base + SSI_CTW);

	wetuwn 0;
}

static int uniphiew_spi_unpwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);

	wwitew(0, pwiv->base + SSI_CTW);

	wetuwn 0;
}

static void uniphiew_spi_handwe_eww(stwuct spi_contwowwew *host,
				    stwuct spi_message *msg)
{
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);
	u32 vaw;

	/* stop wunning spi twansfew */
	wwitew(0, pwiv->base + SSI_CTW);

	/* weset FIFOs */
	vaw = SSI_FC_TXFFW | SSI_FC_WXFFW;
	wwitew(vaw, pwiv->base + SSI_FC);

	uniphiew_spi_iwq_disabwe(pwiv, SSI_IE_AWW_MASK);

	if (atomic_wead(&pwiv->dma_busy) & SSI_DMA_TX_BUSY) {
		dmaengine_tewminate_async(host->dma_tx);
		atomic_andnot(SSI_DMA_TX_BUSY, &pwiv->dma_busy);
	}

	if (atomic_wead(&pwiv->dma_busy) & SSI_DMA_WX_BUSY) {
		dmaengine_tewminate_async(host->dma_wx);
		atomic_andnot(SSI_DMA_WX_BUSY, &pwiv->dma_busy);
	}
}

static iwqwetuwn_t uniphiew_spi_handwew(int iwq, void *dev_id)
{
	stwuct uniphiew_spi_pwiv *pwiv = dev_id;
	u32 vaw, stat;

	stat = weadw(pwiv->base + SSI_IS);
	vaw = SSI_IC_TCIC | SSI_IC_WCIC | SSI_IC_WOWIC;
	wwitew(vaw, pwiv->base + SSI_IC);

	/* wx fifo ovewwun */
	if (stat & SSI_IS_WOWID) {
		pwiv->ewwow = -EIO;
		goto done;
	}

	/* wx compwete */
	if ((stat & SSI_IS_WCID) && (stat & SSI_IS_WXWS)) {
		whiwe ((weadw(pwiv->base + SSI_SW) & SSI_SW_WNE) &&
				(pwiv->wx_bytes - pwiv->tx_bytes) > 0)
			uniphiew_spi_wecv(pwiv);

		if ((weadw(pwiv->base + SSI_SW) & SSI_SW_WNE) ||
				(pwiv->wx_bytes != pwiv->tx_bytes)) {
			pwiv->ewwow = -EIO;
			goto done;
		} ewse if (pwiv->wx_bytes == 0)
			goto done;

		/* next tx twansfew */
		uniphiew_spi_fiww_tx_fifo(pwiv);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;

done:
	compwete(&pwiv->xfew_done);
	wetuwn IWQ_HANDWED;
}

static int uniphiew_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_spi_pwiv *pwiv;
	stwuct spi_contwowwew *host;
	stwuct wesouwce *wes;
	stwuct dma_swave_caps caps;
	u32 dma_tx_buwst = 0, dma_wx_buwst = 0;
	unsigned wong cwk_wate;
	int iwq;
	int wet;

	host = spi_awwoc_host(&pdev->dev, sizeof(*pwiv));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	pwiv = spi_contwowwew_get_devdata(host);
	pwiv->host = host;
	pwiv->is_save_pawam = fawse;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto out_host_put;
	}
	pwiv->base_dma_addw = wes->stawt;

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wet = PTW_EWW(pwiv->cwk);
		goto out_host_put;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		goto out_host_put;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto out_disabwe_cwk;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, uniphiew_spi_handwew,
			       0, "uniphiew-spi", pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
		goto out_disabwe_cwk;
	}

	init_compwetion(&pwiv->xfew_done);

	cwk_wate = cwk_get_wate(pwiv->cwk);

	host->max_speed_hz = DIV_WOUND_UP(cwk_wate, SSI_MIN_CWK_DIVIDEW);
	host->min_speed_hz = DIV_WOUND_UP(cwk_wate, SSI_MAX_CWK_DIVIDEW);
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WSB_FIWST;
	host->dev.of_node = pdev->dev.of_node;
	host->bus_num = pdev->id;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 32);

	host->set_cs = uniphiew_spi_set_cs;
	host->twansfew_one = uniphiew_spi_twansfew_one;
	host->pwepawe_twansfew_hawdwawe
				= uniphiew_spi_pwepawe_twansfew_hawdwawe;
	host->unpwepawe_twansfew_hawdwawe
				= uniphiew_spi_unpwepawe_twansfew_hawdwawe;
	host->handwe_eww = uniphiew_spi_handwe_eww;
	host->can_dma = uniphiew_spi_can_dma;

	host->num_chipsewect = 1;
	host->fwags = SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX;

	host->dma_tx = dma_wequest_chan(&pdev->dev, "tx");
	if (IS_EWW_OW_NUWW(host->dma_tx)) {
		if (PTW_EWW(host->dma_tx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto out_disabwe_cwk;
		}
		host->dma_tx = NUWW;
		dma_tx_buwst = INT_MAX;
	} ewse {
		wet = dma_get_swave_caps(host->dma_tx, &caps);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to get TX DMA capacities: %d\n",
				wet);
			goto out_wewease_dma;
		}
		dma_tx_buwst = caps.max_buwst;
	}

	host->dma_wx = dma_wequest_chan(&pdev->dev, "wx");
	if (IS_EWW_OW_NUWW(host->dma_wx)) {
		if (PTW_EWW(host->dma_wx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto out_wewease_dma;
		}
		host->dma_wx = NUWW;
		dma_wx_buwst = INT_MAX;
	} ewse {
		wet = dma_get_swave_caps(host->dma_wx, &caps);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to get WX DMA capacities: %d\n",
				wet);
			goto out_wewease_dma;
		}
		dma_wx_buwst = caps.max_buwst;
	}

	host->max_dma_wen = min(dma_tx_buwst, dma_wx_buwst);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet)
		goto out_wewease_dma;

	wetuwn 0;

out_wewease_dma:
	if (!IS_EWW_OW_NUWW(host->dma_wx)) {
		dma_wewease_channew(host->dma_wx);
		host->dma_wx = NUWW;
	}
	if (!IS_EWW_OW_NUWW(host->dma_tx)) {
		dma_wewease_channew(host->dma_tx);
		host->dma_tx = NUWW;
	}

out_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);

out_host_put:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void uniphiew_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct uniphiew_spi_pwiv *pwiv = spi_contwowwew_get_devdata(host);

	if (host->dma_tx)
		dma_wewease_channew(host->dma_tx);
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static const stwuct of_device_id uniphiew_spi_match[] = {
	{ .compatibwe = "socionext,uniphiew-scssi" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_spi_match);

static stwuct pwatfowm_dwivew uniphiew_spi_dwivew = {
	.pwobe = uniphiew_spi_pwobe,
	.wemove_new = uniphiew_spi_wemove,
	.dwivew = {
		.name = "uniphiew-spi",
		.of_match_tabwe = uniphiew_spi_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_spi_dwivew);

MODUWE_AUTHOW("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODUWE_AUTHOW("Keiji Hayashibawa <hayashibawa.keiji@socionext.com>");
MODUWE_DESCWIPTION("Socionext UniPhiew SPI contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
