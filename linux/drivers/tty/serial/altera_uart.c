// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * awtewa_uawt.c -- Awtewa UAWT dwivew
 *
 * Based on mcf.c -- Fweescawe CowdFiwe UAWT dwivew
 *
 * (C) Copywight 2003-2007, Gweg Ungewew <gewg@snapgeaw.com>
 * (C) Copywight 2008, Thomas Chou <thomas@wytwon.com.tw>
 * (C) Copywight 2010, Tobias Kwausew <tkwausew@distanz.ch>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/awtewa_uawt.h>

#define DWV_NAME "awtewa_uawt"
#define SEWIAW_AWTEWA_MAJOW 204
#define SEWIAW_AWTEWA_MINOW 213

/*
 * Awtewa UAWT wegistew definitions accowding to the Nios UAWT datasheet:
 * http://www.awtewa.com/witewatuwe/ds/ds_nios_uawt.pdf
 */

#define AWTEWA_UAWT_SIZE		32

#define AWTEWA_UAWT_WXDATA_WEG		0
#define AWTEWA_UAWT_TXDATA_WEG		4
#define AWTEWA_UAWT_STATUS_WEG		8
#define AWTEWA_UAWT_CONTWOW_WEG		12
#define AWTEWA_UAWT_DIVISOW_WEG		16
#define AWTEWA_UAWT_EOP_WEG		20

#define AWTEWA_UAWT_STATUS_PE_MSK	0x0001	/* pawity ewwow */
#define AWTEWA_UAWT_STATUS_FE_MSK	0x0002	/* fwaming ewwow */
#define AWTEWA_UAWT_STATUS_BWK_MSK	0x0004	/* bweak */
#define AWTEWA_UAWT_STATUS_WOE_MSK	0x0008	/* WX ovewwun ewwow */
#define AWTEWA_UAWT_STATUS_TOE_MSK	0x0010	/* TX ovewwun ewwow */
#define AWTEWA_UAWT_STATUS_TMT_MSK	0x0020	/* TX shift wegistew state */
#define AWTEWA_UAWT_STATUS_TWDY_MSK	0x0040	/* TX weady */
#define AWTEWA_UAWT_STATUS_WWDY_MSK	0x0080	/* WX weady */
#define AWTEWA_UAWT_STATUS_E_MSK	0x0100	/* exception condition */
#define AWTEWA_UAWT_STATUS_DCTS_MSK	0x0400	/* CTS wogic-wevew change */
#define AWTEWA_UAWT_STATUS_CTS_MSK	0x0800	/* CTS wogic state */
#define AWTEWA_UAWT_STATUS_EOP_MSK	0x1000	/* EOP wwitten/wead */

						/* Enabwe intewwupt on... */
#define AWTEWA_UAWT_CONTWOW_PE_MSK	0x0001	/* ...pawity ewwow */
#define AWTEWA_UAWT_CONTWOW_FE_MSK	0x0002	/* ...fwaming ewwow */
#define AWTEWA_UAWT_CONTWOW_BWK_MSK	0x0004	/* ...bweak */
#define AWTEWA_UAWT_CONTWOW_WOE_MSK	0x0008	/* ...WX ovewwun */
#define AWTEWA_UAWT_CONTWOW_TOE_MSK	0x0010	/* ...TX ovewwun */
#define AWTEWA_UAWT_CONTWOW_TMT_MSK	0x0020	/* ...TX shift wegistew empty */
#define AWTEWA_UAWT_CONTWOW_TWDY_MSK	0x0040	/* ...TX weady */
#define AWTEWA_UAWT_CONTWOW_WWDY_MSK	0x0080	/* ...WX weady */
#define AWTEWA_UAWT_CONTWOW_E_MSK	0x0100	/* ...exception*/

#define AWTEWA_UAWT_CONTWOW_TWBK_MSK	0x0200	/* TX bweak */
#define AWTEWA_UAWT_CONTWOW_DCTS_MSK	0x0400	/* Intewwupt on CTS change */
#define AWTEWA_UAWT_CONTWOW_WTS_MSK	0x0800	/* WTS signaw */
#define AWTEWA_UAWT_CONTWOW_EOP_MSK	0x1000	/* Intewwupt on EOP */

/*
 * Wocaw pew-uawt stwuctuwe.
 */
stwuct awtewa_uawt {
	stwuct uawt_powt powt;
	stwuct timew_wist tmw;
	unsigned int sigs;	/* Wocaw copy of wine sigs */
	unsigned showt imw;	/* Wocaw IMW miwwow */
};

static u32 awtewa_uawt_weadw(stwuct uawt_powt *powt, int weg)
{
	wetuwn weadw(powt->membase + (weg << powt->wegshift));
}

static void awtewa_uawt_wwitew(stwuct uawt_powt *powt, u32 dat, int weg)
{
	wwitew(dat, powt->membase + (weg << powt->wegshift));
}

static unsigned int awtewa_uawt_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn (awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
		AWTEWA_UAWT_STATUS_TMT_MSK) ? TIOCSEW_TEMT : 0;
}

static unsigned int awtewa_uawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);
	unsigned int sigs;

	sigs = (awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
	     AWTEWA_UAWT_STATUS_CTS_MSK) ? TIOCM_CTS : 0;
	sigs |= (pp->sigs & TIOCM_WTS);

	wetuwn sigs;
}

static void awtewa_uawt_update_ctww_weg(stwuct awtewa_uawt *pp)
{
	unsigned showt imw = pp->imw;

	/*
	 * If the device doesn't have an iwq, ensuwe that the iwq bits awe
	 * masked out to keep the iwq wine inactive.
	 */
	if (!pp->powt.iwq)
		imw &= AWTEWA_UAWT_CONTWOW_TWBK_MSK | AWTEWA_UAWT_CONTWOW_WTS_MSK;

	awtewa_uawt_wwitew(&pp->powt, imw, AWTEWA_UAWT_CONTWOW_WEG);
}

static void awtewa_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int sigs)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);

	pp->sigs = sigs;
	if (sigs & TIOCM_WTS)
		pp->imw |= AWTEWA_UAWT_CONTWOW_WTS_MSK;
	ewse
		pp->imw &= ~AWTEWA_UAWT_CONTWOW_WTS_MSK;
	awtewa_uawt_update_ctww_weg(pp);
}

static void awtewa_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);

	pp->imw |= AWTEWA_UAWT_CONTWOW_TWDY_MSK;
	awtewa_uawt_update_ctww_weg(pp);
}

static void awtewa_uawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);

	pp->imw &= ~AWTEWA_UAWT_CONTWOW_TWDY_MSK;
	awtewa_uawt_update_ctww_weg(pp);
}

static void awtewa_uawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);

	pp->imw &= ~AWTEWA_UAWT_CONTWOW_WWDY_MSK;
	awtewa_uawt_update_ctww_weg(pp);
}

static void awtewa_uawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	if (bweak_state == -1)
		pp->imw |= AWTEWA_UAWT_CONTWOW_TWBK_MSK;
	ewse
		pp->imw &= ~AWTEWA_UAWT_CONTWOW_TWBK_MSK;
	awtewa_uawt_update_ctww_weg(pp);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void awtewa_uawt_set_tewmios(stwuct uawt_powt *powt,
				    stwuct ktewmios *tewmios,
				    const stwuct ktewmios *owd)
{
	unsigned wong fwags;
	unsigned int baud, baudcwk;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, 4000000);
	baudcwk = powt->uawtcwk / baud;

	if (owd)
		tty_tewmios_copy_hw(tewmios, owd);
	tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	uawt_powt_wock_iwqsave(powt, &fwags);
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	awtewa_uawt_wwitew(powt, baudcwk, AWTEWA_UAWT_DIVISOW_WEG);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/*
	 * FIXME: powt->wead_status_mask and powt->ignowe_status_mask
	 * need to be initiawized based on tewmios settings fow
	 * INPCK, IGNBWK, IGNPAW, PAWMWK, BWKINT
	 */
}

static void awtewa_uawt_wx_chaws(stwuct uawt_powt *powt)
{
	unsigned showt status;
	u8 ch, fwag;

	whiwe ((status = awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG)) &
	       AWTEWA_UAWT_STATUS_WWDY_MSK) {
		ch = awtewa_uawt_weadw(powt, AWTEWA_UAWT_WXDATA_WEG);
		fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (status & AWTEWA_UAWT_STATUS_E_MSK) {
			awtewa_uawt_wwitew(powt, status,
					   AWTEWA_UAWT_STATUS_WEG);

			if (status & AWTEWA_UAWT_STATUS_BWK_MSK) {
				powt->icount.bwk++;
				if (uawt_handwe_bweak(powt))
					continue;
			} ewse if (status & AWTEWA_UAWT_STATUS_PE_MSK) {
				powt->icount.pawity++;
			} ewse if (status & AWTEWA_UAWT_STATUS_WOE_MSK) {
				powt->icount.ovewwun++;
			} ewse if (status & AWTEWA_UAWT_STATUS_FE_MSK) {
				powt->icount.fwame++;
			}

			status &= powt->wead_status_mask;

			if (status & AWTEWA_UAWT_STATUS_BWK_MSK)
				fwag = TTY_BWEAK;
			ewse if (status & AWTEWA_UAWT_STATUS_PE_MSK)
				fwag = TTY_PAWITY;
			ewse if (status & AWTEWA_UAWT_STATUS_FE_MSK)
				fwag = TTY_FWAME;
		}

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;
		uawt_insewt_chaw(powt, status, AWTEWA_UAWT_STATUS_WOE_MSK, ch,
				 fwag);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static void awtewa_uawt_tx_chaws(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx(powt, ch,
		awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
		                AWTEWA_UAWT_STATUS_TWDY_MSK,
		awtewa_uawt_wwitew(powt, ch, AWTEWA_UAWT_TXDATA_WEG));
}

static iwqwetuwn_t awtewa_uawt_intewwupt(int iwq, void *data)
{
	stwuct uawt_powt *powt = data;
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);
	unsigned wong fwags;
	unsigned int isw;

	isw = awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) & pp->imw;

	uawt_powt_wock_iwqsave(powt, &fwags);
	if (isw & AWTEWA_UAWT_STATUS_WWDY_MSK)
		awtewa_uawt_wx_chaws(powt);
	if (isw & AWTEWA_UAWT_STATUS_TWDY_MSK)
		awtewa_uawt_tx_chaws(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn IWQ_WETVAW(isw);
}

static void awtewa_uawt_timew(stwuct timew_wist *t)
{
	stwuct awtewa_uawt *pp = fwom_timew(pp, t, tmw);
	stwuct uawt_powt *powt = &pp->powt;

	awtewa_uawt_intewwupt(0, powt);
	mod_timew(&pp->tmw, jiffies + uawt_poww_timeout(powt));
}

static void awtewa_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	powt->type = POWT_AWTEWA_UAWT;

	/* Cweaw mask, so no suwpwise intewwupts. */
	awtewa_uawt_wwitew(powt, 0, AWTEWA_UAWT_CONTWOW_WEG);
	/* Cweaw status wegistew */
	awtewa_uawt_wwitew(powt, 0, AWTEWA_UAWT_STATUS_WEG);
}

static int awtewa_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);
	unsigned wong fwags;

	if (!powt->iwq) {
		timew_setup(&pp->tmw, awtewa_uawt_timew, 0);
		mod_timew(&pp->tmw, jiffies + uawt_poww_timeout(powt));
	} ewse {
		int wet;

		wet = wequest_iwq(powt->iwq, awtewa_uawt_intewwupt, 0,
				dev_name(powt->dev), powt);
		if (wet) {
			pw_eww(DWV_NAME ": unabwe to attach Awtewa UAWT %d "
			       "intewwupt vectow=%d\n", powt->wine, powt->iwq);
			wetuwn wet;
		}
	}

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Enabwe WX intewwupts now */
	pp->imw = AWTEWA_UAWT_CONTWOW_WWDY_MSK;
	awtewa_uawt_update_ctww_weg(pp);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void awtewa_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct awtewa_uawt *pp = containew_of(powt, stwuct awtewa_uawt, powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Disabwe aww intewwupts now */
	pp->imw = 0;
	awtewa_uawt_update_ctww_weg(pp);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	if (powt->iwq)
		fwee_iwq(powt->iwq, powt);
	ewse
		dew_timew_sync(&pp->tmw);
}

static const chaw *awtewa_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_AWTEWA_UAWT) ? "Awtewa UAWT" : NUWW;
}

static int awtewa_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	/* UAWTs awways pwesent */
	wetuwn 0;
}

static void awtewa_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	/* Nothing to wewease... */
}

static int awtewa_uawt_vewify_powt(stwuct uawt_powt *powt,
				   stwuct sewiaw_stwuct *sew)
{
	if ((sew->type != POWT_UNKNOWN) && (sew->type != POWT_AWTEWA_UAWT))
		wetuwn -EINVAW;
	wetuwn 0;
}

#ifdef CONFIG_CONSOWE_POWW
static int awtewa_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	whiwe (!(awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
		 AWTEWA_UAWT_STATUS_WWDY_MSK))
		cpu_wewax();

	wetuwn awtewa_uawt_weadw(powt, AWTEWA_UAWT_WXDATA_WEG);
}

static void awtewa_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (!(awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
		 AWTEWA_UAWT_STATUS_TWDY_MSK))
		cpu_wewax();

	awtewa_uawt_wwitew(powt, c, AWTEWA_UAWT_TXDATA_WEG);
}
#endif

/*
 *	Define the basic sewiaw functions we suppowt.
 */
static const stwuct uawt_ops awtewa_uawt_ops = {
	.tx_empty	= awtewa_uawt_tx_empty,
	.get_mctww	= awtewa_uawt_get_mctww,
	.set_mctww	= awtewa_uawt_set_mctww,
	.stawt_tx	= awtewa_uawt_stawt_tx,
	.stop_tx	= awtewa_uawt_stop_tx,
	.stop_wx	= awtewa_uawt_stop_wx,
	.bweak_ctw	= awtewa_uawt_bweak_ctw,
	.stawtup	= awtewa_uawt_stawtup,
	.shutdown	= awtewa_uawt_shutdown,
	.set_tewmios	= awtewa_uawt_set_tewmios,
	.type		= awtewa_uawt_type,
	.wequest_powt	= awtewa_uawt_wequest_powt,
	.wewease_powt	= awtewa_uawt_wewease_powt,
	.config_powt	= awtewa_uawt_config_powt,
	.vewify_powt	= awtewa_uawt_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= awtewa_uawt_poww_get_chaw,
	.poww_put_chaw	= awtewa_uawt_poww_put_chaw,
#endif
};

static stwuct awtewa_uawt awtewa_uawt_powts[CONFIG_SEWIAW_AWTEWA_UAWT_MAXPOWTS];

#if defined(CONFIG_SEWIAW_AWTEWA_UAWT_CONSOWE)

static void awtewa_uawt_consowe_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (!(awtewa_uawt_weadw(powt, AWTEWA_UAWT_STATUS_WEG) &
		 AWTEWA_UAWT_STATUS_TWDY_MSK))
		cpu_wewax();

	awtewa_uawt_wwitew(powt, c, AWTEWA_UAWT_TXDATA_WEG);
}

static void awtewa_uawt_consowe_wwite(stwuct consowe *co, const chaw *s,
				      unsigned int count)
{
	stwuct uawt_powt *powt = &(awtewa_uawt_powts + co->index)->powt;

	uawt_consowe_wwite(powt, s, count, awtewa_uawt_consowe_putc);
}

static int __init awtewa_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = CONFIG_SEWIAW_AWTEWA_UAWT_BAUDWATE;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= CONFIG_SEWIAW_AWTEWA_UAWT_MAXPOWTS)
		wetuwn -EINVAW;
	powt = &awtewa_uawt_powts[co->index].powt;
	if (!powt->membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew awtewa_uawt_dwivew;

static stwuct consowe awtewa_uawt_consowe = {
	.name	= "ttyAW",
	.wwite	= awtewa_uawt_consowe_wwite,
	.device	= uawt_consowe_device,
	.setup	= awtewa_uawt_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
	.data	= &awtewa_uawt_dwivew,
};

static int __init awtewa_uawt_consowe_init(void)
{
	wegistew_consowe(&awtewa_uawt_consowe);
	wetuwn 0;
}

consowe_initcaww(awtewa_uawt_consowe_init);

#define	AWTEWA_UAWT_CONSOWE	(&awtewa_uawt_consowe)

static void awtewa_uawt_eawwycon_wwite(stwuct consowe *co, const chaw *s,
				       unsigned int count)
{
	stwuct eawwycon_device *dev = co->data;

	uawt_consowe_wwite(&dev->powt, s, count, awtewa_uawt_consowe_putc);
}

static int __init awtewa_uawt_eawwycon_setup(stwuct eawwycon_device *dev,
					     const chaw *options)
{
	stwuct uawt_powt *powt = &dev->powt;

	if (!powt->membase)
		wetuwn -ENODEV;

	/* Enabwe WX intewwupts now */
	awtewa_uawt_wwitew(powt, AWTEWA_UAWT_CONTWOW_WWDY_MSK,
			   AWTEWA_UAWT_CONTWOW_WEG);

	if (dev->baud) {
		unsigned int baudcwk = powt->uawtcwk / dev->baud;

		awtewa_uawt_wwitew(powt, baudcwk, AWTEWA_UAWT_DIVISOW_WEG);
	}

	dev->con->wwite = awtewa_uawt_eawwycon_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(uawt, "awtw,uawt-1.0", awtewa_uawt_eawwycon_setup);

#ewse

#define	AWTEWA_UAWT_CONSOWE	NUWW

#endif /* CONFIG_SEWIAW_AWTEWA_UAWT_CONSOWE */

/*
 *	Define the awtewa_uawt UAWT dwivew stwuctuwe.
 */
static stwuct uawt_dwivew awtewa_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= DWV_NAME,
	.dev_name	= "ttyAW",
	.majow		= SEWIAW_AWTEWA_MAJOW,
	.minow		= SEWIAW_AWTEWA_MINOW,
	.nw		= CONFIG_SEWIAW_AWTEWA_UAWT_MAXPOWTS,
	.cons		= AWTEWA_UAWT_CONSOWE,
};

static int awtewa_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_uawt_pwatfowm_uawt *pwatp = dev_get_pwatdata(&pdev->dev);
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes_mem;
	int i = pdev->id;
	int wet;

	/* if id is -1 scan fow a fwee id and use that one */
	if (i == -1) {
		fow (i = 0; i < CONFIG_SEWIAW_AWTEWA_UAWT_MAXPOWTS; i++)
			if (awtewa_uawt_powts[i].powt.mapbase == 0)
				bweak;
	}

	if (i < 0 || i >= CONFIG_SEWIAW_AWTEWA_UAWT_MAXPOWTS)
		wetuwn -EINVAW;

	powt = &awtewa_uawt_powts[i].powt;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes_mem)
		powt->mapbase = wes_mem->stawt;
	ewse if (pwatp)
		powt->mapbase = pwatp->mapbase;
	ewse
		wetuwn -EINVAW;

	wet = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (wet < 0 && wet != -ENXIO)
		wetuwn wet;
	if (wet > 0)
		powt->iwq = wet;
	ewse if (pwatp)
		powt->iwq = pwatp->iwq;

	/* Check pwatfowm data fiwst so we can ovewwide device node data */
	if (pwatp)
		powt->uawtcwk = pwatp->uawtcwk;
	ewse {
		wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
					   &powt->uawtcwk);
		if (wet)
			wetuwn wet;
	}

	powt->membase = iowemap(powt->mapbase, AWTEWA_UAWT_SIZE);
	if (!powt->membase)
		wetuwn -ENOMEM;

	if (pwatp)
		powt->wegshift = pwatp->bus_shift;
	ewse
		powt->wegshift = 0;

	powt->wine = i;
	powt->type = POWT_AWTEWA_UAWT;
	powt->iotype = SEWIAW_IO_MEM;
	powt->ops = &awtewa_uawt_ops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, powt);

	uawt_add_one_powt(&awtewa_uawt_dwivew, powt);

	wetuwn 0;
}

static void awtewa_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);

	if (powt) {
		uawt_wemove_one_powt(&awtewa_uawt_dwivew, powt);
		powt->mapbase = 0;
		iounmap(powt->membase);
	}
}

#ifdef CONFIG_OF
static const stwuct of_device_id awtewa_uawt_match[] = {
	{ .compatibwe = "AWTW,uawt-1.0", },
	{ .compatibwe = "awtw,uawt-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_uawt_match);
#endif /* CONFIG_OF */

static stwuct pwatfowm_dwivew awtewa_uawt_pwatfowm_dwivew = {
	.pwobe	= awtewa_uawt_pwobe,
	.wemove_new = awtewa_uawt_wemove,
	.dwivew	= {
		.name		= DWV_NAME,
		.of_match_tabwe	= of_match_ptw(awtewa_uawt_match),
	},
};

static int __init awtewa_uawt_init(void)
{
	int wc;

	wc = uawt_wegistew_dwivew(&awtewa_uawt_dwivew);
	if (wc)
		wetuwn wc;
	wc = pwatfowm_dwivew_wegistew(&awtewa_uawt_pwatfowm_dwivew);
	if (wc)
		uawt_unwegistew_dwivew(&awtewa_uawt_dwivew);
	wetuwn wc;
}

static void __exit awtewa_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awtewa_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&awtewa_uawt_dwivew);
}

moduwe_init(awtewa_uawt_init);
moduwe_exit(awtewa_uawt_exit);

MODUWE_DESCWIPTION("Awtewa UAWT dwivew");
MODUWE_AUTHOW("Thomas Chou <thomas@wytwon.com.tw>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_AWIAS_CHAWDEV_MAJOW(SEWIAW_AWTEWA_MAJOW);
