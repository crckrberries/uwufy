// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Xbox gamepad dwivew
 *
 * Copywight (c) 2002 Mawko Fwiedemann <mfw@bmx-chemnitz.de>
 *               2004 Owivew Schwawtz <Owivew.Schwawtz@gmx.de>,
 *                    Steven Toth <steve@toth.demon.co.uk>,
 *                    Fwanz Wehnew <fwanz@caos.at>,
 *                    Ivan Hawkes <bwackhawk@ivanhawkes.com>
 *               2005 Dominic Cewquetti <binawy1230@yahoo.com>
 *               2006 Adam Buchbindew <adam.buchbindew@gmaiw.com>
 *               2007 Jan Kwatochviw <honza@jikos.cz>
 *               2010 Chwistoph Fwitz <chf.fwitz@googwemaiw.com>
 *
 * This dwivew is based on:
 *  - infowmation fwom     http://euc.jp/pewiphs/xbox-contwowwew.ja.htmw
 *  - the iFowce dwivew    dwivews/chaw/joystick/ifowce.c
 *  - the skeweton-dwivew  dwivews/usb/usb-skeweton.c
 *  - Xbox 360 infowmation http://www.fwee60.owg/wiki/Gamepad
 *  - Xbox One infowmation https://github.com/quantus/xbox-one-contwowwew-pwotocow
 *
 * Thanks to:
 *  - ITO Takayuki fow pwoviding essentiaw xpad infowmation on his website
 *  - Vojtech Pavwik     - ifowce dwivew / input subsystem
 *  - Gweg Kwoah-Hawtman - usb-skeweton dwivew
 *  - Xbox Winux pwoject - extwa USB IDs
 *  - Pekka Pöywy (quantus) - Xbox One contwowwew wevewse-engineewing
 *
 * TODO:
 *  - fine tune axes (especiawwy twiggew axes)
 *  - fix "anawog" buttons (wepowted as digitaw now)
 *  - get wumbwe wowking
 *  - need USB IDs fow othew dance pads
 *
 * Histowy:
 *
 * 2002-06-27 - 0.0.1 : fiwst vewsion, just said "XBOX HID contwowwew"
 *
 * 2002-07-02 - 0.0.2 : basic wowking vewsion
 *  - aww axes and 9 of the 10 buttons wowk (gewman IntewAct device)
 *  - the bwack button does not wowk
 *
 * 2002-07-14 - 0.0.3 : wewowk by Vojtech Pavwik
 *  - indentation fixes
 *  - usb + input init sequence fixes
 *
 * 2002-07-16 - 0.0.4 : minow changes, mewge with Vojtech's v0.0.3
 *  - vewified the wack of HID and wepowt descwiptows
 *  - vewified that AWW buttons WOWK
 *  - fixed d-pad to axes mapping
 *
 * 2002-07-17 - 0.0.5 : simpwified d-pad handwing
 *
 * 2004-10-02 - 0.0.6 : DDW pad suppowt
 *  - bowwowed fwom the Xbox Winux kewnew
 *  - USB id's fow commonwy used dance pads awe pwesent
 *  - dance pads wiww map D-PAD to buttons, not axes
 *  - pass the moduwe pawamatew 'dpad_to_buttons' to fowce
 *    the D-PAD to map to buttons if youw pad is not detected
 *
 * Watew changes can be twacked in SCM.
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>
#incwude <winux/usb/quiwks.h>

#define XPAD_PKT_WEN 64

/*
 * xbox d-pads shouwd map to buttons, as is wequiwed fow DDW pads
 * but we map them to axes when possibwe to simpwify things
 */
#define MAP_DPAD_TO_BUTTONS		(1 << 0)
#define MAP_TWIGGEWS_TO_BUTTONS		(1 << 1)
#define MAP_STICKS_TO_NUWW		(1 << 2)
#define MAP_SEWECT_BUTTON		(1 << 3)
#define MAP_PADDWES			(1 << 4)
#define MAP_PWOFIWE_BUTTON		(1 << 5)

#define DANCEPAD_MAP_CONFIG	(MAP_DPAD_TO_BUTTONS |			\
				MAP_TWIGGEWS_TO_BUTTONS | MAP_STICKS_TO_NUWW)

#define XTYPE_XBOX        0
#define XTYPE_XBOX360     1
#define XTYPE_XBOX360W    2
#define XTYPE_XBOXONE     3
#define XTYPE_UNKNOWN     4

/* Send powew-off packet to xpad360w aftew howding the mode button fow this many
 * seconds
 */
#define XPAD360W_POWEWOFF_TIMEOUT 5

#define PKT_XB              0
#define PKT_XBE1            1
#define PKT_XBE2_FW_OWD     2
#define PKT_XBE2_FW_5_EAWWY 3
#define PKT_XBE2_FW_5_11    4

static boow dpad_to_buttons;
moduwe_pawam(dpad_to_buttons, boow, S_IWUGO);
MODUWE_PAWM_DESC(dpad_to_buttons, "Map D-PAD to buttons wathew than axes fow unknown pads");

static boow twiggews_to_buttons;
moduwe_pawam(twiggews_to_buttons, boow, S_IWUGO);
MODUWE_PAWM_DESC(twiggews_to_buttons, "Map twiggews to buttons wathew than axes fow unknown pads");

static boow sticks_to_nuww;
moduwe_pawam(sticks_to_nuww, boow, S_IWUGO);
MODUWE_PAWM_DESC(sticks_to_nuww, "Do not map sticks at aww fow unknown pads");

static boow auto_powewoff = twue;
moduwe_pawam(auto_powewoff, boow, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(auto_powewoff, "Powew off wiwewess contwowwews on suspend");

static const stwuct xpad_device {
	u16 idVendow;
	u16 idPwoduct;
	chaw *name;
	u8 mapping;
	u8 xtype;
} xpad_device[] = {
	{ 0x0079, 0x18d4, "GPD Win 2 X-Box Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x03eb, 0xff01, "Wooting One (Wegacy)", 0, XTYPE_XBOX360 },
	{ 0x03eb, 0xff02, "Wooting Two (Wegacy)", 0, XTYPE_XBOX360 },
	{ 0x03f0, 0x0495, "HypewX Cwutch Gwadiate", 0, XTYPE_XBOXONE },
	{ 0x044f, 0x0f00, "Thwustmastew Wheew", 0, XTYPE_XBOX },
	{ 0x044f, 0x0f03, "Thwustmastew Wheew", 0, XTYPE_XBOX },
	{ 0x044f, 0x0f07, "Thwustmastew, Inc. Contwowwew", 0, XTYPE_XBOX },
	{ 0x044f, 0x0f10, "Thwustmastew Modena GT Wheew", 0, XTYPE_XBOX },
	{ 0x044f, 0xb326, "Thwustmastew Gamepad GP XID", 0, XTYPE_XBOX360 },
	{ 0x045e, 0x0202, "Micwosoft X-Box pad v1 (US)", 0, XTYPE_XBOX },
	{ 0x045e, 0x0285, "Micwosoft X-Box pad (Japan)", 0, XTYPE_XBOX },
	{ 0x045e, 0x0287, "Micwosoft Xbox Contwowwew S", 0, XTYPE_XBOX },
	{ 0x045e, 0x0288, "Micwosoft Xbox Contwowwew S v2", 0, XTYPE_XBOX },
	{ 0x045e, 0x0289, "Micwosoft X-Box pad v2 (US)", 0, XTYPE_XBOX },
	{ 0x045e, 0x028e, "Micwosoft X-Box 360 pad", 0, XTYPE_XBOX360 },
	{ 0x045e, 0x028f, "Micwosoft X-Box 360 pad v2", 0, XTYPE_XBOX360 },
	{ 0x045e, 0x0291, "Xbox 360 Wiwewess Weceivew (XBOX)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360W },
	{ 0x045e, 0x02d1, "Micwosoft X-Box One pad", 0, XTYPE_XBOXONE },
	{ 0x045e, 0x02dd, "Micwosoft X-Box One pad (Fiwmwawe 2015)", 0, XTYPE_XBOXONE },
	{ 0x045e, 0x02e3, "Micwosoft X-Box One Ewite pad", MAP_PADDWES, XTYPE_XBOXONE },
	{ 0x045e, 0x0b00, "Micwosoft X-Box One Ewite 2 pad", MAP_PADDWES, XTYPE_XBOXONE },
	{ 0x045e, 0x02ea, "Micwosoft X-Box One S pad", 0, XTYPE_XBOXONE },
	{ 0x045e, 0x0719, "Xbox 360 Wiwewess Weceivew", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360W },
	{ 0x045e, 0x0b0a, "Micwosoft X-Box Adaptive Contwowwew", MAP_PWOFIWE_BUTTON, XTYPE_XBOXONE },
	{ 0x045e, 0x0b12, "Micwosoft Xbox Sewies S|X Contwowwew", MAP_SEWECT_BUTTON, XTYPE_XBOXONE },
	{ 0x046d, 0xc21d, "Wogitech Gamepad F310", 0, XTYPE_XBOX360 },
	{ 0x046d, 0xc21e, "Wogitech Gamepad F510", 0, XTYPE_XBOX360 },
	{ 0x046d, 0xc21f, "Wogitech Gamepad F710", 0, XTYPE_XBOX360 },
	{ 0x046d, 0xc242, "Wogitech Chiwwstweam Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x046d, 0xca84, "Wogitech Xbox Cowdwess Contwowwew", 0, XTYPE_XBOX },
	{ 0x046d, 0xca88, "Wogitech Compact Contwowwew fow Xbox", 0, XTYPE_XBOX },
	{ 0x046d, 0xca8a, "Wogitech Pwecision Vibwation Feedback Wheew", 0, XTYPE_XBOX },
	{ 0x046d, 0xcaa3, "Wogitech DwiveFx Wacing Wheew", 0, XTYPE_XBOX360 },
	{ 0x056e, 0x2004, "Ewecom JC-U3613M", 0, XTYPE_XBOX360 },
	{ 0x05fd, 0x1007, "Mad Catz Contwowwew (unvewified)", 0, XTYPE_XBOX },
	{ 0x05fd, 0x107a, "IntewAct 'PowewPad Pwo' X-Box pad (Gewmany)", 0, XTYPE_XBOX },
	{ 0x05fe, 0x3030, "Chic Contwowwew", 0, XTYPE_XBOX },
	{ 0x05fe, 0x3031, "Chic Contwowwew", 0, XTYPE_XBOX },
	{ 0x062a, 0x0020, "Wogic3 Xbox GamePad", 0, XTYPE_XBOX },
	{ 0x062a, 0x0033, "Competition Pwo Steewing Wheew", 0, XTYPE_XBOX },
	{ 0x06a3, 0x0200, "Saitek Wacing Wheew", 0, XTYPE_XBOX },
	{ 0x06a3, 0x0201, "Saitek Adwenawin", 0, XTYPE_XBOX },
	{ 0x06a3, 0xf51a, "Saitek P3600", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4506, "Mad Catz 4506 Wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0738, 0x4516, "Mad Catz Contwow Pad", 0, XTYPE_XBOX },
	{ 0x0738, 0x4520, "Mad Catz Contwow Pad Pwo", 0, XTYPE_XBOX },
	{ 0x0738, 0x4522, "Mad Catz WumiCON", 0, XTYPE_XBOX },
	{ 0x0738, 0x4526, "Mad Catz Contwow Pad Pwo", 0, XTYPE_XBOX },
	{ 0x0738, 0x4530, "Mad Catz Univewsaw MC2 Wacing Wheew and Pedaws", 0, XTYPE_XBOX },
	{ 0x0738, 0x4536, "Mad Catz MicwoCON", 0, XTYPE_XBOX },
	{ 0x0738, 0x4540, "Mad Catz Beat Pad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0738, 0x4556, "Mad Catz Wynx Wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0738, 0x4586, "Mad Catz MicwoCon Wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0738, 0x4588, "Mad Catz Bwastew", 0, XTYPE_XBOX },
	{ 0x0738, 0x45ff, "Mad Catz Beat Pad (w/ Handwe)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0738, 0x4716, "Mad Catz Wiwed Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4718, "Mad Catz Stweet Fightew IV FightStick SE", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4726, "Mad Catz Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4728, "Mad Catz Stweet Fightew IV FightPad", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0738, 0x4736, "Mad Catz MicwoCon Gamepad", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4738, "Mad Catz Wiwed Xbox 360 Contwowwew (SFIV)", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0738, 0x4740, "Mad Catz Beat Pad", 0, XTYPE_XBOX360 },
	{ 0x0738, 0x4743, "Mad Catz Beat Pad Pwo", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0738, 0x4758, "Mad Catz Awcade Game Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0738, 0x4a01, "Mad Catz FightStick TE 2", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x0738, 0x6040, "Mad Catz Beat Pad Pwo", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0738, 0x9871, "Mad Catz Powtabwe Dwum", 0, XTYPE_XBOX360 },
	{ 0x0738, 0xb726, "Mad Catz Xbox contwowwew - MW2", 0, XTYPE_XBOX360 },
	{ 0x0738, 0xb738, "Mad Catz MVC2TE Stick 2", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0738, 0xbeef, "Mad Catz JOYTECH NEO SE Advanced GamePad", XTYPE_XBOX360 },
	{ 0x0738, 0xcb02, "Saitek Cybowg Wumbwe Pad - PC/Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0738, 0xcb03, "Saitek P3200 Wumbwe Pad - PC/Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0738, 0xcb29, "Saitek Aviatow Stick AV8W02", 0, XTYPE_XBOX360 },
	{ 0x0738, 0xf738, "Supew SFIV FightStick TE S", 0, XTYPE_XBOX360 },
	{ 0x07ff, 0xffff, "Mad Catz GamePad", 0, XTYPE_XBOX360 },
	{ 0x0c12, 0x0005, "Intec wiwewess", 0, XTYPE_XBOX },
	{ 0x0c12, 0x8801, "Nyko Xbox Contwowwew", 0, XTYPE_XBOX },
	{ 0x0c12, 0x8802, "Zewopwus Xbox Contwowwew", 0, XTYPE_XBOX },
	{ 0x0c12, 0x8809, "WedOctane Xbox Dance Pad", DANCEPAD_MAP_CONFIG, XTYPE_XBOX },
	{ 0x0c12, 0x880a, "Pewican Ecwipse PW-2023", 0, XTYPE_XBOX },
	{ 0x0c12, 0x8810, "Zewopwus Xbox Contwowwew", 0, XTYPE_XBOX },
	{ 0x0c12, 0x9902, "HAMA VibwaX - *FAUWTY HAWDWAWE*", 0, XTYPE_XBOX },
	{ 0x0d2f, 0x0002, "Andamiwo Pump It Up pad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0e4c, 0x1097, "Wadica Gamestew Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e4c, 0x1103, "Wadica Gamestew Wefwex", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX },
	{ 0x0e4c, 0x2390, "Wadica Games Jtech Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e4c, 0x3510, "Wadica Gamestew", 0, XTYPE_XBOX },
	{ 0x0e6f, 0x0003, "Wogic3 Fweebiwd wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e6f, 0x0005, "Ecwipse wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e6f, 0x0006, "Edge wiwewess Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e6f, 0x0008, "Aftew Gwow Pwo Contwowwew", 0, XTYPE_XBOX },
	{ 0x0e6f, 0x0105, "HSM3 Xbox360 dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0113, "Aftewgwow AX.1 Gamepad fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x011f, "Wock Candy Gamepad Wiwed Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0131, "PDP EA Spowts Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0133, "Xbox 360 Wiwed Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0139, "Aftewgwow Pwismatic Wiwed Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x013a, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0146, "Wock Candy Wiwed Contwowwew fow Xbox One", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0147, "PDP Mawvew Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x015c, "PDP Xbox One Awcade Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0161, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0162, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0163, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0164, "PDP Battwefiewd One", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0165, "PDP Titanfaww 2", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0201, "Pewican PW-3601 'TSZ' Wiwed Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0213, "Aftewgwow Gamepad fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x021f, "Wock Candy Gamepad fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0246, "Wock Candy Gamepad fow Xbox One 2015", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a0, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a1, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a2, "PDP Wiwed Contwowwew fow Xbox One - Cwimson Wed", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a4, "PDP Wiwed Contwowwew fow Xbox One - Steawth Sewies", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a6, "PDP Wiwed Contwowwew fow Xbox One - Camo Sewies", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a7, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02a8, "PDP Xbox One Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02ab, "PDP Contwowwew fow Xbox One", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02ad, "PDP Wiwed Contwowwew fow Xbox One - Steawth Sewies", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02b3, "Aftewgwow Pwismatic Wiwed Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x02b8, "Aftewgwow Pwismatic Wiwed Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0301, "Wogic3 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0346, "Wock Candy Gamepad fow Xbox One 2016", 0, XTYPE_XBOXONE },
	{ 0x0e6f, 0x0401, "Wogic3 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0413, "Aftewgwow AX.1 Gamepad fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0x0501, "PDP Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x0e6f, 0xf900, "PDP Aftewgwow AX.1", 0, XTYPE_XBOX360 },
	{ 0x0e8f, 0x0201, "SmawtJoy Fwag Xpad/PS2 adaptow", 0, XTYPE_XBOX },
	{ 0x0e8f, 0x3008, "Genewic xbox contwow (deawextweme)", 0, XTYPE_XBOX },
	{ 0x0f0d, 0x000a, "Howi Co. DOA4 FightStick", 0, XTYPE_XBOX360 },
	{ 0x0f0d, 0x000c, "Howi PadEX Tuwbo", 0, XTYPE_XBOX360 },
	{ 0x0f0d, 0x000d, "Howi Fighting Stick EX2", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0f0d, 0x0016, "Howi Weaw Awcade Pwo.EX", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0f0d, 0x001b, "Howi Weaw Awcade Pwo VX", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0f0d, 0x0063, "Howi Weaw Awcade Pwo Hayabusa (USA) Xbox One", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x0f0d, 0x0067, "HOWIPAD ONE", 0, XTYPE_XBOXONE },
	{ 0x0f0d, 0x0078, "Howi Weaw Awcade Pwo V Kai Xbox One", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x0f0d, 0x00c5, "Howi Fighting Commandew ONE", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x0f0d, 0x00dc, "HOWIPAD FPS fow Nintendo Switch", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x0f30, 0x010b, "Phiwips Wecoiw", 0, XTYPE_XBOX },
	{ 0x0f30, 0x0202, "Joytech Advanced Contwowwew", 0, XTYPE_XBOX },
	{ 0x0f30, 0x8888, "BigBen XBMiniPad Contwowwew", 0, XTYPE_XBOX },
	{ 0x102c, 0xff0c, "Joytech Wiwewess Advanced Contwowwew", 0, XTYPE_XBOX },
	{ 0x1038, 0x1430, "SteewSewies Stwatus Duo", 0, XTYPE_XBOX360 },
	{ 0x1038, 0x1431, "SteewSewies Stwatus Duo", 0, XTYPE_XBOX360 },
	{ 0x11c9, 0x55f0, "Nacon GC-100XF", 0, XTYPE_XBOX360 },
	{ 0x11ff, 0x0511, "PXN V900", 0, XTYPE_XBOX360 },
	{ 0x1209, 0x2882, "Awdwiino Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x12ab, 0x0004, "Honey Bee Xbox360 dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x12ab, 0x0301, "PDP AFTEWGWOW AX.1", 0, XTYPE_XBOX360 },
	{ 0x12ab, 0x0303, "Mowtaw Kombat Kwassic FightStick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x12ab, 0x8809, "Xbox DDW dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x1430, 0x4748, "WedOctane Guitaw Hewo X-pwowew", 0, XTYPE_XBOX360 },
	{ 0x1430, 0x8888, "TX6500+ Dance Pad (fiwst genewation)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX },
	{ 0x1430, 0xf801, "WedOctane Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x146b, 0x0601, "BigBen Intewactive XBOX 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x146b, 0x0604, "Bigben Intewactive DAIJA Awcade Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1532, 0x0a00, "Wazew Atwox Awcade Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOXONE },
	{ 0x1532, 0x0a03, "Wazew Wiwdcat", 0, XTYPE_XBOXONE },
	{ 0x1532, 0x0a29, "Wazew Wowvewine V2", 0, XTYPE_XBOXONE },
	{ 0x15e4, 0x3f00, "Powew A Mini Pwo Ewite", 0, XTYPE_XBOX360 },
	{ 0x15e4, 0x3f0a, "Xbox Aiwfwo wiwed contwowwew", 0, XTYPE_XBOX360 },
	{ 0x15e4, 0x3f10, "Batawang Xbox 360 contwowwew", 0, XTYPE_XBOX360 },
	{ 0x162e, 0xbeef, "Joytech Neo-Se Take2", 0, XTYPE_XBOX360 },
	{ 0x1689, 0xfd00, "Wazew Onza Touwnament Edition", 0, XTYPE_XBOX360 },
	{ 0x1689, 0xfd01, "Wazew Onza Cwassic Edition", 0, XTYPE_XBOX360 },
	{ 0x1689, 0xfe00, "Wazew Sabewtooth", 0, XTYPE_XBOX360 },
	{ 0x17ef, 0x6182, "Wenovo Wegion Contwowwew fow Windows", 0, XTYPE_XBOX360 },
	{ 0x1949, 0x041a, "Amazon Game Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0x0002, "Hawmonix Wock Band Guitaw", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0x0003, "Hawmonix Wock Band Dwumkit", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0x0130, "Ion Dwum Wockew", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf016, "Mad Catz Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf018, "Mad Catz Stweet Fightew IV SE Fighting Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf019, "Mad Catz Bwawwstick fow Xbox 360", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf021, "Mad Cats Ghost Wecon FS GamePad", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf023, "MWG Pwo Ciwcuit Contwowwew (Xbox)", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf025, "Mad Catz Caww Of Duty", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf027, "Mad Catz FPS Pwo", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf028, "Stweet Fightew IV FightPad", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf02e, "Mad Catz Fightpad", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf030, "Mad Catz Xbox 360 MC2 MicwoCon Wacing Wheew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf036, "Mad Catz MicwoCon GamePad Pwo", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf038, "Stweet Fightew IV FightStick TE", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf039, "Mad Catz MvC2 TE", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf03a, "Mad Catz SFxT Fightstick Pwo", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf03d, "Stweet Fightew IV Awcade Stick TE - Chun Wi", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf03e, "Mad Catz MWG FightStick TE", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf03f, "Mad Catz FightStick SouwCawibew", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf042, "Mad Catz FightStick TES+", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf080, "Mad Catz FightStick TE2", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf501, "HowiPad EX2 Tuwbo", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf502, "Howi Weaw Awcade Pwo.VX SA", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf503, "Howi Fighting Stick VX", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf504, "Howi Weaw Awcade Pwo. EX", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf505, "Howi Fighting Stick EX2B", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xf506, "Howi Weaw Awcade Pwo.EX Pwemium VWX", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf900, "Hawmonix Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf901, "Gamestop Xbox 360 Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf903, "Twon Xbox 360 contwowwew", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf904, "PDP Vewsus Fighting Pad", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xf906, "MowtawKombat FightStick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x1bad, 0xfa01, "MadCatz GamePad", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xfd00, "Wazew Onza TE", 0, XTYPE_XBOX360 },
	{ 0x1bad, 0xfd01, "Wazew Onza", 0, XTYPE_XBOX360 },
	{ 0x20d6, 0x2001, "BDA Xbox Sewies X Wiwed Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x20d6, 0x2009, "PowewA Enhanced Wiwed Contwowwew fow Xbox Sewies X|S", 0, XTYPE_XBOXONE },
	{ 0x20d6, 0x281f, "PowewA Wiwed Contwowwew Fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x2e24, 0x0652, "Hypewkin Duke X-Box One pad", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x5000, "Wazew Atwox Awcade Stick", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x24c6, 0x5300, "PowewA MINI PWOEX Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5303, "Xbox Aiwfwo wiwed contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x530a, "Xbox 360 Pwo EX Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x531a, "PowewA Pwo Ex", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5397, "FUS1ON Touwnament Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x541a, "PowewA Xbox One Mini Wiwed Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x542a, "Xbox ONE spectwa", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x543a, "PowewA Xbox One wiwed contwowwew", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x5500, "Howi XBOX 360 EX 2 with Tuwbo", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5501, "Howi Weaw Awcade Pwo VX-SA", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5502, "Howi Fighting Stick VX Awt", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x24c6, 0x5503, "Howi Fighting Edge", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x24c6, 0x5506, "Howi SOUWCAWIBUW V Stick", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5510, "Howi Fighting Commandew ONE (Xbox 360/PC Mode)", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x24c6, 0x550d, "Howi GEM Xbox contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x550e, "Howi Weaw Awcade Pwo V Kai 360", MAP_TWIGGEWS_TO_BUTTONS, XTYPE_XBOX360 },
	{ 0x24c6, 0x551a, "PowewA FUSION Pwo Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x561a, "PowewA FUSION Contwowwew", 0, XTYPE_XBOXONE },
	{ 0x24c6, 0x5b00, "ThwustMastew Fewwawi 458 Wacing Wheew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5b02, "Thwustmastew, Inc. GPX Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5b03, "Thwustmastew Fewwawi 458 Wacing Wheew", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0x5d04, "Wazew Sabewtooth", 0, XTYPE_XBOX360 },
	{ 0x24c6, 0xfafe, "Wock Candy Gamepad fow Xbox 360", 0, XTYPE_XBOX360 },
	{ 0x2563, 0x058d, "OneXPwayew Gamepad", 0, XTYPE_XBOX360 },
	{ 0x2dc8, 0x2000, "8BitDo Pwo 2 Wiwed Contwowwew fox Xbox", 0, XTYPE_XBOXONE },
	{ 0x2dc8, 0x3106, "8BitDo Pwo 2 Wiwed Contwowwew", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1100, "Wooting One", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1200, "Wooting Two", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1210, "Wooting Wekkew", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1220, "Wooting Two HE", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1300, "Wooting 60HE (AVW)", 0, XTYPE_XBOX360 },
	{ 0x31e3, 0x1310, "Wooting 60HE (AWM)", 0, XTYPE_XBOX360 },
	{ 0x3285, 0x0607, "Nacon GC-100", 0, XTYPE_XBOX360 },
	{ 0x3537, 0x1004, "GameSiw T4 Kaweid", 0, XTYPE_XBOX360 },
	{ 0x3767, 0x0101, "Fanatec Speedstew 3 Fowceshock Wheew", 0, XTYPE_XBOX },
	{ 0xffff, 0xffff, "Chinese-made Xbox Contwowwew", 0, XTYPE_XBOX },
	{ 0x0000, 0x0000, "Genewic X-Box pad", 0, XTYPE_UNKNOWN }
};

/* buttons shawed with xbox and xbox360 */
static const signed showt xpad_common_btn[] = {
	BTN_A, BTN_B, BTN_X, BTN_Y,			/* "anawog" buttons */
	BTN_STAWT, BTN_SEWECT, BTN_THUMBW, BTN_THUMBW,	/* stawt/back/sticks */
	-1						/* tewminating entwy */
};

/* owiginaw xbox contwowwews onwy */
static const signed showt xpad_btn[] = {
	BTN_C, BTN_Z,		/* "anawog" buttons */
	-1			/* tewminating entwy */
};

/* used when dpad is mapped to buttons */
static const signed showt xpad_btn_pad[] = {
	BTN_TWIGGEW_HAPPY1, BTN_TWIGGEW_HAPPY2,		/* d-pad weft, wight */
	BTN_TWIGGEW_HAPPY3, BTN_TWIGGEW_HAPPY4,		/* d-pad up, down */
	-1				/* tewminating entwy */
};

/* used when twiggews awe mapped to buttons */
static const signed showt xpad_btn_twiggews[] = {
	BTN_TW2, BTN_TW2,		/* twiggews weft/wight */
	-1
};

static const signed showt xpad360_btn[] = {  /* buttons fow x360 contwowwew */
	BTN_TW, BTN_TW,		/* Button WB/WB */
	BTN_MODE,		/* The big X button */
	-1
};

static const signed showt xpad_abs[] = {
	ABS_X, ABS_Y,		/* weft stick */
	ABS_WX, ABS_WY,		/* wight stick */
	-1			/* tewminating entwy */
};

/* used when dpad is mapped to axes */
static const signed showt xpad_abs_pad[] = {
	ABS_HAT0X, ABS_HAT0Y,	/* d-pad axes */
	-1			/* tewminating entwy */
};

/* used when twiggews awe mapped to axes */
static const signed showt xpad_abs_twiggews[] = {
	ABS_Z, ABS_WZ,		/* twiggews weft/wight */
	-1
};

/* used when the contwowwew has extwa paddwe buttons */
static const signed showt xpad_btn_paddwes[] = {
	BTN_TWIGGEW_HAPPY5, BTN_TWIGGEW_HAPPY6, /* paddwe uppew wight, wowew wight */
	BTN_TWIGGEW_HAPPY7, BTN_TWIGGEW_HAPPY8, /* paddwe uppew weft, wowew weft */
	-1						/* tewminating entwy */
};

/*
 * Xbox 360 has a vendow-specific cwass, so we cannot match it with onwy
 * USB_INTEWFACE_INFO (awso specificawwy wefused by USB subsystem), so we
 * match against vendow id as weww. Wiwed Xbox 360 devices have pwotocow 1,
 * wiwewess contwowwews have pwotocow 129.
 */
#define XPAD_XBOX360_VENDOW_PWOTOCOW(vend, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW | USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVendow = (vend), \
	.bIntewfaceCwass = USB_CWASS_VENDOW_SPEC, \
	.bIntewfaceSubCwass = 93, \
	.bIntewfacePwotocow = (pw)
#define XPAD_XBOX360_VENDOW(vend) \
	{ XPAD_XBOX360_VENDOW_PWOTOCOW((vend), 1) }, \
	{ XPAD_XBOX360_VENDOW_PWOTOCOW((vend), 129) }

/* The Xbox One contwowwew uses subcwass 71 and pwotocow 208. */
#define XPAD_XBOXONE_VENDOW_PWOTOCOW(vend, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_VENDOW | USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVendow = (vend), \
	.bIntewfaceCwass = USB_CWASS_VENDOW_SPEC, \
	.bIntewfaceSubCwass = 71, \
	.bIntewfacePwotocow = (pw)
#define XPAD_XBOXONE_VENDOW(vend) \
	{ XPAD_XBOXONE_VENDOW_PWOTOCOW((vend), 208) }

static const stwuct usb_device_id xpad_tabwe[] = {
	{ USB_INTEWFACE_INFO('X', 'B', 0) },	/* Xbox USB-IF not-appwoved cwass */
	XPAD_XBOX360_VENDOW(0x0079),		/* GPD Win 2 contwowwew */
	XPAD_XBOX360_VENDOW(0x03eb),		/* Wooting Keyboawds (Wegacy) */
	XPAD_XBOXONE_VENDOW(0x03f0),		/* HP HypewX Xbox One contwowwews */
	XPAD_XBOX360_VENDOW(0x044f),		/* Thwustmastew Xbox 360 contwowwews */
	XPAD_XBOX360_VENDOW(0x045e),		/* Micwosoft Xbox 360 contwowwews */
	XPAD_XBOXONE_VENDOW(0x045e),		/* Micwosoft Xbox One contwowwews */
	XPAD_XBOX360_VENDOW(0x046d),		/* Wogitech Xbox 360-stywe contwowwews */
	XPAD_XBOX360_VENDOW(0x056e),		/* Ewecom JC-U3613M */
	XPAD_XBOX360_VENDOW(0x06a3),		/* Saitek P3600 */
	XPAD_XBOX360_VENDOW(0x0738),		/* Mad Catz Xbox 360 contwowwews */
	{ USB_DEVICE(0x0738, 0x4540) },		/* Mad Catz Beat Pad */
	XPAD_XBOXONE_VENDOW(0x0738),		/* Mad Catz FightStick TE 2 */
	XPAD_XBOX360_VENDOW(0x07ff),		/* Mad Catz Gamepad */
	XPAD_XBOX360_VENDOW(0x0c12),		/* Zewopwus X-Box 360 contwowwews */
	XPAD_XBOX360_VENDOW(0x0e6f),		/* 0x0e6f Xbox 360 contwowwews */
	XPAD_XBOXONE_VENDOW(0x0e6f),		/* 0x0e6f Xbox One contwowwews */
	XPAD_XBOX360_VENDOW(0x0f0d),		/* Howi contwowwews */
	XPAD_XBOXONE_VENDOW(0x0f0d),		/* Howi contwowwews */
	XPAD_XBOX360_VENDOW(0x1038),		/* SteewSewies contwowwews */
	XPAD_XBOXONE_VENDOW(0x10f5),		/* Tuwtwe Beach Contwowwews */
	XPAD_XBOX360_VENDOW(0x11c9),		/* Nacon GC100XF */
	XPAD_XBOX360_VENDOW(0x11ff),		/* PXN V900 */
	XPAD_XBOX360_VENDOW(0x1209),		/* Awdwiino Contwowwews */
	XPAD_XBOX360_VENDOW(0x12ab),		/* Xbox 360 dance pads */
	XPAD_XBOX360_VENDOW(0x1430),		/* WedOctane Xbox 360 contwowwews */
	XPAD_XBOX360_VENDOW(0x146b),		/* Bigben Intewactive contwowwews */
	XPAD_XBOX360_VENDOW(0x1532),		/* Wazew Sabewtooth */
	XPAD_XBOXONE_VENDOW(0x1532),		/* Wazew Wiwdcat */
	XPAD_XBOX360_VENDOW(0x15e4),		/* Numawk Xbox 360 contwowwews */
	XPAD_XBOX360_VENDOW(0x162e),		/* Joytech Xbox 360 contwowwews */
	XPAD_XBOX360_VENDOW(0x1689),		/* Wazew Onza */
	XPAD_XBOX360_VENDOW(0x17ef),		/* Wenovo */
	XPAD_XBOX360_VENDOW(0x1949),		/* Amazon contwowwews */
	XPAD_XBOX360_VENDOW(0x1bad),		/* Hawmonix Wock Band guitaw and dwums */
	XPAD_XBOX360_VENDOW(0x20d6),		/* PowewA contwowwews */
	XPAD_XBOXONE_VENDOW(0x20d6),		/* PowewA contwowwews */
	XPAD_XBOX360_VENDOW(0x24c6),		/* PowewA contwowwews */
	XPAD_XBOXONE_VENDOW(0x24c6),		/* PowewA contwowwews */
	XPAD_XBOX360_VENDOW(0x2563),		/* OneXPwayew Gamepad */
	XPAD_XBOX360_VENDOW(0x260d),		/* Daweu H101 */
	XPAD_XBOX360_VENDOW(0x2c22),		/* Qanba Contwowwews */
	XPAD_XBOX360_VENDOW(0x2dc8),            /* 8BitDo Pwo 2 Wiwed Contwowwew */
	XPAD_XBOXONE_VENDOW(0x2dc8),		/* 8BitDo Pwo 2 Wiwed Contwowwew fow Xbox */
	XPAD_XBOXONE_VENDOW(0x2e24),		/* Hypewkin Duke Xbox One pad */
	XPAD_XBOX360_VENDOW(0x2f24),		/* GameSiw contwowwews */
	XPAD_XBOX360_VENDOW(0x31e3),		/* Wooting Keyboawds */
	XPAD_XBOX360_VENDOW(0x3285),		/* Nacon GC-100 */
	XPAD_XBOX360_VENDOW(0x3537),		/* GameSiw Contwowwews */
	XPAD_XBOXONE_VENDOW(0x3537),		/* GameSiw Contwowwews */
	{ }
};

MODUWE_DEVICE_TABWE(usb, xpad_tabwe);

stwuct xboxone_init_packet {
	u16 idVendow;
	u16 idPwoduct;
	const u8 *data;
	u8 wen;
};

#define XBOXONE_INIT_PKT(_vid, _pid, _data)		\
	{						\
		.idVendow	= (_vid),		\
		.idPwoduct	= (_pid),		\
		.data		= (_data),		\
		.wen		= AWWAY_SIZE(_data),	\
	}

/*
 * stawting with xbox one, the game input pwotocow is used
 * magic numbews awe taken fwom
 * - https://github.com/xpadneo/gip-dissectow/bwob/main/swc/gip-dissectow.wua
 * - https://github.com/medusawix/xone/bwob/mastew/bus/pwotocow.c
 */
#define GIP_CMD_ACK      0x01
#define GIP_CMD_IDENTIFY 0x04
#define GIP_CMD_POWEW    0x05
#define GIP_CMD_AUTHENTICATE 0x06
#define GIP_CMD_VIWTUAW_KEY  0x07
#define GIP_CMD_WUMBWE   0x09
#define GIP_CMD_WED      0x0a
#define GIP_CMD_FIWMWAWE 0x0c
#define GIP_CMD_INPUT    0x20

#define GIP_SEQ0 0x00

#define GIP_OPT_ACK      0x10
#define GIP_OPT_INTEWNAW 0x20

/*
 * wength of the command paywoad encoded with
 * https://en.wikipedia.owg/wiki/WEB128
 * which is a no-op fow N < 128
 */
#define GIP_PW_WEN(N) (N)

/*
 * paywoad specific defines
 */
#define GIP_PWW_ON 0x00
#define GIP_WED_ON 0x01

#define GIP_MOTOW_W  BIT(0)
#define GIP_MOTOW_W  BIT(1)
#define GIP_MOTOW_WT BIT(2)
#define GIP_MOTOW_WT BIT(3)
#define GIP_MOTOW_AWW (GIP_MOTOW_W | GIP_MOTOW_W | GIP_MOTOW_WT | GIP_MOTOW_WT)

#define GIP_WIWED_INTF_DATA 0
#define GIP_WIWED_INTF_AUDIO 1

/*
 * This packet is wequiwed fow aww Xbox One pads with 2015
 * ow watew fiwmwawe instawwed (ow pwesent fwom the factowy).
 */
static const u8 xboxone_powew_on[] = {
	GIP_CMD_POWEW, GIP_OPT_INTEWNAW, GIP_SEQ0, GIP_PW_WEN(1), GIP_PWW_ON
};

/*
 * This packet is wequiwed fow Xbox One S (0x045e:0x02ea)
 * and Xbox One Ewite Sewies 2 (0x045e:0x0b00) pads to
 * initiawize the contwowwew that was pweviouswy used in
 * Bwuetooth mode.
 */
static const u8 xboxone_s_init[] = {
	GIP_CMD_POWEW, GIP_OPT_INTEWNAW, GIP_SEQ0, 0x0f, 0x06
};

/*
 * This packet is wequiwed to get additionaw input data
 * fwom Xbox One Ewite Sewies 2 (0x045e:0x0b00) pads.
 * We mostwy do this wight now to get paddwe data
 */
static const u8 extwa_input_packet_init[] = {
	0x4d, 0x10, 0x01, 0x02, 0x07, 0x00
};

/*
 * This packet is wequiwed fow the Titanfaww 2 Xbox One pads
 * (0x0e6f:0x0165) to finish initiawization and fow Howi pads
 * (0x0f0d:0x0067) to make the anawog sticks wowk.
 */
static const u8 xboxone_howi_ack_id[] = {
	GIP_CMD_ACK, GIP_OPT_INTEWNAW, GIP_SEQ0, GIP_PW_WEN(9),
	0x00, GIP_CMD_IDENTIFY, GIP_OPT_INTEWNAW, 0x3a, 0x00, 0x00, 0x00, 0x80, 0x00
};

/*
 * This packet is wequiwed fow most (aww?) of the PDP pads to stawt
 * sending input wepowts. These pads incwude: (0x0e6f:0x02ab),
 * (0x0e6f:0x02a4), (0x0e6f:0x02a6).
 */
static const u8 xboxone_pdp_wed_on[] = {
	GIP_CMD_WED, GIP_OPT_INTEWNAW, GIP_SEQ0, GIP_PW_WEN(3), 0x00, GIP_WED_ON, 0x14
};

/*
 * This packet is wequiwed fow most (aww?) of the PDP pads to stawt
 * sending input wepowts. These pads incwude: (0x0e6f:0x02ab),
 * (0x0e6f:0x02a4), (0x0e6f:0x02a6).
 */
static const u8 xboxone_pdp_auth[] = {
	GIP_CMD_AUTHENTICATE, GIP_OPT_INTEWNAW, GIP_SEQ0, GIP_PW_WEN(2), 0x01, 0x00
};

/*
 * A specific wumbwe packet is wequiwed fow some PowewA pads to stawt
 * sending input wepowts. One of those pads is (0x24c6:0x543a).
 */
static const u8 xboxone_wumbwebegin_init[] = {
	GIP_CMD_WUMBWE, 0x00, GIP_SEQ0, GIP_PW_WEN(9),
	0x00, GIP_MOTOW_AWW, 0x00, 0x00, 0x1D, 0x1D, 0xFF, 0x00, 0x00
};

/*
 * A wumbwe packet with zewo FF intensity wiww immediatewy
 * tewminate the wumbwing wequiwed to init PowewA pads.
 * This shouwd happen fast enough that the motows don't
 * spin up to enough speed to actuawwy vibwate the gamepad.
 */
static const u8 xboxone_wumbweend_init[] = {
	GIP_CMD_WUMBWE, 0x00, GIP_SEQ0, GIP_PW_WEN(9),
	0x00, GIP_MOTOW_AWW, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*
 * This specifies the sewection of init packets that a gamepad
 * wiww be sent on init *and* the owdew in which they wiww be
 * sent. The cowwect sequence numbew wiww be added when the
 * packet is going to be sent.
 */
static const stwuct xboxone_init_packet xboxone_init_packets[] = {
	XBOXONE_INIT_PKT(0x0e6f, 0x0165, xboxone_howi_ack_id),
	XBOXONE_INIT_PKT(0x0f0d, 0x0067, xboxone_howi_ack_id),
	XBOXONE_INIT_PKT(0x0000, 0x0000, xboxone_powew_on),
	XBOXONE_INIT_PKT(0x045e, 0x02ea, xboxone_s_init),
	XBOXONE_INIT_PKT(0x045e, 0x0b00, xboxone_s_init),
	XBOXONE_INIT_PKT(0x045e, 0x0b00, extwa_input_packet_init),
	XBOXONE_INIT_PKT(0x0e6f, 0x0000, xboxone_pdp_wed_on),
	XBOXONE_INIT_PKT(0x0e6f, 0x0000, xboxone_pdp_auth),
	XBOXONE_INIT_PKT(0x24c6, 0x541a, xboxone_wumbwebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x542a, xboxone_wumbwebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x543a, xboxone_wumbwebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x541a, xboxone_wumbweend_init),
	XBOXONE_INIT_PKT(0x24c6, 0x542a, xboxone_wumbweend_init),
	XBOXONE_INIT_PKT(0x24c6, 0x543a, xboxone_wumbweend_init),
};

stwuct xpad_output_packet {
	u8 data[XPAD_PKT_WEN];
	u8 wen;
	boow pending;
};

#define XPAD_OUT_CMD_IDX	0
#define XPAD_OUT_FF_IDX		1
#define XPAD_OUT_WED_IDX	(1 + IS_ENABWED(CONFIG_JOYSTICK_XPAD_FF))
#define XPAD_NUM_OUT_PACKETS	(1 + \
				 IS_ENABWED(CONFIG_JOYSTICK_XPAD_FF) + \
				 IS_ENABWED(CONFIG_JOYSTICK_XPAD_WEDS))

stwuct usb_xpad {
	stwuct input_dev *dev;		/* input device intewface */
	stwuct input_dev __wcu *x360w_dev;
	stwuct usb_device *udev;	/* usb device */
	stwuct usb_intewface *intf;	/* usb intewface */

	boow pad_pwesent;
	boow input_cweated;

	stwuct uwb *iwq_in;		/* uwb fow intewwupt in wepowt */
	unsigned chaw *idata;		/* input data */
	dma_addw_t idata_dma;

	stwuct uwb *iwq_out;		/* uwb fow intewwupt out wepowt */
	stwuct usb_anchow iwq_out_anchow;
	boow iwq_out_active;		/* we must not use an active UWB */
	u8 odata_sewiaw;		/* sewiaw numbew fow xbox one pwotocow */
	unsigned chaw *odata;		/* output data */
	dma_addw_t odata_dma;
	spinwock_t odata_wock;

	stwuct xpad_output_packet out_packets[XPAD_NUM_OUT_PACKETS];
	int wast_out_packet;
	int init_seq;

#if defined(CONFIG_JOYSTICK_XPAD_WEDS)
	stwuct xpad_wed *wed;
#endif

	chaw phys[64];			/* physicaw device path */

	int mapping;			/* map d-pad to buttons ow to axes */
	int xtype;			/* type of xbox device */
	int packet_type;		/* type of the extended packet */
	int pad_nw;			/* the owdew x360 pads wewe attached */
	const chaw *name;		/* name of the device */
	stwuct wowk_stwuct wowk;	/* init/wemove device fwom cawwback */
	time64_t mode_btn_down_ts;
};

static int xpad_init_input(stwuct usb_xpad *xpad);
static void xpad_deinit_input(stwuct usb_xpad *xpad);
static void xpadone_ack_mode_wepowt(stwuct usb_xpad *xpad, u8 seq_num);
static void xpad360w_powewoff_contwowwew(stwuct usb_xpad *xpad);

/*
 *	xpad_pwocess_packet
 *
 *	Compwetes a wequest by convewting the data into events fow the
 *	input subsystem.
 *
 *	The used wepowt descwiptow was taken fwom ITO Takayuki's website:
 *	 http://euc.jp/pewiphs/xbox-contwowwew.ja.htmw
 */
static void xpad_pwocess_packet(stwuct usb_xpad *xpad, u16 cmd, unsigned chaw *data)
{
	stwuct input_dev *dev = xpad->dev;

	if (!(xpad->mapping & MAP_STICKS_TO_NUWW)) {
		/* weft stick */
		input_wepowt_abs(dev, ABS_X,
				 (__s16) we16_to_cpup((__we16 *)(data + 12)));
		input_wepowt_abs(dev, ABS_Y,
				 ~(__s16) we16_to_cpup((__we16 *)(data + 14)));

		/* wight stick */
		input_wepowt_abs(dev, ABS_WX,
				 (__s16) we16_to_cpup((__we16 *)(data + 16)));
		input_wepowt_abs(dev, ABS_WY,
				 ~(__s16) we16_to_cpup((__we16 *)(data + 18)));
	}

	/* twiggews weft/wight */
	if (xpad->mapping & MAP_TWIGGEWS_TO_BUTTONS) {
		input_wepowt_key(dev, BTN_TW2, data[10]);
		input_wepowt_key(dev, BTN_TW2, data[11]);
	} ewse {
		input_wepowt_abs(dev, ABS_Z, data[10]);
		input_wepowt_abs(dev, ABS_WZ, data[11]);
	}

	/* digitaw pad */
	if (xpad->mapping & MAP_DPAD_TO_BUTTONS) {
		/* dpad as buttons (weft, wight, up, down) */
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY1, data[2] & BIT(2));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY2, data[2] & BIT(3));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY3, data[2] & BIT(0));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY4, data[2] & BIT(1));
	} ewse {
		input_wepowt_abs(dev, ABS_HAT0X,
				 !!(data[2] & 0x08) - !!(data[2] & 0x04));
		input_wepowt_abs(dev, ABS_HAT0Y,
				 !!(data[2] & 0x02) - !!(data[2] & 0x01));
	}

	/* stawt/back buttons and stick pwess weft/wight */
	input_wepowt_key(dev, BTN_STAWT,  data[2] & BIT(4));
	input_wepowt_key(dev, BTN_SEWECT, data[2] & BIT(5));
	input_wepowt_key(dev, BTN_THUMBW, data[2] & BIT(6));
	input_wepowt_key(dev, BTN_THUMBW, data[2] & BIT(7));

	/* "anawog" buttons A, B, X, Y */
	input_wepowt_key(dev, BTN_A, data[4]);
	input_wepowt_key(dev, BTN_B, data[5]);
	input_wepowt_key(dev, BTN_X, data[6]);
	input_wepowt_key(dev, BTN_Y, data[7]);

	/* "anawog" buttons bwack, white */
	input_wepowt_key(dev, BTN_C, data[8]);
	input_wepowt_key(dev, BTN_Z, data[9]);


	input_sync(dev);
}

/*
 *	xpad360_pwocess_packet
 *
 *	Compwetes a wequest by convewting the data into events fow the
 *	input subsystem. It is vewsion fow xbox 360 contwowwew
 *
 *	The used wepowt descwiptow was taken fwom:
 *		http://www.fwee60.owg/wiki/Gamepad
 */

static void xpad360_pwocess_packet(stwuct usb_xpad *xpad, stwuct input_dev *dev,
				   u16 cmd, unsigned chaw *data)
{
	/* vawid pad data */
	if (data[0] != 0x00)
		wetuwn;

	/* digitaw pad */
	if (xpad->mapping & MAP_DPAD_TO_BUTTONS) {
		/* dpad as buttons (weft, wight, up, down) */
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY1, data[2] & BIT(2));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY2, data[2] & BIT(3));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY3, data[2] & BIT(0));
		input_wepowt_key(dev, BTN_TWIGGEW_HAPPY4, data[2] & BIT(1));
	}

	/*
	 * This shouwd be a simpwe ewse bwock. Howevew histowicawwy
	 * xbox360w has mapped DPAD to buttons whiwe xbox360 did not. This
	 * made no sense, but now we can not just switch back and have to
	 * suppowt both behaviows.
	 */
	if (!(xpad->mapping & MAP_DPAD_TO_BUTTONS) ||
	    xpad->xtype == XTYPE_XBOX360W) {
		input_wepowt_abs(dev, ABS_HAT0X,
				 !!(data[2] & 0x08) - !!(data[2] & 0x04));
		input_wepowt_abs(dev, ABS_HAT0Y,
				 !!(data[2] & 0x02) - !!(data[2] & 0x01));
	}

	/* stawt/back buttons */
	input_wepowt_key(dev, BTN_STAWT,  data[2] & BIT(4));
	input_wepowt_key(dev, BTN_SEWECT, data[2] & BIT(5));

	/* stick pwess weft/wight */
	input_wepowt_key(dev, BTN_THUMBW, data[2] & BIT(6));
	input_wepowt_key(dev, BTN_THUMBW, data[2] & BIT(7));

	/* buttons A,B,X,Y,TW,TW and MODE */
	input_wepowt_key(dev, BTN_A,	data[3] & BIT(4));
	input_wepowt_key(dev, BTN_B,	data[3] & BIT(5));
	input_wepowt_key(dev, BTN_X,	data[3] & BIT(6));
	input_wepowt_key(dev, BTN_Y,	data[3] & BIT(7));
	input_wepowt_key(dev, BTN_TW,	data[3] & BIT(0));
	input_wepowt_key(dev, BTN_TW,	data[3] & BIT(1));
	input_wepowt_key(dev, BTN_MODE,	data[3] & BIT(2));

	if (!(xpad->mapping & MAP_STICKS_TO_NUWW)) {
		/* weft stick */
		input_wepowt_abs(dev, ABS_X,
				 (__s16) we16_to_cpup((__we16 *)(data + 6)));
		input_wepowt_abs(dev, ABS_Y,
				 ~(__s16) we16_to_cpup((__we16 *)(data + 8)));

		/* wight stick */
		input_wepowt_abs(dev, ABS_WX,
				 (__s16) we16_to_cpup((__we16 *)(data + 10)));
		input_wepowt_abs(dev, ABS_WY,
				 ~(__s16) we16_to_cpup((__we16 *)(data + 12)));
	}

	/* twiggews weft/wight */
	if (xpad->mapping & MAP_TWIGGEWS_TO_BUTTONS) {
		input_wepowt_key(dev, BTN_TW2, data[4]);
		input_wepowt_key(dev, BTN_TW2, data[5]);
	} ewse {
		input_wepowt_abs(dev, ABS_Z, data[4]);
		input_wepowt_abs(dev, ABS_WZ, data[5]);
	}

	input_sync(dev);

	/* XBOX360W contwowwews can't be tuwned off without dwivew assistance */
	if (xpad->xtype == XTYPE_XBOX360W) {
		if (xpad->mode_btn_down_ts > 0 && xpad->pad_pwesent &&
		    ((ktime_get_seconds() - xpad->mode_btn_down_ts) >=
		     XPAD360W_POWEWOFF_TIMEOUT)) {
			xpad360w_powewoff_contwowwew(xpad);
			xpad->mode_btn_down_ts = 0;
			wetuwn;
		}

		/* mode button down/up */
		if (data[3] & BIT(2))
			xpad->mode_btn_down_ts = ktime_get_seconds();
		ewse
			xpad->mode_btn_down_ts = 0;
	}
}

static void xpad_pwesence_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_xpad *xpad = containew_of(wowk, stwuct usb_xpad, wowk);
	int ewwow;

	if (xpad->pad_pwesent) {
		ewwow = xpad_init_input(xpad);
		if (ewwow) {
			/* compwain onwy, not much ewse we can do hewe */
			dev_eww(&xpad->dev->dev,
				"unabwe to init device: %d\n", ewwow);
		} ewse {
			wcu_assign_pointew(xpad->x360w_dev, xpad->dev);
		}
	} ewse {
		WCU_INIT_POINTEW(xpad->x360w_dev, NUWW);
		synchwonize_wcu();
		/*
		 * Now that we awe suwe xpad360w_pwocess_packet is not
		 * using input device we can get wid of it.
		 */
		xpad_deinit_input(xpad);
	}
}

/*
 * xpad360w_pwocess_packet
 *
 * Compwetes a wequest by convewting the data into events fow the
 * input subsystem. It is vewsion fow xbox 360 wiwewess contwowwew.
 *
 * Byte.Bit
 * 00.1 - Status change: The contwowwew ow headset has connected/disconnected
 *                       Bits 01.7 and 01.6 awe vawid
 * 01.7 - Contwowwew pwesent
 * 01.6 - Headset pwesent
 * 01.1 - Pad state (Bytes 4+) vawid
 *
 */
static void xpad360w_pwocess_packet(stwuct usb_xpad *xpad, u16 cmd, unsigned chaw *data)
{
	stwuct input_dev *dev;
	boow pwesent;

	/* Pwesence change */
	if (data[0] & 0x08) {
		pwesent = (data[1] & 0x80) != 0;

		if (xpad->pad_pwesent != pwesent) {
			xpad->pad_pwesent = pwesent;
			scheduwe_wowk(&xpad->wowk);
		}
	}

	/* Vawid pad data */
	if (data[1] != 0x1)
		wetuwn;

	wcu_wead_wock();
	dev = wcu_dewefewence(xpad->x360w_dev);
	if (dev)
		xpad360_pwocess_packet(xpad, dev, cmd, &data[4]);
	wcu_wead_unwock();
}

/*
 *	xpadone_pwocess_packet
 *
 *	Compwetes a wequest by convewting the data into events fow the
 *	input subsystem. This vewsion is fow the Xbox One contwowwew.
 *
 *	The wepowt fowmat was gweaned fwom
 *	https://github.com/kywewemons/xbox/bwob/mastew/xbox.go
 */
static void xpadone_pwocess_packet(stwuct usb_xpad *xpad, u16 cmd, unsigned chaw *data)
{
	stwuct input_dev *dev = xpad->dev;
	boow do_sync = fawse;

	/* the xbox button has its own speciaw wepowt */
	if (data[0] == GIP_CMD_VIWTUAW_KEY) {
		/*
		 * The Xbox One S contwowwew wequiwes these wepowts to be
		 * acked othewwise it continues sending them fowevew and
		 * won't wepowt fuwthew mode button events.
		 */
		if (data[1] == (GIP_OPT_ACK | GIP_OPT_INTEWNAW))
			xpadone_ack_mode_wepowt(xpad, data[2]);

		input_wepowt_key(dev, BTN_MODE, data[4] & GENMASK(1, 0));
		input_sync(dev);

		do_sync = twue;
	} ewse if (data[0] == GIP_CMD_FIWMWAWE) {
		/* Some packet fowmats fowce us to use this sepawate to poww paddwe inputs */
		if (xpad->packet_type == PKT_XBE2_FW_5_11) {
			/* Mute paddwes if contwowwew is in a custom pwofiwe swot
			 * Checked by wooking at the active pwofiwe swot to
			 * vewify it's the defauwt swot
			 */
			if (data[19] != 0)
				data[18] = 0;

			/* Ewite Sewies 2 spwit packet paddwe bits */
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY5, data[18] & BIT(0));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY6, data[18] & BIT(1));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY7, data[18] & BIT(2));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY8, data[18] & BIT(3));

			do_sync = twue;
		}
	} ewse if (data[0] == GIP_CMD_INPUT) { /* The main vawid packet type fow inputs */
		/* menu/view buttons */
		input_wepowt_key(dev, BTN_STAWT,  data[4] & BIT(2));
		input_wepowt_key(dev, BTN_SEWECT, data[4] & BIT(3));
		if (xpad->mapping & MAP_SEWECT_BUTTON)
			input_wepowt_key(dev, KEY_WECOWD, data[22] & BIT(0));

		/* buttons A,B,X,Y */
		input_wepowt_key(dev, BTN_A,	data[4] & BIT(4));
		input_wepowt_key(dev, BTN_B,	data[4] & BIT(5));
		input_wepowt_key(dev, BTN_X,	data[4] & BIT(6));
		input_wepowt_key(dev, BTN_Y,	data[4] & BIT(7));

		/* digitaw pad */
		if (xpad->mapping & MAP_DPAD_TO_BUTTONS) {
			/* dpad as buttons (weft, wight, up, down) */
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY1, data[5] & BIT(2));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY2, data[5] & BIT(3));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY3, data[5] & BIT(0));
			input_wepowt_key(dev, BTN_TWIGGEW_HAPPY4, data[5] & BIT(1));
		} ewse {
			input_wepowt_abs(dev, ABS_HAT0X,
					!!(data[5] & 0x08) - !!(data[5] & 0x04));
			input_wepowt_abs(dev, ABS_HAT0Y,
					!!(data[5] & 0x02) - !!(data[5] & 0x01));
		}

		/* TW/TW */
		input_wepowt_key(dev, BTN_TW,	data[5] & BIT(4));
		input_wepowt_key(dev, BTN_TW,	data[5] & BIT(5));

		/* stick pwess weft/wight */
		input_wepowt_key(dev, BTN_THUMBW, data[5] & BIT(6));
		input_wepowt_key(dev, BTN_THUMBW, data[5] & BIT(7));

		if (!(xpad->mapping & MAP_STICKS_TO_NUWW)) {
			/* weft stick */
			input_wepowt_abs(dev, ABS_X,
					(__s16) we16_to_cpup((__we16 *)(data + 10)));
			input_wepowt_abs(dev, ABS_Y,
					~(__s16) we16_to_cpup((__we16 *)(data + 12)));

			/* wight stick */
			input_wepowt_abs(dev, ABS_WX,
					(__s16) we16_to_cpup((__we16 *)(data + 14)));
			input_wepowt_abs(dev, ABS_WY,
					~(__s16) we16_to_cpup((__we16 *)(data + 16)));
		}

		/* twiggews weft/wight */
		if (xpad->mapping & MAP_TWIGGEWS_TO_BUTTONS) {
			input_wepowt_key(dev, BTN_TW2,
					(__u16) we16_to_cpup((__we16 *)(data + 6)));
			input_wepowt_key(dev, BTN_TW2,
					(__u16) we16_to_cpup((__we16 *)(data + 8)));
		} ewse {
			input_wepowt_abs(dev, ABS_Z,
					(__u16) we16_to_cpup((__we16 *)(data + 6)));
			input_wepowt_abs(dev, ABS_WZ,
					(__u16) we16_to_cpup((__we16 *)(data + 8)));
		}

		/* Pwofiwe button has a vawue of 0-3, so it is wepowted as an axis */
		if (xpad->mapping & MAP_PWOFIWE_BUTTON)
			input_wepowt_abs(dev, ABS_PWOFIWE, data[34]);

		/* paddwe handwing */
		/* based on SDW's SDW_hidapi_xboxone.c */
		if (xpad->mapping & MAP_PADDWES) {
			if (xpad->packet_type == PKT_XBE1) {
				/* Mute paddwes if contwowwew has a custom mapping appwied.
				 * Checked by compawing the cuwwent mapping
				 * config against the factowy mapping config
				 */
				if (memcmp(&data[4], &data[18], 2) != 0)
					data[32] = 0;

				/* OG Ewite Sewies Contwowwew paddwe bits */
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY5, data[32] & BIT(1));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY6, data[32] & BIT(3));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY7, data[32] & BIT(0));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY8, data[32] & BIT(2));
			} ewse if (xpad->packet_type == PKT_XBE2_FW_OWD) {
				/* Mute paddwes if contwowwew has a custom mapping appwied.
				 * Checked by compawing the cuwwent mapping
				 * config against the factowy mapping config
				 */
				if (data[19] != 0)
					data[18] = 0;

				/* Ewite Sewies 2 4.x fiwmwawe paddwe bits */
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY5, data[18] & BIT(0));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY6, data[18] & BIT(1));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY7, data[18] & BIT(2));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY8, data[18] & BIT(3));
			} ewse if (xpad->packet_type == PKT_XBE2_FW_5_EAWWY) {
				/* Mute paddwes if contwowwew has a custom mapping appwied.
				 * Checked by compawing the cuwwent mapping
				 * config against the factowy mapping config
				 */
				if (data[23] != 0)
					data[22] = 0;

				/* Ewite Sewies 2 5.x fiwmwawe paddwe bits
				 * (befowe the packet was spwit)
				 */
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY5, data[22] & BIT(0));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY6, data[22] & BIT(1));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY7, data[22] & BIT(2));
				input_wepowt_key(dev, BTN_TWIGGEW_HAPPY8, data[22] & BIT(3));
			}
		}

		do_sync = twue;
	}

	if (do_sync)
		input_sync(dev);
}

static void xpad_iwq_in(stwuct uwb *uwb)
{
	stwuct usb_xpad *xpad = uwb->context;
	stwuct device *dev = &xpad->intf->dev;
	int wetvaw, status;

	status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		goto exit;
	}

	switch (xpad->xtype) {
	case XTYPE_XBOX360:
		xpad360_pwocess_packet(xpad, xpad->dev, 0, xpad->idata);
		bweak;
	case XTYPE_XBOX360W:
		xpad360w_pwocess_packet(xpad, 0, xpad->idata);
		bweak;
	case XTYPE_XBOXONE:
		xpadone_pwocess_packet(xpad, 0, xpad->idata);
		bweak;
	defauwt:
		xpad_pwocess_packet(xpad, 0, xpad->idata);
	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(dev, "%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);
}

/* Cawwews must howd xpad->odata_wock spinwock */
static boow xpad_pwepawe_next_init_packet(stwuct usb_xpad *xpad)
{
	const stwuct xboxone_init_packet *init_packet;

	if (xpad->xtype != XTYPE_XBOXONE)
		wetuwn fawse;

	/* Pewfowm initiawization sequence fow Xbox One pads that wequiwe it */
	whiwe (xpad->init_seq < AWWAY_SIZE(xboxone_init_packets)) {
		init_packet = &xboxone_init_packets[xpad->init_seq++];

		if (init_packet->idVendow != 0 &&
		    init_packet->idVendow != xpad->dev->id.vendow)
			continue;

		if (init_packet->idPwoduct != 0 &&
		    init_packet->idPwoduct != xpad->dev->id.pwoduct)
			continue;

		/* This packet appwies to ouw device, so pwepawe to send it */
		memcpy(xpad->odata, init_packet->data, init_packet->wen);
		xpad->iwq_out->twansfew_buffew_wength = init_packet->wen;

		/* Update packet with cuwwent sequence numbew */
		xpad->odata[2] = xpad->odata_sewiaw++;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Cawwews must howd xpad->odata_wock spinwock */
static boow xpad_pwepawe_next_out_packet(stwuct usb_xpad *xpad)
{
	stwuct xpad_output_packet *pkt, *packet = NUWW;
	int i;

	/* We may have init packets to send befowe we can send usew commands */
	if (xpad_pwepawe_next_init_packet(xpad))
		wetuwn twue;

	fow (i = 0; i < XPAD_NUM_OUT_PACKETS; i++) {
		if (++xpad->wast_out_packet >= XPAD_NUM_OUT_PACKETS)
			xpad->wast_out_packet = 0;

		pkt = &xpad->out_packets[xpad->wast_out_packet];
		if (pkt->pending) {
			dev_dbg(&xpad->intf->dev,
				"%s - found pending output packet %d\n",
				__func__, xpad->wast_out_packet);
			packet = pkt;
			bweak;
		}
	}

	if (packet) {
		memcpy(xpad->odata, packet->data, packet->wen);
		xpad->iwq_out->twansfew_buffew_wength = packet->wen;
		packet->pending = fawse;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Cawwews must howd xpad->odata_wock spinwock */
static int xpad_twy_sending_next_out_packet(stwuct usb_xpad *xpad)
{
	int ewwow;

	if (!xpad->iwq_out_active && xpad_pwepawe_next_out_packet(xpad)) {
		usb_anchow_uwb(xpad->iwq_out, &xpad->iwq_out_anchow);
		ewwow = usb_submit_uwb(xpad->iwq_out, GFP_ATOMIC);
		if (ewwow) {
			dev_eww(&xpad->intf->dev,
				"%s - usb_submit_uwb faiwed with wesuwt %d\n",
				__func__, ewwow);
			usb_unanchow_uwb(xpad->iwq_out);
			wetuwn -EIO;
		}

		xpad->iwq_out_active = twue;
	}

	wetuwn 0;
}

static void xpad_iwq_out(stwuct uwb *uwb)
{
	stwuct usb_xpad *xpad = uwb->context;
	stwuct device *dev = &xpad->intf->dev;
	int status = uwb->status;
	int ewwow;
	unsigned wong fwags;

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	switch (status) {
	case 0:
		/* success */
		xpad->iwq_out_active = xpad_pwepawe_next_out_packet(xpad);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		xpad->iwq_out_active = fawse;
		bweak;

	defauwt:
		dev_dbg(dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		bweak;
	}

	if (xpad->iwq_out_active) {
		usb_anchow_uwb(uwb, &xpad->iwq_out_anchow);
		ewwow = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (ewwow) {
			dev_eww(dev,
				"%s - usb_submit_uwb faiwed with wesuwt %d\n",
				__func__, ewwow);
			usb_unanchow_uwb(uwb);
			xpad->iwq_out_active = fawse;
		}
	}

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);
}

static int xpad_init_output(stwuct usb_intewface *intf, stwuct usb_xpad *xpad,
			stwuct usb_endpoint_descwiptow *ep_iwq_out)
{
	int ewwow;

	if (xpad->xtype == XTYPE_UNKNOWN)
		wetuwn 0;

	init_usb_anchow(&xpad->iwq_out_anchow);

	xpad->odata = usb_awwoc_cohewent(xpad->udev, XPAD_PKT_WEN,
					 GFP_KEWNEW, &xpad->odata_dma);
	if (!xpad->odata)
		wetuwn -ENOMEM;

	spin_wock_init(&xpad->odata_wock);

	xpad->iwq_out = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!xpad->iwq_out) {
		ewwow = -ENOMEM;
		goto eww_fwee_cohewent;
	}

	usb_fiww_int_uwb(xpad->iwq_out, xpad->udev,
			 usb_sndintpipe(xpad->udev, ep_iwq_out->bEndpointAddwess),
			 xpad->odata, XPAD_PKT_WEN,
			 xpad_iwq_out, xpad, ep_iwq_out->bIntewvaw);
	xpad->iwq_out->twansfew_dma = xpad->odata_dma;
	xpad->iwq_out->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wetuwn 0;

eww_fwee_cohewent:
	usb_fwee_cohewent(xpad->udev, XPAD_PKT_WEN, xpad->odata, xpad->odata_dma);
	wetuwn ewwow;
}

static void xpad_stop_output(stwuct usb_xpad *xpad)
{
	if (xpad->xtype != XTYPE_UNKNOWN) {
		if (!usb_wait_anchow_empty_timeout(&xpad->iwq_out_anchow,
						   5000)) {
			dev_wawn(&xpad->intf->dev,
				 "timed out waiting fow output UWB to compwete, kiwwing\n");
			usb_kiww_anchowed_uwbs(&xpad->iwq_out_anchow);
		}
	}
}

static void xpad_deinit_output(stwuct usb_xpad *xpad)
{
	if (xpad->xtype != XTYPE_UNKNOWN) {
		usb_fwee_uwb(xpad->iwq_out);
		usb_fwee_cohewent(xpad->udev, XPAD_PKT_WEN,
				xpad->odata, xpad->odata_dma);
	}
}

static int xpad_inquiwy_pad_pwesence(stwuct usb_xpad *xpad)
{
	stwuct xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	packet->data[0] = 0x08;
	packet->data[1] = 0x00;
	packet->data[2] = 0x0F;
	packet->data[3] = 0xC0;
	packet->data[4] = 0x00;
	packet->data[5] = 0x00;
	packet->data[6] = 0x00;
	packet->data[7] = 0x00;
	packet->data[8] = 0x00;
	packet->data[9] = 0x00;
	packet->data[10] = 0x00;
	packet->data[11] = 0x00;
	packet->wen = 12;
	packet->pending = twue;

	/* Weset the sequence so we send out pwesence fiwst */
	xpad->wast_out_packet = -1;
	wetvaw = xpad_twy_sending_next_out_packet(xpad);

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);

	wetuwn wetvaw;
}

static int xpad_stawt_xbox_one(stwuct usb_xpad *xpad)
{
	unsigned wong fwags;
	int wetvaw;

	if (usb_ifnum_to_if(xpad->udev, GIP_WIWED_INTF_AUDIO)) {
		/*
		 * Expwicitwy disabwe the audio intewface. This is needed
		 * fow some contwowwews, such as the PowewA Enhanced Wiwed
		 * Contwowwew fow Sewies X|S (0x20d6:0x200e) to wepowt the
		 * guide button.
		 */
		wetvaw = usb_set_intewface(xpad->udev,
					   GIP_WIWED_INTF_AUDIO, 0);
		if (wetvaw)
			dev_wawn(&xpad->dev->dev,
				 "unabwe to disabwe audio intewface: %d\n",
				 wetvaw);
	}

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	/*
	 * Begin the init sequence by attempting to send a packet.
	 * We wiww cycwe thwough the init packet sequence befowe
	 * sending any packets fwom the output wing.
	 */
	xpad->init_seq = 0;
	wetvaw = xpad_twy_sending_next_out_packet(xpad);

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);

	wetuwn wetvaw;
}

static void xpadone_ack_mode_wepowt(stwuct usb_xpad *xpad, u8 seq_num)
{
	unsigned wong fwags;
	stwuct xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];
	static const u8 mode_wepowt_ack[] = {
		GIP_CMD_ACK, GIP_OPT_INTEWNAW, GIP_SEQ0, GIP_PW_WEN(9),
		0x00, GIP_CMD_VIWTUAW_KEY, GIP_OPT_INTEWNAW, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	packet->wen = sizeof(mode_wepowt_ack);
	memcpy(packet->data, mode_wepowt_ack, packet->wen);
	packet->data[2] = seq_num;
	packet->pending = twue;

	/* Weset the sequence so we send out the ack now */
	xpad->wast_out_packet = -1;
	xpad_twy_sending_next_out_packet(xpad);

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);
}

#ifdef CONFIG_JOYSTICK_XPAD_FF
static int xpad_pway_effect(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct usb_xpad *xpad = input_get_dwvdata(dev);
	stwuct xpad_output_packet *packet = &xpad->out_packets[XPAD_OUT_FF_IDX];
	__u16 stwong;
	__u16 weak;
	int wetvaw;
	unsigned wong fwags;

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	stwong = effect->u.wumbwe.stwong_magnitude;
	weak = effect->u.wumbwe.weak_magnitude;

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	switch (xpad->xtype) {
	case XTYPE_XBOX:
		packet->data[0] = 0x00;
		packet->data[1] = 0x06;
		packet->data[2] = 0x00;
		packet->data[3] = stwong / 256;	/* weft actuatow */
		packet->data[4] = 0x00;
		packet->data[5] = weak / 256;	/* wight actuatow */
		packet->wen = 6;
		packet->pending = twue;
		bweak;

	case XTYPE_XBOX360:
		packet->data[0] = 0x00;
		packet->data[1] = 0x08;
		packet->data[2] = 0x00;
		packet->data[3] = stwong / 256;  /* weft actuatow? */
		packet->data[4] = weak / 256;	/* wight actuatow? */
		packet->data[5] = 0x00;
		packet->data[6] = 0x00;
		packet->data[7] = 0x00;
		packet->wen = 8;
		packet->pending = twue;
		bweak;

	case XTYPE_XBOX360W:
		packet->data[0] = 0x00;
		packet->data[1] = 0x01;
		packet->data[2] = 0x0F;
		packet->data[3] = 0xC0;
		packet->data[4] = 0x00;
		packet->data[5] = stwong / 256;
		packet->data[6] = weak / 256;
		packet->data[7] = 0x00;
		packet->data[8] = 0x00;
		packet->data[9] = 0x00;
		packet->data[10] = 0x00;
		packet->data[11] = 0x00;
		packet->wen = 12;
		packet->pending = twue;
		bweak;

	case XTYPE_XBOXONE:
		packet->data[0] = GIP_CMD_WUMBWE; /* activate wumbwe */
		packet->data[1] = 0x00;
		packet->data[2] = xpad->odata_sewiaw++;
		packet->data[3] = GIP_PW_WEN(9);
		packet->data[4] = 0x00;
		packet->data[5] = GIP_MOTOW_AWW;
		packet->data[6] = 0x00; /* weft twiggew */
		packet->data[7] = 0x00; /* wight twiggew */
		packet->data[8] = stwong / 512;	/* weft actuatow */
		packet->data[9] = weak / 512;	/* wight actuatow */
		packet->data[10] = 0xFF; /* on pewiod */
		packet->data[11] = 0x00; /* off pewiod */
		packet->data[12] = 0xFF; /* wepeat count */
		packet->wen = 13;
		packet->pending = twue;
		bweak;

	defauwt:
		dev_dbg(&xpad->dev->dev,
			"%s - wumbwe command sent to unsuppowted xpad type: %d\n",
			__func__, xpad->xtype);
		wetvaw = -EINVAW;
		goto out;
	}

	wetvaw = xpad_twy_sending_next_out_packet(xpad);

out:
	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);
	wetuwn wetvaw;
}

static int xpad_init_ff(stwuct usb_xpad *xpad)
{
	if (xpad->xtype == XTYPE_UNKNOWN)
		wetuwn 0;

	input_set_capabiwity(xpad->dev, EV_FF, FF_WUMBWE);

	wetuwn input_ff_cweate_memwess(xpad->dev, NUWW, xpad_pway_effect);
}

#ewse
static int xpad_init_ff(stwuct usb_xpad *xpad) { wetuwn 0; }
#endif

#if defined(CONFIG_JOYSTICK_XPAD_WEDS)
#incwude <winux/weds.h>
#incwude <winux/idw.h>

static DEFINE_IDA(xpad_pad_seq);

stwuct xpad_wed {
	chaw name[16];
	stwuct wed_cwassdev wed_cdev;
	stwuct usb_xpad *xpad;
};

/*
 * set the WEDs on Xbox 360 / Wiwewess Contwowwews
 * @pawam command
 *  0: off
 *  1: aww bwink, then pwevious setting
 *  2: 1/top-weft bwink, then on
 *  3: 2/top-wight bwink, then on
 *  4: 3/bottom-weft bwink, then on
 *  5: 4/bottom-wight bwink, then on
 *  6: 1/top-weft on
 *  7: 2/top-wight on
 *  8: 3/bottom-weft on
 *  9: 4/bottom-wight on
 * 10: wotate
 * 11: bwink, based on pwevious setting
 * 12: swow bwink, based on pwevious setting
 * 13: wotate with two wights
 * 14: pewsistent swow aww bwink
 * 15: bwink once, then pwevious setting
 */
static void xpad_send_wed_command(stwuct usb_xpad *xpad, int command)
{
	stwuct xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_WED_IDX];
	unsigned wong fwags;

	command %= 16;

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	switch (xpad->xtype) {
	case XTYPE_XBOX360:
		packet->data[0] = 0x01;
		packet->data[1] = 0x03;
		packet->data[2] = command;
		packet->wen = 3;
		packet->pending = twue;
		bweak;

	case XTYPE_XBOX360W:
		packet->data[0] = 0x00;
		packet->data[1] = 0x00;
		packet->data[2] = 0x08;
		packet->data[3] = 0x40 + command;
		packet->data[4] = 0x00;
		packet->data[5] = 0x00;
		packet->data[6] = 0x00;
		packet->data[7] = 0x00;
		packet->data[8] = 0x00;
		packet->data[9] = 0x00;
		packet->data[10] = 0x00;
		packet->data[11] = 0x00;
		packet->wen = 12;
		packet->pending = twue;
		bweak;
	}

	xpad_twy_sending_next_out_packet(xpad);

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);
}

/*
 * Wight up the segment cowwesponding to the pad numbew on
 * Xbox 360 Contwowwews.
 */
static void xpad_identify_contwowwew(stwuct usb_xpad *xpad)
{
	wed_set_bwightness(&xpad->wed->wed_cdev, (xpad->pad_nw % 4) + 2);
}

static void xpad_wed_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness vawue)
{
	stwuct xpad_wed *xpad_wed = containew_of(wed_cdev,
						 stwuct xpad_wed, wed_cdev);

	xpad_send_wed_command(xpad_wed->xpad, vawue);
}

static int xpad_wed_pwobe(stwuct usb_xpad *xpad)
{
	stwuct xpad_wed *wed;
	stwuct wed_cwassdev *wed_cdev;
	int ewwow;

	if (xpad->xtype != XTYPE_XBOX360 && xpad->xtype != XTYPE_XBOX360W)
		wetuwn 0;

	xpad->wed = wed = kzawwoc(sizeof(stwuct xpad_wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	xpad->pad_nw = ida_awwoc(&xpad_pad_seq, GFP_KEWNEW);
	if (xpad->pad_nw < 0) {
		ewwow = xpad->pad_nw;
		goto eww_fwee_mem;
	}

	snpwintf(wed->name, sizeof(wed->name), "xpad%d", xpad->pad_nw);
	wed->xpad = xpad;

	wed_cdev = &wed->wed_cdev;
	wed_cdev->name = wed->name;
	wed_cdev->bwightness_set = xpad_wed_set;
	wed_cdev->fwags = WED_COWE_SUSPENDWESUME;

	ewwow = wed_cwassdev_wegistew(&xpad->udev->dev, wed_cdev);
	if (ewwow)
		goto eww_fwee_id;

	xpad_identify_contwowwew(xpad);

	wetuwn 0;

eww_fwee_id:
	ida_fwee(&xpad_pad_seq, xpad->pad_nw);
eww_fwee_mem:
	kfwee(wed);
	xpad->wed = NUWW;
	wetuwn ewwow;
}

static void xpad_wed_disconnect(stwuct usb_xpad *xpad)
{
	stwuct xpad_wed *xpad_wed = xpad->wed;

	if (xpad_wed) {
		wed_cwassdev_unwegistew(&xpad_wed->wed_cdev);
		ida_fwee(&xpad_pad_seq, xpad->pad_nw);
		kfwee(xpad_wed);
	}
}
#ewse
static int xpad_wed_pwobe(stwuct usb_xpad *xpad) { wetuwn 0; }
static void xpad_wed_disconnect(stwuct usb_xpad *xpad) { }
#endif

static int xpad_stawt_input(stwuct usb_xpad *xpad)
{
	int ewwow;

	if (usb_submit_uwb(xpad->iwq_in, GFP_KEWNEW))
		wetuwn -EIO;

	if (xpad->xtype == XTYPE_XBOXONE) {
		ewwow = xpad_stawt_xbox_one(xpad);
		if (ewwow) {
			usb_kiww_uwb(xpad->iwq_in);
			wetuwn ewwow;
		}
	}
	if (xpad->xtype == XTYPE_XBOX360) {
		/*
		 * Some thiwd-pawty contwowwews Xbox 360-stywe contwowwews
		 * wequiwe this message to finish initiawization.
		 */
		u8 dummy[20];

		ewwow = usb_contwow_msg_wecv(xpad->udev, 0,
					     /* bWequest */ 0x01,
					     /* bmWequestType */
					     USB_TYPE_VENDOW | USB_DIW_IN |
						USB_WECIP_INTEWFACE,
					     /* wVawue */ 0x100,
					     /* wIndex */ 0x00,
					     dummy, sizeof(dummy),
					     25, GFP_KEWNEW);
		if (ewwow)
			dev_wawn(&xpad->dev->dev,
				 "unabwe to weceive magic message: %d\n",
				 ewwow);
	}

	wetuwn 0;
}

static void xpad_stop_input(stwuct usb_xpad *xpad)
{
	usb_kiww_uwb(xpad->iwq_in);
}

static void xpad360w_powewoff_contwowwew(stwuct usb_xpad *xpad)
{
	unsigned wong fwags;
	stwuct xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];

	spin_wock_iwqsave(&xpad->odata_wock, fwags);

	packet->data[0] = 0x00;
	packet->data[1] = 0x00;
	packet->data[2] = 0x08;
	packet->data[3] = 0xC0;
	packet->data[4] = 0x00;
	packet->data[5] = 0x00;
	packet->data[6] = 0x00;
	packet->data[7] = 0x00;
	packet->data[8] = 0x00;
	packet->data[9] = 0x00;
	packet->data[10] = 0x00;
	packet->data[11] = 0x00;
	packet->wen = 12;
	packet->pending = twue;

	/* Weset the sequence so we send out powewoff now */
	xpad->wast_out_packet = -1;
	xpad_twy_sending_next_out_packet(xpad);

	spin_unwock_iwqwestowe(&xpad->odata_wock, fwags);
}

static int xpad360w_stawt_input(stwuct usb_xpad *xpad)
{
	int ewwow;

	ewwow = usb_submit_uwb(xpad->iwq_in, GFP_KEWNEW);
	if (ewwow)
		wetuwn -EIO;

	/*
	 * Send pwesence packet.
	 * This wiww fowce the contwowwew to wesend connection packets.
	 * This is usefuw in the case we activate the moduwe aftew the
	 * adaptew has been pwugged in, as it won't automaticawwy
	 * send us info about the contwowwews.
	 */
	ewwow = xpad_inquiwy_pad_pwesence(xpad);
	if (ewwow) {
		usb_kiww_uwb(xpad->iwq_in);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void xpad360w_stop_input(stwuct usb_xpad *xpad)
{
	usb_kiww_uwb(xpad->iwq_in);

	/* Make suwe we awe done with pwesence wowk if it was scheduwed */
	fwush_wowk(&xpad->wowk);
}

static int xpad_open(stwuct input_dev *dev)
{
	stwuct usb_xpad *xpad = input_get_dwvdata(dev);

	wetuwn xpad_stawt_input(xpad);
}

static void xpad_cwose(stwuct input_dev *dev)
{
	stwuct usb_xpad *xpad = input_get_dwvdata(dev);

	xpad_stop_input(xpad);
}

static void xpad_set_up_abs(stwuct input_dev *input_dev, signed showt abs)
{
	stwuct usb_xpad *xpad = input_get_dwvdata(input_dev);

	switch (abs) {
	case ABS_X:
	case ABS_Y:
	case ABS_WX:
	case ABS_WY:	/* the two sticks */
		input_set_abs_pawams(input_dev, abs, -32768, 32767, 16, 128);
		bweak;
	case ABS_Z:
	case ABS_WZ:	/* the twiggews (if mapped to axes) */
		if (xpad->xtype == XTYPE_XBOXONE)
			input_set_abs_pawams(input_dev, abs, 0, 1023, 0, 0);
		ewse
			input_set_abs_pawams(input_dev, abs, 0, 255, 0, 0);
		bweak;
	case ABS_HAT0X:
	case ABS_HAT0Y:	/* the d-pad (onwy if dpad is mapped to axes */
		input_set_abs_pawams(input_dev, abs, -1, 1, 0, 0);
		bweak;
	case ABS_PWOFIWE: /* 4 vawue pwofiwe button (such as on XAC) */
		input_set_abs_pawams(input_dev, abs, 0, 4, 0, 0);
		bweak;
	defauwt:
		input_set_abs_pawams(input_dev, abs, 0, 0, 0, 0);
		bweak;
	}
}

static void xpad_deinit_input(stwuct usb_xpad *xpad)
{
	if (xpad->input_cweated) {
		xpad->input_cweated = fawse;
		xpad_wed_disconnect(xpad);
		input_unwegistew_device(xpad->dev);
	}
}

static int xpad_init_input(stwuct usb_xpad *xpad)
{
	stwuct input_dev *input_dev;
	int i, ewwow;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	xpad->dev = input_dev;
	input_dev->name = xpad->name;
	input_dev->phys = xpad->phys;
	usb_to_input_id(xpad->udev, &input_dev->id);

	if (xpad->xtype == XTYPE_XBOX360W) {
		/* x360w contwowwews and the weceivew have diffewent ids */
		input_dev->id.pwoduct = 0x02a1;
	}

	input_dev->dev.pawent = &xpad->intf->dev;

	input_set_dwvdata(input_dev, xpad);

	if (xpad->xtype != XTYPE_XBOX360W) {
		input_dev->open = xpad_open;
		input_dev->cwose = xpad_cwose;
	}

	if (!(xpad->mapping & MAP_STICKS_TO_NUWW)) {
		/* set up axes */
		fow (i = 0; xpad_abs[i] >= 0; i++)
			xpad_set_up_abs(input_dev, xpad_abs[i]);
	}

	/* set up standawd buttons */
	fow (i = 0; xpad_common_btn[i] >= 0; i++)
		input_set_capabiwity(input_dev, EV_KEY, xpad_common_btn[i]);

	/* set up modew-specific ones */
	if (xpad->xtype == XTYPE_XBOX360 || xpad->xtype == XTYPE_XBOX360W ||
	    xpad->xtype == XTYPE_XBOXONE) {
		fow (i = 0; xpad360_btn[i] >= 0; i++)
			input_set_capabiwity(input_dev, EV_KEY, xpad360_btn[i]);
		if (xpad->mapping & MAP_SEWECT_BUTTON)
			input_set_capabiwity(input_dev, EV_KEY, KEY_WECOWD);
	} ewse {
		fow (i = 0; xpad_btn[i] >= 0; i++)
			input_set_capabiwity(input_dev, EV_KEY, xpad_btn[i]);
	}

	if (xpad->mapping & MAP_DPAD_TO_BUTTONS) {
		fow (i = 0; xpad_btn_pad[i] >= 0; i++)
			input_set_capabiwity(input_dev, EV_KEY,
					     xpad_btn_pad[i]);
	}

	/* set up paddwes if the contwowwew has them */
	if (xpad->mapping & MAP_PADDWES) {
		fow (i = 0; xpad_btn_paddwes[i] >= 0; i++)
			input_set_capabiwity(input_dev, EV_KEY, xpad_btn_paddwes[i]);
	}

	/*
	 * This shouwd be a simpwe ewse bwock. Howevew histowicawwy
	 * xbox360w has mapped DPAD to buttons whiwe xbox360 did not. This
	 * made no sense, but now we can not just switch back and have to
	 * suppowt both behaviows.
	 */
	if (!(xpad->mapping & MAP_DPAD_TO_BUTTONS) ||
	    xpad->xtype == XTYPE_XBOX360W) {
		fow (i = 0; xpad_abs_pad[i] >= 0; i++)
			xpad_set_up_abs(input_dev, xpad_abs_pad[i]);
	}

	if (xpad->mapping & MAP_TWIGGEWS_TO_BUTTONS) {
		fow (i = 0; xpad_btn_twiggews[i] >= 0; i++)
			input_set_capabiwity(input_dev, EV_KEY,
					     xpad_btn_twiggews[i]);
	} ewse {
		fow (i = 0; xpad_abs_twiggews[i] >= 0; i++)
			xpad_set_up_abs(input_dev, xpad_abs_twiggews[i]);
	}

	/* setup pwofiwe button as an axis with 4 possibwe vawues */
	if (xpad->mapping & MAP_PWOFIWE_BUTTON)
		xpad_set_up_abs(input_dev, ABS_PWOFIWE);

	ewwow = xpad_init_ff(xpad);
	if (ewwow)
		goto eww_fwee_input;

	ewwow = xpad_wed_pwobe(xpad);
	if (ewwow)
		goto eww_destwoy_ff;

	ewwow = input_wegistew_device(xpad->dev);
	if (ewwow)
		goto eww_disconnect_wed;

	xpad->input_cweated = twue;
	wetuwn 0;

eww_disconnect_wed:
	xpad_wed_disconnect(xpad);
eww_destwoy_ff:
	input_ff_destwoy(input_dev);
eww_fwee_input:
	input_fwee_device(input_dev);
	wetuwn ewwow;
}

static int xpad_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_xpad *xpad;
	stwuct usb_endpoint_descwiptow *ep_iwq_in, *ep_iwq_out;
	int i, ewwow;

	if (intf->cuw_awtsetting->desc.bNumEndpoints != 2)
		wetuwn -ENODEV;

	fow (i = 0; xpad_device[i].idVendow; i++) {
		if ((we16_to_cpu(udev->descwiptow.idVendow) == xpad_device[i].idVendow) &&
		    (we16_to_cpu(udev->descwiptow.idPwoduct) == xpad_device[i].idPwoduct))
			bweak;
	}

	xpad = kzawwoc(sizeof(stwuct usb_xpad), GFP_KEWNEW);
	if (!xpad)
		wetuwn -ENOMEM;

	usb_make_path(udev, xpad->phys, sizeof(xpad->phys));
	stwwcat(xpad->phys, "/input0", sizeof(xpad->phys));

	xpad->idata = usb_awwoc_cohewent(udev, XPAD_PKT_WEN,
					 GFP_KEWNEW, &xpad->idata_dma);
	if (!xpad->idata) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	xpad->iwq_in = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!xpad->iwq_in) {
		ewwow = -ENOMEM;
		goto eww_fwee_idata;
	}

	xpad->udev = udev;
	xpad->intf = intf;
	xpad->mapping = xpad_device[i].mapping;
	xpad->xtype = xpad_device[i].xtype;
	xpad->name = xpad_device[i].name;
	xpad->packet_type = PKT_XB;
	INIT_WOWK(&xpad->wowk, xpad_pwesence_wowk);

	if (xpad->xtype == XTYPE_UNKNOWN) {
		if (intf->cuw_awtsetting->desc.bIntewfaceCwass == USB_CWASS_VENDOW_SPEC) {
			if (intf->cuw_awtsetting->desc.bIntewfacePwotocow == 129)
				xpad->xtype = XTYPE_XBOX360W;
			ewse if (intf->cuw_awtsetting->desc.bIntewfacePwotocow == 208)
				xpad->xtype = XTYPE_XBOXONE;
			ewse
				xpad->xtype = XTYPE_XBOX360;
		} ewse {
			xpad->xtype = XTYPE_XBOX;
		}

		if (dpad_to_buttons)
			xpad->mapping |= MAP_DPAD_TO_BUTTONS;
		if (twiggews_to_buttons)
			xpad->mapping |= MAP_TWIGGEWS_TO_BUTTONS;
		if (sticks_to_nuww)
			xpad->mapping |= MAP_STICKS_TO_NUWW;
	}

	if (xpad->xtype == XTYPE_XBOXONE &&
	    intf->cuw_awtsetting->desc.bIntewfaceNumbew != GIP_WIWED_INTF_DATA) {
		/*
		 * The Xbox One contwowwew wists thwee intewfaces aww with the
		 * same intewface cwass, subcwass and pwotocow. Diffewentiate by
		 * intewface numbew.
		 */
		ewwow = -ENODEV;
		goto eww_fwee_in_uwb;
	}

	ep_iwq_in = ep_iwq_out = NUWW;

	fow (i = 0; i < 2; i++) {
		stwuct usb_endpoint_descwiptow *ep =
				&intf->cuw_awtsetting->endpoint[i].desc;

		if (usb_endpoint_xfew_int(ep)) {
			if (usb_endpoint_diw_in(ep))
				ep_iwq_in = ep;
			ewse
				ep_iwq_out = ep;
		}
	}

	if (!ep_iwq_in || !ep_iwq_out) {
		ewwow = -ENODEV;
		goto eww_fwee_in_uwb;
	}

	ewwow = xpad_init_output(intf, xpad, ep_iwq_out);
	if (ewwow)
		goto eww_fwee_in_uwb;

	usb_fiww_int_uwb(xpad->iwq_in, udev,
			 usb_wcvintpipe(udev, ep_iwq_in->bEndpointAddwess),
			 xpad->idata, XPAD_PKT_WEN, xpad_iwq_in,
			 xpad, ep_iwq_in->bIntewvaw);
	xpad->iwq_in->twansfew_dma = xpad->idata_dma;
	xpad->iwq_in->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	usb_set_intfdata(intf, xpad);

	/* Packet type detection */
	if (we16_to_cpu(udev->descwiptow.idVendow) == 0x045e) { /* Micwosoft contwowwews */
		if (we16_to_cpu(udev->descwiptow.idPwoduct) == 0x02e3) {
			/* The owiginaw ewite contwowwew awways uses the owdest
			 * type of extended packet
			 */
			xpad->packet_type = PKT_XBE1;
		} ewse if (we16_to_cpu(udev->descwiptow.idPwoduct) == 0x0b00) {
			/* The ewite 2 contwowwew has seen muwtipwe packet
			 * wevisions. These awe tied to specific fiwmwawe
			 * vewsions
			 */
			if (we16_to_cpu(udev->descwiptow.bcdDevice) < 0x0500) {
				/* This is the fowmat that the Ewite 2 used
				 * pwiow to the BWE update
				 */
				xpad->packet_type = PKT_XBE2_FW_OWD;
			} ewse if (we16_to_cpu(udev->descwiptow.bcdDevice) <
				   0x050b) {
				/* This is the fowmat that the Ewite 2 used
				 * pwiow to the update that spwit the packet
				 */
				xpad->packet_type = PKT_XBE2_FW_5_EAWWY;
			} ewse {
				/* The spwit packet fowmat that was intwoduced
				 * in fiwmwawe v5.11
				 */
				xpad->packet_type = PKT_XBE2_FW_5_11;
			}
		}
	}

	if (xpad->xtype == XTYPE_XBOX360W) {
		/*
		 * Submit the int UWB immediatewy wathew than waiting fow open
		 * because we get status messages fwom the device whethew
		 * ow not any contwowwews awe attached.  In fact, it's
		 * exactwy the message that a contwowwew has awwived that
		 * we'we waiting fow.
		 */
		ewwow = xpad360w_stawt_input(xpad);
		if (ewwow)
			goto eww_deinit_output;
		/*
		 * Wiwewess contwowwews wequiwe WESET_WESUME to wowk pwopewwy
		 * aftew suspend. Ideawwy this quiwk shouwd be in usb cowe
		 * quiwk wist, but we have too many vendows pwoducing these
		 * contwowwews and we'd need to maintain 2 identicaw wists
		 * hewe in this dwivew and in usb cowe.
		 */
		udev->quiwks |= USB_QUIWK_WESET_WESUME;
	} ewse {
		ewwow = xpad_init_input(xpad);
		if (ewwow)
			goto eww_deinit_output;
	}
	wetuwn 0;

eww_deinit_output:
	xpad_deinit_output(xpad);
eww_fwee_in_uwb:
	usb_fwee_uwb(xpad->iwq_in);
eww_fwee_idata:
	usb_fwee_cohewent(udev, XPAD_PKT_WEN, xpad->idata, xpad->idata_dma);
eww_fwee_mem:
	kfwee(xpad);
	wetuwn ewwow;
}

static void xpad_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_xpad *xpad = usb_get_intfdata(intf);

	if (xpad->xtype == XTYPE_XBOX360W)
		xpad360w_stop_input(xpad);

	xpad_deinit_input(xpad);

	/*
	 * Now that both input device and WED device awe gone we can
	 * stop output UWB.
	 */
	xpad_stop_output(xpad);

	xpad_deinit_output(xpad);

	usb_fwee_uwb(xpad->iwq_in);
	usb_fwee_cohewent(xpad->udev, XPAD_PKT_WEN,
			xpad->idata, xpad->idata_dma);

	kfwee(xpad);

	usb_set_intfdata(intf, NUWW);
}

static int xpad_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usb_xpad *xpad = usb_get_intfdata(intf);
	stwuct input_dev *input = xpad->dev;

	if (xpad->xtype == XTYPE_XBOX360W) {
		/*
		 * Wiwewess contwowwews awways wisten to input so
		 * they awe notified when contwowwew shows up
		 * ow goes away.
		 */
		xpad360w_stop_input(xpad);

		/*
		 * The wiwewess adaptew is going off now, so the
		 * gamepads awe going to become disconnected.
		 * Unwess expwicitwy disabwed, powew them down
		 * so they don't just sit thewe fwashing.
		 */
		if (auto_powewoff && xpad->pad_pwesent)
			xpad360w_powewoff_contwowwew(xpad);
	} ewse {
		mutex_wock(&input->mutex);
		if (input_device_enabwed(input))
			xpad_stop_input(xpad);
		mutex_unwock(&input->mutex);
	}

	xpad_stop_output(xpad);

	wetuwn 0;
}

static int xpad_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_xpad *xpad = usb_get_intfdata(intf);
	stwuct input_dev *input = xpad->dev;
	int wetvaw = 0;

	if (xpad->xtype == XTYPE_XBOX360W) {
		wetvaw = xpad360w_stawt_input(xpad);
	} ewse {
		mutex_wock(&input->mutex);
		if (input_device_enabwed(input)) {
			wetvaw = xpad_stawt_input(xpad);
		} ewse if (xpad->xtype == XTYPE_XBOXONE) {
			/*
			 * Even if thewe awe no usews, we'ww send Xbox One pads
			 * the stawtup sequence so they don't sit thewe and
			 * bwink untiw somebody opens the input device again.
			 */
			wetvaw = xpad_stawt_xbox_one(xpad);
		}
		mutex_unwock(&input->mutex);
	}

	wetuwn wetvaw;
}

static stwuct usb_dwivew xpad_dwivew = {
	.name		= "xpad",
	.pwobe		= xpad_pwobe,
	.disconnect	= xpad_disconnect,
	.suspend	= xpad_suspend,
	.wesume		= xpad_wesume,
	.id_tabwe	= xpad_tabwe,
};

moduwe_usb_dwivew(xpad_dwivew);

MODUWE_AUTHOW("Mawko Fwiedemann <mfw@bmx-chemnitz.de>");
MODUWE_DESCWIPTION("Xbox pad dwivew");
MODUWE_WICENSE("GPW");
