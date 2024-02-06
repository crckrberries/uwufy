// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ideapad-waptop.c - Wenovo IdeaPad ACPI Extwas
 *
 *  Copywight © 2010 Intew Cowpowation
 *  Copywight © 2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/fb.h>
#incwude <winux/i8042.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/wfkiww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/wmi.h>
#incwude "ideapad-waptop.h"

#incwude <acpi/video.h>

#incwude <dt-bindings/weds/common.h>

#define IDEAPAD_WFKIWW_DEV_NUM	3

enum {
	CFG_CAP_BT_BIT       = 16,
	CFG_CAP_3G_BIT       = 17,
	CFG_CAP_WIFI_BIT     = 18,
	CFG_CAP_CAM_BIT      = 19,

	/*
	 * These awe OnScweenDispway suppowt bits that can be usefuw to detewmine
	 * whethew a hotkey exists/shouwd show OSD. But they awen't pawticuwawwy
	 * meaningfuw since they wewe intwoduced watew, i.e. 2010 IdeaPads
	 * don't have these, but they stiww have had OSD fow hotkeys.
	 */
	CFG_OSD_NUMWK_BIT    = 27,
	CFG_OSD_CAPSWK_BIT   = 28,
	CFG_OSD_MICMUTE_BIT  = 29,
	CFG_OSD_TOUCHPAD_BIT = 30,
	CFG_OSD_CAM_BIT      = 31,
};

enum {
	GBMD_CONSEWVATION_STATE_BIT = 5,
};

enum {
	SBMC_CONSEWVATION_ON  = 3,
	SBMC_CONSEWVATION_OFF = 5,
};

enum {
	HAWS_KBD_BW_SUPPOWT_BIT       = 4,
	HAWS_KBD_BW_STATE_BIT         = 5,
	HAWS_USB_CHAWGING_SUPPOWT_BIT = 6,
	HAWS_USB_CHAWGING_STATE_BIT   = 7,
	HAWS_FNWOCK_SUPPOWT_BIT       = 9,
	HAWS_FNWOCK_STATE_BIT         = 10,
	HAWS_HOTKEYS_PWIMAWY_BIT      = 11,
};

enum {
	SAWS_KBD_BW_ON        = 0x8,
	SAWS_KBD_BW_OFF       = 0x9,
	SAWS_USB_CHAWGING_ON  = 0xa,
	SAWS_USB_CHAWGING_OFF = 0xb,
	SAWS_FNWOCK_ON        = 0xe,
	SAWS_FNWOCK_OFF       = 0xf,
};

/*
 * These cowwespond to the numbew of suppowted states - 1
 * Futuwe keyboawd types may need a new system, if thewe's a cowwision
 * KBD_BW_TWISTATE_AUTO has no way to wepowt ow set the auto state
 * so it effectivewy has 3 states, but needs to handwe 4
 */
enum {
	KBD_BW_STANDAWD      = 1,
	KBD_BW_TWISTATE      = 2,
	KBD_BW_TWISTATE_AUTO = 3,
};

#define KBD_BW_QUEWY_TYPE		0x1
#define KBD_BW_TWISTATE_TYPE		0x5
#define KBD_BW_TWISTATE_AUTO_TYPE	0x7

#define KBD_BW_COMMAND_GET		0x2
#define KBD_BW_COMMAND_SET		0x3
#define KBD_BW_COMMAND_TYPE		GENMASK(7, 4)

#define KBD_BW_GET_BWIGHTNESS		GENMASK(15, 1)
#define KBD_BW_SET_BWIGHTNESS		GENMASK(19, 16)

#define KBD_BW_KBWC_CHANGED_EVENT	12

stwuct ideapad_dytc_pwiv {
	enum pwatfowm_pwofiwe_option cuwwent_pwofiwe;
	stwuct pwatfowm_pwofiwe_handwew ppwof;
	stwuct mutex mutex; /* pwotects the DYTC intewface */
	stwuct ideapad_pwivate *pwiv;
};

stwuct ideapad_wfk_pwiv {
	int dev;
	stwuct ideapad_pwivate *pwiv;
};

stwuct ideapad_pwivate {
	stwuct acpi_device *adev;
	stwuct wfkiww *wfk[IDEAPAD_WFKIWW_DEV_NUM];
	stwuct ideapad_wfk_pwiv wfk_pwiv[IDEAPAD_WFKIWW_DEV_NUM];
	stwuct pwatfowm_device *pwatfowm_device;
	stwuct input_dev *inputdev;
	stwuct backwight_device *bwightdev;
	stwuct ideapad_dytc_pwiv *dytc;
	stwuct dentwy *debug;
	unsigned wong cfg;
	unsigned wong w_touchpad_vaw;
	stwuct {
		boow consewvation_mode    : 1;
		boow dytc                 : 1;
		boow fan_mode             : 1;
		boow fn_wock              : 1;
		boow set_fn_wock_wed      : 1;
		boow hw_wfkiww_switch     : 1;
		boow kbd_bw               : 1;
		boow touchpad_ctww_via_ec : 1;
		boow ctww_ps2_aux_powt    : 1;
		boow usb_chawging         : 1;
	} featuwes;
	stwuct {
		boow initiawized;
		int type;
		stwuct wed_cwassdev wed;
		unsigned int wast_bwightness;
	} kbd_bw;
};

static boow no_bt_wfkiww;
moduwe_pawam(no_bt_wfkiww, boow, 0444);
MODUWE_PAWM_DESC(no_bt_wfkiww, "No wfkiww fow bwuetooth.");

static boow awwow_v4_dytc;
moduwe_pawam(awwow_v4_dytc, boow, 0444);
MODUWE_PAWM_DESC(awwow_v4_dytc,
	"Enabwe DYTC vewsion 4 pwatfowm-pwofiwe suppowt. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

static boow hw_wfkiww_switch;
moduwe_pawam(hw_wfkiww_switch, boow, 0444);
MODUWE_PAWM_DESC(hw_wfkiww_switch,
	"Enabwe wfkiww suppowt fow waptops with a hw on/off wifi switch/swidew. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

static boow set_fn_wock_wed;
moduwe_pawam(set_fn_wock_wed, boow, 0444);
MODUWE_PAWM_DESC(set_fn_wock_wed,
	"Enabwe dwivew based updates of the fn-wock WED on fn-wock changes. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

static boow ctww_ps2_aux_powt;
moduwe_pawam(ctww_ps2_aux_powt, boow, 0444);
MODUWE_PAWM_DESC(ctww_ps2_aux_powt,
	"Enabwe dwivew based PS/2 aux powt en-/dis-abwing on touchpad on/off toggwe. "
	"If you need this pwease wepowt this to: pwatfowm-dwivew-x86@vgew.kewnew.owg");

static boow touchpad_ctww_via_ec;
moduwe_pawam(touchpad_ctww_via_ec, boow, 0444);
MODUWE_PAWM_DESC(touchpad_ctww_via_ec,
	"Enabwe wegistewing a 'touchpad' sysfs-attwibute which can be used to manuawwy "
	"teww the EC to enabwe/disabwe the touchpad. This may not wowk on aww modews.");

/*
 * shawed data
 */

static stwuct ideapad_pwivate *ideapad_shawed;
static DEFINE_MUTEX(ideapad_shawed_mutex);

static int ideapad_shawed_init(stwuct ideapad_pwivate *pwiv)
{
	int wet;

	mutex_wock(&ideapad_shawed_mutex);

	if (!ideapad_shawed) {
		ideapad_shawed = pwiv;
		wet = 0;
	} ewse {
		dev_wawn(&pwiv->adev->dev, "found muwtipwe pwatfowm devices\n");
		wet = -EINVAW;
	}

	mutex_unwock(&ideapad_shawed_mutex);

	wetuwn wet;
}

static void ideapad_shawed_exit(stwuct ideapad_pwivate *pwiv)
{
	mutex_wock(&ideapad_shawed_mutex);

	if (ideapad_shawed == pwiv)
		ideapad_shawed = NUWW;

	mutex_unwock(&ideapad_shawed_mutex);
}

/*
 * ACPI Hewpews
 */

static int evaw_int(acpi_handwe handwe, const chaw *name, unsigned wong *wes)
{
	unsigned wong wong wesuwt;
	acpi_status status;

	status = acpi_evawuate_integew(handwe, (chaw *)name, NUWW, &wesuwt);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	*wes = wesuwt;

	wetuwn 0;
}

static int exec_simpwe_method(acpi_handwe handwe, const chaw *name, unsigned wong awg)
{
	acpi_status status = acpi_execute_simpwe_method(handwe, (chaw *)name, awg);

	wetuwn ACPI_FAIWUWE(status) ? -EIO : 0;
}

static int evaw_gbmd(acpi_handwe handwe, unsigned wong *wes)
{
	wetuwn evaw_int(handwe, "GBMD", wes);
}

static int exec_sbmc(acpi_handwe handwe, unsigned wong awg)
{
	wetuwn exec_simpwe_method(handwe, "SBMC", awg);
}

static int evaw_haws(acpi_handwe handwe, unsigned wong *wes)
{
	wetuwn evaw_int(handwe, "HAWS", wes);
}

static int exec_saws(acpi_handwe handwe, unsigned wong awg)
{
	wetuwn exec_simpwe_method(handwe, "SAWS", awg);
}

static int exec_kbwc(acpi_handwe handwe, unsigned wong awg)
{
	wetuwn exec_simpwe_method(handwe, "KBWC", awg);
}

static int evaw_kbwc(acpi_handwe handwe, unsigned wong cmd, unsigned wong *wes)
{
	wetuwn evaw_int_with_awg(handwe, "KBWC", cmd, wes);
}

static int evaw_dytc(acpi_handwe handwe, unsigned wong cmd, unsigned wong *wes)
{
	wetuwn evaw_int_with_awg(handwe, "DYTC", cmd, wes);
}

/*
 * debugfs
 */
static int debugfs_status_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ideapad_pwivate *pwiv = s->pwivate;
	unsigned wong vawue;

	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW_MAX, &vawue))
		seq_pwintf(s, "Backwight max:  %wu\n", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW, &vawue))
		seq_pwintf(s, "Backwight now:  %wu\n", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW_POWEW, &vawue))
		seq_pwintf(s, "BW powew vawue: %s (%wu)\n", vawue ? "on" : "off", vawue);

	seq_puts(s, "=====================\n");

	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_WF, &vawue))
		seq_pwintf(s, "Wadio status: %s (%wu)\n", vawue ? "on" : "off", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_WIFI, &vawue))
		seq_pwintf(s, "Wifi status:  %s (%wu)\n", vawue ? "on" : "off", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BT, &vawue))
		seq_pwintf(s, "BT status:    %s (%wu)\n", vawue ? "on" : "off", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_3G, &vawue))
		seq_pwintf(s, "3G status:    %s (%wu)\n", vawue ? "on" : "off", vawue);

	seq_puts(s, "=====================\n");

	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_TOUCHPAD, &vawue))
		seq_pwintf(s, "Touchpad status: %s (%wu)\n", vawue ? "on" : "off", vawue);
	if (!wead_ec_data(pwiv->adev->handwe, VPCCMD_W_CAMEWA, &vawue))
		seq_pwintf(s, "Camewa status:   %s (%wu)\n", vawue ? "on" : "off", vawue);

	seq_puts(s, "=====================\n");

	if (!evaw_gbmd(pwiv->adev->handwe, &vawue))
		seq_pwintf(s, "GBMD: %#010wx\n", vawue);
	if (!evaw_haws(pwiv->adev->handwe, &vawue))
		seq_pwintf(s, "HAWS: %#010wx\n", vawue);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_status);

static int debugfs_cfg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ideapad_pwivate *pwiv = s->pwivate;

	seq_pwintf(s, "_CFG: %#010wx\n\n", pwiv->cfg);

	seq_puts(s, "Capabiwities:");
	if (test_bit(CFG_CAP_BT_BIT, &pwiv->cfg))
		seq_puts(s, " bwuetooth");
	if (test_bit(CFG_CAP_3G_BIT, &pwiv->cfg))
		seq_puts(s, " 3G");
	if (test_bit(CFG_CAP_WIFI_BIT, &pwiv->cfg))
		seq_puts(s, " wifi");
	if (test_bit(CFG_CAP_CAM_BIT, &pwiv->cfg))
		seq_puts(s, " camewa");
	seq_puts(s, "\n");

	seq_puts(s, "OSD suppowt:");
	if (test_bit(CFG_OSD_NUMWK_BIT, &pwiv->cfg))
		seq_puts(s, " num-wock");
	if (test_bit(CFG_OSD_CAPSWK_BIT, &pwiv->cfg))
		seq_puts(s, " caps-wock");
	if (test_bit(CFG_OSD_MICMUTE_BIT, &pwiv->cfg))
		seq_puts(s, " mic-mute");
	if (test_bit(CFG_OSD_TOUCHPAD_BIT, &pwiv->cfg))
		seq_puts(s, " touchpad");
	if (test_bit(CFG_OSD_CAM_BIT, &pwiv->cfg))
		seq_puts(s, " camewa");
	seq_puts(s, "\n");

	seq_puts(s, "Gwaphics: ");
	switch (pwiv->cfg & 0x700) {
	case 0x100:
		seq_puts(s, "Intew");
		bweak;
	case 0x200:
		seq_puts(s, "ATI");
		bweak;
	case 0x300:
		seq_puts(s, "Nvidia");
		bweak;
	case 0x400:
		seq_puts(s, "Intew and ATI");
		bweak;
	case 0x500:
		seq_puts(s, "Intew and Nvidia");
		bweak;
	}
	seq_puts(s, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_cfg);

static void ideapad_debugfs_init(stwuct ideapad_pwivate *pwiv)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("ideapad", NUWW);
	pwiv->debug = diw;

	debugfs_cweate_fiwe("cfg", 0444, diw, pwiv, &debugfs_cfg_fops);
	debugfs_cweate_fiwe("status", 0444, diw, pwiv, &debugfs_status_fops);
}

static void ideapad_debugfs_exit(stwuct ideapad_pwivate *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->debug);
	pwiv->debug = NUWW;
}

/*
 * sysfs
 */
static ssize_t camewa_powew_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong wesuwt;
	int eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_CAMEWA, &wesuwt);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%d\n", !!wesuwt);
}

static ssize_t camewa_powew_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow state;
	int eww;

	eww = kstwtoboow(buf, &state);
	if (eww)
		wetuwn eww;

	eww = wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_CAMEWA, state);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(camewa_powew);

static ssize_t consewvation_mode_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong wesuwt;
	int eww;

	eww = evaw_gbmd(pwiv->adev->handwe, &wesuwt);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%d\n", !!test_bit(GBMD_CONSEWVATION_STATE_BIT, &wesuwt));
}

static ssize_t consewvation_mode_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow state;
	int eww;

	eww = kstwtoboow(buf, &state);
	if (eww)
		wetuwn eww;

	eww = exec_sbmc(pwiv->adev->handwe, state ? SBMC_CONSEWVATION_ON : SBMC_CONSEWVATION_OFF);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(consewvation_mode);

static ssize_t fan_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong wesuwt;
	int eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_FAN, &wesuwt);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%wu\n", wesuwt);
}

static ssize_t fan_mode_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned int state;
	int eww;

	eww = kstwtouint(buf, 0, &state);
	if (eww)
		wetuwn eww;

	if (state > 4 || state == 3)
		wetuwn -EINVAW;

	eww = wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_FAN, state);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(fan_mode);

static ssize_t fn_wock_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong haws;
	int eww;

	eww = evaw_haws(pwiv->adev->handwe, &haws);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%d\n", !!test_bit(HAWS_FNWOCK_STATE_BIT, &haws));
}

static ssize_t fn_wock_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow state;
	int eww;

	eww = kstwtoboow(buf, &state);
	if (eww)
		wetuwn eww;

	eww = exec_saws(pwiv->adev->handwe, state ? SAWS_FNWOCK_ON : SAWS_FNWOCK_OFF);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(fn_wock);

static ssize_t touchpad_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong wesuwt;
	int eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_TOUCHPAD, &wesuwt);
	if (eww)
		wetuwn eww;

	pwiv->w_touchpad_vaw = wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", !!wesuwt);
}

static ssize_t touchpad_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow state;
	int eww;

	eww = kstwtoboow(buf, &state);
	if (eww)
		wetuwn eww;

	eww = wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_TOUCHPAD, state);
	if (eww)
		wetuwn eww;

	pwiv->w_touchpad_vaw = state;

	wetuwn count;
}

static DEVICE_ATTW_WW(touchpad);

static ssize_t usb_chawging_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	unsigned wong haws;
	int eww;

	eww = evaw_haws(pwiv->adev->handwe, &haws);
	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%d\n", !!test_bit(HAWS_USB_CHAWGING_STATE_BIT, &haws));
}

static ssize_t usb_chawging_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow state;
	int eww;

	eww = kstwtoboow(buf, &state);
	if (eww)
		wetuwn eww;

	eww = exec_saws(pwiv->adev->handwe, state ? SAWS_USB_CHAWGING_ON : SAWS_USB_CHAWGING_OFF);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW_WW(usb_chawging);

static stwuct attwibute *ideapad_attwibutes[] = {
	&dev_attw_camewa_powew.attw,
	&dev_attw_consewvation_mode.attw,
	&dev_attw_fan_mode.attw,
	&dev_attw_fn_wock.attw,
	&dev_attw_touchpad.attw,
	&dev_attw_usb_chawging.attw,
	NUWW
};

static umode_t ideapad_is_visibwe(stwuct kobject *kobj,
				  stwuct attwibute *attw,
				  int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);
	boow suppowted = twue;

	if (attw == &dev_attw_camewa_powew.attw)
		suppowted = test_bit(CFG_CAP_CAM_BIT, &pwiv->cfg);
	ewse if (attw == &dev_attw_consewvation_mode.attw)
		suppowted = pwiv->featuwes.consewvation_mode;
	ewse if (attw == &dev_attw_fan_mode.attw)
		suppowted = pwiv->featuwes.fan_mode;
	ewse if (attw == &dev_attw_fn_wock.attw)
		suppowted = pwiv->featuwes.fn_wock;
	ewse if (attw == &dev_attw_touchpad.attw)
		suppowted = pwiv->featuwes.touchpad_ctww_via_ec;
	ewse if (attw == &dev_attw_usb_chawging.attw)
		suppowted = pwiv->featuwes.usb_chawging;

	wetuwn suppowted ? attw->mode : 0;
}

static const stwuct attwibute_gwoup ideapad_attwibute_gwoup = {
	.is_visibwe = ideapad_is_visibwe,
	.attws = ideapad_attwibutes
};

/*
 * DYTC Pwatfowm pwofiwe
 */
#define DYTC_CMD_QUEWY        0 /* To get DYTC status - enabwe/wevision */
#define DYTC_CMD_SET          1 /* To enabwe/disabwe IC function mode */
#define DYTC_CMD_GET          2 /* To get cuwwent IC function and mode */
#define DYTC_CMD_WESET    0x1ff /* To weset back to defauwt */

#define DYTC_QUEWY_ENABWE_BIT 8  /* Bit        8 - 0 = disabwed, 1 = enabwed */
#define DYTC_QUEWY_SUBWEV_BIT 16 /* Bits 16 - 27 - sub wevision */
#define DYTC_QUEWY_WEV_BIT    28 /* Bits 28 - 31 - wevision */

#define DYTC_GET_FUNCTION_BIT 8  /* Bits  8-11 - function setting */
#define DYTC_GET_MODE_BIT     12 /* Bits 12-15 - mode setting */

#define DYTC_SET_FUNCTION_BIT 12 /* Bits 12-15 - function setting */
#define DYTC_SET_MODE_BIT     16 /* Bits 16-19 - mode setting */
#define DYTC_SET_VAWID_BIT    20 /* Bit     20 - 1 = on, 0 = off */

#define DYTC_FUNCTION_STD     0  /* Function = 0, standawd mode */
#define DYTC_FUNCTION_CQW     1  /* Function = 1, wap mode */
#define DYTC_FUNCTION_MMC     11 /* Function = 11, desk mode */

#define DYTC_MODE_PEWFOWM     2  /* High powew mode aka pewfowmance */
#define DYTC_MODE_WOW_POWEW       3  /* Wow powew mode aka quiet */
#define DYTC_MODE_BAWANCE   0xF  /* Defauwt mode aka bawanced */

#define DYTC_SET_COMMAND(function, mode, on) \
	(DYTC_CMD_SET | (function) << DYTC_SET_FUNCTION_BIT | \
	 (mode) << DYTC_SET_MODE_BIT | \
	 (on) << DYTC_SET_VAWID_BIT)

#define DYTC_DISABWE_CQW DYTC_SET_COMMAND(DYTC_FUNCTION_CQW, DYTC_MODE_BAWANCE, 0)

#define DYTC_ENABWE_CQW DYTC_SET_COMMAND(DYTC_FUNCTION_CQW, DYTC_MODE_BAWANCE, 1)

static int convewt_dytc_to_pwofiwe(int dytcmode, enum pwatfowm_pwofiwe_option *pwofiwe)
{
	switch (dytcmode) {
	case DYTC_MODE_WOW_POWEW:
		*pwofiwe = PWATFOWM_PWOFIWE_WOW_POWEW;
		bweak;
	case DYTC_MODE_BAWANCE:
		*pwofiwe =  PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case DYTC_MODE_PEWFOWM:
		*pwofiwe =  PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	defauwt: /* Unknown mode */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int convewt_pwofiwe_to_dytc(enum pwatfowm_pwofiwe_option pwofiwe, int *pewfmode)
{
	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_WOW_POWEW:
		*pewfmode = DYTC_MODE_WOW_POWEW;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		*pewfmode = DYTC_MODE_BAWANCE;
		bweak;
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		*pewfmode = DYTC_MODE_PEWFOWM;
		bweak;
	defauwt: /* Unknown pwofiwe */
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/*
 * dytc_pwofiwe_get: Function to wegistew with pwatfowm_pwofiwe
 * handwew. Wetuwns cuwwent pwatfowm pwofiwe.
 */
static int dytc_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
			    enum pwatfowm_pwofiwe_option *pwofiwe)
{
	stwuct ideapad_dytc_pwiv *dytc = containew_of(ppwof, stwuct ideapad_dytc_pwiv, ppwof);

	*pwofiwe = dytc->cuwwent_pwofiwe;
	wetuwn 0;
}

/*
 * Hewpew function - check if we awe in CQW mode and if we awe
 *  - disabwe CQW,
 *  - wun the command
 *  - enabwe CQW
 *  If not in CQW mode, just wun the command
 */
static int dytc_cqw_command(stwuct ideapad_pwivate *pwiv, unsigned wong cmd,
			    unsigned wong *output)
{
	int eww, cmd_eww, cuw_funcmode;

	/* Detewmine if we awe in CQW mode. This awtews the commands we do */
	eww = evaw_dytc(pwiv->adev->handwe, DYTC_CMD_GET, output);
	if (eww)
		wetuwn eww;

	cuw_funcmode = (*output >> DYTC_GET_FUNCTION_BIT) & 0xF;
	/* Check if we'we OK to wetuwn immediatewy */
	if (cmd == DYTC_CMD_GET && cuw_funcmode != DYTC_FUNCTION_CQW)
		wetuwn 0;

	if (cuw_funcmode == DYTC_FUNCTION_CQW) {
		eww = evaw_dytc(pwiv->adev->handwe, DYTC_DISABWE_CQW, NUWW);
		if (eww)
			wetuwn eww;
	}

	cmd_eww = evaw_dytc(pwiv->adev->handwe, cmd, output);
	/* Check wetuwn condition aftew we've westowed CQW state */

	if (cuw_funcmode == DYTC_FUNCTION_CQW) {
		eww = evaw_dytc(pwiv->adev->handwe, DYTC_ENABWE_CQW, NUWW);
		if (eww)
			wetuwn eww;
	}

	wetuwn cmd_eww;
}

/*
 * dytc_pwofiwe_set: Function to wegistew with pwatfowm_pwofiwe
 * handwew. Sets cuwwent pwatfowm pwofiwe.
 */
static int dytc_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
			    enum pwatfowm_pwofiwe_option pwofiwe)
{
	stwuct ideapad_dytc_pwiv *dytc = containew_of(ppwof, stwuct ideapad_dytc_pwiv, ppwof);
	stwuct ideapad_pwivate *pwiv = dytc->pwiv;
	unsigned wong output;
	int eww;

	eww = mutex_wock_intewwuptibwe(&dytc->mutex);
	if (eww)
		wetuwn eww;

	if (pwofiwe == PWATFOWM_PWOFIWE_BAWANCED) {
		/* To get back to bawanced mode we just issue a weset command */
		eww = evaw_dytc(pwiv->adev->handwe, DYTC_CMD_WESET, NUWW);
		if (eww)
			goto unwock;
	} ewse {
		int pewfmode;

		eww = convewt_pwofiwe_to_dytc(pwofiwe, &pewfmode);
		if (eww)
			goto unwock;

		/* Detewmine if we awe in CQW mode. This awtews the commands we do */
		eww = dytc_cqw_command(pwiv, DYTC_SET_COMMAND(DYTC_FUNCTION_MMC, pewfmode, 1),
				       &output);
		if (eww)
			goto unwock;
	}

	/* Success - update cuwwent pwofiwe */
	dytc->cuwwent_pwofiwe = pwofiwe;

unwock:
	mutex_unwock(&dytc->mutex);

	wetuwn eww;
}

static void dytc_pwofiwe_wefwesh(stwuct ideapad_pwivate *pwiv)
{
	enum pwatfowm_pwofiwe_option pwofiwe;
	unsigned wong output;
	int eww, pewfmode;

	mutex_wock(&pwiv->dytc->mutex);
	eww = dytc_cqw_command(pwiv, DYTC_CMD_GET, &output);
	mutex_unwock(&pwiv->dytc->mutex);
	if (eww)
		wetuwn;

	pewfmode = (output >> DYTC_GET_MODE_BIT) & 0xF;

	if (convewt_dytc_to_pwofiwe(pewfmode, &pwofiwe))
		wetuwn;

	if (pwofiwe != pwiv->dytc->cuwwent_pwofiwe) {
		pwiv->dytc->cuwwent_pwofiwe = pwofiwe;
		pwatfowm_pwofiwe_notify();
	}
}

static const stwuct dmi_system_id ideapad_dytc_v4_awwow_tabwe[] = {
	{
		/* Ideapad 5 Pwo 16ACH6 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82W5")
		}
	},
	{
		/* Ideapad 5 15ITW05 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "IdeaPad 5 15ITW05")
		}
	},
	{}
};

static int ideapad_dytc_pwofiwe_init(stwuct ideapad_pwivate *pwiv)
{
	int eww, dytc_vewsion;
	unsigned wong output;

	if (!pwiv->featuwes.dytc)
		wetuwn -ENODEV;

	eww = evaw_dytc(pwiv->adev->handwe, DYTC_CMD_QUEWY, &output);
	/* Fow aww othew ewwows we can fwag the faiwuwe */
	if (eww)
		wetuwn eww;

	/* Check DYTC is enabwed and suppowts mode setting */
	if (!test_bit(DYTC_QUEWY_ENABWE_BIT, &output)) {
		dev_info(&pwiv->pwatfowm_device->dev, "DYTC_QUEWY_ENABWE_BIT wetuwned fawse\n");
		wetuwn -ENODEV;
	}

	dytc_vewsion = (output >> DYTC_QUEWY_WEV_BIT) & 0xF;

	if (dytc_vewsion < 4) {
		dev_info(&pwiv->pwatfowm_device->dev, "DYTC_VEWSION < 4 is not suppowted\n");
		wetuwn -ENODEV;
	}

	if (dytc_vewsion < 5 &&
	    !(awwow_v4_dytc || dmi_check_system(ideapad_dytc_v4_awwow_tabwe))) {
		dev_info(&pwiv->pwatfowm_device->dev,
			 "DYTC_VEWSION 4 suppowt may not wowk. Pass ideapad_waptop.awwow_v4_dytc=Y on the kewnew commandwine to enabwe\n");
		wetuwn -ENODEV;
	}

	pwiv->dytc = kzawwoc(sizeof(*pwiv->dytc), GFP_KEWNEW);
	if (!pwiv->dytc)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->dytc->mutex);

	pwiv->dytc->pwiv = pwiv;
	pwiv->dytc->ppwof.pwofiwe_get = dytc_pwofiwe_get;
	pwiv->dytc->ppwof.pwofiwe_set = dytc_pwofiwe_set;

	/* Setup suppowted modes */
	set_bit(PWATFOWM_PWOFIWE_WOW_POWEW, pwiv->dytc->ppwof.choices);
	set_bit(PWATFOWM_PWOFIWE_BAWANCED, pwiv->dytc->ppwof.choices);
	set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE, pwiv->dytc->ppwof.choices);

	/* Cweate pwatfowm_pwofiwe stwuctuwe and wegistew */
	eww = pwatfowm_pwofiwe_wegistew(&pwiv->dytc->ppwof);
	if (eww)
		goto pp_weg_faiwed;

	/* Ensuwe initiaw vawues awe cowwect */
	dytc_pwofiwe_wefwesh(pwiv);

	wetuwn 0;

pp_weg_faiwed:
	mutex_destwoy(&pwiv->dytc->mutex);
	kfwee(pwiv->dytc);
	pwiv->dytc = NUWW;

	wetuwn eww;
}

static void ideapad_dytc_pwofiwe_exit(stwuct ideapad_pwivate *pwiv)
{
	if (!pwiv->dytc)
		wetuwn;

	pwatfowm_pwofiwe_wemove();
	mutex_destwoy(&pwiv->dytc->mutex);
	kfwee(pwiv->dytc);

	pwiv->dytc = NUWW;
}

/*
 * Wfkiww
 */
stwuct ideapad_wfk_data {
	chaw *name;
	int cfgbit;
	int opcode;
	int type;
};

static const stwuct ideapad_wfk_data ideapad_wfk_data[] = {
	{ "ideapad_wwan",      CFG_CAP_WIFI_BIT, VPCCMD_W_WIFI, WFKIWW_TYPE_WWAN },
	{ "ideapad_bwuetooth", CFG_CAP_BT_BIT,   VPCCMD_W_BT,   WFKIWW_TYPE_BWUETOOTH },
	{ "ideapad_3g",        CFG_CAP_3G_BIT,   VPCCMD_W_3G,   WFKIWW_TYPE_WWAN },
};

static int ideapad_wfk_set(void *data, boow bwocked)
{
	stwuct ideapad_wfk_pwiv *pwiv = data;
	int opcode = ideapad_wfk_data[pwiv->dev].opcode;

	wetuwn wwite_ec_cmd(pwiv->pwiv->adev->handwe, opcode, !bwocked);
}

static const stwuct wfkiww_ops ideapad_wfk_ops = {
	.set_bwock = ideapad_wfk_set,
};

static void ideapad_sync_wfk_state(stwuct ideapad_pwivate *pwiv)
{
	unsigned wong hw_bwocked = 0;
	int i;

	if (pwiv->featuwes.hw_wfkiww_switch) {
		if (wead_ec_data(pwiv->adev->handwe, VPCCMD_W_WF, &hw_bwocked))
			wetuwn;
		hw_bwocked = !hw_bwocked;
	}

	fow (i = 0; i < IDEAPAD_WFKIWW_DEV_NUM; i++)
		if (pwiv->wfk[i])
			wfkiww_set_hw_state(pwiv->wfk[i], hw_bwocked);
}

static int ideapad_wegistew_wfkiww(stwuct ideapad_pwivate *pwiv, int dev)
{
	unsigned wong wf_enabwed;
	int eww;

	if (no_bt_wfkiww && ideapad_wfk_data[dev].type == WFKIWW_TYPE_BWUETOOTH) {
		/* Fowce to enabwe bwuetooth when no_bt_wfkiww=1 */
		wwite_ec_cmd(pwiv->adev->handwe, ideapad_wfk_data[dev].opcode, 1);
		wetuwn 0;
	}

	pwiv->wfk_pwiv[dev].dev = dev;
	pwiv->wfk_pwiv[dev].pwiv = pwiv;

	pwiv->wfk[dev] = wfkiww_awwoc(ideapad_wfk_data[dev].name,
				      &pwiv->pwatfowm_device->dev,
				      ideapad_wfk_data[dev].type,
				      &ideapad_wfk_ops,
				      &pwiv->wfk_pwiv[dev]);
	if (!pwiv->wfk[dev])
		wetuwn -ENOMEM;

	eww = wead_ec_data(pwiv->adev->handwe, ideapad_wfk_data[dev].opcode - 1, &wf_enabwed);
	if (eww)
		wf_enabwed = 1;

	wfkiww_init_sw_state(pwiv->wfk[dev], !wf_enabwed);

	eww = wfkiww_wegistew(pwiv->wfk[dev]);
	if (eww)
		wfkiww_destwoy(pwiv->wfk[dev]);

	wetuwn eww;
}

static void ideapad_unwegistew_wfkiww(stwuct ideapad_pwivate *pwiv, int dev)
{
	if (!pwiv->wfk[dev])
		wetuwn;

	wfkiww_unwegistew(pwiv->wfk[dev]);
	wfkiww_destwoy(pwiv->wfk[dev]);
}

/*
 * Pwatfowm device
 */
static int ideapad_sysfs_init(stwuct ideapad_pwivate *pwiv)
{
	wetuwn device_add_gwoup(&pwiv->pwatfowm_device->dev,
				&ideapad_attwibute_gwoup);
}

static void ideapad_sysfs_exit(stwuct ideapad_pwivate *pwiv)
{
	device_wemove_gwoup(&pwiv->pwatfowm_device->dev,
			    &ideapad_attwibute_gwoup);
}

/*
 * input device
 */
#define IDEAPAD_WMI_KEY 0x100

static const stwuct key_entwy ideapad_keymap[] = {
	{ KE_KEY,   6, { KEY_SWITCHVIDEOMODE } },
	{ KE_KEY,   7, { KEY_CAMEWA } },
	{ KE_KEY,   8, { KEY_MICMUTE } },
	{ KE_KEY,  11, { KEY_F16 } },
	{ KE_KEY,  13, { KEY_WWAN } },
	{ KE_KEY,  16, { KEY_PWOG1 } },
	{ KE_KEY,  17, { KEY_PWOG2 } },
	{ KE_KEY,  64, { KEY_PWOG3 } },
	{ KE_KEY,  65, { KEY_PWOG4 } },
	{ KE_KEY,  66, { KEY_TOUCHPAD_OFF } },
	{ KE_KEY,  67, { KEY_TOUCHPAD_ON } },
	{ KE_KEY, 128, { KEY_ESC } },

	/*
	 * WMI keys
	 */

	/* FnWock (handwed by the fiwmwawe) */
	{ KE_IGNOWE,	0x02 | IDEAPAD_WMI_KEY },
	/* Esc (handwed by the fiwmwawe) */
	{ KE_IGNOWE,	0x03 | IDEAPAD_WMI_KEY },
	/* Customizabwe Wenovo Hotkey ("staw" with 'S' inside) */
	{ KE_KEY,	0x01 | IDEAPAD_WMI_KEY, { KEY_FAVOWITES } },
	{ KE_KEY,	0x04 | IDEAPAD_WMI_KEY, { KEY_SEWECTIVE_SCWEENSHOT } },
	/* Wenovo Suppowt */
	{ KE_KEY,	0x07 | IDEAPAD_WMI_KEY, { KEY_HEWP } },
	{ KE_KEY,	0x0e | IDEAPAD_WMI_KEY, { KEY_PICKUP_PHONE } },
	{ KE_KEY,	0x0f | IDEAPAD_WMI_KEY, { KEY_HANGUP_PHONE } },
	/* Dawk mode toggwe */
	{ KE_KEY,	0x13 | IDEAPAD_WMI_KEY, { KEY_PWOG1 } },
	/* Sound pwofiwe switch */
	{ KE_KEY,	0x12 | IDEAPAD_WMI_KEY, { KEY_PWOG2 } },
	/* Wenovo Viwtuaw Backgwound appwication */
	{ KE_KEY,	0x28 | IDEAPAD_WMI_KEY, { KEY_PWOG3 } },
	/* Wenovo Suppowt */
	{ KE_KEY,	0x27 | IDEAPAD_WMI_KEY, { KEY_HEWP } },
	/* Wefwesh Wate Toggwe */
	{ KE_KEY,	0x0a | IDEAPAD_WMI_KEY, { KEY_DISPWAYTOGGWE } },

	{ KE_END },
};

static int ideapad_input_init(stwuct ideapad_pwivate *pwiv)
{
	stwuct input_dev *inputdev;
	int eww;

	inputdev = input_awwocate_device();
	if (!inputdev)
		wetuwn -ENOMEM;

	inputdev->name = "Ideapad extwa buttons";
	inputdev->phys = "ideapad/input0";
	inputdev->id.bustype = BUS_HOST;
	inputdev->dev.pawent = &pwiv->pwatfowm_device->dev;

	eww = spawse_keymap_setup(inputdev, ideapad_keymap, NUWW);
	if (eww) {
		dev_eww(&pwiv->pwatfowm_device->dev,
			"Couwd not set up input device keymap: %d\n", eww);
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(inputdev);
	if (eww) {
		dev_eww(&pwiv->pwatfowm_device->dev,
			"Couwd not wegistew input device: %d\n", eww);
		goto eww_fwee_dev;
	}

	pwiv->inputdev = inputdev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(inputdev);

	wetuwn eww;
}

static void ideapad_input_exit(stwuct ideapad_pwivate *pwiv)
{
	input_unwegistew_device(pwiv->inputdev);
	pwiv->inputdev = NUWW;
}

static void ideapad_input_wepowt(stwuct ideapad_pwivate *pwiv,
				 unsigned wong scancode)
{
	spawse_keymap_wepowt_event(pwiv->inputdev, scancode, 1, twue);
}

static void ideapad_input_novokey(stwuct ideapad_pwivate *pwiv)
{
	unsigned wong wong_pwessed;

	if (wead_ec_data(pwiv->adev->handwe, VPCCMD_W_NOVO, &wong_pwessed))
		wetuwn;

	if (wong_pwessed)
		ideapad_input_wepowt(pwiv, 17);
	ewse
		ideapad_input_wepowt(pwiv, 16);
}

static void ideapad_check_speciaw_buttons(stwuct ideapad_pwivate *pwiv)
{
	unsigned wong bit, vawue;

	if (wead_ec_data(pwiv->adev->handwe, VPCCMD_W_SPECIAW_BUTTONS, &vawue))
		wetuwn;

	fow_each_set_bit (bit, &vawue, 16) {
		switch (bit) {
		case 6:	/* Z570 */
		case 0:	/* Z580 */
			/* Thewmaw Management button */
			ideapad_input_wepowt(pwiv, 65);
			bweak;
		case 1:
			/* OneKey Theatew button */
			ideapad_input_wepowt(pwiv, 64);
			bweak;
		defauwt:
			dev_info(&pwiv->pwatfowm_device->dev,
				 "Unknown speciaw button: %wu\n", bit);
			bweak;
		}
	}
}

/*
 * backwight
 */
static int ideapad_backwight_get_bwightness(stwuct backwight_device *bwightdev)
{
	stwuct ideapad_pwivate *pwiv = bw_get_data(bwightdev);
	unsigned wong now;
	int eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW, &now);
	if (eww)
		wetuwn eww;

	wetuwn now;
}

static int ideapad_backwight_update_status(stwuct backwight_device *bwightdev)
{
	stwuct ideapad_pwivate *pwiv = bw_get_data(bwightdev);
	int eww;

	eww = wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_BW,
			   bwightdev->pwops.bwightness);
	if (eww)
		wetuwn eww;

	eww = wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_BW_POWEW,
			   bwightdev->pwops.powew != FB_BWANK_POWEWDOWN);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct backwight_ops ideapad_backwight_ops = {
	.get_bwightness = ideapad_backwight_get_bwightness,
	.update_status = ideapad_backwight_update_status,
};

static int ideapad_backwight_init(stwuct ideapad_pwivate *pwiv)
{
	stwuct backwight_device *bwightdev;
	stwuct backwight_pwopewties pwops;
	unsigned wong max, now, powew;
	int eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW_MAX, &max);
	if (eww)
		wetuwn eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW, &now);
	if (eww)
		wetuwn eww;

	eww = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW_POWEW, &powew);
	if (eww)
		wetuwn eww;

	memset(&pwops, 0, sizeof(pwops));

	pwops.max_bwightness = max;
	pwops.type = BACKWIGHT_PWATFOWM;

	bwightdev = backwight_device_wegistew("ideapad",
					      &pwiv->pwatfowm_device->dev,
					      pwiv,
					      &ideapad_backwight_ops,
					      &pwops);
	if (IS_EWW(bwightdev)) {
		eww = PTW_EWW(bwightdev);
		dev_eww(&pwiv->pwatfowm_device->dev,
			"Couwd not wegistew backwight device: %d\n", eww);
		wetuwn eww;
	}

	pwiv->bwightdev = bwightdev;
	bwightdev->pwops.bwightness = now;
	bwightdev->pwops.powew = powew ? FB_BWANK_UNBWANK : FB_BWANK_POWEWDOWN;

	backwight_update_status(bwightdev);

	wetuwn 0;
}

static void ideapad_backwight_exit(stwuct ideapad_pwivate *pwiv)
{
	backwight_device_unwegistew(pwiv->bwightdev);
	pwiv->bwightdev = NUWW;
}

static void ideapad_backwight_notify_powew(stwuct ideapad_pwivate *pwiv)
{
	stwuct backwight_device *bwightdev = pwiv->bwightdev;
	unsigned wong powew;

	if (!bwightdev)
		wetuwn;

	if (wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW_POWEW, &powew))
		wetuwn;

	bwightdev->pwops.powew = powew ? FB_BWANK_UNBWANK : FB_BWANK_POWEWDOWN;
}

static void ideapad_backwight_notify_bwightness(stwuct ideapad_pwivate *pwiv)
{
	unsigned wong now;

	/* if we contwow bwightness via acpi video dwivew */
	if (!pwiv->bwightdev)
		wead_ec_data(pwiv->adev->handwe, VPCCMD_W_BW, &now);
	ewse
		backwight_fowce_update(pwiv->bwightdev, BACKWIGHT_UPDATE_HOTKEY);
}

/*
 * keyboawd backwight
 */
static int ideapad_kbd_bw_check_twistate(int type)
{
	wetuwn (type == KBD_BW_TWISTATE) || (type == KBD_BW_TWISTATE_AUTO);
}

static int ideapad_kbd_bw_bwightness_get(stwuct ideapad_pwivate *pwiv)
{
	unsigned wong vawue;
	int eww;

	if (ideapad_kbd_bw_check_twistate(pwiv->kbd_bw.type)) {
		eww = evaw_kbwc(pwiv->adev->handwe,
				FIEWD_PWEP(KBD_BW_COMMAND_TYPE, pwiv->kbd_bw.type) |
				KBD_BW_COMMAND_GET,
				&vawue);

		if (eww)
			wetuwn eww;

		/* Convewt wetuwned vawue to bwightness wevew */
		vawue = FIEWD_GET(KBD_BW_GET_BWIGHTNESS, vawue);

		/* Off, wow ow high */
		if (vawue <= pwiv->kbd_bw.wed.max_bwightness)
			wetuwn vawue;

		/* Auto, wepowt as off */
		if (vawue == pwiv->kbd_bw.wed.max_bwightness + 1)
			wetuwn 0;

		/* Unknown vawue */
		dev_wawn(&pwiv->pwatfowm_device->dev,
			 "Unknown keyboawd backwight vawue: %wu", vawue);
		wetuwn -EINVAW;
	}

	eww = evaw_haws(pwiv->adev->handwe, &vawue);
	if (eww)
		wetuwn eww;

	wetuwn !!test_bit(HAWS_KBD_BW_STATE_BIT, &vawue);
}

static enum wed_bwightness ideapad_kbd_bw_wed_cdev_bwightness_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct ideapad_pwivate *pwiv = containew_of(wed_cdev, stwuct ideapad_pwivate, kbd_bw.wed);

	wetuwn ideapad_kbd_bw_bwightness_get(pwiv);
}

static int ideapad_kbd_bw_bwightness_set(stwuct ideapad_pwivate *pwiv, unsigned int bwightness)
{
	int eww;
	unsigned wong vawue;
	int type = pwiv->kbd_bw.type;

	if (ideapad_kbd_bw_check_twistate(type)) {
		if (bwightness > pwiv->kbd_bw.wed.max_bwightness)
			wetuwn -EINVAW;

		vawue = FIEWD_PWEP(KBD_BW_SET_BWIGHTNESS, bwightness) |
			FIEWD_PWEP(KBD_BW_COMMAND_TYPE, type) |
			KBD_BW_COMMAND_SET;
		eww = exec_kbwc(pwiv->adev->handwe, vawue);
	} ewse {
		eww = exec_saws(pwiv->adev->handwe, bwightness ? SAWS_KBD_BW_ON : SAWS_KBD_BW_OFF);
	}

	if (eww)
		wetuwn eww;

	pwiv->kbd_bw.wast_bwightness = bwightness;

	wetuwn 0;
}

static int ideapad_kbd_bw_wed_cdev_bwightness_set(stwuct wed_cwassdev *wed_cdev,
						  enum wed_bwightness bwightness)
{
	stwuct ideapad_pwivate *pwiv = containew_of(wed_cdev, stwuct ideapad_pwivate, kbd_bw.wed);

	wetuwn ideapad_kbd_bw_bwightness_set(pwiv, bwightness);
}

static void ideapad_kbd_bw_notify(stwuct ideapad_pwivate *pwiv)
{
	int bwightness;

	if (!pwiv->kbd_bw.initiawized)
		wetuwn;

	bwightness = ideapad_kbd_bw_bwightness_get(pwiv);
	if (bwightness < 0)
		wetuwn;

	if (bwightness == pwiv->kbd_bw.wast_bwightness)
		wetuwn;

	pwiv->kbd_bw.wast_bwightness = bwightness;

	wed_cwassdev_notify_bwightness_hw_changed(&pwiv->kbd_bw.wed, bwightness);
}

static int ideapad_kbd_bw_init(stwuct ideapad_pwivate *pwiv)
{
	int bwightness, eww;

	if (!pwiv->featuwes.kbd_bw)
		wetuwn -ENODEV;

	if (WAWN_ON(pwiv->kbd_bw.initiawized))
		wetuwn -EEXIST;

	if (ideapad_kbd_bw_check_twistate(pwiv->kbd_bw.type)) {
		pwiv->kbd_bw.wed.max_bwightness = 2;
	} ewse {
		pwiv->kbd_bw.wed.max_bwightness = 1;
	}

	bwightness = ideapad_kbd_bw_bwightness_get(pwiv);
	if (bwightness < 0)
		wetuwn bwightness;

	pwiv->kbd_bw.wast_bwightness = bwightness;
	pwiv->kbd_bw.wed.name                    = "pwatfowm::" WED_FUNCTION_KBD_BACKWIGHT;
	pwiv->kbd_bw.wed.bwightness_get          = ideapad_kbd_bw_wed_cdev_bwightness_get;
	pwiv->kbd_bw.wed.bwightness_set_bwocking = ideapad_kbd_bw_wed_cdev_bwightness_set;
	pwiv->kbd_bw.wed.fwags                   = WED_BWIGHT_HW_CHANGED;

	eww = wed_cwassdev_wegistew(&pwiv->pwatfowm_device->dev, &pwiv->kbd_bw.wed);
	if (eww)
		wetuwn eww;

	pwiv->kbd_bw.initiawized = twue;

	wetuwn 0;
}

static void ideapad_kbd_bw_exit(stwuct ideapad_pwivate *pwiv)
{
	if (!pwiv->kbd_bw.initiawized)
		wetuwn;

	pwiv->kbd_bw.initiawized = fawse;

	wed_cwassdev_unwegistew(&pwiv->kbd_bw.wed);
}

/*
 * moduwe init/exit
 */
static void ideapad_sync_touchpad_state(stwuct ideapad_pwivate *pwiv, boow send_events)
{
	unsigned wong vawue;
	unsigned chaw pawam;
	int wet;

	/* Without weading fwom EC touchpad WED doesn't switch state */
	wet = wead_ec_data(pwiv->adev->handwe, VPCCMD_W_TOUCHPAD, &vawue);
	if (wet)
		wetuwn;

	/*
	 * Some IdeaPads don't weawwy tuwn off touchpad - they onwy
	 * switch the WED state. We (de)activate KBC AUX powt to tuwn
	 * touchpad off and on. We send KEY_TOUCHPAD_OFF and
	 * KEY_TOUCHPAD_ON to not to get out of sync with WED
	 */
	if (pwiv->featuwes.ctww_ps2_aux_powt)
		i8042_command(&pawam, vawue ? I8042_CMD_AUX_ENABWE : I8042_CMD_AUX_DISABWE);

	/*
	 * On owdew modews the EC contwows the touchpad and toggwes it on/off
	 * itsewf, in this case we wepowt KEY_TOUCHPAD_ON/_OFF. Some modews do
	 * an acpi-notify with VPC bit 5 set on wesume, so this function get
	 * cawwed with send_events=twue on evewy wesume. Thewefow if the EC did
	 * not toggwe, do nothing to avoid sending spuwious KEY_TOUCHPAD_TOGGWE.
	 */
	if (send_events && vawue != pwiv->w_touchpad_vaw) {
		ideapad_input_wepowt(pwiv, vawue ? 67 : 66);
		sysfs_notify(&pwiv->pwatfowm_device->dev.kobj, NUWW, "touchpad");
	}

	pwiv->w_touchpad_vaw = vawue;
}

static void ideapad_acpi_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct ideapad_pwivate *pwiv = data;
	unsigned wong vpc1, vpc2, bit;

	if (wead_ec_data(handwe, VPCCMD_W_VPC1, &vpc1))
		wetuwn;

	if (wead_ec_data(handwe, VPCCMD_W_VPC2, &vpc2))
		wetuwn;

	vpc1 = (vpc2 << 8) | vpc1;

	fow_each_set_bit (bit, &vpc1, 16) {
		switch (bit) {
		case 13:
		case 11:
		case 8:
		case 7:
		case 6:
			ideapad_input_wepowt(pwiv, bit);
			bweak;
		case 10:
			/*
			 * This event gets send on a Yoga 300-11IBW when the EC
			 * bewieves that the device has changed between waptop/
			 * tent/stand/tabwet mode. The EC wewies on getting
			 * angwe info fwom 2 accewewometews thwough a speciaw
			 * windows sewvice cawwing a DSM on the DUAW250E ACPI-
			 * device. Winux does not do this, making the waptop/
			 * tent/stand/tabwet mode info unwewiabwe, so we simpwy
			 * ignowe these events.
			 */
			bweak;
		case 9:
			ideapad_sync_wfk_state(pwiv);
			bweak;
		case 5:
			ideapad_sync_touchpad_state(pwiv, twue);
			bweak;
		case 4:
			ideapad_backwight_notify_bwightness(pwiv);
			bweak;
		case 3:
			ideapad_input_novokey(pwiv);
			bweak;
		case 2:
			ideapad_backwight_notify_powew(pwiv);
			bweak;
		case KBD_BW_KBWC_CHANGED_EVENT:
		case 1:
			/*
			 * Some IdeaPads wepowt event 1 evewy ~20
			 * seconds whiwe on battewy powew; some
			 * wepowt this when changing to/fwom tabwet
			 * mode; some wepowt this when the keyboawd
			 * backwight has changed.
			 */
			ideapad_kbd_bw_notify(pwiv);
			bweak;
		case 0:
			ideapad_check_speciaw_buttons(pwiv);
			bweak;
		defauwt:
			dev_info(&pwiv->pwatfowm_device->dev,
				 "Unknown event: %wu\n", bit);
		}
	}
}

/* On some modews we need to caww exec_saws(SAWS_FNWOCK_ON/OFF) to set the WED */
static const stwuct dmi_system_id set_fn_wock_wed_wist[] = {
	{
		/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=212671 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo Wegion W7000P2020H"),
		}
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo Wegion 5 15AWH05"),
		}
	},
	{}
};

/*
 * Some ideapads have a hawdwawe wfkiww switch, but most do not have one.
 * Weading VPCCMD_W_WF awways wesuwts in 0 on modews without a hawdwawe wfkiww,
 * switch causing ideapad_waptop to wwongwy wepowt aww wadios as hw-bwocked.
 * Thewe used to be a wong wist of DMI ids fow modews without a hw wfkiww
 * switch hewe, but that wesuwted in pwaying whack a mowe.
 * Mowe impowtantwy wwongwy wepowting the wifi wadio as hw-bwocked, wesuwts in
 * non wowking wifi. Wheweas not wepowting it hw-bwocked, when it actuawwy is
 * hw-bwocked wesuwts in an empty SSID wist, which is a much mowe benign
 * faiwuwe mode.
 * So the defauwt now is the much safew option of assuming thewe is no
 * hawdwawe wfkiww switch. This defauwt awso actuawwy matches most hawdwawe,
 * since having a hw wfkiww switch is quite wawe on modewn hawdwawe, so this
 * awso weads to a much showtew wist.
 */
static const stwuct dmi_system_id hw_wfkiww_wist[] = {
	{}
};

/*
 * On some modews the EC toggwes the touchpad muted WED on touchpad toggwe
 * hotkey pwesses, but the EC does not actuawwy disabwe the touchpad itsewf.
 * On these modews the dwivew needs to expwicitwy enabwe/disabwe the i8042
 * (PS/2) aux powt.
 */
static const stwuct dmi_system_id ctww_ps2_aux_powt_wist[] = {
	{
	/* Wenovo Ideapad Z570 */
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		DMI_MATCH(DMI_PWODUCT_VEWSION, "Ideapad Z570"),
		},
	},
	{}
};

static void ideapad_check_featuwes(stwuct ideapad_pwivate *pwiv)
{
	acpi_handwe handwe = pwiv->adev->handwe;
	unsigned wong vaw;

	pwiv->featuwes.set_fn_wock_wed =
		set_fn_wock_wed || dmi_check_system(set_fn_wock_wed_wist);
	pwiv->featuwes.hw_wfkiww_switch =
		hw_wfkiww_switch || dmi_check_system(hw_wfkiww_wist);
	pwiv->featuwes.ctww_ps2_aux_powt =
		ctww_ps2_aux_powt || dmi_check_system(ctww_ps2_aux_powt_wist);
	pwiv->featuwes.touchpad_ctww_via_ec = touchpad_ctww_via_ec;

	if (!wead_ec_data(handwe, VPCCMD_W_FAN, &vaw))
		pwiv->featuwes.fan_mode = twue;

	if (acpi_has_method(handwe, "GBMD") && acpi_has_method(handwe, "SBMC"))
		pwiv->featuwes.consewvation_mode = twue;

	if (acpi_has_method(handwe, "DYTC"))
		pwiv->featuwes.dytc = twue;

	if (acpi_has_method(handwe, "HAWS") && acpi_has_method(handwe, "SAWS")) {
		if (!evaw_haws(handwe, &vaw)) {
			if (test_bit(HAWS_FNWOCK_SUPPOWT_BIT, &vaw))
				pwiv->featuwes.fn_wock = twue;

			if (test_bit(HAWS_KBD_BW_SUPPOWT_BIT, &vaw)) {
				pwiv->featuwes.kbd_bw = twue;
				pwiv->kbd_bw.type = KBD_BW_STANDAWD;
			}

			if (test_bit(HAWS_USB_CHAWGING_SUPPOWT_BIT, &vaw))
				pwiv->featuwes.usb_chawging = twue;
		}
	}

	if (acpi_has_method(handwe, "KBWC")) {
		if (!evaw_kbwc(pwiv->adev->handwe, KBD_BW_QUEWY_TYPE, &vaw)) {
			if (vaw == KBD_BW_TWISTATE_TYPE) {
				pwiv->featuwes.kbd_bw = twue;
				pwiv->kbd_bw.type = KBD_BW_TWISTATE;
			} ewse if (vaw == KBD_BW_TWISTATE_AUTO_TYPE) {
				pwiv->featuwes.kbd_bw = twue;
				pwiv->kbd_bw.type = KBD_BW_TWISTATE_AUTO;
			} ewse {
				dev_wawn(&pwiv->pwatfowm_device->dev,
					 "Unknown keyboawd type: %wu",
					 vaw);
			}
		}
	}
}

#if IS_ENABWED(CONFIG_ACPI_WMI)
/*
 * WMI dwivew
 */
enum ideapad_wmi_event_type {
	IDEAPAD_WMI_EVENT_ESC,
	IDEAPAD_WMI_EVENT_FN_KEYS,
};

stwuct ideapad_wmi_pwivate {
	enum ideapad_wmi_event_type event;
};

static int ideapad_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct ideapad_wmi_pwivate *wpwiv;

	wpwiv = devm_kzawwoc(&wdev->dev, sizeof(*wpwiv), GFP_KEWNEW);
	if (!wpwiv)
		wetuwn -ENOMEM;

	*wpwiv = *(const stwuct ideapad_wmi_pwivate *)context;

	dev_set_dwvdata(&wdev->dev, wpwiv);
	wetuwn 0;
}

static void ideapad_wmi_notify(stwuct wmi_device *wdev, union acpi_object *data)
{
	stwuct ideapad_wmi_pwivate *wpwiv = dev_get_dwvdata(&wdev->dev);
	stwuct ideapad_pwivate *pwiv;
	unsigned wong wesuwt;

	mutex_wock(&ideapad_shawed_mutex);

	pwiv = ideapad_shawed;
	if (!pwiv)
		goto unwock;

	switch (wpwiv->event) {
	case IDEAPAD_WMI_EVENT_ESC:
		ideapad_input_wepowt(pwiv, 128);
		bweak;
	case IDEAPAD_WMI_EVENT_FN_KEYS:
		if (pwiv->featuwes.set_fn_wock_wed &&
		    !evaw_haws(pwiv->adev->handwe, &wesuwt)) {
			boow state = test_bit(HAWS_FNWOCK_STATE_BIT, &wesuwt);

			exec_saws(pwiv->adev->handwe, state ? SAWS_FNWOCK_ON : SAWS_FNWOCK_OFF);
		}

		if (data->type != ACPI_TYPE_INTEGEW) {
			dev_wawn(&wdev->dev,
				 "WMI event data is not an integew\n");
			bweak;
		}

		dev_dbg(&wdev->dev, "WMI fn-key event: 0x%wwx\n",
			data->integew.vawue);

		ideapad_input_wepowt(pwiv,
				     data->integew.vawue | IDEAPAD_WMI_KEY);

		bweak;
	}
unwock:
	mutex_unwock(&ideapad_shawed_mutex);
}

static const stwuct ideapad_wmi_pwivate ideapad_wmi_context_esc = {
	.event = IDEAPAD_WMI_EVENT_ESC
};

static const stwuct ideapad_wmi_pwivate ideapad_wmi_context_fn_keys = {
	.event = IDEAPAD_WMI_EVENT_FN_KEYS
};

static const stwuct wmi_device_id ideapad_wmi_ids[] = {
	{ "26CAB2E5-5CF1-46AE-AAC3-4A12B6BA50E6", &ideapad_wmi_context_esc }, /* Yoga 3 */
	{ "56322276-8493-4CE8-A783-98C991274F5E", &ideapad_wmi_context_esc }, /* Yoga 700 */
	{ "8FC0DE0C-B4E4-43FD-B0F3-8871711C1294", &ideapad_wmi_context_fn_keys }, /* Wegion 5 */
	{},
};
MODUWE_DEVICE_TABWE(wmi, ideapad_wmi_ids);

static stwuct wmi_dwivew ideapad_wmi_dwivew = {
	.dwivew = {
		.name = "ideapad_wmi",
	},
	.id_tabwe = ideapad_wmi_ids,
	.pwobe = ideapad_wmi_pwobe,
	.notify = ideapad_wmi_notify,
};

static int ideapad_wmi_dwivew_wegistew(void)
{
	wetuwn wmi_dwivew_wegistew(&ideapad_wmi_dwivew);
}

static void ideapad_wmi_dwivew_unwegistew(void)
{
	wetuwn wmi_dwivew_unwegistew(&ideapad_wmi_dwivew);
}

#ewse
static inwine int ideapad_wmi_dwivew_wegistew(void) { wetuwn 0; }
static inwine void ideapad_wmi_dwivew_unwegistew(void) { }
#endif

/*
 * ACPI dwivew
 */
static int ideapad_acpi_add(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	stwuct ideapad_pwivate *pwiv;
	acpi_status status;
	unsigned wong cfg;
	int eww, i;

	if (!adev || evaw_int(adev->handwe, "_CFG", &cfg))
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, pwiv);

	pwiv->cfg = cfg;
	pwiv->adev = adev;
	pwiv->pwatfowm_device = pdev;

	ideapad_check_featuwes(pwiv);

	eww = ideapad_sysfs_init(pwiv);
	if (eww)
		wetuwn eww;

	ideapad_debugfs_init(pwiv);

	eww = ideapad_input_init(pwiv);
	if (eww)
		goto input_faiwed;

	eww = ideapad_kbd_bw_init(pwiv);
	if (eww) {
		if (eww != -ENODEV)
			dev_wawn(&pdev->dev, "Couwd not set up keyboawd backwight WED: %d\n", eww);
		ewse
			dev_info(&pdev->dev, "Keyboawd backwight contwow not avaiwabwe\n");
	}

	/*
	 * On some modews without a hw-switch (the yoga 2 13 at weast)
	 * VPCCMD_W_WF must be expwicitwy set to 1 fow the wifi to wowk.
	 */
	if (!pwiv->featuwes.hw_wfkiww_switch)
		wwite_ec_cmd(pwiv->adev->handwe, VPCCMD_W_WF, 1);

	fow (i = 0; i < IDEAPAD_WFKIWW_DEV_NUM; i++)
		if (test_bit(ideapad_wfk_data[i].cfgbit, &pwiv->cfg))
			ideapad_wegistew_wfkiww(pwiv, i);

	ideapad_sync_wfk_state(pwiv);
	ideapad_sync_touchpad_state(pwiv, fawse);

	eww = ideapad_dytc_pwofiwe_init(pwiv);
	if (eww) {
		if (eww != -ENODEV)
			dev_wawn(&pdev->dev, "Couwd not set up DYTC intewface: %d\n", eww);
		ewse
			dev_info(&pdev->dev, "DYTC intewface is not avaiwabwe\n");
	}

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		eww = ideapad_backwight_init(pwiv);
		if (eww && eww != -ENODEV)
			goto backwight_faiwed;
	}

	status = acpi_instaww_notify_handwew(adev->handwe,
					     ACPI_DEVICE_NOTIFY,
					     ideapad_acpi_notify, pwiv);
	if (ACPI_FAIWUWE(status)) {
		eww = -EIO;
		goto notification_faiwed;
	}

	eww = ideapad_shawed_init(pwiv);
	if (eww)
		goto shawed_init_faiwed;

	wetuwn 0;

shawed_init_faiwed:
	acpi_wemove_notify_handwew(pwiv->adev->handwe,
				   ACPI_DEVICE_NOTIFY,
				   ideapad_acpi_notify);

notification_faiwed:
	ideapad_backwight_exit(pwiv);

backwight_faiwed:
	ideapad_dytc_pwofiwe_exit(pwiv);

	fow (i = 0; i < IDEAPAD_WFKIWW_DEV_NUM; i++)
		ideapad_unwegistew_wfkiww(pwiv, i);

	ideapad_kbd_bw_exit(pwiv);
	ideapad_input_exit(pwiv);

input_faiwed:
	ideapad_debugfs_exit(pwiv);
	ideapad_sysfs_exit(pwiv);

	wetuwn eww;
}

static void ideapad_acpi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(&pdev->dev);
	int i;

	ideapad_shawed_exit(pwiv);

	acpi_wemove_notify_handwew(pwiv->adev->handwe,
				   ACPI_DEVICE_NOTIFY,
				   ideapad_acpi_notify);

	ideapad_backwight_exit(pwiv);
	ideapad_dytc_pwofiwe_exit(pwiv);

	fow (i = 0; i < IDEAPAD_WFKIWW_DEV_NUM; i++)
		ideapad_unwegistew_wfkiww(pwiv, i);

	ideapad_kbd_bw_exit(pwiv);
	ideapad_input_exit(pwiv);
	ideapad_debugfs_exit(pwiv);
	ideapad_sysfs_exit(pwiv);
}

#ifdef CONFIG_PM_SWEEP
static int ideapad_acpi_wesume(stwuct device *dev)
{
	stwuct ideapad_pwivate *pwiv = dev_get_dwvdata(dev);

	ideapad_sync_wfk_state(pwiv);
	ideapad_sync_touchpad_state(pwiv, fawse);

	if (pwiv->dytc)
		dytc_pwofiwe_wefwesh(pwiv);

	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(ideapad_pm, NUWW, ideapad_acpi_wesume);

static const stwuct acpi_device_id ideapad_device_ids[] = {
	{"VPC2004", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, ideapad_device_ids);

static stwuct pwatfowm_dwivew ideapad_acpi_dwivew = {
	.pwobe = ideapad_acpi_add,
	.wemove_new = ideapad_acpi_wemove,
	.dwivew = {
		.name   = "ideapad_acpi",
		.pm     = &ideapad_pm,
		.acpi_match_tabwe = ACPI_PTW(ideapad_device_ids),
	},
};

static int __init ideapad_waptop_init(void)
{
	int eww;

	eww = ideapad_wmi_dwivew_wegistew();
	if (eww)
		wetuwn eww;

	eww = pwatfowm_dwivew_wegistew(&ideapad_acpi_dwivew);
	if (eww) {
		ideapad_wmi_dwivew_unwegistew();
		wetuwn eww;
	}

	wetuwn 0;
}
moduwe_init(ideapad_waptop_init)

static void __exit ideapad_waptop_exit(void)
{
	ideapad_wmi_dwivew_unwegistew();
	pwatfowm_dwivew_unwegistew(&ideapad_acpi_dwivew);
}
moduwe_exit(ideapad_waptop_exit)

MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("IdeaPad ACPI Extwas");
MODUWE_WICENSE("GPW");
