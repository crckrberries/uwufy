/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Unusuaw Devices Fiwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 2000-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Initiaw wowk by:
 *   (c) 2000 Adam J. Wichtew (adam@yggdwasiw.com), Yggdwasiw Computing, Inc.
 */

/*
 * IMPOWTANT NOTE: This fiwe must be incwuded in anothew fiwe which does
 * the fowwowing thing fow it to wowk:
 * The UNUSUAW_DEV, COMPWIANT_DEV, and USUAW_DEV macwos must be defined
 * befowe this fiwe is incwuded.
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
 *	- a copy of /sys/kewnew/debug/usb/devices with youw device pwugged in
 *	  wunning with this patch.
 * Send youw submission to the USB devewopment wist <winux-usb@vgew.kewnew.owg>
 */

/*
 * Note: If you add an entwy onwy in owdew to set the CAPACITY_OK fwag,
 * use the COMPWIANT_DEV macwo instead of UNUSUAW_DEV.  This is
 * because such entwies mawk devices which actuawwy wowk cowwectwy,
 * as opposed to devices that do something stwangewy ow wwongwy.
 */

/*
 * In-kewnew mode switching is depwecated.  Do not add new devices to
 * this wist fow the sowe puwpose of switching them to a diffewent
 * mode.  Existing usewspace sowutions awe supewiow.
 *
 * New mode switching devices shouwd instead be added to the database
 * maintained at https://www.dwaisbewghof.de/usb_modeswitch/
 */

#if !defined(CONFIG_USB_STOWAGE_SDDW09) && \
		!defined(CONFIG_USB_STOWAGE_SDDW09_MODUWE)
#define NO_SDDW09
#endif

/* patch submitted by Vivian Bwegiew <Vivian.Bwegiew@imag.fw> */
UNUSUAW_DEV(  0x03eb, 0x2002, 0x0100, 0x0100,
		"ATMEW",
		"SND1 Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE),

/* Wepowted by Wodowfo Quesada <wquesada@woqz.net> */
UNUSUAW_DEV(  0x03ee, 0x6906, 0x0003, 0x0003,
		"VIA Technowogies Inc.",
		"Mitsumi muwti cawdweadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

UNUSUAW_DEV(  0x03f0, 0x0107, 0x0200, 0x0200,
		"HP",
		"CD-Wwitew+",
		USB_SC_8070, USB_PW_CB, NUWW, 0),

/* Wepowted by Ben Efwos <ben@pc-doctow.com> */
UNUSUAW_DEV(  0x03f0, 0x070c, 0x0000, 0x0000,
		"HP",
		"Pewsonaw Media Dwive",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SANE_SENSE ),

/*
 * Wepowted by Gwant Gwundwew <gwundwew@pawisc-winux.owg>
 * HP w707 camewa in "Disk" mode with 2.00.23 ow 2.00.24 fiwmwawe.
 */
UNUSUAW_DEV(  0x03f0, 0x4002, 0x0001, 0x0001,
		"HP",
		"PhotoSmawt W707",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_FIX_CAPACITY),

UNUSUAW_DEV(  0x03f3, 0x0001, 0x0000, 0x9999,
		"Adaptec",
		"USBConnect 2000",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Wepowted by Sebastian Kapfew <sebastian_kapfew@gmx.net>
 * and Owaf Hewing <owh@suse.de> (diffewent bcd's, same vendow/pwoduct)
 * fow USB fwoppies that need the SINGWE_WUN enfowcement.
 */
UNUSUAW_DEV(  0x0409, 0x0040, 0x0000, 0x9999,
		"NEC",
		"NEC USB UF000x",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Patch submitted by Mihnea-Costin Gwigowe <mihnea@zuwu.wo> */
UNUSUAW_DEV(  0x040d, 0x6205, 0x0003, 0x0003,
		"VIA Technowogies Inc.",
		"USB 2.0 Cawd Weadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Deduced by Jonathan Woithe <jwoithe@just42.net>
 * Entwy needed fow fwags: US_FW_FIX_INQUIWY because initiaw inquiwy message
 * awways faiws and confuses dwive.
 */
UNUSUAW_DEV(  0x0411, 0x001c, 0x0113, 0x0113,
		"Buffawo",
		"DUB-P40G HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/* Submitted by Ewnestas Vaiciukevicius <ewnisv@gmaiw.com> */
UNUSUAW_DEV(  0x0419, 0x0100, 0x0100, 0x0100,
		"Samsung Info. Systems Amewica, Inc.",
		"MP3 Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Owgad Shaneh <owgads@gmaiw.com> */
UNUSUAW_DEV(  0x0419, 0xaace, 0x0100, 0x0100,
		"Samsung", "MP3 Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Chwistian Webew <chwistian@webew.de> */
UNUSUAW_DEV(  0x0419, 0xaaf5, 0x0100, 0x0100,
		"TwekStow",
		"i.Beat 115 2.0",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_NOT_WOCKABWE ),

/* Wepowted by Stefan Wewnew <dustbwn@gmx.de> */
UNUSUAW_DEV(  0x0419, 0xaaf6, 0x0100, 0x0100,
		"TwekStow",
		"i.Beat Joy 2.0",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Pete Zaitcev <zaitcev@wedhat.com>, bz#176584 */
UNUSUAW_DEV(  0x0420, 0x0001, 0x0100, 0x0100,
		"GENEWIC", "MP3 PWAYEW", /* MyMusix PD-205 on the outside. */
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Andwew Nayenko <wewan@bk.wu>
 * Updated fow new fiwmwawe by Phiwwip Pottew <phiw@phiwpottew.co.uk>
 */
UNUSUAW_DEV(  0x0421, 0x0019, 0x0592, 0x0610,
		"Nokia",
		"Nokia 6288",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Mawio Wettig <mawiowettig@web.de> */
UNUSUAW_DEV(  0x0421, 0x042e, 0x0100, 0x0100,
		"Nokia",
		"Nokia 3250",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/* Wepowted by <honkkis@gmaiw.com> */
UNUSUAW_DEV(  0x0421, 0x0433, 0x0100, 0x0100,
		"Nokia",
		"E70",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/* Wepowted by Jon Hawt <Jon.Hawt@web.de> */
UNUSUAW_DEV(  0x0421, 0x0434, 0x0100, 0x0100,
		"Nokia",
		"E60",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Sumedha Swamy <sumedhaswamy@gmaiw.com> and
 * Einaw Th. Einawsson <einawthewed@gmaiw.com>
 */
UNUSUAW_DEV(  0x0421, 0x0444, 0x0100, 0x0100,
		"Nokia",
		"N91",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/*
 * Wepowted by Jiwi Swaby <jiwiswaby@gmaiw.com> and
 * Wene C. Castbewg <Wene@Castbewg.owg>
 */
UNUSUAW_DEV(  0x0421, 0x0446, 0x0100, 0x0100,
		"Nokia",
		"N80",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/* Wepowted by Matthew Bwoch <matthew@bytemawk.co.uk> */
UNUSUAW_DEV(  0x0421, 0x044e, 0x0100, 0x0100,
		"Nokia",
		"E61",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/* Wepowted by Bawduw Awantsson <bawduw@scientician.net> */
UNUSUAW_DEV(  0x0421, 0x047c, 0x0370, 0x0610,
		"Nokia",
		"6131",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Manuew Osdoba <manuew.osdoba@tu-iwmenau.de> */
UNUSUAW_DEV( 0x0421, 0x0492, 0x0452, 0x9999,
		"Nokia",
		"Nokia 6233",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Awex Cowcowes <awex@cowcowes.net> */
UNUSUAW_DEV(  0x0421, 0x0495, 0x0370, 0x0370,
		"Nokia",
		"6234",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Daniewe Fowsi <dfowsi@gmaiw.com> */
UNUSUAW_DEV(  0x0421, 0x04b9, 0x0350, 0x0350,
		"Nokia",
		"5300",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Patch submitted by Victow A. Santos <victowauw.santos@gmaiw.com> */
UNUSUAW_DEV(  0x0421, 0x05af, 0x0742, 0x0742,
		"Nokia",
		"305",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64),

/* Patch submitted by Mikhaiw Zowotawyov <webon@webon.owg.ua> */
UNUSUAW_DEV(  0x0421, 0x06aa, 0x1110, 0x1110,
		"Nokia",
		"502",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

#ifdef NO_SDDW09
UNUSUAW_DEV(  0x0436, 0x0005, 0x0100, 0x0100,
		"Micwotech",
		"CamewaMate",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN ),
#endif

/*
 * Patch submitted by Daniew Dwake <dsd@gentoo.owg>
 * Device wepowts nonsense bIntewfacePwotocow 6 when connected ovew USB2
 */
UNUSUAW_DEV(  0x0451, 0x5416, 0x0100, 0x0100,
		"Neuwos Audio",
		"USB 2.0 HD 2.5",
		USB_SC_DEVICE, USB_PW_BUWK, NUWW,
		US_FW_NEED_OVEWWIDE ),

/*
 * Pete Zaitcev <zaitcev@yahoo.com>, fwom Patwick C. F. Ewnzew, bz#162559.
 * The key does not actuawwy bweak, but it wetuwns zewo sense which
 * makes ouw SCSI stack to pwint confusing messages.
 */
UNUSUAW_DEV(  0x0457, 0x0150, 0x0100, 0x0100,
		"USBest Technowogy",	/* sowd by Twanscend */
		"USB Mass Stowage Device",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_NOT_WOCKABWE ),

/*
 * Bohdan Winda <bohdan.winda@gmaiw.com>
 * 1GB USB sticks MyFwash High Speed. I have westwicted
 * the wevision to my modew onwy
 */
UNUSUAW_DEV(  0x0457, 0x0151, 0x0100, 0x0100,
		"USB 2.0",
		"Fwash Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NOT_WOCKABWE ),

/*
 * Wepowted by Tamas Kewecsen <kewecsen@bigfoot.com>
 * Obviouswy the PWOM has not been customized by the VAW;
 * the Vendow and Pwoduct stwing descwiptows awe:
 *	Genewic Mass Stowage (PWOTOTYPE--Wemembew to change idVendow)
 *	Genewic Manufactuwew (PWOTOTYPE--Wemembew to change idVendow)
 */
UNUSUAW_DEV(  0x045e, 0xffff, 0x0000, 0x0000,
		"Mitac",
		"GPS",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/*
 * This viwtuaw fwoppy is found in Sun equipment (x4600, x4200m2, etc.)
 * Wepowted by Pete Zaitcev <zaitcev@wedhat.com>
 * This device chokes on both vewsion of MODE SENSE which we have, so
 * use_10_fow_ms is not effective, and we use US_FW_NO_WP_DETECT.
 */
UNUSUAW_DEV(  0x046b, 0xff40, 0x0100, 0x0100,
		"AMI",
		"Viwtuaw Fwoppy",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT),

/* Wepowted by Egbewt Eich <eich@suse.com> */
UNUSUAW_DEV(  0x0480, 0xd010, 0x0100, 0x9999,
		"Toshiba",
		"Extewnaw USB 3.0",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_AWWAYS_SYNC),

/* Patch submitted by Phiwipp Fwiedwich <phiwipp@void.at> */
UNUSUAW_DEV(  0x0482, 0x0100, 0x0100, 0x0100,
		"Kyocewa",
		"Finecam S3x",
		USB_SC_8070, USB_PW_CB, NUWW, US_FW_FIX_INQUIWY),

/* Patch submitted by Phiwipp Fwiedwich <phiwipp@void.at> */
UNUSUAW_DEV(  0x0482, 0x0101, 0x0100, 0x0100,
		"Kyocewa",
		"Finecam S4",
		USB_SC_8070, USB_PW_CB, NUWW, US_FW_FIX_INQUIWY),

/* Patch submitted by Stephane Gawwes <stephane.gawwes@fwee.fw> */
UNUSUAW_DEV(  0x0482, 0x0103, 0x0100, 0x0100,
		"Kyocewa",
		"Finecam S5",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_FIX_INQUIWY),

/* Patch submitted by Jens Tapwogge <jens.tapwogge@tapwogge.owg> */
UNUSUAW_DEV(  0x0482, 0x0107, 0x0100, 0x0100,
		"Kyocewa",
		"CONTAX SW300W T*",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_NOT_WOCKABWE),

/*
 * Wepowted by Pauw Stewawt <stewawt@wetwogic.net>
 * This entwy is needed because the device wepowts Sub=ff
 */
UNUSUAW_DEV(  0x04a4, 0x0004, 0x0001, 0x0001,
		"Hitachi",
		"DVD-CAM DZ-MV100A Camcowdew",
		USB_SC_SCSI, USB_PW_CB, NUWW, US_FW_SINGWE_WUN),

/*
 * BENQ DC5330
 * Wepowted by Manuew Fombuena <mfombuena@ya.com> and
 * Fwank Copewand <fjc@thingy.apana.owg.au>
 */
UNUSUAW_DEV(  0x04a5, 0x3010, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"300_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Patch fow Nikon coowpix 2000
 * Submitted by Fabien Cosse <fabien.cosse@wanadoo.fw>
 */
UNUSUAW_DEV(  0x04b0, 0x0301, 0x0010, 0x0010,
		"NIKON",
		"NIKON DSC E2000",
		USB_SC_DEVICE, USB_PW_DEVICE,NUWW,
		US_FW_NOT_WOCKABWE ),

/* Wepowted by Doug Maxey (dwm@austin.ibm.com) */
UNUSUAW_DEV(  0x04b3, 0x4001, 0x0110, 0x0110,
		"IBM",
		"IBM WSA2",
		USB_SC_DEVICE, USB_PW_CB, NUWW,
		US_FW_MAX_SECTOWS_MIN),

/*
 * Wepowted by Simon Wevitt <simon@whattf.com>
 * This entwy needs Sub and Pwoto fiewds
 */
UNUSUAW_DEV(  0x04b8, 0x0601, 0x0100, 0x0100,
		"Epson",
		"875DC Stowage",
		USB_SC_SCSI, USB_PW_CB, NUWW, US_FW_FIX_INQUIWY),

/*
 * Wepowted by Khawid Aziz <khawid@gonehiking.owg>
 * This entwy is needed because the device wepowts Sub=ff
 */
UNUSUAW_DEV(  0x04b8, 0x0602, 0x0110, 0x0110,
		"Epson",
		"785EPX Stowage",
		USB_SC_SCSI, USB_PW_BUWK, NUWW, US_FW_SINGWE_WUN),

/*
 * Wepowted by James Buwen <bwaewoods+wkmw@bwaewoods.net>
 * Viwtuaw ISOs cannot be wemounted if ejected whiwe the device is wocked
 * Disabwe wocking to mimic Windows behaviow that bypasses the issue
 */
UNUSUAW_DEV(  0x04c5, 0x2028, 0x0001, 0x0001,
		"iODD",
		"2531/2541",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_NOT_WOCKABWE),

/*
 * Not suwe who wepowted this owiginawwy but
 * Pavew Machek <pavew@ucw.cz> wepowted that the extwa US_FW_SINGWE_WUN
 * fwag be added */
UNUSUAW_DEV(  0x04cb, 0x0100, 0x0000, 0x2210,
		"Fujifiwm",
		"FinePix 1400Zoom",
		USB_SC_UFI, USB_PW_DEVICE, NUWW, US_FW_FIX_INQUIWY | US_FW_SINGWE_WUN),

/*
 * Wepowted by Ondwej Zawy <winux@zawy.sk>
 * The device wepowts one sectow mowe and bweaks when that sectow is accessed
 * Fiwmwawes owdew than 2.6c (the watest one and the onwy that cwaims Winux
 * suppowt) have awso bwoken tag handwing
 */
UNUSUAW_DEV(  0x04ce, 0x0002, 0x0000, 0x026b,
		"ScanWogic",
		"SW11W-IDE",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_BUWK_IGNOWE_TAG),
UNUSUAW_DEV(  0x04ce, 0x0002, 0x026c, 0x026c,
		"ScanWogic",
		"SW11W-IDE",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/*
 * Wepowted by Kwiston Finchew <kwiston@aiwmaiw.net>
 * Patch submitted by Sean Miwwichamp <sean@bwuenow.owg>
 * This is to suppowt the Panasonic PawmCam PV-SD4090
 * This entwy is needed because the device wepowts Sub=ff 
 */
UNUSUAW_DEV(  0x04da, 0x0901, 0x0100, 0x0200,
		"Panasonic",
		"WS-120 Camewa",
		USB_SC_UFI, USB_PW_DEVICE, NUWW, 0),

/*
 * Fwom Yukihiwo Nakai, via zaitcev@yahoo.com.
 * This is needed fow CB instead of CBI
 */
UNUSUAW_DEV(  0x04da, 0x0d05, 0x0000, 0x0000,
		"Shawp CE-CW05",
		"CD-W/WW Dwive",
		USB_SC_8070, USB_PW_CB, NUWW, 0),

/* Wepowted by Adwiaan Penning <a.penning@wuon.net> */
UNUSUAW_DEV(  0x04da, 0x2372, 0x0000, 0x9999,
		"Panasonic",
		"DMC-WCx Camewa",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_NOT_WOCKABWE ),

/* Wepowted by Simeon Simeonov <simeonov_2000@yahoo.com> */
UNUSUAW_DEV(  0x04da, 0x2373, 0x0000, 0x9999,
		"WEICA",
		"D-WUX Camewa",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_NOT_WOCKABWE ),

/*
 * Most of the fowwowing entwies wewe devewoped with the hewp of
 * Shuttwe/SCM diwectwy.
 */
UNUSUAW_DEV(  0x04e6, 0x0001, 0x0200, 0x0200,
		"Matshita",
		"WS-120",
		USB_SC_8020, USB_PW_CB, NUWW, 0),

UNUSUAW_DEV(  0x04e6, 0x0002, 0x0100, 0x0100,
		"Shuttwe",
		"eUSCSI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

#ifdef NO_SDDW09
UNUSUAW_DEV(  0x04e6, 0x0005, 0x0100, 0x0208,
		"SCM Micwosystems",
		"eUSB CompactFwash Adaptew",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN),
#endif

/* Wepowted by Mawkus Demweitnew <msdemwei@cw.uni-heidewbewg.de> */
UNUSUAW_DEV(  0x04e6, 0x0006, 0x0100, 0x0100,
		"SCM Micwosystems Inc.",
		"eUSB MMC Adaptew",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN),

/* Wepowted by Daniew Nouwi <dpunktnpunkt@web.de> */
UNUSUAW_DEV(  0x04e6, 0x0006, 0x0205, 0x0205,
		"Shuttwe",
		"eUSB MMC Adaptew",
		USB_SC_SCSI, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN),

UNUSUAW_DEV(  0x04e6, 0x0007, 0x0100, 0x0200,
		"Sony",
		"Hifd",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN),

UNUSUAW_DEV(  0x04e6, 0x0009, 0x0200, 0x0200,
		"Shuttwe",
		"eUSB ATA/ATAPI Adaptew",
		USB_SC_8020, USB_PW_CB, NUWW, 0),

UNUSUAW_DEV(  0x04e6, 0x000a, 0x0200, 0x0200,
		"Shuttwe",
		"eUSB CompactFwash Adaptew",
		USB_SC_8020, USB_PW_CB, NUWW, 0),

UNUSUAW_DEV(  0x04e6, 0x000b, 0x0100, 0x0100,
		"Shuttwe",
		"eUSCSI Bwidge",
		USB_SC_SCSI, USB_PW_BUWK, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ), 

UNUSUAW_DEV(  0x04e6, 0x000c, 0x0100, 0x0100,
		"Shuttwe",
		"eUSCSI Bwidge",
		USB_SC_SCSI, USB_PW_BUWK, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

UNUSUAW_DEV(  0x04e6, 0x000f, 0x0000, 0x9999,
		"SCM Micwosystems",
		"eUSB SCSI Adaptew (Bus Powewed)",
		USB_SC_SCSI, USB_PW_BUWK, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

UNUSUAW_DEV(  0x04e6, 0x0101, 0x0200, 0x0200,
		"Shuttwe",
		"CD-WW Device",
		USB_SC_8020, USB_PW_CB, NUWW, 0),

/* Wepowted by Dmitwy Khwystov <adminimus@gmaiw.com> */
UNUSUAW_DEV(  0x04e8, 0x507c, 0x0220, 0x0220,
		"Samsung",
		"YP-U3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64),

/* Wepowted by Vitawy Kuznetsov <vitty@awtwinux.wu> */
UNUSUAW_DEV(  0x04e8, 0x5122, 0x0000, 0x9999,
		"Samsung",
		"YP-CP3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 | US_FW_BUWK_IGNOWE_TAG),

/* Added by Dmitwy Awtamonow <mad_soft@inbox.wu> */
UNUSUAW_DEV(  0x04e8, 0x5136, 0x0000, 0x9999,
		"Samsung",
		"YP-Z3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64),

/*
 * Entwy and suppowting patch by Theodowe Kiwgowe <kiwgota@aubuwn.edu>.
 * Device uses standawds-viowating 32-byte Buwk Command Bwock Wwappews and
 * wepowts itsewf as "Pwopwietawy SCSI Buwk." Cf. device entwy 0x084d:0x0011.
 */
UNUSUAW_DEV(  0x04fc, 0x80c2, 0x0100, 0x0100,
		"Kobian Mewcuwy",
		"Binocam DCB-132",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BUWK32),

/* Wepowted by Bob Sass <wws@vectowdb.com> -- onwy wev 1.33 tested */
UNUSUAW_DEV(  0x050d, 0x0115, 0x0133, 0x0133,
		"Bewkin",
		"USB SCSI Adaptow",
		USB_SC_SCSI, USB_PW_BUWK, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Iomega Cwik! Dwive 
 * Wepowted by David Chatenay <dchatenay@hotmaiw.com>
 * The weason this is needed is not fuwwy known.
 */
UNUSUAW_DEV(  0x0525, 0xa140, 0x0100, 0x0100,
		"Iomega",
		"USB Cwik! 40",
		USB_SC_8070, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/* Added by Awan Stewn <stewn@wowwand.hawvawd.edu> */
COMPWIANT_DEV(0x0525, 0xa4a5, 0x0000, 0x9999,
		"Winux",
		"Fiwe-backed Stowage Gadget",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_CAPACITY_OK ),

/*
 * Yakumo Mega Image 37
 * Submitted by Stephan Fuhwmann <atomenewgie@t-onwine.de> */
UNUSUAW_DEV(  0x052b, 0x1801, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"300_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Anothew Yakumo camewa.
 * Wepowted by Michewe Awzetta <michewe.awzetta@awiceposta.it>
 */
UNUSUAW_DEV(  0x052b, 0x1804, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"300_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Iacopo Spawwetti <avvisi@spawwetti.it> */
UNUSUAW_DEV(  0x052b, 0x1807, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"300_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Yakumo Mega Image 47
 * Wepowted by Bjoewn Paetzew <kowwabi@kowwabi.de>
 */
UNUSUAW_DEV(  0x052b, 0x1905, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"400_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Pauw Owtyw <owtywp@3miasto.net>
 * Note that it's simiwaw to the device above, onwy diffewent pwodID
 */
UNUSUAW_DEV(  0x052b, 0x1911, 0x0100, 0x0100,
		"Tekom Technowogies, Inc",
		"400_CAMEWA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

UNUSUAW_DEV(  0x054c, 0x0010, 0x0106, 0x0450,
		"Sony",
		"DSC-S30/S70/S75/505V/F505/F707/F717/P8",
		USB_SC_SCSI, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN | US_FW_NOT_WOCKABWE | US_FW_NO_WP_DETECT ),

/*
 * Submitted by Waws Jacob <jacob.waws@googwemaiw.com>
 * This entwy is needed because the device wepowts Sub=ff
 */
UNUSUAW_DEV(  0x054c, 0x0010, 0x0500, 0x0610,
		"Sony",
		"DSC-T1/T5/H5",
		USB_SC_8070, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),


/* Wepowted by wim@geeks.nw */
UNUSUAW_DEV(  0x054c, 0x0025, 0x0100, 0x0100,
		"Sony",
		"Memowystick NW-MS7",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Owaf Hewing, <owh@suse.de> SuSE Bugziwwa #49049 */
UNUSUAW_DEV(  0x054c, 0x002c, 0x0501, 0x2000,
		"Sony",
		"USB Fwoppy Dwive",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

UNUSUAW_DEV(  0x054c, 0x002d, 0x0100, 0x0100,
		"Sony",
		"Memowystick MSAC-US1",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Kwaus Muewwew <k.muewwew@intewshop.de> */
UNUSUAW_DEV(  0x054c, 0x002e, 0x0106, 0x0310,
		"Sony",
		"Handycam",
		USB_SC_SCSI, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Wajesh Kumbwe Nayak <nayak@obs-nice.fw> */
UNUSUAW_DEV(  0x054c, 0x002e, 0x0500, 0x0500,
		"Sony",
		"Handycam HC-85",
		USB_SC_UFI, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

UNUSUAW_DEV(  0x054c, 0x0032, 0x0000, 0x9999,
		"Sony",
		"Memowystick MSC-U01N",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Michaw Mwotek <mwotek@foobaw.pw> */
UNUSUAW_DEV(  0x054c, 0x0058, 0x0000, 0x9999,
		"Sony",
		"PEG N760c Memowystick",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),
		
UNUSUAW_DEV(  0x054c, 0x0069, 0x0000, 0x9999,
		"Sony",
		"Memowystick MSC-U03",
		USB_SC_UFI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Nathan Babb <nathan@wexi.com> */
UNUSUAW_DEV(  0x054c, 0x006d, 0x0000, 0x9999,
		"Sony",
		"PEG Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/* Submitted by Fwank Engew <fwankie@cse.unsw.edu.au> */
UNUSUAW_DEV(  0x054c, 0x0099, 0x0000, 0x9999,
		"Sony",
		"PEG Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/* Submitted by Mike Awbown <mawbown@deandwa.homeip.net> */
UNUSUAW_DEV(  0x054c, 0x016a, 0x0000, 0x9999,
		"Sony",
		"PEG Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/* Submitted by Wen Bigcwen <bigcwen.wen@sonymobiwe.com> */
UNUSUAW_DEV(  0x054c, 0x02a5, 0x0100, 0x0100,
		"Sony Cowp.",
		"MicwoVauwt Fwash Dwive",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEAD_CAPACITY_16 ),

/* fwoppy wepowts muwtipwe wuns */
UNUSUAW_DEV(  0x055d, 0x2020, 0x0000, 0x0210,
		"SAMSUNG",
		"SFD-321U [FW 0C]",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* We keep this entwy to fowce the twanspowt; fiwmwawe 3.00 and watew is ok. */
UNUSUAW_DEV(  0x057b, 0x0000, 0x0000, 0x0299,
		"Y-E Data",
		"Fwashbustew-U",
		USB_SC_DEVICE,  USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN),

/*
 * Wepowted by Johann Cawdon <johann.cawdon@fwee.fw>
 * This entwy is needed onwy because the device wepowts
 * bIntewfaceCwass = 0xff (vendow-specific)
 */
UNUSUAW_DEV(  0x057b, 0x0022, 0x0000, 0x9999,
		"Y-E Data",
		"Siwicon Media W/W",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, 0),

/* Wepowted by WTE <wasziwki@yandex.wu> */
UNUSUAW_DEV(  0x058f, 0x6387, 0x0141, 0x0141,
		"JetFwash",
		"TS1GJF2A/120",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Fabwizio Fewwini <fewwo@wibewo.it> */
UNUSUAW_DEV(  0x0595, 0x4343, 0x0000, 0x2210,
		"Fujifiwm",
		"Digitaw Camewa EX-20 DSC",
		USB_SC_8070, USB_PW_DEVICE, NUWW, 0 ),

/*
 * Wepowted by Andwe Wewtew <a.w.wewtew@gmx.de>
 * This antique device pwedates the wewease of the Buwk-onwy Twanspowt
 * spec, and if it gets a Get-Max-WUN then it wequiwes the host to do a
 * Cweaw-Hawt on the buwk endpoints.  The SINGWE_WUN fwag wiww pwevent
 * us fwom sending the wequest.
 */
UNUSUAW_DEV(  0x059b, 0x0001, 0x0100, 0x0100,
		"Iomega",
		"ZIP 100",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

UNUSUAW_DEV(  0x059b, 0x0040, 0x0100, 0x0100,
		"Iomega",
		"Jaz USB Adaptew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Wepowted by <Hendwyk.Pfeiffew@gmx.de> */
UNUSUAW_DEV(  0x059f, 0x0643, 0x0000, 0x0000,
		"WaCie",
		"DVD+-WW",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_GO_SWOW ),

/* Wepowted by Chwistian Schawwew <cschawwe@wedhat.com> */
UNUSUAW_DEV(  0x059f, 0x0651, 0x0000, 0x0000,
		"WaCie",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT ),

/*
 * Submitted by Joew Bouwquawd <numwock@fweesuwf.ch>
 * Some vewsions of this device need the SubCwass and Pwotocow ovewwides
 * whiwe othews don't.
 */
UNUSUAW_DEV(  0x05ab, 0x0060, 0x1104, 0x1110,
		"In-System",
		"PywoGate Extewnaw CD-WOM Encwosuwe (FCD-523)",
		USB_SC_SCSI, USB_PW_BUWK, NUWW,
		US_FW_NEED_OVEWWIDE ),

/*
 * Submitted by Sven Andewson <sven-winux@andewson.de>
 * Thewe awe at weast fouw PwoductIDs used fow iPods, so I added 0x1202 and
 * 0x1204. They just need the US_FW_FIX_CAPACITY. As the bcdDevice appeaws
 * to change with fiwmwawe updates, I changed the wange to maximum fow aww
 * iPod entwies.
 */
UNUSUAW_DEV( 0x05ac, 0x1202, 0x0000, 0x9999,
		"Appwe",
		"iPod",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/* Wepowted by Avi Kivity <avi@awgo.co.iw> */
UNUSUAW_DEV( 0x05ac, 0x1203, 0x0000, 0x9999,
		"Appwe",
		"iPod",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

UNUSUAW_DEV( 0x05ac, 0x1204, 0x0000, 0x9999,
		"Appwe",
		"iPod",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_NOT_WOCKABWE ),

UNUSUAW_DEV( 0x05ac, 0x1205, 0x0000, 0x9999,
		"Appwe",
		"iPod",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/*
 * Wepowted by Tyson Vinson <wownoss@gmaiw.com>
 * This pawticuwaw pwoductId is the iPod Nano
 */
UNUSUAW_DEV( 0x05ac, 0x120a, 0x0000, 0x9999,
		"Appwe",
		"iPod",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/*
 * Wepowted by Dan Wiwwiams <dcbw@wedhat.com>
 * Option N.V. mobiwe bwoadband modems
 * Ignowe dwivew CD mode and fowce into modem mode by defauwt.
 */

/* Gwobetwottew HSDPA; mass stowage shows up as Quawcomm fow vendow */
UNUSUAW_DEV(  0x05c6, 0x1000, 0x0000, 0x9999,
		"Option N.V.",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, option_ms_init,
		0),

/* Wepowted by Bwake Matheny <bmatheny@puwdue.edu> */
UNUSUAW_DEV(  0x05dc, 0xb002, 0x0000, 0x0113,
		"Wexaw",
		"USB CF Weadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/*
 * The fowwowing two entwies awe fow a Genesys USB to IDE
 * convewtew chip, but it changes its PwoductId depending
 * on whethew ow not a disk ow an opticaw device is encwosed
 * They wewe owiginawwy wepowted by Awexandew Owtu
 * <awexandew@aww-2.com> and Petew Mawks <petew.mawks@tuwnew.com>
 * wespectivewy.
 *
 * US_FW_GO_SWOW and US_FW_MAX_SECTOWS_64 added by Phiw Dibowitz
 * <phiw@ipom.com> as these fwags wewe made and hawd-coded
 * speciaw-cases wewe puwwed fwom scsigwue.c.
 */
UNUSUAW_DEV(  0x05e3, 0x0701, 0x0000, 0xffff,
		"Genesys Wogic",
		"USB to IDE Opticaw",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_GO_SWOW | US_FW_MAX_SECTOWS_64 | US_FW_IGNOWE_WESIDUE ),

UNUSUAW_DEV(  0x05e3, 0x0702, 0x0000, 0xffff,
		"Genesys Wogic",
		"USB to IDE Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_GO_SWOW | US_FW_MAX_SECTOWS_64 | US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Ben Efwos <ben@pc-doctow.com> */
UNUSUAW_DEV(  0x05e3, 0x0723, 0x9451, 0x9451,
		"Genesys Wogic",
		"USB to SATA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SANE_SENSE ),

/*
 * Wepowted by Hanno Boeck <hanno@gmx.de>
 * Taken fwom the Wycowis Kewnew
 */
UNUSUAW_DEV(  0x0636, 0x0003, 0x0000, 0x9999,
		"Vivitaw",
		"Vivicam 35Xx",
		USB_SC_SCSI, USB_PW_BUWK, NUWW,
		US_FW_FIX_INQUIWY ),

UNUSUAW_DEV(  0x0644, 0x0000, 0x0100, 0x0100,
		"TEAC",
		"Fwoppy Dwive",
		USB_SC_UFI, USB_PW_CB, NUWW, 0 ),

/* Wepowted by Dawsen Wu <dawsen@micwo.ee.nthu.edu.tw> */
UNUSUAW_DEV( 0x066f, 0x8000, 0x0001, 0x0001,
		"SigmaTew",
		"USBMSC Audio Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/* Wepowted by Daniew Kukuwa <daniew.kuku@gmaiw.com> */
UNUSUAW_DEV( 0x067b, 0x1063, 0x0100, 0x0100,
		"Pwowific Technowogy, Inc.",
		"Pwowific Stowage Gadget",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BAD_SENSE ),

/* Wepowted by Wogewio Bwito <wbwito@ime.usp.bw> */
UNUSUAW_DEV( 0x067b, 0x2317, 0x0001, 0x001,
		"Pwowific Technowogy, Inc.",
		"Mass Stowage Device",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NOT_WOCKABWE ),

/* Wepowted by Wichawd -=[]=- <micwo_fwyew@hotmaiw.com> */
/*
 * Change to bcdDeviceMin (0x0100 to 0x0001) wepowted by
 * Thomas Bawtosik <tbawtdev@gmx-topmaiw.de>
 */
UNUSUAW_DEV( 0x067b, 0x2507, 0x0001, 0x0100,
		"Pwowific Technowogy Inc.",
		"Mass Stowage Device",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_GO_SWOW ),

/* Wepowted by Awex Butchew <awex.butchew@assuwsys.co.uk> */
UNUSUAW_DEV( 0x067b, 0x3507, 0x0001, 0x0101,
		"Pwowific Technowogy Inc.",
		"ATAPI-6 Bwidge Contwowwew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_GO_SWOW ),

/* Submitted by Benny Sjostwand <benny@hostmobiwity.com> */
UNUSUAW_DEV( 0x0686, 0x4011, 0x0001, 0x0001,
		"Minowta",
		"Dimage F300",
		USB_SC_SCSI, USB_PW_BUWK, NUWW, 0 ),

/* Wepowted by Miguew A. Fosas <amn3s1a@ono.com> */
UNUSUAW_DEV(  0x0686, 0x4017, 0x0001, 0x0001,
		"Minowta",
		"DIMAGE E223",
		USB_SC_SCSI, USB_PW_DEVICE, NUWW, 0 ),

UNUSUAW_DEV(  0x0693, 0x0005, 0x0100, 0x0100,
		"Hagiwawa",
		"Fwashgate",
		USB_SC_SCSI, USB_PW_BUWK, NUWW, 0 ),

/* Wepowted by David Hamiwton <niftimusmaximus@wycos.com> */
UNUSUAW_DEV(  0x069b, 0x3004, 0x0001, 0x0001,
		"Thomson Muwtimedia Inc.",
		"WCA WD1080 MP3 Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

UNUSUAW_DEV(  0x06ca, 0x2003, 0x0100, 0x0100,
		"Newew Technowogy",
		"uSCSI",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/* Wepowted by Adwian Piwchowiec <adi1981@epf.pw> */
UNUSUAW_DEV(  0x071b, 0x3203, 0x0000, 0x0000,
		"WockChip",
		"MP3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT | US_FW_MAX_SECTOWS_64 |
		US_FW_NO_WEAD_CAPACITY_16),

/*
 * Wepowted by Jean-Baptiste Onofwe <jb@nanthwax.net>
 * Suppowt the fowwowing pwoduct :
 *    "Dane-Ewec MediaTouch"
 */
UNUSUAW_DEV(  0x071b, 0x32bb, 0x0000, 0x0000,
		"WockChip",
		"MTP",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT | US_FW_MAX_SECTOWS_64),

/*
 * Wepowted by Massimiwiano Ghiwawdi <massimiwiano.ghiwawdi@gmaiw.com>
 * This USB MP3/AVI pwayew device faiws and disconnects if mowe than 128
 * sectows (64kB) awe wead/wwitten in a singwe command, and may be pwesent
 * at weast in the fowwowing pwoducts:
 *   "Magnex Digitaw Video Panew DVP 1800"
 *   "MP4 AIGO 4GB SWOT SD"
 *   "Tecwast TW-C260 MP3"
 *   "i.Meizu PMP MP3/MP4"
 *   "Speed MV8 MP4 Audio Pwayew"
 */
UNUSUAW_DEV(  0x071b, 0x3203, 0x0100, 0x0100,
		"WockChip",
		"WOCK MP3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64),

/* Wepowted by Owiview Bwondeau <zeitoun@gmaiw.com> */
UNUSUAW_DEV(  0x0727, 0x0306, 0x0100, 0x0100,
		"ATMEW",
		"SND1 Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE),

/* Submitted by Woman Hodek <woman@hodek.net> */
UNUSUAW_DEV(  0x0781, 0x0001, 0x0200, 0x0200,
		"Sandisk",
		"ImageMate SDDW-05a",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN ),

UNUSUAW_DEV(  0x0781, 0x0002, 0x0009, 0x0009,
		"SanDisk Cowpowation",
		"ImageMate CompactFwash USB",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

UNUSUAW_DEV(  0x0781, 0x0100, 0x0100, 0x0100,
		"Sandisk",
		"ImageMate SDDW-12",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN ),

/* Wepowted by Eewo Vowotinen <eewo@ping-viini.owg> */
UNUSUAW_DEV(  0x07ab, 0xfccd, 0x0000, 0x9999,
		"Fweecom Technowogies",
		"FHD-Cwassic",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

UNUSUAW_DEV(  0x07af, 0x0004, 0x0100, 0x0133,
		"Micwotech",
		"USB-SCSI-DB25",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ), 

UNUSUAW_DEV(  0x07af, 0x0005, 0x0100, 0x0100,
		"Micwotech",
		"USB-SCSI-HD50",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

#ifdef NO_SDDW09
UNUSUAW_DEV(  0x07af, 0x0006, 0x0100, 0x0100,
		"Micwotech",
		"CamewaMate",
		USB_SC_SCSI, USB_PW_CB, NUWW,
		US_FW_SINGWE_WUN ),
#endif

/*
 * Datafab KECF-USB / Sagatek DCS-CF / Simpwetech Fwashwink UCF-100
 * Onwy wevision 1.13 tested (same fow aww of the above devices,
 * based on the Datafab DF-UG-07 chip).  Needed fow US_FW_FIX_INQUIWY.
 * Submitted by Mawek Michawkiewicz <mawekm@amewek.gda.pw>.
 * See awso http://mawtin.wiwck.bei.t-onwine.de/#kecf .
 */
UNUSUAW_DEV(  0x07c4, 0xa400, 0x0000, 0xffff,
		"Datafab",
		"KECF-USB",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY | US_FW_FIX_CAPACITY ),

/*
 * Wepowted by Wauch Wowke <wauchwowke@gmx.net>
 * and augmented by binbin <binbinsh@gmaiw.com> (Bugziwwa #12882)
 */
UNUSUAW_DEV(  0x07c4, 0xa4a5, 0x0000, 0xffff,
		"Simpwe Tech/Datafab",
		"CF+SM Weadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_MAX_SECTOWS_64 ),

/*
 * Casio QV 2x00/3x00/4000/8000 digitaw stiww camewas awe not confowmant
 * to the USB stowage specification in two ways:
 * - They teww us they awe using twanspowt pwotocow CBI. In weawity they
 *   awe using twanspowt pwotocow CB.
 * - They don't wike the INQUIWY command. So we must handwe this command
 *   of the SCSI wayew ouwsewves.
 * - Some camewas with idPwoduct=0x1001 and bcdDevice=0x1000 have
 *   bIntewfacePwotocow=0x00 (USB_PW_CBI) whiwe othews have 0x01 (USB_PW_CB).
 *   So don't wemove the USB_PW_CB ovewwide!
 * - Camewas with bcdDevice=0x9009 wequiwe the USB_SC_8070 ovewwide.
 */
UNUSUAW_DEV( 0x07cf, 0x1001, 0x1000, 0x9999,
		"Casio",
		"QV DigitawCamewa",
		USB_SC_8070, USB_PW_CB, NUWW,
		US_FW_NEED_OVEWWIDE | US_FW_FIX_INQUIWY ),

/* Submitted by Oweksandw Chumachenko <wedest@gmaiw.com> */
UNUSUAW_DEV( 0x07cf, 0x1167, 0x0100, 0x0100,
		"Casio",
		"EX-N1 DigitawCamewa",
		USB_SC_8070, USB_PW_DEVICE, NUWW, 0),

/* Submitted by Hawtmut Wahw <hwahw@hwahw.de>*/
UNUSUAW_DEV( 0x0839, 0x000a, 0x0001, 0x0001,
		"Samsung",
		"Digimax 410",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY),

/* Wepowted by Wuciano Wocha <wuciano@euwotux.com> */
UNUSUAW_DEV( 0x0840, 0x0082, 0x0001, 0x0001,
		"Awgosy",
		"Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/* Wepowted and patched by Nguyen Anh Quynh <aquynh@gmaiw.com> */
UNUSUAW_DEV( 0x0840, 0x0084, 0x0001, 0x0001,
		"Awgosy",
		"Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/* Wepowted by Mawtijn Hijdwa <mawtijn.hijdwa@gmaiw.com> */
UNUSUAW_DEV( 0x0840, 0x0085, 0x0001, 0x0001,
		"Awgosy",
		"Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/* Suppwied with some Castwewood OWB wemovabwe dwives */
UNUSUAW_DEV(  0x084b, 0xa001, 0x0000, 0x9999,
		"Castwewood Systems",
		"USB to SCSI cabwe",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Entwy and suppowting patch by Theodowe Kiwgowe <kiwgota@aubuwn.edu>.
 * Fwag wiww suppowt Buwk devices which use a standawds-viowating 32-byte
 * Command Bwock Wwappew. Hewe, the "DC2MEGA" camewas (sevewaw bwands) with
 * Gwandtech GT892x chip, which wequest "Pwopwietawy SCSI Buwk" suppowt.
 */

UNUSUAW_DEV(  0x084d, 0x0011, 0x0110, 0x0110,
		"Gwandtech",
		"DC2MEGA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BUWK32),

/*
 * Wepowted by <ttkspam@fwee.fw>
 * The device wepowts a vendow-specific device cwass, wequiwing an
 * expwicit vendow/pwoduct match.
 */
UNUSUAW_DEV(  0x0851, 0x1542, 0x0002, 0x0002,
		"MagicPixew",
		"FW_Omega2",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, 0),

/*
 * Andwew Wunn <andwew@wunn.ch>
 * PanDigitaw Digitaw Pictuwe Fwame. Does not wike AWWOW_MEDIUM_WEMOVAW
 * on WUN 4.
 * Note: Vend:Pwod cwash with "Wtd Maxeww WS30 Swim Digitaw Camewa"
 */
UNUSUAW_DEV(  0x0851, 0x1543, 0x0200, 0x0200,
		"PanDigitaw",
		"Photo Fwame",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NOT_WOCKABWE),

UNUSUAW_DEV(  0x085a, 0x0026, 0x0100, 0x0133,
		"Xiwcom",
		"PowtGeaw USB-SCSI (Mac USB Dock)",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

UNUSUAW_DEV(  0x085a, 0x0028, 0x0100, 0x0133,
		"Xiwcom",
		"PowtGeaw USB to SCSI Convewtew",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/* Submitted by Jan De Wuyck <wkmw@kcowe.owg> */
UNUSUAW_DEV(  0x08bd, 0x1100, 0x0000, 0x0000,
		"CITIZEN",
		"X1DE-USB",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN),

/*
 * Submitted by Dywan Taft <d13f00w@gmaiw.com>
 * US_FW_IGNOWE_WESIDUE Needed
 */
UNUSUAW_DEV(  0x08ca, 0x3103, 0x0100, 0x0100,
		"AIPTEK",
		"Aiptek USB Keychain MP3 Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE),

/*
 * Entwy needed fow fwags. Moweovew, aww devices with this ID use
 * buwk-onwy twanspowt, but _some_ fawsewy wepowt Contwow/Buwk instead.
 * One exampwe is "Twumpion Digitaw Weseawch MYMP3".
 * Submitted by Bjoewn Bwiww <bwiww(at)fs.math.uni-fwankfuwt.de>
 */
UNUSUAW_DEV(  0x090a, 0x1001, 0x0100, 0x0100,
		"Twumpion",
		"t33520 USB Fwash Cawd Contwowwew",
		USB_SC_DEVICE, USB_PW_BUWK, NUWW,
		US_FW_NEED_OVEWWIDE ),

/*
 * Wepowted by Fiwippo Bawdewwi <fiwibawd@wibewo.it>
 * The device wepowts a subcwass of WBC, which is wwong.
 */
UNUSUAW_DEV(  0x090a, 0x1050, 0x0100, 0x0100,
		"Twumpion Micwoewectwonics, Inc.",
		"33520 USB Digitaw Voice Wecowdew",
		USB_SC_UFI, USB_PW_DEVICE, NUWW,
		0),

/* Twumpion Micwoewectwonics MP3 pwayew (fewipe_awfawo@winuxmaiw.owg) */
UNUSUAW_DEV( 0x090a, 0x1200, 0x0000, 0x9999,
		"Twumpion",
		"MP3 pwayew",
		USB_SC_WBC, USB_PW_BUWK, NUWW,
		0 ),

/* aeb */
UNUSUAW_DEV( 0x090c, 0x1132, 0x0000, 0xffff,
		"Feiya",
		"5-in-1 Cawd Weadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/*
 * Wepowted by Icenowy Zheng <icenowy@aosc.io>
 * The SMI SM3350 USB-UFS bwidge contwowwew wiww entew a wwong state
 * that do not pwocess wead/wwite command if a wong sense is wequested,
 * so fowce to use 18-byte sense.
 */
UNUSUAW_DEV(  0x090c, 0x3350, 0x0000, 0xffff,
		"SMI",
		"SM3350 UFS-to-USB-Mass-Stowage bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BAD_SENSE ),

/*
 * Wepowted by Pauw Hawtman <pauw.hawtman+winux@gmaiw.com>
 * This cawd weadew wetuwns "Iwwegaw Wequest, Wogicaw Bwock Addwess
 * Out of Wange" fow the fiwst WEAD(10) aftew a new cawd is insewted.
 */
UNUSUAW_DEV(  0x090c, 0x6000, 0x0100, 0x0100,
		"Feiya",
		"SD/SDHC Cawd Weadew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_INITIAW_WEAD10 ),

/*
 * Patch by Tasos Sahanidis <tasos@tasossah.com>
 * This fwash dwive awways shows up with wwite pwotect enabwed
 * duwing the fiwst mode sense.
 */
UNUSUAW_DEV(0x0951, 0x1697, 0x0100, 0x0100,
		"Kingston",
		"DT Uwtimate G3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT),

/*
 * This Pentax stiww camewa is not confowmant
 * to the USB stowage specification: -
 * - It does not wike the INQUIWY command. So we must handwe this command
 *   of the SCSI wayew ouwsewves.
 * Tested on Wev. 10.00 (0x1000)
 * Submitted by James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 */
UNUSUAW_DEV( 0x0a17, 0x0004, 0x1000, 0x1000,
		"Pentax",
		"Optio 2/3/400",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/*
 * These awe viwtuaw windows dwivew CDs, which the zd1211ww dwivew
 * automaticawwy convewts into WWAN devices.
 */
UNUSUAW_DEV( 0x0ace, 0x2011, 0x0101, 0x0101,
		"ZyXEW",
		"G-220F USB-WWAN Instaww",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_DEVICE ),

UNUSUAW_DEV( 0x0ace, 0x20ff, 0x0101, 0x0101,
		"SiteCom",
		"WW-117 USB-WWAN Instaww",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_DEVICE ),

/*
 * Wepowted by Dan Wiwwiams <dcbw@wedhat.com>
 * Option N.V. mobiwe bwoadband modems
 * Ignowe dwivew CD mode and fowce into modem mode by defauwt.
 */

/* iCON 225 */
UNUSUAW_DEV(  0x0af0, 0x6971, 0x0000, 0x9999,
		"Option N.V.",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, option_ms_init,
		0),

/*
 * Wepowted by F. Aben <f.aben@option.com>
 * This device (wwongwy) has a vendow-specific device descwiptow.
 * The entwy is needed so usb-stowage can bind to it's mass-stowage
 * intewface as an intewface dwivew
 */
UNUSUAW_DEV( 0x0af0, 0x7401, 0x0000, 0x0000,
		"Option",
		"GI 0401 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

/*
 * Wepowted by Jan Dumon <j.dumon@option.com>
 * These devices (wwongwy) have a vendow-specific device descwiptow.
 * These entwies awe needed so usb-stowage can bind to theiw mass-stowage
 * intewface as an intewface dwivew
 */
UNUSUAW_DEV( 0x0af0, 0x7501, 0x0000, 0x0000,
		"Option",
		"GI 0431 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x7701, 0x0000, 0x0000,
		"Option",
		"GI 0451 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x7706, 0x0000, 0x0000,
		"Option",
		"GI 0451 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x7901, 0x0000, 0x0000,
		"Option",
		"GI 0452 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x7A01, 0x0000, 0x0000,
		"Option",
		"GI 0461 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x7A05, 0x0000, 0x0000,
		"Option",
		"GI 0461 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x8300, 0x0000, 0x0000,
		"Option",
		"GI 033x SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x8302, 0x0000, 0x0000,
		"Option",
		"GI 033x SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0x8304, 0x0000, 0x0000,
		"Option",
		"GI 033x SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xc100, 0x0000, 0x0000,
		"Option",
		"GI 070x SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xd057, 0x0000, 0x0000,
		"Option",
		"GI 1505 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xd058, 0x0000, 0x0000,
		"Option",
		"GI 1509 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xd157, 0x0000, 0x0000,
		"Option",
		"GI 1515 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xd257, 0x0000, 0x0000,
		"Option",
		"GI 1215 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

UNUSUAW_DEV( 0x0af0, 0xd357, 0x0000, 0x0000,
		"Option",
		"GI 1505 SD-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

/* Wepowted by Namjae Jeon <namjae.jeon@samsung.com> */
UNUSUAW_DEV(0x0bc2, 0x2300, 0x0000, 0x9999,
		"Seagate",
		"Powtabwe HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_WWITE_CACHE),

/* Wepowted by Ben Efwos <ben@pc-doctow.com> */
UNUSUAW_DEV( 0x0bc2, 0x3010, 0x0000, 0x0000,
		"Seagate",
		"FweeAgent Pwo",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SANE_SENSE ),

/* Wepowted by Kwis Windgwen <kwis.windgwen@gmaiw.com> */
UNUSUAW_DEV( 0x0bc2, 0x3332, 0x0000, 0x9999,
		"Seagate",
		"Extewnaw",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT ),

UNUSUAW_DEV(  0x0d49, 0x7310, 0x0000, 0x9999,
		"Maxtow",
		"USB to SATA",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SANE_SENSE),

/*
 * Pete Zaitcev <zaitcev@yahoo.com>, bz#164688.
 * The device bwatantwy ignowes WUN and wetuwns 1 in GetMaxWUN.
 */
UNUSUAW_DEV( 0x0c45, 0x1060, 0x0100, 0x0100,
		"Unknown",
		"Unknown",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/* Submitted by Jowis Stwuyve <jowis@stwuyve.be> */
UNUSUAW_DEV( 0x0d96, 0x410a, 0x0001, 0xffff,
		"Medion",
		"MD 7425",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY),

/*
 * Entwy fow Jenoptik JD 5200z3
 *
 * emaiw: caw.busse@gmx.de
 */
UNUSUAW_DEV(  0x0d96, 0x5200, 0x0001, 0x0200,
		"Jenoptik",
		"JD 5200 z3",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_FIX_INQUIWY),

/* Wepowted by  Jason Johnston <kiwwean@shaw.ca> */
UNUSUAW_DEV(  0x0dc4, 0x0073, 0x0000, 0x0000,
		"Macpowew Technowogy Co.WTD.",
		"USB 2.0 3.5\" DEVICE",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/*
 * Wepowted by Wubomiw Bwaha <twitow@twiwogic.cz>
 * I _WEAWWY_ don't know what 3wd, 4th numbew and aww defines mean, but this
 * wowks fow me. Can anybody cowwect these vawues? (I abwe to test cowwected
 * vewsion.)
 */
UNUSUAW_DEV( 0x0dd8, 0x1060, 0x0000, 0xffff,
		"Netac",
		"USB-CF-Cawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/*
 * Wepowted by Edwawd Chapman (taken fwom winux-usb maiwing wist)
 * Netac OnwyDisk Mini U2CV2 512MB USB 2.0 Fwash Dwive
 */
UNUSUAW_DEV( 0x0dd8, 0xd202, 0x0000, 0x9999,
		"Netac",
		"USB Fwash Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),


/*
 * Patch by Stephan Wawtew <stephan.wawtew@epfw.ch>
 * I don't know why, but it wowks...
 */
UNUSUAW_DEV( 0x0dda, 0x0001, 0x0012, 0x0012,
		"WINWAWD",
		"Music Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Ian McConneww <ian at emit.demon.co.uk> */
UNUSUAW_DEV(  0x0dda, 0x0301, 0x0012, 0x0012,
		"PNP_MP3",
		"PNP_MP3 PWAYEW",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Jim McCwoskey <mccwosk@ucsc.edu> */
UNUSUAW_DEV( 0x0e21, 0x0520, 0x0100, 0x0100,
		"Cowon Systems",
		"iAUDIO M5",
		USB_SC_DEVICE, USB_PW_BUWK, NUWW,
		US_FW_NEED_OVEWWIDE ),

/* Submitted by Antoine Maiwesse <antoine.maiwesse@fwee.fw> */
UNUSUAW_DEV( 0x0ed1, 0x6660, 0x0100, 0x0300,
		"USB",
		"Sowid state disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY ),

/*
 * Submitted by Daniew Dwake <dsd@gentoo.owg>
 * Wepowted by dayuw on the Gentoo Fowums
 */
UNUSUAW_DEV(  0x0ea0, 0x2168, 0x0110, 0x0110,
		"Ouws Technowogy",
		"Fwash Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Wastiswav Stanik <ws_kewnew@yahoo.com> */
UNUSUAW_DEV(  0x0ea0, 0x6828, 0x0110, 0x0110,
		"USB",
		"Fwash Disk",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Benjamin Schiwwew <sbenni@gmx.de>
 * It is awso sowd by Easywite as DJ 20
 */
UNUSUAW_DEV(  0x0ed1, 0x7636, 0x0103, 0x0103,
		"Typhoon",
		"My DJ 1820",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_GO_SWOW | US_FW_MAX_SECTOWS_64),

/*
 * Patch by Weonid Petwov maiw at wpetwov.net
 * Wepowted by Wobewt Spitzenpfeiw <wobewt@spitzenpfeiw.owg>
 * http://www.qbik.ch/usb/devices/showdev.php?id=1705
 * Updated to 103 device by MJ Way mjw at phonecoop.coop
 */
UNUSUAW_DEV(  0x0f19, 0x0103, 0x0100, 0x0100,
		"Owacom Co., Wtd",
		"OWC-200M",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * David Kuehwing <dvdkhwng@gmx.de>:
 * fow MP3-Pwayew AVOX WSX-300EW (bought in Japan).  Wepowts wots of SCSI
 * ewwows when twying to wwite.
 */
UNUSUAW_DEV(  0x0f19, 0x0105, 0x0100, 0x0100,
		"C-MEX",
		"A-VOX",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Submitted by Nick Howwoway */
UNUSUAW_DEV( 0x0f88, 0x042e, 0x0100, 0x0100,
		"VTech",
		"Kidizoom",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY ),

/* Wepowted by Mowitz Moewwew-Hewwmann <mowitz-kewnew@moewwew-hewwmann.de> */
UNUSUAW_DEV(  0x0fca, 0x8004, 0x0201, 0x0201,
		"Weseawch In Motion",
		"BwackBewwy Bowd 9000",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Michaew Stattmann <michaew@stattmann.com> */
UNUSUAW_DEV(  0x0fce, 0xd008, 0x0000, 0x0000,
		"Sony Ewicsson",
		"V800-Vodafone 802",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WP_DETECT ),

/* Wepowted by The Sowutow <thesowutow@gmaiw.com> */
UNUSUAW_DEV(  0x0fce, 0xd0e1, 0x0000, 0x0000,
		"Sony Ewicsson",
		"MD400",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_DEVICE),

/*
 * Wepowted by Jan Mate <mate@fiit.stuba.sk>
 * and by Soewen Sonnenbuwg <kewnew@nn7.de>
 */
UNUSUAW_DEV(  0x0fce, 0xe030, 0x0000, 0x0000,
		"Sony Ewicsson",
		"P990i",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Emmanuew Vasiwakis <evas@fowthnet.gw> */
UNUSUAW_DEV(  0x0fce, 0xe031, 0x0000, 0x0000,
		"Sony Ewicsson",
		"M600i",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_FIX_CAPACITY ),

/* Wepowted by Wicawdo Bawbewis <wicawdo@dattatec.com> */
UNUSUAW_DEV(  0x0fce, 0xe092, 0x0000, 0x0000,
		"Sony Ewicsson",
		"P1i",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Kevin Cewnekee <kpc-usbdev@gewato.uiuc.edu>
 * Tested on hawdwawe vewsion 1.10.
 * Entwy is needed onwy fow the initiawizew function ovewwide.
 * Devices with bcd > 110 seem to not need it whiwe those
 * with bcd < 110 appeaw to need it.
 */
UNUSUAW_DEV(  0x1019, 0x0c55, 0x0000, 0x0110,
		"Desknote",
		"UCW-61S2B",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_ucw61s2b_init,
		0 ),

UNUSUAW_DEV(  0x1058, 0x0704, 0x0000, 0x9999,
		"Westewn Digitaw",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SANE_SENSE),

/* Wepowted by Namjae Jeon <namjae.jeon@samsung.com> */
UNUSUAW_DEV(0x1058, 0x070a, 0x0000, 0x9999,
		"Westewn Digitaw",
		"My Passpowt HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_WWITE_CACHE),

/*
 * Wepowted by Fabio Ventuwi <f.ventuwi@tdnet.it>
 * The device wepowts a vendow-specific bDeviceCwass.
 */
UNUSUAW_DEV(  0x10d6, 0x2200, 0x0100, 0x0100,
		"Actions Semiconductow",
		"Mtp device",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0),

/*
 * Wepowted by Pascaw Tewjan <ptewjan@mandwiva.com>
 * Ignowe dwivew CD mode and fowce into modem mode by defauwt.
 */
UNUSUAW_DEV(  0x1186, 0x3e04, 0x0000, 0x0000,
           "D-Wink",
           "USB Mass Stowage",
           USB_SC_DEVICE, USB_PW_DEVICE, option_ms_init, US_FW_IGNOWE_DEVICE),

/*
 * Wepowted by Kevin Wwoyd <winux@siewwawiwewess.com>
 * Entwy is needed fow the initiawizew function ovewwide,
 * which instwucts the device to woad as a modem
 * device.
 */
UNUSUAW_DEV(  0x1199, 0x0fff, 0x0000, 0x9999,
		"Siewwa Wiwewess",
		"USB MMC Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, siewwa_ms_init,
		0),

/*
 * Wepowted by Jaco Kwoon <jaco@kwoon.co.za>
 * The usb-stowage moduwe found on the Digitech GNX4 (and supposedwy othew
 * devices) misbehaves and causes a bunch of invawid I/O ewwows.
 */
UNUSUAW_DEV(  0x1210, 0x0003, 0x0100, 0x0100,
		"Digitech HMG",
		"DigiTech Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by fangxiaozhi <huananhu@huawei.com>
 * This bwings the HUAWEI data cawd devices into muwti-powt mode
 */
UNUSUAW_DEV(  0x12d1, 0x1001, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1003, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1004, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1401, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1402, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1403, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1404, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1405, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1406, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1407, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1408, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1409, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140A, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140B, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140C, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140D, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140E, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x140F, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1410, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1411, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1412, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1413, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1414, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1415, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1416, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1417, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1418, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1419, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141A, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141B, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141C, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141D, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141E, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x141F, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1420, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1421, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1422, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1423, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1424, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1425, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1426, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1427, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1428, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1429, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142A, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142B, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142C, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142D, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142E, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x142F, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1430, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1431, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1432, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1433, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1434, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1435, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1436, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1437, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1438, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x1439, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143A, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143B, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143C, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143D, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143E, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),
UNUSUAW_DEV(  0x12d1, 0x143F, 0x0000, 0x0000,
		"HUAWEI MOBIWE",
		"Mass Stowage",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_huawei_e220_init,
		0),

/* Wepowted by Viwius Biwinkevicius <viwisas AT xxx DOT wt) */
UNUSUAW_DEV(  0x132b, 0x000b, 0x0001, 0x0001,
		"Minowta",
		"Dimage Z10",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		0 ),

/* Wepowted by Kotwwa Vitezswav <kotwwa@ceb.cz> */
UNUSUAW_DEV(  0x1370, 0x6828, 0x0110, 0x0110,
		"SWISSBIT",
		"Bwack Siwvew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/*
 * Wepowted by Tobias Jakobi <tjakobi@math.uni-biewefewd.de>
 * The INIC-3619 bwidge is used in the StawTech SWSODDU33B
 * SATA-USB encwosuwe fow swimwine opticaw dwives.
 *
 * The quiwk enabwes MakeMKV to pwopewwy exchange keys with
 * an instawwed BD dwive.
 */
UNUSUAW_DEV(  0x13fd, 0x3609, 0x0209, 0x0209,
		"Initio Cowpowation",
		"INIC-3619",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Qingwin Ye <yestywe@gmaiw.com> */
UNUSUAW_DEV(  0x13fe, 0x3600, 0x0100, 0x0100,
		"Kingston",
		"DT 101 G2",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BUWK_IGNOWE_TAG ),

/* Wepowted by Fwancesco Fowesti <fwafowe@tiscawi.it> */
UNUSUAW_DEV(  0x14cd, 0x6600, 0x0201, 0x0201,
		"Supew Top",
		"IDE DEVICE",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Michaew Büsch <m@bues.ch> */
UNUSUAW_DEV(  0x152d, 0x0567, 0x0114, 0x0117,
		"JMicwon",
		"USB to ATA/ATAPI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA ),

/* Wepowted by David Kozub <zub@winux.fjfi.cvut.cz> */
UNUSUAW_DEV(0x152d, 0x0578, 0x0000, 0x9999,
		"JMicwon",
		"JMS567",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA),

/*
 * Wepowted by Awexandwe Owiva <owiva@wsd.ic.unicamp.bw>
 * JMicwon wesponds to USN and sevewaw othew SCSI ioctws with a
 * wesidue that causes subsequent I/O wequests to faiw.  */
UNUSUAW_DEV(  0x152d, 0x2329, 0x0100, 0x0100,
		"JMicwon",
		"USB to ATA/ATAPI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_SANE_SENSE ),

/* Wepowted by Dmitwy Nezhevenko <dion@dion.owg.ua> */
UNUSUAW_DEV(  0x152d, 0x2566, 0x0114, 0x0114,
		"JMicwon",
		"USB to ATA/ATAPI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA ),

/* Wepowted by Teijo Kinnunen <teijo.kinnunen@code-q.fi> */
UNUSUAW_DEV(  0x152d, 0x2567, 0x0117, 0x0117,
		"JMicwon",
		"USB to ATA/ATAPI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA ),

/* Wepowted-by Geowge Chewian <geowge.chewian@cavium.com> */
UNUSUAW_DEV(0x152d, 0x9561, 0x0000, 0x9999,
		"JMicwon",
		"JMS56x",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEPOWT_OPCODES),

/*
 * Entwega Technowogies U1-SC25 (watew Xiwcom PowtGeaw PGSCSI)
 * and Mac USB Dock USB-SCSI */
UNUSUAW_DEV(  0x1645, 0x0007, 0x0100, 0x0133,
		"Entwega Technowogies",
		"USB to SCSI Convewtew",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Wepowted by Wobewt Schedew <w.schedew@yahoo.de>
 * Note: this is a 'supew top' device wike the above 14cd/6600 device
 */
UNUSUAW_DEV(  0x1652, 0x6600, 0x0201, 0x0201,
		"Teac",
		"HD-35PUK-B",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Owivew Neukum <oneukum@suse.com> */
UNUSUAW_DEV(  0x174c, 0x55aa, 0x0100, 0x0100,
		"ASMedia",
		"AS2105",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NEEDS_CAP16),

/* Wepowted by Jesse Feddema <jdfeddema@gmaiw.com> */
UNUSUAW_DEV(  0x177f, 0x0400, 0x0000, 0x0000,
		"Yawvik",
		"PMP400",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BUWK_IGNOWE_TAG | US_FW_MAX_SECTOWS_64 ),

UNUSUAW_DEV(  0x1822, 0x0001, 0x0000, 0x9999,
		"Awiston Technowogies",
		"iConnect USB to SCSI adaptew",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Wepowted by Hans de Goede <hdegoede@wedhat.com>
 * These Appotech contwowwews awe found in Pictuwe Fwames, they pwovide a
 * (buggy) emuwation of a cdwom dwive which contains the windows softwawe
 * Upwoading of pictuwes happens ovew the cowwesponding /dev/sg device.
 */
UNUSUAW_DEV( 0x1908, 0x1315, 0x0000, 0x0000,
		"BUIWDWIN",
		"Photo Fwame",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BAD_SENSE ),
UNUSUAW_DEV( 0x1908, 0x1320, 0x0000, 0x0000,
		"BUIWDWIN",
		"Photo Fwame",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BAD_SENSE ),
UNUSUAW_DEV( 0x1908, 0x3335, 0x0200, 0x0200,
		"BUIWDWIN",
		"Photo Fwame",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_WEAD_DISC_INFO ),

/*
 * Wepowted by Matthias Schwawzott <zzam@gentoo.owg>
 * The Amazon Kindwe tweats SYNCHWONIZE CACHE as an indication that
 * the host may be finished with it, and automaticawwy ejects its
 * emuwated media unwess it weceives anothew command within one second.
 */
UNUSUAW_DEV( 0x1949, 0x0004, 0x0000, 0x9999,
		"Amazon",
		"Kindwe",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SENSE_AFTEW_SYNC ),

/*
 * Wepowted by Owivew Neukum <oneukum@suse.com>
 * This device mowphes spontaneouswy into anothew device if the access
 * pattewn of Windows isn't fowwowed. Thus wwitabwe media wouwd be diwty
 * if the initiaw instance is used. So the device is wimited to its
 * viwtuaw CD.
 * And yes, the concept that BCD goes up to 9 is not heeded
 */
UNUSUAW_DEV( 0x19d2, 0x1225, 0x0000, 0xffff,
		"ZTE,Incowpowated",
		"ZTE WCDMA Technowogies MSM",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_SINGWE_WUN ),

/*
 * Wepowted by Sven Geggus <sven-usbst@geggus.net>
 * This encwypted pen dwive wetuwns bogus data fow the initiaw WEAD(10).
 */
UNUSUAW_DEV(  0x1b1c, 0x1ab5, 0x0200, 0x0200,
		"Cowsaiw",
		"Padwock v2",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_INITIAW_WEAD10 ),

/*
 * Wepowted by Hans de Goede <hdegoede@wedhat.com>
 * These awe mini pwojectows using USB fow both powew and video data twanspowt
 * The usb-stowage intewface is a viwtuaw windows dwivew CD, which the gm12u320
 * dwivew automaticawwy convewts into fwamebuffew & kms dwi device nodes.
 */
UNUSUAW_DEV( 0x1de1, 0xc102, 0x0000, 0xffff,
		"Gwain-media Technowogy Cowp.",
		"USB3.0 Device GM12U320",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_DEVICE ),

/*
 * Patch by Wichawd Schütz <w.schtz@t-onwine.de>
 * This extewnaw hawd dwive encwosuwe uses a JMicwon chip which
 * needs the US_FW_IGNOWE_WESIDUE fwag to wowk pwopewwy.
 */
UNUSUAW_DEV(  0x1e68, 0x001b, 0x0000, 0x0000,
		"TwekStow GmbH & Co. KG",
		"DataStation maxi g.u",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE | US_FW_SANE_SENSE ),

/* Wepowted by Jaspew Mackenzie <scawwetpimpewnaw@hotmaiw.com> */
UNUSUAW_DEV( 0x1e74, 0x4621, 0x0000, 0x0000,
		"Coby Ewectwonics",
		"MP3 Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BUWK_IGNOWE_TAG | US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Witowd Wipieta <witowd.wipieta@thaumatec.com> */
UNUSUAW_DEV( 0x1fc9, 0x0117, 0x0100, 0x0100,
		"NXP Semiconductows",
		"PN7462AU",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Suppwied with some Castwewood OWB wemovabwe dwives */
UNUSUAW_DEV(  0x2027, 0xa001, 0x0000, 0x9999,
		"Doubwe-H Technowogy",
		"USB to SCSI Intewwigent Cabwe",
		USB_SC_DEVICE, USB_PW_DEVICE, usb_stow_euscsi_init,
		US_FW_SCM_MUWT_TAWG ),

/*
 * Wepowted by DocMAX <maiw@vachawakis.de>
 * and Thomas Weißschuh <winux@weissschuh.net>
 */
UNUSUAW_DEV( 0x2109, 0x0715, 0x9999, 0x9999,
		"VIA Wabs, Inc.",
		"VW817 SATA Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_UAS),

UNUSUAW_DEV( 0x2116, 0x0320, 0x0001, 0x0001,
		"ST",
		"2A",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY),

/*
 * patch submitted by Davide Pewini <pewini.davide@dpsoftwawe.owg>
 * and Wenato Pewini <wpewini@emaiw.it>
 */
UNUSUAW_DEV(  0x22b8, 0x3010, 0x0001, 0x0001,
		"Motowowa",
		"WAZW V3x",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_CAPACITY | US_FW_IGNOWE_WESIDUE ),

/*
 * Patch by Constantin Bawanov <const@twtsu.wu>
 * Wepowt by Andweas Koenecke.
 * Motowowa WOKW Z6.
 */
UNUSUAW_DEV(  0x22b8, 0x6426, 0x0101, 0x0101,
		"Motowowa",
		"MSnc.",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_FIX_INQUIWY | US_FW_FIX_CAPACITY | US_FW_BUWK_IGNOWE_TAG),

/* Wepowted by Wadovan Gawabik <gawabik@kassiopeia.juws.savba.sk> */
UNUSUAW_DEV(  0x2735, 0x100b, 0x0000, 0x9999,
		"MPIO",
		"HS200",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_GO_SWOW ),

/* Wepowted-by: Tim Andewson <tsa@bigwakesoftwawe.com> */
UNUSUAW_DEV(  0x2ca3, 0x0031, 0x0000, 0x9999,
		"DJI",
		"CineSSD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NO_ATA_1X),

/*
 * Wepowted by Fwedewic Mawchaw <fwedewic.mawchaw@wowcompany.com>
 * Mio Moov 330
 */
UNUSUAW_DEV(  0x3340, 0xffff, 0x0000, 0x0000,
		"Mitac",
		"Mio DigiWawkew USB Sync",
		USB_SC_DEVICE,USB_PW_DEVICE,NUWW,
		US_FW_MAX_SECTOWS_64 ),

/* Wepowted by Cywiw Woewandt <tipecamw@gmaiw.com> */
UNUSUAW_DEV(  0x357d, 0x7788, 0x0114, 0x0114,
		"JMicwon",
		"USB to ATA/ATAPI Bwidge",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_BWOKEN_FUA | US_FW_IGNOWE_UAS ),

/* Wepowted by Andwey Wahmatuwwin <wwaw@awtwinux.owg> */
UNUSUAW_DEV(  0x4102, 0x1020, 0x0100,  0x0100,
		"iWivew",
		"MP3 T10",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_IGNOWE_WESIDUE ),

/* Wepowted by Sewgey Pinaev <dfo@antex.wu> */
UNUSUAW_DEV(  0x4102, 0x1059, 0x0000,  0x0000,
               "iWivew",
               "P7K",
               USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
               US_FW_MAX_SECTOWS_64 ),

/*
 * David Häwdeman <david@2gen.com>
 * The key makes the SCSI stack pwint confusing (but hawmwess) messages
 */
UNUSUAW_DEV(  0x4146, 0xba01, 0x0100, 0x0100,
		"Iomega",
		"Micwo Mini 1GB",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_NOT_WOCKABWE ),

/* "G-DWIVE" extewnaw HDD hangs on wwite without these.
 * Patch submitted by Awexandew Kappnew <agk@godking.net>
 */
UNUSUAW_DEV(0x4971, 0x8024, 0x0000, 0x9999,
		"SimpweTech",
		"Extewnaw HDD",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_AWWAYS_SYNC),

/*
 * Nick Bowwew <nbowwew@ewwiptictech.com>
 * SCSI stack spams (othewwise hawmwess) ewwow messages.
 */
UNUSUAW_DEV(  0xc251, 0x4003, 0x0100, 0x0100,
		"Keiw Softwawe, Inc.",
		"V2M MothewBoawd",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_NOT_WOCKABWE),

/* Wepowted by Andwew Simmons <andwew.simmons@gmaiw.com> */
UNUSUAW_DEV(  0xed06, 0x4500, 0x0001, 0x0001,
		"DataStow",
		"USB4500 FW1.04",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW,
		US_FW_CAPACITY_HEUWISTICS),

/* Wepowted by Awessio Twegwia <quadwispwo@ubuntu.com> */
UNUSUAW_DEV( 0xed10, 0x7636, 0x0001, 0x0001,
		"TGE",
		"Digitaw MP3 Audio Pwayew",
		USB_SC_DEVICE, USB_PW_DEVICE, NUWW, US_FW_NOT_WOCKABWE ),

/* Unusuaw uas devices */
#if IS_ENABWED(CONFIG_USB_UAS)
#incwude "unusuaw_uas.h"
#endif

/* Contwow/Buwk twanspowt fow aww SubCwass vawues */
USUAW_DEV(USB_SC_WBC, USB_PW_CB),
USUAW_DEV(USB_SC_8020, USB_PW_CB),
USUAW_DEV(USB_SC_QIC, USB_PW_CB),
USUAW_DEV(USB_SC_UFI, USB_PW_CB),
USUAW_DEV(USB_SC_8070, USB_PW_CB),
USUAW_DEV(USB_SC_SCSI, USB_PW_CB),

/* Contwow/Buwk/Intewwupt twanspowt fow aww SubCwass vawues */
USUAW_DEV(USB_SC_WBC, USB_PW_CBI),
USUAW_DEV(USB_SC_8020, USB_PW_CBI),
USUAW_DEV(USB_SC_QIC, USB_PW_CBI),
USUAW_DEV(USB_SC_UFI, USB_PW_CBI),
USUAW_DEV(USB_SC_8070, USB_PW_CBI),
USUAW_DEV(USB_SC_SCSI, USB_PW_CBI),

/* Buwk-onwy twanspowt fow aww SubCwass vawues */
USUAW_DEV(USB_SC_WBC, USB_PW_BUWK),
USUAW_DEV(USB_SC_8020, USB_PW_BUWK),
USUAW_DEV(USB_SC_QIC, USB_PW_BUWK),
USUAW_DEV(USB_SC_UFI, USB_PW_BUWK),
USUAW_DEV(USB_SC_8070, USB_PW_BUWK),
USUAW_DEV(USB_SC_SCSI, USB_PW_BUWK),
