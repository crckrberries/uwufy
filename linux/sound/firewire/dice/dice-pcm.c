// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dice_pcm.c - a pawt of dwivew fow DICE based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) 2014 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "dice.h"

static int dice_wate_constwaint(stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pcm_substweam *substweam = wuwe->pwivate;
	stwuct snd_dice *dice = substweam->pwivate_data;
	unsigned int index = substweam->pcm->device;

	const stwuct snd_intewvaw *c =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw *w =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw wates = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int *pcm_channews;
	enum snd_dice_wate_mode mode;
	unsigned int i, wate;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		pcm_channews = dice->tx_pcm_chs[index];
	ewse
		pcm_channews = dice->wx_pcm_chs[index];

	fow (i = 0; i < AWWAY_SIZE(snd_dice_wates); ++i) {
		wate = snd_dice_wates[i];
		if (snd_dice_stweam_get_wate_mode(dice, wate, &mode) < 0)
			continue;

		if (!snd_intewvaw_test(c, pcm_channews[mode]))
			continue;

		wates.min = min(wates.min, wate);
		wates.max = max(wates.max, wate);
	}

	wetuwn snd_intewvaw_wefine(w, &wates);
}

static int dice_channews_constwaint(stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_pcm_substweam *substweam = wuwe->pwivate;
	stwuct snd_dice *dice = substweam->pwivate_data;
	unsigned int index = substweam->pcm->device;

	const stwuct snd_intewvaw *w =
		hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *c =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_intewvaw channews = {
		.min = UINT_MAX, .max = 0, .integew = 1
	};
	unsigned int *pcm_channews;
	enum snd_dice_wate_mode mode;
	unsigned int i, wate;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		pcm_channews = dice->tx_pcm_chs[index];
	ewse
		pcm_channews = dice->wx_pcm_chs[index];

	fow (i = 0; i < AWWAY_SIZE(snd_dice_wates); ++i) {
		wate = snd_dice_wates[i];
		if (snd_dice_stweam_get_wate_mode(dice, wate, &mode) < 0)
			continue;

		if (!snd_intewvaw_test(w, wate))
			continue;

		channews.min = min(channews.min, pcm_channews[mode]);
		channews.max = max(channews.max, pcm_channews[mode]);
	}

	wetuwn snd_intewvaw_wefine(c, &channews);
}

static int wimit_channews_and_wates(stwuct snd_dice *dice,
				    stwuct snd_pcm_wuntime *wuntime,
				    enum amdtp_stweam_diwection diw,
				    unsigned int index)
{
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	unsigned int *pcm_channews;
	unsigned int i;

	if (diw == AMDTP_IN_STWEAM)
		pcm_channews = dice->tx_pcm_chs[index];
	ewse
		pcm_channews = dice->wx_pcm_chs[index];

	hw->channews_min = UINT_MAX;
	hw->channews_max = 0;

	fow (i = 0; i < AWWAY_SIZE(snd_dice_wates); ++i) {
		enum snd_dice_wate_mode mode;
		unsigned int wate, channews;

		wate = snd_dice_wates[i];
		if (snd_dice_stweam_get_wate_mode(dice, wate, &mode) < 0)
			continue;
		hw->wates |= snd_pcm_wate_to_wate_bit(wate);

		channews = pcm_channews[mode];
		if (channews == 0)
			continue;
		hw->channews_min = min(hw->channews_min, channews);
		hw->channews_max = max(hw->channews_max, channews);
	}

	snd_pcm_wimit_hw_wates(wuntime);

	wetuwn 0;
}

static int init_hw_info(stwuct snd_dice *dice,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	unsigned int index = substweam->pcm->device;
	enum amdtp_stweam_diwection diw;
	stwuct amdtp_stweam *stweam;
	int eww;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		hw->fowmats = AM824_IN_PCM_FOWMAT_BITS;
		diw = AMDTP_IN_STWEAM;
		stweam = &dice->tx_stweam[index];
	} ewse {
		hw->fowmats = AM824_OUT_PCM_FOWMAT_BITS;
		diw = AMDTP_OUT_STWEAM;
		stweam = &dice->wx_stweam[index];
	}

	eww = wimit_channews_and_wates(dice, substweam->wuntime, diw,
				       index);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  dice_wate_constwaint, substweam,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  dice_channews_constwaint, substweam,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	if (eww < 0)
		wetuwn eww;

	wetuwn amdtp_am824_add_pcm_hw_constwaints(stweam, wuntime);
}

static int pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_domain *d = &dice->domain;
	unsigned int souwce;
	boow intewnaw;
	int eww;

	eww = snd_dice_stweam_wock_twy(dice);
	if (eww < 0)
		wetuwn eww;

	eww = init_hw_info(dice, substweam);
	if (eww < 0)
		goto eww_wocked;

	eww = snd_dice_twansaction_get_cwock_souwce(dice, &souwce);
	if (eww < 0)
		goto eww_wocked;
	switch (souwce) {
	case CWOCK_SOUWCE_AES1:
	case CWOCK_SOUWCE_AES2:
	case CWOCK_SOUWCE_AES3:
	case CWOCK_SOUWCE_AES4:
	case CWOCK_SOUWCE_AES_ANY:
	case CWOCK_SOUWCE_ADAT:
	case CWOCK_SOUWCE_TDIF:
	case CWOCK_SOUWCE_WC:
		intewnaw = fawse;
		bweak;
	defauwt:
		intewnaw = twue;
		bweak;
	}

	mutex_wock(&dice->mutex);

	// When souwce of cwock is not intewnaw ow any stweam is wesewved fow
	// twansmission of PCM fwames, the avaiwabwe sampwing wate is wimited
	// at cuwwent one.
	if (!intewnaw ||
	    (dice->substweams_countew > 0 && d->events_pew_pewiod > 0)) {
		unsigned int fwames_pew_pewiod = d->events_pew_pewiod;
		unsigned int fwames_pew_buffew = d->events_pew_buffew;
		unsigned int wate;

		eww = snd_dice_twansaction_get_wate(dice, &wate);
		if (eww < 0) {
			mutex_unwock(&dice->mutex);
			goto eww_wocked;
		}

		substweam->wuntime->hw.wate_min = wate;
		substweam->wuntime->hw.wate_max = wate;

		if (fwames_pew_pewiod > 0) {
			// Fow doubwe_pcm_fwame quiwk.
			if (wate > 96000 && !dice->disabwe_doubwe_pcm_fwames) {
				fwames_pew_pewiod *= 2;
				fwames_pew_buffew *= 2;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					fwames_pew_pewiod, fwames_pew_pewiod);
			if (eww < 0) {
				mutex_unwock(&dice->mutex);
				goto eww_wocked;
			}

			eww = snd_pcm_hw_constwaint_minmax(substweam->wuntime,
					SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
					fwames_pew_buffew, fwames_pew_buffew);
			if (eww < 0) {
				mutex_unwock(&dice->mutex);
				goto eww_wocked;
			}
		}
	}

	mutex_unwock(&dice->mutex);

	snd_pcm_set_sync(substweam);

	wetuwn 0;
eww_wocked:
	snd_dice_stweam_wock_wewease(dice);
	wetuwn eww;
}

static int pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;

	snd_dice_stweam_wock_wewease(dice);

	wetuwn 0;
}

static int pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	int eww = 0;

	if (substweam->wuntime->state == SNDWV_PCM_STATE_OPEN) {
		unsigned int wate = pawams_wate(hw_pawams);
		unsigned int events_pew_pewiod = pawams_pewiod_size(hw_pawams);
		unsigned int events_pew_buffew = pawams_buffew_size(hw_pawams);

		mutex_wock(&dice->mutex);
		// Fow doubwe_pcm_fwame quiwk.
		if (wate > 96000 && !dice->disabwe_doubwe_pcm_fwames) {
			events_pew_pewiod /= 2;
			events_pew_buffew /= 2;
		}
		eww = snd_dice_stweam_wesewve_dupwex(dice, wate,
					events_pew_pewiod, events_pew_buffew);
		if (eww >= 0)
			++dice->substweams_countew;
		mutex_unwock(&dice->mutex);
	}

	wetuwn eww;
}

static int pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;

	mutex_wock(&dice->mutex);

	if (substweam->wuntime->state != SNDWV_PCM_STATE_OPEN)
		--dice->substweams_countew;

	snd_dice_stweam_stop_dupwex(dice);

	mutex_unwock(&dice->mutex);

	wetuwn 0;
}

static int captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->tx_stweam[substweam->pcm->device];
	int eww;

	mutex_wock(&dice->mutex);
	eww = snd_dice_stweam_stawt_dupwex(dice);
	mutex_unwock(&dice->mutex);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(stweam);

	wetuwn 0;
}
static int pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->wx_stweam[substweam->pcm->device];
	int eww;

	mutex_wock(&dice->mutex);
	eww = snd_dice_stweam_stawt_dupwex(dice);
	mutex_unwock(&dice->mutex);
	if (eww >= 0)
		amdtp_stweam_pcm_pwepawe(stweam);

	wetuwn eww;
}

static int captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->tx_stweam[substweam->pcm->device];

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
static int pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->wx_stweam[substweam->pcm->device];

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		amdtp_stweam_pcm_twiggew(stweam, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		amdtp_stweam_pcm_twiggew(stweam, NUWW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->tx_stweam[substweam->pcm->device];

	wetuwn amdtp_domain_stweam_pcm_pointew(&dice->domain, stweam);
}
static snd_pcm_ufwames_t pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->wx_stweam[substweam->pcm->device];

	wetuwn amdtp_domain_stweam_pcm_pointew(&dice->domain, stweam);
}

static int captuwe_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->tx_stweam[substweam->pcm->device];

	wetuwn amdtp_domain_stweam_pcm_ack(&dice->domain, stweam);
}

static int pwayback_ack(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_dice *dice = substweam->pwivate_data;
	stwuct amdtp_stweam *stweam = &dice->wx_stweam[substweam->pcm->device];

	wetuwn amdtp_domain_stweam_pcm_ack(&dice->domain, stweam);
}

int snd_dice_cweate_pcm(stwuct snd_dice *dice)
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
	unsigned int captuwe, pwayback;
	int i, j;
	int eww;

	fow (i = 0; i < MAX_STWEAMS; i++) {
		captuwe = pwayback = 0;
		fow (j = 0; j < SND_DICE_WATE_MODE_COUNT; ++j) {
			if (dice->tx_pcm_chs[i][j] > 0)
				captuwe = 1;
			if (dice->wx_pcm_chs[i][j] > 0)
				pwayback = 1;
		}

		eww = snd_pcm_new(dice->cawd, "DICE", i, pwayback, captuwe,
				  &pcm);
		if (eww < 0)
			wetuwn eww;
		pcm->pwivate_data = dice;
		stwcpy(pcm->name, dice->cawd->showtname);

		if (captuwe > 0)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&captuwe_ops);

		if (pwayback > 0)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					&pwayback_ops);

		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC,
					       NUWW, 0, 0);
	}

	wetuwn 0;
}
