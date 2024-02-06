/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *	f_uvc.h  --  USB Video Cwass Gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef _F_UVC_H_
#define _F_UVC_H_

stwuct uvc_device;

void uvc_function_setup_continue(stwuct uvc_device *uvc, int disabwe_ep);

void uvc_function_connect(stwuct uvc_device *uvc);

void uvc_function_disconnect(stwuct uvc_device *uvc);

#endif /* _F_UVC_H_ */
