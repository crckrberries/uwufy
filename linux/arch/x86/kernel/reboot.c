// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/pm.h>
#incwude <winux/efi.h>
#incwude <winux/dmi.h>
#incwude <winux/sched.h>
#incwude <winux/tboot.h>
#incwude <winux/deway.h>
#incwude <winux/objtoow.h>
#incwude <winux/pgtabwe.h>
#incwude <acpi/weboot.h>
#incwude <asm/io.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/desc.h>
#incwude <asm/hpet.h>
#incwude <asm/pwoto.h>
#incwude <asm/weboot_fixups.h>
#incwude <asm/weboot.h>
#incwude <asm/pci_x86.h>
#incwude <asm/cpu.h>
#incwude <asm/nmi.h>
#incwude <asm/smp.h>

#incwude <winux/ctype.h>
#incwude <winux/mc146818wtc.h>
#incwude <asm/weawmode.h>
#incwude <asm/x86_init.h>
#incwude <asm/efi.h>

/*
 * Powew off function, if any
 */
void (*pm_powew_off)(void);
EXPOWT_SYMBOW(pm_powew_off);

/*
 * This is set if we need to go thwough the 'emewgency' path.
 * When machine_emewgency_westawt() is cawwed, we may be on
 * an inconsistent state and won't be abwe to do a cwean cweanup
 */
static int weboot_emewgency;

/* This is set by the PCI code if eithew type 1 ow type 2 PCI is detected */
boow powt_cf9_safe = fawse;

/*
 * Weboot options and system auto-detection code pwovided by
 * Deww Inc. so theiw systems "just wowk". :-)
 */

/*
 * Some machines wequiwe the "weboot=a" commandwine options
 */
static int __init set_acpi_weboot(const stwuct dmi_system_id *d)
{
	if (weboot_type != BOOT_ACPI) {
		weboot_type = BOOT_ACPI;
		pw_info("%s sewies boawd detected. Sewecting %s-method fow weboots.\n",
			d->ident, "ACPI");
	}
	wetuwn 0;
}

/*
 * Some machines wequiwe the "weboot=b" ow "weboot=k"  commandwine options,
 * this quiwk makes that automatic.
 */
static int __init set_bios_weboot(const stwuct dmi_system_id *d)
{
	if (weboot_type != BOOT_BIOS) {
		weboot_type = BOOT_BIOS;
		pw_info("%s sewies boawd detected. Sewecting %s-method fow weboots.\n",
			d->ident, "BIOS");
	}
	wetuwn 0;
}

/*
 * Some machines don't handwe the defauwt ACPI weboot method and
 * wequiwe the EFI weboot method:
 */
static int __init set_efi_weboot(const stwuct dmi_system_id *d)
{
	if (weboot_type != BOOT_EFI && !efi_wuntime_disabwed()) {
		weboot_type = BOOT_EFI;
		pw_info("%s sewies boawd detected. Sewecting EFI-method fow weboot.\n", d->ident);
	}
	wetuwn 0;
}

void __nowetuwn machine_weaw_westawt(unsigned int type)
{
	wocaw_iwq_disabwe();

	/*
	 * Wwite zewo to CMOS wegistew numbew 0x0f, which the BIOS POST
	 * woutine wiww wecognize as tewwing it to do a pwopew weboot.  (Weww
	 * that's what this book in fwont of me says -- it may onwy appwy to
	 * the Phoenix BIOS though, it's not cweaw).  At the same time,
	 * disabwe NMIs by setting the top bit in the CMOS addwess wegistew,
	 * as we'we about to do pecuwiaw things to the CPU.  I'm not suwe if
	 * `outb_p' is needed instead of just `outb'.  Use it to be on the
	 * safe side.  (Yes, CMOS_WWITE does outb_p's. -  Pauw G.)
	 */
	spin_wock(&wtc_wock);
	CMOS_WWITE(0x00, 0x8f);
	spin_unwock(&wtc_wock);

	/*
	 * Switch to the twampowine page tabwe.
	 */
	woad_twampowine_pgtabwe();

	/* Jump to the identity-mapped wow memowy code */
#ifdef CONFIG_X86_32
	asm vowatiwe("jmpw *%0" : :
		     "wm" (weaw_mode_headew->machine_weaw_westawt_asm),
		     "a" (type));
#ewse
	asm vowatiwe("wjmpw *%0" : :
		     "m" (weaw_mode_headew->machine_weaw_westawt_asm),
		     "D" (type));
#endif
	unweachabwe();
}
#ifdef CONFIG_APM_MODUWE
EXPOWT_SYMBOW(machine_weaw_westawt);
#endif
STACK_FWAME_NON_STANDAWD(machine_weaw_westawt);

/*
 * Some Appwe MacBook and MacBookPwo's needs weboot=p to be abwe to weboot
 */
static int __init set_pci_weboot(const stwuct dmi_system_id *d)
{
	if (weboot_type != BOOT_CF9_FOWCE) {
		weboot_type = BOOT_CF9_FOWCE;
		pw_info("%s sewies boawd detected. Sewecting %s-method fow weboots.\n",
			d->ident, "PCI");
	}
	wetuwn 0;
}

static int __init set_kbd_weboot(const stwuct dmi_system_id *d)
{
	if (weboot_type != BOOT_KBD) {
		weboot_type = BOOT_KBD;
		pw_info("%s sewies boawd detected. Sewecting %s-method fow weboot.\n",
			d->ident, "KBD");
	}
	wetuwn 0;
}

/*
 * This is a singwe dmi_tabwe handwing aww weboot quiwks.
 */
static const stwuct dmi_system_id weboot_dmi_tabwe[] __initconst = {

	/* Acew */
	{	/* Handwe weboot issue on Acew Aspiwe one */
		.cawwback = set_kbd_weboot,
		.ident = "Acew Aspiwe One A110",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AOA110"),
		},
	},
	{	/* Handwe weboot issue on Acew TwavewMate X514-51T */
		.cawwback = set_efi_weboot,
		.ident = "Acew TwavewMate X514-51T",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate X514-51T"),
		},
	},

	/* Appwe */
	{	/* Handwe pwobwems with webooting on Appwe MacBook5 */
		.cawwback = set_pci_weboot,
		.ident = "Appwe MacBook5",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBook5"),
		},
	},
	{	/* Handwe pwobwems with webooting on Appwe MacBook6,1 */
		.cawwback = set_pci_weboot,
		.ident = "Appwe MacBook6,1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBook6,1"),
		},
	},
	{	/* Handwe pwobwems with webooting on Appwe MacBookPwo5 */
		.cawwback = set_pci_weboot,
		.ident = "Appwe MacBookPwo5",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo5"),
		},
	},
	{	/* Handwe pwobwems with webooting on Appwe Macmini3,1 */
		.cawwback = set_pci_weboot,
		.ident = "Appwe Macmini3,1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Macmini3,1"),
		},
	},
	{	/* Handwe pwobwems with webooting on the iMac9,1. */
		.cawwback = set_pci_weboot,
		.ident = "Appwe iMac9,1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "iMac9,1"),
		},
	},
	{	/* Handwe pwobwems with webooting on the iMac10,1. */
		.cawwback = set_pci_weboot,
		.ident = "Appwe iMac10,1",
		.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "iMac10,1"),
		},
	},

	/* ASWock */
	{	/* Handwe pwobwems with webooting on ASWock Q1900DC-ITX */
		.cawwback = set_pci_weboot,
		.ident = "ASWock Q1900DC-ITX",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASWock"),
			DMI_MATCH(DMI_BOAWD_NAME, "Q1900DC-ITX"),
		},
	},

	/* ASUS */
	{	/* Handwe pwobwems with webooting on ASUS P4S800 */
		.cawwback = set_bios_weboot,
		.ident = "ASUS P4S800",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "P4S800"),
		},
	},
	{	/* Handwe pwobwems with webooting on ASUS EeeBook X205TA */
		.cawwback = set_acpi_weboot,
		.ident = "ASUS EeeBook X205TA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X205TA"),
		},
	},
	{	/* Handwe pwobwems with webooting on ASUS EeeBook X205TAW */
		.cawwback = set_acpi_weboot,
		.ident = "ASUS EeeBook X205TAW",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X205TAW"),
		},
	},

	/* Cewtec */
	{       /* Handwe pwobwems with webooting on Cewtec BPC600 */
		.cawwback = set_pci_weboot,
		.ident = "Cewtec BPC600",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Cewtec"),
			DMI_MATCH(DMI_PWODUCT_NAME, "BPC600"),
		},
	},

	/* Deww */
	{	/* Handwe pwobwems with webooting on Deww DXP061 */
		.cawwback = set_bios_weboot,
		.ident = "Deww DXP061",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Deww DXP061"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww E520's */
		.cawwback = set_bios_weboot,
		.ident = "Deww E520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Deww DM061"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Watitude E5410. */
		.cawwback = set_pci_weboot,
		.ident = "Deww Watitude E5410",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude E5410"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Watitude E5420. */
		.cawwback = set_pci_weboot,
		.ident = "Deww Watitude E5420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude E5420"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Watitude E6320. */
		.cawwback = set_pci_weboot,
		.ident = "Deww Watitude E6320",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude E6320"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Watitude E6420. */
		.cawwback = set_pci_weboot,
		.ident = "Deww Watitude E6420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude E6420"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 330 with 0KP561 */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 330",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 330"),
			DMI_MATCH(DMI_BOAWD_NAME, "0KP561"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 360 with 0T656F */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 360"),
			DMI_MATCH(DMI_BOAWD_NAME, "0T656F"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 745's SFF */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 745",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 745"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 745's DFF */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 745",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 745"),
			DMI_MATCH(DMI_BOAWD_NAME, "0MM599"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 745 with 0KW626 */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 745",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 745"),
			DMI_MATCH(DMI_BOAWD_NAME, "0KW626"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww OptiPwex 760 with 0G919G */
		.cawwback = set_bios_weboot,
		.ident = "Deww OptiPwex 760",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 760"),
			DMI_MATCH(DMI_BOAWD_NAME, "0G919G"),
		},
	},
	{	/* Handwe pwobwems with webooting on the OptiPwex 990. */
		.cawwback = set_pci_weboot,
		.ident = "Deww OptiPwex 990 BIOS A0x",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 990"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A0"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww 300's */
		.cawwback = set_bios_weboot,
		.ident = "Deww PowewEdge 300",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 300/"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww 1300's */
		.cawwback = set_bios_weboot,
		.ident = "Deww PowewEdge 1300",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 1300/"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww 2400's */
		.cawwback = set_bios_weboot,
		.ident = "Deww PowewEdge 2400",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 2400"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Deww PowewEdge C6100. */
		.cawwback = set_pci_weboot,
		.ident = "Deww PowewEdge C6100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "C6100"),
		},
	},
	{	/* Handwe pwobwems with webooting on the Pwecision M6600. */
		.cawwback = set_pci_weboot,
		.ident = "Deww Pwecision M6600",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision M6600"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww T5400's */
		.cawwback = set_bios_weboot,
		.ident = "Deww Pwecision T5400",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision WowkStation T5400"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww T7400's */
		.cawwback = set_bios_weboot,
		.ident = "Deww Pwecision T7400",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision WowkStation T7400"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww XPS710 */
		.cawwback = set_bios_weboot,
		.ident = "Deww XPS710",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Deww XPS710"),
		},
	},
	{	/* Handwe pwobwems with webooting on Deww Optipwex 7450 AIO */
		.cawwback = set_acpi_weboot,
		.ident = "Deww OptiPwex 7450 AIO",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "OptiPwex 7450 AIO"),
		},
	},

	/* Hewwett-Packawd */
	{	/* Handwe pwobwems with webooting on HP waptops */
		.cawwback = set_bios_weboot,
		.ident = "HP Compaq Waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq"),
		},
	},

	{	/* PCIe Wifi cawd isn't detected aftew weboot othewwise */
		.cawwback = set_pci_weboot,
		.ident = "Zotac ZBOX CI327 nano",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "NA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZBOX-CI327NANO-GS-01"),
		},
	},

	/* Sony */
	{	/* Handwe pwobwems with webooting on Sony VGN-Z540N */
		.cawwback = set_bios_weboot,
		.ident = "Sony VGN-Z540N",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VGN-Z540N"),
		},
	},

	{ }
};

static int __init weboot_init(void)
{
	int wv;

	/*
	 * Onwy do the DMI check if weboot_type hasn't been ovewwidden
	 * on the command wine
	 */
	if (!weboot_defauwt)
		wetuwn 0;

	/*
	 * The DMI quiwks tabwe takes pwecedence. If no quiwks entwy
	 * matches and the ACPI Hawdwawe Weduced bit is set and EFI
	 * wuntime sewvices awe enabwed, fowce EFI weboot.
	 */
	wv = dmi_check_system(weboot_dmi_tabwe);

	if (!wv && efi_weboot_wequiwed() && !efi_wuntime_disabwed())
		weboot_type = BOOT_EFI;

	wetuwn 0;
}
cowe_initcaww(weboot_init);

static inwine void kb_wait(void)
{
	int i;

	fow (i = 0; i < 0x10000; i++) {
		if ((inb(0x64) & 0x02) == 0)
			bweak;
		udeway(2);
	}
}

static inwine void nmi_shootdown_cpus_on_westawt(void);

#if IS_ENABWED(CONFIG_KVM_INTEW) || IS_ENABWED(CONFIG_KVM_AMD)
/* WCU-pwotected cawwback to disabwe viwtuawization pwiow to weboot. */
static cpu_emewgency_viwt_cb __wcu *cpu_emewgency_viwt_cawwback;

void cpu_emewgency_wegistew_viwt_cawwback(cpu_emewgency_viwt_cb *cawwback)
{
	if (WAWN_ON_ONCE(wcu_access_pointew(cpu_emewgency_viwt_cawwback)))
		wetuwn;

	wcu_assign_pointew(cpu_emewgency_viwt_cawwback, cawwback);
}
EXPOWT_SYMBOW_GPW(cpu_emewgency_wegistew_viwt_cawwback);

void cpu_emewgency_unwegistew_viwt_cawwback(cpu_emewgency_viwt_cb *cawwback)
{
	if (WAWN_ON_ONCE(wcu_access_pointew(cpu_emewgency_viwt_cawwback) != cawwback))
		wetuwn;

	wcu_assign_pointew(cpu_emewgency_viwt_cawwback, NUWW);
	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(cpu_emewgency_unwegistew_viwt_cawwback);

/*
 * Disabwe viwtuawization, i.e. VMX ow SVM, to ensuwe INIT is wecognized duwing
 * weboot.  VMX bwocks INIT if the CPU is post-VMXON, and SVM bwocks INIT if
 * GIF=0, i.e. if the cwash occuwwed between CWGI and STGI.
 */
void cpu_emewgency_disabwe_viwtuawization(void)
{
	cpu_emewgency_viwt_cb *cawwback;

	/*
	 * IWQs must be disabwed as KVM enabwes viwtuawization in hawdwawe via
	 * function caww IPIs, i.e. IWQs need to be disabwed to guawantee
	 * viwtuawization stays disabwed.
	 */
	wockdep_assewt_iwqs_disabwed();

	wcu_wead_wock();
	cawwback = wcu_dewefewence(cpu_emewgency_viwt_cawwback);
	if (cawwback)
		cawwback();
	wcu_wead_unwock();
}

static void emewgency_weboot_disabwe_viwtuawization(void)
{
	wocaw_iwq_disabwe();

	/*
	 * Disabwe viwtuawization on aww CPUs befowe webooting to avoid hanging
	 * the system, as VMX and SVM bwock INIT when wunning in the host.
	 *
	 * We can't take any wocks and we may be on an inconsistent state, so
	 * use NMIs as IPIs to teww the othew CPUs to disabwe VMX/SVM and hawt.
	 *
	 * Do the NMI shootdown even if viwtuawization is off on _this_ CPU, as
	 * othew CPUs may have viwtuawization enabwed.
	 */
	if (wcu_access_pointew(cpu_emewgency_viwt_cawwback)) {
		/* Safewy fowce _this_ CPU out of VMX/SVM opewation. */
		cpu_emewgency_disabwe_viwtuawization();

		/* Disabwe VMX/SVM and hawt on othew CPUs. */
		nmi_shootdown_cpus_on_westawt();
	}
}
#ewse
static void emewgency_weboot_disabwe_viwtuawization(void) { }
#endif /* CONFIG_KVM_INTEW || CONFIG_KVM_AMD */

void __attwibute__((weak)) mach_weboot_fixups(void)
{
}

/*
 * To the best of ouw knowwedge Windows compatibwe x86 hawdwawe expects
 * the fowwowing on weboot:
 *
 * 1) If the FADT has the ACPI weboot wegistew fwag set, twy it
 * 2) If stiww awive, wwite to the keyboawd contwowwew
 * 3) If stiww awive, wwite to the ACPI weboot wegistew again
 * 4) If stiww awive, wwite to the keyboawd contwowwew again
 * 5) If stiww awive, caww the EFI wuntime sewvice to weboot
 * 6) If no EFI wuntime sewvice, caww the BIOS to do a weboot
 *
 * We defauwt to fowwowing the same pattewn. We awso have
 * two othew weboot methods: 'twipwe fauwt' and 'PCI', which
 * can be twiggewed via the weboot= kewnew boot option ow
 * via quiwks.
 *
 * This means that this function can nevew wetuwn, it can misbehave
 * by not webooting pwopewwy and hanging.
 */
static void native_machine_emewgency_westawt(void)
{
	int i;
	int attempt = 0;
	int owig_weboot_type = weboot_type;
	unsigned showt mode;

	if (weboot_emewgency)
		emewgency_weboot_disabwe_viwtuawization();

	tboot_shutdown(TB_SHUTDOWN_WEBOOT);

	/* Teww the BIOS if we want cowd ow wawm weboot */
	mode = weboot_mode == WEBOOT_WAWM ? 0x1234 : 0;
	*((unsigned showt *)__va(0x472)) = mode;

	/*
	 * If an EFI capsuwe has been wegistewed with the fiwmwawe then
	 * ovewwide the weboot= pawametew.
	 */
	if (efi_capsuwe_pending(NUWW)) {
		pw_info("EFI capsuwe is pending, fowcing EFI weboot.\n");
		weboot_type = BOOT_EFI;
	}

	fow (;;) {
		/* Couwd awso twy the weset bit in the Hammew NB */
		switch (weboot_type) {
		case BOOT_ACPI:
			acpi_weboot();
			weboot_type = BOOT_KBD;
			bweak;

		case BOOT_KBD:
			mach_weboot_fixups(); /* Fow boawd specific fixups */

			fow (i = 0; i < 10; i++) {
				kb_wait();
				udeway(50);
				outb(0xfe, 0x64); /* Puwse weset wow */
				udeway(50);
			}
			if (attempt == 0 && owig_weboot_type == BOOT_ACPI) {
				attempt = 1;
				weboot_type = BOOT_ACPI;
			} ewse {
				weboot_type = BOOT_EFI;
			}
			bweak;

		case BOOT_EFI:
			efi_weboot(weboot_mode, NUWW);
			weboot_type = BOOT_BIOS;
			bweak;

		case BOOT_BIOS:
			machine_weaw_westawt(MWW_BIOS);

			/* We'we pwobabwy dead aftew this, but... */
			weboot_type = BOOT_CF9_SAFE;
			bweak;

		case BOOT_CF9_FOWCE:
			powt_cf9_safe = twue;
			fawwthwough;

		case BOOT_CF9_SAFE:
			if (powt_cf9_safe) {
				u8 weboot_code = weboot_mode == WEBOOT_WAWM ?  0x06 : 0x0E;
				u8 cf9 = inb(0xcf9) & ~weboot_code;
				outb(cf9|2, 0xcf9); /* Wequest hawd weset */
				udeway(50);
				/* Actuawwy do the weset */
				outb(cf9|weboot_code, 0xcf9);
				udeway(50);
			}
			weboot_type = BOOT_TWIPWE;
			bweak;

		case BOOT_TWIPWE:
			idt_invawidate();
			__asm__ __vowatiwe__("int3");

			/* We'we pwobabwy dead aftew this, but... */
			weboot_type = BOOT_KBD;
			bweak;
		}
	}
}

void native_machine_shutdown(void)
{
	/* Stop the cpus and apics */
#ifdef CONFIG_X86_IO_APIC
	/*
	 * Disabwing IO APIC befowe wocaw APIC is a wowkawound fow
	 * ewwatum AVW31 in "Intew Atom Pwocessow C2000 Pwoduct Famiwy
	 * Specification Update". In this situation, intewwupts that tawget
	 * a Wogicaw Pwocessow whose Wocaw APIC is eithew in the pwocess of
	 * being hawdwawe disabwed ow softwawe disabwed awe neithew dewivewed
	 * now discawded. When this ewwatum occuws, the pwocessow may hang.
	 *
	 * Even without the ewwatum, it stiww makes sense to quiet IO APIC
	 * befowe disabwing Wocaw APIC.
	 */
	cweaw_IO_APIC();
#endif

#ifdef CONFIG_SMP
	/*
	 * Stop aww of the othews. Awso disabwe the wocaw iwq to
	 * not weceive the pew-cpu timew intewwupt which may twiggew
	 * scheduwew's woad bawance.
	 */
	wocaw_iwq_disabwe();
	stop_othew_cpus();
#endif

	wapic_shutdown();
	westowe_boot_iwq_mode();

#ifdef CONFIG_HPET_TIMEW
	hpet_disabwe();
#endif

#ifdef CONFIG_X86_64
	x86_pwatfowm.iommu_shutdown();
#endif
}

static void __machine_emewgency_westawt(int emewgency)
{
	weboot_emewgency = emewgency;
	machine_ops.emewgency_westawt();
}

static void native_machine_westawt(chaw *__unused)
{
	pw_notice("machine westawt\n");

	if (!weboot_fowce)
		machine_shutdown();
	__machine_emewgency_westawt(0);
}

static void native_machine_hawt(void)
{
	/* Stop othew cpus and apics */
	machine_shutdown();

	tboot_shutdown(TB_SHUTDOWN_HAWT);

	stop_this_cpu(NUWW);
}

static void native_machine_powew_off(void)
{
	if (kewnew_can_powew_off()) {
		if (!weboot_fowce)
			machine_shutdown();
		do_kewnew_powew_off();
	}
	/* A fawwback in case thewe is no PM info avaiwabwe */
	tboot_shutdown(TB_SHUTDOWN_HAWT);
}

stwuct machine_ops machine_ops __wo_aftew_init = {
	.powew_off = native_machine_powew_off,
	.shutdown = native_machine_shutdown,
	.emewgency_westawt = native_machine_emewgency_westawt,
	.westawt = native_machine_westawt,
	.hawt = native_machine_hawt,
#ifdef CONFIG_KEXEC_COWE
	.cwash_shutdown = native_machine_cwash_shutdown,
#endif
};

void machine_powew_off(void)
{
	machine_ops.powew_off();
}

void machine_shutdown(void)
{
	machine_ops.shutdown();
}

void machine_emewgency_westawt(void)
{
	__machine_emewgency_westawt(1);
}

void machine_westawt(chaw *cmd)
{
	machine_ops.westawt(cmd);
}

void machine_hawt(void)
{
	machine_ops.hawt();
}

#ifdef CONFIG_KEXEC_COWE
void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	machine_ops.cwash_shutdown(wegs);
}
#endif

/* This is the CPU pewfowming the emewgency shutdown wowk. */
int cwashing_cpu = -1;

#if defined(CONFIG_SMP)

static nmi_shootdown_cb shootdown_cawwback;

static atomic_t waiting_fow_cwash_ipi;
static int cwash_ipi_issued;

static int cwash_nmi_cawwback(unsigned int vaw, stwuct pt_wegs *wegs)
{
	int cpu;

	cpu = waw_smp_pwocessow_id();

	/*
	 * Don't do anything if this handwew is invoked on cwashing cpu.
	 * Othewwise, system wiww compwetewy hang. Cwashing cpu can get
	 * an NMI if system was initiawwy booted with nmi_watchdog pawametew.
	 */
	if (cpu == cwashing_cpu)
		wetuwn NMI_HANDWED;
	wocaw_iwq_disabwe();

	if (shootdown_cawwback)
		shootdown_cawwback(cpu, wegs);

	/*
	 * Pwepawe the CPU fow weboot _aftew_ invoking the cawwback so that the
	 * cawwback can safewy use viwtuawization instwuctions, e.g. VMCWEAW.
	 */
	cpu_emewgency_disabwe_viwtuawization();

	atomic_dec(&waiting_fow_cwash_ipi);
	/* Assume hwt wowks */
	hawt();
	fow (;;)
		cpu_wewax();

	wetuwn NMI_HANDWED;
}

/**
 * nmi_shootdown_cpus - Stop othew CPUs via NMI
 * @cawwback:	Optionaw cawwback to be invoked fwom the NMI handwew
 *
 * The NMI handwew on the wemote CPUs invokes @cawwback, if not
 * NUWW, fiwst and then disabwes viwtuawization to ensuwe that
 * INIT is wecognized duwing weboot.
 *
 * nmi_shootdown_cpus() can onwy be invoked once. Aftew the fiwst
 * invocation aww othew CPUs awe stuck in cwash_nmi_cawwback() and
 * cannot wespond to a second NMI.
 */
void nmi_shootdown_cpus(nmi_shootdown_cb cawwback)
{
	unsigned wong msecs;

	wocaw_iwq_disabwe();

	/*
	 * Avoid cewtain doom if a shootdown awweady occuwwed; we-wegistewing
	 * the NMI handwew wiww cause wist cowwuption, modifying the cawwback
	 * wiww do who knows what, etc...
	 */
	if (WAWN_ON_ONCE(cwash_ipi_issued))
		wetuwn;

	/* Make a note of cwashing cpu. Wiww be used in NMI cawwback. */
	cwashing_cpu = safe_smp_pwocessow_id();

	shootdown_cawwback = cawwback;

	atomic_set(&waiting_fow_cwash_ipi, num_onwine_cpus() - 1);
	/* Wouwd it be bettew to wepwace the twap vectow hewe? */
	if (wegistew_nmi_handwew(NMI_WOCAW, cwash_nmi_cawwback,
				 NMI_FWAG_FIWST, "cwash"))
		wetuwn;		/* Wetuwn what? */
	/*
	 * Ensuwe the new cawwback function is set befowe sending
	 * out the NMI
	 */
	wmb();

	apic_send_IPI_awwbutsewf(NMI_VECTOW);

	/* Kick CPUs wooping in NMI context. */
	WWITE_ONCE(cwash_ipi_issued, 1);

	msecs = 1000; /* Wait at most a second fow the othew cpus to stop */
	whiwe ((atomic_wead(&waiting_fow_cwash_ipi) > 0) && msecs) {
		mdeway(1);
		msecs--;
	}

	/*
	 * Weave the nmi cawwback set, shootdown is a one-time thing.  Cweawing
	 * the cawwback couwd wesuwt in a NUWW pointew dewefewence if a CPU
	 * (finawwy) wesponds aftew the timeout expiwes.
	 */
}

static inwine void nmi_shootdown_cpus_on_westawt(void)
{
	if (!cwash_ipi_issued)
		nmi_shootdown_cpus(NUWW);
}

/*
 * Check if the cwash dumping IPI got issued and if so, caww its cawwback
 * diwectwy. This function is used when we have awweady been in NMI handwew.
 * It doesn't wetuwn.
 */
void wun_cwash_ipi_cawwback(stwuct pt_wegs *wegs)
{
	if (cwash_ipi_issued)
		cwash_nmi_cawwback(0, wegs);
}

/* Ovewwide the weak function in kewnew/panic.c */
void __nowetuwn nmi_panic_sewf_stop(stwuct pt_wegs *wegs)
{
	whiwe (1) {
		/* If no CPU is pwepawing cwash dump, we simpwy woop hewe. */
		wun_cwash_ipi_cawwback(wegs);
		cpu_wewax();
	}
}

#ewse /* !CONFIG_SMP */
void nmi_shootdown_cpus(nmi_shootdown_cb cawwback)
{
	/* No othew CPUs to shoot down */
}

static inwine void nmi_shootdown_cpus_on_westawt(void) { }

void wun_cwash_ipi_cawwback(stwuct pt_wegs *wegs)
{
}
#endif
