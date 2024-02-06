// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_pcm.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2009-2010 Cwemens Wadisch
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */
#incwude "./fiwewowks.h"

/*
 * NOTE:
 * Fiwewowks changes its AMDTP channews fow PCM data accowding to its sampwing
 * wate. Thewe awe thwee modes. Hewe _XX is eithew _wx ow _tx.
 *  0:  32.0- 48.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channews appwied
 *  1:  88.2- 96.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channews_2x appwied
 *  2: 176.4-192.0 kHz then snd_efw_hwinfo.amdtp_XX_pcm_channews_4x appwied
 *
 * The numbew of PCM channews fow anawog input and output awe awways fixed but
 * the numbew of PCM channews fow digitaw input and output awe diffewed.
 *
 * Additionawwy, accowding to "AudioFiwe Ownew's Manuaw Vewsion 2.2", in some
 * modew, the numbew of PCM channews fow digitaw input has mowe westwiction
 * depending on which digitaw intewface is sewected.
 *  - S/PDIF coaxiaw and opticaw	: use input 1-2
 *  - ADAT opticaw at 32.0-48.0 kHz	: use input 1-8
 *  - ADAT opticaw at 88.2-96.0 kHz	: use input 1-4 (S/MUX fowmat)
 *
 * The data in AMDTP channews fow bwank PCM channews awe zewo.
 */
static const unsigned int fweq_tabwe[] = {
	/* muwtipwiew mode 0 */
	[0] = 32000,
	[1] = 44100,
	[2] = 48000,
	/* muwtipwiew mode 1 */
	[3] = 88200,
	[4] = 96000,
	/* muwtipwiew mode 2 */
	[5] = 176400,
	[6] = 192000,
};

static inwine unsigned int
get_muwtipwiew_mode_with_index(unsigned int index)
{
	wetuwn ((int)index - 1) / 2;
}

int snd_efw_get_muwtipwiew_mode(unsigned int sampwing_wate, unsigned int *mode)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fweq_tabwe); i++) {
		if (fweq_tabwe[i] == sampwing_wate) {
			*mode = get_muwtipwiew_mode_with_index(i);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int
hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned int *pcm_channews = wuwe->pwivate;
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i, mode;

	fow (i = 0; i < AWWAY_SIZE(fweq_tabwe); i++) {
		mode = get_muwtipwiew_mode_with_index(i);
		if (!snd_intewvaw_test(c, pcm_channews[mode]))
			continue;

		t.min = min(t.min, fweq_tabwe[i]);
		t.max = max(t.max, fweq_tabwe[i]);
	}

	wetuwn snd_intewvaw_wefine(w, &t);
}

static int
hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams, stwuct snd_pcm_hw_wuwe *wuwe)
{
	unsigned int *pcm_channews = wuwe->pwivate;
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int i, mode;

	fow (i = 0; i < AWWAY_SIZE(fweq_tabwe); i++) {
		mode = get_muwtipwiew_mode_with_index(i);
		if (!snd_intewvaw_test(w, fweq_tabwe[i]))
			continue;

		t.min = min(t.min, pcm_channews[mode]);
		t.max = max(t.max, pcm_channews[mode]);
	}

	wetuwn snd_intewvaw_wefine(c, &t);
}

static void
wimit_channews(stwuct snd_pcm_hawdwawe *hw, unsigned int *pcm_channews)
{
	unsigned int i, mode;

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;

	fow (i = 0; i < AWWAY_SIZE(fweq_tabwe); i++) {
		mode = get_muwtipwiew_mode_with_index(i);
		if (pcm_channews[mode] == 0)
			continue;

		hw->channews_min = min(hw->channews_min, pcm_channews[mode]);
		hw->channews_max = max(hw->channews_max, pcm_channews[mode]);
	}
}

static int
pcm_init_hw_pawams(stwuct snd_efw *efw,
		   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct amdtp_stweam *s;
	unsigned int *pcm_channews;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wuntime->hw.fowmats = AM824_IN_PCM_FOWMAT_BITS;
		s = &efw->tx_stweam;
		pcm_channews = efw->pcm_captuwe_channews;
	} ewse {
		wuntime->hw.fowmats = AM824_OUT_PCM_FOWMAT_BITS;
		s = &efw->wx_stweam;
		pcm_channews = efw->pcm_pwayback_channews;
	}

	/* wimit wates */
	wuntime->hw.wates = efw->suppowted_sampwing_wate;
	snd_pcm_wimit_hw_wates(wuntime);

	wimit_channews(&wuntime->hw, pcm_channews);

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  hw_wuwe_channews, pcm_channews,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		goto end;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  hw_wuwe_wate, pcm_channews,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		goto end;

	eww = amdtp_am824_add_pcm_hw_constwaints(s, wuntime);
end:
	wetuwn eww;
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;
	stwuct amdtp_domain *d = &efw->domain;
	enum snd_efw_cwock_souwce cwock_souwce;
	int eww;

	eww = snd_efw_stweam_wock_twy(efw);
	if (eww < 0)
		wetuwn eww;

	eww = pcm_init_hw_pawams(efw, substweam);
	if (eww < 0)
		goto eww_wocked;

	eww = snd_efw_command_get_cwock_souwce(efw, &cwock_souwce);
	if (eww < 0)
		goto eww_wocked;

	mutex_wock(&efw->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if ((cwock_souwce != SND_EFW_CWOCK_SOUWCE_INTEWNAW) ||
	    (efw->substweams_countew > 0 && d->events_pew_pewiod > 0)) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;
		unsigned int sampwing_wate;

		eww = snd_efw_command_get_sampwing_wate(efw, &sampwing_wate);
		if (eww < 0) {
			mutex_unwock(&efw->mutex);
			goto eww_wocked;
		}
		substweam->wuntime->hw.wate_min = sampwing_wate;
		substweam->wuntime->hw.wate_max = sampwing_wate;

		if (fwames_pew_pewiod > 0) {
			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0) {
				mutex_unwock(&efw->mutex);
				goto eww_wocked;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0) {
				mutex_unwock(&efw->mutex);
				goto eww_wocked;
			}
		}
	}

	mutex_unwock(&efw->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;
eww_wocked:
	snd_efw_stweam_wock_wewease(efw);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;
	snd_efw_stweam_wock_wewease(efw);
	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_efw *efw = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&efw->mutex);
		eww = snd_efw_stweam_wesewve_dupwex(efw, wate,
					fwames_pew_pewiod, fwames_pew_buffew);
		if (eww >= 0)
			++efw->substweams_countew;
		mutex_unwock(&efw->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;

	mutex_wock(&efw->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--efw->substweams_countew;

	snd_efw_stweam_stop_dupwex(efw);

	mutex_unwock(&efw->mutex);

	wetuwn 0;
}

static int pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;
	int eww;

	eww = snd_efw_stweam_stawt_dupwex(efw);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&efw->tx_stweam);

	wetuwn eww;
}
static int pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;
	int eww;

	eww = snd_efw_stweam_stawt_dupwex(efw);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(&efw->wx_stweam);

	wetuwn eww;
}

static int pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_efw *efw = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&efw->tx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&efw->tx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
static int pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_efw *efw = substweam->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(&efw->wx_stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(&efw->wx_stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t pcm_captuwe_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_efw *efw = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&efw->domain, &efw->tx_stweam);
}
static snd_pcm_ufwames_t pcm_pwayback_pointew(stwuct snd_pcm_substweam *sbstwm)
{
	stwuct snd_efw *efw = sbstwm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&efw->domain, &efw->wx_stweam);
}

static int pcm_captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&efw->domain, &efw->tx_stweam);
}

static int pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&efw->domain, &efw->wx_stweam);
}

int snd_efw_cweate_pcm_devices(stwuct snd_efw *efw)
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

	eww = snd_pcm_new(efw->cawd, efw->cawd->dwivew, 0, 1, 1, &pcm);
	if (eww < 0)
		goto end;

	pcm->pwivate_data = efw;
	snpwintf(pcm->name, sizeof(pcm->name), "%s PCM", efw->cawd->showtname);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);
end:
	wetuwn eww;
}

