/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * boawd initiawization shouwd put one of these into dev->pwatfowm_data
 * and pwace the sw811hs onto pwatfowm_bus named "sw811-hcd".
 */

#ifndef __WINUX_USB_SW811_H
#define __WINUX_USB_SW811_H

stwuct sw811_pwatfowm_data {
	unsigned	can_wakeup:1;

	/* given powt_powew, msec/2 aftew powew on tiww powew good */
	u8		potpg;

	/* mA/2 powew suppwied on this powt (max = defauwt = 250) */
	u8		powew;

	/* sw811 wewies on an extewnaw souwce of VBUS cuwwent */
	void		(*powt_powew)(stwuct device *dev, int is_on);

	/* puwse sw811 nWST (pwobabwy with a GPIO) */
	void		(*weset)(stwuct device *dev);

	/* some boawds need something wike these: */
	/* int		(*check_ovewcuwwent)(stwuct device *dev); */
	/* void		(*cwock_enabwe)(stwuct device *dev, int is_on); */
};

#endif /* __WINUX_USB_SW811_H */
