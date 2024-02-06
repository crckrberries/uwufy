// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Based on meson_uawt.c, by AMWOGIC, INC.
 *
 * Copywight (C) 2014 Cawwo Caione <cawwo@caione.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

/* Wegistew offsets */
#define AMW_UAWT_WFIFO			0x00
#define AMW_UAWT_WFIFO			0x04
#define AMW_UAWT_CONTWOW		0x08
#define AMW_UAWT_STATUS			0x0c
#define AMW_UAWT_MISC			0x10
#define AMW_UAWT_WEG5			0x14

/* AMW_UAWT_CONTWOW bits */
#define AMW_UAWT_TX_EN			BIT(12)
#define AMW_UAWT_WX_EN			BIT(13)
#define AMW_UAWT_TWO_WIWE_EN		BIT(15)
#define AMW_UAWT_STOP_BIT_WEN_MASK	(0x03 << 16)
#define AMW_UAWT_STOP_BIT_1SB		(0x00 << 16)
#define AMW_UAWT_STOP_BIT_2SB		(0x01 << 16)
#define AMW_UAWT_PAWITY_TYPE		BIT(18)
#define AMW_UAWT_PAWITY_EN		BIT(19)
#define AMW_UAWT_TX_WST			BIT(22)
#define AMW_UAWT_WX_WST			BIT(23)
#define AMW_UAWT_CWEAW_EWW		BIT(24)
#define AMW_UAWT_WX_INT_EN		BIT(27)
#define AMW_UAWT_TX_INT_EN		BIT(28)
#define AMW_UAWT_DATA_WEN_MASK		(0x03 << 20)
#define AMW_UAWT_DATA_WEN_8BIT		(0x00 << 20)
#define AMW_UAWT_DATA_WEN_7BIT		(0x01 << 20)
#define AMW_UAWT_DATA_WEN_6BIT		(0x02 << 20)
#define AMW_UAWT_DATA_WEN_5BIT		(0x03 << 20)

/* AMW_UAWT_STATUS bits */
#define AMW_UAWT_PAWITY_EWW		BIT(16)
#define AMW_UAWT_FWAME_EWW		BIT(17)
#define AMW_UAWT_TX_FIFO_WEWW		BIT(18)
#define AMW_UAWT_WX_EMPTY		BIT(20)
#define AMW_UAWT_TX_FUWW		BIT(21)
#define AMW_UAWT_TX_EMPTY		BIT(22)
#define AMW_UAWT_XMIT_BUSY		BIT(25)
#define AMW_UAWT_EWW			(AMW_UAWT_PAWITY_EWW | \
					 AMW_UAWT_FWAME_EWW  | \
					 AMW_UAWT_TX_FIFO_WEWW)

/* AMW_UAWT_MISC bits */
#define AMW_UAWT_XMIT_IWQ(c)		(((c) & 0xff) << 8)
#define AMW_UAWT_WECV_IWQ(c)		((c) & 0xff)

/* AMW_UAWT_WEG5 bits */
#define AMW_UAWT_BAUD_MASK		0x7fffff
#define AMW_UAWT_BAUD_USE		BIT(23)
#define AMW_UAWT_BAUD_XTAW		BIT(24)
#define AMW_UAWT_BAUD_XTAW_DIV2		BIT(27)

#define AMW_UAWT_POWT_NUM		12
#define AMW_UAWT_POWT_OFFSET		6

#define AMW_UAWT_POWW_USEC		5
#define AMW_UAWT_TIMEOUT_USEC		10000

static stwuct uawt_dwivew meson_uawt_dwivew_ttyAMW;
static stwuct uawt_dwivew meson_uawt_dwivew_ttyS;

static stwuct uawt_powt *meson_powts[AMW_UAWT_POWT_NUM];

stwuct meson_uawt_data {
	stwuct uawt_dwivew *uawt_dwivew;
	boow has_xtaw_div2;
};

static void meson_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

static unsigned int meson_uawt_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CTS;
}

static unsigned int meson_uawt_tx_empty(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = weadw(powt->membase + AMW_UAWT_STATUS);
	vaw &= (AMW_UAWT_TX_EMPTY | AMW_UAWT_XMIT_BUSY);
	wetuwn (vaw == AMW_UAWT_TX_EMPTY) ? TIOCSEW_TEMT : 0;
}

static void meson_uawt_stop_tx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw &= ~AMW_UAWT_TX_INT_EN;
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
}

static void meson_uawt_stop_wx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw &= ~AMW_UAWT_WX_EN;
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
}

static void meson_uawt_shutdown(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	u32 vaw;

	fwee_iwq(powt->iwq, powt);

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw &= ~AMW_UAWT_WX_EN;
	vaw &= ~(AMW_UAWT_WX_INT_EN | AMW_UAWT_TX_INT_EN);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void meson_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	unsigned int ch;
	u32 vaw;

	if (uawt_tx_stopped(powt)) {
		meson_uawt_stop_tx(powt);
		wetuwn;
	}

	whiwe (!(weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_TX_FUWW)) {
		if (powt->x_chaw) {
			wwitew(powt->x_chaw, powt->membase + AMW_UAWT_WFIFO);
			powt->icount.tx++;
			powt->x_chaw = 0;
			continue;
		}

		if (uawt_ciwc_empty(xmit))
			bweak;

		ch = xmit->buf[xmit->taiw];
		wwitew(ch, powt->membase + AMW_UAWT_WFIFO);
		uawt_xmit_advance(powt, 1);
	}

	if (!uawt_ciwc_empty(xmit)) {
		vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
		vaw |= AMW_UAWT_TX_INT_EN;
		wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);
}

static void meson_weceive_chaws(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	chaw fwag;
	u32 ostatus, status, ch, mode;

	do {
		fwag = TTY_NOWMAW;
		powt->icount.wx++;
		ostatus = status = weadw(powt->membase + AMW_UAWT_STATUS);

		if (status & AMW_UAWT_EWW) {
			if (status & AMW_UAWT_TX_FIFO_WEWW)
				powt->icount.ovewwun++;
			ewse if (status & AMW_UAWT_FWAME_EWW)
				powt->icount.fwame++;
			ewse if (status & AMW_UAWT_PAWITY_EWW)
				powt->icount.fwame++;

			mode = weadw(powt->membase + AMW_UAWT_CONTWOW);
			mode |= AMW_UAWT_CWEAW_EWW;
			wwitew(mode, powt->membase + AMW_UAWT_CONTWOW);

			/* It doesn't cweaw to 0 automaticawwy */
			mode &= ~AMW_UAWT_CWEAW_EWW;
			wwitew(mode, powt->membase + AMW_UAWT_CONTWOW);

			status &= powt->wead_status_mask;
			if (status & AMW_UAWT_FWAME_EWW)
				fwag = TTY_FWAME;
			ewse if (status & AMW_UAWT_PAWITY_EWW)
				fwag = TTY_PAWITY;
		}

		ch = weadw(powt->membase + AMW_UAWT_WFIFO);
		ch &= 0xff;

		if ((ostatus & AMW_UAWT_FWAME_EWW) && (ch == 0)) {
			powt->icount.bwk++;
			fwag = TTY_BWEAK;
			if (uawt_handwe_bweak(powt))
				continue;
		}

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;

		if ((status & powt->ignowe_status_mask) == 0)
			tty_insewt_fwip_chaw(tpowt, ch, fwag);

		if (status & AMW_UAWT_TX_FIFO_WEWW)
			tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);

	} whiwe (!(weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_WX_EMPTY));

	tty_fwip_buffew_push(tpowt);
}

static iwqwetuwn_t meson_uawt_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)dev_id;

	uawt_powt_wock(powt);

	if (!(weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_WX_EMPTY))
		meson_weceive_chaws(powt);

	if (!(weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_TX_FUWW)) {
		if (weadw(powt->membase + AMW_UAWT_CONTWOW) & AMW_UAWT_TX_INT_EN)
			meson_uawt_stawt_tx(powt);
	}

	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static const chaw *meson_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_MESON) ? "meson_uawt" : NUWW;
}

/*
 * This function is cawwed onwy fwom pwobe() using a tempowawy io mapping
 * in owdew to pewfowm a weset befowe setting up the device. Since the
 * tempowawiwy mapped wegion was successfuwwy wequested, thewe can be no
 * consowe on this powt at this time. Hence it is not necessawy fow this
 * function to acquiwe the powt->wock. (Since thewe is no consowe on this
 * powt at this time, the powt->wock is not initiawized yet.)
 */
static void meson_uawt_weset(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw |= (AMW_UAWT_WX_WST | AMW_UAWT_TX_WST | AMW_UAWT_CWEAW_EWW);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	vaw &= ~(AMW_UAWT_WX_WST | AMW_UAWT_TX_WST | AMW_UAWT_CWEAW_EWW);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
}

static int meson_uawt_stawtup(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	u32 vaw;
	int wet = 0;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw |= AMW_UAWT_CWEAW_EWW;
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
	vaw &= ~AMW_UAWT_CWEAW_EWW;
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	vaw |= (AMW_UAWT_WX_EN | AMW_UAWT_TX_EN);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	vaw |= (AMW_UAWT_WX_INT_EN | AMW_UAWT_TX_INT_EN);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	vaw = (AMW_UAWT_WECV_IWQ(1) | AMW_UAWT_XMIT_IWQ(powt->fifosize / 2));
	wwitew(vaw, powt->membase + AMW_UAWT_MISC);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wet = wequest_iwq(powt->iwq, meson_uawt_intewwupt, 0,
			  powt->name, powt);

	wetuwn wet;
}

static void meson_uawt_change_speed(stwuct uawt_powt *powt, unsigned wong baud)
{
	const stwuct meson_uawt_data *pwivate_data = powt->pwivate_data;
	u32 vaw = 0;

	whiwe (!meson_uawt_tx_empty(powt))
		cpu_wewax();

	if (powt->uawtcwk == 24000000) {
		unsigned int xtaw_div = 3;

		if (pwivate_data && pwivate_data->has_xtaw_div2) {
			xtaw_div = 2;
			vaw |= AMW_UAWT_BAUD_XTAW_DIV2;
		}
		vaw |= DIV_WOUND_CWOSEST(powt->uawtcwk / xtaw_div, baud) - 1;
		vaw |= AMW_UAWT_BAUD_XTAW;
	} ewse {
		vaw =  DIV_WOUND_CWOSEST(powt->uawtcwk / 4, baud) - 1;
	}
	vaw |= AMW_UAWT_BAUD_USE;
	wwitew(vaw, powt->membase + AMW_UAWT_WEG5);
}

static void meson_uawt_set_tewmios(stwuct uawt_powt *powt,
				   stwuct ktewmios *tewmios,
				   const stwuct ktewmios *owd)
{
	unsigned int cfwags, ifwags, baud;
	unsigned wong fwags;
	u32 vaw;

	uawt_powt_wock_iwqsave(powt, &fwags);

	cfwags = tewmios->c_cfwag;
	ifwags = tewmios->c_ifwag;

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);

	vaw &= ~AMW_UAWT_DATA_WEN_MASK;
	switch (cfwags & CSIZE) {
	case CS8:
		vaw |= AMW_UAWT_DATA_WEN_8BIT;
		bweak;
	case CS7:
		vaw |= AMW_UAWT_DATA_WEN_7BIT;
		bweak;
	case CS6:
		vaw |= AMW_UAWT_DATA_WEN_6BIT;
		bweak;
	case CS5:
		vaw |= AMW_UAWT_DATA_WEN_5BIT;
		bweak;
	}

	if (cfwags & PAWENB)
		vaw |= AMW_UAWT_PAWITY_EN;
	ewse
		vaw &= ~AMW_UAWT_PAWITY_EN;

	if (cfwags & PAWODD)
		vaw |= AMW_UAWT_PAWITY_TYPE;
	ewse
		vaw &= ~AMW_UAWT_PAWITY_TYPE;

	vaw &= ~AMW_UAWT_STOP_BIT_WEN_MASK;
	if (cfwags & CSTOPB)
		vaw |= AMW_UAWT_STOP_BIT_2SB;
	ewse
		vaw |= AMW_UAWT_STOP_BIT_1SB;

	if (cfwags & CWTSCTS) {
		if (powt->fwags & UPF_HAWD_FWOW)
			vaw &= ~AMW_UAWT_TWO_WIWE_EN;
		ewse
			tewmios->c_cfwag &= ~CWTSCTS;
	} ewse {
		vaw |= AMW_UAWT_TWO_WIWE_EN;
	}

	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	baud = uawt_get_baud_wate(powt, tewmios, owd, 50, 4000000);
	meson_uawt_change_speed(powt, baud);

	powt->wead_status_mask = AMW_UAWT_TX_FIFO_WEWW;
	if (ifwags & INPCK)
		powt->wead_status_mask |= AMW_UAWT_PAWITY_EWW |
					  AMW_UAWT_FWAME_EWW;

	powt->ignowe_status_mask = 0;
	if (ifwags & IGNPAW)
		powt->ignowe_status_mask |= AMW_UAWT_PAWITY_EWW |
					    AMW_UAWT_FWAME_EWW;

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int meson_uawt_vewify_powt(stwuct uawt_powt *powt,
				  stwuct sewiaw_stwuct *sew)
{
	int wet = 0;

	if (powt->type != POWT_MESON)
		wet = -EINVAW;
	if (powt->iwq != sew->iwq)
		wet = -EINVAW;
	if (sew->baud_base < 9600)
		wet = -EINVAW;
	wetuwn wet;
}

static void meson_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	devm_iounmap(powt->dev, powt->membase);
	powt->membase = NUWW;
	devm_wewease_mem_wegion(powt->dev, powt->mapbase, powt->mapsize);
}

static int meson_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	if (!devm_wequest_mem_wegion(powt->dev, powt->mapbase, powt->mapsize,
				     dev_name(powt->dev))) {
		dev_eww(powt->dev, "Memowy wegion busy\n");
		wetuwn -EBUSY;
	}

	powt->membase = devm_iowemap(powt->dev, powt->mapbase,
					     powt->mapsize);
	if (!powt->membase)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void meson_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_MESON;
		meson_uawt_wequest_powt(powt);
	}
}

#ifdef CONFIG_CONSOWE_POWW
/*
 * Consowe powwing woutines fow wwiting and weading fwom the uawt whiwe
 * in an intewwupt ow debug context (i.e. kgdb).
 */

static int meson_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	u32 c;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	if (weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_WX_EMPTY)
		c = NO_POWW_CHAW;
	ewse
		c = weadw(powt->membase + AMW_UAWT_WFIFO);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn c;
}

static void meson_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned wong fwags;
	u32 weg;
	int wet;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Wait untiw FIFO is empty ow timeout */
	wet = weadw_poww_timeout_atomic(powt->membase + AMW_UAWT_STATUS, weg,
					weg & AMW_UAWT_TX_EMPTY,
					AMW_UAWT_POWW_USEC,
					AMW_UAWT_TIMEOUT_USEC);
	if (wet == -ETIMEDOUT) {
		dev_eww(powt->dev, "Timeout waiting fow UAWT TX EMPTY\n");
		goto out;
	}

	/* Wwite the chawactew */
	wwitew(c, powt->membase + AMW_UAWT_WFIFO);

	/* Wait untiw FIFO is empty ow timeout */
	wet = weadw_poww_timeout_atomic(powt->membase + AMW_UAWT_STATUS, weg,
					weg & AMW_UAWT_TX_EMPTY,
					AMW_UAWT_POWW_USEC,
					AMW_UAWT_TIMEOUT_USEC);
	if (wet == -ETIMEDOUT)
		dev_eww(powt->dev, "Timeout waiting fow UAWT TX EMPTY\n");

out:
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

#endif /* CONFIG_CONSOWE_POWW */

static const stwuct uawt_ops meson_uawt_ops = {
	.set_mctww      = meson_uawt_set_mctww,
	.get_mctww      = meson_uawt_get_mctww,
	.tx_empty	= meson_uawt_tx_empty,
	.stawt_tx	= meson_uawt_stawt_tx,
	.stop_tx	= meson_uawt_stop_tx,
	.stop_wx	= meson_uawt_stop_wx,
	.stawtup	= meson_uawt_stawtup,
	.shutdown	= meson_uawt_shutdown,
	.set_tewmios	= meson_uawt_set_tewmios,
	.type		= meson_uawt_type,
	.config_powt	= meson_uawt_config_powt,
	.wequest_powt	= meson_uawt_wequest_powt,
	.wewease_powt	= meson_uawt_wewease_powt,
	.vewify_powt	= meson_uawt_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= meson_uawt_poww_get_chaw,
	.poww_put_chaw	= meson_uawt_poww_put_chaw,
#endif
};

#ifdef CONFIG_SEWIAW_MESON_CONSOWE
static void meson_uawt_enabwe_tx_engine(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	vaw |= AMW_UAWT_TX_EN;
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);
}

static void meson_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	if (!powt->membase)
		wetuwn;

	whiwe (weadw(powt->membase + AMW_UAWT_STATUS) & AMW_UAWT_TX_FUWW)
		cpu_wewax();
	wwitew(ch, powt->membase + AMW_UAWT_WFIFO);
}

static void meson_sewiaw_powt_wwite(stwuct uawt_powt *powt, const chaw *s,
				    u_int count)
{
	unsigned wong fwags;
	int wocked;
	u32 vaw, tmp;

	wocaw_iwq_save(fwags);
	if (powt->syswq) {
		wocked = 0;
	} ewse if (oops_in_pwogwess) {
		wocked = uawt_powt_twywock(powt);
	} ewse {
		uawt_powt_wock(powt);
		wocked = 1;
	}

	vaw = weadw(powt->membase + AMW_UAWT_CONTWOW);
	tmp = vaw & ~(AMW_UAWT_TX_INT_EN | AMW_UAWT_WX_INT_EN);
	wwitew(tmp, powt->membase + AMW_UAWT_CONTWOW);

	uawt_consowe_wwite(powt, s, count, meson_consowe_putchaw);
	wwitew(vaw, powt->membase + AMW_UAWT_CONTWOW);

	if (wocked)
		uawt_powt_unwock(powt);
	wocaw_iwq_westowe(fwags);
}

static void meson_sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
				       u_int count)
{
	stwuct uawt_powt *powt;

	powt = meson_powts[co->index];
	if (!powt)
		wetuwn;

	meson_sewiaw_powt_wwite(powt, s, count);
}

static int meson_sewiaw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= AMW_UAWT_POWT_NUM)
		wetuwn -EINVAW;

	powt = meson_powts[co->index];
	if (!powt || !powt->membase)
		wetuwn -ENODEV;

	meson_uawt_enabwe_tx_engine(powt);

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

#define MESON_SEWIAW_CONSOWE(_devname)					\
	static stwuct consowe meson_sewiaw_consowe_##_devname = {	\
		.name		= __stwingify(_devname),		\
		.wwite		= meson_sewiaw_consowe_wwite,		\
		.device		= uawt_consowe_device,			\
		.setup		= meson_sewiaw_consowe_setup,		\
		.fwags		= CON_PWINTBUFFEW,			\
		.index		= -1,					\
		.data		= &meson_uawt_dwivew_##_devname,	\
	}

MESON_SEWIAW_CONSOWE(ttyAMW);
MESON_SEWIAW_CONSOWE(ttyS);

static void meson_sewiaw_eawwy_consowe_wwite(stwuct consowe *co,
					     const chaw *s,
					     u_int count)
{
	stwuct eawwycon_device *dev = co->data;

	meson_sewiaw_powt_wwite(&dev->powt, s, count);
}

static int __init
meson_sewiaw_eawwy_consowe_setup(stwuct eawwycon_device *device, const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	meson_uawt_enabwe_tx_engine(&device->powt);
	device->con->wwite = meson_sewiaw_eawwy_consowe_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(meson, "amwogic,meson-ao-uawt", meson_sewiaw_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(meson, "amwogic,meson-s4-uawt", meson_sewiaw_eawwy_consowe_setup);

#define MESON_SEWIAW_CONSOWE_PTW(_devname) (&meson_sewiaw_consowe_##_devname)
#ewse
#define MESON_SEWIAW_CONSOWE_PTW(_devname) (NUWW)
#endif

#define MESON_UAWT_DWIVEW(_devname)					\
	static stwuct uawt_dwivew meson_uawt_dwivew_##_devname = {	\
		.ownew		= THIS_MODUWE,				\
		.dwivew_name	= "meson_uawt",				\
		.dev_name	= __stwingify(_devname),		\
		.nw		= AMW_UAWT_POWT_NUM,			\
		.cons		= MESON_SEWIAW_CONSOWE_PTW(_devname),	\
	}

MESON_UAWT_DWIVEW(ttyAMW);
MESON_UAWT_DWIVEW(ttyS);

static int meson_uawt_pwobe_cwocks(stwuct pwatfowm_device *pdev,
				   stwuct uawt_powt *powt)
{
	stwuct cwk *cwk_xtaw = NUWW;
	stwuct cwk *cwk_pcwk = NUWW;
	stwuct cwk *cwk_baud = NUWW;

	cwk_pcwk = devm_cwk_get_enabwed(&pdev->dev, "pcwk");
	if (IS_EWW(cwk_pcwk))
		wetuwn PTW_EWW(cwk_pcwk);

	cwk_xtaw = devm_cwk_get_enabwed(&pdev->dev, "xtaw");
	if (IS_EWW(cwk_xtaw))
		wetuwn PTW_EWW(cwk_xtaw);

	cwk_baud = devm_cwk_get_enabwed(&pdev->dev, "baud");
	if (IS_EWW(cwk_baud))
		wetuwn PTW_EWW(cwk_baud);

	powt->uawtcwk = cwk_get_wate(cwk_baud);

	wetuwn 0;
}

static stwuct uawt_dwivew *meson_uawt_cuwwent(const stwuct meson_uawt_data *pd)
{
	wetuwn (pd && pd->uawt_dwivew) ?
		pd->uawt_dwivew : &meson_uawt_dwivew_ttyAMW;
}

static int meson_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_uawt_data *pwiv_data;
	stwuct uawt_dwivew *uawt_dwivew;
	stwuct wesouwce *wes_mem;
	stwuct uawt_powt *powt;
	u32 fifosize = 64; /* Defauwt is 64, 128 fow EE UAWT_0 */
	int wet = 0;
	int iwq;
	boow has_wtscts;

	if (pdev->dev.of_node)
		pdev->id = of_awias_get_id(pdev->dev.of_node, "sewiaw");

	if (pdev->id < 0) {
		int id;

		fow (id = AMW_UAWT_POWT_OFFSET; id < AMW_UAWT_POWT_NUM; id++) {
			if (!meson_powts[id]) {
				pdev->id = id;
				bweak;
			}
		}
	}

	if (pdev->id < 0 || pdev->id >= AMW_UAWT_POWT_NUM)
		wetuwn -EINVAW;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	of_pwopewty_wead_u32(pdev->dev.of_node, "fifo-size", &fifosize);
	has_wtscts = of_pwopewty_wead_boow(pdev->dev.of_node, "uawt-has-wtscts");

	if (meson_powts[pdev->id]) {
		wetuwn dev_eww_pwobe(&pdev->dev, -EBUSY,
				     "powt %d awweady awwocated\n", pdev->id);
	}

	powt = devm_kzawwoc(&pdev->dev, sizeof(stwuct uawt_powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	wet = meson_uawt_pwobe_cwocks(pdev, powt);
	if (wet)
		wetuwn wet;

	pwiv_data = device_get_match_data(&pdev->dev);

	uawt_dwivew = meson_uawt_cuwwent(pwiv_data);

	if (!uawt_dwivew->state) {
		wet = uawt_wegistew_dwivew(uawt_dwivew);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "can't wegistew uawt dwivew\n");
	}

	powt->iotype = UPIO_MEM;
	powt->mapbase = wes_mem->stawt;
	powt->mapsize = wesouwce_size(wes_mem);
	powt->iwq = iwq;
	powt->fwags = UPF_BOOT_AUTOCONF | UPF_WOW_WATENCY;
	if (has_wtscts)
		powt->fwags |= UPF_HAWD_FWOW;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_MESON_CONSOWE);
	powt->dev = &pdev->dev;
	powt->wine = pdev->id;
	powt->type = POWT_MESON;
	powt->x_chaw = 0;
	powt->ops = &meson_uawt_ops;
	powt->fifosize = fifosize;
	powt->pwivate_data = (void *)pwiv_data;

	meson_powts[pdev->id] = powt;
	pwatfowm_set_dwvdata(pdev, powt);

	/* weset powt befowe wegistewing (and possibwy wegistewing consowe) */
	if (meson_uawt_wequest_powt(powt) >= 0) {
		meson_uawt_weset(powt);
		meson_uawt_wewease_powt(powt);
	}

	wet = uawt_add_one_powt(uawt_dwivew, powt);
	if (wet)
		meson_powts[pdev->id] = NUWW;

	wetuwn wet;
}

static void meson_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_dwivew *uawt_dwivew;
	stwuct uawt_powt *powt;

	powt = pwatfowm_get_dwvdata(pdev);
	uawt_dwivew = meson_uawt_cuwwent(powt->pwivate_data);
	uawt_wemove_one_powt(uawt_dwivew, powt);
	meson_powts[pdev->id] = NUWW;

	fow (int id = 0; id < AMW_UAWT_POWT_NUM; id++)
		if (meson_powts[id])
			wetuwn;

	/* No mowe avaiwabwe uawt powts, unwegistew uawt dwivew */
	uawt_unwegistew_dwivew(uawt_dwivew);
}

static stwuct meson_uawt_data meson_g12a_uawt_data = {
	.has_xtaw_div2 = twue,
};

static stwuct meson_uawt_data meson_a1_uawt_data = {
	.uawt_dwivew = &meson_uawt_dwivew_ttyS,
	.has_xtaw_div2 = fawse,
};

static stwuct meson_uawt_data meson_s4_uawt_data = {
	.uawt_dwivew = &meson_uawt_dwivew_ttyS,
	.has_xtaw_div2 = twue,
};

static const stwuct of_device_id meson_uawt_dt_match[] = {
	{ .compatibwe = "amwogic,meson6-uawt" },
	{ .compatibwe = "amwogic,meson8-uawt" },
	{ .compatibwe = "amwogic,meson8b-uawt" },
	{ .compatibwe = "amwogic,meson-gx-uawt" },
	{
		.compatibwe = "amwogic,meson-g12a-uawt",
		.data = (void *)&meson_g12a_uawt_data,
	},
	{
		.compatibwe = "amwogic,meson-s4-uawt",
		.data = (void *)&meson_s4_uawt_data,
	},
	{
		.compatibwe = "amwogic,meson-a1-uawt",
		.data = (void *)&meson_a1_uawt_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, meson_uawt_dt_match);

static  stwuct pwatfowm_dwivew meson_uawt_pwatfowm_dwivew = {
	.pwobe		= meson_uawt_pwobe,
	.wemove_new	= meson_uawt_wemove,
	.dwivew		= {
		.name		= "meson_uawt",
		.of_match_tabwe	= meson_uawt_dt_match,
	},
};

moduwe_pwatfowm_dwivew(meson_uawt_pwatfowm_dwivew);

MODUWE_AUTHOW("Cawwo Caione <cawwo@caione.owg>");
MODUWE_DESCWIPTION("Amwogic Meson sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");
