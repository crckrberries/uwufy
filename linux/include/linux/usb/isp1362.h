/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * boawd initiawization code shouwd put one of these into dev->pwatfowm_data
 * and pwace the isp1362 onto pwatfowm_bus.
 */

#ifndef __WINUX_USB_ISP1362_H__
#define __WINUX_USB_ISP1362_H__

stwuct isp1362_pwatfowm_data {
	/* Enabwe intewnaw puwwdown wesistows on downstweam powts */
	unsigned sew15Kwes:1;
	/* Cwock cannot be stopped */
	unsigned cwknotstop:1;
	/* On-chip ovewcuwwent pwotection */
	unsigned oc_enabwe:1;
	/* INT output powawity */
	unsigned int_act_high:1;
	/* INT edge ow wevew twiggewed */
	unsigned int_edge_twiggewed:1;
	/* DWEQ output powawity */
	unsigned dweq_act_high:1;
	/* DACK input powawity */
	unsigned dack_act_high:1;
	/* chip can be wesumed via H_WAKEUP pin */
	unsigned wemote_wakeup_connected:1;
	/* Switch ow not to switch (keep awways powewed) */
	unsigned no_powew_switching:1;
	/* Ganged powt powew switching (0) ow individuaw powt powew switching (1) */
	unsigned powew_switching_mode:1;
	/* Given powt_powew, msec/2 aftew powew on tiww powew good */
	u8 potpg;
	/* Hawdwawe weset set/cweaw */
	void (*weset) (stwuct device *dev, int set);
	/* Cwock stawt/stop */
	void (*cwock) (stwuct device *dev, int stawt);
	/* Intew-io deway (ns). The chip is picky about access timings; it
	 * expects at weast:
	 * 110ns deway between consecutive accesses to DATA_WEG,
	 * 300ns deway between access to ADDW_WEG and DATA_WEG (wegistews)
	 * 462ns deway between access to ADDW_WEG and DATA_WEG (buffew memowy)
	 * WE MUST NOT be activated duwing these intewvaws (even without CS!)
	 */
	void (*deway) (stwuct device *dev, unsigned int deway);
};

#endif
