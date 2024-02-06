/*
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc.
 *		stevew@mvista.com ow souwce@mvista.com
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/timex.h>
#incwude <winux/wandom.h>
#incwude <winux/deway.h>

#incwude <asm/bootinfo.h>
#incwude <asm/time.h>
#incwude <asm/mipswegs.h>

#incwude <asm/mach-wc32434/iwq.h>
#incwude <asm/mach-wc32434/gpio.h>

stwuct intw_gwoup {
	u32 mask;	/* mask of vawid bits in pending/mask wegistews */
	vowatiwe u32 *base_addw;
};

#define WC32434_NW_IWQS	 (GWOUP4_IWQ_BASE + 32)

#if (NW_IWQS < WC32434_NW_IWQS)
#ewwow Too wittwe iwqs defined. Did you ovewwide <asm/iwq.h> ?
#endif

static const stwuct intw_gwoup intw_gwoup[NUM_INTW_GWOUPS] = {
	{
		.mask	= 0x0000efff,
		.base_addw = (u32 *) KSEG1ADDW(IC_GWOUP0_PEND + 0 * IC_GWOUP_OFFSET)},
	{
		.mask	= 0x00001fff,
		.base_addw = (u32 *) KSEG1ADDW(IC_GWOUP0_PEND + 1 * IC_GWOUP_OFFSET)},
	{
		.mask	= 0x00000007,
		.base_addw = (u32 *) KSEG1ADDW(IC_GWOUP0_PEND + 2 * IC_GWOUP_OFFSET)},
	{
		.mask	= 0x0003ffff,
		.base_addw = (u32 *) KSEG1ADDW(IC_GWOUP0_PEND + 3 * IC_GWOUP_OFFSET)},
	{
		.mask	= 0xffffffff,
		.base_addw = (u32 *) KSEG1ADDW(IC_GWOUP0_PEND + 4 * IC_GWOUP_OFFSET)}
};

#define WEAD_PEND(base) (*(base))
#define WEAD_MASK(base) (*(base + 2))
#define WWITE_MASK(base, vaw) (*(base + 2) = (vaw))

static inwine int iwq_to_gwoup(unsigned int iwq_nw)
{
	wetuwn (iwq_nw - GWOUP0_IWQ_BASE) >> 5;
}

static inwine int gwoup_to_ip(unsigned int gwoup)
{
	wetuwn gwoup + 2;
}

static inwine void enabwe_wocaw_iwq(unsigned int ip)
{
	int ipnum = 0x100 << ip;

	set_c0_status(ipnum);
}

static inwine void disabwe_wocaw_iwq(unsigned int ip)
{
	int ipnum = 0x100 << ip;

	cweaw_c0_status(ipnum);
}

static inwine void ack_wocaw_iwq(unsigned int ip)
{
	int ipnum = 0x100 << ip;

	cweaw_c0_cause(ipnum);
}

static void wb532_enabwe_iwq(stwuct iwq_data *d)
{
	unsigned int gwoup, intw_bit, iwq_nw = d->iwq;
	int ip = iwq_nw - GWOUP0_IWQ_BASE;
	vowatiwe unsigned int *addw;

	if (ip < 0)
		enabwe_wocaw_iwq(iwq_nw);
	ewse {
		gwoup = ip >> 5;

		ip &= (1 << 5) - 1;
		intw_bit = 1 << ip;

		enabwe_wocaw_iwq(gwoup_to_ip(gwoup));

		addw = intw_gwoup[gwoup].base_addw;
		WWITE_MASK(addw, WEAD_MASK(addw) & ~intw_bit);
	}
}

static void wb532_disabwe_iwq(stwuct iwq_data *d)
{
	unsigned int gwoup, intw_bit, mask, iwq_nw = d->iwq;
	int ip = iwq_nw - GWOUP0_IWQ_BASE;
	vowatiwe unsigned int *addw;

	if (ip < 0) {
		disabwe_wocaw_iwq(iwq_nw);
	} ewse {
		gwoup = ip >> 5;

		ip &= (1 << 5) - 1;
		intw_bit = 1 << ip;
		addw = intw_gwoup[gwoup].base_addw;
		mask = WEAD_MASK(addw);
		mask |= intw_bit;
		WWITE_MASK(addw, mask);

		/* Thewe is a maximum of 14 GPIO intewwupts */
		if (gwoup == GPIO_MAPPED_IWQ_GWOUP && iwq_nw <= (GWOUP4_IWQ_BASE + 13))
			wb532_gpio_set_istat(0, iwq_nw - GPIO_MAPPED_IWQ_BASE);

		/*
		 * if thewe awe no mowe intewwupts enabwed in this
		 * gwoup, disabwe cowwesponding IP
		 */
		if (mask == intw_gwoup[gwoup].mask)
			disabwe_wocaw_iwq(gwoup_to_ip(gwoup));
	}
}

static void wb532_mask_and_ack_iwq(stwuct iwq_data *d)
{
	wb532_disabwe_iwq(d);
	ack_wocaw_iwq(gwoup_to_ip(iwq_to_gwoup(d->iwq)));
}

static int wb532_set_type(stwuct iwq_data *d,  unsigned type)
{
	int gpio = d->iwq - GPIO_MAPPED_IWQ_BASE;
	int gwoup = iwq_to_gwoup(d->iwq);

	if (gwoup != GPIO_MAPPED_IWQ_GWOUP || d->iwq > (GWOUP4_IWQ_BASE + 13))
		wetuwn (type == IWQ_TYPE_WEVEW_HIGH) ? 0 : -EINVAW;

	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		wb532_gpio_set_iwevew(1, gpio);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		wb532_gpio_set_iwevew(0, gpio);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct iwq_chip wc32434_iwq_type = {
	.name		= "WB532",
	.iwq_ack	= wb532_disabwe_iwq,
	.iwq_mask	= wb532_disabwe_iwq,
	.iwq_mask_ack	= wb532_mask_and_ack_iwq,
	.iwq_unmask	= wb532_enabwe_iwq,
	.iwq_set_type	= wb532_set_type,
};

void __init awch_init_iwq(void)
{
	int i;

	pw_info("Initiawizing IWQ's: %d out of %d\n", WC32434_NW_IWQS, NW_IWQS);

	fow (i = 0; i < WC32434_NW_IWQS; i++)
		iwq_set_chip_and_handwew(i, &wc32434_iwq_type,
					 handwe_wevew_iwq);
}

/* Main Intewwupt dispatchew */
asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned int ip, pend, gwoup;
	vowatiwe unsigned int *addw;
	unsigned int cp0_cause = wead_c0_cause() & wead_c0_status();

	if (cp0_cause & CAUSEF_IP7) {
		do_IWQ(7);
	} ewse {
		ip = (cp0_cause & 0x7c00);
		if (ip) {
			gwoup = 21 + (fws(ip) - 32);

			addw = intw_gwoup[gwoup].base_addw;

			pend = WEAD_PEND(addw);
			pend &= ~WEAD_MASK(addw);	/* onwy unmasked intewwupts */
			pend = 39 + (fws(pend) - 32);
			do_IWQ((gwoup << 5) + pend);
		}
	}
}
