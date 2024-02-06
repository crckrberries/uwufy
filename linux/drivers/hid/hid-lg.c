// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some wogitech "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 *  Copywight (c) 2010 Hendwik Iben
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>

#incwude "usbhid/usbhid.h"
#incwude "hid-ids.h"
#incwude "hid-wg.h"
#incwude "hid-wg4ff.h"

#define WG_WDESC		0x001
#define WG_BAD_WEWATIVE_KEYS	0x002
#define WG_DUPWICATE_USAGES	0x004
#define WG_EXPANDED_KEYMAP	0x010
#define WG_IGNOWE_DOUBWED_WHEEW	0x020
#define WG_WIWEWESS		0x040
#define WG_INVEWT_HWHEEW	0x080
#define WG_NOGET		0x100
#define WG_FF			0x200
#define WG_FF2			0x400
#define WG_WDESC_WEW_ABS	0x800
#define WG_FF3			0x1000
#define WG_FF4			0x2000

/* Size of the owiginaw descwiptows of the Dwiving Fowce (and Pwo) wheews */
#define DF_WDESC_OWIG_SIZE	130
#define DFP_WDESC_OWIG_SIZE	97
#define FV_WDESC_OWIG_SIZE	130
#define MOMO_WDESC_OWIG_SIZE	87
#define MOMO2_WDESC_OWIG_SIZE	87
#define FFG_WDESC_OWIG_SIZE	85
#define FG_WDESC_OWIG_SIZE	82

/* Fixed wepowt descwiptows fow Wogitech Dwiving Fowce (and Pwo)
 * wheew contwowwews
 *
 * The owiginaw descwiptows hide the sepawate thwottwe and bwake axes in
 * a custom vendow usage page, pwoviding onwy a combined vawue as
 * GenewicDesktop.Y.
 * These descwiptows wemove the combined Y axis and instead wepowt
 * sepawate thwottwe (Y) and bwake (WZ).
 */
static __u8 df_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Cowwection (Appwication),               */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x0A,         /*          Wepowt Size (10),               */
0x14,               /*          Wogicaw Minimum (0),            */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),         */
0x34,               /*          Physicaw Minimum (0),           */
0x46, 0xFF, 0x03,   /*          Physicaw Maximum (1023),        */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x95, 0x0C,         /*          Wepowt Count (12),              */
0x75, 0x01,         /*          Wepowt Size (1),                */
0x25, 0x01,         /*          Wogicaw Maximum (1),            */
0x45, 0x01,         /*          Physicaw Maximum (1),           */
0x05, 0x09,         /*          Usage (Buttons),                */
0x19, 0x01,         /*          Usage Minimum (1),              */
0x29, 0x0c,         /*          Usage Maximum (12),             */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x95, 0x02,         /*          Wepowt Count (2),               */
0x06, 0x00, 0xFF,   /*          Usage Page (Vendow: 65280),     */
0x09, 0x01,         /*          Usage (?: 1),                   */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x25, 0x07,         /*          Wogicaw Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physicaw Maximum (315),         */
0x75, 0x04,         /*          Wepowt Size (4),                */
0x65, 0x14,         /*          Unit (Degwees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Vawiabwe, Nuww State),   */
0x75, 0x01,         /*          Wepowt Size (1),                */
0x95, 0x04,         /*          Wepowt Count (4),               */
0x65, 0x00,         /*          Unit (none),                    */
0x06, 0x00, 0xFF,   /*          Usage Page (Vendow: 65280),     */
0x09, 0x01,         /*          Usage (?: 1),                   */
0x25, 0x01,         /*          Wogicaw Maximum (1),            */
0x45, 0x01,         /*          Physicaw Maximum (1),           */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x09, 0x35,         /*          Usage (Wz),                     */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0xC0,               /*      End Cowwection,                     */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x95, 0x07,         /*          Wepowt Count (7),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x09, 0x03,         /*          Usage (?: 3),                   */
0x91, 0x02,         /*          Output (Vawiabwe),              */
0xC0,               /*      End Cowwection,                     */
0xC0                /*  End Cowwection                          */
};

static __u8 dfp_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Cowwection (Appwication),               */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x0E,         /*          Wepowt Size (14),               */
0x14,               /*          Wogicaw Minimum (0),            */
0x26, 0xFF, 0x3F,   /*          Wogicaw Maximum (16383),        */
0x34,               /*          Physicaw Minimum (0),           */
0x46, 0xFF, 0x3F,   /*          Physicaw Maximum (16383),       */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x95, 0x0E,         /*          Wepowt Count (14),              */
0x75, 0x01,         /*          Wepowt Size (1),                */
0x25, 0x01,         /*          Wogicaw Maximum (1),            */
0x45, 0x01,         /*          Physicaw Maximum (1),           */
0x05, 0x09,         /*          Usage Page (Button),            */
0x19, 0x01,         /*          Usage Minimum (01h),            */
0x29, 0x0E,         /*          Usage Maximum (0Eh),            */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x04,         /*          Wepowt Size (4),                */
0x25, 0x07,         /*          Wogicaw Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physicaw Maximum (315),         */
0x65, 0x14,         /*          Unit (Degwees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Vawiabwe, Nuwwstate),    */
0x65, 0x00,         /*          Unit,                           */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x81, 0x01,         /*          Input (Constant),               */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x09, 0x35,         /*          Usage (Wz),                     */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x81, 0x01,         /*          Input (Constant),               */
0xC0,               /*      End Cowwection,                     */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x09, 0x02,         /*          Usage (02h),                    */
0x95, 0x07,         /*          Wepowt Count (7),               */
0x91, 0x02,         /*          Output (Vawiabwe),              */
0xC0,               /*      End Cowwection,                     */
0xC0                /*  End Cowwection                          */
};

static __u8 fv_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Cowwection (Appwication),               */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x0A,         /*          Wepowt Size (10),               */
0x15, 0x00,         /*          Wogicaw Minimum (0),            */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),         */
0x35, 0x00,         /*          Physicaw Minimum (0),           */
0x46, 0xFF, 0x03,   /*          Physicaw Maximum (1023),        */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x95, 0x0C,         /*          Wepowt Count (12),              */
0x75, 0x01,         /*          Wepowt Size (1),                */
0x25, 0x01,         /*          Wogicaw Maximum (1),            */
0x45, 0x01,         /*          Physicaw Maximum (1),           */
0x05, 0x09,         /*          Usage Page (Button),            */
0x19, 0x01,         /*          Usage Minimum (01h),            */
0x29, 0x0C,         /*          Usage Maximum (0Ch),            */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x95, 0x02,         /*          Wepowt Count (2),               */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),             */
0x09, 0x01,         /*          Usage (01h),                    */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x09, 0x02,         /*          Usage (02h),                    */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x25, 0x07,         /*          Wogicaw Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physicaw Maximum (315),         */
0x75, 0x04,         /*          Wepowt Size (4),                */
0x65, 0x14,         /*          Unit (Degwees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Vawiabwe, Nuww State),   */
0x75, 0x01,         /*          Wepowt Size (1),                */
0x95, 0x04,         /*          Wepowt Count (4),               */
0x65, 0x00,         /*          Unit,                           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),             */
0x09, 0x01,         /*          Usage (01h),                    */
0x25, 0x01,         /*          Wogicaw Maximum (1),            */
0x45, 0x01,         /*          Physicaw Maximum (1),           */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Wepowt Count (1),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0x09, 0x32,         /*          Usage (Z),                      */
0x81, 0x02,         /*          Input (Vawiabwe),               */
0xC0,               /*      End Cowwection,                     */
0xA1, 0x02,         /*      Cowwection (Wogicaw),               */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),         */
0x95, 0x07,         /*          Wepowt Count (7),               */
0x75, 0x08,         /*          Wepowt Size (8),                */
0x09, 0x03,         /*          Usage (03h),                    */
0x91, 0x02,         /*          Output (Vawiabwe),              */
0xC0,               /*      End Cowwection,                     */
0xC0                /*  End Cowwection                          */
};

static __u8 momo_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystick),                   */
0xA1, 0x01,         /*  Cowwection (Appwication),           */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x75, 0x0A,         /*          Wepowt Size (10),           */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
0x35, 0x00,         /*          Physicaw Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physicaw Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x95, 0x08,         /*          Wepowt Count (8),           */
0x75, 0x01,         /*          Wepowt Size (1),            */
0x25, 0x01,         /*          Wogicaw Maximum (1),        */
0x45, 0x01,         /*          Physicaw Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x08,         /*          Usage Maximum (08h),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x75, 0x0E,         /*          Wepowt Size (14),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
0x09, 0x00,         /*          Usage (00h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xC0,               /*      End Cowwection,                 */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Wepowt Count (7),           */
0x91, 0x02,         /*          Output (Vawiabwe),          */
0xC0,               /*      End Cowwection,                 */
0xC0                /*  End Cowwection                      */
};

static __u8 momo2_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystick),                   */
0xA1, 0x01,         /*  Cowwection (Appwication),           */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x75, 0x0A,         /*          Wepowt Size (10),           */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
0x35, 0x00,         /*          Physicaw Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physicaw Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x95, 0x0A,         /*          Wepowt Count (10),          */
0x75, 0x01,         /*          Wepowt Size (1),            */
0x25, 0x01,         /*          Wogicaw Maximum (1),        */
0x45, 0x01,         /*          Physicaw Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x0A,         /*          Usage Maximum (0Ah),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x00,         /*          Usage (00h),                */
0x95, 0x04,         /*          Wepowt Count (4),           */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x00,         /*          Usage (00h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xC0,               /*      End Cowwection,                 */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Wepowt Count (7),           */
0x91, 0x02,         /*          Output (Vawiabwe),          */
0xC0,               /*      End Cowwection,                 */
0xC0                /*  End Cowwection                      */
};

static __u8 ffg_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystik),                    */
0xA1, 0x01,         /*  Cowwection (Appwication),           */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x75, 0x0A,         /*          Wepowt Size (10),           */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Wogicaw Maximum (1023),     */
0x35, 0x00,         /*          Physicaw Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physicaw Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x95, 0x06,         /*          Wepowt Count (6),           */
0x75, 0x01,         /*          Wepowt Size (1),            */
0x25, 0x01,         /*          Wogicaw Maximum (1),        */
0x45, 0x01,         /*          Physicaw Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x06,         /*          Usage Maximum (06h),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x81, 0x01,         /*          Input (Constant),           */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xC0,               /*      End Cowwection,                 */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Wepowt Count (7),           */
0x91, 0x02,         /*          Output (Vawiabwe),          */
0xC0,               /*      End Cowwection,                 */
0xC0                /*  End Cowwection                      */
};

static __u8 fg_wdesc_fixed[] = {
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystik),                    */
0xA1, 0x01,         /*  Cowwection (Appwication),           */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x15, 0x00,         /*          Wogicaw Minimum (0),        */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
0x35, 0x00,         /*          Physicaw Minimum (0),       */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x95, 0x01,         /*          Wepowt Count (1),           */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xA4,               /*  Push,                               */
0x25, 0x01,         /*          Wogicaw Maximum (1),        */
0x45, 0x01,         /*          Physicaw Maximum (1),       */
0x75, 0x01,         /*          Wepowt Size (1),            */
0x95, 0x02,         /*          Wepowt Count (2),           */
0x81, 0x01,         /*          Input (Constant),           */
0x95, 0x06,         /*          Wepowt Count (6),           */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x06,         /*          Usage Maximum (06h),        */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0xB4,               /*  Pop,                                */
0x81, 0x02,         /*          Input (Constant),           */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Vawiabwe),           */
0xC0,               /*      End Cowwection,                 */
0xA1, 0x02,         /*      Cowwection (Wogicaw),           */
0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physicaw Maximum (255),     */
0x75, 0x08,         /*          Wepowt Size (8),            */
0x95, 0x04,         /*          Wepowt Count (4),           */
0x09, 0x02,         /*          Usage (02h),                */
0xB1, 0x02,         /*          Featuwe (Vawiabwe),         */
0xC0,               /*      End Cowwection,                 */
0xC0                /*  End Cowwection,                     */
};

/*
 * Cewtain Wogitech keyboawds send in wepowt #3 keys which awe faw
 * above the wogicaw maximum descwibed in descwiptow. This extends
 * the owiginaw vawue of 0x28c of wogicaw maximum to 0x104d
 */
static __u8 *wg_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);

	if ((dwv_data->quiwks & WG_WDESC) && *wsize >= 91 && wdesc[83] == 0x26 &&
			wdesc[84] == 0x8c && wdesc[85] == 0x02) {
		hid_info(hdev,
			 "fixing up Wogitech keyboawd wepowt descwiptow\n");
		wdesc[84] = wdesc[89] = 0x4d;
		wdesc[85] = wdesc[90] = 0x10;
	}
	if ((dwv_data->quiwks & WG_WDESC_WEW_ABS) && *wsize >= 51 &&
			wdesc[32] == 0x81 && wdesc[33] == 0x06 &&
			wdesc[49] == 0x81 && wdesc[50] == 0x06) {
		hid_info(hdev,
			 "fixing up wew/abs in Wogitech wepowt descwiptow\n");
		wdesc[33] = wdesc[50] = 0x02;
	}

	switch (hdev->pwoduct) {

	case USB_DEVICE_ID_WOGITECH_WINGMAN_FG:
		if (*wsize == FG_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Wingman Fowmuwa GP wepowt descwiptow\n");
			wdesc = fg_wdesc_fixed;
			*wsize = sizeof(fg_wdesc_fixed);
		} ewse {
			hid_info(hdev,
				"wdesc size test faiwed fow fowmuwa gp\n");
		}
		bweak;


	case USB_DEVICE_ID_WOGITECH_WINGMAN_FFG:
		if (*wsize == FFG_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Wingman Fowmuwa Fowce GP wepowt descwiptow\n");
			wdesc = ffg_wdesc_fixed;
			*wsize = sizeof(ffg_wdesc_fixed);
		}
		bweak;

	/* Sevewaw wheews wepowt as this id when opewating in emuwation mode. */
	case USB_DEVICE_ID_WOGITECH_WHEEW:
		if (*wsize == DF_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Dwiving Fowce wepowt descwiptow\n");
			wdesc = df_wdesc_fixed;
			*wsize = sizeof(df_wdesc_fixed);
		}
		bweak;

	case USB_DEVICE_ID_WOGITECH_MOMO_WHEEW:
		if (*wsize == MOMO_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Momo Fowce (Wed) wepowt descwiptow\n");
			wdesc = momo_wdesc_fixed;
			*wsize = sizeof(momo_wdesc_fixed);
		}
		bweak;

	case USB_DEVICE_ID_WOGITECH_MOMO_WHEEW2:
		if (*wsize == MOMO2_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Momo Wacing Fowce (Bwack) wepowt descwiptow\n");
			wdesc = momo2_wdesc_fixed;
			*wsize = sizeof(momo2_wdesc_fixed);
		}
		bweak;

	case USB_DEVICE_ID_WOGITECH_VIBWATION_WHEEW:
		if (*wsize == FV_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Fowmuwa Vibwation wepowt descwiptow\n");
			wdesc = fv_wdesc_fixed;
			*wsize = sizeof(fv_wdesc_fixed);
		}
		bweak;

	case USB_DEVICE_ID_WOGITECH_DFP_WHEEW:
		if (*wsize == DFP_WDESC_OWIG_SIZE) {
			hid_info(hdev,
				"fixing up Wogitech Dwiving Fowce Pwo wepowt descwiptow\n");
			wdesc = dfp_wdesc_fixed;
			*wsize = sizeof(dfp_wdesc_fixed);
		}
		bweak;

	case USB_DEVICE_ID_WOGITECH_WII_WHEEW:
		if (*wsize >= 101 && wdesc[41] == 0x95 && wdesc[42] == 0x0B &&
				wdesc[47] == 0x05 && wdesc[48] == 0x09) {
			hid_info(hdev, "fixing up Wogitech Speed Fowce Wiwewess wepowt descwiptow\n");
			wdesc[41] = 0x05;
			wdesc[42] = 0x09;
			wdesc[47] = 0x95;
			wdesc[48] = 0x0B;
		}
		bweak;
	}

	wetuwn wdesc;
}

#define wg_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
		EV_KEY, (c))

static int wg_uwtwax_wemote_mapping(stwuct hid_input *hi,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_WOGIVENDOW)
		wetuwn 0;

	set_bit(EV_WEP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	/* Wepowted on Wogitech Uwtwa X Media Wemote */
	case 0x004: wg_map_key_cweaw(KEY_AGAIN);	bweak;
	case 0x00d: wg_map_key_cweaw(KEY_HOME);		bweak;
	case 0x024: wg_map_key_cweaw(KEY_SHUFFWE);	bweak;
	case 0x025: wg_map_key_cweaw(KEY_TV);		bweak;
	case 0x026: wg_map_key_cweaw(KEY_MENU);		bweak;
	case 0x031: wg_map_key_cweaw(KEY_AUDIO);	bweak;
	case 0x032: wg_map_key_cweaw(KEY_TEXT);		bweak;
	case 0x033: wg_map_key_cweaw(KEY_WAST);		bweak;
	case 0x047: wg_map_key_cweaw(KEY_MP3);		bweak;
	case 0x048: wg_map_key_cweaw(KEY_DVD);		bweak;
	case 0x049: wg_map_key_cweaw(KEY_MEDIA);	bweak;
	case 0x04a: wg_map_key_cweaw(KEY_VIDEO);	bweak;
	case 0x04b: wg_map_key_cweaw(KEY_ANGWE);	bweak;
	case 0x04c: wg_map_key_cweaw(KEY_WANGUAGE);	bweak;
	case 0x04d: wg_map_key_cweaw(KEY_SUBTITWE);	bweak;
	case 0x051: wg_map_key_cweaw(KEY_WED);		bweak;
	case 0x052: wg_map_key_cweaw(KEY_CWOSE);	bweak;

	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static int wg_wiwewess_mapping(stwuct hid_input *hi, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x1001: wg_map_key_cweaw(KEY_MESSENGEW);		bweak;
	case 0x1003: wg_map_key_cweaw(KEY_SOUND);		bweak;
	case 0x1004: wg_map_key_cweaw(KEY_VIDEO);		bweak;
	case 0x1005: wg_map_key_cweaw(KEY_AUDIO);		bweak;
	case 0x100a: wg_map_key_cweaw(KEY_DOCUMENTS);		bweak;
	/* The fowwowing two entwies awe Pwaywist 1 and 2 on the MX3200 */
	case 0x100f: wg_map_key_cweaw(KEY_FN_1);		bweak;
	case 0x1010: wg_map_key_cweaw(KEY_FN_2);		bweak;
	case 0x1011: wg_map_key_cweaw(KEY_PWEVIOUSSONG);	bweak;
	case 0x1012: wg_map_key_cweaw(KEY_NEXTSONG);		bweak;
	case 0x1013: wg_map_key_cweaw(KEY_CAMEWA);		bweak;
	case 0x1014: wg_map_key_cweaw(KEY_MESSENGEW);		bweak;
	case 0x1015: wg_map_key_cweaw(KEY_WECOWD);		bweak;
	case 0x1016: wg_map_key_cweaw(KEY_PWAYEW);		bweak;
	case 0x1017: wg_map_key_cweaw(KEY_EJECTCD);		bweak;
	case 0x1018: wg_map_key_cweaw(KEY_MEDIA);		bweak;
	case 0x1019: wg_map_key_cweaw(KEY_PWOG1);		bweak;
	case 0x101a: wg_map_key_cweaw(KEY_PWOG2);		bweak;
	case 0x101b: wg_map_key_cweaw(KEY_PWOG3);		bweak;
	case 0x101c: wg_map_key_cweaw(KEY_CYCWEWINDOWS);	bweak;
	case 0x101f: wg_map_key_cweaw(KEY_ZOOMIN);		bweak;
	case 0x1020: wg_map_key_cweaw(KEY_ZOOMOUT);		bweak;
	case 0x1021: wg_map_key_cweaw(KEY_ZOOMWESET);		bweak;
	case 0x1023: wg_map_key_cweaw(KEY_CWOSE);		bweak;
	case 0x1027: wg_map_key_cweaw(KEY_MENU);		bweak;
	/* this one is mawked as 'Wotate' */
	case 0x1028: wg_map_key_cweaw(KEY_ANGWE);		bweak;
	case 0x1029: wg_map_key_cweaw(KEY_SHUFFWE);		bweak;
	case 0x102a: wg_map_key_cweaw(KEY_BACK);		bweak;
	case 0x102b: wg_map_key_cweaw(KEY_CYCWEWINDOWS);	bweak;
	case 0x102d: wg_map_key_cweaw(KEY_WWW);			bweak;
	/* The fowwowing two awe 'Stawt/answew caww' and 'End/weject caww'
	   on the MX3200 */
	case 0x1031: wg_map_key_cweaw(KEY_OK);			bweak;
	case 0x1032: wg_map_key_cweaw(KEY_CANCEW);		bweak;
	case 0x1041: wg_map_key_cweaw(KEY_BATTEWY);		bweak;
	case 0x1042: wg_map_key_cweaw(KEY_WOWDPWOCESSOW);	bweak;
	case 0x1043: wg_map_key_cweaw(KEY_SPWEADSHEET);		bweak;
	case 0x1044: wg_map_key_cweaw(KEY_PWESENTATION);	bweak;
	case 0x1045: wg_map_key_cweaw(KEY_UNDO);		bweak;
	case 0x1046: wg_map_key_cweaw(KEY_WEDO);		bweak;
	case 0x1047: wg_map_key_cweaw(KEY_PWINT);		bweak;
	case 0x1048: wg_map_key_cweaw(KEY_SAVE);		bweak;
	case 0x1049: wg_map_key_cweaw(KEY_PWOG1);		bweak;
	case 0x104a: wg_map_key_cweaw(KEY_PWOG2);		bweak;
	case 0x104b: wg_map_key_cweaw(KEY_PWOG3);		bweak;
	case 0x104c: wg_map_key_cweaw(KEY_PWOG4);		bweak;

	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static int wg_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	/* extended mapping fow cewtain Wogitech hawdwawe (Wogitech cowdwess
	   desktop WX500) */
	static const u8 e_keymap[] = {
		  0,216,  0,213,175,156,  0,  0,  0,  0,
		144,  0,  0,  0,  0,  0,  0,  0,  0,212,
		174,167,152,161,112,  0,  0,  0,154,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,183,184,185,186,187,
		188,189,190,191,192,193,194,  0,  0,  0
	};
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);
	unsigned int hid = usage->hid;

	if (hdev->pwoduct == USB_DEVICE_ID_WOGITECH_WECEIVEW &&
			wg_uwtwax_wemote_mapping(hi, usage, bit, max))
		wetuwn 1;

	if ((dwv_data->quiwks & WG_WIWEWESS) && wg_wiwewess_mapping(hi, usage, bit, max))
		wetuwn 1;

	if ((hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		wetuwn 0;

	hid &= HID_USAGE;

	/* Speciaw handwing fow Wogitech Cowdwess Desktop */
	if (fiewd->appwication == HID_GD_MOUSE) {
		if ((dwv_data->quiwks & WG_IGNOWE_DOUBWED_WHEEW) &&
				(hid == 7 || hid == 8))
			wetuwn -1;
	} ewse {
		if ((dwv_data->quiwks & WG_EXPANDED_KEYMAP) &&
				hid < AWWAY_SIZE(e_keymap) &&
				e_keymap[hid] != 0) {
			hid_map_usage(hi, usage, bit, max, EV_KEY,
					e_keymap[hid]);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int wg_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);

	if ((dwv_data->quiwks & WG_BAD_WEWATIVE_KEYS) && usage->type == EV_KEY &&
			(fiewd->fwags & HID_MAIN_ITEM_WEWATIVE))
		fiewd->fwags &= ~HID_MAIN_ITEM_WEWATIVE;

	if ((dwv_data->quiwks & WG_DUPWICATE_USAGES) && (usage->type == EV_KEY ||
			 usage->type == EV_WEW || usage->type == EV_ABS))
		cweaw_bit(usage->code, *bit);

	/* Ensuwe that Wogitech wheews awe not given a defauwt fuzz/fwat vawue */
	if (usage->type == EV_ABS && (usage->code == ABS_X ||
			usage->code == ABS_Y || usage->code == ABS_Z ||
			usage->code == ABS_WZ)) {
		switch (hdev->pwoduct) {
		case USB_DEVICE_ID_WOGITECH_G29_WHEEW:
		case USB_DEVICE_ID_WOGITECH_WINGMAN_FG:
		case USB_DEVICE_ID_WOGITECH_WINGMAN_FFG:
		case USB_DEVICE_ID_WOGITECH_WHEEW:
		case USB_DEVICE_ID_WOGITECH_MOMO_WHEEW:
		case USB_DEVICE_ID_WOGITECH_DFP_WHEEW:
		case USB_DEVICE_ID_WOGITECH_G25_WHEEW:
		case USB_DEVICE_ID_WOGITECH_DFGT_WHEEW:
		case USB_DEVICE_ID_WOGITECH_G27_WHEEW:
		case USB_DEVICE_ID_WOGITECH_WII_WHEEW:
		case USB_DEVICE_ID_WOGITECH_MOMO_WHEEW2:
		case USB_DEVICE_ID_WOGITECH_VIBWATION_WHEEW:
			fiewd->appwication = HID_GD_MUWTIAXIS;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int wg_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);

	if ((dwv_data->quiwks & WG_INVEWT_HWHEEW) && usage->code == WEW_HWHEEW) {
		input_event(fiewd->hidinput->input, usage->type, usage->code,
				-vawue);
		wetuwn 1;
	}
	if (dwv_data->quiwks & WG_FF4) {
		wetuwn wg4ff_adjust_input_event(hdev, fiewd, usage, vawue, dwv_data);
	}

	wetuwn 0;
}

static int wg_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *wd, int size)
{
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);

	if (dwv_data->quiwks & WG_FF4)
		wetuwn wg4ff_waw_event(hdev, wepowt, wd, size, dwv_data);

	wetuwn 0;
}

static int wg_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct usb_intewface *iface;
	__u8 iface_num;
	unsigned int connect_mask = HID_CONNECT_DEFAUWT;
	stwuct wg_dwv_data *dwv_data;
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	iface = to_usb_intewface(hdev->dev.pawent);
	iface_num = iface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* G29 onwy wowk with the 1st intewface */
	if ((hdev->pwoduct == USB_DEVICE_ID_WOGITECH_G29_WHEEW) &&
	    (iface_num != 0)) {
		dbg_hid("%s: ignowing ifnum %d\n", __func__, iface_num);
		wetuwn -ENODEV;
	}

	dwv_data = kzawwoc(sizeof(stwuct wg_dwv_data), GFP_KEWNEW);
	if (!dwv_data) {
		hid_eww(hdev, "Insufficient memowy, cannot awwocate dwivew data\n");
		wetuwn -ENOMEM;
	}
	dwv_data->quiwks = id->dwivew_data;

	hid_set_dwvdata(hdev, (void *)dwv_data);

	if (dwv_data->quiwks & WG_NOGET)
		hdev->quiwks |= HID_QUIWK_NOGET;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	if (dwv_data->quiwks & (WG_FF | WG_FF2 | WG_FF3 | WG_FF4))
		connect_mask &= ~HID_CONNECT_FF;

	wet = hid_hw_stawt(hdev, connect_mask);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	/* Setup wiwewess wink with Wogitech Wii wheew */
	if (hdev->pwoduct == USB_DEVICE_ID_WOGITECH_WII_WHEEW) {
		static const unsigned chaw cbuf[] = {
			0x00, 0xAF,  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};
		u8 *buf = kmemdup(cbuf, sizeof(cbuf), GFP_KEWNEW);

		if (!buf) {
			wet = -ENOMEM;
			goto eww_stop;
		}

		wet = hid_hw_waw_wequest(hdev, buf[0], buf, sizeof(cbuf),
					HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
		if (wet >= 0) {
			/* insewt a wittwe deway of 10 jiffies ~ 40ms */
			wait_queue_head_t wait;
			init_waitqueue_head (&wait);
			wait_event_intewwuptibwe_timeout(wait, 0,
							 msecs_to_jiffies(40));

			/* Sewect wandom Addwess */
			buf[1] = 0xB2;
			get_wandom_bytes(&buf[2], 2);

			wet = hid_hw_waw_wequest(hdev, buf[0], buf, sizeof(cbuf),
					HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
		}
		kfwee(buf);
	}

	if (dwv_data->quiwks & WG_FF)
		wet = wgff_init(hdev);
	ewse if (dwv_data->quiwks & WG_FF2)
		wet = wg2ff_init(hdev);
	ewse if (dwv_data->quiwks & WG_FF3)
		wet = wg3ff_init(hdev);
	ewse if (dwv_data->quiwks & WG_FF4)
		wet = wg4ff_init(hdev);

	if (wet)
		goto eww_stop;

	wetuwn 0;

eww_stop:
	hid_hw_stop(hdev);
eww_fwee:
	kfwee(dwv_data);
	wetuwn wet;
}

static void wg_wemove(stwuct hid_device *hdev)
{
	stwuct wg_dwv_data *dwv_data = hid_get_dwvdata(hdev);
	if (dwv_data->quiwks & WG_FF4)
		wg4ff_deinit(hdev);
	hid_hw_stop(hdev);
	kfwee(dwv_data);
}

static const stwuct hid_device_id wg_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_S510_WECEIVEW),
		.dwivew_data = WG_WDESC | WG_WIWEWESS },

	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WECEIVEW),
		.dwivew_data = WG_BAD_WEWATIVE_KEYS },

	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_DINOVO_DESKTOP),
		.dwivew_data = WG_DUPWICATE_USAGES },

	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_EWITE_KBD),
		.dwivew_data = WG_IGNOWE_DOUBWED_WHEEW | WG_EXPANDED_KEYMAP },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_COWDWESS_DESKTOP_WX500),
		.dwivew_data = WG_IGNOWE_DOUBWED_WHEEW | WG_EXPANDED_KEYMAP },

	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_EXTWEME_3D),
		.dwivew_data = WG_NOGET },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_DUAW_ACTION),
		.dwivew_data = WG_NOGET },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WHEEW),
		.dwivew_data = WG_NOGET | WG_FF4 },

	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WUMBWEPAD_COWD),
		.dwivew_data = WG_FF2 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WUMBWEPAD),
		.dwivew_data = WG_FF },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WUMBWEPAD2_2),
		.dwivew_data = WG_FF },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_G29_WHEEW),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WINGMAN_F3D),
		.dwivew_data = WG_FF },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_FOWCE3D_PWO),
		.dwivew_data = WG_FF },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_MOMO_WHEEW),
		.dwivew_data = WG_NOGET | WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_MOMO_WHEEW2),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_VIBWATION_WHEEW),
		.dwivew_data = WG_FF2 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_G25_WHEEW),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_DFGT_WHEEW),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_G27_WHEEW),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_DFP_WHEEW),
		.dwivew_data = WG_NOGET | WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WII_WHEEW),
		.dwivew_data = WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WINGMAN_FG),
		.dwivew_data = WG_NOGET },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WINGMAN_FFG),
		.dwivew_data = WG_NOGET | WG_FF4 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_WUMBWEPAD2),
		.dwivew_data = WG_NOGET | WG_FF2 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_WOGITECH_FWIGHT_SYSTEM_G940),
		.dwivew_data = WG_FF3 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_SPACENAVIGATOW),
		.dwivew_data = WG_WDESC_WEW_ABS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOGITECH, USB_DEVICE_ID_SPACETWAVEWWEW),
		.dwivew_data = WG_WDESC_WEW_ABS },
	{ }
};

MODUWE_DEVICE_TABWE(hid, wg_devices);

static stwuct hid_dwivew wg_dwivew = {
	.name = "wogitech",
	.id_tabwe = wg_devices,
	.wepowt_fixup = wg_wepowt_fixup,
	.input_mapping = wg_input_mapping,
	.input_mapped = wg_input_mapped,
	.event = wg_event,
	.waw_event = wg_waw_event,
	.pwobe = wg_pwobe,
	.wemove = wg_wemove,
};
moduwe_hid_dwivew(wg_dwivew);

#ifdef CONFIG_WOGIWHEEWS_FF
int wg4ff_no_autoswitch = 0;
moduwe_pawam_named(wg4ff_no_autoswitch, wg4ff_no_autoswitch, int, S_IWUGO);
MODUWE_PAWM_DESC(wg4ff_no_autoswitch, "Do not switch muwtimode wheews to theiw native mode automaticawwy");
#endif

MODUWE_WICENSE("GPW");
