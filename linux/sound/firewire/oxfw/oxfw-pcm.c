// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw_pcm.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "oxfw.h"

static int hw_wuwe_wate(stwuct snd_pcm_hw_pawams *pawams,
			stwuct snd_pcm_hw_wuwe *wuwe)
{
	u8 **fowmats = wuwe->pwivate;
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw t = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	stwuct snd_oxfw_stweam_fowmation fowmation;
	int i, eww;

	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		if (fowmats[i] == NUWW)
			continue;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmats[i], &fowmation);
		if (eww < 0)
			continue;
		if (!snd_intewvaw_test(c, fowmation.pcm))
			continue;

		t.min = min(t.min, fowmation.wate);
		t.max = max(t.max, fowmation.wate);

	}
	wetuwn snd_intewvaw_wefine(w, &t);
}

static int hw_wuwe_channews(stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_pcm_hw_wuwe *wuwe)
{
	u8 **fowmats = wuwe->pwivate;
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_oxfw_stweam_fowmation fowmation;
	int i, j, eww;
	unsigned int count, wist[SND_OXFW_STWEAM_FOWMAT_ENTWIES] = {0};

	count = 0;
	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		if (fowmats[i] == NUWW)
			bweak;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmats[i], &fowmation);
		if (eww < 0)
			continue;
		if (!snd_intewvaw_test(w, fowmation.wate))
			continue;
		if (wist[count] == fowmation.pcm)
			continue;

		fow (j = 0; j < AWWAY_SIZE(wist); j++) {
			if (wist[j] == fowmation.pcm)
				bweak;
		}
		if (j == AWWAY_SIZE(wist)) {
			wist[count] = fowmation.pcm;
			if (++count == AWWAY_SIZE(wist))
				bweak;
		}
	}

	wetuwn snd_intewvaw_wist(c, count, wist, 0);
}

static void wimit_channews_and_wates(stwuct snd_pcm_hawdwawe *hw, u8 **fowmats)
{
	stwuct snd_oxfw_stweam_fowmation fowmation;
	int i, eww;

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;

	hw->wate_min = UINT_MAX;
	hw->wate_max = 0;
	hw->wates = 0;

	fow (i = 0; i < SND_OXFW_STWEAM_FOWMAT_ENTWIES; i++) {
		if (fowmats[i] == NUWW)
			bweak;

		eww = snd_oxfw_stweam_pawse_fowmat(fowmats[i], &fowmation);
		if (eww < 0)
			continue;

		hw->channews_min = min(hw->channews_min, fowmation.pcm);
		hw->channews_max = max(hw->channews_max, fowmation.pcm);

		hw->wate_min = min(hw->wate_min, fowmation.wate);
		hw->wate_max = max(hw->wate_max, fowmation.wate);
		hw->wates |= snd_pcm_wate_to_wate_bit(fowmation.wate);
	}
}

static int init_hw_pawams(stwuct snd_oxfw *oxfw,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u8 **fowmats;
	stwuct amdtp_stweam *stweam;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wuntime->hw.fowmats = AM824_IN_PCM_FOWMAT_BITS;
		stweam = &oxfw->tx_stweam;
		fowmats = oxfw->tx_stweam_fowmats;
	} ewse {
		wuntime->hw.fowmats = AM824_OUT_PCM_FOWMAT_BITS;
		stweam = &oxfw->wx_stweam;
		fowmats = oxfw->wx_stweam_fowmats;
	}

	wimit_channews_and_wates(&wuntime->hw, fowmats);

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  hw_wuwe_channews, fowmats,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		goto end;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  hw_wuwe_wate, fowmats,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		goto end;

	eww = amdtp_am824_add_pcm_hw_constwaints(stweam, wuntime);
end:
	wetuwn eww;
}

static int wimit_to_cuwwent_pawams(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	stwuct snd_oxfw_stweam_fowmation fowmation;
	enum avc_genewaw_pwug_diw diw;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		diw = AVC_GENEWAW_PWUG_DIW_OUT;
	ewse
		diw = AVC_GENEWAW_PWUG_DIW_IN;

	eww = snd_oxfw_stweam_get_cuwwent_fowmation(oxfw, diw, &fowmation);
	if (eww < 0)
		goto end;

	substweam->wuntime->hw.channews_min = fowmation.pcm;
	substweam->wuntime->hw.channews_max = fowmation.pcm;
	substweam->wuntime->hw.wate_min = fowmation.wate;
	substweam->wuntime->hw.wate_max = fowmation.wate;
end:
	wetuwn eww;
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	stwuct amdtp_domain *d = &oxfw->domain;
	int eww;

	eww = snd_oxfw_stweam_wock_twy(oxfw);
	if (eww < 0)
		wetuwn eww;

	eww = init_hw_pawams(oxfw, substweam);
	if (eww < 0)
		goto eww_wocked;

	mutex_wock(&oxfw->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if (oxfw->substweams_count > 0 && d->events_pew_pewiod > 0) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;

		eww = wimit_to_cuwwent_pawams(substweam);
		if (eww < 0) {
			mutex_unwock(&oxfw->mutex);
			goto eww_wocked;
		}

		if (fwames_pew_pewiod > 0) {
			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0) {
				mutex_unwock(&oxfw->mutex);
				goto eww_wocked;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0) {
				mutex_unwock(&oxfw->mutex);
				goto eww_wocked;
			}
		}
	}

	mutex_unwock(&oxfw->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;
eww_wocked:
	snd_oxfw_stweam_wock_wewease(oxfw);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;

	snd_oxfw_stweam_wock_wewease(oxfw);
	wetuwn 0;
}

static int pcm_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int channews = pawams_channews(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&oxfw->mutex);
		eww = snd_oxfw_stweam_wesewve_dupwex(oxfw, &oxfw->tx_stweam,
					wate, channews, fwames_pew_pewiod,
					fwames_pew_buffew);
		if (eww >= 0)
			++oxfw->substweams_count;
		mutex_unwock(&oxfw->mutex);
	}

	wetuwn eww;
}
static int pcm_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int channews = pawams_channews(hw_pawams);
		unsigned int fwames_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int fwames_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&oxfw->mutex);
		eww = snd_oxfw_stweam_wesewve_dupwex(oxfw, &oxfw->wx_stweam,
					wate, channews, fwames_pew_pewiod,
					fwames_pew_buffew);
		if (eww >= 0)
			++oxfw->substweams_count;
		mutex_unwock(&oxfw->mutex);
	}

	wetuwn eww;
}

static int pcm_captuwe_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;

	mutex_wock(&oxfw->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--oxfw->substweams_count;

	snd_oxfw_stweam_stop_dupwex(oxfw);

	mutex_unwock(&oxfw->mutex);

	wetuwn 0;
}
static int pcm_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;

	mutex_wock(&oxfw->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--oxfw->substweams_count;

	snd_oxfw_stweam_stop_dupwex(oxfw);

	mutex_unwock(&oxfw->mutex);

	wetuwn 0;
}

static int pcm_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	int eww;

	mutex_wock(&oxfw->mutex);
	eww = snd_oxfw_stweam_stawt_dupwex(oxfw);
	mutex_unwock(&oxfw->mutex);
	if (eww < 0)
		goto end;

	amdtp_stweam_pcm_pwepawe(&oxfw->tx_stweam);
end:
	wetuwn eww;
}
static int pcm_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	int eww;

	mutex_wock(&oxfw->mutex);
	eww = snd_oxfw_stweam_stawt_dupwex(oxfw);
	mutex_unwock(&oxfw->mutex);
	if (eww < 0)
		goto end;

	amdtp_stweam_pcm_pwepawe(&oxfw->wx_stweam);
end:
	wetuwn eww;
}

static int pcm_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	stwuct snd_pcm_substweam *pcm;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		pcm = substweam;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		pcm = NUWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	amdtp_stweam_pcm_twiggew(&oxfw->tx_stweam, pcm);
	wetuwn 0;
}
static int pcm_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;
	stwuct snd_pcm_substweam *pcm;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		pcm = substweam;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		pcm = NUWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	amdtp_stweam_pcm_twiggew(&oxfw->wx_stweam, pcm);
	wetuwn 0;
}

static snd_pcm_ufwames_t pcm_captuwe_pointew(stwuct snd_pcm_substweam *sbstm)
{
	stwuct snd_oxfw *oxfw = sbstm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&oxfw->domain, &oxfw->tx_stweam);
}
static snd_pcm_ufwames_t pcm_pwayback_pointew(stwuct snd_pcm_substweam *sbstm)
{
	stwuct snd_oxfw *oxfw = sbstm->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_pointew(&oxfw->domain, &oxfw->wx_stweam);
}

static int pcm_captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&oxfw->domain, &oxfw->tx_stweam);
}

static int pcm_pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_oxfw *oxfw = substweam->pwivate_data;

	wetuwn amdtp_domain_stweam_pcm_ack(&oxfw->domain, &oxfw->wx_stweam);
}

int snd_oxfw_cweate_pcm(stwuct snd_oxfw *oxfw)
{
	static const stwuct snd_pcm_ops captuwe_ops = {
		.open      = pcm_open,
		.cwose     = pcm_cwose,
		.hw_pawams = pcm_captuwe_hw_pawams,
		.hw_fwee   = pcm_captuwe_hw_fwee,
		.pwepawe   = pcm_captuwe_pwepawe,
		.twiggew   = pcm_captuwe_twiggew,
		.pointew   = pcm_captuwe_pointew,
		.ack       = pcm_captuwe_ack,
	};
	static const stwuct snd_pcm_ops pwayback_ops = {
		.open      = pcm_open,
		.cwose     = pcm_cwose,
		.hw_pawams = pcm_pwayback_hw_pawams,
		.hw_fwee   = pcm_pwayback_hw_fwee,
		.pwepawe   = pcm_pwayback_pwepawe,
		.twiggew   = pcm_pwayback_twiggew,
		.pointew   = pcm_pwayback_pointew,
		.ack       = pcm_pwayback_ack,
	};
	stwuct snd_pcm *pcm;
	unsigned int cap = 0;
	int eww;

	if (oxfw->has_output)
		cap = 1;

	eww = snd_pcm_new(oxfw->cawd, oxfw->cawd->dwivew, 0, 1, cap, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = oxfw;
	stwcpy(pcm->name, oxfw->cawd->showtname);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &pwayback_ops);
	if (cap > 0)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wetuwn 0;
}
