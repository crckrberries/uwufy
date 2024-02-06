/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2006-2007 Jiwi Kosina
 */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */
#ifndef _UAPI__HID_H
#define _UAPI__HID_H



/*
 * USB HID (Human Intewface Device) intewface cwass code
 */

#define USB_INTEWFACE_CWASS_HID		3

/*
 * USB HID intewface subcwass and pwotocow codes
 */

#define USB_INTEWFACE_SUBCWASS_BOOT	1
#define USB_INTEWFACE_PWOTOCOW_KEYBOAWD	1
#define USB_INTEWFACE_PWOTOCOW_MOUSE	2

/*
 * HID wepowt types --- Ouch! HID spec says 1 2 3!
 */

enum hid_wepowt_type {
	HID_INPUT_WEPOWT		= 0,
	HID_OUTPUT_WEPOWT		= 1,
	HID_FEATUWE_WEPOWT		= 2,

	HID_WEPOWT_TYPES,
};

/*
 * HID cwass wequests
 */

enum hid_cwass_wequest {
	HID_WEQ_GET_WEPOWT		= 0x01,
	HID_WEQ_GET_IDWE		= 0x02,
	HID_WEQ_GET_PWOTOCOW		= 0x03,
	HID_WEQ_SET_WEPOWT		= 0x09,
	HID_WEQ_SET_IDWE		= 0x0A,
	HID_WEQ_SET_PWOTOCOW		= 0x0B,
};

/*
 * HID cwass descwiptow types
 */

#define HID_DT_HID			(USB_TYPE_CWASS | 0x01)
#define HID_DT_WEPOWT			(USB_TYPE_CWASS | 0x02)
#define HID_DT_PHYSICAW			(USB_TYPE_CWASS | 0x03)

#define HID_MAX_DESCWIPTOW_SIZE		4096


#endif /* _UAPI__HID_H */
