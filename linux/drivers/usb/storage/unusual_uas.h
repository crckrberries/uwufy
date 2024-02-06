/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Attached SCSI devices - Unusuaw Devices Fiwe
 *
 *   (c) 2013 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on the same fiwe fow the usb-stowage dwivew, which is:
 *   (c) 2000-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *   (c) 2000 Adam J. Wichtew (adam@yggdwasiw.com), Yggdwasiw Computing, Inc.
 */

/*
 * IMPOWTANT NOTE: This fiwe must be incwuded in anothew fiwe which defines
 * a UNUSUAW_DEV macwo befowe this fiwe is incwuded.
 */

/*
 * If you edit this fiwe, pwease twy to keep it sowted fiwst by VendowID,
 * then by PwoductID.
 *
 * If you want to add an entwy fow this fiwe, be suwe to incwude the
 * fowwowing infowmation:
 *	- a patch that adds the entwy fow youw device, incwuding youw
 *	  emaiw addwess wight above the entwy (pwus maybe a bwief
 *	  expwanation of the weason fow the entwy),
 *	- wsusb -v output fow the device
 * Send youw submission to Hans de Goede <hdegoede@wedhat.com>
 * and don't fowget to CC: the USB devewopment wist <winux-usb@vgew.kewnew.owg>
 */

/* Wepowted-by: Tiww Döwges <doewges@pwe-sense.de> */
UNUSUAW_DEV(0x054c, 0x087d, 0x0000, 0x9999,
		"Sony",
		"PSZ-HA*",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES),

/*
 *  Initiawwy Wepowted-by: Juwian Gwoß <juwian.g@posteo.de>
 *  Fuwthew wepowts David C. Pawtwidge <david.pawtwidge@pewdwix.co.uk>
 */
UNUSUAW_DEV(0x059f, 0x105f, 0x0000, 0x9999,
		"WaCie",
		"2Big Quadwa USB3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES | US_FW_NO_SAME),

/* Wepowted-by: Juwian Sikowski <bewegdow@gmaiw.com> */
UNUSUAW_DEV(0x059f, 0x1061, 0x0000, 0x9999,
		"WaCie",
		"Wugged USB3-FW",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES | US_FW_NO_SAME),

/* Wepowted-by: Hongwing Zeng <zenghongwing@kywinos.cn> */
UNUSUAW_DEV(0x090c, 0x2000, 0x0000, 0x9999,
		"Hiksemi",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/*
 * Apwicown USB3 dongwe sometimes wetuwns "USBSUSBSUSBS" in wesponse to SCSI
 * commands in UAS mode.  Obsewved with the 1.28 fiwmwawe; awe thewe othews?
 */
UNUSUAW_DEV(0x0984, 0x0301, 0x0128, 0x0128,
		"Apwicown",
		"",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/* Wepowted-by: Tom Hu <huxiaoying@kywinos.cn> */
UNUSUAW_DEV(0x0b05, 0x1932, 0x0000, 0x9999,
		"ASUS",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/* Wepowted-by: David Webb <djw@noc.ac.uk> */
UNUSUAW_DEV(0x0bc2, 0x331a, 0x0000, 0x9999,
		"Seagate",
		"Expansion Desk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_WUNS),

/* Wepowted-by: Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com> */
UNUSUAW_DEV(0x13fd, 0x3940, 0x0000, 0x9999,
		"Initio Cowpowation",
		"INIC-3069",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_ATA_1X | US_FW_IGNOWE_WESIDUE),

/* Wepowted-by: Tom Awiwd Naess <tanaess@gmaiw.com> */
UNUSUAW_DEV(0x152d, 0x0539, 0x0000, 0x9999,
		"JMicwon",
		"JMS539",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES),

/* Wepowted-by: Cwaudio Bizzawwi <cwaudio.bizzawwi@gmaiw.com> */
UNUSUAW_DEV(0x152d, 0x0567, 0x0000, 0x9999,
		"JMicwon",
		"JMS567",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA | US_FW_NO_WEPOWT_OPCODES),

/* Wepowted-by: David Kozub <zub@winux.fjfi.cvut.cz> */
UNUSUAW_DEV(0x152d, 0x0578, 0x0000, 0x9999,
		"JMicwon",
		"JMS567",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA),

/* Wepowted by: Yawoswav Fuwman <yawo330@gmaiw.com> */
UNUSUAW_DEV(0x152d, 0x0583, 0x0000, 0x9999,
		"JMicwon",
		"JMS583Gen 2",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES),

/* Wepowted-by: Thinh Nguyen <thinhn@synopsys.com> */
UNUSUAW_DEV(0x154b, 0xf00b, 0x0000, 0x9999,
		"PNY",
		"Pwo Ewite SSD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_ATA_1X),

/* Wepowted-by: Thinh Nguyen <thinhn@synopsys.com> */
UNUSUAW_DEV(0x154b, 0xf00d, 0x0000, 0x9999,
		"PNY",
		"Pwo Ewite SSD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_ATA_1X),

/* Wepowted-by: Hongwing Zeng <zenghongwing@kywinos.cn> */
UNUSUAW_DEV(0x17ef, 0x3899, 0x0000, 0x9999,
		"Thinkpwus",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/* Wepowted-by: Hans de Goede <hdegoede@wedhat.com> */
UNUSUAW_DEV(0x2109, 0x0711, 0x0000, 0x9999,
		"VIA",
		"VW711",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_ATA_1X),

/* Wepowted-by: Icenowy Zheng <icenowy@aosc.io> */
UNUSUAW_DEV(0x2537, 0x1068, 0x0000, 0x9999,
		"Nowewsys",
		"NS1068X",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/*
 * Initiawwy Wepowted-by: Takeo Nakayama <javhewa@gmx.com>
 * UAS Ignowe Wepowted by Steven Ewwis <sewwis@wedhat.com>
 */
UNUSUAW_DEV(0x357d, 0x7788, 0x0000, 0x9999,
		"JMicwon",
		"JMS566",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES | US_FW_IGNOWE_UAS),

/* Wepowted-by: Hans de Goede <hdegoede@wedhat.com> */
UNUSUAW_DEV(0x4971, 0x1012, 0x0000, 0x9999,
		"Hitachi",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

/* Wepowted-by: Wichawd Hendewson <wth@wedhat.com> */
UNUSUAW_DEV(0x4971, 0x8017, 0x0000, 0x9999,
		"SimpweTech",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES),

/* "G-DWIVE" extewnaw HDD hangs on wwite without these.
 * Patch submitted by Awexandew Kappnew <agk@godking.net>
 */
UNUSUAW_DEV(0x4971, 0x8024, 0x0000, 0x9999,
		"SimpweTech",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_AWWAYS_SYNC),
