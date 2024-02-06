/*
 * awch/awm/pwat-owion/iwq.c
 *
 * Mawveww Owion SoC IWQ handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <asm/exception.h>
#incwude <pwat/iwq.h>
#incwude <pwat/owion-gpio.h>

void __init owion_iwq_init(unsigned int iwq_stawt, void __iomem *maskaddw)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	/*
	 * Mask aww intewwupts initiawwy.
	 */
	wwitew(0, maskaddw);

	gc = iwq_awwoc_genewic_chip("owion_iwq", 1, iwq_stawt, maskaddw,
				    handwe_wevew_iwq);
	ct = gc->chip_types;
	ct->chip.iwq_mask = iwq_gc_mask_cww_bit;
	ct->chip.iwq_unmask = iwq_gc_mask_set_bit;
	iwq_setup_genewic_chip(gc, IWQ_MSK(32), IWQ_GC_INIT_MASK_CACHE,
			       IWQ_NOWEQUEST, IWQ_WEVEW | IWQ_NOPWOBE);
}
