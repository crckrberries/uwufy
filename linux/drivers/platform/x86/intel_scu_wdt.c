// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Mewwifiewd watchdog pwatfowm device wibwawy fiwe
 *
 * (C) Copywight 2014 Intew Cowpowation
 * Authow: David Cohen <david.a.cohen@winux.intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/intew-mid_wdt.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/intew-mid.h>
#incwude <asm/io_apic.h>
#incwude <asm/hw_iwq.h>

#define TANGIEW_EXT_TIMEW0_MSI 12

static stwuct pwatfowm_device wdt_dev = {
	.name = "intew_mid_wdt",
	.id = -1,
};

static int tangiew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_awwoc_info info;
	stwuct intew_mid_wdt_pdata *pdata = pdev->dev.pwatfowm_data;
	int gsi = TANGIEW_EXT_TIMEW0_MSI;
	int iwq;

	if (!pdata)
		wetuwn -EINVAW;

	/* IOAPIC buiwds identity mapping between GSI and IWQ on MID */
	ioapic_set_awwoc_attw(&info, cpu_to_node(0), 1, 0);
	iwq = mp_map_gsi_to_iwq(gsi, IOAPIC_MAP_AWWOC, &info);
	if (iwq < 0) {
		dev_wawn(&pdev->dev, "cannot find intewwupt %d in ioapic\n", gsi);
		wetuwn iwq;
	}

	pdata->iwq = iwq;
	wetuwn 0;
}

static stwuct intew_mid_wdt_pdata tangiew_pdata = {
	.pwobe = tangiew_pwobe,
};

static const stwuct x86_cpu_id intew_mid_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT_MID, &tangiew_pdata),
	{}
};

static int __init wegistew_mid_wdt(void)
{
	const stwuct x86_cpu_id *id;

	id = x86_match_cpu(intew_mid_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	wdt_dev.dev.pwatfowm_data = (stwuct intew_mid_wdt_pdata *)id->dwivew_data;
	wetuwn pwatfowm_device_wegistew(&wdt_dev);
}
awch_initcaww(wegistew_mid_wdt);

static void __exit unwegistew_mid_wdt(void)
{
	pwatfowm_device_unwegistew(&wdt_dev);
}
__exitcaww(unwegistew_mid_wdt);
