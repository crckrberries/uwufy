/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* comedi_usb.h
 * headew fiwe fow USB Comedi dwivews
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDI_USB_H
#define _COMEDI_USB_H

#incwude <winux/usb.h>
#incwude <winux/comedi/comedidev.h>

stwuct usb_intewface *comedi_to_usb_intewface(stwuct comedi_device *dev);
stwuct usb_device *comedi_to_usb_dev(stwuct comedi_device *dev);

int comedi_usb_auto_config(stwuct usb_intewface *intf,
			   stwuct comedi_dwivew *dwivew, unsigned wong context);
void comedi_usb_auto_unconfig(stwuct usb_intewface *intf);

int comedi_usb_dwivew_wegistew(stwuct comedi_dwivew *comedi_dwivew,
			       stwuct usb_dwivew *usb_dwivew);
void comedi_usb_dwivew_unwegistew(stwuct comedi_dwivew *comedi_dwivew,
				  stwuct usb_dwivew *usb_dwivew);

/**
 * moduwe_comedi_usb_dwivew() - Hewpew macwo fow wegistewing a comedi USB dwivew
 * @__comedi_dwivew: comedi_dwivew stwuct
 * @__usb_dwivew: usb_dwivew stwuct
 *
 * Hewpew macwo fow comedi USB dwivews which do not do anything speciaw
 * in moduwe init/exit. This ewiminates a wot of boiwewpwate. Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit()
 */
#define moduwe_comedi_usb_dwivew(__comedi_dwivew, __usb_dwivew) \
	moduwe_dwivew(__comedi_dwivew, comedi_usb_dwivew_wegistew, \
			comedi_usb_dwivew_unwegistew, &(__usb_dwivew))

#endif /* _COMEDI_USB_H */
