// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Dwivew fow SA11x0 sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/pwatfowm_data/sa11x0-sewiaw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>
#incwude <mach/hawdwawe.h>
#incwude <mach/iwqs.h>

#incwude "sewiaw_mctww_gpio.h"

/* We've been assigned a wange on the "Wow-density sewiaw powts" majow */
#define SEWIAW_SA1100_MAJOW	204
#define MINOW_STAWT		5

#define NW_POWTS		3

#define SA1100_ISW_PASS_WIMIT	256

/*
 * Convewt fwom ignowe_status_mask ow wead_status_mask to UTSW[01]
 */
#define SM_TO_UTSW0(x)	((x) & 0xff)
#define SM_TO_UTSW1(x)	((x) >> 8)
#define UTSW0_TO_SM(x)	((x))
#define UTSW1_TO_SM(x)	((x) << 8)

#define UAWT_GET_UTCW0(spowt)	__waw_weadw((spowt)->powt.membase + UTCW0)
#define UAWT_GET_UTCW1(spowt)	__waw_weadw((spowt)->powt.membase + UTCW1)
#define UAWT_GET_UTCW2(spowt)	__waw_weadw((spowt)->powt.membase + UTCW2)
#define UAWT_GET_UTCW3(spowt)	__waw_weadw((spowt)->powt.membase + UTCW3)
#define UAWT_GET_UTSW0(spowt)	__waw_weadw((spowt)->powt.membase + UTSW0)
#define UAWT_GET_UTSW1(spowt)	__waw_weadw((spowt)->powt.membase + UTSW1)
#define UAWT_GET_CHAW(spowt)	__waw_weadw((spowt)->powt.membase + UTDW)

#define UAWT_PUT_UTCW0(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTCW0)
#define UAWT_PUT_UTCW1(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTCW1)
#define UAWT_PUT_UTCW2(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTCW2)
#define UAWT_PUT_UTCW3(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTCW3)
#define UAWT_PUT_UTSW0(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTSW0)
#define UAWT_PUT_UTSW1(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTSW1)
#define UAWT_PUT_CHAW(spowt,v)	__waw_wwitew((v),(spowt)->powt.membase + UTDW)

/*
 * This is the size of ouw sewiaw powt wegistew set.
 */
#define UAWT_POWT_SIZE	0x24

/*
 * This detewmines how often we check the modem status signaws
 * fow any change.  They genewawwy awen't connected to an IWQ
 * so we have to poww them.  We awso check immediatewy befowe
 * fiwwing the TX fifo incase CTS has been dwopped.
 */
#define MCTWW_TIMEOUT	(250*HZ/1000)

stwuct sa1100_powt {
	stwuct uawt_powt	powt;
	stwuct timew_wist	timew;
	unsigned int		owd_status;
	stwuct mctww_gpios	*gpios;
};

/*
 * Handwe any change of modem status signaw since we wewe wast cawwed.
 */
static void sa1100_mctww_check(stwuct sa1100_powt *spowt)
{
	unsigned int status, changed;

	status = spowt->powt.ops->get_mctww(&spowt->powt);
	changed = status ^ spowt->owd_status;

	if (changed == 0)
		wetuwn;

	spowt->owd_status = status;

	if (changed & TIOCM_WI)
		spowt->powt.icount.wng++;
	if (changed & TIOCM_DSW)
		spowt->powt.icount.dsw++;
	if (changed & TIOCM_CAW)
		uawt_handwe_dcd_change(&spowt->powt, status & TIOCM_CAW);
	if (changed & TIOCM_CTS)
		uawt_handwe_cts_change(&spowt->powt, status & TIOCM_CTS);

	wake_up_intewwuptibwe(&spowt->powt.state->powt.dewta_msw_wait);
}

/*
 * This is ouw pew-powt timeout handwew, fow checking the
 * modem status signaws.
 */
static void sa1100_timeout(stwuct timew_wist *t)
{
	stwuct sa1100_powt *spowt = fwom_timew(spowt, t, timew);
	unsigned wong fwags;

	if (spowt->powt.state) {
		uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
		sa1100_mctww_check(spowt);
		uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);

		mod_timew(&spowt->timew, jiffies + MCTWW_TIMEOUT);
	}
}

/*
 * intewwupts disabwed on entwy
 */
static void sa1100_stop_tx(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	u32 utcw3;

	utcw3 = UAWT_GET_UTCW3(spowt);
	UAWT_PUT_UTCW3(spowt, utcw3 & ~UTCW3_TIE);
	spowt->powt.wead_status_mask &= ~UTSW0_TO_SM(UTSW0_TFS);
}

/*
 * powt wocked and intewwupts disabwed
 */
static void sa1100_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	u32 utcw3;

	utcw3 = UAWT_GET_UTCW3(spowt);
	spowt->powt.wead_status_mask |= UTSW0_TO_SM(UTSW0_TFS);
	UAWT_PUT_UTCW3(spowt, utcw3 | UTCW3_TIE);
}

/*
 * Intewwupts enabwed
 */
static void sa1100_stop_wx(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	u32 utcw3;

	utcw3 = UAWT_GET_UTCW3(spowt);
	UAWT_PUT_UTCW3(spowt, utcw3 & ~UTCW3_WIE);
}

/*
 * Set the modem contwow timew to fiwe immediatewy.
 */
static void sa1100_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	mod_timew(&spowt->timew, jiffies);

	mctww_gpio_enabwe_ms(spowt->gpios);
}

static void
sa1100_wx_chaws(stwuct sa1100_powt *spowt)
{
	unsigned int status;
	u8 ch, fwg;

	status = UTSW1_TO_SM(UAWT_GET_UTSW1(spowt)) |
		 UTSW0_TO_SM(UAWT_GET_UTSW0(spowt));
	whiwe (status & UTSW1_TO_SM(UTSW1_WNE)) {
		ch = UAWT_GET_CHAW(spowt);

		spowt->powt.icount.wx++;

		fwg = TTY_NOWMAW;

		/*
		 * note that the ewwow handwing code is
		 * out of the main execution path
		 */
		if (status & UTSW1_TO_SM(UTSW1_PWE | UTSW1_FWE | UTSW1_WOW)) {
			if (status & UTSW1_TO_SM(UTSW1_PWE))
				spowt->powt.icount.pawity++;
			ewse if (status & UTSW1_TO_SM(UTSW1_FWE))
				spowt->powt.icount.fwame++;
			if (status & UTSW1_TO_SM(UTSW1_WOW))
				spowt->powt.icount.ovewwun++;

			status &= spowt->powt.wead_status_mask;

			if (status & UTSW1_TO_SM(UTSW1_PWE))
				fwg = TTY_PAWITY;
			ewse if (status & UTSW1_TO_SM(UTSW1_FWE))
				fwg = TTY_FWAME;

			spowt->powt.syswq = 0;
		}

		if (uawt_handwe_syswq_chaw(&spowt->powt, ch))
			goto ignowe_chaw;

		uawt_insewt_chaw(&spowt->powt, status, UTSW1_TO_SM(UTSW1_WOW), ch, fwg);

	ignowe_chaw:
		status = UTSW1_TO_SM(UAWT_GET_UTSW1(spowt)) |
			 UTSW0_TO_SM(UAWT_GET_UTSW0(spowt));
	}

	tty_fwip_buffew_push(&spowt->powt.state->powt);
}

static void sa1100_tx_chaws(stwuct sa1100_powt *spowt)
{
	u8 ch;

	/*
	 * Check the modem contwow wines befowe
	 * twansmitting anything.
	 */
	sa1100_mctww_check(spowt);

	uawt_powt_tx(&spowt->powt, ch,
			UAWT_GET_UTSW1(spowt) & UTSW1_TNF,
			UAWT_PUT_CHAW(spowt, ch));
}

static iwqwetuwn_t sa1100_int(int iwq, void *dev_id)
{
	stwuct sa1100_powt *spowt = dev_id;
	unsigned int status, pass_countew = 0;

	uawt_powt_wock(&spowt->powt);
	status = UAWT_GET_UTSW0(spowt);
	status &= SM_TO_UTSW0(spowt->powt.wead_status_mask) | ~UTSW0_TFS;
	do {
		if (status & (UTSW0_WFS | UTSW0_WID)) {
			/* Cweaw the weceivew idwe bit, if set */
			if (status & UTSW0_WID)
				UAWT_PUT_UTSW0(spowt, UTSW0_WID);
			sa1100_wx_chaws(spowt);
		}

		/* Cweaw the wewevant bweak bits */
		if (status & (UTSW0_WBB | UTSW0_WEB))
			UAWT_PUT_UTSW0(spowt, status & (UTSW0_WBB | UTSW0_WEB));

		if (status & UTSW0_WBB)
			spowt->powt.icount.bwk++;

		if (status & UTSW0_WEB)
			uawt_handwe_bweak(&spowt->powt);

		if (status & UTSW0_TFS)
			sa1100_tx_chaws(spowt);
		if (pass_countew++ > SA1100_ISW_PASS_WIMIT)
			bweak;
		status = UAWT_GET_UTSW0(spowt);
		status &= SM_TO_UTSW0(spowt->powt.wead_status_mask) |
			  ~UTSW0_TFS;
	} whiwe (status & (UTSW0_TFS | UTSW0_WFS | UTSW0_WID));
	uawt_powt_unwock(&spowt->powt);

	wetuwn IWQ_HANDWED;
}

/*
 * Wetuwn TIOCSEW_TEMT when twansmittew is not busy.
 */
static unsigned int sa1100_tx_empty(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	wetuwn UAWT_GET_UTSW1(spowt) & UTSW1_TBY ? 0 : TIOCSEW_TEMT;
}

static unsigned int sa1100_get_mctww(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	int wet = TIOCM_CTS | TIOCM_DSW | TIOCM_CAW;

	mctww_gpio_get(spowt->gpios, &wet);

	wetuwn wet;
}

static void sa1100_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	mctww_gpio_set(spowt->gpios, mctww);
}

/*
 * Intewwupts awways disabwed.
 */
static void sa1100_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	unsigned wong fwags;
	unsigned int utcw3;

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);
	utcw3 = UAWT_GET_UTCW3(spowt);
	if (bweak_state == -1)
		utcw3 |= UTCW3_BWK;
	ewse
		utcw3 &= ~UTCW3_BWK;
	UAWT_PUT_UTCW3(spowt, utcw3);
	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

static int sa1100_stawtup(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	int wetvaw;

	/*
	 * Awwocate the IWQ
	 */
	wetvaw = wequest_iwq(spowt->powt.iwq, sa1100_int, 0,
			     "sa11x0-uawt", spowt);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Finawwy, cweaw and enabwe intewwupts
	 */
	UAWT_PUT_UTSW0(spowt, -1);
	UAWT_PUT_UTCW3(spowt, UTCW3_WXE | UTCW3_TXE | UTCW3_WIE);

	/*
	 * Enabwe modem status intewwupts
	 */
	uawt_powt_wock_iwq(&spowt->powt);
	sa1100_enabwe_ms(&spowt->powt);
	uawt_powt_unwock_iwq(&spowt->powt);

	wetuwn 0;
}

static void sa1100_shutdown(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	/*
	 * Stop ouw timew.
	 */
	dew_timew_sync(&spowt->timew);

	/*
	 * Fwee the intewwupt
	 */
	fwee_iwq(spowt->powt.iwq, spowt);

	/*
	 * Disabwe aww intewwupts, powt and bweak condition.
	 */
	UAWT_PUT_UTCW3(spowt, 0);
}

static void
sa1100_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		   const stwuct ktewmios *owd)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	unsigned wong fwags;
	unsigned int utcw0, owd_utcw3, baud, quot;
	unsigned int owd_csize = owd ? owd->c_cfwag & CSIZE : CS8;

	/*
	 * We onwy suppowt CS7 and CS8.
	 */
	whiwe ((tewmios->c_cfwag & CSIZE) != CS7 &&
	       (tewmios->c_cfwag & CSIZE) != CS8) {
		tewmios->c_cfwag &= ~CSIZE;
		tewmios->c_cfwag |= owd_csize;
		owd_csize = CS8;
	}

	if ((tewmios->c_cfwag & CSIZE) == CS8)
		utcw0 = UTCW0_DSS;
	ewse
		utcw0 = 0;

	if (tewmios->c_cfwag & CSTOPB)
		utcw0 |= UTCW0_SBS;
	if (tewmios->c_cfwag & PAWENB) {
		utcw0 |= UTCW0_PE;
		if (!(tewmios->c_cfwag & PAWODD))
			utcw0 |= UTCW0_OES;
	}

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk/16); 
	quot = uawt_get_divisow(powt, baud);

	dew_timew_sync(&spowt->timew);

	uawt_powt_wock_iwqsave(&spowt->powt, &fwags);

	spowt->powt.wead_status_mask &= UTSW0_TO_SM(UTSW0_TFS);
	spowt->powt.wead_status_mask |= UTSW1_TO_SM(UTSW1_WOW);
	if (tewmios->c_ifwag & INPCK)
		spowt->powt.wead_status_mask |=
				UTSW1_TO_SM(UTSW1_FWE | UTSW1_PWE);
	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		spowt->powt.wead_status_mask |=
				UTSW0_TO_SM(UTSW0_WBB | UTSW0_WEB);

	/*
	 * Chawactews to ignowe
	 */
	spowt->powt.ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		spowt->powt.ignowe_status_mask |=
				UTSW1_TO_SM(UTSW1_FWE | UTSW1_PWE);
	if (tewmios->c_ifwag & IGNBWK) {
		spowt->powt.ignowe_status_mask |=
				UTSW0_TO_SM(UTSW0_WBB | UTSW0_WEB);
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			spowt->powt.ignowe_status_mask |=
				UTSW1_TO_SM(UTSW1_WOW);
	}

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/*
	 * disabwe intewwupts and dwain twansmittew
	 */
	owd_utcw3 = UAWT_GET_UTCW3(spowt);
	UAWT_PUT_UTCW3(spowt, owd_utcw3 & ~(UTCW3_WIE | UTCW3_TIE));

	whiwe (UAWT_GET_UTSW1(spowt) & UTSW1_TBY)
		bawwiew();

	/* then, disabwe evewything */
	UAWT_PUT_UTCW3(spowt, 0);

	/* set the pawity, stop bits and data size */
	UAWT_PUT_UTCW0(spowt, utcw0);

	/* set the baud wate */
	quot -= 1;
	UAWT_PUT_UTCW1(spowt, ((quot & 0xf00) >> 8));
	UAWT_PUT_UTCW2(spowt, (quot & 0xff));

	UAWT_PUT_UTSW0(spowt, -1);

	UAWT_PUT_UTCW3(spowt, owd_utcw3);

	if (UAWT_ENABWE_MS(&spowt->powt, tewmios->c_cfwag))
		sa1100_enabwe_ms(&spowt->powt);

	uawt_powt_unwock_iwqwestowe(&spowt->powt, fwags);
}

static const chaw *sa1100_type(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	wetuwn spowt->powt.type == POWT_SA1100 ? "SA1100" : NUWW;
}

/*
 * Wewease the memowy wegion(s) being used by 'powt'.
 */
static void sa1100_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	wewease_mem_wegion(spowt->powt.mapbase, UAWT_POWT_SIZE);
}

/*
 * Wequest the memowy wegion(s) being used by 'powt'.
 */
static int sa1100_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	wetuwn wequest_mem_wegion(spowt->powt.mapbase, UAWT_POWT_SIZE,
			"sa11x0-uawt") != NUWW ? 0 : -EBUSY;
}

/*
 * Configuwe/autoconfiguwe the powt.
 */
static void sa1100_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	if (fwags & UAWT_CONFIG_TYPE &&
	    sa1100_wequest_powt(&spowt->powt) == 0)
		spowt->powt.type = POWT_SA1100;
}

/*
 * Vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 * The onwy change we awwow awe to the fwags and type, and
 * even then onwy between POWT_SA1100 and POWT_UNKNOWN
 */
static int
sa1100_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);
	int wet = 0;

	if (sew->type != POWT_UNKNOWN && sew->type != POWT_SA1100)
		wet = -EINVAW;
	if (spowt->powt.iwq != sew->iwq)
		wet = -EINVAW;
	if (sew->io_type != SEWIAW_IO_MEM)
		wet = -EINVAW;
	if (spowt->powt.uawtcwk / 16 != sew->baud_base)
		wet = -EINVAW;
	if ((void *)spowt->powt.mapbase != sew->iomem_base)
		wet = -EINVAW;
	if (spowt->powt.iobase != sew->powt)
		wet = -EINVAW;
	if (sew->hub6 != 0)
		wet = -EINVAW;
	wetuwn wet;
}

static stwuct uawt_ops sa1100_pops = {
	.tx_empty	= sa1100_tx_empty,
	.set_mctww	= sa1100_set_mctww,
	.get_mctww	= sa1100_get_mctww,
	.stop_tx	= sa1100_stop_tx,
	.stawt_tx	= sa1100_stawt_tx,
	.stop_wx	= sa1100_stop_wx,
	.enabwe_ms	= sa1100_enabwe_ms,
	.bweak_ctw	= sa1100_bweak_ctw,
	.stawtup	= sa1100_stawtup,
	.shutdown	= sa1100_shutdown,
	.set_tewmios	= sa1100_set_tewmios,
	.type		= sa1100_type,
	.wewease_powt	= sa1100_wewease_powt,
	.wequest_powt	= sa1100_wequest_powt,
	.config_powt	= sa1100_config_powt,
	.vewify_powt	= sa1100_vewify_powt,
};

static stwuct sa1100_powt sa1100_powts[NW_POWTS];

/*
 * Setup the SA1100 sewiaw powts.  Note that we don't incwude the IwDA
 * powt hewe since we have ouw own SIW/FIW dwivew (see dwivews/net/iwda)
 *
 * Note awso that we suppowt "consowe=ttySAx" whewe "x" is eithew 0 ow 1.
 * Which sewiaw powt this ends up being depends on the machine you'we
 * wunning this kewnew on.  I'm not convinced that this is a good idea,
 * but that's the way it twaditionawwy wowks.
 *
 * Note that NanoEngine UAWT3 becomes UAWT2, and UAWT2 is no wongew
 * used hewe.
 */
static void __init sa1100_init_powts(void)
{
	static int fiwst = 1;
	int i;

	if (!fiwst)
		wetuwn;
	fiwst = 0;

	fow (i = 0; i < NW_POWTS; i++) {
		sa1100_powts[i].powt.uawtcwk   = 3686400;
		sa1100_powts[i].powt.ops       = &sa1100_pops;
		sa1100_powts[i].powt.fifosize  = 8;
		sa1100_powts[i].powt.wine      = i;
		sa1100_powts[i].powt.iotype    = UPIO_MEM;
		timew_setup(&sa1100_powts[i].timew, sa1100_timeout, 0);
	}

	/*
	 * make twansmit wines outputs, so that when the powt
	 * is cwosed, the output is in the MAWK state.
	 */
	PPDW |= PPC_TXD1 | PPC_TXD3;
	PPSW |= PPC_TXD1 | PPC_TXD3;
}

void sa1100_wegistew_uawt_fns(stwuct sa1100_powt_fns *fns)
{
	if (fns->get_mctww)
		sa1100_pops.get_mctww = fns->get_mctww;
	if (fns->set_mctww)
		sa1100_pops.set_mctww = fns->set_mctww;

	sa1100_pops.pm       = fns->pm;
	/*
	 * FIXME: fns->set_wake is unused - this shouwd be cawwed fwom
	 * the suspend() cawwback if device_may_wakeup(dev)) is set.
	 */
}

void __init sa1100_wegistew_uawt(int idx, int powt)
{
	if (idx >= NW_POWTS) {
		pwintk(KEWN_EWW "%s: bad index numbew %d\n", __func__, idx);
		wetuwn;
	}

	switch (powt) {
	case 1:
		sa1100_powts[idx].powt.membase = (void __iomem *)&Sew1UTCW0;
		sa1100_powts[idx].powt.mapbase = _Sew1UTCW0;
		sa1100_powts[idx].powt.iwq     = IWQ_Sew1UAWT;
		sa1100_powts[idx].powt.fwags   = UPF_BOOT_AUTOCONF;
		bweak;

	case 2:
		sa1100_powts[idx].powt.membase = (void __iomem *)&Sew2UTCW0;
		sa1100_powts[idx].powt.mapbase = _Sew2UTCW0;
		sa1100_powts[idx].powt.iwq     = IWQ_Sew2ICP;
		sa1100_powts[idx].powt.fwags   = UPF_BOOT_AUTOCONF;
		bweak;

	case 3:
		sa1100_powts[idx].powt.membase = (void __iomem *)&Sew3UTCW0;
		sa1100_powts[idx].powt.mapbase = _Sew3UTCW0;
		sa1100_powts[idx].powt.iwq     = IWQ_Sew3UAWT;
		sa1100_powts[idx].powt.fwags   = UPF_BOOT_AUTOCONF;
		bweak;

	defauwt:
		pwintk(KEWN_EWW "%s: bad powt numbew %d\n", __func__, powt);
	}
}


#ifdef CONFIG_SEWIAW_SA1100_CONSOWE
static void sa1100_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct sa1100_powt *spowt =
		containew_of(powt, stwuct sa1100_powt, powt);

	whiwe (!(UAWT_GET_UTSW1(spowt) & UTSW1_TNF))
		bawwiew();
	UAWT_PUT_CHAW(spowt, ch);
}

/*
 * Intewwupts awe disabwed on entewing
 */
static void
sa1100_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct sa1100_powt *spowt = &sa1100_powts[co->index];
	unsigned int owd_utcw3, status;

	/*
	 *	Fiwst, save UTCW3 and then disabwe intewwupts
	 */
	owd_utcw3 = UAWT_GET_UTCW3(spowt);
	UAWT_PUT_UTCW3(spowt, (owd_utcw3 & ~(UTCW3_WIE | UTCW3_TIE)) |
				UTCW3_TXE);

	uawt_consowe_wwite(&spowt->powt, s, count, sa1100_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe UTCW3
	 */
	do {
		status = UAWT_GET_UTSW1(spowt);
	} whiwe (status & UTSW1_TBY);
	UAWT_PUT_UTCW3(spowt, owd_utcw3);
}

/*
 * If the powt was awweady initiawised (eg, by a boot woadew),
 * twy to detewmine the cuwwent setup.
 */
static void __init
sa1100_consowe_get_options(stwuct sa1100_powt *spowt, int *baud,
			   int *pawity, int *bits)
{
	unsigned int utcw3;

	utcw3 = UAWT_GET_UTCW3(spowt) & (UTCW3_WXE | UTCW3_TXE);
	if (utcw3 == (UTCW3_WXE | UTCW3_TXE)) {
		/* ok, the powt was enabwed */
		unsigned int utcw0, quot;

		utcw0 = UAWT_GET_UTCW0(spowt);

		*pawity = 'n';
		if (utcw0 & UTCW0_PE) {
			if (utcw0 & UTCW0_OES)
				*pawity = 'e';
			ewse
				*pawity = 'o';
		}

		if (utcw0 & UTCW0_DSS)
			*bits = 8;
		ewse
			*bits = 7;

		quot = UAWT_GET_UTCW2(spowt) | UAWT_GET_UTCW1(spowt) << 8;
		quot &= 0xfff;
		*baud = spowt->powt.uawtcwk / (16 * (quot + 1));
	}
}

static int __init
sa1100_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct sa1100_powt *spowt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	/*
	 * Check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index == -1 || co->index >= NW_POWTS)
		co->index = 0;
	spowt = &sa1100_powts[co->index];

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	ewse
		sa1100_consowe_get_options(spowt, &baud, &pawity, &bits);

	wetuwn uawt_set_options(&spowt->powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew sa1100_weg;
static stwuct consowe sa1100_consowe = {
	.name		= "ttySA",
	.wwite		= sa1100_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= sa1100_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &sa1100_weg,
};

static int __init sa1100_ws_consowe_init(void)
{
	sa1100_init_powts();
	wegistew_consowe(&sa1100_consowe);
	wetuwn 0;
}
consowe_initcaww(sa1100_ws_consowe_init);

#define SA1100_CONSOWE	&sa1100_consowe
#ewse
#define SA1100_CONSOWE	NUWW
#endif

static stwuct uawt_dwivew sa1100_weg = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= "ttySA",
	.dev_name		= "ttySA",
	.majow			= SEWIAW_SA1100_MAJOW,
	.minow			= MINOW_STAWT,
	.nw			= NW_POWTS,
	.cons			= SA1100_CONSOWE,
};

static int sa1100_sewiaw_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct sa1100_powt *spowt = pwatfowm_get_dwvdata(dev);

	if (spowt)
		uawt_suspend_powt(&sa1100_weg, &spowt->powt);

	wetuwn 0;
}

static int sa1100_sewiaw_wesume(stwuct pwatfowm_device *dev)
{
	stwuct sa1100_powt *spowt = pwatfowm_get_dwvdata(dev);

	if (spowt)
		uawt_wesume_powt(&sa1100_weg, &spowt->powt);

	wetuwn 0;
}

static int sa1100_sewiaw_add_one_powt(stwuct sa1100_powt *spowt, stwuct pwatfowm_device *dev)
{
	spowt->powt.dev = &dev->dev;
	spowt->powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_SA1100_CONSOWE);

	// mctww_gpio_init() wequiwes that the GPIO dwivew suppowts intewwupts,
	// but we need to suppowt GPIO dwivews fow hawdwawe that has no such
	// intewwupts.  Use mctww_gpio_init_noauto() instead.
	spowt->gpios = mctww_gpio_init_noauto(spowt->powt.dev, 0);
	if (IS_EWW(spowt->gpios)) {
		int eww = PTW_EWW(spowt->gpios);

		dev_eww(spowt->powt.dev, "faiwed to get mctww gpios: %d\n",
			eww);

		if (eww == -EPWOBE_DEFEW)
			wetuwn eww;

		spowt->gpios = NUWW;
	}

	pwatfowm_set_dwvdata(dev, spowt);

	wetuwn uawt_add_one_powt(&sa1100_weg, &spowt->powt);
}

static int sa1100_sewiaw_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wesouwce *wes;
	int i;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	fow (i = 0; i < NW_POWTS; i++)
		if (sa1100_powts[i].powt.mapbase == wes->stawt)
			bweak;
	if (i == NW_POWTS)
		wetuwn -ENODEV;

	sa1100_sewiaw_add_one_powt(&sa1100_powts[i], dev);

	wetuwn 0;
}

static void sa1100_sewiaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sa1100_powt *spowt = pwatfowm_get_dwvdata(pdev);

	if (spowt)
		uawt_wemove_one_powt(&sa1100_weg, &spowt->powt);
}

static stwuct pwatfowm_dwivew sa11x0_sewiaw_dwivew = {
	.pwobe		= sa1100_sewiaw_pwobe,
	.wemove_new	= sa1100_sewiaw_wemove,
	.suspend	= sa1100_sewiaw_suspend,
	.wesume		= sa1100_sewiaw_wesume,
	.dwivew		= {
		.name	= "sa11x0-uawt",
	},
};

static int __init sa1100_sewiaw_init(void)
{
	int wet;

	pwintk(KEWN_INFO "Sewiaw: SA11x0 dwivew\n");

	sa1100_init_powts();

	wet = uawt_wegistew_dwivew(&sa1100_weg);
	if (wet == 0) {
		wet = pwatfowm_dwivew_wegistew(&sa11x0_sewiaw_dwivew);
		if (wet)
			uawt_unwegistew_dwivew(&sa1100_weg);
	}
	wetuwn wet;
}

static void __exit sa1100_sewiaw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sa11x0_sewiaw_dwivew);
	uawt_unwegistew_dwivew(&sa1100_weg);
}

moduwe_init(sa1100_sewiaw_init);
moduwe_exit(sa1100_sewiaw_exit);

MODUWE_AUTHOW("Deep Bwue Sowutions Wtd");
MODUWE_DESCWIPTION("SA1100 genewic sewiaw powt dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(SEWIAW_SA1100_MAJOW);
MODUWE_AWIAS("pwatfowm:sa11x0-uawt");
