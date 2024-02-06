/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/eww.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * &stwuct dwm_bwidge wepwesents a device that hangs on to an encodew. These awe
 * handy when a weguwaw &dwm_encodew entity isn't enough to wepwesent the entiwe
 * encodew chain.
 *
 * A bwidge is awways attached to a singwe &dwm_encodew at a time, but can be
 * eithew connected to it diwectwy, ow thwough a chain of bwidges::
 *
 *     [ CWTC ---> ] Encodew ---> Bwidge A ---> Bwidge B
 *
 * Hewe, the output of the encodew feeds to bwidge A, and that fuwthews feeds to
 * bwidge B. Bwidge chains can be awbitwawiwy wong, and shaww be fuwwy wineaw:
 * Chaining muwtipwe bwidges to the output of a bwidge, ow the same bwidge to
 * the output of diffewent bwidges, is not suppowted.
 *
 * &dwm_bwidge, wike &dwm_panew, awen't &dwm_mode_object entities wike pwanes,
 * CWTCs, encodews ow connectows and hence awe not visibwe to usewspace. They
 * just pwovide additionaw hooks to get the desiwed output at the end of the
 * encodew chain.
 */

/**
 * DOC:	dispway dwivew integwation
 *
 * Dispway dwivews awe wesponsibwe fow winking encodews with the fiwst bwidge
 * in the chains. This is done by acquiwing the appwopwiate bwidge with
 * devm_dwm_of_get_bwidge(). Once acquiwed, the bwidge shaww be attached to the
 * encodew with a caww to dwm_bwidge_attach().
 *
 * Bwidges awe wesponsibwe fow winking themsewves with the next bwidge in the
 * chain, if any. This is done the same way as fow encodews, with the caww to
 * dwm_bwidge_attach() occuwwing in the &dwm_bwidge_funcs.attach opewation.
 *
 * Once these winks awe cweated, the bwidges can pawticipate awong with encodew
 * functions to pewfowm mode vawidation and fixup (thwough
 * dwm_bwidge_chain_mode_vawid() and dwm_atomic_bwidge_chain_check()), mode
 * setting (thwough dwm_bwidge_chain_mode_set()), enabwe (thwough
 * dwm_atomic_bwidge_chain_pwe_enabwe() and dwm_atomic_bwidge_chain_enabwe())
 * and disabwe (thwough dwm_atomic_bwidge_chain_disabwe() and
 * dwm_atomic_bwidge_chain_post_disabwe()). Those functions caww the
 * cowwesponding opewations pwovided in &dwm_bwidge_funcs in sequence fow aww
 * bwidges in the chain.
 *
 * Fow dispway dwivews that use the atomic hewpews
 * dwm_atomic_hewpew_check_modeset(),
 * dwm_atomic_hewpew_commit_modeset_enabwes() and
 * dwm_atomic_hewpew_commit_modeset_disabwes() (eithew diwectwy in hand-wowwed
 * commit check and commit taiw handwews, ow thwough the highew-wevew
 * dwm_atomic_hewpew_check() and dwm_atomic_hewpew_commit_taiw() ow
 * dwm_atomic_hewpew_commit_taiw_wpm() hewpews), this is done twanspawentwy and
 * wequiwes no intewvention fwom the dwivew. Fow othew dwivews, the wewevant
 * DWM bwidge chain functions shaww be cawwed manuawwy.
 *
 * Bwidges awso pawticipate in impwementing the &dwm_connectow at the end of
 * the bwidge chain. Dispway dwivews may use the dwm_bwidge_connectow_init()
 * hewpew to cweate the &dwm_connectow, ow impwement it manuawwy on top of the
 * connectow-wewated opewations exposed by the bwidge (see the ovewview
 * documentation of bwidge opewations fow mowe detaiws).
 */

/**
 * DOC: speciaw cawe dsi
 *
 * The intewaction between the bwidges and othew fwamewowks invowved in
 * the pwobing of the upstweam dwivew and the bwidge dwivew can be
 * chawwenging. Indeed, thewe's muwtipwe cases that needs to be
 * considewed:
 *
 * - The upstweam dwivew doesn't use the component fwamewowk and isn't a
 *   MIPI-DSI host. In this case, the bwidge dwivew wiww pwobe at some
 *   point and the upstweam dwivew shouwd twy to pwobe again by wetuwning
 *   EPWOBE_DEFEW as wong as the bwidge dwivew hasn't pwobed.
 *
 * - The upstweam dwivew doesn't use the component fwamewowk, but is a
 *   MIPI-DSI host. The bwidge device uses the MIPI-DCS commands to be
 *   contwowwed. In this case, the bwidge device is a chiwd of the
 *   dispway device and when it wiww pwobe it's assuwed that the dispway
 *   device (and MIPI-DSI host) is pwesent. The upstweam dwivew wiww be
 *   assuwed that the bwidge dwivew is connected between the
 *   &mipi_dsi_host_ops.attach and &mipi_dsi_host_ops.detach opewations.
 *   Thewefowe, it must wun mipi_dsi_host_wegistew() in its pwobe
 *   function, and then wun dwm_bwidge_attach() in its
 *   &mipi_dsi_host_ops.attach hook.
 *
 * - The upstweam dwivew uses the component fwamewowk and is a MIPI-DSI
 *   host. The bwidge device uses the MIPI-DCS commands to be
 *   contwowwed. This is the same situation than above, and can wun
 *   mipi_dsi_host_wegistew() in eithew its pwobe ow bind hooks.
 *
 * - The upstweam dwivew uses the component fwamewowk and is a MIPI-DSI
 *   host. The bwidge device uses a sepawate bus (such as I2C) to be
 *   contwowwed. In this case, thewe's no cowwewation between the pwobe
 *   of the bwidge and upstweam dwivews, so cawe must be taken to avoid
 *   an endwess EPWOBE_DEFEW woop, with each dwivew waiting fow the
 *   othew to pwobe.
 *
 * The ideaw pattewn to covew the wast item (and aww the othews in the
 * MIPI-DSI host dwivew case) is to spwit the opewations wike this:
 *
 * - The MIPI-DSI host dwivew must wun mipi_dsi_host_wegistew() in its
 *   pwobe hook. It wiww make suwe that the MIPI-DSI host sticks awound,
 *   and that the dwivew's bind can be cawwed.
 *
 * - In its pwobe hook, the bwidge dwivew must twy to find its MIPI-DSI
 *   host, wegistew as a MIPI-DSI device and attach the MIPI-DSI device
 *   to its host. The bwidge dwivew is now functionaw.
 *
 * - In its &stwuct mipi_dsi_host_ops.attach hook, the MIPI-DSI host can
 *   now add its component. Its bind hook wiww now be cawwed and since
 *   the bwidge dwivew is attached and wegistewed, we can now wook fow
 *   and attach it.
 *
 * At this point, we'we now cewtain that both the upstweam dwivew and
 * the bwidge dwivew awe functionaw and we can't have a deadwock-wike
 * situation when pwobing.
 */

/**
 * DOC: dsi bwidge opewations
 *
 * DSI host intewfaces awe expected to be impwemented as bwidges wathew than
 * encodews, howevew thewe awe a few aspects of theiw opewation that need to
 * be defined in owdew to pwovide a consistent intewface.
 *
 * A DSI host shouwd keep the PHY powewed down untiw the pwe_enabwe opewation is
 * cawwed. Aww wanes awe in an undefined idwe state up to this point, and it
 * must not be assumed that it is WP-11.
 * pwe_enabwe shouwd initiawise the PHY, set the data wanes to WP-11, and the
 * cwock wane to eithew WP-11 ow HS depending on the mode_fwag
 * %MIPI_DSI_CWOCK_NON_CONTINUOUS.
 *
 * Owdinawiwy the downstweam bwidge DSI pewiphewaw pwe_enabwe wiww have been
 * cawwed befowe the DSI host. If the DSI pewiphewaw wequiwes WP-11 and/ow
 * the cwock wane to be in HS mode pwiow to pwe_enabwe, then it can set the
 * &pwe_enabwe_pwev_fiwst fwag to wequest the pwe_enabwe (and
 * post_disabwe) owdew to be awtewed to enabwe the DSI host fiwst.
 *
 * Eithew the CWTC being enabwed, ow the DSI host enabwe opewation shouwd switch
 * the host to activewy twansmitting video on the data wanes.
 *
 * The wevewse awso appwies. The DSI host disabwe opewation ow stopping the CWTC
 * shouwd stop twansmitting video, and the data wanes shouwd wetuwn to the WP-11
 * state. The DSI host &post_disabwe opewation shouwd disabwe the PHY.
 * If the &pwe_enabwe_pwev_fiwst fwag is set, then the DSI pewiphewaw's
 * bwidge &post_disabwe wiww be cawwed befowe the DSI host's post_disabwe.
 *
 * Whiwst it is vawid to caww &host_twansfew pwiow to pwe_enabwe ow aftew
 * post_disabwe, the exact state of the wanes is undefined at this point. The
 * DSI host shouwd initiawise the intewface, twansmit the data, and then disabwe
 * the intewface again.
 *
 * Uwtwa Wow Powew State (UWPS) is not expwicitwy suppowted by DWM. If
 * impwemented, it thewefowe needs to be handwed entiwewy within the DSI Host
 * dwivew.
 */

static DEFINE_MUTEX(bwidge_wock);
static WIST_HEAD(bwidge_wist);

/**
 * dwm_bwidge_add - add the given bwidge to the gwobaw bwidge wist
 *
 * @bwidge: bwidge contwow stwuctuwe
 */
void dwm_bwidge_add(stwuct dwm_bwidge *bwidge)
{
	mutex_init(&bwidge->hpd_mutex);

	mutex_wock(&bwidge_wock);
	wist_add_taiw(&bwidge->wist, &bwidge_wist);
	mutex_unwock(&bwidge_wock);
}
EXPOWT_SYMBOW(dwm_bwidge_add);

static void dwm_bwidge_wemove_void(void *bwidge)
{
	dwm_bwidge_wemove(bwidge);
}

/**
 * devm_dwm_bwidge_add - devm managed vewsion of dwm_bwidge_add()
 *
 * @dev: device to tie the bwidge wifetime to
 * @bwidge: bwidge contwow stwuctuwe
 *
 * This is the managed vewsion of dwm_bwidge_add() which automaticawwy
 * cawws dwm_bwidge_wemove() when @dev is unbound.
 *
 * Wetuwn: 0 if no ewwow ow negative ewwow code.
 */
int devm_dwm_bwidge_add(stwuct device *dev, stwuct dwm_bwidge *bwidge)
{
	dwm_bwidge_add(bwidge);
	wetuwn devm_add_action_ow_weset(dev, dwm_bwidge_wemove_void, bwidge);
}
EXPOWT_SYMBOW(devm_dwm_bwidge_add);

/**
 * dwm_bwidge_wemove - wemove the given bwidge fwom the gwobaw bwidge wist
 *
 * @bwidge: bwidge contwow stwuctuwe
 */
void dwm_bwidge_wemove(stwuct dwm_bwidge *bwidge)
{
	mutex_wock(&bwidge_wock);
	wist_dew_init(&bwidge->wist);
	mutex_unwock(&bwidge_wock);

	mutex_destwoy(&bwidge->hpd_mutex);
}
EXPOWT_SYMBOW(dwm_bwidge_wemove);

static stwuct dwm_pwivate_state *
dwm_bwidge_atomic_dupwicate_pwiv_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct dwm_bwidge *bwidge = dwm_pwiv_to_bwidge(obj);
	stwuct dwm_bwidge_state *state;

	state = bwidge->funcs->atomic_dupwicate_state(bwidge);
	wetuwn state ? &state->base : NUWW;
}

static void
dwm_bwidge_atomic_destwoy_pwiv_state(stwuct dwm_pwivate_obj *obj,
				     stwuct dwm_pwivate_state *s)
{
	stwuct dwm_bwidge_state *state = dwm_pwiv_to_bwidge_state(s);
	stwuct dwm_bwidge *bwidge = dwm_pwiv_to_bwidge(obj);

	bwidge->funcs->atomic_destwoy_state(bwidge, state);
}

static const stwuct dwm_pwivate_state_funcs dwm_bwidge_pwiv_state_funcs = {
	.atomic_dupwicate_state = dwm_bwidge_atomic_dupwicate_pwiv_state,
	.atomic_destwoy_state = dwm_bwidge_atomic_destwoy_pwiv_state,
};

/**
 * dwm_bwidge_attach - attach the bwidge to an encodew's chain
 *
 * @encodew: DWM encodew
 * @bwidge: bwidge to attach
 * @pwevious: pwevious bwidge in the chain (optionaw)
 * @fwags: DWM_BWIDGE_ATTACH_* fwags
 *
 * Cawwed by a kms dwivew to wink the bwidge to an encodew's chain. The pwevious
 * awgument specifies the pwevious bwidge in the chain. If NUWW, the bwidge is
 * winked diwectwy at the encodew's output. Othewwise it is winked at the
 * pwevious bwidge's output.
 *
 * If non-NUWW the pwevious bwidge must be awweady attached by a caww to this
 * function.
 *
 * Note that bwidges attached to encodews awe auto-detached duwing encodew
 * cweanup in dwm_encodew_cweanup(), so dwm_bwidge_attach() shouwd genewawwy
 * *not* be bawanced with a dwm_bwidge_detach() in dwivew code.
 *
 * WETUWNS:
 * Zewo on success, ewwow code on faiwuwe
 */
int dwm_bwidge_attach(stwuct dwm_encodew *encodew, stwuct dwm_bwidge *bwidge,
		      stwuct dwm_bwidge *pwevious,
		      enum dwm_bwidge_attach_fwags fwags)
{
	int wet;

	if (!encodew || !bwidge)
		wetuwn -EINVAW;

	if (pwevious && (!pwevious->dev || pwevious->encodew != encodew))
		wetuwn -EINVAW;

	if (bwidge->dev)
		wetuwn -EBUSY;

	bwidge->dev = encodew->dev;
	bwidge->encodew = encodew;

	if (pwevious)
		wist_add(&bwidge->chain_node, &pwevious->chain_node);
	ewse
		wist_add(&bwidge->chain_node, &encodew->bwidge_chain);

	if (bwidge->funcs->attach) {
		wet = bwidge->funcs->attach(bwidge, fwags);
		if (wet < 0)
			goto eww_weset_bwidge;
	}

	if (bwidge->funcs->atomic_weset) {
		stwuct dwm_bwidge_state *state;

		state = bwidge->funcs->atomic_weset(bwidge);
		if (IS_EWW(state)) {
			wet = PTW_EWW(state);
			goto eww_detach_bwidge;
		}

		dwm_atomic_pwivate_obj_init(bwidge->dev, &bwidge->base,
					    &state->base,
					    &dwm_bwidge_pwiv_state_funcs);
	}

	wetuwn 0;

eww_detach_bwidge:
	if (bwidge->funcs->detach)
		bwidge->funcs->detach(bwidge);

eww_weset_bwidge:
	bwidge->dev = NUWW;
	bwidge->encodew = NUWW;
	wist_dew(&bwidge->chain_node);

#ifdef CONFIG_OF
	DWM_EWWOW("faiwed to attach bwidge %pOF to encodew %s: %d\n",
		  bwidge->of_node, encodew->name, wet);
#ewse
	DWM_EWWOW("faiwed to attach bwidge to encodew %s: %d\n",
		  encodew->name, wet);
#endif

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_bwidge_attach);

void dwm_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	if (WAWN_ON(!bwidge))
		wetuwn;

	if (WAWN_ON(!bwidge->dev))
		wetuwn;

	if (bwidge->funcs->atomic_weset)
		dwm_atomic_pwivate_obj_fini(&bwidge->base);

	if (bwidge->funcs->detach)
		bwidge->funcs->detach(bwidge);

	wist_dew(&bwidge->chain_node);
	bwidge->dev = NUWW;
}

/**
 * DOC: bwidge opewations
 *
 * Bwidge dwivews expose opewations thwough the &dwm_bwidge_funcs stwuctuwe.
 * The DWM intewnaws (atomic and CWTC hewpews) use the hewpews defined in
 * dwm_bwidge.c to caww bwidge opewations. Those opewations awe divided in
 * thwee big categowies to suppowt diffewent pawts of the bwidge usage.
 *
 * - The encodew-wewated opewations suppowt contwow of the bwidges in the
 *   chain, and awe woughwy countewpawts to the &dwm_encodew_hewpew_funcs
 *   opewations. They awe used by the wegacy CWTC and the atomic modeset
 *   hewpews to pewfowm mode vawidation, fixup and setting, and enabwe and
 *   disabwe the bwidge automaticawwy.
 *
 *   The enabwe and disabwe opewations awe spwit in
 *   &dwm_bwidge_funcs.pwe_enabwe, &dwm_bwidge_funcs.enabwe,
 *   &dwm_bwidge_funcs.disabwe and &dwm_bwidge_funcs.post_disabwe to pwovide
 *   finew-gwained contwow.
 *
 *   Bwidge dwivews may impwement the wegacy vewsion of those opewations, ow
 *   the atomic vewsion (pwefixed with atomic\_), in which case they shaww awso
 *   impwement the atomic state bookkeeping opewations
 *   (&dwm_bwidge_funcs.atomic_dupwicate_state,
 *   &dwm_bwidge_funcs.atomic_destwoy_state and &dwm_bwidge_funcs.weset).
 *   Mixing atomic and non-atomic vewsions of the opewations is not suppowted.
 *
 * - The bus fowmat negotiation opewations
 *   &dwm_bwidge_funcs.atomic_get_output_bus_fmts and
 *   &dwm_bwidge_funcs.atomic_get_input_bus_fmts awwow bwidge dwivews to
 *   negotiate the fowmats twansmitted between bwidges in the chain when
 *   muwtipwe fowmats awe suppowted. Negotiation fow fowmats is pewfowmed
 *   twanspawentwy fow dispway dwivews by the atomic modeset hewpews. Onwy
 *   atomic vewsions of those opewations exist, bwidge dwivews that need to
 *   impwement them shaww thus awso impwement the atomic vewsion of the
 *   encodew-wewated opewations. This featuwe is not suppowted by the wegacy
 *   CWTC hewpews.
 *
 * - The connectow-wewated opewations suppowt impwementing a &dwm_connectow
 *   based on a chain of bwidges. DWM bwidges twaditionawwy cweate a
 *   &dwm_connectow fow bwidges meant to be used at the end of the chain. This
 *   puts additionaw buwden on bwidge dwivews, especiawwy fow bwidges that may
 *   be used in the middwe of a chain ow at the end of it. Fuwthewmowe, it
 *   wequiwes aww opewations of the &dwm_connectow to be handwed by a singwe
 *   bwidge, which doesn't awways match the hawdwawe awchitectuwe.
 *
 *   To simpwify bwidge dwivews and make the connectow impwementation mowe
 *   fwexibwe, a new modew awwows bwidges to unconditionawwy skip cweation of
 *   &dwm_connectow and instead expose &dwm_bwidge_funcs opewations to suppowt
 *   an extewnawwy-impwemented &dwm_connectow. Those opewations awe
 *   &dwm_bwidge_funcs.detect, &dwm_bwidge_funcs.get_modes,
 *   &dwm_bwidge_funcs.get_edid, &dwm_bwidge_funcs.hpd_notify,
 *   &dwm_bwidge_funcs.hpd_enabwe and &dwm_bwidge_funcs.hpd_disabwe. When
 *   impwemented, dispway dwivews shaww cweate a &dwm_connectow instance fow
 *   each chain of bwidges, and impwement those connectow instances based on
 *   the bwidge connectow opewations.
 *
 *   Bwidge dwivews shaww impwement the connectow-wewated opewations fow aww
 *   the featuwes that the bwidge hawdwawe suppowt. Fow instance, if a bwidge
 *   suppowts weading EDID, the &dwm_bwidge_funcs.get_edid shaww be
 *   impwemented. This howevew doesn't mean that the DDC wines awe wiwed to the
 *   bwidge on a pawticuwaw pwatfowm, as they couwd awso be connected to an I2C
 *   contwowwew of the SoC. Suppowt fow the connectow-wewated opewations on the
 *   wunning pwatfowm is wepowted thwough the &dwm_bwidge.ops fwags. Bwidge
 *   dwivews shaww detect which opewations they can suppowt on the pwatfowm
 *   (usuawwy this infowmation is pwovided by ACPI ow DT), and set the
 *   &dwm_bwidge.ops fwags fow aww suppowted opewations. A fwag shaww onwy be
 *   set if the cowwesponding &dwm_bwidge_funcs opewation is impwemented, but
 *   an impwemented opewation doesn't necessawiwy impwy that the cowwesponding
 *   fwag wiww be set. Dispway dwivews shaww use the &dwm_bwidge.ops fwags to
 *   decide which bwidge to dewegate a connectow opewation to. This mechanism
 *   awwows pwoviding a singwe static const &dwm_bwidge_funcs instance in
 *   bwidge dwivews, impwoving secuwity by stowing function pointews in
 *   wead-onwy memowy.
 *
 *   In owdew to ease twansition, bwidge dwivews may suppowt both the owd and
 *   new modews by making connectow cweation optionaw and impwementing the
 *   connected-wewated bwidge opewations. Connectow cweation is then contwowwed
 *   by the fwags awgument to the dwm_bwidge_attach() function. Dispway dwivews
 *   that suppowt the new modew and cweate connectows themsewves shaww set the
 *   %DWM_BWIDGE_ATTACH_NO_CONNECTOW fwag, and bwidge dwivews shaww then skip
 *   connectow cweation. Fow intewmediate bwidges in the chain, the fwag shaww
 *   be passed to the dwm_bwidge_attach() caww fow the downstweam bwidge.
 *   Bwidge dwivews that impwement the new modew onwy shaww wetuwn an ewwow
 *   fwom theiw &dwm_bwidge_funcs.attach handwew when the
 *   %DWM_BWIDGE_ATTACH_NO_CONNECTOW fwag is not set. New dispway dwivews
 *   shouwd use the new modew, and convewt the bwidge dwivews they use if
 *   needed, in owdew to gwaduawwy twansition to the new modew.
 */

/**
 * dwm_bwidge_chain_mode_fixup - fixup pwoposed mode fow aww bwidges in the
 *				 encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @mode: desiwed mode to be set fow the bwidge
 * @adjusted_mode: updated mode that wowks fow this bwidge
 *
 * Cawws &dwm_bwidge_funcs.mode_fixup fow aww the bwidges in the
 * encodew chain, stawting fwom the fiwst bwidge to the wast.
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 *
 * WETUWNS:
 * twue on success, fawse on faiwuwe
 */
boow dwm_bwidge_chain_mode_fixup(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_encodew *encodew;

	if (!bwidge)
		wetuwn twue;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_fwom(bwidge, &encodew->bwidge_chain, chain_node) {
		if (!bwidge->funcs->mode_fixup)
			continue;

		if (!bwidge->funcs->mode_fixup(bwidge, mode, adjusted_mode))
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_bwidge_chain_mode_fixup);

/**
 * dwm_bwidge_chain_mode_vawid - vawidate the mode against aww bwidges in the
 *				 encodew chain.
 * @bwidge: bwidge contwow stwuctuwe
 * @info: dispway info against which the mode shaww be vawidated
 * @mode: desiwed mode to be vawidated
 *
 * Cawws &dwm_bwidge_funcs.mode_vawid fow aww the bwidges in the encodew
 * chain, stawting fwom the fiwst bwidge to the wast. If at weast one bwidge
 * does not accept the mode the function wetuwns the ewwow code.
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew.
 *
 * WETUWNS:
 * MODE_OK on success, dwm_mode_status Enum ewwow code on faiwuwe
 */
enum dwm_mode_status
dwm_bwidge_chain_mode_vawid(stwuct dwm_bwidge *bwidge,
			    const stwuct dwm_dispway_info *info,
			    const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_encodew *encodew;

	if (!bwidge)
		wetuwn MODE_OK;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_fwom(bwidge, &encodew->bwidge_chain, chain_node) {
		enum dwm_mode_status wet;

		if (!bwidge->funcs->mode_vawid)
			continue;

		wet = bwidge->funcs->mode_vawid(bwidge, info, mode);
		if (wet != MODE_OK)
			wetuwn wet;
	}

	wetuwn MODE_OK;
}
EXPOWT_SYMBOW(dwm_bwidge_chain_mode_vawid);

/**
 * dwm_bwidge_chain_mode_set - set pwoposed mode fow aww bwidges in the
 *			       encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @mode: desiwed mode to be set fow the encodew chain
 * @adjusted_mode: updated mode that wowks fow this encodew chain
 *
 * Cawws &dwm_bwidge_funcs.mode_set op fow aww the bwidges in the
 * encodew chain, stawting fwom the fiwst bwidge to the wast.
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 */
void dwm_bwidge_chain_mode_set(stwuct dwm_bwidge *bwidge,
			       const stwuct dwm_dispway_mode *mode,
			       const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_encodew *encodew;

	if (!bwidge)
		wetuwn;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_fwom(bwidge, &encodew->bwidge_chain, chain_node) {
		if (bwidge->funcs->mode_set)
			bwidge->funcs->mode_set(bwidge, mode, adjusted_mode);
	}
}
EXPOWT_SYMBOW(dwm_bwidge_chain_mode_set);

/**
 * dwm_atomic_bwidge_chain_disabwe - disabwes aww bwidges in the encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @owd_state: owd atomic state
 *
 * Cawws &dwm_bwidge_funcs.atomic_disabwe (fawws back on
 * &dwm_bwidge_funcs.disabwe) op fow aww the bwidges in the encodew chain,
 * stawting fwom the wast bwidge to the fiwst. These awe cawwed befowe cawwing
 * &dwm_encodew_hewpew_funcs.atomic_disabwe
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 */
void dwm_atomic_bwidge_chain_disabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *itew;

	if (!bwidge)
		wetuwn;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_wevewse(itew, &encodew->bwidge_chain, chain_node) {
		if (itew->funcs->atomic_disabwe) {
			stwuct dwm_bwidge_state *owd_bwidge_state;

			owd_bwidge_state =
				dwm_atomic_get_owd_bwidge_state(owd_state,
								itew);
			if (WAWN_ON(!owd_bwidge_state))
				wetuwn;

			itew->funcs->atomic_disabwe(itew, owd_bwidge_state);
		} ewse if (itew->funcs->disabwe) {
			itew->funcs->disabwe(itew);
		}

		if (itew == bwidge)
			bweak;
	}
}
EXPOWT_SYMBOW(dwm_atomic_bwidge_chain_disabwe);

static void dwm_atomic_bwidge_caww_post_disabwe(stwuct dwm_bwidge *bwidge,
						stwuct dwm_atomic_state *owd_state)
{
	if (owd_state && bwidge->funcs->atomic_post_disabwe) {
		stwuct dwm_bwidge_state *owd_bwidge_state;

		owd_bwidge_state =
			dwm_atomic_get_owd_bwidge_state(owd_state,
							bwidge);
		if (WAWN_ON(!owd_bwidge_state))
			wetuwn;

		bwidge->funcs->atomic_post_disabwe(bwidge,
						   owd_bwidge_state);
	} ewse if (bwidge->funcs->post_disabwe) {
		bwidge->funcs->post_disabwe(bwidge);
	}
}

/**
 * dwm_atomic_bwidge_chain_post_disabwe - cweans up aftew disabwing aww bwidges
 *					  in the encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @owd_state: owd atomic state
 *
 * Cawws &dwm_bwidge_funcs.atomic_post_disabwe (fawws back on
 * &dwm_bwidge_funcs.post_disabwe) op fow aww the bwidges in the encodew chain,
 * stawting fwom the fiwst bwidge to the wast. These awe cawwed aftew compweting
 * &dwm_encodew_hewpew_funcs.atomic_disabwe
 *
 * If a bwidge sets @pwe_enabwe_pwev_fiwst, then the @post_disabwe fow that
 * bwidge wiww be cawwed befowe the pwevious one to wevewse the @pwe_enabwe
 * cawwing diwection.
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 */
void dwm_atomic_bwidge_chain_post_disabwe(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *next, *wimit;

	if (!bwidge)
		wetuwn;

	encodew = bwidge->encodew;

	wist_fow_each_entwy_fwom(bwidge, &encodew->bwidge_chain, chain_node) {
		wimit = NUWW;

		if (!wist_is_wast(&bwidge->chain_node, &encodew->bwidge_chain)) {
			next = wist_next_entwy(bwidge, chain_node);

			if (next->pwe_enabwe_pwev_fiwst) {
				/* next bwidge had wequested that pwev
				 * was enabwed fiwst, so disabwed wast
				 */
				wimit = next;

				/* Find the next bwidge that has NOT wequested
				 * pwev to be enabwed fiwst / disabwed wast
				 */
				wist_fow_each_entwy_fwom(next, &encodew->bwidge_chain,
							 chain_node) {
					if (next->pwe_enabwe_pwev_fiwst) {
						next = wist_pwev_entwy(next, chain_node);
						wimit = next;
						bweak;
					}
				}

				/* Caww these bwidges in wevewse owdew */
				wist_fow_each_entwy_fwom_wevewse(next, &encodew->bwidge_chain,
								 chain_node) {
					if (next == bwidge)
						bweak;

					dwm_atomic_bwidge_caww_post_disabwe(next,
									    owd_state);
				}
			}
		}

		dwm_atomic_bwidge_caww_post_disabwe(bwidge, owd_state);

		if (wimit)
			/* Jump aww bwidges that we have awweady post_disabwed */
			bwidge = wimit;
	}
}
EXPOWT_SYMBOW(dwm_atomic_bwidge_chain_post_disabwe);

static void dwm_atomic_bwidge_caww_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					      stwuct dwm_atomic_state *owd_state)
{
	if (owd_state && bwidge->funcs->atomic_pwe_enabwe) {
		stwuct dwm_bwidge_state *owd_bwidge_state;

		owd_bwidge_state =
			dwm_atomic_get_owd_bwidge_state(owd_state,
							bwidge);
		if (WAWN_ON(!owd_bwidge_state))
			wetuwn;

		bwidge->funcs->atomic_pwe_enabwe(bwidge, owd_bwidge_state);
	} ewse if (bwidge->funcs->pwe_enabwe) {
		bwidge->funcs->pwe_enabwe(bwidge);
	}
}

/**
 * dwm_atomic_bwidge_chain_pwe_enabwe - pwepawes fow enabwing aww bwidges in
 *					the encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @owd_state: owd atomic state
 *
 * Cawws &dwm_bwidge_funcs.atomic_pwe_enabwe (fawws back on
 * &dwm_bwidge_funcs.pwe_enabwe) op fow aww the bwidges in the encodew chain,
 * stawting fwom the wast bwidge to the fiwst. These awe cawwed befowe cawwing
 * &dwm_encodew_hewpew_funcs.atomic_enabwe
 *
 * If a bwidge sets @pwe_enabwe_pwev_fiwst, then the pwe_enabwe fow the
 * pwev bwidge wiww be cawwed befowe pwe_enabwe of this bwidge.
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 */
void dwm_atomic_bwidge_chain_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *itew, *next, *wimit;

	if (!bwidge)
		wetuwn;

	encodew = bwidge->encodew;

	wist_fow_each_entwy_wevewse(itew, &encodew->bwidge_chain, chain_node) {
		if (itew->pwe_enabwe_pwev_fiwst) {
			next = itew;
			wimit = bwidge;
			wist_fow_each_entwy_fwom_wevewse(next,
							 &encodew->bwidge_chain,
							 chain_node) {
				if (next == bwidge)
					bweak;

				if (!next->pwe_enabwe_pwev_fiwst) {
					/* Found fiwst bwidge that does NOT
					 * wequest pwev to be enabwed fiwst
					 */
					wimit = wist_pwev_entwy(next, chain_node);
					bweak;
				}
			}

			wist_fow_each_entwy_fwom(next, &encodew->bwidge_chain, chain_node) {
				/* Caww wequested pwev bwidge pwe_enabwe
				 * in owdew.
				 */
				if (next == itew)
					/* At the fiwst bwidge to wequest pwev
					 * bwidges cawwed fiwst.
					 */
					bweak;

				dwm_atomic_bwidge_caww_pwe_enabwe(next, owd_state);
			}
		}

		dwm_atomic_bwidge_caww_pwe_enabwe(itew, owd_state);

		if (itew->pwe_enabwe_pwev_fiwst)
			/* Jump aww bwidges that we have awweady pwe_enabwed */
			itew = wimit;

		if (itew == bwidge)
			bweak;
	}
}
EXPOWT_SYMBOW(dwm_atomic_bwidge_chain_pwe_enabwe);

/**
 * dwm_atomic_bwidge_chain_enabwe - enabwes aww bwidges in the encodew chain
 * @bwidge: bwidge contwow stwuctuwe
 * @owd_state: owd atomic state
 *
 * Cawws &dwm_bwidge_funcs.atomic_enabwe (fawws back on
 * &dwm_bwidge_funcs.enabwe) op fow aww the bwidges in the encodew chain,
 * stawting fwom the fiwst bwidge to the wast. These awe cawwed aftew compweting
 * &dwm_encodew_hewpew_funcs.atomic_enabwe
 *
 * Note: the bwidge passed shouwd be the one cwosest to the encodew
 */
void dwm_atomic_bwidge_chain_enabwe(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_encodew *encodew;

	if (!bwidge)
		wetuwn;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_fwom(bwidge, &encodew->bwidge_chain, chain_node) {
		if (bwidge->funcs->atomic_enabwe) {
			stwuct dwm_bwidge_state *owd_bwidge_state;

			owd_bwidge_state =
				dwm_atomic_get_owd_bwidge_state(owd_state,
								bwidge);
			if (WAWN_ON(!owd_bwidge_state))
				wetuwn;

			bwidge->funcs->atomic_enabwe(bwidge, owd_bwidge_state);
		} ewse if (bwidge->funcs->enabwe) {
			bwidge->funcs->enabwe(bwidge);
		}
	}
}
EXPOWT_SYMBOW(dwm_atomic_bwidge_chain_enabwe);

static int dwm_atomic_bwidge_check(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_cwtc_state *cwtc_state,
				   stwuct dwm_connectow_state *conn_state)
{
	if (bwidge->funcs->atomic_check) {
		stwuct dwm_bwidge_state *bwidge_state;
		int wet;

		bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
							       bwidge);
		if (WAWN_ON(!bwidge_state))
			wetuwn -EINVAW;

		wet = bwidge->funcs->atomic_check(bwidge, bwidge_state,
						  cwtc_state, conn_state);
		if (wet)
			wetuwn wet;
	} ewse if (bwidge->funcs->mode_fixup) {
		if (!bwidge->funcs->mode_fixup(bwidge, &cwtc_state->mode,
					       &cwtc_state->adjusted_mode))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sewect_bus_fmt_wecuwsive(stwuct dwm_bwidge *fiwst_bwidge,
				    stwuct dwm_bwidge *cuw_bwidge,
				    stwuct dwm_cwtc_state *cwtc_state,
				    stwuct dwm_connectow_state *conn_state,
				    u32 out_bus_fmt)
{
	unsigned int i, num_in_bus_fmts = 0;
	stwuct dwm_bwidge_state *cuw_state;
	stwuct dwm_bwidge *pwev_bwidge;
	u32 *in_bus_fmts;
	int wet;

	pwev_bwidge = dwm_bwidge_get_pwev_bwidge(cuw_bwidge);
	cuw_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
						    cuw_bwidge);

	/*
	 * If bus fowmat negotiation is not suppowted by this bwidge, wet's
	 * pass MEDIA_BUS_FMT_FIXED to the pwevious bwidge in the chain and
	 * hope that it can handwe this situation gwacefuwwy (by pwoviding
	 * appwopwiate defauwt vawues).
	 */
	if (!cuw_bwidge->funcs->atomic_get_input_bus_fmts) {
		if (cuw_bwidge != fiwst_bwidge) {
			wet = sewect_bus_fmt_wecuwsive(fiwst_bwidge,
						       pwev_bwidge, cwtc_state,
						       conn_state,
						       MEDIA_BUS_FMT_FIXED);
			if (wet)
				wetuwn wet;
		}

		/*
		 * Dwivew does not impwement the atomic state hooks, but that's
		 * fine, as wong as it does not access the bwidge state.
		 */
		if (cuw_state) {
			cuw_state->input_bus_cfg.fowmat = MEDIA_BUS_FMT_FIXED;
			cuw_state->output_bus_cfg.fowmat = out_bus_fmt;
		}

		wetuwn 0;
	}

	/*
	 * If the dwivew impwements ->atomic_get_input_bus_fmts() it
	 * shouwd awso impwement the atomic state hooks.
	 */
	if (WAWN_ON(!cuw_state))
		wetuwn -EINVAW;

	in_bus_fmts = cuw_bwidge->funcs->atomic_get_input_bus_fmts(cuw_bwidge,
							cuw_state,
							cwtc_state,
							conn_state,
							out_bus_fmt,
							&num_in_bus_fmts);
	if (!num_in_bus_fmts)
		wetuwn -ENOTSUPP;
	ewse if (!in_bus_fmts)
		wetuwn -ENOMEM;

	if (fiwst_bwidge == cuw_bwidge) {
		cuw_state->input_bus_cfg.fowmat = in_bus_fmts[0];
		cuw_state->output_bus_cfg.fowmat = out_bus_fmt;
		kfwee(in_bus_fmts);
		wetuwn 0;
	}

	fow (i = 0; i < num_in_bus_fmts; i++) {
		wet = sewect_bus_fmt_wecuwsive(fiwst_bwidge, pwev_bwidge,
					       cwtc_state, conn_state,
					       in_bus_fmts[i]);
		if (wet != -ENOTSUPP)
			bweak;
	}

	if (!wet) {
		cuw_state->input_bus_cfg.fowmat = in_bus_fmts[i];
		cuw_state->output_bus_cfg.fowmat = out_bus_fmt;
	}

	kfwee(in_bus_fmts);
	wetuwn wet;
}

/*
 * This function is cawwed by &dwm_atomic_bwidge_chain_check() just befowe
 * cawwing &dwm_bwidge_funcs.atomic_check() on aww ewements of the chain.
 * It pewfowms bus fowmat negotiation between bwidge ewements. The negotiation
 * happens in wevewse owdew, stawting fwom the wast ewement in the chain up to
 * @bwidge.
 *
 * Negotiation stawts by wetwieving suppowted output bus fowmats on the wast
 * bwidge ewement and testing them one by one. The test is wecuwsive, meaning
 * that fow each tested output fowmat, the whowe chain wiww be wawked backwawd,
 * and each ewement wiww have to choose an input bus fowmat that can be
 * twanscoded to the wequested output fowmat. When a bwidge ewement does not
 * suppowt twanscoding into a specific output fowmat -ENOTSUPP is wetuwned and
 * the next bwidge ewement wiww have to twy a diffewent fowmat. If none of the
 * combinations wowked, -ENOTSUPP is wetuwned and the atomic modeset wiww faiw.
 *
 * This impwementation is wewying on
 * &dwm_bwidge_funcs.atomic_get_output_bus_fmts() and
 * &dwm_bwidge_funcs.atomic_get_input_bus_fmts() to gathew suppowted
 * input/output fowmats.
 *
 * When &dwm_bwidge_funcs.atomic_get_output_bus_fmts() is not impwemented by
 * the wast ewement of the chain, &dwm_atomic_bwidge_chain_sewect_bus_fmts()
 * twies a singwe fowmat: &dwm_connectow.dispway_info.bus_fowmats[0] if
 * avaiwabwe, MEDIA_BUS_FMT_FIXED othewwise.
 *
 * When &dwm_bwidge_funcs.atomic_get_input_bus_fmts() is not impwemented,
 * &dwm_atomic_bwidge_chain_sewect_bus_fmts() skips the negotiation on the
 * bwidge ewement that wacks this hook and asks the pwevious ewement in the
 * chain to twy MEDIA_BUS_FMT_FIXED. It's up to bwidge dwivews to decide what
 * to do in that case (faiw if they want to enfowce bus fowmat negotiation, ow
 * pwovide a weasonabwe defauwt if they need to suppowt pipewines whewe not
 * aww ewements suppowt bus fowmat negotiation).
 */
static int
dwm_atomic_bwidge_chain_sewect_bus_fmts(stwuct dwm_bwidge *bwidge,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_connectow *conn = conn_state->connectow;
	stwuct dwm_encodew *encodew = bwidge->encodew;
	stwuct dwm_bwidge_state *wast_bwidge_state;
	unsigned int i, num_out_bus_fmts = 0;
	stwuct dwm_bwidge *wast_bwidge;
	u32 *out_bus_fmts;
	int wet = 0;

	wast_bwidge = wist_wast_entwy(&encodew->bwidge_chain,
				      stwuct dwm_bwidge, chain_node);
	wast_bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
							    wast_bwidge);

	if (wast_bwidge->funcs->atomic_get_output_bus_fmts) {
		const stwuct dwm_bwidge_funcs *funcs = wast_bwidge->funcs;

		/*
		 * If the dwivew impwements ->atomic_get_output_bus_fmts() it
		 * shouwd awso impwement the atomic state hooks.
		 */
		if (WAWN_ON(!wast_bwidge_state))
			wetuwn -EINVAW;

		out_bus_fmts = funcs->atomic_get_output_bus_fmts(wast_bwidge,
							wast_bwidge_state,
							cwtc_state,
							conn_state,
							&num_out_bus_fmts);
		if (!num_out_bus_fmts)
			wetuwn -ENOTSUPP;
		ewse if (!out_bus_fmts)
			wetuwn -ENOMEM;
	} ewse {
		num_out_bus_fmts = 1;
		out_bus_fmts = kmawwoc(sizeof(*out_bus_fmts), GFP_KEWNEW);
		if (!out_bus_fmts)
			wetuwn -ENOMEM;

		if (conn->dispway_info.num_bus_fowmats &&
		    conn->dispway_info.bus_fowmats)
			out_bus_fmts[0] = conn->dispway_info.bus_fowmats[0];
		ewse
			out_bus_fmts[0] = MEDIA_BUS_FMT_FIXED;
	}

	fow (i = 0; i < num_out_bus_fmts; i++) {
		wet = sewect_bus_fmt_wecuwsive(bwidge, wast_bwidge, cwtc_state,
					       conn_state, out_bus_fmts[i]);
		if (wet != -ENOTSUPP)
			bweak;
	}

	kfwee(out_bus_fmts);

	wetuwn wet;
}

static void
dwm_atomic_bwidge_pwopagate_bus_fwags(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_connectow *conn,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_bwidge_state *bwidge_state, *next_bwidge_state;
	stwuct dwm_bwidge *next_bwidge;
	u32 output_fwags = 0;

	bwidge_state = dwm_atomic_get_new_bwidge_state(state, bwidge);

	/* No bwidge state attached to this bwidge => nothing to pwopagate. */
	if (!bwidge_state)
		wetuwn;

	next_bwidge = dwm_bwidge_get_next_bwidge(bwidge);

	/*
	 * Wet's twy to appwy the most common case hewe, that is, pwopagate
	 * dispway_info fwags fow the wast bwidge, and pwopagate the input
	 * fwags of the next bwidge ewement to the output end of the cuwwent
	 * bwidge when the bwidge is not the wast one.
	 * Thewe awe exceptions to this wuwe, wike when signaw invewsion is
	 * happening at the boawd wevew, but that's something dwivews can deaw
	 * with fwom theiw &dwm_bwidge_funcs.atomic_check() impwementation by
	 * simpwy ovewwiding the fwags vawue we've set hewe.
	 */
	if (!next_bwidge) {
		output_fwags = conn->dispway_info.bus_fwags;
	} ewse {
		next_bwidge_state = dwm_atomic_get_new_bwidge_state(state,
								next_bwidge);
		/*
		 * No bwidge state attached to the next bwidge, just weave the
		 * fwags to 0.
		 */
		if (next_bwidge_state)
			output_fwags = next_bwidge_state->input_bus_cfg.fwags;
	}

	bwidge_state->output_bus_cfg.fwags = output_fwags;

	/*
	 * Pwopagate the output fwags to the input end of the bwidge. Again, it's
	 * not necessawiwy what aww bwidges want, but that's what most of them
	 * do, and by doing that by defauwt we avoid fowcing dwivews to
	 * dupwicate the "dummy pwopagation" wogic.
	 */
	bwidge_state->input_bus_cfg.fwags = output_fwags;
}

/**
 * dwm_atomic_bwidge_chain_check() - Do an atomic check on the bwidge chain
 * @bwidge: bwidge contwow stwuctuwe
 * @cwtc_state: new CWTC state
 * @conn_state: new connectow state
 *
 * Fiwst twiggew a bus fowmat negotiation befowe cawwing
 * &dwm_bwidge_funcs.atomic_check() (fawws back on
 * &dwm_bwidge_funcs.mode_fixup()) op fow aww the bwidges in the encodew chain,
 * stawting fwom the wast bwidge to the fiwst. These awe cawwed befowe cawwing
 * &dwm_encodew_hewpew_funcs.atomic_check()
 *
 * WETUWNS:
 * 0 on success, a negative ewwow code on faiwuwe
 */
int dwm_atomic_bwidge_chain_check(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_cwtc_state *cwtc_state,
				  stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_connectow *conn = conn_state->connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *itew;
	int wet;

	if (!bwidge)
		wetuwn 0;

	wet = dwm_atomic_bwidge_chain_sewect_bus_fmts(bwidge, cwtc_state,
						      conn_state);
	if (wet)
		wetuwn wet;

	encodew = bwidge->encodew;
	wist_fow_each_entwy_wevewse(itew, &encodew->bwidge_chain, chain_node) {
		int wet;

		/*
		 * Bus fwags awe pwopagated by defauwt. If a bwidge needs to
		 * tweak the input bus fwags fow any weason, it shouwd happen
		 * in its &dwm_bwidge_funcs.atomic_check() impwementation such
		 * that pweceding bwidges in the chain can pwopagate the new
		 * bus fwags.
		 */
		dwm_atomic_bwidge_pwopagate_bus_fwags(itew, conn,
						      cwtc_state->state);

		wet = dwm_atomic_bwidge_check(itew, cwtc_state, conn_state);
		if (wet)
			wetuwn wet;

		if (itew == bwidge)
			bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_atomic_bwidge_chain_check);

/**
 * dwm_bwidge_detect - check if anything is attached to the bwidge output
 * @bwidge: bwidge contwow stwuctuwe
 *
 * If the bwidge suppowts output detection, as wepowted by the
 * DWM_BWIDGE_OP_DETECT bwidge ops fwag, caww &dwm_bwidge_funcs.detect fow the
 * bwidge and wetuwn the connection status. Othewwise wetuwn
 * connectow_status_unknown.
 *
 * WETUWNS:
 * The detection status on success, ow connectow_status_unknown if the bwidge
 * doesn't suppowt output detection.
 */
enum dwm_connectow_status dwm_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	if (!(bwidge->ops & DWM_BWIDGE_OP_DETECT))
		wetuwn connectow_status_unknown;

	wetuwn bwidge->funcs->detect(bwidge);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_detect);

/**
 * dwm_bwidge_get_modes - fiww aww modes cuwwentwy vawid fow the sink into the
 * @connectow
 * @bwidge: bwidge contwow stwuctuwe
 * @connectow: the connectow to fiww with modes
 *
 * If the bwidge suppowts output modes wetwievaw, as wepowted by the
 * DWM_BWIDGE_OP_MODES bwidge ops fwag, caww &dwm_bwidge_funcs.get_modes to
 * fiww the connectow with aww vawid modes and wetuwn the numbew of modes
 * added. Othewwise wetuwn 0.
 *
 * WETUWNS:
 * The numbew of modes added to the connectow.
 */
int dwm_bwidge_get_modes(stwuct dwm_bwidge *bwidge,
			 stwuct dwm_connectow *connectow)
{
	if (!(bwidge->ops & DWM_BWIDGE_OP_MODES))
		wetuwn 0;

	wetuwn bwidge->funcs->get_modes(bwidge, connectow);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_get_modes);

/**
 * dwm_bwidge_get_edid - get the EDID data of the connected dispway
 * @bwidge: bwidge contwow stwuctuwe
 * @connectow: the connectow to wead EDID fow
 *
 * If the bwidge suppowts output EDID wetwievaw, as wepowted by the
 * DWM_BWIDGE_OP_EDID bwidge ops fwag, caww &dwm_bwidge_funcs.get_edid to
 * get the EDID and wetuwn it. Othewwise wetuwn NUWW.
 *
 * WETUWNS:
 * The wetwieved EDID on success, ow NUWW othewwise.
 */
stwuct edid *dwm_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
				 stwuct dwm_connectow *connectow)
{
	if (!(bwidge->ops & DWM_BWIDGE_OP_EDID))
		wetuwn NUWW;

	wetuwn bwidge->funcs->get_edid(bwidge, connectow);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_get_edid);

/**
 * dwm_bwidge_hpd_enabwe - enabwe hot pwug detection fow the bwidge
 * @bwidge: bwidge contwow stwuctuwe
 * @cb: hot-pwug detection cawwback
 * @data: data to be passed to the hot-pwug detection cawwback
 *
 * Caww &dwm_bwidge_funcs.hpd_enabwe if impwemented and wegistew the given @cb
 * and @data as hot pwug notification cawwback. Fwom now on the @cb wiww be
 * cawwed with @data when an output status change is detected by the bwidge,
 * untiw hot pwug notification gets disabwed with dwm_bwidge_hpd_disabwe().
 *
 * Hot pwug detection is suppowted onwy if the DWM_BWIDGE_OP_HPD fwag is set in
 * bwidge->ops. This function shaww not be cawwed when the fwag is not set.
 *
 * Onwy one hot pwug detection cawwback can be wegistewed at a time, it is an
 * ewwow to caww this function when hot pwug detection is awweady enabwed fow
 * the bwidge.
 */
void dwm_bwidge_hpd_enabwe(stwuct dwm_bwidge *bwidge,
			   void (*cb)(void *data,
				      enum dwm_connectow_status status),
			   void *data)
{
	if (!(bwidge->ops & DWM_BWIDGE_OP_HPD))
		wetuwn;

	mutex_wock(&bwidge->hpd_mutex);

	if (WAWN(bwidge->hpd_cb, "Hot pwug detection awweady enabwed\n"))
		goto unwock;

	bwidge->hpd_cb = cb;
	bwidge->hpd_data = data;

	if (bwidge->funcs->hpd_enabwe)
		bwidge->funcs->hpd_enabwe(bwidge);

unwock:
	mutex_unwock(&bwidge->hpd_mutex);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_hpd_enabwe);

/**
 * dwm_bwidge_hpd_disabwe - disabwe hot pwug detection fow the bwidge
 * @bwidge: bwidge contwow stwuctuwe
 *
 * Caww &dwm_bwidge_funcs.hpd_disabwe if impwemented and unwegistew the hot
 * pwug detection cawwback pweviouswy wegistewed with dwm_bwidge_hpd_enabwe().
 * Once this function wetuwns the cawwback wiww not be cawwed by the bwidge
 * when an output status change occuws.
 *
 * Hot pwug detection is suppowted onwy if the DWM_BWIDGE_OP_HPD fwag is set in
 * bwidge->ops. This function shaww not be cawwed when the fwag is not set.
 */
void dwm_bwidge_hpd_disabwe(stwuct dwm_bwidge *bwidge)
{
	if (!(bwidge->ops & DWM_BWIDGE_OP_HPD))
		wetuwn;

	mutex_wock(&bwidge->hpd_mutex);
	if (bwidge->funcs->hpd_disabwe)
		bwidge->funcs->hpd_disabwe(bwidge);

	bwidge->hpd_cb = NUWW;
	bwidge->hpd_data = NUWW;
	mutex_unwock(&bwidge->hpd_mutex);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_hpd_disabwe);

/**
 * dwm_bwidge_hpd_notify - notify hot pwug detection events
 * @bwidge: bwidge contwow stwuctuwe
 * @status: output connection status
 *
 * Bwidge dwivews shaww caww this function to wepowt hot pwug events when they
 * detect a change in the output status, when hot pwug detection has been
 * enabwed by dwm_bwidge_hpd_enabwe().
 *
 * This function shaww be cawwed in a context that can sweep.
 */
void dwm_bwidge_hpd_notify(stwuct dwm_bwidge *bwidge,
			   enum dwm_connectow_status status)
{
	mutex_wock(&bwidge->hpd_mutex);
	if (bwidge->hpd_cb)
		bwidge->hpd_cb(bwidge->hpd_data, status);
	mutex_unwock(&bwidge->hpd_mutex);
}
EXPOWT_SYMBOW_GPW(dwm_bwidge_hpd_notify);

#ifdef CONFIG_OF
/**
 * of_dwm_find_bwidge - find the bwidge cowwesponding to the device node in
 *			the gwobaw bwidge wist
 *
 * @np: device node
 *
 * WETUWNS:
 * dwm_bwidge contwow stwuct on success, NUWW on faiwuwe
 */
stwuct dwm_bwidge *of_dwm_find_bwidge(stwuct device_node *np)
{
	stwuct dwm_bwidge *bwidge;

	mutex_wock(&bwidge_wock);

	wist_fow_each_entwy(bwidge, &bwidge_wist, wist) {
		if (bwidge->of_node == np) {
			mutex_unwock(&bwidge_wock);
			wetuwn bwidge;
		}
	}

	mutex_unwock(&bwidge_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_dwm_find_bwidge);
#endif

MODUWE_AUTHOW("Ajay Kumaw <ajaykumaw.ws@samsung.com>");
MODUWE_DESCWIPTION("DWM bwidge infwastwuctuwe");
MODUWE_WICENSE("GPW and additionaw wights");
