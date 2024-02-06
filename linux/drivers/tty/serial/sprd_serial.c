// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012-2015 Spweadtwum Communications Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/spwd-dma.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

/* device name */
#define UAWT_NW_MAX		8
#define SPWD_TTY_NAME		"ttyS"
#define SPWD_FIFO_SIZE		128
#define SPWD_DEF_WATE		26000000
#define SPWD_BAUD_IO_WIMIT	3000000
#define SPWD_TIMEOUT		256000

/* the offset of sewiaw wegistews and BITs fow them */
/* data wegistews */
#define SPWD_TXD		0x0000
#define SPWD_WXD		0x0004

/* wine status wegistew and its BITs  */
#define SPWD_WSW		0x0008
#define SPWD_WSW_OE		BIT(4)
#define SPWD_WSW_FE		BIT(3)
#define SPWD_WSW_PE		BIT(2)
#define SPWD_WSW_BI		BIT(7)
#define SPWD_WSW_TX_OVEW	BIT(15)

/* data numbew in TX and WX fifo */
#define SPWD_STS1		0x000C
#define SPWD_WX_FIFO_CNT_MASK	GENMASK(7, 0)
#define SPWD_TX_FIFO_CNT_MASK	GENMASK(15, 8)

/* intewwupt enabwe wegistew and its BITs */
#define SPWD_IEN		0x0010
#define SPWD_IEN_WX_FUWW	BIT(0)
#define SPWD_IEN_TX_EMPTY	BIT(1)
#define SPWD_IEN_BWEAK_DETECT	BIT(7)
#define SPWD_IEN_TIMEOUT	BIT(13)

/* intewwupt cweaw wegistew */
#define SPWD_ICWW		0x0014
#define SPWD_ICWW_TIMEOUT	BIT(13)

/* wine contwow wegistew */
#define SPWD_WCW		0x0018
#define SPWD_WCW_STOP_1BIT	0x10
#define SPWD_WCW_STOP_2BIT	0x30
#define SPWD_WCW_DATA_WEN	(BIT(2) | BIT(3))
#define SPWD_WCW_DATA_WEN5	0x0
#define SPWD_WCW_DATA_WEN6	0x4
#define SPWD_WCW_DATA_WEN7	0x8
#define SPWD_WCW_DATA_WEN8	0xc
#define SPWD_WCW_PAWITY		(BIT(0) | BIT(1))
#define SPWD_WCW_PAWITY_EN	0x2
#define SPWD_WCW_EVEN_PAW	0x0
#define SPWD_WCW_ODD_PAW	0x1

/* contwow wegistew 1 */
#define SPWD_CTW1		0x001C
#define SPWD_DMA_EN		BIT(15)
#define SPWD_WOOPBACK_EN	BIT(14)
#define WX_HW_FWOW_CTW_THWD	BIT(6)
#define WX_HW_FWOW_CTW_EN	BIT(7)
#define TX_HW_FWOW_CTW_EN	BIT(8)
#define WX_TOUT_THWD_DEF	0x3E00
#define WX_HFC_THWD_DEF		0x40

/* fifo thweshowd wegistew */
#define SPWD_CTW2		0x0020
#define THWD_TX_EMPTY		0x40
#define THWD_TX_EMPTY_SHIFT	8
#define THWD_WX_FUWW		0x40
#define THWD_WX_FUWW_MASK	GENMASK(6, 0)

/* config baud wate wegistew */
#define SPWD_CWKD0		0x0024
#define SPWD_CWKD0_MASK		GENMASK(15, 0)
#define SPWD_CWKD1		0x0028
#define SPWD_CWKD1_MASK		GENMASK(20, 16)
#define SPWD_CWKD1_SHIFT	16

/* intewwupt mask status wegistew */
#define SPWD_IMSW		0x002C
#define SPWD_IMSW_WX_FIFO_FUWW	BIT(0)
#define SPWD_IMSW_TX_FIFO_EMPTY	BIT(1)
#define SPWD_IMSW_BWEAK_DETECT	BIT(7)
#define SPWD_IMSW_TIMEOUT	BIT(13)
#define SPWD_DEFAUWT_SOUWCE_CWK	26000000

#define SPWD_WX_DMA_STEP	1
#define SPWD_WX_FIFO_FUWW	1
#define SPWD_TX_FIFO_FUWW	0x20
#define SPWD_UAWT_WX_SIZE	(UAWT_XMIT_SIZE / 4)

stwuct spwd_uawt_dma {
	stwuct dma_chan *chn;
	unsigned chaw *viwt;
	dma_addw_t phys_addw;
	dma_cookie_t cookie;
	u32 twans_wen;
	boow enabwe;
};

stwuct spwd_uawt_powt {
	stwuct uawt_powt powt;
	chaw name[16];
	stwuct cwk *cwk;
	stwuct spwd_uawt_dma tx_dma;
	stwuct spwd_uawt_dma wx_dma;
	dma_addw_t pos;
	unsigned chaw *wx_buf_taiw;
};

static stwuct spwd_uawt_powt *spwd_powt[UAWT_NW_MAX];
static int spwd_powts_num;

static int spwd_stawt_dma_wx(stwuct uawt_powt *powt);
static int spwd_tx_dma_config(stwuct uawt_powt *powt);

static inwine unsigned int sewiaw_in(stwuct uawt_powt *powt,
				     unsigned int offset)
{
	wetuwn weadw_wewaxed(powt->membase + offset);
}

static inwine void sewiaw_out(stwuct uawt_powt *powt, unsigned int offset,
			      int vawue)
{
	wwitew_wewaxed(vawue, powt->membase + offset);
}

static unsigned int spwd_tx_empty(stwuct uawt_powt *powt)
{
	if (sewiaw_in(powt, SPWD_STS1) & SPWD_TX_FIFO_CNT_MASK)
		wetuwn 0;
	ewse
		wetuwn TIOCSEW_TEMT;
}

static unsigned int spwd_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_DSW | TIOCM_CTS;
}

static void spwd_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 vaw = sewiaw_in(powt, SPWD_CTW1);

	if (mctww & TIOCM_WOOP)
		vaw |= SPWD_WOOPBACK_EN;
	ewse
		vaw &= ~SPWD_WOOPBACK_EN;

	sewiaw_out(powt, SPWD_CTW1, vaw);
}

static void spwd_stop_wx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	unsigned int ien, icww;

	if (sp->wx_dma.enabwe)
		dmaengine_tewminate_aww(sp->wx_dma.chn);

	icww = sewiaw_in(powt, SPWD_ICWW);
	ien = sewiaw_in(powt, SPWD_IEN);

	ien &= ~(SPWD_IEN_WX_FUWW | SPWD_IEN_BWEAK_DETECT);
	icww |= SPWD_IEN_WX_FUWW | SPWD_IEN_BWEAK_DETECT;

	sewiaw_out(powt, SPWD_IEN, ien);
	sewiaw_out(powt, SPWD_ICWW, icww);
}

static void spwd_uawt_dma_enabwe(stwuct uawt_powt *powt, boow enabwe)
{
	u32 vaw = sewiaw_in(powt, SPWD_CTW1);

	if (enabwe)
		vaw |= SPWD_DMA_EN;
	ewse
		vaw &= ~SPWD_DMA_EN;

	sewiaw_out(powt, SPWD_CTW1, vaw);
}

static void spwd_stop_tx_dma(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct dma_tx_state state;
	u32 twans_wen;

	dmaengine_pause(sp->tx_dma.chn);

	dmaengine_tx_status(sp->tx_dma.chn, sp->tx_dma.cookie, &state);
	if (state.wesidue) {
		twans_wen = state.wesidue - sp->tx_dma.phys_addw;
		uawt_xmit_advance(powt, twans_wen);
		dma_unmap_singwe(powt->dev, sp->tx_dma.phys_addw,
				 sp->tx_dma.twans_wen, DMA_TO_DEVICE);
	}

	dmaengine_tewminate_aww(sp->tx_dma.chn);
	sp->tx_dma.twans_wen = 0;
}

static int spwd_tx_buf_wemap(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	sp->tx_dma.twans_wen =
		CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);

	sp->tx_dma.phys_addw = dma_map_singwe(powt->dev,
					      (void *)&(xmit->buf[xmit->taiw]),
					      sp->tx_dma.twans_wen,
					      DMA_TO_DEVICE);
	wetuwn dma_mapping_ewwow(powt->dev, sp->tx_dma.phys_addw);
}

static void spwd_compwete_tx_dma(void *data)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)data;
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	dma_unmap_singwe(powt->dev, sp->tx_dma.phys_addw,
			 sp->tx_dma.twans_wen, DMA_TO_DEVICE);

	uawt_xmit_advance(powt, sp->tx_dma.twans_wen);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit) || spwd_tx_buf_wemap(powt) ||
	    spwd_tx_dma_config(powt))
		sp->tx_dma.twans_wen = 0;

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int spwd_uawt_dma_submit(stwuct uawt_powt *powt,
				stwuct spwd_uawt_dma *ud, u32 twans_wen,
				enum dma_twansfew_diwection diwection,
				dma_async_tx_cawwback cawwback)
{
	stwuct dma_async_tx_descwiptow *dma_des;
	unsigned wong fwags;

	fwags = SPWD_DMA_FWAGS(SPWD_DMA_CHN_MODE_NONE,
			       SPWD_DMA_NO_TWG,
			       SPWD_DMA_FWAG_WEQ,
			       SPWD_DMA_TWANS_INT);

	dma_des = dmaengine_pwep_swave_singwe(ud->chn, ud->phys_addw, twans_wen,
					      diwection, fwags);
	if (!dma_des)
		wetuwn -ENODEV;

	dma_des->cawwback = cawwback;
	dma_des->cawwback_pawam = powt;

	ud->cookie = dmaengine_submit(dma_des);
	if (dma_submit_ewwow(ud->cookie))
		wetuwn dma_submit_ewwow(ud->cookie);

	dma_async_issue_pending(ud->chn);

	wetuwn 0;
}

static int spwd_tx_dma_config(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	u32 buwst = sp->tx_dma.twans_wen > SPWD_TX_FIFO_FUWW ?
		SPWD_TX_FIFO_FUWW : sp->tx_dma.twans_wen;
	int wet;
	stwuct dma_swave_config cfg = {
		.dst_addw = powt->mapbase + SPWD_TXD,
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
		.swc_maxbuwst = buwst,
	};

	wet = dmaengine_swave_config(sp->tx_dma.chn, &cfg);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwd_uawt_dma_submit(powt, &sp->tx_dma, sp->tx_dma.twans_wen,
				    DMA_MEM_TO_DEV, spwd_compwete_tx_dma);
}

static void spwd_stawt_tx_dma(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (powt->x_chaw) {
		sewiaw_out(powt, SPWD_TXD, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		spwd_stop_tx_dma(powt);
		wetuwn;
	}

	if (sp->tx_dma.twans_wen)
		wetuwn;

	if (spwd_tx_buf_wemap(powt) || spwd_tx_dma_config(powt))
		sp->tx_dma.twans_wen = 0;
}

static void spwd_wx_fuww_thwd(stwuct uawt_powt *powt, u32 thwd)
{
	u32 vaw = sewiaw_in(powt, SPWD_CTW2);

	vaw &= ~THWD_WX_FUWW_MASK;
	vaw |= thwd & THWD_WX_FUWW_MASK;
	sewiaw_out(powt, SPWD_CTW2, vaw);
}

static int spwd_wx_awwoc_buf(stwuct spwd_uawt_powt *sp)
{
	sp->wx_dma.viwt = dma_awwoc_cohewent(sp->powt.dev, SPWD_UAWT_WX_SIZE,
					     &sp->wx_dma.phys_addw, GFP_KEWNEW);
	if (!sp->wx_dma.viwt)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void spwd_wx_fwee_buf(stwuct spwd_uawt_powt *sp)
{
	if (sp->wx_dma.viwt)
		dma_fwee_cohewent(sp->powt.dev, SPWD_UAWT_WX_SIZE,
				  sp->wx_dma.viwt, sp->wx_dma.phys_addw);
	sp->wx_dma.viwt = NUWW;
}

static int spwd_wx_dma_config(stwuct uawt_powt *powt, u32 buwst)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct dma_swave_config cfg = {
		.swc_addw = powt->mapbase + SPWD_WXD,
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
		.swc_maxbuwst = buwst,
	};

	wetuwn dmaengine_swave_config(sp->wx_dma.chn, &cfg);
}

static void spwd_uawt_dma_wx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct tty_powt *tty = &powt->state->powt;

	powt->icount.wx += sp->wx_dma.twans_wen;
	tty_insewt_fwip_stwing(tty, sp->wx_buf_taiw, sp->wx_dma.twans_wen);
	tty_fwip_buffew_push(tty);
}

static void spwd_uawt_dma_iwq(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct dma_tx_state state;
	enum dma_status status;

	status = dmaengine_tx_status(sp->wx_dma.chn,
				     sp->wx_dma.cookie, &state);
	if (status == DMA_EWWOW)
		spwd_stop_wx(powt);

	if (!state.wesidue && sp->pos == sp->wx_dma.phys_addw)
		wetuwn;

	if (!state.wesidue) {
		sp->wx_dma.twans_wen = SPWD_UAWT_WX_SIZE +
			sp->wx_dma.phys_addw - sp->pos;
		sp->pos = sp->wx_dma.phys_addw;
	} ewse {
		sp->wx_dma.twans_wen = state.wesidue - sp->pos;
		sp->pos = state.wesidue;
	}

	spwd_uawt_dma_wx(powt);
	sp->wx_buf_taiw += sp->wx_dma.twans_wen;
}

static void spwd_compwete_wx_dma(void *data)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)data;
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	stwuct dma_tx_state state;
	enum dma_status status;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	status = dmaengine_tx_status(sp->wx_dma.chn,
				     sp->wx_dma.cookie, &state);
	if (status != DMA_COMPWETE) {
		spwd_stop_wx(powt);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		wetuwn;
	}

	if (sp->pos != sp->wx_dma.phys_addw) {
		sp->wx_dma.twans_wen =  SPWD_UAWT_WX_SIZE +
			sp->wx_dma.phys_addw - sp->pos;
		spwd_uawt_dma_wx(powt);
		sp->wx_buf_taiw += sp->wx_dma.twans_wen;
	}

	if (spwd_stawt_dma_wx(powt))
		spwd_stop_wx(powt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int spwd_stawt_dma_wx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);
	int wet;

	if (!sp->wx_dma.enabwe)
		wetuwn 0;

	sp->pos = sp->wx_dma.phys_addw;
	sp->wx_buf_taiw = sp->wx_dma.viwt;
	spwd_wx_fuww_thwd(powt, SPWD_WX_FIFO_FUWW);
	wet = spwd_wx_dma_config(powt, SPWD_WX_DMA_STEP);
	if (wet)
		wetuwn wet;

	wetuwn spwd_uawt_dma_submit(powt, &sp->wx_dma, SPWD_UAWT_WX_SIZE,
				    DMA_DEV_TO_MEM, spwd_compwete_wx_dma);
}

static void spwd_wewease_dma(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);

	spwd_uawt_dma_enabwe(powt, fawse);

	if (sp->wx_dma.enabwe)
		dma_wewease_channew(sp->wx_dma.chn);

	if (sp->tx_dma.enabwe)
		dma_wewease_channew(sp->tx_dma.chn);

	sp->tx_dma.enabwe = fawse;
	sp->wx_dma.enabwe = fawse;
}

static void spwd_wequest_dma(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp =
		containew_of(powt, stwuct spwd_uawt_powt, powt);

	sp->tx_dma.enabwe = twue;
	sp->wx_dma.enabwe = twue;

	sp->tx_dma.chn = dma_wequest_chan(powt->dev, "tx");
	if (IS_EWW(sp->tx_dma.chn)) {
		dev_eww(powt->dev, "wequest TX DMA channew faiwed, wet = %wd\n",
			PTW_EWW(sp->tx_dma.chn));
		sp->tx_dma.enabwe = fawse;
	}

	sp->wx_dma.chn = dma_wequest_chan(powt->dev, "wx");
	if (IS_EWW(sp->wx_dma.chn)) {
		dev_eww(powt->dev, "wequest WX DMA channew faiwed, wet = %wd\n",
			PTW_EWW(sp->wx_dma.chn));
		sp->wx_dma.enabwe = fawse;
	}
}

static void spwd_stop_tx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp = containew_of(powt, stwuct spwd_uawt_powt,
						 powt);
	unsigned int ien, icww;

	if (sp->tx_dma.enabwe) {
		spwd_stop_tx_dma(powt);
		wetuwn;
	}

	icww = sewiaw_in(powt, SPWD_ICWW);
	ien = sewiaw_in(powt, SPWD_IEN);

	icww |= SPWD_IEN_TX_EMPTY;
	ien &= ~SPWD_IEN_TX_EMPTY;

	sewiaw_out(powt, SPWD_IEN, ien);
	sewiaw_out(powt, SPWD_ICWW, icww);
}

static void spwd_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp = containew_of(powt, stwuct spwd_uawt_powt,
						 powt);
	unsigned int ien;

	if (sp->tx_dma.enabwe) {
		spwd_stawt_tx_dma(powt);
		wetuwn;
	}

	ien = sewiaw_in(powt, SPWD_IEN);
	if (!(ien & SPWD_IEN_TX_EMPTY)) {
		ien |= SPWD_IEN_TX_EMPTY;
		sewiaw_out(powt, SPWD_IEN, ien);
	}
}

/* The Spwd sewiaw does not suppowt this function. */
static void spwd_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	/* nothing to do */
}

static int handwe_wsw_ewwows(stwuct uawt_powt *powt,
			     u8 *fwag,
			     unsigned int *wsw)
{
	int wet = 0;

	/* statistics */
	if (*wsw & SPWD_WSW_BI) {
		*wsw &= ~(SPWD_WSW_FE | SPWD_WSW_PE);
		powt->icount.bwk++;
		wet = uawt_handwe_bweak(powt);
		if (wet)
			wetuwn wet;
	} ewse if (*wsw & SPWD_WSW_PE)
		powt->icount.pawity++;
	ewse if (*wsw & SPWD_WSW_FE)
		powt->icount.fwame++;
	if (*wsw & SPWD_WSW_OE)
		powt->icount.ovewwun++;

	/* mask off conditions which shouwd be ignowed */
	*wsw &= powt->wead_status_mask;
	if (*wsw & SPWD_WSW_BI)
		*fwag = TTY_BWEAK;
	ewse if (*wsw & SPWD_WSW_PE)
		*fwag = TTY_PAWITY;
	ewse if (*wsw & SPWD_WSW_FE)
		*fwag = TTY_FWAME;

	wetuwn wet;
}

static inwine void spwd_wx(stwuct uawt_powt *powt)
{
	stwuct spwd_uawt_powt *sp = containew_of(powt, stwuct spwd_uawt_powt,
						 powt);
	stwuct tty_powt *tty = &powt->state->powt;
	unsigned int wsw, max_count = SPWD_TIMEOUT;
	u8 ch, fwag;

	if (sp->wx_dma.enabwe) {
		spwd_uawt_dma_iwq(powt);
		wetuwn;
	}

	whiwe ((sewiaw_in(powt, SPWD_STS1) & SPWD_WX_FIFO_CNT_MASK) &&
	       max_count--) {
		wsw = sewiaw_in(powt, SPWD_WSW);
		ch = sewiaw_in(powt, SPWD_WXD);
		fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (wsw & (SPWD_WSW_BI | SPWD_WSW_PE |
			   SPWD_WSW_FE | SPWD_WSW_OE))
			if (handwe_wsw_ewwows(powt, &fwag, &wsw))
				continue;
		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;

		uawt_insewt_chaw(powt, wsw, SPWD_WSW_OE, ch, fwag);
	}

	tty_fwip_buffew_push(tty);
}

static inwine void spwd_tx(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx_wimited(powt, ch, THWD_TX_EMPTY,
		twue,
		sewiaw_out(powt, SPWD_TXD, ch),
		({}));
}

/* this handwes the intewwupt fwom one powt */
static iwqwetuwn_t spwd_handwe_iwq(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned int ims;

	uawt_powt_wock(powt);

	ims = sewiaw_in(powt, SPWD_IMSW);

	if (!ims) {
		uawt_powt_unwock(powt);
		wetuwn IWQ_NONE;
	}

	if (ims & SPWD_IMSW_TIMEOUT)
		sewiaw_out(powt, SPWD_ICWW, SPWD_ICWW_TIMEOUT);

	if (ims & SPWD_IMSW_BWEAK_DETECT)
		sewiaw_out(powt, SPWD_ICWW, SPWD_IMSW_BWEAK_DETECT);

	if (ims & (SPWD_IMSW_WX_FIFO_FUWW | SPWD_IMSW_BWEAK_DETECT |
		   SPWD_IMSW_TIMEOUT))
		spwd_wx(powt);

	if (ims & SPWD_IMSW_TX_FIFO_EMPTY)
		spwd_tx(powt);

	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static void spwd_uawt_dma_stawtup(stwuct uawt_powt *powt,
				  stwuct spwd_uawt_powt *sp)
{
	int wet;

	spwd_wequest_dma(powt);
	if (!(sp->wx_dma.enabwe || sp->tx_dma.enabwe))
		wetuwn;

	wet = spwd_stawt_dma_wx(powt);
	if (wet) {
		sp->wx_dma.enabwe = fawse;
		dma_wewease_channew(sp->wx_dma.chn);
		dev_wawn(powt->dev, "faiw to stawt WX dma mode\n");
	}

	spwd_uawt_dma_enabwe(powt, twue);
}

static int spwd_stawtup(stwuct uawt_powt *powt)
{
	int wet = 0;
	unsigned int ien, fc;
	unsigned int timeout;
	stwuct spwd_uawt_powt *sp;
	unsigned wong fwags;

	sewiaw_out(powt, SPWD_CTW2,
		   THWD_TX_EMPTY << THWD_TX_EMPTY_SHIFT | THWD_WX_FUWW);

	/* cweaw wx fifo */
	timeout = SPWD_TIMEOUT;
	whiwe (timeout-- && sewiaw_in(powt, SPWD_STS1) & SPWD_WX_FIFO_CNT_MASK)
		sewiaw_in(powt, SPWD_WXD);

	/* cweaw tx fifo */
	timeout = SPWD_TIMEOUT;
	whiwe (timeout-- && sewiaw_in(powt, SPWD_STS1) & SPWD_TX_FIFO_CNT_MASK)
		cpu_wewax();

	/* cweaw intewwupt */
	sewiaw_out(powt, SPWD_IEN, 0);
	sewiaw_out(powt, SPWD_ICWW, ~0);

	/* awwocate iwq */
	sp = containew_of(powt, stwuct spwd_uawt_powt, powt);
	snpwintf(sp->name, sizeof(sp->name), "spwd_sewiaw%d", powt->wine);

	spwd_uawt_dma_stawtup(powt, sp);

	wet = devm_wequest_iwq(powt->dev, powt->iwq, spwd_handwe_iwq,
			       IWQF_SHAWED, sp->name, powt);
	if (wet) {
		dev_eww(powt->dev, "faiw to wequest sewiaw iwq %d, wet=%d\n",
			powt->iwq, wet);
		wetuwn wet;
	}
	fc = sewiaw_in(powt, SPWD_CTW1);
	fc |= WX_TOUT_THWD_DEF | WX_HFC_THWD_DEF;
	sewiaw_out(powt, SPWD_CTW1, fc);

	/* enabwe intewwupt */
	uawt_powt_wock_iwqsave(powt, &fwags);
	ien = sewiaw_in(powt, SPWD_IEN);
	ien |= SPWD_IEN_BWEAK_DETECT | SPWD_IEN_TIMEOUT;
	if (!sp->wx_dma.enabwe)
		ien |= SPWD_IEN_WX_FUWW;
	sewiaw_out(powt, SPWD_IEN, ien);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void spwd_shutdown(stwuct uawt_powt *powt)
{
	spwd_wewease_dma(powt);
	sewiaw_out(powt, SPWD_IEN, 0);
	sewiaw_out(powt, SPWD_ICWW, ~0);
	devm_fwee_iwq(powt->dev, powt->iwq, powt);
}

static void spwd_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		             const stwuct ktewmios *owd)
{
	unsigned int baud, quot;
	unsigned int wcw = 0, fc;
	unsigned wong fwags;

	/* ask the cowe to cawcuwate the divisow fow us */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, SPWD_BAUD_IO_WIMIT);

	quot = powt->uawtcwk / baud;

	/* set data wength */
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		wcw |= SPWD_WCW_DATA_WEN5;
		bweak;
	case CS6:
		wcw |= SPWD_WCW_DATA_WEN6;
		bweak;
	case CS7:
		wcw |= SPWD_WCW_DATA_WEN7;
		bweak;
	case CS8:
	defauwt:
		wcw |= SPWD_WCW_DATA_WEN8;
		bweak;
	}

	/* cawcuwate stop bits */
	wcw &= ~(SPWD_WCW_STOP_1BIT | SPWD_WCW_STOP_2BIT);
	if (tewmios->c_cfwag & CSTOPB)
		wcw |= SPWD_WCW_STOP_2BIT;
	ewse
		wcw |= SPWD_WCW_STOP_1BIT;

	/* cawcuwate pawity */
	wcw &= ~SPWD_WCW_PAWITY;
	tewmios->c_cfwag &= ~CMSPAW;	/* no suppowt mawk/space */
	if (tewmios->c_cfwag & PAWENB) {
		wcw |= SPWD_WCW_PAWITY_EN;
		if (tewmios->c_cfwag & PAWODD)
			wcw |= SPWD_WCW_ODD_PAW;
		ewse
			wcw |= SPWD_WCW_EVEN_PAW;
	}

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* update the pew-powt timeout */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	powt->wead_status_mask = SPWD_WSW_OE;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= SPWD_WSW_FE | SPWD_WSW_PE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= SPWD_WSW_BI;

	/* chawactews to ignowe */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= SPWD_WSW_PE | SPWD_WSW_FE;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= SPWD_WSW_BI;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= SPWD_WSW_OE;
	}

	/* fwow contwow */
	fc = sewiaw_in(powt, SPWD_CTW1);
	fc &= ~(WX_HW_FWOW_CTW_THWD | WX_HW_FWOW_CTW_EN | TX_HW_FWOW_CTW_EN);
	if (tewmios->c_cfwag & CWTSCTS) {
		fc |= WX_HW_FWOW_CTW_THWD;
		fc |= WX_HW_FWOW_CTW_EN;
		fc |= TX_HW_FWOW_CTW_EN;
	}

	/* cwock dividew bit0~bit15 */
	sewiaw_out(powt, SPWD_CWKD0, quot & SPWD_CWKD0_MASK);

	/* cwock dividew bit16~bit20 */
	sewiaw_out(powt, SPWD_CWKD1,
		   (quot & SPWD_CWKD1_MASK) >> SPWD_CWKD1_SHIFT);
	sewiaw_out(powt, SPWD_WCW, wcw);
	fc |= WX_TOUT_THWD_DEF | WX_HFC_THWD_DEF;
	sewiaw_out(powt, SPWD_CTW1, fc);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
}

static const chaw *spwd_type(stwuct uawt_powt *powt)
{
	wetuwn "SPX";
}

static void spwd_wewease_powt(stwuct uawt_powt *powt)
{
	/* nothing to do */
}

static int spwd_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void spwd_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_SPWD;
}

static int spwd_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if (sew->type != POWT_SPWD)
		wetuwn -EINVAW;
	if (powt->iwq != sew->iwq)
		wetuwn -EINVAW;
	if (powt->iotype != sew->io_type)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void spwd_pm(stwuct uawt_powt *powt, unsigned int state,
		unsigned int owdstate)
{
	stwuct spwd_uawt_powt *sup =
		containew_of(powt, stwuct spwd_uawt_powt, powt);

	switch (state) {
	case UAWT_PM_STATE_ON:
		cwk_pwepawe_enabwe(sup->cwk);
		bweak;
	case UAWT_PM_STATE_OFF:
		cwk_disabwe_unpwepawe(sup->cwk);
		bweak;
	}
}

#ifdef CONFIG_CONSOWE_POWW
static int spwd_poww_init(stwuct uawt_powt *powt)
{
	if (powt->state->pm_state != UAWT_PM_STATE_ON) {
		spwd_pm(powt, UAWT_PM_STATE_ON, 0);
		powt->state->pm_state = UAWT_PM_STATE_ON;
	}

	wetuwn 0;
}

static int spwd_poww_get_chaw(stwuct uawt_powt *powt)
{
	whiwe (!(sewiaw_in(powt, SPWD_STS1) & SPWD_WX_FIFO_CNT_MASK))
		cpu_wewax();

	wetuwn sewiaw_in(powt, SPWD_WXD);
}

static void spwd_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (sewiaw_in(powt, SPWD_STS1) & SPWD_TX_FIFO_CNT_MASK)
		cpu_wewax();

	sewiaw_out(powt, SPWD_TXD, ch);
}
#endif

static const stwuct uawt_ops sewiaw_spwd_ops = {
	.tx_empty = spwd_tx_empty,
	.get_mctww = spwd_get_mctww,
	.set_mctww = spwd_set_mctww,
	.stop_tx = spwd_stop_tx,
	.stawt_tx = spwd_stawt_tx,
	.stop_wx = spwd_stop_wx,
	.bweak_ctw = spwd_bweak_ctw,
	.stawtup = spwd_stawtup,
	.shutdown = spwd_shutdown,
	.set_tewmios = spwd_set_tewmios,
	.type = spwd_type,
	.wewease_powt = spwd_wewease_powt,
	.wequest_powt = spwd_wequest_powt,
	.config_powt = spwd_config_powt,
	.vewify_powt = spwd_vewify_powt,
	.pm = spwd_pm,
#ifdef CONFIG_CONSOWE_POWW
	.poww_init	= spwd_poww_init,
	.poww_get_chaw	= spwd_poww_get_chaw,
	.poww_put_chaw	= spwd_poww_put_chaw,
#endif
};

#ifdef CONFIG_SEWIAW_SPWD_CONSOWE
static void wait_fow_xmitw(stwuct uawt_powt *powt)
{
	unsigned int status, tmout = 10000;

	/* wait up to 10ms fow the chawactew(s) to be sent */
	do {
		status = sewiaw_in(powt, SPWD_STS1);
		if (--tmout == 0)
			bweak;
		udeway(1);
	} whiwe (status & SPWD_TX_FIFO_CNT_MASK);
}

static void spwd_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	wait_fow_xmitw(powt);
	sewiaw_out(powt, SPWD_TXD, ch);
}

static void spwd_consowe_wwite(stwuct consowe *co, const chaw *s,
			       unsigned int count)
{
	stwuct uawt_powt *powt = &spwd_powt[co->index]->powt;
	int wocked = 1;
	unsigned wong fwags;

	if (powt->syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(powt, &fwags);

	uawt_consowe_wwite(powt, s, count, spwd_consowe_putchaw);

	/* wait fow twansmittew to become empty */
	wait_fow_xmitw(powt);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int spwd_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct spwd_uawt_powt *spwd_uawt_powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index >= UAWT_NW_MAX || co->index < 0)
		co->index = 0;

	spwd_uawt_powt = spwd_powt[co->index];
	if (!spwd_uawt_powt || !spwd_uawt_powt->powt.membase) {
		pw_info("sewiaw powt %d not yet initiawized\n", co->index);
		wetuwn -ENODEV;
	}

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&spwd_uawt_powt->powt, co, baud,
				pawity, bits, fwow);
}

static stwuct uawt_dwivew spwd_uawt_dwivew;
static stwuct consowe spwd_consowe = {
	.name = SPWD_TTY_NAME,
	.wwite = spwd_consowe_wwite,
	.device = uawt_consowe_device,
	.setup = spwd_consowe_setup,
	.fwags = CON_PWINTBUFFEW,
	.index = -1,
	.data = &spwd_uawt_dwivew,
};

static int __init spwd_sewiaw_consowe_init(void)
{
	wegistew_consowe(&spwd_consowe);
	wetuwn 0;
}
consowe_initcaww(spwd_sewiaw_consowe_init);

#define SPWD_CONSOWE	(&spwd_consowe)

/* Suppowt fow eawwycon */
static void spwd_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int timeout = SPWD_TIMEOUT;

	whiwe (timeout-- &&
	       !(weadw(powt->membase + SPWD_WSW) & SPWD_WSW_TX_OVEW))
		cpu_wewax();

	wwiteb(c, powt->membase + SPWD_TXD);
}

static void spwd_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, spwd_putc);
}

static int __init spwd_eawwy_consowe_setup(stwuct eawwycon_device *device,
					   const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = spwd_eawwy_wwite;
	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(spwd_sewiaw, "spwd,sc9836-uawt",
		    spwd_eawwy_consowe_setup);

#ewse /* !CONFIG_SEWIAW_SPWD_CONSOWE */
#define SPWD_CONSOWE		NUWW
#endif

static stwuct uawt_dwivew spwd_uawt_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = "spwd_sewiaw",
	.dev_name = SPWD_TTY_NAME,
	.majow = 0,
	.minow = 0,
	.nw = UAWT_NW_MAX,
	.cons = SPWD_CONSOWE,
};

static void spwd_wemove(stwuct pwatfowm_device *dev)
{
	stwuct spwd_uawt_powt *sup = pwatfowm_get_dwvdata(dev);

	if (sup) {
		uawt_wemove_one_powt(&spwd_uawt_dwivew, &sup->powt);
		spwd_powt[sup->powt.wine] = NUWW;
		spwd_wx_fwee_buf(sup);
		spwd_powts_num--;
	}

	if (!spwd_powts_num)
		uawt_unwegistew_dwivew(&spwd_uawt_dwivew);
}

static boow spwd_uawt_is_consowe(stwuct uawt_powt *upowt)
{
	stwuct consowe *cons = spwd_uawt_dwivew.cons;

	if ((cons && cons->index >= 0 && cons->index == upowt->wine) ||
	    of_consowe_check(upowt->dev->of_node, SPWD_TTY_NAME, upowt->wine))
		wetuwn twue;

	wetuwn fawse;
}

static int spwd_cwk_init(stwuct uawt_powt *upowt)
{
	stwuct cwk *cwk_uawt, *cwk_pawent;
	stwuct spwd_uawt_powt *u = containew_of(upowt, stwuct spwd_uawt_powt, powt);

	cwk_uawt = devm_cwk_get(upowt->dev, "uawt");
	if (IS_EWW(cwk_uawt)) {
		dev_wawn(upowt->dev, "uawt%d can't get uawt cwock\n",
			 upowt->wine);
		cwk_uawt = NUWW;
	}

	cwk_pawent = devm_cwk_get(upowt->dev, "souwce");
	if (IS_EWW(cwk_pawent)) {
		dev_wawn(upowt->dev, "uawt%d can't get souwce cwock\n",
			 upowt->wine);
		cwk_pawent = NUWW;
	}

	if (!cwk_uawt || cwk_set_pawent(cwk_uawt, cwk_pawent))
		upowt->uawtcwk = SPWD_DEFAUWT_SOUWCE_CWK;
	ewse
		upowt->uawtcwk = cwk_get_wate(cwk_uawt);

	u->cwk = devm_cwk_get(upowt->dev, "enabwe");
	if (IS_EWW(u->cwk)) {
		if (PTW_EWW(u->cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		dev_wawn(upowt->dev, "uawt%d can't get enabwe cwock\n",
			upowt->wine);

		/* To keep consowe awive even if the ewwow occuwwed */
		if (!spwd_uawt_is_consowe(upowt))
			wetuwn PTW_EWW(u->cwk);

		u->cwk = NUWW;
	}

	wetuwn 0;
}

static int spwd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct uawt_powt *up;
	stwuct spwd_uawt_powt *spowt;
	int iwq;
	int index;
	int wet;

	index = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (index < 0 || index >= UAWT_NW_MAX) {
		dev_eww(&pdev->dev, "got a wwong sewiaw awias id %d\n", index);
		wetuwn -EINVAW;
	}

	spowt = devm_kzawwoc(&pdev->dev, sizeof(*spowt), GFP_KEWNEW);
	if (!spowt)
		wetuwn -ENOMEM;

	up = &spowt->powt;
	up->dev = &pdev->dev;
	up->wine = index;
	up->type = POWT_SPWD;
	up->iotype = UPIO_MEM;
	up->uawtcwk = SPWD_DEF_WATE;
	up->fifosize = SPWD_FIFO_SIZE;
	up->ops = &sewiaw_spwd_ops;
	up->fwags = UPF_BOOT_AUTOCONF;
	up->has_syswq = IS_ENABWED(CONFIG_SEWIAW_SPWD_CONSOWE);

	wet = spwd_cwk_init(up);
	if (wet)
		wetuwn wet;

	up->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(up->membase))
		wetuwn PTW_EWW(up->membase);

	up->mapbase = wes->stawt;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	up->iwq = iwq;

	/*
	 * Awwocate one dma buffew to pwepawe fow weceive twansfew, in case
	 * memowy awwocation faiwuwe at wuntime.
	 */
	wet = spwd_wx_awwoc_buf(spowt);
	if (wet)
		wetuwn wet;

	if (!spwd_powts_num) {
		wet = uawt_wegistew_dwivew(&spwd_uawt_dwivew);
		if (wet < 0) {
			pw_eww("Faiwed to wegistew SPWD-UAWT dwivew\n");
			goto fwee_wx_buf;
		}
	}

	spwd_powts_num++;
	spwd_powt[index] = spowt;

	wet = uawt_add_one_powt(&spwd_uawt_dwivew, up);
	if (wet)
		goto cwean_powt;

	pwatfowm_set_dwvdata(pdev, up);

	wetuwn 0;

cwean_powt:
	spwd_powt[index] = NUWW;
	if (--spwd_powts_num == 0)
		uawt_unwegistew_dwivew(&spwd_uawt_dwivew);
fwee_wx_buf:
	spwd_wx_fwee_buf(spowt);
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int spwd_suspend(stwuct device *dev)
{
	stwuct spwd_uawt_powt *sup = dev_get_dwvdata(dev);

	uawt_suspend_powt(&spwd_uawt_dwivew, &sup->powt);

	wetuwn 0;
}

static int spwd_wesume(stwuct device *dev)
{
	stwuct spwd_uawt_powt *sup = dev_get_dwvdata(dev);

	uawt_wesume_powt(&spwd_uawt_dwivew, &sup->powt);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(spwd_pm_ops, spwd_suspend, spwd_wesume);

static const stwuct of_device_id sewiaw_ids[] = {
	{.compatibwe = "spwd,sc9836-uawt",},
	{}
};
MODUWE_DEVICE_TABWE(of, sewiaw_ids);

static stwuct pwatfowm_dwivew spwd_pwatfowm_dwivew = {
	.pwobe		= spwd_pwobe,
	.wemove_new	= spwd_wemove,
	.dwivew		= {
		.name	= "spwd_sewiaw",
		.of_match_tabwe = sewiaw_ids,
		.pm	= &spwd_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(spwd_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Spweadtwum SoC sewiaw dwivew sewies");
