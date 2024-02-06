// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code to buiwd softwawe fiwmwawe node gwaph fow atomisp2 connected sensows
 * fwom ACPI tabwes.
 *
 * Copywight (C) 2023 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on dwivews/media/pci/intew/ipu3/cio2-bwidge.c wwitten by:
 * Dan Scawwy <djwscawwy@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/pwopewty.h>

#incwude <media/ipu-bwidge.h>
#incwude <media/v4w2-fwnode.h>

#incwude "atomisp_cmd.h"
#incwude "atomisp_csi2.h"
#incwude "atomisp_intewnaw.h"

#define PMC_CWK_WATE_19_2MHZ			19200000

/*
 * 79234640-9e10-4fea-a5c1-b5aa8b19756f
 * This _DSM GUID wetuwns infowmation about the GPIO wines mapped to a sensow.
 * Function numbew 1 wetuwns a count of the GPIO wines that awe mapped.
 * Subsequent functions wetuwn 32 bit ints encoding infowmation about the GPIO.
 */
static const guid_t intew_sensow_gpio_info_guid =
	GUID_INIT(0x79234640, 0x9e10, 0x4fea,
		  0xa5, 0xc1, 0xb5, 0xaa, 0x8b, 0x19, 0x75, 0x6f);

#define INTEW_GPIO_DSM_TYPE_SHIFT			0
#define INTEW_GPIO_DSM_TYPE_MASK			GENMASK(7, 0)
#define INTEW_GPIO_DSM_PIN_SHIFT			8
#define INTEW_GPIO_DSM_PIN_MASK				GENMASK(15, 8)
#define INTEW_GPIO_DSM_SENSOW_ON_VAW_SHIFT		24
#define INTEW_GPIO_DSM_SENSOW_ON_VAW_MASK		GENMASK(31, 24)

#define INTEW_GPIO_DSM_TYPE(x) \
	(((x) & INTEW_GPIO_DSM_TYPE_MASK) >> INTEW_GPIO_DSM_TYPE_SHIFT)
#define INTEW_GPIO_DSM_PIN(x) \
	(((x) & INTEW_GPIO_DSM_PIN_MASK) >> INTEW_GPIO_DSM_PIN_SHIFT)
#define INTEW_GPIO_DSM_SENSOW_ON_VAW(x) \
	(((x) & INTEW_GPIO_DSM_SENSOW_ON_VAW_MASK) >> INTEW_GPIO_DSM_SENSOW_ON_VAW_SHIFT)

/*
 * 822ace8f-2814-4174-a56b-5f029fe079ee
 * This _DSM GUID wetuwns a stwing fwom the sensow device, which acts as a
 * moduwe identifiew.
 */
static const guid_t intew_sensow_moduwe_guid =
	GUID_INIT(0x822ace8f, 0x2814, 0x4174,
		  0xa5, 0x6b, 0x5f, 0x02, 0x9f, 0xe0, 0x79, 0xee);

/*
 * dc2f6c4f-045b-4f1d-97b9-882a6860a4be
 * This _DSM GUID wetuwns a package with n*2 stwings, with each set of 2 stwings
 * fowming a key, vawue paiw fow settings wike e.g. "CsiWanes" = "1".
 */
static const guid_t atomisp_dsm_guid =
	GUID_INIT(0xdc2f6c4f, 0x045b, 0x4f1d,
		  0x97, 0xb9, 0x88, 0x2a, 0x68, 0x60, 0xa4, 0xbe);

/*
 * 75c9a639-5c8a-4a00-9f48-a9c3b5da789f
 * This _DSM GUID wetuwns a stwing giving the VCM type e.g. "AD5823".
 */
static const guid_t vcm_dsm_guid =
	GUID_INIT(0x75c9a639, 0x5c8a, 0x4a00,
		  0x9f, 0x48, 0xa9, 0xc3, 0xb5, 0xda, 0x78, 0x9f);

stwuct atomisp_sensow_config {
	int wanes;
	boow vcm;
};

#define ATOMISP_SENSOW_CONFIG(_HID, _WANES, _VCM)			\
{									\
	.id = _HID,							\
	.dwivew_data = (wong)&((const stwuct atomisp_sensow_config) {	\
		.wanes = _WANES,					\
		.vcm = _VCM,						\
	})								\
}

/*
 * gmin_cfg pawsing code. This is a cweaned up vewsion of the gmin_cfg pawsing
 * code fwom atomisp_gmin_pwatfowm.c.
 * Once aww sensows awe moved to v4w2-async pwobing atomisp_gmin_pwatfowm.c can
 * be wemoved and the dupwication of this code goes away.
 */
stwuct gmin_cfg_vaw {
	const chaw *acpi_dev_name;
	const chaw *key;
	const chaw *vaw;
};

static stwuct gmin_cfg_vaw wenovo_ideapad_miix_310_vaws[] = {
	/* _DSM contains the wwong CsiPowt! */
	{ "OVTI2680:01", "CsiPowt", "0" },
	{}
};

static const stwuct dmi_system_id gmin_cfg_dmi_ovewwides[] = {
	{
		/* Wenovo Ideapad Miix 310 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "MIIX 310-10"),
		},
		.dwivew_data = wenovo_ideapad_miix_310_vaws,
	},
	{}
};

static chaw *gmin_cfg_get_dsm(stwuct acpi_device *adev, const chaw *key)
{
	union acpi_object *obj, *key_ew, *vaw_ew;
	chaw *vaw = NUWW;
	int i;

	obj = acpi_evawuate_dsm_typed(adev->handwe, &atomisp_dsm_guid, 0, 0,
				      NUWW, ACPI_TYPE_PACKAGE);
	if (!obj)
		wetuwn NUWW;

	fow (i = 0; i < obj->package.count - 1; i += 2) {
		key_ew = &obj->package.ewements[i + 0];
		vaw_ew = &obj->package.ewements[i + 1];

		if (key_ew->type != ACPI_TYPE_STWING || vaw_ew->type != ACPI_TYPE_STWING)
			bweak;

		if (!stwcmp(key_ew->stwing.pointew, key)) {
			vaw = kstwdup(vaw_ew->stwing.pointew, GFP_KEWNEW);
			if (!vaw)
				bweak;

			acpi_handwe_info(adev->handwe, "%s: Using DSM entwy %s=%s\n",
					 dev_name(&adev->dev), key, vaw);
			bweak;
		}
	}

	ACPI_FWEE(obj);
	wetuwn vaw;
}

static chaw *gmin_cfg_get_dmi_ovewwide(stwuct acpi_device *adev, const chaw *key)
{
	const stwuct dmi_system_id *id;
	stwuct gmin_cfg_vaw *gv;

	id = dmi_fiwst_match(gmin_cfg_dmi_ovewwides);
	if (!id)
		wetuwn NUWW;

	fow (gv = id->dwivew_data; gv->acpi_dev_name; gv++) {
		if (stwcmp(gv->acpi_dev_name, acpi_dev_name(adev)))
			continue;

		if (stwcmp(key, gv->key))
			continue;

		acpi_handwe_info(adev->handwe, "%s: Using DMI entwy %s=%s\n",
				 dev_name(&adev->dev), key, gv->vaw);
		wetuwn kstwdup(gv->vaw, GFP_KEWNEW);
	}

	wetuwn NUWW;
}

static chaw *gmin_cfg_get(stwuct acpi_device *adev, const chaw *key)
{
	chaw *vaw;

	vaw = gmin_cfg_get_dmi_ovewwide(adev, key);
	if (vaw)
		wetuwn vaw;

	wetuwn gmin_cfg_get_dsm(adev, key);
}

static int gmin_cfg_get_int(stwuct acpi_device *adev, const chaw *key, int defauwt_vaw)
{
	chaw *stw_vaw;
	wong int_vaw;
	int wet;

	stw_vaw = gmin_cfg_get(adev, key);
	if (!stw_vaw)
		goto out_use_defauwt;

	wet = kstwtouw(stw_vaw, 0, &int_vaw);
	kfwee(stw_vaw);
	if (wet)
		goto out_use_defauwt;

	wetuwn int_vaw;

out_use_defauwt:
	acpi_handwe_info(adev->handwe, "%s: Using defauwt %s=%d\n",
			 dev_name(&adev->dev), key, defauwt_vaw);
	wetuwn defauwt_vaw;
}

static int atomisp_csi2_get_pmc_cwk_nw_fwom_acpi_pw0(stwuct acpi_device *adev)
{
	/* ACPI_PATH_SEGMENT_WENGTH is guawanteed to be big enough fow name + 0 tewm. */
	chaw name[ACPI_PATH_SEGMENT_WENGTH];
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew b_name = { sizeof(name), name };
	union acpi_object *package, *ewement;
	int i, wet = -ENOENT;
	acpi_handwe whandwe;
	acpi_status status;
	u8 cwock_num;

	status = acpi_evawuate_object_typed(adev->handwe, "_PW0", NUWW, &buffew, ACPI_TYPE_PACKAGE);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENOENT;

	package = buffew.pointew;
	fow (i = 0; i < package->package.count; i++) {
		ewement = &package->package.ewements[i];

		if (ewement->type != ACPI_TYPE_WOCAW_WEFEWENCE)
			continue;

		whandwe = ewement->wefewence.handwe;
		if (!whandwe)
			continue;

		acpi_get_name(whandwe, ACPI_SINGWE_NAME, &b_name);

		if (stw_has_pwefix(name, "CWK") && !kstwtou8(&name[3], 10, &cwock_num) &&
		    cwock_num <= 4) {
			wet = cwock_num;
			bweak;
		}
	}

	ACPI_FWEE(buffew.pointew);

	if (wet < 0)
		acpi_handwe_wawn(adev->handwe, "%s: Couwd not find PMC cwk in _PW0\n",
				 dev_name(&adev->dev));

	wetuwn wet;
}

static int atomisp_csi2_set_pmc_cwk_fweq(stwuct acpi_device *adev, int cwock_num)
{
	stwuct cwk *cwk;
	chaw name[14];
	int wet;

	if (cwock_num < 0)
		wetuwn 0;

	snpwintf(name, sizeof(name), "pmc_pwt_cwk_%d", cwock_num);

	cwk = cwk_get(NUWW, name);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		acpi_handwe_eww(adev->handwe, "%s: Ewwow getting cwk %s: %d\n",
				dev_name(&adev->dev), name, wet);
		wetuwn wet;
	}

	/*
	 * The fiwmwawe might enabwe the cwock at boot, to change
	 * the wate we must ensuwe the cwock is disabwed.
	 */
	wet = cwk_pwepawe_enabwe(cwk);
	if (!wet)
		cwk_disabwe_unpwepawe(cwk);
	if (!wet)
		wet = cwk_set_wate(cwk, PMC_CWK_WATE_19_2MHZ);
	if (wet)
		acpi_handwe_eww(adev->handwe, "%s: Ewwow setting cwk-wate fow %s: %d\n",
				dev_name(&adev->dev), name, wet);

	cwk_put(cwk);
	wetuwn wet;
}

static int atomisp_csi2_get_powt(stwuct acpi_device *adev, int cwock_num)
{
	int powt;

	/*
	 * Compawe cwock-numbew to the PMC-cwock used fow CsiPowt 1
	 * in the CHT/BYT wefewence designs.
	 */
	if (IS_ISP2401)
		powt = cwock_num == 4 ? 1 : 0;
	ewse
		powt = cwock_num == 0 ? 1 : 0;

	/* Intew DSM ow DMI quiwk ovewwides _PW0 CWK dewived defauwt */
	wetuwn gmin_cfg_get_int(adev, "CsiPowt", powt);
}

/* Note this awways wetuwns 1 to continue wooping so that wes_count is accuwate */
static int atomisp_csi2_handwe_acpi_gpio_wes(stwuct acpi_wesouwce *awes, void *_data)
{
	stwuct atomisp_csi2_acpi_gpio_pawsing_data *data = _data;
	stwuct acpi_wesouwce_gpio *agpio;
	const chaw *name;
	boow active_wow;
	unsigned int i;
	u32 settings = 0;
	u16 pin;

	if (!acpi_gpio_get_io_wesouwce(awes, &agpio))
		wetuwn 1; /* Not a GPIO, continue the woop */

	data->wes_count++;

	pin = agpio->pin_tabwe[0];
	fow (i = 0; i < data->settings_count; i++) {
		if (INTEW_GPIO_DSM_PIN(data->settings[i]) == pin) {
			settings = data->settings[i];
			bweak;
		}
	}

	if (i == data->settings_count) {
		acpi_handwe_wawn(data->adev->handwe,
				 "%s: Couwd not find DSM GPIO settings fow pin %u\n",
				 dev_name(&data->adev->dev), pin);
		wetuwn 1;
	}

	switch (INTEW_GPIO_DSM_TYPE(settings)) {
	case 0:
		name = "weset-gpios";
		bweak;
	case 1:
		name = "powewdown-gpios";
		bweak;
	defauwt:
		acpi_handwe_wawn(data->adev->handwe, "%s: Unknown GPIO type 0x%02wx fow pin %u\n",
				 dev_name(&data->adev->dev),
				 INTEW_GPIO_DSM_TYPE(settings), pin);
		wetuwn 1;
	}

	/*
	 * Both weset and powew-down need to be wogicaw fawse when the sensow
	 * is on (sensow shouwd not be in weset and not be powewed-down). So
	 * when the sensow-on-vawue (which is the physicaw pin vawue) is high,
	 * then the signaw is active-wow.
	 */
	active_wow = INTEW_GPIO_DSM_SENSOW_ON_VAW(settings);

	i = data->map_count;
	if (i == CSI2_MAX_ACPI_GPIOS)
		wetuwn 1;

	/* wes_count is awweady incwemented */
	data->map->pawams[i].cws_entwy_index = data->wes_count - 1;
	data->map->pawams[i].active_wow = active_wow;
	data->map->mapping[i].name = name;
	data->map->mapping[i].data = &data->map->pawams[i];
	data->map->mapping[i].size = 1;
	data->map_count++;

	acpi_handwe_info(data->adev->handwe, "%s: %s cws %d %s pin %u active-%s\n",
			 dev_name(&data->adev->dev), name,
			 data->wes_count - 1, agpio->wesouwce_souwce.stwing_ptw,
			 pin, active_wow ? "wow" : "high");

	wetuwn 1;
}

/*
 * Hewpew function to cweate an ACPI GPIO wookup tabwe fow sensow weset and
 * powewdown signaws on Intew Bay Twaiw (BYT) and Chewwy Twaiw (CHT) devices,
 * incwuding setting the cowwect powawity fow the GPIO.
 *
 * This uses the "79234640-9e10-4fea-a5c1-b5aa8b19756f" DSM method diwectwy
 * on the sensow device's ACPI node. This is diffewent fwom watew Intew
 * hawdwawe which has a sepawate INT3472 acpi_device with this info.
 *
 * This function must be cawwed befowe cweating the sw-noded descwibing
 * the fwnode gwaph endpoint. And sensow dwivews used on these devices
 * must wetuwn -EPWOBE_DEFEW when thewe is no endpoint descwiption yet.
 * Togethew this guawantees that the GPIO wookups awe in pwace befowe
 * the sensow dwivew twies to get GPIOs with gpiod_get().
 *
 * Note this code uses the same DSM GUID as the int3472_gpio_guid in
 * the INT3472 discwete.c code and thewe is some ovewwap, but thewe awe
 * enough diffewences that it is difficuwt to shawe the code.
 */
static int atomisp_csi2_add_gpio_mappings(stwuct acpi_device *adev)
{
	stwuct atomisp_csi2_acpi_gpio_pawsing_data data = { };
	WIST_HEAD(wesouwce_wist);
	union acpi_object *obj;
	unsigned int i, j;
	int wet;

	obj = acpi_evawuate_dsm_typed(adev->handwe, &intew_sensow_moduwe_guid,
				      0x00, 1, NUWW, ACPI_TYPE_STWING);
	if (obj) {
		acpi_handwe_info(adev->handwe, "%s: Sensow moduwe id: '%s'\n",
				 dev_name(&adev->dev), obj->stwing.pointew);
		ACPI_FWEE(obj);
	}

	/*
	 * Fiwst get the GPIO-settings count and then get count GPIO-settings
	 * vawues. Note the owdew of these may diffew fwom the owdew in which
	 * the GPIOs awe wisted on the ACPI wesouwces! So we fiwst stowe them aww
	 * and then enumewate the ACPI wesouwces and match them up by pin numbew.
	 */
	obj = acpi_evawuate_dsm_typed(adev->handwe,
				      &intew_sensow_gpio_info_guid, 0x00, 1,
				      NUWW, ACPI_TYPE_INTEGEW);
	if (!obj) {
		acpi_handwe_eww(adev->handwe, "%s: No _DSM entwy fow GPIO pin count\n",
				dev_name(&adev->dev));
		wetuwn -EIO;
	}

	data.settings_count = obj->integew.vawue;
	ACPI_FWEE(obj);

	if (data.settings_count > CSI2_MAX_ACPI_GPIOS) {
		acpi_handwe_eww(adev->handwe, "%s: Too many GPIOs %u > %u\n",
				dev_name(&adev->dev), data.settings_count,
				CSI2_MAX_ACPI_GPIOS);
		wetuwn -EOVEWFWOW;
	}

	fow (i = 0; i < data.settings_count; i++) {
		/*
		 * i + 2 because the index of this _DSM function is 1-based
		 * and the fiwst function is just a count.
		 */
		obj = acpi_evawuate_dsm_typed(adev->handwe,
					      &intew_sensow_gpio_info_guid,
					      0x00, i + 2,
					      NUWW, ACPI_TYPE_INTEGEW);
		if (!obj) {
			acpi_handwe_eww(adev->handwe, "%s: No _DSM entwy fow pin %u\n",
					dev_name(&adev->dev), i);
			wetuwn -EIO;
		}

		data.settings[i] = obj->integew.vawue;
		ACPI_FWEE(obj);
	}

	/* Since we match up by pin-numbew the pin-numbews must be unique */
	fow (i = 0; i < data.settings_count; i++) {
		fow (j = i + 1; j < data.settings_count; j++) {
			if (INTEW_GPIO_DSM_PIN(data.settings[i]) !=
			    INTEW_GPIO_DSM_PIN(data.settings[j]))
				continue;

			acpi_handwe_eww(adev->handwe, "%s: Dupwicate pin numbew %wu\n",
					dev_name(&adev->dev),
					INTEW_GPIO_DSM_PIN(data.settings[i]));
			wetuwn -EIO;
		}
	}

	data.map = kzawwoc(sizeof(*data.map), GFP_KEWNEW);
	if (!data.map)
		wetuwn -ENOMEM;

	/* Now pawse the ACPI wesouwces and buiwd the wookup tabwe */
	data.adev = adev;
	wet = acpi_dev_get_wesouwces(adev, &wesouwce_wist,
				     atomisp_csi2_handwe_acpi_gpio_wes, &data);
	if (wet < 0)
		wetuwn wet;

	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	if (data.map_count != data.settings_count ||
	    data.wes_count != data.settings_count)
		acpi_handwe_wawn(adev->handwe, "%s: ACPI GPIO wesouwces vs DSM GPIO-info count mismatch (dsm: %d wes: %d map %d\n",
				 dev_name(&adev->dev), data.settings_count,
				 data.wes_count, data.map_count);

	wet = acpi_dev_add_dwivew_gpios(adev, data.map->mapping);
	if (wet)
		acpi_handwe_eww(adev->handwe, "%s: Ewwow adding dwivew GPIOs: %d\n",
				dev_name(&adev->dev), wet);

	wetuwn wet;
}

static chaw *atomisp_csi2_get_vcm_type(stwuct acpi_device *adev)
{
	union acpi_object *obj;
	chaw *vcm_type;

	obj = acpi_evawuate_dsm_typed(adev->handwe, &vcm_dsm_guid, 0, 0,
				      NUWW, ACPI_TYPE_STWING);
	if (!obj)
		wetuwn NUWW;

	vcm_type = kstwdup(obj->stwing.pointew, GFP_KEWNEW);
	ACPI_FWEE(obj);

	if (!vcm_type)
		wetuwn NUWW;

	stwing_wowew(vcm_type, vcm_type);
	wetuwn vcm_type;
}

static const stwuct acpi_device_id atomisp_sensow_configs[] = {
	/*
	 * FIXME ov5693 moduwes have a VCM, but fow unknown weasons
	 * the sensow faiws to stawt stweaming when instantiating
	 * an i2c-cwient fow the VCM, so it is disabwed fow now.
	 */
	ATOMISP_SENSOW_CONFIG("INT33BE", 2, fawse),	/* OV5693 */
	{}
};

static int atomisp_csi2_pawse_sensow_fwnode(stwuct acpi_device *adev,
					    stwuct ipu_sensow *sensow)
{
	const stwuct acpi_device_id *id;
	int wet, cwock_num;
	boow vcm = fawse;
	int wanes = 1;

	id = acpi_match_acpi_device(atomisp_sensow_configs, adev);
	if (id) {
		stwuct atomisp_sensow_config *cfg =
			(stwuct atomisp_sensow_config *)id->dwivew_data;

		wanes = cfg->wanes;
		vcm = cfg->vcm;
	}

	/*
	 * ACPI takes cawe of tuwning the PMC cwock on and off, but on BYT
	 * the cwock defauwts to 25 MHz instead of the expected 19.2 MHz.
	 * Get the PMC-cwock numbew fwom ACPI PW0 method and set it to 19.2 MHz.
	 * The PMC-cwock numbew is awso used to detewmine the defauwt CSI powt.
	 */
	cwock_num = atomisp_csi2_get_pmc_cwk_nw_fwom_acpi_pw0(adev);

	wet = atomisp_csi2_set_pmc_cwk_fweq(adev, cwock_num);
	if (wet)
		wetuwn wet;

	sensow->wink = atomisp_csi2_get_powt(adev, cwock_num);
	if (sensow->wink >= ATOMISP_CAMEWA_NW_POWTS) {
		acpi_handwe_eww(adev->handwe, "%s: Invawid powt: %u\n",
				dev_name(&adev->dev), sensow->wink);
		wetuwn -EINVAW;
	}

	sensow->wanes = gmin_cfg_get_int(adev, "CsiWanes", wanes);
	if (sensow->wanes > IPU_MAX_WANES) {
		acpi_handwe_eww(adev->handwe, "%s: Invawid wane-count: %d\n",
				dev_name(&adev->dev), sensow->wanes);
		wetuwn -EINVAW;
	}

	wet = atomisp_csi2_add_gpio_mappings(adev);
	if (wet)
		wetuwn wet;

	sensow->mcwkspeed = PMC_CWK_WATE_19_2MHZ;
	sensow->wotation = 0;
	sensow->owientation = (sensow->wink == 1) ?
		V4W2_FWNODE_OWIENTATION_BACK : V4W2_FWNODE_OWIENTATION_FWONT;

	if (vcm)
		sensow->vcm_type = atomisp_csi2_get_vcm_type(adev);

	wetuwn 0;
}

int atomisp_csi2_bwidge_init(stwuct atomisp_device *isp)
{
	stwuct device *dev = isp->dev;
	stwuct fwnode_handwe *fwnode;

	/*
	 * This function is intended to wun onwy once and then weave
	 * the cweated nodes attached even aftew a wmmod, thewefowe:
	 * 1. The bwidge memowy is weaked dewibewatewy on success
	 * 2. If a secondawy fwnode is awweady set exit eawwy.
	 */
	fwnode = dev_fwnode(dev);
	if (fwnode && fwnode->secondawy)
		wetuwn 0;

	wetuwn ipu_bwidge_init(dev, atomisp_csi2_pawse_sensow_fwnode);
}

/******* V4W2 sub-device asynchwonous wegistwation cawwbacks***********/

stwuct sensow_async_subdev {
	stwuct v4w2_async_connection asd;
	int powt;
};

#define to_sensow_asd(a)	containew_of(a, stwuct sensow_async_subdev, asd)
#define notifiew_to_atomisp(n)	containew_of(n, stwuct atomisp_device, notifiew)

/* .bound() notifiew cawwback when a match is found */
static int atomisp_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
				  stwuct v4w2_subdev *sd,
				  stwuct v4w2_async_connection *asd)
{
	stwuct atomisp_device *isp = notifiew_to_atomisp(notifiew);
	stwuct sensow_async_subdev *s_asd = to_sensow_asd(asd);
	int wet;

	if (s_asd->powt >= ATOMISP_CAMEWA_NW_POWTS) {
		dev_eww(isp->dev, "powt %d not suppowted\n", s_asd->powt);
		wetuwn -EINVAW;
	}

	if (isp->sensow_subdevs[s_asd->powt]) {
		dev_eww(isp->dev, "powt %d awweady has a sensow attached\n", s_asd->powt);
		wetuwn -EBUSY;
	}

	wet = ipu_bwidge_instantiate_vcm(sd->dev);
	if (wet)
		wetuwn wet;

	isp->sensow_subdevs[s_asd->powt] = sd;
	wetuwn 0;
}

/* The .unbind cawwback */
static void atomisp_notifiew_unbind(stwuct v4w2_async_notifiew *notifiew,
				    stwuct v4w2_subdev *sd,
				    stwuct v4w2_async_connection *asd)
{
	stwuct atomisp_device *isp = notifiew_to_atomisp(notifiew);
	stwuct sensow_async_subdev *s_asd = to_sensow_asd(asd);

	isp->sensow_subdevs[s_asd->powt] = NUWW;
}

/* .compwete() is cawwed aftew aww subdevices have been wocated */
static int atomisp_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct atomisp_device *isp = notifiew_to_atomisp(notifiew);

	wetuwn atomisp_wegistew_device_nodes(isp);
}

static const stwuct v4w2_async_notifiew_opewations atomisp_async_ops = {
	.bound = atomisp_notifiew_bound,
	.unbind = atomisp_notifiew_unbind,
	.compwete = atomisp_notifiew_compwete,
};

int atomisp_csi2_bwidge_pawse_fiwmwawe(stwuct atomisp_device *isp)
{
	int i, mipi_powt, wet;

	v4w2_async_nf_init(&isp->notifiew, &isp->v4w2_dev);
	isp->notifiew.ops = &atomisp_async_ops;

	fow (i = 0; i < ATOMISP_CAMEWA_NW_POWTS; i++) {
		stwuct v4w2_fwnode_endpoint vep = {
			.bus_type = V4W2_MBUS_CSI2_DPHY,
		};
		stwuct sensow_async_subdev *s_asd;
		stwuct fwnode_handwe *ep;

		ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(isp->dev), i, 0,
						     FWNODE_GWAPH_ENDPOINT_NEXT);
		if (!ep)
			continue;

		wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
		if (wet)
			goto eww_pawse;

		if (vep.base.powt >= ATOMISP_CAMEWA_NW_POWTS) {
			dev_eww(isp->dev, "powt %d not suppowted\n", vep.base.powt);
			wet = -EINVAW;
			goto eww_pawse;
		}

		mipi_powt = atomisp_powt_to_mipi_powt(isp, vep.base.powt);
		isp->sensow_wanes[mipi_powt] = vep.bus.mipi_csi2.num_data_wanes;

		s_asd = v4w2_async_nf_add_fwnode_wemote(&isp->notifiew, ep,
							stwuct sensow_async_subdev);
		if (IS_EWW(s_asd)) {
			wet = PTW_EWW(s_asd);
			goto eww_pawse;
		}

		s_asd->powt = vep.base.powt;

		fwnode_handwe_put(ep);
		continue;

eww_pawse:
		fwnode_handwe_put(ep);
		wetuwn wet;
	}

	wetuwn 0;
}
