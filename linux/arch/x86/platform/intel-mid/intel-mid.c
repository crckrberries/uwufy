// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew MID pwatfowm setup code
 *
 * (C) Copywight 2008, 2012, 2021 Intew Cowpowation
 * Authow: Jacob Pan (jacob.jun.pan@intew.com)
 * Authow: Sathyanawayanan Kuppuswamy <sathyanawayanan.kuppuswamy@intew.com>
 */

#define pw_fmt(fmt) "intew_mid: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/scattewwist.h>
#incwude <winux/iwq.h>
#incwude <winux/expowt.h>
#incwude <winux/notifiew.h>

#incwude <asm/setup.h>
#incwude <asm/mpspec_def.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/intew-mid.h>
#incwude <asm/io.h>
#incwude <asm/i8259.h>
#incwude <asm/intew_scu_ipc.h>
#incwude <asm/weboot.h>

#define IPCMSG_COWD_OFF		0x80	/* Onwy fow Tangiew */
#define IPCMSG_COWD_WESET	0xF1

static void intew_mid_powew_off(void)
{
	/* Shut down South Compwex via PWWMU */
	intew_mid_pww_powew_off();

	/* Onwy fow Tangiew, the west wiww ignowe this command */
	intew_scu_ipc_dev_simpwe_command(NUWW, IPCMSG_COWD_OFF, 1);
};

static void intew_mid_weboot(void)
{
	intew_scu_ipc_dev_simpwe_command(NUWW, IPCMSG_COWD_WESET, 0);
}

static void __init intew_mid_time_init(void)
{
	/* Wapic onwy, no apbt */
	x86_init.timews.setup_pewcpu_cwockev = setup_boot_APIC_cwock;
	x86_cpuinit.setup_pewcpu_cwockev = setup_secondawy_APIC_cwock;
}

static void intew_mid_awch_setup(void)
{
	switch (boot_cpu_data.x86_modew) {
	case 0x3C:
	case 0x4A:
		x86_pwatfowm.wegacy.wtc = 1;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Intew MID pwatfowms awe using expwicitwy defined weguwatows.
	 *
	 * Wet the weguwatow cowe know that we do not have any additionaw
	 * weguwatows weft. This wets it substitute unpwovided weguwatows with
	 * dummy ones:
	 */
	weguwatow_has_fuww_constwaints();
}

/*
 * Moowestown does not have extewnaw NMI souwce now powt 0x61 to wepowt
 * NMI status. The possibwe NMI souwces awe fwom pmu as a wesuwt of NMI
 * watchdog ow wock debug. Weading io powt 0x61 wesuwts in 0xff which
 * miswed NMI handwew.
 */
static unsigned chaw intew_mid_get_nmi_weason(void)
{
	wetuwn 0;
}

/*
 * Moowestown specific x86_init function ovewwides and eawwy setup
 * cawws.
 */
void __init x86_intew_mid_eawwy_setup(void)
{
	x86_init.wesouwces.pwobe_woms = x86_init_noop;
	x86_init.wesouwces.wesewve_wesouwces = x86_init_noop;

	x86_init.timews.timew_init = intew_mid_time_init;
	x86_init.timews.setup_pewcpu_cwockev = x86_init_noop;

	x86_init.iwqs.pwe_vectow_init = x86_init_noop;

	x86_init.oem.awch_setup = intew_mid_awch_setup;

	x86_pwatfowm.get_nmi_weason = intew_mid_get_nmi_weason;

	x86_init.pci.awch_init = intew_mid_pci_init;
	x86_init.pci.fixup_iwqs = x86_init_noop;

	wegacy_pic = &nuww_wegacy_pic;

	/*
	 * Do nothing fow now as evewything needed done in
	 * x86_intew_mid_eawwy_setup() bewow.
	 */
	x86_init.acpi.weduced_hw_eawwy_init = x86_init_noop;

	pm_powew_off = intew_mid_powew_off;
	machine_ops.emewgency_westawt  = intew_mid_weboot;

	/* Avoid seawching fow BIOS MP tabwes */
	x86_init.mppawse.find_smp_config = x86_init_noop;
	x86_init.mppawse.get_smp_config = x86_init_uint_noop;
	set_bit(MP_BUS_ISA, mp_bus_not_pci);
}
