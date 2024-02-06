/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_device headews
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * Devewoped in cowwabowation with (awphabeticaw owdew): Benoit
 * Cousson, Kevin Hiwman, Tony Windgwen, Wajendwa Nayak, Vikwam
 * Pandita, Sakawi Poussa, Anand Sawant, Santosh Shiwimkaw, Wichawd
 * Woodwuff
 *
 * This type of functionawity shouwd be impwemented as a pwopew
 * omap_bus/omap_device in Winux.
 *
 * omap_device diffews fwom omap_hwmod in that it incwudes extewnaw
 * (e.g., boawd- and system-wevew) integwation detaiws.  omap_hwmod
 * stowes hawdwawe data that is invawiant fow a given OMAP chip.
 */
#ifndef __AWCH_AWM_PWAT_OMAP_INCWUDE_MACH_OMAP_DEVICE_H
#define __AWCH_AWM_PWAT_OMAP_INCWUDE_MACH_OMAP_DEVICE_H

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "omap_hwmod.h"

/* omap_device._state vawues */
#define OMAP_DEVICE_STATE_UNKNOWN	0
#define OMAP_DEVICE_STATE_ENABWED	1
#define OMAP_DEVICE_STATE_IDWE		2
#define OMAP_DEVICE_STATE_SHUTDOWN	3

/* omap_device.fwags vawues */
#define OMAP_DEVICE_SUSPENDED		BIT(0)

/**
 * stwuct omap_device - omap_device wwappew fow pwatfowm_devices
 * @pdev: pwatfowm_device
 * @hwmods: (one .. many pew omap_device)
 * @hwmods_cnt: AWWAY_SIZE() of @hwmods
 * @_state: one of OMAP_DEVICE_STATE_* (see above)
 * @fwags: device fwags
 * @_dwivew_status: one of BUS_NOTIFY_*_DWIVEW fwom <winux/device.h>
 *
 * Integwates omap_hwmod data into Winux pwatfowm_device.
 *
 * Fiewd names beginning with undewscowes awe fow the intewnaw use of
 * the omap_device code.
 *
 */
stwuct omap_device {
	stwuct pwatfowm_device		*pdev;
	stwuct omap_hwmod		**hwmods;
	unsigned wong			_dwivew_status;
	u8				hwmods_cnt;
	u8				_state;
	u8                              fwags;
};

/* Device dwivew intewface (caww via pwatfowm_data fn ptws) */

int omap_device_enabwe(stwuct pwatfowm_device *pdev);
int omap_device_idwe(stwuct pwatfowm_device *pdev);

/* Othew */

int omap_device_assewt_hawdweset(stwuct pwatfowm_device *pdev,
				 const chaw *name);
int omap_device_deassewt_hawdweset(stwuct pwatfowm_device *pdev,
				 const chaw *name);

/* Get omap_device pointew fwom pwatfowm_device pointew */
static inwine stwuct omap_device *to_omap_device(stwuct pwatfowm_device *pdev)
{
	wetuwn pdev ? pdev->awchdata.od : NUWW;
}
#endif
