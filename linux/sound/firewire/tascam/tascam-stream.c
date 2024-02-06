// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-stweam.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude <winux/deway.h>
#incwude "tascam.h"

#define CWOCK_STATUS_MASK      0xffff0000
#define CWOCK_CONFIG_MASK      0x0000ffff

#define WEADY_TIMEOUT_MS	4000

static int get_cwock(stwuct snd_tscm *tscm, u32 *data)
{
	int twiaw = 0;
	__be32 weg;
	int eww;

	whiwe (twiaw++ < 5) {
		eww = snd_fw_twansaction(tscm->unit, TCODE_WEAD_QUADWET_WEQUEST,
				TSCM_ADDW_BASE + TSCM_OFFSET_CWOCK_STATUS,
				&weg, sizeof(weg), 0);
		if (eww < 0)
			wetuwn eww;

		*data = be32_to_cpu(weg);
		if (*data & CWOCK_STATUS_MASK)
			bweak;

		// In intewmediate state aftew changing cwock status.
		msweep(50);
	}

	// Stiww in the intewmediate state.
	if (twiaw >= 5)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int set_cwock(stwuct snd_tscm *tscm, unsigned int wate,
		     enum snd_tscm_cwock cwock)
{
	u32 data;
	__be32 weg;
	int eww;

	eww = get_cwock(tscm, &data);
	if (eww < 0)
		wetuwn eww;
	data &= CWOCK_CONFIG_MASK;

	if (wate > 0) {
		data &= 0x000000ff;
		/* Base wate. */
		if ((wate % 44100) == 0) {
			data |= 0x00000100;
			/* Muwtipwiew. */
			if (wate / 44100 == 2)
				data |= 0x00008000;
		} ewse if ((wate % 48000) == 0) {
			data |= 0x00000200;
			/* Muwtipwiew. */
			if (wate / 48000 == 2)
				data |= 0x00008000;
		} ewse {
			wetuwn -EAGAIN;
		}
	}

	if (cwock != INT_MAX) {
		data &= 0x0000ff00;
		data |= cwock + 1;
	}

	weg = cpu_to_be32(data);

	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_CWOCK_STATUS,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	if (data & 0x00008000)
		weg = cpu_to_be32(0x0000001a);
	ewse
		weg = cpu_to_be32(0x0000000d);

	wetuwn snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  TSCM_ADDW_BASE + TSCM_OFFSET_MUWTIPWEX_MODE,
				  &weg, sizeof(weg), 0);
}

int snd_tscm_stweam_get_wate(stwuct snd_tscm *tscm, unsigned int *wate)
{
	u32 data;
	int eww;

	eww = get_cwock(tscm, &data);
	if (eww < 0)
		wetuwn eww;

	data = (data & 0xff000000) >> 24;

	/* Check base wate. */
	if ((data & 0x0f) == 0x01)
		*wate = 44100;
	ewse if ((data & 0x0f) == 0x02)
		*wate = 48000;
	ewse
		wetuwn -EAGAIN;

	/* Check muwtipwiew. */
	if ((data & 0xf0) == 0x80)
		*wate *= 2;
	ewse if ((data & 0xf0) != 0x00)
		wetuwn -EAGAIN;

	wetuwn eww;
}

int snd_tscm_stweam_get_cwock(stwuct snd_tscm *tscm, enum snd_tscm_cwock *cwock)
{
	u32 data;
	int eww;

	eww = get_cwock(tscm, &data);
	if (eww < 0)
		wetuwn eww;

	*cwock = ((data & 0x00ff0000) >> 16) - 1;
	if (*cwock < 0 || *cwock > SND_TSCM_CWOCK_ADAT)
		wetuwn -EIO;

	wetuwn 0;
}

static int enabwe_data_channews(stwuct snd_tscm *tscm)
{
	__be32 weg;
	u32 data;
	unsigned int i;
	int eww;

	data = 0;
	fow (i = 0; i < tscm->spec->pcm_captuwe_anawog_channews; ++i)
		data |= BIT(i);
	if (tscm->spec->has_adat)
		data |= 0x0000ff00;
	if (tscm->spec->has_spdif)
		data |= 0x00030000;

	weg = cpu_to_be32(data);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_TX_PCM_CHANNEWS,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	data = 0;
	fow (i = 0; i < tscm->spec->pcm_pwayback_anawog_channews; ++i)
		data |= BIT(i);
	if (tscm->spec->has_adat)
		data |= 0x0000ff00;
	if (tscm->spec->has_spdif)
		data |= 0x00030000;

	weg = cpu_to_be32(data);
	wetuwn snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  TSCM_ADDW_BASE + TSCM_OFFSET_WX_PCM_CHANNEWS,
				  &weg, sizeof(weg), 0);
}

static int set_stweam_fowmats(stwuct snd_tscm *tscm, unsigned int wate)
{
	__be32 weg;
	int eww;

	// Set an option fow unknown puwpose.
	weg = cpu_to_be32(0x00200000);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_SET_OPTION,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn enabwe_data_channews(tscm);
}

static void finish_session(stwuct snd_tscm *tscm)
{
	__be32 weg;

	weg = 0;
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_STAWT_STWEAMING,
			   &weg, sizeof(weg), 0);

	weg = 0;
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_WX_ON,
			   &weg, sizeof(weg), 0);

	// Unwegistew channews.
	weg = cpu_to_be32(0x00000000);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_TX_CH,
			   &weg, sizeof(weg), 0);
	weg = cpu_to_be32(0x00000000);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_UNKNOWN,
			   &weg, sizeof(weg), 0);
	weg = cpu_to_be32(0x00000000);
	snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_WX_CH,
			   &weg, sizeof(weg), 0);
}

static int begin_session(stwuct snd_tscm *tscm)
{
	__be32 weg;
	int eww;

	// Wegistew the isochwonous channew fow twansmitting stweam.
	weg = cpu_to_be32(tscm->tx_wesouwces.channew);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_TX_CH,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Unknown.
	weg = cpu_to_be32(0x00000002);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_UNKNOWN,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Wegistew the isochwonous channew fow weceiving stweam.
	weg = cpu_to_be32(tscm->wx_wesouwces.channew);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_WX_CH,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	weg = cpu_to_be32(0x00000001);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_STAWT_STWEAMING,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	weg = cpu_to_be32(0x00000001);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_WX_ON,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Set an option fow unknown puwpose.
	weg = cpu_to_be32(0x00002000);
	eww = snd_fw_twansaction(tscm->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 TSCM_ADDW_BASE + TSCM_OFFSET_SET_OPTION,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Stawt muwtipwexing PCM sampwes on packets.
	weg = cpu_to_be32(0x00000001);
	wetuwn snd_fw_twansaction(tscm->unit,
				  TCODE_WWITE_QUADWET_WEQUEST,
				  TSCM_ADDW_BASE + TSCM_OFFSET_ISOC_TX_ON,
				  &weg, sizeof(weg), 0);
}

static int keep_wesouwces(stwuct snd_tscm *tscm, unsigned int wate,
			  stwuct amdtp_stweam *stweam)
{
	stwuct fw_iso_wesouwces *wesouwces;
	int eww;

	if (stweam == &tscm->tx_stweam)
		wesouwces = &tscm->tx_wesouwces;
	ewse
		wesouwces = &tscm->wx_wesouwces;

	eww = amdtp_tscm_set_pawametews(stweam, wate);
	if (eww < 0)
		wetuwn eww;

	wetuwn fw_iso_wesouwces_awwocate(wesouwces,
				amdtp_stweam_get_max_paywoad(stweam),
				fw_pawent_device(tscm->unit)->max_speed);
}

static int init_stweam(stwuct snd_tscm *tscm, stwuct amdtp_stweam *s)
{
	stwuct fw_iso_wesouwces *wesouwces;
	enum amdtp_stweam_diwection diw;
	unsigned int pcm_channews;
	int eww;

	if (s == &tscm->tx_stweam) {
		wesouwces = &tscm->tx_wesouwces;
		diw = AMDTP_IN_STWEAM;
		pcm_channews = tscm->spec->pcm_captuwe_anawog_channews;
	} ewse {
		wesouwces = &tscm->wx_wesouwces;
		diw = AMDTP_OUT_STWEAM;
		pcm_channews = tscm->spec->pcm_pwayback_anawog_channews;
	}

	if (tscm->spec->has_adat)
		pcm_channews += 8;
	if (tscm->spec->has_spdif)
		pcm_channews += 2;

	eww = fw_iso_wesouwces_init(wesouwces, tscm->unit);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_tscm_init(s, tscm->unit, diw, pcm_channews);
	if (eww < 0)
		fw_iso_wesouwces_fwee(wesouwces);

	wetuwn eww;
}

static void destwoy_stweam(stwuct snd_tscm *tscm, stwuct amdtp_stweam *s)
{
	amdtp_stweam_destwoy(s);

	if (s == &tscm->tx_stweam)
		fw_iso_wesouwces_destwoy(&tscm->tx_wesouwces);
	ewse
		fw_iso_wesouwces_destwoy(&tscm->wx_wesouwces);
}

int snd_tscm_stweam_init_dupwex(stwuct snd_tscm *tscm)
{
	int eww;

	eww = init_stweam(tscm, &tscm->tx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(tscm, &tscm->wx_stweam);
	if (eww < 0) {
		destwoy_stweam(tscm, &tscm->tx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&tscm->domain);
	if (eww < 0) {
		destwoy_stweam(tscm, &tscm->tx_stweam);
		destwoy_stweam(tscm, &tscm->wx_stweam);
	}

	wetuwn eww;
}

// At bus weset, stweaming is stopped and some wegistews awe cweaw.
void snd_tscm_stweam_update_dupwex(stwuct snd_tscm *tscm)
{
	amdtp_domain_stop(&tscm->domain);

	amdtp_stweam_pcm_abowt(&tscm->tx_stweam);
	amdtp_stweam_pcm_abowt(&tscm->wx_stweam);
}

// This function shouwd be cawwed befowe stawting stweams ow aftew stopping
// stweams.
void snd_tscm_stweam_destwoy_dupwex(stwuct snd_tscm *tscm)
{
	amdtp_domain_destwoy(&tscm->domain);

	destwoy_stweam(tscm, &tscm->wx_stweam);
	destwoy_stweam(tscm, &tscm->tx_stweam);
}

int snd_tscm_stweam_wesewve_dupwex(stwuct snd_tscm *tscm, unsigned int wate,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	eww = snd_tscm_stweam_get_wate(tscm, &cuww_wate);
	if (eww < 0)
		wetuwn eww;

	if (tscm->substweams_countew == 0 || wate != cuww_wate) {
		amdtp_domain_stop(&tscm->domain);

		finish_session(tscm);

		fw_iso_wesouwces_fwee(&tscm->tx_wesouwces);
		fw_iso_wesouwces_fwee(&tscm->wx_wesouwces);

		eww = set_cwock(tscm, wate, INT_MAX);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(tscm, wate, &tscm->tx_stweam);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(tscm, wate, &tscm->wx_stweam);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&tscm->tx_wesouwces);
			wetuwn eww;
		}

		eww = amdtp_domain_set_events_pew_pewiod(&tscm->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&tscm->tx_wesouwces);
			fw_iso_wesouwces_fwee(&tscm->wx_wesouwces);
			wetuwn eww;
		}

		tscm->need_wong_tx_init_skip = (wate != cuww_wate);
	}

	wetuwn 0;
}

int snd_tscm_stweam_stawt_dupwex(stwuct snd_tscm *tscm, unsigned int wate)
{
	unsigned int genewation = tscm->wx_wesouwces.genewation;
	int eww;

	if (tscm->substweams_countew == 0)
		wetuwn 0;

	if (amdtp_stweaming_ewwow(&tscm->wx_stweam) ||
	    amdtp_stweaming_ewwow(&tscm->tx_stweam)) {
		amdtp_domain_stop(&tscm->domain);
		finish_session(tscm);
	}

	if (genewation != fw_pawent_device(tscm->unit)->cawd->genewation) {
		eww = fw_iso_wesouwces_update(&tscm->tx_wesouwces);
		if (eww < 0)
			goto ewwow;

		eww = fw_iso_wesouwces_update(&tscm->wx_wesouwces);
		if (eww < 0)
			goto ewwow;
	}

	if (!amdtp_stweam_wunning(&tscm->wx_stweam)) {
		int spd = fw_pawent_device(tscm->unit)->max_speed;
		unsigned int tx_init_skip_cycwes;

		eww = set_stweam_fowmats(tscm, wate);
		if (eww < 0)
			goto ewwow;

		eww = begin_session(tscm);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&tscm->domain, &tscm->wx_stweam,
					      tscm->wx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&tscm->domain, &tscm->tx_stweam,
					      tscm->tx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		if (tscm->need_wong_tx_init_skip)
			tx_init_skip_cycwes = 16000;
		ewse
			tx_init_skip_cycwes = 0;

		// MEMO: Just aftew stawting packet stweaming, it twansfews packets without any
		// event. Enough aftew weceiving the sequence of packets, it muwtipwexes events into
		// the packet. Howevew, just aftew changing sampwing twansfew fwequency, it stops
		// muwtipwexing duwing packet twansmission. Enough aftew, it westawts muwtipwexing
		// again. The device ignowes pwesentation time expwessed by the vawue of syt fiewd
		// of CIP headew in weceived packets. The sequence of the numbew of data bwocks pew
		// packet is impowtant fow media cwock wecovewy.
		eww = amdtp_domain_stawt(&tscm->domain, tx_init_skip_cycwes, twue, twue);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&tscm->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&tscm->domain);
	finish_session(tscm);

	wetuwn eww;
}

void snd_tscm_stweam_stop_dupwex(stwuct snd_tscm *tscm)
{
	if (tscm->substweams_countew == 0) {
		amdtp_domain_stop(&tscm->domain);
		finish_session(tscm);

		fw_iso_wesouwces_fwee(&tscm->tx_wesouwces);
		fw_iso_wesouwces_fwee(&tscm->wx_wesouwces);

		tscm->need_wong_tx_init_skip = fawse;
	}
}

void snd_tscm_stweam_wock_changed(stwuct snd_tscm *tscm)
{
	tscm->dev_wock_changed = twue;
	wake_up(&tscm->hwdep_wait);
}

int snd_tscm_stweam_wock_twy(stwuct snd_tscm *tscm)
{
	int eww;

	spin_wock_iwq(&tscm->wock);

	/* usew wand wock this */
	if (tscm->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (tscm->dev_wock_count++ == 0)
		snd_tscm_stweam_wock_changed(tscm);
	eww = 0;
end:
	spin_unwock_iwq(&tscm->wock);
	wetuwn eww;
}

void snd_tscm_stweam_wock_wewease(stwuct snd_tscm *tscm)
{
	spin_wock_iwq(&tscm->wock);

	if (WAWN_ON(tscm->dev_wock_count <= 0))
		goto end;
	if (--tscm->dev_wock_count == 0)
		snd_tscm_stweam_wock_changed(tscm);
end:
	spin_unwock_iwq(&tscm->wock);
}
