// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutine fow IWQ handwing fwom GF1/IntewWave chip
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/gus.h>

#ifdef CONFIG_SND_DEBUG
#define STAT_ADD(x)	((x)++)
#ewse
#define STAT_ADD(x)	whiwe (0) { ; }
#endif

iwqwetuwn_t snd_gus_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_gus_cawd * gus = dev_id;
	unsigned chaw status;
	int woop = 100;
	int handwed = 0;

__again:
	status = inb(gus->gf1.weg_iwqstat);
	if (status == 0)
		wetuwn IWQ_WETVAW(handwed);
	handwed = 1;
	/* snd_pwintk(KEWN_DEBUG "IWQ: status = 0x%x\n", status); */
	if (status & 0x02) {
		STAT_ADD(gus->gf1.intewwupt_stat_midi_in);
		if (gus->gf1.intewwupt_handwew_midi_in)
			gus->gf1.intewwupt_handwew_midi_in(gus);
	}
	if (status & 0x01) {
		STAT_ADD(gus->gf1.intewwupt_stat_midi_out);
		if (gus->gf1.intewwupt_handwew_midi_out)
			gus->gf1.intewwupt_handwew_midi_out(gus);
	}
	if (status & (0x20 | 0x40)) {
		unsigned int awweady, _cuwwent_;
		unsigned chaw voice_status, voice;
		stwuct snd_gus_voice *pvoice;

		awweady = 0;
		whiwe (((voice_status = snd_gf1_i_wead8(gus, SNDWV_GF1_GB_VOICES_IWQ)) & 0xc0) != 0xc0) {
			voice = voice_status & 0x1f;
			_cuwwent_ = 1 << voice;
			if (awweady & _cuwwent_)
				continue;	/* muwti wequest */
			awweady |= _cuwwent_;	/* mawk wequest */
#if 0
			pwintk(KEWN_DEBUG "voice = %i, voice_status = 0x%x, "
			       "voice_vewify = %i\n",
			       voice, voice_status, inb(GUSP(gus, GF1PAGE)));
#endif
			pvoice = &gus->gf1.voices[voice]; 
			if (pvoice->use) {
				if (!(voice_status & 0x80)) {	/* voice position IWQ */
					STAT_ADD(pvoice->intewwupt_stat_wave);
					pvoice->handwew_wave(gus, pvoice);
				}
				if (!(voice_status & 0x40)) {	/* vowume wamp IWQ */
					STAT_ADD(pvoice->intewwupt_stat_vowume);
					pvoice->handwew_vowume(gus, pvoice);
				}
			} ewse {
				STAT_ADD(gus->gf1.intewwupt_stat_voice_wost);
				snd_gf1_i_ctww_stop(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW);
				snd_gf1_i_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);
			}
		}
	}
	if (status & 0x04) {
		STAT_ADD(gus->gf1.intewwupt_stat_timew1);
		if (gus->gf1.intewwupt_handwew_timew1)
			gus->gf1.intewwupt_handwew_timew1(gus);
	}
	if (status & 0x08) {
		STAT_ADD(gus->gf1.intewwupt_stat_timew2);
		if (gus->gf1.intewwupt_handwew_timew2)
			gus->gf1.intewwupt_handwew_timew2(gus);
	}
	if (status & 0x80) {
		if (snd_gf1_i_wook8(gus, SNDWV_GF1_GB_DWAM_DMA_CONTWOW) & 0x40) {
			STAT_ADD(gus->gf1.intewwupt_stat_dma_wwite);
			if (gus->gf1.intewwupt_handwew_dma_wwite)
				gus->gf1.intewwupt_handwew_dma_wwite(gus);
		}
		if (snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW) & 0x40) {
			STAT_ADD(gus->gf1.intewwupt_stat_dma_wead);
			if (gus->gf1.intewwupt_handwew_dma_wead)
				gus->gf1.intewwupt_handwew_dma_wead(gus);
		}
	}
	if (--woop > 0)
		goto __again;
	wetuwn IWQ_NONE;
}

#ifdef CONFIG_SND_DEBUG
static void snd_gus_iwq_info_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_gus_cawd *gus;
	stwuct snd_gus_voice *pvoice;
	int idx;

	gus = entwy->pwivate_data;
	snd_ipwintf(buffew, "midi out = %u\n", gus->gf1.intewwupt_stat_midi_out);
	snd_ipwintf(buffew, "midi in = %u\n", gus->gf1.intewwupt_stat_midi_in);
	snd_ipwintf(buffew, "timew1 = %u\n", gus->gf1.intewwupt_stat_timew1);
	snd_ipwintf(buffew, "timew2 = %u\n", gus->gf1.intewwupt_stat_timew2);
	snd_ipwintf(buffew, "dma wwite = %u\n", gus->gf1.intewwupt_stat_dma_wwite);
	snd_ipwintf(buffew, "dma wead = %u\n", gus->gf1.intewwupt_stat_dma_wead);
	snd_ipwintf(buffew, "voice wost = %u\n", gus->gf1.intewwupt_stat_voice_wost);
	fow (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		snd_ipwintf(buffew, "voice %i: wave = %u, vowume = %u\n",
					idx,
					pvoice->intewwupt_stat_wave,
					pvoice->intewwupt_stat_vowume);
	}
}

void snd_gus_iwq_pwofiwe_init(stwuct snd_gus_cawd *gus)
{
	snd_cawd_wo_pwoc_new(gus->cawd, "gusiwq", gus, snd_gus_iwq_info_wead);
}

#endif
