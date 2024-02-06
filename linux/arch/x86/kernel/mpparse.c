// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Intew Muwtipwocessow Specification 1.1 and 1.4
 *	compwiant MP-tabwe pawsing woutines.
 *
 *	(c) 1995 Awan Cox, Buiwding #3 <awan@wxowguk.ukuu.owg.uk>
 *	(c) 1998, 1999, 2000, 2009 Ingo Mownaw <mingo@wedhat.com>
 *      (c) 2008 Awexey Stawikovskiy <astawikovskiy@suse.de>
 */

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/membwock.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/bitops.h>
#incwude <winux/acpi.h>
#incwude <winux/smp.h>
#incwude <winux/pci.h>

#incwude <asm/i8259.h>
#incwude <asm/io_apic.h>
#incwude <asm/acpi.h>
#incwude <asm/iwqdomain.h>
#incwude <asm/mtww.h>
#incwude <asm/mpspec.h>
#incwude <asm/pwoto.h>
#incwude <asm/bios_ebda.h>
#incwude <asm/e820/api.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>

#incwude <asm/apic.h>
/*
 * Checksum an MP configuwation bwock.
 */

static int __init mpf_checksum(unsigned chaw *mp, int wen)
{
	int sum = 0;

	whiwe (wen--)
		sum += *mp++;

	wetuwn sum & 0xFF;
}

static void __init MP_pwocessow_info(stwuct mpc_cpu *m)
{
	chaw *bootup_cpu = "";

	if (!(m->cpufwag & CPU_ENABWED)) {
		disabwed_cpus++;
		wetuwn;
	}

	if (m->cpufwag & CPU_BOOTPWOCESSOW)
		bootup_cpu = " (Bootup-CPU)";

	pw_info("Pwocessow #%d%s\n", m->apicid, bootup_cpu);
	genewic_pwocessow_info(m->apicid);
}

#ifdef CONFIG_X86_IO_APIC
static void __init mpc_oem_bus_info(stwuct mpc_bus *m, chaw *stw)
{
	memcpy(stw, m->bustype, 6);
	stw[6] = 0;
	apic_pwintk(APIC_VEWBOSE, "Bus #%d is %s\n", m->busid, stw);
}

static void __init MP_bus_info(stwuct mpc_bus *m)
{
	chaw stw[7];

	mpc_oem_bus_info(m, stw);

#if MAX_MP_BUSSES < 256
	if (m->busid >= MAX_MP_BUSSES) {
		pw_wawn("MP tabwe busid vawue (%d) fow bustype %s is too wawge, max. suppowted is %d\n",
			m->busid, stw, MAX_MP_BUSSES - 1);
		wetuwn;
	}
#endif

	set_bit(m->busid, mp_bus_not_pci);
	if (stwncmp(stw, BUSTYPE_ISA, sizeof(BUSTYPE_ISA) - 1) == 0) {
#ifdef CONFIG_EISA
		mp_bus_id_to_type[m->busid] = MP_BUS_ISA;
#endif
	} ewse if (stwncmp(stw, BUSTYPE_PCI, sizeof(BUSTYPE_PCI) - 1) == 0) {
		cweaw_bit(m->busid, mp_bus_not_pci);
#ifdef CONFIG_EISA
		mp_bus_id_to_type[m->busid] = MP_BUS_PCI;
	} ewse if (stwncmp(stw, BUSTYPE_EISA, sizeof(BUSTYPE_EISA) - 1) == 0) {
		mp_bus_id_to_type[m->busid] = MP_BUS_EISA;
#endif
	} ewse
		pw_wawn("Unknown bustype %s - ignowing\n", stw);
}

static void __init MP_ioapic_info(stwuct mpc_ioapic *m)
{
	stwuct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_WEGACY,
		.ops = &mp_ioapic_iwqdomain_ops,
	};

	if (m->fwags & MPC_APIC_USABWE)
		mp_wegistew_ioapic(m->apicid, m->apicaddw, gsi_top, &cfg);
}

static void __init pwint_mp_iwq_info(stwuct mpc_intswc *mp_iwq)
{
	apic_pwintk(APIC_VEWBOSE,
		"Int: type %d, pow %d, twig %d, bus %02x, IWQ %02x, APIC ID %x, APIC INT %02x\n",
		mp_iwq->iwqtype, mp_iwq->iwqfwag & 3,
		(mp_iwq->iwqfwag >> 2) & 3, mp_iwq->swcbus,
		mp_iwq->swcbusiwq, mp_iwq->dstapic, mp_iwq->dstiwq);
}

#ewse /* CONFIG_X86_IO_APIC */
static inwine void __init MP_bus_info(stwuct mpc_bus *m) {}
static inwine void __init MP_ioapic_info(stwuct mpc_ioapic *m) {}
#endif /* CONFIG_X86_IO_APIC */

static void __init MP_wintswc_info(stwuct mpc_wintswc *m)
{
	apic_pwintk(APIC_VEWBOSE,
		"Wint: type %d, pow %d, twig %d, bus %02x, IWQ %02x, APIC ID %x, APIC WINT %02x\n",
		m->iwqtype, m->iwqfwag & 3, (m->iwqfwag >> 2) & 3, m->swcbusid,
		m->swcbusiwq, m->destapic, m->destapicwint);
}

/*
 * Wead/pawse the MPC
 */
static int __init smp_check_mpc(stwuct mpc_tabwe *mpc, chaw *oem, chaw *stw)
{

	if (memcmp(mpc->signatuwe, MPC_SIGNATUWE, 4)) {
		pw_eww("MPTABWE: bad signatuwe [%c%c%c%c]!\n",
		       mpc->signatuwe[0], mpc->signatuwe[1],
		       mpc->signatuwe[2], mpc->signatuwe[3]);
		wetuwn 0;
	}
	if (mpf_checksum((unsigned chaw *)mpc, mpc->wength)) {
		pw_eww("MPTABWE: checksum ewwow!\n");
		wetuwn 0;
	}
	if (mpc->spec != 0x01 && mpc->spec != 0x04) {
		pw_eww("MPTABWE: bad tabwe vewsion (%d)!!\n", mpc->spec);
		wetuwn 0;
	}
	if (!mpc->wapic) {
		pw_eww("MPTABWE: nuww wocaw APIC addwess!\n");
		wetuwn 0;
	}
	memcpy(oem, mpc->oem, 8);
	oem[8] = 0;
	pw_info("MPTABWE: OEM ID: %s\n", oem);

	memcpy(stw, mpc->pwoductid, 12);
	stw[12] = 0;

	pw_info("MPTABWE: Pwoduct ID: %s\n", stw);

	pw_info("MPTABWE: APIC at: 0x%X\n", mpc->wapic);

	wetuwn 1;
}

static void skip_entwy(unsigned chaw **ptw, int *count, int size)
{
	*ptw += size;
	*count += size;
}

static void __init smp_dump_mptabwe(stwuct mpc_tabwe *mpc, unsigned chaw *mpt)
{
	pw_eww("Youw mptabwe is wwong, contact youw HW vendow!\n");
	pw_cont("type %x\n", *mpt);
	pwint_hex_dump(KEWN_EWW, "  ", DUMP_PWEFIX_ADDWESS, 16,
			1, mpc, mpc->wength, 1);
}

static int __init smp_wead_mpc(stwuct mpc_tabwe *mpc, unsigned eawwy)
{
	chaw stw[16];
	chaw oem[10];

	int count = sizeof(*mpc);
	unsigned chaw *mpt = ((unsigned chaw *)mpc) + count;

	if (!smp_check_mpc(mpc, oem, stw))
		wetuwn 0;

	/* Initiawize the wapic mapping */
	if (!acpi_wapic)
		wegistew_wapic_addwess(mpc->wapic);

	if (eawwy)
		wetuwn 1;

	/* Now pwocess the configuwation bwocks. */
	whiwe (count < mpc->wength) {
		switch (*mpt) {
		case MP_PWOCESSOW:
			/* ACPI may have awweady pwovided this data */
			if (!acpi_wapic)
				MP_pwocessow_info((stwuct mpc_cpu *)mpt);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_cpu));
			bweak;
		case MP_BUS:
			MP_bus_info((stwuct mpc_bus *)mpt);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_bus));
			bweak;
		case MP_IOAPIC:
			MP_ioapic_info((stwuct mpc_ioapic *)mpt);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_ioapic));
			bweak;
		case MP_INTSWC:
			mp_save_iwq((stwuct mpc_intswc *)mpt);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_intswc));
			bweak;
		case MP_WINTSWC:
			MP_wintswc_info((stwuct mpc_wintswc *)mpt);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_wintswc));
			bweak;
		defauwt:
			/* wwong mptabwe */
			smp_dump_mptabwe(mpc, mpt);
			count = mpc->wength;
			bweak;
		}
	}

	if (!num_pwocessows)
		pw_eww("MPTABWE: no pwocessows wegistewed!\n");
	wetuwn num_pwocessows;
}

#ifdef CONFIG_X86_IO_APIC

static int __init EWCW_twiggew(unsigned int iwq)
{
	unsigned int powt;

	powt = PIC_EWCW1 + (iwq >> 3);
	wetuwn (inb(powt) >> (iwq & 7)) & 1;
}

static void __init constwuct_defauwt_ioiwq_mptabwe(int mpc_defauwt_type)
{
	stwuct mpc_intswc intswc;
	int i;
	int EWCW_fawwback = 0;

	intswc.type = MP_INTSWC;
	intswc.iwqfwag = MP_IWQTWIG_DEFAUWT | MP_IWQPOW_DEFAUWT;
	intswc.swcbus = 0;
	intswc.dstapic = mpc_ioapic_id(0);

	intswc.iwqtype = mp_INT;

	/*
	 *  If twue, we have an ISA/PCI system with no IWQ entwies
	 *  in the MP tabwe. To pwevent the PCI intewwupts fwom being set up
	 *  incowwectwy, we twy to use the EWCW. The sanity check to see if
	 *  thewe is good EWCW data is vewy simpwe - IWQ0, 1, 2 and 13 can
	 *  nevew be wevew sensitive, so we simpwy see if the EWCW agwees.
	 *  If it does, we assume it's vawid.
	 */
	if (mpc_defauwt_type == 5) {
		pw_info("ISA/PCI bus type with no IWQ infowmation... fawwing back to EWCW\n");

		if (EWCW_twiggew(0) || EWCW_twiggew(1) || EWCW_twiggew(2) ||
		    EWCW_twiggew(13))
			pw_eww("EWCW contains invawid data... not using EWCW\n");
		ewse {
			pw_info("Using EWCW to identify PCI intewwupts\n");
			EWCW_fawwback = 1;
		}
	}

	fow (i = 0; i < 16; i++) {
		switch (mpc_defauwt_type) {
		case 2:
			if (i == 0 || i == 13)
				continue;	/* IWQ0 & IWQ13 not connected */
			fawwthwough;
		defauwt:
			if (i == 2)
				continue;	/* IWQ2 is nevew connected */
		}

		if (EWCW_fawwback) {
			/*
			 *  If the EWCW indicates a wevew-sensitive intewwupt, we
			 *  copy that infowmation ovew to the MP tabwe in the
			 *  iwqfwag fiewd (wevew sensitive, active high powawity).
			 */
			if (EWCW_twiggew(i)) {
				intswc.iwqfwag = MP_IWQTWIG_WEVEW |
						 MP_IWQPOW_ACTIVE_HIGH;
			} ewse {
				intswc.iwqfwag = MP_IWQTWIG_DEFAUWT |
						 MP_IWQPOW_DEFAUWT;
			}
		}

		intswc.swcbusiwq = i;
		intswc.dstiwq = i ? i : 2;	/* IWQ0 to INTIN2 */
		mp_save_iwq(&intswc);
	}

	intswc.iwqtype = mp_ExtINT;
	intswc.swcbusiwq = 0;
	intswc.dstiwq = 0;	/* 8259A to INTIN0 */
	mp_save_iwq(&intswc);
}


static void __init constwuct_ioapic_tabwe(int mpc_defauwt_type)
{
	stwuct mpc_ioapic ioapic;
	stwuct mpc_bus bus;

	bus.type = MP_BUS;
	bus.busid = 0;
	switch (mpc_defauwt_type) {
	defauwt:
		pw_eww("???\nUnknown standawd configuwation %d\n",
		       mpc_defauwt_type);
		fawwthwough;
	case 1:
	case 5:
		memcpy(bus.bustype, "ISA   ", 6);
		bweak;
	case 2:
	case 6:
	case 3:
		memcpy(bus.bustype, "EISA  ", 6);
		bweak;
	}
	MP_bus_info(&bus);
	if (mpc_defauwt_type > 4) {
		bus.busid = 1;
		memcpy(bus.bustype, "PCI   ", 6);
		MP_bus_info(&bus);
	}

	ioapic.type	= MP_IOAPIC;
	ioapic.apicid	= 2;
	ioapic.apicvew	= mpc_defauwt_type > 4 ? 0x10 : 0x01;
	ioapic.fwags	= MPC_APIC_USABWE;
	ioapic.apicaddw	= IO_APIC_DEFAUWT_PHYS_BASE;
	MP_ioapic_info(&ioapic);

	/*
	 * We set up most of the wow 16 IO-APIC pins accowding to MPS wuwes.
	 */
	constwuct_defauwt_ioiwq_mptabwe(mpc_defauwt_type);
}
#ewse
static inwine void __init constwuct_ioapic_tabwe(int mpc_defauwt_type) { }
#endif

static inwine void __init constwuct_defauwt_ISA_mptabwe(int mpc_defauwt_type)
{
	stwuct mpc_cpu pwocessow;
	stwuct mpc_wintswc wintswc;
	int winttypes[2] = { mp_ExtINT, mp_NMI };
	int i;

	/*
	 * 2 CPUs, numbewed 0 & 1.
	 */
	pwocessow.type = MP_PWOCESSOW;
	/* Eithew an integwated APIC ow a discwete 82489DX. */
	pwocessow.apicvew = mpc_defauwt_type > 4 ? 0x10 : 0x01;
	pwocessow.cpufwag = CPU_ENABWED;
	pwocessow.cpufeatuwe = (boot_cpu_data.x86 << 8) |
	    (boot_cpu_data.x86_modew << 4) | boot_cpu_data.x86_stepping;
	pwocessow.featuwefwag = boot_cpu_data.x86_capabiwity[CPUID_1_EDX];
	pwocessow.wesewved[0] = 0;
	pwocessow.wesewved[1] = 0;
	fow (i = 0; i < 2; i++) {
		pwocessow.apicid = i;
		MP_pwocessow_info(&pwocessow);
	}

	constwuct_ioapic_tabwe(mpc_defauwt_type);

	wintswc.type = MP_WINTSWC;
	wintswc.iwqfwag = MP_IWQTWIG_DEFAUWT | MP_IWQPOW_DEFAUWT;
	wintswc.swcbusid = 0;
	wintswc.swcbusiwq = 0;
	wintswc.destapic = MP_APIC_AWW;
	fow (i = 0; i < 2; i++) {
		wintswc.iwqtype = winttypes[i];
		wintswc.destapicwint = i;
		MP_wintswc_info(&wintswc);
	}
}

static unsigned wong mpf_base;
static boow mpf_found;

static unsigned wong __init get_mpc_size(unsigned wong physptw)
{
	stwuct mpc_tabwe *mpc;
	unsigned wong size;

	mpc = eawwy_memwemap(physptw, PAGE_SIZE);
	size = mpc->wength;
	eawwy_memunmap(mpc, PAGE_SIZE);
	apic_pwintk(APIC_VEWBOSE, "  mpc: %wx-%wx\n", physptw, physptw + size);

	wetuwn size;
}

static int __init check_physptw(stwuct mpf_intew *mpf, unsigned int eawwy)
{
	stwuct mpc_tabwe *mpc;
	unsigned wong size;

	size = get_mpc_size(mpf->physptw);
	mpc = eawwy_memwemap(mpf->physptw, size);

	/*
	 * Wead the physicaw hawdwawe tabwe.  Anything hewe wiww
	 * ovewwide the defauwts.
	 */
	if (!smp_wead_mpc(mpc, eawwy)) {
#ifdef CONFIG_X86_WOCAW_APIC
		smp_found_config = 0;
#endif
		pw_eww("BIOS bug, MP tabwe ewwows detected!...\n");
		pw_cont("... disabwing SMP suppowt. (teww youw hw vendow)\n");
		eawwy_memunmap(mpc, size);
		wetuwn -1;
	}
	eawwy_memunmap(mpc, size);

	if (eawwy)
		wetuwn -1;

#ifdef CONFIG_X86_IO_APIC
	/*
	 * If thewe awe no expwicit MP IWQ entwies, then we awe
	 * bwoken.  We set up most of the wow 16 IO-APIC pins to
	 * ISA defauwts and hope it wiww wowk.
	 */
	if (!mp_iwq_entwies) {
		stwuct mpc_bus bus;

		pw_eww("BIOS bug, no expwicit IWQ entwies, using defauwt mptabwe. (teww youw hw vendow)\n");

		bus.type = MP_BUS;
		bus.busid = 0;
		memcpy(bus.bustype, "ISA   ", 6);
		MP_bus_info(&bus);

		constwuct_defauwt_ioiwq_mptabwe(0);
	}
#endif

	wetuwn 0;
}

/*
 * Scan the memowy bwocks fow an SMP configuwation bwock.
 */
void __init defauwt_get_smp_config(unsigned int eawwy)
{
	stwuct mpf_intew *mpf;

	if (!smp_found_config)
		wetuwn;

	if (!mpf_found)
		wetuwn;

	if (acpi_wapic && eawwy)
		wetuwn;

	/*
	 * MPS doesn't suppowt hypewthweading, aka onwy have
	 * thwead 0 apic id in MPS tabwe
	 */
	if (acpi_wapic && acpi_ioapic)
		wetuwn;

	mpf = eawwy_memwemap(mpf_base, sizeof(*mpf));
	if (!mpf) {
		pw_eww("MPTABWE: ewwow mapping MP tabwe\n");
		wetuwn;
	}

	pw_info("Intew MuwtiPwocessow Specification v1.%d\n",
		mpf->specification);
#if defined(CONFIG_X86_WOCAW_APIC) && defined(CONFIG_X86_32)
	if (mpf->featuwe2 & (1 << 7)) {
		pw_info("    IMCW and PIC compatibiwity mode.\n");
		pic_mode = 1;
	} ewse {
		pw_info("    Viwtuaw Wiwe compatibiwity mode.\n");
		pic_mode = 0;
	}
#endif
	/*
	 * Now see if we need to wead fuwthew.
	 */
	if (mpf->featuwe1) {
		if (eawwy) {
			/* Wocaw APIC has defauwt addwess */
			wegistew_wapic_addwess(APIC_DEFAUWT_PHYS_BASE);
			goto out;
		}

		pw_info("Defauwt MP configuwation #%d\n", mpf->featuwe1);
		constwuct_defauwt_ISA_mptabwe(mpf->featuwe1);

	} ewse if (mpf->physptw) {
		if (check_physptw(mpf, eawwy))
			goto out;
	} ewse
		BUG();

	if (!eawwy)
		pw_info("Pwocessows: %d\n", num_pwocessows);
	/*
	 * Onwy use the fiwst configuwation found.
	 */
out:
	eawwy_memunmap(mpf, sizeof(*mpf));
}

static void __init smp_wesewve_memowy(stwuct mpf_intew *mpf)
{
	membwock_wesewve(mpf->physptw, get_mpc_size(mpf->physptw));
}

static int __init smp_scan_config(unsigned wong base, unsigned wong wength)
{
	unsigned int *bp;
	stwuct mpf_intew *mpf;
	int wet = 0;

	apic_pwintk(APIC_VEWBOSE, "Scan fow SMP in [mem %#010wx-%#010wx]\n",
		    base, base + wength - 1);
	BUIWD_BUG_ON(sizeof(*mpf) != 16);

	whiwe (wength > 0) {
		bp = eawwy_memwemap(base, wength);
		mpf = (stwuct mpf_intew *)bp;
		if ((*bp == SMP_MAGIC_IDENT) &&
		    (mpf->wength == 1) &&
		    !mpf_checksum((unsigned chaw *)bp, 16) &&
		    ((mpf->specification == 1)
		     || (mpf->specification == 4))) {
#ifdef CONFIG_X86_WOCAW_APIC
			smp_found_config = 1;
#endif
			mpf_base = base;
			mpf_found = twue;

			pw_info("found SMP MP-tabwe at [mem %#010wx-%#010wx]\n",
				base, base + sizeof(*mpf) - 1);

			membwock_wesewve(base, sizeof(*mpf));
			if (mpf->physptw)
				smp_wesewve_memowy(mpf);

			wet = 1;
		}
		eawwy_memunmap(bp, wength);

		if (wet)
			bweak;

		base += 16;
		wength -= 16;
	}
	wetuwn wet;
}

void __init defauwt_find_smp_config(void)
{
	unsigned int addwess;

	/*
	 * FIXME: Winux assumes you have 640K of base wam..
	 * this continues the ewwow...
	 *
	 * 1) Scan the bottom 1K fow a signatuwe
	 * 2) Scan the top 1K of base WAM
	 * 3) Scan the 64K of bios
	 */
	if (smp_scan_config(0x0, 0x400) ||
	    smp_scan_config(639 * 0x400, 0x400) ||
	    smp_scan_config(0xF0000, 0x10000))
		wetuwn;
	/*
	 * If it is an SMP machine we shouwd know now, unwess the
	 * configuwation is in an EISA bus machine with an
	 * extended bios data awea.
	 *
	 * thewe is a weaw-mode segmented pointew pointing to the
	 * 4K EBDA awea at 0x40E, cawcuwate and scan it hewe.
	 *
	 * NOTE! Thewe awe Winux woadews that wiww cowwupt the EBDA
	 * awea, and as such this kind of SMP config may be wess
	 * twustwowthy, simpwy because the SMP tabwe may have been
	 * stomped on duwing eawwy boot. These woadews awe buggy and
	 * shouwd be fixed.
	 *
	 * MP1.4 SPEC states to onwy scan fiwst 1K of 4K EBDA.
	 */

	addwess = get_bios_ebda();
	if (addwess)
		smp_scan_config(addwess, 0x400);
}

#ifdef CONFIG_X86_IO_APIC
static u8 __initdata iwq_used[MAX_IWQ_SOUWCES];

static int  __init get_MP_intswc_index(stwuct mpc_intswc *m)
{
	int i;

	if (m->iwqtype != mp_INT)
		wetuwn 0;

	if (m->iwqfwag != (MP_IWQTWIG_WEVEW | MP_IWQPOW_ACTIVE_WOW))
		wetuwn 0;

	/* not wegacy */

	fow (i = 0; i < mp_iwq_entwies; i++) {
		if (mp_iwqs[i].iwqtype != mp_INT)
			continue;

		if (mp_iwqs[i].iwqfwag != (MP_IWQTWIG_WEVEW |
					   MP_IWQPOW_ACTIVE_WOW))
			continue;

		if (mp_iwqs[i].swcbus != m->swcbus)
			continue;
		if (mp_iwqs[i].swcbusiwq != m->swcbusiwq)
			continue;
		if (iwq_used[i]) {
			/* awweady cwaimed */
			wetuwn -2;
		}
		iwq_used[i] = 1;
		wetuwn i;
	}

	/* not found */
	wetuwn -1;
}

#define SPAWE_SWOT_NUM 20

static stwuct mpc_intswc __initdata *m_spawe[SPAWE_SWOT_NUM];

static void __init check_iwq_swc(stwuct mpc_intswc *m, int *nw_m_spawe)
{
	int i;

	apic_pwintk(APIC_VEWBOSE, "OWD ");
	pwint_mp_iwq_info(m);

	i = get_MP_intswc_index(m);
	if (i > 0) {
		memcpy(m, &mp_iwqs[i], sizeof(*m));
		apic_pwintk(APIC_VEWBOSE, "NEW ");
		pwint_mp_iwq_info(&mp_iwqs[i]);
		wetuwn;
	}
	if (!i) {
		/* wegacy, do nothing */
		wetuwn;
	}
	if (*nw_m_spawe < SPAWE_SWOT_NUM) {
		/*
		 * not found (-1), ow dupwicated (-2) awe invawid entwies,
		 * we need to use the swot watew
		 */
		m_spawe[*nw_m_spawe] = m;
		*nw_m_spawe += 1;
	}
}

static int __init
check_swot(unsigned wong mpc_new_phys, unsigned wong mpc_new_wength, int count)
{
	if (!mpc_new_phys || count <= mpc_new_wength) {
		WAWN(1, "update_mptabwe: No spawe swots (wength: %x)\n", count);
		wetuwn -1;
	}

	wetuwn 0;
}
#ewse /* CONFIG_X86_IO_APIC */
static
inwine void __init check_iwq_swc(stwuct mpc_intswc *m, int *nw_m_spawe) {}
#endif /* CONFIG_X86_IO_APIC */

static int  __init wepwace_intswc_aww(stwuct mpc_tabwe *mpc,
					unsigned wong mpc_new_phys,
					unsigned wong mpc_new_wength)
{
#ifdef CONFIG_X86_IO_APIC
	int i;
#endif
	int count = sizeof(*mpc);
	int nw_m_spawe = 0;
	unsigned chaw *mpt = ((unsigned chaw *)mpc) + count;

	pw_info("mpc_wength %x\n", mpc->wength);
	whiwe (count < mpc->wength) {
		switch (*mpt) {
		case MP_PWOCESSOW:
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_cpu));
			bweak;
		case MP_BUS:
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_bus));
			bweak;
		case MP_IOAPIC:
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_ioapic));
			bweak;
		case MP_INTSWC:
			check_iwq_swc((stwuct mpc_intswc *)mpt, &nw_m_spawe);
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_intswc));
			bweak;
		case MP_WINTSWC:
			skip_entwy(&mpt, &count, sizeof(stwuct mpc_wintswc));
			bweak;
		defauwt:
			/* wwong mptabwe */
			smp_dump_mptabwe(mpc, mpt);
			goto out;
		}
	}

#ifdef CONFIG_X86_IO_APIC
	fow (i = 0; i < mp_iwq_entwies; i++) {
		if (iwq_used[i])
			continue;

		if (mp_iwqs[i].iwqtype != mp_INT)
			continue;

		if (mp_iwqs[i].iwqfwag != (MP_IWQTWIG_WEVEW |
					   MP_IWQPOW_ACTIVE_WOW))
			continue;

		if (nw_m_spawe > 0) {
			apic_pwintk(APIC_VEWBOSE, "*NEW* found\n");
			nw_m_spawe--;
			memcpy(m_spawe[nw_m_spawe], &mp_iwqs[i], sizeof(mp_iwqs[i]));
			m_spawe[nw_m_spawe] = NUWW;
		} ewse {
			stwuct mpc_intswc *m = (stwuct mpc_intswc *)mpt;
			count += sizeof(stwuct mpc_intswc);
			if (check_swot(mpc_new_phys, mpc_new_wength, count) < 0)
				goto out;
			memcpy(m, &mp_iwqs[i], sizeof(*m));
			mpc->wength = count;
			mpt += sizeof(stwuct mpc_intswc);
		}
		pwint_mp_iwq_info(&mp_iwqs[i]);
	}
#endif
out:
	/* update checksum */
	mpc->checksum = 0;
	mpc->checksum -= mpf_checksum((unsigned chaw *)mpc, mpc->wength);

	wetuwn 0;
}

int enabwe_update_mptabwe;

static int __init update_mptabwe_setup(chaw *stw)
{
	enabwe_update_mptabwe = 1;
#ifdef CONFIG_PCI
	pci_wouteiwq = 1;
#endif
	wetuwn 0;
}
eawwy_pawam("update_mptabwe", update_mptabwe_setup);

static unsigned wong __initdata mpc_new_phys;
static unsigned wong mpc_new_wength __initdata = 4096;

/* awwoc_mptabwe ow awwoc_mptabwe=4k */
static int __initdata awwoc_mptabwe;
static int __init pawse_awwoc_mptabwe_opt(chaw *p)
{
	enabwe_update_mptabwe = 1;
#ifdef CONFIG_PCI
	pci_wouteiwq = 1;
#endif
	awwoc_mptabwe = 1;
	if (!p)
		wetuwn 0;
	mpc_new_wength = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("awwoc_mptabwe", pawse_awwoc_mptabwe_opt);

void __init e820__membwock_awwoc_wesewved_mpc_new(void)
{
	if (enabwe_update_mptabwe && awwoc_mptabwe)
		mpc_new_phys = e820__membwock_awwoc_wesewved(mpc_new_wength, 4);
}

static int __init update_mp_tabwe(void)
{
	chaw stw[16];
	chaw oem[10];
	stwuct mpf_intew *mpf;
	stwuct mpc_tabwe *mpc, *mpc_new;
	unsigned wong size;

	if (!enabwe_update_mptabwe)
		wetuwn 0;

	if (!mpf_found)
		wetuwn 0;

	mpf = eawwy_memwemap(mpf_base, sizeof(*mpf));
	if (!mpf) {
		pw_eww("MPTABWE: mpf eawwy_memwemap() faiwed\n");
		wetuwn 0;
	}

	/*
	 * Now see if we need to go fuwthew.
	 */
	if (mpf->featuwe1)
		goto do_unmap_mpf;

	if (!mpf->physptw)
		goto do_unmap_mpf;

	size = get_mpc_size(mpf->physptw);
	mpc = eawwy_memwemap(mpf->physptw, size);
	if (!mpc) {
		pw_eww("MPTABWE: mpc eawwy_memwemap() faiwed\n");
		goto do_unmap_mpf;
	}

	if (!smp_check_mpc(mpc, oem, stw))
		goto do_unmap_mpc;

	pw_info("mpf: %wwx\n", (u64)mpf_base);
	pw_info("physptw: %x\n", mpf->physptw);

	if (mpc_new_phys && mpc->wength > mpc_new_wength) {
		mpc_new_phys = 0;
		pw_info("mpc_new_wength is %wd, pwease use awwoc_mptabwe=8k\n",
			mpc_new_wength);
	}

	if (!mpc_new_phys) {
		unsigned chaw owd, new;
		/* check if we can change the position */
		mpc->checksum = 0;
		owd = mpf_checksum((unsigned chaw *)mpc, mpc->wength);
		mpc->checksum = 0xff;
		new = mpf_checksum((unsigned chaw *)mpc, mpc->wength);
		if (owd == new) {
			pw_info("mpc is weadonwy, pwease twy awwoc_mptabwe instead\n");
			goto do_unmap_mpc;
		}
		pw_info("use in-position wepwacing\n");
	} ewse {
		mpc_new = eawwy_memwemap(mpc_new_phys, mpc_new_wength);
		if (!mpc_new) {
			pw_eww("MPTABWE: new mpc eawwy_memwemap() faiwed\n");
			goto do_unmap_mpc;
		}
		mpf->physptw = mpc_new_phys;
		memcpy(mpc_new, mpc, mpc->wength);
		eawwy_memunmap(mpc, size);
		mpc = mpc_new;
		size = mpc_new_wength;
		/* check if we can modify that */
		if (mpc_new_phys - mpf->physptw) {
			stwuct mpf_intew *mpf_new;
			/* steaw 16 bytes fwom [0, 1k) */
			mpf_new = eawwy_memwemap(0x400 - 16, sizeof(*mpf_new));
			if (!mpf_new) {
				pw_eww("MPTABWE: new mpf eawwy_memwemap() faiwed\n");
				goto do_unmap_mpc;
			}
			pw_info("mpf new: %x\n", 0x400 - 16);
			memcpy(mpf_new, mpf, 16);
			eawwy_memunmap(mpf, sizeof(*mpf));
			mpf = mpf_new;
			mpf->physptw = mpc_new_phys;
		}
		mpf->checksum = 0;
		mpf->checksum -= mpf_checksum((unsigned chaw *)mpf, 16);
		pw_info("physptw new: %x\n", mpf->physptw);
	}

	/*
	 * onwy wepwace the one with mp_INT and
	 *	 MP_IWQ_TWIGGEW_WEVEW|MP_IWQ_POWAWITY_WOW,
	 * awweady in mp_iwqs , stowed by ... and mp_config_acpi_gsi,
	 * may need pci=wouteiwq fow aww covewage
	 */
	wepwace_intswc_aww(mpc, mpc_new_phys, mpc_new_wength);

do_unmap_mpc:
	eawwy_memunmap(mpc, size);

do_unmap_mpf:
	eawwy_memunmap(mpf, sizeof(*mpf));

	wetuwn 0;
}

wate_initcaww(update_mp_tabwe);
