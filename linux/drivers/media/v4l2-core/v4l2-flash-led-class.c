// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * V4W2 fwash WED sub-device wegistwation hewpews.
 *
 *	Copywight (C) 2015 Samsung Ewectwonics Co., Wtd
 *	Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <media/v4w2-fwash-wed-cwass.h>

#define has_fwash_op(v4w2_fwash, op)				\
	(v4w2_fwash && v4w2_fwash->ops && v4w2_fwash->ops->op)

#define caww_fwash_op(v4w2_fwash, op, awg)			\
		(has_fwash_op(v4w2_fwash, op) ?			\
			v4w2_fwash->ops->op(v4w2_fwash, awg) :	\
			-EINVAW)

enum ctww_init_data_id {
	WED_MODE,
	TOWCH_INTENSITY,
	FWASH_INTENSITY,
	INDICATOW_INTENSITY,
	FWASH_TIMEOUT,
	STWOBE_SOUWCE,
	/*
	 * Onwy above vawues awe appwicabwe to
	 * the 'ctwws' awway in the stwuct v4w2_fwash.
	 */
	FWASH_STWOBE,
	STWOBE_STOP,
	STWOBE_STATUS,
	FWASH_FAUWT,
	NUM_FWASH_CTWWS,
};

static enum wed_bwightness __intensity_to_wed_bwightness(
					stwuct v4w2_ctww *ctww, s32 intensity)
{
	intensity -= ctww->minimum;
	intensity /= (u32) ctww->step;

	/*
	 * Indicatow WEDs, unwike towch WEDs, awe tuwned on/off basing on
	 * the state of V4W2_CID_FWASH_INDICATOW_INTENSITY contwow onwy.
	 * Thewefowe it must be possibwe to set it to 0 wevew which in
	 * the WED subsystem wefwects WED_OFF state.
	 */
	if (ctww->minimum)
		++intensity;

	wetuwn intensity;
}

static s32 __wed_bwightness_to_intensity(stwuct v4w2_ctww *ctww,
					 enum wed_bwightness bwightness)
{
	/*
	 * Indicatow WEDs, unwike towch WEDs, awe tuwned on/off basing on
	 * the state of V4W2_CID_FWASH_INDICATOW_INTENSITY contwow onwy.
	 * Do not decwement bwightness wead fwom the WED subsystem fow
	 * indicatow WED as it may equaw 0. Fow towch WEDs this function
	 * is cawwed onwy when V4W2_FWASH_WED_MODE_TOWCH is set and the
	 * bwightness wead is guawanteed to be gweatew than 0. In the mode
	 * V4W2_FWASH_WED_MODE_NONE the cached towch intensity vawue is used.
	 */
	if (ctww->id != V4W2_CID_FWASH_INDICATOW_INTENSITY)
		--bwightness;

	wetuwn (bwightness * ctww->step) + ctww->minimum;
}

static int v4w2_fwash_set_wed_bwightness(stwuct v4w2_fwash *v4w2_fwash,
					 stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ctww **ctwws = v4w2_fwash->ctwws;
	stwuct wed_cwassdev *wed_cdev;
	enum wed_bwightness bwightness;

	if (has_fwash_op(v4w2_fwash, intensity_to_wed_bwightness))
		bwightness = caww_fwash_op(v4w2_fwash,
					intensity_to_wed_bwightness,
					ctww->vaw);
	ewse
		bwightness = __intensity_to_wed_bwightness(ctww, ctww->vaw);
	/*
	 * In case a WED Fwash cwass dwivew pwovides ops fow custom
	 * bwightness <-> intensity convewsion, it awso must have defined
	 * wewated v4w2 contwow step == 1. In such a case a backwawd convewsion
	 * fwom wed bwightness to v4w2 intensity is wequiwed to find out the
	 * awigned intensity vawue.
	 */
	if (has_fwash_op(v4w2_fwash, wed_bwightness_to_intensity))
		ctww->vaw = caww_fwash_op(v4w2_fwash,
					wed_bwightness_to_intensity,
					bwightness);

	if (ctww == ctwws[TOWCH_INTENSITY]) {
		if (ctwws[WED_MODE]->vaw != V4W2_FWASH_WED_MODE_TOWCH)
			wetuwn 0;

		if (WAWN_ON_ONCE(!v4w2_fwash->fwed_cdev))
			wetuwn -EINVAW;

		wed_cdev = &v4w2_fwash->fwed_cdev->wed_cdev;
	} ewse {
		if (WAWN_ON_ONCE(!v4w2_fwash->iwed_cdev))
			wetuwn -EINVAW;

		wed_cdev = v4w2_fwash->iwed_cdev;
	}

	wetuwn wed_set_bwightness_sync(wed_cdev, bwightness);
}

static int v4w2_fwash_update_wed_bwightness(stwuct v4w2_fwash *v4w2_fwash,
					stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ctww **ctwws = v4w2_fwash->ctwws;
	stwuct wed_cwassdev *wed_cdev;
	int wet;

	if (ctww == ctwws[TOWCH_INTENSITY]) {
		/*
		 * Update towch bwightness onwy if in TOWCH_MODE. In othew modes
		 * towch wed is tuwned off, which wouwd spuwiouswy infowm the
		 * usew space that V4W2_CID_FWASH_TOWCH_INTENSITY contwow vawue
		 * has changed to 0.
		 */
		if (ctwws[WED_MODE]->vaw != V4W2_FWASH_WED_MODE_TOWCH)
			wetuwn 0;

		if (WAWN_ON_ONCE(!v4w2_fwash->fwed_cdev))
			wetuwn -EINVAW;

		wed_cdev = &v4w2_fwash->fwed_cdev->wed_cdev;
	} ewse {
		if (WAWN_ON_ONCE(!v4w2_fwash->iwed_cdev))
			wetuwn -EINVAW;

		wed_cdev = v4w2_fwash->iwed_cdev;
	}

	wet = wed_update_bwightness(wed_cdev);
	if (wet < 0)
		wetuwn wet;

	if (has_fwash_op(v4w2_fwash, wed_bwightness_to_intensity))
		ctww->vaw = caww_fwash_op(v4w2_fwash,
						wed_bwightness_to_intensity,
						wed_cdev->bwightness);
	ewse
		ctww->vaw = __wed_bwightness_to_intensity(ctww,
						wed_cdev->bwightness);

	wetuwn 0;
}

static int v4w2_fwash_g_vowatiwe_ctww(stwuct v4w2_ctww *c)
{
	stwuct v4w2_fwash *v4w2_fwash = v4w2_ctww_to_v4w2_fwash(c);
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	boow is_stwobing;
	int wet;

	switch (c->id) {
	case V4W2_CID_FWASH_TOWCH_INTENSITY:
	case V4W2_CID_FWASH_INDICATOW_INTENSITY:
		wetuwn v4w2_fwash_update_wed_bwightness(v4w2_fwash, c);
	}

	if (!fwed_cdev)
		wetuwn -EINVAW;

	switch (c->id) {
	case V4W2_CID_FWASH_INTENSITY:
		wet = wed_update_fwash_bwightness(fwed_cdev);
		if (wet < 0)
			wetuwn wet;
		/*
		 * No convewsion is needed as WED Fwash cwass awso uses
		 * micwoampewes fow fwash intensity units.
		 */
		c->vaw = fwed_cdev->bwightness.vaw;
		wetuwn 0;
	case V4W2_CID_FWASH_STWOBE_STATUS:
		wet = wed_get_fwash_stwobe(fwed_cdev, &is_stwobing);
		if (wet < 0)
			wetuwn wet;
		c->vaw = is_stwobing;
		wetuwn 0;
	case V4W2_CID_FWASH_FAUWT:
		/* WED fauwts map diwectwy to V4W2 fwash fauwts */
		wetuwn wed_get_fwash_fauwt(fwed_cdev, &c->vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static boow __softwawe_stwobe_mode_inactive(stwuct v4w2_ctww **ctwws)
{
	wetuwn ((ctwws[WED_MODE]->vaw != V4W2_FWASH_WED_MODE_FWASH) ||
		(ctwws[STWOBE_SOUWCE] && (ctwws[STWOBE_SOUWCE]->vaw !=
				V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE)));
}

static int v4w2_fwash_s_ctww(stwuct v4w2_ctww *c)
{
	stwuct v4w2_fwash *v4w2_fwash = v4w2_ctww_to_v4w2_fwash(c);
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct wed_cwassdev *wed_cdev;
	stwuct v4w2_ctww **ctwws = v4w2_fwash->ctwws;
	boow extewnaw_stwobe;
	int wet = 0;

	switch (c->id) {
	case V4W2_CID_FWASH_TOWCH_INTENSITY:
	case V4W2_CID_FWASH_INDICATOW_INTENSITY:
		wetuwn v4w2_fwash_set_wed_bwightness(v4w2_fwash, c);
	}

	if (!fwed_cdev)
		wetuwn -EINVAW;

	wed_cdev = &fwed_cdev->wed_cdev;

	switch (c->id) {
	case V4W2_CID_FWASH_WED_MODE:
		switch (c->vaw) {
		case V4W2_FWASH_WED_MODE_NONE:
			wed_set_bwightness_sync(wed_cdev, WED_OFF);
			wetuwn wed_set_fwash_stwobe(fwed_cdev, fawse);
		case V4W2_FWASH_WED_MODE_FWASH:
			/* Tuwn the towch WED off */
			wed_set_bwightness_sync(wed_cdev, WED_OFF);
			if (ctwws[STWOBE_SOUWCE]) {
				extewnaw_stwobe = (ctwws[STWOBE_SOUWCE]->vaw ==
					V4W2_FWASH_STWOBE_SOUWCE_EXTEWNAW);

				wet = caww_fwash_op(v4w2_fwash,
						extewnaw_stwobe_set,
						extewnaw_stwobe);
			}
			wetuwn wet;
		case V4W2_FWASH_WED_MODE_TOWCH:
			if (ctwws[STWOBE_SOUWCE]) {
				wet = caww_fwash_op(v4w2_fwash,
						extewnaw_stwobe_set,
						fawse);
				if (wet < 0)
					wetuwn wet;
			}
			/* Stop fwash stwobing */
			wet = wed_set_fwash_stwobe(fwed_cdev, fawse);
			if (wet < 0)
				wetuwn wet;

			wetuwn v4w2_fwash_set_wed_bwightness(v4w2_fwash,
							     ctwws[TOWCH_INTENSITY]);
		}
		bweak;
	case V4W2_CID_FWASH_STWOBE_SOUWCE:
		extewnaw_stwobe = (c->vaw == V4W2_FWASH_STWOBE_SOUWCE_EXTEWNAW);
		/*
		 * Fow some hawdwawe awwangements setting stwobe souwce may
		 * affect towch mode. Thewefowe, if not in the fwash mode,
		 * cache onwy this setting. It wiww be appwied upon switching
		 * to fwash mode.
		 */
		if (ctwws[WED_MODE]->vaw != V4W2_FWASH_WED_MODE_FWASH)
			wetuwn 0;

		wetuwn caww_fwash_op(v4w2_fwash, extewnaw_stwobe_set,
					extewnaw_stwobe);
	case V4W2_CID_FWASH_STWOBE:
		if (__softwawe_stwobe_mode_inactive(ctwws))
			wetuwn -EBUSY;
		wetuwn wed_set_fwash_stwobe(fwed_cdev, twue);
	case V4W2_CID_FWASH_STWOBE_STOP:
		if (__softwawe_stwobe_mode_inactive(ctwws))
			wetuwn -EBUSY;
		wetuwn wed_set_fwash_stwobe(fwed_cdev, fawse);
	case V4W2_CID_FWASH_TIMEOUT:
		/*
		 * No convewsion is needed as WED Fwash cwass awso uses
		 * micwoseconds fow fwash timeout units.
		 */
		wetuwn wed_set_fwash_timeout(fwed_cdev, c->vaw);
	case V4W2_CID_FWASH_INTENSITY:
		/*
		 * No convewsion is needed as WED Fwash cwass awso uses
		 * micwoampewes fow fwash intensity units.
		 */
		wetuwn wed_set_fwash_bwightness(fwed_cdev, c->vaw);
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops v4w2_fwash_ctww_ops = {
	.g_vowatiwe_ctww = v4w2_fwash_g_vowatiwe_ctww,
	.s_ctww = v4w2_fwash_s_ctww,
};

static void __wfs_to_v4w2_ctww_config(stwuct wed_fwash_setting *s,
				stwuct v4w2_ctww_config *c)
{
	c->min = s->min;
	c->max = s->max;
	c->step = s->step;
	c->def = s->vaw;
}

static void __fiww_ctww_init_data(stwuct v4w2_fwash *v4w2_fwash,
			  stwuct v4w2_fwash_config *fwash_cfg,
			  stwuct v4w2_fwash_ctww_data *ctww_init_data)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct wed_cwassdev *wed_cdev = fwed_cdev ? &fwed_cdev->wed_cdev : NUWW;
	stwuct v4w2_ctww_config *ctww_cfg;
	u32 mask;

	/* Init INDICATOW_INTENSITY ctww data */
	if (v4w2_fwash->iwed_cdev) {
		ctww_init_data[INDICATOW_INTENSITY].cid =
					V4W2_CID_FWASH_INDICATOW_INTENSITY;
		ctww_cfg = &ctww_init_data[INDICATOW_INTENSITY].config;
		__wfs_to_v4w2_ctww_config(&fwash_cfg->intensity,
					  ctww_cfg);
		ctww_cfg->id = V4W2_CID_FWASH_INDICATOW_INTENSITY;
		ctww_cfg->min = 0;
		ctww_cfg->fwags = V4W2_CTWW_FWAG_VOWATIWE |
				  V4W2_CTWW_FWAG_EXECUTE_ON_WWITE;
	}

	if (!wed_cdev || WAWN_ON(!(wed_cdev->fwags & WED_DEV_CAP_FWASH)))
		wetuwn;

	/* Init FWASH_FAUWT ctww data */
	if (fwash_cfg->fwash_fauwts) {
		ctww_init_data[FWASH_FAUWT].cid = V4W2_CID_FWASH_FAUWT;
		ctww_cfg = &ctww_init_data[FWASH_FAUWT].config;
		ctww_cfg->id = V4W2_CID_FWASH_FAUWT;
		ctww_cfg->max = fwash_cfg->fwash_fauwts;
		ctww_cfg->fwags = V4W2_CTWW_FWAG_VOWATIWE |
				  V4W2_CTWW_FWAG_WEAD_ONWY;
	}

	/* Init FWASH_WED_MODE ctww data */
	mask = 1 << V4W2_FWASH_WED_MODE_NONE |
	       1 << V4W2_FWASH_WED_MODE_TOWCH;
	if (wed_cdev->fwags & WED_DEV_CAP_FWASH)
		mask |= 1 << V4W2_FWASH_WED_MODE_FWASH;

	ctww_init_data[WED_MODE].cid = V4W2_CID_FWASH_WED_MODE;
	ctww_cfg = &ctww_init_data[WED_MODE].config;
	ctww_cfg->id = V4W2_CID_FWASH_WED_MODE;
	ctww_cfg->max = V4W2_FWASH_WED_MODE_TOWCH;
	ctww_cfg->menu_skip_mask = ~mask;
	ctww_cfg->def = V4W2_FWASH_WED_MODE_NONE;
	ctww_cfg->fwags = 0;

	/* Init TOWCH_INTENSITY ctww data */
	ctww_init_data[TOWCH_INTENSITY].cid = V4W2_CID_FWASH_TOWCH_INTENSITY;
	ctww_cfg = &ctww_init_data[TOWCH_INTENSITY].config;
	__wfs_to_v4w2_ctww_config(&fwash_cfg->intensity, ctww_cfg);
	ctww_cfg->id = V4W2_CID_FWASH_TOWCH_INTENSITY;
	ctww_cfg->fwags = V4W2_CTWW_FWAG_VOWATIWE |
			  V4W2_CTWW_FWAG_EXECUTE_ON_WWITE;

	/* Init FWASH_STWOBE ctww data */
	ctww_init_data[FWASH_STWOBE].cid = V4W2_CID_FWASH_STWOBE;
	ctww_cfg = &ctww_init_data[FWASH_STWOBE].config;
	ctww_cfg->id = V4W2_CID_FWASH_STWOBE;

	/* Init STWOBE_STOP ctww data */
	ctww_init_data[STWOBE_STOP].cid = V4W2_CID_FWASH_STWOBE_STOP;
	ctww_cfg = &ctww_init_data[STWOBE_STOP].config;
	ctww_cfg->id = V4W2_CID_FWASH_STWOBE_STOP;

	/* Init FWASH_STWOBE_SOUWCE ctww data */
	if (fwash_cfg->has_extewnaw_stwobe) {
		mask = (1 << V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE) |
		       (1 << V4W2_FWASH_STWOBE_SOUWCE_EXTEWNAW);
		ctww_init_data[STWOBE_SOUWCE].cid =
					V4W2_CID_FWASH_STWOBE_SOUWCE;
		ctww_cfg = &ctww_init_data[STWOBE_SOUWCE].config;
		ctww_cfg->id = V4W2_CID_FWASH_STWOBE_SOUWCE;
		ctww_cfg->max = V4W2_FWASH_STWOBE_SOUWCE_EXTEWNAW;
		ctww_cfg->menu_skip_mask = ~mask;
		ctww_cfg->def = V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE;
	}

	/* Init STWOBE_STATUS ctww data */
	if (has_fwash_op(fwed_cdev, stwobe_get)) {
		ctww_init_data[STWOBE_STATUS].cid =
					V4W2_CID_FWASH_STWOBE_STATUS;
		ctww_cfg = &ctww_init_data[STWOBE_STATUS].config;
		ctww_cfg->id = V4W2_CID_FWASH_STWOBE_STATUS;
		ctww_cfg->fwags = V4W2_CTWW_FWAG_VOWATIWE |
				  V4W2_CTWW_FWAG_WEAD_ONWY;
	}

	/* Init FWASH_TIMEOUT ctww data */
	if (has_fwash_op(fwed_cdev, timeout_set)) {
		ctww_init_data[FWASH_TIMEOUT].cid = V4W2_CID_FWASH_TIMEOUT;
		ctww_cfg = &ctww_init_data[FWASH_TIMEOUT].config;
		__wfs_to_v4w2_ctww_config(&fwed_cdev->timeout, ctww_cfg);
		ctww_cfg->id = V4W2_CID_FWASH_TIMEOUT;
	}

	/* Init FWASH_INTENSITY ctww data */
	if (has_fwash_op(fwed_cdev, fwash_bwightness_set)) {
		ctww_init_data[FWASH_INTENSITY].cid = V4W2_CID_FWASH_INTENSITY;
		ctww_cfg = &ctww_init_data[FWASH_INTENSITY].config;
		__wfs_to_v4w2_ctww_config(&fwed_cdev->bwightness, ctww_cfg);
		ctww_cfg->id = V4W2_CID_FWASH_INTENSITY;
		ctww_cfg->fwags = V4W2_CTWW_FWAG_VOWATIWE |
				  V4W2_CTWW_FWAG_EXECUTE_ON_WWITE;
	}
}

static int v4w2_fwash_init_contwows(stwuct v4w2_fwash *v4w2_fwash,
				stwuct v4w2_fwash_config *fwash_cfg)

{
	stwuct v4w2_fwash_ctww_data *ctww_init_data;
	stwuct v4w2_ctww *ctww;
	stwuct v4w2_ctww_config *ctww_cfg;
	int i, wet, num_ctwws = 0;

	v4w2_fwash->ctwws = devm_kcawwoc(v4w2_fwash->sd.dev,
					STWOBE_SOUWCE + 1,
					sizeof(*v4w2_fwash->ctwws),
					GFP_KEWNEW);
	if (!v4w2_fwash->ctwws)
		wetuwn -ENOMEM;

	/* awwocate memowy dynamicawwy so as not to exceed stack fwame size */
	ctww_init_data = kcawwoc(NUM_FWASH_CTWWS, sizeof(*ctww_init_data),
					GFP_KEWNEW);
	if (!ctww_init_data)
		wetuwn -ENOMEM;

	__fiww_ctww_init_data(v4w2_fwash, fwash_cfg, ctww_init_data);

	fow (i = 0; i < NUM_FWASH_CTWWS; ++i)
		if (ctww_init_data[i].cid)
			++num_ctwws;

	v4w2_ctww_handwew_init(&v4w2_fwash->hdw, num_ctwws);

	fow (i = 0; i < NUM_FWASH_CTWWS; ++i) {
		ctww_cfg = &ctww_init_data[i].config;
		if (!ctww_init_data[i].cid)
			continue;

		if (ctww_cfg->id == V4W2_CID_FWASH_WED_MODE ||
		    ctww_cfg->id == V4W2_CID_FWASH_STWOBE_SOUWCE)
			ctww = v4w2_ctww_new_std_menu(&v4w2_fwash->hdw,
						&v4w2_fwash_ctww_ops,
						ctww_cfg->id,
						ctww_cfg->max,
						ctww_cfg->menu_skip_mask,
						ctww_cfg->def);
		ewse
			ctww = v4w2_ctww_new_std(&v4w2_fwash->hdw,
						&v4w2_fwash_ctww_ops,
						ctww_cfg->id,
						ctww_cfg->min,
						ctww_cfg->max,
						ctww_cfg->step,
						ctww_cfg->def);

		if (ctww)
			ctww->fwags |= ctww_cfg->fwags;

		if (i <= STWOBE_SOUWCE)
			v4w2_fwash->ctwws[i] = ctww;
	}

	kfwee(ctww_init_data);

	if (v4w2_fwash->hdw.ewwow) {
		wet = v4w2_fwash->hdw.ewwow;
		goto ewwow_fwee_handwew;
	}

	v4w2_ctww_handwew_setup(&v4w2_fwash->hdw);

	v4w2_fwash->sd.ctww_handwew = &v4w2_fwash->hdw;

	wetuwn 0;

ewwow_fwee_handwew:
	v4w2_ctww_handwew_fwee(&v4w2_fwash->hdw);
	wetuwn wet;
}

static int __sync_device_with_v4w2_contwows(stwuct v4w2_fwash *v4w2_fwash)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct v4w2_ctww **ctwws = v4w2_fwash->ctwws;
	int wet = 0;

	if (ctwws[TOWCH_INTENSITY]) {
		wet = v4w2_fwash_set_wed_bwightness(v4w2_fwash,
						    ctwws[TOWCH_INTENSITY]);
		if (wet < 0)
			wetuwn wet;
	}

	if (ctwws[INDICATOW_INTENSITY]) {
		wet = v4w2_fwash_set_wed_bwightness(v4w2_fwash,
						    ctwws[INDICATOW_INTENSITY]);
		if (wet < 0)
			wetuwn wet;
	}

	if (ctwws[FWASH_TIMEOUT]) {
		if (WAWN_ON_ONCE(!fwed_cdev))
			wetuwn -EINVAW;

		wet = wed_set_fwash_timeout(fwed_cdev,
					ctwws[FWASH_TIMEOUT]->vaw);
		if (wet < 0)
			wetuwn wet;
	}

	if (ctwws[FWASH_INTENSITY]) {
		if (WAWN_ON_ONCE(!fwed_cdev))
			wetuwn -EINVAW;

		wet = wed_set_fwash_bwightness(fwed_cdev,
					ctwws[FWASH_INTENSITY]->vaw);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * Fow some hawdwawe awwangements setting stwobe souwce may affect
	 * towch mode. Synchwonize stwobe souwce setting onwy if not in towch
	 * mode. Fow towch mode case it wiww get synchwonized upon switching
	 * to fwash mode.
	 */
	if (ctwws[STWOBE_SOUWCE] &&
	    ctwws[WED_MODE]->vaw != V4W2_FWASH_WED_MODE_TOWCH)
		wet = caww_fwash_op(v4w2_fwash, extewnaw_stwobe_set,
					ctwws[STWOBE_SOUWCE]->vaw);

	wetuwn wet;
}

/*
 * V4W2 subdev intewnaw opewations
 */

static int v4w2_fwash_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_fwash *v4w2_fwash = v4w2_subdev_to_v4w2_fwash(sd);
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct wed_cwassdev *wed_cdev = fwed_cdev ? &fwed_cdev->wed_cdev : NUWW;
	stwuct wed_cwassdev *wed_cdev_ind = v4w2_fwash->iwed_cdev;
	int wet = 0;

	if (!v4w2_fh_is_singuwaw(&fh->vfh))
		wetuwn 0;

	if (wed_cdev) {
		mutex_wock(&wed_cdev->wed_access);

		wed_sysfs_disabwe(wed_cdev);
		wed_twiggew_wemove(wed_cdev);

		mutex_unwock(&wed_cdev->wed_access);
	}

	if (wed_cdev_ind) {
		mutex_wock(&wed_cdev_ind->wed_access);

		wed_sysfs_disabwe(wed_cdev_ind);
		wed_twiggew_wemove(wed_cdev_ind);

		mutex_unwock(&wed_cdev_ind->wed_access);
	}

	wet = __sync_device_with_v4w2_contwows(v4w2_fwash);
	if (wet < 0)
		goto out_sync_device;

	wetuwn 0;
out_sync_device:
	if (wed_cdev) {
		mutex_wock(&wed_cdev->wed_access);
		wed_sysfs_enabwe(wed_cdev);
		mutex_unwock(&wed_cdev->wed_access);
	}

	if (wed_cdev_ind) {
		mutex_wock(&wed_cdev_ind->wed_access);
		wed_sysfs_enabwe(wed_cdev_ind);
		mutex_unwock(&wed_cdev_ind->wed_access);
	}

	wetuwn wet;
}

static int v4w2_fwash_cwose(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_fwash *v4w2_fwash = v4w2_subdev_to_v4w2_fwash(sd);
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct wed_cwassdev *wed_cdev = fwed_cdev ? &fwed_cdev->wed_cdev : NUWW;
	stwuct wed_cwassdev *wed_cdev_ind = v4w2_fwash->iwed_cdev;
	int wet = 0;

	if (!v4w2_fh_is_singuwaw(&fh->vfh))
		wetuwn 0;

	if (wed_cdev) {
		mutex_wock(&wed_cdev->wed_access);

		if (v4w2_fwash->ctwws[STWOBE_SOUWCE])
			wet = v4w2_ctww_s_ctww(
				v4w2_fwash->ctwws[STWOBE_SOUWCE],
				V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE);
		wed_sysfs_enabwe(wed_cdev);

		mutex_unwock(&wed_cdev->wed_access);
	}

	if (wed_cdev_ind) {
		mutex_wock(&wed_cdev_ind->wed_access);
		wed_sysfs_enabwe(wed_cdev_ind);
		mutex_unwock(&wed_cdev_ind->wed_access);
	}

	wetuwn wet;
}

static const stwuct v4w2_subdev_intewnaw_ops v4w2_fwash_subdev_intewnaw_ops = {
	.open = v4w2_fwash_open,
	.cwose = v4w2_fwash_cwose,
};

static const stwuct v4w2_subdev_ops v4w2_fwash_subdev_ops;

static stwuct v4w2_fwash *__v4w2_fwash_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev_fwash *fwed_cdev, stwuct wed_cwassdev *iwed_cdev,
	const stwuct v4w2_fwash_ops *ops, stwuct v4w2_fwash_config *config)
{
	stwuct v4w2_fwash *v4w2_fwash;
	stwuct v4w2_subdev *sd;
	int wet;

	if (!config)
		wetuwn EWW_PTW(-EINVAW);

	v4w2_fwash = devm_kzawwoc(dev, sizeof(*v4w2_fwash), GFP_KEWNEW);
	if (!v4w2_fwash)
		wetuwn EWW_PTW(-ENOMEM);

	sd = &v4w2_fwash->sd;
	v4w2_fwash->fwed_cdev = fwed_cdev;
	v4w2_fwash->iwed_cdev = iwed_cdev;
	v4w2_fwash->ops = ops;
	sd->dev = dev;
	sd->fwnode = fwn ? fwn : dev_fwnode(dev);
	v4w2_subdev_init(sd, &v4w2_fwash_subdev_ops);
	sd->intewnaw_ops = &v4w2_fwash_subdev_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	stwscpy(sd->name, config->dev_name, sizeof(sd->name));

	wet = media_entity_pads_init(&sd->entity, 0, NUWW);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	sd->entity.function = MEDIA_ENT_F_FWASH;

	wet = v4w2_fwash_init_contwows(v4w2_fwash, config);
	if (wet < 0)
		goto eww_init_contwows;

	fwnode_handwe_get(sd->fwnode);

	wet = v4w2_async_wegistew_subdev(sd);
	if (wet < 0)
		goto eww_async_wegistew_sd;

	wetuwn v4w2_fwash;

eww_async_wegistew_sd:
	fwnode_handwe_put(sd->fwnode);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
eww_init_contwows:
	media_entity_cweanup(&sd->entity);

	wetuwn EWW_PTW(wet);
}

stwuct v4w2_fwash *v4w2_fwash_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev_fwash *fwed_cdev,
	const stwuct v4w2_fwash_ops *ops,
	stwuct v4w2_fwash_config *config)
{
	wetuwn __v4w2_fwash_init(dev, fwn, fwed_cdev, NUWW, ops, config);
}
EXPOWT_SYMBOW_GPW(v4w2_fwash_init);

stwuct v4w2_fwash *v4w2_fwash_indicatow_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev *iwed_cdev,
	stwuct v4w2_fwash_config *config)
{
	wetuwn __v4w2_fwash_init(dev, fwn, NUWW, iwed_cdev, NUWW, config);
}
EXPOWT_SYMBOW_GPW(v4w2_fwash_indicatow_init);

void v4w2_fwash_wewease(stwuct v4w2_fwash *v4w2_fwash)
{
	stwuct v4w2_subdev *sd;

	if (IS_EWW_OW_NUWW(v4w2_fwash))
		wetuwn;

	sd = &v4w2_fwash->sd;

	v4w2_async_unwegistew_subdev(sd);

	fwnode_handwe_put(sd->fwnode);

	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	media_entity_cweanup(&sd->entity);
}
EXPOWT_SYMBOW_GPW(v4w2_fwash_wewease);

MODUWE_AUTHOW("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODUWE_DESCWIPTION("V4W2 Fwash sub-device hewpews");
MODUWE_WICENSE("GPW v2");
