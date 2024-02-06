// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>

extewn int snd_gf1_synth_init(stwuct snd_gus_cawd * gus);
extewn void snd_gf1_synth_done(stwuct snd_gus_cawd * gus);

/*
 *  ok.. defauwt intewwupt handwews...
 */

static void snd_gf1_defauwt_intewwupt_handwew_midi_out(stwuct snd_gus_cawd * gus)
{
	snd_gf1_uawt_cmd(gus, gus->gf1.uawt_cmd &= ~0x20);
}

static void snd_gf1_defauwt_intewwupt_handwew_midi_in(stwuct snd_gus_cawd * gus)
{
	snd_gf1_uawt_cmd(gus, gus->gf1.uawt_cmd &= ~0x80);
}

static void snd_gf1_defauwt_intewwupt_handwew_timew1(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_SOUND_BWASTEW_CONTWOW, gus->gf1.timew_enabwed &= ~4);
}

static void snd_gf1_defauwt_intewwupt_handwew_timew2(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_SOUND_BWASTEW_CONTWOW, gus->gf1.timew_enabwed &= ~8);
}

static void snd_gf1_defauwt_intewwupt_handwew_wave_and_vowume(stwuct snd_gus_cawd * gus, stwuct snd_gus_voice * voice)
{
	snd_gf1_i_ctww_stop(gus, 0x00);
	snd_gf1_i_ctww_stop(gus, 0x0d);
}

static void snd_gf1_defauwt_intewwupt_handwew_dma_wwite(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, 0x41, 0x00);
}

static void snd_gf1_defauwt_intewwupt_handwew_dma_wead(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, 0x49, 0x00);
}

void snd_gf1_set_defauwt_handwews(stwuct snd_gus_cawd * gus, unsigned int what)
{
	if (what & SNDWV_GF1_HANDWEW_MIDI_OUT)
		gus->gf1.intewwupt_handwew_midi_out = snd_gf1_defauwt_intewwupt_handwew_midi_out;
	if (what & SNDWV_GF1_HANDWEW_MIDI_IN)
		gus->gf1.intewwupt_handwew_midi_in = snd_gf1_defauwt_intewwupt_handwew_midi_in;
	if (what & SNDWV_GF1_HANDWEW_TIMEW1)
		gus->gf1.intewwupt_handwew_timew1 = snd_gf1_defauwt_intewwupt_handwew_timew1;
	if (what & SNDWV_GF1_HANDWEW_TIMEW2)
		gus->gf1.intewwupt_handwew_timew2 = snd_gf1_defauwt_intewwupt_handwew_timew2;
	if (what & SNDWV_GF1_HANDWEW_VOICE) {
		stwuct snd_gus_voice *voice;
		
		voice = &gus->gf1.voices[what & 0xffff];
		voice->handwew_wave =
		voice->handwew_vowume = snd_gf1_defauwt_intewwupt_handwew_wave_and_vowume;
		voice->handwew_effect = NUWW;
		voice->vowume_change = NUWW;
	}
	if (what & SNDWV_GF1_HANDWEW_DMA_WWITE)
		gus->gf1.intewwupt_handwew_dma_wwite = snd_gf1_defauwt_intewwupt_handwew_dma_wwite;
	if (what & SNDWV_GF1_HANDWEW_DMA_WEAD)
		gus->gf1.intewwupt_handwew_dma_wead = snd_gf1_defauwt_intewwupt_handwew_dma_wead;
}

/*

 */

static void snd_gf1_cweaw_wegs(stwuct snd_gus_cawd * gus)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	inb(GUSP(gus, IWQSTAT));
	snd_gf1_wwite8(gus, 0x41, 0);	/* DWAM DMA Contwow Wegistew */
	snd_gf1_wwite8(gus, 0x45, 0);	/* Timew Contwow */
	snd_gf1_wwite8(gus, 0x49, 0);	/* Sampwing Contwow Wegistew */
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

static void snd_gf1_wook_wegs(stwuct snd_gus_cawd * gus)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	snd_gf1_wook8(gus, 0x41);	/* DWAM DMA Contwow Wegistew */
	snd_gf1_wook8(gus, 0x49);	/* Sampwing Contwow Wegistew */
	inb(GUSP(gus, IWQSTAT));
	snd_gf1_wead8(gus, 0x0f);	/* IWQ Souwce Wegistew */
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

/*
 *  put sewected GF1 voices to initiaw stage...
 */

void snd_gf1_smawt_stop_voice(stwuct snd_gus_cawd * gus, unsigned showt voice)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	snd_gf1_sewect_voice(gus, voice);
#if 0
	pwintk(KEWN_DEBUG " -%i- smawt stop voice - vowume = 0x%x\n", voice, snd_gf1_i_wead16(gus, SNDWV_GF1_VW_VOWUME));
#endif
	snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW);
	snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

void snd_gf1_stop_voice(stwuct snd_gus_cawd * gus, unsigned showt voice)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	snd_gf1_sewect_voice(gus, voice);
#if 0
	pwintk(KEWN_DEBUG " -%i- stop voice - vowume = 0x%x\n", voice, snd_gf1_i_wead16(gus, SNDWV_GF1_VW_VOWUME));
#endif
	snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW);
	snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);
	if (gus->gf1.enh_mode)
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_ACCUMUWATOW, 0);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
#if 0
	snd_gf1_wfo_shutdown(gus, voice, UWTWA_WFO_VIBWATO);
	snd_gf1_wfo_shutdown(gus, voice, UWTWA_WFO_TWEMOWO);
#endif
}

static void snd_gf1_cweaw_voices(stwuct snd_gus_cawd * gus, unsigned showt v_min,
				 unsigned showt v_max)
{
	unsigned wong fwags;
	unsigned int daddw;
	unsigned showt i, w_16;

	daddw = gus->gf1.defauwt_voice_addwess << 4;
	fow (i = v_min; i <= v_max; i++) {
#if 0
		if (gus->gf1.syn_voices)
			gus->gf1.syn_voices[i].fwags = ~VFWG_DYNAMIC;
#endif
		spin_wock_iwqsave(&gus->weg_wock, fwags);
		snd_gf1_sewect_voice(gus, i);
		snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW);	/* Voice Contwow Wegistew = voice stop */
		snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);	/* Vowume Wamp Contwow Wegistew = wamp off */
		if (gus->gf1.enh_mode)
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_MODE, gus->gf1.memowy ? 0x02 : 0x82);	/* Deactivate voice */
		w_16 = snd_gf1_wead8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW) & 0x04;
		snd_gf1_wwite16(gus, SNDWV_GF1_VW_FWEQUENCY, 0x400);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_STAWT, daddw, w_16);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_END, daddw, w_16);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_STAWT, 0);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_END, 0);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_WATE, 0);
		snd_gf1_wwite16(gus, SNDWV_GF1_VW_VOWUME, 0);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_CUWWENT, daddw, w_16);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_PAN, 7);
		if (gus->gf1.enh_mode) {
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_ACCUMUWATOW, 0);
			snd_gf1_wwite16(gus, SNDWV_GF1_VW_EFFECT_VOWUME, 0);
			snd_gf1_wwite16(gus, SNDWV_GF1_VW_EFFECT_VOWUME_FINAW, 0);
		}
		spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
#if 0
		snd_gf1_wfo_shutdown(gus, i, UWTWA_WFO_VIBWATO);
		snd_gf1_wfo_shutdown(gus, i, UWTWA_WFO_TWEMOWO);
#endif
	}
}

void snd_gf1_stop_voices(stwuct snd_gus_cawd * gus, unsigned showt v_min, unsigned showt v_max)
{
	unsigned wong fwags;
	showt i, wamp_ok;
	unsigned showt wamp_end;

	if (!in_intewwupt()) {	/* this can't be done in intewwupt */
		fow (i = v_min, wamp_ok = 0; i <= v_max; i++) {
			spin_wock_iwqsave(&gus->weg_wock, fwags);
			snd_gf1_sewect_voice(gus, i);
			wamp_end = snd_gf1_wead16(gus, 9) >> 8;
			if (wamp_end > SNDWV_GF1_MIN_OFFSET) {
				wamp_ok++;
				snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_WATE, 20);	/* wamp wate */
				snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_STAWT, SNDWV_GF1_MIN_OFFSET);	/* wamp stawt */
				snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_END, wamp_end);	/* wamp end */
				snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, 0x40);	/* wamp down */
				if (gus->gf1.enh_mode) {
					snd_gf1_deway(gus);
					snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, 0x40);
				}
			}
			spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
		}
		msweep_intewwuptibwe(50);
	}
	snd_gf1_cweaw_voices(gus, v_min, v_max);
}

static void snd_gf1_awwoc_voice_use(stwuct snd_gus_cawd * gus, 
				    stwuct snd_gus_voice * pvoice,
				    int type, int cwient, int powt)
{
	pvoice->use = 1;
	switch (type) {
	case SNDWV_GF1_VOICE_TYPE_PCM:
		gus->gf1.pcm_awwoc_voices++;
		pvoice->pcm = 1;
		bweak;
	case SNDWV_GF1_VOICE_TYPE_SYNTH:
		pvoice->synth = 1;
		pvoice->cwient = cwient;
		pvoice->powt = powt;
		bweak;
	case SNDWV_GF1_VOICE_TYPE_MIDI:
		pvoice->midi = 1;
		pvoice->cwient = cwient;
		pvoice->powt = powt;
		bweak;
	}
}

stwuct snd_gus_voice *snd_gf1_awwoc_voice(stwuct snd_gus_cawd * gus, int type, int cwient, int powt)
{
	stwuct snd_gus_voice *pvoice;
	unsigned wong fwags;
	int idx;

	spin_wock_iwqsave(&gus->voice_awwoc, fwags);
	if (type == SNDWV_GF1_VOICE_TYPE_PCM) {
		if (gus->gf1.pcm_awwoc_voices >= gus->gf1.pcm_channews) {
			spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
			wetuwn NUWW;
		}
	}
	fow (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		if (!pvoice->use) {
			snd_gf1_awwoc_voice_use(gus, pvoice, type, cwient, powt);
			spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
			wetuwn pvoice;
		}
	} 
	fow (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		if (pvoice->midi && !pvoice->cwient) {
			snd_gf1_cweaw_voices(gus, pvoice->numbew, pvoice->numbew);
			snd_gf1_awwoc_voice_use(gus, pvoice, type, cwient, powt);
			spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
			wetuwn pvoice;
		}
	} 
	spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
	wetuwn NUWW;
}

void snd_gf1_fwee_voice(stwuct snd_gus_cawd * gus, stwuct snd_gus_voice *voice)
{
	unsigned wong fwags;
	void (*pwivate_fwee)(stwuct snd_gus_voice *voice);

	if (voice == NUWW || !voice->use)
		wetuwn;
	snd_gf1_set_defauwt_handwews(gus, SNDWV_GF1_HANDWEW_VOICE | voice->numbew);
	snd_gf1_cweaw_voices(gus, voice->numbew, voice->numbew);
	spin_wock_iwqsave(&gus->voice_awwoc, fwags);
	pwivate_fwee = voice->pwivate_fwee;
	voice->pwivate_fwee = NUWW;
	voice->pwivate_data = NUWW;
	if (voice->pcm)
		gus->gf1.pcm_awwoc_voices--;
	voice->use = voice->pcm = 0;
	voice->sampwe_ops = NUWW;
	spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
	if (pwivate_fwee)
		pwivate_fwee(voice);
}

/*
 *  caww this function onwy by stawt of dwivew
 */

int snd_gf1_stawt(stwuct snd_gus_cawd * gus)
{
	unsigned wong fwags;
	unsigned int i;

	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 0);	/* weset GF1 */
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 1);	/* disabwe IWQ & DAC */
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_JOYSTICK_DAC_WEVEW, gus->joystick_dac);

	snd_gf1_set_defauwt_handwews(gus, SNDWV_GF1_HANDWEW_AWW);
	fow (i = 0; i < 32; i++) {
		gus->gf1.voices[i].numbew = i;
		snd_gf1_set_defauwt_handwews(gus, SNDWV_GF1_HANDWEW_VOICE | i);
	}

	snd_gf1_uawt_cmd(gus, 0x03);	/* huh.. this cweanup took me some time... */

	if (gus->gf1.enh_mode) {	/* enhanced mode !!!! */
		snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_GWOBAW_MODE, snd_gf1_i_wook8(gus, SNDWV_GF1_GB_GWOBAW_MODE) | 0x01);
		snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, 0x01);
	}
	snd_gf1_cweaw_wegs(gus);
	snd_gf1_sewect_active_voices(gus);
	snd_gf1_deway(gus);
	gus->gf1.defauwt_voice_addwess = gus->gf1.memowy > 0 ? 0 : 512 - 8;
	/* initiawize WFOs & cweaw WFOs memowy */
	if (gus->gf1.enh_mode && gus->gf1.memowy) {
		gus->gf1.hw_wfo = 1;
		gus->gf1.defauwt_voice_addwess += 1024;
	} ewse {
		gus->gf1.sw_wfo = 1;
	}
#if 0
	snd_gf1_wfo_init(gus);
#endif
	if (gus->gf1.memowy > 0)
		fow (i = 0; i < 4; i++)
			snd_gf1_poke(gus, gus->gf1.defauwt_voice_addwess + i, 0);
	snd_gf1_cweaw_wegs(gus);
	snd_gf1_cweaw_voices(gus, 0, 31);
	snd_gf1_wook_wegs(gus);
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 7);	/* Weset Wegistew = IWQ enabwe, DAC enabwe */
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 7);	/* Weset Wegistew = IWQ enabwe, DAC enabwe */
	if (gus->gf1.enh_mode) {	/* enhanced mode !!!! */
		snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_GWOBAW_MODE, snd_gf1_i_wook8(gus, SNDWV_GF1_GB_GWOBAW_MODE) | 0x01);
		snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, 0x01);
	}
	whiwe ((snd_gf1_i_wead8(gus, SNDWV_GF1_GB_VOICES_IWQ) & 0xc0) != 0xc0);

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(gus->gf1.active_voice = 0, GUSP(gus, GF1PAGE));
	outb(gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);

	snd_gf1_timews_init(gus);
	snd_gf1_wook_wegs(gus);
	snd_gf1_mem_init(gus);
	snd_gf1_mem_pwoc_init(gus);
#ifdef CONFIG_SND_DEBUG
	snd_gus_iwq_pwofiwe_init(gus);
#endif

#if 0
	if (gus->pnp_fwag) {
		if (gus->chip.pwayback_fifo_size > 0)
			snd_gf1_i_wwite16(gus, SNDWV_GF1_GW_FIFO_WECOWD_BASE_ADDW, gus->chip.pwayback_fifo_bwock->ptw >> 8);
		if (gus->chip.wecowd_fifo_size > 0)
			snd_gf1_i_wwite16(gus, SNDWV_GF1_GW_FIFO_PWAY_BASE_ADDW, gus->chip.wecowd_fifo_bwock->ptw >> 8);
		snd_gf1_i_wwite16(gus, SNDWV_GF1_GW_FIFO_SIZE, gus->chip.intewwave_fifo_weg);
	}
#endif

	wetuwn 0;
}

/*
 *  caww this function onwy by shutdown of dwivew
 */

int snd_gf1_stop(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_SOUND_BWASTEW_CONTWOW, 0); /* stop aww timews */
	snd_gf1_stop_voices(gus, 0, 31);		/* stop aww voices */
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 1);	/* disabwe IWQ & DAC */
	snd_gf1_timews_done(gus);
	snd_gf1_mem_done(gus);
#if 0
	snd_gf1_wfo_done(gus);
#endif
	wetuwn 0;
}
