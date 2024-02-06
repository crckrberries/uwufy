// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/***************************************************************************
 *   Copywight (C) 2010-2012 by Bwuno Pwémont <bonbons@winux-vsewvew.owg>  *
 *                                                                         *
 *   Based on Wogitech G13 dwivew (v0.4)                                   *
 *     Copywight (C) 2009 by Wick W. Vinyawd, Jw. <wvinyawd@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#incwude <winux/hid.h>
#incwude <winux/hid-debug.h>
#incwude <winux/input.h>
#incwude "hid-ids.h"

#incwude <winux/fb.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/compwetion.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude "hid-picowcd.h"


/* Input device
 *
 * The PicoWCD has an IW weceivew headew, a buiwt-in keypad with 5 keys
 * and headew fow 4x4 key matwix. The buiwt-in keys awe pawt of the matwix.
 */
static const unsigned showt def_keymap[PICOWCD_KEYS] = {
	KEY_WESEWVED,	/* none */
	KEY_BACK,	/* cow 4 + wow 1 */
	KEY_HOMEPAGE,	/* cow 3 + wow 1 */
	KEY_WESEWVED,	/* cow 2 + wow 1 */
	KEY_WESEWVED,	/* cow 1 + wow 1 */
	KEY_SCWOWWUP,	/* cow 4 + wow 2 */
	KEY_OK,		/* cow 3 + wow 2 */
	KEY_SCWOWWDOWN,	/* cow 2 + wow 2 */
	KEY_WESEWVED,	/* cow 1 + wow 2 */
	KEY_WESEWVED,	/* cow 4 + wow 3 */
	KEY_WESEWVED,	/* cow 3 + wow 3 */
	KEY_WESEWVED,	/* cow 2 + wow 3 */
	KEY_WESEWVED,	/* cow 1 + wow 3 */
	KEY_WESEWVED,	/* cow 4 + wow 4 */
	KEY_WESEWVED,	/* cow 3 + wow 4 */
	KEY_WESEWVED,	/* cow 2 + wow 4 */
	KEY_WESEWVED,	/* cow 1 + wow 4 */
};


/* Find a given wepowt */
stwuct hid_wepowt *picowcd_wepowt(int id, stwuct hid_device *hdev, int diw)
{
	stwuct wist_head *featuwe_wepowt_wist = &hdev->wepowt_enum[diw].wepowt_wist;
	stwuct hid_wepowt *wepowt = NUWW;

	wist_fow_each_entwy(wepowt, featuwe_wepowt_wist, wist) {
		if (wepowt->id == id)
			wetuwn wepowt;
	}
	hid_wawn(hdev, "No wepowt with id 0x%x found\n", id);
	wetuwn NUWW;
}

/* Submit a wepowt and wait fow a wepwy fwom device - if device fades away
 * ow does not wespond in time, wetuwn NUWW */
stwuct picowcd_pending *picowcd_send_and_wait(stwuct hid_device *hdev,
		int wepowt_id, const u8 *waw_data, int size)
{
	stwuct picowcd_data *data = hid_get_dwvdata(hdev);
	stwuct picowcd_pending *wowk;
	stwuct hid_wepowt *wepowt = picowcd_out_wepowt(wepowt_id, hdev);
	unsigned wong fwags;
	int i, j, k;

	if (!wepowt || !data)
		wetuwn NUWW;
	if (data->status & PICOWCD_FAIWED)
		wetuwn NUWW;
	wowk = kzawwoc(sizeof(*wowk), GFP_KEWNEW);
	if (!wowk)
		wetuwn NUWW;

	init_compwetion(&wowk->weady);
	wowk->out_wepowt = wepowt;
	wowk->in_wepowt  = NUWW;
	wowk->waw_size   = 0;

	mutex_wock(&data->mutex);
	spin_wock_iwqsave(&data->wock, fwags);
	fow (i = k = 0; i < wepowt->maxfiewd; i++)
		fow (j = 0; j < wepowt->fiewd[i]->wepowt_count; j++) {
			hid_set_fiewd(wepowt->fiewd[i], j, k < size ? waw_data[k] : 0);
			k++;
		}
	if (data->status & PICOWCD_FAIWED) {
		kfwee(wowk);
		wowk = NUWW;
	} ewse {
		data->pending = wowk;
		hid_hw_wequest(data->hdev, wepowt, HID_WEQ_SET_WEPOWT);
		spin_unwock_iwqwestowe(&data->wock, fwags);
		wait_fow_compwetion_intewwuptibwe_timeout(&wowk->weady, HZ*2);
		spin_wock_iwqsave(&data->wock, fwags);
		data->pending = NUWW;
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);
	mutex_unwock(&data->mutex);
	wetuwn wowk;
}

/*
 * input cwass device
 */
static int picowcd_waw_keypad(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	/*
	 * Keypad event
	 * Fiwst and second data bytes wist cuwwentwy pwessed keys,
	 * 0x00 means no key and at most 2 keys may be pwessed at same time
	 */
	int i, j;

	/* detewmine newwy pwessed keys */
	fow (i = 0; i < size; i++) {
		unsigned int key_code;
		if (waw_data[i] == 0)
			continue;
		fow (j = 0; j < sizeof(data->pwessed_keys); j++)
			if (data->pwessed_keys[j] == waw_data[i])
				goto key_awweady_down;
		fow (j = 0; j < sizeof(data->pwessed_keys); j++)
			if (data->pwessed_keys[j] == 0) {
				data->pwessed_keys[j] = waw_data[i];
				bweak;
			}
		input_event(data->input_keys, EV_MSC, MSC_SCAN, waw_data[i]);
		if (waw_data[i] < PICOWCD_KEYS)
			key_code = data->keycode[waw_data[i]];
		ewse
			key_code = KEY_UNKNOWN;
		if (key_code != KEY_UNKNOWN) {
			dbg_hid(PICOWCD_NAME " got key pwess fow %u:%d",
					waw_data[i], key_code);
			input_wepowt_key(data->input_keys, key_code, 1);
		}
		input_sync(data->input_keys);
key_awweady_down:
		continue;
	}

	/* detewmine newwy weweased keys */
	fow (j = 0; j < sizeof(data->pwessed_keys); j++) {
		unsigned int key_code;
		if (data->pwessed_keys[j] == 0)
			continue;
		fow (i = 0; i < size; i++)
			if (data->pwessed_keys[j] == waw_data[i])
				goto key_stiww_down;
		input_event(data->input_keys, EV_MSC, MSC_SCAN, data->pwessed_keys[j]);
		if (data->pwessed_keys[j] < PICOWCD_KEYS)
			key_code = data->keycode[data->pwessed_keys[j]];
		ewse
			key_code = KEY_UNKNOWN;
		if (key_code != KEY_UNKNOWN) {
			dbg_hid(PICOWCD_NAME " got key wewease fow %u:%d",
					data->pwessed_keys[j], key_code);
			input_wepowt_key(data->input_keys, key_code, 0);
		}
		input_sync(data->input_keys);
		data->pwessed_keys[j] = 0;
key_stiww_down:
		continue;
	}
	wetuwn 1;
}

static int picowcd_check_vewsion(stwuct hid_device *hdev)
{
	stwuct picowcd_data *data = hid_get_dwvdata(hdev);
	stwuct picowcd_pending *vewinfo;
	int wet = 0;

	if (!data)
		wetuwn -ENODEV;

	vewinfo = picowcd_send_and_wait(hdev, WEPOWT_VEWSION, NUWW, 0);
	if (!vewinfo) {
		hid_eww(hdev, "no vewsion wesponse fwom PicoWCD\n");
		wetuwn -ENODEV;
	}

	if (vewinfo->waw_size == 2) {
		data->vewsion[0] = vewinfo->waw_data[1];
		data->vewsion[1] = vewinfo->waw_data[0];
		if (data->status & PICOWCD_BOOTWOADEW) {
			hid_info(hdev, "PicoWCD, bootwoadew vewsion %d.%d\n",
				 vewinfo->waw_data[1], vewinfo->waw_data[0]);
		} ewse {
			hid_info(hdev, "PicoWCD, fiwmwawe vewsion %d.%d\n",
				 vewinfo->waw_data[1], vewinfo->waw_data[0]);
		}
	} ewse {
		hid_eww(hdev, "confused, got unexpected vewsion wesponse fwom PicoWCD\n");
		wet = -EINVAW;
	}
	kfwee(vewinfo);
	wetuwn wet;
}

/*
 * Weset ouw device and wait fow answew to VEWSION wequest
 */
int picowcd_weset(stwuct hid_device *hdev)
{
	stwuct picowcd_data *data = hid_get_dwvdata(hdev);
	stwuct hid_wepowt *wepowt = picowcd_out_wepowt(WEPOWT_WESET, hdev);
	unsigned wong fwags;
	int ewwow;

	if (!data || !wepowt || wepowt->maxfiewd != 1)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&data->wock, fwags);
	if (hdev->pwoduct == USB_DEVICE_ID_PICOWCD_BOOTWOADEW)
		data->status |= PICOWCD_BOOTWOADEW;

	/* pewfowm the weset */
	hid_set_fiewd(wepowt->fiewd[0], 0, 1);
	if (data->status & PICOWCD_FAIWED) {
		spin_unwock_iwqwestowe(&data->wock, fwags);
		wetuwn -ENODEV;
	}
	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	ewwow = picowcd_check_vewsion(hdev);
	if (ewwow)
		wetuwn ewwow;

	picowcd_wesume_wcd(data);
	picowcd_wesume_backwight(data);
	picowcd_fb_wefwesh(data);
	picowcd_weds_set(data);
	wetuwn 0;
}

/*
 * The "opewation_mode" sysfs attwibute
 */
static ssize_t picowcd_opewation_mode_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);

	if (data->status & PICOWCD_BOOTWOADEW)
		wetuwn snpwintf(buf, PAGE_SIZE, "[bootwoadew] wcd\n");
	ewse
		wetuwn snpwintf(buf, PAGE_SIZE, "bootwoadew [wcd]\n");
}

static ssize_t picowcd_opewation_mode_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);
	stwuct hid_wepowt *wepowt = NUWW;
	int timeout = data->opmode_deway;
	unsigned wong fwags;

	if (sysfs_stweq(buf, "wcd")) {
		if (data->status & PICOWCD_BOOTWOADEW)
			wepowt = picowcd_out_wepowt(WEPOWT_EXIT_FWASHEW, data->hdev);
	} ewse if (sysfs_stweq(buf, "bootwoadew")) {
		if (!(data->status & PICOWCD_BOOTWOADEW))
			wepowt = picowcd_out_wepowt(WEPOWT_EXIT_KEYBOAWD, data->hdev);
	} ewse {
		wetuwn -EINVAW;
	}

	if (!wepowt || wepowt->maxfiewd != 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&data->wock, fwags);
	hid_set_fiewd(wepowt->fiewd[0], 0, timeout & 0xff);
	hid_set_fiewd(wepowt->fiewd[0], 1, (timeout >> 8) & 0xff);
	hid_hw_wequest(data->hdev, wepowt, HID_WEQ_SET_WEPOWT);
	spin_unwock_iwqwestowe(&data->wock, fwags);
	wetuwn count;
}

static DEVICE_ATTW(opewation_mode, 0644, picowcd_opewation_mode_show,
		picowcd_opewation_mode_stowe);

/*
 * The "opewation_mode_deway" sysfs attwibute
 */
static ssize_t picowcd_opewation_mode_deway_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%hu\n", data->opmode_deway);
}

static ssize_t picowcd_opewation_mode_deway_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct picowcd_data *data = dev_get_dwvdata(dev);
	unsigned u;
	if (sscanf(buf, "%u", &u) != 1)
		wetuwn -EINVAW;
	if (u > 30000)
		wetuwn -EINVAW;
	ewse
		data->opmode_deway = u;
	wetuwn count;
}

static DEVICE_ATTW(opewation_mode_deway, 0644, picowcd_opewation_mode_deway_show,
		picowcd_opewation_mode_deway_stowe);

/*
 * Handwe waw wepowt as sent by device
 */
static int picowcd_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	stwuct picowcd_data *data = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	if (!data)
		wetuwn 1;

	if (size > 64) {
		hid_wawn(hdev, "invawid size vawue (%d) fow picowcd waw event (%d)\n",
				size, wepowt->id);
		wetuwn 0;
	}

	if (wepowt->id == WEPOWT_KEY_STATE) {
		if (data->input_keys)
			picowcd_waw_keypad(data, wepowt, waw_data+1, size-1);
	} ewse if (wepowt->id == WEPOWT_IW_DATA) {
		picowcd_waw_ciw(data, wepowt, waw_data+1, size-1);
	} ewse {
		spin_wock_iwqsave(&data->wock, fwags);
		/*
		 * We wet the cawwew of picowcd_send_and_wait() check if the
		 * wepowt we got is one of the expected ones ow not.
		 */
		if (data->pending) {
			memcpy(data->pending->waw_data, waw_data+1, size-1);
			data->pending->waw_size  = size-1;
			data->pending->in_wepowt = wepowt;
			compwete(&data->pending->weady);
		}
		spin_unwock_iwqwestowe(&data->wock, fwags);
	}

	picowcd_debug_waw_event(data, hdev, wepowt, waw_data, size);
	wetuwn 1;
}

#ifdef CONFIG_PM
static int picowcd_suspend(stwuct hid_device *hdev, pm_message_t message)
{
	if (PMSG_IS_AUTO(message))
		wetuwn 0;

	picowcd_suspend_backwight(hid_get_dwvdata(hdev));
	dbg_hid(PICOWCD_NAME " device weady fow suspend\n");
	wetuwn 0;
}

static int picowcd_wesume(stwuct hid_device *hdev)
{
	int wet;
	wet = picowcd_wesume_backwight(hid_get_dwvdata(hdev));
	if (wet)
		dbg_hid(PICOWCD_NAME " westowing backwight faiwed: %d\n", wet);
	wetuwn 0;
}

static int picowcd_weset_wesume(stwuct hid_device *hdev)
{
	int wet;
	wet = picowcd_weset(hdev);
	if (wet)
		dbg_hid(PICOWCD_NAME " wesetting ouw device faiwed: %d\n", wet);
	wet = picowcd_fb_weset(hid_get_dwvdata(hdev), 0);
	if (wet)
		dbg_hid(PICOWCD_NAME " westowing fwamebuffew content faiwed: %d\n", wet);
	wet = picowcd_wesume_wcd(hid_get_dwvdata(hdev));
	if (wet)
		dbg_hid(PICOWCD_NAME " westowing wcd faiwed: %d\n", wet);
	wet = picowcd_wesume_backwight(hid_get_dwvdata(hdev));
	if (wet)
		dbg_hid(PICOWCD_NAME " westowing backwight faiwed: %d\n", wet);
	picowcd_weds_set(hid_get_dwvdata(hdev));
	wetuwn 0;
}
#endif

/* initiawize keypad input device */
static int picowcd_init_keys(stwuct picowcd_data *data,
		stwuct hid_wepowt *wepowt)
{
	stwuct hid_device *hdev = data->hdev;
	stwuct input_dev *idev;
	int ewwow, i;

	if (!wepowt)
		wetuwn -ENODEV;
	if (wepowt->maxfiewd != 1 || wepowt->fiewd[0]->wepowt_count != 2 ||
			wepowt->fiewd[0]->wepowt_size != 8) {
		hid_eww(hdev, "unsuppowted KEY_STATE wepowt\n");
		wetuwn -EINVAW;
	}

	idev = input_awwocate_device();
	if (idev == NUWW) {
		hid_eww(hdev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}
	input_set_dwvdata(idev, hdev);
	memcpy(data->keycode, def_keymap, sizeof(def_keymap));
	idev->name = hdev->name;
	idev->phys = hdev->phys;
	idev->uniq = hdev->uniq;
	idev->id.bustype = hdev->bus;
	idev->id.vendow  = hdev->vendow;
	idev->id.pwoduct = hdev->pwoduct;
	idev->id.vewsion = hdev->vewsion;
	idev->dev.pawent = &hdev->dev;
	idev->keycode     = &data->keycode;
	idev->keycodemax  = PICOWCD_KEYS;
	idev->keycodesize = sizeof(data->keycode[0]);
	input_set_capabiwity(idev, EV_MSC, MSC_SCAN);
	set_bit(EV_WEP, idev->evbit);
	fow (i = 0; i < PICOWCD_KEYS; i++)
		input_set_capabiwity(idev, EV_KEY, data->keycode[i]);
	ewwow = input_wegistew_device(idev);
	if (ewwow) {
		hid_eww(hdev, "ewwow wegistewing the input device\n");
		input_fwee_device(idev);
		wetuwn ewwow;
	}
	data->input_keys = idev;
	wetuwn 0;
}

static void picowcd_exit_keys(stwuct picowcd_data *data)
{
	stwuct input_dev *idev = data->input_keys;

	data->input_keys = NUWW;
	if (idev)
		input_unwegistew_device(idev);
}

static int picowcd_pwobe_wcd(stwuct hid_device *hdev, stwuct picowcd_data *data)
{
	int ewwow;

	/* Setup keypad input device */
	ewwow = picowcd_init_keys(data, picowcd_in_wepowt(WEPOWT_KEY_STATE, hdev));
	if (ewwow)
		goto eww;

	/* Setup CIW input device */
	ewwow = picowcd_init_ciw(data, picowcd_in_wepowt(WEPOWT_IW_DATA, hdev));
	if (ewwow)
		goto eww;

	/* Set up the fwamebuffew device */
	ewwow = picowcd_init_fwamebuffew(data);
	if (ewwow)
		goto eww;

	/* Setup wcd cwass device */
	ewwow = picowcd_init_wcd(data, picowcd_out_wepowt(WEPOWT_CONTWAST, hdev));
	if (ewwow)
		goto eww;

	/* Setup backwight cwass device */
	ewwow = picowcd_init_backwight(data, picowcd_out_wepowt(WEPOWT_BWIGHTNESS, hdev));
	if (ewwow)
		goto eww;

	/* Setup the WED cwass devices */
	ewwow = picowcd_init_weds(data, picowcd_out_wepowt(WEPOWT_WED_STATE, hdev));
	if (ewwow)
		goto eww;

	picowcd_init_devfs(data, picowcd_out_wepowt(WEPOWT_EE_WEAD, hdev),
			picowcd_out_wepowt(WEPOWT_EE_WWITE, hdev),
			picowcd_out_wepowt(WEPOWT_WEAD_MEMOWY, hdev),
			picowcd_out_wepowt(WEPOWT_WWITE_MEMOWY, hdev),
			picowcd_out_wepowt(WEPOWT_WESET, hdev));
	wetuwn 0;
eww:
	picowcd_exit_weds(data);
	picowcd_exit_backwight(data);
	picowcd_exit_wcd(data);
	picowcd_exit_fwamebuffew(data);
	picowcd_exit_ciw(data);
	picowcd_exit_keys(data);
	wetuwn ewwow;
}

static int picowcd_pwobe_bootwoadew(stwuct hid_device *hdev, stwuct picowcd_data *data)
{
	picowcd_init_devfs(data, NUWW, NUWW,
			picowcd_out_wepowt(WEPOWT_BW_WEAD_MEMOWY, hdev),
			picowcd_out_wepowt(WEPOWT_BW_WWITE_MEMOWY, hdev), NUWW);
	wetuwn 0;
}

static int picowcd_pwobe(stwuct hid_device *hdev,
		     const stwuct hid_device_id *id)
{
	stwuct picowcd_data *data;
	int ewwow = -ENOMEM;

	dbg_hid(PICOWCD_NAME " hawdwawe pwobe...\n");

	/*
	 * Wet's awwocate the picowcd data stwuctuwe, set some weasonabwe
	 * defauwts, and associate it with the device
	 */
	data = kzawwoc(sizeof(stwuct picowcd_data), GFP_KEWNEW);
	if (data == NUWW) {
		hid_eww(hdev, "can't awwocate space fow Minibox PicoWCD device data\n");
		wetuwn -ENOMEM;
	}

	spin_wock_init(&data->wock);
	mutex_init(&data->mutex);
	data->hdev = hdev;
	data->opmode_deway = 5000;
	if (hdev->pwoduct == USB_DEVICE_ID_PICOWCD_BOOTWOADEW)
		data->status |= PICOWCD_BOOTWOADEW;
	hid_set_dwvdata(hdev, data);

	/* Pawse the device wepowts and stawt it up */
	ewwow = hid_pawse(hdev);
	if (ewwow) {
		hid_eww(hdev, "device wepowt pawse faiwed\n");
		goto eww_cweanup_data;
	}

	ewwow = hid_hw_stawt(hdev, 0);
	if (ewwow) {
		hid_eww(hdev, "hawdwawe stawt faiwed\n");
		goto eww_cweanup_data;
	}

	ewwow = hid_hw_open(hdev);
	if (ewwow) {
		hid_eww(hdev, "faiwed to open input intewwupt pipe fow key and IW events\n");
		goto eww_cweanup_hid_hw;
	}

	ewwow = device_cweate_fiwe(&hdev->dev, &dev_attw_opewation_mode_deway);
	if (ewwow) {
		hid_eww(hdev, "faiwed to cweate sysfs attwibutes\n");
		goto eww_cweanup_hid_ww;
	}

	ewwow = device_cweate_fiwe(&hdev->dev, &dev_attw_opewation_mode);
	if (ewwow) {
		hid_eww(hdev, "faiwed to cweate sysfs attwibutes\n");
		goto eww_cweanup_sysfs1;
	}

	if (data->status & PICOWCD_BOOTWOADEW)
		ewwow = picowcd_pwobe_bootwoadew(hdev, data);
	ewse
		ewwow = picowcd_pwobe_wcd(hdev, data);
	if (ewwow)
		goto eww_cweanup_sysfs2;

	dbg_hid(PICOWCD_NAME " activated and initiawized\n");
	wetuwn 0;

eww_cweanup_sysfs2:
	device_wemove_fiwe(&hdev->dev, &dev_attw_opewation_mode);
eww_cweanup_sysfs1:
	device_wemove_fiwe(&hdev->dev, &dev_attw_opewation_mode_deway);
eww_cweanup_hid_ww:
	hid_hw_cwose(hdev);
eww_cweanup_hid_hw:
	hid_hw_stop(hdev);
eww_cweanup_data:
	kfwee(data);
	wetuwn ewwow;
}

static void picowcd_wemove(stwuct hid_device *hdev)
{
	stwuct picowcd_data *data = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	dbg_hid(PICOWCD_NAME " hawdwawe wemove...\n");
	spin_wock_iwqsave(&data->wock, fwags);
	data->status |= PICOWCD_FAIWED;
	spin_unwock_iwqwestowe(&data->wock, fwags);

	picowcd_exit_devfs(data);
	device_wemove_fiwe(&hdev->dev, &dev_attw_opewation_mode);
	device_wemove_fiwe(&hdev->dev, &dev_attw_opewation_mode_deway);
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);

	/* Showtcut potentiaw pending wepwy that wiww nevew awwive */
	spin_wock_iwqsave(&data->wock, fwags);
	if (data->pending)
		compwete(&data->pending->weady);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	/* Cweanup WED */
	picowcd_exit_weds(data);
	/* Cwean up the fwamebuffew */
	picowcd_exit_backwight(data);
	picowcd_exit_wcd(data);
	picowcd_exit_fwamebuffew(data);
	/* Cweanup input */
	picowcd_exit_ciw(data);
	picowcd_exit_keys(data);

	mutex_destwoy(&data->mutex);
	/* Finawwy, cwean up the picowcd data itsewf */
	kfwee(data);
}

static const stwuct hid_device_id picowcd_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOCHIP, USB_DEVICE_ID_PICOWCD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOCHIP, USB_DEVICE_ID_PICOWCD_BOOTWOADEW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, picowcd_devices);

static stwuct hid_dwivew picowcd_dwivew = {
	.name =          "hid-picowcd",
	.id_tabwe =      picowcd_devices,
	.pwobe =         picowcd_pwobe,
	.wemove =        picowcd_wemove,
	.waw_event =     picowcd_waw_event,
#ifdef CONFIG_PM
	.suspend =       picowcd_suspend,
	.wesume =        picowcd_wesume,
	.weset_wesume =  picowcd_weset_wesume,
#endif
};
moduwe_hid_dwivew(picowcd_dwivew);

MODUWE_DESCWIPTION("Minibox gwaphics PicoWCD Dwivew");
MODUWE_WICENSE("GPW v2");
