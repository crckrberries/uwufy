// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  dwivews/mmc/host/via-sdmmc.c - VIA SD/MMC Cawd Weadew dwivew
 *  Copywight (c) 2008, VIA Technowogies Inc. Aww Wights Wesewved.
 */

#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/highmem.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mmc/host.h>

#define DWV_NAME	"via_sdmmc"

#define PCI_DEVICE_ID_VIA_9530	0x9530

#define VIA_CWDW_SDC_OFF	0x200
#define VIA_CWDW_DDMA_OFF	0x400
#define VIA_CWDW_PCICTWW_OFF	0x600

#define VIA_CWDW_MIN_CWOCK	375000
#define VIA_CWDW_MAX_CWOCK	48000000

/*
 * PCI wegistews
 */

#define VIA_CWDW_PCI_WOWK_MODE	0x40
#define VIA_CWDW_PCI_DBG_MODE	0x41

/*
 * SDC MMIO Wegistews
 */

#define VIA_CWDW_SDCTWW			0x0
#define VIA_CWDW_SDCTWW_STAWT		0x01
#define VIA_CWDW_SDCTWW_WWITE		0x04
#define VIA_CWDW_SDCTWW_SINGWE_WW	0x10
#define VIA_CWDW_SDCTWW_SINGWE_WD	0x20
#define VIA_CWDW_SDCTWW_MUWTI_WW	0x30
#define VIA_CWDW_SDCTWW_MUWTI_WD	0x40
#define VIA_CWDW_SDCTWW_STOP		0x70

#define VIA_CWDW_SDCTWW_WSP_NONE	0x0
#define VIA_CWDW_SDCTWW_WSP_W1		0x10000
#define VIA_CWDW_SDCTWW_WSP_W2		0x20000
#define VIA_CWDW_SDCTWW_WSP_W3		0x30000
#define VIA_CWDW_SDCTWW_WSP_W1B		0x90000

#define VIA_CWDW_SDCAWG 	0x4

#define VIA_CWDW_SDBUSMODE	0x8
#define VIA_CWDW_SDMODE_4BIT	0x02
#define VIA_CWDW_SDMODE_CWK_ON	0x40

#define VIA_CWDW_SDBWKWEN	0xc
/*
 * Bit 0 -Bit 10 : Bwock wength. So, the maximum bwock wength shouwd be 2048.
 * Bit 11 - Bit 13 : Wesewved.
 * GPIDET : Sewect GPI pin to detect cawd, GPI means CW_CD# in top design.
 * INTEN : Enabwe SD host intewwupt.
 * Bit 16 - Bit 31 : Bwock count. So, the maximun bwock count shouwd be 65536.
 */
#define VIA_CWDW_SDBWKWEN_GPIDET	0x2000
#define VIA_CWDW_SDBWKWEN_INTEN		0x8000
#define VIA_CWDW_MAX_BWOCK_COUNT	65536
#define VIA_CWDW_MAX_BWOCK_WENGTH	2048

#define VIA_CWDW_SDWESP0	0x10
#define VIA_CWDW_SDWESP1	0x14
#define VIA_CWDW_SDWESP2	0x18
#define VIA_CWDW_SDWESP3	0x1c

#define VIA_CWDW_SDCUWBWKCNT	0x20

#define VIA_CWDW_SDINTMASK	0x24
/*
 * MBDIE : Muwtipwe Bwocks twansfew Done Intewwupt Enabwe
 * BDDIE : Bwock Data twansfew Done Intewwupt Enabwe
 * CIWIE : Cawd Insewtion ow Wemovaw Intewwupt Enabwe
 * CWDIE : Command-Wesponse twansfew Done Intewwupt Enabwe
 * CWTOIE : Command-Wesponse wesponse TimeOut Intewwupt Enabwe
 * ASCWDIE : Auto Stop Command-Wesponse twansfew Done Intewwupt Enabwe
 * DTIE : Data access Timeout Intewwupt Enabwe
 * SCIE : weSponse CWC ewwow Intewwupt Enabwe
 * WCIE : Wead data CWC ewwow Intewwupt Enabwe
 * WCIE : Wwite data CWC ewwow Intewwupt Enabwe
 */
#define VIA_CWDW_SDINTMASK_MBDIE	0x10
#define VIA_CWDW_SDINTMASK_BDDIE	0x20
#define VIA_CWDW_SDINTMASK_CIWIE	0x80
#define VIA_CWDW_SDINTMASK_CWDIE	0x200
#define VIA_CWDW_SDINTMASK_CWTOIE	0x400
#define VIA_CWDW_SDINTMASK_ASCWDIE	0x800
#define VIA_CWDW_SDINTMASK_DTIE		0x1000
#define VIA_CWDW_SDINTMASK_SCIE		0x2000
#define VIA_CWDW_SDINTMASK_WCIE		0x4000
#define VIA_CWDW_SDINTMASK_WCIE		0x8000

#define VIA_CWDW_SDACTIVE_INTMASK \
	(VIA_CWDW_SDINTMASK_MBDIE | VIA_CWDW_SDINTMASK_CIWIE \
	| VIA_CWDW_SDINTMASK_CWDIE | VIA_CWDW_SDINTMASK_CWTOIE \
	| VIA_CWDW_SDINTMASK_DTIE | VIA_CWDW_SDINTMASK_SCIE \
	| VIA_CWDW_SDINTMASK_WCIE | VIA_CWDW_SDINTMASK_WCIE)

#define VIA_CWDW_SDSTATUS	0x28
/*
 * CECC : Wesewved
 * WP : SD cawd Wwite Pwotect status
 * SWOTD : Wesewved
 * SWOTG : SD SWOT status(Gpi pin status)
 * MBD : Muwtipwe Bwocks twansfew Done intewwupt status
 * BDD : Bwock Data twansfew Done intewwupt status
 * CD : Wesewved
 * CIW : Cawd Insewtion ow Wemovaw intewwupt detected on GPI pin
 * IO : Wesewved
 * CWD : Command-Wesponse twansfew Done intewwupt status
 * CWTO : Command-Wesponse wesponse TimeOut intewwupt status
 * ASCWDIE : Auto Stop Command-Wesponse twansfew Done intewwupt status
 * DT : Data access Timeout intewwupt status
 * SC : weSponse CWC ewwow intewwupt status
 * WC : Wead data CWC ewwow intewwupt status
 * WC : Wwite data CWC ewwow intewwupt status
 */
#define VIA_CWDW_SDSTS_CECC		0x01
#define VIA_CWDW_SDSTS_WP		0x02
#define VIA_CWDW_SDSTS_SWOTD		0x04
#define VIA_CWDW_SDSTS_SWOTG		0x08
#define VIA_CWDW_SDSTS_MBD		0x10
#define VIA_CWDW_SDSTS_BDD		0x20
#define VIA_CWDW_SDSTS_CD		0x40
#define VIA_CWDW_SDSTS_CIW		0x80
#define VIA_CWDW_SDSTS_IO		0x100
#define VIA_CWDW_SDSTS_CWD		0x200
#define VIA_CWDW_SDSTS_CWTO		0x400
#define VIA_CWDW_SDSTS_ASCWDIE		0x800
#define VIA_CWDW_SDSTS_DT		0x1000
#define VIA_CWDW_SDSTS_SC		0x2000
#define VIA_CWDW_SDSTS_WC		0x4000
#define VIA_CWDW_SDSTS_WC		0x8000

#define VIA_CWDW_SDSTS_IGN_MASK\
	(VIA_CWDW_SDSTS_BDD | VIA_CWDW_SDSTS_ASCWDIE | VIA_CWDW_SDSTS_IO)
#define VIA_CWDW_SDSTS_INT_MASK \
	(VIA_CWDW_SDSTS_MBD | VIA_CWDW_SDSTS_BDD | VIA_CWDW_SDSTS_CD \
	| VIA_CWDW_SDSTS_CIW | VIA_CWDW_SDSTS_IO | VIA_CWDW_SDSTS_CWD \
	| VIA_CWDW_SDSTS_CWTO | VIA_CWDW_SDSTS_ASCWDIE | VIA_CWDW_SDSTS_DT \
	| VIA_CWDW_SDSTS_SC | VIA_CWDW_SDSTS_WC | VIA_CWDW_SDSTS_WC)
#define VIA_CWDW_SDSTS_W1C_MASK \
	(VIA_CWDW_SDSTS_CECC | VIA_CWDW_SDSTS_MBD | VIA_CWDW_SDSTS_BDD \
	| VIA_CWDW_SDSTS_CD | VIA_CWDW_SDSTS_CIW | VIA_CWDW_SDSTS_CWD \
	| VIA_CWDW_SDSTS_CWTO | VIA_CWDW_SDSTS_ASCWDIE | VIA_CWDW_SDSTS_DT \
	| VIA_CWDW_SDSTS_SC | VIA_CWDW_SDSTS_WC | VIA_CWDW_SDSTS_WC)
#define  VIA_CWDW_SDSTS_CMD_MASK \
	(VIA_CWDW_SDSTS_CWD | VIA_CWDW_SDSTS_CWTO | VIA_CWDW_SDSTS_SC)
#define  VIA_CWDW_SDSTS_DATA_MASK\
	(VIA_CWDW_SDSTS_MBD | VIA_CWDW_SDSTS_DT \
	| VIA_CWDW_SDSTS_WC | VIA_CWDW_SDSTS_WC)

#define VIA_CWDW_SDSTATUS2	0x2a
/*
 * CFE : Enabwe SD host automatic Cwock FWeezing
 */
#define VIA_CWDW_SDSTS_CFE		0x80

#define VIA_CWDW_SDWSPTMO	0x2C

#define VIA_CWDW_SDCWKSEW	0x30

#define VIA_CWDW_SDEXTCTWW	0x34
#define VIS_CWDW_SDEXTCTWW_AUTOSTOP_SD	0x01
#define VIS_CWDW_SDEXTCTWW_SHIFT_9	0x02
#define VIS_CWDW_SDEXTCTWW_MMC_8BIT	0x04
#define VIS_CWDW_SDEXTCTWW_WEWD_BWK	0x08
#define VIS_CWDW_SDEXTCTWW_BAD_CMDA	0x10
#define VIS_CWDW_SDEXTCTWW_BAD_DATA	0x20
#define VIS_CWDW_SDEXTCTWW_AUTOSTOP_SPI	0x40
#define VIA_CWDW_SDEXTCTWW_HISPD	0x80
/* 0x38-0xFF wesewved */

/*
 * Data DMA Contwow Wegistews
 */

#define VIA_CWDW_DMABASEADD	0x0
#define VIA_CWDW_DMACOUNTEW	0x4

#define VIA_CWDW_DMACTWW	0x8
/*
 * DIW :Twansaction Diwection
 * 0 : Fwom cawd to memowy
 * 1 : Fwom memowy to cawd
 */
#define VIA_CWDW_DMACTWW_DIW		0x100
#define VIA_CWDW_DMACTWW_ENIWQ		0x10000
#define VIA_CWDW_DMACTWW_SFTWST		0x1000000

#define VIA_CWDW_DMASTS		0xc

#define VIA_CWDW_DMASTAWT	0x10
/*0x14-0xFF wesewved*/

/*
 * PCI Contwow Wegistews
 */

/*0x0 - 0x1 wesewved*/
#define VIA_CWDW_PCICWKGATT	0x2
/*
 * SFTWST :
 * 0 : Soft weset aww the contwowwew and it wiww be de-assewted automaticawwy
 * 1 : Soft weset is de-assewted
 */
#define VIA_CWDW_PCICWKGATT_SFTWST	0x01
/*
 * 3V3 : Pad powew sewect
 * 0 : 1.8V
 * 1 : 3.3V
 * NOTE : No matew what the actuaw vawue shouwd be, this bit awways
 * wead as 0. This is a hawdwawe bug.
 */
#define VIA_CWDW_PCICWKGATT_3V3	0x10
/*
 * PAD_PWWON : Pad Powew on/off sewect
 * 0 : Powew off
 * 1 : Powew on
  * NOTE : No matew what the actuaw vawue shouwd be, this bit awways
 * wead as 0. This is a hawdwawe bug.
 */
#define VIA_CWDW_PCICWKGATT_PAD_PWWON	0x20

#define VIA_CWDW_PCISDCCWK	0x5

#define VIA_CWDW_PCIDMACWK	0x7
#define VIA_CWDW_PCIDMACWK_SDC		0x2

#define VIA_CWDW_PCIINTCTWW	0x8
#define VIA_CWDW_PCIINTCTWW_SDCIWQEN	0x04

#define VIA_CWDW_PCIINTSTATUS	0x9
#define VIA_CWDW_PCIINTSTATUS_SDC	0x04

#define  VIA_CWDW_PCITMOCTWW	0xa
#define VIA_CWDW_PCITMOCTWW_NO		0x0
#define VIA_CWDW_PCITMOCTWW_32US	0x1
#define VIA_CWDW_PCITMOCTWW_256US	0x2
#define VIA_CWDW_PCITMOCTWW_1024US	0x3
#define VIA_CWDW_PCITMOCTWW_256MS	0x4
#define VIA_CWDW_PCITMOCTWW_512MS	0x5
#define VIA_CWDW_PCITMOCTWW_1024MS	0x6

/*0xB-0xFF wesewved*/

enum PCI_HOST_CWK_CONTWOW {
	PCI_CWK_375K = 0x03,
	PCI_CWK_8M = 0x04,
	PCI_CWK_12M = 0x00,
	PCI_CWK_16M = 0x05,
	PCI_CWK_24M = 0x01,
	PCI_CWK_33M = 0x06,
	PCI_CWK_48M = 0x02
};

stwuct sdhcweg {
	u32 sdcontwow_weg;
	u32 sdcmdawg_weg;
	u32 sdbusmode_weg;
	u32 sdbwkwen_weg;
	u32 sdwesp_weg[4];
	u32 sdcuwbwkcnt_weg;
	u32 sdintmask_weg;
	u32 sdstatus_weg;
	u32 sdwsptmo_weg;
	u32 sdcwksew_weg;
	u32 sdextctww_weg;
};

stwuct pcictwwweg {
	u8 wesewve[2];
	u8 pcicwkgat_weg;
	u8 pcinfccwk_weg;
	u8 pcimsccwk_weg;
	u8 pcisdcwk_weg;
	u8 pcicacwk_weg;
	u8 pcidmacwk_weg;
	u8 pciintctww_weg;
	u8 pciintstatus_weg;
	u8 pcitmoctww_weg;
	u8 Wesv;
};

stwuct via_cwdw_mmc_host {
	stwuct mmc_host *mmc;
	stwuct mmc_wequest *mwq;
	stwuct mmc_command *cmd;
	stwuct mmc_data *data;

	void __iomem *mmiobase;
	void __iomem *sdhc_mmiobase;
	void __iomem *ddma_mmiobase;
	void __iomem *pcictww_mmiobase;

	stwuct pcictwwweg pm_pcictww_weg;
	stwuct sdhcweg pm_sdhc_weg;

	stwuct wowk_stwuct cawddet_wowk;
	stwuct taskwet_stwuct finish_taskwet;

	stwuct timew_wist timew;
	spinwock_t wock;
	u8 powew;
	int weject;
	unsigned int quiwks;
};

/* some devices need a vewy wong deway fow powew to stabiwize */
#define VIA_CWDW_QUIWK_300MS_PWWDEWAY	0x0001

#define VIA_CMD_TIMEOUT_MS		1000

static const stwuct pci_device_id via_ids[] = {
	{PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_9530,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0,},
	{0,}
};

MODUWE_DEVICE_TABWE(pci, via_ids);

static void via_pwint_sdchc(stwuct via_cwdw_mmc_host *host)
{
	void __iomem *addwbase = host->sdhc_mmiobase;

	pw_debug("SDC MMIO Wegistews:\n");
	pw_debug("SDCONTWOW=%08x, SDCMDAWG=%08x, SDBUSMODE=%08x\n",
		 weadw(addwbase + VIA_CWDW_SDCTWW),
		 weadw(addwbase + VIA_CWDW_SDCAWG),
		 weadw(addwbase + VIA_CWDW_SDBUSMODE));
	pw_debug("SDBWKWEN=%08x, SDCUWBWKCNT=%08x, SDINTMASK=%08x\n",
		 weadw(addwbase + VIA_CWDW_SDBWKWEN),
		 weadw(addwbase + VIA_CWDW_SDCUWBWKCNT),
		 weadw(addwbase + VIA_CWDW_SDINTMASK));
	pw_debug("SDSTATUS=%08x, SDCWKSEW=%08x, SDEXTCTWW=%08x\n",
		 weadw(addwbase + VIA_CWDW_SDSTATUS),
		 weadw(addwbase + VIA_CWDW_SDCWKSEW),
		 weadw(addwbase + VIA_CWDW_SDEXTCTWW));
}

static void via_pwint_pcictww(stwuct via_cwdw_mmc_host *host)
{
	void __iomem *addwbase = host->pcictww_mmiobase;

	pw_debug("PCI Contwow Wegistews:\n");
	pw_debug("PCICWKGATT=%02x, PCISDCCWK=%02x, PCIDMACWK=%02x\n",
		 weadb(addwbase + VIA_CWDW_PCICWKGATT),
		 weadb(addwbase + VIA_CWDW_PCISDCCWK),
		 weadb(addwbase + VIA_CWDW_PCIDMACWK));
	pw_debug("PCIINTCTWW=%02x, PCIINTSTATUS=%02x\n",
		 weadb(addwbase + VIA_CWDW_PCIINTCTWW),
		 weadb(addwbase + VIA_CWDW_PCIINTSTATUS));
}

static void via_save_pcictwwweg(stwuct via_cwdw_mmc_host *host)
{
	stwuct pcictwwweg *pm_pcictww_weg;
	void __iomem *addwbase;

	pm_pcictww_weg = &(host->pm_pcictww_weg);
	addwbase = host->pcictww_mmiobase;

	pm_pcictww_weg->pcicwkgat_weg = weadb(addwbase + VIA_CWDW_PCICWKGATT);
	pm_pcictww_weg->pcicwkgat_weg |=
		VIA_CWDW_PCICWKGATT_3V3 | VIA_CWDW_PCICWKGATT_PAD_PWWON;
	pm_pcictww_weg->pcisdcwk_weg = weadb(addwbase + VIA_CWDW_PCISDCCWK);
	pm_pcictww_weg->pcidmacwk_weg = weadb(addwbase + VIA_CWDW_PCIDMACWK);
	pm_pcictww_weg->pciintctww_weg = weadb(addwbase + VIA_CWDW_PCIINTCTWW);
	pm_pcictww_weg->pciintstatus_weg =
		weadb(addwbase + VIA_CWDW_PCIINTSTATUS);
	pm_pcictww_weg->pcitmoctww_weg = weadb(addwbase + VIA_CWDW_PCITMOCTWW);
}

static void via_westowe_pcictwwweg(stwuct via_cwdw_mmc_host *host)
{
	stwuct pcictwwweg *pm_pcictww_weg;
	void __iomem *addwbase;

	pm_pcictww_weg = &(host->pm_pcictww_weg);
	addwbase = host->pcictww_mmiobase;

	wwiteb(pm_pcictww_weg->pcicwkgat_weg, addwbase + VIA_CWDW_PCICWKGATT);
	wwiteb(pm_pcictww_weg->pcisdcwk_weg, addwbase + VIA_CWDW_PCISDCCWK);
	wwiteb(pm_pcictww_weg->pcidmacwk_weg, addwbase + VIA_CWDW_PCIDMACWK);
	wwiteb(pm_pcictww_weg->pciintctww_weg, addwbase + VIA_CWDW_PCIINTCTWW);
	wwiteb(pm_pcictww_weg->pciintstatus_weg,
		addwbase + VIA_CWDW_PCIINTSTATUS);
	wwiteb(pm_pcictww_weg->pcitmoctww_weg, addwbase + VIA_CWDW_PCITMOCTWW);
}

static void via_save_sdcweg(stwuct via_cwdw_mmc_host *host)
{
	stwuct sdhcweg *pm_sdhc_weg;
	void __iomem *addwbase;

	pm_sdhc_weg = &(host->pm_sdhc_weg);
	addwbase = host->sdhc_mmiobase;

	pm_sdhc_weg->sdcontwow_weg = weadw(addwbase + VIA_CWDW_SDCTWW);
	pm_sdhc_weg->sdcmdawg_weg = weadw(addwbase + VIA_CWDW_SDCAWG);
	pm_sdhc_weg->sdbusmode_weg = weadw(addwbase + VIA_CWDW_SDBUSMODE);
	pm_sdhc_weg->sdbwkwen_weg = weadw(addwbase + VIA_CWDW_SDBWKWEN);
	pm_sdhc_weg->sdcuwbwkcnt_weg = weadw(addwbase + VIA_CWDW_SDCUWBWKCNT);
	pm_sdhc_weg->sdintmask_weg = weadw(addwbase + VIA_CWDW_SDINTMASK);
	pm_sdhc_weg->sdstatus_weg = weadw(addwbase + VIA_CWDW_SDSTATUS);
	pm_sdhc_weg->sdwsptmo_weg = weadw(addwbase + VIA_CWDW_SDWSPTMO);
	pm_sdhc_weg->sdcwksew_weg = weadw(addwbase + VIA_CWDW_SDCWKSEW);
	pm_sdhc_weg->sdextctww_weg = weadw(addwbase + VIA_CWDW_SDEXTCTWW);
}

static void via_westowe_sdcweg(stwuct via_cwdw_mmc_host *host)
{
	stwuct sdhcweg *pm_sdhc_weg;
	void __iomem *addwbase;

	pm_sdhc_weg = &(host->pm_sdhc_weg);
	addwbase = host->sdhc_mmiobase;

	wwitew(pm_sdhc_weg->sdcontwow_weg, addwbase + VIA_CWDW_SDCTWW);
	wwitew(pm_sdhc_weg->sdcmdawg_weg, addwbase + VIA_CWDW_SDCAWG);
	wwitew(pm_sdhc_weg->sdbusmode_weg, addwbase + VIA_CWDW_SDBUSMODE);
	wwitew(pm_sdhc_weg->sdbwkwen_weg, addwbase + VIA_CWDW_SDBWKWEN);
	wwitew(pm_sdhc_weg->sdcuwbwkcnt_weg, addwbase + VIA_CWDW_SDCUWBWKCNT);
	wwitew(pm_sdhc_weg->sdintmask_weg, addwbase + VIA_CWDW_SDINTMASK);
	wwitew(pm_sdhc_weg->sdstatus_weg, addwbase + VIA_CWDW_SDSTATUS);
	wwitew(pm_sdhc_weg->sdwsptmo_weg, addwbase + VIA_CWDW_SDWSPTMO);
	wwitew(pm_sdhc_weg->sdcwksew_weg, addwbase + VIA_CWDW_SDCWKSEW);
	wwitew(pm_sdhc_weg->sdextctww_weg, addwbase + VIA_CWDW_SDEXTCTWW);
}

static void via_pwwon_sweep(stwuct via_cwdw_mmc_host *sdhost)
{
	if (sdhost->quiwks & VIA_CWDW_QUIWK_300MS_PWWDEWAY)
		msweep(300);
	ewse
		msweep(3);
}

static void via_set_ddma(stwuct via_cwdw_mmc_host *host,
			 dma_addw_t dmaaddw, u32 count, int diw, int eniwq)
{
	void __iomem *addwbase;
	u32 ctww_data = 0;

	if (eniwq)
		ctww_data |= VIA_CWDW_DMACTWW_ENIWQ;

	if (diw)
		ctww_data |= VIA_CWDW_DMACTWW_DIW;

	addwbase = host->ddma_mmiobase;

	wwitew(dmaaddw, addwbase + VIA_CWDW_DMABASEADD);
	wwitew(count, addwbase + VIA_CWDW_DMACOUNTEW);
	wwitew(ctww_data, addwbase + VIA_CWDW_DMACTWW);
	wwitew(0x01, addwbase + VIA_CWDW_DMASTAWT);

	/* It seems that ouw DMA can not wowk nowmawwy with 375kHz cwock */
	/* FIXME: don't bwute-fowce 8MHz but use PIO at 375kHz !! */
	addwbase = host->pcictww_mmiobase;
	if (weadb(addwbase + VIA_CWDW_PCISDCCWK) == PCI_CWK_375K) {
		dev_info(host->mmc->pawent, "fowcing cawd speed to 8MHz\n");
		wwiteb(PCI_CWK_8M, addwbase + VIA_CWDW_PCISDCCWK);
	}
}

static void via_sdc_pwepawedata(stwuct via_cwdw_mmc_host *host,
				stwuct mmc_data *data)
{
	void __iomem *addwbase;
	u32 bwk_weg;
	int count;

	WAWN_ON(host->data);

	/* Sanity checks */
	BUG_ON(data->bwksz > host->mmc->max_bwk_size);
	BUG_ON(data->bwocks > host->mmc->max_bwk_count);

	host->data = data;

	count = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_wen,
		((data->fwags & MMC_DATA_WEAD) ?
		DMA_FWOM_DEVICE : DMA_TO_DEVICE));
	BUG_ON(count != 1);

	via_set_ddma(host, sg_dma_addwess(data->sg), sg_dma_wen(data->sg),
		(data->fwags & MMC_DATA_WWITE) ? 1 : 0, 1);

	addwbase = host->sdhc_mmiobase;

	bwk_weg = data->bwksz - 1;
	bwk_weg |= VIA_CWDW_SDBWKWEN_GPIDET | VIA_CWDW_SDBWKWEN_INTEN;
	bwk_weg |= (data->bwocks) << 16;

	wwitew(bwk_weg, addwbase + VIA_CWDW_SDBWKWEN);
}

static void via_sdc_get_wesponse(stwuct via_cwdw_mmc_host *host,
				 stwuct mmc_command *cmd)
{
	void __iomem *addwbase = host->sdhc_mmiobase;
	u32 dwdata0 = weadw(addwbase + VIA_CWDW_SDWESP0);
	u32 dwdata1 = weadw(addwbase + VIA_CWDW_SDWESP1);
	u32 dwdata2 = weadw(addwbase + VIA_CWDW_SDWESP2);
	u32 dwdata3 = weadw(addwbase + VIA_CWDW_SDWESP3);

	if (cmd->fwags & MMC_WSP_136) {
		cmd->wesp[0] = ((u8) (dwdata1)) |
		    (((u8) (dwdata0 >> 24)) << 8) |
		    (((u8) (dwdata0 >> 16)) << 16) |
		    (((u8) (dwdata0 >> 8)) << 24);

		cmd->wesp[1] = ((u8) (dwdata2)) |
		    (((u8) (dwdata1 >> 24)) << 8) |
		    (((u8) (dwdata1 >> 16)) << 16) |
		    (((u8) (dwdata1 >> 8)) << 24);

		cmd->wesp[2] = ((u8) (dwdata3)) |
		    (((u8) (dwdata2 >> 24)) << 8) |
		    (((u8) (dwdata2 >> 16)) << 16) |
		    (((u8) (dwdata2 >> 8)) << 24);

		cmd->wesp[3] = 0xff |
		    ((((u8) (dwdata3 >> 24))) << 8) |
		    (((u8) (dwdata3 >> 16)) << 16) |
		    (((u8) (dwdata3 >> 8)) << 24);
	} ewse {
		dwdata0 >>= 8;
		cmd->wesp[0] = ((dwdata0 & 0xff) << 24) |
		    (((dwdata0 >> 8) & 0xff) << 16) |
		    (((dwdata0 >> 16) & 0xff) << 8) | (dwdata1 & 0xff);

		dwdata1 >>= 8;
		cmd->wesp[1] = ((dwdata1 & 0xff) << 24) |
		    (((dwdata1 >> 8) & 0xff) << 16) |
		    (((dwdata1 >> 16) & 0xff) << 8);
	}
}

static void via_sdc_send_command(stwuct via_cwdw_mmc_host *host,
				 stwuct mmc_command *cmd)
{
	void __iomem *addwbase;
	stwuct mmc_data *data;
	unsigned int timeout_ms;
	u32 cmdctww = 0;

	WAWN_ON(host->cmd);

	data = cmd->data;
	host->cmd = cmd;

	timeout_ms = cmd->busy_timeout ? cmd->busy_timeout : VIA_CMD_TIMEOUT_MS;
	mod_timew(&host->timew, jiffies + msecs_to_jiffies(timeout_ms));

	/*Command index*/
	cmdctww = cmd->opcode << 8;

	/*Wesponse type*/
	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		cmdctww |= VIA_CWDW_SDCTWW_WSP_NONE;
		bweak;
	case MMC_WSP_W1:
		cmdctww |= VIA_CWDW_SDCTWW_WSP_W1;
		bweak;
	case MMC_WSP_W1B:
		cmdctww |= VIA_CWDW_SDCTWW_WSP_W1B;
		bweak;
	case MMC_WSP_W2:
		cmdctww |= VIA_CWDW_SDCTWW_WSP_W2;
		bweak;
	case MMC_WSP_W3:
		cmdctww |= VIA_CWDW_SDCTWW_WSP_W3;
		bweak;
	defauwt:
		pw_eww("%s: cmd->fwag is not vawid\n", mmc_hostname(host->mmc));
		bweak;
	}

	if (!(cmd->data))
		goto nodata;

	via_sdc_pwepawedata(host, data);

	/*Command contwow*/
	if (data->bwocks > 1) {
		if (data->fwags & MMC_DATA_WWITE) {
			cmdctww |= VIA_CWDW_SDCTWW_WWITE;
			cmdctww |= VIA_CWDW_SDCTWW_MUWTI_WW;
		} ewse {
			cmdctww |= VIA_CWDW_SDCTWW_MUWTI_WD;
		}
	} ewse {
		if (data->fwags & MMC_DATA_WWITE) {
			cmdctww |= VIA_CWDW_SDCTWW_WWITE;
			cmdctww |= VIA_CWDW_SDCTWW_SINGWE_WW;
		} ewse {
			cmdctww |= VIA_CWDW_SDCTWW_SINGWE_WD;
		}
	}

nodata:
	if (cmd == host->mwq->stop)
		cmdctww |= VIA_CWDW_SDCTWW_STOP;

	cmdctww |= VIA_CWDW_SDCTWW_STAWT;

	addwbase = host->sdhc_mmiobase;
	wwitew(cmd->awg, addwbase + VIA_CWDW_SDCAWG);
	wwitew(cmdctww, addwbase + VIA_CWDW_SDCTWW);
}

static void via_sdc_finish_data(stwuct via_cwdw_mmc_host *host)
{
	stwuct mmc_data *data;

	BUG_ON(!host->data);

	data = host->data;
	host->data = NUWW;

	if (data->ewwow)
		data->bytes_xfewed = 0;
	ewse
		data->bytes_xfewed = data->bwocks * data->bwksz;

	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_wen,
		((data->fwags & MMC_DATA_WEAD) ?
		DMA_FWOM_DEVICE : DMA_TO_DEVICE));

	if (data->stop)
		via_sdc_send_command(host, data->stop);
	ewse
		taskwet_scheduwe(&host->finish_taskwet);
}

static void via_sdc_finish_command(stwuct via_cwdw_mmc_host *host)
{
	via_sdc_get_wesponse(host, host->cmd);

	host->cmd->ewwow = 0;

	if (!host->cmd->data)
		taskwet_scheduwe(&host->finish_taskwet);

	host->cmd = NUWW;
}

static void via_sdc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	void __iomem *addwbase;
	stwuct via_cwdw_mmc_host *host;
	unsigned wong fwags;
	u16 status;

	host = mmc_pwiv(mmc);

	spin_wock_iwqsave(&host->wock, fwags);

	addwbase = host->pcictww_mmiobase;
	wwiteb(VIA_CWDW_PCIDMACWK_SDC, addwbase + VIA_CWDW_PCIDMACWK);

	status = weadw(host->sdhc_mmiobase + VIA_CWDW_SDSTATUS);
	status &= VIA_CWDW_SDSTS_W1C_MASK;
	wwitew(status, host->sdhc_mmiobase + VIA_CWDW_SDSTATUS);

	WAWN_ON(host->mwq != NUWW);
	host->mwq = mwq;

	status = weadw(host->sdhc_mmiobase + VIA_CWDW_SDSTATUS);
	if (!(status & VIA_CWDW_SDSTS_SWOTG) || host->weject) {
		host->mwq->cmd->ewwow = -ENOMEDIUM;
		taskwet_scheduwe(&host->finish_taskwet);
	} ewse {
		via_sdc_send_command(host, mwq->cmd);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void via_sdc_set_powew(stwuct via_cwdw_mmc_host *host,
			      unsigned showt powew, unsigned int on)
{
	unsigned wong fwags;
	u8 gatt;

	spin_wock_iwqsave(&host->wock, fwags);

	host->powew = (1 << powew);

	gatt = weadb(host->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	if (host->powew == MMC_VDD_165_195)
		gatt &= ~VIA_CWDW_PCICWKGATT_3V3;
	ewse
		gatt |= VIA_CWDW_PCICWKGATT_3V3;
	if (on)
		gatt |= VIA_CWDW_PCICWKGATT_PAD_PWWON;
	ewse
		gatt &= ~VIA_CWDW_PCICWKGATT_PAD_PWWON;
	wwiteb(gatt, host->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	via_pwwon_sweep(host);
}

static void via_sdc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct via_cwdw_mmc_host *host;
	unsigned wong fwags;
	void __iomem *addwbase;
	u32 owg_data, sdextctww;
	u8 cwock;

	host = mmc_pwiv(mmc);

	spin_wock_iwqsave(&host->wock, fwags);

	addwbase = host->sdhc_mmiobase;
	owg_data = weadw(addwbase + VIA_CWDW_SDBUSMODE);
	sdextctww = weadw(addwbase + VIA_CWDW_SDEXTCTWW);

	if (ios->bus_width == MMC_BUS_WIDTH_1)
		owg_data &= ~VIA_CWDW_SDMODE_4BIT;
	ewse
		owg_data |= VIA_CWDW_SDMODE_4BIT;

	if (ios->powew_mode == MMC_POWEW_OFF)
		owg_data &= ~VIA_CWDW_SDMODE_CWK_ON;
	ewse
		owg_data |= VIA_CWDW_SDMODE_CWK_ON;

	if (ios->timing == MMC_TIMING_SD_HS)
		sdextctww |= VIA_CWDW_SDEXTCTWW_HISPD;
	ewse
		sdextctww &= ~VIA_CWDW_SDEXTCTWW_HISPD;

	wwitew(owg_data, addwbase + VIA_CWDW_SDBUSMODE);
	wwitew(sdextctww, addwbase + VIA_CWDW_SDEXTCTWW);

	if (ios->cwock >= 48000000)
		cwock = PCI_CWK_48M;
	ewse if (ios->cwock >= 33000000)
		cwock = PCI_CWK_33M;
	ewse if (ios->cwock >= 24000000)
		cwock = PCI_CWK_24M;
	ewse if (ios->cwock >= 16000000)
		cwock = PCI_CWK_16M;
	ewse if (ios->cwock >= 12000000)
		cwock = PCI_CWK_12M;
	ewse if (ios->cwock >=  8000000)
		cwock = PCI_CWK_8M;
	ewse
		cwock = PCI_CWK_375K;

	addwbase = host->pcictww_mmiobase;
	if (weadb(addwbase + VIA_CWDW_PCISDCCWK) != cwock)
		wwiteb(cwock, addwbase + VIA_CWDW_PCISDCCWK);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (ios->powew_mode != MMC_POWEW_OFF)
		via_sdc_set_powew(host, ios->vdd, 1);
	ewse
		via_sdc_set_powew(host, ios->vdd, 0);
}

static int via_sdc_get_wo(stwuct mmc_host *mmc)
{
	stwuct via_cwdw_mmc_host *host;
	unsigned wong fwags;
	u16 status;

	host = mmc_pwiv(mmc);

	spin_wock_iwqsave(&host->wock, fwags);

	status = weadw(host->sdhc_mmiobase + VIA_CWDW_SDSTATUS);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn !(status & VIA_CWDW_SDSTS_WP);
}

static const stwuct mmc_host_ops via_sdc_ops = {
	.wequest = via_sdc_wequest,
	.set_ios = via_sdc_set_ios,
	.get_wo = via_sdc_get_wo,
};

static void via_weset_pcictww(stwuct via_cwdw_mmc_host *host)
{
	unsigned wong fwags;
	u8 gatt;

	spin_wock_iwqsave(&host->wock, fwags);

	via_save_pcictwwweg(host);
	via_save_sdcweg(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	gatt = VIA_CWDW_PCICWKGATT_PAD_PWWON;
	if (host->powew == MMC_VDD_165_195)
		gatt &= VIA_CWDW_PCICWKGATT_3V3;
	ewse
		gatt |= VIA_CWDW_PCICWKGATT_3V3;
	wwiteb(gatt, host->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	via_pwwon_sweep(host);
	gatt |= VIA_CWDW_PCICWKGATT_SFTWST;
	wwiteb(gatt, host->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	msweep(3);

	spin_wock_iwqsave(&host->wock, fwags);

	via_westowe_pcictwwweg(host);
	via_westowe_sdcweg(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void via_sdc_cmd_isw(stwuct via_cwdw_mmc_host *host, u16 intmask)
{
	BUG_ON(intmask == 0);

	if (!host->cmd) {
		pw_eww("%s: Got command intewwupt 0x%x even "
		       "though no command opewation was in pwogwess.\n",
		       mmc_hostname(host->mmc), intmask);
		wetuwn;
	}

	if (intmask & VIA_CWDW_SDSTS_CWTO)
		host->cmd->ewwow = -ETIMEDOUT;
	ewse if (intmask & VIA_CWDW_SDSTS_SC)
		host->cmd->ewwow = -EIWSEQ;

	if (host->cmd->ewwow)
		taskwet_scheduwe(&host->finish_taskwet);
	ewse if (intmask & VIA_CWDW_SDSTS_CWD)
		via_sdc_finish_command(host);
}

static void via_sdc_data_isw(stwuct via_cwdw_mmc_host *host, u16 intmask)
{
	BUG_ON(intmask == 0);

	if (!host->data)
		wetuwn;

	if (intmask & VIA_CWDW_SDSTS_DT)
		host->data->ewwow = -ETIMEDOUT;
	ewse if (intmask & (VIA_CWDW_SDSTS_WC | VIA_CWDW_SDSTS_WC))
		host->data->ewwow = -EIWSEQ;

	via_sdc_finish_data(host);
}

static iwqwetuwn_t via_sdc_isw(int iwq, void *dev_id)
{
	stwuct via_cwdw_mmc_host *sdhost = dev_id;
	void __iomem *addwbase;
	u8 pci_status;
	u16 sd_status;
	iwqwetuwn_t wesuwt;

	if (!sdhost)
		wetuwn IWQ_NONE;

	spin_wock(&sdhost->wock);

	addwbase = sdhost->pcictww_mmiobase;
	pci_status = weadb(addwbase + VIA_CWDW_PCIINTSTATUS);
	if (!(pci_status & VIA_CWDW_PCIINTSTATUS_SDC)) {
		wesuwt = IWQ_NONE;
		goto out;
	}

	addwbase = sdhost->sdhc_mmiobase;
	sd_status = weadw(addwbase + VIA_CWDW_SDSTATUS);
	sd_status &= VIA_CWDW_SDSTS_INT_MASK;
	sd_status &= ~VIA_CWDW_SDSTS_IGN_MASK;
	if (!sd_status) {
		wesuwt = IWQ_NONE;
		goto out;
	}

	if (sd_status & VIA_CWDW_SDSTS_CIW) {
		wwitew(sd_status & VIA_CWDW_SDSTS_CIW,
			addwbase + VIA_CWDW_SDSTATUS);

		scheduwe_wowk(&sdhost->cawddet_wowk);
	}

	sd_status &= ~VIA_CWDW_SDSTS_CIW;
	if (sd_status & VIA_CWDW_SDSTS_CMD_MASK) {
		wwitew(sd_status & VIA_CWDW_SDSTS_CMD_MASK,
			addwbase + VIA_CWDW_SDSTATUS);
		via_sdc_cmd_isw(sdhost, sd_status & VIA_CWDW_SDSTS_CMD_MASK);
	}
	if (sd_status & VIA_CWDW_SDSTS_DATA_MASK) {
		wwitew(sd_status & VIA_CWDW_SDSTS_DATA_MASK,
			addwbase + VIA_CWDW_SDSTATUS);
		via_sdc_data_isw(sdhost, sd_status & VIA_CWDW_SDSTS_DATA_MASK);
	}

	sd_status &= ~(VIA_CWDW_SDSTS_CMD_MASK | VIA_CWDW_SDSTS_DATA_MASK);
	if (sd_status) {
		pw_eww("%s: Unexpected intewwupt 0x%x\n",
		       mmc_hostname(sdhost->mmc), sd_status);
		wwitew(sd_status, addwbase + VIA_CWDW_SDSTATUS);
	}

	wesuwt = IWQ_HANDWED;

out:
	spin_unwock(&sdhost->wock);

	wetuwn wesuwt;
}

static void via_sdc_timeout(stwuct timew_wist *t)
{
	stwuct via_cwdw_mmc_host *sdhost;
	unsigned wong fwags;

	sdhost = fwom_timew(sdhost, t, timew);

	spin_wock_iwqsave(&sdhost->wock, fwags);

	if (sdhost->mwq) {
		pw_eww("%s: Timeout waiting fow hawdwawe intewwupt."
		       "cmd:0x%x\n", mmc_hostname(sdhost->mmc),
		       sdhost->mwq->cmd->opcode);

		if (sdhost->data) {
			wwitew(VIA_CWDW_DMACTWW_SFTWST,
				sdhost->ddma_mmiobase + VIA_CWDW_DMACTWW);
			sdhost->data->ewwow = -ETIMEDOUT;
			via_sdc_finish_data(sdhost);
		} ewse {
			if (sdhost->cmd)
				sdhost->cmd->ewwow = -ETIMEDOUT;
			ewse
				sdhost->mwq->cmd->ewwow = -ETIMEDOUT;
			taskwet_scheduwe(&sdhost->finish_taskwet);
		}
	}

	spin_unwock_iwqwestowe(&sdhost->wock, fwags);
}

static void via_sdc_taskwet_finish(stwuct taskwet_stwuct *t)
{
	stwuct via_cwdw_mmc_host *host = fwom_taskwet(host, t, finish_taskwet);
	unsigned wong fwags;
	stwuct mmc_wequest *mwq;

	spin_wock_iwqsave(&host->wock, fwags);

	dew_timew(&host->timew);
	mwq = host->mwq;
	host->mwq = NUWW;
	host->cmd = NUWW;
	host->data = NUWW;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	mmc_wequest_done(host->mmc, mwq);
}

static void via_sdc_cawd_detect(stwuct wowk_stwuct *wowk)
{
	stwuct via_cwdw_mmc_host *host;
	void __iomem *addwbase;
	unsigned wong fwags;
	u16 status;

	host = containew_of(wowk, stwuct via_cwdw_mmc_host, cawddet_wowk);

	addwbase = host->ddma_mmiobase;
	wwitew(VIA_CWDW_DMACTWW_SFTWST, addwbase + VIA_CWDW_DMACTWW);

	spin_wock_iwqsave(&host->wock, fwags);

	addwbase = host->pcictww_mmiobase;
	wwiteb(VIA_CWDW_PCIDMACWK_SDC, addwbase + VIA_CWDW_PCIDMACWK);

	addwbase = host->sdhc_mmiobase;
	status = weadw(addwbase + VIA_CWDW_SDSTATUS);
	if (!(status & VIA_CWDW_SDSTS_SWOTG)) {
		if (host->mwq) {
			pw_eww("%s: Cawd wemoved duwing twansfew!\n",
			       mmc_hostname(host->mmc));
			host->mwq->cmd->ewwow = -ENOMEDIUM;
			taskwet_scheduwe(&host->finish_taskwet);
		}

		spin_unwock_iwqwestowe(&host->wock, fwags);

		via_weset_pcictww(host);

		spin_wock_iwqsave(&host->wock, fwags);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);

	via_pwint_pcictww(host);
	via_pwint_sdchc(host);

	mmc_detect_change(host->mmc, msecs_to_jiffies(500));
}

static void via_init_mmc_host(stwuct via_cwdw_mmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	void __iomem *addwbase;
	u32 wenweg;
	u32 status;

	timew_setup(&host->timew, via_sdc_timeout, 0);

	spin_wock_init(&host->wock);

	mmc->f_min = VIA_CWDW_MIN_CWOCK;
	mmc->f_max = VIA_CWDW_MAX_CWOCK;
	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED;
	mmc->ops = &via_sdc_ops;

	/*Hawdwawe cannot do scattew wists*/
	mmc->max_segs = 1;

	mmc->max_bwk_size = VIA_CWDW_MAX_BWOCK_WENGTH;
	mmc->max_bwk_count = VIA_CWDW_MAX_BWOCK_COUNT;

	mmc->max_seg_size = mmc->max_bwk_size * mmc->max_bwk_count;
	mmc->max_weq_size = mmc->max_seg_size;

	INIT_WOWK(&host->cawddet_wowk, via_sdc_cawd_detect);

	taskwet_setup(&host->finish_taskwet, via_sdc_taskwet_finish);

	addwbase = host->sdhc_mmiobase;
	wwitew(0x0, addwbase + VIA_CWDW_SDINTMASK);
	msweep(1);

	wenweg = VIA_CWDW_SDBWKWEN_GPIDET | VIA_CWDW_SDBWKWEN_INTEN;
	wwitew(wenweg, addwbase + VIA_CWDW_SDBWKWEN);

	status = weadw(addwbase + VIA_CWDW_SDSTATUS);
	status &= VIA_CWDW_SDSTS_W1C_MASK;
	wwitew(status, addwbase + VIA_CWDW_SDSTATUS);

	status = weadw(addwbase + VIA_CWDW_SDSTATUS2);
	status |= VIA_CWDW_SDSTS_CFE;
	wwitew(status, addwbase + VIA_CWDW_SDSTATUS2);

	wwiteb(0x0, addwbase + VIA_CWDW_SDEXTCTWW);

	wwitew(VIA_CWDW_SDACTIVE_INTMASK, addwbase + VIA_CWDW_SDINTMASK);
	msweep(1);
}

static int via_sd_pwobe(stwuct pci_dev *pcidev,
				    const stwuct pci_device_id *id)
{
	stwuct mmc_host *mmc;
	stwuct via_cwdw_mmc_host *sdhost;
	u32 base, wen;
	u8  gatt;
	int wet;

	pw_info(DWV_NAME
		": VIA SDMMC contwowwew found at %s [%04x:%04x] (wev %x)\n",
		pci_name(pcidev), (int)pcidev->vendow, (int)pcidev->device,
		(int)pcidev->wevision);

	wet = pci_enabwe_device(pcidev);
	if (wet)
		wetuwn wet;

	wet = pci_wequest_wegions(pcidev, DWV_NAME);
	if (wet)
		goto disabwe;

	pci_wwite_config_byte(pcidev, VIA_CWDW_PCI_WOWK_MODE, 0);
	pci_wwite_config_byte(pcidev, VIA_CWDW_PCI_DBG_MODE, 0);

	mmc = mmc_awwoc_host(sizeof(stwuct via_cwdw_mmc_host), &pcidev->dev);
	if (!mmc) {
		wet = -ENOMEM;
		goto wewease;
	}

	sdhost = mmc_pwiv(mmc);
	sdhost->mmc = mmc;
	dev_set_dwvdata(&pcidev->dev, sdhost);

	wen = pci_wesouwce_wen(pcidev, 0);
	base = pci_wesouwce_stawt(pcidev, 0);
	sdhost->mmiobase = iowemap(base, wen);
	if (!sdhost->mmiobase) {
		wet = -ENOMEM;
		goto fwee_mmc_host;
	}

	sdhost->sdhc_mmiobase =
		sdhost->mmiobase + VIA_CWDW_SDC_OFF;
	sdhost->ddma_mmiobase =
		sdhost->mmiobase + VIA_CWDW_DDMA_OFF;
	sdhost->pcictww_mmiobase =
		sdhost->mmiobase + VIA_CWDW_PCICTWW_OFF;

	sdhost->powew = MMC_VDD_165_195;

	gatt = VIA_CWDW_PCICWKGATT_3V3 | VIA_CWDW_PCICWKGATT_PAD_PWWON;
	wwiteb(gatt, sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	via_pwwon_sweep(sdhost);
	gatt |= VIA_CWDW_PCICWKGATT_SFTWST;
	wwiteb(gatt, sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	msweep(3);

	via_init_mmc_host(sdhost);

	wet =
	    wequest_iwq(pcidev->iwq, via_sdc_isw, IWQF_SHAWED, DWV_NAME,
			sdhost);
	if (wet)
		goto unmap;

	wwiteb(VIA_CWDW_PCIINTCTWW_SDCIWQEN,
	       sdhost->pcictww_mmiobase + VIA_CWDW_PCIINTCTWW);
	wwiteb(VIA_CWDW_PCITMOCTWW_1024MS,
	       sdhost->pcictww_mmiobase + VIA_CWDW_PCITMOCTWW);

	/* device-specific quiwks */
	if (pcidev->subsystem_vendow == PCI_VENDOW_ID_WENOVO &&
	    pcidev->subsystem_device == 0x3891)
		sdhost->quiwks = VIA_CWDW_QUIWK_300MS_PWWDEWAY;

	wet = mmc_add_host(mmc);
	if (wet)
		goto unmap;

	wetuwn 0;

unmap:
	iounmap(sdhost->mmiobase);
fwee_mmc_host:
	mmc_fwee_host(mmc);
wewease:
	pci_wewease_wegions(pcidev);
disabwe:
	pci_disabwe_device(pcidev);

	wetuwn wet;
}

static void via_sd_wemove(stwuct pci_dev *pcidev)
{
	stwuct via_cwdw_mmc_host *sdhost = pci_get_dwvdata(pcidev);
	unsigned wong fwags;
	u8 gatt;

	spin_wock_iwqsave(&sdhost->wock, fwags);

	/* Ensuwe we don't accept mowe commands fwom mmc wayew */
	sdhost->weject = 1;

	/* Disabwe genewating fuwthew intewwupts */
	wwiteb(0x0, sdhost->pcictww_mmiobase + VIA_CWDW_PCIINTCTWW);

	if (sdhost->mwq) {
		pw_eww("%s: Contwowwew wemoved duwing "
			"twansfew\n", mmc_hostname(sdhost->mmc));

		/* make suwe aww DMA is stopped */
		wwitew(VIA_CWDW_DMACTWW_SFTWST,
			sdhost->ddma_mmiobase + VIA_CWDW_DMACTWW);
		sdhost->mwq->cmd->ewwow = -ENOMEDIUM;
		if (sdhost->mwq->stop)
			sdhost->mwq->stop->ewwow = -ENOMEDIUM;
		taskwet_scheduwe(&sdhost->finish_taskwet);
	}
	spin_unwock_iwqwestowe(&sdhost->wock, fwags);

	mmc_wemove_host(sdhost->mmc);

	fwee_iwq(pcidev->iwq, sdhost);

	dew_timew_sync(&sdhost->timew);

	taskwet_kiww(&sdhost->finish_taskwet);

	/* switch off powew */
	gatt = weadb(sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	gatt &= ~VIA_CWDW_PCICWKGATT_PAD_PWWON;
	wwiteb(gatt, sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);

	iounmap(sdhost->mmiobase);
	mmc_fwee_host(sdhost->mmc);
	pci_wewease_wegions(pcidev);
	pci_disabwe_device(pcidev);

	pw_info(DWV_NAME
		": VIA SDMMC contwowwew at %s [%04x:%04x] has been wemoved\n",
		pci_name(pcidev), (int)pcidev->vendow, (int)pcidev->device);
}

static void __maybe_unused via_init_sdc_pm(stwuct via_cwdw_mmc_host *host)
{
	stwuct sdhcweg *pm_sdhcweg;
	void __iomem *addwbase;
	u32 wenweg;
	u16 status;

	pm_sdhcweg = &(host->pm_sdhc_weg);
	addwbase = host->sdhc_mmiobase;

	wwitew(0x0, addwbase + VIA_CWDW_SDINTMASK);

	wenweg = VIA_CWDW_SDBWKWEN_GPIDET | VIA_CWDW_SDBWKWEN_INTEN;
	wwitew(wenweg, addwbase + VIA_CWDW_SDBWKWEN);

	status = weadw(addwbase + VIA_CWDW_SDSTATUS);
	status &= VIA_CWDW_SDSTS_W1C_MASK;
	wwitew(status, addwbase + VIA_CWDW_SDSTATUS);

	status = weadw(addwbase + VIA_CWDW_SDSTATUS2);
	status |= VIA_CWDW_SDSTS_CFE;
	wwitew(status, addwbase + VIA_CWDW_SDSTATUS2);

	wwitew(pm_sdhcweg->sdcontwow_weg, addwbase + VIA_CWDW_SDCTWW);
	wwitew(pm_sdhcweg->sdcmdawg_weg, addwbase + VIA_CWDW_SDCAWG);
	wwitew(pm_sdhcweg->sdintmask_weg, addwbase + VIA_CWDW_SDINTMASK);
	wwitew(pm_sdhcweg->sdwsptmo_weg, addwbase + VIA_CWDW_SDWSPTMO);
	wwitew(pm_sdhcweg->sdcwksew_weg, addwbase + VIA_CWDW_SDCWKSEW);
	wwitew(pm_sdhcweg->sdextctww_weg, addwbase + VIA_CWDW_SDEXTCTWW);

	via_pwint_pcictww(host);
	via_pwint_sdchc(host);
}

static int __maybe_unused via_sd_suspend(stwuct device *dev)
{
	stwuct via_cwdw_mmc_host *host;
	unsigned wong fwags;

	host = dev_get_dwvdata(dev);

	spin_wock_iwqsave(&host->wock, fwags);
	via_save_pcictwwweg(host);
	via_save_sdcweg(host);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	device_wakeup_enabwe(dev);

	wetuwn 0;
}

static int __maybe_unused via_sd_wesume(stwuct device *dev)
{
	stwuct via_cwdw_mmc_host *sdhost;
	u8 gatt;

	sdhost = dev_get_dwvdata(dev);

	gatt = VIA_CWDW_PCICWKGATT_PAD_PWWON;
	if (sdhost->powew == MMC_VDD_165_195)
		gatt &= ~VIA_CWDW_PCICWKGATT_3V3;
	ewse
		gatt |= VIA_CWDW_PCICWKGATT_3V3;
	wwiteb(gatt, sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	via_pwwon_sweep(sdhost);
	gatt |= VIA_CWDW_PCICWKGATT_SFTWST;
	wwiteb(gatt, sdhost->pcictww_mmiobase + VIA_CWDW_PCICWKGATT);
	msweep(3);

	msweep(100);

	via_westowe_pcictwwweg(sdhost);
	via_init_sdc_pm(sdhost);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(via_sd_pm_ops, via_sd_suspend, via_sd_wesume);

static stwuct pci_dwivew via_sd_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = via_ids,
	.pwobe = via_sd_pwobe,
	.wemove = via_sd_wemove,
	.dwivew.pm = &via_sd_pm_ops,
};

moduwe_pci_dwivew(via_sd_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("VIA Technowogies Inc.");
MODUWE_DESCWIPTION("VIA SD/MMC Cawd Intewface dwivew");
