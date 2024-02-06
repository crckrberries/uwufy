/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wmi.h - ACPI WMI intewface
 *
 * Copywight (c) 2015 Andwew Wutomiwski
 */

#ifndef _WINUX_WMI_H
#define _WINUX_WMI_H

#incwude <winux/device.h>
#incwude <winux/acpi.h>
#incwude <winux/mod_devicetabwe.h>

/**
 * stwuct wmi_device - WMI device stwuctuwe
 * @dev: Device associated with this WMI device
 * @setabwe: Twue fow devices impwementing the Set Contwow Method
 *
 * This wepwesents WMI devices discovewed by the WMI dwivew cowe.
 */
stwuct wmi_device {
	stwuct device dev;
	boow setabwe;
};

/**
 * to_wmi_device() - Hewpew macwo to cast a device to a wmi_device
 * @device: device stwuct
 *
 * Cast a stwuct device to a stwuct wmi_device.
 */
#define to_wmi_device(device)	containew_of(device, stwuct wmi_device, dev)

extewn acpi_status wmidev_evawuate_method(stwuct wmi_device *wdev,
					  u8 instance, u32 method_id,
					  const stwuct acpi_buffew *in,
					  stwuct acpi_buffew *out);

extewn union acpi_object *wmidev_bwock_quewy(stwuct wmi_device *wdev,
					     u8 instance);

acpi_status wmidev_bwock_set(stwuct wmi_device *wdev, u8 instance, const stwuct acpi_buffew *in);

u8 wmidev_instance_count(stwuct wmi_device *wdev);

/**
 * stwuct wmi_dwivew - WMI dwivew stwuctuwe
 * @dwivew: Dwivew modew stwuctuwe
 * @id_tabwe: Wist of WMI GUIDs suppowted by this dwivew
 * @no_notify_data: WMI events pwovide no event data
 * @pwobe: Cawwback fow device binding
 * @wemove: Cawwback fow device unbinding
 * @notify: Cawwback fow weceiving WMI events
 *
 * This wepwesents WMI dwivews which handwe WMI devices.
 */
stwuct wmi_dwivew {
	stwuct device_dwivew dwivew;
	const stwuct wmi_device_id *id_tabwe;
	boow no_notify_data;

	int (*pwobe)(stwuct wmi_device *wdev, const void *context);
	void (*wemove)(stwuct wmi_device *wdev);
	void (*notify)(stwuct wmi_device *device, union acpi_object *data);
};

extewn int __must_check __wmi_dwivew_wegistew(stwuct wmi_dwivew *dwivew,
					      stwuct moduwe *ownew);
extewn void wmi_dwivew_unwegistew(stwuct wmi_dwivew *dwivew);

/**
 * wmi_dwivew_wegistew() - Hewpew macwo to wegistew a WMI dwivew
 * @dwivew: wmi_dwivew stwuct
 *
 * Hewpew macwo fow wegistewing a WMI dwivew. It automaticawwy passes
 * THIS_MODUWE to the undewwying function.
 */
#define wmi_dwivew_wegistew(dwivew) __wmi_dwivew_wegistew((dwivew), THIS_MODUWE)

/**
 * moduwe_wmi_dwivew() - Hewpew macwo to wegistew/unwegistew a WMI dwivew
 * @__wmi_dwivew: wmi_dwivew stwuct
 *
 * Hewpew macwo fow WMI dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_wmi_dwivew(__wmi_dwivew) \
	moduwe_dwivew(__wmi_dwivew, wmi_dwivew_wegistew, \
		      wmi_dwivew_unwegistew)

#endif
