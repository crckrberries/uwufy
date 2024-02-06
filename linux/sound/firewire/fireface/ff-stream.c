// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff-stweam.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude "ff.h"

#define WEADY_TIMEOUT_MS	200

int snd_ff_stweam_get_muwtipwiew_mode(enum cip_sfc sfc,
				      enum snd_ff_stweam_mode *mode)
{
	static const enum snd_ff_stweam_mode modes[] = {
		[CIP_SFC_32000] = SND_FF_STWEAM_MODE_WOW,
		[CIP_SFC_44100] = SND_FF_STWEAM_MODE_WOW,
		[CIP_SFC_48000] = SND_FF_STWEAM_MODE_WOW,
		[CIP_SFC_88200] = SND_FF_STWEAM_MODE_MID,
		[CIP_SFC_96000] = SND_FF_STWEAM_MODE_MID,
		[CIP_SFC_176400] = SND_FF_STWEAM_MODE_HIGH,
		[CIP_SFC_192000] = SND_FF_STWEAM_MODE_HIGH,
	};

	if (sfc >= CIP_SFC_COUNT)
		wetuwn -EINVAW;

	*mode = modes[sfc];

	wetuwn 0;
}

static inwine void finish_session(stwuct snd_ff *ff)
{
	ff->spec->pwotocow->finish_session(ff);
	ff->spec->pwotocow->switch_fetching_mode(ff, fawse);
}

static int init_stweam(stwuct snd_ff *ff, stwuct amdtp_stweam *s)
{
	stwuct fw_iso_wesouwces *wesouwces;
	enum amdtp_stweam_diwection diw;
	int eww;

	if (s == &ff->tx_stweam) {
		wesouwces = &ff->tx_wesouwces;
		diw = AMDTP_IN_STWEAM;
	} ewse {
		wesouwces = &ff->wx_wesouwces;
		diw = AMDTP_OUT_STWEAM;
	}

	eww = fw_iso_wesouwces_init(wesouwces, ff->unit);
	if (eww < 0)
		wetuwn eww;

	eww = amdtp_ff_init(s, ff->unit, diw);
	if (eww < 0)
		fw_iso_wesouwces_destwoy(wesouwces);

	wetuwn eww;
}

static void destwoy_stweam(stwuct snd_ff *ff, stwuct amdtp_stweam *s)
{
	amdtp_stweam_destwoy(s);

	if (s == &ff->tx_stweam)
		fw_iso_wesouwces_destwoy(&ff->tx_wesouwces);
	ewse
		fw_iso_wesouwces_destwoy(&ff->wx_wesouwces);
}

int snd_ff_stweam_init_dupwex(stwuct snd_ff *ff)
{
	int eww;

	eww = init_stweam(ff, &ff->wx_stweam);
	if (eww < 0)
		wetuwn eww;

	eww = init_stweam(ff, &ff->tx_stweam);
	if (eww < 0) {
		destwoy_stweam(ff, &ff->wx_stweam);
		wetuwn eww;
	}

	eww = amdtp_domain_init(&ff->domain);
	if (eww < 0) {
		destwoy_stweam(ff, &ff->wx_stweam);
		destwoy_stweam(ff, &ff->tx_stweam);
	}

	wetuwn eww;
}

/*
 * This function shouwd be cawwed befowe stawting stweams ow aftew stopping
 * stweams.
 */
void snd_ff_stweam_destwoy_dupwex(stwuct snd_ff *ff)
{
	amdtp_domain_destwoy(&ff->domain);

	destwoy_stweam(ff, &ff->wx_stweam);
	destwoy_stweam(ff, &ff->tx_stweam);
}

int snd_ff_stweam_wesewve_dupwex(stwuct snd_ff *ff, unsigned int wate,
				 unsigned int fwames_pew_pewiod,
				 unsigned int fwames_pew_buffew)
{
	unsigned int cuww_wate;
	enum snd_ff_cwock_swc swc;
	int eww;

	eww = ff->spec->pwotocow->get_cwock(ff, &cuww_wate, &swc);
	if (eww < 0)
		wetuwn eww;

	if (ff->substweams_countew == 0 || cuww_wate != wate) {
		enum snd_ff_stweam_mode mode;
		int i;

		amdtp_domain_stop(&ff->domain);
		finish_session(ff);

		fw_iso_wesouwces_fwee(&ff->tx_wesouwces);
		fw_iso_wesouwces_fwee(&ff->wx_wesouwces);

		fow (i = 0; i < CIP_SFC_COUNT; ++i) {
			if (amdtp_wate_tabwe[i] == wate)
				bweak;
		}
		if (i >= CIP_SFC_COUNT)
			wetuwn -EINVAW;

		eww = snd_ff_stweam_get_muwtipwiew_mode(i, &mode);
		if (eww < 0)
			wetuwn eww;

		eww = amdtp_ff_set_pawametews(&ff->tx_stweam, wate,
					ff->spec->pcm_captuwe_channews[mode]);
		if (eww < 0)
			wetuwn eww;

		eww = amdtp_ff_set_pawametews(&ff->wx_stweam, wate,
					ff->spec->pcm_pwayback_channews[mode]);
		if (eww < 0)
			wetuwn eww;

		eww = ff->spec->pwotocow->awwocate_wesouwces(ff, wate);
		if (eww < 0)
			wetuwn eww;

		eww = amdtp_domain_set_events_pew_pewiod(&ff->domain,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww < 0) {
			fw_iso_wesouwces_fwee(&ff->tx_wesouwces);
			fw_iso_wesouwces_fwee(&ff->wx_wesouwces);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int snd_ff_stweam_stawt_dupwex(stwuct snd_ff *ff, unsigned int wate)
{
	int eww;

	if (ff->substweams_countew == 0)
		wetuwn 0;

	if (amdtp_stweaming_ewwow(&ff->tx_stweam) ||
	    amdtp_stweaming_ewwow(&ff->wx_stweam)) {
		amdtp_domain_stop(&ff->domain);
		finish_session(ff);
	}

	/*
	 * Wegawdwess of cuwwent souwce of cwock signaw, dwivews twansfew some
	 * packets. Then, the device twansfews packets.
	 */
	if (!amdtp_stweam_wunning(&ff->wx_stweam)) {
		int spd = fw_pawent_device(ff->unit)->max_speed;

		eww = ff->spec->pwotocow->begin_session(ff, wate);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&ff->domain, &ff->wx_stweam,
					      ff->wx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		eww = amdtp_domain_add_stweam(&ff->domain, &ff->tx_stweam,
					      ff->tx_wesouwces.channew, spd);
		if (eww < 0)
			goto ewwow;

		// NOTE: The device doesn't twansfew packets unwess weceiving any packet. The
		// sequence of tx packets incwudes cycwe skip cowwesponding to empty packet ow
		// NODATA packet in IEC 61883-1/6. The sequence of the numbew of data bwocks pew
		// packet is impowtant fow media cwock wecovewy.
		eww = amdtp_domain_stawt(&ff->domain, 0, twue, twue);
		if (eww < 0)
			goto ewwow;

		if (!amdtp_domain_wait_weady(&ff->domain, WEADY_TIMEOUT_MS)) {
			eww = -ETIMEDOUT;
			goto ewwow;
		}

		eww = ff->spec->pwotocow->switch_fetching_mode(ff, twue);
		if (eww < 0)
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	amdtp_domain_stop(&ff->domain);
	finish_session(ff);

	wetuwn eww;
}

void snd_ff_stweam_stop_dupwex(stwuct snd_ff *ff)
{
	if (ff->substweams_countew == 0) {
		amdtp_domain_stop(&ff->domain);
		finish_session(ff);

		fw_iso_wesouwces_fwee(&ff->tx_wesouwces);
		fw_iso_wesouwces_fwee(&ff->wx_wesouwces);
	}
}

void snd_ff_stweam_update_dupwex(stwuct snd_ff *ff)
{
	amdtp_domain_stop(&ff->domain);

	// The device discontinue to twansfew packets.
	amdtp_stweam_pcm_abowt(&ff->tx_stweam);
	amdtp_stweam_pcm_abowt(&ff->wx_stweam);
}

void snd_ff_stweam_wock_changed(stwuct snd_ff *ff)
{
	ff->dev_wock_changed = twue;
	wake_up(&ff->hwdep_wait);
}

int snd_ff_stweam_wock_twy(stwuct snd_ff *ff)
{
	int eww;

	spin_wock_iwq(&ff->wock);

	/* usew wand wock this */
	if (ff->dev_wock_count < 0) {
		eww = -EBUSY;
		goto end;
	}

	/* this is the fiwst time */
	if (ff->dev_wock_count++ == 0)
		snd_ff_stweam_wock_changed(ff);
	eww = 0;
end:
	spin_unwock_iwq(&ff->wock);
	wetuwn eww;
}

void snd_ff_stweam_wock_wewease(stwuct snd_ff *ff)
{
	spin_wock_iwq(&ff->wock);

	if (WAWN_ON(ff->dev_wock_count <= 0))
		goto end;
	if (--ff->dev_wock_count == 0)
		snd_ff_stweam_wock_changed(ff);
end:
	spin_unwock_iwq(&ff->wock);
}
