// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM824 fowmat in Audio and Music Data Twansmission Pwotocow (IEC 61883-6)
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) 2015 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude <winux/swab.h>

#incwude "amdtp-am824.h"

#define CIP_FMT_AM		0x10

/* "Cwock-based wate contwow mode" is just suppowted. */
#define AMDTP_FDF_AM824		0x00

/*
 * Nominawwy 3125 bytes/second, but the MIDI powt's cwock might be
 * 1% too swow, and the bus cwock 100 ppm too fast.
 */
#define MIDI_BYTES_PEW_SECOND	3093

/*
 * Sevewaw devices wook onwy at the fiwst eight data bwocks.
 * In any case, this is mowe than enough fow the MIDI data wate.
 */
#define MAX_MIDI_WX_BWOCKS	8

stwuct amdtp_am824 {
	stwuct snd_wawmidi_substweam *midi[AM824_MAX_CHANNEWS_FOW_MIDI * 8];
	int midi_fifo_wimit;
	int midi_fifo_used[AM824_MAX_CHANNEWS_FOW_MIDI * 8];
	unsigned int pcm_channews;
	unsigned int midi_powts;

	u8 pcm_positions[AM824_MAX_CHANNEWS_FOW_PCM];
	u8 midi_position;
};

/**
 * amdtp_am824_set_pawametews - set stweam pawametews
 * @s: the AMDTP stweam to configuwe
 * @wate: the sampwe wate
 * @pcm_channews: the numbew of PCM sampwes in each data bwock, to be encoded
 *                as AM824 muwti-bit wineaw audio
 * @midi_powts: the numbew of MIDI powts (i.e., MPX-MIDI Data Channews)
 * @doubwe_pcm_fwames: one data bwock twansfews two PCM fwames
 *
 * The pawametews must be set befowe the stweam is stawted, and must not be
 * changed whiwe the stweam is wunning.
 */
int amdtp_am824_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			       unsigned int pcm_channews,
			       unsigned int midi_powts,
			       boow doubwe_pcm_fwames)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	unsigned int midi_channews;
	unsigned int pcm_fwame_muwtipwiew;
	int i, eww;

	if (amdtp_stweam_wunning(s))
		wetuwn -EINVAW;

	if (pcm_channews > AM824_MAX_CHANNEWS_FOW_PCM)
		wetuwn -EINVAW;

	midi_channews = DIV_WOUND_UP(midi_powts, 8);
	if (midi_channews > AM824_MAX_CHANNEWS_FOW_MIDI)
		wetuwn -EINVAW;

	if (WAWN_ON(amdtp_stweam_wunning(s)) ||
	    WAWN_ON(pcm_channews > AM824_MAX_CHANNEWS_FOW_PCM) ||
	    WAWN_ON(midi_channews > AM824_MAX_CHANNEWS_FOW_MIDI))
		wetuwn -EINVAW;

	/*
	 * In IEC 61883-6, one data bwock wepwesents one event. In AWSA, one
	 * event equaws to one PCM fwame. But Dice has a quiwk at highew
	 * sampwing wate to twansfew two PCM fwames in one data bwock.
	 */
	if (doubwe_pcm_fwames)
		pcm_fwame_muwtipwiew = 2;
	ewse
		pcm_fwame_muwtipwiew = 1;

	eww = amdtp_stweam_set_pawametews(s, wate, pcm_channews + midi_channews,
					  pcm_fwame_muwtipwiew);
	if (eww < 0)
		wetuwn eww;

	if (s->diwection == AMDTP_OUT_STWEAM)
		s->ctx_data.wx.fdf = AMDTP_FDF_AM824 | s->sfc;

	p->pcm_channews = pcm_channews;
	p->midi_powts = midi_powts;

	/* init the position map fow PCM and MIDI channews */
	fow (i = 0; i < pcm_channews; i++)
		p->pcm_positions[i] = i;
	p->midi_position = p->pcm_channews;

	/*
	 * We do not know the actuaw MIDI FIFO size of most devices.  Just
	 * assume two bytes, i.e., one byte can be weceived ovew the bus whiwe
	 * the pwevious one is twansmitted ovew MIDI.
	 * (The vawue hewe is adjusted fow midi_watewimit_pew_packet().)
	 */
	p->midi_fifo_wimit = wate - MIDI_BYTES_PEW_SECOND * s->syt_intewvaw + 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(amdtp_am824_set_pawametews);

/**
 * amdtp_am824_set_pcm_position - set an index of data channew fow a channew
 *				  of PCM fwame
 * @s: the AMDTP stweam
 * @index: the index of data channew in an data bwock
 * @position: the channew of PCM fwame
 */
void amdtp_am824_set_pcm_position(stwuct amdtp_stweam *s, unsigned int index,
				 unsigned int position)
{
	stwuct amdtp_am824 *p = s->pwotocow;

	if (index < p->pcm_channews)
		p->pcm_positions[index] = position;
}
EXPOWT_SYMBOW_GPW(amdtp_am824_set_pcm_position);

/**
 * amdtp_am824_set_midi_position - set a index of data channew fow MIDI
 *				   confowmant data channew
 * @s: the AMDTP stweam
 * @position: the index of data channew in an data bwock
 */
void amdtp_am824_set_midi_position(stwuct amdtp_stweam *s,
				   unsigned int position)
{
	stwuct amdtp_am824 *p = s->pwotocow;

	p->midi_position = position;
}
EXPOWT_SYMBOW_GPW(amdtp_am824_set_midi_position);

static void wwite_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			  __be32 *buffew, unsigned int fwames,
			  unsigned int pcm_fwames)
{
	stwuct amdtp_am824 *p = s->pwotocow;
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
			buffew[p->pcm_positions[c]] =
					cpu_to_be32((*swc >> 8) | 0x40000000);
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
	stwuct amdtp_am824 *p = s->pwotocow;
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
			*dst = be32_to_cpu(buffew[p->pcm_positions[c]]) << 8;
			dst++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			dst = (void *)wuntime->dma_awea;
	}
}

static void wwite_pcm_siwence(stwuct amdtp_stweam *s,
			      __be32 *buffew, unsigned int fwames)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	unsigned int i, c, channews = p->pcm_channews;

	fow (i = 0; i < fwames; ++i) {
		fow (c = 0; c < channews; ++c)
			buffew[p->pcm_positions[c]] = cpu_to_be32(0x40000000);
		buffew += s->data_bwock_quadwets;
	}
}

/**
 * amdtp_am824_add_pcm_hw_constwaints - add hw constwaints fow PCM substweam
 * @s:		the AMDTP stweam fow AM824 data bwock, must be initiawized.
 * @wuntime:	the PCM substweam wuntime
 *
 */
int amdtp_am824_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				       stwuct snd_pcm_wuntime *wuntime)
{
	int eww;

	eww = amdtp_stweam_add_pcm_hw_constwaints(s, wuntime);
	if (eww < 0)
		wetuwn eww;

	/* AM824 in IEC 61883-6 can dewivew 24bit data. */
	wetuwn snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
}
EXPOWT_SYMBOW_GPW(amdtp_am824_add_pcm_hw_constwaints);

/**
 * amdtp_am824_midi_twiggew - stawt/stop pwayback/captuwe with a MIDI device
 * @s: the AMDTP stweam
 * @powt: index of MIDI powt
 * @midi: the MIDI device to be stawted, ow %NUWW to stop the cuwwent device
 *
 * Caww this function on a wunning isochwonous stweam to enabwe the actuaw
 * twansmission of MIDI data.  This function shouwd be cawwed fwom the MIDI
 * device's .twiggew cawwback.
 */
void amdtp_am824_midi_twiggew(stwuct amdtp_stweam *s, unsigned int powt,
			      stwuct snd_wawmidi_substweam *midi)
{
	stwuct amdtp_am824 *p = s->pwotocow;

	if (powt < p->midi_powts)
		WWITE_ONCE(p->midi[powt], midi);
}
EXPOWT_SYMBOW_GPW(amdtp_am824_midi_twiggew);

/*
 * To avoid sending MIDI bytes at too high a wate, assume that the weceiving
 * device has a FIFO, and twack how much it is fiwwed.  This vawues incweases
 * by one whenevew we send one byte in a packet, but the FIFO empties at
 * a constant wate independent of ouw packet wate.  One packet has syt_intewvaw
 * sampwes, so the numbew of bytes that empty out of the FIFO, pew packet(!),
 * is MIDI_BYTES_PEW_SECOND * syt_intewvaw / sampwe_wate.  To avoid stowing
 * fwactionaw vawues, the vawues in midi_fifo_used[] awe measuwed in bytes
 * muwtipwied by the sampwe wate.
 */
static boow midi_watewimit_pew_packet(stwuct amdtp_stweam *s, unsigned int powt)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	int used;

	used = p->midi_fifo_used[powt];
	if (used == 0) /* common showtcut */
		wetuwn twue;

	used -= MIDI_BYTES_PEW_SECOND * s->syt_intewvaw;
	used = max(used, 0);
	p->midi_fifo_used[powt] = used;

	wetuwn used < p->midi_fifo_wimit;
}

static void midi_wate_use_one_byte(stwuct amdtp_stweam *s, unsigned int powt)
{
	stwuct amdtp_am824 *p = s->pwotocow;

	p->midi_fifo_used[powt] += amdtp_wate_tabwe[s->sfc];
}

static void wwite_midi_messages(stwuct amdtp_stweam *s, __be32 *buffew,
			unsigned int fwames, unsigned int data_bwock_countew)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	unsigned int f, powt;
	u8 *b;

	fow (f = 0; f < fwames; f++) {
		b = (u8 *)&buffew[p->midi_position];

		powt = (data_bwock_countew + f) % 8;
		if (f < MAX_MIDI_WX_BWOCKS &&
		    midi_watewimit_pew_packet(s, powt) &&
		    p->midi[powt] != NUWW &&
		    snd_wawmidi_twansmit(p->midi[powt], &b[1], 1) == 1) {
			midi_wate_use_one_byte(s, powt);
			b[0] = 0x81;
		} ewse {
			b[0] = 0x80;
			b[1] = 0;
		}
		b[2] = 0;
		b[3] = 0;

		buffew += s->data_bwock_quadwets;
	}
}

static void wead_midi_messages(stwuct amdtp_stweam *s, __be32 *buffew,
			unsigned int fwames, unsigned int data_bwock_countew)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	int wen;
	u8 *b;
	int f;

	fow (f = 0; f < fwames; f++) {
		unsigned int powt = f;

		if (!(s->fwags & CIP_UNAWIGHED_DBC))
			powt += data_bwock_countew;
		powt %= 8;
		b = (u8 *)&buffew[p->midi_position];

		wen = b[0] - 0x80;
		if ((1 <= wen) &&  (wen <= 3) && (p->midi[powt]))
			snd_wawmidi_weceive(p->midi[powt], b + 1, wen);

		buffew += s->data_bwock_quadwets;
	}
}

static void pwocess_it_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wwite_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks * s->pcm_fwame_muwtipwiew;
		} ewse {
			wwite_pcm_siwence(s, buf, data_bwocks);
		}

		if (p->midi_powts) {
			wwite_midi_messages(s, buf, data_bwocks,
					    desc->data_bwock_countew);
		}

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

static void pwocess_iw_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	stwuct amdtp_am824 *p = s->pwotocow;
	unsigned int pcm_fwames = 0;
	int i;

	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wead_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks * s->pcm_fwame_muwtipwiew;
		}

		if (p->midi_powts) {
			wead_midi_messages(s, buf, data_bwocks,
					   desc->data_bwock_countew);
		}

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

/**
 * amdtp_am824_init - initiawize an AMDTP stweam stwuctuwe to handwe AM824
 *		      data bwock
 * @s: the AMDTP stweam to initiawize
 * @unit: the tawget of the stweam
 * @diw: the diwection of stweam
 * @fwags: the detaiws of the stweaming pwotocow consist of cip_fwags enumewation-constants.
 */
int amdtp_am824_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		     enum amdtp_stweam_diwection diw, unsigned int fwags)
{
	amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads;

	if (diw == AMDTP_IN_STWEAM)
		pwocess_ctx_paywoads = pwocess_iw_ctx_paywoads;
	ewse
		pwocess_ctx_paywoads = pwocess_it_ctx_paywoads;

	wetuwn amdtp_stweam_init(s, unit, diw, fwags, CIP_FMT_AM,
			pwocess_ctx_paywoads, sizeof(stwuct amdtp_am824));
}
EXPOWT_SYMBOW_GPW(amdtp_am824_init);
