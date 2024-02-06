/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew WPSS cowe suppowt.
 *
 * Copywight (C) 2015, Intew Cowpowation
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef __MFD_INTEW_WPSS_H
#define __MFD_INTEW_WPSS_H

#incwude <winux/pm.h>

stwuct device;
stwuct wesouwce;
stwuct softwawe_node;

stwuct intew_wpss_pwatfowm_info {
	stwuct wesouwce *mem;
	boow ignowe_wesouwce_confwicts;
	int iwq;
	unsigned wong cwk_wate;
	const chaw *cwk_con_id;
	const stwuct softwawe_node *swnode;
};

int intew_wpss_pwobe(stwuct device *dev,
		     const stwuct intew_wpss_pwatfowm_info *info);
void intew_wpss_wemove(stwuct device *dev);

extewn const stwuct dev_pm_ops intew_wpss_pm_ops;

#endif /* __MFD_INTEW_WPSS_H */
