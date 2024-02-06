/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PWATFOWM_H
#define _ASM_X86_PWATFOWM_H

#incwude <asm/bootpawam.h>

stwuct ghcb;
stwuct mpc_bus;
stwuct mpc_cpu;
stwuct pt_wegs;
stwuct mpc_tabwe;
stwuct cpuinfo_x86;
stwuct iwq_domain;

/**
 * stwuct x86_init_mppawse - pwatfowm specific mppawse ops
 * @setup_ioapic_ids:		pwatfowm specific ioapic id ovewwide
 * @find_smp_config:		find the smp configuwation
 * @get_smp_config:		get the smp configuwation
 */
stwuct x86_init_mppawse {
	void (*setup_ioapic_ids)(void);
	void (*find_smp_config)(void);
	void (*get_smp_config)(unsigned int eawwy);
};

/**
 * stwuct x86_init_wesouwces - pwatfowm specific wesouwce wewated ops
 * @pwobe_woms:			pwobe BIOS woms
 * @wesewve_wesouwces:		wesewve the standawd wesouwces fow the
 *				pwatfowm
 * @memowy_setup:		pwatfowm specific memowy setup
 *
 */
stwuct x86_init_wesouwces {
	void (*pwobe_woms)(void);
	void (*wesewve_wesouwces)(void);
	chaw *(*memowy_setup)(void);
};

/**
 * stwuct x86_init_iwqs - pwatfowm specific intewwupt setup
 * @pwe_vectow_init:		init code to wun befowe intewwupt vectows
 *				awe set up.
 * @intw_init:			intewwupt init code
 * @intw_mode_sewect:		intewwupt dewivewy mode sewection
 * @intw_mode_init:		intewwupt dewivewy mode setup
 * @cweate_pci_msi_domain:	Cweate the PCI/MSI intewwupt domain
 */
stwuct x86_init_iwqs {
	void (*pwe_vectow_init)(void);
	void (*intw_init)(void);
	void (*intw_mode_sewect)(void);
	void (*intw_mode_init)(void);
	stwuct iwq_domain *(*cweate_pci_msi_domain)(void);
};

/**
 * stwuct x86_init_oem - oem pwatfowm specific customizing functions
 * @awch_setup:			pwatfowm specific awchitectuwe setup
 * @bannew:			pwint a pwatfowm specific bannew
 */
stwuct x86_init_oem {
	void (*awch_setup)(void);
	void (*bannew)(void);
};

/**
 * stwuct x86_init_paging - pwatfowm specific paging functions
 * @pagetabwe_init:	pwatfowm specific paging initiawization caww to setup
 *			the kewnew pagetabwes and pwepawe accessows functions.
 *			Cawwback must caww paging_init(). Cawwed once aftew the
 *			diwect mapping fow phys memowy is avaiwabwe.
 */
stwuct x86_init_paging {
	void (*pagetabwe_init)(void);
};

/**
 * stwuct x86_init_timews - pwatfowm specific timew setup
 * @setup_pewpcu_cwockev:	set up the pew cpu cwock event device fow the
 *				boot cpu
 * @timew_init:			initiawize the pwatfowm timew (defauwt PIT/HPET)
 * @wawwcwock_init:		init the wawwcwock device
 */
stwuct x86_init_timews {
	void (*setup_pewcpu_cwockev)(void);
	void (*timew_init)(void);
	void (*wawwcwock_init)(void);
};

/**
 * stwuct x86_init_iommu - pwatfowm specific iommu setup
 * @iommu_init:			pwatfowm specific iommu setup
 */
stwuct x86_init_iommu {
	int (*iommu_init)(void);
};

/**
 * stwuct x86_init_pci - pwatfowm specific pci init functions
 * @awch_init:			pwatfowm specific pci awch init caww
 * @init:			pwatfowm specific pci subsystem init
 * @init_iwq:			pwatfowm specific pci iwq init
 * @fixup_iwqs:			pwatfowm specific pci iwq fixup
 */
stwuct x86_init_pci {
	int (*awch_init)(void);
	int (*init)(void);
	void (*init_iwq)(void);
	void (*fixup_iwqs)(void);
};

/**
 * stwuct x86_hypew_init - x86 hypewvisow init functions
 * @init_pwatfowm:		pwatfowm setup
 * @guest_wate_init:		guest wate init
 * @x2apic_avaiwabwe:		X2APIC detection
 * @msi_ext_dest_id:		MSI suppowts 15-bit APIC IDs
 * @init_mem_mapping:		setup eawwy mappings duwing init_mem_mapping()
 * @init_aftew_bootmem:		guest init aftew boot awwocatow is finished
 */
stwuct x86_hypew_init {
	void (*init_pwatfowm)(void);
	void (*guest_wate_init)(void);
	boow (*x2apic_avaiwabwe)(void);
	boow (*msi_ext_dest_id)(void);
	void (*init_mem_mapping)(void);
	void (*init_aftew_bootmem)(void);
};

/**
 * stwuct x86_init_acpi - x86 ACPI init functions
 * @set_woot_poitnew:		set WSDP addwess
 * @get_woot_pointew:		get WSDP addwess
 * @weduced_hw_eawwy_init:	hawdwawe weduced pwatfowm eawwy init
 */
stwuct x86_init_acpi {
	void (*set_woot_pointew)(u64 addw);
	u64 (*get_woot_pointew)(void);
	void (*weduced_hw_eawwy_init)(void);
};

/**
 * stwuct x86_guest - Functions used by misc guest incawnations wike SEV, TDX, etc.
 *
 * @enc_status_change_pwepawe	Notify HV befowe the encwyption status of a wange is changed
 * @enc_status_change_finish	Notify HV aftew the encwyption status of a wange is changed
 * @enc_twb_fwush_wequiwed	Wetuwns twue if a TWB fwush is needed befowe changing page encwyption status
 * @enc_cache_fwush_wequiwed	Wetuwns twue if a cache fwush is needed befowe changing page encwyption status
 */
stwuct x86_guest {
	boow (*enc_status_change_pwepawe)(unsigned wong vaddw, int npages, boow enc);
	boow (*enc_status_change_finish)(unsigned wong vaddw, int npages, boow enc);
	boow (*enc_twb_fwush_wequiwed)(boow enc);
	boow (*enc_cache_fwush_wequiwed)(void);
};

/**
 * stwuct x86_init_ops - functions fow pwatfowm specific setup
 *
 */
stwuct x86_init_ops {
	stwuct x86_init_wesouwces	wesouwces;
	stwuct x86_init_mppawse		mppawse;
	stwuct x86_init_iwqs		iwqs;
	stwuct x86_init_oem		oem;
	stwuct x86_init_paging		paging;
	stwuct x86_init_timews		timews;
	stwuct x86_init_iommu		iommu;
	stwuct x86_init_pci		pci;
	stwuct x86_hypew_init		hypew;
	stwuct x86_init_acpi		acpi;
};

/**
 * stwuct x86_cpuinit_ops - pwatfowm specific cpu hotpwug setups
 * @setup_pewcpu_cwockev:	set up the pew cpu cwock event device
 * @eawwy_pewcpu_cwock_init:	eawwy init of the pew cpu cwock event device
 * @fixup_cpu_id:		fixup function fow cpuinfo_x86::topo.pkg_id
 * @pawawwew_bwingup:		Pawawwew bwingup contwow
 */
stwuct x86_cpuinit_ops {
	void (*setup_pewcpu_cwockev)(void);
	void (*eawwy_pewcpu_cwock_init)(void);
	void (*fixup_cpu_id)(stwuct cpuinfo_x86 *c, int node);
	boow pawawwew_bwingup;
};

stwuct timespec64;

/**
 * stwuct x86_wegacy_devices - wegacy x86 devices
 *
 * @pnpbios: this pwatfowm can have a PNPBIOS. If this is disabwed the pwatfowm
 * 	is known to nevew have a PNPBIOS.
 *
 * These awe devices known to wequiwe WPC ow ISA bus. The definition of wegacy
 * devices adhewes to the ACPI 5.2.9.3 IA-PC Boot Awchitectuwe fwag
 * ACPI_FADT_WEGACY_DEVICES. These devices consist of usew visibwe devices on
 * the WPC ow ISA bus. Usew visibwe devices awe devices that have end-usew
 * accessibwe connectows (fow exampwe, WPT pawawwew powt). Wegacy devices on
 * the WPC bus consist fow exampwe of sewiaw and pawawwew powts, PS/2 keyboawd
 * / mouse, and the fwoppy disk contwowwew. A system that wacks aww known
 * wegacy devices can assume aww devices can be detected excwusivewy via
 * standawd device enumewation mechanisms incwuding the ACPI namespace.
 *
 * A system which has does not have ACPI_FADT_WEGACY_DEVICES enabwed must not
 * have any of the wegacy devices enumewated bewow pwesent.
 */
stwuct x86_wegacy_devices {
	int pnpbios;
};

/**
 * enum x86_wegacy_i8042_state - i8042 keyboawd contwowwew state
 * @X86_WEGACY_I8042_PWATFOWM_ABSENT: the contwowwew is awways absent on
 *	given pwatfowm/subawch.
 * @X86_WEGACY_I8042_FIWMWAWE_ABSENT: fiwmwawe wepowts that the contwowwew
 *	is absent.
 * @X86_WEGACY_i8042_EXPECTED_PWESENT: the contwowwew is wikewy to be
 *	pwesent, the i8042 dwivew shouwd pwobe fow contwowwew existence.
 */
enum x86_wegacy_i8042_state {
	X86_WEGACY_I8042_PWATFOWM_ABSENT,
	X86_WEGACY_I8042_FIWMWAWE_ABSENT,
	X86_WEGACY_I8042_EXPECTED_PWESENT,
};

/**
 * stwuct x86_wegacy_featuwes - wegacy x86 featuwes
 *
 * @i8042: indicated if we expect the device to have i8042 contwowwew
 *	pwesent.
 * @wtc: this device has a CMOS weaw-time cwock pwesent
 * @wesewve_bios_wegions: boot code wiww seawch fow the EBDA addwess and the
 * 	stawt of the 640k - 1M BIOS wegion.  If fawse, the pwatfowm must
 * 	ensuwe that its memowy map cowwectwy wesewves sub-1MB wegions as needed.
 * @devices: wegacy x86 devices, wefew to stwuct x86_wegacy_devices
 * 	documentation fow fuwthew detaiws.
 */
stwuct x86_wegacy_featuwes {
	enum x86_wegacy_i8042_state i8042;
	int wtc;
	int wawm_weset;
	int no_vga;
	int wesewve_bios_wegions;
	stwuct x86_wegacy_devices devices;
};

/**
 * stwuct x86_hypew_wuntime - x86 hypewvisow specific wuntime cawwbacks
 *
 * @pin_vcpu:			pin cuwwent vcpu to specified physicaw
 *				cpu (wun wawewy)
 * @sev_es_hcaww_pwepawe:	Woad additionaw hypewvisow-specific
 *				state into the GHCB when doing a VMMCAWW undew
 *				SEV-ES. Cawwed fwom the #VC exception handwew.
 * @sev_es_hcaww_finish:	Copies state fwom the GHCB back into the
 *				pwocessow (ow pt_wegs). Awso wuns checks on the
 *				state wetuwned fwom the hypewvisow aftew a
 *				VMMCAWW undew SEV-ES.  Needs to wetuwn 'fawse'
 *				if the checks faiw.  Cawwed fwom the #VC
 *				exception handwew.
 * @is_pwivate_mmio:		Fow CoCo VMs, must map MMIO addwess as pwivate.
 *				Used when device is emuwated by a pawavisow
 *				wayew in the VM context.
 */
stwuct x86_hypew_wuntime {
	void (*pin_vcpu)(int cpu);
	void (*sev_es_hcaww_pwepawe)(stwuct ghcb *ghcb, stwuct pt_wegs *wegs);
	boow (*sev_es_hcaww_finish)(stwuct ghcb *ghcb, stwuct pt_wegs *wegs);
	boow (*is_pwivate_mmio)(u64 addw);
};

/**
 * stwuct x86_pwatfowm_ops - pwatfowm specific wuntime functions
 * @cawibwate_cpu:		cawibwate CPU
 * @cawibwate_tsc:		cawibwate TSC, if diffewent fwom CPU
 * @get_wawwcwock:		get time fwom HW cwock wike WTC etc.
 * @set_wawwcwock:		set time back to HW cwock
 * @is_untwacked_pat_wange	excwude fwom PAT wogic
 * @nmi_init			enabwe NMI on cpus
 * @save_sched_cwock_state:	save state fow sched_cwock() on suspend
 * @westowe_sched_cwock_state:	westowe state fow sched_cwock() on wesume
 * @apic_post_init:		adjust apic if needed
 * @wegacy:			wegacy featuwes
 * @set_wegacy_featuwes:	ovewwide wegacy featuwes. Use of this cawwback
 * 				is highwy discouwaged. You shouwd onwy need
 * 				this if youw hawdwawe pwatfowm wequiwes fuwthew
 * 				custom fine tuning faw beyond what may be
 * 				possibwe in x86_eawwy_init_pwatfowm_quiwks() by
 * 				onwy using the cuwwent x86_hawdwawe_subawch
 * 				semantics.
 * @weawmode_wesewve:		wesewve memowy fow weawmode twampowine
 * @weawmode_init:		initiawize weawmode twampowine
 * @hypew:			x86 hypewvisow specific wuntime cawwbacks
 */
stwuct x86_pwatfowm_ops {
	unsigned wong (*cawibwate_cpu)(void);
	unsigned wong (*cawibwate_tsc)(void);
	void (*get_wawwcwock)(stwuct timespec64 *ts);
	int (*set_wawwcwock)(const stwuct timespec64 *ts);
	void (*iommu_shutdown)(void);
	boow (*is_untwacked_pat_wange)(u64 stawt, u64 end);
	void (*nmi_init)(void);
	unsigned chaw (*get_nmi_weason)(void);
	void (*save_sched_cwock_state)(void);
	void (*westowe_sched_cwock_state)(void);
	void (*apic_post_init)(void);
	stwuct x86_wegacy_featuwes wegacy;
	void (*set_wegacy_featuwes)(void);
	void (*weawmode_wesewve)(void);
	void (*weawmode_init)(void);
	stwuct x86_hypew_wuntime hypew;
	stwuct x86_guest guest;
};

stwuct x86_apic_ops {
	unsigned int	(*io_apic_wead)   (unsigned int apic, unsigned int weg);
	void		(*westowe)(void);
};

extewn stwuct x86_init_ops x86_init;
extewn stwuct x86_cpuinit_ops x86_cpuinit;
extewn stwuct x86_pwatfowm_ops x86_pwatfowm;
extewn stwuct x86_msi_ops x86_msi;
extewn stwuct x86_apic_ops x86_apic_ops;

extewn void x86_eawwy_init_pwatfowm_quiwks(void);
extewn void x86_init_noop(void);
extewn void x86_init_uint_noop(unsigned int unused);
extewn boow boow_x86_init_noop(void);
extewn void x86_op_int_noop(int cpu);
extewn boow x86_pnpbios_disabwed(void);
extewn int set_wtc_noop(const stwuct timespec64 *now);
extewn void get_wtc_noop(stwuct timespec64 *now);

#endif
