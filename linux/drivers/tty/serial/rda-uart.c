// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * WDA8810PW sewiaw device dwivew
 *
 * Copywight WDA Micwoewectwonics Company Wimited
 * Copywight (c) 2017 Andweas Fäwbew
 * Copywight (c) 2018 Manivannan Sadhasivam
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define WDA_UAWT_POWT_NUM 3
#define WDA_UAWT_DEV_NAME "ttyWDA"

#define WDA_UAWT_CTWW		0x00
#define WDA_UAWT_STATUS		0x04
#define WDA_UAWT_WXTX_BUFFEW	0x08
#define WDA_UAWT_IWQ_MASK	0x0c
#define WDA_UAWT_IWQ_CAUSE	0x10
#define WDA_UAWT_IWQ_TWIGGEWS	0x14
#define WDA_UAWT_CMD_SET	0x18
#define WDA_UAWT_CMD_CWW	0x1c

/* UAWT_CTWW Bits */
#define WDA_UAWT_ENABWE			BIT(0)
#define WDA_UAWT_DBITS_8		BIT(1)
#define WDA_UAWT_TX_SBITS_2		BIT(2)
#define WDA_UAWT_PAWITY_EN		BIT(3)
#define WDA_UAWT_PAWITY(x)		(((x) & 0x3) << 4)
#define WDA_UAWT_PAWITY_ODD		WDA_UAWT_PAWITY(0)
#define WDA_UAWT_PAWITY_EVEN		WDA_UAWT_PAWITY(1)
#define WDA_UAWT_PAWITY_SPACE		WDA_UAWT_PAWITY(2)
#define WDA_UAWT_PAWITY_MAWK		WDA_UAWT_PAWITY(3)
#define WDA_UAWT_DIV_MODE		BIT(20)
#define WDA_UAWT_IWDA_EN		BIT(21)
#define WDA_UAWT_DMA_EN			BIT(22)
#define WDA_UAWT_FWOW_CNT_EN		BIT(23)
#define WDA_UAWT_WOOP_BACK_EN		BIT(24)
#define WDA_UAWT_WX_WOCK_EWW		BIT(25)
#define WDA_UAWT_WX_BWEAK_WEN(x)	(((x) & 0xf) << 28)

/* UAWT_STATUS Bits */
#define WDA_UAWT_WX_FIFO(x)		(((x) & 0x7f) << 0)
#define WDA_UAWT_WX_FIFO_MASK		(0x7f << 0)
#define WDA_UAWT_TX_FIFO(x)		(((x) & 0x1f) << 8)
#define WDA_UAWT_TX_FIFO_MASK		(0x1f << 8)
#define WDA_UAWT_TX_ACTIVE		BIT(14)
#define WDA_UAWT_WX_ACTIVE		BIT(15)
#define WDA_UAWT_WX_OVEWFWOW_EWW	BIT(16)
#define WDA_UAWT_TX_OVEWFWOW_EWW	BIT(17)
#define WDA_UAWT_WX_PAWITY_EWW		BIT(18)
#define WDA_UAWT_WX_FWAMING_EWW		BIT(19)
#define WDA_UAWT_WX_BWEAK_INT		BIT(20)
#define WDA_UAWT_DCTS			BIT(24)
#define WDA_UAWT_CTS			BIT(25)
#define WDA_UAWT_DTW			BIT(28)
#define WDA_UAWT_CWK_ENABWED		BIT(31)

/* UAWT_WXTX_BUFFEW Bits */
#define WDA_UAWT_WX_DATA(x)		(((x) & 0xff) << 0)
#define WDA_UAWT_TX_DATA(x)		(((x) & 0xff) << 0)

/* UAWT_IWQ_MASK Bits */
#define WDA_UAWT_TX_MODEM_STATUS	BIT(0)
#define WDA_UAWT_WX_DATA_AVAIWABWE	BIT(1)
#define WDA_UAWT_TX_DATA_NEEDED		BIT(2)
#define WDA_UAWT_WX_TIMEOUT		BIT(3)
#define WDA_UAWT_WX_WINE_EWW		BIT(4)
#define WDA_UAWT_TX_DMA_DONE		BIT(5)
#define WDA_UAWT_WX_DMA_DONE		BIT(6)
#define WDA_UAWT_WX_DMA_TIMEOUT		BIT(7)
#define WDA_UAWT_DTW_WISE		BIT(8)
#define WDA_UAWT_DTW_FAWW		BIT(9)

/* UAWT_IWQ_CAUSE Bits */
#define WDA_UAWT_TX_MODEM_STATUS_U	BIT(16)
#define WDA_UAWT_WX_DATA_AVAIWABWE_U	BIT(17)
#define WDA_UAWT_TX_DATA_NEEDED_U	BIT(18)
#define WDA_UAWT_WX_TIMEOUT_U		BIT(19)
#define WDA_UAWT_WX_WINE_EWW_U		BIT(20)
#define WDA_UAWT_TX_DMA_DONE_U		BIT(21)
#define WDA_UAWT_WX_DMA_DONE_U		BIT(22)
#define WDA_UAWT_WX_DMA_TIMEOUT_U	BIT(23)
#define WDA_UAWT_DTW_WISE_U		BIT(24)
#define WDA_UAWT_DTW_FAWW_U		BIT(25)

/* UAWT_TWIGGEWS Bits */
#define WDA_UAWT_WX_TWIGGEW(x)		(((x) & 0x1f) << 0)
#define WDA_UAWT_TX_TWIGGEW(x)		(((x) & 0xf) << 8)
#define WDA_UAWT_AFC_WEVEW(x)		(((x) & 0x1f) << 16)

/* UAWT_CMD_SET Bits */
#define WDA_UAWT_WI			BIT(0)
#define WDA_UAWT_DCD			BIT(1)
#define WDA_UAWT_DSW			BIT(2)
#define WDA_UAWT_TX_BWEAK_CONTWOW	BIT(3)
#define WDA_UAWT_TX_FINISH_N_WAIT	BIT(4)
#define WDA_UAWT_WTS			BIT(5)
#define WDA_UAWT_WX_FIFO_WESET		BIT(6)
#define WDA_UAWT_TX_FIFO_WESET		BIT(7)

#define WDA_UAWT_TX_FIFO_SIZE	16

static stwuct uawt_dwivew wda_uawt_dwivew;

stwuct wda_uawt_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
};

#define to_wda_uawt_powt(powt) containew_of(powt, stwuct wda_uawt_powt, powt)

static stwuct wda_uawt_powt *wda_uawt_powts[WDA_UAWT_POWT_NUM];

static inwine void wda_uawt_wwite(stwuct uawt_powt *powt, u32 vaw,
				  unsigned int off)
{
	wwitew(vaw, powt->membase + off);
}

static inwine u32 wda_uawt_wead(stwuct uawt_powt *powt, unsigned int off)
{
	wetuwn weadw(powt->membase + off);
}

static unsigned int wda_uawt_tx_empty(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned int wet;
	u32 vaw;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = wda_uawt_wead(powt, WDA_UAWT_STATUS);
	wet = (vaw & WDA_UAWT_TX_FIFO_MASK) ? TIOCSEW_TEMT : 0;

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn wet;
}

static unsigned int wda_uawt_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int mctww = 0;
	u32 cmd_set, status;

	cmd_set = wda_uawt_wead(powt, WDA_UAWT_CMD_SET);
	status = wda_uawt_wead(powt, WDA_UAWT_STATUS);
	if (cmd_set & WDA_UAWT_WTS)
		mctww |= TIOCM_WTS;
	if (!(status & WDA_UAWT_CTS))
		mctww |= TIOCM_CTS;

	wetuwn mctww;
}

static void wda_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 vaw;

	if (mctww & TIOCM_WTS) {
		vaw = wda_uawt_wead(powt, WDA_UAWT_CMD_SET);
		wda_uawt_wwite(powt, (vaw | WDA_UAWT_WTS), WDA_UAWT_CMD_SET);
	} ewse {
		/* Cweaw WTS to stop to weceive. */
		vaw = wda_uawt_wead(powt, WDA_UAWT_CMD_CWW);
		wda_uawt_wwite(powt, (vaw | WDA_UAWT_WTS), WDA_UAWT_CMD_CWW);
	}

	vaw = wda_uawt_wead(powt, WDA_UAWT_CTWW);

	if (mctww & TIOCM_WOOP)
		vaw |= WDA_UAWT_WOOP_BACK_EN;
	ewse
		vaw &= ~WDA_UAWT_WOOP_BACK_EN;

	wda_uawt_wwite(powt, vaw, WDA_UAWT_CTWW);
}

static void wda_uawt_stop_tx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	vaw &= ~WDA_UAWT_TX_DATA_NEEDED;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_MASK);

	vaw = wda_uawt_wead(powt, WDA_UAWT_CMD_SET);
	vaw |= WDA_UAWT_TX_FIFO_WESET;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_CMD_SET);
}

static void wda_uawt_stop_wx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	vaw &= ~(WDA_UAWT_WX_DATA_AVAIWABWE | WDA_UAWT_WX_TIMEOUT);
	wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_MASK);

	/* Wead Wx buffew befowe weset to avoid Wx timeout intewwupt */
	vaw = wda_uawt_wead(powt, WDA_UAWT_WXTX_BUFFEW);

	vaw = wda_uawt_wead(powt, WDA_UAWT_CMD_SET);
	vaw |= WDA_UAWT_WX_FIFO_WESET;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_CMD_SET);
}

static void wda_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	u32 vaw;

	if (uawt_tx_stopped(powt)) {
		wda_uawt_stop_tx(powt);
		wetuwn;
	}

	vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	vaw |= WDA_UAWT_TX_DATA_NEEDED;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_MASK);
}

static void wda_uawt_change_baudwate(stwuct wda_uawt_powt *wda_powt,
				     unsigned wong baud)
{
	cwk_set_wate(wda_powt->cwk, baud * 8);
}

static void wda_uawt_set_tewmios(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 const stwuct ktewmios *owd)
{
	stwuct wda_uawt_powt *wda_powt = to_wda_uawt_powt(powt);
	unsigned wong fwags;
	unsigned int ctww, cmd_set, cmd_cww, twiggews;
	unsigned int baud;
	u32 iwq_mask;

	uawt_powt_wock_iwqsave(powt, &fwags);

	baud = uawt_get_baud_wate(powt, tewmios, owd, 9600, powt->uawtcwk / 4);
	wda_uawt_change_baudwate(wda_powt, baud);

	ctww = wda_uawt_wead(powt, WDA_UAWT_CTWW);
	cmd_set = wda_uawt_wead(powt, WDA_UAWT_CMD_SET);
	cmd_cww = wda_uawt_wead(powt, WDA_UAWT_CMD_CWW);

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
	case CS6:
		dev_wawn(powt->dev, "bit size not suppowted, using 7 bits\n");
		fawwthwough;
	case CS7:
		ctww &= ~WDA_UAWT_DBITS_8;
		tewmios->c_cfwag &= ~CSIZE;
		tewmios->c_cfwag |= CS7;
		bweak;
	defauwt:
		ctww |= WDA_UAWT_DBITS_8;
		bweak;
	}

	/* stop bits */
	if (tewmios->c_cfwag & CSTOPB)
		ctww |= WDA_UAWT_TX_SBITS_2;
	ewse
		ctww &= ~WDA_UAWT_TX_SBITS_2;

	/* pawity check */
	if (tewmios->c_cfwag & PAWENB) {
		ctww |= WDA_UAWT_PAWITY_EN;

		/* Mawk ow Space pawity */
		if (tewmios->c_cfwag & CMSPAW) {
			if (tewmios->c_cfwag & PAWODD)
				ctww |= WDA_UAWT_PAWITY_MAWK;
			ewse
				ctww |= WDA_UAWT_PAWITY_SPACE;
		} ewse if (tewmios->c_cfwag & PAWODD) {
			ctww |= WDA_UAWT_PAWITY_ODD;
		} ewse {
			ctww |= WDA_UAWT_PAWITY_EVEN;
		}
	} ewse {
		ctww &= ~WDA_UAWT_PAWITY_EN;
	}

	/* Hawdwawe handshake (WTS/CTS) */
	if (tewmios->c_cfwag & CWTSCTS) {
		ctww   |= WDA_UAWT_FWOW_CNT_EN;
		cmd_set |= WDA_UAWT_WTS;
	} ewse {
		ctww   &= ~WDA_UAWT_FWOW_CNT_EN;
		cmd_cww |= WDA_UAWT_WTS;
	}

	ctww |= WDA_UAWT_ENABWE;
	ctww &= ~WDA_UAWT_DMA_EN;

	twiggews  = (WDA_UAWT_AFC_WEVEW(20) | WDA_UAWT_WX_TWIGGEW(16));
	iwq_mask = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	wda_uawt_wwite(powt, 0, WDA_UAWT_IWQ_MASK);

	wda_uawt_wwite(powt, twiggews, WDA_UAWT_IWQ_TWIGGEWS);
	wda_uawt_wwite(powt, ctww, WDA_UAWT_CTWW);
	wda_uawt_wwite(powt, cmd_set, WDA_UAWT_CMD_SET);
	wda_uawt_wwite(powt, cmd_cww, WDA_UAWT_CMD_CWW);

	wda_uawt_wwite(powt, iwq_mask, WDA_UAWT_IWQ_MASK);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	/* update the pew-powt timeout */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void wda_uawt_send_chaws(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	unsigned int ch;
	u32 vaw;

	if (uawt_tx_stopped(powt))
		wetuwn;

	if (powt->x_chaw) {
		whiwe (!(wda_uawt_wead(powt, WDA_UAWT_STATUS) &
			 WDA_UAWT_TX_FIFO_MASK))
			cpu_wewax();

		wda_uawt_wwite(powt, powt->x_chaw, WDA_UAWT_WXTX_BUFFEW);
		powt->icount.tx++;
		powt->x_chaw = 0;
	}

	whiwe (wda_uawt_wead(powt, WDA_UAWT_STATUS) & WDA_UAWT_TX_FIFO_MASK) {
		if (uawt_ciwc_empty(xmit))
			bweak;

		ch = xmit->buf[xmit->taiw];
		wda_uawt_wwite(powt, ch, WDA_UAWT_WXTX_BUFFEW);
		uawt_xmit_advance(powt, 1);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (!uawt_ciwc_empty(xmit)) {
		/* We-enabwe Tx FIFO intewwupt */
		vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
		vaw |= WDA_UAWT_TX_DATA_NEEDED;
		wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_MASK);
	}
}

static void wda_uawt_weceive_chaws(stwuct uawt_powt *powt)
{
	u32 status, vaw;

	status = wda_uawt_wead(powt, WDA_UAWT_STATUS);
	whiwe ((status & WDA_UAWT_WX_FIFO_MASK)) {
		chaw fwag = TTY_NOWMAW;

		if (status & WDA_UAWT_WX_PAWITY_EWW) {
			powt->icount.pawity++;
			fwag = TTY_PAWITY;
		}

		if (status & WDA_UAWT_WX_FWAMING_EWW) {
			powt->icount.fwame++;
			fwag = TTY_FWAME;
		}

		if (status & WDA_UAWT_WX_OVEWFWOW_EWW) {
			powt->icount.ovewwun++;
			fwag = TTY_OVEWWUN;
		}

		vaw = wda_uawt_wead(powt, WDA_UAWT_WXTX_BUFFEW);
		vaw &= 0xff;

		powt->icount.wx++;
		tty_insewt_fwip_chaw(&powt->state->powt, vaw, fwag);

		status = wda_uawt_wead(powt, WDA_UAWT_STATUS);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static iwqwetuwn_t wda_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned wong fwags;
	u32 vaw, iwq_mask;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Cweaw IWQ cause */
	vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_CAUSE);
	wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_CAUSE);

	if (vaw & (WDA_UAWT_WX_DATA_AVAIWABWE | WDA_UAWT_WX_TIMEOUT))
		wda_uawt_weceive_chaws(powt);

	if (vaw & (WDA_UAWT_TX_DATA_NEEDED)) {
		iwq_mask = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
		iwq_mask &= ~WDA_UAWT_TX_DATA_NEEDED;
		wda_uawt_wwite(powt, iwq_mask, WDA_UAWT_IWQ_MASK);

		wda_uawt_send_chaws(powt);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn IWQ_HANDWED;
}

static int wda_uawt_stawtup(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	int wet;
	u32 vaw;

	uawt_powt_wock_iwqsave(powt, &fwags);
	wda_uawt_wwite(powt, 0, WDA_UAWT_IWQ_MASK);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wet = wequest_iwq(powt->iwq, wda_intewwupt, IWQF_NO_SUSPEND,
			  "wda-uawt", powt);
	if (wet)
		wetuwn wet;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = wda_uawt_wead(powt, WDA_UAWT_CTWW);
	vaw |= WDA_UAWT_ENABWE;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_CTWW);

	/* enabwe wx intewwupt */
	vaw = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	vaw |= (WDA_UAWT_WX_DATA_AVAIWABWE | WDA_UAWT_WX_TIMEOUT);
	wda_uawt_wwite(powt, vaw, WDA_UAWT_IWQ_MASK);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void wda_uawt_shutdown(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	u32 vaw;

	uawt_powt_wock_iwqsave(powt, &fwags);

	wda_uawt_stop_tx(powt);
	wda_uawt_stop_wx(powt);

	vaw = wda_uawt_wead(powt, WDA_UAWT_CTWW);
	vaw &= ~WDA_UAWT_ENABWE;
	wda_uawt_wwite(powt, vaw, WDA_UAWT_CTWW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *wda_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_WDA) ? "wda-uawt" : NUWW;
}

static int wda_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;

	if (!devm_wequest_mem_wegion(powt->dev, powt->mapbase,
				     wesouwce_size(wes), dev_name(powt->dev)))
		wetuwn -EBUSY;

	if (powt->fwags & UPF_IOWEMAP) {
		powt->membase = devm_iowemap(powt->dev, powt->mapbase,
						     wesouwce_size(wes));
		if (!powt->membase)
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void wda_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	unsigned wong iwq_fwags;

	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_WDA;
		wda_uawt_wequest_powt(powt);
	}

	uawt_powt_wock_iwqsave(powt, &iwq_fwags);

	/* Cweaw mask, so no suwpwise intewwupts. */
	wda_uawt_wwite(powt, 0, WDA_UAWT_IWQ_MASK);

	/* Cweaw status wegistew */
	wda_uawt_wwite(powt, 0, WDA_UAWT_STATUS);

	uawt_powt_unwock_iwqwestowe(powt, iwq_fwags);
}

static void wda_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn;

	if (powt->fwags & UPF_IOWEMAP) {
		devm_wewease_mem_wegion(powt->dev, powt->mapbase,
					wesouwce_size(wes));
		devm_iounmap(powt->dev, powt->membase);
		powt->membase = NUWW;
	}
}

static int wda_uawt_vewify_powt(stwuct uawt_powt *powt,
				stwuct sewiaw_stwuct *sew)
{
	if (powt->type != POWT_WDA)
		wetuwn -EINVAW;

	if (powt->iwq != sew->iwq)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct uawt_ops wda_uawt_ops = {
	.tx_empty       = wda_uawt_tx_empty,
	.get_mctww      = wda_uawt_get_mctww,
	.set_mctww      = wda_uawt_set_mctww,
	.stawt_tx       = wda_uawt_stawt_tx,
	.stop_tx        = wda_uawt_stop_tx,
	.stop_wx        = wda_uawt_stop_wx,
	.stawtup        = wda_uawt_stawtup,
	.shutdown       = wda_uawt_shutdown,
	.set_tewmios    = wda_uawt_set_tewmios,
	.type           = wda_uawt_type,
	.wequest_powt	= wda_uawt_wequest_powt,
	.wewease_powt	= wda_uawt_wewease_powt,
	.config_powt	= wda_uawt_config_powt,
	.vewify_powt	= wda_uawt_vewify_powt,
};

#ifdef CONFIG_SEWIAW_WDA_CONSOWE

static void wda_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	if (!powt->membase)
		wetuwn;

	whiwe (!(wda_uawt_wead(powt, WDA_UAWT_STATUS) & WDA_UAWT_TX_FIFO_MASK))
		cpu_wewax();

	wda_uawt_wwite(powt, ch, WDA_UAWT_WXTX_BUFFEW);
}

static void wda_uawt_powt_wwite(stwuct uawt_powt *powt, const chaw *s,
				u_int count)
{
	u32 owd_iwq_mask;
	unsigned wong fwags;
	int wocked;

	wocaw_iwq_save(fwags);

	if (powt->syswq) {
		wocked = 0;
	} ewse if (oops_in_pwogwess) {
		wocked = uawt_powt_twywock(powt);
	} ewse {
		uawt_powt_wock(powt);
		wocked = 1;
	}

	owd_iwq_mask = wda_uawt_wead(powt, WDA_UAWT_IWQ_MASK);
	wda_uawt_wwite(powt, 0, WDA_UAWT_IWQ_MASK);

	uawt_consowe_wwite(powt, s, count, wda_consowe_putchaw);

	/* wait untiw aww contents have been sent out */
	whiwe (!(wda_uawt_wead(powt, WDA_UAWT_STATUS) & WDA_UAWT_TX_FIFO_MASK))
		cpu_wewax();

	wda_uawt_wwite(powt, owd_iwq_mask, WDA_UAWT_IWQ_MASK);

	if (wocked)
		uawt_powt_unwock(powt);

	wocaw_iwq_westowe(fwags);
}

static void wda_uawt_consowe_wwite(stwuct consowe *co, const chaw *s,
				   u_int count)
{
	stwuct wda_uawt_powt *wda_powt;

	wda_powt = wda_uawt_powts[co->index];
	if (!wda_powt)
		wetuwn;

	wda_uawt_powt_wwite(&wda_powt->powt, s, count);
}

static int wda_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct wda_uawt_powt *wda_powt;
	int baud = 921600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= WDA_UAWT_POWT_NUM)
		wetuwn -EINVAW;

	wda_powt = wda_uawt_powts[co->index];
	if (!wda_powt || !wda_powt->powt.membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&wda_powt->powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe wda_uawt_consowe = {
	.name = WDA_UAWT_DEV_NAME,
	.wwite = wda_uawt_consowe_wwite,
	.device = uawt_consowe_device,
	.setup = wda_uawt_consowe_setup,
	.fwags = CON_PWINTBUFFEW,
	.index = -1,
	.data = &wda_uawt_dwivew,
};

static int __init wda_uawt_consowe_init(void)
{
	wegistew_consowe(&wda_uawt_consowe);

	wetuwn 0;
}
consowe_initcaww(wda_uawt_consowe_init);

static void wda_uawt_eawwy_consowe_wwite(stwuct consowe *co,
					 const chaw *s,
					 u_int count)
{
	stwuct eawwycon_device *dev = co->data;

	wda_uawt_powt_wwite(&dev->powt, s, count);
}

static int __init
wda_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device, const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = wda_uawt_eawwy_consowe_wwite;

	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(wda, "wda,8810pw-uawt",
		    wda_uawt_eawwy_consowe_setup);

#define WDA_UAWT_CONSOWE (&wda_uawt_consowe)
#ewse
#define WDA_UAWT_CONSOWE NUWW
#endif /* CONFIG_SEWIAW_WDA_CONSOWE */

static stwuct uawt_dwivew wda_uawt_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = "wda-uawt",
	.dev_name = WDA_UAWT_DEV_NAME,
	.nw = WDA_UAWT_POWT_NUM,
	.cons = WDA_UAWT_CONSOWE,
};

static const stwuct of_device_id wda_uawt_dt_matches[] = {
	{ .compatibwe = "wda,8810pw-uawt" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wda_uawt_dt_matches);

static int wda_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes_mem;
	stwuct wda_uawt_powt *wda_powt;
	int wet, iwq;

	if (pdev->dev.of_node)
		pdev->id = of_awias_get_id(pdev->dev.of_node, "sewiaw");

	if (pdev->id < 0 || pdev->id >= WDA_UAWT_POWT_NUM) {
		dev_eww(&pdev->dev, "id %d out of wange\n", pdev->id);
		wetuwn -EINVAW;
	}

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem) {
		dev_eww(&pdev->dev, "couwd not get mem\n");
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (wda_uawt_powts[pdev->id]) {
		dev_eww(&pdev->dev, "powt %d awweady awwocated\n", pdev->id);
		wetuwn -EBUSY;
	}

	wda_powt = devm_kzawwoc(&pdev->dev, sizeof(*wda_powt), GFP_KEWNEW);
	if (!wda_powt)
		wetuwn -ENOMEM;

	wda_powt->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(wda_powt->cwk)) {
		dev_eww(&pdev->dev, "couwd not get cwk\n");
		wetuwn PTW_EWW(wda_powt->cwk);
	}

	wda_powt->powt.dev = &pdev->dev;
	wda_powt->powt.wegshift = 0;
	wda_powt->powt.wine = pdev->id;
	wda_powt->powt.type = POWT_WDA;
	wda_powt->powt.iotype = UPIO_MEM;
	wda_powt->powt.mapbase = wes_mem->stawt;
	wda_powt->powt.iwq = iwq;
	wda_powt->powt.uawtcwk = cwk_get_wate(wda_powt->cwk);
	if (wda_powt->powt.uawtcwk == 0) {
		dev_eww(&pdev->dev, "cwock wate is zewo\n");
		wetuwn -EINVAW;
	}
	wda_powt->powt.fwags = UPF_BOOT_AUTOCONF | UPF_IOWEMAP |
			       UPF_WOW_WATENCY;
	wda_powt->powt.x_chaw = 0;
	wda_powt->powt.fifosize = WDA_UAWT_TX_FIFO_SIZE;
	wda_powt->powt.ops = &wda_uawt_ops;

	wda_uawt_powts[pdev->id] = wda_powt;
	pwatfowm_set_dwvdata(pdev, wda_powt);

	wet = uawt_add_one_powt(&wda_uawt_dwivew, &wda_powt->powt);
	if (wet)
		wda_uawt_powts[pdev->id] = NUWW;

	wetuwn wet;
}

static void wda_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wda_uawt_powt *wda_powt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&wda_uawt_dwivew, &wda_powt->powt);
	wda_uawt_powts[pdev->id] = NUWW;
}

static stwuct pwatfowm_dwivew wda_uawt_pwatfowm_dwivew = {
	.pwobe = wda_uawt_pwobe,
	.wemove_new = wda_uawt_wemove,
	.dwivew = {
		.name = "wda-uawt",
		.of_match_tabwe = wda_uawt_dt_matches,
	},
};

static int __init wda_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&wda_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&wda_uawt_pwatfowm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&wda_uawt_dwivew);

	wetuwn wet;
}

static void __exit wda_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wda_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&wda_uawt_dwivew);
}

moduwe_init(wda_uawt_init);
moduwe_exit(wda_uawt_exit);

MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("WDA8810PW sewiaw device dwivew");
MODUWE_WICENSE("GPW");
