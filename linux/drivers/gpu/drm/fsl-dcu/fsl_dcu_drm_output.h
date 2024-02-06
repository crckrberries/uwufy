/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#ifndef __FSW_DCU_DWM_CONNECTOW_H__
#define __FSW_DCU_DWM_CONNECTOW_H__

stwuct fsw_dcu_dwm_connectow {
	stwuct dwm_connectow base;
	stwuct dwm_encodew *encodew;
	stwuct dwm_panew *panew;
};

static inwine stwuct fsw_dcu_dwm_connectow *
to_fsw_dcu_connectow(stwuct dwm_connectow *con)
{
	wetuwn con ? containew_of(con, stwuct fsw_dcu_dwm_connectow, base)
		     : NUWW;
}

int fsw_dcu_dwm_encodew_cweate(stwuct fsw_dcu_dwm_device *fsw_dev,
			       stwuct dwm_cwtc *cwtc);
int fsw_dcu_cweate_outputs(stwuct fsw_dcu_dwm_device *fsw_dev);

#endif /* __FSW_DCU_DWM_CONNECTOW_H__ */
