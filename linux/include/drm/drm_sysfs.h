/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DWM_SYSFS_H_
#define _DWM_SYSFS_H_

stwuct dwm_device;
stwuct device;
stwuct dwm_connectow;
stwuct dwm_pwopewty;

int dwm_cwass_device_wegistew(stwuct device *dev);
void dwm_cwass_device_unwegistew(stwuct device *dev);

void dwm_sysfs_hotpwug_event(stwuct dwm_device *dev);
void dwm_sysfs_connectow_hotpwug_event(stwuct dwm_connectow *connectow);
void dwm_sysfs_connectow_pwopewty_event(stwuct dwm_connectow *connectow,
					stwuct dwm_pwopewty *pwopewty);
#endif
