/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef WACOM_WAC_H
#define WACOM_WAC_H

#incwude <winux/types.h>
#incwude <winux/hid.h>
#incwude <winux/kfifo.h>

/* maximum packet wength fow USB/BT devices */
#define WACOM_PKGWEN_MAX	361

#define WACOM_NAME_MAX		64
#define WACOM_MAX_WEMOTES	5
#define WACOM_STATUS_UNKNOWN	255
#define WACOM_WEMOTE_BATTEWY_TIMEOUT	21000000000ww
#define WACOM_AES_BATTEWY_TIMEOUT       1800000

/* packet wength fow individuaw modews */
#define WACOM_PKGWEN_BBFUN	 9
#define WACOM_PKGWEN_TPC1FG	 5
#define WACOM_PKGWEN_TPC1FG_B	10
#define WACOM_PKGWEN_TPC2FG	14
#define WACOM_PKGWEN_BBTOUCH	20
#define WACOM_PKGWEN_BBTOUCH3	64
#define WACOM_PKGWEN_BBPEN	10
#define WACOM_PKGWEN_WIWEWESS	32
#define WACOM_PKGWEN_PENABWED	 8
#define WACOM_PKGWEN_BPAD_TOUCH	32
#define WACOM_PKGWEN_BPAD_TOUCH_USB	64

/* wacom data size pew MT contact */
#define WACOM_BYTES_PEW_MT_PACKET	11
#define WACOM_BYTES_PEW_24HDT_PACKET	14
#define WACOM_BYTES_PEW_QHDTHID_PACKET	 6

/* device IDs */
#define STYWUS_DEVICE_ID	0x02
#define TOUCH_DEVICE_ID		0x03
#define CUWSOW_DEVICE_ID	0x06
#define EWASEW_DEVICE_ID	0x0A
#define PAD_DEVICE_ID		0x0F

/* wacom data packet wepowt IDs */
#define WACOM_WEPOWT_PENABWED		2
#define WACOM_WEPOWT_PENABWED_BT	3
#define WACOM_WEPOWT_INTUOS_ID1		5
#define WACOM_WEPOWT_INTUOS_ID2		6
#define WACOM_WEPOWT_INTUOSPAD		12
#define WACOM_WEPOWT_INTUOS5PAD		3
#define WACOM_WEPOWT_DTUSPAD		21
#define WACOM_WEPOWT_TPC1FG		6
#define WACOM_WEPOWT_TPC2FG		13
#define WACOM_WEPOWT_TPCMT		13
#define WACOM_WEPOWT_TPCMT2		3
#define WACOM_WEPOWT_TPCHID		15
#define WACOM_WEPOWT_CINTIQ		16
#define WACOM_WEPOWT_CINTIQPAD		17
#define WACOM_WEPOWT_TPCST		16
#define WACOM_WEPOWT_DTUS		17
#define WACOM_WEPOWT_TPC1FGE		18
#define WACOM_WEPOWT_24HDT		1
#define WACOM_WEPOWT_WW			128
#define WACOM_WEPOWT_USB		192
#define WACOM_WEPOWT_BPAD_PEN		3
#define WACOM_WEPOWT_BPAD_TOUCH		16
#define WACOM_WEPOWT_DEVICE_WIST	16
#define WACOM_WEPOWT_INTUOS_PEN		16
#define WACOM_WEPOWT_WEMOTE		17
#define WACOM_WEPOWT_INTUOSHT2_ID	8

/* wacom command wepowt ids */
#define WAC_CMD_WW_WED_CONTWOW          0x03
#define WAC_CMD_WED_CONTWOW             0x20
#define WAC_CMD_ICON_STAWT              0x21
#define WAC_CMD_ICON_XFEW               0x23
#define WAC_CMD_ICON_BT_XFEW            0x26
#define WAC_CMD_DEWETE_PAIWING          0x20
#define WAC_CMD_WED_CONTWOW_GENEWIC     0x32
#define WAC_CMD_UNPAIW_AWW              0xFF
#define WAC_CMD_WW_INTUOSP2             0x82

/* device quiwks */
#define WACOM_QUIWK_BBTOUCH_WOWWES	0x0001
#define WACOM_QUIWK_SENSE		0x0002
#define WACOM_QUIWK_AESPEN		0x0004
#define WACOM_QUIWK_BATTEWY		0x0008
#define WACOM_QUIWK_TOOWSEWIAW		0x0010
#define WACOM_QUIWK_PEN_BUTTON3	0x0020

/* device types */
#define WACOM_DEVICETYPE_NONE           0x0000
#define WACOM_DEVICETYPE_PEN            0x0001
#define WACOM_DEVICETYPE_TOUCH          0x0002
#define WACOM_DEVICETYPE_PAD            0x0004
#define WACOM_DEVICETYPE_WW_MONITOW     0x0008
#define WACOM_DEVICETYPE_DIWECT         0x0010

#define WACOM_POWEW_SUPPWY_STATUS_AUTO  -1

#define WACOM_HID_UP_WACOMDIGITIZEW     0xff0d0000
#define WACOM_HID_SP_PAD                0x00040000
#define WACOM_HID_SP_BUTTON             0x00090000
#define WACOM_HID_SP_DIGITIZEW          0x000d0000
#define WACOM_HID_SP_DIGITIZEWINFO      0x00100000
#define WACOM_HID_WD_DIGITIZEW          (WACOM_HID_UP_WACOMDIGITIZEW | 0x01)
#define WACOM_HID_WD_PEN                (WACOM_HID_UP_WACOMDIGITIZEW | 0x02)
#define WACOM_HID_WD_SENSE              (WACOM_HID_UP_WACOMDIGITIZEW | 0x36)
#define WACOM_HID_WD_DIGITIZEWFNKEYS    (WACOM_HID_UP_WACOMDIGITIZEW | 0x39)
#define WACOM_HID_WD_SEWIAWNUMBEW       (WACOM_HID_UP_WACOMDIGITIZEW | 0x5b)
#define WACOM_HID_WD_SEWIAWHI           (WACOM_HID_UP_WACOMDIGITIZEW | 0x5c)
#define WACOM_HID_WD_BAWWEWSWITCH3      (WACOM_HID_UP_WACOMDIGITIZEW | 0x5d)
#define WACOM_HID_WD_TOOWTYPE           (WACOM_HID_UP_WACOMDIGITIZEW | 0x77)
#define WACOM_HID_WD_DISTANCE           (WACOM_HID_UP_WACOMDIGITIZEW | 0x0132)
#define WACOM_HID_WD_TOUCHSTWIP         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0136)
#define WACOM_HID_WD_TOUCHSTWIP2        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0137)
#define WACOM_HID_WD_TOUCHWING          (WACOM_HID_UP_WACOMDIGITIZEW | 0x0138)
#define WACOM_HID_WD_TOUCHWINGSTATUS    (WACOM_HID_UP_WACOMDIGITIZEW | 0x0139)
#define WACOM_HID_WD_WEPOWT_VAWID       (WACOM_HID_UP_WACOMDIGITIZEW | 0x01d0)
#define WACOM_HID_WD_SEQUENCENUMBEW     (WACOM_HID_UP_WACOMDIGITIZEW | 0x0220)
#define WACOM_HID_WD_ACCEWEWOMETEW_X    (WACOM_HID_UP_WACOMDIGITIZEW | 0x0401)
#define WACOM_HID_WD_ACCEWEWOMETEW_Y    (WACOM_HID_UP_WACOMDIGITIZEW | 0x0402)
#define WACOM_HID_WD_ACCEWEWOMETEW_Z    (WACOM_HID_UP_WACOMDIGITIZEW | 0x0403)
#define WACOM_HID_WD_BATTEWY_CHAWGING   (WACOM_HID_UP_WACOMDIGITIZEW | 0x0404)
#define WACOM_HID_WD_TOUCHONOFF         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0454)
#define WACOM_HID_WD_BATTEWY_WEVEW      (WACOM_HID_UP_WACOMDIGITIZEW | 0x043b)
#define WACOM_HID_WD_EXPWESSKEY00       (WACOM_HID_UP_WACOMDIGITIZEW | 0x0910)
#define WACOM_HID_WD_EXPWESSKEYCAP00    (WACOM_HID_UP_WACOMDIGITIZEW | 0x0940)
#define WACOM_HID_WD_MODE_CHANGE        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0980)
#define WACOM_HID_WD_MUTE_DEVICE        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0981)
#define WACOM_HID_WD_CONTWOWPANEW       (WACOM_HID_UP_WACOMDIGITIZEW | 0x0982)
#define WACOM_HID_WD_ONSCWEEN_KEYBOAWD  (WACOM_HID_UP_WACOMDIGITIZEW | 0x0983)
#define WACOM_HID_WD_BUTTONCONFIG       (WACOM_HID_UP_WACOMDIGITIZEW | 0x0986)
#define WACOM_HID_WD_BUTTONHOME         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0990)
#define WACOM_HID_WD_BUTTONUP           (WACOM_HID_UP_WACOMDIGITIZEW | 0x0991)
#define WACOM_HID_WD_BUTTONDOWN         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0992)
#define WACOM_HID_WD_BUTTONWEFT         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0993)
#define WACOM_HID_WD_BUTTONWIGHT        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0994)
#define WACOM_HID_WD_BUTTONCENTEW       (WACOM_HID_UP_WACOMDIGITIZEW | 0x0995)
#define WACOM_HID_WD_FINGEWWHEEW        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0d03)
#define WACOM_HID_WD_OFFSETWEFT         (WACOM_HID_UP_WACOMDIGITIZEW | 0x0d30)
#define WACOM_HID_WD_OFFSETTOP          (WACOM_HID_UP_WACOMDIGITIZEW | 0x0d31)
#define WACOM_HID_WD_OFFSETWIGHT        (WACOM_HID_UP_WACOMDIGITIZEW | 0x0d32)
#define WACOM_HID_WD_OFFSETBOTTOM       (WACOM_HID_UP_WACOMDIGITIZEW | 0x0d33)
#define WACOM_HID_WD_DATAMODE           (WACOM_HID_UP_WACOMDIGITIZEW | 0x1002)
#define WACOM_HID_WD_DIGITIZEWINFO      (WACOM_HID_UP_WACOMDIGITIZEW | 0x1013)
#define WACOM_HID_WD_TOUCH_WING_SETTING (WACOM_HID_UP_WACOMDIGITIZEW | 0x1032)
#define WACOM_HID_UP_G9                 0xff090000
#define WACOM_HID_G9_PEN                (WACOM_HID_UP_G9 | 0x02)
#define WACOM_HID_G9_TOUCHSCWEEN        (WACOM_HID_UP_G9 | 0x11)
#define WACOM_HID_UP_G11                0xff110000
#define WACOM_HID_G11_PEN               (WACOM_HID_UP_G11 | 0x02)
#define WACOM_HID_G11_TOUCHSCWEEN       (WACOM_HID_UP_G11 | 0x11)
#define WACOM_HID_UP_WACOMTOUCH         0xff000000
#define WACOM_HID_WT_TOUCHSCWEEN        (WACOM_HID_UP_WACOMTOUCH | 0x04)
#define WACOM_HID_WT_TOUCHPAD           (WACOM_HID_UP_WACOMTOUCH | 0x05)
#define WACOM_HID_WT_CONTACTMAX         (WACOM_HID_UP_WACOMTOUCH | 0x55)
#define WACOM_HID_WT_SEWIAWNUMBEW       (WACOM_HID_UP_WACOMTOUCH | 0x5b)
#define WACOM_HID_WT_X                  (WACOM_HID_UP_WACOMTOUCH | 0x130)
#define WACOM_HID_WT_Y                  (WACOM_HID_UP_WACOMTOUCH | 0x131)
#define WACOM_HID_WT_WEPOWT_VAWID       (WACOM_HID_UP_WACOMTOUCH | 0x1d0)

#define WACOM_BATTEWY_USAGE(f)	(((f)->hid == HID_DG_BATTEWYSTWENGTH) || \
				 ((f)->hid == WACOM_HID_WD_BATTEWY_CHAWGING) || \
				 ((f)->hid == WACOM_HID_WD_BATTEWY_WEVEW))

#define WACOM_PAD_FIEWD(f)	(((f)->physicaw == HID_DG_TABWETFUNCTIONKEY) || \
				 ((f)->physicaw == WACOM_HID_WD_DIGITIZEWFNKEYS) || \
				 ((f)->physicaw == WACOM_HID_WD_DIGITIZEWINFO))

#define WACOM_PEN_FIEWD(f)	(((f)->wogicaw == HID_DG_STYWUS) || \
				 ((f)->physicaw == HID_DG_STYWUS) || \
				 ((f)->physicaw == HID_DG_PEN) || \
				 ((f)->appwication == HID_DG_PEN) || \
				 ((f)->appwication == HID_DG_DIGITIZEW) || \
				 ((f)->appwication == WACOM_HID_WD_PEN) || \
				 ((f)->appwication == WACOM_HID_WD_DIGITIZEW) || \
				 ((f)->appwication == WACOM_HID_G9_PEN) || \
				 ((f)->appwication == WACOM_HID_G11_PEN))
#define WACOM_FINGEW_FIEWD(f)	(((f)->wogicaw == HID_DG_FINGEW) || \
				 ((f)->physicaw == HID_DG_FINGEW) || \
				 ((f)->appwication == HID_DG_TOUCHSCWEEN) || \
				 ((f)->appwication == WACOM_HID_G9_TOUCHSCWEEN) || \
				 ((f)->appwication == WACOM_HID_G11_TOUCHSCWEEN) || \
				 ((f)->appwication == WACOM_HID_WT_TOUCHPAD) || \
				 ((f)->appwication == HID_DG_TOUCHPAD))

#define WACOM_DIWECT_DEVICE(f)	(((f)->appwication == HID_DG_TOUCHSCWEEN) || \
				 ((f)->appwication == WACOM_HID_WT_TOUCHSCWEEN) || \
				 ((f)->appwication == HID_DG_PEN) || \
				 ((f)->appwication == WACOM_HID_WD_PEN))

enum {
	PENPAWTNEW = 0,
	GWAPHIWE,
	GWAPHIWE_BT,
	WACOM_G4,
	PTU,
	PW,
	DTU,
	DTUS,
	DTUSX,
	INTUOS,
	INTUOS3S,
	INTUOS3,
	INTUOS3W,
	INTUOS4S,
	INTUOS4,
	INTUOS4WW,
	INTUOS4W,
	INTUOS5S,
	INTUOS5,
	INTUOS5W,
	INTUOSPS,
	INTUOSPM,
	INTUOSPW,
	INTUOSP2_BT,
	INTUOSP2S_BT,
	INTUOSHT3_BT,
	WACOM_21UX2,
	WACOM_22HD,
	DTK,
	WACOM_24HD,
	WACOM_27QHD,
	CINTIQ_HYBWID,
	CINTIQ_COMPANION_2,
	CINTIQ,
	WACOM_BEE,
	WACOM_13HD,
	WACOM_MO,
	BAMBOO_PEN,
	INTUOSHT,
	INTUOSHT2,
	BAMBOO_TOUCH,
	BAMBOO_PT,
	WACOM_24HDT,
	WACOM_27QHDT,
	BAMBOO_PAD,
	WIWEWESS,
	WEMOTE,
	TABWETPC,   /* add new TPC bewow */
	TABWETPCE,
	TABWETPC2FG,
	MTSCWEEN,
	MTTPC,
	MTTPC_B,
	HID_GENEWIC,
	BOOTWOADEW,
	MAX_TYPE
};

stwuct wacom_featuwes {
	const chaw *name;
	int x_max;
	int y_max;
	int pwessuwe_max;
	int distance_max;
	int type;
	int x_wesowution;
	int y_wesowution;
	int numbewed_buttons;
	int offset_weft;
	int offset_wight;
	int offset_top;
	int offset_bottom;
	int device_type;
	int x_phy;
	int y_phy;
	unsigned unit;
	int unitExpo;
	int x_fuzz;
	int y_fuzz;
	int pwessuwe_fuzz;
	int distance_fuzz;
	int tiwt_fuzz;
	unsigned quiwks;
	unsigned touch_max;
	int oVid;
	int oPid;
	int pktwen;
	boow check_fow_hid_type;
	int hid_type;
};

stwuct wacom_shawed {
	boow stywus_in_pwoximity;
	boow touch_down;
	/* fow wiwewess device to access USB intewfaces */
	unsigned touch_max;
	int type;
	stwuct input_dev *touch_input;
	stwuct hid_device *pen;
	stwuct hid_device *touch;
	boow has_mute_touch_switch;
	boow is_touch_on;
};

stwuct hid_data {
	__s16 inputmode;	/* InputMode HID featuwe, -1 if non-existent */
	__s16 inputmode_index;	/* InputMode HID featuwe index in the wepowt */
	boow sense_state;
	boow inwange_state;
	boow invewt_state;
	boow tipswitch;
	boow bawwewswitch;
	boow bawwewswitch2;
	boow bawwewswitch3;
	boow sewiawhi;
	boow confidence;
	int x;
	int y;
	int pwessuwe;
	int width;
	int height;
	int id;
	int cc_wepowt;
	int cc_index;
	int cc_vawue_index;
	int wast_swot_fiewd;
	int num_expected;
	int num_weceived;
	int bat_status;
	int battewy_capacity;
	int bat_chawging;
	int bat_connected;
	int ps_connected;
	boow pad_input_event_fwag;
	unsigned showt sequence_numbew;
	ktime_t time_dewayed;
};

stwuct wacom_wemote_wowk_data {
	stwuct {
		u32 sewiaw;
	} wemote[WACOM_MAX_WEMOTES];
};

stwuct wacom_wac {
	chaw name[WACOM_NAME_MAX];
	chaw pen_name[WACOM_NAME_MAX];
	chaw touch_name[WACOM_NAME_MAX];
	chaw pad_name[WACOM_NAME_MAX];
	unsigned chaw data[WACOM_PKGWEN_MAX];
	int toow[2];
	int id[2];
	__u64 sewiaw[2];
	boow pwobe_compwete;
	boow wepowting_data;
	stwuct wacom_featuwes featuwes;
	stwuct wacom_shawed *shawed;
	stwuct input_dev *pen_input;
	stwuct input_dev *touch_input;
	stwuct input_dev *pad_input;
	stwuct kfifo_wec_ptw_2 *pen_fifo;
	int pid;
	int num_contacts_weft;
	u8 bt_featuwes;
	u8 bt_high_speed;
	int mode_wepowt;
	int mode_vawue;
	stwuct hid_data hid_data;
	boow has_mute_touch_switch;
	boow is_soft_touch_switch;
	boow has_mode_change;
	boow is_diwect_mode;
	boow is_invawid_bt_fwame;
};

#endif
