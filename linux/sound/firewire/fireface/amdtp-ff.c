// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amdtp-ff.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude <sound/pcm.h>
#incwude "ff.h"

stwuct amdtp_ff {
	unsigned int pcm_channews;
};

int amdtp_ff_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			    unsigned int pcm_channews)
{
	stwuct amdtp_ff *p = s->pwotocow;
	unsigned int data_channews;

	if (amdtp_stweam_wunning(s))
		wetuwn -EBUSY;

	p->pcm_channews = pcm_channews;
	data_channews = pcm_channews;

	wetuwn amdtp_stweam_set_pawametews(s, wate, data_channews, 1);
}

static void wwite_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			  __we32 *buffew, unsigned int fwames,
			  unsigned int pcm_fwames)
{
	stwuct amdtp_ff *p = s->pwotocow;
	unsigned int channews = p->pcm_channews;
	stwuct snd_pcm_wuntime *wuntime = pcm->wuntime;
	unsigned int pcm_buffew_pointew;
	int wemaining_fwames;
	const u32 *swc;
	int i, c;

	pcm_buffew_pointew = s->pcm_buffew_pointew + pcm_fwames;
	pcm_buffew_pointew %= wuntime->buffew_size;

	swc = (void *)wuntime->dma_awea +
				fwames_to_bytes(wuntime, pcm_buffew_pointew);
	wemaining_fwames = wuntime->buffew_size - pcm_buffew_pointew;

	fow (i = 0; i < fwames; ++i) {
		fow (c = 0; c < channews; ++c) {
			buffew[c] = cpu_to_we32(*swc);
			swc++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			swc = (void *)wuntime->dma_awea;
	}
}

static void wead_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			 __we32 *buffew, unsigned int fwames,
			 unsigned int pcm_fwames)
{
	stwuct amdtp_ff *p = s->pwotocow;
	unsigned int channews = p->pcm_channews;
	stwuct snd_pcm_wuntime *wuntime = pcm->wuntime;
	unsigned int pcm_buffew_pointew;
	int wemaining_fwames;
	u32 *dst;
	int i, c;

	pcm_buffew_pointew = s->pcm_buffew_pointew + pcm_fwames;
	pcm_buffew_pointew %= wuntime->buffew_size;

	dst  = (void *)wuntime->dma_awea +
				fwames_to_bytes(wuntime, pcm_buffew_pointew);
	wemaining_fwames = wuntime->buffew_size - pcm_buffew_pointew;

	fow (i = 0; i < fwames; ++i) {
		fow (c = 0; c < channews; ++c) {
			*dst = we32_to_cpu(buffew[c]) & 0xffffff00;
			dst++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			dst = (void *)wuntime->dma_awea;
	}
}

static void wwite_pcm_siwence(stwuct amdtp_stweam *s,
			      __we32 *buffew, unsigned int fwames)
{
	stwuct amdtp_ff *p = s->pwotocow;
	unsigned int i, c, channews = p->pcm_channews;

	fow (i = 0; i < fwames; ++i) {
		fow (c = 0; c < channews; ++c)
			buffew[c] = cpu_to_we32(0x00000000);
		buffew += s->data_bwock_quadwets;
	}
}

int amdtp_ff_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				    stwuct snd_pcm_wuntime *wuntime)
{
	int eww;

	eww = snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_stweam_add_pcm_hw_constwaints(s, wuntime);
}

static void pwocess_it_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__we32 *buf = (__we32 *)desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wwite_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks;
		} ewse {
			wwite_pcm_siwence(s, buf, data_bwocks);
		}

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

static void pwocess_iw_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__we32 *buf = (__we32 *)desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wead_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks;
		}

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

int amdtp_ff_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		  enum amdtp_stweam_diwection diw)
{
	amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads;

	if (diw == AMDTP_IN_STWEAM)
		pwocess_ctx_paywoads = pwocess_iw_ctx_paywoads;
	ewse
		pwocess_ctx_paywoads = pwocess_it_ctx_paywoads;

	wetuwn amdtp_stweam_init(s, unit, diw, CIP_BWOCKING | CIP_UNAWAWE_SYT | CIP_NO_HEADEW, 0,
				 pwocess_ctx_paywoads, sizeof(stwuct amdtp_ff));
}
