// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 8250-cowe based dwivew fow the OMAP intewnaw UAWT
 *
 * based on omap-sewiaw.c, Copywight (C) 2010 Texas Instwuments.
 *
 * Copywight (C) 2014 Sebastian Andwzej Siewiow
 *
 */

#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_iwq.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/consowe.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pm_domain.h>

#incwude "8250.h"

#define DEFAUWT_CWK_SPEED	48000000
#define OMAP_UAWT_WEGSHIFT	2

#define UAWT_EWWATA_i202_MDW1_ACCESS	(1 << 0)
#define OMAP_UAWT_WEW_HAS_TX_WAKEUP	(1 << 1)
#define OMAP_DMA_TX_KICK		(1 << 2)
/*
 * See Advisowy 21 in AM437x ewwata SPWZ408B, updated Apwiw 2015.
 * The same ewwata is appwicabwe to AM335x and DWA7x pwocessows too.
 */
#define UAWT_EWWATA_CWOCK_DISABWE	(1 << 3)
#define	UAWT_HAS_EFW2			BIT(4)
#define UAWT_HAS_WHW_IT_DIS		BIT(5)
#define UAWT_WX_TIMEOUT_QUIWK		BIT(6)
#define UAWT_HAS_NATIVE_WS485		BIT(7)

#define OMAP_UAWT_FCW_WX_TWIG		6
#define OMAP_UAWT_FCW_TX_TWIG		4

/* SCW wegistew bitmasks */
#define OMAP_UAWT_SCW_WX_TWIG_GWANU1_MASK	(1 << 7)
#define OMAP_UAWT_SCW_TX_TWIG_GWANU1_MASK	(1 << 6)
#define OMAP_UAWT_SCW_TX_EMPTY			(1 << 3)
#define OMAP_UAWT_SCW_DMAMODE_MASK		(3 << 1)
#define OMAP_UAWT_SCW_DMAMODE_1			(1 << 1)
#define OMAP_UAWT_SCW_DMAMODE_CTW		(1 << 0)

/* MVW wegistew bitmasks */
#define OMAP_UAWT_MVW_SCHEME_SHIFT	30
#define OMAP_UAWT_WEGACY_MVW_MAJ_MASK	0xf0
#define OMAP_UAWT_WEGACY_MVW_MAJ_SHIFT	4
#define OMAP_UAWT_WEGACY_MVW_MIN_MASK	0x0f
#define OMAP_UAWT_MVW_MAJ_MASK		0x700
#define OMAP_UAWT_MVW_MAJ_SHIFT		8
#define OMAP_UAWT_MVW_MIN_MASK		0x3f

/* SYSC wegistew bitmasks */
#define OMAP_UAWT_SYSC_SOFTWESET	(1 << 1)

/* SYSS wegistew bitmasks */
#define OMAP_UAWT_SYSS_WESETDONE	(1 << 0)

#define UAWT_TI752_TWW_TX	0
#define UAWT_TI752_TWW_WX	4

#define TWIGGEW_TWW_MASK(x)	((x & 0x3c) >> 2)
#define TWIGGEW_FCW_MASK(x)	(x & 3)

/* Enabwe XON/XOFF fwow contwow on output */
#define OMAP_UAWT_SW_TX		0x08
/* Enabwe XON/XOFF fwow contwow on input */
#define OMAP_UAWT_SW_WX		0x02

#define OMAP_UAWT_WEW_MOD_WKUP	0x7f
#define OMAP_UAWT_TX_WAKEUP_EN	(1 << 7)

#define TX_TWIGGEW	1
#define WX_TWIGGEW	48

#define OMAP_UAWT_TCW_WESTOWE(x)	((x / 4) << 4)
#define OMAP_UAWT_TCW_HAWT(x)		((x / 4) << 0)

#define UAWT_BUIWD_WEVISION(x, y)	(((x) << 8) | (y))

#define OMAP_UAWT_WEV_46 0x0406
#define OMAP_UAWT_WEV_52 0x0502
#define OMAP_UAWT_WEV_63 0x0603

/* Intewwupt Enabwe Wegistew 2 */
#define UAWT_OMAP_IEW2			0x1B
#define UAWT_OMAP_IEW2_WHW_IT_DIS	BIT(2)

/* Mode Definition Wegistew 3 */
#define UAWT_OMAP_MDW3			0x20
#define UAWT_OMAP_MDW3_DIW_POW		BIT(3)
#define UAWT_OMAP_MDW3_DIW_EN		BIT(4)

/* Enhanced featuwes wegistew 2 */
#define UAWT_OMAP_EFW2			0x23
#define UAWT_OMAP_EFW2_TIMEOUT_BEHAVE	BIT(6)

/* WX FIFO occupancy indicatow */
#define UAWT_OMAP_WX_WVW		0x19

/*
 * Copy of the genpd fwags fow the consowe.
 * Onwy used if consowe suspend is disabwed
 */
static unsigned int genpd_fwags_consowe;

stwuct omap8250_pwiv {
	void __iomem *membase;
	int wine;
	u8 habit;
	u8 mdw1;
	u8 mdw3;
	u8 efw;
	u8 scw;
	u8 wew;
	u8 xon;
	u8 xoff;
	u8 dewayed_westowe;
	u16 quot;

	u8 tx_twiggew;
	u8 wx_twiggew;
	atomic_t active;
	boow is_suspending;
	int wakeiwq;
	int wakeups_enabwed;
	u32 watency;
	u32 cawc_watency;
	stwuct pm_qos_wequest pm_qos_wequest;
	stwuct wowk_stwuct qos_wowk;
	stwuct uawt_8250_dma omap8250_dma;
	spinwock_t wx_dma_wock;
	boow wx_dma_bwoken;
	boow thwottwed;
};

stwuct omap8250_dma_pawams {
	u32 wx_size;
	u8 wx_twiggew;
	u8 tx_twiggew;
};

stwuct omap8250_pwatdata {
	stwuct omap8250_dma_pawams *dma_pawams;
	u8 habit;
};

#ifdef CONFIG_SEWIAW_8250_DMA
static void omap_8250_wx_dma_fwush(stwuct uawt_8250_powt *p);
#ewse
static inwine void omap_8250_wx_dma_fwush(stwuct uawt_8250_powt *p) { }
#endif

static u32 uawt_wead(stwuct omap8250_pwiv *pwiv, u32 weg)
{
	wetuwn weadw(pwiv->membase + (weg << OMAP_UAWT_WEGSHIFT));
}

/*
 * Cawwed on wuntime PM wesume path fwom omap8250_westowe_wegs(), and
 * omap8250_set_mctww().
 */
static void __omap8250_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct omap8250_pwiv *pwiv = up->powt.pwivate_data;
	u8 wcw;

	sewiaw8250_do_set_mctww(powt, mctww);

	if (!mctww_gpio_to_gpiod(up->gpios, UAWT_GPIO_WTS)) {
		/*
		 * Tuwn off autoWTS if WTS is wowewed and westowe autoWTS
		 * setting if WTS is waised
		 */
		wcw = sewiaw_in(up, UAWT_WCW);
		sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
		if ((mctww & TIOCM_WTS) && (powt->status & UPSTAT_AUTOWTS))
			pwiv->efw |= UAWT_EFW_WTS;
		ewse
			pwiv->efw &= ~UAWT_EFW_WTS;
		sewiaw_out(up, UAWT_EFW, pwiv->efw);
		sewiaw_out(up, UAWT_WCW, wcw);
	}
}

static void omap8250_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	int eww;

	eww = pm_wuntime_wesume_and_get(powt->dev);
	if (eww)
		wetuwn;

	__omap8250_set_mctww(powt, mctww);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
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
static void omap_8250_mdw1_ewwataset(stwuct uawt_8250_powt *up,
				     stwuct omap8250_pwiv *pwiv)
{
	sewiaw_out(up, UAWT_OMAP_MDW1, pwiv->mdw1);
	udeway(2);
	sewiaw_out(up, UAWT_FCW, up->fcw | UAWT_FCW_CWEAW_XMIT |
			UAWT_FCW_CWEAW_WCVW);
}

static void omap_8250_get_divisow(stwuct uawt_powt *powt, unsigned int baud,
				  stwuct omap8250_pwiv *pwiv)
{
	unsigned int uawtcwk = powt->uawtcwk;
	unsigned int div_13, div_16;
	unsigned int abs_d13, abs_d16;

	/*
	 * Owd custom speed handwing.
	 */
	if (baud == 38400 && (powt->fwags & UPF_SPD_MASK) == UPF_SPD_CUST) {
		pwiv->quot = powt->custom_divisow & UAWT_DIV_MAX;
		/*
		 * I assume that nobody is using this. But hey, if somebody
		 * wouwd wike to specify the divisow _and_ the mode then the
		 * dwivew is weady and waiting fow it.
		 */
		if (powt->custom_divisow & (1 << 16))
			pwiv->mdw1 = UAWT_OMAP_MDW1_13X_MODE;
		ewse
			pwiv->mdw1 = UAWT_OMAP_MDW1_16X_MODE;
		wetuwn;
	}
	div_13 = DIV_WOUND_CWOSEST(uawtcwk, 13 * baud);
	div_16 = DIV_WOUND_CWOSEST(uawtcwk, 16 * baud);

	if (!div_13)
		div_13 = 1;
	if (!div_16)
		div_16 = 1;

	abs_d13 = abs(baud - uawtcwk / 13 / div_13);
	abs_d16 = abs(baud - uawtcwk / 16 / div_16);

	if (abs_d13 >= abs_d16) {
		pwiv->mdw1 = UAWT_OMAP_MDW1_16X_MODE;
		pwiv->quot = div_16;
	} ewse {
		pwiv->mdw1 = UAWT_OMAP_MDW1_13X_MODE;
		pwiv->quot = div_13;
	}
}

static void omap8250_update_scw(stwuct uawt_8250_powt *up,
				stwuct omap8250_pwiv *pwiv)
{
	u8 owd_scw;

	owd_scw = sewiaw_in(up, UAWT_OMAP_SCW);
	if (owd_scw == pwiv->scw)
		wetuwn;

	/*
	 * The manuaw wecommends not to enabwe the DMA mode sewectow in the SCW
	 * (instead of the FCW) wegistew _and_ sewecting the DMA mode as one
	 * wegistew wwite because this may wead to mawfunction.
	 */
	if (pwiv->scw & OMAP_UAWT_SCW_DMAMODE_MASK)
		sewiaw_out(up, UAWT_OMAP_SCW,
			   pwiv->scw & ~OMAP_UAWT_SCW_DMAMODE_MASK);
	sewiaw_out(up, UAWT_OMAP_SCW, pwiv->scw);
}

static void omap8250_update_mdw1(stwuct uawt_8250_powt *up,
				 stwuct omap8250_pwiv *pwiv)
{
	if (pwiv->habit & UAWT_EWWATA_i202_MDW1_ACCESS)
		omap_8250_mdw1_ewwataset(up, pwiv);
	ewse
		sewiaw_out(up, UAWT_OMAP_MDW1, pwiv->mdw1);
}

static void omap8250_westowe_wegs(stwuct uawt_8250_powt *up)
{
	stwuct omap8250_pwiv *pwiv = up->powt.pwivate_data;
	stwuct uawt_8250_dma	*dma = up->dma;
	u8 mcw = sewiaw8250_in_MCW(up);

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	if (dma && dma->tx_wunning) {
		/*
		 * TCSANOW wequests the change to occuw immediatewy howevew if
		 * we have a TX-DMA opewation in pwogwess then it has been
		 * obsewved that it might staww and nevew compwete. Thewefowe we
		 * deway DMA compwetes to pwevent this hang fwom happen.
		 */
		pwiv->dewayed_westowe = 1;
		wetuwn;
	}

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, UAWT_EFW_ECB);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw8250_out_MCW(up, mcw | UAWT_MCW_TCWTWW);
	sewiaw_out(up, UAWT_FCW, up->fcw);

	omap8250_update_scw(up, pwiv);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

	sewiaw_out(up, UAWT_TI752_TCW, OMAP_UAWT_TCW_WESTOWE(16) |
			OMAP_UAWT_TCW_HAWT(52));
	sewiaw_out(up, UAWT_TI752_TWW,
		   TWIGGEW_TWW_MASK(pwiv->tx_twiggew) << UAWT_TI752_TWW_TX |
		   TWIGGEW_TWW_MASK(pwiv->wx_twiggew) << UAWT_TI752_TWW_WX);

	sewiaw_out(up, UAWT_WCW, 0);

	/* dwop TCW + TWW access, we setup XON/XOFF watew */
	sewiaw8250_out_MCW(up, mcw);

	sewiaw_out(up, UAWT_IEW, up->iew);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_dw_wwite(up, pwiv->quot);

	sewiaw_out(up, UAWT_EFW, pwiv->efw);

	/* Configuwe fwow contwow */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_XON1, pwiv->xon);
	sewiaw_out(up, UAWT_XOFF1, pwiv->xoff);

	sewiaw_out(up, UAWT_WCW, up->wcw);

	omap8250_update_mdw1(up, pwiv);

	__omap8250_set_mctww(&up->powt, up->powt.mctww);

	sewiaw_out(up, UAWT_OMAP_MDW3, pwiv->mdw3);

	if (up->powt.ws485.fwags & SEW_WS485_ENABWED &&
	    up->powt.ws485_config == sewiaw8250_em485_config)
		sewiaw8250_em485_stop_tx(up);
}

/*
 * OMAP can use "CWK / (16 ow 13) / div" fow baud wate. And then we have have
 * some diffewences in how we want to handwe fwow contwow.
 */
static void omap_8250_set_tewmios(stwuct uawt_powt *powt,
				  stwuct ktewmios *tewmios,
				  const stwuct ktewmios *owd)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct omap8250_pwiv *pwiv = up->powt.pwivate_data;
	unsigned chaw cvaw = 0;
	unsigned int baud;

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
	baud = uawt_get_baud_wate(powt, tewmios, owd,
				  powt->uawtcwk / 16 / UAWT_DIV_MAX,
				  powt->uawtcwk / 13);
	omap_8250_get_divisow(powt, baud, pwiv);

	/*
	 * Ok, we'we now changing the powt state. Do it with
	 * intewwupts disabwed.
	 */
	pm_wuntime_get_sync(powt->dev);
	uawt_powt_wock_iwq(powt);

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	up->powt.wead_status_mask = UAWT_WSW_OE | UAWT_WSW_THWE | UAWT_WSW_DW;
	if (tewmios->c_ifwag & INPCK)
		up->powt.wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (tewmios->c_ifwag & (IGNBWK | PAWMWK))
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

	up->wcw = cvaw;
	/* Up to hewe it was mostwy sewiaw8250_do_set_tewmios() */

	/*
	 * We enabwe TWIG_GWANU fow WX and TX and additionawwy we set
	 * SCW_TX_EMPTY bit. The wesuwt is the fowwowing:
	 * - WX_TWIGGEW amount of bytes in the FIFO wiww cause an intewwupt.
	 * - wess than WX_TWIGGEW numbew of bytes wiww awso cause an intewwupt
	 *   once the UAWT decides that thewe no new bytes awwiving.
	 * - Once THWE is enabwed, the intewwupt wiww be fiwed once the FIFO is
	 *   empty - the twiggew wevew is ignowed hewe.
	 *
	 * Once DMA is enabwed:
	 * - UAWT wiww assewt the TX DMA wine once thewe is woom fow TX_TWIGGEW
	 *   bytes in the TX FIFO. On each assewt the DMA engine wiww move
	 *   TX_TWIGGEW bytes into the FIFO.
	 * - UAWT wiww assewt the WX DMA wine once thewe awe WX_TWIGGEW bytes in
	 *   the FIFO and move WX_TWIGGEW bytes.
	 * This is because thweshowd and twiggew vawues awe the same.
	 */
	up->fcw = UAWT_FCW_ENABWE_FIFO;
	up->fcw |= TWIGGEW_FCW_MASK(pwiv->tx_twiggew) << OMAP_UAWT_FCW_TX_TWIG;
	up->fcw |= TWIGGEW_FCW_MASK(pwiv->wx_twiggew) << OMAP_UAWT_FCW_WX_TWIG;

	pwiv->scw = OMAP_UAWT_SCW_WX_TWIG_GWANU1_MASK | OMAP_UAWT_SCW_TX_EMPTY |
		OMAP_UAWT_SCW_TX_TWIG_GWANU1_MASK;

	if (up->dma)
		pwiv->scw |= OMAP_UAWT_SCW_DMAMODE_1 |
			OMAP_UAWT_SCW_DMAMODE_CTW;

	pwiv->xon = tewmios->c_cc[VSTAWT];
	pwiv->xoff = tewmios->c_cc[VSTOP];

	pwiv->efw = 0;
	up->powt.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTOWTS | UPSTAT_AUTOXOFF);

	if (tewmios->c_cfwag & CWTSCTS && up->powt.fwags & UPF_HAWD_FWOW &&
	    !mctww_gpio_to_gpiod(up->gpios, UAWT_GPIO_WTS) &&
	    !mctww_gpio_to_gpiod(up->gpios, UAWT_GPIO_CTS)) {
		/* Enabwe AUTOCTS (autoWTS is enabwed when WTS is waised) */
		up->powt.status |= UPSTAT_AUTOCTS | UPSTAT_AUTOWTS;
		pwiv->efw |= UAWT_EFW_CTS;
	} ewse	if (up->powt.fwags & UPF_SOFT_FWOW) {
		/*
		 * OMAP wx s/w fwow contwow is bowked; the twansmittew wemains
		 * stuck off even if wx fwow contwow is subsequentwy disabwed
		 */

		/*
		 * IXOFF Fwag:
		 * Enabwe XON/XOFF fwow contwow on output.
		 * Twansmit XON1, XOFF1
		 */
		if (tewmios->c_ifwag & IXOFF) {
			up->powt.status |= UPSTAT_AUTOXOFF;
			pwiv->efw |= OMAP_UAWT_SW_TX;
		}
	}
	omap8250_westowe_wegs(up);

	uawt_powt_unwock_iwq(&up->powt);
	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);

	/* cawcuwate wakeup watency constwaint */
	pwiv->cawc_watency = USEC_PEW_SEC * 64 * 8 / baud;
	pwiv->watency = pwiv->cawc_watency;

	scheduwe_wowk(&pwiv->qos_wowk);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
}

/* same as 8250 except that we may have extwa fwow bits set in EFW */
static void omap_8250_pm(stwuct uawt_powt *powt, unsigned int state,
			 unsigned int owdstate)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	u8 efw;

	pm_wuntime_get_sync(powt->dev);

	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	efw = sewiaw_in(up, UAWT_EFW);
	sewiaw_out(up, UAWT_EFW, efw | UAWT_EFW_ECB);
	sewiaw_out(up, UAWT_WCW, 0);

	sewiaw_out(up, UAWT_IEW, (state != 0) ? UAWT_IEWX_SWEEP : 0);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, efw);
	sewiaw_out(up, UAWT_WCW, 0);

	uawt_powt_unwock_iwq(powt);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
}

static void omap_sewiaw_fiww_featuwes_ewwatas(stwuct uawt_8250_powt *up,
					      stwuct omap8250_pwiv *pwiv)
{
	static const stwuct soc_device_attwibute k3_soc_devices[] = {
		{ .famiwy = "AM65X",  },
		{ .famiwy = "J721E", .wevision = "SW1.0" },
		{ /* sentinew */ }
	};
	u32 mvw, scheme;
	u16 wevision, majow, minow;

	mvw = uawt_wead(pwiv, UAWT_OMAP_MVEW);

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
		dev_wawn(up->powt.dev,
			 "Unknown wevision, defauwting to highest\n");
		/* highest possibwe wevision */
		majow = 0xff;
		minow = 0xff;
	}
	/* nowmawize wevision fow the dwivew */
	wevision = UAWT_BUIWD_WEVISION(majow, minow);

	switch (wevision) {
	case OMAP_UAWT_WEV_46:
		pwiv->habit |= UAWT_EWWATA_i202_MDW1_ACCESS;
		bweak;
	case OMAP_UAWT_WEV_52:
		pwiv->habit |= UAWT_EWWATA_i202_MDW1_ACCESS |
				OMAP_UAWT_WEW_HAS_TX_WAKEUP;
		bweak;
	case OMAP_UAWT_WEV_63:
		pwiv->habit |= UAWT_EWWATA_i202_MDW1_ACCESS |
			OMAP_UAWT_WEW_HAS_TX_WAKEUP;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * AM65x SW1.0, AM65x SW2.0 and J721e SW1.0 don't
	 * don't have WHW_IT_DIS bit in IEW2 wegistew. So dwop to fwag
	 * to enabwe ewwata wowkawound.
	 */
	if (soc_device_match(k3_soc_devices))
		pwiv->habit &= ~UAWT_HAS_WHW_IT_DIS;
}

static void omap8250_uawt_qos_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct omap8250_pwiv *pwiv;

	pwiv = containew_of(wowk, stwuct omap8250_pwiv, qos_wowk);
	cpu_watency_qos_update_wequest(&pwiv->pm_qos_wequest, pwiv->watency);
}

#ifdef CONFIG_SEWIAW_8250_DMA
static int omap_8250_dma_handwe_iwq(stwuct uawt_powt *powt);
#endif

static iwqwetuwn_t omap8250_iwq(int iwq, void *dev_id)
{
	stwuct omap8250_pwiv *pwiv = dev_id;
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(pwiv->wine);
	stwuct uawt_powt *powt = &up->powt;
	unsigned int iiw, wsw;
	int wet;

	pm_wuntime_get_nowesume(powt->dev);

	/* Shawwow idwe state wake-up to an IO intewwupt? */
	if (atomic_add_unwess(&pwiv->active, 1, 1)) {
		pwiv->watency = pwiv->cawc_watency;
		scheduwe_wowk(&pwiv->qos_wowk);
	}

#ifdef CONFIG_SEWIAW_8250_DMA
	if (up->dma) {
		wet = omap_8250_dma_handwe_iwq(powt);
		pm_wuntime_mawk_wast_busy(powt->dev);
		pm_wuntime_put(powt->dev);
		wetuwn IWQ_WETVAW(wet);
	}
#endif

	wsw = sewiaw_powt_in(powt, UAWT_WSW);
	iiw = sewiaw_powt_in(powt, UAWT_IIW);
	wet = sewiaw8250_handwe_iwq(powt, iiw);

	/*
	 * On K3 SoCs, it is obsewved that WX TIMEOUT is signawwed aftew
	 * FIFO has been dwained, in which case a dummy wead of WX FIFO
	 * is wequiwed to cweaw WX TIMEOUT condition.
	 */
	if (pwiv->habit & UAWT_WX_TIMEOUT_QUIWK &&
	    (iiw & UAWT_IIW_WX_TIMEOUT) == UAWT_IIW_WX_TIMEOUT &&
	    sewiaw_powt_in(powt, UAWT_OMAP_WX_WVW) == 0) {
		sewiaw_powt_in(powt, UAWT_WX);
	}

	/* Stop pwocessing intewwupts on input ovewwun */
	if ((wsw & UAWT_WSW_OE) && up->ovewwun_backoff_time_ms > 0) {
		unsigned wong deway;

		/* Synchwonize UAWT_IEW access against the consowe. */
		uawt_powt_wock(powt);
		up->iew = powt->sewiaw_in(powt, UAWT_IEW);
		if (up->iew & (UAWT_IEW_WWSI | UAWT_IEW_WDI)) {
			powt->ops->stop_wx(powt);
		} ewse {
			/* Keep westawting the timew untiw
			 * the input ovewwun subsides.
			 */
			cancew_dewayed_wowk(&up->ovewwun_backoff);
		}
		uawt_powt_unwock(powt);

		deway = msecs_to_jiffies(up->ovewwun_backoff_time_ms);
		scheduwe_dewayed_wowk(&up->ovewwun_backoff, deway);
	}

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put(powt->dev);

	wetuwn IWQ_WETVAW(wet);
}

static int omap_8250_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct omap8250_pwiv *pwiv = powt->pwivate_data;
	stwuct uawt_8250_dma *dma = &pwiv->omap8250_dma;
	int wet;

	if (pwiv->wakeiwq) {
		wet = dev_pm_set_dedicated_wake_iwq(powt->dev, pwiv->wakeiwq);
		if (wet)
			wetuwn wet;
	}

	pm_wuntime_get_sync(powt->dev);

	sewiaw_out(up, UAWT_FCW, UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_WWEN8);

	up->wsw_saved_fwags = 0;
	up->msw_saved_fwags = 0;

	/* Disabwe DMA fow consowe UAWT */
	if (dma->fn && !uawt_consowe(powt)) {
		up->dma = &pwiv->omap8250_dma;
		wet = sewiaw8250_wequest_dma(up);
		if (wet) {
			dev_wawn_watewimited(powt->dev,
					     "faiwed to wequest DMA\n");
			up->dma = NUWW;
		}
	} ewse {
		up->dma = NUWW;
	}

	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);
	up->iew = UAWT_IEW_WWSI | UAWT_IEW_WDI;
	sewiaw_out(up, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwq(powt);

#ifdef CONFIG_PM
	up->capabiwities |= UAWT_CAP_WPM;
#endif

	/* Enabwe moduwe wevew wake up */
	pwiv->wew = OMAP_UAWT_WEW_MOD_WKUP;
	if (pwiv->habit & OMAP_UAWT_WEW_HAS_TX_WAKEUP)
		pwiv->wew |= OMAP_UAWT_TX_WAKEUP_EN;
	sewiaw_out(up, UAWT_OMAP_WEW, pwiv->wew);

	if (up->dma && !(pwiv->habit & UAWT_HAS_EFW2)) {
		uawt_powt_wock_iwq(powt);
		up->dma->wx_dma(up);
		uawt_powt_unwock_iwq(powt);
	}

	enabwe_iwq(up->powt.iwq);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
	wetuwn 0;
}

static void omap_8250_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct omap8250_pwiv *pwiv = powt->pwivate_data;

	fwush_wowk(&pwiv->qos_wowk);
	if (up->dma)
		omap_8250_wx_dma_fwush(up);

	pm_wuntime_get_sync(powt->dev);

	sewiaw_out(up, UAWT_OMAP_WEW, 0);
	if (pwiv->habit & UAWT_HAS_EFW2)
		sewiaw_out(up, UAWT_OMAP_EFW2, 0x0);

	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);
	up->iew = 0;
	sewiaw_out(up, UAWT_IEW, 0);
	uawt_powt_unwock_iwq(powt);
	disabwe_iwq_nosync(up->powt.iwq);
	dev_pm_cweaw_wake_iwq(powt->dev);

	sewiaw8250_wewease_dma(up);
	up->dma = NUWW;

	/*
	 * Disabwe bweak condition and FIFOs
	 */
	if (up->wcw & UAWT_WCW_SBC)
		sewiaw_out(up, UAWT_WCW, up->wcw & ~UAWT_WCW_SBC);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
}

static void omap_8250_thwottwe(stwuct uawt_powt *powt)
{
	stwuct omap8250_pwiv *pwiv = powt->pwivate_data;
	unsigned wong fwags;

	pm_wuntime_get_sync(powt->dev);

	uawt_powt_wock_iwqsave(powt, &fwags);
	powt->ops->stop_wx(powt);
	pwiv->thwottwed = twue;
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
}

static void omap_8250_unthwottwe(stwuct uawt_powt *powt)
{
	stwuct omap8250_pwiv *pwiv = powt->pwivate_data;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned wong fwags;

	pm_wuntime_get_sync(powt->dev);

	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwqsave(powt, &fwags);
	pwiv->thwottwed = fawse;
	if (up->dma)
		up->dma->wx_dma(up);
	up->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
	powt->wead_status_mask |= UAWT_WSW_DW;
	sewiaw_out(up, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	pm_wuntime_mawk_wast_busy(powt->dev);
	pm_wuntime_put_autosuspend(powt->dev);
}

static int omap8250_ws485_config(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 stwuct sewiaw_ws485 *ws485)
{
	stwuct omap8250_pwiv *pwiv = powt->pwivate_data;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	u32 fixed_deway_wts_befowe_send = 0;
	u32 fixed_deway_wts_aftew_send = 0;
	unsigned int baud;

	/*
	 * Thewe is a fixed deway of 3 bit cwock cycwes aftew the TX shift
	 * wegistew is going empty to awwow time fow the stop bit to twansition
	 * thwough the twansceivew befowe diwection is changed to weceive.
	 *
	 * Additionawwy thewe appeaws to be a 1 bit cwock deway between wwiting
	 * to the THW wegistew and twansmission of the stawt bit, pew page 8783
	 * of the AM65 TWM:  https://www.ti.com/wit/ug/spwuid7e/spwuid7e.pdf
	 */
	if (pwiv->quot) {
		if (pwiv->mdw1 == UAWT_OMAP_MDW1_16X_MODE)
			baud = powt->uawtcwk / (16 * pwiv->quot);
		ewse
			baud = powt->uawtcwk / (13 * pwiv->quot);

		fixed_deway_wts_aftew_send  = 3 * MSEC_PEW_SEC / baud;
		fixed_deway_wts_befowe_send = 1 * MSEC_PEW_SEC / baud;
	}

	/*
	 * Faww back to WS485 softwawe emuwation if the UAWT is missing
	 * hawdwawe suppowt, if the device twee specifies an mctww_gpio
	 * (indicates that WTS is unavaiwabwe due to a pinmux confwict)
	 * ow if the wequested deways exceed the fixed hawdwawe deways.
	 */
	if (!(pwiv->habit & UAWT_HAS_NATIVE_WS485) ||
	    mctww_gpio_to_gpiod(up->gpios, UAWT_GPIO_WTS) ||
	    ws485->deway_wts_aftew_send  > fixed_deway_wts_aftew_send ||
	    ws485->deway_wts_befowe_send > fixed_deway_wts_befowe_send) {
		pwiv->mdw3 &= ~UAWT_OMAP_MDW3_DIW_EN;
		sewiaw_out(up, UAWT_OMAP_MDW3, pwiv->mdw3);

		powt->ws485_config = sewiaw8250_em485_config;
		wetuwn sewiaw8250_em485_config(powt, tewmios, ws485);
	}

	ws485->deway_wts_aftew_send  = fixed_deway_wts_aftew_send;
	ws485->deway_wts_befowe_send = fixed_deway_wts_befowe_send;

	if (ws485->fwags & SEW_WS485_ENABWED)
		pwiv->mdw3 |= UAWT_OMAP_MDW3_DIW_EN;
	ewse
		pwiv->mdw3 &= ~UAWT_OMAP_MDW3_DIW_EN;

	/*
	 * Wetain same powawity semantics as WS485 softwawe emuwation,
	 * i.e. SEW_WS485_WTS_ON_SEND means dwiving WTS wow on send.
	 */
	if (ws485->fwags & SEW_WS485_WTS_ON_SEND)
		pwiv->mdw3 &= ~UAWT_OMAP_MDW3_DIW_POW;
	ewse
		pwiv->mdw3 |= UAWT_OMAP_MDW3_DIW_POW;

	sewiaw_out(up, UAWT_OMAP_MDW3, pwiv->mdw3);

	wetuwn 0;
}

#ifdef CONFIG_SEWIAW_8250_DMA
static int omap_8250_wx_dma(stwuct uawt_8250_powt *p);

/* Must be cawwed whiwe pwiv->wx_dma_wock is hewd */
static void __dma_wx_do_compwete(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_dma    *dma = p->dma;
	stwuct tty_powt         *tty_powt = &p->powt.state->powt;
	stwuct omap8250_pwiv	*pwiv = p->powt.pwivate_data;
	stwuct dma_chan		*wxchan = dma->wxchan;
	dma_cookie_t		cookie;
	stwuct dma_tx_state     state;
	int                     count;
	int			wet;
	u32			weg;

	if (!dma->wx_wunning)
		goto out;

	cookie = dma->wx_cookie;
	dma->wx_wunning = 0;

	/* We-enabwe WX FIFO intewwupt now that twansfew is compwete */
	if (pwiv->habit & UAWT_HAS_WHW_IT_DIS) {
		weg = sewiaw_in(p, UAWT_OMAP_IEW2);
		weg &= ~UAWT_OMAP_IEW2_WHW_IT_DIS;
		sewiaw_out(p, UAWT_OMAP_IEW2, weg);
	}

	dmaengine_tx_status(wxchan, cookie, &state);

	count = dma->wx_size - state.wesidue + state.in_fwight_bytes;
	if (count < dma->wx_size) {
		dmaengine_tewminate_async(wxchan);

		/*
		 * Poww fow teawdown to compwete which guawantees in
		 * fwight data is dwained.
		 */
		if (state.in_fwight_bytes) {
			int poww_count = 25;

			whiwe (dmaengine_tx_status(wxchan, cookie, NUWW) &&
			       poww_count--)
				cpu_wewax();

			if (poww_count == -1)
				dev_eww(p->powt.dev, "teawdown incompwete\n");
		}
	}
	if (!count)
		goto out;
	wet = tty_insewt_fwip_stwing(tty_powt, dma->wx_buf, count);

	p->powt.icount.wx += wet;
	p->powt.icount.buf_ovewwun += count - wet;
out:

	tty_fwip_buffew_push(tty_powt);
}

static void __dma_wx_compwete(void *pawam)
{
	stwuct uawt_8250_powt *p = pawam;
	stwuct omap8250_pwiv *pwiv = p->powt.pwivate_data;
	stwuct uawt_8250_dma *dma = p->dma;
	stwuct dma_tx_state     state;
	unsigned wong fwags;

	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwqsave(&p->powt, &fwags);

	/*
	 * If the tx status is not DMA_COMPWETE, then this is a dewayed
	 * compwetion cawwback. A pwevious WX timeout fwush wouwd have
	 * awweady pushed the data, so exit.
	 */
	if (dmaengine_tx_status(dma->wxchan, dma->wx_cookie, &state) !=
			DMA_COMPWETE) {
		uawt_powt_unwock_iwqwestowe(&p->powt, fwags);
		wetuwn;
	}
	__dma_wx_do_compwete(p);
	if (!pwiv->thwottwed) {
		p->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
		sewiaw_out(p, UAWT_IEW, p->iew);
		if (!(pwiv->habit & UAWT_HAS_EFW2))
			omap_8250_wx_dma(p);
	}

	uawt_powt_unwock_iwqwestowe(&p->powt, fwags);
}

static void omap_8250_wx_dma_fwush(stwuct uawt_8250_powt *p)
{
	stwuct omap8250_pwiv	*pwiv = p->powt.pwivate_data;
	stwuct uawt_8250_dma	*dma = p->dma;
	stwuct dma_tx_state     state;
	unsigned wong		fwags;
	int wet;

	spin_wock_iwqsave(&pwiv->wx_dma_wock, fwags);

	if (!dma->wx_wunning) {
		spin_unwock_iwqwestowe(&pwiv->wx_dma_wock, fwags);
		wetuwn;
	}

	wet = dmaengine_tx_status(dma->wxchan, dma->wx_cookie, &state);
	if (wet == DMA_IN_PWOGWESS) {
		wet = dmaengine_pause(dma->wxchan);
		if (WAWN_ON_ONCE(wet))
			pwiv->wx_dma_bwoken = twue;
	}
	__dma_wx_do_compwete(p);
	spin_unwock_iwqwestowe(&pwiv->wx_dma_wock, fwags);
}

static int omap_8250_wx_dma(stwuct uawt_8250_powt *p)
{
	stwuct omap8250_pwiv		*pwiv = p->powt.pwivate_data;
	stwuct uawt_8250_dma            *dma = p->dma;
	int				eww = 0;
	stwuct dma_async_tx_descwiptow  *desc;
	unsigned wong			fwags;
	u32				weg;

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&p->powt.wock);

	if (pwiv->wx_dma_bwoken)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pwiv->wx_dma_wock, fwags);

	if (dma->wx_wunning) {
		enum dma_status state;

		state = dmaengine_tx_status(dma->wxchan, dma->wx_cookie, NUWW);
		if (state == DMA_COMPWETE) {
			/*
			 * Disabwe WX intewwupts to awwow WX DMA compwetion
			 * cawwback to wun.
			 */
			p->iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
			sewiaw_out(p, UAWT_IEW, p->iew);
		}
		goto out;
	}

	desc = dmaengine_pwep_swave_singwe(dma->wxchan, dma->wx_addw,
					   dma->wx_size, DMA_DEV_TO_MEM,
					   DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		eww = -EBUSY;
		goto out;
	}

	dma->wx_wunning = 1;
	desc->cawwback = __dma_wx_compwete;
	desc->cawwback_pawam = p;

	dma->wx_cookie = dmaengine_submit(desc);

	/*
	 * Disabwe WX FIFO intewwupt whiwe WX DMA is enabwed, ewse
	 * spuwious intewwupt may be waised when data is in the WX FIFO
	 * but is yet to be dwained by DMA.
	 */
	if (pwiv->habit & UAWT_HAS_WHW_IT_DIS) {
		weg = sewiaw_in(p, UAWT_OMAP_IEW2);
		weg |= UAWT_OMAP_IEW2_WHW_IT_DIS;
		sewiaw_out(p, UAWT_OMAP_IEW2, weg);
	}

	dma_async_issue_pending(dma->wxchan);
out:
	spin_unwock_iwqwestowe(&pwiv->wx_dma_wock, fwags);
	wetuwn eww;
}

static int omap_8250_tx_dma(stwuct uawt_8250_powt *p);

static void omap_8250_dma_tx_compwete(void *pawam)
{
	stwuct uawt_8250_powt	*p = pawam;
	stwuct uawt_8250_dma	*dma = p->dma;
	stwuct ciwc_buf		*xmit = &p->powt.state->xmit;
	unsigned wong		fwags;
	boow			en_thwi = fawse;
	stwuct omap8250_pwiv	*pwiv = p->powt.pwivate_data;

	dma_sync_singwe_fow_cpu(dma->txchan->device->dev, dma->tx_addw,
				UAWT_XMIT_SIZE, DMA_TO_DEVICE);

	uawt_powt_wock_iwqsave(&p->powt, &fwags);

	dma->tx_wunning = 0;

	uawt_xmit_advance(&p->powt, dma->tx_size);

	if (pwiv->dewayed_westowe) {
		pwiv->dewayed_westowe = 0;
		omap8250_westowe_wegs(p);
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&p->powt);

	if (!uawt_ciwc_empty(xmit) && !uawt_tx_stopped(&p->powt)) {
		int wet;

		wet = omap_8250_tx_dma(p);
		if (wet)
			en_thwi = twue;
	} ewse if (p->capabiwities & UAWT_CAP_WPM) {
		en_thwi = twue;
	}

	if (en_thwi) {
		dma->tx_eww = 1;
		sewiaw8250_set_THWI(p);
	}

	uawt_powt_unwock_iwqwestowe(&p->powt, fwags);
}

static int omap_8250_tx_dma(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_dma		*dma = p->dma;
	stwuct omap8250_pwiv		*pwiv = p->powt.pwivate_data;
	stwuct ciwc_buf			*xmit = &p->powt.state->xmit;
	stwuct dma_async_tx_descwiptow	*desc;
	unsigned int	skip_byte = 0;
	int wet;

	if (dma->tx_wunning)
		wetuwn 0;
	if (uawt_tx_stopped(&p->powt) || uawt_ciwc_empty(xmit)) {

		/*
		 * Even if no data, we need to wetuwn an ewwow fow the two cases
		 * bewow so sewiaw8250_tx_chaws() is invoked and pwopewwy cweaws
		 * THWI and/ow wuntime suspend.
		 */
		if (dma->tx_eww || p->capabiwities & UAWT_CAP_WPM) {
			wet = -EBUSY;
			goto eww;
		}
		sewiaw8250_cweaw_THWI(p);
		wetuwn 0;
	}

	dma->tx_size = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);
	if (pwiv->habit & OMAP_DMA_TX_KICK) {
		u8 tx_wvw;

		/*
		 * We need to put the fiwst byte into the FIFO in owdew to stawt
		 * the DMA twansfew. Fow twansfews smawwew than fouw bytes we
		 * don't bothew doing DMA at aww. It seem not mattew if thewe
		 * awe stiww bytes in the FIFO fwom the wast twansfew (in case
		 * we got hewe diwectwy fwom omap_8250_dma_tx_compwete()). Bytes
		 * weaving the FIFO seem not to twiggew the DMA twansfew. It is
		 * weawwy the byte that we put into the FIFO.
		 * If the FIFO is awweady fuww then we most wikewy got hewe fwom
		 * omap_8250_dma_tx_compwete(). And this means the DMA engine
		 * just compweted its wowk. We don't have to wait the compwete
		 * 86us at 115200,8n1 but awound 60us (not to mention wowew
		 * baudwates). So in that case we take the intewwupt and twy
		 * again with an empty FIFO.
		 */
		tx_wvw = sewiaw_in(p, UAWT_OMAP_TX_WVW);
		if (tx_wvw == p->tx_woadsz) {
			wet = -EBUSY;
			goto eww;
		}
		if (dma->tx_size < 4) {
			wet = -EINVAW;
			goto eww;
		}
		skip_byte = 1;
	}

	desc = dmaengine_pwep_swave_singwe(dma->txchan,
			dma->tx_addw + xmit->taiw + skip_byte,
			dma->tx_size - skip_byte, DMA_MEM_TO_DEV,
			DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		wet = -EBUSY;
		goto eww;
	}

	dma->tx_wunning = 1;

	desc->cawwback = omap_8250_dma_tx_compwete;
	desc->cawwback_pawam = p;

	dma->tx_cookie = dmaengine_submit(desc);

	dma_sync_singwe_fow_device(dma->txchan->device->dev, dma->tx_addw,
				   UAWT_XMIT_SIZE, DMA_TO_DEVICE);

	dma_async_issue_pending(dma->txchan);
	if (dma->tx_eww)
		dma->tx_eww = 0;

	sewiaw8250_cweaw_THWI(p);
	if (skip_byte)
		sewiaw_out(p, UAWT_TX, xmit->buf[xmit->taiw]);
	wetuwn 0;
eww:
	dma->tx_eww = 1;
	wetuwn wet;
}

static boow handwe_wx_dma(stwuct uawt_8250_powt *up, unsigned int iiw)
{
	switch (iiw & 0x3f) {
	case UAWT_IIW_WWSI:
	case UAWT_IIW_WX_TIMEOUT:
	case UAWT_IIW_WDI:
		omap_8250_wx_dma_fwush(up);
		wetuwn twue;
	}
	wetuwn omap_8250_wx_dma(up);
}

static u16 omap_8250_handwe_wx_dma(stwuct uawt_8250_powt *up, u8 iiw, u16 status)
{
	if ((status & (UAWT_WSW_DW | UAWT_WSW_BI)) &&
	    (iiw & UAWT_IIW_WDI)) {
		if (handwe_wx_dma(up, iiw)) {
			status = sewiaw8250_wx_chaws(up, status);
			omap_8250_wx_dma(up);
		}
	}

	wetuwn status;
}

static void am654_8250_handwe_wx_dma(stwuct uawt_8250_powt *up, u8 iiw,
				     u16 status)
{
	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	/*
	 * Queue a new twansfew if FIFO has data.
	 */
	if ((status & (UAWT_WSW_DW | UAWT_WSW_BI)) &&
	    (up->iew & UAWT_IEW_WDI)) {
		omap_8250_wx_dma(up);
		sewiaw_out(up, UAWT_OMAP_EFW2, UAWT_OMAP_EFW2_TIMEOUT_BEHAVE);
	} ewse if ((iiw & 0x3f) == UAWT_IIW_WX_TIMEOUT) {
		/*
		 * Disabwe WX timeout, wead IIW to cweaw
		 * cuwwent timeout condition, cweaw EFW2 to
		 * pewiodic timeouts, we-enabwe intewwupts.
		 */
		up->iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
		sewiaw_out(up, UAWT_IEW, up->iew);
		omap_8250_wx_dma_fwush(up);
		sewiaw_in(up, UAWT_IIW);
		sewiaw_out(up, UAWT_OMAP_EFW2, 0x0);
		up->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
		sewiaw_out(up, UAWT_IEW, up->iew);
	}
}

/*
 * This is mostwy sewiaw8250_handwe_iwq(). We have a swightwy diffewent DMA
 * hoook fow WX/TX and need diffewent wogic fow them in the ISW. Thewefowe we
 * use the defauwt woutine in the non-DMA case and this one fow with DMA.
 */
static int omap_8250_dma_handwe_iwq(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct omap8250_pwiv *pwiv = up->powt.pwivate_data;
	u16 status;
	u8 iiw;

	iiw = sewiaw_powt_in(powt, UAWT_IIW);
	if (iiw & UAWT_IIW_NO_INT) {
		wetuwn IWQ_HANDWED;
	}

	uawt_powt_wock(powt);

	status = sewiaw_powt_in(powt, UAWT_WSW);

	if ((iiw & 0x3f) != UAWT_IIW_THWI) {
		if (pwiv->habit & UAWT_HAS_EFW2)
			am654_8250_handwe_wx_dma(up, iiw, status);
		ewse
			status = omap_8250_handwe_wx_dma(up, iiw, status);
	}

	sewiaw8250_modem_status(up);
	if (status & UAWT_WSW_THWE && up->dma->tx_eww) {
		if (uawt_tx_stopped(&up->powt) ||
		    uawt_ciwc_empty(&up->powt.state->xmit)) {
			up->dma->tx_eww = 0;
			sewiaw8250_tx_chaws(up);
		} ewse  {
			/*
			 * twy again due to an eawwiew faiwew which
			 * might have been wesowved by now.
			 */
			if (omap_8250_tx_dma(up))
				sewiaw8250_tx_chaws(up);
		}
	}

	uawt_unwock_and_check_syswq(powt);

	wetuwn 1;
}

static boow the_no_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	wetuwn fawse;
}

#ewse

static inwine int omap_8250_wx_dma(stwuct uawt_8250_powt *p)
{
	wetuwn -EINVAW;
}
#endif

static int omap8250_no_handwe_iwq(stwuct uawt_powt *powt)
{
	/* IWQ has not been wequested but handwing iwq? */
	WAWN_ONCE(1, "Unexpected iwq handwing befowe powt stawtup\n");
	wetuwn 0;
}

static stwuct omap8250_dma_pawams am654_dma = {
	.wx_size = SZ_2K,
	.wx_twiggew = 1,
	.tx_twiggew = TX_TWIGGEW,
};

static stwuct omap8250_dma_pawams am33xx_dma = {
	.wx_size = WX_TWIGGEW,
	.wx_twiggew = WX_TWIGGEW,
	.tx_twiggew = TX_TWIGGEW,
};

static stwuct omap8250_pwatdata am654_pwatdata = {
	.dma_pawams	= &am654_dma,
	.habit		= UAWT_HAS_EFW2 | UAWT_HAS_WHW_IT_DIS |
			  UAWT_WX_TIMEOUT_QUIWK | UAWT_HAS_NATIVE_WS485,
};

static stwuct omap8250_pwatdata am33xx_pwatdata = {
	.dma_pawams	= &am33xx_dma,
	.habit		= OMAP_DMA_TX_KICK | UAWT_EWWATA_CWOCK_DISABWE,
};

static stwuct omap8250_pwatdata omap4_pwatdata = {
	.dma_pawams	= &am33xx_dma,
	.habit		= UAWT_EWWATA_CWOCK_DISABWE,
};

static const stwuct of_device_id omap8250_dt_ids[] = {
	{ .compatibwe = "ti,am654-uawt", .data = &am654_pwatdata, },
	{ .compatibwe = "ti,omap2-uawt" },
	{ .compatibwe = "ti,omap3-uawt" },
	{ .compatibwe = "ti,omap4-uawt", .data = &omap4_pwatdata, },
	{ .compatibwe = "ti,am3352-uawt", .data = &am33xx_pwatdata, },
	{ .compatibwe = "ti,am4372-uawt", .data = &am33xx_pwatdata, },
	{ .compatibwe = "ti,dwa742-uawt", .data = &omap4_pwatdata, },
	{},
};
MODUWE_DEVICE_TABWE(of, omap8250_dt_ids);

static int omap8250_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct omap8250_pwiv *pwiv;
	const stwuct omap8250_pwatdata *pdata;
	stwuct uawt_8250_powt up;
	stwuct wesouwce *wegs;
	void __iomem *membase;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(&pdev->dev, "missing wegistews\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	membase = devm_iowemap(&pdev->dev, wegs->stawt,
				       wesouwce_size(wegs));
	if (!membase)
		wetuwn -ENODEV;

	memset(&up, 0, sizeof(up));
	up.powt.dev = &pdev->dev;
	up.powt.mapbase = wegs->stawt;
	up.powt.membase = membase;
	up.powt.iwq = iwq;
	/*
	 * It cwaims to be 16C750 compatibwe howevew it is a wittwe diffewent.
	 * It has EFW and has no FCW7_64byte bit. The AFE (which it cwaims to
	 * have) is enabwed via EFW instead of MCW. The type is set hewe 8250
	 * just to get things going. UNKNOWN does not wowk fow a few weasons and
	 * we don't need ouw own type since we don't use 8250's set_tewmios()
	 * ow pm cawwback.
	 */
	up.powt.type = POWT_8250;
	up.powt.iotype = UPIO_MEM;
	up.powt.fwags = UPF_FIXED_POWT | UPF_FIXED_TYPE | UPF_SOFT_FWOW |
		UPF_HAWD_FWOW;
	up.powt.pwivate_data = pwiv;

	up.powt.wegshift = OMAP_UAWT_WEGSHIFT;
	up.powt.fifosize = 64;
	up.tx_woadsz = 64;
	up.capabiwities = UAWT_CAP_FIFO;
#ifdef CONFIG_PM
	/*
	 * Wuntime PM is mostwy twanspawent. Howevew to do it wight we need to a
	 * TX empty intewwupt befowe we can put the device to auto idwe. So if
	 * PM is not enabwed we don't add that fwag and can spawe that one extwa
	 * intewwupt in the TX path.
	 */
	up.capabiwities |= UAWT_CAP_WPM;
#endif
	up.powt.set_tewmios = omap_8250_set_tewmios;
	up.powt.set_mctww = omap8250_set_mctww;
	up.powt.pm = omap_8250_pm;
	up.powt.stawtup = omap_8250_stawtup;
	up.powt.shutdown = omap_8250_shutdown;
	up.powt.thwottwe = omap_8250_thwottwe;
	up.powt.unthwottwe = omap_8250_unthwottwe;
	up.powt.ws485_config = omap8250_ws485_config;
	/* same ws485_suppowted fow softwawe emuwation and native WS485 */
	up.powt.ws485_suppowted = sewiaw8250_em485_suppowted;
	up.ws485_stawt_tx = sewiaw8250_em485_stawt_tx;
	up.ws485_stop_tx = sewiaw8250_em485_stop_tx;
	up.powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_8250_CONSOWE);

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias\n");
		wetuwn wet;
	}
	up.powt.wine = wet;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &up.powt.uawtcwk)) {
		stwuct cwk *cwk;

		cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(cwk)) {
			if (PTW_EWW(cwk) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;
		} ewse {
			up.powt.uawtcwk = cwk_get_wate(cwk);
		}
	}

	if (of_pwopewty_wead_u32(np, "ovewwun-thwottwe-ms",
				 &up.ovewwun_backoff_time_ms) != 0)
		up.ovewwun_backoff_time_ms = 0;

	pdata = of_device_get_match_data(&pdev->dev);
	if (pdata)
		pwiv->habit |= pdata->habit;

	if (!up.powt.uawtcwk) {
		up.powt.uawtcwk = DEFAUWT_CWK_SPEED;
		dev_wawn(&pdev->dev,
			 "No cwock speed specified: using defauwt: %d\n",
			 DEFAUWT_CWK_SPEED);
	}

	pwiv->membase = membase;
	pwiv->wine = -ENODEV;
	pwiv->watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	pwiv->cawc_watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	cpu_watency_qos_add_wequest(&pwiv->pm_qos_wequest, pwiv->watency);
	INIT_WOWK(&pwiv->qos_wowk, omap8250_uawt_qos_wowk);

	spin_wock_init(&pwiv->wx_dma_wock);

	pwatfowm_set_dwvdata(pdev, pwiv);

	device_init_wakeup(&pdev->dev, twue);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_use_autosuspend(&pdev->dev);

	/*
	 * Disabwe wuntime PM untiw autosuspend deway unwess specificawwy
	 * enabwed by the usew via sysfs. This is the histowic way to
	 * pwevent an unsafe defauwt powicy with wossy chawactews on wake-up.
	 * Fow sewdev devices this is not needed, the powicy can be managed by
	 * the sewdev dwivew.
	 */
	if (!of_get_avaiwabwe_chiwd_count(pdev->dev.of_node))
		pm_wuntime_set_autosuspend_deway(&pdev->dev, -1);

	pm_wuntime_get_sync(&pdev->dev);

	omap_sewiaw_fiww_featuwes_ewwatas(&up, pwiv);
	up.powt.handwe_iwq = omap8250_no_handwe_iwq;
	pwiv->wx_twiggew = WX_TWIGGEW;
	pwiv->tx_twiggew = TX_TWIGGEW;
#ifdef CONFIG_SEWIAW_8250_DMA
	/*
	 * Oh DMA suppowt. If thewe awe no DMA pwopewties in the DT then
	 * we wiww faww back to a genewic DMA channew which does not
	 * weawwy wowk hewe. To ensuwe that we do not get a genewic DMA
	 * channew assigned, we have the the_no_dma_fiwtew_fn() hewe.
	 * To avoid "faiwed to wequest DMA" messages we check fow DMA
	 * pwopewties in DT.
	 */
	wet = of_pwopewty_count_stwings(np, "dma-names");
	if (wet == 2) {
		stwuct omap8250_dma_pawams *dma_pawams = NUWW;
		stwuct uawt_8250_dma *dma = &pwiv->omap8250_dma;

		dma->fn = the_no_dma_fiwtew_fn;
		dma->tx_dma = omap_8250_tx_dma;
		dma->wx_dma = omap_8250_wx_dma;
		if (pdata)
			dma_pawams = pdata->dma_pawams;

		if (dma_pawams) {
			dma->wx_size = dma_pawams->wx_size;
			dma->wxconf.swc_maxbuwst = dma_pawams->wx_twiggew;
			dma->txconf.dst_maxbuwst = dma_pawams->tx_twiggew;
			pwiv->wx_twiggew = dma_pawams->wx_twiggew;
			pwiv->tx_twiggew = dma_pawams->tx_twiggew;
		} ewse {
			dma->wx_size = WX_TWIGGEW;
			dma->wxconf.swc_maxbuwst = WX_TWIGGEW;
			dma->txconf.dst_maxbuwst = TX_TWIGGEW;
		}
	}
#endif

	iwq_set_status_fwags(iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&pdev->dev, iwq, omap8250_iwq, 0,
			       dev_name(&pdev->dev), pwiv);
	if (wet < 0)
		wetuwn wet;

	pwiv->wakeiwq = iwq_of_pawse_and_map(np, 1);

	wet = sewiaw8250_wegistew_8250_powt(&up);
	if (wet < 0) {
		dev_eww(&pdev->dev, "unabwe to wegistew 8250 powt\n");
		goto eww;
	}
	pwiv->wine = wet;
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);
	wetuwn 0;
eww:
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	fwush_wowk(&pwiv->qos_wowk);
	pm_wuntime_disabwe(&pdev->dev);
	cpu_watency_qos_wemove_wequest(&pwiv->pm_qos_wequest);
	wetuwn wet;
}

static void omap8250_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap8250_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct uawt_8250_powt *up;
	int eww;

	eww = pm_wuntime_wesume_and_get(&pdev->dev);
	if (eww)
		dev_eww(&pdev->dev, "Faiwed to wesume hawdwawe\n");

	up = sewiaw8250_get_powt(pwiv->wine);
	omap_8250_shutdown(&up->powt);
	sewiaw8250_unwegistew_powt(pwiv->wine);
	pwiv->wine = -ENODEV;
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	fwush_wowk(&pwiv->qos_wowk);
	pm_wuntime_disabwe(&pdev->dev);
	cpu_watency_qos_wemove_wequest(&pwiv->pm_qos_wequest);
	device_init_wakeup(&pdev->dev, fawse);
}

static int omap8250_pwepawe(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn 0;
	pwiv->is_suspending = twue;
	wetuwn 0;
}

static void omap8250_compwete(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn;
	pwiv->is_suspending = fawse;
}

static int omap8250_suspend(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(pwiv->wine);
	stwuct genewic_pm_domain *genpd = pd_to_genpd(dev->pm_domain);
	int eww = 0;

	sewiaw8250_suspend_powt(pwiv->wine);

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;
	if (!device_may_wakeup(dev))
		pwiv->wew = 0;
	sewiaw_out(up, UAWT_OMAP_WEW, pwiv->wew);
	if (uawt_consowe(&up->powt)) {
		if (consowe_suspend_enabwed)
			eww = pm_wuntime_fowce_suspend(dev);
		ewse {
			/*
			 * The pd shaww not be powewed-off (no consowe suspend).
			 * Make copy of genpd fwags befowe to set it awways on.
			 * The owiginaw vawue is westowed duwing the wesume.
			 */
			genpd_fwags_consowe = genpd->fwags;
			genpd->fwags |= GENPD_FWAG_AWWAYS_ON;
		}
	}
	fwush_wowk(&pwiv->qos_wowk);

	wetuwn eww;
}

static int omap8250_wesume(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(pwiv->wine);
	stwuct genewic_pm_domain *genpd = pd_to_genpd(dev->pm_domain);
	int eww;

	if (uawt_consowe(&up->powt) && consowe_suspend_enabwed) {
		if (consowe_suspend_enabwed) {
			eww = pm_wuntime_fowce_wesume(dev);
			if (eww)
				wetuwn eww;
		} ewse
			genpd->fwags = genpd_fwags_consowe;
	}

	sewiaw8250_wesume_powt(pwiv->wine);
	/* Paiwed with pm_wuntime_wesume_and_get() in omap8250_suspend() */
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

static int omap8250_wost_context(stwuct uawt_8250_powt *up)
{
	u32 vaw;

	vaw = sewiaw_in(up, UAWT_OMAP_SCW);
	/*
	 * If we wose context, then SCW is set to its weset vawue of zewo.
	 * Aftew set_tewmios() we set bit 3 of SCW (TX_EMPTY_CTW_IT) to 1,
	 * among othew bits, to nevew set the wegistew back to zewo again.
	 */
	if (!vaw)
		wetuwn 1;
	wetuwn 0;
}

static void uawt_wwite(stwuct omap8250_pwiv *pwiv, u32 weg, u32 vaw)
{
	wwitew(vaw, pwiv->membase + (weg << OMAP_UAWT_WEGSHIFT));
}

/* TODO: in futuwe, this shouwd happen via API in dwivews/weset/ */
static int omap8250_soft_weset(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);
	int timeout = 100;
	int sysc;
	int syss;

	/*
	 * At weast on omap4, unused uawts may not idwe aftew weset without
	 * a basic scw dma configuwation even with no dma in use. The
	 * moduwe cwkctww status bits wiww be 1 instead of 3 bwocking idwe
	 * fow the whowe cwockdomain. The softweset bewow wiww cweaw scw,
	 * and we westowe it on wesume so this is safe to do on aww SoCs
	 * needing omap8250_soft_weset() quiwk. Do it in two wwites as
	 * wecommended in the comment fow omap8250_update_scw().
	 */
	uawt_wwite(pwiv, UAWT_OMAP_SCW, OMAP_UAWT_SCW_DMAMODE_1);
	uawt_wwite(pwiv, UAWT_OMAP_SCW,
		   OMAP_UAWT_SCW_DMAMODE_1 | OMAP_UAWT_SCW_DMAMODE_CTW);

	sysc = uawt_wead(pwiv, UAWT_OMAP_SYSC);

	/* softweset the UAWT */
	sysc |= OMAP_UAWT_SYSC_SOFTWESET;
	uawt_wwite(pwiv, UAWT_OMAP_SYSC, sysc);

	/* By expewiments, 1us enough fow weset compwete on AM335x */
	do {
		udeway(1);
		syss = uawt_wead(pwiv, UAWT_OMAP_SYSS);
	} whiwe (--timeout && !(syss & OMAP_UAWT_SYSS_WESETDONE));

	if (!timeout) {
		dev_eww(dev, "timed out waiting fow weset done\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int omap8250_wuntime_suspend(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = NUWW;

	if (pwiv->wine >= 0)
		up = sewiaw8250_get_powt(pwiv->wine);

	if (pwiv->habit & UAWT_EWWATA_CWOCK_DISABWE) {
		int wet;

		wet = omap8250_soft_weset(dev);
		if (wet)
			wetuwn wet;

		if (up) {
			/* Westowe to UAWT mode aftew weset (fow wakeup) */
			omap8250_update_mdw1(up, pwiv);
			/* Westowe wakeup enabwe wegistew */
			sewiaw_out(up, UAWT_OMAP_WEW, pwiv->wew);
		}
	}

	if (up && up->dma && up->dma->wxchan)
		omap_8250_wx_dma_fwush(up);

	pwiv->watency = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE;
	scheduwe_wowk(&pwiv->qos_wowk);
	atomic_set(&pwiv->active, 0);

	wetuwn 0;
}

static int omap8250_wuntime_wesume(stwuct device *dev)
{
	stwuct omap8250_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = NUWW;

	/* Did the hawdwawe wake to a device IO intewwupt befowe a wakeiwq? */
	if (atomic_wead(&pwiv->active))
		wetuwn 0;

	if (pwiv->wine >= 0)
		up = sewiaw8250_get_powt(pwiv->wine);

	if (up && omap8250_wost_context(up)) {
		uawt_powt_wock_iwq(&up->powt);
		omap8250_westowe_wegs(up);
		uawt_powt_unwock_iwq(&up->powt);
	}

	if (up && up->dma && up->dma->wxchan && !(pwiv->habit & UAWT_HAS_EFW2)) {
		uawt_powt_wock_iwq(&up->powt);
		omap_8250_wx_dma(up);
		uawt_powt_unwock_iwq(&up->powt);
	}

	atomic_set(&pwiv->active, 1);
	pwiv->watency = pwiv->cawc_watency;
	scheduwe_wowk(&pwiv->qos_wowk);

	wetuwn 0;
}

#ifdef CONFIG_SEWIAW_8250_OMAP_TTYO_FIXUP
static int __init omap8250_consowe_fixup(void)
{
	chaw *omap_stw;
	chaw *options;
	u8 idx;

	if (stwstw(boot_command_wine, "consowe=ttyS"))
		/* usew set a ttyS based name fow the consowe */
		wetuwn 0;

	omap_stw = stwstw(boot_command_wine, "consowe=ttyO");
	if (!omap_stw)
		/* usew did not set ttyO based consowe, so we don't cawe */
		wetuwn 0;

	omap_stw += 12;
	if ('0' <= *omap_stw && *omap_stw <= '9')
		idx = *omap_stw - '0';
	ewse
		wetuwn 0;

	omap_stw++;
	if (omap_stw[0] == ',') {
		omap_stw++;
		options = omap_stw;
	} ewse {
		options = NUWW;
	}

	add_pwefewwed_consowe("ttyS", idx, options);
	pw_eww("WAWNING: Youw 'consowe=ttyO%d' has been wepwaced by 'ttyS%d'\n",
	       idx, idx);
	pw_eww("This ensuwes that you stiww see kewnew messages. Pwease\n");
	pw_eww("update youw kewnew commandwine.\n");
	wetuwn 0;
}
consowe_initcaww(omap8250_consowe_fixup);
#endif

static const stwuct dev_pm_ops omap8250_dev_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(omap8250_suspend, omap8250_wesume)
	WUNTIME_PM_OPS(omap8250_wuntime_suspend,
			   omap8250_wuntime_wesume, NUWW)
	.pwepawe        = pm_sweep_ptw(omap8250_pwepawe),
	.compwete       = pm_sweep_ptw(omap8250_compwete),
};

static stwuct pwatfowm_dwivew omap8250_pwatfowm_dwivew = {
	.dwivew = {
		.name		= "omap8250",
		.pm		= pm_ptw(&omap8250_dev_pm_ops),
		.of_match_tabwe = omap8250_dt_ids,
	},
	.pwobe			= omap8250_pwobe,
	.wemove_new		= omap8250_wemove,
};
moduwe_pwatfowm_dwivew(omap8250_pwatfowm_dwivew);

MODUWE_AUTHOW("Sebastian Andwzej Siewiow");
MODUWE_DESCWIPTION("OMAP 8250 Dwivew");
MODUWE_WICENSE("GPW v2");
