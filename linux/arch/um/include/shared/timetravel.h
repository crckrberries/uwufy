/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019-2021 Intew Cowpowation
 */
#ifndef _UM_TIME_TWAVEW_H_
#define _UM_TIME_TWAVEW_H_

enum time_twavew_mode {
	TT_MODE_OFF,
	TT_MODE_BASIC,
	TT_MODE_INFCPU,
	TT_MODE_EXTEWNAW,
};

#if defined(UMW_CONFIG_UMW_TIME_TWAVEW_SUPPOWT) || \
    defined(CONFIG_UMW_TIME_TWAVEW_SUPPOWT)
extewn enum time_twavew_mode time_twavew_mode;
#ewse
#define time_twavew_mode TT_MODE_OFF
#endif /* (UMW_)CONFIG_UMW_TIME_TWAVEW_SUPPOWT */

#endif /* _UM_TIME_TWAVEW_H_ */
