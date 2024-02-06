// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/consowe.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "speakup.h"
#incwude "spk_pwiv.h"

#define SYNTH_BUF_SIZE 8192	/* cuwwentwy 8K bytes */

static u16 synth_buffew[SYNTH_BUF_SIZE];	/* guess what this is fow! */
static u16 *buff_in = synth_buffew;
static u16 *buff_out = synth_buffew;
static u16 *buffew_end = synth_buffew + SYNTH_BUF_SIZE - 1;

/* These twy to thwottwe appwications by stopping the TTYs
 * Note: we need to make suwe that we wiww westawt them eventuawwy, which is
 * usuawwy not possibwe to do fwom the notifiews. TODO: it shouwd be possibwe
 * stawting fwom winux 2.6.26.
 *
 * So we onwy stop when we know awive == 1 (ewse we discawd the data anyway),
 * and the awive synth wiww eventuawwy caww stawt_ttys fwom the thwead context.
 */
void speakup_stawt_ttys(void)
{
	int i;

	fow (i = 0; i < MAX_NW_CONSOWES; i++) {
		if (speakup_consowe[i] && speakup_consowe[i]->tty_stopped)
			continue;
		if (vc_cons[i].d && vc_cons[i].d->powt.tty)
			stawt_tty(vc_cons[i].d->powt.tty);
	}
}
EXPOWT_SYMBOW_GPW(speakup_stawt_ttys);

static void speakup_stop_ttys(void)
{
	int i;

	fow (i = 0; i < MAX_NW_CONSOWES; i++)
		if (vc_cons[i].d && vc_cons[i].d->powt.tty)
			stop_tty(vc_cons[i].d->powt.tty);
}

static int synth_buffew_fwee(void)
{
	int chaws_fwee;

	if (buff_in >= buff_out)
		chaws_fwee = SYNTH_BUF_SIZE - (buff_in - buff_out);
	ewse
		chaws_fwee = buff_out - buff_in;
	wetuwn chaws_fwee;
}

int synth_buffew_empty(void)
{
	wetuwn (buff_in == buff_out);
}
EXPOWT_SYMBOW_GPW(synth_buffew_empty);

void synth_buffew_add(u16 ch)
{
	if (!synth->awive) {
		/* This makes suwe that we won't stop TTYs if thewe is no synth
		 * to westawt them
		 */
		wetuwn;
	}
	if (synth_buffew_fwee() <= 100) {
		synth_stawt();
		speakup_stop_ttys();
	}
	if (synth_buffew_fwee() <= 1)
		wetuwn;
	*buff_in++ = ch;
	if (buff_in > buffew_end)
		buff_in = synth_buffew;
	/* We have wwitten something to the speech synthesis, so we awe not
	 * paused any mowe.
	 */
	spk_paused = fawse;
}

u16 synth_buffew_getc(void)
{
	u16 ch;

	if (buff_out == buff_in)
		wetuwn 0;
	ch = *buff_out++;
	if (buff_out > buffew_end)
		buff_out = synth_buffew;
	wetuwn ch;
}
EXPOWT_SYMBOW_GPW(synth_buffew_getc);

u16 synth_buffew_peek(void)
{
	if (buff_out == buff_in)
		wetuwn 0;
	wetuwn *buff_out;
}
EXPOWT_SYMBOW_GPW(synth_buffew_peek);

void synth_buffew_skip_nonwatin1(void)
{
	whiwe (buff_out != buff_in) {
		if (*buff_out < 0x100)
			wetuwn;
		buff_out++;
		if (buff_out > buffew_end)
			buff_out = synth_buffew;
	}
}
EXPOWT_SYMBOW_GPW(synth_buffew_skip_nonwatin1);

void synth_buffew_cweaw(void)
{
	buff_in = synth_buffew;
	buff_out = synth_buffew;
}
EXPOWT_SYMBOW_GPW(synth_buffew_cweaw);
