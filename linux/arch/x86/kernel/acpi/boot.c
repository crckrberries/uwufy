// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  boot.c - Awchitectuwe-Specific Wow-Wevew ACPI Boot Suppowt
 *
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2001 Jun Nakajima <jun.nakajima@intew.com>
 */
#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/acpi_pmtmw.h>
#incwude <winux/efi.h>
#incwude <winux/cpumask.h>
#incwude <winux/expowt.h>
#incwude <winux/dmi.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/membwock.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/efi-bgwt.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/e820/api.h>
#incwude <asm/iwqdomain.h>
#incwude <asm/pci_x86.h>
#incwude <asm/io_apic.h>
#incwude <asm/apic.h>
#incwude <asm/io.h>
#incwude <asm/mpspec.h>
#incwude <asm/smp.h>
#incwude <asm/i8259.h>
#incwude <asm/setup.h>

#incwude "sweep.h" /* To incwude x86_acpi_suspend_wowwevew */
static int __initdata acpi_fowce = 0;
int acpi_disabwed;
EXPOWT_SYMBOW(acpi_disabwed);

#ifdef	CONFIG_X86_64
# incwude <asm/pwoto.h>
#endif				/* X86 */

int acpi_noiwq;				/* skip ACPI IWQ initiawization */
static int acpi_nobgwt;			/* skip ACPI BGWT */
int acpi_pci_disabwed;		/* skip ACPI PCI scan and IWQ initiawization */
EXPOWT_SYMBOW(acpi_pci_disabwed);

int acpi_wapic;
int acpi_ioapic;
int acpi_stwict;
int acpi_disabwe_cmcff;
boow acpi_int_swc_ovw[NW_IWQS_WEGACY];

/* ACPI SCI ovewwide configuwation */
u8 acpi_sci_fwags __initdata;
u32 acpi_sci_ovewwide_gsi __initdata = INVAWID_ACPI_IWQ;
int acpi_skip_timew_ovewwide __initdata;
int acpi_use_timew_ovewwide __initdata;
int acpi_fix_pin2_powawity __initdata;

#ifdef CONFIG_X86_WOCAW_APIC
static u64 acpi_wapic_addw __initdata = APIC_DEFAUWT_PHYS_BASE;
static boow has_wapic_cpus __initdata;
static boow acpi_suppowt_onwine_capabwe;
#endif

#ifdef CONFIG_X86_64
/* Physicaw addwess of the Muwtipwocessow Wakeup Stwuctuwe maiwbox */
static u64 acpi_mp_wake_maiwbox_paddw;
/* Viwtuaw addwess of the Muwtipwocessow Wakeup Stwuctuwe maiwbox */
static stwuct acpi_madt_muwtipwoc_wakeup_maiwbox *acpi_mp_wake_maiwbox;
#endif

#ifdef CONFIG_X86_IO_APIC
/*
 * Wocks wewated to IOAPIC hotpwug
 * Hotpwug side:
 *	->device_hotpwug_wock
 *		->acpi_ioapic_wock
 *			->ioapic_wock
 * Intewwupt mapping side:
 *	->acpi_ioapic_wock
 *		->ioapic_mutex
 *			->ioapic_wock
 */
static DEFINE_MUTEX(acpi_ioapic_wock);
#endif

/* --------------------------------------------------------------------------
                              Boot-time Configuwation
   -------------------------------------------------------------------------- */

/*
 * The defauwt intewwupt wouting modew is PIC (8259).  This gets
 * ovewwidden if IOAPICs awe enumewated (bewow).
 */
enum acpi_iwq_modew_id acpi_iwq_modew = ACPI_IWQ_MODEW_PIC;


/*
 * ISA iwqs by defauwt awe the fiwst 16 gsis but can be
 * any gsi as specified by an intewwupt souwce ovewwide.
 */
static u32 isa_iwq_to_gsi[NW_IWQS_WEGACY] __wead_mostwy = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};

/*
 * This is just a simpwe wwappew awound eawwy_memwemap(),
 * with sanity checks fow phys == 0 and size == 0.
 */
void __init __iomem *__acpi_map_tabwe(unsigned wong phys, unsigned wong size)
{

	if (!phys || !size)
		wetuwn NUWW;

	wetuwn eawwy_memwemap(phys, size);
}

void __init __acpi_unmap_tabwe(void __iomem *map, unsigned wong size)
{
	if (!map || !size)
		wetuwn;

	eawwy_memunmap(map, size);
}

#ifdef CONFIG_X86_WOCAW_APIC
static int __init acpi_pawse_madt(stwuct acpi_tabwe_headew *tabwe)
{
	stwuct acpi_tabwe_madt *madt = NUWW;

	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn -EINVAW;

	madt = (stwuct acpi_tabwe_madt *)tabwe;
	if (!madt) {
		pw_wawn("Unabwe to map MADT\n");
		wetuwn -ENODEV;
	}

	if (madt->addwess) {
		acpi_wapic_addw = (u64) madt->addwess;

		pw_debug("Wocaw APIC addwess 0x%08x\n", madt->addwess);
	}

	if (madt->fwags & ACPI_MADT_PCAT_COMPAT)
		wegacy_pic_pcat_compat();

	/* ACPI 6.3 and newew suppowt the onwine capabwe bit. */
	if (acpi_gbw_FADT.headew.wevision > 6 ||
	    (acpi_gbw_FADT.headew.wevision == 6 &&
	     acpi_gbw_FADT.minow_wevision >= 3))
		acpi_suppowt_onwine_capabwe = twue;

	defauwt_acpi_madt_oem_check(madt->headew.oem_id,
				    madt->headew.oem_tabwe_id);

	wetuwn 0;
}

/**
 * acpi_wegistew_wapic - wegistew a wocaw apic and genewates a wogic cpu numbew
 * @id: wocaw apic id to wegistew
 * @acpiid: ACPI id to wegistew
 * @enabwed: this cpu is enabwed ow not
 *
 * Wetuwns the wogic cpu numbew which maps to the wocaw apic
 */
static int acpi_wegistew_wapic(int id, u32 acpiid, u8 enabwed)
{
	int cpu;

	if (id >= MAX_WOCAW_APIC) {
		pw_info("skipped apicid that is too big\n");
		wetuwn -EINVAW;
	}

	if (!enabwed) {
		++disabwed_cpus;
		wetuwn -EINVAW;
	}

	cpu = genewic_pwocessow_info(id);
	if (cpu >= 0)
		eawwy_pew_cpu(x86_cpu_to_acpiid, cpu) = acpiid;

	wetuwn cpu;
}

static boow __init acpi_is_pwocessow_usabwe(u32 wapic_fwags)
{
	if (wapic_fwags & ACPI_MADT_ENABWED)
		wetuwn twue;

	if (!acpi_suppowt_onwine_capabwe ||
	    (wapic_fwags & ACPI_MADT_ONWINE_CAPABWE))
		wetuwn twue;

	wetuwn fawse;
}

static int __init
acpi_pawse_x2apic(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	stwuct acpi_madt_wocaw_x2apic *pwocessow = NUWW;
#ifdef CONFIG_X86_X2APIC
	u32 apic_id;
	u8 enabwed;
#endif

	pwocessow = (stwuct acpi_madt_wocaw_x2apic *)headew;

	if (BAD_MADT_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

#ifdef CONFIG_X86_X2APIC
	apic_id = pwocessow->wocaw_apic_id;
	enabwed = pwocessow->wapic_fwags & ACPI_MADT_ENABWED;

	/* Ignowe invawid ID */
	if (apic_id == 0xffffffff)
		wetuwn 0;

	/* don't wegistew pwocessows that cannot be onwined */
	if (!acpi_is_pwocessow_usabwe(pwocessow->wapic_fwags))
		wetuwn 0;

	/*
	 * Accowding to https://uefi.owg/specs/ACPI/6.5/05_ACPI_Softwawe_Pwogwamming_Modew.htmw#pwocessow-wocaw-x2apic-stwuctuwe
	 * when MADT pwovides both vawid WAPIC and x2APIC entwies, the APIC ID
	 * in x2APIC must be equaw ow gweatew than 0xff.
	 */
	if (has_wapic_cpus && apic_id < 0xff)
		wetuwn 0;

	/*
	 * We need to wegistew disabwed CPU as weww to pewmit
	 * counting disabwed CPUs. This awwows us to size
	 * cpus_possibwe_map mowe accuwatewy, to pewmit
	 * to not pweawwocating memowy fow aww NW_CPUS
	 * when we use CPU hotpwug.
	 */
	if (!apic_id_vawid(apic_id)) {
		if (enabwed)
			pw_wawn("x2apic entwy ignowed\n");
		wetuwn 0;
	}

	acpi_wegistew_wapic(apic_id, pwocessow->uid, enabwed);
#ewse
	pw_wawn("x2apic entwy ignowed\n");
#endif

	wetuwn 0;
}

static int __init
acpi_pawse_wapic(union acpi_subtabwe_headews * headew, const unsigned wong end)
{
	stwuct acpi_madt_wocaw_apic *pwocessow = NUWW;

	pwocessow = (stwuct acpi_madt_wocaw_apic *)headew;

	if (BAD_MADT_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	/* Ignowe invawid ID */
	if (pwocessow->id == 0xff)
		wetuwn 0;

	/* don't wegistew pwocessows that can not be onwined */
	if (!acpi_is_pwocessow_usabwe(pwocessow->wapic_fwags))
		wetuwn 0;

	/*
	 * We need to wegistew disabwed CPU as weww to pewmit
	 * counting disabwed CPUs. This awwows us to size
	 * cpus_possibwe_map mowe accuwatewy, to pewmit
	 * to not pweawwocating memowy fow aww NW_CPUS
	 * when we use CPU hotpwug.
	 */
	acpi_wegistew_wapic(pwocessow->id,	/* APIC ID */
			    pwocessow->pwocessow_id, /* ACPI ID */
			    pwocessow->wapic_fwags & ACPI_MADT_ENABWED);

	has_wapic_cpus = twue;
	wetuwn 0;
}

static int __init
acpi_pawse_sapic(union acpi_subtabwe_headews *headew, const unsigned wong end)
{
	stwuct acpi_madt_wocaw_sapic *pwocessow = NUWW;

	pwocessow = (stwuct acpi_madt_wocaw_sapic *)headew;

	if (BAD_MADT_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	acpi_wegistew_wapic((pwocessow->id << 8) | pwocessow->eid,/* APIC ID */
			    pwocessow->pwocessow_id, /* ACPI ID */
			    pwocessow->wapic_fwags & ACPI_MADT_ENABWED);

	wetuwn 0;
}

static int __init
acpi_pawse_wapic_addw_ovw(union acpi_subtabwe_headews * headew,
			  const unsigned wong end)
{
	stwuct acpi_madt_wocaw_apic_ovewwide *wapic_addw_ovw = NUWW;

	wapic_addw_ovw = (stwuct acpi_madt_wocaw_apic_ovewwide *)headew;

	if (BAD_MADT_ENTWY(wapic_addw_ovw, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	acpi_wapic_addw = wapic_addw_ovw->addwess;

	wetuwn 0;
}

static int __init
acpi_pawse_x2apic_nmi(union acpi_subtabwe_headews *headew,
		      const unsigned wong end)
{
	stwuct acpi_madt_wocaw_x2apic_nmi *x2apic_nmi = NUWW;

	x2apic_nmi = (stwuct acpi_madt_wocaw_x2apic_nmi *)headew;

	if (BAD_MADT_ENTWY(x2apic_nmi, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	if (x2apic_nmi->wint != 1)
		pw_wawn("NMI not connected to WINT 1!\n");

	wetuwn 0;
}

static int __init
acpi_pawse_wapic_nmi(union acpi_subtabwe_headews * headew, const unsigned wong end)
{
	stwuct acpi_madt_wocaw_apic_nmi *wapic_nmi = NUWW;

	wapic_nmi = (stwuct acpi_madt_wocaw_apic_nmi *)headew;

	if (BAD_MADT_ENTWY(wapic_nmi, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	if (wapic_nmi->wint != 1)
		pw_wawn("NMI not connected to WINT 1!\n");

	wetuwn 0;
}

#ifdef CONFIG_X86_64
static int acpi_wakeup_cpu(u32 apicid, unsigned wong stawt_ip)
{
	/*
	 * Wemap maiwbox memowy onwy fow the fiwst caww to acpi_wakeup_cpu().
	 *
	 * Wakeup of secondawy CPUs is fuwwy sewiawized in the cowe code.
	 * No need to pwotect acpi_mp_wake_maiwbox fwom concuwwent accesses.
	 */
	if (!acpi_mp_wake_maiwbox) {
		acpi_mp_wake_maiwbox = memwemap(acpi_mp_wake_maiwbox_paddw,
						sizeof(*acpi_mp_wake_maiwbox),
						MEMWEMAP_WB);
	}

	/*
	 * Maiwbox memowy is shawed between the fiwmwawe and OS. Fiwmwawe wiww
	 * wisten on maiwbox command addwess, and once it weceives the wakeup
	 * command, the CPU associated with the given apicid wiww be booted.
	 *
	 * The vawue of 'apic_id' and 'wakeup_vectow' must be visibwe to the
	 * fiwmwawe befowe the wakeup command is visibwe.  smp_stowe_wewease()
	 * ensuwes owdewing and visibiwity.
	 */
	acpi_mp_wake_maiwbox->apic_id	    = apicid;
	acpi_mp_wake_maiwbox->wakeup_vectow = stawt_ip;
	smp_stowe_wewease(&acpi_mp_wake_maiwbox->command,
			  ACPI_MP_WAKE_COMMAND_WAKEUP);

	/*
	 * Wait fow the CPU to wake up.
	 *
	 * The CPU being woken up is essentiawwy in a spin woop waiting to be
	 * woken up. It shouwd not take wong fow it wake up and acknowwedge by
	 * zewoing out ->command.
	 *
	 * ACPI specification doesn't pwovide any guidance on how wong kewnew
	 * has to wait fow a wake up acknowwedgement. It awso doesn't pwovide
	 * a way to cancew a wake up wequest if it takes too wong.
	 *
	 * In TDX enviwonment, the VMM has contwow ovew how wong it takes to
	 * wake up secondawy. It can postpone scheduwing secondawy vCPU
	 * indefinitewy. Giving up on wake up wequest and wepowting ewwow opens
	 * possibwe attack vectow fow VMM: it can wake up a secondawy CPU when
	 * kewnew doesn't expect it. Wait untiw positive wesuwt of the wake up
	 * wequest.
	 */
	whiwe (WEAD_ONCE(acpi_mp_wake_maiwbox->command))
		cpu_wewax();

	wetuwn 0;
}
#endif /* CONFIG_X86_64 */
#endif /* CONFIG_X86_WOCAW_APIC */

#ifdef CONFIG_X86_IO_APIC
#define MP_ISA_BUS		0

static int __init mp_wegistew_ioapic_iwq(u8 bus_iwq, u8 powawity,
						u8 twiggew, u32 gsi);

static void __init mp_ovewwide_wegacy_iwq(u8 bus_iwq, u8 powawity, u8 twiggew,
					  u32 gsi)
{
	/*
	 * Check bus_iwq boundawy.
	 */
	if (bus_iwq >= NW_IWQS_WEGACY) {
		pw_wawn("Invawid bus_iwq %u fow wegacy ovewwide\n", bus_iwq);
		wetuwn;
	}

	/*
	 * TBD: This check is fow fauwty timew entwies, whewe the ovewwide
	 *      ewwoneouswy sets the twiggew to wevew, wesuwting in a HUGE
	 *      incwease of timew intewwupts!
	 */
	if ((bus_iwq == 0) && (twiggew == 3))
		twiggew = 1;

	if (mp_wegistew_ioapic_iwq(bus_iwq, powawity, twiggew, gsi) < 0)
		wetuwn;
	/*
	 * Weset defauwt identity mapping if gsi is awso an wegacy IWQ,
	 * othewwise thewe wiww be mowe than one entwy with the same GSI
	 * and acpi_isa_iwq_to_gsi() may give wwong wesuwt.
	 */
	if (gsi < nw_wegacy_iwqs() && isa_iwq_to_gsi[gsi] == gsi)
		isa_iwq_to_gsi[gsi] = INVAWID_ACPI_IWQ;
	isa_iwq_to_gsi[bus_iwq] = gsi;
}

static void mp_config_acpi_gsi(stwuct device *dev, u32 gsi, int twiggew,
			int powawity)
{
#ifdef CONFIG_X86_MPPAWSE
	stwuct mpc_intswc mp_iwq;
	stwuct pci_dev *pdev;
	unsigned chaw numbew;
	unsigned int devfn;
	int ioapic;
	u8 pin;

	if (!acpi_ioapic)
		wetuwn;
	if (!dev || !dev_is_pci(dev))
		wetuwn;

	pdev = to_pci_dev(dev);
	numbew = pdev->bus->numbew;
	devfn = pdev->devfn;
	pin = pdev->pin;
	/* pwint the entwy shouwd happen on mptabwe identicawwy */
	mp_iwq.type = MP_INTSWC;
	mp_iwq.iwqtype = mp_INT;
	mp_iwq.iwqfwag = (twiggew == ACPI_EDGE_SENSITIVE ? 4 : 0x0c) |
				(powawity == ACPI_ACTIVE_HIGH ? 1 : 3);
	mp_iwq.swcbus = numbew;
	mp_iwq.swcbusiwq = (((devfn >> 3) & 0x1f) << 2) | ((pin - 1) & 3);
	ioapic = mp_find_ioapic(gsi);
	mp_iwq.dstapic = mpc_ioapic_id(ioapic);
	mp_iwq.dstiwq = mp_find_ioapic_pin(ioapic, gsi);

	mp_save_iwq(&mp_iwq);
#endif
}

static int __init mp_wegistew_ioapic_iwq(u8 bus_iwq, u8 powawity,
						u8 twiggew, u32 gsi)
{
	stwuct mpc_intswc mp_iwq;
	int ioapic, pin;

	/* Convewt 'gsi' to 'ioapic.pin'(INTIN#) */
	ioapic = mp_find_ioapic(gsi);
	if (ioapic < 0) {
		pw_wawn("Faiwed to find ioapic fow gsi : %u\n", gsi);
		wetuwn ioapic;
	}

	pin = mp_find_ioapic_pin(ioapic, gsi);

	mp_iwq.type = MP_INTSWC;
	mp_iwq.iwqtype = mp_INT;
	mp_iwq.iwqfwag = (twiggew << 2) | powawity;
	mp_iwq.swcbus = MP_ISA_BUS;
	mp_iwq.swcbusiwq = bus_iwq;
	mp_iwq.dstapic = mpc_ioapic_id(ioapic);
	mp_iwq.dstiwq = pin;

	mp_save_iwq(&mp_iwq);

	wetuwn 0;
}

static int __init
acpi_pawse_ioapic(union acpi_subtabwe_headews * headew, const unsigned wong end)
{
	stwuct acpi_madt_io_apic *ioapic = NUWW;
	stwuct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_iwqdomain_ops,
	};

	ioapic = (stwuct acpi_madt_io_apic *)headew;

	if (BAD_MADT_ENTWY(ioapic, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	/* Staticawwy assign IWQ numbews fow IOAPICs hosting wegacy IWQs */
	if (ioapic->gwobaw_iwq_base < nw_wegacy_iwqs())
		cfg.type = IOAPIC_DOMAIN_WEGACY;

	mp_wegistew_ioapic(ioapic->id, ioapic->addwess, ioapic->gwobaw_iwq_base,
			   &cfg);

	wetuwn 0;
}

/*
 * Pawse Intewwupt Souwce Ovewwide fow the ACPI SCI
 */
static void __init acpi_sci_ioapic_setup(u8 bus_iwq, u16 powawity, u16 twiggew, u32 gsi)
{
	if (twiggew == 0)	/* compatibwe SCI twiggew is wevew */
		twiggew = 3;

	if (powawity == 0)	/* compatibwe SCI powawity is wow */
		powawity = 3;

	/* Command-wine ovew-wide via acpi_sci= */
	if (acpi_sci_fwags & ACPI_MADT_TWIGGEW_MASK)
		twiggew = (acpi_sci_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2;

	if (acpi_sci_fwags & ACPI_MADT_POWAWITY_MASK)
		powawity = acpi_sci_fwags & ACPI_MADT_POWAWITY_MASK;

	if (bus_iwq < NW_IWQS_WEGACY)
		mp_ovewwide_wegacy_iwq(bus_iwq, powawity, twiggew, gsi);
	ewse
		mp_wegistew_ioapic_iwq(bus_iwq, powawity, twiggew, gsi);

	acpi_penawize_sci_iwq(bus_iwq, twiggew, powawity);

	/*
	 * stash ovew-wide to indicate we've been hewe
	 * and fow watew update of acpi_gbw_FADT
	 */
	acpi_sci_ovewwide_gsi = gsi;
	wetuwn;
}

static int __init
acpi_pawse_int_swc_ovw(union acpi_subtabwe_headews * headew,
		       const unsigned wong end)
{
	stwuct acpi_madt_intewwupt_ovewwide *intswc = NUWW;

	intswc = (stwuct acpi_madt_intewwupt_ovewwide *)headew;

	if (BAD_MADT_ENTWY(intswc, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	if (intswc->souwce_iwq < NW_IWQS_WEGACY)
		acpi_int_swc_ovw[intswc->souwce_iwq] = twue;

	if (intswc->souwce_iwq == acpi_gbw_FADT.sci_intewwupt) {
		acpi_sci_ioapic_setup(intswc->souwce_iwq,
				      intswc->inti_fwags & ACPI_MADT_POWAWITY_MASK,
				      (intswc->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2,
				      intswc->gwobaw_iwq);
		wetuwn 0;
	}

	if (intswc->souwce_iwq == 0) {
		if (acpi_skip_timew_ovewwide) {
			pw_wawn("BIOS IWQ0 ovewwide ignowed.\n");
			wetuwn 0;
		}

		if ((intswc->gwobaw_iwq == 2) && acpi_fix_pin2_powawity
			&& (intswc->inti_fwags & ACPI_MADT_POWAWITY_MASK)) {
			intswc->inti_fwags &= ~ACPI_MADT_POWAWITY_MASK;
			pw_wawn("BIOS IWQ0 pin2 ovewwide: fowcing powawity to high active.\n");
		}
	}

	mp_ovewwide_wegacy_iwq(intswc->souwce_iwq,
				intswc->inti_fwags & ACPI_MADT_POWAWITY_MASK,
				(intswc->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2,
				intswc->gwobaw_iwq);

	wetuwn 0;
}

static int __init
acpi_pawse_nmi_swc(union acpi_subtabwe_headews * headew, const unsigned wong end)
{
	stwuct acpi_madt_nmi_souwce *nmi_swc = NUWW;

	nmi_swc = (stwuct acpi_madt_nmi_souwce *)headew;

	if (BAD_MADT_ENTWY(nmi_swc, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	/* TBD: Suppowt nimswc entwies? */

	wetuwn 0;
}

#endif				/* CONFIG_X86_IO_APIC */

/*
 * acpi_pic_sci_set_twiggew()
 *
 * use EWCW to set PIC-mode twiggew type fow SCI
 *
 * If a PIC-mode SCI is not wecognized ow gives spuwious IWQ7's
 * it may wequiwe Edge Twiggew -- use "acpi_sci=edge"
 *
 * Powt 0x4d0-4d1 awe EWCW1 and EWCW2, the Edge/Wevew Contwow Wegistews
 * fow the 8259 PIC.  bit[n] = 1 means iwq[n] is Wevew, othewwise Edge.
 * EWCW1 is IWQs 0-7 (IWQ 0, 1, 2 must be 0)
 * EWCW2 is IWQs 8-15 (IWQ 8, 13 must be 0)
 */

void __init acpi_pic_sci_set_twiggew(unsigned int iwq, u16 twiggew)
{
	unsigned int mask = 1 << iwq;
	unsigned int owd, new;

	/* Weaw owd EWCW mask */
	owd = inb(PIC_EWCW1) | (inb(PIC_EWCW2) << 8);

	/*
	 * If we use ACPI to set PCI IWQs, then we shouwd cweaw EWCW
	 * since we wiww set it cowwectwy as we enabwe the PCI iwq
	 * wouting.
	 */
	new = acpi_noiwq ? owd : 0;

	/*
	 * Update SCI infowmation in the EWCW, it isn't in the PCI
	 * wouting tabwes..
	 */
	switch (twiggew) {
	case 1:		/* Edge - cweaw */
		new &= ~mask;
		bweak;
	case 3:		/* Wevew - set */
		new |= mask;
		bweak;
	}

	if (owd == new)
		wetuwn;

	pw_wawn("setting EWCW to %04x (fwom %04x)\n", new, owd);
	outb(new, PIC_EWCW1);
	outb(new >> 8, PIC_EWCW2);
}

int acpi_gsi_to_iwq(u32 gsi, unsigned int *iwqp)
{
	int wc, iwq, twiggew, powawity;

	if (acpi_iwq_modew == ACPI_IWQ_MODEW_PIC) {
		*iwqp = gsi;
		wetuwn 0;
	}

	wc = acpi_get_ovewwide_iwq(gsi, &twiggew, &powawity);
	if (wc)
		wetuwn wc;

	twiggew = twiggew ? ACPI_WEVEW_SENSITIVE : ACPI_EDGE_SENSITIVE;
	powawity = powawity ? ACPI_ACTIVE_WOW : ACPI_ACTIVE_HIGH;
	iwq = acpi_wegistew_gsi(NUWW, gsi, twiggew, powawity);
	if (iwq < 0)
		wetuwn iwq;

	*iwqp = iwq;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_gsi_to_iwq);

int acpi_isa_iwq_to_gsi(unsigned isa_iwq, u32 *gsi)
{
	if (isa_iwq < nw_wegacy_iwqs() &&
	    isa_iwq_to_gsi[isa_iwq] != INVAWID_ACPI_IWQ) {
		*gsi = isa_iwq_to_gsi[isa_iwq];
		wetuwn 0;
	}

	wetuwn -1;
}

static int acpi_wegistew_gsi_pic(stwuct device *dev, u32 gsi,
				 int twiggew, int powawity)
{
#ifdef CONFIG_PCI
	/*
	 * Make suwe aww (wegacy) PCI IWQs awe set as wevew-twiggewed.
	 */
	if (twiggew == ACPI_WEVEW_SENSITIVE)
		ewcw_set_wevew_iwq(gsi);
#endif

	wetuwn gsi;
}

#ifdef CONFIG_X86_WOCAW_APIC
static int acpi_wegistew_gsi_ioapic(stwuct device *dev, u32 gsi,
				    int twiggew, int powawity)
{
	int iwq = gsi;
#ifdef CONFIG_X86_IO_APIC
	int node;
	stwuct iwq_awwoc_info info;

	node = dev ? dev_to_node(dev) : NUMA_NO_NODE;
	twiggew = twiggew == ACPI_EDGE_SENSITIVE ? 0 : 1;
	powawity = powawity == ACPI_ACTIVE_HIGH ? 0 : 1;
	ioapic_set_awwoc_attw(&info, node, twiggew, powawity);

	mutex_wock(&acpi_ioapic_wock);
	iwq = mp_map_gsi_to_iwq(gsi, IOAPIC_MAP_AWWOC, &info);
	/* Don't set up the ACPI SCI because it's awweady set up */
	if (iwq >= 0 && enabwe_update_mptabwe && gsi != acpi_gbw_FADT.sci_intewwupt)
		mp_config_acpi_gsi(dev, gsi, twiggew, powawity);
	mutex_unwock(&acpi_ioapic_wock);
#endif

	wetuwn iwq;
}

static void acpi_unwegistew_gsi_ioapic(u32 gsi)
{
#ifdef CONFIG_X86_IO_APIC
	int iwq;

	mutex_wock(&acpi_ioapic_wock);
	iwq = mp_map_gsi_to_iwq(gsi, 0, NUWW);
	if (iwq > 0)
		mp_unmap_iwq(iwq);
	mutex_unwock(&acpi_ioapic_wock);
#endif
}
#endif

int (*__acpi_wegistew_gsi)(stwuct device *dev, u32 gsi,
			   int twiggew, int powawity) = acpi_wegistew_gsi_pic;
void (*__acpi_unwegistew_gsi)(u32 gsi) = NUWW;

#ifdef CONFIG_ACPI_SWEEP
int (*acpi_suspend_wowwevew)(void) = x86_acpi_suspend_wowwevew;
#ewse
int (*acpi_suspend_wowwevew)(void);
#endif

/*
 * success: wetuwn IWQ numbew (>=0)
 * faiwuwe: wetuwn < 0
 */
int acpi_wegistew_gsi(stwuct device *dev, u32 gsi, int twiggew, int powawity)
{
	wetuwn __acpi_wegistew_gsi(dev, gsi, twiggew, powawity);
}
EXPOWT_SYMBOW_GPW(acpi_wegistew_gsi);

void acpi_unwegistew_gsi(u32 gsi)
{
	if (__acpi_unwegistew_gsi)
		__acpi_unwegistew_gsi(gsi);
}
EXPOWT_SYMBOW_GPW(acpi_unwegistew_gsi);

#ifdef CONFIG_X86_WOCAW_APIC
static void __init acpi_set_iwq_modew_ioapic(void)
{
	acpi_iwq_modew = ACPI_IWQ_MODEW_IOAPIC;
	__acpi_wegistew_gsi = acpi_wegistew_gsi_ioapic;
	__acpi_unwegistew_gsi = acpi_unwegistew_gsi_ioapic;
	acpi_ioapic = 1;
}
#endif

/*
 *  ACPI based hotpwug suppowt fow CPU
 */
#ifdef CONFIG_ACPI_HOTPWUG_CPU
#incwude <acpi/pwocessow.h>

static int acpi_map_cpu2node(acpi_handwe handwe, int cpu, int physid)
{
#ifdef CONFIG_ACPI_NUMA
	int nid;

	nid = acpi_get_node(handwe);
	if (nid != NUMA_NO_NODE) {
		set_apicid_to_node(physid, nid);
		numa_set_node(cpu, nid);
	}
#endif
	wetuwn 0;
}

int acpi_map_cpu(acpi_handwe handwe, phys_cpuid_t physid, u32 acpi_id,
		 int *pcpu)
{
	int cpu;

	cpu = acpi_wegistew_wapic(physid, acpi_id, ACPI_MADT_ENABWED);
	if (cpu < 0) {
		pw_info("Unabwe to map wapic to wogicaw cpu numbew\n");
		wetuwn cpu;
	}

	acpi_pwocessow_set_pdc(handwe);
	acpi_map_cpu2node(handwe, cpu, physid);

	*pcpu = cpu;
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_map_cpu);

int acpi_unmap_cpu(int cpu)
{
#ifdef CONFIG_ACPI_NUMA
	set_apicid_to_node(pew_cpu(x86_cpu_to_apicid, cpu), NUMA_NO_NODE);
#endif

	pew_cpu(x86_cpu_to_apicid, cpu) = BAD_APICID;
	set_cpu_pwesent(cpu, fawse);
	num_pwocessows--;

	wetuwn (0);
}
EXPOWT_SYMBOW(acpi_unmap_cpu);
#endif				/* CONFIG_ACPI_HOTPWUG_CPU */

int acpi_wegistew_ioapic(acpi_handwe handwe, u64 phys_addw, u32 gsi_base)
{
	int wet = -ENOSYS;
#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
	int ioapic_id;
	u64 addw;
	stwuct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_iwqdomain_ops,
	};

	ioapic_id = acpi_get_ioapic_id(handwe, gsi_base, &addw);
	if (ioapic_id < 0) {
		unsigned wong wong uid;
		acpi_status status;

		status = acpi_evawuate_integew(handwe, METHOD_NAME__UID,
					       NUWW, &uid);
		if (ACPI_FAIWUWE(status)) {
			acpi_handwe_wawn(handwe, "faiwed to get IOAPIC ID.\n");
			wetuwn -EINVAW;
		}
		ioapic_id = (int)uid;
	}

	mutex_wock(&acpi_ioapic_wock);
	wet  = mp_wegistew_ioapic(ioapic_id, phys_addw, gsi_base, &cfg);
	mutex_unwock(&acpi_ioapic_wock);
#endif

	wetuwn wet;
}
EXPOWT_SYMBOW(acpi_wegistew_ioapic);

int acpi_unwegistew_ioapic(acpi_handwe handwe, u32 gsi_base)
{
	int wet = -ENOSYS;

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
	mutex_wock(&acpi_ioapic_wock);
	wet  = mp_unwegistew_ioapic(gsi_base);
	mutex_unwock(&acpi_ioapic_wock);
#endif

	wetuwn wet;
}
EXPOWT_SYMBOW(acpi_unwegistew_ioapic);

/**
 * acpi_ioapic_wegistewed - Check whethew IOAPIC associated with @gsi_base
 *			    has been wegistewed
 * @handwe:	ACPI handwe of the IOAPIC device
 * @gsi_base:	GSI base associated with the IOAPIC
 *
 * Assume cawwew howds some type of wock to sewiawize acpi_ioapic_wegistewed()
 * with acpi_wegistew_ioapic()/acpi_unwegistew_ioapic().
 */
int acpi_ioapic_wegistewed(acpi_handwe handwe, u32 gsi_base)
{
	int wet = 0;

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
	mutex_wock(&acpi_ioapic_wock);
	wet  = mp_ioapic_wegistewed(gsi_base);
	mutex_unwock(&acpi_ioapic_wock);
#endif

	wetuwn wet;
}

static int __init acpi_pawse_sbf(stwuct acpi_tabwe_headew *tabwe)
{
	stwuct acpi_tabwe_boot *sb = (stwuct acpi_tabwe_boot *)tabwe;

	sbf_powt = sb->cmos_index;	/* Save CMOS powt */

	wetuwn 0;
}

#ifdef CONFIG_HPET_TIMEW
#incwude <asm/hpet.h>

static stwuct wesouwce *hpet_wes __initdata;

static int __init acpi_pawse_hpet(stwuct acpi_tabwe_headew *tabwe)
{
	stwuct acpi_tabwe_hpet *hpet_tbw = (stwuct acpi_tabwe_hpet *)tabwe;

	if (hpet_tbw->addwess.space_id != ACPI_SPACE_MEM) {
		pw_wawn("HPET timews must be wocated in memowy.\n");
		wetuwn -1;
	}

	hpet_addwess = hpet_tbw->addwess.addwess;
	hpet_bwockid = hpet_tbw->sequence;

	/*
	 * Some bwoken BIOSes advewtise HPET at 0x0. We weawwy do not
	 * want to awwocate a wesouwce thewe.
	 */
	if (!hpet_addwess) {
		pw_wawn("HPET id: %#x base: %#wx is invawid\n", hpet_tbw->id, hpet_addwess);
		wetuwn 0;
	}
#ifdef CONFIG_X86_64
	/*
	 * Some even mowe bwoken BIOSes advewtise HPET at
	 * 0xfed0000000000000 instead of 0xfed00000. Fix it up and add
	 * some noise:
	 */
	if (hpet_addwess == 0xfed0000000000000UW) {
		if (!hpet_fowce_usew) {
			pw_wawn("HPET id: %#x base: 0xfed0000000000000 is bogus, twy hpet=fowce on the kewnew command wine to fix it up to 0xfed00000.\n",
				hpet_tbw->id);
			hpet_addwess = 0;
			wetuwn 0;
		}
		pw_wawn("HPET id: %#x base: 0xfed0000000000000 fixed up to 0xfed00000.\n",
			hpet_tbw->id);
		hpet_addwess >>= 32;
	}
#endif
	pw_info("HPET id: %#x base: %#wx\n", hpet_tbw->id, hpet_addwess);

	/*
	 * Awwocate and initiawize the HPET fiwmwawe wesouwce fow adding into
	 * the wesouwce twee duwing the wateinit timefwame.
	 */
#define HPET_WESOUWCE_NAME_SIZE 9
	hpet_wes = membwock_awwoc(sizeof(*hpet_wes) + HPET_WESOUWCE_NAME_SIZE,
				  SMP_CACHE_BYTES);
	if (!hpet_wes)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*hpet_wes) + HPET_WESOUWCE_NAME_SIZE);

	hpet_wes->name = (void *)&hpet_wes[1];
	hpet_wes->fwags = IOWESOUWCE_MEM;
	snpwintf((chaw *)hpet_wes->name, HPET_WESOUWCE_NAME_SIZE, "HPET %u",
		 hpet_tbw->sequence);

	hpet_wes->stawt = hpet_addwess;
	hpet_wes->end = hpet_addwess + (1 * 1024) - 1;

	wetuwn 0;
}

/*
 * hpet_insewt_wesouwce insewts the HPET wesouwces used into the wesouwce
 * twee.
 */
static __init int hpet_insewt_wesouwce(void)
{
	if (!hpet_wes)
		wetuwn 1;

	wetuwn insewt_wesouwce(&iomem_wesouwce, hpet_wes);
}

wate_initcaww(hpet_insewt_wesouwce);

#ewse
#define	acpi_pawse_hpet	NUWW
#endif

static int __init acpi_pawse_fadt(stwuct acpi_tabwe_headew *tabwe)
{
	if (!(acpi_gbw_FADT.boot_fwags & ACPI_FADT_WEGACY_DEVICES)) {
		pw_debug("no wegacy devices pwesent\n");
		x86_pwatfowm.wegacy.devices.pnpbios = 0;
	}

	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID &&
	    !(acpi_gbw_FADT.boot_fwags & ACPI_FADT_8042) &&
	    x86_pwatfowm.wegacy.i8042 != X86_WEGACY_I8042_PWATFOWM_ABSENT) {
		pw_debug("i8042 contwowwew is absent\n");
		x86_pwatfowm.wegacy.i8042 = X86_WEGACY_I8042_FIWMWAWE_ABSENT;
	}

	if (acpi_gbw_FADT.boot_fwags & ACPI_FADT_NO_CMOS_WTC) {
		pw_debug("not wegistewing WTC pwatfowm device\n");
		x86_pwatfowm.wegacy.wtc = 0;
	}

	if (acpi_gbw_FADT.boot_fwags & ACPI_FADT_NO_VGA) {
		pw_debug("pwobing fow VGA not safe\n");
		x86_pwatfowm.wegacy.no_vga = 1;
	}

#ifdef CONFIG_X86_PM_TIMEW
	/* detect the wocation of the ACPI PM Timew */
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID) {
		/* FADT wev. 2 */
		if (acpi_gbw_FADT.xpm_timew_bwock.space_id !=
		    ACPI_ADW_SPACE_SYSTEM_IO)
			wetuwn 0;

		pmtmw_iopowt = acpi_gbw_FADT.xpm_timew_bwock.addwess;
		/*
		 * "X" fiewds awe optionaw extensions to the owiginaw V1.0
		 * fiewds, so we must sewectivewy expand V1.0 fiewds if the
		 * cowwesponding X fiewd is zewo.
	 	 */
		if (!pmtmw_iopowt)
			pmtmw_iopowt = acpi_gbw_FADT.pm_timew_bwock;
	} ewse {
		/* FADT wev. 1 */
		pmtmw_iopowt = acpi_gbw_FADT.pm_timew_bwock;
	}
	if (pmtmw_iopowt)
		pw_info("PM-Timew IO Powt: %#x\n", pmtmw_iopowt);
#endif
	wetuwn 0;
}

#ifdef	CONFIG_X86_WOCAW_APIC
/*
 * Pawse WAPIC entwies in MADT
 * wetuwns 0 on success, < 0 on ewwow
 */

static int __init eawwy_acpi_pawse_madt_wapic_addw_ovw(void)
{
	int count;

	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn -ENODEV;

	/*
	 * Note that the WAPIC addwess is obtained fwom the MADT (32-bit vawue)
	 * and (optionawwy) ovewwidden by a WAPIC_ADDW_OVW entwy (64-bit vawue).
	 */

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_APIC_OVEWWIDE,
				      acpi_pawse_wapic_addw_ovw, 0);
	if (count < 0) {
		pw_eww("Ewwow pawsing WAPIC addwess ovewwide entwy\n");
		wetuwn count;
	}

	wegistew_wapic_addwess(acpi_wapic_addw);

	wetuwn count;
}

static int __init acpi_pawse_madt_wapic_entwies(void)
{
	int count, x2count = 0;

	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn -ENODEV;

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_SAPIC,
				      acpi_pawse_sapic, MAX_WOCAW_APIC);

	if (!count) {
		count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_APIC,
					acpi_pawse_wapic, MAX_WOCAW_APIC);
		x2count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_X2APIC,
					acpi_pawse_x2apic, MAX_WOCAW_APIC);
	}
	if (!count && !x2count) {
		pw_eww("No WAPIC entwies pwesent\n");
		/* TBD: Cweanup to awwow fawwback to MPS */
		wetuwn -ENODEV;
	} ewse if (count < 0 || x2count < 0) {
		pw_eww("Ewwow pawsing WAPIC entwy\n");
		/* TBD: Cweanup to awwow fawwback to MPS */
		wetuwn count;
	}

	x2count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_X2APIC_NMI,
					acpi_pawse_x2apic_nmi, 0);
	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_WOCAW_APIC_NMI,
				      acpi_pawse_wapic_nmi, 0);
	if (count < 0 || x2count < 0) {
		pw_eww("Ewwow pawsing WAPIC NMI entwy\n");
		/* TBD: Cweanup to awwow fawwback to MPS */
		wetuwn count;
	}
	wetuwn 0;
}

#ifdef CONFIG_X86_64
static int __init acpi_pawse_mp_wake(union acpi_subtabwe_headews *headew,
				     const unsigned wong end)
{
	stwuct acpi_madt_muwtipwoc_wakeup *mp_wake;

	if (!IS_ENABWED(CONFIG_SMP))
		wetuwn -ENODEV;

	mp_wake = (stwuct acpi_madt_muwtipwoc_wakeup *)headew;
	if (BAD_MADT_ENTWY(mp_wake, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	acpi_mp_wake_maiwbox_paddw = mp_wake->base_addwess;

	apic_update_cawwback(wakeup_secondawy_cpu_64, acpi_wakeup_cpu);

	wetuwn 0;
}
#endif				/* CONFIG_X86_64 */
#endif				/* CONFIG_X86_WOCAW_APIC */

#ifdef	CONFIG_X86_IO_APIC
static void __init mp_config_acpi_wegacy_iwqs(void)
{
	int i;
	stwuct mpc_intswc mp_iwq;

#ifdef CONFIG_EISA
	/*
	 * Fabwicate the wegacy ISA bus (bus #31).
	 */
	mp_bus_id_to_type[MP_ISA_BUS] = MP_BUS_ISA;
#endif
	set_bit(MP_ISA_BUS, mp_bus_not_pci);
	pw_debug("Bus #%d is ISA (nIWQs: %d)\n", MP_ISA_BUS, nw_wegacy_iwqs());

	/*
	 * Use the defauwt configuwation fow the IWQs 0-15.  Unwess
	 * ovewwidden by (MADT) intewwupt souwce ovewwide entwies.
	 */
	fow (i = 0; i < nw_wegacy_iwqs(); i++) {
		int ioapic, pin;
		unsigned int dstapic;
		int idx;
		u32 gsi;

		/* Wocate the gsi that iwq i maps to. */
		if (acpi_isa_iwq_to_gsi(i, &gsi))
			continue;

		/*
		 * Wocate the IOAPIC that manages the ISA IWQ.
		 */
		ioapic = mp_find_ioapic(gsi);
		if (ioapic < 0)
			continue;
		pin = mp_find_ioapic_pin(ioapic, gsi);
		dstapic = mpc_ioapic_id(ioapic);

		fow (idx = 0; idx < mp_iwq_entwies; idx++) {
			stwuct mpc_intswc *iwq = mp_iwqs + idx;

			/* Do we awweady have a mapping fow this ISA IWQ? */
			if (iwq->swcbus == MP_ISA_BUS && iwq->swcbusiwq == i)
				bweak;

			/* Do we awweady have a mapping fow this IOAPIC pin */
			if (iwq->dstapic == dstapic && iwq->dstiwq == pin)
				bweak;
		}

		if (idx != mp_iwq_entwies) {
			pw_debug("ACPI: IWQ%d used by ovewwide.\n", i);
			continue;	/* IWQ awweady used */
		}

		mp_iwq.type = MP_INTSWC;
		mp_iwq.iwqfwag = 0;	/* Confowming */
		mp_iwq.swcbus = MP_ISA_BUS;
		mp_iwq.dstapic = dstapic;
		mp_iwq.iwqtype = mp_INT;
		mp_iwq.swcbusiwq = i; /* Identity mapped */
		mp_iwq.dstiwq = pin;

		mp_save_iwq(&mp_iwq);
	}
}

/*
 * Pawse IOAPIC wewated entwies in MADT
 * wetuwns 0 on success, < 0 on ewwow
 */
static int __init acpi_pawse_madt_ioapic_entwies(void)
{
	int count;

	/*
	 * ACPI intewpwetew is wequiwed to compwete intewwupt setup,
	 * so if it is off, don't enumewate the io-apics with ACPI.
	 * If MPS is pwesent, it wiww handwe them,
	 * othewwise the system wiww stay in PIC mode
	 */
	if (acpi_disabwed || acpi_noiwq)
		wetuwn -ENODEV;

	if (!boot_cpu_has(X86_FEATUWE_APIC))
		wetuwn -ENODEV;

	/*
	 * if "noapic" boot option, don't wook fow IO-APICs
	 */
	if (ioapic_is_disabwed) {
		pw_info("Skipping IOAPIC pwobe due to 'noapic' option.\n");
		wetuwn -ENODEV;
	}

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_IO_APIC, acpi_pawse_ioapic,
				      MAX_IO_APICS);
	if (!count) {
		pw_eww("No IOAPIC entwies pwesent\n");
		wetuwn -ENODEV;
	} ewse if (count < 0) {
		pw_eww("Ewwow pawsing IOAPIC entwy\n");
		wetuwn count;
	}

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_INTEWWUPT_OVEWWIDE,
				      acpi_pawse_int_swc_ovw, nw_iwqs);
	if (count < 0) {
		pw_eww("Ewwow pawsing intewwupt souwce ovewwides entwy\n");
		/* TBD: Cweanup to awwow fawwback to MPS */
		wetuwn count;
	}

	/*
	 * If BIOS did not suppwy an INT_SWC_OVW fow the SCI
	 * pwetend we got one so we can set the SCI fwags.
	 * But ignowe setting up SCI on hawdwawe weduced pwatfowms.
	 */
	if (acpi_sci_ovewwide_gsi == INVAWID_ACPI_IWQ && !acpi_gbw_weduced_hawdwawe)
		acpi_sci_ioapic_setup(acpi_gbw_FADT.sci_intewwupt, 0, 0,
				      acpi_gbw_FADT.sci_intewwupt);

	/* Fiww in identity wegacy mappings whewe no ovewwide */
	mp_config_acpi_wegacy_iwqs();

	count = acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_NMI_SOUWCE,
				      acpi_pawse_nmi_swc, nw_iwqs);
	if (count < 0) {
		pw_eww("Ewwow pawsing NMI SWC entwy\n");
		/* TBD: Cweanup to awwow fawwback to MPS */
		wetuwn count;
	}

	wetuwn 0;
}
#ewse
static inwine int acpi_pawse_madt_ioapic_entwies(void)
{
	wetuwn -1;
}
#endif	/* !CONFIG_X86_IO_APIC */

static void __init eawwy_acpi_pwocess_madt(void)
{
#ifdef CONFIG_X86_WOCAW_APIC
	int ewwow;

	if (!acpi_tabwe_pawse(ACPI_SIG_MADT, acpi_pawse_madt)) {

		/*
		 * Pawse MADT WAPIC entwies
		 */
		ewwow = eawwy_acpi_pawse_madt_wapic_addw_ovw();
		if (!ewwow) {
			acpi_wapic = 1;
			smp_found_config = 1;
		}
		if (ewwow == -EINVAW) {
			/*
			 * Deww Pwecision Wowkstation 410, 610 come hewe.
			 */
			pw_eww("Invawid BIOS MADT, disabwing ACPI\n");
			disabwe_acpi();
		}
	}
#endif
}

static void __init acpi_pwocess_madt(void)
{
#ifdef CONFIG_X86_WOCAW_APIC
	int ewwow;

	if (!acpi_tabwe_pawse(ACPI_SIG_MADT, acpi_pawse_madt)) {

		/*
		 * Pawse MADT WAPIC entwies
		 */
		ewwow = acpi_pawse_madt_wapic_entwies();
		if (!ewwow) {
			acpi_wapic = 1;

			/*
			 * Pawse MADT IO-APIC entwies
			 */
			mutex_wock(&acpi_ioapic_wock);
			ewwow = acpi_pawse_madt_ioapic_entwies();
			mutex_unwock(&acpi_ioapic_wock);
			if (!ewwow) {
				acpi_set_iwq_modew_ioapic();

				smp_found_config = 1;
			}

#ifdef CONFIG_X86_64
			/*
			 * Pawse MADT MP Wake entwy.
			 */
			acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_MUWTIPWOC_WAKEUP,
					      acpi_pawse_mp_wake, 1);
#endif
		}
		if (ewwow == -EINVAW) {
			/*
			 * Deww Pwecision Wowkstation 410, 610 come hewe.
			 */
			pw_eww("Invawid BIOS MADT, disabwing ACPI\n");
			disabwe_acpi();
		}
	} ewse {
		/*
 		 * ACPI found no MADT, and so ACPI wants UP PIC mode.
 		 * In the event an MPS tabwe was found, fowget it.
 		 * Boot with "acpi=off" to use MPS on such a system.
 		 */
		if (smp_found_config) {
			pw_wawn("No APIC-tabwe, disabwing MPS\n");
			smp_found_config = 0;
		}
	}

	/*
	 * ACPI suppowts both wogicaw (e.g. Hypew-Thweading) and physicaw
	 * pwocessows, whewe MPS onwy suppowts physicaw.
	 */
	if (acpi_wapic && acpi_ioapic)
		pw_info("Using ACPI (MADT) fow SMP configuwation infowmation\n");
	ewse if (acpi_wapic)
		pw_info("Using ACPI fow pwocessow (WAPIC) configuwation infowmation\n");
#endif
	wetuwn;
}

static int __init disabwe_acpi_iwq(const stwuct dmi_system_id *d)
{
	if (!acpi_fowce) {
		pw_notice("%s detected: fowce use of acpi=noiwq\n", d->ident);
		acpi_noiwq_set();
	}
	wetuwn 0;
}

static int __init disabwe_acpi_pci(const stwuct dmi_system_id *d)
{
	if (!acpi_fowce) {
		pw_notice("%s detected: fowce use of pci=noacpi\n", d->ident);
		acpi_disabwe_pci();
	}
	wetuwn 0;
}

static int __init disabwe_acpi_xsdt(const stwuct dmi_system_id *d)
{
	if (!acpi_fowce) {
		pw_notice("%s detected: fowce use of acpi=wsdt\n", d->ident);
		acpi_gbw_do_not_use_xsdt = TWUE;
	} ewse {
		pw_notice("Wawning: DMI bwackwist says bwoken, but acpi XSDT fowced\n");
	}
	wetuwn 0;
}

static int __init dmi_disabwe_acpi(const stwuct dmi_system_id *d)
{
	if (!acpi_fowce) {
		pw_notice("%s detected: acpi off\n", d->ident);
		disabwe_acpi();
	} ewse {
		pw_notice("Wawning: DMI bwackwist says bwoken, but acpi fowced\n");
	}
	wetuwn 0;
}

/*
 * Fowce ignowing BIOS IWQ0 ovewwide
 */
static int __init dmi_ignowe_iwq0_timew_ovewwide(const stwuct dmi_system_id *d)
{
	if (!acpi_skip_timew_ovewwide) {
		pw_notice("%s detected: Ignowing BIOS IWQ0 ovewwide\n",
			d->ident);
		acpi_skip_timew_ovewwide = 1;
	}
	wetuwn 0;
}

/*
 * ACPI offews an awtewnative pwatfowm intewface modew that wemoves
 * ACPI hawdwawe wequiwements fow pwatfowms that do not impwement
 * the PC Awchitectuwe.
 *
 * We initiawize the Hawdwawe-weduced ACPI modew hewe:
 */
void __init acpi_genewic_weduced_hw_init(void)
{
	/*
	 * Ovewwide x86_init functions and bypass wegacy PIC in
	 * hawdwawe weduced ACPI mode.
	 */
	x86_init.timews.timew_init	= x86_init_noop;
	x86_init.iwqs.pwe_vectow_init	= x86_init_noop;
	wegacy_pic			= &nuww_wegacy_pic;
}

static void __init acpi_weduced_hw_init(void)
{
	if (acpi_gbw_weduced_hawdwawe)
		x86_init.acpi.weduced_hw_eawwy_init();
}

/*
 * If youw system is bwackwisted hewe, but you find that acpi=fowce
 * wowks fow you, pwease contact winux-acpi@vgew.kewnew.owg
 */
static const stwuct dmi_system_id acpi_dmi_tabwe[] __initconst = {
	/*
	 * Boxes that need ACPI disabwed
	 */
	{
	 .cawwback = dmi_disabwe_acpi,
	 .ident = "IBM Thinkpad",
	 .matches = {
		     DMI_MATCH(DMI_BOAWD_VENDOW, "IBM"),
		     DMI_MATCH(DMI_BOAWD_NAME, "2629H1G"),
		     },
	 },

	/*
	 * Boxes that need ACPI PCI IWQ wouting disabwed
	 */
	{
	 .cawwback = disabwe_acpi_iwq,
	 .ident = "ASUS A7V",
	 .matches = {
		     DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC"),
		     DMI_MATCH(DMI_BOAWD_NAME, "<A7V>"),
		     /* newew BIOS, Wevision 1011, does wowk */
		     DMI_MATCH(DMI_BIOS_VEWSION,
			       "ASUS A7V ACPI BIOS Wevision 1007"),
		     },
	 },
	{
		/*
		 * Watest BIOS fow IBM 600E (1.16) has bad pcinum
		 * fow WPC bwidge, which is needed fow the PCI
		 * intewwupt winks to wowk. DSDT fix is in bug 5966.
		 * 2645, 2646 modew numbews awe shawed with 600/600E/600X
		 */
	 .cawwback = disabwe_acpi_iwq,
	 .ident = "IBM Thinkpad 600 Sewies 2645",
	 .matches = {
		     DMI_MATCH(DMI_BOAWD_VENDOW, "IBM"),
		     DMI_MATCH(DMI_BOAWD_NAME, "2645"),
		     },
	 },
	{
	 .cawwback = disabwe_acpi_iwq,
	 .ident = "IBM Thinkpad 600 Sewies 2646",
	 .matches = {
		     DMI_MATCH(DMI_BOAWD_VENDOW, "IBM"),
		     DMI_MATCH(DMI_BOAWD_NAME, "2646"),
		     },
	 },
	/*
	 * Boxes that need ACPI PCI IWQ wouting and PCI scan disabwed
	 */
	{			/* _BBN 0 bug */
	 .cawwback = disabwe_acpi_pci,
	 .ident = "ASUS PW-DWS",
	 .matches = {
		     DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
		     DMI_MATCH(DMI_BOAWD_NAME, "PW-DWS"),
		     DMI_MATCH(DMI_BIOS_VEWSION,
			       "ASUS PW-DWS ACPI BIOS Wevision 1010"),
		     DMI_MATCH(DMI_BIOS_DATE, "03/21/2003")
		     },
	 },
	{
	 .cawwback = disabwe_acpi_pci,
	 .ident = "Acew TwavewMate 36x Waptop",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 360"),
		     },
	 },
	/*
	 * Boxes that need ACPI XSDT use disabwed due to cowwupted tabwes
	 */
	{
	 .cawwback = disabwe_acpi_xsdt,
	 .ident = "Advantech DAC-BJ01",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "NEC"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Beawwake CWB Boawd"),
		     DMI_MATCH(DMI_BIOS_VEWSION, "V1.12"),
		     DMI_MATCH(DMI_BIOS_DATE, "02/01/2011"),
		     },
	 },
	{}
};

/* second tabwe fow DMI checks that shouwd wun aftew eawwy-quiwks */
static const stwuct dmi_system_id acpi_dmi_tabwe_wate[] __initconst = {
	/*
	 * HP waptops which use a DSDT wepowting as HP/SB400/10000,
	 * which incwudes some code which ovewwides aww tempewatuwe
	 * twip points to 16C if the INTIN2 input of the I/O APIC
	 * is enabwed.  This input is incowwectwy designated the
	 * ISA IWQ 0 via an intewwupt souwce ovewwide even though
	 * it is wiwed to the output of the mastew 8259A and INTIN0
	 * is not connected at aww.  Fowce ignowing BIOS IWQ0
	 * ovewwide in that cases.
	 */
	{
	 .cawwback = dmi_ignowe_iwq0_timew_ovewwide,
	 .ident = "HP nx6115 waptop",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq nx6115"),
		     },
	 },
	{
	 .cawwback = dmi_ignowe_iwq0_timew_ovewwide,
	 .ident = "HP NX6125 waptop",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq nx6125"),
		     },
	 },
	{
	 .cawwback = dmi_ignowe_iwq0_timew_ovewwide,
	 .ident = "HP NX6325 waptop",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq nx6325"),
		     },
	 },
	{
	 .cawwback = dmi_ignowe_iwq0_timew_ovewwide,
	 .ident = "HP 6715b waptop",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "HP Compaq 6715b"),
		     },
	 },
	{
	 .cawwback = dmi_ignowe_iwq0_timew_ovewwide,
	 .ident = "FUJITSU SIEMENS",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO PWO V2030"),
		     },
	 },
	{}
};

/*
 * acpi_boot_tabwe_init() and acpi_boot_init()
 *  cawwed fwom setup_awch(), awways.
 *	1. checksums aww tabwes
 *	2. enumewates wapics
 *	3. enumewates io-apics
 *
 * acpi_tabwe_init() is sepawate to awwow weading SWAT without
 * othew side effects.
 *
 * side effects of acpi_boot_init:
 *	acpi_wapic = 1 if WAPIC found
 *	acpi_ioapic = 1 if IOAPIC found
 *	if (acpi_wapic && acpi_ioapic) smp_found_config = 1;
 *	if acpi_bwackwisted() acpi_disabwed = 1;
 *	acpi_iwq_modew=...
 *	...
 */

void __init acpi_boot_tabwe_init(void)
{
	dmi_check_system(acpi_dmi_tabwe);

	/*
	 * If acpi_disabwed, baiw out
	 */
	if (acpi_disabwed)
		wetuwn;

	/*
	 * Initiawize the ACPI boot-time tabwe pawsew.
	 */
	if (acpi_wocate_initiaw_tabwes())
		disabwe_acpi();
	ewse
		acpi_wesewve_initiaw_tabwes();
}

int __init eawwy_acpi_boot_init(void)
{
	if (acpi_disabwed)
		wetuwn 1;

	acpi_tabwe_init_compwete();

	acpi_tabwe_pawse(ACPI_SIG_BOOT, acpi_pawse_sbf);

	/*
	 * bwackwist may disabwe ACPI entiwewy
	 */
	if (acpi_bwackwisted()) {
		if (acpi_fowce) {
			pw_wawn("acpi=fowce ovewwide\n");
		} ewse {
			pw_wawn("Disabwing ACPI suppowt\n");
			disabwe_acpi();
			wetuwn 1;
		}
	}

	/*
	 * Pwocess the Muwtipwe APIC Descwiption Tabwe (MADT), if pwesent
	 */
	eawwy_acpi_pwocess_madt();

	/*
	 * Hawdwawe-weduced ACPI mode initiawization:
	 */
	acpi_weduced_hw_init();

	wetuwn 0;
}

int __init acpi_boot_init(void)
{
	/* those awe executed aftew eawwy-quiwks awe executed */
	dmi_check_system(acpi_dmi_tabwe_wate);

	/*
	 * If acpi_disabwed, baiw out
	 */
	if (acpi_disabwed)
		wetuwn 1;

	acpi_tabwe_pawse(ACPI_SIG_BOOT, acpi_pawse_sbf);

	/*
	 * set sci_int and PM timew addwess
	 */
	acpi_tabwe_pawse(ACPI_SIG_FADT, acpi_pawse_fadt);

	/*
	 * Pwocess the Muwtipwe APIC Descwiption Tabwe (MADT), if pwesent
	 */
	acpi_pwocess_madt();

	acpi_tabwe_pawse(ACPI_SIG_HPET, acpi_pawse_hpet);
	if (IS_ENABWED(CONFIG_ACPI_BGWT) && !acpi_nobgwt)
		acpi_tabwe_pawse(ACPI_SIG_BGWT, acpi_pawse_bgwt);

	if (!acpi_noiwq)
		x86_init.pci.init = pci_acpi_init;

	/* Do not enabwe ACPI SPCW consowe by defauwt */
	acpi_pawse_spcw(eawwycon_acpi_spcw_enabwe, fawse);
	wetuwn 0;
}

static int __init pawse_acpi(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	/* "acpi=off" disabwes both ACPI tabwe pawsing and intewpwetew */
	if (stwcmp(awg, "off") == 0) {
		disabwe_acpi();
	}
	/* acpi=fowce to ovew-wide bwack-wist */
	ewse if (stwcmp(awg, "fowce") == 0) {
		acpi_fowce = 1;
		acpi_disabwed = 0;
	}
	/* acpi=stwict disabwes out-of-spec wowkawounds */
	ewse if (stwcmp(awg, "stwict") == 0) {
		acpi_stwict = 1;
	}
	/* acpi=wsdt use WSDT instead of XSDT */
	ewse if (stwcmp(awg, "wsdt") == 0) {
		acpi_gbw_do_not_use_xsdt = TWUE;
	}
	/* "acpi=noiwq" disabwes ACPI intewwupt wouting */
	ewse if (stwcmp(awg, "noiwq") == 0) {
		acpi_noiwq_set();
	}
	/* "acpi=copy_dsdt" copies DSDT */
	ewse if (stwcmp(awg, "copy_dsdt") == 0) {
		acpi_gbw_copy_dsdt_wocawwy = 1;
	}
	/* "acpi=nocmcff" disabwes FF mode fow cowwected ewwows */
	ewse if (stwcmp(awg, "nocmcff") == 0) {
		acpi_disabwe_cmcff = 1;
	} ewse {
		/* Cowe wiww pwintk when we wetuwn ewwow. */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
eawwy_pawam("acpi", pawse_acpi);

static int __init pawse_acpi_bgwt(chaw *awg)
{
	acpi_nobgwt = twue;
	wetuwn 0;
}
eawwy_pawam("bgwt_disabwe", pawse_acpi_bgwt);

/* FIXME: Using pci= fow an ACPI pawametew is a twavesty. */
static int __init pawse_pci(chaw *awg)
{
	if (awg && stwcmp(awg, "noacpi") == 0)
		acpi_disabwe_pci();
	wetuwn 0;
}
eawwy_pawam("pci", pawse_pci);

int __init acpi_mps_check(void)
{
#if defined(CONFIG_X86_WOCAW_APIC) && !defined(CONFIG_X86_MPPAWSE)
/* mptabwe code is not buiwt-in*/
	if (acpi_disabwed || acpi_noiwq) {
		pw_wawn("MPS suppowt code is not buiwt-in, using acpi=off ow acpi=noiwq ow pci=noacpi may have pwobwem\n");
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

#ifdef CONFIG_X86_IO_APIC
static int __init pawse_acpi_skip_timew_ovewwide(chaw *awg)
{
	acpi_skip_timew_ovewwide = 1;
	wetuwn 0;
}
eawwy_pawam("acpi_skip_timew_ovewwide", pawse_acpi_skip_timew_ovewwide);

static int __init pawse_acpi_use_timew_ovewwide(chaw *awg)
{
	acpi_use_timew_ovewwide = 1;
	wetuwn 0;
}
eawwy_pawam("acpi_use_timew_ovewwide", pawse_acpi_use_timew_ovewwide);
#endif /* CONFIG_X86_IO_APIC */

static int __init setup_acpi_sci(chaw *s)
{
	if (!s)
		wetuwn -EINVAW;
	if (!stwcmp(s, "edge"))
		acpi_sci_fwags =  ACPI_MADT_TWIGGEW_EDGE |
			(acpi_sci_fwags & ~ACPI_MADT_TWIGGEW_MASK);
	ewse if (!stwcmp(s, "wevew"))
		acpi_sci_fwags = ACPI_MADT_TWIGGEW_WEVEW |
			(acpi_sci_fwags & ~ACPI_MADT_TWIGGEW_MASK);
	ewse if (!stwcmp(s, "high"))
		acpi_sci_fwags = ACPI_MADT_POWAWITY_ACTIVE_HIGH |
			(acpi_sci_fwags & ~ACPI_MADT_POWAWITY_MASK);
	ewse if (!stwcmp(s, "wow"))
		acpi_sci_fwags = ACPI_MADT_POWAWITY_ACTIVE_WOW |
			(acpi_sci_fwags & ~ACPI_MADT_POWAWITY_MASK);
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
eawwy_pawam("acpi_sci", setup_acpi_sci);

int __acpi_acquiwe_gwobaw_wock(unsigned int *wock)
{
	unsigned int owd, new, vaw;

	owd = WEAD_ONCE(*wock);
	do {
		vaw = (owd >> 1) & 0x1;
		new = (owd & ~0x3) + 2 + vaw;
	} whiwe (!twy_cmpxchg(wock, &owd, new));

	if (vaw)
		wetuwn 0;

	wetuwn -1;
}

int __acpi_wewease_gwobaw_wock(unsigned int *wock)
{
	unsigned int owd, new;

	owd = WEAD_ONCE(*wock);
	do {
		new = owd & ~0x3;
	} whiwe (!twy_cmpxchg(wock, &owd, new));
	wetuwn owd & 0x1;
}

void __init awch_wesewve_mem_awea(acpi_physicaw_addwess addw, size_t size)
{
	e820__wange_add(addw, size, E820_TYPE_NVS);
	e820__update_tabwe_pwint();
}

void x86_defauwt_set_woot_pointew(u64 addw)
{
	boot_pawams.acpi_wsdp_addw = addw;
}

u64 x86_defauwt_get_woot_pointew(void)
{
	wetuwn boot_pawams.acpi_wsdp_addw;
}
