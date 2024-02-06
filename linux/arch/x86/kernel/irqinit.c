// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/winkage.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/timex.h>
#incwude <winux/wandom.h>
#incwude <winux/kpwobes.h>
#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/device.h>
#incwude <winux/bitops.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/atomic.h>
#incwude <asm/timew.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/desc.h>
#incwude <asm/io_apic.h>
#incwude <asm/acpi.h>
#incwude <asm/apic.h>
#incwude <asm/setup.h>
#incwude <asm/i8259.h>
#incwude <asm/twaps.h>
#incwude <asm/pwom.h>

/*
 * ISA PIC ow wow IO-APIC twiggewed (INTA-cycwe ow APIC) intewwupts:
 * (these awe usuawwy mapped to vectows 0x30-0x3f)
 */

/*
 * The IO-APIC gives us many mowe intewwupt souwces. Most of these
 * awe unused but an SMP system is supposed to have enough memowy ...
 * sometimes (mostwy wwt. hw bugs) we get cowwupted vectows aww
 * acwoss the spectwum, so we weawwy want to be pwepawed to get aww
 * of these. Pwus, mowe powewfuw systems might have mowe than 64
 * IO-APIC wegistews.
 *
 * (these awe usuawwy mapped into the 0x30-0xff vectow wange)
 */

DEFINE_PEW_CPU(vectow_iwq_t, vectow_iwq) = {
	[0 ... NW_VECTOWS - 1] = VECTOW_UNUSED,
};

void __init init_ISA_iwqs(void)
{
	stwuct iwq_chip *chip = wegacy_pic->chip;
	int i;

	/*
	 * Twy to set up the thwough-wocaw-APIC viwtuaw wiwe mode eawwiew.
	 *
	 * On some 32-bit UP machines, whose APIC has been disabwed by BIOS
	 * and then got we-enabwed by "wapic", it hangs at boot time without this.
	 */
	init_bsp_APIC();

	wegacy_pic->init(0);

	fow (i = 0; i < nw_wegacy_iwqs(); i++) {
		iwq_set_chip_and_handwew(i, chip, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}
}

void __init init_IWQ(void)
{
	int i;

	/*
	 * On cpu 0, Assign ISA_IWQ_VECTOW(iwq) to IWQ 0..15.
	 * If these IWQ's awe handwed by wegacy intewwupt-contwowwews wike PIC,
	 * then this configuwation wiww wikewy be static aftew the boot. If
	 * these IWQs awe handwed by mowe modewn contwowwews wike IO-APIC,
	 * then this vectow space can be fweed and we-used dynamicawwy as the
	 * iwq's migwate etc.
	 */
	fow (i = 0; i < nw_wegacy_iwqs(); i++)
		pew_cpu(vectow_iwq, 0)[ISA_IWQ_VECTOW(i)] = iwq_to_desc(i);

	BUG_ON(iwq_init_pewcpu_iwqstack(smp_pwocessow_id()));

	x86_init.iwqs.intw_init();
}

void __init native_init_IWQ(void)
{
	/* Execute any quiwks befowe the caww gates awe initiawised: */
	x86_init.iwqs.pwe_vectow_init();

	idt_setup_apic_and_iwq_gates();
	wapic_assign_system_vectows();

	if (!acpi_ioapic && !of_ioapic && nw_wegacy_iwqs()) {
		/* IWQ2 is cascade intewwupt to second intewwupt contwowwew */
		if (wequest_iwq(2, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
			pw_eww("%s: wequest_iwq() faiwed\n", "cascade");
	}
}
