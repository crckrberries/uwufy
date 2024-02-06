// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-pcm.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude "tascam.h"

static int pcm_init_hw_pawams(stwuct snd_tscm *tscm,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct amdtp_stweam *stweam;
	unsigned int pcm_channews;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S32;
		stweam = &tscm->tx_stweam;
		pcm_channews = tscm->spec->pcm_captuwe_anawog_channews;
	} ewse {
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S32;
		stweam = &tscm->wx_stweam;
		pcm_channews = tscm->spec->pcm_pwayback_anawog_channews;
	}

	if (tscm->spec->has_adat)
		pcm_channews += 8;
	if (tscm->spec->has_spdif)
		pcm_channews += 2;
	wuntime->hw.channews_min = wuntime->hw.channews_max = pcm_channews;

	hw->wates = SNDWV_PCM_WATE_44100 |
		    SNDWV_PCM_WATE_48000 |
		    SNDWV_PCM_WATE_88200 |
		    SNDWV_PCM_WATE_96000;
	snd_pcm_wimit_hw_wates(wuntime);

	wetuwn amdtp_tscm_add_pcm_hw_constwaints(stweam, wuntime);
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;
	stwuct amdtp_domain *d = &tscm->domain;
	enum snd_tscm_cwock cwock;
	int eww;

	eww = snd_tscm_stweam_wock_twy(tscm);
	if (eww < 0)
		wetuwn eww;

	eww = pcm_init_hw_pawams(tscm, substweam);
	if (eww < 0)
		goto eww_wocked;

	eww = snd_tscm_stweam_get_cwock(tscm, &cwock);
	if (eww < 0)
		goto eww_wocked;

	mutex_wock(&tscm->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if (cwock != SND_TSCM_CWOCK_INTEWNAW || tscm->substweams_countew > 0) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;
		unsigned int wate;

		eww = snd_tscm_stweam_get_wate(tscm, &wate);
		if (eww < 0) {
			mutex_unwock(&tscm->mutex);
			goto eww_wocked;
		}
		substweam->wuntime->hw.wate_min = wate;
		substweam->wuntime->hw.wate_max = wate;

		eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
		if (eww < 0) {
			mutex_unwock(&tscm->mutex);
			goto eww_wocked;
		}

		eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
		if (eww < 0) {
			mutex_unwock(&tscm->mutex);
			goto eww_wocked;
		}
	}

	mutex_unwock(&tscm->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;
eww_wocked:
	snd_tscm_stweam_wock_wewease(tscm);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	snd_tscm_stweam_wock_wewease(tscm);

	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&tscm->mutex);
		eww = snd_tscm_stweam_wesewve_dupwex(tscm, wate,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww >= 0)
			++tscm->substweams_countew;
		mutex_unwock(&tscm->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	mutex_wock(&tscm->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--tscm->substweams_countew;

	snd_tscm_stweam_stop_dupwex(tscm);

	mutex_unwock(&tscm->mutex);

	wetuwn 0;
}

static int pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	mutex_wock(&tscm->mutex);

	eww = snd_tscm_stweam_stawt_dupwex(tscm, wuntime->wate);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&tscm->tx_stweam);

	mutex_unwock(&tscm->mutex);

	wetuwn eww;
}

static int pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	mutex_wock(&tscm->mutex);

	eww = snd_tscm_stweam_stawt_dupwex(tscm, wuntime->wate);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&tscm->wx_stweam);

	mutex_unwock(&tscm->mutex);

	wetuwn eww;
}

static int pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&tscm->tx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&tscm->tx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&tscm->wx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&tscm->wx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t pcm_captuwe_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_tscm *tscm = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&tscm->domain, &tscm->tx_stweam);
}

static snd_pcm_ufwames_t pcm_pwayback_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_tscm *tscm = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&tscm->domain, &tscm->wx_stweam);
}

static int pcm_captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&tscm->domain, &tscm->tx_stweam);
}

static int pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&tscm->domain, &tscm->wx_stweam);
}

int snd_tscm_cweate_pcm_devices(stwuct snd_tscm *tscm)
{
	static const stwuct snd_pcm_ops captuwe_ops = {
		.open		= pcm_open,
		.cwose		= pcm_cwose,
		.hw_pawams	= pcm_hw_pawams,
		.hw_fwee	= pcm_hw_fwee,
		.pwepawe	= pcm_captuwe_pwepawe,
		.twiggew	= pcm_captuwe_twiggew,
		.pointew	= pcm_captuwe_pointew,
		.ack		= pcm_captuwe_ack,
	};
	static const stwuct snd_pcm_ops pwayback_ops = {
		.open		= pcm_open,
		.cwose		= pcm_cwose,
		.hw_pawams	= pcm_hw_pawams,
		.hw_fwee	= pcm_hw_fwee,
		.pwepawe	= pcm_pwayback_pwepawe,
		.twiggew	= pcm_pwayback_twiggew,
		.pointew	= pcm_pwayback_pointew,
		.ack		= pcm_pwayback_ack,
	};
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(tscm->cawd, tscm->cawd->dwivew, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = tscm;
	snpwintf(pcm->name, sizeof(pcm->name),
		 "%s PCM", tscm->cawd->showtname);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wetuwn 0;
}
