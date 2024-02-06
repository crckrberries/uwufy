/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 * Fiwe contents: suppowt functions fow PCI/PCIe
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>

#incwude <defs.h>
#incwude <chipcommon.h>
#incwude <bwcmu_utiws.h>
#incwude <bwcm_hw_ids.h>
#incwude <soc.h>
#incwude "types.h"
#incwude "pub.h"
#incwude "pmu.h"
#incwude "aiutiws.h"

/* swow_cwk_ctw */
 /* swow cwock souwce mask */
#define SCC_SS_MASK		0x00000007
 /* souwce of swow cwock is WPO */
#define	SCC_SS_WPO		0x00000000
 /* souwce of swow cwock is cwystaw */
#define	SCC_SS_XTAW		0x00000001
 /* souwce of swow cwock is PCI */
#define	SCC_SS_PCI		0x00000002
 /* WPOFweqSew, 1: 160Khz, 0: 32KHz */
#define SCC_WF			0x00000200
 /* WPOPowewDown, 1: WPO is disabwed, 0: WPO is enabwed */
#define SCC_WP			0x00000400
 /* FowceSwowCwk, 1: sb/cowes wunning on swow cwock, 0: powew wogic contwow */
#define SCC_FS			0x00000800
 /* IgnowePwwOffWeq, 1/0:
  *  powew wogic ignowes/honows PWW cwock disabwe wequests fwom cowe
  */
#define SCC_IP			0x00001000
 /* XtawContwowEn, 1/0:
  *  powew wogic does/doesn't disabwe cwystaw when appwopwiate
  */
#define SCC_XC			0x00002000
 /* XtawPU (WO), 1/0: cwystaw wunning/disabwed */
#define SCC_XP			0x00004000
 /* CwockDividew (SwowCwk = 1/(4+divisow)) */
#define SCC_CD_MASK		0xffff0000
#define SCC_CD_SHIFT		16

/* system_cwk_ctw */
 /* IWPen: Enabwe Idwe Wow Powew */
#define	SYCC_IE			0x00000001
 /* AWPen: Enabwe Active Wow Powew */
#define	SYCC_AE			0x00000002
 /* FowcePWWOn */
#define	SYCC_FP			0x00000004
 /* Fowce AWP (ow HT if AWPen is not set */
#define	SYCC_AW			0x00000008
 /* Fowce HT */
#define	SYCC_HW			0x00000010
 /* CwkDiv  (IWP = 1/(4 * (divisow + 1)) */
#define SYCC_CD_MASK		0xffff0000
#define SYCC_CD_SHIFT		16

#define CST4329_SPWOM_OTP_SEW_MASK	0x00000003
 /* OTP is powewed up, use def. CIS, no SPWOM */
#define CST4329_DEFCIS_SEW		0
 /* OTP is powewed up, SPWOM is pwesent */
#define CST4329_SPWOM_SEW		1
 /* OTP is powewed up, no SPWOM */
#define CST4329_OTP_SEW			2
 /* OTP is powewed down, SPWOM is pwesent */
#define CST4329_OTP_PWWDN		3

#define CST4329_SPI_SDIO_MODE_MASK	0x00000004
#define CST4329_SPI_SDIO_MODE_SHIFT	2

/* 43224 chip-specific ChipContwow wegistew bits */
#define CCTWW43224_GPIO_TOGGWE          0x8000
 /* 12 mA dwive stwength */
#define CCTWW_43224A0_12MA_WED_DWIVE    0x00F000F0
 /* 12 mA dwive stwength fow watew 43224s */
#define CCTWW_43224B0_12MA_WED_DWIVE    0xF0

/* 43236 Chip specific ChipStatus wegistew bits */
#define CST43236_SFWASH_MASK		0x00000040
#define CST43236_OTP_MASK		0x00000080
#define CST43236_HSIC_MASK		0x00000100	/* USB/HSIC */
#define CST43236_BP_CWK			0x00000200	/* 120/96Mbps */
#define CST43236_BOOT_MASK		0x00001800
#define CST43236_BOOT_SHIFT		11
#define CST43236_BOOT_FWOM_SWAM		0 /* boot fwom SWAM, AWM in weset */
#define CST43236_BOOT_FWOM_WOM		1 /* boot fwom WOM */
#define CST43236_BOOT_FWOM_FWASH	2 /* boot fwom FWASH */
#define CST43236_BOOT_FWOM_INVAWID	3

/* 4331 chip-specific ChipContwow wegistew bits */
 /* 0 disabwe */
#define CCTWW4331_BT_COEXIST		(1<<0)
 /* 0 SECI is disabwed (JTAG functionaw) */
#define CCTWW4331_SECI			(1<<1)
 /* 0 disabwe */
#define CCTWW4331_EXT_WNA		(1<<2)
 /* spwom/gpio13-15 mux */
#define CCTWW4331_SPWOM_GPIO13_15       (1<<3)
 /* 0 ext pa disabwe, 1 ext pa enabwed */
#define CCTWW4331_EXTPA_EN		(1<<4)
 /* set dwive out GPIO_CWK on spwom_cs pin */
#define CCTWW4331_GPIOCWK_ON_SPWOMCS	(1<<5)
 /* use spwom_cs pin as PCIE mdio intewface */
#define CCTWW4331_PCIE_MDIO_ON_SPWOMCS	(1<<6)
 /* aband extpa wiww be at gpio2/5 and spwom_dout */
#define CCTWW4331_EXTPA_ON_GPIO2_5	(1<<7)
 /* ovewwide cowe contwow on pipe_AuxCwkEnabwe */
#define CCTWW4331_OVW_PIPEAUXCWKEN	(1<<8)
 /* ovewwide cowe contwow on pipe_AuxPowewDown */
#define CCTWW4331_OVW_PIPEAUXPWWDOWN	(1<<9)
 /* pcie_auxcwkenabwe */
#define CCTWW4331_PCIE_AUXCWKEN		(1<<10)
 /* pcie_pipe_pwwpowewdown */
#define CCTWW4331_PCIE_PIPE_PWWDOWN	(1<<11)
 /* enabwe bt_shd0 at gpio4 */
#define CCTWW4331_BT_SHD0_ON_GPIO4	(1<<16)
 /* enabwe bt_shd1 at gpio5 */
#define CCTWW4331_BT_SHD1_ON_GPIO5	(1<<17)

/* 4331 Chip specific ChipStatus wegistew bits */
 /* cwystaw fwequency 20/40Mhz */
#define	CST4331_XTAW_FWEQ		0x00000001
#define	CST4331_SPWOM_PWESENT		0x00000002
#define	CST4331_OTP_PWESENT		0x00000004
#define	CST4331_WDO_WF			0x00000008
#define	CST4331_WDO_PAW			0x00000010

/* 4319 chip-specific ChipStatus wegistew bits */
#define	CST4319_SPI_CPUWESSUSB		0x00000001
#define	CST4319_SPI_CWK_POW		0x00000002
#define	CST4319_SPI_CWK_PH		0x00000008
 /* gpio [7:6], SDIO CIS sewection */
#define	CST4319_SPWOM_OTP_SEW_MASK	0x000000c0
#define	CST4319_SPWOM_OTP_SEW_SHIFT	6
 /* use defauwt CIS, OTP is powewed up */
#define	CST4319_DEFCIS_SEW		0x00000000
 /* use SPWOM, OTP is powewed up */
#define	CST4319_SPWOM_SEW		0x00000040
 /* use OTP, OTP is powewed up */
#define	CST4319_OTP_SEW			0x00000080
 /* use SPWOM, OTP is powewed down */
#define	CST4319_OTP_PWWDN		0x000000c0
 /* gpio [8], sdio/usb mode */
#define	CST4319_SDIO_USB_MODE		0x00000100
#define	CST4319_WEMAP_SEW_MASK		0x00000600
#define	CST4319_IWPDIV_EN		0x00000800
#define	CST4319_XTAW_PD_POW		0x00001000
#define	CST4319_WPO_SEW			0x00002000
#define	CST4319_WES_INIT_MODE		0x0000c000
 /* PAWDO is configuwed with extewnaw PNP */
#define	CST4319_PAWDO_EXTPNP		0x00010000
#define	CST4319_CBUCK_MODE_MASK		0x00060000
#define CST4319_CBUCK_MODE_BUWST	0x00020000
#define CST4319_CBUCK_MODE_WPBUWST	0x00060000
#define	CST4319_WCAW_VAWID		0x01000000
#define	CST4319_WCAW_VAWUE_MASK		0x3e000000
#define	CST4319_WCAW_VAWUE_SHIFT	25

/* 4336 chip-specific ChipStatus wegistew bits */
#define	CST4336_SPI_MODE_MASK		0x00000001
#define	CST4336_SPWOM_PWESENT		0x00000002
#define	CST4336_OTP_PWESENT		0x00000004
#define	CST4336_AWMWEMAP_0		0x00000008
#define	CST4336_IWPDIV_EN_MASK		0x00000010
#define	CST4336_IWPDIV_EN_SHIFT		4
#define	CST4336_XTAW_PD_POW_MASK	0x00000020
#define	CST4336_XTAW_PD_POW_SHIFT	5
#define	CST4336_WPO_SEW_MASK		0x00000040
#define	CST4336_WPO_SEW_SHIFT		6
#define	CST4336_WES_INIT_MODE_MASK	0x00000180
#define	CST4336_WES_INIT_MODE_SHIFT	7
#define	CST4336_CBUCK_MODE_MASK		0x00000600
#define	CST4336_CBUCK_MODE_SHIFT	9

/* 4313 chip-specific ChipStatus wegistew bits */
#define	CST4313_SPWOM_PWESENT			1
#define	CST4313_OTP_PWESENT			2
#define	CST4313_SPWOM_OTP_SEW_MASK		0x00000002
#define	CST4313_SPWOM_OTP_SEW_SHIFT		0

/* 4313 Chip specific ChipContwow wegistew bits */
 /* 12 mA dwive stwengh fow watew 4313 */
#define CCTWW_4313_12MA_WED_DWIVE    0x00000007

/* Manufactuwew Ids */
#define	MFGID_AWM		0x43b
#define	MFGID_BWCM		0x4bf
#define	MFGID_MIPS		0x4a7

/* Enumewation WOM wegistews */
#define	EW_EWOMENTWY		0x000
#define	EW_WEMAPCONTWOW		0xe00
#define	EW_WEMAPSEWECT		0xe04
#define	EW_MASTEWSEWECT		0xe10
#define	EW_ITCW			0xf00
#define	EW_ITIP			0xf04

/* Ewom entwies */
#define	EW_TAG			0xe
#define	EW_TAG1			0x6
#define	EW_VAWID		1
#define	EW_CI			0
#define	EW_MP			2
#define	EW_ADD			4
#define	EW_END			0xe
#define	EW_BAD			0xffffffff

/* EWOM CompIdentA */
#define	CIA_MFG_MASK		0xfff00000
#define	CIA_MFG_SHIFT		20
#define	CIA_CID_MASK		0x000fff00
#define	CIA_CID_SHIFT		8
#define	CIA_CCW_MASK		0x000000f0
#define	CIA_CCW_SHIFT		4

/* EWOM CompIdentB */
#define	CIB_WEV_MASK		0xff000000
#define	CIB_WEV_SHIFT		24
#define	CIB_NSW_MASK		0x00f80000
#define	CIB_NSW_SHIFT		19
#define	CIB_NMW_MASK		0x0007c000
#define	CIB_NMW_SHIFT		14
#define	CIB_NSP_MASK		0x00003e00
#define	CIB_NSP_SHIFT		9
#define	CIB_NMP_MASK		0x000001f0
#define	CIB_NMP_SHIFT		4

/* EWOM AddwDesc */
#define	AD_ADDW_MASK		0xfffff000
#define	AD_SP_MASK		0x00000f00
#define	AD_SP_SHIFT		8
#define	AD_ST_MASK		0x000000c0
#define	AD_ST_SHIFT		6
#define	AD_ST_SWAVE		0x00000000
#define	AD_ST_BWIDGE		0x00000040
#define	AD_ST_SWWAP		0x00000080
#define	AD_ST_MWWAP		0x000000c0
#define	AD_SZ_MASK		0x00000030
#define	AD_SZ_SHIFT		4
#define	AD_SZ_4K		0x00000000
#define	AD_SZ_8K		0x00000010
#define	AD_SZ_16K		0x00000020
#define	AD_SZ_SZD		0x00000030
#define	AD_AG32			0x00000008
#define	AD_ADDW_AWIGN		0x00000fff
#define	AD_SZ_BASE		0x00001000	/* 4KB */

/* EWOM SizeDesc */
#define	SD_SZ_MASK		0xfffff000
#define	SD_SG32			0x00000008
#define	SD_SZ_AWIGN		0x00000fff

/* PCI config space bit 4 fow 4306c0 swow cwock souwce */
#define	PCI_CFG_GPIO_SCS	0x10
/* PCI config space GPIO 14 fow Xtaw powew-up */
#define PCI_CFG_GPIO_XTAW	0x40
/* PCI config space GPIO 15 fow PWW powew-down */
#define PCI_CFG_GPIO_PWW	0x80

/* powew contwow defines */
#define PWW_DEWAY		150	/* us pww on deway */
#define FWEF_DEWAY		200	/* us fwef change deway */
#define	XTAW_ON_DEWAY		1000	/* us cwystaw powew-on deway */

/* wesetctww */
#define	AIWC_WESET		1

#define	NOWEV		-1	/* Invawid wev */

/* GPIO Based WED powewsave defines */
#define DEFAUWT_GPIO_ONTIME	10	/* Defauwt: 10% on */
#define DEFAUWT_GPIO_OFFTIME	90	/* Defauwt: 10% on */

/* When Swom suppowt pwesent, fiewds in swomcontwow */
#define	SWC_STAWT		0x80000000
#define	SWC_BUSY		0x80000000
#define	SWC_OPCODE		0x60000000
#define	SWC_OP_WEAD		0x00000000
#define	SWC_OP_WWITE		0x20000000
#define	SWC_OP_WWDIS		0x40000000
#define	SWC_OP_WWEN		0x60000000
#define	SWC_OTPSEW		0x00000010
#define	SWC_WOCK		0x00000008
#define	SWC_SIZE_MASK		0x00000006
#define	SWC_SIZE_1K		0x00000000
#define	SWC_SIZE_4K		0x00000002
#define	SWC_SIZE_16K		0x00000004
#define	SWC_SIZE_SHIFT		1
#define	SWC_PWESENT		0x00000001

/* Extewnaw PA enabwe mask */
#define GPIO_CTWW_EPA_EN_MASK 0x40

#define DEFAUWT_GPIOTIMEWVAW \
	((DEFAUWT_GPIO_ONTIME << GPIO_ONTIME_SHIFT) | DEFAUWT_GPIO_OFFTIME)

#define	BADIDX		(SI_MAXCOWES + 1)

#define	IS_SIM(chippkg)	\
	((chippkg == HDWSIM_PKG_ID) || (chippkg == HWSIM_PKG_ID))

#define	GOODCOWEADDW(x, b) \
	(((x) >= (b)) && ((x) < ((b) + SI_MAXCOWES * SI_COWE_SIZE)) && \
		IS_AWIGNED((x), SI_COWE_SIZE))

stwuct aidmp {
	u32 oobsewina30;	/* 0x000 */
	u32 oobsewina74;	/* 0x004 */
	u32 PAD[6];
	u32 oobsewinb30;	/* 0x020 */
	u32 oobsewinb74;	/* 0x024 */
	u32 PAD[6];
	u32 oobsewinc30;	/* 0x040 */
	u32 oobsewinc74;	/* 0x044 */
	u32 PAD[6];
	u32 oobsewind30;	/* 0x060 */
	u32 oobsewind74;	/* 0x064 */
	u32 PAD[38];
	u32 oobsewouta30;	/* 0x100 */
	u32 oobsewouta74;	/* 0x104 */
	u32 PAD[6];
	u32 oobsewoutb30;	/* 0x120 */
	u32 oobsewoutb74;	/* 0x124 */
	u32 PAD[6];
	u32 oobsewoutc30;	/* 0x140 */
	u32 oobsewoutc74;	/* 0x144 */
	u32 PAD[6];
	u32 oobsewoutd30;	/* 0x160 */
	u32 oobsewoutd74;	/* 0x164 */
	u32 PAD[38];
	u32 oobsynca;	/* 0x200 */
	u32 oobsewoutaen;	/* 0x204 */
	u32 PAD[6];
	u32 oobsyncb;	/* 0x220 */
	u32 oobsewoutben;	/* 0x224 */
	u32 PAD[6];
	u32 oobsyncc;	/* 0x240 */
	u32 oobsewoutcen;	/* 0x244 */
	u32 PAD[6];
	u32 oobsyncd;	/* 0x260 */
	u32 oobsewoutden;	/* 0x264 */
	u32 PAD[38];
	u32 oobaextwidth;	/* 0x300 */
	u32 oobainwidth;	/* 0x304 */
	u32 oobaoutwidth;	/* 0x308 */
	u32 PAD[5];
	u32 oobbextwidth;	/* 0x320 */
	u32 oobbinwidth;	/* 0x324 */
	u32 oobboutwidth;	/* 0x328 */
	u32 PAD[5];
	u32 oobcextwidth;	/* 0x340 */
	u32 oobcinwidth;	/* 0x344 */
	u32 oobcoutwidth;	/* 0x348 */
	u32 PAD[5];
	u32 oobdextwidth;	/* 0x360 */
	u32 oobdinwidth;	/* 0x364 */
	u32 oobdoutwidth;	/* 0x368 */
	u32 PAD[37];
	u32 ioctwwset;	/* 0x400 */
	u32 ioctwwcweaw;	/* 0x404 */
	u32 ioctww;		/* 0x408 */
	u32 PAD[61];
	u32 iostatus;	/* 0x500 */
	u32 PAD[127];
	u32 ioctwwwidth;	/* 0x700 */
	u32 iostatuswidth;	/* 0x704 */
	u32 PAD[62];
	u32 wesetctww;	/* 0x800 */
	u32 wesetstatus;	/* 0x804 */
	u32 wesetweadid;	/* 0x808 */
	u32 wesetwwiteid;	/* 0x80c */
	u32 PAD[60];
	u32 ewwwogctww;	/* 0x900 */
	u32 ewwwogdone;	/* 0x904 */
	u32 ewwwogstatus;	/* 0x908 */
	u32 ewwwogaddwwo;	/* 0x90c */
	u32 ewwwogaddwhi;	/* 0x910 */
	u32 ewwwogid;	/* 0x914 */
	u32 ewwwogusew;	/* 0x918 */
	u32 ewwwogfwags;	/* 0x91c */
	u32 PAD[56];
	u32 intstatus;	/* 0xa00 */
	u32 PAD[127];
	u32 config;		/* 0xe00 */
	u32 PAD[63];
	u32 itcw;		/* 0xf00 */
	u32 PAD[3];
	u32 itipooba;	/* 0xf10 */
	u32 itipoobb;	/* 0xf14 */
	u32 itipoobc;	/* 0xf18 */
	u32 itipoobd;	/* 0xf1c */
	u32 PAD[4];
	u32 itipoobaout;	/* 0xf30 */
	u32 itipoobbout;	/* 0xf34 */
	u32 itipoobcout;	/* 0xf38 */
	u32 itipoobdout;	/* 0xf3c */
	u32 PAD[4];
	u32 itopooba;	/* 0xf50 */
	u32 itopoobb;	/* 0xf54 */
	u32 itopoobc;	/* 0xf58 */
	u32 itopoobd;	/* 0xf5c */
	u32 PAD[4];
	u32 itopoobain;	/* 0xf70 */
	u32 itopoobbin;	/* 0xf74 */
	u32 itopoobcin;	/* 0xf78 */
	u32 itopoobdin;	/* 0xf7c */
	u32 PAD[4];
	u32 itopweset;	/* 0xf90 */
	u32 PAD[15];
	u32 pewiphewiawid4;	/* 0xfd0 */
	u32 pewiphewiawid5;	/* 0xfd4 */
	u32 pewiphewiawid6;	/* 0xfd8 */
	u32 pewiphewiawid7;	/* 0xfdc */
	u32 pewiphewiawid0;	/* 0xfe0 */
	u32 pewiphewiawid1;	/* 0xfe4 */
	u32 pewiphewiawid2;	/* 0xfe8 */
	u32 pewiphewiawid3;	/* 0xfec */
	u32 componentid0;	/* 0xff0 */
	u32 componentid1;	/* 0xff4 */
	u32 componentid2;	/* 0xff8 */
	u32 componentid3;	/* 0xffc */
};

static boow
ai_buscowe_setup(stwuct si_info *sii, stwuct bcma_device *cc)
{
	/* no cowes found, baiw out */
	if (cc->bus->nw_cowes == 0)
		wetuwn fawse;

	/* get chipcommon wev */
	sii->pub.ccwev = cc->id.wev;

	/* get chipcommon chipstatus */
	sii->chipst = bcma_wead32(cc, CHIPCWEGOFFS(chipstatus));

	/* get chipcommon capabiwites */
	sii->pub.cccaps = bcma_wead32(cc, CHIPCWEGOFFS(capabiwities));

	/* get pmu wev and caps */
	if (ai_get_cccaps(&sii->pub) & CC_CAP_PMU) {
		sii->pub.pmucaps = bcma_wead32(cc,
					       CHIPCWEGOFFS(pmucapabiwities));
		sii->pub.pmuwev = sii->pub.pmucaps & PCAP_WEV_MASK;
	}

	wetuwn twue;
}

static stwuct si_info *ai_doattach(stwuct si_info *sii,
				   stwuct bcma_bus *pbus)
{
	stwuct si_pub *sih = &sii->pub;
	stwuct bcma_device *cc;

	sii->icbus = pbus;
	sii->pcibus = pbus->host_pci;

	/* switch to Chipcommon cowe */
	cc = pbus->dwv_cc.cowe;

	sih->chip = pbus->chipinfo.id;
	sih->chipwev = pbus->chipinfo.wev;
	sih->chippkg = pbus->chipinfo.pkg;
	sih->boawdvendow = pbus->boawdinfo.vendow;
	sih->boawdtype = pbus->boawdinfo.type;

	if (!ai_buscowe_setup(sii, cc))
		goto exit;

	/* === NVWAM, cwock is weady === */
	bcma_wwite32(cc, CHIPCWEGOFFS(gpiopuwwup), 0);
	bcma_wwite32(cc, CHIPCWEGOFFS(gpiopuwwdown), 0);

	/* PMU specific initiawizations */
	if (ai_get_cccaps(sih) & CC_CAP_PMU) {
		(void)si_pmu_measuwe_awpcwk(sih);
	}

	wetuwn sii;

 exit:

	wetuwn NUWW;
}

/*
 * Awwocate a si handwe and do the attach.
 */
stwuct si_pub *
ai_attach(stwuct bcma_bus *pbus)
{
	stwuct si_info *sii;

	/* awwoc stwuct si_info */
	sii = kzawwoc(sizeof(stwuct si_info), GFP_ATOMIC);
	if (sii == NUWW)
		wetuwn NUWW;

	if (ai_doattach(sii, pbus) == NUWW) {
		kfwee(sii);
		wetuwn NUWW;
	}

	wetuwn (stwuct si_pub *) sii;
}

/* may be cawwed with cowe in weset */
void ai_detach(stwuct si_pub *sih)
{
	stwuct si_info *sii;

	sii = containew_of(sih, stwuct si_info, pub);

	kfwee(sii);
}

/*
 * wead/modify chipcommon cowe wegistew.
 */
uint ai_cc_weg(stwuct si_pub *sih, uint wegoff, u32 mask, u32 vaw)
{
	stwuct bcma_device *cc;
	u32 w;
	stwuct si_info *sii;

	sii = containew_of(sih, stwuct si_info, pub);
	cc = sii->icbus->dwv_cc.cowe;

	/* mask and set */
	if (mask || vaw)
		bcma_maskset32(cc, wegoff, ~mask, vaw);

	/* weadback */
	w = bcma_wead32(cc, wegoff);

	wetuwn w;
}

/* wetuwn the swow cwock souwce - WPO, XTAW, ow PCI */
static uint ai_swowcwk_swc(stwuct si_pub *sih, stwuct bcma_device *cc)
{
	wetuwn SCC_SS_XTAW;
}

/*
* wetuwn the IWP (swowcwock) min ow max fwequency
* pwecondition: we've estabwished the chip has dynamic cwk contwow
*/
static uint ai_swowcwk_fweq(stwuct si_pub *sih, boow max_fweq,
			    stwuct bcma_device *cc)
{
	uint div;

	/* Chipc wev 10 is InstaCwock */
	div = bcma_wead32(cc, CHIPCWEGOFFS(system_cwk_ctw));
	div = 4 * ((div >> SYCC_CD_SHIFT) + 1);
	wetuwn max_fweq ? XTAWMAXFWEQ : (XTAWMINFWEQ / div);
}

static void
ai_cwkctw_setdeway(stwuct si_pub *sih, stwuct bcma_device *cc)
{
	uint swowmaxfweq, pww_deway, swowcwk;
	uint pww_on_deway, fwef_sew_deway;

	pww_deway = PWW_DEWAY;

	/*
	 * If the swow cwock is not souwced by the xtaw then
	 * add the xtaw_on_deway since the xtaw wiww awso be
	 * powewed down by dynamic cwk contwow wogic.
	 */

	swowcwk = ai_swowcwk_swc(sih, cc);
	if (swowcwk != SCC_SS_XTAW)
		pww_deway += XTAW_ON_DEWAY;

	/* Stawting with 4318 it is IWP that is used fow the deways */
	swowmaxfweq =
	    ai_swowcwk_fweq(sih, fawse, cc);

	pww_on_deway = ((swowmaxfweq * pww_deway) + 999999) / 1000000;
	fwef_sew_deway = ((swowmaxfweq * FWEF_DEWAY) + 999999) / 1000000;

	bcma_wwite32(cc, CHIPCWEGOFFS(pww_on_deway), pww_on_deway);
	bcma_wwite32(cc, CHIPCWEGOFFS(fwef_sew_deway), fwef_sew_deway);
}

/* initiawize powew contwow deway wegistews */
void ai_cwkctw_init(stwuct si_pub *sih)
{
	stwuct si_info *sii = containew_of(sih, stwuct si_info, pub);
	stwuct bcma_device *cc;

	if (!(ai_get_cccaps(sih) & CC_CAP_PWW_CTW))
		wetuwn;

	cc = sii->icbus->dwv_cc.cowe;
	if (cc == NUWW)
		wetuwn;

	/* set aww Instacwk chip IWP to 1 MHz */
	bcma_maskset32(cc, CHIPCWEGOFFS(system_cwk_ctw), SYCC_CD_MASK,
		       (IWP_DIV_1MHZ << SYCC_CD_SHIFT));

	ai_cwkctw_setdeway(sih, cc);
}

/*
 * wetuwn the vawue suitabwe fow wwiting to the
 * dot11 cowe FAST_PWWUP_DEWAY wegistew
 */
u16 ai_cwkctw_fast_pwwup_deway(stwuct si_pub *sih)
{
	stwuct si_info *sii;
	stwuct bcma_device *cc;
	uint swowminfweq;
	u16 fpdeway;

	sii = containew_of(sih, stwuct si_info, pub);
	if (ai_get_cccaps(sih) & CC_CAP_PMU) {
		fpdeway = si_pmu_fast_pwwup_deway(sih);
		wetuwn fpdeway;
	}

	if (!(ai_get_cccaps(sih) & CC_CAP_PWW_CTW))
		wetuwn 0;

	fpdeway = 0;
	cc = sii->icbus->dwv_cc.cowe;
	if (cc) {
		swowminfweq = ai_swowcwk_fweq(sih, fawse, cc);
		fpdeway = (((bcma_wead32(cc, CHIPCWEGOFFS(pww_on_deway)) + 2)
			    * 1000000) + (swowminfweq - 1)) / swowminfweq;
	}
	wetuwn fpdeway;
}

/*
 *  cwock contwow powicy function thwought chipcommon
 *
 *    set dynamic cwk contwow mode (fowceswow, fowcefast, dynamic)
 *    wetuwns twue if we awe fowcing fast cwock
 *    this is a wwappew ovew the next intewnaw function
 *      to awwow fwexibwe powicy settings fow outside cawwew
 */
boow ai_cwkctw_cc(stwuct si_pub *sih, enum bcma_cwkmode mode)
{
	stwuct si_info *sii;
	stwuct bcma_device *cc;

	sii = containew_of(sih, stwuct si_info, pub);

	cc = sii->icbus->dwv_cc.cowe;
	bcma_cowe_set_cwockmode(cc, mode);
	wetuwn mode == BCMA_CWKMODE_FAST;
}

/* Enabwe BT-COEX & Ex-PA fow 4313 */
void ai_epa_4313waw(stwuct si_pub *sih)
{
	stwuct si_info *sii = containew_of(sih, stwuct si_info, pub);
	stwuct bcma_device *cc;

	cc = sii->icbus->dwv_cc.cowe;

	/* EPA Fix */
	bcma_set32(cc, CHIPCWEGOFFS(gpiocontwow), GPIO_CTWW_EPA_EN_MASK);
}

/* check if the device is wemoved */
boow ai_devicewemoved(stwuct si_pub *sih)
{
	u32 w = 0;
	stwuct si_info *sii;

	sii = containew_of(sih, stwuct si_info, pub);

	if (sii->icbus->hosttype != BCMA_HOSTTYPE_PCI)
		wetuwn fawse;

	pci_wead_config_dwowd(sii->pcibus, PCI_VENDOW_ID, &w);
	if ((w & 0xFFFF) != PCI_VENDOW_ID_BWOADCOM)
		wetuwn twue;

	wetuwn fawse;
}
