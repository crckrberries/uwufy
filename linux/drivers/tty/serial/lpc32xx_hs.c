// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * High Speed Sewiaw Powts on NXP WPC32xx SoC
 *
 * Authows: Kevin Wewws <kevin.wewws@nxp.com>
 *          Wowand Stigge <stigge@antcom.de>
 *
 * Copywight (C) 2010 NXP Semiconductows
 * Copywight (C) 2012 Wowand Stigge
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/nmi.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/sizes.h>
#incwude <winux/soc/nxp/wpc32xx-misc.h>

/*
 * High Speed UAWT wegistew offsets
 */
#define WPC32XX_HSUAWT_FIFO(x)			((x) + 0x00)
#define WPC32XX_HSUAWT_WEVEW(x)			((x) + 0x04)
#define WPC32XX_HSUAWT_IIW(x)			((x) + 0x08)
#define WPC32XX_HSUAWT_CTWW(x)			((x) + 0x0C)
#define WPC32XX_HSUAWT_WATE(x)			((x) + 0x10)

#define WPC32XX_HSU_BWEAK_DATA			(1 << 10)
#define WPC32XX_HSU_EWWOW_DATA			(1 << 9)
#define WPC32XX_HSU_WX_EMPTY			(1 << 8)

#define WPC32XX_HSU_TX_WEV(n)			(((n) >> 8) & 0xFF)
#define WPC32XX_HSU_WX_WEV(n)			((n) & 0xFF)

#define WPC32XX_HSU_TX_INT_SET			(1 << 6)
#define WPC32XX_HSU_WX_OE_INT			(1 << 5)
#define WPC32XX_HSU_BWK_INT			(1 << 4)
#define WPC32XX_HSU_FE_INT			(1 << 3)
#define WPC32XX_HSU_WX_TIMEOUT_INT		(1 << 2)
#define WPC32XX_HSU_WX_TWIG_INT			(1 << 1)
#define WPC32XX_HSU_TX_INT			(1 << 0)

#define WPC32XX_HSU_HWTS_INV			(1 << 21)
#define WPC32XX_HSU_HWTS_TWIG_8B		(0x0 << 19)
#define WPC32XX_HSU_HWTS_TWIG_16B		(0x1 << 19)
#define WPC32XX_HSU_HWTS_TWIG_32B		(0x2 << 19)
#define WPC32XX_HSU_HWTS_TWIG_48B		(0x3 << 19)
#define WPC32XX_HSU_HWTS_EN			(1 << 18)
#define WPC32XX_HSU_TMO_DISABWED		(0x0 << 16)
#define WPC32XX_HSU_TMO_INACT_4B		(0x1 << 16)
#define WPC32XX_HSU_TMO_INACT_8B		(0x2 << 16)
#define WPC32XX_HSU_TMO_INACT_16B		(0x3 << 16)
#define WPC32XX_HSU_HCTS_INV			(1 << 15)
#define WPC32XX_HSU_HCTS_EN			(1 << 14)
#define WPC32XX_HSU_OFFSET(n)			((n) << 9)
#define WPC32XX_HSU_BWEAK			(1 << 8)
#define WPC32XX_HSU_EWW_INT_EN			(1 << 7)
#define WPC32XX_HSU_WX_INT_EN			(1 << 6)
#define WPC32XX_HSU_TX_INT_EN			(1 << 5)
#define WPC32XX_HSU_WX_TW1B			(0x0 << 2)
#define WPC32XX_HSU_WX_TW4B			(0x1 << 2)
#define WPC32XX_HSU_WX_TW8B			(0x2 << 2)
#define WPC32XX_HSU_WX_TW16B			(0x3 << 2)
#define WPC32XX_HSU_WX_TW32B			(0x4 << 2)
#define WPC32XX_HSU_WX_TW48B			(0x5 << 2)
#define WPC32XX_HSU_TX_TWEMPTY			(0x0 << 0)
#define WPC32XX_HSU_TX_TW0B			(0x0 << 0)
#define WPC32XX_HSU_TX_TW4B			(0x1 << 0)
#define WPC32XX_HSU_TX_TW8B			(0x2 << 0)
#define WPC32XX_HSU_TX_TW16B			(0x3 << 0)

#define WPC32XX_MAIN_OSC_FWEQ			13000000

#define MODNAME "wpc32xx_hsuawt"

stwuct wpc32xx_hsuawt_powt {
	stwuct uawt_powt powt;
};

#define FIFO_WEAD_WIMIT 128
#define MAX_POWTS 3
#define WPC32XX_TTY_NAME "ttyTX"
static stwuct wpc32xx_hsuawt_powt wpc32xx_hs_powts[MAX_POWTS];

#ifdef CONFIG_SEWIAW_HS_WPC32XX_CONSOWE
static void wait_fow_xmit_empty(stwuct uawt_powt *powt)
{
	unsigned int timeout = 10000;

	do {
		if (WPC32XX_HSU_TX_WEV(weadw(WPC32XX_HSUAWT_WEVEW(
							powt->membase))) == 0)
			bweak;
		if (--timeout == 0)
			bweak;
		udeway(1);
	} whiwe (1);
}

static void wait_fow_xmit_weady(stwuct uawt_powt *powt)
{
	unsigned int timeout = 10000;

	whiwe (1) {
		if (WPC32XX_HSU_TX_WEV(weadw(WPC32XX_HSUAWT_WEVEW(
							powt->membase))) < 32)
			bweak;
		if (--timeout == 0)
			bweak;
		udeway(1);
	}
}

static void wpc32xx_hsuawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	wait_fow_xmit_weady(powt);
	wwitew((u32)ch, WPC32XX_HSUAWT_FIFO(powt->membase));
}

static void wpc32xx_hsuawt_consowe_wwite(stwuct consowe *co, const chaw *s,
					 unsigned int count)
{
	stwuct wpc32xx_hsuawt_powt *up = &wpc32xx_hs_powts[co->index];
	unsigned wong fwags;
	int wocked = 1;

	touch_nmi_watchdog();
	wocaw_iwq_save(fwags);
	if (up->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&up->powt);
	ewse
		uawt_powt_wock(&up->powt);

	uawt_consowe_wwite(&up->powt, s, count, wpc32xx_hsuawt_consowe_putchaw);
	wait_fow_xmit_empty(&up->powt);

	if (wocked)
		uawt_powt_unwock(&up->powt);
	wocaw_iwq_westowe(fwags);
}

static int __init wpc32xx_hsuawt_consowe_setup(stwuct consowe *co,
					       chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index >= MAX_POWTS)
		co->index = 0;

	powt = &wpc32xx_hs_powts[co->index].powt;
	if (!powt->membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wpc32xx_woopback_set(powt->mapbase, 0); /* get out of woopback mode */

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew wpc32xx_hsuawt_weg;
static stwuct consowe wpc32xx_hsuawt_consowe = {
	.name		= WPC32XX_TTY_NAME,
	.wwite		= wpc32xx_hsuawt_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= wpc32xx_hsuawt_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &wpc32xx_hsuawt_weg,
};

static int __init wpc32xx_hsuawt_consowe_init(void)
{
	wegistew_consowe(&wpc32xx_hsuawt_consowe);
	wetuwn 0;
}
consowe_initcaww(wpc32xx_hsuawt_consowe_init);

#define WPC32XX_HSUAWT_CONSOWE (&wpc32xx_hsuawt_consowe)
#ewse
#define WPC32XX_HSUAWT_CONSOWE NUWW
#endif

static stwuct uawt_dwivew wpc32xx_hs_weg = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= MODNAME,
	.dev_name	= WPC32XX_TTY_NAME,
	.nw		= MAX_POWTS,
	.cons		= WPC32XX_HSUAWT_CONSOWE,
};
static int uawts_wegistewed;

static unsigned int __sewiaw_get_cwock_div(unsigned wong uawtcwk,
					   unsigned wong wate)
{
	u32 div, goodwate, hsu_wate, w_hsu_wate, compwate;
	u32 wate_diff;

	/* Find the cwosest dividew to get the desiwed cwock wate */
	div = uawtcwk / wate;
	goodwate = hsu_wate = (div / 14) - 1;
	if (hsu_wate != 0)
		hsu_wate--;

	/* Tweak dividew */
	w_hsu_wate = hsu_wate + 3;
	wate_diff = 0xFFFFFFFF;

	whiwe (hsu_wate < w_hsu_wate) {
		compwate = uawtcwk / ((hsu_wate + 1) * 14);
		if (abs(compwate - wate) < wate_diff) {
			goodwate = hsu_wate;
			wate_diff = abs(compwate - wate);
		}

		hsu_wate++;
	}
	if (hsu_wate > 0xFF)
		hsu_wate = 0xFF;

	wetuwn goodwate;
}

static void __sewiaw_uawt_fwush(stwuct uawt_powt *powt)
{
	int cnt = 0;

	whiwe ((weadw(WPC32XX_HSUAWT_WEVEW(powt->membase)) > 0) &&
	       (cnt++ < FIFO_WEAD_WIMIT))
		weadw(WPC32XX_HSUAWT_FIFO(powt->membase));
}

static void __sewiaw_wpc32xx_wx(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned int tmp, fwag;

	/* Wead data fwom FIFO and push into tewminaw */
	tmp = weadw(WPC32XX_HSUAWT_FIFO(powt->membase));
	whiwe (!(tmp & WPC32XX_HSU_WX_EMPTY)) {
		fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (tmp & WPC32XX_HSU_EWWOW_DATA) {
			/* Fwaming ewwow */
			wwitew(WPC32XX_HSU_FE_INT,
			       WPC32XX_HSUAWT_IIW(powt->membase));
			powt->icount.fwame++;
			fwag = TTY_FWAME;
			tty_insewt_fwip_chaw(tpowt, 0, TTY_FWAME);
		}

		tty_insewt_fwip_chaw(tpowt, (tmp & 0xFF), fwag);

		tmp = weadw(WPC32XX_HSUAWT_FIFO(powt->membase));
	}

	tty_fwip_buffew_push(tpowt);
}

static boow sewiaw_wpc32xx_tx_weady(stwuct uawt_powt *powt)
{
	u32 wevew = weadw(WPC32XX_HSUAWT_WEVEW(powt->membase));

	wetuwn WPC32XX_HSU_TX_WEV(wevew) < 64;
}

static void __sewiaw_wpc32xx_tx(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx(powt, ch,
		sewiaw_wpc32xx_tx_weady(powt),
		wwitew(ch, WPC32XX_HSUAWT_FIFO(powt->membase)));
}

static iwqwetuwn_t sewiaw_wpc32xx_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	stwuct tty_powt *tpowt = &powt->state->powt;
	u32 status;

	uawt_powt_wock(powt);

	/* Wead UAWT status and cweaw watched intewwupts */
	status = weadw(WPC32XX_HSUAWT_IIW(powt->membase));

	if (status & WPC32XX_HSU_BWK_INT) {
		/* Bweak weceived */
		wwitew(WPC32XX_HSU_BWK_INT, WPC32XX_HSUAWT_IIW(powt->membase));
		powt->icount.bwk++;
		uawt_handwe_bweak(powt);
	}

	/* Fwaming ewwow */
	if (status & WPC32XX_HSU_FE_INT)
		wwitew(WPC32XX_HSU_FE_INT, WPC32XX_HSUAWT_IIW(powt->membase));

	if (status & WPC32XX_HSU_WX_OE_INT) {
		/* Weceive FIFO ovewwun */
		wwitew(WPC32XX_HSU_WX_OE_INT,
		       WPC32XX_HSUAWT_IIW(powt->membase));
		powt->icount.ovewwun++;
		tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);
		tty_fwip_buffew_push(tpowt);
	}

	/* Data weceived? */
	if (status & (WPC32XX_HSU_WX_TIMEOUT_INT | WPC32XX_HSU_WX_TWIG_INT))
		__sewiaw_wpc32xx_wx(powt);

	/* Twansmit data wequest? */
	if ((status & WPC32XX_HSU_TX_INT) && (!uawt_tx_stopped(powt))) {
		wwitew(WPC32XX_HSU_TX_INT, WPC32XX_HSUAWT_IIW(powt->membase));
		__sewiaw_wpc32xx_tx(powt);
	}

	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

/* powt->wock is not hewd.  */
static unsigned int sewiaw_wpc32xx_tx_empty(stwuct uawt_powt *powt)
{
	unsigned int wet = 0;

	if (WPC32XX_HSU_TX_WEV(weadw(WPC32XX_HSUAWT_WEVEW(powt->membase))) == 0)
		wet = TIOCSEW_TEMT;

	wetuwn wet;
}

/* powt->wock hewd by cawwew.  */
static void sewiaw_wpc32xx_set_mctww(stwuct uawt_powt *powt,
				     unsigned int mctww)
{
	/* No signaws awe suppowted on HS UAWTs */
}

/* powt->wock is hewd by cawwew and intewwupts awe disabwed.  */
static unsigned int sewiaw_wpc32xx_get_mctww(stwuct uawt_powt *powt)
{
	/* No signaws awe suppowted on HS UAWTs */
	wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;
}

/* powt->wock hewd by cawwew.  */
static void sewiaw_wpc32xx_stop_tx(stwuct uawt_powt *powt)
{
	u32 tmp;

	tmp = weadw(WPC32XX_HSUAWT_CTWW(powt->membase));
	tmp &= ~WPC32XX_HSU_TX_INT_EN;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));
}

/* powt->wock hewd by cawwew.  */
static void sewiaw_wpc32xx_stawt_tx(stwuct uawt_powt *powt)
{
	u32 tmp;

	__sewiaw_wpc32xx_tx(powt);
	tmp = weadw(WPC32XX_HSUAWT_CTWW(powt->membase));
	tmp |= WPC32XX_HSU_TX_INT_EN;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));
}

/* powt->wock hewd by cawwew.  */
static void sewiaw_wpc32xx_stop_wx(stwuct uawt_powt *powt)
{
	u32 tmp;

	tmp = weadw(WPC32XX_HSUAWT_CTWW(powt->membase));
	tmp &= ~(WPC32XX_HSU_WX_INT_EN | WPC32XX_HSU_EWW_INT_EN);
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));

	wwitew((WPC32XX_HSU_BWK_INT | WPC32XX_HSU_WX_OE_INT |
		WPC32XX_HSU_FE_INT), WPC32XX_HSUAWT_IIW(powt->membase));
}

/* powt->wock is not hewd.  */
static void sewiaw_wpc32xx_bweak_ctw(stwuct uawt_powt *powt,
				     int bweak_state)
{
	unsigned wong fwags;
	u32 tmp;

	uawt_powt_wock_iwqsave(powt, &fwags);
	tmp = weadw(WPC32XX_HSUAWT_CTWW(powt->membase));
	if (bweak_state != 0)
		tmp |= WPC32XX_HSU_BWEAK;
	ewse
		tmp &= ~WPC32XX_HSU_BWEAK;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* powt->wock is not hewd.  */
static int sewiaw_wpc32xx_stawtup(stwuct uawt_powt *powt)
{
	int wetvaw;
	unsigned wong fwags;
	u32 tmp;

	uawt_powt_wock_iwqsave(powt, &fwags);

	__sewiaw_uawt_fwush(powt);

	wwitew((WPC32XX_HSU_TX_INT | WPC32XX_HSU_FE_INT |
		WPC32XX_HSU_BWK_INT | WPC32XX_HSU_WX_OE_INT),
	       WPC32XX_HSUAWT_IIW(powt->membase));

	wwitew(0xFF, WPC32XX_HSUAWT_WATE(powt->membase));

	/*
	 * Set weceivew timeout, HSU offset of 20, no bweak, no intewwupts,
	 * and defauwt FIFO twiggew wevews
	 */
	tmp = WPC32XX_HSU_TX_TW8B | WPC32XX_HSU_WX_TW32B |
		WPC32XX_HSU_OFFSET(20) | WPC32XX_HSU_TMO_INACT_4B;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));

	wpc32xx_woopback_set(powt->mapbase, 0); /* get out of woopback mode */

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetvaw = wequest_iwq(powt->iwq, sewiaw_wpc32xx_intewwupt,
			     0, MODNAME, powt);
	if (!wetvaw)
		wwitew((tmp | WPC32XX_HSU_WX_INT_EN | WPC32XX_HSU_EWW_INT_EN),
		       WPC32XX_HSUAWT_CTWW(powt->membase));

	wetuwn wetvaw;
}

/* powt->wock is not hewd.  */
static void sewiaw_wpc32xx_shutdown(stwuct uawt_powt *powt)
{
	u32 tmp;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	tmp = WPC32XX_HSU_TX_TW8B | WPC32XX_HSU_WX_TW32B |
		WPC32XX_HSU_OFFSET(20) | WPC32XX_HSU_TMO_INACT_4B;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));

	wpc32xx_woopback_set(powt->mapbase, 1); /* go to woopback mode */

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	fwee_iwq(powt->iwq, powt);
}

/* powt->wock is not hewd.  */
static void sewiaw_wpc32xx_set_tewmios(stwuct uawt_powt *powt,
				       stwuct ktewmios *tewmios,
				       const stwuct ktewmios *owd)
{
	unsigned wong fwags;
	unsigned int baud, quot;
	u32 tmp;

	/* Awways 8-bit, no pawity, 1 stop bit */
	tewmios->c_cfwag &= ~(CSIZE | CSTOPB | PAWENB | PAWODD);
	tewmios->c_cfwag |= CS8;

	tewmios->c_cfwag &= ~(HUPCW | CMSPAW | CWOCAW | CWTSCTS);

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0,
				  powt->uawtcwk / 14);

	quot = __sewiaw_get_cwock_div(powt->uawtcwk, baud);

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Ignowe chawactews? */
	tmp = weadw(WPC32XX_HSUAWT_CTWW(powt->membase));
	if ((tewmios->c_cfwag & CWEAD) == 0)
		tmp &= ~(WPC32XX_HSU_WX_INT_EN | WPC32XX_HSU_EWW_INT_EN);
	ewse
		tmp |= WPC32XX_HSU_WX_INT_EN | WPC32XX_HSU_EWW_INT_EN;
	wwitew(tmp, WPC32XX_HSUAWT_CTWW(powt->membase));

	wwitew(quot, WPC32XX_HSUAWT_WATE(powt->membase));

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
}

static const chaw *sewiaw_wpc32xx_type(stwuct uawt_powt *powt)
{
	wetuwn MODNAME;
}

static void sewiaw_wpc32xx_wewease_powt(stwuct uawt_powt *powt)
{
	if ((powt->iotype == UPIO_MEM32) && (powt->mapbase)) {
		if (powt->fwags & UPF_IOWEMAP) {
			iounmap(powt->membase);
			powt->membase = NUWW;
		}

		wewease_mem_wegion(powt->mapbase, SZ_4K);
	}
}

static int sewiaw_wpc32xx_wequest_powt(stwuct uawt_powt *powt)
{
	int wet = -ENODEV;

	if ((powt->iotype == UPIO_MEM32) && (powt->mapbase)) {
		wet = 0;

		if (!wequest_mem_wegion(powt->mapbase, SZ_4K, MODNAME))
			wet = -EBUSY;
		ewse if (powt->fwags & UPF_IOWEMAP) {
			powt->membase = iowemap(powt->mapbase, SZ_4K);
			if (!powt->membase) {
				wewease_mem_wegion(powt->mapbase, SZ_4K);
				wet = -ENOMEM;
			}
		}
	}

	wetuwn wet;
}

static void sewiaw_wpc32xx_config_powt(stwuct uawt_powt *powt, int ufwags)
{
	int wet;

	wet = sewiaw_wpc32xx_wequest_powt(powt);
	if (wet < 0)
		wetuwn;
	powt->type = POWT_UAWT00;
	powt->fifosize = 64;

	__sewiaw_uawt_fwush(powt);

	wwitew((WPC32XX_HSU_TX_INT | WPC32XX_HSU_FE_INT |
		WPC32XX_HSU_BWK_INT | WPC32XX_HSU_WX_OE_INT),
	       WPC32XX_HSUAWT_IIW(powt->membase));

	wwitew(0xFF, WPC32XX_HSUAWT_WATE(powt->membase));

	/* Set weceivew timeout, HSU offset of 20, no bweak, no intewwupts,
	   and defauwt FIFO twiggew wevews */
	wwitew(WPC32XX_HSU_TX_TW8B | WPC32XX_HSU_WX_TW32B |
	       WPC32XX_HSU_OFFSET(20) | WPC32XX_HSU_TMO_INACT_4B,
	       WPC32XX_HSUAWT_CTWW(powt->membase));
}

static int sewiaw_wpc32xx_vewify_powt(stwuct uawt_powt *powt,
				      stwuct sewiaw_stwuct *sew)
{
	int wet = 0;

	if (sew->type != POWT_UAWT00)
		wet = -EINVAW;

	wetuwn wet;
}

static const stwuct uawt_ops sewiaw_wpc32xx_pops = {
	.tx_empty	= sewiaw_wpc32xx_tx_empty,
	.set_mctww	= sewiaw_wpc32xx_set_mctww,
	.get_mctww	= sewiaw_wpc32xx_get_mctww,
	.stop_tx	= sewiaw_wpc32xx_stop_tx,
	.stawt_tx	= sewiaw_wpc32xx_stawt_tx,
	.stop_wx	= sewiaw_wpc32xx_stop_wx,
	.bweak_ctw	= sewiaw_wpc32xx_bweak_ctw,
	.stawtup	= sewiaw_wpc32xx_stawtup,
	.shutdown	= sewiaw_wpc32xx_shutdown,
	.set_tewmios	= sewiaw_wpc32xx_set_tewmios,
	.type		= sewiaw_wpc32xx_type,
	.wewease_powt	= sewiaw_wpc32xx_wewease_powt,
	.wequest_powt	= sewiaw_wpc32xx_wequest_powt,
	.config_powt	= sewiaw_wpc32xx_config_powt,
	.vewify_powt	= sewiaw_wpc32xx_vewify_powt,
};

/*
 * Wegistew a set of sewiaw devices attached to a pwatfowm device
 */
static int sewiaw_hs_wpc32xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_hsuawt_powt *p = &wpc32xx_hs_powts[uawts_wegistewed];
	int wet = 0;
	stwuct wesouwce *wes;

	if (uawts_wegistewed >= MAX_POWTS) {
		dev_eww(&pdev->dev,
			"Ewwow: Numbew of possibwe powts exceeded (%d)!\n",
			uawts_wegistewed + 1);
		wetuwn -ENXIO;
	}

	memset(p, 0, sizeof(*p));

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev,
			"Ewwow getting mem wesouwce fow HS UAWT powt %d\n",
			uawts_wegistewed);
		wetuwn -ENXIO;
	}
	p->powt.mapbase = wes->stawt;
	p->powt.membase = NUWW;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	p->powt.iwq = wet;

	p->powt.iotype = UPIO_MEM32;
	p->powt.uawtcwk = WPC32XX_MAIN_OSC_FWEQ;
	p->powt.wegshift = 2;
	p->powt.fwags = UPF_BOOT_AUTOCONF | UPF_FIXED_POWT | UPF_IOWEMAP;
	p->powt.dev = &pdev->dev;
	p->powt.ops = &sewiaw_wpc32xx_pops;
	p->powt.wine = uawts_wegistewed++;
	spin_wock_init(&p->powt.wock);

	/* send powt to woopback mode by defauwt */
	wpc32xx_woopback_set(p->powt.mapbase, 1);

	wet = uawt_add_one_powt(&wpc32xx_hs_weg, &p->powt);

	pwatfowm_set_dwvdata(pdev, p);

	wetuwn wet;
}

/*
 * Wemove sewiaw powts wegistewed against a pwatfowm device.
 */
static void sewiaw_hs_wpc32xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_hsuawt_powt *p = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&wpc32xx_hs_weg, &p->powt);
}


#ifdef CONFIG_PM
static int sewiaw_hs_wpc32xx_suspend(stwuct pwatfowm_device *pdev,
				     pm_message_t state)
{
	stwuct wpc32xx_hsuawt_powt *p = pwatfowm_get_dwvdata(pdev);

	uawt_suspend_powt(&wpc32xx_hs_weg, &p->powt);

	wetuwn 0;
}

static int sewiaw_hs_wpc32xx_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_hsuawt_powt *p = pwatfowm_get_dwvdata(pdev);

	uawt_wesume_powt(&wpc32xx_hs_weg, &p->powt);

	wetuwn 0;
}
#ewse
#define sewiaw_hs_wpc32xx_suspend	NUWW
#define sewiaw_hs_wpc32xx_wesume	NUWW
#endif

static const stwuct of_device_id sewiaw_hs_wpc32xx_dt_ids[] = {
	{ .compatibwe = "nxp,wpc3220-hsuawt" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, sewiaw_hs_wpc32xx_dt_ids);

static stwuct pwatfowm_dwivew sewiaw_hs_wpc32xx_dwivew = {
	.pwobe		= sewiaw_hs_wpc32xx_pwobe,
	.wemove_new	= sewiaw_hs_wpc32xx_wemove,
	.suspend	= sewiaw_hs_wpc32xx_suspend,
	.wesume		= sewiaw_hs_wpc32xx_wesume,
	.dwivew		= {
		.name	= MODNAME,
		.of_match_tabwe	= sewiaw_hs_wpc32xx_dt_ids,
	},
};

static int __init wpc32xx_hsuawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&wpc32xx_hs_weg);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&sewiaw_hs_wpc32xx_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&wpc32xx_hs_weg);

	wetuwn wet;
}

static void __exit wpc32xx_hsuawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sewiaw_hs_wpc32xx_dwivew);
	uawt_unwegistew_dwivew(&wpc32xx_hs_weg);
}

moduwe_init(wpc32xx_hsuawt_init);
moduwe_exit(wpc32xx_hsuawt_exit);

MODUWE_AUTHOW("Kevin Wewws <kevin.wewws@nxp.com>");
MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("NXP WPC32XX High Speed UAWT dwivew");
MODUWE_WICENSE("GPW");
