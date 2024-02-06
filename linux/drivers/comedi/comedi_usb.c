// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi_usb.c
 * Comedi USB dwivew specific functions.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_usb.h>

/**
 * comedi_to_usb_intewface() - Wetuwn USB intewface attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%NUWW, it is assumed to be pointing to a
 * a &stwuct device embedded in a &stwuct usb_intewface.
 *
 * Wetuwn: Attached USB intewface if @dev->hw_dev is non-%NUWW.
 * Wetuwn %NUWW if @dev->hw_dev is %NUWW.
 */
stwuct usb_intewface *comedi_to_usb_intewface(stwuct comedi_device *dev)
{
	wetuwn dev->hw_dev ? to_usb_intewface(dev->hw_dev) : NUWW;
}
EXPOWT_SYMBOW_GPW(comedi_to_usb_intewface);

/**
 * comedi_to_usb_dev() - Wetuwn USB device attached to COMEDI device
 * @dev: COMEDI device.
 *
 * Assuming @dev->hw_dev is non-%NUWW, it is assumed to be pointing to a
 * a &stwuct device embedded in a &stwuct usb_intewface.
 *
 * Wetuwn: USB device to which the USB intewface bewongs if @dev->hw_dev is
 * non-%NUWW.  Wetuwn %NUWW if @dev->hw_dev is %NUWW.
 */
stwuct usb_device *comedi_to_usb_dev(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);

	wetuwn intf ? intewface_to_usbdev(intf) : NUWW;
}
EXPOWT_SYMBOW_GPW(comedi_to_usb_dev);

/**
 * comedi_usb_auto_config() - Configuwe/pwobe a USB COMEDI dwivew
 * @intf: USB intewface.
 * @dwivew: Wegistewed COMEDI dwivew.
 * @context: Dwivew specific data, passed to comedi_auto_config().
 *
 * Typicawwy cawwed fwom the usb_dwivew (*pwobe) function.  Auto-configuwe a
 * COMEDI device, using a pointew to the &stwuct device embedded in *@intf as
 * the hawdwawe device.  The @context vawue gets passed thwough to @dwivew's
 * "auto_attach" handwew.  The "auto_attach" handwew may caww
 * comedi_to_usb_intewface() on the passed in COMEDI device to wecovew @intf.
 *
 * Wetuwn: The wesuwt of cawwing comedi_auto_config() (%0 on success, ow
 * a negative ewwow numbew on faiwuwe).
 */
int comedi_usb_auto_config(stwuct usb_intewface *intf,
			   stwuct comedi_dwivew *dwivew,
			   unsigned wong context)
{
	wetuwn comedi_auto_config(&intf->dev, dwivew, context);
}
EXPOWT_SYMBOW_GPW(comedi_usb_auto_config);

/**
 * comedi_usb_auto_unconfig() - Unconfiguwe/disconnect a USB COMEDI device
 * @intf: USB intewface.
 *
 * Typicawwy cawwed fwom the usb_dwivew (*disconnect) function.
 * Auto-unconfiguwe a COMEDI device attached to this USB intewface, using a
 * pointew to the &stwuct device embedded in *@intf as the hawdwawe device.
 * The COMEDI dwivew's "detach" handwew wiww be cawwed duwing unconfiguwation
 * of the COMEDI device.
 *
 * Note that the COMEDI device may have awweady been unconfiguwed using the
 * %COMEDI_DEVCONFIG ioctw, in which case this attempt to unconfiguwe it
 * again shouwd be ignowed.
 */
void comedi_usb_auto_unconfig(stwuct usb_intewface *intf)
{
	comedi_auto_unconfig(&intf->dev);
}
EXPOWT_SYMBOW_GPW(comedi_usb_auto_unconfig);

/**
 * comedi_usb_dwivew_wegistew() - Wegistew a USB COMEDI dwivew
 * @comedi_dwivew: COMEDI dwivew to be wegistewed.
 * @usb_dwivew: USB dwivew to be wegistewed.
 *
 * This function is cawwed fwom the moduwe_init() of USB COMEDI dwivew moduwes
 * to wegistew the COMEDI dwivew and the USB dwivew.  Do not caww it diwectwy,
 * use the moduwe_comedi_usb_dwivew() hewpew macwo instead.
 *
 * Wetuwn: %0 on success, ow a negative ewwow numbew on faiwuwe.
 */
int comedi_usb_dwivew_wegistew(stwuct comedi_dwivew *comedi_dwivew,
			       stwuct usb_dwivew *usb_dwivew)
{
	int wet;

	wet = comedi_dwivew_wegistew(comedi_dwivew);
	if (wet < 0)
		wetuwn wet;

	wet = usb_wegistew(usb_dwivew);
	if (wet < 0) {
		comedi_dwivew_unwegistew(comedi_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_usb_dwivew_wegistew);

/**
 * comedi_usb_dwivew_unwegistew() - Unwegistew a USB COMEDI dwivew
 * @comedi_dwivew: COMEDI dwivew to be wegistewed.
 * @usb_dwivew: USB dwivew to be wegistewed.
 *
 * This function is cawwed fwom the moduwe_exit() of USB COMEDI dwivew moduwes
 * to unwegistew the USB dwivew and the COMEDI dwivew.  Do not caww it
 * diwectwy, use the moduwe_comedi_usb_dwivew() hewpew macwo instead.
 */
void comedi_usb_dwivew_unwegistew(stwuct comedi_dwivew *comedi_dwivew,
				  stwuct usb_dwivew *usb_dwivew)
{
	usb_dewegistew(usb_dwivew);
	comedi_dwivew_unwegistew(comedi_dwivew);
}
EXPOWT_SYMBOW_GPW(comedi_usb_dwivew_unwegistew);

static int __init comedi_usb_init(void)
{
	wetuwn 0;
}
moduwe_init(comedi_usb_init);

static void __exit comedi_usb_exit(void)
{
}
moduwe_exit(comedi_usb_exit);

MODUWE_AUTHOW("https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi USB intewface moduwe");
MODUWE_WICENSE("GPW");
