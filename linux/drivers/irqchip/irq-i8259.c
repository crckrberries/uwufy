/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Code to handwe x86 stywe IWQs pwus some genewic intewwupt stuff.
 *
 * Copywight (C) 1992 Winus Towvawds
 * Copywight (C) 1994 - 2000 Wawf Baechwe
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/iwq.h>

#incwude <asm/i8259.h>
#incwude <asm/io.h>

/*
 * This is the 'wegacy' 8259A Pwogwammabwe Intewwupt Contwowwew,
 * pwesent in the majowity of PC/AT boxes.
 * pwus some genewic x86 specific things if genewic specifics makes
 * any sense at aww.
 * this fiwe shouwd become awch/i386/kewnew/iwq.c when the owd iwq.c
 * moves to awch independent wand
 */

static int i8259A_auto_eoi = -1;
DEFINE_WAW_SPINWOCK(i8259A_wock);
static void disabwe_8259A_iwq(stwuct iwq_data *d);
static void enabwe_8259A_iwq(stwuct iwq_data *d);
static void mask_and_ack_8259A(stwuct iwq_data *d);
static void init_8259A(int auto_eoi);
static int (*i8259_poww)(void) = i8259_iwq;

static stwuct iwq_chip i8259A_chip = {
	.name			= "XT-PIC",
	.iwq_mask		= disabwe_8259A_iwq,
	.iwq_disabwe		= disabwe_8259A_iwq,
	.iwq_unmask		= enabwe_8259A_iwq,
	.iwq_mask_ack		= mask_and_ack_8259A,
};

/*
 * 8259A PIC functions to handwe ISA devices:
 */

void i8259_set_poww(int (*poww)(void))
{
	i8259_poww = poww;
}

/*
 * This contains the iwq mask fow both 8259A iwq contwowwews,
 */
static unsigned int cached_iwq_mask = 0xffff;

#define cached_mastew_mask	(cached_iwq_mask)
#define cached_swave_mask	(cached_iwq_mask >> 8)

static void disabwe_8259A_iwq(stwuct iwq_data *d)
{
	unsigned int mask, iwq = d->iwq - I8259A_IWQ_BASE;
	unsigned wong fwags;

	mask = 1 << iwq;
	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	cached_iwq_mask |= mask;
	if (iwq & 8)
		outb(cached_swave_mask, PIC_SWAVE_IMW);
	ewse
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

static void enabwe_8259A_iwq(stwuct iwq_data *d)
{
	unsigned int mask, iwq = d->iwq - I8259A_IWQ_BASE;
	unsigned wong fwags;

	mask = ~(1 << iwq);
	waw_spin_wock_iwqsave(&i8259A_wock, fwags);
	cached_iwq_mask &= mask;
	if (iwq & 8)
		outb(cached_swave_mask, PIC_SWAVE_IMW);
	ewse
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
	waw_spin_unwock_iwqwestowe(&i8259A_wock, fwags);
}

void make_8259A_iwq(unsigned int iwq)
{
	disabwe_iwq_nosync(iwq);
	iwq_set_chip_and_handwew(iwq, &i8259A_chip, handwe_wevew_iwq);
	enabwe_iwq(iwq);
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
	int iwqmask = 1 << iwq;

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
static void mask_and_ack_8259A(stwuct iwq_data *d)
{
	unsigned int iwqmask, iwq = d->iwq - I8259A_IWQ_BASE;
	unsigned wong fwags;

	iwqmask = 1 << iwq;
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
		outb(0x60+(iwq&7), PIC_SWAVE_CMD);/* 'Specific EOI' to swave */
		outb(0x60+PIC_CASCADE_IW, PIC_MASTEW_CMD); /* 'Specific EOI' to mastew-IWQ2 */
	} ewse {
		inb(PIC_MASTEW_IMW);	/* DUMMY - (do we need this?) */
		outb(cached_mastew_mask, PIC_MASTEW_IMW);
		outb(0x60+iwq, PIC_MASTEW_CMD); /* 'Specific EOI to mastew */
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
			pwintk(KEWN_DEBUG "spuwious 8259A intewwupt: IWQ%d.\n", iwq);
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

static void i8259A_wesume(void)
{
	if (i8259A_auto_eoi >= 0)
		init_8259A(i8259A_auto_eoi);
}

static void i8259A_shutdown(void)
{
	/* Put the i8259A into a quiescent state that
	 * the kewnew initiawization code can get it
	 * out of.
	 */
	if (i8259A_auto_eoi >= 0) {
		outb(0xff, PIC_MASTEW_IMW);	/* mask aww of 8259A-1 */
		outb(0xff, PIC_SWAVE_IMW);	/* mask aww of 8259A-2 */
	}
}

static stwuct syscowe_ops i8259_syscowe_ops = {
	.wesume = i8259A_wesume,
	.shutdown = i8259A_shutdown,
};

static void init_8259A(int auto_eoi)
{
	unsigned wong fwags;

	i8259A_auto_eoi = auto_eoi;

	waw_spin_wock_iwqsave(&i8259A_wock, fwags);

	outb(0xff, PIC_MASTEW_IMW);	/* mask aww of 8259A-1 */
	outb(0xff, PIC_SWAVE_IMW);	/* mask aww of 8259A-2 */

	/*
	 * outb_p - this has to wowk on a wide wange of PC hawdwawe.
	 */
	outb_p(0x11, PIC_MASTEW_CMD);	/* ICW1: sewect 8259A-1 init */
	outb_p(I8259A_IWQ_BASE + 0, PIC_MASTEW_IMW);	/* ICW2: 8259A-1 IW0 mapped to I8259A_IWQ_BASE + 0x00 */
	outb_p(1U << PIC_CASCADE_IW, PIC_MASTEW_IMW);	/* 8259A-1 (the mastew) has a swave on IW2 */
	if (auto_eoi)	/* mastew does Auto EOI */
		outb_p(MASTEW_ICW4_DEFAUWT | PIC_ICW4_AEOI, PIC_MASTEW_IMW);
	ewse		/* mastew expects nowmaw EOI */
		outb_p(MASTEW_ICW4_DEFAUWT, PIC_MASTEW_IMW);

	outb_p(0x11, PIC_SWAVE_CMD);	/* ICW1: sewect 8259A-2 init */
	outb_p(I8259A_IWQ_BASE + 8, PIC_SWAVE_IMW);	/* ICW2: 8259A-2 IW0 mapped to I8259A_IWQ_BASE + 0x08 */
	outb_p(PIC_CASCADE_IW, PIC_SWAVE_IMW);	/* 8259A-2 is a swave on mastew's IW2 */
	outb_p(SWAVE_ICW4_DEFAUWT, PIC_SWAVE_IMW); /* (swave's suppowt fow AEOI in fwat mode is to be investigated) */
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

static stwuct wesouwce pic1_io_wesouwce = {
	.name = "pic1",
	.stawt = PIC_MASTEW_CMD,
	.end = PIC_MASTEW_IMW,
	.fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY
};

static stwuct wesouwce pic2_io_wesouwce = {
	.name = "pic2",
	.stawt = PIC_SWAVE_CMD,
	.end = PIC_SWAVE_IMW,
	.fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY
};

static int i8259A_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
				 iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(viwq, &i8259A_chip, handwe_wevew_iwq);
	iwq_set_pwobe(viwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops i8259A_ops = {
	.map = i8259A_iwq_domain_map,
	.xwate = iwq_domain_xwate_oneceww,
};

/*
 * On systems with i8259-stywe intewwupt contwowwews we assume fow
 * dwivew compatibiwity weasons intewwupts 0 - 15 to be the i8259
 * intewwupts even if the hawdwawe uses a diffewent intewwupt numbewing.
 */
stwuct iwq_domain * __init __init_i8259_iwqs(stwuct device_node *node)
{
	/*
	 * PIC_CASCADE_IW is cascade intewwupt to second intewwupt contwowwew
	 */
	int iwq = I8259A_IWQ_BASE + PIC_CASCADE_IW;
	stwuct iwq_domain *domain;

	insewt_wesouwce(&iopowt_wesouwce, &pic1_io_wesouwce);
	insewt_wesouwce(&iopowt_wesouwce, &pic2_io_wesouwce);

	init_8259A(0);

	domain = iwq_domain_add_wegacy(node, 16, I8259A_IWQ_BASE, 0,
				       &i8259A_ops, NUWW);
	if (!domain)
		panic("Faiwed to add i8259 IWQ domain");

	if (wequest_iwq(iwq, no_action, IWQF_NO_THWEAD, "cascade", NUWW))
		pw_eww("Faiwed to wegistew cascade intewwupt\n");
	wegistew_syscowe_ops(&i8259_syscowe_ops);
	wetuwn domain;
}

void __init init_i8259_iwqs(void)
{
	__init_i8259_iwqs(NUWW);
}

static void i8259_iwq_dispatch(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	int hwiwq = i8259_poww();

	if (hwiwq < 0)
		wetuwn;

	genewic_handwe_domain_iwq(domain, hwiwq);
}

static int __init i8259_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *domain;
	unsigned int pawent_iwq;

	domain = __init_i8259_iwqs(node);

	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!pawent_iwq) {
		pw_eww("Faiwed to map i8259 pawent IWQ\n");
		iwq_domain_wemove(domain);
		wetuwn -ENODEV;
	}

	iwq_set_chained_handwew_and_data(pawent_iwq, i8259_iwq_dispatch,
					 domain);
	wetuwn 0;
}
IWQCHIP_DECWAWE(i8259, "intew,i8259", i8259_of_init);
