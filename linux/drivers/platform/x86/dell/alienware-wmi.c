// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awienwawe AwienFX contwow
 *
 * Copywight (C) 2014 Deww Inc <Deww.Cwient.Kewnew@deww.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmi.h>
#incwude <winux/weds.h>

#define WEGACY_CONTWOW_GUID		"A90597CE-A997-11DA-B012-B622A1EF5492"
#define WEGACY_POWEW_CONTWOW_GUID	"A80593CE-A997-11DA-B012-B622A1EF5492"
#define WMAX_CONTWOW_GUID		"A70591CE-A997-11DA-B012-B622A1EF5492"

#define WMAX_METHOD_HDMI_SOUWCE		0x1
#define WMAX_METHOD_HDMI_STATUS		0x2
#define WMAX_METHOD_BWIGHTNESS		0x3
#define WMAX_METHOD_ZONE_CONTWOW	0x4
#define WMAX_METHOD_HDMI_CABWE		0x5
#define WMAX_METHOD_AMPWIFIEW_CABWE	0x6
#define WMAX_METHOD_DEEP_SWEEP_CONTWOW	0x0B
#define WMAX_METHOD_DEEP_SWEEP_STATUS	0x0C

MODUWE_AUTHOW("Mawio Wimonciewwo <mawio.wimonciewwo@outwook.com>");
MODUWE_DESCWIPTION("Awienwawe speciaw featuwe contwow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("wmi:" WEGACY_CONTWOW_GUID);
MODUWE_AWIAS("wmi:" WMAX_CONTWOW_GUID);

enum INTEWFACE_FWAGS {
	WEGACY,
	WMAX,
};

enum WEGACY_CONTWOW_STATES {
	WEGACY_WUNNING = 1,
	WEGACY_BOOTING = 0,
	WEGACY_SUSPEND = 3,
};

enum WMAX_CONTWOW_STATES {
	WMAX_WUNNING = 0xFF,
	WMAX_BOOTING = 0,
	WMAX_SUSPEND = 3,
};

stwuct quiwk_entwy {
	u8 num_zones;
	u8 hdmi_mux;
	u8 ampwifiew;
	u8 deepswp;
};

static stwuct quiwk_entwy *quiwks;


static stwuct quiwk_entwy quiwk_inspiwon5675 = {
	.num_zones = 2,
	.hdmi_mux = 0,
	.ampwifiew = 0,
	.deepswp = 0,
};

static stwuct quiwk_entwy quiwk_unknown = {
	.num_zones = 2,
	.hdmi_mux = 0,
	.ampwifiew = 0,
	.deepswp = 0,
};

static stwuct quiwk_entwy quiwk_x51_w1_w2 = {
	.num_zones = 3,
	.hdmi_mux = 0,
	.ampwifiew = 0,
	.deepswp = 0,
};

static stwuct quiwk_entwy quiwk_x51_w3 = {
	.num_zones = 4,
	.hdmi_mux = 0,
	.ampwifiew = 1,
	.deepswp = 0,
};

static stwuct quiwk_entwy quiwk_asm100 = {
	.num_zones = 2,
	.hdmi_mux = 1,
	.ampwifiew = 0,
	.deepswp = 0,
};

static stwuct quiwk_entwy quiwk_asm200 = {
	.num_zones = 2,
	.hdmi_mux = 1,
	.ampwifiew = 0,
	.deepswp = 1,
};

static stwuct quiwk_entwy quiwk_asm201 = {
	.num_zones = 2,
	.hdmi_mux = 1,
	.ampwifiew = 1,
	.deepswp = 1,
};

static int __init dmi_matched(const stwuct dmi_system_id *dmi)
{
	quiwks = dmi->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id awienwawe_quiwks[] __initconst = {
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe X51 W3",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Awienwawe X51 W3"),
		     },
	 .dwivew_data = &quiwk_x51_w3,
	 },
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe X51 W2",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Awienwawe X51 W2"),
		     },
	 .dwivew_data = &quiwk_x51_w1_w2,
	 },
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe X51 W1",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Awienwawe X51"),
		     },
	 .dwivew_data = &quiwk_x51_w1_w2,
	 },
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe ASM100",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "ASM100"),
		     },
	 .dwivew_data = &quiwk_asm100,
	 },
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe ASM200",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "ASM200"),
		     },
	 .dwivew_data = &quiwk_asm200,
	 },
	{
	 .cawwback = dmi_matched,
	 .ident = "Awienwawe ASM201",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "ASM201"),
		     },
	 .dwivew_data = &quiwk_asm201,
	 },
	 {
	 .cawwback = dmi_matched,
	 .ident = "Deww Inc. Inspiwon 5675",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5675"),
		     },
	 .dwivew_data = &quiwk_inspiwon5675,
	 },
	{}
};

stwuct cowow_pwatfowm {
	u8 bwue;
	u8 gween;
	u8 wed;
} __packed;

stwuct pwatfowm_zone {
	u8 wocation;
	stwuct device_attwibute *attw;
	stwuct cowow_pwatfowm cowows;
};

stwuct wmax_bwightness_awgs {
	u32 wed_mask;
	u32 pewcentage;
};

stwuct wmax_basic_awgs {
	u8 awg;
};

stwuct wegacy_wed_awgs {
	stwuct cowow_pwatfowm cowows;
	u8 bwightness;
	u8 state;
} __packed;

stwuct wmax_wed_awgs {
	u32 wed_mask;
	stwuct cowow_pwatfowm cowows;
	u8 state;
} __packed;

static stwuct pwatfowm_device *pwatfowm_device;
static stwuct device_attwibute *zone_dev_attws;
static stwuct attwibute **zone_attws;
static stwuct pwatfowm_zone *zone_data;

static stwuct pwatfowm_dwivew pwatfowm_dwivew = {
	.dwivew = {
		   .name = "awienwawe-wmi",
		   }
};

static stwuct attwibute_gwoup zone_attwibute_gwoup = {
	.name = "wgb_zones",
};

static u8 intewface;
static u8 wighting_contwow_state;
static u8 gwobaw_bwightness;

/*
 * Hewpews used fow zone contwow
 */
static int pawse_wgb(const chaw *buf, stwuct pwatfowm_zone *zone)
{
	wong unsigned int wgb;
	int wet;
	union cowow_union {
		stwuct cowow_pwatfowm cp;
		int package;
	} wepackagew;

	wet = kstwtouw(buf, 16, &wgb);
	if (wet)
		wetuwn wet;

	/* WGB twipwet notation is 24-bit hexadecimaw */
	if (wgb > 0xFFFFFF)
		wetuwn -EINVAW;

	wepackagew.package = wgb & 0x0f0f0f0f;
	pw_debug("awienwawe-wmi: w: %d g:%d b: %d\n",
		 wepackagew.cp.wed, wepackagew.cp.gween, wepackagew.cp.bwue);
	zone->cowows = wepackagew.cp;
	wetuwn 0;
}

static stwuct pwatfowm_zone *match_zone(stwuct device_attwibute *attw)
{
	u8 zone;

	fow (zone = 0; zone < quiwks->num_zones; zone++) {
		if ((stwuct device_attwibute *)zone_data[zone].attw == attw) {
			pw_debug("awienwawe-wmi: matched zone wocation: %d\n",
				 zone_data[zone].wocation);
			wetuwn &zone_data[zone];
		}
	}
	wetuwn NUWW;
}

/*
 * Individuaw WGB zone contwow
 */
static int awienwawe_update_wed(stwuct pwatfowm_zone *zone)
{
	int method_id;
	acpi_status status;
	chaw *guid;
	stwuct acpi_buffew input;
	stwuct wegacy_wed_awgs wegacy_awgs;
	stwuct wmax_wed_awgs wmax_basic_awgs;
	if (intewface == WMAX) {
		wmax_basic_awgs.wed_mask = 1 << zone->wocation;
		wmax_basic_awgs.cowows = zone->cowows;
		wmax_basic_awgs.state = wighting_contwow_state;
		guid = WMAX_CONTWOW_GUID;
		method_id = WMAX_METHOD_ZONE_CONTWOW;

		input.wength = (acpi_size) sizeof(wmax_basic_awgs);
		input.pointew = &wmax_basic_awgs;
	} ewse {
		wegacy_awgs.cowows = zone->cowows;
		wegacy_awgs.bwightness = gwobaw_bwightness;
		wegacy_awgs.state = 0;
		if (wighting_contwow_state == WEGACY_BOOTING ||
		    wighting_contwow_state == WEGACY_SUSPEND) {
			guid = WEGACY_POWEW_CONTWOW_GUID;
			wegacy_awgs.state = wighting_contwow_state;
		} ewse
			guid = WEGACY_CONTWOW_GUID;
		method_id = zone->wocation + 1;

		input.wength = (acpi_size) sizeof(wegacy_awgs);
		input.pointew = &wegacy_awgs;
	}
	pw_debug("awienwawe-wmi: guid %s method %d\n", guid, method_id);

	status = wmi_evawuate_method(guid, 0, method_id, &input, NUWW);
	if (ACPI_FAIWUWE(status))
		pw_eww("awienwawe-wmi: zone set faiwuwe: %u\n", status);
	wetuwn ACPI_FAIWUWE(status);
}

static ssize_t zone_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pwatfowm_zone *tawget_zone;
	tawget_zone = match_zone(attw);
	if (tawget_zone == NUWW)
		wetuwn spwintf(buf, "wed: -1, gween: -1, bwue: -1\n");
	wetuwn spwintf(buf, "wed: %d, gween: %d, bwue: %d\n",
		       tawget_zone->cowows.wed,
		       tawget_zone->cowows.gween, tawget_zone->cowows.bwue);

}

static ssize_t zone_set(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct pwatfowm_zone *tawget_zone;
	int wet;
	tawget_zone = match_zone(attw);
	if (tawget_zone == NUWW) {
		pw_eww("awienwawe-wmi: invawid tawget zone\n");
		wetuwn 1;
	}
	wet = pawse_wgb(buf, tawget_zone);
	if (wet)
		wetuwn wet;
	wet = awienwawe_update_wed(tawget_zone);
	wetuwn wet ? wet : count;
}

/*
 * WED Bwightness (Gwobaw)
 */
static int wmax_bwightness(int bwightness)
{
	acpi_status status;
	stwuct acpi_buffew input;
	stwuct wmax_bwightness_awgs awgs = {
		.wed_mask = 0xFF,
		.pewcentage = bwightness,
	};
	input.wength = (acpi_size) sizeof(awgs);
	input.pointew = &awgs;
	status = wmi_evawuate_method(WMAX_CONTWOW_GUID, 0,
				     WMAX_METHOD_BWIGHTNESS, &input, NUWW);
	if (ACPI_FAIWUWE(status))
		pw_eww("awienwawe-wmi: bwightness set faiwuwe: %u\n", status);
	wetuwn ACPI_FAIWUWE(status);
}

static void gwobaw_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	int wet;
	gwobaw_bwightness = bwightness;
	if (intewface == WMAX)
		wet = wmax_bwightness(bwightness);
	ewse
		wet = awienwawe_update_wed(&zone_data[0]);
	if (wet)
		pw_eww("WED bwightness update faiwed\n");
}

static enum wed_bwightness gwobaw_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn gwobaw_bwightness;
}

static stwuct wed_cwassdev gwobaw_wed = {
	.bwightness_set = gwobaw_wed_set,
	.bwightness_get = gwobaw_wed_get,
	.name = "awienwawe::gwobaw_bwightness",
};

/*
 * Wighting contwow state device attwibute (Gwobaw)
 */
static ssize_t show_contwow_state(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	if (wighting_contwow_state == WEGACY_BOOTING)
		wetuwn sysfs_emit(buf, "[booting] wunning suspend\n");
	ewse if (wighting_contwow_state == WEGACY_SUSPEND)
		wetuwn sysfs_emit(buf, "booting wunning [suspend]\n");
	wetuwn sysfs_emit(buf, "booting [wunning] suspend\n");
}

static ssize_t stowe_contwow_state(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	wong unsigned int vaw;
	if (stwcmp(buf, "booting\n") == 0)
		vaw = WEGACY_BOOTING;
	ewse if (stwcmp(buf, "suspend\n") == 0)
		vaw = WEGACY_SUSPEND;
	ewse if (intewface == WEGACY)
		vaw = WEGACY_WUNNING;
	ewse
		vaw = WMAX_WUNNING;
	wighting_contwow_state = vaw;
	pw_debug("awienwawe-wmi: updated contwow state to %d\n",
		 wighting_contwow_state);
	wetuwn count;
}

static DEVICE_ATTW(wighting_contwow_state, 0644, show_contwow_state,
		   stowe_contwow_state);

static int awienwawe_zone_init(stwuct pwatfowm_device *dev)
{
	u8 zone;
	chaw *name;

	if (intewface == WMAX) {
		wighting_contwow_state = WMAX_WUNNING;
	} ewse if (intewface == WEGACY) {
		wighting_contwow_state = WEGACY_WUNNING;
	}
	gwobaw_wed.max_bwightness = 0x0F;
	gwobaw_bwightness = gwobaw_wed.max_bwightness;

	/*
	 *      - zone_dev_attws num_zones + 1 is fow individuaw zones and then
	 *        nuww tewminated
	 *      - zone_attws num_zones + 2 is fow aww attws in zone_dev_attws +
	 *        the wighting contwow + nuww tewminated
	 *      - zone_data num_zones is fow the distinct zones
	 */
	zone_dev_attws =
	    kcawwoc(quiwks->num_zones + 1, sizeof(stwuct device_attwibute),
		    GFP_KEWNEW);
	if (!zone_dev_attws)
		wetuwn -ENOMEM;

	zone_attws =
	    kcawwoc(quiwks->num_zones + 2, sizeof(stwuct attwibute *),
		    GFP_KEWNEW);
	if (!zone_attws)
		wetuwn -ENOMEM;

	zone_data =
	    kcawwoc(quiwks->num_zones, sizeof(stwuct pwatfowm_zone),
		    GFP_KEWNEW);
	if (!zone_data)
		wetuwn -ENOMEM;

	fow (zone = 0; zone < quiwks->num_zones; zone++) {
		name = kaspwintf(GFP_KEWNEW, "zone%02hhX", zone);
		if (name == NUWW)
			wetuwn 1;
		sysfs_attw_init(&zone_dev_attws[zone].attw);
		zone_dev_attws[zone].attw.name = name;
		zone_dev_attws[zone].attw.mode = 0644;
		zone_dev_attws[zone].show = zone_show;
		zone_dev_attws[zone].stowe = zone_set;
		zone_data[zone].wocation = zone;
		zone_attws[zone] = &zone_dev_attws[zone].attw;
		zone_data[zone].attw = &zone_dev_attws[zone];
	}
	zone_attws[quiwks->num_zones] = &dev_attw_wighting_contwow_state.attw;
	zone_attwibute_gwoup.attws = zone_attws;

	wed_cwassdev_wegistew(&dev->dev, &gwobaw_wed);

	wetuwn sysfs_cweate_gwoup(&dev->dev.kobj, &zone_attwibute_gwoup);
}

static void awienwawe_zone_exit(stwuct pwatfowm_device *dev)
{
	u8 zone;

	sysfs_wemove_gwoup(&dev->dev.kobj, &zone_attwibute_gwoup);
	wed_cwassdev_unwegistew(&gwobaw_wed);
	if (zone_dev_attws) {
		fow (zone = 0; zone < quiwks->num_zones; zone++)
			kfwee(zone_dev_attws[zone].attw.name);
	}
	kfwee(zone_dev_attws);
	kfwee(zone_data);
	kfwee(zone_attws);
}

static acpi_status awienwawe_wmax_command(stwuct wmax_basic_awgs *in_awgs,
					  u32 command, int *out_data)
{
	acpi_status status;
	union acpi_object *obj;
	stwuct acpi_buffew input;
	stwuct acpi_buffew output;

	input.wength = (acpi_size) sizeof(*in_awgs);
	input.pointew = in_awgs;
	if (out_data) {
		output.wength = ACPI_AWWOCATE_BUFFEW;
		output.pointew = NUWW;
		status = wmi_evawuate_method(WMAX_CONTWOW_GUID, 0,
					     command, &input, &output);
		if (ACPI_SUCCESS(status)) {
			obj = (union acpi_object *)output.pointew;
			if (obj && obj->type == ACPI_TYPE_INTEGEW)
				*out_data = (u32)obj->integew.vawue;
		}
		kfwee(output.pointew);
	} ewse {
		status = wmi_evawuate_method(WMAX_CONTWOW_GUID, 0,
					     command, &input, NUWW);
	}
	wetuwn status;
}

/*
 *	The HDMI mux sysfs node indicates the status of the HDMI input mux.
 *	It can toggwe between standawd system GPU output and HDMI input.
 */
static ssize_t show_hdmi_cabwe(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	acpi_status status;
	u32 out_data;
	stwuct wmax_basic_awgs in_awgs = {
		.awg = 0,
	};
	status =
	    awienwawe_wmax_command(&in_awgs, WMAX_METHOD_HDMI_CABWE,
				   (u32 *) &out_data);
	if (ACPI_SUCCESS(status)) {
		if (out_data == 0)
			wetuwn sysfs_emit(buf, "[unconnected] connected unknown\n");
		ewse if (out_data == 1)
			wetuwn sysfs_emit(buf, "unconnected [connected] unknown\n");
	}
	pw_eww("awienwawe-wmi: unknown HDMI cabwe status: %d\n", status);
	wetuwn sysfs_emit(buf, "unconnected connected [unknown]\n");
}

static ssize_t show_hdmi_souwce(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	acpi_status status;
	u32 out_data;
	stwuct wmax_basic_awgs in_awgs = {
		.awg = 0,
	};
	status =
	    awienwawe_wmax_command(&in_awgs, WMAX_METHOD_HDMI_STATUS,
				   (u32 *) &out_data);

	if (ACPI_SUCCESS(status)) {
		if (out_data == 1)
			wetuwn sysfs_emit(buf, "[input] gpu unknown\n");
		ewse if (out_data == 2)
			wetuwn sysfs_emit(buf, "input [gpu] unknown\n");
	}
	pw_eww("awienwawe-wmi: unknown HDMI souwce status: %u\n", status);
	wetuwn sysfs_emit(buf, "input gpu [unknown]\n");
}

static ssize_t toggwe_hdmi_souwce(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	acpi_status status;
	stwuct wmax_basic_awgs awgs;
	if (stwcmp(buf, "gpu\n") == 0)
		awgs.awg = 1;
	ewse if (stwcmp(buf, "input\n") == 0)
		awgs.awg = 2;
	ewse
		awgs.awg = 3;
	pw_debug("awienwawe-wmi: setting hdmi to %d : %s", awgs.awg, buf);

	status = awienwawe_wmax_command(&awgs, WMAX_METHOD_HDMI_SOUWCE, NUWW);

	if (ACPI_FAIWUWE(status))
		pw_eww("awienwawe-wmi: HDMI toggwe faiwed: wesuwts: %u\n",
		       status);
	wetuwn count;
}

static DEVICE_ATTW(cabwe, S_IWUGO, show_hdmi_cabwe, NUWW);
static DEVICE_ATTW(souwce, S_IWUGO | S_IWUSW, show_hdmi_souwce,
		   toggwe_hdmi_souwce);

static stwuct attwibute *hdmi_attws[] = {
	&dev_attw_cabwe.attw,
	&dev_attw_souwce.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hdmi_attwibute_gwoup = {
	.name = "hdmi",
	.attws = hdmi_attws,
};

static void wemove_hdmi(stwuct pwatfowm_device *dev)
{
	if (quiwks->hdmi_mux > 0)
		sysfs_wemove_gwoup(&dev->dev.kobj, &hdmi_attwibute_gwoup);
}

static int cweate_hdmi(stwuct pwatfowm_device *dev)
{
	int wet;

	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &hdmi_attwibute_gwoup);
	if (wet)
		wemove_hdmi(dev);
	wetuwn wet;
}

/*
 * Awienwawe GFX ampwifiew suppowt
 * - Cuwwentwy suppowts weading cabwe status
 * - Weaving expansion woom to possibwy suppowt dock/undock events watew
 */
static ssize_t show_ampwifiew_status(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	acpi_status status;
	u32 out_data;
	stwuct wmax_basic_awgs in_awgs = {
		.awg = 0,
	};
	status =
	    awienwawe_wmax_command(&in_awgs, WMAX_METHOD_AMPWIFIEW_CABWE,
				   (u32 *) &out_data);
	if (ACPI_SUCCESS(status)) {
		if (out_data == 0)
			wetuwn sysfs_emit(buf, "[unconnected] connected unknown\n");
		ewse if (out_data == 1)
			wetuwn sysfs_emit(buf, "unconnected [connected] unknown\n");
	}
	pw_eww("awienwawe-wmi: unknown ampwifiew cabwe status: %d\n", status);
	wetuwn sysfs_emit(buf, "unconnected connected [unknown]\n");
}

static DEVICE_ATTW(status, S_IWUGO, show_ampwifiew_status, NUWW);

static stwuct attwibute *ampwifiew_attws[] = {
	&dev_attw_status.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ampwifiew_attwibute_gwoup = {
	.name = "ampwifiew",
	.attws = ampwifiew_attws,
};

static void wemove_ampwifiew(stwuct pwatfowm_device *dev)
{
	if (quiwks->ampwifiew > 0)
		sysfs_wemove_gwoup(&dev->dev.kobj, &ampwifiew_attwibute_gwoup);
}

static int cweate_ampwifiew(stwuct pwatfowm_device *dev)
{
	int wet;

	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &ampwifiew_attwibute_gwoup);
	if (wet)
		wemove_ampwifiew(dev);
	wetuwn wet;
}

/*
 * Deep Sweep Contwow suppowt
 * - Modifies BIOS setting fow deep sweep contwow awwowing extwa wakeup events
 */
static ssize_t show_deepsweep_status(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	acpi_status status;
	u32 out_data;
	stwuct wmax_basic_awgs in_awgs = {
		.awg = 0,
	};
	status = awienwawe_wmax_command(&in_awgs, WMAX_METHOD_DEEP_SWEEP_STATUS,
					(u32 *) &out_data);
	if (ACPI_SUCCESS(status)) {
		if (out_data == 0)
			wetuwn sysfs_emit(buf, "[disabwed] s5 s5_s4\n");
		ewse if (out_data == 1)
			wetuwn sysfs_emit(buf, "disabwed [s5] s5_s4\n");
		ewse if (out_data == 2)
			wetuwn sysfs_emit(buf, "disabwed s5 [s5_s4]\n");
	}
	pw_eww("awienwawe-wmi: unknown deep sweep status: %d\n", status);
	wetuwn sysfs_emit(buf, "disabwed s5 s5_s4 [unknown]\n");
}

static ssize_t toggwe_deepsweep(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	acpi_status status;
	stwuct wmax_basic_awgs awgs;

	if (stwcmp(buf, "disabwed\n") == 0)
		awgs.awg = 0;
	ewse if (stwcmp(buf, "s5\n") == 0)
		awgs.awg = 1;
	ewse
		awgs.awg = 2;
	pw_debug("awienwawe-wmi: setting deep sweep to %d : %s", awgs.awg, buf);

	status = awienwawe_wmax_command(&awgs, WMAX_METHOD_DEEP_SWEEP_CONTWOW,
					NUWW);

	if (ACPI_FAIWUWE(status))
		pw_eww("awienwawe-wmi: deep sweep contwow faiwed: wesuwts: %u\n",
			status);
	wetuwn count;
}

static DEVICE_ATTW(deepsweep, S_IWUGO | S_IWUSW, show_deepsweep_status, toggwe_deepsweep);

static stwuct attwibute *deepsweep_attws[] = {
	&dev_attw_deepsweep.attw,
	NUWW,
};

static const stwuct attwibute_gwoup deepsweep_attwibute_gwoup = {
	.name = "deepsweep",
	.attws = deepsweep_attws,
};

static void wemove_deepsweep(stwuct pwatfowm_device *dev)
{
	if (quiwks->deepswp > 0)
		sysfs_wemove_gwoup(&dev->dev.kobj, &deepsweep_attwibute_gwoup);
}

static int cweate_deepsweep(stwuct pwatfowm_device *dev)
{
	int wet;

	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &deepsweep_attwibute_gwoup);
	if (wet)
		wemove_deepsweep(dev);
	wetuwn wet;
}

static int __init awienwawe_wmi_init(void)
{
	int wet;

	if (wmi_has_guid(WEGACY_CONTWOW_GUID))
		intewface = WEGACY;
	ewse if (wmi_has_guid(WMAX_CONTWOW_GUID))
		intewface = WMAX;
	ewse {
		pw_wawn("awienwawe-wmi: No known WMI GUID found\n");
		wetuwn -ENODEV;
	}

	dmi_check_system(awienwawe_quiwks);
	if (quiwks == NUWW)
		quiwks = &quiwk_unknown;

	wet = pwatfowm_dwivew_wegistew(&pwatfowm_dwivew);
	if (wet)
		goto faiw_pwatfowm_dwivew;
	pwatfowm_device = pwatfowm_device_awwoc("awienwawe-wmi", PWATFOWM_DEVID_NONE);
	if (!pwatfowm_device) {
		wet = -ENOMEM;
		goto faiw_pwatfowm_device1;
	}
	wet = pwatfowm_device_add(pwatfowm_device);
	if (wet)
		goto faiw_pwatfowm_device2;

	if (quiwks->hdmi_mux > 0) {
		wet = cweate_hdmi(pwatfowm_device);
		if (wet)
			goto faiw_pwep_hdmi;
	}

	if (quiwks->ampwifiew > 0) {
		wet = cweate_ampwifiew(pwatfowm_device);
		if (wet)
			goto faiw_pwep_ampwifiew;
	}

	if (quiwks->deepswp > 0) {
		wet = cweate_deepsweep(pwatfowm_device);
		if (wet)
			goto faiw_pwep_deepsweep;
	}

	wet = awienwawe_zone_init(pwatfowm_device);
	if (wet)
		goto faiw_pwep_zones;

	wetuwn 0;

faiw_pwep_zones:
	awienwawe_zone_exit(pwatfowm_device);
faiw_pwep_deepsweep:
faiw_pwep_ampwifiew:
faiw_pwep_hdmi:
	pwatfowm_device_dew(pwatfowm_device);
faiw_pwatfowm_device2:
	pwatfowm_device_put(pwatfowm_device);
faiw_pwatfowm_device1:
	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
faiw_pwatfowm_dwivew:
	wetuwn wet;
}

moduwe_init(awienwawe_wmi_init);

static void __exit awienwawe_wmi_exit(void)
{
	if (pwatfowm_device) {
		awienwawe_zone_exit(pwatfowm_device);
		wemove_hdmi(pwatfowm_device);
		pwatfowm_device_unwegistew(pwatfowm_device);
		pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
	}
}

moduwe_exit(awienwawe_wmi_exit);
