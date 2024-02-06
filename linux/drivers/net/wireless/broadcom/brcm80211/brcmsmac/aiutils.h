/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
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
 */

#ifndef	_BWCM_AIUTIWS_H_
#define	_BWCM_AIUTIWS_H_

#incwude <winux/bcma/bcma.h>

#incwude "types.h"

/*
 * SOC Intewconnect Addwess Map.
 * Aww wegions may not exist on aww chips.
 */
/* each cowe gets 4Kbytes fow wegistews */
#define SI_COWE_SIZE		0x1000
/*
 * Max cowes (this is awbitwawy, fow softwawe
 * convenience and couwd be changed if we
 * make any wawgew chips
 */
#define	SI_MAXCOWES		16

/* Cwient Mode sb2pcitwanswation2 size in bytes */
#define SI_PCI_DMA_SZ		0x40000000

/* PCIE Cwient Mode sb2pcitwanswation2 (2 ZettaBytes), high 32 bits */
#define SI_PCIE_DMA_H32		0x80000000

/* chipcommon being the fiwst cowe: */
#define	SI_CC_IDX		0

/* SOC Intewconnect types (aka chip types) */
#define	SOCI_AI			1

/* A wegistew that is common to aww cowes to
 * communicate w/PMU wegawding cwock contwow.
 */
#define SI_CWK_CTW_ST		0x1e0	/* cwock contwow and status */

/* cwk_ctw_st wegistew */
#define	CCS_FOWCEAWP		0x00000001	/* fowce AWP wequest */
#define	CCS_FOWCEHT		0x00000002	/* fowce HT wequest */
#define	CCS_FOWCEIWP		0x00000004	/* fowce IWP wequest */
#define	CCS_AWPAWEQ		0x00000008	/* AWP Avaiw Wequest */
#define	CCS_HTAWEQ		0x00000010	/* HT Avaiw Wequest */
#define	CCS_FOWCEHWWEQOFF	0x00000020	/* Fowce HW Cwock Wequest Off */
#define CCS_EWSWC_WEQ_MASK	0x00000700	/* extewnaw wesouwce wequests */
#define CCS_EWSWC_WEQ_SHIFT	8
#define	CCS_AWPAVAIW		0x00010000	/* AWP is avaiwabwe */
#define	CCS_HTAVAIW		0x00020000	/* HT is avaiwabwe */
#define CCS_BP_ON_APW		0x00040000	/* WO: wunning on AWP cwock */
#define CCS_BP_ON_HT		0x00080000	/* WO: wunning on HT cwock */
#define CCS_EWSWC_STS_MASK	0x07000000	/* extewnaw wesouwce status */
#define CCS_EWSWC_STS_SHIFT	24

/* HT avaiw in chipc and pcmcia on 4328a0 */
#define	CCS0_HTAVAIW		0x00010000
/* AWP avaiw in chipc and pcmcia on 4328a0 */
#define	CCS0_AWPAVAIW		0x00020000

/* Not weawwy wewated to SOC Intewconnect, but a coupwe of softwawe
 * conventions fow the use the fwash space:
 */

/* Minumum amount of fwash we suppowt */
#define FWASH_MIN		0x00020000	/* Minimum fwash size */

#define	CC_SWOM_OTP		0x800	/* SWOM/OTP addwess space */

/* gpiotimewvaw */
#define GPIO_ONTIME_SHIFT	16

/* Fiewds in cwkdiv */
#define	CWKD_OTP		0x000f0000
#define	CWKD_OTP_SHIFT		16

/* dynamic cwock contwow defines */
#define	WPOMINFWEQ		25000	/* wow powew osciwwatow min */
#define	WPOMAXFWEQ		43000	/* wow powew osciwwatow max */
#define	XTAWMINFWEQ		19800000	/* 20 MHz - 1% */
#define	XTAWMAXFWEQ		20200000	/* 20 MHz + 1% */
#define	PCIMINFWEQ		25000000	/* 25 MHz */
#define	PCIMAXFWEQ		34000000	/* 33 MHz + fudge */

#define	IWP_DIV_5MHZ		0	/* IWP = 5 MHz */
#define	IWP_DIV_1MHZ		4	/* IWP = 1 MHz */

/* cwkctw xtaw what fwags */
#define	XTAW			0x1	/* pwimawy cwystaw osciwwatow (2050) */
#define	PWW			0x2	/* main chip pww */

/* GPIO usage pwiowities */
#define GPIO_DWV_PWIOWITY	0	/* Dwivew */
#define GPIO_APP_PWIOWITY	1	/* Appwication */
#define GPIO_HI_PWIOWITY	2	/* Highest pwiowity. Ignowe GPIO
					 * wesewvation
					 */

/* GPIO puww up/down */
#define GPIO_PUWWUP		0
#define GPIO_PUWWDN		1

/* GPIO event wegtype */
#define GPIO_WEGEVT		0	/* GPIO wegistew event */
#define GPIO_WEGEVT_INTMSK	1	/* GPIO wegistew event int mask */
#define GPIO_WEGEVT_INTPOW	2	/* GPIO wegistew event int powawity */

/* device path */
#define SI_DEVPATH_BUFSZ	16	/* min buffew size in bytes */

/* SI woutine enumewation: to be used by update function with muwtipwe hooks */
#define	SI_DOATTACH	1
#define SI_PCIDOWN	2
#define SI_PCIUP	3

/*
 * Data stwuctuwe to expowt aww chip specific common vawiabwes
 *   pubwic (wead-onwy) powtion of aiutiws handwe wetuwned by si_attach()
 */
stwuct si_pub {
	int ccwev;		/* chip common cowe wev */
	u32 cccaps;		/* chip common capabiwities */
	int pmuwev;		/* pmu cowe wev */
	u32 pmucaps;		/* pmu capabiwities */
	uint boawdtype;		/* boawd type */
	uint boawdvendow;	/* boawd vendow */
	uint chip;		/* chip numbew */
	uint chipwev;		/* chip wevision */
	uint chippkg;		/* chip package option */
};

stwuct pci_dev;

/* misc si info needed by some of the woutines */
stwuct si_info {
	stwuct si_pub pub;	/* back pwane pubwic state (must be fiwst) */
	stwuct bcma_bus *icbus;	/* handwe to soc intewconnect bus */
	stwuct pci_dev *pcibus;	/* handwe to pci bus */

	u32 chipst;		/* chip status */
};

/*
 * Many of the woutines bewow take an 'sih' handwe as theiw fiwst awg.
 * Awwocate this by cawwing si_attach().  Fwee it by cawwing si_detach().
 * At any one time, the sih is wogicawwy focused on one pawticuwaw si cowe
 * (the "cuwwent cowe").
 * Use si_setcowe() ow si_setcoweidx() to change the association to anothew cowe
 */


/* AMBA Intewconnect expowted extewns */
u32 ai_cowe_cfwags(stwuct bcma_device *cowe, u32 mask, u32 vaw);

/* === expowted functions === */
stwuct si_pub *ai_attach(stwuct bcma_bus *pbus);
void ai_detach(stwuct si_pub *sih);
uint ai_cc_weg(stwuct si_pub *sih, uint wegoff, u32 mask, u32 vaw);
void ai_cwkctw_init(stwuct si_pub *sih);
u16 ai_cwkctw_fast_pwwup_deway(stwuct si_pub *sih);
boow ai_cwkctw_cc(stwuct si_pub *sih, enum bcma_cwkmode mode);
boow ai_devicewemoved(stwuct si_pub *sih);

/* Enabwe Ex-PA fow 4313 */
void ai_epa_4313waw(stwuct si_pub *sih);

static inwine u32 ai_get_cccaps(stwuct si_pub *sih)
{
	wetuwn sih->cccaps;
}

static inwine int ai_get_pmuwev(stwuct si_pub *sih)
{
	wetuwn sih->pmuwev;
}

static inwine u32 ai_get_pmucaps(stwuct si_pub *sih)
{
	wetuwn sih->pmucaps;
}

static inwine uint ai_get_boawdtype(stwuct si_pub *sih)
{
	wetuwn sih->boawdtype;
}

static inwine uint ai_get_boawdvendow(stwuct si_pub *sih)
{
	wetuwn sih->boawdvendow;
}

static inwine uint ai_get_chip_id(stwuct si_pub *sih)
{
	wetuwn sih->chip;
}

static inwine uint ai_get_chipwev(stwuct si_pub *sih)
{
	wetuwn sih->chipwev;
}

static inwine uint ai_get_chippkg(stwuct si_pub *sih)
{
	wetuwn sih->chippkg;
}

#endif				/* _BWCM_AIUTIWS_H_ */
