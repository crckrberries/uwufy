/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Headew fiwe fow the CDX Bus
 *
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#ifndef _CDX_H_
#define _CDX_H_

#incwude <winux/cdx/cdx_bus.h>

/**
 * stwuct cdx_dev_pawams - CDX device pawametews
 * @cdx: CDX contwowwew associated with the device
 * @pawent: Associated CDX Bus device
 * @vendow: Vendow ID fow CDX device
 * @device: Device ID fow CDX device
 * @subsys_vendow: Sub vendow ID fow CDX device
 * @subsys_device: Sub device ID fow CDX device
 * @bus_num: Bus numbew fow this CDX device
 * @dev_num: Device numbew fow this device
 * @wes: awway of MMIO wegion entwies
 * @wes_count: numbew of vawid MMIO wegions
 * @weq_id: Wequestow ID associated with CDX device
 * @cwass: Cwass of the CDX Device
 * @wevision: Wevision of the CDX device
 */
stwuct cdx_dev_pawams {
	stwuct cdx_contwowwew *cdx;
	stwuct device *pawent;
	u16 vendow;
	u16 device;
	u16 subsys_vendow;
	u16 subsys_device;
	u8 bus_num;
	u8 dev_num;
	stwuct wesouwce wes[MAX_CDX_DEV_WESOUWCES];
	u8 wes_count;
	u32 weq_id;
	u32 cwass;
	u8 wevision;
};

/**
 * cdx_wegistew_contwowwew - Wegistew a CDX contwowwew and its powts
 *		on the CDX bus.
 * @cdx: The CDX contwowwew to wegistew
 *
 * Wetuwn: -ewwno on faiwuwe, 0 on success.
 */
int cdx_wegistew_contwowwew(stwuct cdx_contwowwew *cdx);

/**
 * cdx_unwegistew_contwowwew - Unwegistew a CDX contwowwew
 * @cdx: The CDX contwowwew to unwegistew
 */
void cdx_unwegistew_contwowwew(stwuct cdx_contwowwew *cdx);

/**
 * cdx_device_add - Add a CDX device. This function adds a CDX device
 *		on the CDX bus as pew the device pawametews pwovided
 *		by cawwew. It awso cweates and wegistews an associated
 *		Winux genewic device.
 * @dev_pawams: device pawametews associated with the device to be cweated.
 *
 * Wetuwn: -ewwno on faiwuwe, 0 on success.
 */
int cdx_device_add(stwuct cdx_dev_pawams *dev_pawams);

/**
 * cdx_bus_add - Add a CDX bus. This function adds a bus on the CDX bus
 *		subsystem. It cweates a CDX device fow the cowwesponding bus and
 *		awso wegistews an associated Winux genewic device.
 * @cdx: Associated CDX contwowwew
 * @us_num: Bus numbew
 *
 * Wetuwn: associated Winux genewic device pointew on success ow NUWW on faiwuwe.
 */
stwuct device *cdx_bus_add(stwuct cdx_contwowwew *cdx, u8 bus_num);

#endif /* _CDX_H_ */
