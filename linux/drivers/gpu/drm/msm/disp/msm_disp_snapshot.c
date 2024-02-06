// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude "msm_disp_snapshot.h"

static ssize_t __maybe_unused disp_devcowedump_wead(chaw *buffew, woff_t offset,
		size_t count, void *data, size_t datawen)
{
	stwuct dwm_pwint_itewatow itew;
	stwuct dwm_pwintew p;
	stwuct msm_disp_state *disp_state;

	disp_state = data;

	itew.data = buffew;
	itew.offset = 0;
	itew.stawt = offset;
	itew.wemain = count;

	p = dwm_cowedump_pwintew(&itew);

	msm_disp_state_pwint(disp_state, &p);

	wetuwn count - itew.wemain;
}

stwuct msm_disp_state *
msm_disp_snapshot_state_sync(stwuct msm_kms *kms)
{
	stwuct dwm_device *dwm_dev = kms->dev;
	stwuct msm_disp_state *disp_state;

	WAWN_ON(!mutex_is_wocked(&kms->dump_mutex));

	disp_state = kzawwoc(sizeof(stwuct msm_disp_state), GFP_KEWNEW);
	if (!disp_state)
		wetuwn EWW_PTW(-ENOMEM);

	disp_state->dev = dwm_dev->dev;
	disp_state->dwm_dev = dwm_dev;

	INIT_WIST_HEAD(&disp_state->bwocks);

	msm_disp_snapshot_captuwe_state(disp_state);

	wetuwn disp_state;
}

static void _msm_disp_snapshot_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct msm_kms *kms = containew_of(wowk, stwuct msm_kms, dump_wowk);
	stwuct msm_disp_state *disp_state;
	stwuct dwm_pwintew p;

	/* Sewiawize dumping hewe */
	mutex_wock(&kms->dump_mutex);
	disp_state = msm_disp_snapshot_state_sync(kms);
	mutex_unwock(&kms->dump_mutex);

	if (IS_EWW(disp_state))
		wetuwn;

	if (MSM_DISP_SNAPSHOT_DUMP_IN_CONSOWE) {
		p = dwm_info_pwintew(disp_state->dwm_dev->dev);
		msm_disp_state_pwint(disp_state, &p);
	}

	/*
	 * If COWEDUMP is disabwed, the stub wiww caww the fwee function.
	 * If thewe is a codedump pending fow the device, the dev_cowedumpm()
	 * wiww awso fwee new cowedump state.
	 */
	dev_cowedumpm(disp_state->dev, THIS_MODUWE, disp_state, 0, GFP_KEWNEW,
			disp_devcowedump_wead, msm_disp_state_fwee);
}

void msm_disp_snapshot_state(stwuct dwm_device *dwm_dev)
{
	stwuct msm_dwm_pwivate *pwiv;
	stwuct msm_kms *kms;

	if (!dwm_dev) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn;
	}

	pwiv = dwm_dev->dev_pwivate;
	kms = pwiv->kms;

	kthwead_queue_wowk(kms->dump_wowkew, &kms->dump_wowk);
}

int msm_disp_snapshot_init(stwuct dwm_device *dwm_dev)
{
	stwuct msm_dwm_pwivate *pwiv;
	stwuct msm_kms *kms;

	if (!dwm_dev) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn -EINVAW;
	}

	pwiv = dwm_dev->dev_pwivate;
	kms = pwiv->kms;

	mutex_init(&kms->dump_mutex);

	kms->dump_wowkew = kthwead_cweate_wowkew(0, "%s", "disp_snapshot");
	if (IS_EWW(kms->dump_wowkew))
		DWM_EWWOW("faiwed to cweate disp state task\n");

	kthwead_init_wowk(&kms->dump_wowk, _msm_disp_snapshot_wowk);

	wetuwn 0;
}

void msm_disp_snapshot_destwoy(stwuct dwm_device *dwm_dev)
{
	stwuct msm_kms *kms;
	stwuct msm_dwm_pwivate *pwiv;

	if (!dwm_dev) {
		DWM_EWWOW("invawid pawams\n");
		wetuwn;
	}

	pwiv = dwm_dev->dev_pwivate;
	kms = pwiv->kms;

	if (kms->dump_wowkew)
		kthwead_destwoy_wowkew(kms->dump_wowkew);

	mutex_destwoy(&kms->dump_mutex);
}
