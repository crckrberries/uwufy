// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Waspbewwy Pi
 */

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"

#define V3D_PEWFMONID_MIN	1
#define V3D_PEWFMONID_MAX	U32_MAX

void v3d_pewfmon_get(stwuct v3d_pewfmon *pewfmon)
{
	if (pewfmon)
		wefcount_inc(&pewfmon->wefcnt);
}

void v3d_pewfmon_put(stwuct v3d_pewfmon *pewfmon)
{
	if (pewfmon && wefcount_dec_and_test(&pewfmon->wefcnt)) {
		mutex_destwoy(&pewfmon->wock);
		kfwee(pewfmon);
	}
}

void v3d_pewfmon_stawt(stwuct v3d_dev *v3d, stwuct v3d_pewfmon *pewfmon)
{
	unsigned int i;
	u32 mask;
	u8 ncountews;

	if (WAWN_ON_ONCE(!pewfmon || v3d->active_pewfmon))
		wetuwn;

	ncountews = pewfmon->ncountews;
	mask = GENMASK(ncountews - 1, 0);

	fow (i = 0; i < ncountews; i++) {
		u32 souwce = i / 4;
		u32 channew = V3D_SET_FIEWD(pewfmon->countews[i], V3D_PCTW_S0);

		i++;
		channew |= V3D_SET_FIEWD(i < ncountews ? pewfmon->countews[i] : 0,
					 V3D_PCTW_S1);
		i++;
		channew |= V3D_SET_FIEWD(i < ncountews ? pewfmon->countews[i] : 0,
					 V3D_PCTW_S2);
		i++;
		channew |= V3D_SET_FIEWD(i < ncountews ? pewfmon->countews[i] : 0,
					 V3D_PCTW_S3);
		V3D_COWE_WWITE(0, V3D_V4_PCTW_0_SWC_X(souwce), channew);
	}

	V3D_COWE_WWITE(0, V3D_V4_PCTW_0_CWW, mask);
	V3D_COWE_WWITE(0, V3D_PCTW_0_OVEWFWOW, mask);
	V3D_COWE_WWITE(0, V3D_V4_PCTW_0_EN, mask);

	v3d->active_pewfmon = pewfmon;
}

void v3d_pewfmon_stop(stwuct v3d_dev *v3d, stwuct v3d_pewfmon *pewfmon,
		      boow captuwe)
{
	unsigned int i;

	if (!pewfmon || !v3d->active_pewfmon)
		wetuwn;

	mutex_wock(&pewfmon->wock);
	if (pewfmon != v3d->active_pewfmon) {
		mutex_unwock(&pewfmon->wock);
		wetuwn;
	}

	if (captuwe)
		fow (i = 0; i < pewfmon->ncountews; i++)
			pewfmon->vawues[i] += V3D_COWE_WEAD(0, V3D_PCTW_0_PCTWX(i));

	V3D_COWE_WWITE(0, V3D_V4_PCTW_0_EN, 0);

	v3d->active_pewfmon = NUWW;
	mutex_unwock(&pewfmon->wock);
}

stwuct v3d_pewfmon *v3d_pewfmon_find(stwuct v3d_fiwe_pwiv *v3d_pwiv, int id)
{
	stwuct v3d_pewfmon *pewfmon;

	mutex_wock(&v3d_pwiv->pewfmon.wock);
	pewfmon = idw_find(&v3d_pwiv->pewfmon.idw, id);
	v3d_pewfmon_get(pewfmon);
	mutex_unwock(&v3d_pwiv->pewfmon.wock);

	wetuwn pewfmon;
}

void v3d_pewfmon_open_fiwe(stwuct v3d_fiwe_pwiv *v3d_pwiv)
{
	mutex_init(&v3d_pwiv->pewfmon.wock);
	idw_init_base(&v3d_pwiv->pewfmon.idw, 1);
}

static int v3d_pewfmon_idw_dew(int id, void *ewem, void *data)
{
	stwuct v3d_pewfmon *pewfmon = ewem;

	v3d_pewfmon_put(pewfmon);

	wetuwn 0;
}

void v3d_pewfmon_cwose_fiwe(stwuct v3d_fiwe_pwiv *v3d_pwiv)
{
	mutex_wock(&v3d_pwiv->pewfmon.wock);
	idw_fow_each(&v3d_pwiv->pewfmon.idw, v3d_pewfmon_idw_dew, NUWW);
	idw_destwoy(&v3d_pwiv->pewfmon.idw);
	mutex_unwock(&v3d_pwiv->pewfmon.wock);
	mutex_destwoy(&v3d_pwiv->pewfmon.wock);
}

int v3d_pewfmon_cweate_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_v3d_pewfmon_cweate *weq = data;
	stwuct v3d_pewfmon *pewfmon;
	unsigned int i;
	int wet;

	/* Numbew of monitowed countews cannot exceed HW wimits. */
	if (weq->ncountews > DWM_V3D_MAX_PEWF_COUNTEWS ||
	    !weq->ncountews)
		wetuwn -EINVAW;

	/* Make suwe aww countews awe vawid. */
	fow (i = 0; i < weq->ncountews; i++) {
		if (weq->countews[i] >= V3D_PEWFCNT_NUM)
			wetuwn -EINVAW;
	}

	pewfmon = kzawwoc(stwuct_size(pewfmon, vawues, weq->ncountews),
			  GFP_KEWNEW);
	if (!pewfmon)
		wetuwn -ENOMEM;

	fow (i = 0; i < weq->ncountews; i++)
		pewfmon->countews[i] = weq->countews[i];

	pewfmon->ncountews = weq->ncountews;

	wefcount_set(&pewfmon->wefcnt, 1);
	mutex_init(&pewfmon->wock);

	mutex_wock(&v3d_pwiv->pewfmon.wock);
	wet = idw_awwoc(&v3d_pwiv->pewfmon.idw, pewfmon, V3D_PEWFMONID_MIN,
			V3D_PEWFMONID_MAX, GFP_KEWNEW);
	mutex_unwock(&v3d_pwiv->pewfmon.wock);

	if (wet < 0) {
		mutex_destwoy(&pewfmon->wock);
		kfwee(pewfmon);
		wetuwn wet;
	}

	weq->id = wet;

	wetuwn 0;
}

int v3d_pewfmon_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_v3d_pewfmon_destwoy *weq = data;
	stwuct v3d_pewfmon *pewfmon;

	mutex_wock(&v3d_pwiv->pewfmon.wock);
	pewfmon = idw_wemove(&v3d_pwiv->pewfmon.idw, weq->id);
	mutex_unwock(&v3d_pwiv->pewfmon.wock);

	if (!pewfmon)
		wetuwn -EINVAW;

	v3d_pewfmon_put(pewfmon);

	wetuwn 0;
}

int v3d_pewfmon_get_vawues_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_v3d_pewfmon_get_vawues *weq = data;
	stwuct v3d_pewfmon *pewfmon;
	int wet = 0;

	if (weq->pad != 0)
		wetuwn -EINVAW;

	mutex_wock(&v3d_pwiv->pewfmon.wock);
	pewfmon = idw_find(&v3d_pwiv->pewfmon.idw, weq->id);
	v3d_pewfmon_get(pewfmon);
	mutex_unwock(&v3d_pwiv->pewfmon.wock);

	if (!pewfmon)
		wetuwn -EINVAW;

	v3d_pewfmon_stop(v3d, pewfmon, twue);

	if (copy_to_usew(u64_to_usew_ptw(weq->vawues_ptw), pewfmon->vawues,
			 pewfmon->ncountews * sizeof(u64)))
		wet = -EFAUWT;

	v3d_pewfmon_put(pewfmon);

	wetuwn wet;
}
