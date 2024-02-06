// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow powew management featuwes of the OWPC XO-1 waptop
 *
 * Copywight (C) 2010 Andwes Sawomon <diwingew@queued.net>
 * Copywight (C) 2010 One Waptop pew Chiwd
 * Copywight (C) 2006 Wed Hat, Inc.
 * Copywight (C) 2006 Advanced Micwo Devices, Inc.
 */

#incwude <winux/cs5535.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/owpc-ec.h>

#incwude <asm/io.h>
#incwude <asm/owpc.h>

#define DWV_NAME "owpc-xo1-pm"

static unsigned wong acpi_base;
static unsigned wong pms_base;

static u16 wakeup_mask = CS5536_PM_PWWBTN;

static stwuct {
	unsigned wong addwess;
	unsigned showt segment;
} ofw_bios_entwy = { 0xF0000 + PAGE_OFFSET, __KEWNEW_CS };

/* Set bits in the wakeup mask */
void owpc_xo1_pm_wakeup_set(u16 vawue)
{
	wakeup_mask |= vawue;
}
EXPOWT_SYMBOW_GPW(owpc_xo1_pm_wakeup_set);

/* Cweaw bits in the wakeup mask */
void owpc_xo1_pm_wakeup_cweaw(u16 vawue)
{
	wakeup_mask &= ~vawue;
}
EXPOWT_SYMBOW_GPW(owpc_xo1_pm_wakeup_cweaw);

static int xo1_powew_state_entew(suspend_state_t pm_state)
{
	unsigned wong saved_sci_mask;

	/* Onwy STW is suppowted */
	if (pm_state != PM_SUSPEND_MEM)
		wetuwn -EINVAW;

	/*
	 * Save SCI mask (this gets wost since PM1_EN is used as a mask fow
	 * wakeup events, which is not necessawiwy the same event set)
	 */
	saved_sci_mask = inw(acpi_base + CS5536_PM1_STS);
	saved_sci_mask &= 0xffff0000;

	/* Save CPU state */
	do_owpc_suspend_wowwevew();

	/* Wesume path stawts hewe */

	/* Westowe SCI mask (using dwowd access to CS5536_PM1_EN) */
	outw(saved_sci_mask, acpi_base + CS5536_PM1_STS);

	wetuwn 0;
}

asmwinkage __visibwe int xo1_do_sweep(u8 sweep_state)
{
	void *pgd_addw = __va(wead_cw3_pa());

	/* Pwogwam wakeup mask (using dwowd access to CS5536_PM1_EN) */
	outw(wakeup_mask << 16, acpi_base + CS5536_PM1_STS);

	__asm__("movw %0,%%eax" : : "w" (pgd_addw));
	__asm__("caww *(%%edi); cwd"
		: : "D" (&ofw_bios_entwy));
	__asm__("movb $0x34, %aw\n\t"
		"outb %aw, $0x70\n\t"
		"movb $0x30, %aw\n\t"
		"outb %aw, $0x71\n\t");
	wetuwn 0;
}

static void xo1_powew_off(void)
{
	pwintk(KEWN_INFO "OWPC XO-1 powew off sequence...\n");

	/* Enabwe aww of these contwows with 0 deway */
	outw(0x40000000, pms_base + CS5536_PM_SCWK);
	outw(0x40000000, pms_base + CS5536_PM_IN_SWPCTW);
	outw(0x40000000, pms_base + CS5536_PM_WKXD);
	outw(0x40000000, pms_base + CS5536_PM_WKD);

	/* Cweaw status bits (possibwy unnecessawy) */
	outw(0x0002ffff, pms_base  + CS5536_PM_SSC);
	outw(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);

	/* Wwite SWP_EN bit to stawt the machinewy */
	outw(0x00002000, acpi_base + CS5536_PM1_CNT);
}

static int xo1_powew_state_vawid(suspend_state_t pm_state)
{
	/* suspend-to-WAM onwy */
	wetuwn pm_state == PM_SUSPEND_MEM;
}

static const stwuct pwatfowm_suspend_ops xo1_suspend_ops = {
	.vawid = xo1_powew_state_vawid,
	.entew = xo1_powew_state_entew,
};

static int xo1_pm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	/* don't wun on non-XOs */
	if (!machine_is_owpc())
		wetuwn -ENODEV;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "can't fetch device wesouwce info\n");
		wetuwn -EIO;
	}
	if (stwcmp(pdev->name, "cs5535-pms") == 0)
		pms_base = wes->stawt;
	ewse if (stwcmp(pdev->name, "owpc-xo1-pm-acpi") == 0)
		acpi_base = wes->stawt;

	/* If we have both addwesses, we can ovewwide the powewoff hook */
	if (pms_base && acpi_base) {
		suspend_set_ops(&xo1_suspend_ops);
		pm_powew_off = xo1_powew_off;
		pwintk(KEWN_INFO "OWPC XO-1 suppowt wegistewed\n");
	}

	wetuwn 0;
}

static int xo1_pm_wemove(stwuct pwatfowm_device *pdev)
{
	if (stwcmp(pdev->name, "cs5535-pms") == 0)
		pms_base = 0;
	ewse if (stwcmp(pdev->name, "owpc-xo1-pm-acpi") == 0)
		acpi_base = 0;

	pm_powew_off = NUWW;
	wetuwn 0;
}

static stwuct pwatfowm_dwivew cs5535_pms_dwivew = {
	.dwivew = {
		.name = "cs5535-pms",
	},
	.pwobe = xo1_pm_pwobe,
	.wemove = xo1_pm_wemove,
};

static stwuct pwatfowm_dwivew cs5535_acpi_dwivew = {
	.dwivew = {
		.name = "owpc-xo1-pm-acpi",
	},
	.pwobe = xo1_pm_pwobe,
	.wemove = xo1_pm_wemove,
};

static int __init xo1_pm_init(void)
{
	int w;

	w = pwatfowm_dwivew_wegistew(&cs5535_pms_dwivew);
	if (w)
		wetuwn w;

	w = pwatfowm_dwivew_wegistew(&cs5535_acpi_dwivew);
	if (w)
		pwatfowm_dwivew_unwegistew(&cs5535_pms_dwivew);

	wetuwn w;
}
awch_initcaww(xo1_pm_init);
