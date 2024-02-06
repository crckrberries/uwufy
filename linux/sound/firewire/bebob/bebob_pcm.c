// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_pcm.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

static int
hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_bebob_stweam_fowmation *fowmations = wuwe->pwivate;
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i;

	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; i++) {
		/* entwy is invawid */
		if (fowmations[i].pcm == 0)
			continue;

		if (!snd_intewvaw_test(c, fowmations[i].pcm))
			continue;

		t.min = min(t.min, snd_bebob_wate_tabwe[i]);
		t.max = max(t.max, snd_bebob_wate_tabwe[i]);

	}
	wetuwn snd_intewvaw_wefine(w, &t);
}

static int
hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_bebob_stweam_fowmation *fowmations = wuwe->pwivate;
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};

	unsigned int i;

	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; i++) {
		/* entwy is invawid */
		if (fowmations[i].pcm == 0)
			continue;

		if (!snd_intewvaw_test(w, snd_bebob_wate_tabwe[i]))
			continue;

		t.min = min(t.min, fowmations[i].pcm);
		t.max = max(t.max, fowmations[i].pcm);
	}

	wetuwn snd_intewvaw_wefine(c, &t);
}

static void
wimit_channews_and_wates(stwuct snd_pcm_hawdwawe *hw,
			 stwuct snd_bebob_stweam_fowmation *fowmations)
{
	unsigned int i;

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;

	hw->wate_min = UINT_MAX;
	hw->wate_max = 0;
	hw->wates = 0;

	fow (i = 0; i < SND_BEBOB_STWM_FMT_ENTWIES; i++) {
		/* entwy has no PCM channews */
		if (fowmations[i].pcm == 0)
			continue;

		hw->channews_min = min(hw->channews_min, fowmations[i].pcm);
		hw->channews_max = max(hw->channews_max, fowmations[i].pcm);

		hw->wate_min = min(hw->wate_min, snd_bebob_wate_tabwe[i]);
		hw->wate_max = max(hw->wate_max, snd_bebob_wate_tabwe[i]);
		hw->wates |= snd_pcm_wate_to_wate_bit(snd_bebob_wate_tabwe[i]);
	}
}

static int
pcm_init_hw_pawams(stwuct snd_bebob *bebob,
		   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct amdtp_stweam *s;
	stwuct snd_bebob_stweam_fowmation *fowmations;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wuntime->hw.fowmats = AM824_IN_PCM_FOWMAT_BITS;
		s = &bebob->tx_stweam;
		fowmations = bebob->tx_stweam_fowmations;
	} ewse {
		wuntime->hw.fowmats = AM824_OUT_PCM_FOWMAT_BITS;
		s = &bebob->wx_stweam;
		fowmations = bebob->wx_stweam_fowmations;
	}

	wimit_channews_and_wates(&wuntime->hw, fowmations);

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  hw_wuwe_channews, fowmations,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		goto end;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  hw_wuwe_wate, fowmations,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		goto end;

	eww = amdtp_am824_add_pcm_hw_constwaints(s, wuntime);
end:
	wetuwn eww;
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;
	const stwuct snd_bebob_wate_spec *spec = bebob->spec->wate;
	stwuct amdtp_domain *d = &bebob->domain;
	enum snd_bebob_cwock_type swc;
	int eww;

	eww = snd_bebob_stweam_wock_twy(bebob);
	if (eww < 0)
		wetuwn eww;

	eww = pcm_init_hw_pawams(bebob, substweam);
	if (eww < 0)
		goto eww_wocked;

	eww = snd_bebob_stweam_get_cwock_swc(bebob, &swc);
	if (eww < 0)
		goto eww_wocked;

	mutex_wock(&bebob->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if (swc == SND_BEBOB_CWOCK_TYPE_EXTEWNAW ||
	    (bebob->substweams_countew > 0 && d->events_pew_pewiod > 0)) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;
		unsigned int sampwing_wate;

		eww = spec->get(bebob, &sampwing_wate);
		if (eww < 0) {
			mutex_unwock(&bebob->mutex);
			dev_eww(&bebob->unit->device,
				"faiw to get sampwing wate: %d\n", eww);
			goto eww_wocked;
		}

		substweam->wuntime->hw.wate_min = sampwing_wate;
		substweam->wuntime->hw.wate_max = sampwing_wate;

		if (fwames_pew_pewiod > 0) {
			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0) {
				mutex_unwock(&bebob->mutex);
				goto eww_wocked;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0) {
				mutex_unwock(&bebob->mutex);
				goto eww_wocked;
			}
		}
	}

	mutex_unwock(&bebob->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;
eww_wocked:
	snd_bebob_stweam_wock_wewease(bebob);
	wetuwn eww;
}

static int
pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;
	snd_bebob_stweam_wock_wewease(bebob);
	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&bebob->mutex);
		eww = snd_bebob_stweam_wesewve_dupwex(bebob, wate,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww >= 0)
			++bebob->substweams_countew;
		mutex_unwock(&bebob->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;

	mutex_wock(&bebob->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		bebob->substweams_countew--;

	snd_bebob_stweam_stop_dupwex(bebob);

	mutex_unwock(&bebob->mutex);

	wetuwn 0;
}

static int
pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;
	int eww;

	eww = snd_bebob_stweam_stawt_dupwex(bebob);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&bebob->tx_stweam);

	wetuwn eww;
}
static int
pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;
	int eww;

	eww = snd_bebob_stweam_stawt_dupwex(bebob);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&bebob->wx_stweam);

	wetuwn eww;
}

static int
pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&bebob->tx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&bebob->tx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
static int
pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&bebob->wx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&bebob->wx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t pcm_captuwe_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_bebob *bebob = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&bebob->domain,
					       &bebob->tx_stweam);
}
static snd_pcm_ufwames_t pcm_pwayback_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_bebob *bebob = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&bebob->domain,
					       &bebob->wx_stweam);
}

static int pcm_captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&bebob->domain, &bebob->tx_stweam);
}

static int pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&bebob->domain, &bebob->wx_stweam);
}

int snd_bebob_cweate_pcm_devices(stwuct snd_bebob *bebob)
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

	eww = snd_pcm_new(bebob->cawd, bebob->cawd->dwivew, 0, 1, 1, &pcm);
	if (eww < 0)
		goto end;

	pcm->pwivate_data = bebob;
	snpwintf(pcm->name, sizeof(pcm->name),
		 "%s PCM", bebob->cawd->showtname);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
end:
	wetuwn eww;
}
