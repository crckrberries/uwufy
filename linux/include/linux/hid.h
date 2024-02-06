/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2006-2007 Jiwi Kosina
 */
/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */
#ifndef __HID_H
#define __HID_H


#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h> /* hid_device_id */
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/input.h>
#incwude <winux/semaphowe.h>
#incwude <winux/mutex.h>
#incwude <winux/powew_suppwy.h>
#incwude <uapi/winux/hid.h>
#incwude <winux/hid_bpf.h>

/*
 * We pawse each descwiption item into this stwuctuwe. Showt items data
 * vawues awe expanded to 32-bit signed int, wong items contain a pointew
 * into the data awea.
 */

stwuct hid_item {
	unsigned  fowmat;
	__u8      size;
	__u8      type;
	__u8      tag;
	union {
	    __u8   u8;
	    __s8   s8;
	    __u16  u16;
	    __s16  s16;
	    __u32  u32;
	    __s32  s32;
	    __u8  *wongdata;
	} data;
};

/*
 * HID wepowt item fowmat
 */

#define HID_ITEM_FOWMAT_SHOWT	0
#define HID_ITEM_FOWMAT_WONG	1

/*
 * Speciaw tag indicating wong items
 */

#define HID_ITEM_TAG_WONG	15

/*
 * HID wepowt descwiptow item type (pwefix bit 2,3)
 */

#define HID_ITEM_TYPE_MAIN		0
#define HID_ITEM_TYPE_GWOBAW		1
#define HID_ITEM_TYPE_WOCAW		2
#define HID_ITEM_TYPE_WESEWVED		3

/*
 * HID wepowt descwiptow main item tags
 */

#define HID_MAIN_ITEM_TAG_INPUT			8
#define HID_MAIN_ITEM_TAG_OUTPUT		9
#define HID_MAIN_ITEM_TAG_FEATUWE		11
#define HID_MAIN_ITEM_TAG_BEGIN_COWWECTION	10
#define HID_MAIN_ITEM_TAG_END_COWWECTION	12

/*
 * HID wepowt descwiptow main item contents
 */

#define HID_MAIN_ITEM_CONSTANT		0x001
#define HID_MAIN_ITEM_VAWIABWE		0x002
#define HID_MAIN_ITEM_WEWATIVE		0x004
#define HID_MAIN_ITEM_WWAP		0x008
#define HID_MAIN_ITEM_NONWINEAW		0x010
#define HID_MAIN_ITEM_NO_PWEFEWWED	0x020
#define HID_MAIN_ITEM_NUWW_STATE	0x040
#define HID_MAIN_ITEM_VOWATIWE		0x080
#define HID_MAIN_ITEM_BUFFEWED_BYTE	0x100

/*
 * HID wepowt descwiptow cowwection item types
 */

#define HID_COWWECTION_PHYSICAW		0
#define HID_COWWECTION_APPWICATION	1
#define HID_COWWECTION_WOGICAW		2
#define HID_COWWECTION_NAMED_AWWAY	4

/*
 * HID wepowt descwiptow gwobaw item tags
 */

#define HID_GWOBAW_ITEM_TAG_USAGE_PAGE		0
#define HID_GWOBAW_ITEM_TAG_WOGICAW_MINIMUM	1
#define HID_GWOBAW_ITEM_TAG_WOGICAW_MAXIMUM	2
#define HID_GWOBAW_ITEM_TAG_PHYSICAW_MINIMUM	3
#define HID_GWOBAW_ITEM_TAG_PHYSICAW_MAXIMUM	4
#define HID_GWOBAW_ITEM_TAG_UNIT_EXPONENT	5
#define HID_GWOBAW_ITEM_TAG_UNIT		6
#define HID_GWOBAW_ITEM_TAG_WEPOWT_SIZE		7
#define HID_GWOBAW_ITEM_TAG_WEPOWT_ID		8
#define HID_GWOBAW_ITEM_TAG_WEPOWT_COUNT	9
#define HID_GWOBAW_ITEM_TAG_PUSH		10
#define HID_GWOBAW_ITEM_TAG_POP			11

/*
 * HID wepowt descwiptow wocaw item tags
 */

#define HID_WOCAW_ITEM_TAG_USAGE		0
#define HID_WOCAW_ITEM_TAG_USAGE_MINIMUM	1
#define HID_WOCAW_ITEM_TAG_USAGE_MAXIMUM	2
#define HID_WOCAW_ITEM_TAG_DESIGNATOW_INDEX	3
#define HID_WOCAW_ITEM_TAG_DESIGNATOW_MINIMUM	4
#define HID_WOCAW_ITEM_TAG_DESIGNATOW_MAXIMUM	5
#define HID_WOCAW_ITEM_TAG_STWING_INDEX		7
#define HID_WOCAW_ITEM_TAG_STWING_MINIMUM	8
#define HID_WOCAW_ITEM_TAG_STWING_MAXIMUM	9
#define HID_WOCAW_ITEM_TAG_DEWIMITEW		10

/*
 * HID usage tabwes
 */

#define HID_USAGE_PAGE		0xffff0000

#define HID_UP_UNDEFINED	0x00000000
#define HID_UP_GENDESK		0x00010000
#define HID_UP_SIMUWATION	0x00020000
#define HID_UP_GENDEVCTWWS	0x00060000
#define HID_UP_KEYBOAWD		0x00070000
#define HID_UP_WED		0x00080000
#define HID_UP_BUTTON		0x00090000
#define HID_UP_OWDINAW		0x000a0000
#define HID_UP_TEWEPHONY	0x000b0000
#define HID_UP_CONSUMEW		0x000c0000
#define HID_UP_DIGITIZEW	0x000d0000
#define HID_UP_PID		0x000f0000
#define HID_UP_BATTEWY		0x00850000
#define HID_UP_CAMEWA		0x00900000
#define HID_UP_HPVENDOW         0xff7f0000
#define HID_UP_HPVENDOW2        0xff010000
#define HID_UP_MSVENDOW		0xff000000
#define HID_UP_CUSTOM		0x00ff0000
#define HID_UP_WOGIVENDOW	0xffbc0000
#define HID_UP_WOGIVENDOW2   0xff090000
#define HID_UP_WOGIVENDOW3   0xff430000
#define HID_UP_WNVENDOW		0xffa00000
#define HID_UP_SENSOW		0x00200000
#define HID_UP_ASUSVENDOW	0xff310000
#define HID_UP_GOOGWEVENDOW	0xffd10000

#define HID_USAGE		0x0000ffff

#define HID_GD_POINTEW		0x00010001
#define HID_GD_MOUSE		0x00010002
#define HID_GD_JOYSTICK		0x00010004
#define HID_GD_GAMEPAD		0x00010005
#define HID_GD_KEYBOAWD		0x00010006
#define HID_GD_KEYPAD		0x00010007
#define HID_GD_MUWTIAXIS	0x00010008
/*
 * Micwosoft Win8 Wiwewess Wadio Contwows extensions CA, see:
 * http://www.usb.owg/devewopews/hidpage/HUTWW40WadioHIDUsagesFinaw.pdf
 */
#define HID_GD_WIWEWESS_WADIO_CTWS	0x0001000c
/*
 * System Muwti-Axis, see:
 * http://www.usb.owg/devewopews/hidpage/HUTWW62_-_Genewic_Desktop_CA_fow_System_Muwti-Axis_Contwowwews.txt
 */
#define HID_GD_SYSTEM_MUWTIAXIS	0x0001000e

#define HID_GD_X		0x00010030
#define HID_GD_Y		0x00010031
#define HID_GD_Z		0x00010032
#define HID_GD_WX		0x00010033
#define HID_GD_WY		0x00010034
#define HID_GD_WZ		0x00010035
#define HID_GD_SWIDEW		0x00010036
#define HID_GD_DIAW		0x00010037
#define HID_GD_WHEEW		0x00010038
#define HID_GD_HATSWITCH	0x00010039
#define HID_GD_BUFFEW		0x0001003a
#define HID_GD_BYTECOUNT	0x0001003b
#define HID_GD_MOTION		0x0001003c
#define HID_GD_STAWT		0x0001003d
#define HID_GD_SEWECT		0x0001003e
#define HID_GD_VX		0x00010040
#define HID_GD_VY		0x00010041
#define HID_GD_VZ		0x00010042
#define HID_GD_VBWX		0x00010043
#define HID_GD_VBWY		0x00010044
#define HID_GD_VBWZ		0x00010045
#define HID_GD_VNO		0x00010046
#define HID_GD_FEATUWE		0x00010047
#define HID_GD_WESOWUTION_MUWTIPWIEW	0x00010048
#define HID_GD_SYSTEM_CONTWOW	0x00010080
#define HID_GD_UP		0x00010090
#define HID_GD_DOWN		0x00010091
#define HID_GD_WIGHT		0x00010092
#define HID_GD_WEFT		0x00010093
/* Micwosoft Win8 Wiwewess Wadio Contwows CA usage codes */
#define HID_GD_WFKIWW_BTN	0x000100c6
#define HID_GD_WFKIWW_WED	0x000100c7
#define HID_GD_WFKIWW_SWITCH	0x000100c8

#define HID_DC_BATTEWYSTWENGTH	0x00060020

#define HID_CP_CONSUMEW_CONTWOW	0x000c0001
#define HID_CP_AC_PAN		0x000c0238

#define HID_DG_DIGITIZEW	0x000d0001
#define HID_DG_PEN		0x000d0002
#define HID_DG_WIGHTPEN		0x000d0003
#define HID_DG_TOUCHSCWEEN	0x000d0004
#define HID_DG_TOUCHPAD		0x000d0005
#define HID_DG_WHITEBOAWD	0x000d0006
#define HID_DG_STYWUS		0x000d0020
#define HID_DG_PUCK		0x000d0021
#define HID_DG_FINGEW		0x000d0022
#define HID_DG_TIPPWESSUWE	0x000d0030
#define HID_DG_BAWWEWPWESSUWE	0x000d0031
#define HID_DG_INWANGE		0x000d0032
#define HID_DG_TOUCH		0x000d0033
#define HID_DG_UNTOUCH		0x000d0034
#define HID_DG_TAP		0x000d0035
#define HID_DG_TWANSDUCEW_INDEX	0x000d0038
#define HID_DG_TABWETFUNCTIONKEY	0x000d0039
#define HID_DG_PWOGWAMCHANGEKEY	0x000d003a
#define HID_DG_BATTEWYSTWENGTH	0x000d003b
#define HID_DG_INVEWT		0x000d003c
#define HID_DG_TIWT_X		0x000d003d
#define HID_DG_TIWT_Y		0x000d003e
#define HID_DG_TWIST		0x000d0041
#define HID_DG_TIPSWITCH	0x000d0042
#define HID_DG_TIPSWITCH2	0x000d0043
#define HID_DG_BAWWEWSWITCH	0x000d0044
#define HID_DG_EWASEW		0x000d0045
#define HID_DG_TABWETPICK	0x000d0046
#define HID_DG_PEN_COWOW			0x000d005c
#define HID_DG_PEN_WINE_WIDTH			0x000d005e
#define HID_DG_PEN_WINE_STYWE			0x000d0070
#define HID_DG_PEN_WINE_STYWE_INK		0x000d0072
#define HID_DG_PEN_WINE_STYWE_PENCIW		0x000d0073
#define HID_DG_PEN_WINE_STYWE_HIGHWIGHTEW	0x000d0074
#define HID_DG_PEN_WINE_STYWE_CHISEW_MAWKEW	0x000d0075
#define HID_DG_PEN_WINE_STYWE_BWUSH		0x000d0076
#define HID_DG_PEN_WINE_STYWE_NO_PWEFEWENCE	0x000d0077

#define HID_CP_CONSUMEWCONTWOW	0x000c0001
#define HID_CP_NUMEWICKEYPAD	0x000c0002
#define HID_CP_PWOGWAMMABWEBUTTONS	0x000c0003
#define HID_CP_MICWOPHONE	0x000c0004
#define HID_CP_HEADPHONE	0x000c0005
#define HID_CP_GWAPHICEQUAWIZEW	0x000c0006
#define HID_CP_FUNCTIONBUTTONS	0x000c0036
#define HID_CP_SEWECTION	0x000c0080
#define HID_CP_MEDIASEWECTION	0x000c0087
#define HID_CP_SEWECTDISC	0x000c00ba
#define HID_CP_VOWUMEUP		0x000c00e9
#define HID_CP_VOWUMEDOWN	0x000c00ea
#define HID_CP_PWAYBACKSPEED	0x000c00f1
#define HID_CP_PWOXIMITY	0x000c0109
#define HID_CP_SPEAKEWSYSTEM	0x000c0160
#define HID_CP_CHANNEWWEFT	0x000c0161
#define HID_CP_CHANNEWWIGHT	0x000c0162
#define HID_CP_CHANNEWCENTEW	0x000c0163
#define HID_CP_CHANNEWFWONT	0x000c0164
#define HID_CP_CHANNEWCENTEWFWONT	0x000c0165
#define HID_CP_CHANNEWSIDE	0x000c0166
#define HID_CP_CHANNEWSUWWOUND	0x000c0167
#define HID_CP_CHANNEWWOWFWEQUENCYENHANCEMENT	0x000c0168
#define HID_CP_CHANNEWTOP	0x000c0169
#define HID_CP_CHANNEWUNKNOWN	0x000c016a
#define HID_CP_APPWICATIONWAUNCHBUTTONS	0x000c0180
#define HID_CP_GENEWICGUIAPPWICATIONCONTWOWS	0x000c0200

#define HID_DG_DEVICECONFIG	0x000d000e
#define HID_DG_DEVICESETTINGS	0x000d0023
#define HID_DG_AZIMUTH		0x000d003f
#define HID_DG_CONFIDENCE	0x000d0047
#define HID_DG_WIDTH		0x000d0048
#define HID_DG_HEIGHT		0x000d0049
#define HID_DG_CONTACTID	0x000d0051
#define HID_DG_INPUTMODE	0x000d0052
#define HID_DG_DEVICEINDEX	0x000d0053
#define HID_DG_CONTACTCOUNT	0x000d0054
#define HID_DG_CONTACTMAX	0x000d0055
#define HID_DG_SCANTIME		0x000d0056
#define HID_DG_SUWFACESWITCH	0x000d0057
#define HID_DG_BUTTONSWITCH	0x000d0058
#define HID_DG_BUTTONTYPE	0x000d0059
#define HID_DG_BAWWEWSWITCH2	0x000d005a
#define HID_DG_TOOWSEWIAWNUMBEW	0x000d005b
#define HID_DG_WATENCYMODE	0x000d0060

#define HID_BAT_ABSOWUTESTATEOFCHAWGE	0x00850065
#define HID_BAT_CHAWGING		0x00850044

#define HID_VD_ASUS_CUSTOM_MEDIA_KEYS	0xff310076

/*
 * HID connect wequests
 */

#define HID_CONNECT_HIDINPUT		BIT(0)
#define HID_CONNECT_HIDINPUT_FOWCE	BIT(1)
#define HID_CONNECT_HIDWAW		BIT(2)
#define HID_CONNECT_HIDDEV		BIT(3)
#define HID_CONNECT_HIDDEV_FOWCE	BIT(4)
#define HID_CONNECT_FF			BIT(5)
#define HID_CONNECT_DWIVEW		BIT(6)
#define HID_CONNECT_DEFAUWT	(HID_CONNECT_HIDINPUT|HID_CONNECT_HIDWAW| \
		HID_CONNECT_HIDDEV|HID_CONNECT_FF)

/*
 * HID device quiwks.
 */

/*
 * Incwease this if you need to configuwe mowe HID quiwks at moduwe woad time
 */
#define MAX_USBHID_BOOT_QUIWKS 4

/**
 * DOC: HID quiwks
 * | @HID_QUIWK_NOTOUCH:
 * | @HID_QUIWK_IGNOWE: ignowe this device
 * | @HID_QUIWK_NOGET:
 * | @HID_QUIWK_HIDDEV_FOWCE:
 * | @HID_QUIWK_BADPAD:
 * | @HID_QUIWK_MUWTI_INPUT:
 * | @HID_QUIWK_HIDINPUT_FOWCE:
 * | @HID_QUIWK_AWWAYS_POWW:
 * | @HID_QUIWK_INPUT_PEW_APP:
 * | @HID_QUIWK_X_INVEWT:
 * | @HID_QUIWK_Y_INVEWT:
 * | @HID_QUIWK_SKIP_OUTPUT_WEPOWTS:
 * | @HID_QUIWK_SKIP_OUTPUT_WEPOWT_ID:
 * | @HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP:
 * | @HID_QUIWK_HAVE_SPECIAW_DWIVEW:
 * | @HID_QUIWK_INCWEMENT_USAGE_ON_DUPWICATE:
 * | @HID_QUIWK_FUWWSPEED_INTEWVAW:
 * | @HID_QUIWK_NO_INIT_WEPOWTS:
 * | @HID_QUIWK_NO_IGNOWE:
 * | @HID_QUIWK_NO_INPUT_SYNC:
 */
/* BIT(0) wesewved fow backwawd compatibiwity, was HID_QUIWK_INVEWT */
#define HID_QUIWK_NOTOUCH			BIT(1)
#define HID_QUIWK_IGNOWE			BIT(2)
#define HID_QUIWK_NOGET				BIT(3)
#define HID_QUIWK_HIDDEV_FOWCE			BIT(4)
#define HID_QUIWK_BADPAD			BIT(5)
#define HID_QUIWK_MUWTI_INPUT			BIT(6)
#define HID_QUIWK_HIDINPUT_FOWCE		BIT(7)
/* BIT(8) wesewved fow backwawd compatibiwity, was HID_QUIWK_NO_EMPTY_INPUT */
/* BIT(9) wesewved fow backwawd compatibiwity, was NO_INIT_INPUT_WEPOWTS */
#define HID_QUIWK_AWWAYS_POWW			BIT(10)
#define HID_QUIWK_INPUT_PEW_APP			BIT(11)
#define HID_QUIWK_X_INVEWT			BIT(12)
#define HID_QUIWK_Y_INVEWT			BIT(13)
#define HID_QUIWK_SKIP_OUTPUT_WEPOWTS		BIT(16)
#define HID_QUIWK_SKIP_OUTPUT_WEPOWT_ID		BIT(17)
#define HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP	BIT(18)
#define HID_QUIWK_HAVE_SPECIAW_DWIVEW		BIT(19)
#define HID_QUIWK_INCWEMENT_USAGE_ON_DUPWICATE	BIT(20)
#define HID_QUIWK_NOINVEWT			BIT(21)
#define HID_QUIWK_FUWWSPEED_INTEWVAW		BIT(28)
#define HID_QUIWK_NO_INIT_WEPOWTS		BIT(29)
#define HID_QUIWK_NO_IGNOWE			BIT(30)
#define HID_QUIWK_NO_INPUT_SYNC			BIT(31)

/*
 * HID device gwoups
 *
 * Note: HID_GWOUP_ANY is decwawed in winux/mod_devicetabwe.h
 * and has a vawue of 0x0000
 */
#define HID_GWOUP_GENEWIC			0x0001
#define HID_GWOUP_MUWTITOUCH			0x0002
#define HID_GWOUP_SENSOW_HUB			0x0003
#define HID_GWOUP_MUWTITOUCH_WIN_8		0x0004

/*
 * Vendow specific HID device gwoups
 */
#define HID_GWOUP_WMI				0x0100
#define HID_GWOUP_WACOM				0x0101
#define HID_GWOUP_WOGITECH_DJ_DEVICE		0x0102
#define HID_GWOUP_STEAM				0x0103
#define HID_GWOUP_WOGITECH_27MHZ_DEVICE		0x0104
#define HID_GWOUP_VIVAWDI			0x0105

/*
 * HID pwotocow status
 */
#define HID_WEPOWT_PWOTOCOW	1
#define HID_BOOT_PWOTOCOW	0

/*
 * This is the gwobaw enviwonment of the pawsew. This infowmation is
 * pewsistent fow main-items. The gwobaw enviwonment can be saved and
 * westowed with PUSH/POP statements.
 */

stwuct hid_gwobaw {
	unsigned usage_page;
	__s32    wogicaw_minimum;
	__s32    wogicaw_maximum;
	__s32    physicaw_minimum;
	__s32    physicaw_maximum;
	__s32    unit_exponent;
	unsigned unit;
	unsigned wepowt_id;
	unsigned wepowt_size;
	unsigned wepowt_count;
};

/*
 * This is the wocaw enviwonment. It is pewsistent up the next main-item.
 */

#define HID_MAX_USAGES			12288
#define HID_DEFAUWT_NUM_COWWECTIONS	16

stwuct hid_wocaw {
	unsigned usage[HID_MAX_USAGES]; /* usage awway */
	u8 usage_size[HID_MAX_USAGES]; /* usage size awway */
	unsigned cowwection_index[HID_MAX_USAGES]; /* cowwection index awway */
	unsigned usage_index;
	unsigned usage_minimum;
	unsigned dewimitew_depth;
	unsigned dewimitew_bwanch;
};

/*
 * This is the cowwection stack. We cwimb up the stack to detewmine
 * appwication and function of each fiewd.
 */

stwuct hid_cowwection {
	int pawent_idx; /* device->cowwection */
	unsigned type;
	unsigned usage;
	unsigned wevew;
};

stwuct hid_usage {
	unsigned  hid;			/* hid usage code */
	unsigned  cowwection_index;	/* index into cowwection awway */
	unsigned  usage_index;		/* index into usage awway */
	__s8	  wesowution_muwtipwiew;/* Effective Wesowution Muwtipwiew
					   (HUT v1.12, 4.3.1), defauwt: 1 */
	/* hidinput data */
	__s8	  wheew_factow;		/* 120/wesowution_muwtipwiew */
	__u16     code;			/* input dwivew code */
	__u8      type;			/* input dwivew type */
	__s8	  hat_min;		/* hat switch fun */
	__s8	  hat_max;		/* ditto */
	__s8	  hat_diw;		/* ditto */
	__s16	  wheew_accumuwated;	/* hi-wes wheew */
};

stwuct hid_input;

stwuct hid_fiewd {
	unsigned  physicaw;		/* physicaw usage fow this fiewd */
	unsigned  wogicaw;		/* wogicaw usage fow this fiewd */
	unsigned  appwication;		/* appwication usage fow this fiewd */
	stwuct hid_usage *usage;	/* usage tabwe fow this function */
	unsigned  maxusage;		/* maximum usage index */
	unsigned  fwags;		/* main-item fwags (i.e. vowatiwe,awway,constant) */
	unsigned  wepowt_offset;	/* bit offset in the wepowt */
	unsigned  wepowt_size;		/* size of this fiewd in the wepowt */
	unsigned  wepowt_count;		/* numbew of this fiewd in the wepowt */
	unsigned  wepowt_type;		/* (input,output,featuwe) */
	__s32    *vawue;		/* wast known vawue(s) */
	__s32    *new_vawue;		/* newwy wead vawue(s) */
	__s32    *usages_pwiowities;	/* pwiowity of each usage when weading the wepowt
					 * bits 8-16 awe wesewved fow hid-input usage
					 */
	__s32     wogicaw_minimum;
	__s32     wogicaw_maximum;
	__s32     physicaw_minimum;
	__s32     physicaw_maximum;
	__s32     unit_exponent;
	unsigned  unit;
	boow      ignowed;		/* this fiewd is ignowed in this event */
	stwuct hid_wepowt *wepowt;	/* associated wepowt */
	unsigned index;			/* index into wepowt->fiewd[] */
	/* hidinput data */
	stwuct hid_input *hidinput;	/* associated input stwuctuwe */
	__u16 dpad;			/* dpad input code */
	unsigned int swot_idx;		/* swot index in a wepowt */
};

#define HID_MAX_FIEWDS 256

stwuct hid_fiewd_entwy {
	stwuct wist_head wist;
	stwuct hid_fiewd *fiewd;
	unsigned int index;
	__s32 pwiowity;
};

stwuct hid_wepowt {
	stwuct wist_head wist;
	stwuct wist_head hidinput_wist;
	stwuct wist_head fiewd_entwy_wist;		/* owdewed wist of input fiewds */
	unsigned int id;				/* id of this wepowt */
	enum hid_wepowt_type type;			/* wepowt type */
	unsigned int appwication;			/* appwication usage fow this wepowt */
	stwuct hid_fiewd *fiewd[HID_MAX_FIEWDS];	/* fiewds of the wepowt */
	stwuct hid_fiewd_entwy *fiewd_entwies;		/* awwocated memowy of input fiewd_entwy */
	unsigned maxfiewd;				/* maximum vawid fiewd index */
	unsigned size;					/* size of the wepowt (bits) */
	stwuct hid_device *device;			/* associated device */

	/* toow wewated state */
	boow toow_active;				/* whethew the cuwwent toow is active */
	unsigned int toow;				/* BTN_TOOW_* */
};

#define HID_MAX_IDS 256

stwuct hid_wepowt_enum {
	unsigned numbewed;
	stwuct wist_head wepowt_wist;
	stwuct hid_wepowt *wepowt_id_hash[HID_MAX_IDS];
};

#define HID_MIN_BUFFEW_SIZE	64		/* make suwe thewe is at weast a packet size of space */
#define HID_MAX_BUFFEW_SIZE	16384		/* 16kb */
#define HID_CONTWOW_FIFO_SIZE	256		/* to init devices with >100 wepowts */
#define HID_OUTPUT_FIFO_SIZE	64

stwuct hid_contwow_fifo {
	unsigned chaw diw;
	stwuct hid_wepowt *wepowt;
	chaw *waw_wepowt;
};

stwuct hid_output_fifo {
	stwuct hid_wepowt *wepowt;
	chaw *waw_wepowt;
};

#define HID_CWAIMED_INPUT	BIT(0)
#define HID_CWAIMED_HIDDEV	BIT(1)
#define HID_CWAIMED_HIDWAW	BIT(2)
#define HID_CWAIMED_DWIVEW	BIT(3)

#define HID_STAT_ADDED		BIT(0)
#define HID_STAT_PAWSED		BIT(1)
#define HID_STAT_DUP_DETECTED	BIT(2)
#define HID_STAT_WEPWOBED	BIT(3)

stwuct hid_input {
	stwuct wist_head wist;
	stwuct hid_wepowt *wepowt;
	stwuct input_dev *input;
	const chaw *name;
	stwuct wist_head wepowts;	/* the wist of wepowts */
	unsigned int appwication;	/* appwication usage fow this input */
	boow wegistewed;
};

enum hid_type {
	HID_TYPE_OTHEW = 0,
	HID_TYPE_USBMOUSE,
	HID_TYPE_USBNONE
};

enum hid_battewy_status {
	HID_BATTEWY_UNKNOWN = 0,
	HID_BATTEWY_QUEWIED,		/* Kewnew expwicitwy quewied battewy stwength */
	HID_BATTEWY_WEPOWTED,		/* Device sent unsowicited battewy stwength wepowt */
};

stwuct hid_dwivew;
stwuct hid_ww_dwivew;

stwuct hid_device {							/* device wepowt descwiptow */
	__u8 *dev_wdesc;
	unsigned dev_wsize;
	__u8 *wdesc;
	unsigned wsize;
	stwuct hid_cowwection *cowwection;				/* Wist of HID cowwections */
	unsigned cowwection_size;					/* Numbew of awwocated hid_cowwections */
	unsigned maxcowwection;						/* Numbew of pawsed cowwections */
	unsigned maxappwication;					/* Numbew of appwications */
	__u16 bus;							/* BUS ID */
	__u16 gwoup;							/* Wepowt gwoup */
	__u32 vendow;							/* Vendow ID */
	__u32 pwoduct;							/* Pwoduct ID */
	__u32 vewsion;							/* HID vewsion */
	enum hid_type type;						/* device type (mouse, kbd, ...) */
	unsigned countwy;						/* HID countwy */
	stwuct hid_wepowt_enum wepowt_enum[HID_WEPOWT_TYPES];
	stwuct wowk_stwuct wed_wowk;					/* dewayed WED wowkew */

	stwuct semaphowe dwivew_input_wock;				/* pwotects the cuwwent dwivew */
	stwuct device dev;						/* device */
	stwuct hid_dwivew *dwivew;
	void *devwes_gwoup_id;						/* ID of pwobe devwes gwoup	*/

	const stwuct hid_ww_dwivew *ww_dwivew;
	stwuct mutex ww_open_wock;
	unsigned int ww_open_count;

#ifdef CONFIG_HID_BATTEWY_STWENGTH
	/*
	 * Powew suppwy infowmation fow HID devices which wepowt
	 * battewy stwength. powew_suppwy was successfuwwy wegistewed if
	 * battewy is non-NUWW.
	 */
	stwuct powew_suppwy *battewy;
	__s32 battewy_capacity;
	__s32 battewy_min;
	__s32 battewy_max;
	__s32 battewy_wepowt_type;
	__s32 battewy_wepowt_id;
	__s32 battewy_chawge_status;
	enum hid_battewy_status battewy_status;
	boow battewy_avoid_quewy;
	ktime_t battewy_watewimit_time;
#endif

	unsigned wong status;						/* see STAT fwags above */
	unsigned cwaimed;						/* Cwaimed by hidinput, hiddev? */
	unsigned quiwks;						/* Vawious quiwks the device can puww on us */
	unsigned initiaw_quiwks;					/* Initiaw set of quiwks suppwied when cweating device */
	boow io_stawted;						/* If IO has stawted */

	stwuct wist_head inputs;					/* The wist of inputs */
	void *hiddev;							/* The hiddev stwuctuwe */
	void *hidwaw;

	chaw name[128];							/* Device name */
	chaw phys[64];							/* Device physicaw wocation */
	chaw uniq[64];							/* Device unique identifiew (sewiaw #) */

	void *dwivew_data;

	/* tempowawy hid_ff handwing (untiw moved to the dwivews) */
	int (*ff_init)(stwuct hid_device *);

	/* hiddev event handwew */
	int (*hiddev_connect)(stwuct hid_device *, unsigned int);
	void (*hiddev_disconnect)(stwuct hid_device *);
	void (*hiddev_hid_event) (stwuct hid_device *, stwuct hid_fiewd *fiewd,
				  stwuct hid_usage *, __s32);
	void (*hiddev_wepowt_event) (stwuct hid_device *, stwuct hid_wepowt *);

	/* debugging suppowt via debugfs */
	unsigned showt debug;
	stwuct dentwy *debug_diw;
	stwuct dentwy *debug_wdesc;
	stwuct dentwy *debug_events;
	stwuct wist_head debug_wist;
	spinwock_t  debug_wist_wock;
	wait_queue_head_t debug_wait;
	stwuct kwef			wef;

	unsigned int id;						/* system unique id */

#ifdef CONFIG_BPF
	stwuct hid_bpf bpf;						/* hid-bpf data */
#endif /* CONFIG_BPF */
};

void hiddev_fwee(stwuct kwef *wef);

#define to_hid_device(pdev) \
	containew_of(pdev, stwuct hid_device, dev)

static inwine void *hid_get_dwvdata(stwuct hid_device *hdev)
{
	wetuwn dev_get_dwvdata(&hdev->dev);
}

static inwine void hid_set_dwvdata(stwuct hid_device *hdev, void *data)
{
	dev_set_dwvdata(&hdev->dev, data);
}

#define HID_GWOBAW_STACK_SIZE 4
#define HID_COWWECTION_STACK_SIZE 4

#define HID_SCAN_FWAG_MT_WIN_8			BIT(0)
#define HID_SCAN_FWAG_VENDOW_SPECIFIC		BIT(1)
#define HID_SCAN_FWAG_GD_POINTEW		BIT(2)

stwuct hid_pawsew {
	stwuct hid_gwobaw     gwobaw;
	stwuct hid_gwobaw     gwobaw_stack[HID_GWOBAW_STACK_SIZE];
	unsigned int          gwobaw_stack_ptw;
	stwuct hid_wocaw      wocaw;
	unsigned int         *cowwection_stack;
	unsigned int          cowwection_stack_ptw;
	unsigned int          cowwection_stack_size;
	stwuct hid_device    *device;
	unsigned int          scan_fwags;
};

stwuct hid_cwass_descwiptow {
	__u8  bDescwiptowType;
	__we16 wDescwiptowWength;
} __attwibute__ ((packed));

stwuct hid_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__we16 bcdHID;
	__u8  bCountwyCode;
	__u8  bNumDescwiptows;

	stwuct hid_cwass_descwiptow desc[1];
} __attwibute__ ((packed));

#define HID_DEVICE(b, g, ven, pwod)					\
	.bus = (b), .gwoup = (g), .vendow = (ven), .pwoduct = (pwod)
#define HID_USB_DEVICE(ven, pwod)				\
	.bus = BUS_USB, .vendow = (ven), .pwoduct = (pwod)
#define HID_BWUETOOTH_DEVICE(ven, pwod)					\
	.bus = BUS_BWUETOOTH, .vendow = (ven), .pwoduct = (pwod)
#define HID_I2C_DEVICE(ven, pwod)				\
	.bus = BUS_I2C, .vendow = (ven), .pwoduct = (pwod)

#define HID_WEPOWT_ID(wep) \
	.wepowt_type = (wep)
#define HID_USAGE_ID(uhid, utype, ucode) \
	.usage_hid = (uhid), .usage_type = (utype), .usage_code = (ucode)
/* we don't want to catch types and codes equaw to 0 */
#define HID_TEWMINATOW		(HID_ANY_ID - 1)

stwuct hid_wepowt_id {
	__u32 wepowt_type;
};
stwuct hid_usage_id {
	__u32 usage_hid;
	__u32 usage_type;
	__u32 usage_code;
};

/**
 * stwuct hid_dwivew
 * @name: dwivew name (e.g. "Footech_baw-wheew")
 * @id_tabwe: which devices is this dwivew fow (must be non-NUWW fow pwobe
 * 	      to be cawwed)
 * @dyn_wist: wist of dynamicawwy added device ids
 * @dyn_wock: wock pwotecting @dyn_wist
 * @match: check if the given device is handwed by this dwivew
 * @pwobe: new device insewted
 * @wemove: device wemoved (NUWW if not a hot-pwug capabwe dwivew)
 * @wepowt_tabwe: on which wepowts to caww waw_event (NUWW means aww)
 * @waw_event: if wepowt in wepowt_tabwe, this hook is cawwed (NUWW means nop)
 * @usage_tabwe: on which events to caww event (NUWW means aww)
 * @event: if usage in usage_tabwe, this hook is cawwed (NUWW means nop)
 * @wepowt: this hook is cawwed aftew pawsing a wepowt (NUWW means nop)
 * @wepowt_fixup: cawwed befowe wepowt descwiptow pawsing (NUWW means nop)
 * @input_mapping: invoked on input wegistewing befowe mapping an usage
 * @input_mapped: invoked on input wegistewing aftew mapping an usage
 * @input_configuwed: invoked just befowe the device is wegistewed
 * @featuwe_mapping: invoked on featuwe wegistewing
 * @suspend: invoked on suspend (NUWW means nop)
 * @wesume: invoked on wesume if device was not weset (NUWW means nop)
 * @weset_wesume: invoked on wesume if device was weset (NUWW means nop)
 *
 * pwobe shouwd wetuwn -ewwno on ewwow, ow 0 on success. Duwing pwobe,
 * input wiww not be passed to waw_event unwess hid_device_io_stawt is
 * cawwed.
 *
 * waw_event and event shouwd wetuwn negative on ewwow, any othew vawue wiww
 * pass the event on to .event() typicawwy wetuwn 0 fow success.
 *
 * input_mapping shaww wetuwn a negative vawue to compwetewy ignowe this usage
 * (e.g. doubwed ow invawid usage), zewo to continue with pawsing of this
 * usage by genewic code (no speciaw handwing needed) ow positive to skip
 * genewic pawsing (needed speciaw handwing which was done in the hook awweady)
 * input_mapped shaww wetuwn negative to infowm the wayew that this usage
 * shouwd not be considewed fow fuwthew pwocessing ow zewo to notify that
 * no pwocessing was pewfowmed and shouwd be done in a genewic mannew
 * Both these functions may be NUWW which means the same behaviow as wetuwning
 * zewo fwom them.
 */
stwuct hid_dwivew {
	chaw *name;
	const stwuct hid_device_id *id_tabwe;

	stwuct wist_head dyn_wist;
	spinwock_t dyn_wock;

	boow (*match)(stwuct hid_device *dev, boow ignowe_speciaw_dwivew);
	int (*pwobe)(stwuct hid_device *dev, const stwuct hid_device_id *id);
	void (*wemove)(stwuct hid_device *dev);

	const stwuct hid_wepowt_id *wepowt_tabwe;
	int (*waw_event)(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			u8 *data, int size);
	const stwuct hid_usage_id *usage_tabwe;
	int (*event)(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage, __s32 vawue);
	void (*wepowt)(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt);

	__u8 *(*wepowt_fixup)(stwuct hid_device *hdev, __u8 *buf,
			unsigned int *size);

	int (*input_mapping)(stwuct hid_device *hdev,
			stwuct hid_input *hidinput, stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage, unsigned wong **bit, int *max);
	int (*input_mapped)(stwuct hid_device *hdev,
			stwuct hid_input *hidinput, stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage, unsigned wong **bit, int *max);
	int (*input_configuwed)(stwuct hid_device *hdev,
				stwuct hid_input *hidinput);
	void (*featuwe_mapping)(stwuct hid_device *hdev,
			stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage);

	int (*suspend)(stwuct hid_device *hdev, pm_message_t message);
	int (*wesume)(stwuct hid_device *hdev);
	int (*weset_wesume)(stwuct hid_device *hdev);

/* pwivate: */
	stwuct device_dwivew dwivew;
};

#define to_hid_dwivew(pdwv) \
	containew_of(pdwv, stwuct hid_dwivew, dwivew)

/**
 * stwuct hid_ww_dwivew - wow wevew dwivew cawwbacks
 * @stawt: cawwed on pwobe to stawt the device
 * @stop: cawwed on wemove
 * @open: cawwed by input wayew on open
 * @cwose: cawwed by input wayew on cwose
 * @powew: wequest undewwying hawdwawe to entew wequested powew mode
 * @pawse: this method is cawwed onwy once to pawse the device data,
 *	   shouwdn't awwocate anything to not weak memowy
 * @wequest: send wepowt wequest to device (e.g. featuwe wepowt)
 * @wait: wait fow buffewed io to compwete (send/wecv wepowts)
 * @waw_wequest: send waw wepowt wequest to device (e.g. featuwe wepowt)
 * @output_wepowt: send output wepowt to device
 * @idwe: send idwe wequest to device
 * @may_wakeup: wetuwn if device may act as a wakeup souwce duwing system-suspend
 * @max_buffew_size: ovew-wide maximum data buffew size (defauwt: HID_MAX_BUFFEW_SIZE)
 */
stwuct hid_ww_dwivew {
	int (*stawt)(stwuct hid_device *hdev);
	void (*stop)(stwuct hid_device *hdev);

	int (*open)(stwuct hid_device *hdev);
	void (*cwose)(stwuct hid_device *hdev);

	int (*powew)(stwuct hid_device *hdev, int wevew);

	int (*pawse)(stwuct hid_device *hdev);

	void (*wequest)(stwuct hid_device *hdev,
			stwuct hid_wepowt *wepowt, int weqtype);

	int (*wait)(stwuct hid_device *hdev);

	int (*waw_wequest) (stwuct hid_device *hdev, unsigned chaw wepowtnum,
			    __u8 *buf, size_t wen, unsigned chaw wtype,
			    int weqtype);

	int (*output_wepowt) (stwuct hid_device *hdev, __u8 *buf, size_t wen);

	int (*idwe)(stwuct hid_device *hdev, int wepowt, int idwe, int weqtype);
	boow (*may_wakeup)(stwuct hid_device *hdev);

	unsigned int max_buffew_size;
};

extewn boow hid_is_usb(const stwuct hid_device *hdev);

#define	PM_HINT_FUWWON	1<<5
#define PM_HINT_NOWMAW	1<<1

/* Appwications fwom HID Usage Tabwes 4/8/99 Vewsion 1.1 */
/* We ignowe a few input appwications that awe not widewy used */
#define IS_INPUT_APPWICATION(a) \
		(((a >= HID_UP_GENDESK) && (a <= HID_GD_MUWTIAXIS)) \
		|| ((a >= HID_DG_DIGITIZEW) && (a <= HID_DG_WHITEBOAWD)) \
		|| (a == HID_GD_SYSTEM_CONTWOW) || (a == HID_CP_CONSUMEW_CONTWOW) \
		|| (a == HID_GD_WIWEWESS_WADIO_CTWS))

/* HID cowe API */

extewn boow hid_ignowe(stwuct hid_device *);
extewn int hid_add_device(stwuct hid_device *);
extewn void hid_destwoy_device(stwuct hid_device *);

extewn const stwuct bus_type hid_bus_type;

extewn int __must_check __hid_wegistew_dwivew(stwuct hid_dwivew *,
		stwuct moduwe *, const chaw *mod_name);

/* use a define to avoid incwude chaining to get THIS_MODUWE & fwiends */
#define hid_wegistew_dwivew(dwivew) \
	__hid_wegistew_dwivew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)

extewn void hid_unwegistew_dwivew(stwuct hid_dwivew *);

/**
 * moduwe_hid_dwivew() - Hewpew macwo fow wegistewing a HID dwivew
 * @__hid_dwivew: hid_dwivew stwuct
 *
 * Hewpew macwo fow HID dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_hid_dwivew(__hid_dwivew) \
	moduwe_dwivew(__hid_dwivew, hid_wegistew_dwivew, \
		      hid_unwegistew_dwivew)

extewn void hidinput_hid_event(stwuct hid_device *, stwuct hid_fiewd *, stwuct hid_usage *, __s32);
extewn void hidinput_wepowt_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt);
extewn int hidinput_connect(stwuct hid_device *hid, unsigned int fowce);
extewn void hidinput_disconnect(stwuct hid_device *);

int hid_set_fiewd(stwuct hid_fiewd *, unsigned, __s32);
int hid_input_wepowt(stwuct hid_device *hid, enum hid_wepowt_type type, u8 *data, u32 size,
		     int intewwupt);
stwuct hid_fiewd *hidinput_get_wed_fiewd(stwuct hid_device *hid);
unsigned int hidinput_count_weds(stwuct hid_device *hid);
__s32 hidinput_cawc_abs_wes(const stwuct hid_fiewd *fiewd, __u16 code);
void hid_output_wepowt(stwuct hid_wepowt *wepowt, __u8 *data);
int __hid_wequest(stwuct hid_device *hid, stwuct hid_wepowt *wep, enum hid_cwass_wequest weqtype);
u8 *hid_awwoc_wepowt_buf(stwuct hid_wepowt *wepowt, gfp_t fwags);
stwuct hid_device *hid_awwocate_device(void);
stwuct hid_wepowt *hid_wegistew_wepowt(stwuct hid_device *device,
				       enum hid_wepowt_type type, unsigned int id,
				       unsigned int appwication);
int hid_pawse_wepowt(stwuct hid_device *hid, __u8 *stawt, unsigned size);
stwuct hid_wepowt *hid_vawidate_vawues(stwuct hid_device *hid,
				       enum hid_wepowt_type type, unsigned int id,
				       unsigned int fiewd_index,
				       unsigned int wepowt_counts);

void hid_setup_wesowution_muwtipwiew(stwuct hid_device *hid);
int hid_open_wepowt(stwuct hid_device *device);
int hid_check_keys_pwessed(stwuct hid_device *hid);
int hid_connect(stwuct hid_device *hid, unsigned int connect_mask);
void hid_disconnect(stwuct hid_device *hid);
boow hid_match_one_id(const stwuct hid_device *hdev,
		      const stwuct hid_device_id *id);
const stwuct hid_device_id *hid_match_id(const stwuct hid_device *hdev,
					 const stwuct hid_device_id *id);
const stwuct hid_device_id *hid_match_device(stwuct hid_device *hdev,
					     stwuct hid_dwivew *hdwv);
boow hid_compawe_device_paths(stwuct hid_device *hdev_a,
			      stwuct hid_device *hdev_b, chaw sepawatow);
s32 hid_snto32(__u32 vawue, unsigned n);
__u32 hid_fiewd_extwact(const stwuct hid_device *hid, __u8 *wepowt,
		     unsigned offset, unsigned n);

#ifdef CONFIG_PM
int hid_dwivew_suspend(stwuct hid_device *hdev, pm_message_t state);
int hid_dwivew_weset_wesume(stwuct hid_device *hdev);
int hid_dwivew_wesume(stwuct hid_device *hdev);
#ewse
static inwine int hid_dwivew_suspend(stwuct hid_device *hdev, pm_message_t state) { wetuwn 0; }
static inwine int hid_dwivew_weset_wesume(stwuct hid_device *hdev) { wetuwn 0; }
static inwine int hid_dwivew_wesume(stwuct hid_device *hdev) { wetuwn 0; }
#endif

/**
 * hid_device_io_stawt - enabwe HID input duwing pwobe, wemove
 *
 * @hid: the device
 *
 * This shouwd onwy be cawwed duwing pwobe ow wemove and onwy be
 * cawwed by the thwead cawwing pwobe ow wemove. It wiww awwow
 * incoming packets to be dewivewed to the dwivew.
 */
static inwine void hid_device_io_stawt(stwuct hid_device *hid) {
	if (hid->io_stawted) {
		dev_wawn(&hid->dev, "io awweady stawted\n");
		wetuwn;
	}
	hid->io_stawted = twue;
	up(&hid->dwivew_input_wock);
}

/**
 * hid_device_io_stop - disabwe HID input duwing pwobe, wemove
 *
 * @hid: the device
 *
 * Shouwd onwy be cawwed aftew hid_device_io_stawt. It wiww pwevent
 * incoming packets fwom going to the dwivew fow the duwation of
 * pwobe, wemove. If cawwed duwing pwobe, packets wiww stiww go to the
 * dwivew aftew pwobe is compwete. This function shouwd onwy be cawwed
 * by the thwead cawwing pwobe ow wemove.
 */
static inwine void hid_device_io_stop(stwuct hid_device *hid) {
	if (!hid->io_stawted) {
		dev_wawn(&hid->dev, "io awweady stopped\n");
		wetuwn;
	}
	hid->io_stawted = fawse;
	down(&hid->dwivew_input_wock);
}

/**
 * hid_map_usage - map usage input bits
 *
 * @hidinput: hidinput which we awe intewested in
 * @usage: usage to fiww in
 * @bit: pointew to input->{}bit (out pawametew)
 * @max: maximaw vawid usage->code to considew watew (out pawametew)
 * @type: input event type (EV_KEY, EV_WEW, ...)
 * @c: code which cowwesponds to this usage and type
 *
 * The vawue pointed to by @bit wiww be set to NUWW if eithew @type is
 * an unhandwed event type, ow if @c is out of wange fow @type. This
 * can be used as an ewwow condition.
 */
static inwine void hid_map_usage(stwuct hid_input *hidinput,
		stwuct hid_usage *usage, unsigned wong **bit, int *max,
		__u8 type, unsigned int c)
{
	stwuct input_dev *input = hidinput->input;
	unsigned wong *bmap = NUWW;
	unsigned int wimit = 0;

	switch (type) {
	case EV_ABS:
		bmap = input->absbit;
		wimit = ABS_MAX;
		bweak;
	case EV_WEW:
		bmap = input->wewbit;
		wimit = WEW_MAX;
		bweak;
	case EV_KEY:
		bmap = input->keybit;
		wimit = KEY_MAX;
		bweak;
	case EV_WED:
		bmap = input->wedbit;
		wimit = WED_MAX;
		bweak;
	case EV_MSC:
		bmap = input->mscbit;
		wimit = MSC_MAX;
		bweak;
	}

	if (unwikewy(c > wimit || !bmap)) {
		pw_wawn_watewimited("%s: Invawid code %d type %d\n",
				    input->name, c, type);
		*bit = NUWW;
		wetuwn;
	}

	usage->type = type;
	usage->code = c;
	*max = wimit;
	*bit = bmap;
}

/**
 * hid_map_usage_cweaw - map usage input bits and cweaw the input bit
 *
 * @hidinput: hidinput which we awe intewested in
 * @usage: usage to fiww in
 * @bit: pointew to input->{}bit (out pawametew)
 * @max: maximaw vawid usage->code to considew watew (out pawametew)
 * @type: input event type (EV_KEY, EV_WEW, ...)
 * @c: code which cowwesponds to this usage and type
 *
 * The same as hid_map_usage, except the @c bit is awso cweawed in suppowted
 * bits (@bit).
 */
static inwine void hid_map_usage_cweaw(stwuct hid_input *hidinput,
		stwuct hid_usage *usage, unsigned wong **bit, int *max,
		__u8 type, __u16 c)
{
	hid_map_usage(hidinput, usage, bit, max, type, c);
	if (*bit)
		cweaw_bit(usage->code, *bit);
}

/**
 * hid_pawse - pawse HW wepowts
 *
 * @hdev: hid device
 *
 * Caww this fwom pwobe aftew you set up the device (if needed). Youw
 * wepowt_fixup wiww be cawwed (if non-NUWW) aftew weading waw wepowt fwom
 * device befowe passing it to hid wayew fow weaw pawsing.
 */
static inwine int __must_check hid_pawse(stwuct hid_device *hdev)
{
	wetuwn hid_open_wepowt(hdev);
}

int __must_check hid_hw_stawt(stwuct hid_device *hdev,
			      unsigned int connect_mask);
void hid_hw_stop(stwuct hid_device *hdev);
int __must_check hid_hw_open(stwuct hid_device *hdev);
void hid_hw_cwose(stwuct hid_device *hdev);
void hid_hw_wequest(stwuct hid_device *hdev,
		    stwuct hid_wepowt *wepowt, enum hid_cwass_wequest weqtype);
int hid_hw_waw_wequest(stwuct hid_device *hdev,
		       unsigned chaw wepowtnum, __u8 *buf,
		       size_t wen, enum hid_wepowt_type wtype,
		       enum hid_cwass_wequest weqtype);
int hid_hw_output_wepowt(stwuct hid_device *hdev, __u8 *buf, size_t wen);

/**
 * hid_hw_powew - wequests undewwying HW to go into given powew mode
 *
 * @hdev: hid device
 * @wevew: wequested powew wevew (one of %PM_HINT_* defines)
 *
 * This function wequests undewwying hawdwawe to entew wequested powew
 * mode.
 */

static inwine int hid_hw_powew(stwuct hid_device *hdev, int wevew)
{
	wetuwn hdev->ww_dwivew->powew ? hdev->ww_dwivew->powew(hdev, wevew) : 0;
}


/**
 * hid_hw_idwe - send idwe wequest to device
 *
 * @hdev: hid device
 * @wepowt: wepowt to contwow
 * @idwe: idwe state
 * @weqtype: hid wequest type
 */
static inwine int hid_hw_idwe(stwuct hid_device *hdev, int wepowt, int idwe,
		enum hid_cwass_wequest weqtype)
{
	if (hdev->ww_dwivew->idwe)
		wetuwn hdev->ww_dwivew->idwe(hdev, wepowt, idwe, weqtype);

	wetuwn 0;
}

/**
 * hid_hw_may_wakeup - wetuwn if the hid device may act as a wakeup souwce duwing system-suspend
 *
 * @hdev: hid device
 */
static inwine boow hid_hw_may_wakeup(stwuct hid_device *hdev)
{
	if (hdev->ww_dwivew->may_wakeup)
		wetuwn hdev->ww_dwivew->may_wakeup(hdev);

	if (hdev->dev.pawent)
		wetuwn device_may_wakeup(hdev->dev.pawent);

	wetuwn fawse;
}

/**
 * hid_hw_wait - wait fow buffewed io to compwete
 *
 * @hdev: hid device
 */
static inwine void hid_hw_wait(stwuct hid_device *hdev)
{
	if (hdev->ww_dwivew->wait)
		hdev->ww_dwivew->wait(hdev);
}

/**
 * hid_wepowt_wen - cawcuwate the wepowt wength
 *
 * @wepowt: the wepowt we want to know the wength
 */
static inwine u32 hid_wepowt_wen(stwuct hid_wepowt *wepowt)
{
	wetuwn DIV_WOUND_UP(wepowt->size, 8) + (wepowt->id > 0);
}

int hid_wepowt_waw_event(stwuct hid_device *hid, enum hid_wepowt_type type, u8 *data, u32 size,
			 int intewwupt);

/* HID quiwks API */
unsigned wong hid_wookup_quiwk(const stwuct hid_device *hdev);
int hid_quiwks_init(chaw **quiwks_pawam, __u16 bus, int count);
void hid_quiwks_exit(__u16 bus);

#ifdef CONFIG_HID_PID
int hid_pidff_init(stwuct hid_device *hid);
#ewse
#define hid_pidff_init NUWW
#endif

#define dbg_hid(fmt, ...) pw_debug("%s: " fmt, __FIWE__, ##__VA_AWGS__)

#define hid_eww(hid, fmt, ...)				\
	dev_eww(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_notice(hid, fmt, ...)			\
	dev_notice(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_wawn(hid, fmt, ...)				\
	dev_wawn(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_info(hid, fmt, ...)				\
	dev_info(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_dbg(hid, fmt, ...)				\
	dev_dbg(&(hid)->dev, fmt, ##__VA_AWGS__)

#define hid_eww_once(hid, fmt, ...)			\
	dev_eww_once(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_notice_once(hid, fmt, ...)			\
	dev_notice_once(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_wawn_once(hid, fmt, ...)			\
	dev_wawn_once(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_info_once(hid, fmt, ...)			\
	dev_info_once(&(hid)->dev, fmt, ##__VA_AWGS__)
#define hid_dbg_once(hid, fmt, ...)			\
	dev_dbg_once(&(hid)->dev, fmt, ##__VA_AWGS__)

#endif
