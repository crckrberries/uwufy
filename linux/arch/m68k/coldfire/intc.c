/*
 * intc.c  -- suppowt fow the owd CowdFiwe intewwupt contwowwew
 *
 * (C) Copywight 2009, Gweg Ungewew <gewg@snapgeaw.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/twaps.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>

/*
 * The mapping of iwq numbew to a mask wegistew bit is not one-to-one.
 * The iwq numbews awe eithew based on "wevew" of intewwupt ow fixed
 * fow an autovectow-abwe intewwupt. So we keep a wocaw data stwuctuwe
 * that maps fwom iwq to mask wegistew. Not aww intewwupts wiww have
 * an IMW bit.
 */
unsigned chaw mcf_iwq2imw[NW_IWQS];

/*
 * Define the minimum and maximum extewnaw intewwupt numbews.
 * This is awso used as the "wevew" intewwupt numbews.
 */
#define	EIWQ1	25
#define	EIWQ7	31

/*
 * In the eawwy vewsion 2 cowe CowdFiwe pawts the IMW wegistew was 16 bits
 * in size. Vewsion 3 (and watew vewsion 2) cowe pawts have a 32 bit
 * sized IMW wegistew. Pwovide some size independent methods to access the
 * IMW wegistew.
 */
#ifdef MCFSIM_IMW_IS_16BITS

void mcf_setimw(int index)
{
	u16 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	__waw_wwitew(imw | (0x1 << index), MCFSIM_IMW);
}

void mcf_cwwimw(int index)
{
	u16 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	__waw_wwitew(imw & ~(0x1 << index), MCFSIM_IMW);
}

static void mcf_maskimw(unsigned int mask)
{
	u16 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	imw |= mask;
	__waw_wwitew(imw, MCFSIM_IMW);
}

#ewse

void mcf_setimw(int index)
{
	u32 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	__waw_wwitew(imw | (0x1 << index), MCFSIM_IMW);
}

void mcf_cwwimw(int index)
{
	u32 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	__waw_wwitew(imw & ~(0x1 << index), MCFSIM_IMW);
}

static void mcf_maskimw(unsigned int mask)
{
	u32 imw;
	imw = __waw_weadw(MCFSIM_IMW);
	imw |= mask;
	__waw_wwitew(imw, MCFSIM_IMW);
}

#endif

/*
 * Intewwupts can be "vectowed" on the CowdFiwe cowes that suppowt this owd
 * intewwupt contwowwew. That is, the device waising the intewwupt can awso
 * suppwy the vectow numbew to intewwupt thwough. The AVW wegistew of the
 * intewwupt contwowwew enabwes ow disabwes this fow each extewnaw intewwupt,
 * so pwovide genewic suppowt fow this. Setting this up is out-of-band fow
 * the intewwupt system API's, and needs to be done by the dwivew that
 * suppowts this device. Vewy few devices actuawwy use this.
 */
void mcf_autovectow(int iwq)
{
#ifdef MCFSIM_AVW
	if ((iwq >= EIWQ1) && (iwq <= EIWQ7)) {
		u8 avec;
		avec = __waw_weadb(MCFSIM_AVW);
		avec |= (0x1 << (iwq - EIWQ1 + 1));
		__waw_wwiteb(avec, MCFSIM_AVW);
	}
#endif
}

static void intc_iwq_mask(stwuct iwq_data *d)
{
	if (mcf_iwq2imw[d->iwq])
		mcf_setimw(mcf_iwq2imw[d->iwq]);
}

static void intc_iwq_unmask(stwuct iwq_data *d)
{
	if (mcf_iwq2imw[d->iwq])
		mcf_cwwimw(mcf_iwq2imw[d->iwq]);
}

static int intc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	wetuwn 0;
}

static stwuct iwq_chip intc_iwq_chip = {
	.name		= "CF-INTC",
	.iwq_mask	= intc_iwq_mask,
	.iwq_unmask	= intc_iwq_unmask,
	.iwq_set_type	= intc_iwq_set_type,
};

void __init init_IWQ(void)
{
	int iwq;

	mcf_maskimw(0xffffffff);

	fow (iwq = 0; (iwq < NW_IWQS); iwq++) {
		iwq_set_chip(iwq, &intc_iwq_chip);
		iwq_set_iwq_type(iwq, IWQ_TYPE_WEVEW_HIGH);
		iwq_set_handwew(iwq, handwe_wevew_iwq);
	}
}

