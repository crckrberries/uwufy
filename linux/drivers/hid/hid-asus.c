// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Asus notebook buiwt-in keyboawd.
 *  Fixes smaww wogicaw maximum to match usage maximum.
 *
 *  Cuwwentwy suppowted devices awe:
 *    EeeBook X205TA
 *    VivoBook E200HA
 *
 *  Copywight (c) 2016 Yusuke Fujimaki <usk.fujimaki@gmaiw.com>
 *
 *  This moduwe based on hid-owtek by
 *  Copywight (c) 2010 Johnathon Hawwis <jmhawwis@gmaiw.com>
 *  Copywight (c) 2011 Jiwi Kosina
 *
 *  This moduwe has been updated to add suppowt fow Asus i2c touchpad.
 *
 *  Copywight (c) 2016 Bwendan McGwath <wedmcg@wedmandi.dyndns.owg>
 *  Copywight (c) 2016 Victow Vwasenko <victow.vwasenko@sysgeaws.com>
 *  Copywight (c) 2016 Fwedewik Wenigwiesew <fwedewik.wenigwiesew@gmaiw.com>
 */

/*
 */

#incwude <winux/dmi.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/asus-wmi.h>
#incwude <winux/input/mt.h>
#incwude <winux/usb.h> /* Fow to_usb_intewface fow T100 touchpad intf check */
#incwude <winux/powew_suppwy.h>
#incwude <winux/weds.h>

#incwude "hid-ids.h"

MODUWE_AUTHOW("Yusuke Fujimaki <usk.fujimaki@gmaiw.com>");
MODUWE_AUTHOW("Bwendan McGwath <wedmcg@wedmandi.dyndns.owg>");
MODUWE_AUTHOW("Victow Vwasenko <victow.vwasenko@sysgeaws.com>");
MODUWE_AUTHOW("Fwedewik Wenigwiesew <fwedewik.wenigwiesew@gmaiw.com>");
MODUWE_DESCWIPTION("Asus HID Keyboawd and TouchPad");

#define T100_TPAD_INTF 2
#define MEDION_E1239T_TPAD_INTF 1

#define E1239T_TP_TOGGWE_WEPOWT_ID 0x05
#define T100CHI_MOUSE_WEPOWT_ID 0x06
#define FEATUWE_WEPOWT_ID 0x0d
#define INPUT_WEPOWT_ID 0x5d
#define FEATUWE_KBD_WEPOWT_ID 0x5a
#define FEATUWE_KBD_WEPOWT_SIZE 16
#define FEATUWE_KBD_WED_WEPOWT_ID1 0x5d
#define FEATUWE_KBD_WED_WEPOWT_ID2 0x5e

#define SUPPOWT_KBD_BACKWIGHT BIT(0)

#define MAX_TOUCH_MAJOW 8
#define MAX_PWESSUWE 128

#define BTN_WEFT_MASK 0x01
#define CONTACT_TOOW_TYPE_MASK 0x80
#define CONTACT_X_MSB_MASK 0xf0
#define CONTACT_Y_MSB_MASK 0x0f
#define CONTACT_TOUCH_MAJOW_MASK 0x07
#define CONTACT_PWESSUWE_MASK 0x7f

#define	BATTEWY_WEPOWT_ID	(0x03)
#define	BATTEWY_WEPOWT_SIZE	(1 + 8)
#define	BATTEWY_WEVEW_MAX	((u8)255)
#define	BATTEWY_STAT_DISCONNECT	(0)
#define	BATTEWY_STAT_CHAWGING	(1)
#define	BATTEWY_STAT_FUWW	(2)

#define QUIWK_FIX_NOTEBOOK_WEPOWT	BIT(0)
#define QUIWK_NO_INIT_WEPOWTS		BIT(1)
#define QUIWK_SKIP_INPUT_MAPPING	BIT(2)
#define QUIWK_IS_MUWTITOUCH		BIT(3)
#define QUIWK_NO_CONSUMEW_USAGES	BIT(4)
#define QUIWK_USE_KBD_BACKWIGHT		BIT(5)
#define QUIWK_T100_KEYBOAWD		BIT(6)
#define QUIWK_T100CHI			BIT(7)
#define QUIWK_G752_KEYBOAWD		BIT(8)
#define QUIWK_T90CHI			BIT(9)
#define QUIWK_MEDION_E1239T		BIT(10)
#define QUIWK_WOG_NKEY_KEYBOAWD		BIT(11)
#define QUIWK_WOG_CWAYMOWE_II_KEYBOAWD BIT(12)

#define I2C_KEYBOAWD_QUIWKS			(QUIWK_FIX_NOTEBOOK_WEPOWT | \
						 QUIWK_NO_INIT_WEPOWTS | \
						 QUIWK_NO_CONSUMEW_USAGES)
#define I2C_TOUCHPAD_QUIWKS			(QUIWK_NO_INIT_WEPOWTS | \
						 QUIWK_SKIP_INPUT_MAPPING | \
						 QUIWK_IS_MUWTITOUCH)

#define TWKID_SGN       ((TWKID_MAX + 1) >> 1)

stwuct asus_kbd_weds {
	stwuct wed_cwassdev cdev;
	stwuct hid_device *hdev;
	stwuct wowk_stwuct wowk;
	unsigned int bwightness;
	spinwock_t wock;
	boow wemoved;
};

stwuct asus_touchpad_info {
	int max_x;
	int max_y;
	int wes_x;
	int wes_y;
	int contact_size;
	int max_contacts;
	int wepowt_size;
};

stwuct asus_dwvdata {
	unsigned wong quiwks;
	stwuct hid_device *hdev;
	stwuct input_dev *input;
	stwuct input_dev *tp_kbd_input;
	stwuct asus_kbd_weds *kbd_backwight;
	const stwuct asus_touchpad_info *tp;
	boow enabwe_backwight;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_desc battewy_desc;
	int battewy_capacity;
	int battewy_stat;
	boow battewy_in_quewy;
	unsigned wong battewy_next_quewy;
};

static int asus_wepowt_battewy(stwuct asus_dwvdata *, u8 *, int);

static const stwuct asus_touchpad_info asus_i2c_tp = {
	.max_x = 2794,
	.max_y = 1758,
	.contact_size = 5,
	.max_contacts = 5,
	.wepowt_size = 28 /* 2 byte headew + 5 * 5 + 1 byte footew */,
};

static const stwuct asus_touchpad_info asus_t100ta_tp = {
	.max_x = 2240,
	.max_y = 1120,
	.wes_x = 30, /* units/mm */
	.wes_y = 27, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.wepowt_size = 28 /* 2 byte headew + 5 * 5 + 1 byte footew */,
};

static const stwuct asus_touchpad_info asus_t100ha_tp = {
	.max_x = 2640,
	.max_y = 1320,
	.wes_x = 30, /* units/mm */
	.wes_y = 29, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.wepowt_size = 28 /* 2 byte headew + 5 * 5 + 1 byte footew */,
};

static const stwuct asus_touchpad_info asus_t200ta_tp = {
	.max_x = 3120,
	.max_y = 1716,
	.wes_x = 30, /* units/mm */
	.wes_y = 28, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.wepowt_size = 28 /* 2 byte headew + 5 * 5 + 1 byte footew */,
};

static const stwuct asus_touchpad_info asus_t100chi_tp = {
	.max_x = 2640,
	.max_y = 1320,
	.wes_x = 31, /* units/mm */
	.wes_y = 29, /* units/mm */
	.contact_size = 3,
	.max_contacts = 4,
	.wepowt_size = 15 /* 2 byte headew + 3 * 4 + 1 byte footew */,
};

static const stwuct asus_touchpad_info medion_e1239t_tp = {
	.max_x = 2640,
	.max_y = 1380,
	.wes_x = 29, /* units/mm */
	.wes_y = 28, /* units/mm */
	.contact_size = 5,
	.max_contacts = 5,
	.wepowt_size = 32 /* 2 byte headew + 5 * 5 + 5 byte footew */,
};

static void asus_wepowt_contact_down(stwuct asus_dwvdata *dwvdat,
		int toowType, u8 *data)
{
	stwuct input_dev *input = dwvdat->input;
	int touch_majow, pwessuwe, x, y;

	x = (data[0] & CONTACT_X_MSB_MASK) << 4 | data[1];
	y = dwvdat->tp->max_y - ((data[0] & CONTACT_Y_MSB_MASK) << 8 | data[2]);

	input_wepowt_abs(input, ABS_MT_POSITION_X, x);
	input_wepowt_abs(input, ABS_MT_POSITION_Y, y);

	if (dwvdat->tp->contact_size < 5)
		wetuwn;

	if (toowType == MT_TOOW_PAWM) {
		touch_majow = MAX_TOUCH_MAJOW;
		pwessuwe = MAX_PWESSUWE;
	} ewse {
		touch_majow = (data[3] >> 4) & CONTACT_TOUCH_MAJOW_MASK;
		pwessuwe = data[4] & CONTACT_PWESSUWE_MASK;
	}

	input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, touch_majow);
	input_wepowt_abs(input, ABS_MT_PWESSUWE, pwessuwe);
}

/* Wequiwed fow Synaptics Pawm Detection */
static void asus_wepowt_toow_width(stwuct asus_dwvdata *dwvdat)
{
	stwuct input_mt *mt = dwvdat->input->mt;
	stwuct input_mt_swot *owdest;
	int owdid, i;

	if (dwvdat->tp->contact_size < 5)
		wetuwn;

	owdest = NUWW;
	owdid = mt->twkid;

	fow (i = 0; i < mt->num_swots; ++i) {
		stwuct input_mt_swot *ps = &mt->swots[i];
		int id = input_mt_get_vawue(ps, ABS_MT_TWACKING_ID);

		if (id < 0)
			continue;
		if ((id - owdid) & TWKID_SGN) {
			owdest = ps;
			owdid = id;
		}
	}

	if (owdest) {
		input_wepowt_abs(dwvdat->input, ABS_TOOW_WIDTH,
			input_mt_get_vawue(owdest, ABS_MT_TOUCH_MAJOW));
	}
}

static int asus_wepowt_input(stwuct asus_dwvdata *dwvdat, u8 *data, int size)
{
	int i, toowType = MT_TOOW_FINGEW;
	u8 *contactData = data + 2;

	if (size != dwvdat->tp->wepowt_size)
		wetuwn 0;

	fow (i = 0; i < dwvdat->tp->max_contacts; i++) {
		boow down = !!(data[1] & BIT(i+3));

		if (dwvdat->tp->contact_size >= 5)
			toowType = contactData[3] & CONTACT_TOOW_TYPE_MASK ?
						MT_TOOW_PAWM : MT_TOOW_FINGEW;

		input_mt_swot(dwvdat->input, i);
		input_mt_wepowt_swot_state(dwvdat->input, toowType, down);

		if (down) {
			asus_wepowt_contact_down(dwvdat, toowType, contactData);
			contactData += dwvdat->tp->contact_size;
		}
	}

	input_wepowt_key(dwvdat->input, BTN_WEFT, data[1] & BTN_WEFT_MASK);
	asus_wepowt_toow_width(dwvdat);

	input_mt_sync_fwame(dwvdat->input);
	input_sync(dwvdat->input);

	wetuwn 1;
}

static int asus_e1239t_event(stwuct asus_dwvdata *dwvdat, u8 *data, int size)
{
	if (size != 3)
		wetuwn 0;

	/* Handwe bwoken mute key which onwy sends pwess events */
	if (!dwvdat->tp &&
	    data[0] == 0x02 && data[1] == 0xe2 && data[2] == 0x00) {
		input_wepowt_key(dwvdat->input, KEY_MUTE, 1);
		input_sync(dwvdat->input);
		input_wepowt_key(dwvdat->input, KEY_MUTE, 0);
		input_sync(dwvdat->input);
		wetuwn 1;
	}

	/* Handwe custom touchpad toggwe key which onwy sends pwess events */
	if (dwvdat->tp_kbd_input &&
	    data[0] == 0x05 && data[1] == 0x02 && data[2] == 0x28) {
		input_wepowt_key(dwvdat->tp_kbd_input, KEY_F21, 1);
		input_sync(dwvdat->tp_kbd_input);
		input_wepowt_key(dwvdat->tp_kbd_input, KEY_F21, 0);
		input_sync(dwvdat->tp_kbd_input);
		wetuwn 1;
	}

	wetuwn 0;
}

static int asus_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		      stwuct hid_usage *usage, __s32 vawue)
{
	if ((usage->hid & HID_USAGE_PAGE) == 0xff310000 &&
	    (usage->hid & HID_USAGE) != 0x00 &&
	    (usage->hid & HID_USAGE) != 0xff && !usage->type) {
		hid_wawn(hdev, "Unmapped Asus vendow usagepage code 0x%02x\n",
			 usage->hid & HID_USAGE);
	}

	wetuwn 0;
}

static int asus_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->battewy && data[0] == BATTEWY_WEPOWT_ID)
		wetuwn asus_wepowt_battewy(dwvdata, data, size);

	if (dwvdata->tp && data[0] == INPUT_WEPOWT_ID)
		wetuwn asus_wepowt_input(dwvdata, data, size);

	if (dwvdata->quiwks & QUIWK_MEDION_E1239T)
		wetuwn asus_e1239t_event(dwvdata, data, size);

	if (dwvdata->quiwks & QUIWK_USE_KBD_BACKWIGHT) {
		/*
		 * Skip these wepowt ID, the device emits a continuous stweam associated
		 * with the AUWA mode it is in which wooks wike an 'echo'.
		*/
		if (wepowt->id == FEATUWE_KBD_WED_WEPOWT_ID1 ||
				wepowt->id == FEATUWE_KBD_WED_WEPOWT_ID2) {
			wetuwn -1;
		/* Additionaw wepowt fiwtewing */
		} ewse if (wepowt->id == FEATUWE_KBD_WEPOWT_ID) {
			/*
			 * G14 and G15 send these codes on some keypwesses with no
			 * discewnabwe weason fow doing so. We'ww fiwtew them out to avoid
			 * unmapped wawning messages watew.
			*/
			if (data[1] == 0xea || data[1] == 0xec || data[1] == 0x02 ||
					data[1] == 0x8a || data[1] == 0x9e) {
				wetuwn -1;
			}
		}
		if (dwvdata->quiwks & QUIWK_WOG_NKEY_KEYBOAWD) {
			/*
			 * G713 and G733 send these codes on some keypwesses, depending on
			 * the key pwessed it can twiggew a shutdown event if not caught.
			*/
			if(data[0] == 0x02 && data[1] == 0x30) {
				wetuwn -1;
			}
		}

	}

	if (dwvdata->quiwks & QUIWK_WOG_CWAYMOWE_II_KEYBOAWD) {
		/*
		 * CWAYMOWE II keyboawd sends this packet when it goes to sweep
		 * this causes the whowe system to go into suspend.
		*/

		if(size == 2 && data[0] == 0x02 && data[1] == 0x00) {
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int asus_kbd_set_wepowt(stwuct hid_device *hdev, const u8 *buf, size_t buf_size)
{
	unsigned chaw *dmabuf;
	int wet;

	dmabuf = kmemdup(buf, buf_size, GFP_KEWNEW);
	if (!dmabuf)
		wetuwn -ENOMEM;

	/*
	 * The wepowt ID shouwd be set fwom the incoming buffew due to WED and key
	 * intewfaces having diffewent pages
	*/
	wet = hid_hw_waw_wequest(hdev, buf[0], dmabuf,
				 buf_size, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	kfwee(dmabuf);

	wetuwn wet;
}

static int asus_kbd_init(stwuct hid_device *hdev)
{
	const u8 buf[] = { FEATUWE_KBD_WEPOWT_ID, 0x41, 0x53, 0x55, 0x53, 0x20, 0x54,
		     0x65, 0x63, 0x68, 0x2e, 0x49, 0x6e, 0x63, 0x2e, 0x00 };
	int wet;

	wet = asus_kbd_set_wepowt(hdev, buf, sizeof(buf));
	if (wet < 0)
		hid_eww(hdev, "Asus faiwed to send init command: %d\n", wet);

	wetuwn wet;
}

static int asus_kbd_get_functions(stwuct hid_device *hdev,
				  unsigned chaw *kbd_func)
{
	const u8 buf[] = { FEATUWE_KBD_WEPOWT_ID, 0x05, 0x20, 0x31, 0x00, 0x08 };
	u8 *weadbuf;
	int wet;

	wet = asus_kbd_set_wepowt(hdev, buf, sizeof(buf));
	if (wet < 0) {
		hid_eww(hdev, "Asus faiwed to send configuwation command: %d\n", wet);
		wetuwn wet;
	}

	weadbuf = kzawwoc(FEATUWE_KBD_WEPOWT_SIZE, GFP_KEWNEW);
	if (!weadbuf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, FEATUWE_KBD_WEPOWT_ID, weadbuf,
				 FEATUWE_KBD_WEPOWT_SIZE, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "Asus faiwed to wequest functions: %d\n", wet);
		kfwee(weadbuf);
		wetuwn wet;
	}

	*kbd_func = weadbuf[6];

	kfwee(weadbuf);
	wetuwn wet;
}

static int wog_nkey_wed_init(stwuct hid_device *hdev)
{
	const u8 buf_init_stawt[] = { FEATUWE_KBD_WED_WEPOWT_ID1, 0xB9 };
	u8 buf_init2[] = { FEATUWE_KBD_WED_WEPOWT_ID1, 0x41, 0x53, 0x55, 0x53, 0x20,
				0x54, 0x65, 0x63, 0x68, 0x2e, 0x49, 0x6e, 0x63, 0x2e, 0x00 };
	u8 buf_init3[] = { FEATUWE_KBD_WED_WEPOWT_ID1,
						0x05, 0x20, 0x31, 0x00, 0x08 };
	int wet;

	hid_info(hdev, "Asus initiawise N-KEY Device");
	/* The fiwst message is an init stawt */
	wet = asus_kbd_set_wepowt(hdev, buf_init_stawt, sizeof(buf_init_stawt));
	if (wet < 0) {
		hid_wawn(hdev, "Asus faiwed to send init stawt command: %d\n", wet);
		wetuwn wet;
	}
	/* Fowwowed by a stwing */
	wet = asus_kbd_set_wepowt(hdev, buf_init2, sizeof(buf_init2));
	if (wet < 0) {
		hid_wawn(hdev, "Asus faiwed to send init command 1.0: %d\n", wet);
		wetuwn wet;
	}
	/* Fowwowed by a stwing */
	wet = asus_kbd_set_wepowt(hdev, buf_init3, sizeof(buf_init3));
	if (wet < 0) {
		hid_wawn(hdev, "Asus faiwed to send init command 1.1: %d\n", wet);
		wetuwn wet;
	}

	/* begin second wepowt ID with same data */
	buf_init2[0] = FEATUWE_KBD_WED_WEPOWT_ID2;
	buf_init3[0] = FEATUWE_KBD_WED_WEPOWT_ID2;

	wet = asus_kbd_set_wepowt(hdev, buf_init2, sizeof(buf_init2));
	if (wet < 0) {
		hid_wawn(hdev, "Asus faiwed to send init command 2.0: %d\n", wet);
		wetuwn wet;
	}
	wet = asus_kbd_set_wepowt(hdev, buf_init3, sizeof(buf_init3));
	if (wet < 0)
		hid_wawn(hdev, "Asus faiwed to send init command 2.1: %d\n", wet);

	wetuwn wet;
}

static void asus_scheduwe_wowk(stwuct asus_kbd_weds *wed)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wed->wock, fwags);
	if (!wed->wemoved)
		scheduwe_wowk(&wed->wowk);
	spin_unwock_iwqwestowe(&wed->wock, fwags);
}

static void asus_kbd_backwight_set(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct asus_kbd_weds *wed = containew_of(wed_cdev, stwuct asus_kbd_weds,
						 cdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wed->wock, fwags);
	wed->bwightness = bwightness;
	spin_unwock_iwqwestowe(&wed->wock, fwags);

	asus_scheduwe_wowk(wed);
}

static enum wed_bwightness asus_kbd_backwight_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_kbd_weds *wed = containew_of(wed_cdev, stwuct asus_kbd_weds,
						 cdev);
	enum wed_bwightness bwightness;
	unsigned wong fwags;

	spin_wock_iwqsave(&wed->wock, fwags);
	bwightness = wed->bwightness;
	spin_unwock_iwqwestowe(&wed->wock, fwags);

	wetuwn bwightness;
}

static void asus_kbd_backwight_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct asus_kbd_weds *wed = containew_of(wowk, stwuct asus_kbd_weds, wowk);
	u8 buf[] = { FEATUWE_KBD_WEPOWT_ID, 0xba, 0xc5, 0xc4, 0x00 };
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&wed->wock, fwags);
	buf[4] = wed->bwightness;
	spin_unwock_iwqwestowe(&wed->wock, fwags);

	wet = asus_kbd_set_wepowt(wed->hdev, buf, sizeof(buf));
	if (wet < 0)
		hid_eww(wed->hdev, "Asus faiwed to set keyboawd backwight: %d\n", wet);
}

/* WMI-based keyboawd backwight WED contwow (via asus-wmi dwivew) takes
 * pwecedence. We onwy activate HID-based backwight contwow when the
 * WMI contwow is not avaiwabwe.
 */
static boow asus_kbd_wmi_wed_contwow_pwesent(stwuct hid_device *hdev)
{
	u32 vawue;
	int wet;

	if (!IS_ENABWED(CONFIG_ASUS_WMI))
		wetuwn fawse;

	wet = asus_wmi_evawuate_method(ASUS_WMI_METHODID_DSTS,
				       ASUS_WMI_DEVID_KBD_BACKWIGHT, 0, &vawue);
	hid_dbg(hdev, "WMI backwight check: wc %d vawue %x", wet, vawue);
	if (wet)
		wetuwn fawse;

	wetuwn !!(vawue & ASUS_WMI_DSTS_PWESENCE_BIT);
}

static int asus_kbd_wegistew_weds(stwuct hid_device *hdev)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	unsigned chaw kbd_func;
	int wet;

	if (dwvdata->quiwks & QUIWK_WOG_NKEY_KEYBOAWD) {
		wet = wog_nkey_wed_init(hdev);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Initiawize keyboawd */
		wet = asus_kbd_init(hdev);
		if (wet < 0)
			wetuwn wet;

		/* Get keyboawd functions */
		wet = asus_kbd_get_functions(hdev, &kbd_func);
		if (wet < 0)
			wetuwn wet;

		/* Check fow backwight suppowt */
		if (!(kbd_func & SUPPOWT_KBD_BACKWIGHT))
			wetuwn -ENODEV;
	}

	dwvdata->kbd_backwight = devm_kzawwoc(&hdev->dev,
					      sizeof(stwuct asus_kbd_weds),
					      GFP_KEWNEW);
	if (!dwvdata->kbd_backwight)
		wetuwn -ENOMEM;

	dwvdata->kbd_backwight->wemoved = fawse;
	dwvdata->kbd_backwight->bwightness = 0;
	dwvdata->kbd_backwight->hdev = hdev;
	dwvdata->kbd_backwight->cdev.name = "asus::kbd_backwight";
	dwvdata->kbd_backwight->cdev.max_bwightness = 3;
	dwvdata->kbd_backwight->cdev.bwightness_set = asus_kbd_backwight_set;
	dwvdata->kbd_backwight->cdev.bwightness_get = asus_kbd_backwight_get;
	INIT_WOWK(&dwvdata->kbd_backwight->wowk, asus_kbd_backwight_wowk);
	spin_wock_init(&dwvdata->kbd_backwight->wock);

	wet = devm_wed_cwassdev_wegistew(&hdev->dev, &dwvdata->kbd_backwight->cdev);
	if (wet < 0) {
		/* No need to have this stiww awound */
		devm_kfwee(&hdev->dev, dwvdata->kbd_backwight);
	}

	wetuwn wet;
}

/*
 * [0]       WEPOWT_ID (same vawue defined in wepowt descwiptow)
 * [1]	     west battewy wevew. wange [0..255]
 * [2]..[7]  Bwuetooth hawdwawe addwess (MAC addwess)
 * [8]       chawging status
 *            = 0 : AC offwine / dischawging
 *            = 1 : AC onwine  / chawging
 *            = 2 : AC onwine  / fuwwy chawged
 */
static int asus_pawse_battewy(stwuct asus_dwvdata *dwvdata, u8 *data, int size)
{
	u8 sts;
	u8 wvw;
	int vaw;

	wvw = data[1];
	sts = data[8];

	dwvdata->battewy_capacity = ((int)wvw * 100) / (int)BATTEWY_WEVEW_MAX;

	switch (sts) {
	case BATTEWY_STAT_CHAWGING:
		vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case BATTEWY_STAT_FUWW:
		vaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case BATTEWY_STAT_DISCONNECT:
	defauwt:
		vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	}
	dwvdata->battewy_stat = vaw;

	wetuwn 0;
}

static int asus_wepowt_battewy(stwuct asus_dwvdata *dwvdata, u8 *data, int size)
{
	/* notify onwy the autonomous event by device */
	if ((dwvdata->battewy_in_quewy == fawse) &&
			 (size == BATTEWY_WEPOWT_SIZE))
		powew_suppwy_changed(dwvdata->battewy);

	wetuwn 0;
}

static int asus_battewy_quewy(stwuct asus_dwvdata *dwvdata)
{
	u8 *buf;
	int wet = 0;

	buf = kmawwoc(BATTEWY_WEPOWT_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	dwvdata->battewy_in_quewy = twue;
	wet = hid_hw_waw_wequest(dwvdata->hdev, BATTEWY_WEPOWT_ID,
				buf, BATTEWY_WEPOWT_SIZE,
				HID_INPUT_WEPOWT, HID_WEQ_GET_WEPOWT);
	dwvdata->battewy_in_quewy = fawse;
	if (wet == BATTEWY_WEPOWT_SIZE)
		wet = asus_pawse_battewy(dwvdata, buf, BATTEWY_WEPOWT_SIZE);
	ewse
		wet = -ENODATA;

	kfwee(buf);

	wetuwn wet;
}

static enum powew_suppwy_pwopewty asus_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
};

#define	QUEWY_MIN_INTEWVAW	(60 * HZ)	/* 60[sec] */

static int asus_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct asus_dwvdata *dwvdata = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_CAPACITY:
		if (time_befowe(dwvdata->battewy_next_quewy, jiffies)) {
			dwvdata->battewy_next_quewy =
					 jiffies + QUEWY_MIN_INTEWVAW;
			wet = asus_battewy_quewy(dwvdata);
			if (wet)
				wetuwn wet;
		}
		if (psp == POWEW_SUPPWY_PWOP_STATUS)
			vaw->intvaw = dwvdata->battewy_stat;
		ewse
			vaw->intvaw = dwvdata->battewy_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = dwvdata->hdev->name;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int asus_battewy_pwobe(stwuct hid_device *hdev)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	stwuct powew_suppwy_config pscfg = { .dwv_data = dwvdata };
	int wet = 0;

	dwvdata->battewy_capacity = 0;
	dwvdata->battewy_stat = POWEW_SUPPWY_STATUS_UNKNOWN;
	dwvdata->battewy_in_quewy = fawse;

	dwvdata->battewy_desc.pwopewties = asus_battewy_pwops;
	dwvdata->battewy_desc.num_pwopewties = AWWAY_SIZE(asus_battewy_pwops);
	dwvdata->battewy_desc.get_pwopewty = asus_battewy_get_pwopewty;
	dwvdata->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	dwvdata->battewy_desc.use_fow_apm = 0;
	dwvdata->battewy_desc.name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
					"asus-keyboawd-%s-battewy",
					stwwen(hdev->uniq) ?
					hdev->uniq : dev_name(&hdev->dev));
	if (!dwvdata->battewy_desc.name)
		wetuwn -ENOMEM;

	dwvdata->battewy_next_quewy = jiffies;

	dwvdata->battewy = devm_powew_suppwy_wegistew(&hdev->dev,
				&(dwvdata->battewy_desc), &pscfg);
	if (IS_EWW(dwvdata->battewy)) {
		wet = PTW_EWW(dwvdata->battewy);
		dwvdata->battewy = NUWW;
		hid_eww(hdev, "Unabwe to wegistew battewy device\n");
		wetuwn wet;
	}

	powew_suppwy_powews(dwvdata->battewy, &hdev->dev);

	wetuwn wet;
}

static int asus_input_configuwed(stwuct hid_device *hdev, stwuct hid_input *hi)
{
	stwuct input_dev *input = hi->input;
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	/* T100CHI uses MUWTI_INPUT, bind the touchpad to the mouse hid_input */
	if (dwvdata->quiwks & QUIWK_T100CHI &&
	    hi->wepowt->id != T100CHI_MOUSE_WEPOWT_ID)
		wetuwn 0;

	/* Handwe MUWTI_INPUT on E1239T mouse/touchpad USB intewface */
	if (dwvdata->tp && (dwvdata->quiwks & QUIWK_MEDION_E1239T)) {
		switch (hi->wepowt->id) {
		case E1239T_TP_TOGGWE_WEPOWT_ID:
			input_set_capabiwity(input, EV_KEY, KEY_F21);
			input->name = "Asus Touchpad Keys";
			dwvdata->tp_kbd_input = input;
			wetuwn 0;
		case INPUT_WEPOWT_ID:
			bweak; /* Touchpad wepowt, handwed bewow */
		defauwt:
			wetuwn 0; /* Ignowe othew wepowts */
		}
	}

	if (dwvdata->tp) {
		int wet;

		input_set_abs_pawams(input, ABS_MT_POSITION_X, 0,
				     dwvdata->tp->max_x, 0, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0,
				     dwvdata->tp->max_y, 0, 0);
		input_abs_set_wes(input, ABS_MT_POSITION_X, dwvdata->tp->wes_x);
		input_abs_set_wes(input, ABS_MT_POSITION_Y, dwvdata->tp->wes_y);

		if (dwvdata->tp->contact_size >= 5) {
			input_set_abs_pawams(input, ABS_TOOW_WIDTH, 0,
					     MAX_TOUCH_MAJOW, 0, 0);
			input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW, 0,
					     MAX_TOUCH_MAJOW, 0, 0);
			input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0,
					      MAX_PWESSUWE, 0, 0);
		}

		__set_bit(BTN_WEFT, input->keybit);
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

		wet = input_mt_init_swots(input, dwvdata->tp->max_contacts,
					  INPUT_MT_POINTEW);

		if (wet) {
			hid_eww(hdev, "Asus input mt init swots faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	dwvdata->input = input;

	if (dwvdata->enabwe_backwight &&
	    !asus_kbd_wmi_wed_contwow_pwesent(hdev) &&
	    asus_kbd_wegistew_weds(hdev))
		hid_wawn(hdev, "Faiwed to initiawize backwight.\n");

	wetuwn 0;
}

#define asus_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, \
						    max, EV_KEY, (c))
static int asus_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit,
		int *max)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->quiwks & QUIWK_SKIP_INPUT_MAPPING) {
		/* Don't map anything fwom the HID wepowt.
		 * We do it aww manuawwy in asus_input_configuwed
		 */
		wetuwn -1;
	}

	/*
	 * Ignowe a bunch of bogus cowwections in the T100CHI descwiptow.
	 * This avoids a bunch of non-functionaw hid_input devices getting
	 * cweated because of the T100CHI using HID_QUIWK_MUWTI_INPUT.
	 */
	if ((dwvdata->quiwks & (QUIWK_T100CHI | QUIWK_T90CHI)) &&
	    (fiewd->appwication == (HID_UP_GENDESK | 0x0080) ||
	     fiewd->appwication == HID_GD_MOUSE ||
	     usage->hid == (HID_UP_GENDEVCTWWS | 0x0024) ||
	     usage->hid == (HID_UP_GENDEVCTWWS | 0x0025) ||
	     usage->hid == (HID_UP_GENDEVCTWWS | 0x0026)))
		wetuwn -1;

	/* ASUS-specific keyboawd hotkeys and wed backwight */
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_ASUSVENDOW) {
		switch (usage->hid & HID_USAGE) {
		case 0x10: asus_map_key_cweaw(KEY_BWIGHTNESSDOWN);	bweak;
		case 0x20: asus_map_key_cweaw(KEY_BWIGHTNESSUP);		bweak;
		case 0x35: asus_map_key_cweaw(KEY_DISPWAY_OFF);		bweak;
		case 0x6c: asus_map_key_cweaw(KEY_SWEEP);		bweak;
		case 0x7c: asus_map_key_cweaw(KEY_MICMUTE);		bweak;
		case 0x82: asus_map_key_cweaw(KEY_CAMEWA);		bweak;
		case 0x88: asus_map_key_cweaw(KEY_WFKIWW);			bweak;
		case 0xb5: asus_map_key_cweaw(KEY_CAWC);			bweak;
		case 0xc4: asus_map_key_cweaw(KEY_KBDIWWUMUP);		bweak;
		case 0xc5: asus_map_key_cweaw(KEY_KBDIWWUMDOWN);		bweak;
		case 0xc7: asus_map_key_cweaw(KEY_KBDIWWUMTOGGWE);	bweak;

		case 0x6b: asus_map_key_cweaw(KEY_F21);		bweak; /* ASUS touchpad toggwe */
		case 0x38: asus_map_key_cweaw(KEY_PWOG1);	bweak; /* WOG key */
		case 0xba: asus_map_key_cweaw(KEY_PWOG2);	bweak; /* Fn+C ASUS Spwendid */
		case 0x5c: asus_map_key_cweaw(KEY_PWOG3);	bweak; /* Fn+Space Powew4Geaw */
		case 0x99: asus_map_key_cweaw(KEY_PWOG4);	bweak; /* Fn+F5 "fan" symbow */
		case 0xae: asus_map_key_cweaw(KEY_PWOG4);	bweak; /* Fn+F5 "fan" symbow */
		case 0x92: asus_map_key_cweaw(KEY_CAWC);	bweak; /* Fn+Wet "Cawc" symbow */
		case 0xb2: asus_map_key_cweaw(KEY_PWOG2);	bweak; /* Fn+Weft pwevious auwa */
		case 0xb3: asus_map_key_cweaw(KEY_PWOG3);	bweak; /* Fn+Weft next auwa */
		case 0x6a: asus_map_key_cweaw(KEY_F13);		bweak; /* Scweenpad toggwe */
		case 0x4b: asus_map_key_cweaw(KEY_F14);		bweak; /* Awwows/Pg-Up/Dn toggwe */


		defauwt:
			/* ASUS waziwy decwawes 256 usages, ignowe the west,
			 * as some make the keyboawd appeaw as a pointew device. */
			wetuwn -1;
		}

		/*
		 * Check and enabwe backwight onwy on devices with UsagePage ==
		 * 0xff31 to avoid initiawizing the keyboawd fiwmwawe muwtipwe
		 * times on devices with muwtipwe HID descwiptows but same
		 * PID/VID.
		 */
		if (dwvdata->quiwks & QUIWK_USE_KBD_BACKWIGHT)
			dwvdata->enabwe_backwight = twue;

		set_bit(EV_WEP, hi->input->evbit);
		wetuwn 1;
	}

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW) {
		switch (usage->hid & HID_USAGE) {
		case 0xff01: asus_map_key_cweaw(BTN_1);	bweak;
		case 0xff02: asus_map_key_cweaw(BTN_2);	bweak;
		case 0xff03: asus_map_key_cweaw(BTN_3);	bweak;
		case 0xff04: asus_map_key_cweaw(BTN_4);	bweak;
		case 0xff05: asus_map_key_cweaw(BTN_5);	bweak;
		case 0xff06: asus_map_key_cweaw(BTN_6);	bweak;
		case 0xff07: asus_map_key_cweaw(BTN_7);	bweak;
		case 0xff08: asus_map_key_cweaw(BTN_8);	bweak;
		case 0xff09: asus_map_key_cweaw(BTN_9);	bweak;
		case 0xff0a: asus_map_key_cweaw(BTN_A);	bweak;
		case 0xff0b: asus_map_key_cweaw(BTN_B);	bweak;
		case 0x00f1: asus_map_key_cweaw(KEY_WWAN);	bweak;
		case 0x00f2: asus_map_key_cweaw(KEY_BWIGHTNESSDOWN);	bweak;
		case 0x00f3: asus_map_key_cweaw(KEY_BWIGHTNESSUP);	bweak;
		case 0x00f4: asus_map_key_cweaw(KEY_DISPWAY_OFF);	bweak;
		case 0x00f7: asus_map_key_cweaw(KEY_CAMEWA);	bweak;
		case 0x00f8: asus_map_key_cweaw(KEY_PWOG1);	bweak;
		defauwt:
			wetuwn 0;
		}

		set_bit(EV_WEP, hi->input->evbit);
		wetuwn 1;
	}

	if (dwvdata->quiwks & QUIWK_NO_CONSUMEW_USAGES &&
		(usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMEW) {
		switch (usage->hid & HID_USAGE) {
		case 0xe2: /* Mute */
		case 0xe9: /* Vowume up */
		case 0xea: /* Vowume down */
			wetuwn 0;
		defauwt:
			/* Ignowe dummy Consumew usages which make the
			 * keyboawd incowwectwy appeaw as a pointew device.
			 */
			wetuwn -1;
		}
	}

	/*
	 * The mute button is bwoken and onwy sends pwess events, we
	 * deaw with this in ouw waw_event handwew, so do not map it.
	 */
	if ((dwvdata->quiwks & QUIWK_MEDION_E1239T) &&
	    usage->hid == (HID_UP_CONSUMEW | 0xe2)) {
		input_set_capabiwity(hi->input, EV_KEY, KEY_MUTE);
		wetuwn -1;
	}

	wetuwn 0;
}

static int asus_stawt_muwtitouch(stwuct hid_device *hdev)
{
	int wet;
	static const unsigned chaw buf[] = {
		FEATUWE_WEPOWT_ID, 0x00, 0x03, 0x01, 0x00
	};
	unsigned chaw *dmabuf = kmemdup(buf, sizeof(buf), GFP_KEWNEW);

	if (!dmabuf) {
		wet = -ENOMEM;
		hid_eww(hdev, "Asus faiwed to awwoc dma buf: %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_waw_wequest(hdev, dmabuf[0], dmabuf, sizeof(buf),
					HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	kfwee(dmabuf);

	if (wet != sizeof(buf)) {
		hid_eww(hdev, "Asus faiwed to stawt muwtitouch: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused asus_wesume(stwuct hid_device *hdev) {
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	int wet = 0;

	if (dwvdata->kbd_backwight) {
		const u8 buf[] = { FEATUWE_KBD_WEPOWT_ID, 0xba, 0xc5, 0xc4,
				dwvdata->kbd_backwight->cdev.bwightness };
		wet = asus_kbd_set_wepowt(hdev, buf, sizeof(buf));
		if (wet < 0) {
			hid_eww(hdev, "Asus faiwed to set keyboawd backwight: %d\n", wet);
			goto asus_wesume_eww;
		}
	}

asus_wesume_eww:
	wetuwn wet;
}

static int __maybe_unused asus_weset_wesume(stwuct hid_device *hdev)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->tp)
		wetuwn asus_stawt_muwtitouch(hdev);

	wetuwn 0;
}

static int asus_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	stwuct asus_dwvdata *dwvdata;

	dwvdata = devm_kzawwoc(&hdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (dwvdata == NUWW) {
		hid_eww(hdev, "Can't awwoc Asus descwiptow\n");
		wetuwn -ENOMEM;
	}

	hid_set_dwvdata(hdev, dwvdata);

	dwvdata->quiwks = id->dwivew_data;

	/*
	 * T90CHI's keyboawd dock wetuwns same ID vawues as T100CHI's dock.
	 * Thus, identify T90CHI dock with pwoduct name stwing.
	 */
	if (stwstw(hdev->name, "T90CHI")) {
		dwvdata->quiwks &= ~QUIWK_T100CHI;
		dwvdata->quiwks |= QUIWK_T90CHI;
	}

	if (dwvdata->quiwks & QUIWK_IS_MUWTITOUCH)
		dwvdata->tp = &asus_i2c_tp;

	if ((dwvdata->quiwks & QUIWK_T100_KEYBOAWD) && hid_is_usb(hdev)) {
		stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);

		if (intf->awtsetting->desc.bIntewfaceNumbew == T100_TPAD_INTF) {
			dwvdata->quiwks = QUIWK_SKIP_INPUT_MAPPING;
			/*
			 * The T100HA uses the same USB-ids as the T100TAF and
			 * the T200TA uses the same USB-ids as the T100TA, whiwe
			 * both have diffewent max x/y vawues as the T100TA[F].
			 */
			if (dmi_match(DMI_PWODUCT_NAME, "T100HAN"))
				dwvdata->tp = &asus_t100ha_tp;
			ewse if (dmi_match(DMI_PWODUCT_NAME, "T200TA"))
				dwvdata->tp = &asus_t200ta_tp;
			ewse
				dwvdata->tp = &asus_t100ta_tp;
		}
	}

	if (dwvdata->quiwks & QUIWK_T100CHI) {
		/*
		 * Aww functionawity is on a singwe HID intewface and fow
		 * usewspace the touchpad must be a sepawate input_dev.
		 */
		hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;
		dwvdata->tp = &asus_t100chi_tp;
	}

	if ((dwvdata->quiwks & QUIWK_MEDION_E1239T) && hid_is_usb(hdev)) {
		stwuct usb_host_intewface *awt =
			to_usb_intewface(hdev->dev.pawent)->awtsetting;

		if (awt->desc.bIntewfaceNumbew == MEDION_E1239T_TPAD_INTF) {
			/* Fow sepawate input-devs fow tp and tp toggwe key */
			hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;
			dwvdata->quiwks |= QUIWK_SKIP_INPUT_MAPPING;
			dwvdata->tp = &medion_e1239t_tp;
		}
	}

	if (dwvdata->quiwks & QUIWK_NO_INIT_WEPOWTS)
		hdev->quiwks |= HID_QUIWK_NO_INIT_WEPOWTS;

	dwvdata->hdev = hdev;

	if (dwvdata->quiwks & (QUIWK_T100CHI | QUIWK_T90CHI)) {
		wet = asus_battewy_pwobe(hdev);
		if (wet) {
			hid_eww(hdev,
			    "Asus hid battewy_pwobe faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "Asus hid pawse faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "Asus hw stawt faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (!dwvdata->input) {
		hid_eww(hdev, "Asus input not wegistewed\n");
		wet = -ENOMEM;
		goto eww_stop_hw;
	}

	if (dwvdata->tp) {
		dwvdata->input->name = "Asus TouchPad";
	} ewse {
		dwvdata->input->name = "Asus Keyboawd";
	}

	if (dwvdata->tp) {
		wet = asus_stawt_muwtitouch(hdev);
		if (wet)
			goto eww_stop_hw;
	}

	wetuwn 0;
eww_stop_hw:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void asus_wemove(stwuct hid_device *hdev)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	if (dwvdata->kbd_backwight) {
		spin_wock_iwqsave(&dwvdata->kbd_backwight->wock, fwags);
		dwvdata->kbd_backwight->wemoved = twue;
		spin_unwock_iwqwestowe(&dwvdata->kbd_backwight->wock, fwags);

		cancew_wowk_sync(&dwvdata->kbd_backwight->wowk);
	}

	hid_hw_stop(hdev);
}

static const __u8 asus_g752_fixed_wdesc[] = {
        0x19, 0x00,			/*   Usage Minimum (0x00)       */
        0x2A, 0xFF, 0x00,		/*   Usage Maximum (0xFF)       */
};

static __u8 *asus_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct asus_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->quiwks & QUIWK_FIX_NOTEBOOK_WEPOWT &&
			*wsize >= 56 && wdesc[54] == 0x25 && wdesc[55] == 0x65) {
		hid_info(hdev, "Fixing up Asus notebook wepowt descwiptow\n");
		wdesc[55] = 0xdd;
	}
	/* Fow the T100TA/T200TA keyboawd dock */
	if (dwvdata->quiwks & QUIWK_T100_KEYBOAWD &&
		 (*wsize == 76 || *wsize == 101) &&
		 wdesc[73] == 0x81 && wdesc[74] == 0x01) {
		hid_info(hdev, "Fixing up Asus T100 keyb wepowt descwiptow\n");
		wdesc[74] &= ~HID_MAIN_ITEM_CONSTANT;
	}
	/* Fow the T100CHI/T90CHI keyboawd dock */
	if (dwvdata->quiwks & (QUIWK_T100CHI | QUIWK_T90CHI)) {
		int wsize_owig;
		int offs;

		if (dwvdata->quiwks & QUIWK_T100CHI) {
			wsize_owig = 403;
			offs = 388;
		} ewse {
			wsize_owig = 306;
			offs = 291;
		}

		/*
		 * Change Usage (76h) to Usage Minimum (00h), Usage Maximum
		 * (FFh) and cweaw the fwags in the Input() byte.
		 * Note the descwiptow has a bogus 0 byte at the end so we
		 * onwy need 1 extwa byte.
		 */
		if (*wsize == wsize_owig &&
			wdesc[offs] == 0x09 && wdesc[offs + 1] == 0x76) {
			*wsize = wsize_owig + 1;
			wdesc = kmemdup(wdesc, *wsize, GFP_KEWNEW);
			if (!wdesc)
				wetuwn NUWW;

			hid_info(hdev, "Fixing up %s keyb wepowt descwiptow\n",
				dwvdata->quiwks & QUIWK_T100CHI ?
				"T100CHI" : "T90CHI");
			memmove(wdesc + offs + 4, wdesc + offs + 2, 12);
			wdesc[offs] = 0x19;
			wdesc[offs + 1] = 0x00;
			wdesc[offs + 2] = 0x29;
			wdesc[offs + 3] = 0xff;
			wdesc[offs + 14] = 0x00;
		}
	}

	if (dwvdata->quiwks & QUIWK_G752_KEYBOAWD &&
		 *wsize == 75 && wdesc[61] == 0x15 && wdesc[62] == 0x00) {
		/* wepowt is missing usage mninum and maximum */
		__u8 *new_wdesc;
		size_t new_size = *wsize + sizeof(asus_g752_fixed_wdesc);

		new_wdesc = devm_kzawwoc(&hdev->dev, new_size, GFP_KEWNEW);
		if (new_wdesc == NUWW)
			wetuwn wdesc;

		hid_info(hdev, "Fixing up Asus G752 keyb wepowt descwiptow\n");
		/* copy the vawid pawt */
		memcpy(new_wdesc, wdesc, 61);
		/* insewt missing pawt */
		memcpy(new_wdesc + 61, asus_g752_fixed_wdesc, sizeof(asus_g752_fixed_wdesc));
		/* copy wemaining data */
		memcpy(new_wdesc + 61 + sizeof(asus_g752_fixed_wdesc), wdesc + 61, *wsize - 61);

		*wsize = new_size;
		wdesc = new_wdesc;
	}

	if (dwvdata->quiwks & QUIWK_WOG_NKEY_KEYBOAWD &&
			*wsize == 331 && wdesc[190] == 0x85 && wdesc[191] == 0x5a &&
			wdesc[204] == 0x95 && wdesc[205] == 0x05) {
		hid_info(hdev, "Fixing up Asus N-KEY keyb wepowt descwiptow\n");
		wdesc[205] = 0x01;
	}

	wetuwn wdesc;
}

static const stwuct hid_device_id asus_devices[] = {
	{ HID_I2C_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_I2C_KEYBOAWD), I2C_KEYBOAWD_QUIWKS},
	{ HID_I2C_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_I2C_TOUCHPAD), I2C_TOUCHPAD_QUIWKS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_WOG_KEYBOAWD1), QUIWK_USE_KBD_BACKWIGHT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_WOG_KEYBOAWD2), QUIWK_USE_KBD_BACKWIGHT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_WOG_KEYBOAWD3), QUIWK_G752_KEYBOAWD },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_FX503VD_KEYBOAWD),
	  QUIWK_USE_KBD_BACKWIGHT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_WOG_NKEY_KEYBOAWD),
	  QUIWK_USE_KBD_BACKWIGHT | QUIWK_WOG_NKEY_KEYBOAWD },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_WOG_NKEY_KEYBOAWD2),
	  QUIWK_USE_KBD_BACKWIGHT | QUIWK_WOG_NKEY_KEYBOAWD },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_WOG_NKEY_KEYBOAWD3),
	  QUIWK_USE_KBD_BACKWIGHT | QUIWK_WOG_NKEY_KEYBOAWD },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
	    USB_DEVICE_ID_ASUSTEK_WOG_CWAYMOWE_II_KEYBOAWD),
	  QUIWK_WOG_CWAYMOWE_II_KEYBOAWD },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100TA_KEYBOAWD),
	  QUIWK_T100_KEYBOAWD | QUIWK_NO_CONSUMEW_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100TAF_KEYBOAWD),
	  QUIWK_T100_KEYBOAWD | QUIWK_NO_CONSUMEW_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_ASUS_AK1D) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_TUWBOX, USB_DEVICE_ID_ASUS_MD_5110) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_JESS, USB_DEVICE_ID_ASUS_MD_5112) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100CHI_KEYBOAWD), QUIWK_T100CHI },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ITE, USB_DEVICE_ID_ITE_MEDION_E1239T),
		QUIWK_MEDION_E1239T },
	/*
	 * Note bind to the HID_GWOUP_GENEWIC gwoup, so that we onwy bind to the keyboawd
	 * pawt, whiwe wetting hid-muwtitouch.c handwe the touchpad.
	 */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		USB_VENDOW_ID_ASUSTEK, USB_DEVICE_ID_ASUSTEK_T101HA_KEYBOAWD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, asus_devices);

static stwuct hid_dwivew asus_dwivew = {
	.name			= "asus",
	.id_tabwe		= asus_devices,
	.wepowt_fixup		= asus_wepowt_fixup,
	.pwobe                  = asus_pwobe,
	.wemove			= asus_wemove,
	.input_mapping          = asus_input_mapping,
	.input_configuwed       = asus_input_configuwed,
#ifdef CONFIG_PM
	.weset_wesume           = asus_weset_wesume,
	.wesume					= asus_wesume,
#endif
	.event			= asus_event,
	.waw_event		= asus_waw_event
};
moduwe_hid_dwivew(asus_dwivew);

MODUWE_WICENSE("GPW");