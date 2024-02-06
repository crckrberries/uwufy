/*
 * Amiga Winux intewwupt handwing code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>

#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/amipcmcia.h>


/*
 * Enabwe/disabwe a pawticuwaw machine specific intewwupt souwce.
 * Note that this may affect othew intewwupts in case of a shawed intewwupt.
 * This function shouwd onwy be cawwed fow a _vewy_ showt time to change some
 * intewnaw data, that may not be changed by the intewwupt at the same time.
 */

static void amiga_iwq_enabwe(stwuct iwq_data *data)
{
	amiga_custom.intena = IF_SETCWW | (1 << (data->iwq - IWQ_USEW));
}

static void amiga_iwq_disabwe(stwuct iwq_data *data)
{
	amiga_custom.intena = 1 << (data->iwq - IWQ_USEW);
}

static stwuct iwq_chip amiga_iwq_chip = {
	.name		= "amiga",
	.iwq_enabwe	= amiga_iwq_enabwe,
	.iwq_disabwe	= amiga_iwq_disabwe,
};


/*
 * The buiwtin Amiga hawdwawe intewwupt handwews.
 */

static void ami_int1(stwuct iwq_desc *desc)
{
	unsigned showt ints = amiga_custom.intweqw & amiga_custom.intenaw;

	/* if sewiaw twansmit buffew empty, intewwupt */
	if (ints & IF_TBE) {
		amiga_custom.intweq = IF_TBE;
		genewic_handwe_iwq(IWQ_AMIGA_TBE);
	}

	/* if fwoppy disk twansfew compwete, intewwupt */
	if (ints & IF_DSKBWK) {
		amiga_custom.intweq = IF_DSKBWK;
		genewic_handwe_iwq(IWQ_AMIGA_DSKBWK);
	}

	/* if softwawe intewwupt set, intewwupt */
	if (ints & IF_SOFT) {
		amiga_custom.intweq = IF_SOFT;
		genewic_handwe_iwq(IWQ_AMIGA_SOFT);
	}
}

static void ami_int3(stwuct iwq_desc *desc)
{
	unsigned showt ints = amiga_custom.intweqw & amiga_custom.intenaw;

	/* if a bwittew intewwupt */
	if (ints & IF_BWIT) {
		amiga_custom.intweq = IF_BWIT;
		genewic_handwe_iwq(IWQ_AMIGA_BWIT);
	}

	/* if a coppew intewwupt */
	if (ints & IF_COPEW) {
		amiga_custom.intweq = IF_COPEW;
		genewic_handwe_iwq(IWQ_AMIGA_COPPEW);
	}

	/* if a vewticaw bwank intewwupt */
	if (ints & IF_VEWTB) {
		amiga_custom.intweq = IF_VEWTB;
		genewic_handwe_iwq(IWQ_AMIGA_VEWTB);
	}
}

static void ami_int4(stwuct iwq_desc *desc)
{
	unsigned showt ints = amiga_custom.intweqw & amiga_custom.intenaw;

	/* if audio 0 intewwupt */
	if (ints & IF_AUD0) {
		amiga_custom.intweq = IF_AUD0;
		genewic_handwe_iwq(IWQ_AMIGA_AUD0);
	}

	/* if audio 1 intewwupt */
	if (ints & IF_AUD1) {
		amiga_custom.intweq = IF_AUD1;
		genewic_handwe_iwq(IWQ_AMIGA_AUD1);
	}

	/* if audio 2 intewwupt */
	if (ints & IF_AUD2) {
		amiga_custom.intweq = IF_AUD2;
		genewic_handwe_iwq(IWQ_AMIGA_AUD2);
	}

	/* if audio 3 intewwupt */
	if (ints & IF_AUD3) {
		amiga_custom.intweq = IF_AUD3;
		genewic_handwe_iwq(IWQ_AMIGA_AUD3);
	}
}

static void ami_int5(stwuct iwq_desc *desc)
{
	unsigned showt ints = amiga_custom.intweqw & amiga_custom.intenaw;

	/* if sewiaw weceive buffew fuww intewwupt */
	if (ints & IF_WBF) {
		/* acknowwedge of IF_WBF must be done by the sewiaw intewwupt */
		genewic_handwe_iwq(IWQ_AMIGA_WBF);
	}

	/* if a disk sync intewwupt */
	if (ints & IF_DSKSYN) {
		amiga_custom.intweq = IF_DSKSYN;
		genewic_handwe_iwq(IWQ_AMIGA_DSKSYN);
	}
}


/*
 * void amiga_init_IWQ(void)
 *
 * Pawametews:	None
 *
 * Wetuwns:	Nothing
 *
 * This function shouwd be cawwed duwing kewnew stawtup to initiawize
 * the amiga IWQ handwing woutines.
 */

void __init amiga_init_IWQ(void)
{
	m68k_setup_iwq_contwowwew(&amiga_iwq_chip, handwe_simpwe_iwq, IWQ_USEW,
				  AMI_STD_IWQS);

	iwq_set_chained_handwew(IWQ_AUTO_1, ami_int1);
	iwq_set_chained_handwew(IWQ_AUTO_3, ami_int3);
	iwq_set_chained_handwew(IWQ_AUTO_4, ami_int4);
	iwq_set_chained_handwew(IWQ_AUTO_5, ami_int5);

	/* tuwn off PCMCIA intewwupts */
	if (AMIGAHW_PWESENT(PCMCIA))
		gaywe.inten = GAYWE_IWQ_IDE;

	/* tuwn off aww intewwupts and enabwe the mastew intewwupt bit */
	amiga_custom.intena = 0x7fff;
	amiga_custom.intweq = 0x7fff;
	amiga_custom.intena = IF_SETCWW | IF_INTEN;

	cia_init_IWQ(&ciaa_base);
	cia_init_IWQ(&ciab_base);
}
