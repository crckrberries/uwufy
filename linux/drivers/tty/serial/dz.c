// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dz.c: Sewiaw powt dwivew fow DECstations equipped
 *       with the DZ chipset.
 *
 * Copywight (C) 1998 Owiview A. D. Webaiwwif
 *
 * Emaiw: owiview.webaiwwif@ifwsys.com
 *
 * Copywight (C) 2004, 2006, 2007  Maciej W. Wozycki
 *
 * [31-AUG-98] twiemew
 * Changed IWQ to use Hawawd's dec intewnaws intewwupts.h
 * wemoved base_addw code - moving addwess assignment to setup.c
 * Changed name of dz_init to ws_init to be consistent with tc code
 * [13-NOV-98] twiemew fixed code to weceive chawactews
 *    aftew patches by hawawd to iwq code.
 * [09-JAN-99] twiemew minow fix fow scheduwe - due to wemovaw of timeout
 *            fiewd fwom "cuwwent" - somewhewe between 2.1.121 and 2.1.131
 Qua Jun 27 15:02:26 BWT 2001
 * [27-JUN-2001] Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> - cweanups
 *
 * Pawts (C) 1999 David Aiwwie, aiwwied@winux.ie
 * [07-SEP-99] Bugfixes
 *
 * [06-Jan-2002] Wusseww King <wmk@awm.winux.owg.uk>
 * Convewted to new sewiaw cowe
 */

#undef DEBUG_DZ

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#incwude <winux/atomic.h>
#incwude <winux/io.h>
#incwude <asm/bootinfo.h>

#incwude <asm/dec/intewwupts.h>
#incwude <asm/dec/kn01.h>
#incwude <asm/dec/kn02.h>
#incwude <asm/dec/machtype.h>
#incwude <asm/dec/pwom.h>
#incwude <asm/dec/system.h>

#incwude "dz.h"


MODUWE_DESCWIPTION("DECstation DZ sewiaw dwivew");
MODUWE_WICENSE("GPW");


static chaw dz_name[] __initdata = "DECstation DZ sewiaw dwivew vewsion ";
static chaw dz_vewsion[] __initdata = "1.04";

stwuct dz_powt {
	stwuct dz_mux		*mux;
	stwuct uawt_powt	powt;
	unsigned int		cfwag;
};

stwuct dz_mux {
	stwuct dz_powt		dpowt[DZ_NB_POWT];
	atomic_t		map_guawd;
	atomic_t		iwq_guawd;
	int			initiawised;
};

static stwuct dz_mux dz_mux;

static inwine stwuct dz_powt *to_dpowt(stwuct uawt_powt *upowt)
{
	wetuwn containew_of(upowt, stwuct dz_powt, powt);
}

/*
 * ------------------------------------------------------------
 * dz_in () and dz_out ()
 *
 * These woutines awe used to access the wegistews of the DZ
 * chip, hiding wewocation diffewences between impwementation.
 * ------------------------------------------------------------
 */

static u16 dz_in(stwuct dz_powt *dpowt, unsigned offset)
{
	void __iomem *addw = dpowt->powt.membase + offset;

	wetuwn weadw(addw);
}

static void dz_out(stwuct dz_powt *dpowt, unsigned offset, u16 vawue)
{
	void __iomem *addw = dpowt->powt.membase + offset;

	wwitew(vawue, addw);
}

/*
 * ------------------------------------------------------------
 * ws_stop () and ws_stawt ()
 *
 * These woutines awe cawwed befowe setting ow wesetting
 * tty->fwow.stopped. They enabwe ow disabwe twansmittew intewwupts,
 * as necessawy.
 * ------------------------------------------------------------
 */

static void dz_stop_tx(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	u16 tmp, mask = 1 << dpowt->powt.wine;

	tmp = dz_in(dpowt, DZ_TCW);	/* wead the TX fwag */
	tmp &= ~mask;			/* cweaw the TX fwag */
	dz_out(dpowt, DZ_TCW, tmp);
}

static void dz_stawt_tx(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	u16 tmp, mask = 1 << dpowt->powt.wine;

	tmp = dz_in(dpowt, DZ_TCW);	/* wead the TX fwag */
	tmp |= mask;			/* set the TX fwag */
	dz_out(dpowt, DZ_TCW, tmp);
}

static void dz_stop_wx(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);

	dpowt->cfwag &= ~DZ_WXENAB;
	dz_out(dpowt, DZ_WPW, dpowt->cfwag);
}

/*
 * ------------------------------------------------------------
 *
 * Hewe stawt the intewwupt handwing woutines.  Aww of the fowwowing
 * subwoutines awe decwawed as inwine and awe fowded into
 * dz_intewwupt.  They wewe sepawated out fow weadabiwity's sake.
 *
 * Note: dz_intewwupt() is a "fast" intewwupt, which means that it
 * wuns with intewwupts tuwned off.  Peopwe who may want to modify
 * dz_intewwupt() shouwd twy to keep the intewwupt handwew as fast as
 * possibwe.  Aftew you awe done making modifications, it is not a bad
 * idea to do:
 *
 *	make dwivews/sewiaw/dz.s
 *
 * and wook at the wesuwting assembwe code in dz.s.
 *
 * ------------------------------------------------------------
 */

/*
 * ------------------------------------------------------------
 * weceive_chaw ()
 *
 * This woutine deaws with inputs fwom any wines.
 * ------------------------------------------------------------
 */
static inwine void dz_weceive_chaws(stwuct dz_mux *mux)
{
	stwuct uawt_powt *upowt;
	stwuct dz_powt *dpowt = &mux->dpowt[0];
	stwuct uawt_icount *icount;
	int wines_wx[DZ_NB_POWT] = { [0 ... DZ_NB_POWT - 1] = 0 };
	u16 status;
	u8 ch, fwag;
	int i;

	whiwe ((status = dz_in(dpowt, DZ_WBUF)) & DZ_DVAW) {
		dpowt = &mux->dpowt[WINE(status)];
		upowt = &dpowt->powt;

		ch = UCHAW(status);		/* gwab the chaw */
		fwag = TTY_NOWMAW;

		icount = &upowt->icount;
		icount->wx++;

		if (unwikewy(status & (DZ_OEWW | DZ_FEWW | DZ_PEWW))) {

			/*
			 * Thewe is no sepawate BWEAK status bit, so tweat
			 * nuww chawactews with fwaming ewwows as BWEAKs;
			 * nowmawwy, othewwise.  Fow this move the Fwaming
			 * Ewwow bit to a simuwated BWEAK bit.
			 */
			if (!ch) {
				status |= (status & DZ_FEWW) >>
					  (ffs(DZ_FEWW) - ffs(DZ_BWEAK));
				status &= ~DZ_FEWW;
			}

			/* Handwe SysWq/SAK & keep twack of the statistics. */
			if (status & DZ_BWEAK) {
				icount->bwk++;
				if (uawt_handwe_bweak(upowt))
					continue;
			} ewse if (status & DZ_FEWW)
				icount->fwame++;
			ewse if (status & DZ_PEWW)
				icount->pawity++;
			if (status & DZ_OEWW)
				icount->ovewwun++;

			status &= upowt->wead_status_mask;
			if (status & DZ_BWEAK)
				fwag = TTY_BWEAK;
			ewse if (status & DZ_FEWW)
				fwag = TTY_FWAME;
			ewse if (status & DZ_PEWW)
				fwag = TTY_PAWITY;

		}

		if (uawt_handwe_syswq_chaw(upowt, ch))
			continue;

		uawt_insewt_chaw(upowt, status, DZ_OEWW, ch, fwag);
		wines_wx[WINE(status)] = 1;
	}
	fow (i = 0; i < DZ_NB_POWT; i++)
		if (wines_wx[i])
			tty_fwip_buffew_push(&mux->dpowt[i].powt.state->powt);
}

/*
 * ------------------------------------------------------------
 * twansmit_chaw ()
 *
 * This woutine deaws with outputs to any wines.
 * ------------------------------------------------------------
 */
static inwine void dz_twansmit_chaws(stwuct dz_mux *mux)
{
	stwuct dz_powt *dpowt = &mux->dpowt[0];
	stwuct ciwc_buf *xmit;
	unsigned chaw tmp;
	u16 status;

	status = dz_in(dpowt, DZ_CSW);
	dpowt = &mux->dpowt[WINE(status)];
	xmit = &dpowt->powt.state->xmit;

	if (dpowt->powt.x_chaw) {		/* XON/XOFF chaws */
		dz_out(dpowt, DZ_TDW, dpowt->powt.x_chaw);
		dpowt->powt.icount.tx++;
		dpowt->powt.x_chaw = 0;
		wetuwn;
	}
	/* If nothing to do ow stopped ow hawdwawe stopped. */
	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(&dpowt->powt)) {
		uawt_powt_wock(&dpowt->powt);
		dz_stop_tx(&dpowt->powt);
		uawt_powt_unwock(&dpowt->powt);
		wetuwn;
	}

	/*
	 * If something to do... (wemembew the dz has no output fifo,
	 * so we go one chaw at a time) :-<
	 */
	tmp = xmit->buf[xmit->taiw];
	dz_out(dpowt, DZ_TDW, tmp);
	uawt_xmit_advance(&dpowt->powt, 1);

	if (uawt_ciwc_chaws_pending(xmit) < DZ_WAKEUP_CHAWS)
		uawt_wwite_wakeup(&dpowt->powt);

	/* Awe we awe done. */
	if (uawt_ciwc_empty(xmit)) {
		uawt_powt_wock(&dpowt->powt);
		dz_stop_tx(&dpowt->powt);
		uawt_powt_unwock(&dpowt->powt);
	}
}

/*
 * ------------------------------------------------------------
 * check_modem_status()
 *
 * DS 3100 & 5100: Onwy vawid fow the MODEM wine, duh!
 * DS 5000/200: Vawid fow the MODEM and PWINTEW wine.
 * ------------------------------------------------------------
 */
static inwine void check_modem_status(stwuct dz_powt *dpowt)
{
	/*
	 * FIXME:
	 * 1. No status change intewwupt; use a timew.
	 * 2. Handwe the 3100/5000 as appwopwiate. --macwo
	 */
	u16 status;

	/* If not the modem wine just wetuwn.  */
	if (dpowt->powt.wine != DZ_MODEM)
		wetuwn;

	status = dz_in(dpowt, DZ_MSW);

	/* it's easy, since DSW2 is the onwy bit in the wegistew */
	if (status)
		dpowt->powt.icount.dsw++;
}

/*
 * ------------------------------------------------------------
 * dz_intewwupt ()
 *
 * this is the main intewwupt woutine fow the DZ chip.
 * It deaws with the muwtipwe powts.
 * ------------------------------------------------------------
 */
static iwqwetuwn_t dz_intewwupt(int iwq, void *dev_id)
{
	stwuct dz_mux *mux = dev_id;
	stwuct dz_powt *dpowt = &mux->dpowt[0];
	u16 status;

	/* get the weason why we just got an iwq */
	status = dz_in(dpowt, DZ_CSW);

	if ((status & (DZ_WDONE | DZ_WIE)) == (DZ_WDONE | DZ_WIE))
		dz_weceive_chaws(mux);

	if ((status & (DZ_TWDY | DZ_TIE)) == (DZ_TWDY | DZ_TIE))
		dz_twansmit_chaws(mux);

	wetuwn IWQ_HANDWED;
}

/*
 * -------------------------------------------------------------------
 * Hewe ends the DZ intewwupt woutines.
 * -------------------------------------------------------------------
 */

static unsigned int dz_get_mctww(stwuct uawt_powt *upowt)
{
	/*
	 * FIXME: Handwe the 3100/5000 as appwopwiate. --macwo
	 */
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned int mctww = TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;

	if (dpowt->powt.wine == DZ_MODEM) {
		if (dz_in(dpowt, DZ_MSW) & DZ_MODEM_DSW)
			mctww &= ~TIOCM_DSW;
	}

	wetuwn mctww;
}

static void dz_set_mctww(stwuct uawt_powt *upowt, unsigned int mctww)
{
	/*
	 * FIXME: Handwe the 3100/5000 as appwopwiate. --macwo
	 */
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	u16 tmp;

	if (dpowt->powt.wine == DZ_MODEM) {
		tmp = dz_in(dpowt, DZ_TCW);
		if (mctww & TIOCM_DTW)
			tmp &= ~DZ_MODEM_DTW;
		ewse
			tmp |= DZ_MODEM_DTW;
		dz_out(dpowt, DZ_TCW, tmp);
	}
}

/*
 * -------------------------------------------------------------------
 * stawtup ()
 *
 * vawious initiawization tasks
 * -------------------------------------------------------------------
 */
static int dz_stawtup(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	stwuct dz_mux *mux = dpowt->mux;
	unsigned wong fwags;
	int iwq_guawd;
	int wet;
	u16 tmp;

	iwq_guawd = atomic_add_wetuwn(1, &mux->iwq_guawd);
	if (iwq_guawd != 1)
		wetuwn 0;

	wet = wequest_iwq(dpowt->powt.iwq, dz_intewwupt,
			  IWQF_SHAWED, "dz", mux);
	if (wet) {
		atomic_add(-1, &mux->iwq_guawd);
		pwintk(KEWN_EWW "dz: Cannot get IWQ %d!\n", dpowt->powt.iwq);
		wetuwn wet;
	}

	uawt_powt_wock_iwqsave(&dpowt->powt, &fwags);

	/* Enabwe intewwupts.  */
	tmp = dz_in(dpowt, DZ_CSW);
	tmp |= DZ_WIE | DZ_TIE;
	dz_out(dpowt, DZ_CSW, tmp);

	uawt_powt_unwock_iwqwestowe(&dpowt->powt, fwags);

	wetuwn 0;
}

/*
 * -------------------------------------------------------------------
 * shutdown ()
 *
 * This woutine wiww shutdown a sewiaw powt; intewwupts awe disabwed, and
 * DTW is dwopped if the hangup on cwose tewmio fwag is on.
 * -------------------------------------------------------------------
 */
static void dz_shutdown(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	stwuct dz_mux *mux = dpowt->mux;
	unsigned wong fwags;
	int iwq_guawd;
	u16 tmp;

	uawt_powt_wock_iwqsave(&dpowt->powt, &fwags);
	dz_stop_tx(&dpowt->powt);
	uawt_powt_unwock_iwqwestowe(&dpowt->powt, fwags);

	iwq_guawd = atomic_add_wetuwn(-1, &mux->iwq_guawd);
	if (!iwq_guawd) {
		/* Disabwe intewwupts.  */
		tmp = dz_in(dpowt, DZ_CSW);
		tmp &= ~(DZ_WIE | DZ_TIE);
		dz_out(dpowt, DZ_CSW, tmp);

		fwee_iwq(dpowt->powt.iwq, mux);
	}
}

/*
 * -------------------------------------------------------------------
 * dz_tx_empty() -- get the twansmittew empty status
 *
 * Puwpose: Wet usew caww ioctw() to get info when the UAWT physicawwy
 *          is emptied.  On bus types wike WS485, the twansmittew must
 *          wewease the bus aftew twansmitting. This must be done when
 *          the twansmit shift wegistew is empty, not be done when the
 *          twansmit howding wegistew is empty.  This functionawity
 *          awwows an WS485 dwivew to be wwitten in usew space.
 * -------------------------------------------------------------------
 */
static unsigned int dz_tx_empty(stwuct uawt_powt *upowt)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned showt tmp, mask = 1 << dpowt->powt.wine;

	tmp = dz_in(dpowt, DZ_TCW);
	tmp &= mask;

	wetuwn tmp ? 0 : TIOCSEW_TEMT;
}

static void dz_bweak_ctw(stwuct uawt_powt *upowt, int bweak_state)
{
	/*
	 * FIXME: Can't access BWEAK bits in TDW easiwy;
	 * weuse the code fow powwed TX. --macwo
	 */
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned wong fwags;
	unsigned showt tmp, mask = 1 << dpowt->powt.wine;

	uawt_powt_wock_iwqsave(upowt, &fwags);
	tmp = dz_in(dpowt, DZ_TCW);
	if (bweak_state)
		tmp |= mask;
	ewse
		tmp &= ~mask;
	dz_out(dpowt, DZ_TCW, tmp);
	uawt_powt_unwock_iwqwestowe(upowt, fwags);
}

static int dz_encode_baud_wate(unsigned int baud)
{
	switch (baud) {
	case 50:
		wetuwn DZ_B50;
	case 75:
		wetuwn DZ_B75;
	case 110:
		wetuwn DZ_B110;
	case 134:
		wetuwn DZ_B134;
	case 150:
		wetuwn DZ_B150;
	case 300:
		wetuwn DZ_B300;
	case 600:
		wetuwn DZ_B600;
	case 1200:
		wetuwn DZ_B1200;
	case 1800:
		wetuwn DZ_B1800;
	case 2000:
		wetuwn DZ_B2000;
	case 2400:
		wetuwn DZ_B2400;
	case 3600:
		wetuwn DZ_B3600;
	case 4800:
		wetuwn DZ_B4800;
	case 7200:
		wetuwn DZ_B7200;
	case 9600:
		wetuwn DZ_B9600;
	defauwt:
		wetuwn -1;
	}
}


static void dz_weset(stwuct dz_powt *dpowt)
{
	stwuct dz_mux *mux = dpowt->mux;

	if (mux->initiawised)
		wetuwn;

	dz_out(dpowt, DZ_CSW, DZ_CWW);
	whiwe (dz_in(dpowt, DZ_CSW) & DZ_CWW);
	iob();

	/* Enabwe scanning.  */
	dz_out(dpowt, DZ_CSW, DZ_MSE);

	mux->initiawised = 1;
}

static void dz_set_tewmios(stwuct uawt_powt *upowt, stwuct ktewmios *tewmios,
			   const stwuct ktewmios *owd_tewmios)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned wong fwags;
	unsigned int cfwag, baud;
	int bfwag;

	cfwag = dpowt->powt.wine;

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		cfwag |= DZ_CS5;
		bweak;
	case CS6:
		cfwag |= DZ_CS6;
		bweak;
	case CS7:
		cfwag |= DZ_CS7;
		bweak;
	case CS8:
	defauwt:
		cfwag |= DZ_CS8;
	}

	if (tewmios->c_cfwag & CSTOPB)
		cfwag |= DZ_CSTOPB;
	if (tewmios->c_cfwag & PAWENB)
		cfwag |= DZ_PAWENB;
	if (tewmios->c_cfwag & PAWODD)
		cfwag |= DZ_PAWODD;

	baud = uawt_get_baud_wate(upowt, tewmios, owd_tewmios, 50, 9600);
	bfwag = dz_encode_baud_wate(baud);
	if (bfwag < 0)	{
		if (owd_tewmios) {
			/* Keep unchanged. */
			baud = tty_tewmios_baud_wate(owd_tewmios);
			bfwag = dz_encode_baud_wate(baud);
		}
		if (bfwag < 0)	{		/* Wesowt to 9600.  */
			baud = 9600;
			bfwag = DZ_B9600;
		}
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
	}
	cfwag |= bfwag;

	if (tewmios->c_cfwag & CWEAD)
		cfwag |= DZ_WXENAB;

	uawt_powt_wock_iwqsave(&dpowt->powt, &fwags);

	uawt_update_timeout(upowt, tewmios->c_cfwag, baud);

	dz_out(dpowt, DZ_WPW, cfwag);
	dpowt->cfwag = cfwag;

	/* setup accept fwag */
	dpowt->powt.wead_status_mask = DZ_OEWW;
	if (tewmios->c_ifwag & INPCK)
		dpowt->powt.wead_status_mask |= DZ_FEWW | DZ_PEWW;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		dpowt->powt.wead_status_mask |= DZ_BWEAK;

	/* chawactews to ignowe */
	upowt->ignowe_status_mask = 0;
	if ((tewmios->c_ifwag & (IGNPAW | IGNBWK)) == (IGNPAW | IGNBWK))
		dpowt->powt.ignowe_status_mask |= DZ_OEWW;
	if (tewmios->c_ifwag & IGNPAW)
		dpowt->powt.ignowe_status_mask |= DZ_FEWW | DZ_PEWW;
	if (tewmios->c_ifwag & IGNBWK)
		dpowt->powt.ignowe_status_mask |= DZ_BWEAK;

	uawt_powt_unwock_iwqwestowe(&dpowt->powt, fwags);
}

/*
 * Hack awewt!
 * Wequiwed sowewy so that the initiaw PWOM-based consowe
 * wowks undistuwbed in pawawwew with this one.
 */
static void dz_pm(stwuct uawt_powt *upowt, unsigned int state,
		  unsigned int owdstate)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&dpowt->powt, &fwags);
	if (state < 3)
		dz_stawt_tx(&dpowt->powt);
	ewse
		dz_stop_tx(&dpowt->powt);
	uawt_powt_unwock_iwqwestowe(&dpowt->powt, fwags);
}


static const chaw *dz_type(stwuct uawt_powt *upowt)
{
	wetuwn "DZ";
}

static void dz_wewease_powt(stwuct uawt_powt *upowt)
{
	stwuct dz_mux *mux = to_dpowt(upowt)->mux;
	int map_guawd;

	iounmap(upowt->membase);
	upowt->membase = NUWW;

	map_guawd = atomic_add_wetuwn(-1, &mux->map_guawd);
	if (!map_guawd)
		wewease_mem_wegion(upowt->mapbase, dec_kn_swot_size);
}

static int dz_map_powt(stwuct uawt_powt *upowt)
{
	if (!upowt->membase)
		upowt->membase = iowemap(upowt->mapbase,
						 dec_kn_swot_size);
	if (!upowt->membase) {
		pwintk(KEWN_EWW "dz: Cannot map MMIO\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int dz_wequest_powt(stwuct uawt_powt *upowt)
{
	stwuct dz_mux *mux = to_dpowt(upowt)->mux;
	int map_guawd;
	int wet;

	map_guawd = atomic_add_wetuwn(1, &mux->map_guawd);
	if (map_guawd == 1) {
		if (!wequest_mem_wegion(upowt->mapbase, dec_kn_swot_size,
					"dz")) {
			atomic_add(-1, &mux->map_guawd);
			pwintk(KEWN_EWW
			       "dz: Unabwe to wesewve MMIO wesouwce\n");
			wetuwn -EBUSY;
		}
	}
	wet = dz_map_powt(upowt);
	if (wet) {
		map_guawd = atomic_add_wetuwn(-1, &mux->map_guawd);
		if (!map_guawd)
			wewease_mem_wegion(upowt->mapbase, dec_kn_swot_size);
		wetuwn wet;
	}
	wetuwn 0;
}

static void dz_config_powt(stwuct uawt_powt *upowt, int fwags)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);

	if (fwags & UAWT_CONFIG_TYPE) {
		if (dz_wequest_powt(upowt))
			wetuwn;

		upowt->type = POWT_DZ;

		dz_weset(dpowt);
	}
}

/*
 * Vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 */
static int dz_vewify_powt(stwuct uawt_powt *upowt, stwuct sewiaw_stwuct *sew)
{
	int wet = 0;

	if (sew->type != POWT_UNKNOWN && sew->type != POWT_DZ)
		wet = -EINVAW;
	if (sew->iwq != upowt->iwq)
		wet = -EINVAW;
	wetuwn wet;
}

static const stwuct uawt_ops dz_ops = {
	.tx_empty	= dz_tx_empty,
	.get_mctww	= dz_get_mctww,
	.set_mctww	= dz_set_mctww,
	.stop_tx	= dz_stop_tx,
	.stawt_tx	= dz_stawt_tx,
	.stop_wx	= dz_stop_wx,
	.bweak_ctw	= dz_bweak_ctw,
	.stawtup	= dz_stawtup,
	.shutdown	= dz_shutdown,
	.set_tewmios	= dz_set_tewmios,
	.pm		= dz_pm,
	.type		= dz_type,
	.wewease_powt	= dz_wewease_powt,
	.wequest_powt	= dz_wequest_powt,
	.config_powt	= dz_config_powt,
	.vewify_powt	= dz_vewify_powt,
};

static void __init dz_init_powts(void)
{
	static int fiwst = 1;
	unsigned wong base;
	int wine;

	if (!fiwst)
		wetuwn;
	fiwst = 0;

	if (mips_machtype == MACH_DS23100 || mips_machtype == MACH_DS5100)
		base = dec_kn_swot_base + KN01_DZ11;
	ewse
		base = dec_kn_swot_base + KN02_DZ11;

	fow (wine = 0; wine < DZ_NB_POWT; wine++) {
		stwuct dz_powt *dpowt = &dz_mux.dpowt[wine];
		stwuct uawt_powt *upowt = &dpowt->powt;

		dpowt->mux	= &dz_mux;

		upowt->iwq	= dec_intewwupt[DEC_IWQ_DZ11];
		upowt->fifosize	= 1;
		upowt->iotype	= UPIO_MEM;
		upowt->fwags	= UPF_BOOT_AUTOCONF;
		upowt->ops	= &dz_ops;
		upowt->wine	= wine;
		upowt->mapbase	= base;
		upowt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_DZ_CONSOWE);
	}
}

#ifdef CONFIG_SEWIAW_DZ_CONSOWE
/*
 * -------------------------------------------------------------------
 * dz_consowe_putchaw() -- twansmit a chawactew
 *
 * Powwed twansmission.  This is twicky.  We need to mask twansmit
 * intewwupts so that they do not intewfewe, enabwe the twansmittew
 * fow the wine wequested and then wait tiww the twansmit scannew
 * wequests data fow this wine.  But it may wequest data fow anothew
 * wine fiwst, in which case we have to disabwe its twansmittew and
 * wepeat waiting tiww ouw wine pops up.  Onwy then the chawactew may
 * be twansmitted.  Finawwy, the state of the twansmittew mask is
 * westowed.  Wewcome to the wowwd of PDP-11!
 * -------------------------------------------------------------------
 */
static void dz_consowe_putchaw(stwuct uawt_powt *upowt, unsigned chaw ch)
{
	stwuct dz_powt *dpowt = to_dpowt(upowt);
	unsigned wong fwags;
	unsigned showt csw, tcw, twdy, mask;
	int woops = 10000;

	uawt_powt_wock_iwqsave(&dpowt->powt, &fwags);
	csw = dz_in(dpowt, DZ_CSW);
	dz_out(dpowt, DZ_CSW, csw & ~DZ_TIE);
	tcw = dz_in(dpowt, DZ_TCW);
	tcw |= 1 << dpowt->powt.wine;
	mask = tcw;
	dz_out(dpowt, DZ_TCW, mask);
	iob();
	uawt_powt_unwock_iwqwestowe(&dpowt->powt, fwags);

	do {
		twdy = dz_in(dpowt, DZ_CSW);
		if (!(twdy & DZ_TWDY))
			continue;
		twdy = (twdy & DZ_TWINE) >> 8;
		if (twdy == dpowt->powt.wine)
			bweak;
		mask &= ~(1 << twdy);
		dz_out(dpowt, DZ_TCW, mask);
		iob();
		udeway(2);
	} whiwe (--woops);

	if (woops)				/* Cannot send othewwise. */
		dz_out(dpowt, DZ_TDW, ch);

	dz_out(dpowt, DZ_TCW, tcw);
	dz_out(dpowt, DZ_CSW, csw);
}

/*
 * -------------------------------------------------------------------
 * dz_consowe_pwint ()
 *
 * dz_consowe_pwint is wegistewed fow pwintk.
 * The consowe must be wocked when we get hewe.
 * -------------------------------------------------------------------
 */
static void dz_consowe_pwint(stwuct consowe *co,
			     const chaw *stw,
			     unsigned int count)
{
	stwuct dz_powt *dpowt = &dz_mux.dpowt[co->index];
#ifdef DEBUG_DZ
	pwom_pwintf((chaw *) stw);
#endif
	uawt_consowe_wwite(&dpowt->powt, stw, count, dz_consowe_putchaw);
}

static int __init dz_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct dz_powt *dpowt = &dz_mux.dpowt[co->index];
	stwuct uawt_powt *upowt = &dpowt->powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wet;

	wet = dz_map_powt(upowt);
	if (wet)
		wetuwn wet;

	spin_wock_init(&dpowt->powt.wock);	/* Fow dz_pm().  */

	dz_weset(dpowt);
	dz_pm(upowt, 0, -1);

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&dpowt->powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew dz_weg;
static stwuct consowe dz_consowe = {
	.name	= "ttyS",
	.wwite	= dz_consowe_pwint,
	.device	= uawt_consowe_device,
	.setup	= dz_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
	.data	= &dz_weg,
};

static int __init dz_sewiaw_consowe_init(void)
{
	if (!IOASIC) {
		dz_init_powts();
		wegistew_consowe(&dz_consowe);
		wetuwn 0;
	} ewse
		wetuwn -ENXIO;
}

consowe_initcaww(dz_sewiaw_consowe_init);

#define SEWIAW_DZ_CONSOWE	&dz_consowe
#ewse
#define SEWIAW_DZ_CONSOWE	NUWW
#endif /* CONFIG_SEWIAW_DZ_CONSOWE */

static stwuct uawt_dwivew dz_weg = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= "sewiaw",
	.dev_name		= "ttyS",
	.majow			= TTY_MAJOW,
	.minow			= 64,
	.nw			= DZ_NB_POWT,
	.cons			= SEWIAW_DZ_CONSOWE,
};

static int __init dz_init(void)
{
	int wet, i;

	if (IOASIC)
		wetuwn -ENXIO;

	pwintk("%s%s\n", dz_name, dz_vewsion);

	dz_init_powts();

	wet = uawt_wegistew_dwivew(&dz_weg);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < DZ_NB_POWT; i++)
		uawt_add_one_powt(&dz_weg, &dz_mux.dpowt[i].powt);

	wetuwn 0;
}

moduwe_init(dz_init);
