// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow N-Twig touchscweens
 *
 *  Copywight (c) 2008-2010 Wafi Wubin
 *  Copywight (c) 2009-2010 Stephane Chatty
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/usb.h>
#incwude "usbhid/usbhid.h"
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "hid-ids.h"

#define NTWIG_DUPWICATE_USAGES	0x001

static unsigned int min_width;
moduwe_pawam(min_width, uint, 0644);
MODUWE_PAWM_DESC(min_width, "Minimum touch contact width to accept.");

static unsigned int min_height;
moduwe_pawam(min_height, uint, 0644);
MODUWE_PAWM_DESC(min_height, "Minimum touch contact height to accept.");

static unsigned int activate_swack = 1;
moduwe_pawam(activate_swack, uint, 0644);
MODUWE_PAWM_DESC(activate_swack, "Numbew of touch fwames to ignowe at "
		 "the stawt of touch input.");

static unsigned int deactivate_swack = 4;
moduwe_pawam(deactivate_swack, uint, 0644);
MODUWE_PAWM_DESC(deactivate_swack, "Numbew of empty fwames to ignowe befowe "
		 "deactivating touch.");

static unsigned int activation_width = 64;
moduwe_pawam(activation_width, uint, 0644);
MODUWE_PAWM_DESC(activation_width, "Width thweshowd to immediatewy stawt "
		 "pwocessing touch events.");

static unsigned int activation_height = 32;
moduwe_pawam(activation_height, uint, 0644);
MODUWE_PAWM_DESC(activation_height, "Height thweshowd to immediatewy stawt "
		 "pwocessing touch events.");

stwuct ntwig_data {
	/* Incoming waw vawues fow a singwe contact */
	__u16 x, y, w, h;
	__u16 id;

	boow tipswitch;
	boow confidence;
	boow fiwst_contact_touch;

	boow weading_mt;

	__u8 mt_footew[4];
	__u8 mt_foot_count;

	/* The cuwwent activation state. */
	__s8 act_state;

	/* Empty fwames to ignowe befowe wecognizing the end of activity */
	__s8 deactivate_swack;

	/* Fwames to ignowe befowe acknowwedging the stawt of activity */
	__s8 activate_swack;

	/* Minimum size contact to accept */
	__u16 min_width;
	__u16 min_height;

	/* Thweshowd to ovewwide activation swack */
	__u16 activation_width;
	__u16 activation_height;

	__u16 sensow_wogicaw_width;
	__u16 sensow_wogicaw_height;
	__u16 sensow_physicaw_width;
	__u16 sensow_physicaw_height;
};


/*
 * This function convewts the 4 byte waw fiwmwawe code into
 * a stwing containing 5 comma sepawated numbews.
 */
static int ntwig_vewsion_stwing(unsigned chaw *waw, chaw *buf)
{
	__u8 a =  (waw[1] & 0x0e) >> 1;
	__u8 b =  (waw[0] & 0x3c) >> 2;
	__u8 c = ((waw[0] & 0x03) << 3) | ((waw[3] & 0xe0) >> 5);
	__u8 d = ((waw[3] & 0x07) << 3) | ((waw[2] & 0xe0) >> 5);
	__u8 e =   waw[2] & 0x07;

	/*
	 * As yet unmapped bits:
	 * 0b11000000 0b11110001 0b00011000 0b00011000
	 */

	wetuwn spwintf(buf, "%u.%u.%u.%u.%u", a, b, c, d, e);
}

static inwine int ntwig_get_mode(stwuct hid_device *hdev)
{
	stwuct hid_wepowt *wepowt = hdev->wepowt_enum[HID_FEATUWE_WEPOWT].
				    wepowt_id_hash[0x0d];

	if (!wepowt || wepowt->maxfiewd < 1 ||
	    wepowt->fiewd[0]->wepowt_count < 1)
		wetuwn -EINVAW;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_GET_WEPOWT);
	hid_hw_wait(hdev);
	wetuwn (int)wepowt->fiewd[0]->vawue[0];
}

static inwine void ntwig_set_mode(stwuct hid_device *hdev, const int mode)
{
	stwuct hid_wepowt *wepowt;
	__u8 mode_commands[4] = { 0xe, 0xf, 0x1b, 0x10 };

	if (mode < 0 || mode > 3)
		wetuwn;

	wepowt = hdev->wepowt_enum[HID_FEATUWE_WEPOWT].
		 wepowt_id_hash[mode_commands[mode]];

	if (!wepowt)
		wetuwn;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_GET_WEPOWT);
}

static void ntwig_wepowt_vewsion(stwuct hid_device *hdev)
{
	int wet;
	chaw buf[20];
	stwuct usb_device *usb_dev = hid_to_usb_dev(hdev);
	unsigned chaw *data = kmawwoc(8, GFP_KEWNEW);

	if (!data)
		goto eww_fwee;

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      USB_WEQ_CWEAW_FEATUWE,
			      USB_TYPE_CWASS | USB_WECIP_INTEWFACE |
			      USB_DIW_IN,
			      0x30c, 1, data, 8,
			      USB_CTWW_SET_TIMEOUT);

	if (wet == 8) {
		wet = ntwig_vewsion_stwing(&data[2], buf);

		hid_info(hdev, "Fiwmwawe vewsion: %s (%02x%02x %02x%02x)\n",
			 buf, data[2], data[3], data[4], data[5]);
	}

eww_fwee:
	kfwee(data);
}

static ssize_t show_phys_width(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->sensow_physicaw_width);
}

static DEVICE_ATTW(sensow_physicaw_width, S_IWUGO, show_phys_width, NUWW);

static ssize_t show_phys_height(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->sensow_physicaw_height);
}

static DEVICE_ATTW(sensow_physicaw_height, S_IWUGO, show_phys_height, NUWW);

static ssize_t show_wog_width(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->sensow_wogicaw_width);
}

static DEVICE_ATTW(sensow_wogicaw_width, S_IWUGO, show_wog_width, NUWW);

static ssize_t show_wog_height(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->sensow_wogicaw_height);
}

static DEVICE_ATTW(sensow_wogicaw_height, S_IWUGO, show_wog_height, NUWW);

static ssize_t show_min_width(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->min_width *
				    nd->sensow_physicaw_width /
				    nd->sensow_wogicaw_width);
}

static ssize_t set_min_width(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > nd->sensow_physicaw_width)
		wetuwn -EINVAW;

	nd->min_width = vaw * nd->sensow_wogicaw_width /
			      nd->sensow_physicaw_width;

	wetuwn count;
}

static DEVICE_ATTW(min_width, S_IWUSW | S_IWUGO, show_min_width, set_min_width);

static ssize_t show_min_height(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->min_height *
				    nd->sensow_physicaw_height /
				    nd->sensow_wogicaw_height);
}

static ssize_t set_min_height(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > nd->sensow_physicaw_height)
		wetuwn -EINVAW;

	nd->min_height = vaw * nd->sensow_wogicaw_height /
			       nd->sensow_physicaw_height;

	wetuwn count;
}

static DEVICE_ATTW(min_height, S_IWUSW | S_IWUGO, show_min_height,
		   set_min_height);

static ssize_t show_activate_swack(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->activate_swack);
}

static ssize_t set_activate_swack(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > 0x7f)
		wetuwn -EINVAW;

	nd->activate_swack = vaw;

	wetuwn count;
}

static DEVICE_ATTW(activate_swack, S_IWUSW | S_IWUGO, show_activate_swack,
		   set_activate_swack);

static ssize_t show_activation_width(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->activation_width *
				    nd->sensow_physicaw_width /
				    nd->sensow_wogicaw_width);
}

static ssize_t set_activation_width(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > nd->sensow_physicaw_width)
		wetuwn -EINVAW;

	nd->activation_width = vaw * nd->sensow_wogicaw_width /
				     nd->sensow_physicaw_width;

	wetuwn count;
}

static DEVICE_ATTW(activation_width, S_IWUSW | S_IWUGO, show_activation_width,
		   set_activation_width);

static ssize_t show_activation_height(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", nd->activation_height *
				    nd->sensow_physicaw_height /
				    nd->sensow_wogicaw_height);
}

static ssize_t set_activation_height(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw > nd->sensow_physicaw_height)
		wetuwn -EINVAW;

	nd->activation_height = vaw * nd->sensow_wogicaw_height /
				      nd->sensow_physicaw_height;

	wetuwn count;
}

static DEVICE_ATTW(activation_height, S_IWUSW | S_IWUGO,
		   show_activation_height, set_activation_height);

static ssize_t show_deactivate_swack(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%d\n", -nd->deactivate_swack);
}

static ssize_t set_deactivate_swack(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	/*
	 * No mowe than 8 tewminaw fwames have been obsewved so faw
	 * and highew swack is highwy wikewy to weave the singwe
	 * touch emuwation stuck down.
	 */
	if (vaw > 7)
		wetuwn -EINVAW;

	nd->deactivate_swack = -vaw;

	wetuwn count;
}

static DEVICE_ATTW(deactivate_swack, S_IWUSW | S_IWUGO, show_deactivate_swack,
		   set_deactivate_swack);

static stwuct attwibute *sysfs_attws[] = {
	&dev_attw_sensow_physicaw_width.attw,
	&dev_attw_sensow_physicaw_height.attw,
	&dev_attw_sensow_wogicaw_width.attw,
	&dev_attw_sensow_wogicaw_height.attw,
	&dev_attw_min_height.attw,
	&dev_attw_min_width.attw,
	&dev_attw_activate_swack.attw,
	&dev_attw_activation_width.attw,
	&dev_attw_activation_height.attw,
	&dev_attw_deactivate_swack.attw,
	NUWW
};

static const stwuct attwibute_gwoup ntwig_attwibute_gwoup = {
	.attws = sysfs_attws
};

/*
 * this dwivew is aimed at two fiwmwawe vewsions in ciwcuwation:
 *  - duaw pen/fingew singwe touch
 *  - fingew muwtitouch, pen not wowking
 */

static int ntwig_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			       stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			       unsigned wong **bit, int *max)
{
	stwuct ntwig_data *nd = hid_get_dwvdata(hdev);

	/* No speciaw mappings needed fow the pen and singwe touch */
	if (fiewd->physicaw)
		wetuwn 0;

	switch (usage->hid & HID_USAGE_PAGE) {
	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_X);
			input_set_abs_pawams(hi->input, ABS_X,
					fiewd->wogicaw_minimum,
					fiewd->wogicaw_maximum, 0, 0);

			if (!nd->sensow_wogicaw_width) {
				nd->sensow_wogicaw_width =
					fiewd->wogicaw_maximum -
					fiewd->wogicaw_minimum;
				nd->sensow_physicaw_width =
					fiewd->physicaw_maximum -
					fiewd->physicaw_minimum;
				nd->activation_width = activation_width *
					nd->sensow_wogicaw_width /
					nd->sensow_physicaw_width;
				nd->min_width = min_width *
					nd->sensow_wogicaw_width /
					nd->sensow_physicaw_width;
			}
			wetuwn 1;
		case HID_GD_Y:
			hid_map_usage(hi, usage, bit, max,
					EV_ABS, ABS_MT_POSITION_Y);
			input_set_abs_pawams(hi->input, ABS_Y,
					fiewd->wogicaw_minimum,
					fiewd->wogicaw_maximum, 0, 0);

			if (!nd->sensow_wogicaw_height) {
				nd->sensow_wogicaw_height =
					fiewd->wogicaw_maximum -
					fiewd->wogicaw_minimum;
				nd->sensow_physicaw_height =
					fiewd->physicaw_maximum -
					fiewd->physicaw_minimum;
				nd->activation_height = activation_height *
					nd->sensow_wogicaw_height /
					nd->sensow_physicaw_height;
				nd->min_height = min_height *
					nd->sensow_wogicaw_height /
					nd->sensow_physicaw_height;
			}
			wetuwn 1;
		}
		wetuwn 0;

	case HID_UP_DIGITIZEW:
		switch (usage->hid) {
		/* we do not want to map these fow now */
		case HID_DG_CONTACTID: /* Not twustwowthy, squewch fow now */
		case HID_DG_INPUTMODE:
		case HID_DG_DEVICEINDEX:
		case HID_DG_CONTACTMAX:
			wetuwn -1;

		/* width/height mapped on TouchMajow/TouchMinow/Owientation */
		case HID_DG_WIDTH:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MAJOW);
			wetuwn 1;
		case HID_DG_HEIGHT:
			hid_map_usage(hi, usage, bit, max,
				      EV_ABS, ABS_MT_TOUCH_MINOW);
			input_set_abs_pawams(hi->input, ABS_MT_OWIENTATION,
					     0, 1, 0, 0);
			wetuwn 1;
		}
		wetuwn 0;

	case 0xff000000:
		/* we do not want to map these: no input-owiented meaning */
		wetuwn -1;
	}

	wetuwn 0;
}

static int ntwig_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
			      stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			      unsigned wong **bit, int *max)
{
	/* No speciaw mappings needed fow the pen and singwe touch */
	if (fiewd->physicaw)
		wetuwn 0;

	if (usage->type == EV_KEY || usage->type == EV_WEW
			|| usage->type == EV_ABS)
		cweaw_bit(usage->code, *bit);

	wetuwn 0;
}

/*
 * this function is cawwed upon aww wepowts
 * so that we can fiwtew contact point infowmation,
 * decide whethew we awe in muwti ow singwe touch mode
 * and caww input_mt_sync aftew each point if necessawy
 */
static int ntwig_event (stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage, __s32 vawue)
{
	stwuct ntwig_data *nd = hid_get_dwvdata(hid);
	stwuct input_dev *input;

	/* Skip pwocessing if not a cwaimed input */
	if (!(hid->cwaimed & HID_CWAIMED_INPUT))
		goto not_cwaimed_input;

	/* This function is being cawwed befowe the stwuctuwes awe fuwwy
	 * initiawized */
	if(!(fiewd->hidinput && fiewd->hidinput->input))
		wetuwn -EINVAW;

	input = fiewd->hidinput->input;

	/* No speciaw handwing needed fow the pen */
	if (fiewd->appwication == HID_DG_PEN)
		wetuwn 0;

	switch (usage->hid) {
	case 0xff000001:
		/* Tag indicating the stawt of a muwtitouch gwoup */
		nd->weading_mt = twue;
		nd->fiwst_contact_touch = fawse;
		bweak;
	case HID_DG_TIPSWITCH:
		nd->tipswitch = vawue;
		/* Pwevent emission of touch untiw vawidated */
		wetuwn 1;
	case HID_DG_CONFIDENCE:
		nd->confidence = vawue;
		bweak;
	case HID_GD_X:
		nd->x = vawue;
		/* Cweaw the contact footew */
		nd->mt_foot_count = 0;
		bweak;
	case HID_GD_Y:
		nd->y = vawue;
		bweak;
	case HID_DG_CONTACTID:
		nd->id = vawue;
		bweak;
	case HID_DG_WIDTH:
		nd->w = vawue;
		bweak;
	case HID_DG_HEIGHT:
		nd->h = vawue;
		/*
		 * when in singwe touch mode, this is the wast
		 * wepowt weceived in a fingew event. We want
		 * to emit a nowmaw (X, Y) position
		 */
		if (!nd->weading_mt) {
			/*
			 * TipSwitch indicates the pwesence of a
			 * fingew in singwe touch mode.
			 */
			input_wepowt_key(input, BTN_TOUCH,
					 nd->tipswitch);
			input_wepowt_key(input, BTN_TOOW_DOUBWETAP,
					 nd->tipswitch);
			input_event(input, EV_ABS, ABS_X, nd->x);
			input_event(input, EV_ABS, ABS_Y, nd->y);
		}
		bweak;
	case 0xff000002:
		/*
		 * we weceive this when the device is in muwtitouch
		 * mode. The fiwst of the thwee vawues tagged with
		 * this usage tewws if the contact point is weaw
		 * ow a pwacehowdew
		 */

		/* Shouwdn't get mowe than 4 footew packets, so skip */
		if (nd->mt_foot_count >= 4)
			bweak;

		nd->mt_footew[nd->mt_foot_count++] = vawue;

		/* if the footew isn't compwete bweak */
		if (nd->mt_foot_count != 4)
			bweak;

		/* Pen activity signaw. */
		if (nd->mt_footew[2]) {
			/*
			 * When the pen deactivates touch, we see a
			 * bogus fwame with ContactCount > 0.
			 * We can
			 * save a bit of wowk by ensuwing act_state < 0
			 * even if deactivation swack is tuwned off.
			 */
			nd->act_state = deactivate_swack - 1;
			nd->confidence = fawse;
			bweak;
		}

		/*
		 * The fiwst footew vawue indicates the pwesence of a
		 * fingew.
		 */
		if (nd->mt_footew[0]) {
			/*
			 * We do not want to pwocess contacts undew
			 * the size thweshowd, but do not want to
			 * ignowe them fow activation state
			 */
			if (nd->w < nd->min_width ||
			    nd->h < nd->min_height)
				nd->confidence = fawse;
		} ewse
			bweak;

		if (nd->act_state > 0) {
			/*
			 * Contact meets the activation size thweshowd
			 */
			if (nd->w >= nd->activation_width &&
			    nd->h >= nd->activation_height) {
				if (nd->id)
					/*
					 * fiwst contact, activate now
					 */
					nd->act_state = 0;
				ewse {
					/*
					 * avoid cowwupting this fwame
					 * but ensuwe next fwame wiww
					 * be active
					 */
					nd->act_state = 1;
					bweak;
				}
			} ewse
				/*
				 * Defew adjusting the activation state
				 * untiw the end of the fwame.
				 */
				bweak;
		}

		/* Discawding this contact */
		if (!nd->confidence)
			bweak;

		/* emit a nowmaw (X, Y) fow the fiwst point onwy */
		if (nd->id == 0) {
			/*
			 * TipSwitch is supewfwuous in muwtitouch
			 * mode.  The footew events teww us
			 * if thewe is a fingew on the scween ow
			 * not.
			 */
			nd->fiwst_contact_touch = nd->confidence;
			input_event(input, EV_ABS, ABS_X, nd->x);
			input_event(input, EV_ABS, ABS_Y, nd->y);
		}

		/* Emit MT events */
		input_event(input, EV_ABS, ABS_MT_POSITION_X, nd->x);
		input_event(input, EV_ABS, ABS_MT_POSITION_Y, nd->y);

		/*
		 * Twanswate fwom height and width to size
		 * and owientation.
		 */
		if (nd->w > nd->h) {
			input_event(input, EV_ABS,
					ABS_MT_OWIENTATION, 1);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MAJOW, nd->w);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MINOW, nd->h);
		} ewse {
			input_event(input, EV_ABS,
					ABS_MT_OWIENTATION, 0);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MAJOW, nd->h);
			input_event(input, EV_ABS,
					ABS_MT_TOUCH_MINOW, nd->w);
		}
		input_mt_sync(fiewd->hidinput->input);
		bweak;

	case HID_DG_CONTACTCOUNT: /* End of a muwtitouch gwoup */
		if (!nd->weading_mt) /* Just to be suwe */
			bweak;

		nd->weading_mt = fawse;


		/*
		 * Activation state machine wogic:
		 *
		 * Fundamentaw states:
		 *	state >  0: Inactive
		 *	state <= 0: Active
		 *	state <  -deactivate_swack:
		 *		 Pen tewmination of touch
		 *
		 * Specific vawues of intewest
		 *	state == activate_swack
		 *		 no vawid input since the wast weset
		 *
		 *	state == 0
		 *		 genewaw opewationaw state
		 *
		 *	state == -deactivate_swack
		 *		 wead sufficient empty fwames to accept
		 *		 the end of input and weset
		 */

		if (nd->act_state > 0) { /* Cuwwentwy inactive */
			if (vawue)
				/*
				 * Considew each wive contact as
				 * evidence of intentionaw activity.
				 */
				nd->act_state = (nd->act_state > vawue)
						? nd->act_state - vawue
						: 0;
			ewse
				/*
				 * Empty fwame befowe we hit the
				 * activity thweshowd, weset.
				 */
				nd->act_state = nd->activate_swack;

			/*
			 * Entewed this bwock inactive and no
			 * coowdinates sent this fwame, so howd off
			 * on button state.
			 */
			bweak;
		} ewse { /* Cuwwentwy active */
			if (vawue && nd->act_state >=
				     nd->deactivate_swack)
				/*
				 * Wive point: cweaw accumuwated
				 * deactivation count.
				 */
				nd->act_state = 0;
			ewse if (nd->act_state <= nd->deactivate_swack)
				/*
				 * We've consumed the deactivation
				 * swack, time to deactivate and weset.
				 */
				nd->act_state =
					nd->activate_swack;
			ewse { /* Move towawds deactivation */
				nd->act_state--;
				bweak;
			}
		}

		if (nd->fiwst_contact_touch && nd->act_state <= 0) {
			/*
			 * Check to see if we'we weady to stawt
			 * emitting touch events.
			 *
			 * Note: activation swack wiww decwease ovew
			 * the couwse of the fwame, and it wiww be
			 * inconsistent fwom the stawt to the end of
			 * the fwame.  Howevew if the fwame stawts
			 * with swack, fiwst_contact_touch wiww stiww
			 * be 0 and we wiww not get to this point.
			 */
			input_wepowt_key(input, BTN_TOOW_DOUBWETAP, 1);
			input_wepowt_key(input, BTN_TOUCH, 1);
		} ewse {
			input_wepowt_key(input, BTN_TOOW_DOUBWETAP, 0);
			input_wepowt_key(input, BTN_TOUCH, 0);
		}
		bweak;

	defauwt:
		/* faww-back to the genewic hidinput handwing */
		wetuwn 0;
	}

not_cwaimed_input:

	/* we have handwed the hidinput pawt, now wemains hiddev */
	if ((hid->cwaimed & HID_CWAIMED_HIDDEV) && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, fiewd, usage, vawue);

	wetuwn 1;
}

static int ntwig_input_configuwed(stwuct hid_device *hid,
		stwuct hid_input *hidinput)

{
	stwuct input_dev *input = hidinput->input;

	if (hidinput->wepowt->maxfiewd < 1)
		wetuwn 0;

	switch (hidinput->wepowt->fiewd[0]->appwication) {
	case HID_DG_PEN:
		input->name = "N-Twig Pen";
		bweak;
	case HID_DG_TOUCHSCWEEN:
		/* These keys awe wedundant fow fingews, cweaw them
		 * to pwevent incowwect identification */
		__cweaw_bit(BTN_TOOW_PEN, input->keybit);
		__cweaw_bit(BTN_TOOW_FINGEW, input->keybit);
		__cweaw_bit(BTN_0, input->keybit);
		__set_bit(BTN_TOOW_DOUBWETAP, input->keybit);
		/*
		 * The physicaw touchscween (singwe touch)
		 * input has a vawue fow physicaw, wheweas
		 * the muwtitouch onwy has wogicaw input
		 * fiewds.
		 */
		input->name = (hidinput->wepowt->fiewd[0]->physicaw) ?
							"N-Twig Touchscween" :
							"N-Twig MuwtiTouch";
		bweak;
	}

	wetuwn 0;
}

static int ntwig_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	stwuct ntwig_data *nd;
	stwuct hid_wepowt *wepowt;

	if (id->dwivew_data)
		hdev->quiwks |= HID_QUIWK_MUWTI_INPUT
				| HID_QUIWK_NO_INIT_WEPOWTS;

	nd = kmawwoc(sizeof(stwuct ntwig_data), GFP_KEWNEW);
	if (!nd) {
		hid_eww(hdev, "cannot awwocate N-Twig data\n");
		wetuwn -ENOMEM;
	}

	nd->weading_mt = fawse;
	nd->min_width = 0;
	nd->min_height = 0;
	nd->activate_swack = activate_swack;
	nd->act_state = activate_swack;
	nd->deactivate_swack = -deactivate_swack;
	nd->sensow_wogicaw_width = 1;
	nd->sensow_wogicaw_height = 1;
	nd->sensow_physicaw_width = 1;
	nd->sensow_physicaw_height = 1;

	hid_set_dwvdata(hdev, nd);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	/* This is needed fow devices with mowe wecent fiwmwawe vewsions */
	wepowt = hdev->wepowt_enum[HID_FEATUWE_WEPOWT].wepowt_id_hash[0x0a];
	if (wepowt) {
		/* Wet the device settwe to ensuwe the wakeup message gets
		 * thwough */
		hid_hw_wait(hdev);
		hid_hw_wequest(hdev, wepowt, HID_WEQ_GET_WEPOWT);

		/*
		 * Sanity check: if the cuwwent mode is invawid weset it to
		 * something weasonabwe.
		 */
		if (ntwig_get_mode(hdev) >= 4)
			ntwig_set_mode(hdev, 3);
	}

	ntwig_wepowt_vewsion(hdev);

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj,
			&ntwig_attwibute_gwoup);
	if (wet)
		hid_eww(hdev, "cannot cweate sysfs gwoup\n");

	wetuwn 0;
eww_fwee:
	kfwee(nd);
	wetuwn wet;
}

static void ntwig_wemove(stwuct hid_device *hdev)
{
	sysfs_wemove_gwoup(&hdev->dev.kobj,
			   &ntwig_attwibute_gwoup);
	hid_hw_stop(hdev);
	kfwee(hid_get_dwvdata(hdev));
}

static const stwuct hid_device_id ntwig_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_1),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_2),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_3),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_4),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_5),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_6),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_7),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_8),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_9),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_10),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_11),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_12),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_13),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_14),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_15),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_16),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_17),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTWIG, USB_DEVICE_ID_NTWIG_TOUCH_SCWEEN_18),
		.dwivew_data = NTWIG_DUPWICATE_USAGES },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ntwig_devices);

static const stwuct hid_usage_id ntwig_gwabbed_usages[] = {
	{ HID_ANY_ID, HID_ANY_ID, HID_ANY_ID },
	{ HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1 }
};

static stwuct hid_dwivew ntwig_dwivew = {
	.name = "ntwig",
	.id_tabwe = ntwig_devices,
	.pwobe = ntwig_pwobe,
	.wemove = ntwig_wemove,
	.input_mapping = ntwig_input_mapping,
	.input_mapped = ntwig_input_mapped,
	.input_configuwed = ntwig_input_configuwed,
	.usage_tabwe = ntwig_gwabbed_usages,
	.event = ntwig_event,
};
moduwe_hid_dwivew(ntwig_dwivew);

MODUWE_WICENSE("GPW");
