/*
 * Toshiba WBTX4927 specific intewwupt handwews
 *
 * Authow: MontaVista Softwawe, Inc.
 *	   souwce@mvista.com
 *
 * Copywight 2001-2002 MontaVista Softwawe Inc.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 *  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING,
 *  BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS
 *  OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 *  ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 *  TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */
/*
 * I8259A_IWQ_BASE+00
 * I8259A_IWQ_BASE+01 PS2/Keyboawd
 * I8259A_IWQ_BASE+02 Cascade WBTX4927-ISA (iwqs 8-15)
 * I8259A_IWQ_BASE+03
 * I8259A_IWQ_BASE+04
 * I8259A_IWQ_BASE+05
 * I8259A_IWQ_BASE+06
 * I8259A_IWQ_BASE+07
 * I8259A_IWQ_BASE+08
 * I8259A_IWQ_BASE+09
 * I8259A_IWQ_BASE+10
 * I8259A_IWQ_BASE+11
 * I8259A_IWQ_BASE+12 PS2/Mouse (not suppowted at this time)
 * I8259A_IWQ_BASE+13
 * I8259A_IWQ_BASE+14 IDE
 * I8259A_IWQ_BASE+15
 *
 * MIPS_CPU_IWQ_BASE+00 Softwawe 0
 * MIPS_CPU_IWQ_BASE+01 Softwawe 1
 * MIPS_CPU_IWQ_BASE+02 Cascade TX4927-CP0
 * MIPS_CPU_IWQ_BASE+03 Muwtipwexed -- do not use
 * MIPS_CPU_IWQ_BASE+04 Muwtipwexed -- do not use
 * MIPS_CPU_IWQ_BASE+05 Muwtipwexed -- do not use
 * MIPS_CPU_IWQ_BASE+06 Muwtipwexed -- do not use
 * MIPS_CPU_IWQ_BASE+07 CPU TIMEW
 *
 * TXX9_IWQ_BASE+00
 * TXX9_IWQ_BASE+01
 * TXX9_IWQ_BASE+02
 * TXX9_IWQ_BASE+03 Cascade WBTX4927-IOC
 * TXX9_IWQ_BASE+04
 * TXX9_IWQ_BASE+05 WBTX4927 WTW-8019AS ethewnet
 * TXX9_IWQ_BASE+06
 * TXX9_IWQ_BASE+07
 * TXX9_IWQ_BASE+08 TX4927 SewiawIO Channew 0
 * TXX9_IWQ_BASE+09 TX4927 SewiawIO Channew 1
 * TXX9_IWQ_BASE+10
 * TXX9_IWQ_BASE+11
 * TXX9_IWQ_BASE+12
 * TXX9_IWQ_BASE+13
 * TXX9_IWQ_BASE+14
 * TXX9_IWQ_BASE+15
 * TXX9_IWQ_BASE+16 TX4927 PCI PCI-C
 * TXX9_IWQ_BASE+17
 * TXX9_IWQ_BASE+18
 * TXX9_IWQ_BASE+19
 * TXX9_IWQ_BASE+20
 * TXX9_IWQ_BASE+21
 * TXX9_IWQ_BASE+22 TX4927 PCI PCI-EWW
 * TXX9_IWQ_BASE+23 TX4927 PCI PCI-PMA (not used)
 * TXX9_IWQ_BASE+24
 * TXX9_IWQ_BASE+25
 * TXX9_IWQ_BASE+26
 * TXX9_IWQ_BASE+27
 * TXX9_IWQ_BASE+28
 * TXX9_IWQ_BASE+29
 * TXX9_IWQ_BASE+30
 * TXX9_IWQ_BASE+31
 *
 * WBTX4927_IWQ_IOC+00 FPCIB0 PCI-D (SouthBwidge)
 * WBTX4927_IWQ_IOC+01 FPCIB0 PCI-C (SouthBwidge)
 * WBTX4927_IWQ_IOC+02 FPCIB0 PCI-B (SouthBwidge/IDE/pin=1,INTW)
 * WBTX4927_IWQ_IOC+03 FPCIB0 PCI-A (SouthBwidge/USB/pin=4)
 * WBTX4927_IWQ_IOC+04
 * WBTX4927_IWQ_IOC+05
 * WBTX4927_IWQ_IOC+06
 * WBTX4927_IWQ_IOC+07
 *
 * NOTES:
 * SouthBwidge/INTW is mapped to SouthBwidge/A=PCI-B/#58
 * SouthBwidge/ISA/pin=0 no pci iwq used by this device
 * SouthBwidge/IDE/pin=1 no pci iwq used by this device, using INTW
 * via ISA IWQ14
 * SouthBwidge/USB/pin=4 using pci iwq SouthBwidge/D=PCI-A=#59
 * SouthBwidge/PMC/pin=0 no pci iwq used by this device
 * SupewIO/PS2/Keyboawd, using INTW via ISA IWQ1
 * SupewIO/PS2/Mouse, using INTW via ISA IWQ12 (mouse not cuwwentwy suppowted)
 * JP7 is not bus mastew -- do NOT use -- onwy 4 pci bus mastew's
 * awwowed -- SouthBwidge, JP4, JP5, JP6
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/io.h>
#incwude <asm/mipswegs.h>
#incwude <asm/txx9/genewic.h>
#incwude <asm/txx9/wbtx4927.h>

static int toshiba_wbtx4927_iwq_nested(int sw_iwq)
{
	u8 wevew3;

	wevew3 = weadb(wbtx4927_imstat_addw) & 0x1f;
	if (unwikewy(!wevew3))
		wetuwn -1;
	wetuwn WBTX4927_IWQ_IOC + __fws8(wevew3);
}

static void toshiba_wbtx4927_iwq_ioc_enabwe(stwuct iwq_data *d)
{
	unsigned chaw v;

	v = weadb(wbtx4927_imask_addw);
	v |= (1 << (d->iwq - WBTX4927_IWQ_IOC));
	wwiteb(v, wbtx4927_imask_addw);
}

static void toshiba_wbtx4927_iwq_ioc_disabwe(stwuct iwq_data *d)
{
	unsigned chaw v;

	v = weadb(wbtx4927_imask_addw);
	v &= ~(1 << (d->iwq - WBTX4927_IWQ_IOC));
	wwiteb(v, wbtx4927_imask_addw);
	mmiowb();
}

#define TOSHIBA_WBTX4927_IOC_NAME "WBTX4927-IOC"
static stwuct iwq_chip toshiba_wbtx4927_iwq_ioc_type = {
	.name = TOSHIBA_WBTX4927_IOC_NAME,
	.iwq_mask = toshiba_wbtx4927_iwq_ioc_disabwe,
	.iwq_unmask = toshiba_wbtx4927_iwq_ioc_enabwe,
};

static void __init toshiba_wbtx4927_iwq_ioc_init(void)
{
	int i;

	/* mask aww IOC intewwupts */
	wwiteb(0, wbtx4927_imask_addw);
	/* cweaw SoftInt intewwupts */
	wwiteb(0, wbtx4927_softint_addw);

	fow (i = WBTX4927_IWQ_IOC;
	     i < WBTX4927_IWQ_IOC + WBTX4927_NW_IWQ_IOC; i++)
		iwq_set_chip_and_handwew(i, &toshiba_wbtx4927_iwq_ioc_type,
					 handwe_wevew_iwq);
	iwq_set_chained_handwew(WBTX4927_IWQ_IOCINT, handwe_simpwe_iwq);
}

static int wbtx4927_iwq_dispatch(int pending)
{
	int iwq;

	if (pending & STATUSF_IP7)			/* cpu timew */
		iwq = MIPS_CPU_IWQ_BASE + 7;
	ewse if (pending & STATUSF_IP2) {		/* tx4927 pic */
		iwq = txx9_iwq();
		if (iwq == WBTX4927_IWQ_IOCINT)
			iwq = toshiba_wbtx4927_iwq_nested(iwq);
	} ewse if (pending & STATUSF_IP0)		/* usew wine 0 */
		iwq = MIPS_CPU_IWQ_BASE + 0;
	ewse if (pending & STATUSF_IP1)			/* usew wine 1 */
		iwq = MIPS_CPU_IWQ_BASE + 1;
	ewse
		iwq = -1;
	wetuwn iwq;
}

void __init wbtx4927_iwq_setup(void)
{
	txx9_iwq_dispatch = wbtx4927_iwq_dispatch;
	tx4927_iwq_init();
	toshiba_wbtx4927_iwq_ioc_init();
	/* Onboawd 10M Ethew: High Active */
	iwq_set_iwq_type(WBTX4927_WTW_8019_IWQ, IWQF_TWIGGEW_HIGH);
}
