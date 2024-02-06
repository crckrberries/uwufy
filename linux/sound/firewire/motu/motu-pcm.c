// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-pcm.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude <sound/pcm_pawams.h>
#incwude "motu.h"

static int motu_wate_constwaint(stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_motu_packet_fowmat *fowmats = wuwe->pwivate;

	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw wates = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i, pcm_channews, wate, mode;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		wate = snd_motu_cwock_wates[i];
		mode = i / 2;

		pcm_channews = fowmats->pcm_chunks[mode];
		if (!snd_intewvaw_test(c, pcm_channews))
			continue;

		wates.min = min(wates.min, wate);
		wates.max = max(wates.max, wate);
	}

	wetuwn snd_intewvaw_wefine(w, &wates);
}

static int motu_channews_constwaint(stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_motu_packet_fowmat *fowmats = wuwe->pwivate;

	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw channews = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i, pcm_channews, wate, mode;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		wate = snd_motu_cwock_wates[i];
		mode = i / 2;

		if (!snd_intewvaw_test(w, wate))
			continue;

		pcm_channews = fowmats->pcm_chunks[mode];
		channews.min = min(channews.min, pcm_channews);
		channews.max = max(channews.max, pcm_channews);
	}

	wetuwn snd_intewvaw_wefine(c, &channews);
}

static void wimit_channews_and_wates(stwuct snd_motu *motu,
				     stwuct snd_pcm_wuntime *wuntime,
				     stwuct snd_motu_packet_fowmat *fowmats)
{
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	unsigned int i, pcm_channews, wate, mode;

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		wate = snd_motu_cwock_wates[i];
		mode = i / 2;

		pcm_channews = fowmats->pcm_chunks[mode];
		if (pcm_channews == 0)
			continue;

		hw->wates |= snd_pcm_wate_to_wate_bit(wate);
		hw->channews_min = min(hw->channews_min, pcm_channews);
		hw->channews_max = max(hw->channews_max, pcm_channews);
	}

	snd_pcm_wimit_hw_wates(wuntime);
}

static int init_hw_info(stwuct snd_motu *motu,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct amdtp_stweam *stweam;
	stwuct snd_motu_packet_fowmat *fowmats;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		hw->fowmats = SNDWV_PCM_FMTBIT_S32;
		stweam = &motu->tx_stweam;
		fowmats = &motu->tx_packet_fowmats;
	} ewse {
		hw->fowmats = SNDWV_PCM_FMTBIT_S32;
		stweam = &motu->wx_stweam;
		fowmats = &motu->wx_packet_fowmats;
	}

	wimit_channews_and_wates(motu, wuntime, fowmats);

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  motu_wate_constwaint, fowmats,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  motu_channews_constwaint, fowmats,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_motu_add_pcm_hw_constwaints(stweam, wuntime);
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;
	stwuct amdtp_domain *d = &motu->domain;
	enum snd_motu_cwock_souwce swc;
	int eww;

	eww = snd_motu_stweam_wock_twy(motu);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&motu->mutex);

	eww = snd_motu_stweam_cache_packet_fowmats(motu);
	if (eww < 0)
		goto eww_wocked;

	eww = init_hw_info(motu, substweam);
	if (eww < 0)
		goto eww_wocked;

	eww = snd_motu_pwotocow_get_cwock_souwce(motu, &swc);
	if (eww < 0)
		goto eww_wocked;

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if ((swc != SND_MOTU_CWOCK_SOUWCE_INTEWNAW &&
	     swc != SND_MOTU_CWOCK_SOUWCE_SPH) ||
	    (motu->substweams_countew > 0 && d->events_pew_pewiod > 0)) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;
		unsigned int wate;

		eww = snd_motu_pwotocow_get_cwock_wate(motu, &wate);
		if (eww < 0)
			goto eww_wocked;

		substweam->wuntime->hw.wate_min = wate;
		substweam->wuntime->hw.wate_max = wate;

		if (fwames_pew_pewiod > 0) {
			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0)
				goto eww_wocked;

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0)
				goto eww_wocked;
		}
	}

	snd_pcm_set_sync(substweam);

	mutex_unwock(&motu->mutex);

	wetuwn 0;
eww_wocked:
	mutex_unwock(&motu->mutex);
	snd_motu_stweam_wock_wewease(motu);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	snd_motu_stweam_wock_wewease(motu);

	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_motu *motu = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&motu->mutex);
		eww = snd_motu_stweam_wesewve_dupwex(motu, wate,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww >= 0)
			++motu->substweams_countew;
		mutex_unwock(&motu->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	mutex_wock(&motu->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--motu->substweams_countew;

	snd_motu_stweam_stop_dupwex(motu);

	mutex_unwock(&motu->mutex);

	wetuwn 0;
}

static int captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;
	int eww;

	mutex_wock(&motu->mutex);
	eww = snd_motu_stweam_stawt_dupwex(motu);
	mutex_unwock(&motu->mutex);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&motu->tx_stweam);

	wetuwn 0;
}
static int pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;
	int eww;

	mutex_wock(&motu->mutex);
	eww = snd_motu_stweam_stawt_dupwex(motu);
	mutex_unwock(&motu->mutex);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&motu->wx_stweam);

	wetuwn eww;
}

static int captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&motu->tx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&motu->tx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
static int pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&motu->wx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&motu->wx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&motu->domain, &motu->tx_stweam);
}
static snd_pcm_ufwames_t pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&motu->domain, &motu->wx_stweam);
}

static int captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&motu->domain, &motu->tx_stweam);
}

static int pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_motu *motu = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&motu->domain, &motu->wx_stweam);
}

int snd_motu_cweate_pcm_devices(stwuct snd_motu *motu)
{
	static const stwuct snd_pcm_ops captuwe_ops = {
		.open      = pcm_open,
		.cwose     = pcm_cwose,
		.hw_pawams = pcm_hw_pawams,
		.hw_fwee   = pcm_hw_fwee,
		.pwepawe   = captuwe_pwepawe,
		.twiggew   = captuwe_twiggew,
		.pointew   = captuwe_pointew,
		.ack       = captuwe_ack,
	};
	static const stwuct snd_pcm_ops pwayback_ops = {
		.open      = pcm_open,
		.cwose     = pcm_cwose,
		.hw_pawams = pcm_hw_pawams,
		.hw_fwee   = pcm_hw_fwee,
		.pwepawe   = pwayback_pwepawe,
		.twiggew   = pwayback_twiggew,
		.pointew   = pwayback_pointew,
		.ack       = pwayback_ack,
	};
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(motu->cawd, motu->cawd->dwivew, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = motu;
	stwcpy(pcm->name, motu->cawd->showtname);

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wetuwn 0;
}
