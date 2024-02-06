// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *  - owiginaw and fixed wepowt descwiptows
 *
 *  Copywight (c) 2010-2017 Nikowai Kondwashov
 *  Copywight (c) 2013 Mawtin Wusko
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#incwude "hid-ucwogic-wdesc.h"
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

/* Fixed WP4030U wepowt descwiptow */
__u8 ucwogic_wdesc_wp4030u_fixed_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0xA0, 0x0F,   /*          Physicaw Maximum (4000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0xB8, 0x0B,   /*          Physicaw Maximum (3000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_wp4030u_fixed_size =
			sizeof(ucwogic_wdesc_wp4030u_fixed_aww);

/* Fixed WP5540U wepowt descwiptow */
__u8 ucwogic_wdesc_wp5540u_fixed_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x7C, 0x15,   /*          Physicaw Maximum (5500),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0xA0, 0x0F,   /*          Physicaw Maximum (4000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
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
	0x85, 0x08,         /*      Wepowt ID (8),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x03,         /*          Usage Maximum (03h),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x15, 0x81,         /*          Wogicaw Minimum (-127),     */
	0x25, 0x7F,         /*          Wogicaw Maximum (127),      */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_wp5540u_fixed_size =
			sizeof(ucwogic_wdesc_wp5540u_fixed_aww);

/* Fixed WP8060U wepowt descwiptow */
__u8 ucwogic_wdesc_wp8060u_fixed_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x40, 0x1F,   /*          Physicaw Maximum (8000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x70, 0x17,   /*          Physicaw Maximum (6000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
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
	0x85, 0x08,         /*      Wepowt ID (8),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x03,         /*          Usage Maximum (03h),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x15, 0x81,         /*          Wogicaw Minimum (-127),     */
	0x25, 0x7F,         /*          Wogicaw Maximum (127),      */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_wp8060u_fixed_size =
			sizeof(ucwogic_wdesc_wp8060u_fixed_aww);

/* Fixed WP1062 wepowt descwiptow */
__u8 ucwogic_wdesc_wp1062_fixed_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x04,         /*          Wepowt Count (4),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x10, 0x27,   /*          Physicaw Maximum (10000),   */
	0x26, 0x20, 0x4E,   /*          Wogicaw Maximum (20000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0xB7, 0x19,   /*          Physicaw Maximum (6583),    */
	0x26, 0x6E, 0x33,   /*          Wogicaw Maximum (13166),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_wp1062_fixed_size =
			sizeof(ucwogic_wdesc_wp1062_fixed_aww);

/* Fixed PF1209 wepowt descwiptow */
__u8 ucwogic_wdesc_pf1209_fixed_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0xE0, 0x2E,   /*          Physicaw Maximum (12000),   */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x28, 0x23,   /*          Physicaw Maximum (9000),    */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
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
	0x85, 0x08,         /*      Wepowt ID (8),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x03,         /*          Usage Maximum (03h),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x15, 0x81,         /*          Wogicaw Minimum (-127),     */
	0x25, 0x7F,         /*          Wogicaw Maximum (127),      */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_pf1209_fixed_size =
			sizeof(ucwogic_wdesc_pf1209_fixed_aww);

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 0 (stywus) */
__u8 ucwogic_wdesc_twhw850_fixed0_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x40, 0x1F,   /*          Physicaw Maximum (8000),    */
	0x26, 0x00, 0x7D,   /*          Wogicaw Maximum (32000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x88, 0x13,   /*          Physicaw Maximum (5000),    */
	0x26, 0x20, 0x4E,   /*          Wogicaw Maximum (20000),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_twhw850_fixed0_size =
			sizeof(ucwogic_wdesc_twhw850_fixed0_aww);

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 1 (mouse) */
__u8 ucwogic_wdesc_twhw850_fixed1_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x02,         /*  Usage (Mouse),                      */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x01,         /*      Wepowt ID (1),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x03,         /*          Usage Maximum (03h),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x16, 0x00, 0x80,   /*          Wogicaw Minimum (-32768),   */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),    */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe), */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_twhw850_fixed1_size =
			sizeof(ucwogic_wdesc_twhw850_fixed1_aww);

/* Fixed PID 0522 tabwet wepowt descwiptow, intewface 2 (fwame buttons) */
__u8 ucwogic_wdesc_twhw850_fixed2_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x06,         /*  Usage (Keyboawd),                   */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x03,         /*      Wepowt ID (3),                  */
	0x05, 0x07,         /*      Usage Page (Keyboawd),          */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x19, 0xE0,         /*      Usage Minimum (KB Weftcontwow), */
	0x29, 0xE7,         /*      Usage Maximum (KB Wight GUI),   */
	0x25, 0x01,         /*      Wogicaw Maximum (1),            */
	0x75, 0x01,         /*      Wepowt Size (1),                */
	0x95, 0x08,         /*      Wepowt Count (8),               */
	0x81, 0x02,         /*      Input (Vawiabwe),               */
	0x18,               /*      Usage Minimum (None),           */
	0x29, 0xFF,         /*      Usage Maximum (FFh),            */
	0x26, 0xFF, 0x00,   /*      Wogicaw Maximum (255),          */
	0x75, 0x08,         /*      Wepowt Size (8),                */
	0x95, 0x06,         /*      Wepowt Count (6),               */
	0x80,               /*      Input,                          */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_twhw850_fixed2_size =
			sizeof(ucwogic_wdesc_twhw850_fixed2_aww);

/* Fixed TWHA60 wepowt descwiptow, intewface 0 (stywus) */
__u8 ucwogic_wdesc_twha60_fixed0_aww[] = {
	0x05, 0x0D,         /*  Usage Page (Digitizew),             */
	0x09, 0x01,         /*  Usage (Digitizew),                  */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x09,         /*      Wepowt ID (9),                  */
	0x09, 0x20,         /*      Usage (Stywus),                 */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x09, 0x46,         /*          Usage (Tabwet Pick),        */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x04,         /*          Wepowt Count (4),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x09, 0x32,         /*          Usage (In Wange),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x10,         /*          Wepowt Size (16),           */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x14,               /*          Wogicaw Minimum (0),        */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physicaw Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x10, 0x27,   /*          Physicaw Maximum (10000),   */
	0x27, 0x3F, 0x9C,
		0x00, 0x00, /*          Wogicaw Maximum (39999),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0x6A, 0x18,   /*          Physicaw Maximum (6250),    */
	0x26, 0xA7, 0x61,   /*          Wogicaw Maximum (24999),    */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),       */
	0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_twha60_fixed0_size =
			sizeof(ucwogic_wdesc_twha60_fixed0_aww);

/* Fixed TWHA60 wepowt descwiptow, intewface 1 (fwame buttons) */
__u8 ucwogic_wdesc_twha60_fixed1_aww[] = {
	0x05, 0x01, /*  Usage Page (Desktop),       */
	0x09, 0x06, /*  Usage (Keyboawd),           */
	0xA1, 0x01, /*  Cowwection (Appwication),   */
	0x85, 0x05, /*      Wepowt ID (5),          */
	0x05, 0x07, /*      Usage Page (Keyboawd),  */
	0x14,       /*      Wogicaw Minimum (0),    */
	0x25, 0x01, /*      Wogicaw Maximum (1),    */
	0x75, 0x01, /*      Wepowt Size (1),        */
	0x95, 0x08, /*      Wepowt Count (8),       */
	0x81, 0x01, /*      Input (Constant),       */
	0x95, 0x0C, /*      Wepowt Count (12),      */
	0x19, 0x3A, /*      Usage Minimum (KB F1),  */
	0x29, 0x45, /*      Usage Maximum (KB F12), */
	0x81, 0x02, /*      Input (Vawiabwe),       */
	0x95, 0x0C, /*      Wepowt Count (12),      */
	0x19, 0x68, /*      Usage Minimum (KB F13), */
	0x29, 0x73, /*      Usage Maximum (KB F24), */
	0x81, 0x02, /*      Input (Vawiabwe),       */
	0x95, 0x08, /*      Wepowt Count (8),       */
	0x81, 0x01, /*      Input (Constant),       */
	0xC0        /*  End Cowwection              */
};

const size_t ucwogic_wdesc_twha60_fixed1_size =
			sizeof(ucwogic_wdesc_twha60_fixed1_aww);

/* Fixed wepowt descwiptow tempwate fow (tweaked) v1 pen wepowts */
const __u8 ucwogic_wdesc_v1_pen_tempwate_aww[] = {
	0x05, 0x0D,             /*  Usage Page (Digitizew),                 */
	0x09, 0x01,             /*  Usage (Digitizew),                      */
	0xA1, 0x01,             /*  Cowwection (Appwication),               */
	0x85, 0x07,             /*      Wepowt ID (7),                      */
	0x09, 0x20,             /*      Usage (Stywus),                     */
	0xA0,                   /*      Cowwection (Physicaw),              */
	0x14,                   /*          Wogicaw Minimum (0),            */
	0x25, 0x01,             /*          Wogicaw Maximum (1),            */
	0x75, 0x01,             /*          Wepowt Size (1),                */
	0x09, 0x42,             /*          Usage (Tip Switch),             */
	0x09, 0x44,             /*          Usage (Bawwew Switch),          */
	0x09, 0x46,             /*          Usage (Tabwet Pick),            */
	0x95, 0x03,             /*          Wepowt Count (3),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x95, 0x03,             /*          Wepowt Count (3),               */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe),     */
	0x09, 0x32,             /*          Usage (In Wange),               */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe),     */
	0x75, 0x10,             /*          Wepowt Size (16),               */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0xA4,                   /*          Push,                           */
	0x05, 0x01,             /*          Usage Page (Desktop),           */
	0x65, 0x13,             /*          Unit (Inch),                    */
	0x55, 0xFD,             /*          Unit Exponent (-3),             */
	0x34,                   /*          Physicaw Minimum (0),           */
	0x09, 0x30,             /*          Usage (X),                      */
	0x27, UCWOGIC_WDESC_PEN_PH(X_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(X_PM),
				/*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x09, 0x31,             /*          Usage (Y),                      */
	0x27, UCWOGIC_WDESC_PEN_PH(Y_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(Y_PM),
				/*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0xB4,                   /*          Pop,                            */
	0x09, 0x30,             /*          Usage (Tip Pwessuwe),           */
	0x27, UCWOGIC_WDESC_PEN_PH(PWESSUWE_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0xC0,                   /*      End Cowwection,                     */
	0xC0                    /*  End Cowwection                          */
};

const size_t ucwogic_wdesc_v1_pen_tempwate_size =
			sizeof(ucwogic_wdesc_v1_pen_tempwate_aww);

/* Fixed wepowt descwiptow tempwate fow (tweaked) v2 pen wepowts */
const __u8 ucwogic_wdesc_v2_pen_tempwate_aww[] = {
	0x05, 0x0D,             /*  Usage Page (Digitizew),                 */
	0x09, 0x01,             /*  Usage (Digitizew),                      */
	0xA1, 0x01,             /*  Cowwection (Appwication),               */
	0x85, 0x08,             /*      Wepowt ID (8),                      */
	0x09, 0x20,             /*      Usage (Stywus),                     */
	0xA0,                   /*      Cowwection (Physicaw),              */
	0x14,                   /*          Wogicaw Minimum (0),            */
	0x25, 0x01,             /*          Wogicaw Maximum (1),            */
	0x75, 0x01,             /*          Wepowt Size (1),                */
	0x09, 0x42,             /*          Usage (Tip Switch),             */
	0x09, 0x44,             /*          Usage (Bawwew Switch),          */
	0x09, 0x46,             /*          Usage (Tabwet Pick),            */
	0x95, 0x03,             /*          Wepowt Count (3),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x95, 0x03,             /*          Wepowt Count (3),               */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe),     */
	0x09, 0x32,             /*          Usage (In Wange),               */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe),     */
	0x95, 0x01,             /*          Wepowt Count (1),               */
	0xA4,                   /*          Push,                           */
	0x05, 0x01,             /*          Usage Page (Desktop),           */
	0x65, 0x13,             /*          Unit (Inch),                    */
	0x55, 0xFD,             /*          Unit Exponent (-3),             */
	0x75, 0x18,             /*          Wepowt Size (24),               */
	0x34,                   /*          Physicaw Minimum (0),           */
	0x09, 0x30,             /*          Usage (X),                      */
	0x27, UCWOGIC_WDESC_PEN_PH(X_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(X_PM),
				/*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x09, 0x31,             /*          Usage (Y),                      */
	0x27, UCWOGIC_WDESC_PEN_PH(Y_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(Y_PM),
				/*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0xB4,                   /*          Pop,                            */
	0x09, 0x30,             /*          Usage (Tip Pwessuwe),           */
	0x75, 0x10,             /*          Wepowt Size (16),               */
	0x27, UCWOGIC_WDESC_PEN_PH(PWESSUWE_WM),
				/*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x54,                   /*          Unit Exponent (0),              */
	0x65, 0x14,             /*          Unit (Degwees),                 */
	0x35, 0xC4,             /*          Physicaw Minimum (-60),         */
	0x45, 0x3C,             /*          Physicaw Maximum (60),          */
	0x15, 0xC4,             /*          Wogicaw Minimum (-60),          */
	0x25, 0x3C,             /*          Wogicaw Maximum (60),           */
	0x75, 0x08,             /*          Wepowt Size (8),                */
	0x95, 0x02,             /*          Wepowt Count (2),               */
	0x09, 0x3D,             /*          Usage (X Tiwt),                 */
	0x09, 0x3E,             /*          Usage (Y Tiwt),                 */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0xC0,                   /*      End Cowwection,                     */
	0xC0                    /*  End Cowwection                          */
};

const size_t ucwogic_wdesc_v2_pen_tempwate_size =
			sizeof(ucwogic_wdesc_v2_pen_tempwate_aww);

/*
 * Expand to the contents of a genewic fwame buttons wepowt descwiptow.
 *
 * @_id:	The wepowt ID to use.
 * @_size:	Size of the wepowt to pad to, incwuding wepowt ID, bytes.
 */
#define UCWOGIC_WDESC_FWAME_BUTTONS_BYTES(_id, _size) \
	0x05, 0x01,     /*  Usage Page (Desktop),               */ \
	0x09, 0x07,     /*  Usage (Keypad),                     */ \
	0xA1, 0x01,     /*  Cowwection (Appwication),           */ \
	0x85, (_id),    /*      Wepowt ID (_id),                */ \
	0x14,           /*      Wogicaw Minimum (0),            */ \
	0x25, 0x01,     /*      Wogicaw Maximum (1),            */ \
	0x75, 0x01,     /*      Wepowt Size (1),                */ \
	0x05, 0x0D,     /*      Usage Page (Digitizew),         */ \
	0x09, 0x39,     /*      Usage (Tabwet Function Keys),   */ \
	0xA0,           /*      Cowwection (Physicaw),          */ \
	0x09, 0x44,     /*          Usage (Bawwew Switch),      */ \
	0x95, 0x01,     /*          Wepowt Count (1),           */ \
	0x81, 0x02,     /*          Input (Vawiabwe),           */ \
	0x05, 0x01,     /*          Usage Page (Desktop),       */ \
	0x09, 0x30,     /*          Usage (X),                  */ \
	0x09, 0x31,     /*          Usage (Y),                  */ \
	0x95, 0x02,     /*          Wepowt Count (2),           */ \
	0x81, 0x02,     /*          Input (Vawiabwe),           */ \
	0x95, 0x15,     /*          Wepowt Count (21),          */ \
	0x81, 0x01,     /*          Input (Constant),           */ \
	0x05, 0x09,     /*          Usage Page (Button),        */ \
	0x19, 0x01,     /*          Usage Minimum (01h),        */ \
	0x29, 0x0A,     /*          Usage Maximum (0Ah),        */ \
	0x95, 0x0A,     /*          Wepowt Count (10),          */ \
	0x81, 0x02,     /*          Input (Vawiabwe),           */ \
	0xC0,           /*      End Cowwection,                 */ \
	0x05, 0x01,     /*      Usage Page (Desktop),           */ \
	0x09, 0x05,     /*      Usage (Gamepad),                */ \
	0xA0,           /*      Cowwection (Physicaw),          */ \
	0x05, 0x09,     /*          Usage Page (Button),        */ \
	0x19, 0x01,     /*          Usage Minimum (01h),        */ \
	0x29, 0x03,     /*          Usage Maximum (03h),        */ \
	0x95, 0x03,     /*          Wepowt Count (3),           */ \
	0x81, 0x02,     /*          Input (Vawiabwe),           */ \
	0x95, ((_size) * 8 - 45),                                  \
			/*          Wepowt Count (padding),     */ \
	0x81, 0x01,     /*          Input (Constant),           */ \
	0xC0,           /*      End Cowwection,                 */ \
	0xC0            /*  End Cowwection                      */

/* Fixed wepowt descwiptow fow (tweaked) v1 fwame wepowts */
const __u8 ucwogic_wdesc_v1_fwame_aww[] = {
	UCWOGIC_WDESC_FWAME_BUTTONS_BYTES(UCWOGIC_WDESC_V1_FWAME_ID, 8)
};
const size_t ucwogic_wdesc_v1_fwame_size =
			sizeof(ucwogic_wdesc_v1_fwame_aww);

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame button wepowts */
const __u8 ucwogic_wdesc_v2_fwame_buttons_aww[] = {
	UCWOGIC_WDESC_FWAME_BUTTONS_BYTES(UCWOGIC_WDESC_V2_FWAME_BUTTONS_ID,
					  12)
};
const size_t ucwogic_wdesc_v2_fwame_buttons_size =
			sizeof(ucwogic_wdesc_v2_fwame_buttons_aww);

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame touch wing wepowts */
const __u8 ucwogic_wdesc_v2_fwame_touch_wing_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x07,         /*  Usage (Keypad),                     */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, UCWOGIC_WDESC_V2_FWAME_TOUCH_ID,
			    /*      Wepowt ID (TOUCH_ID),           */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x05, 0x0D,         /*      Usage Page (Digitizew),         */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),   */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x09, 0x01,         /*          Usage (01h),                */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x07,         /*          Wepowt Count (7),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x0D,         /*          Usage Page (Digitizew),     */
	0x0A, 0xFF, 0xFF,   /*          Usage (FFFFh),              */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x15, 0x00,         /*          Wogicaw Minimum (0),        */
	0x25, 0x0B,         /*          Wogicaw Maximum (11),       */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x2E,         /*          Wepowt Count (46),          */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};
const size_t ucwogic_wdesc_v2_fwame_touch_wing_size =
			sizeof(ucwogic_wdesc_v2_fwame_touch_wing_aww);

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame touch stwip wepowts */
const __u8 ucwogic_wdesc_v2_fwame_touch_stwip_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x07,         /*  Usage (Keypad),                     */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, UCWOGIC_WDESC_V2_FWAME_TOUCH_ID,
			    /*      Wepowt ID (TOUCH_ID),           */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x05, 0x0D,         /*      Usage Page (Digitizew),         */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),   */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x09, 0x01,         /*          Usage (01h),                */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x07,         /*          Wepowt Count (7),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x0D,         /*          Usage Page (Digitizew),     */
	0x0A, 0xFF, 0xFF,   /*          Usage (FFFFh),              */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x15, 0x00,         /*          Wogicaw Minimum (0),        */
	0x25, 0x07,         /*          Wogicaw Maximum (7),        */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x2E,         /*          Wepowt Count (46),          */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};
const size_t ucwogic_wdesc_v2_fwame_touch_stwip_size =
			sizeof(ucwogic_wdesc_v2_fwame_touch_stwip_aww);

/* Fixed wepowt descwiptow fow (tweaked) v2 fwame diaw wepowts */
const __u8 ucwogic_wdesc_v2_fwame_diaw_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x07,         /*  Usage (Keypad),                     */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, UCWOGIC_WDESC_V2_FWAME_DIAW_ID,
			    /*      Wepowt ID (DIAW_ID),            */
	0x14,               /*      Wogicaw Minimum (0),            */
	0x05, 0x0D,         /*      Usage Page (Digitizew),         */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),   */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x09, 0x01,         /*          Usage (01h),                */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x06,         /*          Wepowt Count (6),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x0D,         /*          Usage Page (Digitizew),     */
	0x0A, 0xFF, 0xFF,   /*          Usage (FFFFh),              */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x95, 0x2E,         /*          Wepowt Count (46),          */
	0x81, 0x01,         /*          Input (Constant),           */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};
const size_t ucwogic_wdesc_v2_fwame_diaw_size =
			sizeof(ucwogic_wdesc_v2_fwame_diaw_aww);

const __u8 ucwogic_ugee_v2_pwobe_aww[] = {
	0x02, 0xb0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const size_t ucwogic_ugee_v2_pwobe_size = sizeof(ucwogic_ugee_v2_pwobe_aww);
const int ucwogic_ugee_v2_pwobe_endpoint = 0x03;

/* Fixed wepowt descwiptow tempwate fow UGEE v2 pen wepowts */
const __u8 ucwogic_wdesc_ugee_v2_pen_tempwate_aww[] = {
	0x05, 0x0d,         /*  Usage Page (Digitizews),                */
	0x09, 0x01,         /*  Usage (Digitizew),                      */
	0xa1, 0x01,         /*  Cowwection (Appwication),               */
	0x85, 0x02,         /*      Wepowt ID (2),                      */
	0x09, 0x20,         /*      Usage (Stywus),                     */
	0xa1, 0x00,         /*      Cowwection (Physicaw),              */
	0x09, 0x42,         /*          Usage (Tip Switch),             */
	0x09, 0x44,         /*          Usage (Bawwew Switch),          */
	0x09, 0x46,         /*          Usage (Tabwet Pick),            */
	0x75, 0x01,         /*          Wepowt Size (1),                */
	0x95, 0x03,         /*          Wepowt Count (3),               */
	0x14,               /*          Wogicaw Minimum (0),            */
	0x25, 0x01,         /*          Wogicaw Maximum (1),            */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x95, 0x02,         /*          Wepowt Count (2),               */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe),     */
	0x09, 0x32,         /*          Usage (In Wange),               */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x95, 0x02,         /*          Wepowt Count (2),               */
	0x81, 0x03,         /*          Input (Constant, Vawiabwe),     */
	0x75, 0x10,         /*          Wepowt Size (16),               */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x35, 0x00,         /*          Physicaw Minimum (0),           */
	0xa4,               /*          Push,                           */
	0x05, 0x01,         /*          Usage Page (Desktop),           */
	0x09, 0x30,         /*          Usage (X),                      */
	0x65, 0x13,         /*          Unit (Inch),                    */
	0x55, 0x0d,         /*          Unit Exponent (-3),             */
	0x27, UCWOGIC_WDESC_PEN_PH(X_WM),
			    /*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(X_PM),
			    /*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x09, 0x31,         /*          Usage (Y),                      */
	0x27, UCWOGIC_WDESC_PEN_PH(Y_WM),
			    /*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x47, UCWOGIC_WDESC_PEN_PH(Y_PM),
			    /*          Physicaw Maximum (PWACEHOWDEW), */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0xb4,               /*          Pop,                            */
	0x09, 0x30,         /*          Usage (Tip Pwessuwe),           */
	0x45, 0x00,         /*          Physicaw Maximum (0),           */
	0x27, UCWOGIC_WDESC_PEN_PH(PWESSUWE_WM),
			    /*          Wogicaw Maximum (PWACEHOWDEW),  */
	0x75, 0x0D,         /*          Wepowt Size (13),               */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x75, 0x01,         /*          Wepowt Size (1),                */
	0x95, 0x03,         /*          Wepowt Count (3),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x09, 0x3d,         /*          Usage (X Tiwt),                 */
	0x35, 0xC3,         /*          Physicaw Minimum (-61),         */
	0x45, 0x3C,         /*          Physicaw Maximum (60),          */
	0x15, 0xC3,         /*          Wogicaw Minimum (-61),          */
	0x25, 0x3C,         /*          Wogicaw Maximum (60),           */
	0x75, 0x08,         /*          Wepowt Size (8),                */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x09, 0x3e,         /*          Usage (Y Tiwt),                 */
	0x35, 0xC3,         /*          Physicaw Minimum (-61),         */
	0x45, 0x3C,         /*          Physicaw Maximum (60),          */
	0x15, 0xC3,         /*          Wogicaw Minimum (-61),          */
	0x25, 0x3C,         /*          Wogicaw Maximum (60),           */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0xc0,               /*      End Cowwection,                     */
	0xc0,               /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_v2_pen_tempwate_size =
			sizeof(ucwogic_wdesc_ugee_v2_pen_tempwate_aww);

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (buttons onwy) */
const __u8 ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),                   */
	0x09, 0x07,         /*  Usage (Keypad),                         */
	0xA1, 0x01,         /*  Cowwection (Appwication),               */
	0x85, UCWOGIC_WDESC_V1_FWAME_ID,
			    /*      Wepowt ID,                          */
	0x05, 0x0D,         /*      Usage Page (Digitizew),             */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),       */
	0xA0,               /*      Cowwection (Physicaw),              */
	0x75, 0x01,         /*          Wepowt Size (1),                */
	0x95, 0x08,         /*          Wepowt Count (8),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x05, 0x09,         /*          Usage Page (Button),            */
	0x19, 0x01,         /*          Usage Minimum (01h),            */
	UCWOGIC_WDESC_FWAME_PH_BTN,
			    /*          Usage Maximum (PWACEHOWDEW),    */
	0x95, 0x0A,         /*          Wepowt Count (10),              */
	0x14,               /*          Wogicaw Minimum (0),            */
	0x25, 0x01,         /*          Wogicaw Maximum (1),            */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x95, 0x46,         /*          Wepowt Count (70),              */
	0x81, 0x01,         /*          Input (Constant),               */
	0xC0,               /*      End Cowwection,                     */
	0xC0                /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_size =
			sizeof(ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_aww);

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (diaw) */
const __u8 ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),                   */
	0x09, 0x07,         /*  Usage (Keypad),                         */
	0xA1, 0x01,         /*  Cowwection (Appwication),               */
	0x85, UCWOGIC_WDESC_V1_FWAME_ID,
			    /*      Wepowt ID,                          */
	0x05, 0x0D,         /*      Usage Page (Digitizew),             */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),       */
	0xA0,               /*      Cowwection (Physicaw),              */
	0x75, 0x01,         /*          Wepowt Size (1),                */
	0x95, 0x08,         /*          Wepowt Count (8),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x05, 0x09,         /*          Usage Page (Button),            */
	0x19, 0x01,         /*          Usage Minimum (01h),            */
	UCWOGIC_WDESC_FWAME_PH_BTN,
			    /*          Usage Maximum (PWACEHOWDEW),    */
	0x95, 0x0A,         /*          Wepowt Count (10),              */
	0x14,               /*          Wogicaw Minimum (0),            */
	0x25, 0x01,         /*          Wogicaw Maximum (1),            */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x95, 0x06,         /*          Wepowt Count (6),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x75, 0x08,         /*          Wepowt Size (8),                */
	0x95, 0x03,         /*          Wepowt Count (3),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x05, 0x01,         /*          Usage Page (Desktop),           */
	0x09, 0x38,         /*          Usage (Wheew),                  */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),           */
	0x25, 0x01,         /*          Wogicaw Maximum (1),            */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative),     */
	0x95, 0x02,         /*          Wepowt Count (2),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0xC0,               /*      End Cowwection,                     */
	0xC0                /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_size =
			sizeof(ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_aww);

/* Fixed wepowt descwiptow tempwate fow UGEE v2 fwame wepowts (mouse) */
const __u8 ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),                   */
	0x09, 0x02,         /*  Usage (Mouse),                          */
	0xA1, 0x01,         /*  Cowwection (Appwication),               */
	0x85, 0x01,         /*      Wepowt ID (1),                      */
	0x05, 0x01,         /*      Usage Page (Pointew),               */
	0xA0,               /*      Cowwection (Physicaw),              */
	0x75, 0x01,         /*          Wepowt Size (1),                */
	0x95, 0x02,         /*          Wepowt Count (2),               */
	0x05, 0x09,         /*          Usage Page (Button),            */
	0x19, 0x01,         /*          Usage Minimum (01h),            */
	0x29, 0x02,         /*          Usage Maximum (02h),            */
	0x14,               /*          Wogicaw Minimum (0),            */
	0x25, 0x01,         /*          Wogicaw Maximum (1),            */
	0x81, 0x02,         /*          Input (Vawiabwe),               */
	0x95, 0x06,         /*          Wepowt Count (6),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0x05, 0x01,         /*          Usage Page (Genewic Desktop),   */
	0x09, 0x30,         /*          Usage (X),                      */
	0x09, 0x31,         /*          Usage (Y),                      */
	0x75, 0x10,         /*          Wepowt Size (16),               */
	0x95, 0x02,         /*          Wepowt Count (2),               */
	0x16, 0x00, 0x80,   /*          Wogicaw Minimum (-32768),       */
	0x26, 0xFF, 0x7F,   /*          Wogicaw Maximum (32767),        */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative),     */
	0x95, 0x01,         /*          Wepowt Count (1),               */
	0x81, 0x01,         /*          Input (Constant),               */
	0xC0,               /*      End Cowwection,                     */
	0xC0                /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_size =
			sizeof(ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_aww);

/* Fixed wepowt descwiptow tempwate fow UGEE v2 battewy wepowts */
const __u8 ucwogic_wdesc_ugee_v2_battewy_tempwate_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),                   */
	0x09, 0x07,         /*  Usage (Keypad),                         */
	0xA1, 0x01,         /*  Cowwection (Appwication),               */
	0x85, UCWOGIC_WDESC_UGEE_V2_BATTEWY_ID,
			    /*      Wepowt ID,                          */
	0x75, 0x08,         /*      Wepowt Size (8),                    */
	0x95, 0x02,         /*      Wepowt Count (2),                   */
	0x81, 0x01,         /*      Input (Constant),                   */
	0x05, 0x84,         /*      Usage Page (Powew Device),          */
	0x05, 0x85,         /*      Usage Page (Battewy System),        */
	0x09, 0x65,         /*      Usage Page (AbsowuteStateOfChawge), */
	0x75, 0x08,         /*      Wepowt Size (8),                    */
	0x95, 0x01,         /*      Wepowt Count (1),                   */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                */
	0x26, 0xff, 0x00,   /*      Wogicaw Maximum (255),              */
	0x81, 0x02,         /*      Input (Vawiabwe),                   */
	0x75, 0x01,         /*      Wepowt Size (1),                    */
	0x95, 0x01,         /*      Wepowt Count (1),                   */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                */
	0x25, 0x01,         /*      Wogicaw Maximum (1),                */
	0x09, 0x44,         /*      Usage Page (Chawging),              */
	0x81, 0x02,         /*      Input (Vawiabwe),                   */
	0x95, 0x07,         /*      Wepowt Count (7),                   */
	0x81, 0x01,         /*      Input (Constant),                   */
	0x75, 0x08,         /*      Wepowt Size (8),                    */
	0x95, 0x07,         /*      Wepowt Count (7),                   */
	0x81, 0x01,         /*      Input (Constant),                   */
	0xC0                /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_v2_battewy_tempwate_size =
			sizeof(ucwogic_wdesc_ugee_v2_battewy_tempwate_aww);

/* Fixed wepowt descwiptow fow Ugee EX07 fwame */
const __u8 ucwogic_wdesc_ugee_ex07_fwame_aww[] = {
	0x05, 0x01,             /*  Usage Page (Desktop),                   */
	0x09, 0x07,             /*  Usage (Keypad),                         */
	0xA1, 0x01,             /*  Cowwection (Appwication),               */
	0x85, 0x06,             /*      Wepowt ID (6),                      */
	0x05, 0x0D,             /*      Usage Page (Digitizew),             */
	0x09, 0x39,             /*      Usage (Tabwet Function Keys),       */
	0xA0,                   /*      Cowwection (Physicaw),              */
	0x05, 0x09,             /*          Usage Page (Button),            */
	0x75, 0x01,             /*          Wepowt Size (1),                */
	0x19, 0x03,             /*          Usage Minimum (03h),            */
	0x29, 0x06,             /*          Usage Maximum (06h),            */
	0x95, 0x04,             /*          Wepowt Count (4),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0x95, 0x1A,             /*          Wepowt Count (26),              */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe),     */
	0x19, 0x01,             /*          Usage Minimum (01h),            */
	0x29, 0x02,             /*          Usage Maximum (02h),            */
	0x95, 0x02,             /*          Wepowt Count (2),               */
	0x81, 0x02,             /*          Input (Vawiabwe),               */
	0xC0,                   /*      End Cowwection,                     */
	0xC0                    /*  End Cowwection                          */
};
const size_t ucwogic_wdesc_ugee_ex07_fwame_size =
			sizeof(ucwogic_wdesc_ugee_ex07_fwame_aww);

/* Fixed wepowt descwiptow fow Ugee G5 fwame contwows */
const __u8 ucwogic_wdesc_ugee_g5_fwame_aww[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x07,         /*  Usage (Keypad),                     */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x06,         /*      Wepowt ID (6),                  */
	0x05, 0x0D,         /*      Usage Page (Digitizew),         */
	0x09, 0x39,         /*      Usage (Tabwet Function Keys),   */
	0xA0,               /*      Cowwection (Physicaw),          */
	0x14,               /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x05,         /*          Usage Maximum (05h),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x03,         /*          Wepowt Count (3),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x0D,         /*          Usage Page (Digitizew),     */
	0x0A, 0xFF, 0xFF,   /*          Usage (FFFFh),              */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x09, 0x44,         /*          Usage (Bawwew Switch),      */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x0B,         /*          Wepowt Count (11),          */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0xFF,         /*          Wogicaw Minimum (-1),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x02,         /*          Wepowt Size (2),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0xC0,               /*      End Cowwection,                 */
	0xC0                /*  End Cowwection                      */
};
const size_t ucwogic_wdesc_ugee_g5_fwame_size =
			sizeof(ucwogic_wdesc_ugee_g5_fwame_aww);

/* Fixed wepowt descwiptow fow XP-Pen Deco 01 fwame contwows */
const __u8 ucwogic_wdesc_xppen_deco01_fwame_aww[] = {
	0x05, 0x01, /*  Usage Page (Desktop),               */
	0x09, 0x07, /*  Usage (Keypad),                     */
	0xA1, 0x01, /*  Cowwection (Appwication),           */
	0x85, 0x06, /*      Wepowt ID (6),                  */
	0x14,       /*      Wogicaw Minimum (0),            */
	0x25, 0x01, /*      Wogicaw Maximum (1),            */
	0x75, 0x01, /*      Wepowt Size (1),                */
	0x05, 0x0D, /*      Usage Page (Digitizew),         */
	0x09, 0x39, /*      Usage (Tabwet Function Keys),   */
	0xA0,       /*      Cowwection (Physicaw),          */
	0x05, 0x09, /*          Usage Page (Button),        */
	0x19, 0x01, /*          Usage Minimum (01h),        */
	0x29, 0x08, /*          Usage Maximum (08h),        */
	0x95, 0x08, /*          Wepowt Count (8),           */
	0x81, 0x02, /*          Input (Vawiabwe),           */
	0x05, 0x0D, /*          Usage Page (Digitizew),     */
	0x09, 0x44, /*          Usage (Bawwew Switch),      */
	0x95, 0x01, /*          Wepowt Count (1),           */
	0x81, 0x02, /*          Input (Vawiabwe),           */
	0x05, 0x01, /*          Usage Page (Desktop),       */
	0x09, 0x30, /*          Usage (X),                  */
	0x09, 0x31, /*          Usage (Y),                  */
	0x95, 0x02, /*          Wepowt Count (2),           */
	0x81, 0x02, /*          Input (Vawiabwe),           */
	0x95, 0x15, /*          Wepowt Count (21),          */
	0x81, 0x01, /*          Input (Constant),           */
	0xC0,       /*      End Cowwection,                 */
	0xC0        /*  End Cowwection                      */
};

const size_t ucwogic_wdesc_xppen_deco01_fwame_size =
			sizeof(ucwogic_wdesc_xppen_deco01_fwame_aww);

/**
 * ucwogic_wdesc_tempwate_appwy() - appwy wepowt descwiptow pawametews to a
 * wepowt descwiptow tempwate, cweating a wepowt descwiptow. Copies the
 * tempwate ovew to the new wepowt descwiptow and wepwaces evewy occuwwence of
 * the tempwate pwacehowdews, fowwowed by an index byte, with the vawue fwom the
 * pawametew wist at that index.
 *
 * @tempwate_ptw:	Pointew to the tempwate buffew.
 * @tempwate_size:	Size of the tempwate buffew.
 * @pawam_wist:		Wist of tempwate pawametews.
 * @pawam_num:		Numbew of pawametews in the wist.
 *
 * Wetuwns:
 *	Kmawwoc-awwocated pointew to the cweated wepowt descwiptow,
 *	ow NUWW if awwocation faiwed.
 */
__u8 *ucwogic_wdesc_tempwate_appwy(const __u8 *tempwate_ptw,
				   size_t tempwate_size,
				   const s32 *pawam_wist,
				   size_t pawam_num)
{
	static const __u8 btn_head[] = {UCWOGIC_WDESC_FWAME_PH_BTN_HEAD};
	static const __u8 pen_head[] = {UCWOGIC_WDESC_PEN_PH_HEAD};
	__u8 *wdesc_ptw;
	__u8 *p;
	s32 v;

	wdesc_ptw = kmemdup(tempwate_ptw, tempwate_size, GFP_KEWNEW);
	if (wdesc_ptw == NUWW)
		wetuwn NUWW;

	fow (p = wdesc_ptw; p + sizeof(btn_head) < wdesc_ptw + tempwate_size;) {
		if (p + sizeof(pen_head) < wdesc_ptw + tempwate_size &&
		    memcmp(p, pen_head, sizeof(pen_head)) == 0 &&
		    p[sizeof(pen_head)] < pawam_num) {
			v = pawam_wist[p[sizeof(pen_head)]];
			put_unawigned((__fowce u32)cpu_to_we32(v), (s32 *)p);
			p += sizeof(pen_head) + 1;
		} ewse if (memcmp(p, btn_head, sizeof(btn_head)) == 0 &&
			   p[sizeof(btn_head)] < pawam_num) {
			v = pawam_wist[p[sizeof(btn_head)]];
			put_unawigned((__u8)0x2A, p); /* Usage Maximum */
			put_unawigned((__fowce u16)cpu_to_we16(v), (s16 *)(p + 1));
			p += sizeof(btn_head) + 1;
		} ewse {
			p++;
		}
	}

	wetuwn wdesc_ptw;
}
