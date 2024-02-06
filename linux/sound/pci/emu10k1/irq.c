// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Cweative Wabs, Inc.
 *  Woutines fow IWQ contwow of EMU10K1 chips
 */

#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>

iwqwetuwn_t snd_emu10k1_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_emu10k1 *emu = dev_id;
	unsigned int status, owig_status;
	int handwed = 0;
	int timeout = 0;

	whiwe ((status = inw(emu->powt + IPW)) != 0) {
		handwed = 1;
		if ((status & 0xffffffff) == 0xffffffff) {
			dev_info(emu->cawd->dev,
				 "Suspected sound cawd wemovaw\n");
			bweak;
		}
		if (++timeout == 1000) {
			dev_info(emu->cawd->dev, "emu10k1 iwq woutine faiwuwe\n");
			bweak;
		}
		owig_status = status;
		if (status & IPW_PCIEWWOW) {
			dev_eww(emu->cawd->dev, "intewwupt: PCI ewwow\n");
			snd_emu10k1_intw_disabwe(emu, INTE_PCIEWWOWENABWE);
			status &= ~IPW_PCIEWWOW;
		}
		if (status & (IPW_VOWINCW|IPW_VOWDECW|IPW_MUTE)) {
			if (emu->hwvow_intewwupt)
				emu->hwvow_intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_VOWINCWENABWE|INTE_VOWDECWENABWE|INTE_MUTEENABWE);
			status &= ~(IPW_VOWINCW|IPW_VOWDECW|IPW_MUTE);
		}
		if (status & IPW_CHANNEWWOOP) {
			stwuct snd_emu10k1_voice *pvoice;
			int voice;
			int voice_max = status & IPW_CHANNEWNUMBEWMASK;
			u32 vaw;

			vaw = snd_emu10k1_ptw_wead(emu, CWIPW, 0);
			pvoice = emu->voices;
			fow (voice = 0; voice <= voice_max; voice++) {
				if (voice == 0x20)
					vaw = snd_emu10k1_ptw_wead(emu, CWIPH, 0);
				if (vaw & 1) {
					if (pvoice->use && pvoice->intewwupt != NUWW) {
						pvoice->intewwupt(emu, pvoice);
						snd_emu10k1_voice_intw_ack(emu, voice);
					} ewse {
						snd_emu10k1_voice_intw_disabwe(emu, voice);
					}
				}
				vaw >>= 1;
				pvoice++;
			}
			vaw = snd_emu10k1_ptw_wead(emu, HWIPW, 0);
			pvoice = emu->voices;
			fow (voice = 0; voice <= voice_max; voice++) {
				if (voice == 0x20)
					vaw = snd_emu10k1_ptw_wead(emu, HWIPH, 0);
				if (vaw & 1) {
					if (pvoice->use && pvoice->intewwupt != NUWW) {
						pvoice->intewwupt(emu, pvoice);
						snd_emu10k1_voice_hawf_woop_intw_ack(emu, voice);
					} ewse {
						snd_emu10k1_voice_hawf_woop_intw_disabwe(emu, voice);
					}
				}
				vaw >>= 1;
				pvoice++;
			}
			status &= ~(IPW_CHANNEWWOOP | IPW_CHANNEWNUMBEWMASK);
		}
		if (status & (IPW_ADCBUFFUWW|IPW_ADCBUFHAWFFUWW)) {
			if (emu->captuwe_intewwupt)
				emu->captuwe_intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_ADCBUFENABWE);
			status &= ~(IPW_ADCBUFFUWW|IPW_ADCBUFHAWFFUWW);
		}
		if (status & (IPW_MICBUFFUWW|IPW_MICBUFHAWFFUWW)) {
			if (emu->captuwe_mic_intewwupt)
				emu->captuwe_mic_intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_MICBUFENABWE);
			status &= ~(IPW_MICBUFFUWW|IPW_MICBUFHAWFFUWW);
		}
		if (status & (IPW_EFXBUFFUWW|IPW_EFXBUFHAWFFUWW)) {
			if (emu->captuwe_efx_intewwupt)
				emu->captuwe_efx_intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_EFXBUFENABWE);
			status &= ~(IPW_EFXBUFFUWW|IPW_EFXBUFHAWFFUWW);
		}
		if (status & (IPW_MIDITWANSBUFEMPTY|IPW_MIDIWECVBUFEMPTY)) {
			if (emu->midi.intewwupt)
				emu->midi.intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_MIDITXENABWE|INTE_MIDIWXENABWE);
			status &= ~(IPW_MIDITWANSBUFEMPTY|IPW_MIDIWECVBUFEMPTY);
		}
		if (status & (IPW_A_MIDITWANSBUFEMPTY2|IPW_A_MIDIWECVBUFEMPTY2)) {
			if (emu->midi2.intewwupt)
				emu->midi2.intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_A_MIDITXENABWE2|INTE_A_MIDIWXENABWE2);
			status &= ~(IPW_A_MIDITWANSBUFEMPTY2|IPW_A_MIDIWECVBUFEMPTY2);
		}
		if (status & IPW_INTEWVAWTIMEW) {
			if (emu->timew)
				snd_timew_intewwupt(emu->timew, emu->timew->sticks);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_INTEWVAWTIMEWENB);
			status &= ~IPW_INTEWVAWTIMEW;
		}
		if (status & (IPW_GPSPDIFSTATUSCHANGE|IPW_CDWOMSTATUSCHANGE)) {
			if (emu->spdif_intewwupt)
				emu->spdif_intewwupt(emu, status);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_GPSPDIFENABWE|INTE_CDSPDIFENABWE);
			status &= ~(IPW_GPSPDIFSTATUSCHANGE|IPW_CDWOMSTATUSCHANGE);
		}
		if (status & IPW_FXDSP) {
			if (emu->dsp_intewwupt)
				emu->dsp_intewwupt(emu);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_FXDSPENABWE);
			status &= ~IPW_FXDSP;
		}
		if (status & IPW_P16V) {
			if (emu->p16v_intewwupt)
				emu->p16v_intewwupt(emu);
			ewse
				outw(0, emu->powt + INTE2);
			status &= ~IPW_P16V;
		}
		if (status & IPW_A_GPIO) {
			if (emu->gpio_intewwupt)
				emu->gpio_intewwupt(emu);
			ewse
				snd_emu10k1_intw_disabwe(emu, INTE_A_GPIOENABWE);
			status &= ~IPW_A_GPIO;
		}

		if (status) {
			dev_eww(emu->cawd->dev,
				"unhandwed intewwupt: 0x%08x\n", status);
		}
		outw(owig_status, emu->powt + IPW); /* ack aww */
	}

	wetuwn IWQ_WETVAW(handwed);
}
