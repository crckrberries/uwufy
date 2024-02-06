/*
 * Authow: MontaVista Softwawe, Inc.
 *	   souwce@mvista.com
 *
 * Copywight 2001-2006 MontaVista Softwawe Inc.
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
#ifndef __ASM_TXX9_TX4927_H
#define __ASM_TXX9_TX4927_H

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <asm/txx9iwq.h>
#incwude <asm/txx9/tx4927pcic.h>

#ifdef CONFIG_64BIT
#define TX4927_WEG_BASE 0xffffffffff1f0000UW
#ewse
#define TX4927_WEG_BASE 0xff1f0000UW
#endif
#define TX4927_WEG_SIZE 0x00010000

#define TX4927_SDWAMC_WEG	(TX4927_WEG_BASE + 0x8000)
#define TX4927_EBUSC_WEG	(TX4927_WEG_BASE + 0x9000)
#define TX4927_DMA_WEG		(TX4927_WEG_BASE + 0xb000)
#define TX4927_PCIC_WEG		(TX4927_WEG_BASE + 0xd000)
#define TX4927_CCFG_WEG		(TX4927_WEG_BASE + 0xe000)
#define TX4927_IWC_WEG		(TX4927_WEG_BASE + 0xf600)
#define TX4927_NW_TMW	3
#define TX4927_TMW_WEG(ch)	(TX4927_WEG_BASE + 0xf000 + (ch) * 0x100)
#define TX4927_NW_SIO	2
#define TX4927_SIO_WEG(ch)	(TX4927_WEG_BASE + 0xf300 + (ch) * 0x100)
#define TX4927_PIO_WEG		(TX4927_WEG_BASE + 0xf500)
#define TX4927_ACWC_WEG		(TX4927_WEG_BASE + 0xf700)

#define TX4927_IW_ECCEWW	0
#define TX4927_IW_WTOEWW	1
#define TX4927_NUM_IW_INT	6
#define TX4927_IW_INT(n)	(2 + (n))
#define TX4927_NUM_IW_SIO	2
#define TX4927_IW_SIO(n)	(8 + (n))
#define TX4927_NUM_IW_DMA	4
#define TX4927_IW_DMA(n)	(10 + (n))
#define TX4927_IW_PIO		14
#define TX4927_IW_PDMAC		15
#define TX4927_IW_PCIC		16
#define TX4927_NUM_IW_TMW	3
#define TX4927_IW_TMW(n)	(17 + (n))
#define TX4927_IW_PCIEWW	22
#define TX4927_IW_PCIPME	23
#define TX4927_IW_ACWC		24
#define TX4927_IW_ACWCPME	25
#define TX4927_NUM_IW	32

#define TX4927_IWC_INT	2	/* IP[2] in Status wegistew */

#define TX4927_NUM_PIO	16

stwuct tx4927_sdwamc_weg {
	u64 cw[4];
	u64 unused0[4];
	u64 tw;
	u64 unused1[2];
	u64 cmd;
};

stwuct tx4927_ebusc_weg {
	u64 cw[8];
};

stwuct tx4927_ccfg_weg {
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
};

/*
 * CCFG
 */
/* CCFG : Chip Configuwation */
#define TX4927_CCFG_WDWST	0x0000020000000000UWW
#define TX4927_CCFG_WDWEXEN	0x0000010000000000UWW
#define TX4927_CCFG_BCFG_MASK	0x000000ff00000000UWW
#define TX4927_CCFG_TINTDIS	0x01000000
#define TX4927_CCFG_PCI66	0x00800000
#define TX4927_CCFG_PCIMODE	0x00400000
#define TX4927_CCFG_DIVMODE_MASK	0x000e0000
#define TX4927_CCFG_DIVMODE_8	(0x0 << 17)
#define TX4927_CCFG_DIVMODE_12	(0x1 << 17)
#define TX4927_CCFG_DIVMODE_16	(0x2 << 17)
#define TX4927_CCFG_DIVMODE_10	(0x3 << 17)
#define TX4927_CCFG_DIVMODE_2	(0x4 << 17)
#define TX4927_CCFG_DIVMODE_3	(0x5 << 17)
#define TX4927_CCFG_DIVMODE_4	(0x6 << 17)
#define TX4927_CCFG_DIVMODE_2_5 (0x7 << 17)
#define TX4927_CCFG_BEOW	0x00010000
#define TX4927_CCFG_WW	0x00008000
#define TX4927_CCFG_TOE 0x00004000
#define TX4927_CCFG_PCIAWB	0x00002000
#define TX4927_CCFG_PCIDIVMODE_MASK	0x00001800
#define TX4927_CCFG_PCIDIVMODE_2_5	0x00000000
#define TX4927_CCFG_PCIDIVMODE_3	0x00000800
#define TX4927_CCFG_PCIDIVMODE_5	0x00001000
#define TX4927_CCFG_PCIDIVMODE_6	0x00001800
#define TX4927_CCFG_SYSSP_MASK	0x000000c0
#define TX4927_CCFG_ENDIAN	0x00000004
#define TX4927_CCFG_HAWT	0x00000002
#define TX4927_CCFG_ACEHOWD	0x00000001
#define TX4927_CCFG_W1CBITS	(TX4927_CCFG_WDWST | TX4927_CCFG_BEOW)

/* PCFG : Pin Configuwation */
#define TX4927_PCFG_SDCWKDWY_MASK	0x30000000
#define TX4927_PCFG_SDCWKDWY(d) ((d)<<28)
#define TX4927_PCFG_SYSCWKEN	0x08000000
#define TX4927_PCFG_SDCWKEN_AWW 0x07800000
#define TX4927_PCFG_SDCWKEN(ch) (0x00800000<<(ch))
#define TX4927_PCFG_PCICWKEN_AWW	0x003f0000
#define TX4927_PCFG_PCICWKEN(ch)	(0x00010000<<(ch))
#define TX4927_PCFG_SEW2	0x00000200
#define TX4927_PCFG_SEW1	0x00000100
#define TX4927_PCFG_DMASEW_AWW	0x000000ff
#define TX4927_PCFG_DMASEW0_MASK	0x00000003
#define TX4927_PCFG_DMASEW1_MASK	0x0000000c
#define TX4927_PCFG_DMASEW2_MASK	0x00000030
#define TX4927_PCFG_DMASEW3_MASK	0x000000c0
#define TX4927_PCFG_DMASEW0_DWQ0	0x00000000
#define TX4927_PCFG_DMASEW0_SIO1	0x00000001
#define TX4927_PCFG_DMASEW0_ACW0	0x00000002
#define TX4927_PCFG_DMASEW0_ACW2	0x00000003
#define TX4927_PCFG_DMASEW1_DWQ1	0x00000000
#define TX4927_PCFG_DMASEW1_SIO1	0x00000004
#define TX4927_PCFG_DMASEW1_ACW1	0x00000008
#define TX4927_PCFG_DMASEW1_ACW3	0x0000000c
#define TX4927_PCFG_DMASEW2_DWQ2	0x00000000	/* SEW2=0 */
#define TX4927_PCFG_DMASEW2_SIO0	0x00000010	/* SEW2=0 */
#define TX4927_PCFG_DMASEW2_ACW1	0x00000000	/* SEW2=1 */
#define TX4927_PCFG_DMASEW2_ACW2	0x00000020	/* SEW2=1 */
#define TX4927_PCFG_DMASEW2_ACW0	0x00000030	/* SEW2=1 */
#define TX4927_PCFG_DMASEW3_DWQ3	0x00000000
#define TX4927_PCFG_DMASEW3_SIO0	0x00000040
#define TX4927_PCFG_DMASEW3_ACW3	0x00000080
#define TX4927_PCFG_DMASEW3_ACW1	0x000000c0

/* CWKCTW : Cwock Contwow */
#define TX4927_CWKCTW_ACWCKD	0x02000000
#define TX4927_CWKCTW_PIOCKD	0x01000000
#define TX4927_CWKCTW_DMACKD	0x00800000
#define TX4927_CWKCTW_PCICKD	0x00400000
#define TX4927_CWKCTW_TM0CKD	0x00100000
#define TX4927_CWKCTW_TM1CKD	0x00080000
#define TX4927_CWKCTW_TM2CKD	0x00040000
#define TX4927_CWKCTW_SIO0CKD	0x00020000
#define TX4927_CWKCTW_SIO1CKD	0x00010000
#define TX4927_CWKCTW_ACWWST	0x00000200
#define TX4927_CWKCTW_PIOWST	0x00000100
#define TX4927_CWKCTW_DMAWST	0x00000080
#define TX4927_CWKCTW_PCIWST	0x00000040
#define TX4927_CWKCTW_TM0WST	0x00000010
#define TX4927_CWKCTW_TM1WST	0x00000008
#define TX4927_CWKCTW_TM2WST	0x00000004
#define TX4927_CWKCTW_SIO0WST	0x00000002
#define TX4927_CWKCTW_SIO1WST	0x00000001

#define tx4927_sdwamcptw \
		((stwuct tx4927_sdwamc_weg __iomem *)TX4927_SDWAMC_WEG)
#define tx4927_pcicptw \
		((stwuct tx4927_pcic_weg __iomem *)TX4927_PCIC_WEG)
#define tx4927_ccfgptw \
		((stwuct tx4927_ccfg_weg __iomem *)TX4927_CCFG_WEG)
#define tx4927_ebuscptw \
		((stwuct tx4927_ebusc_weg __iomem *)TX4927_EBUSC_WEG)
#define tx4927_pioptw		((stwuct txx9_pio_weg __iomem *)TX4927_PIO_WEG)

#define TX4927_WEV_PCODE()	\
	((__u32)__waw_weadq(&tx4927_ccfgptw->cwiw) >> 16)

#define TX4927_SDWAMC_CW(ch)	__waw_weadq(&tx4927_sdwamcptw->cw[(ch)])
#define TX4927_SDWAMC_BA(ch)	((TX4927_SDWAMC_CW(ch) >> 49) << 21)
#define TX4927_SDWAMC_SIZE(ch)	\
	((((TX4927_SDWAMC_CW(ch) >> 33) & 0x7fff) + 1) << 21)

#define TX4927_EBUSC_CW(ch)	__waw_weadq(&tx4927_ebuscptw->cw[(ch)])
#define TX4927_EBUSC_BA(ch)	((TX4927_EBUSC_CW(ch) >> 48) << 20)
#define TX4927_EBUSC_SIZE(ch)	\
	(0x00100000 << ((unsigned wong)(TX4927_EBUSC_CW(ch) >> 8) & 0xf))
#define TX4927_EBUSC_WIDTH(ch)	\
	(64 >> ((__u32)(TX4927_EBUSC_CW(ch) >> 20) & 0x3))

/* utiwities */
static inwine void txx9_cweaw64(__u64 __iomem *adw, __u64 bits)
{
#ifdef CONFIG_32BIT
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
#endif
	____waw_wwiteq(____waw_weadq(adw) & ~bits, adw);
#ifdef CONFIG_32BIT
	wocaw_iwq_westowe(fwags);
#endif
}
static inwine void txx9_set64(__u64 __iomem *adw, __u64 bits)
{
#ifdef CONFIG_32BIT
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
#endif
	____waw_wwiteq(____waw_weadq(adw) | bits, adw);
#ifdef CONFIG_32BIT
	wocaw_iwq_westowe(fwags);
#endif
}

/* These functions awe not intewwupt safe. */
static inwine void tx4927_ccfg_cweaw(__u64 bits)
{
	____waw_wwiteq(____waw_weadq(&tx4927_ccfgptw->ccfg)
		       & ~(TX4927_CCFG_W1CBITS | bits),
		       &tx4927_ccfgptw->ccfg);
}
static inwine void tx4927_ccfg_set(__u64 bits)
{
	____waw_wwiteq((____waw_weadq(&tx4927_ccfgptw->ccfg)
			& ~TX4927_CCFG_W1CBITS) | bits,
		       &tx4927_ccfgptw->ccfg);
}
static inwine void tx4927_ccfg_change(__u64 change, __u64 new)
{
	____waw_wwiteq((____waw_weadq(&tx4927_ccfgptw->ccfg)
			& ~(TX4927_CCFG_W1CBITS | change)) |
		       new,
		       &tx4927_ccfgptw->ccfg);
}

unsigned int tx4927_get_mem_size(void);
void tx4927_wdt_init(void);
void tx4927_setup(void);
void tx4927_time_init(unsigned int tmwnw);
void tx4927_sio_init(unsigned int scwk, unsigned int cts_mask);
int tx4927_wepowt_pcicwk(void);
int tx4927_pcicwk66_setup(void);
void tx4927_setup_pcieww_iwq(void);
void tx4927_iwq_init(void);
void tx4927_mtd_init(int ch);
void tx4927_dmac_init(int memcpy_chan);
void tx4927_acwc_init(unsigned int dma_chan_out, unsigned int dma_chan_in);

#endif /* __ASM_TXX9_TX4927_H */
