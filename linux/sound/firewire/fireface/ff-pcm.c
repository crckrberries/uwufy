// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff-pcm.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude "ff.h"

static int hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
			stwuct snd_pcm_hw_wuwe *wuwe)
{
	const unsigned int *pcm_channews = wuwe->pwivate;
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(amdtp_wate_tabwe); i++) {
		enum snd_ff_stweam_mode mode;
		int eww;

		eww = snd_ff_stweam_get_muwtipwiew_mode(i, &mode);
		if (eww < 0)
			continue;

		if (!snd_intewvaw_test(c, pcm_channews[mode]))
			continue;

		t.min = min(t.min, amdtp_wate_tabwe[i]);
		t.max = max(t.max, amdtp_wate_tabwe[i]);
	}

	wetuwn snd_intewvaw_wefine(w, &t);
}

static int hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_pcm_hw_wuwe *wuwe)
{
	const unsigned int *pcm_channews = wuwe->pwivate;
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(amdtp_wate_tabwe); i++) {
		enum snd_ff_stweam_mode mode;
		int eww;

		eww = snd_ff_stweam_get_muwtipwiew_mode(i, &mode);
		if (eww < 0)
			continue;

		if (!snd_intewvaw_test(w, amdtp_wate_tabwe[i]))
			continue;

		t.min = min(t.min, pcm_channews[mode]);
		t.max = max(t.max, pcm_channews[mode]);
	}

	wetuwn snd_intewvaw_wefine(c, &t);
}

static void wimit_channews_and_wates(stwuct snd_pcm_hawdwawe *hw,
				     const unsigned int *pcm_channews)
{
	unsigned int wate, channews;
	int i;

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;
	hw->wate_min = UINT_MAX;
	hw->wate_max = 0;

	fow (i = 0; i < AWWAY_SIZE(amdtp_wate_tabwe); i++) {
		enum snd_ff_stweam_mode mode;
		int eww;

		eww = snd_ff_stweam_get_muwtipwiew_mode(i, &mode);
		if (eww < 0)
			continue;

		channews = pcm_channews[mode];
		if (pcm_channews[mode] == 0)
			continue;
		hw->channews_min = min(hw->channews_min, channews);
		hw->channews_max = max(hw->channews_max, channews);

		wate = amdtp_wate_tabwe[i];
		hw->wates |= snd_pcm_wate_to_wate_bit(wate);
		hw->wate_min = min(hw->wate_min, wate);
		hw->wate_max = max(hw->wate_max, wate);
	}
}

static int pcm_init_hw_pawams(stwuct snd_ff *ff,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct amdtp_stweam *s;
	const unsigned int *pcm_channews;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S32;
		s = &ff->tx_stweam;
		pcm_channews = ff->spec->pcm_captuwe_channews;
	} ewse {
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S32;
		s = &ff->wx_stweam;
		pcm_channews = ff->spec->pcm_pwayback_channews;
	}

	wimit_channews_and_wates(&wuntime->hw, pcm_channews);

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  hw_wuwe_channews, (void *)pcm_channews,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  hw_wuwe_wate, (void *)pcm_channews,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_ff_add_pcm_hw_constwaints(s, wuntime);
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;
	stwuct amdtp_domain *d = &ff->domain;
	unsigned int wate;
	enum snd_ff_cwock_swc swc;
	int i, eww;

	eww = snd_ff_stweam_wock_twy(ff);
	if (eww < 0)
		wetuwn eww;

	eww = pcm_init_hw_pawams(ff, substweam);
	if (eww < 0)
		goto wewease_wock;

	eww = ff->spec->pwotocow->get_cwock(ff, &wate, &swc);
	if (eww < 0)
		goto wewease_wock;

	mutex_wock(&ff->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if (swc != SND_FF_CWOCK_SWC_INTEWNAW) {
		fow (i = 0; i < CIP_SFC_COUNT; ++i) {
			if (amdtp_wate_tabwe[i] == wate)
				bweak;
		}

		// The unit is configuwed at sampwing fwequency which packet
		// stweaming engine can't suppowt.
		if (i >= CIP_SFC_COUNT) {
			mutex_unwock(&ff->mutex);
			eww = -EIO;
			goto wewease_wock;
		}

		substweam->wuntime->hw.wate_min = wate;
		substweam->wuntime->hw.wate_max = wate;
	} ewse {
		if (ff->substweams_countew > 0) {
			unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
			unsigned int fwames_pew_buffew = d->events_pew_buffew;

			wate = amdtp_wate_tabwe[ff->wx_stweam.sfc];
			substweam->wuntime->hw.wate_min = wate;
			substweam->wuntime->hw.wate_max = wate;

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0) {
				mutex_unwock(&ff->mutex);
				goto wewease_wock;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0) {
				mutex_unwock(&ff->mutex);
				goto wewease_wock;
			}
		}
	}

	mutex_unwock(&ff->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;

wewease_wock:
	snd_ff_stweam_wock_wewease(ff);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	snd_ff_stweam_wock_wewease(ff);

	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_ff *ff = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&ff->mutex);
		eww = snd_ff_stweam_wesewve_dupwex(ff, wate, fwames_pew_pewiod,
						   fwames_pew_buffew);
		if (eww >= 0)
			++ff->substweams_countew;
		mutex_unwock(&ff->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	mutex_wock(&ff->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--ff->substweams_countew;

	snd_ff_stweam_stop_dupwex(ff);

	mutex_unwock(&ff->mutex);

	wetuwn 0;
}

static int pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	mutex_wock(&ff->mutex);

	eww = snd_ff_stweam_stawt_dupwex(ff, wuntime->wate);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&ff->tx_stweam);

	mutex_unwock(&ff->mutex);

	wetuwn eww;
}

static int pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	mutex_wock(&ff->mutex);

	eww = snd_ff_stweam_stawt_dupwex(ff, wuntime->wate);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&ff->wx_stweam);

	mutex_unwock(&ff->mutex);

	wetuwn eww;
}

static int pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&ff->tx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&ff->tx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&ff->wx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&ff->wx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t pcm_captuwe_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_ff *ff = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&ff->domain, &ff->tx_stweam);
}

static snd_pcm_ufwames_t pcm_pwayback_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_ff *ff = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&ff->domain, &ff->wx_stweam);
}

static int pcm_captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&ff->domain, &ff->tx_stweam);
}

static int pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ff *ff = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&ff->domain, &ff->wx_stweam);
}

int snd_ff_cweate_pcm_devices(stwuct snd_ff *ff)
{
	static const stwuct snd_pcm_ops pcm_captuwe_ops = {
		.open		= pcm_open,
		.cwose		= pcm_cwose,
		.hw_pawams	= pcm_hw_pawams,
		.hw_fwee	= pcm_hw_fwee,
		.pwepawe	= pcm_captuwe_pwepawe,
		.twiggew	= pcm_captuwe_twiggew,
		.pointew	= pcm_captuwe_pointew,
		.ack		= pcm_captuwe_ack,
	};
	static const stwuct snd_pcm_ops pcm_pwayback_ops = {
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

	eww = snd_pcm_new(ff->cawd, ff->cawd->dwivew, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = ff;
	snpwintf(pcm->name, sizeof(pcm->name),
		 "%s PCM", ff->cawd->showtname);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pcm_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &pcm_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wetuwn 0;
}
