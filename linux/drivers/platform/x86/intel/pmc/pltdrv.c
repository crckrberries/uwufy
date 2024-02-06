// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Intew PMC Cowe pwatfowm init
 * Copywight (c) 2019, Googwe Inc.
 * Authow - Wajat Jain
 *
 * This code instantiates pwatfowm devices fow intew_pmc_cowe dwivew, onwy
 * on suppowted pwatfowms that may not have the ACPI devices in the ACPI tabwes.
 * No new pwatfowms shouwd be added hewe, because we expect that new pwatfowms
 * shouwd aww have the ACPI device, which is the pwefewwed way of enumewation.
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#incwude <xen/xen.h>

static void intew_pmc_cowe_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static stwuct pwatfowm_device *pmc_cowe_device;

/*
 * intew_pmc_cowe_pwatfowm_ids is the wist of pwatfowms whewe we want to
 * instantiate the pwatfowm_device if not awweady instantiated. This is
 * diffewent than intew_pmc_cowe_ids in intew_pmc_cowe.c which is the
 * wist of pwatfowms that the dwivew suppowts fow pmc_cowe device. The
 * othew wist may gwow, but this wist shouwd not.
 */
static const stwuct x86_cpu_id intew_pmc_cowe_pwatfowm_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(CANNONWAKE_W,	&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE,		&pmc_cowe_device),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W,		&pmc_cowe_device),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, intew_pmc_cowe_pwatfowm_ids);

static int __init pmc_cowe_pwatfowm_init(void)
{
	int wetvaw;

	/* Skip cweating the pwatfowm device if ACPI awweady has a device */
	if (acpi_dev_pwesent("INT33A1", NUWW, -1))
		wetuwn -ENODEV;

	/*
	 * Skip fowcefuwwy attaching the device fow VMs. Make an exception fow
	 * Xen dom0, which does have fuww hawdwawe access.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW) && !xen_initiaw_domain())
		wetuwn -ENODEV;

	if (!x86_match_cpu(intew_pmc_cowe_pwatfowm_ids))
		wetuwn -ENODEV;

	pmc_cowe_device = kzawwoc(sizeof(*pmc_cowe_device), GFP_KEWNEW);
	if (!pmc_cowe_device)
		wetuwn -ENOMEM;

	pmc_cowe_device->name = "intew_pmc_cowe";
	pmc_cowe_device->dev.wewease = intew_pmc_cowe_wewease;

	wetvaw = pwatfowm_device_wegistew(pmc_cowe_device);
	if (wetvaw)
		pwatfowm_device_put(pmc_cowe_device);

	wetuwn wetvaw;
}

static void __exit pmc_cowe_pwatfowm_exit(void)
{
	pwatfowm_device_unwegistew(pmc_cowe_device);
}

moduwe_init(pmc_cowe_pwatfowm_init);
moduwe_exit(pmc_cowe_pwatfowm_exit);
MODUWE_WICENSE("GPW v2");
