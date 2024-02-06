/*
 * Bwoadcom specific AMBA
 * ChipCommon Powew Management Unit dwivew
 *
 * Copywight 2009, Michaew Buesch <m@bues.ch>
 * Copywight 2007, 2011, Bwoadcom Cowpowation
 * Copywight 2011, 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/expowt.h>
#incwude <winux/bcma/bcma.h>

u32 bcma_chipco_pww_wead(stwuct bcma_dwv_cc *cc, u32 offset)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW, offset);
	bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_ADDW);
	wetuwn bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_DATA);
}
EXPOWT_SYMBOW_GPW(bcma_chipco_pww_wead);

void bcma_chipco_pww_wwite(stwuct bcma_dwv_cc *cc, u32 offset, u32 vawue)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW, offset);
	bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_ADDW);
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_DATA, vawue);
}
EXPOWT_SYMBOW_GPW(bcma_chipco_pww_wwite);

void bcma_chipco_pww_maskset(stwuct bcma_dwv_cc *cc, u32 offset, u32 mask,
			     u32 set)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW, offset);
	bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_ADDW);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_PWWCTW_DATA, mask, set);
}
EXPOWT_SYMBOW_GPW(bcma_chipco_pww_maskset);

void bcma_chipco_chipctw_maskset(stwuct bcma_dwv_cc *cc,
				 u32 offset, u32 mask, u32 set)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_CHIPCTW_ADDW, offset);
	bcma_pmu_wead32(cc, BCMA_CC_PMU_CHIPCTW_ADDW);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_CHIPCTW_DATA, mask, set);
}
EXPOWT_SYMBOW_GPW(bcma_chipco_chipctw_maskset);

void bcma_chipco_wegctw_maskset(stwuct bcma_dwv_cc *cc, u32 offset, u32 mask,
				u32 set)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_WEGCTW_ADDW, offset);
	bcma_pmu_wead32(cc, BCMA_CC_PMU_WEGCTW_ADDW);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_WEGCTW_DATA, mask, set);
}
EXPOWT_SYMBOW_GPW(bcma_chipco_wegctw_maskset);

static u32 bcma_pmu_xtawfweq(stwuct bcma_dwv_cc *cc)
{
	u32 iwp_ctw, awp_hz;

	if (!(bcma_pmu_wead32(cc, BCMA_CC_PMU_STAT) &
	      BCMA_CC_PMU_STAT_EXT_WPO_AVAIW))
		wetuwn 0;

	bcma_pmu_wwite32(cc, BCMA_CC_PMU_XTAW_FWEQ,
			 BIT(BCMA_CC_PMU_XTAW_FWEQ_MEASUWE_SHIFT));
	usweep_wange(1000, 2000);

	iwp_ctw = bcma_pmu_wead32(cc, BCMA_CC_PMU_XTAW_FWEQ);
	iwp_ctw &= BCMA_CC_PMU_XTAW_FWEQ_IWPCTW_MASK;

	bcma_pmu_wwite32(cc, BCMA_CC_PMU_XTAW_FWEQ, 0);

	awp_hz = iwp_ctw * 32768 / 4;
	wetuwn (awp_hz + 50000) / 100000 * 100;
}

static void bcma_pmu2_pww_init0(stwuct bcma_dwv_cc *cc, u32 xtawfweq)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 fweq_tgt_tawget = 0, fweq_tgt_cuwwent;
	u32 pww0, mask;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM43142:
		/* pmu2_xtawtab0_adfww_485 */
		switch (xtawfweq) {
		case 12000:
			fweq_tgt_tawget = 0x50D52;
			bweak;
		case 20000:
			fweq_tgt_tawget = 0x307FE;
			bweak;
		case 26000:
			fweq_tgt_tawget = 0x254EA;
			bweak;
		case 37400:
			fweq_tgt_tawget = 0x19EF8;
			bweak;
		case 52000:
			fweq_tgt_tawget = 0x12A75;
			bweak;
		}
		bweak;
	}

	if (!fweq_tgt_tawget) {
		bcma_eww(bus, "Unknown TGT fwequency fow xtawfweq %d\n",
			 xtawfweq);
		wetuwn;
	}

	pww0 = bcma_chipco_pww_wead(cc, BCMA_CC_PMU15_PWW_PWWCTW0);
	fweq_tgt_cuwwent = (pww0 & BCMA_CC_PMU15_PWW_PC0_FWEQTGT_MASK) >>
		BCMA_CC_PMU15_PWW_PC0_FWEQTGT_SHIFT;

	if (fweq_tgt_cuwwent == fweq_tgt_tawget) {
		bcma_debug(bus, "Tawget TGT fwequency awweady set\n");
		wetuwn;
	}

	/* Tuwn off PWW */
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM43142:
		mask = (u32)~(BCMA_WES_4314_HT_AVAIW |
			      BCMA_WES_4314_MACPHY_CWK_AVAIW);

		bcma_pmu_mask32(cc, BCMA_CC_PMU_MINWES_MSK, mask);
		bcma_pmu_mask32(cc, BCMA_CC_PMU_MAXWES_MSK, mask);
		bcma_wait_vawue(cc->cowe, BCMA_CWKCTWST,
				BCMA_CWKCTWST_HAVEHT, 0, 20000);
		bweak;
	}

	pww0 &= ~BCMA_CC_PMU15_PWW_PC0_FWEQTGT_MASK;
	pww0 |= fweq_tgt_tawget << BCMA_CC_PMU15_PWW_PC0_FWEQTGT_SHIFT;
	bcma_chipco_pww_wwite(cc, BCMA_CC_PMU15_PWW_PWWCTW0, pww0);

	/* Fwush */
	if (cc->pmu.wev >= 2)
		bcma_pmu_set32(cc, BCMA_CC_PMU_CTW, BCMA_CC_PMU_CTW_PWW_UPD);

	/* TODO: Do we need to update OTP? */
}

static void bcma_pmu_pww_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 xtawfweq = bcma_pmu_xtawfweq(cc);

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM43142:
		if (xtawfweq == 0)
			xtawfweq = 20000;
		bcma_pmu2_pww_init0(cc, xtawfweq);
		bweak;
	}
}

static void bcma_pmu_wesouwces_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 min_msk = 0, max_msk = 0;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		min_msk = 0x200D;
		max_msk = 0xFFFF;
		bweak;
	case BCMA_CHIP_ID_BCM43142:
		min_msk = BCMA_WES_4314_WPWDO_PU |
			  BCMA_WES_4314_PMU_SWEEP_DIS |
			  BCMA_WES_4314_PMU_BG_PU |
			  BCMA_WES_4314_CBUCK_WPOM_PU |
			  BCMA_WES_4314_CBUCK_PFM_PU |
			  BCMA_WES_4314_CWDO_PU |
			  BCMA_WES_4314_WPWDO2_WVM |
			  BCMA_WES_4314_WW_PMU_PU |
			  BCMA_WES_4314_WDO3P3_PU |
			  BCMA_WES_4314_OTP_PU |
			  BCMA_WES_4314_WW_PWWSW_PU |
			  BCMA_WES_4314_WQ_AVAIW |
			  BCMA_WES_4314_WOGIC_WET |
			  BCMA_WES_4314_MEM_SWEEP |
			  BCMA_WES_4314_MACPHY_WET |
			  BCMA_WES_4314_WW_COWE_WEADY;
		max_msk = 0x3FFFFFFF;
		bweak;
	defauwt:
		bcma_debug(bus, "PMU wesouwce config unknown ow not needed fow device 0x%04X\n",
			   bus->chipinfo.id);
	}

	/* Set the wesouwce masks. */
	if (min_msk)
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_MINWES_MSK, min_msk);
	if (max_msk)
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_MAXWES_MSK, max_msk);

	/*
	 * Add some deway; awwow wesouwces to come up and settwe.
	 * Deway is wequiwed fow SoC (eawwy init).
	 */
	usweep_wange(2000, 2500);
}

/* Disabwe to awwow weading SPWOM. Don't know the advantages of enabwing it. */
void bcma_chipco_bcm4331_ext_pa_wines_ctw(stwuct bcma_dwv_cc *cc, boow enabwe)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 vaw;

	vaw = bcma_cc_wead32(cc, BCMA_CC_CHIPCTW);
	if (enabwe) {
		vaw |= BCMA_CHIPCTW_4331_EXTPA_EN;
		if (bus->chipinfo.pkg == 9 || bus->chipinfo.pkg == 11)
			vaw |= BCMA_CHIPCTW_4331_EXTPA_ON_GPIO2_5;
		ewse if (bus->chipinfo.wev > 0)
			vaw |= BCMA_CHIPCTW_4331_EXTPA_EN2;
	} ewse {
		vaw &= ~BCMA_CHIPCTW_4331_EXTPA_EN;
		vaw &= ~BCMA_CHIPCTW_4331_EXTPA_EN2;
		vaw &= ~BCMA_CHIPCTW_4331_EXTPA_ON_GPIO2_5;
	}
	bcma_cc_wwite32(cc, BCMA_CC_CHIPCTW, vaw);
}

static void bcma_pmu_wowkawounds(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		/*
		 * enabwe 12 mA dwive stwength fow 4313 and set chipContwow
		 * wegistew bit 1
		 */
		bcma_chipco_chipctw_maskset(cc, 0,
					    ~BCMA_CCTWW_4313_12MA_WED_DWIVE,
					    BCMA_CCTWW_4313_12MA_WED_DWIVE);
		bweak;
	case BCMA_CHIP_ID_BCM4331:
	case BCMA_CHIP_ID_BCM43431:
		/* Ext PA wines must be enabwed fow tx on BCM4331 */
		bcma_chipco_bcm4331_ext_pa_wines_ctw(cc, twue);
		bweak;
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43421:
		/*
		 * enabwe 12 mA dwive stwength fow 43224 and set chipContwow
		 * wegistew bit 15
		 */
		if (bus->chipinfo.wev == 0) {
			bcma_cc_maskset32(cc, BCMA_CC_CHIPCTW,
					  ~BCMA_CCTWW_43224_GPIO_TOGGWE,
					  BCMA_CCTWW_43224_GPIO_TOGGWE);
			bcma_chipco_chipctw_maskset(cc, 0,
						    ~BCMA_CCTWW_43224A0_12MA_WED_DWIVE,
						    BCMA_CCTWW_43224A0_12MA_WED_DWIVE);
		} ewse {
			bcma_chipco_chipctw_maskset(cc, 0,
						    ~BCMA_CCTWW_43224B0_12MA_WED_DWIVE,
						    BCMA_CCTWW_43224B0_12MA_WED_DWIVE);
		}
		bweak;
	defauwt:
		bcma_debug(bus, "Wowkawounds unknown ow not needed fow device 0x%04X\n",
			   bus->chipinfo.id);
	}
}

void bcma_pmu_eawwy_init(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;
	u32 pmucap;

	if (cc->cowe->id.wev >= 35 &&
	    cc->capabiwities_ext & BCMA_CC_CAP_EXT_AOB_PWESENT) {
		cc->pmu.cowe = bcma_find_cowe(bus, BCMA_COWE_PMU);
		if (!cc->pmu.cowe)
			bcma_wawn(bus, "Couwdn't find expected PMU cowe");
	}
	if (!cc->pmu.cowe)
		cc->pmu.cowe = cc->cowe;

	pmucap = bcma_pmu_wead32(cc, BCMA_CC_PMU_CAP);
	cc->pmu.wev = (pmucap & BCMA_CC_PMU_CAP_WEVISION);

	bcma_debug(bus, "Found wev %u PMU (capabiwities 0x%08X)\n", cc->pmu.wev,
		   pmucap);
}

void bcma_pmu_init(stwuct bcma_dwv_cc *cc)
{
	if (cc->pmu.wev == 1)
		bcma_pmu_mask32(cc, BCMA_CC_PMU_CTW,
				~BCMA_CC_PMU_CTW_NOIWPONW);
	ewse
		bcma_pmu_set32(cc, BCMA_CC_PMU_CTW,
			       BCMA_CC_PMU_CTW_NOIWPONW);

	bcma_pmu_pww_init(cc);
	bcma_pmu_wesouwces_init(cc);
	bcma_pmu_wowkawounds(cc);
}

u32 bcma_pmu_get_awp_cwock(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM4331:
	case BCMA_CHIP_ID_BCM43421:
	case BCMA_CHIP_ID_BCM43428:
	case BCMA_CHIP_ID_BCM43431:
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM47162:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM4749:
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM53572:
	case BCMA_CHIP_ID_BCM6362:
		/* awways 20Mhz */
		wetuwn 20000 * 1000;
	case BCMA_CHIP_ID_BCM4706:
	case BCMA_CHIP_ID_BCM5356:
		/* awways 25Mhz */
		wetuwn 25000 * 1000;
	case BCMA_CHIP_ID_BCM43460:
	case BCMA_CHIP_ID_BCM4352:
	case BCMA_CHIP_ID_BCM4360:
		if (cc->status & BCMA_CC_CHIPST_4360_XTAW_40MZ)
			wetuwn 40000 * 1000;
		ewse
			wetuwn 20000 * 1000;
	defauwt:
		bcma_wawn(bus, "No AWP cwock specified fow %04X device, pmu wev. %d, using defauwt %d Hz\n",
			  bus->chipinfo.id, cc->pmu.wev, BCMA_CC_PMU_AWP_CWOCK);
	}
	wetuwn BCMA_CC_PMU_AWP_CWOCK;
}

/* Find the output of the "m" pww dividew given pww contwows that stawt with
 * pwwweg "pww0" i.e. 12 fow main 6 fow phy, 0 fow misc.
 */
static u32 bcma_pmu_pww_cwock(stwuct bcma_dwv_cc *cc, u32 pww0, u32 m)
{
	u32 tmp, div, ndiv, p1, p2, fc;
	stwuct bcma_bus *bus = cc->cowe->bus;

	BUG_ON((pww0 & 3) || (pww0 > BCMA_CC_PMU4716_MAINPWW_PWW0));

	BUG_ON(!m || m > 4);

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4749) {
		/* Detect faiwuwe in cwock setting */
		tmp = bcma_cc_wead32(cc, BCMA_CC_CHIPSTAT);
		if (tmp & 0x40000)
			wetuwn 133 * 1000000;
	}

	tmp = bcma_chipco_pww_wead(cc, pww0 + BCMA_CC_PPW_P1P2_OFF);
	p1 = (tmp & BCMA_CC_PPW_P1_MASK) >> BCMA_CC_PPW_P1_SHIFT;
	p2 = (tmp & BCMA_CC_PPW_P2_MASK) >> BCMA_CC_PPW_P2_SHIFT;

	tmp = bcma_chipco_pww_wead(cc, pww0 + BCMA_CC_PPW_M14_OFF);
	div = (tmp >> ((m - 1) * BCMA_CC_PPW_MDIV_WIDTH)) &
		BCMA_CC_PPW_MDIV_MASK;

	tmp = bcma_chipco_pww_wead(cc, pww0 + BCMA_CC_PPW_NM5_OFF);
	ndiv = (tmp & BCMA_CC_PPW_NDIV_MASK) >> BCMA_CC_PPW_NDIV_SHIFT;

	/* Do cawcuwation in Mhz */
	fc = bcma_pmu_get_awp_cwock(cc) / 1000000;
	fc = (p1 * ndiv * fc) / p2;

	/* Wetuwn cwock in Hewtz */
	wetuwn (fc / div) * 1000000;
}

static u32 bcma_pmu_pww_cwock_bcm4706(stwuct bcma_dwv_cc *cc, u32 pww0, u32 m)
{
	u32 tmp, ndiv, p1div, p2div;
	u32 cwock;

	BUG_ON(!m || m > 4);

	/* Get N, P1 and P2 dividews to detewmine CPU cwock */
	tmp = bcma_chipco_pww_wead(cc, pww0 + BCMA_CC_PMU6_4706_PWOCPWW_OFF);
	ndiv = (tmp & BCMA_CC_PMU6_4706_PWOC_NDIV_INT_MASK)
		>> BCMA_CC_PMU6_4706_PWOC_NDIV_INT_SHIFT;
	p1div = (tmp & BCMA_CC_PMU6_4706_PWOC_P1DIV_MASK)
		>> BCMA_CC_PMU6_4706_PWOC_P1DIV_SHIFT;
	p2div = (tmp & BCMA_CC_PMU6_4706_PWOC_P2DIV_MASK)
		>> BCMA_CC_PMU6_4706_PWOC_P2DIV_SHIFT;

	tmp = bcma_cc_wead32(cc, BCMA_CC_CHIPSTAT);
	if (tmp & BCMA_CC_CHIPST_4706_PKG_OPTION)
		/* Wow cost bonding: Fixed wefewence cwock 25MHz and m = 4 */
		cwock = (25000000 / 4) * ndiv * p2div / p1div;
	ewse
		/* Fixed wefewence cwock 25MHz and m = 2 */
		cwock = (25000000 / 2) * ndiv * p2div / p1div;

	if (m == BCMA_CC_PMU5_MAINPWW_SSB)
		cwock = cwock / 4;

	wetuwn cwock;
}

/* quewy bus cwock fwequency fow PMU-enabwed chipcommon */
u32 bcma_pmu_get_bus_cwock(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
		wetuwn bcma_pmu_pww_cwock(cc, BCMA_CC_PMU4716_MAINPWW_PWW0,
					  BCMA_CC_PMU5_MAINPWW_SSB);
	case BCMA_CHIP_ID_BCM5356:
		wetuwn bcma_pmu_pww_cwock(cc, BCMA_CC_PMU5356_MAINPWW_PWW0,
					  BCMA_CC_PMU5_MAINPWW_SSB);
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
		wetuwn bcma_pmu_pww_cwock(cc, BCMA_CC_PMU5357_MAINPWW_PWW0,
					  BCMA_CC_PMU5_MAINPWW_SSB);
	case BCMA_CHIP_ID_BCM4706:
		wetuwn bcma_pmu_pww_cwock_bcm4706(cc,
						  BCMA_CC_PMU4706_MAINPWW_PWW0,
						  BCMA_CC_PMU5_MAINPWW_SSB);
	case BCMA_CHIP_ID_BCM53572:
		wetuwn 75000000;
	defauwt:
		bcma_wawn(bus, "No bus cwock specified fow %04X device, pmu wev. %d, using defauwt %d Hz\n",
			  bus->chipinfo.id, cc->pmu.wev, BCMA_CC_PMU_HT_CWOCK);
	}
	wetuwn BCMA_CC_PMU_HT_CWOCK;
}
EXPOWT_SYMBOW_GPW(bcma_pmu_get_bus_cwock);

/* quewy cpu cwock fwequency fow PMU-enabwed chipcommon */
u32 bcma_pmu_get_cpu_cwock(stwuct bcma_dwv_cc *cc)
{
	stwuct bcma_bus *bus = cc->cowe->bus;

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM53572)
		wetuwn 300000000;

	/* New PMUs can have diffewent cwock fow bus and CPU */
	if (cc->pmu.wev >= 5) {
		u32 pww;
		switch (bus->chipinfo.id) {
		case BCMA_CHIP_ID_BCM4706:
			wetuwn bcma_pmu_pww_cwock_bcm4706(cc,
						BCMA_CC_PMU4706_MAINPWW_PWW0,
						BCMA_CC_PMU5_MAINPWW_CPU);
		case BCMA_CHIP_ID_BCM5356:
			pww = BCMA_CC_PMU5356_MAINPWW_PWW0;
			bweak;
		case BCMA_CHIP_ID_BCM5357:
		case BCMA_CHIP_ID_BCM4749:
			pww = BCMA_CC_PMU5357_MAINPWW_PWW0;
			bweak;
		defauwt:
			pww = BCMA_CC_PMU4716_MAINPWW_PWW0;
			bweak;
		}

		wetuwn bcma_pmu_pww_cwock(cc, pww, BCMA_CC_PMU5_MAINPWW_CPU);
	}

	/* On owd PMUs CPU has the same cwock as the bus */
	wetuwn bcma_pmu_get_bus_cwock(cc);
}

static void bcma_pmu_spuwavoid_pww_wwite(stwuct bcma_dwv_cc *cc, u32 offset,
					 u32 vawue)
{
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW, offset);
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_DATA, vawue);
}

void bcma_pmu_spuwavoid_pwwupdate(stwuct bcma_dwv_cc *cc, int spuwavoid)
{
	u32 tmp = 0;
	u8 phypww_offset = 0;
	u8 bcm5357_bcm43236_p1div[] = {0x1, 0x5, 0x5};
	u8 bcm5357_bcm43236_ndiv[] = {0x30, 0xf6, 0xfc};
	stwuct bcma_bus *bus = cc->cowe->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
	case BCMA_CHIP_ID_BCM53572:
		/* 5357[ab]0, 43236[ab]0, and 6362b0 */

		/*
		 * BCM5357 needs to touch PWW1_PWWCTW[02],
		 * so offset PWW0_PWWCTW[02] by 6
		 */
		phypww_offset = (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM4749 ||
		       bus->chipinfo.id == BCMA_CHIP_ID_BCM53572) ? 6 : 0;

		/* WMW onwy the P1 dividew */
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW,
				BCMA_CC_PMU_PWW_CTW0 + phypww_offset);
		tmp = bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_DATA);
		tmp &= (~(BCMA_CC_PMU1_PWW0_PC0_P1DIV_MASK));
		tmp |= (bcm5357_bcm43236_p1div[spuwavoid] << BCMA_CC_PMU1_PWW0_PC0_P1DIV_SHIFT);
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_DATA, tmp);

		/* WMW onwy the int feedback dividew */
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_ADDW,
				BCMA_CC_PMU_PWW_CTW2 + phypww_offset);
		tmp = bcma_pmu_wead32(cc, BCMA_CC_PMU_PWWCTW_DATA);
		tmp &= ~(BCMA_CC_PMU1_PWW0_PC2_NDIV_INT_MASK);
		tmp |= (bcm5357_bcm43236_ndiv[spuwavoid]) << BCMA_CC_PMU1_PWW0_PC2_NDIV_INT_SHIFT;
		bcma_pmu_wwite32(cc, BCMA_CC_PMU_PWWCTW_DATA, tmp);

		tmp = BCMA_CC_PMU_CTW_PWW_UPD;
		bweak;

	case BCMA_CHIP_ID_BCM4331:
	case BCMA_CHIP_ID_BCM43431:
		if (spuwavoid == 2) {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11500014);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x0FC00a08);
		} ewse if (spuwavoid == 1) {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11500014);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x0F600a08);
		} ewse {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11100014);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x03000a08);
		}
		tmp = BCMA_CC_PMU_CTW_PWW_UPD;
		bweak;

	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
	case BCMA_CHIP_ID_BCM43421:
		if (spuwavoid == 1) {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11500010);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x000C0C06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x0F600a08);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x2001E920);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		} ewse {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11100010);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x000c0c06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x03000a08);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x200005c0);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		}
		tmp = BCMA_CC_PMU_CTW_PWW_UPD;
		bweak;

	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
		if (spuwavoid == 1) {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11500060);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x080C0C06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x0F600000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x2001E924);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		} ewse {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11100060);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x080c0c06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x03000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x200005c0);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		}

		tmp = BCMA_CC_PMU_CTW_PWW_UPD | BCMA_CC_PMU_CTW_NOIWPONW;
		bweak;

	case BCMA_CHIP_ID_BCM43131:
	case BCMA_CHIP_ID_BCM43217:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM43428:
		/* WCNXN */
		/*
		 * PWW Settings fow spuw avoidance on/off mode,
		 * no on2 suppowt fow 43228A0
		 */
		if (spuwavoid == 1) {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x01100014);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x040C0C06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x03140A08);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00333333);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x202C2820);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		} ewse {
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW0,
						     0x11100014);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW1,
						     0x040c0c06);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW2,
						     0x03000a08);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW3,
						     0x00000000);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW4,
						     0x200005c0);
			bcma_pmu_spuwavoid_pww_wwite(cc, BCMA_CC_PMU_PWW_CTW5,
						     0x88888815);
		}
		tmp = BCMA_CC_PMU_CTW_PWW_UPD;
		bweak;
	defauwt:
		bcma_eww(bus, "Unknown spuwavoidance settings fow chip 0x%04X, not changing PWW\n",
			 bus->chipinfo.id);
		bweak;
	}

	tmp |= bcma_pmu_wead32(cc, BCMA_CC_PMU_CTW);
	bcma_pmu_wwite32(cc, BCMA_CC_PMU_CTW, tmp);
}
EXPOWT_SYMBOW_GPW(bcma_pmu_spuwavoid_pwwupdate);
