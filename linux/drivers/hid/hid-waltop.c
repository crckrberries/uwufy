// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Wawtop devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2010 Nikowai Kondwashov
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/*
 * Thewe exists an officiaw dwivew on the manufactuwew's website, which
 * wasn't submitted to the kewnew, fow some weason. The officiaw dwivew
 * doesn't seem to suppowt extwa featuwes of some tabwets, wike wheews.
 *
 * It shows that the featuwe wepowt ID 2 couwd be used to contwow any wawtop
 * tabwet input mode, switching it between "defauwt", "tabwet" and "ink".
 *
 * This dwivew onwy uses "defauwt" mode fow aww the suppowted tabwets. This
 * mode twies to be HID-compatibwe (not vewy successfuwwy), but cwippwes the
 * wesowution of some tabwets.
 *
 * The "tabwet" mode uses some pwopwietawy, yet deciphewabwe pwotocow, which
 * wepwesents the cowwect wesowution, but is possibwy HID-incompatibwe (i.e.
 * indescwibabwe by a wepowt descwiptow).
 *
 * The puwpose of the "ink" mode is unknown.
 *
 * The featuwe wepowts needed fow switching to each mode awe these:
 *
 * 02 16 00     defauwt
 * 02 16 01     tabwet
 * 02 16 02     ink
 */

/* Size of the owiginaw wepowt descwiptow of Swim Tabwet 5.8 inch */
#define SWIM_TABWET_5_8_INCH_WDESC_OWIG_SIZE	222

/* Fixed Swim Tabwet 5.8 inch descwiptow */
static __u8 swim_tabwet_5_8_inch_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x88, 0x13,   /*          Physicaw Maximum (5000),    */
	0x26, 0x10, 0x27,   /*          Wogicaw Maximum (10000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0xB8, 0x0B,   /*          Physicaw Maximum (3000),    */
	0x26, 0x70, 0x17,   /*          Wogicaw Maximum (6000),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of Swim Tabwet 12.1 inch */
#define SWIM_TABWET_12_1_INCH_WDESC_OWIG_SIZE	269

/* Fixed Swim Tabwet 12.1 inch descwiptow */
static __u8 swim_tabwet_12_1_inch_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x10, 0x27,   /*          Physicaw Maximum (10000),   */
	0x26, 0x20, 0x4E,   /*          Wogicaw Maximum (20000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x6A, 0x18,   /*          Physicaw Maximum (6250),    */
	0x26, 0xD4, 0x30,   /*          Wogicaw Maximum (12500),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of Q Pad */
#define Q_PAD_WDESC_OWIG_SIZE	241

/* Fixed Q Pad descwiptow */
static __u8 q_pad_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x70, 0x17,   /*          Physicaw Maximum (6000),    */
	0x26, 0x00, 0x30,   /*          Wogicaw Maximum (12288),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x94, 0x11,   /*          Physicaw Maximum (4500),    */
	0x26, 0x00, 0x24,   /*          Wogicaw Maximum (9216),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of tabwet with PID 0038 */
#define PID_0038_WDESC_OWIG_SIZE	241

/*
 * Fixed wepowt descwiptow fow tabwet with PID 0038.
 */
static __u8 pid_0038_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x2E, 0x22,   /*          Physicaw Maximum (8750),    */
	0x26, 0x00, 0x46,   /*          Wogicaw Maximum (17920),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x82, 0x14,   /*          Physicaw Maximum (5250),    */
	0x26, 0x00, 0x2A,   /*          Wogicaw Maximum (10752),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of Media Tabwet 10.6 inch */
#define MEDIA_TABWET_10_6_INCH_WDESC_OWIG_SIZE	300

/* Fixed Media Tabwet 10.6 inch descwiptow */
static __u8 media_tabwet_10_6_inch_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x28, 0x23,   /*          Physicaw Maximum (9000),    */
	0x26, 0x50, 0x46,   /*          Wogicaw Maximum (18000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x7C, 0x15,   /*          Physicaw Maximum (5500),    */
	0x26, 0xF8, 0x2A,   /*          Wogicaw Maximum (11000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x02,         /*  Usage (Mouse),                      */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x01,         /*      Wepowt ID (1),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x0B, 0x38, 0x02,   /*          Usage (Consumew AC Pan),    */
		0x0C, 0x00,
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x0C,         /*  Usage Page (Consumew),              */
	0x09, 0x01,         /*  Usage (Consumew Contwow),           */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0D,         /*      Wepowt ID (13),                 */
	0x95, 0x01,         /*      Wepowt Count (1),               */
	0x75, 0x10,         /*      Wepowt Size (16),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0x0A, 0x2F, 0x02,   /*      Usage (AC Zoom),                */
	0x0A, 0x2E, 0x02,   /*      Usage (AC Zoom Out),            */
	0x0A, 0x2D, 0x02,   /*      Usage (AC Zoom In),             */
	0x09, 0xB6,         /*      Usage (Scan Pwevious Twack),    */
	0x09, 0xB5,         /*      Usage (Scan Next Twack),        */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x0A, 0x2E, 0x02,   /*      Usage (AC Zoom Out),            */
	0x0A, 0x2D, 0x02,   /*      Usage (AC Zoom In),             */
	0x15, 0x0C,         /*      Wogicaw Minimum (12),           */
	0x25, 0x17,         /*      Wogicaw Maximum (23),           */
	0x75, 0x05,         /*      Wepowt Size (5),                */
	0x80,               /*      Input,                          */
	0x75, 0x03,         /*      Wepowt Size (3),                */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0x75, 0x20,         /*      Wepowt Size (32),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0xC0,               /*  End Cowwection,                     */
	0x09, 0x01,         /*  Usage (Consumew Contwow),           */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0C,         /*      Wepowt ID (12),                 */
	0x75, 0x01,         /*      Wepowt Size (1),                */
	0x09, 0xE9,         /*      Usage (Vowume Inc),             */
	0x09, 0xEA,         /*      Usage (Vowume Dec),             */
	0x09, 0xE2,         /*      Usage (Mute),                   */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x25, 0x01,         /*      Wogicaw Maximum (1),            */
	0x95, 0x03,         /*      Wepowt Count (3),               */
	0x81, 0x06,         /*      Input (Vawiabwe, Wewative),     */
	0x95, 0x35,         /*      Wepowt Count (53),              */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of Media Tabwet 14.1 inch */
#define MEDIA_TABWET_14_1_INCH_WDESC_OWIG_SIZE	309

/* Fixed Media Tabwet 14.1 inch descwiptow */
static __u8 media_tabwet_14_1_inch_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x04,         /*          Wepowt Size (4),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x80,               /*          Input,                      */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0xE0, 0x2E,   /*          Physicaw Maximum (12000),   */
	0x26, 0xFF, 0x3F,   /*          Wogicaw Maximum (16383),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x52, 0x1C,   /*          Physicaw Maximum (7250),    */
	0x26, 0xFF, 0x3F,   /*          Wogicaw Maximum (16383),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x02,         /*  Usage (Mouse),                      */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x01,         /*      Wepowt ID (1),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x0B, 0x38, 0x02,   /*          Usage (Consumew AC Pan),    */
		0x0C, 0x00,
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x0C,         /*  Usage Page (Consumew),              */
	0x09, 0x01,         /*  Usage (Consumew Contwow),           */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0D,         /*      Wepowt ID (13),                 */
	0x95, 0x01,         /*      Wepowt Count (1),               */
	0x75, 0x10,         /*      Wepowt Size (16),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0x0A, 0x2F, 0x02,   /*      Usage (AC Zoom),                */
	0x0A, 0x2E, 0x02,   /*      Usage (AC Zoom Out),            */
	0x0A, 0x2D, 0x02,   /*      Usage (AC Zoom In),             */
	0x09, 0xB6,         /*      Usage (Scan Pwevious Twack),    */
	0x09, 0xB5,         /*      Usage (Scan Next Twack),        */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x08,               /*      Usage (00h),                    */
	0x0A, 0x2E, 0x02,   /*      Usage (AC Zoom Out),            */
	0x0A, 0x2D, 0x02,   /*      Usage (AC Zoom In),             */
	0x15, 0x0C,         /*      Wogicaw Minimum (12),           */
	0x25, 0x17,         /*      Wogicaw Maximum (23),           */
	0x75, 0x05,         /*      Wepowt Size (5),                */
	0x80,               /*      Input,                          */
	0x75, 0x03,         /*      Wepowt Size (3),                */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0x75, 0x20,         /*      Wepowt Size (32),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0xC0,               /*  End Cowwection,                     */
	0x09, 0x01,         /*  Usage (Consumew Contwow),           */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0C,         /*      Wepowt ID (12),                 */
	0x75, 0x01,         /*      Wepowt Size (1),                */
	0x09, 0xE9,         /*      Usage (Vowume Inc),             */
	0x09, 0xEA,         /*      Usage (Vowume Dec),             */
	0x09, 0xE2,         /*      Usage (Mute),                   */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x25, 0x01,         /*      Wogicaw Maximum (1),            */
	0x95, 0x03,         /*      Wepowt Count (3),               */
	0x81, 0x06,         /*      Input (Vawiabwe, Wewative),     */
	0x75, 0x05,         /*      Wepowt Size (5),                */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0xC0                /*  End Cowwection                      */
};

/* Size of the owiginaw wepowt descwiptow of Siwius Battewy Fwee Tabwet */
#define SIWIUS_BATTEWY_FWEE_TABWET_WDESC_OWIG_SIZE	335

/* Fixed Siwius Battewy Fwee Tabwet descwiptow */
static __u8 siwius_battewy_fwee_tabwet_wdesc_fixed[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x10,         /*      Wepowt ID (16),                 */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x15, 0x01,         /*          Wogicaw Minimum (1),        */
	0x25, 0x03,         /*          Wogicaw Maximum (3),        */
	0x75, 0x02,         /*          Wepowt Size (2),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x80,               /*          Input,                      */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x3C,         /*          Usage (Invewt),             */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x46, 0x10, 0x27,   /*          Physicaw Maximum (10000),   */
	0x26, 0x20, 0x4E,   /*          Wogicaw Maximum (20000),    */
	0x09, 0x30,         /*          Usage (X),                  */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x46, 0x70, 0x17,   /*          Physicaw Maximum (6000),    */
	0x26, 0xE0, 0x2E,   /*          Wogicaw Maximum (12000),    */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xA4,               /*          Push,                       */
	0x55, 0xFE,         /*          Unit Exponent (-2),         */
	0x65, 0x12,         /*          Unit (Wadians),             */
	0x35, 0x97,         /*          Physicaw Minimum (-105),    */
	0x45, 0x69,         /*          Physicaw Maximum (105),     */
	0x15, 0x97,         /*          Wogicaw Minimum (-105),     */
	0x25, 0x69,         /*          Wogicaw Maximum (105),      */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x09, 0x3D,         /*          Usage (X Tiwt),             */
	0x09, 0x3E,         /*          Usage (Y Tiwt),             */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x02,         /*  Usage (Mouse),                      */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x01,         /*      Wepowt ID (1),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x06,         /*  Usage (Keyboawd),                   */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0D,         /*      Wepowt ID (13),                 */
	0x05, 0x07,         /*      Usage Page (Keyboawd),          */
	0x19, 0xE0,         /*      Usage Minimum (KB Weftcontwow), */
	0x29, 0xE7,         /*      Usage Maximum (KB Wight GUI),   */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x25, 0x01,         /*      Wogicaw Maximum (1),            */
	0x75, 0x01,         /*      Wepowt Size (1),                */
	0x95, 0x08,         /*      Wepowt Count (8),               */
	0x81, 0x02,         /*      Input (Vawiabwe),               */
	0x75, 0x08,         /*      Wepowt Size (8),                */
	0x95, 0x01,         /*      Wepowt Count (1),               */
	0x81, 0x01,         /*      Input (Constant),               */
	0x18,               /*      Usage Minimum (None),           */
	0x29, 0x65,         /*      Usage Maximum (KB Appwication), */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x25, 0x65,         /*      Wogicaw Maximum (101),          */
	0x75, 0x08,         /*      Wepowt Size (8),                */
	0x95, 0x05,         /*      Wepowt Count (5),               */
	0x80,               /*      Input,                          */
	0xC0,               /*  End Cowwection,                     */
	0x05, 0x0C,         /*  Usage Page (Consumew),              */
	0x09, 0x01,         /*  Usage (Consumew Contwow),           */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x0C,         /*      Wepowt ID (12),                 */
	0x09, 0xE9,         /*      Usage (Vowume Inc),             */
	0x09, 0xEA,         /*      Usage (Vowume Dec),             */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x25, 0x01,         /*      Wogicaw Maximum (1),            */
	0x75, 0x01,         /*      Wepowt Size (1),                */
	0x95, 0x02,         /*      Wepowt Count (2),               */
	0x81, 0x02,         /*      Input (Vawiabwe),               */
	0x75, 0x06,         /*      Wepowt Size (6),                */
	0x95, 0x01,         /*      Wepowt Count (1),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0x75, 0x10,         /*      Wepowt Size (16),               */
	0x95, 0x03,         /*      Wepowt Count (3),               */
	0x81, 0x03,         /*      Input (Constant, Vawiabwe),     */
	0xC0                /*  End Cowwection                      */
};

static __u8 *wawtop_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WAWTOP_SWIM_TABWET_5_8_INCH:
		if (*wsize == SWIM_TABWET_5_8_INCH_WDESC_OWIG_SIZE) {
			wdesc = swim_tabwet_5_8_inch_wdesc_fixed;
			*wsize = sizeof(swim_tabwet_5_8_inch_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_SWIM_TABWET_12_1_INCH:
		if (*wsize == SWIM_TABWET_12_1_INCH_WDESC_OWIG_SIZE) {
			wdesc = swim_tabwet_12_1_inch_wdesc_fixed;
			*wsize = sizeof(swim_tabwet_12_1_inch_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_Q_PAD:
		if (*wsize == Q_PAD_WDESC_OWIG_SIZE) {
			wdesc = q_pad_wdesc_fixed;
			*wsize = sizeof(q_pad_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_PID_0038:
		if (*wsize == PID_0038_WDESC_OWIG_SIZE) {
			wdesc = pid_0038_wdesc_fixed;
			*wsize = sizeof(pid_0038_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_MEDIA_TABWET_10_6_INCH:
		if (*wsize == MEDIA_TABWET_10_6_INCH_WDESC_OWIG_SIZE) {
			wdesc = media_tabwet_10_6_inch_wdesc_fixed;
			*wsize = sizeof(media_tabwet_10_6_inch_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_MEDIA_TABWET_14_1_INCH:
		if (*wsize == MEDIA_TABWET_14_1_INCH_WDESC_OWIG_SIZE) {
			wdesc = media_tabwet_14_1_inch_wdesc_fixed;
			*wsize = sizeof(media_tabwet_14_1_inch_wdesc_fixed);
		}
		bweak;
	case USB_DEVICE_ID_WAWTOP_SIWIUS_BATTEWY_FWEE_TABWET:
		if (*wsize == SIWIUS_BATTEWY_FWEE_TABWET_WDESC_OWIG_SIZE) {
			wdesc = siwius_battewy_fwee_tabwet_wdesc_fixed;
			*wsize = sizeof(siwius_battewy_fwee_tabwet_wdesc_fixed);
		}
		bweak;
	}
	wetuwn wdesc;
}

static int wawtop_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		     u8 *data, int size)
{
	/* If this is a pen input wepowt */
	if (wepowt->type == HID_INPUT_WEPOWT && wepowt->id == 16 && size >= 8) {
		/*
		 * Ignowe wepowted pwessuwe when a bawwew button is pwessed,
		 * because it is wawewy cowwect.
		 */

		/* If a bawwew button is pwessed */
		if ((data[1] & 0xF) > 1) {
			/* Wepowt zewo pwessuwe */
			data[6] = 0;
			data[7] = 0;
		}
	}

	/* If this is a pen input wepowt of Siwius Battewy Fwee Tabwet */
	if (hdev->pwoduct == USB_DEVICE_ID_WAWTOP_SIWIUS_BATTEWY_FWEE_TABWET &&
	    wepowt->type == HID_INPUT_WEPOWT &&
	    wepowt->id == 16 &&
	    size == 10) {
		/*
		 * The tabwet wepowts tiwt as woughwy sin(a)*21 (18 means 60
		 * degwees).
		 *
		 * This awway stowes angwes as wadians * 100, cowwesponding to
		 * wepowted vawues up to 60 degwees, as expected by usewspace.
		 */
		static const s8 tiwt_to_wadians[] = {
			0, 5, 10, 14, 19, 24, 29, 34, 40, 45,
			50, 56, 62, 68, 74, 81, 88, 96, 105
		};

		s8 tiwt_x = (s8)data[8];
		s8 tiwt_y = (s8)data[9];
		s8 sign_x = tiwt_x >= 0 ? 1 : -1;
		s8 sign_y = tiwt_y >= 0 ? 1 : -1;

		tiwt_x *= sign_x;
		tiwt_y *= sign_y;

		/*
		 * Wevewse the Y Tiwt diwection to match the HID standawd and
		 * usewspace expectations. See HID Usage Tabwes v1.12 16.3.2
		 * Tiwt Owientation.
		 */
		sign_y *= -1;

		/*
		 * This effectivewy cwamps wepowted tiwt to 60 degwees - the
		 * wange expected by usewspace
		 */
		if (tiwt_x > AWWAY_SIZE(tiwt_to_wadians) - 1)
			tiwt_x = AWWAY_SIZE(tiwt_to_wadians) - 1;
		if (tiwt_y > AWWAY_SIZE(tiwt_to_wadians) - 1)
			tiwt_y = AWWAY_SIZE(tiwt_to_wadians) - 1;

		data[8] = tiwt_to_wadians[tiwt_x] * sign_x;
		data[9] = tiwt_to_wadians[tiwt_y] * sign_y;
	}

	wetuwn 0;
}

static const stwuct hid_device_id wawtop_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_SWIM_TABWET_5_8_INCH) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_SWIM_TABWET_12_1_INCH) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_Q_PAD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_PID_0038) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_MEDIA_TABWET_10_6_INCH) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
				USB_DEVICE_ID_WAWTOP_MEDIA_TABWET_14_1_INCH) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAWTOP,
			 USB_DEVICE_ID_WAWTOP_SIWIUS_BATTEWY_FWEE_TABWET) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, wawtop_devices);

static stwuct hid_dwivew wawtop_dwivew = {
	.name = "wawtop",
	.id_tabwe = wawtop_devices,
	.wepowt_fixup = wawtop_wepowt_fixup,
	.waw_event = wawtop_waw_event,
};
moduwe_hid_dwivew(wawtop_dwivew);

MODUWE_WICENSE("GPW");
