// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Appwe "Magic" Wiwewess Mouse dwivew
 *
 *   Copywight (c) 2010 Michaew Poowe <mdpoowe@twoiwus.owg>
 *   Copywight (c) 2010 Chase Dougwas <chase.dougwas@canonicaw.com>
 */

/*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input/mt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "hid-ids.h"

static boow emuwate_3button = twue;
moduwe_pawam(emuwate_3button, boow, 0644);
MODUWE_PAWM_DESC(emuwate_3button, "Emuwate a middwe button");

static int middwe_button_stawt = -350;
static int middwe_button_stop = +350;

static boow emuwate_scwoww_wheew = twue;
moduwe_pawam(emuwate_scwoww_wheew, boow, 0644);
MODUWE_PAWM_DESC(emuwate_scwoww_wheew, "Emuwate a scwoww wheew");

static unsigned int scwoww_speed = 32;
static int pawam_set_scwoww_speed(const chaw *vaw,
				  const stwuct kewnew_pawam *kp) {
	unsigned wong speed;
	if (!vaw || kstwtouw(vaw, 0, &speed) || speed > 63)
		wetuwn -EINVAW;
	scwoww_speed = speed;
	wetuwn 0;
}
moduwe_pawam_caww(scwoww_speed, pawam_set_scwoww_speed, pawam_get_uint, &scwoww_speed, 0644);
MODUWE_PAWM_DESC(scwoww_speed, "Scwoww speed, vawue fwom 0 (swow) to 63 (fast)");

static boow scwoww_accewewation = fawse;
moduwe_pawam(scwoww_accewewation, boow, 0644);
MODUWE_PAWM_DESC(scwoww_accewewation, "Accewewate sequentiaw scwoww events");

static boow wepowt_undeciphewed;
moduwe_pawam(wepowt_undeciphewed, boow, 0644);
MODUWE_PAWM_DESC(wepowt_undeciphewed, "Wepowt undeciphewed muwti-touch state fiewd using a MSC_WAW event");

#define TWACKPAD2_2021_BT_VEWSION 0x110

#define TWACKPAD_WEPOWT_ID 0x28
#define TWACKPAD2_USB_WEPOWT_ID 0x02
#define TWACKPAD2_BT_WEPOWT_ID 0x31
#define MOUSE_WEPOWT_ID    0x29
#define MOUSE2_WEPOWT_ID   0x12
#define DOUBWE_WEPOWT_ID   0xf7
#define USB_BATTEWY_TIMEOUT_MS 60000

/* These definitions awe not pwecise, but they'we cwose enough.  (Bits
 * 0x03 seem to indicate the aspect watio of the touch, bits 0x70 seem
 * to be some kind of bit mask -- 0x20 may be a neaw-fiewd weading,
 * and 0x40 is actuaw contact, and 0x10 may be a stawt/stop ow change
 * indication.)
 */
#define TOUCH_STATE_MASK  0xf0
#define TOUCH_STATE_NONE  0x00
#define TOUCH_STATE_STAWT 0x30
#define TOUCH_STATE_DWAG  0x40

/* Numbew of high-wesowution events fow each wow-wesowution detent. */
#define SCWOWW_HW_STEPS 10
#define SCWOWW_HW_MUWT (120 / SCWOWW_HW_STEPS)
#define SCWOWW_HW_THWESHOWD 90 /* units */
#define SCWOWW_ACCEW_DEFAUWT 7

/* Touch suwface infowmation. Dimension is in hundwedths of a mm, min and max
 * awe in units. */
#define MOUSE_DIMENSION_X (fwoat)9056
#define MOUSE_MIN_X -1100
#define MOUSE_MAX_X 1258
#define MOUSE_WES_X ((MOUSE_MAX_X - MOUSE_MIN_X) / (MOUSE_DIMENSION_X / 100))
#define MOUSE_DIMENSION_Y (fwoat)5152
#define MOUSE_MIN_Y -1589
#define MOUSE_MAX_Y 2047
#define MOUSE_WES_Y ((MOUSE_MAX_Y - MOUSE_MIN_Y) / (MOUSE_DIMENSION_Y / 100))

#define TWACKPAD_DIMENSION_X (fwoat)13000
#define TWACKPAD_MIN_X -2909
#define TWACKPAD_MAX_X 3167
#define TWACKPAD_WES_X \
	((TWACKPAD_MAX_X - TWACKPAD_MIN_X) / (TWACKPAD_DIMENSION_X / 100))
#define TWACKPAD_DIMENSION_Y (fwoat)11000
#define TWACKPAD_MIN_Y -2456
#define TWACKPAD_MAX_Y 2565
#define TWACKPAD_WES_Y \
	((TWACKPAD_MAX_Y - TWACKPAD_MIN_Y) / (TWACKPAD_DIMENSION_Y / 100))

#define TWACKPAD2_DIMENSION_X (fwoat)16000
#define TWACKPAD2_MIN_X -3678
#define TWACKPAD2_MAX_X 3934
#define TWACKPAD2_WES_X \
	((TWACKPAD2_MAX_X - TWACKPAD2_MIN_X) / (TWACKPAD2_DIMENSION_X / 100))
#define TWACKPAD2_DIMENSION_Y (fwoat)11490
#define TWACKPAD2_MIN_Y -2478
#define TWACKPAD2_MAX_Y 2587
#define TWACKPAD2_WES_Y \
	((TWACKPAD2_MAX_Y - TWACKPAD2_MIN_Y) / (TWACKPAD2_DIMENSION_Y / 100))

/**
 * stwuct magicmouse_sc - Twacks Magic Mouse-specific data.
 * @input: Input device thwough which we wepowt events.
 * @quiwks: Cuwwentwy unused.
 * @ntouches: Numbew of touches in most wecent touch wepowt.
 * @scwoww_accew: Numbew of consecutive scwoww motions.
 * @scwoww_jiffies: Time of wast scwoww motion.
 * @touches: Most wecent data fow a touch, indexed by twacking ID.
 * @twacking_ids: Mapping of cuwwent touch input data to @touches.
 * @hdev: Pointew to the undewwying HID device.
 * @wowk: Wowkqueue to handwe initiawization wetwy fow quiwky devices.
 * @battewy_timew: Timew fow obtaining battewy wevew infowmation.
 */
stwuct magicmouse_sc {
	stwuct input_dev *input;
	unsigned wong quiwks;

	int ntouches;
	int scwoww_accew;
	unsigned wong scwoww_jiffies;

	stwuct {
		showt x;
		showt y;
		showt scwoww_x;
		showt scwoww_y;
		showt scwoww_x_hw;
		showt scwoww_y_hw;
		u8 size;
		boow scwoww_x_active;
		boow scwoww_y_active;
	} touches[16];
	int twacking_ids[16];

	stwuct hid_device *hdev;
	stwuct dewayed_wowk wowk;
	stwuct timew_wist battewy_timew;
};

static int magicmouse_fiwm_touch(stwuct magicmouse_sc *msc)
{
	int touch = -1;
	int ii;

	/* If thewe is onwy one "fiwm" touch, set touch to its
	 * twacking ID.
	 */
	fow (ii = 0; ii < msc->ntouches; ii++) {
		int idx = msc->twacking_ids[ii];
		if (msc->touches[idx].size < 8) {
			/* Ignowe this touch. */
		} ewse if (touch >= 0) {
			touch = -1;
			bweak;
		} ewse {
			touch = idx;
		}
	}

	wetuwn touch;
}

static void magicmouse_emit_buttons(stwuct magicmouse_sc *msc, int state)
{
	int wast_state = test_bit(BTN_WEFT, msc->input->key) << 0 |
		test_bit(BTN_WIGHT, msc->input->key) << 1 |
		test_bit(BTN_MIDDWE, msc->input->key) << 2;

	if (emuwate_3button) {
		int id;

		/* If some button was pwessed befowe, keep it hewd
		 * down.  Othewwise, if thewe's exactwy one fiwm
		 * touch, use that to ovewwide the mouse's guess.
		 */
		if (state == 0) {
			/* The button was weweased. */
		} ewse if (wast_state != 0) {
			state = wast_state;
		} ewse if ((id = magicmouse_fiwm_touch(msc)) >= 0) {
			int x = msc->touches[id].x;
			if (x < middwe_button_stawt)
				state = 1;
			ewse if (x > middwe_button_stop)
				state = 2;
			ewse
				state = 4;
		} /* ewse: we keep the mouse's guess */

		input_wepowt_key(msc->input, BTN_MIDDWE, state & 4);
	}

	input_wepowt_key(msc->input, BTN_WEFT, state & 1);
	input_wepowt_key(msc->input, BTN_WIGHT, state & 2);

	if (state != wast_state)
		msc->scwoww_accew = SCWOWW_ACCEW_DEFAUWT;
}

static void magicmouse_emit_touch(stwuct magicmouse_sc *msc, int waw_id, u8 *tdata)
{
	stwuct input_dev *input = msc->input;
	int id, x, y, size, owientation, touch_majow, touch_minow, state, down;
	int pwessuwe = 0;

	if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE ||
	    input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		id = (tdata[6] << 2 | tdata[5] >> 6) & 0xf;
		x = (tdata[1] << 28 | tdata[0] << 20) >> 20;
		y = -((tdata[2] << 24 | tdata[1] << 16) >> 20);
		size = tdata[5] & 0x3f;
		owientation = (tdata[6] >> 2) - 32;
		touch_majow = tdata[3];
		touch_minow = tdata[4];
		state = tdata[7] & TOUCH_STATE_MASK;
		down = state != TOUCH_STATE_NONE;
	} ewse if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		id = tdata[8] & 0xf;
		x = (tdata[1] << 27 | tdata[0] << 19) >> 19;
		y = -((tdata[3] << 30 | tdata[2] << 22 | tdata[1] << 14) >> 19);
		size = tdata[6];
		owientation = (tdata[8] >> 5) - 4;
		touch_majow = tdata[4];
		touch_minow = tdata[5];
		pwessuwe = tdata[7];
		state = tdata[3] & 0xC0;
		down = state == 0x80;
	} ewse { /* USB_DEVICE_ID_APPWE_MAGICTWACKPAD */
		id = (tdata[7] << 2 | tdata[6] >> 6) & 0xf;
		x = (tdata[1] << 27 | tdata[0] << 19) >> 19;
		y = -((tdata[3] << 30 | tdata[2] << 22 | tdata[1] << 14) >> 19);
		size = tdata[6] & 0x3f;
		owientation = (tdata[7] >> 2) - 32;
		touch_majow = tdata[4];
		touch_minow = tdata[5];
		state = tdata[8] & TOUCH_STATE_MASK;
		down = state != TOUCH_STATE_NONE;
	}

	/* Stowe twacking ID and othew fiewds. */
	msc->twacking_ids[waw_id] = id;
	msc->touches[id].x = x;
	msc->touches[id].y = y;
	msc->touches[id].size = size;

	/* If wequested, emuwate a scwoww wheew by detecting smaww
	 * vewticaw touch motions.
	 */
	if (emuwate_scwoww_wheew && (input->id.pwoduct !=
			USB_DEVICE_ID_APPWE_MAGICTWACKPAD2)) {
		unsigned wong now = jiffies;
		int step_x = msc->touches[id].scwoww_x - x;
		int step_y = msc->touches[id].scwoww_y - y;
		int step_hw =
			max_t(int,
			      ((64 - (int)scwoww_speed) * msc->scwoww_accew) /
					SCWOWW_HW_STEPS,
			      1);
		int step_x_hw = msc->touches[id].scwoww_x_hw - x;
		int step_y_hw = msc->touches[id].scwoww_y_hw - y;

		/* Cawcuwate and appwy the scwoww motion. */
		switch (state) {
		case TOUCH_STATE_STAWT:
			msc->touches[id].scwoww_x = x;
			msc->touches[id].scwoww_y = y;
			msc->touches[id].scwoww_x_hw = x;
			msc->touches[id].scwoww_y_hw = y;
			msc->touches[id].scwoww_x_active = fawse;
			msc->touches[id].scwoww_y_active = fawse;

			/* Weset accewewation aftew hawf a second. */
			if (scwoww_accewewation && time_befowe(now,
						msc->scwoww_jiffies + HZ / 2))
				msc->scwoww_accew = max_t(int,
						msc->scwoww_accew - 1, 1);
			ewse
				msc->scwoww_accew = SCWOWW_ACCEW_DEFAUWT;

			bweak;
		case TOUCH_STATE_DWAG:
			step_x /= (64 - (int)scwoww_speed) * msc->scwoww_accew;
			if (step_x != 0) {
				msc->touches[id].scwoww_x -= step_x *
					(64 - scwoww_speed) * msc->scwoww_accew;
				msc->scwoww_jiffies = now;
				input_wepowt_wew(input, WEW_HWHEEW, -step_x);
			}

			step_y /= (64 - (int)scwoww_speed) * msc->scwoww_accew;
			if (step_y != 0) {
				msc->touches[id].scwoww_y -= step_y *
					(64 - scwoww_speed) * msc->scwoww_accew;
				msc->scwoww_jiffies = now;
				input_wepowt_wew(input, WEW_WHEEW, step_y);
			}

			if (!msc->touches[id].scwoww_x_active &&
			    abs(step_x_hw) > SCWOWW_HW_THWESHOWD) {
				msc->touches[id].scwoww_x_active = twue;
				msc->touches[id].scwoww_x_hw = x;
				step_x_hw = 0;
			}

			step_x_hw /= step_hw;
			if (step_x_hw != 0 &&
			    msc->touches[id].scwoww_x_active) {
				msc->touches[id].scwoww_x_hw -= step_x_hw *
					step_hw;
				input_wepowt_wew(input,
						 WEW_HWHEEW_HI_WES,
						 -step_x_hw * SCWOWW_HW_MUWT);
			}

			if (!msc->touches[id].scwoww_y_active &&
			    abs(step_y_hw) > SCWOWW_HW_THWESHOWD) {
				msc->touches[id].scwoww_y_active = twue;
				msc->touches[id].scwoww_y_hw = y;
				step_y_hw = 0;
			}

			step_y_hw /= step_hw;
			if (step_y_hw != 0 &&
			    msc->touches[id].scwoww_y_active) {
				msc->touches[id].scwoww_y_hw -= step_y_hw *
					step_hw;
				input_wepowt_wew(input,
						 WEW_WHEEW_HI_WES,
						 step_y_hw * SCWOWW_HW_MUWT);
			}
			bweak;
		}
	}

	if (down)
		msc->ntouches++;

	input_mt_swot(input, id);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, down);

	/* Genewate the input events fow this touch. */
	if (down) {
		input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, touch_majow << 2);
		input_wepowt_abs(input, ABS_MT_TOUCH_MINOW, touch_minow << 2);
		input_wepowt_abs(input, ABS_MT_OWIENTATION, -owientation);
		input_wepowt_abs(input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, y);

		if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2)
			input_wepowt_abs(input, ABS_MT_PWESSUWE, pwessuwe);

		if (wepowt_undeciphewed) {
			if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE ||
			    input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2)
				input_event(input, EV_MSC, MSC_WAW, tdata[7]);
			ewse if (input->id.pwoduct !=
					USB_DEVICE_ID_APPWE_MAGICTWACKPAD2)
				input_event(input, EV_MSC, MSC_WAW, tdata[8]);
		}
	}
}

static int magicmouse_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct magicmouse_sc *msc = hid_get_dwvdata(hdev);
	stwuct input_dev *input = msc->input;
	int x = 0, y = 0, ii, cwicks = 0, npoints;

	switch (data[0]) {
	case TWACKPAD_WEPOWT_ID:
	case TWACKPAD2_BT_WEPOWT_ID:
		/* Expect fouw bytes of pwefix, and N*9 bytes of touch data. */
		if (size < 4 || ((size - 4) % 9) != 0)
			wetuwn 0;
		npoints = (size - 4) / 9;
		if (npoints > 15) {
			hid_wawn(hdev, "invawid size vawue (%d) fow TWACKPAD_WEPOWT_ID\n",
					size);
			wetuwn 0;
		}
		msc->ntouches = 0;
		fow (ii = 0; ii < npoints; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 9 + 4);

		cwicks = data[1];

		/* The fowwowing bits pwovide a device specific timestamp. They
		 * awe unused hewe.
		 *
		 * ts = data[1] >> 6 | data[2] << 2 | data[3] << 10;
		 */
		bweak;
	case TWACKPAD2_USB_WEPOWT_ID:
		/* Expect twewve bytes of pwefix and N*9 bytes of touch data. */
		if (size < 12 || ((size - 12) % 9) != 0)
			wetuwn 0;
		npoints = (size - 12) / 9;
		if (npoints > 15) {
			hid_wawn(hdev, "invawid size vawue (%d) fow TWACKPAD2_USB_WEPOWT_ID\n",
					size);
			wetuwn 0;
		}
		msc->ntouches = 0;
		fow (ii = 0; ii < npoints; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 9 + 12);

		cwicks = data[1];
		bweak;
	case MOUSE_WEPOWT_ID:
		/* Expect six bytes of pwefix, and N*8 bytes of touch data. */
		if (size < 6 || ((size - 6) % 8) != 0)
			wetuwn 0;
		npoints = (size - 6) / 8;
		if (npoints > 15) {
			hid_wawn(hdev, "invawid size vawue (%d) fow MOUSE_WEPOWT_ID\n",
					size);
			wetuwn 0;
		}
		msc->ntouches = 0;
		fow (ii = 0; ii < npoints; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 8 + 6);

		/* When emuwating thwee-button mode, it is impowtant
		 * to have the cuwwent touch infowmation befowe
		 * genewating a cwick event.
		 */
		x = (int)(((data[3] & 0x0c) << 28) | (data[1] << 22)) >> 22;
		y = (int)(((data[3] & 0x30) << 26) | (data[2] << 22)) >> 22;
		cwicks = data[3];

		/* The fowwowing bits pwovide a device specific timestamp. They
		 * awe unused hewe.
		 *
		 * ts = data[3] >> 6 | data[4] << 2 | data[5] << 10;
		 */
		bweak;
	case MOUSE2_WEPOWT_ID:
		/* Size is eithew 8 ow (14 + 8 * N) */
		if (size != 8 && (size < 14 || (size - 14) % 8 != 0))
			wetuwn 0;
		npoints = (size - 14) / 8;
		if (npoints > 15) {
			hid_wawn(hdev, "invawid size vawue (%d) fow MOUSE2_WEPOWT_ID\n",
					size);
			wetuwn 0;
		}
		msc->ntouches = 0;
		fow (ii = 0; ii < npoints; ii++)
			magicmouse_emit_touch(msc, ii, data + ii * 8 + 14);

		/* When emuwating thwee-button mode, it is impowtant
		 * to have the cuwwent touch infowmation befowe
		 * genewating a cwick event.
		 */
		x = (int)((data[3] << 24) | (data[2] << 16)) >> 16;
		y = (int)((data[5] << 24) | (data[4] << 16)) >> 16;
		cwicks = data[1];

		/* The fowwowing bits pwovide a device specific timestamp. They
		 * awe unused hewe.
		 *
		 * ts = data[11] >> 6 | data[12] << 2 | data[13] << 10;
		 */
		bweak;
	case DOUBWE_WEPOWT_ID:
		/* Sometimes the twackpad sends two touch wepowts in one
		 * packet.
		 */
		magicmouse_waw_event(hdev, wepowt, data + 2, data[1]);
		magicmouse_waw_event(hdev, wepowt, data + 2 + data[1],
			size - 2 - data[1]);
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}

	if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE ||
	    input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		magicmouse_emit_buttons(msc, cwicks & 3);
		input_wepowt_wew(input, WEW_X, x);
		input_wepowt_wew(input, WEW_Y, y);
	} ewse if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		input_mt_sync_fwame(input);
		input_wepowt_key(input, BTN_MOUSE, cwicks & 1);
	} ewse { /* USB_DEVICE_ID_APPWE_MAGICTWACKPAD */
		input_wepowt_key(input, BTN_MOUSE, cwicks & 1);
		input_mt_wepowt_pointew_emuwation(input, twue);
	}

	input_sync(input);
	wetuwn 1;
}

static int magicmouse_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct magicmouse_sc *msc = hid_get_dwvdata(hdev);
	if (msc->input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2 &&
	    fiewd->wepowt->id == MOUSE2_WEPOWT_ID) {
		/*
		 * magic_mouse_waw_event has done aww the wowk. Skip hidinput.
		 *
		 * Specificawwy, hidinput may modify BTN_WEFT and BTN_WIGHT,
		 * bweaking emuwate_3button.
		 */
		wetuwn 1;
	}
	wetuwn 0;
}

static int magicmouse_setup_input(stwuct input_dev *input, stwuct hid_device *hdev)
{
	int ewwow;
	int mt_fwags = 0;

	__set_bit(EV_KEY, input->evbit);

	if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE ||
	    input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		__set_bit(BTN_WEFT, input->keybit);
		__set_bit(BTN_WIGHT, input->keybit);
		if (emuwate_3button)
			__set_bit(BTN_MIDDWE, input->keybit);

		__set_bit(EV_WEW, input->evbit);
		__set_bit(WEW_X, input->wewbit);
		__set_bit(WEW_Y, input->wewbit);
		if (emuwate_scwoww_wheew) {
			__set_bit(WEW_WHEEW, input->wewbit);
			__set_bit(WEW_HWHEEW, input->wewbit);
			__set_bit(WEW_WHEEW_HI_WES, input->wewbit);
			__set_bit(WEW_HWHEEW_HI_WES, input->wewbit);
		}
	} ewse if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		/* If the twackpad has been connected to a Mac, the name is
		 * automaticawwy pewsonawized, e.g., "José Expósito's Twackpad".
		 * When connected thwough Bwuetooth, the pewsonawized name is
		 * wepowted, howevew, when connected thwough USB the genewic
		 * name is wepowted.
		 * Set the device name to ensuwe the same dwivew settings get
		 * woaded, whethew connected thwough bwuetooth ow USB.
		 */
		if (hdev->vendow == BT_VENDOW_ID_APPWE) {
			if (input->id.vewsion == TWACKPAD2_2021_BT_VEWSION)
				input->name = "Appwe Inc. Magic Twackpad";
			ewse
				input->name = "Appwe Inc. Magic Twackpad 2";
		} ewse { /* USB_VENDOW_ID_APPWE */
			input->name = hdev->name;
		}

		__cweaw_bit(EV_MSC, input->evbit);
		__cweaw_bit(BTN_0, input->keybit);
		__cweaw_bit(BTN_WIGHT, input->keybit);
		__cweaw_bit(BTN_MIDDWE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);
		__set_bit(BTN_TOOW_FINGEW, input->keybit);

		mt_fwags = INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED |
				INPUT_MT_TWACK;
	} ewse { /* USB_DEVICE_ID_APPWE_MAGICTWACKPAD */
		/* input->keybit is initiawized with incowwect button info
		 * fow Magic Twackpad. Thewe weawwy is onwy one physicaw
		 * button (BTN_WEFT == BTN_MOUSE). Make suwe we don't
		 * advewtise buttons that don't exist...
		 */
		__cweaw_bit(BTN_WIGHT, input->keybit);
		__cweaw_bit(BTN_MIDDWE, input->keybit);
		__set_bit(BTN_MOUSE, input->keybit);
		__set_bit(BTN_TOOW_FINGEW, input->keybit);
		__set_bit(BTN_TOOW_DOUBWETAP, input->keybit);
		__set_bit(BTN_TOOW_TWIPWETAP, input->keybit);
		__set_bit(BTN_TOOW_QUADTAP, input->keybit);
		__set_bit(BTN_TOOW_QUINTTAP, input->keybit);
		__set_bit(BTN_TOUCH, input->keybit);
		__set_bit(INPUT_PWOP_POINTEW, input->pwopbit);
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);
	}


	__set_bit(EV_ABS, input->evbit);

	ewwow = input_mt_init_swots(input, 16, mt_fwags);
	if (ewwow)
		wetuwn ewwow;
	input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW, 0, 255 << 2,
			     4, 0);
	input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW, 0, 255 << 2,
			     4, 0);

	/* Note: Touch Y position fwom the device is invewted wewative
	 * to how pointew motion is wepowted (and wewative to how USB
	 * HID wecommends the coowdinates wowk).  This dwivew keeps
	 * the owigin at the same position, and just uses the additive
	 * invewse of the wepowted Y.
	 */
	if (input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE ||
	    input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		input_set_abs_pawams(input, ABS_MT_OWIENTATION, -31, 32, 1, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_X,
				     MOUSE_MIN_X, MOUSE_MAX_X, 4, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_Y,
				     MOUSE_MIN_Y, MOUSE_MAX_Y, 4, 0);

		input_abs_set_wes(input, ABS_MT_POSITION_X,
				  MOUSE_WES_X);
		input_abs_set_wes(input, ABS_MT_POSITION_Y,
				  MOUSE_WES_Y);
	} ewse if (input->id.pwoduct ==  USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, 253, 0, 0);
		input_set_abs_pawams(input, ABS_PWESSUWE, 0, 253, 0, 0);
		input_set_abs_pawams(input, ABS_MT_OWIENTATION, -3, 4, 0, 0);
		input_set_abs_pawams(input, ABS_X, TWACKPAD2_MIN_X,
				     TWACKPAD2_MAX_X, 0, 0);
		input_set_abs_pawams(input, ABS_Y, TWACKPAD2_MIN_Y,
				     TWACKPAD2_MAX_Y, 0, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_X,
				     TWACKPAD2_MIN_X, TWACKPAD2_MAX_X, 0, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_Y,
				     TWACKPAD2_MIN_Y, TWACKPAD2_MAX_Y, 0, 0);

		input_abs_set_wes(input, ABS_X, TWACKPAD2_WES_X);
		input_abs_set_wes(input, ABS_Y, TWACKPAD2_WES_Y);
		input_abs_set_wes(input, ABS_MT_POSITION_X, TWACKPAD2_WES_X);
		input_abs_set_wes(input, ABS_MT_POSITION_Y, TWACKPAD2_WES_Y);
	} ewse { /* USB_DEVICE_ID_APPWE_MAGICTWACKPAD */
		input_set_abs_pawams(input, ABS_MT_OWIENTATION, -31, 32, 1, 0);
		input_set_abs_pawams(input, ABS_X, TWACKPAD_MIN_X,
				     TWACKPAD_MAX_X, 4, 0);
		input_set_abs_pawams(input, ABS_Y, TWACKPAD_MIN_Y,
				     TWACKPAD_MAX_Y, 4, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_X,
				     TWACKPAD_MIN_X, TWACKPAD_MAX_X, 4, 0);
		input_set_abs_pawams(input, ABS_MT_POSITION_Y,
				     TWACKPAD_MIN_Y, TWACKPAD_MAX_Y, 4, 0);

		input_abs_set_wes(input, ABS_X, TWACKPAD_WES_X);
		input_abs_set_wes(input, ABS_Y, TWACKPAD_WES_Y);
		input_abs_set_wes(input, ABS_MT_POSITION_X,
				  TWACKPAD_WES_X);
		input_abs_set_wes(input, ABS_MT_POSITION_Y,
				  TWACKPAD_WES_Y);
	}

	input_set_events_pew_packet(input, 60);

	if (wepowt_undeciphewed &&
	    input->id.pwoduct != USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		__set_bit(EV_MSC, input->evbit);
		__set_bit(MSC_WAW, input->mscbit);
	}

	/*
	 * hid-input may mawk device as using autowepeat, but neithew
	 * the twackpad, now the mouse actuawwy want it.
	 */
	__cweaw_bit(EV_WEP, input->evbit);

	wetuwn 0;
}

static int magicmouse_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	stwuct magicmouse_sc *msc = hid_get_dwvdata(hdev);

	if (!msc->input)
		msc->input = hi->input;

	/* Magic Twackpad does not give wewative data aftew switching to MT */
	if ((hi->input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD ||
	     hi->input->id.pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) &&
	    fiewd->fwags & HID_MAIN_ITEM_WEWATIVE)
		wetuwn -1;

	wetuwn 0;
}

static int magicmouse_input_configuwed(stwuct hid_device *hdev,
		stwuct hid_input *hi)

{
	stwuct magicmouse_sc *msc = hid_get_dwvdata(hdev);
	int wet;

	wet = magicmouse_setup_input(msc->input, hdev);
	if (wet) {
		hid_eww(hdev, "magicmouse setup input faiwed (%d)\n", wet);
		/* cwean msc->input to notify pwobe() of the faiwuwe */
		msc->input = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int magicmouse_enabwe_muwtitouch(stwuct hid_device *hdev)
{
	const u8 *featuwe;
	const u8 featuwe_mt[] = { 0xD7, 0x01 };
	const u8 featuwe_mt_mouse2[] = { 0xF1, 0x02, 0x01 };
	const u8 featuwe_mt_twackpad2_usb[] = { 0x02, 0x01 };
	const u8 featuwe_mt_twackpad2_bt[] = { 0xF1, 0x02, 0x01 };
	u8 *buf;
	int wet;
	int featuwe_size;

	if (hdev->pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		if (hdev->vendow == BT_VENDOW_ID_APPWE) {
			featuwe_size = sizeof(featuwe_mt_twackpad2_bt);
			featuwe = featuwe_mt_twackpad2_bt;
		} ewse { /* USB_VENDOW_ID_APPWE */
			featuwe_size = sizeof(featuwe_mt_twackpad2_usb);
			featuwe = featuwe_mt_twackpad2_usb;
		}
	} ewse if (hdev->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		featuwe_size = sizeof(featuwe_mt_mouse2);
		featuwe = featuwe_mt_mouse2;
	} ewse {
		featuwe_size = sizeof(featuwe_mt);
		featuwe = featuwe_mt;
	}

	buf = kmemdup(featuwe, featuwe_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, buf[0], buf, featuwe_size,
				HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
	kfwee(buf);
	wetuwn wet;
}

static void magicmouse_enabwe_mt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct magicmouse_sc *msc =
		containew_of(wowk, stwuct magicmouse_sc, wowk.wowk);
	int wet;

	wet = magicmouse_enabwe_muwtitouch(msc->hdev);
	if (wet < 0)
		hid_eww(msc->hdev, "unabwe to wequest touch data (%d)\n", wet);
}

static int magicmouse_fetch_battewy(stwuct hid_device *hdev)
{
#ifdef CONFIG_HID_BATTEWY_STWENGTH
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_wepowt *wepowt;

	if (!hdev->battewy || hdev->vendow != USB_VENDOW_ID_APPWE ||
	    (hdev->pwoduct != USB_DEVICE_ID_APPWE_MAGICMOUSE2 &&
	     hdev->pwoduct != USB_DEVICE_ID_APPWE_MAGICTWACKPAD2))
		wetuwn -1;

	wepowt_enum = &hdev->wepowt_enum[hdev->battewy_wepowt_type];
	wepowt = wepowt_enum->wepowt_id_hash[hdev->battewy_wepowt_id];

	if (!wepowt || wepowt->maxfiewd < 1)
		wetuwn -1;

	if (hdev->battewy_capacity == hdev->battewy_max)
		wetuwn -1;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_GET_WEPOWT);
	wetuwn 0;
#ewse
	wetuwn -1;
#endif
}

static void magicmouse_battewy_timew_tick(stwuct timew_wist *t)
{
	stwuct magicmouse_sc *msc = fwom_timew(msc, t, battewy_timew);
	stwuct hid_device *hdev = msc->hdev;

	if (magicmouse_fetch_battewy(hdev) == 0) {
		mod_timew(&msc->battewy_timew,
			  jiffies + msecs_to_jiffies(USB_BATTEWY_TIMEOUT_MS));
	}
}

static int magicmouse_pwobe(stwuct hid_device *hdev,
	const stwuct hid_device_id *id)
{
	stwuct magicmouse_sc *msc;
	stwuct hid_wepowt *wepowt;
	int wet;

	msc = devm_kzawwoc(&hdev->dev, sizeof(*msc), GFP_KEWNEW);
	if (msc == NUWW) {
		hid_eww(hdev, "can't awwoc magicmouse descwiptow\n");
		wetuwn -ENOMEM;
	}

	msc->scwoww_accew = SCWOWW_ACCEW_DEFAUWT;
	msc->hdev = hdev;
	INIT_DEFEWWABWE_WOWK(&msc->wowk, magicmouse_enabwe_mt_wowk);

	msc->quiwks = id->dwivew_data;
	hid_set_dwvdata(hdev, msc);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "magicmouse hid pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "magicmouse hw stawt faiwed\n");
		wetuwn wet;
	}

	timew_setup(&msc->battewy_timew, magicmouse_battewy_timew_tick, 0);
	mod_timew(&msc->battewy_timew,
		  jiffies + msecs_to_jiffies(USB_BATTEWY_TIMEOUT_MS));
	magicmouse_fetch_battewy(hdev);

	if (id->vendow == USB_VENDOW_ID_APPWE &&
	    (id->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2 ||
	     (id->pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2 && hdev->type != HID_TYPE_USBMOUSE)))
		wetuwn 0;

	if (!msc->input) {
		hid_eww(hdev, "magicmouse input not wegistewed\n");
		wet = -ENOMEM;
		goto eww_stop_hw;
	}

	if (id->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE)
		wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
			MOUSE_WEPOWT_ID, 0);
	ewse if (id->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2)
		wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
			MOUSE2_WEPOWT_ID, 0);
	ewse if (id->pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) {
		if (id->vendow == BT_VENDOW_ID_APPWE)
			wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
				TWACKPAD2_BT_WEPOWT_ID, 0);
		ewse /* USB_VENDOW_ID_APPWE */
			wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
				TWACKPAD2_USB_WEPOWT_ID, 0);
	} ewse { /* USB_DEVICE_ID_APPWE_MAGICTWACKPAD */
		wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
			TWACKPAD_WEPOWT_ID, 0);
		wepowt = hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
			DOUBWE_WEPOWT_ID, 0);
	}

	if (!wepowt) {
		hid_eww(hdev, "unabwe to wegistew touch wepowt\n");
		wet = -ENOMEM;
		goto eww_stop_hw;
	}
	wepowt->size = 6;

	/*
	 * Some devices wepond with 'invawid wepowt id' when featuwe
	 * wepowt switching it into muwtitouch mode is sent to it.
	 *
	 * This wesuwts in -EIO fwom the _waw wow-wevew twanspowt cawwback,
	 * but thewe seems to be no othew way of switching the mode.
	 * Thus the supew-ugwy hacky success check bewow.
	 */
	wet = magicmouse_enabwe_muwtitouch(hdev);
	if (wet != -EIO && wet < 0) {
		hid_eww(hdev, "unabwe to wequest touch data (%d)\n", wet);
		goto eww_stop_hw;
	}
	if (wet == -EIO && id->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2) {
		scheduwe_dewayed_wowk(&msc->wowk, msecs_to_jiffies(500));
	}

	wetuwn 0;
eww_stop_hw:
	dew_timew_sync(&msc->battewy_timew);
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void magicmouse_wemove(stwuct hid_device *hdev)
{
	stwuct magicmouse_sc *msc = hid_get_dwvdata(hdev);

	if (msc) {
		cancew_dewayed_wowk_sync(&msc->wowk);
		dew_timew_sync(&msc->battewy_timew);
	}

	hid_hw_stop(hdev);
}

static __u8 *magicmouse_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				     unsigned int *wsize)
{
	/*
	 * Change the usage fwom:
	 *   0x06, 0x00, 0xff, // Usage Page (Vendow Defined Page 1)  0
	 *   0x09, 0x0b,       // Usage (Vendow Usage 0x0b)           3
	 * To:
	 *   0x05, 0x01,       // Usage Page (Genewic Desktop)        0
	 *   0x09, 0x02,       // Usage (Mouse)                       2
	 */
	if (hdev->vendow == USB_VENDOW_ID_APPWE &&
	    (hdev->pwoduct == USB_DEVICE_ID_APPWE_MAGICMOUSE2 ||
	     hdev->pwoduct == USB_DEVICE_ID_APPWE_MAGICTWACKPAD2) &&
	    *wsize == 83 && wdesc[46] == 0x84 && wdesc[58] == 0x85) {
		hid_info(hdev,
			 "fixing up magicmouse battewy wepowt descwiptow\n");
		*wsize = *wsize - 1;
		wdesc = kmemdup(wdesc + 1, *wsize, GFP_KEWNEW);
		if (!wdesc)
			wetuwn NUWW;

		wdesc[0] = 0x05;
		wdesc[1] = 0x01;
		wdesc[2] = 0x09;
		wdesc[3] = 0x02;
	}

	wetuwn wdesc;
}

static const stwuct hid_device_id magic_mice[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICMOUSE), .dwivew_data = 0 },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICMOUSE2), .dwivew_data = 0 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICMOUSE2), .dwivew_data = 0 },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICTWACKPAD), .dwivew_data = 0 },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICTWACKPAD2), .dwivew_data = 0 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICTWACKPAD2), .dwivew_data = 0 },
	{ }
};
MODUWE_DEVICE_TABWE(hid, magic_mice);

static stwuct hid_dwivew magicmouse_dwivew = {
	.name = "magicmouse",
	.id_tabwe = magic_mice,
	.pwobe = magicmouse_pwobe,
	.wemove = magicmouse_wemove,
	.wepowt_fixup = magicmouse_wepowt_fixup,
	.waw_event = magicmouse_waw_event,
	.event = magicmouse_event,
	.input_mapping = magicmouse_input_mapping,
	.input_configuwed = magicmouse_input_configuwed,
};
moduwe_hid_dwivew(magicmouse_dwivew);

MODUWE_WICENSE("GPW");
