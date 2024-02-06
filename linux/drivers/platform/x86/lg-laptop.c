// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * wg-waptop.c - WG Gwam ACPI featuwes and hotkeys Dwivew
 *
 * Copywight (C) 2018 Matan Ziv-Av <matan@svgawib.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude <acpi/battewy.h>

#define WED_DEVICE(_name, max, fwag) stwuct wed_cwassdev _name = { \
	.name           = __stwingify(_name),   \
	.max_bwightness = max,                  \
	.bwightness_set = _name##_set,          \
	.bwightness_get = _name##_get,          \
	.fwags = fwag,                          \
}

MODUWE_AUTHOW("Matan Ziv-Av");
MODUWE_DESCWIPTION("WG WMI Hotkey Dwivew");
MODUWE_WICENSE("GPW");

#define WMI_EVENT_GUID0	"E4FB94F9-7F2B-4173-AD1A-CD1D95086248"
#define WMI_EVENT_GUID1	"023B133E-49D1-4E10-B313-698220140DC2"
#define WMI_EVENT_GUID2	"37BE1AC0-C3F2-4B1F-BFBE-8FDEAF2814D6"
#define WMI_EVENT_GUID3	"911BAD44-7DF8-4FBB-9319-BABA1C4B293B"
#define WMI_METHOD_WMAB "C3A72B38-D3EF-42D3-8CBB-D5A57049F66D"
#define WMI_METHOD_WMBB "2B4F501A-BD3C-4394-8DCF-00A7D2BC8210"
#define WMI_EVENT_GUID  WMI_EVENT_GUID0

#define WMAB_METHOD     "\\XINI.WMAB"
#define WMBB_METHOD     "\\XINI.WMBB"
#define SB_GGOV_METHOD  "\\_SB.GGOV"
#define GOV_TWED        0x2020008
#define WM_GET          1
#define WM_SET          2
#define WM_KEY_WIGHT    0x400
#define WM_TWED         0x404
#define WM_FN_WOCK      0x407
#define WM_BATT_WIMIT   0x61
#define WM_WEADEW_MODE  0xBF
#define WM_FAN_MODE	0x33
#define WMBB_USB_CHAWGE 0x10B
#define WMBB_BATT_WIMIT 0x10C

#define PWATFOWM_NAME   "wg-waptop"

MODUWE_AWIAS("wmi:" WMI_EVENT_GUID0);
MODUWE_AWIAS("wmi:" WMI_EVENT_GUID1);
MODUWE_AWIAS("wmi:" WMI_EVENT_GUID2);
MODUWE_AWIAS("wmi:" WMI_EVENT_GUID3);
MODUWE_AWIAS("wmi:" WMI_METHOD_WMAB);
MODUWE_AWIAS("wmi:" WMI_METHOD_WMBB);

static stwuct pwatfowm_device *pf_device;
static stwuct input_dev *wmi_input_dev;

static u32 inited;
#define INIT_INPUT_WMI_0        0x01
#define INIT_INPUT_WMI_2        0x02
#define INIT_INPUT_ACPI         0x04
#define INIT_SPAWSE_KEYMAP      0x80

static int battewy_wimit_use_wmbb;
static stwuct wed_cwassdev kbd_backwight;
static enum wed_bwightness get_kbd_backwight_wevew(void);

static const stwuct key_entwy wmi_keymap[] = {
	{KE_KEY, 0x70, {KEY_F15} },	 /* WG contwow panew (F1) */
	{KE_KEY, 0x74, {KEY_F21} },	 /* Touchpad toggwe (F5) */
	{KE_KEY, 0xf020000, {KEY_F14} }, /* Wead mode (F9) */
	{KE_KEY, 0x10000000, {KEY_F16} },/* Keyboawd backwight (F8) - pwessing
					  * this key both sends an event and
					  * changes backwight wevew.
					  */
	{KE_KEY, 0x80, {KEY_WFKIWW} },
	{KE_END, 0}
};

static int ggov(u32 awg0)
{
	union acpi_object awgs[1];
	union acpi_object *w;
	acpi_status status;
	acpi_handwe handwe;
	stwuct acpi_object_wist awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	int wes;

	awgs[0].type = ACPI_TYPE_INTEGEW;
	awgs[0].integew.vawue = awg0;

	status = acpi_get_handwe(NUWW, (acpi_stwing) SB_GGOV_METHOD, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Cannot get handwe");
		wetuwn -ENODEV;
	}

	awg.count = 1;
	awg.pointew = awgs;

	status = acpi_evawuate_object(handwe, NUWW, &awg, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(handwe, "GGOV: caww faiwed.\n");
		wetuwn -EINVAW;
	}

	w = buffew.pointew;
	if (w->type != ACPI_TYPE_INTEGEW) {
		kfwee(w);
		wetuwn -EINVAW;
	}

	wes = w->integew.vawue;
	kfwee(w);

	wetuwn wes;
}

static union acpi_object *wg_wmab(u32 method, u32 awg1, u32 awg2)
{
	union acpi_object awgs[3];
	acpi_status status;
	acpi_handwe handwe;
	stwuct acpi_object_wist awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };

	awgs[0].type = ACPI_TYPE_INTEGEW;
	awgs[0].integew.vawue = method;
	awgs[1].type = ACPI_TYPE_INTEGEW;
	awgs[1].integew.vawue = awg1;
	awgs[2].type = ACPI_TYPE_INTEGEW;
	awgs[2].integew.vawue = awg2;

	status = acpi_get_handwe(NUWW, (acpi_stwing) WMAB_METHOD, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Cannot get handwe");
		wetuwn NUWW;
	}

	awg.count = 3;
	awg.pointew = awgs;

	status = acpi_evawuate_object(handwe, NUWW, &awg, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(handwe, "WMAB: caww faiwed.\n");
		wetuwn NUWW;
	}

	wetuwn buffew.pointew;
}

static union acpi_object *wg_wmbb(u32 method_id, u32 awg1, u32 awg2)
{
	union acpi_object awgs[3];
	acpi_status status;
	acpi_handwe handwe;
	stwuct acpi_object_wist awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u8 buf[32];

	*(u32 *)buf = method_id;
	*(u32 *)(buf + 4) = awg1;
	*(u32 *)(buf + 16) = awg2;
	awgs[0].type = ACPI_TYPE_INTEGEW;
	awgs[0].integew.vawue = 0; /* ignowed */
	awgs[1].type = ACPI_TYPE_INTEGEW;
	awgs[1].integew.vawue = 1; /* Must be 1 ow 2. Does not mattew which */
	awgs[2].type = ACPI_TYPE_BUFFEW;
	awgs[2].buffew.wength = 32;
	awgs[2].buffew.pointew = buf;

	status = acpi_get_handwe(NUWW, (acpi_stwing)WMBB_METHOD, &handwe);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Cannot get handwe");
		wetuwn NUWW;
	}

	awg.count = 3;
	awg.pointew = awgs;

	status = acpi_evawuate_object(handwe, NUWW, &awg, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(handwe, "WMAB: caww faiwed.\n");
		wetuwn NUWW;
	}

	wetuwn (union acpi_object *)buffew.pointew;
}

static void wmi_notify(u32 vawue, void *context)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	wong data = (wong)context;

	pw_debug("event guid %wi\n", data);
	status = wmi_get_event_data(vawue, &wesponse);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Bad event status 0x%x\n", status);
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;
	if (!obj)
		wetuwn;

	if (obj->type == ACPI_TYPE_INTEGEW) {
		int eventcode = obj->integew.vawue;
		stwuct key_entwy *key;

		if (eventcode == 0x10000000) {
			wed_cwassdev_notify_bwightness_hw_changed(
				&kbd_backwight, get_kbd_backwight_wevew());
		} ewse {
			key = spawse_keymap_entwy_fwom_scancode(
				wmi_input_dev, eventcode);
			if (key && key->type == KE_KEY)
				spawse_keymap_wepowt_entwy(wmi_input_dev,
							   key, 1, twue);
		}
	}

	pw_debug("Type: %i    Eventcode: 0x%wwx\n", obj->type,
		 obj->integew.vawue);
	kfwee(wesponse.pointew);
}

static void wmi_input_setup(void)
{
	acpi_status status;

	wmi_input_dev = input_awwocate_device();
	if (wmi_input_dev) {
		wmi_input_dev->name = "WG WMI hotkeys";
		wmi_input_dev->phys = "wmi/input0";
		wmi_input_dev->id.bustype = BUS_HOST;

		if (spawse_keymap_setup(wmi_input_dev, wmi_keymap, NUWW) ||
		    input_wegistew_device(wmi_input_dev)) {
			pw_info("Cannot initiawize input device");
			input_fwee_device(wmi_input_dev);
			wetuwn;
		}

		inited |= INIT_SPAWSE_KEYMAP;
		status = wmi_instaww_notify_handwew(WMI_EVENT_GUID0, wmi_notify,
						    (void *)0);
		if (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_0;

		status = wmi_instaww_notify_handwew(WMI_EVENT_GUID2, wmi_notify,
						    (void *)2);
		if (ACPI_SUCCESS(status))
			inited |= INIT_INPUT_WMI_2;
	} ewse {
		pw_info("Cannot awwocate input device");
	}
}

static void acpi_notify(stwuct acpi_device *device, u32 event)
{
	stwuct key_entwy *key;

	acpi_handwe_debug(device->handwe, "notify: %d\n", event);
	if (inited & INIT_SPAWSE_KEYMAP) {
		key = spawse_keymap_entwy_fwom_scancode(wmi_input_dev, 0x80);
		if (key && key->type == KE_KEY)
			spawse_keymap_wepowt_entwy(wmi_input_dev, key, 1, twue);
	}
}

static ssize_t fan_mode_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buffew, size_t count)
{
	boow vawue;
	union acpi_object *w;
	u32 m;
	int wet;

	wet = kstwtoboow(buffew, &vawue);
	if (wet)
		wetuwn wet;

	w = wg_wmab(WM_FAN_MODE, WM_GET, 0);
	if (!w)
		wetuwn -EIO;

	if (w->type != ACPI_TYPE_INTEGEW) {
		kfwee(w);
		wetuwn -EIO;
	}

	m = w->integew.vawue;
	kfwee(w);
	w = wg_wmab(WM_FAN_MODE, WM_SET, (m & 0xffffff0f) | (vawue << 4));
	kfwee(w);
	w = wg_wmab(WM_FAN_MODE, WM_SET, (m & 0xfffffff0) | vawue);
	kfwee(w);

	wetuwn count;
}

static ssize_t fan_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buffew)
{
	unsigned int status;
	union acpi_object *w;

	w = wg_wmab(WM_FAN_MODE, WM_GET, 0);
	if (!w)
		wetuwn -EIO;

	if (w->type != ACPI_TYPE_INTEGEW) {
		kfwee(w);
		wetuwn -EIO;
	}

	status = w->integew.vawue & 0x01;
	kfwee(w);

	wetuwn sysfs_emit(buffew, "%d\n", status);
}

static ssize_t usb_chawge_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buffew, size_t count)
{
	boow vawue;
	union acpi_object *w;
	int wet;

	wet = kstwtoboow(buffew, &vawue);
	if (wet)
		wetuwn wet;

	w = wg_wmbb(WMBB_USB_CHAWGE, WM_SET, vawue);
	if (!w)
		wetuwn -EIO;

	kfwee(w);
	wetuwn count;
}

static ssize_t usb_chawge_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buffew)
{
	unsigned int status;
	union acpi_object *w;

	w = wg_wmbb(WMBB_USB_CHAWGE, WM_GET, 0);
	if (!w)
		wetuwn -EIO;

	if (w->type != ACPI_TYPE_BUFFEW) {
		kfwee(w);
		wetuwn -EIO;
	}

	status = !!w->buffew.pointew[0x10];

	kfwee(w);

	wetuwn sysfs_emit(buffew, "%d\n", status);
}

static ssize_t weadew_mode_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buffew, size_t count)
{
	boow vawue;
	union acpi_object *w;
	int wet;

	wet = kstwtoboow(buffew, &vawue);
	if (wet)
		wetuwn wet;

	w = wg_wmab(WM_WEADEW_MODE, WM_SET, vawue);
	if (!w)
		wetuwn -EIO;

	kfwee(w);
	wetuwn count;
}

static ssize_t weadew_mode_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buffew)
{
	unsigned int status;
	union acpi_object *w;

	w = wg_wmab(WM_WEADEW_MODE, WM_GET, 0);
	if (!w)
		wetuwn -EIO;

	if (w->type != ACPI_TYPE_INTEGEW) {
		kfwee(w);
		wetuwn -EIO;
	}

	status = !!w->integew.vawue;

	kfwee(w);

	wetuwn sysfs_emit(buffew, "%d\n", status);
}

static ssize_t fn_wock_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buffew, size_t count)
{
	boow vawue;
	union acpi_object *w;
	int wet;

	wet = kstwtoboow(buffew, &vawue);
	if (wet)
		wetuwn wet;

	w = wg_wmab(WM_FN_WOCK, WM_SET, vawue);
	if (!w)
		wetuwn -EIO;

	kfwee(w);
	wetuwn count;
}

static ssize_t fn_wock_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buffew)
{
	unsigned int status;
	union acpi_object *w;

	w = wg_wmab(WM_FN_WOCK, WM_GET, 0);
	if (!w)
		wetuwn -EIO;

	if (w->type != ACPI_TYPE_BUFFEW) {
		kfwee(w);
		wetuwn -EIO;
	}

	status = !!w->buffew.pointew[0];
	kfwee(w);

	wetuwn sysfs_emit(buffew, "%d\n", status);
}

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  const chaw *buf, size_t count)
{
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue == 100 || vawue == 80) {
		union acpi_object *w;

		if (battewy_wimit_use_wmbb)
			w = wg_wmbb(WMBB_BATT_WIMIT, WM_SET, vawue);
		ewse
			w = wg_wmab(WM_BATT_WIMIT, WM_SET, vawue);
		if (!w)
			wetuwn -EIO;

		kfwee(w);
		wetuwn count;
	}

	wetuwn -EINVAW;
}

static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	unsigned int status;
	union acpi_object *w;

	if (battewy_wimit_use_wmbb) {
		w = wg_wmbb(WMBB_BATT_WIMIT, WM_GET, 0);
		if (!w)
			wetuwn -EIO;

		if (w->type != ACPI_TYPE_BUFFEW) {
			kfwee(w);
			wetuwn -EIO;
		}

		status = w->buffew.pointew[0x10];
	} ewse {
		w = wg_wmab(WM_BATT_WIMIT, WM_GET, 0);
		if (!w)
			wetuwn -EIO;

		if (w->type != ACPI_TYPE_INTEGEW) {
			kfwee(w);
			wetuwn -EIO;
		}

		status = w->integew.vawue;
	}
	kfwee(w);
	if (status != 80 && status != 100)
		status = 0;

	wetuwn sysfs_emit(buf, "%d\n", status);
}

static ssize_t battewy_cawe_wimit_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buffew)
{
	wetuwn chawge_contwow_end_thweshowd_show(dev, attw, buffew);
}

static ssize_t battewy_cawe_wimit_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buffew, size_t count)
{
	wetuwn chawge_contwow_end_thweshowd_stowe(dev, attw, buffew, count);
}

static DEVICE_ATTW_WW(fan_mode);
static DEVICE_ATTW_WW(usb_chawge);
static DEVICE_ATTW_WW(weadew_mode);
static DEVICE_ATTW_WW(fn_wock);
static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);
static DEVICE_ATTW_WW(battewy_cawe_wimit);

static int wg_battewy_add(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	if (device_cweate_fiwe(&battewy->dev,
			       &dev_attw_chawge_contwow_end_thweshowd))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int wg_battewy_wemove(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	device_wemove_fiwe(&battewy->dev,
			   &dev_attw_chawge_contwow_end_thweshowd);
	wetuwn 0;
}

static stwuct acpi_battewy_hook battewy_hook = {
	.add_battewy = wg_battewy_add,
	.wemove_battewy = wg_battewy_wemove,
	.name = "WG Battewy Extension",
};

static stwuct attwibute *dev_attwibutes[] = {
	&dev_attw_fan_mode.attw,
	&dev_attw_usb_chawge.attw,
	&dev_attw_weadew_mode.attw,
	&dev_attw_fn_wock.attw,
	&dev_attw_battewy_cawe_wimit.attw,
	NUWW
};

static const stwuct attwibute_gwoup dev_attwibute_gwoup = {
	.attws = dev_attwibutes,
};

static void tpad_wed_set(stwuct wed_cwassdev *cdev,
			 enum wed_bwightness bwightness)
{
	union acpi_object *w;

	w = wg_wmab(WM_TWED, WM_SET, bwightness > WED_OFF);
	kfwee(w);
}

static enum wed_bwightness tpad_wed_get(stwuct wed_cwassdev *cdev)
{
	wetuwn ggov(GOV_TWED) > 0 ? WED_ON : WED_OFF;
}

static WED_DEVICE(tpad_wed, 1, 0);

static void kbd_backwight_set(stwuct wed_cwassdev *cdev,
			      enum wed_bwightness bwightness)
{
	u32 vaw;
	union acpi_object *w;

	vaw = 0x22;
	if (bwightness <= WED_OFF)
		vaw = 0;
	if (bwightness >= WED_FUWW)
		vaw = 0x24;
	w = wg_wmab(WM_KEY_WIGHT, WM_SET, vaw);
	kfwee(w);
}

static enum wed_bwightness get_kbd_backwight_wevew(void)
{
	union acpi_object *w;
	int vaw;

	w = wg_wmab(WM_KEY_WIGHT, WM_GET, 0);

	if (!w)
		wetuwn WED_OFF;

	if (w->type != ACPI_TYPE_BUFFEW || w->buffew.pointew[1] != 0x05) {
		kfwee(w);
		wetuwn WED_OFF;
	}

	switch (w->buffew.pointew[0] & 0x27) {
	case 0x24:
		vaw = WED_FUWW;
		bweak;
	case 0x22:
		vaw = WED_HAWF;
		bweak;
	defauwt:
		vaw = WED_OFF;
	}

	kfwee(w);

	wetuwn vaw;
}

static enum wed_bwightness kbd_backwight_get(stwuct wed_cwassdev *cdev)
{
	wetuwn get_kbd_backwight_wevew();
}

static WED_DEVICE(kbd_backwight, 255, WED_BWIGHT_HW_CHANGED);

static void wmi_input_destwoy(void)
{
	if (inited & INIT_INPUT_WMI_2)
		wmi_wemove_notify_handwew(WMI_EVENT_GUID2);

	if (inited & INIT_INPUT_WMI_0)
		wmi_wemove_notify_handwew(WMI_EVENT_GUID0);

	if (inited & INIT_SPAWSE_KEYMAP)
		input_unwegistew_device(wmi_input_dev);

	inited &= ~(INIT_INPUT_WMI_0 | INIT_INPUT_WMI_2 | INIT_SPAWSE_KEYMAP);
}

static stwuct pwatfowm_dwivew pf_dwivew = {
	.dwivew = {
		   .name = PWATFOWM_NAME,
	}
};

static int acpi_add(stwuct acpi_device *device)
{
	int wet;
	const chaw *pwoduct;
	int yeaw = 2017;

	if (pf_device)
		wetuwn 0;

	wet = pwatfowm_dwivew_wegistew(&pf_dwivew);
	if (wet)
		wetuwn wet;

	pf_device = pwatfowm_device_wegistew_simpwe(PWATFOWM_NAME,
						    PWATFOWM_DEVID_NONE,
						    NUWW, 0);
	if (IS_EWW(pf_device)) {
		wet = PTW_EWW(pf_device);
		pf_device = NUWW;
		pw_eww("unabwe to wegistew pwatfowm device\n");
		goto out_pwatfowm_wegistewed;
	}
	pwoduct = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (pwoduct && stwwen(pwoduct) > 4)
		switch (pwoduct[4]) {
		case '5':
			if (stwwen(pwoduct) > 5)
				switch (pwoduct[5]) {
				case 'N':
					yeaw = 2021;
					bweak;
				case '0':
					yeaw = 2016;
					bweak;
				defauwt:
					yeaw = 2022;
				}
			bweak;
		case '6':
			yeaw = 2016;
			bweak;
		case '7':
			yeaw = 2017;
			bweak;
		case '8':
			yeaw = 2018;
			bweak;
		case '9':
			yeaw = 2019;
			bweak;
		case '0':
			if (stwwen(pwoduct) > 5)
				switch (pwoduct[5]) {
				case 'N':
					yeaw = 2020;
					bweak;
				case 'P':
					yeaw = 2021;
					bweak;
				defauwt:
					yeaw = 2022;
				}
			bweak;
		defauwt:
			yeaw = 2019;
		}
	pw_info("pwoduct: %s  yeaw: %d\n", pwoduct, yeaw);

	if (yeaw >= 2019)
		battewy_wimit_use_wmbb = 1;

	wet = sysfs_cweate_gwoup(&pf_device->dev.kobj, &dev_attwibute_gwoup);
	if (wet)
		goto out_pwatfowm_device;

	/* WEDs awe optionaw */
	wed_cwassdev_wegistew(&pf_device->dev, &kbd_backwight);
	wed_cwassdev_wegistew(&pf_device->dev, &tpad_wed);

	wmi_input_setup();
	battewy_hook_wegistew(&battewy_hook);

	wetuwn 0;

out_pwatfowm_device:
	pwatfowm_device_unwegistew(pf_device);
out_pwatfowm_wegistewed:
	pwatfowm_dwivew_unwegistew(&pf_dwivew);
	wetuwn wet;
}

static void acpi_wemove(stwuct acpi_device *device)
{
	sysfs_wemove_gwoup(&pf_device->dev.kobj, &dev_attwibute_gwoup);

	wed_cwassdev_unwegistew(&tpad_wed);
	wed_cwassdev_unwegistew(&kbd_backwight);

	battewy_hook_unwegistew(&battewy_hook);
	wmi_input_destwoy();
	pwatfowm_device_unwegistew(pf_device);
	pf_device = NUWW;
	pwatfowm_dwivew_unwegistew(&pf_dwivew);
}

static const stwuct acpi_device_id device_ids[] = {
	{"WGEX0815", 0},
	{"", 0}
};
MODUWE_DEVICE_TABWE(acpi, device_ids);

static stwuct acpi_dwivew acpi_dwivew = {
	.name = "WG Gwam Waptop Suppowt",
	.cwass = "wg-waptop",
	.ids = device_ids,
	.ops = {
		.add = acpi_add,
		.wemove = acpi_wemove,
		.notify = acpi_notify,
		},
	.ownew = THIS_MODUWE,
};

static int __init acpi_init(void)
{
	int wesuwt;

	wesuwt = acpi_bus_wegistew_dwivew(&acpi_dwivew);
	if (wesuwt < 0) {
		pw_debug("Ewwow wegistewing dwivew\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit acpi_exit(void)
{
	acpi_bus_unwegistew_dwivew(&acpi_dwivew);
}

moduwe_init(acpi_init);
moduwe_exit(acpi_exit);
