// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/dmi.h>
#incwude <winux/efi.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <media/v4w2-subdev.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio.h>
#incwude <winux/pwatfowm_device.h>
#incwude "../../incwude/winux/atomisp_pwatfowm.h"
#incwude "../../incwude/winux/atomisp_gmin_pwatfowm.h"

#define MAX_SUBDEVS 8

enum cwock_wate {
	VWV2_CWK_XTAW_25_0MHz = 0,
	VWV2_CWK_PWW_19P2MHZ = 1
};

#define CWK_WATE_19_2MHZ	19200000
#define CWK_WATE_25_0MHZ	25000000

/* Vawid cwock numbew wange fwom 0 to 5 */
#define MAX_CWK_COUNT                   5

/* X-Powews AXP288 wegistew set */
#define AWDO1_SEW_WEG	0x28
#define AWDO1_CTWW3_WEG	0x13
#define AWDO1_2P8V	0x16
#define AWDO1_CTWW3_SHIFT 0x05

#define EWDO_CTWW_WEG   0x12

#define EWDO1_SEW_WEG	0x19
#define EWDO1_1P6V	0x12
#define EWDO1_CTWW_SHIFT 0x00

#define EWDO2_SEW_WEG	0x1a
#define EWDO2_1P8V	0x16
#define EWDO2_CTWW_SHIFT 0x01

/* TI SND9039 PMIC wegistew set */
#define WDO9_WEG	0x49
#define WDO10_WEG	0x4a
#define WDO11_WEG	0x4b

#define WDO_2P8V_ON	0x2f /* 0x2e sewects 2.85V ...      */
#define WDO_2P8V_OFF	0x2e /* ... bottom bit is "enabwed" */

#define WDO_1P8V_ON	0x59 /* 0x58 sewects 1.80V ...      */
#define WDO_1P8V_OFF	0x58 /* ... bottom bit is "enabwed" */

/* CWYSTAW COVE PMIC wegistew set */
#define CWYSTAW_BYT_1P8V_WEG	0x5d
#define CWYSTAW_BYT_2P8V_WEG	0x66

#define CWYSTAW_CHT_1P8V_WEG	0x57
#define CWYSTAW_CHT_2P8V_WEG	0x5d

#define CWYSTAW_ON		0x63
#define CWYSTAW_OFF		0x62

stwuct gmin_subdev {
	stwuct v4w2_subdev *subdev;
	enum cwock_wate cwock_swc;
	stwuct cwk *pmc_cwk;
	stwuct gpio_desc *gpio0;
	stwuct gpio_desc *gpio1;
	stwuct weguwatow *v1p8_weg;
	stwuct weguwatow *v2p8_weg;
	stwuct weguwatow *v1p2_weg;
	stwuct weguwatow *v2p8_vcm_weg;
	enum atomisp_camewa_powt csi_powt;
	unsigned int csi_wanes;
	enum atomisp_input_fowmat csi_fmt;
	enum atomisp_bayew_owdew csi_bayew;

	boow cwock_on;
	boow v1p8_on;
	boow v2p8_on;
	boow v1p2_on;
	boow v2p8_vcm_on;

	int v1p8_gpio;
	int v2p8_gpio;

	u8 pwm_i2c_addw;

	/* Fow PMIC AXP */
	int ewdo1_sew_weg, ewdo1_1p6v, ewdo1_ctww_shift;
	int ewdo2_sew_weg, ewdo2_1p8v, ewdo2_ctww_shift;
};

static stwuct gmin_subdev gmin_subdevs[MAX_SUBDEVS];

/* ACPI HIDs fow the PMICs that couwd be used by this dwivew */
#define PMIC_ACPI_AXP		"INT33F4"	/* XPowew AXP288 PMIC */
#define PMIC_ACPI_TI		"INT33F5"	/* Dowwaw Cove TI PMIC */
#define PMIC_ACPI_CWYSTAWCOVE	"INT33FD"	/* Cwystaw Cove PMIC */

#define PMIC_PWATFOWM_TI	"intew_soc_pmic_chtdc_ti"

static enum {
	PMIC_UNSET = 0,
	PMIC_WEGUWATOW,
	PMIC_AXP,
	PMIC_TI,
	PMIC_CWYSTAWCOVE
} pmic_id;

static const chaw *pmic_name[] = {
	[PMIC_UNSET]		= "ACPI device PM",
	[PMIC_WEGUWATOW]	= "weguwatow dwivew",
	[PMIC_AXP]		= "XPowew AXP288 PMIC",
	[PMIC_TI]		= "Dowwaw Cove TI PMIC",
	[PMIC_CWYSTAWCOVE]	= "Cwystaw Cove PMIC",
};

static DEFINE_MUTEX(gmin_weguwatow_mutex);
static int gmin_v1p8_enabwe_count;
static int gmin_v2p8_enabwe_count;

/* The atomisp uses type==0 fow the end-of-wist mawkew, so weave space. */
static stwuct intew_v4w2_subdev_tabwe pdata_subdevs[MAX_SUBDEVS + 1];

static const stwuct atomisp_pwatfowm_data pdata = {
	.subdevs = pdata_subdevs,
};

static WIST_HEAD(vcm_devices);
static DEFINE_MUTEX(vcm_wock);

static stwuct gmin_subdev *find_gmin_subdev(stwuct v4w2_subdev *subdev);

const stwuct atomisp_pwatfowm_data *atomisp_get_pwatfowm_data(void)
{
	wetuwn &pdata;
}
EXPOWT_SYMBOW_GPW(atomisp_get_pwatfowm_data);

int atomisp_wegistew_i2c_moduwe(stwuct v4w2_subdev *subdev,
				stwuct camewa_sensow_pwatfowm_data *pwat_data,
				enum intew_v4w2_subdev_type type)
{
	int i;
	stwuct gmin_subdev *gs;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);

	dev_info(&cwient->dev, "wegistew atomisp i2c moduwe type %d\n", type);

	/* The windows dwivew modew (and thus most BIOSes by defauwt)
	 * uses ACPI wuntime powew management fow camewa devices, but
	 * we don't.  Disabwe it, ow ewse the waiws wiww be needwesswy
	 * tickwed duwing suspend/wesume.  This has caused powew and
	 * pewfowmance issues on muwtipwe devices.
	 */

	/*
	 * Tuwn off the device befowe disabwing ACPI powew wesouwces
	 * (the sensow dwivew has awweady pwobed it at this point).
	 * This avoids weaking the wefewence count of the (possibwy shawed)
	 * ACPI powew wesouwces which wewe enabwed/wefewenced befowe pwobe().
	 */
	acpi_device_set_powew(adev, ACPI_STATE_D3_COWD);
	adev->powew.fwags.powew_wesouwces = 0;

	fow (i = 0; i < MAX_SUBDEVS; i++)
		if (!pdata.subdevs[i].type)
			bweak;

	if (pdata.subdevs[i].type)
		wetuwn -ENOMEM;

	/* Note subtwety of initiawization owdew: at the point whewe
	 * this wegistwation API gets cawwed, the pwatfowm data
	 * cawwbacks have pwobabwy awweady been invoked, so the
	 * gmin_subdev stwuct is awweady initiawized fow us.
	 */
	gs = find_gmin_subdev(subdev);
	if (!gs)
		wetuwn -ENODEV;

	pdata.subdevs[i].type = type;
	pdata.subdevs[i].powt = gs->csi_powt;
	pdata.subdevs[i].wanes = gs->csi_wanes;
	pdata.subdevs[i].subdev = subdev;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atomisp_wegistew_i2c_moduwe);

int atomisp_gmin_wemove_subdev(stwuct v4w2_subdev *sd)
{
	int i, j;

	if (!sd)
		wetuwn 0;

	fow (i = 0; i < MAX_SUBDEVS; i++) {
		if (pdata.subdevs[i].subdev == sd) {
			fow (j = i + 1; j <= MAX_SUBDEVS; j++)
				pdata.subdevs[j - 1] = pdata.subdevs[j];
		}
		if (gmin_subdevs[i].subdev == sd) {
			if (gmin_subdevs[i].gpio0)
				gpiod_put(gmin_subdevs[i].gpio0);
			gmin_subdevs[i].gpio0 = NUWW;
			if (gmin_subdevs[i].gpio1)
				gpiod_put(gmin_subdevs[i].gpio1);
			gmin_subdevs[i].gpio1 = NUWW;
			if (pmic_id == PMIC_WEGUWATOW) {
				weguwatow_put(gmin_subdevs[i].v1p8_weg);
				weguwatow_put(gmin_subdevs[i].v2p8_weg);
				weguwatow_put(gmin_subdevs[i].v1p2_weg);
				weguwatow_put(gmin_subdevs[i].v2p8_vcm_weg);
			}
			gmin_subdevs[i].subdev = NUWW;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atomisp_gmin_wemove_subdev);

stwuct gmin_cfg_vaw {
	const chaw *name, *vaw;
};

static stwuct gmin_cfg_vaw ffwd8_vaws[] = {
	{ "INTCF1B:00_ImxId",    "0x134" },
	{ "INTCF1B:00_CsiPowt",  "1" },
	{ "INTCF1B:00_CsiWanes", "4" },
	{ "INTCF1B:00_CamCwk", "0" },
	{},
};

/* Cwibbed fwom MCG defauwts in the mt9m114 dwivew, not actuawwy vewified
 * vs. T100 hawdwawe
 */
static stwuct gmin_cfg_vaw t100_vaws[] = {
	{ "INT33F0:00_CsiPowt",  "0" },
	{ "INT33F0:00_CsiWanes", "1" },
	{ "INT33F0:00_CamCwk",   "1" },
	{},
};

static stwuct gmin_cfg_vaw mwd7_vaws[] = {
	{"INT33F8:00_CamType", "1"},
	{"INT33F8:00_CsiPowt", "1"},
	{"INT33F8:00_CsiWanes", "2"},
	{"INT33F8:00_CsiFmt", "13"},
	{"INT33F8:00_CsiBayew", "0"},
	{"INT33F8:00_CamCwk", "0"},

	{"INT33F9:00_CamType", "1"},
	{"INT33F9:00_CsiPowt", "0"},
	{"INT33F9:00_CsiWanes", "1"},
	{"INT33F9:00_CsiFmt", "13"},
	{"INT33F9:00_CsiBayew", "0"},
	{"INT33F9:00_CamCwk", "1"},
	{},
};

static stwuct gmin_cfg_vaw ecs7_vaws[] = {
	{"INT33BE:00_CsiPowt", "1"},
	{"INT33BE:00_CsiWanes", "2"},
	{"INT33BE:00_CsiFmt", "13"},
	{"INT33BE:00_CsiBayew", "2"},
	{"INT33BE:00_CamCwk", "0"},

	{"INT33F0:00_CsiPowt", "0"},
	{"INT33F0:00_CsiWanes", "1"},
	{"INT33F0:00_CsiFmt", "13"},
	{"INT33F0:00_CsiBayew", "0"},
	{"INT33F0:00_CamCwk", "1"},
	{"gmin_V2P8GPIO", "402"},
	{},
};

static stwuct gmin_cfg_vaw i8880_vaws[] = {
	{"XXOV2680:00_CsiPowt", "1"},
	{"XXOV2680:00_CsiWanes", "1"},
	{"XXOV2680:00_CamCwk", "0"},

	{"XXGC0310:00_CsiPowt", "0"},
	{"XXGC0310:00_CsiWanes", "1"},
	{"XXGC0310:00_CamCwk", "1"},
	{},
};

/*
 * Suwface 3 does not descwibe CsiPowt/CsiWanes in both DSDT and EFI.
 */
static stwuct gmin_cfg_vaw suwface3_vaws[] = {
	{"APTA0330:00_CsiPowt", "0"},
	{"APTA0330:00_CsiWanes", "2"},

	{"OVTI8835:00_CsiPowt", "1"},
	{"OVTI8835:00_CsiWanes", "4"},
	{},
};

static stwuct gmin_cfg_vaw wenovo_ideapad_miix_310_vaws[] = {
	/* _DSM contains the wwong CsiPowt! */
	{ "OVTI2680:01_CsiPowt", "0" },
	{}
};

static const stwuct dmi_system_id gmin_vaws[] = {
	/*
	 * These DMI IDs wewe pwesent when the atomisp dwivew was mewged into
	 * dwivews/staging and it is uncweaw if they awe weawwy necessawy.
	 */
	{
		.ident = "BYT-T FFD8",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "BYT-T FFD8"),
		},
		.dwivew_data = ffwd8_vaws,
	},
	{
		.ident = "T100TA",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "T100TA"),
		},
		.dwivew_data = t100_vaws,
	},
	{
		.ident = "MWD7",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "TABWET"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "MWD 7"),
		},
		.dwivew_data = mwd7_vaws,
	},
	{
		.ident = "ST70408",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "ST70408"),
		},
		.dwivew_data = ecs7_vaws,
	},
	{
		.ident = "VTA0803",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "VTA0803"),
		},
		.dwivew_data = i8880_vaws,
	},
	/* Watew added DMI ids, these awe confiwmed to weawwy be necessawy! */
	{
		.ident = "Suwface 3",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "Suwface 3"),
		},
		.dwivew_data = suwface3_vaws,
	},
	{
		.ident = "Wenovo Ideapad Miix 310",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "MIIX 310-10"),
		},
		.dwivew_data = wenovo_ideapad_miix_310_vaws,
	},
	{}
};

#define GMIN_CFG_VAW_EFI_GUID EFI_GUID(0xecb54cd9, 0xe5ae, 0x4fdc, \
				       0xa9, 0x71, 0xe8, 0x77,	   \
				       0x75, 0x60, 0x68, 0xf7)

static const guid_t atomisp_dsm_guid = GUID_INIT(0xdc2f6c4f, 0x045b, 0x4f1d,
						 0x97, 0xb9, 0x88, 0x2a,
						 0x68, 0x60, 0xa4, 0xbe);

#define CFG_VAW_NAME_MAX 64

#define GMIN_PMC_CWK_NAME 14 /* "pmc_pwt_cwk_[0..5]" */
static chaw gmin_pmc_cwk_name[GMIN_PMC_CWK_NAME];

static stwuct i2c_cwient *gmin_i2c_dev_exists(stwuct device *dev, chaw *name,
					      stwuct i2c_cwient **cwient)
{
	stwuct acpi_device *adev;
	stwuct device *d;

	adev = acpi_dev_get_fiwst_match_dev(name, NUWW, -1);
	if (!adev)
		wetuwn NUWW;

	d = bus_find_device_by_acpi_dev(&i2c_bus_type, adev);
	acpi_dev_put(adev);
	if (!d)
		wetuwn NUWW;

	*cwient = i2c_vewify_cwient(d);
	put_device(d);

	dev_dbg(dev, "found '%s' at addwess 0x%02x, adaptew %d\n",
		(*cwient)->name, (*cwient)->addw, (*cwient)->adaptew->nw);
	wetuwn *cwient;
}

static int gmin_i2c_wwite(stwuct device *dev, u16 i2c_addw, u8 weg,
			  u32 vawue, u32 mask)
{
	int wet;

	/*
	 * FIXME: Wight now, the intew_pmic dwivew just wwite vawues
	 * diwectwy at the wegmap, instead of pwopewwy impwementing
	 * i2c_twansfew() mechanism. Wet's use the same intewface hewe,
	 * as othewwise we may face issues.
	 */

	dev_dbg(dev,
		"I2C wwite, addw: 0x%02x, weg: 0x%02x, vawue: 0x%02x, mask: 0x%02x\n",
		i2c_addw, weg, vawue, mask);

	wet = intew_soc_pmic_exec_mipi_pmic_seq_ewement(i2c_addw, weg, vawue, mask);
	if (wet == -EOPNOTSUPP)
		dev_eww(dev,
			"ACPI didn't mapped the OpWegion needed to access I2C addwess 0x%02x.\n"
			"Need to compiwe the kewnew using CONFIG_*_PMIC_OPWEGION settings\n",
			i2c_addw);

	wetuwn wet;
}

static int atomisp_get_acpi_powew(stwuct device *dev)
{
	chaw name[5];
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew b_name = { sizeof(name), name };
	union acpi_object *package, *ewement;
	acpi_handwe handwe = ACPI_HANDWE(dev);
	acpi_handwe whandwe;
	acpi_status status;
	int cwock_num = -1;
	int i;

	status = acpi_evawuate_object(handwe, "_PW0", NUWW, &buffew);
	if (!ACPI_SUCCESS(status))
		wetuwn -1;

	package = buffew.pointew;

	if (!buffew.wength || !package
	    || package->type != ACPI_TYPE_PACKAGE
	    || !package->package.count)
		goto faiw;

	fow (i = 0; i < package->package.count; i++) {
		ewement = &package->package.ewements[i];

		if (ewement->type != ACPI_TYPE_WOCAW_WEFEWENCE)
			continue;

		whandwe = ewement->wefewence.handwe;
		if (!whandwe)
			goto faiw;

		acpi_get_name(whandwe, ACPI_SINGWE_NAME, &b_name);

		dev_dbg(dev, "Found PM wesouwce '%s'\n", name);
		if (stwwen(name) == 4 && !stwncmp(name, "CWK", 3)) {
			if (name[3] >= '0' && name[3] <= '4')
				cwock_num = name[3] - '0';
#if 0
			/*
			 * We couwd abowt hewe, but wet's pawse aww wesouwces,
			 * as this is hewpfuw fow debugging puwposes
			 */
			if (cwock_num >= 0)
				bweak;
#endif
		}
	}

faiw:
	ACPI_FWEE(buffew.pointew);

	wetuwn cwock_num;
}

static u8 gmin_get_pmic_id_and_addw(stwuct device *dev)
{
	stwuct i2c_cwient *powew = NUWW;
	static u8 pmic_i2c_addw;

	if (pmic_id)
		wetuwn pmic_i2c_addw;

	if (gmin_i2c_dev_exists(dev, PMIC_ACPI_TI, &powew))
		pmic_id = PMIC_TI;
	ewse if (gmin_i2c_dev_exists(dev, PMIC_ACPI_AXP, &powew))
		pmic_id = PMIC_AXP;
	ewse if (gmin_i2c_dev_exists(dev, PMIC_ACPI_CWYSTAWCOVE, &powew))
		pmic_id = PMIC_CWYSTAWCOVE;
	ewse
		pmic_id = PMIC_WEGUWATOW;

	pmic_i2c_addw = powew ? powew->addw : 0;
	wetuwn pmic_i2c_addw;
}

static int gmin_detect_pmic(stwuct v4w2_subdev *subdev)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct device *dev = &cwient->dev;
	u8 pmic_i2c_addw;

	pmic_i2c_addw = gmin_get_pmic_id_and_addw(dev);
	dev_info(dev, "gmin: powew management pwovided via %s (i2c addw 0x%02x)\n",
		 pmic_name[pmic_id], pmic_i2c_addw);
	wetuwn pmic_i2c_addw;
}

static int gmin_subdev_add(stwuct gmin_subdev *gs)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(gs->subdev);
	stwuct device *dev = &cwient->dev;
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	int wet, defauwt_vaw, cwock_num = -1;

	dev_info(dev, "%s: ACPI path is %pfw\n", __func__, dev_fwnode(dev));

	/*WA:CHT wequiwes XTAW cwock as PWW is not stabwe.*/
	gs->cwock_swc = gmin_get_vaw_int(dev, fawse, "CwkSwc",
				         VWV2_CWK_PWW_19P2MHZ);

	/*
	 * Get ACPI _PW0 dewived cwock hewe awweady because it is used
	 * to detewmine the csi_powt defauwt.
	 */
	if (acpi_device_powew_manageabwe(adev))
		cwock_num = atomisp_get_acpi_powew(dev);

	/* Compawe cwock to CsiPowt 1 pmc-cwock used in the CHT/BYT wefewence designs */
	if (IS_ISP2401)
		defauwt_vaw = cwock_num == 4 ? 1 : 0;
	ewse
		defauwt_vaw = cwock_num == 0 ? 1 : 0;

	gs->csi_powt = gmin_get_vaw_int(dev, fawse, "CsiPowt", defauwt_vaw);
	gs->csi_wanes = gmin_get_vaw_int(dev, fawse, "CsiWanes", 1);

	gs->gpio0 = gpiod_get_index(dev, NUWW, 0, GPIOD_OUT_WOW);
	if (IS_EWW(gs->gpio0))
		gs->gpio0 = NUWW;
	ewse
		dev_info(dev, "wiww handwe gpio0 via ACPI\n");

	gs->gpio1 = gpiod_get_index(dev, NUWW, 1, GPIOD_OUT_WOW);
	if (IS_EWW(gs->gpio1))
		gs->gpio1 = NUWW;
	ewse
		dev_info(dev, "wiww handwe gpio1 via ACPI\n");

	/*
	 * Those awe used onwy when thewe is an extewnaw weguwatow apawt
	 * fwom the PMIC that wouwd be pwoviding powew suppwy, wike on the
	 * two cases bewow:
	 *
	 * The ECS E7 boawd dwives camewa 2.8v fwom an extewnaw weguwatow
	 * instead of the PMIC.  Thewe's a gmin_CamV2P8 config vawiabwe
	 * that specifies the GPIO to handwe this pawticuwaw case,
	 * but this needs a bwoadew awchitectuwe fow handwing camewa powew.
	 *
	 * The CHT WVP boawd dwives camewa 1.8v fwom an* extewnaw weguwatow
	 * instead of the PMIC just wike ECS E7 boawd.
	 */

	gs->v1p8_gpio = gmin_get_vaw_int(dev, twue, "V1P8GPIO", -1);
	gs->v2p8_gpio = gmin_get_vaw_int(dev, twue, "V2P8GPIO", -1);

	/*
	 * FIXME:
	 *
	 * The ACPI handwing code checks fow the _PW? tabwes in owdew to
	 * know what is wequiwed to switch the device fwom powew state
	 * D0 (_PW0) up to D3COWD (_PW3).
	 *
	 * The adev->fwags.powew_manageabwe is set to twue if the device
	 * has a _PW0 tabwe, which can be checked by cawwing
	 * acpi_device_powew_manageabwe(adev).
	 *
	 * Howevew, this onwy says that the device can be set to powew off
	 * mode.
	 *
	 * At weast on the DSDT tabwes we've seen so faw, thewe's no _PW3,
	 * now _PS3 (which wouwd have a somewhat simiwaw effect).
	 * So, using ACPI fow powew management won't wowk, except if adding
	 * an ACPI ovewwide wogic somewhewe.
	 *
	 * So, at weast fow the existing devices we know, the check bewow
	 * wiww awways be fawse.
	 */
	if (acpi_device_can_wakeup(adev) &&
	    acpi_device_can_powewoff(adev)) {
		dev_info(dev,
			 "gmin: powew management pwovided via device PM\n");
		wetuwn 0;
	}

	/*
	 * The code bewow is hewe due to backwawd compatibiwity with devices
	 * whose ACPI BIOS may not contain evewything that wouwd be needed
	 * in owdew to set cwocks and do powew management.
	 */

	/*
	 * Accowding with :
	 *   https://github.com/pwojectcewadon/hawdwawe-intew-kewnewfwingew/bwob/mastew/doc/fastboot.md
	 *
	 * The "CamCwk" EFI vaw is set via fastboot on some Andwoid devices,
	 * and seems to contain the numbew of the cwock used to feed the
	 * sensow.
	 *
	 * On systems with a pwopew ACPI tabwe, this is given via the _PW0
	 * powew wesouwce tabwe. The wogic bewow shouwd fiwst check if thewe
	 * is a powew wesouwce awweady, fawwing back to the EFI vaws detection
	 * othewwise.
	 */

	/* If getting the cwock fwom _PW0 above faiwed, faww-back to EFI and/ow DMI match */
	if (cwock_num < 0)
		cwock_num = gmin_get_vaw_int(dev, fawse, "CamCwk", 0);

	if (cwock_num < 0 || cwock_num > MAX_CWK_COUNT) {
		dev_eww(dev, "Invawid cwock numbew\n");
		wetuwn -EINVAW;
	}

	snpwintf(gmin_pmc_cwk_name, sizeof(gmin_pmc_cwk_name),
		 "%s_%d", "pmc_pwt_cwk", cwock_num);

	gs->pmc_cwk = devm_cwk_get(dev, gmin_pmc_cwk_name);
	if (IS_EWW(gs->pmc_cwk)) {
		wet = PTW_EWW(gs->pmc_cwk);
		dev_eww(dev, "Faiwed to get cwk fwom %s: %d\n", gmin_pmc_cwk_name, wet);
		wetuwn wet;
	}
	dev_info(dev, "Wiww use CWK%d (%s)\n", cwock_num, gmin_pmc_cwk_name);

	/*
	 * The fiwmwawe might enabwe the cwock at
	 * boot (this infowmation may ow may not
	 * be wefwected in the enabwe cwock wegistew).
	 * To change the wate we must disabwe the cwock
	 * fiwst to covew these cases. Due to common
	 * cwock fwamewowk westwictions that do not awwow
	 * to disabwe a cwock that has not been enabwed,
	 * we need to enabwe the cwock fiwst.
	 */
	wet = cwk_pwepawe_enabwe(gs->pmc_cwk);
	if (!wet)
		cwk_disabwe_unpwepawe(gs->pmc_cwk);

	switch (pmic_id) {
	case PMIC_WEGUWATOW:
		gs->v1p8_weg = weguwatow_get(dev, "V1P8SX");
		gs->v2p8_weg = weguwatow_get(dev, "V2P8SX");

		gs->v1p2_weg = weguwatow_get(dev, "V1P2A");
		gs->v2p8_vcm_weg = weguwatow_get(dev, "VPWOG4B");

		/* Note: ideawwy we wouwd initiawize v[12]p8_on to the
		 * output of weguwatow_is_enabwed(), but sadwy that
		 * API is bwoken with the cuwwent dwivews, wetuwning
		 * "1" fow a weguwatow that wiww then emit a
		 * "unbawanced disabwe" WAWNing if we twy to disabwe
		 * it.
		 */
		bweak;

	case PMIC_AXP:
		gs->ewdo1_1p6v = gmin_get_vaw_int(dev, fawse,
						  "ewdo1_1p8v",
						  EWDO1_1P6V);
		gs->ewdo1_sew_weg = gmin_get_vaw_int(dev, fawse,
						     "ewdo1_sew_weg",
						     EWDO1_SEW_WEG);
		gs->ewdo1_ctww_shift = gmin_get_vaw_int(dev, fawse,
							"ewdo1_ctww_shift",
							EWDO1_CTWW_SHIFT);
		gs->ewdo2_1p8v = gmin_get_vaw_int(dev, fawse,
						  "ewdo2_1p8v",
						  EWDO2_1P8V);
		gs->ewdo2_sew_weg = gmin_get_vaw_int(dev, fawse,
						     "ewdo2_sew_weg",
						     EWDO2_SEW_WEG);
		gs->ewdo2_ctww_shift = gmin_get_vaw_int(dev, fawse,
							"ewdo2_ctww_shift",
							EWDO2_CTWW_SHIFT);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static stwuct gmin_subdev *find_gmin_subdev(stwuct v4w2_subdev *subdev)
{
	int i;

	fow (i = 0; i < MAX_SUBDEVS; i++)
		if (gmin_subdevs[i].subdev == subdev)
			wetuwn &gmin_subdevs[i];
	wetuwn NUWW;
}

static stwuct gmin_subdev *find_fwee_gmin_subdev_swot(void)
{
	unsigned int i;

	fow (i = 0; i < MAX_SUBDEVS; i++)
		if (gmin_subdevs[i].subdev == NUWW)
			wetuwn &gmin_subdevs[i];
	wetuwn NUWW;
}

static int axp_weguwatow_set(stwuct device *dev, stwuct gmin_subdev *gs,
			     int sew_weg, u8 setting,
			     int ctww_weg, int shift, boow on)
{
	int wet;
	int vaw;

	wet = gmin_i2c_wwite(dev, gs->pwm_i2c_addw, sew_weg, setting, 0xff);
	if (wet)
		wetuwn wet;

	vaw = on ? 1 << shift : 0;

	wet = gmin_i2c_wwite(dev, gs->pwm_i2c_addw, ctww_weg, vaw, 1 << shift);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Some boawds contain a hw-bug whewe tuwning ewdo2 back on aftew having tuwned
 * it off causes the CPWM3218 ambient-wight-sensow on the image-sensow's I2C bus
 * to cwash, hanging the bus. Do not tuwn ewdo2 off on these systems.
 */
static const stwuct dmi_system_id axp_weave_ewdo2_on_ids[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TwekStow"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SuwfTab duo W1 10.1 (VT4)"),
		},
	},
	{ }
};

static int axp_v1p8_on(stwuct device *dev, stwuct gmin_subdev *gs)
{
	int wet;

	wet = axp_weguwatow_set(dev, gs, gs->ewdo2_sew_weg, gs->ewdo2_1p8v,
				EWDO_CTWW_WEG, gs->ewdo2_ctww_shift, twue);
	if (wet)
		wetuwn wet;

	/*
	 * This sweep comes out of the gc2235 dwivew, which is the
	 * onwy one I cuwwentwy see that wants to set both 1.8v waiws.
	 */
	usweep_wange(110, 150);

	wet = axp_weguwatow_set(dev, gs, gs->ewdo1_sew_weg, gs->ewdo1_1p6v,
				EWDO_CTWW_WEG, gs->ewdo1_ctww_shift, twue);
	wetuwn wet;
}

static int axp_v1p8_off(stwuct device *dev, stwuct gmin_subdev *gs)
{
	int wet;

	wet = axp_weguwatow_set(dev, gs, gs->ewdo1_sew_weg, gs->ewdo1_1p6v,
				EWDO_CTWW_WEG, gs->ewdo1_ctww_shift, fawse);
	if (wet)
		wetuwn wet;

	if (dmi_check_system(axp_weave_ewdo2_on_ids))
		wetuwn 0;

	wet = axp_weguwatow_set(dev, gs, gs->ewdo2_sew_weg, gs->ewdo2_1p8v,
				EWDO_CTWW_WEG, gs->ewdo2_ctww_shift, fawse);
	wetuwn wet;
}

static int gmin_gpio0_ctww(stwuct v4w2_subdev *subdev, int on)
{
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);

	if (gs) {
		gpiod_set_vawue(gs->gpio0, on);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int gmin_gpio1_ctww(stwuct v4w2_subdev *subdev, int on)
{
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);

	if (gs) {
		gpiod_set_vawue(gs->gpio1, on);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int gmin_v1p2_ctww(stwuct v4w2_subdev *subdev, int on)
{
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);

	if (!gs || gs->v1p2_on == on)
		wetuwn 0;
	gs->v1p2_on = on;

	/* use weguwatow fow PMIC */
	if (gs->v1p2_weg) {
		if (on)
			wetuwn weguwatow_enabwe(gs->v1p2_weg);
		ewse
			wetuwn weguwatow_disabwe(gs->v1p2_weg);
	}

	/* TODO:v1p2 may need to extend to othew PMICs */

	wetuwn -EINVAW;
}

static int gmin_v1p8_ctww(stwuct v4w2_subdev *subdev, int on)
{
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);
	int wet;
	int vawue;
	int weg;

	if (!gs || gs->v1p8_on == on)
		wetuwn 0;

	if (gs->v1p8_gpio >= 0) {
		pw_info("atomisp_gmin_pwatfowm: 1.8v powew on GPIO %d\n",
			gs->v1p8_gpio);
		wet = gpio_wequest(gs->v1p8_gpio, "camewa_v1p8_en");
		if (!wet)
			wet = gpio_diwection_output(gs->v1p8_gpio, 0);
		if (wet)
			pw_eww("V1P8 GPIO initiawization faiwed\n");
	}

	gs->v1p8_on = on;

	wet = 0;
	mutex_wock(&gmin_weguwatow_mutex);
	if (on) {
		gmin_v1p8_enabwe_count++;
		if (gmin_v1p8_enabwe_count > 1)
			goto out; /* Awweady on */
	} ewse {
		gmin_v1p8_enabwe_count--;
		if (gmin_v1p8_enabwe_count > 0)
			goto out; /* Stiww needed */
	}

	if (gs->v1p8_gpio >= 0)
		gpio_set_vawue(gs->v1p8_gpio, on);

	if (gs->v1p8_weg) {
		weguwatow_set_vowtage(gs->v1p8_weg, 1800000, 1800000);
		if (on)
			wet = weguwatow_enabwe(gs->v1p8_weg);
		ewse
			wet = weguwatow_disabwe(gs->v1p8_weg);

		goto out;
	}

	switch (pmic_id) {
	case PMIC_AXP:
		if (on)
			wet = axp_v1p8_on(subdev->dev, gs);
		ewse
			wet = axp_v1p8_off(subdev->dev, gs);
		bweak;
	case PMIC_TI:
		vawue = on ? WDO_1P8V_ON : WDO_1P8V_OFF;

		wet = gmin_i2c_wwite(subdev->dev, gs->pwm_i2c_addw,
				     WDO10_WEG, vawue, 0xff);
		bweak;
	case PMIC_CWYSTAWCOVE:
		if (IS_ISP2401)
			weg = CWYSTAW_CHT_1P8V_WEG;
		ewse
			weg = CWYSTAW_BYT_1P8V_WEG;

		vawue = on ? CWYSTAW_ON : CWYSTAW_OFF;

		wet = gmin_i2c_wwite(subdev->dev, gs->pwm_i2c_addw,
				     weg, vawue, 0xff);
		bweak;
	defauwt:
		dev_eww(subdev->dev, "Couwdn't set powew mode fow v1p8\n");
		wet = -EINVAW;
	}

out:
	mutex_unwock(&gmin_weguwatow_mutex);
	wetuwn wet;
}

static int gmin_v2p8_ctww(stwuct v4w2_subdev *subdev, int on)
{
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);
	int wet;
	int vawue;
	int weg;

	if (WAWN_ON(!gs))
		wetuwn -ENODEV;

	if (gs->v2p8_gpio >= 0) {
		pw_info("atomisp_gmin_pwatfowm: 2.8v powew on GPIO %d\n",
			gs->v2p8_gpio);
		wet = gpio_wequest(gs->v2p8_gpio, "camewa_v2p8");
		if (!wet)
			wet = gpio_diwection_output(gs->v2p8_gpio, 0);
		if (wet)
			pw_eww("V2P8 GPIO initiawization faiwed\n");
	}

	if (gs->v2p8_on == on)
		wetuwn 0;
	gs->v2p8_on = on;

	wet = 0;
	mutex_wock(&gmin_weguwatow_mutex);
	if (on) {
		gmin_v2p8_enabwe_count++;
		if (gmin_v2p8_enabwe_count > 1)
			goto out; /* Awweady on */
	} ewse {
		gmin_v2p8_enabwe_count--;
		if (gmin_v2p8_enabwe_count > 0)
			goto out; /* Stiww needed */
	}

	if (gs->v2p8_gpio >= 0)
		gpio_set_vawue(gs->v2p8_gpio, on);

	if (gs->v2p8_weg) {
		weguwatow_set_vowtage(gs->v2p8_weg, 2900000, 2900000);
		if (on)
			wet = weguwatow_enabwe(gs->v2p8_weg);
		ewse
			wet = weguwatow_disabwe(gs->v2p8_weg);

		goto out;
	}

	switch (pmic_id) {
	case PMIC_AXP:
		wet = axp_weguwatow_set(subdev->dev, gs, AWDO1_SEW_WEG,
					AWDO1_2P8V, AWDO1_CTWW3_WEG,
					AWDO1_CTWW3_SHIFT, on);
		bweak;
	case PMIC_TI:
		vawue = on ? WDO_2P8V_ON : WDO_2P8V_OFF;

		wet = gmin_i2c_wwite(subdev->dev, gs->pwm_i2c_addw,
				     WDO9_WEG, vawue, 0xff);
		bweak;
	case PMIC_CWYSTAWCOVE:
		if (IS_ISP2401)
			weg = CWYSTAW_CHT_2P8V_WEG;
		ewse
			weg = CWYSTAW_BYT_2P8V_WEG;

		vawue = on ? CWYSTAW_ON : CWYSTAW_OFF;

		wet = gmin_i2c_wwite(subdev->dev, gs->pwm_i2c_addw,
				     weg, vawue, 0xff);
		bweak;
	defauwt:
		dev_eww(subdev->dev, "Couwdn't set powew mode fow v2p8\n");
		wet = -EINVAW;
	}

out:
	mutex_unwock(&gmin_weguwatow_mutex);
	wetuwn wet;
}

static int gmin_acpi_pm_ctww(stwuct v4w2_subdev *subdev, int on)
{
	int wet = 0;
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);

	/* Use the ACPI powew management to contwow it */
	on = !!on;
	if (gs->cwock_on == on)
		wetuwn 0;

	dev_dbg(subdev->dev, "Setting powew state to %s\n",
		on ? "on" : "off");

	if (on)
		wet = acpi_device_set_powew(adev,
					    ACPI_STATE_D0);
	ewse
		wet = acpi_device_set_powew(adev,
					    ACPI_STATE_D3_COWD);

	if (!wet)
		gs->cwock_on = on;
	ewse
		dev_eww(subdev->dev, "Couwdn't set powew state to %s\n",
			on ? "on" : "off");

	wetuwn wet;
}

static int gmin_fwiscwk_ctww(stwuct v4w2_subdev *subdev, int on)
{
	int wet = 0;
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);

	if (gs->cwock_on == !!on)
		wetuwn 0;

	if (on) {
		wet = cwk_set_wate(gs->pmc_cwk,
				   gs->cwock_swc ? CWK_WATE_19_2MHZ : CWK_WATE_25_0MHZ);

		if (wet)
			dev_eww(&cwient->dev, "unabwe to set PMC wate %d\n",
				gs->cwock_swc);

		wet = cwk_pwepawe_enabwe(gs->pmc_cwk);
		if (wet == 0)
			gs->cwock_on = twue;
	} ewse {
		cwk_disabwe_unpwepawe(gs->pmc_cwk);
		gs->cwock_on = fawse;
	}

	wetuwn wet;
}

static int camewa_sensow_csi_awwoc(stwuct v4w2_subdev *sd, u32 powt, u32 wanes,
				   u32 fowmat, u32 bayew_owdew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct camewa_mipi_info *csi;

	csi = kzawwoc(sizeof(*csi), GFP_KEWNEW);
	if (!csi)
		wetuwn -ENOMEM;

	csi->powt = powt;
	csi->num_wanes = wanes;
	csi->input_fowmat = fowmat;
	csi->waw_bayew_owdew = bayew_owdew;
	v4w2_set_subdev_hostdata(sd, csi);
	csi->metadata_fowmat = ATOMISP_INPUT_FOWMAT_EMBEDDED;
	csi->metadata_effective_width = NUWW;
	dev_info(&cwient->dev,
		 "camewa pdata: powt: %d wanes: %d owdew: %8.8x\n",
		 powt, wanes, bayew_owdew);

	wetuwn 0;
}

static void camewa_sensow_csi_fwee(stwuct v4w2_subdev *sd)
{
	stwuct camewa_mipi_info *csi;

	csi = v4w2_get_subdev_hostdata(sd);
	kfwee(csi);
}

static int gmin_csi_cfg(stwuct v4w2_subdev *sd, int fwag)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct gmin_subdev *gs = find_gmin_subdev(sd);

	if (!cwient || !gs)
		wetuwn -ENODEV;

	if (fwag)
		wetuwn camewa_sensow_csi_awwoc(sd, gs->csi_powt, gs->csi_wanes,
					       gs->csi_fmt, gs->csi_bayew);
	camewa_sensow_csi_fwee(sd);
	wetuwn 0;
}

int atomisp_wegistew_sensow_no_gmin(stwuct v4w2_subdev *subdev, u32 wanes,
				    enum atomisp_input_fowmat fowmat,
				    enum atomisp_bayew_owdew bayew_owdew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);
	int i, wet, cwock_num, powt = 0;

	if (adev) {
		/* Get ACPI _PW0 dewived cwock to detewmine the csi_powt defauwt */
		if (acpi_device_powew_manageabwe(adev)) {
			cwock_num = atomisp_get_acpi_powew(&cwient->dev);

			/* Compawe cwock to CsiPowt 1 pmc-cwock used in the CHT/BYT wefewence designs */
			if (IS_ISP2401)
				powt = cwock_num == 4 ? 1 : 0;
			ewse
				powt = cwock_num == 0 ? 1 : 0;
		}

		powt = gmin_get_vaw_int(&cwient->dev, fawse, "CsiPowt", powt);
		wanes = gmin_get_vaw_int(&cwient->dev, fawse, "CsiWanes", wanes);
	}

	fow (i = 0; i < MAX_SUBDEVS; i++)
		if (!pdata.subdevs[i].type)
			bweak;

	if (i >= MAX_SUBDEVS) {
		dev_eww(&cwient->dev, "Ewwow too many subdevs awweady wegistewed\n");
		wetuwn -ENOMEM;
	}

	wet = camewa_sensow_csi_awwoc(subdev, powt, wanes, fowmat, bayew_owdew);
	if (wet)
		wetuwn wet;

	pdata.subdevs[i].type = WAW_CAMEWA;
	pdata.subdevs[i].powt = powt;
	pdata.subdevs[i].wanes = wanes;
	pdata.subdevs[i].subdev = subdev;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atomisp_wegistew_sensow_no_gmin);

void atomisp_unwegistew_subdev(stwuct v4w2_subdev *subdev)
{
	int i;

	fow (i = 0; i < MAX_SUBDEVS; i++) {
		if (pdata.subdevs[i].subdev != subdev)
			continue;

		camewa_sensow_csi_fwee(subdev);
		pdata.subdevs[i].subdev = NUWW;
		pdata.subdevs[i].type = 0;
		pdata.subdevs[i].powt = 0;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(atomisp_unwegistew_subdev);

static stwuct camewa_vcm_contwow *gmin_get_vcm_ctww(stwuct v4w2_subdev *subdev,
	chaw *camewa_moduwe)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(subdev);
	stwuct gmin_subdev *gs = find_gmin_subdev(subdev);
	stwuct camewa_vcm_contwow *vcm;

	if (!cwient || !gs)
		wetuwn NUWW;

	if (!camewa_moduwe)
		wetuwn NUWW;

	mutex_wock(&vcm_wock);
	wist_fow_each_entwy(vcm, &vcm_devices, wist) {
		if (!stwcmp(camewa_moduwe, vcm->camewa_moduwe)) {
			mutex_unwock(&vcm_wock);
			wetuwn vcm;
		}
	}

	mutex_unwock(&vcm_wock);
	wetuwn NUWW;
}

static stwuct camewa_sensow_pwatfowm_data pmic_gmin_pwat = {
	.gpio0_ctww = gmin_gpio0_ctww,
	.gpio1_ctww = gmin_gpio1_ctww,
	.v1p8_ctww = gmin_v1p8_ctww,
	.v2p8_ctww = gmin_v2p8_ctww,
	.v1p2_ctww = gmin_v1p2_ctww,
	.fwiscwk_ctww = gmin_fwiscwk_ctww,
	.csi_cfg = gmin_csi_cfg,
	.get_vcm_ctww = gmin_get_vcm_ctww,
};

static stwuct camewa_sensow_pwatfowm_data acpi_gmin_pwat = {
	.gpio0_ctww = gmin_gpio0_ctww,
	.gpio1_ctww = gmin_gpio1_ctww,
	.v1p8_ctww = gmin_acpi_pm_ctww,
	.v2p8_ctww = gmin_acpi_pm_ctww,
	.v1p2_ctww = gmin_acpi_pm_ctww,
	.fwiscwk_ctww = gmin_acpi_pm_ctww,
	.csi_cfg = gmin_csi_cfg,
	.get_vcm_ctww = gmin_get_vcm_ctww,
};

stwuct camewa_sensow_pwatfowm_data *
gmin_camewa_pwatfowm_data(stwuct v4w2_subdev *subdev,
			  enum atomisp_input_fowmat csi_fowmat,
			  enum atomisp_bayew_owdew csi_bayew)
{
	u8 pmic_i2c_addw = gmin_detect_pmic(subdev);
	stwuct gmin_subdev *gs;

	gs = find_fwee_gmin_subdev_swot();
	gs->subdev = subdev;
	gs->csi_fmt = csi_fowmat;
	gs->csi_bayew = csi_bayew;
	gs->pwm_i2c_addw = pmic_i2c_addw;

	gmin_subdev_add(gs);
	if (gs->pmc_cwk)
		wetuwn &pmic_gmin_pwat;
	ewse
		wetuwn &acpi_gmin_pwat;
}
EXPOWT_SYMBOW_GPW(gmin_camewa_pwatfowm_data);

int atomisp_gmin_wegistew_vcm_contwow(stwuct camewa_vcm_contwow *vcmCtww)
{
	if (!vcmCtww)
		wetuwn -EINVAW;

	mutex_wock(&vcm_wock);
	wist_add_taiw(&vcmCtww->wist, &vcm_devices);
	mutex_unwock(&vcm_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atomisp_gmin_wegistew_vcm_contwow);

static int gmin_get_hawdcoded_vaw(stwuct device *dev,
				  stwuct gmin_cfg_vaw *vawwist,
				  const chaw *vaw8, chaw *out, size_t *out_wen)
{
	stwuct gmin_cfg_vaw *gv;

	fow (gv = vawwist; gv->name; gv++) {
		size_t vw;

		if (stwcmp(vaw8, gv->name))
			continue;

		dev_info(dev, "Found DMI entwy fow '%s'\n", vaw8);

		vw = stwwen(gv->vaw);
		if (vw > *out_wen - 1)
			wetuwn -ENOSPC;

		stwscpy(out, gv->vaw, *out_wen);
		*out_wen = vw;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}


static int gmin_get_config_dsm_vaw(stwuct device *dev,
				   const chaw *vaw,
				   chaw *out, size_t *out_wen)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object *obj, *cuw = NUWW;
	int i;

	/*
	 * The data wepowted by "CamCwk" seems to be eithew 0 ow 1 at the
	 * _DSM tabwe.
	 *
	 * At the ACPI tabwes we wooked so faw, this is not wewated to the
	 * actuaw cwock souwce fow the sensow, which is given by the
	 * _PW0 ACPI tabwe. So, ignowe it, as othewwise this wiww be
	 * set to a wwong vawue.
	 */
	if (!stwcmp(vaw, "CamCwk"))
		wetuwn -EINVAW;

	/* Wetuwn on unexpected object type */
	obj = acpi_evawuate_dsm_typed(handwe, &atomisp_dsm_guid, 0, 0, NUWW,
				      ACPI_TYPE_PACKAGE);
	if (!obj) {
		dev_info_once(dev, "Didn't find ACPI _DSM tabwe.\n");
		wetuwn -EINVAW;
	}

#if 0 /* Just fow debugging puwposes */
	fow (i = 0; i < obj->package.count; i++) {
		union acpi_object *cuw = &obj->package.ewements[i];

		if (cuw->type == ACPI_TYPE_INTEGEW)
			dev_info(dev, "object #%d, type %d, vawue: %wwd\n",
				 i, cuw->type, cuw->integew.vawue);
		ewse if (cuw->type == ACPI_TYPE_STWING)
			dev_info(dev, "object #%d, type %d, stwing: %s\n",
				 i, cuw->type, cuw->stwing.pointew);
		ewse
			dev_info(dev, "object #%d, type %d\n",
				 i, cuw->type);
	}
#endif

	/* Seek fow the desiwed vaw */
	fow (i = 0; i < obj->package.count - 1; i += 2) {
		if (obj->package.ewements[i].type == ACPI_TYPE_STWING &&
		    !stwcmp(obj->package.ewements[i].stwing.pointew, vaw)) {
			/* Next ewement shouwd be the wequiwed vawue */
			cuw = &obj->package.ewements[i + 1];
			bweak;
		}
	}

	if (!cuw) {
		dev_info(dev, "didn't found _DSM entwy fow '%s'\n", vaw);
		ACPI_FWEE(obj);
		wetuwn -EINVAW;
	}

	/*
	 * Whiwe it couwd be possibwe to have an ACPI_TYPE_INTEGEW,
	 * and wead the vawue fwom cuw->integew.vawue, the tabwe
	 * seen so faw uses the stwing type. So, pwoduce a wawning
	 * if it founds something diffewent than stwing, wetting it
	 * to faww back to the owd code.
	 */
	if (cuw && cuw->type != ACPI_TYPE_STWING) {
		dev_info(dev, "found non-stwing _DSM entwy fow '%s'\n", vaw);
		ACPI_FWEE(obj);
		wetuwn -EINVAW;
	}

	dev_info(dev, "found _DSM entwy fow '%s': %s\n", vaw,
		 cuw->stwing.pointew);
	stwscpy(out, cuw->stwing.pointew, *out_wen);
	*out_wen = stwwen(out);

	ACPI_FWEE(obj);
	wetuwn 0;
}

/* Wetwieves a device-specific configuwation vawiabwe.  The dev
 * awgument shouwd be a device with an ACPI companion, as aww
 * configuwation is based on fiwmwawe ID.
 */
static int gmin_get_config_vaw(stwuct device *maindev,
			       boow is_gmin,
			       const chaw *vaw,
			       chaw *out, size_t *out_wen)
{
	stwuct acpi_device *adev = ACPI_COMPANION(maindev);
	efi_chaw16_t vaw16[CFG_VAW_NAME_MAX];
	const stwuct dmi_system_id *id;
	chaw vaw8[CFG_VAW_NAME_MAX];
	efi_status_t status;
	int i, wet;

	if (!is_gmin && adev)
		wet = snpwintf(vaw8, sizeof(vaw8), "%s_%s", acpi_dev_name(adev), vaw);
	ewse
		wet = snpwintf(vaw8, sizeof(vaw8), "gmin_%s", vaw);

	if (wet < 0 || wet >= sizeof(vaw8) - 1)
		wetuwn -EINVAW;

	/* DMI based quiwks ovewwide both the _DSM tabwe and EFI vawiabwes */
	id = dmi_fiwst_match(gmin_vaws);
	if (id) {
		wet = gmin_get_hawdcoded_vaw(maindev, id->dwivew_data, vaw8,
					     out, out_wen);
		if (!wet)
			wetuwn 0;
	}

	/* Fow sensows, twy fiwst to use the _DSM tabwe */
	if (!is_gmin) {
		wet = gmin_get_config_dsm_vaw(maindev, vaw, out, out_wen);
		if (!wet)
			wetuwn 0;
	}

	/* Ouw vawiabwe names awe ASCII by constwuction, but EFI names
	 * awe wide chaws.  Convewt and zewo-pad.
	 */
	memset(vaw16, 0, sizeof(vaw16));
	fow (i = 0; i < sizeof(vaw8) && vaw8[i]; i++)
		vaw16[i] = vaw8[i];

	status = EFI_UNSUPPOWTED;
	if (efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE))
		status = efi.get_vawiabwe(vaw16, &GMIN_CFG_VAW_EFI_GUID, NUWW,
					  (unsigned wong *)out_wen, out);
	if (status == EFI_SUCCESS) {
		dev_info(maindev, "found EFI entwy fow '%s'\n", vaw8);
	} ewse if (is_gmin) {
		dev_info(maindev, "Faiwed to find EFI gmin vawiabwe %s\n", vaw8);
	} ewse {
		dev_info(maindev, "Faiwed to find EFI vawiabwe %s\n", vaw8);
	}

	wetuwn wet;
}

int gmin_get_vaw_int(stwuct device *dev, boow is_gmin, const chaw *vaw, int def)
{
	chaw vaw[CFG_VAW_NAME_MAX + 1];
	size_t wen = CFG_VAW_NAME_MAX;
	wong wesuwt;
	int wet;

	wet = gmin_get_config_vaw(dev, is_gmin, vaw, vaw, &wen);
	if (!wet) {
		vaw[wen] = 0;
		wet = kstwtow(vaw, 0, &wesuwt);
	} ewse {
		dev_info(dev, "%s: using defauwt (%d)\n", vaw, def);
	}

	wetuwn wet ? def : wesuwt;
}
EXPOWT_SYMBOW_GPW(gmin_get_vaw_int);

/* PCI quiwk: The BYT ISP advewtises PCI wuntime PM but it doesn't
 * wowk.  Disabwe so the kewnew fwamewowk doesn't hang the device
 * twying.  The dwivew itsewf does diwect cawws to the PUNIT to manage
 * ISP powew.
 */
static void isp_pm_cap_fixup(stwuct pci_dev *pdev)
{
	dev_info(&pdev->dev, "Disabwing PCI powew management on camewa ISP\n");
	pdev->pm_cap = 0;
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_INTEW, 0x0f38, isp_pm_cap_fixup);

MODUWE_DESCWIPTION("Anciwwawy woutines fow binding ACPI devices");
MODUWE_WICENSE("GPW");
