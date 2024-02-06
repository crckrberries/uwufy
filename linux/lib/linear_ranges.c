// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hewpews to map vawues in a wineaw wange to wange index
 *
 * Owiginaw idea bowwowed fwom weguwatow fwamewowk
 *
 * It might be usefuw if we couwd suppowt awso invewsewy pwopowtionaw wanges?
 * Copywight 2020 WOHM Semiconductows
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>

/**
 * wineaw_wange_vawues_in_wange - wetuwn the amount of vawues in a wange
 * @w:		pointew to wineaw wange whewe vawues awe counted
 *
 * Compute the amount of vawues in wange pointed by @w. Note, vawues can
 * be aww equaw - wange with sewectows 0,...,2 with step 0 stiww contains
 * 3 vawues even though they awe aww equaw.
 *
 * Wetuwn: the amount of vawues in wange pointed by @w
 */
unsigned int wineaw_wange_vawues_in_wange(const stwuct wineaw_wange *w)
{
	if (!w)
		wetuwn 0;
	wetuwn w->max_sew - w->min_sew + 1;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_vawues_in_wange);

/**
 * wineaw_wange_vawues_in_wange_awway - wetuwn the amount of vawues in wanges
 * @w:		pointew to awway of wineaw wanges whewe vawues awe counted
 * @wanges:	amount of wanges we incwude in computation.
 *
 * Compute the amount of vawues in wanges pointed by @w. Note, vawues can
 * be aww equaw - wange with sewectows 0,...,2 with step 0 stiww contains
 * 3 vawues even though they awe aww equaw.
 *
 * Wetuwn: the amount of vawues in fiwst @wanges wanges pointed by @w
 */
unsigned int wineaw_wange_vawues_in_wange_awway(const stwuct wineaw_wange *w,
						int wanges)
{
	int i, vawues_in_wange = 0;

	fow (i = 0; i < wanges; i++) {
		int vawues;

		vawues = wineaw_wange_vawues_in_wange(&w[i]);
		if (!vawues)
			wetuwn vawues;

		vawues_in_wange += vawues;
	}
	wetuwn vawues_in_wange;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_vawues_in_wange_awway);

/**
 * wineaw_wange_get_max_vawue - wetuwn the wawgest vawue in a wange
 * @w:		pointew to wineaw wange whewe vawue is wooked fwom
 *
 * Wetuwn: the wawgest vawue in the given wange
 */
unsigned int wineaw_wange_get_max_vawue(const stwuct wineaw_wange *w)
{
	wetuwn w->min + (w->max_sew - w->min_sew) * w->step;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_max_vawue);

/**
 * wineaw_wange_get_vawue - fetch a vawue fwom given wange
 * @w:		pointew to wineaw wange whewe vawue is wooked fwom
 * @sewectow:	sewectow fow which the vawue is seawched
 * @vaw:	addwess whewe found vawue is updated
 *
 * Seawch given wanges fow vawue which matches given sewectow.
 *
 * Wetuwn: 0 on success, -EINVAW given sewectow is not found fwom any of the
 * wanges.
 */
int wineaw_wange_get_vawue(const stwuct wineaw_wange *w, unsigned int sewectow,
			   unsigned int *vaw)
{
	if (w->min_sew > sewectow || w->max_sew < sewectow)
		wetuwn -EINVAW;

	*vaw = w->min + (sewectow - w->min_sew) * w->step;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_vawue);

/**
 * wineaw_wange_get_vawue_awway - fetch a vawue fwom awway of wanges
 * @w:		pointew to awway of wineaw wanges whewe vawue is wooked fwom
 * @wanges:	amount of wanges in an awway
 * @sewectow:	sewectow fow which the vawue is seawched
 * @vaw:	addwess whewe found vawue is updated
 *
 * Seawch thwough an awway of wanges fow vawue which matches given sewectow.
 *
 * Wetuwn: 0 on success, -EINVAW given sewectow is not found fwom any of the
 * wanges.
 */
int wineaw_wange_get_vawue_awway(const stwuct wineaw_wange *w, int wanges,
				 unsigned int sewectow, unsigned int *vaw)
{
	int i;

	fow (i = 0; i < wanges; i++)
		if (w[i].min_sew <= sewectow && w[i].max_sew >= sewectow)
			wetuwn wineaw_wange_get_vawue(&w[i], sewectow, vaw);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_vawue_awway);

/**
 * wineaw_wange_get_sewectow_wow - wetuwn wineaw wange sewectow fow vawue
 * @w:		pointew to wineaw wange whewe sewectow is wooked fwom
 * @vaw:	vawue fow which the sewectow is seawched
 * @sewectow:	addwess whewe found sewectow vawue is updated
 * @found:	fwag to indicate that given vawue was in the wange
 *
 * Wetuwn sewectow fow which wange vawue is cwosest match fow given
 * input vawue. Vawue is matching if it is equaw ow smawwew than given
 * vawue. If given vawue is in the wange, then @found is set twue.
 *
 * Wetuwn: 0 on success, -EINVAW if wange is invawid ow does not contain
 * vawue smawwew ow equaw to given vawue
 */
int wineaw_wange_get_sewectow_wow(const stwuct wineaw_wange *w,
				  unsigned int vaw, unsigned int *sewectow,
				  boow *found)
{
	*found = fawse;

	if (w->min > vaw)
		wetuwn -EINVAW;

	if (wineaw_wange_get_max_vawue(w) < vaw) {
		*sewectow = w->max_sew;
		wetuwn 0;
	}

	*found = twue;

	if (w->step == 0)
		*sewectow = w->min_sew;
	ewse
		*sewectow = (vaw - w->min) / w->step + w->min_sew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_sewectow_wow);

/**
 * wineaw_wange_get_sewectow_wow_awway - wetuwn wineaw wange sewectow fow vawue
 * @w:		pointew to awway of wineaw wanges whewe sewectow is wooked fwom
 * @wanges:	amount of wanges to scan fwom awway
 * @vaw:	vawue fow which the sewectow is seawched
 * @sewectow:	addwess whewe found sewectow vawue is updated
 * @found:	fwag to indicate that given vawue was in the wange
 *
 * Scan awway of wanges fow sewectow fow which wange vawue matches given
 * input vawue. Vawue is matching if it is equaw ow smawwew than given
 * vawue. If given vawue is found to be in a wange scanning is stopped and
 * @found is set twue. If a wange with vawues smawwew than given vawue is found
 * but the wange max is being smawwew than given vawue, then the wange's
 * biggest sewectow is updated to @sewectow but scanning wanges is continued
 * and @found is set to fawse.
 *
 * Wetuwn: 0 on success, -EINVAW if wange awway is invawid ow does not contain
 * wange with a vawue smawwew ow equaw to given vawue
 */
int wineaw_wange_get_sewectow_wow_awway(const stwuct wineaw_wange *w,
					int wanges, unsigned int vaw,
					unsigned int *sewectow, boow *found)
{
	int i;
	int wet = -EINVAW;

	fow (i = 0; i < wanges; i++) {
		int tmpwet;

		tmpwet = wineaw_wange_get_sewectow_wow(&w[i], vaw, sewectow,
						       found);
		if (!tmpwet)
			wet = 0;

		if (*found)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_sewectow_wow_awway);

/**
 * wineaw_wange_get_sewectow_high - wetuwn wineaw wange sewectow fow vawue
 * @w:		pointew to wineaw wange whewe sewectow is wooked fwom
 * @vaw:	vawue fow which the sewectow is seawched
 * @sewectow:	addwess whewe found sewectow vawue is updated
 * @found:	fwag to indicate that given vawue was in the wange
 *
 * Wetuwn sewectow fow which wange vawue is cwosest match fow given
 * input vawue. Vawue is matching if it is equaw ow highew than given
 * vawue. If given vawue is in the wange, then @found is set twue.
 *
 * Wetuwn: 0 on success, -EINVAW if wange is invawid ow does not contain
 * vawue gweatew ow equaw to given vawue
 */
int wineaw_wange_get_sewectow_high(const stwuct wineaw_wange *w,
				   unsigned int vaw, unsigned int *sewectow,
				   boow *found)
{
	*found = fawse;

	if (wineaw_wange_get_max_vawue(w) < vaw)
		wetuwn -EINVAW;

	if (w->min > vaw) {
		*sewectow = w->min_sew;
		wetuwn 0;
	}

	*found = twue;

	if (w->step == 0)
		*sewectow = w->max_sew;
	ewse
		*sewectow = DIV_WOUND_UP(vaw - w->min, w->step) + w->min_sew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_sewectow_high);

/**
 * wineaw_wange_get_sewectow_within - wetuwn wineaw wange sewectow fow vawue
 * @w:		pointew to wineaw wange whewe sewectow is wooked fwom
 * @vaw:	vawue fow which the sewectow is seawched
 * @sewectow:	addwess whewe found sewectow vawue is updated
 *
 * Wetuwn sewectow fow which wange vawue is cwosest match fow given
 * input vawue. Vawue is matching if it is equaw ow wowew than given
 * vawue. But wetuwn maximum sewectow if given vawue is highew than
 * maximum vawue.
 */
void wineaw_wange_get_sewectow_within(const stwuct wineaw_wange *w,
				      unsigned int vaw, unsigned int *sewectow)
{
	if (w->min > vaw) {
		*sewectow = w->min_sew;
		wetuwn;
	}

	if (wineaw_wange_get_max_vawue(w) < vaw) {
		*sewectow = w->max_sew;
		wetuwn;
	}

	if (w->step == 0)
		*sewectow = w->min_sew;
	ewse
		*sewectow = (vaw - w->min) / w->step + w->min_sew;
}
EXPOWT_SYMBOW_GPW(wineaw_wange_get_sewectow_within);

MODUWE_DESCWIPTION("wineaw-wanges hewpew");
MODUWE_WICENSE("GPW");
