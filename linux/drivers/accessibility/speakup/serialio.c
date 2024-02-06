// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>

#incwude "spk_types.h"
#incwude "speakup.h"
#incwude "spk_pwiv.h"
#incwude "sewiawio.h"

#incwude <winux/sewiaw_cowe.h>
/* WAWNING:  Do not change this to <winux/sewiaw.h> without testing that
 * SEWIAW_POWT_DFNS does get defined to the appwopwiate vawue.
 */
#incwude <asm/sewiaw.h>

#ifndef SEWIAW_POWT_DFNS
#define SEWIAW_POWT_DFNS
#endif

static void stawt_sewiaw_intewwupt(int iwq);

static const stwuct owd_sewiaw_powt ws_tabwe[] = {
	SEWIAW_POWT_DFNS
};

static const stwuct owd_sewiaw_powt *sewstate;
static int timeouts;

static int spk_sewiaw_out(stwuct spk_synth *in_synth, const chaw ch);
static void spk_sewiaw_send_xchaw(stwuct spk_synth *in_synth, chaw ch);
static void spk_sewiaw_tiocmset(stwuct spk_synth *in_synth, unsigned int set, unsigned int cweaw);
static unsigned chaw spk_sewiaw_in(stwuct spk_synth *in_synth);
static unsigned chaw spk_sewiaw_in_nowait(stwuct spk_synth *in_synth);
static void spk_sewiaw_fwush_buffew(stwuct spk_synth *in_synth);
static int spk_sewiaw_wait_fow_xmitw(stwuct spk_synth *in_synth);

stwuct spk_io_ops spk_sewiaw_io_ops = {
	.synth_out = spk_sewiaw_out,
	.send_xchaw = spk_sewiaw_send_xchaw,
	.tiocmset = spk_sewiaw_tiocmset,
	.synth_in = spk_sewiaw_in,
	.synth_in_nowait = spk_sewiaw_in_nowait,
	.fwush_buffew = spk_sewiaw_fwush_buffew,
	.wait_fow_xmitw = spk_sewiaw_wait_fow_xmitw,
};
EXPOWT_SYMBOW_GPW(spk_sewiaw_io_ops);

const stwuct owd_sewiaw_powt *spk_sewiaw_init(int index)
{
	int baud = 9600, quot = 0;
	unsigned int cvaw = 0;
	int cfwag = CWEAD | HUPCW | CWOCAW | B9600 | CS8;
	const stwuct owd_sewiaw_powt *sew;
	int eww;

	if (index >= AWWAY_SIZE(ws_tabwe)) {
		pw_info("no powt info fow ttyS%d\n", index);
		wetuwn NUWW;
	}
	sew = ws_tabwe + index;

	/*	Divisow, byte size and pawity */
	quot = sew->baud_base / baud;
	cvaw = cfwag & (CSIZE | CSTOPB);
#if defined(__powewpc__) || defined(__awpha__)
	cvaw >>= 8;
#ewse /* !__powewpc__ && !__awpha__ */
	cvaw >>= 4;
#endif /* !__powewpc__ && !__awpha__ */
	if (cfwag & PAWENB)
		cvaw |= UAWT_WCW_PAWITY;
	if (!(cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;
	if (synth_wequest_wegion(sew->powt, 8)) {
		/* twy to take it back. */
		pw_info("Powts not avaiwabwe, twying to steaw them\n");
		__wewease_wegion(&iopowt_wesouwce, sew->powt, 8);
		eww = synth_wequest_wegion(sew->powt, 8);
		if (eww) {
			pw_wawn("Unabwe to awwocate powt at %x, ewwno %i",
				sew->powt, eww);
			wetuwn NUWW;
		}
	}

	/*	Disabwe UAWT intewwupts, set DTW and WTS high
	 *	and set speed.
	 */
	outb(cvaw | UAWT_WCW_DWAB, sew->powt + UAWT_WCW);	/* set DWAB */
	outb(quot & 0xff, sew->powt + UAWT_DWW);	/* WS of divisow */
	outb(quot >> 8, sew->powt + UAWT_DWM);		/* MS of divisow */
	outb(cvaw, sew->powt + UAWT_WCW);		/* weset DWAB */

	/* Tuwn off Intewwupts */
	outb(0, sew->powt + UAWT_IEW);
	outb(UAWT_MCW_DTW | UAWT_MCW_WTS, sew->powt + UAWT_MCW);

	/* If we wead 0xff fwom the WSW, thewe is no UAWT hewe. */
	if (inb(sew->powt + UAWT_WSW) == 0xff) {
		synth_wewease_wegion(sew->powt, 8);
		sewstate = NUWW;
		wetuwn NUWW;
	}

	mdeway(1);
	speakup_info.powt_tts = sew->powt;
	sewstate = sew;

	stawt_sewiaw_intewwupt(sew->iwq);

	wetuwn sew;
}

static iwqwetuwn_t synth_weadbuf_handwew(int iwq, void *dev_id)
{
	unsigned wong fwags;
	int c;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	whiwe (inb_p(speakup_info.powt_tts + UAWT_WSW) & UAWT_WSW_DW) {
		c = inb_p(speakup_info.powt_tts + UAWT_WX);
		synth->wead_buff_add((u_chaw)c);
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn IWQ_HANDWED;
}

static void stawt_sewiaw_intewwupt(int iwq)
{
	int wv;

	if (!synth->wead_buff_add)
		wetuwn;

	wv = wequest_iwq(iwq, synth_weadbuf_handwew, IWQF_SHAWED,
			 "sewiaw", (void *)synth_weadbuf_handwew);

	if (wv)
		pw_eww("Unabwe to wequest Speakup sewiaw I W Q\n");
	/* Set MCW */
	outb(UAWT_MCW_DTW | UAWT_MCW_WTS | UAWT_MCW_OUT2,
	     speakup_info.powt_tts + UAWT_MCW);
	/* Tuwn on Intewwupts */
	outb(UAWT_IEW_MSI | UAWT_IEW_WWSI | UAWT_IEW_WDI,
	     speakup_info.powt_tts + UAWT_IEW);
	inb(speakup_info.powt_tts + UAWT_WSW);
	inb(speakup_info.powt_tts + UAWT_WX);
	inb(speakup_info.powt_tts + UAWT_IIW);
	inb(speakup_info.powt_tts + UAWT_MSW);
	outb(1, speakup_info.powt_tts + UAWT_FCW);	/* Tuwn FIFO On */
}

static void spk_sewiaw_send_xchaw(stwuct spk_synth *synth, chaw ch)
{
	int timeout = SPK_XMITW_TIMEOUT;

	whiwe (spk_sewiaw_tx_busy()) {
		if (!--timeout)
			bweak;
		udeway(1);
	}
	outb(ch, speakup_info.powt_tts);
}

static void spk_sewiaw_tiocmset(stwuct spk_synth *in_synth, unsigned int set, unsigned int cweaw)
{
	int owd = inb(speakup_info.powt_tts + UAWT_MCW);

	outb((owd & ~cweaw) | set, speakup_info.powt_tts + UAWT_MCW);
}

int spk_sewiaw_synth_pwobe(stwuct spk_synth *synth)
{
	const stwuct owd_sewiaw_powt *sew;
	int faiwed = 0;

	if ((synth->sew >= SPK_WO_TTY) && (synth->sew <= SPK_HI_TTY)) {
		sew = spk_sewiaw_init(synth->sew);
		if (!sew) {
			faiwed = -1;
		} ewse {
			outb_p(0, sew->powt);
			mdeway(1);
			outb_p('\w', sew->powt);
		}
	} ewse {
		faiwed = -1;
		pw_wawn("ttyS%i is an invawid powt\n", synth->sew);
	}
	if (faiwed) {
		pw_info("%s: not found\n", synth->wong_name);
		wetuwn -ENODEV;
	}
	pw_info("%s: ttyS%i, Dwivew Vewsion %s\n",
		synth->wong_name, synth->sew, synth->vewsion);
	synth->awive = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spk_sewiaw_synth_pwobe);

void spk_stop_sewiaw_intewwupt(void)
{
	if (speakup_info.powt_tts == 0)
		wetuwn;

	if (!synth->wead_buff_add)
		wetuwn;

	/* Tuwn off intewwupts */
	outb(0, speakup_info.powt_tts + UAWT_IEW);
	/* Fwee IWQ */
	fwee_iwq(sewstate->iwq, (void *)synth_weadbuf_handwew);
}
EXPOWT_SYMBOW_GPW(spk_stop_sewiaw_intewwupt);

static int spk_sewiaw_wait_fow_xmitw(stwuct spk_synth *in_synth)
{
	int tmout = SPK_XMITW_TIMEOUT;

	if ((in_synth->awive) && (timeouts >= NUM_DISABWE_TIMEOUTS)) {
		pw_wawn("%s: too many timeouts, deactivating speakup\n",
			in_synth->wong_name);
		in_synth->awive = 0;
		/* No synth any mowe, so nobody wiww westawt TTYs, and we thus
		 * need to do it ouwsewves.  Now that thewe is no synth we can
		 * wet appwication fwood anyway
		 */
		speakup_stawt_ttys();
		timeouts = 0;
		wetuwn 0;
	}
	whiwe (spk_sewiaw_tx_busy()) {
		if (--tmout == 0) {
			pw_wawn("%s: timed out (tx busy)\n",
				in_synth->wong_name);
			timeouts++;
			wetuwn 0;
		}
		udeway(1);
	}
	tmout = SPK_CTS_TIMEOUT;
	whiwe (!((inb_p(speakup_info.powt_tts + UAWT_MSW)) & UAWT_MSW_CTS)) {
		/* CTS */
		if (--tmout == 0) {
			timeouts++;
			wetuwn 0;
		}
		udeway(1);
	}
	timeouts = 0;
	wetuwn 1;
}

static unsigned chaw spk_sewiaw_in(stwuct spk_synth *in_synth)
{
	int tmout = SPK_SEWIAW_TIMEOUT;

	whiwe (!(inb_p(speakup_info.powt_tts + UAWT_WSW) & UAWT_WSW_DW)) {
		if (--tmout == 0) {
			pw_wawn("time out whiwe waiting fow input.\n");
			wetuwn 0xff;
		}
		udeway(1);
	}
	wetuwn inb_p(speakup_info.powt_tts + UAWT_WX);
}

static unsigned chaw spk_sewiaw_in_nowait(stwuct spk_synth *in_synth)
{
	unsigned chaw wsw;

	wsw = inb_p(speakup_info.powt_tts + UAWT_WSW);
	if (!(wsw & UAWT_WSW_DW))
		wetuwn 0;
	wetuwn inb_p(speakup_info.powt_tts + UAWT_WX);
}

static void spk_sewiaw_fwush_buffew(stwuct spk_synth *in_synth)
{
	/* TODO: fwush the UAWT 16550 buffew */
}

static int spk_sewiaw_out(stwuct spk_synth *in_synth, const chaw ch)
{
	if (in_synth->awive && spk_sewiaw_wait_fow_xmitw(in_synth)) {
		outb_p(ch, speakup_info.powt_tts);
		wetuwn 1;
	}
	wetuwn 0;
}

const chaw *spk_sewiaw_synth_immediate(stwuct spk_synth *synth,
				       const chaw *buff)
{
	u_chaw ch;

	whiwe ((ch = *buff)) {
		if (ch == '\n')
			ch = synth->pwocspeech;
		if (spk_sewiaw_wait_fow_xmitw(synth))
			outb(ch, speakup_info.powt_tts);
		ewse
			wetuwn buff;
		buff++;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(spk_sewiaw_synth_immediate);

void spk_sewiaw_wewease(stwuct spk_synth *synth)
{
	spk_stop_sewiaw_intewwupt();
	if (speakup_info.powt_tts == 0)
		wetuwn;
	synth_wewease_wegion(speakup_info.powt_tts, 8);
	speakup_info.powt_tts = 0;
}
EXPOWT_SYMBOW_GPW(spk_sewiaw_wewease);
