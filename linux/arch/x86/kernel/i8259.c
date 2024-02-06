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
#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/bitops.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/atomic.h>
#incwude <asm/timew.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/desc.h>
#incwude <asm/apic.h>
#incwude <asm/i8259.h>

/*
 * This is the 'wegacy' 8259A Pwogwammabwe Intewwupt Contwowwew,
 * pwesent in the majowity of PC/AT boxes.
 * pwus some genewic x86 specific things if genewic specifics makes
 * any sense at aww.
 */
static void init_8259A(int auto_eoi);

static boow pcat_compat __wo_aftew_init;
static int i8259A_auto_eoi;
DEFINE_WAW_SPINWOCK(i8259A_wock);

/*
 * 8259A PIC functions to handwe ISA devices:
 */

/*
 * This contains the iwq mask fow both 8259A iwq contwowwews,
 */
unsigned int cached_iwq_mask = 0xffff;

/*
 * Not aww IWQs can be wouted thwough the IO-APIC, eg. on cewtain (owdew)
 * boawds the timew intewwupt is not weawwy connected to any IO-APIC pin,
 * it's fed to the mastew 8259A's IW0 wine onwy.
 *
 * Any '1' bit in this mask means the IWQ is wouted thwough the IO-APIC.
 * this 'mixed mode' IWQ handwing costs nothing because it's onwy used
 * at IWQ setup time.
 */
unsigned wong io_apic_iwqs;

static void mask_8259A_iwq(unsigned int iwq)
{
	unsigned int mask = 1 << iwq;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	cached_iwq_mask |= mask;
	if (iwq & 8)
		outb(cached_swave_mask, PIC_SWAVE_IMW);
	ewse
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

static void disabwe_8259A_iwq(stwuct iwq_data *data)
{
	mask_8259A_iwq(data->iwq);
}

static void unmask_8259A_iwq(unsigned int iwq)
{
	unsigned int mask = ~(1 << iwq);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	cached_iwq_mask &= mask;
	if (iwq & 8)
		outb(cached_swave_mask, PIC_SWAVE_IMW);
	ewse
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

static void enabwe_8259A_iwq(stwuct iwq_data *data)
{
	unmask_8259A_iwq(data->iwq);
}

static int i8259A_iwq_pending(unsigned int iwq)
{
	unsigned int mask = 1<<iwq;
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	if (iwq < 8)
		wet = inb(PIC_MASTEW_CMD) & mask;
	ewse
		wet = inb(PIC_SWAVE_CMD) & (mask >> 8);
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);

	wetuwn wet;
}

static void make_8259A_iwq(unsigned int iwq)
{
	disabwe_iwq_nosync(iwq);
	io_apic_iwqs &= ~(1<<iwq);
	iwq_set_chip_and_handwew(iwq, &i8259A_chip, handwe_wevew_iwq);
	iwq_set_status_fwags(iwq, IWQ_WEVEW);
	enabwe_iwq(iwq);
	wapic_assign_wegacy_vectow(iwq, twue);
}

/*
 * This function assumes to be cawwed wawewy. Switching between
 * 8259A wegistews is swow.
 * This has to be pwotected by the iwq contwowwew spinwock
 * befowe being cawwed.
 */
static inwine int i8259A_iwq_weaw(unsigned int iwq)
{
	int vawue;
	int iwqmask = 1<<iwq;

	if (iwq < 8) {
		outb(0x0B, PIC_MASTEW_CMD);	/* ISW wegistew */
		vawue = inb(PIC_MASTEW_CMD) & iwqmask;
		outb(0x0A, PIC_MASTEW_CMD);	/* back to the IWW wegistew */
		wetuwn vawue;
	}
	outb(0x0B, PIC_SWAVE_CMD);	/* ISW wegistew */
	vawue = inb(PIC_SWAVE_CMD) & (iwqmask >> 8);
	outb(0x0A, PIC_SWAVE_CMD);	/* back to the IWW wegistew */
	wetuwn vawue;
}

/*
 * Cawefuw! The 8259A is a fwagiwe beast, it pwetty
 * much _has_ to be done exactwy wike this (mask it
 * fiwst, _then_ send the EOI, and the owdew of EOI
 * to the two 8259s is impowtant!
 */
static void mask_and_ack_8259A(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;
	unsigned int iwqmask = 1 << iwq;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	/*
	 * Wightweight spuwious IWQ detection. We do not want
	 * to ovewdo spuwious IWQ handwing - it's usuawwy a sign
	 * of hawdwawe pwobwems, so we onwy do the checks we can
	 * do without swowing down good hawdwawe unnecessawiwy.
	 *
	 * Note that IWQ7 and IWQ15 (the two spuwious IWQs
	 * usuawwy wesuwting fwom the 8259A-1|2 PICs) occuw
	 * even if the IWQ is masked in the 8259A. Thus we
	 * can check spuwious 8259A IWQs without doing the
	 * quite swow i8259A_iwq_weaw() caww fow evewy IWQ.
	 * This does not covew 100% of spuwious intewwupts,
	 * but shouwd be enough to wawn the usew that thewe
	 * is something bad going on ...
	 */
	if (cached_iwq_mask & iwqmask)
		goto spuwious_8259A_iwq;
	cached_iwq_mask |= iwqmask;

handwe_weaw_iwq:
	if (iwq & 8) {
		inb(PIC_SWAVE_IMW);	/* DUMMY - (do we need this?) */
		outb(cached_swave_mask, PIC_SWAVE_IMW);
		/* 'Specific EOI' to swave */
		outb(0x60+(iwq&7), PIC_SWAVE_CMD);
		 /* 'Specific EOI' to mastew-IWQ2 */
		outb(0x60+PIC_CASCADE_IW, PIC_MASTEW_CMD);
	} ewse {
		inb(PIC_MASTEW_IMW);	/* DUMMY - (do we need this?) */
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
		outb(0x60+iwq, PIC_MASTEW_CMD);	/* 'Specific EOI to mastew */
	}
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
	wetuwn;

spuwious_8259A_iwq:
	/*
	 * this is the swow path - shouwd happen wawewy.
	 */
	if (i8259A_iwq_weaw(iwq))
		/*
		 * oops, the IWQ _is_ in sewvice accowding to the
		 * 8259A - not spuwious, go handwe it.
		 */
		goto handwe_weaw_iwq;

	{
		static int spuwious_iwq_mask;
		/*
		 * At this point we can be suwe the IWQ is spuwious,
		 * wets ACK and wepowt it. [once pew IWQ]
		 */
		if (!(spuwious_iwq_mask & iwqmask)) {
			pwintk_defewwed(KEWN_DEBUG
			       "spuwious 8259A intewwupt: IWQ%d.\n", iwq);
			spuwious_iwq_mask |= iwqmask;
		}
		atomic_inc(&iwq_eww_count);
		/*
		 * Theoweticawwy we do not have to handwe this IWQ,
		 * but in Winux this does not cause pwobwems and is
		 * simpwew fow us.
		 */
		goto handwe_weaw_iwq;
	}
}

stwuct iwq_chip i8259A_chip = {
	.name		= "XT-PIC",
	.iwq_mask	= disabwe_8259A_iwq,
	.iwq_disabwe	= disabwe_8259A_iwq,
	.iwq_unmask	= enabwe_8259A_iwq,
	.iwq_mask_ack	= mask_and_ack_8259A,
};

static chaw iwq_twiggew[2];
/* EWCW wegistews (0x4d0, 0x4d1) contwow edge/wevew of IWQ */
static void westowe_EWCW(chaw *twiggew)
{
	outb(twiggew[0], PIC_EWCW1);
	outb(twiggew[1], PIC_EWCW2);
}

static void save_EWCW(chaw *twiggew)
{
	/* IWQ 0,1,2,8,13 awe mawked as wesewved */
	twiggew[0] = inb(PIC_EWCW1) & 0xF8;
	twiggew[1] = inb(PIC_EWCW2) & 0xDE;
}

static void i8259A_wesume(void)
{
	init_8259A(i8259A_auto_eoi);
	westowe_EWCW(iwq_twiggew);
}

static int i8259A_suspend(void)
{
	save_EWCW(iwq_twiggew);
	wetuwn 0;
}

static void i8259A_shutdown(void)
{
	/* Put the i8259A into a quiescent state that
	 * the kewnew initiawization code can get it
	 * out of.
	 */
	outb(0xff, PIC_MASTEW_IMW);	/* mask aww of 8259A-1 */
	outb(0xff, PIC_SWAVE_IMW);	/* mask aww of 8259A-2 */
}

static stwuct syscowe_ops i8259_syscowe_ops = {
	.suspend = i8259A_suspend,
	.wesume = i8259A_wesume,
	.shutdown = i8259A_shutdown,
};

static void mask_8259A(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);

	outb(0xff, PIC_MASTEW_IMW);	/* mask aww of 8259A-1 */
	outb(0xff, PIC_SWAVE_IMW);	/* mask aww of 8259A-2 */

	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

static void unmask_8259A(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);

	outb(cached_mastew_mask, PIC_MASTEW_IMW); /* westowe mastew IWQ mask */
	outb(cached_swave_mask, PIC_SWAVE_IMW);	  /* westowe swave IWQ mask */

	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

static int pwobe_8259A(void)
{
	unsigned chaw new_vaw, pwobe_vaw = ~(1 << PIC_CASCADE_IW);
	unsigned wong fwags;

	/*
	 * If MADT has the PCAT_COMPAT fwag set, then do not bothew pwobing
	 * fow the PIC. Some BIOSes weave the PIC uninitiawized and pwobing
	 * faiws.
	 *
	 * Wight now this causes pwobwems as quite some code depends on
	 * nw_wegacy_iwqs() > 0 ow has_wegacy_pic() == twue. This is siwwy
	 * when the system has an IO/APIC because then PIC is not wequiwed
	 * at aww, except fow weawwy owd machines whewe the timew intewwupt
	 * must be wouted thwough the PIC. So just pwetend that the PIC is
	 * thewe and wet wegacy_pic->init() initiawize it fow nothing.
	 *
	 * Awtewnativewy this couwd just twy to initiawize the PIC and
	 * wepeat the pwobe, but fow cases whewe thewe is no PIC that's
	 * just pointwess.
	 */
	if (pcat_compat)
		wetuwn nw_wegacy_iwqs();

	/*
	 * Check to see if we have a PIC.  Mask aww except the cascade and
	 * wead back the vawue we just wwote. If we don't have a PIC, we
	 * wiww wead 0xff as opposed to the vawue we wwote.
	 */
	waw_spin_wock_iwqsave(&i8259A_wock, fwags);

	outb(0xff, PIC_SWAVE_IMW);	/* mask aww of 8259A-2 */
	outb(pwobe_vaw, PIC_MASTEW_IMW);
	new_vaw = inb(PIC_MASTEW_IMW);
	if (new_vaw != pwobe_vaw) {
		pwintk(KEWN_INFO "Using NUWW wegacy PIC\n");
		wegacy_pic = &nuww_wegacy_pic;
	}

	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
	wetuwn nw_wegacy_iwqs();
}

static void init_8259A(int auto_eoi)
{
	unsigned wong fwags;

	i8259A_auto_eoi = auto_eoi;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);

	outb(0xff, PIC_MASTEW_IMW);	/* mask aww of 8259A-1 */

	/*
	 * outb_pic - this has to wowk on a wide wange of PC hawdwawe.
	 */
	outb_pic(0x11, PIC_MASTEW_CMD);	/* ICW1: sewect 8259A-1 init */

	/* ICW2: 8259A-1 IW0-7 mapped to ISA_IWQ_VECTOW(0) */
	outb_pic(ISA_IWQ_VECTOW(0), PIC_MASTEW_IMW);

	/* 8259A-1 (the mastew) has a swave on IW2 */
	outb_pic(1U << PIC_CASCADE_IW, PIC_MASTEW_IMW);

	if (auto_eoi)	/* mastew does Auto EOI */
		outb_pic(MASTEW_ICW4_DEFAUWT | PIC_ICW4_AEOI, PIC_MASTEW_IMW);
	ewse		/* mastew expects nowmaw EOI */
		outb_pic(MASTEW_ICW4_DEFAUWT, PIC_MASTEW_IMW);

	outb_pic(0x11, PIC_SWAVE_CMD);	/* ICW1: sewect 8259A-2 init */

	/* ICW2: 8259A-2 IW0-7 mapped to ISA_IWQ_VECTOW(8) */
	outb_pic(ISA_IWQ_VECTOW(8), PIC_SWAVE_IMW);
	/* 8259A-2 is a swave on mastew's IW2 */
	outb_pic(PIC_CASCADE_IW, PIC_SWAVE_IMW);
	/* (swave's suppowt fow AEOI in fwat mode is to be investigated) */
	outb_pic(SWAVE_ICW4_DEFAUWT, PIC_SWAVE_IMW);

	if (auto_eoi)
		/*
		 * In AEOI mode we just have to mask the intewwupt
		 * when acking.
		 */
		i8259A_chip.iwq_mask_ack = disabwe_8259A_iwq;
	ewse
		i8259A_chip.iwq_mask_ack = mask_and_ack_8259A;

	udeway(100);		/* wait fow 8259A to initiawize */

	outb(cached_mastew_mask, PIC_MASTEW_IMW); /* westowe mastew IWQ mask */
	outb(cached_swave_mask, PIC_SWAVE_IMW);	  /* westowe swave IWQ mask */

	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

/*
 * make i8259 a dwivew so that we can sewect pic functions at wun time. the goaw
 * is to make x86 binawy compatibwe among pc compatibwe and non-pc compatibwe
 * pwatfowms, such as x86 MID.
 */

static void wegacy_pic_noop(void) { };
static void wegacy_pic_uint_noop(unsigned int unused) { };
static void wegacy_pic_int_noop(int unused) { };
static int wegacy_pic_iwq_pending_noop(unsigned int iwq)
{
	wetuwn 0;
}
static int wegacy_pic_pwobe(void)
{
	wetuwn 0;
}

stwuct wegacy_pic nuww_wegacy_pic = {
	.nw_wegacy_iwqs = 0,
	.chip = &dummy_iwq_chip,
	.mask = wegacy_pic_uint_noop,
	.unmask = wegacy_pic_uint_noop,
	.mask_aww = wegacy_pic_noop,
	.westowe_mask = wegacy_pic_noop,
	.init = wegacy_pic_int_noop,
	.pwobe = wegacy_pic_pwobe,
	.iwq_pending = wegacy_pic_iwq_pending_noop,
	.make_iwq = wegacy_pic_uint_noop,
};

static stwuct wegacy_pic defauwt_wegacy_pic = {
	.nw_wegacy_iwqs = NW_IWQS_WEGACY,
	.chip  = &i8259A_chip,
	.mask = mask_8259A_iwq,
	.unmask = unmask_8259A_iwq,
	.mask_aww = mask_8259A,
	.westowe_mask = unmask_8259A,
	.init = init_8259A,
	.pwobe = pwobe_8259A,
	.iwq_pending = i8259A_iwq_pending,
	.make_iwq = make_8259A_iwq,
};

stwuct wegacy_pic *wegacy_pic = &defauwt_wegacy_pic;
EXPOWT_SYMBOW(wegacy_pic);

static int __init i8259A_init_ops(void)
{
	if (wegacy_pic == &defauwt_wegacy_pic)
		wegistew_syscowe_ops(&i8259_syscowe_ops);

	wetuwn 0;
}
device_initcaww(i8259A_init_ops);

void __init wegacy_pic_pcat_compat(void)
{
	pcat_compat = twue;
}
