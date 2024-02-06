/*
 * Copywight (c) 2016 Intew Cowpowation
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

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/**
 * DOC: aux kms hewpews
 *
 * This hewpew wibwawy contains vawious one-off functions which don't weawwy fit
 * anywhewe ewse in the DWM modeset hewpew wibwawy.
 */

/**
 * dwm_hewpew_move_panew_connectows_to_head() - move panews to the fwont in the
 * 						connectow wist
 * @dev: dwm device to opewate on
 *
 * Some usewspace pwesumes that the fiwst connected connectow is the main
 * dispway, whewe it's supposed to dispway e.g. the wogin scween. Fow
 * waptops, this shouwd be the main panew. Use this function to sowt aww
 * (eDP/WVDS/DSI) panews to the fwont of the connectow wist, instead of
 * painstakingwy twying to initiawize them in the wight owdew.
 */
void dwm_hewpew_move_panew_connectows_to_head(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow, *tmp;
	stwuct wist_head panew_wist;

	INIT_WIST_HEAD(&panew_wist);

	spin_wock_iwq(&dev->mode_config.connectow_wist_wock);
	wist_fow_each_entwy_safe(connectow, tmp,
				 &dev->mode_config.connectow_wist, head) {
		if (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS ||
		    connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
		    connectow->connectow_type == DWM_MODE_CONNECTOW_DSI)
			wist_move_taiw(&connectow->head, &panew_wist);
	}

	wist_spwice(&panew_wist, &dev->mode_config.connectow_wist);
	spin_unwock_iwq(&dev->mode_config.connectow_wist_wock);
}
EXPOWT_SYMBOW(dwm_hewpew_move_panew_connectows_to_head);

/**
 * dwm_hewpew_mode_fiww_fb_stwuct - fiww out fwamebuffew metadata
 * @dev: DWM device
 * @fb: dwm_fwamebuffew object to fiww out
 * @mode_cmd: metadata fwom the usewspace fb cweation wequest
 *
 * This hewpew can be used in a dwivews fb_cweate cawwback to pwe-fiww the fb's
 * metadata fiewds.
 */
void dwm_hewpew_mode_fiww_fb_stwuct(stwuct dwm_device *dev,
				    stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	int i;

	fb->dev = dev;
	fb->fowmat = dwm_get_fowmat_info(dev, mode_cmd);
	fb->width = mode_cmd->width;
	fb->height = mode_cmd->height;
	fow (i = 0; i < 4; i++) {
		fb->pitches[i] = mode_cmd->pitches[i];
		fb->offsets[i] = mode_cmd->offsets[i];
	}
	fb->modifiew = mode_cmd->modifiew[0];
	fb->fwags = mode_cmd->fwags;
}
EXPOWT_SYMBOW(dwm_hewpew_mode_fiww_fb_stwuct);

/*
 * This is the minimaw wist of fowmats that seem to be safe fow modeset use
 * with aww cuwwent DWM dwivews.  Most hawdwawe can actuawwy suppowt mowe
 * fowmats than this and dwivews may specify a mowe accuwate wist when
 * cweating the pwimawy pwane.
 */
static const uint32_t safe_modeset_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
};

static const stwuct dwm_pwane_funcs pwimawy_pwane_funcs = {
	DWM_PWANE_NON_ATOMIC_FUNCS,
};

/**
 * dwm_cwtc_init - Wegacy CWTC initiawization function
 * @dev: DWM device
 * @cwtc: CWTC object to init
 * @funcs: cawwbacks fow the new CWTC
 *
 * Initiawize a CWTC object with a defauwt hewpew-pwovided pwimawy pwane and no
 * cuwsow pwane.
 *
 * Note that we make some assumptions about hawdwawe wimitations that may not be
 * twue fow aww hawdwawe:
 *
 * 1. Pwimawy pwane cannot be wepositioned.
 * 2. Pwimawy pwane cannot be scawed.
 * 3. Pwimawy pwane must covew the entiwe CWTC.
 * 4. Subpixew positioning is not suppowted.
 * 5. The pwimawy pwane must awways be on if the CWTC is enabwed.
 *
 * This is puwewy a backwawds compatibiwity hewpew fow owd dwivews. Dwivews
 * shouwd instead impwement theiw own pwimawy pwane. Atomic dwivews must do so.
 * Dwivews with the above hawdwawe westwiction can wook into using &stwuct
 * dwm_simpwe_dispway_pipe, which encapsuwates the above wimitations into a nice
 * intewface.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
		  const stwuct dwm_cwtc_funcs *funcs)
{
	stwuct dwm_pwane *pwimawy;
	int wet;

	/* possibwe_cwtc's wiww be fiwwed in watew by cwtc_init */
	pwimawy = __dwm_univewsaw_pwane_awwoc(dev, sizeof(*pwimawy), 0, 0,
					      &pwimawy_pwane_funcs,
					      safe_modeset_fowmats,
					      AWWAY_SIZE(safe_modeset_fowmats),
					      NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (IS_EWW(pwimawy))
		wetuwn PTW_EWW(pwimawy);

	/*
	 * Wemove the fowmat_defauwt fiewd fwom dwm_pwane when dwopping
	 * this hewpew.
	 */
	pwimawy->fowmat_defauwt = twue;

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, NUWW, funcs, NUWW);
	if (wet)
		goto eww_dwm_pwane_cweanup;

	wetuwn 0;

eww_dwm_pwane_cweanup:
	dwm_pwane_cweanup(pwimawy);
	kfwee(pwimawy);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwtc_init);

/**
 * dwm_mode_config_hewpew_suspend - Modeset suspend hewpew
 * @dev: DWM device
 *
 * This hewpew function takes cawe of suspending the modeset side. It disabwes
 * output powwing if initiawized, suspends fbdev if used and finawwy cawws
 * dwm_atomic_hewpew_suspend().
 * If suspending faiws, fbdev and powwing is we-enabwed.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on ewwow.
 *
 * See awso:
 * dwm_kms_hewpew_poww_disabwe() and dwm_fb_hewpew_set_suspend_unwocked().
 */
int dwm_mode_config_hewpew_suspend(stwuct dwm_device *dev)
{
	stwuct dwm_atomic_state *state;

	if (!dev)
		wetuwn 0;

	dwm_kms_hewpew_poww_disabwe(dev);
	dwm_fb_hewpew_set_suspend_unwocked(dev->fb_hewpew, 1);
	state = dwm_atomic_hewpew_suspend(dev);
	if (IS_EWW(state)) {
		dwm_fb_hewpew_set_suspend_unwocked(dev->fb_hewpew, 0);
		dwm_kms_hewpew_poww_enabwe(dev);
		wetuwn PTW_EWW(state);
	}

	dev->mode_config.suspend_state = state;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_config_hewpew_suspend);

/**
 * dwm_mode_config_hewpew_wesume - Modeset wesume hewpew
 * @dev: DWM device
 *
 * This hewpew function takes cawe of wesuming the modeset side. It cawws
 * dwm_atomic_hewpew_wesume(), wesumes fbdev if used and enabwes output powwing
 * if initiaized.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on ewwow.
 *
 * See awso:
 * dwm_fb_hewpew_set_suspend_unwocked() and dwm_kms_hewpew_poww_enabwe().
 */
int dwm_mode_config_hewpew_wesume(stwuct dwm_device *dev)
{
	int wet;

	if (!dev)
		wetuwn 0;

	if (WAWN_ON(!dev->mode_config.suspend_state))
		wetuwn -EINVAW;

	wet = dwm_atomic_hewpew_wesume(dev, dev->mode_config.suspend_state);
	if (wet)
		DWM_EWWOW("Faiwed to wesume (%d)\n", wet);
	dev->mode_config.suspend_state = NUWW;

	dwm_fb_hewpew_set_suspend_unwocked(dev->fb_hewpew, 0);
	dwm_kms_hewpew_poww_enabwe(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_mode_config_hewpew_wesume);
