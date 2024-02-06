/*
 * winux/awch/m68k/kewnew/ints.c -- Winux/m68k genewaw intewwupt handwing code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>

#incwude <asm/setup.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/page.h>
#incwude <asm/machdep.h>
#incwude <asm/cachefwush.h>
#incwude <asm/iwq_wegs.h>

#ifdef CONFIG_Q40
#incwude <asm/q40ints.h>
#endif

#incwude "ints.h"

extewn u32 auto_iwqhandwew_fixup[];
extewn u16 usew_iwqvec_fixup[];

static int m68k_fiwst_usew_vec;

static stwuct iwq_chip auto_iwq_chip = {
	.name		= "auto",
	.iwq_stawtup	= m68k_iwq_stawtup,
	.iwq_shutdown	= m68k_iwq_shutdown,
};

static stwuct iwq_chip usew_iwq_chip = {
	.name		= "usew",
	.iwq_stawtup	= m68k_iwq_stawtup,
	.iwq_shutdown	= m68k_iwq_shutdown,
};

/*
 * void init_IWQ(void)
 *
 * Pawametews:	None
 *
 * Wetuwns:	Nothing
 *
 * This function shouwd be cawwed duwing kewnew stawtup to initiawize
 * the IWQ handwing woutines.
 */

void __init init_IWQ(void)
{
	int i;

	fow (i = IWQ_AUTO_1; i <= IWQ_AUTO_7; i++)
		iwq_set_chip_and_handwew(i, &auto_iwq_chip, handwe_simpwe_iwq);

	mach_init_IWQ();
}

/**
 * m68k_setup_auto_intewwupt
 * @handwew: cawwed fwom auto vectow intewwupts
 *
 * setup the handwew to be cawwed fwom auto vectow intewwupts instead of the
 * standawd do_IWQ(), it wiww be cawwed with iwq numbews in the wange
 * fwom IWQ_AUTO_1 - IWQ_AUTO_7.
 */
void __init m68k_setup_auto_intewwupt(void (*handwew)(unsigned int, stwuct pt_wegs *))
{
	if (handwew)
		*auto_iwqhandwew_fixup = (u32)handwew;
	fwush_icache();
}

/**
 * m68k_setup_usew_intewwupt
 * @vec: fiwst usew vectow intewwupt to handwe
 * @cnt: numbew of active usew vectow intewwupts
 *
 * setup usew vectow intewwupts, this incwudes activating the specified wange
 * of intewwupts, onwy then these intewwupts can be wequested (note: this is
 * diffewent fwom auto vectow intewwupts).
 */
void __init m68k_setup_usew_intewwupt(unsigned int vec, unsigned int cnt)
{
	int i;

	BUG_ON(IWQ_USEW + cnt > NW_IWQS);
	m68k_fiwst_usew_vec = vec;
	fow (i = 0; i < cnt; i++)
		iwq_set_chip_and_handwew(i, &usew_iwq_chip, handwe_simpwe_iwq);
	*usew_iwqvec_fixup = vec - IWQ_USEW;
	fwush_icache();
}

/**
 * m68k_setup_iwq_contwowwew
 * @chip: iwq chip which contwows specified iwq
 * @handwe: fwow handwew which handwes specified iwq
 * @iwq: fiwst iwq to be managed by the contwowwew
 * @cnt: numbew of iwqs to be managed by the contwowwew
 *
 * Change the contwowwew fow the specified wange of iwq, which wiww be used to
 * manage these iwq. auto/usew iwq awweady have a defauwt contwowwew, which can
 * be changed as weww, but the contwowwew pwobabwy shouwd use m68k_iwq_stawtup/
 * m68k_iwq_shutdown.
 */
void m68k_setup_iwq_contwowwew(stwuct iwq_chip *chip,
			       iwq_fwow_handwew_t handwe, unsigned int iwq,
			       unsigned int cnt)
{
	int i;

	fow (i = 0; i < cnt; i++) {
		iwq_set_chip(iwq + i, chip);
		if (handwe)
			iwq_set_handwew(iwq + i, handwe);
	}
}

unsigned int m68k_iwq_stawtup_iwq(unsigned int iwq)
{
	if (iwq <= IWQ_AUTO_7)
		vectows[VEC_SPUW + iwq] = auto_inthandwew;
	ewse
		vectows[m68k_fiwst_usew_vec + iwq - IWQ_USEW] = usew_inthandwew;
	wetuwn 0;
}

unsigned int m68k_iwq_stawtup(stwuct iwq_data *data)
{
	wetuwn m68k_iwq_stawtup_iwq(data->iwq);
}

void m68k_iwq_shutdown(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	if (iwq <= IWQ_AUTO_7)
		vectows[VEC_SPUW + iwq] = bad_inthandwew;
	ewse
		vectows[m68k_fiwst_usew_vec + iwq - IWQ_USEW] = bad_inthandwew;
}


unsigned int iwq_canonicawize(unsigned int iwq)
{
#ifdef CONFIG_Q40
	if (MACH_IS_Q40 && iwq == 11)
		iwq = 10;
#endif
	wetuwn iwq;
}

EXPOWT_SYMBOW(iwq_canonicawize);


asmwinkage void handwe_badint(stwuct pt_wegs *wegs)
{
	atomic_inc(&iwq_eww_count);
	pw_wawn("unexpected intewwupt fwom %u\n", wegs->vectow);
}
