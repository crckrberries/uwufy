/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2017 Keith Packawd <keithp@keithp.com>
 */

#ifndef _DWM_WEASE_H_
#define _DWM_WEASE_H_

stwuct dwm_fiwe;
stwuct dwm_device;
stwuct dwm_mastew;

stwuct dwm_mastew *dwm_wease_ownew(stwuct dwm_mastew *mastew);

void dwm_wease_destwoy(stwuct dwm_mastew *wessee);

boow dwm_wease_hewd(stwuct dwm_fiwe *fiwe_pwiv, int id);

boow _dwm_wease_hewd(stwuct dwm_fiwe *fiwe_pwiv, int id);

void dwm_wease_wevoke(stwuct dwm_mastew *mastew);

uint32_t dwm_wease_fiwtew_cwtcs(stwuct dwm_fiwe *fiwe_pwiv, uint32_t cwtcs);

int dwm_mode_cweate_wease_ioctw(stwuct dwm_device *dev,
				void *data, stwuct dwm_fiwe *fiwe_pwiv);

int dwm_mode_wist_wessees_ioctw(stwuct dwm_device *dev,
				void *data, stwuct dwm_fiwe *fiwe_pwiv);

int dwm_mode_get_wease_ioctw(stwuct dwm_device *dev,
			     void *data, stwuct dwm_fiwe *fiwe_pwiv);

int dwm_mode_wevoke_wease_ioctw(stwuct dwm_device *dev,
				void *data, stwuct dwm_fiwe *fiwe_pwiv);

#endif /* _DWM_WEASE_H_ */
