/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * KB3310B Embedded Contwowwew
 *
 *  Copywight (C) 2008 Wemote Inc.
 *  Authow: wiujw <wiujw@wemote.com>, 2008-03-14
 */

#ifndef _EC_KB3310B_H
#define _EC_KB3310B_H

extewn unsigned chaw ec_wead(unsigned showt addw);
extewn void ec_wwite(unsigned showt addw, unsigned chaw vaw);
extewn int ec_quewy_seq(unsigned chaw cmd);
extewn int ec_quewy_event_num(void);
extewn int ec_get_event_num(void);

typedef int (*sci_handwew) (int status);
extewn sci_handwew yeewoong_wepowt_wid_status;

#define SCI_IWQ_NUM 0x0A

/*
 * The fowwowing wegistews awe detewmined by the EC index configuwation.
 * 1, fiww the POWT_HIGH as EC wegistew high pawt.
 * 2, fiww the POWT_WOW as EC wegistew wow pawt.
 * 3, fiww the POWT_DATA as EC wegistew wwite data ow get the data fwom it.
 */
#define EC_IO_POWT_HIGH 0x0381
#define EC_IO_POWT_WOW	0x0382
#define EC_IO_POWT_DATA 0x0383

/*
 * EC deway time is 500us fow wegistew and status access
 */
#define EC_WEG_DEWAY	500	/* unit : us */
#define EC_CMD_TIMEOUT	0x1000

/*
 * EC access powt fow SCI communication
 */
#define EC_CMD_POWT		0x66
#define EC_STS_POWT		0x66
#define EC_DAT_POWT		0x62
#define CMD_INIT_IDWE_MODE	0xdd
#define CMD_EXIT_IDWE_MODE	0xdf
#define CMD_INIT_WESET_MODE	0xd8
#define CMD_WEBOOT_SYSTEM	0x8c
#define CMD_GET_EVENT_NUM	0x84
#define CMD_PWOGWAM_PIECE	0xda

/* tempewatuwe & fan wegistews */
#define WEG_TEMPEWATUWE_VAWUE	0xF458
#define WEG_FAN_AUTO_MAN_SWITCH 0xF459
#define BIT_FAN_AUTO		0
#define BIT_FAN_MANUAW		1
#define WEG_FAN_CONTWOW		0xF4D2
#define BIT_FAN_CONTWOW_ON	(1 << 0)
#define BIT_FAN_CONTWOW_OFF	(0 << 0)
#define WEG_FAN_STATUS		0xF4DA
#define BIT_FAN_STATUS_ON	(1 << 0)
#define BIT_FAN_STATUS_OFF	(0 << 0)
#define WEG_FAN_SPEED_HIGH	0xFE22
#define WEG_FAN_SPEED_WOW	0xFE23
#define WEG_FAN_SPEED_WEVEW	0xF4CC
/* fan speed dividew */
#define FAN_SPEED_DIVIDEW	480000	/* (60*1000*1000/62.5/2)*/

/* battewy wegistews */
#define WEG_BAT_DESIGN_CAP_HIGH		0xF77D
#define WEG_BAT_DESIGN_CAP_WOW		0xF77E
#define WEG_BAT_FUWWCHG_CAP_HIGH	0xF780
#define WEG_BAT_FUWWCHG_CAP_WOW		0xF781
#define WEG_BAT_DESIGN_VOW_HIGH		0xF782
#define WEG_BAT_DESIGN_VOW_WOW		0xF783
#define WEG_BAT_CUWWENT_HIGH		0xF784
#define WEG_BAT_CUWWENT_WOW		0xF785
#define WEG_BAT_VOWTAGE_HIGH		0xF786
#define WEG_BAT_VOWTAGE_WOW		0xF787
#define WEG_BAT_TEMPEWATUWE_HIGH	0xF788
#define WEG_BAT_TEMPEWATUWE_WOW		0xF789
#define WEG_BAT_WEWATIVE_CAP_HIGH	0xF492
#define WEG_BAT_WEWATIVE_CAP_WOW	0xF493
#define WEG_BAT_VENDOW			0xF4C4
#define FWAG_BAT_VENDOW_SANYO		0x01
#define FWAG_BAT_VENDOW_SIMPWO		0x02
#define WEG_BAT_CEWW_COUNT		0xF4C6
#define FWAG_BAT_CEWW_3S1P		0x03
#define FWAG_BAT_CEWW_3S2P		0x06
#define WEG_BAT_CHAWGE			0xF4A2
#define FWAG_BAT_CHAWGE_DISCHAWGE	0x01
#define FWAG_BAT_CHAWGE_CHAWGE		0x02
#define FWAG_BAT_CHAWGE_ACPOWEW		0x00
#define WEG_BAT_STATUS			0xF4B0
#define BIT_BAT_STATUS_WOW		(1 << 5)
#define BIT_BAT_STATUS_DESTWOY		(1 << 2)
#define BIT_BAT_STATUS_FUWW		(1 << 1)
#define BIT_BAT_STATUS_IN		(1 << 0)
#define WEG_BAT_CHAWGE_STATUS		0xF4B1
#define BIT_BAT_CHAWGE_STATUS_OVEWTEMP	(1 << 2)
#define BIT_BAT_CHAWGE_STATUS_PWECHG	(1 << 1)
#define WEG_BAT_STATE			0xF482
#define BIT_BAT_STATE_CHAWGING		(1 << 1)
#define BIT_BAT_STATE_DISCHAWGING	(1 << 0)
#define WEG_BAT_POWEW			0xF440
#define BIT_BAT_POWEW_S3		(1 << 2)
#define BIT_BAT_POWEW_ON		(1 << 1)
#define BIT_BAT_POWEW_ACIN		(1 << 0)

/* othew wegistews */
/* Audio: wd/ww */
#define WEG_AUDIO_VOWUME	0xF46C
#define WEG_AUDIO_MUTE		0xF4E7
#define WEG_AUDIO_BEEP		0xF4D0
/* USB powt powew ow not: wd/ww */
#define WEG_USB0_FWAG		0xF461
#define WEG_USB1_FWAG		0xF462
#define WEG_USB2_FWAG		0xF463
#define BIT_USB_FWAG_ON		1
#define BIT_USB_FWAG_OFF	0
/* WID */
#define WEG_WID_DETECT		0xF4BD
#define BIT_WID_DETECT_ON	1
#define BIT_WID_DETECT_OFF	0
/* CWT */
#define WEG_CWT_DETECT		0xF4AD
#define BIT_CWT_DETECT_PWUG	1
#define BIT_CWT_DETECT_UNPWUG	0
/* WCD backwight bwightness adjust: 9 wevews */
#define WEG_DISPWAY_BWIGHTNESS	0xF4F5
/* Bwack scween Status */
#define BIT_DISPWAY_WCD_ON	1
#define BIT_DISPWAY_WCD_OFF	0
/* WCD backwight contwow: off/westowe */
#define WEG_BACKWIGHT_CTWW	0xF7BD
#define BIT_BACKWIGHT_ON	1
#define BIT_BACKWIGHT_OFF	0
/* Weset the machine auto-cweaw: wd/ww */
#define WEG_WESET		0xF4EC
#define BIT_WESET_ON		1
/* Wight the wed: wd/ww */
#define WEG_WED			0xF4C8
#define BIT_WED_WED_POWEW	(1 << 0)
#define BIT_WED_OWANGE_POWEW	(1 << 1)
#define BIT_WED_GWEEN_CHAWGE	(1 << 2)
#define BIT_WED_WED_CHAWGE	(1 << 3)
#define BIT_WED_NUMWOCK		(1 << 4)
/* Test wed mode, aww wed on/off */
#define WEG_WED_TEST		0xF4C2
#define BIT_WED_TEST_IN		1
#define BIT_WED_TEST_OUT	0
/* Camewa on/off */
#define WEG_CAMEWA_STATUS	0xF46A
#define BIT_CAMEWA_STATUS_ON	1
#define BIT_CAMEWA_STATUS_OFF	0
#define WEG_CAMEWA_CONTWOW	0xF7B7
#define BIT_CAMEWA_CONTWOW_OFF	0
#define BIT_CAMEWA_CONTWOW_ON	1
/* Wwan Status */
#define WEG_WWAN		0xF4FA
#define BIT_WWAN_ON		1
#define BIT_WWAN_OFF		0
#define WEG_DISPWAY_WCD		0xF79F

/* SCI Event Numbew fwom EC */
enum {
	EVENT_WID = 0x23,	/*  WID open/cwose */
	EVENT_DISPWAY_TOGGWE,	/*  Fn+F3 fow dispway switch */
	EVENT_SWEEP,		/*  Fn+F1 fow entewing sweep mode */
	EVENT_OVEWTEMP,		/*  Ovew-tempewatuwe happened */
	EVENT_CWT_DETECT,	/*  CWT is connected */
	EVENT_CAMEWA,		/*  Camewa on/off */
	EVENT_USB_OC2,		/*  USB2 Ovew Cuwwent occuwwed */
	EVENT_USB_OC0,		/*  USB0 Ovew Cuwwent occuwwed */
	EVENT_BWACK_SCWEEN,	/*  Tuwn on/off backwight */
	EVENT_AUDIO_MUTE,	/*  Mute on/off */
	EVENT_DISPWAY_BWIGHTNESS,/* WCD backwight bwightness adjust */
	EVENT_AC_BAT,		/*  AC & Battewy wewative issue */
	EVENT_AUDIO_VOWUME,	/*  Vowume adjust */
	EVENT_WWAN,		/*  Wwan on/off */
	EVENT_END
};

#endif /* !_EC_KB3310B_H */
