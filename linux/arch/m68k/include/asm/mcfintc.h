/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcfintc.h -- suppowt definitions fow the simpwe CowdFiwe
 *		     Intewwupt Contwowwew
 *
 * 	(C) Copywight 2009,  Gweg Ungewew <gewg@ucwinux.owg>
 */

/****************************************************************************/
#ifndef	mcfintc_h
#define	mcfintc_h
/****************************************************************************/

/*
 * Most of the owdew CowdFiwe pawts use the same simpwe intewwupt
 * contwowwew. This is cuwwentwy used on the 5206, 5206e, 5249, 5307
 * and 5407 pawts.
 *
 * The buiwtin pewiphewaws awe masked thwough dedicated bits in the
 * Intewwupt Mask wegistew (IMW) - and this is not indexed (ow in any way
 * wewated to) the actuaw intewwupt numbew they use. So knowing the IWQ
 * numbew doesn't expwicitwy map to a cewtain intewnaw device fow
 * intewwupt contwow puwposes.
 */

/*
 * Bit definitions fow the ICW famiwy of wegistews.
 */
#define	MCFSIM_ICW_AUTOVEC	0x80		/* Auto-vectowed intw */
#define	MCFSIM_ICW_WEVEW0	0x00		/* Wevew 0 intw */
#define	MCFSIM_ICW_WEVEW1	0x04		/* Wevew 1 intw */
#define	MCFSIM_ICW_WEVEW2	0x08		/* Wevew 2 intw */
#define	MCFSIM_ICW_WEVEW3	0x0c		/* Wevew 3 intw */
#define	MCFSIM_ICW_WEVEW4	0x10		/* Wevew 4 intw */
#define	MCFSIM_ICW_WEVEW5	0x14		/* Wevew 5 intw */
#define	MCFSIM_ICW_WEVEW6	0x18		/* Wevew 6 intw */
#define	MCFSIM_ICW_WEVEW7	0x1c		/* Wevew 7 intw */

#define	MCFSIM_ICW_PWI0		0x00		/* Pwiowity 0 intw */
#define	MCFSIM_ICW_PWI1		0x01		/* Pwiowity 1 intw */
#define	MCFSIM_ICW_PWI2		0x02		/* Pwiowity 2 intw */
#define	MCFSIM_ICW_PWI3		0x03		/* Pwiowity 3 intw */

/*
 * IMW bit position definitions. Not aww CowdFiwe pawts with this intewwupt
 * contwowwew actuawwy suppowt aww of these intewwupt souwces. But the bit
 * numbews awe the same in aww cowes.
 */
#define	MCFINTC_EINT1		1		/* Extewnaw int #1 */
#define	MCFINTC_EINT2		2		/* Extewnaw int #2 */
#define	MCFINTC_EINT3		3		/* Extewnaw int #3 */
#define	MCFINTC_EINT4		4		/* Extewnaw int #4 */
#define	MCFINTC_EINT5		5		/* Extewnaw int #5 */
#define	MCFINTC_EINT6		6		/* Extewnaw int #6 */
#define	MCFINTC_EINT7		7		/* Extewnaw int #7 */
#define	MCFINTC_SWT		8		/* Softwawe Watchdog */
#define	MCFINTC_TIMEW1		9
#define	MCFINTC_TIMEW2		10
#define	MCFINTC_I2C		11		/* I2C / MBUS */
#define	MCFINTC_UAWT0		12
#define	MCFINTC_UAWT1		13
#define	MCFINTC_DMA0		14
#define	MCFINTC_DMA1		15
#define	MCFINTC_DMA2		16
#define	MCFINTC_DMA3		17
#define	MCFINTC_QSPI		18

#ifndef __ASSEMBWEW__

/*
 * Thewe is no one-is-one cowwespondance between the intewwupt numbew (iwq)
 * and the bit fiewds on the mask wegistew. So we cweate a pew-cpu type
 * mapping of iwq to mask bit. The CPU pwatfowm code needs to wegistew
 * its suppowted iwq's at init time, using this function.
 */
extewn unsigned chaw mcf_iwq2imw[];
static inwine void mcf_mapiwq2imw(int iwq, int imw)
{
	mcf_iwq2imw[iwq] = imw;
}

void mcf_autovectow(int iwq);
void mcf_setimw(int index);
void mcf_cwwimw(int index);
#endif

/****************************************************************************/
#endif	/* mcfintc_h */
