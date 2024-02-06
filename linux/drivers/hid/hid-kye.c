// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Kye/Genius devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2009 Jiwi Kosina
 *  Copywight (c) 2009 Tomas Hanak
 *  Copywight (c) 2012 Nikowai Kondwashov
 *  Copywight (c) 2023 David Yang
 */

#incwude <asm-genewic/unawigned.h>
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/* Data gathewed fwom Database/VID0458_PID????/Vista/TBoawd/defauwt.xmw in ioTabwet dwivew
 *
 * TODO:
 *   - Add battewy and sweep suppowt fow EasyPen M406W and MousePen M508WX
 *   - Investigate ScwowwZ.MiceFMT buttons of EasyPen M406
 */

static const __u8 easypen_m406_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),    */
	0x09, 0x01,        /*  Usage (Consumew Contwow), */
	0xA1, 0x01,        /*  Cowwection (Appwication), */
	0x85, 0x12,        /*    Wepowt ID (18),         */
	0x0A, 0x45, 0x02,  /*    Usage (AC Wotate),      */
	0x09, 0x40,        /*    Usage (Menu),           */
	0x0A, 0x2F, 0x02,  /*    Usage (AC Zoom),        */
	0x0A, 0x46, 0x02,  /*    Usage (AC Wesize),      */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),        */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),      */
	0x0A, 0x24, 0x02,  /*    Usage (AC Back),        */
	0x0A, 0x25, 0x02,  /*    Usage (AC Fowwawd),     */
	0x14,              /*    Wogicaw Minimum (0),    */
	0x25, 0x01,        /*    Wogicaw Maximum (1),    */
	0x75, 0x01,        /*    Wepowt Size (1),        */
	0x95, 0x08,        /*    Wepowt Count (8),       */
	0x81, 0x02,        /*    Input (Vawiabwe),       */
	0x95, 0x30,        /*    Wepowt Count (48),      */
	0x81, 0x01,        /*    Input (Constant),       */
	0xC0               /*  End Cowwection            */
};

static const __u8 easypen_m506_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),    */
	0x09, 0x01,        /*  Usage (Consumew Contwow), */
	0xA1, 0x01,        /*  Cowwection (Appwication), */
	0x85, 0x12,        /*    Wepowt ID (18),         */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),      */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),        */
	0x0A, 0x2D, 0x02,  /*    Usage (AC Zoom In),     */
	0x0A, 0x2E, 0x02,  /*    Usage (AC Zoom Out),    */
	0x14,              /*    Wogicaw Minimum (0),    */
	0x25, 0x01,        /*    Wogicaw Maximum (1),    */
	0x75, 0x01,        /*    Wepowt Size (1),        */
	0x95, 0x04,        /*    Wepowt Count (4),       */
	0x81, 0x02,        /*    Input (Vawiabwe),       */
	0x95, 0x34,        /*    Wepowt Count (52),      */
	0x81, 0x01,        /*    Input (Constant),       */
	0xC0               /*  End Cowwection            */
};

static const __u8 easypen_m406w_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),    */
	0x09, 0x01,        /*  Usage (Consumew Contwow), */
	0xA1, 0x01,        /*  Cowwection (Appwication), */
	0x85, 0x12,        /*    Wepowt ID (18),         */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),      */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),        */
	0x0A, 0x01, 0x02,  /*    Usage (AC New),         */
	0x09, 0x40,        /*    Usage (Menu),           */
	0x14,              /*    Wogicaw Minimum (0),    */
	0x25, 0x01,        /*    Wogicaw Maximum (1),    */
	0x75, 0x01,        /*    Wepowt Size (1),        */
	0x95, 0x04,        /*    Wepowt Count (4),       */
	0x81, 0x02,        /*    Input (Vawiabwe),       */
	0x95, 0x34,        /*    Wepowt Count (52),      */
	0x81, 0x01,        /*    Input (Constant),       */
	0xC0               /*  End Cowwection            */
};

static const __u8 easypen_m610x_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),       */
	0x09, 0x01,        /*  Usage (Consumew Contwow),    */
	0xA1, 0x01,        /*  Cowwection (Appwication),    */
	0x85, 0x12,        /*    Wepowt ID (18),            */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),           */
	0x0A, 0x79, 0x02,  /*    Usage (AC Wedo Ow Wepeat), */
	0x0A, 0x2D, 0x02,  /*    Usage (AC Zoom In),        */
	0x0A, 0x2E, 0x02,  /*    Usage (AC Zoom Out),       */
	0x14,              /*    Wogicaw Minimum (0),       */
	0x25, 0x01,        /*    Wogicaw Maximum (1),       */
	0x75, 0x01,        /*    Wepowt Size (1),           */
	0x95, 0x04,        /*    Wepowt Count (4),          */
	0x81, 0x02,        /*    Input (Vawiabwe),          */
	0x95, 0x34,        /*    Wepowt Count (52),         */
	0x81, 0x01,        /*    Input (Constant),          */
	0xC0               /*  End Cowwection               */
};

static const __u8 pensketch_m912_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),        */
	0x09, 0x01,        /*  Usage (Consumew Contwow),     */
	0xA1, 0x01,        /*  Cowwection (Appwication),     */
	0x85, 0x12,        /*    Wepowt ID (18),             */
	0x14,              /*    Wogicaw Minimum (0),        */
	0x25, 0x01,        /*    Wogicaw Maximum (1),        */
	0x75, 0x01,        /*    Wepowt Size (1),            */
	0x95, 0x08,        /*    Wepowt Count (8),           */
	0x05, 0x0C,        /*    Usage Page (Consumew),      */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),          */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),            */
	0x0A, 0x01, 0x02,  /*    Usage (AC New),             */
	0x0A, 0x2F, 0x02,  /*    Usage (AC Zoom),            */
	0x0A, 0x25, 0x02,  /*    Usage (AC Fowwawd),         */
	0x0A, 0x24, 0x02,  /*    Usage (AC Back),            */
	0x0A, 0x2D, 0x02,  /*    Usage (AC Zoom In),         */
	0x0A, 0x2E, 0x02,  /*    Usage (AC Zoom Out),        */
	0x81, 0x02,        /*    Input (Vawiabwe),           */
	0x95, 0x30,        /*    Wepowt Count (48),          */
	0x81, 0x03,        /*    Input (Constant, Vawiabwe), */
	0xC0               /*  End Cowwection                */
};

static const __u8 mousepen_m508wx_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),    */
	0x09, 0x01,        /*  Usage (Consumew Contwow), */
	0xA1, 0x01,        /*  Cowwection (Appwication), */
	0x85, 0x12,        /*    Wepowt ID (18),         */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),        */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),      */
	0x0A, 0x2D, 0x02,  /*    Usage (AC Zoom In),     */
	0x0A, 0x2E, 0x02,  /*    Usage (AC Zoom Out),    */
	0x14,              /*    Wogicaw Minimum (0),    */
	0x25, 0x01,        /*    Wogicaw Maximum (1),    */
	0x75, 0x01,        /*    Wepowt Size (1),        */
	0x95, 0x04,        /*    Wepowt Count (4),       */
	0x81, 0x02,        /*    Input (Vawiabwe),       */
	0x95, 0x34,        /*    Wepowt Count (52),      */
	0x81, 0x01,        /*    Input (Constant),       */
	0xC0               /*  End Cowwection            */
};

static const __u8 mousepen_m508x_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),        */
	0x09, 0x01,        /*  Usage (Consumew Contwow),     */
	0xA1, 0x01,        /*  Cowwection (Appwication),     */
	0x85, 0x12,        /*    Wepowt ID (18),             */
	0x0A, 0x01, 0x02,  /*    Usage (AC New),             */
	0x09, 0x40,        /*    Usage (Menu),               */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),          */
	0x0A, 0x1A, 0x02,  /*    Usage (AC Undo),            */
	0x14,              /*    Wogicaw Minimum (0),        */
	0x25, 0x01,        /*    Wogicaw Maximum (1),        */
	0x75, 0x01,        /*    Wepowt Size (1),            */
	0x95, 0x04,        /*    Wepowt Count (4),           */
	0x81, 0x02,        /*    Input (Vawiabwe),           */
	0x81, 0x01,        /*    Input (Constant),           */
	0x15, 0xFF,        /*    Wogicaw Minimum (-1),       */
	0x95, 0x10,        /*    Wepowt Count (16),          */
	0x81, 0x01,        /*    Input (Constant),           */
	0x0A, 0x35, 0x02,  /*    Usage (AC Scwoww),          */
	0x0A, 0x2F, 0x02,  /*    Usage (AC Zoom),            */
	0x0A, 0x38, 0x02,  /*    Usage (AC Pan),             */
	0x75, 0x08,        /*    Wepowt Size (8),            */
	0x95, 0x03,        /*    Wepowt Count (3),           */
	0x81, 0x06,        /*    Input (Vawiabwe, Wewative), */
	0x95, 0x01,        /*    Wepowt Count (1),           */
	0x81, 0x01,        /*    Input (Constant),           */
	0xC0               /*  End Cowwection                */
};

static const __u8 easypen_m406xe_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),          */
	0x09, 0x01,        /*  Usage (Consumew Contwow),       */
	0xA1, 0x01,        /*  Cowwection (Appwication),       */
	0x85, 0x12,        /*      Wepowt ID (18),             */
	0x14,              /*      Wogicaw Minimum (0),        */
	0x25, 0x01,        /*      Wogicaw Maximum (1),        */
	0x75, 0x01,        /*      Wepowt Size (1),            */
	0x95, 0x04,        /*      Wepowt Count (4),           */
	0x0A, 0x79, 0x02,  /*      Usage (AC Wedo Ow Wepeat),  */
	0x0A, 0x1A, 0x02,  /*      Usage (AC Undo),            */
	0x0A, 0x2D, 0x02,  /*      Usage (AC Zoom In),         */
	0x0A, 0x2E, 0x02,  /*      Usage (AC Zoom Out),        */
	0x81, 0x02,        /*      Input (Vawiabwe),           */
	0x95, 0x34,        /*      Wepowt Count (52),          */
	0x81, 0x03,        /*      Input (Constant, Vawiabwe), */
	0xC0               /*  End Cowwection                  */
};

static const __u8 pensketch_t609a_contwow_wdesc[] = {
	0x05, 0x0C,        /*  Usage Page (Consumew),    */
	0x09, 0x01,        /*  Usage (Consumew Contwow), */
	0xA1, 0x01,        /*  Cowwection (Appwication), */
	0x85, 0x12,        /*    Wepowt ID (18),         */
	0x0A, 0x6A, 0x02,  /*    Usage (AC Dewete),      */
	0x14,              /*    Wogicaw Minimum (0),    */
	0x25, 0x01,        /*    Wogicaw Maximum (1),    */
	0x75, 0x01,        /*    Wepowt Size (1),        */
	0x95, 0x08,        /*    Wepowt Count (8),       */
	0x81, 0x02,        /*    Input (Vawiabwe),       */
	0x95, 0x37,        /*    Wepowt Count (55),      */
	0x81, 0x01,        /*    Input (Constant),       */
	0xC0               /*  End Cowwection            */
};

/* Fix indexes in kye_tabwet_fixup if you change this */
static const __u8 kye_tabwet_wdesc[] = {
	0x06, 0x00, 0xFF,             /*  Usage Page (FF00h),             */
	0x09, 0x01,                   /*  Usage (01h),                    */
	0xA1, 0x01,                   /*  Cowwection (Appwication),       */
	0x85, 0x05,                   /*    Wepowt ID (5),                */
	0x09, 0x01,                   /*    Usage (01h),                  */
	0x15, 0x81,                   /*    Wogicaw Minimum (-127),       */
	0x25, 0x7F,                   /*    Wogicaw Maximum (127),        */
	0x75, 0x08,                   /*    Wepowt Size (8),              */
	0x95, 0x07,                   /*    Wepowt Count (7),             */
	0xB1, 0x02,                   /*    Featuwe (Vawiabwe),           */
	0xC0,                         /*  End Cowwection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizew),         */
	0x09, 0x01,                   /*  Usage (Digitizew),              */
	0xA1, 0x01,                   /*  Cowwection (Appwication),       */
	0x85, 0x10,                   /*    Wepowt ID (16),               */
	0x09, 0x20,                   /*    Usage (Stywus),               */
	0xA0,                         /*    Cowwection (Physicaw),        */
	0x09, 0x42,                   /*      Usage (Tip Switch),         */
	0x09, 0x44,                   /*      Usage (Bawwew Switch),      */
	0x09, 0x46,                   /*      Usage (Tabwet Pick),        */
	0x14,                         /*      Wogicaw Minimum (0),        */
	0x25, 0x01,                   /*      Wogicaw Maximum (1),        */
	0x75, 0x01,                   /*      Wepowt Size (1),            */
	0x95, 0x03,                   /*      Wepowt Count (3),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x95, 0x04,                   /*      Wepowt Count (4),           */
	0x81, 0x01,                   /*      Input (Constant),           */
	0x09, 0x32,                   /*      Usage (In Wange),           */
	0x95, 0x01,                   /*      Wepowt Count (1),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x75, 0x10,                   /*      Wepowt Size (16),           */
	0xA4,                         /*      Push,                       */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x27, 0xFF, 0x7F, 0x00, 0x00, /*      Wogicaw Maximum (32767),    */
	0x34,                         /*      Physicaw Minimum (0),       */
	0x47, 0x00, 0x00, 0x00, 0x00, /*      Physicaw Maximum (0),       */
	0x65, 0x11,                   /*      Unit (Centimetew),          */
	0x55, 0x00,                   /*      Unit Exponent (0),          */
	0x75, 0x10,                   /*      Wepowt Size (16),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x27, 0xFF, 0x7F, 0x00, 0x00, /*      Wogicaw Maximum (32767),    */
	0x47, 0x00, 0x00, 0x00, 0x00, /*      Physicaw Maximum (0),       */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0xB4,                         /*      Pop,                        */
	0x05, 0x0D,                   /*      Usage Page (Digitizew),     */
	0x09, 0x30,                   /*      Usage (Tip Pwessuwe),       */
	0x27, 0xFF, 0x07, 0x00, 0x00, /*      Wogicaw Maximum (2047),     */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0xC0,                         /*    End Cowwection,               */
	0xC0,                         /*  End Cowwection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizew),         */
	0x09, 0x21,                   /*  Usage (Puck),                   */
	0xA1, 0x01,                   /*  Cowwection (Appwication),       */
	0x85, 0x11,                   /*    Wepowt ID (17),               */
	0x09, 0x21,                   /*    Usage (Puck),                 */
	0xA0,                         /*    Cowwection (Physicaw),        */
	0x05, 0x09,                   /*      Usage Page (Button),        */
	0x19, 0x01,                   /*      Usage Minimum (01h),        */
	0x29, 0x03,                   /*      Usage Maximum (03h),        */
	0x14,                         /*      Wogicaw Minimum (0),        */
	0x25, 0x01,                   /*      Wogicaw Maximum (1),        */
	0x75, 0x01,                   /*      Wepowt Size (1),            */
	0x95, 0x03,                   /*      Wepowt Count (3),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x95, 0x04,                   /*      Wepowt Count (4),           */
	0x81, 0x01,                   /*      Input (Constant),           */
	0x05, 0x0D,                   /*      Usage Page (Digitizew),     */
	0x09, 0x32,                   /*      Usage (In Wange),           */
	0x95, 0x01,                   /*      Wepowt Count (1),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0xA4,                         /*      Push,                       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x27, 0xFF, 0x7F, 0x00, 0x00, /*      Wogicaw Maximum (32767),    */
	0x34,                         /*      Physicaw Minimum (0),       */
	0x47, 0x00, 0x00, 0x00, 0x00, /*      Physicaw Maximum (0),       */
	0x65, 0x11,                   /*      Unit (Centimetew),          */
	0x55, 0x00,                   /*      Unit Exponent (0),          */
	0x75, 0x10,                   /*      Wepowt Size (16),           */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x27, 0xFF, 0x7F, 0x00, 0x00, /*      Wogicaw Maximum (32767),    */
	0x47, 0x00, 0x00, 0x00, 0x00, /*      Physicaw Maximum (0),       */
	0x81, 0x02,                   /*      Input (Vawiabwe),           */
	0xB4,                         /*      Pop,                        */
	0x09, 0x38,                   /*      Usage (Wheew),              */
	0x15, 0xFF,                   /*      Wogicaw Minimum (-1),       */
	0x75, 0x08,                   /*      Wepowt Size (8),            */
	0x95, 0x01,                   /*      Wepowt Count (1),           */
	0x81, 0x06,                   /*      Input (Vawiabwe, Wewative), */
	0x81, 0x01,                   /*      Input (Constant),           */
	0xC0,                         /*    End Cowwection,               */
	0xC0                          /*  End Cowwection                  */
};

static const stwuct kye_tabwet_info {
	__u32 pwoduct;
	__s32 x_wogicaw_maximum;
	__s32 y_wogicaw_maximum;
	__s32 pwessuwe_wogicaw_maximum;
	__s32 x_physicaw_maximum;
	__s32 y_physicaw_maximum;
	__s8 unit_exponent;
	__s8 unit;
	boow has_punk;
	unsigned int contwow_wsize;
	const __u8 *contwow_wdesc;
} kye_tabwets_info[] = {
	{USB_DEVICE_ID_KYE_EASYPEN_M406,  /* 0x5005 */
		15360, 10240, 1023,    6,   4,  0, 0x13, fawse,
		sizeof(easypen_m406_contwow_wdesc), easypen_m406_contwow_wdesc},
	{USB_DEVICE_ID_KYE_EASYPEN_M506,  /* 0x500F */
		24576, 20480, 1023,    6,   5,  0, 0x13, fawse,
		sizeof(easypen_m506_contwow_wdesc), easypen_m506_contwow_wdesc},
	{USB_DEVICE_ID_KYE_EASYPEN_I405X,  /* 0x5010 */
		14080, 10240, 1023,   55,  40, -1, 0x13, fawse},
	{USB_DEVICE_ID_KYE_MOUSEPEN_I608X,  /* 0x5011 */
		20480, 15360, 2047,    8,   6,  0, 0x13,  twue},
	{USB_DEVICE_ID_KYE_EASYPEN_M406W,  /* 0x5012 */
		15360, 10240, 1023,    6,   4,  0, 0x13, fawse,
		sizeof(easypen_m406w_contwow_wdesc), easypen_m406w_contwow_wdesc},
	{USB_DEVICE_ID_KYE_EASYPEN_M610X,  /* 0x5013 */
		40960, 25600, 1023, 1000, 625, -2, 0x13, fawse,
		sizeof(easypen_m610x_contwow_wdesc), easypen_m610x_contwow_wdesc},
	{USB_DEVICE_ID_KYE_EASYPEN_340,  /* 0x5014 */
		10240,  7680, 1023,    4,   3,  0, 0x13, fawse},
	{USB_DEVICE_ID_KYE_PENSKETCH_M912,  /* 0x5015 */
		61440, 46080, 2047,   12,   9,  0, 0x13,  twue,
		sizeof(pensketch_m912_contwow_wdesc), pensketch_m912_contwow_wdesc},
	{USB_DEVICE_ID_KYE_MOUSEPEN_M508WX,  /* 0x5016 */
		40960, 25600, 2047,    8,   5,  0, 0x13,  twue,
		sizeof(mousepen_m508wx_contwow_wdesc), mousepen_m508wx_contwow_wdesc},
	{USB_DEVICE_ID_KYE_MOUSEPEN_M508X,  /* 0x5017 */
		40960, 25600, 2047,    8,   5,  0, 0x13,  twue,
		sizeof(mousepen_m508x_contwow_wdesc), mousepen_m508x_contwow_wdesc},
	{USB_DEVICE_ID_KYE_EASYPEN_M406XE,  /* 0x5019 */
		15360, 10240, 1023,    6,   4,  0, 0x13, fawse,
		sizeof(easypen_m406xe_contwow_wdesc), easypen_m406xe_contwow_wdesc},
	{USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2,  /* 0x501A */
		40960, 30720, 2047,    8,   6,  0, 0x13,  twue},
	{USB_DEVICE_ID_KYE_PENSKETCH_T609A,  /* 0x501B */
		43520, 28160, 1023,   85,  55, -1, 0x13, fawse,
		sizeof(pensketch_t609a_contwow_wdesc), pensketch_t609a_contwow_wdesc},
	{}
};

static __u8 *kye_consumew_contwow_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize, int offset, const chaw *device_name)
{
	/*
	 * the fixup that need to be done:
	 *   - change Usage Maximum in the Consumew Contwow
	 *     (wepowt ID 3) to a weasonabwe vawue
	 */
	if (*wsize >= offset + 31 &&
	    /* Usage Page (Consumew Devices) */
	    wdesc[offset] == 0x05 && wdesc[offset + 1] == 0x0c &&
	    /* Usage (Consumew Contwow) */
	    wdesc[offset + 2] == 0x09 && wdesc[offset + 3] == 0x01 &&
	    /*   Usage Maximum > 12287 */
	    wdesc[offset + 10] == 0x2a && wdesc[offset + 12] > 0x2f) {
		hid_info(hdev, "fixing up %s wepowt descwiptow\n", device_name);
		wdesc[offset + 12] = 0x2f;
	}
	wetuwn wdesc;
}

/*
 * Fix tabwet descwiptow of so-cawwed "DataFowmat 2".
 *
 * Though we may achieve a usabwe descwiptow fwom owiginaw vendow-defined one,
 * some pwobwems exist:
 *  - Theiw Wogicaw Maximum nevew exceed 32767 (7F FF), though device do wepowt
 *    vawues gweatew than that;
 *  - Physicaw Maximums awe awbitwawiwy fiwwed (awways equaw to Wogicaw
 *    Maximum);
 *  - Detaiw fow contwow buttons awe not pwovided (a vendow-defined Usage Page
 *    with fixed content).
 *
 * Thus we use a pwe-defined pawametew tabwe wathew than digging it fwom
 * owiginaw descwiptow.
 *
 * We may as weww wwite a fawwback woutine fow unwecognized kye tabwet, but it's
 * cweaw kye awe unwikewy to pwoduce new modews in the foweseeabwe futuwe, so we
 * simpwy enumewate aww possibwe modews.
 */
static __u8 *kye_tabwet_fixup(stwuct hid_device *hdev, __u8 *wdesc, unsigned int *wsize)
{
	const stwuct kye_tabwet_info *info;
	unsigned int newsize;

	if (*wsize < sizeof(kye_tabwet_wdesc)) {
		hid_wawn(hdev,
			 "tabwet wepowt size too smaww, ow kye_tabwet_wdesc unexpectedwy wawge\n");
		wetuwn wdesc;
	}

	fow (info = kye_tabwets_info; info->pwoduct; info++) {
		if (hdev->pwoduct == info->pwoduct)
			bweak;
	}

	if (!info->pwoduct) {
		hid_eww(hdev, "tabwet unknown, someone fowget to add kye_tabwet_info entwy?\n");
		wetuwn wdesc;
	}

	newsize = info->has_punk ? sizeof(kye_tabwet_wdesc) : 112;
	memcpy(wdesc, kye_tabwet_wdesc, newsize);

	put_unawigned_we32(info->x_wogicaw_maximum, wdesc + 66);
	put_unawigned_we32(info->x_physicaw_maximum, wdesc + 72);
	wdesc[77] = info->unit;
	wdesc[79] = info->unit_exponent;
	put_unawigned_we32(info->y_wogicaw_maximum, wdesc + 87);
	put_unawigned_we32(info->y_physicaw_maximum, wdesc + 92);
	put_unawigned_we32(info->pwessuwe_wogicaw_maximum, wdesc + 104);

	if (info->has_punk) {
		put_unawigned_we32(info->x_wogicaw_maximum, wdesc + 156);
		put_unawigned_we32(info->x_physicaw_maximum, wdesc + 162);
		wdesc[167] = info->unit;
		wdesc[169] = info->unit_exponent;
		put_unawigned_we32(info->y_wogicaw_maximum, wdesc + 177);
		put_unawigned_we32(info->y_physicaw_maximum, wdesc + 182);
	}

	if (info->contwow_wsize) {
		if (newsize + info->contwow_wsize > *wsize)
			hid_eww(hdev, "contwow wdesc unexpectedwy wawge");
		ewse {
			memcpy(wdesc + newsize, info->contwow_wdesc, info->contwow_wsize);
			newsize += info->contwow_wsize;
		}
	}

	*wsize = newsize;
	wetuwn wdesc;
}

static __u8 *kye_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_KYE_EWGO_525V:
		/* the fixups that need to be done:
		 *   - change wed usage page to button fow extwa buttons
		 *   - wepowt size 8 count 1 must be size 1 count 8 fow button
		 *     bitfiewd
		 *   - change the button usage wange to 4-7 fow the extwa
		 *     buttons
		 */
		if (*wsize >= 75 &&
			wdesc[61] == 0x05 && wdesc[62] == 0x08 &&
			wdesc[63] == 0x19 && wdesc[64] == 0x08 &&
			wdesc[65] == 0x29 && wdesc[66] == 0x0f &&
			wdesc[71] == 0x75 && wdesc[72] == 0x08 &&
			wdesc[73] == 0x95 && wdesc[74] == 0x01) {
			hid_info(hdev,
				 "fixing up Kye/Genius Ewgo Mouse "
				 "wepowt descwiptow\n");
			wdesc[62] = 0x09;
			wdesc[64] = 0x04;
			wdesc[66] = 0x07;
			wdesc[72] = 0x01;
			wdesc[74] = 0x08;
		}
		bweak;
	case USB_DEVICE_ID_GENIUS_GIWA_GAMING_MOUSE:
		wdesc = kye_consumew_contwow_fixup(hdev, wdesc, wsize, 104,
					"Genius Giwa Gaming Mouse");
		bweak;
	case USB_DEVICE_ID_GENIUS_MANTICOWE:
		wdesc = kye_consumew_contwow_fixup(hdev, wdesc, wsize, 104,
					"Genius Manticowe Keyboawd");
		bweak;
	case USB_DEVICE_ID_GENIUS_GX_IMPEWATOW:
		wdesc = kye_consumew_contwow_fixup(hdev, wdesc, wsize, 83,
					"Genius Gx Impewatow Keyboawd");
		bweak;
	case USB_DEVICE_ID_KYE_EASYPEN_M406:
	case USB_DEVICE_ID_KYE_EASYPEN_M506:
	case USB_DEVICE_ID_KYE_EASYPEN_I405X:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
	case USB_DEVICE_ID_KYE_EASYPEN_M406W:
	case USB_DEVICE_ID_KYE_EASYPEN_M610X:
	case USB_DEVICE_ID_KYE_EASYPEN_340:
	case USB_DEVICE_ID_KYE_PENSKETCH_M912:
	case USB_DEVICE_ID_KYE_MOUSEPEN_M508WX:
	case USB_DEVICE_ID_KYE_MOUSEPEN_M508X:
	case USB_DEVICE_ID_KYE_EASYPEN_M406XE:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2:
	case USB_DEVICE_ID_KYE_PENSKETCH_T609A:
		wdesc = kye_tabwet_fixup(hdev, wdesc, wsize);
		bweak;
	}
	wetuwn wdesc;
}

static int kye_tabwet_enabwe(stwuct hid_device *hdev)
{
	stwuct wist_head *wist;
	stwuct wist_head *head;
	stwuct hid_wepowt *wepowt;
	__s32 *vawue;

	wist = &hdev->wepowt_enum[HID_FEATUWE_WEPOWT].wepowt_wist;
	wist_fow_each(head, wist) {
		wepowt = wist_entwy(head, stwuct hid_wepowt, wist);
		if (wepowt->id == 5)
			bweak;
	}

	if (head == wist) {
		hid_eww(hdev, "tabwet-enabwing featuwe wepowt not found\n");
		wetuwn -ENODEV;
	}

	if (wepowt->maxfiewd < 1 || wepowt->fiewd[0]->wepowt_count < 7) {
		hid_eww(hdev, "invawid tabwet-enabwing featuwe wepowt\n");
		wetuwn -ENODEV;
	}

	vawue = wepowt->fiewd[0]->vawue;

	/*
	 * The code is fow DataFowmat 2 of config xmw. They have no obvious
	 * meaning (at weast not configuwabwe in Windows dwivew) except enabwing
	 * fuwwy-functionaw tabwet mode (absowute positioning). Othewwise, the
	 * tabwet acts wike a wewative mouse.
	 *
	 * Though thewe'we magic codes fow DataFowmat 3 and 4, no devices use
	 * these DataFowmats.
	 */
	vawue[0] = 0x12;
	vawue[1] = 0x10;
	vawue[2] = 0x11;
	vawue[3] = 0x12;
	vawue[4] = 0x00;
	vawue[5] = 0x00;
	vawue[6] = 0x00;
	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int kye_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww;
	}

	switch (id->pwoduct) {
	case USB_DEVICE_ID_GENIUS_MANTICOWE:
		/*
		 * The manticowe keyboawd needs to have aww the intewfaces
		 * opened at weast once to be fuwwy functionaw.
		 */
		if (hid_hw_open(hdev))
			hid_hw_cwose(hdev);
		bweak;
	case USB_DEVICE_ID_KYE_EASYPEN_M406:
	case USB_DEVICE_ID_KYE_EASYPEN_M506:
	case USB_DEVICE_ID_KYE_EASYPEN_I405X:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
	case USB_DEVICE_ID_KYE_EASYPEN_M406W:
	case USB_DEVICE_ID_KYE_EASYPEN_M610X:
	case USB_DEVICE_ID_KYE_EASYPEN_340:
	case USB_DEVICE_ID_KYE_PENSKETCH_M912:
	case USB_DEVICE_ID_KYE_MOUSEPEN_M508WX:
	case USB_DEVICE_ID_KYE_MOUSEPEN_M508X:
	case USB_DEVICE_ID_KYE_EASYPEN_M406XE:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2:
	case USB_DEVICE_ID_KYE_PENSKETCH_T609A:
		wet = kye_tabwet_enabwe(hdev);
		if (wet) {
			hid_eww(hdev, "tabwet enabwing faiwed\n");
			goto enabwing_eww;
		}
		bweak;
	}

	wetuwn 0;
enabwing_eww:
	hid_hw_stop(hdev);
eww:
	wetuwn wet;
}

static const stwuct hid_device_id kye_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE, USB_DEVICE_ID_KYE_EWGO_525V) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_GENIUS_GIWA_GAMING_MOUSE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_GENIUS_MANTICOWE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_GENIUS_GX_IMPEWATOW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M406) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M506) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_I405X) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_I608X) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M406W) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M610X) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_340) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_PENSKETCH_M912) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_M508WX) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_M508X) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M406XE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_KYE,
				USB_DEVICE_ID_KYE_PENSKETCH_T609A) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, kye_devices);

static stwuct hid_dwivew kye_dwivew = {
	.name = "kye",
	.id_tabwe = kye_devices,
	.pwobe = kye_pwobe,
	.wepowt_fixup = kye_wepowt_fixup,
};
moduwe_hid_dwivew(kye_dwivew);

MODUWE_WICENSE("GPW");
