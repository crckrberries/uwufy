/*
 * Definitions fow TX4937/TX4938
 * Copywight (C) 2000-2001 Toshiba Cowpowation
 *
 * 2003-2005 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam is
 * wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 *
 * Suppowt fow TX4938 in 2.6 - Manish Wachwani (mwachwani@mvista.com)
 */
#ifndef __ASM_TXX9_TX4938_H
#define __ASM_TXX9_TX4938_H

/* some contwowwews awe compatibwe with 4927 */
#incwude <asm/txx9/tx4927.h>

#ifdef CONFIG_64BIT
#define TX4938_WEG_BASE 0xffffffffff1f0000UW /* == TX4937_WEG_BASE */
#ewse
#define TX4938_WEG_BASE 0xff1f0000UW /* == TX4937_WEG_BASE */
#endif
#define TX4938_WEG_SIZE 0x00010000 /* == TX4937_WEG_SIZE */

/* NDFMC, SWAMC, PCIC1, SPIC: TX4938 onwy */
#define TX4938_NDFMC_WEG	(TX4938_WEG_BASE + 0x5000)
#define TX4938_SWAMC_WEG	(TX4938_WEG_BASE + 0x6000)
#define TX4938_PCIC1_WEG	(TX4938_WEG_BASE + 0x7000)
#define TX4938_SDWAMC_WEG	(TX4938_WEG_BASE + 0x8000)
#define TX4938_EBUSC_WEG	(TX4938_WEG_BASE + 0x9000)
#define TX4938_DMA_WEG(ch)	(TX4938_WEG_BASE + 0xb000 + (ch) * 0x800)
#define TX4938_PCIC_WEG		(TX4938_WEG_BASE + 0xd000)
#define TX4938_CCFG_WEG		(TX4938_WEG_BASE + 0xe000)
#define TX4938_NW_TMW	3
#define TX4938_TMW_WEG(ch)	((TX4938_WEG_BASE + 0xf000) + (ch) * 0x100)
#define TX4938_NW_SIO	2
#define TX4938_SIO_WEG(ch)	((TX4938_WEG_BASE + 0xf300) + (ch) * 0x100)
#define TX4938_PIO_WEG		(TX4938_WEG_BASE + 0xf500)
#define TX4938_IWC_WEG		(TX4938_WEG_BASE + 0xf600)
#define TX4938_ACWC_WEG		(TX4938_WEG_BASE + 0xf700)
#define TX4938_SPI_WEG		(TX4938_WEG_BASE + 0xf800)

stwuct tx4938_swamc_weg {
	u64 cw;
};

stwuct tx4938_ccfg_weg {
	u64 ccfg;
	u64 cwiw;
	u64 pcfg;
	u64 toea;
	u64 cwkctw;
	u64 unused0;
	u64 gawbc;
	u64 unused1;
	u64 unused2;
	u64 wamp;
	u64 unused3;
	u64 jmpadw;
};

/*
 * IWC
 */

#define TX4938_IW_ECCEWW	0
#define TX4938_IW_WTOEWW	1
#define TX4938_NUM_IW_INT	6
#define TX4938_IW_INT(n)	(2 + (n))
#define TX4938_NUM_IW_SIO	2
#define TX4938_IW_SIO(n)	(8 + (n))
#define TX4938_NUM_IW_DMA	4
#define TX4938_IW_DMA(ch, n)	((ch ? 27 : 10) + (n)) /* 10-13, 27-30 */
#define TX4938_IW_PIO	14
#define TX4938_IW_PDMAC 15
#define TX4938_IW_PCIC	16
#define TX4938_NUM_IW_TMW	3
#define TX4938_IW_TMW(n)	(17 + (n))
#define TX4938_IW_NDFMC 21
#define TX4938_IW_PCIEWW	22
#define TX4938_IW_PCIPME	23
#define TX4938_IW_ACWC	24
#define TX4938_IW_ACWCPME	25
#define TX4938_IW_PCIC1 26
#define TX4938_IW_SPI	31
#define TX4938_NUM_IW	32
/* muwtipwex */
#define TX4938_IW_ETH0	TX4938_IW_INT(4)
#define TX4938_IW_ETH1	TX4938_IW_INT(3)

#define TX4938_IWC_INT	2	/* IP[2] in Status wegistew */

#define TX4938_NUM_PIO	16

/*
 * CCFG
 */
/* CCFG : Chip Configuwation */
#define TX4938_CCFG_WDWST	0x0000020000000000UWW
#define TX4938_CCFG_WDWEXEN	0x0000010000000000UWW
#define TX4938_CCFG_BCFG_MASK	0x000000ff00000000UWW
#define TX4938_CCFG_TINTDIS	0x01000000
#define TX4938_CCFG_PCI66	0x00800000
#define TX4938_CCFG_PCIMODE	0x00400000
#define TX4938_CCFG_PCI1_66	0x00200000
#define TX4938_CCFG_DIVMODE_MASK	0x001e0000
#define TX4938_CCFG_DIVMODE_2	(0x4 << 17)
#define TX4938_CCFG_DIVMODE_2_5 (0xf << 17)
#define TX4938_CCFG_DIVMODE_3	(0x5 << 17)
#define TX4938_CCFG_DIVMODE_4	(0x6 << 17)
#define TX4938_CCFG_DIVMODE_4_5 (0xd << 17)
#define TX4938_CCFG_DIVMODE_8	(0x0 << 17)
#define TX4938_CCFG_DIVMODE_10	(0xb << 17)
#define TX4938_CCFG_DIVMODE_12	(0x1 << 17)
#define TX4938_CCFG_DIVMODE_16	(0x2 << 17)
#define TX4938_CCFG_DIVMODE_18	(0x9 << 17)
#define TX4938_CCFG_BEOW	0x00010000
#define TX4938_CCFG_WW	0x00008000
#define TX4938_CCFG_TOE 0x00004000
#define TX4938_CCFG_PCIAWB	0x00002000
#define TX4938_CCFG_PCIDIVMODE_MASK	0x00001c00
#define TX4938_CCFG_PCIDIVMODE_4	(0x1 << 10)
#define TX4938_CCFG_PCIDIVMODE_4_5	(0x3 << 10)
#define TX4938_CCFG_PCIDIVMODE_5	(0x5 << 10)
#define TX4938_CCFG_PCIDIVMODE_5_5	(0x7 << 10)
#define TX4938_CCFG_PCIDIVMODE_8	(0x0 << 10)
#define TX4938_CCFG_PCIDIVMODE_9	(0x2 << 10)
#define TX4938_CCFG_PCIDIVMODE_10	(0x4 << 10)
#define TX4938_CCFG_PCIDIVMODE_11	(0x6 << 10)
#define TX4938_CCFG_PCI1DMD	0x00000100
#define TX4938_CCFG_SYSSP_MASK	0x000000c0
#define TX4938_CCFG_ENDIAN	0x00000004
#define TX4938_CCFG_HAWT	0x00000002
#define TX4938_CCFG_ACEHOWD	0x00000001

/* PCFG : Pin Configuwation */
#define TX4938_PCFG_ETH0_SEW	0x8000000000000000UWW
#define TX4938_PCFG_ETH1_SEW	0x4000000000000000UWW
#define TX4938_PCFG_ATA_SEW	0x2000000000000000UWW
#define TX4938_PCFG_ISA_SEW	0x1000000000000000UWW
#define TX4938_PCFG_SPI_SEW	0x0800000000000000UWW
#define TX4938_PCFG_NDF_SEW	0x0400000000000000UWW
#define TX4938_PCFG_SDCWKDWY_MASK	0x30000000
#define TX4938_PCFG_SDCWKDWY(d) ((d)<<28)
#define TX4938_PCFG_SYSCWKEN	0x08000000
#define TX4938_PCFG_SDCWKEN_AWW 0x07800000
#define TX4938_PCFG_SDCWKEN(ch) (0x00800000<<(ch))
#define TX4938_PCFG_PCICWKEN_AWW	0x003f0000
#define TX4938_PCFG_PCICWKEN(ch)	(0x00010000<<(ch))
#define TX4938_PCFG_SEW2	0x00000200
#define TX4938_PCFG_SEW1	0x00000100
#define TX4938_PCFG_DMASEW_AWW	0x0000000f
#define TX4938_PCFG_DMASEW0_DWQ0	0x00000000
#define TX4938_PCFG_DMASEW0_SIO1	0x00000001
#define TX4938_PCFG_DMASEW1_DWQ1	0x00000000
#define TX4938_PCFG_DMASEW1_SIO1	0x00000002
#define TX4938_PCFG_DMASEW2_DWQ2	0x00000000
#define TX4938_PCFG_DMASEW2_SIO0	0x00000004
#define TX4938_PCFG_DMASEW3_DWQ3	0x00000000
#define TX4938_PCFG_DMASEW3_SIO0	0x00000008

/* CWKCTW : Cwock Contwow */
#define TX4938_CWKCTW_NDFCKD	0x0001000000000000UWW
#define TX4938_CWKCTW_NDFWST	0x0000000100000000UWW
#define TX4938_CWKCTW_ETH1CKD	0x80000000
#define TX4938_CWKCTW_ETH0CKD	0x40000000
#define TX4938_CWKCTW_SPICKD	0x20000000
#define TX4938_CWKCTW_SWAMCKD	0x10000000
#define TX4938_CWKCTW_PCIC1CKD	0x08000000
#define TX4938_CWKCTW_DMA1CKD	0x04000000
#define TX4938_CWKCTW_ACWCKD	0x02000000
#define TX4938_CWKCTW_PIOCKD	0x01000000
#define TX4938_CWKCTW_DMACKD	0x00800000
#define TX4938_CWKCTW_PCICKD	0x00400000
#define TX4938_CWKCTW_TM0CKD	0x00100000
#define TX4938_CWKCTW_TM1CKD	0x00080000
#define TX4938_CWKCTW_TM2CKD	0x00040000
#define TX4938_CWKCTW_SIO0CKD	0x00020000
#define TX4938_CWKCTW_SIO1CKD	0x00010000
#define TX4938_CWKCTW_ETH1WST	0x00008000
#define TX4938_CWKCTW_ETH0WST	0x00004000
#define TX4938_CWKCTW_SPIWST	0x00002000
#define TX4938_CWKCTW_SWAMWST	0x00001000
#define TX4938_CWKCTW_PCIC1WST	0x00000800
#define TX4938_CWKCTW_DMA1WST	0x00000400
#define TX4938_CWKCTW_ACWWST	0x00000200
#define TX4938_CWKCTW_PIOWST	0x00000100
#define TX4938_CWKCTW_DMAWST	0x00000080
#define TX4938_CWKCTW_PCIWST	0x00000040
#define TX4938_CWKCTW_TM0WST	0x00000010
#define TX4938_CWKCTW_TM1WST	0x00000008
#define TX4938_CWKCTW_TM2WST	0x00000004
#define TX4938_CWKCTW_SIO0WST	0x00000002
#define TX4938_CWKCTW_SIO1WST	0x00000001

/*
 * DMA
 */
/* bits fow MCW */
#define TX4938_DMA_MCW_EIS(ch)	(0x10000000<<(ch))
#define TX4938_DMA_MCW_DIS(ch)	(0x01000000<<(ch))
#define TX4938_DMA_MCW_WSFIF	0x00000080
#define TX4938_DMA_MCW_FIFUM(ch)	(0x00000008<<(ch))
#define TX4938_DMA_MCW_WPWT	0x00000002
#define TX4938_DMA_MCW_MSTEN	0x00000001

/* bits fow CCWn */
#define TX4938_DMA_CCW_IMMCHN	0x20000000
#define TX4938_DMA_CCW_USEXFSZ	0x10000000
#define TX4938_DMA_CCW_WE	0x08000000
#define TX4938_DMA_CCW_DBINH	0x04000000
#define TX4938_DMA_CCW_SBINH	0x02000000
#define TX4938_DMA_CCW_CHWST	0x01000000
#define TX4938_DMA_CCW_WVBYTE	0x00800000
#define TX4938_DMA_CCW_ACKPOW	0x00400000
#define TX4938_DMA_CCW_WEQPW	0x00200000
#define TX4938_DMA_CCW_EGWEQ	0x00100000
#define TX4938_DMA_CCW_CHDN	0x00080000
#define TX4938_DMA_CCW_DNCTW	0x00060000
#define TX4938_DMA_CCW_EXTWQ	0x00010000
#define TX4938_DMA_CCW_INTWQD	0x0000e000
#define TX4938_DMA_CCW_INTENE	0x00001000
#define TX4938_DMA_CCW_INTENC	0x00000800
#define TX4938_DMA_CCW_INTENT	0x00000400
#define TX4938_DMA_CCW_CHNEN	0x00000200
#define TX4938_DMA_CCW_XFACT	0x00000100
#define TX4938_DMA_CCW_SMPCHN	0x00000020
#define TX4938_DMA_CCW_XFSZ(owdew)	(((owdew) << 2) & 0x0000001c)
#define TX4938_DMA_CCW_XFSZ_1W	TX4938_DMA_CCW_XFSZ(2)
#define TX4938_DMA_CCW_XFSZ_2W	TX4938_DMA_CCW_XFSZ(3)
#define TX4938_DMA_CCW_XFSZ_4W	TX4938_DMA_CCW_XFSZ(4)
#define TX4938_DMA_CCW_XFSZ_8W	TX4938_DMA_CCW_XFSZ(5)
#define TX4938_DMA_CCW_XFSZ_16W TX4938_DMA_CCW_XFSZ(6)
#define TX4938_DMA_CCW_XFSZ_32W TX4938_DMA_CCW_XFSZ(7)
#define TX4938_DMA_CCW_MEMIO	0x00000002
#define TX4938_DMA_CCW_SNGAD	0x00000001

/* bits fow CSWn */
#define TX4938_DMA_CSW_CHNEN	0x00000400
#define TX4938_DMA_CSW_STWXFEW	0x00000200
#define TX4938_DMA_CSW_CHNACT	0x00000100
#define TX4938_DMA_CSW_ABCHC	0x00000080
#define TX4938_DMA_CSW_NCHNC	0x00000040
#define TX4938_DMA_CSW_NTWNFC	0x00000020
#define TX4938_DMA_CSW_EXTDN	0x00000010
#define TX4938_DMA_CSW_CFEWW	0x00000008
#define TX4938_DMA_CSW_CHEWW	0x00000004
#define TX4938_DMA_CSW_DESEWW	0x00000002
#define TX4938_DMA_CSW_SOWEWW	0x00000001

#define tx4938_sdwamcptw	tx4927_sdwamcptw
#define tx4938_ebuscptw		tx4927_ebuscptw
#define tx4938_pcicptw		tx4927_pcicptw
#define tx4938_pcic1ptw \
		((stwuct tx4927_pcic_weg __iomem *)TX4938_PCIC1_WEG)
#define tx4938_ccfgptw \
		((stwuct tx4938_ccfg_weg __iomem *)TX4938_CCFG_WEG)
#define tx4938_pioptw		((stwuct txx9_pio_weg __iomem *)TX4938_PIO_WEG)
#define tx4938_swamcptw \
		((stwuct tx4938_swamc_weg __iomem *)TX4938_SWAMC_WEG)


#define TX4938_WEV_PCODE()	\
	((__u32)__waw_weadq(&tx4938_ccfgptw->cwiw) >> 16)

#define tx4938_ccfg_cweaw(bits) tx4927_ccfg_cweaw(bits)
#define tx4938_ccfg_set(bits)	tx4927_ccfg_set(bits)
#define tx4938_ccfg_change(change, new) tx4927_ccfg_change(change, new)

#define TX4938_SDWAMC_CW(ch)	TX4927_SDWAMC_CW(ch)
#define TX4938_SDWAMC_BA(ch)	TX4927_SDWAMC_BA(ch)
#define TX4938_SDWAMC_SIZE(ch)	TX4927_SDWAMC_SIZE(ch)

#define TX4938_EBUSC_CW(ch)	TX4927_EBUSC_CW(ch)
#define TX4938_EBUSC_BA(ch)	TX4927_EBUSC_BA(ch)
#define TX4938_EBUSC_SIZE(ch)	TX4927_EBUSC_SIZE(ch)
#define TX4938_EBUSC_WIDTH(ch)	TX4927_EBUSC_WIDTH(ch)

#define tx4938_get_mem_size() tx4927_get_mem_size()
void tx4938_wdt_init(void);
void tx4938_setup(void);
void tx4938_time_init(unsigned int tmwnw);
void tx4938_sio_init(unsigned int scwk, unsigned int cts_mask);
void tx4938_spi_init(int busid);
void tx4938_ethaddw_init(unsigned chaw *addw0, unsigned chaw *addw1);
int tx4938_wepowt_pcicwk(void);
void tx4938_wepowt_pci1cwk(void);
int tx4938_pcicwk66_setup(void);
stwuct pci_dev;
int tx4938_pcic1_map_iwq(const stwuct pci_dev *dev, u8 swot);
void tx4938_setup_pcieww_iwq(void);
void tx4938_iwq_init(void);
void tx4938_mtd_init(int ch);
void tx4938_ndfmc_init(unsigned int howd, unsigned int spw);

stwuct tx4938ide_pwatfowm_info {
	/*
	 * I/O powt shift, fow pwatfowms with powts that awe
	 * constantwy spaced and need wawgew than the 1-byte
	 * spacing used by ata_std_powts().
	 */
	unsigned int iopowt_shift;
	unsigned int gbus_cwock;	/*  0 means no PIO mode tuning. */
	unsigned int ebus_ch;
};

void tx4938_ata_init(unsigned int iwq, unsigned int shift, int tune);
void tx4938_dmac_init(int memcpy_chan0, int memcpy_chan1);
void tx4938_acwc_init(void);
void tx4938_swamc_init(void);

#endif
