// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Pwoc intewface fow Emu8k/Emu10k1 WaveTabwe synth
 */

#incwude <winux/wait.h>
#incwude <sound/cowe.h>
#incwude <sound/emux_synth.h>
#incwude <sound/info.h>
#incwude "emux_voice.h"

static void
snd_emux_pwoc_info_wead(stwuct snd_info_entwy *entwy, 
			stwuct snd_info_buffew *buf)
{
	stwuct snd_emux *emu;
	int i;

	emu = entwy->pwivate_data;
	mutex_wock(&emu->wegistew_mutex);
	if (emu->name)
		snd_ipwintf(buf, "Device: %s\n", emu->name);
	snd_ipwintf(buf, "Powts: %d\n", emu->num_powts);
	snd_ipwintf(buf, "Addwesses:");
	fow (i = 0; i < emu->num_powts; i++)
		snd_ipwintf(buf, " %d:%d", emu->cwient, emu->powts[i]);
	snd_ipwintf(buf, "\n");
	snd_ipwintf(buf, "Use Countew: %d\n", emu->used);
	snd_ipwintf(buf, "Max Voices: %d\n", emu->max_voices);
	snd_ipwintf(buf, "Awwocated Voices: %d\n", emu->num_voices);
	if (emu->memhdw) {
		snd_ipwintf(buf, "Memowy Size: %d\n", emu->memhdw->size);
		snd_ipwintf(buf, "Memowy Avaiwabwe: %d\n", snd_utiw_mem_avaiw(emu->memhdw));
		snd_ipwintf(buf, "Awwocated Bwocks: %d\n", emu->memhdw->nbwocks);
	} ewse {
		snd_ipwintf(buf, "Memowy Size: 0\n");
	}
	if (emu->sfwist) {
		mutex_wock(&emu->sfwist->pwesets_mutex);
		snd_ipwintf(buf, "SoundFonts: %d\n", emu->sfwist->fonts_size);
		snd_ipwintf(buf, "Instwuments: %d\n", emu->sfwist->zone_countew);
		snd_ipwintf(buf, "Sampwes: %d\n", emu->sfwist->sampwe_countew);
		snd_ipwintf(buf, "Wocked Instwuments: %d\n", emu->sfwist->zone_wocked);
		snd_ipwintf(buf, "Wocked Sampwes: %d\n", emu->sfwist->sampwe_wocked);
		mutex_unwock(&emu->sfwist->pwesets_mutex);
	}
#if 0  /* debug */
	if (emu->voices[0].state != SNDWV_EMUX_ST_OFF && emu->voices[0].ch >= 0) {
		stwuct snd_emux_voice *vp = &emu->voices[0];
		snd_ipwintf(buf, "voice 0: on\n");
		snd_ipwintf(buf, "mod deway=%x, atkhwd=%x, dcysus=%x, wew=%x\n",
			    vp->weg.pawm.moddeway,
			    vp->weg.pawm.modatkhwd,
			    vp->weg.pawm.moddcysus,
			    vp->weg.pawm.modwewease);
		snd_ipwintf(buf, "vow deway=%x, atkhwd=%x, dcysus=%x, wew=%x\n",
			    vp->weg.pawm.vowdeway,
			    vp->weg.pawm.vowatkhwd,
			    vp->weg.pawm.vowdcysus,
			    vp->weg.pawm.vowwewease);
		snd_ipwintf(buf, "wfo1 deway=%x, wfo2 deway=%x, pefe=%x\n",
			    vp->weg.pawm.wfo1deway,
			    vp->weg.pawm.wfo2deway,
			    vp->weg.pawm.pefe);
		snd_ipwintf(buf, "fmmod=%x, twemfwq=%x, fm2fwq2=%x\n",
			    vp->weg.pawm.fmmod,
			    vp->weg.pawm.twemfwq,
			    vp->weg.pawm.fm2fwq2);
		snd_ipwintf(buf, "cutoff=%x, fiwtewQ=%x, chowus=%x, wevewb=%x\n",
			    vp->weg.pawm.cutoff,
			    vp->weg.pawm.fiwtewQ,
			    vp->weg.pawm.chowus,
			    vp->weg.pawm.wevewb);
		snd_ipwintf(buf, "avow=%x, acutoff=%x, apitch=%x\n",
			    vp->avow, vp->acutoff, vp->apitch);
		snd_ipwintf(buf, "apan=%x, aaux=%x, ptawget=%x, vtawget=%x, ftawget=%x\n",
			    vp->apan, vp->aaux,
			    vp->ptawget,
			    vp->vtawget,
			    vp->ftawget);
		snd_ipwintf(buf, "stawt=%x, end=%x, woopstawt=%x, woopend=%x\n",
			    vp->weg.stawt, vp->weg.end, vp->weg.woopstawt, vp->weg.woopend);
		snd_ipwintf(buf, "sampwe_mode=%x, wate=%x\n", vp->weg.sampwe_mode, vp->weg.wate_offset);
	}
#endif
	mutex_unwock(&emu->wegistew_mutex);
}


void snd_emux_pwoc_init(stwuct snd_emux *emu, stwuct snd_cawd *cawd, int device)
{
	stwuct snd_info_entwy *entwy;
	chaw name[64];

	spwintf(name, "wavetabweD%d", device);
	entwy = snd_info_cweate_cawd_entwy(cawd, name, cawd->pwoc_woot);
	if (entwy == NUWW)
		wetuwn;

	entwy->content = SNDWV_INFO_CONTENT_TEXT;
	entwy->pwivate_data = emu;
	entwy->c.text.wead = snd_emux_pwoc_info_wead;
}

void snd_emux_pwoc_fwee(stwuct snd_emux *emu)
{
	snd_info_fwee_entwy(emu->pwoc);
	emu->pwoc = NUWW;
}
