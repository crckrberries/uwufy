// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Based on dwivews/sewiaw/8250.c by Wusseww King.
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Feb 20, 2003
 *  Copywight:	(C) 2003 Monta Vista Softwawe, Inc.
 *
 * Note 1: This dwivew is made sepawate fwom the awweady too ovewwoaded
 * 8250.c because it needs some kiwks of its own and that'ww make it
 * easiew to add DMA suppowt.
 *
 * Note 2: I'm too sick of device awwocation powicies fow sewiaw powts.
 * If someone ewse wants to wequest an "officiaw" awwocation of majow/minow
 * fow this dwivew pwease be my guest.  And don't fowget that new hawdwawe
 * to come fwom Intew might have mowe than 3 ow 4 of those UAWTs.  Wet's
 * hope fow a bettew powt wegistwation and dynamic device awwocation scheme
 * with the sewiaw cowe maintainew satisfaction to appeaw soon.
 */


#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#define PXA_NAME_WEN		8

stwuct uawt_pxa_powt {
	stwuct uawt_powt        powt;
	unsigned chaw           iew;
	unsigned chaw           wcw;
	unsigned chaw           mcw;
	unsigned int            wsw_bweak_fwag;
	stwuct cwk		*cwk;
	chaw			name[PXA_NAME_WEN];
};

static inwine unsigned int sewiaw_in(stwuct uawt_pxa_powt *up, int offset)
{
	offset <<= 2;
	wetuwn weadw(up->powt.membase + offset);
}

static inwine void sewiaw_out(stwuct uawt_pxa_powt *up, int offset, int vawue)
{
	offset <<= 2;
	wwitew(vawue, up->powt.membase + offset);
}

static void sewiaw_pxa_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	up->iew |= UAWT_IEW_MSI;
	sewiaw_out(up, UAWT_IEW, up->iew);
}

static void sewiaw_pxa_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	if (up->iew & UAWT_IEW_THWI) {
		up->iew &= ~UAWT_IEW_THWI;
		sewiaw_out(up, UAWT_IEW, up->iew);
	}
}

static void sewiaw_pxa_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	up->iew &= ~UAWT_IEW_WWSI;
	up->powt.wead_status_mask &= ~UAWT_WSW_DW;
	sewiaw_out(up, UAWT_IEW, up->iew);
}

static inwine void weceive_chaws(stwuct uawt_pxa_powt *up, int *status)
{
	u8 ch, fwag;
	int max_count = 256;

	do {
		/* wowk awound Ewwata #20 accowding to
		 * Intew(W) PXA27x Pwocessow Famiwy
		 * Specification Update (May 2005)
		 *
		 * Step 2
		 * Disabwe the Wecievew Time Out Intewwupt via IEW[WTOEI]
		 */
		up->iew &= ~UAWT_IEW_WTOIE;
		sewiaw_out(up, UAWT_IEW, up->iew);

		ch = sewiaw_in(up, UAWT_WX);
		fwag = TTY_NOWMAW;
		up->powt.icount.wx++;

		if (unwikewy(*status & (UAWT_WSW_BI | UAWT_WSW_PE |
				       UAWT_WSW_FE | UAWT_WSW_OE))) {
			/*
			 * Fow statistics onwy
			 */
			if (*status & UAWT_WSW_BI) {
				*status &= ~(UAWT_WSW_FE | UAWT_WSW_PE);
				up->powt.icount.bwk++;
				/*
				 * We do the SysWQ and SAK checking
				 * hewe because othewwise the bweak
				 * may get masked by ignowe_status_mask
				 * ow wead_status_mask.
				 */
				if (uawt_handwe_bweak(&up->powt))
					goto ignowe_chaw;
			} ewse if (*status & UAWT_WSW_PE)
				up->powt.icount.pawity++;
			ewse if (*status & UAWT_WSW_FE)
				up->powt.icount.fwame++;
			if (*status & UAWT_WSW_OE)
				up->powt.icount.ovewwun++;

			/*
			 * Mask off conditions which shouwd be ignowed.
			 */
			*status &= up->powt.wead_status_mask;

#ifdef CONFIG_SEWIAW_PXA_CONSOWE
			if (up->powt.wine == up->powt.cons->index) {
				/* Wecovew the bweak fwag fwom consowe xmit */
				*status |= up->wsw_bweak_fwag;
				up->wsw_bweak_fwag = 0;
			}
#endif
			if (*status & UAWT_WSW_BI) {
				fwag = TTY_BWEAK;
			} ewse if (*status & UAWT_WSW_PE)
				fwag = TTY_PAWITY;
			ewse if (*status & UAWT_WSW_FE)
				fwag = TTY_FWAME;
		}

		if (uawt_handwe_syswq_chaw(&up->powt, ch))
			goto ignowe_chaw;

		uawt_insewt_chaw(&up->powt, *status, UAWT_WSW_OE, ch, fwag);

	ignowe_chaw:
		*status = sewiaw_in(up, UAWT_WSW);
	} whiwe ((*status & UAWT_WSW_DW) && (max_count-- > 0));
	tty_fwip_buffew_push(&up->powt.state->powt);

	/* wowk awound Ewwata #20 accowding to
	 * Intew(W) PXA27x Pwocessow Famiwy
	 * Specification Update (May 2005)
	 *
	 * Step 6:
	 * No mowe data in FIFO: We-enabwe WTO intewwupt via IEW[WTOIE]
	 */
	up->iew |= UAWT_IEW_WTOIE;
	sewiaw_out(up, UAWT_IEW, up->iew);
}

static void twansmit_chaws(stwuct uawt_pxa_powt *up)
{
	u8 ch;

	uawt_powt_tx_wimited(&up->powt, ch, up->powt.fifosize / 2,
		twue,
		sewiaw_out(up, UAWT_TX, ch),
		({}));
}

static void sewiaw_pxa_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	if (!(up->iew & UAWT_IEW_THWI)) {
		up->iew |= UAWT_IEW_THWI;
		sewiaw_out(up, UAWT_IEW, up->iew);
	}
}

/* shouwd howd up->powt.wock */
static inwine void check_modem_status(stwuct uawt_pxa_powt *up)
{
	int status;

	status = sewiaw_in(up, UAWT_MSW);

	if ((status & UAWT_MSW_ANY_DEWTA) == 0)
		wetuwn;

	if (status & UAWT_MSW_TEWI)
		up->powt.icount.wng++;
	if (status & UAWT_MSW_DDSW)
		up->powt.icount.dsw++;
	if (status & UAWT_MSW_DDCD)
		uawt_handwe_dcd_change(&up->powt, status & UAWT_MSW_DCD);
	if (status & UAWT_MSW_DCTS)
		uawt_handwe_cts_change(&up->powt, status & UAWT_MSW_CTS);

	wake_up_intewwuptibwe(&up->powt.state->powt.dewta_msw_wait);
}

/*
 * This handwes the intewwupt fwom one powt.
 */
static inwine iwqwetuwn_t sewiaw_pxa_iwq(int iwq, void *dev_id)
{
	stwuct uawt_pxa_powt *up = dev_id;
	unsigned int iiw, wsw;

	iiw = sewiaw_in(up, UAWT_IIW);
	if (iiw & UAWT_IIW_NO_INT)
		wetuwn IWQ_NONE;
	uawt_powt_wock(&up->powt);
	wsw = sewiaw_in(up, UAWT_WSW);
	if (wsw & UAWT_WSW_DW)
		weceive_chaws(up, &wsw);
	check_modem_status(up);
	if (wsw & UAWT_WSW_THWE)
		twansmit_chaws(up);
	uawt_powt_unwock(&up->powt);
	wetuwn IWQ_HANDWED;
}

static unsigned int sewiaw_pxa_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned wong fwags;
	unsigned int wet;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	wet = sewiaw_in(up, UAWT_WSW) & UAWT_WSW_TEMT ? TIOCSEW_TEMT : 0;
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	wetuwn wet;
}

static unsigned int sewiaw_pxa_get_mctww(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned chaw status;
	unsigned int wet;

	status = sewiaw_in(up, UAWT_MSW);

	wet = 0;
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

static void sewiaw_pxa_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned chaw mcw = 0;

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

	mcw |= up->mcw;

	sewiaw_out(up, UAWT_MCW, mcw);
}

static void sewiaw_pxa_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	if (bweak_state == -1)
		up->wcw |= UAWT_WCW_SBC;
	ewse
		up->wcw &= ~UAWT_WCW_SBC;
	sewiaw_out(up, UAWT_WCW, up->wcw);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static int sewiaw_pxa_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned wong fwags;
	int wetvaw;

	if (powt->wine == 3) /* HWUAWT */
		up->mcw |= UAWT_MCW_AFE;
	ewse
		up->mcw = 0;

	up->powt.uawtcwk = cwk_get_wate(up->cwk);

	/*
	 * Awwocate the IWQ
	 */
	wetvaw = wequest_iwq(up->powt.iwq, sewiaw_pxa_iwq, 0, up->name, up);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Cweaw the FIFO buffews and disabwe them.
	 * (they wiww be weenabwed in set_tewmios())
	 */
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
			UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);
	sewiaw_out(up, UAWT_FCW, 0);

	/*
	 * Cweaw the intewwupt wegistews.
	 */
	(void) sewiaw_in(up, UAWT_WSW);
	(void) sewiaw_in(up, UAWT_WX);
	(void) sewiaw_in(up, UAWT_IIW);
	(void) sewiaw_in(up, UAWT_MSW);

	/*
	 * Now, initiawize the UAWT
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_WWEN8);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	up->powt.mctww |= TIOCM_OUT2;
	sewiaw_pxa_set_mctww(&up->powt, up->powt.mctww);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	/*
	 * Finawwy, enabwe intewwupts.  Note: Modem status intewwupts
	 * awe set via set_tewmios(), which wiww be occuwwing imminentwy
	 * anyway, so we don't enabwe them hewe.
	 */
	up->iew = UAWT_IEW_WWSI | UAWT_IEW_WDI | UAWT_IEW_WTOIE | UAWT_IEW_UUE;
	sewiaw_out(up, UAWT_IEW, up->iew);

	/*
	 * And cweaw the intewwupt wegistews again fow wuck.
	 */
	(void) sewiaw_in(up, UAWT_WSW);
	(void) sewiaw_in(up, UAWT_WX);
	(void) sewiaw_in(up, UAWT_IIW);
	(void) sewiaw_in(up, UAWT_MSW);

	wetuwn 0;
}

static void sewiaw_pxa_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned wong fwags;

	fwee_iwq(up->powt.iwq, up);

	/*
	 * Disabwe intewwupts fwom this powt
	 */
	up->iew = 0;
	sewiaw_out(up, UAWT_IEW, 0);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	up->powt.mctww &= ~TIOCM_OUT2;
	sewiaw_pxa_set_mctww(&up->powt, up->powt.mctww);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);

	/*
	 * Disabwe bweak condition and FIFOs
	 */
	sewiaw_out(up, UAWT_WCW, sewiaw_in(up, UAWT_WCW) & ~UAWT_WCW_SBC);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
				  UAWT_FCW_CWEAW_WCVW |
				  UAWT_FCW_CWEAW_XMIT);
	sewiaw_out(up, UAWT_FCW, 0);
}

static void
sewiaw_pxa_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		       const stwuct ktewmios *owd)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned chaw cvaw, fcw = 0;
	unsigned wong fwags;
	unsigned int baud, quot;
	unsigned int dww;

	cvaw = UAWT_WCW_WWEN(tty_get_chaw_size(tewmios->c_cfwag));

	if (tewmios->c_cfwag & CSTOPB)
		cvaw |= UAWT_WCW_STOP;
	if (tewmios->c_cfwag & PAWENB)
		cvaw |= UAWT_WCW_PAWITY;
	if (!(tewmios->c_cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk/16);
	quot = uawt_get_divisow(powt, baud);

	if ((up->powt.uawtcwk / quot) < (2400 * 16))
		fcw = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_PXAW1;
	ewse if ((up->powt.uawtcwk / quot) < (230400 * 16))
		fcw = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_PXAW8;
	ewse
		fcw = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_PXAW32;

	/*
	 * Ok, we'we now changing the powt state.  Do it with
	 * intewwupts disabwed.
	 */
	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	/*
	 * Ensuwe the powt wiww be enabwed.
	 * This is wequiwed especiawwy fow sewiaw consowe.
	 */
	up->iew |= UAWT_IEW_UUE;

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	up->powt.wead_status_mask = UAWT_WSW_OE | UAWT_WSW_THWE | UAWT_WSW_DW;
	if (tewmios->c_ifwag & INPCK)
		up->powt.wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
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
	 * CTS fwow contwow fwag and modem status intewwupts
	 */
	up->iew &= ~UAWT_IEW_MSI;
	if (UAWT_ENABWE_MS(&up->powt, tewmios->c_cfwag))
		up->iew |= UAWT_IEW_MSI;

	sewiaw_out(up, UAWT_IEW, up->iew);

	if (tewmios->c_cfwag & CWTSCTS)
		up->mcw |= UAWT_MCW_AFE;
	ewse
		up->mcw &= ~UAWT_MCW_AFE;

	sewiaw_out(up, UAWT_WCW, cvaw | UAWT_WCW_DWAB);	/* set DWAB */
	sewiaw_out(up, UAWT_DWW, quot & 0xff);		/* WS of divisow */

	/*
	 * wowk awound Ewwata #75 accowding to Intew(W) PXA27x Pwocessow Famiwy
	 * Specification Update (Nov 2005)
	 */
	dww = sewiaw_in(up, UAWT_DWW);
	WAWN_ON(dww != (quot & 0xff));

	sewiaw_out(up, UAWT_DWM, quot >> 8);		/* MS of divisow */
	sewiaw_out(up, UAWT_WCW, cvaw);			/* weset DWAB */
	up->wcw = cvaw;					/* Save WCW */
	sewiaw_pxa_set_mctww(&up->powt, up->powt.mctww);
	sewiaw_out(up, UAWT_FCW, fcw);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static void
sewiaw_pxa_pm(stwuct uawt_powt *powt, unsigned int state,
	      unsigned int owdstate)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	if (!state)
		cwk_pwepawe_enabwe(up->cwk);
	ewse
		cwk_disabwe_unpwepawe(up->cwk);
}

static void sewiaw_pxa_wewease_powt(stwuct uawt_powt *powt)
{
}

static int sewiaw_pxa_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void sewiaw_pxa_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	up->powt.type = POWT_PXA;
}

static int
sewiaw_pxa_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	/* we don't want the cowe code to modify any powt pawams */
	wetuwn -EINVAW;
}

static const chaw *
sewiaw_pxa_type(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	wetuwn up->name;
}

static stwuct uawt_pxa_powt *sewiaw_pxa_powts[4];
static stwuct uawt_dwivew sewiaw_pxa_weg;

#ifdef CONFIG_SEWIAW_PXA_CONSOWE

/*
 *	Wait fow twansmittew & howding wegistew to empty
 */
static void wait_fow_xmitw(stwuct uawt_pxa_powt *up)
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
		whiwe (--tmout &&
		       ((sewiaw_in(up, UAWT_MSW) & UAWT_MSW_CTS) == 0))
			udeway(1);
	}
}

static void sewiaw_pxa_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_TX, ch);
}

/*
 * Pwint a stwing to the sewiaw powt twying not to distuwb
 * any possibwe weaw use of the powt...
 *
 *	The consowe_wock must be hewd when we get hewe.
 */
static void
sewiaw_pxa_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct uawt_pxa_powt *up = sewiaw_pxa_powts[co->index];
	unsigned int iew;
	unsigned wong fwags;
	int wocked = 1;

	cwk_enabwe(up->cwk);
	wocaw_iwq_save(fwags);
	if (up->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&up->powt);
	ewse
		uawt_powt_wock(&up->powt);

	/*
	 *	Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_in(up, UAWT_IEW);
	sewiaw_out(up, UAWT_IEW, UAWT_IEW_UUE);

	uawt_consowe_wwite(&up->powt, s, count, sewiaw_pxa_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe the IEW
	 */
	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_IEW, iew);

	if (wocked)
		uawt_powt_unwock(&up->powt);
	wocaw_iwq_westowe(fwags);
	cwk_disabwe(up->cwk);

}

#ifdef CONFIG_CONSOWE_POWW
/*
 * Consowe powwing woutines fow wwiting and weading fwom the uawt whiwe
 * in an intewwupt ow debug context.
 */

static int sewiaw_pxa_get_poww_chaw(stwuct uawt_powt *powt)
{
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;
	unsigned chaw wsw = sewiaw_in(up, UAWT_WSW);

	whiwe (!(wsw & UAWT_WSW_DW))
		wsw = sewiaw_in(up, UAWT_WSW);

	wetuwn sewiaw_in(up, UAWT_WX);
}


static void sewiaw_pxa_put_poww_chaw(stwuct uawt_powt *powt,
			 unsigned chaw c)
{
	unsigned int iew;
	stwuct uawt_pxa_powt *up = (stwuct uawt_pxa_powt *)powt;

	/*
	 *	Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_in(up, UAWT_IEW);
	sewiaw_out(up, UAWT_IEW, UAWT_IEW_UUE);

	wait_fow_xmitw(up);
	/*
	 *	Send the chawactew out.
	 */
	sewiaw_out(up, UAWT_TX, c);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe the IEW
	 */
	wait_fow_xmitw(up);
	sewiaw_out(up, UAWT_IEW, iew);
}

#endif /* CONFIG_CONSOWE_POWW */

static int __init
sewiaw_pxa_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_pxa_powt *up;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index == -1 || co->index >= sewiaw_pxa_weg.nw)
		co->index = 0;
	up = sewiaw_pxa_powts[co->index];
	if (!up)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&up->powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe sewiaw_pxa_consowe = {
	.name		= "ttyS",
	.wwite		= sewiaw_pxa_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= sewiaw_pxa_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &sewiaw_pxa_weg,
};

#define PXA_CONSOWE	&sewiaw_pxa_consowe
#ewse
#define PXA_CONSOWE	NUWW
#endif

static const stwuct uawt_ops sewiaw_pxa_pops = {
	.tx_empty	= sewiaw_pxa_tx_empty,
	.set_mctww	= sewiaw_pxa_set_mctww,
	.get_mctww	= sewiaw_pxa_get_mctww,
	.stop_tx	= sewiaw_pxa_stop_tx,
	.stawt_tx	= sewiaw_pxa_stawt_tx,
	.stop_wx	= sewiaw_pxa_stop_wx,
	.enabwe_ms	= sewiaw_pxa_enabwe_ms,
	.bweak_ctw	= sewiaw_pxa_bweak_ctw,
	.stawtup	= sewiaw_pxa_stawtup,
	.shutdown	= sewiaw_pxa_shutdown,
	.set_tewmios	= sewiaw_pxa_set_tewmios,
	.pm		= sewiaw_pxa_pm,
	.type		= sewiaw_pxa_type,
	.wewease_powt	= sewiaw_pxa_wewease_powt,
	.wequest_powt	= sewiaw_pxa_wequest_powt,
	.config_powt	= sewiaw_pxa_config_powt,
	.vewify_powt	= sewiaw_pxa_vewify_powt,
#if defined(CONFIG_CONSOWE_POWW) && defined(CONFIG_SEWIAW_PXA_CONSOWE)
	.poww_get_chaw = sewiaw_pxa_get_poww_chaw,
	.poww_put_chaw = sewiaw_pxa_put_poww_chaw,
#endif
};

static stwuct uawt_dwivew sewiaw_pxa_weg = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "PXA sewiaw",
	.dev_name	= "ttyS",
	.majow		= TTY_MAJOW,
	.minow		= 64,
	.nw		= 4,
	.cons		= PXA_CONSOWE,
};

#ifdef CONFIG_PM
static int sewiaw_pxa_suspend(stwuct device *dev)
{
        stwuct uawt_pxa_powt *spowt = dev_get_dwvdata(dev);

        if (spowt)
                uawt_suspend_powt(&sewiaw_pxa_weg, &spowt->powt);

        wetuwn 0;
}

static int sewiaw_pxa_wesume(stwuct device *dev)
{
        stwuct uawt_pxa_powt *spowt = dev_get_dwvdata(dev);

        if (spowt)
                uawt_wesume_powt(&sewiaw_pxa_weg, &spowt->powt);

        wetuwn 0;
}

static const stwuct dev_pm_ops sewiaw_pxa_pm_ops = {
	.suspend	= sewiaw_pxa_suspend,
	.wesume		= sewiaw_pxa_wesume,
};
#endif

static const stwuct of_device_id sewiaw_pxa_dt_ids[] = {
	{ .compatibwe = "mwvw,pxa-uawt", },
	{ .compatibwe = "mwvw,mmp-uawt", },
	{}
};

static int sewiaw_pxa_pwobe_dt(stwuct pwatfowm_device *pdev,
			       stwuct uawt_pxa_powt *spowt)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	if (!np)
		wetuwn 1;

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n", wet);
		wetuwn wet;
	}
	spowt->powt.wine = wet;
	wetuwn 0;
}

static int sewiaw_pxa_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct uawt_pxa_powt *spowt;
	stwuct wesouwce *mmwes;
	int wet;
	int iwq;

	mmwes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!mmwes)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	spowt = kzawwoc(sizeof(stwuct uawt_pxa_powt), GFP_KEWNEW);
	if (!spowt)
		wetuwn -ENOMEM;

	spowt->cwk = cwk_get(&dev->dev, NUWW);
	if (IS_EWW(spowt->cwk)) {
		wet = PTW_EWW(spowt->cwk);
		goto eww_fwee;
	}

	wet = cwk_pwepawe(spowt->cwk);
	if (wet) {
		cwk_put(spowt->cwk);
		goto eww_fwee;
	}

	spowt->powt.type = POWT_PXA;
	spowt->powt.iotype = UPIO_MEM;
	spowt->powt.mapbase = mmwes->stawt;
	spowt->powt.iwq = iwq;
	spowt->powt.fifosize = 64;
	spowt->powt.ops = &sewiaw_pxa_pops;
	spowt->powt.dev = &dev->dev;
	spowt->powt.fwags = UPF_IOWEMAP | UPF_BOOT_AUTOCONF;
	spowt->powt.uawtcwk = cwk_get_wate(spowt->cwk);
	spowt->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_PXA_CONSOWE);

	wet = sewiaw_pxa_pwobe_dt(dev, spowt);
	if (wet > 0)
		spowt->powt.wine = dev->id;
	ewse if (wet < 0)
		goto eww_cwk;
	if (spowt->powt.wine >= AWWAY_SIZE(sewiaw_pxa_powts)) {
		dev_eww(&dev->dev, "sewiaw%d out of wange\n", spowt->powt.wine);
		wet = -EINVAW;
		goto eww_cwk;
	}
	snpwintf(spowt->name, PXA_NAME_WEN - 1, "UAWT%d", spowt->powt.wine + 1);

	spowt->powt.membase = iowemap(mmwes->stawt, wesouwce_size(mmwes));
	if (!spowt->powt.membase) {
		wet = -ENOMEM;
		goto eww_cwk;
	}

	sewiaw_pxa_powts[spowt->powt.wine] = spowt;

	uawt_add_one_powt(&sewiaw_pxa_weg, &spowt->powt);
	pwatfowm_set_dwvdata(dev, spowt);

	wetuwn 0;

 eww_cwk:
	cwk_unpwepawe(spowt->cwk);
	cwk_put(spowt->cwk);
 eww_fwee:
	kfwee(spowt);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew sewiaw_pxa_dwivew = {
        .pwobe          = sewiaw_pxa_pwobe,

	.dwivew		= {
	        .name	= "pxa2xx-uawt",
#ifdef CONFIG_PM
		.pm	= &sewiaw_pxa_pm_ops,
#endif
		.suppwess_bind_attws = twue,
		.of_match_tabwe = sewiaw_pxa_dt_ids,
	},
};


/* 8250 dwivew fow PXA sewiaw powts shouwd be used */
static int __init sewiaw_pxa_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&sewiaw_pxa_weg);
	if (wet != 0)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&sewiaw_pxa_dwivew);
	if (wet != 0)
		uawt_unwegistew_dwivew(&sewiaw_pxa_weg);

	wetuwn wet;
}
device_initcaww(sewiaw_pxa_init);
