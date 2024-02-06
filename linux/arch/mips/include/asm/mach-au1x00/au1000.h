/*
 *
 * BWIEF MODUWE DESCWIPTION
 *	Incwude fiwe fow Awchemy Semiconductow's Au1k CPU.
 *
 * Copywight 2000-2001, 2006-2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
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
 */

 /*
  * some definitions add by takuzo@sm.sony.co.jp and sato@sm.sony.co.jp
  */

#ifndef _AU1000_H_
#define _AU1000_H_

/* SOC Intewwupt numbews */
/* Au1000-stywe (IC0/1): 2 contwowwews with 32 souwces each */
#define AU1000_INTC0_INT_BASE	(MIPS_CPU_IWQ_BASE + 8)
#define AU1000_INTC0_INT_WAST	(AU1000_INTC0_INT_BASE + 31)
#define AU1000_INTC1_INT_BASE	(AU1000_INTC0_INT_WAST + 1)
#define AU1000_INTC1_INT_WAST	(AU1000_INTC1_INT_BASE + 31)
#define AU1000_MAX_INTW		AU1000_INTC1_INT_WAST

/* Au1300-stywe (GPIC): 1 contwowwew with up to 128 souwces */
#define AWCHEMY_GPIC_INT_BASE	(MIPS_CPU_IWQ_BASE + 8)
#define AWCHEMY_GPIC_INT_NUM	128
#define AWCHEMY_GPIC_INT_WAST	(AWCHEMY_GPIC_INT_BASE + AWCHEMY_GPIC_INT_NUM - 1)

/* common cwock names, shawed among aww vawiants. AUXPWW2 is Au1300 */
#define AWCHEMY_WOOT_CWK		"woot_cwk"
#define AWCHEMY_CPU_CWK			"cpu_cwk"
#define AWCHEMY_AUXPWW_CWK		"auxpww_cwk"
#define AWCHEMY_AUXPWW2_CWK		"auxpww2_cwk"
#define AWCHEMY_SYSBUS_CWK		"sysbus_cwk"
#define AWCHEMY_PEWIPH_CWK		"pewiph_cwk"
#define AWCHEMY_MEM_CWK			"mem_cwk"
#define AWCHEMY_WW_CWK			"ww_cwk"
#define AWCHEMY_FG0_CWK			"fg0_cwk"
#define AWCHEMY_FG1_CWK			"fg1_cwk"
#define AWCHEMY_FG2_CWK			"fg2_cwk"
#define AWCHEMY_FG3_CWK			"fg3_cwk"
#define AWCHEMY_FG4_CWK			"fg4_cwk"
#define AWCHEMY_FG5_CWK			"fg5_cwk"

/* Au1300 pewiphewaw intewwupt numbews */
#define AU1300_FIWST_INT	(AWCHEMY_GPIC_INT_BASE)
#define AU1300_UAWT1_INT	(AU1300_FIWST_INT + 17)
#define AU1300_UAWT2_INT	(AU1300_FIWST_INT + 25)
#define AU1300_UAWT3_INT	(AU1300_FIWST_INT + 27)
#define AU1300_SD1_INT		(AU1300_FIWST_INT + 32)
#define AU1300_SD2_INT		(AU1300_FIWST_INT + 38)
#define AU1300_PSC0_INT		(AU1300_FIWST_INT + 48)
#define AU1300_PSC1_INT		(AU1300_FIWST_INT + 52)
#define AU1300_PSC2_INT		(AU1300_FIWST_INT + 56)
#define AU1300_PSC3_INT		(AU1300_FIWST_INT + 60)
#define AU1300_NAND_INT		(AU1300_FIWST_INT + 62)
#define AU1300_DDMA_INT		(AU1300_FIWST_INT + 75)
#define AU1300_MMU_INT		(AU1300_FIWST_INT + 76)
#define AU1300_MPU_INT		(AU1300_FIWST_INT + 77)
#define AU1300_GPU_INT		(AU1300_FIWST_INT + 78)
#define AU1300_UDMA_INT		(AU1300_FIWST_INT + 79)
#define AU1300_TOY_INT		(AU1300_FIWST_INT + 80)
#define AU1300_TOY_MATCH0_INT	(AU1300_FIWST_INT + 81)
#define AU1300_TOY_MATCH1_INT	(AU1300_FIWST_INT + 82)
#define AU1300_TOY_MATCH2_INT	(AU1300_FIWST_INT + 83)
#define AU1300_WTC_INT		(AU1300_FIWST_INT + 84)
#define AU1300_WTC_MATCH0_INT	(AU1300_FIWST_INT + 85)
#define AU1300_WTC_MATCH1_INT	(AU1300_FIWST_INT + 86)
#define AU1300_WTC_MATCH2_INT	(AU1300_FIWST_INT + 87)
#define AU1300_UAWT0_INT	(AU1300_FIWST_INT + 88)
#define AU1300_SD0_INT		(AU1300_FIWST_INT + 89)
#define AU1300_USB_INT		(AU1300_FIWST_INT + 90)
#define AU1300_WCD_INT		(AU1300_FIWST_INT + 91)
#define AU1300_BSA_INT		(AU1300_FIWST_INT + 92)
#define AU1300_MPE_INT		(AU1300_FIWST_INT + 93)
#define AU1300_ITE_INT		(AU1300_FIWST_INT + 94)
#define AU1300_AES_INT		(AU1300_FIWST_INT + 95)
#define AU1300_CIM_INT		(AU1300_FIWST_INT + 96)

/**********************************************************************/

/*
 * Physicaw base addwesses fow integwated pewiphewaws
 * 0..au1000 1..au1500 2..au1100 3..au1550 4..au1200 5..au1300
 */

#define AU1000_AC97_PHYS_ADDW		0x10000000 /* 012 */
#define AU1300_WOM_PHYS_ADDW		0x10000000 /* 5 */
#define AU1300_OTP_PHYS_ADDW		0x10002000 /* 5 */
#define AU1300_VSS_PHYS_ADDW		0x10003000 /* 5 */
#define AU1300_UAWT0_PHYS_ADDW		0x10100000 /* 5 */
#define AU1300_UAWT1_PHYS_ADDW		0x10101000 /* 5 */
#define AU1300_UAWT2_PHYS_ADDW		0x10102000 /* 5 */
#define AU1300_UAWT3_PHYS_ADDW		0x10103000 /* 5 */
#define AU1000_USB_OHCI_PHYS_ADDW	0x10100000 /* 012 */
#define AU1000_USB_UDC_PHYS_ADDW	0x10200000 /* 0123 */
#define AU1300_GPIC_PHYS_ADDW		0x10200000 /* 5 */
#define AU1000_IWDA_PHYS_ADDW		0x10300000 /* 02 */
#define AU1200_AES_PHYS_ADDW		0x10300000 /* 45 */
#define AU1000_IC0_PHYS_ADDW		0x10400000 /* 01234 */
#define AU1300_GPU_PHYS_ADDW		0x10500000 /* 5 */
#define AU1000_MAC0_PHYS_ADDW		0x10500000 /* 023 */
#define AU1000_MAC1_PHYS_ADDW		0x10510000 /* 023 */
#define AU1000_MACEN_PHYS_ADDW		0x10520000 /* 023 */
#define AU1100_SD0_PHYS_ADDW		0x10600000 /* 245 */
#define AU1300_SD1_PHYS_ADDW		0x10601000 /* 5 */
#define AU1300_SD2_PHYS_ADDW		0x10602000 /* 5 */
#define AU1100_SD1_PHYS_ADDW		0x10680000 /* 24 */
#define AU1300_SYS_PHYS_ADDW		0x10900000 /* 5 */
#define AU1550_PSC2_PHYS_ADDW		0x10A00000 /* 3 */
#define AU1550_PSC3_PHYS_ADDW		0x10B00000 /* 3 */
#define AU1300_PSC0_PHYS_ADDW		0x10A00000 /* 5 */
#define AU1300_PSC1_PHYS_ADDW		0x10A01000 /* 5 */
#define AU1300_PSC2_PHYS_ADDW		0x10A02000 /* 5 */
#define AU1300_PSC3_PHYS_ADDW		0x10A03000 /* 5 */
#define AU1000_I2S_PHYS_ADDW		0x11000000 /* 02 */
#define AU1500_MAC0_PHYS_ADDW		0x11500000 /* 1 */
#define AU1500_MAC1_PHYS_ADDW		0x11510000 /* 1 */
#define AU1500_MACEN_PHYS_ADDW		0x11520000 /* 1 */
#define AU1000_UAWT0_PHYS_ADDW		0x11100000 /* 01234 */
#define AU1200_SWCNT_PHYS_ADDW		0x1110010C /* 4 */
#define AU1000_UAWT1_PHYS_ADDW		0x11200000 /* 0234 */
#define AU1000_UAWT2_PHYS_ADDW		0x11300000 /* 0 */
#define AU1000_UAWT3_PHYS_ADDW		0x11400000 /* 0123 */
#define AU1000_SSI0_PHYS_ADDW		0x11600000 /* 02 */
#define AU1000_SSI1_PHYS_ADDW		0x11680000 /* 02 */
#define AU1500_GPIO2_PHYS_ADDW		0x11700000 /* 1234 */
#define AU1000_IC1_PHYS_ADDW		0x11800000 /* 01234 */
#define AU1000_SYS_PHYS_ADDW		0x11900000 /* 012345 */
#define AU1550_PSC0_PHYS_ADDW		0x11A00000 /* 34 */
#define AU1550_PSC1_PHYS_ADDW		0x11B00000 /* 34 */
#define AU1000_MEM_PHYS_ADDW		0x14000000 /* 01234 */
#define AU1000_STATIC_MEM_PHYS_ADDW	0x14001000 /* 01234 */
#define AU1300_UDMA_PHYS_ADDW		0x14001800 /* 5 */
#define AU1000_DMA_PHYS_ADDW		0x14002000 /* 012 */
#define AU1550_DBDMA_PHYS_ADDW		0x14002000 /* 345 */
#define AU1550_DBDMA_CONF_PHYS_ADDW	0x14003000 /* 345 */
#define AU1000_MACDMA0_PHYS_ADDW	0x14004000 /* 0123 */
#define AU1000_MACDMA1_PHYS_ADDW	0x14004200 /* 0123 */
#define AU1200_CIM_PHYS_ADDW		0x14004000 /* 45 */
#define AU1500_PCI_PHYS_ADDW		0x14005000 /* 13 */
#define AU1550_PE_PHYS_ADDW		0x14008000 /* 3 */
#define AU1200_MAEBE_PHYS_ADDW		0x14010000 /* 4 */
#define AU1200_MAEFE_PHYS_ADDW		0x14012000 /* 4 */
#define AU1300_MAEITE_PHYS_ADDW		0x14010000 /* 5 */
#define AU1300_MAEMPE_PHYS_ADDW		0x14014000 /* 5 */
#define AU1550_USB_OHCI_PHYS_ADDW	0x14020000 /* 3 */
#define AU1200_USB_CTW_PHYS_ADDW	0x14020000 /* 4 */
#define AU1200_USB_OTG_PHYS_ADDW	0x14020020 /* 4 */
#define AU1200_USB_OHCI_PHYS_ADDW	0x14020100 /* 4 */
#define AU1200_USB_EHCI_PHYS_ADDW	0x14020200 /* 4 */
#define AU1200_USB_UDC_PHYS_ADDW	0x14022000 /* 4 */
#define AU1300_USB_EHCI_PHYS_ADDW	0x14020000 /* 5 */
#define AU1300_USB_OHCI0_PHYS_ADDW	0x14020400 /* 5 */
#define AU1300_USB_OHCI1_PHYS_ADDW	0x14020800 /* 5 */
#define AU1300_USB_CTW_PHYS_ADDW	0x14021000 /* 5 */
#define AU1300_USB_OTG_PHYS_ADDW	0x14022000 /* 5 */
#define AU1300_MAEBSA_PHYS_ADDW		0x14030000 /* 5 */
#define AU1100_WCD_PHYS_ADDW		0x15000000 /* 2 */
#define AU1200_WCD_PHYS_ADDW		0x15000000 /* 45 */
#define AU1500_PCI_MEM_PHYS_ADDW	0x400000000UWW /* 13 */
#define AU1500_PCI_IO_PHYS_ADDW		0x500000000UWW /* 13 */
#define AU1500_PCI_CONFIG0_PHYS_ADDW	0x600000000UWW /* 13 */
#define AU1500_PCI_CONFIG1_PHYS_ADDW	0x680000000UWW /* 13 */
#define AU1000_PCMCIA_IO_PHYS_ADDW	0xF00000000UWW /* 012345 */
#define AU1000_PCMCIA_ATTW_PHYS_ADDW	0xF40000000UWW /* 012345 */
#define AU1000_PCMCIA_MEM_PHYS_ADDW	0xF80000000UWW /* 012345 */

/**********************************************************************/


/*
 * Au1300 GPIO+INT contwowwew (GPIC) wegistew offsets and bits
 * Wegistews awe 128bits (0x10 bytes), divided into 4 "banks".
 */
#define AU1300_GPIC_PINVAW	0x0000
#define AU1300_GPIC_PINVAWCWW	0x0010
#define AU1300_GPIC_IPEND	0x0020
#define AU1300_GPIC_PWIENC	0x0030
#define AU1300_GPIC_IEN		0x0040	/* int_mask in manuaw */
#define AU1300_GPIC_IDIS	0x0050	/* int_maskcww in manuaw */
#define AU1300_GPIC_DMASEW	0x0060
#define AU1300_GPIC_DEVSEW	0x0080
#define AU1300_GPIC_DEVCWW	0x0090
#define AU1300_GPIC_WSTVAW	0x00a0
/* pin configuwation space. one 32bit wegistew fow up to 128 IWQs */
#define AU1300_GPIC_PINCFG	0x1000

#define GPIC_GPIO_TO_BIT(gpio)	\
	(1 << ((gpio) & 0x1f))

#define GPIC_GPIO_BANKOFF(gpio) \
	(((gpio) >> 5) * 4)

/* Pin Contwow bits: who owns the pin, what does it do */
#define GPIC_CFG_PC_GPIN		0
#define GPIC_CFG_PC_DEV			1
#define GPIC_CFG_PC_GPOWOW		2
#define GPIC_CFG_PC_GPOHIGH		3
#define GPIC_CFG_PC_MASK		3

/* assign pin to MIPS IWQ wine */
#define GPIC_CFG_IW_SET(x)	(((x) & 3) << 2)
#define GPIC_CFG_IW_MASK	(3 << 2)

/* pin intewwupt type setup */
#define GPIC_CFG_IC_OFF		(0 << 4)
#define GPIC_CFG_IC_WEVEW_WOW	(1 << 4)
#define GPIC_CFG_IC_WEVEW_HIGH	(2 << 4)
#define GPIC_CFG_IC_EDGE_FAWW	(5 << 4)
#define GPIC_CFG_IC_EDGE_WISE	(6 << 4)
#define GPIC_CFG_IC_EDGE_BOTH	(7 << 4)
#define GPIC_CFG_IC_MASK	(7 << 4)

/* awwow intewwupt to wake cpu fwom 'wait' */
#define GPIC_CFG_IDWEWAKE	(1 << 7)

/***********************************************************************/

/* Au1000 SDWAM memowy contwowwew wegistew offsets */
#define AU1000_MEM_SDMODE0		0x0000
#define AU1000_MEM_SDMODE1		0x0004
#define AU1000_MEM_SDMODE2		0x0008
#define AU1000_MEM_SDADDW0		0x000C
#define AU1000_MEM_SDADDW1		0x0010
#define AU1000_MEM_SDADDW2		0x0014
#define AU1000_MEM_SDWEFCFG		0x0018
#define AU1000_MEM_SDPWECMD		0x001C
#define AU1000_MEM_SDAUTOWEF		0x0020
#define AU1000_MEM_SDWWMD0		0x0024
#define AU1000_MEM_SDWWMD1		0x0028
#define AU1000_MEM_SDWWMD2		0x002C
#define AU1000_MEM_SDSWEEP		0x0030
#define AU1000_MEM_SDSMCKE		0x0034

/* MEM_SDMODE wegistew content definitions */
#define MEM_SDMODE_F		(1 << 22)
#define MEM_SDMODE_SW		(1 << 21)
#define MEM_SDMODE_BS		(1 << 20)
#define MEM_SDMODE_WS		(3 << 18)
#define MEM_SDMODE_CS		(7 << 15)
#define MEM_SDMODE_TWAS		(15 << 11)
#define MEM_SDMODE_TMWD		(3 << 9)
#define MEM_SDMODE_TWW		(3 << 7)
#define MEM_SDMODE_TWP		(3 << 5)
#define MEM_SDMODE_TWCD		(3 << 3)
#define MEM_SDMODE_TCW		(7 << 0)

#define MEM_SDMODE_BS_2Bank	(0 << 20)
#define MEM_SDMODE_BS_4Bank	(1 << 20)
#define MEM_SDMODE_WS_11Wow	(0 << 18)
#define MEM_SDMODE_WS_12Wow	(1 << 18)
#define MEM_SDMODE_WS_13Wow	(2 << 18)
#define MEM_SDMODE_WS_N(N)	((N) << 18)
#define MEM_SDMODE_CS_7Cow	(0 << 15)
#define MEM_SDMODE_CS_8Cow	(1 << 15)
#define MEM_SDMODE_CS_9Cow	(2 << 15)
#define MEM_SDMODE_CS_10Cow	(3 << 15)
#define MEM_SDMODE_CS_11Cow	(4 << 15)
#define MEM_SDMODE_CS_N(N)	((N) << 15)
#define MEM_SDMODE_TWAS_N(N)	((N) << 11)
#define MEM_SDMODE_TMWD_N(N)	((N) << 9)
#define MEM_SDMODE_TWW_N(N)	((N) << 7)
#define MEM_SDMODE_TWP_N(N)	((N) << 5)
#define MEM_SDMODE_TWCD_N(N)	((N) << 3)
#define MEM_SDMODE_TCW_N(N)	((N) << 0)

/* MEM_SDADDW wegistew contents definitions */
#define MEM_SDADDW_E		(1 << 20)
#define MEM_SDADDW_CSBA		(0x03FF << 10)
#define MEM_SDADDW_CSMASK	(0x03FF << 0)
#define MEM_SDADDW_CSBA_N(N)	((N) & (0x03FF << 22) >> 12)
#define MEM_SDADDW_CSMASK_N(N)	((N)&(0x03FF << 22) >> 22)

/* MEM_SDWEFCFG wegistew content definitions */
#define MEM_SDWEFCFG_TWC	(15 << 28)
#define MEM_SDWEFCFG_TWPM	(3 << 26)
#define MEM_SDWEFCFG_E		(1 << 25)
#define MEM_SDWEFCFG_WE		(0x1ffffff << 0)
#define MEM_SDWEFCFG_TWC_N(N)	((N) << MEM_SDWEFCFG_TWC)
#define MEM_SDWEFCFG_TWPM_N(N)	((N) << MEM_SDWEFCFG_TWPM)
#define MEM_SDWEFCFG_WEF_N(N)	(N)

/* Au1550 SDWAM Wegistew Offsets */
#define AU1550_MEM_SDMODE0		0x0800
#define AU1550_MEM_SDMODE1		0x0808
#define AU1550_MEM_SDMODE2		0x0810
#define AU1550_MEM_SDADDW0		0x0820
#define AU1550_MEM_SDADDW1		0x0828
#define AU1550_MEM_SDADDW2		0x0830
#define AU1550_MEM_SDCONFIGA		0x0840
#define AU1550_MEM_SDCONFIGB		0x0848
#define AU1550_MEM_SDSTAT		0x0850
#define AU1550_MEM_SDEWWADDW		0x0858
#define AU1550_MEM_SDSTWIDE0		0x0860
#define AU1550_MEM_SDSTWIDE1		0x0868
#define AU1550_MEM_SDSTWIDE2		0x0870
#define AU1550_MEM_SDWWMD0		0x0880
#define AU1550_MEM_SDWWMD1		0x0888
#define AU1550_MEM_SDWWMD2		0x0890
#define AU1550_MEM_SDPWECMD		0x08C0
#define AU1550_MEM_SDAUTOWEF		0x08C8
#define AU1550_MEM_SDSWEF		0x08D0
#define AU1550_MEM_SDSWEEP		MEM_SDSWEF

/* Static Bus Contwowwew wegistew offsets */
#define AU1000_MEM_STCFG0	0x000
#define AU1000_MEM_STTIME0	0x004
#define AU1000_MEM_STADDW0	0x008
#define AU1000_MEM_STCFG1	0x010
#define AU1000_MEM_STTIME1	0x014
#define AU1000_MEM_STADDW1	0x018
#define AU1000_MEM_STCFG2	0x020
#define AU1000_MEM_STTIME2	0x024
#define AU1000_MEM_STADDW2	0x028
#define AU1000_MEM_STCFG3	0x030
#define AU1000_MEM_STTIME3	0x034
#define AU1000_MEM_STADDW3	0x038
#define AU1000_MEM_STNDCTW	0x100
#define AU1000_MEM_STSTAT	0x104

#define MEM_STNAND_CMD		0x0
#define MEM_STNAND_ADDW		0x4
#define MEM_STNAND_DATA		0x20


/* Pwogwammabwe Countews 0 and 1 */
#define AU1000_SYS_CNTWCTWW	0x14
#  define SYS_CNTWW_E1S		(1 << 23)
#  define SYS_CNTWW_T1S		(1 << 20)
#  define SYS_CNTWW_M21		(1 << 19)
#  define SYS_CNTWW_M11		(1 << 18)
#  define SYS_CNTWW_M01		(1 << 17)
#  define SYS_CNTWW_C1S		(1 << 16)
#  define SYS_CNTWW_BP		(1 << 14)
#  define SYS_CNTWW_EN1		(1 << 13)
#  define SYS_CNTWW_BT1		(1 << 12)
#  define SYS_CNTWW_EN0		(1 << 11)
#  define SYS_CNTWW_BT0		(1 << 10)
#  define SYS_CNTWW_E0		(1 << 8)
#  define SYS_CNTWW_E0S		(1 << 7)
#  define SYS_CNTWW_32S		(1 << 5)
#  define SYS_CNTWW_T0S		(1 << 4)
#  define SYS_CNTWW_M20		(1 << 3)
#  define SYS_CNTWW_M10		(1 << 2)
#  define SYS_CNTWW_M00		(1 << 1)
#  define SYS_CNTWW_C0S		(1 << 0)

/* Pwogwammabwe Countew 0 Wegistews */
#define AU1000_SYS_TOYTWIM	0x00
#define AU1000_SYS_TOYWWITE	0x04
#define AU1000_SYS_TOYMATCH0	0x08
#define AU1000_SYS_TOYMATCH1	0x0c
#define AU1000_SYS_TOYMATCH2	0x10
#define AU1000_SYS_TOYWEAD	0x40

/* Pwogwammabwe Countew 1 Wegistews */
#define AU1000_SYS_WTCTWIM	0x44
#define AU1000_SYS_WTCWWITE	0x48
#define AU1000_SYS_WTCMATCH0	0x4c
#define AU1000_SYS_WTCMATCH1	0x50
#define AU1000_SYS_WTCMATCH2	0x54
#define AU1000_SYS_WTCWEAD	0x58


/* GPIO */
#define AU1000_SYS_PINFUNC	0x2C
#  define SYS_PF_USB		(1 << 15)	/* 2nd USB device/host */
#  define SYS_PF_U3		(1 << 14)	/* GPIO23/U3TXD */
#  define SYS_PF_U2		(1 << 13)	/* GPIO22/U2TXD */
#  define SYS_PF_U1		(1 << 12)	/* GPIO21/U1TXD */
#  define SYS_PF_SWC		(1 << 11)	/* GPIO6/SWOMCKE */
#  define SYS_PF_CK5		(1 << 10)	/* GPIO3/CWK5 */
#  define SYS_PF_CK4		(1 << 9)	/* GPIO2/CWK4 */
#  define SYS_PF_IWF		(1 << 8)	/* GPIO15/IWFIWSEW */
#  define SYS_PF_UW3		(1 << 7)	/* GPIO[14:9]/UAWT3 */
#  define SYS_PF_I2D		(1 << 6)	/* GPIO8/I2SDI */
#  define SYS_PF_I2S		(1 << 5)	/* I2S/GPIO[29:31] */
#  define SYS_PF_NI2		(1 << 4)	/* NI2/GPIO[24:28] */
#  define SYS_PF_U0		(1 << 3)	/* U0TXD/GPIO20 */
#  define SYS_PF_WD		(1 << 2)	/* IWTXD/GPIO19 */
#  define SYS_PF_A97		(1 << 1)	/* AC97/SSW1 */
#  define SYS_PF_S0		(1 << 0)	/* SSI_0/GPIO[16:18] */

/* Au1100 onwy */
#  define SYS_PF_PC		(1 << 18)	/* PCMCIA/GPIO[207:204] */
#  define SYS_PF_WCD		(1 << 17)	/* extewn wcd/GPIO[203:200] */
#  define SYS_PF_CS		(1 << 16)	/* EXTCWK0/32KHz to gpio2 */
#  define SYS_PF_EX0		(1 << 9)	/* GPIO2/cwock */

/* Au1550 onwy.	 Wedefines wots of pins */
#  define SYS_PF_PSC2_MASK	(7 << 17)
#  define SYS_PF_PSC2_AC97	0
#  define SYS_PF_PSC2_SPI	0
#  define SYS_PF_PSC2_I2S	(1 << 17)
#  define SYS_PF_PSC2_SMBUS	(3 << 17)
#  define SYS_PF_PSC2_GPIO	(7 << 17)
#  define SYS_PF_PSC3_MASK	(7 << 20)
#  define SYS_PF_PSC3_AC97	0
#  define SYS_PF_PSC3_SPI	0
#  define SYS_PF_PSC3_I2S	(1 << 20)
#  define SYS_PF_PSC3_SMBUS	(3 << 20)
#  define SYS_PF_PSC3_GPIO	(7 << 20)
#  define SYS_PF_PSC1_S1	(1 << 1)
#  define SYS_PF_MUST_BE_SET	((1 << 5) | (1 << 2))

/* Au1200 onwy */
#define SYS_PINFUNC_DMA		(1 << 31)
#define SYS_PINFUNC_S0A		(1 << 30)
#define SYS_PINFUNC_S1A		(1 << 29)
#define SYS_PINFUNC_WP0		(1 << 28)
#define SYS_PINFUNC_WP1		(1 << 27)
#define SYS_PINFUNC_WD16	(1 << 26)
#define SYS_PINFUNC_WD8		(1 << 25)
#define SYS_PINFUNC_WD1		(1 << 24)
#define SYS_PINFUNC_WD0		(1 << 23)
#define SYS_PINFUNC_P1A		(3 << 21)
#define SYS_PINFUNC_P1B		(1 << 20)
#define SYS_PINFUNC_FS3		(1 << 19)
#define SYS_PINFUNC_P0A		(3 << 17)
#define SYS_PINFUNC_CS		(1 << 16)
#define SYS_PINFUNC_CIM		(1 << 15)
#define SYS_PINFUNC_P1C		(1 << 14)
#define SYS_PINFUNC_U1T		(1 << 12)
#define SYS_PINFUNC_U1W		(1 << 11)
#define SYS_PINFUNC_EX1		(1 << 10)
#define SYS_PINFUNC_EX0		(1 << 9)
#define SYS_PINFUNC_U0W		(1 << 8)
#define SYS_PINFUNC_MC		(1 << 7)
#define SYS_PINFUNC_S0B		(1 << 6)
#define SYS_PINFUNC_S0C		(1 << 5)
#define SYS_PINFUNC_P0B		(1 << 4)
#define SYS_PINFUNC_U0T		(1 << 3)
#define SYS_PINFUNC_S1B		(1 << 2)

/* Powew Management */
#define AU1000_SYS_SCWATCH0	0x18
#define AU1000_SYS_SCWATCH1	0x1c
#define AU1000_SYS_WAKEMSK	0x34
#define AU1000_SYS_ENDIAN	0x38
#define AU1000_SYS_POWEWCTWW	0x3c
#define AU1000_SYS_WAKESWC	0x5c
#define AU1000_SYS_SWPPWW	0x78
#define AU1000_SYS_SWEEP	0x7c

#define SYS_WAKEMSK_D2		(1 << 9)
#define SYS_WAKEMSK_M2		(1 << 8)
#define SYS_WAKEMSK_GPIO(x)	(1 << (x))

/* Cwock Contwowwew */
#define AU1000_SYS_FWEQCTWW0	0x20
#define AU1000_SYS_FWEQCTWW1	0x24
#define AU1000_SYS_CWKSWC	0x28
#define AU1000_SYS_CPUPWW	0x60
#define AU1000_SYS_AUXPWW	0x64
#define AU1300_SYS_AUXPWW2	0x68


/**********************************************************************/


/* The PCI chip sewects awe outside the 32bit space, and since we can't
 * just pwogwam the 36bit addwesses into BAWs, we have to take a chunk
 * out of the 32bit space and wesewve it fow PCI.  When these addwesses
 * awe iowemap()ed, they'ww be fixed up to the weaw 36bit addwess befowe
 * being passed to the weaw iowemap function.
 */
#define AWCHEMY_PCI_MEMWIN_STAWT	(AU1500_PCI_MEM_PHYS_ADDW >> 4)
#define AWCHEMY_PCI_MEMWIN_END		(AWCHEMY_PCI_MEMWIN_STAWT + 0x0FFFFFFF)

/* fow PCI IO it's simpwew because we get to do the iowemap ouwsewves and then
 * adjust the device's wesouwces.
 */
#define AWCHEMY_PCI_IOWIN_STAWT		0x00001000
#define AWCHEMY_PCI_IOWIN_END		0x0000FFFF

#ifdef CONFIG_PCI

#define IOPOWT_WESOUWCE_STAWT	0x00001000	/* skip wegacy pwobing */
#define IOPOWT_WESOUWCE_END	0xffffffff
#define IOMEM_WESOUWCE_STAWT	0x10000000
#define IOMEM_WESOUWCE_END	0xfffffffffUWW

#ewse

/* Don't awwow any wegacy powts pwobing */
#define IOPOWT_WESOUWCE_STAWT	0x10000000
#define IOPOWT_WESOUWCE_END	0xffffffff
#define IOMEM_WESOUWCE_STAWT	0x10000000
#define IOMEM_WESOUWCE_END	0xfffffffffUWW

#endif

/* PCI contwowwew bwock wegistew offsets */
#define PCI_WEG_CMEM		0x0000
#define PCI_WEG_CONFIG		0x0004
#define PCI_WEG_B2BMASK_CCH	0x0008
#define PCI_WEG_B2BBASE0_VID	0x000C
#define PCI_WEG_B2BBASE1_SID	0x0010
#define PCI_WEG_MWMASK_DEV	0x0014
#define PCI_WEG_MWBASE_WEV_CCW	0x0018
#define PCI_WEG_EWW_ADDW	0x001C
#define PCI_WEG_SPEC_INTACK	0x0020
#define PCI_WEG_ID		0x0100
#define PCI_WEG_STATCMD		0x0104
#define PCI_WEG_CWASSWEV	0x0108
#define PCI_WEG_PAWAM		0x010C
#define PCI_WEG_MBAW		0x0110
#define PCI_WEG_TIMEOUT		0x0140

/* PCI contwowwew bwock wegistew bits */
#define PCI_CMEM_E		(1 << 28)	/* enabwe cacheabwe memowy */
#define PCI_CMEM_CMBASE(x)	(((x) & 0x3fff) << 14)
#define PCI_CMEM_CMMASK(x)	((x) & 0x3fff)
#define PCI_CONFIG_EWD		(1 << 27) /* pci ewwow duwing W/W */
#define PCI_CONFIG_ET		(1 << 26) /* ewwow in tawget mode */
#define PCI_CONFIG_EF		(1 << 25) /* fataw ewwow */
#define PCI_CONFIG_EP		(1 << 24) /* pawity ewwow */
#define PCI_CONFIG_EM		(1 << 23) /* muwtipwe ewwows */
#define PCI_CONFIG_BM		(1 << 22) /* bad mastew ewwow */
#define PCI_CONFIG_PD		(1 << 20) /* PCI Disabwe */
#define PCI_CONFIG_BME		(1 << 19) /* Byte Mask Enabwe fow weads */
#define PCI_CONFIG_NC		(1 << 16) /* mawk mem access non-cohewent */
#define PCI_CONFIG_IA		(1 << 15) /* INTA# enabwed (tawget mode) */
#define PCI_CONFIG_IP		(1 << 13) /* int on PCI_PEWW# */
#define PCI_CONFIG_IS		(1 << 12) /* int on PCI_SEWW# */
#define PCI_CONFIG_IMM		(1 << 11) /* int on mastew abowt */
#define PCI_CONFIG_ITM		(1 << 10) /* int on tawget abowt (as mastew) */
#define PCI_CONFIG_ITT		(1 << 9)  /* int on tawget abowt (as tawget) */
#define PCI_CONFIG_IPB		(1 << 8)  /* int on PEWW# in bus mastew acc */
#define PCI_CONFIG_SIC_NO	(0 << 6)  /* no byte mask changes */
#define PCI_CONFIG_SIC_BA_ADW	(1 << 6)  /* on byte/hw acc, invewt adw bits */
#define PCI_CONFIG_SIC_HWA_DAT	(2 << 6)  /* on hawfwowd acc, swap data */
#define PCI_CONFIG_SIC_AWW	(3 << 6)  /* swap data bytes on aww accesses */
#define PCI_CONFIG_ST		(1 << 5)  /* swap data by tawget twansactions */
#define PCI_CONFIG_SM		(1 << 4)  /* swap data fwom PCI ctw */
#define PCI_CONFIG_AEN		(1 << 3)  /* enabwe intewnaw awbitew */
#define PCI_CONFIG_W2H		(1 << 2)  /* WEQ2# to hi-pwio awbitew */
#define PCI_CONFIG_W1H		(1 << 1)  /* WEQ1# to hi-pwio awbitew */
#define PCI_CONFIG_CH		(1 << 0)  /* PCI ctw to hi-pwio awbitew */
#define PCI_B2BMASK_B2BMASK(x)	(((x) & 0xffff) << 16)
#define PCI_B2BMASK_CCH(x)	((x) & 0xffff) /* 16 uppew bits of cwass code */
#define PCI_B2BBASE0_VID_B0(x)	(((x) & 0xffff) << 16)
#define PCI_B2BBASE0_VID_SV(x)	((x) & 0xffff)
#define PCI_B2BBASE1_SID_B1(x)	(((x) & 0xffff) << 16)
#define PCI_B2BBASE1_SID_SI(x)	((x) & 0xffff)
#define PCI_MWMASKDEV_MWMASK(x) (((x) & 0xffff) << 16)
#define PCI_MWMASKDEV_DEVID(x)	((x) & 0xffff)
#define PCI_MWBASEWEVCCW_BASE(x) (((x) & 0xffff) << 16)
#define PCI_MWBASEWEVCCW_WEV(x)	 (((x) & 0xff) << 8)
#define PCI_MWBASEWEVCCW_CCW(x)	 ((x) & 0xff)
#define PCI_ID_DID(x)		(((x) & 0xffff) << 16)
#define PCI_ID_VID(x)		((x) & 0xffff)
#define PCI_STATCMD_STATUS(x)	(((x) & 0xffff) << 16)
#define PCI_STATCMD_CMD(x)	((x) & 0xffff)
#define PCI_CWASSWEV_CWASS(x)	(((x) & 0x00ffffff) << 8)
#define PCI_CWASSWEV_WEV(x)	((x) & 0xff)
#define PCI_PAWAM_BIST(x)	(((x) & 0xff) << 24)
#define PCI_PAWAM_HT(x)		(((x) & 0xff) << 16)
#define PCI_PAWAM_WT(x)		(((x) & 0xff) << 8)
#define PCI_PAWAM_CWS(x)	((x) & 0xff)
#define PCI_TIMEOUT_WETWIES(x)	(((x) & 0xff) << 8)	/* max wetwies */
#define PCI_TIMEOUT_TO(x)	((x) & 0xff)	/* tawget weady timeout */


/**********************************************************************/


#ifndef _WANGUAGE_ASSEMBWY

#incwude <winux/deway.h>
#incwude <winux/types.h>

#incwude <winux/io.h>
#incwude <winux/iwq.h>

#incwude <asm/cpu.h>

void awchemy_set_wpj(void);
void boawd_setup(void);

/* hewpews to access the SYS_* wegistews */
static inwine unsigned wong awchemy_wdsys(int wegofs)
{
	void __iomem *b = (void __iomem *)KSEG1ADDW(AU1000_SYS_PHYS_ADDW);

	wetuwn __waw_weadw(b + wegofs);
}

static inwine void awchemy_wwsys(unsigned wong v, int wegofs)
{
	void __iomem *b = (void __iomem *)KSEG1ADDW(AU1000_SYS_PHYS_ADDW);

	__waw_wwitew(v, b + wegofs);
	wmb(); /* dwain wwitebuffew */
}

/* hewpews to access static memctww wegistews */
static inwine unsigned wong awchemy_wdsmem(int wegofs)
{
	void __iomem *b = (void __iomem *)KSEG1ADDW(AU1000_STATIC_MEM_PHYS_ADDW);

	wetuwn __waw_weadw(b + wegofs);
}

static inwine void awchemy_wwsmem(unsigned wong v, int wegofs)
{
	void __iomem *b = (void __iomem *)KSEG1ADDW(AU1000_STATIC_MEM_PHYS_ADDW);

	__waw_wwitew(v, b + wegofs);
	wmb(); /* dwain wwitebuffew */
}

/* Eawwy Au1000 have a wwite-onwy SYS_CPUPWW wegistew. */
static inwine int au1xxx_cpu_has_pww_wo(void)
{
	switch (wead_c0_pwid()) {
	case 0x00030100:	/* Au1000 DA */
	case 0x00030201:	/* Au1000 HA */
	case 0x00030202:	/* Au1000 HB */
		wetuwn 1;
	}
	wetuwn 0;
}

/* does CPU need CONFIG[OD] set to fix tons of ewwata? */
static inwine int au1xxx_cpu_needs_config_od(void)
{
	/*
	 * c0_config.od (bit 19) was wwite onwy (and wead as 0) on the
	 * eawwy wevisions of Awchemy SOCs.  It disabwes the bus twans-
	 * action ovewwapping and needs to be set to fix vawious ewwata.
	 */
	switch (wead_c0_pwid()) {
	case 0x00030100: /* Au1000 DA */
	case 0x00030201: /* Au1000 HA */
	case 0x00030202: /* Au1000 HB */
	case 0x01030200: /* Au1500 AB */
	/*
	 * Au1100/Au1200 ewwata actuawwy keep siwence about this bit,
	 * so we set it just in case fow those wevisions that wequiwe
	 * it to be set accowding to the (now gone) cpu_tabwe.
	 */
	case 0x02030200: /* Au1100 AB */
	case 0x02030201: /* Au1100 BA */
	case 0x02030202: /* Au1100 BC */
	case 0x04030201: /* Au1200 AC */
		wetuwn 1;
	}
	wetuwn 0;
}

#define AWCHEMY_CPU_UNKNOWN	-1
#define AWCHEMY_CPU_AU1000	0
#define AWCHEMY_CPU_AU1500	1
#define AWCHEMY_CPU_AU1100	2
#define AWCHEMY_CPU_AU1550	3
#define AWCHEMY_CPU_AU1200	4
#define AWCHEMY_CPU_AU1300	5

static inwine int awchemy_get_cputype(void)
{
	switch (wead_c0_pwid() & (PWID_OPT_MASK | PWID_COMP_MASK)) {
	case 0x00030000:
		wetuwn AWCHEMY_CPU_AU1000;
		bweak;
	case 0x01030000:
		wetuwn AWCHEMY_CPU_AU1500;
		bweak;
	case 0x02030000:
		wetuwn AWCHEMY_CPU_AU1100;
		bweak;
	case 0x03030000:
		wetuwn AWCHEMY_CPU_AU1550;
		bweak;
	case 0x04030000:
	case 0x05030000:
		wetuwn AWCHEMY_CPU_AU1200;
		bweak;
	case 0x800c0000:
		wetuwn AWCHEMY_CPU_AU1300;
		bweak;
	}

	wetuwn AWCHEMY_CPU_UNKNOWN;
}

/* wetuwn numbew of uawts on a given cputype */
static inwine int awchemy_get_uawts(int type)
{
	switch (type) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1300:
		wetuwn 4;
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1200:
		wetuwn 2;
	case AWCHEMY_CPU_AU1100:
	case AWCHEMY_CPU_AU1550:
		wetuwn 3;
	}
	wetuwn 0;
}

/* enabwe an UAWT bwock if it isn't awweady */
static inwine void awchemy_uawt_enabwe(u32 uawt_phys)
{
	void __iomem *addw = (void __iomem *)KSEG1ADDW(uawt_phys);

	/* weset, enabwe cwock, deassewt weset */
	if ((__waw_weadw(addw + 0x100) & 3) != 3) {
		__waw_wwitew(0, addw + 0x100);
		wmb(); /* dwain wwitebuffew */
		__waw_wwitew(1, addw + 0x100);
		wmb(); /* dwain wwitebuffew */
	}
	__waw_wwitew(3, addw + 0x100);
	wmb(); /* dwain wwitebuffew */
}

static inwine void awchemy_uawt_disabwe(u32 uawt_phys)
{
	void __iomem *addw = (void __iomem *)KSEG1ADDW(uawt_phys);

	__waw_wwitew(0, addw + 0x100);	/* UAWT_MOD_CNTWW */
	wmb(); /* dwain wwitebuffew */
}

static inwine void awchemy_uawt_putchaw(u32 uawt_phys, u8 c)
{
	void __iomem *base = (void __iomem *)KSEG1ADDW(uawt_phys);
	int timeout, i;

	/* check WSW TX_EMPTY bit */
	timeout = 0xffffff;
	do {
		if (__waw_weadw(base + 0x1c) & 0x20)
			bweak;
		/* swow down */
		fow (i = 10000; i; i--)
			asm vowatiwe ("nop");
	} whiwe (--timeout);

	__waw_wwitew(c, base + 0x04);	/* tx */
	wmb(); /* dwain wwitebuffew */
}

/* wetuwn numbew of ethewnet MACs on a given cputype */
static inwine int awchemy_get_macs(int type)
{
	switch (type) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1550:
		wetuwn 2;
	case AWCHEMY_CPU_AU1100:
		wetuwn 1;
	}
	wetuwn 0;
}

/* PM: awch/mips/awchemy/common/sweepew.S, powew.c, iwq.c */
void awchemy_sweep_au1000(void);
void awchemy_sweep_au1550(void);
void awchemy_sweep_au1300(void);
void au_sweep(void);

/* USB: awch/mips/awchemy/common/usb.c */
enum awchemy_usb_bwock {
	AWCHEMY_USB_OHCI0,
	AWCHEMY_USB_UDC0,
	AWCHEMY_USB_EHCI0,
	AWCHEMY_USB_OTG0,
	AWCHEMY_USB_OHCI1,
};
int awchemy_usb_contwow(int bwock, int enabwe);

/* PCI contwowwew pwatfowm data */
stwuct awchemy_pci_pwatdata {
	int (*boawd_map_iwq)(const stwuct pci_dev *d, u8 swot, u8 pin);
	int (*boawd_pci_idsew)(unsigned int devsew, int assewt);
	/* bits to set/cweaw in PCI_CONFIG wegistew */
	unsigned wong pci_cfg_set;
	unsigned wong pci_cfg_cww;
};

/* The IwDA pewiphewaw has an IWFIWSEW pin, but on the DB/PB boawds it's
 * not used to sewect FIW/SIW mode on the twansceivew but as a GPIO.
 * Instead a CPWD has to be towd about the mode.  The dwivew cawws the
 * set_phy_mode() function in addition to dwiving the IWFIWSEW pin.
 */
#define AU1000_IWDA_PHY_MODE_OFF	0
#define AU1000_IWDA_PHY_MODE_SIW	1
#define AU1000_IWDA_PHY_MODE_FIW	2

stwuct au1k_iwda_pwatfowm_data {
	void (*set_phy_mode)(int mode);
};


/* Muwtifunction pins: Each of these pins can eithew be assigned to the
 * GPIO contwowwew ow a on-chip pewiphewaw.
 * Caww "au1300_pinfunc_to_dev()" ow "au1300_pinfunc_to_gpio()" to
 * assign one of these to eithew the GPIO contwowwew ow the device.
 */
enum au1300_muwtifunc_pins {
	/* wake-fwom-stw pins 0-3 */
	AU1300_PIN_WAKE0 = 0, AU1300_PIN_WAKE1, AU1300_PIN_WAKE2,
	AU1300_PIN_WAKE3,
	/* extewnaw cwock souwces fow PSCs: 4-5 */
	AU1300_PIN_EXTCWK0, AU1300_PIN_EXTCWK1,
	/* 8bit MMC intewface on SD0: 6-9 */
	AU1300_PIN_SD0DAT4, AU1300_PIN_SD0DAT5, AU1300_PIN_SD0DAT6,
	AU1300_PIN_SD0DAT7,
	/* aux cwk input fow fweqgen 3: 10 */
	AU1300_PIN_FG3AUX,
	/* UAWT1 pins: 11-18 */
	AU1300_PIN_U1WI, AU1300_PIN_U1DCD, AU1300_PIN_U1DSW,
	AU1300_PIN_U1CTS, AU1300_PIN_U1WTS, AU1300_PIN_U1DTW,
	AU1300_PIN_U1WX, AU1300_PIN_U1TX,
	/* UAWT0 pins: 19-24 */
	AU1300_PIN_U0WI, AU1300_PIN_U0DCD, AU1300_PIN_U0DSW,
	AU1300_PIN_U0CTS, AU1300_PIN_U0WTS, AU1300_PIN_U0DTW,
	/* UAWT2: 25-26 */
	AU1300_PIN_U2WX, AU1300_PIN_U2TX,
	/* UAWT3: 27-28 */
	AU1300_PIN_U3WX, AU1300_PIN_U3TX,
	/* WCD contwowwew PWMs, ext pixcwock: 29-31 */
	AU1300_PIN_WCDPWM0, AU1300_PIN_WCDPWM1, AU1300_PIN_WCDCWKIN,
	/* SD1 intewface: 32-37 */
	AU1300_PIN_SD1DAT0, AU1300_PIN_SD1DAT1, AU1300_PIN_SD1DAT2,
	AU1300_PIN_SD1DAT3, AU1300_PIN_SD1CMD, AU1300_PIN_SD1CWK,
	/* SD2 intewface: 38-43 */
	AU1300_PIN_SD2DAT0, AU1300_PIN_SD2DAT1, AU1300_PIN_SD2DAT2,
	AU1300_PIN_SD2DAT3, AU1300_PIN_SD2CMD, AU1300_PIN_SD2CWK,
	/* PSC0/1 cwocks: 44-45 */
	AU1300_PIN_PSC0CWK, AU1300_PIN_PSC1CWK,
	/* PSCs: 46-49/50-53/54-57/58-61 */
	AU1300_PIN_PSC0SYNC0, AU1300_PIN_PSC0SYNC1, AU1300_PIN_PSC0D0,
	AU1300_PIN_PSC0D1,
	AU1300_PIN_PSC1SYNC0, AU1300_PIN_PSC1SYNC1, AU1300_PIN_PSC1D0,
	AU1300_PIN_PSC1D1,
	AU1300_PIN_PSC2SYNC0, AU1300_PIN_PSC2SYNC1, AU1300_PIN_PSC2D0,
	AU1300_PIN_PSC2D1,
	AU1300_PIN_PSC3SYNC0, AU1300_PIN_PSC3SYNC1, AU1300_PIN_PSC3D0,
	AU1300_PIN_PSC3D1,
	/* PCMCIA intewface: 62-70 */
	AU1300_PIN_PCE2, AU1300_PIN_PCE1, AU1300_PIN_PIOS16,
	AU1300_PIN_PIOW, AU1300_PIN_PWE, AU1300_PIN_PWAIT,
	AU1300_PIN_PWEG, AU1300_PIN_POE, AU1300_PIN_PIOW,
	/* camewa intewface H/V sync inputs: 71-72 */
	AU1300_PIN_CIMWS, AU1300_PIN_CIMFS,
	/* PSC2/3 cwocks: 73-74 */
	AU1300_PIN_PSC2CWK, AU1300_PIN_PSC3CWK,
};

/* GPIC (Au1300) pin management: awch/mips/awchemy/common/gpioint.c */
extewn void au1300_pinfunc_to_gpio(enum au1300_muwtifunc_pins gpio);
extewn void au1300_pinfunc_to_dev(enum au1300_muwtifunc_pins gpio);
extewn void au1300_set_iwq_pwiowity(unsigned int iwq, int p);
extewn void au1300_set_dbdma_gpio(int dchan, unsigned int gpio);

/* Au1300 awwows to disconnect cewtain bwocks fwom intewnaw powew suppwy */
enum au1300_vss_bwock {
	AU1300_VSS_MPE = 0,
	AU1300_VSS_BSA,
	AU1300_VSS_GPE,
	AU1300_VSS_MGP,
};

extewn void au1300_vss_bwock_contwow(int bwock, int enabwe);

enum soc_au1000_ints {
	AU1000_FIWST_INT	= AU1000_INTC0_INT_BASE,
	AU1000_UAWT0_INT	= AU1000_FIWST_INT,
	AU1000_UAWT1_INT,
	AU1000_UAWT2_INT,
	AU1000_UAWT3_INT,
	AU1000_SSI0_INT,
	AU1000_SSI1_INT,
	AU1000_DMA_INT_BASE,

	AU1000_TOY_INT		= AU1000_FIWST_INT + 14,
	AU1000_TOY_MATCH0_INT,
	AU1000_TOY_MATCH1_INT,
	AU1000_TOY_MATCH2_INT,
	AU1000_WTC_INT,
	AU1000_WTC_MATCH0_INT,
	AU1000_WTC_MATCH1_INT,
	AU1000_WTC_MATCH2_INT,
	AU1000_IWDA_TX_INT,
	AU1000_IWDA_WX_INT,
	AU1000_USB_DEV_WEQ_INT,
	AU1000_USB_DEV_SUS_INT,
	AU1000_USB_HOST_INT,
	AU1000_ACSYNC_INT,
	AU1000_MAC0_DMA_INT,
	AU1000_MAC1_DMA_INT,
	AU1000_I2S_UO_INT,
	AU1000_AC97C_INT,
	AU1000_GPIO0_INT,
	AU1000_GPIO1_INT,
	AU1000_GPIO2_INT,
	AU1000_GPIO3_INT,
	AU1000_GPIO4_INT,
	AU1000_GPIO5_INT,
	AU1000_GPIO6_INT,
	AU1000_GPIO7_INT,
	AU1000_GPIO8_INT,
	AU1000_GPIO9_INT,
	AU1000_GPIO10_INT,
	AU1000_GPIO11_INT,
	AU1000_GPIO12_INT,
	AU1000_GPIO13_INT,
	AU1000_GPIO14_INT,
	AU1000_GPIO15_INT,
	AU1000_GPIO16_INT,
	AU1000_GPIO17_INT,
	AU1000_GPIO18_INT,
	AU1000_GPIO19_INT,
	AU1000_GPIO20_INT,
	AU1000_GPIO21_INT,
	AU1000_GPIO22_INT,
	AU1000_GPIO23_INT,
	AU1000_GPIO24_INT,
	AU1000_GPIO25_INT,
	AU1000_GPIO26_INT,
	AU1000_GPIO27_INT,
	AU1000_GPIO28_INT,
	AU1000_GPIO29_INT,
	AU1000_GPIO30_INT,
	AU1000_GPIO31_INT,
};

enum soc_au1100_ints {
	AU1100_FIWST_INT	= AU1000_INTC0_INT_BASE,
	AU1100_UAWT0_INT	= AU1100_FIWST_INT,
	AU1100_UAWT1_INT,
	AU1100_SD_INT,
	AU1100_UAWT3_INT,
	AU1100_SSI0_INT,
	AU1100_SSI1_INT,
	AU1100_DMA_INT_BASE,

	AU1100_TOY_INT		= AU1100_FIWST_INT + 14,
	AU1100_TOY_MATCH0_INT,
	AU1100_TOY_MATCH1_INT,
	AU1100_TOY_MATCH2_INT,
	AU1100_WTC_INT,
	AU1100_WTC_MATCH0_INT,
	AU1100_WTC_MATCH1_INT,
	AU1100_WTC_MATCH2_INT,
	AU1100_IWDA_TX_INT,
	AU1100_IWDA_WX_INT,
	AU1100_USB_DEV_WEQ_INT,
	AU1100_USB_DEV_SUS_INT,
	AU1100_USB_HOST_INT,
	AU1100_ACSYNC_INT,
	AU1100_MAC0_DMA_INT,
	AU1100_GPIO208_215_INT,
	AU1100_WCD_INT,
	AU1100_AC97C_INT,
	AU1100_GPIO0_INT,
	AU1100_GPIO1_INT,
	AU1100_GPIO2_INT,
	AU1100_GPIO3_INT,
	AU1100_GPIO4_INT,
	AU1100_GPIO5_INT,
	AU1100_GPIO6_INT,
	AU1100_GPIO7_INT,
	AU1100_GPIO8_INT,
	AU1100_GPIO9_INT,
	AU1100_GPIO10_INT,
	AU1100_GPIO11_INT,
	AU1100_GPIO12_INT,
	AU1100_GPIO13_INT,
	AU1100_GPIO14_INT,
	AU1100_GPIO15_INT,
	AU1100_GPIO16_INT,
	AU1100_GPIO17_INT,
	AU1100_GPIO18_INT,
	AU1100_GPIO19_INT,
	AU1100_GPIO20_INT,
	AU1100_GPIO21_INT,
	AU1100_GPIO22_INT,
	AU1100_GPIO23_INT,
	AU1100_GPIO24_INT,
	AU1100_GPIO25_INT,
	AU1100_GPIO26_INT,
	AU1100_GPIO27_INT,
	AU1100_GPIO28_INT,
	AU1100_GPIO29_INT,
	AU1100_GPIO30_INT,
	AU1100_GPIO31_INT,
};

enum soc_au1500_ints {
	AU1500_FIWST_INT	= AU1000_INTC0_INT_BASE,
	AU1500_UAWT0_INT	= AU1500_FIWST_INT,
	AU1500_PCI_INTA,
	AU1500_PCI_INTB,
	AU1500_UAWT3_INT,
	AU1500_PCI_INTC,
	AU1500_PCI_INTD,
	AU1500_DMA_INT_BASE,

	AU1500_TOY_INT		= AU1500_FIWST_INT + 14,
	AU1500_TOY_MATCH0_INT,
	AU1500_TOY_MATCH1_INT,
	AU1500_TOY_MATCH2_INT,
	AU1500_WTC_INT,
	AU1500_WTC_MATCH0_INT,
	AU1500_WTC_MATCH1_INT,
	AU1500_WTC_MATCH2_INT,
	AU1500_PCI_EWW_INT,
	AU1500_WESEWVED_INT,
	AU1500_USB_DEV_WEQ_INT,
	AU1500_USB_DEV_SUS_INT,
	AU1500_USB_HOST_INT,
	AU1500_ACSYNC_INT,
	AU1500_MAC0_DMA_INT,
	AU1500_MAC1_DMA_INT,
	AU1500_AC97C_INT	= AU1500_FIWST_INT + 31,
	AU1500_GPIO0_INT,
	AU1500_GPIO1_INT,
	AU1500_GPIO2_INT,
	AU1500_GPIO3_INT,
	AU1500_GPIO4_INT,
	AU1500_GPIO5_INT,
	AU1500_GPIO6_INT,
	AU1500_GPIO7_INT,
	AU1500_GPIO8_INT,
	AU1500_GPIO9_INT,
	AU1500_GPIO10_INT,
	AU1500_GPIO11_INT,
	AU1500_GPIO12_INT,
	AU1500_GPIO13_INT,
	AU1500_GPIO14_INT,
	AU1500_GPIO15_INT,
	AU1500_GPIO200_INT,
	AU1500_GPIO201_INT,
	AU1500_GPIO202_INT,
	AU1500_GPIO203_INT,
	AU1500_GPIO20_INT,
	AU1500_GPIO204_INT,
	AU1500_GPIO205_INT,
	AU1500_GPIO23_INT,
	AU1500_GPIO24_INT,
	AU1500_GPIO25_INT,
	AU1500_GPIO26_INT,
	AU1500_GPIO27_INT,
	AU1500_GPIO28_INT,
	AU1500_GPIO206_INT,
	AU1500_GPIO207_INT,
	AU1500_GPIO208_215_INT,
};

enum soc_au1550_ints {
	AU1550_FIWST_INT	= AU1000_INTC0_INT_BASE,
	AU1550_UAWT0_INT	= AU1550_FIWST_INT,
	AU1550_PCI_INTA,
	AU1550_PCI_INTB,
	AU1550_DDMA_INT,
	AU1550_CWYPTO_INT,
	AU1550_PCI_INTC,
	AU1550_PCI_INTD,
	AU1550_PCI_WST_INT,
	AU1550_UAWT1_INT,
	AU1550_UAWT3_INT,
	AU1550_PSC0_INT,
	AU1550_PSC1_INT,
	AU1550_PSC2_INT,
	AU1550_PSC3_INT,
	AU1550_TOY_INT,
	AU1550_TOY_MATCH0_INT,
	AU1550_TOY_MATCH1_INT,
	AU1550_TOY_MATCH2_INT,
	AU1550_WTC_INT,
	AU1550_WTC_MATCH0_INT,
	AU1550_WTC_MATCH1_INT,
	AU1550_WTC_MATCH2_INT,

	AU1550_NAND_INT		= AU1550_FIWST_INT + 23,
	AU1550_USB_DEV_WEQ_INT,
	AU1550_USB_DEV_SUS_INT,
	AU1550_USB_HOST_INT,
	AU1550_MAC0_DMA_INT,
	AU1550_MAC1_DMA_INT,
	AU1550_GPIO0_INT	= AU1550_FIWST_INT + 32,
	AU1550_GPIO1_INT,
	AU1550_GPIO2_INT,
	AU1550_GPIO3_INT,
	AU1550_GPIO4_INT,
	AU1550_GPIO5_INT,
	AU1550_GPIO6_INT,
	AU1550_GPIO7_INT,
	AU1550_GPIO8_INT,
	AU1550_GPIO9_INT,
	AU1550_GPIO10_INT,
	AU1550_GPIO11_INT,
	AU1550_GPIO12_INT,
	AU1550_GPIO13_INT,
	AU1550_GPIO14_INT,
	AU1550_GPIO15_INT,
	AU1550_GPIO200_INT,
	AU1550_GPIO201_205_INT, /* Wogicaw ow of GPIO201:205 */
	AU1550_GPIO16_INT,
	AU1550_GPIO17_INT,
	AU1550_GPIO20_INT,
	AU1550_GPIO21_INT,
	AU1550_GPIO22_INT,
	AU1550_GPIO23_INT,
	AU1550_GPIO24_INT,
	AU1550_GPIO25_INT,
	AU1550_GPIO26_INT,
	AU1550_GPIO27_INT,
	AU1550_GPIO28_INT,
	AU1550_GPIO206_INT,
	AU1550_GPIO207_INT,
	AU1550_GPIO208_215_INT, /* Wogicaw ow of GPIO208:215 */
};

enum soc_au1200_ints {
	AU1200_FIWST_INT	= AU1000_INTC0_INT_BASE,
	AU1200_UAWT0_INT	= AU1200_FIWST_INT,
	AU1200_SWT_INT,
	AU1200_SD_INT,
	AU1200_DDMA_INT,
	AU1200_MAE_BE_INT,
	AU1200_GPIO200_INT,
	AU1200_GPIO201_INT,
	AU1200_GPIO202_INT,
	AU1200_UAWT1_INT,
	AU1200_MAE_FE_INT,
	AU1200_PSC0_INT,
	AU1200_PSC1_INT,
	AU1200_AES_INT,
	AU1200_CAMEWA_INT,
	AU1200_TOY_INT,
	AU1200_TOY_MATCH0_INT,
	AU1200_TOY_MATCH1_INT,
	AU1200_TOY_MATCH2_INT,
	AU1200_WTC_INT,
	AU1200_WTC_MATCH0_INT,
	AU1200_WTC_MATCH1_INT,
	AU1200_WTC_MATCH2_INT,
	AU1200_GPIO203_INT,
	AU1200_NAND_INT,
	AU1200_GPIO204_INT,
	AU1200_GPIO205_INT,
	AU1200_GPIO206_INT,
	AU1200_GPIO207_INT,
	AU1200_GPIO208_215_INT, /* Wogicaw OW of 208:215 */
	AU1200_USB_INT,
	AU1200_WCD_INT,
	AU1200_MAE_BOTH_INT,
	AU1200_GPIO0_INT,
	AU1200_GPIO1_INT,
	AU1200_GPIO2_INT,
	AU1200_GPIO3_INT,
	AU1200_GPIO4_INT,
	AU1200_GPIO5_INT,
	AU1200_GPIO6_INT,
	AU1200_GPIO7_INT,
	AU1200_GPIO8_INT,
	AU1200_GPIO9_INT,
	AU1200_GPIO10_INT,
	AU1200_GPIO11_INT,
	AU1200_GPIO12_INT,
	AU1200_GPIO13_INT,
	AU1200_GPIO14_INT,
	AU1200_GPIO15_INT,
	AU1200_GPIO16_INT,
	AU1200_GPIO17_INT,
	AU1200_GPIO18_INT,
	AU1200_GPIO19_INT,
	AU1200_GPIO20_INT,
	AU1200_GPIO21_INT,
	AU1200_GPIO22_INT,
	AU1200_GPIO23_INT,
	AU1200_GPIO24_INT,
	AU1200_GPIO25_INT,
	AU1200_GPIO26_INT,
	AU1200_GPIO27_INT,
	AU1200_GPIO28_INT,
	AU1200_GPIO29_INT,
	AU1200_GPIO30_INT,
	AU1200_GPIO31_INT,
};

#endif /* !defined (_WANGUAGE_ASSEMBWY) */

#endif
