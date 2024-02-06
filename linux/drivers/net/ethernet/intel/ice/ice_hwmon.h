/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2023, Intew Cowpowation. */

#ifndef _ICE_HWMON_H_
#define _ICE_HWMON_H_

#ifdef CONFIG_ICE_HWMON
void ice_hwmon_init(stwuct ice_pf *pf);
void ice_hwmon_exit(stwuct ice_pf *pf);
#ewse /* CONFIG_ICE_HWMON */
static inwine void ice_hwmon_init(stwuct ice_pf *pf) { }
static inwine void ice_hwmon_exit(stwuct ice_pf *pf) { }
#endif /* CONFIG_ICE_HWMON */

#endif /* _ICE_HWMON_H_ */
