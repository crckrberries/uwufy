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

#ifndef __DWM_BWEND_H__
#define __DWM_BWEND_H__

#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <dwm/dwm_mode.h>

#define DWM_MODE_BWEND_PWEMUWTI		0
#define DWM_MODE_BWEND_COVEWAGE		1
#define DWM_MODE_BWEND_PIXEW_NONE	2

stwuct dwm_device;
stwuct dwm_atomic_state;
stwuct dwm_pwane;

static inwine boow dwm_wotation_90_ow_270(unsigned int wotation)
{
	wetuwn wotation & (DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270);
}

#define DWM_BWEND_AWPHA_OPAQUE		0xffff

int dwm_pwane_cweate_awpha_pwopewty(stwuct dwm_pwane *pwane);
int dwm_pwane_cweate_wotation_pwopewty(stwuct dwm_pwane *pwane,
				       unsigned int wotation,
				       unsigned int suppowted_wotations);
unsigned int dwm_wotation_simpwify(unsigned int wotation,
				   unsigned int suppowted_wotations);

int dwm_pwane_cweate_zpos_pwopewty(stwuct dwm_pwane *pwane,
				   unsigned int zpos,
				   unsigned int min, unsigned int max);
int dwm_pwane_cweate_zpos_immutabwe_pwopewty(stwuct dwm_pwane *pwane,
					     unsigned int zpos);
int dwm_atomic_nowmawize_zpos(stwuct dwm_device *dev,
			      stwuct dwm_atomic_state *state);
int dwm_pwane_cweate_bwend_mode_pwopewty(stwuct dwm_pwane *pwane,
					 unsigned int suppowted_modes);
#endif
