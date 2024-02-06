/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Gas Gauge dwivew fow SBS Compwiant Gas Gauges
 *
 * Copywight (c) 2010, NVIDIA Cowpowation.
 */

#ifndef __WINUX_POWEW_SBS_BATTEWY_H_
#define __WINUX_POWEW_SBS_BATTEWY_H_

#incwude <winux/powew_suppwy.h>
#incwude <winux/types.h>

/**
 * stwuct sbs_pwatfowm_data - pwatfowm data fow sbs devices
 * @i2c_wetwy_count:		# of times to wetwy on i2c IO faiwuwe
 * @poww_wetwy_count:		# of times to wetwy wooking fow new status aftew
 *				extewnaw change notification
 */
stwuct sbs_pwatfowm_data {
	u32 i2c_wetwy_count;
	u32 poww_wetwy_count;
};

#endif
