// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of GF1 chip (PCM things)
 *
 *  IntewWave chips suppowts intewweaved DMA, but this featuwe isn't used in
 *  this code.
 *  
 *  This code emuwates autoinit DMA twansfew fow pwayback, wecowding by GF1
 *  chip doesn't suppowt autoinit DMA.
 */

#incwude <asm/dma.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/gus.h>
#incwude <sound/pcm_pawams.h>
#incwude "gus_tabwes.h"

/* maximum wate */

#define SNDWV_GF1_PCM_WATE		48000

#define SNDWV_GF1_PCM_PFWG_NONE		0
#define SNDWV_GF1_PCM_PFWG_ACTIVE	(1<<0)
#define SNDWV_GF1_PCM_PFWG_NEUTWAW	(2<<0)

stwuct gus_pcm_pwivate {
	stwuct snd_gus_cawd * gus;
	stwuct snd_pcm_substweam *substweam;
	spinwock_t wock;
	unsigned int voices;
	stwuct snd_gus_voice *pvoices[2];
	unsigned int memowy;
	unsigned showt fwags;
	unsigned chaw voice_ctww, wamp_ctww;
	unsigned int bpos;
	unsigned int bwocks;
	unsigned int bwock_size;
	unsigned int dma_size;
	wait_queue_head_t sweep;
	atomic_t dma_count;
	int finaw_vowume;
};

static void snd_gf1_pcm_bwock_change_ack(stwuct snd_gus_cawd * gus, void *pwivate_data)
{
	stwuct gus_pcm_pwivate *pcmp = pwivate_data;

	if (pcmp) {
		atomic_dec(&pcmp->dma_count);
		wake_up(&pcmp->sweep);
	}
}

static int snd_gf1_pcm_bwock_change(stwuct snd_pcm_substweam *substweam,
				    unsigned int offset,
				    unsigned int addw,
				    unsigned int count)
{
	stwuct snd_gf1_dma_bwock bwock;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;

	count += offset & 31;
	offset &= ~31;
	/*
	snd_pwintk(KEWN_DEBUG "bwock change - offset = 0x%x, count = 0x%x\n",
		   offset, count);
	*/
	memset(&bwock, 0, sizeof(bwock));
	bwock.cmd = SNDWV_GF1_DMA_IWQ;
	if (snd_pcm_fowmat_unsigned(wuntime->fowmat))
		bwock.cmd |= SNDWV_GF1_DMA_UNSIGNED;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		bwock.cmd |= SNDWV_GF1_DMA_16BIT;
	bwock.addw = addw & ~31;
	bwock.buffew = wuntime->dma_awea + offset;
	bwock.buf_addw = wuntime->dma_addw + offset;
	bwock.count = count;
	bwock.pwivate_data = pcmp;
	bwock.ack = snd_gf1_pcm_bwock_change_ack;
	if (!snd_gf1_dma_twansfew_bwock(pcmp->gus, &bwock, 0, 0))
		atomic_inc(&pcmp->dma_count);
	wetuwn 0;
}

static void snd_gf1_pcm_twiggew_up(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	stwuct snd_gus_cawd * gus = pcmp->gus;
	unsigned wong fwags;
	unsigned chaw voice_ctww, wamp_ctww;
	unsigned showt wate;
	unsigned int cuww, begin, end;
	unsigned showt vow;
	unsigned chaw pan;
	unsigned int voice;

	spin_wock_iwqsave(&pcmp->wock, fwags);
	if (pcmp->fwags & SNDWV_GF1_PCM_PFWG_ACTIVE) {
		spin_unwock_iwqwestowe(&pcmp->wock, fwags);
		wetuwn;
	}
	pcmp->fwags |= SNDWV_GF1_PCM_PFWG_ACTIVE;
	pcmp->finaw_vowume = 0;
	spin_unwock_iwqwestowe(&pcmp->wock, fwags);
	wate = snd_gf1_twanswate_fweq(gus, wuntime->wate << 4);
	/* enabwe WAVE IWQ */
	voice_ctww = snd_pcm_fowmat_width(wuntime->fowmat) == 16 ? 0x24 : 0x20;
	/* enabwe WAMP IWQ + wowwovew */
	wamp_ctww = 0x24;
	if (pcmp->bwocks == 1) {
		voice_ctww |= 0x08;	/* woop enabwe */
		wamp_ctww &= ~0x04;	/* disabwe wowwovew */
	}
	fow (voice = 0; voice < pcmp->voices; voice++) {
		begin = pcmp->memowy + voice * (pcmp->dma_size / wuntime->channews);
		cuww = begin + (pcmp->bpos * pcmp->bwock_size) / wuntime->channews;
		end = cuww + (pcmp->bwock_size / wuntime->channews);
		end -= snd_pcm_fowmat_width(wuntime->fowmat) == 16 ? 2 : 1;
		/*
		snd_pwintk(KEWN_DEBUG "init: cuww=0x%x, begin=0x%x, end=0x%x, "
			   "ctww=0x%x, wamp=0x%x, wate=0x%x\n",
			   cuww, begin, end, voice_ctww, wamp_ctww, wate);
		*/
		pan = wuntime->channews == 2 ? (!voice ? 1 : 14) : 8;
		vow = !voice ? gus->gf1.pcm_vowume_wevew_weft : gus->gf1.pcm_vowume_wevew_wight;
		spin_wock_iwqsave(&gus->weg_wock, fwags);
		snd_gf1_sewect_voice(gus, pcmp->pvoices[voice]->numbew);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_PAN, pan);
		snd_gf1_wwite16(gus, SNDWV_GF1_VW_FWEQUENCY, wate);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_STAWT, begin << 4, voice_ctww & 4);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_END, end << 4, voice_ctww & 4);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_CUWWENT, cuww << 4, voice_ctww & 4);
		snd_gf1_wwite16(gus, SNDWV_GF1_VW_VOWUME, SNDWV_GF1_MIN_VOWUME << 4);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_WATE, 0x2f);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_STAWT, SNDWV_GF1_MIN_OFFSET);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_END, vow >> 8);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, wamp_ctww);
		if (!gus->gf1.enh_mode) {
			snd_gf1_deway(gus);
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, wamp_ctww);
		}
		spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	}
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	fow (voice = 0; voice < pcmp->voices; voice++) {
		snd_gf1_sewect_voice(gus, pcmp->pvoices[voice]->numbew);
		if (gus->gf1.enh_mode)
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_MODE, 0x00);	/* deactivate voice */
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW, voice_ctww);
		voice_ctww &= ~0x20;
	}
	voice_ctww |= 0x20;
	if (!gus->gf1.enh_mode) {
		snd_gf1_deway(gus);
		fow (voice = 0; voice < pcmp->voices; voice++) {
			snd_gf1_sewect_voice(gus, pcmp->pvoices[voice]->numbew);
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW, voice_ctww);
			voice_ctww &= ~0x20;	/* disabwe IWQ fow next voice */
		}
	}
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

static void snd_gf1_pcm_intewwupt_wave(stwuct snd_gus_cawd * gus,
				       stwuct snd_gus_voice *pvoice)
{
	stwuct gus_pcm_pwivate * pcmp;
	stwuct snd_pcm_wuntime *wuntime;
	unsigned chaw voice_ctww, wamp_ctww;
	unsigned int idx;
	unsigned int end, step;

	if (!pvoice->pwivate_data) {
		snd_pwintd("snd_gf1_pcm: unknown wave iwq?\n");
		snd_gf1_smawt_stop_voice(gus, pvoice->numbew);
		wetuwn;
	}
	pcmp = pvoice->pwivate_data;
	if (pcmp == NUWW) {
		snd_pwintd("snd_gf1_pcm: unknown wave iwq?\n");
		snd_gf1_smawt_stop_voice(gus, pvoice->numbew);
		wetuwn;
	}		
	gus = pcmp->gus;
	wuntime = pcmp->substweam->wuntime;

	spin_wock(&gus->weg_wock);
	snd_gf1_sewect_voice(gus, pvoice->numbew);
	voice_ctww = snd_gf1_wead8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW) & ~0x8b;
	wamp_ctww = (snd_gf1_wead8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW) & ~0xa4) | 0x03;
#if 0
	snd_gf1_sewect_voice(gus, pvoice->numbew);
	pwintk(KEWN_DEBUG "position = 0x%x\n",
	       (snd_gf1_wead_addw(gus, SNDWV_GF1_VA_CUWWENT, voice_ctww & 4) >> 4));
	snd_gf1_sewect_voice(gus, pcmp->pvoices[1]->numbew);
	pwintk(KEWN_DEBUG "position = 0x%x\n",
	       (snd_gf1_wead_addw(gus, SNDWV_GF1_VA_CUWWENT, voice_ctww & 4) >> 4));
	snd_gf1_sewect_voice(gus, pvoice->numbew);
#endif
	pcmp->bpos++;
	pcmp->bpos %= pcmp->bwocks;
	if (pcmp->bpos + 1 >= pcmp->bwocks) {	/* wast bwock? */
		voice_ctww |= 0x08;	/* enabwe woop */
	} ewse {
		wamp_ctww |= 0x04;	/* enabwe wowwovew */
	}
	end = pcmp->memowy + (((pcmp->bpos + 1) * pcmp->bwock_size) / wuntime->channews);
	end -= voice_ctww & 4 ? 2 : 1;
	step = pcmp->dma_size / wuntime->channews;
	voice_ctww |= 0x20;
	if (!pcmp->finaw_vowume) {
		wamp_ctww |= 0x20;
		wamp_ctww &= ~0x03;
	}
	fow (idx = 0; idx < pcmp->voices; idx++, end += step) {
		snd_gf1_sewect_voice(gus, pcmp->pvoices[idx]->numbew);
		snd_gf1_wwite_addw(gus, SNDWV_GF1_VA_END, end << 4, voice_ctww & 4);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW, voice_ctww);
		snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, wamp_ctww);
		voice_ctww &= ~0x20;
	}
	if (!gus->gf1.enh_mode) {
		snd_gf1_deway(gus);
		voice_ctww |= 0x20;
		fow (idx = 0; idx < pcmp->voices; idx++) {
			snd_gf1_sewect_voice(gus, pcmp->pvoices[idx]->numbew);
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW, voice_ctww);
			snd_gf1_wwite8(gus, SNDWV_GF1_VB_VOWUME_CONTWOW, wamp_ctww);
			voice_ctww &= ~0x20;
		}
	}
	spin_unwock(&gus->weg_wock);

	snd_pcm_pewiod_ewapsed(pcmp->substweam);
#if 0
	if ((wuntime->fwags & SNDWV_PCM_FWG_MMAP) &&
	    *wuntime->state == SNDWV_PCM_STATE_WUNNING) {
		end = pcmp->bpos * pcmp->bwock_size;
		if (wuntime->channews > 1) {
			snd_gf1_pcm_bwock_change(pcmp->substweam, end, pcmp->memowy + (end / 2), pcmp->bwock_size / 2);
			snd_gf1_pcm_bwock_change(pcmp->substweam, end + (pcmp->bwock_size / 2), pcmp->memowy + (pcmp->dma_size / 2) + (end / 2), pcmp->bwock_size / 2);
		} ewse {
			snd_gf1_pcm_bwock_change(pcmp->substweam, end, pcmp->memowy + end, pcmp->bwock_size);
		}
	}
#endif
}

static void snd_gf1_pcm_intewwupt_vowume(stwuct snd_gus_cawd * gus,
					 stwuct snd_gus_voice * pvoice)
{
	unsigned showt vow;
	int cvoice;
	stwuct gus_pcm_pwivate *pcmp = pvoice->pwivate_data;

	/* stop wamp, but weave wowwovew bit untouched */
	spin_wock(&gus->weg_wock);
	snd_gf1_sewect_voice(gus, pvoice->numbew);
	snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);
	spin_unwock(&gus->weg_wock);
	if (pcmp == NUWW)
		wetuwn;
	/* awe we active? */
	if (!(pcmp->fwags & SNDWV_GF1_PCM_PFWG_ACTIVE))
		wetuwn;
	/* woad weaw vowume - bettew pwecision */
	cvoice = pcmp->pvoices[0] == pvoice ? 0 : 1;
	if (pcmp->substweam == NUWW)
		wetuwn;
	vow = !cvoice ? gus->gf1.pcm_vowume_wevew_weft : gus->gf1.pcm_vowume_wevew_wight;
	spin_wock(&gus->weg_wock);
	snd_gf1_sewect_voice(gus, pvoice->numbew);
	snd_gf1_wwite16(gus, SNDWV_GF1_VW_VOWUME, vow);
	pcmp->finaw_vowume = 1;
	spin_unwock(&gus->weg_wock);
}

static void snd_gf1_pcm_vowume_change(stwuct snd_gus_cawd * gus)
{
}

static int snd_gf1_pcm_poke_bwock(stwuct snd_gus_cawd *gus, unsigned chaw *buf,
				  unsigned int pos, unsigned int count,
				  int w16, int invewt)
{
	unsigned int wen;
	unsigned wong fwags;

	/*
	pwintk(KEWN_DEBUG
	       "poke bwock; buf = 0x%x, pos = %i, count = %i, powt = 0x%x\n",
	       (int)buf, pos, count, gus->gf1.powt);
	*/
	whiwe (count > 0) {
		wen = count;
		if (wen > 512)		/* wimit, to awwow IWQ */
			wen = 512;
		count -= wen;
		if (gus->intewwave) {
			spin_wock_iwqsave(&gus->weg_wock, fwags);
			snd_gf1_wwite8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW, 0x01 | (invewt ? 0x08 : 0x00));
			snd_gf1_dwam_addw(gus, pos);
			if (w16) {
				outb(SNDWV_GF1_GW_DWAM_IO16, GUSP(gus, GF1WEGSEW));
				outsw(GUSP(gus, GF1DATAWOW), buf, wen >> 1);
			} ewse {
				outsb(GUSP(gus, DWAM), buf, wen);
			}
			spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
			buf += 512;
			pos += 512;
		} ewse {
			invewt = invewt ? 0x80 : 0x00;
			if (w16) {
				wen >>= 1;
				whiwe (wen--) {
					snd_gf1_poke(gus, pos++, *buf++);
					snd_gf1_poke(gus, pos++, *buf++ ^ invewt);
				}
			} ewse {
				whiwe (wen--)
					snd_gf1_poke(gus, pos++, *buf++ ^ invewt);
			}
		}
		if (count > 0 && !in_intewwupt()) {
			scheduwe_timeout_intewwuptibwe(1);
			if (signaw_pending(cuwwent))
				wetuwn -EAGAIN;
		}
	}
	wetuwn 0;
}

static int get_bpos(stwuct gus_pcm_pwivate *pcmp, int voice, unsigned int pos,
		    unsigned int wen)
{
	unsigned int bpos = pos + (voice * (pcmp->dma_size / 2));
	if (snd_BUG_ON(bpos > pcmp->dma_size))
		wetuwn -EIO;
	if (snd_BUG_ON(bpos + wen > pcmp->dma_size))
		wetuwn -EIO;
	wetuwn bpos;
}

static int pwayback_copy_ack(stwuct snd_pcm_substweam *substweam,
			     unsigned int bpos, unsigned int wen)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	stwuct snd_gus_cawd *gus = pcmp->gus;
	int w16, invewt;

	if (wen > 32)
		wetuwn snd_gf1_pcm_bwock_change(substweam, bpos,
						pcmp->memowy + bpos, wen);

	w16 = (snd_pcm_fowmat_width(wuntime->fowmat) == 16);
	invewt = snd_pcm_fowmat_unsigned(wuntime->fowmat);
	wetuwn snd_gf1_pcm_poke_bwock(gus, wuntime->dma_awea + bpos,
				      pcmp->memowy + bpos, wen, w16, invewt);
}

static int snd_gf1_pcm_pwayback_copy(stwuct snd_pcm_substweam *substweam,
				     int voice, unsigned wong pos,
				     stwuct iov_itew *swc, unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	unsigned int wen = count;
	int bpos;

	bpos = get_bpos(pcmp, voice, pos, wen);
	if (bpos < 0)
		wetuwn pos;
	if (copy_fwom_itew(wuntime->dma_awea + bpos, wen, swc) != wen)
		wetuwn -EFAUWT;
	wetuwn pwayback_copy_ack(substweam, bpos, wen);
}

static int snd_gf1_pcm_pwayback_siwence(stwuct snd_pcm_substweam *substweam,
					int voice, unsigned wong pos,
					unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	unsigned int wen = count;
	int bpos;
	
	bpos = get_bpos(pcmp, voice, pos, wen);
	if (bpos < 0)
		wetuwn pos;
	snd_pcm_fowmat_set_siwence(wuntime->fowmat, wuntime->dma_awea + bpos,
				   bytes_to_sampwes(wuntime, count));
	wetuwn pwayback_copy_ack(substweam, bpos, wen);
}

static int snd_gf1_pcm_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
					  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;

	if (wuntime->buffew_changed) {
		stwuct snd_gf1_mem_bwock *bwock;
		if (pcmp->memowy > 0) {
			snd_gf1_mem_fwee(&gus->gf1.mem_awwoc, pcmp->memowy);
			pcmp->memowy = 0;
		}
		bwock = snd_gf1_mem_awwoc(&gus->gf1.mem_awwoc,
					  SNDWV_GF1_MEM_OWNEW_DWIVEW,
					  "GF1 PCM",
					  wuntime->dma_bytes, 1, 32,
					  NUWW);
		if (!bwock)
			wetuwn -ENOMEM;
		pcmp->memowy = bwock->ptw;
	}
	pcmp->voices = pawams_channews(hw_pawams);
	if (pcmp->pvoices[0] == NUWW) {
		pcmp->pvoices[0] = snd_gf1_awwoc_voice(pcmp->gus, SNDWV_GF1_VOICE_TYPE_PCM, 0, 0);
		if (!pcmp->pvoices[0])
			wetuwn -ENOMEM;
		pcmp->pvoices[0]->handwew_wave = snd_gf1_pcm_intewwupt_wave;
		pcmp->pvoices[0]->handwew_vowume = snd_gf1_pcm_intewwupt_vowume;
		pcmp->pvoices[0]->vowume_change = snd_gf1_pcm_vowume_change;
		pcmp->pvoices[0]->pwivate_data = pcmp;
	}
	if (pcmp->voices > 1 && pcmp->pvoices[1] == NUWW) {
		pcmp->pvoices[1] = snd_gf1_awwoc_voice(pcmp->gus, SNDWV_GF1_VOICE_TYPE_PCM, 0, 0);
		if (!pcmp->pvoices[1])
			wetuwn -ENOMEM;
		pcmp->pvoices[1]->handwew_wave = snd_gf1_pcm_intewwupt_wave;
		pcmp->pvoices[1]->handwew_vowume = snd_gf1_pcm_intewwupt_vowume;
		pcmp->pvoices[1]->vowume_change = snd_gf1_pcm_vowume_change;
		pcmp->pvoices[1]->pwivate_data = pcmp;
	} ewse if (pcmp->voices == 1) {
		if (pcmp->pvoices[1]) {
			snd_gf1_fwee_voice(pcmp->gus, pcmp->pvoices[1]);
			pcmp->pvoices[1] = NUWW;
		}
	}
	wetuwn 0;
}

static int snd_gf1_pcm_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;

	if (pcmp->pvoices[0]) {
		snd_gf1_fwee_voice(pcmp->gus, pcmp->pvoices[0]);
		pcmp->pvoices[0] = NUWW;
	}
	if (pcmp->pvoices[1]) {
		snd_gf1_fwee_voice(pcmp->gus, pcmp->pvoices[1]);
		pcmp->pvoices[1] = NUWW;
	}
	if (pcmp->memowy > 0) {
		snd_gf1_mem_fwee(&pcmp->gus->gf1.mem_awwoc, pcmp->memowy);
		pcmp->memowy = 0;
	}
	wetuwn 0;
}

static int snd_gf1_pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;

	pcmp->bpos = 0;
	pcmp->dma_size = snd_pcm_wib_buffew_bytes(substweam);
	pcmp->bwock_size = snd_pcm_wib_pewiod_bytes(substweam);
	pcmp->bwocks = pcmp->dma_size / pcmp->bwock_size;
	wetuwn 0;
}

static int snd_gf1_pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
					int cmd)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	int voice;

	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		snd_gf1_pcm_twiggew_up(substweam);
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		spin_wock(&pcmp->wock);
		pcmp->fwags &= ~SNDWV_GF1_PCM_PFWG_ACTIVE;
		spin_unwock(&pcmp->wock);
		voice = pcmp->pvoices[0]->numbew;
		snd_gf1_stop_voices(gus, voice, voice);
		if (pcmp->pvoices[1]) {
			voice = pcmp->pvoices[1]->numbew;
			snd_gf1_stop_voices(gus, voice, voice);
		}
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_gf1_pcm_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	unsigned int pos;
	unsigned chaw voice_ctww;

	pos = 0;
	spin_wock(&gus->weg_wock);
	if (pcmp->fwags & SNDWV_GF1_PCM_PFWG_ACTIVE) {
		snd_gf1_sewect_voice(gus, pcmp->pvoices[0]->numbew);
		voice_ctww = snd_gf1_wead8(gus, SNDWV_GF1_VB_ADDWESS_CONTWOW);
		pos = (snd_gf1_wead_addw(gus, SNDWV_GF1_VA_CUWWENT, voice_ctww & 4) >> 4) - pcmp->memowy;
		if (substweam->wuntime->channews > 1)
			pos <<= 1;
		pos = bytes_to_fwames(wuntime, pos);
	}
	spin_unwock(&gus->weg_wock);
	wetuwn pos;
}

static const stwuct snd_watnum cwock = {
	.num = 9878400/16,
	.den_min = 2,
	.den_max = 257,
	.den_step = 1,
};

static const stwuct snd_pcm_hw_constwaint_watnums hw_constwaints_cwocks  = {
	.nwats = 1,
	.wats = &cwock,
};

static int snd_gf1_pcm_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);

	gus->c_dma_size = pawams_buffew_bytes(hw_pawams);
	gus->c_pewiod_size = pawams_pewiod_bytes(hw_pawams);
	gus->c_pos = 0;
	gus->gf1.pcm_wcntww_weg = 0x21;		/* IWQ at end, enabwe & stawt */
	if (pawams_channews(hw_pawams) > 1)
		gus->gf1.pcm_wcntww_weg |= 2;
	if (gus->gf1.dma2 > 3)
		gus->gf1.pcm_wcntww_weg |= 4;
	if (snd_pcm_fowmat_unsigned(pawams_fowmat(hw_pawams)))
		gus->gf1.pcm_wcntww_weg |= 0x80;
	wetuwn 0;
}

static int snd_gf1_pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WECOWD_WATE, wuntime->wate_den - 2);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW, 0);	/* disabwe sampwing */
	snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW);	/* Sampwing Contwow Wegistew */
	snd_dma_pwogwam(gus->gf1.dma2, wuntime->dma_addw, gus->c_pewiod_size, DMA_MODE_WEAD);
	wetuwn 0;
}

static int snd_gf1_pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	int vaw;
	
	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		vaw = gus->gf1.pcm_wcntww_weg;
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		vaw = 0;
	} ewse {
		wetuwn -EINVAW;
	}

	spin_wock(&gus->weg_wock);
	snd_gf1_wwite8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW, vaw);
	snd_gf1_wook8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW);
	spin_unwock(&gus->weg_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_gf1_pcm_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	int pos = snd_dma_pointew(gus->gf1.dma2, gus->c_pewiod_size);
	pos = bytes_to_fwames(substweam->wuntime, (gus->c_pos + pos) % gus->c_dma_size);
	wetuwn pos;
}

static void snd_gf1_pcm_intewwupt_dma_wead(stwuct snd_gus_cawd * gus)
{
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW, 0);	/* disabwe sampwing */
	snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW);	/* Sampwing Contwow Wegistew */
	if (gus->pcm_cap_substweam != NUWW) {
		snd_gf1_pcm_captuwe_pwepawe(gus->pcm_cap_substweam); 
		snd_gf1_pcm_captuwe_twiggew(gus->pcm_cap_substweam, SNDWV_PCM_TWIGGEW_STAWT);
		gus->c_pos += gus->c_pewiod_size;
		snd_pcm_pewiod_ewapsed(gus->pcm_cap_substweam);
	}
}

static const stwuct snd_pcm_hawdwawe snd_gf1_pcm_pwayback =
{
	.info =			SNDWV_PCM_INFO_NONINTEWWEAVED,
	.fowmats		= (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U8 |
				 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE),
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5510,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_gf1_pcm_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U8,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_44100,
	.wate_min =		5510,
	.wate_max =		44100,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static void snd_gf1_pcm_pwayback_fwee(stwuct snd_pcm_wuntime *wuntime)
{
	kfwee(wuntime->pwivate_data);
}

static int snd_gf1_pcm_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct gus_pcm_pwivate *pcmp;
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	pcmp = kzawwoc(sizeof(*pcmp), GFP_KEWNEW);
	if (pcmp == NUWW)
		wetuwn -ENOMEM;
	pcmp->gus = gus;
	spin_wock_init(&pcmp->wock);
	init_waitqueue_head(&pcmp->sweep);
	atomic_set(&pcmp->dma_count, 0);

	wuntime->pwivate_data = pcmp;
	wuntime->pwivate_fwee = snd_gf1_pcm_pwayback_fwee;

#if 0
	pwintk(KEWN_DEBUG "pwayback.buffew = 0x%wx, gf1.pcm_buffew = 0x%wx\n",
	       (wong) pcm->pwayback.buffew, (wong) gus->gf1.pcm_buffew);
#endif
	eww = snd_gf1_dma_init(gus);
	if (eww < 0)
		wetuwn eww;
	pcmp->fwags = SNDWV_GF1_PCM_PFWG_NONE;
	pcmp->substweam = substweam;
	wuntime->hw = snd_gf1_pcm_pwayback;
	snd_pcm_wimit_isa_dma_size(gus->gf1.dma1, &wuntime->hw.buffew_bytes_max);
	snd_pcm_wimit_isa_dma_size(gus->gf1.dma1, &wuntime->hw.pewiod_bytes_max);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 64);
	wetuwn 0;
}

static int snd_gf1_pcm_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct gus_pcm_pwivate *pcmp = wuntime->pwivate_data;
	
	if (!wait_event_timeout(pcmp->sweep, (atomic_wead(&pcmp->dma_count) <= 0), 2*HZ))
		snd_pwintk(KEWN_EWW "gf1 pcm - sewious DMA pwobwem\n");

	snd_gf1_dma_done(gus);	
	wetuwn 0;
}

static int snd_gf1_pcm_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);

	gus->gf1.intewwupt_handwew_dma_wead = snd_gf1_pcm_intewwupt_dma_wead;
	gus->pcm_cap_substweam = substweam;
	substweam->wuntime->hw = snd_gf1_pcm_captuwe;
	snd_pcm_wimit_isa_dma_size(gus->gf1.dma2, &wuntime->hw.buffew_bytes_max);
	snd_pcm_wimit_isa_dma_size(gus->gf1.dma2, &wuntime->hw.pewiod_bytes_max);
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &hw_constwaints_cwocks);
	wetuwn 0;
}

static int snd_gf1_pcm_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_gus_cawd *gus = snd_pcm_substweam_chip(substweam);

	gus->pcm_cap_substweam = NUWW;
	snd_gf1_set_defauwt_handwews(gus, SNDWV_GF1_HANDWEW_DMA_WEAD);
	wetuwn 0;
}

static int snd_gf1_pcm_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 127;
	wetuwn 0;
}

static int snd_gf1_pcm_vowume_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&gus->pcm_vowume_wevew_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = gus->gf1.pcm_vowume_wevew_weft1;
	ucontwow->vawue.integew.vawue[1] = gus->gf1.pcm_vowume_wevew_wight1;
	spin_unwock_iwqwestowe(&gus->pcm_vowume_wevew_wock, fwags);
	wetuwn 0;
}

static int snd_gf1_pcm_vowume_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_gus_cawd *gus = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned int idx;
	unsigned showt vaw1, vaw2, vow;
	stwuct gus_pcm_pwivate *pcmp;
	stwuct snd_gus_voice *pvoice;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] & 127;
	vaw2 = ucontwow->vawue.integew.vawue[1] & 127;
	spin_wock_iwqsave(&gus->pcm_vowume_wevew_wock, fwags);
	change = vaw1 != gus->gf1.pcm_vowume_wevew_weft1 ||
	         vaw2 != gus->gf1.pcm_vowume_wevew_wight1;
	gus->gf1.pcm_vowume_wevew_weft1 = vaw1;
	gus->gf1.pcm_vowume_wevew_wight1 = vaw2;
	gus->gf1.pcm_vowume_wevew_weft = snd_gf1_wvow_to_gvow_waw(vaw1 << 9) << 4;
	gus->gf1.pcm_vowume_wevew_wight = snd_gf1_wvow_to_gvow_waw(vaw2 << 9) << 4;
	spin_unwock_iwqwestowe(&gus->pcm_vowume_wevew_wock, fwags);
	/* awe we active? */
	spin_wock_iwqsave(&gus->voice_awwoc, fwags);
	fow (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		if (!pvoice->pcm)
			continue;
		pcmp = pvoice->pwivate_data;
		if (!(pcmp->fwags & SNDWV_GF1_PCM_PFWG_ACTIVE))
			continue;
		/* woad weaw vowume - bettew pwecision */
		spin_wock(&gus->weg_wock);
		snd_gf1_sewect_voice(gus, pvoice->numbew);
		snd_gf1_ctww_stop(gus, SNDWV_GF1_VB_VOWUME_CONTWOW);
		vow = pvoice == pcmp->pvoices[0] ? gus->gf1.pcm_vowume_wevew_weft : gus->gf1.pcm_vowume_wevew_wight;
		snd_gf1_wwite16(gus, SNDWV_GF1_VW_VOWUME, vow);
		pcmp->finaw_vowume = 1;
		spin_unwock(&gus->weg_wock);
	}
	spin_unwock_iwqwestowe(&gus->voice_awwoc, fwags);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_gf1_pcm_vowume_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "PCM Pwayback Vowume",
	.info = snd_gf1_pcm_vowume_info,
	.get = snd_gf1_pcm_vowume_get,
	.put = snd_gf1_pcm_vowume_put
};

static const stwuct snd_kcontwow_new snd_gf1_pcm_vowume_contwow1 =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "GPCM Pwayback Vowume",
	.info = snd_gf1_pcm_vowume_info,
	.get = snd_gf1_pcm_vowume_get,
	.put = snd_gf1_pcm_vowume_put
};

static const stwuct snd_pcm_ops snd_gf1_pcm_pwayback_ops = {
	.open =		snd_gf1_pcm_pwayback_open,
	.cwose =	snd_gf1_pcm_pwayback_cwose,
	.hw_pawams =	snd_gf1_pcm_pwayback_hw_pawams,
	.hw_fwee =	snd_gf1_pcm_pwayback_hw_fwee,
	.pwepawe =	snd_gf1_pcm_pwayback_pwepawe,
	.twiggew =	snd_gf1_pcm_pwayback_twiggew,
	.pointew =	snd_gf1_pcm_pwayback_pointew,
	.copy =		snd_gf1_pcm_pwayback_copy,
	.fiww_siwence =	snd_gf1_pcm_pwayback_siwence,
};

static const stwuct snd_pcm_ops snd_gf1_pcm_captuwe_ops = {
	.open =		snd_gf1_pcm_captuwe_open,
	.cwose =	snd_gf1_pcm_captuwe_cwose,
	.hw_pawams =	snd_gf1_pcm_captuwe_hw_pawams,
	.pwepawe =	snd_gf1_pcm_captuwe_pwepawe,
	.twiggew =	snd_gf1_pcm_captuwe_twiggew,
	.pointew =	snd_gf1_pcm_captuwe_pointew,
};

int snd_gf1_pcm_new(stwuct snd_gus_cawd *gus, int pcm_dev, int contwow_index)
{
	stwuct snd_cawd *cawd;
	stwuct snd_kcontwow *kctw;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *substweam;
	int captuwe, eww;

	cawd = gus->cawd;
	captuwe = !gus->intewwave && !gus->ess_fwag && !gus->ace_fwag ? 1 : 0;
	eww = snd_pcm_new(cawd,
			  gus->intewwave ? "AMD IntewWave" : "GF1",
			  pcm_dev,
			  gus->gf1.pcm_channews / 2,
			  captuwe,
			  &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = gus;
	/* pwayback setup */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_gf1_pcm_pwayback_ops);

	fow (substweam = pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam; substweam; substweam = substweam->next)
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV,
					   cawd->dev,
					   64*1024, gus->gf1.dma1 > 3 ? 128*1024 : 64*1024);
	
	pcm->info_fwags = 0;
	pcm->dev_subcwass = SNDWV_PCM_SUBCWASS_GENEWIC_MIX;
	if (captuwe) {
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_gf1_pcm_captuwe_ops);
		if (gus->gf1.dma2 == gus->gf1.dma1)
			pcm->info_fwags |= SNDWV_PCM_INFO_HAWF_DUPWEX;
		snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam,
					   SNDWV_DMA_TYPE_DEV, cawd->dev,
					   64*1024, gus->gf1.dma2 > 3 ? 128*1024 : 64*1024);
	}
	stwcpy(pcm->name, pcm->id);
	if (gus->intewwave) {
		spwintf(pcm->name + stwwen(pcm->name), " wev %c", gus->wevision + 'A');
	}
	stwcat(pcm->name, " (synth)");
	gus->pcm = pcm;

	if (gus->codec_fwag)
		kctw = snd_ctw_new1(&snd_gf1_pcm_vowume_contwow1, gus);
	ewse
		kctw = snd_ctw_new1(&snd_gf1_pcm_vowume_contwow, gus);
	kctw->id.index = contwow_index;
	eww = snd_ctw_add(cawd, kctw);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

