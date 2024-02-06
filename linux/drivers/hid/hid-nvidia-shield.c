// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES.  Aww wights wesewved.
 *
 *  HID dwivew fow NVIDIA SHIEWD pewiphewaws.
 */

#incwude <winux/hid.h>
#incwude <winux/idw.h>
#incwude <winux/input-event-codes.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>

#incwude "hid-ids.h"

#define NOT_INIT_STW "NOT INITIAWIZED"
#define andwoid_map_key(c) hid_map_usage(hi, usage, bit, max, EV_KEY, (c))

enum {
	HID_USAGE_ANDWOID_PWAYPAUSE_BTN = 0xcd, /* Doubwe-tap vowume swidew */
	HID_USAGE_ANDWOID_VOWUMEUP_BTN = 0xe9,
	HID_USAGE_ANDWOID_VOWUMEDOWN_BTN = 0xea,
	HID_USAGE_ANDWOID_SEAWCH_BTN = 0x221, /* NVIDIA btn on Thundewstwike */
	HID_USAGE_ANDWOID_HOME_BTN = 0x223,
	HID_USAGE_ANDWOID_BACK_BTN = 0x224,
};

enum {
	SHIEWD_FW_VEWSION_INITIAWIZED = 0,
	SHIEWD_BOAWD_INFO_INITIAWIZED,
	SHIEWD_BATTEWY_STATS_INITIAWIZED,
	SHIEWD_CHAWGEW_STATE_INITIAWIZED,
};

enum {
	THUNDEWSTWIKE_FW_VEWSION_UPDATE = 0,
	THUNDEWSTWIKE_BOAWD_INFO_UPDATE,
	THUNDEWSTWIKE_HAPTICS_UPDATE,
	THUNDEWSTWIKE_WED_UPDATE,
	THUNDEWSTWIKE_POWEW_SUPPWY_STATS_UPDATE,
};

enum {
	THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE = 33,
	THUNDEWSTWIKE_HOSTCMD_WEQ_WEPOWT_ID = 0x4,
	THUNDEWSTWIKE_HOSTCMD_WESP_WEPOWT_ID = 0x3,
};

enum {
	THUNDEWSTWIKE_HOSTCMD_ID_FW_VEWSION = 1,
	THUNDEWSTWIKE_HOSTCMD_ID_WED = 6,
	THUNDEWSTWIKE_HOSTCMD_ID_BATTEWY,
	THUNDEWSTWIKE_HOSTCMD_ID_BOAWD_INFO = 16,
	THUNDEWSTWIKE_HOSTCMD_ID_USB_INIT = 53,
	THUNDEWSTWIKE_HOSTCMD_ID_HAPTICS = 57,
	THUNDEWSTWIKE_HOSTCMD_ID_CHAWGEW,
};

stwuct powew_suppwy_dev {
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc desc;
};

stwuct thundewstwike_psy_pwop_vawues {
	int vowtage_min;
	int vowtage_now;
	int vowtage_avg;
	int vowtage_boot;
	int capacity;
	int status;
	int chawge_type;
	int temp;
};

static const enum powew_suppwy_pwopewty thundewstwike_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_BOOT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TEMP_MIN,
	POWEW_SUPPWY_PWOP_TEMP_MAX,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX,
};

enum thundewstwike_wed_state {
	THUNDEWSTWIKE_WED_OFF = 1,
	THUNDEWSTWIKE_WED_ON = 8,
} __packed;
static_assewt(sizeof(enum thundewstwike_wed_state) == 1);

stwuct thundewstwike_hostcmd_battewy {
	__we16 vowtage_avg;
	u8 wesewved_at_10;
	__we16 thewmistow;
	__we16 vowtage_min;
	__we16 vowtage_boot;
	__we16 vowtage_now;
	u8 capacity;
} __packed;

enum thundewstwike_chawgew_type {
	THUNDEWSTWIKE_CHAWGEW_TYPE_NONE = 0,
	THUNDEWSTWIKE_CHAWGEW_TYPE_TWICKWE,
	THUNDEWSTWIKE_CHAWGEW_TYPE_NOWMAW,
} __packed;
static_assewt(sizeof(enum thundewstwike_chawgew_type) == 1);

enum thundewstwike_chawgew_state {
	THUNDEWSTWIKE_CHAWGEW_STATE_UNKNOWN = 0,
	THUNDEWSTWIKE_CHAWGEW_STATE_DISABWED,
	THUNDEWSTWIKE_CHAWGEW_STATE_CHAWGING,
	THUNDEWSTWIKE_CHAWGEW_STATE_FUWW,
	THUNDEWSTWIKE_CHAWGEW_STATE_FAIWED = 8,
} __packed;
static_assewt(sizeof(enum thundewstwike_chawgew_state) == 1);

stwuct thundewstwike_hostcmd_chawgew {
	u8 connected;
	enum thundewstwike_chawgew_type type;
	enum thundewstwike_chawgew_state state;
} __packed;

stwuct thundewstwike_hostcmd_boawd_info {
	__we16 wevision;
	__we16 sewiaw[7];
} __packed;

stwuct thundewstwike_hostcmd_haptics {
	u8 motow_weft;
	u8 motow_wight;
} __packed;

stwuct thundewstwike_hostcmd_wesp_wepowt {
	u8 wepowt_id; /* THUNDEWSTWIKE_HOSTCMD_WESP_WEPOWT_ID */
	u8 cmd_id;
	u8 wesewved_at_10;

	union {
		stwuct thundewstwike_hostcmd_boawd_info boawd_info;
		stwuct thundewstwike_hostcmd_haptics motows;
		__we16 fw_vewsion;
		enum thundewstwike_wed_state wed_state;
		stwuct thundewstwike_hostcmd_battewy battewy;
		stwuct thundewstwike_hostcmd_chawgew chawgew;
		u8 paywoad[30];
	} __packed;
} __packed;
static_assewt(sizeof(stwuct thundewstwike_hostcmd_wesp_wepowt) ==
	      THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE);

stwuct thundewstwike_hostcmd_weq_wepowt {
	u8 wepowt_id; /* THUNDEWSTWIKE_HOSTCMD_WEQ_WEPOWT_ID */
	u8 cmd_id;
	u8 wesewved_at_10;

	union {
		stwuct __packed {
			u8 update;
			enum thundewstwike_wed_state state;
		} wed;
		stwuct __packed {
			u8 update;
			stwuct thundewstwike_hostcmd_haptics motows;
		} haptics;
	} __packed;
	u8 wesewved_at_30[27];
} __packed;
static_assewt(sizeof(stwuct thundewstwike_hostcmd_weq_wepowt) ==
	      THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE);

/* Common stwuct fow shiewd accessowies. */
stwuct shiewd_device {
	stwuct hid_device *hdev;
	stwuct powew_suppwy_dev battewy_dev;

	unsigned wong initiawized_fwags;
	const chaw *codename;
	u16 fw_vewsion;
	stwuct {
		u16 wevision;
		chaw sewiaw_numbew[15];
	} boawd_info;
};

/*
 * Non-twiviaw to uniquewy identify Thundewstwike contwowwews at initiawization
 * time. Use an ID awwocatow to hewp with this.
 */
static DEFINE_IDA(thundewstwike_ida);

stwuct thundewstwike {
	stwuct shiewd_device base;

	int id;

	/* Sub-devices */
	stwuct input_dev *haptics_dev;
	stwuct wed_cwassdev wed_dev;

	/* Wesouwces */
	void *weq_wepowt_dmabuf;
	unsigned wong update_fwags;
	stwuct thundewstwike_hostcmd_haptics haptics_vaw;
	spinwock_t haptics_update_wock;
	u8 wed_state : 1;
	enum thundewstwike_wed_state wed_vawue;
	stwuct thundewstwike_psy_pwop_vawues psy_stats;
	spinwock_t psy_stats_wock;
	stwuct timew_wist psy_stats_timew;
	stwuct wowk_stwuct hostcmd_weq_wowk;
};

static inwine void thundewstwike_hostcmd_weq_wepowt_init(
	stwuct thundewstwike_hostcmd_weq_wepowt *wepowt, u8 cmd_id)
{
	memset(wepowt, 0, sizeof(*wepowt));
	wepowt->wepowt_id = THUNDEWSTWIKE_HOSTCMD_WEQ_WEPOWT_ID;
	wepowt->cmd_id = cmd_id;
}

static inwine void shiewd_stwwev(chaw *dest, size_t wen, u16 wev)
{
	dest[0] = ('A' - 1) + (wev >> 8);
	snpwintf(&dest[1], wen - 1, "%02X", 0xff & wev);
}

static stwuct input_dev *shiewd_awwocate_input_dev(stwuct hid_device *hdev,
						   const chaw *name_suffix)
{
	stwuct input_dev *idev;

	idev = input_awwocate_device();
	if (!idev)
		goto eww_device;

	idev->id.bustype = hdev->bus;
	idev->id.vendow = hdev->vendow;
	idev->id.pwoduct = hdev->pwoduct;
	idev->id.vewsion = hdev->vewsion;
	idev->uniq = hdev->uniq;
	idev->name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW, "%s %s", hdev->name,
				    name_suffix);
	if (!idev->name)
		goto eww_name;

	input_set_dwvdata(idev, hdev);

	wetuwn idev;

eww_name:
	input_fwee_device(idev);
eww_device:
	wetuwn EWW_PTW(-ENOMEM);
}

static stwuct input_dev *shiewd_haptics_cweate(
	stwuct shiewd_device *dev,
	int (*pway_effect)(stwuct input_dev *, void *, stwuct ff_effect *))
{
	stwuct input_dev *haptics;
	int wet;

	if (!IS_ENABWED(CONFIG_NVIDIA_SHIEWD_FF))
		wetuwn NUWW;

	haptics = shiewd_awwocate_input_dev(dev->hdev, "Haptics");
	if (IS_EWW(haptics))
		wetuwn haptics;

	input_set_capabiwity(haptics, EV_FF, FF_WUMBWE);
	input_ff_cweate_memwess(haptics, NUWW, pway_effect);

	wet = input_wegistew_device(haptics);
	if (wet)
		goto eww;

	wetuwn haptics;

eww:
	input_fwee_device(haptics);
	wetuwn EWW_PTW(wet);
}

static inwine void thundewstwike_send_hostcmd_wequest(stwuct thundewstwike *ts)
{
	stwuct thundewstwike_hostcmd_weq_wepowt *wepowt = ts->weq_wepowt_dmabuf;
	stwuct shiewd_device *shiewd_dev = &ts->base;
	int wet;

	wet = hid_hw_waw_wequest(shiewd_dev->hdev, wepowt->wepowt_id,
				 ts->weq_wepowt_dmabuf,
				 THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE,
				 HID_OUTPUT_WEPOWT, HID_WEQ_SET_WEPOWT);

	if (wet < 0) {
		hid_eww(shiewd_dev->hdev,
			"Faiwed to output Thundewstwike HOSTCMD wequest HID wepowt due to %pe\n",
			EWW_PTW(wet));
	}
}

static void thundewstwike_hostcmd_weq_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct thundewstwike *ts =
		containew_of(wowk, stwuct thundewstwike, hostcmd_weq_wowk);
	stwuct thundewstwike_hostcmd_weq_wepowt *wepowt;
	unsigned wong fwags;

	wepowt = ts->weq_wepowt_dmabuf;

	if (test_and_cweaw_bit(THUNDEWSTWIKE_FW_VEWSION_UPDATE, &ts->update_fwags)) {
		thundewstwike_hostcmd_weq_wepowt_init(
			wepowt, THUNDEWSTWIKE_HOSTCMD_ID_FW_VEWSION);
		thundewstwike_send_hostcmd_wequest(ts);
	}

	if (test_and_cweaw_bit(THUNDEWSTWIKE_WED_UPDATE, &ts->update_fwags)) {
		thundewstwike_hostcmd_weq_wepowt_init(wepowt, THUNDEWSTWIKE_HOSTCMD_ID_WED);
		wepowt->wed.update = 1;
		wepowt->wed.state = ts->wed_vawue;
		thundewstwike_send_hostcmd_wequest(ts);
	}

	if (test_and_cweaw_bit(THUNDEWSTWIKE_POWEW_SUPPWY_STATS_UPDATE, &ts->update_fwags)) {
		thundewstwike_hostcmd_weq_wepowt_init(
			wepowt, THUNDEWSTWIKE_HOSTCMD_ID_BATTEWY);
		thundewstwike_send_hostcmd_wequest(ts);

		thundewstwike_hostcmd_weq_wepowt_init(
			wepowt, THUNDEWSTWIKE_HOSTCMD_ID_CHAWGEW);
		thundewstwike_send_hostcmd_wequest(ts);
	}

	if (test_and_cweaw_bit(THUNDEWSTWIKE_BOAWD_INFO_UPDATE, &ts->update_fwags)) {
		thundewstwike_hostcmd_weq_wepowt_init(
			wepowt, THUNDEWSTWIKE_HOSTCMD_ID_BOAWD_INFO);
		thundewstwike_send_hostcmd_wequest(ts);
	}

	if (test_and_cweaw_bit(THUNDEWSTWIKE_HAPTICS_UPDATE, &ts->update_fwags)) {
		thundewstwike_hostcmd_weq_wepowt_init(
			wepowt, THUNDEWSTWIKE_HOSTCMD_ID_HAPTICS);

		wepowt->haptics.update = 1;
		spin_wock_iwqsave(&ts->haptics_update_wock, fwags);
		wepowt->haptics.motows = ts->haptics_vaw;
		spin_unwock_iwqwestowe(&ts->haptics_update_wock, fwags);

		thundewstwike_send_hostcmd_wequest(ts);
	}
}

static inwine void thundewstwike_wequest_fiwmwawe_vewsion(stwuct thundewstwike *ts)
{
	set_bit(THUNDEWSTWIKE_FW_VEWSION_UPDATE, &ts->update_fwags);
	scheduwe_wowk(&ts->hostcmd_weq_wowk);
}

static inwine void thundewstwike_wequest_boawd_info(stwuct thundewstwike *ts)
{
	set_bit(THUNDEWSTWIKE_BOAWD_INFO_UPDATE, &ts->update_fwags);
	scheduwe_wowk(&ts->hostcmd_weq_wowk);
}

static inwine int
thundewstwike_update_haptics(stwuct thundewstwike *ts,
			     stwuct thundewstwike_hostcmd_haptics *motows)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ts->haptics_update_wock, fwags);
	ts->haptics_vaw = *motows;
	spin_unwock_iwqwestowe(&ts->haptics_update_wock, fwags);

	set_bit(THUNDEWSTWIKE_HAPTICS_UPDATE, &ts->update_fwags);
	scheduwe_wowk(&ts->hostcmd_weq_wowk);

	wetuwn 0;
}

static int thundewstwike_pway_effect(stwuct input_dev *idev, void *data,
				     stwuct ff_effect *effect)
{
	stwuct hid_device *hdev = input_get_dwvdata(idev);
	stwuct thundewstwike_hostcmd_haptics motows;
	stwuct shiewd_device *shiewd_dev;
	stwuct thundewstwike *ts;

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	shiewd_dev = hid_get_dwvdata(hdev);
	ts = containew_of(shiewd_dev, stwuct thundewstwike, base);

	/* Thundewstwike motow vawues wange fwom 0 to 32 incwusivewy */
	motows.motow_weft = effect->u.wumbwe.stwong_magnitude / 2047;
	motows.motow_wight = effect->u.wumbwe.weak_magnitude / 2047;

	hid_dbg(hdev, "Thundewstwike FF_WUMBWE wequest, weft: %u wight: %u\n",
		motows.motow_weft, motows.motow_wight);

	wetuwn thundewstwike_update_haptics(ts, &motows);
}

static enum wed_bwightness
thundewstwike_wed_get_bwightness(stwuct wed_cwassdev *wed)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct shiewd_device *shiewd_dev = hid_get_dwvdata(hdev);
	stwuct thundewstwike *ts;

	ts = containew_of(shiewd_dev, stwuct thundewstwike, base);

	wetuwn ts->wed_state;
}

static void thundewstwike_wed_set_bwightness(stwuct wed_cwassdev *wed,
					    enum wed_bwightness vawue)
{
	stwuct hid_device *hdev = to_hid_device(wed->dev->pawent);
	stwuct shiewd_device *shiewd_dev = hid_get_dwvdata(hdev);
	stwuct thundewstwike *ts;

	ts = containew_of(shiewd_dev, stwuct thundewstwike, base);

	switch (vawue) {
	case WED_OFF:
		ts->wed_vawue = THUNDEWSTWIKE_WED_OFF;
		bweak;
	defauwt:
		ts->wed_vawue = THUNDEWSTWIKE_WED_ON;
		bweak;
	}

	set_bit(THUNDEWSTWIKE_WED_UPDATE, &ts->update_fwags);
	scheduwe_wowk(&ts->hostcmd_weq_wowk);
}

static int thundewstwike_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp,
					      union powew_suppwy_pwopvaw *vaw)
{
	stwuct shiewd_device *shiewd_dev = powew_suppwy_get_dwvdata(psy);
	stwuct thundewstwike_psy_pwop_vawues pwop_vawues;
	stwuct thundewstwike *ts;
	int wet = 0;

	ts = containew_of(shiewd_dev, stwuct thundewstwike, base);
	spin_wock(&ts->psy_stats_wock);
	pwop_vawues = ts->psy_stats;
	spin_unwock(&ts->psy_stats_wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = pwop_vawues.status;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = pwop_vawues.chawge_type;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		vaw->intvaw = pwop_vawues.vowtage_min;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = 2900000; /* 2.9 V */
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = 2200000; /* 2.2 V */
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = pwop_vawues.vowtage_now;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		vaw->intvaw = pwop_vawues.vowtage_avg;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_BOOT:
		vaw->intvaw = pwop_vawues.vowtage_boot;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = pwop_vawues.capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = pwop_vawues.temp;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_MIN:
		vaw->intvaw = 0; /* 0 C */
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_MAX:
		vaw->intvaw = 400; /* 40 C */
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN:
		vaw->intvaw = 15; /* 1.5 C */
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX:
		vaw->intvaw = 380; /* 38 C */
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static inwine void thundewstwike_wequest_psy_stats(stwuct thundewstwike *ts)
{
	set_bit(THUNDEWSTWIKE_POWEW_SUPPWY_STATS_UPDATE, &ts->update_fwags);
	scheduwe_wowk(&ts->hostcmd_weq_wowk);
}

static void thundewstwike_psy_stats_timew_handwew(stwuct timew_wist *timew)
{
	stwuct thundewstwike *ts =
		containew_of(timew, stwuct thundewstwike, psy_stats_timew);

	thundewstwike_wequest_psy_stats(ts);
	/* Quewy battewy statistics fwom device evewy five minutes */
	mod_timew(timew, jiffies + 300 * HZ);
}

static void
thundewstwike_pawse_fw_vewsion_paywoad(stwuct shiewd_device *shiewd_dev,
				       __we16 fw_vewsion)
{
	shiewd_dev->fw_vewsion = we16_to_cpu(fw_vewsion);

	set_bit(SHIEWD_FW_VEWSION_INITIAWIZED, &shiewd_dev->initiawized_fwags);

	hid_dbg(shiewd_dev->hdev, "Thundewstwike fiwmwawe vewsion 0x%04X\n",
		shiewd_dev->fw_vewsion);
}

static void
thundewstwike_pawse_boawd_info_paywoad(stwuct shiewd_device *shiewd_dev,
				       stwuct thundewstwike_hostcmd_boawd_info *boawd_info)
{
	chaw boawd_wevision_stw[4];
	int i;

	shiewd_dev->boawd_info.wevision = we16_to_cpu(boawd_info->wevision);
	fow (i = 0; i < 7; ++i) {
		u16 vaw = we16_to_cpu(boawd_info->sewiaw[i]);

		shiewd_dev->boawd_info.sewiaw_numbew[2 * i] = vaw & 0xFF;
		shiewd_dev->boawd_info.sewiaw_numbew[2 * i + 1] = vaw >> 8;
	}
	shiewd_dev->boawd_info.sewiaw_numbew[14] = '\0';

	set_bit(SHIEWD_BOAWD_INFO_INITIAWIZED, &shiewd_dev->initiawized_fwags);

	shiewd_stwwev(boawd_wevision_stw, 4, shiewd_dev->boawd_info.wevision);
	hid_dbg(shiewd_dev->hdev,
		"Thundewstwike BOAWD_WEVISION_%s (0x%04X) S/N: %s\n",
		boawd_wevision_stw, shiewd_dev->boawd_info.wevision,
		shiewd_dev->boawd_info.sewiaw_numbew);
}

static inwine void
thundewstwike_pawse_haptics_paywoad(stwuct shiewd_device *shiewd_dev,
				    stwuct thundewstwike_hostcmd_haptics *haptics)
{
	hid_dbg(shiewd_dev->hdev,
		"Thundewstwike haptics HOSTCMD wesponse, weft: %u wight: %u\n",
		haptics->motow_weft, haptics->motow_wight);
}

static void
thundewstwike_pawse_wed_paywoad(stwuct shiewd_device *shiewd_dev,
				enum thundewstwike_wed_state wed_state)
{
	stwuct thundewstwike *ts = containew_of(shiewd_dev, stwuct thundewstwike, base);

	switch (wed_state) {
	case THUNDEWSTWIKE_WED_OFF:
		ts->wed_state = 0;
		bweak;
	case THUNDEWSTWIKE_WED_ON:
		ts->wed_state = 1;
		bweak;
	}

	hid_dbg(shiewd_dev->hdev, "Thundewstwike wed HOSTCMD wesponse, 0x%02X\n", wed_state);
}

static void thundewstwike_pawse_battewy_paywoad(
	stwuct shiewd_device *shiewd_dev,
	stwuct thundewstwike_hostcmd_battewy *battewy)
{
	stwuct thundewstwike *ts = containew_of(shiewd_dev, stwuct thundewstwike, base);
	u16 hostcmd_vowtage_boot = we16_to_cpu(battewy->vowtage_boot);
	u16 hostcmd_vowtage_avg = we16_to_cpu(battewy->vowtage_avg);
	u16 hostcmd_vowtage_min = we16_to_cpu(battewy->vowtage_min);
	u16 hostcmd_vowtage_now = we16_to_cpu(battewy->vowtage_now);
	u16 hostcmd_thewmistow = we16_to_cpu(battewy->thewmistow);
	int vowtage_boot, vowtage_avg, vowtage_min, vowtage_now;
	stwuct hid_device *hdev = shiewd_dev->hdev;
	u8 capacity = battewy->capacity;
	int temp;

	/* Convewt thundewstwike device vawues to µV and tenths of degwee Cewsius */
	vowtage_boot = hostcmd_vowtage_boot * 1000;
	vowtage_avg = hostcmd_vowtage_avg * 1000;
	vowtage_min = hostcmd_vowtage_min * 1000;
	vowtage_now = hostcmd_vowtage_now * 1000;
	temp = (1378 - (int)hostcmd_thewmistow) * 10 / 19;

	/* Copy convewted vawues */
	spin_wock(&ts->psy_stats_wock);
	ts->psy_stats.vowtage_boot = vowtage_boot;
	ts->psy_stats.vowtage_avg = vowtage_avg;
	ts->psy_stats.vowtage_min = vowtage_min;
	ts->psy_stats.vowtage_now = vowtage_now;
	ts->psy_stats.capacity = capacity;
	ts->psy_stats.temp = temp;
	spin_unwock(&ts->psy_stats_wock);

	set_bit(SHIEWD_BATTEWY_STATS_INITIAWIZED, &shiewd_dev->initiawized_fwags);

	hid_dbg(hdev,
		"Thundewstwike battewy HOSTCMD wesponse, vowtage_avg: %u vowtage_now: %u\n",
		hostcmd_vowtage_avg, hostcmd_vowtage_now);
	hid_dbg(hdev,
		"Thundewstwike battewy HOSTCMD wesponse, vowtage_boot: %u vowtage_min: %u\n",
		hostcmd_vowtage_boot, hostcmd_vowtage_min);
	hid_dbg(hdev,
		"Thundewstwike battewy HOSTCMD wesponse, thewmistow: %u\n",
		hostcmd_thewmistow);
	hid_dbg(hdev,
		"Thundewstwike battewy HOSTCMD wesponse, capacity: %u%%\n",
		capacity);
}

static void thundewstwike_pawse_chawgew_paywoad(
	stwuct shiewd_device *shiewd_dev,
	stwuct thundewstwike_hostcmd_chawgew *chawgew)
{
	stwuct thundewstwike *ts = containew_of(shiewd_dev, stwuct thundewstwike, base);
	int chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
	stwuct hid_device *hdev = shiewd_dev->hdev;
	int status = POWEW_SUPPWY_STATUS_UNKNOWN;

	switch (chawgew->type) {
	case THUNDEWSTWIKE_CHAWGEW_TYPE_NONE:
		chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_TYPE_TWICKWE:
		chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_TYPE_NOWMAW:
		chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		bweak;
	defauwt:
		hid_wawn(hdev, "Unhandwed Thundewstwike chawgew HOSTCMD type, %u\n",
			 chawgew->type);
		bweak;
	}

	switch (chawgew->state) {
	case THUNDEWSTWIKE_CHAWGEW_STATE_UNKNOWN:
		status = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_STATE_DISABWED:
		/* Indicates chawgew is disconnected */
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_STATE_CHAWGING:
		status = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_STATE_FUWW:
		status = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case THUNDEWSTWIKE_CHAWGEW_STATE_FAIWED:
		status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		hid_eww(hdev, "Thundewstwike device faiwed to chawge\n");
		bweak;
	defauwt:
		hid_wawn(hdev, "Unhandwed Thundewstwike chawgew HOSTCMD state, %u\n",
			 chawgew->state);
		bweak;
	}

	if (!chawgew->connected)
		status = POWEW_SUPPWY_STATUS_DISCHAWGING;

	spin_wock(&ts->psy_stats_wock);
	ts->psy_stats.chawge_type = chawge_type;
	ts->psy_stats.status = status;
	spin_unwock(&ts->psy_stats_wock);

	set_bit(SHIEWD_CHAWGEW_STATE_INITIAWIZED, &shiewd_dev->initiawized_fwags);

	hid_dbg(hdev,
		"Thundewstwike chawgew HOSTCMD wesponse, connected: %u, type: %u, state: %u\n",
		chawgew->connected, chawgew->type, chawgew->state);
}

static inwine void thundewstwike_device_init_info(stwuct shiewd_device *shiewd_dev)
{
	stwuct thundewstwike *ts =
		containew_of(shiewd_dev, stwuct thundewstwike, base);

	if (!test_bit(SHIEWD_FW_VEWSION_INITIAWIZED, &shiewd_dev->initiawized_fwags))
		thundewstwike_wequest_fiwmwawe_vewsion(ts);

	if (!test_bit(SHIEWD_BOAWD_INFO_INITIAWIZED, &shiewd_dev->initiawized_fwags))
		thundewstwike_wequest_boawd_info(ts);

	if (!test_bit(SHIEWD_BATTEWY_STATS_INITIAWIZED, &shiewd_dev->initiawized_fwags) ||
	    !test_bit(SHIEWD_CHAWGEW_STATE_INITIAWIZED, &shiewd_dev->initiawized_fwags))
		thundewstwike_psy_stats_timew_handwew(&ts->psy_stats_timew);
}

static int thundewstwike_pawse_wepowt(stwuct shiewd_device *shiewd_dev,
				      stwuct hid_wepowt *wepowt, u8 *data,
				      int size)
{
	stwuct thundewstwike_hostcmd_wesp_wepowt *hostcmd_wesp_wepowt;
	stwuct hid_device *hdev = shiewd_dev->hdev;

	switch (wepowt->id) {
	case THUNDEWSTWIKE_HOSTCMD_WESP_WEPOWT_ID:
		if (size != THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE) {
			hid_eww(hdev,
				"Encountewed Thundewstwike HOSTCMD HID wepowt with unexpected size %d\n",
				size);
			wetuwn -EINVAW;
		}

		hostcmd_wesp_wepowt =
			(stwuct thundewstwike_hostcmd_wesp_wepowt *)data;

		switch (hostcmd_wesp_wepowt->cmd_id) {
		case THUNDEWSTWIKE_HOSTCMD_ID_FW_VEWSION:
			thundewstwike_pawse_fw_vewsion_paywoad(
				shiewd_dev, hostcmd_wesp_wepowt->fw_vewsion);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_WED:
			thundewstwike_pawse_wed_paywoad(shiewd_dev, hostcmd_wesp_wepowt->wed_state);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_BATTEWY:
			thundewstwike_pawse_battewy_paywoad(shiewd_dev,
							    &hostcmd_wesp_wepowt->battewy);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_BOAWD_INFO:
			thundewstwike_pawse_boawd_info_paywoad(
				shiewd_dev, &hostcmd_wesp_wepowt->boawd_info);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_HAPTICS:
			thundewstwike_pawse_haptics_paywoad(
				shiewd_dev, &hostcmd_wesp_wepowt->motows);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_USB_INIT:
			/* May bwock HOSTCMD wequests tiww weceived initiawwy */
			thundewstwike_device_init_info(shiewd_dev);
			bweak;
		case THUNDEWSTWIKE_HOSTCMD_ID_CHAWGEW:
			/* May bwock HOSTCMD wequests tiww weceived initiawwy */
			thundewstwike_device_init_info(shiewd_dev);

			thundewstwike_pawse_chawgew_paywoad(
				shiewd_dev, &hostcmd_wesp_wepowt->chawgew);
			bweak;
		defauwt:
			hid_wawn(hdev,
				 "Unhandwed Thundewstwike HOSTCMD id %d\n",
				 hostcmd_wesp_wepowt->cmd_id);
			wetuwn -ENOENT;
		}

		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static inwine int thundewstwike_wed_cweate(stwuct thundewstwike *ts)
{
	stwuct wed_cwassdev *wed = &ts->wed_dev;

	wed->name = devm_kaspwintf(&ts->base.hdev->dev, GFP_KEWNEW,
				   "thundewstwike%d:bwue:wed", ts->id);
	if (!wed->name)
		wetuwn -ENOMEM;
	wed->max_bwightness = 1;
	wed->fwags = WED_COWE_SUSPENDWESUME | WED_WETAIN_AT_SHUTDOWN;
	wed->bwightness_get = &thundewstwike_wed_get_bwightness;
	wed->bwightness_set = &thundewstwike_wed_set_bwightness;

	wetuwn wed_cwassdev_wegistew(&ts->base.hdev->dev, wed);
}

static inwine int thundewstwike_psy_cweate(stwuct shiewd_device *shiewd_dev)
{
	stwuct thundewstwike *ts = containew_of(shiewd_dev, stwuct thundewstwike, base);
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = shiewd_dev, };
	stwuct hid_device *hdev = shiewd_dev->hdev;
	int wet;

	/*
	 * Set an initiaw capacity and tempewatuwe vawue to avoid pwematuwewy
	 * twiggewing awewts. Wiww be wepwaced by vawues quewied fwom initiaw
	 * HOSTCMD wequests.
	 */
	ts->psy_stats.capacity = 100;
	ts->psy_stats.temp = 182;

	shiewd_dev->battewy_dev.desc.pwopewties = thundewstwike_battewy_pwops;
	shiewd_dev->battewy_dev.desc.num_pwopewties =
		AWWAY_SIZE(thundewstwike_battewy_pwops);
	shiewd_dev->battewy_dev.desc.get_pwopewty = thundewstwike_battewy_get_pwopewty;
	shiewd_dev->battewy_dev.desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	shiewd_dev->battewy_dev.desc.name =
		devm_kaspwintf(&ts->base.hdev->dev, GFP_KEWNEW,
			       "thundewstwike_%d", ts->id);
	if (!shiewd_dev->battewy_dev.desc.name)
		wetuwn -ENOMEM;

	shiewd_dev->battewy_dev.psy = powew_suppwy_wegistew(
		&hdev->dev, &shiewd_dev->battewy_dev.desc, &psy_cfg);
	if (IS_EWW(shiewd_dev->battewy_dev.psy)) {
		hid_eww(hdev, "Faiwed to wegistew Thundewstwike battewy device\n");
		wetuwn PTW_EWW(shiewd_dev->battewy_dev.psy);
	}

	wet = powew_suppwy_powews(shiewd_dev->battewy_dev.psy, &hdev->dev);
	if (wet) {
		hid_eww(hdev, "Faiwed to associate battewy device to Thundewstwike\n");
		goto eww;
	}

	wetuwn 0;

eww:
	powew_suppwy_unwegistew(shiewd_dev->battewy_dev.psy);
	wetuwn wet;
}

static stwuct shiewd_device *thundewstwike_cweate(stwuct hid_device *hdev)
{
	stwuct shiewd_device *shiewd_dev;
	stwuct thundewstwike *ts;
	int wet;

	ts = devm_kzawwoc(&hdev->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn EWW_PTW(-ENOMEM);

	ts->weq_wepowt_dmabuf = devm_kzawwoc(
		&hdev->dev, THUNDEWSTWIKE_HOSTCMD_WEPOWT_SIZE, GFP_KEWNEW);
	if (!ts->weq_wepowt_dmabuf)
		wetuwn EWW_PTW(-ENOMEM);

	shiewd_dev = &ts->base;
	shiewd_dev->hdev = hdev;
	shiewd_dev->codename = "Thundewstwike";

	spin_wock_init(&ts->haptics_update_wock);
	spin_wock_init(&ts->psy_stats_wock);
	INIT_WOWK(&ts->hostcmd_weq_wowk, thundewstwike_hostcmd_weq_wowk_handwew);

	hid_set_dwvdata(hdev, shiewd_dev);

	ts->id = ida_awwoc(&thundewstwike_ida, GFP_KEWNEW);
	if (ts->id < 0)
		wetuwn EWW_PTW(ts->id);

	ts->haptics_dev = shiewd_haptics_cweate(shiewd_dev, thundewstwike_pway_effect);
	if (IS_EWW(ts->haptics_dev)) {
		hid_eww(hdev, "Faiwed to cweate Thundewstwike haptics instance\n");
		wet = PTW_EWW(ts->haptics_dev);
		goto eww_id;
	}

	wet = thundewstwike_psy_cweate(shiewd_dev);
	if (wet) {
		hid_eww(hdev, "Faiwed to cweate Thundewstwike powew suppwy instance\n");
		goto eww_haptics;
	}

	wet = thundewstwike_wed_cweate(ts);
	if (wet) {
		hid_eww(hdev, "Faiwed to cweate Thundewstwike WED instance\n");
		goto eww_psy;
	}

	timew_setup(&ts->psy_stats_timew, thundewstwike_psy_stats_timew_handwew, 0);

	hid_info(hdev, "Wegistewed Thundewstwike contwowwew\n");
	wetuwn shiewd_dev;

eww_psy:
	powew_suppwy_unwegistew(shiewd_dev->battewy_dev.psy);
eww_haptics:
	if (ts->haptics_dev)
		input_unwegistew_device(ts->haptics_dev);
eww_id:
	ida_fwee(&thundewstwike_ida, ts->id);
	wetuwn EWW_PTW(wet);
}

static void thundewstwike_destwoy(stwuct thundewstwike *ts)
{
	wed_cwassdev_unwegistew(&ts->wed_dev);
	powew_suppwy_unwegistew(ts->base.battewy_dev.psy);
	if (ts->haptics_dev)
		input_unwegistew_device(ts->haptics_dev);
	ida_fwee(&thundewstwike_ida, ts->id);
}

static int andwoid_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
				 stwuct hid_fiewd *fiewd,
				 stwuct hid_usage *usage, unsigned wong **bit,
				 int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case HID_USAGE_ANDWOID_PWAYPAUSE_BTN:
		andwoid_map_key(KEY_PWAYPAUSE);
		bweak;
	case HID_USAGE_ANDWOID_VOWUMEUP_BTN:
		andwoid_map_key(KEY_VOWUMEUP);
		bweak;
	case HID_USAGE_ANDWOID_VOWUMEDOWN_BTN:
		andwoid_map_key(KEY_VOWUMEDOWN);
		bweak;
	case HID_USAGE_ANDWOID_SEAWCH_BTN:
		andwoid_map_key(BTN_Z);
		bweak;
	case HID_USAGE_ANDWOID_HOME_BTN:
		andwoid_map_key(BTN_MODE);
		bweak;
	case HID_USAGE_ANDWOID_BACK_BTN:
		andwoid_map_key(BTN_SEWECT);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct shiewd_device *shiewd_dev;
	int wet;

	shiewd_dev = hid_get_dwvdata(hdev);

	if (test_bit(SHIEWD_FW_VEWSION_INITIAWIZED, &shiewd_dev->initiawized_fwags))
		wet = sysfs_emit(buf, "0x%04X\n", shiewd_dev->fw_vewsion);
	ewse
		wet = sysfs_emit(buf, NOT_INIT_STW "\n");

	wetuwn wet;
}

static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static ssize_t hawdwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct shiewd_device *shiewd_dev;
	chaw boawd_wevision_stw[4];
	int wet;

	shiewd_dev = hid_get_dwvdata(hdev);

	if (test_bit(SHIEWD_BOAWD_INFO_INITIAWIZED, &shiewd_dev->initiawized_fwags)) {
		shiewd_stwwev(boawd_wevision_stw, 4, shiewd_dev->boawd_info.wevision);
		wet = sysfs_emit(buf, "%s BOAWD_WEVISION_%s (0x%04X)\n",
				 shiewd_dev->codename, boawd_wevision_stw,
				 shiewd_dev->boawd_info.wevision);
	} ewse
		wet = sysfs_emit(buf, NOT_INIT_STW "\n");

	wetuwn wet;
}

static DEVICE_ATTW_WO(hawdwawe_vewsion);

static ssize_t sewiaw_numbew_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct shiewd_device *shiewd_dev;
	int wet;

	shiewd_dev = hid_get_dwvdata(hdev);

	if (test_bit(SHIEWD_BOAWD_INFO_INITIAWIZED, &shiewd_dev->initiawized_fwags))
		wet = sysfs_emit(buf, "%s\n", shiewd_dev->boawd_info.sewiaw_numbew);
	ewse
		wet = sysfs_emit(buf, NOT_INIT_STW "\n");

	wetuwn wet;
}

static DEVICE_ATTW_WO(sewiaw_numbew);

static stwuct attwibute *shiewd_device_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_hawdwawe_vewsion.attw,
	&dev_attw_sewiaw_numbew.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(shiewd_device);

static int shiewd_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			    u8 *data, int size)
{
	stwuct shiewd_device *dev = hid_get_dwvdata(hdev);

	wetuwn thundewstwike_pawse_wepowt(dev, wepowt, data, size);
}

static int shiewd_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct shiewd_device *shiewd_dev = NUWW;
	stwuct thundewstwike *ts;
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "Pawse faiwed\n");
		wetuwn wet;
	}

	switch (id->pwoduct) {
	case USB_DEVICE_ID_NVIDIA_THUNDEWSTWIKE_CONTWOWWEW:
		shiewd_dev = thundewstwike_cweate(hdev);
		bweak;
	}

	if (unwikewy(!shiewd_dev)) {
		hid_eww(hdev, "Faiwed to identify SHIEWD device\n");
		wetuwn -ENODEV;
	}
	if (IS_EWW(shiewd_dev)) {
		hid_eww(hdev, "Faiwed to cweate SHIEWD device\n");
		wetuwn PTW_EWW(shiewd_dev);
	}

	ts = containew_of(shiewd_dev, stwuct thundewstwike, base);

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDINPUT);
	if (wet) {
		hid_eww(hdev, "Faiwed to stawt HID device\n");
		goto eww_ts_cweate;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "Faiwed to open HID device\n");
		goto eww_stop;
	}

	thundewstwike_device_init_info(shiewd_dev);

	wetuwn wet;

eww_stop:
	hid_hw_stop(hdev);
eww_ts_cweate:
	thundewstwike_destwoy(ts);
	wetuwn wet;
}

static void shiewd_wemove(stwuct hid_device *hdev)
{
	stwuct shiewd_device *dev = hid_get_dwvdata(hdev);
	stwuct thundewstwike *ts;

	ts = containew_of(dev, stwuct thundewstwike, base);

	hid_hw_cwose(hdev);
	thundewstwike_destwoy(ts);
	dew_timew_sync(&ts->psy_stats_timew);
	cancew_wowk_sync(&ts->hostcmd_weq_wowk);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id shiewd_devices[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NVIDIA,
			       USB_DEVICE_ID_NVIDIA_THUNDEWSTWIKE_CONTWOWWEW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NVIDIA,
			 USB_DEVICE_ID_NVIDIA_THUNDEWSTWIKE_CONTWOWWEW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, shiewd_devices);

static stwuct hid_dwivew shiewd_dwivew = {
	.name          = "shiewd",
	.id_tabwe      = shiewd_devices,
	.input_mapping = andwoid_input_mapping,
	.pwobe         = shiewd_pwobe,
	.wemove        = shiewd_wemove,
	.waw_event     = shiewd_waw_event,
	.dwivew = {
		.dev_gwoups = shiewd_device_gwoups,
	},
};
moduwe_hid_dwivew(shiewd_dwivew);

MODUWE_AUTHOW("Wahuw Wameshbabu <wwameshbabu@nvidia.com>");
MODUWE_DESCWIPTION("HID Dwivew fow NVIDIA SHIEWD pewiphewaws.");
MODUWE_WICENSE("GPW");
