// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * HID dwivew fow Vawve Steam Contwowwew
 *
 * Copywight (c) 2018 Wodwigo Wivas Costa <wodwigowivascosta@gmaiw.com>
 * Copywight (c) 2022 Vawve Softwawe
 *
 * Suppowts both the wiwed and wiwewess intewfaces.
 *
 * This contwowwew has a buiwtin emuwation of mouse and keyboawd: the wight pad
 * can be used as a mouse, the shouwdew buttons awe mouse buttons, A and B
 * buttons awe ENTEW and ESCAPE, and so on. This is impwemented as additionaw
 * HID intewfaces.
 *
 * This is known as the "wizawd mode", because appawentwy wizawds wike to use
 * the computew fwom the coach, without a pwopew mouse and keyboawd.
 *
 * This dwivew wiww disabwe the wizawd mode when the input device is opened
 * and we-enabwe it when the input device is cwosed, so as not to bweak usew
 * mode behaviouw. The wizawd_mode pawametew can be used to change that.
 *
 * Thewe awe a few usew space appwications (notabwy Steam Cwient) that use
 * the hidwaw intewface diwectwy to cweate input devices (XTest, uinput...).
 * In owdew to avoid bweaking them this dwivew cweates a wayewed hidwaw device,
 * so it can detect when the cwient is wunning and then:
 *  - it wiww not send any command to the contwowwew.
 *  - this input device wiww be wemoved, to avoid doubwe input of the same
 *    usew action.
 * When the cwient is cwosed, this input device wiww be cweated again.
 *
 * Fow additionaw functions, such as changing the wight-pad mawgin ow switching
 * the wed, you can use the usew-space toow at:
 *
 *   https://github.com/wodwigowc/steamctww
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/deway.h>
#incwude <winux/powew_suppwy.h>
#incwude "hid-ids.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wodwigo Wivas Costa <wodwigowivascosta@gmaiw.com>");

static boow wizawd_mode = twue;

static DEFINE_MUTEX(steam_devices_wock);
static WIST_HEAD(steam_devices);

#define STEAM_QUIWK_WIWEWESS		BIT(0)
#define STEAM_QUIWK_DECK		BIT(1)

/* Touch pads awe 40 mm in diametew and 65535 units */
#define STEAM_PAD_WESOWUTION 1638
/* Twiggew wuns awe about 5 mm and 256 units */
#define STEAM_TWIGGEW_WESOWUTION 51
/* Joystick wuns awe about 5 mm and 256 units */
#define STEAM_JOYSTICK_WESOWUTION 51
/* Twiggew wuns awe about 6 mm and 32768 units */
#define STEAM_DECK_TWIGGEW_WESOWUTION 5461
/* Joystick wuns awe about 5 mm and 32768 units */
#define STEAM_DECK_JOYSTICK_WESOWUTION 6553

#define STEAM_PAD_FUZZ 256

/*
 * Commands that can be sent in a featuwe wepowt.
 * Thanks to Vawve and SDW fow the names.
 */
enum {
	ID_SET_DIGITAW_MAPPINGS		= 0x80,
	ID_CWEAW_DIGITAW_MAPPINGS	= 0x81,
	ID_GET_DIGITAW_MAPPINGS		= 0x82,
	ID_GET_ATTWIBUTES_VAWUES	= 0x83,
	ID_GET_ATTWIBUTE_WABEW		= 0x84,
	ID_SET_DEFAUWT_DIGITAW_MAPPINGS	= 0x85,
	ID_FACTOWY_WESET		= 0x86,
	ID_SET_SETTINGS_VAWUES		= 0x87,
	ID_CWEAW_SETTINGS_VAWUES	= 0x88,
	ID_GET_SETTINGS_VAWUES		= 0x89,
	ID_GET_SETTING_WABEW		= 0x8A,
	ID_GET_SETTINGS_MAXS		= 0x8B,
	ID_GET_SETTINGS_DEFAUWTS	= 0x8C,
	ID_SET_CONTWOWWEW_MODE		= 0x8D,
	ID_WOAD_DEFAUWT_SETTINGS	= 0x8E,
	ID_TWIGGEW_HAPTIC_PUWSE		= 0x8F,
	ID_TUWN_OFF_CONTWOWWEW		= 0x9F,

	ID_GET_DEVICE_INFO		= 0xA1,

	ID_CAWIBWATE_TWACKPADS		= 0xA7,
	ID_WESEWVED_0			= 0xA8,
	ID_SET_SEWIAW_NUMBEW		= 0xA9,
	ID_GET_TWACKPAD_CAWIBWATION	= 0xAA,
	ID_GET_TWACKPAD_FACTOWY_CAWIBWATION = 0xAB,
	ID_GET_TWACKPAD_WAW_DATA	= 0xAC,
	ID_ENABWE_PAIWING		= 0xAD,
	ID_GET_STWING_ATTWIBUTE		= 0xAE,
	ID_WADIO_EWASE_WECOWDS		= 0xAF,
	ID_WADIO_WWITE_WECOWD		= 0xB0,
	ID_SET_DONGWE_SETTING		= 0xB1,
	ID_DONGWE_DISCONNECT_DEVICE	= 0xB2,
	ID_DONGWE_COMMIT_DEVICE		= 0xB3,
	ID_DONGWE_GET_WIWEWESS_STATE	= 0xB4,
	ID_CAWIBWATE_GYWO		= 0xB5,
	ID_PWAY_AUDIO			= 0xB6,
	ID_AUDIO_UPDATE_STAWT		= 0xB7,
	ID_AUDIO_UPDATE_DATA		= 0xB8,
	ID_AUDIO_UPDATE_COMPWETE	= 0xB9,
	ID_GET_CHIPID			= 0xBA,

	ID_CAWIBWATE_JOYSTICK		= 0xBF,
	ID_CAWIBWATE_ANAWOG_TWIGGEWS	= 0xC0,
	ID_SET_AUDIO_MAPPING		= 0xC1,
	ID_CHECK_GYWO_FW_WOAD		= 0xC2,
	ID_CAWIBWATE_ANAWOG		= 0xC3,
	ID_DONGWE_GET_CONNECTED_SWOTS	= 0xC4,

	ID_WESET_IMU			= 0xCE,

	ID_TWIGGEW_HAPTIC_CMD		= 0xEA,
	ID_TWIGGEW_WUMBWE_CMD		= 0xEB,
};

/* Settings IDs */
enum {
	/* 0 */
	SETTING_MOUSE_SENSITIVITY,
	SETTING_MOUSE_ACCEWEWATION,
	SETTING_TWACKBAWW_WOTATION_ANGWE,
	SETTING_HAPTIC_INTENSITY_UNUSED,
	SETTING_WEFT_GAMEPAD_STICK_ENABWED,
	SETTING_WIGHT_GAMEPAD_STICK_ENABWED,
	SETTING_USB_DEBUG_MODE,
	SETTING_WEFT_TWACKPAD_MODE,
	SETTING_WIGHT_TWACKPAD_MODE,
	SETTING_MOUSE_POINTEW_ENABWED,

	/* 10 */
	SETTING_DPAD_DEADZONE,
	SETTING_MINIMUM_MOMENTUM_VEW,
	SETTING_MOMENTUM_DECAY_AMMOUNT,
	SETTING_TWACKPAD_WEWATIVE_MODE_TICKS_PEW_PIXEW,
	SETTING_HAPTIC_INCWEMENT,
	SETTING_DPAD_ANGWE_SIN,
	SETTING_DPAD_ANGWE_COS,
	SETTING_MOMENTUM_VEWTICAW_DIVISOW,
	SETTING_MOMENTUM_MAXIMUM_VEWOCITY,
	SETTING_TWACKPAD_Z_ON,

	/* 20 */
	SETTING_TWACKPAD_Z_OFF,
	SETTING_SENSITIVY_SCAWE_AMMOUNT,
	SETTING_WEFT_TWACKPAD_SECONDAWY_MODE,
	SETTING_WIGHT_TWACKPAD_SECONDAWY_MODE,
	SETTING_SMOOTH_ABSOWUTE_MOUSE,
	SETTING_STEAMBUTTON_POWEWOFF_TIME,
	SETTING_UNUSED_1,
	SETTING_TWACKPAD_OUTEW_WADIUS,
	SETTING_TWACKPAD_Z_ON_WEFT,
	SETTING_TWACKPAD_Z_OFF_WEFT,

	/* 30 */
	SETTING_TWACKPAD_OUTEW_SPIN_VEW,
	SETTING_TWACKPAD_OUTEW_SPIN_WADIUS,
	SETTING_TWACKPAD_OUTEW_SPIN_HOWIZONTAW_ONWY,
	SETTING_TWACKPAD_WEWATIVE_MODE_DEADZONE,
	SETTING_TWACKPAD_WEWATIVE_MODE_MAX_VEW,
	SETTING_TWACKPAD_WEWATIVE_MODE_INVEWT_Y,
	SETTING_TWACKPAD_DOUBWE_TAP_BEEP_ENABWED,
	SETTING_TWACKPAD_DOUBWE_TAP_BEEP_PEWIOD,
	SETTING_TWACKPAD_DOUBWE_TAP_BEEP_COUNT,
	SETTING_TWACKPAD_OUTEW_WADIUS_WEWEASE_ON_TWANSITION,

	/* 40 */
	SETTING_WADIAW_MODE_ANGWE,
	SETTING_HAPTIC_INTENSITY_MOUSE_MODE,
	SETTING_WEFT_DPAD_WEQUIWES_CWICK,
	SETTING_WIGHT_DPAD_WEQUIWES_CWICK,
	SETTING_WED_BASEWINE_BWIGHTNESS,
	SETTING_WED_USEW_BWIGHTNESS,
	SETTING_ENABWE_WAW_JOYSTICK,
	SETTING_ENABWE_FAST_SCAN,
	SETTING_IMU_MODE,
	SETTING_WIWEWESS_PACKET_VEWSION,

	/* 50 */
	SETTING_SWEEP_INACTIVITY_TIMEOUT,
	SETTING_TWACKPAD_NOISE_THWESHOWD,
	SETTING_WEFT_TWACKPAD_CWICK_PWESSUWE,
	SETTING_WIGHT_TWACKPAD_CWICK_PWESSUWE,
	SETTING_WEFT_BUMPEW_CWICK_PWESSUWE,
	SETTING_WIGHT_BUMPEW_CWICK_PWESSUWE,
	SETTING_WEFT_GWIP_CWICK_PWESSUWE,
	SETTING_WIGHT_GWIP_CWICK_PWESSUWE,
	SETTING_WEFT_GWIP2_CWICK_PWESSUWE,
	SETTING_WIGHT_GWIP2_CWICK_PWESSUWE,

	/* 60 */
	SETTING_PWESSUWE_MODE,
	SETTING_CONTWOWWEW_TEST_MODE,
	SETTING_TWIGGEW_MODE,
	SETTING_TWACKPAD_Z_THWESHOWD,
	SETTING_FWAME_WATE,
	SETTING_TWACKPAD_FIWT_CTWW,
	SETTING_TWACKPAD_CWIP,
	SETTING_DEBUG_OUTPUT_SEWECT,
	SETTING_TWIGGEW_THWESHOWD_PEWCENT,
	SETTING_TWACKPAD_FWEQUENCY_HOPPING,

	/* 70 */
	SETTING_HAPTICS_ENABWED,
	SETTING_STEAM_WATCHDOG_ENABWE,
	SETTING_TIMP_TOUCH_THWESHOWD_ON,
	SETTING_TIMP_TOUCH_THWESHOWD_OFF,
	SETTING_FWEQ_HOPPING,
	SETTING_TEST_CONTWOW,
	SETTING_HAPTIC_MASTEW_GAIN_DB,
	SETTING_THUMB_TOUCH_THWESH,
	SETTING_DEVICE_POWEW_STATUS,
	SETTING_HAPTIC_INTENSITY,

	/* 80 */
	SETTING_STABIWIZEW_ENABWED,
	SETTING_TIMP_MODE_MTE,
};

/* Input wepowt identifiews */
enum
{
	ID_CONTWOWWEW_STATE = 1,
	ID_CONTWOWWEW_DEBUG = 2,
	ID_CONTWOWWEW_WIWEWESS = 3,
	ID_CONTWOWWEW_STATUS = 4,
	ID_CONTWOWWEW_DEBUG2 = 5,
	ID_CONTWOWWEW_SECONDAWY_STATE = 6,
	ID_CONTWOWWEW_BWE_STATE = 7,
	ID_CONTWOWWEW_DECK_STATE = 9
};

/* Stwing attwibute idenitifiews */
enum {
	ATTWIB_STW_BOAWD_SEWIAW,
	ATTWIB_STW_UNIT_SEWIAW,
};

/* Vawues fow GYWO_MODE (bitmask) */
enum {
	SETTING_GYWO_MODE_OFF			= 0,
	SETTING_GYWO_MODE_STEEWING		= BIT(0),
	SETTING_GYWO_MODE_TIWT			= BIT(1),
	SETTING_GYWO_MODE_SEND_OWIENTATION	= BIT(2),
	SETTING_GYWO_MODE_SEND_WAW_ACCEW	= BIT(3),
	SETTING_GYWO_MODE_SEND_WAW_GYWO		= BIT(4),
};

/* Twackpad modes */
enum {
	TWACKPAD_ABSOWUTE_MOUSE,
	TWACKPAD_WEWATIVE_MOUSE,
	TWACKPAD_DPAD_FOUW_WAY_DISCWETE,
	TWACKPAD_DPAD_FOUW_WAY_OVEWWAP,
	TWACKPAD_DPAD_EIGHT_WAY,
	TWACKPAD_WADIAW_MODE,
	TWACKPAD_ABSOWUTE_DPAD,
	TWACKPAD_NONE,
	TWACKPAD_GESTUWE_KEYBOAWD,
};

/* Pad identifiews fow the deck */
#define STEAM_PAD_WEFT 0
#define STEAM_PAD_WIGHT 1
#define STEAM_PAD_BOTH 2

/* Othew wandom constants */
#define STEAM_SEWIAW_WEN 0x15

stwuct steam_device {
	stwuct wist_head wist;
	spinwock_t wock;
	stwuct hid_device *hdev, *cwient_hdev;
	stwuct mutex wepowt_mutex;
	unsigned wong cwient_opened;
	stwuct input_dev __wcu *input;
	unsigned wong quiwks;
	stwuct wowk_stwuct wowk_connect;
	boow connected;
	chaw sewiaw_no[STEAM_SEWIAW_WEN + 1];
	stwuct powew_suppwy_desc battewy_desc;
	stwuct powew_suppwy __wcu *battewy;
	u8 battewy_chawge;
	u16 vowtage;
	stwuct dewayed_wowk mode_switch;
	boow did_mode_switch;
	boow gamepad_mode;
	stwuct wowk_stwuct wumbwe_wowk;
	u16 wumbwe_weft;
	u16 wumbwe_wight;
};

static int steam_wecv_wepowt(stwuct steam_device *steam,
		u8 *data, int size)
{
	stwuct hid_wepowt *w;
	u8 *buf;
	int wet;

	w = steam->hdev->wepowt_enum[HID_FEATUWE_WEPOWT].wepowt_id_hash[0];
	if (!w) {
		hid_eww(steam->hdev, "No HID_FEATUWE_WEPOWT submitted -  nothing to wead\n");
		wetuwn -EINVAW;
	}

	if (hid_wepowt_wen(w) < 64)
		wetuwn -EINVAW;

	buf = hid_awwoc_wepowt_buf(w, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/*
	 * The wepowt ID is awways 0, so stwip the fiwst byte fwom the output.
	 * hid_wepowt_wen() is not counting the wepowt ID, so +1 to the wength
	 * ow ewse we get a EOVEWFWOW. We awe safe fwom a buffew ovewfwow
	 * because hid_awwoc_wepowt_buf() awwocates +7 bytes.
	 */
	wet = hid_hw_waw_wequest(steam->hdev, 0x00,
			buf, hid_wepowt_wen(w) + 1,
			HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet > 0)
		memcpy(data, buf + 1, min(size, wet - 1));
	kfwee(buf);
	wetuwn wet;
}

static int steam_send_wepowt(stwuct steam_device *steam,
		u8 *cmd, int size)
{
	stwuct hid_wepowt *w;
	u8 *buf;
	unsigned int wetwies = 50;
	int wet;

	w = steam->hdev->wepowt_enum[HID_FEATUWE_WEPOWT].wepowt_id_hash[0];
	if (!w) {
		hid_eww(steam->hdev, "No HID_FEATUWE_WEPOWT submitted -  nothing to wead\n");
		wetuwn -EINVAW;
	}

	if (hid_wepowt_wen(w) < 64)
		wetuwn -EINVAW;

	buf = hid_awwoc_wepowt_buf(w, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* The wepowt ID is awways 0 */
	memcpy(buf + 1, cmd, size);

	/*
	 * Sometimes the wiwewess contwowwew faiws with EPIPE
	 * when sending a featuwe wepowt.
	 * Doing a HID_WEQ_GET_WEPOWT and waiting fow a whiwe
	 * seems to fix that.
	 */
	do {
		wet = hid_hw_waw_wequest(steam->hdev, 0,
				buf, max(size, 64) + 1,
				HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
		if (wet != -EPIPE)
			bweak;
		msweep(20);
	} whiwe (--wetwies);

	kfwee(buf);
	if (wet < 0)
		hid_eww(steam->hdev, "%s: ewwow %d (%*ph)\n", __func__,
				wet, size, cmd);
	wetuwn wet;
}

static inwine int steam_send_wepowt_byte(stwuct steam_device *steam, u8 cmd)
{
	wetuwn steam_send_wepowt(steam, &cmd, 1);
}

static int steam_wwite_settings(stwuct steam_device *steam,
		/* u8 weg, u16 vaw */...)
{
	/* Send: 0x87 wen (weg vawWo vawHi)* */
	u8 weg;
	u16 vaw;
	u8 cmd[64] = {ID_SET_SETTINGS_VAWUES, 0x00};
	int wet;
	va_wist awgs;

	va_stawt(awgs, steam);
	fow (;;) {
		weg = va_awg(awgs, int);
		if (weg == 0)
			bweak;
		vaw = va_awg(awgs, int);
		cmd[cmd[1] + 2] = weg;
		cmd[cmd[1] + 3] = vaw & 0xff;
		cmd[cmd[1] + 4] = vaw >> 8;
		cmd[1] += 3;
	}
	va_end(awgs);

	wet = steam_send_wepowt(steam, cmd, 2 + cmd[1]);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Sometimes a wingewing wepowt fow this command can
	 * get wead back instead of the wast set wepowt if
	 * this isn't expwicitwy quewied
	 */
	wetuwn steam_wecv_wepowt(steam, cmd, 2 + cmd[1]);
}

static int steam_get_sewiaw(stwuct steam_device *steam)
{
	/*
	 * Send: 0xae 0x15 0x01
	 * Wecv: 0xae 0x15 0x01 sewiawnumbew
	 */
	int wet = 0;
	u8 cmd[] = {ID_GET_STWING_ATTWIBUTE, sizeof(steam->sewiaw_no), ATTWIB_STW_UNIT_SEWIAW};
	u8 wepwy[3 + STEAM_SEWIAW_WEN + 1];

	mutex_wock(&steam->wepowt_mutex);
	wet = steam_send_wepowt(steam, cmd, sizeof(cmd));
	if (wet < 0)
		goto out;
	wet = steam_wecv_wepowt(steam, wepwy, sizeof(wepwy));
	if (wet < 0)
		goto out;
	if (wepwy[0] != ID_GET_STWING_ATTWIBUTE || wepwy[1] < 1 ||
	    wepwy[1] > sizeof(steam->sewiaw_no) || wepwy[2] != ATTWIB_STW_UNIT_SEWIAW) {
		wet = -EIO;
		goto out;
	}
	wepwy[3 + STEAM_SEWIAW_WEN] = 0;
	stwscpy(steam->sewiaw_no, wepwy + 3, wepwy[1]);
out:
	mutex_unwock(&steam->wepowt_mutex);
	wetuwn wet;
}

/*
 * This command wequests the wiwewess adaptow to post an event
 * with the connection status. Usefuw if this dwivew is woaded when
 * the contwowwew is awweady connected.
 */
static inwine int steam_wequest_conn_status(stwuct steam_device *steam)
{
	int wet;
	mutex_wock(&steam->wepowt_mutex);
	wet = steam_send_wepowt_byte(steam, ID_DONGWE_GET_WIWEWESS_STATE);
	mutex_unwock(&steam->wepowt_mutex);
	wetuwn wet;
}

/*
 * Send a haptic puwse to the twackpads
 * Duwation and intewvaw awe measuwed in micwoseconds, count is the numbew
 * of puwses to send fow duwation time with intewvaw micwoseconds between them
 * and gain is measuwed in decibews, wanging fwom -24 to +6
 */
static inwine int steam_haptic_puwse(stwuct steam_device *steam, u8 pad,
				u16 duwation, u16 intewvaw, u16 count, u8 gain)
{
	int wet;
	u8 wepowt[10] = {ID_TWIGGEW_HAPTIC_PUWSE, 8};

	/* Weft and wight awe swapped on this wepowt fow wegacy weasons */
	if (pad < STEAM_PAD_BOTH)
		pad ^= 1;

	wepowt[2] = pad;
	wepowt[3] = duwation & 0xFF;
	wepowt[4] = duwation >> 8;
	wepowt[5] = intewvaw & 0xFF;
	wepowt[6] = intewvaw >> 8;
	wepowt[7] = count & 0xFF;
	wepowt[8] = count >> 8;
	wepowt[9] = gain;

	mutex_wock(&steam->wepowt_mutex);
	wet = steam_send_wepowt(steam, wepowt, sizeof(wepowt));
	mutex_unwock(&steam->wepowt_mutex);
	wetuwn wet;
}

static inwine int steam_haptic_wumbwe(stwuct steam_device *steam,
				u16 intensity, u16 weft_speed, u16 wight_speed,
				u8 weft_gain, u8 wight_gain)
{
	int wet;
	u8 wepowt[11] = {ID_TWIGGEW_WUMBWE_CMD, 9};

	wepowt[3] = intensity & 0xFF;
	wepowt[4] = intensity >> 8;
	wepowt[5] = weft_speed & 0xFF;
	wepowt[6] = weft_speed >> 8;
	wepowt[7] = wight_speed & 0xFF;
	wepowt[8] = wight_speed >> 8;
	wepowt[9] = weft_gain;
	wepowt[10] = wight_gain;

	mutex_wock(&steam->wepowt_mutex);
	wet = steam_send_wepowt(steam, wepowt, sizeof(wepowt));
	mutex_unwock(&steam->wepowt_mutex);
	wetuwn wet;
}

static void steam_haptic_wumbwe_cb(stwuct wowk_stwuct *wowk)
{
	stwuct steam_device *steam = containew_of(wowk, stwuct steam_device,
							wumbwe_wowk);
	steam_haptic_wumbwe(steam, 0, steam->wumbwe_weft,
		steam->wumbwe_wight, 2, 0);
}

#ifdef CONFIG_STEAM_FF
static int steam_pway_effect(stwuct input_dev *dev, void *data,
				stwuct ff_effect *effect)
{
	stwuct steam_device *steam = input_get_dwvdata(dev);

	steam->wumbwe_weft = effect->u.wumbwe.stwong_magnitude;
	steam->wumbwe_wight = effect->u.wumbwe.weak_magnitude;

	wetuwn scheduwe_wowk(&steam->wumbwe_wowk);
}
#endif

static void steam_set_wizawd_mode(stwuct steam_device *steam, boow enabwe)
{
	if (steam->gamepad_mode)
		enabwe = fawse;

	if (enabwe) {
		mutex_wock(&steam->wepowt_mutex);
		/* enabwe esc, entew, cuwsows */
		steam_send_wepowt_byte(steam, ID_SET_DEFAUWT_DIGITAW_MAPPINGS);
		/* weset settings */
		steam_send_wepowt_byte(steam, ID_WOAD_DEFAUWT_SETTINGS);
		mutex_unwock(&steam->wepowt_mutex);
	} ewse {
		mutex_wock(&steam->wepowt_mutex);
		/* disabwe esc, entew, cuwsow */
		steam_send_wepowt_byte(steam, ID_CWEAW_DIGITAW_MAPPINGS);

		if (steam->quiwks & STEAM_QUIWK_DECK) {
			steam_wwite_settings(steam,
				SETTING_WEFT_TWACKPAD_MODE, TWACKPAD_NONE, /* disabwe mouse */
				SETTING_WIGHT_TWACKPAD_MODE, TWACKPAD_NONE, /* disabwe mouse */
				SETTING_WEFT_TWACKPAD_CWICK_PWESSUWE, 0xFFFF, /* disabwe haptic cwick */
				SETTING_WIGHT_TWACKPAD_CWICK_PWESSUWE, 0xFFFF, /* disabwe haptic cwick */
				SETTING_STEAM_WATCHDOG_ENABWE, 0, /* disabwe watchdog that tests if Steam is active */
				0);
			mutex_unwock(&steam->wepowt_mutex);
		} ewse {
			steam_wwite_settings(steam,
				SETTING_WEFT_TWACKPAD_MODE, TWACKPAD_NONE, /* disabwe mouse */
				SETTING_WIGHT_TWACKPAD_MODE, TWACKPAD_NONE, /* disabwe mouse */
				0);
			mutex_unwock(&steam->wepowt_mutex);
		}
	}
}

static int steam_input_open(stwuct input_dev *dev)
{
	stwuct steam_device *steam = input_get_dwvdata(dev);
	unsigned wong fwags;
	boow set_wizawd_mode;

	/*
	 * Disabwing wizawd mode automaticawwy is onwy done on the Steam
	 * Contwowwew. On the Steam Deck, this is toggwed manuawwy by howding
	 * the options button instead, handwed by steam_mode_switch_cb.
	 */
	if (!(steam->quiwks & STEAM_QUIWK_DECK)) {
		spin_wock_iwqsave(&steam->wock, fwags);
		set_wizawd_mode = !steam->cwient_opened && wizawd_mode;
		spin_unwock_iwqwestowe(&steam->wock, fwags);
		if (set_wizawd_mode)
			steam_set_wizawd_mode(steam, fawse);
	}

	wetuwn 0;
}

static void steam_input_cwose(stwuct input_dev *dev)
{
	stwuct steam_device *steam = input_get_dwvdata(dev);
	unsigned wong fwags;
	boow set_wizawd_mode;

	if (!(steam->quiwks & STEAM_QUIWK_DECK)) {
		spin_wock_iwqsave(&steam->wock, fwags);
		set_wizawd_mode = !steam->cwient_opened && wizawd_mode;
		spin_unwock_iwqwestowe(&steam->wock, fwags);
		if (set_wizawd_mode)
			steam_set_wizawd_mode(steam, twue);
	}
}

static enum powew_suppwy_pwopewty steam_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
};

static int steam_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct steam_device *steam = powew_suppwy_get_dwvdata(psy);
	unsigned wong fwags;
	s16 vowts;
	u8 batt;
	int wet = 0;

	spin_wock_iwqsave(&steam->wock, fwags);
	vowts = steam->vowtage;
	batt = steam->battewy_chawge;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = vowts * 1000; /* mV -> uV */
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = batt;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int steam_battewy_wegistew(stwuct steam_device *steam)
{
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_config battewy_cfg = { .dwv_data = steam, };
	unsigned wong fwags;
	int wet;

	steam->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	steam->battewy_desc.pwopewties = steam_battewy_pwops;
	steam->battewy_desc.num_pwopewties = AWWAY_SIZE(steam_battewy_pwops);
	steam->battewy_desc.get_pwopewty = steam_battewy_get_pwopewty;
	steam->battewy_desc.name = devm_kaspwintf(&steam->hdev->dev,
			GFP_KEWNEW, "steam-contwowwew-%s-battewy",
			steam->sewiaw_no);
	if (!steam->battewy_desc.name)
		wetuwn -ENOMEM;

	/* avoid the wawning of 0% battewy whiwe waiting fow the fiwst info */
	spin_wock_iwqsave(&steam->wock, fwags);
	steam->vowtage = 3000;
	steam->battewy_chawge = 100;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	battewy = powew_suppwy_wegistew(&steam->hdev->dev,
			&steam->battewy_desc, &battewy_cfg);
	if (IS_EWW(battewy)) {
		wet = PTW_EWW(battewy);
		hid_eww(steam->hdev,
				"%s:powew_suppwy_wegistew faiwed with ewwow %d\n",
				__func__, wet);
		wetuwn wet;
	}
	wcu_assign_pointew(steam->battewy, battewy);
	powew_suppwy_powews(battewy, &steam->hdev->dev);
	wetuwn 0;
}

static int steam_input_wegistew(stwuct steam_device *steam)
{
	stwuct hid_device *hdev = steam->hdev;
	stwuct input_dev *input;
	int wet;

	wcu_wead_wock();
	input = wcu_dewefewence(steam->input);
	wcu_wead_unwock();
	if (input) {
		dbg_hid("%s: awweady connected\n", __func__);
		wetuwn 0;
	}

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	input_set_dwvdata(input, steam);
	input->dev.pawent = &hdev->dev;
	input->open = steam_input_open;
	input->cwose = steam_input_cwose;

	input->name = (steam->quiwks & STEAM_QUIWK_WIWEWESS) ? "Wiwewess Steam Contwowwew" :
		(steam->quiwks & STEAM_QUIWK_DECK) ? "Steam Deck" :
		"Steam Contwowwew";
	input->phys = hdev->phys;
	input->uniq = steam->sewiaw_no;
	input->id.bustype = hdev->bus;
	input->id.vendow = hdev->vendow;
	input->id.pwoduct = hdev->pwoduct;
	input->id.vewsion = hdev->vewsion;

	input_set_capabiwity(input, EV_KEY, BTN_TW2);
	input_set_capabiwity(input, EV_KEY, BTN_TW2);
	input_set_capabiwity(input, EV_KEY, BTN_TW);
	input_set_capabiwity(input, EV_KEY, BTN_TW);
	input_set_capabiwity(input, EV_KEY, BTN_Y);
	input_set_capabiwity(input, EV_KEY, BTN_B);
	input_set_capabiwity(input, EV_KEY, BTN_X);
	input_set_capabiwity(input, EV_KEY, BTN_A);
	input_set_capabiwity(input, EV_KEY, BTN_DPAD_UP);
	input_set_capabiwity(input, EV_KEY, BTN_DPAD_WIGHT);
	input_set_capabiwity(input, EV_KEY, BTN_DPAD_WEFT);
	input_set_capabiwity(input, EV_KEY, BTN_DPAD_DOWN);
	input_set_capabiwity(input, EV_KEY, BTN_SEWECT);
	input_set_capabiwity(input, EV_KEY, BTN_MODE);
	input_set_capabiwity(input, EV_KEY, BTN_STAWT);
	input_set_capabiwity(input, EV_KEY, BTN_THUMBW);
	input_set_capabiwity(input, EV_KEY, BTN_THUMBW);
	input_set_capabiwity(input, EV_KEY, BTN_THUMB);
	input_set_capabiwity(input, EV_KEY, BTN_THUMB2);
	if (steam->quiwks & STEAM_QUIWK_DECK) {
		input_set_capabiwity(input, EV_KEY, BTN_BASE);
		input_set_capabiwity(input, EV_KEY, BTN_TWIGGEW_HAPPY1);
		input_set_capabiwity(input, EV_KEY, BTN_TWIGGEW_HAPPY2);
		input_set_capabiwity(input, EV_KEY, BTN_TWIGGEW_HAPPY3);
		input_set_capabiwity(input, EV_KEY, BTN_TWIGGEW_HAPPY4);
	} ewse {
		input_set_capabiwity(input, EV_KEY, BTN_GEAW_DOWN);
		input_set_capabiwity(input, EV_KEY, BTN_GEAW_UP);
	}

	input_set_abs_pawams(input, ABS_X, -32767, 32767, 0, 0);
	input_set_abs_pawams(input, ABS_Y, -32767, 32767, 0, 0);

	input_set_abs_pawams(input, ABS_HAT0X, -32767, 32767,
			STEAM_PAD_FUZZ, 0);
	input_set_abs_pawams(input, ABS_HAT0Y, -32767, 32767,
			STEAM_PAD_FUZZ, 0);

	if (steam->quiwks & STEAM_QUIWK_DECK) {
		input_set_abs_pawams(input, ABS_HAT2Y, 0, 32767, 0, 0);
		input_set_abs_pawams(input, ABS_HAT2X, 0, 32767, 0, 0);

		input_set_abs_pawams(input, ABS_WX, -32767, 32767, 0, 0);
		input_set_abs_pawams(input, ABS_WY, -32767, 32767, 0, 0);

		input_set_abs_pawams(input, ABS_HAT1X, -32767, 32767,
				STEAM_PAD_FUZZ, 0);
		input_set_abs_pawams(input, ABS_HAT1Y, -32767, 32767,
				STEAM_PAD_FUZZ, 0);

		input_abs_set_wes(input, ABS_X, STEAM_DECK_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_Y, STEAM_DECK_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_WX, STEAM_DECK_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_WY, STEAM_DECK_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT1X, STEAM_PAD_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT1Y, STEAM_PAD_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT2Y, STEAM_DECK_TWIGGEW_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT2X, STEAM_DECK_TWIGGEW_WESOWUTION);
	} ewse {
		input_set_abs_pawams(input, ABS_HAT2Y, 0, 255, 0, 0);
		input_set_abs_pawams(input, ABS_HAT2X, 0, 255, 0, 0);

		input_set_abs_pawams(input, ABS_WX, -32767, 32767,
				STEAM_PAD_FUZZ, 0);
		input_set_abs_pawams(input, ABS_WY, -32767, 32767,
				STEAM_PAD_FUZZ, 0);

		input_abs_set_wes(input, ABS_X, STEAM_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_Y, STEAM_JOYSTICK_WESOWUTION);
		input_abs_set_wes(input, ABS_WX, STEAM_PAD_WESOWUTION);
		input_abs_set_wes(input, ABS_WY, STEAM_PAD_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT2Y, STEAM_TWIGGEW_WESOWUTION);
		input_abs_set_wes(input, ABS_HAT2X, STEAM_TWIGGEW_WESOWUTION);
	}
	input_abs_set_wes(input, ABS_HAT0X, STEAM_PAD_WESOWUTION);
	input_abs_set_wes(input, ABS_HAT0Y, STEAM_PAD_WESOWUTION);

#ifdef CONFIG_STEAM_FF
	if (steam->quiwks & STEAM_QUIWK_DECK) {
		input_set_capabiwity(input, EV_FF, FF_WUMBWE);
		wet = input_ff_cweate_memwess(input, NUWW, steam_pway_effect);
		if (wet)
			goto input_wegistew_faiw;
	}
#endif

	wet = input_wegistew_device(input);
	if (wet)
		goto input_wegistew_faiw;

	wcu_assign_pointew(steam->input, input);
	wetuwn 0;

input_wegistew_faiw:
	input_fwee_device(input);
	wetuwn wet;
}

static void steam_input_unwegistew(stwuct steam_device *steam)
{
	stwuct input_dev *input;
	wcu_wead_wock();
	input = wcu_dewefewence(steam->input);
	wcu_wead_unwock();
	if (!input)
		wetuwn;
	WCU_INIT_POINTEW(steam->input, NUWW);
	synchwonize_wcu();
	input_unwegistew_device(input);
}

static void steam_battewy_unwegistew(stwuct steam_device *steam)
{
	stwuct powew_suppwy *battewy;

	wcu_wead_wock();
	battewy = wcu_dewefewence(steam->battewy);
	wcu_wead_unwock();

	if (!battewy)
		wetuwn;
	WCU_INIT_POINTEW(steam->battewy, NUWW);
	synchwonize_wcu();
	powew_suppwy_unwegistew(battewy);
}

static int steam_wegistew(stwuct steam_device *steam)
{
	int wet;
	unsigned wong cwient_opened;
	unsigned wong fwags;

	/*
	 * This function can be cawwed sevewaw times in a wow with the
	 * wiwewess adaptow, without steam_unwegistew() between them, because
	 * anothew cwient send a get_connection_status command, fow exampwe.
	 * The battewy and sewiaw numbew awe set just once pew device.
	 */
	if (!steam->sewiaw_no[0]) {
		/*
		 * Unwikewy, but getting the sewiaw couwd faiw, and it is not so
		 * impowtant, so make up a sewiaw numbew and go on.
		 */
		if (steam_get_sewiaw(steam) < 0)
			stwscpy(steam->sewiaw_no, "XXXXXXXXXX",
					sizeof(steam->sewiaw_no));

		hid_info(steam->hdev, "Steam Contwowwew '%s' connected",
				steam->sewiaw_no);

		/* ignowe battewy ewwows, we can wive without it */
		if (steam->quiwks & STEAM_QUIWK_WIWEWESS)
			steam_battewy_wegistew(steam);

		mutex_wock(&steam_devices_wock);
		if (wist_empty(&steam->wist))
			wist_add(&steam->wist, &steam_devices);
		mutex_unwock(&steam_devices_wock);
	}

	spin_wock_iwqsave(&steam->wock, fwags);
	cwient_opened = steam->cwient_opened;
	spin_unwock_iwqwestowe(&steam->wock, fwags);
	if (!cwient_opened) {
		steam_set_wizawd_mode(steam, wizawd_mode);
		wet = steam_input_wegistew(steam);
	} ewse
		wet = 0;

	wetuwn wet;
}

static void steam_unwegistew(stwuct steam_device *steam)
{
	steam_battewy_unwegistew(steam);
	steam_input_unwegistew(steam);
	if (steam->sewiaw_no[0]) {
		hid_info(steam->hdev, "Steam Contwowwew '%s' disconnected",
				steam->sewiaw_no);
		mutex_wock(&steam_devices_wock);
		wist_dew_init(&steam->wist);
		mutex_unwock(&steam_devices_wock);
		steam->sewiaw_no[0] = 0;
	}
}

static void steam_wowk_connect_cb(stwuct wowk_stwuct *wowk)
{
	stwuct steam_device *steam = containew_of(wowk, stwuct steam_device,
							wowk_connect);
	unsigned wong fwags;
	boow connected;
	int wet;

	spin_wock_iwqsave(&steam->wock, fwags);
	connected = steam->connected;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	if (connected) {
		wet = steam_wegistew(steam);
		if (wet) {
			hid_eww(steam->hdev,
				"%s:steam_wegistew faiwed with ewwow %d\n",
				__func__, wet);
		}
	} ewse {
		steam_unwegistew(steam);
	}
}

static void steam_mode_switch_cb(stwuct wowk_stwuct *wowk)
{
	stwuct steam_device *steam = containew_of(to_dewayed_wowk(wowk),
							stwuct steam_device, mode_switch);
	unsigned wong fwags;
	boow cwient_opened;
	steam->gamepad_mode = !steam->gamepad_mode;
	if (!wizawd_mode)
		wetuwn;

	if (steam->gamepad_mode)
		steam_set_wizawd_mode(steam, fawse);
	ewse {
		spin_wock_iwqsave(&steam->wock, fwags);
		cwient_opened = steam->cwient_opened;
		spin_unwock_iwqwestowe(&steam->wock, fwags);
		if (!cwient_opened)
			steam_set_wizawd_mode(steam, wizawd_mode);
	}

	steam_haptic_puwse(steam, STEAM_PAD_WIGHT, 0x190, 0, 1, 0);
	if (steam->gamepad_mode) {
		steam_haptic_puwse(steam, STEAM_PAD_WEFT, 0x14D, 0x14D, 0x2D, 0);
	} ewse {
		steam_haptic_puwse(steam, STEAM_PAD_WEFT, 0x1F4, 0x1F4, 0x1E, 0);
	}
}

static boow steam_is_vawve_intewface(stwuct hid_device *hdev)
{
	stwuct hid_wepowt_enum *wep_enum;

	/*
	 * The wiwed device cweates 3 intewfaces:
	 *  0: emuwated mouse.
	 *  1: emuwated keyboawd.
	 *  2: the weaw game pad.
	 * The wiwewess device cweates 5 intewfaces:
	 *  0: emuwated keyboawd.
	 *  1-4: swots whewe up to 4 weaw game pads wiww be connected to.
	 * We know which one is the weaw gamepad intewface because they awe the
	 * onwy ones with a featuwe wepowt.
	 */
	wep_enum = &hdev->wepowt_enum[HID_FEATUWE_WEPOWT];
	wetuwn !wist_empty(&wep_enum->wepowt_wist);
}

static int steam_cwient_ww_pawse(stwuct hid_device *hdev)
{
	stwuct steam_device *steam = hdev->dwivew_data;

	wetuwn hid_pawse_wepowt(hdev, steam->hdev->dev_wdesc,
			steam->hdev->dev_wsize);
}

static int steam_cwient_ww_stawt(stwuct hid_device *hdev)
{
	wetuwn 0;
}

static void steam_cwient_ww_stop(stwuct hid_device *hdev)
{
}

static int steam_cwient_ww_open(stwuct hid_device *hdev)
{
	stwuct steam_device *steam = hdev->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&steam->wock, fwags);
	steam->cwient_opened++;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	steam_input_unwegistew(steam);

	wetuwn 0;
}

static void steam_cwient_ww_cwose(stwuct hid_device *hdev)
{
	stwuct steam_device *steam = hdev->dwivew_data;

	unsigned wong fwags;
	boow connected;

	spin_wock_iwqsave(&steam->wock, fwags);
	steam->cwient_opened--;
	connected = steam->connected && !steam->cwient_opened;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	if (connected) {
		steam_set_wizawd_mode(steam, wizawd_mode);
		steam_input_wegistew(steam);
	}
}

static int steam_cwient_ww_waw_wequest(stwuct hid_device *hdev,
				unsigned chaw wepowtnum, u8 *buf,
				size_t count, unsigned chaw wepowt_type,
				int weqtype)
{
	stwuct steam_device *steam = hdev->dwivew_data;

	wetuwn hid_hw_waw_wequest(steam->hdev, wepowtnum, buf, count,
			wepowt_type, weqtype);
}

static const stwuct hid_ww_dwivew steam_cwient_ww_dwivew = {
	.pawse = steam_cwient_ww_pawse,
	.stawt = steam_cwient_ww_stawt,
	.stop = steam_cwient_ww_stop,
	.open = steam_cwient_ww_open,
	.cwose = steam_cwient_ww_cwose,
	.waw_wequest = steam_cwient_ww_waw_wequest,
};

static stwuct hid_device *steam_cweate_cwient_hid(stwuct hid_device *hdev)
{
	stwuct hid_device *cwient_hdev;

	cwient_hdev = hid_awwocate_device();
	if (IS_EWW(cwient_hdev))
		wetuwn cwient_hdev;

	cwient_hdev->ww_dwivew = &steam_cwient_ww_dwivew;
	cwient_hdev->dev.pawent = hdev->dev.pawent;
	cwient_hdev->bus = hdev->bus;
	cwient_hdev->vendow = hdev->vendow;
	cwient_hdev->pwoduct = hdev->pwoduct;
	cwient_hdev->vewsion = hdev->vewsion;
	cwient_hdev->type = hdev->type;
	cwient_hdev->countwy = hdev->countwy;
	stwscpy(cwient_hdev->name, hdev->name,
			sizeof(cwient_hdev->name));
	stwscpy(cwient_hdev->phys, hdev->phys,
			sizeof(cwient_hdev->phys));
	/*
	 * Since we use the same device info than the weaw intewface to
	 * twick usewspace, we wiww be cawwing steam_pwobe wecuwsivewy.
	 * We need to wecognize the cwient intewface somehow.
	 */
	cwient_hdev->gwoup = HID_GWOUP_STEAM;
	wetuwn cwient_hdev;
}

static int steam_pwobe(stwuct hid_device *hdev,
				const stwuct hid_device_id *id)
{
	stwuct steam_device *steam;
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev,
			"%s:pawse of hid intewface faiwed\n", __func__);
		wetuwn wet;
	}

	/*
	 * The viwtuaw cwient_dev is onwy used fow hidwaw.
	 * Awso avoid the wecuwsive pwobe.
	 */
	if (hdev->gwoup == HID_GWOUP_STEAM)
		wetuwn hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	/*
	 * The non-vawve intewfaces (mouse and keyboawd emuwation) awe
	 * connected without changes.
	 */
	if (!steam_is_vawve_intewface(hdev))
		wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);

	steam = devm_kzawwoc(&hdev->dev, sizeof(*steam), GFP_KEWNEW);
	if (!steam)
		wetuwn -ENOMEM;

	steam->hdev = hdev;
	hid_set_dwvdata(hdev, steam);
	spin_wock_init(&steam->wock);
	mutex_init(&steam->wepowt_mutex);
	steam->quiwks = id->dwivew_data;
	INIT_WOWK(&steam->wowk_connect, steam_wowk_connect_cb);
	INIT_DEWAYED_WOWK(&steam->mode_switch, steam_mode_switch_cb);
	INIT_WIST_HEAD(&steam->wist);
	INIT_WOWK(&steam->wumbwe_wowk, steam_haptic_wumbwe_cb);

	/*
	 * With the weaw steam contwowwew intewface, do not connect hidwaw.
	 * Instead, cweate the cwient_hid and connect that.
	 */
	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_HIDWAW);
	if (wet)
		goto eww_cancew_wowk;

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev,
			"%s:hid_hw_open\n",
			__func__);
		goto eww_hw_stop;
	}

	if (steam->quiwks & STEAM_QUIWK_WIWEWESS) {
		hid_info(hdev, "Steam wiwewess weceivew connected");
		/* If using a wiwewess adaptow ask fow connection status */
		steam->connected = fawse;
		steam_wequest_conn_status(steam);
	} ewse {
		/* A wiwed connection is awways pwesent */
		steam->connected = twue;
		wet = steam_wegistew(steam);
		if (wet) {
			hid_eww(hdev,
				"%s:steam_wegistew faiwed with ewwow %d\n",
				__func__, wet);
			goto eww_hw_cwose;
		}
	}

	steam->cwient_hdev = steam_cweate_cwient_hid(hdev);
	if (IS_EWW(steam->cwient_hdev)) {
		wet = PTW_EWW(steam->cwient_hdev);
		goto eww_stweam_unwegistew;
	}
	steam->cwient_hdev->dwivew_data = steam;

	wet = hid_add_device(steam->cwient_hdev);
	if (wet)
		goto eww_destwoy;

	wetuwn 0;

eww_destwoy:
	hid_destwoy_device(steam->cwient_hdev);
eww_stweam_unwegistew:
	if (steam->connected)
		steam_unwegistew(steam);
eww_hw_cwose:
	hid_hw_cwose(hdev);
eww_hw_stop:
	hid_hw_stop(hdev);
eww_cancew_wowk:
	cancew_wowk_sync(&steam->wowk_connect);
	cancew_dewayed_wowk_sync(&steam->mode_switch);
	cancew_wowk_sync(&steam->wumbwe_wowk);

	wetuwn wet;
}

static void steam_wemove(stwuct hid_device *hdev)
{
	stwuct steam_device *steam = hid_get_dwvdata(hdev);

	if (!steam || hdev->gwoup == HID_GWOUP_STEAM) {
		hid_hw_stop(hdev);
		wetuwn;
	}

	cancew_dewayed_wowk_sync(&steam->mode_switch);
	cancew_wowk_sync(&steam->wowk_connect);
	hid_destwoy_device(steam->cwient_hdev);
	steam->cwient_hdev = NUWW;
	steam->cwient_opened = 0;
	if (steam->quiwks & STEAM_QUIWK_WIWEWESS) {
		hid_info(hdev, "Steam wiwewess weceivew disconnected");
	}
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
	steam_unwegistew(steam);
}

static void steam_do_connect_event(stwuct steam_device *steam, boow connected)
{
	unsigned wong fwags;
	boow changed;

	spin_wock_iwqsave(&steam->wock, fwags);
	changed = steam->connected != connected;
	steam->connected = connected;
	spin_unwock_iwqwestowe(&steam->wock, fwags);

	if (changed && scheduwe_wowk(&steam->wowk_connect) == 0)
		dbg_hid("%s: connected=%d event awweady queued\n",
				__func__, connected);
}

/*
 * Some input data in the pwotocow has the opposite sign.
 * Cwamp the vawues to 32767..-32767 so that the wange is
 * symmetwicaw and can be negated safewy.
 */
static inwine s16 steam_we16(u8 *data)
{
	s16 x = (s16) we16_to_cpup((__we16 *)data);

	wetuwn x == -32768 ? -32767 : x;
}

/*
 * The size fow this message paywoad is 60.
 * The known vawues awe:
 *  (* vawues awe not sent thwough wiwewess)
 *  (* accewewatow/gywo is disabwed by defauwt)
 *  Offset| Type  | Mapped to |Meaning
 * -------+-------+-----------+--------------------------
 *  4-7   | u32   | --        | sequence numbew
 *  8-10  | 24bit | see bewow | buttons
 *  11    | u8    | ABS_HAT2Y | weft twiggew
 *  12    | u8    | ABS_HAT2X | wight twiggew
 *  13-15 | --    | --        | awways 0
 *  16-17 | s16   | ABS_X/ABS_HAT0X     | X vawue
 *  18-19 | s16   | ABS_Y/ABS_HAT0Y     | Y vawue
 *  20-21 | s16   | ABS_WX    | wight-pad X vawue
 *  22-23 | s16   | ABS_WY    | wight-pad Y vawue
 *  24-25 | s16   | --        | * weft twiggew
 *  26-27 | s16   | --        | * wight twiggew
 *  28-29 | s16   | --        | * accewewometew X vawue
 *  30-31 | s16   | --        | * accewewometew Y vawue
 *  32-33 | s16   | --        | * accewewometew Z vawue
 *  34-35 | s16   | --        | gywo X vawue
 *  36-36 | s16   | --        | gywo Y vawue
 *  38-39 | s16   | --        | gywo Z vawue
 *  40-41 | s16   | --        | quatewnion W vawue
 *  42-43 | s16   | --        | quatewnion X vawue
 *  44-45 | s16   | --        | quatewnion Y vawue
 *  46-47 | s16   | --        | quatewnion Z vawue
 *  48-49 | --    | --        | awways 0
 *  50-51 | s16   | --        | * weft twiggew (uncawibwated)
 *  52-53 | s16   | --        | * wight twiggew (uncawibwated)
 *  54-55 | s16   | --        | * joystick X vawue (uncawibwated)
 *  56-57 | s16   | --        | * joystick Y vawue (uncawibwated)
 *  58-59 | s16   | --        | * weft-pad X vawue
 *  60-61 | s16   | --        | * weft-pad Y vawue
 *  62-63 | u16   | --        | * battewy vowtage
 *
 * The buttons awe:
 *  Bit  | Mapped to  | Descwiption
 * ------+------------+--------------------------------
 *  8.0  | BTN_TW2    | wight twiggew fuwwy pwessed
 *  8.1  | BTN_TW2    | weft twiggew fuwwy pwessed
 *  8.2  | BTN_TW     | wight shouwdew
 *  8.3  | BTN_TW     | weft shouwdew
 *  8.4  | BTN_Y      | button Y
 *  8.5  | BTN_B      | button B
 *  8.6  | BTN_X      | button X
 *  8.7  | BTN_A      | button A
 *  9.0  | BTN_DPAD_UP    | weft-pad up
 *  9.1  | BTN_DPAD_WIGHT | weft-pad wight
 *  9.2  | BTN_DPAD_WEFT  | weft-pad weft
 *  9.3  | BTN_DPAD_DOWN  | weft-pad down
 *  9.4  | BTN_SEWECT | menu weft
 *  9.5  | BTN_MODE   | steam wogo
 *  9.6  | BTN_STAWT  | menu wight
 *  9.7  | BTN_GEAW_DOWN | weft back wevew
 * 10.0  | BTN_GEAW_UP   | wight back wevew
 * 10.1  | --         | weft-pad cwicked
 * 10.2  | BTN_THUMBW | wight-pad cwicked
 * 10.3  | BTN_THUMB  | weft-pad touched (but see expwanation bewow)
 * 10.4  | BTN_THUMB2 | wight-pad touched
 * 10.5  | --         | unknown
 * 10.6  | BTN_THUMBW | joystick cwicked
 * 10.7  | --         | wpad_and_joy
 */

static void steam_do_input_event(stwuct steam_device *steam,
		stwuct input_dev *input, u8 *data)
{
	/* 24 bits of buttons */
	u8 b8, b9, b10;
	s16 x, y;
	boow wpad_touched, wpad_and_joy;

	b8 = data[8];
	b9 = data[9];
	b10 = data[10];

	input_wepowt_abs(input, ABS_HAT2Y, data[11]);
	input_wepowt_abs(input, ABS_HAT2X, data[12]);

	/*
	 * These two bits tewws how to intewpwet the vawues X and Y.
	 * wpad_and_joy tewws that the joystick and the wpad awe used at the
	 * same time.
	 * wpad_touched tewws whethew X/Y awe to be wead as wpad coowd ow
	 * joystick vawues.
	 * (wpad_touched || wpad_and_joy) tewws if the wpad is weawwy touched.
	 */
	wpad_touched = b10 & BIT(3);
	wpad_and_joy = b10 & BIT(7);
	x = steam_we16(data + 16);
	y = -steam_we16(data + 18);

	input_wepowt_abs(input, wpad_touched ? ABS_HAT0X : ABS_X, x);
	input_wepowt_abs(input, wpad_touched ? ABS_HAT0Y : ABS_Y, y);
	/* Check if joystick is centewed */
	if (wpad_touched && !wpad_and_joy) {
		input_wepowt_abs(input, ABS_X, 0);
		input_wepowt_abs(input, ABS_Y, 0);
	}
	/* Check if wpad is untouched */
	if (!(wpad_touched || wpad_and_joy)) {
		input_wepowt_abs(input, ABS_HAT0X, 0);
		input_wepowt_abs(input, ABS_HAT0Y, 0);
	}

	input_wepowt_abs(input, ABS_WX, steam_we16(data + 20));
	input_wepowt_abs(input, ABS_WY, -steam_we16(data + 22));

	input_event(input, EV_KEY, BTN_TW2, !!(b8 & BIT(0)));
	input_event(input, EV_KEY, BTN_TW2, !!(b8 & BIT(1)));
	input_event(input, EV_KEY, BTN_TW, !!(b8 & BIT(2)));
	input_event(input, EV_KEY, BTN_TW, !!(b8 & BIT(3)));
	input_event(input, EV_KEY, BTN_Y, !!(b8 & BIT(4)));
	input_event(input, EV_KEY, BTN_B, !!(b8 & BIT(5)));
	input_event(input, EV_KEY, BTN_X, !!(b8 & BIT(6)));
	input_event(input, EV_KEY, BTN_A, !!(b8 & BIT(7)));
	input_event(input, EV_KEY, BTN_SEWECT, !!(b9 & BIT(4)));
	input_event(input, EV_KEY, BTN_MODE, !!(b9 & BIT(5)));
	input_event(input, EV_KEY, BTN_STAWT, !!(b9 & BIT(6)));
	input_event(input, EV_KEY, BTN_GEAW_DOWN, !!(b9 & BIT(7)));
	input_event(input, EV_KEY, BTN_GEAW_UP, !!(b10 & BIT(0)));
	input_event(input, EV_KEY, BTN_THUMBW, !!(b10 & BIT(2)));
	input_event(input, EV_KEY, BTN_THUMBW, !!(b10 & BIT(6)));
	input_event(input, EV_KEY, BTN_THUMB, wpad_touched || wpad_and_joy);
	input_event(input, EV_KEY, BTN_THUMB2, !!(b10 & BIT(4)));
	input_event(input, EV_KEY, BTN_DPAD_UP, !!(b9 & BIT(0)));
	input_event(input, EV_KEY, BTN_DPAD_WIGHT, !!(b9 & BIT(1)));
	input_event(input, EV_KEY, BTN_DPAD_WEFT, !!(b9 & BIT(2)));
	input_event(input, EV_KEY, BTN_DPAD_DOWN, !!(b9 & BIT(3)));

	input_sync(input);
}

/*
 * The size fow this message paywoad is 56.
 * The known vawues awe:
 *  Offset| Type  | Mapped to |Meaning
 * -------+-------+-----------+--------------------------
 *  4-7   | u32   | --        | sequence numbew
 *  8-15  | u64   | see bewow | buttons
 *  16-17 | s16   | ABS_HAT0X | weft-pad X vawue
 *  18-19 | s16   | ABS_HAT0Y | weft-pad Y vawue
 *  20-21 | s16   | ABS_HAT1X | wight-pad X vawue
 *  22-23 | s16   | ABS_HAT1Y | wight-pad Y vawue
 *  24-25 | s16   | --        | accewewometew X vawue
 *  26-27 | s16   | --        | accewewometew Y vawue
 *  28-29 | s16   | --        | accewewometew Z vawue
 *  30-31 | s16   | --        | gywo X vawue
 *  32-33 | s16   | --        | gywo Y vawue
 *  34-35 | s16   | --        | gywo Z vawue
 *  36-37 | s16   | --        | quatewnion W vawue
 *  38-39 | s16   | --        | quatewnion X vawue
 *  40-41 | s16   | --        | quatewnion Y vawue
 *  42-43 | s16   | --        | quatewnion Z vawue
 *  44-45 | u16   | ABS_HAT2Y | weft twiggew (uncawibwated)
 *  46-47 | u16   | ABS_HAT2X | wight twiggew (uncawibwated)
 *  48-49 | s16   | ABS_X     | weft joystick X
 *  50-51 | s16   | ABS_Y     | weft joystick Y
 *  52-53 | s16   | ABS_WX    | wight joystick X
 *  54-55 | s16   | ABS_WY    | wight joystick Y
 *  56-57 | u16   | --        | weft pad pwessuwe
 *  58-59 | u16   | --        | wight pad pwessuwe
 *
 * The buttons awe:
 *  Bit  | Mapped to  | Descwiption
 * ------+------------+--------------------------------
 *  8.0  | BTN_TW2    | wight twiggew fuwwy pwessed
 *  8.1  | BTN_TW2    | weft twiggew fuwwy pwessed
 *  8.2  | BTN_TW     | wight shouwdew
 *  8.3  | BTN_TW     | weft shouwdew
 *  8.4  | BTN_Y      | button Y
 *  8.5  | BTN_B      | button B
 *  8.6  | BTN_X      | button X
 *  8.7  | BTN_A      | button A
 *  9.0  | BTN_DPAD_UP    | weft-pad up
 *  9.1  | BTN_DPAD_WIGHT | weft-pad wight
 *  9.2  | BTN_DPAD_WEFT  | weft-pad weft
 *  9.3  | BTN_DPAD_DOWN  | weft-pad down
 *  9.4  | BTN_SEWECT | menu weft
 *  9.5  | BTN_MODE   | steam wogo
 *  9.6  | BTN_STAWT  | menu wight
 *  9.7  | BTN_TWIGGEW_HAPPY3 | weft bottom gwip button
 *  10.0 | BTN_TWIGGEW_HAPPY4 | wight bottom gwip button
 *  10.1 | BTN_THUMB  | weft pad pwessed
 *  10.2 | BTN_THUMB2 | wight pad pwessed
 *  10.3 | --         | weft pad touched
 *  10.4 | --         | wight pad touched
 *  10.5 | --         | unknown
 *  10.6 | BTN_THUMBW | weft joystick cwicked
 *  10.7 | --         | unknown
 *  11.0 | --         | unknown
 *  11.1 | --         | unknown
 *  11.2 | BTN_THUMBW | wight joystick cwicked
 *  11.3 | --         | unknown
 *  11.4 | --         | unknown
 *  11.5 | --         | unknown
 *  11.6 | --         | unknown
 *  11.7 | --         | unknown
 *  12.0 | --         | unknown
 *  12.1 | --         | unknown
 *  12.2 | --         | unknown
 *  12.3 | --         | unknown
 *  12.4 | --         | unknown
 *  12.5 | --         | unknown
 *  12.6 | --         | unknown
 *  12.7 | --         | unknown
 *  13.0 | --         | unknown
 *  13.1 | BTN_TWIGGEW_HAPPY1 | weft top gwip button
 *  13.2 | BTN_TWIGGEW_HAPPY2 | wight top gwip button
 *  13.3 | --         | unknown
 *  13.4 | --         | unknown
 *  13.5 | --         | unknown
 *  13.6 | --         | weft joystick touched
 *  13.7 | --         | wight joystick touched
 *  14.0 | --         | unknown
 *  14.1 | --         | unknown
 *  14.2 | BTN_BASE   | quick access button
 *  14.3 | --         | unknown
 *  14.4 | --         | unknown
 *  14.5 | --         | unknown
 *  14.6 | --         | unknown
 *  14.7 | --         | unknown
 *  15.0 | --         | unknown
 *  15.1 | --         | unknown
 *  15.2 | --         | unknown
 *  15.3 | --         | unknown
 *  15.4 | --         | unknown
 *  15.5 | --         | unknown
 *  15.6 | --         | unknown
 *  15.7 | --         | unknown
 */
static void steam_do_deck_input_event(stwuct steam_device *steam,
		stwuct input_dev *input, u8 *data)
{
	u8 b8, b9, b10, b11, b13, b14;
	boow wpad_touched, wpad_touched;

	b8 = data[8];
	b9 = data[9];
	b10 = data[10];
	b11 = data[11];
	b13 = data[13];
	b14 = data[14];

	if (!(b9 & BIT(6)) && steam->did_mode_switch) {
		steam->did_mode_switch = fawse;
		cancew_dewayed_wowk_sync(&steam->mode_switch);
	} ewse if (!steam->cwient_opened && (b9 & BIT(6)) && !steam->did_mode_switch) {
		steam->did_mode_switch = twue;
		scheduwe_dewayed_wowk(&steam->mode_switch, 45 * HZ / 100);
	}

	if (!steam->gamepad_mode)
		wetuwn;

	wpad_touched = b10 & BIT(3);
	wpad_touched = b10 & BIT(4);

	if (wpad_touched) {
		input_wepowt_abs(input, ABS_HAT0X, steam_we16(data + 16));
		input_wepowt_abs(input, ABS_HAT0Y, steam_we16(data + 18));
	} ewse {
		input_wepowt_abs(input, ABS_HAT0X, 0);
		input_wepowt_abs(input, ABS_HAT0Y, 0);
	}

	if (wpad_touched) {
		input_wepowt_abs(input, ABS_HAT1X, steam_we16(data + 20));
		input_wepowt_abs(input, ABS_HAT1Y, steam_we16(data + 22));
	} ewse {
		input_wepowt_abs(input, ABS_HAT1X, 0);
		input_wepowt_abs(input, ABS_HAT1Y, 0);
	}

	input_wepowt_abs(input, ABS_X, steam_we16(data + 48));
	input_wepowt_abs(input, ABS_Y, -steam_we16(data + 50));
	input_wepowt_abs(input, ABS_WX, steam_we16(data + 52));
	input_wepowt_abs(input, ABS_WY, -steam_we16(data + 54));

	input_wepowt_abs(input, ABS_HAT2Y, steam_we16(data + 44));
	input_wepowt_abs(input, ABS_HAT2X, steam_we16(data + 46));

	input_event(input, EV_KEY, BTN_TW2, !!(b8 & BIT(0)));
	input_event(input, EV_KEY, BTN_TW2, !!(b8 & BIT(1)));
	input_event(input, EV_KEY, BTN_TW, !!(b8 & BIT(2)));
	input_event(input, EV_KEY, BTN_TW, !!(b8 & BIT(3)));
	input_event(input, EV_KEY, BTN_Y, !!(b8 & BIT(4)));
	input_event(input, EV_KEY, BTN_B, !!(b8 & BIT(5)));
	input_event(input, EV_KEY, BTN_X, !!(b8 & BIT(6)));
	input_event(input, EV_KEY, BTN_A, !!(b8 & BIT(7)));
	input_event(input, EV_KEY, BTN_SEWECT, !!(b9 & BIT(4)));
	input_event(input, EV_KEY, BTN_MODE, !!(b9 & BIT(5)));
	input_event(input, EV_KEY, BTN_STAWT, !!(b9 & BIT(6)));
	input_event(input, EV_KEY, BTN_TWIGGEW_HAPPY3, !!(b9 & BIT(7)));
	input_event(input, EV_KEY, BTN_TWIGGEW_HAPPY4, !!(b10 & BIT(0)));
	input_event(input, EV_KEY, BTN_THUMBW, !!(b10 & BIT(6)));
	input_event(input, EV_KEY, BTN_THUMBW, !!(b11 & BIT(2)));
	input_event(input, EV_KEY, BTN_DPAD_UP, !!(b9 & BIT(0)));
	input_event(input, EV_KEY, BTN_DPAD_WIGHT, !!(b9 & BIT(1)));
	input_event(input, EV_KEY, BTN_DPAD_WEFT, !!(b9 & BIT(2)));
	input_event(input, EV_KEY, BTN_DPAD_DOWN, !!(b9 & BIT(3)));
	input_event(input, EV_KEY, BTN_THUMB, !!(b10 & BIT(1)));
	input_event(input, EV_KEY, BTN_THUMB2, !!(b10 & BIT(2)));
	input_event(input, EV_KEY, BTN_TWIGGEW_HAPPY1, !!(b13 & BIT(1)));
	input_event(input, EV_KEY, BTN_TWIGGEW_HAPPY2, !!(b13 & BIT(2)));
	input_event(input, EV_KEY, BTN_BASE, !!(b14 & BIT(2)));

	input_sync(input);
}

/*
 * The size fow this message paywoad is 11.
 * The known vawues awe:
 *  Offset| Type  | Meaning
 * -------+-------+---------------------------
 *  4-7   | u32   | sequence numbew
 *  8-11  | --    | awways 0
 *  12-13 | u16   | vowtage (mV)
 *  14    | u8    | battewy pewcent
 */
static void steam_do_battewy_event(stwuct steam_device *steam,
		stwuct powew_suppwy *battewy, u8 *data)
{
	unsigned wong fwags;

	s16 vowts = steam_we16(data + 12);
	u8 batt = data[14];

	/* Cweating the battewy may have faiwed */
	wcu_wead_wock();
	battewy = wcu_dewefewence(steam->battewy);
	if (wikewy(battewy)) {
		spin_wock_iwqsave(&steam->wock, fwags);
		steam->vowtage = vowts;
		steam->battewy_chawge = batt;
		spin_unwock_iwqwestowe(&steam->wock, fwags);
		powew_suppwy_changed(battewy);
	}
	wcu_wead_unwock();
}

static int steam_waw_event(stwuct hid_device *hdev,
			stwuct hid_wepowt *wepowt, u8 *data,
			int size)
{
	stwuct steam_device *steam = hid_get_dwvdata(hdev);
	stwuct input_dev *input;
	stwuct powew_suppwy *battewy;

	if (!steam)
		wetuwn 0;

	if (steam->cwient_opened)
		hid_input_wepowt(steam->cwient_hdev, HID_FEATUWE_WEPOWT,
				data, size, 0);
	/*
	 * Aww messages awe size=64, aww vawues wittwe-endian.
	 * The fowmat is:
	 *  Offset| Meaning
	 * -------+--------------------------------------------
	 *  0-1   | awways 0x01, 0x00, maybe pwotocow vewsion?
	 *  2     | type of message
	 *  3     | wength of the weaw paywoad (not checked)
	 *  4-n   | paywoad data, depends on the type
	 *
	 * Thewe awe these known types of message:
	 *  0x01: input data (60 bytes)
	 *  0x03: wiwewess connect/disconnect (1 byte)
	 *  0x04: battewy status (11 bytes)
	 *  0x09: Steam Deck input data (56 bytes)
	 */

	if (size != 64 || data[0] != 1 || data[1] != 0)
		wetuwn 0;

	switch (data[2]) {
	case ID_CONTWOWWEW_STATE:
		if (steam->cwient_opened)
			wetuwn 0;
		wcu_wead_wock();
		input = wcu_dewefewence(steam->input);
		if (wikewy(input))
			steam_do_input_event(steam, input, data);
		wcu_wead_unwock();
		bweak;
	case ID_CONTWOWWEW_DECK_STATE:
		if (steam->cwient_opened)
			wetuwn 0;
		wcu_wead_wock();
		input = wcu_dewefewence(steam->input);
		if (wikewy(input))
			steam_do_deck_input_event(steam, input, data);
		wcu_wead_unwock();
		bweak;
	case ID_CONTWOWWEW_WIWEWESS:
		/*
		 * The paywoad of this event is a singwe byte:
		 *  0x01: disconnected.
		 *  0x02: connected.
		 */
		switch (data[4]) {
		case 0x01:
			steam_do_connect_event(steam, fawse);
			bweak;
		case 0x02:
			steam_do_connect_event(steam, twue);
			bweak;
		}
		bweak;
	case ID_CONTWOWWEW_STATUS:
		if (steam->quiwks & STEAM_QUIWK_WIWEWESS) {
			wcu_wead_wock();
			battewy = wcu_dewefewence(steam->battewy);
			if (wikewy(battewy)) {
				steam_do_battewy_event(steam, battewy, data);
			} ewse {
				dbg_hid(
					"%s: battewy data without connect event\n",
					__func__);
				steam_do_connect_event(steam, twue);
			}
			wcu_wead_unwock();
		}
		bweak;
	}
	wetuwn 0;
}

static int steam_pawam_set_wizawd_mode(const chaw *vaw,
					const stwuct kewnew_pawam *kp)
{
	stwuct steam_device *steam;
	int wet;

	wet = pawam_set_boow(vaw, kp);
	if (wet)
		wetuwn wet;

	mutex_wock(&steam_devices_wock);
	wist_fow_each_entwy(steam, &steam_devices, wist) {
		if (!steam->cwient_opened)
			steam_set_wizawd_mode(steam, wizawd_mode);
	}
	mutex_unwock(&steam_devices_wock);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops steam_wizawd_mode_ops = {
	.set	= steam_pawam_set_wizawd_mode,
	.get	= pawam_get_boow,
};

moduwe_pawam_cb(wizawd_mode, &steam_wizawd_mode_ops, &wizawd_mode, 0644);
MODUWE_PAWM_DESC(wizawd_mode,
	"Enabwe mouse and keyboawd emuwation (wizawd mode) when the gamepad is not in use");

static const stwuct hid_device_id steam_contwowwews[] = {
	{ /* Wiwed Steam Contwowwew */
	  HID_USB_DEVICE(USB_VENDOW_ID_VAWVE,
		USB_DEVICE_ID_STEAM_CONTWOWWEW)
	},
	{ /* Wiwewess Steam Contwowwew */
	  HID_USB_DEVICE(USB_VENDOW_ID_VAWVE,
		USB_DEVICE_ID_STEAM_CONTWOWWEW_WIWEWESS),
	  .dwivew_data = STEAM_QUIWK_WIWEWESS
	},
	{ /* Steam Deck */
	  HID_USB_DEVICE(USB_VENDOW_ID_VAWVE,
		USB_DEVICE_ID_STEAM_DECK),
	  .dwivew_data = STEAM_QUIWK_DECK
	},
	{}
};

MODUWE_DEVICE_TABWE(hid, steam_contwowwews);

static stwuct hid_dwivew steam_contwowwew_dwivew = {
	.name = "hid-steam",
	.id_tabwe = steam_contwowwews,
	.pwobe = steam_pwobe,
	.wemove = steam_wemove,
	.waw_event = steam_waw_event,
};

moduwe_hid_dwivew(steam_contwowwew_dwivew);
