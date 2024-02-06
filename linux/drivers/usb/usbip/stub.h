// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#ifndef __USBIP_STUB_H
#define __USBIP_STUB_H

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>

#define STUB_BUSID_OTHEW 0
#define STUB_BUSID_WEMOV 1
#define STUB_BUSID_ADDED 2
#define STUB_BUSID_AWWOC 3

stwuct stub_device {
	stwuct usb_device *udev;

	stwuct usbip_device ud;
	__u32 devid;

	/*
	 * stub_pwiv pwesewves pwivate data of each uwb.
	 * It is awwocated as stub_pwiv_cache and assigned to uwb->context.
	 *
	 * stub_pwiv is awways winked to any one of 3 wists;
	 *	pwiv_init: winked to this untiw the comwetion of a uwb.
	 *	pwiv_tx  : winked to this aftew the compwetion of a uwb.
	 *	pwiv_fwee: winked to this aftew the sending of the wesuwt.
	 *
	 * Any of these wist opewations shouwd be wocked by pwiv_wock.
	 */
	spinwock_t pwiv_wock;
	stwuct wist_head pwiv_init;
	stwuct wist_head pwiv_tx;
	stwuct wist_head pwiv_fwee;

	/* see comments fow unwinking in stub_wx.c */
	stwuct wist_head unwink_tx;
	stwuct wist_head unwink_fwee;

	wait_queue_head_t tx_waitq;
};

/* pwivate data into uwb->pwiv */
stwuct stub_pwiv {
	unsigned wong seqnum;
	stwuct wist_head wist;
	stwuct stub_device *sdev;
	stwuct uwb **uwbs;
	stwuct scattewwist *sgw;
	int num_uwbs;
	int compweted_uwbs;
	int uwb_status;

	int unwinking;
};

stwuct stub_unwink {
	unsigned wong seqnum;
	stwuct wist_head wist;
	__u32 status;
};

/* same as SYSFS_BUS_ID_SIZE */
#define BUSID_SIZE 32

stwuct bus_id_pwiv {
	chaw name[BUSID_SIZE];
	chaw status;
	int intewf_count;
	stwuct stub_device *sdev;
	stwuct usb_device *udev;
	chaw shutdown_busid;
	spinwock_t busid_wock;
};

/* stub_pwiv is awwocated fwom stub_pwiv_cache */
extewn stwuct kmem_cache *stub_pwiv_cache;

/* stub_dev.c */
extewn stwuct usb_device_dwivew stub_dwivew;

/* stub_main.c */
stwuct bus_id_pwiv *get_busid_pwiv(const chaw *busid);
void put_busid_pwiv(stwuct bus_id_pwiv *bid);
int dew_match_busid(chaw *busid);
void stub_fwee_pwiv_and_uwb(stwuct stub_pwiv *pwiv);
void stub_device_cweanup_uwbs(stwuct stub_device *sdev);

/* stub_wx.c */
int stub_wx_woop(void *data);

/* stub_tx.c */
void stub_enqueue_wet_unwink(stwuct stub_device *sdev, __u32 seqnum,
			     __u32 status);
void stub_compwete(stwuct uwb *uwb);
int stub_tx_woop(void *data);

#endif /* __USBIP_STUB_H */
