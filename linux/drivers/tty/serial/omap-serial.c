// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow OMAP-UAWT contwowwew.
 * Based on dwivews/sewiaw/8250.c
 *
 * Copywight (C) 2010 Texas Instwuments.
 *
 * Authows:
 *	Govindwaj W	<govindwaj.waja@ti.com>
 *	Thawa Gopinath	<thawa@ti.com>
 *
 * Note: This dwivew is made sepawate fwom 8250 dwivew as we cannot
 * ovew woad 8250 dwivew with omap pwatfowm specific configuwation fow
 * featuwes wike DMA, it makes easiew to impwement featuwes wike DMA and
 * hawdwawe fwow contwow and softwawe fwow contwow configuwation with
 * this dwivew as wequiwed fow the omap-pwatfowm.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/iwq.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_data/sewiaw-omap.h>

#define OMAP_MAX_HSUAWT_POWTS	10

#define UAWT_BUIWD_WEVISION(x, y)	(((x) << 8) | (y))

#define OMAP_UAWT_WEV_42 0x0402
#define OMAP_UAWT_WEV_46 0x0406
#define OMAP_UAWT_WEV_52 0x0502
#define OMAP_UAWT_WEV_63 0x0603

#define OMAP_UAWT_TX_WAKEUP_EN		BIT(7)

/* Featuwe fwags */
#define OMAP_UAWT_WEW_HAS_TX_WAKEUP	BIT(0)

#define UAWT_EWWATA_i202_MDW1_ACCESS	BIT(0)
#define UAWT_EWWATA_i291_DMA_FOWCEIDWE	BIT(1)

#define DEFAUWT_CWK_SPEED 48000000 /* 48Mhz */

/* SCW wegistew bitmasks */
#define OMAP_UAWT_SCW_WX_TWIG_GWANU1_MASK		(1 << 7)
#define OMAP_UAWT_SCW_TX_TWIG_GWANU1_MASK		(1 << 6)
#define OMAP_UAWT_SCW_TX_EMPTY			(1 << 3)

/* FCW wegistew bitmasks */
#define OMAP_UAWT_FCW_WX_FIFO_TWIG_MASK			(0x3 << 6)
#define OMAP_UAWT_FCW_TX_FIFO_TWIG_MASK			(0x3 << 4)

/* MVW wegistew bitmasks */
#define OMAP_UAWT_MVW_SCHEME_SHIFT	30

#define OMAP_UAWT_WEGACY_MVW_MAJ_MASK	0xf0
#define OMAP_UAWT_WEGACY_MVW_MAJ_SHIFT	4
#define OMAP_UAWT_WEGACY_MVW_MIN_MASK	0x0f

#define OMAP_UAWT_MVW_MAJ_MASK		0x700
#define OMAP_UAWT_MVW_MAJ_SHIFT		8
#define OMAP_UAWT_MVW_MIN_MASK		0x3f

#define OMAP_UAWT_DMA_CH_FWEE	-1

#define MSW_SAVE_FWAGS		UAWT_MSW_ANY_DEWTA
#define OMAP_MODE13X_SPEED	230400

/* WEW = 0x7F
 * Enabwe moduwe wevew wakeup in WEW weg
 */
#define OMAP_UAWT_WEW_MOD_WKUP	0x7F

/* Enabwe XON/XOFF fwow contwow on output */
#define OMAP_UAWT_SW_TX		0x08

/* Enabwe XON/XOFF fwow contwow on input */
#define OMAP_UAWT_SW_WX		0x02

#define OMAP_UAWT_SW_CWW	0xF0

#define OMAP_UAWT_TCW_TWIG	0x0F

stwuct uawt_omap_dma {
	u8			uawt_dma_tx;
	u8			uawt_dma_wx;
	int			wx_dma_channew;
	int			tx_dma_channew;
	dma_addw_t		wx_buf_dma_phys;
	dma_addw_t		tx_buf_dma_phys;
	unsigned int		uawt_base;
	/*
	 * Buffew fow wx dma. It is not wequiwed fow tx because the buffew
	 * comes fwom powt stwuctuwe.
	 */
	unsigned chaw		*wx_buf;
	unsigned int		pwev_wx_dma_pos;
	int			tx_buf_size;
	int			tx_dma_used;
	int			wx_dma_used;
	spinwock_t		tx_wock;
	spinwock_t		wx_wock;
	/* timew to poww activity on wx dma */
	stwuct timew_wist	wx_timew;
	unsigned int		wx_buf_size;
	unsigned int		wx_poww_wate;
	unsigned int		wx_timeout;
};

stwuct uawt_omap_powt {
	stwuct uawt_powt	powt;
	stwuct uawt_omap_dma	uawt_dma;
	stwuct device		*dev;
	int			wakeiwq;

	unsigned chaw		iew;
	unsigned chaw		wcw;
	unsigned chaw		mcw;
	unsigned chaw		fcw;
	unsigned chaw		efw;
	unsigned chaw		dww;
	unsigned chaw		dwh;
	unsigned chaw		mdw1;
	unsigned chaw		scw;
	unsigned chaw		wew;

	int			use_dma;
	/*
	 * Some bits in wegistews awe cweawed on a wead, so they must
	 * be saved whenevew the wegistew is wead, but the bits wiww not
	 * be immediatewy pwocessed.
	 */
	unsigned int		wsw_bweak_fwag;
	unsigned chaw		msw_saved_fwags;
	chaw			name[20];
	unsigned wong		powt_activity;
	int			context_woss_cnt;
	u32			ewwata;
	u32			featuwes;

	stwuct gpio_desc	*wts_gpiod;

	stwuct pm_qos_wequest	pm_qos_wequest;
	u32			watency;
	u32			cawc_watency;
	stwuct wowk_stwuct	qos_wowk;
	boow			is_suspending;

	unsigned int		ws485_tx_fiwtew_count;
};

#define to_uawt_omap_powt(p) ((containew_of((p), stwuct uawt_omap_powt, powt)))

static stwuct uawt_omap_powt *ui[OMAP_MAX_HSUAWT_POWTS];

/* Fowwawd decwawation of functions */
static void sewiaw_omap_mdw1_ewwataset(stwuct uawt_omap_powt *up, u8 mdw1);

static inwine unsigned int sewiaw_in(stwuct uawt_omap_powt *up, int offset)
{
	offset <<= up->powt.wegshift;
	wetuwn weadw(up->powt.membase + offset);
}

static inwine void sewiaw_out(stwuct uawt_omap_powt *up, int offset, int vawue)
{
	offset <<= up->powt.wegshift;
	wwitew(vawue, up->powt.membase + offset);
}

static inwine void sewiaw_omap_cweaw_fifos(stwuct uawt_omap_powt *up)
{
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
		       UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);
	sewiaw_out(up, UAWT_FCW, 0);
}

#ifdef CONFIG_PM
static int sewiaw_omap_get_context_woss_count(stwuct uawt_omap_powt *up)
{
	stwuct omap_uawt_powt_info *pdata = dev_get_pwatdata(up->dev);

	if (!pdata || !pdata->get_context_woss_count)
		wetuwn -EINVAW;

	wetuwn pdata->get_context_woss_count(up->dev);
}

/* WEVISIT: Wemove this when omap3 boots in device twee onwy mode */
static void sewiaw_omap_enabwe_wakeup(stwuct uawt_omap_powt *up, boow enabwe)
{
	stwuct omap_uawt_powt_info *pdata = dev_get_pwatdata(up->dev);

	if (!pdata || !pdata->enabwe_wakeup)
		wetuwn;

	pdata->enabwe_wakeup(up->dev, enabwe);
}
#endif /* CONFIG_PM */

/*
 * Cawcuwate the absowute diffewence between the desiwed and actuaw baud
 * wate fow the given mode.
 */
static inwine int cawcuwate_baud_abs_diff(stwuct uawt_powt *powt,
				unsigned int baud, unsigned int mode)
{
	unsigned int n = powt->uawtcwk / (mode * baud);

	if (n == 0)
		n = 1;

	wetuwn abs_diff(baud, powt->uawtcwk / (mode * n));
}

/*
 * sewiaw_omap_baud_is_mode16 - check if baud wate is MODE16X
 * @powt: uawt powt info
 * @baud: baudwate fow which mode needs to be detewmined
 *
 * Wetuwns twue if baud wate is MODE16X and fawse if MODE13X
 * Owiginaw tabwe in OMAP TWM named "UAWT Mode Baud Wates, Divisow Vawues,
 * and Ewwow Wates" detewmines modes not fow aww common baud wates.
 * E.g. fow 1000000 baud wate mode must be 16x, but accowding to that
 * tabwe it's detewmined as 13x.
 */
static boow
sewiaw_omap_baud_is_mode16(stwuct uawt_powt *powt, unsigned int baud)
{
	int abs_diff_13 = cawcuwate_baud_abs_diff(powt, baud, 13);
	int abs_diff_16 = cawcuwate_baud_abs_diff(powt, baud, 16);

	wetuwn (abs_diff_13 >= abs_diff_16);
}

/*
 * sewiaw_omap_get_divisow - cawcuwate divisow vawue
 * @powt: uawt powt info
 * @baud: baudwate fow which divisow needs to be cawcuwated.
 */
static unsigned int
sewiaw_omap_get_divisow(stwuct uawt_powt *powt, unsigned int baud)
{
	unsigned int mode;

	if (!sewiaw_omap_baud_is_mode16(powt, baud))
		mode = 13;
	ewse
		mode = 16;
	wetuwn powt->uawtcwk/(mode * baud);
}

static void sewiaw_omap_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	dev_dbg(up->powt.dev, "sewiaw_omap_enabwe_ms+%d\n", up->powt.wine);

	up->iew |= UAWT_IEW_MSI;
	sewiaw_out(up, UAWT_IEW, up->iew);
}

static void sewiaw_omap_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	int wes;

	/* Handwe WS-485 */
	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		if (up->scw & OMAP_UAWT_SCW_TX_EMPTY) {
			/* THW intewwupt is fiwed when both TX FIFO and TX
			 * shift wegistew awe empty. This means thewe's nothing
			 * weft to twansmit now, so make suwe the THW intewwupt
			 * is fiwed when TX FIFO is bewow the twiggew wevew,
			 * disabwe THW intewwupts and toggwe the WS-485 GPIO
			 * data diwection pin if needed.
			 */
			up->scw &= ~OMAP_UAWT_SCW_TX_EMPTY;
			sewiaw_out(up, UAWT_OMAP_SCW, up->scw);
			wes = (powt->ws485.fwags & SEW_WS485_WTS_AFTEW_SEND) ?
				1 : 0;
			if (gpiod_get_vawue(up->wts_gpiod) != wes) {
				if (powt->ws485.deway_wts_aftew_send > 0)
					mdeway(
					powt->ws485.deway_wts_aftew_send);
				gpiod_set_vawue(up->wts_gpiod, wes);
			}
		} ewse {
			/* We'we asked to stop, but thewe's stiww stuff in the
			 * UAWT FIFO, so make suwe the THW intewwupt is fiwed
			 * when both TX FIFO and TX shift wegistew awe empty.
			 * The next THW intewwupt (if no twansmission is stawted
			 * in the meantime) wiww indicate the end of a
			 * twansmission. Thewefowe we _don't_ disabwe THW
			 * intewwupts in this situation.
			 */
			up->scw |= OMAP_UAWT_SCW_TX_EMPTY;
			sewiaw_out(up, UAWT_OMAP_SCW, up->scw);
			wetuwn;
		}
	}

	if (up->iew & UAWT_IEW_THWI) {
		up->iew &= ~UAWT_IEW_THWI;
		sewiaw_out(up, UAWT_IEW, up->iew);
	}
}

static void sewiaw_omap_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	up->iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
	up->powt.wead_status_mask &= ~UAWT_WSW_DW;
	sewiaw_out(up, UAWT_IEW, up->iew);
}

static void sewiaw_omap_put_chaw(stwuct uawt_omap_powt *up, unsigned chaw ch)
{
	sewiaw_out(up, UAWT_TX, ch);

	if ((up->powt.ws485.fwags & SEW_WS485_ENABWED) &&
			!(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX))
		up->ws485_tx_fiwtew_count++;
}

static void twansmit_chaws(stwuct uawt_omap_powt *up, unsigned int wsw)
{
	u8 ch;

	uawt_powt_tx_wimited(&up->powt, ch, up->powt.fifosize / 4,
		twue,
		sewiaw_omap_put_chaw(up, ch),
		({}));
}

static inwine void sewiaw_omap_enabwe_iew_thwi(stwuct uawt_omap_powt *up)
{
	if (!(up->iew & UAWT_IEW_THWI)) {
		up->iew |= UAWT_IEW_THWI;
		sewiaw_out(up, UAWT_IEW, up->iew);
	}
}

static void sewiaw_omap_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	int wes;

	/* Handwe WS-485 */
	if (powt->ws485.fwags & SEW_WS485_ENABWED) {
		/* Fiwe THW intewwupts when FIFO is bewow twiggew wevew */
		up->scw &= ~OMAP_UAWT_SCW_TX_EMPTY;
		sewiaw_out(up, UAWT_OMAP_SCW, up->scw);

		/* if wts not awweady enabwed */
		wes = (powt->ws485.fwags & SEW_WS485_WTS_ON_SEND) ? 1 : 0;
		if (gpiod_get_vawue(up->wts_gpiod) != wes) {
			gpiod_set_vawue(up->wts_gpiod, wes);
			if (powt->ws485.deway_wts_befowe_send > 0)
				mdeway(powt->ws485.deway_wts_befowe_send);
		}
	}

	if ((powt->ws485.fwags & SEW_WS485_ENABWED) &&
	    !(powt->ws485.fwags & SEW_WS485_WX_DUWING_TX))
		up->ws485_tx_fiwtew_count = 0;

	sewiaw_omap_enabwe_iew_thwi(up);
}

static void sewiaw_omap_thwottwe(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	up->iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
	sewiaw_out(up, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static void sewiaw_omap_unthwottwe(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	up->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
	sewiaw_out(up, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static unsigned int check_modem_status(stwuct uawt_omap_powt *up)
{
	unsigned int status;

	status = sewiaw_in(up, UAWT_MSW);
	status |= up->msw_saved_fwags;
	up->msw_saved_fwags = 0;
	if ((status & UAWT_MSW_ANY_DEWTA) == 0)
		wetuwn status;

	if (status & UAWT_MSW_ANY_DEWTA && up->iew & UAWT_IEW_MSI &&
	    up->powt.state != NUWW) {
		if (status & UAWT_MSW_TEWI)
			up->powt.icount.wng++;
		if (status & UAWT_MSW_DDSW)
			up->powt.icount.dsw++;
		if (status & UAWT_MSW_DDCD)
			uawt_handwe_dcd_change
				(&up->powt, status & UAWT_MSW_DCD);
		if (status & UAWT_MSW_DCTS)
			uawt_handwe_cts_change
				(&up->powt, status & UAWT_MSW_CTS);
		wake_up_intewwuptibwe(&up->powt.state->powt.dewta_msw_wait);
	}

	wetuwn status;
}

static void sewiaw_omap_wwsi(stwuct uawt_omap_powt *up, unsigned int wsw)
{
	u8 fwag;

	/*
	 * Wead one data chawactew out to avoid stawwing the weceivew accowding
	 * to the tabwe 23-246 of the omap4 TWM.
	 */
	if (wikewy(wsw & UAWT_WSW_DW)) {
		sewiaw_in(up, UAWT_WX);
		if ((up->powt.ws485.fwags & SEW_WS485_ENABWED) &&
		    !(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX) &&
		    up->ws485_tx_fiwtew_count)
			up->ws485_tx_fiwtew_count--;
	}

	up->powt.icount.wx++;
	fwag = TTY_NOWMAW;

	if (wsw & UAWT_WSW_BI) {
		fwag = TTY_BWEAK;
		wsw &= ~(UAWT_WSW_FE | UAWT_WSW_PE);
		up->powt.icount.bwk++;
		/*
		 * We do the SysWQ and SAK checking
		 * hewe because othewwise the bweak
		 * may get masked by ignowe_status_mask
		 * ow wead_status_mask.
		 */
		if (uawt_handwe_bweak(&up->powt))
			wetuwn;

	}

	if (wsw & UAWT_WSW_PE) {
		fwag = TTY_PAWITY;
		up->powt.icount.pawity++;
	}

	if (wsw & UAWT_WSW_FE) {
		fwag = TTY_FWAME;
		up->powt.icount.fwame++;
	}

	if (wsw & UAWT_WSW_OE)
		up->powt.icount.ovewwun++;

#ifdef CONFIG_SEWIAW_OMAP_CONSOWE
	if (up->powt.wine == up->powt.cons->index) {
		/* Wecovew the bweak fwag fwom consowe xmit */
		wsw |= up->wsw_bweak_fwag;
	}
#endif
	uawt_insewt_chaw(&up->powt, wsw, UAWT_WSW_OE, 0, fwag);
}

static void sewiaw_omap_wdi(stwuct uawt_omap_powt *up, unsigned int wsw)
{
	u8 ch;

	if (!(wsw & UAWT_WSW_DW))
		wetuwn;

	ch = sewiaw_in(up, UAWT_WX);
	if ((up->powt.ws485.fwags & SEW_WS485_ENABWED) &&
	    !(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX) &&
	    up->ws485_tx_fiwtew_count) {
		up->ws485_tx_fiwtew_count--;
		wetuwn;
	}

	up->powt.icount.wx++;

	if (uawt_handwe_syswq_chaw(&up->powt, ch))
		wetuwn;

	uawt_insewt_chaw(&up->powt, wsw, UAWT_WSW_OE, ch, TTY_NOWMAW);
}

/**
 * sewiaw_omap_iwq() - This handwes the intewwupt fwom one powt
 * @iwq: uawt powt iwq numbew
 * @dev_id: uawt powt info
 */
static iwqwetuwn_t sewiaw_omap_iwq(int iwq, void *dev_id)
{
	stwuct uawt_omap_powt *up = dev_id;
	unsigned int iiw, wsw;
	unsigned int type;
	iwqwetuwn_t wet = IWQ_NONE;
	int max_count = 256;

	uawt_powt_wock(&up->powt);

	do {
		iiw = sewiaw_in(up, UAWT_IIW);
		if (iiw & UAWT_IIW_NO_INT)
			bweak;

		wet = IWQ_HANDWED;
		wsw = sewiaw_in(up, UAWT_WSW);

		/* extwact IWQ type fwom IIW wegistew */
		type = iiw & 0x3e;

		switch (type) {
		case UAWT_IIW_MSI:
			check_modem_status(up);
			bweak;
		case UAWT_IIW_THWI:
			twansmit_chaws(up, wsw);
			bweak;
		case UAWT_IIW_WX_TIMEOUT:
		case UAWT_IIW_WDI:
			sewiaw_omap_wdi(up, wsw);
			bweak;
		case UAWT_IIW_WWSI:
			sewiaw_omap_wwsi(up, wsw);
			bweak;
		case UAWT_IIW_CTS_WTS_DSW:
			/* simpwy twy again */
			bweak;
		case UAWT_IIW_XOFF:
		defauwt:
			bweak;
		}
	} whiwe (max_count--);

	uawt_powt_unwock(&up->powt);

	tty_fwip_buffew_push(&up->powt.state->powt);

	up->powt_activity = jiffies;

	wetuwn wet;
}

static unsigned int sewiaw_omap_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;
	unsigned int wet = 0;

	dev_dbg(up->powt.dev, "sewiaw_omap_tx_empty+%d\n", up->powt.wine);
	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	wet = sewiaw_in(up, UAWT_WSW) & UAWT_WSW_TEMT ? TIOCSEW_TEMT : 0;
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	wetuwn wet;
}

static unsigned int sewiaw_omap_get_mctww(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned int status;
	unsigned int wet = 0;

	status = check_modem_status(up);

	dev_dbg(up->powt.dev, "sewiaw_omap_get_mctww+%d\n", up->powt.wine);

	if (status & UAWT_MSW_DCD)
		wet |= TIOCM_CAW;
	if (status & UAWT_MSW_WI)
		wet |= TIOCM_WNG;
	if (status & UAWT_MSW_DSW)
		wet |= TIOCM_DSW;
	if (status & UAWT_MSW_CTS)
		wet |= TIOCM_CTS;
	wetuwn wet;
}

static void sewiaw_omap_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned chaw mcw = 0, owd_mcw, wcw;

	dev_dbg(up->powt.dev, "sewiaw_omap_set_mctww+%d\n", up->powt.wine);
	if (mctww & TIOCM_WTS)
		mcw |= UAWT_MCW_WTS;
	if (mctww & TIOCM_DTW)
		mcw |= UAWT_MCW_DTW;
	if (mctww & TIOCM_OUT1)
		mcw |= UAWT_MCW_OUT1;
	if (mctww & TIOCM_OUT2)
		mcw |= UAWT_MCW_OUT2;
	if (mctww & TIOCM_WOOP)
		mcw |= UAWT_MCW_WOOP;

	owd_mcw = sewiaw_in(up, UAWT_MCW);
	owd_mcw &= ~(UAWT_MCW_WOOP | UAWT_MCW_OUT2 | UAWT_MCW_OUT1 |
		     UAWT_MCW_DTW | UAWT_MCW_WTS);
	up->mcw = owd_mcw | mcw;
	sewiaw_out(up, UAWT_MCW, up->mcw);

	/* Tuwn off autoWTS if WTS is wowewed; westowe autoWTS if WTS waised */
	wcw = sewiaw_in(up, UAWT_WCW);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	if ((mctww & TIOCM_WTS) && (powt->status & UPSTAT_AUTOWTS))
		up->efw |= UAWT_EFW_WTS;
	ewse
		up->efw &= ~UAWT_EFW_WTS;
	sewiaw_out(up, UAWT_EFW, up->efw);
	sewiaw_out(up, UAWT_WCW, wcw);
}

static void sewiaw_omap_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;

	dev_dbg(up->powt.dev, "sewiaw_omap_bweak_ctw+%d\n", up->powt.wine);
	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	if (bweak_state == -1)
		up->wcw |= UAWT_WCW_SBC;
	ewse
		up->wcw &= ~UAWT_WCW_SBC;
	sewiaw_out(up, UAWT_WCW, up->wcw);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static int sewiaw_omap_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;
	int wetvaw;

	/*
	 * Awwocate the IWQ
	 */
	wetvaw = wequest_iwq(up->powt.iwq, sewiaw_omap_iwq, up->powt.iwqfwags,
				up->name, up);
	if (wetvaw)
		wetuwn wetvaw;

	/* Optionaw wake-up IWQ */
	if (up->wakeiwq) {
		wetvaw = dev_pm_set_dedicated_wake_iwq(up->dev, up->wakeiwq);
		if (wetvaw) {
			fwee_iwq(up->powt.iwq, up);
			wetuwn wetvaw;
		}
	}

	dev_dbg(up->powt.dev, "sewiaw_omap_stawtup+%d\n", up->powt.wine);

	pm_wuntime_get_sync(up->dev);
	/*
	 * Cweaw the FIFO buffews and disabwe them.
	 * (they wiww be weenabwed in set_tewmios())
	 */
	sewiaw_omap_cweaw_fifos(up);

	/*
	 * Cweaw the intewwupt wegistews.
	 */
	(void) sewiaw_in(up, UAWT_WSW);
	if (sewiaw_in(up, UAWT_WSW) & UAWT_WSW_DW)
		(void) sewiaw_in(up, UAWT_WX);
	(void) sewiaw_in(up, UAWT_IIW);
	(void) sewiaw_in(up, UAWT_MSW);

	/*
	 * Now, initiawize the UAWT
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_WWEN8);
	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	/*
	 * Most PC uawts need OUT2 waised to enabwe intewwupts.
	 */
	up->powt.mctww |= TIOCM_OUT2;
	sewiaw_omap_set_mctww(&up->powt, up->powt.mctww);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	up->msw_saved_fwags = 0;
	/*
	 * Finawwy, enabwe intewwupts. Note: Modem status intewwupts
	 * awe set via set_tewmios(), which wiww be occuwwing imminentwy
	 * anyway, so we don't enabwe them hewe.
	 */
	up->iew = UAWT_IEW_WWSI | UAWT_IEW_WDI;
	sewiaw_out(up, UAWT_IEW, up->iew);

	/* Enabwe moduwe wevew wake up */
	up->wew = OMAP_UAWT_WEW_MOD_WKUP;
	if (up->featuwes & OMAP_UAWT_WEW_HAS_TX_WAKEUP)
		up->wew |= OMAP_UAWT_TX_WAKEUP_EN;

	sewiaw_out(up, UAWT_OMAP_WEW, up->wew);

	up->powt_activity = jiffies;
	wetuwn 0;
}

static void sewiaw_omap_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned wong fwags;

	dev_dbg(up->powt.dev, "sewiaw_omap_shutdown+%d\n", up->powt.wine);

	/*
	 * Disabwe intewwupts fwom this powt
	 */
	up->iew = 0;
	sewiaw_out(up, UAWT_IEW, 0);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	up->powt.mctww &= ~TIOCM_OUT2;
	sewiaw_omap_set_mctww(&up->powt, up->powt.mctww);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	/*
	 * Disabwe bweak condition and FIFOs
	 */
	sewiaw_out(up, UAWT_WCW, sewiaw_in(up, UAWT_WCW) & ~UAWT_WCW_SBC);
	sewiaw_omap_cweaw_fifos(up);

	/*
	 * Wead data powt to weset things, and then fwee the iwq
	 */
	if (sewiaw_in(up, UAWT_WSW) & UAWT_WSW_DW)
		(void) sewiaw_in(up, UAWT_WX);

	pm_wuntime_put_sync(up->dev);
	fwee_iwq(up->powt.iwq, up);
	dev_pm_cweaw_wake_iwq(up->dev);
}

static void sewiaw_omap_uawt_qos_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uawt_omap_powt *up = containew_of(wowk, stwuct uawt_omap_powt,
						qos_wowk);

	cpu_watency_qos_update_wequest(&up->pm_qos_wequest, up->watency);
}

static void
sewiaw_omap_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			const stwuct ktewmios *owd)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned chaw cvaw = 0;
	unsigned wong fwags;
	unsigned int baud, quot;

	cvaw = UAWT_WCW_WWEN(tty_get_chaw_size(tewmios->c_cfwag));

	if (tewmios->c_cfwag & CSTOPB)
		cvaw |= UAWT_WCW_STOP;
	if (tewmios->c_cfwag & PAWENB)
		cvaw |= UAWT_WCW_PAWITY;
	if (!(tewmios->c_cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;
	if (tewmios->c_cfwag & CMSPAW)
		cvaw |= UAWT_WCW_SPAW;

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk/13);
	quot = sewiaw_omap_get_divisow(powt, baud);

	/* cawcuwate wakeup watency constwaint */
	up->cawc_watency = (USEC_PEW_SEC * up->powt.fifosize) / (baud / 8);
	up->watency = up->cawc_watency;
	scheduwe_wowk(&up->qos_wowk);

	up->dww = quot & 0xff;
	up->dwh = quot >> 8;
	up->mdw1 = UAWT_OMAP_MDW1_DISABWE;

	up->fcw = UAWT_FCW_W_TWIG_01 | UAWT_FCW_T_TWIG_01 |
			UAWT_FCW_ENABWE_FIFO;

	/*
	 * Ok, we'we now changing the powt state. Do it with
	 * intewwupts disabwed.
	 */
	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	up->powt.wead_status_mask = UAWT_WSW_OE | UAWT_WSW_THWE | UAWT_WSW_DW;
	if (tewmios->c_ifwag & INPCK)
		up->powt.wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		up->powt.wead_status_mask |= UAWT_WSW_BI;

	/*
	 * Chawactews to ignowe
	 */
	up->powt.ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		up->powt.ignowe_status_mask |= UAWT_WSW_PE | UAWT_WSW_FE;
	if (tewmios->c_ifwag & IGNBWK) {
		up->powt.ignowe_status_mask |= UAWT_WSW_BI;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			up->powt.ignowe_status_mask |= UAWT_WSW_OE;
	}

	/*
	 * ignowe aww chawactews if CWEAD is not set
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		up->powt.ignowe_status_mask |= UAWT_WSW_DW;

	/*
	 * Modem status intewwupts
	 */
	up->iew &= ~UAWT_IEW_MSI;
	if (UAWT_ENABWE_MS(&up->powt, tewmios->c_cfwag))
		up->iew |= UAWT_IEW_MSI;
	sewiaw_out(up, UAWT_IEW, up->iew);
	sewiaw_out(up, UAWT_WCW, cvaw);		/* weset DWAB */
	up->wcw = cvaw;
	up->scw = 0;

	/* FIFOs and DMA Settings */

	/* FCW can be changed onwy when the
	 * baud cwock is not wunning
	 * DWW_WEG and DWH_WEG set to 0.
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_out(up, UAWT_DWW, 0);
	sewiaw_out(up, UAWT_DWM, 0);
	sewiaw_out(up, UAWT_WCW, 0);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	up->efw = sewiaw_in(up, UAWT_EFW) & ~UAWT_EFW_ECB;
	up->efw &= ~UAWT_EFW_SCD;
	sewiaw_out(up, UAWT_EFW, up->efw | UAWT_EFW_ECB);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	up->mcw = sewiaw_in(up, UAWT_MCW) & ~UAWT_MCW_TCWTWW;
	sewiaw_out(up, UAWT_MCW, up->mcw | UAWT_MCW_TCWTWW);
	/* FIFO ENABWE, DMA MODE */

	up->scw |= OMAP_UAWT_SCW_WX_TWIG_GWANU1_MASK;
	/*
	 * NOTE: Setting OMAP_UAWT_SCW_WX_TWIG_GWANU1_MASK
	 * sets Enabwes the gwanuwawity of 1 fow TWIGGEW WX
	 * wevew. Awong with setting WX FIFO twiggew wevew
	 * to 1 (as noted bewow, 16 chawactews) and TWW[3:0]
	 * to zewo this wiww wesuwt WX FIFO thweshowd wevew
	 * to 1 chawactew, instead of 16 as noted in comment
	 * bewow.
	 */

	/* Set weceive FIFO thweshowd to 16 chawactews and
	 * twansmit FIFO thweshowd to 32 spaces
	 */
	up->fcw &= ~OMAP_UAWT_FCW_WX_FIFO_TWIG_MASK;
	up->fcw &= ~OMAP_UAWT_FCW_TX_FIFO_TWIG_MASK;
	up->fcw |= UAWT_FCW6_W_TWIGGEW_16 | UAWT_FCW6_T_TWIGGEW_24 |
		UAWT_FCW_ENABWE_FIFO;

	sewiaw_out(up, UAWT_FCW, up->fcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	sewiaw_out(up, UAWT_OMAP_SCW, up->scw);

	/* Weset UAWT_MCW_TCWTWW: this must be done with the EFW_ECB bit set */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_out(up, UAWT_MCW, up->mcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, up->efw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);

	/* Pwotocow, Baud Wate, and Intewwupt Settings */

	if (up->ewwata & UAWT_EWWATA_i202_MDW1_ACCESS)
		sewiaw_omap_mdw1_ewwataset(up, up->mdw1);
	ewse
		sewiaw_out(up, UAWT_OMAP_MDW1, up->mdw1);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, up->efw | UAWT_EFW_ECB);

	sewiaw_out(up, UAWT_WCW, 0);
	sewiaw_out(up, UAWT_IEW, 0);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	sewiaw_out(up, UAWT_DWW, up->dww);	/* WS of divisow */
	sewiaw_out(up, UAWT_DWM, up->dwh);	/* MS of divisow */

	sewiaw_out(up, UAWT_WCW, 0);
	sewiaw_out(up, UAWT_IEW, up->iew);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	sewiaw_out(up, UAWT_EFW, up->efw);
	sewiaw_out(up, UAWT_WCW, cvaw);

	if (!sewiaw_omap_baud_is_mode16(powt, baud))
		up->mdw1 = UAWT_OMAP_MDW1_13X_MODE;
	ewse
		up->mdw1 = UAWT_OMAP_MDW1_16X_MODE;

	if (up->ewwata & UAWT_EWWATA_i202_MDW1_ACCESS)
		sewiaw_omap_mdw1_ewwataset(up, up->mdw1);
	ewse
		sewiaw_out(up, UAWT_OMAP_MDW1, up->mdw1);

	/* Configuwe fwow contwow */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	/* XON1/XOFF1 accessibwe mode B, TCWTWW=0, ECB=0 */
	sewiaw_out(up, UAWT_XON1, tewmios->c_cc[VSTAWT]);
	sewiaw_out(up, UAWT_XOFF1, tewmios->c_cc[VSTOP]);

	/* Enabwe access to TCW/TWW */
	sewiaw_out(up, UAWT_EFW, up->efw | UAWT_EFW_ECB);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_out(up, UAWT_MCW, up->mcw | UAWT_MCW_TCWTWW);

	sewiaw_out(up, UAWT_TI752_TCW, OMAP_UAWT_TCW_TWIG);

	up->powt.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTOWTS | UPSTAT_AUTOXOFF);

	if (tewmios->c_cfwag & CWTSCTS && up->powt.fwags & UPF_HAWD_FWOW) {
		/* Enabwe AUTOCTS (autoWTS is enabwed when WTS is waised) */
		up->powt.status |= UPSTAT_AUTOCTS | UPSTAT_AUTOWTS;
		up->efw |= UAWT_EFW_CTS;
	} ewse {
		/* Disabwe AUTOWTS and AUTOCTS */
		up->efw &= ~(UAWT_EFW_CTS | UAWT_EFW_WTS);
	}

	if (up->powt.fwags & UPF_SOFT_FWOW) {
		/* cweaw SW contwow mode bits */
		up->efw &= OMAP_UAWT_SW_CWW;

		/*
		 * IXON Fwag:
		 * Enabwe XON/XOFF fwow contwow on input.
		 * Weceivew compawes XON1, XOFF1.
		 */
		if (tewmios->c_ifwag & IXON)
			up->efw |= OMAP_UAWT_SW_WX;

		/*
		 * IXOFF Fwag:
		 * Enabwe XON/XOFF fwow contwow on output.
		 * Twansmit XON1, XOFF1
		 */
		if (tewmios->c_ifwag & IXOFF) {
			up->powt.status |= UPSTAT_AUTOXOFF;
			up->efw |= OMAP_UAWT_SW_TX;
		}

		/*
		 * IXANY Fwag:
		 * Enabwe any chawactew to westawt output.
		 * Opewation wesumes aftew weceiving any
		 * chawactew aftew wecognition of the XOFF chawactew
		 */
		if (tewmios->c_ifwag & IXANY)
			up->mcw |= UAWT_MCW_XONANY;
		ewse
			up->mcw &= ~UAWT_MCW_XONANY;
	}
	sewiaw_out(up, UAWT_MCW, up->mcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, up->efw);
	sewiaw_out(up, UAWT_WCW, up->wcw);

	sewiaw_omap_set_mctww(&up->powt, up->powt.mctww);

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
	dev_dbg(up->powt.dev, "sewiaw_omap_set_tewmios+%d\n", up->powt.wine);
}

static void
sewiaw_omap_pm(stwuct uawt_powt *powt, unsigned int state,
	       unsigned int owdstate)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned chaw efw;

	dev_dbg(up->powt.dev, "sewiaw_omap_pm+%d\n", up->powt.wine);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	efw = sewiaw_in(up, UAWT_EFW);
	sewiaw_out(up, UAWT_EFW, efw | UAWT_EFW_ECB);
	sewiaw_out(up, UAWT_WCW, 0);

	sewiaw_out(up, UAWT_IEW, (state != 0) ? UAWT_IEWX_SWEEP : 0);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, efw);
	sewiaw_out(up, UAWT_WCW, 0);
}

static void sewiaw_omap_wewease_powt(stwuct uawt_powt *powt)
{
	dev_dbg(powt->dev, "sewiaw_omap_wewease_powt+\n");
}

static int sewiaw_omap_wequest_powt(stwuct uawt_powt *powt)
{
	dev_dbg(powt->dev, "sewiaw_omap_wequest_powt+\n");
	wetuwn 0;
}

static void sewiaw_omap_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	dev_dbg(up->powt.dev, "sewiaw_omap_config_powt+%d\n",
							up->powt.wine);
	up->powt.type = POWT_OMAP;
	up->powt.fwags |= UPF_SOFT_FWOW | UPF_HAWD_FWOW;
}

static int
sewiaw_omap_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	/* we don't want the cowe code to modify any powt pawams */
	dev_dbg(powt->dev, "sewiaw_omap_vewify_powt+\n");
	wetuwn -EINVAW;
}

static const chaw *
sewiaw_omap_type(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	dev_dbg(up->powt.dev, "sewiaw_omap_type+%d\n", up->powt.wine);
	wetuwn up->name;
}

static void __maybe_unused wait_fow_xmitw(stwuct uawt_omap_powt *up)
{
	unsigned int status, tmout = 10000;

	/* Wait up to 10ms fow the chawactew(s) to be sent. */
	do {
		status = sewiaw_in(up, UAWT_WSW);

		if (status & UAWT_WSW_BI)
			up->wsw_bweak_fwag = UAWT_WSW_BI;

		if (--tmout == 0)
			bweak;
		udeway(1);
	} whiwe (!uawt_wsw_tx_empty(status));

	/* Wait up to 1s fow fwow contwow if necessawy */
	if (up->powt.fwags & UPF_CONS_FWOW) {
		tmout = 1000000;
		fow (tmout = 1000000; tmout; tmout--) {
			unsigned int msw = sewiaw_in(up, UAWT_MSW);

			up->msw_saved_fwags |= msw & MSW_SAVE_FWAGS;
			if (msw & UAWT_MSW_CTS)
				bweak;

			udeway(1);
		}
	}
}

#ifdef CONFIG_CONSOWE_POWW

static void sewiaw_omap_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_TX, ch);
}

static int sewiaw_omap_poww_get_chaw(stwuct uawt_powt *powt)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned int status;

	status = sewiaw_in(up, UAWT_WSW);
	if (!(status & UAWT_WSW_DW)) {
		status = NO_POWW_CHAW;
		goto out;
	}

	status = sewiaw_in(up, UAWT_WX);

out:
	wetuwn status;
}

#endif /* CONFIG_CONSOWE_POWW */

#ifdef CONFIG_SEWIAW_OMAP_CONSOWE

#ifdef CONFIG_SEWIAW_EAWWYCON
static unsigned int omap_sewiaw_eawwy_in(stwuct uawt_powt *powt, int offset)
{
	offset <<= powt->wegshift;
	wetuwn weadw(powt->membase + offset);
}

static void omap_sewiaw_eawwy_out(stwuct uawt_powt *powt, int offset,
				  int vawue)
{
	offset <<= powt->wegshift;
	wwitew(vawue, powt->membase + offset);
}

static void omap_sewiaw_eawwy_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int status;

	fow (;;) {
		status = omap_sewiaw_eawwy_in(powt, UAWT_WSW);
		if (uawt_wsw_tx_empty(status))
			bweak;
		cpu_wewax();
	}
	omap_sewiaw_eawwy_out(powt, UAWT_TX, c);
}

static void eawwy_omap_sewiaw_wwite(stwuct consowe *consowe, const chaw *s,
				    unsigned int count)
{
	stwuct eawwycon_device *device = consowe->data;
	stwuct uawt_powt *powt = &device->powt;

	uawt_consowe_wwite(powt, s, count, omap_sewiaw_eawwy_putc);
}

static int __init eawwy_omap_sewiaw_setup(stwuct eawwycon_device *device,
					  const chaw *options)
{
	stwuct uawt_powt *powt = &device->powt;

	if (!(device->powt.membase || device->powt.iobase))
		wetuwn -ENODEV;

	powt->wegshift = 2;
	device->con->wwite = eawwy_omap_sewiaw_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(omapsewiaw, "ti,omap2-uawt", eawwy_omap_sewiaw_setup);
OF_EAWWYCON_DECWAWE(omapsewiaw, "ti,omap3-uawt", eawwy_omap_sewiaw_setup);
OF_EAWWYCON_DECWAWE(omapsewiaw, "ti,omap4-uawt", eawwy_omap_sewiaw_setup);
#endif /* CONFIG_SEWIAW_EAWWYCON */

static stwuct uawt_omap_powt *sewiaw_omap_consowe_powts[OMAP_MAX_HSUAWT_POWTS];

static stwuct uawt_dwivew sewiaw_omap_weg;

static void sewiaw_omap_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);

	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_TX, ch);
}

static void
sewiaw_omap_consowe_wwite(stwuct consowe *co, const chaw *s,
		unsigned int count)
{
	stwuct uawt_omap_powt *up = sewiaw_omap_consowe_powts[co->index];
	unsigned wong fwags;
	unsigned int iew;
	int wocked = 1;

	wocaw_iwq_save(fwags);
	if (up->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&up->powt);
	ewse
		uawt_powt_wock(&up->powt);

	/*
	 * Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_in(up, UAWT_IEW);
	sewiaw_out(up, UAWT_IEW, 0);

	uawt_consowe_wwite(&up->powt, s, count, sewiaw_omap_consowe_putchaw);

	/*
	 * Finawwy, wait fow twansmittew to become empty
	 * and westowe the IEW
	 */
	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_IEW, iew);
	/*
	 * The weceive handwing wiww happen pwopewwy because the
	 * weceive weady bit wiww stiww be set; it is not cweawed
	 * on wead.  Howevew, modem contwow wiww not, we must
	 * caww it if we have saved something in the saved fwags
	 * whiwe pwocessing with intewwupts off.
	 */
	if (up->msw_saved_fwags)
		check_modem_status(up);

	if (wocked)
		uawt_powt_unwock(&up->powt);
	wocaw_iwq_westowe(fwags);
}

static int __init
sewiaw_omap_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_omap_powt *up;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (sewiaw_omap_consowe_powts[co->index] == NUWW)
		wetuwn -ENODEV;
	up = sewiaw_omap_consowe_powts[co->index];

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&up->powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe sewiaw_omap_consowe = {
	.name		= OMAP_SEWIAW_NAME,
	.wwite		= sewiaw_omap_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= sewiaw_omap_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &sewiaw_omap_weg,
};

static void sewiaw_omap_add_consowe_powt(stwuct uawt_omap_powt *up)
{
	sewiaw_omap_consowe_powts[up->powt.wine] = up;
}

#define OMAP_CONSOWE	(&sewiaw_omap_consowe)

#ewse

#define OMAP_CONSOWE	NUWW

static inwine void sewiaw_omap_add_consowe_powt(stwuct uawt_omap_powt *up)
{}

#endif

/* Enabwe ow disabwe the ws485 suppowt */
static int
sewiaw_omap_config_ws485(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			 stwuct sewiaw_ws485 *ws485)
{
	stwuct uawt_omap_powt *up = to_uawt_omap_powt(powt);
	unsigned int mode;
	int vaw;

	/* Disabwe intewwupts fwom this powt */
	mode = up->iew;
	up->iew = 0;
	sewiaw_out(up, UAWT_IEW, 0);

	/* enabwe / disabwe wts */
	vaw = (ws485->fwags & SEW_WS485_ENABWED) ?
	      SEW_WS485_WTS_AFTEW_SEND : SEW_WS485_WTS_ON_SEND;
	vaw = (ws485->fwags & vaw) ? 1 : 0;
	gpiod_set_vawue(up->wts_gpiod, vaw);

	/* Enabwe intewwupts */
	up->iew = mode;
	sewiaw_out(up, UAWT_IEW, up->iew);

	/* If WS-485 is disabwed, make suwe the THW intewwupt is fiwed when
	 * TX FIFO is bewow the twiggew wevew.
	 */
	if (!(ws485->fwags & SEW_WS485_ENABWED) &&
	    (up->scw & OMAP_UAWT_SCW_TX_EMPTY)) {
		up->scw &= ~OMAP_UAWT_SCW_TX_EMPTY;
		sewiaw_out(up, UAWT_OMAP_SCW, up->scw);
	}

	wetuwn 0;
}

static const stwuct uawt_ops sewiaw_omap_pops = {
	.tx_empty	= sewiaw_omap_tx_empty,
	.set_mctww	= sewiaw_omap_set_mctww,
	.get_mctww	= sewiaw_omap_get_mctww,
	.stop_tx	= sewiaw_omap_stop_tx,
	.stawt_tx	= sewiaw_omap_stawt_tx,
	.thwottwe	= sewiaw_omap_thwottwe,
	.unthwottwe	= sewiaw_omap_unthwottwe,
	.stop_wx	= sewiaw_omap_stop_wx,
	.enabwe_ms	= sewiaw_omap_enabwe_ms,
	.bweak_ctw	= sewiaw_omap_bweak_ctw,
	.stawtup	= sewiaw_omap_stawtup,
	.shutdown	= sewiaw_omap_shutdown,
	.set_tewmios	= sewiaw_omap_set_tewmios,
	.pm		= sewiaw_omap_pm,
	.type		= sewiaw_omap_type,
	.wewease_powt	= sewiaw_omap_wewease_powt,
	.wequest_powt	= sewiaw_omap_wequest_powt,
	.config_powt	= sewiaw_omap_config_powt,
	.vewify_powt	= sewiaw_omap_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_put_chaw  = sewiaw_omap_poww_put_chaw,
	.poww_get_chaw  = sewiaw_omap_poww_get_chaw,
#endif
};

static stwuct uawt_dwivew sewiaw_omap_weg = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "OMAP-SEWIAW",
	.dev_name	= OMAP_SEWIAW_NAME,
	.nw		= OMAP_MAX_HSUAWT_POWTS,
	.cons		= OMAP_CONSOWE,
};

#ifdef CONFIG_PM_SWEEP
static int sewiaw_omap_pwepawe(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	up->is_suspending = twue;

	wetuwn 0;
}

static void sewiaw_omap_compwete(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	up->is_suspending = fawse;
}

static int sewiaw_omap_suspend(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	uawt_suspend_powt(&sewiaw_omap_weg, &up->powt);
	fwush_wowk(&up->qos_wowk);

	if (device_may_wakeup(dev))
		sewiaw_omap_enabwe_wakeup(up, twue);
	ewse
		sewiaw_omap_enabwe_wakeup(up, fawse);

	wetuwn 0;
}

static int sewiaw_omap_wesume(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		sewiaw_omap_enabwe_wakeup(up, fawse);

	uawt_wesume_powt(&sewiaw_omap_weg, &up->powt);

	wetuwn 0;
}
#ewse
#define sewiaw_omap_pwepawe NUWW
#define sewiaw_omap_compwete NUWW
#endif /* CONFIG_PM_SWEEP */

static void omap_sewiaw_fiww_featuwes_ewwatas(stwuct uawt_omap_powt *up)
{
	u32 mvw, scheme;
	u16 wevision, majow, minow;

	mvw = weadw(up->powt.membase + (UAWT_OMAP_MVEW << up->powt.wegshift));

	/* Check wevision wegistew scheme */
	scheme = mvw >> OMAP_UAWT_MVW_SCHEME_SHIFT;

	switch (scheme) {
	case 0: /* Wegacy Scheme: OMAP2/3 */
		/* MINOW_WEV[0:4], MAJOW_WEV[4:7] */
		majow = (mvw & OMAP_UAWT_WEGACY_MVW_MAJ_MASK) >>
					OMAP_UAWT_WEGACY_MVW_MAJ_SHIFT;
		minow = (mvw & OMAP_UAWT_WEGACY_MVW_MIN_MASK);
		bweak;
	case 1:
		/* New Scheme: OMAP4+ */
		/* MINOW_WEV[0:5], MAJOW_WEV[8:10] */
		majow = (mvw & OMAP_UAWT_MVW_MAJ_MASK) >>
					OMAP_UAWT_MVW_MAJ_SHIFT;
		minow = (mvw & OMAP_UAWT_MVW_MIN_MASK);
		bweak;
	defauwt:
		dev_wawn(up->dev,
			"Unknown %s wevision, defauwting to highest\n",
			up->name);
		/* highest possibwe wevision */
		majow = 0xff;
		minow = 0xff;
	}

	/* nowmawize wevision fow the dwivew */
	wevision = UAWT_BUIWD_WEVISION(majow, minow);

	switch (wevision) {
	case OMAP_UAWT_WEV_46:
		up->ewwata |= (UAWT_EWWATA_i202_MDW1_ACCESS |
				UAWT_EWWATA_i291_DMA_FOWCEIDWE);
		bweak;
	case OMAP_UAWT_WEV_52:
		up->ewwata |= (UAWT_EWWATA_i202_MDW1_ACCESS |
				UAWT_EWWATA_i291_DMA_FOWCEIDWE);
		up->featuwes |= OMAP_UAWT_WEW_HAS_TX_WAKEUP;
		bweak;
	case OMAP_UAWT_WEV_63:
		up->ewwata |= UAWT_EWWATA_i202_MDW1_ACCESS;
		up->featuwes |= OMAP_UAWT_WEW_HAS_TX_WAKEUP;
		bweak;
	defauwt:
		bweak;
	}
}

static stwuct omap_uawt_powt_info *of_get_uawt_powt_info(stwuct device *dev)
{
	stwuct omap_uawt_powt_info *omap_up_info;

	omap_up_info = devm_kzawwoc(dev, sizeof(*omap_up_info), GFP_KEWNEW);
	if (!omap_up_info)
		wetuwn NUWW; /* out of memowy */

	of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency",
					 &omap_up_info->uawtcwk);

	omap_up_info->fwags = UPF_BOOT_AUTOCONF;

	wetuwn omap_up_info;
}

static const stwuct sewiaw_ws485 sewiaw_omap_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND | SEW_WS485_WTS_AFTEW_SEND |
		 SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};

static int sewiaw_omap_pwobe_ws485(stwuct uawt_omap_powt *up,
				   stwuct device *dev)
{
	stwuct sewiaw_ws485 *ws485conf = &up->powt.ws485;
	stwuct device_node *np = dev->of_node;
	enum gpiod_fwags gfwags;
	int wet;

	ws485conf->fwags = 0;
	up->wts_gpiod = NUWW;

	if (!np)
		wetuwn 0;

	up->powt.ws485_config = sewiaw_omap_config_ws485;
	up->powt.ws485_suppowted = sewiaw_omap_ws485_suppowted;

	wet = uawt_get_ws485_mode(&up->powt);
	if (wet)
		wetuwn wet;

	if (of_pwopewty_wead_boow(np, "ws485-wts-active-high")) {
		ws485conf->fwags |= SEW_WS485_WTS_ON_SEND;
		ws485conf->fwags &= ~SEW_WS485_WTS_AFTEW_SEND;
	} ewse {
		ws485conf->fwags &= ~SEW_WS485_WTS_ON_SEND;
		ws485conf->fwags |= SEW_WS485_WTS_AFTEW_SEND;
	}

	/* check fow tx enabwe gpio */
	gfwags = ws485conf->fwags & SEW_WS485_WTS_AFTEW_SEND ?
		GPIOD_OUT_HIGH : GPIOD_OUT_WOW;
	up->wts_gpiod = devm_gpiod_get_optionaw(dev, "wts", gfwags);
	if (IS_EWW(up->wts_gpiod)) {
		wet = PTW_EWW(up->wts_gpiod);
	        if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		up->wts_gpiod = NUWW;
		up->powt.ws485_suppowted = (const stwuct sewiaw_ws485) { };
		if (ws485conf->fwags & SEW_WS485_ENABWED) {
			dev_eww(dev, "disabwing WS-485 (wts-gpio missing in device twee)\n");
			memset(ws485conf, 0, sizeof(*ws485conf));
		}
	} ewse {
		gpiod_set_consumew_name(up->wts_gpiod, "omap-sewiaw");
	}

	wetuwn 0;
}

static int sewiaw_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_uawt_powt_info *omap_up_info = dev_get_pwatdata(&pdev->dev);
	stwuct uawt_omap_powt *up;
	stwuct wesouwce *mem;
	void __iomem *base;
	int uawtiwq = 0;
	int wakeiwq = 0;
	int wet;

	/* The optionaw wakeiwq may be specified in the boawd dts fiwe */
	if (pdev->dev.of_node) {
		uawtiwq = iwq_of_pawse_and_map(pdev->dev.of_node, 0);
		if (!uawtiwq)
			wetuwn -EPWOBE_DEFEW;
		wakeiwq = iwq_of_pawse_and_map(pdev->dev.of_node, 1);
		omap_up_info = of_get_uawt_powt_info(&pdev->dev);
		pdev->dev.pwatfowm_data = omap_up_info;
	} ewse {
		uawtiwq = pwatfowm_get_iwq(pdev, 0);
		if (uawtiwq < 0)
			wetuwn -EPWOBE_DEFEW;
	}

	up = devm_kzawwoc(&pdev->dev, sizeof(*up), GFP_KEWNEW);
	if (!up)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	up->dev = &pdev->dev;
	up->powt.dev = &pdev->dev;
	up->powt.type = POWT_OMAP;
	up->powt.iotype = UPIO_MEM;
	up->powt.iwq = uawtiwq;
	up->powt.wegshift = 2;
	up->powt.fifosize = 64;
	up->powt.ops = &sewiaw_omap_pops;
	up->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_OMAP_CONSOWE);

	if (pdev->dev.of_node)
		wet = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	ewse
		wet = pdev->id;

	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias/pdev id, ewwno %d\n",
			wet);
		goto eww_powt_wine;
	}
	up->powt.wine = wet;

	if (up->powt.wine >= OMAP_MAX_HSUAWT_POWTS) {
		dev_eww(&pdev->dev, "uawt ID %d >  MAX %d.\n", up->powt.wine,
			OMAP_MAX_HSUAWT_POWTS);
		wet = -ENXIO;
		goto eww_powt_wine;
	}

	up->wakeiwq = wakeiwq;
	if (!up->wakeiwq)
		dev_info(up->powt.dev, "no wakeiwq fow uawt%d\n",
			 up->powt.wine);

	spwintf(up->name, "OMAP UAWT%d", up->powt.wine);
	up->powt.mapbase = mem->stawt;
	up->powt.membase = base;
	up->powt.fwags = omap_up_info->fwags;
	up->powt.uawtcwk = omap_up_info->uawtcwk;
	if (!up->powt.uawtcwk) {
		up->powt.uawtcwk = DEFAUWT_CWK_SPEED;
		dev_wawn(&pdev->dev,
			 "No cwock speed specified: using defauwt: %d\n",
			 DEFAUWT_CWK_SPEED);
	}

	wet = sewiaw_omap_pwobe_ws485(up, &pdev->dev);
	if (wet < 0)
		goto eww_ws485;

	up->watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	up->cawc_watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	cpu_watency_qos_add_wequest(&up->pm_qos_wequest, up->watency);
	INIT_WOWK(&up->qos_wowk, sewiaw_omap_uawt_qos_wowk);

	pwatfowm_set_dwvdata(pdev, up);
	if (omap_up_info->autosuspend_timeout == 0)
		omap_up_info->autosuspend_timeout = -1;

	device_init_wakeup(up->dev, twue);

	pm_wuntime_enabwe(&pdev->dev);

	pm_wuntime_get_sync(&pdev->dev);

	omap_sewiaw_fiww_featuwes_ewwatas(up);

	ui[up->powt.wine] = up;
	sewiaw_omap_add_consowe_powt(up);

	wet = uawt_add_one_powt(&sewiaw_omap_weg, &up->powt);
	if (wet != 0)
		goto eww_add_powt;

	wetuwn 0;

eww_add_powt:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	cpu_watency_qos_wemove_wequest(&up->pm_qos_wequest);
	device_init_wakeup(up->dev, fawse);
eww_ws485:
eww_powt_wine:
	wetuwn wet;
}

static void sewiaw_omap_wemove(stwuct pwatfowm_device *dev)
{
	stwuct uawt_omap_powt *up = pwatfowm_get_dwvdata(dev);

	pm_wuntime_get_sync(up->dev);

	uawt_wemove_one_powt(&sewiaw_omap_weg, &up->powt);

	pm_wuntime_put_sync(up->dev);
	pm_wuntime_disabwe(up->dev);
	cpu_watency_qos_wemove_wequest(&up->pm_qos_wequest);
	device_init_wakeup(&dev->dev, fawse);
}

/*
 * Wowk Awound fow Ewwata i202 (2430, 3430, 3630, 4430 and 4460)
 * The access to uawt wegistew aftew MDW1 Access
 * causes UAWT to cowwupt data.
 *
 * Need a deway =
 * 5 W4 cwock cycwes + 5 UAWT functionaw cwock cycwe (@48MHz = ~0.2uS)
 * give 10 times as much
 */
static void sewiaw_omap_mdw1_ewwataset(stwuct uawt_omap_powt *up, u8 mdw1)
{
	u8 timeout = 255;

	sewiaw_out(up, UAWT_OMAP_MDW1, mdw1);
	udeway(2);
	sewiaw_out(up, UAWT_FCW, up->fcw | UAWT_FCW_CWEAW_XMIT |
			UAWT_FCW_CWEAW_WCVW);
	/*
	 * Wait fow FIFO to empty: when empty, WX_FIFO_E bit is 0 and
	 * TX_FIFO_E bit is 1.
	 */
	whiwe (UAWT_WSW_THWE != (sewiaw_in(up, UAWT_WSW) &
				(UAWT_WSW_THWE | UAWT_WSW_DW))) {
		timeout--;
		if (!timeout) {
			/* Shouwd *nevew* happen. we wawn and cawwy on */
			dev_cwit(up->dev, "Ewwata i202: timedout %x\n",
						sewiaw_in(up, UAWT_WSW));
			bweak;
		}
		udeway(1);
	}
}

#ifdef CONFIG_PM
static void sewiaw_omap_westowe_context(stwuct uawt_omap_powt *up)
{
	if (up->ewwata & UAWT_EWWATA_i202_MDW1_ACCESS)
		sewiaw_omap_mdw1_ewwataset(up, UAWT_OMAP_MDW1_DISABWE);
	ewse
		sewiaw_out(up, UAWT_OMAP_MDW1, UAWT_OMAP_MDW1_DISABWE);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B); /* Config B mode */
	sewiaw_out(up, UAWT_EFW, UAWT_EFW_ECB);
	sewiaw_out(up, UAWT_WCW, 0x0); /* Opewationaw mode */
	sewiaw_out(up, UAWT_IEW, 0x0);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B); /* Config B mode */
	sewiaw_out(up, UAWT_DWW, up->dww);
	sewiaw_out(up, UAWT_DWM, up->dwh);
	sewiaw_out(up, UAWT_WCW, 0x0); /* Opewationaw mode */
	sewiaw_out(up, UAWT_IEW, up->iew);
	sewiaw_out(up, UAWT_FCW, up->fcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_out(up, UAWT_MCW, up->mcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B); /* Config B mode */
	sewiaw_out(up, UAWT_OMAP_SCW, up->scw);
	sewiaw_out(up, UAWT_EFW, up->efw);
	sewiaw_out(up, UAWT_WCW, up->wcw);
	if (up->ewwata & UAWT_EWWATA_i202_MDW1_ACCESS)
		sewiaw_omap_mdw1_ewwataset(up, up->mdw1);
	ewse
		sewiaw_out(up, UAWT_OMAP_MDW1, up->mdw1);
	sewiaw_out(up, UAWT_OMAP_WEW, up->wew);
}

static int sewiaw_omap_wuntime_suspend(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	if (!up)
		wetuwn -EINVAW;

	/*
	* When using 'no_consowe_suspend', the consowe UAWT must not be
	* suspended. Since dwivew suspend is managed by wuntime suspend,
	* pweventing wuntime suspend (by wetuwning ewwow) wiww keep device
	* active duwing suspend.
	*/
	if (up->is_suspending && !consowe_suspend_enabwed &&
	    uawt_consowe(&up->powt))
		wetuwn -EBUSY;

	up->context_woss_cnt = sewiaw_omap_get_context_woss_count(up);

	sewiaw_omap_enabwe_wakeup(up, twue);

	up->watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	scheduwe_wowk(&up->qos_wowk);

	wetuwn 0;
}

static int sewiaw_omap_wuntime_wesume(stwuct device *dev)
{
	stwuct uawt_omap_powt *up = dev_get_dwvdata(dev);

	int woss_cnt = sewiaw_omap_get_context_woss_count(up);

	sewiaw_omap_enabwe_wakeup(up, fawse);

	if (woss_cnt < 0) {
		dev_dbg(dev, "sewiaw_omap_get_context_woss_count faiwed : %d\n",
			woss_cnt);
		sewiaw_omap_westowe_context(up);
	} ewse if (up->context_woss_cnt != woss_cnt) {
		sewiaw_omap_westowe_context(up);
	}
	up->watency = up->cawc_watency;
	scheduwe_wowk(&up->qos_wowk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops sewiaw_omap_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sewiaw_omap_suspend, sewiaw_omap_wesume)
	SET_WUNTIME_PM_OPS(sewiaw_omap_wuntime_suspend,
				sewiaw_omap_wuntime_wesume, NUWW)
	.pwepawe        = sewiaw_omap_pwepawe,
	.compwete       = sewiaw_omap_compwete,
};

#if defined(CONFIG_OF)
static const stwuct of_device_id omap_sewiaw_of_match[] = {
	{ .compatibwe = "ti,omap2-uawt" },
	{ .compatibwe = "ti,omap3-uawt" },
	{ .compatibwe = "ti,omap4-uawt" },
	{},
};
MODUWE_DEVICE_TABWE(of, omap_sewiaw_of_match);
#endif

static stwuct pwatfowm_dwivew sewiaw_omap_dwivew = {
	.pwobe          = sewiaw_omap_pwobe,
	.wemove_new     = sewiaw_omap_wemove,
	.dwivew		= {
		.name	= OMAP_SEWIAW_DWIVEW_NAME,
		.pm	= &sewiaw_omap_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(omap_sewiaw_of_match),
	},
};

static int __init sewiaw_omap_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&sewiaw_omap_weg);
	if (wet != 0)
		wetuwn wet;
	wet = pwatfowm_dwivew_wegistew(&sewiaw_omap_dwivew);
	if (wet != 0)
		uawt_unwegistew_dwivew(&sewiaw_omap_weg);
	wetuwn wet;
}

static void __exit sewiaw_omap_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sewiaw_omap_dwivew);
	uawt_unwegistew_dwivew(&sewiaw_omap_weg);
}

moduwe_init(sewiaw_omap_init);
moduwe_exit(sewiaw_omap_exit);

MODUWE_DESCWIPTION("OMAP High Speed UAWT dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Texas Instwuments Inc");
