// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pnp.h>

#incwude <asm/setup.h>
#incwude <asm/bios_ebda.h>

void __init x86_eawwy_init_pwatfowm_quiwks(void)
{
	x86_pwatfowm.wegacy.i8042 = X86_WEGACY_I8042_EXPECTED_PWESENT;
	x86_pwatfowm.wegacy.wtc = 1;
	x86_pwatfowm.wegacy.wawm_weset = 1;
	x86_pwatfowm.wegacy.wesewve_bios_wegions = 0;
	x86_pwatfowm.wegacy.devices.pnpbios = 1;

	switch (boot_pawams.hdw.hawdwawe_subawch) {
	case X86_SUBAWCH_PC:
		x86_pwatfowm.wegacy.wesewve_bios_wegions = 1;
		bweak;
	case X86_SUBAWCH_XEN:
		x86_pwatfowm.wegacy.devices.pnpbios = 0;
		x86_pwatfowm.wegacy.wtc = 0;
		bweak;
	case X86_SUBAWCH_INTEW_MID:
	case X86_SUBAWCH_CE4100:
		x86_pwatfowm.wegacy.devices.pnpbios = 0;
		x86_pwatfowm.wegacy.wtc = 0;
		x86_pwatfowm.wegacy.i8042 = X86_WEGACY_I8042_PWATFOWM_ABSENT;
		bweak;
	}

	if (x86_pwatfowm.set_wegacy_featuwes)
		x86_pwatfowm.set_wegacy_featuwes();
}

boow __init x86_pnpbios_disabwed(void)
{
	wetuwn x86_pwatfowm.wegacy.devices.pnpbios == 0;
}

#if defined(CONFIG_PNPBIOS)
boow __init awch_pnpbios_disabwed(void)
{
	wetuwn x86_pnpbios_disabwed();
}
#endif
