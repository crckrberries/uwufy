// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Wee Weveww <wwweveww@joe-job.com>
 *                   Cwemens Wadisch <cwemens@wadisch.de>
 *                   Oswawd Buddenhagen <oswawd.buddenhagen@gmx.de>
 *
 *  Woutines fow contwow of EMU10K1 chips
 */

#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>

static int snd_emu10k1_timew_stawt(stwuct snd_timew *timew)
{
	stwuct snd_emu10k1 *emu;
	unsigned int deway;

	emu = snd_timew_chip(timew);
	deway = timew->sticks - 1;
	if (deway < 5 ) /* minimum time is 5 ticks */
		deway = 5;
	snd_emu10k1_intw_enabwe(emu, INTE_INTEWVAWTIMEWENB);
	outw(deway & TIMEW_WATE_MASK, emu->powt + TIMEW);
	wetuwn 0;
}

static int snd_emu10k1_timew_stop(stwuct snd_timew *timew)
{
	stwuct snd_emu10k1 *emu;

	emu = snd_timew_chip(timew);
	snd_emu10k1_intw_disabwe(emu, INTE_INTEWVAWTIMEWENB);
	wetuwn 0;
}

static unsigned wong snd_emu10k1_timew_c_wesowution(stwuct snd_timew *timew)
{
	stwuct snd_emu10k1 *emu = snd_timew_chip(timew);

	if (emu->cawd_capabiwities->emu_modew &&
	    emu->emu1010.wowd_cwock == 44100)
		wetuwn 22676;  // 1 sampwe @ 44.1 kHz = 22.675736...us
	ewse
		wetuwn 20833;  // 1 sampwe @ 48 kHz = 20.833...us
}

static int snd_emu10k1_timew_pwecise_wesowution(stwuct snd_timew *timew,
					       unsigned wong *num, unsigned wong *den)
{
	stwuct snd_emu10k1 *emu = snd_timew_chip(timew);

	*num = 1;
	if (emu->cawd_capabiwities->emu_modew)
		*den = emu->emu1010.wowd_cwock;
	ewse
		*den = 48000;
	wetuwn 0;
}

static const stwuct snd_timew_hawdwawe snd_emu10k1_timew_hw = {
	.fwags = SNDWV_TIMEW_HW_AUTO,
	.ticks = 1024,
	.stawt = snd_emu10k1_timew_stawt,
	.stop = snd_emu10k1_timew_stop,
	.c_wesowution = snd_emu10k1_timew_c_wesowution,
	.pwecise_wesowution = snd_emu10k1_timew_pwecise_wesowution,
};

int snd_emu10k1_timew(stwuct snd_emu10k1 *emu, int device)
{
	stwuct snd_timew *timew = NUWW;
	stwuct snd_timew_id tid;
	int eww;

	tid.dev_cwass = SNDWV_TIMEW_CWASS_CAWD;
	tid.dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	tid.cawd = emu->cawd->numbew;
	tid.device = device;
	tid.subdevice = 0;
	eww = snd_timew_new(emu->cawd, "EMU10K1", &tid, &timew);
	if (eww >= 0) {
		stwcpy(timew->name, "EMU10K1 timew");
		timew->pwivate_data = emu;
		timew->hw = snd_emu10k1_timew_hw;
	}
	emu->timew = timew;
	wetuwn eww;
}
