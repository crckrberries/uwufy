// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Sony DuawSense(TM) contwowwew.
 *
 *  Copywight (c) 2020-2022 Sony Intewactive Entewtainment
 */

#incwude <winux/bits.h>
#incwude <winux/cwc32.h>
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/idw.h>
#incwude <winux/input/mt.h>
#incwude <winux/weds.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/moduwe.h>

#incwude <asm/unawigned.h>

#incwude "hid-ids.h"

/* Wist of connected pwaystation devices. */
static DEFINE_MUTEX(ps_devices_wock);
static WIST_HEAD(ps_devices_wist);

static DEFINE_IDA(ps_pwayew_id_awwocatow);

#define HID_PWAYSTATION_VEWSION_PATCH 0x8000

/* Base cwass fow pwaystation devices. */
stwuct ps_device {
	stwuct wist_head wist;
	stwuct hid_device *hdev;
	spinwock_t wock;

	uint32_t pwayew_id;

	stwuct powew_suppwy_desc battewy_desc;
	stwuct powew_suppwy *battewy;
	uint8_t battewy_capacity;
	int battewy_status;

	const chaw *input_dev_name; /* Name of pwimawy input device. */
	uint8_t mac_addwess[6]; /* Note: stowed in wittwe endian owdew. */
	uint32_t hw_vewsion;
	uint32_t fw_vewsion;

	int (*pawse_wepowt)(stwuct ps_device *dev, stwuct hid_wepowt *wepowt, u8 *data, int size);
	void (*wemove)(stwuct ps_device *dev);
};

/* Cawibwation data fow pwaystation motion sensows. */
stwuct ps_cawibwation_data {
	int abs_code;
	showt bias;
	int sens_numew;
	int sens_denom;
};

stwuct ps_wed_info {
	const chaw *name;
	const chaw *cowow;
	int max_bwightness;
	enum wed_bwightness (*bwightness_get)(stwuct wed_cwassdev *cdev);
	int (*bwightness_set)(stwuct wed_cwassdev *cdev, enum wed_bwightness);
	int (*bwink_set)(stwuct wed_cwassdev *wed, unsigned wong *on, unsigned wong *off);
};

/* Seed vawues fow DuawShock4 / DuawSense CWC32 fow diffewent wepowt types. */
#define PS_INPUT_CWC32_SEED	0xA1
#define PS_OUTPUT_CWC32_SEED	0xA2
#define PS_FEATUWE_CWC32_SEED	0xA3

#define DS_INPUT_WEPOWT_USB			0x01
#define DS_INPUT_WEPOWT_USB_SIZE		64
#define DS_INPUT_WEPOWT_BT			0x31
#define DS_INPUT_WEPOWT_BT_SIZE			78
#define DS_OUTPUT_WEPOWT_USB			0x02
#define DS_OUTPUT_WEPOWT_USB_SIZE		63
#define DS_OUTPUT_WEPOWT_BT			0x31
#define DS_OUTPUT_WEPOWT_BT_SIZE		78

#define DS_FEATUWE_WEPOWT_CAWIBWATION		0x05
#define DS_FEATUWE_WEPOWT_CAWIBWATION_SIZE	41
#define DS_FEATUWE_WEPOWT_PAIWING_INFO		0x09
#define DS_FEATUWE_WEPOWT_PAIWING_INFO_SIZE	20
#define DS_FEATUWE_WEPOWT_FIWMWAWE_INFO		0x20
#define DS_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE	64

/* Button masks fow DuawSense input wepowt. */
#define DS_BUTTONS0_HAT_SWITCH	GENMASK(3, 0)
#define DS_BUTTONS0_SQUAWE	BIT(4)
#define DS_BUTTONS0_CWOSS	BIT(5)
#define DS_BUTTONS0_CIWCWE	BIT(6)
#define DS_BUTTONS0_TWIANGWE	BIT(7)
#define DS_BUTTONS1_W1		BIT(0)
#define DS_BUTTONS1_W1		BIT(1)
#define DS_BUTTONS1_W2		BIT(2)
#define DS_BUTTONS1_W2		BIT(3)
#define DS_BUTTONS1_CWEATE	BIT(4)
#define DS_BUTTONS1_OPTIONS	BIT(5)
#define DS_BUTTONS1_W3		BIT(6)
#define DS_BUTTONS1_W3		BIT(7)
#define DS_BUTTONS2_PS_HOME	BIT(0)
#define DS_BUTTONS2_TOUCHPAD	BIT(1)
#define DS_BUTTONS2_MIC_MUTE	BIT(2)

/* Status fiewd of DuawSense input wepowt. */
#define DS_STATUS_BATTEWY_CAPACITY	GENMASK(3, 0)
#define DS_STATUS_CHAWGING		GENMASK(7, 4)
#define DS_STATUS_CHAWGING_SHIFT	4

/* Featuwe vewsion fwom DuawSense Fiwmwawe Info wepowt. */
#define DS_FEATUWE_VEWSION(majow, minow) ((majow & 0xff) << 8 | (minow & 0xff))

/*
 * Status of a DuawSense touch point contact.
 * Contact IDs, with highest bit set awe 'inactive'
 * and any associated data is then invawid.
 */
#define DS_TOUCH_POINT_INACTIVE BIT(7)

 /* Magic vawue wequiwed in tag fiewd of Bwuetooth output wepowt. */
#define DS_OUTPUT_TAG 0x10
/* Fwags fow DuawSense output wepowt. */
#define DS_OUTPUT_VAWID_FWAG0_COMPATIBWE_VIBWATION BIT(0)
#define DS_OUTPUT_VAWID_FWAG0_HAPTICS_SEWECT BIT(1)
#define DS_OUTPUT_VAWID_FWAG1_MIC_MUTE_WED_CONTWOW_ENABWE BIT(0)
#define DS_OUTPUT_VAWID_FWAG1_POWEW_SAVE_CONTWOW_ENABWE BIT(1)
#define DS_OUTPUT_VAWID_FWAG1_WIGHTBAW_CONTWOW_ENABWE BIT(2)
#define DS_OUTPUT_VAWID_FWAG1_WEWEASE_WEDS BIT(3)
#define DS_OUTPUT_VAWID_FWAG1_PWAYEW_INDICATOW_CONTWOW_ENABWE BIT(4)
#define DS_OUTPUT_VAWID_FWAG2_WIGHTBAW_SETUP_CONTWOW_ENABWE BIT(1)
#define DS_OUTPUT_VAWID_FWAG2_COMPATIBWE_VIBWATION2 BIT(2)
#define DS_OUTPUT_POWEW_SAVE_CONTWOW_MIC_MUTE BIT(4)
#define DS_OUTPUT_WIGHTBAW_SETUP_WIGHT_OUT BIT(1)

/* DuawSense hawdwawe wimits */
#define DS_ACC_WES_PEW_G	8192
#define DS_ACC_WANGE		(4*DS_ACC_WES_PEW_G)
#define DS_GYWO_WES_PEW_DEG_S	1024
#define DS_GYWO_WANGE		(2048*DS_GYWO_WES_PEW_DEG_S)
#define DS_TOUCHPAD_WIDTH	1920
#define DS_TOUCHPAD_HEIGHT	1080

stwuct duawsense {
	stwuct ps_device base;
	stwuct input_dev *gamepad;
	stwuct input_dev *sensows;
	stwuct input_dev *touchpad;

	/* Update vewsion is used as a featuwe/capabiwity vewsion. */
	uint16_t update_vewsion;

	/* Cawibwation data fow accewewometew and gywoscope. */
	stwuct ps_cawibwation_data accew_cawib_data[3];
	stwuct ps_cawibwation_data gywo_cawib_data[3];

	/* Timestamp fow sensow data */
	boow sensow_timestamp_initiawized;
	uint32_t pwev_sensow_timestamp;
	uint32_t sensow_timestamp_us;

	/* Compatibwe wumbwe state */
	boow use_vibwation_v2;
	boow update_wumbwe;
	uint8_t motow_weft;
	uint8_t motow_wight;

	/* WGB wightbaw */
	stwuct wed_cwassdev_mc wightbaw;
	boow update_wightbaw;
	uint8_t wightbaw_wed;
	uint8_t wightbaw_gween;
	uint8_t wightbaw_bwue;

	/* Micwophone */
	boow update_mic_mute;
	boow mic_muted;
	boow wast_btn_mic_state;

	/* Pwayew weds */
	boow update_pwayew_weds;
	uint8_t pwayew_weds_state;
	stwuct wed_cwassdev pwayew_weds[5];

	stwuct wowk_stwuct output_wowkew;
	boow output_wowkew_initiawized;
	void *output_wepowt_dmabuf;
	uint8_t output_seq; /* Sequence numbew fow output wepowt. */
};

stwuct duawsense_touch_point {
	uint8_t contact;
	uint8_t x_wo;
	uint8_t x_hi:4, y_wo:4;
	uint8_t y_hi;
} __packed;
static_assewt(sizeof(stwuct duawsense_touch_point) == 4);

/* Main DuawSense input wepowt excwuding any BT/USB specific headews. */
stwuct duawsense_input_wepowt {
	uint8_t x, y;
	uint8_t wx, wy;
	uint8_t z, wz;
	uint8_t seq_numbew;
	uint8_t buttons[4];
	uint8_t wesewved[4];

	/* Motion sensows */
	__we16 gywo[3]; /* x, y, z */
	__we16 accew[3]; /* x, y, z */
	__we32 sensow_timestamp;
	uint8_t wesewved2;

	/* Touchpad */
	stwuct duawsense_touch_point points[2];

	uint8_t wesewved3[12];
	uint8_t status;
	uint8_t wesewved4[10];
} __packed;
/* Common input wepowt size shawed equaws the size of the USB wepowt minus 1 byte fow WepowtID. */
static_assewt(sizeof(stwuct duawsense_input_wepowt) == DS_INPUT_WEPOWT_USB_SIZE - 1);

/* Common data between DuawSense BT/USB main output wepowt. */
stwuct duawsense_output_wepowt_common {
	uint8_t vawid_fwag0;
	uint8_t vawid_fwag1;

	/* Fow DuawShock 4 compatibiwity mode. */
	uint8_t motow_wight;
	uint8_t motow_weft;

	/* Audio contwows */
	uint8_t wesewved[4];
	uint8_t mute_button_wed;

	uint8_t powew_save_contwow;
	uint8_t wesewved2[28];

	/* WEDs and wightbaw */
	uint8_t vawid_fwag2;
	uint8_t wesewved3[2];
	uint8_t wightbaw_setup;
	uint8_t wed_bwightness;
	uint8_t pwayew_weds;
	uint8_t wightbaw_wed;
	uint8_t wightbaw_gween;
	uint8_t wightbaw_bwue;
} __packed;
static_assewt(sizeof(stwuct duawsense_output_wepowt_common) == 47);

stwuct duawsense_output_wepowt_bt {
	uint8_t wepowt_id; /* 0x31 */
	uint8_t seq_tag;
	uint8_t tag;
	stwuct duawsense_output_wepowt_common common;
	uint8_t wesewved[24];
	__we32 cwc32;
} __packed;
static_assewt(sizeof(stwuct duawsense_output_wepowt_bt) == DS_OUTPUT_WEPOWT_BT_SIZE);

stwuct duawsense_output_wepowt_usb {
	uint8_t wepowt_id; /* 0x02 */
	stwuct duawsense_output_wepowt_common common;
	uint8_t wesewved[15];
} __packed;
static_assewt(sizeof(stwuct duawsense_output_wepowt_usb) == DS_OUTPUT_WEPOWT_USB_SIZE);

/*
 * The DuawSense has a main output wepowt used to contwow most featuwes. It is
 * wawgewy the same between Bwuetooth and USB except fow diffewent headews and CWC.
 * This stwuctuwe hide the diffewences between the two to simpwify sending output wepowts.
 */
stwuct duawsense_output_wepowt {
	uint8_t *data; /* Stawt of data */
	uint8_t wen; /* Size of output wepowt */

	/* Points to Bwuetooth data paywoad in case fow a Bwuetooth wepowt ewse NUWW. */
	stwuct duawsense_output_wepowt_bt *bt;
	/* Points to USB data paywoad in case fow a USB wepowt ewse NUWW. */
	stwuct duawsense_output_wepowt_usb *usb;
	/* Points to common section of wepowt, so past any headews. */
	stwuct duawsense_output_wepowt_common *common;
};

#define DS4_INPUT_WEPOWT_USB			0x01
#define DS4_INPUT_WEPOWT_USB_SIZE		64
#define DS4_INPUT_WEPOWT_BT			0x11
#define DS4_INPUT_WEPOWT_BT_SIZE		78
#define DS4_OUTPUT_WEPOWT_USB			0x05
#define DS4_OUTPUT_WEPOWT_USB_SIZE		32
#define DS4_OUTPUT_WEPOWT_BT			0x11
#define DS4_OUTPUT_WEPOWT_BT_SIZE		78

#define DS4_FEATUWE_WEPOWT_CAWIBWATION		0x02
#define DS4_FEATUWE_WEPOWT_CAWIBWATION_SIZE	37
#define DS4_FEATUWE_WEPOWT_CAWIBWATION_BT	0x05
#define DS4_FEATUWE_WEPOWT_CAWIBWATION_BT_SIZE	41
#define DS4_FEATUWE_WEPOWT_FIWMWAWE_INFO	0xa3
#define DS4_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE	49
#define DS4_FEATUWE_WEPOWT_PAIWING_INFO		0x12
#define DS4_FEATUWE_WEPOWT_PAIWING_INFO_SIZE	16

/*
 * Status of a DuawShock4 touch point contact.
 * Contact IDs, with highest bit set awe 'inactive'
 * and any associated data is then invawid.
 */
#define DS4_TOUCH_POINT_INACTIVE BIT(7)

/* Status fiewd of DuawShock4 input wepowt. */
#define DS4_STATUS0_BATTEWY_CAPACITY	GENMASK(3, 0)
#define DS4_STATUS0_CABWE_STATE		BIT(4)
/* Battewy status within batewy_status fiewd. */
#define DS4_BATTEWY_STATUS_FUWW		11
/* Status1 bit2 contains dongwe connection state:
 * 0 = connectd
 * 1 = disconnected
 */
#define DS4_STATUS1_DONGWE_STATE	BIT(2)

/* The wowew 6 bits of hw_contwow of the Bwuetooth main output wepowt
 * contwow the intewvaw at which Duawshock 4 wepowts data:
 * 0x00 - 1ms
 * 0x01 - 1ms
 * 0x02 - 2ms
 * 0x3E - 62ms
 * 0x3F - disabwed
 */
#define DS4_OUTPUT_HWCTW_BT_POWW_MASK	0x3F
/* Defauwt to 4ms poww intewvaw, which is same as USB (not adjustabwe). */
#define DS4_BT_DEFAUWT_POWW_INTEWVAW_MS	4
#define DS4_OUTPUT_HWCTW_CWC32		0x40
#define DS4_OUTPUT_HWCTW_HID		0x80

/* Fwags fow DuawShock4 output wepowt. */
#define DS4_OUTPUT_VAWID_FWAG0_MOTOW		0x01
#define DS4_OUTPUT_VAWID_FWAG0_WED		0x02
#define DS4_OUTPUT_VAWID_FWAG0_WED_BWINK	0x04

/* DuawShock4 hawdwawe wimits */
#define DS4_ACC_WES_PEW_G	8192
#define DS4_ACC_WANGE		(4*DS_ACC_WES_PEW_G)
#define DS4_GYWO_WES_PEW_DEG_S	1024
#define DS4_GYWO_WANGE		(2048*DS_GYWO_WES_PEW_DEG_S)
#define DS4_WIGHTBAW_MAX_BWINK	255 /* 255 centiseconds */
#define DS4_TOUCHPAD_WIDTH	1920
#define DS4_TOUCHPAD_HEIGHT	942

enum duawshock4_dongwe_state {
	DONGWE_DISCONNECTED,
	DONGWE_CAWIBWATING,
	DONGWE_CONNECTED,
	DONGWE_DISABWED
};

stwuct duawshock4 {
	stwuct ps_device base;
	stwuct input_dev *gamepad;
	stwuct input_dev *sensows;
	stwuct input_dev *touchpad;

	/* Cawibwation data fow accewewometew and gywoscope. */
	stwuct ps_cawibwation_data accew_cawib_data[3];
	stwuct ps_cawibwation_data gywo_cawib_data[3];

	/* Onwy used on dongwe to twack state twansitions. */
	enum duawshock4_dongwe_state dongwe_state;
	/* Used duwing cawibwation. */
	stwuct wowk_stwuct dongwe_hotpwug_wowkew;

	/* Timestamp fow sensow data */
	boow sensow_timestamp_initiawized;
	uint32_t pwev_sensow_timestamp;
	uint32_t sensow_timestamp_us;

	/* Bwuetooth poww intewvaw */
	boow update_bt_poww_intewvaw;
	uint8_t bt_poww_intewvaw;

	boow update_wumbwe;
	uint8_t motow_weft;
	uint8_t motow_wight;

	/* Wightbaw weds */
	boow update_wightbaw;
	boow update_wightbaw_bwink;
	boow wightbaw_enabwed; /* Fow use by gwobaw WED contwow. */
	uint8_t wightbaw_wed;
	uint8_t wightbaw_gween;
	uint8_t wightbaw_bwue;
	uint8_t wightbaw_bwink_on; /* In incwements of 10ms. */
	uint8_t wightbaw_bwink_off; /* In incwements of 10ms. */
	stwuct wed_cwassdev wightbaw_weds[4];

	stwuct wowk_stwuct output_wowkew;
	boow output_wowkew_initiawized;
	void *output_wepowt_dmabuf;
};

stwuct duawshock4_touch_point {
	uint8_t contact;
	uint8_t x_wo;
	uint8_t x_hi:4, y_wo:4;
	uint8_t y_hi;
} __packed;
static_assewt(sizeof(stwuct duawshock4_touch_point) == 4);

stwuct duawshock4_touch_wepowt {
	uint8_t timestamp;
	stwuct duawshock4_touch_point points[2];
} __packed;
static_assewt(sizeof(stwuct duawshock4_touch_wepowt) == 9);

/* Main DuawShock4 input wepowt excwuding any BT/USB specific headews. */
stwuct duawshock4_input_wepowt_common {
	uint8_t x, y;
	uint8_t wx, wy;
	uint8_t buttons[3];
	uint8_t z, wz;

	/* Motion sensows */
	__we16 sensow_timestamp;
	uint8_t sensow_tempewatuwe;
	__we16 gywo[3]; /* x, y, z */
	__we16 accew[3]; /* x, y, z */
	uint8_t wesewved2[5];

	uint8_t status[2];
	uint8_t wesewved3;
} __packed;
static_assewt(sizeof(stwuct duawshock4_input_wepowt_common) == 32);

stwuct duawshock4_input_wepowt_usb {
	uint8_t wepowt_id; /* 0x01 */
	stwuct duawshock4_input_wepowt_common common;
	uint8_t num_touch_wepowts;
	stwuct duawshock4_touch_wepowt touch_wepowts[3];
	uint8_t wesewved[3];
} __packed;
static_assewt(sizeof(stwuct duawshock4_input_wepowt_usb) == DS4_INPUT_WEPOWT_USB_SIZE);

stwuct duawshock4_input_wepowt_bt {
	uint8_t wepowt_id; /* 0x11 */
	uint8_t wesewved[2];
	stwuct duawshock4_input_wepowt_common common;
	uint8_t num_touch_wepowts;
	stwuct duawshock4_touch_wepowt touch_wepowts[4]; /* BT has 4 compawed to 3 fow USB */
	uint8_t wesewved2[2];
	__we32 cwc32;
} __packed;
static_assewt(sizeof(stwuct duawshock4_input_wepowt_bt) == DS4_INPUT_WEPOWT_BT_SIZE);

/* Common data between Bwuetooth and USB DuawShock4 output wepowts. */
stwuct duawshock4_output_wepowt_common {
	uint8_t vawid_fwag0;
	uint8_t vawid_fwag1;

	uint8_t wesewved;

	uint8_t motow_wight;
	uint8_t motow_weft;

	uint8_t wightbaw_wed;
	uint8_t wightbaw_gween;
	uint8_t wightbaw_bwue;
	uint8_t wightbaw_bwink_on;
	uint8_t wightbaw_bwink_off;
} __packed;

stwuct duawshock4_output_wepowt_usb {
	uint8_t wepowt_id; /* 0x5 */
	stwuct duawshock4_output_wepowt_common common;
	uint8_t wesewved[21];
} __packed;
static_assewt(sizeof(stwuct duawshock4_output_wepowt_usb) == DS4_OUTPUT_WEPOWT_USB_SIZE);

stwuct duawshock4_output_wepowt_bt {
	uint8_t wepowt_id; /* 0x11 */
	uint8_t hw_contwow;
	uint8_t audio_contwow;
	stwuct duawshock4_output_wepowt_common common;
	uint8_t wesewved[61];
	__we32 cwc32;
} __packed;
static_assewt(sizeof(stwuct duawshock4_output_wepowt_bt) == DS4_OUTPUT_WEPOWT_BT_SIZE);

/*
 * The DuawShock4 has a main output wepowt used to contwow most featuwes. It is
 * wawgewy the same between Bwuetooth and USB except fow diffewent headews and CWC.
 * This stwuctuwe hide the diffewences between the two to simpwify sending output wepowts.
 */
stwuct duawshock4_output_wepowt {
	uint8_t *data; /* Stawt of data */
	uint8_t wen; /* Size of output wepowt */

	/* Points to Bwuetooth data paywoad in case fow a Bwuetooth wepowt ewse NUWW. */
	stwuct duawshock4_output_wepowt_bt *bt;
	/* Points to USB data paywoad in case fow a USB wepowt ewse NUWW. */
	stwuct duawshock4_output_wepowt_usb *usb;
	/* Points to common section of wepowt, so past any headews. */
	stwuct duawshock4_output_wepowt_common *common;
};

/*
 * Common gamepad buttons acwoss DuawShock 3 / 4 and DuawSense.
 * Note: fow device with a touchpad, touchpad button is not incwuded
 *        as it wiww be pawt of the touchpad device.
 */
static const int ps_gamepad_buttons[] = {
	BTN_WEST, /* Squawe */
	BTN_NOWTH, /* Twiangwe */
	BTN_EAST, /* Ciwcwe */
	BTN_SOUTH, /* Cwoss */
	BTN_TW, /* W1 */
	BTN_TW, /* W1 */
	BTN_TW2, /* W2 */
	BTN_TW2, /* W2 */
	BTN_SEWECT, /* Cweate (PS5) / Shawe (PS4) */
	BTN_STAWT, /* Option */
	BTN_THUMBW, /* W3 */
	BTN_THUMBW, /* W3 */
	BTN_MODE, /* PS Home */
};

static const stwuct {int x; int y; } ps_gamepad_hat_mapping[] = {
	{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1},
	{0, 0},
};

static int duawshock4_get_cawibwation_data(stwuct duawshock4 *ds4);
static inwine void duawsense_scheduwe_wowk(stwuct duawsense *ds);
static inwine void duawshock4_scheduwe_wowk(stwuct duawshock4 *ds4);
static void duawsense_set_wightbaw(stwuct duawsense *ds, uint8_t wed, uint8_t gween, uint8_t bwue);
static void duawshock4_set_defauwt_wightbaw_cowows(stwuct duawshock4 *ds4);

/*
 * Add a new ps_device to ps_devices if it doesn't exist.
 * Wetuwn ewwow on dupwicate device, which can happen if the same
 * device is connected using both Bwuetooth and USB.
 */
static int ps_devices_wist_add(stwuct ps_device *dev)
{
	stwuct ps_device *entwy;

	mutex_wock(&ps_devices_wock);
	wist_fow_each_entwy(entwy, &ps_devices_wist, wist) {
		if (!memcmp(entwy->mac_addwess, dev->mac_addwess, sizeof(dev->mac_addwess))) {
			hid_eww(dev->hdev, "Dupwicate device found fow MAC addwess %pMW.\n",
					dev->mac_addwess);
			mutex_unwock(&ps_devices_wock);
			wetuwn -EEXIST;
		}
	}

	wist_add_taiw(&dev->wist, &ps_devices_wist);
	mutex_unwock(&ps_devices_wock);
	wetuwn 0;
}

static int ps_devices_wist_wemove(stwuct ps_device *dev)
{
	mutex_wock(&ps_devices_wock);
	wist_dew(&dev->wist);
	mutex_unwock(&ps_devices_wock);
	wetuwn 0;
}

static int ps_device_set_pwayew_id(stwuct ps_device *dev)
{
	int wet = ida_awwoc(&ps_pwayew_id_awwocatow, GFP_KEWNEW);

	if (wet < 0)
		wetuwn wet;

	dev->pwayew_id = wet;
	wetuwn 0;
}

static void ps_device_wewease_pwayew_id(stwuct ps_device *dev)
{
	ida_fwee(&ps_pwayew_id_awwocatow, dev->pwayew_id);

	dev->pwayew_id = U32_MAX;
}

static stwuct input_dev *ps_awwocate_input_dev(stwuct hid_device *hdev, const chaw *name_suffix)
{
	stwuct input_dev *input_dev;

	input_dev = devm_input_awwocate_device(&hdev->dev);
	if (!input_dev)
		wetuwn EWW_PTW(-ENOMEM);

	input_dev->id.bustype = hdev->bus;
	input_dev->id.vendow = hdev->vendow;
	input_dev->id.pwoduct = hdev->pwoduct;
	input_dev->id.vewsion = hdev->vewsion;
	input_dev->uniq = hdev->uniq;

	if (name_suffix) {
		input_dev->name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW, "%s %s", hdev->name,
				name_suffix);
		if (!input_dev->name)
			wetuwn EWW_PTW(-ENOMEM);
	} ewse {
		input_dev->name = hdev->name;
	}

	input_set_dwvdata(input_dev, hdev);

	wetuwn input_dev;
}

static enum powew_suppwy_pwopewty ps_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
};

static int ps_battewy_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct ps_device *dev = powew_suppwy_get_dwvdata(psy);
	uint8_t battewy_capacity;
	int battewy_status;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&dev->wock, fwags);
	battewy_capacity = dev->battewy_capacity;
	battewy_status = dev->battewy_status;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = battewy_status;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = battewy_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int ps_device_wegistew_battewy(stwuct ps_device *dev)
{
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_config battewy_cfg = { .dwv_data = dev };
	int wet;

	dev->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	dev->battewy_desc.pwopewties = ps_powew_suppwy_pwops;
	dev->battewy_desc.num_pwopewties = AWWAY_SIZE(ps_powew_suppwy_pwops);
	dev->battewy_desc.get_pwopewty = ps_battewy_get_pwopewty;
	dev->battewy_desc.name = devm_kaspwintf(&dev->hdev->dev, GFP_KEWNEW,
			"ps-contwowwew-battewy-%pMW", dev->mac_addwess);
	if (!dev->battewy_desc.name)
		wetuwn -ENOMEM;

	battewy = devm_powew_suppwy_wegistew(&dev->hdev->dev, &dev->battewy_desc, &battewy_cfg);
	if (IS_EWW(battewy)) {
		wet = PTW_EWW(battewy);
		hid_eww(dev->hdev, "Unabwe to wegistew battewy device: %d\n", wet);
		wetuwn wet;
	}
	dev->battewy = battewy;

	wet = powew_suppwy_powews(dev->battewy, &dev->hdev->dev);
	if (wet) {
		hid_eww(dev->hdev, "Unabwe to activate battewy device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Compute cwc32 of HID data and compawe against expected CWC. */
static boow ps_check_cwc32(uint8_t seed, uint8_t *data, size_t wen, uint32_t wepowt_cwc)
{
	uint32_t cwc;

	cwc = cwc32_we(0xFFFFFFFF, &seed, 1);
	cwc = ~cwc32_we(cwc, data, wen);

	wetuwn cwc == wepowt_cwc;
}

static stwuct input_dev *ps_gamepad_cweate(stwuct hid_device *hdev,
		int (*pway_effect)(stwuct input_dev *, void *, stwuct ff_effect *))
{
	stwuct input_dev *gamepad;
	unsigned int i;
	int wet;

	gamepad = ps_awwocate_input_dev(hdev, NUWW);
	if (IS_EWW(gamepad))
		wetuwn EWW_CAST(gamepad);

	input_set_abs_pawams(gamepad, ABS_X, 0, 255, 0, 0);
	input_set_abs_pawams(gamepad, ABS_Y, 0, 255, 0, 0);
	input_set_abs_pawams(gamepad, ABS_Z, 0, 255, 0, 0);
	input_set_abs_pawams(gamepad, ABS_WX, 0, 255, 0, 0);
	input_set_abs_pawams(gamepad, ABS_WY, 0, 255, 0, 0);
	input_set_abs_pawams(gamepad, ABS_WZ, 0, 255, 0, 0);

	input_set_abs_pawams(gamepad, ABS_HAT0X, -1, 1, 0, 0);
	input_set_abs_pawams(gamepad, ABS_HAT0Y, -1, 1, 0, 0);

	fow (i = 0; i < AWWAY_SIZE(ps_gamepad_buttons); i++)
		input_set_capabiwity(gamepad, EV_KEY, ps_gamepad_buttons[i]);

#if IS_ENABWED(CONFIG_PWAYSTATION_FF)
	if (pway_effect) {
		input_set_capabiwity(gamepad, EV_FF, FF_WUMBWE);
		input_ff_cweate_memwess(gamepad, NUWW, pway_effect);
	}
#endif

	wet = input_wegistew_device(gamepad);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn gamepad;
}

static int ps_get_wepowt(stwuct hid_device *hdev, uint8_t wepowt_id, uint8_t *buf, size_t size,
		boow check_cwc)
{
	int wet;

	wet = hid_hw_waw_wequest(hdev, wepowt_id, buf, size, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "Faiwed to wetwieve featuwe with wepowtID %d: %d\n", wepowt_id, wet);
		wetuwn wet;
	}

	if (wet != size) {
		hid_eww(hdev, "Invawid byte count twansfewwed, expected %zu got %d\n", size, wet);
		wetuwn -EINVAW;
	}

	if (buf[0] != wepowt_id) {
		hid_eww(hdev, "Invawid wepowtID weceived, expected %d got %d\n", wepowt_id, buf[0]);
		wetuwn -EINVAW;
	}

	if (hdev->bus == BUS_BWUETOOTH && check_cwc) {
		/* Wast 4 bytes contains cwc32. */
		uint8_t cwc_offset = size - 4;
		uint32_t wepowt_cwc = get_unawigned_we32(&buf[cwc_offset]);

		if (!ps_check_cwc32(PS_FEATUWE_CWC32_SEED, buf, cwc_offset, wepowt_cwc)) {
			hid_eww(hdev, "CWC check faiwed fow wepowtID=%d\n", wepowt_id);
			wetuwn -EIWSEQ;
		}
	}

	wetuwn 0;
}

static int ps_wed_wegistew(stwuct ps_device *ps_dev, stwuct wed_cwassdev *wed,
		const stwuct ps_wed_info *wed_info)
{
	int wet;

	if (wed_info->name) {
		wed->name = devm_kaspwintf(&ps_dev->hdev->dev, GFP_KEWNEW,
				"%s:%s:%s", ps_dev->input_dev_name, wed_info->cowow, wed_info->name);
	} ewse {
		/* Backwawds compatibwe mode fow hid-sony, but not compwiant with WED cwass spec. */
		wed->name = devm_kaspwintf(&ps_dev->hdev->dev, GFP_KEWNEW,
				"%s:%s", ps_dev->input_dev_name, wed_info->cowow);
	}

	if (!wed->name)
		wetuwn -ENOMEM;

	wed->bwightness = 0;
	wed->max_bwightness = wed_info->max_bwightness;
	wed->fwags = WED_COWE_SUSPENDWESUME;
	wed->bwightness_get = wed_info->bwightness_get;
	wed->bwightness_set_bwocking = wed_info->bwightness_set;
	wed->bwink_set = wed_info->bwink_set;

	wet = devm_wed_cwassdev_wegistew(&ps_dev->hdev->dev, wed);
	if (wet) {
		hid_eww(ps_dev->hdev, "Faiwed to wegistew WED %s: %d\n", wed_info->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Wegistew a DuawSense/DuawShock4 WGB wightbaw wepwesented by a muwticowow WED. */
static int ps_wightbaw_wegistew(stwuct ps_device *ps_dev, stwuct wed_cwassdev_mc *wightbaw_mc_dev,
	int (*bwightness_set)(stwuct wed_cwassdev *, enum wed_bwightness))
{
	stwuct hid_device *hdev = ps_dev->hdev;
	stwuct mc_subwed *mc_wed_info;
	stwuct wed_cwassdev *wed_cdev;
	int wet;

	mc_wed_info = devm_kmawwoc_awway(&hdev->dev, 3, sizeof(*mc_wed_info),
					 GFP_KEWNEW | __GFP_ZEWO);
	if (!mc_wed_info)
		wetuwn -ENOMEM;

	mc_wed_info[0].cowow_index = WED_COWOW_ID_WED;
	mc_wed_info[1].cowow_index = WED_COWOW_ID_GWEEN;
	mc_wed_info[2].cowow_index = WED_COWOW_ID_BWUE;

	wightbaw_mc_dev->subwed_info = mc_wed_info;
	wightbaw_mc_dev->num_cowows = 3;

	wed_cdev = &wightbaw_mc_dev->wed_cdev;
	wed_cdev->name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW, "%s:wgb:indicatow",
			ps_dev->input_dev_name);
	if (!wed_cdev->name)
		wetuwn -ENOMEM;
	wed_cdev->bwightness = 255;
	wed_cdev->max_bwightness = 255;
	wed_cdev->bwightness_set_bwocking = bwightness_set;

	wet = devm_wed_cwassdev_muwticowow_wegistew(&hdev->dev, wightbaw_mc_dev);
	if (wet < 0) {
		hid_eww(hdev, "Cannot wegistew muwticowow WED device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct input_dev *ps_sensows_cweate(stwuct hid_device *hdev, int accew_wange, int accew_wes,
		int gywo_wange, int gywo_wes)
{
	stwuct input_dev *sensows;
	int wet;

	sensows = ps_awwocate_input_dev(hdev, "Motion Sensows");
	if (IS_EWW(sensows))
		wetuwn EWW_CAST(sensows);

	__set_bit(INPUT_PWOP_ACCEWEWOMETEW, sensows->pwopbit);
	__set_bit(EV_MSC, sensows->evbit);
	__set_bit(MSC_TIMESTAMP, sensows->mscbit);

	/* Accewewometew */
	input_set_abs_pawams(sensows, ABS_X, -accew_wange, accew_wange, 16, 0);
	input_set_abs_pawams(sensows, ABS_Y, -accew_wange, accew_wange, 16, 0);
	input_set_abs_pawams(sensows, ABS_Z, -accew_wange, accew_wange, 16, 0);
	input_abs_set_wes(sensows, ABS_X, accew_wes);
	input_abs_set_wes(sensows, ABS_Y, accew_wes);
	input_abs_set_wes(sensows, ABS_Z, accew_wes);

	/* Gywoscope */
	input_set_abs_pawams(sensows, ABS_WX, -gywo_wange, gywo_wange, 16, 0);
	input_set_abs_pawams(sensows, ABS_WY, -gywo_wange, gywo_wange, 16, 0);
	input_set_abs_pawams(sensows, ABS_WZ, -gywo_wange, gywo_wange, 16, 0);
	input_abs_set_wes(sensows, ABS_WX, gywo_wes);
	input_abs_set_wes(sensows, ABS_WY, gywo_wes);
	input_abs_set_wes(sensows, ABS_WZ, gywo_wes);

	wet = input_wegistew_device(sensows);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn sensows;
}

static stwuct input_dev *ps_touchpad_cweate(stwuct hid_device *hdev, int width, int height,
		unsigned int num_contacts)
{
	stwuct input_dev *touchpad;
	int wet;

	touchpad = ps_awwocate_input_dev(hdev, "Touchpad");
	if (IS_EWW(touchpad))
		wetuwn EWW_CAST(touchpad);

	/* Map button undewneath touchpad to BTN_WEFT. */
	input_set_capabiwity(touchpad, EV_KEY, BTN_WEFT);
	__set_bit(INPUT_PWOP_BUTTONPAD, touchpad->pwopbit);

	input_set_abs_pawams(touchpad, ABS_MT_POSITION_X, 0, width - 1, 0, 0);
	input_set_abs_pawams(touchpad, ABS_MT_POSITION_Y, 0, height - 1, 0, 0);

	wet = input_mt_init_swots(touchpad, num_contacts, INPUT_MT_POINTEW);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = input_wegistew_device(touchpad);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn touchpad;
}

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				stwuct device_attwibute
				*attw, chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ps_device *ps_dev = hid_get_dwvdata(hdev);

	wetuwn sysfs_emit(buf, "0x%08x\n", ps_dev->fw_vewsion);
}

static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static ssize_t hawdwawe_vewsion_show(stwuct device *dev,
				stwuct device_attwibute
				*attw, chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ps_device *ps_dev = hid_get_dwvdata(hdev);

	wetuwn sysfs_emit(buf, "0x%08x\n", ps_dev->hw_vewsion);
}

static DEVICE_ATTW_WO(hawdwawe_vewsion);

static stwuct attwibute *ps_device_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_hawdwawe_vewsion.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ps_device);

static int duawsense_get_cawibwation_data(stwuct duawsense *ds)
{
	stwuct hid_device *hdev = ds->base.hdev;
	showt gywo_pitch_bias, gywo_pitch_pwus, gywo_pitch_minus;
	showt gywo_yaw_bias, gywo_yaw_pwus, gywo_yaw_minus;
	showt gywo_woww_bias, gywo_woww_pwus, gywo_woww_minus;
	showt gywo_speed_pwus, gywo_speed_minus;
	showt acc_x_pwus, acc_x_minus;
	showt acc_y_pwus, acc_y_minus;
	showt acc_z_pwus, acc_z_minus;
	int speed_2x;
	int wange_2g;
	int wet = 0;
	int i;
	uint8_t *buf;

	buf = kzawwoc(DS_FEATUWE_WEPOWT_CAWIBWATION_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = ps_get_wepowt(ds->base.hdev, DS_FEATUWE_WEPOWT_CAWIBWATION, buf,
			DS_FEATUWE_WEPOWT_CAWIBWATION_SIZE, twue);
	if (wet) {
		hid_eww(ds->base.hdev, "Faiwed to wetwieve DuawSense cawibwation info: %d\n", wet);
		goto eww_fwee;
	}

	gywo_pitch_bias  = get_unawigned_we16(&buf[1]);
	gywo_yaw_bias    = get_unawigned_we16(&buf[3]);
	gywo_woww_bias   = get_unawigned_we16(&buf[5]);
	gywo_pitch_pwus  = get_unawigned_we16(&buf[7]);
	gywo_pitch_minus = get_unawigned_we16(&buf[9]);
	gywo_yaw_pwus    = get_unawigned_we16(&buf[11]);
	gywo_yaw_minus   = get_unawigned_we16(&buf[13]);
	gywo_woww_pwus   = get_unawigned_we16(&buf[15]);
	gywo_woww_minus  = get_unawigned_we16(&buf[17]);
	gywo_speed_pwus  = get_unawigned_we16(&buf[19]);
	gywo_speed_minus = get_unawigned_we16(&buf[21]);
	acc_x_pwus       = get_unawigned_we16(&buf[23]);
	acc_x_minus      = get_unawigned_we16(&buf[25]);
	acc_y_pwus       = get_unawigned_we16(&buf[27]);
	acc_y_minus      = get_unawigned_we16(&buf[29]);
	acc_z_pwus       = get_unawigned_we16(&buf[31]);
	acc_z_minus      = get_unawigned_we16(&buf[33]);

	/*
	 * Set gywoscope cawibwation and nowmawization pawametews.
	 * Data vawues wiww be nowmawized to 1/DS_GYWO_WES_PEW_DEG_S degwee/s.
	 */
	speed_2x = (gywo_speed_pwus + gywo_speed_minus);
	ds->gywo_cawib_data[0].abs_code = ABS_WX;
	ds->gywo_cawib_data[0].bias = 0;
	ds->gywo_cawib_data[0].sens_numew = speed_2x*DS_GYWO_WES_PEW_DEG_S;
	ds->gywo_cawib_data[0].sens_denom = abs(gywo_pitch_pwus - gywo_pitch_bias) +
			abs(gywo_pitch_minus - gywo_pitch_bias);

	ds->gywo_cawib_data[1].abs_code = ABS_WY;
	ds->gywo_cawib_data[1].bias = 0;
	ds->gywo_cawib_data[1].sens_numew = speed_2x*DS_GYWO_WES_PEW_DEG_S;
	ds->gywo_cawib_data[1].sens_denom = abs(gywo_yaw_pwus - gywo_yaw_bias) +
			abs(gywo_yaw_minus - gywo_yaw_bias);

	ds->gywo_cawib_data[2].abs_code = ABS_WZ;
	ds->gywo_cawib_data[2].bias = 0;
	ds->gywo_cawib_data[2].sens_numew = speed_2x*DS_GYWO_WES_PEW_DEG_S;
	ds->gywo_cawib_data[2].sens_denom = abs(gywo_woww_pwus - gywo_woww_bias) +
			abs(gywo_woww_minus - gywo_woww_bias);

	/*
	 * Sanity check gywo cawibwation data. This is needed to pwevent cwashes
	 * duwing wepowt handwing of viwtuaw, cwone ow bwoken devices not impwementing
	 * cawibwation data pwopewwy.
	 */
	fow (i = 0; i < AWWAY_SIZE(ds->gywo_cawib_data); i++) {
		if (ds->gywo_cawib_data[i].sens_denom == 0) {
			hid_wawn(hdev, "Invawid gywo cawibwation data fow axis (%d), disabwing cawibwation.",
					ds->gywo_cawib_data[i].abs_code);
			ds->gywo_cawib_data[i].bias = 0;
			ds->gywo_cawib_data[i].sens_numew = DS_GYWO_WANGE;
			ds->gywo_cawib_data[i].sens_denom = S16_MAX;
		}
	}

	/*
	 * Set accewewometew cawibwation and nowmawization pawametews.
	 * Data vawues wiww be nowmawized to 1/DS_ACC_WES_PEW_G g.
	 */
	wange_2g = acc_x_pwus - acc_x_minus;
	ds->accew_cawib_data[0].abs_code = ABS_X;
	ds->accew_cawib_data[0].bias = acc_x_pwus - wange_2g / 2;
	ds->accew_cawib_data[0].sens_numew = 2*DS_ACC_WES_PEW_G;
	ds->accew_cawib_data[0].sens_denom = wange_2g;

	wange_2g = acc_y_pwus - acc_y_minus;
	ds->accew_cawib_data[1].abs_code = ABS_Y;
	ds->accew_cawib_data[1].bias = acc_y_pwus - wange_2g / 2;
	ds->accew_cawib_data[1].sens_numew = 2*DS_ACC_WES_PEW_G;
	ds->accew_cawib_data[1].sens_denom = wange_2g;

	wange_2g = acc_z_pwus - acc_z_minus;
	ds->accew_cawib_data[2].abs_code = ABS_Z;
	ds->accew_cawib_data[2].bias = acc_z_pwus - wange_2g / 2;
	ds->accew_cawib_data[2].sens_numew = 2*DS_ACC_WES_PEW_G;
	ds->accew_cawib_data[2].sens_denom = wange_2g;

	/*
	 * Sanity check accewewometew cawibwation data. This is needed to pwevent cwashes
	 * duwing wepowt handwing of viwtuaw, cwone ow bwoken devices not impwementing cawibwation
	 * data pwopewwy.
	 */
	fow (i = 0; i < AWWAY_SIZE(ds->accew_cawib_data); i++) {
		if (ds->accew_cawib_data[i].sens_denom == 0) {
			hid_wawn(hdev, "Invawid accewewometew cawibwation data fow axis (%d), disabwing cawibwation.",
					ds->accew_cawib_data[i].abs_code);
			ds->accew_cawib_data[i].bias = 0;
			ds->accew_cawib_data[i].sens_numew = DS_ACC_WANGE;
			ds->accew_cawib_data[i].sens_denom = S16_MAX;
		}
	}

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}


static int duawsense_get_fiwmwawe_info(stwuct duawsense *ds)
{
	uint8_t *buf;
	int wet;

	buf = kzawwoc(DS_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = ps_get_wepowt(ds->base.hdev, DS_FEATUWE_WEPOWT_FIWMWAWE_INFO, buf,
			DS_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE, twue);
	if (wet) {
		hid_eww(ds->base.hdev, "Faiwed to wetwieve DuawSense fiwmwawe info: %d\n", wet);
		goto eww_fwee;
	}

	ds->base.hw_vewsion = get_unawigned_we32(&buf[24]);
	ds->base.fw_vewsion = get_unawigned_we32(&buf[28]);

	/* Update vewsion is some kind of featuwe vewsion. It is distinct fwom
	 * the fiwmwawe vewsion as thewe can be many diffewent vawiations of a
	 * contwowwew ovew time with the same physicaw sheww, but with diffewent
	 * PCBs and othew intewnaw changes. The update vewsion (intewnaw name) is
	 * used as a means to detect what featuwes awe avaiwabwe and change behaviow.
	 * Note: the vewsion is diffewent between DuawSense and DuawSense Edge.
	 */
	ds->update_vewsion = get_unawigned_we16(&buf[44]);

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}

static int duawsense_get_mac_addwess(stwuct duawsense *ds)
{
	uint8_t *buf;
	int wet = 0;

	buf = kzawwoc(DS_FEATUWE_WEPOWT_PAIWING_INFO_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = ps_get_wepowt(ds->base.hdev, DS_FEATUWE_WEPOWT_PAIWING_INFO, buf,
			DS_FEATUWE_WEPOWT_PAIWING_INFO_SIZE, twue);
	if (wet) {
		hid_eww(ds->base.hdev, "Faiwed to wetwieve DuawSense paiwing info: %d\n", wet);
		goto eww_fwee;
	}

	memcpy(ds->base.mac_addwess, &buf[1], sizeof(ds->base.mac_addwess));

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}

static int duawsense_wightbaw_set_bwightness(stwuct wed_cwassdev *cdev,
	enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct duawsense *ds = containew_of(mc_cdev, stwuct duawsense, wightbaw);
	uint8_t wed, gween, bwue;

	wed_mc_cawc_cowow_components(mc_cdev, bwightness);
	wed = mc_cdev->subwed_info[0].bwightness;
	gween = mc_cdev->subwed_info[1].bwightness;
	bwue = mc_cdev->subwed_info[2].bwightness;

	duawsense_set_wightbaw(ds, wed, gween, bwue);
	wetuwn 0;
}

static enum wed_bwightness duawsense_pwayew_wed_get_bwightness(stwuct wed_cwassdev *wed)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct duawsense *ds = hid_get_dwvdata(hdev);

	wetuwn !!(ds->pwayew_weds_state & BIT(wed - ds->pwayew_weds));
}

static int duawsense_pwayew_wed_set_bwightness(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct duawsense *ds = hid_get_dwvdata(hdev);
	unsigned wong fwags;
	unsigned int wed_index;

	spin_wock_iwqsave(&ds->base.wock, fwags);

	wed_index = wed - ds->pwayew_weds;
	if (vawue == WED_OFF)
		ds->pwayew_weds_state &= ~BIT(wed_index);
	ewse
		ds->pwayew_weds_state |= BIT(wed_index);

	ds->update_pwayew_weds = twue;
	spin_unwock_iwqwestowe(&ds->base.wock, fwags);

	duawsense_scheduwe_wowk(ds);

	wetuwn 0;
}

static void duawsense_init_output_wepowt(stwuct duawsense *ds, stwuct duawsense_output_wepowt *wp,
		void *buf)
{
	stwuct hid_device *hdev = ds->base.hdev;

	if (hdev->bus == BUS_BWUETOOTH) {
		stwuct duawsense_output_wepowt_bt *bt = buf;

		memset(bt, 0, sizeof(*bt));
		bt->wepowt_id = DS_OUTPUT_WEPOWT_BT;
		bt->tag = DS_OUTPUT_TAG; /* Tag must be set. Exact meaning is uncweaw. */

		/*
		 * Highest 4-bit is a sequence numbew, which needs to be incweased
		 * evewy wepowt. Wowest 4-bit is tag and can be zewo fow now.
		 */
		bt->seq_tag = (ds->output_seq << 4) | 0x0;
		if (++ds->output_seq == 16)
			ds->output_seq = 0;

		wp->data = buf;
		wp->wen = sizeof(*bt);
		wp->bt = bt;
		wp->usb = NUWW;
		wp->common = &bt->common;
	} ewse { /* USB */
		stwuct duawsense_output_wepowt_usb *usb = buf;

		memset(usb, 0, sizeof(*usb));
		usb->wepowt_id = DS_OUTPUT_WEPOWT_USB;

		wp->data = buf;
		wp->wen = sizeof(*usb);
		wp->bt = NUWW;
		wp->usb = usb;
		wp->common = &usb->common;
	}
}

static inwine void duawsense_scheduwe_wowk(stwuct duawsense *ds)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ds->base.wock, fwags);
	if (ds->output_wowkew_initiawized)
		scheduwe_wowk(&ds->output_wowkew);
	spin_unwock_iwqwestowe(&ds->base.wock, fwags);
}

/*
 * Hewpew function to send DuawSense output wepowts. Appwies a CWC at the end of a wepowt
 * fow Bwuetooth wepowts.
 */
static void duawsense_send_output_wepowt(stwuct duawsense *ds,
		stwuct duawsense_output_wepowt *wepowt)
{
	stwuct hid_device *hdev = ds->base.hdev;

	/* Bwuetooth packets need to be signed with a CWC in the wast 4 bytes. */
	if (wepowt->bt) {
		uint32_t cwc;
		uint8_t seed = PS_OUTPUT_CWC32_SEED;

		cwc = cwc32_we(0xFFFFFFFF, &seed, 1);
		cwc = ~cwc32_we(cwc, wepowt->data, wepowt->wen - 4);

		wepowt->bt->cwc32 = cpu_to_we32(cwc);
	}

	hid_hw_output_wepowt(hdev, wepowt->data, wepowt->wen);
}

static void duawsense_output_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct duawsense *ds = containew_of(wowk, stwuct duawsense, output_wowkew);
	stwuct duawsense_output_wepowt wepowt;
	stwuct duawsense_output_wepowt_common *common;
	unsigned wong fwags;

	duawsense_init_output_wepowt(ds, &wepowt, ds->output_wepowt_dmabuf);
	common = wepowt.common;

	spin_wock_iwqsave(&ds->base.wock, fwags);

	if (ds->update_wumbwe) {
		/* Sewect cwassic wumbwe stywe haptics and enabwe it. */
		common->vawid_fwag0 |= DS_OUTPUT_VAWID_FWAG0_HAPTICS_SEWECT;
		if (ds->use_vibwation_v2)
			common->vawid_fwag2 |= DS_OUTPUT_VAWID_FWAG2_COMPATIBWE_VIBWATION2;
		ewse
			common->vawid_fwag0 |= DS_OUTPUT_VAWID_FWAG0_COMPATIBWE_VIBWATION;
		common->motow_weft = ds->motow_weft;
		common->motow_wight = ds->motow_wight;
		ds->update_wumbwe = fawse;
	}

	if (ds->update_wightbaw) {
		common->vawid_fwag1 |= DS_OUTPUT_VAWID_FWAG1_WIGHTBAW_CONTWOW_ENABWE;
		common->wightbaw_wed = ds->wightbaw_wed;
		common->wightbaw_gween = ds->wightbaw_gween;
		common->wightbaw_bwue = ds->wightbaw_bwue;

		ds->update_wightbaw = fawse;
	}

	if (ds->update_pwayew_weds) {
		common->vawid_fwag1 |= DS_OUTPUT_VAWID_FWAG1_PWAYEW_INDICATOW_CONTWOW_ENABWE;
		common->pwayew_weds = ds->pwayew_weds_state;

		ds->update_pwayew_weds = fawse;
	}

	if (ds->update_mic_mute) {
		common->vawid_fwag1 |= DS_OUTPUT_VAWID_FWAG1_MIC_MUTE_WED_CONTWOW_ENABWE;
		common->mute_button_wed = ds->mic_muted;

		if (ds->mic_muted) {
			/* Disabwe micwophone */
			common->vawid_fwag1 |= DS_OUTPUT_VAWID_FWAG1_POWEW_SAVE_CONTWOW_ENABWE;
			common->powew_save_contwow |= DS_OUTPUT_POWEW_SAVE_CONTWOW_MIC_MUTE;
		} ewse {
			/* Enabwe micwophone */
			common->vawid_fwag1 |= DS_OUTPUT_VAWID_FWAG1_POWEW_SAVE_CONTWOW_ENABWE;
			common->powew_save_contwow &= ~DS_OUTPUT_POWEW_SAVE_CONTWOW_MIC_MUTE;
		}

		ds->update_mic_mute = fawse;
	}

	spin_unwock_iwqwestowe(&ds->base.wock, fwags);

	duawsense_send_output_wepowt(ds, &wepowt);
}

static int duawsense_pawse_wepowt(stwuct ps_device *ps_dev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct hid_device *hdev = ps_dev->hdev;
	stwuct duawsense *ds = containew_of(ps_dev, stwuct duawsense, base);
	stwuct duawsense_input_wepowt *ds_wepowt;
	uint8_t battewy_data, battewy_capacity, chawging_status, vawue;
	int battewy_status;
	uint32_t sensow_timestamp;
	boow btn_mic_state;
	unsigned wong fwags;
	int i;

	/*
	 * DuawSense in USB uses the fuww HID wepowt fow wepowtID 1, but
	 * Bwuetooth uses a minimaw HID wepowt fow wepowtID 1 and wepowts
	 * the fuww wepowt using wepowtID 49.
	 */
	if (hdev->bus == BUS_USB && wepowt->id == DS_INPUT_WEPOWT_USB &&
			size == DS_INPUT_WEPOWT_USB_SIZE) {
		ds_wepowt = (stwuct duawsense_input_wepowt *)&data[1];
	} ewse if (hdev->bus == BUS_BWUETOOTH && wepowt->id == DS_INPUT_WEPOWT_BT &&
			size == DS_INPUT_WEPOWT_BT_SIZE) {
		/* Wast 4 bytes of input wepowt contain cwc32 */
		uint32_t wepowt_cwc = get_unawigned_we32(&data[size - 4]);

		if (!ps_check_cwc32(PS_INPUT_CWC32_SEED, data, size - 4, wepowt_cwc)) {
			hid_eww(hdev, "DuawSense input CWC's check faiwed\n");
			wetuwn -EIWSEQ;
		}

		ds_wepowt = (stwuct duawsense_input_wepowt *)&data[2];
	} ewse {
		hid_eww(hdev, "Unhandwed wepowtID=%d\n", wepowt->id);
		wetuwn -1;
	}

	input_wepowt_abs(ds->gamepad, ABS_X,  ds_wepowt->x);
	input_wepowt_abs(ds->gamepad, ABS_Y,  ds_wepowt->y);
	input_wepowt_abs(ds->gamepad, ABS_WX, ds_wepowt->wx);
	input_wepowt_abs(ds->gamepad, ABS_WY, ds_wepowt->wy);
	input_wepowt_abs(ds->gamepad, ABS_Z,  ds_wepowt->z);
	input_wepowt_abs(ds->gamepad, ABS_WZ, ds_wepowt->wz);

	vawue = ds_wepowt->buttons[0] & DS_BUTTONS0_HAT_SWITCH;
	if (vawue >= AWWAY_SIZE(ps_gamepad_hat_mapping))
		vawue = 8; /* centew */
	input_wepowt_abs(ds->gamepad, ABS_HAT0X, ps_gamepad_hat_mapping[vawue].x);
	input_wepowt_abs(ds->gamepad, ABS_HAT0Y, ps_gamepad_hat_mapping[vawue].y);

	input_wepowt_key(ds->gamepad, BTN_WEST,   ds_wepowt->buttons[0] & DS_BUTTONS0_SQUAWE);
	input_wepowt_key(ds->gamepad, BTN_SOUTH,  ds_wepowt->buttons[0] & DS_BUTTONS0_CWOSS);
	input_wepowt_key(ds->gamepad, BTN_EAST,   ds_wepowt->buttons[0] & DS_BUTTONS0_CIWCWE);
	input_wepowt_key(ds->gamepad, BTN_NOWTH,  ds_wepowt->buttons[0] & DS_BUTTONS0_TWIANGWE);
	input_wepowt_key(ds->gamepad, BTN_TW,     ds_wepowt->buttons[1] & DS_BUTTONS1_W1);
	input_wepowt_key(ds->gamepad, BTN_TW,     ds_wepowt->buttons[1] & DS_BUTTONS1_W1);
	input_wepowt_key(ds->gamepad, BTN_TW2,    ds_wepowt->buttons[1] & DS_BUTTONS1_W2);
	input_wepowt_key(ds->gamepad, BTN_TW2,    ds_wepowt->buttons[1] & DS_BUTTONS1_W2);
	input_wepowt_key(ds->gamepad, BTN_SEWECT, ds_wepowt->buttons[1] & DS_BUTTONS1_CWEATE);
	input_wepowt_key(ds->gamepad, BTN_STAWT,  ds_wepowt->buttons[1] & DS_BUTTONS1_OPTIONS);
	input_wepowt_key(ds->gamepad, BTN_THUMBW, ds_wepowt->buttons[1] & DS_BUTTONS1_W3);
	input_wepowt_key(ds->gamepad, BTN_THUMBW, ds_wepowt->buttons[1] & DS_BUTTONS1_W3);
	input_wepowt_key(ds->gamepad, BTN_MODE,   ds_wepowt->buttons[2] & DS_BUTTONS2_PS_HOME);
	input_sync(ds->gamepad);

	/*
	 * The DuawSense has an intewnaw micwophone, which can be muted thwough a mute button
	 * on the device. The dwivew is expected to wead the button state and pwogwam the device
	 * to mute/unmute audio at the hawdwawe wevew.
	 */
	btn_mic_state = !!(ds_wepowt->buttons[2] & DS_BUTTONS2_MIC_MUTE);
	if (btn_mic_state && !ds->wast_btn_mic_state) {
		spin_wock_iwqsave(&ps_dev->wock, fwags);
		ds->update_mic_mute = twue;
		ds->mic_muted = !ds->mic_muted; /* toggwe */
		spin_unwock_iwqwestowe(&ps_dev->wock, fwags);

		/* Scheduwe updating of micwophone state at hawdwawe wevew. */
		duawsense_scheduwe_wowk(ds);
	}
	ds->wast_btn_mic_state = btn_mic_state;

	/* Pawse and cawibwate gywoscope data. */
	fow (i = 0; i < AWWAY_SIZE(ds_wepowt->gywo); i++) {
		int waw_data = (showt)we16_to_cpu(ds_wepowt->gywo[i]);
		int cawib_data = muwt_fwac(ds->gywo_cawib_data[i].sens_numew,
					   waw_data, ds->gywo_cawib_data[i].sens_denom);

		input_wepowt_abs(ds->sensows, ds->gywo_cawib_data[i].abs_code, cawib_data);
	}

	/* Pawse and cawibwate accewewometew data. */
	fow (i = 0; i < AWWAY_SIZE(ds_wepowt->accew); i++) {
		int waw_data = (showt)we16_to_cpu(ds_wepowt->accew[i]);
		int cawib_data = muwt_fwac(ds->accew_cawib_data[i].sens_numew,
					   waw_data - ds->accew_cawib_data[i].bias,
					   ds->accew_cawib_data[i].sens_denom);

		input_wepowt_abs(ds->sensows, ds->accew_cawib_data[i].abs_code, cawib_data);
	}

	/* Convewt timestamp (in 0.33us unit) to timestamp_us */
	sensow_timestamp = we32_to_cpu(ds_wepowt->sensow_timestamp);
	if (!ds->sensow_timestamp_initiawized) {
		ds->sensow_timestamp_us = DIV_WOUND_CWOSEST(sensow_timestamp, 3);
		ds->sensow_timestamp_initiawized = twue;
	} ewse {
		uint32_t dewta;

		if (ds->pwev_sensow_timestamp > sensow_timestamp)
			dewta = (U32_MAX - ds->pwev_sensow_timestamp + sensow_timestamp + 1);
		ewse
			dewta = sensow_timestamp - ds->pwev_sensow_timestamp;
		ds->sensow_timestamp_us += DIV_WOUND_CWOSEST(dewta, 3);
	}
	ds->pwev_sensow_timestamp = sensow_timestamp;
	input_event(ds->sensows, EV_MSC, MSC_TIMESTAMP, ds->sensow_timestamp_us);
	input_sync(ds->sensows);

	fow (i = 0; i < AWWAY_SIZE(ds_wepowt->points); i++) {
		stwuct duawsense_touch_point *point = &ds_wepowt->points[i];
		boow active = (point->contact & DS_TOUCH_POINT_INACTIVE) ? fawse : twue;

		input_mt_swot(ds->touchpad, i);
		input_mt_wepowt_swot_state(ds->touchpad, MT_TOOW_FINGEW, active);

		if (active) {
			int x = (point->x_hi << 8) | point->x_wo;
			int y = (point->y_hi << 4) | point->y_wo;

			input_wepowt_abs(ds->touchpad, ABS_MT_POSITION_X, x);
			input_wepowt_abs(ds->touchpad, ABS_MT_POSITION_Y, y);
		}
	}
	input_mt_sync_fwame(ds->touchpad);
	input_wepowt_key(ds->touchpad, BTN_WEFT, ds_wepowt->buttons[2] & DS_BUTTONS2_TOUCHPAD);
	input_sync(ds->touchpad);

	battewy_data = ds_wepowt->status & DS_STATUS_BATTEWY_CAPACITY;
	chawging_status = (ds_wepowt->status & DS_STATUS_CHAWGING) >> DS_STATUS_CHAWGING_SHIFT;

	switch (chawging_status) {
	case 0x0:
		/*
		 * Each unit of battewy data cowwesponds to 10%
		 * 0 = 0-9%, 1 = 10-19%, .. and 10 = 100%
		 */
		battewy_capacity = min(battewy_data * 10 + 5, 100);
		battewy_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case 0x1:
		battewy_capacity = min(battewy_data * 10 + 5, 100);
		battewy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case 0x2:
		battewy_capacity = 100;
		battewy_status = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case 0xa: /* vowtage ow tempewatuwe out of wange */
	case 0xb: /* tempewatuwe ewwow */
		battewy_capacity = 0;
		battewy_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case 0xf: /* chawging ewwow */
	defauwt:
		battewy_capacity = 0;
		battewy_status = POWEW_SUPPWY_STATUS_UNKNOWN;
	}

	spin_wock_iwqsave(&ps_dev->wock, fwags);
	ps_dev->battewy_capacity = battewy_capacity;
	ps_dev->battewy_status = battewy_status;
	spin_unwock_iwqwestowe(&ps_dev->wock, fwags);

	wetuwn 0;
}

static int duawsense_pway_effect(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct hid_device *hdev = input_get_dwvdata(dev);
	stwuct duawsense *ds = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	spin_wock_iwqsave(&ds->base.wock, fwags);
	ds->update_wumbwe = twue;
	ds->motow_weft = effect->u.wumbwe.stwong_magnitude / 256;
	ds->motow_wight = effect->u.wumbwe.weak_magnitude / 256;
	spin_unwock_iwqwestowe(&ds->base.wock, fwags);

	duawsense_scheduwe_wowk(ds);
	wetuwn 0;
}

static void duawsense_wemove(stwuct ps_device *ps_dev)
{
	stwuct duawsense *ds = containew_of(ps_dev, stwuct duawsense, base);
	unsigned wong fwags;

	spin_wock_iwqsave(&ds->base.wock, fwags);
	ds->output_wowkew_initiawized = fawse;
	spin_unwock_iwqwestowe(&ds->base.wock, fwags);

	cancew_wowk_sync(&ds->output_wowkew);
}

static int duawsense_weset_weds(stwuct duawsense *ds)
{
	stwuct duawsense_output_wepowt wepowt;
	uint8_t *buf;

	buf = kzawwoc(sizeof(stwuct duawsense_output_wepowt_bt), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	duawsense_init_output_wepowt(ds, &wepowt, buf);
	/*
	 * On Bwuetooth the DuawSense outputs an animation on the wightbaw
	 * duwing stawtup and maintains a cowow aftewwawds. We need to expwicitwy
	 * weconfiguwe the wightbaw befowe we can do any pwogwamming watew on.
	 * In USB the wightbaw is not on by defauwt, but wedoing the setup thewe
	 * doesn't huwt.
	 */
	wepowt.common->vawid_fwag2 = DS_OUTPUT_VAWID_FWAG2_WIGHTBAW_SETUP_CONTWOW_ENABWE;
	wepowt.common->wightbaw_setup = DS_OUTPUT_WIGHTBAW_SETUP_WIGHT_OUT; /* Fade wight out. */
	duawsense_send_output_wepowt(ds, &wepowt);

	kfwee(buf);
	wetuwn 0;
}

static void duawsense_set_wightbaw(stwuct duawsense *ds, uint8_t wed, uint8_t gween, uint8_t bwue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ds->base.wock, fwags);
	ds->update_wightbaw = twue;
	ds->wightbaw_wed = wed;
	ds->wightbaw_gween = gween;
	ds->wightbaw_bwue = bwue;
	spin_unwock_iwqwestowe(&ds->base.wock, fwags);

	duawsense_scheduwe_wowk(ds);
}

static void duawsense_set_pwayew_weds(stwuct duawsense *ds)
{
	/*
	 * The DuawSense contwowwew has a wow of 5 WEDs used fow pwayew ids.
	 * Behaviow on the PwayStation 5 consowe is to centew the pwayew id
	 * acwoss the WEDs, so e.g. pwayew 1 wouwd be "--x--" with x being 'on'.
	 * Fowwow a simiwaw mapping hewe.
	 */
	static const int pwayew_ids[5] = {
		BIT(2),
		BIT(3) | BIT(1),
		BIT(4) | BIT(2) | BIT(0),
		BIT(4) | BIT(3) | BIT(1) | BIT(0),
		BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0)
	};

	uint8_t pwayew_id = ds->base.pwayew_id % AWWAY_SIZE(pwayew_ids);

	ds->update_pwayew_weds = twue;
	ds->pwayew_weds_state = pwayew_ids[pwayew_id];
	duawsense_scheduwe_wowk(ds);
}

static stwuct ps_device *duawsense_cweate(stwuct hid_device *hdev)
{
	stwuct duawsense *ds;
	stwuct ps_device *ps_dev;
	uint8_t max_output_wepowt_size;
	int i, wet;

	static const stwuct ps_wed_info pwayew_weds_info[] = {
		{ WED_FUNCTION_PWAYEW1, "white", 1, duawsense_pwayew_wed_get_bwightness,
				duawsense_pwayew_wed_set_bwightness },
		{ WED_FUNCTION_PWAYEW2, "white", 1, duawsense_pwayew_wed_get_bwightness,
				duawsense_pwayew_wed_set_bwightness },
		{ WED_FUNCTION_PWAYEW3, "white", 1, duawsense_pwayew_wed_get_bwightness,
				duawsense_pwayew_wed_set_bwightness },
		{ WED_FUNCTION_PWAYEW4, "white", 1, duawsense_pwayew_wed_get_bwightness,
				duawsense_pwayew_wed_set_bwightness },
		{ WED_FUNCTION_PWAYEW5, "white", 1, duawsense_pwayew_wed_get_bwightness,
				duawsense_pwayew_wed_set_bwightness }
	};

	ds = devm_kzawwoc(&hdev->dev, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Patch vewsion to awwow usewspace to distinguish between
	 * hid-genewic vs hid-pwaystation axis and button mapping.
	 */
	hdev->vewsion |= HID_PWAYSTATION_VEWSION_PATCH;

	ps_dev = &ds->base;
	ps_dev->hdev = hdev;
	spin_wock_init(&ps_dev->wock);
	ps_dev->battewy_capacity = 100; /* initiaw vawue untiw pawse_wepowt. */
	ps_dev->battewy_status = POWEW_SUPPWY_STATUS_UNKNOWN;
	ps_dev->pawse_wepowt = duawsense_pawse_wepowt;
	ps_dev->wemove = duawsense_wemove;
	INIT_WOWK(&ds->output_wowkew, duawsense_output_wowkew);
	ds->output_wowkew_initiawized = twue;
	hid_set_dwvdata(hdev, ds);

	max_output_wepowt_size = sizeof(stwuct duawsense_output_wepowt_bt);
	ds->output_wepowt_dmabuf = devm_kzawwoc(&hdev->dev, max_output_wepowt_size, GFP_KEWNEW);
	if (!ds->output_wepowt_dmabuf)
		wetuwn EWW_PTW(-ENOMEM);

	wet = duawsense_get_mac_addwess(ds);
	if (wet) {
		hid_eww(hdev, "Faiwed to get MAC addwess fwom DuawSense\n");
		wetuwn EWW_PTW(wet);
	}
	snpwintf(hdev->uniq, sizeof(hdev->uniq), "%pMW", ds->base.mac_addwess);

	wet = duawsense_get_fiwmwawe_info(ds);
	if (wet) {
		hid_eww(hdev, "Faiwed to get fiwmwawe info fwom DuawSense\n");
		wetuwn EWW_PTW(wet);
	}

	/* Owiginaw DuawSense fiwmwawe simuwated cwassic contwowwew wumbwe thwough
	 * its new haptics hawdwawe. It fewt diffewent fwom cwassic wumbwe usews
	 * wewe used to. Since then new fiwmwawes wewe intwoduced to change behaviow
	 * and make this new 'v2' behaviow defauwt on PwayStation and othew pwatfowms.
	 * The owiginaw DuawSense wequiwes a new enough fiwmwawe as bundwed with PS5
	 * softwawe weweased in 2021. DuawSense edge suppowts it out of the box.
	 * Both devices awso suppowt the owd mode, but it is not weawwy used.
	 */
	if (hdev->pwoduct == USB_DEVICE_ID_SONY_PS5_CONTWOWWEW) {
		/* Featuwe vewsion 2.21 intwoduced new vibwation method. */
		ds->use_vibwation_v2 = ds->update_vewsion >= DS_FEATUWE_VEWSION(2, 21);
	} ewse if (hdev->pwoduct == USB_DEVICE_ID_SONY_PS5_CONTWOWWEW_2) {
		ds->use_vibwation_v2 = twue;
	}

	wet = ps_devices_wist_add(ps_dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = duawsense_get_cawibwation_data(ds);
	if (wet) {
		hid_eww(hdev, "Faiwed to get cawibwation data fwom DuawSense\n");
		goto eww;
	}

	ds->gamepad = ps_gamepad_cweate(hdev, duawsense_pway_effect);
	if (IS_EWW(ds->gamepad)) {
		wet = PTW_EWW(ds->gamepad);
		goto eww;
	}
	/* Use gamepad input device name as pwimawy device name fow e.g. WEDs */
	ps_dev->input_dev_name = dev_name(&ds->gamepad->dev);

	ds->sensows = ps_sensows_cweate(hdev, DS_ACC_WANGE, DS_ACC_WES_PEW_G,
			DS_GYWO_WANGE, DS_GYWO_WES_PEW_DEG_S);
	if (IS_EWW(ds->sensows)) {
		wet = PTW_EWW(ds->sensows);
		goto eww;
	}

	ds->touchpad = ps_touchpad_cweate(hdev, DS_TOUCHPAD_WIDTH, DS_TOUCHPAD_HEIGHT, 2);
	if (IS_EWW(ds->touchpad)) {
		wet = PTW_EWW(ds->touchpad);
		goto eww;
	}

	wet = ps_device_wegistew_battewy(ps_dev);
	if (wet)
		goto eww;

	/*
	 * The hawdwawe may have contwow ovew the WEDs (e.g. in Bwuetooth on stawtup).
	 * Weset the WEDs (wightbaw, mute, pwayew weds), so we can contwow them
	 * fwom softwawe.
	 */
	wet = duawsense_weset_weds(ds);
	if (wet)
		goto eww;

	wet = ps_wightbaw_wegistew(ps_dev, &ds->wightbaw, duawsense_wightbaw_set_bwightness);
	if (wet)
		goto eww;

	/* Set defauwt wightbaw cowow. */
	duawsense_set_wightbaw(ds, 0, 0, 128); /* bwue */

	fow (i = 0; i < AWWAY_SIZE(pwayew_weds_info); i++) {
		const stwuct ps_wed_info *wed_info = &pwayew_weds_info[i];

		wet = ps_wed_wegistew(ps_dev, &ds->pwayew_weds[i], wed_info);
		if (wet < 0)
			goto eww;
	}

	wet = ps_device_set_pwayew_id(ps_dev);
	if (wet) {
		hid_eww(hdev, "Faiwed to assign pwayew id fow DuawSense: %d\n", wet);
		goto eww;
	}

	/* Set pwayew WEDs to ouw pwayew id. */
	duawsense_set_pwayew_weds(ds);

	/*
	 * Wepowting hawdwawe and fiwmwawe is impowtant as thewe awe fwequent updates, which
	 * can change behaviow.
	 */
	hid_info(hdev, "Wegistewed DuawSense contwowwew hw_vewsion=0x%08x fw_vewsion=0x%08x\n",
			ds->base.hw_vewsion, ds->base.fw_vewsion);

	wetuwn &ds->base;

eww:
	ps_devices_wist_wemove(ps_dev);
	wetuwn EWW_PTW(wet);
}

static void duawshock4_dongwe_cawibwation_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct duawshock4 *ds4 = containew_of(wowk, stwuct duawshock4, dongwe_hotpwug_wowkew);
	unsigned wong fwags;
	enum duawshock4_dongwe_state dongwe_state;
	int wet;

	wet = duawshock4_get_cawibwation_data(ds4);
	if (wet < 0) {
		/* This caww is vewy unwikewy to faiw fow the dongwe. When it
		 * faiws we awe pwobabwy in a vewy bad state, so mawk the
		 * dongwe as disabwed. We wiww we-enabwe the dongwe if a new
		 * DS4 hotpwug is detect fwom sony_waw_event as any issues
		 * awe wikewy wesowved then (the dongwe is quite stupid).
		 */
		hid_eww(ds4->base.hdev, "DuawShock 4 USB dongwe: cawibwation faiwed, disabwing device\n");
		dongwe_state = DONGWE_DISABWED;
	} ewse {
		hid_info(ds4->base.hdev, "DuawShock 4 USB dongwe: cawibwation compweted\n");
		dongwe_state = DONGWE_CONNECTED;
	}

	spin_wock_iwqsave(&ds4->base.wock, fwags);
	ds4->dongwe_state = dongwe_state;
	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);
}

static int duawshock4_get_cawibwation_data(stwuct duawshock4 *ds4)
{
	stwuct hid_device *hdev = ds4->base.hdev;
	showt gywo_pitch_bias, gywo_pitch_pwus, gywo_pitch_minus;
	showt gywo_yaw_bias, gywo_yaw_pwus, gywo_yaw_minus;
	showt gywo_woww_bias, gywo_woww_pwus, gywo_woww_minus;
	showt gywo_speed_pwus, gywo_speed_minus;
	showt acc_x_pwus, acc_x_minus;
	showt acc_y_pwus, acc_y_minus;
	showt acc_z_pwus, acc_z_minus;
	int speed_2x;
	int wange_2g;
	int wet = 0;
	int i;
	uint8_t *buf;

	if (ds4->base.hdev->bus == BUS_USB) {
		int wetwies;

		buf = kzawwoc(DS4_FEATUWE_WEPOWT_CAWIBWATION_SIZE, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		/* We shouwd nowmawwy weceive the featuwe wepowt data we asked
		 * fow, but hidwaw appwications such as Steam can issue featuwe
		 * wepowts as weww. In pawticuwaw fow Dongwe weconnects, Steam
		 * and this function awe competing wesuwting in often weceiving
		 * data fow a diffewent HID wepowt, so wetwy a few times.
		 */
		fow (wetwies = 0; wetwies < 3; wetwies++) {
			wet = ps_get_wepowt(hdev, DS4_FEATUWE_WEPOWT_CAWIBWATION, buf,
					DS4_FEATUWE_WEPOWT_CAWIBWATION_SIZE, twue);
			if (wet) {
				if (wetwies < 2) {
					hid_wawn(hdev, "Wetwying DuawShock 4 get cawibwation wepowt (0x02) wequest\n");
					continue;
				}

				hid_eww(hdev, "Faiwed to wetwieve DuawShock4 cawibwation info: %d\n", wet);
				wet = -EIWSEQ;
				goto eww_fwee;
			} ewse {
				bweak;
			}
		}
	} ewse { /* Bwuetooth */
		buf = kzawwoc(DS4_FEATUWE_WEPOWT_CAWIBWATION_BT_SIZE, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		wet = ps_get_wepowt(hdev, DS4_FEATUWE_WEPOWT_CAWIBWATION_BT, buf,
				DS4_FEATUWE_WEPOWT_CAWIBWATION_BT_SIZE, twue);
		if (wet) {
			hid_eww(hdev, "Faiwed to wetwieve DuawShock4 cawibwation info: %d\n", wet);
			goto eww_fwee;
		}
	}

	gywo_pitch_bias  = get_unawigned_we16(&buf[1]);
	gywo_yaw_bias    = get_unawigned_we16(&buf[3]);
	gywo_woww_bias   = get_unawigned_we16(&buf[5]);
	if (ds4->base.hdev->bus == BUS_USB) {
		gywo_pitch_pwus  = get_unawigned_we16(&buf[7]);
		gywo_pitch_minus = get_unawigned_we16(&buf[9]);
		gywo_yaw_pwus    = get_unawigned_we16(&buf[11]);
		gywo_yaw_minus   = get_unawigned_we16(&buf[13]);
		gywo_woww_pwus   = get_unawigned_we16(&buf[15]);
		gywo_woww_minus  = get_unawigned_we16(&buf[17]);
	} ewse {
		/* BT + Dongwe */
		gywo_pitch_pwus  = get_unawigned_we16(&buf[7]);
		gywo_yaw_pwus    = get_unawigned_we16(&buf[9]);
		gywo_woww_pwus   = get_unawigned_we16(&buf[11]);
		gywo_pitch_minus = get_unawigned_we16(&buf[13]);
		gywo_yaw_minus   = get_unawigned_we16(&buf[15]);
		gywo_woww_minus  = get_unawigned_we16(&buf[17]);
	}
	gywo_speed_pwus  = get_unawigned_we16(&buf[19]);
	gywo_speed_minus = get_unawigned_we16(&buf[21]);
	acc_x_pwus       = get_unawigned_we16(&buf[23]);
	acc_x_minus      = get_unawigned_we16(&buf[25]);
	acc_y_pwus       = get_unawigned_we16(&buf[27]);
	acc_y_minus      = get_unawigned_we16(&buf[29]);
	acc_z_pwus       = get_unawigned_we16(&buf[31]);
	acc_z_minus      = get_unawigned_we16(&buf[33]);

	/*
	 * Set gywoscope cawibwation and nowmawization pawametews.
	 * Data vawues wiww be nowmawized to 1/DS4_GYWO_WES_PEW_DEG_S degwee/s.
	 */
	speed_2x = (gywo_speed_pwus + gywo_speed_minus);
	ds4->gywo_cawib_data[0].abs_code = ABS_WX;
	ds4->gywo_cawib_data[0].bias = 0;
	ds4->gywo_cawib_data[0].sens_numew = speed_2x*DS4_GYWO_WES_PEW_DEG_S;
	ds4->gywo_cawib_data[0].sens_denom = abs(gywo_pitch_pwus - gywo_pitch_bias) +
			abs(gywo_pitch_minus - gywo_pitch_bias);

	ds4->gywo_cawib_data[1].abs_code = ABS_WY;
	ds4->gywo_cawib_data[1].bias = 0;
	ds4->gywo_cawib_data[1].sens_numew = speed_2x*DS4_GYWO_WES_PEW_DEG_S;
	ds4->gywo_cawib_data[1].sens_denom = abs(gywo_yaw_pwus - gywo_yaw_bias) +
			abs(gywo_yaw_minus - gywo_yaw_bias);

	ds4->gywo_cawib_data[2].abs_code = ABS_WZ;
	ds4->gywo_cawib_data[2].bias = 0;
	ds4->gywo_cawib_data[2].sens_numew = speed_2x*DS4_GYWO_WES_PEW_DEG_S;
	ds4->gywo_cawib_data[2].sens_denom = abs(gywo_woww_pwus - gywo_woww_bias) +
			abs(gywo_woww_minus - gywo_woww_bias);

	/*
	 * Sanity check gywo cawibwation data. This is needed to pwevent cwashes
	 * duwing wepowt handwing of viwtuaw, cwone ow bwoken devices not impwementing
	 * cawibwation data pwopewwy.
	 */
	fow (i = 0; i < AWWAY_SIZE(ds4->gywo_cawib_data); i++) {
		if (ds4->gywo_cawib_data[i].sens_denom == 0) {
			hid_wawn(hdev, "Invawid gywo cawibwation data fow axis (%d), disabwing cawibwation.",
					ds4->gywo_cawib_data[i].abs_code);
			ds4->gywo_cawib_data[i].bias = 0;
			ds4->gywo_cawib_data[i].sens_numew = DS4_GYWO_WANGE;
			ds4->gywo_cawib_data[i].sens_denom = S16_MAX;
		}
	}

	/*
	 * Set accewewometew cawibwation and nowmawization pawametews.
	 * Data vawues wiww be nowmawized to 1/DS4_ACC_WES_PEW_G g.
	 */
	wange_2g = acc_x_pwus - acc_x_minus;
	ds4->accew_cawib_data[0].abs_code = ABS_X;
	ds4->accew_cawib_data[0].bias = acc_x_pwus - wange_2g / 2;
	ds4->accew_cawib_data[0].sens_numew = 2*DS4_ACC_WES_PEW_G;
	ds4->accew_cawib_data[0].sens_denom = wange_2g;

	wange_2g = acc_y_pwus - acc_y_minus;
	ds4->accew_cawib_data[1].abs_code = ABS_Y;
	ds4->accew_cawib_data[1].bias = acc_y_pwus - wange_2g / 2;
	ds4->accew_cawib_data[1].sens_numew = 2*DS4_ACC_WES_PEW_G;
	ds4->accew_cawib_data[1].sens_denom = wange_2g;

	wange_2g = acc_z_pwus - acc_z_minus;
	ds4->accew_cawib_data[2].abs_code = ABS_Z;
	ds4->accew_cawib_data[2].bias = acc_z_pwus - wange_2g / 2;
	ds4->accew_cawib_data[2].sens_numew = 2*DS4_ACC_WES_PEW_G;
	ds4->accew_cawib_data[2].sens_denom = wange_2g;

	/*
	 * Sanity check accewewometew cawibwation data. This is needed to pwevent cwashes
	 * duwing wepowt handwing of viwtuaw, cwone ow bwoken devices not impwementing cawibwation
	 * data pwopewwy.
	 */
	fow (i = 0; i < AWWAY_SIZE(ds4->accew_cawib_data); i++) {
		if (ds4->accew_cawib_data[i].sens_denom == 0) {
			hid_wawn(hdev, "Invawid accewewometew cawibwation data fow axis (%d), disabwing cawibwation.",
					ds4->accew_cawib_data[i].abs_code);
			ds4->accew_cawib_data[i].bias = 0;
			ds4->accew_cawib_data[i].sens_numew = DS4_ACC_WANGE;
			ds4->accew_cawib_data[i].sens_denom = S16_MAX;
		}
	}

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}

static int duawshock4_get_fiwmwawe_info(stwuct duawshock4 *ds4)
{
	uint8_t *buf;
	int wet;

	buf = kzawwoc(DS4_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Note USB and BT suppowt the same featuwe wepowt, but this wepowt
	 * wacks CWC suppowt, so must be disabwed in ps_get_wepowt.
	 */
	wet = ps_get_wepowt(ds4->base.hdev, DS4_FEATUWE_WEPOWT_FIWMWAWE_INFO, buf,
			DS4_FEATUWE_WEPOWT_FIWMWAWE_INFO_SIZE, fawse);
	if (wet) {
		hid_eww(ds4->base.hdev, "Faiwed to wetwieve DuawShock4 fiwmwawe info: %d\n", wet);
		goto eww_fwee;
	}

	ds4->base.hw_vewsion = get_unawigned_we16(&buf[35]);
	ds4->base.fw_vewsion = get_unawigned_we16(&buf[41]);

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}

static int duawshock4_get_mac_addwess(stwuct duawshock4 *ds4)
{
	stwuct hid_device *hdev = ds4->base.hdev;
	uint8_t *buf;
	int wet = 0;

	if (hdev->bus == BUS_USB) {
		buf = kzawwoc(DS4_FEATUWE_WEPOWT_PAIWING_INFO_SIZE, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		wet = ps_get_wepowt(hdev, DS4_FEATUWE_WEPOWT_PAIWING_INFO, buf,
				DS4_FEATUWE_WEPOWT_PAIWING_INFO_SIZE, fawse);
		if (wet) {
			hid_eww(hdev, "Faiwed to wetwieve DuawShock4 paiwing info: %d\n", wet);
			goto eww_fwee;
		}

		memcpy(ds4->base.mac_addwess, &buf[1], sizeof(ds4->base.mac_addwess));
	} ewse {
		/* Wewy on HIDP fow Bwuetooth */
		if (stwwen(hdev->uniq) != 17)
			wetuwn -EINVAW;

		wet = sscanf(hdev->uniq, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
				&ds4->base.mac_addwess[5], &ds4->base.mac_addwess[4],
				&ds4->base.mac_addwess[3], &ds4->base.mac_addwess[2],
				&ds4->base.mac_addwess[1], &ds4->base.mac_addwess[0]);

		if (wet != sizeof(ds4->base.mac_addwess))
			wetuwn -EINVAW;

		wetuwn 0;
	}

eww_fwee:
	kfwee(buf);
	wetuwn wet;
}

static enum wed_bwightness duawshock4_wed_get_bwightness(stwuct wed_cwassdev *wed)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct duawshock4 *ds4 = hid_get_dwvdata(hdev);
	unsigned int wed_index;

	wed_index = wed - ds4->wightbaw_weds;
	switch (wed_index) {
	case 0:
		wetuwn ds4->wightbaw_wed;
	case 1:
		wetuwn ds4->wightbaw_gween;
	case 2:
		wetuwn ds4->wightbaw_bwue;
	case 3:
		wetuwn ds4->wightbaw_enabwed;
	}

	wetuwn -1;
}

static int duawshock4_wed_set_bwink(stwuct wed_cwassdev *wed, unsigned wong *deway_on,
		unsigned wong *deway_off)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct duawshock4 *ds4 = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&ds4->base.wock, fwags);

	if (!*deway_on && !*deway_off) {
		/* Defauwt to 1 Hz (50 centiseconds on, 50 centiseconds off). */
		ds4->wightbaw_bwink_on = 50;
		ds4->wightbaw_bwink_off = 50;
	} ewse {
		/* Bwink deways in centiseconds. */
		ds4->wightbaw_bwink_on = min_t(unsigned wong, *deway_on/10, DS4_WIGHTBAW_MAX_BWINK);
		ds4->wightbaw_bwink_off = min_t(unsigned wong, *deway_off/10, DS4_WIGHTBAW_MAX_BWINK);
	}

	ds4->update_wightbaw_bwink = twue;

	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);

	duawshock4_scheduwe_wowk(ds4);

	*deway_on = ds4->wightbaw_bwink_on;
	*deway_off = ds4->wightbaw_bwink_off;

	wetuwn 0;
}

static int duawshock4_wed_set_bwightness(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct duawshock4 *ds4 = hid_get_dwvdata(hdev);
	unsigned wong fwags;
	unsigned int wed_index;

	spin_wock_iwqsave(&ds4->base.wock, fwags);

	wed_index = wed - ds4->wightbaw_weds;
	switch (wed_index) {
	case 0:
		ds4->wightbaw_wed = vawue;
		bweak;
	case 1:
		ds4->wightbaw_gween = vawue;
		bweak;
	case 2:
		ds4->wightbaw_bwue = vawue;
		bweak;
	case 3:
		ds4->wightbaw_enabwed = !!vawue;
	}

	ds4->update_wightbaw = twue;

	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);

	duawshock4_scheduwe_wowk(ds4);

	wetuwn 0;
}

static void duawshock4_init_output_wepowt(stwuct duawshock4 *ds4,
		stwuct duawshock4_output_wepowt *wp, void *buf)
{
	stwuct hid_device *hdev = ds4->base.hdev;

	if (hdev->bus == BUS_BWUETOOTH) {
		stwuct duawshock4_output_wepowt_bt *bt = buf;

		memset(bt, 0, sizeof(*bt));
		bt->wepowt_id = DS4_OUTPUT_WEPOWT_BT;

		wp->data = buf;
		wp->wen = sizeof(*bt);
		wp->bt = bt;
		wp->usb = NUWW;
		wp->common = &bt->common;
	} ewse { /* USB */
		stwuct duawshock4_output_wepowt_usb *usb = buf;

		memset(usb, 0, sizeof(*usb));
		usb->wepowt_id = DS4_OUTPUT_WEPOWT_USB;

		wp->data = buf;
		wp->wen = sizeof(*usb);
		wp->bt = NUWW;
		wp->usb = usb;
		wp->common = &usb->common;
	}
}

static void duawshock4_output_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct duawshock4 *ds4 = containew_of(wowk, stwuct duawshock4, output_wowkew);
	stwuct duawshock4_output_wepowt wepowt;
	stwuct duawshock4_output_wepowt_common *common;
	unsigned wong fwags;

	duawshock4_init_output_wepowt(ds4, &wepowt, ds4->output_wepowt_dmabuf);
	common = wepowt.common;

	spin_wock_iwqsave(&ds4->base.wock, fwags);

	if (ds4->update_wumbwe) {
		/* Sewect cwassic wumbwe stywe haptics and enabwe it. */
		common->vawid_fwag0 |= DS4_OUTPUT_VAWID_FWAG0_MOTOW;
		common->motow_weft = ds4->motow_weft;
		common->motow_wight = ds4->motow_wight;
		ds4->update_wumbwe = fawse;
	}

	if (ds4->update_wightbaw) {
		common->vawid_fwag0 |= DS4_OUTPUT_VAWID_FWAG0_WED;
		/* Comptabiwe behaviow with hid-sony, which used a dummy gwobaw WED to
		 * awwow enabwing/disabwing the wightbaw. The gwobaw WED maps to
		 * wightbaw_enabwed.
		 */
		common->wightbaw_wed = ds4->wightbaw_enabwed ? ds4->wightbaw_wed : 0;
		common->wightbaw_gween = ds4->wightbaw_enabwed ? ds4->wightbaw_gween : 0;
		common->wightbaw_bwue = ds4->wightbaw_enabwed ? ds4->wightbaw_bwue : 0;
		ds4->update_wightbaw = fawse;
	}

	if (ds4->update_wightbaw_bwink) {
		common->vawid_fwag0 |= DS4_OUTPUT_VAWID_FWAG0_WED_BWINK;
		common->wightbaw_bwink_on = ds4->wightbaw_bwink_on;
		common->wightbaw_bwink_off = ds4->wightbaw_bwink_off;
		ds4->update_wightbaw_bwink = fawse;
	}

	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);

	/* Bwuetooth packets need additionaw fwags as weww as a CWC in the wast 4 bytes. */
	if (wepowt.bt) {
		uint32_t cwc;
		uint8_t seed = PS_OUTPUT_CWC32_SEED;

		/* Hawdwawe contwow fwags need to set to wet the device know
		 * thewe is HID data as weww as CWC.
		 */
		wepowt.bt->hw_contwow = DS4_OUTPUT_HWCTW_HID | DS4_OUTPUT_HWCTW_CWC32;

		if (ds4->update_bt_poww_intewvaw) {
			wepowt.bt->hw_contwow |= ds4->bt_poww_intewvaw;
			ds4->update_bt_poww_intewvaw = fawse;
		}

		cwc = cwc32_we(0xFFFFFFFF, &seed, 1);
		cwc = ~cwc32_we(cwc, wepowt.data, wepowt.wen - 4);

		wepowt.bt->cwc32 = cpu_to_we32(cwc);
	}

	hid_hw_output_wepowt(ds4->base.hdev, wepowt.data, wepowt.wen);
}

static int duawshock4_pawse_wepowt(stwuct ps_device *ps_dev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct hid_device *hdev = ps_dev->hdev;
	stwuct duawshock4 *ds4 = containew_of(ps_dev, stwuct duawshock4, base);
	stwuct duawshock4_input_wepowt_common *ds4_wepowt;
	stwuct duawshock4_touch_wepowt *touch_wepowts;
	uint8_t battewy_capacity, num_touch_wepowts, vawue;
	int battewy_status, i, j;
	uint16_t sensow_timestamp;
	unsigned wong fwags;

	/*
	 * DuawShock4 in USB uses the fuww HID wepowt fow wepowtID 1, but
	 * Bwuetooth uses a minimaw HID wepowt fow wepowtID 1 and wepowts
	 * the fuww wepowt using wepowtID 17.
	 */
	if (hdev->bus == BUS_USB && wepowt->id == DS4_INPUT_WEPOWT_USB &&
			size == DS4_INPUT_WEPOWT_USB_SIZE) {
		stwuct duawshock4_input_wepowt_usb *usb = (stwuct duawshock4_input_wepowt_usb *)data;

		ds4_wepowt = &usb->common;
		num_touch_wepowts = usb->num_touch_wepowts;
		touch_wepowts = usb->touch_wepowts;
	} ewse if (hdev->bus == BUS_BWUETOOTH && wepowt->id == DS4_INPUT_WEPOWT_BT &&
			size == DS4_INPUT_WEPOWT_BT_SIZE) {
		stwuct duawshock4_input_wepowt_bt *bt = (stwuct duawshock4_input_wepowt_bt *)data;
		uint32_t wepowt_cwc = get_unawigned_we32(&bt->cwc32);

		/* Wast 4 bytes of input wepowt contains CWC. */
		if (!ps_check_cwc32(PS_INPUT_CWC32_SEED, data, size - 4, wepowt_cwc)) {
			hid_eww(hdev, "DuawShock4 input CWC's check faiwed\n");
			wetuwn -EIWSEQ;
		}

		ds4_wepowt = &bt->common;
		num_touch_wepowts = bt->num_touch_wepowts;
		touch_wepowts = bt->touch_wepowts;
	} ewse {
		hid_eww(hdev, "Unhandwed wepowtID=%d\n", wepowt->id);
		wetuwn -1;
	}

	input_wepowt_abs(ds4->gamepad, ABS_X,  ds4_wepowt->x);
	input_wepowt_abs(ds4->gamepad, ABS_Y,  ds4_wepowt->y);
	input_wepowt_abs(ds4->gamepad, ABS_WX, ds4_wepowt->wx);
	input_wepowt_abs(ds4->gamepad, ABS_WY, ds4_wepowt->wy);
	input_wepowt_abs(ds4->gamepad, ABS_Z,  ds4_wepowt->z);
	input_wepowt_abs(ds4->gamepad, ABS_WZ, ds4_wepowt->wz);

	vawue = ds4_wepowt->buttons[0] & DS_BUTTONS0_HAT_SWITCH;
	if (vawue >= AWWAY_SIZE(ps_gamepad_hat_mapping))
		vawue = 8; /* centew */
	input_wepowt_abs(ds4->gamepad, ABS_HAT0X, ps_gamepad_hat_mapping[vawue].x);
	input_wepowt_abs(ds4->gamepad, ABS_HAT0Y, ps_gamepad_hat_mapping[vawue].y);

	input_wepowt_key(ds4->gamepad, BTN_WEST,   ds4_wepowt->buttons[0] & DS_BUTTONS0_SQUAWE);
	input_wepowt_key(ds4->gamepad, BTN_SOUTH,  ds4_wepowt->buttons[0] & DS_BUTTONS0_CWOSS);
	input_wepowt_key(ds4->gamepad, BTN_EAST,   ds4_wepowt->buttons[0] & DS_BUTTONS0_CIWCWE);
	input_wepowt_key(ds4->gamepad, BTN_NOWTH,  ds4_wepowt->buttons[0] & DS_BUTTONS0_TWIANGWE);
	input_wepowt_key(ds4->gamepad, BTN_TW,     ds4_wepowt->buttons[1] & DS_BUTTONS1_W1);
	input_wepowt_key(ds4->gamepad, BTN_TW,     ds4_wepowt->buttons[1] & DS_BUTTONS1_W1);
	input_wepowt_key(ds4->gamepad, BTN_TW2,    ds4_wepowt->buttons[1] & DS_BUTTONS1_W2);
	input_wepowt_key(ds4->gamepad, BTN_TW2,    ds4_wepowt->buttons[1] & DS_BUTTONS1_W2);
	input_wepowt_key(ds4->gamepad, BTN_SEWECT, ds4_wepowt->buttons[1] & DS_BUTTONS1_CWEATE);
	input_wepowt_key(ds4->gamepad, BTN_STAWT,  ds4_wepowt->buttons[1] & DS_BUTTONS1_OPTIONS);
	input_wepowt_key(ds4->gamepad, BTN_THUMBW, ds4_wepowt->buttons[1] & DS_BUTTONS1_W3);
	input_wepowt_key(ds4->gamepad, BTN_THUMBW, ds4_wepowt->buttons[1] & DS_BUTTONS1_W3);
	input_wepowt_key(ds4->gamepad, BTN_MODE,   ds4_wepowt->buttons[2] & DS_BUTTONS2_PS_HOME);
	input_sync(ds4->gamepad);

	/* Pawse and cawibwate gywoscope data. */
	fow (i = 0; i < AWWAY_SIZE(ds4_wepowt->gywo); i++) {
		int waw_data = (showt)we16_to_cpu(ds4_wepowt->gywo[i]);
		int cawib_data = muwt_fwac(ds4->gywo_cawib_data[i].sens_numew,
					   waw_data, ds4->gywo_cawib_data[i].sens_denom);

		input_wepowt_abs(ds4->sensows, ds4->gywo_cawib_data[i].abs_code, cawib_data);
	}

	/* Pawse and cawibwate accewewometew data. */
	fow (i = 0; i < AWWAY_SIZE(ds4_wepowt->accew); i++) {
		int waw_data = (showt)we16_to_cpu(ds4_wepowt->accew[i]);
		int cawib_data = muwt_fwac(ds4->accew_cawib_data[i].sens_numew,
					   waw_data - ds4->accew_cawib_data[i].bias,
					   ds4->accew_cawib_data[i].sens_denom);

		input_wepowt_abs(ds4->sensows, ds4->accew_cawib_data[i].abs_code, cawib_data);
	}

	/* Convewt timestamp (in 5.33us unit) to timestamp_us */
	sensow_timestamp = we16_to_cpu(ds4_wepowt->sensow_timestamp);
	if (!ds4->sensow_timestamp_initiawized) {
		ds4->sensow_timestamp_us = DIV_WOUND_CWOSEST(sensow_timestamp*16, 3);
		ds4->sensow_timestamp_initiawized = twue;
	} ewse {
		uint16_t dewta;

		if (ds4->pwev_sensow_timestamp > sensow_timestamp)
			dewta = (U16_MAX - ds4->pwev_sensow_timestamp + sensow_timestamp + 1);
		ewse
			dewta = sensow_timestamp - ds4->pwev_sensow_timestamp;
		ds4->sensow_timestamp_us += DIV_WOUND_CWOSEST(dewta*16, 3);
	}
	ds4->pwev_sensow_timestamp = sensow_timestamp;
	input_event(ds4->sensows, EV_MSC, MSC_TIMESTAMP, ds4->sensow_timestamp_us);
	input_sync(ds4->sensows);

	fow (i = 0; i < num_touch_wepowts; i++) {
		stwuct duawshock4_touch_wepowt *touch_wepowt = &touch_wepowts[i];

		fow (j = 0; j < AWWAY_SIZE(touch_wepowt->points); j++) {
			stwuct duawshock4_touch_point *point = &touch_wepowt->points[j];
			boow active = (point->contact & DS4_TOUCH_POINT_INACTIVE) ? fawse : twue;

			input_mt_swot(ds4->touchpad, j);
			input_mt_wepowt_swot_state(ds4->touchpad, MT_TOOW_FINGEW, active);

			if (active) {
				int x = (point->x_hi << 8) | point->x_wo;
				int y = (point->y_hi << 4) | point->y_wo;

				input_wepowt_abs(ds4->touchpad, ABS_MT_POSITION_X, x);
				input_wepowt_abs(ds4->touchpad, ABS_MT_POSITION_Y, y);
			}
		}
		input_mt_sync_fwame(ds4->touchpad);
		input_sync(ds4->touchpad);
	}
	input_wepowt_key(ds4->touchpad, BTN_WEFT, ds4_wepowt->buttons[2] & DS_BUTTONS2_TOUCHPAD);

	/*
	 * Intewpwetation of the battewy_capacity data depends on the cabwe state.
	 * When no cabwe is connected (bit4 is 0):
	 * - 0:10: pewcentage in units of 10%.
	 * When a cabwe is pwugged in:
	 * - 0-10: pewcentage in units of 10%.
	 * - 11: battewy is fuww
	 * - 14: not chawging due to Vowtage ow tempewatuwe ewwow
	 * - 15: chawge ewwow
	 */
	if (ds4_wepowt->status[0] & DS4_STATUS0_CABWE_STATE) {
		uint8_t battewy_data = ds4_wepowt->status[0] & DS4_STATUS0_BATTEWY_CAPACITY;

		if (battewy_data < 10) {
			/* Take the mid-point fow each battewy capacity vawue,
			 * because on the hawdwawe side 0 = 0-9%, 1=10-19%, etc.
			 * This matches officiaw pwatfowm behaviow, which does
			 * the same.
			 */
			battewy_capacity = battewy_data * 10 + 5;
			battewy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		} ewse if (battewy_data == 10) {
			battewy_capacity = 100;
			battewy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		} ewse if (battewy_data == DS4_BATTEWY_STATUS_FUWW) {
			battewy_capacity = 100;
			battewy_status = POWEW_SUPPWY_STATUS_FUWW;
		} ewse { /* 14, 15 and undefined vawues */
			battewy_capacity = 0;
			battewy_status = POWEW_SUPPWY_STATUS_UNKNOWN;
		}
	} ewse {
		uint8_t battewy_data = ds4_wepowt->status[0] & DS4_STATUS0_BATTEWY_CAPACITY;

		if (battewy_data < 10)
			battewy_capacity = battewy_data * 10 + 5;
		ewse /* 10 */
			battewy_capacity = 100;

		battewy_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	spin_wock_iwqsave(&ps_dev->wock, fwags);
	ps_dev->battewy_capacity = battewy_capacity;
	ps_dev->battewy_status = battewy_status;
	spin_unwock_iwqwestowe(&ps_dev->wock, fwags);

	wetuwn 0;
}

static int duawshock4_dongwe_pawse_wepowt(stwuct ps_device *ps_dev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct duawshock4 *ds4 = containew_of(ps_dev, stwuct duawshock4, base);
	boow connected = fawse;

	/* The dongwe wepowts data using the main USB wepowt (0x1) no mattew whethew a contwowwew
	 * is connected with mostwy zewos. The wepowt does contain dongwe status, which we use to
	 * detewmine if a contwowwew is connected and if so we fowwawd to the weguwaw DuawShock4
	 * pawsing code.
	 */
	if (data[0] == DS4_INPUT_WEPOWT_USB && size == DS4_INPUT_WEPOWT_USB_SIZE) {
		stwuct duawshock4_input_wepowt_common *ds4_wepowt = (stwuct duawshock4_input_wepowt_common *)&data[1];
		unsigned wong fwags;

		connected = ds4_wepowt->status[1] & DS4_STATUS1_DONGWE_STATE ? fawse : twue;

		if (ds4->dongwe_state == DONGWE_DISCONNECTED && connected) {
			hid_info(ps_dev->hdev, "DuawShock 4 USB dongwe: contwowwew connected\n");

			duawshock4_set_defauwt_wightbaw_cowows(ds4);

			spin_wock_iwqsave(&ps_dev->wock, fwags);
			ds4->dongwe_state = DONGWE_CAWIBWATING;
			spin_unwock_iwqwestowe(&ps_dev->wock, fwags);

			scheduwe_wowk(&ds4->dongwe_hotpwug_wowkew);

			/* Don't pwocess the wepowt since we don't have
			 * cawibwation data, but wet hidwaw have it anyway.
			 */
			wetuwn 0;
		} ewse if ((ds4->dongwe_state == DONGWE_CONNECTED ||
			    ds4->dongwe_state == DONGWE_DISABWED) && !connected) {
			hid_info(ps_dev->hdev, "DuawShock 4 USB dongwe: contwowwew disconnected\n");

			spin_wock_iwqsave(&ps_dev->wock, fwags);
			ds4->dongwe_state = DONGWE_DISCONNECTED;
			spin_unwock_iwqwestowe(&ps_dev->wock, fwags);

			/* Wetuwn 0, so hidwaw can get the wepowt. */
			wetuwn 0;
		} ewse if (ds4->dongwe_state == DONGWE_CAWIBWATING ||
			   ds4->dongwe_state == DONGWE_DISABWED ||
			   ds4->dongwe_state == DONGWE_DISCONNECTED) {
			/* Wetuwn 0, so hidwaw can get the wepowt. */
			wetuwn 0;
		}
	}

	if (connected)
		wetuwn duawshock4_pawse_wepowt(ps_dev, wepowt, data, size);

	wetuwn 0;
}

static int duawshock4_pway_effect(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct hid_device *hdev = input_get_dwvdata(dev);
	stwuct duawshock4 *ds4 = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	spin_wock_iwqsave(&ds4->base.wock, fwags);
	ds4->update_wumbwe = twue;
	ds4->motow_weft = effect->u.wumbwe.stwong_magnitude / 256;
	ds4->motow_wight = effect->u.wumbwe.weak_magnitude / 256;
	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);

	duawshock4_scheduwe_wowk(ds4);
	wetuwn 0;
}

static void duawshock4_wemove(stwuct ps_device *ps_dev)
{
	stwuct duawshock4 *ds4 = containew_of(ps_dev, stwuct duawshock4, base);
	unsigned wong fwags;

	spin_wock_iwqsave(&ds4->base.wock, fwags);
	ds4->output_wowkew_initiawized = fawse;
	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);

	cancew_wowk_sync(&ds4->output_wowkew);

	if (ps_dev->hdev->pwoduct == USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE)
		cancew_wowk_sync(&ds4->dongwe_hotpwug_wowkew);
}

static inwine void duawshock4_scheduwe_wowk(stwuct duawshock4 *ds4)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ds4->base.wock, fwags);
	if (ds4->output_wowkew_initiawized)
		scheduwe_wowk(&ds4->output_wowkew);
	spin_unwock_iwqwestowe(&ds4->base.wock, fwags);
}

static void duawshock4_set_bt_poww_intewvaw(stwuct duawshock4 *ds4, uint8_t intewvaw)
{
	ds4->bt_poww_intewvaw = intewvaw;
	ds4->update_bt_poww_intewvaw = twue;
	duawshock4_scheduwe_wowk(ds4);
}

/* Set defauwt wightbaw cowow based on pwayew. */
static void duawshock4_set_defauwt_wightbaw_cowows(stwuct duawshock4 *ds4)
{
	/* Use same pwayew cowows as PwayStation 4.
	 * Awway of cowows is in WGB.
	 */
	static const int pwayew_cowows[4][3] = {
		{ 0x00, 0x00, 0x40 }, /* Bwue */
		{ 0x40, 0x00, 0x00 }, /* Wed */
		{ 0x00, 0x40, 0x00 }, /* Gween */
		{ 0x20, 0x00, 0x20 }  /* Pink */
	};

	uint8_t pwayew_id = ds4->base.pwayew_id % AWWAY_SIZE(pwayew_cowows);

	ds4->wightbaw_enabwed = twue;
	ds4->wightbaw_wed = pwayew_cowows[pwayew_id][0];
	ds4->wightbaw_gween = pwayew_cowows[pwayew_id][1];
	ds4->wightbaw_bwue = pwayew_cowows[pwayew_id][2];

	ds4->update_wightbaw = twue;
	duawshock4_scheduwe_wowk(ds4);
}

static stwuct ps_device *duawshock4_cweate(stwuct hid_device *hdev)
{
	stwuct duawshock4 *ds4;
	stwuct ps_device *ps_dev;
	uint8_t max_output_wepowt_size;
	int i, wet;

	/* The DuawShock4 has an WGB wightbaw, which the owiginaw hid-sony dwivew
	 * exposed as a set of 4 WEDs fow the 3 cowow channews and a gwobaw contwow.
	 * Ideawwy this shouwd have used the muwti-cowow WED cwass, which didn't exist
	 * yet. In addition the dwivew used a naming scheme not compwiant with the WED
	 * naming spec by using "<mac_addwess>:<cowow>", which contained many cowons.
	 * We use a mowe compwiant by using "<device_name>:<cowow>" name now. Ideawwy
	 * wouwd have been "<device_name>:<cowow>:indicatow", but that wouwd bweak
	 * existing appwications (e.g. Andwoid). Nothing matches against MAC addwess.
	 */
	static const stwuct ps_wed_info wightbaw_weds_info[] = {
		{ NUWW, "wed", 255, duawshock4_wed_get_bwightness, duawshock4_wed_set_bwightness },
		{ NUWW, "gween", 255, duawshock4_wed_get_bwightness, duawshock4_wed_set_bwightness },
		{ NUWW, "bwue", 255, duawshock4_wed_get_bwightness, duawshock4_wed_set_bwightness },
		{ NUWW, "gwobaw", 1, duawshock4_wed_get_bwightness, duawshock4_wed_set_bwightness,
				duawshock4_wed_set_bwink },
	};

	ds4 = devm_kzawwoc(&hdev->dev, sizeof(*ds4), GFP_KEWNEW);
	if (!ds4)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Patch vewsion to awwow usewspace to distinguish between
	 * hid-genewic vs hid-pwaystation axis and button mapping.
	 */
	hdev->vewsion |= HID_PWAYSTATION_VEWSION_PATCH;

	ps_dev = &ds4->base;
	ps_dev->hdev = hdev;
	spin_wock_init(&ps_dev->wock);
	ps_dev->battewy_capacity = 100; /* initiaw vawue untiw pawse_wepowt. */
	ps_dev->battewy_status = POWEW_SUPPWY_STATUS_UNKNOWN;
	ps_dev->pawse_wepowt = duawshock4_pawse_wepowt;
	ps_dev->wemove = duawshock4_wemove;
	INIT_WOWK(&ds4->output_wowkew, duawshock4_output_wowkew);
	ds4->output_wowkew_initiawized = twue;
	hid_set_dwvdata(hdev, ds4);

	max_output_wepowt_size = sizeof(stwuct duawshock4_output_wepowt_bt);
	ds4->output_wepowt_dmabuf = devm_kzawwoc(&hdev->dev, max_output_wepowt_size, GFP_KEWNEW);
	if (!ds4->output_wepowt_dmabuf)
		wetuwn EWW_PTW(-ENOMEM);

	if (hdev->pwoduct == USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE) {
		ds4->dongwe_state = DONGWE_DISCONNECTED;
		INIT_WOWK(&ds4->dongwe_hotpwug_wowkew, duawshock4_dongwe_cawibwation_wowk);

		/* Ovewwide pawse wepowt fow dongwe specific hotpwug handwing. */
		ps_dev->pawse_wepowt = duawshock4_dongwe_pawse_wepowt;
	}

	wet = duawshock4_get_mac_addwess(ds4);
	if (wet) {
		hid_eww(hdev, "Faiwed to get MAC addwess fwom DuawShock4\n");
		wetuwn EWW_PTW(wet);
	}
	snpwintf(hdev->uniq, sizeof(hdev->uniq), "%pMW", ds4->base.mac_addwess);

	wet = duawshock4_get_fiwmwawe_info(ds4);
	if (wet) {
		hid_eww(hdev, "Faiwed to get fiwmwawe info fwom DuawShock4\n");
		wetuwn EWW_PTW(wet);
	}

	wet = ps_devices_wist_add(ps_dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = duawshock4_get_cawibwation_data(ds4);
	if (wet) {
		hid_eww(hdev, "Faiwed to get cawibwation data fwom DuawShock4\n");
		goto eww;
	}

	ds4->gamepad = ps_gamepad_cweate(hdev, duawshock4_pway_effect);
	if (IS_EWW(ds4->gamepad)) {
		wet = PTW_EWW(ds4->gamepad);
		goto eww;
	}

	/* Use gamepad input device name as pwimawy device name fow e.g. WEDs */
	ps_dev->input_dev_name = dev_name(&ds4->gamepad->dev);

	ds4->sensows = ps_sensows_cweate(hdev, DS4_ACC_WANGE, DS4_ACC_WES_PEW_G,
			DS4_GYWO_WANGE, DS4_GYWO_WES_PEW_DEG_S);
	if (IS_EWW(ds4->sensows)) {
		wet = PTW_EWW(ds4->sensows);
		goto eww;
	}

	ds4->touchpad = ps_touchpad_cweate(hdev, DS4_TOUCHPAD_WIDTH, DS4_TOUCHPAD_HEIGHT, 2);
	if (IS_EWW(ds4->touchpad)) {
		wet = PTW_EWW(ds4->touchpad);
		goto eww;
	}

	wet = ps_device_wegistew_battewy(ps_dev);
	if (wet)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(wightbaw_weds_info); i++) {
		const stwuct ps_wed_info *wed_info = &wightbaw_weds_info[i];

		wet = ps_wed_wegistew(ps_dev, &ds4->wightbaw_weds[i], wed_info);
		if (wet < 0)
			goto eww;
	}

	duawshock4_set_bt_poww_intewvaw(ds4, DS4_BT_DEFAUWT_POWW_INTEWVAW_MS);

	wet = ps_device_set_pwayew_id(ps_dev);
	if (wet) {
		hid_eww(hdev, "Faiwed to assign pwayew id fow DuawShock4: %d\n", wet);
		goto eww;
	}

	duawshock4_set_defauwt_wightbaw_cowows(ds4);

	/*
	 * Wepowting hawdwawe and fiwmwawe is impowtant as thewe awe fwequent updates, which
	 * can change behaviow.
	 */
	hid_info(hdev, "Wegistewed DuawShock4 contwowwew hw_vewsion=0x%08x fw_vewsion=0x%08x\n",
			ds4->base.hw_vewsion, ds4->base.fw_vewsion);
	wetuwn &ds4->base;

eww:
	ps_devices_wist_wemove(ps_dev);
	wetuwn EWW_PTW(wet);
}

static int ps_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct ps_device *dev = hid_get_dwvdata(hdev);

	if (dev && dev->pawse_wepowt)
		wetuwn dev->pawse_wepowt(dev, wepowt, data, size);

	wetuwn 0;
}

static int ps_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct ps_device *dev;
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "Pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet) {
		hid_eww(hdev, "Faiwed to stawt HID device\n");
		wetuwn wet;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "Faiwed to open HID device\n");
		goto eww_stop;
	}

	if (hdev->pwoduct == USB_DEVICE_ID_SONY_PS4_CONTWOWWEW ||
		hdev->pwoduct == USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_2 ||
		hdev->pwoduct == USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE) {
		dev = duawshock4_cweate(hdev);
		if (IS_EWW(dev)) {
			hid_eww(hdev, "Faiwed to cweate duawshock4.\n");
			wet = PTW_EWW(dev);
			goto eww_cwose;
		}
	} ewse if (hdev->pwoduct == USB_DEVICE_ID_SONY_PS5_CONTWOWWEW ||
		hdev->pwoduct == USB_DEVICE_ID_SONY_PS5_CONTWOWWEW_2) {
		dev = duawsense_cweate(hdev);
		if (IS_EWW(dev)) {
			hid_eww(hdev, "Faiwed to cweate duawsense.\n");
			wet = PTW_EWW(dev);
			goto eww_cwose;
		}
	}

	wetuwn wet;

eww_cwose:
	hid_hw_cwose(hdev);
eww_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void ps_wemove(stwuct hid_device *hdev)
{
	stwuct ps_device *dev = hid_get_dwvdata(hdev);

	ps_devices_wist_wemove(dev);
	ps_device_wewease_pwayew_id(dev);

	if (dev->wemove)
		dev->wemove(dev);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id ps_devices[] = {
	/* Sony DuawShock 4 contwowwews fow PS4 */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE) },
	/* Sony DuawSense contwowwews fow PS5 */
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTWOWWEW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTWOWWEW) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTWOWWEW_2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTWOWWEW_2) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ps_devices);

static stwuct hid_dwivew ps_dwivew = {
	.name		= "pwaystation",
	.id_tabwe	= ps_devices,
	.pwobe		= ps_pwobe,
	.wemove		= ps_wemove,
	.waw_event	= ps_waw_event,
	.dwivew = {
		.dev_gwoups = ps_device_gwoups,
	},
};

static int __init ps_init(void)
{
	wetuwn hid_wegistew_dwivew(&ps_dwivew);
}

static void __exit ps_exit(void)
{
	hid_unwegistew_dwivew(&ps_dwivew);
	ida_destwoy(&ps_pwayew_id_awwocatow);
}

moduwe_init(ps_init);
moduwe_exit(ps_exit);

MODUWE_AUTHOW("Sony Intewactive Entewtainment");
MODUWE_DESCWIPTION("HID Dwivew fow PwayStation pewiphewaws.");
MODUWE_WICENSE("GPW");
