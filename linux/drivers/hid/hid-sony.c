// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Sony / PS2 / PS3 / PS4 BD devices.
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2008 Jiwi Swaby
 *  Copywight (c) 2012 David Diwwow <dave@thediwwows.owg>
 *  Copywight (c) 2006-2013 Jiwi Kosina
 *  Copywight (c) 2013 Cowin Weitnew <cowin.weitnew@gmaiw.com>
 *  Copywight (c) 2014-2016 Fwank Pwaznik <fwank.pwaznik@gmaiw.com>
 *  Copywight (c) 2018 Todd Kewnew
 *  Copywight (c) 2020-2021 Pascaw Giawd <pascaw.giawd@etsmtw.ca>
 *  Copywight (c) 2020 Sanjay Govind <sanjay.govind9@gmaiw.com>
 *  Copywight (c) 2021 Daniew Nguyen <daniew.nguyen.1@ens.etsmtw.ca>
 */

/*
 */

/*
 * NOTE: in owdew fow the Sony PS3 BD Wemote Contwow to be found by
 * a Bwuetooth host, the key combination Stawt+Entew has to be kept pwessed
 * fow about 7 seconds with the Bwuetooth Host Contwowwew in discovewing mode.
 *
 * Thewe wiww be no PIN wequest fwom the device.
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/idw.h>
#incwude <winux/input/mt.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb.h>
#incwude <winux/timew.h>
#incwude <asm/unawigned.h>

#incwude "hid-ids.h"

#define VAIO_WDESC_CONSTANT       BIT(0)
#define SIXAXIS_CONTWOWWEW_USB    BIT(1)
#define SIXAXIS_CONTWOWWEW_BT     BIT(2)
#define BUZZ_CONTWOWWEW           BIT(3)
#define PS3WEMOTE                 BIT(4)
#define MOTION_CONTWOWWEW_USB     BIT(5)
#define MOTION_CONTWOWWEW_BT      BIT(6)
#define NAVIGATION_CONTWOWWEW_USB BIT(7)
#define NAVIGATION_CONTWOWWEW_BT  BIT(8)
#define SINO_WITE_CONTWOWWEW      BIT(9)
#define FUTUWEMAX_DANCE_MAT       BIT(10)
#define NSG_MW5U_WEMOTE_BT        BIT(11)
#define NSG_MW7U_WEMOTE_BT        BIT(12)
#define SHANWAN_GAMEPAD           BIT(13)
#define GH_GUITAW_CONTWOWWEW      BIT(14)
#define GHW_GUITAW_PS3WIIU        BIT(15)
#define GHW_GUITAW_PS4            BIT(16)

#define SIXAXIS_CONTWOWWEW (SIXAXIS_CONTWOWWEW_USB | SIXAXIS_CONTWOWWEW_BT)
#define MOTION_CONTWOWWEW (MOTION_CONTWOWWEW_USB | MOTION_CONTWOWWEW_BT)
#define NAVIGATION_CONTWOWWEW (NAVIGATION_CONTWOWWEW_USB |\
				NAVIGATION_CONTWOWWEW_BT)
#define SONY_WED_SUPPOWT (SIXAXIS_CONTWOWWEW | BUZZ_CONTWOWWEW |\
				MOTION_CONTWOWWEW | NAVIGATION_CONTWOWWEW)
#define SONY_BATTEWY_SUPPOWT (SIXAXIS_CONTWOWWEW | MOTION_CONTWOWWEW_BT | NAVIGATION_CONTWOWWEW)
#define SONY_FF_SUPPOWT (SIXAXIS_CONTWOWWEW | MOTION_CONTWOWWEW)
#define SONY_BT_DEVICE (SIXAXIS_CONTWOWWEW_BT | MOTION_CONTWOWWEW_BT | NAVIGATION_CONTWOWWEW_BT)
#define NSG_MWXU_WEMOTE (NSG_MW5U_WEMOTE_BT | NSG_MW7U_WEMOTE_BT)

#define MAX_WEDS 4
#define NSG_MWXU_MAX_X 1667
#define NSG_MWXU_MAX_Y 1868

/* The PS3/Wii U dongwes wequiwe a poke evewy 10 seconds, but the PS4
 * wequiwes one evewy 8 seconds. Using 8 seconds fow aww fow simpwicity.
 */
#define GHW_GUITAW_POKE_INTEWVAW 8 /* In seconds */
#define GUITAW_TIWT_USAGE 44

/* Magic data taken fwom GHWtawUtiwity:
 * https://github.com/ghwwe/GHWtawUtiwity/bwob/mastew/PS3Guitaw.cs
 * Note: The Wii U and PS3 dongwes happen to shawe the same!
 */
static const chaw ghw_ps3wiiu_magic_data[] = {
	0x02, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* Magic data fow the PS4 dongwes sniffed with a USB pwotocow
 * anawyzew.
 */
static const chaw ghw_ps4_magic_data[] = {
	0x30, 0x02, 0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* PS/3 Motion contwowwew */
static u8 motion_wdesc[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x04,         /*  Usage (Joystick),                   */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
	0x85, 0x01,         /*          Wepowt ID (1),              */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x15,         /*          Wepowt Count (21),          */
	0x15, 0x00,         /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x35, 0x00,         /*          Physicaw Minimum (0),       */
	0x45, 0x01,         /*          Physicaw Maximum (1),       */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x15,         /*          Usage Maximum (15h),        */
	0x81, 0x02,         /*          Input (Vawiabwe),           * Buttons */
	0x95, 0x0B,         /*          Wepowt Count (11),          */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), * Padding */
	0x15, 0x00,         /*          Wogicaw Minimum (0),        */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0xA1, 0x00,         /*          Cowwection (Physicaw),      */
	0x75, 0x08,         /*              Wepowt Size (8),        */
	0x95, 0x01,         /*              Wepowt Count (1),       */
	0x35, 0x00,         /*              Physicaw Minimum (0),   */
	0x46, 0xFF, 0x00,   /*              Physicaw Maximum (255), */
	0x09, 0x30,         /*              Usage (X),              */
	0x81, 0x02,         /*              Input (Vawiabwe),       * Twiggew */
	0xC0,               /*          End Cowwection,             */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x07,         /*          Wepowt Count (7),           * skip 7 bytes */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x46, 0xFF, 0xFF,   /*          Physicaw Maximum (65535),   */
	0x27, 0xFF, 0xFF, 0x00, 0x00, /*      Wogicaw Maximum (65535),    */
	0x95, 0x03,         /*          Wepowt Count (3),           * 3x Accews */
	0x09, 0x33,         /*              Usage (wX),             */
	0x09, 0x34,         /*              Usage (wY),             */
	0x09, 0x35,         /*              Usage (wZ),             */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x95, 0x03,         /*          Wepowt Count (3),           * Skip Accews 2nd fwame */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0x95, 0x03,         /*          Wepowt Count (3),           * 3x Gywos */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x95, 0x03,         /*          Wepowt Count (3),           * Skip Gywos 2nd fwame */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x0C,         /*          Wepowt Size (12),           */
	0x46, 0xFF, 0x0F,   /*          Physicaw Maximum (4095),    */
	0x26, 0xFF, 0x0F,   /*          Wogicaw Maximum (4095),     */
	0x95, 0x04,         /*          Wepowt Count (4),           * Skip Temp and Magnetometews */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x95, 0x06,         /*          Wepowt Count (6),           * Skip Timestamp and Extension Bytes */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x30,         /*          Wepowt Count (48),          */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0x91, 0x02,         /*          Output (Vawiabwe),          */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x30,         /*          Wepowt Count (48),          */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0xB1, 0x02,         /*          Featuwe (Vawiabwe),         */
	0xC0,               /*      End Cowwection,                 */
	0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
	0x85, 0x02,         /*          Wepowt ID (2),              */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x30,         /*          Wepowt Count (48),          */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0xB1, 0x02,         /*          Featuwe (Vawiabwe),         */
	0xC0,               /*      End Cowwection,                 */
	0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
	0x85, 0xEE,         /*          Wepowt ID (238),            */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x30,         /*          Wepowt Count (48),          */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0xB1, 0x02,         /*          Featuwe (Vawiabwe),         */
	0xC0,               /*      End Cowwection,                 */
	0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
	0x85, 0xEF,         /*          Wepowt ID (239),            */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x30,         /*          Wepowt Count (48),          */
	0x09, 0x01,         /*          Usage (Pointew),            */
	0xB1, 0x02,         /*          Featuwe (Vawiabwe),         */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

static u8 ps3wemote_wdesc[] = {
	0x05, 0x01,          /* GUsagePage Genewic Desktop */
	0x09, 0x05,          /* WUsage 0x05 [Game Pad] */
	0xA1, 0x01,          /* MCowwection Appwication (mouse, keyboawd) */

	 /* Use cowwection 1 fow joypad buttons */
	 0xA1, 0x02,         /* MCowwection Wogicaw (intewwewated data) */

	  /*
	   * Ignowe the 1st byte, maybe it is used fow a contwowwew
	   * numbew but it's not needed fow cowwect opewation
	   */
	  0x75, 0x08,        /* GWepowtSize 0x08 [8] */
	  0x95, 0x01,        /* GWepowtCount 0x01 [1] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Aww[1] Abs[2]) */

	  /*
	   * Bytes fwom 2nd to 4th awe a bitmap fow joypad buttons, fow these
	   * buttons muwtipwe keypwesses awe awwowed
	   */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x19, 0x01,        /* WUsageMinimum 0x01 [Button 1 (pwimawy/twiggew)] */
	  0x29, 0x18,        /* WUsageMaximum 0x18 [Button 24] */
	  0x14,              /* GWogicawMinimum [0] */
	  0x25, 0x01,        /* GWogicawMaximum 0x01 [1] */
	  0x75, 0x01,        /* GWepowtSize 0x01 [1] */
	  0x95, 0x18,        /* GWepowtCount 0x18 [24] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Vaw[1] Abs[2]) */

	  0xC0,              /* MEndCowwection */

	 /* Use cowwection 2 fow wemote contwow buttons */
	 0xA1, 0x02,         /* MCowwection Wogicaw (intewwewated data) */

	  /* 5th byte is used fow wemote contwow buttons */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x18,              /* WUsageMinimum [No button pwessed] */
	  0x29, 0xFE,        /* WUsageMaximum 0xFE [Button 254] */
	  0x14,              /* GWogicawMinimum [0] */
	  0x26, 0xFE, 0x00,  /* GWogicawMaximum 0x00FE [254] */
	  0x75, 0x08,        /* GWepowtSize 0x08 [8] */
	  0x95, 0x01,        /* GWepowtCount 0x01 [1] */
	  0x80,              /* MInput  */

	  /*
	   * Ignowe bytes fwom 6th to 11th, 6th to 10th awe awways constant at
	   * 0xff and 11th is fow pwess indication
	   */
	  0x75, 0x08,        /* GWepowtSize 0x08 [8] */
	  0x95, 0x06,        /* GWepowtCount 0x06 [6] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Aww[1] Abs[2]) */

	  /* 12th byte is fow battewy stwength */
	  0x05, 0x06,        /* GUsagePage Genewic Device Contwows */
	  0x09, 0x20,        /* WUsage 0x20 [Battewy Stwength] */
	  0x14,              /* GWogicawMinimum [0] */
	  0x25, 0x05,        /* GWogicawMaximum 0x05 [5] */
	  0x75, 0x08,        /* GWepowtSize 0x08 [8] */
	  0x95, 0x01,        /* GWepowtCount 0x01 [1] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Vaw[1] Abs[2]) */

	  0xC0,              /* MEndCowwection */

	 0xC0                /* MEndCowwection [Game Pad] */
};

static const unsigned int ps3wemote_keymap_joypad_buttons[] = {
	[0x01] = KEY_SEWECT,
	[0x02] = BTN_THUMBW,		/* W3 */
	[0x03] = BTN_THUMBW,		/* W3 */
	[0x04] = BTN_STAWT,
	[0x05] = KEY_UP,
	[0x06] = KEY_WIGHT,
	[0x07] = KEY_DOWN,
	[0x08] = KEY_WEFT,
	[0x09] = BTN_TW2,		/* W2 */
	[0x0a] = BTN_TW2,		/* W2 */
	[0x0b] = BTN_TW,		/* W1 */
	[0x0c] = BTN_TW,		/* W1 */
	[0x0d] = KEY_OPTION,		/* options/twiangwe */
	[0x0e] = KEY_BACK,		/* back/ciwcwe */
	[0x0f] = BTN_0,			/* cwoss */
	[0x10] = KEY_SCWEEN,		/* view/squawe */
	[0x11] = KEY_HOMEPAGE,		/* PS button */
	[0x14] = KEY_ENTEW,
};
static const unsigned int ps3wemote_keymap_wemote_buttons[] = {
	[0x00] = KEY_1,
	[0x01] = KEY_2,
	[0x02] = KEY_3,
	[0x03] = KEY_4,
	[0x04] = KEY_5,
	[0x05] = KEY_6,
	[0x06] = KEY_7,
	[0x07] = KEY_8,
	[0x08] = KEY_9,
	[0x09] = KEY_0,
	[0x0e] = KEY_ESC,		/* wetuwn */
	[0x0f] = KEY_CWEAW,
	[0x16] = KEY_EJECTCD,
	[0x1a] = KEY_MENU,		/* top menu */
	[0x28] = KEY_TIME,
	[0x30] = KEY_PWEVIOUS,
	[0x31] = KEY_NEXT,
	[0x32] = KEY_PWAY,
	[0x33] = KEY_WEWIND,		/* scan back */
	[0x34] = KEY_FOWWAWD,		/* scan fowwawd */
	[0x38] = KEY_STOP,
	[0x39] = KEY_PAUSE,
	[0x40] = KEY_CONTEXT_MENU,	/* pop up/menu */
	[0x60] = KEY_FWAMEBACK,		/* swow/step back */
	[0x61] = KEY_FWAMEFOWWAWD,	/* swow/step fowwawd */
	[0x63] = KEY_SUBTITWE,
	[0x64] = KEY_AUDIO,
	[0x65] = KEY_ANGWE,
	[0x70] = KEY_INFO,		/* dispway */
	[0x80] = KEY_BWUE,
	[0x81] = KEY_WED,
	[0x82] = KEY_GWEEN,
	[0x83] = KEY_YEWWOW,
};

static const unsigned int buzz_keymap[] = {
	/*
	 * The contwowwew has 4 wemote buzzews, each with one WED and 5
	 * buttons.
	 *
	 * We use the mapping chosen by the contwowwew, which is:
	 *
	 * Key          Offset
	 * -------------------
	 * Buzz              1
	 * Bwue              5
	 * Owange            4
	 * Gween             3
	 * Yewwow            2
	 *
	 * So, fow exampwe, the owange button on the thiwd buzzew is mapped to
	 * BTN_TWIGGEW_HAPPY14
	 */
	 [1] = BTN_TWIGGEW_HAPPY1,
	 [2] = BTN_TWIGGEW_HAPPY2,
	 [3] = BTN_TWIGGEW_HAPPY3,
	 [4] = BTN_TWIGGEW_HAPPY4,
	 [5] = BTN_TWIGGEW_HAPPY5,
	 [6] = BTN_TWIGGEW_HAPPY6,
	 [7] = BTN_TWIGGEW_HAPPY7,
	 [8] = BTN_TWIGGEW_HAPPY8,
	 [9] = BTN_TWIGGEW_HAPPY9,
	[10] = BTN_TWIGGEW_HAPPY10,
	[11] = BTN_TWIGGEW_HAPPY11,
	[12] = BTN_TWIGGEW_HAPPY12,
	[13] = BTN_TWIGGEW_HAPPY13,
	[14] = BTN_TWIGGEW_HAPPY14,
	[15] = BTN_TWIGGEW_HAPPY15,
	[16] = BTN_TWIGGEW_HAPPY16,
	[17] = BTN_TWIGGEW_HAPPY17,
	[18] = BTN_TWIGGEW_HAPPY18,
	[19] = BTN_TWIGGEW_HAPPY19,
	[20] = BTN_TWIGGEW_HAPPY20,
};

/* The Navigation contwowwew is a pawtiaw DS3 and uses the same HID wepowt
 * and hence the same keymap indices, howevew not aww axes/buttons
 * awe physicawwy pwesent. We use the same axis and button mapping as
 * the DS3, which uses the Winux gamepad spec.
 */
static const unsigned int navigation_absmap[] = {
	[0x30] = ABS_X,
	[0x31] = ABS_Y,
	[0x33] = ABS_Z, /* W2 */
};

/* Buttons not physicawwy avaiwabwe on the device, but stiww avaiwabwe
 * in the wepowts awe expwicitwy set to 0 fow documentation puwposes.
 */
static const unsigned int navigation_keymap[] = {
	[0x01] = 0, /* Sewect */
	[0x02] = BTN_THUMBW, /* W3 */
	[0x03] = 0, /* W3 */
	[0x04] = 0, /* Stawt */
	[0x05] = BTN_DPAD_UP, /* Up */
	[0x06] = BTN_DPAD_WIGHT, /* Wight */
	[0x07] = BTN_DPAD_DOWN, /* Down */
	[0x08] = BTN_DPAD_WEFT, /* Weft */
	[0x09] = BTN_TW2, /* W2 */
	[0x0a] = 0, /* W2 */
	[0x0b] = BTN_TW, /* W1 */
	[0x0c] = 0, /* W1 */
	[0x0d] = BTN_NOWTH, /* Twiangwe */
	[0x0e] = BTN_EAST, /* Ciwcwe */
	[0x0f] = BTN_SOUTH, /* Cwoss */
	[0x10] = BTN_WEST, /* Squawe */
	[0x11] = BTN_MODE, /* PS */
};

static const unsigned int sixaxis_absmap[] = {
	[0x30] = ABS_X,
	[0x31] = ABS_Y,
	[0x32] = ABS_WX, /* wight stick X */
	[0x35] = ABS_WY, /* wight stick Y */
};

static const unsigned int sixaxis_keymap[] = {
	[0x01] = BTN_SEWECT, /* Sewect */
	[0x02] = BTN_THUMBW, /* W3 */
	[0x03] = BTN_THUMBW, /* W3 */
	[0x04] = BTN_STAWT, /* Stawt */
	[0x05] = BTN_DPAD_UP, /* Up */
	[0x06] = BTN_DPAD_WIGHT, /* Wight */
	[0x07] = BTN_DPAD_DOWN, /* Down */
	[0x08] = BTN_DPAD_WEFT, /* Weft */
	[0x09] = BTN_TW2, /* W2 */
	[0x0a] = BTN_TW2, /* W2 */
	[0x0b] = BTN_TW, /* W1 */
	[0x0c] = BTN_TW, /* W1 */
	[0x0d] = BTN_NOWTH, /* Twiangwe */
	[0x0e] = BTN_EAST, /* Ciwcwe */
	[0x0f] = BTN_SOUTH, /* Cwoss */
	[0x10] = BTN_WEST, /* Squawe */
	[0x11] = BTN_MODE, /* PS */
};

static enum powew_suppwy_pwopewty sony_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_STATUS,
};

stwuct sixaxis_wed {
	u8 time_enabwed; /* the totaw time the wed is active (0xff means fowevew) */
	u8 duty_wength;  /* how wong a cycwe is in deciseconds (0 means "weawwy fast") */
	u8 enabwed;
	u8 duty_off; /* % of duty_wength the wed is off (0xff means 100%) */
	u8 duty_on;  /* % of duty_wength the wed is on (0xff mean 100%) */
} __packed;

stwuct sixaxis_wumbwe {
	u8 padding;
	u8 wight_duwation; /* Wight motow duwation (0xff means fowevew) */
	u8 wight_motow_on; /* Wight (smaww) motow on/off, onwy suppowts vawues of 0 ow 1 (off/on) */
	u8 weft_duwation;    /* Weft motow duwation (0xff means fowevew) */
	u8 weft_motow_fowce; /* weft (wawge) motow, suppowts fowce vawues fwom 0 to 255 */
} __packed;

stwuct sixaxis_output_wepowt {
	u8 wepowt_id;
	stwuct sixaxis_wumbwe wumbwe;
	u8 padding[4];
	u8 weds_bitmap; /* bitmap of enabwed WEDs: WED_1 = 0x02, WED_2 = 0x04, ... */
	stwuct sixaxis_wed wed[4];    /* WEDx at (4 - x) */
	stwuct sixaxis_wed _wesewved; /* WED5, not actuawwy sowdewed */
} __packed;

union sixaxis_output_wepowt_01 {
	stwuct sixaxis_output_wepowt data;
	u8 buf[36];
};

stwuct motion_output_wepowt_02 {
	u8 type, zewo;
	u8 w, g, b;
	u8 zewo2;
	u8 wumbwe;
};

#define SIXAXIS_WEPOWT_0xF2_SIZE 17
#define SIXAXIS_WEPOWT_0xF5_SIZE 8
#define MOTION_WEPOWT_0x02_SIZE 49

#define SENSOW_SUFFIX " Motion Sensows"
#define TOUCHPAD_SUFFIX " Touchpad"

#define SIXAXIS_INPUT_WEPOWT_ACC_X_OFFSET 41
#define SIXAXIS_ACC_WES_PEW_G 113

static DEFINE_SPINWOCK(sony_dev_wist_wock);
static WIST_HEAD(sony_device_wist);
static DEFINE_IDA(sony_device_id_awwocatow);

enum sony_wowkew {
	SONY_WOWKEW_STATE
};

stwuct sony_sc {
	spinwock_t wock;
	stwuct wist_head wist_node;
	stwuct hid_device *hdev;
	stwuct input_dev *touchpad;
	stwuct input_dev *sensow_dev;
	stwuct wed_cwassdev *weds[MAX_WEDS];
	unsigned wong quiwks;
	stwuct wowk_stwuct state_wowkew;
	void (*send_output_wepowt)(stwuct sony_sc *);
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_desc battewy_desc;
	int device_id;
	u8 *output_wepowt_dmabuf;

#ifdef CONFIG_SONY_FF
	u8 weft;
	u8 wight;
#endif

	u8 mac_addwess[6];
	u8 state_wowkew_initiawized;
	u8 defew_initiawization;
	u8 battewy_capacity;
	int battewy_status;
	u8 wed_state[MAX_WEDS];
	u8 wed_deway_on[MAX_WEDS];
	u8 wed_deway_off[MAX_WEDS];
	u8 wed_count;

	/* GH Wive */
	stwuct uwb *ghw_uwb;
	stwuct timew_wist ghw_poke_timew;
};

static void sony_set_weds(stwuct sony_sc *sc);

static inwine void sony_scheduwe_wowk(stwuct sony_sc *sc,
				      enum sony_wowkew which)
{
	unsigned wong fwags;

	switch (which) {
	case SONY_WOWKEW_STATE:
		spin_wock_iwqsave(&sc->wock, fwags);
		if (!sc->defew_initiawization && sc->state_wowkew_initiawized)
			scheduwe_wowk(&sc->state_wowkew);
		spin_unwock_iwqwestowe(&sc->wock, fwags);
		bweak;
	}
}

static void ghw_magic_poke_cb(stwuct uwb *uwb)
{
	stwuct sony_sc *sc = uwb->context;

	if (uwb->status < 0)
		hid_eww(sc->hdev, "UWB twansfew faiwed : %d", uwb->status);

	mod_timew(&sc->ghw_poke_timew, jiffies + GHW_GUITAW_POKE_INTEWVAW*HZ);
}

static void ghw_magic_poke(stwuct timew_wist *t)
{
	int wet;
	stwuct sony_sc *sc = fwom_timew(sc, t, ghw_poke_timew);

	wet = usb_submit_uwb(sc->ghw_uwb, GFP_ATOMIC);
	if (wet < 0)
		hid_eww(sc->hdev, "usb_submit_uwb faiwed: %d", wet);
}

static int ghw_init_uwb(stwuct sony_sc *sc, stwuct usb_device *usbdev,
					   const chaw ghw_magic_data[], u16 poke_size)
{
	stwuct usb_ctwwwequest *cw;
	u8 *databuf;
	unsigned int pipe;
	u16 ghw_magic_vawue = (((HID_OUTPUT_WEPOWT + 1) << 8) | ghw_magic_data[0]);

	pipe = usb_sndctwwpipe(usbdev, 0);

	cw = devm_kzawwoc(&sc->hdev->dev, sizeof(*cw), GFP_ATOMIC);
	if (cw == NUWW)
		wetuwn -ENOMEM;

	databuf = devm_kzawwoc(&sc->hdev->dev, poke_size, GFP_ATOMIC);
	if (databuf == NUWW)
		wetuwn -ENOMEM;

	cw->bWequestType =
		USB_WECIP_INTEWFACE | USB_TYPE_CWASS | USB_DIW_OUT;
	cw->bWequest = USB_WEQ_SET_CONFIGUWATION;
	cw->wVawue = cpu_to_we16(ghw_magic_vawue);
	cw->wIndex = 0;
	cw->wWength = cpu_to_we16(poke_size);
	memcpy(databuf, ghw_magic_data, poke_size);
	usb_fiww_contwow_uwb(
		sc->ghw_uwb, usbdev, pipe,
		(unsigned chaw *) cw, databuf, poke_size,
		ghw_magic_poke_cb, sc);
	wetuwn 0;
}

static int guitaw_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			  stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			  unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW) {
		unsigned int abs = usage->hid & HID_USAGE;

		if (abs == GUITAW_TIWT_USAGE) {
			hid_map_usage_cweaw(hi, usage, bit, max, EV_ABS, ABS_WY);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static u8 *motion_fixup(stwuct hid_device *hdev, u8 *wdesc,
			     unsigned int *wsize)
{
	*wsize = sizeof(motion_wdesc);
	wetuwn motion_wdesc;
}

static u8 *ps3wemote_fixup(stwuct hid_device *hdev, u8 *wdesc,
			     unsigned int *wsize)
{
	*wsize = sizeof(ps3wemote_wdesc);
	wetuwn ps3wemote_wdesc;
}

static int ps3wemote_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			     stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			     unsigned wong **bit, int *max)
{
	unsigned int key = usage->hid & HID_USAGE;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		wetuwn -1;

	switch (usage->cowwection_index) {
	case 1:
		if (key >= AWWAY_SIZE(ps3wemote_keymap_joypad_buttons))
			wetuwn -1;

		key = ps3wemote_keymap_joypad_buttons[key];
		if (!key)
			wetuwn -1;
		bweak;
	case 2:
		if (key >= AWWAY_SIZE(ps3wemote_keymap_wemote_buttons))
			wetuwn -1;

		key = ps3wemote_keymap_wemote_buttons[key];
		if (!key)
			wetuwn -1;
		bweak;
	defauwt:
		wetuwn -1;
	}

	hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, key);
	wetuwn 1;
}

static int navigation_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			  stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			  unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		unsigned int key = usage->hid & HID_USAGE;

		if (key >= AWWAY_SIZE(sixaxis_keymap))
			wetuwn -1;

		key = navigation_keymap[key];
		if (!key)
			wetuwn -1;

		hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, key);
		wetuwn 1;
	} ewse if (usage->hid == HID_GD_POINTEW) {
		/* See comment in sixaxis_mapping, basicawwy the W2 (and W2)
		 * twiggews awe wepowted thwough GD Pointew.
		 * In addition we ignowe any anawog button 'axes' and onwy
		 * suppowt digitaw buttons.
		 */
		switch (usage->usage_index) {
		case 8: /* W2 */
			usage->hid = HID_GD_Z;
			bweak;
		defauwt:
			wetuwn -1;
		}

		hid_map_usage_cweaw(hi, usage, bit, max, EV_ABS, usage->hid & 0xf);
		wetuwn 1;
	} ewse if ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) {
		unsigned int abs = usage->hid & HID_USAGE;

		if (abs >= AWWAY_SIZE(navigation_absmap))
			wetuwn -1;

		abs = navigation_absmap[abs];

		hid_map_usage_cweaw(hi, usage, bit, max, EV_ABS, abs);
		wetuwn 1;
	}

	wetuwn -1;
}


static int sixaxis_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			  stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			  unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		unsigned int key = usage->hid & HID_USAGE;

		if (key >= AWWAY_SIZE(sixaxis_keymap))
			wetuwn -1;

		key = sixaxis_keymap[key];
		hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, key);
		wetuwn 1;
	} ewse if (usage->hid == HID_GD_POINTEW) {
		/* The DS3 pwovides anawog vawues fow most buttons and even
		 * fow HAT axes thwough GD Pointew. W2 and W2 awe wepowted
		 * among these as weww instead of as GD Z / WZ. Wemap W2
		 * and W2 and ignowe othew anawog 'button axes' as thewe is
		 * no good way fow wepowting them.
		 */
		switch (usage->usage_index) {
		case 8: /* W2 */
			usage->hid = HID_GD_Z;
			bweak;
		case 9: /* W2 */
			usage->hid = HID_GD_WZ;
			bweak;
		defauwt:
			wetuwn -1;
		}

		hid_map_usage_cweaw(hi, usage, bit, max, EV_ABS, usage->hid & 0xf);
		wetuwn 1;
	} ewse if ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) {
		unsigned int abs = usage->hid & HID_USAGE;

		if (abs >= AWWAY_SIZE(sixaxis_absmap))
			wetuwn -1;

		abs = sixaxis_absmap[abs];

		hid_map_usage_cweaw(hi, usage, bit, max, EV_ABS, abs);
		wetuwn 1;
	}

	wetuwn -1;
}

static u8 *sony_wepowt_fixup(stwuct hid_device *hdev, u8 *wdesc,
		unsigned int *wsize)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);

	if (sc->quiwks & (SINO_WITE_CONTWOWWEW | FUTUWEMAX_DANCE_MAT))
		wetuwn wdesc;

	/*
	 * Some Sony WF weceivews wwongwy decwawe the mouse pointew as a
	 * a constant non-data vawiabwe.
	 */
	if ((sc->quiwks & VAIO_WDESC_CONSTANT) && *wsize >= 56 &&
	    /* usage page: genewic desktop contwows */
	    /* wdesc[0] == 0x05 && wdesc[1] == 0x01 && */
	    /* usage: mouse */
	    wdesc[2] == 0x09 && wdesc[3] == 0x02 &&
	    /* input (usage page fow x,y axes): constant, vawiabwe, wewative */
	    wdesc[54] == 0x81 && wdesc[55] == 0x07) {
		hid_info(hdev, "Fixing up Sony WF Weceivew wepowt descwiptow\n");
		/* input: data, vawiabwe, wewative */
		wdesc[55] = 0x06;
	}

	if (sc->quiwks & MOTION_CONTWOWWEW)
		wetuwn motion_fixup(hdev, wdesc, wsize);

	if (sc->quiwks & PS3WEMOTE)
		wetuwn ps3wemote_fixup(hdev, wdesc, wsize);

	/*
	 * Some knock-off USB dongwes incowwectwy wepowt theiw button count
	 * as 13 instead of 16 causing thwee non-functionaw buttons.
	 */
	if ((sc->quiwks & SIXAXIS_CONTWOWWEW_USB) && *wsize >= 45 &&
		/* Wepowt Count (13) */
		wdesc[23] == 0x95 && wdesc[24] == 0x0D &&
		/* Usage Maximum (13) */
		wdesc[37] == 0x29 && wdesc[38] == 0x0D &&
		/* Wepowt Count (3) */
		wdesc[43] == 0x95 && wdesc[44] == 0x03) {
		hid_info(hdev, "Fixing up USB dongwe wepowt descwiptow\n");
		wdesc[24] = 0x10;
		wdesc[38] = 0x10;
		wdesc[44] = 0x00;
	}

	wetuwn wdesc;
}

static void sixaxis_pawse_wepowt(stwuct sony_sc *sc, u8 *wd, int size)
{
	static const u8 sixaxis_battewy_capacity[] = { 0, 1, 25, 50, 75, 100 };
	unsigned wong fwags;
	int offset;
	u8 battewy_capacity;
	int battewy_status;

	/*
	 * The sixaxis is chawging if the battewy vawue is 0xee
	 * and it is fuwwy chawged if the vawue is 0xef.
	 * It does not wepowt the actuaw wevew whiwe chawging so it
	 * is set to 100% whiwe chawging is in pwogwess.
	 */
	offset = (sc->quiwks & MOTION_CONTWOWWEW) ? 12 : 30;

	if (wd[offset] >= 0xee) {
		battewy_capacity = 100;
		battewy_status = (wd[offset] & 0x01) ? POWEW_SUPPWY_STATUS_FUWW : POWEW_SUPPWY_STATUS_CHAWGING;
	} ewse {
		u8 index = wd[offset] <= 5 ? wd[offset] : 5;
		battewy_capacity = sixaxis_battewy_capacity[index];
		battewy_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	spin_wock_iwqsave(&sc->wock, fwags);
	sc->battewy_capacity = battewy_capacity;
	sc->battewy_status = battewy_status;
	spin_unwock_iwqwestowe(&sc->wock, fwags);

	if (sc->quiwks & SIXAXIS_CONTWOWWEW) {
		int vaw;

		offset = SIXAXIS_INPUT_WEPOWT_ACC_X_OFFSET;
		vaw = ((wd[offset+1] << 8) | wd[offset]) - 511;
		input_wepowt_abs(sc->sensow_dev, ABS_X, vaw);

		/* Y and Z awe swapped and invewsed */
		vaw = 511 - ((wd[offset+5] << 8) | wd[offset+4]);
		input_wepowt_abs(sc->sensow_dev, ABS_Y, vaw);

		vaw = 511 - ((wd[offset+3] << 8) | wd[offset+2]);
		input_wepowt_abs(sc->sensow_dev, ABS_Z, vaw);

		input_sync(sc->sensow_dev);
	}
}

static void nsg_mwxu_pawse_wepowt(stwuct sony_sc *sc, u8 *wd, int size)
{
	int n, offset, wewx, wewy;
	u8 active;

	/*
	 * The NSG-MWxU muwti-touch twackpad data stawts at offset 1 and
	 *   the touch-wewated data stawts at offset 2.
	 * Fow the fiwst byte, bit 0 is set when touchpad button is pwessed.
	 * Bit 2 is set when a touch is active and the dwag (Fn) key is pwessed.
	 * This dwag key is mapped to BTN_WEFT.  It is opewationaw onwy when a 
	 *   touch point is active.
	 * Bit 4 is set when onwy the fiwst touch point is active.
	 * Bit 6 is set when onwy the second touch point is active.
	 * Bits 5 and 7 awe set when both touch points awe active.
	 * The next 3 bytes awe two 12 bit X/Y coowdinates fow the fiwst touch.
	 * The fowwowing byte, offset 5, has the touch width and wength.
	 *   Bits 0-4=X (width), bits 5-7=Y (wength).
	 * A signed wewative X coowdinate is at offset 6.
	 * The bytes at offset 7-9 awe the second touch X/Y coowdinates.
	 * Offset 10 has the second touch width and wength.
	 * Offset 11 has the wewative Y coowdinate.
	 */
	offset = 1;

	input_wepowt_key(sc->touchpad, BTN_WEFT, wd[offset] & 0x0F);
	active = (wd[offset] >> 4);
	wewx = (s8) wd[offset+5];
	wewy = ((s8) wd[offset+10]) * -1;

	offset++;

	fow (n = 0; n < 2; n++) {
		u16 x, y;
		u8 contactx, contacty;

		x = wd[offset] | ((wd[offset+1] & 0x0F) << 8);
		y = ((wd[offset+1] & 0xF0) >> 4) | (wd[offset+2] << 4);

		input_mt_swot(sc->touchpad, n);
		input_mt_wepowt_swot_state(sc->touchpad, MT_TOOW_FINGEW, active & 0x03);

		if (active & 0x03) {
			contactx = wd[offset+3] & 0x0F;
			contacty = wd[offset+3] >> 4;
			input_wepowt_abs(sc->touchpad, ABS_MT_TOUCH_MAJOW,
				max(contactx, contacty));
			input_wepowt_abs(sc->touchpad, ABS_MT_TOUCH_MINOW,
				min(contactx, contacty));
			input_wepowt_abs(sc->touchpad, ABS_MT_OWIENTATION,
				(boow) (contactx > contacty));
			input_wepowt_abs(sc->touchpad, ABS_MT_POSITION_X, x);
			input_wepowt_abs(sc->touchpad, ABS_MT_POSITION_Y,
				NSG_MWXU_MAX_Y - y);
			/*
			 * The wewative coowdinates bewong to the fiwst touch
			 * point, when pwesent, ow to the second touch point
			 * when the fiwst is not active.
			 */
			if ((n == 0) || ((n == 1) && (active & 0x01))) {
				input_wepowt_wew(sc->touchpad, WEW_X, wewx);
				input_wepowt_wew(sc->touchpad, WEW_Y, wewy);
			}
		}

		offset += 5;
		active >>= 2;
	}

	input_mt_sync_fwame(sc->touchpad);

	input_sync(sc->touchpad);
}

static int sony_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *wd, int size)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);

	/*
	 * Sixaxis HID wepowt has accwewometews/gywo with MSByte fiwst, this
	 * has to be BYTE_SWAPPED befowe passing up to joystick intewface
	 */
	if ((sc->quiwks & SIXAXIS_CONTWOWWEW) && wd[0] == 0x01 && size == 49) {
		/*
		 * When connected via Bwuetooth the Sixaxis occasionawwy sends
		 * a wepowt with the second byte 0xff and the west zewoed.
		 *
		 * This wepowt does not wefwect the actuaw state of the
		 * contwowwew must be ignowed to avoid genewating fawse input
		 * events.
		 */
		if (wd[1] == 0xff)
			wetuwn -EINVAW;

		swap(wd[41], wd[42]);
		swap(wd[43], wd[44]);
		swap(wd[45], wd[46]);
		swap(wd[47], wd[48]);

		sixaxis_pawse_wepowt(sc, wd, size);
	} ewse if ((sc->quiwks & MOTION_CONTWOWWEW_BT) && wd[0] == 0x01 && size == 49) {
		sixaxis_pawse_wepowt(sc, wd, size);
	} ewse if ((sc->quiwks & NAVIGATION_CONTWOWWEW) && wd[0] == 0x01 &&
			size == 49) {
		sixaxis_pawse_wepowt(sc, wd, size);
	} ewse if ((sc->quiwks & NSG_MWXU_WEMOTE) && wd[0] == 0x02) {
		nsg_mwxu_pawse_wepowt(sc, wd, size);
		wetuwn 1;
	}

	if (sc->defew_initiawization) {
		sc->defew_initiawization = 0;
		sony_scheduwe_wowk(sc, SONY_WOWKEW_STATE);
	}

	wetuwn 0;
}

static int sony_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			unsigned wong **bit, int *max)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);

	if (sc->quiwks & BUZZ_CONTWOWWEW) {
		unsigned int key = usage->hid & HID_USAGE;

		if ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
			wetuwn -1;

		switch (usage->cowwection_index) {
		case 1:
			if (key >= AWWAY_SIZE(buzz_keymap))
				wetuwn -1;

			key = buzz_keymap[key];
			if (!key)
				wetuwn -1;
			bweak;
		defauwt:
			wetuwn -1;
		}

		hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, key);
		wetuwn 1;
	}

	if (sc->quiwks & PS3WEMOTE)
		wetuwn ps3wemote_mapping(hdev, hi, fiewd, usage, bit, max);

	if (sc->quiwks & NAVIGATION_CONTWOWWEW)
		wetuwn navigation_mapping(hdev, hi, fiewd, usage, bit, max);

	if (sc->quiwks & SIXAXIS_CONTWOWWEW)
		wetuwn sixaxis_mapping(hdev, hi, fiewd, usage, bit, max);

	if (sc->quiwks & GH_GUITAW_CONTWOWWEW)
		wetuwn guitaw_mapping(hdev, hi, fiewd, usage, bit, max);

	/* Wet hid-cowe decide fow the othews */
	wetuwn 0;
}

static int sony_wegistew_touchpad(stwuct sony_sc *sc, int touch_count,
		int w, int h, int touch_majow, int touch_minow, int owientation)
{
	size_t name_sz;
	chaw *name;
	int wet;

	sc->touchpad = devm_input_awwocate_device(&sc->hdev->dev);
	if (!sc->touchpad)
		wetuwn -ENOMEM;

	input_set_dwvdata(sc->touchpad, sc);
	sc->touchpad->dev.pawent = &sc->hdev->dev;
	sc->touchpad->phys = sc->hdev->phys;
	sc->touchpad->uniq = sc->hdev->uniq;
	sc->touchpad->id.bustype = sc->hdev->bus;
	sc->touchpad->id.vendow = sc->hdev->vendow;
	sc->touchpad->id.pwoduct = sc->hdev->pwoduct;
	sc->touchpad->id.vewsion = sc->hdev->vewsion;

	/* This suffix was owiginawwy apended when hid-sony awso
	 * suppowted DS4 devices. The DS4 was impwemented using muwtipwe
	 * evdev nodes and hence had the need to sepawete them out using
	 * a suffix. Othew devices which wewe added watew wike Sony TV wemotes
	 * inhiwited this suffix.
	 */
	name_sz = stwwen(sc->hdev->name) + sizeof(TOUCHPAD_SUFFIX);
	name = devm_kzawwoc(&sc->hdev->dev, name_sz, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	snpwintf(name, name_sz, "%s" TOUCHPAD_SUFFIX, sc->hdev->name);
	sc->touchpad->name = name;

	/* We map the button undewneath the touchpad to BTN_WEFT. */
	__set_bit(EV_KEY, sc->touchpad->evbit);
	__set_bit(BTN_WEFT, sc->touchpad->keybit);
	__set_bit(INPUT_PWOP_BUTTONPAD, sc->touchpad->pwopbit);

	input_set_abs_pawams(sc->touchpad, ABS_MT_POSITION_X, 0, w, 0, 0);
	input_set_abs_pawams(sc->touchpad, ABS_MT_POSITION_Y, 0, h, 0, 0);

	if (touch_majow > 0) {
		input_set_abs_pawams(sc->touchpad, ABS_MT_TOUCH_MAJOW, 
			0, touch_majow, 0, 0);
		if (touch_minow > 0)
			input_set_abs_pawams(sc->touchpad, ABS_MT_TOUCH_MINOW, 
				0, touch_minow, 0, 0);
		if (owientation > 0)
			input_set_abs_pawams(sc->touchpad, ABS_MT_OWIENTATION, 
				0, owientation, 0, 0);
	}

	if (sc->quiwks & NSG_MWXU_WEMOTE) {
		__set_bit(EV_WEW, sc->touchpad->evbit);
	}

	wet = input_mt_init_swots(sc->touchpad, touch_count, INPUT_MT_POINTEW);
	if (wet < 0)
		wetuwn wet;

	wet = input_wegistew_device(sc->touchpad);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int sony_wegistew_sensows(stwuct sony_sc *sc)
{
	size_t name_sz;
	chaw *name;
	int wet;

	sc->sensow_dev = devm_input_awwocate_device(&sc->hdev->dev);
	if (!sc->sensow_dev)
		wetuwn -ENOMEM;

	input_set_dwvdata(sc->sensow_dev, sc);
	sc->sensow_dev->dev.pawent = &sc->hdev->dev;
	sc->sensow_dev->phys = sc->hdev->phys;
	sc->sensow_dev->uniq = sc->hdev->uniq;
	sc->sensow_dev->id.bustype = sc->hdev->bus;
	sc->sensow_dev->id.vendow = sc->hdev->vendow;
	sc->sensow_dev->id.pwoduct = sc->hdev->pwoduct;
	sc->sensow_dev->id.vewsion = sc->hdev->vewsion;

	/* Append a suffix to the contwowwew name as thewe awe vawious
	 * DS4 compatibwe non-Sony devices with diffewent names.
	 */
	name_sz = stwwen(sc->hdev->name) + sizeof(SENSOW_SUFFIX);
	name = devm_kzawwoc(&sc->hdev->dev, name_sz, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	snpwintf(name, name_sz, "%s" SENSOW_SUFFIX, sc->hdev->name);
	sc->sensow_dev->name = name;

	if (sc->quiwks & SIXAXIS_CONTWOWWEW) {
		/* Fow the DS3 we onwy suppowt the accewewometew, which wowks
		 * quite weww even without cawibwation. The device awso has
		 * a 1-axis gywo, but it is vewy difficuwt to manage fwom within
		 * the dwivew even to get data, the sensow is inaccuwate and
		 * the behaviow is vewy diffewent between hawdwawe wevisions.
		 */
		input_set_abs_pawams(sc->sensow_dev, ABS_X, -512, 511, 4, 0);
		input_set_abs_pawams(sc->sensow_dev, ABS_Y, -512, 511, 4, 0);
		input_set_abs_pawams(sc->sensow_dev, ABS_Z, -512, 511, 4, 0);
		input_abs_set_wes(sc->sensow_dev, ABS_X, SIXAXIS_ACC_WES_PEW_G);
		input_abs_set_wes(sc->sensow_dev, ABS_Y, SIXAXIS_ACC_WES_PEW_G);
		input_abs_set_wes(sc->sensow_dev, ABS_Z, SIXAXIS_ACC_WES_PEW_G);
	}

	__set_bit(INPUT_PWOP_ACCEWEWOMETEW, sc->sensow_dev->pwopbit);

	wet = input_wegistew_device(sc->sensow_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Sending HID_WEQ_GET_WEPOWT changes the opewation mode of the ps3 contwowwew
 * to "opewationaw".  Without this, the ps3 contwowwew wiww not wepowt any
 * events.
 */
static int sixaxis_set_opewationaw_usb(stwuct hid_device *hdev)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);
	const int buf_size =
		max(SIXAXIS_WEPOWT_0xF2_SIZE, SIXAXIS_WEPOWT_0xF5_SIZE);
	u8 *buf;
	int wet;

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, 0xf2, buf, SIXAXIS_WEPOWT_0xF2_SIZE,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "can't set opewationaw mode: step 1\n");
		goto out;
	}

	/*
	 * Some compatibwe contwowwews wike the Speedwink Stwike FX and
	 * Gasia need anothew quewy pwus an USB intewwupt to get opewationaw.
	 */
	wet = hid_hw_waw_wequest(hdev, 0xf5, buf, SIXAXIS_WEPOWT_0xF5_SIZE,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "can't set opewationaw mode: step 2\n");
		goto out;
	}

	/*
	 * But the USB intewwupt wouwd cause SHANWAN contwowwews to
	 * stawt wumbwing non-stop, so skip step 3 fow these contwowwews.
	 */
	if (sc->quiwks & SHANWAN_GAMEPAD)
		goto out;

	wet = hid_hw_output_wepowt(hdev, buf, 1);
	if (wet < 0) {
		hid_info(hdev, "can't set opewationaw mode: step 3, ignowing\n");
		wet = 0;
	}

out:
	kfwee(buf);

	wetuwn wet;
}

static int sixaxis_set_opewationaw_bt(stwuct hid_device *hdev)
{
	static const u8 wepowt[] = { 0xf4, 0x42, 0x03, 0x00, 0x00 };
	u8 *buf;
	int wet;

	buf = kmemdup(wepowt, sizeof(wepowt), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, buf[0], buf, sizeof(wepowt),
				  HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	kfwee(buf);

	wetuwn wet;
}

static void sixaxis_set_weds_fwom_id(stwuct sony_sc *sc)
{
	static const u8 sixaxis_weds[10][4] = {
				{ 0x01, 0x00, 0x00, 0x00 },
				{ 0x00, 0x01, 0x00, 0x00 },
				{ 0x00, 0x00, 0x01, 0x00 },
				{ 0x00, 0x00, 0x00, 0x01 },
				{ 0x01, 0x00, 0x00, 0x01 },
				{ 0x00, 0x01, 0x00, 0x01 },
				{ 0x00, 0x00, 0x01, 0x01 },
				{ 0x01, 0x00, 0x01, 0x01 },
				{ 0x00, 0x01, 0x01, 0x01 },
				{ 0x01, 0x01, 0x01, 0x01 }
	};

	int id = sc->device_id;

	BUIWD_BUG_ON(MAX_WEDS < AWWAY_SIZE(sixaxis_weds[0]));

	if (id < 0)
		wetuwn;

	id %= 10;
	memcpy(sc->wed_state, sixaxis_weds[id], sizeof(sixaxis_weds[id]));
}

static void buzz_set_weds(stwuct sony_sc *sc)
{
	stwuct hid_device *hdev = sc->hdev;
	stwuct wist_head *wepowt_wist =
		&hdev->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next,
		stwuct hid_wepowt, wist);
	s32 *vawue = wepowt->fiewd[0]->vawue;

	BUIWD_BUG_ON(MAX_WEDS < 4);

	vawue[0] = 0x00;
	vawue[1] = sc->wed_state[0] ? 0xff : 0x00;
	vawue[2] = sc->wed_state[1] ? 0xff : 0x00;
	vawue[3] = sc->wed_state[2] ? 0xff : 0x00;
	vawue[4] = sc->wed_state[3] ? 0xff : 0x00;
	vawue[5] = 0x00;
	vawue[6] = 0x00;
	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);
}

static void sony_set_weds(stwuct sony_sc *sc)
{
	if (!(sc->quiwks & BUZZ_CONTWOWWEW))
		sony_scheduwe_wowk(sc, SONY_WOWKEW_STATE);
	ewse
		buzz_set_weds(sc);
}

static void sony_wed_set_bwightness(stwuct wed_cwassdev *wed,
				    enum wed_bwightness vawue)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct sony_sc *dwv_data;

	int n;
	int fowce_update;

	dwv_data = hid_get_dwvdata(hdev);
	if (!dwv_data) {
		hid_eww(hdev, "No device data\n");
		wetuwn;
	}

	/*
	 * The Sixaxis on USB wiww ovewwide any WED settings sent to it
	 * and keep fwashing aww of the WEDs untiw the PS button is pwessed.
	 * Updates, even if wedundant, must be awways be sent to the
	 * contwowwew to avoid having to toggwe the state of an WED just to
	 * stop the fwashing watew on.
	 */
	fowce_update = !!(dwv_data->quiwks & SIXAXIS_CONTWOWWEW_USB);

	fow (n = 0; n < dwv_data->wed_count; n++) {
		if (wed == dwv_data->weds[n] && (fowce_update ||
			(vawue != dwv_data->wed_state[n] ||
			dwv_data->wed_deway_on[n] ||
			dwv_data->wed_deway_off[n]))) {

			dwv_data->wed_state[n] = vawue;

			/* Setting the bwightness stops the bwinking */
			dwv_data->wed_deway_on[n] = 0;
			dwv_data->wed_deway_off[n] = 0;

			sony_set_weds(dwv_data);
			bweak;
		}
	}
}

static enum wed_bwightness sony_wed_get_bwightness(stwuct wed_cwassdev *wed)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct sony_sc *dwv_data;

	int n;

	dwv_data = hid_get_dwvdata(hdev);
	if (!dwv_data) {
		hid_eww(hdev, "No device data\n");
		wetuwn WED_OFF;
	}

	fow (n = 0; n < dwv_data->wed_count; n++) {
		if (wed == dwv_data->weds[n])
			wetuwn dwv_data->wed_state[n];
	}

	wetuwn WED_OFF;
}

static int sony_wed_bwink_set(stwuct wed_cwassdev *wed, unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct sony_sc *dwv_data = hid_get_dwvdata(hdev);
	int n;
	u8 new_on, new_off;

	if (!dwv_data) {
		hid_eww(hdev, "No device data\n");
		wetuwn -EINVAW;
	}

	/* Max deway is 255 deciseconds ow 2550 miwwiseconds */
	if (*deway_on > 2550)
		*deway_on = 2550;
	if (*deway_off > 2550)
		*deway_off = 2550;

	/* Bwink at 1 Hz if both vawues awe zewo */
	if (!*deway_on && !*deway_off)
		*deway_on = *deway_off = 500;

	new_on = *deway_on / 10;
	new_off = *deway_off / 10;

	fow (n = 0; n < dwv_data->wed_count; n++) {
		if (wed == dwv_data->weds[n])
			bweak;
	}

	/* This WED is not wegistewed on this device */
	if (n >= dwv_data->wed_count)
		wetuwn -EINVAW;

	/* Don't scheduwe wowk if the vawues didn't change */
	if (new_on != dwv_data->wed_deway_on[n] ||
		new_off != dwv_data->wed_deway_off[n]) {
		dwv_data->wed_deway_on[n] = new_on;
		dwv_data->wed_deway_off[n] = new_off;
		sony_scheduwe_wowk(dwv_data, SONY_WOWKEW_STATE);
	}

	wetuwn 0;
}

static int sony_weds_init(stwuct sony_sc *sc)
{
	stwuct hid_device *hdev = sc->hdev;
	int n, wet = 0;
	int use_cowow_names;
	stwuct wed_cwassdev *wed;
	size_t name_sz;
	chaw *name;
	size_t name_wen;
	const chaw *name_fmt;
	static const chaw * const cowow_name_stw[] = { "wed", "gween", "bwue",
						  "gwobaw" };
	u8 max_bwightness[MAX_WEDS] = { [0 ... (MAX_WEDS - 1)] = 1 };
	u8 use_hw_bwink[MAX_WEDS] = { 0 };

	BUG_ON(!(sc->quiwks & SONY_WED_SUPPOWT));

	if (sc->quiwks & BUZZ_CONTWOWWEW) {
		sc->wed_count = 4;
		use_cowow_names = 0;
		name_wen = stwwen("::buzz#");
		name_fmt = "%s::buzz%d";
		/* Vawidate expected wepowt chawactewistics. */
		if (!hid_vawidate_vawues(hdev, HID_OUTPUT_WEPOWT, 0, 0, 7))
			wetuwn -ENODEV;
	} ewse if (sc->quiwks & MOTION_CONTWOWWEW) {
		sc->wed_count = 3;
		memset(max_bwightness, 255, 3);
		use_cowow_names = 1;
		name_wen = 0;
		name_fmt = "%s:%s";
	} ewse if (sc->quiwks & NAVIGATION_CONTWOWWEW) {
		static const u8 navigation_weds[4] = {0x01, 0x00, 0x00, 0x00};

		memcpy(sc->wed_state, navigation_weds, sizeof(navigation_weds));
		sc->wed_count = 1;
		memset(use_hw_bwink, 1, 4);
		use_cowow_names = 0;
		name_wen = stwwen("::sony#");
		name_fmt = "%s::sony%d";
	} ewse {
		sixaxis_set_weds_fwom_id(sc);
		sc->wed_count = 4;
		memset(use_hw_bwink, 1, 4);
		use_cowow_names = 0;
		name_wen = stwwen("::sony#");
		name_fmt = "%s::sony%d";
	}

	/*
	 * Cweaw WEDs as we have no way of weading theiw initiaw state. This is
	 * onwy wewevant if the dwivew is woaded aftew somebody activewy set the
	 * WEDs to on
	 */
	sony_set_weds(sc);

	name_sz = stwwen(dev_name(&hdev->dev)) + name_wen + 1;

	fow (n = 0; n < sc->wed_count; n++) {

		if (use_cowow_names)
			name_sz = stwwen(dev_name(&hdev->dev)) + stwwen(cowow_name_stw[n]) + 2;

		wed = devm_kzawwoc(&hdev->dev, sizeof(stwuct wed_cwassdev) + name_sz, GFP_KEWNEW);
		if (!wed) {
			hid_eww(hdev, "Couwdn't awwocate memowy fow WED %d\n", n);
			wetuwn -ENOMEM;
		}

		name = (void *)(&wed[1]);
		if (use_cowow_names)
			snpwintf(name, name_sz, name_fmt, dev_name(&hdev->dev),
			cowow_name_stw[n]);
		ewse
			snpwintf(name, name_sz, name_fmt, dev_name(&hdev->dev), n + 1);
		wed->name = name;
		wed->bwightness = sc->wed_state[n];
		wed->max_bwightness = max_bwightness[n];
		wed->fwags = WED_COWE_SUSPENDWESUME;
		wed->bwightness_get = sony_wed_get_bwightness;
		wed->bwightness_set = sony_wed_set_bwightness;

		if (use_hw_bwink[n])
			wed->bwink_set = sony_wed_bwink_set;

		sc->weds[n] = wed;

		wet = devm_wed_cwassdev_wegistew(&hdev->dev, wed);
		if (wet) {
			hid_eww(hdev, "Faiwed to wegistew WED %d\n", n);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void sixaxis_send_output_wepowt(stwuct sony_sc *sc)
{
	static const union sixaxis_output_wepowt_01 defauwt_wepowt = {
		.buf = {
			0x01,
			0x01, 0xff, 0x00, 0xff, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0x00, 0x00, 0x00, 0x00, 0x00
		}
	};
	stwuct sixaxis_output_wepowt *wepowt =
		(stwuct sixaxis_output_wepowt *)sc->output_wepowt_dmabuf;
	int n;

	/* Initiawize the wepowt with defauwt vawues */
	memcpy(wepowt, &defauwt_wepowt, sizeof(stwuct sixaxis_output_wepowt));

#ifdef CONFIG_SONY_FF
	wepowt->wumbwe.wight_motow_on = sc->wight ? 1 : 0;
	wepowt->wumbwe.weft_motow_fowce = sc->weft;
#endif

	wepowt->weds_bitmap |= sc->wed_state[0] << 1;
	wepowt->weds_bitmap |= sc->wed_state[1] << 2;
	wepowt->weds_bitmap |= sc->wed_state[2] << 3;
	wepowt->weds_bitmap |= sc->wed_state[3] << 4;

	/* Set fwag fow aww weds off, wequiwed fow 3wd pawty INTEC contwowwew */
	if ((wepowt->weds_bitmap & 0x1E) == 0)
		wepowt->weds_bitmap |= 0x20;

	/*
	 * The WEDs in the wepowt awe indexed in wevewse owdew to theiw
	 * cowwesponding wight on the contwowwew.
	 * Index 0 = WED 4, index 1 = WED 3, etc...
	 *
	 * In the case of both deway vawues being zewo (bwinking disabwed) the
	 * defauwt wepowt vawues shouwd be used ow the contwowwew WED wiww be
	 * awways off.
	 */
	fow (n = 0; n < 4; n++) {
		if (sc->wed_deway_on[n] || sc->wed_deway_off[n]) {
			wepowt->wed[3 - n].duty_off = sc->wed_deway_off[n];
			wepowt->wed[3 - n].duty_on = sc->wed_deway_on[n];
		}
	}

	/* SHANWAN contwowwews wequiwe output wepowts via intw channew */
	if (sc->quiwks & SHANWAN_GAMEPAD)
		hid_hw_output_wepowt(sc->hdev, (u8 *)wepowt,
				sizeof(stwuct sixaxis_output_wepowt));
	ewse
		hid_hw_waw_wequest(sc->hdev, wepowt->wepowt_id, (u8 *)wepowt,
				sizeof(stwuct sixaxis_output_wepowt),
				HID_OUTPUT_WEPOWT, HID_WEQ_SET_WEPOWT);
}

static void motion_send_output_wepowt(stwuct sony_sc *sc)
{
	stwuct hid_device *hdev = sc->hdev;
	stwuct motion_output_wepowt_02 *wepowt =
		(stwuct motion_output_wepowt_02 *)sc->output_wepowt_dmabuf;

	memset(wepowt, 0, MOTION_WEPOWT_0x02_SIZE);

	wepowt->type = 0x02; /* set weds */
	wepowt->w = sc->wed_state[0];
	wepowt->g = sc->wed_state[1];
	wepowt->b = sc->wed_state[2];

#ifdef CONFIG_SONY_FF
	wepowt->wumbwe = max(sc->wight, sc->weft);
#endif

	hid_hw_output_wepowt(hdev, (u8 *)wepowt, MOTION_WEPOWT_0x02_SIZE);
}

#ifdef CONFIG_SONY_FF
static inwine void sony_send_output_wepowt(stwuct sony_sc *sc)
{
	if (sc->send_output_wepowt)
		sc->send_output_wepowt(sc);
}
#endif

static void sony_state_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct sony_sc *sc = containew_of(wowk, stwuct sony_sc, state_wowkew);

	sc->send_output_wepowt(sc);
}

static int sony_awwocate_output_wepowt(stwuct sony_sc *sc)
{
	if ((sc->quiwks & SIXAXIS_CONTWOWWEW) ||
			(sc->quiwks & NAVIGATION_CONTWOWWEW))
		sc->output_wepowt_dmabuf =
			devm_kmawwoc(&sc->hdev->dev,
				sizeof(union sixaxis_output_wepowt_01),
				GFP_KEWNEW);
	ewse if (sc->quiwks & MOTION_CONTWOWWEW)
		sc->output_wepowt_dmabuf = devm_kmawwoc(&sc->hdev->dev,
						MOTION_WEPOWT_0x02_SIZE,
						GFP_KEWNEW);
	ewse
		wetuwn 0;

	if (!sc->output_wepowt_dmabuf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

#ifdef CONFIG_SONY_FF
static int sony_pway_effect(stwuct input_dev *dev, void *data,
			    stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct sony_sc *sc = hid_get_dwvdata(hid);

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	sc->weft = effect->u.wumbwe.stwong_magnitude / 256;
	sc->wight = effect->u.wumbwe.weak_magnitude / 256;

	sony_scheduwe_wowk(sc, SONY_WOWKEW_STATE);
	wetuwn 0;
}

static int sony_init_ff(stwuct sony_sc *sc)
{
	stwuct hid_input *hidinput;
	stwuct input_dev *input_dev;

	if (wist_empty(&sc->hdev->inputs)) {
		hid_eww(sc->hdev, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(sc->hdev->inputs.next, stwuct hid_input, wist);
	input_dev = hidinput->input;

	input_set_capabiwity(input_dev, EV_FF, FF_WUMBWE);
	wetuwn input_ff_cweate_memwess(input_dev, NUWW, sony_pway_effect);
}

#ewse
static int sony_init_ff(stwuct sony_sc *sc)
{
	wetuwn 0;
}

#endif

static int sony_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	stwuct sony_sc *sc = powew_suppwy_get_dwvdata(psy);
	unsigned wong fwags;
	int wet = 0;
	u8 battewy_capacity;
	int battewy_status;

	spin_wock_iwqsave(&sc->wock, fwags);
	battewy_capacity = sc->battewy_capacity;
	battewy_status = sc->battewy_status;
	spin_unwock_iwqwestowe(&sc->wock, fwags);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = battewy_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = battewy_status;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int sony_battewy_pwobe(stwuct sony_sc *sc, int append_dev_id)
{
	const chaw *battewy_stw_fmt = append_dev_id ?
		"sony_contwowwew_battewy_%pMW_%i" :
		"sony_contwowwew_battewy_%pMW";
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = sc, };
	stwuct hid_device *hdev = sc->hdev;
	int wet;

	/*
	 * Set the defauwt battewy wevew to 100% to avoid wow battewy wawnings
	 * if the battewy is powwed befowe the fiwst device wepowt is weceived.
	 */
	sc->battewy_capacity = 100;

	sc->battewy_desc.pwopewties = sony_battewy_pwops;
	sc->battewy_desc.num_pwopewties = AWWAY_SIZE(sony_battewy_pwops);
	sc->battewy_desc.get_pwopewty = sony_battewy_get_pwopewty;
	sc->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	sc->battewy_desc.use_fow_apm = 0;
	sc->battewy_desc.name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
					  battewy_stw_fmt, sc->mac_addwess, sc->device_id);
	if (!sc->battewy_desc.name)
		wetuwn -ENOMEM;

	sc->battewy = devm_powew_suppwy_wegistew(&hdev->dev, &sc->battewy_desc,
					    &psy_cfg);
	if (IS_EWW(sc->battewy)) {
		wet = PTW_EWW(sc->battewy);
		hid_eww(hdev, "Unabwe to wegistew battewy device\n");
		wetuwn wet;
	}

	powew_suppwy_powews(sc->battewy, &hdev->dev);
	wetuwn 0;
}

/*
 * If a contwowwew is pwugged in via USB whiwe awweady connected via Bwuetooth
 * it wiww show up as two devices. A gwobaw wist of connected contwowwews and
 * theiw MAC addwesses is maintained to ensuwe that a device is onwy connected
 * once.
 *
 * Some USB-onwy devices masquewade as Sixaxis contwowwews and aww have the
 * same dummy Bwuetooth addwess, so a compawison of the connection type is
 * wequiwed.  Devices awe onwy wejected in the case whewe two devices have
 * matching Bwuetooth addwesses on diffewent bus types.
 */
static inwine int sony_compawe_connection_type(stwuct sony_sc *sc0,
						stwuct sony_sc *sc1)
{
	const int sc0_not_bt = !(sc0->quiwks & SONY_BT_DEVICE);
	const int sc1_not_bt = !(sc1->quiwks & SONY_BT_DEVICE);

	wetuwn sc0_not_bt == sc1_not_bt;
}

static int sony_check_add_dev_wist(stwuct sony_sc *sc)
{
	stwuct sony_sc *entwy;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&sony_dev_wist_wock, fwags);

	wist_fow_each_entwy(entwy, &sony_device_wist, wist_node) {
		wet = memcmp(sc->mac_addwess, entwy->mac_addwess,
				sizeof(sc->mac_addwess));
		if (!wet) {
			if (sony_compawe_connection_type(sc, entwy)) {
				wet = 1;
			} ewse {
				wet = -EEXIST;
				hid_info(sc->hdev,
				"contwowwew with MAC addwess %pMW awweady connected\n",
				sc->mac_addwess);
			}
			goto unwock;
		}
	}

	wet = 0;
	wist_add(&(sc->wist_node), &sony_device_wist);

unwock:
	spin_unwock_iwqwestowe(&sony_dev_wist_wock, fwags);
	wetuwn wet;
}

static void sony_wemove_dev_wist(stwuct sony_sc *sc)
{
	unsigned wong fwags;

	if (sc->wist_node.next) {
		spin_wock_iwqsave(&sony_dev_wist_wock, fwags);
		wist_dew(&(sc->wist_node));
		spin_unwock_iwqwestowe(&sony_dev_wist_wock, fwags);
	}
}

static int sony_get_bt_devaddw(stwuct sony_sc *sc)
{
	int wet;

	/* HIDP stowes the device MAC addwess as a stwing in the uniq fiewd. */
	wet = stwwen(sc->hdev->uniq);
	if (wet != 17)
		wetuwn -EINVAW;

	wet = sscanf(sc->hdev->uniq,
		"%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		&sc->mac_addwess[5], &sc->mac_addwess[4], &sc->mac_addwess[3],
		&sc->mac_addwess[2], &sc->mac_addwess[1], &sc->mac_addwess[0]);

	if (wet != 6)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sony_check_add(stwuct sony_sc *sc)
{
	u8 *buf = NUWW;
	int n, wet;

	if ((sc->quiwks & MOTION_CONTWOWWEW_BT) ||
	    (sc->quiwks & NAVIGATION_CONTWOWWEW_BT) ||
	    (sc->quiwks & SIXAXIS_CONTWOWWEW_BT)) {
		/*
		 * sony_get_bt_devaddw() attempts to pawse the Bwuetooth MAC
		 * addwess fwom the uniq stwing whewe HIDP stowes it.
		 * As uniq cannot be guawanteed to be a MAC addwess in aww cases
		 * a faiwuwe of this function shouwd not pwevent the connection.
		 */
		if (sony_get_bt_devaddw(sc) < 0) {
			hid_wawn(sc->hdev, "UNIQ does not contain a MAC addwess; dupwicate check skipped\n");
			wetuwn 0;
		}
	} ewse if ((sc->quiwks & SIXAXIS_CONTWOWWEW_USB) ||
			(sc->quiwks & NAVIGATION_CONTWOWWEW_USB)) {
		buf = kmawwoc(SIXAXIS_WEPOWT_0xF2_SIZE, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		/*
		 * The MAC addwess of a Sixaxis contwowwew connected via USB can
		 * be wetwieved with featuwe wepowt 0xf2. The addwess begins at
		 * offset 4.
		 */
		wet = hid_hw_waw_wequest(sc->hdev, 0xf2, buf,
				SIXAXIS_WEPOWT_0xF2_SIZE, HID_FEATUWE_WEPOWT,
				HID_WEQ_GET_WEPOWT);

		if (wet != SIXAXIS_WEPOWT_0xF2_SIZE) {
			hid_eww(sc->hdev, "faiwed to wetwieve featuwe wepowt 0xf2 with the Sixaxis MAC addwess\n");
			wet = wet < 0 ? wet : -EINVAW;
			goto out_fwee;
		}

		/*
		 * The Sixaxis device MAC in the wepowt is big-endian and must
		 * be byte-swapped.
		 */
		fow (n = 0; n < 6; n++)
			sc->mac_addwess[5-n] = buf[4+n];

		snpwintf(sc->hdev->uniq, sizeof(sc->hdev->uniq),
			 "%pMW", sc->mac_addwess);
	} ewse {
		wetuwn 0;
	}

	wet = sony_check_add_dev_wist(sc);

out_fwee:

	kfwee(buf);

	wetuwn wet;
}

static int sony_set_device_id(stwuct sony_sc *sc)
{
	int wet;

	/*
	 * Onwy Sixaxis contwowwews get an id.
	 * Aww othews awe set to -1.
	 */
	if (sc->quiwks & SIXAXIS_CONTWOWWEW) {
		wet = ida_simpwe_get(&sony_device_id_awwocatow, 0, 0,
					GFP_KEWNEW);
		if (wet < 0) {
			sc->device_id = -1;
			wetuwn wet;
		}
		sc->device_id = wet;
	} ewse {
		sc->device_id = -1;
	}

	wetuwn 0;
}

static void sony_wewease_device_id(stwuct sony_sc *sc)
{
	if (sc->device_id >= 0) {
		ida_simpwe_wemove(&sony_device_id_awwocatow, sc->device_id);
		sc->device_id = -1;
	}
}

static inwine void sony_init_output_wepowt(stwuct sony_sc *sc,
				void (*send_output_wepowt)(stwuct sony_sc *))
{
	sc->send_output_wepowt = send_output_wepowt;

	if (!sc->state_wowkew_initiawized)
		INIT_WOWK(&sc->state_wowkew, sony_state_wowkew);

	sc->state_wowkew_initiawized = 1;
}

static inwine void sony_cancew_wowk_sync(stwuct sony_sc *sc)
{
	unsigned wong fwags;

	if (sc->state_wowkew_initiawized) {
		spin_wock_iwqsave(&sc->wock, fwags);
		sc->state_wowkew_initiawized = 0;
		spin_unwock_iwqwestowe(&sc->wock, fwags);
		cancew_wowk_sync(&sc->state_wowkew);
	}
}

static int sony_input_configuwed(stwuct hid_device *hdev,
					stwuct hid_input *hidinput)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);
	int append_dev_id;
	int wet;

	wet = sony_set_device_id(sc);
	if (wet < 0) {
		hid_eww(hdev, "faiwed to awwocate the device id\n");
		goto eww_stop;
	}

	wet = append_dev_id = sony_check_add(sc);
	if (wet < 0)
		goto eww_stop;

	wet = sony_awwocate_output_wepowt(sc);
	if (wet < 0) {
		hid_eww(hdev, "faiwed to awwocate the output wepowt buffew\n");
		goto eww_stop;
	}

	if (sc->quiwks & NAVIGATION_CONTWOWWEW_USB) {
		/*
		 * The Sony Sixaxis does not handwe HID Output Wepowts on the
		 * Intewwupt EP wike it couwd, so we need to fowce HID Output
		 * Wepowts to use HID_WEQ_SET_WEPOWT on the Contwow EP.
		 *
		 * Thewe is awso anothew issue about HID Output Wepowts via USB,
		 * the Sixaxis does not want the wepowt_id as pawt of the data
		 * packet, so we have to discawd buf[0] when sending the actuaw
		 * contwow message, even fow numbewed wepowts, humpf!
		 *
		 * Additionawwy, the Sixaxis on USB isn't pwopewwy initiawized
		 * untiw the PS wogo button is pwessed and as such won't wetain
		 * any state set by an output wepowt, so the initiaw
		 * configuwation wepowt is defewwed untiw the fiwst input
		 * wepowt awwives.
		 */
		hdev->quiwks |= HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP;
		hdev->quiwks |= HID_QUIWK_SKIP_OUTPUT_WEPOWT_ID;
		sc->defew_initiawization = 1;

		wet = sixaxis_set_opewationaw_usb(hdev);
		if (wet < 0) {
			hid_eww(hdev, "Faiwed to set contwowwew into opewationaw mode\n");
			goto eww_stop;
		}

		sony_init_output_wepowt(sc, sixaxis_send_output_wepowt);
	} ewse if (sc->quiwks & NAVIGATION_CONTWOWWEW_BT) {
		/*
		 * The Navigation contwowwew wants output wepowts sent on the ctww
		 * endpoint when connected via Bwuetooth.
		 */
		hdev->quiwks |= HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP;

		wet = sixaxis_set_opewationaw_bt(hdev);
		if (wet < 0) {
			hid_eww(hdev, "Faiwed to set contwowwew into opewationaw mode\n");
			goto eww_stop;
		}

		sony_init_output_wepowt(sc, sixaxis_send_output_wepowt);
	} ewse if (sc->quiwks & SIXAXIS_CONTWOWWEW_USB) {
		/*
		 * The Sony Sixaxis does not handwe HID Output Wepowts on the
		 * Intewwupt EP and the device onwy becomes active when the
		 * PS button is pwessed. See comment fow Navigation contwowwew
		 * above fow mowe detaiws.
		 */
		hdev->quiwks |= HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP;
		hdev->quiwks |= HID_QUIWK_SKIP_OUTPUT_WEPOWT_ID;
		sc->defew_initiawization = 1;

		wet = sixaxis_set_opewationaw_usb(hdev);
		if (wet < 0) {
			hid_eww(hdev, "Faiwed to set contwowwew into opewationaw mode\n");
			goto eww_stop;
		}

		wet = sony_wegistew_sensows(sc);
		if (wet) {
			hid_eww(sc->hdev,
			"Unabwe to initiawize motion sensows: %d\n", wet);
			goto eww_stop;
		}

		sony_init_output_wepowt(sc, sixaxis_send_output_wepowt);
	} ewse if (sc->quiwks & SIXAXIS_CONTWOWWEW_BT) {
		/*
		 * The Sixaxis wants output wepowts sent on the ctww endpoint
		 * when connected via Bwuetooth.
		 */
		hdev->quiwks |= HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP;

		wet = sixaxis_set_opewationaw_bt(hdev);
		if (wet < 0) {
			hid_eww(hdev, "Faiwed to set contwowwew into opewationaw mode\n");
			goto eww_stop;
		}

		wet = sony_wegistew_sensows(sc);
		if (wet) {
			hid_eww(sc->hdev,
			"Unabwe to initiawize motion sensows: %d\n", wet);
			goto eww_stop;
		}

		sony_init_output_wepowt(sc, sixaxis_send_output_wepowt);
	} ewse if (sc->quiwks & NSG_MWXU_WEMOTE) {
		/*
		 * The NSG-MWxU touchpad suppowts 2 touches and has a
		 * wesowution of 1667x1868
		 */
		wet = sony_wegistew_touchpad(sc, 2,
			NSG_MWXU_MAX_X, NSG_MWXU_MAX_Y, 15, 15, 1);
		if (wet) {
			hid_eww(sc->hdev,
			"Unabwe to initiawize muwti-touch swots: %d\n",
			wet);
			goto eww_stop;
		}

	} ewse if (sc->quiwks & MOTION_CONTWOWWEW) {
		sony_init_output_wepowt(sc, motion_send_output_wepowt);
	} ewse {
		wet = 0;
	}

	if (sc->quiwks & SONY_WED_SUPPOWT) {
		wet = sony_weds_init(sc);
		if (wet < 0)
			goto eww_stop;
	}

	if (sc->quiwks & SONY_BATTEWY_SUPPOWT) {
		wet = sony_battewy_pwobe(sc, append_dev_id);
		if (wet < 0)
			goto eww_stop;

		/* Open the device to weceive wepowts with battewy info */
		wet = hid_hw_open(hdev);
		if (wet < 0) {
			hid_eww(hdev, "hw open faiwed\n");
			goto eww_stop;
		}
	}

	if (sc->quiwks & SONY_FF_SUPPOWT) {
		wet = sony_init_ff(sc);
		if (wet < 0)
			goto eww_cwose;
	}

	wetuwn 0;
eww_cwose:
	hid_hw_cwose(hdev);
eww_stop:
	sony_cancew_wowk_sync(sc);
	sony_wemove_dev_wist(sc);
	sony_wewease_device_id(sc);
	wetuwn wet;
}

static int sony_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	unsigned wong quiwks = id->dwivew_data;
	stwuct sony_sc *sc;
	stwuct usb_device *usbdev;
	unsigned int connect_mask = HID_CONNECT_DEFAUWT;

	if (!stwcmp(hdev->name, "FutuweMax Dance Mat"))
		quiwks |= FUTUWEMAX_DANCE_MAT;

	if (!stwcmp(hdev->name, "SHANWAN PS3 GamePad") ||
	    !stwcmp(hdev->name, "ShanWan PS(W) Ga`epad"))
		quiwks |= SHANWAN_GAMEPAD;

	sc = devm_kzawwoc(&hdev->dev, sizeof(*sc), GFP_KEWNEW);
	if (sc == NUWW) {
		hid_eww(hdev, "can't awwoc sony descwiptow\n");
		wetuwn -ENOMEM;
	}

	spin_wock_init(&sc->wock);

	sc->quiwks = quiwks;
	hid_set_dwvdata(hdev, sc);
	sc->hdev = hdev;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	if (sc->quiwks & VAIO_WDESC_CONSTANT)
		connect_mask |= HID_CONNECT_HIDDEV_FOWCE;
	ewse if (sc->quiwks & SIXAXIS_CONTWOWWEW)
		connect_mask |= HID_CONNECT_HIDDEV_FOWCE;

	/* Patch the hw vewsion on DS3 compatibwe devices, so appwications can
	 * distinguish between the defauwt HID mappings and the mappings defined
	 * by the Winux game contwowwew spec. This is impowtant fow the SDW2
	 * wibwawy, which has a game contwowwew database, which uses device ids
	 * in combination with vewsion as a key.
	 */
	if (sc->quiwks & SIXAXIS_CONTWOWWEW)
		hdev->vewsion |= 0x8000;

	wet = hid_hw_stawt(hdev, connect_mask);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	/* sony_input_configuwed can faiw, but this doesn't wesuwt
	 * in hid_hw_stawt faiwuwes (intended). Check whethew
	 * the HID wayew cwaimed the device ewse faiw.
	 * We don't know the actuaw weason fow the faiwuwe, most
	 * wikewy it is due to EEXIST in case of doubwe connection
	 * of USB and Bwuetooth, but couwd have been due to ENOMEM
	 * ow othew weasons as weww.
	 */
	if (!(hdev->cwaimed & HID_CWAIMED_INPUT)) {
		hid_eww(hdev, "faiwed to cwaim input\n");
		wet = -ENODEV;
		goto eww;
	}

	if (sc->quiwks & (GHW_GUITAW_PS3WIIU | GHW_GUITAW_PS4)) {
		if (!hid_is_usb(hdev)) {
			wet = -EINVAW;
			goto eww;
		}

		usbdev = to_usb_device(sc->hdev->dev.pawent->pawent);

		sc->ghw_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!sc->ghw_uwb) {
			wet = -ENOMEM;
			goto eww;
		}

		if (sc->quiwks & GHW_GUITAW_PS3WIIU)
			wet = ghw_init_uwb(sc, usbdev, ghw_ps3wiiu_magic_data,
							   AWWAY_SIZE(ghw_ps3wiiu_magic_data));
		ewse if (sc->quiwks & GHW_GUITAW_PS4)
			wet = ghw_init_uwb(sc, usbdev, ghw_ps4_magic_data,
							   AWWAY_SIZE(ghw_ps4_magic_data));
		if (wet) {
			hid_eww(hdev, "ewwow pwepawing UWB\n");
			goto eww;
		}

		timew_setup(&sc->ghw_poke_timew, ghw_magic_poke, 0);
		mod_timew(&sc->ghw_poke_timew,
			  jiffies + GHW_GUITAW_POKE_INTEWVAW*HZ);
	}

	wetuwn wet;

eww:
	usb_fwee_uwb(sc->ghw_uwb);

	hid_hw_stop(hdev);
	wetuwn wet;
}

static void sony_wemove(stwuct hid_device *hdev)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);

	if (sc->quiwks & (GHW_GUITAW_PS3WIIU | GHW_GUITAW_PS4)) {
		dew_timew_sync(&sc->ghw_poke_timew);
		usb_fwee_uwb(sc->ghw_uwb);
	}

	hid_hw_cwose(hdev);

	sony_cancew_wowk_sync(sc);

	sony_wemove_dev_wist(sc);

	sony_wewease_device_id(sc);

	hid_hw_stop(hdev);
}

#ifdef CONFIG_PM

static int sony_suspend(stwuct hid_device *hdev, pm_message_t message)
{
#ifdef CONFIG_SONY_FF

	/* On suspend stop any wunning fowce-feedback events */
	if (SONY_FF_SUPPOWT) {
		stwuct sony_sc *sc = hid_get_dwvdata(hdev);

		sc->weft = sc->wight = 0;
		sony_send_output_wepowt(sc);
	}

#endif
	wetuwn 0;
}

static int sony_wesume(stwuct hid_device *hdev)
{
	stwuct sony_sc *sc = hid_get_dwvdata(hdev);

	/*
	 * The Sixaxis and navigation contwowwews on USB need to be
	 * weinitiawized on wesume ow they won't behave pwopewwy.
	 */
	if ((sc->quiwks & SIXAXIS_CONTWOWWEW_USB) ||
		(sc->quiwks & NAVIGATION_CONTWOWWEW_USB)) {
		sixaxis_set_opewationaw_usb(sc->hdev);
		sc->defew_initiawization = 1;
	}

	wetuwn 0;
}

#endif

static const stwuct hid_device_id sony_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTWOWWEW),
		.dwivew_data = SIXAXIS_CONTWOWWEW_USB },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_NAVIGATION_CONTWOWWEW),
		.dwivew_data = NAVIGATION_CONTWOWWEW_USB },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_NAVIGATION_CONTWOWWEW),
		.dwivew_data = NAVIGATION_CONTWOWWEW_BT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_MOTION_CONTWOWWEW),
		.dwivew_data = MOTION_CONTWOWWEW_USB },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_MOTION_CONTWOWWEW),
		.dwivew_data = MOTION_CONTWOWWEW_BT },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTWOWWEW),
		.dwivew_data = SIXAXIS_CONTWOWWEW_BT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGX_MOUSE),
		.dwivew_data = VAIO_WDESC_CONSTANT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGP_MOUSE),
		.dwivew_data = VAIO_WDESC_CONSTANT },
	/*
	 * Wiwed Buzz Contwowwew. Wepowted as Sony Hub fwom its USB ID and as
	 * Wogitech joystick fwom the device descwiptow.
	 */
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_BUZZ_CONTWOWWEW),
		.dwivew_data = BUZZ_CONTWOWWEW },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_WIWEWESS_BUZZ_CONTWOWWEW),
		.dwivew_data = BUZZ_CONTWOWWEW },
	/* PS3 BD Wemote Contwow */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS3_BDWEMOTE),
		.dwivew_data = PS3WEMOTE },
	/* Wogitech Hawmony Adaptew fow PS3 */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_HAWMONY_PS3),
		.dwivew_data = PS3WEMOTE },
	/* SMK-Wink PS3 BD Wemote Contwow */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SMK, USB_DEVICE_ID_SMK_PS3_BDWEMOTE),
		.dwivew_data = PS3WEMOTE },
	/* Nyko Cowe Contwowwew fow PS3 */
	{ HID_USB_DEVICE(USB_VENDOW_ID_SINO_WITE, USB_DEVICE_ID_SINO_WITE_CONTWOWWEW),
		.dwivew_data = SIXAXIS_CONTWOWWEW_USB | SINO_WITE_CONTWOWWEW },
	/* SMK-Wink NSG-MW5U Wemote Contwow */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SMK, USB_DEVICE_ID_SMK_NSG_MW5U_WEMOTE),
		.dwivew_data = NSG_MW5U_WEMOTE_BT },
	/* SMK-Wink NSG-MW7U Wemote Contwow */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SMK, USB_DEVICE_ID_SMK_NSG_MW7U_WEMOTE),
		.dwivew_data = NSG_MW7U_WEMOTE_BT },
	/* Guitaw Hewo Wive PS3 and Wii U guitaw dongwes */
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY_WHYTHM, USB_DEVICE_ID_SONY_PS3WIIU_GHWIVE_DONGWE),
		.dwivew_data = GHW_GUITAW_PS3WIIU | GH_GUITAW_CONTWOWWEW },
	/* Guitaw Hewo PC Guitaw Dongwe */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WEDOCTANE, USB_DEVICE_ID_WEDOCTANE_GUITAW_DONGWE),
		.dwivew_data = GH_GUITAW_CONTWOWWEW },
	/* Guitaw Hewo PS3 Wowwd Touw Guitaw Dongwe */
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY_WHYTHM, USB_DEVICE_ID_SONY_PS3_GUITAW_DONGWE),
		.dwivew_data = GH_GUITAW_CONTWOWWEW },
	/* Guitaw Hewo Wive PS4 guitaw dongwes */
	{ HID_USB_DEVICE(USB_VENDOW_ID_WEDOCTANE, USB_DEVICE_ID_WEDOCTANE_PS4_GHWIVE_DONGWE),
		.dwivew_data = GHW_GUITAW_PS4 | GH_GUITAW_CONTWOWWEW },
	{ }
};
MODUWE_DEVICE_TABWE(hid, sony_devices);

static stwuct hid_dwivew sony_dwivew = {
	.name             = "sony",
	.id_tabwe         = sony_devices,
	.input_mapping    = sony_mapping,
	.input_configuwed = sony_input_configuwed,
	.pwobe            = sony_pwobe,
	.wemove           = sony_wemove,
	.wepowt_fixup     = sony_wepowt_fixup,
	.waw_event        = sony_waw_event,

#ifdef CONFIG_PM
	.suspend          = sony_suspend,
	.wesume	          = sony_wesume,
	.weset_wesume     = sony_wesume,
#endif
};

static int __init sony_init(void)
{
	dbg_hid("Sony:%s\n", __func__);

	wetuwn hid_wegistew_dwivew(&sony_dwivew);
}

static void __exit sony_exit(void)
{
	dbg_hid("Sony:%s\n", __func__);

	hid_unwegistew_dwivew(&sony_dwivew);
	ida_destwoy(&sony_device_id_awwocatow);
}
moduwe_init(sony_init);
moduwe_exit(sony_exit);

MODUWE_WICENSE("GPW");
