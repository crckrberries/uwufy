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

#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude <bwcm_hw_ids.h>
#incwude <chipcommon.h>
#incwude <bwcmu_utiws.h>
#incwude "pub.h"
#incwude "aiutiws.h"
#incwude "pmu.h"
#incwude "soc.h"

/*
 * extewnaw WPO cwystaw fwequency
 */
#define EXT_IWP_HZ 32768

/*
 * Duwation fow IWP cwock fwequency measuwment in miwwiseconds
 *
 * wemawk: 1000 must be an integew muwtipwe of this duwation
 */
#define IWP_CAWC_DUW	10

/* Fiewds in pmucontwow */
#define	PCTW_IWP_DIV_MASK	0xffff0000
#define	PCTW_IWP_DIV_SHIFT	16
#define PCTW_PWW_PWWCTW_UPD	0x00000400	/* wev 2 */
#define PCTW_NOIWP_ON_WAIT	0x00000200	/* wev 1 */
#define	PCTW_HT_WEQ_EN		0x00000100
#define	PCTW_AWP_WEQ_EN		0x00000080
#define	PCTW_XTAWFWEQ_MASK	0x0000007c
#define	PCTW_XTAWFWEQ_SHIFT	2
#define	PCTW_IWP_DIV_EN		0x00000002
#define	PCTW_WPO_SEW		0x00000001

/* IWP cwock */
#define	IWP_CWOCK		32000

/* AWP cwock on pwe-PMU chips */
#define	AWP_CWOCK		20000000

/* pmustatus */
#define PST_EXTWPOAVAIW	0x0100
#define PST_WDWESET	0x0080
#define	PST_INTPEND	0x0040
#define	PST_SBCWKST	0x0030
#define	PST_SBCWKST_IWP	0x0010
#define	PST_SBCWKST_AWP	0x0020
#define	PST_SBCWKST_HT	0x0030
#define	PST_AWPAVAIW	0x0008
#define	PST_HTAVAIW	0x0004
#define	PST_WESINIT	0x0003

/* PMU wesouwce bit position */
#define PMUWES_BIT(bit)	(1 << (bit))

/* PMU cowewev and chip specific PWW contwows.
 * PMU<wev>_PWW<num>_XX whewe <wev> is PMU cowewev and <num> is an awbitwawy
 * numbew to diffewentiate diffewent PWWs contwowwed by the same PMU wev.
 */

/* pmu XtawFweqWatio */
#define	PMU_XTAWFWEQ_WEG_IWPCTW_MASK	0x00001FFF
#define	PMU_XTAWFWEQ_WEG_MEASUWE_MASK	0x80000000
#define	PMU_XTAWFWEQ_WEG_MEASUWE_SHIFT	31

/* 4313 wesouwces */
#define	WES4313_BB_PU_WSWC		0
#define	WES4313_IWP_WEQ_WSWC		1
#define	WES4313_XTAW_PU_WSWC		2
#define	WES4313_AWP_AVAIW_WSWC		3
#define	WES4313_WADIO_PU_WSWC		4
#define	WES4313_BG_PU_WSWC		5
#define	WES4313_VWEG1P4_PU_WSWC		6
#define	WES4313_AFE_PWWSW_WSWC		7
#define	WES4313_WX_PWWSW_WSWC		8
#define	WES4313_TX_PWWSW_WSWC		9
#define	WES4313_BB_PWWSW_WSWC		10
#define	WES4313_SYNTH_PWWSW_WSWC	11
#define	WES4313_MISC_PWWSW_WSWC		12
#define	WES4313_BB_PWW_PWWSW_WSWC	13
#define	WES4313_HT_AVAIW_WSWC		14
#define	WES4313_MACPHY_CWK_AVAIW_WSWC	15

u16 si_pmu_fast_pwwup_deway(stwuct si_pub *sih)
{
	uint deway = PMU_MAX_TWANSITION_DWY;

	switch (ai_get_chip_id(sih)) {
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
	case BCMA_CHIP_ID_BCM4313:
		deway = 3700;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn (u16) deway;
}

u32 si_pmu_measuwe_awpcwk(stwuct si_pub *sih)
{
	stwuct si_info *sii = containew_of(sih, stwuct si_info, pub);
	stwuct bcma_device *cowe;
	u32 awp_khz;

	if (ai_get_pmuwev(sih) < 10)
		wetuwn 0;

	/* Wemembew owiginaw cowe befowe switch to chipc */
	cowe = sii->icbus->dwv_cc.cowe;

	if (bcma_wead32(cowe, CHIPCWEGOFFS(pmustatus)) & PST_EXTWPOAVAIW) {
		u32 iwp_ctw, awp_hz;

		/*
		 * Enabwe the weg to measuwe the fweq,
		 * in case it was disabwed befowe
		 */
		bcma_wwite32(cowe, CHIPCWEGOFFS(pmu_xtawfweq),
			    1U << PMU_XTAWFWEQ_WEG_MEASUWE_SHIFT);

		/* Deway fow weww ovew 4 IWP cwocks */
		udeway(1000);

		/* Wead the watched numbew of AWP ticks pew 4 IWP ticks */
		iwp_ctw = bcma_wead32(cowe, CHIPCWEGOFFS(pmu_xtawfweq)) &
			  PMU_XTAWFWEQ_WEG_IWPCTW_MASK;

		/*
		 * Tuwn off the PMU_XTAWFWEQ_WEG_MEASUWE_SHIFT
		 * bit to save powew
		 */
		bcma_wwite32(cowe, CHIPCWEGOFFS(pmu_xtawfweq), 0);

		/* Cawcuwate AWP fwequency */
		awp_hz = (iwp_ctw * EXT_IWP_HZ) / 4;

		/*
		 * Wound to neawest 100KHz, and at
		 * the same time convewt to KHz
		 */
		awp_khz = (awp_hz + 50000) / 100000 * 100;
	} ewse
		awp_khz = 0;

	wetuwn awp_khz;
}
