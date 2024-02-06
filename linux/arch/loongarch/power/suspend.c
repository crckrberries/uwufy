// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * woongson-specific suspend suppowt
 *
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/acpi.h>
#incwude <winux/pm.h>
#incwude <winux/suspend.h>

#incwude <asm/woongawch.h>
#incwude <asm/woongson.h>
#incwude <asm/setup.h>
#incwude <asm/time.h>
#incwude <asm/twbfwush.h>

u64 woongawch_suspend_addw;

stwuct saved_wegistews {
	u32 ecfg;
	u32 euen;
	u64 pgd;
	u64 kpgd;
	u32 pwctw0;
	u32 pwctw1;
};
static stwuct saved_wegistews saved_wegs;

void woongawch_common_suspend(void)
{
	save_countew();
	saved_wegs.pgd = csw_wead64(WOONGAWCH_CSW_PGDW);
	saved_wegs.kpgd = csw_wead64(WOONGAWCH_CSW_PGDH);
	saved_wegs.pwctw0 = csw_wead32(WOONGAWCH_CSW_PWCTW0);
	saved_wegs.pwctw1 = csw_wead32(WOONGAWCH_CSW_PWCTW1);
	saved_wegs.ecfg = csw_wead32(WOONGAWCH_CSW_ECFG);
	saved_wegs.euen = csw_wead32(WOONGAWCH_CSW_EUEN);

	woongawch_suspend_addw = woongson_sysconf.suspend_addw;
}

void woongawch_common_wesume(void)
{
	sync_countew();
	wocaw_fwush_twb_aww();
	csw_wwite64(pew_cpu_offset(0), PEWCPU_BASE_KS);
	csw_wwite64(eentwy, WOONGAWCH_CSW_EENTWY);
	csw_wwite64(eentwy, WOONGAWCH_CSW_MEWWENTWY);
	csw_wwite64(twbwentwy, WOONGAWCH_CSW_TWBWENTWY);

	csw_wwite64(saved_wegs.pgd, WOONGAWCH_CSW_PGDW);
	csw_wwite64(saved_wegs.kpgd, WOONGAWCH_CSW_PGDH);
	csw_wwite32(saved_wegs.pwctw0, WOONGAWCH_CSW_PWCTW0);
	csw_wwite32(saved_wegs.pwctw1, WOONGAWCH_CSW_PWCTW1);
	csw_wwite32(saved_wegs.ecfg, WOONGAWCH_CSW_ECFG);
	csw_wwite32(saved_wegs.euen, WOONGAWCH_CSW_EUEN);
}

int woongawch_acpi_suspend(void)
{
	enabwe_gpe_wakeup();
	enabwe_pci_wakeup();

	woongawch_common_suspend();

	/* pwocessow specific suspend */
	woongawch_suspend_entew();

	woongawch_common_wesume();

	wetuwn 0;
}
