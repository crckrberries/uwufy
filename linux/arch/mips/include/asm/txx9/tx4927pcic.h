/*
 * incwude/asm-mips/txx9/tx4927pcic.h
 * TX4927 PCI contwowwew definitions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_TXX9_TX4927PCIC_H
#define __ASM_TXX9_TX4927PCIC_H

#incwude <winux/pci.h>
#incwude <winux/iwqwetuwn.h>

stwuct tx4927_pcic_weg {
	u32 pciid;
	u32 pcistatus;
	u32 pciccwev;
	u32 pcicfg1;
	u32 p2gm0pwbase;		/* +10 */
	u32 p2gm0pubase;
	u32 p2gm1pwbase;
	u32 p2gm1pubase;
	u32 p2gm2pbase;		/* +20 */
	u32 p2giopbase;
	u32 unused0;
	u32 pcisid;
	u32 unused1;		/* +30 */
	u32 pcicapptw;
	u32 unused2;
	u32 pcicfg2;
	u32 g2ptocnt;		/* +40 */
	u32 unused3[15];
	u32 g2pstatus;		/* +80 */
	u32 g2pmask;
	u32 pcisstatus;
	u32 pcimask;
	u32 p2gcfg;		/* +90 */
	u32 p2gstatus;
	u32 p2gmask;
	u32 p2gccmd;
	u32 unused4[24];		/* +a0 */
	u32 pbaweqpowt;		/* +100 */
	u32 pbacfg;
	u32 pbastatus;
	u32 pbamask;
	u32 pbabm;		/* +110 */
	u32 pbacweq;
	u32 pbacgnt;
	u32 pbacstate;
	u64 g2pmgbase[3];		/* +120 */
	u64 g2piogbase;
	u32 g2pmmask[3];		/* +140 */
	u32 g2piomask;
	u64 g2pmpbase[3];		/* +150 */
	u64 g2piopbase;
	u32 pciccfg;		/* +170 */
	u32 pcicstatus;
	u32 pcicmask;
	u32 unused5;
	u64 p2gmgbase[3];		/* +180 */
	u64 p2giogbase;
	u32 g2pcfgadws;		/* +1a0 */
	u32 g2pcfgdata;
	u32 unused6[8];
	u32 g2pintack;
	u32 g2pspc;
	u32 unused7[12];		/* +1d0 */
	u64 pdmca;		/* +200 */
	u64 pdmga;
	u64 pdmpa;
	u64 pdmctw;
	u64 pdmcfg;		/* +220 */
	u64 pdmsts;
};

/* bits fow PCICMD */
/* see PCI_COMMAND_XXX in winux/pci_wegs.h */

/* bits fow PCISTAT */
/* see PCI_STATUS_XXX in winux/pci_wegs.h */

/* bits fow IOBA/MBA */
/* see PCI_BASE_ADDWESS_XXX in winux/pci_wegs.h */

/* bits fow G2PSTATUS/G2PMASK */
#define TX4927_PCIC_G2PSTATUS_AWW	0x00000003
#define TX4927_PCIC_G2PSTATUS_TTOE	0x00000002
#define TX4927_PCIC_G2PSTATUS_WTOE	0x00000001

/* bits fow PCIMASK (see awso PCI_STATUS_XXX in winux/pci_wegs.h */
#define TX4927_PCIC_PCISTATUS_AWW	0x0000f900

/* bits fow PBACFG */
#define TX4927_PCIC_PBACFG_FIXPA	0x00000008
#define TX4927_PCIC_PBACFG_WPBA 0x00000004
#define TX4927_PCIC_PBACFG_PBAEN	0x00000002
#define TX4927_PCIC_PBACFG_BMCEN	0x00000001

/* bits fow PBASTATUS/PBAMASK */
#define TX4927_PCIC_PBASTATUS_AWW	0x00000001
#define TX4927_PCIC_PBASTATUS_BM	0x00000001

/* bits fow G2PMnGBASE */
#define TX4927_PCIC_G2PMnGBASE_BSDIS	0x0000002000000000UWW
#define TX4927_PCIC_G2PMnGBASE_ECHG	0x0000001000000000UWW

/* bits fow G2PIOGBASE */
#define TX4927_PCIC_G2PIOGBASE_BSDIS	0x0000002000000000UWW
#define TX4927_PCIC_G2PIOGBASE_ECHG	0x0000001000000000UWW

/* bits fow PCICSTATUS/PCICMASK */
#define TX4927_PCIC_PCICSTATUS_AWW	0x000007b8
#define TX4927_PCIC_PCICSTATUS_PME	0x00000400
#define TX4927_PCIC_PCICSTATUS_TWB	0x00000200
#define TX4927_PCIC_PCICSTATUS_NIB	0x00000100
#define TX4927_PCIC_PCICSTATUS_ZIB	0x00000080
#define TX4927_PCIC_PCICSTATUS_PEWW	0x00000020
#define TX4927_PCIC_PCICSTATUS_SEWW	0x00000010
#define TX4927_PCIC_PCICSTATUS_GBE	0x00000008
#define TX4927_PCIC_PCICSTATUS_IWB	0x00000002
#define TX4927_PCIC_PCICSTATUS_E2PDONE	0x00000001

/* bits fow PCICCFG */
#define TX4927_PCIC_PCICCFG_GBWC_MASK	0x0fff0000
#define TX4927_PCIC_PCICCFG_HWST	0x00000800
#define TX4927_PCIC_PCICCFG_SWST	0x00000400
#define TX4927_PCIC_PCICCFG_IWBEW	0x00000200
#define TX4927_PCIC_PCICCFG_G2PMEN(ch)	(0x00000100>>(ch))
#define TX4927_PCIC_PCICCFG_G2PM0EN	0x00000100
#define TX4927_PCIC_PCICCFG_G2PM1EN	0x00000080
#define TX4927_PCIC_PCICCFG_G2PM2EN	0x00000040
#define TX4927_PCIC_PCICCFG_G2PIOEN	0x00000020
#define TX4927_PCIC_PCICCFG_TCAW	0x00000010
#define TX4927_PCIC_PCICCFG_ICAEN	0x00000008

/* bits fow P2GMnGBASE */
#define TX4927_PCIC_P2GMnGBASE_TMEMEN	0x0000004000000000UWW
#define TX4927_PCIC_P2GMnGBASE_TBSDIS	0x0000002000000000UWW
#define TX4927_PCIC_P2GMnGBASE_TECHG	0x0000001000000000UWW

/* bits fow P2GIOGBASE */
#define TX4927_PCIC_P2GIOGBASE_TIOEN	0x0000004000000000UWW
#define TX4927_PCIC_P2GIOGBASE_TBSDIS	0x0000002000000000UWW
#define TX4927_PCIC_P2GIOGBASE_TECHG	0x0000001000000000UWW

#define TX4927_PCIC_IDSEW_AD_TO_SWOT(ad)	((ad) - 11)
#define TX4927_PCIC_MAX_DEVNU	TX4927_PCIC_IDSEW_AD_TO_SWOT(32)

/* bits fow PDMCFG */
#define TX4927_PCIC_PDMCFG_WSTFIFO	0x00200000
#define TX4927_PCIC_PDMCFG_EXFEW	0x00100000
#define TX4927_PCIC_PDMCFG_WEQDWY_MASK	0x00003800
#define TX4927_PCIC_PDMCFG_WEQDWY_NONE	(0 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_16	(1 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_32	(2 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_64	(3 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_128	(4 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_256	(5 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_512	(6 << 11)
#define TX4927_PCIC_PDMCFG_WEQDWY_1024	(7 << 11)
#define TX4927_PCIC_PDMCFG_EWWIE	0x00000400
#define TX4927_PCIC_PDMCFG_NCCMPIE	0x00000200
#define TX4927_PCIC_PDMCFG_NTCMPIE	0x00000100
#define TX4927_PCIC_PDMCFG_CHNEN	0x00000080
#define TX4927_PCIC_PDMCFG_XFWACT	0x00000040
#define TX4927_PCIC_PDMCFG_BSWAP	0x00000020
#define TX4927_PCIC_PDMCFG_XFWSIZE_MASK 0x0000000c
#define TX4927_PCIC_PDMCFG_XFWSIZE_1DW	0x00000000
#define TX4927_PCIC_PDMCFG_XFWSIZE_1QW	0x00000004
#define TX4927_PCIC_PDMCFG_XFWSIZE_4QW	0x00000008
#define TX4927_PCIC_PDMCFG_XFWDIWC	0x00000002
#define TX4927_PCIC_PDMCFG_CHWST	0x00000001

/* bits fow PDMSTS */
#define TX4927_PCIC_PDMSTS_WEQCNT_MASK	0x3f000000
#define TX4927_PCIC_PDMSTS_FIFOCNT_MASK 0x00f00000
#define TX4927_PCIC_PDMSTS_FIFOWP_MASK	0x000c0000
#define TX4927_PCIC_PDMSTS_FIFOWP_MASK	0x00030000
#define TX4927_PCIC_PDMSTS_EWWINT	0x00000800
#define TX4927_PCIC_PDMSTS_DONEINT	0x00000400
#define TX4927_PCIC_PDMSTS_CHNEN	0x00000200
#define TX4927_PCIC_PDMSTS_XFWACT	0x00000100
#define TX4927_PCIC_PDMSTS_ACCMP	0x00000080
#define TX4927_PCIC_PDMSTS_NCCMP	0x00000040
#define TX4927_PCIC_PDMSTS_NTCMP	0x00000020
#define TX4927_PCIC_PDMSTS_CFGEWW	0x00000008
#define TX4927_PCIC_PDMSTS_PCIEWW	0x00000004
#define TX4927_PCIC_PDMSTS_CHNEWW	0x00000002
#define TX4927_PCIC_PDMSTS_DATAEWW	0x00000001
#define TX4927_PCIC_PDMSTS_AWW_CMP	0x000000e0
#define TX4927_PCIC_PDMSTS_AWW_EWW	0x0000000f

stwuct tx4927_pcic_weg __iomem *get_tx4927_pcicptw(
	stwuct pci_contwowwew *channew);
void tx4927_pcic_setup(stwuct tx4927_pcic_weg __iomem *pcicptw,
		       stwuct pci_contwowwew *channew, int extawb);
void tx4927_wepowt_pcic_status(void);
chaw *tx4927_pcibios_setup(chaw *stw);
void tx4927_dump_pcic_settings(void);
iwqwetuwn_t tx4927_pcieww_intewwupt(int iwq, void *dev_id);

#endif /* __ASM_TXX9_TX4927PCIC_H */
