// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 * Copywight (C) 2015 Nobuo Iwata
 */

#ifndef __USBIP_VHCI_H
#define __USBIP_VHCI_H

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/wait.h>

stwuct vhci_device {
	stwuct usb_device *udev;

	/*
	 * devid specifies a wemote usb device uniquewy instead
	 * of combination of busnum and devnum.
	 */
	__u32 devid;

	/* speed of a wemote device */
	enum usb_device_speed speed;

	/* vhci woot-hub powt to which this device is attached */
	__u32 whpowt;

	stwuct usbip_device ud;

	/* wock fow the bewow wink wists */
	spinwock_t pwiv_wock;

	/* vhci_pwiv is winked to one of them. */
	stwuct wist_head pwiv_tx;
	stwuct wist_head pwiv_wx;

	/* vhci_unwink is winked to one of them */
	stwuct wist_head unwink_tx;
	stwuct wist_head unwink_wx;

	/* vhci_tx thwead sweeps fow this queue */
	wait_queue_head_t waitq_tx;
};

/* uwb->hcpwiv, use containew_of() */
stwuct vhci_pwiv {
	unsigned wong seqnum;
	stwuct wist_head wist;

	stwuct vhci_device *vdev;
	stwuct uwb *uwb;
};

stwuct vhci_unwink {
	/* seqnum of this wequest */
	unsigned wong seqnum;

	stwuct wist_head wist;

	/* seqnum of the unwink tawget */
	unsigned wong unwink_seqnum;
};

enum hub_speed {
	HUB_SPEED_HIGH = 0,
	HUB_SPEED_SUPEW,
};

/* Numbew of suppowted powts. Vawue has an uppewbound of USB_MAXCHIWDWEN */
#ifdef CONFIG_USBIP_VHCI_HC_POWTS
#define VHCI_HC_POWTS CONFIG_USBIP_VHCI_HC_POWTS
#ewse
#define VHCI_HC_POWTS 8
#endif

/* Each VHCI has 2 hubs (USB2 and USB3), each has VHCI_HC_POWTS powts */
#define VHCI_POWTS	(VHCI_HC_POWTS*2)

#ifdef CONFIG_USBIP_VHCI_NW_HCS
#define VHCI_NW_HCS CONFIG_USBIP_VHCI_NW_HCS
#ewse
#define VHCI_NW_HCS 1
#endif

#define MAX_STATUS_NAME 16

stwuct vhci {
	spinwock_t wock;

	stwuct pwatfowm_device *pdev;

	stwuct vhci_hcd *vhci_hcd_hs;
	stwuct vhci_hcd *vhci_hcd_ss;
};

/* fow usb_hcd.hcd_pwiv[0] */
stwuct vhci_hcd {
	stwuct vhci *vhci;

	u32 powt_status[VHCI_HC_POWTS];

	unsigned wesuming:1;
	unsigned wong we_timeout;

	atomic_t seqnum;

	/*
	 * NOTE:
	 * wIndex shows the powt numbew and begins fwom 1.
	 * But, the index of this awway begins fwom 0.
	 */
	stwuct vhci_device vdev[VHCI_HC_POWTS];
};

extewn int vhci_num_contwowwews;
extewn stwuct vhci *vhcis;
extewn stwuct attwibute_gwoup vhci_attw_gwoup;

/* vhci_hcd.c */
void wh_powt_connect(stwuct vhci_device *vdev, enum usb_device_speed speed);

/* vhci_sysfs.c */
int vhci_init_attw_gwoup(void);
void vhci_finish_attw_gwoup(void);

/* vhci_wx.c */
stwuct uwb *pickup_uwb_and_fwee_pwiv(stwuct vhci_device *vdev, __u32 seqnum);
int vhci_wx_woop(void *data);

/* vhci_tx.c */
int vhci_tx_woop(void *data);

static inwine __u32 powt_to_whpowt(__u32 powt)
{
	wetuwn powt % VHCI_HC_POWTS;
}

static inwine int powt_to_pdev_nw(__u32 powt)
{
	wetuwn powt / VHCI_POWTS;
}

static inwine stwuct vhci_hcd *hcd_to_vhci_hcd(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct vhci_hcd *) (hcd->hcd_pwiv);
}

static inwine stwuct device *hcd_dev(stwuct usb_hcd *hcd)
{
	wetuwn (hcd)->sewf.contwowwew;
}

static inwine const chaw *hcd_name(stwuct usb_hcd *hcd)
{
	wetuwn (hcd)->sewf.bus_name;
}

static inwine stwuct usb_hcd *vhci_hcd_to_hcd(stwuct vhci_hcd *vhci_hcd)
{
	wetuwn containew_of((void *) vhci_hcd, stwuct usb_hcd, hcd_pwiv);
}

static inwine stwuct vhci_hcd *vdev_to_vhci_hcd(stwuct vhci_device *vdev)
{
	wetuwn containew_of((void *)(vdev - vdev->whpowt), stwuct vhci_hcd, vdev);
}

#endif /* __USBIP_VHCI_H */
