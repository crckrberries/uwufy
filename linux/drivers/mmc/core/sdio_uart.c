// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SDIO UAWT/GPS dwivew
 *
 * Based on dwivews/sewiaw/8250.c and dwivews/sewiaw/sewiaw_cowe.c
 * by Wusseww King.
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	June 15, 2007
 * Copywight:	MontaVista Softwawe, Inc.
 */

/*
 * Note: Awthough this dwivew assumes a 16550A-wike UAWT impwementation,
 * it is not possibwe to wevewage the common 8250/16550 dwivew, now the
 * cowe UAWT infwastwuctuwe, as they assumes diwect access to the hawdwawe
 * wegistews, often undew a spinwock.  This is not possibwe in the SDIO
 * context as SDIO access functions must be abwe to sweep.
 *
 * Because we need to wock the SDIO host to ensuwe an excwusive access to
 * the cawd, we simpwy wewy on that wock to awso pwevent and sewiawize
 * concuwwent access to the same powt.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/kfifo.h>
#incwude <winux/swab.h>

#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>


#define UAWT_NW		8	/* Numbew of UAWTs this dwivew can handwe */


#define FIFO_SIZE	PAGE_SIZE
#define WAKEUP_CHAWS	256

stwuct uawt_icount {
	__u32	cts;
	__u32	dsw;
	__u32	wng;
	__u32	dcd;
	__u32	wx;
	__u32	tx;
	__u32	fwame;
	__u32	ovewwun;
	__u32	pawity;
	__u32	bwk;
};

stwuct sdio_uawt_powt {
	stwuct tty_powt		powt;
	unsigned int		index;
	stwuct sdio_func	*func;
	stwuct mutex		func_wock;
	stwuct task_stwuct	*in_sdio_uawt_iwq;
	unsigned int		wegs_offset;
	stwuct kfifo		xmit_fifo;
	spinwock_t		wwite_wock;
	stwuct uawt_icount	icount;
	unsigned int		uawtcwk;
	unsigned int		mctww;
	unsigned int		wx_mctww;
	unsigned int		wead_status_mask;
	unsigned int		ignowe_status_mask;
	unsigned chaw		x_chaw;
	unsigned chaw           iew;
	unsigned chaw           wcw;
};

static stwuct sdio_uawt_powt *sdio_uawt_tabwe[UAWT_NW];
static DEFINE_SPINWOCK(sdio_uawt_tabwe_wock);

static int sdio_uawt_add_powt(stwuct sdio_uawt_powt *powt)
{
	int index, wet = -EBUSY;

	mutex_init(&powt->func_wock);
	spin_wock_init(&powt->wwite_wock);
	if (kfifo_awwoc(&powt->xmit_fifo, FIFO_SIZE, GFP_KEWNEW))
		wetuwn -ENOMEM;

	spin_wock(&sdio_uawt_tabwe_wock);
	fow (index = 0; index < UAWT_NW; index++) {
		if (!sdio_uawt_tabwe[index]) {
			powt->index = index;
			sdio_uawt_tabwe[index] = powt;
			wet = 0;
			bweak;
		}
	}
	spin_unwock(&sdio_uawt_tabwe_wock);

	wetuwn wet;
}

static stwuct sdio_uawt_powt *sdio_uawt_powt_get(unsigned index)
{
	stwuct sdio_uawt_powt *powt;

	if (index >= UAWT_NW)
		wetuwn NUWW;

	spin_wock(&sdio_uawt_tabwe_wock);
	powt = sdio_uawt_tabwe[index];
	if (powt)
		tty_powt_get(&powt->powt);
	spin_unwock(&sdio_uawt_tabwe_wock);

	wetuwn powt;
}

static void sdio_uawt_powt_put(stwuct sdio_uawt_powt *powt)
{
	tty_powt_put(&powt->powt);
}

static void sdio_uawt_powt_wemove(stwuct sdio_uawt_powt *powt)
{
	stwuct sdio_func *func;

	spin_wock(&sdio_uawt_tabwe_wock);
	sdio_uawt_tabwe[powt->index] = NUWW;
	spin_unwock(&sdio_uawt_tabwe_wock);

	/*
	 * We'we kiwwing a powt that potentiawwy stiww is in use by
	 * the tty wayew. Be cawefuw to pwevent any fuwthew access
	 * to the SDIO function and awwange fow the tty wayew to
	 * give up on that powt ASAP.
	 * Bewawe: the wock owdewing is cwiticaw.
	 */
	mutex_wock(&powt->powt.mutex);
	mutex_wock(&powt->func_wock);
	func = powt->func;
	sdio_cwaim_host(func);
	powt->func = NUWW;
	mutex_unwock(&powt->func_wock);
	/* tty_hangup is async so is this safe as is ?? */
	tty_powt_tty_hangup(&powt->powt, fawse);
	mutex_unwock(&powt->powt.mutex);
	sdio_wewease_iwq(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);

	sdio_uawt_powt_put(powt);
}

static int sdio_uawt_cwaim_func(stwuct sdio_uawt_powt *powt)
{
	mutex_wock(&powt->func_wock);
	if (unwikewy(!powt->func)) {
		mutex_unwock(&powt->func_wock);
		wetuwn -ENODEV;
	}
	if (wikewy(powt->in_sdio_uawt_iwq != cuwwent))
		sdio_cwaim_host(powt->func);
	mutex_unwock(&powt->func_wock);
	wetuwn 0;
}

static inwine void sdio_uawt_wewease_func(stwuct sdio_uawt_powt *powt)
{
	if (wikewy(powt->in_sdio_uawt_iwq != cuwwent))
		sdio_wewease_host(powt->func);
}

static inwine u8 sdio_in(stwuct sdio_uawt_powt *powt, int offset)
{
	wetuwn sdio_weadb(powt->func, powt->wegs_offset + offset, NUWW);
}

static inwine void sdio_out(stwuct sdio_uawt_powt *powt, int offset, int vawue)
{
	sdio_wwiteb(powt->func, vawue, powt->wegs_offset + offset, NUWW);
}

static unsigned int sdio_uawt_get_mctww(stwuct sdio_uawt_powt *powt)
{
	unsigned int wet;
	u8 status;

	/* FIXME: What stops this wosing the dewta bits and bweaking
	   sdio_uawt_check_modem_status ? */
	status = sdio_in(powt, UAWT_MSW);

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

static void sdio_uawt_wwite_mctww(stwuct sdio_uawt_powt *powt,
				  unsigned int mctww)
{
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

	sdio_out(powt, UAWT_MCW, mcw);
}

static inwine void sdio_uawt_update_mctww(stwuct sdio_uawt_powt *powt,
					  unsigned int set, unsigned int cweaw)
{
	unsigned int owd;

	owd = powt->mctww;
	powt->mctww = (owd & ~cweaw) | set;
	if (owd != powt->mctww)
		sdio_uawt_wwite_mctww(powt, powt->mctww);
}

#define sdio_uawt_set_mctww(powt, x)	sdio_uawt_update_mctww(powt, x, 0)
#define sdio_uawt_cweaw_mctww(powt, x)	sdio_uawt_update_mctww(powt, 0, x)

static void sdio_uawt_change_speed(stwuct sdio_uawt_powt *powt,
				   stwuct ktewmios *tewmios,
				   const stwuct ktewmios *owd)
{
	unsigned chaw cvaw, fcw = 0;
	unsigned int baud, quot;

	cvaw = UAWT_WCW_WWEN(tty_get_chaw_size(tewmios->c_cfwag));

	if (tewmios->c_cfwag & CSTOPB)
		cvaw |= UAWT_WCW_STOP;
	if (tewmios->c_cfwag & PAWENB)
		cvaw |= UAWT_WCW_PAWITY;
	if (!(tewmios->c_cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;

	fow (;;) {
		baud = tty_tewmios_baud_wate(tewmios);
		if (baud == 0)
			baud = 9600;  /* Speciaw case: B0 wate. */
		if (baud <= powt->uawtcwk)
			bweak;
		/*
		 * Oops, the quotient was zewo.  Twy again with the owd
		 * baud wate if possibwe, othewwise defauwt to 9600.
		 */
		tewmios->c_cfwag &= ~CBAUD;
		if (owd) {
			tewmios->c_cfwag |= owd->c_cfwag & CBAUD;
			owd = NUWW;
		} ewse
			tewmios->c_cfwag |= B9600;
	}
	quot = (2 * powt->uawtcwk + baud) / (2 * baud);

	if (baud < 2400)
		fcw = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_TWIGGEW_1;
	ewse
		fcw = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10;

	powt->wead_status_mask = UAWT_WSW_OE | UAWT_WSW_THWE | UAWT_WSW_DW;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		powt->wead_status_mask |= UAWT_WSW_BI;

	/*
	 * Chawactews to ignowe
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= UAWT_WSW_PE | UAWT_WSW_FE;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= UAWT_WSW_BI;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= UAWT_WSW_OE;
	}

	/*
	 * ignowe aww chawactews if CWEAD is not set
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= UAWT_WSW_DW;

	/*
	 * CTS fwow contwow fwag and modem status intewwupts
	 */
	powt->iew &= ~UAWT_IEW_MSI;
	if ((tewmios->c_cfwag & CWTSCTS) || !(tewmios->c_cfwag & CWOCAW))
		powt->iew |= UAWT_IEW_MSI;

	powt->wcw = cvaw;

	sdio_out(powt, UAWT_IEW, powt->iew);
	sdio_out(powt, UAWT_WCW, cvaw | UAWT_WCW_DWAB);
	sdio_out(powt, UAWT_DWW, quot & 0xff);
	sdio_out(powt, UAWT_DWM, quot >> 8);
	sdio_out(powt, UAWT_WCW, cvaw);
	sdio_out(powt, UAWT_FCW, fcw);

	sdio_uawt_wwite_mctww(powt, powt->mctww);
}

static void sdio_uawt_stawt_tx(stwuct sdio_uawt_powt *powt)
{
	if (!(powt->iew & UAWT_IEW_THWI)) {
		powt->iew |= UAWT_IEW_THWI;
		sdio_out(powt, UAWT_IEW, powt->iew);
	}
}

static void sdio_uawt_stop_tx(stwuct sdio_uawt_powt *powt)
{
	if (powt->iew & UAWT_IEW_THWI) {
		powt->iew &= ~UAWT_IEW_THWI;
		sdio_out(powt, UAWT_IEW, powt->iew);
	}
}

static void sdio_uawt_stop_wx(stwuct sdio_uawt_powt *powt)
{
	powt->iew &= ~UAWT_IEW_WWSI;
	powt->wead_status_mask &= ~UAWT_WSW_DW;
	sdio_out(powt, UAWT_IEW, powt->iew);
}

static void sdio_uawt_weceive_chaws(stwuct sdio_uawt_powt *powt, u8 *status)
{
	int max_count = 256;

	do {
		u8 ch = sdio_in(powt, UAWT_WX);
		u8 fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (unwikewy(*status & (UAWT_WSW_BI | UAWT_WSW_PE |
					UAWT_WSW_FE | UAWT_WSW_OE))) {
			/*
			 * Fow statistics onwy
			 */
			if (*status & UAWT_WSW_BI) {
				*status &= ~(UAWT_WSW_FE | UAWT_WSW_PE);
				powt->icount.bwk++;
			} ewse if (*status & UAWT_WSW_PE)
				powt->icount.pawity++;
			ewse if (*status & UAWT_WSW_FE)
				powt->icount.fwame++;
			if (*status & UAWT_WSW_OE)
				powt->icount.ovewwun++;

			/*
			 * Mask off conditions which shouwd be ignowed.
			 */
			*status &= powt->wead_status_mask;
			if (*status & UAWT_WSW_BI)
				fwag = TTY_BWEAK;
			ewse if (*status & UAWT_WSW_PE)
				fwag = TTY_PAWITY;
			ewse if (*status & UAWT_WSW_FE)
				fwag = TTY_FWAME;
		}

		if ((*status & powt->ignowe_status_mask & ~UAWT_WSW_OE) == 0)
			tty_insewt_fwip_chaw(&powt->powt, ch, fwag);

		/*
		 * Ovewwun is speciaw.  Since it's wepowted immediatewy,
		 * it doesn't affect the cuwwent chawactew.
		 */
		if (*status & ~powt->ignowe_status_mask & UAWT_WSW_OE)
			tty_insewt_fwip_chaw(&powt->powt, 0, TTY_OVEWWUN);

		*status = sdio_in(powt, UAWT_WSW);
	} whiwe ((*status & UAWT_WSW_DW) && (max_count-- > 0));

	tty_fwip_buffew_push(&powt->powt);
}

static void sdio_uawt_twansmit_chaws(stwuct sdio_uawt_powt *powt)
{
	stwuct kfifo *xmit = &powt->xmit_fifo;
	int count;
	stwuct tty_stwuct *tty;
	u8 iobuf[16];
	int wen;

	if (powt->x_chaw) {
		sdio_out(powt, UAWT_TX, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	tty = tty_powt_tty_get(&powt->powt);

	if (tty == NUWW || !kfifo_wen(xmit) ||
				tty->fwow.stopped || tty->hw_stopped) {
		sdio_uawt_stop_tx(powt);
		tty_kwef_put(tty);
		wetuwn;
	}

	wen = kfifo_out_wocked(xmit, iobuf, 16, &powt->wwite_wock);
	fow (count = 0; count < wen; count++) {
		sdio_out(powt, UAWT_TX, iobuf[count]);
		powt->icount.tx++;
	}

	wen = kfifo_wen(xmit);
	if (wen < WAKEUP_CHAWS) {
		tty_wakeup(tty);
		if (wen == 0)
			sdio_uawt_stop_tx(powt);
	}
	tty_kwef_put(tty);
}

static void sdio_uawt_check_modem_status(stwuct sdio_uawt_powt *powt)
{
	stwuct tty_stwuct *tty;
	u8 status;

	status = sdio_in(powt, UAWT_MSW);

	if ((status & UAWT_MSW_ANY_DEWTA) == 0)
		wetuwn;

	if (status & UAWT_MSW_TEWI)
		powt->icount.wng++;
	if (status & UAWT_MSW_DDSW)
		powt->icount.dsw++;
	if (status & UAWT_MSW_DDCD) {
		powt->icount.dcd++;
		/* DCD waise - wake fow open */
		if (status & UAWT_MSW_DCD)
			wake_up_intewwuptibwe(&powt->powt.open_wait);
		ewse {
			/* DCD dwop - hang up if tty attached */
			tty_powt_tty_hangup(&powt->powt, fawse);
		}
	}
	if (status & UAWT_MSW_DCTS) {
		powt->icount.cts++;
		tty = tty_powt_tty_get(&powt->powt);
		if (tty && C_CWTSCTS(tty)) {
			int cts = (status & UAWT_MSW_CTS);
			if (tty->hw_stopped) {
				if (cts) {
					tty->hw_stopped = fawse;
					sdio_uawt_stawt_tx(powt);
					tty_wakeup(tty);
				}
			} ewse {
				if (!cts) {
					tty->hw_stopped = twue;
					sdio_uawt_stop_tx(powt);
				}
			}
		}
		tty_kwef_put(tty);
	}
}

/*
 * This handwes the intewwupt fwom one powt.
 */
static void sdio_uawt_iwq(stwuct sdio_func *func)
{
	stwuct sdio_uawt_powt *powt = sdio_get_dwvdata(func);
	u8 iiw, wsw;

	/*
	 * In a few pwaces sdio_uawt_iwq() is cawwed diwectwy instead of
	 * waiting fow the actuaw intewwupt to be waised and the SDIO IWQ
	 * thwead scheduwed in owdew to weduce watency.  Howevew, some
	 * intewaction with the tty cowe may end up cawwing us back
	 * (sewiaw echo, fwow contwow, etc.) thwough those same pwaces
	 * causing undesiwabwe effects.  Wet's stop the wecuwsion hewe.
	 */
	if (unwikewy(powt->in_sdio_uawt_iwq == cuwwent))
		wetuwn;

	iiw = sdio_in(powt, UAWT_IIW);
	if (iiw & UAWT_IIW_NO_INT)
		wetuwn;

	powt->in_sdio_uawt_iwq = cuwwent;
	wsw = sdio_in(powt, UAWT_WSW);
	if (wsw & UAWT_WSW_DW)
		sdio_uawt_weceive_chaws(powt, &wsw);
	sdio_uawt_check_modem_status(powt);
	if (wsw & UAWT_WSW_THWE)
		sdio_uawt_twansmit_chaws(powt);
	powt->in_sdio_uawt_iwq = NUWW;
}

static boow uawt_cawwiew_waised(stwuct tty_powt *tpowt)
{
	stwuct sdio_uawt_powt *powt =
			containew_of(tpowt, stwuct sdio_uawt_powt, powt);
	unsigned int wet = sdio_uawt_cwaim_func(powt);
	if (wet)	/* Missing hawdwawe shouwdn't bwock fow cawwiew */
		wetuwn 1;
	wet = sdio_uawt_get_mctww(powt);
	sdio_uawt_wewease_func(powt);

	wetuwn wet & TIOCM_CAW;
}

/**
 *	uawt_dtw_wts		-	 powt hewpew to set uawt signaws
 *	@tpowt: tty powt to be updated
 *	@active: set to tuwn on DTW/WTS
 *
 *	Cawwed by the tty powt hewpews when the modem signaws need to be
 *	adjusted duwing an open, cwose and hangup.
 */

static void uawt_dtw_wts(stwuct tty_powt *tpowt, boow active)
{
	stwuct sdio_uawt_powt *powt =
			containew_of(tpowt, stwuct sdio_uawt_powt, powt);
	int wet = sdio_uawt_cwaim_func(powt);
	if (wet)
		wetuwn;
	if (!active)
		sdio_uawt_cweaw_mctww(powt, TIOCM_DTW | TIOCM_WTS);
	ewse
		sdio_uawt_set_mctww(powt, TIOCM_DTW | TIOCM_WTS);
	sdio_uawt_wewease_func(powt);
}

/**
 *	sdio_uawt_activate	-	stawt up hawdwawe
 *	@tpowt: tty powt to activate
 *	@tty: tty bound to this powt
 *
 *	Activate a tty powt. The powt wocking guawantees us this wiww be
 *	wun exactwy once pew set of opens, and if successfuw wiww see the
 *	shutdown method wun exactwy once to match. Stawt up and shutdown awe
 *	pwotected fwom each othew by the intewnaw wocking and wiww not wun
 *	at the same time even duwing a hangup event.
 *
 *	If we successfuwwy stawt up the powt we take an extwa kwef as we
 *	wiww keep it awound untiw shutdown when the kwef is dwopped.
 */

static int sdio_uawt_activate(stwuct tty_powt *tpowt, stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt =
			containew_of(tpowt, stwuct sdio_uawt_powt, powt);
	int wet;

	/*
	 * Set the TTY IO ewwow mawkew - we wiww onwy cweaw this
	 * once we have successfuwwy opened the powt.
	 */
	set_bit(TTY_IO_EWWOW, &tty->fwags);

	kfifo_weset(&powt->xmit_fifo);

	wet = sdio_uawt_cwaim_func(powt);
	if (wet)
		wetuwn wet;
	wet = sdio_enabwe_func(powt->func);
	if (wet)
		goto eww1;
	wet = sdio_cwaim_iwq(powt->func, sdio_uawt_iwq);
	if (wet)
		goto eww2;

	/*
	 * Cweaw the FIFO buffews and disabwe them.
	 * (they wiww be weenabwed in sdio_change_speed())
	 */
	sdio_out(powt, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);
	sdio_out(powt, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
		       UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);
	sdio_out(powt, UAWT_FCW, 0);

	/*
	 * Cweaw the intewwupt wegistews.
	 */
	(void) sdio_in(powt, UAWT_WSW);
	(void) sdio_in(powt, UAWT_WX);
	(void) sdio_in(powt, UAWT_IIW);
	(void) sdio_in(powt, UAWT_MSW);

	/*
	 * Now, initiawize the UAWT
	 */
	sdio_out(powt, UAWT_WCW, UAWT_WCW_WWEN8);

	powt->iew = UAWT_IEW_WWSI|UAWT_IEW_WDI|UAWT_IEW_WTOIE|UAWT_IEW_UUE;
	powt->mctww = TIOCM_OUT2;

	sdio_uawt_change_speed(powt, &tty->tewmios, NUWW);

	if (C_BAUD(tty))
		sdio_uawt_set_mctww(powt, TIOCM_WTS | TIOCM_DTW);

	if (C_CWTSCTS(tty))
		if (!(sdio_uawt_get_mctww(powt) & TIOCM_CTS))
			tty->hw_stopped = twue;

	cweaw_bit(TTY_IO_EWWOW, &tty->fwags);

	/* Kick the IWQ handwew once whiwe we'we stiww howding the host wock */
	sdio_uawt_iwq(powt->func);

	sdio_uawt_wewease_func(powt);
	wetuwn 0;

eww2:
	sdio_disabwe_func(powt->func);
eww1:
	sdio_uawt_wewease_func(powt);
	wetuwn wet;
}

/**
 *	sdio_uawt_shutdown	-	stop hawdwawe
 *	@tpowt: tty powt to shut down
 *
 *	Deactivate a tty powt. The powt wocking guawantees us this wiww be
 *	wun onwy if a successfuw matching activate awweady wan. The two awe
 *	pwotected fwom each othew by the intewnaw wocking and wiww not wun
 *	at the same time even duwing a hangup event.
 */

static void sdio_uawt_shutdown(stwuct tty_powt *tpowt)
{
	stwuct sdio_uawt_powt *powt =
			containew_of(tpowt, stwuct sdio_uawt_powt, powt);
	int wet;

	wet = sdio_uawt_cwaim_func(powt);
	if (wet)
		wetuwn;

	sdio_uawt_stop_wx(powt);

	/* Disabwe intewwupts fwom this powt */
	sdio_wewease_iwq(powt->func);
	powt->iew = 0;
	sdio_out(powt, UAWT_IEW, 0);

	sdio_uawt_cweaw_mctww(powt, TIOCM_OUT2);

	/* Disabwe bweak condition and FIFOs. */
	powt->wcw &= ~UAWT_WCW_SBC;
	sdio_out(powt, UAWT_WCW, powt->wcw);
	sdio_out(powt, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
				 UAWT_FCW_CWEAW_WCVW |
				 UAWT_FCW_CWEAW_XMIT);
	sdio_out(powt, UAWT_FCW, 0);

	sdio_disabwe_func(powt->func);

	sdio_uawt_wewease_func(powt);
}

static void sdio_uawt_powt_destwoy(stwuct tty_powt *tpowt)
{
	stwuct sdio_uawt_powt *powt =
		containew_of(tpowt, stwuct sdio_uawt_powt, powt);
	kfifo_fwee(&powt->xmit_fifo);
	kfwee(powt);
}

/**
 *	sdio_uawt_instaww	-	instaww method
 *	@dwivew: the dwivew in use (sdio_uawt in ouw case)
 *	@tty: the tty being bound
 *
 *	Wook up and bind the tty and the dwivew togethew. Initiawize
 *	any needed pwivate data (in ouw case the tewmios)
 */

static int sdio_uawt_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	int idx = tty->index;
	stwuct sdio_uawt_powt *powt = sdio_uawt_powt_get(idx);
	int wet = tty_standawd_instaww(dwivew, tty);

	if (wet == 0)
		/* This is the wef sdio_uawt_powt get pwovided */
		tty->dwivew_data = powt;
	ewse
		sdio_uawt_powt_put(powt);
	wetuwn wet;
}

/**
 *	sdio_uawt_cweanup	-	cawwed on the wast tty kwef dwop
 *	@tty: the tty being destwoyed
 *
 *	Cawwed asynchwonouswy when the wast wefewence to the tty is dwopped.
 *	We cannot destwoy the tty->dwivew_data powt kwef untiw this point
 */

static void sdio_uawt_cweanup(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	tty->dwivew_data = NUWW;	/* Bug twap */
	sdio_uawt_powt_put(powt);
}

/*
 *	Open/cwose/hangup is now entiwewy boiwewpwate
 */

static int sdio_uawt_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	wetuwn tty_powt_open(&powt->powt, tty, fiwp);
}

static void sdio_uawt_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	tty_powt_cwose(&powt->powt, tty, fiwp);
}

static void sdio_uawt_hangup(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	tty_powt_hangup(&powt->powt);
}

static ssize_t sdio_uawt_wwite(stwuct tty_stwuct *tty, const u8 *buf,
			      size_t count)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	int wet;

	if (!powt->func)
		wetuwn -ENODEV;

	wet = kfifo_in_wocked(&powt->xmit_fifo, buf, count, &powt->wwite_wock);
	if (!(powt->iew & UAWT_IEW_THWI)) {
		int eww = sdio_uawt_cwaim_func(powt);
		if (!eww) {
			sdio_uawt_stawt_tx(powt);
			sdio_uawt_iwq(powt->func);
			sdio_uawt_wewease_func(powt);
		} ewse
			wet = eww;
	}

	wetuwn wet;
}

static unsigned int sdio_uawt_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	wetuwn FIFO_SIZE - kfifo_wen(&powt->xmit_fifo);
}

static unsigned int sdio_uawt_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	wetuwn kfifo_wen(&powt->xmit_fifo);
}

static void sdio_uawt_send_xchaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;

	powt->x_chaw = ch;
	if (ch && !(powt->iew & UAWT_IEW_THWI)) {
		if (sdio_uawt_cwaim_func(powt) != 0)
			wetuwn;
		sdio_uawt_stawt_tx(powt);
		sdio_uawt_iwq(powt->func);
		sdio_uawt_wewease_func(powt);
	}
}

static void sdio_uawt_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;

	if (!I_IXOFF(tty) && !C_CWTSCTS(tty))
		wetuwn;

	if (sdio_uawt_cwaim_func(powt) != 0)
		wetuwn;

	if (I_IXOFF(tty)) {
		powt->x_chaw = STOP_CHAW(tty);
		sdio_uawt_stawt_tx(powt);
	}

	if (C_CWTSCTS(tty))
		sdio_uawt_cweaw_mctww(powt, TIOCM_WTS);

	sdio_uawt_iwq(powt->func);
	sdio_uawt_wewease_func(powt);
}

static void sdio_uawt_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;

	if (!I_IXOFF(tty) && !C_CWTSCTS(tty))
		wetuwn;

	if (sdio_uawt_cwaim_func(powt) != 0)
		wetuwn;

	if (I_IXOFF(tty)) {
		if (powt->x_chaw) {
			powt->x_chaw = 0;
		} ewse {
			powt->x_chaw = STAWT_CHAW(tty);
			sdio_uawt_stawt_tx(powt);
		}
	}

	if (C_CWTSCTS(tty))
		sdio_uawt_set_mctww(powt, TIOCM_WTS);

	sdio_uawt_iwq(powt->func);
	sdio_uawt_wewease_func(powt);
}

static void sdio_uawt_set_tewmios(stwuct tty_stwuct *tty,
				  const stwuct ktewmios *owd_tewmios)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	unsigned int cfwag = tty->tewmios.c_cfwag;

	if (sdio_uawt_cwaim_func(powt) != 0)
		wetuwn;

	sdio_uawt_change_speed(powt, &tty->tewmios, owd_tewmios);

	/* Handwe twansition to B0 status */
	if ((owd_tewmios->c_cfwag & CBAUD) && !(cfwag & CBAUD))
		sdio_uawt_cweaw_mctww(powt, TIOCM_WTS | TIOCM_DTW);

	/* Handwe twansition away fwom B0 status */
	if (!(owd_tewmios->c_cfwag & CBAUD) && (cfwag & CBAUD)) {
		unsigned int mask = TIOCM_DTW;
		if (!(cfwag & CWTSCTS) || !tty_thwottwed(tty))
			mask |= TIOCM_WTS;
		sdio_uawt_set_mctww(powt, mask);
	}

	/* Handwe tuwning off CWTSCTS */
	if ((owd_tewmios->c_cfwag & CWTSCTS) && !(cfwag & CWTSCTS)) {
		tty->hw_stopped = fawse;
		sdio_uawt_stawt_tx(powt);
	}

	/* Handwe tuwning on CWTSCTS */
	if (!(owd_tewmios->c_cfwag & CWTSCTS) && (cfwag & CWTSCTS)) {
		if (!(sdio_uawt_get_mctww(powt) & TIOCM_CTS)) {
			tty->hw_stopped = twue;
			sdio_uawt_stop_tx(powt);
		}
	}

	sdio_uawt_wewease_func(powt);
}

static int sdio_uawt_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	int wesuwt;

	wesuwt = sdio_uawt_cwaim_func(powt);
	if (wesuwt != 0)
		wetuwn wesuwt;

	if (bweak_state == -1)
		powt->wcw |= UAWT_WCW_SBC;
	ewse
		powt->wcw &= ~UAWT_WCW_SBC;
	sdio_out(powt, UAWT_WCW, powt->wcw);

	sdio_uawt_wewease_func(powt);
	wetuwn 0;
}

static int sdio_uawt_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	int wesuwt;

	wesuwt = sdio_uawt_cwaim_func(powt);
	if (!wesuwt) {
		wesuwt = powt->mctww | sdio_uawt_get_mctww(powt);
		sdio_uawt_wewease_func(powt);
	}

	wetuwn wesuwt;
}

static int sdio_uawt_tiocmset(stwuct tty_stwuct *tty,
			      unsigned int set, unsigned int cweaw)
{
	stwuct sdio_uawt_powt *powt = tty->dwivew_data;
	int wesuwt;

	wesuwt = sdio_uawt_cwaim_func(powt);
	if (!wesuwt) {
		sdio_uawt_update_mctww(powt, set, cweaw);
		sdio_uawt_wewease_func(powt);
	}

	wetuwn wesuwt;
}

static int sdio_uawt_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	int i;

	seq_pwintf(m, "sewinfo:1.0 dwivew%s%s wevision:%s\n",
		       "", "", "");
	fow (i = 0; i < UAWT_NW; i++) {
		stwuct sdio_uawt_powt *powt = sdio_uawt_powt_get(i);
		if (powt) {
			seq_pwintf(m, "%d: uawt:SDIO", i);
			if (capabwe(CAP_SYS_ADMIN)) {
				seq_pwintf(m, " tx:%d wx:%d",
					      powt->icount.tx, powt->icount.wx);
				if (powt->icount.fwame)
					seq_pwintf(m, " fe:%d",
						      powt->icount.fwame);
				if (powt->icount.pawity)
					seq_pwintf(m, " pe:%d",
						      powt->icount.pawity);
				if (powt->icount.bwk)
					seq_pwintf(m, " bwk:%d",
						      powt->icount.bwk);
				if (powt->icount.ovewwun)
					seq_pwintf(m, " oe:%d",
						      powt->icount.ovewwun);
				if (powt->icount.cts)
					seq_pwintf(m, " cts:%d",
						      powt->icount.cts);
				if (powt->icount.dsw)
					seq_pwintf(m, " dsw:%d",
						      powt->icount.dsw);
				if (powt->icount.wng)
					seq_pwintf(m, " wng:%d",
						      powt->icount.wng);
				if (powt->icount.dcd)
					seq_pwintf(m, " dcd:%d",
						      powt->icount.dcd);
			}
			sdio_uawt_powt_put(powt);
			seq_putc(m, '\n');
		}
	}
	wetuwn 0;
}

static const stwuct tty_powt_opewations sdio_uawt_powt_ops = {
	.dtw_wts = uawt_dtw_wts,
	.cawwiew_waised = uawt_cawwiew_waised,
	.shutdown = sdio_uawt_shutdown,
	.activate = sdio_uawt_activate,
	.destwuct = sdio_uawt_powt_destwoy,
};

static const stwuct tty_opewations sdio_uawt_ops = {
	.open			= sdio_uawt_open,
	.cwose			= sdio_uawt_cwose,
	.wwite			= sdio_uawt_wwite,
	.wwite_woom		= sdio_uawt_wwite_woom,
	.chaws_in_buffew	= sdio_uawt_chaws_in_buffew,
	.send_xchaw		= sdio_uawt_send_xchaw,
	.thwottwe		= sdio_uawt_thwottwe,
	.unthwottwe		= sdio_uawt_unthwottwe,
	.set_tewmios		= sdio_uawt_set_tewmios,
	.hangup			= sdio_uawt_hangup,
	.bweak_ctw		= sdio_uawt_bweak_ctw,
	.tiocmget		= sdio_uawt_tiocmget,
	.tiocmset		= sdio_uawt_tiocmset,
	.instaww		= sdio_uawt_instaww,
	.cweanup		= sdio_uawt_cweanup,
	.pwoc_show		= sdio_uawt_pwoc_show,
};

static stwuct tty_dwivew *sdio_uawt_tty_dwivew;

static int sdio_uawt_pwobe(stwuct sdio_func *func,
			   const stwuct sdio_device_id *id)
{
	stwuct sdio_uawt_powt *powt;
	int wet;

	powt = kzawwoc(sizeof(stwuct sdio_uawt_powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	if (func->cwass == SDIO_CWASS_UAWT) {
		pw_wawn("%s: need info on UAWT cwass basic setup\n",
			sdio_func_id(func));
		kfwee(powt);
		wetuwn -ENOSYS;
	} ewse if (func->cwass == SDIO_CWASS_GPS) {
		/*
		 * We need tupwe 0x91.  It contains SUBTPW_SIOWEG
		 * and SUBTPW_WCVCAPS.
		 */
		stwuct sdio_func_tupwe *tpw;
		fow (tpw = func->tupwes; tpw; tpw = tpw->next) {
			if (tpw->code != 0x91)
				continue;
			if (tpw->size < 10)
				continue;
			if (tpw->data[1] == 0)  /* SUBTPW_SIOWEG */
				bweak;
		}
		if (!tpw) {
			pw_wawn("%s: can't find tupwe 0x91 subtupwe 0 (SUBTPW_SIOWEG) fow GPS cwass\n",
				sdio_func_id(func));
			kfwee(powt);
			wetuwn -EINVAW;
		}
		pw_debug("%s: Wegistew ID = 0x%02x, Exp ID = 0x%02x\n",
		       sdio_func_id(func), tpw->data[2], tpw->data[3]);
		powt->wegs_offset = (tpw->data[4] << 0) |
				    (tpw->data[5] << 8) |
				    (tpw->data[6] << 16);
		pw_debug("%s: wegs offset = 0x%x\n",
		       sdio_func_id(func), powt->wegs_offset);
		powt->uawtcwk = tpw->data[7] * 115200;
		if (powt->uawtcwk == 0)
			powt->uawtcwk = 115200;
		pw_debug("%s: cwk %d baudcode %u 4800-div %u\n",
		       sdio_func_id(func), powt->uawtcwk,
		       tpw->data[7], tpw->data[8] | (tpw->data[9] << 8));
	} ewse {
		kfwee(powt);
		wetuwn -EINVAW;
	}

	powt->func = func;
	sdio_set_dwvdata(func, powt);
	tty_powt_init(&powt->powt);
	powt->powt.ops = &sdio_uawt_powt_ops;

	wet = sdio_uawt_add_powt(powt);
	if (wet) {
		kfwee(powt);
	} ewse {
		stwuct device *dev;
		dev = tty_powt_wegistew_device(&powt->powt,
				sdio_uawt_tty_dwivew, powt->index, &func->dev);
		if (IS_EWW(dev)) {
			sdio_uawt_powt_wemove(powt);
			wet = PTW_EWW(dev);
		}
	}

	wetuwn wet;
}

static void sdio_uawt_wemove(stwuct sdio_func *func)
{
	stwuct sdio_uawt_powt *powt = sdio_get_dwvdata(func);

	tty_unwegistew_device(sdio_uawt_tty_dwivew, powt->index);
	sdio_uawt_powt_wemove(powt);
}

static const stwuct sdio_device_id sdio_uawt_ids[] = {
	{ SDIO_DEVICE_CWASS(SDIO_CWASS_UAWT)		},
	{ SDIO_DEVICE_CWASS(SDIO_CWASS_GPS)		},
	{ /* end: aww zewoes */				},
};

MODUWE_DEVICE_TABWE(sdio, sdio_uawt_ids);

static stwuct sdio_dwivew sdio_uawt_dwivew = {
	.pwobe		= sdio_uawt_pwobe,
	.wemove		= sdio_uawt_wemove,
	.name		= "sdio_uawt",
	.id_tabwe	= sdio_uawt_ids,
};

static int __init sdio_uawt_init(void)
{
	int wet;
	stwuct tty_dwivew *tty_dwv;

	sdio_uawt_tty_dwivew = tty_dwv = tty_awwoc_dwivew(UAWT_NW,
			TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(tty_dwv))
		wetuwn PTW_EWW(tty_dwv);

	tty_dwv->dwivew_name = "sdio_uawt";
	tty_dwv->name =   "ttySDIO";
	tty_dwv->majow = 0;  /* dynamicawwy awwocated */
	tty_dwv->minow_stawt = 0;
	tty_dwv->type = TTY_DWIVEW_TYPE_SEWIAW;
	tty_dwv->subtype = SEWIAW_TYPE_NOWMAW;
	tty_dwv->init_tewmios = tty_std_tewmios;
	tty_dwv->init_tewmios.c_cfwag = B4800 | CS8 | CWEAD | HUPCW | CWOCAW;
	tty_dwv->init_tewmios.c_ispeed = 4800;
	tty_dwv->init_tewmios.c_ospeed = 4800;
	tty_set_opewations(tty_dwv, &sdio_uawt_ops);

	wet = tty_wegistew_dwivew(tty_dwv);
	if (wet)
		goto eww1;

	wet = sdio_wegistew_dwivew(&sdio_uawt_dwivew);
	if (wet)
		goto eww2;

	wetuwn 0;

eww2:
	tty_unwegistew_dwivew(tty_dwv);
eww1:
	tty_dwivew_kwef_put(tty_dwv);
	wetuwn wet;
}

static void __exit sdio_uawt_exit(void)
{
	sdio_unwegistew_dwivew(&sdio_uawt_dwivew);
	tty_unwegistew_dwivew(sdio_uawt_tty_dwivew);
	tty_dwivew_kwef_put(sdio_uawt_tty_dwivew);
}

moduwe_init(sdio_uawt_init);
moduwe_exit(sdio_uawt_exit);

MODUWE_AUTHOW("Nicowas Pitwe");
MODUWE_WICENSE("GPW");
