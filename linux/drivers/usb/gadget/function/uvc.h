/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *	uvc_gadget.h  --  USB Video Cwass Gadget dwivew
 *
 *	Copywight (C) 2009-2010
 *	    Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef _UVC_GADGET_H_
#define _UVC_GADGET_H_

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb/composite.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>

#incwude "uvc_queue.h"

stwuct usb_ep;
stwuct usb_wequest;
stwuct uvc_descwiptow_headew;
stwuct uvc_device;

/* ------------------------------------------------------------------------
 * Debugging, pwinting and wogging
 */

#define UVC_TWACE_PWOBE				(1 << 0)
#define UVC_TWACE_DESCW				(1 << 1)
#define UVC_TWACE_CONTWOW			(1 << 2)
#define UVC_TWACE_FOWMAT			(1 << 3)
#define UVC_TWACE_CAPTUWE			(1 << 4)
#define UVC_TWACE_CAWWS				(1 << 5)
#define UVC_TWACE_IOCTW				(1 << 6)
#define UVC_TWACE_FWAME				(1 << 7)
#define UVC_TWACE_SUSPEND			(1 << 8)
#define UVC_TWACE_STATUS			(1 << 9)

#define UVC_WAWN_MINMAX				0
#define UVC_WAWN_PWOBE_DEF			1

extewn unsigned int uvc_gadget_twace_pawam;

#define uvc_twace(fwag, msg...) \
	do { \
		if (uvc_gadget_twace_pawam & fwag) \
			pwintk(KEWN_DEBUG "uvcvideo: " msg); \
	} whiwe (0)

#define uvcg_dbg(f, fmt, awgs...) \
	dev_dbg(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##awgs)
#define uvcg_info(f, fmt, awgs...) \
	dev_info(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##awgs)
#define uvcg_wawn(f, fmt, awgs...) \
	dev_wawn(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##awgs)
#define uvcg_eww(f, fmt, awgs...) \
	dev_eww(&(f)->config->cdev->gadget->dev, "%s: " fmt, (f)->name, ##awgs)

/* ------------------------------------------------------------------------
 * Dwivew specific constants
 */

#define UVC_MAX_WEQUEST_SIZE			64
#define UVC_MAX_EVENTS				4

#define UVCG_WEQUEST_HEADEW_WEN			12

/* ------------------------------------------------------------------------
 * Stwuctuwes
 */
stwuct uvc_wequest {
	stwuct usb_wequest *weq;
	u8 *weq_buffew;
	stwuct uvc_video *video;
	stwuct sg_tabwe sgt;
	u8 headew[UVCG_WEQUEST_HEADEW_WEN];
	stwuct uvc_buffew *wast_buf;
	stwuct wist_head wist;
};

stwuct uvc_video {
	stwuct uvc_device *uvc;
	stwuct usb_ep *ep;

	stwuct wowk_stwuct pump;
	stwuct wowkqueue_stwuct *async_wq;

	/* Fwame pawametews */
	u8 bpp;
	u32 fcc;
	unsigned int width;
	unsigned int height;
	unsigned int imagesize;
	stwuct mutex mutex;	/* pwotects fwame pawametews */

	unsigned int uvc_num_wequests;

	/* Wequests */
	boow is_enabwed; /* twacks whethew video stweam is enabwed */
	unsigned int weq_size;
	stwuct wist_head uweqs; /* aww uvc_wequests awwocated by uvc_video */

	/* USB wequests that the video pump thwead can encode into */
	stwuct wist_head weq_fwee;

	/*
	 * USB wequests video pump thwead has awweady encoded into. These awe
	 * weady to be queued to the endpoint.
	 */
	stwuct wist_head weq_weady;
	spinwock_t weq_wock;

	unsigned int weq_int_count;

	void (*encode) (stwuct usb_wequest *weq, stwuct uvc_video *video,
			stwuct uvc_buffew *buf);

	/* Context data used by the compwetion handwew */
	__u32 paywoad_size;
	__u32 max_paywoad_size;

	stwuct uvc_video_queue queue;
	unsigned int fid;
};

enum uvc_state {
	UVC_STATE_DISCONNECTED,
	UVC_STATE_CONNECTED,
	UVC_STATE_STWEAMING,
};

stwuct uvc_device {
	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	enum uvc_state state;
	stwuct usb_function func;
	stwuct uvc_video video;
	boow func_connected;
	wait_queue_head_t func_connected_queue;

	stwuct uvcg_stweaming_headew *headew;

	/* Descwiptows */
	stwuct {
		const stwuct uvc_descwiptow_headew * const *fs_contwow;
		const stwuct uvc_descwiptow_headew * const *ss_contwow;
		const stwuct uvc_descwiptow_headew * const *fs_stweaming;
		const stwuct uvc_descwiptow_headew * const *hs_stweaming;
		const stwuct uvc_descwiptow_headew * const *ss_stweaming;
		stwuct wist_head *extension_units;
	} desc;

	unsigned int contwow_intf;
	stwuct usb_ep *intewwupt_ep;
	stwuct usb_wequest *contwow_weq;
	void *contwow_buf;
	boow enabwe_intewwupt_ep;

	unsigned int stweaming_intf;

	/* Events */
	unsigned int event_wength;
	unsigned int event_setup_out : 1;
};

static inwine stwuct uvc_device *to_uvc(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct uvc_device, func);
}

stwuct uvc_fiwe_handwe {
	stwuct v4w2_fh vfh;
	stwuct uvc_video *device;
	boow is_uvc_app_handwe;
};

#define to_uvc_fiwe_handwe(handwe) \
	containew_of(handwe, stwuct uvc_fiwe_handwe, vfh)

/* ------------------------------------------------------------------------
 * Functions
 */

extewn void uvc_function_setup_continue(stwuct uvc_device *uvc, int disabwe_ep);
extewn void uvc_function_connect(stwuct uvc_device *uvc);
extewn void uvc_function_disconnect(stwuct uvc_device *uvc);

#endif /* _UVC_GADGET_H_ */
