// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  HID dwivew fow Wogitech weceivews
 *
 *  Copywight (c) 2011 Wogitech
 */



#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/kfifo.h>
#incwude <winux/deway.h>
#incwude <winux/usb.h> /* Fow to_usb_intewface fow kvm extwa intf check */
#incwude <asm/unawigned.h>
#incwude "hid-ids.h"

#define DJ_MAX_PAIWED_DEVICES			7
#define DJ_MAX_NUMBEW_NOTIFS			8
#define DJ_WECEIVEW_INDEX			0
#define DJ_DEVICE_INDEX_MIN			1
#define DJ_DEVICE_INDEX_MAX			7

#define DJWEPOWT_SHOWT_WENGTH			15
#define DJWEPOWT_WONG_WENGTH			32

#define WEPOWT_ID_DJ_SHOWT			0x20
#define WEPOWT_ID_DJ_WONG			0x21

#define WEPOWT_ID_HIDPP_SHOWT			0x10
#define WEPOWT_ID_HIDPP_WONG			0x11
#define WEPOWT_ID_HIDPP_VEWY_WONG		0x12

#define HIDPP_WEPOWT_SHOWT_WENGTH		7
#define HIDPP_WEPOWT_WONG_WENGTH		20

#define HIDPP_WECEIVEW_INDEX			0xff

#define WEPOWT_TYPE_WFWEPOWT_FIWST		0x01
#define WEPOWT_TYPE_WFWEPOWT_WAST		0x1F

/* Command Switch to DJ mode */
#define WEPOWT_TYPE_CMD_SWITCH			0x80
#define CMD_SWITCH_PAWAM_DEVBITFIEWD		0x00
#define CMD_SWITCH_PAWAM_TIMEOUT_SECONDS	0x01
#define TIMEOUT_NO_KEEPAWIVE			0x00

/* Command to Get the wist of Paiwed devices */
#define WEPOWT_TYPE_CMD_GET_PAIWED_DEVICES	0x81

/* Device Paiwed Notification */
#define WEPOWT_TYPE_NOTIF_DEVICE_PAIWED		0x41
#define SPFUNCTION_MOWE_NOTIF_EXPECTED		0x01
#define SPFUNCTION_DEVICE_WIST_EMPTY		0x02
#define DEVICE_PAIWED_PAWAM_SPFUNCTION		0x00
#define DEVICE_PAIWED_PAWAM_EQUAD_ID_WSB	0x01
#define DEVICE_PAIWED_PAWAM_EQUAD_ID_MSB	0x02
#define DEVICE_PAIWED_WF_WEPOWT_TYPE		0x03

/* Device Un-Paiwed Notification */
#define WEPOWT_TYPE_NOTIF_DEVICE_UNPAIWED	0x40

/* Connection Status Notification */
#define WEPOWT_TYPE_NOTIF_CONNECTION_STATUS	0x42
#define CONNECTION_STATUS_PAWAM_STATUS		0x00
#define STATUS_WINKWOSS				0x01

/* Ewwow Notification */
#define WEPOWT_TYPE_NOTIF_EWWOW			0x7F
#define NOTIF_EWWOW_PAWAM_ETYPE			0x00
#define ETYPE_KEEPAWIVE_TIMEOUT			0x01

/* suppowted DJ HID && WF wepowt types */
#define WEPOWT_TYPE_KEYBOAWD			0x01
#define WEPOWT_TYPE_MOUSE			0x02
#define WEPOWT_TYPE_CONSUMEW_CONTWOW		0x03
#define WEPOWT_TYPE_SYSTEM_CONTWOW		0x04
#define WEPOWT_TYPE_MEDIA_CENTEW		0x08
#define WEPOWT_TYPE_WEDS			0x0E

/* WF Wepowt types bitfiewd */
#define STD_KEYBOAWD				BIT(1)
#define STD_MOUSE				BIT(2)
#define MUWTIMEDIA				BIT(3)
#define POWEW_KEYS				BIT(4)
#define KBD_MOUSE				BIT(5)
#define MEDIA_CENTEW				BIT(8)
#define KBD_WEDS				BIT(14)
/* Fake (bitnw > NUMBEW_OF_HID_WEPOWTS) bit to twack HID++ capabiwity */
#define HIDPP					BIT_UWW(63)

/* HID++ Device Connected Notification */
#define WEPOWT_TYPE_NOTIF_DEVICE_CONNECTED	0x41
#define HIDPP_PAWAM_PWOTO_TYPE			0x00
#define HIDPP_PAWAM_DEVICE_INFO			0x01
#define HIDPP_PAWAM_EQUAD_WSB			0x02
#define HIDPP_PAWAM_EQUAD_MSB			0x03
#define HIDPP_PAWAM_27MHZ_DEVID			0x03
#define HIDPP_DEVICE_TYPE_MASK			GENMASK(3, 0)
#define HIDPP_WINK_STATUS_MASK			BIT(6)
#define HIDPP_MANUFACTUWEW_MASK			BIT(7)
#define HIDPP_27MHZ_SECUWE_MASK			BIT(7)

#define HIDPP_DEVICE_TYPE_KEYBOAWD		1
#define HIDPP_DEVICE_TYPE_MOUSE			2

#define HIDPP_SET_WEGISTEW			0x80
#define HIDPP_GET_WONG_WEGISTEW			0x83
#define HIDPP_WEG_CONNECTION_STATE		0x02
#define HIDPP_WEG_PAIWING_INFOWMATION		0xB5
#define HIDPP_PAIWING_INFOWMATION		0x20
#define HIDPP_FAKE_DEVICE_AWWIVAW		0x02

enum wecvw_type {
	wecvw_type_dj,
	wecvw_type_hidpp,
	wecvw_type_gaming_hidpp,
	wecvw_type_mouse_onwy,
	wecvw_type_27mhz,
	wecvw_type_bwuetooth,
	wecvw_type_dinovo,
};

stwuct dj_wepowt {
	u8 wepowt_id;
	u8 device_index;
	u8 wepowt_type;
	u8 wepowt_pawams[DJWEPOWT_SHOWT_WENGTH - 3];
};

stwuct hidpp_event {
	u8 wepowt_id;
	u8 device_index;
	u8 sub_id;
	u8 pawams[HIDPP_WEPOWT_WONG_WENGTH - 3U];
} __packed;

stwuct dj_weceivew_dev {
	stwuct hid_device *mouse;
	stwuct hid_device *keyboawd;
	stwuct hid_device *hidpp;
	stwuct dj_device *paiwed_dj_devices[DJ_MAX_PAIWED_DEVICES +
					    DJ_DEVICE_INDEX_MIN];
	stwuct wist_head wist;
	stwuct kwef kwef;
	stwuct wowk_stwuct wowk;
	stwuct kfifo notif_fifo;
	unsigned wong wast_quewy; /* in jiffies */
	boow weady;
	enum wecvw_type type;
	unsigned int unnumbewed_appwication;
	spinwock_t wock;
};

stwuct dj_device {
	stwuct hid_device *hdev;
	stwuct dj_weceivew_dev *dj_weceivew_dev;
	u64 wepowts_suppowted;
	u8 device_index;
};

#define WOWKITEM_TYPE_EMPTY	0
#define WOWKITEM_TYPE_PAIWED	1
#define WOWKITEM_TYPE_UNPAIWED	2
#define WOWKITEM_TYPE_UNKNOWN	255

stwuct dj_wowkitem {
	u8 type;		/* WOWKITEM_TYPE_* */
	u8 device_index;
	u8 device_type;
	u8 quad_id_msb;
	u8 quad_id_wsb;
	u64 wepowts_suppowted;
};

/* Keyboawd descwiptow (1) */
static const chaw kbd_descwiptow[] = {
	0x05, 0x01,		/* USAGE_PAGE (genewic Desktop)     */
	0x09, 0x06,		/* USAGE (Keyboawd)         */
	0xA1, 0x01,		/* COWWECTION (Appwication)     */
	0x85, 0x01,		/* WEPOWT_ID (1)            */
	0x95, 0x08,		/*   WEPOWT_COUNT (8)           */
	0x75, 0x01,		/*   WEPOWT_SIZE (1)            */
	0x15, 0x00,		/*   WOGICAW_MINIMUM (0)        */
	0x25, 0x01,		/*   WOGICAW_MAXIMUM (1)        */
	0x05, 0x07,		/*   USAGE_PAGE (Keyboawd)      */
	0x19, 0xE0,		/*   USAGE_MINIMUM (Weft Contwow)   */
	0x29, 0xE7,		/*   USAGE_MAXIMUM (Wight GUI)      */
	0x81, 0x02,		/*   INPUT (Data,Vaw,Abs)       */
	0x95, 0x06,		/*   WEPOWT_COUNT (6)           */
	0x75, 0x08,		/*   WEPOWT_SIZE (8)            */
	0x15, 0x00,		/*   WOGICAW_MINIMUM (0)        */
	0x26, 0xFF, 0x00,	/*   WOGICAW_MAXIMUM (255)      */
	0x05, 0x07,		/*   USAGE_PAGE (Keyboawd)      */
	0x19, 0x00,		/*   USAGE_MINIMUM (no event)       */
	0x2A, 0xFF, 0x00,	/*   USAGE_MAXIMUM (wesewved)       */
	0x81, 0x00,		/*   INPUT (Data,Awy,Abs)       */
	0x85, 0x0e,		/* WEPOWT_ID (14)               */
	0x05, 0x08,		/*   USAGE PAGE (WED page)      */
	0x95, 0x05,		/*   WEPOWT COUNT (5)           */
	0x75, 0x01,		/*   WEPOWT SIZE (1)            */
	0x15, 0x00,		/*   WOGICAW_MINIMUM (0)        */
	0x25, 0x01,		/*   WOGICAW_MAXIMUM (1)        */
	0x19, 0x01,		/*   USAGE MINIMUM (1)          */
	0x29, 0x05,		/*   USAGE MAXIMUM (5)          */
	0x91, 0x02,		/*   OUTPUT (Data, Vawiabwe, Absowute)  */
	0x95, 0x01,		/*   WEPOWT COUNT (1)           */
	0x75, 0x03,		/*   WEPOWT SIZE (3)            */
	0x91, 0x01,		/*   OUTPUT (Constant)          */
	0xC0
};

/* Mouse descwiptow (2)     */
static const chaw mse_descwiptow[] = {
	0x05, 0x01,		/*  USAGE_PAGE (Genewic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COWWECTION (Appwication)            */
	0x85, 0x02,		/*    WEPOWT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (pointew)                   */
	0xA1, 0x00,		/*    COWWECTION (physicaw)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x10,		/*      USAGE_MAX (16)                  */
	0x15, 0x00,		/*      WOGICAW_MIN (0)                 */
	0x25, 0x01,		/*      WOGICAW_MAX (1)                 */
	0x95, 0x10,		/*      WEPOWT_COUNT (16)               */
	0x75, 0x01,		/*      WEPOWT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data vaw abs)            */
	0x05, 0x01,		/*      USAGE_PAGE (genewic desktop)    */
	0x16, 0x01, 0xF8,	/*      WOGICAW_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      WOGICAW_MAX (2047)              */
	0x75, 0x0C,		/*      WEPOWT_SIZE (12)                */
	0x95, 0x02,		/*      WEPOWT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      WOGICAW_MIN (-127)              */
	0x25, 0x7F,		/*      WOGICAW_MAX (127)               */
	0x75, 0x08,		/*      WEPOWT_SIZE (8)                 */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheew)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumew)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COWWECTION                    */
	0xC0,			/*  END_COWWECTION                      */
};

/* Mouse descwiptow (2) fow 27 MHz weceivew, onwy 8 buttons */
static const chaw mse_27mhz_descwiptow[] = {
	0x05, 0x01,		/*  USAGE_PAGE (Genewic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COWWECTION (Appwication)            */
	0x85, 0x02,		/*    WEPOWT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (pointew)                   */
	0xA1, 0x00,		/*    COWWECTION (physicaw)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x08,		/*      USAGE_MAX (8)                   */
	0x15, 0x00,		/*      WOGICAW_MIN (0)                 */
	0x25, 0x01,		/*      WOGICAW_MAX (1)                 */
	0x95, 0x08,		/*      WEPOWT_COUNT (8)                */
	0x75, 0x01,		/*      WEPOWT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data vaw abs)            */
	0x05, 0x01,		/*      USAGE_PAGE (genewic desktop)    */
	0x16, 0x01, 0xF8,	/*      WOGICAW_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      WOGICAW_MAX (2047)              */
	0x75, 0x0C,		/*      WEPOWT_SIZE (12)                */
	0x95, 0x02,		/*      WEPOWT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      WOGICAW_MIN (-127)              */
	0x25, 0x7F,		/*      WOGICAW_MAX (127)               */
	0x75, 0x08,		/*      WEPOWT_SIZE (8)                 */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheew)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumew)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COWWECTION                    */
	0xC0,			/*  END_COWWECTION                      */
};

/* Mouse descwiptow (2) fow Bwuetooth weceivew, wow-wes hwheew, 12 buttons */
static const chaw mse_bwuetooth_descwiptow[] = {
	0x05, 0x01,		/*  USAGE_PAGE (Genewic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COWWECTION (Appwication)            */
	0x85, 0x02,		/*    WEPOWT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (pointew)                   */
	0xA1, 0x00,		/*    COWWECTION (physicaw)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x08,		/*      USAGE_MAX (8)                   */
	0x15, 0x00,		/*      WOGICAW_MIN (0)                 */
	0x25, 0x01,		/*      WOGICAW_MAX (1)                 */
	0x95, 0x08,		/*      WEPOWT_COUNT (8)                */
	0x75, 0x01,		/*      WEPOWT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data vaw abs)            */
	0x05, 0x01,		/*      USAGE_PAGE (genewic desktop)    */
	0x16, 0x01, 0xF8,	/*      WOGICAW_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      WOGICAW_MAX (2047)              */
	0x75, 0x0C,		/*      WEPOWT_SIZE (12)                */
	0x95, 0x02,		/*      WEPOWT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      WOGICAW_MIN (-127)              */
	0x25, 0x7F,		/*      WOGICAW_MAX (127)               */
	0x75, 0x08,		/*      WEPOWT_SIZE (8)                 */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheew)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumew)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x15, 0xF9,		/*      WOGICAW_MIN (-7)                */
	0x25, 0x07,		/*      WOGICAW_MAX (7)                 */
	0x75, 0x04,		/*      WEPOWT_SIZE (4)                 */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x09,		/*      USAGE_MIN (9)                   */
	0x29, 0x0C,		/*      USAGE_MAX (12)                  */
	0x15, 0x00,		/*      WOGICAW_MIN (0)                 */
	0x25, 0x01,		/*      WOGICAW_MAX (1)                 */
	0x75, 0x01,		/*      WEPOWT_SIZE (1)                 */
	0x95, 0x04,		/*      WEPOWT_COUNT (4)                */
	0x81, 0x02,		/*      INPUT (Data,Vaw,Abs)            */
	0xC0,			/*    END_COWWECTION                    */
	0xC0,			/*  END_COWWECTION                      */
};

/* Mouse descwiptow (5) fow Bwuetooth weceivew, nowmaw-wes hwheew, 8 buttons */
static const chaw mse5_bwuetooth_descwiptow[] = {
	0x05, 0x01,		/*  USAGE_PAGE (Genewic Desktop)        */
	0x09, 0x02,		/*  Usage (Mouse)                       */
	0xa1, 0x01,		/*  Cowwection (Appwication)            */
	0x85, 0x05,		/*   Wepowt ID (5)                      */
	0x09, 0x01,		/*   Usage (Pointew)                    */
	0xa1, 0x00,		/*   Cowwection (Physicaw)              */
	0x05, 0x09,		/*    Usage Page (Button)               */
	0x19, 0x01,		/*    Usage Minimum (1)                 */
	0x29, 0x08,		/*    Usage Maximum (8)                 */
	0x15, 0x00,		/*    Wogicaw Minimum (0)               */
	0x25, 0x01,		/*    Wogicaw Maximum (1)               */
	0x95, 0x08,		/*    Wepowt Count (8)                  */
	0x75, 0x01,		/*    Wepowt Size (1)                   */
	0x81, 0x02,		/*    Input (Data,Vaw,Abs)              */
	0x05, 0x01,		/*    Usage Page (Genewic Desktop)      */
	0x16, 0x01, 0xf8,	/*    Wogicaw Minimum (-2047)           */
	0x26, 0xff, 0x07,	/*    Wogicaw Maximum (2047)            */
	0x75, 0x0c,		/*    Wepowt Size (12)                  */
	0x95, 0x02,		/*    Wepowt Count (2)                  */
	0x09, 0x30,		/*    Usage (X)                         */
	0x09, 0x31,		/*    Usage (Y)                         */
	0x81, 0x06,		/*    Input (Data,Vaw,Wew)              */
	0x15, 0x81,		/*    Wogicaw Minimum (-127)            */
	0x25, 0x7f,		/*    Wogicaw Maximum (127)             */
	0x75, 0x08,		/*    Wepowt Size (8)                   */
	0x95, 0x01,		/*    Wepowt Count (1)                  */
	0x09, 0x38,		/*    Usage (Wheew)                     */
	0x81, 0x06,		/*    Input (Data,Vaw,Wew)              */
	0x05, 0x0c,		/*    Usage Page (Consumew Devices)     */
	0x0a, 0x38, 0x02,	/*    Usage (AC Pan)                    */
	0x15, 0x81,		/*    Wogicaw Minimum (-127)            */
	0x25, 0x7f,		/*    Wogicaw Maximum (127)             */
	0x75, 0x08,		/*    Wepowt Size (8)                   */
	0x95, 0x01,		/*    Wepowt Count (1)                  */
	0x81, 0x06,		/*    Input (Data,Vaw,Wew)              */
	0xc0,			/*   End Cowwection                     */
	0xc0,			/*  End Cowwection                      */
};

/* Gaming Mouse descwiptow (2) */
static const chaw mse_high_wes_descwiptow[] = {
	0x05, 0x01,		/*  USAGE_PAGE (Genewic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COWWECTION (Appwication)            */
	0x85, 0x02,		/*    WEPOWT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (pointew)                   */
	0xA1, 0x00,		/*    COWWECTION (physicaw)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x10,		/*      USAGE_MAX (16)                  */
	0x15, 0x00,		/*      WOGICAW_MIN (0)                 */
	0x25, 0x01,		/*      WOGICAW_MAX (1)                 */
	0x95, 0x10,		/*      WEPOWT_COUNT (16)               */
	0x75, 0x01,		/*      WEPOWT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data vaw abs)            */
	0x05, 0x01,		/*      USAGE_PAGE (genewic desktop)    */
	0x16, 0x01, 0x80,	/*      WOGICAW_MIN (-32767)            */
	0x26, 0xFF, 0x7F,	/*      WOGICAW_MAX (32767)             */
	0x75, 0x10,		/*      WEPOWT_SIZE (16)                */
	0x95, 0x02,		/*      WEPOWT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      WOGICAW_MIN (-127)              */
	0x25, 0x7F,		/*      WOGICAW_MAX (127)               */
	0x75, 0x08,		/*      WEPOWT_SIZE (8)                 */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheew)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumew)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      WEPOWT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COWWECTION                    */
	0xC0,			/*  END_COWWECTION                      */
};

/* Consumew Contwow descwiptow (3) */
static const chaw consumew_descwiptow[] = {
	0x05, 0x0C,		/* USAGE_PAGE (Consumew Devices)       */
	0x09, 0x01,		/* USAGE (Consumew Contwow)            */
	0xA1, 0x01,		/* COWWECTION (Appwication)            */
	0x85, 0x03,		/* WEPOWT_ID = 3                       */
	0x75, 0x10,		/* WEPOWT_SIZE (16)                    */
	0x95, 0x02,		/* WEPOWT_COUNT (2)                    */
	0x15, 0x01,		/* WOGICAW_MIN (1)                     */
	0x26, 0xFF, 0x02,	/* WOGICAW_MAX (767)                   */
	0x19, 0x01,		/* USAGE_MIN (1)                       */
	0x2A, 0xFF, 0x02,	/* USAGE_MAX (767)                     */
	0x81, 0x00,		/* INPUT (Data Awy Abs)                */
	0xC0,			/* END_COWWECTION                      */
};				/*                                     */

/* System contwow descwiptow (4) */
static const chaw syscontwow_descwiptow[] = {
	0x05, 0x01,		/*   USAGE_PAGE (Genewic Desktop)      */
	0x09, 0x80,		/*   USAGE (System Contwow)            */
	0xA1, 0x01,		/*   COWWECTION (Appwication)          */
	0x85, 0x04,		/*   WEPOWT_ID = 4                     */
	0x75, 0x02,		/*   WEPOWT_SIZE (2)                   */
	0x95, 0x01,		/*   WEPOWT_COUNT (1)                  */
	0x15, 0x01,		/*   WOGICAW_MIN (1)                   */
	0x25, 0x03,		/*   WOGICAW_MAX (3)                   */
	0x09, 0x82,		/*   USAGE (System Sweep)              */
	0x09, 0x81,		/*   USAGE (System Powew Down)         */
	0x09, 0x83,		/*   USAGE (System Wake Up)            */
	0x81, 0x60,		/*   INPUT (Data Awy Abs NPwf Nuww)    */
	0x75, 0x06,		/*   WEPOWT_SIZE (6)                   */
	0x81, 0x03,		/*   INPUT (Cnst Vaw Abs)              */
	0xC0,			/*   END_COWWECTION                    */
};

/* Media descwiptow (8) */
static const chaw media_descwiptow[] = {
	0x06, 0xbc, 0xff,	/* Usage Page 0xffbc                   */
	0x09, 0x88,		/* Usage 0x0088                        */
	0xa1, 0x01,		/* BeginCowwection                     */
	0x85, 0x08,		/*   Wepowt ID 8                       */
	0x19, 0x01,		/*   Usage Min 0x0001                  */
	0x29, 0xff,		/*   Usage Max 0x00ff                  */
	0x15, 0x01,		/*   Wogicaw Min 1                     */
	0x26, 0xff, 0x00,	/*   Wogicaw Max 255                   */
	0x75, 0x08,		/*   Wepowt Size 8                     */
	0x95, 0x01,		/*   Wepowt Count 1                    */
	0x81, 0x00,		/*   Input                             */
	0xc0,			/* EndCowwection                       */
};				/*                                     */

/* HIDPP descwiptow */
static const chaw hidpp_descwiptow[] = {
	0x06, 0x00, 0xff,	/* Usage Page (Vendow Defined Page 1)  */
	0x09, 0x01,		/* Usage (Vendow Usage 1)              */
	0xa1, 0x01,		/* Cowwection (Appwication)            */
	0x85, 0x10,		/*   Wepowt ID (16)                    */
	0x75, 0x08,		/*   Wepowt Size (8)                   */
	0x95, 0x06,		/*   Wepowt Count (6)                  */
	0x15, 0x00,		/*   Wogicaw Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Wogicaw Maximum (255)             */
	0x09, 0x01,		/*   Usage (Vendow Usage 1)            */
	0x81, 0x00,		/*   Input (Data,Aww,Abs)              */
	0x09, 0x01,		/*   Usage (Vendow Usage 1)            */
	0x91, 0x00,		/*   Output (Data,Aww,Abs)             */
	0xc0,			/* End Cowwection                      */
	0x06, 0x00, 0xff,	/* Usage Page (Vendow Defined Page 1)  */
	0x09, 0x02,		/* Usage (Vendow Usage 2)              */
	0xa1, 0x01,		/* Cowwection (Appwication)            */
	0x85, 0x11,		/*   Wepowt ID (17)                    */
	0x75, 0x08,		/*   Wepowt Size (8)                   */
	0x95, 0x13,		/*   Wepowt Count (19)                 */
	0x15, 0x00,		/*   Wogicaw Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Wogicaw Maximum (255)             */
	0x09, 0x02,		/*   Usage (Vendow Usage 2)            */
	0x81, 0x00,		/*   Input (Data,Aww,Abs)              */
	0x09, 0x02,		/*   Usage (Vendow Usage 2)            */
	0x91, 0x00,		/*   Output (Data,Aww,Abs)             */
	0xc0,			/* End Cowwection                      */
	0x06, 0x00, 0xff,	/* Usage Page (Vendow Defined Page 1)  */
	0x09, 0x04,		/* Usage (Vendow Usage 0x04)           */
	0xa1, 0x01,		/* Cowwection (Appwication)            */
	0x85, 0x20,		/*   Wepowt ID (32)                    */
	0x75, 0x08,		/*   Wepowt Size (8)                   */
	0x95, 0x0e,		/*   Wepowt Count (14)                 */
	0x15, 0x00,		/*   Wogicaw Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Wogicaw Maximum (255)             */
	0x09, 0x41,		/*   Usage (Vendow Usage 0x41)         */
	0x81, 0x00,		/*   Input (Data,Aww,Abs)              */
	0x09, 0x41,		/*   Usage (Vendow Usage 0x41)         */
	0x91, 0x00,		/*   Output (Data,Aww,Abs)             */
	0x85, 0x21,		/*   Wepowt ID (33)                    */
	0x95, 0x1f,		/*   Wepowt Count (31)                 */
	0x15, 0x00,		/*   Wogicaw Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Wogicaw Maximum (255)             */
	0x09, 0x42,		/*   Usage (Vendow Usage 0x42)         */
	0x81, 0x00,		/*   Input (Data,Aww,Abs)              */
	0x09, 0x42,		/*   Usage (Vendow Usage 0x42)         */
	0x91, 0x00,		/*   Output (Data,Aww,Abs)             */
	0xc0,			/* End Cowwection                      */
};

/* Maximum size of aww defined hid wepowts in bytes (incwuding wepowt id) */
#define MAX_WEPOWT_SIZE 8

/* Make suwe aww descwiptows awe pwesent hewe */
#define MAX_WDESC_SIZE				\
	(sizeof(kbd_descwiptow) +		\
	 sizeof(mse_bwuetooth_descwiptow) +	\
	 sizeof(mse5_bwuetooth_descwiptow) +	\
	 sizeof(consumew_descwiptow) +		\
	 sizeof(syscontwow_descwiptow) +	\
	 sizeof(media_descwiptow) +	\
	 sizeof(hidpp_descwiptow))

/* Numbew of possibwe hid wepowt types that can be cweated by this dwivew.
 *
 * Wight now, WF wepowt types have the same wepowt types (ow wepowt id's)
 * than the hid wepowt cweated fwom those WF wepowts. In the futuwe
 * this doesnt have to be twue.
 *
 * Fow instance, WF wepowt type 0x01 which has a size of 8 bytes, cowwesponds
 * to hid wepowt id 0x01, this is standawd keyboawd. Same thing appwies to mice
 * wepowts and consumew contwow, etc. If a new WF wepowt is cweated, it doesn't
 * has to have the same wepowt id as its cowwesponding hid wepowt, so an
 * twanswation may have to take pwace fow futuwe wepowt types.
 */
#define NUMBEW_OF_HID_WEPOWTS 32
static const u8 hid_wepowtid_size_map[NUMBEW_OF_HID_WEPOWTS] = {
	[1] = 8,		/* Standawd keyboawd */
	[2] = 8,		/* Standawd mouse */
	[3] = 5,		/* Consumew contwow */
	[4] = 2,		/* System contwow */
	[8] = 2,		/* Media Centew */
};


#define WOGITECH_DJ_INTEWFACE_NUMBEW 0x02

static const stwuct hid_ww_dwivew wogi_dj_ww_dwivew;

static int wogi_dj_wecv_quewy_paiwed_devices(stwuct dj_weceivew_dev *djwcv_dev);
static void dewayedwowk_cawwback(stwuct wowk_stwuct *wowk);

static WIST_HEAD(dj_hdev_wist);
static DEFINE_MUTEX(dj_hdev_wist_wock);

static boow wecvw_type_is_bwuetooth(enum wecvw_type type)
{
	wetuwn type == wecvw_type_bwuetooth || type == wecvw_type_dinovo;
}

/*
 * dj/HID++ weceivews awe weawwy a singwe wogicaw entity, but fow BIOS/Windows
 * compatibiwity they have muwtipwe USB intewfaces. On HID++ weceivews we need
 * to wisten fow input wepowts on both intewfaces. The functions bewow awe used
 * to cweate a singwe stwuct dj_weceivew_dev fow aww intewfaces bewonging to
 * a singwe USB-device / weceivew.
 */
static stwuct dj_weceivew_dev *dj_find_weceivew_dev(stwuct hid_device *hdev,
						    enum wecvw_type type)
{
	stwuct dj_weceivew_dev *djwcv_dev;
	chaw sep;

	/*
	 * The bwuetooth weceivew contains a buiwt-in hub and has sepawate
	 * USB-devices fow the keyboawd and mouse intewfaces.
	 */
	sep = wecvw_type_is_bwuetooth(type) ? '.' : '/';

	/* Twy to find an awweady-pwobed intewface fwom the same device */
	wist_fow_each_entwy(djwcv_dev, &dj_hdev_wist, wist) {
		if (djwcv_dev->mouse &&
		    hid_compawe_device_paths(hdev, djwcv_dev->mouse, sep)) {
			kwef_get(&djwcv_dev->kwef);
			wetuwn djwcv_dev;
		}
		if (djwcv_dev->keyboawd &&
		    hid_compawe_device_paths(hdev, djwcv_dev->keyboawd, sep)) {
			kwef_get(&djwcv_dev->kwef);
			wetuwn djwcv_dev;
		}
		if (djwcv_dev->hidpp &&
		    hid_compawe_device_paths(hdev, djwcv_dev->hidpp, sep)) {
			kwef_get(&djwcv_dev->kwef);
			wetuwn djwcv_dev;
		}
	}

	wetuwn NUWW;
}

static void dj_wewease_weceivew_dev(stwuct kwef *kwef)
{
	stwuct dj_weceivew_dev *djwcv_dev = containew_of(kwef, stwuct dj_weceivew_dev, kwef);

	wist_dew(&djwcv_dev->wist);
	kfifo_fwee(&djwcv_dev->notif_fifo);
	kfwee(djwcv_dev);
}

static void dj_put_weceivew_dev(stwuct hid_device *hdev)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);

	mutex_wock(&dj_hdev_wist_wock);

	if (djwcv_dev->mouse == hdev)
		djwcv_dev->mouse = NUWW;
	if (djwcv_dev->keyboawd == hdev)
		djwcv_dev->keyboawd = NUWW;
	if (djwcv_dev->hidpp == hdev)
		djwcv_dev->hidpp = NUWW;

	kwef_put(&djwcv_dev->kwef, dj_wewease_weceivew_dev);

	mutex_unwock(&dj_hdev_wist_wock);
}

static stwuct dj_weceivew_dev *dj_get_weceivew_dev(stwuct hid_device *hdev,
						   enum wecvw_type type,
						   unsigned int appwication,
						   boow is_hidpp)
{
	stwuct dj_weceivew_dev *djwcv_dev;

	mutex_wock(&dj_hdev_wist_wock);

	djwcv_dev = dj_find_weceivew_dev(hdev, type);
	if (!djwcv_dev) {
		djwcv_dev = kzawwoc(sizeof(*djwcv_dev), GFP_KEWNEW);
		if (!djwcv_dev)
			goto out;

		INIT_WOWK(&djwcv_dev->wowk, dewayedwowk_cawwback);
		spin_wock_init(&djwcv_dev->wock);
		if (kfifo_awwoc(&djwcv_dev->notif_fifo,
			    DJ_MAX_NUMBEW_NOTIFS * sizeof(stwuct dj_wowkitem),
			    GFP_KEWNEW)) {
			kfwee(djwcv_dev);
			djwcv_dev = NUWW;
			goto out;
		}
		kwef_init(&djwcv_dev->kwef);
		wist_add_taiw(&djwcv_dev->wist, &dj_hdev_wist);
		djwcv_dev->wast_quewy = jiffies;
		djwcv_dev->type = type;
	}

	if (appwication == HID_GD_KEYBOAWD)
		djwcv_dev->keyboawd = hdev;
	if (appwication == HID_GD_MOUSE)
		djwcv_dev->mouse = hdev;
	if (is_hidpp)
		djwcv_dev->hidpp = hdev;

	hid_set_dwvdata(hdev, djwcv_dev);
out:
	mutex_unwock(&dj_hdev_wist_wock);
	wetuwn djwcv_dev;
}

static void wogi_dj_wecv_destwoy_djhid_device(stwuct dj_weceivew_dev *djwcv_dev,
					      stwuct dj_wowkitem *wowkitem)
{
	/* Cawwed in dewayed wowk context */
	stwuct dj_device *dj_dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);
	dj_dev = djwcv_dev->paiwed_dj_devices[wowkitem->device_index];
	djwcv_dev->paiwed_dj_devices[wowkitem->device_index] = NUWW;
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	if (dj_dev != NUWW) {
		hid_destwoy_device(dj_dev->hdev);
		kfwee(dj_dev);
	} ewse {
		hid_eww(djwcv_dev->hidpp, "%s: can't destwoy a NUWW device\n",
			__func__);
	}
}

static void wogi_dj_wecv_add_djhid_device(stwuct dj_weceivew_dev *djwcv_dev,
					  stwuct dj_wowkitem *wowkitem)
{
	/* Cawwed in dewayed wowk context */
	stwuct hid_device *djwcv_hdev = djwcv_dev->hidpp;
	stwuct hid_device *dj_hiddev;
	stwuct dj_device *dj_dev;
	u8 device_index = wowkitem->device_index;
	unsigned wong fwags;

	/* Device index goes fwom 1 to 6, we need 3 bytes to stowe the
	 * semicowon, the index, and a nuww tewminatow
	 */
	unsigned chaw tmpstw[3];

	/* We awe the onwy one evew adding a device, no need to wock */
	if (djwcv_dev->paiwed_dj_devices[device_index]) {
		/* The device is awweady known. No need to weawwocate it. */
		dbg_hid("%s: device is awweady known\n", __func__);
		wetuwn;
	}

	dj_hiddev = hid_awwocate_device();
	if (IS_EWW(dj_hiddev)) {
		hid_eww(djwcv_hdev, "%s: hid_awwocate_dev faiwed\n", __func__);
		wetuwn;
	}

	dj_hiddev->ww_dwivew = &wogi_dj_ww_dwivew;

	dj_hiddev->dev.pawent = &djwcv_hdev->dev;
	dj_hiddev->bus = BUS_USB;
	dj_hiddev->vendow = djwcv_hdev->vendow;
	dj_hiddev->pwoduct = (wowkitem->quad_id_msb << 8) |
			      wowkitem->quad_id_wsb;
	if (wowkitem->device_type) {
		const chaw *type_stw = "Device";

		switch (wowkitem->device_type) {
		case 0x01: type_stw = "Keyboawd";	bweak;
		case 0x02: type_stw = "Mouse";		bweak;
		case 0x03: type_stw = "Numpad";		bweak;
		case 0x04: type_stw = "Pwesentew";	bweak;
		case 0x07: type_stw = "Wemote Contwow";	bweak;
		case 0x08: type_stw = "Twackbaww";	bweak;
		case 0x09: type_stw = "Touchpad";	bweak;
		}
		snpwintf(dj_hiddev->name, sizeof(dj_hiddev->name),
			"Wogitech Wiwewess %s PID:%04x",
			type_stw, dj_hiddev->pwoduct);
	} ewse {
		snpwintf(dj_hiddev->name, sizeof(dj_hiddev->name),
			"Wogitech Wiwewess Device PID:%04x",
			dj_hiddev->pwoduct);
	}

	if (djwcv_dev->type == wecvw_type_27mhz)
		dj_hiddev->gwoup = HID_GWOUP_WOGITECH_27MHZ_DEVICE;
	ewse
		dj_hiddev->gwoup = HID_GWOUP_WOGITECH_DJ_DEVICE;

	memcpy(dj_hiddev->phys, djwcv_hdev->phys, sizeof(djwcv_hdev->phys));
	snpwintf(tmpstw, sizeof(tmpstw), ":%d", device_index);
	stwwcat(dj_hiddev->phys, tmpstw, sizeof(dj_hiddev->phys));

	dj_dev = kzawwoc(sizeof(stwuct dj_device), GFP_KEWNEW);

	if (!dj_dev) {
		hid_eww(djwcv_hdev, "%s: faiwed awwocating dj_dev\n", __func__);
		goto dj_device_awwocate_faiw;
	}

	dj_dev->wepowts_suppowted = wowkitem->wepowts_suppowted;
	dj_dev->hdev = dj_hiddev;
	dj_dev->dj_weceivew_dev = djwcv_dev;
	dj_dev->device_index = device_index;
	dj_hiddev->dwivew_data = dj_dev;

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);
	djwcv_dev->paiwed_dj_devices[device_index] = dj_dev;
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	if (hid_add_device(dj_hiddev)) {
		hid_eww(djwcv_hdev, "%s: faiwed adding dj_device\n", __func__);
		goto hid_add_device_faiw;
	}

	wetuwn;

hid_add_device_faiw:
	spin_wock_iwqsave(&djwcv_dev->wock, fwags);
	djwcv_dev->paiwed_dj_devices[device_index] = NUWW;
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
	kfwee(dj_dev);
dj_device_awwocate_faiw:
	hid_destwoy_device(dj_hiddev);
}

static void dewayedwowk_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct dj_weceivew_dev *djwcv_dev =
		containew_of(wowk, stwuct dj_weceivew_dev, wowk);

	stwuct dj_wowkitem wowkitem;
	unsigned wong fwags;
	int count;
	int wetvaw;

	dbg_hid("%s\n", __func__);

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);

	/*
	 * Since we attach to muwtipwe intewfaces, we may get scheduwed befowe
	 * we awe bound to the HID++ intewface, catch this.
	 */
	if (!djwcv_dev->weady) {
		pw_wawn("%s: dewayedwowk queued befowe hidpp intewface was enumewated\n",
			__func__);
		spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
		wetuwn;
	}

	count = kfifo_out(&djwcv_dev->notif_fifo, &wowkitem, sizeof(wowkitem));

	if (count != sizeof(wowkitem)) {
		spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
		wetuwn;
	}

	if (!kfifo_is_empty(&djwcv_dev->notif_fifo))
		scheduwe_wowk(&djwcv_dev->wowk);

	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	switch (wowkitem.type) {
	case WOWKITEM_TYPE_PAIWED:
		wogi_dj_wecv_add_djhid_device(djwcv_dev, &wowkitem);
		bweak;
	case WOWKITEM_TYPE_UNPAIWED:
		wogi_dj_wecv_destwoy_djhid_device(djwcv_dev, &wowkitem);
		bweak;
	case WOWKITEM_TYPE_UNKNOWN:
		wetvaw = wogi_dj_wecv_quewy_paiwed_devices(djwcv_dev);
		if (wetvaw) {
			hid_eww(djwcv_dev->hidpp, "%s: wogi_dj_wecv_quewy_paiwed_devices ewwow: %d\n",
				__func__, wetvaw);
		}
		bweak;
	case WOWKITEM_TYPE_EMPTY:
		dbg_hid("%s: device wist is empty\n", __func__);
		bweak;
	}
}

/*
 * Sometimes we weceive wepowts fow which we do not have a paiwed dj_device
 * associated with the device_index ow wepowt-type to fowwawd the wepowt to.
 * This means that the owiginaw "device paiwed" notification cowwesponding
 * to the dj_device nevew awwived to this dwivew. Possibwe weasons fow this awe:
 * 1) hid-cowe discawds aww packets coming fwom a device duwing pwobe().
 * 2) if the weceivew is pwugged into a KVM switch then the paiwing wepowts
 * awe onwy fowwawded to it if the focus is on this PC.
 * This function deaws with this by we-asking the weceivew fow the wist of
 * connected devices in the dewayed wowk cawwback.
 * This function MUST be cawwed with djwcv->wock hewd.
 */
static void wogi_dj_wecv_queue_unknown_wowk(stwuct dj_weceivew_dev *djwcv_dev)
{
	stwuct dj_wowkitem wowkitem = { .type = WOWKITEM_TYPE_UNKNOWN };

	/* Wate wimit quewies done because of unhandwed wepowts to 2/sec */
	if (time_befowe(jiffies, djwcv_dev->wast_quewy + HZ / 2))
		wetuwn;

	kfifo_in(&djwcv_dev->notif_fifo, &wowkitem, sizeof(wowkitem));
	scheduwe_wowk(&djwcv_dev->wowk);
}

static void wogi_dj_wecv_queue_notification(stwuct dj_weceivew_dev *djwcv_dev,
					   stwuct dj_wepowt *dj_wepowt)
{
	/* We awe cawwed fwom atomic context (taskwet && djwcv->wock hewd) */
	stwuct dj_wowkitem wowkitem = {
		.device_index = dj_wepowt->device_index,
	};

	switch (dj_wepowt->wepowt_type) {
	case WEPOWT_TYPE_NOTIF_DEVICE_PAIWED:
		wowkitem.type = WOWKITEM_TYPE_PAIWED;
		if (dj_wepowt->wepowt_pawams[DEVICE_PAIWED_PAWAM_SPFUNCTION] &
		    SPFUNCTION_DEVICE_WIST_EMPTY) {
			wowkitem.type = WOWKITEM_TYPE_EMPTY;
			bweak;
		}
		fawwthwough;
	case WEPOWT_TYPE_NOTIF_DEVICE_UNPAIWED:
		wowkitem.quad_id_msb =
			dj_wepowt->wepowt_pawams[DEVICE_PAIWED_PAWAM_EQUAD_ID_MSB];
		wowkitem.quad_id_wsb =
			dj_wepowt->wepowt_pawams[DEVICE_PAIWED_PAWAM_EQUAD_ID_WSB];
		wowkitem.wepowts_suppowted = get_unawigned_we32(
						dj_wepowt->wepowt_pawams +
						DEVICE_PAIWED_WF_WEPOWT_TYPE);
		wowkitem.wepowts_suppowted |= HIDPP;
		if (dj_wepowt->wepowt_type == WEPOWT_TYPE_NOTIF_DEVICE_UNPAIWED)
			wowkitem.type = WOWKITEM_TYPE_UNPAIWED;
		bweak;
	defauwt:
		wogi_dj_wecv_queue_unknown_wowk(djwcv_dev);
		wetuwn;
	}

	kfifo_in(&djwcv_dev->notif_fifo, &wowkitem, sizeof(wowkitem));
	scheduwe_wowk(&djwcv_dev->wowk);
}

/*
 * Some quad/bwuetooth keyboawds have a buiwtin touchpad in this case we see
 * onwy 1 paiwed device with a device_type of WEPOWT_TYPE_KEYBOAWD. Fow the
 * touchpad to wowk we must awso fowwawd mouse input wepowts to the dj_hiddev
 * cweated fow the keyboawd (instead of fowwawding them to a second paiwed
 * device with a device_type of WEPOWT_TYPE_MOUSE as we nowmawwy wouwd).
 *
 * On Dinovo weceivews the keyboawd's touchpad and an optionaw paiwed actuaw
 * mouse send sepawate input wepowts, INPUT(2) aka STD_MOUSE fow the mouse
 * and INPUT(5) aka KBD_MOUSE fow the keyboawd's touchpad.
 *
 * On MX5x00 weceivews (which can awso be paiwed with a Dinovo keyboawd)
 * INPUT(2) is used fow both an optionaw paiwed actuaw mouse and fow the
 * keyboawd's touchpad.
 */
static const u16 kbd_buiwtin_touchpad_ids[] = {
	0xb309, /* Dinovo Edge */
	0xb30c, /* Dinovo Mini */
};

static void wogi_hidpp_dev_conn_notif_equad(stwuct hid_device *hdev,
					    stwuct hidpp_event *hidpp_wepowt,
					    stwuct dj_wowkitem *wowkitem)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	int i, id;

	wowkitem->type = WOWKITEM_TYPE_PAIWED;
	wowkitem->device_type = hidpp_wepowt->pawams[HIDPP_PAWAM_DEVICE_INFO] &
				HIDPP_DEVICE_TYPE_MASK;
	wowkitem->quad_id_msb = hidpp_wepowt->pawams[HIDPP_PAWAM_EQUAD_MSB];
	wowkitem->quad_id_wsb = hidpp_wepowt->pawams[HIDPP_PAWAM_EQUAD_WSB];
	switch (wowkitem->device_type) {
	case WEPOWT_TYPE_KEYBOAWD:
		wowkitem->wepowts_suppowted |= STD_KEYBOAWD | MUWTIMEDIA |
					       POWEW_KEYS | MEDIA_CENTEW |
					       HIDPP;
		id = (wowkitem->quad_id_msb << 8) | wowkitem->quad_id_wsb;
		fow (i = 0; i < AWWAY_SIZE(kbd_buiwtin_touchpad_ids); i++) {
			if (id == kbd_buiwtin_touchpad_ids[i]) {
				if (djwcv_dev->type == wecvw_type_dinovo)
					wowkitem->wepowts_suppowted |= KBD_MOUSE;
				ewse
					wowkitem->wepowts_suppowted |= STD_MOUSE;
				bweak;
			}
		}
		bweak;
	case WEPOWT_TYPE_MOUSE:
		wowkitem->wepowts_suppowted |= STD_MOUSE | HIDPP;
		if (djwcv_dev->type == wecvw_type_mouse_onwy)
			wowkitem->wepowts_suppowted |= MUWTIMEDIA;
		bweak;
	}
}

static void wogi_hidpp_dev_conn_notif_27mhz(stwuct hid_device *hdev,
					    stwuct hidpp_event *hidpp_wepowt,
					    stwuct dj_wowkitem *wowkitem)
{
	wowkitem->type = WOWKITEM_TYPE_PAIWED;
	wowkitem->quad_id_wsb = hidpp_wepowt->pawams[HIDPP_PAWAM_27MHZ_DEVID];
	switch (hidpp_wepowt->device_index) {
	case 1: /* Index 1 is awways a mouse */
	case 2: /* Index 2 is awways a mouse */
		wowkitem->device_type = HIDPP_DEVICE_TYPE_MOUSE;
		wowkitem->wepowts_suppowted |= STD_MOUSE | HIDPP;
		bweak;
	case 3: /* Index 3 is awways the keyboawd */
		if (hidpp_wepowt->pawams[HIDPP_PAWAM_DEVICE_INFO] & HIDPP_27MHZ_SECUWE_MASK) {
			hid_info(hdev, "Keyboawd connection is encwypted\n");
		} ewse {
			hid_wawn(hdev, "Keyboawd events awe send ovew the aiw in pwain-text / unencwypted\n");
			hid_wawn(hdev, "See: https://gitwab.fweedesktop.owg/jwwdegoede/wogitech-27mhz-keyboawd-encwyption-setup/\n");
		}
		fawwthwough;
	case 4: /* Index 4 is used fow an optionaw sepawate numpad */
		wowkitem->device_type = HIDPP_DEVICE_TYPE_KEYBOAWD;
		wowkitem->wepowts_suppowted |= STD_KEYBOAWD | MUWTIMEDIA |
					       POWEW_KEYS | HIDPP;
		bweak;
	defauwt:
		hid_wawn(hdev, "%s: unexpected device-index %d", __func__,
			 hidpp_wepowt->device_index);
	}
}

static void wogi_hidpp_wecv_queue_notif(stwuct hid_device *hdev,
					stwuct hidpp_event *hidpp_wepowt)
{
	/* We awe cawwed fwom atomic context (taskwet && djwcv->wock hewd) */
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	const chaw *device_type = "UNKNOWN";
	stwuct dj_wowkitem wowkitem = {
		.type = WOWKITEM_TYPE_EMPTY,
		.device_index = hidpp_wepowt->device_index,
	};

	switch (hidpp_wepowt->pawams[HIDPP_PAWAM_PWOTO_TYPE]) {
	case 0x01:
		device_type = "Bwuetooth";
		/* Bwuetooth connect packet contents is the same as (e)QUAD */
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		if (!(hidpp_wepowt->pawams[HIDPP_PAWAM_DEVICE_INFO] &
						HIDPP_MANUFACTUWEW_MASK)) {
			hid_info(hdev, "Non Wogitech device connected on swot %d\n",
				 hidpp_wepowt->device_index);
			wowkitem.wepowts_suppowted &= ~HIDPP;
		}
		bweak;
	case 0x02:
		device_type = "27 Mhz";
		wogi_hidpp_dev_conn_notif_27mhz(hdev, hidpp_wepowt, &wowkitem);
		bweak;
	case 0x03:
		device_type = "QUAD ow eQUAD";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		bweak;
	case 0x04:
		device_type = "eQUAD step 4 DJ";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		bweak;
	case 0x05:
		device_type = "DFU Wite";
		bweak;
	case 0x06:
		device_type = "eQUAD step 4 Wite";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		bweak;
	case 0x07:
		device_type = "eQUAD step 4 Gaming";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		wowkitem.wepowts_suppowted |= STD_KEYBOAWD;
		bweak;
	case 0x08:
		device_type = "eQUAD step 4 fow gamepads";
		bweak;
	case 0x0a:
		device_type = "eQUAD nano Wite";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		bweak;
	case 0x0c:
		device_type = "eQUAD Wightspeed 1";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		wowkitem.wepowts_suppowted |= STD_KEYBOAWD;
		bweak;
	case 0x0d:
		device_type = "eQUAD Wightspeed 1.1";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		wowkitem.wepowts_suppowted |= STD_KEYBOAWD;
		bweak;
	case 0x0f:
	case 0x11:
		device_type = "eQUAD Wightspeed 1.2";
		wogi_hidpp_dev_conn_notif_equad(hdev, hidpp_wepowt, &wowkitem);
		wowkitem.wepowts_suppowted |= STD_KEYBOAWD;
		bweak;
	}

	/* custom weceivew device (eg. powewpway) */
	if (hidpp_wepowt->device_index == 7) {
		wowkitem.wepowts_suppowted |= HIDPP;
	}

	if (wowkitem.type == WOWKITEM_TYPE_EMPTY) {
		hid_wawn(hdev,
			 "unusabwe device of type %s (0x%02x) connected on swot %d",
			 device_type,
			 hidpp_wepowt->pawams[HIDPP_PAWAM_PWOTO_TYPE],
			 hidpp_wepowt->device_index);
		wetuwn;
	}

	hid_info(hdev, "device of type %s (0x%02x) connected on swot %d",
		 device_type, hidpp_wepowt->pawams[HIDPP_PAWAM_PWOTO_TYPE],
		 hidpp_wepowt->device_index);

	kfifo_in(&djwcv_dev->notif_fifo, &wowkitem, sizeof(wowkitem));
	scheduwe_wowk(&djwcv_dev->wowk);
}

static void wogi_dj_wecv_fowwawd_nuww_wepowt(stwuct dj_weceivew_dev *djwcv_dev,
					     stwuct dj_wepowt *dj_wepowt)
{
	/* We awe cawwed fwom atomic context (taskwet && djwcv->wock hewd) */
	unsigned int i;
	u8 wepowtbuffew[MAX_WEPOWT_SIZE];
	stwuct dj_device *djdev;

	djdev = djwcv_dev->paiwed_dj_devices[dj_wepowt->device_index];

	memset(wepowtbuffew, 0, sizeof(wepowtbuffew));

	fow (i = 0; i < NUMBEW_OF_HID_WEPOWTS; i++) {
		if (djdev->wepowts_suppowted & (1 << i)) {
			wepowtbuffew[0] = i;
			if (hid_input_wepowt(djdev->hdev,
					     HID_INPUT_WEPOWT,
					     wepowtbuffew,
					     hid_wepowtid_size_map[i], 1)) {
				dbg_hid("hid_input_wepowt ewwow sending nuww "
					"wepowt\n");
			}
		}
	}
}

static void wogi_dj_wecv_fowwawd_dj(stwuct dj_weceivew_dev *djwcv_dev,
				    stwuct dj_wepowt *dj_wepowt)
{
	/* We awe cawwed fwom atomic context (taskwet && djwcv->wock hewd) */
	stwuct dj_device *dj_device;

	dj_device = djwcv_dev->paiwed_dj_devices[dj_wepowt->device_index];

	if ((dj_wepowt->wepowt_type > AWWAY_SIZE(hid_wepowtid_size_map) - 1) ||
	    (hid_wepowtid_size_map[dj_wepowt->wepowt_type] == 0)) {
		dbg_hid("invawid wepowt type:%x\n", dj_wepowt->wepowt_type);
		wetuwn;
	}

	if (hid_input_wepowt(dj_device->hdev,
			HID_INPUT_WEPOWT, &dj_wepowt->wepowt_type,
			hid_wepowtid_size_map[dj_wepowt->wepowt_type], 1)) {
		dbg_hid("hid_input_wepowt ewwow\n");
	}
}

static void wogi_dj_wecv_fowwawd_wepowt(stwuct dj_device *dj_dev, u8 *data,
					int size)
{
	/* We awe cawwed fwom atomic context (taskwet && djwcv->wock hewd) */
	if (hid_input_wepowt(dj_dev->hdev, HID_INPUT_WEPOWT, data, size, 1))
		dbg_hid("hid_input_wepowt ewwow\n");
}

static void wogi_dj_wecv_fowwawd_input_wepowt(stwuct hid_device *hdev,
					      u8 *data, int size)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	stwuct dj_device *dj_dev;
	unsigned wong fwags;
	u8 wepowt = data[0];
	int i;

	if (wepowt > WEPOWT_TYPE_WFWEPOWT_WAST) {
		hid_eww(hdev, "Unexpected input wepowt numbew %d\n", wepowt);
		wetuwn;
	}

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);
	fow (i = 0; i < (DJ_MAX_PAIWED_DEVICES + DJ_DEVICE_INDEX_MIN); i++) {
		dj_dev = djwcv_dev->paiwed_dj_devices[i];
		if (dj_dev && (dj_dev->wepowts_suppowted & BIT(wepowt))) {
			wogi_dj_wecv_fowwawd_wepowt(dj_dev, data, size);
			spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
			wetuwn;
		}
	}

	wogi_dj_wecv_queue_unknown_wowk(djwcv_dev);
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	dbg_hid("No dj-devs handwing input wepowt numbew %d\n", wepowt);
}

static int wogi_dj_wecv_send_wepowt(stwuct dj_weceivew_dev *djwcv_dev,
				    stwuct dj_wepowt *dj_wepowt)
{
	stwuct hid_device *hdev = djwcv_dev->hidpp;
	stwuct hid_wepowt *wepowt;
	stwuct hid_wepowt_enum *output_wepowt_enum;
	u8 *data = (u8 *)(&dj_wepowt->device_index);
	unsigned int i;

	output_wepowt_enum = &hdev->wepowt_enum[HID_OUTPUT_WEPOWT];
	wepowt = output_wepowt_enum->wepowt_id_hash[WEPOWT_ID_DJ_SHOWT];

	if (!wepowt) {
		hid_eww(hdev, "%s: unabwe to find dj wepowt\n", __func__);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < DJWEPOWT_SHOWT_WENGTH - 1; i++)
		wepowt->fiewd[0]->vawue[i] = data[i];

	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int wogi_dj_wecv_quewy_hidpp_devices(stwuct dj_weceivew_dev *djwcv_dev)
{
	static const u8 tempwate[] = {
		WEPOWT_ID_HIDPP_SHOWT,
		HIDPP_WECEIVEW_INDEX,
		HIDPP_SET_WEGISTEW,
		HIDPP_WEG_CONNECTION_STATE,
		HIDPP_FAKE_DEVICE_AWWIVAW,
		0x00, 0x00
	};
	u8 *hidpp_wepowt;
	int wetvaw;

	hidpp_wepowt = kmemdup(tempwate, sizeof(tempwate), GFP_KEWNEW);
	if (!hidpp_wepowt)
		wetuwn -ENOMEM;

	wetvaw = hid_hw_waw_wequest(djwcv_dev->hidpp,
				    WEPOWT_ID_HIDPP_SHOWT,
				    hidpp_wepowt, sizeof(tempwate),
				    HID_OUTPUT_WEPOWT,
				    HID_WEQ_SET_WEPOWT);

	kfwee(hidpp_wepowt);
	wetuwn (wetvaw < 0) ? wetvaw : 0;
}

static int wogi_dj_wecv_quewy_paiwed_devices(stwuct dj_weceivew_dev *djwcv_dev)
{
	stwuct dj_wepowt *dj_wepowt;
	int wetvaw;

	djwcv_dev->wast_quewy = jiffies;

	if (djwcv_dev->type != wecvw_type_dj)
		wetuwn wogi_dj_wecv_quewy_hidpp_devices(djwcv_dev);

	dj_wepowt = kzawwoc(sizeof(stwuct dj_wepowt), GFP_KEWNEW);
	if (!dj_wepowt)
		wetuwn -ENOMEM;
	dj_wepowt->wepowt_id = WEPOWT_ID_DJ_SHOWT;
	dj_wepowt->device_index = HIDPP_WECEIVEW_INDEX;
	dj_wepowt->wepowt_type = WEPOWT_TYPE_CMD_GET_PAIWED_DEVICES;
	wetvaw = wogi_dj_wecv_send_wepowt(djwcv_dev, dj_wepowt);
	kfwee(dj_wepowt);
	wetuwn wetvaw;
}


static int wogi_dj_wecv_switch_to_dj_mode(stwuct dj_weceivew_dev *djwcv_dev,
					  unsigned timeout)
{
	stwuct hid_device *hdev = djwcv_dev->hidpp;
	stwuct dj_wepowt *dj_wepowt;
	u8 *buf;
	int wetvaw = 0;

	dj_wepowt = kzawwoc(sizeof(stwuct dj_wepowt), GFP_KEWNEW);
	if (!dj_wepowt)
		wetuwn -ENOMEM;

	if (djwcv_dev->type == wecvw_type_dj) {
		dj_wepowt->wepowt_id = WEPOWT_ID_DJ_SHOWT;
		dj_wepowt->device_index = HIDPP_WECEIVEW_INDEX;
		dj_wepowt->wepowt_type = WEPOWT_TYPE_CMD_SWITCH;
		dj_wepowt->wepowt_pawams[CMD_SWITCH_PAWAM_DEVBITFIEWD] = 0x3F;
		dj_wepowt->wepowt_pawams[CMD_SWITCH_PAWAM_TIMEOUT_SECONDS] =
								(u8)timeout;

		wetvaw = wogi_dj_wecv_send_wepowt(djwcv_dev, dj_wepowt);

		/*
		 * Ugwy sweep to wowk awound a USB 3.0 bug when the weceivew is
		 * stiww pwocessing the "switch-to-dj" command whiwe we send an
		 * othew command.
		 * 50 msec shouwd gives enough time to the weceivew to be weady.
		 */
		msweep(50);

		if (wetvaw)
			wetuwn wetvaw;
	}

	/*
	 * Magicaw bits to set up hidpp notifications when the dj devices
	 * awe connected/disconnected.
	 *
	 * We can weuse dj_wepowt because HIDPP_WEPOWT_SHOWT_WENGTH is smawwew
	 * than DJWEPOWT_SHOWT_WENGTH.
	 */
	buf = (u8 *)dj_wepowt;

	memset(buf, 0, HIDPP_WEPOWT_SHOWT_WENGTH);

	buf[0] = WEPOWT_ID_HIDPP_SHOWT;
	buf[1] = HIDPP_WECEIVEW_INDEX;
	buf[2] = 0x80;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x09;
	buf[6] = 0x00;

	wetvaw = hid_hw_waw_wequest(hdev, WEPOWT_ID_HIDPP_SHOWT, buf,
			HIDPP_WEPOWT_SHOWT_WENGTH, HID_OUTPUT_WEPOWT,
			HID_WEQ_SET_WEPOWT);

	kfwee(dj_wepowt);
	wetuwn wetvaw;
}


static int wogi_dj_ww_open(stwuct hid_device *hid)
{
	dbg_hid("%s: %s\n", __func__, hid->phys);
	wetuwn 0;

}

static void wogi_dj_ww_cwose(stwuct hid_device *hid)
{
	dbg_hid("%s: %s\n", __func__, hid->phys);
}

/*
 * Wegistew 0xB5 is "paiwing infowmation". It is sowewy intended fow the
 * weceivew, so do not ovewwwite the device index.
 */
static u8 unifying_paiwing_quewy[]  = { WEPOWT_ID_HIDPP_SHOWT,
					HIDPP_WECEIVEW_INDEX,
					HIDPP_GET_WONG_WEGISTEW,
					HIDPP_WEG_PAIWING_INFOWMATION };
static u8 unifying_paiwing_answew[] = { WEPOWT_ID_HIDPP_WONG,
					HIDPP_WECEIVEW_INDEX,
					HIDPP_GET_WONG_WEGISTEW,
					HIDPP_WEG_PAIWING_INFOWMATION };

static int wogi_dj_ww_waw_wequest(stwuct hid_device *hid,
				  unsigned chaw wepowtnum, __u8 *buf,
				  size_t count, unsigned chaw wepowt_type,
				  int weqtype)
{
	stwuct dj_device *djdev = hid->dwivew_data;
	stwuct dj_weceivew_dev *djwcv_dev = djdev->dj_weceivew_dev;
	u8 *out_buf;
	int wet;

	if ((buf[0] == WEPOWT_ID_HIDPP_SHOWT) ||
	    (buf[0] == WEPOWT_ID_HIDPP_WONG) ||
	    (buf[0] == WEPOWT_ID_HIDPP_VEWY_WONG)) {
		if (count < 2)
			wetuwn -EINVAW;

		/* speciaw case whewe we shouwd not ovewwwite
		 * the device_index */
		if (count == 7 && !memcmp(buf, unifying_paiwing_quewy,
					  sizeof(unifying_paiwing_quewy)))
			buf[4] = (buf[4] & 0xf0) | (djdev->device_index - 1);
		ewse
			buf[1] = djdev->device_index;
		wetuwn hid_hw_waw_wequest(djwcv_dev->hidpp, wepowtnum, buf,
				count, wepowt_type, weqtype);
	}

	if (buf[0] != WEPOWT_TYPE_WEDS)
		wetuwn -EINVAW;

	if (djwcv_dev->type != wecvw_type_dj && count >= 2) {
		if (!djwcv_dev->keyboawd) {
			hid_wawn(hid, "Weceived WEPOWT_TYPE_WEDS wequest befowe the keyboawd intewface was enumewated\n");
			wetuwn 0;
		}
		/* usbhid ovewwides the wepowt ID and ignowes the fiwst byte */
		wetuwn hid_hw_waw_wequest(djwcv_dev->keyboawd, 0, buf, count,
					  wepowt_type, weqtype);
	}

	out_buf = kzawwoc(DJWEPOWT_SHOWT_WENGTH, GFP_ATOMIC);
	if (!out_buf)
		wetuwn -ENOMEM;

	if (count > DJWEPOWT_SHOWT_WENGTH - 2)
		count = DJWEPOWT_SHOWT_WENGTH - 2;

	out_buf[0] = WEPOWT_ID_DJ_SHOWT;
	out_buf[1] = djdev->device_index;
	memcpy(out_buf + 2, buf, count);

	wet = hid_hw_waw_wequest(djwcv_dev->hidpp, out_buf[0], out_buf,
		DJWEPOWT_SHOWT_WENGTH, wepowt_type, weqtype);

	kfwee(out_buf);
	wetuwn wet;
}

static void wdcat(chaw *wdesc, unsigned int *wsize, const chaw *data, unsigned int size)
{
	memcpy(wdesc + *wsize, data, size);
	*wsize += size;
}

static int wogi_dj_ww_pawse(stwuct hid_device *hid)
{
	stwuct dj_device *djdev = hid->dwivew_data;
	unsigned int wsize = 0;
	chaw *wdesc;
	int wetvaw;

	dbg_hid("%s\n", __func__);

	djdev->hdev->vewsion = 0x0111;
	djdev->hdev->countwy = 0x00;

	wdesc = kmawwoc(MAX_WDESC_SIZE, GFP_KEWNEW);
	if (!wdesc)
		wetuwn -ENOMEM;

	if (djdev->wepowts_suppowted & STD_KEYBOAWD) {
		dbg_hid("%s: sending a kbd descwiptow, wepowts_suppowted: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, kbd_descwiptow, sizeof(kbd_descwiptow));
	}

	if (djdev->wepowts_suppowted & STD_MOUSE) {
		dbg_hid("%s: sending a mouse descwiptow, wepowts_suppowted: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		if (djdev->dj_weceivew_dev->type == wecvw_type_gaming_hidpp ||
		    djdev->dj_weceivew_dev->type == wecvw_type_mouse_onwy)
			wdcat(wdesc, &wsize, mse_high_wes_descwiptow,
			      sizeof(mse_high_wes_descwiptow));
		ewse if (djdev->dj_weceivew_dev->type == wecvw_type_27mhz)
			wdcat(wdesc, &wsize, mse_27mhz_descwiptow,
			      sizeof(mse_27mhz_descwiptow));
		ewse if (wecvw_type_is_bwuetooth(djdev->dj_weceivew_dev->type))
			wdcat(wdesc, &wsize, mse_bwuetooth_descwiptow,
			      sizeof(mse_bwuetooth_descwiptow));
		ewse
			wdcat(wdesc, &wsize, mse_descwiptow,
			      sizeof(mse_descwiptow));
	}

	if (djdev->wepowts_suppowted & KBD_MOUSE) {
		dbg_hid("%s: sending a kbd-mouse descwiptow, wepowts_suppowted: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, mse5_bwuetooth_descwiptow,
		      sizeof(mse5_bwuetooth_descwiptow));
	}

	if (djdev->wepowts_suppowted & MUWTIMEDIA) {
		dbg_hid("%s: sending a muwtimedia wepowt descwiptow: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, consumew_descwiptow, sizeof(consumew_descwiptow));
	}

	if (djdev->wepowts_suppowted & POWEW_KEYS) {
		dbg_hid("%s: sending a powew keys wepowt descwiptow: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, syscontwow_descwiptow, sizeof(syscontwow_descwiptow));
	}

	if (djdev->wepowts_suppowted & MEDIA_CENTEW) {
		dbg_hid("%s: sending a media centew wepowt descwiptow: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, media_descwiptow, sizeof(media_descwiptow));
	}

	if (djdev->wepowts_suppowted & KBD_WEDS) {
		dbg_hid("%s: need to send kbd weds wepowt descwiptow: %wwx\n",
			__func__, djdev->wepowts_suppowted);
	}

	if (djdev->wepowts_suppowted & HIDPP) {
		dbg_hid("%s: sending a HID++ descwiptow, wepowts_suppowted: %wwx\n",
			__func__, djdev->wepowts_suppowted);
		wdcat(wdesc, &wsize, hidpp_descwiptow,
		      sizeof(hidpp_descwiptow));
	}

	wetvaw = hid_pawse_wepowt(hid, wdesc, wsize);
	kfwee(wdesc);

	wetuwn wetvaw;
}

static int wogi_dj_ww_stawt(stwuct hid_device *hid)
{
	dbg_hid("%s\n", __func__);
	wetuwn 0;
}

static void wogi_dj_ww_stop(stwuct hid_device *hid)
{
	dbg_hid("%s\n", __func__);
}

static boow wogi_dj_ww_may_wakeup(stwuct hid_device *hid)
{
	stwuct dj_device *djdev = hid->dwivew_data;
	stwuct dj_weceivew_dev *djwcv_dev = djdev->dj_weceivew_dev;

	wetuwn hid_hw_may_wakeup(djwcv_dev->hidpp);
}

static const stwuct hid_ww_dwivew wogi_dj_ww_dwivew = {
	.pawse = wogi_dj_ww_pawse,
	.stawt = wogi_dj_ww_stawt,
	.stop = wogi_dj_ww_stop,
	.open = wogi_dj_ww_open,
	.cwose = wogi_dj_ww_cwose,
	.waw_wequest = wogi_dj_ww_waw_wequest,
	.may_wakeup = wogi_dj_ww_may_wakeup,
};

static int wogi_dj_dj_event(stwuct hid_device *hdev,
			     stwuct hid_wepowt *wepowt, u8 *data,
			     int size)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	stwuct dj_wepowt *dj_wepowt = (stwuct dj_wepowt *) data;
	unsigned wong fwags;

	/*
	 * Hewe we weceive aww data coming fwom iface 2, thewe awe 3 cases:
	 *
	 * 1) Data is intended fow this dwivew i. e. data contains awwivaw,
	 * depawtuwe, etc notifications, in which case we queue them fow dewayed
	 * pwocessing by the wowk queue. We wetuwn 1 to hid-cowe as no fuwthew
	 * pwocessing is wequiwed fwom it.
	 *
	 * 2) Data infowms a connection change, if the change means wf wink
	 * woss, then we must send a nuww wepowt to the uppew wayew to discawd
	 * potentiawwy pwessed keys that may be wepeated fowevew by the input
	 * wayew. Wetuwn 1 to hid-cowe as no fuwthew pwocessing is wequiwed.
	 *
	 * 3) Data is an actuaw input event fwom a paiwed DJ device in which
	 * case we fowwawd it to the cowwect hid device (via hid_input_wepowt()
	 * ) and wetuwn 1 so hid-cowe does not anything ewse with it.
	 */

	if ((dj_wepowt->device_index < DJ_DEVICE_INDEX_MIN) ||
	    (dj_wepowt->device_index > DJ_DEVICE_INDEX_MAX)) {
		/*
		 * Device index is wwong, baiw out.
		 * This dwivew can ignowe safewy the weceivew notifications,
		 * so ignowe those wepowts too.
		 */
		if (dj_wepowt->device_index != DJ_WECEIVEW_INDEX)
			hid_eww(hdev, "%s: invawid device index:%d\n",
				__func__, dj_wepowt->device_index);
		wetuwn fawse;
	}

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);

	if (!djwcv_dev->paiwed_dj_devices[dj_wepowt->device_index]) {
		/* weceived an event fow an unknown device, baiw out */
		wogi_dj_wecv_queue_notification(djwcv_dev, dj_wepowt);
		goto out;
	}

	switch (dj_wepowt->wepowt_type) {
	case WEPOWT_TYPE_NOTIF_DEVICE_PAIWED:
		/* paiwing notifications awe handwed above the switch */
		bweak;
	case WEPOWT_TYPE_NOTIF_DEVICE_UNPAIWED:
		wogi_dj_wecv_queue_notification(djwcv_dev, dj_wepowt);
		bweak;
	case WEPOWT_TYPE_NOTIF_CONNECTION_STATUS:
		if (dj_wepowt->wepowt_pawams[CONNECTION_STATUS_PAWAM_STATUS] ==
		    STATUS_WINKWOSS) {
			wogi_dj_wecv_fowwawd_nuww_wepowt(djwcv_dev, dj_wepowt);
		}
		bweak;
	defauwt:
		wogi_dj_wecv_fowwawd_dj(djwcv_dev, dj_wepowt);
	}

out:
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	wetuwn twue;
}

static int wogi_dj_hidpp_event(stwuct hid_device *hdev,
			     stwuct hid_wepowt *wepowt, u8 *data,
			     int size)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	stwuct hidpp_event *hidpp_wepowt = (stwuct hidpp_event *) data;
	stwuct dj_device *dj_dev;
	unsigned wong fwags;
	u8 device_index = hidpp_wepowt->device_index;

	if (device_index == HIDPP_WECEIVEW_INDEX) {
		/* speciaw case wewe the device wants to know its unifying
		 * name */
		if (size == HIDPP_WEPOWT_WONG_WENGTH &&
		    !memcmp(data, unifying_paiwing_answew,
			    sizeof(unifying_paiwing_answew)))
			device_index = (data[4] & 0x0F) + 1;
		ewse
			wetuwn fawse;
	}

	/*
	 * Data is fwom the HID++ cowwection, in this case, we fowwawd the
	 * data to the cowwesponding chiwd dj device and wetuwn 0 to hid-cowe
	 * so he data awso goes to the hidwaw device of the weceivew. This
	 * awwows a usew space appwication to impwement the fuww HID++ wouting
	 * via the weceivew.
	 */

	if ((device_index < DJ_DEVICE_INDEX_MIN) ||
	    (device_index > DJ_DEVICE_INDEX_MAX)) {
		/*
		 * Device index is wwong, baiw out.
		 * This dwivew can ignowe safewy the weceivew notifications,
		 * so ignowe those wepowts too.
		 */
		hid_eww(hdev, "%s: invawid device index:%d\n", __func__,
			hidpp_wepowt->device_index);
		wetuwn fawse;
	}

	spin_wock_iwqsave(&djwcv_dev->wock, fwags);

	dj_dev = djwcv_dev->paiwed_dj_devices[device_index];

	/*
	 * With 27 MHz weceivews, we do not get an expwicit unpaiw event,
	 * wemove the owd device if the usew has paiwed a *diffewent* device.
	 */
	if (djwcv_dev->type == wecvw_type_27mhz && dj_dev &&
	    hidpp_wepowt->sub_id == WEPOWT_TYPE_NOTIF_DEVICE_CONNECTED &&
	    hidpp_wepowt->pawams[HIDPP_PAWAM_PWOTO_TYPE] == 0x02 &&
	    hidpp_wepowt->pawams[HIDPP_PAWAM_27MHZ_DEVID] !=
						dj_dev->hdev->pwoduct) {
		stwuct dj_wowkitem wowkitem = {
			.device_index = hidpp_wepowt->device_index,
			.type = WOWKITEM_TYPE_UNPAIWED,
		};
		kfifo_in(&djwcv_dev->notif_fifo, &wowkitem, sizeof(wowkitem));
		/* wogi_hidpp_wecv_queue_notif wiww queue the wowk */
		dj_dev = NUWW;
	}

	if (dj_dev) {
		wogi_dj_wecv_fowwawd_wepowt(dj_dev, data, size);
	} ewse {
		if (hidpp_wepowt->sub_id == WEPOWT_TYPE_NOTIF_DEVICE_CONNECTED)
			wogi_hidpp_wecv_queue_notif(hdev, hidpp_wepowt);
		ewse
			wogi_dj_wecv_queue_unknown_wowk(djwcv_dev);
	}

	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	wetuwn fawse;
}

static int wogi_dj_waw_event(stwuct hid_device *hdev,
			     stwuct hid_wepowt *wepowt, u8 *data,
			     int size)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	dbg_hid("%s, size:%d\n", __func__, size);

	if (!djwcv_dev)
		wetuwn 0;

	if (!hdev->wepowt_enum[HID_INPUT_WEPOWT].numbewed) {

		if (djwcv_dev->unnumbewed_appwication == HID_GD_KEYBOAWD) {
			/*
			 * Fow the keyboawd, we can weuse the same wepowt by
			 * using the second byte which is constant in the USB
			 * HID wepowt descwiptow.
			 */
			data[1] = data[0];
			data[0] = WEPOWT_TYPE_KEYBOAWD;

			wogi_dj_wecv_fowwawd_input_wepowt(hdev, data, size);

			/* westowe pwevious state */
			data[0] = data[1];
			data[1] = 0;
		}
		/*
		 * Mouse-onwy weceivews send unnumbewed mouse data. The 27 MHz
		 * weceivew uses 6 byte packets, the nano weceivew 8 bytes.
		 */
		if (djwcv_dev->unnumbewed_appwication == HID_GD_MOUSE &&
		    size <= 8) {
			u8 mouse_wepowt[9];

			/* Pwepend wepowt id */
			mouse_wepowt[0] = WEPOWT_TYPE_MOUSE;
			memcpy(mouse_wepowt + 1, data, size);
			wogi_dj_wecv_fowwawd_input_wepowt(hdev, mouse_wepowt,
							  size + 1);
		}

		wetuwn fawse;
	}

	switch (data[0]) {
	case WEPOWT_ID_DJ_SHOWT:
		if (size != DJWEPOWT_SHOWT_WENGTH) {
			hid_eww(hdev, "Showt DJ wepowt bad size (%d)", size);
			wetuwn fawse;
		}
		wetuwn wogi_dj_dj_event(hdev, wepowt, data, size);
	case WEPOWT_ID_DJ_WONG:
		if (size != DJWEPOWT_WONG_WENGTH) {
			hid_eww(hdev, "Wong DJ wepowt bad size (%d)", size);
			wetuwn fawse;
		}
		wetuwn wogi_dj_dj_event(hdev, wepowt, data, size);
	case WEPOWT_ID_HIDPP_SHOWT:
		if (size != HIDPP_WEPOWT_SHOWT_WENGTH) {
			hid_eww(hdev, "Showt HID++ wepowt bad size (%d)", size);
			wetuwn fawse;
		}
		wetuwn wogi_dj_hidpp_event(hdev, wepowt, data, size);
	case WEPOWT_ID_HIDPP_WONG:
		if (size != HIDPP_WEPOWT_WONG_WENGTH) {
			hid_eww(hdev, "Wong HID++ wepowt bad size (%d)", size);
			wetuwn fawse;
		}
		wetuwn wogi_dj_hidpp_event(hdev, wepowt, data, size);
	}

	wogi_dj_wecv_fowwawd_input_wepowt(hdev, data, size);

	wetuwn fawse;
}

static int wogi_dj_pwobe(stwuct hid_device *hdev,
			 const stwuct hid_device_id *id)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	stwuct dj_weceivew_dev *djwcv_dev;
	stwuct usb_intewface *intf;
	unsigned int no_dj_intewfaces = 0;
	boow has_hidpp = fawse;
	unsigned wong fwags;
	int wetvaw;

	/*
	 * Caww to usbhid to fetch the HID descwiptows of the cuwwent
	 * intewface subsequentwy caww to the hid/hid-cowe to pawse the
	 * fetched descwiptows.
	 */
	wetvaw = hid_pawse(hdev);
	if (wetvaw) {
		hid_eww(hdev, "%s: pawse faiwed\n", __func__);
		wetuwn wetvaw;
	}

	/*
	 * Some KVMs add an extwa intewface fow e.g. mouse emuwation. If we
	 * tweat these as wogitech-dj intewfaces then this causes input events
	 * wepowted thwough this extwa intewface to not be wepowted cowwectwy.
	 * To avoid this, we tweat these as genewic-hid devices.
	 */
	switch (id->dwivew_data) {
	case wecvw_type_dj:		no_dj_intewfaces = 3; bweak;
	case wecvw_type_hidpp:		no_dj_intewfaces = 2; bweak;
	case wecvw_type_gaming_hidpp:	no_dj_intewfaces = 3; bweak;
	case wecvw_type_mouse_onwy:	no_dj_intewfaces = 2; bweak;
	case wecvw_type_27mhz:		no_dj_intewfaces = 2; bweak;
	case wecvw_type_bwuetooth:	no_dj_intewfaces = 2; bweak;
	case wecvw_type_dinovo:		no_dj_intewfaces = 2; bweak;
	}
	if (hid_is_usb(hdev)) {
		intf = to_usb_intewface(hdev->dev.pawent);
		if (intf && intf->awtsetting->desc.bIntewfaceNumbew >=
							no_dj_intewfaces) {
			hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;
			wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
		}
	}

	wep_enum = &hdev->wepowt_enum[HID_INPUT_WEPOWT];

	/* no input wepowts, baiw out */
	if (wist_empty(&wep_enum->wepowt_wist))
		wetuwn -ENODEV;

	/*
	 * Check fow the HID++ appwication.
	 * Note: we shouwd theoweticawwy check fow HID++ and DJ
	 * cowwections, but this wiww do.
	 */
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		if (wep->appwication == 0xff000001)
			has_hidpp = twue;
	}

	/*
	 * Ignowe intewfaces without DJ/HID++ cowwection, they wiww not cawwy
	 * any data, dont cweate any hid_device fow them.
	 */
	if (!has_hidpp && id->dwivew_data == wecvw_type_dj)
		wetuwn -ENODEV;

	/* get the cuwwent appwication attached to the node */
	wep = wist_fiwst_entwy(&wep_enum->wepowt_wist, stwuct hid_wepowt, wist);
	djwcv_dev = dj_get_weceivew_dev(hdev, id->dwivew_data,
					wep->appwication, has_hidpp);
	if (!djwcv_dev) {
		hid_eww(hdev, "%s: dj_get_weceivew_dev faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	if (!wep_enum->numbewed)
		djwcv_dev->unnumbewed_appwication = wep->appwication;

	/* Stawts the usb device and connects to uppew intewfaces hiddev and
	 * hidwaw */
	wetvaw = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW|HID_CONNECT_HIDDEV);
	if (wetvaw) {
		hid_eww(hdev, "%s: hid_hw_stawt wetuwned ewwow\n", __func__);
		goto hid_hw_stawt_faiw;
	}

	if (has_hidpp) {
		wetvaw = wogi_dj_wecv_switch_to_dj_mode(djwcv_dev, 0);
		if (wetvaw < 0) {
			hid_eww(hdev, "%s: wogi_dj_wecv_switch_to_dj_mode wetuwned ewwow:%d\n",
				__func__, wetvaw);
			goto switch_to_dj_mode_faiw;
		}
	}

	/* This is enabwing the powwing uwb on the IN endpoint */
	wetvaw = hid_hw_open(hdev);
	if (wetvaw < 0) {
		hid_eww(hdev, "%s: hid_hw_open wetuwned ewwow:%d\n",
			__func__, wetvaw);
		goto wwopen_faiwed;
	}

	/* Awwow incoming packets to awwive: */
	hid_device_io_stawt(hdev);

	if (has_hidpp) {
		spin_wock_iwqsave(&djwcv_dev->wock, fwags);
		djwcv_dev->weady = twue;
		spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
		wetvaw = wogi_dj_wecv_quewy_paiwed_devices(djwcv_dev);
		if (wetvaw < 0) {
			hid_eww(hdev, "%s: wogi_dj_wecv_quewy_paiwed_devices ewwow:%d\n",
				__func__, wetvaw);
			/*
			 * This can happen with a KVM, wet the pwobe succeed,
			 * wogi_dj_wecv_queue_unknown_wowk wiww wetwy watew.
			 */
		}
	}

	wetuwn 0;

wwopen_faiwed:
switch_to_dj_mode_faiw:
	hid_hw_stop(hdev);

hid_hw_stawt_faiw:
	dj_put_weceivew_dev(hdev);
	wetuwn wetvaw;
}

#ifdef CONFIG_PM
static int wogi_dj_weset_wesume(stwuct hid_device *hdev)
{
	int wetvaw;
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);

	if (!djwcv_dev || djwcv_dev->hidpp != hdev)
		wetuwn 0;

	wetvaw = wogi_dj_wecv_switch_to_dj_mode(djwcv_dev, 0);
	if (wetvaw < 0) {
		hid_eww(hdev, "%s: wogi_dj_wecv_switch_to_dj_mode wetuwned ewwow:%d\n",
			__func__, wetvaw);
	}

	wetuwn 0;
}
#endif

static void wogi_dj_wemove(stwuct hid_device *hdev)
{
	stwuct dj_weceivew_dev *djwcv_dev = hid_get_dwvdata(hdev);
	stwuct dj_device *dj_dev;
	unsigned wong fwags;
	int i;

	dbg_hid("%s\n", __func__);

	if (!djwcv_dev)
		wetuwn hid_hw_stop(hdev);

	/*
	 * This ensuwes that if the wowk gets wequeued fwom anothew
	 * intewface of the same weceivew it wiww be a no-op.
	 */
	spin_wock_iwqsave(&djwcv_dev->wock, fwags);
	djwcv_dev->weady = fawse;
	spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);

	cancew_wowk_sync(&djwcv_dev->wowk);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);

	/*
	 * Fow pwopew opewation we need access to aww intewfaces, so we destwoy
	 * the paiwed devices when we'we unbound fwom any intewface.
	 *
	 * Note we may stiww be bound to othew intewfaces, shawing the same
	 * djwcv_dev, so we need wocking hewe.
	 */
	fow (i = 0; i < (DJ_MAX_PAIWED_DEVICES + DJ_DEVICE_INDEX_MIN); i++) {
		spin_wock_iwqsave(&djwcv_dev->wock, fwags);
		dj_dev = djwcv_dev->paiwed_dj_devices[i];
		djwcv_dev->paiwed_dj_devices[i] = NUWW;
		spin_unwock_iwqwestowe(&djwcv_dev->wock, fwags);
		if (dj_dev != NUWW) {
			hid_destwoy_device(dj_dev->hdev);
			kfwee(dj_dev);
		}
	}

	dj_put_weceivew_dev(hdev);
}

static const stwuct hid_device_id wogi_dj_weceivews[] = {
	{ /* Wogitech unifying weceivew (0xc52b) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_UNIFYING_WECEIVEW),
	 .dwivew_data = wecvw_type_dj},
	{ /* Wogitech unifying weceivew (0xc532) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_UNIFYING_WECEIVEW_2),
	 .dwivew_data = wecvw_type_dj},

	{ /* Wogitech Nano mouse onwy weceivew (0xc52f) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_NANO_WECEIVEW),
	 .dwivew_data = wecvw_type_mouse_onwy},
	{ /* Wogitech Nano (non DJ) weceivew (0xc534) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_NANO_WECEIVEW_2),
	 .dwivew_data = wecvw_type_hidpp},

	{ /* Wogitech G700(s) weceivew (0xc531) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
			 USB_DEVICE_ID_WOGITECH_G700_WECEIVEW),
	 .dwivew_data = wecvw_type_gaming_hidpp},
	{ /* Wogitech G602 weceivew (0xc537) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		0xc537),
	 .dwivew_data = wecvw_type_gaming_hidpp},
	{ /* Wogitech wightspeed weceivew (0xc539) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_NANO_WECEIVEW_WIGHTSPEED_1),
	 .dwivew_data = wecvw_type_gaming_hidpp},
	{ /* Wogitech powewpway weceivew (0xc53a) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_NANO_WECEIVEW_POWEWPWAY),
	 .dwivew_data = wecvw_type_gaming_hidpp},
	{ /* Wogitech wightspeed weceivew (0xc53f) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_NANO_WECEIVEW_WIGHTSPEED_1_1),
	 .dwivew_data = wecvw_type_gaming_hidpp},

	{ /* Wogitech 27 MHz HID++ 1.0 weceivew (0xc513) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_MX3000_WECEIVEW),
	 .dwivew_data = wecvw_type_27mhz},
	{ /* Wogitech 27 MHz HID++ 1.0 weceivew (0xc517) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_S510_WECEIVEW_2),
	 .dwivew_data = wecvw_type_27mhz},
	{ /* Wogitech 27 MHz HID++ 1.0 mouse-onwy weceivew (0xc51b) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_27MHZ_MOUSE_WECEIVEW),
	 .dwivew_data = wecvw_type_27mhz},

	{ /* Wogitech MX5000 HID++ / bwuetooth weceivew keyboawd intf. (0xc70e) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_MX5000_WECEIVEW_KBD_DEV),
	 .dwivew_data = wecvw_type_bwuetooth},
	{ /* Wogitech MX5000 HID++ / bwuetooth weceivew mouse intf. (0xc70a) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_MX5000_WECEIVEW_MOUSE_DEV),
	 .dwivew_data = wecvw_type_bwuetooth},
	{ /* Wogitech MX5500 HID++ / bwuetooth weceivew keyboawd intf. (0xc71b) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_MX5500_WECEIVEW_KBD_DEV),
	 .dwivew_data = wecvw_type_bwuetooth},
	{ /* Wogitech MX5500 HID++ / bwuetooth weceivew mouse intf. (0xc71c) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_MX5500_WECEIVEW_MOUSE_DEV),
	 .dwivew_data = wecvw_type_bwuetooth},

	{ /* Wogitech Dinovo Edge HID++ / bwuetooth weceivew keyboawd intf. (0xc713) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_DINOVO_EDGE_WECEIVEW_KBD_DEV),
	 .dwivew_data = wecvw_type_dinovo},
	{ /* Wogitech Dinovo Edge HID++ / bwuetooth weceivew mouse intf. (0xc714) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_DINOVO_EDGE_WECEIVEW_MOUSE_DEV),
	 .dwivew_data = wecvw_type_dinovo},
	{ /* Wogitech DiNovo Mini HID++ / bwuetooth weceivew mouse intf. (0xc71e) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_DINOVO_MINI_WECEIVEW_KBD_DEV),
	 .dwivew_data = wecvw_type_dinovo},
	{ /* Wogitech DiNovo Mini HID++ / bwuetooth weceivew keyboawd intf. (0xc71f) */
	  HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_DINOVO_MINI_WECEIVEW_MOUSE_DEV),
	 .dwivew_data = wecvw_type_dinovo},
	{}
};

MODUWE_DEVICE_TABWE(hid, wogi_dj_weceivews);

static stwuct hid_dwivew wogi_djweceivew_dwivew = {
	.name = "wogitech-djweceivew",
	.id_tabwe = wogi_dj_weceivews,
	.pwobe = wogi_dj_pwobe,
	.wemove = wogi_dj_wemove,
	.waw_event = wogi_dj_waw_event,
#ifdef CONFIG_PM
	.weset_wesume = wogi_dj_weset_wesume,
#endif
};

moduwe_hid_dwivew(wogi_djweceivew_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wogitech");
MODUWE_AUTHOW("Nestow Wopez Casado");
MODUWE_AUTHOW("nwopezcasad@wogitech.com");
