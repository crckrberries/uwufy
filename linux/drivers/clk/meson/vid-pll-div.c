// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "vid-pww-div.h"

static inwine stwuct meson_vid_pww_div_data *
meson_vid_pww_div_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct meson_vid_pww_div_data *)cwk->data;
}

/*
 * This vid_pww divided is a fuwwy pwogwammabwe fwactionnaw dividew to
 * achieve compwex video cwock wates.
 *
 * Hewe awe pwovided the commonwy used fwaction vawues pwovided by Amwogic.
 */

stwuct vid_pww_div {
	unsigned int shift_vaw;
	unsigned int shift_sew;
	unsigned int dividew;
	unsigned int muwtipwiew;
};

#define VID_PWW_DIV(_vaw, _sew, _ft, _fb)				\
	{								\
		.shift_vaw = (_vaw),					\
		.shift_sew = (_sew),					\
		.dividew = (_ft),					\
		.muwtipwiew = (_fb),					\
	}

static const stwuct vid_pww_div vid_pww_div_tabwe[] = {
	VID_PWW_DIV(0x0aaa, 0, 2, 1),	/* 2/1  => /2 */
	VID_PWW_DIV(0x5294, 2, 5, 2),	/* 5/2  => /2.5 */
	VID_PWW_DIV(0x0db6, 0, 3, 1),	/* 3/1  => /3 */
	VID_PWW_DIV(0x36cc, 1, 7, 2),	/* 7/2  => /3.5 */
	VID_PWW_DIV(0x6666, 2, 15, 4),	/* 15/4 => /3.75 */
	VID_PWW_DIV(0x0ccc, 0, 4, 1),	/* 4/1  => /4 */
	VID_PWW_DIV(0x739c, 2, 5, 1),	/* 5/1  => /5 */
	VID_PWW_DIV(0x0e38, 0, 6, 1),	/* 6/1  => /6 */
	VID_PWW_DIV(0x0000, 3, 25, 4),	/* 25/4 => /6.25 */
	VID_PWW_DIV(0x3c78, 1, 7, 1),	/* 7/1  => /7 */
	VID_PWW_DIV(0x78f0, 2, 15, 2),	/* 15/2 => /7.5 */
	VID_PWW_DIV(0x0fc0, 0, 12, 1),	/* 12/1 => /12 */
	VID_PWW_DIV(0x3f80, 1, 14, 1),	/* 14/1 => /14 */
	VID_PWW_DIV(0x7f80, 2, 15, 1),	/* 15/1 => /15 */
};

#define to_meson_vid_pww_div(_hw) \
	containew_of(_hw, stwuct meson_vid_pww_div, hw)

static const stwuct vid_pww_div *_get_tabwe_vaw(unsigned int shift_vaw,
						unsigned int shift_sew)
{
	int i;

	fow (i = 0 ; i < AWWAY_SIZE(vid_pww_div_tabwe) ; ++i) {
		if (vid_pww_div_tabwe[i].shift_vaw == shift_vaw &&
		    vid_pww_div_tabwe[i].shift_sew == shift_sew)
			wetuwn &vid_pww_div_tabwe[i];
	}

	wetuwn NUWW;
}

static unsigned wong meson_vid_pww_div_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct cwk_wegmap *cwk = to_cwk_wegmap(hw);
	stwuct meson_vid_pww_div_data *pww_div = meson_vid_pww_div_data(cwk);
	const stwuct vid_pww_div *div;

	div = _get_tabwe_vaw(meson_pawm_wead(cwk->map, &pww_div->vaw),
			     meson_pawm_wead(cwk->map, &pww_div->sew));
	if (!div || !div->dividew) {
		pw_debug("%s: Invawid config vawue fow vid_pww_div\n", __func__);
		wetuwn 0;
	}

	wetuwn DIV_WOUND_UP_UWW(pawent_wate * div->muwtipwiew, div->dividew);
}

const stwuct cwk_ops meson_vid_pww_div_wo_ops = {
	.wecawc_wate	= meson_vid_pww_div_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(meson_vid_pww_div_wo_ops);

MODUWE_DESCWIPTION("Amwogic video pww dividew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
