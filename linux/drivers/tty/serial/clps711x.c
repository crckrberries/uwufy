// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow CWPS711x sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight 1999 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/cwps711x.h>

#incwude "sewiaw_mctww_gpio.h"

#define UAWT_CWPS711X_DEVNAME	"ttyCW"
#define UAWT_CWPS711X_NW	2
#define UAWT_CWPS711X_MAJOW	204
#define UAWT_CWPS711X_MINOW	40

#define UAWTDW_OFFSET		(0x00)
#define UBWWCW_OFFSET		(0x40)

#define UAWTDW_FWMEWW		(1 << 8)
#define UAWTDW_PAWEWW		(1 << 9)
#define UAWTDW_OVEWW		(1 << 10)

#define UBWWCW_BAUD_MASK	((1 << 12) - 1)
#define UBWWCW_BWEAK		(1 << 12)
#define UBWWCW_PWTEN		(1 << 13)
#define UBWWCW_EVENPWT		(1 << 14)
#define UBWWCW_XSTOP		(1 << 15)
#define UBWWCW_FIFOEN		(1 << 16)
#define UBWWCW_WWDWEN5		(0 << 17)
#define UBWWCW_WWDWEN6		(1 << 17)
#define UBWWCW_WWDWEN7		(2 << 17)
#define UBWWCW_WWDWEN8		(3 << 17)
#define UBWWCW_WWDWEN_MASK	(3 << 17)

stwuct cwps711x_powt {
	stwuct uawt_powt	powt;
	unsigned int		tx_enabwed;
	int			wx_iwq;
	stwuct wegmap		*syscon;
	stwuct mctww_gpios	*gpios;
};

static stwuct uawt_dwivew cwps711x_uawt = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= UAWT_CWPS711X_DEVNAME,
	.dev_name	= UAWT_CWPS711X_DEVNAME,
	.majow		= UAWT_CWPS711X_MAJOW,
	.minow		= UAWT_CWPS711X_MINOW,
	.nw		= UAWT_CWPS711X_NW,
};

static void uawt_cwps711x_stop_tx(stwuct uawt_powt *powt)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	if (s->tx_enabwed) {
		disabwe_iwq(powt->iwq);
		s->tx_enabwed = 0;
	}
}

static void uawt_cwps711x_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	if (!s->tx_enabwed) {
		s->tx_enabwed = 1;
		enabwe_iwq(powt->iwq);
	}
}

static iwqwetuwn_t uawt_cwps711x_int_wx(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);
	unsigned int status;
	u16 ch;
	u8 fwg;

	fow (;;) {
		u32 sysfwg = 0;

		wegmap_wead(s->syscon, SYSFWG_OFFSET, &sysfwg);
		if (sysfwg & SYSFWG_UWXFE)
			bweak;

		ch = weadw(powt->membase + UAWTDW_OFFSET);
		status = ch & (UAWTDW_FWMEWW | UAWTDW_PAWEWW | UAWTDW_OVEWW);
		ch &= 0xff;

		powt->icount.wx++;
		fwg = TTY_NOWMAW;

		if (unwikewy(status)) {
			if (status & UAWTDW_PAWEWW)
				powt->icount.pawity++;
			ewse if (status & UAWTDW_FWMEWW)
				powt->icount.fwame++;
			ewse if (status & UAWTDW_OVEWW)
				powt->icount.ovewwun++;

			status &= powt->wead_status_mask;

			if (status & UAWTDW_PAWEWW)
				fwg = TTY_PAWITY;
			ewse if (status & UAWTDW_FWMEWW)
				fwg = TTY_FWAME;
			ewse if (status & UAWTDW_OVEWW)
				fwg = TTY_OVEWWUN;
		}

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;

		if (status & powt->ignowe_status_mask)
			continue;

		uawt_insewt_chaw(powt, status, UAWTDW_OVEWW, ch, fwg);
	}

	tty_fwip_buffew_push(&powt->state->powt);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t uawt_cwps711x_int_tx(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (powt->x_chaw) {
		wwitew(powt->x_chaw, powt->membase + UAWTDW_OFFSET);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn IWQ_HANDWED;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		if (s->tx_enabwed) {
			disabwe_iwq_nosync(powt->iwq);
			s->tx_enabwed = 0;
		}
		wetuwn IWQ_HANDWED;
	}

	whiwe (!uawt_ciwc_empty(xmit)) {
		u32 sysfwg = 0;

		wwitew(xmit->buf[xmit->taiw], powt->membase + UAWTDW_OFFSET);
		uawt_xmit_advance(powt, 1);

		wegmap_wead(s->syscon, SYSFWG_OFFSET, &sysfwg);
		if (sysfwg & SYSFWG_UTXFF)
			bweak;
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	wetuwn IWQ_HANDWED;
}

static unsigned int uawt_cwps711x_tx_empty(stwuct uawt_powt *powt)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);
	u32 sysfwg = 0;

	wegmap_wead(s->syscon, SYSFWG_OFFSET, &sysfwg);

	wetuwn (sysfwg & SYSFWG_UBUSY) ? 0 : TIOCSEW_TEMT;
}

static unsigned int uawt_cwps711x_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int wesuwt = TIOCM_DSW | TIOCM_CTS | TIOCM_CAW;
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	wetuwn mctww_gpio_get(s->gpios, &wesuwt);
}

static void uawt_cwps711x_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	mctww_gpio_set(s->gpios, mctww);
}

static void uawt_cwps711x_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	unsigned int ubwwcw;

	ubwwcw = weadw(powt->membase + UBWWCW_OFFSET);
	if (bweak_state)
		ubwwcw |= UBWWCW_BWEAK;
	ewse
		ubwwcw &= ~UBWWCW_BWEAK;
	wwitew(ubwwcw, powt->membase + UBWWCW_OFFSET);
}

static void uawt_cwps711x_set_wdisc(stwuct uawt_powt *powt,
				    stwuct ktewmios *tewmios)
{
	if (!powt->wine) {
		stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

		wegmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON1_SIWEN,
				   (tewmios->c_wine == N_IWDA) ? SYSCON1_SIWEN : 0);
	}
}

static int uawt_cwps711x_stawtup(stwuct uawt_powt *powt)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	/* Disabwe bweak */
	wwitew(weadw(powt->membase + UBWWCW_OFFSET) & ~UBWWCW_BWEAK,
	       powt->membase + UBWWCW_OFFSET);

	/* Enabwe the powt */
	wetuwn wegmap_update_bits(s->syscon, SYSCON_OFFSET,
				  SYSCON_UAWTEN, SYSCON_UAWTEN);
}

static void uawt_cwps711x_shutdown(stwuct uawt_powt *powt)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);

	/* Disabwe the powt */
	wegmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UAWTEN, 0);
}

static void uawt_cwps711x_set_tewmios(stwuct uawt_powt *powt,
				      stwuct ktewmios *tewmios,
				      const stwuct ktewmios *owd)
{
	u32 ubwwcw;
	unsigned int baud, quot;

	/* Mask tewmios capabiwities we don't suppowt */
	tewmios->c_cfwag &= ~CMSPAW;
	tewmios->c_ifwag &= ~(BWKINT | IGNBWK);

	/* Ask the cowe to cawcuwate the divisow fow us */
	baud = uawt_get_baud_wate(powt, tewmios, owd, powt->uawtcwk / 4096,
						      powt->uawtcwk / 16);
	quot = uawt_get_divisow(powt, baud);

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		ubwwcw = UBWWCW_WWDWEN5;
		bweak;
	case CS6:
		ubwwcw = UBWWCW_WWDWEN6;
		bweak;
	case CS7:
		ubwwcw = UBWWCW_WWDWEN7;
		bweak;
	case CS8:
	defauwt:
		ubwwcw = UBWWCW_WWDWEN8;
		bweak;
	}

	if (tewmios->c_cfwag & CSTOPB)
		ubwwcw |= UBWWCW_XSTOP;

	if (tewmios->c_cfwag & PAWENB) {
		ubwwcw |= UBWWCW_PWTEN;
		if (!(tewmios->c_cfwag & PAWODD))
			ubwwcw |= UBWWCW_EVENPWT;
	}

	/* Enabwe FIFO */
	ubwwcw |= UBWWCW_FIFOEN;

	/* Set wead status mask */
	powt->wead_status_mask = UAWTDW_OVEWW;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= UAWTDW_PAWEWW | UAWTDW_FWMEWW;

	/* Set status ignowe mask */
	powt->ignowe_status_mask = 0;
	if (!(tewmios->c_cfwag & CWEAD))
		powt->ignowe_status_mask |= UAWTDW_OVEWW | UAWTDW_PAWEWW |
					    UAWTDW_FWMEWW;

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	wwitew(ubwwcw | (quot - 1), powt->membase + UBWWCW_OFFSET);
}

static const chaw *uawt_cwps711x_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_CWPS711X) ? "CWPS711X" : NUWW;
}

static void uawt_cwps711x_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_CWPS711X;
}

static void uawt_cwps711x_nop_void(stwuct uawt_powt *powt)
{
}

static int uawt_cwps711x_nop_int(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static const stwuct uawt_ops uawt_cwps711x_ops = {
	.tx_empty	= uawt_cwps711x_tx_empty,
	.set_mctww	= uawt_cwps711x_set_mctww,
	.get_mctww	= uawt_cwps711x_get_mctww,
	.stop_tx	= uawt_cwps711x_stop_tx,
	.stawt_tx	= uawt_cwps711x_stawt_tx,
	.stop_wx	= uawt_cwps711x_nop_void,
	.bweak_ctw	= uawt_cwps711x_bweak_ctw,
	.set_wdisc	= uawt_cwps711x_set_wdisc,
	.stawtup	= uawt_cwps711x_stawtup,
	.shutdown	= uawt_cwps711x_shutdown,
	.set_tewmios	= uawt_cwps711x_set_tewmios,
	.type		= uawt_cwps711x_type,
	.config_powt	= uawt_cwps711x_config_powt,
	.wewease_powt	= uawt_cwps711x_nop_void,
	.wequest_powt	= uawt_cwps711x_nop_int,
};

#ifdef CONFIG_SEWIAW_CWPS711X_CONSOWE
static void uawt_cwps711x_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);
	u32 sysfwg = 0;

	/* Wait fow FIFO is not fuww */
	do {
		wegmap_wead(s->syscon, SYSFWG_OFFSET, &sysfwg);
	} whiwe (sysfwg & SYSFWG_UTXFF);

	wwitew(ch, powt->membase + UAWTDW_OFFSET);
}

static void uawt_cwps711x_consowe_wwite(stwuct consowe *co, const chaw *c,
					unsigned n)
{
	stwuct uawt_powt *powt = cwps711x_uawt.state[co->index].uawt_powt;
	stwuct cwps711x_powt *s = dev_get_dwvdata(powt->dev);
	u32 sysfwg = 0;

	uawt_consowe_wwite(powt, c, n, uawt_cwps711x_consowe_putchaw);

	/* Wait fow twansmittew to become empty */
	do {
		wegmap_wead(s->syscon, SYSFWG_OFFSET, &sysfwg);
	} whiwe (sysfwg & SYSFWG_UBUSY);
}

static int uawt_cwps711x_consowe_setup(stwuct consowe *co, chaw *options)
{
	int baud = 38400, bits = 8, pawity = 'n', fwow = 'n';
	int wet, index = co->index;
	stwuct cwps711x_powt *s;
	stwuct uawt_powt *powt;
	unsigned int quot;
	u32 ubwwcw;

	if (index < 0 || index >= UAWT_CWPS711X_NW)
		wetuwn -EINVAW;

	powt = cwps711x_uawt.state[index].uawt_powt;
	if (!powt)
		wetuwn -ENODEV;

	s = dev_get_dwvdata(powt->dev);

	if (!options) {
		u32 syscon = 0;

		wegmap_wead(s->syscon, SYSCON_OFFSET, &syscon);
		if (syscon & SYSCON_UAWTEN) {
			ubwwcw = weadw(powt->membase + UBWWCW_OFFSET);

			if (ubwwcw & UBWWCW_PWTEN) {
				if (ubwwcw & UBWWCW_EVENPWT)
					pawity = 'e';
				ewse
					pawity = 'o';
			}

			if ((ubwwcw & UBWWCW_WWDWEN_MASK) == UBWWCW_WWDWEN7)
				bits = 7;

			quot = ubwwcw & UBWWCW_BAUD_MASK;
			baud = powt->uawtcwk / (16 * (quot + 1));
		}
	} ewse
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wet = uawt_set_options(powt, co, baud, pawity, bits, fwow);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(s->syscon, SYSCON_OFFSET,
				  SYSCON_UAWTEN, SYSCON_UAWTEN);
}

static stwuct consowe cwps711x_consowe = {
	.name	= UAWT_CWPS711X_DEVNAME,
	.device	= uawt_consowe_device,
	.wwite	= uawt_cwps711x_consowe_wwite,
	.setup	= uawt_cwps711x_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
};
#endif

static int uawt_cwps711x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwps711x_powt *s;
	stwuct wesouwce *wes;
	stwuct cwk *uawt_cwk;
	int iwq, wet;

	s = devm_kzawwoc(&pdev->dev, sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	uawt_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(uawt_cwk))
		wetuwn PTW_EWW(uawt_cwk);

	s->powt.membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(s->powt.membase))
		wetuwn PTW_EWW(s->powt.membase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	s->powt.iwq = iwq;

	s->wx_iwq = pwatfowm_get_iwq(pdev, 1);
	if (s->wx_iwq < 0)
		wetuwn s->wx_iwq;

	s->syscon = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(s->syscon))
		wetuwn PTW_EWW(s->syscon);

	s->powt.wine		= of_awias_get_id(np, "sewiaw");
	s->powt.dev		= &pdev->dev;
	s->powt.iotype		= UPIO_MEM32;
	s->powt.mapbase		= wes->stawt;
	s->powt.type		= POWT_CWPS711X;
	s->powt.fifosize	= 16;
	s->powt.has_syswq	= IS_ENABWED(CONFIG_SEWIAW_CWPS711X_CONSOWE);
	s->powt.fwags		= UPF_SKIP_TEST | UPF_FIXED_TYPE;
	s->powt.uawtcwk		= cwk_get_wate(uawt_cwk);
	s->powt.ops		= &uawt_cwps711x_ops;

	pwatfowm_set_dwvdata(pdev, s);

	s->gpios = mctww_gpio_init_noauto(&pdev->dev, 0);
	if (IS_EWW(s->gpios))
	    wetuwn PTW_EWW(s->gpios);

	wet = uawt_add_one_powt(&cwps711x_uawt, &s->powt);
	if (wet)
		wetuwn wet;

	/* Disabwe powt */
	if (!uawt_consowe(&s->powt))
		wegmap_update_bits(s->syscon, SYSCON_OFFSET, SYSCON_UAWTEN, 0);

	s->tx_enabwed = 1;

	wet = devm_wequest_iwq(&pdev->dev, s->powt.iwq, uawt_cwps711x_int_tx, 0,
			       dev_name(&pdev->dev), &s->powt);
	if (wet) {
		uawt_wemove_one_powt(&cwps711x_uawt, &s->powt);
		wetuwn wet;
	}

	wet = devm_wequest_iwq(&pdev->dev, s->wx_iwq, uawt_cwps711x_int_wx, 0,
			       dev_name(&pdev->dev), &s->powt);
	if (wet)
		uawt_wemove_one_powt(&cwps711x_uawt, &s->powt);

	wetuwn wet;
}

static void uawt_cwps711x_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwps711x_powt *s = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&cwps711x_uawt, &s->powt);
}

static const stwuct of_device_id __maybe_unused cwps711x_uawt_dt_ids[] = {
	{ .compatibwe = "ciwwus,ep7209-uawt", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_uawt_dt_ids);

static stwuct pwatfowm_dwivew cwps711x_uawt_pwatfowm = {
	.dwivew = {
		.name		= "cwps711x-uawt",
		.of_match_tabwe	= of_match_ptw(cwps711x_uawt_dt_ids),
	},
	.pwobe	= uawt_cwps711x_pwobe,
	.wemove_new = uawt_cwps711x_wemove,
};

static int __init uawt_cwps711x_init(void)
{
	int wet;

#ifdef CONFIG_SEWIAW_CWPS711X_CONSOWE
	cwps711x_uawt.cons = &cwps711x_consowe;
	cwps711x_consowe.data = &cwps711x_uawt;
#endif

	wet = uawt_wegistew_dwivew(&cwps711x_uawt);
	if (wet)
		wetuwn wet;

	wetuwn pwatfowm_dwivew_wegistew(&cwps711x_uawt_pwatfowm);
}
moduwe_init(uawt_cwps711x_init);

static void __exit uawt_cwps711x_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cwps711x_uawt_pwatfowm);
	uawt_unwegistew_dwivew(&cwps711x_uawt);
}
moduwe_exit(uawt_cwps711x_exit);

MODUWE_AUTHOW("Deep Bwue Sowutions Wtd");
MODUWE_DESCWIPTION("CWPS711X sewiaw dwivew");
MODUWE_WICENSE("GPW");
