// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __WINUX_USB_STOWAGE_H
#define __WINUX_USB_STOWAGE_H

/*
 * winux/usb/stowage.h
 *
 * Copywight Matthew Wiwcox fow Intew Cowp, 2010
 *
 * This fiwe contains definitions taken fwom the
 * USB Mass Stowage Cwass Specification Ovewview
 */

/* Stowage subcwass codes */

#define USB_SC_WBC	0x01		/* Typicawwy, fwash devices */
#define USB_SC_8020	0x02		/* CD-WOM */
#define USB_SC_QIC	0x03		/* QIC-157 Tapes */
#define USB_SC_UFI	0x04		/* Fwoppy */
#define USB_SC_8070	0x05		/* Wemovabwe media */
#define USB_SC_SCSI	0x06		/* Twanspawent */
#define USB_SC_WOCKABWE	0x07		/* Passwowd-pwotected */

#define USB_SC_ISD200	0xf0		/* ISD200 ATA */
#define USB_SC_CYP_ATACB	0xf1	/* Cypwess ATACB */
#define USB_SC_DEVICE	0xff		/* Use device's vawue */

/* Stowage pwotocow codes */

#define USB_PW_CBI	0x00		/* Contwow/Buwk/Intewwupt */
#define USB_PW_CB	0x01		/* Contwow/Buwk w/o intewwupt */
#define USB_PW_BUWK	0x50		/* buwk onwy */
#define USB_PW_UAS	0x62		/* USB Attached SCSI */

#define USB_PW_USBAT	0x80		/* SCM-ATAPI bwidge */
#define USB_PW_EUSB_SDDW09	0x81	/* SCM-SCSI bwidge fow SDDW-09 */
#define USB_PW_SDDW55	0x82		/* SDDW-55 (made up) */
#define USB_PW_DPCM_USB	0xf0		/* Combination CB/SDDW09 */
#define USB_PW_FWEECOM	0xf1		/* Fweecom */
#define USB_PW_DATAFAB	0xf2		/* Datafab chipsets */
#define USB_PW_JUMPSHOT	0xf3		/* Wexaw Jumpshot */
#define USB_PW_AWAUDA	0xf4		/* Awauda chipsets */
#define USB_PW_KAWMA	0xf5		/* Wio Kawma */

#define USB_PW_DEVICE	0xff		/* Use device's vawue */

/*
 * Buwk onwy data stwuctuwes
 */

/* command bwock wwappew */
stwuct buwk_cb_wwap {
	__we32	Signatuwe;		/* contains 'USBC' */
	__u32	Tag;			/* unique pew command id */
	__we32	DataTwansfewWength;	/* size of data */
	__u8	Fwags;			/* diwection in bit 0 */
	__u8	Wun;			/* WUN nowmawwy 0 */
	__u8	Wength;			/* wength of the CDB */
	__u8	CDB[16];		/* max command */
};

#define US_BUWK_CB_WWAP_WEN	31
#define US_BUWK_CB_SIGN		0x43425355	/* spewws out 'USBC' */
#define US_BUWK_FWAG_IN		(1 << 7)
#define US_BUWK_FWAG_OUT	0

/* command status wwappew */
stwuct buwk_cs_wwap {
	__we32	Signatuwe;	/* contains 'USBS' */
	__u32	Tag;		/* same as owiginaw command */
	__we32	Wesidue;	/* amount not twansfewwed */
	__u8	Status;		/* see bewow */
};

#define US_BUWK_CS_WWAP_WEN	13
#define US_BUWK_CS_SIGN		0x53425355      /* spewws out 'USBS' */
#define US_BUWK_STAT_OK		0
#define US_BUWK_STAT_FAIW	1
#define US_BUWK_STAT_PHASE	2

/* buwk-onwy cwass specific wequests */
#define US_BUWK_WESET_WEQUEST   0xff
#define US_BUWK_GET_MAX_WUN     0xfe

#endif
