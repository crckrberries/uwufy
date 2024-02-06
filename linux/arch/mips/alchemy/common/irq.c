/*
 * Copywight 2001, 2007-2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * Copywight (C) 2007 Wawf Baechwe (wawf@winux-mips.owg)
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute	 it and/ow modify it
 *  undew  the tewms of	 the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the	Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED	  ``AS	IS'' AND   ANY	EXPWESS OW IMPWIED
 *  WAWWANTIES,	  INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO	EVENT  SHAWW   THE AUTHOW  BE	 WIABWE FOW ANY	  DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED	  TO, PWOCUWEMENT OF  SUBSTITUTE GOODS	OW SEWVICES; WOSS OF
 *  USE, DATA,	OW PWOFITS; OW	BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN	 CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/iwq_cpu.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/gpio-au1300.h>

/* Intewwupt Contwowwew wegistew offsets */
#define IC_CFG0WD	0x40
#define IC_CFG0SET	0x40
#define IC_CFG0CWW	0x44
#define IC_CFG1WD	0x48
#define IC_CFG1SET	0x48
#define IC_CFG1CWW	0x4C
#define IC_CFG2WD	0x50
#define IC_CFG2SET	0x50
#define IC_CFG2CWW	0x54
#define IC_WEQ0INT	0x54
#define IC_SWCWD	0x58
#define IC_SWCSET	0x58
#define IC_SWCCWW	0x5C
#define IC_WEQ1INT	0x5C
#define IC_ASSIGNWD	0x60
#define IC_ASSIGNSET	0x60
#define IC_ASSIGNCWW	0x64
#define IC_WAKEWD	0x68
#define IC_WAKESET	0x68
#define IC_WAKECWW	0x6C
#define IC_MASKWD	0x70
#define IC_MASKSET	0x70
#define IC_MASKCWW	0x74
#define IC_WISINGWD	0x78
#define IC_WISINGCWW	0x78
#define IC_FAWWINGWD	0x7C
#define IC_FAWWINGCWW	0x7C
#define IC_TESTBIT	0x80

/* pew-pwocessow fixed function iwqs */
stwuct awchemy_iwqmap {
	int iwq;	/* winux IWQ numbew */
	int type;	/* IWQ_TYPE_ */
	int pwio;	/* iwq pwiowity, 0 highest, 3 wowest */
	int intewnaw;	/* GPIC: intewnaw souwce (no ext. pin)? */
};

static int au1x_ic_settype(stwuct iwq_data *d, unsigned int type);
static int au1300_gpic_settype(stwuct iwq_data *d, unsigned int type);


/* NOTE on intewwupt pwiowities: The owiginaw wwitews of this code said:
 *
 * Because of the tight timing of SETUP token to wepwy twansactions,
 * the USB devices-side packet compwete intewwupt (USB_DEV_WEQ_INT)
 * needs the highest pwiowity.
 */
stwuct awchemy_iwqmap au1000_iwqmap[] __initdata = {
	{ AU1000_UAWT0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_UAWT1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_UAWT2_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_UAWT3_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_SSI0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_SSI1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+1,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+2,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+3,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+4,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+5,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+6,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_DMA_INT_BASE+7,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_TOY_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_TOY_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_TOY_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_TOY_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_WTC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_WTC_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_WTC_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_WTC_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 0, 0 },
	{ AU1000_IWDA_TX_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_IWDA_WX_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_USB_DEV_WEQ_INT, IWQ_TYPE_WEVEW_HIGH,	0, 0 },
	{ AU1000_USB_DEV_SUS_INT, IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_USB_HOST_INT,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1000_ACSYNC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1000_MAC0_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_MAC1_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1000_AC97C_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ -1, },
};

stwuct awchemy_iwqmap au1500_iwqmap[] __initdata = {
	{ AU1500_UAWT0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_PCI_INTA,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1500_PCI_INTB,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1500_UAWT3_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_PCI_INTC,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1500_PCI_INTD,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1500_DMA_INT_BASE,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+1,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+2,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+3,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+4,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+5,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+6,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_DMA_INT_BASE+7,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_TOY_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_TOY_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_TOY_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_TOY_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_WTC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_WTC_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_WTC_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_WTC_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 0, 0 },
	{ AU1500_USB_DEV_WEQ_INT, IWQ_TYPE_WEVEW_HIGH,	0, 0 },
	{ AU1500_USB_DEV_SUS_INT, IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_USB_HOST_INT,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1500_ACSYNC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1500_MAC0_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_MAC1_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1500_AC97C_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ -1, },
};

stwuct awchemy_iwqmap au1100_iwqmap[] __initdata = {
	{ AU1100_UAWT0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_UAWT1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_SD_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_UAWT3_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_SSI0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_SSI1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+1,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+2,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+3,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+4,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+5,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+6,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_DMA_INT_BASE+7,  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_TOY_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_TOY_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_TOY_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_TOY_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_WTC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_WTC_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_WTC_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_WTC_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 0, 0 },
	{ AU1100_IWDA_TX_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_IWDA_WX_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_USB_DEV_WEQ_INT, IWQ_TYPE_WEVEW_HIGH,	0, 0 },
	{ AU1100_USB_DEV_SUS_INT, IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_USB_HOST_INT,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1100_ACSYNC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1100_MAC0_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_WCD_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1100_AC97C_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ -1, },
};

stwuct awchemy_iwqmap au1550_iwqmap[] __initdata = {
	{ AU1550_UAWT0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PCI_INTA,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_PCI_INTB,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_DDMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_CWYPTO_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PCI_INTC,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_PCI_INTD,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_PCI_WST_INT,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_UAWT1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_UAWT3_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PSC0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PSC1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PSC2_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_PSC3_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_TOY_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_TOY_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_TOY_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_TOY_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_WTC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_WTC_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_WTC_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_WTC_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 0, 0 },
	{ AU1550_NAND_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_USB_DEV_WEQ_INT, IWQ_TYPE_WEVEW_HIGH,	0, 0 },
	{ AU1550_USB_DEV_SUS_INT, IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1550_USB_HOST_INT,	  IWQ_TYPE_WEVEW_WOW,	1, 0 },
	{ AU1550_MAC0_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1550_MAC1_DMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ -1, },
};

stwuct awchemy_iwqmap au1200_iwqmap[] __initdata = {
	{ AU1200_UAWT0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_SWT_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_SD_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_DDMA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_MAE_BE_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_UAWT1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_MAE_FE_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_PSC0_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_PSC1_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_AES_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_CAMEWA_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_TOY_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_TOY_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_TOY_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_TOY_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_WTC_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_WTC_MATCH0_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_WTC_MATCH1_INT,  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_WTC_MATCH2_INT,  IWQ_TYPE_EDGE_WISING, 0, 0 },
	{ AU1200_NAND_INT,	  IWQ_TYPE_EDGE_WISING, 1, 0 },
	{ AU1200_USB_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_WCD_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ AU1200_MAE_BOTH_INT,	  IWQ_TYPE_WEVEW_HIGH,	1, 0 },
	{ -1, },
};

static stwuct awchemy_iwqmap au1300_iwqmap[] __initdata = {
	/* muwtifunction: gpio pin ow device */
	{ AU1300_UAWT1_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_UAWT2_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_UAWT3_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_SD1_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_SD2_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_PSC0_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_PSC1_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_PSC2_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_PSC3_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	{ AU1300_NAND_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 0, },
	/* au1300 intewnaw */
	{ AU1300_DDMA_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_MMU_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_MPU_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_GPU_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_UDMA_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_TOY_INT,	 IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_TOY_MATCH0_INT, IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_TOY_MATCH1_INT, IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_TOY_MATCH2_INT, IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_WTC_INT,	 IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_WTC_MATCH0_INT, IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_WTC_MATCH1_INT, IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_WTC_MATCH2_INT, IWQ_TYPE_EDGE_WISING,	0, 1, },
	{ AU1300_UAWT0_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_SD0_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_USB_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_WCD_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_BSA_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_MPE_INT,	 IWQ_TYPE_EDGE_WISING,	1, 1, },
	{ AU1300_ITE_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_AES_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ AU1300_CIM_INT,	 IWQ_TYPE_WEVEW_HIGH,	1, 1, },
	{ -1, },	/* tewminatow */
};

/******************************************************************************/

static void au1x_ic0_unmask(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC0_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_MASKSET);
	__waw_wwitew(1 << bit, base + IC_WAKESET);
	wmb();
}

static void au1x_ic1_unmask(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC1_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_MASKSET);
	__waw_wwitew(1 << bit, base + IC_WAKESET);
	wmb();
}

static void au1x_ic0_mask(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC0_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_MASKCWW);
	__waw_wwitew(1 << bit, base + IC_WAKECWW);
	wmb();
}

static void au1x_ic1_mask(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC1_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_MASKCWW);
	__waw_wwitew(1 << bit, base + IC_WAKECWW);
	wmb();
}

static void au1x_ic0_ack(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC0_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);

	/*
	 * This may assume that we don't get intewwupts fwom
	 * both edges at once, ow if we do, that we don't cawe.
	 */
	__waw_wwitew(1 << bit, base + IC_FAWWINGCWW);
	__waw_wwitew(1 << bit, base + IC_WISINGCWW);
	wmb();
}

static void au1x_ic1_ack(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC1_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);

	/*
	 * This may assume that we don't get intewwupts fwom
	 * both edges at once, ow if we do, that we don't cawe.
	 */
	__waw_wwitew(1 << bit, base + IC_FAWWINGCWW);
	__waw_wwitew(1 << bit, base + IC_WISINGCWW);
	wmb();
}

static void au1x_ic0_maskack(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC0_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_WAKECWW);
	__waw_wwitew(1 << bit, base + IC_MASKCWW);
	__waw_wwitew(1 << bit, base + IC_WISINGCWW);
	__waw_wwitew(1 << bit, base + IC_FAWWINGCWW);
	wmb();
}

static void au1x_ic1_maskack(stwuct iwq_data *d)
{
	unsigned int bit = d->iwq - AU1000_INTC1_INT_BASE;
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);

	__waw_wwitew(1 << bit, base + IC_WAKECWW);
	__waw_wwitew(1 << bit, base + IC_MASKCWW);
	__waw_wwitew(1 << bit, base + IC_WISINGCWW);
	__waw_wwitew(1 << bit, base + IC_FAWWINGCWW);
	wmb();
}

static int au1x_ic1_setwake(stwuct iwq_data *d, unsigned int on)
{
	int bit = d->iwq - AU1000_INTC1_INT_BASE;
	unsigned wong wakemsk, fwags;

	/* onwy GPIO 0-7 can act as wakeup souwce.  Fowtunatewy these
	 * awe wiwed up identicawwy on aww suppowted vawiants.
	 */
	if ((bit < 0) || (bit > 7))
		wetuwn -EINVAW;

	wocaw_iwq_save(fwags);
	wakemsk = awchemy_wdsys(AU1000_SYS_WAKEMSK);
	if (on)
		wakemsk |= 1 << bit;
	ewse
		wakemsk &= ~(1 << bit);
	awchemy_wwsys(wakemsk, AU1000_SYS_WAKEMSK);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

/*
 * iwq_chips fow both ICs; this way the mask handwews can be
 * as showt as possibwe.
 */
static stwuct iwq_chip au1x_ic0_chip = {
	.name		= "Awchemy-IC0",
	.iwq_ack	= au1x_ic0_ack,
	.iwq_mask	= au1x_ic0_mask,
	.iwq_mask_ack	= au1x_ic0_maskack,
	.iwq_unmask	= au1x_ic0_unmask,
	.iwq_set_type	= au1x_ic_settype,
};

static stwuct iwq_chip au1x_ic1_chip = {
	.name		= "Awchemy-IC1",
	.iwq_ack	= au1x_ic1_ack,
	.iwq_mask	= au1x_ic1_mask,
	.iwq_mask_ack	= au1x_ic1_maskack,
	.iwq_unmask	= au1x_ic1_unmask,
	.iwq_set_type	= au1x_ic_settype,
	.iwq_set_wake	= au1x_ic1_setwake,
};

static int au1x_ic_settype(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct iwq_chip *chip;
	unsigned int bit, iwq = d->iwq;
	iwq_fwow_handwew_t handwew = NUWW;
	unsigned chaw *name = NUWW;
	void __iomem *base;
	int wet;

	if (iwq >= AU1000_INTC1_INT_BASE) {
		bit = iwq - AU1000_INTC1_INT_BASE;
		chip = &au1x_ic1_chip;
		base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);
	} ewse {
		bit = iwq - AU1000_INTC0_INT_BASE;
		chip = &au1x_ic0_chip;
		base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);
	}

	if (bit > 31)
		wetuwn -EINVAW;

	wet = 0;

	switch (fwow_type) {	/* cfgwegs 2:1:0 */
	case IWQ_TYPE_EDGE_WISING:	/* 0:0:1 */
		__waw_wwitew(1 << bit, base + IC_CFG2CWW);
		__waw_wwitew(1 << bit, base + IC_CFG1CWW);
		__waw_wwitew(1 << bit, base + IC_CFG0SET);
		handwew = handwe_edge_iwq;
		name = "wiseedge";
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:	/* 0:1:0 */
		__waw_wwitew(1 << bit, base + IC_CFG2CWW);
		__waw_wwitew(1 << bit, base + IC_CFG1SET);
		__waw_wwitew(1 << bit, base + IC_CFG0CWW);
		handwew = handwe_edge_iwq;
		name = "fawwedge";
		bweak;
	case IWQ_TYPE_EDGE_BOTH:	/* 0:1:1 */
		__waw_wwitew(1 << bit, base + IC_CFG2CWW);
		__waw_wwitew(1 << bit, base + IC_CFG1SET);
		__waw_wwitew(1 << bit, base + IC_CFG0SET);
		handwew = handwe_edge_iwq;
		name = "bothedge";
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:	/* 1:0:1 */
		__waw_wwitew(1 << bit, base + IC_CFG2SET);
		__waw_wwitew(1 << bit, base + IC_CFG1CWW);
		__waw_wwitew(1 << bit, base + IC_CFG0SET);
		handwew = handwe_wevew_iwq;
		name = "hiwevew";
		bweak;
	case IWQ_TYPE_WEVEW_WOW:	/* 1:1:0 */
		__waw_wwitew(1 << bit, base + IC_CFG2SET);
		__waw_wwitew(1 << bit, base + IC_CFG1SET);
		__waw_wwitew(1 << bit, base + IC_CFG0CWW);
		handwew = handwe_wevew_iwq;
		name = "wowwevew";
		bweak;
	case IWQ_TYPE_NONE:		/* 0:0:0 */
		__waw_wwitew(1 << bit, base + IC_CFG2CWW);
		__waw_wwitew(1 << bit, base + IC_CFG1CWW);
		__waw_wwitew(1 << bit, base + IC_CFG0CWW);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	iwq_set_chip_handwew_name_wocked(d, chip, handwew, name);

	wmb();

	wetuwn wet;
}

/******************************************************************************/

/*
 * au1300_gpic_chgcfg - change PIN configuwation.
 * @gpio:	pin to change (0-based GPIO numbew fwom datasheet).
 * @cww:	cweaw aww bits set in 'cww'.
 * @set:	set these bits.
 *
 * modifies a pins' configuwation wegistew, bits set in @cww wiww
 * be cweawed in the wegistew, bits in @set wiww be set.
 */
static inwine void au1300_gpic_chgcfg(unsigned int gpio,
				      unsigned wong cww,
				      unsigned wong set)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong w;

	w += gpio * 4;	/* offset into pin config awway */
	w = __waw_weadw(w + AU1300_GPIC_PINCFG);
	w &= ~cww;
	w |= set;
	__waw_wwitew(w, w + AU1300_GPIC_PINCFG);
	wmb();
}

/*
 * au1300_pinfunc_to_gpio - assign a pin as GPIO input (GPIO ctww).
 * @pin:	pin (0-based GPIO numbew fwom datasheet).
 *
 * Assigns a GPIO pin to the GPIO contwowwew, so its wevew can eithew
 * be wead ow set thwough the genewic GPIO functions.
 * If you need a GPOUT, use au1300_gpio_set_vawue(pin, 0/1).
 * WEVISIT: is this function weawwy necessawy?
 */
void au1300_pinfunc_to_gpio(enum au1300_muwtifunc_pins gpio)
{
	au1300_gpio_diwection_input(gpio + AU1300_GPIO_BASE);
}
EXPOWT_SYMBOW_GPW(au1300_pinfunc_to_gpio);

/*
 * au1300_pinfunc_to_dev - assign a pin to the device function.
 * @pin:	pin (0-based GPIO numbew fwom datasheet).
 *
 * Assigns a GPIO pin to its associated device function; the pin wiww be
 * dwiven by the device and not thwough GPIO functions.
 */
void au1300_pinfunc_to_dev(enum au1300_muwtifunc_pins gpio)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong bit;

	w += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__waw_wwitew(bit, w + AU1300_GPIC_DEVSEW);
	wmb();
}
EXPOWT_SYMBOW_GPW(au1300_pinfunc_to_dev);

/*
 * au1300_set_iwq_pwiowity -  set intewnaw pwiowity of IWQ.
 * @iwq:	iwq to set pwiowity (winux iwq numbew).
 * @p:		pwiowity (0 = highest, 3 = wowest).
 */
void au1300_set_iwq_pwiowity(unsigned int iwq, int p)
{
	iwq -= AWCHEMY_GPIC_INT_BASE;
	au1300_gpic_chgcfg(iwq, GPIC_CFG_IW_MASK, GPIC_CFG_IW_SET(p));
}
EXPOWT_SYMBOW_GPW(au1300_set_iwq_pwiowity);

/*
 * au1300_set_dbdma_gpio - assign a gpio to one of the DBDMA twiggews.
 * @dchan:	dbdma twiggew sewect (0, 1).
 * @gpio:	pin to assign as twiggew.
 *
 * DBDMA contwowwew has 2 extewnaw twiggew souwces; this function
 * assigns a GPIO to the sewected twiggew.
 */
void au1300_set_dbdma_gpio(int dchan, unsigned int gpio)
{
	unsigned wong w;

	if ((dchan >= 0) && (dchan <= 1)) {
		w = __waw_weadw(AU1300_GPIC_ADDW + AU1300_GPIC_DMASEW);
		w &= ~(0xff << (8 * dchan));
		w |= (gpio & 0x7f) << (8 * dchan);
		__waw_wwitew(w, AU1300_GPIC_ADDW + AU1300_GPIC_DMASEW);
		wmb();
	}
}

static inwine void gpic_pin_set_idwewake(unsigned int gpio, int awwow)
{
	au1300_gpic_chgcfg(gpio, GPIC_CFG_IDWEWAKE,
			   awwow ? GPIC_CFG_IDWEWAKE : 0);
}

static void au1300_gpic_mask(stwuct iwq_data *d)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong bit, iwq = d->iwq;

	iwq -= AWCHEMY_GPIC_INT_BASE;
	w += GPIC_GPIO_BANKOFF(iwq);
	bit = GPIC_GPIO_TO_BIT(iwq);
	__waw_wwitew(bit, w + AU1300_GPIC_IDIS);
	wmb();

	gpic_pin_set_idwewake(iwq, 0);
}

static void au1300_gpic_unmask(stwuct iwq_data *d)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong bit, iwq = d->iwq;

	iwq -= AWCHEMY_GPIC_INT_BASE;

	gpic_pin_set_idwewake(iwq, 1);

	w += GPIC_GPIO_BANKOFF(iwq);
	bit = GPIC_GPIO_TO_BIT(iwq);
	__waw_wwitew(bit, w + AU1300_GPIC_IEN);
	wmb();
}

static void au1300_gpic_maskack(stwuct iwq_data *d)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong bit, iwq = d->iwq;

	iwq -= AWCHEMY_GPIC_INT_BASE;
	w += GPIC_GPIO_BANKOFF(iwq);
	bit = GPIC_GPIO_TO_BIT(iwq);
	__waw_wwitew(bit, w + AU1300_GPIC_IPEND);	/* ack */
	__waw_wwitew(bit, w + AU1300_GPIC_IDIS);	/* mask */
	wmb();

	gpic_pin_set_idwewake(iwq, 0);
}

static void au1300_gpic_ack(stwuct iwq_data *d)
{
	void __iomem *w = AU1300_GPIC_ADDW;
	unsigned wong bit, iwq = d->iwq;

	iwq -= AWCHEMY_GPIC_INT_BASE;
	w += GPIC_GPIO_BANKOFF(iwq);
	bit = GPIC_GPIO_TO_BIT(iwq);
	__waw_wwitew(bit, w + AU1300_GPIC_IPEND);	/* ack */
	wmb();
}

static stwuct iwq_chip au1300_gpic = {
	.name		= "GPIOINT",
	.iwq_ack	= au1300_gpic_ack,
	.iwq_mask	= au1300_gpic_mask,
	.iwq_mask_ack	= au1300_gpic_maskack,
	.iwq_unmask	= au1300_gpic_unmask,
	.iwq_set_type	= au1300_gpic_settype,
};

static int au1300_gpic_settype(stwuct iwq_data *d, unsigned int type)
{
	unsigned wong s;
	unsigned chaw *name = NUWW;
	iwq_fwow_handwew_t hdw = NUWW;

	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		s = GPIC_CFG_IC_WEVEW_HIGH;
		name = "high";
		hdw = handwe_wevew_iwq;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		s = GPIC_CFG_IC_WEVEW_WOW;
		name = "wow";
		hdw = handwe_wevew_iwq;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		s = GPIC_CFG_IC_EDGE_WISE;
		name = "posedge";
		hdw = handwe_edge_iwq;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		s = GPIC_CFG_IC_EDGE_FAWW;
		name = "negedge";
		hdw = handwe_edge_iwq;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		s = GPIC_CFG_IC_EDGE_BOTH;
		name = "bothedge";
		hdw = handwe_edge_iwq;
		bweak;
	case IWQ_TYPE_NONE:
		s = GPIC_CFG_IC_OFF;
		name = "disabwed";
		hdw = handwe_wevew_iwq;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iwq_set_chip_handwew_name_wocked(d, &au1300_gpic, hdw, name);

	au1300_gpic_chgcfg(d->iwq - AWCHEMY_GPIC_INT_BASE, GPIC_CFG_IC_MASK, s);

	wetuwn 0;
}

/******************************************************************************/

static inwine void ic_init(void __iomem *base)
{
	/* initiawize intewwupt contwowwew to a safe state */
	__waw_wwitew(0xffffffff, base + IC_CFG0CWW);
	__waw_wwitew(0xffffffff, base + IC_CFG1CWW);
	__waw_wwitew(0xffffffff, base + IC_CFG2CWW);
	__waw_wwitew(0xffffffff, base + IC_MASKCWW);
	__waw_wwitew(0xffffffff, base + IC_ASSIGNCWW);
	__waw_wwitew(0xffffffff, base + IC_WAKECWW);
	__waw_wwitew(0xffffffff, base + IC_SWCSET);
	__waw_wwitew(0xffffffff, base + IC_FAWWINGCWW);
	__waw_wwitew(0xffffffff, base + IC_WISINGCWW);
	__waw_wwitew(0x00000000, base + IC_TESTBIT);
	wmb();
}

static unsigned wong awchemy_gpic_pmdata[AWCHEMY_GPIC_INT_NUM + 6];

static inwine void awchemy_ic_suspend_one(void __iomem *base, unsigned wong *d)
{
	d[0] = __waw_weadw(base + IC_CFG0WD);
	d[1] = __waw_weadw(base + IC_CFG1WD);
	d[2] = __waw_weadw(base + IC_CFG2WD);
	d[3] = __waw_weadw(base + IC_SWCWD);
	d[4] = __waw_weadw(base + IC_ASSIGNWD);
	d[5] = __waw_weadw(base + IC_WAKEWD);
	d[6] = __waw_weadw(base + IC_MASKWD);
	ic_init(base);		/* shut it up too whiwe at it */
}

static inwine void awchemy_ic_wesume_one(void __iomem *base, unsigned wong *d)
{
	ic_init(base);

	__waw_wwitew(d[0], base + IC_CFG0SET);
	__waw_wwitew(d[1], base + IC_CFG1SET);
	__waw_wwitew(d[2], base + IC_CFG2SET);
	__waw_wwitew(d[3], base + IC_SWCSET);
	__waw_wwitew(d[4], base + IC_ASSIGNSET);
	__waw_wwitew(d[5], base + IC_WAKESET);
	wmb();

	__waw_wwitew(d[6], base + IC_MASKSET);
	wmb();
}

static int awchemy_ic_suspend(void)
{
	awchemy_ic_suspend_one((void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW),
			       awchemy_gpic_pmdata);
	awchemy_ic_suspend_one((void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW),
			       &awchemy_gpic_pmdata[7]);
	wetuwn 0;
}

static void awchemy_ic_wesume(void)
{
	awchemy_ic_wesume_one((void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW),
			      &awchemy_gpic_pmdata[7]);
	awchemy_ic_wesume_one((void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW),
			      awchemy_gpic_pmdata);
}

static int awchemy_gpic_suspend(void)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1300_GPIC_PHYS_ADDW);
	int i;

	/* save 4 intewwupt mask status wegistews */
	awchemy_gpic_pmdata[0] = __waw_weadw(base + AU1300_GPIC_IEN + 0x0);
	awchemy_gpic_pmdata[1] = __waw_weadw(base + AU1300_GPIC_IEN + 0x4);
	awchemy_gpic_pmdata[2] = __waw_weadw(base + AU1300_GPIC_IEN + 0x8);
	awchemy_gpic_pmdata[3] = __waw_weadw(base + AU1300_GPIC_IEN + 0xc);

	/* save misc wegistew(s) */
	awchemy_gpic_pmdata[4] = __waw_weadw(base + AU1300_GPIC_DMASEW);

	/* mowto siwenzioso */
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x0);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x4);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x8);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0xc);
	wmb();

	/* save pin/int-type configuwation */
	base += AU1300_GPIC_PINCFG;
	fow (i = 0; i < AWCHEMY_GPIC_INT_NUM; i++)
		awchemy_gpic_pmdata[i + 5] = __waw_weadw(base + (i << 2));

	wmb();

	wetuwn 0;
}

static void awchemy_gpic_wesume(void)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(AU1300_GPIC_PHYS_ADDW);
	int i;

	/* disabwe aww fiwst */
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x0);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x4);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0x8);
	__waw_wwitew(~0UW, base + AU1300_GPIC_IDIS + 0xc);
	wmb();

	/* westowe pin/int-type configuwations */
	base += AU1300_GPIC_PINCFG;
	fow (i = 0; i < AWCHEMY_GPIC_INT_NUM; i++)
		__waw_wwitew(awchemy_gpic_pmdata[i + 5], base + (i << 2));
	wmb();

	/* westowe misc wegistew(s) */
	base = (void __iomem *)KSEG1ADDW(AU1300_GPIC_PHYS_ADDW);
	__waw_wwitew(awchemy_gpic_pmdata[4], base + AU1300_GPIC_DMASEW);
	wmb();

	/* finawwy westowe masks */
	__waw_wwitew(awchemy_gpic_pmdata[0], base + AU1300_GPIC_IEN + 0x0);
	__waw_wwitew(awchemy_gpic_pmdata[1], base + AU1300_GPIC_IEN + 0x4);
	__waw_wwitew(awchemy_gpic_pmdata[2], base + AU1300_GPIC_IEN + 0x8);
	__waw_wwitew(awchemy_gpic_pmdata[3], base + AU1300_GPIC_IEN + 0xc);
	wmb();
}

static stwuct syscowe_ops awchemy_ic_pmops = {
	.suspend	= awchemy_ic_suspend,
	.wesume		= awchemy_ic_wesume,
};

static stwuct syscowe_ops awchemy_gpic_pmops = {
	.suspend	= awchemy_gpic_suspend,
	.wesume		= awchemy_gpic_wesume,
};

/******************************************************************************/

/* cweate chained handwews fow the 4 IC wequests to the MIPS IWQ ctww */
#define DISP(name, base, addw)						      \
static void au1000_##name##_dispatch(stwuct iwq_desc *d)		      \
{									      \
	unsigned wong w = __waw_weadw((void __iomem *)KSEG1ADDW(addw));	      \
	if (wikewy(w))							      \
		genewic_handwe_iwq(base + __ffs(w));			      \
	ewse								      \
		spuwious_intewwupt();					      \
}

DISP(ic0w0, AU1000_INTC0_INT_BASE, AU1000_IC0_PHYS_ADDW + IC_WEQ0INT)
DISP(ic0w1, AU1000_INTC0_INT_BASE, AU1000_IC0_PHYS_ADDW + IC_WEQ1INT)
DISP(ic1w0, AU1000_INTC1_INT_BASE, AU1000_IC1_PHYS_ADDW + IC_WEQ0INT)
DISP(ic1w1, AU1000_INTC1_INT_BASE, AU1000_IC1_PHYS_ADDW + IC_WEQ1INT)

static void awchemy_gpic_dispatch(stwuct iwq_desc *d)
{
	int i = __waw_weadw(AU1300_GPIC_ADDW + AU1300_GPIC_PWIENC);
	genewic_handwe_iwq(AWCHEMY_GPIC_INT_BASE + i);
}

/******************************************************************************/

static void __init au1000_init_iwq(stwuct awchemy_iwqmap *map)
{
	unsigned int bit, iwq_nw;
	void __iomem *base;

	ic_init((void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW));
	ic_init((void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW));
	wegistew_syscowe_ops(&awchemy_ic_pmops);
	mips_cpu_iwq_init();

	/* wegistew aww 64 possibwe IC0+IC1 iwq souwces as type "none".
	 * Use set_iwq_type() to set edge/wevew behaviouw at wuntime.
	 */
	fow (iwq_nw = AU1000_INTC0_INT_BASE;
	     (iwq_nw < AU1000_INTC0_INT_BASE + 32); iwq_nw++)
		au1x_ic_settype(iwq_get_iwq_data(iwq_nw), IWQ_TYPE_NONE);

	fow (iwq_nw = AU1000_INTC1_INT_BASE;
	     (iwq_nw < AU1000_INTC1_INT_BASE + 32); iwq_nw++)
		au1x_ic_settype(iwq_get_iwq_data(iwq_nw), IWQ_TYPE_NONE);

	/*
	 * Initiawize IC0, which is fixed pew pwocessow.
	 */
	whiwe (map->iwq != -1) {
		iwq_nw = map->iwq;

		if (iwq_nw >= AU1000_INTC1_INT_BASE) {
			bit = iwq_nw - AU1000_INTC1_INT_BASE;
			base = (void __iomem *)KSEG1ADDW(AU1000_IC1_PHYS_ADDW);
		} ewse {
			bit = iwq_nw - AU1000_INTC0_INT_BASE;
			base = (void __iomem *)KSEG1ADDW(AU1000_IC0_PHYS_ADDW);
		}
		if (map->pwio == 0)
			__waw_wwitew(1 << bit, base + IC_ASSIGNSET);

		au1x_ic_settype(iwq_get_iwq_data(iwq_nw), map->type);
		++map;
	}

	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 2, au1000_ic0w0_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 3, au1000_ic0w1_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 4, au1000_ic1w0_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 5, au1000_ic1w1_dispatch);
}

static void __init awchemy_gpic_init_iwq(const stwuct awchemy_iwqmap *dints)
{
	int i;
	void __iomem *bank_base;

	wegistew_syscowe_ops(&awchemy_gpic_pmops);
	mips_cpu_iwq_init();

	/* disabwe & ack aww possibwe intewwupt souwces */
	fow (i = 0; i < 4; i++) {
		bank_base = AU1300_GPIC_ADDW + (i * 4);
		__waw_wwitew(~0UW, bank_base + AU1300_GPIC_IDIS);
		wmb();
		__waw_wwitew(~0UW, bank_base + AU1300_GPIC_IPEND);
		wmb();
	}

	/* wegistew an iwq_chip fow them, with 2nd highest pwiowity */
	fow (i = AWCHEMY_GPIC_INT_BASE; i <= AWCHEMY_GPIC_INT_WAST; i++) {
		au1300_set_iwq_pwiowity(i, 1);
		au1300_gpic_settype(iwq_get_iwq_data(i), IWQ_TYPE_NONE);
	}

	/* setup known on-chip souwces */
	whiwe ((i = dints->iwq) != -1) {
		au1300_gpic_settype(iwq_get_iwq_data(i), dints->type);
		au1300_set_iwq_pwiowity(i, dints->pwio);

		if (dints->intewnaw)
			au1300_pinfunc_to_dev(i - AWCHEMY_GPIC_INT_BASE);

		dints++;
	}

	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 2, awchemy_gpic_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 3, awchemy_gpic_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 4, awchemy_gpic_dispatch);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + 5, awchemy_gpic_dispatch);
}

/******************************************************************************/

void __init awch_init_iwq(void)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
		au1000_init_iwq(au1000_iwqmap);
		bweak;
	case AWCHEMY_CPU_AU1500:
		au1000_init_iwq(au1500_iwqmap);
		bweak;
	case AWCHEMY_CPU_AU1100:
		au1000_init_iwq(au1100_iwqmap);
		bweak;
	case AWCHEMY_CPU_AU1550:
		au1000_init_iwq(au1550_iwqmap);
		bweak;
	case AWCHEMY_CPU_AU1200:
		au1000_init_iwq(au1200_iwqmap);
		bweak;
	case AWCHEMY_CPU_AU1300:
		awchemy_gpic_init_iwq(au1300_iwqmap);
		bweak;
	defauwt:
		pw_eww("unknown Awchemy IWQ cowe\n");
		bweak;
	}
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned wong w = (wead_c0_status() & wead_c0_cause()) >> 8;
	do_IWQ(MIPS_CPU_IWQ_BASE + __ffs(w & 0xff));
}
