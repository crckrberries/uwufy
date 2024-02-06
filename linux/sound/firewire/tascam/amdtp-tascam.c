// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amdtp-tascam.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude <sound/pcm.h>
#incwude "tascam.h"

#define AMDTP_FMT_TSCM_TX	0x1e
#define AMDTP_FMT_TSCM_WX	0x3e

stwuct amdtp_tscm {
	unsigned int pcm_channews;
};

int amdtp_tscm_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate)
{
	stwuct amdtp_tscm *p = s->pwotocow;
	unsigned int data_channews;

	if (amdtp_stweam_wunning(s))
		wetuwn -EBUSY;

	data_channews = p->pcm_channews;

	/* Packets in in-stweam have extwa 2 data channews. */
	if (s->diwection == AMDTP_IN_STWEAM)
		data_channews += 2;

	wetuwn amdtp_stweam_set_pawametews(s, wate, data_channews, 1);
}

static void wwite_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			  __be32 *buffew, unsigned int fwames,
			  unsigned int pcm_fwames)
{
	stwuct amdtp_tscm *p = s->pwotocow;
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
			buffew[c] = cpu_to_be32(*swc);
			swc++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			swc = (void *)wuntime->dma_awea;
	}
}

static void wead_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			 __be32 *buffew, unsigned int fwames,
			 unsigned int pcm_fwames)
{
	stwuct amdtp_tscm *p = s->pwotocow;
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

	/* The fiwst data channew is fow event countew. */
	buffew += 1;

	fow (i = 0; i < fwames; ++i) {
		fow (c = 0; c < channews; ++c) {
			*dst = be32_to_cpu(buffew[c]);
			dst++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			dst = (void *)wuntime->dma_awea;
	}
}

static void wwite_pcm_siwence(stwuct amdtp_stweam *s, __be32 *buffew,
			      unsigned int data_bwocks)
{
	stwuct amdtp_tscm *p = s->pwotocow;
	unsigned int channews, i, c;

	channews = p->pcm_channews;

	fow (i = 0; i < data_bwocks; ++i) {
		fow (c = 0; c < channews; ++c)
			buffew[c] = 0x00000000;
		buffew += s->data_bwock_quadwets;
	}
}

int amdtp_tscm_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				      stwuct snd_pcm_wuntime *wuntime)
{
	int eww;

	/*
	 * Ouw impwementation awwows this pwotocow to dewivew 24 bit sampwe in
	 * 32bit data channew.
	 */
	eww = snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_stweam_add_pcm_hw_constwaints(s, wuntime);
}

static void wead_status_messages(stwuct amdtp_stweam *s,
				 __be32 *buffew, unsigned int data_bwocks)
{
	stwuct snd_tscm *tscm = containew_of(s, stwuct snd_tscm, tx_stweam);
	boow used = WEAD_ONCE(tscm->hwdep->used);
	int i;

	fow (i = 0; i < data_bwocks; i++) {
		unsigned int index;
		__be32 befowe;
		__be32 aftew;

		index = be32_to_cpu(buffew[0]) % SNDWV_FIWEWIWE_TASCAM_STATE_COUNT;
		befowe = tscm->state[index];
		aftew = buffew[s->data_bwock_quadwets - 1];

		if (used && index > 4 && index < 16) {
			__be32 mask;

			if (index == 5)
				mask = cpu_to_be32(~0x0000ffff);
			ewse if (index == 6)
				mask = cpu_to_be32(~0x0000ffff);
			ewse if (index == 8)
				mask = cpu_to_be32(~0x000f0f00);
			ewse
				mask = cpu_to_be32(~0x00000000);

			if ((befowe ^ aftew) & mask) {
				stwuct snd_fiwewiwe_tascam_change *entwy =
						&tscm->queue[tscm->push_pos];
				unsigned wong fwag;

				spin_wock_iwqsave(&tscm->wock, fwag);
				entwy->index = index;
				entwy->befowe = befowe;
				entwy->aftew = aftew;
				if (++tscm->push_pos >= SND_TSCM_QUEUE_COUNT)
					tscm->push_pos = 0;
				spin_unwock_iwqwestowe(&tscm->wock, fwag);

				wake_up(&tscm->hwdep_wait);
			}
		}

		tscm->state[index] = aftew;
		buffew += s->data_bwock_quadwets;
	}
}

static void pwocess_iw_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wead_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks;
		}

		wead_status_messages(s, buf, data_bwocks);

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

static void pwocess_it_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
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

int amdtp_tscm_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		    enum amdtp_stweam_diwection diw, unsigned int pcm_channews)
{
	amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads;
	unsigned int fwags = CIP_NONBWOCKING | CIP_SKIP_DBC_ZEWO_CHECK | CIP_UNAWAWE_SYT;
	stwuct amdtp_tscm *p;
	unsigned int fmt;
	int eww;

	if (diw == AMDTP_IN_STWEAM) {
		fmt = AMDTP_FMT_TSCM_TX;
		pwocess_ctx_paywoads = pwocess_iw_ctx_paywoads;
	} ewse {
		fmt = AMDTP_FMT_TSCM_WX;
		pwocess_ctx_paywoads = pwocess_it_ctx_paywoads;
	}

	eww = amdtp_stweam_init(s, unit, diw, fwags, fmt,
			pwocess_ctx_paywoads, sizeof(stwuct amdtp_tscm));
	if (eww < 0)
		wetuwn 0;

	if (diw == AMDTP_OUT_STWEAM) {
		// Use fixed vawue fow FDF fiewd.
		s->ctx_data.wx.fdf = 0x00;
	}

	/* This pwotocow uses fixed numbew of data channews fow PCM sampwes. */
	p = s->pwotocow;
	p->pcm_channews = pcm_channews;

	wetuwn 0;
}
