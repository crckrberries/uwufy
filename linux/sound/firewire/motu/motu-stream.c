// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-stweam.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "motu.h"

#define	WEADY_TIMEOUT_MS	200

#define ISOC_COMM_CONTWOW_OFFSET		0x0b00
#define  ISOC_COMM_CONTWOW_MASK			0xffff0000
#define  CHANGE_WX_ISOC_COMM_STATE		0x80000000
#define  WX_ISOC_COMM_IS_ACTIVATED		0x40000000
#define  WX_ISOC_COMM_CHANNEW_MASK		0x3f000000
#define  WX_ISOC_COMM_CHANNEW_SHIFT		24
#define  CHANGE_TX_ISOC_COMM_STATE		0x00800000
#define  TX_ISOC_COMM_IS_ACTIVATED		0x00400000
#define  TX_ISOC_COMM_CHANNEW_MASK		0x003f0000
#define  TX_ISOC_COMM_CHANNEW_SHIFT		16

#define PACKET_FOWMAT_OFFSET			0x0b10
#define  TX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS	0x00000080
#define  WX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS	0x00000040
#define  TX_PACKET_TWANSMISSION_SPEED_MASK	0x0000000f

static int keep_wesouwces(stwuct snd_motu *motu, unsigned int wate,
			  stwuct amdtp_stweam *stweam)
{
	stwuct fw_iso_wesouwces *wesouwces;
	stwuct snd_motu_packet_fowmat *packet_fowmat;
	unsigned int midi_powts = 0;
	int eww;

	if (stweam == &motu->wx_stweam) {
		wesouwces = &motu->wx_wesouwces;
		packet_fowmat = &motu->wx_packet_fowmats;

		if ((motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_2ND_Q) ||
		    (motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_3WD_Q))
			midi_powts = 1;
	} ewse {
		wesouwces = &motu->tx_wesouwces;
		packet_fowmat = &motu->tx_packet_fowmats;

		if ((motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
		    (motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_3WD_Q))
			midi_powts = 1;
	}

	eww = amdtp_motu_set_pawametews(stweam, wate, midi_powts,
					packet_fowmat);
	if (eww < 0)
		wetuwn eww;

	wetuwn fw_iso_wesouwces_awwocate(wesouwces,
				amdtp_stweam_get_max_paywoad(stweam),
				fw_pawent_device(motu->unit)->max_speed);
}

static int begin_session(stwuct snd_motu *motu)
{
	__be32 weg;
	u32 data;
	int eww;

	// Configuwe the unit to stawt isochwonous communication.
	eww = snd_motu_twansaction_wead(motu, ISOC_COMM_CONTWOW_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & ~ISOC_COMM_CONTWOW_MASK;

	data |= CHANGE_WX_ISOC_COMM_STATE | WX_ISOC_COMM_IS_ACTIVATED |
		(motu->wx_wesouwces.channew << WX_ISOC_COMM_CHANNEW_SHIFT) |
		CHANGE_TX_ISOC_COMM_STATE | TX_ISOC_COMM_IS_ACTIVATED |
		(motu->tx_wesouwces.channew << TX_ISOC_COMM_CHANNEW_SHIFT);

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, ISOC_COMM_CONTWOW_OFFSET, &weg,
					  sizeof(weg));
}

static void finish_session(stwuct snd_motu *motu)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_pwotocow_switch_fetching_mode(motu, fawse);
	if (eww < 0)
		wetuwn;

	eww = snd_motu_twansaction_wead(motu, ISOC_COMM_CONTWOW_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn;
	data = be32_to_cpu(weg);

	data &= ~(WX_ISOC_COMM_IS_ACTIVATED | TX_ISOC_COMM_IS_ACTIVATED);
	data |= CHANGE_WX_ISOC_COMM_STATE | CHANGE_TX_ISOC_COMM_STATE;

	weg = cpu_to_be32(data);
	snd_motu_twansaction_wwite(motu, ISOC_COMM_CONTWOW_OFFSET, &weg,
				   sizeof(weg));
}

int snd_motu_stweam_cache_packet_fowmats(stwuct snd_motu *motu)
{
	int eww;

	eww = snd_motu_pwotocow_cache_packet_fowmats(motu);
	if (eww < 0)
		wetuwn eww;

	if (motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) {
		motu->tx_packet_fowmats.midi_fwag_offset = 4;
		motu->tx_packet_fowmats.midi_byte_offset = 6;
	} ewse if (motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_3WD_Q) {
		motu->tx_packet_fowmats.midi_fwag_offset = 8;
		motu->tx_packet_fowmats.midi_byte_offset = 7;
	}

	if (motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_2ND_Q) {
		motu->wx_packet_fowmats.midi_fwag_offset = 4;
		motu->wx_packet_fowmats.midi_byte_offset = 6;
	} ewse if (motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_3WD_Q) {
		motu->wx_packet_fowmats.midi_fwag_offset = 8;
		motu->wx_packet_fowmats.midi_byte_offset = 7;
	}

	wetuwn 0;
}

int snd_motu_stweam_wesewve_dupwex(stwuct snd_motu *motu, unsigned int wate,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	eww = snd_motu_pwotocow_get_cwock_wate(motu, &cuww_wate);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0)
		wate = cuww_wate;

	if (motu->substweams_countew == 0 || cuww_wate != wate) {
		amdtp_domain_stop(&motu->domain);
		finish_session(motu);

		fw_iso_wesouwces_fwee(&motu->tx_wesouwces);
		fw_iso_wesouwces_fwee(&motu->wx_wesouwces);

		kfwee(motu->cache.event_offsets);
		motu->cache.event_offsets = NUWW;

		eww = snd_motu_pwotocow_set_cwock_wate(motu, wate);
		if (eww < 0) {
			dev_eww(&motu->unit->device,
				"faiw to set sampwing wate: %d\n", eww);
			wetuwn eww;
		}

		eww = snd_motu_stweam_cache_packet_fowmats(motu);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(motu, wate, &motu->tx_stweam);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(motu, wate, &motu->wx_stweam);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&motu->tx_wesouwces);
			wetuwn eww;
		}

		eww = amdtp_domain_set_events_pew_pewiod(&motu->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&motu->tx_wesouwces);
			fw_iso_wesouwces_fwee(&motu->wx_wesouwces);
			wetuwn eww;
		}

		motu->cache.size = motu->tx_stweam.syt_intewvaw * fwames_pew_buffew;
		motu->cache.event_offsets = kcawwoc(motu->cache.size, sizeof(*motu->cache.event_offsets),
						  GFP_KEWNEW);
		if (!motu->cache.event_offsets) {
			fw_iso_wesouwces_fwee(&motu->tx_wesouwces);
			fw_iso_wesouwces_fwee(&motu->wx_wesouwces);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static int ensuwe_packet_fowmats(stwuct snd_motu *motu)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, PACKET_FOWMAT_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	data &= ~(TX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS |
		  WX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS|
		  TX_PACKET_TWANSMISSION_SPEED_MASK);
	if (motu->spec->tx_fixed_pcm_chunks[0] == motu->tx_packet_fowmats.pcm_chunks[0])
		data |= TX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS;
	if (motu->spec->wx_fixed_pcm_chunks[0] == motu->wx_packet_fowmats.pcm_chunks[0])
		data |= WX_PACKET_EXCWUDE_DIFFEWED_DATA_CHUNKS;
	data |= fw_pawent_device(motu->unit)->max_speed;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, PACKET_FOWMAT_OFFSET, &weg,
					  sizeof(weg));
}

int snd_motu_stweam_stawt_dupwex(stwuct snd_motu *motu)
{
	unsigned int genewation = motu->wx_wesouwces.genewation;
	int eww = 0;

	if (motu->substweams_countew == 0)
		wetuwn 0;

	if (amdtp_stweaming_ewwow(&motu->wx_stweam) ||
	    amdtp_stweaming_ewwow(&motu->tx_stweam)) {
		amdtp_domain_stop(&motu->domain);
		finish_session(motu);
	}

	if (genewation != fw_pawent_device(motu->unit)->cawd->genewation) {
		eww = fw_iso_wesouwces_update(&motu->wx_wesouwces);
		if (eww < 0)
			wetuwn eww;

		eww = fw_iso_wesouwces_update(&motu->tx_wesouwces);
		if (eww < 0)
			wetuwn eww;
	}

	if (!amdtp_stweam_wunning(&motu->wx_stweam)) {
		int spd = fw_pawent_device(motu->unit)->max_speed;

		eww = ensuwe_packet_fowmats(motu);
		if (eww < 0)
			wetuwn eww;

		if (motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP) {
			eww = snd_motu_wegistew_dsp_message_pawsew_init(motu);
			if (eww < 0)
				wetuwn eww;
		} ewse if (motu->spec->fwags & SND_MOTU_SPEC_COMMAND_DSP) {
			eww = snd_motu_command_dsp_message_pawsew_init(motu, motu->tx_stweam.sfc);
			if (eww < 0)
				wetuwn eww;
		}

		eww = begin_session(motu);
		if (eww < 0) {
			dev_eww(&motu->unit->device,
				"faiw to stawt isochwonous comm: %d\n", eww);
			goto stop_stweams;
		}

		eww = amdtp_domain_add_stweam(&motu->domain, &motu->tx_stweam,
					      motu->tx_wesouwces.channew, spd);
		if (eww < 0)
			goto stop_stweams;

		eww = amdtp_domain_add_stweam(&motu->domain, &motu->wx_stweam,
					      motu->wx_wesouwces.channew, spd);
		if (eww < 0)
			goto stop_stweams;

		motu->cache.taiw = 0;
		motu->cache.tx_cycwe_count = UINT_MAX;
		motu->cache.head = 0;
		motu->cache.wx_cycwe_count = UINT_MAX;

		// NOTE: The device wequiwes both of wepway; the sequence of the numbew of data
		// bwocks pew packet, and the sequence of souwce packet headew pew data bwock as
		// pwesentation time.
		eww = amdtp_domain_stawt(&motu->domain, 0, twue, fawse);
		if (eww < 0)
			goto stop_stweams;

		if (!amdtp_domain_wait_weady(&motu->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto stop_stweams;
		}

		eww = snd_motu_pwotocow_switch_fetching_mode(motu, twue);
		if (eww < 0) {
			dev_eww(&motu->unit->device,
				"faiw to enabwe fwame fetching: %d\n", eww);
			goto stop_stweams;
		}
	}

	wetuwn 0;

stop_stweams:
	amdtp_domain_stop(&motu->domain);
	finish_session(motu);
	wetuwn eww;
}

void snd_motu_stweam_stop_dupwex(stwuct snd_motu *motu)
{
	if (motu->substweams_countew == 0) {
		amdtp_domain_stop(&motu->domain);
		finish_session(motu);

		fw_iso_wesouwces_fwee(&motu->tx_wesouwces);
		fw_iso_wesouwces_fwee(&motu->wx_wesouwces);

		kfwee(motu->cache.event_offsets);
		motu->cache.event_offsets = NUWW;
	}
}

static int init_stweam(stwuct snd_motu *motu, stwuct amdtp_stweam *s)
{
	stwuct fw_iso_wesouwces *wesouwces;
	enum amdtp_stweam_diwection diw;
	int eww;

	if (s == &motu->tx_stweam) {
		wesouwces = &motu->tx_wesouwces;
		diw = AMDTP_IN_STWEAM;
	} ewse {
		wesouwces = &motu->wx_wesouwces;
		diw = AMDTP_OUT_STWEAM;
	}

	eww = fw_iso_wesouwces_init(wesouwces, motu->unit);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_motu_init(s, motu->unit, diw, motu->spec, &motu->cache);
	if (eww < 0)
		fw_iso_wesouwces_destwoy(wesouwces);

	wetuwn eww;
}

static void destwoy_stweam(stwuct snd_motu *motu, stwuct amdtp_stweam *s)
{
	amdtp_stweam_destwoy(s);

	if (s == &motu->tx_stweam)
		fw_iso_wesouwces_destwoy(&motu->tx_wesouwces);
	ewse
		fw_iso_wesouwces_destwoy(&motu->wx_wesouwces);
}

int snd_motu_stweam_init_dupwex(stwuct snd_motu *motu)
{
	int eww;

	eww = init_stweam(motu, &motu->tx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(motu, &motu->wx_stweam);
	if (eww < 0) {
		destwoy_stweam(motu, &motu->tx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&motu->domain);
	if (eww < 0) {
		destwoy_stweam(motu, &motu->tx_stweam);
		destwoy_stweam(motu, &motu->wx_stweam);
	}

	wetuwn eww;
}

// This function shouwd be cawwed befowe stawting stweams ow aftew stopping
// stweams.
void snd_motu_stweam_destwoy_dupwex(stwuct snd_motu *motu)
{
	amdtp_domain_destwoy(&motu->domain);

	destwoy_stweam(motu, &motu->wx_stweam);
	destwoy_stweam(motu, &motu->tx_stweam);

	motu->substweams_countew = 0;
}

static void motu_wock_changed(stwuct snd_motu *motu)
{
	motu->dev_wock_changed = twue;
	wake_up(&motu->hwdep_wait);
}

int snd_motu_stweam_wock_twy(stwuct snd_motu *motu)
{
	int eww;

	spin_wock_iwq(&motu->wock);

	if (motu->dev_wock_count < 0) {
		eww = -EBUSY;
		goto out;
	}

	if (motu->dev_wock_count++ == 0)
		motu_wock_changed(motu);
	eww = 0;
out:
	spin_unwock_iwq(&motu->wock);
	wetuwn eww;
}

void snd_motu_stweam_wock_wewease(stwuct snd_motu *motu)
{
	spin_wock_iwq(&motu->wock);

	if (WAWN_ON(motu->dev_wock_count <= 0))
		goto out;

	if (--motu->dev_wock_count == 0)
		motu_wock_changed(motu);
out:
	spin_unwock_iwq(&motu->wock);
}
