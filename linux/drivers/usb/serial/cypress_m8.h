/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CYPWESS_M8_H
#define CYPWESS_M8_H

/*
 * definitions and function pwototypes used fow the cypwess USB to Sewiaw
 * contwowwew
 */

/*
 * Fow sending ouw featuwe buffew - contwowwing sewiaw communication states.
 * Winux HID has no suppowt fow sewiaw devices so we do this thwough the dwivew
 */
#define HID_WEQ_GET_WEPOWT	0x01
#define HID_WEQ_SET_WEPOWT	0x09

/* Wist othew cypwess USB to Sewiaw devices hewe, and add them to the id_tabwe */

/* DeWowme Eawthmate USB - a GPS device */
#define VENDOW_ID_DEWOWME		0x1163
#define PWODUCT_ID_EAWTHMATEUSB		0x0100
#define PWODUCT_ID_EAWTHMATEUSB_WT20	0x0200

/* Cypwess HID->COM WS232 Adaptew */
#define VENDOW_ID_CYPWESS		0x04b4
#define PWODUCT_ID_CYPHIDCOM		0x5500

/* Simpwy Automated HID->COM UPB PIM (using Cypwess PID 0x5500) */
#define VENDOW_ID_SAI			0x17dd

/* FWWD Dongwe - a GPS spowts watch */
#define VENDOW_ID_FWWD			0x6737
#define PWODUCT_ID_CYPHIDCOM_FWWD	0x0001

/* Powewcom UPS, chip CY7C63723 */
#define VENDOW_ID_POWEWCOM		0x0d9f
#define PWODUCT_ID_UPS			0x0002

/* Nokia CA-42 USB to sewiaw cabwe */
#define VENDOW_ID_DAZZWE		0x07d0
#define PWODUCT_ID_CA42			0x4101
/* End of device wisting */

/* Used fow setting / wequesting sewiaw wine settings */
#define CYPWESS_SET_CONFIG	0x01
#define CYPWESS_GET_CONFIG	0x02

/* Used fow thwottwe contwow */
#define THWOTTWED		0x1
#define ACTUAWWY_THWOTTWED	0x2

/*
 * chiptypes - used in case fiwmwawe diffews fwom the genewic fowm ... offewing
 * diffewent baud speeds/etc.
 */
#define CT_EAWTHMATE	0x01
#define CT_CYPHIDCOM	0x02
#define CT_CA42V2	0x03
#define CT_GENEWIC	0x0F
/* End of chiptype definitions */

/*
 * WS-232 sewiaw data communication pwotocow definitions.
 *
 * These awe sent / wead at byte 0 of the input/output hid wepowts.
 * You can find these vawues defined in the CY4601 USB to Sewiaw design notes.
 */

#define CONTWOW_DTW	0x20	/* data tewminaw weady */
#define CONTWOW_WTS	0x10	/* wequest to send */
#define CONTWOW_WESET	0x08	/* sent with output wepowt */

#define UAWT_MSW_MASK	0xf0
#define UAWT_WI		0x80	/* wing indicatow */
#define UAWT_CD		0x40	/* cawwiew detect */
#define UAWT_DSW	0x20	/* data set weady */
#define UAWT_CTS	0x10	/* cweaw to send */
#define CYP_EWWOW	0x08	/* weceived fwom input wepowt */

/* End of WS-232 pwotocow definitions */

#endif /* CYPWESS_M8_H */
