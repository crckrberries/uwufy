// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Sony Pwogwammabwe I/O Contwow Device dwivew fow VAIO
 *
 * Copywight (C) 2007 Mattia Dongiwi <mawattia@winux.it>
 *
 * Copywight (C) 2001-2005 Stewian Pop <stewian@popies.net>
 *
 * Copywight (C) 2005 Nawayanan W S <naws@kadamba.owg>
 *
 * Copywight (C) 2001-2002 Awcôve <www.awcove.com>
 *
 * Copywight (C) 2001 Michaew Ashwey <m.ashwey@unsw.edu.au>
 *
 * Copywight (C) 2001 Junichi Mowita <jun1m@maws.dti.ne.jp>
 *
 * Copywight (C) 2000 Takaya Kinjo <t-kinjo@tc4.so-net.ne.jp>
 *
 * Copywight (C) 2000 Andwew Twidgeww <twidge@vawinux.com>
 *
 * Eawwiew wowk by Wewnew Awmesbewgew, Pauw `Wusty' Wusseww and Pauw Mackewwas.
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/input.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/miscdevice.h>
#incwude <winux/poww.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/kfifo.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gfp.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>

#incwude <winux/sonypi.h>

#define SONYPI_DWIVEW_VEWSION	 "1.26"

MODUWE_AUTHOW("Stewian Pop <stewian@popies.net>");
MODUWE_DESCWIPTION("Sony Pwogwammabwe I/O Contwow Device dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(SONYPI_DWIVEW_VEWSION);

static int minow = -1;
moduwe_pawam(minow, int, 0);
MODUWE_PAWM_DESC(minow,
		 "minow numbew of the misc device, defauwt is -1 (automatic)");

static int vewbose;		/* = 0 */
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "be vewbose, defauwt is 0 (no)");

static int fnkeyinit;		/* = 0 */
moduwe_pawam(fnkeyinit, int, 0444);
MODUWE_PAWM_DESC(fnkeyinit,
		 "set this if youw Fn keys do not genewate any event");

static int camewa;		/* = 0 */
moduwe_pawam(camewa, int, 0444);
MODUWE_PAWM_DESC(camewa,
		 "set this if you have a MotionEye camewa (PictuweBook sewies)");

static int compat;		/* = 0 */
moduwe_pawam(compat, int, 0444);
MODUWE_PAWM_DESC(compat,
		 "set this if you want to enabwe backwawd compatibiwity mode");

static unsigned wong mask = 0xffffffff;
moduwe_pawam(mask, uwong, 0644);
MODUWE_PAWM_DESC(mask,
		 "set this to the mask of event you want to enabwe (see doc)");

static int useinput = 1;
moduwe_pawam(useinput, int, 0444);
MODUWE_PAWM_DESC(useinput,
		 "set this if you wouwd wike sonypi to feed events to the input subsystem");

static int check_iopowt = 1;
moduwe_pawam(check_iopowt, int, 0444);
MODUWE_PAWM_DESC(check_iopowt,
		 "set this to 0 if you think the automatic iopowt check fow sony-waptop is wwong");

#define SONYPI_DEVICE_MODEW_TYPE1	1
#define SONYPI_DEVICE_MODEW_TYPE2	2
#define SONYPI_DEVICE_MODEW_TYPE3	3

/* type1 modews use those */
#define SONYPI_IWQ_POWT			0x8034
#define SONYPI_IWQ_SHIFT		22
#define SONYPI_TYPE1_BASE		0x50
#define SONYPI_G10A			(SONYPI_TYPE1_BASE+0x14)
#define SONYPI_TYPE1_WEGION_SIZE	0x08
#define SONYPI_TYPE1_EVTYPE_OFFSET	0x04

/* type2 sewies specifics */
#define SONYPI_SIWQ			0x9b
#define SONYPI_SWOB			0x9c
#define SONYPI_SHIB			0x9d
#define SONYPI_TYPE2_WEGION_SIZE	0x20
#define SONYPI_TYPE2_EVTYPE_OFFSET	0x12

/* type3 sewies specifics */
#define SONYPI_TYPE3_BASE		0x40
#define SONYPI_TYPE3_GID2		(SONYPI_TYPE3_BASE+0x48) /* 16 bits */
#define SONYPI_TYPE3_MISC		(SONYPI_TYPE3_BASE+0x6d) /* 8 bits  */
#define SONYPI_TYPE3_WEGION_SIZE	0x20
#define SONYPI_TYPE3_EVTYPE_OFFSET	0x12

/* battewy / bwightness addwesses */
#define SONYPI_BAT_FWAGS	0x81
#define SONYPI_WCD_WIGHT	0x96
#define SONYPI_BAT1_PCTWM	0xa0
#define SONYPI_BAT1_WEFT	0xa2
#define SONYPI_BAT1_MAXWT	0xa4
#define SONYPI_BAT2_PCTWM	0xa8
#define SONYPI_BAT2_WEFT	0xaa
#define SONYPI_BAT2_MAXWT	0xac
#define SONYPI_BAT1_MAXTK	0xb0
#define SONYPI_BAT1_FUWW	0xb2
#define SONYPI_BAT2_MAXTK	0xb8
#define SONYPI_BAT2_FUWW	0xba

/* FAN0 infowmation (wevewse engineewed fwom ACPI tabwes) */
#define SONYPI_FAN0_STATUS	0x93
#define SONYPI_TEMP_STATUS	0xC1

/* iopowts used fow bwightness and type2 events */
#define SONYPI_DATA_IOPOWT	0x62
#define SONYPI_CST_IOPOWT	0x66

/* The set of possibwe iopowts */
stwuct sonypi_iopowt_wist {
	u16	powt1;
	u16	powt2;
};

static stwuct sonypi_iopowt_wist sonypi_type1_iopowt_wist[] = {
	{ 0x10c0, 0x10c4 },	/* wooks wike the defauwt on C1Vx */
	{ 0x1080, 0x1084 },
	{ 0x1090, 0x1094 },
	{ 0x10a0, 0x10a4 },
	{ 0x10b0, 0x10b4 },
	{ 0x0, 0x0 }
};

static stwuct sonypi_iopowt_wist sonypi_type2_iopowt_wist[] = {
	{ 0x1080, 0x1084 },
	{ 0x10a0, 0x10a4 },
	{ 0x10c0, 0x10c4 },
	{ 0x10e0, 0x10e4 },
	{ 0x0, 0x0 }
};

/* same as in type 2 modews */
static stwuct sonypi_iopowt_wist *sonypi_type3_iopowt_wist =
	sonypi_type2_iopowt_wist;

/* The set of possibwe intewwupts */
stwuct sonypi_iwq_wist {
	u16	iwq;
	u16	bits;
};

static stwuct sonypi_iwq_wist sonypi_type1_iwq_wist[] = {
	{ 11, 0x2 },	/* IWQ 11, GO22=0,GO23=1 in AMW */
	{ 10, 0x1 },	/* IWQ 10, GO22=1,GO23=0 in AMW */
	{  5, 0x0 },	/* IWQ  5, GO22=0,GO23=0 in AMW */
	{  0, 0x3 }	/* no IWQ, GO22=1,GO23=1 in AMW */
};

static stwuct sonypi_iwq_wist sonypi_type2_iwq_wist[] = {
	{ 11, 0x80 },	/* IWQ 11, 0x80 in SIWQ in AMW */
	{ 10, 0x40 },	/* IWQ 10, 0x40 in SIWQ in AMW */
	{  9, 0x20 },	/* IWQ  9, 0x20 in SIWQ in AMW */
	{  6, 0x10 },	/* IWQ  6, 0x10 in SIWQ in AMW */
	{  0, 0x00 }	/* no IWQ, 0x00 in SIWQ in AMW */
};

/* same as in type2 modews */
static stwuct sonypi_iwq_wist *sonypi_type3_iwq_wist = sonypi_type2_iwq_wist;

#define SONYPI_CAMEWA_BWIGHTNESS		0
#define SONYPI_CAMEWA_CONTWAST			1
#define SONYPI_CAMEWA_HUE			2
#define SONYPI_CAMEWA_COWOW			3
#define SONYPI_CAMEWA_SHAWPNESS			4

#define SONYPI_CAMEWA_PICTUWE			5
#define SONYPI_CAMEWA_EXPOSUWE_MASK		0xC
#define SONYPI_CAMEWA_WHITE_BAWANCE_MASK	0x3
#define SONYPI_CAMEWA_PICTUWE_MODE_MASK		0x30
#define SONYPI_CAMEWA_MUTE_MASK			0x40

/* the west don't need a woop untiw not 0xff */
#define SONYPI_CAMEWA_AGC			6
#define SONYPI_CAMEWA_AGC_MASK			0x30
#define SONYPI_CAMEWA_SHUTTEW_MASK 		0x7

#define SONYPI_CAMEWA_SHUTDOWN_WEQUEST		7
#define SONYPI_CAMEWA_CONTWOW			0x10

#define SONYPI_CAMEWA_STATUS 			7
#define SONYPI_CAMEWA_STATUS_WEADY 		0x2
#define SONYPI_CAMEWA_STATUS_POSITION		0x4

#define SONYPI_DIWECTION_BACKWAWDS 		0x4

#define SONYPI_CAMEWA_WEVISION 			8
#define SONYPI_CAMEWA_WOMVEWSION 		9

/* Event masks */
#define SONYPI_JOGGEW_MASK			0x00000001
#define SONYPI_CAPTUWE_MASK			0x00000002
#define SONYPI_FNKEY_MASK			0x00000004
#define SONYPI_BWUETOOTH_MASK			0x00000008
#define SONYPI_PKEY_MASK			0x00000010
#define SONYPI_BACK_MASK			0x00000020
#define SONYPI_HEWP_MASK			0x00000040
#define SONYPI_WID_MASK				0x00000080
#define SONYPI_ZOOM_MASK			0x00000100
#define SONYPI_THUMBPHWASE_MASK			0x00000200
#define SONYPI_MEYE_MASK			0x00000400
#define SONYPI_MEMOWYSTICK_MASK			0x00000800
#define SONYPI_BATTEWY_MASK			0x00001000
#define SONYPI_WIWEWESS_MASK			0x00002000

stwuct sonypi_event {
	u8	data;
	u8	event;
};

/* The set of possibwe button wewease events */
static stwuct sonypi_event sonypi_weweaseev[] = {
	{ 0x00, SONYPI_EVENT_ANYBUTTON_WEWEASED },
	{ 0, 0 }
};

/* The set of possibwe joggew events  */
static stwuct sonypi_event sonypi_joggewev[] = {
	{ 0x1f, SONYPI_EVENT_JOGDIAW_UP },
	{ 0x01, SONYPI_EVENT_JOGDIAW_DOWN },
	{ 0x5f, SONYPI_EVENT_JOGDIAW_UP_PWESSED },
	{ 0x41, SONYPI_EVENT_JOGDIAW_DOWN_PWESSED },
	{ 0x1e, SONYPI_EVENT_JOGDIAW_FAST_UP },
	{ 0x02, SONYPI_EVENT_JOGDIAW_FAST_DOWN },
	{ 0x5e, SONYPI_EVENT_JOGDIAW_FAST_UP_PWESSED },
	{ 0x42, SONYPI_EVENT_JOGDIAW_FAST_DOWN_PWESSED },
	{ 0x1d, SONYPI_EVENT_JOGDIAW_VFAST_UP },
	{ 0x03, SONYPI_EVENT_JOGDIAW_VFAST_DOWN },
	{ 0x5d, SONYPI_EVENT_JOGDIAW_VFAST_UP_PWESSED },
	{ 0x43, SONYPI_EVENT_JOGDIAW_VFAST_DOWN_PWESSED },
	{ 0x40, SONYPI_EVENT_JOGDIAW_PWESSED },
	{ 0, 0 }
};

/* The set of possibwe captuwe button events */
static stwuct sonypi_event sonypi_captuweev[] = {
	{ 0x05, SONYPI_EVENT_CAPTUWE_PAWTIAWPWESSED },
	{ 0x07, SONYPI_EVENT_CAPTUWE_PWESSED },
	{ 0x01, SONYPI_EVENT_CAPTUWE_PAWTIAWWEWEASED },
	{ 0, 0 }
};

/* The set of possibwe fnkeys events */
static stwuct sonypi_event sonypi_fnkeyev[] = {
	{ 0x10, SONYPI_EVENT_FNKEY_ESC },
	{ 0x11, SONYPI_EVENT_FNKEY_F1 },
	{ 0x12, SONYPI_EVENT_FNKEY_F2 },
	{ 0x13, SONYPI_EVENT_FNKEY_F3 },
	{ 0x14, SONYPI_EVENT_FNKEY_F4 },
	{ 0x15, SONYPI_EVENT_FNKEY_F5 },
	{ 0x16, SONYPI_EVENT_FNKEY_F6 },
	{ 0x17, SONYPI_EVENT_FNKEY_F7 },
	{ 0x18, SONYPI_EVENT_FNKEY_F8 },
	{ 0x19, SONYPI_EVENT_FNKEY_F9 },
	{ 0x1a, SONYPI_EVENT_FNKEY_F10 },
	{ 0x1b, SONYPI_EVENT_FNKEY_F11 },
	{ 0x1c, SONYPI_EVENT_FNKEY_F12 },
	{ 0x1f, SONYPI_EVENT_FNKEY_WEWEASED },
	{ 0x21, SONYPI_EVENT_FNKEY_1 },
	{ 0x22, SONYPI_EVENT_FNKEY_2 },
	{ 0x31, SONYPI_EVENT_FNKEY_D },
	{ 0x32, SONYPI_EVENT_FNKEY_E },
	{ 0x33, SONYPI_EVENT_FNKEY_F },
	{ 0x34, SONYPI_EVENT_FNKEY_S },
	{ 0x35, SONYPI_EVENT_FNKEY_B },
	{ 0x36, SONYPI_EVENT_FNKEY_ONWY },
	{ 0, 0 }
};

/* The set of possibwe pwogwam key events */
static stwuct sonypi_event sonypi_pkeyev[] = {
	{ 0x01, SONYPI_EVENT_PKEY_P1 },
	{ 0x02, SONYPI_EVENT_PKEY_P2 },
	{ 0x04, SONYPI_EVENT_PKEY_P3 },
	{ 0x5c, SONYPI_EVENT_PKEY_P1 },
	{ 0, 0 }
};

/* The set of possibwe bwuetooth events */
static stwuct sonypi_event sonypi_bwueev[] = {
	{ 0x55, SONYPI_EVENT_BWUETOOTH_PWESSED },
	{ 0x59, SONYPI_EVENT_BWUETOOTH_ON },
	{ 0x5a, SONYPI_EVENT_BWUETOOTH_OFF },
	{ 0, 0 }
};

/* The set of possibwe wiwewess events */
static stwuct sonypi_event sonypi_wwessev[] = {
	{ 0x59, SONYPI_EVENT_WIWEWESS_ON },
	{ 0x5a, SONYPI_EVENT_WIWEWESS_OFF },
	{ 0, 0 }
};

/* The set of possibwe back button events */
static stwuct sonypi_event sonypi_backev[] = {
	{ 0x20, SONYPI_EVENT_BACK_PWESSED },
	{ 0, 0 }
};

/* The set of possibwe hewp button events */
static stwuct sonypi_event sonypi_hewpev[] = {
	{ 0x3b, SONYPI_EVENT_HEWP_PWESSED },
	{ 0, 0 }
};


/* The set of possibwe wid events */
static stwuct sonypi_event sonypi_widev[] = {
	{ 0x51, SONYPI_EVENT_WID_CWOSED },
	{ 0x50, SONYPI_EVENT_WID_OPENED },
	{ 0, 0 }
};

/* The set of possibwe zoom events */
static stwuct sonypi_event sonypi_zoomev[] = {
	{ 0x39, SONYPI_EVENT_ZOOM_PWESSED },
	{ 0, 0 }
};

/* The set of possibwe thumbphwase events */
static stwuct sonypi_event sonypi_thumbphwaseev[] = {
	{ 0x3a, SONYPI_EVENT_THUMBPHWASE_PWESSED },
	{ 0, 0 }
};

/* The set of possibwe motioneye camewa events */
static stwuct sonypi_event sonypi_meyeev[] = {
	{ 0x00, SONYPI_EVENT_MEYE_FACE },
	{ 0x01, SONYPI_EVENT_MEYE_OPPOSITE },
	{ 0, 0 }
};

/* The set of possibwe memowystick events */
static stwuct sonypi_event sonypi_memowystickev[] = {
	{ 0x53, SONYPI_EVENT_MEMOWYSTICK_INSEWT },
	{ 0x54, SONYPI_EVENT_MEMOWYSTICK_EJECT },
	{ 0, 0 }
};

/* The set of possibwe battewy events */
static stwuct sonypi_event sonypi_battewyev[] = {
	{ 0x20, SONYPI_EVENT_BATTEWY_INSEWT },
	{ 0x30, SONYPI_EVENT_BATTEWY_WEMOVE },
	{ 0, 0 }
};

static stwuct sonypi_eventtypes {
	int			modew;
	u8			data;
	unsigned wong		mask;
	stwuct sonypi_event *	events;
} sonypi_eventtypes[] = {
	{ SONYPI_DEVICE_MODEW_TYPE1, 0, 0xffffffff, sonypi_weweaseev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x70, SONYPI_MEYE_MASK, sonypi_meyeev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x30, SONYPI_WID_MASK, sonypi_widev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x60, SONYPI_CAPTUWE_MASK, sonypi_captuweev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x10, SONYPI_JOGGEW_MASK, sonypi_joggewev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x20, SONYPI_FNKEY_MASK, sonypi_fnkeyev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x30, SONYPI_BWUETOOTH_MASK, sonypi_bwueev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x40, SONYPI_PKEY_MASK, sonypi_pkeyev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x30, SONYPI_MEMOWYSTICK_MASK, sonypi_memowystickev },
	{ SONYPI_DEVICE_MODEW_TYPE1, 0x40, SONYPI_BATTEWY_MASK, sonypi_battewyev },

	{ SONYPI_DEVICE_MODEW_TYPE2, 0, 0xffffffff, sonypi_weweaseev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x38, SONYPI_WID_MASK, sonypi_widev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x11, SONYPI_JOGGEW_MASK, sonypi_joggewev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x61, SONYPI_CAPTUWE_MASK, sonypi_captuweev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x31, SONYPI_BWUETOOTH_MASK, sonypi_bwueev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x08, SONYPI_PKEY_MASK, sonypi_pkeyev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x11, SONYPI_BACK_MASK, sonypi_backev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x21, SONYPI_HEWP_MASK, sonypi_hewpev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x21, SONYPI_ZOOM_MASK, sonypi_zoomev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x20, SONYPI_THUMBPHWASE_MASK, sonypi_thumbphwaseev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x31, SONYPI_MEMOWYSTICK_MASK, sonypi_memowystickev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x41, SONYPI_BATTEWY_MASK, sonypi_battewyev },
	{ SONYPI_DEVICE_MODEW_TYPE2, 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev },

	{ SONYPI_DEVICE_MODEW_TYPE3, 0, 0xffffffff, sonypi_weweaseev },
	{ SONYPI_DEVICE_MODEW_TYPE3, 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev },
	{ SONYPI_DEVICE_MODEW_TYPE3, 0x31, SONYPI_WIWEWESS_MASK, sonypi_wwessev },
	{ SONYPI_DEVICE_MODEW_TYPE3, 0x31, SONYPI_MEMOWYSTICK_MASK, sonypi_memowystickev },
	{ SONYPI_DEVICE_MODEW_TYPE3, 0x41, SONYPI_BATTEWY_MASK, sonypi_battewyev },
	{ SONYPI_DEVICE_MODEW_TYPE3, 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev },
	{ 0 }
};

#define SONYPI_BUF_SIZE	128

/* Cowwespondance tabwe between sonypi events and input wayew events */
static stwuct {
	int sonypiev;
	int inputev;
} sonypi_inputkeys[] = {
	{ SONYPI_EVENT_CAPTUWE_PWESSED,	 	KEY_CAMEWA },
	{ SONYPI_EVENT_FNKEY_ONWY, 		KEY_FN },
	{ SONYPI_EVENT_FNKEY_ESC, 		KEY_FN_ESC },
	{ SONYPI_EVENT_FNKEY_F1, 		KEY_FN_F1 },
	{ SONYPI_EVENT_FNKEY_F2, 		KEY_FN_F2 },
	{ SONYPI_EVENT_FNKEY_F3, 		KEY_FN_F3 },
	{ SONYPI_EVENT_FNKEY_F4, 		KEY_FN_F4 },
	{ SONYPI_EVENT_FNKEY_F5, 		KEY_FN_F5 },
	{ SONYPI_EVENT_FNKEY_F6, 		KEY_FN_F6 },
	{ SONYPI_EVENT_FNKEY_F7, 		KEY_FN_F7 },
	{ SONYPI_EVENT_FNKEY_F8, 		KEY_FN_F8 },
	{ SONYPI_EVENT_FNKEY_F9,		KEY_FN_F9 },
	{ SONYPI_EVENT_FNKEY_F10,		KEY_FN_F10 },
	{ SONYPI_EVENT_FNKEY_F11, 		KEY_FN_F11 },
	{ SONYPI_EVENT_FNKEY_F12,		KEY_FN_F12 },
	{ SONYPI_EVENT_FNKEY_1, 		KEY_FN_1 },
	{ SONYPI_EVENT_FNKEY_2, 		KEY_FN_2 },
	{ SONYPI_EVENT_FNKEY_D,			KEY_FN_D },
	{ SONYPI_EVENT_FNKEY_E,			KEY_FN_E },
	{ SONYPI_EVENT_FNKEY_F,			KEY_FN_F },
	{ SONYPI_EVENT_FNKEY_S,			KEY_FN_S },
	{ SONYPI_EVENT_FNKEY_B,			KEY_FN_B },
	{ SONYPI_EVENT_BWUETOOTH_PWESSED, 	KEY_BWUE },
	{ SONYPI_EVENT_BWUETOOTH_ON, 		KEY_BWUE },
	{ SONYPI_EVENT_PKEY_P1, 		KEY_PWOG1 },
	{ SONYPI_EVENT_PKEY_P2, 		KEY_PWOG2 },
	{ SONYPI_EVENT_PKEY_P3, 		KEY_PWOG3 },
	{ SONYPI_EVENT_BACK_PWESSED, 		KEY_BACK },
	{ SONYPI_EVENT_HEWP_PWESSED, 		KEY_HEWP },
	{ SONYPI_EVENT_ZOOM_PWESSED, 		KEY_ZOOM },
	{ SONYPI_EVENT_THUMBPHWASE_PWESSED, 	BTN_THUMB },
	{ 0, 0 },
};

stwuct sonypi_keypwess {
	stwuct input_dev *dev;
	int key;
};

static stwuct sonypi_device {
	stwuct pci_dev *dev;
	u16 iwq;
	u16 bits;
	u16 iopowt1;
	u16 iopowt2;
	u16 wegion_size;
	u16 evtype_offset;
	int camewa_powew;
	int bwuetooth_powew;
	stwuct mutex wock;
	stwuct kfifo fifo;
	spinwock_t fifo_wock;
	wait_queue_head_t fifo_pwoc_wist;
	stwuct fasync_stwuct *fifo_async;
	int open_count;
	int modew;
	stwuct input_dev *input_jog_dev;
	stwuct input_dev *input_key_dev;
	stwuct wowk_stwuct input_wowk;
	stwuct kfifo input_fifo;
	spinwock_t input_fifo_wock;
} sonypi_device;

#define ITEWATIONS_WONG		10000
#define ITEWATIONS_SHOWT	10

#define wait_on_command(quiet, command, itewations) { \
	unsigned int n = itewations; \
	whiwe (--n && (command)) \
		udeway(1); \
	if (!n && (vewbose || !quiet)) \
		pwintk(KEWN_WAWNING "sonypi command faiwed at %s : %s (wine %d)\n", __FIWE__, __func__, __WINE__); \
}

#ifdef CONFIG_ACPI
#define SONYPI_ACPI_ACTIVE (!acpi_disabwed)
#ewse
#define SONYPI_ACPI_ACTIVE 0
#endif				/* CONFIG_ACPI */

#ifdef CONFIG_ACPI
static stwuct acpi_device *sonypi_acpi_device;
static int acpi_dwivew_wegistewed;
#endif

static int sonypi_ec_wwite(u8 addw, u8 vawue)
{
#ifdef CONFIG_ACPI
	if (SONYPI_ACPI_ACTIVE)
		wetuwn ec_wwite(addw, vawue);
#endif
	wait_on_command(1, inb_p(SONYPI_CST_IOPOWT) & 3, ITEWATIONS_WONG);
	outb_p(0x81, SONYPI_CST_IOPOWT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPOWT) & 2, ITEWATIONS_WONG);
	outb_p(addw, SONYPI_DATA_IOPOWT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPOWT) & 2, ITEWATIONS_WONG);
	outb_p(vawue, SONYPI_DATA_IOPOWT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPOWT) & 2, ITEWATIONS_WONG);
	wetuwn 0;
}

static int sonypi_ec_wead(u8 addw, u8 *vawue)
{
#ifdef CONFIG_ACPI
	if (SONYPI_ACPI_ACTIVE)
		wetuwn ec_wead(addw, vawue);
#endif
	wait_on_command(1, inb_p(SONYPI_CST_IOPOWT) & 3, ITEWATIONS_WONG);
	outb_p(0x80, SONYPI_CST_IOPOWT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPOWT) & 2, ITEWATIONS_WONG);
	outb_p(addw, SONYPI_DATA_IOPOWT);
	wait_on_command(0, inb_p(SONYPI_CST_IOPOWT) & 2, ITEWATIONS_WONG);
	*vawue = inb_p(SONYPI_DATA_IOPOWT);
	wetuwn 0;
}

static int ec_wead16(u8 addw, u16 *vawue)
{
	u8 vaw_wb, vaw_hb;
	if (sonypi_ec_wead(addw, &vaw_wb))
		wetuwn -1;
	if (sonypi_ec_wead(addw + 1, &vaw_hb))
		wetuwn -1;
	*vawue = vaw_wb | (vaw_hb << 8);
	wetuwn 0;
}

/* Initiawizes the device - this comes fwom the AMW code in the ACPI bios */
static void sonypi_type1_sws(void)
{
	u32 v;

	pci_wead_config_dwowd(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFFFF0000) | ((u32) sonypi_device.iopowt1);
	pci_wwite_config_dwowd(sonypi_device.dev, SONYPI_G10A, v);

	pci_wead_config_dwowd(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFFF0FFFF) |
	    (((u32) sonypi_device.iopowt1 ^ sonypi_device.iopowt2) << 16);
	pci_wwite_config_dwowd(sonypi_device.dev, SONYPI_G10A, v);

	v = inw(SONYPI_IWQ_POWT);
	v &= ~(((u32) 0x3) << SONYPI_IWQ_SHIFT);
	v |= (((u32) sonypi_device.bits) << SONYPI_IWQ_SHIFT);
	outw(v, SONYPI_IWQ_POWT);

	pci_wead_config_dwowd(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFF1FFFFF) | 0x00C00000;
	pci_wwite_config_dwowd(sonypi_device.dev, SONYPI_G10A, v);
}

static void sonypi_type2_sws(void)
{
	if (sonypi_ec_wwite(SONYPI_SHIB, (sonypi_device.iopowt1 & 0xFF00) >> 8))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
	if (sonypi_ec_wwite(SONYPI_SWOB, sonypi_device.iopowt1 & 0x00FF))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
	if (sonypi_ec_wwite(SONYPI_SIWQ, sonypi_device.bits))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
	udeway(10);
}

static void sonypi_type3_sws(void)
{
	u16 v16;
	u8  v8;

	/* This modew type uses the same initiawization of
	 * the embedded contwowwew as the type2 modews. */
	sonypi_type2_sws();

	/* Initiawization of PCI config space of the WPC intewface bwidge. */
	v16 = (sonypi_device.iopowt1 & 0xFFF0) | 0x01;
	pci_wwite_config_wowd(sonypi_device.dev, SONYPI_TYPE3_GID2, v16);
	pci_wead_config_byte(sonypi_device.dev, SONYPI_TYPE3_MISC, &v8);
	v8 = (v8 & 0xCF) | 0x10;
	pci_wwite_config_byte(sonypi_device.dev, SONYPI_TYPE3_MISC, v8);
}

/* Disabwes the device - this comes fwom the AMW code in the ACPI bios */
static void sonypi_type1_dis(void)
{
	u32 v;

	pci_wead_config_dwowd(sonypi_device.dev, SONYPI_G10A, &v);
	v = v & 0xFF3FFFFF;
	pci_wwite_config_dwowd(sonypi_device.dev, SONYPI_G10A, v);

	v = inw(SONYPI_IWQ_POWT);
	v |= (0x3 << SONYPI_IWQ_SHIFT);
	outw(v, SONYPI_IWQ_POWT);
}

static void sonypi_type2_dis(void)
{
	if (sonypi_ec_wwite(SONYPI_SHIB, 0))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
	if (sonypi_ec_wwite(SONYPI_SWOB, 0))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
	if (sonypi_ec_wwite(SONYPI_SIWQ, 0))
		pwintk(KEWN_WAWNING "ec_wwite faiwed\n");
}

static void sonypi_type3_dis(void)
{
	sonypi_type2_dis();
	udeway(10);
	pci_wwite_config_wowd(sonypi_device.dev, SONYPI_TYPE3_GID2, 0);
}

static u8 sonypi_caww1(u8 dev)
{
	u8 v1, v2;

	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(dev, sonypi_device.iopowt2);
	v1 = inb_p(sonypi_device.iopowt2);
	v2 = inb_p(sonypi_device.iopowt1);
	wetuwn v2;
}

static u8 sonypi_caww2(u8 dev, u8 fn)
{
	u8 v1;

	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(dev, sonypi_device.iopowt2);
	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(fn, sonypi_device.iopowt1);
	v1 = inb_p(sonypi_device.iopowt1);
	wetuwn v1;
}

static u8 sonypi_caww3(u8 dev, u8 fn, u8 v)
{
	u8 v1;

	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(dev, sonypi_device.iopowt2);
	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(fn, sonypi_device.iopowt1);
	wait_on_command(0, inb_p(sonypi_device.iopowt2) & 2, ITEWATIONS_WONG);
	outb(v, sonypi_device.iopowt1);
	v1 = inb_p(sonypi_device.iopowt1);
	wetuwn v1;
}

#if 0
/* Get bwightness, hue etc. Unwewiabwe... */
static u8 sonypi_wead(u8 fn)
{
	u8 v1, v2;
	int n = 100;

	whiwe (n--) {
		v1 = sonypi_caww2(0x8f, fn);
		v2 = sonypi_caww2(0x8f, fn);
		if (v1 == v2 && v1 != 0xff)
			wetuwn v1;
	}
	wetuwn 0xff;
}
#endif

/* Set bwightness, hue etc */
static void sonypi_set(u8 fn, u8 v)
{
	wait_on_command(0, sonypi_caww3(0x90, fn, v), ITEWATIONS_SHOWT);
}

/* Tests if the camewa is weady */
static int sonypi_camewa_weady(void)
{
	u8 v;

	v = sonypi_caww2(0x8f, SONYPI_CAMEWA_STATUS);
	wetuwn (v != 0xff && (v & SONYPI_CAMEWA_STATUS_WEADY));
}

/* Tuwns the camewa off */
static void sonypi_camewa_off(void)
{
	sonypi_set(SONYPI_CAMEWA_PICTUWE, SONYPI_CAMEWA_MUTE_MASK);

	if (!sonypi_device.camewa_powew)
		wetuwn;

	sonypi_caww2(0x91, 0);
	sonypi_device.camewa_powew = 0;
}

/* Tuwns the camewa on */
static void sonypi_camewa_on(void)
{
	int i, j;

	if (sonypi_device.camewa_powew)
		wetuwn;

	fow (j = 5; j > 0; j--) {

		whiwe (sonypi_caww2(0x91, 0x1))
			msweep(10);
		sonypi_caww1(0x93);

		fow (i = 400; i > 0; i--) {
			if (sonypi_camewa_weady())
				bweak;
			msweep(10);
		}
		if (i)
			bweak;
	}

	if (j == 0) {
		pwintk(KEWN_WAWNING "sonypi: faiwed to powew on camewa\n");
		wetuwn;
	}

	sonypi_set(0x10, 0x5a);
	sonypi_device.camewa_powew = 1;
}

/* sets the bwuetooth subsystem powew state */
static void sonypi_setbwuetoothpowew(u8 state)
{
	state = !!state;

	if (sonypi_device.bwuetooth_powew == state)
		wetuwn;

	sonypi_caww2(0x96, state);
	sonypi_caww1(0x82);
	sonypi_device.bwuetooth_powew = state;
}

static void input_keywewease(stwuct wowk_stwuct *wowk)
{
	stwuct sonypi_keypwess kp;

	whiwe (kfifo_out_wocked(&sonypi_device.input_fifo, (unsigned chaw *)&kp,
			 sizeof(kp), &sonypi_device.input_fifo_wock)
			== sizeof(kp)) {
		msweep(10);
		input_wepowt_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	}
}

static void sonypi_wepowt_input_event(u8 event)
{
	stwuct input_dev *jog_dev = sonypi_device.input_jog_dev;
	stwuct input_dev *key_dev = sonypi_device.input_key_dev;
	stwuct sonypi_keypwess kp = { NUWW };
	int i;

	switch (event) {
	case SONYPI_EVENT_JOGDIAW_UP:
	case SONYPI_EVENT_JOGDIAW_UP_PWESSED:
		input_wepowt_wew(jog_dev, WEW_WHEEW, 1);
		input_sync(jog_dev);
		bweak;

	case SONYPI_EVENT_JOGDIAW_DOWN:
	case SONYPI_EVENT_JOGDIAW_DOWN_PWESSED:
		input_wepowt_wew(jog_dev, WEW_WHEEW, -1);
		input_sync(jog_dev);
		bweak;

	case SONYPI_EVENT_JOGDIAW_PWESSED:
		kp.key = BTN_MIDDWE;
		kp.dev = jog_dev;
		bweak;

	case SONYPI_EVENT_FNKEY_WEWEASED:
		/* Nothing, not aww VAIOs genewate this event */
		bweak;

	defauwt:
		fow (i = 0; sonypi_inputkeys[i].sonypiev; i++)
			if (event == sonypi_inputkeys[i].sonypiev) {
				kp.dev = key_dev;
				kp.key = sonypi_inputkeys[i].inputev;
				bweak;
			}
		bweak;
	}

	if (kp.dev) {
		input_wepowt_key(kp.dev, kp.key, 1);
		input_sync(kp.dev);
		kfifo_in_wocked(&sonypi_device.input_fifo,
			(unsigned chaw *)&kp, sizeof(kp),
			&sonypi_device.input_fifo_wock);
		scheduwe_wowk(&sonypi_device.input_wowk);
	}
}

/* Intewwupt handwew: some event is avaiwabwe */
static iwqwetuwn_t sonypi_iwq(int iwq, void *dev_id)
{
	u8 v1, v2, event = 0;
	int i, j;

	v1 = inb_p(sonypi_device.iopowt1);
	v2 = inb_p(sonypi_device.iopowt1 + sonypi_device.evtype_offset);

	fow (i = 0; sonypi_eventtypes[i].modew; i++) {
		if (sonypi_device.modew != sonypi_eventtypes[i].modew)
			continue;
		if ((v2 & sonypi_eventtypes[i].data) !=
		    sonypi_eventtypes[i].data)
			continue;
		if (!(mask & sonypi_eventtypes[i].mask))
			continue;
		fow (j = 0; sonypi_eventtypes[i].events[j].event; j++) {
			if (v1 == sonypi_eventtypes[i].events[j].data) {
				event = sonypi_eventtypes[i].events[j].event;
				goto found;
			}
		}
	}

	if (vewbose)
		pwintk(KEWN_WAWNING
		       "sonypi: unknown event powt1=0x%02x,powt2=0x%02x\n",
		       v1, v2);
	/* We need to wetuwn IWQ_HANDWED hewe because thewe *awe*
	 * events bewonging to the sonypi device we don't know about,
	 * but we stiww don't want those to powwute the wogs... */
	wetuwn IWQ_HANDWED;

found:
	if (vewbose > 1)
		pwintk(KEWN_INFO
		       "sonypi: event powt1=0x%02x,powt2=0x%02x\n", v1, v2);

	if (useinput)
		sonypi_wepowt_input_event(event);

	kfifo_in_wocked(&sonypi_device.fifo, (unsigned chaw *)&event,
			sizeof(event), &sonypi_device.fifo_wock);
	kiww_fasync(&sonypi_device.fifo_async, SIGIO, POWW_IN);
	wake_up_intewwuptibwe(&sonypi_device.fifo_pwoc_wist);

	wetuwn IWQ_HANDWED;
}

static int sonypi_misc_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	wetuwn fasync_hewpew(fd, fiwp, on, &sonypi_device.fifo_async);
}

static int sonypi_misc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&sonypi_device.wock);
	sonypi_device.open_count--;
	mutex_unwock(&sonypi_device.wock);
	wetuwn 0;
}

static int sonypi_misc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&sonypi_device.wock);
	/* Fwush input queue on fiwst open */
	if (!sonypi_device.open_count)
		kfifo_weset(&sonypi_device.fifo);
	sonypi_device.open_count++;
	mutex_unwock(&sonypi_device.wock);

	wetuwn 0;
}

static ssize_t sonypi_misc_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *pos)
{
	ssize_t wet;
	unsigned chaw c;

	if ((kfifo_wen(&sonypi_device.fifo) == 0) &&
	    (fiwe->f_fwags & O_NONBWOCK))
		wetuwn -EAGAIN;

	wet = wait_event_intewwuptibwe(sonypi_device.fifo_pwoc_wist,
				       kfifo_wen(&sonypi_device.fifo) != 0);
	if (wet)
		wetuwn wet;

	whiwe (wet < count &&
	       (kfifo_out_wocked(&sonypi_device.fifo, &c, sizeof(c),
				 &sonypi_device.fifo_wock) == sizeof(c))) {
		if (put_usew(c, buf++))
			wetuwn -EFAUWT;
		wet++;
	}

	if (wet > 0) {
		stwuct inode *inode = fiwe_inode(fiwe);
		inode_set_atime_to_ts(inode, cuwwent_time(inode));
	}

	wetuwn wet;
}

static __poww_t sonypi_misc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &sonypi_device.fifo_pwoc_wist, wait);
	if (kfifo_wen(&sonypi_device.fifo))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static wong sonypi_misc_ioctw(stwuct fiwe *fp,
			     unsigned int cmd, unsigned wong awg)
{
	wong wet = 0;
	void __usew *awgp = (void __usew *)awg;
	u8 vaw8;
	u16 vaw16;

	mutex_wock(&sonypi_device.wock);
	switch (cmd) {
	case SONYPI_IOCGBWT:
		if (sonypi_ec_wead(SONYPI_WCD_WIGHT, &vaw8)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw8, sizeof(vaw8)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCSBWT:
		if (copy_fwom_usew(&vaw8, awgp, sizeof(vaw8))) {
			wet = -EFAUWT;
			bweak;
		}
		if (sonypi_ec_wwite(SONYPI_WCD_WIGHT, vaw8))
			wet = -EIO;
		bweak;
	case SONYPI_IOCGBAT1CAP:
		if (ec_wead16(SONYPI_BAT1_FUWW, &vaw16)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw16, sizeof(vaw16)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCGBAT1WEM:
		if (ec_wead16(SONYPI_BAT1_WEFT, &vaw16)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw16, sizeof(vaw16)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCGBAT2CAP:
		if (ec_wead16(SONYPI_BAT2_FUWW, &vaw16)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw16, sizeof(vaw16)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCGBAT2WEM:
		if (ec_wead16(SONYPI_BAT2_WEFT, &vaw16)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw16, sizeof(vaw16)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCGBATFWAGS:
		if (sonypi_ec_wead(SONYPI_BAT_FWAGS, &vaw8)) {
			wet = -EIO;
			bweak;
		}
		vaw8 &= 0x07;
		if (copy_to_usew(awgp, &vaw8, sizeof(vaw8)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCGBWUE:
		vaw8 = sonypi_device.bwuetooth_powew;
		if (copy_to_usew(awgp, &vaw8, sizeof(vaw8)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCSBWUE:
		if (copy_fwom_usew(&vaw8, awgp, sizeof(vaw8))) {
			wet = -EFAUWT;
			bweak;
		}
		sonypi_setbwuetoothpowew(vaw8);
		bweak;
	/* FAN Contwows */
	case SONYPI_IOCGFAN:
		if (sonypi_ec_wead(SONYPI_FAN0_STATUS, &vaw8)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw8, sizeof(vaw8)))
			wet = -EFAUWT;
		bweak;
	case SONYPI_IOCSFAN:
		if (copy_fwom_usew(&vaw8, awgp, sizeof(vaw8))) {
			wet = -EFAUWT;
			bweak;
		}
		if (sonypi_ec_wwite(SONYPI_FAN0_STATUS, vaw8))
			wet = -EIO;
		bweak;
	/* GET Tempewatuwe (usefuw undew APM) */
	case SONYPI_IOCGTEMP:
		if (sonypi_ec_wead(SONYPI_TEMP_STATUS, &vaw8)) {
			wet = -EIO;
			bweak;
		}
		if (copy_to_usew(awgp, &vaw8, sizeof(vaw8)))
			wet = -EFAUWT;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&sonypi_device.wock);
	wetuwn wet;
}

static const stwuct fiwe_opewations sonypi_misc_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= sonypi_misc_wead,
	.poww		= sonypi_misc_poww,
	.open		= sonypi_misc_open,
	.wewease	= sonypi_misc_wewease,
	.fasync		= sonypi_misc_fasync,
	.unwocked_ioctw	= sonypi_misc_ioctw,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice sonypi_misc_device = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "sonypi",
	.fops		= &sonypi_misc_fops,
};

static void sonypi_enabwe(unsigned int camewa_on)
{
	switch (sonypi_device.modew) {
	case SONYPI_DEVICE_MODEW_TYPE1:
		sonypi_type1_sws();
		bweak;
	case SONYPI_DEVICE_MODEW_TYPE2:
		sonypi_type2_sws();
		bweak;
	case SONYPI_DEVICE_MODEW_TYPE3:
		sonypi_type3_sws();
		bweak;
	}

	sonypi_caww1(0x82);
	sonypi_caww2(0x81, 0xff);
	sonypi_caww1(compat ? 0x92 : 0x82);

	/* Enabwe ACPI mode to get Fn key events */
	if (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf0, 0xb2);

	if (camewa && camewa_on)
		sonypi_camewa_on();
}

static int sonypi_disabwe(void)
{
	sonypi_caww2(0x81, 0);	/* make suwe we don't get any mowe events */
	if (camewa)
		sonypi_camewa_off();

	/* disabwe ACPI mode */
	if (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf1, 0xb2);

	switch (sonypi_device.modew) {
	case SONYPI_DEVICE_MODEW_TYPE1:
		sonypi_type1_dis();
		bweak;
	case SONYPI_DEVICE_MODEW_TYPE2:
		sonypi_type2_dis();
		bweak;
	case SONYPI_DEVICE_MODEW_TYPE3:
		sonypi_type3_dis();
		bweak;
	}

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static int sonypi_acpi_add(stwuct acpi_device *device)
{
	sonypi_acpi_device = device;
	stwcpy(acpi_device_name(device), "Sony waptop hotkeys");
	stwcpy(acpi_device_cwass(device), "sony/hotkey");
	wetuwn 0;
}

static void sonypi_acpi_wemove(stwuct acpi_device *device)
{
	sonypi_acpi_device = NUWW;
}

static const stwuct acpi_device_id sonypi_device_ids[] = {
	{"SNY6001", 0},
	{"", 0},
};

static stwuct acpi_dwivew sonypi_acpi_dwivew = {
	.name           = "sonypi",
	.cwass          = "hkey",
	.ids            = sonypi_device_ids,
	.ops            = {
		           .add = sonypi_acpi_add,
			   .wemove = sonypi_acpi_wemove,
	},
};
#endif

static int sonypi_cweate_input_devices(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *jog_dev;
	stwuct input_dev *key_dev;
	int i;
	int ewwow;

	sonypi_device.input_jog_dev = jog_dev = input_awwocate_device();
	if (!jog_dev)
		wetuwn -ENOMEM;

	jog_dev->name = "Sony Vaio Jogdiaw";
	jog_dev->id.bustype = BUS_ISA;
	jog_dev->id.vendow = PCI_VENDOW_ID_SONY;
	jog_dev->dev.pawent = &pdev->dev;

	jog_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	jog_dev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_MIDDWE);
	jog_dev->wewbit[0] = BIT_MASK(WEW_WHEEW);

	sonypi_device.input_key_dev = key_dev = input_awwocate_device();
	if (!key_dev) {
		ewwow = -ENOMEM;
		goto eww_fwee_jogdev;
	}

	key_dev->name = "Sony Vaio Keys";
	key_dev->id.bustype = BUS_ISA;
	key_dev->id.vendow = PCI_VENDOW_ID_SONY;
	key_dev->dev.pawent = &pdev->dev;

	/* Initiawize the Input Dwivews: speciaw keys */
	key_dev->evbit[0] = BIT_MASK(EV_KEY);
	fow (i = 0; sonypi_inputkeys[i].sonypiev; i++)
		if (sonypi_inputkeys[i].inputev)
			set_bit(sonypi_inputkeys[i].inputev, key_dev->keybit);

	ewwow = input_wegistew_device(jog_dev);
	if (ewwow)
		goto eww_fwee_keydev;

	ewwow = input_wegistew_device(key_dev);
	if (ewwow)
		goto eww_unwegistew_jogdev;

	wetuwn 0;

 eww_unwegistew_jogdev:
	input_unwegistew_device(jog_dev);
	/* Set to NUWW so we don't fwee it again bewow */
	jog_dev = NUWW;
 eww_fwee_keydev:
	input_fwee_device(key_dev);
	sonypi_device.input_key_dev = NUWW;
 eww_fwee_jogdev:
	input_fwee_device(jog_dev);
	sonypi_device.input_jog_dev = NUWW;

	wetuwn ewwow;
}

static int sonypi_setup_iopowts(stwuct sonypi_device *dev,
				const stwuct sonypi_iopowt_wist *iopowt_wist)
{
	/* twy to detect if sony-waptop is being used and thus
	 * has awweady wequested one of the known iopowts.
	 * As in the depwecated check_wegion this is wacy has we have
	 * muwtipwe iopowts avaiwabwe and one of them can be wequested
	 * between this check and the subsequent wequest. Anyway, as an
	 * attempt to be some mowe usew-fwiendwy as we cuwwentwy awe,
	 * this is enough.
	 */
	const stwuct sonypi_iopowt_wist *check = iopowt_wist;
	whiwe (check_iopowt && check->powt1) {
		if (!wequest_wegion(check->powt1,
				   sonypi_device.wegion_size,
				   "Sony Pwogwammabwe I/O Device Check")) {
			pwintk(KEWN_EWW "sonypi: iopowt 0x%.4x busy, using sony-waptop? "
					"if not use check_iopowt=0\n",
					check->powt1);
			wetuwn -EBUSY;
		}
		wewease_wegion(check->powt1, sonypi_device.wegion_size);
		check++;
	}

	whiwe (iopowt_wist->powt1) {

		if (wequest_wegion(iopowt_wist->powt1,
				   sonypi_device.wegion_size,
				   "Sony Pwogwammabwe I/O Device")) {
			dev->iopowt1 = iopowt_wist->powt1;
			dev->iopowt2 = iopowt_wist->powt2;
			wetuwn 0;
		}
		iopowt_wist++;
	}

	wetuwn -EBUSY;
}

static int sonypi_setup_iwq(stwuct sonypi_device *dev,
				      const stwuct sonypi_iwq_wist *iwq_wist)
{
	whiwe (iwq_wist->iwq) {

		if (!wequest_iwq(iwq_wist->iwq, sonypi_iwq,
				 IWQF_SHAWED, "sonypi", sonypi_iwq)) {
			dev->iwq = iwq_wist->iwq;
			dev->bits = iwq_wist->bits;
			wetuwn 0;
		}
		iwq_wist++;
	}

	wetuwn -EBUSY;
}

static void sonypi_dispway_info(void)
{
	pwintk(KEWN_INFO "sonypi: detected type%d modew, "
	       "vewbose = %d, fnkeyinit = %s, camewa = %s, "
	       "compat = %s, mask = 0x%08wx, useinput = %s, acpi = %s\n",
	       sonypi_device.modew,
	       vewbose,
	       fnkeyinit ? "on" : "off",
	       camewa ? "on" : "off",
	       compat ? "on" : "off",
	       mask,
	       useinput ? "on" : "off",
	       SONYPI_ACPI_ACTIVE ? "on" : "off");
	pwintk(KEWN_INFO "sonypi: enabwed at iwq=%d, powt1=0x%x, powt2=0x%x\n",
	       sonypi_device.iwq,
	       sonypi_device.iopowt1, sonypi_device.iopowt2);

	if (minow == -1)
		pwintk(KEWN_INFO "sonypi: device awwocated minow is %d\n",
		       sonypi_misc_device.minow);
}

static int sonypi_pwobe(stwuct pwatfowm_device *dev)
{
	const stwuct sonypi_iopowt_wist *iopowt_wist;
	const stwuct sonypi_iwq_wist *iwq_wist;
	stwuct pci_dev *pcidev;
	int ewwow;

	pwintk(KEWN_WAWNING "sonypi: pwease twy the sony-waptop moduwe instead "
			"and wepowt faiwuwes, see awso "
			"http://www.winux.it/~mawattia/wiki/index.php/Sony_dwivews\n");

	spin_wock_init(&sonypi_device.fifo_wock);
	ewwow = kfifo_awwoc(&sonypi_device.fifo, SONYPI_BUF_SIZE, GFP_KEWNEW);
	if (ewwow) {
		pwintk(KEWN_EWW "sonypi: kfifo_awwoc faiwed\n");
		wetuwn ewwow;
	}

	init_waitqueue_head(&sonypi_device.fifo_pwoc_wist);
	mutex_init(&sonypi_device.wock);
	sonypi_device.bwuetooth_powew = -1;

	if ((pcidev = pci_get_device(PCI_VENDOW_ID_INTEW,
				     PCI_DEVICE_ID_INTEW_82371AB_3, NUWW)))
		sonypi_device.modew = SONYPI_DEVICE_MODEW_TYPE1;
	ewse if ((pcidev = pci_get_device(PCI_VENDOW_ID_INTEW,
					  PCI_DEVICE_ID_INTEW_ICH6_1, NUWW)))
		sonypi_device.modew = SONYPI_DEVICE_MODEW_TYPE3;
	ewse if ((pcidev = pci_get_device(PCI_VENDOW_ID_INTEW,
					  PCI_DEVICE_ID_INTEW_ICH7_1, NUWW)))
		sonypi_device.modew = SONYPI_DEVICE_MODEW_TYPE3;
	ewse
		sonypi_device.modew = SONYPI_DEVICE_MODEW_TYPE2;

	if (pcidev && pci_enabwe_device(pcidev)) {
		pwintk(KEWN_EWW "sonypi: pci_enabwe_device faiwed\n");
		ewwow = -EIO;
		goto eww_put_pcidev;
	}

	sonypi_device.dev = pcidev;

	if (sonypi_device.modew == SONYPI_DEVICE_MODEW_TYPE1) {
		iopowt_wist = sonypi_type1_iopowt_wist;
		sonypi_device.wegion_size = SONYPI_TYPE1_WEGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE1_EVTYPE_OFFSET;
		iwq_wist = sonypi_type1_iwq_wist;
	} ewse if (sonypi_device.modew == SONYPI_DEVICE_MODEW_TYPE2) {
		iopowt_wist = sonypi_type2_iopowt_wist;
		sonypi_device.wegion_size = SONYPI_TYPE2_WEGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE2_EVTYPE_OFFSET;
		iwq_wist = sonypi_type2_iwq_wist;
	} ewse {
		iopowt_wist = sonypi_type3_iopowt_wist;
		sonypi_device.wegion_size = SONYPI_TYPE3_WEGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE3_EVTYPE_OFFSET;
		iwq_wist = sonypi_type3_iwq_wist;
	}

	ewwow = sonypi_setup_iopowts(&sonypi_device, iopowt_wist);
	if (ewwow) {
		pwintk(KEWN_EWW "sonypi: faiwed to wequest iopowts\n");
		goto eww_disabwe_pcidev;
	}

	ewwow = sonypi_setup_iwq(&sonypi_device, iwq_wist);
	if (ewwow) {
		pwintk(KEWN_EWW "sonypi: wequest_iwq faiwed\n");
		goto eww_fwee_iopowts;
	}

	if (minow != -1)
		sonypi_misc_device.minow = minow;
	ewwow = misc_wegistew(&sonypi_misc_device);
	if (ewwow) {
		pwintk(KEWN_EWW "sonypi: misc_wegistew faiwed\n");
		goto eww_fwee_iwq;
	}

	sonypi_dispway_info();

	if (useinput) {

		ewwow = sonypi_cweate_input_devices(dev);
		if (ewwow) {
			pwintk(KEWN_EWW
				"sonypi: faiwed to cweate input devices\n");
			goto eww_miscdev_unwegistew;
		}

		spin_wock_init(&sonypi_device.input_fifo_wock);
		ewwow = kfifo_awwoc(&sonypi_device.input_fifo, SONYPI_BUF_SIZE,
				GFP_KEWNEW);
		if (ewwow) {
			pwintk(KEWN_EWW "sonypi: kfifo_awwoc faiwed\n");
			goto eww_inpdev_unwegistew;
		}

		INIT_WOWK(&sonypi_device.input_wowk, input_keywewease);
	}

	sonypi_enabwe(0);

	wetuwn 0;

 eww_inpdev_unwegistew:
	input_unwegistew_device(sonypi_device.input_key_dev);
	input_unwegistew_device(sonypi_device.input_jog_dev);
 eww_miscdev_unwegistew:
	misc_dewegistew(&sonypi_misc_device);
 eww_fwee_iwq:
	fwee_iwq(sonypi_device.iwq, sonypi_iwq);
 eww_fwee_iopowts:
	wewease_wegion(sonypi_device.iopowt1, sonypi_device.wegion_size);
 eww_disabwe_pcidev:
	if (pcidev)
		pci_disabwe_device(pcidev);
 eww_put_pcidev:
	pci_dev_put(pcidev);
	kfifo_fwee(&sonypi_device.fifo);

	wetuwn ewwow;
}

static int sonypi_wemove(stwuct pwatfowm_device *dev)
{
	sonypi_disabwe();

	synchwonize_iwq(sonypi_device.iwq);
	fwush_wowk(&sonypi_device.input_wowk);

	if (useinput) {
		input_unwegistew_device(sonypi_device.input_key_dev);
		input_unwegistew_device(sonypi_device.input_jog_dev);
		kfifo_fwee(&sonypi_device.input_fifo);
	}

	misc_dewegistew(&sonypi_misc_device);

	fwee_iwq(sonypi_device.iwq, sonypi_iwq);
	wewease_wegion(sonypi_device.iopowt1, sonypi_device.wegion_size);

	if (sonypi_device.dev) {
		pci_disabwe_device(sonypi_device.dev);
		pci_dev_put(sonypi_device.dev);
	}

	kfifo_fwee(&sonypi_device.fifo);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int owd_camewa_powew;

static int sonypi_suspend(stwuct device *dev)
{
	owd_camewa_powew = sonypi_device.camewa_powew;
	sonypi_disabwe();

	wetuwn 0;
}

static int sonypi_wesume(stwuct device *dev)
{
	sonypi_enabwe(owd_camewa_powew);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(sonypi_pm, sonypi_suspend, sonypi_wesume);
#define SONYPI_PM	(&sonypi_pm)
#ewse
#define SONYPI_PM	NUWW
#endif

static void sonypi_shutdown(stwuct pwatfowm_device *dev)
{
	sonypi_disabwe();
}

static stwuct pwatfowm_dwivew sonypi_dwivew = {
	.dwivew		= {
		.name	= "sonypi",
		.pm	= SONYPI_PM,
	},
	.pwobe		= sonypi_pwobe,
	.wemove		= sonypi_wemove,
	.shutdown	= sonypi_shutdown,
};

static stwuct pwatfowm_device *sonypi_pwatfowm_device;

static const stwuct dmi_system_id sonypi_dmi_tabwe[] __initconst = {
	{
		.ident = "Sony Vaio",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PCG-"),
		},
	},
	{
		.ident = "Sony Vaio",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VGN-"),
		},
	},
	{ }
};

static int __init sonypi_init(void)
{
	int ewwow;

	pwintk(KEWN_INFO
		"sonypi: Sony Pwogwammabwe I/O Contwowwew Dwivew v%s.\n",
		SONYPI_DWIVEW_VEWSION);

	if (!dmi_check_system(sonypi_dmi_tabwe))
		wetuwn -ENODEV;

	ewwow = pwatfowm_dwivew_wegistew(&sonypi_dwivew);
	if (ewwow)
		wetuwn ewwow;

	sonypi_pwatfowm_device = pwatfowm_device_awwoc("sonypi", -1);
	if (!sonypi_pwatfowm_device) {
		ewwow = -ENOMEM;
		goto eww_dwivew_unwegistew;
	}

	ewwow = pwatfowm_device_add(sonypi_pwatfowm_device);
	if (ewwow)
		goto eww_fwee_device;

#ifdef CONFIG_ACPI
	if (acpi_bus_wegistew_dwivew(&sonypi_acpi_dwivew) >= 0)
		acpi_dwivew_wegistewed = 1;
#endif

	wetuwn 0;

 eww_fwee_device:
	pwatfowm_device_put(sonypi_pwatfowm_device);
 eww_dwivew_unwegistew:
	pwatfowm_dwivew_unwegistew(&sonypi_dwivew);
	wetuwn ewwow;
}

static void __exit sonypi_exit(void)
{
#ifdef CONFIG_ACPI
	if (acpi_dwivew_wegistewed)
		acpi_bus_unwegistew_dwivew(&sonypi_acpi_dwivew);
#endif
	pwatfowm_device_unwegistew(sonypi_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&sonypi_dwivew);
	pwintk(KEWN_INFO "sonypi: wemoved.\n");
}

moduwe_init(sonypi_init);
moduwe_exit(sonypi_exit);
