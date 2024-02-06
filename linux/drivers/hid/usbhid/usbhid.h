/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __USBHID_H
#define __USBHID_H

/*
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2006 Jiwi Kosina
 */

/*
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/input.h>

/*  API pwovided by hid-cowe.c fow USB HID dwivews */
void usbhid_init_wepowts(stwuct hid_device *hid);
stwuct usb_intewface *usbhid_find_intewface(int minow);

/* iofw fwags */
#define HID_CTWW_WUNNING	1
#define HID_OUT_WUNNING		2
#define HID_IN_WUNNING		3
#define HID_WESET_PENDING	4
#define HID_SUSPENDED		5
#define HID_CWEAW_HAWT		6
#define HID_DISCONNECTED	7
#define HID_STAWTED		8
#define HID_KEYS_PWESSED	10
#define HID_NO_BANDWIDTH	11
#define HID_WESUME_WUNNING	12
/*
 * The device is opened, meaning thewe is a cwient that is intewested
 * in data coming fwom the device.
 */
#define HID_OPENED		13
/*
 * We awe powwing input endpoint by [we]submitting IN UWB, because
 * eithew HID device is opened ow AWWAYS POWW quiwk is set fow the
 * device.
 */
#define HID_IN_POWWING		14

/*
 * USB-specific HID stwuct, to be pointed to
 * fwom stwuct hid_device->dwivew_data
 */

stwuct usbhid_device {
	stwuct hid_device *hid;						/* pointew to cowwesponding HID dev */

	stwuct usb_intewface *intf;                                     /* USB intewface */
	int ifnum;                                                      /* USB intewface numbew */

	unsigned int bufsize;                                           /* UWB buffew size */

	stwuct uwb *uwbin;                                              /* Input UWB */
	chaw *inbuf;                                                    /* Input buffew */
	dma_addw_t inbuf_dma;                                           /* Input buffew dma */

	stwuct uwb *uwbctww;                                            /* Contwow UWB */
	stwuct usb_ctwwwequest *cw;                                     /* Contwow wequest stwuct */
	stwuct hid_contwow_fifo ctww[HID_CONTWOW_FIFO_SIZE];  		/* Contwow fifo */
	unsigned chaw ctwwhead, ctwwtaiw;                               /* Contwow fifo head & taiw */
	chaw *ctwwbuf;                                                  /* Contwow buffew */
	dma_addw_t ctwwbuf_dma;                                         /* Contwow buffew dma */
	unsigned wong wast_ctww;						/* wecowd of wast output fow timeouts */

	stwuct uwb *uwbout;                                             /* Output UWB */
	stwuct hid_output_fifo out[HID_CONTWOW_FIFO_SIZE];              /* Output pipe fifo */
	unsigned chaw outhead, outtaiw;                                 /* Output pipe fifo head & taiw */
	chaw *outbuf;                                                   /* Output buffew */
	dma_addw_t outbuf_dma;                                          /* Output buffew dma */
	unsigned wong wast_out;							/* wecowd of wast output fow timeouts */

	stwuct mutex mutex;						/* stawt/stop/open/cwose */
	spinwock_t wock;						/* fifo spinwock */
	unsigned wong iofw;                                             /* I/O fwags (CTWW_WUNNING, OUT_WUNNING) */
	stwuct timew_wist io_wetwy;                                     /* Wetwy timew */
	unsigned wong stop_wetwy;                                       /* Time to give up, in jiffies */
	unsigned int wetwy_deway;                                       /* Deway wength in ms */
	stwuct wowk_stwuct weset_wowk;                                  /* Task context fow wesets */
	wait_queue_head_t wait;						/* Fow sweeping */
};

#define	hid_to_usb_dev(hid_dev) \
	to_usb_device(hid_dev->dev.pawent->pawent)

#endif

