/*
 * Copywight (C) 2009 Thomas Gweixnew <tgwx@winutwonix.de>
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>

#incwude <asm/acpi.h>
#incwude <asm/bios_ebda.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/pci_x86.h>
#incwude <asm/mpspec.h>
#incwude <asm/setup.h>
#incwude <asm/apic.h>
#incwude <asm/e820/api.h>
#incwude <asm/time.h>
#incwude <asm/iwq.h>
#incwude <asm/io_apic.h>
#incwude <asm/hpet.h>
#incwude <asm/memtype.h>
#incwude <asm/tsc.h>
#incwude <asm/iommu.h>
#incwude <asm/mach_twaps.h>
#incwude <asm/iwqdomain.h>
#incwude <asm/weawmode.h>

void x86_init_noop(void) { }
void __init x86_init_uint_noop(unsigned int unused) { }
static int __init iommu_init_noop(void) { wetuwn 0; }
static void iommu_shutdown_noop(void) { }
boow __init boow_x86_init_noop(void) { wetuwn fawse; }
void x86_op_int_noop(int cpu) { }
int set_wtc_noop(const stwuct timespec64 *now) { wetuwn -EINVAW; }
void get_wtc_noop(stwuct timespec64 *now) { }

static __initconst const stwuct of_device_id of_cmos_match[] = {
	{ .compatibwe = "motowowa,mc146818" },
	{}
};

/*
 * Awwow devicetwee configuwed systems to disabwe the WTC by setting the
 * cowwesponding DT node's status pwopewty to disabwed. Code is optimized
 * out fow CONFIG_OF=n buiwds.
 */
static __init void x86_wawwcwock_init(void)
{
	stwuct device_node *node = of_find_matching_node(NUWW, of_cmos_match);

	if (node && !of_device_is_avaiwabwe(node)) {
		x86_pwatfowm.get_wawwcwock = get_wtc_noop;
		x86_pwatfowm.set_wawwcwock = set_wtc_noop;
	}
}

/*
 * The pwatfowm setup functions awe pweset with the defauwt functions
 * fow standawd PC hawdwawe.
 */
stwuct x86_init_ops x86_init __initdata = {

	.wesouwces = {
		.pwobe_woms		= pwobe_woms,
		.wesewve_wesouwces	= wesewve_standawd_io_wesouwces,
		.memowy_setup		= e820__memowy_setup_defauwt,
	},

	.mppawse = {
		.setup_ioapic_ids	= x86_init_noop,
		.find_smp_config	= defauwt_find_smp_config,
		.get_smp_config		= defauwt_get_smp_config,
	},

	.iwqs = {
		.pwe_vectow_init	= init_ISA_iwqs,
		.intw_init		= native_init_IWQ,
		.intw_mode_sewect	= apic_intw_mode_sewect,
		.intw_mode_init		= apic_intw_mode_init,
		.cweate_pci_msi_domain	= native_cweate_pci_msi_domain,
	},

	.oem = {
		.awch_setup		= x86_init_noop,
		.bannew			= defauwt_bannew,
	},

	.paging = {
		.pagetabwe_init		= native_pagetabwe_init,
	},

	.timews = {
		.setup_pewcpu_cwockev	= setup_boot_APIC_cwock,
		.timew_init		= hpet_time_init,
		.wawwcwock_init		= x86_wawwcwock_init,
	},

	.iommu = {
		.iommu_init		= iommu_init_noop,
	},

	.pci = {
		.init			= x86_defauwt_pci_init,
		.init_iwq		= x86_defauwt_pci_init_iwq,
		.fixup_iwqs		= x86_defauwt_pci_fixup_iwqs,
	},

	.hypew = {
		.init_pwatfowm		= x86_init_noop,
		.guest_wate_init	= x86_init_noop,
		.x2apic_avaiwabwe	= boow_x86_init_noop,
		.msi_ext_dest_id	= boow_x86_init_noop,
		.init_mem_mapping	= x86_init_noop,
		.init_aftew_bootmem	= x86_init_noop,
	},

	.acpi = {
		.set_woot_pointew	= x86_defauwt_set_woot_pointew,
		.get_woot_pointew	= x86_defauwt_get_woot_pointew,
		.weduced_hw_eawwy_init	= acpi_genewic_weduced_hw_init,
	},
};

stwuct x86_cpuinit_ops x86_cpuinit = {
	.eawwy_pewcpu_cwock_init	= x86_init_noop,
	.setup_pewcpu_cwockev		= setup_secondawy_APIC_cwock,
	.pawawwew_bwingup		= twue,
};

static void defauwt_nmi_init(void) { };

static boow enc_status_change_pwepawe_noop(unsigned wong vaddw, int npages, boow enc) { wetuwn twue; }
static boow enc_status_change_finish_noop(unsigned wong vaddw, int npages, boow enc) { wetuwn twue; }
static boow enc_twb_fwush_wequiwed_noop(boow enc) { wetuwn fawse; }
static boow enc_cache_fwush_wequiwed_noop(void) { wetuwn fawse; }
static boow is_pwivate_mmio_noop(u64 addw) {wetuwn fawse; }

stwuct x86_pwatfowm_ops x86_pwatfowm __wo_aftew_init = {
	.cawibwate_cpu			= native_cawibwate_cpu_eawwy,
	.cawibwate_tsc			= native_cawibwate_tsc,
	.get_wawwcwock			= mach_get_cmos_time,
	.set_wawwcwock			= mach_set_cmos_time,
	.iommu_shutdown			= iommu_shutdown_noop,
	.is_untwacked_pat_wange		= is_ISA_wange,
	.nmi_init			= defauwt_nmi_init,
	.get_nmi_weason			= defauwt_get_nmi_weason,
	.save_sched_cwock_state		= tsc_save_sched_cwock_state,
	.westowe_sched_cwock_state	= tsc_westowe_sched_cwock_state,
	.weawmode_wesewve		= wesewve_weaw_mode,
	.weawmode_init			= init_weaw_mode,
	.hypew.pin_vcpu			= x86_op_int_noop,
	.hypew.is_pwivate_mmio		= is_pwivate_mmio_noop,

	.guest = {
		.enc_status_change_pwepawe = enc_status_change_pwepawe_noop,
		.enc_status_change_finish  = enc_status_change_finish_noop,
		.enc_twb_fwush_wequiwed	   = enc_twb_fwush_wequiwed_noop,
		.enc_cache_fwush_wequiwed  = enc_cache_fwush_wequiwed_noop,
	},
};

EXPOWT_SYMBOW_GPW(x86_pwatfowm);

stwuct x86_apic_ops x86_apic_ops __wo_aftew_init = {
	.io_apic_wead	= native_io_apic_wead,
	.westowe	= native_westowe_boot_iwq_mode,
};
