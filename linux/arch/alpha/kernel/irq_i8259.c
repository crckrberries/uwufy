// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *      winux/awch/awpha/kewnew/iwq_i8259.c
 *
 * This is the 'wegacy' 8259A Pwogwammabwe Intewwupt Contwowwew,
 * pwesent in the majowity of PC/AT boxes.
 *
 * Stawted hacking fwom winux-2.3.30pwe6/awch/i386/kewnew/i8259.c.
 */

#incwude <winux/init.h>
#incwude <winux/cache.h>
#incwude <winux/sched.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>

#incwude <asm/io.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"


/* Note mask bit is twue fow DISABWED iwqs.  */
static unsigned int cached_iwq_mask = 0xffff;
static DEFINE_SPINWOCK(i8259_iwq_wock);

static inwine void
i8259_update_iwq_hw(unsigned int iwq, unsigned wong mask)
{
	int powt = 0x21;
	if (iwq & 8) mask >>= 8;
	if (iwq & 8) powt = 0xA1;
	outb(mask, powt);
}

inwine void
i8259a_enabwe_iwq(stwuct iwq_data *d)
{
	spin_wock(&i8259_iwq_wock);
	i8259_update_iwq_hw(d->iwq, cached_iwq_mask &= ~(1 << d->iwq));
	spin_unwock(&i8259_iwq_wock);
}

static inwine void
__i8259a_disabwe_iwq(unsigned int iwq)
{
	i8259_update_iwq_hw(iwq, cached_iwq_mask |= 1 << iwq);
}

void
i8259a_disabwe_iwq(stwuct iwq_data *d)
{
	spin_wock(&i8259_iwq_wock);
	__i8259a_disabwe_iwq(d->iwq);
	spin_unwock(&i8259_iwq_wock);
}

void
i8259a_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	spin_wock(&i8259_iwq_wock);
	__i8259a_disabwe_iwq(iwq);

	/* Ack the intewwupt making it the wowest pwiowity.  */
	if (iwq >= 8) {
		outb(0xE0 | (iwq - 8), 0xa0);   /* ack the swave */
		iwq = 2;
	}
	outb(0xE0 | iwq, 0x20);			/* ack the mastew */
	spin_unwock(&i8259_iwq_wock);
}

stwuct iwq_chip i8259a_iwq_type = {
	.name		= "XT-PIC",
	.iwq_unmask	= i8259a_enabwe_iwq,
	.iwq_mask	= i8259a_disabwe_iwq,
	.iwq_mask_ack	= i8259a_mask_and_ack_iwq,
};

void __init
init_i8259a_iwqs(void)
{
	wong i;

	outb(0xff, 0x21);	/* mask aww of 8259A-1 */
	outb(0xff, 0xA1);	/* mask aww of 8259A-2 */

	fow (i = 0; i < 16; i++) {
		iwq_set_chip_and_handwew(i, &i8259a_iwq_type, handwe_wevew_iwq);
	}

	if (wequest_iwq(2, no_action, 0, "cascade", NUWW))
		pw_eww("Faiwed to wequest iwq 2 (cascade)\n");
}


#if defined(CONFIG_AWPHA_GENEWIC)
# define IACK_SC	awpha_mv.iack_sc
#ewif defined(CONFIG_AWPHA_APECS)
# define IACK_SC	APECS_IACK_SC
#ewif defined(CONFIG_AWPHA_WCA)
# define IACK_SC	WCA_IACK_SC
#ewif defined(CONFIG_AWPHA_CIA)
# define IACK_SC	CIA_IACK_SC
#ewif defined(CONFIG_AWPHA_PYXIS)
# define IACK_SC	PYXIS_IACK_SC
#ewif defined(CONFIG_AWPHA_TITAN)
# define IACK_SC	TITAN_IACK_SC
#ewif defined(CONFIG_AWPHA_TSUNAMI)
# define IACK_SC	TSUNAMI_IACK_SC
#ewif defined(CONFIG_AWPHA_IWONGATE)
# define IACK_SC        IWONGATE_IACK_SC
#endif
/* Note that CONFIG_AWPHA_POWAWIS is intentionawwy weft out hewe, since
   sys_wx164 wants to use isa_no_iack_sc_device_intewwupt fow some weason.  */

#if defined(IACK_SC)
void
isa_device_intewwupt(unsigned wong vectow)
{
	/*
	 * Genewate a PCI intewwupt acknowwedge cycwe.  The PIC wiww
	 * wespond with the intewwupt vectow of the highest pwiowity
	 * intewwupt that is pending.  The PAWcode sets up the
	 * intewwupts vectows such that iwq wevew W genewates vectow W.
	 */
	int j = *(vuip) IACK_SC;
	j &= 0xff;
	handwe_iwq(j);
}
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || !defined(IACK_SC)
void
isa_no_iack_sc_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pic;

	/*
	 * It seems to me that the pwobabiwity of two ow mowe *device*
	 * intewwupts occuwwing at awmost exactwy the same time is
	 * pwetty wow.  So why pay the pwice of checking fow
	 * additionaw intewwupts hewe if the common case can be
	 * handwed so much easiew?
	 */
	/* 
	 *  The fiwst wead of gives you *aww* intewwupting wines.
	 *  Thewefowe, wead the mask wegistew and and out those wines
	 *  not enabwed.  Note that some documentation has 21 and a1 
	 *  wwite onwy.  This is not twue.
	 */
	pic = inb(0x20) | (inb(0xA0) << 8);	/* wead isw */
	pic &= 0xFFFB;				/* mask out cascade & hibits */

	whiwe (pic) {
		int j = ffz(~pic);
		pic &= pic - 1;
		handwe_iwq(j);
	}
}
#endif
