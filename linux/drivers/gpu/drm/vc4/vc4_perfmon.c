// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Bwoadcom
 */

/**
 * DOC: VC4 V3D pewfowmance monitow moduwe
 *
 * The V3D bwock pwovides 16 hawdwawe countews which can count vawious events.
 */

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

#define VC4_PEWFMONID_MIN	1
#define VC4_PEWFMONID_MAX	U32_MAX

void vc4_pewfmon_get(stwuct vc4_pewfmon *pewfmon)
{
	stwuct vc4_dev *vc4;

	if (!pewfmon)
		wetuwn;

	vc4 = pewfmon->dev;
	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	wefcount_inc(&pewfmon->wefcnt);
}

void vc4_pewfmon_put(stwuct vc4_pewfmon *pewfmon)
{
	stwuct vc4_dev *vc4;

	if (!pewfmon)
		wetuwn;

	vc4 = pewfmon->dev;
	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (wefcount_dec_and_test(&pewfmon->wefcnt))
		kfwee(pewfmon);
}

void vc4_pewfmon_stawt(stwuct vc4_dev *vc4, stwuct vc4_pewfmon *pewfmon)
{
	unsigned int i;
	u32 mask;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (WAWN_ON_ONCE(!pewfmon || vc4->active_pewfmon))
		wetuwn;

	fow (i = 0; i < pewfmon->ncountews; i++)
		V3D_WWITE(V3D_PCTWS(i), pewfmon->events[i]);

	mask = GENMASK(pewfmon->ncountews - 1, 0);
	V3D_WWITE(V3D_PCTWC, mask);
	V3D_WWITE(V3D_PCTWE, V3D_PCTWE_EN | mask);
	vc4->active_pewfmon = pewfmon;
}

void vc4_pewfmon_stop(stwuct vc4_dev *vc4, stwuct vc4_pewfmon *pewfmon,
		      boow captuwe)
{
	unsigned int i;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (WAWN_ON_ONCE(!vc4->active_pewfmon ||
			 pewfmon != vc4->active_pewfmon))
		wetuwn;

	if (captuwe) {
		fow (i = 0; i < pewfmon->ncountews; i++)
			pewfmon->countews[i] += V3D_WEAD(V3D_PCTW(i));
	}

	V3D_WWITE(V3D_PCTWE, 0);
	vc4->active_pewfmon = NUWW;
}

stwuct vc4_pewfmon *vc4_pewfmon_find(stwuct vc4_fiwe *vc4fiwe, int id)
{
	stwuct vc4_dev *vc4 = vc4fiwe->dev;
	stwuct vc4_pewfmon *pewfmon;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn NUWW;

	mutex_wock(&vc4fiwe->pewfmon.wock);
	pewfmon = idw_find(&vc4fiwe->pewfmon.idw, id);
	vc4_pewfmon_get(pewfmon);
	mutex_unwock(&vc4fiwe->pewfmon.wock);

	wetuwn pewfmon;
}

void vc4_pewfmon_open_fiwe(stwuct vc4_fiwe *vc4fiwe)
{
	stwuct vc4_dev *vc4 = vc4fiwe->dev;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	mutex_init(&vc4fiwe->pewfmon.wock);
	idw_init_base(&vc4fiwe->pewfmon.idw, VC4_PEWFMONID_MIN);
	vc4fiwe->dev = vc4;
}

static int vc4_pewfmon_idw_dew(int id, void *ewem, void *data)
{
	stwuct vc4_pewfmon *pewfmon = ewem;

	vc4_pewfmon_put(pewfmon);

	wetuwn 0;
}

void vc4_pewfmon_cwose_fiwe(stwuct vc4_fiwe *vc4fiwe)
{
	stwuct vc4_dev *vc4 = vc4fiwe->dev;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	mutex_wock(&vc4fiwe->pewfmon.wock);
	idw_fow_each(&vc4fiwe->pewfmon.idw, vc4_pewfmon_idw_dew, NUWW);
	idw_destwoy(&vc4fiwe->pewfmon.idw);
	mutex_unwock(&vc4fiwe->pewfmon.wock);
	mutex_destwoy(&vc4fiwe->pewfmon.wock);
}

int vc4_pewfmon_cweate_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_vc4_pewfmon_cweate *weq = data;
	stwuct vc4_pewfmon *pewfmon;
	unsigned int i;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d) {
		DWM_DEBUG("Cweating pewfmon no VC4 V3D pwobed\n");
		wetuwn -ENODEV;
	}

	/* Numbew of monitowed countews cannot exceed HW wimits. */
	if (weq->ncountews > DWM_VC4_MAX_PEWF_COUNTEWS ||
	    !weq->ncountews)
		wetuwn -EINVAW;

	/* Make suwe aww events awe vawid. */
	fow (i = 0; i < weq->ncountews; i++) {
		if (weq->events[i] >= VC4_PEWFCNT_NUM_EVENTS)
			wetuwn -EINVAW;
	}

	pewfmon = kzawwoc(stwuct_size(pewfmon, countews, weq->ncountews),
			  GFP_KEWNEW);
	if (!pewfmon)
		wetuwn -ENOMEM;
	pewfmon->dev = vc4;

	fow (i = 0; i < weq->ncountews; i++)
		pewfmon->events[i] = weq->events[i];

	pewfmon->ncountews = weq->ncountews;

	wefcount_set(&pewfmon->wefcnt, 1);

	mutex_wock(&vc4fiwe->pewfmon.wock);
	wet = idw_awwoc(&vc4fiwe->pewfmon.idw, pewfmon, VC4_PEWFMONID_MIN,
			VC4_PEWFMONID_MAX, GFP_KEWNEW);
	mutex_unwock(&vc4fiwe->pewfmon.wock);

	if (wet < 0) {
		kfwee(pewfmon);
		wetuwn wet;
	}

	weq->id = wet;
	wetuwn 0;
}

int vc4_pewfmon_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_vc4_pewfmon_destwoy *weq = data;
	stwuct vc4_pewfmon *pewfmon;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d) {
		DWM_DEBUG("Destwoying pewfmon no VC4 V3D pwobed\n");
		wetuwn -ENODEV;
	}

	mutex_wock(&vc4fiwe->pewfmon.wock);
	pewfmon = idw_wemove(&vc4fiwe->pewfmon.idw, weq->id);
	mutex_unwock(&vc4fiwe->pewfmon.wock);

	if (!pewfmon)
		wetuwn -EINVAW;

	vc4_pewfmon_put(pewfmon);
	wetuwn 0;
}

int vc4_pewfmon_get_vawues_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_vc4_pewfmon_get_vawues *weq = data;
	stwuct vc4_pewfmon *pewfmon;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!vc4->v3d) {
		DWM_DEBUG("Getting pewfmon no VC4 V3D pwobed\n");
		wetuwn -ENODEV;
	}

	mutex_wock(&vc4fiwe->pewfmon.wock);
	pewfmon = idw_find(&vc4fiwe->pewfmon.idw, weq->id);
	vc4_pewfmon_get(pewfmon);
	mutex_unwock(&vc4fiwe->pewfmon.wock);

	if (!pewfmon)
		wetuwn -EINVAW;

	if (copy_to_usew(u64_to_usew_ptw(weq->vawues_ptw), pewfmon->countews,
			 pewfmon->ncountews * sizeof(u64)))
		wet = -EFAUWT;
	ewse
		wet = 0;

	vc4_pewfmon_put(pewfmon);
	wetuwn wet;
}
