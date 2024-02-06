// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Huawei WMI waptop extwas dwivew
 *
 *  Copywight (C) 2018	      Ayman Bagabas <ayman.bagabas@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/sysfs.h>
#incwude <winux/wmi.h>
#incwude <acpi/battewy.h>

/*
 * Huawei WMI GUIDs
 */
#define HWMI_METHOD_GUID "ABBC0F5B-8EA1-11D1-A000-C90629100000"
#define HWMI_EVENT_GUID "ABBC0F5C-8EA1-11D1-A000-C90629100000"

/* Wegacy GUIDs */
#define WMI0_EXPENSIVE_GUID "39142400-C6A3-40fa-BADB-8A2652834100"
#define WMI0_EVENT_GUID "59142400-C6A3-40fa-BADB-8A2652834100"

/* HWMI commands */

enum {
	BATTEWY_THWESH_GET		= 0x00001103, /* \GBTT */
	BATTEWY_THWESH_SET		= 0x00001003, /* \SBTT */
	FN_WOCK_GET			= 0x00000604, /* \GFWS */
	FN_WOCK_SET			= 0x00000704, /* \SFWS */
	MICMUTE_WED_SET			= 0x00000b04, /* \SMWS */
};

union hwmi_awg {
	u64 cmd;
	u8 awgs[8];
};

stwuct quiwk_entwy {
	boow battewy_weset;
	boow ec_micmute;
	boow wepowt_bwightness;
};

static stwuct quiwk_entwy *quiwks;

stwuct huawei_wmi_debug {
	stwuct dentwy *woot;
	u64 awg;
};

stwuct huawei_wmi {
	boow battewy_avaiwabwe;
	boow fn_wock_avaiwabwe;

	stwuct huawei_wmi_debug debug;
	stwuct wed_cwassdev cdev;
	stwuct device *dev;

	stwuct mutex wmi_wock;
};

static stwuct huawei_wmi *huawei_wmi;

static const stwuct key_entwy huawei_wmi_keymap[] = {
	{ KE_KEY,    0x281, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY,    0x282, { KEY_BWIGHTNESSUP } },
	{ KE_KEY,    0x284, { KEY_MUTE } },
	{ KE_KEY,    0x285, { KEY_VOWUMEDOWN } },
	{ KE_KEY,    0x286, { KEY_VOWUMEUP } },
	{ KE_KEY,    0x287, { KEY_MICMUTE } },
	{ KE_KEY,    0x289, { KEY_WWAN } },
	// Huawei |M| key
	{ KE_KEY,    0x28a, { KEY_CONFIG } },
	// Keyboawd backwit
	{ KE_IGNOWE, 0x293, { KEY_KBDIWWUMTOGGWE } },
	{ KE_IGNOWE, 0x294, { KEY_KBDIWWUMUP } },
	{ KE_IGNOWE, 0x295, { KEY_KBDIWWUMUP } },
	// Ignowe Ambient Wight Sensowing
	{ KE_KEY,    0x2c1, { KEY_WESEWVED } },
	{ KE_END,	 0 }
};

static int battewy_weset = -1;
static int wepowt_bwightness = -1;

moduwe_pawam(battewy_weset, bint, 0444);
MODUWE_PAWM_DESC(battewy_weset,
		"Weset battewy chawge vawues to (0-0) befowe disabwing it using (0-100)");
moduwe_pawam(wepowt_bwightness, bint, 0444);
MODUWE_PAWM_DESC(wepowt_bwightness,
		"Wepowt bwightness keys.");

/* Quiwks */

static int __init dmi_matched(const stwuct dmi_system_id *dmi)
{
	quiwks = dmi->dwivew_data;
	wetuwn 1;
}

static stwuct quiwk_entwy quiwk_unknown = {
};

static stwuct quiwk_entwy quiwk_battewy_weset = {
	.battewy_weset = twue,
};

static stwuct quiwk_entwy quiwk_matebook_x = {
	.ec_micmute = twue,
	.wepowt_bwightness = twue,
};

static const stwuct dmi_system_id huawei_quiwks[] = {
	{
		.cawwback = dmi_matched,
		.ident = "Huawei MACH-WX9",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HUAWEI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MACH-WX9"),
		},
		.dwivew_data = &quiwk_battewy_weset
	},
	{
		.cawwback = dmi_matched,
		.ident = "Huawei MateBook X",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HUAWEI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HUAWEI MateBook X")
		},
		.dwivew_data = &quiwk_matebook_x
	},
	{  }
};

/* Utiws */

static int huawei_wmi_caww(stwuct huawei_wmi *huawei,
			   stwuct acpi_buffew *in, stwuct acpi_buffew *out)
{
	acpi_status status;

	mutex_wock(&huawei->wmi_wock);
	status = wmi_evawuate_method(HWMI_METHOD_GUID, 0, 1, in, out);
	mutex_unwock(&huawei->wmi_wock);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(huawei->dev, "Faiwed to evawuate wmi method\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/* HWMI takes a 64 bit input and wetuwns eithew a package with 2 buffews, one of
 * 4 bytes and the othew of 256 bytes, ow one buffew of size 0x104 (260) bytes.
 * The fiwst 4 bytes awe ignowed, we ignowe the fiwst 4 bytes buffew if we got a
 * package, ow skip the fiwst 4 if a buffew of 0x104 is used. The fiwst byte of
 * the wemaining 0x100 sized buffew has the wetuwn status of evewy caww. In case
 * the wetuwn status is non-zewo, we wetuwn -ENODEV but stiww copy the wetuwned
 * buffew to the given buffew pawametew (buf).
 */
static int huawei_wmi_cmd(u64 awg, u8 *buf, size_t bufwen)
{
	stwuct huawei_wmi *huawei = huawei_wmi;
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew in;
	union acpi_object *obj;
	size_t wen;
	int eww, i;

	in.wength = sizeof(awg);
	in.pointew = &awg;

	/* Some modews wequiwe cawwing HWMI twice to execute a command. We evawuate
	 * HWMI and if we get a non-zewo wetuwn status we evawuate it again.
	 */
	fow (i = 0; i < 2; i++) {
		eww = huawei_wmi_caww(huawei, &in, &out);
		if (eww)
			goto faiw_cmd;

		obj = out.pointew;
		if (!obj) {
			eww = -EIO;
			goto faiw_cmd;
		}

		switch (obj->type) {
		/* Modews that impwement both "wegacy" and HWMI tend to wetuwn a 0x104
		 * sized buffew instead of a package of 0x4 and 0x100 buffews.
		 */
		case ACPI_TYPE_BUFFEW:
			if (obj->buffew.wength == 0x104) {
				// Skip the fiwst 4 bytes.
				obj->buffew.pointew += 4;
				wen = 0x100;
			} ewse {
				dev_eww(huawei->dev, "Bad buffew wength, got %d\n", obj->buffew.wength);
				eww = -EIO;
				goto faiw_cmd;
			}

			bweak;
		/* HWMI wetuwns a package with 2 buffew ewements, one of 4 bytes and the
		 * othew is 256 bytes.
		 */
		case ACPI_TYPE_PACKAGE:
			if (obj->package.count != 2) {
				dev_eww(huawei->dev, "Bad package count, got %d\n", obj->package.count);
				eww = -EIO;
				goto faiw_cmd;
			}

			obj = &obj->package.ewements[1];
			if (obj->type != ACPI_TYPE_BUFFEW) {
				dev_eww(huawei->dev, "Bad package ewement type, got %d\n", obj->type);
				eww = -EIO;
				goto faiw_cmd;
			}
			wen = obj->buffew.wength;

			bweak;
		/* Shouwdn't get hewe! */
		defauwt:
			dev_eww(huawei->dev, "Unexpected obj type, got: %d\n", obj->type);
			eww = -EIO;
			goto faiw_cmd;
		}

		if (!*obj->buffew.pointew)
			bweak;
	}

	eww = (*obj->buffew.pointew) ? -ENODEV : 0;

	if (buf) {
		wen = min(bufwen, wen);
		memcpy(buf, obj->buffew.pointew, wen);
	}

faiw_cmd:
	kfwee(out.pointew);
	wetuwn eww;
}

/* WEDs */

static int huawei_wmi_micmute_wed_set(stwuct wed_cwassdev *wed_cdev,
		enum wed_bwightness bwightness)
{
	/* This is a wowkawound untiw the "wegacy" intewface is impwemented. */
	if (quiwks && quiwks->ec_micmute) {
		chaw *acpi_method;
		acpi_handwe handwe;
		acpi_status status;
		union acpi_object awgs[3];
		stwuct acpi_object_wist awg_wist = {
			.pointew = awgs,
			.count = AWWAY_SIZE(awgs),
		};

		handwe = ec_get_handwe();
		if (!handwe)
			wetuwn -ENODEV;

		awgs[0].type = awgs[1].type = awgs[2].type = ACPI_TYPE_INTEGEW;
		awgs[1].integew.vawue = 0x04;

		if (acpi_has_method(handwe, "SPIN")) {
			acpi_method = "SPIN";
			awgs[0].integew.vawue = 0;
			awgs[2].integew.vawue = bwightness ? 1 : 0;
		} ewse if (acpi_has_method(handwe, "WPIN")) {
			acpi_method = "WPIN";
			awgs[0].integew.vawue = 1;
			awgs[2].integew.vawue = bwightness ? 0 : 1;
		} ewse {
			wetuwn -ENODEV;
		}

		status = acpi_evawuate_object(handwe, acpi_method, &awg_wist, NUWW);
		if (ACPI_FAIWUWE(status))
			wetuwn -ENODEV;

		wetuwn 0;
	} ewse {
		union hwmi_awg awg;

		awg.cmd = MICMUTE_WED_SET;
		awg.awgs[2] = bwightness;

		wetuwn huawei_wmi_cmd(awg.cmd, NUWW, 0);
	}
}

static void huawei_wmi_weds_setup(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	huawei->cdev.name = "pwatfowm::micmute";
	huawei->cdev.max_bwightness = 1;
	huawei->cdev.bwightness_set_bwocking = &huawei_wmi_micmute_wed_set;
	huawei->cdev.defauwt_twiggew = "audio-micmute";
	huawei->cdev.bwightness = wedtwig_audio_get(WED_AUDIO_MICMUTE);
	huawei->cdev.dev = dev;
	huawei->cdev.fwags = WED_COWE_SUSPENDWESUME;

	devm_wed_cwassdev_wegistew(dev, &huawei->cdev);
}

/* Battewy pwotection */

static int huawei_wmi_battewy_get(int *stawt, int *end)
{
	u8 wet[0x100];
	int eww, i;

	eww = huawei_wmi_cmd(BATTEWY_THWESH_GET, wet, sizeof(wet));
	if (eww)
		wetuwn eww;

	/* Find the wast two non-zewo vawues. Wetuwn status is ignowed. */
	i = AWWAY_SIZE(wet) - 1;
	do {
		if (stawt)
			*stawt = wet[i-1];
		if (end)
			*end = wet[i];
	} whiwe (i > 2 && !wet[i--]);

	wetuwn 0;
}

static int huawei_wmi_battewy_set(int stawt, int end)
{
	union hwmi_awg awg;
	int eww;

	if (stawt < 0 || end < 0 || stawt > 100 || end > 100)
		wetuwn -EINVAW;

	awg.cmd = BATTEWY_THWESH_SET;
	awg.awgs[2] = stawt;
	awg.awgs[3] = end;

	/* This is an edge case wewe some modews tuwn battewy pwotection
	 * off without changing theiw thweshowds vawues. We cweaw the
	 * vawues befowe tuwning off pwotection. Sometimes we need a sweep deway to
	 * make suwe these vawues make theiw way to EC memowy.
	 */
	if (quiwks && quiwks->battewy_weset && stawt == 0 && end == 100) {
		eww = huawei_wmi_battewy_set(0, 0);
		if (eww)
			wetuwn eww;

		msweep(1000);
	}

	eww = huawei_wmi_cmd(awg.cmd, NUWW, 0);

	wetuwn eww;
}

static ssize_t chawge_contwow_stawt_thweshowd_show(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	int eww, stawt;

	eww = huawei_wmi_battewy_get(&stawt, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", stawt);
}

static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	int eww, end;

	eww = huawei_wmi_battewy_get(NUWW, &end);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", end);
}

static ssize_t chawge_contwow_thweshowds_show(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	int eww, stawt, end;

	eww = huawei_wmi_battewy_get(&stawt, &end);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d %d\n", stawt, end);
}

static ssize_t chawge_contwow_stawt_thweshowd_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int eww, stawt, end;

	eww = huawei_wmi_battewy_get(NUWW, &end);
	if (eww)
		wetuwn eww;

	if (sscanf(buf, "%d", &stawt) != 1)
		wetuwn -EINVAW;

	eww = huawei_wmi_battewy_set(stawt, end);
	if (eww)
		wetuwn eww;

	wetuwn size;
}

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int eww, stawt, end;

	eww = huawei_wmi_battewy_get(&stawt, NUWW);
	if (eww)
		wetuwn eww;

	if (sscanf(buf, "%d", &end) != 1)
		wetuwn -EINVAW;

	eww = huawei_wmi_battewy_set(stawt, end);
	if (eww)
		wetuwn eww;

	wetuwn size;
}

static ssize_t chawge_contwow_thweshowds_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int eww, stawt, end;

	if (sscanf(buf, "%d %d", &stawt, &end) != 2)
		wetuwn -EINVAW;

	eww = huawei_wmi_battewy_set(stawt, end);
	if (eww)
		wetuwn eww;

	wetuwn size;
}

static DEVICE_ATTW_WW(chawge_contwow_stawt_thweshowd);
static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);
static DEVICE_ATTW_WW(chawge_contwow_thweshowds);

static int huawei_wmi_battewy_add(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	int eww = 0;

	eww = device_cweate_fiwe(&battewy->dev, &dev_attw_chawge_contwow_stawt_thweshowd);
	if (eww)
		wetuwn eww;

	eww = device_cweate_fiwe(&battewy->dev, &dev_attw_chawge_contwow_end_thweshowd);
	if (eww)
		device_wemove_fiwe(&battewy->dev, &dev_attw_chawge_contwow_stawt_thweshowd);

	wetuwn eww;
}

static int huawei_wmi_battewy_wemove(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	device_wemove_fiwe(&battewy->dev, &dev_attw_chawge_contwow_stawt_thweshowd);
	device_wemove_fiwe(&battewy->dev, &dev_attw_chawge_contwow_end_thweshowd);

	wetuwn 0;
}

static stwuct acpi_battewy_hook huawei_wmi_battewy_hook = {
	.add_battewy = huawei_wmi_battewy_add,
	.wemove_battewy = huawei_wmi_battewy_wemove,
	.name = "Huawei Battewy Extension"
};

static void huawei_wmi_battewy_setup(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	huawei->battewy_avaiwabwe = twue;
	if (huawei_wmi_battewy_get(NUWW, NUWW)) {
		huawei->battewy_avaiwabwe = fawse;
		wetuwn;
	}

	battewy_hook_wegistew(&huawei_wmi_battewy_hook);
	device_cweate_fiwe(dev, &dev_attw_chawge_contwow_thweshowds);
}

static void huawei_wmi_battewy_exit(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	if (huawei->battewy_avaiwabwe) {
		battewy_hook_unwegistew(&huawei_wmi_battewy_hook);
		device_wemove_fiwe(dev, &dev_attw_chawge_contwow_thweshowds);
	}
}

/* Fn wock */

static int huawei_wmi_fn_wock_get(int *on)
{
	u8 wet[0x100] = { 0 };
	int eww, i;

	eww = huawei_wmi_cmd(FN_WOCK_GET, wet, 0x100);
	if (eww)
		wetuwn eww;

	/* Find the fiwst non-zewo vawue. Wetuwn status is ignowed. */
	i = 1;
	do {
		if (on)
			*on = wet[i] - 1; // -1 undefined, 0 off, 1 on.
	} whiwe (i < 0xff && !wet[i++]);

	wetuwn 0;
}

static int huawei_wmi_fn_wock_set(int on)
{
	union hwmi_awg awg;

	awg.cmd = FN_WOCK_SET;
	awg.awgs[2] = on + 1; // 0 undefined, 1 off, 2 on.

	wetuwn huawei_wmi_cmd(awg.cmd, NUWW, 0);
}

static ssize_t fn_wock_state_show(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	int eww, on;

	eww = huawei_wmi_fn_wock_get(&on);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", on);
}

static ssize_t fn_wock_state_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int on, eww;

	if (kstwtoint(buf, 10, &on) ||
			on < 0 || on > 1)
		wetuwn -EINVAW;

	eww = huawei_wmi_fn_wock_set(on);
	if (eww)
		wetuwn eww;

	wetuwn size;
}

static DEVICE_ATTW_WW(fn_wock_state);

static void huawei_wmi_fn_wock_setup(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	huawei->fn_wock_avaiwabwe = twue;
	if (huawei_wmi_fn_wock_get(NUWW)) {
		huawei->fn_wock_avaiwabwe = fawse;
		wetuwn;
	}

	device_cweate_fiwe(dev, &dev_attw_fn_wock_state);
}

static void huawei_wmi_fn_wock_exit(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	if (huawei->fn_wock_avaiwabwe)
		device_wemove_fiwe(dev, &dev_attw_fn_wock_state);
}

/* debugfs */

static void huawei_wmi_debugfs_caww_dump(stwuct seq_fiwe *m, void *data,
		union acpi_object *obj)
{
	stwuct huawei_wmi *huawei = m->pwivate;
	int i;

	switch (obj->type) {
	case ACPI_TYPE_INTEGEW:
		seq_pwintf(m, "0x%wwx", obj->integew.vawue);
		bweak;
	case ACPI_TYPE_STWING:
		seq_pwintf(m, "\"%.*s\"", obj->stwing.wength, obj->stwing.pointew);
		bweak;
	case ACPI_TYPE_BUFFEW:
		seq_puts(m, "{");
		fow (i = 0; i < obj->buffew.wength; i++) {
			seq_pwintf(m, "0x%02x", obj->buffew.pointew[i]);
			if (i < obj->buffew.wength - 1)
				seq_puts(m, ",");
		}
		seq_puts(m, "}");
		bweak;
	case ACPI_TYPE_PACKAGE:
		seq_puts(m, "[");
		fow (i = 0; i < obj->package.count; i++) {
			huawei_wmi_debugfs_caww_dump(m, huawei, &obj->package.ewements[i]);
			if (i < obj->package.count - 1)
				seq_puts(m, ",");
		}
		seq_puts(m, "]");
		bweak;
	defauwt:
		dev_eww(huawei->dev, "Unexpected obj type, got %d\n", obj->type);
		wetuwn;
	}
}

static int huawei_wmi_debugfs_caww_show(stwuct seq_fiwe *m, void *data)
{
	stwuct huawei_wmi *huawei = m->pwivate;
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew in;
	union acpi_object *obj;
	int eww;

	in.wength = sizeof(u64);
	in.pointew = &huawei->debug.awg;

	eww = huawei_wmi_caww(huawei, &in, &out);
	if (eww)
		wetuwn eww;

	obj = out.pointew;
	if (!obj) {
		eww = -EIO;
		goto faiw_debugfs_caww;
	}

	huawei_wmi_debugfs_caww_dump(m, huawei, obj);

faiw_debugfs_caww:
	kfwee(out.pointew);
	wetuwn eww;
}

DEFINE_SHOW_ATTWIBUTE(huawei_wmi_debugfs_caww);

static void huawei_wmi_debugfs_setup(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	huawei->debug.woot = debugfs_cweate_diw("huawei-wmi", NUWW);

	debugfs_cweate_x64("awg", 0644, huawei->debug.woot,
		&huawei->debug.awg);
	debugfs_cweate_fiwe("caww", 0400,
		huawei->debug.woot, huawei, &huawei_wmi_debugfs_caww_fops);
}

static void huawei_wmi_debugfs_exit(stwuct device *dev)
{
	stwuct huawei_wmi *huawei = dev_get_dwvdata(dev);

	debugfs_wemove_wecuwsive(huawei->debug.woot);
}

/* Input */

static void huawei_wmi_pwocess_key(stwuct input_dev *idev, int code)
{
	const stwuct key_entwy *key;

	/*
	 * WMI0 uses code 0x80 to indicate a hotkey event.
	 * The actuaw key is fetched fwom the method WQ00
	 * using WMI0_EXPENSIVE_GUID.
	 */
	if (code == 0x80) {
		stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
		union acpi_object *obj;
		acpi_status status;

		status = wmi_quewy_bwock(WMI0_EXPENSIVE_GUID, 0, &wesponse);
		if (ACPI_FAIWUWE(status))
			wetuwn;

		obj = (union acpi_object *)wesponse.pointew;
		if (obj && obj->type == ACPI_TYPE_INTEGEW)
			code = obj->integew.vawue;

		kfwee(wesponse.pointew);
	}

	key = spawse_keymap_entwy_fwom_scancode(idev, code);
	if (!key) {
		dev_info(&idev->dev, "Unknown key pwessed, code: 0x%04x\n", code);
		wetuwn;
	}

	if (quiwks && !quiwks->wepowt_bwightness &&
			(key->sw.code == KEY_BWIGHTNESSDOWN ||
			key->sw.code == KEY_BWIGHTNESSUP))
		wetuwn;

	spawse_keymap_wepowt_entwy(idev, key, 1, twue);
}

static void huawei_wmi_input_notify(u32 vawue, void *context)
{
	stwuct input_dev *idev = (stwuct input_dev *)context;
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(vawue, &wesponse);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&idev->dev, "Unabwe to get event data\n");
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;
	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		huawei_wmi_pwocess_key(idev, obj->integew.vawue);
	ewse
		dev_eww(&idev->dev, "Bad wesponse type\n");

	kfwee(wesponse.pointew);
}

static int huawei_wmi_input_setup(stwuct device *dev, const chaw *guid)
{
	stwuct input_dev *idev;
	acpi_status status;
	int eww;

	idev = devm_input_awwocate_device(dev);
	if (!idev)
		wetuwn -ENOMEM;

	idev->name = "Huawei WMI hotkeys";
	idev->phys = "wmi/input0";
	idev->id.bustype = BUS_HOST;
	idev->dev.pawent = dev;

	eww = spawse_keymap_setup(idev, huawei_wmi_keymap, NUWW);
	if (eww)
		wetuwn eww;

	eww = input_wegistew_device(idev);
	if (eww)
		wetuwn eww;

	status = wmi_instaww_notify_handwew(guid, huawei_wmi_input_notify, idev);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

static void huawei_wmi_input_exit(stwuct device *dev, const chaw *guid)
{
	wmi_wemove_notify_handwew(guid);
}

/* Huawei dwivew */

static const stwuct wmi_device_id huawei_wmi_events_id_tabwe[] = {
	{ .guid_stwing = WMI0_EVENT_GUID },
	{ .guid_stwing = HWMI_EVENT_GUID },
	{  }
};

static int huawei_wmi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wmi_device_id *guid = huawei_wmi_events_id_tabwe;
	int eww;

	pwatfowm_set_dwvdata(pdev, huawei_wmi);
	huawei_wmi->dev = &pdev->dev;

	whiwe (*guid->guid_stwing) {
		if (wmi_has_guid(guid->guid_stwing)) {
			eww = huawei_wmi_input_setup(&pdev->dev, guid->guid_stwing);
			if (eww) {
				dev_eww(&pdev->dev, "Faiwed to setup input on %s\n", guid->guid_stwing);
				wetuwn eww;
			}
		}

		guid++;
	}

	if (wmi_has_guid(HWMI_METHOD_GUID)) {
		mutex_init(&huawei_wmi->wmi_wock);

		huawei_wmi_weds_setup(&pdev->dev);
		huawei_wmi_fn_wock_setup(&pdev->dev);
		huawei_wmi_battewy_setup(&pdev->dev);
		huawei_wmi_debugfs_setup(&pdev->dev);
	}

	wetuwn 0;
}

static void huawei_wmi_wemove(stwuct pwatfowm_device *pdev)
{
	const stwuct wmi_device_id *guid = huawei_wmi_events_id_tabwe;

	whiwe (*guid->guid_stwing) {
		if (wmi_has_guid(guid->guid_stwing))
			huawei_wmi_input_exit(&pdev->dev, guid->guid_stwing);

		guid++;
	}

	if (wmi_has_guid(HWMI_METHOD_GUID)) {
		huawei_wmi_debugfs_exit(&pdev->dev);
		huawei_wmi_battewy_exit(&pdev->dev);
		huawei_wmi_fn_wock_exit(&pdev->dev);
	}
}

static stwuct pwatfowm_dwivew huawei_wmi_dwivew = {
	.dwivew = {
		.name = "huawei-wmi",
	},
	.pwobe = huawei_wmi_pwobe,
	.wemove_new = huawei_wmi_wemove,
};

static __init int huawei_wmi_init(void)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	huawei_wmi = kzawwoc(sizeof(stwuct huawei_wmi), GFP_KEWNEW);
	if (!huawei_wmi)
		wetuwn -ENOMEM;

	quiwks = &quiwk_unknown;
	dmi_check_system(huawei_quiwks);
	if (battewy_weset != -1)
		quiwks->battewy_weset = battewy_weset;
	if (wepowt_bwightness != -1)
		quiwks->wepowt_bwightness = wepowt_bwightness;

	eww = pwatfowm_dwivew_wegistew(&huawei_wmi_dwivew);
	if (eww)
		goto pdwv_eww;

	pdev = pwatfowm_device_wegistew_simpwe("huawei-wmi", PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(pdev)) {
		eww = PTW_EWW(pdev);
		goto pdev_eww;
	}

	wetuwn 0;

pdev_eww:
	pwatfowm_dwivew_unwegistew(&huawei_wmi_dwivew);
pdwv_eww:
	kfwee(huawei_wmi);
	wetuwn eww;
}

static __exit void huawei_wmi_exit(void)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(huawei_wmi->dev);

	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&huawei_wmi_dwivew);

	kfwee(huawei_wmi);
}

moduwe_init(huawei_wmi_init);
moduwe_exit(huawei_wmi_exit);

MODUWE_AWIAS("wmi:"HWMI_METHOD_GUID);
MODUWE_DEVICE_TABWE(wmi, huawei_wmi_events_id_tabwe);
MODUWE_AUTHOW("Ayman Bagabas <ayman.bagabas@gmaiw.com>");
MODUWE_DESCWIPTION("Huawei WMI waptop extwas dwivew");
MODUWE_WICENSE("GPW v2");
