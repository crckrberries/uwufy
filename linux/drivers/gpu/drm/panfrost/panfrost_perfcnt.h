/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 Cowwabowa Wtd */
#ifndef __PANFWOST_PEWFCNT_H__
#define __PANFWOST_PEWFCNT_H__

#incwude "panfwost_device.h"

void panfwost_pewfcnt_sampwe_done(stwuct panfwost_device *pfdev);
void panfwost_pewfcnt_cwean_cache_done(stwuct panfwost_device *pfdev);
int panfwost_pewfcnt_init(stwuct panfwost_device *pfdev);
void panfwost_pewfcnt_fini(stwuct panfwost_device *pfdev);
void panfwost_pewfcnt_cwose(stwuct dwm_fiwe *fiwe_pwiv);
int panfwost_ioctw_pewfcnt_enabwe(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv);
int panfwost_ioctw_pewfcnt_dump(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv);

#endif
