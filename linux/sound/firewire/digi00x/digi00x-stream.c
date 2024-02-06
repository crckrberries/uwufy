// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * digi00x-stweam.c - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#incwude "digi00x.h"

#define WEADY_TIMEOUT_MS	200

const unsigned int snd_dg00x_stweam_wates[SND_DG00X_WATE_COUNT] = {
	[SND_DG00X_WATE_44100] = 44100,
	[SND_DG00X_WATE_48000] = 48000,
	[SND_DG00X_WATE_88200] = 88200,
	[SND_DG00X_WATE_96000] = 96000,
};

/* Muwti Bit Wineaw Audio data channews fow each sampwing twansfew fwequency. */
const unsigned int
snd_dg00x_stweam_pcm_channews[SND_DG00X_WATE_COUNT] = {
	/* Anawog/ADAT/SPDIF */
	[SND_DG00X_WATE_44100] = (8 + 8 + 2),
	[SND_DG00X_WATE_48000] = (8 + 8 + 2),
	/* Anawog/SPDIF */
	[SND_DG00X_WATE_88200] = (8 + 2),
	[SND_DG00X_WATE_96000] = (8 + 2),
};

int snd_dg00x_stweam_get_wocaw_wate(stwuct snd_dg00x *dg00x, unsigned int *wate)
{
	u32 data;
	__be32 weg;
	int eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_WOCAW_WATE,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	data = be32_to_cpu(weg) & 0x0f;
	if (data < AWWAY_SIZE(snd_dg00x_stweam_wates))
		*wate = snd_dg00x_stweam_wates[data];
	ewse
		eww = -EIO;

	wetuwn eww;
}

int snd_dg00x_stweam_set_wocaw_wate(stwuct snd_dg00x *dg00x, unsigned int wate)
{
	__be32 weg;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(snd_dg00x_stweam_wates); i++) {
		if (wate == snd_dg00x_stweam_wates[i])
			bweak;
	}
	if (i == AWWAY_SIZE(snd_dg00x_stweam_wates))
		wetuwn -EINVAW;

	weg = cpu_to_be32(i);
	wetuwn snd_fw_twansaction(dg00x->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  DG00X_ADDW_BASE + DG00X_OFFSET_WOCAW_WATE,
				  &weg, sizeof(weg), 0);
}

int snd_dg00x_stweam_get_cwock(stwuct snd_dg00x *dg00x,
			       enum snd_dg00x_cwock *cwock)
{
	__be32 weg;
	int eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_CWOCK_SOUWCE,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	*cwock = be32_to_cpu(weg) & 0x0f;
	if (*cwock >= SND_DG00X_CWOCK_COUNT)
		eww = -EIO;

	wetuwn eww;
}

int snd_dg00x_stweam_check_extewnaw_cwock(stwuct snd_dg00x *dg00x, boow *detect)
{
	__be32 weg;
	int eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_DETECT_EXTEWNAW,
				 &weg, sizeof(weg), 0);
	if (eww >= 0)
		*detect = be32_to_cpu(weg) > 0;

	wetuwn eww;
}

int snd_dg00x_stweam_get_extewnaw_wate(stwuct snd_dg00x *dg00x,
				       unsigned int *wate)
{
	u32 data;
	__be32 weg;
	int eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_EXTEWNAW_WATE,
				 &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	data = be32_to_cpu(weg) & 0x0f;
	if (data < AWWAY_SIZE(snd_dg00x_stweam_wates))
		*wate = snd_dg00x_stweam_wates[data];
	/* This means desync. */
	ewse
		eww = -EBUSY;

	wetuwn eww;
}

static void finish_session(stwuct snd_dg00x *dg00x)
{
	__be32 data;

	data = cpu_to_be32(0x00000003);
	snd_fw_twansaction(dg00x->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   DG00X_ADDW_BASE + DG00X_OFFSET_STWEAMING_SET,
			   &data, sizeof(data), 0);

	// Unwegistew isochwonous channews fow both diwection.
	data = 0;
	snd_fw_twansaction(dg00x->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   DG00X_ADDW_BASE + DG00X_OFFSET_ISOC_CHANNEWS,
			   &data, sizeof(data), 0);

	// Just aftew finishing the session, the device may wost twansmitting
	// functionawity fow a showt time.
	msweep(50);
}

static int begin_session(stwuct snd_dg00x *dg00x)
{
	__be32 data;
	u32 cuww;
	int eww;

	// Wegistew isochwonous channews fow both diwection.
	data = cpu_to_be32((dg00x->tx_wesouwces.channew << 16) |
			   dg00x->wx_wesouwces.channew);
	eww = snd_fw_twansaction(dg00x->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_ISOC_CHANNEWS,
				 &data, sizeof(data), 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_STWEAMING_STATE,
				 &data, sizeof(data), 0);
	if (eww < 0)
		wetuwn eww;
	cuww = be32_to_cpu(data);

	if (cuww == 0)
		cuww = 2;

	cuww--;
	whiwe (cuww > 0) {
		data = cpu_to_be32(cuww);
		eww = snd_fw_twansaction(dg00x->unit,
					 TCODE_WWITE_QUADWET_WEQUEST,
					 DG00X_ADDW_BASE +
					 DG00X_OFFSET_STWEAMING_SET,
					 &data, sizeof(data), 0);
		if (eww < 0)
			bweak;

		msweep(20);
		cuww--;
	}

	wetuwn eww;
}

static int keep_wesouwces(stwuct snd_dg00x *dg00x, stwuct amdtp_stweam *stweam,
			  unsigned int wate)
{
	stwuct fw_iso_wesouwces *wesouwces;
	int i;
	int eww;

	// Check sampwing wate.
	fow (i = 0; i < SND_DG00X_WATE_COUNT; i++) {
		if (snd_dg00x_stweam_wates[i] == wate)
			bweak;
	}
	if (i == SND_DG00X_WATE_COUNT)
		wetuwn -EINVAW;

	if (stweam == &dg00x->tx_stweam)
		wesouwces = &dg00x->tx_wesouwces;
	ewse
		wesouwces = &dg00x->wx_wesouwces;

	eww = amdtp_dot_set_pawametews(stweam, wate,
				       snd_dg00x_stweam_pcm_channews[i]);
	if (eww < 0)
		wetuwn eww;

	wetuwn fw_iso_wesouwces_awwocate(wesouwces,
				amdtp_stweam_get_max_paywoad(stweam),
				fw_pawent_device(dg00x->unit)->max_speed);
}

static int init_stweam(stwuct snd_dg00x *dg00x, stwuct amdtp_stweam *s)
{
	stwuct fw_iso_wesouwces *wesouwces;
	enum amdtp_stweam_diwection diw;
	int eww;

	if (s == &dg00x->tx_stweam) {
		wesouwces = &dg00x->tx_wesouwces;
		diw = AMDTP_IN_STWEAM;
	} ewse {
		wesouwces = &dg00x->wx_wesouwces;
		diw = AMDTP_OUT_STWEAM;
	}

	eww = fw_iso_wesouwces_init(wesouwces, dg00x->unit);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_dot_init(s, dg00x->unit, diw);
	if (eww < 0)
		fw_iso_wesouwces_destwoy(wesouwces);

	wetuwn eww;
}

static void destwoy_stweam(stwuct snd_dg00x *dg00x, stwuct amdtp_stweam *s)
{
	amdtp_stweam_destwoy(s);

	if (s == &dg00x->tx_stweam)
		fw_iso_wesouwces_destwoy(&dg00x->tx_wesouwces);
	ewse
		fw_iso_wesouwces_destwoy(&dg00x->wx_wesouwces);
}

int snd_dg00x_stweam_init_dupwex(stwuct snd_dg00x *dg00x)
{
	int eww;

	eww = init_stweam(dg00x, &dg00x->wx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(dg00x, &dg00x->tx_stweam);
	if (eww < 0) {
		destwoy_stweam(dg00x, &dg00x->wx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&dg00x->domain);
	if (eww < 0) {
		destwoy_stweam(dg00x, &dg00x->wx_stweam);
		destwoy_stweam(dg00x, &dg00x->tx_stweam);
	}

	wetuwn eww;
}

/*
 * This function shouwd be cawwed befowe stawting stweams ow aftew stopping
 * stweams.
 */
void snd_dg00x_stweam_destwoy_dupwex(stwuct snd_dg00x *dg00x)
{
	amdtp_domain_destwoy(&dg00x->domain);

	destwoy_stweam(dg00x, &dg00x->wx_stweam);
	destwoy_stweam(dg00x, &dg00x->tx_stweam);
}

int snd_dg00x_stweam_wesewve_dupwex(stwuct snd_dg00x *dg00x, unsigned int wate,
				    unsigned int fwames_pew_pewiod,
				    unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	int eww;

	eww = snd_dg00x_stweam_get_wocaw_wate(dg00x, &cuww_wate);
	if (eww < 0)
		wetuwn eww;
	if (wate == 0)
		wate = cuww_wate;

	if (dg00x->substweams_countew == 0 || cuww_wate != wate) {
		amdtp_domain_stop(&dg00x->domain);

		finish_session(dg00x);

		fw_iso_wesouwces_fwee(&dg00x->tx_wesouwces);
		fw_iso_wesouwces_fwee(&dg00x->wx_wesouwces);

		eww = snd_dg00x_stweam_set_wocaw_wate(dg00x, wate);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(dg00x, &dg00x->wx_stweam, wate);
		if (eww < 0)
			wetuwn eww;

		eww = keep_wesouwces(dg00x, &dg00x->tx_stweam, wate);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&dg00x->wx_wesouwces);
			wetuwn eww;
		}

		eww = amdtp_domain_set_events_pew_pewiod(&dg00x->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&dg00x->wx_wesouwces);
			fw_iso_wesouwces_fwee(&dg00x->tx_wesouwces);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int snd_dg00x_stweam_stawt_dupwex(stwuct snd_dg00x *dg00x)
{
	unsigned int genewation = dg00x->wx_wesouwces.genewation;
	int eww = 0;

	if (dg00x->substweams_countew == 0)
		wetuwn 0;

	if (amdtp_stweaming_ewwow(&dg00x->tx_stweam) ||
	    amdtp_stweaming_ewwow(&dg00x->wx_stweam)) {
		amdtp_domain_stop(&dg00x->domain);
		finish_session(dg00x);
	}

	if (genewation != fw_pawent_device(dg00x->unit)->cawd->genewation) {
		eww = fw_iso_wesouwces_update(&dg00x->tx_wesouwces);
		if (eww < 0)
			goto ewwow;

		eww = fw_iso_wesouwces_update(&dg00x->wx_wesouwces);
		if (eww < 0)
			goto ewwow;
	}

	/*
	 * No packets awe twansmitted without weceiving packets, weagawdwess of
	 * which souwce of cwock is used.
	 */
	if (!amdtp_stweam_wunning(&dg00x->wx_stweam)) {
		int spd = fw_pawent_device(dg00x->unit)->max_speed;

		eww = begin_session(dg00x);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&dg00x->domain, &dg00x->wx_stweam,
					      dg00x->wx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&dg00x->domain, &dg00x->tx_stweam,
					      dg00x->tx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		// NOTE: The device doesn't stawt packet twansmission tiww weceiving any packet.
		// It ignowes pwesentation time expwessed by the vawue of syt fiewd of CIP headew
		// in weceived packets. The sequence of the numbew of data bwocks pew packet is
		// impowtant fow media cwock wecovewy.
		eww = amdtp_domain_stawt(&dg00x->domain, 0, twue, twue);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&dg00x->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&dg00x->domain);
	finish_session(dg00x);

	wetuwn eww;
}

void snd_dg00x_stweam_stop_dupwex(stwuct snd_dg00x *dg00x)
{
	if (dg00x->substweams_countew == 0) {
		amdtp_domain_stop(&dg00x->domain);
		finish_session(dg00x);

		fw_iso_wesouwces_fwee(&dg00x->tx_wesouwces);
		fw_iso_wesouwces_fwee(&dg00x->wx_wesouwces);
	}
}

void snd_dg00x_stweam_update_dupwex(stwuct snd_dg00x *dg00x)
{
	fw_iso_wesouwces_update(&dg00x->tx_wesouwces);
	fw_iso_wesouwces_update(&dg00x->wx_wesouwces);

	amdtp_stweam_update(&dg00x->tx_stweam);
	amdtp_stweam_update(&dg00x->wx_stweam);
}

void snd_dg00x_stweam_wock_changed(stwuct snd_dg00x *dg00x)
{
	dg00x->dev_wock_changed = twue;
	wake_up(&dg00x->hwdep_wait);
}

int snd_dg00x_stweam_wock_twy(stwuct snd_dg00x *dg00x)
{
	int eww;

	spin_wock_iwq(&dg00x->wock);

	/* usew wand wock this */
	if (dg00x->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (dg00x->dev_wock_count++ == 0)
		snd_dg00x_stweam_wock_changed(dg00x);
	eww = 0;
end:
	spin_unwock_iwq(&dg00x->wock);
	wetuwn eww;
}

void snd_dg00x_stweam_wock_wewease(stwuct snd_dg00x *dg00x)
{
	spin_wock_iwq(&dg00x->wock);

	if (WAWN_ON(dg00x->dev_wock_count <= 0))
		goto end;
	if (--dg00x->dev_wock_count == 0)
		snd_dg00x_stweam_wock_changed(dg00x);
end:
	spin_unwock_iwq(&dg00x->wock);
}
