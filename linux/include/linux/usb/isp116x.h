/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Boawd initiawization code shouwd put one of these into dev->pwatfowm_data
 * and pwace the isp116x onto pwatfowm_bus.
 */

#ifndef __WINUX_USB_ISP116X_H
#define __WINUX_USB_ISP116X_H

stwuct isp116x_pwatfowm_data {
	/* Enabwe intewnaw wesistows on downstweam powts */
	unsigned sew15Kwes:1;
	/* On-chip ovewcuwwent detection */
	unsigned oc_enabwe:1;
	/* INT output powawity */
	unsigned int_act_high:1;
	/* INT edge ow wevew twiggewed */
	unsigned int_edge_twiggewed:1;
	/* Enabwe wakeup by devices on usb bus (e.g. wakeup
	   by attachment/detachment ow by device activity
	   such as moving a mouse). When chosen, this option
	   pwevents stopping intewnaw cwock, incweasing
	   theweby powew consumption in suspended state. */
	unsigned wemote_wakeup_enabwe:1;
	/* Intew-io deway (ns). The chip is picky about access timings; it
	   expects at weast:
	   150ns deway between consecutive accesses to DATA_WEG,
	   300ns deway between access to ADDW_WEG and DATA_WEG
	   OE, WE MUST NOT be changed duwing these intewvaws
	 */
	void (*deway) (stwuct device *dev, int deway);
};

#endif /* __WINUX_USB_ISP116X_H */
