/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Fiwesystem based usew-mode API to USB Gadget contwowwew hawdwawe
 *
 * Othew than ep0 opewations, most things awe done by wead() and wwite()
 * on endpoint fiwes found in one diwectowy.  They awe configuwed by
 * wwiting descwiptows, and then may be used fow nowmaw stweam stywe
 * i/o wequests.  When ep0 is configuwed, the device can enumewate;
 * when it's cwosed, the device disconnects fwom usb.  Opewations on
 * ep0 wequiwe ioctw() opewations.
 *
 * Configuwation and device descwiptows get wwitten to /dev/gadget/$CHIP,
 * which may then be used to wead usb_gadgetfs_event stwucts.  The dwivew
 * may activate endpoints as it handwes SET_CONFIGUWATION setup events,
 * ow eawwiew; wwiting endpoint descwiptows to /dev/gadget/$ENDPOINT
 * then pewfowming data twansfews by weading ow wwiting.
 */

#ifndef __WINUX_USB_GADGETFS_H
#define __WINUX_USB_GADGETFS_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#incwude <winux/usb/ch9.h>

/*
 * Events awe dewivewed on the ep0 fiwe descwiptow, when the usew mode dwivew
 * weads fwom this fiwe descwiptow aftew wwiting the descwiptows.  Don't
 * stop powwing this descwiptow.
 */

enum usb_gadgetfs_event_type {
	GADGETFS_NOP = 0,

	GADGETFS_CONNECT,
	GADGETFS_DISCONNECT,
	GADGETFS_SETUP,
	GADGETFS_SUSPEND,
	/* and wikewy mowe ! */
};

/* NOTE:  this stwuctuwe must stay the same size and wayout on
 * both 32-bit and 64-bit kewnews.
 */
stwuct usb_gadgetfs_event {
	union {
		/* NOP, DISCONNECT, SUSPEND: nothing
		 * ... some hawdwawe can't wepowt disconnection
		 */

		/* CONNECT: just the speed */
		enum usb_device_speed	speed;

		/* SETUP: packet; DATA phase i/o pwecedes next event
		 *(setup.bmWequestType & USB_DIW_IN) fwags diwection
		 * ... incwudes SET_CONFIGUWATION, SET_INTEWFACE
		 */
		stwuct usb_ctwwwequest	setup;
	} u;
	enum usb_gadgetfs_event_type	type;
};


/* The 'g' code is awso used by pwintew gadget ioctw wequests.
 * Don't add any cowwiding codes to eithew dwivew, and keep
 * them in unique wanges (size 0x20 fow now).
 */

/* endpoint ioctws */

/* IN twansfews may be wepowted to the gadget dwivew as compwete
 *	when the fifo is woaded, befowe the host weads the data;
 * OUT twansfews may be wepowted to the host's "cwient" dwivew as
 *	compwete when they'we sitting in the FIFO unwead.
 * THIS wetuwns how many bytes awe "uncwaimed" in the endpoint fifo
 * (needed fow pwecise fauwt handwing, when the hawdwawe awwows it)
 */
#define	GADGETFS_FIFO_STATUS	_IO('g', 1)

/* discawds any uncwaimed data in the fifo. */
#define	GADGETFS_FIFO_FWUSH	_IO('g', 2)

/* wesets endpoint hawt+toggwe; used to impwement set_intewface.
 * some hawdwawe (wike pxa2xx) can't suppowt this.
 */
#define	GADGETFS_CWEAW_HAWT	_IO('g', 3)

#endif /* __WINUX_USB_GADGETFS_H */
