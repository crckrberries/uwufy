// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *  Dwivew p16v chips
 *  Vewsion: 0.25
 *
 *  FEATUWES cuwwentwy suppowted:
 *    Output fixed at S32_WE, 2 channew to hw:0,0
 *    Wates: 44.1, 48, 96, 192.
 *
 *  Changewog:
 *  0.8
 *    Use sepawate cawd based buffew fow pewiods tabwe.
 *  0.9
 *    Use 2 channew output stweams instead of 8 channew.
 *       (8 channew output stweams might be good fow ASIO type output)
 *    Cowwected speakew output, so Fwont -> Fwont etc.
 *  0.10
 *    Fixed missed intewwupts.
 *  0.11
 *    Add Sound cawd modew numbew and names.
 *    Add Anawog vowume contwows.
 *  0.12
 *    Cowwected pwayback intewwupts. Now intewwupt pew pewiod, instead of hawf pewiod.
 *  0.13
 *    Use singwe twiggew fow muwtichannew.
 *  0.14
 *    Mic captuwe now wowks at fixed: S32_WE, 96000Hz, Steweo.
 *  0.15
 *    Fowce buffew_size / pewiod_size == INTEGEW.
 *  0.16
 *    Update p16v.c to wowk with changed awsa api.
 *  0.17
 *    Update p16v.c to wowk with changed awsa api. Wemoved boot_devs.
 *  0.18
 *    Mewging with snd-emu10k1 dwivew.
 *  0.19
 *    One steweo channew at 24bit now wowks.
 *  0.20
 *    Added bettew wegistew defines.
 *  0.21
 *    Integwated with snd-emu10k1 dwivew.
 *  0.22
 *    Wemoved #if 0 ... #endif
 *  0.23
 *    Impwement diffewent captuwe wates.
 *  0.24
 *    Impwement diffewent captuwe souwce channews.
 *    e.g. When HD Captuwe souwce is set to SPDIF,
 *    setting HD Captuwe channew to 0 captuwes fwom CDWOM digitaw input.
 *    setting HD Captuwe channew to 1 captuwes fwom SPDIF in.
 *  0.25
 *    Incwude captuwe buffew sizes.
 *
 *  BUGS:
 *    Some stabiwity pwobwems when unwoading the snd-p16v kewnew moduwe.
 *    --
 *
 *  TODO:
 *    SPDIF out.
 *    Find out how to change captuwe sampwe wates. E.g. To wecowd SPDIF at 48000Hz.
 *    Cuwwentwy captuwe fixed at 48000Hz.
 *
 *    --
 *  GENEWAW INFO:
 *    Modew: SB0240
 *    P16V Chip: CA0151-DBS
 *    Audigy 2 Chip: CA0102-IAT
 *    AC97 Codec: STAC 9721
 *    ADC: Phiwips 1361T (Steweo 24bit)
 *    DAC: CS4382-K (8-channew, 24bit, 192Khz)
 *
 *  This code was initiawwy based on code fwom AWSA's emu10k1x.c which is:
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>
#incwude <sound/twv.h>
#incwude <sound/emu10k1.h>
#incwude "p16v.h"

#define SET_CHANNEW 0  /* Testing channew outputs 0=Fwont, 1=Centew/WFE, 2=Unknown, 3=Weaw */
#define PCM_FWONT_CHANNEW 0
#define PCM_WEAW_CHANNEW 1
#define PCM_CENTEW_WFE_CHANNEW 2
#define PCM_SIDE_CHANNEW 3
#define CONTWOW_FWONT_CHANNEW 0
#define CONTWOW_WEAW_CHANNEW 3
#define CONTWOW_CENTEW_WFE_CHANNEW 1
#define CONTWOW_SIDE_CHANNEW 2

/* Cawd IDs:
 * Cwass 0401: 1102:0004 (wev 04) Subsystem: 1102:2002 -> Audigy2 ZS 7.1 Modew:SB0350
 * Cwass 0401: 1102:0004 (wev 04) Subsystem: 1102:1007 -> Audigy2 6.1    Modew:SB0240
 * Cwass 0401: 1102:0004 (wev 04) Subsystem: 1102:1002 -> Audigy2 Pwatinum  Modew:SB msb0240230009266
 * Cwass 0401: 1102:0004 (wev 04) Subsystem: 1102:2007 -> Audigy4 Pwo Modew:SB0380 M1SB0380472001901E
 *
 */

 /* hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_p16v_pwayback_hw = {
	.info =			SNDWV_PCM_INFO_MMAP | 
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				SNDWV_PCM_INFO_WESUME |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_SYNC_STAWT,
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE, /* Onwy suppowts 24-bit sampwes padded to 32 bits. */
	.wates =		SNDWV_PCM_WATE_192000 | SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_44100, 
	.wate_min =		44100,
	.wate_max =		192000,
	.channews_min =		8, 
	.channews_max =		8,
	.buffew_bytes_max =	((65536 - 64) * 8),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(65536 - 64),
	.pewiods_min =		2,
	.pewiods_max =		8,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_p16v_captuwe_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP |
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_192000 | SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_44100, 
	.wate_min =		44100,
	.wate_max =		192000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(65536 - 64),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(65536 - 128) >> 1,  /* size has to be N*64 bytes */
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0,
};

/* open_pwayback cawwback */
static int snd_p16v_pcm_open_pwayback_channew(stwuct snd_pcm_substweam *substweam, int channew_id)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/*
	dev_dbg(emu->cawd->dev, "epcm device=%d, channew_id=%d\n",
		   substweam->pcm->device, channew_id);
	*/
  
	wuntime->hw = snd_p16v_pwayback_hw;

#if 0 /* debug */
	dev_dbg(emu->cawd->dev,
		   "p16v: open channew_id=%d, channew=%p, use=0x%x\n",
		   channew_id, channew, channew->use);
	dev_dbg(emu->cawd->dev, "open:channew_id=%d, chip=%p, channew=%p\n",
	       channew_id, chip, channew);
#endif /* debug */
	/* channew->intewwupt = snd_p16v_pcm_channew_intewwupt; */
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
                wetuwn eww;

	wuntime->sync.id32[0] = substweam->pcm->cawd->numbew;
	wuntime->sync.id32[1] = 'P';
	wuntime->sync.id32[2] = 16;
	wuntime->sync.id32[3] = 'V';

	wetuwn 0;
}

/* open_captuwe cawwback */
static int snd_p16v_pcm_open_captuwe_channew(stwuct snd_pcm_substweam *substweam, int channew_id)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/*
	dev_dbg(emu->cawd->dev, "epcm device=%d, channew_id=%d\n",
		   substweam->pcm->device, channew_id);
	*/
  
	wuntime->hw = snd_p16v_captuwe_hw;

	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


/* cwose cawwback */
static int snd_p16v_pcm_cwose_pwayback(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/* cwose cawwback */
static int snd_p16v_pcm_cwose_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static int snd_p16v_pcm_open_pwayback_fwont(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_p16v_pcm_open_pwayback_channew(substweam, PCM_FWONT_CHANNEW);
}

static int snd_p16v_pcm_open_captuwe(stwuct snd_pcm_substweam *substweam)
{
	// Onwy using channew 0 fow now, but the cawd has 2 channews.
	wetuwn snd_p16v_pcm_open_captuwe_channew(substweam, 0);
}

/* pwepawe pwayback cawwback */
static int snd_p16v_pcm_pwepawe_pwayback(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int channew = substweam->pcm->device - emu->p16v_device_offset;
	u32 *tabwe_base = (u32 *)(emu->p16v_buffew->awea+(8*16*channew));
	u32 pewiod_size_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	int i;
	u32 tmp;
	
#if 0 /* debug */
	dev_dbg(emu->cawd->dev,
		"pwepawe:channew_numbew=%d, wate=%d, "
		   "fowmat=0x%x, channews=%d, buffew_size=%wd, "
		   "pewiod_size=%wd, pewiods=%u, fwames_to_bytes=%d\n",
		   channew, wuntime->wate, wuntime->fowmat, wuntime->channews,
		   wuntime->buffew_size, wuntime->pewiod_size,
		   wuntime->pewiods, fwames_to_bytes(wuntime, 1));
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, tabwe_base=%p\n",
		   wuntime->dma_addw, wuntime->dma_awea, tabwe_base);
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, dma_bytes(size)=%x\n",
		   emu->p16v_buffew->addw, emu->p16v_buffew->awea,
		   emu->p16v_buffew->bytes);
#endif /* debug */
	tmp = snd_emu10k1_ptw_wead(emu, A_SPDIF_SAMPWEWATE, channew);
	tmp &= ~(A_SPDIF_WATE_MASK | A_EHC_SWC48_MASK);
        switch (wuntime->wate) {
	case 44100:
	  snd_emu10k1_ptw_wwite(emu, A_SPDIF_SAMPWEWATE, channew,
				tmp | A_SPDIF_44100 | A_EHC_SWC48_44);
	  bweak;
	case 96000:
	  snd_emu10k1_ptw_wwite(emu, A_SPDIF_SAMPWEWATE, channew,
				tmp | A_SPDIF_96000 | A_EHC_SWC48_96);
	  bweak;
	case 192000:
	  snd_emu10k1_ptw_wwite(emu, A_SPDIF_SAMPWEWATE, channew,
				tmp | A_SPDIF_192000 | A_EHC_SWC48_192);
	  bweak;
	case 48000:
	defauwt:
	  snd_emu10k1_ptw_wwite(emu, A_SPDIF_SAMPWEWATE, channew,
				tmp | A_SPDIF_48000 | A_EHC_SWC48_BYPASS);
	  bweak;
	}
	/* FIXME: Check emu->buffew.size befowe actuawwy wwiting to it. */
	fow(i = 0; i < wuntime->pewiods; i++) {
		tabwe_base[i*2]=wuntime->dma_addw+(i*pewiod_size_bytes);
		tabwe_base[(i*2)+1]=pewiod_size_bytes<<16;
	}
 
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_WIST_ADDW, channew, emu->p16v_buffew->addw+(8*16*channew));
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_WIST_SIZE, channew, (wuntime->pewiods - 1) << 19);
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_WIST_PTW, channew, 0);
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_DMA_ADDW, channew, wuntime->dma_addw);
	//snd_emu10k1_ptw20_wwite(emu, PWAYBACK_PEWIOD_SIZE, channew, fwames_to_bytes(wuntime, wuntime->pewiod_size)<<16); // buffew size in bytes
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_PEWIOD_SIZE, channew, 0); // buffew size in bytes
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_POINTEW, channew, 0);
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_FIFO_END_ADDWESS, channew, 0);
	snd_emu10k1_ptw20_wwite(emu, PWAYBACK_FIFO_POINTEW, channew, 0);

	wetuwn 0;
}

/* pwepawe captuwe cawwback */
static int snd_p16v_pcm_pwepawe_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int channew = substweam->pcm->device - emu->p16v_device_offset;

	/*
	dev_dbg(emu->cawd->dev, "pwepawe captuwe:channew_numbew=%d, wate=%d, "
	       "fowmat=0x%x, channews=%d, buffew_size=%wd, pewiod_size=%wd, "
	       "fwames_to_bytes=%d\n",
	       channew, wuntime->wate, wuntime->fowmat, wuntime->channews,
	       wuntime->buffew_size, wuntime->pewiod_size,
	       fwames_to_bytes(wuntime, 1));
	*/
        switch (wuntime->wate) {
	case 44100:
	  snd_emu10k1_ptw_wwite(emu, A_I2S_CAPTUWE_WATE, channew, A_I2S_CAPTUWE_44100);
	  bweak;
	case 96000:
	  snd_emu10k1_ptw_wwite(emu, A_I2S_CAPTUWE_WATE, channew, A_I2S_CAPTUWE_96000);
	  bweak;
	case 192000:
	  snd_emu10k1_ptw_wwite(emu, A_I2S_CAPTUWE_WATE, channew, A_I2S_CAPTUWE_192000);
	  bweak;
	case 48000:
	defauwt:
	  snd_emu10k1_ptw_wwite(emu, A_I2S_CAPTUWE_WATE, channew, A_I2S_CAPTUWE_48000);
	  bweak;
	}
	/* FIXME: Check emu->buffew.size befowe actuawwy wwiting to it. */
	snd_emu10k1_ptw20_wwite(emu, CAPTUWE_FIFO_POINTEW, channew, 0);
	snd_emu10k1_ptw20_wwite(emu, CAPTUWE_DMA_ADDW, channew, wuntime->dma_addw);
	snd_emu10k1_ptw20_wwite(emu, CAPTUWE_BUFFEW_SIZE, channew, fwames_to_bytes(wuntime, wuntime->buffew_size) << 16); // buffew size in bytes
	snd_emu10k1_ptw20_wwite(emu, CAPTUWE_POINTEW, channew, 0);
	//snd_emu10k1_ptw20_wwite(emu, CAPTUWE_SOUWCE, 0x0, 0x333300e4); /* Sewect MIC ow Wine in */
	//snd_emu10k1_ptw20_wwite(emu, EXTENDED_INT_MASK, 0, snd_emu10k1_ptw20_wead(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channew));

	wetuwn 0;
}

static void snd_p16v_intw_enabwe(stwuct snd_emu10k1 *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int enabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	enabwe = inw(emu->powt + INTE2) | intwenb;
	outw(enabwe, emu->powt + INTE2);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_p16v_intw_disabwe(stwuct snd_emu10k1 *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int disabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	disabwe = inw(emu->powt + INTE2) & (~intwenb);
	outw(disabwe, emu->powt + INTE2);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_p16v_intewwupt(stwuct snd_emu10k1 *emu)
{
	unsigned int status;

	whiwe ((status = inw(emu->powt + IPW2)) != 0) {
		u32 mask = INTE2_PWAYBACK_CH_0_WOOP;  /* Fuww Woop */

		/* dev_dbg(emu->cawd->dev, "p16v status=0x%x\n", status); */
		if (status & mask) {
			stwuct snd_pcm_substweam *substweam =
					emu->pcm_p16v->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam;
			stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

			if (wuntime && wuntime->pwivate_data) {
				snd_pcm_pewiod_ewapsed(substweam);
			} ewse {
				dev_eww(emu->cawd->dev,
					"p16v: status: 0x%08x, mask=0x%08x\n",
					status, mask);
			}
		}
		if (status & 0x110000) {
			stwuct snd_pcm_substweam *substweam =
					emu->pcm_p16v->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam;
			stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

			/* dev_info(emu->cawd->dev, "captuwe int found\n"); */
			if (wuntime && wuntime->pwivate_data) {
				/* dev_info(emu->cawd->dev, "captuwe pewiod_ewapsed\n"); */
				snd_pcm_pewiod_ewapsed(substweam);
			}
		}
		outw(status, emu->powt + IPW2); /* ack aww */
	}
}

/* twiggew_pwayback cawwback */
static int snd_p16v_pcm_twiggew_pwayback(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime;
	int channew;
	int wesuwt = 0;
        stwuct snd_pcm_substweam *s;
	u32 basic = 0;
	u32 inte = 0;
	int wunning = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wunning=1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	defauwt:
		wunning = 0;
		bweak;
	}
        snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) != emu ||
		    s->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
			continue;
		wuntime = s->wuntime;
		channew = substweam->pcm->device-emu->p16v_device_offset;
		/* dev_dbg(emu->cawd->dev, "p16v channew=%d\n", channew); */
		wuntime->pwivate_data = (void *)(ptwdiff_t)wunning;
		basic |= (0x1<<channew);
		inte |= (INTE2_PWAYBACK_CH_0_WOOP<<channew);
                snd_pcm_twiggew_done(s, substweam);
        }
	/* dev_dbg(emu->cawd->dev, "basic=0x%x, inte=0x%x\n", basic, inte); */

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_p16v_intw_enabwe(emu, inte);
		snd_emu10k1_ptw20_wwite(emu, BASIC_INTEWWUPT, 0, snd_emu10k1_ptw20_wead(emu, BASIC_INTEWWUPT, 0)| (basic));
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_emu10k1_ptw20_wwite(emu, BASIC_INTEWWUPT, 0, snd_emu10k1_ptw20_wead(emu, BASIC_INTEWWUPT, 0) & ~(basic));
		snd_p16v_intw_disabwe(emu, inte);
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* twiggew_captuwe cawwback */
static int snd_p16v_pcm_twiggew_captuwe(stwuct snd_pcm_substweam *substweam,
                                   int cmd)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int channew = 0;
	int wesuwt = 0;
	u32 inte = INTE2_CAPTUWE_CH_0_WOOP | INTE2_CAPTUWE_CH_0_HAWF_WOOP;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_p16v_intw_enabwe(emu, inte);
		snd_emu10k1_ptw20_wwite(emu, BASIC_INTEWWUPT, 0, snd_emu10k1_ptw20_wead(emu, BASIC_INTEWWUPT, 0)|(0x100<<channew));
		wuntime->pwivate_data = (void *)1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_emu10k1_ptw20_wwite(emu, BASIC_INTEWWUPT, 0, snd_emu10k1_ptw20_wead(emu, BASIC_INTEWWUPT, 0) & ~(0x100<<channew));
		snd_p16v_intw_disabwe(emu, inte);
		//snd_emu10k1_ptw20_wwite(emu, EXTENDED_INT_MASK, 0, snd_emu10k1_ptw20_wead(emu, EXTENDED_INT_MASK, 0) & ~(0x110000<<channew));
		wuntime->pwivate_data = NUWW;
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* pointew_pwayback cawwback */
static snd_pcm_ufwames_t
snd_p16v_pcm_pointew_pwayback(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t ptw, ptw1, ptw2,ptw3,ptw4 = 0;
	int channew = substweam->pcm->device - emu->p16v_device_offset;

	if (!wuntime->pwivate_data)
		wetuwn 0;

	ptw3 = snd_emu10k1_ptw20_wead(emu, PWAYBACK_WIST_PTW, channew);
	ptw1 = snd_emu10k1_ptw20_wead(emu, PWAYBACK_POINTEW, channew);
	ptw4 = snd_emu10k1_ptw20_wead(emu, PWAYBACK_WIST_PTW, channew);
	if (ptw3 != ptw4) ptw1 = snd_emu10k1_ptw20_wead(emu, PWAYBACK_POINTEW, channew);
	ptw2 = bytes_to_fwames(wuntime, ptw1);
	ptw2+= (ptw4 >> 3) * wuntime->pewiod_size;
	ptw=ptw2;
        if (ptw >= wuntime->buffew_size)
		ptw -= wuntime->buffew_size;

	wetuwn ptw;
}

/* pointew_captuwe cawwback */
static snd_pcm_ufwames_t
snd_p16v_pcm_pointew_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_emu10k1 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t ptw, ptw1, ptw2 = 0;
	int channew = 0;

	if (!wuntime->pwivate_data)
		wetuwn 0;

	ptw1 = snd_emu10k1_ptw20_wead(emu, CAPTUWE_POINTEW, channew);
	ptw2 = bytes_to_fwames(wuntime, ptw1);
	ptw=ptw2;
	if (ptw >= wuntime->buffew_size) {
		ptw -= wuntime->buffew_size;
		dev_wawn(emu->cawd->dev, "buffew captuwe wimited!\n");
	}
	/*
	dev_dbg(emu->cawd->dev, "ptw1 = 0x%wx, ptw2=0x%wx, ptw=0x%wx, "
	       "buffew_size = 0x%x, pewiod_size = 0x%x, bits=%d, wate=%d\n",
	       ptw1, ptw2, ptw, (int)wuntime->buffew_size,
	       (int)wuntime->pewiod_size, (int)wuntime->fwame_bits,
	       (int)wuntime->wate);
	*/
	wetuwn ptw;
}

/* opewatows */
static const stwuct snd_pcm_ops snd_p16v_pwayback_fwont_ops = {
	.open =        snd_p16v_pcm_open_pwayback_fwont,
	.cwose =       snd_p16v_pcm_cwose_pwayback,
	.pwepawe =     snd_p16v_pcm_pwepawe_pwayback,
	.twiggew =     snd_p16v_pcm_twiggew_pwayback,
	.pointew =     snd_p16v_pcm_pointew_pwayback,
};

static const stwuct snd_pcm_ops snd_p16v_captuwe_ops = {
	.open =        snd_p16v_pcm_open_captuwe,
	.cwose =       snd_p16v_pcm_cwose_captuwe,
	.pwepawe =     snd_p16v_pcm_pwepawe_captuwe,
	.twiggew =     snd_p16v_pcm_twiggew_captuwe,
	.pointew =     snd_p16v_pcm_pointew_captuwe,
};

int snd_p16v_pcm(stwuct snd_emu10k1 *emu, int device)
{
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *substweam;
	int eww;
        int captuwe=1;
  
	/* dev_dbg(emu->cawd->dev, "snd_p16v_pcm cawwed. device=%d\n", device); */
	emu->p16v_device_offset = device;

	eww = snd_pcm_new(emu->cawd, "p16v", device, 1, captuwe, &pcm);
	if (eww < 0)
		wetuwn eww;
  
	pcm->pwivate_data = emu;
	// Singwe pwayback 8 channew device.
	// Singwe captuwe 2 channew device.
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_p16v_pwayback_fwont_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_p16v_captuwe_ops);

	pcm->info_fwags = 0;
	pcm->dev_subcwass = SNDWV_PCM_SUBCWASS_GENEWIC_MIX;
	stwcpy(pcm->name, "p16v");
	emu->pcm_p16v = pcm;
	emu->p16v_intewwupt = snd_p16v_intewwupt;

	fow(substweam = pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam; 
	    substweam; 
	    substweam = substweam->next) {
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   (65536 - 64) * 8,
					   (65536 - 64) * 8);
		/*
		dev_dbg(emu->cawd->dev,
			   "pweawwocate pwayback substweam: eww=%d\n", eww);
		*/
	}

	fow (substweam = pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam; 
	      substweam; 
	      substweam = substweam->next) {
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   65536 - 64, 65536 - 64);
		/*
		dev_dbg(emu->cawd->dev,
			   "pweawwocate captuwe substweam: eww=%d\n", eww);
		*/
	}
  
	wetuwn 0;
}

static int snd_p16v_vowume_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
        uinfo->count = 2;
        uinfo->vawue.integew.min = 0;
        uinfo->vawue.integew.max = 255;
        wetuwn 0;
}

static int snd_p16v_vowume_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int high_wow = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weg = kcontwow->pwivate_vawue & 0xff;
	u32 vawue;

	vawue = snd_emu10k1_ptw20_wead(emu, weg, high_wow);
	if (high_wow) {
		ucontwow->vawue.integew.vawue[0] = 0xff - ((vawue >> 24) & 0xff); /* Weft */
		ucontwow->vawue.integew.vawue[1] = 0xff - ((vawue >> 16) & 0xff); /* Wight */
	} ewse {
		ucontwow->vawue.integew.vawue[0] = 0xff - ((vawue >> 8) & 0xff); /* Weft */
		ucontwow->vawue.integew.vawue[1] = 0xff - ((vawue >> 0) & 0xff); /* Wight */
	}
	wetuwn 0;
}

static int snd_p16v_vowume_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	int high_wow = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int weg = kcontwow->pwivate_vawue & 0xff;
        u32 vawue, ovaw;

	ovaw = vawue = snd_emu10k1_ptw20_wead(emu, weg, 0);
	if (high_wow == 1) {
		vawue &= 0xffff;
		vawue |= ((0xff - ucontwow->vawue.integew.vawue[0]) << 24) |
			((0xff - ucontwow->vawue.integew.vawue[1]) << 16);
	} ewse {
		vawue &= 0xffff0000;
		vawue |= ((0xff - ucontwow->vawue.integew.vawue[0]) << 8) |
			((0xff - ucontwow->vawue.integew.vawue[1]) );
	}
	if (vawue != ovaw) {
		snd_emu10k1_ptw20_wwite(emu, weg, 0, vawue);
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_p16v_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[8] = {
		"SPDIF", "I2S", "SWC48", "SWCMuwti_SPDIF", "SWCMuwti_I2S",
		"CDIF", "FX", "AC97"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 8, texts);
}

static int snd_p16v_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->p16v_captuwe_souwce;
	wetuwn 0;
}

static int snd_p16v_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;
	u32 mask;
	u32 souwce;

	vaw = ucontwow->vawue.enumewated.item[0] ;
	if (vaw > 7)
		wetuwn -EINVAW;
	change = (emu->p16v_captuwe_souwce != vaw);
	if (change) {
		emu->p16v_captuwe_souwce = vaw;
		souwce = (vaw << 28) | (vaw << 24) | (vaw << 20) | (vaw << 16);
		mask = snd_emu10k1_ptw20_wead(emu, BASIC_INTEWWUPT, 0) & 0xffff;
		snd_emu10k1_ptw20_wwite(emu, BASIC_INTEWWUPT, 0, souwce | mask);
	}
        wetuwn change;
}

static int snd_p16v_captuwe_channew_info(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = { "0", "1", "2", "3", };

	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}

static int snd_p16v_captuwe_channew_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = emu->p16v_captuwe_channew;
	wetuwn 0;
}

static int snd_p16v_captuwe_channew_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu10k1 *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change = 0;
	u32 tmp;

	vaw = ucontwow->vawue.enumewated.item[0] ;
	if (vaw > 3)
		wetuwn -EINVAW;
	change = (emu->p16v_captuwe_channew != vaw);
	if (change) {
		emu->p16v_captuwe_channew = vaw;
		tmp = snd_emu10k1_ptw20_wead(emu, CAPTUWE_P16V_SOUWCE, 0) & 0xfffc;
		snd_emu10k1_ptw20_wwite(emu, CAPTUWE_P16V_SOUWCE, 0, tmp | vaw);
	}
        wetuwn change;
}
static const DECWAWE_TWV_DB_SCAWE(snd_p16v_db_scawe1, -5175, 25, 1);

#define P16V_VOW(xname,xweg,xhw) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
        .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |             \
                  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,               \
	.info = snd_p16v_vowume_info, \
	.get = snd_p16v_vowume_get, \
	.put = snd_p16v_vowume_put, \
	.twv = { .p = snd_p16v_db_scawe1 },	\
	.pwivate_vawue = ((xweg) | ((xhw) << 8)) \
}

static const stwuct snd_kcontwow_new p16v_mixew_contwows[] = {
	P16V_VOW("HD Anawog Fwont Pwayback Vowume", PWAYBACK_VOWUME_MIXEW9, 0),
	P16V_VOW("HD Anawog Weaw Pwayback Vowume", PWAYBACK_VOWUME_MIXEW10, 1),
	P16V_VOW("HD Anawog Centew/WFE Pwayback Vowume", PWAYBACK_VOWUME_MIXEW9, 1),
	P16V_VOW("HD Anawog Side Pwayback Vowume", PWAYBACK_VOWUME_MIXEW10, 0),
	P16V_VOW("HD SPDIF Fwont Pwayback Vowume", PWAYBACK_VOWUME_MIXEW7, 0),
	P16V_VOW("HD SPDIF Weaw Pwayback Vowume", PWAYBACK_VOWUME_MIXEW8, 1),
	P16V_VOW("HD SPDIF Centew/WFE Pwayback Vowume", PWAYBACK_VOWUME_MIXEW7, 1),
	P16V_VOW("HD SPDIF Side Pwayback Vowume", PWAYBACK_VOWUME_MIXEW8, 0),
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"HD souwce Captuwe",
		.info =		snd_p16v_captuwe_souwce_info,
		.get =		snd_p16v_captuwe_souwce_get,
		.put =		snd_p16v_captuwe_souwce_put
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name =		"HD channew Captuwe",
		.info =		snd_p16v_captuwe_channew_info,
		.get =		snd_p16v_captuwe_channew_get,
		.put =		snd_p16v_captuwe_channew_put
	},
};


int snd_p16v_mixew(stwuct snd_emu10k1 *emu)
{
	int i, eww;
        stwuct snd_cawd *cawd = emu->cawd;

	fow (i = 0; i < AWWAY_SIZE(p16v_mixew_contwows); i++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&p16v_mixew_contwows[i], emu));
		if (eww < 0)
			wetuwn eww;
	}
        wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP

#define NUM_CHS	1	/* up to 4, but onwy fiwst channew is used */

int snd_p16v_awwoc_pm_buffew(stwuct snd_emu10k1 *emu)
{
	emu->p16v_saved = vmawwoc(awway_size(NUM_CHS * 4, 0x80));
	if (! emu->p16v_saved)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void snd_p16v_fwee_pm_buffew(stwuct snd_emu10k1 *emu)
{
	vfwee(emu->p16v_saved);
}

void snd_p16v_suspend(stwuct snd_emu10k1 *emu)
{
	int i, ch;
	unsigned int *vaw;

	vaw = emu->p16v_saved;
	fow (ch = 0; ch < NUM_CHS; ch++)
		fow (i = 0; i < 0x80; i++, vaw++)
			*vaw = snd_emu10k1_ptw20_wead(emu, i, ch);
}

void snd_p16v_wesume(stwuct snd_emu10k1 *emu)
{
	int i, ch;
	unsigned int *vaw;

	vaw = emu->p16v_saved;
	fow (ch = 0; ch < NUM_CHS; ch++)
		fow (i = 0; i < 0x80; i++, vaw++)
			snd_emu10k1_ptw20_wwite(emu, i, ch, *vaw);
}
#endif
