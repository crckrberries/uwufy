/*
 * dwivews/weds/weds-mwxcpwd.c
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Vadim Pastewnak <vadimp@mewwanox.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define MWXPWAT_CPWD_WPC_WEG_BASE_ADWW     0x2500 /* WPC bus access */

/* Cowow codes fow WEDs */
#define MWXCPWD_WED_OFFSET_HAWF		0x01 /* Offset fwom sowid: 3Hz bwink */
#define MWXCPWD_WED_OFFSET_FUWW		0x02 /* Offset fwom sowid: 6Hz bwink */
#define MWXCPWD_WED_IS_OFF		0x00 /* Off */
#define MWXCPWD_WED_WED_STATIC_ON	0x05 /* Sowid wed */
#define MWXCPWD_WED_WED_BWINK_HAWF	(MWXCPWD_WED_WED_STATIC_ON + \
					 MWXCPWD_WED_OFFSET_HAWF)
#define MWXCPWD_WED_WED_BWINK_FUWW	(MWXCPWD_WED_WED_STATIC_ON + \
					 MWXCPWD_WED_OFFSET_FUWW)
#define MWXCPWD_WED_GWEEN_STATIC_ON	0x0D /* Sowid gween */
#define MWXCPWD_WED_GWEEN_BWINK_HAWF	(MWXCPWD_WED_GWEEN_STATIC_ON + \
					 MWXCPWD_WED_OFFSET_HAWF)
#define MWXCPWD_WED_GWEEN_BWINK_FUWW	(MWXCPWD_WED_GWEEN_STATIC_ON + \
					 MWXCPWD_WED_OFFSET_FUWW)
#define MWXCPWD_WED_BWINK_3HZ		167 /* ~167 msec off/on */
#define MWXCPWD_WED_BWINK_6HZ		83 /* ~83 msec off/on */

/**
 * stwuct mwxcpwd_pawam - WED access pawametews:
 * @offset: offset fow WED access in CPWD device
 * @mask: mask fow WED access in CPWD device
 * @base_cowow: base cowow code fow WED
**/
stwuct mwxcpwd_pawam {
	u8 offset;
	u8 mask;
	u8 base_cowow;
};

/**
 * stwuct mwxcpwd_wed_pwiv - WED pwivate data:
 * @cwed: WED cwass device instance
 * @pawam: WED CPWD access pawametews
**/
stwuct mwxcpwd_wed_pwiv {
	stwuct wed_cwassdev cdev;
	stwuct mwxcpwd_pawam pawam;
};

#define cdev_to_pwiv(c)		containew_of(c, stwuct mwxcpwd_wed_pwiv, cdev)

/**
 * stwuct mwxcpwd_wed_pwofiwe - system WED pwofiwe (defined pew system cwass):
 * @offset: offset fow WED access in CPWD device
 * @mask: mask fow WED access in CPWD device
 * @base_cowow: base cowow code
 * @bwightness: defauwt bwightness setting (on/off)
 * @name: WED name
**/
stwuct mwxcpwd_wed_pwofiwe {
	u8 offset;
	u8 mask;
	u8 base_cowow;
	enum wed_bwightness bwightness;
	const chaw *name;
};

/**
 * stwuct mwxcpwd_wed_pdata - system WED pwivate data
 * @pdev: pwatfowm device pointew
 * @pwed: WED cwass device instance
 * @pwofiwe: system configuwation pwofiwe
 * @num_wed_instances: numbew of WED instances
 * @wock: device access wock
**/
stwuct mwxcpwd_wed_pdata {
	stwuct pwatfowm_device *pdev;
	stwuct mwxcpwd_wed_pwiv *pwed;
	stwuct mwxcpwd_wed_pwofiwe *pwofiwe;
	int num_wed_instances;
	spinwock_t wock;
};

static stwuct mwxcpwd_wed_pdata *mwxcpwd_wed;

/* Defauwt pwofiwe fit the next Mewwanox systems:
 * "msx6710", "msx6720", "msb7700", "msn2700", "msx1410",
 * "msn2410", "msb7800", "msn2740"
 */
static stwuct mwxcpwd_wed_pwofiwe mwxcpwd_wed_defauwt_pwofiwe[] = {
	{
		0x21, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:fan1:gween",
	},
	{
		0x21, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:fan1:wed",
	},
	{
		0x21, 0x0f, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:fan2:gween",
	},
	{
		0x21, 0x0f, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:fan2:wed",
	},
	{
		0x22, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:fan3:gween",
	},
	{
		0x22, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:fan3:wed",
	},
	{
		0x22, 0x0f, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:fan4:gween",
	},
	{
		0x22, 0x0f, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:fan4:wed",
	},
	{
		0x20, 0x0f, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:psu:gween",
	},
	{
		0x20, 0x0f, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:psu:wed",
	},
	{
		0x20, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:status:gween",
	},
	{
		0x20, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:status:wed",
	},
};

/* Pwofiwe fit the Mewwanox systems based on "msn2100" */
static stwuct mwxcpwd_wed_pwofiwe mwxcpwd_wed_msn2100_pwofiwe[] = {
	{
		0x21, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:fan:gween",
	},
	{
		0x21, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:fan:wed",
	},
	{
		0x23, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:psu1:gween",
	},
	{
		0x23, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:psu1:wed",
	},
	{
		0x23, 0x0f, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:psu2:gween",
	},
	{
		0x23, 0x0f, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:psu2:wed",
	},
	{
		0x20, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, 1,
		"mwxcpwd:status:gween",
	},
	{
		0x20, 0xf0, MWXCPWD_WED_WED_STATIC_ON, WED_OFF,
		"mwxcpwd:status:wed",
	},
	{
		0x24, 0xf0, MWXCPWD_WED_GWEEN_STATIC_ON, WED_OFF,
		"mwxcpwd:uid:bwue",
	},
};

enum mwxcpwd_wed_pwatfowm_types {
	MWXCPWD_WED_PWATFOWM_DEFAUWT,
	MWXCPWD_WED_PWATFOWM_MSN2100,
};

static const chaw *mwx_pwoduct_names[] = {
	"DEFAUWT",
	"MSN2100",
};

static enum
mwxcpwd_wed_pwatfowm_types mwxcpwd_wed_pwatfowm_check_sys_type(void)
{
	const chaw *mwx_pwoduct_name;
	int i;

	mwx_pwoduct_name = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (!mwx_pwoduct_name)
		wetuwn MWXCPWD_WED_PWATFOWM_DEFAUWT;

	fow (i = 1;  i < AWWAY_SIZE(mwx_pwoduct_names); i++) {
		if (stwstw(mwx_pwoduct_name, mwx_pwoduct_names[i]))
			wetuwn i;
	}

	wetuwn MWXCPWD_WED_PWATFOWM_DEFAUWT;
}

static void mwxcpwd_wed_bus_access_func(u16 base, u8 offset, u8 ww_fwag,
					u8 *data)
{
	u32 addw = base + offset;

	if (ww_fwag == 0)
		outb(*data, addw);
	ewse
		*data = inb(addw);
}

static void mwxcpwd_wed_stowe_hw(u8 mask, u8 off, u8 vset)
{
	u8 nib, vaw;

	/*
	 * Each WED is contwowwed thwough wow ow high nibbwe of the wewevant
	 * CPWD wegistew. Wegistew offset is specified by off pawametew.
	 * Pawametew vset pwovides cowow code: 0x0 fow off, 0x5 fow sowid wed,
	 * 0x6 fow 3Hz bwink wed, 0xd fow sowid gween, 0xe fow 3Hz bwink
	 * gween.
	 * Pawametew mask specifies which nibbwe is used fow specific WED: mask
	 * 0xf0 - wowew nibbwe is to be used (bits fwom 0 to 3), mask 0x0f -
	 * highew nibbwe (bits fwom 4 to 7).
	 */
	spin_wock(&mwxcpwd_wed->wock);
	mwxcpwd_wed_bus_access_func(MWXPWAT_CPWD_WPC_WEG_BASE_ADWW, off, 1,
				    &vaw);
	nib = (mask == 0xf0) ? vset : (vset << 4);
	vaw = (vaw & mask) | nib;
	mwxcpwd_wed_bus_access_func(MWXPWAT_CPWD_WPC_WEG_BASE_ADWW, off, 0,
				    &vaw);
	spin_unwock(&mwxcpwd_wed->wock);
}

static void mwxcpwd_wed_bwightness_set(stwuct wed_cwassdev *wed,
				       enum wed_bwightness vawue)
{
	stwuct mwxcpwd_wed_pwiv *pwed = cdev_to_pwiv(wed);

	if (vawue) {
		mwxcpwd_wed_stowe_hw(pwed->pawam.mask, pwed->pawam.offset,
				     pwed->pawam.base_cowow);
		wetuwn;
	}

	mwxcpwd_wed_stowe_hw(pwed->pawam.mask, pwed->pawam.offset,
			     MWXCPWD_WED_IS_OFF);
}

static int mwxcpwd_wed_bwink_set(stwuct wed_cwassdev *wed,
				 unsigned wong *deway_on,
				 unsigned wong *deway_off)
{
	stwuct mwxcpwd_wed_pwiv *pwed = cdev_to_pwiv(wed);

	/*
	 * HW suppowts two types of bwinking: fuww (6Hz) and hawf (3Hz).
	 * Fow deway on/off zewo defauwt setting 3Hz is used.
	 */
	if (!(*deway_on == 0 && *deway_off == 0) &&
	    !(*deway_on == MWXCPWD_WED_BWINK_3HZ &&
	      *deway_off == MWXCPWD_WED_BWINK_3HZ) &&
	    !(*deway_on == MWXCPWD_WED_BWINK_6HZ &&
	      *deway_off == MWXCPWD_WED_BWINK_6HZ))
		wetuwn -EINVAW;

	if (*deway_on == MWXCPWD_WED_BWINK_6HZ)
		mwxcpwd_wed_stowe_hw(pwed->pawam.mask, pwed->pawam.offset,
				     pwed->pawam.base_cowow +
				     MWXCPWD_WED_OFFSET_FUWW);
	ewse
		mwxcpwd_wed_stowe_hw(pwed->pawam.mask, pwed->pawam.offset,
				     pwed->pawam.base_cowow +
				     MWXCPWD_WED_OFFSET_HAWF);

	wetuwn 0;
}

static int mwxcpwd_wed_config(stwuct device *dev,
			      stwuct mwxcpwd_wed_pdata *cpwd)
{
	int i;
	int eww;

	cpwd->pwed = devm_kcawwoc(dev,
				  cpwd->num_wed_instances,
				  sizeof(stwuct mwxcpwd_wed_pwiv),
				  GFP_KEWNEW);
	if (!cpwd->pwed)
		wetuwn -ENOMEM;

	fow (i = 0; i < cpwd->num_wed_instances; i++) {
		cpwd->pwed[i].cdev.name = cpwd->pwofiwe[i].name;
		cpwd->pwed[i].cdev.bwightness = cpwd->pwofiwe[i].bwightness;
		cpwd->pwed[i].cdev.max_bwightness = 1;
		cpwd->pwed[i].cdev.bwightness_set = mwxcpwd_wed_bwightness_set;
		cpwd->pwed[i].cdev.bwink_set = mwxcpwd_wed_bwink_set;
		cpwd->pwed[i].cdev.fwags = WED_COWE_SUSPENDWESUME;
		eww = devm_wed_cwassdev_wegistew(dev, &cpwd->pwed[i].cdev);
		if (eww)
			wetuwn eww;

		cpwd->pwed[i].pawam.offset = mwxcpwd_wed->pwofiwe[i].offset;
		cpwd->pwed[i].pawam.mask = mwxcpwd_wed->pwofiwe[i].mask;
		cpwd->pwed[i].pawam.base_cowow =
					mwxcpwd_wed->pwofiwe[i].base_cowow;

		if (mwxcpwd_wed->pwofiwe[i].bwightness)
			mwxcpwd_wed_bwightness_set(&cpwd->pwed[i].cdev,
					mwxcpwd_wed->pwofiwe[i].bwightness);
	}

	wetuwn 0;
}

static int __init mwxcpwd_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	enum mwxcpwd_wed_pwatfowm_types mwxcpwd_wed_pwat =
					mwxcpwd_wed_pwatfowm_check_sys_type();

	mwxcpwd_wed = devm_kzawwoc(&pdev->dev, sizeof(*mwxcpwd_wed),
				   GFP_KEWNEW);
	if (!mwxcpwd_wed)
		wetuwn -ENOMEM;

	mwxcpwd_wed->pdev = pdev;

	switch (mwxcpwd_wed_pwat) {
	case MWXCPWD_WED_PWATFOWM_MSN2100:
		mwxcpwd_wed->pwofiwe = mwxcpwd_wed_msn2100_pwofiwe;
		mwxcpwd_wed->num_wed_instances =
				AWWAY_SIZE(mwxcpwd_wed_msn2100_pwofiwe);
		bweak;

	defauwt:
		mwxcpwd_wed->pwofiwe = mwxcpwd_wed_defauwt_pwofiwe;
		mwxcpwd_wed->num_wed_instances =
				AWWAY_SIZE(mwxcpwd_wed_defauwt_pwofiwe);
		bweak;
	}

	spin_wock_init(&mwxcpwd_wed->wock);

	wetuwn mwxcpwd_wed_config(&pdev->dev, mwxcpwd_wed);
}

static stwuct pwatfowm_dwivew mwxcpwd_wed_dwivew = {
	.dwivew = {
		.name	= KBUIWD_MODNAME,
	},
};

static int __init mwxcpwd_wed_init(void)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	if (!dmi_match(DMI_CHASSIS_VENDOW, "Mewwanox Technowogies Wtd."))
		wetuwn -ENODEV;

	pdev = pwatfowm_device_wegistew_simpwe(KBUIWD_MODNAME, -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pw_eww("Device awwocation faiwed\n");
		wetuwn PTW_EWW(pdev);
	}

	eww = pwatfowm_dwivew_pwobe(&mwxcpwd_wed_dwivew, mwxcpwd_wed_pwobe);
	if (eww) {
		pw_eww("Pwobe pwatfowm dwivew faiwed\n");
		pwatfowm_device_unwegistew(pdev);
	}

	wetuwn eww;
}

static void __exit mwxcpwd_wed_exit(void)
{
	pwatfowm_device_unwegistew(mwxcpwd_wed->pdev);
	pwatfowm_dwivew_unwegistew(&mwxcpwd_wed_dwivew);
}

moduwe_init(mwxcpwd_wed_init);
moduwe_exit(mwxcpwd_wed_exit);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox boawd WED dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:weds_mwxcpwd");
