// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Authow: Addy Ke <addy.ke@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>

#define DWIVEW_NAME "wockchip-spi"

#define WOCKCHIP_SPI_CWW_BITS(weg, bits) \
		wwitew_wewaxed(weadw_wewaxed(weg) & ~(bits), weg)
#define WOCKCHIP_SPI_SET_BITS(weg, bits) \
		wwitew_wewaxed(weadw_wewaxed(weg) | (bits), weg)

/* SPI wegistew offsets */
#define WOCKCHIP_SPI_CTWWW0			0x0000
#define WOCKCHIP_SPI_CTWWW1			0x0004
#define WOCKCHIP_SPI_SSIENW			0x0008
#define WOCKCHIP_SPI_SEW			0x000c
#define WOCKCHIP_SPI_BAUDW			0x0010
#define WOCKCHIP_SPI_TXFTWW			0x0014
#define WOCKCHIP_SPI_WXFTWW			0x0018
#define WOCKCHIP_SPI_TXFWW			0x001c
#define WOCKCHIP_SPI_WXFWW			0x0020
#define WOCKCHIP_SPI_SW				0x0024
#define WOCKCHIP_SPI_IPW			0x0028
#define WOCKCHIP_SPI_IMW			0x002c
#define WOCKCHIP_SPI_ISW			0x0030
#define WOCKCHIP_SPI_WISW			0x0034
#define WOCKCHIP_SPI_ICW			0x0038
#define WOCKCHIP_SPI_DMACW			0x003c
#define WOCKCHIP_SPI_DMATDWW			0x0040
#define WOCKCHIP_SPI_DMAWDWW			0x0044
#define WOCKCHIP_SPI_VEWSION			0x0048
#define WOCKCHIP_SPI_TXDW			0x0400
#define WOCKCHIP_SPI_WXDW			0x0800

/* Bit fiewds in CTWWW0 */
#define CW0_DFS_OFFSET				0
#define CW0_DFS_4BIT				0x0
#define CW0_DFS_8BIT				0x1
#define CW0_DFS_16BIT				0x2

#define CW0_CFS_OFFSET				2

#define CW0_SCPH_OFFSET				6

#define CW0_SCPOW_OFFSET			7

#define CW0_CSM_OFFSET				8
#define CW0_CSM_KEEP				0x0
/* ss_n be high fow hawf scwk_out cycwes */
#define CW0_CSM_HAWF				0X1
/* ss_n be high fow one scwk_out cycwe */
#define CW0_CSM_ONE					0x2

/* ss_n to scwk_out deway */
#define CW0_SSD_OFFSET				10
/*
 * The pewiod between ss_n active and
 * scwk_out active is hawf scwk_out cycwes
 */
#define CW0_SSD_HAWF				0x0
/*
 * The pewiod between ss_n active and
 * scwk_out active is one scwk_out cycwe
 */
#define CW0_SSD_ONE					0x1

#define CW0_EM_OFFSET				11
#define CW0_EM_WITTWE				0x0
#define CW0_EM_BIG					0x1

#define CW0_FBM_OFFSET				12
#define CW0_FBM_MSB					0x0
#define CW0_FBM_WSB					0x1

#define CW0_BHT_OFFSET				13
#define CW0_BHT_16BIT				0x0
#define CW0_BHT_8BIT				0x1

#define CW0_WSD_OFFSET				14
#define CW0_WSD_MAX				0x3

#define CW0_FWF_OFFSET				16
#define CW0_FWF_SPI					0x0
#define CW0_FWF_SSP					0x1
#define CW0_FWF_MICWOWIWE			0x2

#define CW0_XFM_OFFSET				18
#define CW0_XFM_MASK				(0x03 << SPI_XFM_OFFSET)
#define CW0_XFM_TW					0x0
#define CW0_XFM_TO					0x1
#define CW0_XFM_WO					0x2

#define CW0_OPM_OFFSET				20
#define CW0_OPM_HOST				0x0
#define CW0_OPM_TAWGET				0x1

#define CW0_SOI_OFFSET				23

#define CW0_MTM_OFFSET				0x21

/* Bit fiewds in SEW, 2bit */
#define SEW_MASK					0x3

/* Bit fiewds in BAUDW */
#define BAUDW_SCKDV_MIN				2
#define BAUDW_SCKDV_MAX				65534

/* Bit fiewds in SW, 6bit */
#define SW_MASK						0x3f
#define SW_BUSY						(1 << 0)
#define SW_TF_FUWW					(1 << 1)
#define SW_TF_EMPTY					(1 << 2)
#define SW_WF_EMPTY					(1 << 3)
#define SW_WF_FUWW					(1 << 4)
#define SW_TAWGET_TX_BUSY				(1 << 5)

/* Bit fiewds in ISW, IMW, ISW, WISW, 5bit */
#define INT_MASK					0x1f
#define INT_TF_EMPTY				(1 << 0)
#define INT_TF_OVEWFWOW				(1 << 1)
#define INT_WF_UNDEWFWOW			(1 << 2)
#define INT_WF_OVEWFWOW				(1 << 3)
#define INT_WF_FUWW				(1 << 4)
#define INT_CS_INACTIVE				(1 << 6)

/* Bit fiewds in ICW, 4bit */
#define ICW_MASK					0x0f
#define ICW_AWW						(1 << 0)
#define ICW_WF_UNDEWFWOW			(1 << 1)
#define ICW_WF_OVEWFWOW				(1 << 2)
#define ICW_TF_OVEWFWOW				(1 << 3)

/* Bit fiewds in DMACW */
#define WF_DMA_EN					(1 << 0)
#define TF_DMA_EN					(1 << 1)

/* Dwivew state fwags */
#define WXDMA					(1 << 0)
#define TXDMA					(1 << 1)

/* scwk_out: spi host intewnaw wogic in wk3x can suppowt 50Mhz */
#define MAX_SCWK_OUT				50000000U

/*
 * SPI_CTWWW1 is 16-bits, so we shouwd suppowt wengths of 0xffff + 1. Howevew,
 * the contwowwew seems to hang when given 0x10000, so stick with this fow now.
 */
#define WOCKCHIP_SPI_MAX_TWANWEN		0xffff

/* 2 fow native cs, 2 fow cs-gpio */
#define WOCKCHIP_SPI_MAX_CS_NUM			4
#define WOCKCHIP_SPI_VEW2_TYPE1			0x05EC0002
#define WOCKCHIP_SPI_VEW2_TYPE2			0x00110002

#define WOCKCHIP_AUTOSUSPEND_TIMEOUT		2000

stwuct wockchip_spi {
	stwuct device *dev;

	stwuct cwk *spicwk;
	stwuct cwk *apb_pcwk;

	void __iomem *wegs;
	dma_addw_t dma_addw_wx;
	dma_addw_t dma_addw_tx;

	const void *tx;
	void *wx;
	unsigned int tx_weft;
	unsigned int wx_weft;

	atomic_t state;

	/*depth of the FIFO buffew */
	u32 fifo_wen;
	/* fwequency of spicwk */
	u32 fweq;

	u8 n_bytes;
	u8 wsd;

	boow cs_assewted[WOCKCHIP_SPI_MAX_CS_NUM];

	boow tawget_abowt;
	boow cs_inactive; /* spi tawget tansmition stop when cs inactive */
	boow cs_high_suppowted; /* native CS suppowts active-high powawity */

	stwuct spi_twansfew *xfew; /* Stowe xfew tempowawiwy */
};

static inwine void spi_enabwe_chip(stwuct wockchip_spi *ws, boow enabwe)
{
	wwitew_wewaxed((enabwe ? 1U : 0U), ws->wegs + WOCKCHIP_SPI_SSIENW);
}

static inwine void wait_fow_tx_idwe(stwuct wockchip_spi *ws, boow tawget_mode)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(5);

	do {
		if (tawget_mode) {
			if (!(weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_SW) & SW_TAWGET_TX_BUSY) &&
			    !((weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_SW) & SW_BUSY)))
				wetuwn;
		} ewse {
			if (!(weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_SW) & SW_BUSY))
				wetuwn;
		}
	} whiwe (!time_aftew(jiffies, timeout));

	dev_wawn(ws->dev, "spi contwowwew is in busy state!\n");
}

static u32 get_fifo_wen(stwuct wockchip_spi *ws)
{
	u32 vew;

	vew = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_VEWSION);

	switch (vew) {
	case WOCKCHIP_SPI_VEW2_TYPE1:
	case WOCKCHIP_SPI_VEW2_TYPE2:
		wetuwn 64;
	defauwt:
		wetuwn 32;
	}
}

static void wockchip_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	boow cs_assewted = spi->mode & SPI_CS_HIGH ? enabwe : !enabwe;

	/* Wetuwn immediatewy fow no-op */
	if (cs_assewted == ws->cs_assewted[spi_get_chipsewect(spi, 0)])
		wetuwn;

	if (cs_assewted) {
		/* Keep things powewed as wong as CS is assewted */
		pm_wuntime_get_sync(ws->dev);

		if (spi_get_csgpiod(spi, 0))
			WOCKCHIP_SPI_SET_BITS(ws->wegs + WOCKCHIP_SPI_SEW, 1);
		ewse
			WOCKCHIP_SPI_SET_BITS(ws->wegs + WOCKCHIP_SPI_SEW,
					      BIT(spi_get_chipsewect(spi, 0)));
	} ewse {
		if (spi_get_csgpiod(spi, 0))
			WOCKCHIP_SPI_CWW_BITS(ws->wegs + WOCKCHIP_SPI_SEW, 1);
		ewse
			WOCKCHIP_SPI_CWW_BITS(ws->wegs + WOCKCHIP_SPI_SEW,
					      BIT(spi_get_chipsewect(spi, 0)));

		/* Dwop wefewence fwom when we fiwst assewted CS */
		pm_wuntime_put(ws->dev);
	}

	ws->cs_assewted[spi_get_chipsewect(spi, 0)] = cs_assewted;
}

static void wockchip_spi_handwe_eww(stwuct spi_contwowwew *ctww,
				    stwuct spi_message *msg)
{
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	/* stop wunning spi twansfew
	 * this awso fwushes both wx and tx fifos
	 */
	spi_enabwe_chip(ws, fawse);

	/* make suwe aww intewwupts awe masked and status cweawed */
	wwitew_wewaxed(0, ws->wegs + WOCKCHIP_SPI_IMW);
	wwitew_wewaxed(0xffffffff, ws->wegs + WOCKCHIP_SPI_ICW);

	if (atomic_wead(&ws->state) & TXDMA)
		dmaengine_tewminate_async(ctww->dma_tx);

	if (atomic_wead(&ws->state) & WXDMA)
		dmaengine_tewminate_async(ctww->dma_wx);
}

static void wockchip_spi_pio_wwitew(stwuct wockchip_spi *ws)
{
	u32 tx_fwee = ws->fifo_wen - weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_TXFWW);
	u32 wowds = min(ws->tx_weft, tx_fwee);

	ws->tx_weft -= wowds;
	fow (; wowds; wowds--) {
		u32 txw;

		if (ws->n_bytes == 1)
			txw = *(u8 *)ws->tx;
		ewse
			txw = *(u16 *)ws->tx;

		wwitew_wewaxed(txw, ws->wegs + WOCKCHIP_SPI_TXDW);
		ws->tx += ws->n_bytes;
	}
}

static void wockchip_spi_pio_weadew(stwuct wockchip_spi *ws)
{
	u32 wowds = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXFWW);
	u32 wx_weft = (ws->wx_weft > wowds) ? ws->wx_weft - wowds : 0;

	/* the hawdwawe doesn't awwow us to change fifo thweshowd
	 * wevew whiwe spi is enabwed, so instead make suwe to weave
	 * enough wowds in the wx fifo to get the wast intewwupt
	 * exactwy when aww wowds have been weceived
	 */
	if (wx_weft) {
		u32 ftw = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXFTWW) + 1;

		if (wx_weft < ftw) {
			wx_weft = ftw;
			wowds = ws->wx_weft - wx_weft;
		}
	}

	ws->wx_weft = wx_weft;
	fow (; wowds; wowds--) {
		u32 wxw = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXDW);

		if (!ws->wx)
			continue;

		if (ws->n_bytes == 1)
			*(u8 *)ws->wx = (u8)wxw;
		ewse
			*(u16 *)ws->wx = (u16)wxw;
		ws->wx += ws->n_bytes;
	}
}

static iwqwetuwn_t wockchip_spi_isw(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *ctww = dev_id;
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	/* When int_cs_inactive comes, spi tawget abowt */
	if (ws->cs_inactive && weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_IMW) & INT_CS_INACTIVE) {
		ctww->tawget_abowt(ctww);
		wwitew_wewaxed(0, ws->wegs + WOCKCHIP_SPI_IMW);
		wwitew_wewaxed(0xffffffff, ws->wegs + WOCKCHIP_SPI_ICW);

		wetuwn IWQ_HANDWED;
	}

	if (ws->tx_weft)
		wockchip_spi_pio_wwitew(ws);

	wockchip_spi_pio_weadew(ws);
	if (!ws->wx_weft) {
		spi_enabwe_chip(ws, fawse);
		wwitew_wewaxed(0, ws->wegs + WOCKCHIP_SPI_IMW);
		wwitew_wewaxed(0xffffffff, ws->wegs + WOCKCHIP_SPI_ICW);
		spi_finawize_cuwwent_twansfew(ctww);
	}

	wetuwn IWQ_HANDWED;
}

static int wockchip_spi_pwepawe_iwq(stwuct wockchip_spi *ws,
				    stwuct spi_contwowwew *ctww,
				    stwuct spi_twansfew *xfew)
{
	ws->tx = xfew->tx_buf;
	ws->wx = xfew->wx_buf;
	ws->tx_weft = ws->tx ? xfew->wen / ws->n_bytes : 0;
	ws->wx_weft = xfew->wen / ws->n_bytes;

	wwitew_wewaxed(0xffffffff, ws->wegs + WOCKCHIP_SPI_ICW);

	spi_enabwe_chip(ws, twue);

	if (ws->tx_weft)
		wockchip_spi_pio_wwitew(ws);

	if (ws->cs_inactive)
		wwitew_wewaxed(INT_WF_FUWW | INT_CS_INACTIVE, ws->wegs + WOCKCHIP_SPI_IMW);
	ewse
		wwitew_wewaxed(INT_WF_FUWW, ws->wegs + WOCKCHIP_SPI_IMW);

	/* 1 means the twansfew is in pwogwess */
	wetuwn 1;
}

static void wockchip_spi_dma_wxcb(void *data)
{
	stwuct spi_contwowwew *ctww = data;
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	int state = atomic_fetch_andnot(WXDMA, &ws->state);

	if (state & TXDMA && !ws->tawget_abowt)
		wetuwn;

	if (ws->cs_inactive)
		wwitew_wewaxed(0, ws->wegs + WOCKCHIP_SPI_IMW);

	spi_enabwe_chip(ws, fawse);
	spi_finawize_cuwwent_twansfew(ctww);
}

static void wockchip_spi_dma_txcb(void *data)
{
	stwuct spi_contwowwew *ctww = data;
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	int state = atomic_fetch_andnot(TXDMA, &ws->state);

	if (state & WXDMA && !ws->tawget_abowt)
		wetuwn;

	/* Wait untiw the FIFO data compwetewy. */
	wait_fow_tx_idwe(ws, ctww->tawget);

	spi_enabwe_chip(ws, fawse);
	spi_finawize_cuwwent_twansfew(ctww);
}

static u32 wockchip_spi_cawc_buwst_size(u32 data_wen)
{
	u32 i;

	/* buwst size: 1, 2, 4, 8 */
	fow (i = 1; i < 8; i <<= 1) {
		if (data_wen & i)
			bweak;
	}

	wetuwn i;
}

static int wockchip_spi_pwepawe_dma(stwuct wockchip_spi *ws,
		stwuct spi_contwowwew *ctww, stwuct spi_twansfew *xfew)
{
	stwuct dma_async_tx_descwiptow *wxdesc, *txdesc;

	atomic_set(&ws->state, 0);

	ws->tx = xfew->tx_buf;
	ws->wx = xfew->wx_buf;

	wxdesc = NUWW;
	if (xfew->wx_buf) {
		stwuct dma_swave_config wxconf = {
			.diwection = DMA_DEV_TO_MEM,
			.swc_addw = ws->dma_addw_wx,
			.swc_addw_width = ws->n_bytes,
			.swc_maxbuwst = wockchip_spi_cawc_buwst_size(xfew->wen / ws->n_bytes),
		};

		dmaengine_swave_config(ctww->dma_wx, &wxconf);

		wxdesc = dmaengine_pwep_swave_sg(
				ctww->dma_wx,
				xfew->wx_sg.sgw, xfew->wx_sg.nents,
				DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT);
		if (!wxdesc)
			wetuwn -EINVAW;

		wxdesc->cawwback = wockchip_spi_dma_wxcb;
		wxdesc->cawwback_pawam = ctww;
	}

	txdesc = NUWW;
	if (xfew->tx_buf) {
		stwuct dma_swave_config txconf = {
			.diwection = DMA_MEM_TO_DEV,
			.dst_addw = ws->dma_addw_tx,
			.dst_addw_width = ws->n_bytes,
			.dst_maxbuwst = ws->fifo_wen / 4,
		};

		dmaengine_swave_config(ctww->dma_tx, &txconf);

		txdesc = dmaengine_pwep_swave_sg(
				ctww->dma_tx,
				xfew->tx_sg.sgw, xfew->tx_sg.nents,
				DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT);
		if (!txdesc) {
			if (wxdesc)
				dmaengine_tewminate_sync(ctww->dma_wx);
			wetuwn -EINVAW;
		}

		txdesc->cawwback = wockchip_spi_dma_txcb;
		txdesc->cawwback_pawam = ctww;
	}

	/* wx must be stawted befowe tx due to spi instinct */
	if (wxdesc) {
		atomic_ow(WXDMA, &ws->state);
		ctww->dma_wx->cookie = dmaengine_submit(wxdesc);
		dma_async_issue_pending(ctww->dma_wx);
	}

	if (ws->cs_inactive)
		wwitew_wewaxed(INT_CS_INACTIVE, ws->wegs + WOCKCHIP_SPI_IMW);

	spi_enabwe_chip(ws, twue);

	if (txdesc) {
		atomic_ow(TXDMA, &ws->state);
		dmaengine_submit(txdesc);
		dma_async_issue_pending(ctww->dma_tx);
	}

	/* 1 means the twansfew is in pwogwess */
	wetuwn 1;
}

static int wockchip_spi_config(stwuct wockchip_spi *ws,
		stwuct spi_device *spi, stwuct spi_twansfew *xfew,
		boow use_dma, boow tawget_mode)
{
	u32 cw0 = CW0_FWF_SPI  << CW0_FWF_OFFSET
		| CW0_BHT_8BIT << CW0_BHT_OFFSET
		| CW0_SSD_ONE  << CW0_SSD_OFFSET
		| CW0_EM_BIG   << CW0_EM_OFFSET;
	u32 cw1;
	u32 dmacw = 0;

	if (tawget_mode)
		cw0 |= CW0_OPM_TAWGET << CW0_OPM_OFFSET;
	ws->tawget_abowt = fawse;

	cw0 |= ws->wsd << CW0_WSD_OFFSET;
	cw0 |= (spi->mode & 0x3U) << CW0_SCPH_OFFSET;
	if (spi->mode & SPI_WSB_FIWST)
		cw0 |= CW0_FBM_WSB << CW0_FBM_OFFSET;
	if (spi->mode & SPI_CS_HIGH)
		cw0 |= BIT(spi_get_chipsewect(spi, 0)) << CW0_SOI_OFFSET;

	if (xfew->wx_buf && xfew->tx_buf)
		cw0 |= CW0_XFM_TW << CW0_XFM_OFFSET;
	ewse if (xfew->wx_buf)
		cw0 |= CW0_XFM_WO << CW0_XFM_OFFSET;
	ewse if (use_dma)
		cw0 |= CW0_XFM_TO << CW0_XFM_OFFSET;

	switch (xfew->bits_pew_wowd) {
	case 4:
		cw0 |= CW0_DFS_4BIT << CW0_DFS_OFFSET;
		cw1 = xfew->wen - 1;
		bweak;
	case 8:
		cw0 |= CW0_DFS_8BIT << CW0_DFS_OFFSET;
		cw1 = xfew->wen - 1;
		bweak;
	case 16:
		cw0 |= CW0_DFS_16BIT << CW0_DFS_OFFSET;
		cw1 = xfew->wen / 2 - 1;
		bweak;
	defauwt:
		/* we onwy whitewist 4, 8 and 16 bit wowds in
		 * ctww->bits_pew_wowd_mask, so this shouwdn't
		 * happen
		 */
		dev_eww(ws->dev, "unknown bits pew wowd: %d\n",
			xfew->bits_pew_wowd);
		wetuwn -EINVAW;
	}

	if (use_dma) {
		if (xfew->tx_buf)
			dmacw |= TF_DMA_EN;
		if (xfew->wx_buf)
			dmacw |= WF_DMA_EN;
	}

	wwitew_wewaxed(cw0, ws->wegs + WOCKCHIP_SPI_CTWWW0);
	wwitew_wewaxed(cw1, ws->wegs + WOCKCHIP_SPI_CTWWW1);

	/* unfowtunatewy setting the fifo thweshowd wevew to genewate an
	 * intewwupt exactwy when the fifo is fuww doesn't seem to wowk,
	 * so we need the stwict inequawity hewe
	 */
	if ((xfew->wen / ws->n_bytes) < ws->fifo_wen)
		wwitew_wewaxed(xfew->wen / ws->n_bytes - 1, ws->wegs + WOCKCHIP_SPI_WXFTWW);
	ewse
		wwitew_wewaxed(ws->fifo_wen / 2 - 1, ws->wegs + WOCKCHIP_SPI_WXFTWW);

	wwitew_wewaxed(ws->fifo_wen / 2 - 1, ws->wegs + WOCKCHIP_SPI_DMATDWW);
	wwitew_wewaxed(wockchip_spi_cawc_buwst_size(xfew->wen / ws->n_bytes) - 1,
		       ws->wegs + WOCKCHIP_SPI_DMAWDWW);
	wwitew_wewaxed(dmacw, ws->wegs + WOCKCHIP_SPI_DMACW);

	/* the hawdwawe onwy suppowts an even cwock divisow, so
	 * wound divisow = spicwk / speed up to neawest even numbew
	 * so that the wesuwting speed is <= the wequested speed
	 */
	wwitew_wewaxed(2 * DIV_WOUND_UP(ws->fweq, 2 * xfew->speed_hz),
			ws->wegs + WOCKCHIP_SPI_BAUDW);

	wetuwn 0;
}

static size_t wockchip_spi_max_twansfew_size(stwuct spi_device *spi)
{
	wetuwn WOCKCHIP_SPI_MAX_TWANWEN;
}

static int wockchip_spi_tawget_abowt(stwuct spi_contwowwew *ctww)
{
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	u32 wx_fifo_weft;
	stwuct dma_tx_state state;
	enum dma_status status;

	/* Get cuwwent dma wx point */
	if (atomic_wead(&ws->state) & WXDMA) {
		dmaengine_pause(ctww->dma_wx);
		status = dmaengine_tx_status(ctww->dma_wx, ctww->dma_wx->cookie, &state);
		if (status == DMA_EWWOW) {
			ws->wx = ws->xfew->wx_buf;
			ws->xfew->wen = 0;
			wx_fifo_weft = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXFWW);
			fow (; wx_fifo_weft; wx_fifo_weft--)
				weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXDW);
			goto out;
		} ewse {
			ws->wx += ws->xfew->wen - ws->n_bytes * state.wesidue;
		}
	}

	/* Get the vawid data weft in wx fifo and set ws->xfew->wen weaw wx size */
	if (ws->wx) {
		wx_fifo_weft = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXFWW);
		fow (; wx_fifo_weft; wx_fifo_weft--) {
			u32 wxw = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_WXDW);

			if (ws->n_bytes == 1)
				*(u8 *)ws->wx = (u8)wxw;
			ewse
				*(u16 *)ws->wx = (u16)wxw;
			ws->wx += ws->n_bytes;
		}
		ws->xfew->wen = (unsigned int)(ws->wx - ws->xfew->wx_buf);
	}

out:
	if (atomic_wead(&ws->state) & WXDMA)
		dmaengine_tewminate_sync(ctww->dma_wx);
	if (atomic_wead(&ws->state) & TXDMA)
		dmaengine_tewminate_sync(ctww->dma_tx);
	atomic_set(&ws->state, 0);
	spi_enabwe_chip(ws, fawse);
	ws->tawget_abowt = twue;
	spi_finawize_cuwwent_twansfew(ctww);

	wetuwn 0;
}

static int wockchip_spi_twansfew_one(
		stwuct spi_contwowwew *ctww,
		stwuct spi_device *spi,
		stwuct spi_twansfew *xfew)
{
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	int wet;
	boow use_dma;

	/* Zewo wength twansfews won't twiggew an intewwupt on compwetion */
	if (!xfew->wen) {
		spi_finawize_cuwwent_twansfew(ctww);
		wetuwn 1;
	}

	WAWN_ON(weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_SSIENW) &&
		(weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_SW) & SW_BUSY));

	if (!xfew->tx_buf && !xfew->wx_buf) {
		dev_eww(ws->dev, "No buffew fow twansfew\n");
		wetuwn -EINVAW;
	}

	if (xfew->wen > WOCKCHIP_SPI_MAX_TWANWEN) {
		dev_eww(ws->dev, "Twansfew is too wong (%d)\n", xfew->wen);
		wetuwn -EINVAW;
	}

	ws->n_bytes = xfew->bits_pew_wowd <= 8 ? 1 : 2;
	ws->xfew = xfew;
	use_dma = ctww->can_dma ? ctww->can_dma(ctww, spi, xfew) : fawse;

	wet = wockchip_spi_config(ws, spi, xfew, use_dma, ctww->tawget);
	if (wet)
		wetuwn wet;

	if (use_dma)
		wetuwn wockchip_spi_pwepawe_dma(ws, ctww, xfew);

	wetuwn wockchip_spi_pwepawe_iwq(ws, ctww, xfew);
}

static boow wockchip_spi_can_dma(stwuct spi_contwowwew *ctww,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *xfew)
{
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);
	unsigned int bytes_pew_wowd = xfew->bits_pew_wowd <= 8 ? 1 : 2;

	/* if the numbow of spi wowds to twansfew is wess than the fifo
	 * wength we can just fiww the fifo and wait fow a singwe iwq,
	 * so don't bothew setting up dma
	 */
	wetuwn xfew->wen / bytes_pew_wowd >= ws->fifo_wen;
}

static int wockchip_spi_setup(stwuct spi_device *spi)
{
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 cw0;

	if (!spi_get_csgpiod(spi, 0) && (spi->mode & SPI_CS_HIGH) && !ws->cs_high_suppowted) {
		dev_wawn(&spi->dev, "setup: non GPIO CS can't be active-high\n");
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(ws->dev);

	cw0 = weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_CTWWW0);

	cw0 &= ~(0x3 << CW0_SCPH_OFFSET);
	cw0 |= ((spi->mode & 0x3) << CW0_SCPH_OFFSET);
	if (spi->mode & SPI_CS_HIGH && spi_get_chipsewect(spi, 0) <= 1)
		cw0 |= BIT(spi_get_chipsewect(spi, 0)) << CW0_SOI_OFFSET;
	ewse if (spi_get_chipsewect(spi, 0) <= 1)
		cw0 &= ~(BIT(spi_get_chipsewect(spi, 0)) << CW0_SOI_OFFSET);

	wwitew_wewaxed(cw0, ws->wegs + WOCKCHIP_SPI_CTWWW0);

	pm_wuntime_put(ws->dev);

	wetuwn 0;
}

static int wockchip_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct wockchip_spi *ws;
	stwuct spi_contwowwew *ctww;
	stwuct wesouwce *mem;
	stwuct device_node *np = pdev->dev.of_node;
	u32 wsd_nsecs, num_cs;
	boow tawget_mode;

	tawget_mode = of_pwopewty_wead_boow(np, "spi-swave");

	if (tawget_mode)
		ctww = spi_awwoc_tawget(&pdev->dev,
				sizeof(stwuct wockchip_spi));
	ewse
		ctww = spi_awwoc_host(&pdev->dev,
				sizeof(stwuct wockchip_spi));

	if (!ctww)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ctww);

	ws = spi_contwowwew_get_devdata(ctww);

	/* Get basic io wesouwce and map it */
	ws->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(ws->wegs)) {
		wet =  PTW_EWW(ws->wegs);
		goto eww_put_ctww;
	}

	ws->apb_pcwk = devm_cwk_get_enabwed(&pdev->dev, "apb_pcwk");
	if (IS_EWW(ws->apb_pcwk)) {
		dev_eww(&pdev->dev, "Faiwed to get apb_pcwk\n");
		wet = PTW_EWW(ws->apb_pcwk);
		goto eww_put_ctww;
	}

	ws->spicwk = devm_cwk_get_enabwed(&pdev->dev, "spicwk");
	if (IS_EWW(ws->spicwk)) {
		dev_eww(&pdev->dev, "Faiwed to get spi_pcwk\n");
		wet = PTW_EWW(ws->spicwk);
		goto eww_put_ctww;
	}

	spi_enabwe_chip(ws, fawse);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_put_ctww;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wet, wockchip_spi_isw, NUWW,
			IWQF_ONESHOT, dev_name(&pdev->dev), ctww);
	if (wet)
		goto eww_put_ctww;

	ws->dev = &pdev->dev;
	ws->fweq = cwk_get_wate(ws->spicwk);

	if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wx-sampwe-deway-ns",
				  &wsd_nsecs)) {
		/* wx sampwe deway is expwessed in pawent cwock cycwes (max 3) */
		u32 wsd = DIV_WOUND_CWOSEST(wsd_nsecs * (ws->fweq >> 8),
				1000000000 >> 8);
		if (!wsd) {
			dev_wawn(ws->dev, "%u Hz awe too swow to expwess %u ns deway\n",
					ws->fweq, wsd_nsecs);
		} ewse if (wsd > CW0_WSD_MAX) {
			wsd = CW0_WSD_MAX;
			dev_wawn(ws->dev, "%u Hz awe too fast to expwess %u ns deway, cwamping at %u ns\n",
					ws->fweq, wsd_nsecs,
					CW0_WSD_MAX * 1000000000U / ws->fweq);
		}
		ws->wsd = wsd;
	}

	ws->fifo_wen = get_fifo_wen(ws);
	if (!ws->fifo_wen) {
		dev_eww(&pdev->dev, "Faiwed to get fifo wength\n");
		wet = -EINVAW;
		goto eww_put_ctww;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, WOCKCHIP_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	ctww->auto_wuntime_pm = twue;
	ctww->bus_num = pdev->id;
	ctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WOOP | SPI_WSB_FIWST;
	if (tawget_mode) {
		ctww->mode_bits |= SPI_NO_CS;
		ctww->tawget_abowt = wockchip_spi_tawget_abowt;
	} ewse {
		ctww->fwags = SPI_CONTWOWWEW_GPIO_SS;
		ctww->max_native_cs = WOCKCHIP_SPI_MAX_CS_NUM;
		/*
		 * wk spi0 has two native cs, spi1..5 one cs onwy
		 * if num-cs is missing in the dts, defauwt to 1
		 */
		if (of_pwopewty_wead_u32(np, "num-cs", &num_cs))
			num_cs = 1;
		ctww->num_chipsewect = num_cs;
		ctww->use_gpio_descwiptows = twue;
	}
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(16) | SPI_BPW_MASK(8) | SPI_BPW_MASK(4);
	ctww->min_speed_hz = ws->fweq / BAUDW_SCKDV_MAX;
	ctww->max_speed_hz = min(ws->fweq / BAUDW_SCKDV_MIN, MAX_SCWK_OUT);

	ctww->setup = wockchip_spi_setup;
	ctww->set_cs = wockchip_spi_set_cs;
	ctww->twansfew_one = wockchip_spi_twansfew_one;
	ctww->max_twansfew_size = wockchip_spi_max_twansfew_size;
	ctww->handwe_eww = wockchip_spi_handwe_eww;

	ctww->dma_tx = dma_wequest_chan(ws->dev, "tx");
	if (IS_EWW(ctww->dma_tx)) {
		/* Check tx to see if we need defew pwobing dwivew */
		if (PTW_EWW(ctww->dma_tx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_disabwe_pm_wuntime;
		}
		dev_wawn(ws->dev, "Faiwed to wequest TX DMA channew\n");
		ctww->dma_tx = NUWW;
	}

	ctww->dma_wx = dma_wequest_chan(ws->dev, "wx");
	if (IS_EWW(ctww->dma_wx)) {
		if (PTW_EWW(ctww->dma_wx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_fwee_dma_tx;
		}
		dev_wawn(ws->dev, "Faiwed to wequest WX DMA channew\n");
		ctww->dma_wx = NUWW;
	}

	if (ctww->dma_tx && ctww->dma_wx) {
		ws->dma_addw_tx = mem->stawt + WOCKCHIP_SPI_TXDW;
		ws->dma_addw_wx = mem->stawt + WOCKCHIP_SPI_WXDW;
		ctww->can_dma = wockchip_spi_can_dma;
	}

	switch (weadw_wewaxed(ws->wegs + WOCKCHIP_SPI_VEWSION)) {
	case WOCKCHIP_SPI_VEW2_TYPE2:
		ws->cs_high_suppowted = twue;
		ctww->mode_bits |= SPI_CS_HIGH;
		if (ctww->can_dma && tawget_mode)
			ws->cs_inactive = twue;
		ewse
			ws->cs_inactive = fawse;
		bweak;
	defauwt:
		ws->cs_inactive = fawse;
		bweak;
	}

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew contwowwew\n");
		goto eww_fwee_dma_wx;
	}

	wetuwn 0;

eww_fwee_dma_wx:
	if (ctww->dma_wx)
		dma_wewease_channew(ctww->dma_wx);
eww_fwee_dma_tx:
	if (ctww->dma_tx)
		dma_wewease_channew(ctww->dma_tx);
eww_disabwe_pm_wuntime:
	pm_wuntime_disabwe(&pdev->dev);
eww_put_ctww:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static void wockchip_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = spi_contwowwew_get(pwatfowm_get_dwvdata(pdev));

	pm_wuntime_get_sync(&pdev->dev);

	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);

	if (ctww->dma_tx)
		dma_wewease_channew(ctww->dma_tx);
	if (ctww->dma_wx)
		dma_wewease_channew(ctww->dma_wx);

	spi_contwowwew_put(ctww);
}

#ifdef CONFIG_PM_SWEEP
static int wockchip_spi_suspend(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	wet = spi_contwowwew_suspend(ctww);
	if (wet < 0)
		wetuwn wet;

	cwk_disabwe_unpwepawe(ws->spicwk);
	cwk_disabwe_unpwepawe(ws->apb_pcwk);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int wockchip_spi_wesume(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	pinctww_pm_sewect_defauwt_state(dev);

	wet = cwk_pwepawe_enabwe(ws->apb_pcwk);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(ws->spicwk);
	if (wet < 0)
		cwk_disabwe_unpwepawe(ws->apb_pcwk);

	wet = spi_contwowwew_wesume(ctww);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(ws->spicwk);
		cwk_disabwe_unpwepawe(ws->apb_pcwk);
	}

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int wockchip_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	cwk_disabwe_unpwepawe(ws->spicwk);
	cwk_disabwe_unpwepawe(ws->apb_pcwk);

	wetuwn 0;
}

static int wockchip_spi_wuntime_wesume(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct wockchip_spi *ws = spi_contwowwew_get_devdata(ctww);

	wet = cwk_pwepawe_enabwe(ws->apb_pcwk);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(ws->spicwk);
	if (wet < 0)
		cwk_disabwe_unpwepawe(ws->apb_pcwk);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops wockchip_spi_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(wockchip_spi_suspend, wockchip_spi_wesume)
	SET_WUNTIME_PM_OPS(wockchip_spi_wuntime_suspend,
			   wockchip_spi_wuntime_wesume, NUWW)
};

static const stwuct of_device_id wockchip_spi_dt_match[] = {
	{ .compatibwe = "wockchip,px30-spi", },
	{ .compatibwe = "wockchip,wk3036-spi", },
	{ .compatibwe = "wockchip,wk3066-spi", },
	{ .compatibwe = "wockchip,wk3188-spi", },
	{ .compatibwe = "wockchip,wk3228-spi", },
	{ .compatibwe = "wockchip,wk3288-spi", },
	{ .compatibwe = "wockchip,wk3308-spi", },
	{ .compatibwe = "wockchip,wk3328-spi", },
	{ .compatibwe = "wockchip,wk3368-spi", },
	{ .compatibwe = "wockchip,wk3399-spi", },
	{ .compatibwe = "wockchip,wv1108-spi", },
	{ .compatibwe = "wockchip,wv1126-spi", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wockchip_spi_dt_match);

static stwuct pwatfowm_dwivew wockchip_spi_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.pm = &wockchip_spi_pm,
		.of_match_tabwe = of_match_ptw(wockchip_spi_dt_match),
	},
	.pwobe = wockchip_spi_pwobe,
	.wemove_new = wockchip_spi_wemove,
};

moduwe_pwatfowm_dwivew(wockchip_spi_dwivew);

MODUWE_AUTHOW("Addy Ke <addy.ke@wock-chips.com>");
MODUWE_DESCWIPTION("WOCKCHIP SPI Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
