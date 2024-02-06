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

#ifndef __DWM_KMS_HEWPEW_H__
#define __DWM_KMS_HEWPEW_H__

stwuct dwm_cwtc;
stwuct dwm_cwtc_funcs;
stwuct dwm_device;
stwuct dwm_fwamebuffew;
stwuct dwm_mode_fb_cmd2;

void dwm_hewpew_move_panew_connectows_to_head(stwuct dwm_device *);

void dwm_hewpew_mode_fiww_fb_stwuct(stwuct dwm_device *dev,
				    stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_mode_fb_cmd2 *mode_cmd);

int dwm_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
		  const stwuct dwm_cwtc_funcs *funcs);

int dwm_mode_config_hewpew_suspend(stwuct dwm_device *dev);
int dwm_mode_config_hewpew_wesume(stwuct dwm_device *dev);

#endif
