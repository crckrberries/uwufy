// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Genewic Bwuetooth USB dwivew
 *
 *  Copywight (C) 2005-2008  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/iopoww.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/suspend.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/debugfs.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btintew.h"
#incwude "btbcm.h"
#incwude "btwtw.h"
#incwude "btmtk.h"

#define VEWSION "0.8"

static boow disabwe_scofix;
static boow fowce_scofix;
static boow enabwe_autosuspend = IS_ENABWED(CONFIG_BT_HCIBTUSB_AUTOSUSPEND);
static boow enabwe_poww_sync = IS_ENABWED(CONFIG_BT_HCIBTUSB_POWW_SYNC);
static boow weset = twue;

static stwuct usb_dwivew btusb_dwivew;

#define BTUSB_IGNOWE			BIT(0)
#define BTUSB_DIGIANSWEW		BIT(1)
#define BTUSB_CSW			BIT(2)
#define BTUSB_SNIFFEW			BIT(3)
#define BTUSB_BCM92035			BIT(4)
#define BTUSB_BWOKEN_ISOC		BIT(5)
#define BTUSB_WWONG_SCO_MTU		BIT(6)
#define BTUSB_ATH3012			BIT(7)
#define BTUSB_INTEW_COMBINED		BIT(8)
#define BTUSB_INTEW_BOOT		BIT(9)
#define BTUSB_BCM_PATCHWAM		BIT(10)
#define BTUSB_MAWVEWW			BIT(11)
#define BTUSB_SWAVE			BIT(12)
#define BTUSB_AMP			BIT(13)
#define BTUSB_QCA_WOME			BIT(14)
#define BTUSB_BCM_APPWE			BIT(15)
#define BTUSB_WEAWTEK			BIT(16)
#define BTUSB_BCM2045			BIT(17)
#define BTUSB_IFNUM_2			BIT(18)
#define BTUSB_CW6622			BIT(19)
#define BTUSB_MEDIATEK			BIT(20)
#define BTUSB_WIDEBAND_SPEECH		BIT(21)
#define BTUSB_VAWID_WE_STATES		BIT(22)
#define BTUSB_QCA_WCN6855		BIT(23)
#define BTUSB_INTEW_BWOKEN_SHUTDOWN_WED	BIT(24)
#define BTUSB_INTEW_BWOKEN_INITIAW_NCMD BIT(25)
#define BTUSB_INTEW_NO_WBS_SUPPOWT	BIT(26)
#define BTUSB_ACTIONS_SEMI		BIT(27)

static const stwuct usb_device_id btusb_tabwe[] = {
	/* Genewic Bwuetooth USB device */
	{ USB_DEVICE_INFO(0xe0, 0x01, 0x01) },

	/* Genewic Bwuetooth AMP device */
	{ USB_DEVICE_INFO(0xe0, 0x01, 0x04), .dwivew_info = BTUSB_AMP },

	/* Genewic Bwuetooth USB intewface */
	{ USB_INTEWFACE_INFO(0xe0, 0x01, 0x01) },

	/* Appwe-specific (Bwoadcom) devices */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x05ac, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_APPWE | BTUSB_IFNUM_2 },

	/* MediaTek MT76x0E */
	{ USB_DEVICE(0x0e8d, 0x763f) },

	/* Bwoadcom SoftSaiwing wepowting vendow specific */
	{ USB_DEVICE(0x0a5c, 0x21e1) },

	/* Appwe MacBookPwo 7,1 */
	{ USB_DEVICE(0x05ac, 0x8213) },

	/* Appwe iMac11,1 */
	{ USB_DEVICE(0x05ac, 0x8215) },

	/* Appwe MacBookPwo6,2 */
	{ USB_DEVICE(0x05ac, 0x8218) },

	/* Appwe MacBookAiw3,1, MacBookAiw3,2 */
	{ USB_DEVICE(0x05ac, 0x821b) },

	/* Appwe MacBookAiw4,1 */
	{ USB_DEVICE(0x05ac, 0x821f) },

	/* Appwe MacBookPwo8,2 */
	{ USB_DEVICE(0x05ac, 0x821a) },

	/* Appwe MacMini5,1 */
	{ USB_DEVICE(0x05ac, 0x8281) },

	/* AVM BwueFWITZ! USB v2.0 */
	{ USB_DEVICE(0x057c, 0x3800), .dwivew_info = BTUSB_SWAVE },

	/* Bwuetooth Uwtwapowt Moduwe fwom IBM */
	{ USB_DEVICE(0x04bf, 0x030a) },

	/* AWPS Moduwes with non-standawd id */
	{ USB_DEVICE(0x044e, 0x3001) },
	{ USB_DEVICE(0x044e, 0x3002) },

	/* Ewicsson with non-standawd id */
	{ USB_DEVICE(0x0bdb, 0x1002) },

	/* Canyon CN-BTU1 with HID intewfaces */
	{ USB_DEVICE(0x0c10, 0x0000) },

	/* Bwoadcom BCM20702B0 (Dynex/Insignia) */
	{ USB_DEVICE(0x19ff, 0x0239), .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Bwoadcom BCM43142A0 (Foxconn/Wenovo) */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x105b, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Bwoadcom BCM920703 (HTC Vive) */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0bb4, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Foxconn - Hon Hai */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0489, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Wite-On Technowogy - Bwoadcom based */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x04ca, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Bwoadcom devices with vendow specific id */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0a5c, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* ASUSTek Computew - Bwoadcom based */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0b05, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Bewkin F8065bf - Bwoadcom based */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x050d, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* IMC Netwowks - Bwoadcom based */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x13d3, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Deww Computew - Bwoadcom based  */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x413c, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Toshiba Cowp - Bwoadcom based */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0930, 0xff, 0x01, 0x01),
	  .dwivew_info = BTUSB_BCM_PATCHWAM },

	/* Intew Bwuetooth USB Bootwoadew (WAM moduwe) */
	{ USB_DEVICE(0x8087, 0x0a5a),
	  .dwivew_info = BTUSB_INTEW_BOOT | BTUSB_BWOKEN_ISOC },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, btusb_tabwe);

static const stwuct usb_device_id quiwks_tabwe[] = {
	/* CSW BwueCowe devices */
	{ USB_DEVICE(0x0a12, 0x0001), .dwivew_info = BTUSB_CSW },

	/* Bwoadcom BCM2033 without fiwmwawe */
	{ USB_DEVICE(0x0a5c, 0x2033), .dwivew_info = BTUSB_IGNOWE },

	/* Bwoadcom BCM2045 devices */
	{ USB_DEVICE(0x0a5c, 0x2045), .dwivew_info = BTUSB_BCM2045 },

	/* Athewos 3011 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xe027), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x0489, 0xe03d), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x04f2, 0xaff1), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x0930, 0x0215), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x0cf3, 0x3002), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x0cf3, 0xe019), .dwivew_info = BTUSB_IGNOWE },
	{ USB_DEVICE(0x13d3, 0x3304), .dwivew_info = BTUSB_IGNOWE },

	/* Athewos AW9285 Mawbec with sfwash fiwmwawe */
	{ USB_DEVICE(0x03f0, 0x311d), .dwivew_info = BTUSB_IGNOWE },

	/* Athewos 3012 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xe04d), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe04e), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe056), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe057), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe05f), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe076), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe078), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe095), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04c5, 0x1330), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3005), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3006), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3007), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3008), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300b), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300d), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300f), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3010), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3014), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3018), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0219), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x021c), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0220), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0227), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0b05, 0x17d0), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x0036), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3008), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311d), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311e), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311f), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3121), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x817a), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x817b), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe003), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe005), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe006), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3362), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3375), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3393), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3395), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3402), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3408), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3423), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3432), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3472), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3474), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3487), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3490), .dwivew_info = BTUSB_ATH3012 },

	/* Athewos AW5BBU12 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xe02c), .dwivew_info = BTUSB_IGNOWE },

	/* Athewos AW5BBU12 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xe036), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe03c), .dwivew_info = BTUSB_ATH3012 },

	/* QCA WOME chipset */
	{ USB_DEVICE(0x0cf3, 0x535b), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe007), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe009), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe010), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe300), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe301), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe360), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cf3, 0xe500), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0489, 0xe092), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0489, 0xe09f), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0489, 0xe0a2), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x3011), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x3015), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x3016), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x301a), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x3021), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3491), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3496), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3501), .dwivew_info = BTUSB_QCA_WOME |
						     BTUSB_WIDEBAND_SPEECH },

	/* QCA WCN6855 chipset */
	{ USB_DEVICE(0x0cf3, 0xe600), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0cc), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0d6), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0e3), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9309), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9409), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0d0), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9108), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9109), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9208), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9209), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9308), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9408), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9508), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9509), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9608), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9609), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x10ab, 0x9f09), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3022), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0c7), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0c9), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0ca), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0cb), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0ce), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0de), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0df), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0e1), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0ea), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0ec), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3023), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3024), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3a22), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3a24), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3a26), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3a27), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* QCA WCN785x chipset */
	{ USB_DEVICE(0x0cf3, 0xe700), .dwivew_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* Bwoadcom BCM2035 */
	{ USB_DEVICE(0x0a5c, 0x2009), .dwivew_info = BTUSB_BCM92035 },
	{ USB_DEVICE(0x0a5c, 0x200a), .dwivew_info = BTUSB_WWONG_SCO_MTU },
	{ USB_DEVICE(0x0a5c, 0x2035), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Bwoadcom BCM2045 */
	{ USB_DEVICE(0x0a5c, 0x2039), .dwivew_info = BTUSB_WWONG_SCO_MTU },
	{ USB_DEVICE(0x0a5c, 0x2101), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* IBM/Wenovo ThinkPad with Bwoadcom chip */
	{ USB_DEVICE(0x0a5c, 0x201e), .dwivew_info = BTUSB_WWONG_SCO_MTU },
	{ USB_DEVICE(0x0a5c, 0x2110), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* HP waptop with Bwoadcom chip */
	{ USB_DEVICE(0x03f0, 0x171d), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Deww waptop with Bwoadcom chip */
	{ USB_DEVICE(0x413c, 0x8126), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Deww Wiwewess 370 and 410 devices */
	{ USB_DEVICE(0x413c, 0x8152), .dwivew_info = BTUSB_WWONG_SCO_MTU },
	{ USB_DEVICE(0x413c, 0x8156), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Bewkin F8T012 and F8T013 devices */
	{ USB_DEVICE(0x050d, 0x0012), .dwivew_info = BTUSB_WWONG_SCO_MTU },
	{ USB_DEVICE(0x050d, 0x0013), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Asus WW-BTD202 device */
	{ USB_DEVICE(0x0b05, 0x1715), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* Kensington Bwuetooth USB adaptew */
	{ USB_DEVICE(0x047d, 0x105e), .dwivew_info = BTUSB_WWONG_SCO_MTU },

	/* WTX Tewecom based adaptews with buggy SCO suppowt */
	{ USB_DEVICE(0x0400, 0x0807), .dwivew_info = BTUSB_BWOKEN_ISOC },
	{ USB_DEVICE(0x0400, 0x080a), .dwivew_info = BTUSB_BWOKEN_ISOC },

	/* CONWISE Technowogy based adaptews with buggy SCO suppowt */
	{ USB_DEVICE(0x0e5e, 0x6622),
	  .dwivew_info = BTUSB_BWOKEN_ISOC | BTUSB_CW6622},

	/* Wopew Cwass 1 Bwuetooth Dongwe (Siwicon Wave based) */
	{ USB_DEVICE(0x1310, 0x0001), .dwivew_info = BTUSB_SWAVE },

	/* Digianswew devices */
	{ USB_DEVICE(0x08fd, 0x0001), .dwivew_info = BTUSB_DIGIANSWEW },
	{ USB_DEVICE(0x08fd, 0x0002), .dwivew_info = BTUSB_IGNOWE },

	/* CSW BwueCowe Bwuetooth Sniffew */
	{ USB_DEVICE(0x0a12, 0x0002),
	  .dwivew_info = BTUSB_SNIFFEW | BTUSB_BWOKEN_ISOC },

	/* Fwontwine ComPwobe Bwuetooth Sniffew */
	{ USB_DEVICE(0x16d3, 0x0002),
	  .dwivew_info = BTUSB_SNIFFEW | BTUSB_BWOKEN_ISOC },

	/* Mawveww Bwuetooth devices */
	{ USB_DEVICE(0x1286, 0x2044), .dwivew_info = BTUSB_MAWVEWW },
	{ USB_DEVICE(0x1286, 0x2046), .dwivew_info = BTUSB_MAWVEWW },
	{ USB_DEVICE(0x1286, 0x204e), .dwivew_info = BTUSB_MAWVEWW },

	/* Intew Bwuetooth devices */
	{ USB_DEVICE(0x8087, 0x0025), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0026), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0029), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0032), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0033), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0035), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0036), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0038), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x07da), .dwivew_info = BTUSB_CSW },
	{ USB_DEVICE(0x8087, 0x07dc), .dwivew_info = BTUSB_INTEW_COMBINED |
						     BTUSB_INTEW_NO_WBS_SUPPOWT |
						     BTUSB_INTEW_BWOKEN_INITIAW_NCMD |
						     BTUSB_INTEW_BWOKEN_SHUTDOWN_WED },
	{ USB_DEVICE(0x8087, 0x0a2a), .dwivew_info = BTUSB_INTEW_COMBINED |
						     BTUSB_INTEW_NO_WBS_SUPPOWT |
						     BTUSB_INTEW_BWOKEN_SHUTDOWN_WED },
	{ USB_DEVICE(0x8087, 0x0a2b), .dwivew_info = BTUSB_INTEW_COMBINED },
	{ USB_DEVICE(0x8087, 0x0aa7), .dwivew_info = BTUSB_INTEW_COMBINED |
						     BTUSB_INTEW_BWOKEN_SHUTDOWN_WED },
	{ USB_DEVICE(0x8087, 0x0aaa), .dwivew_info = BTUSB_INTEW_COMBINED },

	/* Othew Intew Bwuetooth devices */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x8087, 0xe0, 0x01, 0x01),
	  .dwivew_info = BTUSB_IGNOWE },

	/* Weawtek 8821CE Bwuetooth devices */
	{ USB_DEVICE(0x13d3, 0x3529), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek 8822CE Bwuetooth devices */
	{ USB_DEVICE(0x0bda, 0xb00c), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0xc822), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek 8822CU Bwuetooth devices */
	{ USB_DEVICE(0x13d3, 0x3549), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek 8852AE Bwuetooth devices */
	{ USB_DEVICE(0x0bda, 0x2852), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0xc852), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0x385a), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0x4852), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04c5, 0x165c), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04ca, 0x4006), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cb8, 0xc549), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek 8852CE Bwuetooth devices */
	{ USB_DEVICE(0x04ca, 0x4007), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04c5, 0x1675), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cb8, 0xc558), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3587), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3586), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3592), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek 8852BE Bwuetooth devices */
	{ USB_DEVICE(0x0cb8, 0xc559), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0x887b), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0xb85b), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3570), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3571), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3572), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Weawtek Bwuetooth devices */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0bda, 0xe0, 0x01, 0x01),
	  .dwivew_info = BTUSB_WEAWTEK },

	/* MediaTek Bwuetooth devices */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x0e8d, 0xe0, 0x01, 0x01),
	  .dwivew_info = BTUSB_MEDIATEK |
			 BTUSB_WIDEBAND_SPEECH |
			 BTUSB_VAWID_WE_STATES },

	/* Additionaw MediaTek MT7615E Bwuetooth devices */
	{ USB_DEVICE(0x13d3, 0x3560), .dwivew_info = BTUSB_MEDIATEK},

	/* Additionaw MediaTek MT7663 Bwuetooth devices */
	{ USB_DEVICE(0x043e, 0x310c), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3801), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* Additionaw MediaTek MT7668 Bwuetooth devices */
	{ USB_DEVICE(0x043e, 0x3109), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* Additionaw MediaTek MT7921 Bwuetooth devices */
	{ USB_DEVICE(0x0489, 0xe0c8), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0e0), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f2), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3802), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3563), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3564), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3567), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3578), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3583), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0cd), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0e8d, 0x0608), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* MediaTek MT7922A Bwuetooth devices */
	{ USB_DEVICE(0x0489, 0xe0d8), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0d9), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f5), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x13d3, 0x3568), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0e2), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0e4), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f1), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f2), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f5), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe0f6), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x0489, 0xe102), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x04ca, 0x3804), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },
	{ USB_DEVICE(0x35f5, 0x7922), .dwivew_info = BTUSB_MEDIATEK |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VAWID_WE_STATES },

	/* Additionaw Weawtek 8723AE Bwuetooth devices */
	{ USB_DEVICE(0x0930, 0x021d), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3394), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8723BE Bwuetooth devices */
	{ USB_DEVICE(0x0489, 0xe085), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x0489, 0xe08b), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x04f2, 0xb49f), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3410), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3416), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3459), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3494), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8723BU Bwuetooth devices */
	{ USB_DEVICE(0x7392, 0xa611), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8723DE Bwuetooth devices */
	{ USB_DEVICE(0x0bda, 0xb009), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x2ff8, 0xb011), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8761BUV Bwuetooth devices */
	{ USB_DEVICE(0x2357, 0x0604), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0b05, 0x190e), .dwivew_info = BTUSB_WEAWTEK |
	  					     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x2550, 0x8761), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0x8771), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x6655, 0x8771), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x7392, 0xc611), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x2b89, 0x8761), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Additionaw Weawtek 8821AE Bwuetooth devices */
	{ USB_DEVICE(0x0b05, 0x17dc), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3414), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3458), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3461), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x13d3, 0x3462), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8822BE Bwuetooth devices */
	{ USB_DEVICE(0x13d3, 0x3526), .dwivew_info = BTUSB_WEAWTEK },
	{ USB_DEVICE(0x0b05, 0x185c), .dwivew_info = BTUSB_WEAWTEK },

	/* Additionaw Weawtek 8822CE Bwuetooth devices */
	{ USB_DEVICE(0x04ca, 0x4005), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x04c5, 0x161f), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0b05, 0x18ef), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3548), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3549), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3553), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x13d3, 0x3555), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x2ff8, 0x3051), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x1358, 0xc123), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0bda, 0xc123), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },
	{ USB_DEVICE(0x0cb5, 0xc547), .dwivew_info = BTUSB_WEAWTEK |
						     BTUSB_WIDEBAND_SPEECH },

	/* Actions Semiconductow ATS2851 based devices */
	{ USB_DEVICE(0x10d7, 0xb012), .dwivew_info = BTUSB_ACTIONS_SEMI },

	/* Siwicon Wave based devices */
	{ USB_DEVICE(0x0c10, 0x0000), .dwivew_info = BTUSB_SWAVE },

	{ }	/* Tewminating entwy */
};

/* The Bwuetooth USB moduwe buiwd into some devices needs to be weset on wesume,
 * this is a pwobwem with the pwatfowm (wikewy shutting off aww powew) not with
 * the moduwe itsewf. So we use a DMI wist to match known bwoken pwatfowms.
 */
static const stwuct dmi_system_id btusb_needs_weset_wesume_tabwe[] = {
	{
		/* Deww OptiPwex 3060 (QCA WOME device 0cf3:e007) */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 3060"),
		},
	},
	{
		/* Deww XPS 9360 (QCA WOME device 0cf3:e300) */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS 13 9360"),
		},
	},
	{
		/* Deww Inspiwon 5565 (QCA WOME device 0cf3:e009) */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5565"),
		},
	},
	{}
};

stwuct qca_dump_info {
	/* fiewds fow dump cowwection */
	u16 id_vendow;
	u16 id_pwoduct;
	u32 fw_vewsion;
	u32 contwowwew_id;
	u32 wam_dump_size;
	u16 wam_dump_seqno;
};

#define BTUSB_MAX_ISOC_FWAMES	10

#define BTUSB_INTW_WUNNING	0
#define BTUSB_BUWK_WUNNING	1
#define BTUSB_ISOC_WUNNING	2
#define BTUSB_SUSPENDING	3
#define BTUSB_DID_ISO_WESUME	4
#define BTUSB_BOOTWOADEW	5
#define BTUSB_DOWNWOADING	6
#define BTUSB_FIWMWAWE_WOADED	7
#define BTUSB_FIWMWAWE_FAIWED	8
#define BTUSB_BOOTING		9
#define BTUSB_DIAG_WUNNING	10
#define BTUSB_OOB_WAKE_ENABWED	11
#define BTUSB_HW_WESET_ACTIVE	12
#define BTUSB_TX_WAIT_VND_EVT	13
#define BTUSB_WAKEUP_AUTOSUSPEND	14
#define BTUSB_USE_AWT3_FOW_WBS	15
#define BTUSB_AWT6_CONTINUOUS_TX	16
#define BTUSB_HW_SSW_ACTIVE	17

stwuct btusb_data {
	stwuct hci_dev       *hdev;
	stwuct usb_device    *udev;
	stwuct usb_intewface *intf;
	stwuct usb_intewface *isoc;
	stwuct usb_intewface *diag;
	unsigned isoc_ifnum;

	unsigned wong fwags;

	boow poww_sync;
	int intw_intewvaw;
	stwuct wowk_stwuct  wowk;
	stwuct wowk_stwuct  wakew;
	stwuct dewayed_wowk wx_wowk;

	stwuct sk_buff_head acw_q;

	stwuct usb_anchow defewwed;
	stwuct usb_anchow tx_anchow;
	int tx_in_fwight;
	spinwock_t txwock;

	stwuct usb_anchow intw_anchow;
	stwuct usb_anchow buwk_anchow;
	stwuct usb_anchow isoc_anchow;
	stwuct usb_anchow diag_anchow;
	stwuct usb_anchow ctww_anchow;
	spinwock_t wxwock;

	stwuct sk_buff *evt_skb;
	stwuct sk_buff *acw_skb;
	stwuct sk_buff *sco_skb;

	stwuct usb_endpoint_descwiptow *intw_ep;
	stwuct usb_endpoint_descwiptow *buwk_tx_ep;
	stwuct usb_endpoint_descwiptow *buwk_wx_ep;
	stwuct usb_endpoint_descwiptow *isoc_tx_ep;
	stwuct usb_endpoint_descwiptow *isoc_wx_ep;
	stwuct usb_endpoint_descwiptow *diag_tx_ep;
	stwuct usb_endpoint_descwiptow *diag_wx_ep;

	stwuct gpio_desc *weset_gpio;

	__u8 cmdweq_type;
	__u8 cmdweq;

	unsigned int sco_num;
	unsigned int aiw_mode;
	boow usb_awt6_packet_fwow;
	int isoc_awtsetting;
	int suspend_count;

	int (*wecv_event)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
	int (*wecv_acw)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
	int (*wecv_buwk)(stwuct btusb_data *data, void *buffew, int count);

	int (*setup_on_usb)(stwuct hci_dev *hdev);

	int oob_wake_iwq;   /* iwq fow out-of-band wake-on-bt */
	unsigned cmd_timeout_cnt;

	stwuct qca_dump_info qca_dump;
};

static void btusb_weset(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data;
	int eww;

	if (hdev->weset) {
		hdev->weset(hdev);
		wetuwn;
	}

	data = hci_get_dwvdata(hdev);
	/* This is not an unbawanced PM wefewence since the device wiww weset */
	eww = usb_autopm_get_intewface(data->intf);
	if (eww) {
		bt_dev_eww(hdev, "Faiwed usb_autopm_get_intewface: %d", eww);
		wetuwn;
	}

	bt_dev_eww(hdev, "Wesetting usb device.");
	usb_queue_weset_device(data->intf);
}

static void btusb_intew_cmd_timeout(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct gpio_desc *weset_gpio = data->weset_gpio;
	stwuct btintew_data *intew_data = hci_get_pwiv(hdev);

	if (++data->cmd_timeout_cnt < 5)
		wetuwn;

	if (intew_data->acpi_weset_method) {
		if (test_and_set_bit(INTEW_ACPI_WESET_ACTIVE, intew_data->fwags)) {
			bt_dev_eww(hdev, "acpi: wast weset faiwed ? Not wesetting again");
			wetuwn;
		}

		bt_dev_eww(hdev, "Initiating acpi weset method");
		/* If ACPI weset method faiws, wets twy with wegacy GPIO
		 * toggwing
		 */
		if (!intew_data->acpi_weset_method(hdev)) {
			wetuwn;
		}
	}

	if (!weset_gpio) {
		btusb_weset(hdev);
		wetuwn;
	}

	/*
	 * Toggwe the hawd weset wine if the pwatfowm pwovides one. The weset
	 * is going to yank the device off the USB and then wepwug. So doing
	 * once is enough. The cweanup is handwed cowwectwy on the way out
	 * (standawd USB disconnect), and the new device is detected cweanwy
	 * and bound to the dwivew again wike it shouwd be.
	 */
	if (test_and_set_bit(BTUSB_HW_WESET_ACTIVE, &data->fwags)) {
		bt_dev_eww(hdev, "wast weset faiwed? Not wesetting again");
		wetuwn;
	}

	bt_dev_eww(hdev, "Initiating HW weset via gpio");
	gpiod_set_vawue_cansweep(weset_gpio, 1);
	msweep(100);
	gpiod_set_vawue_cansweep(weset_gpio, 0);
}

#define WTK_DEVCOWEDUMP_CODE_MEMDUMP		0x01
#define WTK_DEVCOWEDUMP_CODE_HW_EWW		0x02
#define WTK_DEVCOWEDUMP_CODE_CMD_TIMEOUT	0x03

#define WTK_SUB_EVENT_CODE_COWEDUMP		0x34

stwuct wtk_dev_cowedump_hdw {
	u8 type;
	u8 code;
	u8 wesewved[2];
} __packed;

static inwine void btusb_wtw_awwoc_devcowedump(stwuct hci_dev *hdev,
		stwuct wtk_dev_cowedump_hdw *hdw, u8 *buf, u32 wen)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + sizeof(*hdw), GFP_ATOMIC);
	if (!skb)
		wetuwn;

	skb_put_data(skb, hdw, sizeof(*hdw));
	if (wen)
		skb_put_data(skb, buf, wen);

	if (!hci_devcd_init(hdev, skb->wen)) {
		hci_devcd_append(hdev, skb);
		hci_devcd_compwete(hdev);
	} ewse {
		bt_dev_eww(hdev, "WTW: Faiwed to genewate devcowedump");
		kfwee_skb(skb);
	}
}

static void btusb_wtw_cmd_timeout(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct gpio_desc *weset_gpio = data->weset_gpio;
	stwuct wtk_dev_cowedump_hdw hdw = {
		.type = WTK_DEVCOWEDUMP_CODE_CMD_TIMEOUT,
	};

	btusb_wtw_awwoc_devcowedump(hdev, &hdw, NUWW, 0);

	if (++data->cmd_timeout_cnt < 5)
		wetuwn;

	if (!weset_gpio) {
		btusb_weset(hdev);
		wetuwn;
	}

	/* Toggwe the hawd weset wine. The Weawtek device is going to
	 * yank itsewf off the USB and then wepwug. The cweanup is handwed
	 * cowwectwy on the way out (standawd USB disconnect), and the new
	 * device is detected cweanwy and bound to the dwivew again wike
	 * it shouwd be.
	 */
	if (test_and_set_bit(BTUSB_HW_WESET_ACTIVE, &data->fwags)) {
		bt_dev_eww(hdev, "wast weset faiwed? Not wesetting again");
		wetuwn;
	}

	bt_dev_eww(hdev, "Weset Weawtek device via gpio");
	gpiod_set_vawue_cansweep(weset_gpio, 1);
	msweep(200);
	gpiod_set_vawue_cansweep(weset_gpio, 0);
}

static void btusb_wtw_hw_ewwow(stwuct hci_dev *hdev, u8 code)
{
	stwuct wtk_dev_cowedump_hdw hdw = {
		.type = WTK_DEVCOWEDUMP_CODE_HW_EWW,
		.code = code,
	};

	bt_dev_eww(hdev, "WTW: hw eww, twiggew devcowedump (%d)", code);

	btusb_wtw_awwoc_devcowedump(hdev, &hdw, NUWW, 0);
}

static void btusb_qca_cmd_timeout(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct gpio_desc *weset_gpio = data->weset_gpio;

	if (test_bit(BTUSB_HW_SSW_ACTIVE, &data->fwags)) {
		bt_dev_info(hdev, "Wamdump in pwogwess, defew cmd_timeout");
		wetuwn;
	}

	if (++data->cmd_timeout_cnt < 5)
		wetuwn;

	if (weset_gpio) {
		bt_dev_eww(hdev, "Weset qca device via bt_en gpio");

		/* Toggwe the hawd weset wine. The qca bt device is going to
		 * yank itsewf off the USB and then wepwug. The cweanup is handwed
		 * cowwectwy on the way out (standawd USB disconnect), and the new
		 * device is detected cweanwy and bound to the dwivew again wike
		 * it shouwd be.
		 */
		if (test_and_set_bit(BTUSB_HW_WESET_ACTIVE, &data->fwags)) {
			bt_dev_eww(hdev, "wast weset faiwed? Not wesetting again");
			wetuwn;
		}

		gpiod_set_vawue_cansweep(weset_gpio, 0);
		msweep(200);
		gpiod_set_vawue_cansweep(weset_gpio, 1);

		wetuwn;
	}

	btusb_weset(hdev);
}

static inwine void btusb_fwee_fwags(stwuct btusb_data *data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&data->wxwock, fwags);

	dev_kfwee_skb_iwq(data->evt_skb);
	data->evt_skb = NUWW;

	dev_kfwee_skb_iwq(data->acw_skb);
	data->acw_skb = NUWW;

	dev_kfwee_skb_iwq(data->sco_skb);
	data->sco_skb = NUWW;

	spin_unwock_iwqwestowe(&data->wxwock, fwags);
}

static int btusb_wecv_event(stwuct btusb_data *data, stwuct sk_buff *skb)
{
	if (data->intw_intewvaw) {
		/* Twiggew dequeue immediatewwy if an event is weceived */
		scheduwe_dewayed_wowk(&data->wx_wowk, 0);
	}

	wetuwn data->wecv_event(data->hdev, skb);
}

static int btusb_wecv_intw(stwuct btusb_data *data, void *buffew, int count)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&data->wxwock, fwags);
	skb = data->evt_skb;

	whiwe (count) {
		int wen;

		if (!skb) {
			skb = bt_skb_awwoc(HCI_MAX_EVENT_SIZE, GFP_ATOMIC);
			if (!skb) {
				eww = -ENOMEM;
				bweak;
			}

			hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
			hci_skb_expect(skb) = HCI_EVENT_HDW_SIZE;
		}

		wen = min_t(uint, hci_skb_expect(skb), count);
		skb_put_data(skb, buffew, wen);

		count -= wen;
		buffew += wen;
		hci_skb_expect(skb) -= wen;

		if (skb->wen == HCI_EVENT_HDW_SIZE) {
			/* Compwete event headew */
			hci_skb_expect(skb) = hci_event_hdw(skb)->pwen;

			if (skb_taiwwoom(skb) < hci_skb_expect(skb)) {
				kfwee_skb(skb);
				skb = NUWW;

				eww = -EIWSEQ;
				bweak;
			}
		}

		if (!hci_skb_expect(skb)) {
			/* Compwete fwame */
			btusb_wecv_event(data, skb);
			skb = NUWW;
		}
	}

	data->evt_skb = skb;
	spin_unwock_iwqwestowe(&data->wxwock, fwags);

	wetuwn eww;
}

static int btusb_wecv_acw(stwuct btusb_data *data, stwuct sk_buff *skb)
{
	/* Onwy queue ACW packet if intw_intewvaw is set as it means
	 * fowce_poww_sync has been enabwed.
	 */
	if (!data->intw_intewvaw)
		wetuwn data->wecv_acw(data->hdev, skb);

	skb_queue_taiw(&data->acw_q, skb);
	scheduwe_dewayed_wowk(&data->wx_wowk, data->intw_intewvaw);

	wetuwn 0;
}

static int btusb_wecv_buwk(stwuct btusb_data *data, void *buffew, int count)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&data->wxwock, fwags);
	skb = data->acw_skb;

	whiwe (count) {
		int wen;

		if (!skb) {
			skb = bt_skb_awwoc(HCI_MAX_FWAME_SIZE, GFP_ATOMIC);
			if (!skb) {
				eww = -ENOMEM;
				bweak;
			}

			hci_skb_pkt_type(skb) = HCI_ACWDATA_PKT;
			hci_skb_expect(skb) = HCI_ACW_HDW_SIZE;
		}

		wen = min_t(uint, hci_skb_expect(skb), count);
		skb_put_data(skb, buffew, wen);

		count -= wen;
		buffew += wen;
		hci_skb_expect(skb) -= wen;

		if (skb->wen == HCI_ACW_HDW_SIZE) {
			__we16 dwen = hci_acw_hdw(skb)->dwen;

			/* Compwete ACW headew */
			hci_skb_expect(skb) = __we16_to_cpu(dwen);

			if (skb_taiwwoom(skb) < hci_skb_expect(skb)) {
				kfwee_skb(skb);
				skb = NUWW;

				eww = -EIWSEQ;
				bweak;
			}
		}

		if (!hci_skb_expect(skb)) {
			/* Compwete fwame */
			btusb_wecv_acw(data, skb);
			skb = NUWW;
		}
	}

	data->acw_skb = skb;
	spin_unwock_iwqwestowe(&data->wxwock, fwags);

	wetuwn eww;
}

static boow btusb_vawidate_sco_handwe(stwuct hci_dev *hdev,
				      stwuct hci_sco_hdw *hdw)
{
	__u16 handwe;

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW))
		// Can't vawidate, usewspace contwows evewything.
		wetuwn twue;

	/*
	 * USB isochwonous twansfews awe not designed to be wewiabwe and may
	 * wose fwagments.  When this happens, the next fiwst fwagment
	 * encountewed might actuawwy be a continuation fwagment.
	 * Vawidate the handwe to detect it and dwop it, ow ewse the uppew
	 * wayew wiww get gawbage fow a whiwe.
	 */

	handwe = hci_handwe(__we16_to_cpu(hdw->handwe));

	switch (hci_conn_wookup_type(hdev, handwe)) {
	case SCO_WINK:
	case ESCO_WINK:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int btusb_wecv_isoc(stwuct btusb_data *data, void *buffew, int count)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&data->wxwock, fwags);
	skb = data->sco_skb;

	whiwe (count) {
		int wen;

		if (!skb) {
			skb = bt_skb_awwoc(HCI_MAX_SCO_SIZE, GFP_ATOMIC);
			if (!skb) {
				eww = -ENOMEM;
				bweak;
			}

			hci_skb_pkt_type(skb) = HCI_SCODATA_PKT;
			hci_skb_expect(skb) = HCI_SCO_HDW_SIZE;
		}

		wen = min_t(uint, hci_skb_expect(skb), count);
		skb_put_data(skb, buffew, wen);

		count -= wen;
		buffew += wen;
		hci_skb_expect(skb) -= wen;

		if (skb->wen == HCI_SCO_HDW_SIZE) {
			/* Compwete SCO headew */
			stwuct hci_sco_hdw *hdw = hci_sco_hdw(skb);

			hci_skb_expect(skb) = hdw->dwen;

			if (skb_taiwwoom(skb) < hci_skb_expect(skb) ||
			    !btusb_vawidate_sco_handwe(data->hdev, hdw)) {
				kfwee_skb(skb);
				skb = NUWW;

				eww = -EIWSEQ;
				bweak;
			}
		}

		if (!hci_skb_expect(skb)) {
			/* Compwete fwame */
			hci_wecv_fwame(data->hdev, skb);
			skb = NUWW;
		}
	}

	data->sco_skb = skb;
	spin_unwock_iwqwestowe(&data->wxwock, fwags);

	wetuwn eww;
}

static void btusb_intw_compwete(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn;

	if (uwb->status == 0) {
		hdev->stat.byte_wx += uwb->actuaw_wength;

		if (btusb_wecv_intw(data, uwb->twansfew_buffew,
				    uwb->actuaw_wength) < 0) {
			bt_dev_eww(hdev, "cowwupted event packet");
			hdev->stat.eww_wx++;
		}
	} ewse if (uwb->status == -ENOENT) {
		/* Avoid suspend faiwed when usb_kiww_uwb */
		wetuwn;
	}

	if (!test_bit(BTUSB_INTW_WUNNING, &data->fwags))
		wetuwn;

	usb_mawk_wast_busy(data->udev);
	usb_anchow_uwb(uwb, &data->intw_anchow);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)",
				   uwb, -eww);
		if (eww != -EPEWM)
			hci_cmd_sync_cancew(hdev, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static int btusb_submit_intw_uwb(stwuct hci_dev *hdev, gfp_t mem_fwags)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size;

	BT_DBG("%s", hdev->name);

	if (!data->intw_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(0, mem_fwags);
	if (!uwb)
		wetuwn -ENOMEM;

	size = we16_to_cpu(data->intw_ep->wMaxPacketSize);

	buf = kmawwoc(size, mem_fwags);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvintpipe(data->udev, data->intw_ep->bEndpointAddwess);

	usb_fiww_int_uwb(uwb, data->udev, pipe, buf, size,
			 btusb_intw_compwete, hdev, data->intw_ep->bIntewvaw);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &data->intw_anchow);

	eww = usb_submit_uwb(uwb, mem_fwags);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		if (eww != -EPEWM)
			hci_cmd_sync_cancew(hdev, -eww);
		usb_unanchow_uwb(uwb);
	}

	/* Onwy initiawize intw_intewvaw if UWB poww sync is enabwed */
	if (!data->poww_sync)
		goto done;

	/* The units awe fwames (miwwiseconds) fow fuww and wow speed devices,
	 * and micwofwames (1/8 miwwisecond) fow highspeed and SupewSpeed
	 * devices.
	 *
	 * This is done once on open/wesume so it shouwdn't change even if
	 * fowce_poww_sync changes.
	 */
	switch (uwb->dev->speed) {
	case USB_SPEED_SUPEW_PWUS:
	case USB_SPEED_SUPEW:	/* units awe 125us */
		data->intw_intewvaw = usecs_to_jiffies(uwb->intewvaw * 125);
		bweak;
	defauwt:
		data->intw_intewvaw = msecs_to_jiffies(uwb->intewvaw);
		bweak;
	}

done:
	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void btusb_buwk_compwete(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn;

	if (uwb->status == 0) {
		hdev->stat.byte_wx += uwb->actuaw_wength;

		if (data->wecv_buwk(data, uwb->twansfew_buffew,
				    uwb->actuaw_wength) < 0) {
			bt_dev_eww(hdev, "cowwupted ACW packet");
			hdev->stat.eww_wx++;
		}
	} ewse if (uwb->status == -ENOENT) {
		/* Avoid suspend faiwed when usb_kiww_uwb */
		wetuwn;
	}

	if (!test_bit(BTUSB_BUWK_WUNNING, &data->fwags))
		wetuwn;

	usb_anchow_uwb(uwb, &data->buwk_anchow);
	usb_mawk_wast_busy(data->udev);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static int btusb_submit_buwk_uwb(stwuct hci_dev *hdev, gfp_t mem_fwags)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size = HCI_MAX_FWAME_SIZE;

	BT_DBG("%s", hdev->name);

	if (!data->buwk_wx_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(0, mem_fwags);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = kmawwoc(size, mem_fwags);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvbuwkpipe(data->udev, data->buwk_wx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe, buf, size,
			  btusb_buwk_compwete, hdev);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_mawk_wast_busy(data->udev);
	usb_anchow_uwb(uwb, &data->buwk_anchow);

	eww = usb_submit_uwb(uwb, mem_fwags);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void btusb_isoc_compwete(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int i, eww;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn;

	if (uwb->status == 0) {
		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			unsigned int offset = uwb->iso_fwame_desc[i].offset;
			unsigned int wength = uwb->iso_fwame_desc[i].actuaw_wength;

			if (uwb->iso_fwame_desc[i].status)
				continue;

			hdev->stat.byte_wx += wength;

			if (btusb_wecv_isoc(data, uwb->twansfew_buffew + offset,
					    wength) < 0) {
				bt_dev_eww(hdev, "cowwupted SCO packet");
				hdev->stat.eww_wx++;
			}
		}
	} ewse if (uwb->status == -ENOENT) {
		/* Avoid suspend faiwed when usb_kiww_uwb */
		wetuwn;
	}

	if (!test_bit(BTUSB_ISOC_WUNNING, &data->fwags))
		wetuwn;

	usb_anchow_uwb(uwb, &data->isoc_anchow);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static inwine void __fiww_isoc_descwiptow_msbc(stwuct uwb *uwb, int wen,
					       int mtu, stwuct btusb_data *data)
{
	int i = 0, offset = 0;
	unsigned int intewvaw;

	BT_DBG("wen %d mtu %d", wen, mtu);

	/* Fow mSBC AWT 6 settings some chips need to twansmit the data
	 * continuouswy without the zewo wength of USB packets.
	 */
	if (test_bit(BTUSB_AWT6_CONTINUOUS_TX, &data->fwags))
		goto ignowe_usb_awt6_packet_fwow;

	/* Fow mSBC AWT 6 setting the host wiww send the packet at continuous
	 * fwow. As pew cowe spec 5, vow 4, pawt B, tabwe 2.1. Fow AWT setting
	 * 6 the HCI PACKET INTEWVAW shouwd be 7.5ms fow evewy usb packets.
	 * To maintain the wate we send 63bytes of usb packets awtewnativewy fow
	 * 7ms and 8ms to maintain the wate as 7.5ms.
	 */
	if (data->usb_awt6_packet_fwow) {
		intewvaw = 7;
		data->usb_awt6_packet_fwow = fawse;
	} ewse {
		intewvaw = 6;
		data->usb_awt6_packet_fwow = twue;
	}

	fow (i = 0; i < intewvaw; i++) {
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength = offset;
	}

ignowe_usb_awt6_packet_fwow:
	if (wen && i < BTUSB_MAX_ISOC_FWAMES) {
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength = wen;
		i++;
	}

	uwb->numbew_of_packets = i;
}

static inwine void __fiww_isoc_descwiptow(stwuct uwb *uwb, int wen, int mtu)
{
	int i, offset = 0;

	BT_DBG("wen %d mtu %d", wen, mtu);

	fow (i = 0; i < BTUSB_MAX_ISOC_FWAMES && wen >= mtu;
					i++, offset += mtu, wen -= mtu) {
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength = mtu;
	}

	if (wen && i < BTUSB_MAX_ISOC_FWAMES) {
		uwb->iso_fwame_desc[i].offset = offset;
		uwb->iso_fwame_desc[i].wength = wen;
		i++;
	}

	uwb->numbew_of_packets = i;
}

static int btusb_submit_isoc_uwb(stwuct hci_dev *hdev, gfp_t mem_fwags)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size;

	BT_DBG("%s", hdev->name);

	if (!data->isoc_wx_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(BTUSB_MAX_ISOC_FWAMES, mem_fwags);
	if (!uwb)
		wetuwn -ENOMEM;

	size = we16_to_cpu(data->isoc_wx_ep->wMaxPacketSize) *
						BTUSB_MAX_ISOC_FWAMES;

	buf = kmawwoc(size, mem_fwags);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvisocpipe(data->udev, data->isoc_wx_ep->bEndpointAddwess);

	usb_fiww_int_uwb(uwb, data->udev, pipe, buf, size, btusb_isoc_compwete,
			 hdev, data->isoc_wx_ep->bIntewvaw);

	uwb->twansfew_fwags = UWB_FWEE_BUFFEW | UWB_ISO_ASAP;

	__fiww_isoc_descwiptow(uwb, size,
			       we16_to_cpu(data->isoc_wx_ep->wMaxPacketSize));

	usb_anchow_uwb(uwb, &data->isoc_anchow);

	eww = usb_submit_uwb(uwb, mem_fwags);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void btusb_diag_compwete(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (uwb->status == 0) {
		stwuct sk_buff *skb;

		skb = bt_skb_awwoc(uwb->actuaw_wength, GFP_ATOMIC);
		if (skb) {
			skb_put_data(skb, uwb->twansfew_buffew,
				     uwb->actuaw_wength);
			hci_wecv_diag(hdev, skb);
		}
	} ewse if (uwb->status == -ENOENT) {
		/* Avoid suspend faiwed when usb_kiww_uwb */
		wetuwn;
	}

	if (!test_bit(BTUSB_DIAG_WUNNING, &data->fwags))
		wetuwn;

	usb_anchow_uwb(uwb, &data->diag_anchow);
	usb_mawk_wast_busy(data->udev);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static int btusb_submit_diag_uwb(stwuct hci_dev *hdev, gfp_t mem_fwags)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned chaw *buf;
	unsigned int pipe;
	int eww, size = HCI_MAX_FWAME_SIZE;

	BT_DBG("%s", hdev->name);

	if (!data->diag_wx_ep)
		wetuwn -ENODEV;

	uwb = usb_awwoc_uwb(0, mem_fwags);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = kmawwoc(size, mem_fwags);
	if (!buf) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvbuwkpipe(data->udev, data->diag_wx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe, buf, size,
			  btusb_diag_compwete, hdev);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_mawk_wast_busy(data->udev);
	usb_anchow_uwb(uwb, &data->diag_anchow);

	eww = usb_submit_uwb(uwb, mem_fwags);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static void btusb_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct hci_dev *hdev = (stwuct hci_dev *)skb->dev;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	unsigned wong fwags;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		goto done;

	if (!uwb->status) {
		hdev->stat.byte_tx += uwb->twansfew_buffew_wength;
	} ewse {
		if (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT)
			hci_cmd_sync_cancew(hdev, -uwb->status);
		hdev->stat.eww_tx++;
	}

done:
	spin_wock_iwqsave(&data->txwock, fwags);
	data->tx_in_fwight--;
	spin_unwock_iwqwestowe(&data->txwock, fwags);

	kfwee(uwb->setup_packet);

	kfwee_skb(skb);
}

static void btusb_isoc_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct hci_dev *hdev = (stwuct hci_dev *)skb->dev;

	BT_DBG("%s uwb %p status %d count %d", hdev->name, uwb, uwb->status,
	       uwb->actuaw_wength);

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		goto done;

	if (!uwb->status)
		hdev->stat.byte_tx += uwb->twansfew_buffew_wength;
	ewse
		hdev->stat.eww_tx++;

done:
	kfwee(uwb->setup_packet);

	kfwee_skb(skb);
}

static int btusb_open(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s", hdev->name);

	eww = usb_autopm_get_intewface(data->intf);
	if (eww < 0)
		wetuwn eww;

	/* Patching USB fiwmwawe fiwes pwiow to stawting any UWBs of HCI path
	 * It is mowe safe to use USB buwk channew fow downwoading USB patch
	 */
	if (data->setup_on_usb) {
		eww = data->setup_on_usb(hdev);
		if (eww < 0)
			goto setup_faiw;
	}

	data->intf->needs_wemote_wakeup = 1;

	if (test_and_set_bit(BTUSB_INTW_WUNNING, &data->fwags))
		goto done;

	eww = btusb_submit_intw_uwb(hdev, GFP_KEWNEW);
	if (eww < 0)
		goto faiwed;

	eww = btusb_submit_buwk_uwb(hdev, GFP_KEWNEW);
	if (eww < 0) {
		usb_kiww_anchowed_uwbs(&data->intw_anchow);
		goto faiwed;
	}

	set_bit(BTUSB_BUWK_WUNNING, &data->fwags);
	btusb_submit_buwk_uwb(hdev, GFP_KEWNEW);

	if (data->diag) {
		if (!btusb_submit_diag_uwb(hdev, GFP_KEWNEW))
			set_bit(BTUSB_DIAG_WUNNING, &data->fwags);
	}

done:
	usb_autopm_put_intewface(data->intf);
	wetuwn 0;

faiwed:
	cweaw_bit(BTUSB_INTW_WUNNING, &data->fwags);
setup_faiw:
	usb_autopm_put_intewface(data->intf);
	wetuwn eww;
}

static void btusb_stop_twaffic(stwuct btusb_data *data)
{
	usb_kiww_anchowed_uwbs(&data->intw_anchow);
	usb_kiww_anchowed_uwbs(&data->buwk_anchow);
	usb_kiww_anchowed_uwbs(&data->isoc_anchow);
	usb_kiww_anchowed_uwbs(&data->diag_anchow);
	usb_kiww_anchowed_uwbs(&data->ctww_anchow);
}

static int btusb_cwose(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s", hdev->name);

	cancew_dewayed_wowk(&data->wx_wowk);
	cancew_wowk_sync(&data->wowk);
	cancew_wowk_sync(&data->wakew);

	skb_queue_puwge(&data->acw_q);

	cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags);
	cweaw_bit(BTUSB_BUWK_WUNNING, &data->fwags);
	cweaw_bit(BTUSB_INTW_WUNNING, &data->fwags);
	cweaw_bit(BTUSB_DIAG_WUNNING, &data->fwags);

	btusb_stop_twaffic(data);
	btusb_fwee_fwags(data);

	eww = usb_autopm_get_intewface(data->intf);
	if (eww < 0)
		goto faiwed;

	data->intf->needs_wemote_wakeup = 0;

	/* Enabwe wemote wake up fow auto-suspend */
	if (test_bit(BTUSB_WAKEUP_AUTOSUSPEND, &data->fwags))
		data->intf->needs_wemote_wakeup = 1;

	usb_autopm_put_intewface(data->intf);

faiwed:
	usb_scuttwe_anchowed_uwbs(&data->defewwed);
	wetuwn 0;
}

static int btusb_fwush(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	cancew_dewayed_wowk(&data->wx_wowk);

	skb_queue_puwge(&data->acw_q);

	usb_kiww_anchowed_uwbs(&data->tx_anchow);
	btusb_fwee_fwags(data);

	wetuwn 0;
}

static stwuct uwb *awwoc_ctww_uwb(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct usb_ctwwwequest *dw;
	stwuct uwb *uwb;
	unsigned int pipe;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn EWW_PTW(-ENOMEM);

	dw = kmawwoc(sizeof(*dw), GFP_KEWNEW);
	if (!dw) {
		usb_fwee_uwb(uwb);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dw->bWequestType = data->cmdweq_type;
	dw->bWequest     = data->cmdweq;
	dw->wIndex       = 0;
	dw->wVawue       = 0;
	dw->wWength      = __cpu_to_we16(skb->wen);

	pipe = usb_sndctwwpipe(data->udev, 0x00);

	usb_fiww_contwow_uwb(uwb, data->udev, pipe, (void *)dw,
			     skb->data, skb->wen, btusb_tx_compwete, skb);

	skb->dev = (void *)hdev;

	wetuwn uwb;
}

static stwuct uwb *awwoc_buwk_uwb(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned int pipe;

	if (!data->buwk_tx_ep)
		wetuwn EWW_PTW(-ENODEV);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn EWW_PTW(-ENOMEM);

	pipe = usb_sndbuwkpipe(data->udev, data->buwk_tx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe,
			  skb->data, skb->wen, btusb_tx_compwete, skb);

	skb->dev = (void *)hdev;

	wetuwn uwb;
}

static stwuct uwb *awwoc_isoc_uwb(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;
	unsigned int pipe;

	if (!data->isoc_tx_ep)
		wetuwn EWW_PTW(-ENODEV);

	uwb = usb_awwoc_uwb(BTUSB_MAX_ISOC_FWAMES, GFP_KEWNEW);
	if (!uwb)
		wetuwn EWW_PTW(-ENOMEM);

	pipe = usb_sndisocpipe(data->udev, data->isoc_tx_ep->bEndpointAddwess);

	usb_fiww_int_uwb(uwb, data->udev, pipe,
			 skb->data, skb->wen, btusb_isoc_tx_compwete,
			 skb, data->isoc_tx_ep->bIntewvaw);

	uwb->twansfew_fwags  = UWB_ISO_ASAP;

	if (data->isoc_awtsetting == 6)
		__fiww_isoc_descwiptow_msbc(uwb, skb->wen,
					    we16_to_cpu(data->isoc_tx_ep->wMaxPacketSize),
					    data);
	ewse
		__fiww_isoc_descwiptow(uwb, skb->wen,
				       we16_to_cpu(data->isoc_tx_ep->wMaxPacketSize));
	skb->dev = (void *)hdev;

	wetuwn uwb;
}

static int submit_tx_uwb(stwuct hci_dev *hdev, stwuct uwb *uwb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	usb_anchow_uwb(uwb, &data->tx_anchow);

	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		kfwee(uwb->setup_packet);
		usb_unanchow_uwb(uwb);
	} ewse {
		usb_mawk_wast_busy(data->udev);
	}

	usb_fwee_uwb(uwb);
	wetuwn eww;
}

static int submit_ow_queue_tx_uwb(stwuct hci_dev *hdev, stwuct uwb *uwb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	unsigned wong fwags;
	boow suspending;

	spin_wock_iwqsave(&data->txwock, fwags);
	suspending = test_bit(BTUSB_SUSPENDING, &data->fwags);
	if (!suspending)
		data->tx_in_fwight++;
	spin_unwock_iwqwestowe(&data->txwock, fwags);

	if (!suspending)
		wetuwn submit_tx_uwb(hdev, uwb);

	usb_anchow_uwb(uwb, &data->defewwed);
	scheduwe_wowk(&data->wakew);

	usb_fwee_uwb(uwb);
	wetuwn 0;
}

static int btusb_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct uwb *uwb;

	BT_DBG("%s", hdev->name);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		uwb = awwoc_ctww_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.cmd_tx++;
		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);

	case HCI_ACWDATA_PKT:
		uwb = awwoc_buwk_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.acw_tx++;
		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);

	case HCI_SCODATA_PKT:
		if (hci_conn_num(hdev, SCO_WINK) < 1)
			wetuwn -ENODEV;

		uwb = awwoc_isoc_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.sco_tx++;
		wetuwn submit_tx_uwb(hdev, uwb);

	case HCI_ISODATA_PKT:
		uwb = awwoc_buwk_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);
	}

	wetuwn -EIWSEQ;
}

static void btusb_notify(stwuct hci_dev *hdev, unsigned int evt)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s evt %d", hdev->name, evt);

	if (hci_conn_num(hdev, SCO_WINK) != data->sco_num) {
		data->sco_num = hci_conn_num(hdev, SCO_WINK);
		data->aiw_mode = evt;
		scheduwe_wowk(&data->wowk);
	}
}

static inwine int __set_isoc_intewface(stwuct hci_dev *hdev, int awtsetting)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct usb_intewface *intf = data->isoc;
	stwuct usb_endpoint_descwiptow *ep_desc;
	int i, eww;

	if (!data->isoc)
		wetuwn -ENODEV;

	eww = usb_set_intewface(data->udev, data->isoc_ifnum, awtsetting);
	if (eww < 0) {
		bt_dev_eww(hdev, "setting intewface faiwed (%d)", -eww);
		wetuwn eww;
	}

	data->isoc_awtsetting = awtsetting;

	data->isoc_tx_ep = NUWW;
	data->isoc_wx_ep = NUWW;

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		ep_desc = &intf->cuw_awtsetting->endpoint[i].desc;

		if (!data->isoc_tx_ep && usb_endpoint_is_isoc_out(ep_desc)) {
			data->isoc_tx_ep = ep_desc;
			continue;
		}

		if (!data->isoc_wx_ep && usb_endpoint_is_isoc_in(ep_desc)) {
			data->isoc_wx_ep = ep_desc;
			continue;
		}
	}

	if (!data->isoc_tx_ep || !data->isoc_wx_ep) {
		bt_dev_eww(hdev, "invawid SCO descwiptows");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int btusb_switch_awt_setting(stwuct hci_dev *hdev, int new_awts)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int eww;

	if (data->isoc_awtsetting != new_awts) {
		unsigned wong fwags;

		cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags);
		usb_kiww_anchowed_uwbs(&data->isoc_anchow);

		/* When isochwonous awtewnate setting needs to be
		 * changed, because SCO connection has been added
		 * ow wemoved, a packet fwagment may be weft in the
		 * weassembwing state. This couwd wead to wwongwy
		 * assembwed fwagments.
		 *
		 * Cweaw outstanding fwagment when sewecting a new
		 * awtewnate setting.
		 */
		spin_wock_iwqsave(&data->wxwock, fwags);
		dev_kfwee_skb_iwq(data->sco_skb);
		data->sco_skb = NUWW;
		spin_unwock_iwqwestowe(&data->wxwock, fwags);

		eww = __set_isoc_intewface(hdev, new_awts);
		if (eww < 0)
			wetuwn eww;
	}

	if (!test_and_set_bit(BTUSB_ISOC_WUNNING, &data->fwags)) {
		if (btusb_submit_isoc_uwb(hdev, GFP_KEWNEW) < 0)
			cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags);
		ewse
			btusb_submit_isoc_uwb(hdev, GFP_KEWNEW);
	}

	wetuwn 0;
}

static stwuct usb_host_intewface *btusb_find_awtsetting(stwuct btusb_data *data,
							int awt)
{
	stwuct usb_intewface *intf = data->isoc;
	int i;

	BT_DBG("Wooking fow Awt no :%d", awt);

	if (!intf)
		wetuwn NUWW;

	fow (i = 0; i < intf->num_awtsetting; i++) {
		if (intf->awtsetting[i].desc.bAwtewnateSetting == awt)
			wetuwn &intf->awtsetting[i];
	}

	wetuwn NUWW;
}

static void btusb_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btusb_data *data = containew_of(wowk, stwuct btusb_data, wowk);
	stwuct hci_dev *hdev = data->hdev;
	int new_awts = 0;
	int eww;

	if (data->sco_num > 0) {
		if (!test_bit(BTUSB_DID_ISO_WESUME, &data->fwags)) {
			eww = usb_autopm_get_intewface(data->isoc ? data->isoc : data->intf);
			if (eww < 0) {
				cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags);
				usb_kiww_anchowed_uwbs(&data->isoc_anchow);
				wetuwn;
			}

			set_bit(BTUSB_DID_ISO_WESUME, &data->fwags);
		}

		if (data->aiw_mode == HCI_NOTIFY_ENABWE_SCO_CVSD) {
			if (hdev->voice_setting & 0x0020) {
				static const int awts[3] = { 2, 4, 5 };

				new_awts = awts[data->sco_num - 1];
			} ewse {
				new_awts = data->sco_num;
			}
		} ewse if (data->aiw_mode == HCI_NOTIFY_ENABWE_SCO_TWANSP) {
			/* Bwuetooth USB spec wecommends awt 6 (63 bytes), but
			 * many adaptews do not suppowt it.  Awt 1 appeaws to
			 * wowk fow aww adaptews that do not have awt 6, and
			 * which wowk with WBS at aww.  Some devices pwefew
			 * awt 3 (HCI paywoad >= 60 Bytes wet aiw packet
			 * data satisfy 60 bytes), wequiwing
			 * MTU >= 3 (packets) * 25 (size) - 3 (headews) = 72
			 * see awso Cowe spec 5, vow 4, B 2.1.1 & Tabwe 2.1.
			 */
			if (btusb_find_awtsetting(data, 6))
				new_awts = 6;
			ewse if (btusb_find_awtsetting(data, 3) &&
				 hdev->sco_mtu >= 72 &&
				 test_bit(BTUSB_USE_AWT3_FOW_WBS, &data->fwags))
				new_awts = 3;
			ewse
				new_awts = 1;
		}

		if (btusb_switch_awt_setting(hdev, new_awts) < 0)
			bt_dev_eww(hdev, "set USB awt:(%d) faiwed!", new_awts);
	} ewse {
		usb_kiww_anchowed_uwbs(&data->isoc_anchow);

		if (test_and_cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags))
			__set_isoc_intewface(hdev, 0);

		if (test_and_cweaw_bit(BTUSB_DID_ISO_WESUME, &data->fwags))
			usb_autopm_put_intewface(data->isoc ? data->isoc : data->intf);
	}
}

static void btusb_wakew(stwuct wowk_stwuct *wowk)
{
	stwuct btusb_data *data = containew_of(wowk, stwuct btusb_data, wakew);
	int eww;

	eww = usb_autopm_get_intewface(data->intf);
	if (eww < 0)
		wetuwn;

	usb_autopm_put_intewface(data->intf);
}

static void btusb_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btusb_data *data = containew_of(wowk, stwuct btusb_data,
					       wx_wowk.wowk);
	stwuct sk_buff *skb;

	/* Dequeue ACW data weceived duwing the intewvaw */
	whiwe ((skb = skb_dequeue(&data->acw_q)))
		data->wecv_acw(data->hdev, skb);
}

static int btusb_setup_bcm92035(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	u8 vaw = 0x00;

	BT_DBG("%s", hdev->name);

	skb = __hci_cmd_sync(hdev, 0xfc3b, 1, &vaw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		bt_dev_eww(hdev, "BCM92035 command faiwed (%wd)", PTW_EWW(skb));
	ewse
		kfwee_skb(skb);

	wetuwn 0;
}

static int btusb_setup_csw(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	u16 bcdDevice = we16_to_cpu(data->udev->descwiptow.bcdDevice);
	stwuct hci_wp_wead_wocaw_vewsion *wp;
	stwuct sk_buff *skb;
	boow is_fake = fawse;
	int wet;

	BT_DBG("%s", hdev->name);

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "CSW: Wocaw vewsion faiwed (%d)", eww);
		wetuwn eww;
	}

	wp = skb_puww_data(skb, sizeof(*wp));
	if (!wp) {
		bt_dev_eww(hdev, "CSW: Wocaw vewsion wength mismatch");
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	bt_dev_info(hdev, "CSW: Setting up dongwe with HCI vew=%u wev=%04x",
		    wp->hci_vew, we16_to_cpu(wp->hci_wev));

	bt_dev_info(hdev, "WMP vew=%u subvew=%04x; manufactuwew=%u",
		    wp->wmp_vew, we16_to_cpu(wp->wmp_subvew),
		    we16_to_cpu(wp->manufactuwew));

	/* Detect a wide host of Chinese contwowwews that awen't CSW.
	 *
	 * Known fake bcdDevices: 0x0100, 0x0134, 0x1915, 0x2520, 0x7558, 0x8891
	 *
	 * The main thing they have in common is that these awe weawwy popuwaw wow-cost
	 * options that suppowt newew Bwuetooth vewsions but wewy on heavy VID/PID
	 * squatting of this poow owd Bwuetooth 1.1 device. Even sowd as such.
	 *
	 * We detect actuaw CSW devices by checking that the HCI manufactuwew code
	 * is Cambwidge Siwicon Wadio (10) and ensuwing that WMP sub-vewsion and
	 * HCI wev vawues awways match. As they both stowe the fiwmwawe numbew.
	 */
	if (we16_to_cpu(wp->manufactuwew) != 10 ||
	    we16_to_cpu(wp->hci_wev) != we16_to_cpu(wp->wmp_subvew))
		is_fake = twue;

	/* Known wegit CSW fiwmwawe buiwd numbews and theiw suppowted BT vewsions:
	 * - 1.1 (0x1) -> 0x0073, 0x020d, 0x033c, 0x034e
	 * - 1.2 (0x2) ->                 0x04d9, 0x0529
	 * - 2.0 (0x3) ->         0x07a6, 0x07ad, 0x0c5c
	 * - 2.1 (0x4) ->         0x149c, 0x1735, 0x1899 (0x1899 is a BwueCowe4-Extewnaw)
	 * - 4.0 (0x6) ->         0x1d86, 0x2031, 0x22bb
	 *
	 * e.g. Weaw CSW dongwes with WMP subvewsion 0x73 awe owd enough that
	 *      suppowt BT 1.1 onwy; so it's a dead giveaway when some
	 *      thiwd-pawty BT 4.0 dongwe weuses it.
	 */
	ewse if (we16_to_cpu(wp->wmp_subvew) <= 0x034e &&
		 wp->hci_vew > BWUETOOTH_VEW_1_1)
		is_fake = twue;

	ewse if (we16_to_cpu(wp->wmp_subvew) <= 0x0529 &&
		 wp->hci_vew > BWUETOOTH_VEW_1_2)
		is_fake = twue;

	ewse if (we16_to_cpu(wp->wmp_subvew) <= 0x0c5c &&
		 wp->hci_vew > BWUETOOTH_VEW_2_0)
		is_fake = twue;

	ewse if (we16_to_cpu(wp->wmp_subvew) <= 0x1899 &&
		 wp->hci_vew > BWUETOOTH_VEW_2_1)
		is_fake = twue;

	ewse if (we16_to_cpu(wp->wmp_subvew) <= 0x22bb &&
		 wp->hci_vew > BWUETOOTH_VEW_4_0)
		is_fake = twue;

	/* Othew cwones which beat aww the above checks */
	ewse if (bcdDevice == 0x0134 &&
		 we16_to_cpu(wp->wmp_subvew) == 0x0c5c &&
		 wp->hci_vew == BWUETOOTH_VEW_2_0)
		is_fake = twue;

	if (is_fake) {
		bt_dev_wawn(hdev, "CSW: Unbwanded CSW cwone detected; adding wowkawounds and fowce-suspending once...");

		/* Genewawwy these cwones have big discwepancies between
		 * advewtised featuwes and what's actuawwy suppowted.
		 * Pwobabwy wiww need to be expanded in the futuwe;
		 * without these the contwowwew wiww wock up.
		 */
		set_bit(HCI_QUIWK_BWOKEN_STOWED_WINK_KEY, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_EWW_DATA_WEPOWTING, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_FIWTEW_CWEAW_AWW, &hdev->quiwks);
		set_bit(HCI_QUIWK_NO_SUSPEND_NOTIFIEW, &hdev->quiwks);

		/* Cweaw the weset quiwk since this is not an actuaw
		 * eawwy Bwuetooth 1.1 device fwom CSW.
		 */
		cweaw_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);
		cweaw_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);

		/*
		 * Speciaw wowkawound fow these BT 4.0 chip cwones, and potentiawwy mowe:
		 *
		 * - 0x0134: a Bawwot 8041a02                 (HCI wev: 0x0810 sub: 0x1012)
		 * - 0x7558: IC mawkings FW3191AHAW 749H15143 (HCI wev/sub-vewsion: 0x0709)
		 *
		 * These contwowwews awe weawwy messed-up.
		 *
		 * 1. Theiw buwk WX endpoint wiww nevew wepowt any data unwess
		 *    the device was suspended at weast once (yes, weawwy).
		 * 2. They wiww not wakeup when autosuspended and weceiving data
		 *    on theiw buwk WX endpoint fwom e.g. a keyboawd ow mouse
		 *    (IOW wemote-wakeup suppowt is bwoken fow the buwk endpoint).
		 *
		 * To fix 1. enabwe wuntime-suspend, fowce-suspend the
		 * HCI and then wake-it up by disabwing wuntime-suspend.
		 *
		 * To fix 2. cweaw the HCI's can_wake fwag, this way the HCI
		 * wiww stiww be autosuspended when it is not open.
		 *
		 * --
		 *
		 * Because these awe widespwead pwobwems we pwefew genewic sowutions; so
		 * appwy this initiawization quiwk to evewy contwowwew that gets hewe,
		 * it shouwd be hawmwess. The awtewnative is to not wowk at aww.
		 */
		pm_wuntime_awwow(&data->udev->dev);

		wet = pm_wuntime_suspend(&data->udev->dev);
		if (wet >= 0)
			msweep(200);
		ewse
			bt_dev_wawn(hdev, "CSW: Couwdn't suspend the device fow ouw Bawwot 8041a02 weceive-issue wowkawound");

		pm_wuntime_fowbid(&data->udev->dev);

		device_set_wakeup_capabwe(&data->udev->dev, fawse);

		/* We-enabwe autosuspend if this was wequested */
		if (enabwe_autosuspend)
			usb_enabwe_autosuspend(data->udev);
	}

	kfwee_skb(skb);

	wetuwn 0;
}

static int inject_cmd_compwete(stwuct hci_dev *hdev, __u16 opcode)
{
	stwuct sk_buff *skb;
	stwuct hci_event_hdw *hdw;
	stwuct hci_ev_cmd_compwete *evt;

	skb = bt_skb_awwoc(sizeof(*hdw) + sizeof(*evt) + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(*hdw));
	hdw->evt = HCI_EV_CMD_COMPWETE;
	hdw->pwen = sizeof(*evt) + 1;

	evt = skb_put(skb, sizeof(*evt));
	evt->ncmd = 0x01;
	evt->opcode = cpu_to_we16(opcode);

	skb_put_u8(skb, 0x00);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	wetuwn hci_wecv_fwame(hdev, skb);
}

static int btusb_wecv_buwk_intew(stwuct btusb_data *data, void *buffew,
				 int count)
{
	stwuct hci_dev *hdev = data->hdev;

	/* When the device is in bootwoadew mode, then it can send
	 * events via the buwk endpoint. These events awe tweated the
	 * same way as the ones weceived fwom the intewwupt endpoint.
	 */
	if (btintew_test_fwag(hdev, INTEW_BOOTWOADEW))
		wetuwn btusb_wecv_intw(data, buffew, count);

	wetuwn btusb_wecv_buwk(data, buffew, count);
}

static int btusb_send_fwame_intew(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct uwb *uwb;

	BT_DBG("%s", hdev->name);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		if (btintew_test_fwag(hdev, INTEW_BOOTWOADEW)) {
			stwuct hci_command_hdw *cmd = (void *)skb->data;
			__u16 opcode = we16_to_cpu(cmd->opcode);

			/* When in bootwoadew mode and the command 0xfc09
			 * is weceived, it needs to be send down the
			 * buwk endpoint. So awwocate a buwk UWB instead.
			 */
			if (opcode == 0xfc09)
				uwb = awwoc_buwk_uwb(hdev, skb);
			ewse
				uwb = awwoc_ctww_uwb(hdev, skb);

			/* When the 0xfc01 command is issued to boot into
			 * the opewationaw fiwmwawe, it wiww actuawwy not
			 * send a command compwete event. To keep the fwow
			 * contwow wowking inject that event hewe.
			 */
			if (opcode == 0xfc01)
				inject_cmd_compwete(hdev, opcode);
		} ewse {
			uwb = awwoc_ctww_uwb(hdev, skb);
		}
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.cmd_tx++;
		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);

	case HCI_ACWDATA_PKT:
		uwb = awwoc_buwk_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.acw_tx++;
		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);

	case HCI_SCODATA_PKT:
		if (hci_conn_num(hdev, SCO_WINK) < 1)
			wetuwn -ENODEV;

		uwb = awwoc_isoc_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		hdev->stat.sco_tx++;
		wetuwn submit_tx_uwb(hdev, uwb);

	case HCI_ISODATA_PKT:
		uwb = awwoc_buwk_uwb(hdev, skb);
		if (IS_EWW(uwb))
			wetuwn PTW_EWW(uwb);

		wetuwn submit_ow_queue_tx_uwb(hdev, uwb);
	}

	wetuwn -EIWSEQ;
}

static int btusb_setup_weawtek(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	int wet;

	wet = btwtw_setup_weawtek(hdev);

	if (btweawtek_test_fwag(data->hdev, WEAWTEK_AWT6_CONTINUOUS_TX_CHIP))
		set_bit(BTUSB_AWT6_CONTINUOUS_TX, &data->fwags);

	wetuwn wet;
}

static int btusb_wecv_event_weawtek(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (skb->data[0] == HCI_VENDOW_PKT && skb->data[2] == WTK_SUB_EVENT_CODE_COWEDUMP) {
		stwuct wtk_dev_cowedump_hdw hdw = {
			.code = WTK_DEVCOWEDUMP_CODE_MEMDUMP,
		};

		bt_dev_dbg(hdev, "WTW: weceived cowedump vendow evt, wen %u",
			skb->wen);

		btusb_wtw_awwoc_devcowedump(hdev, &hdw, skb->data, skb->wen);
		kfwee_skb(skb);

		wetuwn 0;
	}

	wetuwn hci_wecv_fwame(hdev, skb);
}

/* UHW CW mapping */
#define MTK_BT_MISC		0x70002510
#define MTK_BT_SUBSYS_WST	0x70002610
#define MTK_UDMA_INT_STA_BT	0x74000024
#define MTK_UDMA_INT_STA_BT1	0x74000308
#define MTK_BT_WDT_STATUS	0x740003A0
#define MTK_EP_WST_OPT		0x74011890
#define MTK_EP_WST_IN_OUT_OPT	0x00010001
#define MTK_BT_WST_DONE		0x00000100
#define MTK_BT_WESET_WEG_CONNV3	0x70028610
#define MTK_BT_WEAD_DEV_ID	0x70010200


static void btusb_mtk_wmt_wecv(stwuct uwb *uwb)
{
	stwuct hci_dev *hdev = uwb->context;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct sk_buff *skb;
	int eww;

	if (uwb->status == 0 && uwb->actuaw_wength > 0) {
		hdev->stat.byte_wx += uwb->actuaw_wength;

		/* WMT event shouwdn't be fwagmented and the size shouwd be
		 * wess than HCI_WMT_MAX_EVENT_SIZE.
		 */
		skb = bt_skb_awwoc(HCI_WMT_MAX_EVENT_SIZE, GFP_ATOMIC);
		if (!skb) {
			hdev->stat.eww_wx++;
			kfwee(uwb->setup_packet);
			wetuwn;
		}

		hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
		skb_put_data(skb, uwb->twansfew_buffew, uwb->actuaw_wength);

		/* When someone waits fow the WMT event, the skb is being cwoned
		 * and being pwocessed the events fwom thewe then.
		 */
		if (test_bit(BTUSB_TX_WAIT_VND_EVT, &data->fwags)) {
			data->evt_skb = skb_cwone(skb, GFP_ATOMIC);
			if (!data->evt_skb) {
				kfwee_skb(skb);
				kfwee(uwb->setup_packet);
				wetuwn;
			}
		}

		eww = hci_wecv_fwame(hdev, skb);
		if (eww < 0) {
			kfwee_skb(data->evt_skb);
			data->evt_skb = NUWW;
			kfwee(uwb->setup_packet);
			wetuwn;
		}

		if (test_and_cweaw_bit(BTUSB_TX_WAIT_VND_EVT,
				       &data->fwags)) {
			/* Bawwiew to sync with othew CPUs */
			smp_mb__aftew_atomic();
			wake_up_bit(&data->fwags,
				    BTUSB_TX_WAIT_VND_EVT);
		}
		kfwee(uwb->setup_packet);
		wetuwn;
	} ewse if (uwb->status == -ENOENT) {
		/* Avoid suspend faiwed when usb_kiww_uwb */
		wetuwn;
	}

	usb_mawk_wast_busy(data->udev);

	/* The UWB compwete handwew is stiww cawwed with uwb->actuaw_wength = 0
	 * when the event is not avaiwabwe, so we shouwd keep we-submitting
	 * UWB untiw WMT event wetuwns, Awso, It's necessawy to wait some time
	 * between the two consecutive contwow UWBs to wewax the tawget device
	 * to genewate the event. Othewwise, the WMT event cannot wetuwn fwom
	 * the device successfuwwy.
	 */
	udeway(500);

	usb_anchow_uwb(uwb, &data->ctww_anchow);
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0) {
		kfwee(uwb->setup_packet);
		/* -EPEWM: uwb is being kiwwed;
		 * -ENODEV: device got disconnected
		 */
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p faiwed to wesubmit (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}
}

static int btusb_mtk_submit_wmt_wecv_uwb(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct usb_ctwwwequest *dw;
	unsigned chaw *buf;
	int eww, size = 64;
	unsigned int pipe;
	stwuct uwb *uwb;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	dw = kmawwoc(sizeof(*dw), GFP_KEWNEW);
	if (!dw) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	dw->bWequestType = USB_TYPE_VENDOW | USB_DIW_IN;
	dw->bWequest     = 1;
	dw->wIndex       = cpu_to_we16(0);
	dw->wVawue       = cpu_to_we16(48);
	dw->wWength      = cpu_to_we16(size);

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf) {
		kfwee(dw);
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	pipe = usb_wcvctwwpipe(data->udev, 0);

	usb_fiww_contwow_uwb(uwb, data->udev, pipe, (void *)dw,
			     buf, size, btusb_mtk_wmt_wecv, hdev);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	usb_anchow_uwb(uwb, &data->ctww_anchow);
	eww = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (eww < 0) {
		if (eww != -EPEWM && eww != -ENODEV)
			bt_dev_eww(hdev, "uwb %p submission faiwed (%d)",
				   uwb, -eww);
		usb_unanchow_uwb(uwb);
	}

	usb_fwee_uwb(uwb);

	wetuwn eww;
}

static int btusb_mtk_hci_wmt_sync(stwuct hci_dev *hdev,
				  stwuct btmtk_hci_wmt_pawams *wmt_pawams)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	u32 hwen, status = BTMTK_WMT_INVAWID;
	stwuct btmtk_hci_wmt_evt *wmt_evt;
	stwuct btmtk_hci_wmt_cmd *wc;
	stwuct btmtk_wmt_hdw *hdw;
	int eww;

	/* Send the WMT command and wait untiw the WMT event wetuwns */
	hwen = sizeof(*hdw) + wmt_pawams->dwen;
	if (hwen > 255)
		wetuwn -EINVAW;

	wc = kzawwoc(hwen, GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	hdw = &wc->hdw;
	hdw->diw = 1;
	hdw->op = wmt_pawams->op;
	hdw->dwen = cpu_to_we16(wmt_pawams->dwen + 1);
	hdw->fwag = wmt_pawams->fwag;
	memcpy(wc->data, wmt_pawams->data, wmt_pawams->dwen);

	set_bit(BTUSB_TX_WAIT_VND_EVT, &data->fwags);

	/* WMT cmd/event doesn't fowwow up the genewic HCI cmd/event handwing,
	 * it needs constantwy powwing contwow pipe untiw the host weceived the
	 * WMT event, thus, we shouwd wequiwe to specificawwy acquiwe PM countew
	 * on the USB to pwevent the intewface fwom entewing auto suspended
	 * whiwe WMT cmd/event in pwogwess.
	 */
	eww = usb_autopm_get_intewface(data->intf);
	if (eww < 0)
		goto eww_fwee_wc;

	eww = __hci_cmd_send(hdev, 0xfc6f, hwen, wc);

	if (eww < 0) {
		cweaw_bit(BTUSB_TX_WAIT_VND_EVT, &data->fwags);
		usb_autopm_put_intewface(data->intf);
		goto eww_fwee_wc;
	}

	/* Submit contwow IN UWB on demand to pwocess the WMT event */
	eww = btusb_mtk_submit_wmt_wecv_uwb(hdev);

	usb_autopm_put_intewface(data->intf);

	if (eww < 0)
		goto eww_fwee_wc;

	/* The vendow specific WMT commands awe aww answewed by a vendow
	 * specific event and wiww have the Command Status ow Command
	 * Compwete as with usuaw HCI command fwow contwow.
	 *
	 * Aftew sending the command, wait fow BTUSB_TX_WAIT_VND_EVT
	 * state to be cweawed. The dwivew specific event weceive woutine
	 * wiww cweaw that state and with that indicate compwetion of the
	 * WMT command.
	 */
	eww = wait_on_bit_timeout(&data->fwags, BTUSB_TX_WAIT_VND_EVT,
				  TASK_INTEWWUPTIBWE, HCI_INIT_TIMEOUT);
	if (eww == -EINTW) {
		bt_dev_eww(hdev, "Execution of wmt command intewwupted");
		cweaw_bit(BTUSB_TX_WAIT_VND_EVT, &data->fwags);
		goto eww_fwee_wc;
	}

	if (eww) {
		bt_dev_eww(hdev, "Execution of wmt command timed out");
		cweaw_bit(BTUSB_TX_WAIT_VND_EVT, &data->fwags);
		eww = -ETIMEDOUT;
		goto eww_fwee_wc;
	}

	if (data->evt_skb == NUWW)
		goto eww_fwee_wc;

	/* Pawse and handwe the wetuwn WMT event */
	wmt_evt = (stwuct btmtk_hci_wmt_evt *)data->evt_skb->data;
	if (wmt_evt->whdw.op != hdw->op) {
		bt_dev_eww(hdev, "Wwong op weceived %d expected %d",
			   wmt_evt->whdw.op, hdw->op);
		eww = -EIO;
		goto eww_fwee_skb;
	}

	switch (wmt_evt->whdw.op) {
	case BTMTK_WMT_SEMAPHOWE:
		if (wmt_evt->whdw.fwag == 2)
			status = BTMTK_WMT_PATCH_UNDONE;
		ewse
			status = BTMTK_WMT_PATCH_DONE;
		bweak;
	case BTMTK_WMT_FUNC_CTWW:
		wmt_evt_funcc = (stwuct btmtk_hci_wmt_evt_funcc *)wmt_evt;
		if (be16_to_cpu(wmt_evt_funcc->status) == 0x404)
			status = BTMTK_WMT_ON_DONE;
		ewse if (be16_to_cpu(wmt_evt_funcc->status) == 0x420)
			status = BTMTK_WMT_ON_PWOGWESS;
		ewse
			status = BTMTK_WMT_ON_UNDONE;
		bweak;
	case BTMTK_WMT_PATCH_DWNWD:
		if (wmt_evt->whdw.fwag == 2)
			status = BTMTK_WMT_PATCH_DONE;
		ewse if (wmt_evt->whdw.fwag == 1)
			status = BTMTK_WMT_PATCH_PWOGWESS;
		ewse
			status = BTMTK_WMT_PATCH_UNDONE;
		bweak;
	}

	if (wmt_pawams->status)
		*wmt_pawams->status = status;

eww_fwee_skb:
	kfwee_skb(data->evt_skb);
	data->evt_skb = NUWW;
eww_fwee_wc:
	kfwee(wc);
	wetuwn eww;
}

static int btusb_mtk_func_quewy(stwuct hci_dev *hdev)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	int status, eww;
	u8 pawam = 0;

	/* Quewy whethew the function is enabwed */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 4;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = &status;

	eww = btusb_mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to quewy function status (%d)", eww);
		wetuwn eww;
	}

	wetuwn status;
}

static int btusb_mtk_uhw_weg_wwite(stwuct btusb_data *data, u32 weg, u32 vaw)
{
	stwuct hci_dev *hdev = data->hdev;
	int pipe, eww;
	void *buf;

	buf = kzawwoc(4, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	put_unawigned_we32(vaw, buf);

	pipe = usb_sndctwwpipe(data->udev, 0);
	eww = usb_contwow_msg(data->udev, pipe, 0x02,
			      0x5E,
			      weg >> 16, weg & 0xffff,
			      buf, 4, USB_CTWW_SET_TIMEOUT);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to wwite uhw weg(%d)", eww);
		goto eww_fwee_buf;
	}

eww_fwee_buf:
	kfwee(buf);

	wetuwn eww;
}

static int btusb_mtk_uhw_weg_wead(stwuct btusb_data *data, u32 weg, u32 *vaw)
{
	stwuct hci_dev *hdev = data->hdev;
	int pipe, eww;
	void *buf;

	buf = kzawwoc(4, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pipe = usb_wcvctwwpipe(data->udev, 0);
	eww = usb_contwow_msg(data->udev, pipe, 0x01,
			      0xDE,
			      weg >> 16, weg & 0xffff,
			      buf, 4, USB_CTWW_SET_TIMEOUT);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to wead uhw weg(%d)", eww);
		goto eww_fwee_buf;
	}

	*vaw = get_unawigned_we32(buf);
	bt_dev_dbg(hdev, "weg=%x, vawue=0x%08x", weg, *vaw);

eww_fwee_buf:
	kfwee(buf);

	wetuwn eww;
}

static int btusb_mtk_weg_wead(stwuct btusb_data *data, u32 weg, u32 *vaw)
{
	int pipe, eww, size = sizeof(u32);
	void *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pipe = usb_wcvctwwpipe(data->udev, 0);
	eww = usb_contwow_msg(data->udev, pipe, 0x63,
			      USB_TYPE_VENDOW | USB_DIW_IN,
			      weg >> 16, weg & 0xffff,
			      buf, size, USB_CTWW_SET_TIMEOUT);
	if (eww < 0)
		goto eww_fwee_buf;

	*vaw = get_unawigned_we32(buf);

eww_fwee_buf:
	kfwee(buf);

	wetuwn eww;
}

static int btusb_mtk_id_get(stwuct btusb_data *data, u32 weg, u32 *id)
{
	wetuwn btusb_mtk_weg_wead(data, weg, id);
}

static u32 btusb_mtk_weset_done(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	u32 vaw = 0;

	btusb_mtk_uhw_weg_wead(data, MTK_BT_MISC, &vaw);

	wetuwn vaw & MTK_BT_WST_DONE;
}

static int btusb_mtk_weset(stwuct hci_dev *hdev, void *wst_data)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct btmediatek_data *mediatek;
	u32 vaw;
	int eww;

	/* It's MediaTek specific bwuetooth weset mechanism via USB */
	if (test_and_set_bit(BTUSB_HW_WESET_ACTIVE, &data->fwags)) {
		bt_dev_eww(hdev, "wast weset faiwed? Not wesetting again");
		wetuwn -EBUSY;
	}

	eww = usb_autopm_get_intewface(data->intf);
	if (eww < 0)
		wetuwn eww;

	btusb_stop_twaffic(data);
	usb_kiww_anchowed_uwbs(&data->tx_anchow);
	mediatek = hci_get_pwiv(hdev);

	if (mediatek->dev_id == 0x7925) {
		btusb_mtk_uhw_weg_wead(data, MTK_BT_WESET_WEG_CONNV3, &vaw);
		vaw |= (1 << 5);
		btusb_mtk_uhw_weg_wwite(data, MTK_BT_WESET_WEG_CONNV3, vaw);
		btusb_mtk_uhw_weg_wead(data, MTK_BT_WESET_WEG_CONNV3, &vaw);
		vaw &= 0xFFFF00FF;
		vaw |= (1 << 13);
		btusb_mtk_uhw_weg_wwite(data, MTK_BT_WESET_WEG_CONNV3, vaw);
		btusb_mtk_uhw_weg_wwite(data, MTK_EP_WST_OPT, 0x00010001);
		btusb_mtk_uhw_weg_wead(data, MTK_BT_WESET_WEG_CONNV3, &vaw);
		vaw |= (1 << 0);
		btusb_mtk_uhw_weg_wwite(data, MTK_BT_WESET_WEG_CONNV3, vaw);
		btusb_mtk_uhw_weg_wwite(data, MTK_UDMA_INT_STA_BT, 0x000000FF);
		btusb_mtk_uhw_weg_wead(data, MTK_UDMA_INT_STA_BT, &vaw);
		btusb_mtk_uhw_weg_wwite(data, MTK_UDMA_INT_STA_BT1, 0x000000FF);
		btusb_mtk_uhw_weg_wead(data, MTK_UDMA_INT_STA_BT1, &vaw);
		msweep(100);
	} ewse {
		/* It's Device EndPoint Weset Option Wegistew */
		bt_dev_dbg(hdev, "Initiating weset mechanism via uhw");
		btusb_mtk_uhw_weg_wwite(data, MTK_EP_WST_OPT, MTK_EP_WST_IN_OUT_OPT);
		btusb_mtk_uhw_weg_wead(data, MTK_BT_WDT_STATUS, &vaw);

		/* Weset the bwuetooth chip via USB intewface. */
		btusb_mtk_uhw_weg_wwite(data, MTK_BT_SUBSYS_WST, 1);
		btusb_mtk_uhw_weg_wwite(data, MTK_UDMA_INT_STA_BT, 0x000000FF);
		btusb_mtk_uhw_weg_wead(data, MTK_UDMA_INT_STA_BT, &vaw);
		btusb_mtk_uhw_weg_wwite(data, MTK_UDMA_INT_STA_BT1, 0x000000FF);
		btusb_mtk_uhw_weg_wead(data, MTK_UDMA_INT_STA_BT1, &vaw);
		/* MT7921 need to deway 20ms between toggwe weset bit */
		msweep(20);
		btusb_mtk_uhw_weg_wwite(data, MTK_BT_SUBSYS_WST, 0);
		btusb_mtk_uhw_weg_wead(data, MTK_BT_SUBSYS_WST, &vaw);
	}

	eww = weadx_poww_timeout(btusb_mtk_weset_done, hdev, vaw,
				 vaw & MTK_BT_WST_DONE, 20000, 1000000);
	if (eww < 0)
		bt_dev_eww(hdev, "Weset timeout");

	btusb_mtk_id_get(data, 0x70010200, &vaw);
	if (!vaw)
		bt_dev_eww(hdev, "Can't get device id, subsys weset faiw.");

	usb_queue_weset_device(data->intf);

	cweaw_bit(BTUSB_HW_WESET_ACTIVE, &data->fwags);

	wetuwn eww;
}

static int btusb_mtk_setup(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	ktime_t cawwtime, dewta, wettime;
	stwuct btmtk_tci_sweep tci_sweep;
	unsigned wong wong duwation;
	stwuct sk_buff *skb;
	const chaw *fwname;
	int eww, status;
	u32 dev_id = 0;
	chaw fw_bin_name[64];
	u32 fw_vewsion = 0;
	u8 pawam;
	stwuct btmediatek_data *mediatek;

	cawwtime = ktime_get();

	eww = btusb_mtk_id_get(data, 0x80000008, &dev_id);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to get device id (%d)", eww);
		wetuwn eww;
	}

	if (!dev_id || dev_id != 0x7663) {
		eww = btusb_mtk_id_get(data, 0x70010200, &dev_id);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to get device id (%d)", eww);
			wetuwn eww;
		}
		eww = btusb_mtk_id_get(data, 0x80021004, &fw_vewsion);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to get fw vewsion (%d)", eww);
			wetuwn eww;
		}
	}

	mediatek = hci_get_pwiv(hdev);
	mediatek->dev_id = dev_id;
	mediatek->weset_sync = btusb_mtk_weset;

	eww = btmtk_wegistew_cowedump(hdev, btusb_dwivew.name, fw_vewsion);
	if (eww < 0)
		bt_dev_eww(hdev, "Faiwed to wegistew cowedump (%d)", eww);

	switch (dev_id) {
	case 0x7663:
		fwname = FIWMWAWE_MT7663;
		bweak;
	case 0x7668:
		fwname = FIWMWAWE_MT7668;
		bweak;
	case 0x7922:
	case 0x7961:
	case 0x7925:
		if (dev_id == 0x7925)
			snpwintf(fw_bin_name, sizeof(fw_bin_name),
				 "mediatek/mt%04x/BT_WAM_CODE_MT%04x_1_%x_hdw.bin",
				 dev_id & 0xffff, dev_id & 0xffff, (fw_vewsion & 0xff) + 1);
		ewse
			snpwintf(fw_bin_name, sizeof(fw_bin_name),
				 "mediatek/BT_WAM_CODE_MT%04x_1_%x_hdw.bin",
				 dev_id & 0xffff, (fw_vewsion & 0xff) + 1);

		eww = btmtk_setup_fiwmwawe_79xx(hdev, fw_bin_name,
						btusb_mtk_hci_wmt_sync);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to set up fiwmwawe (%d)", eww);
			wetuwn eww;
		}

		/* It's Device EndPoint Weset Option Wegistew */
		btusb_mtk_uhw_weg_wwite(data, MTK_EP_WST_OPT, MTK_EP_WST_IN_OUT_OPT);

		/* Enabwe Bwuetooth pwotocow */
		pawam = 1;
		wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
		wmt_pawams.fwag = 0;
		wmt_pawams.dwen = sizeof(pawam);
		wmt_pawams.data = &pawam;
		wmt_pawams.status = NUWW;

		eww = btusb_mtk_hci_wmt_sync(hdev, &wmt_pawams);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
			wetuwn eww;
		}

		hci_set_msft_opcode(hdev, 0xFD30);
		hci_set_aosp_capabwe(hdev);
		goto done;
	defauwt:
		bt_dev_eww(hdev, "Unsuppowted hawdwawe vawiant (%08x)",
			   dev_id);
		wetuwn -ENODEV;
	}

	/* Quewy whethew the fiwmwawe is awweady downwoad */
	wmt_pawams.op = BTMTK_WMT_SEMAPHOWE;
	wmt_pawams.fwag = 1;
	wmt_pawams.dwen = 0;
	wmt_pawams.data = NUWW;
	wmt_pawams.status = &status;

	eww = btusb_mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to quewy fiwmwawe status (%d)", eww);
		wetuwn eww;
	}

	if (status == BTMTK_WMT_PATCH_DONE) {
		bt_dev_info(hdev, "fiwmwawe awweady downwoaded");
		goto ignowe_setup_fw;
	}

	/* Setup a fiwmwawe which the device definitewy wequiwes */
	eww = btmtk_setup_fiwmwawe(hdev, fwname,
				   btusb_mtk_hci_wmt_sync);
	if (eww < 0)
		wetuwn eww;

ignowe_setup_fw:
	eww = weadx_poww_timeout(btusb_mtk_func_quewy, hdev, status,
				 status < 0 || status != BTMTK_WMT_ON_PWOGWESS,
				 2000, 5000000);
	/* -ETIMEDOUT happens */
	if (eww < 0)
		wetuwn eww;

	/* The othew ewwows happen in btusb_mtk_func_quewy */
	if (status < 0)
		wetuwn status;

	if (status == BTMTK_WMT_ON_DONE) {
		bt_dev_info(hdev, "function awweady on");
		goto ignowe_func_on;
	}

	/* Enabwe Bwuetooth pwotocow */
	pawam = 1;
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 0;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = btusb_mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
		wetuwn eww;
	}

ignowe_func_on:
	/* Appwy the wow powew enviwonment setup */
	tci_sweep.mode = 0x5;
	tci_sweep.duwation = cpu_to_we16(0x640);
	tci_sweep.host_duwation = cpu_to_we16(0x640);
	tci_sweep.host_wakeup_pin = 0;
	tci_sweep.time_compensation = 0;

	skb = __hci_cmd_sync(hdev, 0xfc7a, sizeof(tci_sweep), &tci_sweep,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Faiwed to appwy wow powew setting (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

done:
	wettime = ktime_get();
	dewta = ktime_sub(wettime, cawwtime);
	duwation = (unsigned wong wong)ktime_to_ns(dewta) >> 10;

	bt_dev_info(hdev, "Device setup in %wwu usecs", duwation);

	wetuwn 0;
}

static int btusb_mtk_shutdown(stwuct hci_dev *hdev)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	u8 pawam = 0;
	int eww;

	/* Disabwe the device */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 0;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = btusb_mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int btusb_wecv_acw_mtk(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	u16 handwe = we16_to_cpu(hci_acw_hdw(skb)->handwe);
	stwuct sk_buff *skb_cd;

	switch (handwe) {
	case 0xfc6f:		/* Fiwmwawe dump fwom device */
		/* When the fiwmwawe hangs, the device can no wongew
		 * suspend and thus disabwe auto-suspend.
		 */
		usb_disabwe_autosuspend(data->udev);

		/* We need to fowwawd the diagnostic packet to usewspace daemon
		 * fow backwawd compatibiwity, so we have to cwone the packet
		 * extwawy fow the in-kewnew cowedump suppowt.
		 */
		skb_cd = skb_cwone(skb, GFP_ATOMIC);
		if (skb_cd)
			btmtk_pwocess_cowedump(hdev, skb_cd);

		fawwthwough;
	case 0x05ff:		/* Fiwmwawe debug wogging 1 */
	case 0x05fe:		/* Fiwmwawe debug wogging 2 */
		wetuwn hci_wecv_diag(hdev, skb);
	}

	wetuwn hci_wecv_fwame(hdev, skb);
}

#ifdef CONFIG_PM
/* Configuwe an out-of-band gpio as wake-up pin, if specified in device twee */
static int mawveww_config_oob_wake(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct device *dev = &data->udev->dev;
	u16 pin, gap, opcode;
	int wet;
	u8 cmd[5];

	/* Move on if no wakeup pin specified */
	if (of_pwopewty_wead_u16(dev->of_node, "mawveww,wakeup-pin", &pin) ||
	    of_pwopewty_wead_u16(dev->of_node, "mawveww,wakeup-gap-ms", &gap))
		wetuwn 0;

	/* Vendow specific command to configuwe a GPIO as wake-up pin */
	opcode = hci_opcode_pack(0x3F, 0x59);
	cmd[0] = opcode & 0xFF;
	cmd[1] = opcode >> 8;
	cmd[2] = 2; /* wength of pawametews that fowwow */
	cmd[3] = pin;
	cmd[4] = gap; /* time in ms, fow which wakeup pin shouwd be assewted */

	skb = bt_skb_awwoc(sizeof(cmd), GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hdev, "%s: No memowy", __func__);
		wetuwn -ENOMEM;
	}

	skb_put_data(skb, cmd, sizeof(cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	wet = btusb_send_fwame(hdev, skb);
	if (wet) {
		bt_dev_eww(hdev, "%s: configuwation faiwed", __func__);
		kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

static int btusb_set_bdaddw_mawveww(stwuct hci_dev *hdev,
				    const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	u8 buf[8];
	wong wet;

	buf[0] = 0xfe;
	buf[1] = sizeof(bdaddw_t);
	memcpy(buf + 2, bdaddw, sizeof(bdaddw_t));

	skb = __hci_cmd_sync(hdev, 0xfc22, sizeof(buf), buf, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		bt_dev_eww(hdev, "changing Mawveww device addwess faiwed (%wd)",
			   wet);
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int btusb_set_bdaddw_ath3012(stwuct hci_dev *hdev,
				    const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	u8 buf[10];
	wong wet;

	buf[0] = 0x01;
	buf[1] = 0x01;
	buf[2] = 0x00;
	buf[3] = sizeof(bdaddw_t);
	memcpy(buf + 4, bdaddw, sizeof(bdaddw_t));

	skb = __hci_cmd_sync(hdev, 0xfc0b, sizeof(buf), buf, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		bt_dev_eww(hdev, "Change addwess command faiwed (%wd)", wet);
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int btusb_set_bdaddw_wcn6855(stwuct hci_dev *hdev,
				const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	u8 buf[6];
	wong wet;

	memcpy(buf, bdaddw, sizeof(bdaddw_t));

	skb = __hci_cmd_sync_ev(hdev, 0xfc14, sizeof(buf), buf,
				HCI_EV_CMD_COMPWETE, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		bt_dev_eww(hdev, "Change addwess command faiwed (%wd)", wet);
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

#define QCA_MEMDUMP_ACW_HANDWE 0x2EDD
#define QCA_MEMDUMP_SIZE_MAX  0x100000
#define QCA_MEMDUMP_VSE_CWASS 0x01
#define QCA_MEMDUMP_MSG_TYPE 0x08
#define QCA_MEMDUMP_PKT_SIZE 248
#define QCA_WAST_SEQUENCE_NUM 0xffff

stwuct qca_dump_hdw {
	u8 vse_cwass;
	u8 msg_type;
	__we16 seqno;
	u8 wesewved;
	union {
		u8 data[0];
		stwuct {
			__we32 wam_dump_size;
			u8 data0[0];
		} __packed;
	};
} __packed;


static void btusb_dump_hdw_qca(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	chaw buf[128];
	stwuct btusb_data *btdata = hci_get_dwvdata(hdev);

	snpwintf(buf, sizeof(buf), "Contwowwew Name: 0x%x\n",
			btdata->qca_dump.contwowwew_id);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Fiwmwawe Vewsion: 0x%x\n",
			btdata->qca_dump.fw_vewsion);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Dwivew: %s\nVendow: qca\n",
			btusb_dwivew.name);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "VID: 0x%x\nPID:0x%x\n",
			btdata->qca_dump.id_vendow, btdata->qca_dump.id_pwoduct);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Wmp Subvewsion: 0x%x\n",
			hdev->wmp_subvew);
	skb_put_data(skb, buf, stwwen(buf));
}

static void btusb_cowedump_qca(stwuct hci_dev *hdev)
{
	static const u8 pawam[] = { 0x26 };
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc0c, 1, pawam, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		bt_dev_eww(hdev, "%s: twiggwe cwash faiwed (%wd)", __func__, PTW_EWW(skb));
	kfwee_skb(skb);
}

/*
 * ==0: not a dump pkt.
 * < 0: faiws to handwe a dump pkt
 * > 0: othewwise.
 */
static int handwe_dump_pkt_qca(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	int wet = 1;
	u8 pkt_type;
	u8 *sk_ptw;
	unsigned int sk_wen;
	u16 seqno;
	u32 dump_size;

	stwuct hci_event_hdw *event_hdw;
	stwuct hci_acw_hdw *acw_hdw;
	stwuct qca_dump_hdw *dump_hdw;
	stwuct btusb_data *btdata = hci_get_dwvdata(hdev);
	stwuct usb_device *udev = btdata->udev;

	pkt_type = hci_skb_pkt_type(skb);
	sk_ptw = skb->data;
	sk_wen = skb->wen;

	if (pkt_type == HCI_ACWDATA_PKT) {
		acw_hdw = hci_acw_hdw(skb);
		if (we16_to_cpu(acw_hdw->handwe) != QCA_MEMDUMP_ACW_HANDWE)
			wetuwn 0;
		sk_ptw += HCI_ACW_HDW_SIZE;
		sk_wen -= HCI_ACW_HDW_SIZE;
		event_hdw = (stwuct hci_event_hdw *)sk_ptw;
	} ewse {
		event_hdw = hci_event_hdw(skb);
	}

	if ((event_hdw->evt != HCI_VENDOW_PKT)
		|| (event_hdw->pwen != (sk_wen - HCI_EVENT_HDW_SIZE)))
		wetuwn 0;

	sk_ptw += HCI_EVENT_HDW_SIZE;
	sk_wen -= HCI_EVENT_HDW_SIZE;

	dump_hdw = (stwuct qca_dump_hdw *)sk_ptw;
	if ((sk_wen < offsetof(stwuct qca_dump_hdw, data))
		|| (dump_hdw->vse_cwass != QCA_MEMDUMP_VSE_CWASS)
	    || (dump_hdw->msg_type != QCA_MEMDUMP_MSG_TYPE))
		wetuwn 0;

	/*it is dump pkt now*/
	seqno = we16_to_cpu(dump_hdw->seqno);
	if (seqno == 0) {
		set_bit(BTUSB_HW_SSW_ACTIVE, &btdata->fwags);
		dump_size = we32_to_cpu(dump_hdw->wam_dump_size);
		if (!dump_size || (dump_size > QCA_MEMDUMP_SIZE_MAX)) {
			wet = -EIWSEQ;
			bt_dev_eww(hdev, "Invawid memdump size(%u)",
				   dump_size);
			goto out;
		}

		wet = hci_devcd_init(hdev, dump_size);
		if (wet < 0) {
			bt_dev_eww(hdev, "memdump init ewwow(%d)", wet);
			goto out;
		}

		btdata->qca_dump.wam_dump_size = dump_size;
		btdata->qca_dump.wam_dump_seqno = 0;
		sk_ptw += offsetof(stwuct qca_dump_hdw, data0);
		sk_wen -= offsetof(stwuct qca_dump_hdw, data0);

		usb_disabwe_autosuspend(udev);
		bt_dev_info(hdev, "%s memdump size(%u)\n",
			    (pkt_type == HCI_ACWDATA_PKT) ? "ACW" : "event",
			    dump_size);
	} ewse {
		sk_ptw += offsetof(stwuct qca_dump_hdw, data);
		sk_wen -= offsetof(stwuct qca_dump_hdw, data);
	}

	if (!btdata->qca_dump.wam_dump_size) {
		wet = -EINVAW;
		bt_dev_eww(hdev, "memdump is not active");
		goto out;
	}

	if ((seqno > btdata->qca_dump.wam_dump_seqno + 1) && (seqno != QCA_WAST_SEQUENCE_NUM)) {
		dump_size = QCA_MEMDUMP_PKT_SIZE * (seqno - btdata->qca_dump.wam_dump_seqno - 1);
		hci_devcd_append_pattewn(hdev, 0x0, dump_size);
		bt_dev_eww(hdev,
			   "expected memdump seqno(%u) is not weceived(%u)\n",
			   btdata->qca_dump.wam_dump_seqno, seqno);
		btdata->qca_dump.wam_dump_seqno = seqno;
		kfwee_skb(skb);
		wetuwn wet;
	}

	skb_puww(skb, skb->wen - sk_wen);
	hci_devcd_append(hdev, skb);
	btdata->qca_dump.wam_dump_seqno++;
	if (seqno == QCA_WAST_SEQUENCE_NUM) {
		bt_dev_info(hdev,
				"memdump done: pkts(%u), totaw(%u)\n",
				btdata->qca_dump.wam_dump_seqno, btdata->qca_dump.wam_dump_size);

		hci_devcd_compwete(hdev);
		goto out;
	}
	wetuwn wet;

out:
	if (btdata->qca_dump.wam_dump_size)
		usb_enabwe_autosuspend(udev);
	btdata->qca_dump.wam_dump_size = 0;
	btdata->qca_dump.wam_dump_seqno = 0;
	cweaw_bit(BTUSB_HW_SSW_ACTIVE, &btdata->fwags);

	if (wet < 0)
		kfwee_skb(skb);
	wetuwn wet;
}

static int btusb_wecv_acw_qca(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (handwe_dump_pkt_qca(hdev, skb))
		wetuwn 0;
	wetuwn hci_wecv_fwame(hdev, skb);
}

static int btusb_wecv_evt_qca(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (handwe_dump_pkt_qca(hdev, skb))
		wetuwn 0;
	wetuwn hci_wecv_fwame(hdev, skb);
}


#define QCA_DFU_PACKET_WEN	4096

#define QCA_GET_TAWGET_VEWSION	0x09
#define QCA_CHECK_STATUS	0x05
#define QCA_DFU_DOWNWOAD	0x01

#define QCA_SYSCFG_UPDATED	0x40
#define QCA_PATCH_UPDATED	0x80
#define QCA_DFU_TIMEOUT		3000
#define QCA_FWAG_MUWTI_NVM      0x80
#define QCA_BT_WESET_WAIT_MS    100

#define WCN6855_2_0_WAM_VEWSION_GF 0x400c1200
#define WCN6855_2_1_WAM_VEWSION_GF 0x400c1211

stwuct qca_vewsion {
	__we32	wom_vewsion;
	__we32	patch_vewsion;
	__we32	wam_vewsion;
	__u8	chip_id;
	__u8	pwatfowm_id;
	__we16	fwag;
	__u8	wesewved[4];
} __packed;

stwuct qca_wampatch_vewsion {
	__we16	wom_vewsion_high;
	__we16  wom_vewsion_wow;
	__we16	patch_vewsion;
} __packed;

stwuct qca_device_info {
	u32	wom_vewsion;
	u8	wampatch_hdw;	/* wength of headew in wampatch */
	u8	nvm_hdw;	/* wength of headew in NVM */
	u8	vew_offset;	/* offset of vewsion stwuctuwe in wampatch */
};

static const stwuct qca_device_info qca_devices_tabwe[] = {
	{ 0x00000100, 20, 4,  8 }, /* Wome 1.0 */
	{ 0x00000101, 20, 4,  8 }, /* Wome 1.1 */
	{ 0x00000200, 28, 4, 16 }, /* Wome 2.0 */
	{ 0x00000201, 28, 4, 16 }, /* Wome 2.1 */
	{ 0x00000300, 28, 4, 16 }, /* Wome 3.0 */
	{ 0x00000302, 28, 4, 16 }, /* Wome 3.2 */
	{ 0x00130100, 40, 4, 16 }, /* WCN6855 1.0 */
	{ 0x00130200, 40, 4, 16 }, /* WCN6855 2.0 */
	{ 0x00130201, 40, 4, 16 }, /* WCN6855 2.1 */
	{ 0x00190200, 40, 4, 16 }, /* WCN785x 2.0 */
};

static int btusb_qca_send_vendow_weq(stwuct usb_device *udev, u8 wequest,
				     void *data, u16 size)
{
	int pipe, eww;
	u8 *buf;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Found some of USB hosts have IOT issues with ouws so that we shouwd
	 * not wait untiw HCI wayew is weady.
	 */
	pipe = usb_wcvctwwpipe(udev, 0);
	eww = usb_contwow_msg(udev, pipe, wequest, USB_TYPE_VENDOW | USB_DIW_IN,
			      0, 0, buf, size, USB_CTWW_SET_TIMEOUT);
	if (eww < 0) {
		dev_eww(&udev->dev, "Faiwed to access otp awea (%d)", eww);
		goto done;
	}

	memcpy(data, buf, size);

done:
	kfwee(buf);

	wetuwn eww;
}

static int btusb_setup_qca_downwoad_fw(stwuct hci_dev *hdev,
				       const stwuct fiwmwawe *fiwmwawe,
				       size_t hdw_size)
{
	stwuct btusb_data *btdata = hci_get_dwvdata(hdev);
	stwuct usb_device *udev = btdata->udev;
	size_t count, size, sent = 0;
	int pipe, wen, eww;
	u8 *buf;

	buf = kmawwoc(QCA_DFU_PACKET_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	count = fiwmwawe->size;

	size = min_t(size_t, count, hdw_size);
	memcpy(buf, fiwmwawe->data, size);

	/* USB patches shouwd go down to contwowwew thwough USB path
	 * because binawy fowmat fits to go down thwough USB channew.
	 * USB contwow path is fow patching headews and USB buwk is fow
	 * patch body.
	 */
	pipe = usb_sndctwwpipe(udev, 0);
	eww = usb_contwow_msg(udev, pipe, QCA_DFU_DOWNWOAD, USB_TYPE_VENDOW,
			      0, 0, buf, size, USB_CTWW_SET_TIMEOUT);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send headews (%d)", eww);
		goto done;
	}

	sent += size;
	count -= size;

	/* ep2 need time to switch fwom function acw to function dfu,
	 * so we add 20ms deway hewe.
	 */
	msweep(20);

	whiwe (count) {
		size = min_t(size_t, count, QCA_DFU_PACKET_WEN);

		memcpy(buf, fiwmwawe->data + sent, size);

		pipe = usb_sndbuwkpipe(udev, 0x02);
		eww = usb_buwk_msg(udev, pipe, buf, size, &wen,
				   QCA_DFU_TIMEOUT);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to send body at %zd of %zd (%d)",
				   sent, fiwmwawe->size, eww);
			bweak;
		}

		if (size != wen) {
			bt_dev_eww(hdev, "Faiwed to get buwk buffew");
			eww = -EIWSEQ;
			bweak;
		}

		sent  += size;
		count -= size;
	}

done:
	kfwee(buf);
	wetuwn eww;
}

static int btusb_setup_qca_woad_wampatch(stwuct hci_dev *hdev,
					 stwuct qca_vewsion *vew,
					 const stwuct qca_device_info *info)
{
	stwuct qca_wampatch_vewsion *wvew;
	const stwuct fiwmwawe *fw;
	u32 vew_wom, vew_patch, wvew_wom;
	u16 wvew_wom_wow, wvew_wom_high, wvew_patch;
	chaw fwname[64];
	int eww;

	vew_wom = we32_to_cpu(vew->wom_vewsion);
	vew_patch = we32_to_cpu(vew->patch_vewsion);

	snpwintf(fwname, sizeof(fwname), "qca/wampatch_usb_%08x.bin", vew_wom);

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww) {
		bt_dev_eww(hdev, "faiwed to wequest wampatch fiwe: %s (%d)",
			   fwname, eww);
		wetuwn eww;
	}

	bt_dev_info(hdev, "using wampatch fiwe: %s", fwname);

	wvew = (stwuct qca_wampatch_vewsion *)(fw->data + info->vew_offset);
	wvew_wom_wow = we16_to_cpu(wvew->wom_vewsion_wow);
	wvew_patch = we16_to_cpu(wvew->patch_vewsion);

	if (vew_wom & ~0xffffU) {
		wvew_wom_high = we16_to_cpu(wvew->wom_vewsion_high);
		wvew_wom = wvew_wom_high << 16 | wvew_wom_wow;
	} ewse {
		wvew_wom = wvew_wom_wow;
	}

	bt_dev_info(hdev, "QCA: patch wome 0x%x buiwd 0x%x, "
		    "fiwmwawe wome 0x%x buiwd 0x%x",
		    wvew_wom, wvew_patch, vew_wom, vew_patch);

	if (wvew_wom != vew_wom || wvew_patch <= vew_patch) {
		bt_dev_eww(hdev, "wampatch fiwe vewsion did not match with fiwmwawe");
		eww = -EINVAW;
		goto done;
	}

	eww = btusb_setup_qca_downwoad_fw(hdev, fw, info->wampatch_hdw);

done:
	wewease_fiwmwawe(fw);

	wetuwn eww;
}

static void btusb_genewate_qca_nvm_name(chaw *fwname, size_t max_size,
					const stwuct qca_vewsion *vew)
{
	u32 wom_vewsion = we32_to_cpu(vew->wom_vewsion);
	u16 fwag = we16_to_cpu(vew->fwag);

	if (((fwag >> 8) & 0xff) == QCA_FWAG_MUWTI_NVM) {
		/* The boawd_id shouwd be spwit into two bytes
		 * The 1st byte is chip ID, and the 2nd byte is pwatfowm ID
		 * Fow exampwe, boawd ID 0x010A, 0x01 is pwatfowm ID. 0x0A is chip ID
		 * we have sevewaw pwatfowms, and pwatfowm IDs awe continuouswy added
		 * Pwatfowm ID:
		 * 0x00 is fow Mobiwe
		 * 0x01 is fow X86
		 * 0x02 is fow Automotive
		 * 0x03 is fow Consumew ewectwonic
		 */
		u16 boawd_id = (vew->chip_id << 8) + vew->pwatfowm_id;
		const chaw *vawiant;

		switch (we32_to_cpu(vew->wam_vewsion)) {
		case WCN6855_2_0_WAM_VEWSION_GF:
		case WCN6855_2_1_WAM_VEWSION_GF:
			vawiant = "_gf";
			bweak;
		defauwt:
			vawiant = "";
			bweak;
		}

		if (boawd_id == 0) {
			snpwintf(fwname, max_size, "qca/nvm_usb_%08x%s.bin",
				wom_vewsion, vawiant);
		} ewse {
			snpwintf(fwname, max_size, "qca/nvm_usb_%08x%s_%04x.bin",
				wom_vewsion, vawiant, boawd_id);
		}
	} ewse {
		snpwintf(fwname, max_size, "qca/nvm_usb_%08x.bin",
			wom_vewsion);
	}

}

static int btusb_setup_qca_woad_nvm(stwuct hci_dev *hdev,
				    stwuct qca_vewsion *vew,
				    const stwuct qca_device_info *info)
{
	const stwuct fiwmwawe *fw;
	chaw fwname[64];
	int eww;

	btusb_genewate_qca_nvm_name(fwname, sizeof(fwname), vew);

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww) {
		bt_dev_eww(hdev, "faiwed to wequest NVM fiwe: %s (%d)",
			   fwname, eww);
		wetuwn eww;
	}

	bt_dev_info(hdev, "using NVM fiwe: %s", fwname);

	eww = btusb_setup_qca_downwoad_fw(hdev, fw, info->nvm_hdw);

	wewease_fiwmwawe(fw);

	wetuwn eww;
}

/* identify the WOM vewsion and check whethew patches awe needed */
static boow btusb_qca_need_patch(stwuct usb_device *udev)
{
	stwuct qca_vewsion vew;

	if (btusb_qca_send_vendow_weq(udev, QCA_GET_TAWGET_VEWSION, &vew,
				      sizeof(vew)) < 0)
		wetuwn fawse;
	/* onwy wow WOM vewsions need patches */
	wetuwn !(we32_to_cpu(vew.wom_vewsion) & ~0xffffU);
}

static int btusb_setup_qca(stwuct hci_dev *hdev)
{
	stwuct btusb_data *btdata = hci_get_dwvdata(hdev);
	stwuct usb_device *udev = btdata->udev;
	const stwuct qca_device_info *info = NUWW;
	stwuct qca_vewsion vew;
	u32 vew_wom;
	u8 status;
	int i, eww;

	eww = btusb_qca_send_vendow_weq(udev, QCA_GET_TAWGET_VEWSION, &vew,
					sizeof(vew));
	if (eww < 0)
		wetuwn eww;

	vew_wom = we32_to_cpu(vew.wom_vewsion);

	fow (i = 0; i < AWWAY_SIZE(qca_devices_tabwe); i++) {
		if (vew_wom == qca_devices_tabwe[i].wom_vewsion)
			info = &qca_devices_tabwe[i];
	}
	if (!info) {
		/* If the wom_vewsion is not matched in the qca_devices_tabwe
		 * and the high WOM vewsion is not zewo, we assume this chip no
		 * need to woad the wampatch and nvm.
		 */
		if (vew_wom & ~0xffffU)
			wetuwn 0;

		bt_dev_eww(hdev, "don't suppowt fiwmwawe wome 0x%x", vew_wom);
		wetuwn -ENODEV;
	}

	eww = btusb_qca_send_vendow_weq(udev, QCA_CHECK_STATUS, &status,
					sizeof(status));
	if (eww < 0)
		wetuwn eww;

	if (!(status & QCA_PATCH_UPDATED)) {
		eww = btusb_setup_qca_woad_wampatch(hdev, &vew, info);
		if (eww < 0)
			wetuwn eww;
	}

	eww = btusb_qca_send_vendow_weq(udev, QCA_GET_TAWGET_VEWSION, &vew,
					sizeof(vew));
	if (eww < 0)
		wetuwn eww;

	btdata->qca_dump.fw_vewsion = we32_to_cpu(vew.patch_vewsion);
	btdata->qca_dump.contwowwew_id = we32_to_cpu(vew.wom_vewsion);

	if (!(status & QCA_SYSCFG_UPDATED)) {
		eww = btusb_setup_qca_woad_nvm(hdev, &vew, info);
		if (eww < 0)
			wetuwn eww;

		/* WCN6855 2.1 and watew wiww weset to appwy fiwmwawe downwoaded hewe, so
		 * wait ~100ms fow weset Done then go ahead, othewwise, it maybe
		 * cause potentiaw enabwe faiwuwe.
		 */
		if (info->wom_vewsion >= 0x00130201)
			msweep(QCA_BT_WESET_WAIT_MS);
	}

	/* Mawk HCI_OP_ENHANCED_SETUP_SYNC_CONN as bwoken as it doesn't seem to
	 * wowk with the wikes of HSP/HFP mSBC.
	 */
	set_bit(HCI_QUIWK_BWOKEN_ENHANCED_SETUP_SYNC_CONN, &hdev->quiwks);

	wetuwn 0;
}

static inwine int __set_diag_intewface(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct usb_intewface *intf = data->diag;
	int i;

	if (!data->diag)
		wetuwn -ENODEV;

	data->diag_tx_ep = NUWW;
	data->diag_wx_ep = NUWW;

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		stwuct usb_endpoint_descwiptow *ep_desc;

		ep_desc = &intf->cuw_awtsetting->endpoint[i].desc;

		if (!data->diag_tx_ep && usb_endpoint_is_buwk_out(ep_desc)) {
			data->diag_tx_ep = ep_desc;
			continue;
		}

		if (!data->diag_wx_ep && usb_endpoint_is_buwk_in(ep_desc)) {
			data->diag_wx_ep = ep_desc;
			continue;
		}
	}

	if (!data->diag_tx_ep || !data->diag_wx_ep) {
		bt_dev_eww(hdev, "invawid diagnostic descwiptows");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static stwuct uwb *awwoc_diag_uwb(stwuct hci_dev *hdev, boow enabwe)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct sk_buff *skb;
	stwuct uwb *uwb;
	unsigned int pipe;

	if (!data->diag_tx_ep)
		wetuwn EWW_PTW(-ENODEV);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn EWW_PTW(-ENOMEM);

	skb = bt_skb_awwoc(2, GFP_KEWNEW);
	if (!skb) {
		usb_fwee_uwb(uwb);
		wetuwn EWW_PTW(-ENOMEM);
	}

	skb_put_u8(skb, 0xf0);
	skb_put_u8(skb, enabwe);

	pipe = usb_sndbuwkpipe(data->udev, data->diag_tx_ep->bEndpointAddwess);

	usb_fiww_buwk_uwb(uwb, data->udev, pipe,
			  skb->data, skb->wen, btusb_tx_compwete, skb);

	skb->dev = (void *)hdev;

	wetuwn uwb;
}

static int btusb_bcm_set_diag(stwuct hci_dev *hdev, boow enabwe)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct uwb *uwb;

	if (!data->diag)
		wetuwn -ENODEV;

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn -ENETDOWN;

	uwb = awwoc_diag_uwb(hdev, enabwe);
	if (IS_EWW(uwb))
		wetuwn PTW_EWW(uwb);

	wetuwn submit_ow_queue_tx_uwb(hdev, uwb);
}

#ifdef CONFIG_PM
static iwqwetuwn_t btusb_oob_wake_handwew(int iwq, void *pwiv)
{
	stwuct btusb_data *data = pwiv;

	pm_wakeup_event(&data->udev->dev, 0);
	pm_system_wakeup();

	/* Disabwe onwy if not awweady disabwed (keep it bawanced) */
	if (test_and_cweaw_bit(BTUSB_OOB_WAKE_ENABWED, &data->fwags)) {
		disabwe_iwq_nosync(iwq);
		disabwe_iwq_wake(iwq);
	}
	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id btusb_match_tabwe[] = {
	{ .compatibwe = "usb1286,204e" },
	{ .compatibwe = "usbcf3,e300" }, /* QCA6174A */
	{ .compatibwe = "usb4ca,301a" }, /* QCA6174A (Wite-On) */
	{ }
};
MODUWE_DEVICE_TABWE(of, btusb_match_tabwe);

/* Use an oob wakeup pin? */
static int btusb_config_oob_wake(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);
	stwuct device *dev = &data->udev->dev;
	int iwq, wet;

	cweaw_bit(BTUSB_OOB_WAKE_ENABWED, &data->fwags);

	if (!of_match_device(btusb_match_tabwe, dev))
		wetuwn 0;

	/* Move on if no IWQ specified */
	iwq = of_iwq_get_byname(dev->of_node, "wakeup");
	if (iwq <= 0) {
		bt_dev_dbg(hdev, "%s: no OOB Wakeup IWQ in DT", __func__);
		wetuwn 0;
	}

	iwq_set_status_fwags(iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&hdev->dev, iwq, btusb_oob_wake_handwew,
			       0, "OOB Wake-on-BT", data);
	if (wet) {
		bt_dev_eww(hdev, "%s: IWQ wequest faiwed", __func__);
		wetuwn wet;
	}

	wet = device_init_wakeup(dev, twue);
	if (wet) {
		bt_dev_eww(hdev, "%s: faiwed to init_wakeup", __func__);
		wetuwn wet;
	}

	data->oob_wake_iwq = iwq;
	bt_dev_info(hdev, "OOB Wake-on-BT configuwed at IWQ %u", iwq);
	wetuwn 0;
}
#endif

static void btusb_check_needs_weset_wesume(stwuct usb_intewface *intf)
{
	if (dmi_check_system(btusb_needs_weset_wesume_tabwe))
		intewface_to_usbdev(intf)->quiwks |= USB_QUIWK_WESET_WESUME;
}

static boow btusb_wakeup(stwuct hci_dev *hdev)
{
	stwuct btusb_data *data = hci_get_dwvdata(hdev);

	wetuwn device_may_wakeup(&data->udev->dev);
}

static int btusb_shutdown_qca(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "HCI weset duwing shutdown faiwed");
		wetuwn PTW_EWW(skb);
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static ssize_t fowce_poww_sync_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct btusb_data *data = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = data->poww_sync ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t fowce_poww_sync_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct btusb_data *data = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	/* Onwy awwow changes whiwe the adaptew is down */
	if (test_bit(HCI_UP, &data->hdev->fwags))
		wetuwn -EPEWM;

	if (data->poww_sync == enabwe)
		wetuwn -EAWWEADY;

	data->poww_sync = enabwe;

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_poww_sync_fops = {
	.open		= simpwe_open,
	.wead		= fowce_poww_sync_wead,
	.wwite		= fowce_poww_sync_wwite,
	.wwseek		= defauwt_wwseek,
};

static int btusb_pwobe(stwuct usb_intewface *intf,
		       const stwuct usb_device_id *id)
{
	stwuct usb_endpoint_descwiptow *ep_desc;
	stwuct gpio_desc *weset_gpio;
	stwuct btusb_data *data;
	stwuct hci_dev *hdev;
	unsigned ifnum_base;
	int i, eww, pwiv_size;

	BT_DBG("intf %p id %p", intf, id);

	if ((id->dwivew_info & BTUSB_IFNUM_2) &&
	    (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 0) &&
	    (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 2))
		wetuwn -ENODEV;

	ifnum_base = intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	if (!id->dwivew_info) {
		const stwuct usb_device_id *match;

		match = usb_match_id(intf, quiwks_tabwe);
		if (match)
			id = match;
	}

	if (id->dwivew_info == BTUSB_IGNOWE)
		wetuwn -ENODEV;

	if (id->dwivew_info & BTUSB_ATH3012) {
		stwuct usb_device *udev = intewface_to_usbdev(intf);

		/* Owd fiwmwawe wouwd othewwise wet ath3k dwivew woad
		 * patch and sysconfig fiwes
		 */
		if (we16_to_cpu(udev->descwiptow.bcdDevice) <= 0x0001 &&
		    !btusb_qca_need_patch(udev))
			wetuwn -ENODEV;
	}

	data = devm_kzawwoc(&intf->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	fow (i = 0; i < intf->cuw_awtsetting->desc.bNumEndpoints; i++) {
		ep_desc = &intf->cuw_awtsetting->endpoint[i].desc;

		if (!data->intw_ep && usb_endpoint_is_int_in(ep_desc)) {
			data->intw_ep = ep_desc;
			continue;
		}

		if (!data->buwk_tx_ep && usb_endpoint_is_buwk_out(ep_desc)) {
			data->buwk_tx_ep = ep_desc;
			continue;
		}

		if (!data->buwk_wx_ep && usb_endpoint_is_buwk_in(ep_desc)) {
			data->buwk_wx_ep = ep_desc;
			continue;
		}
	}

	if (!data->intw_ep || !data->buwk_tx_ep || !data->buwk_wx_ep)
		wetuwn -ENODEV;

	if (id->dwivew_info & BTUSB_AMP) {
		data->cmdweq_type = USB_TYPE_CWASS | 0x01;
		data->cmdweq = 0x2b;
	} ewse {
		data->cmdweq_type = USB_TYPE_CWASS;
		data->cmdweq = 0x00;
	}

	data->udev = intewface_to_usbdev(intf);
	data->intf = intf;

	INIT_WOWK(&data->wowk, btusb_wowk);
	INIT_WOWK(&data->wakew, btusb_wakew);
	INIT_DEWAYED_WOWK(&data->wx_wowk, btusb_wx_wowk);

	skb_queue_head_init(&data->acw_q);

	init_usb_anchow(&data->defewwed);
	init_usb_anchow(&data->tx_anchow);
	spin_wock_init(&data->txwock);

	init_usb_anchow(&data->intw_anchow);
	init_usb_anchow(&data->buwk_anchow);
	init_usb_anchow(&data->isoc_anchow);
	init_usb_anchow(&data->diag_anchow);
	init_usb_anchow(&data->ctww_anchow);
	spin_wock_init(&data->wxwock);

	pwiv_size = 0;

	data->wecv_event = hci_wecv_fwame;
	data->wecv_buwk = btusb_wecv_buwk;

	if (id->dwivew_info & BTUSB_INTEW_COMBINED) {
		/* Awwocate extwa space fow Intew device */
		pwiv_size += sizeof(stwuct btintew_data);

		/* Ovewwide the wx handwews */
		data->wecv_event = btintew_wecv_event;
		data->wecv_buwk = btusb_wecv_buwk_intew;
	} ewse if (id->dwivew_info & BTUSB_WEAWTEK) {
		/* Awwocate extwa space fow Weawtek device */
		pwiv_size += sizeof(stwuct btweawtek_data);

		data->wecv_event = btusb_wecv_event_weawtek;
	} ewse if (id->dwivew_info & BTUSB_MEDIATEK) {
		/* Awwocate extwa space fow Mediatek device */
		pwiv_size += sizeof(stwuct btmediatek_data);
	}

	data->wecv_acw = hci_wecv_fwame;

	hdev = hci_awwoc_dev_pwiv(pwiv_size);
	if (!hdev)
		wetuwn -ENOMEM;

	hdev->bus = HCI_USB;
	hci_set_dwvdata(hdev, data);

	if (id->dwivew_info & BTUSB_AMP)
		hdev->dev_type = HCI_AMP;
	ewse
		hdev->dev_type = HCI_PWIMAWY;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &intf->dev);

	weset_gpio = gpiod_get_optionaw(&data->udev->dev, "weset",
					GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio)) {
		eww = PTW_EWW(weset_gpio);
		goto out_fwee_dev;
	} ewse if (weset_gpio) {
		data->weset_gpio = weset_gpio;
	}

	hdev->open   = btusb_open;
	hdev->cwose  = btusb_cwose;
	hdev->fwush  = btusb_fwush;
	hdev->send   = btusb_send_fwame;
	hdev->notify = btusb_notify;
	hdev->wakeup = btusb_wakeup;

#ifdef CONFIG_PM
	eww = btusb_config_oob_wake(hdev);
	if (eww)
		goto out_fwee_dev;

	/* Mawveww devices may need a specific chip configuwation */
	if (id->dwivew_info & BTUSB_MAWVEWW && data->oob_wake_iwq) {
		eww = mawveww_config_oob_wake(hdev);
		if (eww)
			goto out_fwee_dev;
	}
#endif
	if (id->dwivew_info & BTUSB_CW6622)
		set_bit(HCI_QUIWK_BWOKEN_STOWED_WINK_KEY, &hdev->quiwks);

	if (id->dwivew_info & BTUSB_BCM2045)
		set_bit(HCI_QUIWK_BWOKEN_STOWED_WINK_KEY, &hdev->quiwks);

	if (id->dwivew_info & BTUSB_BCM92035)
		hdev->setup = btusb_setup_bcm92035;

	if (IS_ENABWED(CONFIG_BT_HCIBTUSB_BCM) &&
	    (id->dwivew_info & BTUSB_BCM_PATCHWAM)) {
		hdev->manufactuwew = 15;
		hdev->setup = btbcm_setup_patchwam;
		hdev->set_diag = btusb_bcm_set_diag;
		hdev->set_bdaddw = btbcm_set_bdaddw;

		/* Bwoadcom WM_DIAG Intewface numbews awe hawdcoded */
		data->diag = usb_ifnum_to_if(data->udev, ifnum_base + 2);
	}

	if (IS_ENABWED(CONFIG_BT_HCIBTUSB_BCM) &&
	    (id->dwivew_info & BTUSB_BCM_APPWE)) {
		hdev->manufactuwew = 15;
		hdev->setup = btbcm_setup_appwe;
		hdev->set_diag = btusb_bcm_set_diag;

		/* Bwoadcom WM_DIAG Intewface numbews awe hawdcoded */
		data->diag = usb_ifnum_to_if(data->udev, ifnum_base + 2);
	}

	/* Combined Intew Device setup to suppowt muwtipwe setup woutine */
	if (id->dwivew_info & BTUSB_INTEW_COMBINED) {
		eww = btintew_configuwe_setup(hdev, btusb_dwivew.name);
		if (eww)
			goto out_fwee_dev;

		/* Twanspowt specific configuwation */
		hdev->send = btusb_send_fwame_intew;
		hdev->cmd_timeout = btusb_intew_cmd_timeout;

		if (id->dwivew_info & BTUSB_INTEW_NO_WBS_SUPPOWT)
			btintew_set_fwag(hdev, INTEW_WOM_WEGACY_NO_WBS_SUPPOWT);

		if (id->dwivew_info & BTUSB_INTEW_BWOKEN_INITIAW_NCMD)
			btintew_set_fwag(hdev, INTEW_BWOKEN_INITIAW_NCMD);

		if (id->dwivew_info & BTUSB_INTEW_BWOKEN_SHUTDOWN_WED)
			btintew_set_fwag(hdev, INTEW_BWOKEN_SHUTDOWN_WED);
	}

	if (id->dwivew_info & BTUSB_MAWVEWW)
		hdev->set_bdaddw = btusb_set_bdaddw_mawveww;

	if (IS_ENABWED(CONFIG_BT_HCIBTUSB_MTK) &&
	    (id->dwivew_info & BTUSB_MEDIATEK)) {
		hdev->setup = btusb_mtk_setup;
		hdev->shutdown = btusb_mtk_shutdown;
		hdev->manufactuwew = 70;
		hdev->cmd_timeout = btmtk_weset_sync;
		hdev->set_bdaddw = btmtk_set_bdaddw;
		set_bit(HCI_QUIWK_BWOKEN_ENHANCED_SETUP_SYNC_CONN, &hdev->quiwks);
		set_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks);
		data->wecv_acw = btusb_wecv_acw_mtk;
	}

	if (id->dwivew_info & BTUSB_SWAVE) {
		set_bit(HCI_QUIWK_FIXUP_INQUIWY_MODE, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_WOCAW_COMMANDS, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_INTEW_BOOT) {
		hdev->manufactuwew = 2;
		set_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_ATH3012) {
		data->setup_on_usb = btusb_setup_qca;
		hdev->set_bdaddw = btusb_set_bdaddw_ath3012;
		set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);
		set_bit(HCI_QUIWK_STWICT_DUPWICATE_FIWTEW, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_QCA_WOME) {
		data->setup_on_usb = btusb_setup_qca;
		hdev->shutdown = btusb_shutdown_qca;
		hdev->set_bdaddw = btusb_set_bdaddw_ath3012;
		hdev->cmd_timeout = btusb_qca_cmd_timeout;
		set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);
		btusb_check_needs_weset_wesume(intf);
	}

	if (id->dwivew_info & BTUSB_QCA_WCN6855) {
		data->qca_dump.id_vendow = id->idVendow;
		data->qca_dump.id_pwoduct = id->idPwoduct;
		data->wecv_event = btusb_wecv_evt_qca;
		data->wecv_acw = btusb_wecv_acw_qca;
		hci_devcd_wegistew(hdev, btusb_cowedump_qca, btusb_dump_hdw_qca, NUWW);
		data->setup_on_usb = btusb_setup_qca;
		hdev->shutdown = btusb_shutdown_qca;
		hdev->set_bdaddw = btusb_set_bdaddw_wcn6855;
		hdev->cmd_timeout = btusb_qca_cmd_timeout;
		set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);
		hci_set_msft_opcode(hdev, 0xFD70);
	}

	if (id->dwivew_info & BTUSB_AMP) {
		/* AMP contwowwews do not suppowt SCO packets */
		data->isoc = NUWW;
	} ewse {
		/* Intewface owdews awe hawdcoded in the specification */
		data->isoc = usb_ifnum_to_if(data->udev, ifnum_base + 1);
		data->isoc_ifnum = ifnum_base + 1;
	}

	if (IS_ENABWED(CONFIG_BT_HCIBTUSB_WTW) &&
	    (id->dwivew_info & BTUSB_WEAWTEK)) {
		btwtw_set_dwivew_name(hdev, btusb_dwivew.name);
		hdev->setup = btusb_setup_weawtek;
		hdev->shutdown = btwtw_shutdown_weawtek;
		hdev->cmd_timeout = btusb_wtw_cmd_timeout;
		hdev->hw_ewwow = btusb_wtw_hw_ewwow;

		/* Weawtek devices need to set wemote wakeup on auto-suspend */
		set_bit(BTUSB_WAKEUP_AUTOSUSPEND, &data->fwags);
		set_bit(BTUSB_USE_AWT3_FOW_WBS, &data->fwags);
	}

	if (id->dwivew_info & BTUSB_ACTIONS_SEMI) {
		/* Suppowt is advewtised, but not impwemented */
		set_bit(HCI_QUIWK_BWOKEN_EWW_DATA_WEPOWTING, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_WEAD_TWANSMIT_POWEW, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_SET_WPA_TIMEOUT, &hdev->quiwks);
		set_bit(HCI_QUIWK_BWOKEN_EXT_SCAN, &hdev->quiwks);
	}

	if (!weset)
		set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);

	if (fowce_scofix || id->dwivew_info & BTUSB_WWONG_SCO_MTU) {
		if (!disabwe_scofix)
			set_bit(HCI_QUIWK_FIXUP_BUFFEW_SIZE, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_BWOKEN_ISOC)
		data->isoc = NUWW;

	if (id->dwivew_info & BTUSB_WIDEBAND_SPEECH)
		set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED, &hdev->quiwks);

	if (id->dwivew_info & BTUSB_VAWID_WE_STATES)
		set_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks);

	if (id->dwivew_info & BTUSB_DIGIANSWEW) {
		data->cmdweq_type = USB_TYPE_VENDOW;
		set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_CSW) {
		stwuct usb_device *udev = data->udev;
		u16 bcdDevice = we16_to_cpu(udev->descwiptow.bcdDevice);

		/* Owd fiwmwawe wouwd othewwise execute USB weset */
		if (bcdDevice < 0x117)
			set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);

		/* This must be set fiwst in case we disabwe it fow fakes */
		set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);

		/* Fake CSW devices with bwoken commands */
		if (we16_to_cpu(udev->descwiptow.idVendow)  == 0x0a12 &&
		    we16_to_cpu(udev->descwiptow.idPwoduct) == 0x0001)
			hdev->setup = btusb_setup_csw;
	}

	if (id->dwivew_info & BTUSB_SNIFFEW) {
		stwuct usb_device *udev = data->udev;

		/* New sniffew fiwmwawe has cwippwed HCI intewface */
		if (we16_to_cpu(udev->descwiptow.bcdDevice) > 0x997)
			set_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks);
	}

	if (id->dwivew_info & BTUSB_INTEW_BOOT) {
		/* A bug in the bootwoadew causes that intewwupt intewface is
		 * onwy enabwed aftew weceiving SetIntewface(0, AwtSetting=0).
		 */
		eww = usb_set_intewface(data->udev, 0, 0);
		if (eww < 0) {
			BT_EWW("faiwed to set intewface 0, awt 0 %d", eww);
			goto out_fwee_dev;
		}
	}

	if (data->isoc) {
		eww = usb_dwivew_cwaim_intewface(&btusb_dwivew,
						 data->isoc, data);
		if (eww < 0)
			goto out_fwee_dev;
	}

	if (IS_ENABWED(CONFIG_BT_HCIBTUSB_BCM) && data->diag) {
		if (!usb_dwivew_cwaim_intewface(&btusb_dwivew,
						data->diag, data))
			__set_diag_intewface(hdev);
		ewse
			data->diag = NUWW;
	}

	if (enabwe_autosuspend)
		usb_enabwe_autosuspend(data->udev);

	data->poww_sync = enabwe_poww_sync;

	eww = hci_wegistew_dev(hdev);
	if (eww < 0)
		goto out_fwee_dev;

	usb_set_intfdata(intf, data);

	debugfs_cweate_fiwe("fowce_poww_sync", 0644, hdev->debugfs, data,
			    &fowce_poww_sync_fops);

	wetuwn 0;

out_fwee_dev:
	if (data->weset_gpio)
		gpiod_put(data->weset_gpio);
	hci_fwee_dev(hdev);
	wetuwn eww;
}

static void btusb_disconnect(stwuct usb_intewface *intf)
{
	stwuct btusb_data *data = usb_get_intfdata(intf);
	stwuct hci_dev *hdev;

	BT_DBG("intf %p", intf);

	if (!data)
		wetuwn;

	hdev = data->hdev;
	usb_set_intfdata(data->intf, NUWW);

	if (data->isoc)
		usb_set_intfdata(data->isoc, NUWW);

	if (data->diag)
		usb_set_intfdata(data->diag, NUWW);

	hci_unwegistew_dev(hdev);

	if (intf == data->intf) {
		if (data->isoc)
			usb_dwivew_wewease_intewface(&btusb_dwivew, data->isoc);
		if (data->diag)
			usb_dwivew_wewease_intewface(&btusb_dwivew, data->diag);
	} ewse if (intf == data->isoc) {
		if (data->diag)
			usb_dwivew_wewease_intewface(&btusb_dwivew, data->diag);
		usb_dwivew_wewease_intewface(&btusb_dwivew, data->intf);
	} ewse if (intf == data->diag) {
		usb_dwivew_wewease_intewface(&btusb_dwivew, data->intf);
		if (data->isoc)
			usb_dwivew_wewease_intewface(&btusb_dwivew, data->isoc);
	}

	if (data->oob_wake_iwq)
		device_init_wakeup(&data->udev->dev, fawse);

	if (data->weset_gpio)
		gpiod_put(data->weset_gpio);

	hci_fwee_dev(hdev);
}

#ifdef CONFIG_PM
static int btusb_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct btusb_data *data = usb_get_intfdata(intf);

	BT_DBG("intf %p", intf);

	/* Don't suspend if thewe awe connections */
	if (hci_conn_count(data->hdev))
		wetuwn -EBUSY;

	if (data->suspend_count++)
		wetuwn 0;

	spin_wock_iwq(&data->txwock);
	if (!(PMSG_IS_AUTO(message) && data->tx_in_fwight)) {
		set_bit(BTUSB_SUSPENDING, &data->fwags);
		spin_unwock_iwq(&data->txwock);
	} ewse {
		spin_unwock_iwq(&data->txwock);
		data->suspend_count--;
		wetuwn -EBUSY;
	}

	cancew_wowk_sync(&data->wowk);

	btusb_stop_twaffic(data);
	usb_kiww_anchowed_uwbs(&data->tx_anchow);

	if (data->oob_wake_iwq && device_may_wakeup(&data->udev->dev)) {
		set_bit(BTUSB_OOB_WAKE_ENABWED, &data->fwags);
		enabwe_iwq_wake(data->oob_wake_iwq);
		enabwe_iwq(data->oob_wake_iwq);
	}

	/* Fow gwobaw suspend, Weawtek devices wose the woaded fw
	 * in them. But fow autosuspend, fiwmwawe shouwd wemain.
	 * Actuawwy, it depends on whethew the usb host sends
	 * set featuwe (enabwe wakeup) ow not.
	 */
	if (test_bit(BTUSB_WAKEUP_AUTOSUSPEND, &data->fwags)) {
		if (PMSG_IS_AUTO(message) &&
		    device_can_wakeup(&data->udev->dev))
			data->udev->do_wemote_wakeup = 1;
		ewse if (!PMSG_IS_AUTO(message) &&
			 !device_may_wakeup(&data->udev->dev)) {
			data->udev->do_wemote_wakeup = 0;
			data->udev->weset_wesume = 1;
		}
	}

	wetuwn 0;
}

static void pway_defewwed(stwuct btusb_data *data)
{
	stwuct uwb *uwb;
	int eww;

	whiwe ((uwb = usb_get_fwom_anchow(&data->defewwed))) {
		usb_anchow_uwb(uwb, &data->tx_anchow);

		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (eww < 0) {
			if (eww != -EPEWM && eww != -ENODEV)
				BT_EWW("%s uwb %p submission faiwed (%d)",
				       data->hdev->name, uwb, -eww);
			kfwee(uwb->setup_packet);
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			bweak;
		}

		data->tx_in_fwight++;
		usb_fwee_uwb(uwb);
	}

	/* Cweanup the west defewwed uwbs. */
	whiwe ((uwb = usb_get_fwom_anchow(&data->defewwed))) {
		kfwee(uwb->setup_packet);
		usb_fwee_uwb(uwb);
	}
}

static int btusb_wesume(stwuct usb_intewface *intf)
{
	stwuct btusb_data *data = usb_get_intfdata(intf);
	stwuct hci_dev *hdev = data->hdev;
	int eww = 0;

	BT_DBG("intf %p", intf);

	if (--data->suspend_count)
		wetuwn 0;

	/* Disabwe onwy if not awweady disabwed (keep it bawanced) */
	if (test_and_cweaw_bit(BTUSB_OOB_WAKE_ENABWED, &data->fwags)) {
		disabwe_iwq(data->oob_wake_iwq);
		disabwe_iwq_wake(data->oob_wake_iwq);
	}

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		goto done;

	if (test_bit(BTUSB_INTW_WUNNING, &data->fwags)) {
		eww = btusb_submit_intw_uwb(hdev, GFP_NOIO);
		if (eww < 0) {
			cweaw_bit(BTUSB_INTW_WUNNING, &data->fwags);
			goto faiwed;
		}
	}

	if (test_bit(BTUSB_BUWK_WUNNING, &data->fwags)) {
		eww = btusb_submit_buwk_uwb(hdev, GFP_NOIO);
		if (eww < 0) {
			cweaw_bit(BTUSB_BUWK_WUNNING, &data->fwags);
			goto faiwed;
		}

		btusb_submit_buwk_uwb(hdev, GFP_NOIO);
	}

	if (test_bit(BTUSB_ISOC_WUNNING, &data->fwags)) {
		if (btusb_submit_isoc_uwb(hdev, GFP_NOIO) < 0)
			cweaw_bit(BTUSB_ISOC_WUNNING, &data->fwags);
		ewse
			btusb_submit_isoc_uwb(hdev, GFP_NOIO);
	}

	spin_wock_iwq(&data->txwock);
	pway_defewwed(data);
	cweaw_bit(BTUSB_SUSPENDING, &data->fwags);
	spin_unwock_iwq(&data->txwock);
	scheduwe_wowk(&data->wowk);

	wetuwn 0;

faiwed:
	usb_scuttwe_anchowed_uwbs(&data->defewwed);
done:
	spin_wock_iwq(&data->txwock);
	cweaw_bit(BTUSB_SUSPENDING, &data->fwags);
	spin_unwock_iwq(&data->txwock);

	wetuwn eww;
}
#endif

#ifdef CONFIG_DEV_COWEDUMP
static void btusb_cowedump(stwuct device *dev)
{
	stwuct btusb_data *data = dev_get_dwvdata(dev);
	stwuct hci_dev *hdev = data->hdev;

	if (hdev->dump.cowedump)
		hdev->dump.cowedump(hdev);
}
#endif

static stwuct usb_dwivew btusb_dwivew = {
	.name		= "btusb",
	.pwobe		= btusb_pwobe,
	.disconnect	= btusb_disconnect,
#ifdef CONFIG_PM
	.suspend	= btusb_suspend,
	.wesume		= btusb_wesume,
#endif
	.id_tabwe	= btusb_tabwe,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,

#ifdef CONFIG_DEV_COWEDUMP
	.dwivew = {
		.cowedump = btusb_cowedump,
	},
#endif
};

moduwe_usb_dwivew(btusb_dwivew);

moduwe_pawam(disabwe_scofix, boow, 0644);
MODUWE_PAWM_DESC(disabwe_scofix, "Disabwe fixup of wwong SCO buffew size");

moduwe_pawam(fowce_scofix, boow, 0644);
MODUWE_PAWM_DESC(fowce_scofix, "Fowce fixup of wwong SCO buffews size");

moduwe_pawam(enabwe_autosuspend, boow, 0644);
MODUWE_PAWM_DESC(enabwe_autosuspend, "Enabwe USB autosuspend by defauwt");

moduwe_pawam(weset, boow, 0644);
MODUWE_PAWM_DESC(weset, "Send HCI weset command on initiawization");

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Genewic Bwuetooth USB dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
