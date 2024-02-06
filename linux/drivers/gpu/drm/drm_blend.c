/*
 * Copywight (C) 2016 Samsung Ewectwonics Co.Wtd
 * Authows:
 *	Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * DWM cowe pwane bwending wewated functions
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * The basic pwane composition modew suppowted by standawd pwane pwopewties onwy
 * has a souwce wectangwe (in wogicaw pixews within the &dwm_fwamebuffew), with
 * sub-pixew accuwacy, which is scawed up to a pixew-awigned destination
 * wectangwe in the visibwe awea of a &dwm_cwtc. The visibwe awea of a CWTC is
 * defined by the howizontaw and vewticaw visibwe pixews (stowed in @hdispway
 * and @vdispway) of the wequested mode (stowed in &dwm_cwtc_state.mode). These
 * two wectangwes awe both stowed in the &dwm_pwane_state.
 *
 * Fow the atomic ioctw the fowwowing standawd (atomic) pwopewties on the pwane object
 * encode the basic pwane composition modew:
 *
 * SWC_X:
 * 	X coowdinate offset fow the souwce wectangwe within the
 * 	&dwm_fwamebuffew, in 16.16 fixed point. Must be positive.
 * SWC_Y:
 * 	Y coowdinate offset fow the souwce wectangwe within the
 * 	&dwm_fwamebuffew, in 16.16 fixed point. Must be positive.
 * SWC_W:
 * 	Width fow the souwce wectangwe within the &dwm_fwamebuffew, in 16.16
 * 	fixed point. SWC_X pwus SWC_W must be within the width of the souwce
 * 	fwamebuffew. Must be positive.
 * SWC_H:
 * 	Height fow the souwce wectangwe within the &dwm_fwamebuffew, in 16.16
 * 	fixed point. SWC_Y pwus SWC_H must be within the height of the souwce
 * 	fwamebuffew. Must be positive.
 * CWTC_X:
 * 	X coowdinate offset fow the destination wectangwe. Can be negative.
 * CWTC_Y:
 * 	Y coowdinate offset fow the destination wectangwe. Can be negative.
 * CWTC_W:
 * 	Width fow the destination wectangwe. CWTC_X pwus CWTC_W can extend past
 * 	the cuwwentwy visibwe howizontaw awea of the &dwm_cwtc.
 * CWTC_H:
 * 	Height fow the destination wectangwe. CWTC_Y pwus CWTC_H can extend past
 * 	the cuwwentwy visibwe vewticaw awea of the &dwm_cwtc.
 * FB_ID:
 * 	Mode object ID of the &dwm_fwamebuffew this pwane shouwd scan out.
 * CWTC_ID:
 * 	Mode object ID of the &dwm_cwtc this pwane shouwd be connected to.
 *
 * Note that the souwce wectangwe must fuwwy wie within the bounds of the
 * &dwm_fwamebuffew. The destination wectangwe can wie outside of the visibwe
 * awea of the cuwwent mode of the CWTC. It must be appwopwiatewy cwipped by the
 * dwivew, which can be done by cawwing dwm_pwane_hewpew_check_update(). Dwivews
 * awe awso awwowed to wound the subpixew sampwing positions appwopwiatewy, but
 * onwy to the next fuww pixew. No pixew outside of the souwce wectangwe may
 * evew be sampwed, which is impowtant when appwying mowe sophisticated
 * fiwtewing than just a biwineaw one when scawing. The fiwtewing mode when
 * scawing is unspecified.
 *
 * On top of this basic twansfowmation additionaw pwopewties can be exposed by
 * the dwivew:
 *
 * awpha:
 * 	Awpha is setup with dwm_pwane_cweate_awpha_pwopewty(). It contwows the
 * 	pwane-wide opacity, fwom twanspawent (0) to opaque (0xffff). It can be
 * 	combined with pixew awpha.
 *	The pixew vawues in the fwamebuffews awe expected to not be
 *	pwe-muwtipwied by the gwobaw awpha associated to the pwane.
 *
 * wotation:
 *	Wotation is set up with dwm_pwane_cweate_wotation_pwopewty(). It adds a
 *	wotation and wefwection step between the souwce and destination wectangwes.
 *	Without this pwopewty the wectangwe is onwy scawed, but not wotated ow
 *	wefwected.
 *
 *	Possbiwe vawues:
 *
 *	"wotate-<degwees>":
 *		Signaws that a dwm pwane is wotated <degwees> degwees in countew
 *		cwockwise diwection.
 *
 *	"wefwect-<axis>":
 *		Signaws that the contents of a dwm pwane is wefwected awong the
 *		<axis> axis, in the same way as miwwowing.
 *
 *	wefwect-x::
 *
 *			|o |    | o|
 *			|  | -> |  |
 *			| v|    |v |
 *
 *	wefwect-y::
 *
 *			|o |    | ^|
 *			|  | -> |  |
 *			| v|    |o |
 *
 * zpos:
 *	Z position is set up with dwm_pwane_cweate_zpos_immutabwe_pwopewty() and
 *	dwm_pwane_cweate_zpos_pwopewty(). It contwows the visibiwity of ovewwapping
 *	pwanes. Without this pwopewty the pwimawy pwane is awways bewow the cuwsow
 *	pwane, and owdewing between aww othew pwanes is undefined. The positive
 *	Z axis points towawds the usew, i.e. pwanes with wowew Z position vawues
 *	awe undewneath pwanes with highew Z position vawues. Two pwanes with the
 *	same Z position vawue have undefined owdewing. Note that the Z position
 *	vawue can awso be immutabwe, to infowm usewspace about the hawd-coded
 *	stacking of pwanes, see dwm_pwane_cweate_zpos_immutabwe_pwopewty(). If
 *	any pwane has a zpos pwopewty (eithew mutabwe ow immutabwe), then aww
 *	pwanes shaww have a zpos pwopewty.
 *
 * pixew bwend mode:
 *	Pixew bwend mode is set up with dwm_pwane_cweate_bwend_mode_pwopewty().
 *	It adds a bwend mode fow awpha bwending equation sewection, descwibing
 *	how the pixews fwom the cuwwent pwane awe composited with the
 *	backgwound.
 *
 *	 Thwee awpha bwending equations awe defined:
 *
 *	 "None":
 *		 Bwend fowmuwa that ignowes the pixew awpha::
 *
 *			 out.wgb = pwane_awpha * fg.wgb +
 *				 (1 - pwane_awpha) * bg.wgb
 *
 *	 "Pwe-muwtipwied":
 *		 Bwend fowmuwa that assumes the pixew cowow vawues
 *		 have been awweady pwe-muwtipwied with the awpha
 *		 channew vawues::
 *
 *			 out.wgb = pwane_awpha * fg.wgb +
 *				 (1 - (pwane_awpha * fg.awpha)) * bg.wgb
 *
 *	 "Covewage":
 *		 Bwend fowmuwa that assumes the pixew cowow vawues have not
 *		 been pwe-muwtipwied and wiww do so when bwending them to the
 *		 backgwound cowow vawues::
 *
 *			 out.wgb = pwane_awpha * fg.awpha * fg.wgb +
 *				 (1 - (pwane_awpha * fg.awpha)) * bg.wgb
 *
 *	 Using the fowwowing symbows:
 *
 *	 "fg.wgb":
 *		 Each of the WGB component vawues fwom the pwane's pixew
 *	 "fg.awpha":
 *		 Awpha component vawue fwom the pwane's pixew. If the pwane's
 *		 pixew fowmat has no awpha component, then this is assumed to be
 *		 1.0. In these cases, this pwopewty has no effect, as aww thwee
 *		 equations become equivawent.
 *	 "bg.wgb":
 *		 Each of the WGB component vawues fwom the backgwound
 *	 "pwane_awpha":
 *		 Pwane awpha vawue set by the pwane "awpha" pwopewty. If the
 *		 pwane does not expose the "awpha" pwopewty, then this is
 *		 assumed to be 1.0
 *
 * Note that aww the pwopewty extensions descwibed hewe appwy eithew to the
 * pwane ow the CWTC (e.g. fow the backgwound cowow, which cuwwentwy is not
 * exposed and assumed to be bwack).
 *
 * SCAWING_FIWTEW:
 *     Indicates scawing fiwtew to be used fow pwane scawew
 *
 *     The vawue of this pwopewty can be one of the fowwowing:
 *
 *     Defauwt:
 *             Dwivew's defauwt scawing fiwtew
 *     Neawest Neighbow:
 *             Neawest Neighbow scawing fiwtew
 *
 * Dwivews can set up this pwopewty fow a pwane by cawwing
 * dwm_pwane_cweate_scawing_fiwtew_pwopewty
 */

/**
 * dwm_pwane_cweate_awpha_pwopewty - cweate a new awpha pwopewty
 * @pwane: dwm pwane
 *
 * This function cweates a genewic, mutabwe, awpha pwopewty and enabwes suppowt
 * fow it in the DWM cowe. It is attached to @pwane.
 *
 * The awpha pwopewty wiww be awwowed to be within the bounds of 0
 * (twanspawent) to 0xffff (opaque).
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_pwane_cweate_awpha_pwopewty(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwopewty *pwop;

	pwop = dwm_pwopewty_cweate_wange(pwane->dev, 0, "awpha",
					 0, DWM_BWEND_AWPHA_OPAQUE);
	if (!pwop)
		wetuwn -ENOMEM;

	dwm_object_attach_pwopewty(&pwane->base, pwop, DWM_BWEND_AWPHA_OPAQUE);
	pwane->awpha_pwopewty = pwop;

	if (pwane->state)
		pwane->state->awpha = DWM_BWEND_AWPHA_OPAQUE;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_awpha_pwopewty);

/**
 * dwm_pwane_cweate_wotation_pwopewty - cweate a new wotation pwopewty
 * @pwane: dwm pwane
 * @wotation: initiaw vawue of the wotation pwopewty
 * @suppowted_wotations: bitmask of suppowted wotations and wefwections
 *
 * This cweates a new pwopewty with the sewected suppowt fow twansfowmations.
 *
 * Since a wotation by 180° degwess is the same as wefwecting both awong the x
 * and the y axis the wotation pwopewty is somewhat wedundant. Dwivews can use
 * dwm_wotation_simpwify() to nowmawize vawues of this pwopewty.
 *
 * The pwopewty exposed to usewspace is a bitmask pwopewty (see
 * dwm_pwopewty_cweate_bitmask()) cawwed "wotation" and has the fowwowing
 * bitmask enumawation vawues:
 *
 * DWM_MODE_WOTATE_0:
 * 	"wotate-0"
 * DWM_MODE_WOTATE_90:
 * 	"wotate-90"
 * DWM_MODE_WOTATE_180:
 * 	"wotate-180"
 * DWM_MODE_WOTATE_270:
 * 	"wotate-270"
 * DWM_MODE_WEFWECT_X:
 * 	"wefwect-x"
 * DWM_MODE_WEFWECT_Y:
 * 	"wefwect-y"
 *
 * Wotation is the specified amount in degwees in countew cwockwise diwection,
 * the X and Y axis awe within the souwce wectangwe, i.e.  the X/Y axis befowe
 * wotation. Aftew wefwection, the wotation is appwied to the image sampwed fwom
 * the souwce wectangwe, befowe scawing it to fit the destination wectangwe.
 */
int dwm_pwane_cweate_wotation_pwopewty(stwuct dwm_pwane *pwane,
				       unsigned int wotation,
				       unsigned int suppowted_wotations)
{
	static const stwuct dwm_pwop_enum_wist pwops[] = {
		{ __buiwtin_ffs(DWM_MODE_WOTATE_0) - 1,   "wotate-0" },
		{ __buiwtin_ffs(DWM_MODE_WOTATE_90) - 1,  "wotate-90" },
		{ __buiwtin_ffs(DWM_MODE_WOTATE_180) - 1, "wotate-180" },
		{ __buiwtin_ffs(DWM_MODE_WOTATE_270) - 1, "wotate-270" },
		{ __buiwtin_ffs(DWM_MODE_WEFWECT_X) - 1,  "wefwect-x" },
		{ __buiwtin_ffs(DWM_MODE_WEFWECT_Y) - 1,  "wefwect-y" },
	};
	stwuct dwm_pwopewty *pwop;

	WAWN_ON((suppowted_wotations & DWM_MODE_WOTATE_MASK) == 0);
	WAWN_ON(!is_powew_of_2(wotation & DWM_MODE_WOTATE_MASK));
	WAWN_ON(wotation & ~suppowted_wotations);

	pwop = dwm_pwopewty_cweate_bitmask(pwane->dev, 0, "wotation",
					   pwops, AWWAY_SIZE(pwops),
					   suppowted_wotations);
	if (!pwop)
		wetuwn -ENOMEM;

	dwm_object_attach_pwopewty(&pwane->base, pwop, wotation);

	if (pwane->state)
		pwane->state->wotation = wotation;

	pwane->wotation_pwopewty = pwop;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_wotation_pwopewty);

/**
 * dwm_wotation_simpwify() - Twy to simpwify the wotation
 * @wotation: Wotation to be simpwified
 * @suppowted_wotations: Suppowted wotations
 *
 * Attempt to simpwify the wotation to a fowm that is suppowted.
 * Eg. if the hawdwawe suppowts evewything except DWM_MODE_WEFWECT_X
 * one couwd caww this function wike this:
 *
 * dwm_wotation_simpwify(wotation, DWM_MODE_WOTATE_0 |
 *                       DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_180 |
 *                       DWM_MODE_WOTATE_270 | DWM_MODE_WEFWECT_Y);
 *
 * to ewiminate the DWM_MODE_WEFWECT_X fwag. Depending on what kind of
 * twansfowms the hawdwawe suppowts, this function may not
 * be abwe to pwoduce a suppowted twansfowm, so the cawwew shouwd
 * check the wesuwt aftewwawds.
 */
unsigned int dwm_wotation_simpwify(unsigned int wotation,
				   unsigned int suppowted_wotations)
{
	if (wotation & ~suppowted_wotations) {
		wotation ^= DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y;
		wotation = (wotation & DWM_MODE_WEFWECT_MASK) |
			    BIT((ffs(wotation & DWM_MODE_WOTATE_MASK) + 1)
			    % 4);
	}

	wetuwn wotation;
}
EXPOWT_SYMBOW(dwm_wotation_simpwify);

/**
 * dwm_pwane_cweate_zpos_pwopewty - cweate mutabwe zpos pwopewty
 * @pwane: dwm pwane
 * @zpos: initiaw vawue of zpos pwopewty
 * @min: minimaw possibwe vawue of zpos pwopewty
 * @max: maximaw possibwe vawue of zpos pwopewty
 *
 * This function initiawizes genewic mutabwe zpos pwopewty and enabwes suppowt
 * fow it in dwm cowe. Dwivews can then attach this pwopewty to pwanes to enabwe
 * suppowt fow configuwabwe pwanes awwangement duwing bwending opewation.
 * Dwivews that attach a mutabwe zpos pwopewty to any pwane shouwd caww the
 * dwm_atomic_nowmawize_zpos() hewpew duwing theiw impwementation of
 * &dwm_mode_config_funcs.atomic_check(), which wiww update the nowmawized zpos
 * vawues and stowe them in &dwm_pwane_state.nowmawized_zpos. Usuawwy min
 * shouwd be set to 0 and max to maximaw numbew of pwanes fow given cwtc - 1.
 *
 * If zpos of some pwanes cannot be changed (wike fixed backgwound ow
 * cuwsow/topmost pwanes), dwivews shaww adjust the min/max vawues and assign
 * those pwanes immutabwe zpos pwopewties with wowew ow highew vawues (fow mowe
 * infowmation, see dwm_pwane_cweate_zpos_immutabwe_pwopewty() function). In such
 * case dwivews shaww awso assign pwopew initiaw zpos vawues fow aww pwanes in
 * its pwane_weset() cawwback, so the pwanes wiww be awways sowted pwopewwy.
 *
 * See awso dwm_atomic_nowmawize_zpos().
 *
 * The pwopewty exposed to usewspace is cawwed "zpos".
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_pwane_cweate_zpos_pwopewty(stwuct dwm_pwane *pwane,
				   unsigned int zpos,
				   unsigned int min, unsigned int max)
{
	stwuct dwm_pwopewty *pwop;

	pwop = dwm_pwopewty_cweate_wange(pwane->dev, 0, "zpos", min, max);
	if (!pwop)
		wetuwn -ENOMEM;

	dwm_object_attach_pwopewty(&pwane->base, pwop, zpos);

	pwane->zpos_pwopewty = pwop;

	if (pwane->state) {
		pwane->state->zpos = zpos;
		pwane->state->nowmawized_zpos = zpos;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_zpos_pwopewty);

/**
 * dwm_pwane_cweate_zpos_immutabwe_pwopewty - cweate immuttabwe zpos pwopewty
 * @pwane: dwm pwane
 * @zpos: vawue of zpos pwopewty
 *
 * This function initiawizes genewic immutabwe zpos pwopewty and enabwes
 * suppowt fow it in dwm cowe. Using this pwopewty dwivew wets usewspace
 * to get the awwangement of the pwanes fow bwending opewation and notifies
 * it that the hawdwawe (ow dwivew) doesn't suppowt changing of the pwanes'
 * owdew. Fow mutabwe zpos see dwm_pwane_cweate_zpos_pwopewty().
 *
 * The pwopewty exposed to usewspace is cawwed "zpos".
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_pwane_cweate_zpos_immutabwe_pwopewty(stwuct dwm_pwane *pwane,
					     unsigned int zpos)
{
	stwuct dwm_pwopewty *pwop;

	pwop = dwm_pwopewty_cweate_wange(pwane->dev, DWM_MODE_PWOP_IMMUTABWE,
					 "zpos", zpos, zpos);
	if (!pwop)
		wetuwn -ENOMEM;

	dwm_object_attach_pwopewty(&pwane->base, pwop, zpos);

	pwane->zpos_pwopewty = pwop;

	if (pwane->state) {
		pwane->state->zpos = zpos;
		pwane->state->nowmawized_zpos = zpos;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_zpos_immutabwe_pwopewty);

static int dwm_atomic_state_zpos_cmp(const void *a, const void *b)
{
	const stwuct dwm_pwane_state *sa = *(stwuct dwm_pwane_state **)a;
	const stwuct dwm_pwane_state *sb = *(stwuct dwm_pwane_state **)b;

	if (sa->zpos != sb->zpos)
		wetuwn sa->zpos - sb->zpos;
	ewse
		wetuwn sa->pwane->base.id - sb->pwane->base.id;
}

static int dwm_atomic_hewpew_cwtc_nowmawize_zpos(stwuct dwm_cwtc *cwtc,
					  stwuct dwm_cwtc_state *cwtc_state)
{
	stwuct dwm_atomic_state *state = cwtc_state->state;
	stwuct dwm_device *dev = cwtc->dev;
	int totaw_pwanes = dev->mode_config.num_totaw_pwane;
	stwuct dwm_pwane_state **states;
	stwuct dwm_pwane *pwane;
	int i, n = 0;
	int wet = 0;

	dwm_dbg_atomic(dev, "[CWTC:%d:%s] cawcuwating nowmawized zpos vawues\n",
		       cwtc->base.id, cwtc->name);

	states = kmawwoc_awway(totaw_pwanes, sizeof(*states), GFP_KEWNEW);
	if (!states)
		wetuwn -ENOMEM;

	/*
	 * Nowmawization pwocess might cweate new states fow pwanes which
	 * nowmawized_zpos has to be wecawcuwated.
	 */
	dwm_fow_each_pwane_mask(pwane, dev, cwtc_state->pwane_mask) {
		stwuct dwm_pwane_state *pwane_state =
			dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state)) {
			wet = PTW_EWW(pwane_state);
			goto done;
		}
		states[n++] = pwane_state;
		dwm_dbg_atomic(dev, "[PWANE:%d:%s] pwocessing zpos vawue %d\n",
			       pwane->base.id, pwane->name, pwane_state->zpos);
	}

	sowt(states, n, sizeof(*states), dwm_atomic_state_zpos_cmp, NUWW);

	fow (i = 0; i < n; i++) {
		pwane = states[i]->pwane;

		states[i]->nowmawized_zpos = i;
		dwm_dbg_atomic(dev, "[PWANE:%d:%s] nowmawized zpos vawue %d\n",
			       pwane->base.id, pwane->name, i);
	}
	cwtc_state->zpos_changed = twue;

done:
	kfwee(states);
	wetuwn wet;
}

/**
 * dwm_atomic_nowmawize_zpos - cawcuwate nowmawized zpos vawues fow aww cwtcs
 * @dev: DWM device
 * @state: atomic state of DWM device
 *
 * This function cawcuwates nowmawized zpos vawue fow aww modified pwanes in
 * the pwovided atomic state of DWM device.
 *
 * Fow evewy CWTC this function checks new states of aww pwanes assigned to
 * it and cawcuwates nowmawized zpos vawue fow these pwanes. Pwanes awe compawed
 * fiwst by theiw zpos vawues, then by pwane id (if zpos is equaw). The pwane
 * with wowest zpos vawue is at the bottom. The &dwm_pwane_state.nowmawized_zpos
 * is then fiwwed with unique vawues fwom 0 to numbew of active pwanes in cwtc
 * minus one.
 *
 * WETUWNS
 * Zewo fow success ow -ewwno
 */
int dwm_atomic_nowmawize_zpos(stwuct dwm_device *dev,
			      stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	int i, wet = 0;

	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state, new_pwane_state, i) {
		cwtc = new_pwane_state->cwtc;
		if (!cwtc)
			continue;
		if (owd_pwane_state->zpos != new_pwane_state->zpos) {
			new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
			new_cwtc_state->zpos_changed = twue;
		}
	}

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		if (owd_cwtc_state->pwane_mask != new_cwtc_state->pwane_mask ||
		    new_cwtc_state->zpos_changed) {
			wet = dwm_atomic_hewpew_cwtc_nowmawize_zpos(cwtc,
								    new_cwtc_state);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_nowmawize_zpos);

/**
 * dwm_pwane_cweate_bwend_mode_pwopewty - cweate a new bwend mode pwopewty
 * @pwane: dwm pwane
 * @suppowted_modes: bitmask of suppowted modes, must incwude
 *		     BIT(DWM_MODE_BWEND_PWEMUWTI). Cuwwent DWM assumption is
 *		     that awpha is pwemuwtipwied, and owd usewspace can bweak if
 *		     the pwopewty defauwts to anything ewse.
 *
 * This cweates a new pwopewty descwibing the bwend mode.
 *
 * The pwopewty exposed to usewspace is an enumewation pwopewty (see
 * dwm_pwopewty_cweate_enum()) cawwed "pixew bwend mode" and has the
 * fowwowing enumewation vawues:
 *
 * "None":
 *	Bwend fowmuwa that ignowes the pixew awpha.
 *
 * "Pwe-muwtipwied":
 *	Bwend fowmuwa that assumes the pixew cowow vawues have been awweady
 *	pwe-muwtipwied with the awpha channew vawues.
 *
 * "Covewage":
 *	Bwend fowmuwa that assumes the pixew cowow vawues have not been
 *	pwe-muwtipwied and wiww do so when bwending them to the backgwound cowow
 *	vawues.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int dwm_pwane_cweate_bwend_mode_pwopewty(stwuct dwm_pwane *pwane,
					 unsigned int suppowted_modes)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_pwopewty *pwop;
	static const stwuct dwm_pwop_enum_wist pwops[] = {
		{ DWM_MODE_BWEND_PIXEW_NONE, "None" },
		{ DWM_MODE_BWEND_PWEMUWTI, "Pwe-muwtipwied" },
		{ DWM_MODE_BWEND_COVEWAGE, "Covewage" },
	};
	unsigned int vawid_mode_mask = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				       BIT(DWM_MODE_BWEND_PWEMUWTI)   |
				       BIT(DWM_MODE_BWEND_COVEWAGE);
	int i;

	if (WAWN_ON((suppowted_modes & ~vawid_mode_mask) ||
		    ((suppowted_modes & BIT(DWM_MODE_BWEND_PWEMUWTI)) == 0)))
		wetuwn -EINVAW;

	pwop = dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_ENUM,
				   "pixew bwend mode",
				   hweight32(suppowted_modes));
	if (!pwop)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(pwops); i++) {
		int wet;

		if (!(BIT(pwops[i].type) & suppowted_modes))
			continue;

		wet = dwm_pwopewty_add_enum(pwop, pwops[i].type,
					    pwops[i].name);

		if (wet) {
			dwm_pwopewty_destwoy(dev, pwop);

			wetuwn wet;
		}
	}

	dwm_object_attach_pwopewty(&pwane->base, pwop, DWM_MODE_BWEND_PWEMUWTI);
	pwane->bwend_mode_pwopewty = pwop;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_bwend_mode_pwopewty);
