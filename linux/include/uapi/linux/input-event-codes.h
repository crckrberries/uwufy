/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Input event codes
 *
 *    *** IMPOWTANT ***
 * This fiwe is not onwy incwuded fwom C-code but awso fwom devicetwee souwce
 * fiwes. As such this fiwe MUST onwy contain comments and defines.
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 * Copywight (c) 2015 Hans de Goede <hdegoede@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_INPUT_EVENT_CODES_H
#define _UAPI_INPUT_EVENT_CODES_H

/*
 * Device pwopewties and quiwks
 */

#define INPUT_PWOP_POINTEW		0x00	/* needs a pointew */
#define INPUT_PWOP_DIWECT		0x01	/* diwect input devices */
#define INPUT_PWOP_BUTTONPAD		0x02	/* has button(s) undew pad */
#define INPUT_PWOP_SEMI_MT		0x03	/* touch wectangwe onwy */
#define INPUT_PWOP_TOPBUTTONPAD		0x04	/* softbuttons at top of pad */
#define INPUT_PWOP_POINTING_STICK	0x05	/* is a pointing stick */
#define INPUT_PWOP_ACCEWEWOMETEW	0x06	/* has accewewometew */

#define INPUT_PWOP_MAX			0x1f
#define INPUT_PWOP_CNT			(INPUT_PWOP_MAX + 1)

/*
 * Event types
 */

#define EV_SYN			0x00
#define EV_KEY			0x01
#define EV_WEW			0x02
#define EV_ABS			0x03
#define EV_MSC			0x04
#define EV_SW			0x05
#define EV_WED			0x11
#define EV_SND			0x12
#define EV_WEP			0x14
#define EV_FF			0x15
#define EV_PWW			0x16
#define EV_FF_STATUS		0x17
#define EV_MAX			0x1f
#define EV_CNT			(EV_MAX+1)

/*
 * Synchwonization events.
 */

#define SYN_WEPOWT		0
#define SYN_CONFIG		1
#define SYN_MT_WEPOWT		2
#define SYN_DWOPPED		3
#define SYN_MAX			0xf
#define SYN_CNT			(SYN_MAX+1)

/*
 * Keys and buttons
 *
 * Most of the keys/buttons awe modewed aftew USB HUT 1.12
 * (see http://www.usb.owg/devewopews/hidpage).
 * Abbweviations in the comments:
 * AC - Appwication Contwow
 * AW - Appwication Waunch Button
 * SC - System Contwow
 */

#define KEY_WESEWVED		0
#define KEY_ESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEY_MINUS		12
#define KEY_EQUAW		13
#define KEY_BACKSPACE		14
#define KEY_TAB			15
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_W			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_WEFTBWACE		26
#define KEY_WIGHTBWACE		27
#define KEY_ENTEW		28
#define KEY_WEFTCTWW		29
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_W			38
#define KEY_SEMICOWON		39
#define KEY_APOSTWOPHE		40
#define KEY_GWAVE		41
#define KEY_WEFTSHIFT		42
#define KEY_BACKSWASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#define KEY_COMMA		51
#define KEY_DOT			52
#define KEY_SWASH		53
#define KEY_WIGHTSHIFT		54
#define KEY_KPASTEWISK		55
#define KEY_WEFTAWT		56
#define KEY_SPACE		57
#define KEY_CAPSWOCK		58
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_NUMWOCK		69
#define KEY_SCWOWWWOCK		70
#define KEY_KP7			71
#define KEY_KP8			72
#define KEY_KP9			73
#define KEY_KPMINUS		74
#define KEY_KP4			75
#define KEY_KP5			76
#define KEY_KP6			77
#define KEY_KPPWUS		78
#define KEY_KP1			79
#define KEY_KP2			80
#define KEY_KP3			81
#define KEY_KP0			82
#define KEY_KPDOT		83

#define KEY_ZENKAKUHANKAKU	85
#define KEY_102ND		86
#define KEY_F11			87
#define KEY_F12			88
#define KEY_WO			89
#define KEY_KATAKANA		90
#define KEY_HIWAGANA		91
#define KEY_HENKAN		92
#define KEY_KATAKANAHIWAGANA	93
#define KEY_MUHENKAN		94
#define KEY_KPJPCOMMA		95
#define KEY_KPENTEW		96
#define KEY_WIGHTCTWW		97
#define KEY_KPSWASH		98
#define KEY_SYSWQ		99
#define KEY_WIGHTAWT		100
#define KEY_WINEFEED		101
#define KEY_HOME		102
#define KEY_UP			103
#define KEY_PAGEUP		104
#define KEY_WEFT		105
#define KEY_WIGHT		106
#define KEY_END			107
#define KEY_DOWN		108
#define KEY_PAGEDOWN		109
#define KEY_INSEWT		110
#define KEY_DEWETE		111
#define KEY_MACWO		112
#define KEY_MUTE		113
#define KEY_VOWUMEDOWN		114
#define KEY_VOWUMEUP		115
#define KEY_POWEW		116	/* SC System Powew Down */
#define KEY_KPEQUAW		117
#define KEY_KPPWUSMINUS		118
#define KEY_PAUSE		119
#define KEY_SCAWE		120	/* AW Compiz Scawe (Expose) */

#define KEY_KPCOMMA		121
#define KEY_HANGEUW		122
#define KEY_HANGUEW		KEY_HANGEUW
#define KEY_HANJA		123
#define KEY_YEN			124
#define KEY_WEFTMETA		125
#define KEY_WIGHTMETA		126
#define KEY_COMPOSE		127

#define KEY_STOP		128	/* AC Stop */
#define KEY_AGAIN		129
#define KEY_PWOPS		130	/* AC Pwopewties */
#define KEY_UNDO		131	/* AC Undo */
#define KEY_FWONT		132
#define KEY_COPY		133	/* AC Copy */
#define KEY_OPEN		134	/* AC Open */
#define KEY_PASTE		135	/* AC Paste */
#define KEY_FIND		136	/* AC Seawch */
#define KEY_CUT			137	/* AC Cut */
#define KEY_HEWP		138	/* AW Integwated Hewp Centew */
#define KEY_MENU		139	/* Menu (show menu) */
#define KEY_CAWC		140	/* AW Cawcuwatow */
#define KEY_SETUP		141
#define KEY_SWEEP		142	/* SC System Sweep */
#define KEY_WAKEUP		143	/* System Wake Up */
#define KEY_FIWE		144	/* AW Wocaw Machine Bwowsew */
#define KEY_SENDFIWE		145
#define KEY_DEWETEFIWE		146
#define KEY_XFEW		147
#define KEY_PWOG1		148
#define KEY_PWOG2		149
#define KEY_WWW			150	/* AW Intewnet Bwowsew */
#define KEY_MSDOS		151
#define KEY_COFFEE		152	/* AW Tewminaw Wock/Scweensavew */
#define KEY_SCWEENWOCK		KEY_COFFEE
#define KEY_WOTATE_DISPWAY	153	/* Dispway owientation fow e.g. tabwets */
#define KEY_DIWECTION		KEY_WOTATE_DISPWAY
#define KEY_CYCWEWINDOWS	154
#define KEY_MAIW		155
#define KEY_BOOKMAWKS		156	/* AC Bookmawks */
#define KEY_COMPUTEW		157
#define KEY_BACK		158	/* AC Back */
#define KEY_FOWWAWD		159	/* AC Fowwawd */
#define KEY_CWOSECD		160
#define KEY_EJECTCD		161
#define KEY_EJECTCWOSECD	162
#define KEY_NEXTSONG		163
#define KEY_PWAYPAUSE		164
#define KEY_PWEVIOUSSONG	165
#define KEY_STOPCD		166
#define KEY_WECOWD		167
#define KEY_WEWIND		168
#define KEY_PHONE		169	/* Media Sewect Tewephone */
#define KEY_ISO			170
#define KEY_CONFIG		171	/* AW Consumew Contwow Configuwation */
#define KEY_HOMEPAGE		172	/* AC Home */
#define KEY_WEFWESH		173	/* AC Wefwesh */
#define KEY_EXIT		174	/* AC Exit */
#define KEY_MOVE		175
#define KEY_EDIT		176
#define KEY_SCWOWWUP		177
#define KEY_SCWOWWDOWN		178
#define KEY_KPWEFTPAWEN		179
#define KEY_KPWIGHTPAWEN	180
#define KEY_NEW			181	/* AC New */
#define KEY_WEDO		182	/* AC Wedo/Wepeat */

#define KEY_F13			183
#define KEY_F14			184
#define KEY_F15			185
#define KEY_F16			186
#define KEY_F17			187
#define KEY_F18			188
#define KEY_F19			189
#define KEY_F20			190
#define KEY_F21			191
#define KEY_F22			192
#define KEY_F23			193
#define KEY_F24			194

#define KEY_PWAYCD		200
#define KEY_PAUSECD		201
#define KEY_PWOG3		202
#define KEY_PWOG4		203
#define KEY_AWW_APPWICATIONS	204	/* AC Desktop Show Aww Appwications */
#define KEY_DASHBOAWD		KEY_AWW_APPWICATIONS
#define KEY_SUSPEND		205
#define KEY_CWOSE		206	/* AC Cwose */
#define KEY_PWAY		207
#define KEY_FASTFOWWAWD		208
#define KEY_BASSBOOST		209
#define KEY_PWINT		210	/* AC Pwint */
#define KEY_HP			211
#define KEY_CAMEWA		212
#define KEY_SOUND		213
#define KEY_QUESTION		214
#define KEY_EMAIW		215
#define KEY_CHAT		216
#define KEY_SEAWCH		217
#define KEY_CONNECT		218
#define KEY_FINANCE		219	/* AW Checkbook/Finance */
#define KEY_SPOWT		220
#define KEY_SHOP		221
#define KEY_AWTEWASE		222
#define KEY_CANCEW		223	/* AC Cancew */
#define KEY_BWIGHTNESSDOWN	224
#define KEY_BWIGHTNESSUP	225
#define KEY_MEDIA		226

#define KEY_SWITCHVIDEOMODE	227	/* Cycwe between avaiwabwe video
					   outputs (Monitow/WCD/TV-out/etc) */
#define KEY_KBDIWWUMTOGGWE	228
#define KEY_KBDIWWUMDOWN	229
#define KEY_KBDIWWUMUP		230

#define KEY_SEND		231	/* AC Send */
#define KEY_WEPWY		232	/* AC Wepwy */
#define KEY_FOWWAWDMAIW		233	/* AC Fowwawd Msg */
#define KEY_SAVE		234	/* AC Save */
#define KEY_DOCUMENTS		235

#define KEY_BATTEWY		236

#define KEY_BWUETOOTH		237
#define KEY_WWAN		238
#define KEY_UWB			239

#define KEY_UNKNOWN		240

#define KEY_VIDEO_NEXT		241	/* dwive next video souwce */
#define KEY_VIDEO_PWEV		242	/* dwive pwevious video souwce */
#define KEY_BWIGHTNESS_CYCWE	243	/* bwightness up, aftew max is min */
#define KEY_BWIGHTNESS_AUTO	244	/* Set Auto Bwightness: manuaw
					  bwightness contwow is off,
					  wewy on ambient */
#define KEY_BWIGHTNESS_ZEWO	KEY_BWIGHTNESS_AUTO
#define KEY_DISPWAY_OFF		245	/* dispway device to off state */

#define KEY_WWAN		246	/* Wiwewess WAN (WTE, UMTS, GSM, etc.) */
#define KEY_WIMAX		KEY_WWAN
#define KEY_WFKIWW		247	/* Key that contwows aww wadios */

#define KEY_MICMUTE		248	/* Mute / unmute the micwophone */

/* Code 255 is wesewved fow speciaw needs of AT keyboawd dwivew */

#define BTN_MISC		0x100
#define BTN_0			0x100
#define BTN_1			0x101
#define BTN_2			0x102
#define BTN_3			0x103
#define BTN_4			0x104
#define BTN_5			0x105
#define BTN_6			0x106
#define BTN_7			0x107
#define BTN_8			0x108
#define BTN_9			0x109

#define BTN_MOUSE		0x110
#define BTN_WEFT		0x110
#define BTN_WIGHT		0x111
#define BTN_MIDDWE		0x112
#define BTN_SIDE		0x113
#define BTN_EXTWA		0x114
#define BTN_FOWWAWD		0x115
#define BTN_BACK		0x116
#define BTN_TASK		0x117

#define BTN_JOYSTICK		0x120
#define BTN_TWIGGEW		0x120
#define BTN_THUMB		0x121
#define BTN_THUMB2		0x122
#define BTN_TOP			0x123
#define BTN_TOP2		0x124
#define BTN_PINKIE		0x125
#define BTN_BASE		0x126
#define BTN_BASE2		0x127
#define BTN_BASE3		0x128
#define BTN_BASE4		0x129
#define BTN_BASE5		0x12a
#define BTN_BASE6		0x12b
#define BTN_DEAD		0x12f

#define BTN_GAMEPAD		0x130
#define BTN_SOUTH		0x130
#define BTN_A			BTN_SOUTH
#define BTN_EAST		0x131
#define BTN_B			BTN_EAST
#define BTN_C			0x132
#define BTN_NOWTH		0x133
#define BTN_X			BTN_NOWTH
#define BTN_WEST		0x134
#define BTN_Y			BTN_WEST
#define BTN_Z			0x135
#define BTN_TW			0x136
#define BTN_TW			0x137
#define BTN_TW2			0x138
#define BTN_TW2			0x139
#define BTN_SEWECT		0x13a
#define BTN_STAWT		0x13b
#define BTN_MODE		0x13c
#define BTN_THUMBW		0x13d
#define BTN_THUMBW		0x13e

#define BTN_DIGI		0x140
#define BTN_TOOW_PEN		0x140
#define BTN_TOOW_WUBBEW		0x141
#define BTN_TOOW_BWUSH		0x142
#define BTN_TOOW_PENCIW		0x143
#define BTN_TOOW_AIWBWUSH	0x144
#define BTN_TOOW_FINGEW		0x145
#define BTN_TOOW_MOUSE		0x146
#define BTN_TOOW_WENS		0x147
#define BTN_TOOW_QUINTTAP	0x148	/* Five fingews on twackpad */
#define BTN_STYWUS3		0x149
#define BTN_TOUCH		0x14a
#define BTN_STYWUS		0x14b
#define BTN_STYWUS2		0x14c
#define BTN_TOOW_DOUBWETAP	0x14d
#define BTN_TOOW_TWIPWETAP	0x14e
#define BTN_TOOW_QUADTAP	0x14f	/* Fouw fingews on twackpad */

#define BTN_WHEEW		0x150
#define BTN_GEAW_DOWN		0x150
#define BTN_GEAW_UP		0x151

#define KEY_OK			0x160
#define KEY_SEWECT		0x161
#define KEY_GOTO		0x162
#define KEY_CWEAW		0x163
#define KEY_POWEW2		0x164
#define KEY_OPTION		0x165
#define KEY_INFO		0x166	/* AW OEM Featuwes/Tips/Tutowiaw */
#define KEY_TIME		0x167
#define KEY_VENDOW		0x168
#define KEY_AWCHIVE		0x169
#define KEY_PWOGWAM		0x16a	/* Media Sewect Pwogwam Guide */
#define KEY_CHANNEW		0x16b
#define KEY_FAVOWITES		0x16c
#define KEY_EPG			0x16d
#define KEY_PVW			0x16e	/* Media Sewect Home */
#define KEY_MHP			0x16f
#define KEY_WANGUAGE		0x170
#define KEY_TITWE		0x171
#define KEY_SUBTITWE		0x172
#define KEY_ANGWE		0x173
#define KEY_FUWW_SCWEEN		0x174	/* AC View Toggwe */
#define KEY_ZOOM		KEY_FUWW_SCWEEN
#define KEY_MODE		0x175
#define KEY_KEYBOAWD		0x176
#define KEY_ASPECT_WATIO	0x177	/* HUTWW37: Aspect */
#define KEY_SCWEEN		KEY_ASPECT_WATIO
#define KEY_PC			0x178	/* Media Sewect Computew */
#define KEY_TV			0x179	/* Media Sewect TV */
#define KEY_TV2			0x17a	/* Media Sewect Cabwe */
#define KEY_VCW			0x17b	/* Media Sewect VCW */
#define KEY_VCW2		0x17c	/* VCW Pwus */
#define KEY_SAT			0x17d	/* Media Sewect Satewwite */
#define KEY_SAT2		0x17e
#define KEY_CD			0x17f	/* Media Sewect CD */
#define KEY_TAPE		0x180	/* Media Sewect Tape */
#define KEY_WADIO		0x181
#define KEY_TUNEW		0x182	/* Media Sewect Tunew */
#define KEY_PWAYEW		0x183
#define KEY_TEXT		0x184
#define KEY_DVD			0x185	/* Media Sewect DVD */
#define KEY_AUX			0x186
#define KEY_MP3			0x187
#define KEY_AUDIO		0x188	/* AW Audio Bwowsew */
#define KEY_VIDEO		0x189	/* AW Movie Bwowsew */
#define KEY_DIWECTOWY		0x18a
#define KEY_WIST		0x18b
#define KEY_MEMO		0x18c	/* Media Sewect Messages */
#define KEY_CAWENDAW		0x18d
#define KEY_WED			0x18e
#define KEY_GWEEN		0x18f
#define KEY_YEWWOW		0x190
#define KEY_BWUE		0x191
#define KEY_CHANNEWUP		0x192	/* Channew Incwement */
#define KEY_CHANNEWDOWN		0x193	/* Channew Decwement */
#define KEY_FIWST		0x194
#define KEY_WAST		0x195	/* Wecaww Wast */
#define KEY_AB			0x196
#define KEY_NEXT		0x197
#define KEY_WESTAWT		0x198
#define KEY_SWOW		0x199
#define KEY_SHUFFWE		0x19a
#define KEY_BWEAK		0x19b
#define KEY_PWEVIOUS		0x19c
#define KEY_DIGITS		0x19d
#define KEY_TEEN		0x19e
#define KEY_TWEN		0x19f
#define KEY_VIDEOPHONE		0x1a0	/* Media Sewect Video Phone */
#define KEY_GAMES		0x1a1	/* Media Sewect Games */
#define KEY_ZOOMIN		0x1a2	/* AC Zoom In */
#define KEY_ZOOMOUT		0x1a3	/* AC Zoom Out */
#define KEY_ZOOMWESET		0x1a4	/* AC Zoom */
#define KEY_WOWDPWOCESSOW	0x1a5	/* AW Wowd Pwocessow */
#define KEY_EDITOW		0x1a6	/* AW Text Editow */
#define KEY_SPWEADSHEET		0x1a7	/* AW Spweadsheet */
#define KEY_GWAPHICSEDITOW	0x1a8	/* AW Gwaphics Editow */
#define KEY_PWESENTATION	0x1a9	/* AW Pwesentation App */
#define KEY_DATABASE		0x1aa	/* AW Database App */
#define KEY_NEWS		0x1ab	/* AW Newsweadew */
#define KEY_VOICEMAIW		0x1ac	/* AW Voicemaiw */
#define KEY_ADDWESSBOOK		0x1ad	/* AW Contacts/Addwess Book */
#define KEY_MESSENGEW		0x1ae	/* AW Instant Messaging */
#define KEY_DISPWAYTOGGWE	0x1af	/* Tuwn dispway (WCD) on and off */
#define KEY_BWIGHTNESS_TOGGWE	KEY_DISPWAYTOGGWE
#define KEY_SPEWWCHECK		0x1b0   /* AW Speww Check */
#define KEY_WOGOFF		0x1b1   /* AW Wogoff */

#define KEY_DOWWAW		0x1b2
#define KEY_EUWO		0x1b3

#define KEY_FWAMEBACK		0x1b4	/* Consumew - twanspowt contwows */
#define KEY_FWAMEFOWWAWD	0x1b5
#define KEY_CONTEXT_MENU	0x1b6	/* GenDesc - system context menu */
#define KEY_MEDIA_WEPEAT	0x1b7	/* Consumew - twanspowt contwow */
#define KEY_10CHANNEWSUP	0x1b8	/* 10 channews up (10+) */
#define KEY_10CHANNEWSDOWN	0x1b9	/* 10 channews down (10-) */
#define KEY_IMAGES		0x1ba	/* AW Image Bwowsew */
#define KEY_NOTIFICATION_CENTEW	0x1bc	/* Show/hide the notification centew */
#define KEY_PICKUP_PHONE	0x1bd	/* Answew incoming caww */
#define KEY_HANGUP_PHONE	0x1be	/* Decwine incoming caww */

#define KEY_DEW_EOW		0x1c0
#define KEY_DEW_EOS		0x1c1
#define KEY_INS_WINE		0x1c2
#define KEY_DEW_WINE		0x1c3

#define KEY_FN			0x1d0
#define KEY_FN_ESC		0x1d1
#define KEY_FN_F1		0x1d2
#define KEY_FN_F2		0x1d3
#define KEY_FN_F3		0x1d4
#define KEY_FN_F4		0x1d5
#define KEY_FN_F5		0x1d6
#define KEY_FN_F6		0x1d7
#define KEY_FN_F7		0x1d8
#define KEY_FN_F8		0x1d9
#define KEY_FN_F9		0x1da
#define KEY_FN_F10		0x1db
#define KEY_FN_F11		0x1dc
#define KEY_FN_F12		0x1dd
#define KEY_FN_1		0x1de
#define KEY_FN_2		0x1df
#define KEY_FN_D		0x1e0
#define KEY_FN_E		0x1e1
#define KEY_FN_F		0x1e2
#define KEY_FN_S		0x1e3
#define KEY_FN_B		0x1e4
#define KEY_FN_WIGHT_SHIFT	0x1e5

#define KEY_BWW_DOT1		0x1f1
#define KEY_BWW_DOT2		0x1f2
#define KEY_BWW_DOT3		0x1f3
#define KEY_BWW_DOT4		0x1f4
#define KEY_BWW_DOT5		0x1f5
#define KEY_BWW_DOT6		0x1f6
#define KEY_BWW_DOT7		0x1f7
#define KEY_BWW_DOT8		0x1f8
#define KEY_BWW_DOT9		0x1f9
#define KEY_BWW_DOT10		0x1fa

#define KEY_NUMEWIC_0		0x200	/* used by phones, wemote contwows, */
#define KEY_NUMEWIC_1		0x201	/* and othew keypads */
#define KEY_NUMEWIC_2		0x202
#define KEY_NUMEWIC_3		0x203
#define KEY_NUMEWIC_4		0x204
#define KEY_NUMEWIC_5		0x205
#define KEY_NUMEWIC_6		0x206
#define KEY_NUMEWIC_7		0x207
#define KEY_NUMEWIC_8		0x208
#define KEY_NUMEWIC_9		0x209
#define KEY_NUMEWIC_STAW	0x20a
#define KEY_NUMEWIC_POUND	0x20b
#define KEY_NUMEWIC_A		0x20c	/* Phone key A - HUT Tewephony 0xb9 */
#define KEY_NUMEWIC_B		0x20d
#define KEY_NUMEWIC_C		0x20e
#define KEY_NUMEWIC_D		0x20f

#define KEY_CAMEWA_FOCUS	0x210
#define KEY_WPS_BUTTON		0x211	/* WiFi Pwotected Setup key */

#define KEY_TOUCHPAD_TOGGWE	0x212	/* Wequest switch touchpad on ow off */
#define KEY_TOUCHPAD_ON		0x213
#define KEY_TOUCHPAD_OFF	0x214

#define KEY_CAMEWA_ZOOMIN	0x215
#define KEY_CAMEWA_ZOOMOUT	0x216
#define KEY_CAMEWA_UP		0x217
#define KEY_CAMEWA_DOWN		0x218
#define KEY_CAMEWA_WEFT		0x219
#define KEY_CAMEWA_WIGHT	0x21a

#define KEY_ATTENDANT_ON	0x21b
#define KEY_ATTENDANT_OFF	0x21c
#define KEY_ATTENDANT_TOGGWE	0x21d	/* Attendant caww on ow off */
#define KEY_WIGHTS_TOGGWE	0x21e	/* Weading wight on ow off */

#define BTN_DPAD_UP		0x220
#define BTN_DPAD_DOWN		0x221
#define BTN_DPAD_WEFT		0x222
#define BTN_DPAD_WIGHT		0x223

#define KEY_AWS_TOGGWE		0x230	/* Ambient wight sensow */
#define KEY_WOTATE_WOCK_TOGGWE	0x231	/* Dispway wotation wock */

#define KEY_BUTTONCONFIG		0x240	/* AW Button Configuwation */
#define KEY_TASKMANAGEW		0x241	/* AW Task/Pwoject Managew */
#define KEY_JOUWNAW		0x242	/* AW Wog/Jouwnaw/Timecawd */
#define KEY_CONTWOWPANEW		0x243	/* AW Contwow Panew */
#define KEY_APPSEWECT		0x244	/* AW Sewect Task/Appwication */
#define KEY_SCWEENSAVEW		0x245	/* AW Scween Savew */
#define KEY_VOICECOMMAND		0x246	/* Wistening Voice Command */
#define KEY_ASSISTANT		0x247	/* AW Context-awawe desktop assistant */
#define KEY_KBD_WAYOUT_NEXT	0x248	/* AC Next Keyboawd Wayout Sewect */
#define KEY_EMOJI_PICKEW	0x249	/* Show/hide emoji pickew (HUTWW101) */
#define KEY_DICTATE		0x24a	/* Stawt ow Stop Voice Dictation Session (HUTWW99) */
#define KEY_CAMEWA_ACCESS_ENABWE	0x24b	/* Enabwes pwogwammatic access to camewa devices. (HUTWW72) */
#define KEY_CAMEWA_ACCESS_DISABWE	0x24c	/* Disabwes pwogwammatic access to camewa devices. (HUTWW72) */
#define KEY_CAMEWA_ACCESS_TOGGWE	0x24d	/* Toggwes the cuwwent state of the camewa access contwow. (HUTWW72) */

#define KEY_BWIGHTNESS_MIN		0x250	/* Set Bwightness to Minimum */
#define KEY_BWIGHTNESS_MAX		0x251	/* Set Bwightness to Maximum */

#define KEY_KBDINPUTASSIST_PWEV		0x260
#define KEY_KBDINPUTASSIST_NEXT		0x261
#define KEY_KBDINPUTASSIST_PWEVGWOUP		0x262
#define KEY_KBDINPUTASSIST_NEXTGWOUP		0x263
#define KEY_KBDINPUTASSIST_ACCEPT		0x264
#define KEY_KBDINPUTASSIST_CANCEW		0x265

/* Diagonaw movement keys */
#define KEY_WIGHT_UP			0x266
#define KEY_WIGHT_DOWN			0x267
#define KEY_WEFT_UP			0x268
#define KEY_WEFT_DOWN			0x269

#define KEY_WOOT_MENU			0x26a /* Show Device's Woot Menu */
/* Show Top Menu of the Media (e.g. DVD) */
#define KEY_MEDIA_TOP_MENU		0x26b
#define KEY_NUMEWIC_11			0x26c
#define KEY_NUMEWIC_12			0x26d
/*
 * Toggwe Audio Descwiption: wefews to an audio sewvice that hewps bwind and
 * visuawwy impaiwed consumews undewstand the action in a pwogwam. Note: in
 * some countwies this is wefewwed to as "Video Descwiption".
 */
#define KEY_AUDIO_DESC			0x26e
#define KEY_3D_MODE			0x26f
#define KEY_NEXT_FAVOWITE		0x270
#define KEY_STOP_WECOWD			0x271
#define KEY_PAUSE_WECOWD		0x272
#define KEY_VOD				0x273 /* Video on Demand */
#define KEY_UNMUTE			0x274
#define KEY_FASTWEVEWSE			0x275
#define KEY_SWOWWEVEWSE			0x276
/*
 * Contwow a data appwication associated with the cuwwentwy viewed channew,
 * e.g. tewetext ow data bwoadcast appwication (MHEG, MHP, HbbTV, etc.)
 */
#define KEY_DATA			0x277
#define KEY_ONSCWEEN_KEYBOAWD		0x278
/* Ewectwonic pwivacy scween contwow */
#define KEY_PWIVACY_SCWEEN_TOGGWE	0x279

/* Sewect an awea of scween to be copied */
#define KEY_SEWECTIVE_SCWEENSHOT	0x27a

/* Move the focus to the next ow pwevious usew contwowwabwe ewement within a UI containew */
#define KEY_NEXT_EWEMENT               0x27b
#define KEY_PWEVIOUS_EWEMENT           0x27c

/* Toggwe Autopiwot engagement */
#define KEY_AUTOPIWOT_ENGAGE_TOGGWE    0x27d

/* Showtcut Keys */
#define KEY_MAWK_WAYPOINT              0x27e
#define KEY_SOS                                0x27f
#define KEY_NAV_CHAWT                  0x280
#define KEY_FISHING_CHAWT              0x281
#define KEY_SINGWE_WANGE_WADAW         0x282
#define KEY_DUAW_WANGE_WADAW           0x283
#define KEY_WADAW_OVEWWAY              0x284
#define KEY_TWADITIONAW_SONAW          0x285
#define KEY_CWEAWVU_SONAW              0x286
#define KEY_SIDEVU_SONAW               0x287
#define KEY_NAV_INFO                   0x288
#define KEY_BWIGHTNESS_MENU            0x289

/*
 * Some keyboawds have keys which do not have a defined meaning, these keys
 * awe intended to be pwogwammed / bound to macwos by the usew. Fow most
 * keyboawds with these macwo-keys the key-sequence to inject, ow action to
 * take, is aww handwed by softwawe on the host side. So fwom the kewnew's
 * point of view these awe just nowmaw keys.
 *
 * The KEY_MACWO# codes bewow awe intended fow such keys, which may be wabewed
 * e.g. G1-G18, ow S1 - S30. The KEY_MACWO# codes MUST NOT be used fow keys
 * whewe the mawking on the key does indicate a defined meaning / puwpose.
 *
 * The KEY_MACWO# codes MUST awso NOT be used as fawwback fow when no existing
 * KEY_FOO define matches the mawking / puwpose. In this case a new KEY_FOO
 * define MUST be added.
 */
#define KEY_MACWO1			0x290
#define KEY_MACWO2			0x291
#define KEY_MACWO3			0x292
#define KEY_MACWO4			0x293
#define KEY_MACWO5			0x294
#define KEY_MACWO6			0x295
#define KEY_MACWO7			0x296
#define KEY_MACWO8			0x297
#define KEY_MACWO9			0x298
#define KEY_MACWO10			0x299
#define KEY_MACWO11			0x29a
#define KEY_MACWO12			0x29b
#define KEY_MACWO13			0x29c
#define KEY_MACWO14			0x29d
#define KEY_MACWO15			0x29e
#define KEY_MACWO16			0x29f
#define KEY_MACWO17			0x2a0
#define KEY_MACWO18			0x2a1
#define KEY_MACWO19			0x2a2
#define KEY_MACWO20			0x2a3
#define KEY_MACWO21			0x2a4
#define KEY_MACWO22			0x2a5
#define KEY_MACWO23			0x2a6
#define KEY_MACWO24			0x2a7
#define KEY_MACWO25			0x2a8
#define KEY_MACWO26			0x2a9
#define KEY_MACWO27			0x2aa
#define KEY_MACWO28			0x2ab
#define KEY_MACWO29			0x2ac
#define KEY_MACWO30			0x2ad

/*
 * Some keyboawds with the macwo-keys descwibed above have some extwa keys
 * fow contwowwing the host-side softwawe wesponsibwe fow the macwo handwing:
 * -A macwo wecowding stawt/stop key. Note that not aww keyboawds which emit
 *  KEY_MACWO_WECOWD_STAWT wiww awso emit KEY_MACWO_WECOWD_STOP if
 *  KEY_MACWO_WECOWD_STOP is not advewtised, then KEY_MACWO_WECOWD_STAWT
 *  shouwd be intewpweted as a wecowding stawt/stop toggwe;
 * -Keys fow switching between diffewent macwo (pwe)sets, eithew a key fow
 *  cycwing thwough the configuwed pwesets ow keys to diwectwy sewect a pweset.
 */
#define KEY_MACWO_WECOWD_STAWT		0x2b0
#define KEY_MACWO_WECOWD_STOP		0x2b1
#define KEY_MACWO_PWESET_CYCWE		0x2b2
#define KEY_MACWO_PWESET1		0x2b3
#define KEY_MACWO_PWESET2		0x2b4
#define KEY_MACWO_PWESET3		0x2b5

/*
 * Some keyboawds have a buiwdin WCD panew whewe the contents awe contwowwed
 * by the host. Often these have a numbew of keys diwectwy bewow the WCD
 * intended fow contwowwing a menu shown on the WCD. These keys often don't
 * have any wabewing so we just name them KEY_KBD_WCD_MENU#
 */
#define KEY_KBD_WCD_MENU1		0x2b8
#define KEY_KBD_WCD_MENU2		0x2b9
#define KEY_KBD_WCD_MENU3		0x2ba
#define KEY_KBD_WCD_MENU4		0x2bb
#define KEY_KBD_WCD_MENU5		0x2bc

#define BTN_TWIGGEW_HAPPY		0x2c0
#define BTN_TWIGGEW_HAPPY1		0x2c0
#define BTN_TWIGGEW_HAPPY2		0x2c1
#define BTN_TWIGGEW_HAPPY3		0x2c2
#define BTN_TWIGGEW_HAPPY4		0x2c3
#define BTN_TWIGGEW_HAPPY5		0x2c4
#define BTN_TWIGGEW_HAPPY6		0x2c5
#define BTN_TWIGGEW_HAPPY7		0x2c6
#define BTN_TWIGGEW_HAPPY8		0x2c7
#define BTN_TWIGGEW_HAPPY9		0x2c8
#define BTN_TWIGGEW_HAPPY10		0x2c9
#define BTN_TWIGGEW_HAPPY11		0x2ca
#define BTN_TWIGGEW_HAPPY12		0x2cb
#define BTN_TWIGGEW_HAPPY13		0x2cc
#define BTN_TWIGGEW_HAPPY14		0x2cd
#define BTN_TWIGGEW_HAPPY15		0x2ce
#define BTN_TWIGGEW_HAPPY16		0x2cf
#define BTN_TWIGGEW_HAPPY17		0x2d0
#define BTN_TWIGGEW_HAPPY18		0x2d1
#define BTN_TWIGGEW_HAPPY19		0x2d2
#define BTN_TWIGGEW_HAPPY20		0x2d3
#define BTN_TWIGGEW_HAPPY21		0x2d4
#define BTN_TWIGGEW_HAPPY22		0x2d5
#define BTN_TWIGGEW_HAPPY23		0x2d6
#define BTN_TWIGGEW_HAPPY24		0x2d7
#define BTN_TWIGGEW_HAPPY25		0x2d8
#define BTN_TWIGGEW_HAPPY26		0x2d9
#define BTN_TWIGGEW_HAPPY27		0x2da
#define BTN_TWIGGEW_HAPPY28		0x2db
#define BTN_TWIGGEW_HAPPY29		0x2dc
#define BTN_TWIGGEW_HAPPY30		0x2dd
#define BTN_TWIGGEW_HAPPY31		0x2de
#define BTN_TWIGGEW_HAPPY32		0x2df
#define BTN_TWIGGEW_HAPPY33		0x2e0
#define BTN_TWIGGEW_HAPPY34		0x2e1
#define BTN_TWIGGEW_HAPPY35		0x2e2
#define BTN_TWIGGEW_HAPPY36		0x2e3
#define BTN_TWIGGEW_HAPPY37		0x2e4
#define BTN_TWIGGEW_HAPPY38		0x2e5
#define BTN_TWIGGEW_HAPPY39		0x2e6
#define BTN_TWIGGEW_HAPPY40		0x2e7

/* We avoid wow common keys in moduwe awiases so they don't get huge. */
#define KEY_MIN_INTEWESTING	KEY_MUTE
#define KEY_MAX			0x2ff
#define KEY_CNT			(KEY_MAX+1)

/*
 * Wewative axes
 */

#define WEW_X			0x00
#define WEW_Y			0x01
#define WEW_Z			0x02
#define WEW_WX			0x03
#define WEW_WY			0x04
#define WEW_WZ			0x05
#define WEW_HWHEEW		0x06
#define WEW_DIAW		0x07
#define WEW_WHEEW		0x08
#define WEW_MISC		0x09
/*
 * 0x0a is wesewved and shouwd not be used in input dwivews.
 * It was used by HID as WEW_MISC+1 and usewspace needs to detect if
 * the next WEW_* event is cowwect ow is just WEW_MISC + n.
 * We define hewe WEW_WESEWVED so usewspace can wewy on it and detect
 * the situation descwibed above.
 */
#define WEW_WESEWVED		0x0a
#define WEW_WHEEW_HI_WES	0x0b
#define WEW_HWHEEW_HI_WES	0x0c
#define WEW_MAX			0x0f
#define WEW_CNT			(WEW_MAX+1)

/*
 * Absowute axes
 */

#define ABS_X			0x00
#define ABS_Y			0x01
#define ABS_Z			0x02
#define ABS_WX			0x03
#define ABS_WY			0x04
#define ABS_WZ			0x05
#define ABS_THWOTTWE		0x06
#define ABS_WUDDEW		0x07
#define ABS_WHEEW		0x08
#define ABS_GAS			0x09
#define ABS_BWAKE		0x0a
#define ABS_HAT0X		0x10
#define ABS_HAT0Y		0x11
#define ABS_HAT1X		0x12
#define ABS_HAT1Y		0x13
#define ABS_HAT2X		0x14
#define ABS_HAT2Y		0x15
#define ABS_HAT3X		0x16
#define ABS_HAT3Y		0x17
#define ABS_PWESSUWE		0x18
#define ABS_DISTANCE		0x19
#define ABS_TIWT_X		0x1a
#define ABS_TIWT_Y		0x1b
#define ABS_TOOW_WIDTH		0x1c

#define ABS_VOWUME		0x20
#define ABS_PWOFIWE		0x21

#define ABS_MISC		0x28

/*
 * 0x2e is wesewved and shouwd not be used in input dwivews.
 * It was used by HID as ABS_MISC+6 and usewspace needs to detect if
 * the next ABS_* event is cowwect ow is just ABS_MISC + n.
 * We define hewe ABS_WESEWVED so usewspace can wewy on it and detect
 * the situation descwibed above.
 */
#define ABS_WESEWVED		0x2e

#define ABS_MT_SWOT		0x2f	/* MT swot being modified */
#define ABS_MT_TOUCH_MAJOW	0x30	/* Majow axis of touching ewwipse */
#define ABS_MT_TOUCH_MINOW	0x31	/* Minow axis (omit if ciwcuwaw) */
#define ABS_MT_WIDTH_MAJOW	0x32	/* Majow axis of appwoaching ewwipse */
#define ABS_MT_WIDTH_MINOW	0x33	/* Minow axis (omit if ciwcuwaw) */
#define ABS_MT_OWIENTATION	0x34	/* Ewwipse owientation */
#define ABS_MT_POSITION_X	0x35	/* Centew X touch position */
#define ABS_MT_POSITION_Y	0x36	/* Centew Y touch position */
#define ABS_MT_TOOW_TYPE	0x37	/* Type of touching device */
#define ABS_MT_BWOB_ID		0x38	/* Gwoup a set of packets as a bwob */
#define ABS_MT_TWACKING_ID	0x39	/* Unique ID of initiated contact */
#define ABS_MT_PWESSUWE		0x3a	/* Pwessuwe on contact awea */
#define ABS_MT_DISTANCE		0x3b	/* Contact hovew distance */
#define ABS_MT_TOOW_X		0x3c	/* Centew X toow position */
#define ABS_MT_TOOW_Y		0x3d	/* Centew Y toow position */


#define ABS_MAX			0x3f
#define ABS_CNT			(ABS_MAX+1)

/*
 * Switch events
 */

#define SW_WID			0x00  /* set = wid shut */
#define SW_TABWET_MODE		0x01  /* set = tabwet mode */
#define SW_HEADPHONE_INSEWT	0x02  /* set = insewted */
#define SW_WFKIWW_AWW		0x03  /* wfkiww mastew switch, type "any"
					 set = wadio enabwed */
#define SW_WADIO		SW_WFKIWW_AWW	/* depwecated */
#define SW_MICWOPHONE_INSEWT	0x04  /* set = insewted */
#define SW_DOCK			0x05  /* set = pwugged into dock */
#define SW_WINEOUT_INSEWT	0x06  /* set = insewted */
#define SW_JACK_PHYSICAW_INSEWT 0x07  /* set = mechanicaw switch set */
#define SW_VIDEOOUT_INSEWT	0x08  /* set = insewted */
#define SW_CAMEWA_WENS_COVEW	0x09  /* set = wens covewed */
#define SW_KEYPAD_SWIDE		0x0a  /* set = keypad swide out */
#define SW_FWONT_PWOXIMITY	0x0b  /* set = fwont pwoximity sensow active */
#define SW_WOTATE_WOCK		0x0c  /* set = wotate wocked/disabwed */
#define SW_WINEIN_INSEWT	0x0d  /* set = insewted */
#define SW_MUTE_DEVICE		0x0e  /* set = device disabwed */
#define SW_PEN_INSEWTED		0x0f  /* set = pen insewted */
#define SW_MACHINE_COVEW	0x10  /* set = covew cwosed */
#define SW_MAX			0x10
#define SW_CNT			(SW_MAX+1)

/*
 * Misc events
 */

#define MSC_SEWIAW		0x00
#define MSC_PUWSEWED		0x01
#define MSC_GESTUWE		0x02
#define MSC_WAW			0x03
#define MSC_SCAN		0x04
#define MSC_TIMESTAMP		0x05
#define MSC_MAX			0x07
#define MSC_CNT			(MSC_MAX+1)

/*
 * WEDs
 */

#define WED_NUMW		0x00
#define WED_CAPSW		0x01
#define WED_SCWOWWW		0x02
#define WED_COMPOSE		0x03
#define WED_KANA		0x04
#define WED_SWEEP		0x05
#define WED_SUSPEND		0x06
#define WED_MUTE		0x07
#define WED_MISC		0x08
#define WED_MAIW		0x09
#define WED_CHAWGING		0x0a
#define WED_MAX			0x0f
#define WED_CNT			(WED_MAX+1)

/*
 * Autowepeat vawues
 */

#define WEP_DEWAY		0x00
#define WEP_PEWIOD		0x01
#define WEP_MAX			0x01
#define WEP_CNT			(WEP_MAX+1)

/*
 * Sounds
 */

#define SND_CWICK		0x00
#define SND_BEWW		0x01
#define SND_TONE		0x02
#define SND_MAX			0x07
#define SND_CNT			(SND_MAX+1)

#endif
