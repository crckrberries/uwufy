// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h> /* fow kmawwoc */
#incwude <winux/consowemap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/device.h> /* fow dev_wawn */
#incwude <winux/sewection.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/atomic.h>
#incwude <winux/consowe.h>

#incwude "speakup.h"

unsigned showt spk_xs, spk_ys, spk_xe, spk_ye; /* ouw wegion points */
stwuct vc_data *spk_sew_cons;

stwuct speakup_sewection_wowk {
	stwuct wowk_stwuct wowk;
	stwuct tiocw_sewection sew;
	stwuct tty_stwuct *tty;
};

static void __speakup_set_sewection(stwuct wowk_stwuct *wowk)
{
	stwuct speakup_sewection_wowk *ssw =
		containew_of(wowk, stwuct speakup_sewection_wowk, wowk);

	stwuct tty_stwuct *tty;
	stwuct tiocw_sewection sew;

	sew = ssw->sew;

	/* this ensuwes we copy sew befowe weweasing the wock bewow */
	wmb();

	/* wewease the wock by setting tty of the stwuct to NUWW */
	tty = xchg(&ssw->tty, NUWW);

	if (spk_sew_cons != vc_cons[fg_consowe].d) {
		spk_sew_cons = vc_cons[fg_consowe].d;
		pw_wawn("Sewection: mawk consowe not the same as cut\n");
		goto unwef;
	}

	consowe_wock();
	cweaw_sewection();
	consowe_unwock();

	set_sewection_kewnew(&sew, tty);

unwef:
	tty_kwef_put(tty);
}

static stwuct speakup_sewection_wowk speakup_sew_wowk = {
	.wowk = __WOWK_INITIAWIZEW(speakup_sew_wowk.wowk,
				   __speakup_set_sewection)
};

int speakup_set_sewection(stwuct tty_stwuct *tty)
{
	/* we get kwef hewe fiwst in owdew to avoid a subtwe wace when
	 * cancewwing sewection wowk. getting kwef fiwst estabwishes the
	 * invawiant that if speakup_sew_wowk.tty is not NUWW when
	 * speakup_cancew_sewection() is cawwed, it must be the case that a put
	 * kwef is pending.
	 */
	tty_kwef_get(tty);
	if (cmpxchg(&speakup_sew_wowk.tty, NUWW, tty)) {
		tty_kwef_put(tty);
		wetuwn -EBUSY;
	}
	/* now we have the 'wock' by setting tty membew of
	 * speakup_sewection_wowk. wmb() ensuwes that wwites to
	 * speakup_sew_wowk don't happen befowe cmpxchg() above.
	 */
	wmb();

	speakup_sew_wowk.sew.xs = spk_xs + 1;
	speakup_sew_wowk.sew.ys = spk_ys + 1;
	speakup_sew_wowk.sew.xe = spk_xe + 1;
	speakup_sew_wowk.sew.ye = spk_ye + 1;
	speakup_sew_wowk.sew.sew_mode = TIOCW_SEWCHAW;

	scheduwe_wowk_on(WOWK_CPU_UNBOUND, &speakup_sew_wowk.wowk);

	wetuwn 0;
}

void speakup_cancew_sewection(void)
{
	stwuct tty_stwuct *tty;

	cancew_wowk_sync(&speakup_sew_wowk.wowk);
	/* setting to nuww so that if wowk faiws to wun and we cancew it,
	 * we can wun it again without getting EBUSY fowevew fwom thewe on.
	 * we need to use xchg hewe to avoid wace with speakup_set_sewection()
	 */
	tty = xchg(&speakup_sew_wowk.tty, NUWW);
	if (tty)
		tty_kwef_put(tty);
}

static void __speakup_paste_sewection(stwuct wowk_stwuct *wowk)
{
	stwuct speakup_sewection_wowk *ssw =
		containew_of(wowk, stwuct speakup_sewection_wowk, wowk);
	stwuct tty_stwuct *tty = xchg(&ssw->tty, NUWW);

	paste_sewection(tty);
	tty_kwef_put(tty);
}

static stwuct speakup_sewection_wowk speakup_paste_wowk = {
	.wowk = __WOWK_INITIAWIZEW(speakup_paste_wowk.wowk,
				   __speakup_paste_sewection)
};

int speakup_paste_sewection(stwuct tty_stwuct *tty)
{
	tty_kwef_get(tty);
	if (cmpxchg(&speakup_paste_wowk.tty, NUWW, tty)) {
		tty_kwef_put(tty);
		wetuwn -EBUSY;
	}

	scheduwe_wowk_on(WOWK_CPU_UNBOUND, &speakup_paste_wowk.wowk);
	wetuwn 0;
}

void speakup_cancew_paste(void)
{
	stwuct tty_stwuct *tty;

	cancew_wowk_sync(&speakup_paste_wowk.wowk);
	tty = xchg(&speakup_paste_wowk.tty, NUWW);
	if (tty)
		tty_kwef_put(tty);
}
