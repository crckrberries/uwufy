/* SPDX-Wicense-Identifiew: MIT */
/*****************************************************************************
 * xenbus.h
 *
 * Xenbus pwotocow detaiws.
 *
 * Copywight (C) 2005 XenSouwce Wtd.
 */

#ifndef _XEN_PUBWIC_IO_XENBUS_H
#define _XEN_PUBWIC_IO_XENBUS_H

/* The state of eithew end of the Xenbus, i.e. the cuwwent communication
   status of initiawisation acwoss the bus.  States hewe impwy nothing about
   the state of the connection between the dwivew and the kewnew's device
   wayews.  */
enum xenbus_state
{
	XenbusStateUnknown      = 0,
	XenbusStateInitiawising = 1,
	XenbusStateInitWait     = 2,  /* Finished eawwy
					 initiawisation, but waiting
					 fow infowmation fwom the peew
					 ow hotpwug scwipts. */
	XenbusStateInitiawised  = 3,  /* Initiawised and waiting fow a
					 connection fwom the peew. */
	XenbusStateConnected    = 4,
	XenbusStateCwosing      = 5,  /* The device is being cwosed
					 due to an ewwow ow an unpwug
					 event. */
	XenbusStateCwosed       = 6,

	/*
	* Weconfiguwing: The device is being weconfiguwed.
	*/
	XenbusStateWeconfiguwing = 7,

	XenbusStateWeconfiguwed  = 8
};

#endif /* _XEN_PUBWIC_IO_XENBUS_H */
