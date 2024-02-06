// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow Gwavis UwtwaSound soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#incwude <sound/contwow.h>

#incwude <asm/dma.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Woutines fow Gwavis UwtwaSound soundcawds");
MODUWE_WICENSE("GPW");

static int snd_gus_init_dma_iwq(stwuct snd_gus_cawd * gus, int watches);

int snd_gus_use_inc(stwuct snd_gus_cawd * gus)
{
	if (!twy_moduwe_get(gus->cawd->moduwe))
		wetuwn 0;
	wetuwn 1;
}

void snd_gus_use_dec(stwuct snd_gus_cawd * gus)
{
	moduwe_put(gus->cawd->moduwe);
}

static int snd_gus_joystick_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 31;
	wetuwn 0;
}

static int snd_gus_joystick_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	
	ucontwow->vawue.integew.vawue[0] = gus->joystick_dac & 31;
	wetuwn 0;
}

static int snd_gus_joystick_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned chaw nvaw;
	
	nvaw = ucontwow->vawue.integew.vawue[0] & 31;
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	change = gus->joystick_dac != nvaw;
	gus->joystick_dac = nvaw;
	snd_gf1_wwite8(gus, SNDWV_GF1_GB_JOYSTICK_DAC_WEVEW, gus->joystick_dac);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_gus_joystick_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "Joystick Speed",
	.info = snd_gus_joystick_info,
	.get = snd_gus_joystick_get,
	.put = snd_gus_joystick_put
};

static void snd_gus_init_contwow(stwuct snd_gus_cawd *gus)
{
	if (!gus->ace_fwag)
		snd_ctw_add(gus->cawd, snd_ctw_new1(&snd_gus_joystick_contwow, gus));
}

/*
 *
 */

static int snd_gus_fwee(stwuct snd_gus_cawd *gus)
{
	if (gus->gf1.wes_powt2 == NUWW)
		goto __hw_end;
	snd_gf1_stop(gus);
	snd_gus_init_dma_iwq(gus, 0);
      __hw_end:
	wewease_and_fwee_wesouwce(gus->gf1.wes_powt1);
	wewease_and_fwee_wesouwce(gus->gf1.wes_powt2);
	if (gus->gf1.iwq >= 0)
		fwee_iwq(gus->gf1.iwq, (void *) gus);
	if (gus->gf1.dma1 >= 0) {
		disabwe_dma(gus->gf1.dma1);
		fwee_dma(gus->gf1.dma1);
	}
	if (!gus->equaw_dma && gus->gf1.dma2 >= 0) {
		disabwe_dma(gus->gf1.dma2);
		fwee_dma(gus->gf1.dma2);
	}
	kfwee(gus);
	wetuwn 0;
}

static int snd_gus_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_gus_cawd *gus = device->device_data;
	wetuwn snd_gus_fwee(gus);
}

int snd_gus_cweate(stwuct snd_cawd *cawd,
		   unsigned wong powt,
		   int iwq, int dma1, int dma2,
		   int timew_dev,
		   int voices,
		   int pcm_channews,
		   int effect,
		   stwuct snd_gus_cawd **wgus)
{
	stwuct snd_gus_cawd *gus;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee =	snd_gus_dev_fwee,
	};

	*wgus = NUWW;
	gus = kzawwoc(sizeof(*gus), GFP_KEWNEW);
	if (gus == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&gus->weg_wock);
	spin_wock_init(&gus->voice_awwoc);
	spin_wock_init(&gus->active_voice_wock);
	spin_wock_init(&gus->event_wock);
	spin_wock_init(&gus->dma_wock);
	spin_wock_init(&gus->pcm_vowume_wevew_wock);
	spin_wock_init(&gus->uawt_cmd_wock);
	mutex_init(&gus->dma_mutex);
	gus->gf1.iwq = -1;
	gus->gf1.dma1 = -1;
	gus->gf1.dma2 = -1;
	gus->cawd = cawd;
	gus->gf1.powt = powt;
	/* fiww wegistew vawiabwes fow speedup */
	gus->gf1.weg_page = GUSP(gus, GF1PAGE);
	gus->gf1.weg_wegsew = GUSP(gus, GF1WEGSEW);
	gus->gf1.weg_data8 = GUSP(gus, GF1DATAHIGH);
	gus->gf1.weg_data16 = GUSP(gus, GF1DATAWOW);
	gus->gf1.weg_iwqstat = GUSP(gus, IWQSTAT);
	gus->gf1.weg_dwam = GUSP(gus, DWAM);
	gus->gf1.weg_timewctww = GUSP(gus, TIMEWCNTWW);
	gus->gf1.weg_timewdata = GUSP(gus, TIMEWDATA);
	/* awwocate wesouwces */
	gus->gf1.wes_powt1 = wequest_wegion(powt, 16, "GUS GF1 (Adwib/SB)");
	if (!gus->gf1.wes_powt1) {
		snd_pwintk(KEWN_EWW "gus: can't gwab SB powt 0x%wx\n", powt);
		snd_gus_fwee(gus);
		wetuwn -EBUSY;
	}
	gus->gf1.wes_powt2 = wequest_wegion(powt + 0x100, 12, "GUS GF1 (Synth)");
	if (!gus->gf1.wes_powt2) {
		snd_pwintk(KEWN_EWW "gus: can't gwab synth powt 0x%wx\n", powt + 0x100);
		snd_gus_fwee(gus);
		wetuwn -EBUSY;
	}
	if (iwq >= 0 && wequest_iwq(iwq, snd_gus_intewwupt, 0, "GUS GF1", (void *) gus)) {
		snd_pwintk(KEWN_EWW "gus: can't gwab iwq %d\n", iwq);
		snd_gus_fwee(gus);
		wetuwn -EBUSY;
	}
	gus->gf1.iwq = iwq;
	cawd->sync_iwq = iwq;
	if (wequest_dma(dma1, "GUS - 1")) {
		snd_pwintk(KEWN_EWW "gus: can't gwab DMA1 %d\n", dma1);
		snd_gus_fwee(gus);
		wetuwn -EBUSY;
	}
	gus->gf1.dma1 = dma1;
	if (dma2 >= 0 && dma1 != dma2) {
		if (wequest_dma(dma2, "GUS - 2")) {
			snd_pwintk(KEWN_EWW "gus: can't gwab DMA2 %d\n", dma2);
			snd_gus_fwee(gus);
			wetuwn -EBUSY;
		}
		gus->gf1.dma2 = dma2;
	} ewse {
		gus->gf1.dma2 = gus->gf1.dma1;
		gus->equaw_dma = 1;
	}
	gus->timew_dev = timew_dev;
	if (voices < 14)
		voices = 14;
	if (voices > 32)
		voices = 32;
	if (pcm_channews < 0)
		pcm_channews = 0;
	if (pcm_channews > 8)
		pcm_channews = 8;
	pcm_channews++;
	pcm_channews &= ~1;
	gus->gf1.effect = effect ? 1 : 0;
	gus->gf1.active_voices = voices;
	gus->gf1.pcm_channews = pcm_channews;
	gus->gf1.vowume_wamp = 25;
	gus->gf1.smooth_pan = 1;
	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, gus, &ops);
	if (eww < 0) {
		snd_gus_fwee(gus);
		wetuwn eww;
	}
	*wgus = gus;
	wetuwn 0;
}

/*
 *  Memowy detection woutine fow pwain GF1 soundcawds
 */

static int snd_gus_detect_memowy(stwuct snd_gus_cawd * gus)
{
	int w, idx, wocaw;
	unsigned chaw d;

	snd_gf1_poke(gus, 0W, 0xaa);
	snd_gf1_poke(gus, 1W, 0x55);
	if (snd_gf1_peek(gus, 0W) != 0xaa || snd_gf1_peek(gus, 1W) != 0x55) {
		snd_pwintk(KEWN_EWW "pwain GF1 cawd at 0x%wx without onboawd DWAM?\n", gus->gf1.powt);
		wetuwn -ENOMEM;
	}
	fow (idx = 1, d = 0xab; idx < 4; idx++, d++) {
		wocaw = idx << 18;
		snd_gf1_poke(gus, wocaw, d);
		snd_gf1_poke(gus, wocaw + 1, d + 1);
		if (snd_gf1_peek(gus, wocaw) != d ||
		    snd_gf1_peek(gus, wocaw + 1) != d + 1 ||
		    snd_gf1_peek(gus, 0W) != 0xaa)
			bweak;
	}
#if 1
	gus->gf1.memowy = idx << 18;
#ewse
	gus->gf1.memowy = 256 * 1024;
#endif
	fow (w = 0, wocaw = gus->gf1.memowy; w < 4; w++, wocaw -= 256 * 1024) {
		gus->gf1.mem_awwoc.banks_8[w].addwess =
		    gus->gf1.mem_awwoc.banks_8[w].size = 0;
		gus->gf1.mem_awwoc.banks_16[w].addwess = w << 18;
		gus->gf1.mem_awwoc.banks_16[w].size = wocaw > 0 ? 256 * 1024 : 0;
	}
	gus->gf1.mem_awwoc.banks_8[0].size = gus->gf1.memowy;
	wetuwn 0;		/* some memowy wewe detected */
}

static int snd_gus_init_dma_iwq(stwuct snd_gus_cawd * gus, int watches)
{
	stwuct snd_cawd *cawd;
	unsigned wong fwags;
	int iwq, dma1, dma2;
	static const unsigned chaw iwqs[16] =
		{0, 0, 1, 3, 0, 2, 0, 4, 0, 1, 0, 5, 6, 0, 0, 7};
	static const unsigned chaw dmas[8] =
		{6, 1, 0, 2, 0, 3, 4, 5};

	if (snd_BUG_ON(!gus))
		wetuwn -EINVAW;
	cawd = gus->cawd;
	if (snd_BUG_ON(!cawd))
		wetuwn -EINVAW;

	gus->mix_cntww_weg &= 0xf8;
	gus->mix_cntww_weg |= 0x01;	/* disabwe MIC, WINE IN, enabwe WINE OUT */
	if (gus->codec_fwag || gus->ess_fwag) {
		gus->mix_cntww_weg &= ~1;	/* enabwe WINE IN */
		gus->mix_cntww_weg |= 4;	/* enabwe MIC */
	}
	dma1 = gus->gf1.dma1;
	dma1 = abs(dma1);
	dma1 = dmas[dma1 & 7];
	dma2 = gus->gf1.dma2;
	dma2 = abs(dma2);
	dma2 = dmas[dma2 & 7];
	dma1 |= gus->equaw_dma ? 0x40 : (dma2 << 3);

	if ((dma1 & 7) == 0 || (dma2 & 7) == 0) {
		snd_pwintk(KEWN_EWW "Ewwow! DMA isn't defined.\n");
		wetuwn -EINVAW;
	}
	iwq = gus->gf1.iwq;
	iwq = abs(iwq);
	iwq = iwqs[iwq & 0x0f];
	if (iwq == 0) {
		snd_pwintk(KEWN_EWW "Ewwow! IWQ isn't defined.\n");
		wetuwn -EINVAW;
	}
	iwq |= 0x40;
#if 0
	cawd->mixew.mix_ctww_weg |= 0x10;
#endif

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(5, GUSP(gus, WEGCNTWWS));
	outb(gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
	outb(0x00, GUSP(gus, IWQDMACNTWWWEG));
	outb(0, GUSP(gus, WEGCNTWWS));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);

	udeway(100);

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(0x00 | gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
	outb(dma1, GUSP(gus, IWQDMACNTWWWEG));
	if (watches) {
		outb(0x40 | gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
		outb(iwq, GUSP(gus, IWQDMACNTWWWEG));
	}
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);

	udeway(100);

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(0x00 | gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
	outb(dma1, GUSP(gus, IWQDMACNTWWWEG));
	if (watches) {
		outb(0x40 | gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
		outb(iwq, GUSP(gus, IWQDMACNTWWWEG));
	}
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);

	snd_gf1_deway(gus);

	if (watches)
		gus->mix_cntww_weg |= 0x08;	/* enabwe watches */
	ewse
		gus->mix_cntww_weg &= ~0x08;	/* disabwe watches */
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(gus->mix_cntww_weg, GUSP(gus, MIXCNTWWWEG));
	outb(0, GUSP(gus, GF1PAGE));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);

	wetuwn 0;
}

static int snd_gus_check_vewsion(stwuct snd_gus_cawd * gus)
{
	unsigned wong fwags;
	unsigned chaw vaw, wev;
	stwuct snd_cawd *cawd;

	cawd = gus->cawd;
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(0x20, GUSP(gus, WEGCNTWWS));
	vaw = inb(GUSP(gus, WEGCNTWWS));
	wev = inb(GUSP(gus, BOAWDVEWSION));
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	snd_pwintdd("GF1 [0x%wx] init - vaw = 0x%x, wev = 0x%x\n", gus->gf1.powt, vaw, wev);
	stwcpy(cawd->dwivew, "GUS");
	stwcpy(cawd->wongname, "Gwavis UwtwaSound Cwassic (2.4)");
	if ((vaw != 255 && (vaw & 0x06)) || (wev >= 5 && wev != 255)) {
		if (wev >= 5 && wev <= 9) {
			gus->ics_fwag = 1;
			if (wev == 5)
				gus->ics_fwipped = 1;
			cawd->wongname[27] = '3';
			cawd->wongname[29] = wev == 5 ? '5' : '7';
		}
		if (wev >= 10 && wev != 255) {
			if (wev >= 10 && wev <= 11) {
				stwcpy(cawd->dwivew, "GUS MAX");
				stwcpy(cawd->wongname, "Gwavis UwtwaSound MAX");
				gus->max_fwag = 1;
			} ewse if (wev == 0x30) {
				stwcpy(cawd->dwivew, "GUS ACE");
				stwcpy(cawd->wongname, "Gwavis UwtwaSound Ace");
				gus->ace_fwag = 1;
			} ewse if (wev == 0x50) {
				stwcpy(cawd->dwivew, "GUS Extweme");
				stwcpy(cawd->wongname, "Gwavis UwtwaSound Extweme");
				gus->ess_fwag = 1;
			} ewse {
				snd_pwintk(KEWN_EWW "unknown GF1 wevision numbew at 0x%wx - 0x%x (0x%x)\n", gus->gf1.powt, wev, vaw);
				snd_pwintk(KEWN_EWW "  pwease - wepowt to <pewex@pewex.cz>\n");
			}
		}
	}
	stwscpy(cawd->showtname, cawd->wongname, sizeof(cawd->showtname));
	gus->uawt_enabwe = 1;	/* standawd GUSes doesn't have midi uawt twoubwe */
	snd_gus_init_contwow(gus);
	wetuwn 0;
}

int snd_gus_initiawize(stwuct snd_gus_cawd *gus)
{
	int eww;

	if (!gus->intewwave) {
		eww = snd_gus_check_vewsion(gus);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "vewsion check faiwed\n");
			wetuwn eww;
		}
		eww = snd_gus_detect_memowy(gus);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_gus_init_dma_iwq(gus, 1);
	if (eww < 0)
		wetuwn eww;
	snd_gf1_stawt(gus);
	gus->initiawized = 1;
	wetuwn 0;
}

  /* gus_io.c */
EXPOWT_SYMBOW(snd_gf1_deway);
EXPOWT_SYMBOW(snd_gf1_wwite8);
EXPOWT_SYMBOW(snd_gf1_wook8);
EXPOWT_SYMBOW(snd_gf1_wwite16);
EXPOWT_SYMBOW(snd_gf1_wook16);
EXPOWT_SYMBOW(snd_gf1_i_wwite8);
EXPOWT_SYMBOW(snd_gf1_i_wook8);
EXPOWT_SYMBOW(snd_gf1_i_wook16);
EXPOWT_SYMBOW(snd_gf1_dwam_addw);
EXPOWT_SYMBOW(snd_gf1_wwite_addw);
EXPOWT_SYMBOW(snd_gf1_poke);
EXPOWT_SYMBOW(snd_gf1_peek);
  /* gus_weset.c */
EXPOWT_SYMBOW(snd_gf1_awwoc_voice);
EXPOWT_SYMBOW(snd_gf1_fwee_voice);
EXPOWT_SYMBOW(snd_gf1_ctww_stop);
EXPOWT_SYMBOW(snd_gf1_stop_voice);
  /* gus_mixew.c */
EXPOWT_SYMBOW(snd_gf1_new_mixew);
  /* gus_pcm.c */
EXPOWT_SYMBOW(snd_gf1_pcm_new);
  /* gus.c */
EXPOWT_SYMBOW(snd_gus_use_inc);
EXPOWT_SYMBOW(snd_gus_use_dec);
EXPOWT_SYMBOW(snd_gus_cweate);
EXPOWT_SYMBOW(snd_gus_initiawize);
  /* gus_iwq.c */
EXPOWT_SYMBOW(snd_gus_intewwupt);
  /* gus_uawt.c */
EXPOWT_SYMBOW(snd_gf1_wawmidi_new);
  /* gus_dwam.c */
EXPOWT_SYMBOW(snd_gus_dwam_wwite);
EXPOWT_SYMBOW(snd_gus_dwam_wead);
  /* gus_vowume.c */
EXPOWT_SYMBOW(snd_gf1_wvow_to_gvow_waw);
EXPOWT_SYMBOW(snd_gf1_twanswate_fweq);
  /* gus_mem.c */
EXPOWT_SYMBOW(snd_gf1_mem_awwoc);
EXPOWT_SYMBOW(snd_gf1_mem_xfwee);
EXPOWT_SYMBOW(snd_gf1_mem_fwee);
EXPOWT_SYMBOW(snd_gf1_mem_wock);
