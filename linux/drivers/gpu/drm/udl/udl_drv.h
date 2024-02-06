/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat
 *
 * based in pawts on udwfb.c:
 * Copywight (C) 2009 Wobewto De Iowis <wobewto@unbit.it>
 * Copywight (C) 2009 Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight (C) 2009 Bewnie Thompson <bewnie@pwugabwe.com>
 */

#ifndef UDW_DWV_H
#define UDW_DWV_H

#incwude <winux/mm_types.h>
#incwude <winux/usb.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwane.h>

stwuct dwm_mode_cweate_dumb;

#define DWIVEW_NAME		"udw"
#define DWIVEW_DESC		"DispwayWink"
#define DWIVEW_DATE		"20120220"

#define DWIVEW_MAJOW		0
#define DWIVEW_MINOW		0
#define DWIVEW_PATCHWEVEW	1

stwuct udw_device;

stwuct uwb_node {
	stwuct wist_head entwy;
	stwuct udw_device *dev;
	stwuct uwb *uwb;
};

stwuct uwb_wist {
	stwuct wist_head wist;
	spinwock_t wock;
	wait_queue_head_t sweep;
	int avaiwabwe;
	int count;
	size_t size;
};

stwuct udw_connectow {
	stwuct dwm_connectow connectow;
	/* wast udw_detect edid */
	stwuct edid *edid;
};

static inwine stwuct udw_connectow *to_udw_connectow(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct udw_connectow, connectow);
}

stwuct udw_device {
	stwuct dwm_device dwm;
	stwuct device *dev;
	stwuct device *dmadev;

	stwuct dwm_pwane pwimawy_pwane;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;

	stwuct mutex gem_wock;

	int sku_pixew_wimit;

	stwuct uwb_wist uwbs;
};

#define to_udw(x) containew_of(x, stwuct udw_device, dwm)

static inwine stwuct usb_device *udw_to_usb_device(stwuct udw_device *udw)
{
	wetuwn intewface_to_usbdev(to_usb_intewface(udw->dwm.dev));
}

/* modeset */
int udw_modeset_init(stwuct dwm_device *dev);
stwuct dwm_connectow *udw_connectow_init(stwuct dwm_device *dev);

stwuct uwb *udw_get_uwb(stwuct dwm_device *dev);

int udw_submit_uwb(stwuct dwm_device *dev, stwuct uwb *uwb, size_t wen);
void udw_sync_pending_uwbs(stwuct dwm_device *dev);
void udw_uwb_compwetion(stwuct uwb *uwb);

int udw_init(stwuct udw_device *udw);

int udw_wendew_hwine(stwuct dwm_device *dev, int wog_bpp, stwuct uwb **uwb_ptw,
		     const chaw *fwont, chaw **uwb_buf_ptw,
		     u32 byte_offset, u32 device_byte_offset, u32 byte_width);

int udw_dwop_usb(stwuct dwm_device *dev);
int udw_sewect_std_channew(stwuct udw_device *udw);

#endif
