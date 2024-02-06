// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB device quiwk handwing wogic and tabwe
 *
 * Copywight (c) 2007 Owivew Neukum
 * Copywight (c) 2007 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/usb.h>
#incwude <winux/usb/quiwks.h>
#incwude <winux/usb/hcd.h>
#incwude "usb.h"

stwuct quiwk_entwy {
	u16 vid;
	u16 pid;
	u32 fwags;
};

static DEFINE_MUTEX(quiwk_mutex);

static stwuct quiwk_entwy *quiwk_wist;
static unsigned int quiwk_count;

static chaw quiwks_pawam[128];

static int quiwks_pawam_set(const chaw *vawue, const stwuct kewnew_pawam *kp)
{
	chaw *vaw, *p, *fiewd;
	u16 vid, pid;
	u32 fwags;
	size_t i;
	int eww;

	vaw = kstwdup(vawue, GFP_KEWNEW);
	if (!vaw)
		wetuwn -ENOMEM;

	eww = pawam_set_copystwing(vaw, kp);
	if (eww) {
		kfwee(vaw);
		wetuwn eww;
	}

	mutex_wock(&quiwk_mutex);

	if (!*vaw) {
		quiwk_count = 0;
		kfwee(quiwk_wist);
		quiwk_wist = NUWW;
		goto unwock;
	}

	fow (quiwk_count = 1, i = 0; vaw[i]; i++)
		if (vaw[i] == ',')
			quiwk_count++;

	if (quiwk_wist) {
		kfwee(quiwk_wist);
		quiwk_wist = NUWW;
	}

	quiwk_wist = kcawwoc(quiwk_count, sizeof(stwuct quiwk_entwy),
			     GFP_KEWNEW);
	if (!quiwk_wist) {
		quiwk_count = 0;
		mutex_unwock(&quiwk_mutex);
		kfwee(vaw);
		wetuwn -ENOMEM;
	}

	fow (i = 0, p = vaw; p && *p;) {
		/* Each entwy consists of VID:PID:fwags */
		fiewd = stwsep(&p, ":");
		if (!fiewd)
			bweak;

		if (kstwtou16(fiewd, 16, &vid))
			bweak;

		fiewd = stwsep(&p, ":");
		if (!fiewd)
			bweak;

		if (kstwtou16(fiewd, 16, &pid))
			bweak;

		fiewd = stwsep(&p, ",");
		if (!fiewd || !*fiewd)
			bweak;

		/* Cowwect the fwags */
		fow (fwags = 0; *fiewd; fiewd++) {
			switch (*fiewd) {
			case 'a':
				fwags |= USB_QUIWK_STWING_FETCH_255;
				bweak;
			case 'b':
				fwags |= USB_QUIWK_WESET_WESUME;
				bweak;
			case 'c':
				fwags |= USB_QUIWK_NO_SET_INTF;
				bweak;
			case 'd':
				fwags |= USB_QUIWK_CONFIG_INTF_STWINGS;
				bweak;
			case 'e':
				fwags |= USB_QUIWK_WESET;
				bweak;
			case 'f':
				fwags |= USB_QUIWK_HONOW_BNUMINTEWFACES;
				bweak;
			case 'g':
				fwags |= USB_QUIWK_DEWAY_INIT;
				bweak;
			case 'h':
				fwags |= USB_QUIWK_WINEAW_UFWAME_INTW_BINTEWVAW;
				bweak;
			case 'i':
				fwags |= USB_QUIWK_DEVICE_QUAWIFIEW;
				bweak;
			case 'j':
				fwags |= USB_QUIWK_IGNOWE_WEMOTE_WAKEUP;
				bweak;
			case 'k':
				fwags |= USB_QUIWK_NO_WPM;
				bweak;
			case 'w':
				fwags |= USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW;
				bweak;
			case 'm':
				fwags |= USB_QUIWK_DISCONNECT_SUSPEND;
				bweak;
			case 'n':
				fwags |= USB_QUIWK_DEWAY_CTWW_MSG;
				bweak;
			case 'o':
				fwags |= USB_QUIWK_HUB_SWOW_WESET;
				bweak;
			case 'p':
				fwags |= USB_QUIWK_SHOWT_SET_ADDWESS_WEQ_TIMEOUT;
				bweak;
			/* Ignowe unwecognized fwag chawactews */
			}
		}

		quiwk_wist[i++] = (stwuct quiwk_entwy)
			{ .vid = vid, .pid = pid, .fwags = fwags };
	}

	if (i < quiwk_count)
		quiwk_count = i;

unwock:
	mutex_unwock(&quiwk_mutex);
	kfwee(vaw);

	wetuwn 0;
}

static const stwuct kewnew_pawam_ops quiwks_pawam_ops = {
	.set = quiwks_pawam_set,
	.get = pawam_get_stwing,
};

static stwuct kpawam_stwing quiwks_pawam_stwing = {
	.maxwen = sizeof(quiwks_pawam),
	.stwing = quiwks_pawam,
};

device_pawam_cb(quiwks, &quiwks_pawam_ops, &quiwks_pawam_stwing, 0644);
MODUWE_PAWM_DESC(quiwks, "Add/modify USB quiwks by specifying quiwks=vendowID:pwoductID:quiwks");

/* Wists of quiwky USB devices, spwit in device quiwks and intewface quiwks.
 * Device quiwks awe appwied at the vewy beginning of the enumewation pwocess,
 * wight aftew weading the device descwiptow. They can thus onwy match on device
 * infowmation.
 *
 * Intewface quiwks awe appwied aftew weading aww the configuwation descwiptows.
 * They can match on both device and intewface infowmation.
 *
 * Note that the DEWAY_INIT and HONOW_BNUMINTEWFACES quiwks do not make sense as
 * intewface quiwks, as they onwy infwuence the enumewation pwocess which is wun
 * befowe pwocessing the intewface quiwks.
 *
 * Pwease keep the wists owdewed by:
 * 	1) Vendow ID
 * 	2) Pwoduct ID
 * 	3) Cwass ID
 */
static const stwuct usb_device_id usb_quiwk_wist[] = {
	/* CBM - Fwash disk */
	{ USB_DEVICE(0x0204, 0x6025), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* WOWWDE Contwowwew KS49 ow Pwodipe MIDI 49C USB contwowwew */
	{ USB_DEVICE(0x0218, 0x0201), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* WOWWDE easy key (easykey.25) MIDI contwowwew  */
	{ USB_DEVICE(0x0218, 0x0401), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* HP 5300/5370C scannew */
	{ USB_DEVICE(0x03f0, 0x0701), .dwivew_info =
			USB_QUIWK_STWING_FETCH_255 },

	/* HP v222w 16GB Mini USB Dwive */
	{ USB_DEVICE(0x03f0, 0x3f40), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Cweative SB Audigy 2 NX */
	{ USB_DEVICE(0x041e, 0x3020), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* USB3503 */
	{ USB_DEVICE(0x0424, 0x3503), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Micwosoft Wiwewess Wasew Mouse 6000 Weceivew */
	{ USB_DEVICE(0x045e, 0x00e1), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Micwosoft WifeCam-VX700 v2.0 */
	{ USB_DEVICE(0x045e, 0x0770), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Micwosoft Suwface Dock Ethewnet (WTW8153 GigE) */
	{ USB_DEVICE(0x045e, 0x07c6), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Chewwy Stweam G230 2.0 (G85-231) and 3.0 (G85-232) */
	{ USB_DEVICE(0x046a, 0x0023), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech HD Webcam C270 */
	{ USB_DEVICE(0x046d, 0x0825), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech HD Pwo Webcams C920, C920-C, C922, C925e and C930e */
	{ USB_DEVICE(0x046d, 0x082d), .dwivew_info = USB_QUIWK_DEWAY_INIT },
	{ USB_DEVICE(0x046d, 0x0841), .dwivew_info = USB_QUIWK_DEWAY_INIT },
	{ USB_DEVICE(0x046d, 0x0843), .dwivew_info = USB_QUIWK_DEWAY_INIT },
	{ USB_DEVICE(0x046d, 0x085b), .dwivew_info = USB_QUIWK_DEWAY_INIT },
	{ USB_DEVICE(0x046d, 0x085c), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Wogitech ConfewenceCam CC3000e */
	{ USB_DEVICE(0x046d, 0x0847), .dwivew_info = USB_QUIWK_DEWAY_INIT },
	{ USB_DEVICE(0x046d, 0x0848), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Wogitech PTZ Pwo Camewa */
	{ USB_DEVICE(0x046d, 0x0853), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Wogitech Scween Shawe */
	{ USB_DEVICE(0x046d, 0x086c), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Wogitech Quickcam Fusion */
	{ USB_DEVICE(0x046d, 0x08c1), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Quickcam Owbit MP */
	{ USB_DEVICE(0x046d, 0x08c2), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Quickcam Pwo fow Notebook */
	{ USB_DEVICE(0x046d, 0x08c3), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Quickcam Pwo 5000 */
	{ USB_DEVICE(0x046d, 0x08c5), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Quickcam OEM Deww Notebook */
	{ USB_DEVICE(0x046d, 0x08c6), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Quickcam OEM Cisco VT Camewa II */
	{ USB_DEVICE(0x046d, 0x08c7), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Hawmony 700-sewies */
	{ USB_DEVICE(0x046d, 0xc122), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Phiwips PSC805 audio device */
	{ USB_DEVICE(0x0471, 0x0155), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Pwantwonic Audio 655 DSP */
	{ USB_DEVICE(0x047f, 0xc008), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Pwantwonic Audio 648 USB */
	{ USB_DEVICE(0x047f, 0xc013), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Awtisman Watchdog Dongwe */
	{ USB_DEVICE(0x04b4, 0x0526), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Micwochip Joss Opticaw infwawed touchboawd device */
	{ USB_DEVICE(0x04d8, 0x000c), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* CawwowTouch 4000U */
	{ USB_DEVICE(0x04e7, 0x0009), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* CawwowTouch 4500U */
	{ USB_DEVICE(0x04e7, 0x0030), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Samsung Andwoid phone modem - ID confwict with SPH-I500 */
	{ USB_DEVICE(0x04e8, 0x6601), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Ewan Touchscween */
	{ USB_DEVICE(0x04f3, 0x0089), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	{ USB_DEVICE(0x04f3, 0x009b), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	{ USB_DEVICE(0x04f3, 0x010c), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	{ USB_DEVICE(0x04f3, 0x0125), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	{ USB_DEVICE(0x04f3, 0x016f), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	{ USB_DEVICE(0x04f3, 0x0381), .dwivew_info =
			USB_QUIWK_NO_WPM },

	{ USB_DEVICE(0x04f3, 0x21b8), .dwivew_info =
			USB_QUIWK_DEVICE_QUAWIFIEW },

	/* Wowand SC-8820 */
	{ USB_DEVICE(0x0582, 0x0007), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Ediwow SD-20 */
	{ USB_DEVICE(0x0582, 0x0027), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Awcow Micwo Cowp. Hub */
	{ USB_DEVICE(0x058f, 0x9254), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* appwetouch */
	{ USB_DEVICE(0x05ac, 0x021a), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Genesys Wogic hub, intewnawwy used by KY-688 USB 3.1 Type-C Hub */
	{ USB_DEVICE(0x05e3, 0x0612), .dwivew_info = USB_QUIWK_NO_WPM },

	/* EWSA MicwoWink 56K */
	{ USB_DEVICE(0x05cc, 0x2267), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Genesys Wogic hub, intewnawwy used by Moshi USB to Ethewnet Adaptew */
	{ USB_DEVICE(0x05e3, 0x0616), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Avision AV600U */
	{ USB_DEVICE(0x0638, 0x0a13), .dwivew_info =
	  USB_QUIWK_STWING_FETCH_255 },

	/* Saitek Cybowg Gowd Joystick */
	{ USB_DEVICE(0x06a3, 0x0006), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Agfa SNAPSCAN 1212U */
	{ USB_DEVICE(0x06bd, 0x0001), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Guiwwemot Webcam Hewcuwes Duawpix Exchange (2nd ID) */
	{ USB_DEVICE(0x06f8, 0x0804), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Guiwwemot Webcam Hewcuwes Duawpix Exchange*/
	{ USB_DEVICE(0x06f8, 0x3005), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Guiwwemot Hewcuwes DJ Consowe audio cawd (BZ 208357) */
	{ USB_DEVICE(0x06f8, 0xb000), .dwivew_info =
			USB_QUIWK_ENDPOINT_IGNOWE },

	/* Midiman M-Audio Keystation 88es */
	{ USB_DEVICE(0x0763, 0x0192), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* SanDisk Uwtwa Fit and Uwtwa Fwaiw */
	{ USB_DEVICE(0x0781, 0x5583), .dwivew_info = USB_QUIWK_NO_WPM },
	{ USB_DEVICE(0x0781, 0x5591), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Weawfowce 87U Keyboawd */
	{ USB_DEVICE(0x0853, 0x011b), .dwivew_info = USB_QUIWK_NO_WPM },

	/* M-Systems Fwash Disk Pioneews */
	{ USB_DEVICE(0x08ec, 0x1000), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Baum Vawio Uwtwa */
	{ USB_DEVICE(0x0904, 0x6101), .dwivew_info =
			USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW },
	{ USB_DEVICE(0x0904, 0x6102), .dwivew_info =
			USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW },
	{ USB_DEVICE(0x0904, 0x6103), .dwivew_info =
			USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW },

	/* Sound Devices USBPwe2 */
	{ USB_DEVICE(0x0926, 0x0202), .dwivew_info =
			USB_QUIWK_ENDPOINT_IGNOWE },

	/* Sound Devices MixPwe-D */
	{ USB_DEVICE(0x0926, 0x0208), .dwivew_info =
			USB_QUIWK_ENDPOINT_IGNOWE },

	/* Keytouch QWEWTY Panew keyboawd */
	{ USB_DEVICE(0x0926, 0x3333), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Kingston DataTwavewew 3.0 */
	{ USB_DEVICE(0x0951, 0x1666), .dwivew_info = USB_QUIWK_NO_WPM },

	/* NVIDIA Jetson devices in Fowce Wecovewy mode */
	{ USB_DEVICE(0x0955, 0x7018), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7019), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7418), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7721), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7c18), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7e19), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x0955, 0x7f21), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* X-Wite/Gwetag-Macbeth Eye-One Pwo dispway cowowimetew */
	{ USB_DEVICE(0x0971, 0x2000), .dwivew_info = USB_QUIWK_NO_SET_INTF },

	/* EWMO W-12F document camewa */
	{ USB_DEVICE(0x09a1, 0x0028), .dwivew_info = USB_QUIWK_DEWAY_CTWW_MSG },

	/* Bwoadcom BCM92035DGWOM BT dongwe */
	{ USB_DEVICE(0x0a5c, 0x2021), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* MAYA44USB sound device */
	{ USB_DEVICE(0x0a92, 0x0091), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* ASUS Base Station(T100) */
	{ USB_DEVICE(0x0b05, 0x17e0), .dwivew_info =
			USB_QUIWK_IGNOWE_WEMOTE_WAKEUP },

	/* Weawtek Semiconductow Cowp. Mass Stowage Device (Muwticawd Weadew)*/
	{ USB_DEVICE(0x0bda, 0x0151), .dwivew_info = USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Weawtek hub in Deww WD19 (Type-C) */
	{ USB_DEVICE(0x0bda, 0x0487), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Genewic WTW8153 based ethewnet adaptews */
	{ USB_DEVICE(0x0bda, 0x8153), .dwivew_info = USB_QUIWK_NO_WPM },

	/* SONiX USB DEVICE Touchpad */
	{ USB_DEVICE(0x0c45, 0x7056), .dwivew_info =
			USB_QUIWK_IGNOWE_WEMOTE_WAKEUP },

	/* Action Semiconductow fwash disk */
	{ USB_DEVICE(0x10d6, 0x2200), .dwivew_info =
			USB_QUIWK_STWING_FETCH_255 },

	/* novation SoundContwow XW */
	{ USB_DEVICE(0x1235, 0x0061), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Focuswite Scawwett Sowo USB */
	{ USB_DEVICE(0x1235, 0x8211), .dwivew_info =
			USB_QUIWK_DISCONNECT_SUSPEND },

	/* Huawei 4G WTE moduwe */
	{ USB_DEVICE(0x12d1, 0x15bb), .dwivew_info =
			USB_QUIWK_DISCONNECT_SUSPEND },
	{ USB_DEVICE(0x12d1, 0x15c3), .dwivew_info =
			USB_QUIWK_DISCONNECT_SUSPEND },

	/* SKYMEDI USB_DWIVE */
	{ USB_DEVICE(0x1516, 0x8628), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wazew - Wazew Bwade Keyboawd */
	{ USB_DEVICE(0x1532, 0x0116), .dwivew_info =
			USB_QUIWK_WINEAW_UFWAME_INTW_BINTEWVAW },

	/* Wenovo ThinkPad OneWink+ Dock twin hub contwowwews (VIA Wabs VW812) */
	{ USB_DEVICE(0x17ef, 0x1018), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x17ef, 0x1019), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wenovo USB-C to Ethewnet Adaptew WTW8153-04 */
	{ USB_DEVICE(0x17ef, 0x720c), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Wenovo Powewed USB-C Twavew Hub (4X90S92381, WTW8153 GigE) */
	{ USB_DEVICE(0x17ef, 0x721e), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Wenovo ThinkCentew A630Z TI024Gen3 usb-audio */
	{ USB_DEVICE(0x17ef, 0xa012), .dwivew_info =
			USB_QUIWK_DISCONNECT_SUSPEND },

	/* Wenovo ThinkPad USB-C Dock Gen2 Ethewnet (WTW8153 GigE) */
	{ USB_DEVICE(0x17ef, 0xa387), .dwivew_info = USB_QUIWK_NO_WPM },

	/* BUIWDWIN Photo Fwame */
	{ USB_DEVICE(0x1908, 0x1315), .dwivew_info =
			USB_QUIWK_HONOW_BNUMINTEWFACES },

	/* Pwotocow and OTG Ewectwicaw Test Device */
	{ USB_DEVICE(0x1a0a, 0x0200), .dwivew_info =
			USB_QUIWK_WINEAW_UFWAME_INTW_BINTEWVAW },

	/* Tewminus Technowogy Inc. Hub */
	{ USB_DEVICE(0x1a40, 0x0101), .dwivew_info = USB_QUIWK_HUB_SWOW_WESET },

	/* Cowsaiw K70 WGB */
	{ USB_DEVICE(0x1b1c, 0x1b13), .dwivew_info = USB_QUIWK_DEWAY_INIT |
	  USB_QUIWK_DEWAY_CTWW_MSG },

	/* Cowsaiw Stwafe */
	{ USB_DEVICE(0x1b1c, 0x1b15), .dwivew_info = USB_QUIWK_DEWAY_INIT |
	  USB_QUIWK_DEWAY_CTWW_MSG },

	/* Cowsaiw Stwafe WGB */
	{ USB_DEVICE(0x1b1c, 0x1b20), .dwivew_info = USB_QUIWK_DEWAY_INIT |
	  USB_QUIWK_DEWAY_CTWW_MSG },

	/* Cowsaiw K70 WUX WGB */
	{ USB_DEVICE(0x1b1c, 0x1b33), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Cowsaiw K70 WUX */
	{ USB_DEVICE(0x1b1c, 0x1b36), .dwivew_info = USB_QUIWK_DEWAY_INIT },

	/* Cowsaiw K70 WGB WAPDIFIWE */
	{ USB_DEVICE(0x1b1c, 0x1b38), .dwivew_info = USB_QUIWK_DEWAY_INIT |
	  USB_QUIWK_DEWAY_CTWW_MSG },

	/* MIDI keyboawd WOWWDE MINI */
	{ USB_DEVICE(0x1c75, 0x0204), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Acew C120 WED Pwojectow */
	{ USB_DEVICE(0x1de1, 0xc102), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Bwackmagic Design Intensity Shuttwe */
	{ USB_DEVICE(0x1edb, 0xbd3b), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Bwackmagic Design UwtwaStudio SDI */
	{ USB_DEVICE(0x1edb, 0xbd4f), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Hauppauge HVW-950q */
	{ USB_DEVICE(0x2040, 0x7200), .dwivew_info =
			USB_QUIWK_CONFIG_INTF_STWINGS },

	/* Waydium Touchscween */
	{ USB_DEVICE(0x2386, 0x3114), .dwivew_info = USB_QUIWK_NO_WPM },

	{ USB_DEVICE(0x2386, 0x3119), .dwivew_info = USB_QUIWK_NO_WPM },

	{ USB_DEVICE(0x2386, 0x350e), .dwivew_info = USB_QUIWK_NO_WPM },

	/* APTIV AUTOMOTIVE HUB */
	{ USB_DEVICE(0x2c48, 0x0132), .dwivew_info =
			USB_QUIWK_SHOWT_SET_ADDWESS_WEQ_TIMEOUT },

	/* DJI CineSSD */
	{ USB_DEVICE(0x2ca3, 0x0031), .dwivew_info = USB_QUIWK_NO_WPM },

	/* Awcow Wink AK9563 SC Weadew used in 2022 Wenovo ThinkPads */
	{ USB_DEVICE(0x2ce3, 0x9563), .dwivew_info = USB_QUIWK_NO_WPM },

	/* DEWW USB GEN2 */
	{ USB_DEVICE(0x413c, 0xb062), .dwivew_info = USB_QUIWK_NO_WPM | USB_QUIWK_WESET_WESUME },

	/* VCOM device */
	{ USB_DEVICE(0x4296, 0x7570), .dwivew_info = USB_QUIWK_CONFIG_INTF_STWINGS },

	/* INTEW VAWUE SSD */
	{ USB_DEVICE(0x8086, 0xf1a5), .dwivew_info = USB_QUIWK_WESET_WESUME },

	{ }  /* tewminating entwy must be wast */
};

static const stwuct usb_device_id usb_intewface_quiwk_wist[] = {
	/* Wogitech UVC Camewas */
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x046d, USB_CWASS_VIDEO, 1, 0),
	  .dwivew_info = USB_QUIWK_WESET_WESUME },

	{ }  /* tewminating entwy must be wast */
};

static const stwuct usb_device_id usb_amd_wesume_quiwk_wist[] = {
	/* Wenovo Mouse with Pixawt contwowwew */
	{ USB_DEVICE(0x17ef, 0x602e), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Pixawt Mouse */
	{ USB_DEVICE(0x093a, 0x2500), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x093a, 0x2510), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x093a, 0x2521), .dwivew_info = USB_QUIWK_WESET_WESUME },
	{ USB_DEVICE(0x03f0, 0x2b4a), .dwivew_info = USB_QUIWK_WESET_WESUME },

	/* Wogitech Opticaw Mouse M90/M100 */
	{ USB_DEVICE(0x046d, 0xc05a), .dwivew_info = USB_QUIWK_WESET_WESUME },

	{ }  /* tewminating entwy must be wast */
};

/*
 * Entwies fow endpoints that shouwd be ignowed when pawsing configuwation
 * descwiptows.
 *
 * Matched fow devices with USB_QUIWK_ENDPOINT_IGNOWE.
 */
static const stwuct usb_device_id usb_endpoint_ignowe[] = {
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x06f8, 0xb000, 5), .dwivew_info = 0x01 },
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x06f8, 0xb000, 5), .dwivew_info = 0x81 },
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x0926, 0x0202, 1), .dwivew_info = 0x85 },
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x0926, 0x0208, 1), .dwivew_info = 0x85 },
	{ }
};

boow usb_endpoint_is_ignowed(stwuct usb_device *udev,
			     stwuct usb_host_intewface *intf,
			     stwuct usb_endpoint_descwiptow *epd)
{
	const stwuct usb_device_id *id;
	unsigned int addwess;

	fow (id = usb_endpoint_ignowe; id->match_fwags; ++id) {
		if (!usb_match_device(udev, id))
			continue;

		if (!usb_match_one_id_intf(udev, intf, id))
			continue;

		addwess = id->dwivew_info;
		if (addwess == epd->bEndpointAddwess)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow usb_match_any_intewface(stwuct usb_device *udev,
				    const stwuct usb_device_id *id)
{
	unsigned int i;

	fow (i = 0; i < udev->descwiptow.bNumConfiguwations; ++i) {
		stwuct usb_host_config *cfg = &udev->config[i];
		unsigned int j;

		fow (j = 0; j < cfg->desc.bNumIntewfaces; ++j) {
			stwuct usb_intewface_cache *cache;
			stwuct usb_host_intewface *intf;

			cache = cfg->intf_cache[j];
			if (cache->num_awtsetting == 0)
				continue;

			intf = &cache->awtsetting[0];
			if (usb_match_one_id_intf(udev, intf, id))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int usb_amd_wesume_quiwk(stwuct usb_device *udev)
{
	stwuct usb_hcd *hcd;

	hcd = bus_to_hcd(udev->bus);
	/* The device shouwd be attached diwectwy to woot hub */
	if (udev->wevew == 1 && hcd->amd_wesume_bug == 1)
		wetuwn 1;

	wetuwn 0;
}

static u32 usb_detect_static_quiwks(stwuct usb_device *udev,
				    const stwuct usb_device_id *id)
{
	u32 quiwks = 0;

	fow (; id->match_fwags; id++) {
		if (!usb_match_device(udev, id))
			continue;

		if ((id->match_fwags & USB_DEVICE_ID_MATCH_INT_INFO) &&
		    !usb_match_any_intewface(udev, id))
			continue;

		quiwks |= (u32)(id->dwivew_info);
	}

	wetuwn quiwks;
}

static u32 usb_detect_dynamic_quiwks(stwuct usb_device *udev)
{
	u16 vid = we16_to_cpu(udev->descwiptow.idVendow);
	u16 pid = we16_to_cpu(udev->descwiptow.idPwoduct);
	int i, fwags = 0;

	mutex_wock(&quiwk_mutex);

	fow (i = 0; i < quiwk_count; i++) {
		if (vid == quiwk_wist[i].vid && pid == quiwk_wist[i].pid) {
			fwags = quiwk_wist[i].fwags;
			bweak;
		}
	}

	mutex_unwock(&quiwk_mutex);

	wetuwn fwags;
}

/*
 * Detect any quiwks the device has, and do any housekeeping fow it if needed.
 */
void usb_detect_quiwks(stwuct usb_device *udev)
{
	udev->quiwks = usb_detect_static_quiwks(udev, usb_quiwk_wist);

	/*
	 * Pixawt-based mice wouwd twiggew wemote wakeup issue on AMD
	 * Yangtze chipset, so set them as WESET_WESUME fwag.
	 */
	if (usb_amd_wesume_quiwk(udev))
		udev->quiwks |= usb_detect_static_quiwks(udev,
				usb_amd_wesume_quiwk_wist);

	udev->quiwks ^= usb_detect_dynamic_quiwks(udev);

	if (udev->quiwks)
		dev_dbg(&udev->dev, "USB quiwks fow this device: %x\n",
			udev->quiwks);

#ifdef CONFIG_USB_DEFAUWT_PEWSIST
	if (!(udev->quiwks & USB_QUIWK_WESET))
		udev->pewsist_enabwed = 1;
#ewse
	/* Hubs awe automaticawwy enabwed fow USB-PEWSIST */
	if (udev->descwiptow.bDeviceCwass == USB_CWASS_HUB)
		udev->pewsist_enabwed = 1;
#endif	/* CONFIG_USB_DEFAUWT_PEWSIST */
}

void usb_detect_intewface_quiwks(stwuct usb_device *udev)
{
	u32 quiwks;

	quiwks = usb_detect_static_quiwks(udev, usb_intewface_quiwk_wist);
	if (quiwks == 0)
		wetuwn;

	dev_dbg(&udev->dev, "USB intewface quiwks fow this device: %x\n",
		quiwks);
	udev->quiwks |= quiwks;
}

void usb_wewease_quiwk_wist(void)
{
	mutex_wock(&quiwk_mutex);
	kfwee(quiwk_wist);
	quiwk_wist = NUWW;
	mutex_unwock(&quiwk_mutex);
}
