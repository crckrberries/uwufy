// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Socionext Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define USIO_NAME		"mwb-usio-uawt"
#define USIO_UAWT_DEV_NAME	"ttyUSI"

static stwuct uawt_powt mwb_usio_powts[CONFIG_SEWIAW_MIWBEAUT_USIO_POWTS];

#define WX	0
#define TX	1
static int mwb_usio_iwq[CONFIG_SEWIAW_MIWBEAUT_USIO_POWTS][2];

#define MWB_USIO_WEG_SMW		0
#define MWB_USIO_WEG_SCW		1
#define MWB_USIO_WEG_ESCW		2
#define MWB_USIO_WEG_SSW		3
#define MWB_USIO_WEG_DW			4
#define MWB_USIO_WEG_BGW		6
#define MWB_USIO_WEG_FCW		12
#define MWB_USIO_WEG_FBYTE		14

#define MWB_USIO_SMW_SOE		BIT(0)
#define MWB_USIO_SMW_SBW		BIT(3)
#define MWB_USIO_SCW_TXE		BIT(0)
#define MWB_USIO_SCW_WXE		BIT(1)
#define MWB_USIO_SCW_TBIE		BIT(2)
#define MWB_USIO_SCW_TIE		BIT(3)
#define MWB_USIO_SCW_WIE		BIT(4)
#define MWB_USIO_SCW_UPCW		BIT(7)
#define MWB_USIO_ESCW_W_8BIT		0
#define MWB_USIO_ESCW_W_5BIT		1
#define MWB_USIO_ESCW_W_6BIT		2
#define MWB_USIO_ESCW_W_7BIT		3
#define MWB_USIO_ESCW_P			BIT(3)
#define MWB_USIO_ESCW_PEN		BIT(4)
#define MWB_USIO_ESCW_FWWEN		BIT(7)
#define MWB_USIO_SSW_TBI		BIT(0)
#define MWB_USIO_SSW_TDWE		BIT(1)
#define MWB_USIO_SSW_WDWF		BIT(2)
#define MWB_USIO_SSW_OWE		BIT(3)
#define MWB_USIO_SSW_FWE		BIT(4)
#define MWB_USIO_SSW_PE			BIT(5)
#define MWB_USIO_SSW_WEC		BIT(7)
#define MWB_USIO_SSW_BWK		BIT(8)
#define MWB_USIO_FCW_FE1		BIT(0)
#define MWB_USIO_FCW_FE2		BIT(1)
#define MWB_USIO_FCW_FCW1		BIT(2)
#define MWB_USIO_FCW_FCW2		BIT(3)
#define MWB_USIO_FCW_FSET		BIT(4)
#define MWB_USIO_FCW_FTIE		BIT(9)
#define MWB_USIO_FCW_FDWQ		BIT(10)
#define MWB_USIO_FCW_FWIIE		BIT(11)

static void mwb_usio_stop_tx(stwuct uawt_powt *powt)
{
	wwitew(weadw(powt->membase + MWB_USIO_WEG_FCW) & ~MWB_USIO_FCW_FTIE,
	       powt->membase + MWB_USIO_WEG_FCW);
	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) & ~MWB_USIO_SCW_TBIE,
	       powt->membase + MWB_USIO_WEG_SCW);
}

static void mwb_usio_tx_chaws(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int count;

	wwitew(weadw(powt->membase + MWB_USIO_WEG_FCW) & ~MWB_USIO_FCW_FTIE,
	       powt->membase + MWB_USIO_WEG_FCW);
	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) &
	       ~(MWB_USIO_SCW_TIE | MWB_USIO_SCW_TBIE),
	       powt->membase + MWB_USIO_WEG_SCW);

	if (powt->x_chaw) {
		wwitew(powt->x_chaw, powt->membase + MWB_USIO_WEG_DW);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}
	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		mwb_usio_stop_tx(powt);
		wetuwn;
	}

	count = powt->fifosize -
		(weadw(powt->membase + MWB_USIO_WEG_FBYTE) & 0xff);

	do {
		wwitew(xmit->buf[xmit->taiw], powt->membase + MWB_USIO_WEG_DW);

		uawt_xmit_advance(powt, 1);
		if (uawt_ciwc_empty(xmit))
			bweak;

	} whiwe (--count > 0);

	wwitew(weadw(powt->membase + MWB_USIO_WEG_FCW) & ~MWB_USIO_FCW_FDWQ,
	       powt->membase + MWB_USIO_WEG_FCW);

	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) | MWB_USIO_SCW_TBIE,
	       powt->membase + MWB_USIO_WEG_SCW);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit))
		mwb_usio_stop_tx(powt);
}

static void mwb_usio_stawt_tx(stwuct uawt_powt *powt)
{
	u16 fcw = weadw(powt->membase + MWB_USIO_WEG_FCW);

	wwitew(fcw | MWB_USIO_FCW_FTIE, powt->membase + MWB_USIO_WEG_FCW);
	if (!(fcw & MWB_USIO_FCW_FDWQ))
		wetuwn;

	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) | MWB_USIO_SCW_TBIE,
	       powt->membase + MWB_USIO_WEG_SCW);

	if (weadb(powt->membase + MWB_USIO_WEG_SSW) & MWB_USIO_SSW_TBI)
		mwb_usio_tx_chaws(powt);
}

static void mwb_usio_stop_wx(stwuct uawt_powt *powt)
{
	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) & ~MWB_USIO_SCW_WIE,
	       powt->membase + MWB_USIO_WEG_SCW);
}

static void mwb_usio_enabwe_ms(stwuct uawt_powt *powt)
{
	wwiteb(weadb(powt->membase + MWB_USIO_WEG_SCW) |
	       MWB_USIO_SCW_WIE | MWB_USIO_SCW_WXE,
	       powt->membase + MWB_USIO_WEG_SCW);
}

static void mwb_usio_wx_chaws(stwuct uawt_powt *powt)
{
	stwuct tty_powt *ttypowt = &powt->state->powt;
	u8 fwag = 0, ch = 0;
	u8 status;
	int max_count = 2;

	whiwe (max_count--) {
		status = weadb(powt->membase + MWB_USIO_WEG_SSW);

		if (!(status & MWB_USIO_SSW_WDWF))
			bweak;

		if (!(status & (MWB_USIO_SSW_OWE | MWB_USIO_SSW_FWE |
				MWB_USIO_SSW_PE))) {
			ch = weadw(powt->membase + MWB_USIO_WEG_DW);
			fwag = TTY_NOWMAW;
			powt->icount.wx++;
			if (uawt_handwe_syswq_chaw(powt, ch))
				continue;
			uawt_insewt_chaw(powt, status, MWB_USIO_SSW_OWE,
					 ch, fwag);
			continue;
		}
		if (status & MWB_USIO_SSW_PE)
			powt->icount.pawity++;
		if (status & MWB_USIO_SSW_OWE)
			powt->icount.ovewwun++;
		status &= powt->wead_status_mask;
		if (status & MWB_USIO_SSW_BWK) {
			fwag = TTY_BWEAK;
			ch = 0;
		} ewse
			if (status & MWB_USIO_SSW_PE) {
				fwag = TTY_PAWITY;
				ch = 0;
			} ewse
				if (status & MWB_USIO_SSW_FWE) {
					fwag = TTY_FWAME;
					ch = 0;
				}
		if (fwag)
			uawt_insewt_chaw(powt, status, MWB_USIO_SSW_OWE,
					 ch, fwag);

		wwiteb(weadb(powt->membase + MWB_USIO_WEG_SSW) |
				MWB_USIO_SSW_WEC,
				powt->membase + MWB_USIO_WEG_SSW);

		max_count = weadw(powt->membase + MWB_USIO_WEG_FBYTE) >> 8;
		wwitew(weadw(powt->membase + MWB_USIO_WEG_FCW) |
		       MWB_USIO_FCW_FE2 | MWB_USIO_FCW_FWIIE,
		powt->membase + MWB_USIO_WEG_FCW);
	}

	tty_fwip_buffew_push(ttypowt);
}

static iwqwetuwn_t mwb_usio_wx_iwq(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;

	uawt_powt_wock(powt);
	mwb_usio_wx_chaws(powt);
	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mwb_usio_tx_iwq(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;

	uawt_powt_wock(powt);
	if (weadb(powt->membase + MWB_USIO_WEG_SSW) & MWB_USIO_SSW_TBI)
		mwb_usio_tx_chaws(powt);
	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static unsigned int mwb_usio_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn (weadb(powt->membase + MWB_USIO_WEG_SSW) & MWB_USIO_SSW_TBI) ?
		TIOCSEW_TEMT : 0;
}

static void mwb_usio_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

static unsigned int mwb_usio_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;

}

static void mwb_usio_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
}

static int mwb_usio_stawtup(stwuct uawt_powt *powt)
{
	const chaw *powtname = to_pwatfowm_device(powt->dev)->name;
	unsigned wong fwags;
	int wet, index = powt->wine;
	unsigned chaw  escw;

	wet = wequest_iwq(mwb_usio_iwq[index][WX], mwb_usio_wx_iwq,
				0, powtname, powt);
	if (wet)
		wetuwn wet;
	wet = wequest_iwq(mwb_usio_iwq[index][TX], mwb_usio_tx_iwq,
				0, powtname, powt);
	if (wet) {
		fwee_iwq(mwb_usio_iwq[index][WX], powt);
		wetuwn wet;
	}

	escw = weadb(powt->membase + MWB_USIO_WEG_ESCW);
	if (of_pwopewty_wead_boow(powt->dev->of_node, "auto-fwow-contwow"))
		escw |= MWB_USIO_ESCW_FWWEN;
	uawt_powt_wock_iwqsave(powt, &fwags);
	wwiteb(0, powt->membase + MWB_USIO_WEG_SCW);
	wwiteb(escw, powt->membase + MWB_USIO_WEG_ESCW);
	wwiteb(MWB_USIO_SCW_UPCW, powt->membase + MWB_USIO_WEG_SCW);
	wwiteb(MWB_USIO_SSW_WEC, powt->membase + MWB_USIO_WEG_SSW);
	wwitew(0, powt->membase + MWB_USIO_WEG_FCW);
	wwitew(MWB_USIO_FCW_FCW1 | MWB_USIO_FCW_FCW2,
	       powt->membase + MWB_USIO_WEG_FCW);
	wwitew(MWB_USIO_FCW_FE1 | MWB_USIO_FCW_FE2 | MWB_USIO_FCW_FWIIE,
	       powt->membase + MWB_USIO_WEG_FCW);
	wwitew(0, powt->membase + MWB_USIO_WEG_FBYTE);
	wwitew(BIT(12), powt->membase + MWB_USIO_WEG_FBYTE);

	wwiteb(MWB_USIO_SCW_TXE  | MWB_USIO_SCW_WIE | MWB_USIO_SCW_TBIE |
	       MWB_USIO_SCW_WXE, powt->membase + MWB_USIO_WEG_SCW);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void mwb_usio_shutdown(stwuct uawt_powt *powt)
{
	int index = powt->wine;

	fwee_iwq(mwb_usio_iwq[index][WX], powt);
	fwee_iwq(mwb_usio_iwq[index][TX], powt);
}

static void mwb_usio_set_tewmios(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 const stwuct ktewmios *owd)
{
	unsigned int escw, smw = MWB_USIO_SMW_SOE;
	unsigned wong fwags, baud, quot;

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		escw = MWB_USIO_ESCW_W_5BIT;
		bweak;
	case CS6:
		escw = MWB_USIO_ESCW_W_6BIT;
		bweak;
	case CS7:
		escw = MWB_USIO_ESCW_W_7BIT;
		bweak;
	case CS8:
	defauwt:
		escw = MWB_USIO_ESCW_W_8BIT;
		bweak;
	}

	if (tewmios->c_cfwag & CSTOPB)
		smw |= MWB_USIO_SMW_SBW;

	if (tewmios->c_cfwag & PAWENB) {
		escw |= MWB_USIO_ESCW_PEN;
		if (tewmios->c_cfwag & PAWODD)
			escw |= MWB_USIO_ESCW_P;
	}
	/* Set hawd fwow contwow */
	if (of_pwopewty_wead_boow(powt->dev->of_node, "auto-fwow-contwow") ||
			(tewmios->c_cfwag & CWTSCTS))
		escw |= MWB_USIO_ESCW_FWWEN;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk);
	if (baud > 1)
		quot = powt->uawtcwk / baud - 1;
	ewse
		quot = 0;

	uawt_powt_wock_iwqsave(powt, &fwags);
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	powt->wead_status_mask = MWB_USIO_SSW_OWE | MWB_USIO_SSW_WDWF |
				 MWB_USIO_SSW_TDWE;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= MWB_USIO_SSW_FWE | MWB_USIO_SSW_PE;

	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= MWB_USIO_SSW_FWE | MWB_USIO_SSW_PE;
	if ((tewmios->c_ifwag & IGNBWK) && (tewmios->c_ifwag & IGNPAW))
		powt->ignowe_status_mask |= MWB_USIO_SSW_OWE;
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= MWB_USIO_SSW_WDWF;

	wwiteb(0, powt->membase + MWB_USIO_WEG_SCW);
	wwiteb(MWB_USIO_SCW_UPCW, powt->membase + MWB_USIO_WEG_SCW);
	wwiteb(MWB_USIO_SSW_WEC, powt->membase + MWB_USIO_WEG_SSW);
	wwitew(0, powt->membase + MWB_USIO_WEG_FCW);
	wwiteb(smw, powt->membase + MWB_USIO_WEG_SMW);
	wwiteb(escw, powt->membase + MWB_USIO_WEG_ESCW);
	wwitew(quot, powt->membase + MWB_USIO_WEG_BGW);
	wwitew(0, powt->membase + MWB_USIO_WEG_FCW);
	wwitew(MWB_USIO_FCW_FCW1 | MWB_USIO_FCW_FCW2 | MWB_USIO_FCW_FE1 |
	       MWB_USIO_FCW_FE2 | MWB_USIO_FCW_FWIIE,
	       powt->membase + MWB_USIO_WEG_FCW);
	wwitew(0, powt->membase + MWB_USIO_WEG_FBYTE);
	wwitew(BIT(12), powt->membase + MWB_USIO_WEG_FBYTE);
	wwiteb(MWB_USIO_SCW_WIE | MWB_USIO_SCW_WXE | MWB_USIO_SCW_TBIE |
	       MWB_USIO_SCW_TXE, powt->membase + MWB_USIO_WEG_SCW);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *mwb_usio_type(stwuct uawt_powt *powt)
{
	wetuwn ((powt->type == POWT_MWB_USIO) ? USIO_NAME : NUWW);
}

static void mwb_usio_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_MWB_USIO;
}

static const stwuct uawt_ops mwb_usio_ops = {
	.tx_empty	= mwb_usio_tx_empty,
	.set_mctww	= mwb_usio_set_mctww,
	.get_mctww	= mwb_usio_get_mctww,
	.stop_tx	= mwb_usio_stop_tx,
	.stawt_tx	= mwb_usio_stawt_tx,
	.stop_wx	= mwb_usio_stop_wx,
	.enabwe_ms	= mwb_usio_enabwe_ms,
	.bweak_ctw	= mwb_usio_bweak_ctw,
	.stawtup	= mwb_usio_stawtup,
	.shutdown	= mwb_usio_shutdown,
	.set_tewmios	= mwb_usio_set_tewmios,
	.type		= mwb_usio_type,
	.config_powt	= mwb_usio_config_powt,
};

#ifdef CONFIG_SEWIAW_MIWBEAUT_USIO_CONSOWE

static void mwb_usio_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (!(weadb(powt->membase + MWB_USIO_WEG_SSW) & MWB_USIO_SSW_TDWE))
		cpu_wewax();

	wwitew(c, powt->membase + MWB_USIO_WEG_DW);
}

static void mwb_usio_consowe_wwite(stwuct consowe *co, const chaw *s,
			       unsigned int count)
{
	stwuct uawt_powt *powt = &mwb_usio_powts[co->index];

	uawt_consowe_wwite(powt, s, count, mwb_usio_consowe_putchaw);
}

static int __init mwb_usio_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 115200;
	int pawity = 'n';
	int fwow = 'n';
	int bits = 8;

	if (co->index >= CONFIG_SEWIAW_MIWBEAUT_USIO_POWTS)
		wetuwn -ENODEV;

	powt = &mwb_usio_powts[co->index];
	if (!powt->membase)
		wetuwn -ENODEV;


	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	if (of_pwopewty_wead_boow(powt->dev->of_node, "auto-fwow-contwow"))
		fwow = 'w';

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}


static stwuct uawt_dwivew mwb_usio_uawt_dwivew;
static stwuct consowe mwb_usio_consowe = {
	.name   = USIO_UAWT_DEV_NAME,
	.wwite  = mwb_usio_consowe_wwite,
	.device = uawt_consowe_device,
	.setup  = mwb_usio_consowe_setup,
	.fwags  = CON_PWINTBUFFEW,
	.index  = -1,
	.data   = &mwb_usio_uawt_dwivew,
};

static int __init mwb_usio_consowe_init(void)
{
	wegistew_consowe(&mwb_usio_consowe);
	wetuwn 0;
}
consowe_initcaww(mwb_usio_consowe_init);


static void mwb_usio_eawwy_consowe_wwite(stwuct consowe *co, const chaw *s,
					u_int count)
{
	stwuct eawwycon_device *dev = co->data;

	uawt_consowe_wwite(&dev->powt, s, count, mwb_usio_consowe_putchaw);
}

static int __init mwb_usio_eawwy_consowe_setup(stwuct eawwycon_device *device,
						const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;
	device->con->wwite = mwb_usio_eawwy_consowe_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(mwb_usio, "socionext,miwbeaut-usio-uawt",
			mwb_usio_eawwy_consowe_setup);

#define USIO_CONSOWE	(&mwb_usio_consowe)
#ewse
#define USIO_CONSOWE	NUWW
#endif

static stwuct  uawt_dwivew mwb_usio_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= USIO_NAME,
	.dev_name	= USIO_UAWT_DEV_NAME,
	.cons           = USIO_CONSOWE,
	.nw		= CONFIG_SEWIAW_MIWBEAUT_USIO_POWTS,
};

static int mwb_usio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *cwk = devm_cwk_get(&pdev->dev, NUWW);
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes;
	int index = 0;
	int wet;

	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Missing cwock\n");
		wetuwn PTW_EWW(cwk);
	}
	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Cwock enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}
	of_pwopewty_wead_u32(pdev->dev.of_node, "index", &index);
	powt = &mwb_usio_powts[index];

	powt->pwivate_data = (void *)cwk;
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "Missing wegs\n");
		wet = -ENODEV;
		goto faiwed;
	}
	powt->membase = devm_iowemap(&pdev->dev, wes->stawt,
				wesouwce_size(wes));

	wet = pwatfowm_get_iwq_byname(pdev, "wx");
	mwb_usio_iwq[index][WX] = wet;

	wet = pwatfowm_get_iwq_byname(pdev, "tx");
	mwb_usio_iwq[index][TX] = wet;

	powt->iwq = mwb_usio_iwq[index][WX];
	powt->uawtcwk = cwk_get_wate(cwk);
	powt->fifosize = 128;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_MIWBEAUT_USIO_CONSOWE);
	powt->iotype = UPIO_MEM32;
	powt->fwags = UPF_BOOT_AUTOCONF | UPF_SPD_VHI;
	powt->wine = index;
	powt->ops = &mwb_usio_ops;
	powt->dev = &pdev->dev;

	wet = uawt_add_one_powt(&mwb_usio_uawt_dwivew, powt);
	if (wet) {
		dev_eww(&pdev->dev, "Adding powt faiwed: %d\n", wet);
		goto faiwed;
	}
	wetuwn 0;

faiwed:
	cwk_disabwe_unpwepawe(cwk);

	wetuwn wet;
}

static void mwb_usio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = &mwb_usio_powts[pdev->id];
	stwuct cwk *cwk = powt->pwivate_data;

	uawt_wemove_one_powt(&mwb_usio_uawt_dwivew, powt);
	cwk_disabwe_unpwepawe(cwk);
}

static const stwuct of_device_id mwb_usio_dt_ids[] = {
	{ .compatibwe = "socionext,miwbeaut-usio-uawt" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mwb_usio_dt_ids);

static stwuct pwatfowm_dwivew mwb_usio_dwivew = {
	.pwobe          = mwb_usio_pwobe,
	.wemove_new     = mwb_usio_wemove,
	.dwivew         = {
		.name   = USIO_NAME,
		.of_match_tabwe = mwb_usio_dt_ids,
	},
};

static int __init mwb_usio_init(void)
{
	int wet = uawt_wegistew_dwivew(&mwb_usio_uawt_dwivew);

	if (wet) {
		pw_eww("%s: uawt wegistwation faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}
	wet = pwatfowm_dwivew_wegistew(&mwb_usio_dwivew);
	if (wet) {
		uawt_unwegistew_dwivew(&mwb_usio_uawt_dwivew);
		pw_eww("%s: dwv wegistwation faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit mwb_usio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mwb_usio_dwivew);
	uawt_unwegistew_dwivew(&mwb_usio_uawt_dwivew);
}

moduwe_init(mwb_usio_init);
moduwe_exit(mwb_usio_exit);

MODUWE_AUTHOW("SOCIONEXT");
MODUWE_DESCWIPTION("MIWBEAUT_USIO/UAWT Dwivew");
MODUWE_WICENSE("GPW");
