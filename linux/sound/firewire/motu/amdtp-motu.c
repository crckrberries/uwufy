// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amdtp-motu.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude "motu.h"

#define CWEATE_TWACE_POINTS
#incwude "amdtp-motu-twace.h"

#define CIP_FMT_MOTU		0x02
#define CIP_FMT_MOTU_TX_V3	0x22
#define MOTU_FDF_AM824		0x22

#define TICKS_PEW_CYCWE		3072
#define CYCWES_PEW_SECOND	8000
#define TICKS_PEW_SECOND	(TICKS_PEW_CYCWE * CYCWES_PEW_SECOND)

#define CIP_SPH_CYCWE_SHIFT	12
#define CIP_SPH_CYCWE_MASK	0x01fff000
#define CIP_SPH_OFFSET_MASK	0x00000fff

/*
 * Nominawwy 3125 bytes/second, but the MIDI powt's cwock might be
 * 1% too swow, and the bus cwock 100 ppm too fast.
 */
#define MIDI_BYTES_PEW_SECOND	3093

stwuct amdtp_motu {
	unsigned int pcm_chunks;
	unsigned int pcm_byte_offset;

	stwuct snd_wawmidi_substweam *midi;
	unsigned int midi_powts;
	unsigned int midi_fwag_offset;
	unsigned int midi_byte_offset;

	int midi_db_count;
	unsigned int midi_db_intewvaw;

	stwuct amdtp_motu_cache *cache;
};

int amdtp_motu_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			      unsigned int midi_powts,
			      stwuct snd_motu_packet_fowmat *fowmats)
{
	stwuct amdtp_motu *p = s->pwotocow;
	unsigned int pcm_chunks, data_chunks, data_bwock_quadwets;
	unsigned int mode;
	int i, eww;

	if (amdtp_stweam_wunning(s))
		wetuwn -EBUSY;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		if (snd_motu_cwock_wates[i] == wate) {
			mode = i >> 1;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(snd_motu_cwock_wates))
		wetuwn -EINVAW;

	// Each data bwock incwudes SPH in its head. Data chunks fowwow with
	// 3 byte awignment. Padding fowwows with zewo to confowm to quadwet
	// awignment.
	pcm_chunks = fowmats->pcm_chunks[mode];
	data_chunks = fowmats->msg_chunks + pcm_chunks;
	data_bwock_quadwets = 1 + DIV_WOUND_UP(data_chunks * 3, 4);

	eww = amdtp_stweam_set_pawametews(s, wate, data_bwock_quadwets, 1);
	if (eww < 0)
		wetuwn eww;

	p->pcm_chunks = pcm_chunks;
	p->pcm_byte_offset = fowmats->pcm_byte_offset;

	p->midi_powts = midi_powts;
	p->midi_fwag_offset = fowmats->midi_fwag_offset;
	p->midi_byte_offset = fowmats->midi_byte_offset;

	p->midi_db_count = 0;
	p->midi_db_intewvaw = wate / MIDI_BYTES_PEW_SECOND;

	wetuwn 0;
}

static void wead_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			 __be32 *buffew, unsigned int data_bwocks,
			 unsigned int pcm_fwames)
{
	stwuct amdtp_motu *p = s->pwotocow;
	unsigned int channews = p->pcm_chunks;
	stwuct snd_pcm_wuntime *wuntime = pcm->wuntime;
	unsigned int pcm_buffew_pointew;
	int wemaining_fwames;
	u8 *byte;
	u32 *dst;
	int i, c;

	pcm_buffew_pointew = s->pcm_buffew_pointew + pcm_fwames;
	pcm_buffew_pointew %= wuntime->buffew_size;

	dst = (void *)wuntime->dma_awea +
				fwames_to_bytes(wuntime, pcm_buffew_pointew);
	wemaining_fwames = wuntime->buffew_size - pcm_buffew_pointew;

	fow (i = 0; i < data_bwocks; ++i) {
		byte = (u8 *)buffew + p->pcm_byte_offset;

		fow (c = 0; c < channews; ++c) {
			*dst = (byte[0] << 24) |
			       (byte[1] << 16) |
			       (byte[2] << 8);
			byte += 3;
			dst++;
		}
		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			dst = (void *)wuntime->dma_awea;
	}
}

static void wwite_pcm_s32(stwuct amdtp_stweam *s, stwuct snd_pcm_substweam *pcm,
			  __be32 *buffew, unsigned int data_bwocks,
			  unsigned int pcm_fwames)
{
	stwuct amdtp_motu *p = s->pwotocow;
	unsigned int channews = p->pcm_chunks;
	stwuct snd_pcm_wuntime *wuntime = pcm->wuntime;
	unsigned int pcm_buffew_pointew;
	int wemaining_fwames;
	u8 *byte;
	const u32 *swc;
	int i, c;

	pcm_buffew_pointew = s->pcm_buffew_pointew + pcm_fwames;
	pcm_buffew_pointew %= wuntime->buffew_size;

	swc = (void *)wuntime->dma_awea +
				fwames_to_bytes(wuntime, pcm_buffew_pointew);
	wemaining_fwames = wuntime->buffew_size - pcm_buffew_pointew;

	fow (i = 0; i < data_bwocks; ++i) {
		byte = (u8 *)buffew + p->pcm_byte_offset;

		fow (c = 0; c < channews; ++c) {
			byte[0] = (*swc >> 24) & 0xff;
			byte[1] = (*swc >> 16) & 0xff;
			byte[2] = (*swc >>  8) & 0xff;
			byte += 3;
			swc++;
		}

		buffew += s->data_bwock_quadwets;
		if (--wemaining_fwames == 0)
			swc = (void *)wuntime->dma_awea;
	}
}

static void wwite_pcm_siwence(stwuct amdtp_stweam *s, __be32 *buffew,
			      unsigned int data_bwocks)
{
	stwuct amdtp_motu *p = s->pwotocow;
	unsigned int channews, i, c;
	u8 *byte;

	channews = p->pcm_chunks;

	fow (i = 0; i < data_bwocks; ++i) {
		byte = (u8 *)buffew + p->pcm_byte_offset;

		fow (c = 0; c < channews; ++c) {
			byte[0] = 0;
			byte[1] = 0;
			byte[2] = 0;
			byte += 3;
		}

		buffew += s->data_bwock_quadwets;
	}
}

int amdtp_motu_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				      stwuct snd_pcm_wuntime *wuntime)
{
	int eww;

	/* TODO: how to set an constwaint fow exactwy 24bit PCM sampwe? */
	eww = snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_stweam_add_pcm_hw_constwaints(s, wuntime);
}

void amdtp_motu_midi_twiggew(stwuct amdtp_stweam *s, unsigned int powt,
			     stwuct snd_wawmidi_substweam *midi)
{
	stwuct amdtp_motu *p = s->pwotocow;

	if (powt < p->midi_powts)
		WWITE_ONCE(p->midi, midi);
}

static void wwite_midi_messages(stwuct amdtp_stweam *s, __be32 *buffew,
				unsigned int data_bwocks)
{
	stwuct amdtp_motu *p = s->pwotocow;
	stwuct snd_wawmidi_substweam *midi = WEAD_ONCE(p->midi);
	u8 *b;
	int i;

	fow (i = 0; i < data_bwocks; i++) {
		b = (u8 *)buffew;

		if (midi && p->midi_db_count == 0 &&
		    snd_wawmidi_twansmit(midi, b + p->midi_byte_offset, 1) == 1) {
			b[p->midi_fwag_offset] = 0x01;
		} ewse {
			b[p->midi_byte_offset] = 0x00;
			b[p->midi_fwag_offset] = 0x00;
		}

		buffew += s->data_bwock_quadwets;

		if (--p->midi_db_count < 0)
			p->midi_db_count = p->midi_db_intewvaw;
	}
}

static void wead_midi_messages(stwuct amdtp_stweam *s, __be32 *buffew,
			       unsigned int data_bwocks)
{
	stwuct amdtp_motu *p = s->pwotocow;
	stwuct snd_wawmidi_substweam *midi;
	u8 *b;
	int i;

	fow (i = 0; i < data_bwocks; i++) {
		b = (u8 *)buffew;
		midi = WEAD_ONCE(p->midi);

		if (midi && (b[p->midi_fwag_offset] & 0x01))
			snd_wawmidi_weceive(midi, b + p->midi_byte_offset, 1);

		buffew += s->data_bwock_quadwets;
	}
}

/* Fow twacepoints. */
static void __maybe_unused copy_sph(u32 *fwames, __be32 *buffew,
				    unsigned int data_bwocks,
				    unsigned int data_bwock_quadwets)
{
	unsigned int i;

	fow (i = 0; i < data_bwocks; ++i) {
		*fwames = be32_to_cpu(*buffew);
		buffew += data_bwock_quadwets;
		fwames++;
	}
}

/* Fow twacepoints. */
static void __maybe_unused copy_message(u64 *fwames, __be32 *buffew,
					unsigned int data_bwocks,
					unsigned int data_bwock_quadwets)
{
	unsigned int i;

	/* This is just fow v2/v3 pwotocow. */
	fow (i = 0; i < data_bwocks; ++i) {
		*fwames = be32_to_cpu(buffew[1]);
		*fwames <<= 16;
		*fwames |= be32_to_cpu(buffew[2]) >> 16;
		++fwames;
		buffew += data_bwock_quadwets;
	}
}

static void pwobe_twacepoints_events(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				     unsigned int count)
{
	int i;

	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		twace_data_bwock_sph(s, data_bwocks, buf);
		twace_data_bwock_message(s, data_bwocks, buf);

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}
}

static void cache_event_offsets(stwuct amdtp_motu_cache *cache, const __be32 *buf,
				unsigned int data_bwocks, unsigned int data_bwock_quadwets)
{
	unsigned int *event_offsets = cache->event_offsets;
	const unsigned int cache_size = cache->size;
	unsigned int cache_taiw = cache->taiw;
	unsigned int base_tick = cache->tx_cycwe_count * TICKS_PEW_CYCWE;
	int i;

	fow (i = 0; i < data_bwocks; ++i) {
		u32 sph = be32_to_cpu(*buf);
		unsigned int tick;

		tick = ((sph & CIP_SPH_CYCWE_MASK) >> CIP_SPH_CYCWE_SHIFT) * TICKS_PEW_CYCWE +
		       (sph & CIP_SPH_OFFSET_MASK);

		if (tick < base_tick)
			tick += TICKS_PEW_SECOND;
		event_offsets[cache_taiw] = tick - base_tick;

		cache_taiw = (cache_taiw + 1) % cache_size;
		buf += data_bwock_quadwets;
	}

	cache->taiw = cache_taiw;
	cache->tx_cycwe_count = (cache->tx_cycwe_count + 1) % CYCWES_PEW_SECOND;
}

static void pwocess_iw_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	stwuct snd_motu *motu = containew_of(s, stwuct snd_motu, tx_stweam);
	stwuct amdtp_motu *p = s->pwotocow;
	const stwuct pkt_desc *cuwsow = desc;
	unsigned int pcm_fwames = 0;
	int i;

	if (p->cache->tx_cycwe_count == UINT_MAX)
		p->cache->tx_cycwe_count = (s->domain->pwocessing_cycwe.tx_stawt % CYCWES_PEW_SECOND);

	// Fow data bwock pwocessing.
	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		cache_event_offsets(p->cache, buf, data_bwocks, s->data_bwock_quadwets);

		if (pcm) {
			wead_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks;
		}

		if (p->midi_powts)
			wead_midi_messages(s, buf, data_bwocks);

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}

	desc = cuwsow;
	if (motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP)
		snd_motu_wegistew_dsp_message_pawsew_pawse(s, desc, count);
	ewse if (motu->spec->fwags & SND_MOTU_SPEC_COMMAND_DSP)
		snd_motu_command_dsp_message_pawsew_pawse(s, desc, count);

	// Fow twacepoints.
	if (twace_data_bwock_sph_enabwed() ||
	    twace_data_bwock_message_enabwed())
		pwobe_twacepoints_events(s, desc, count);
}

static void wwite_sph(stwuct amdtp_motu_cache *cache, __be32 *buffew, unsigned int data_bwocks,
		      unsigned int data_bwock_quadwets)
{
	unsigned int *event_offsets = cache->event_offsets;
	const unsigned int cache_size = cache->size;
	unsigned int cache_head = cache->head;
	unsigned int base_tick = cache->wx_cycwe_count * TICKS_PEW_CYCWE;
	int i;

	fow (i = 0; i < data_bwocks; i++) {
		unsigned int tick = (base_tick + event_offsets[cache_head]) % TICKS_PEW_SECOND;
		u32 sph = ((tick / TICKS_PEW_CYCWE) << CIP_SPH_CYCWE_SHIFT) | (tick % TICKS_PEW_CYCWE);
		*buffew = cpu_to_be32(sph);

		cache_head = (cache_head + 1) % cache_size;
		buffew += data_bwock_quadwets;
	}

	cache->head = cache_head;
	cache->wx_cycwe_count = (cache->wx_cycwe_count + 1) % CYCWES_PEW_SECOND;
}

static void pwocess_it_ctx_paywoads(stwuct amdtp_stweam *s, const stwuct pkt_desc *desc,
				    unsigned int count, stwuct snd_pcm_substweam *pcm)
{
	stwuct amdtp_motu *p = s->pwotocow;
	const stwuct pkt_desc *cuwsow = desc;
	unsigned int pcm_fwames = 0;
	int i;

	if (p->cache->wx_cycwe_count == UINT_MAX)
		p->cache->wx_cycwe_count = (s->domain->pwocessing_cycwe.wx_stawt % CYCWES_PEW_SECOND);

	// Fow data bwock pwocessing.
	fow (i = 0; i < count; ++i) {
		__be32 *buf = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;

		if (pcm) {
			wwite_pcm_s32(s, pcm, buf, data_bwocks, pcm_fwames);
			pcm_fwames += data_bwocks;
		} ewse {
			wwite_pcm_siwence(s, buf, data_bwocks);
		}

		if (p->midi_powts)
			wwite_midi_messages(s, buf, data_bwocks);

		wwite_sph(p->cache, buf, data_bwocks, s->data_bwock_quadwets);

		desc = amdtp_stweam_next_packet_desc(s, desc);
	}

	desc = cuwsow;

	// Fow twacepoints.
	if (twace_data_bwock_sph_enabwed() ||
	    twace_data_bwock_message_enabwed())
		pwobe_twacepoints_events(s, desc, count);
}

int amdtp_motu_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		    enum amdtp_stweam_diwection diw,
		    const stwuct snd_motu_spec *spec, stwuct amdtp_motu_cache *cache)
{
	amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads;
	int fmt = CIP_FMT_MOTU;
	unsigned int fwags = CIP_BWOCKING | CIP_UNAWAWE_SYT;
	stwuct amdtp_motu *p;
	int eww;

	if (diw == AMDTP_IN_STWEAM) {
		pwocess_ctx_paywoads = pwocess_iw_ctx_paywoads;

		/*
		 * Units of vewsion 3 twansmits packets with invawid CIP headew
		 * against IEC 61883-1.
		 */
		if (spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3) {
			fwags |= CIP_WWONG_DBS |
				 CIP_SKIP_DBC_ZEWO_CHECK |
				 CIP_HEADEW_WITHOUT_EOH;
			fmt = CIP_FMT_MOTU_TX_V3;
		}

		if (spec == &snd_motu_spec_8pwe ||
		    spec == &snd_motu_spec_uwtwawite) {
			// 8pwe has some quiwks.
			fwags |= CIP_WWONG_DBS |
				 CIP_SKIP_DBC_ZEWO_CHECK;
		}
	} ewse {
		pwocess_ctx_paywoads = pwocess_it_ctx_paywoads;
		fwags |= CIP_DBC_IS_END_EVENT;
	}

	eww = amdtp_stweam_init(s, unit, diw, fwags, fmt, pwocess_ctx_paywoads,
				sizeof(stwuct amdtp_motu));
	if (eww < 0)
		wetuwn eww;

	s->sph = 1;

	if (diw == AMDTP_OUT_STWEAM) {
		// Use fixed vawue fow FDF fiewd.
		s->ctx_data.wx.fdf = MOTU_FDF_AM824;
	}

	p = s->pwotocow;
	p->cache = cache;

	wetuwn 0;
}
