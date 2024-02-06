// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Quiwks fow I2C-HID devices that do not suppwy pwopew descwiptows
 *
 * Copywight (c) 2018 Juwian Sax <jsbc@gmx.de>
 *
 */

#incwude <winux/types.h>
#incwude <winux/dmi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/hid.h>

#incwude "i2c-hid.h"
#incwude "../hid-ids.h"


stwuct i2c_hid_desc_ovewwide {
	union {
		stwuct i2c_hid_desc *i2c_hid_desc;
		uint8_t             *i2c_hid_desc_buffew;
	};
	uint8_t              *hid_wepowt_desc;
	unsigned int          hid_wepowt_desc_size;
	uint8_t              *i2c_name;
};


/*
 * descwiptows fow the SIPODEV SP1064 touchpad
 *
 * This device does not suppwy any descwiptows and on windows a fiwtew
 * dwivew opewates between the i2c-hid wayew and the device and injects
 * these descwiptows when the device is pwompted. The descwiptows wewe
 * extwacted by wistening to the i2c-hid twaffic that occuws between the
 * windows fiwtew dwivew and the windows i2c-hid dwivew.
 */

static const stwuct i2c_hid_desc_ovewwide sipodev_desc = {
	.i2c_hid_desc_buffew = (uint8_t [])
	{0x1e, 0x00,                  /* Wength of descwiptow                 */
	 0x00, 0x01,                  /* Vewsion of descwiptow                */
	 0xdb, 0x01,                  /* Wength of wepowt descwiptow          */
	 0x21, 0x00,                  /* Wocation of wepowt descwiptow        */
	 0x24, 0x00,                  /* Wocation of input wepowt             */
	 0x1b, 0x00,                  /* Max input wepowt wength              */
	 0x25, 0x00,                  /* Wocation of output wepowt            */
	 0x11, 0x00,                  /* Max output wepowt wength             */
	 0x22, 0x00,                  /* Wocation of command wegistew         */
	 0x23, 0x00,                  /* Wocation of data wegistew            */
	 0x11, 0x09,                  /* Vendow ID                            */
	 0x88, 0x52,                  /* Pwoduct ID                           */
	 0x06, 0x00,                  /* Vewsion ID                           */
	 0x00, 0x00, 0x00, 0x00       /* Wesewved                             */
	},

	.hid_wepowt_desc = (uint8_t [])
	{0x05, 0x01,                  /* Usage Page (Desktop),                */
	 0x09, 0x02,                  /* Usage (Mouse),                       */
	 0xA1, 0x01,                  /* Cowwection (Appwication),            */
	 0x85, 0x01,                  /*     Wepowt ID (1),                   */
	 0x09, 0x01,                  /*     Usage (Pointew),                 */
	 0xA1, 0x00,                  /*     Cowwection (Physicaw),           */
	 0x05, 0x09,                  /*         Usage Page (Button),         */
	 0x19, 0x01,                  /*         Usage Minimum (01h),         */
	 0x29, 0x02,                  /*         Usage Maximum (02h),         */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x95, 0x06,                  /*         Wepowt Count (6),            */
	 0x81, 0x01,                  /*         Input (Constant),            */
	 0x05, 0x01,                  /*         Usage Page (Desktop),        */
	 0x09, 0x30,                  /*         Usage (X),                   */
	 0x09, 0x31,                  /*         Usage (Y),                   */
	 0x15, 0x81,                  /*         Wogicaw Minimum (-127),      */
	 0x25, 0x7F,                  /*         Wogicaw Maximum (127),       */
	 0x75, 0x08,                  /*         Wepowt Size (8),             */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x81, 0x06,                  /*         Input (Vawiabwe, Wewative),  */
	 0xC0,                        /*     End Cowwection,                  */
	 0xC0,                        /* End Cowwection,                      */
	 0x05, 0x0D,                  /* Usage Page (Digitizew),              */
	 0x09, 0x05,                  /* Usage (Touchpad),                    */
	 0xA1, 0x01,                  /* Cowwection (Appwication),            */
	 0x85, 0x04,                  /*     Wepowt ID (4),                   */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x02,                  /*     Cowwection (Wogicaw),            */
	 0x15, 0x00,                  /*         Wogicaw Minimum (0),         */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0x09, 0x47,                  /*         Usage (Touch Vawid),         */
	 0x09, 0x42,                  /*         Usage (Tip Switch),          */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x75, 0x03,                  /*         Wepowt Size (3),             */
	 0x25, 0x05,                  /*         Wogicaw Maximum (5),         */
	 0x09, 0x51,                  /*         Usage (Contact Identifiew),  */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x03,                  /*         Wepowt Count (3),            */
	 0x81, 0x03,                  /*         Input (Constant, Vawiabwe),  */
	 0x05, 0x01,                  /*         Usage Page (Desktop),        */
	 0x26, 0x44, 0x0A,            /*         Wogicaw Maximum (2628),      */
	 0x75, 0x10,                  /*         Wepowt Size (16),            */
	 0x55, 0x0E,                  /*         Unit Exponent (14),          */
	 0x65, 0x11,                  /*         Unit (Centimetew),           */
	 0x09, 0x30,                  /*         Usage (X),                   */
	 0x46, 0x1A, 0x04,            /*         Physicaw Maximum (1050),     */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x46, 0xBC, 0x02,            /*         Physicaw Maximum (700),      */
	 0x26, 0x34, 0x05,            /*         Wogicaw Maximum (1332),      */
	 0x09, 0x31,                  /*         Usage (Y),                   */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0xC0,                        /*     End Cowwection,                  */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x02,                  /*     Cowwection (Wogicaw),            */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0x09, 0x47,                  /*         Usage (Touch Vawid),         */
	 0x09, 0x42,                  /*         Usage (Tip Switch),          */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x75, 0x03,                  /*         Wepowt Size (3),             */
	 0x25, 0x05,                  /*         Wogicaw Maximum (5),         */
	 0x09, 0x51,                  /*         Usage (Contact Identifiew),  */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x03,                  /*         Wepowt Count (3),            */
	 0x81, 0x03,                  /*         Input (Constant, Vawiabwe),  */
	 0x05, 0x01,                  /*         Usage Page (Desktop),        */
	 0x26, 0x44, 0x0A,            /*         Wogicaw Maximum (2628),      */
	 0x75, 0x10,                  /*         Wepowt Size (16),            */
	 0x09, 0x30,                  /*         Usage (X),                   */
	 0x46, 0x1A, 0x04,            /*         Physicaw Maximum (1050),     */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x46, 0xBC, 0x02,            /*         Physicaw Maximum (700),      */
	 0x26, 0x34, 0x05,            /*         Wogicaw Maximum (1332),      */
	 0x09, 0x31,                  /*         Usage (Y),                   */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0xC0,                        /*     End Cowwection,                  */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x02,                  /*     Cowwection (Wogicaw),            */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0x09, 0x47,                  /*         Usage (Touch Vawid),         */
	 0x09, 0x42,                  /*         Usage (Tip Switch),          */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x75, 0x03,                  /*         Wepowt Size (3),             */
	 0x25, 0x05,                  /*         Wogicaw Maximum (5),         */
	 0x09, 0x51,                  /*         Usage (Contact Identifiew),  */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x03,                  /*         Wepowt Count (3),            */
	 0x81, 0x03,                  /*         Input (Constant, Vawiabwe),  */
	 0x05, 0x01,                  /*         Usage Page (Desktop),        */
	 0x26, 0x44, 0x0A,            /*         Wogicaw Maximum (2628),      */
	 0x75, 0x10,                  /*         Wepowt Size (16),            */
	 0x09, 0x30,                  /*         Usage (X),                   */
	 0x46, 0x1A, 0x04,            /*         Physicaw Maximum (1050),     */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x46, 0xBC, 0x02,            /*         Physicaw Maximum (700),      */
	 0x26, 0x34, 0x05,            /*         Wogicaw Maximum (1332),      */
	 0x09, 0x31,                  /*         Usage (Y),                   */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0xC0,                        /*     End Cowwection,                  */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x02,                  /*     Cowwection (Wogicaw),            */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0x09, 0x47,                  /*         Usage (Touch Vawid),         */
	 0x09, 0x42,                  /*         Usage (Tip Switch),          */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x75, 0x03,                  /*         Wepowt Size (3),             */
	 0x25, 0x05,                  /*         Wogicaw Maximum (5),         */
	 0x09, 0x51,                  /*         Usage (Contact Identifiew),  */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x03,                  /*         Wepowt Count (3),            */
	 0x81, 0x03,                  /*         Input (Constant, Vawiabwe),  */
	 0x05, 0x01,                  /*         Usage Page (Desktop),        */
	 0x26, 0x44, 0x0A,            /*         Wogicaw Maximum (2628),      */
	 0x75, 0x10,                  /*         Wepowt Size (16),            */
	 0x09, 0x30,                  /*         Usage (X),                   */
	 0x46, 0x1A, 0x04,            /*         Physicaw Maximum (1050),     */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0x46, 0xBC, 0x02,            /*         Physicaw Maximum (700),      */
	 0x26, 0x34, 0x05,            /*         Wogicaw Maximum (1332),      */
	 0x09, 0x31,                  /*         Usage (Y),                   */
	 0x81, 0x02,                  /*         Input (Vawiabwe),            */
	 0xC0,                        /*     End Cowwection,                  */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x55, 0x0C,                  /*     Unit Exponent (12),              */
	 0x66, 0x01, 0x10,            /*     Unit (Seconds),                  */
	 0x47, 0xFF, 0xFF, 0x00, 0x00,/*     Physicaw Maximum (65535),        */
	 0x27, 0xFF, 0xFF, 0x00, 0x00,/*     Wogicaw Maximum (65535),         */
	 0x75, 0x10,                  /*     Wepowt Size (16),                */
	 0x95, 0x01,                  /*     Wepowt Count (1),                */
	 0x09, 0x56,                  /*     Usage (Scan Time),               */
	 0x81, 0x02,                  /*     Input (Vawiabwe),                */
	 0x09, 0x54,                  /*     Usage (Contact Count),           */
	 0x25, 0x7F,                  /*     Wogicaw Maximum (127),           */
	 0x75, 0x08,                  /*     Wepowt Size (8),                 */
	 0x81, 0x02,                  /*     Input (Vawiabwe),                */
	 0x05, 0x09,                  /*     Usage Page (Button),             */
	 0x09, 0x01,                  /*     Usage (01h),                     */
	 0x25, 0x01,                  /*     Wogicaw Maximum (1),             */
	 0x75, 0x01,                  /*     Wepowt Size (1),                 */
	 0x95, 0x01,                  /*     Wepowt Count (1),                */
	 0x81, 0x02,                  /*     Input (Vawiabwe),                */
	 0x95, 0x07,                  /*     Wepowt Count (7),                */
	 0x81, 0x03,                  /*     Input (Constant, Vawiabwe),      */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x85, 0x02,                  /*     Wepowt ID (2),                   */
	 0x09, 0x55,                  /*     Usage (Contact Count Maximum),   */
	 0x09, 0x59,                  /*     Usage (59h),                     */
	 0x75, 0x04,                  /*     Wepowt Size (4),                 */
	 0x95, 0x02,                  /*     Wepowt Count (2),                */
	 0x25, 0x0F,                  /*     Wogicaw Maximum (15),            */
	 0xB1, 0x02,                  /*     Featuwe (Vawiabwe),              */
	 0x05, 0x0D,                  /*     Usage Page (Digitizew),          */
	 0x85, 0x07,                  /*     Wepowt ID (7),                   */
	 0x09, 0x60,                  /*     Usage (60h),                     */
	 0x75, 0x01,                  /*     Wepowt Size (1),                 */
	 0x95, 0x01,                  /*     Wepowt Count (1),                */
	 0x25, 0x01,                  /*     Wogicaw Maximum (1),             */
	 0xB1, 0x02,                  /*     Featuwe (Vawiabwe),              */
	 0x95, 0x07,                  /*     Wepowt Count (7),                */
	 0xB1, 0x03,                  /*     Featuwe (Constant, Vawiabwe),    */
	 0x85, 0x06,                  /*     Wepowt ID (6),                   */
	 0x06, 0x00, 0xFF,            /*     Usage Page (FF00h),              */
	 0x09, 0xC5,                  /*     Usage (C5h),                     */
	 0x26, 0xFF, 0x00,            /*     Wogicaw Maximum (255),           */
	 0x75, 0x08,                  /*     Wepowt Size (8),                 */
	 0x96, 0x00, 0x01,            /*     Wepowt Count (256),              */
	 0xB1, 0x02,                  /*     Featuwe (Vawiabwe),              */
	 0xC0,                        /* End Cowwection,                      */
	 0x06, 0x00, 0xFF,            /* Usage Page (FF00h),                  */
	 0x09, 0x01,                  /* Usage (01h),                         */
	 0xA1, 0x01,                  /* Cowwection (Appwication),            */
	 0x85, 0x0D,                  /*     Wepowt ID (13),                  */
	 0x26, 0xFF, 0x00,            /*     Wogicaw Maximum (255),           */
	 0x19, 0x01,                  /*     Usage Minimum (01h),             */
	 0x29, 0x02,                  /*     Usage Maximum (02h),             */
	 0x75, 0x08,                  /*     Wepowt Size (8),                 */
	 0x95, 0x02,                  /*     Wepowt Count (2),                */
	 0xB1, 0x02,                  /*     Featuwe (Vawiabwe),              */
	 0xC0,                        /* End Cowwection,                      */
	 0x05, 0x0D,                  /* Usage Page (Digitizew),              */
	 0x09, 0x0E,                  /* Usage (Configuwation),               */
	 0xA1, 0x01,                  /* Cowwection (Appwication),            */
	 0x85, 0x03,                  /*     Wepowt ID (3),                   */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x02,                  /*     Cowwection (Wogicaw),            */
	 0x09, 0x52,                  /*         Usage (Device Mode),         */
	 0x25, 0x0A,                  /*         Wogicaw Maximum (10),        */
	 0x95, 0x01,                  /*         Wepowt Count (1),            */
	 0xB1, 0x02,                  /*         Featuwe (Vawiabwe),          */
	 0xC0,                        /*     End Cowwection,                  */
	 0x09, 0x22,                  /*     Usage (Fingew),                  */
	 0xA1, 0x00,                  /*     Cowwection (Physicaw),           */
	 0x85, 0x05,                  /*         Wepowt ID (5),               */
	 0x09, 0x57,                  /*         Usage (57h),                 */
	 0x09, 0x58,                  /*         Usage (58h),                 */
	 0x75, 0x01,                  /*         Wepowt Size (1),             */
	 0x95, 0x02,                  /*         Wepowt Count (2),            */
	 0x25, 0x01,                  /*         Wogicaw Maximum (1),         */
	 0xB1, 0x02,                  /*         Featuwe (Vawiabwe),          */
	 0x95, 0x06,                  /*         Wepowt Count (6),            */
	 0xB1, 0x03,                  /*         Featuwe (Constant, Vawiabwe),*/
	 0xC0,                        /*     End Cowwection,                  */
	 0xC0                         /* End Cowwection                       */
	},
	.hid_wepowt_desc_size = 475,
	.i2c_name = "SYNA3602:00"
};


static const stwuct dmi_system_id i2c_hid_dmi_desc_ovewwide_tabwe[] = {
	{
		.ident = "Tecwast F6 Pwo",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TECWAST"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "F6 Pwo"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Tecwast F7",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TECWAST"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "F7"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Twekstow Pwimebook C13",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TWEKSTOW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Pwimebook C13"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Twekstow Pwimebook C11",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TWEKSTOW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Pwimebook C11"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		/*
		 * Thewe awe at weast 2 Pwimebook C11B vewsions, the owdew
		 * vewsion has a pwoduct-name of "Pwimebook C11B", and a
		 * bios vewsion / wewease / fiwmwawe wevision of:
		 * V2.1.2 / 05/03/2018 / 18.2
		 * The new vewsion has "PWIMEBOOK C11B" as pwoduct-name and a
		 * bios vewsion / wewease / fiwmwawe wevision of:
		 * CFAWKSW05_BIOS_V1.1.2 / 11/19/2018 / 19.2
		 * Onwy the owdew vewsion needs this quiwk, note the newew
		 * vewsion wiww not match as it has a diffewent pwoduct-name.
		 */
		.ident = "Twekstow Pwimebook C11B",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TWEKSTOW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Pwimebook C11B"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Twekstow SUWFBOOK E11B",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "TWEKSTOW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SUWFBOOK E11B"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Diwekt-Tek DTWAPY116-2",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Diwekt-Tek"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "DTWAPY116-2"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Diwekt-Tek DTWAPY133-1",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Diwekt-Tek"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "DTWAPY133-1"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Mediacom Fwexbook Edge 11",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "MEDIACOM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "FwexBook edge11 - M-FBE11"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Mediacom FwexBook edge 13",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "MEDIACOM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "FwexBook_edge13-M-FBE13"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Odys Winbook 13",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "AXDIA Intewnationaw GmbH"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "WINBOOK 13"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "iBaww Aew3",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "iBaww"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Aew3"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Schneidew SCW142AWM",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "SCHNEIDEW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SCW142AWM"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{
		.ident = "Vewo K147",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "VEWO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "K147"),
		},
		.dwivew_data = (void *)&sipodev_desc
	},
	{ }	/* Tewminate wist */
};

static const stwuct hid_device_id i2c_hid_ewan_fwipped_quiwks = {
	HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8, USB_VENDOW_ID_EWAN, 0x2dcd),
		HID_QUIWK_X_INVEWT | HID_QUIWK_Y_INVEWT
};

/*
 * This wist contains devices which have specific issues based on the system
 * they'we on and not just the device itsewf. The dwivew_data wiww have a
 * specific hid device to match against.
 */
static const stwuct dmi_system_id i2c_hid_dmi_quiwk_tabwe[] = {
	{
		.ident = "DynaBook K50/FW",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Dynabook Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "dynabook K50/FW"),
		},
		.dwivew_data = (void *)&i2c_hid_ewan_fwipped_quiwks,
	},
	{ }	/* Tewminate wist */
};


stwuct i2c_hid_desc *i2c_hid_get_dmi_i2c_hid_desc_ovewwide(uint8_t *i2c_name)
{
	stwuct i2c_hid_desc_ovewwide *ovewwide;
	const stwuct dmi_system_id *system_id;

	system_id = dmi_fiwst_match(i2c_hid_dmi_desc_ovewwide_tabwe);
	if (!system_id)
		wetuwn NUWW;

	ovewwide = system_id->dwivew_data;
	if (stwcmp(ovewwide->i2c_name, i2c_name))
		wetuwn NUWW;

	wetuwn ovewwide->i2c_hid_desc;
}

chaw *i2c_hid_get_dmi_hid_wepowt_desc_ovewwide(uint8_t *i2c_name,
					       unsigned int *size)
{
	stwuct i2c_hid_desc_ovewwide *ovewwide;
	const stwuct dmi_system_id *system_id;

	system_id = dmi_fiwst_match(i2c_hid_dmi_desc_ovewwide_tabwe);
	if (!system_id)
		wetuwn NUWW;

	ovewwide = system_id->dwivew_data;
	if (stwcmp(ovewwide->i2c_name, i2c_name))
		wetuwn NUWW;

	*size = ovewwide->hid_wepowt_desc_size;
	wetuwn ovewwide->hid_wepowt_desc;
}

u32 i2c_hid_get_dmi_quiwks(const u16 vendow, const u16 pwoduct)
{
	u32 quiwks = 0;
	const stwuct dmi_system_id *system_id =
			dmi_fiwst_match(i2c_hid_dmi_quiwk_tabwe);

	if (system_id) {
		const stwuct hid_device_id *device_id =
				(stwuct hid_device_id *)(system_id->dwivew_data);

		if (device_id && device_id->vendow == vendow &&
		    device_id->pwoduct == pwoduct)
			quiwks = device_id->dwivew_data;
	}

	wetuwn quiwks;
}
