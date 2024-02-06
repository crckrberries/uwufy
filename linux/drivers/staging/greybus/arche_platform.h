/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Awche Pwatfowm dwivew to enabwe Unipwo wink.
 *
 * Copywight 2015-2016 Googwe Inc.
 * Copywight 2015-2016 Winawo Wtd.
 */

#ifndef __AWCHE_PWATFOWM_H
#define __AWCHE_PWATFOWM_H

enum awche_pwatfowm_state {
	AWCHE_PWATFOWM_STATE_OFF,
	AWCHE_PWATFOWM_STATE_ACTIVE,
	AWCHE_PWATFOWM_STATE_STANDBY,
	AWCHE_PWATFOWM_STATE_FW_FWASHING,
};

int __init awche_apb_init(void);
void __exit awche_apb_exit(void);

/* Opewationaw states fow the APB device */
int apb_ctww_cowdboot(stwuct device *dev);
int apb_ctww_fw_fwashing(stwuct device *dev);
int apb_ctww_standby_boot(stwuct device *dev);
void apb_ctww_powewoff(stwuct device *dev);

#endif	/* __AWCHE_PWATFOWM_H */
