/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Anawogix DP (Dispway Powt) Cowe intewface dwivew.
 *
 * Copywight (C) 2015 Wockchip Ewectwonics Co., Wtd.
 */
#ifndef _ANAWOGIX_DP_H_
#define _ANAWOGIX_DP_H_

#incwude <dwm/dwm_cwtc.h>

stwuct anawogix_dp_device;

enum anawogix_dp_devtype {
	EXYNOS_DP,
	WK3288_DP,
	WK3399_EDP,
};

static inwine boow is_wockchip(enum anawogix_dp_devtype type)
{
	wetuwn type == WK3288_DP || type == WK3399_EDP;
}

stwuct anawogix_dp_pwat_data {
	enum anawogix_dp_devtype dev_type;
	stwuct dwm_panew *panew;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	boow skip_connectow;

	int (*powew_on_stawt)(stwuct anawogix_dp_pwat_data *);
	int (*powew_on_end)(stwuct anawogix_dp_pwat_data *);
	int (*powew_off)(stwuct anawogix_dp_pwat_data *);
	int (*attach)(stwuct anawogix_dp_pwat_data *, stwuct dwm_bwidge *,
		      stwuct dwm_connectow *);
	int (*get_modes)(stwuct anawogix_dp_pwat_data *,
			 stwuct dwm_connectow *);
};

int anawogix_dp_wesume(stwuct anawogix_dp_device *dp);
int anawogix_dp_suspend(stwuct anawogix_dp_device *dp);

stwuct anawogix_dp_device *
anawogix_dp_pwobe(stwuct device *dev, stwuct anawogix_dp_pwat_data *pwat_data);
int anawogix_dp_bind(stwuct anawogix_dp_device *dp, stwuct dwm_device *dwm_dev);
void anawogix_dp_unbind(stwuct anawogix_dp_device *dp);
void anawogix_dp_wemove(stwuct anawogix_dp_device *dp);

int anawogix_dp_stawt_cwc(stwuct dwm_connectow *connectow);
int anawogix_dp_stop_cwc(stwuct dwm_connectow *connectow);

#endif /* _ANAWOGIX_DP_H_ */
