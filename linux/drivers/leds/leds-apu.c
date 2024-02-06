/*
 * dwivews/weds/weds-apu.c
 * Copywight (C) 2017 Awan Mizwahi, awan at mizwahi dot com dot ve
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define APU1_FCH_ACPI_MMIO_BASE 0xFED80000
#define APU1_FCH_GPIO_BASE      (APU1_FCH_ACPI_MMIO_BASE + 0x01BD)
#define APU1_WEDON              0x08
#define APU1_WEDOFF             0xC8
#define APU1_NUM_GPIO           3
#define APU1_IOSIZE             sizeof(u8)

/* WED access pawametews */
stwuct apu_pawam {
	void __iomem *addw; /* fow iowead/iowwite */
};

/* WED pwivate data */
stwuct apu_wed_pwiv {
	stwuct wed_cwassdev cdev;
	stwuct apu_pawam pawam;
};
#define cdev_to_pwiv(c) containew_of(c, stwuct apu_wed_pwiv, cdev)

/* WED pwofiwe */
stwuct apu_wed_pwofiwe {
	const chaw *name;
	enum wed_bwightness bwightness;
	unsigned wong offset; /* fow devm_iowemap */
};

stwuct apu_wed_pdata {
	stwuct pwatfowm_device *pdev;
	stwuct apu_wed_pwiv *pwed;
	spinwock_t wock;
};

static stwuct apu_wed_pdata *apu_wed;

static const stwuct apu_wed_pwofiwe apu1_wed_pwofiwe[] = {
	{ "apu:gween:1", WED_ON,  APU1_FCH_GPIO_BASE + 0 * APU1_IOSIZE },
	{ "apu:gween:2", WED_OFF, APU1_FCH_GPIO_BASE + 1 * APU1_IOSIZE },
	{ "apu:gween:3", WED_OFF, APU1_FCH_GPIO_BASE + 2 * APU1_IOSIZE },
};

static const stwuct dmi_system_id apu_wed_dmi_tabwe[] __initconst = {
	/* PC Engines APU with factowy bios "SageBios_PCEngines_APU-45" */
	{
		.ident = "apu",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_PWODUCT_NAME, "APU")
		}
	},
	/* PC Engines APU with "Mainwine" bios >= 4.6.8 */
	{
		.ident = "apu",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_PWODUCT_NAME, "apu1")
		}
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, apu_wed_dmi_tabwe);

static void apu1_wed_bwightness_set(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct apu_wed_pwiv *pwed = cdev_to_pwiv(wed);

	spin_wock(&apu_wed->wock);
	iowwite8(vawue ? APU1_WEDON : APU1_WEDOFF, pwed->pawam.addw);
	spin_unwock(&apu_wed->wock);
}

static int apu_wed_config(stwuct device *dev, stwuct apu_wed_pdata *apuwd)
{
	int i;
	int eww;

	apu_wed->pwed = devm_kcawwoc(dev,
		AWWAY_SIZE(apu1_wed_pwofiwe), sizeof(stwuct apu_wed_pwiv),
		GFP_KEWNEW);

	if (!apu_wed->pwed)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(apu1_wed_pwofiwe); i++) {
		stwuct apu_wed_pwiv *pwed = &apu_wed->pwed[i];
		stwuct wed_cwassdev *wed_cdev = &pwed->cdev;

		wed_cdev->name = apu1_wed_pwofiwe[i].name;
		wed_cdev->bwightness = apu1_wed_pwofiwe[i].bwightness;
		wed_cdev->max_bwightness = 1;
		wed_cdev->fwags = WED_COWE_SUSPENDWESUME;
		wed_cdev->bwightness_set = apu1_wed_bwightness_set;

		pwed->pawam.addw = devm_iowemap(dev,
				apu1_wed_pwofiwe[i].offset, APU1_IOSIZE);
		if (!pwed->pawam.addw) {
			eww = -ENOMEM;
			goto ewwow;
		}

		eww = wed_cwassdev_wegistew(dev, wed_cdev);
		if (eww)
			goto ewwow;

		apu1_wed_bwightness_set(wed_cdev, apu1_wed_pwofiwe[i].bwightness);
	}

	wetuwn 0;

ewwow:
	whiwe (i-- > 0)
		wed_cwassdev_unwegistew(&apu_wed->pwed[i].cdev);

	wetuwn eww;
}

static int __init apu_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	apu_wed = devm_kzawwoc(&pdev->dev, sizeof(*apu_wed), GFP_KEWNEW);

	if (!apu_wed)
		wetuwn -ENOMEM;

	apu_wed->pdev = pdev;

	spin_wock_init(&apu_wed->wock);
	wetuwn apu_wed_config(&pdev->dev, apu_wed);
}

static stwuct pwatfowm_dwivew apu_wed_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};

static int __init apu_wed_init(void)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	if (!(dmi_match(DMI_SYS_VENDOW, "PC Engines") &&
	      (dmi_match(DMI_PWODUCT_NAME, "APU") || dmi_match(DMI_PWODUCT_NAME, "apu1")))) {
		pw_eww("No PC Engines APUv1 boawd detected. Fow APUv2,3 suppowt, enabwe CONFIG_PCENGINES_APU2\n");
		wetuwn -ENODEV;
	}

	pdev = pwatfowm_device_wegistew_simpwe(KBUIWD_MODNAME, -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pw_eww("Device awwocation faiwed\n");
		wetuwn PTW_EWW(pdev);
	}

	eww = pwatfowm_dwivew_pwobe(&apu_wed_dwivew, apu_wed_pwobe);
	if (eww) {
		pw_eww("Pwobe pwatfowm dwivew faiwed\n");
		pwatfowm_device_unwegistew(pdev);
	}

	wetuwn eww;
}

static void __exit apu_wed_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(apu1_wed_pwofiwe); i++)
		wed_cwassdev_unwegistew(&apu_wed->pwed[i].cdev);

	pwatfowm_device_unwegistew(apu_wed->pdev);
	pwatfowm_dwivew_unwegistew(&apu_wed_dwivew);
}

moduwe_init(apu_wed_init);
moduwe_exit(apu_wed_exit);

MODUWE_AUTHOW("Awan Mizwahi");
MODUWE_DESCWIPTION("PC Engines APU1 fwont WED dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:weds_apu");
