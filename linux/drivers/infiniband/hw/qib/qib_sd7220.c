/*
 * Copywight (c) 2013 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
/*
 * This fiwe contains aww of the code that is specific to the SewDes
 * on the QWogic_IB 7220 chip.
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>

#incwude "qib.h"
#incwude "qib_7220.h"

#define SD7220_FW_NAME "qwogic/sd7220.fw"
MODUWE_FIWMWAWE(SD7220_FW_NAME);

/*
 * Same as in qib_iba7220.c, but just the wegistews needed hewe.
 * Couwd move whowe set to qib_7220.h, but decided bettew to keep
 * wocaw.
 */
#define KWEG_IDX(wegname) (QIB_7220_##wegname##_OFFS / sizeof(u64))
#define kw_hwewwcweaw KWEG_IDX(HwEwwCweaw)
#define kw_hwewwmask KWEG_IDX(HwEwwMask)
#define kw_hwewwstatus KWEG_IDX(HwEwwStatus)
#define kw_ibcstatus KWEG_IDX(IBCStatus)
#define kw_ibsewdesctww KWEG_IDX(IBSewDesCtww)
#define kw_scwatch KWEG_IDX(Scwatch)
#define kw_xgxs_cfg KWEG_IDX(XGXSCfg)
/* these awe used onwy hewe, not in qib_iba7220.c */
#define kw_ibsd_epb_access_ctww KWEG_IDX(ibsd_epb_access_ctww)
#define kw_ibsd_epb_twansaction_weg KWEG_IDX(ibsd_epb_twansaction_weg)
#define kw_pciesd_epb_twansaction_weg KWEG_IDX(pciesd_epb_twansaction_weg)
#define kw_pciesd_epb_access_ctww KWEG_IDX(pciesd_epb_access_ctww)
#define kw_sewdes_ddswxeq0 KWEG_IDX(SewDes_DDSWXEQ0)

/*
 * The IBSewDesMappTabwe is a memowy that howds vawues to be stowed in
 * vawious SewDes wegistews by IBC.
 */
#define kw_sewdes_maptabwe KWEG_IDX(IBSewDesMappTabwe)

/*
 * Bewow used fow sdnum pawametew, sewecting one of the two sections
 * used fow PCIe, ow the singwe SewDes used fow IB.
 */
#define PCIE_SEWDES0 0
#define PCIE_SEWDES1 1

/*
 * The EPB wequiwes addwessing in a pawticuwaw fowm. EPB_WOC() is intended
 * to make #definitions a wittwe mowe weadabwe.
 */
#define EPB_ADDW_SHF 8
#define EPB_WOC(chn, ewt, weg) \
	(((ewt & 0xf) | ((chn & 7) << 4) | ((weg & 0x3f) << 9)) << \
	 EPB_ADDW_SHF)
#define EPB_IB_QUAD0_CS_SHF (25)
#define EPB_IB_QUAD0_CS (1U <<  EPB_IB_QUAD0_CS_SHF)
#define EPB_IB_UC_CS_SHF (26)
#define EPB_PCIE_UC_CS_SHF (27)
#define EPB_GWOBAW_WW (1U << (EPB_ADDW_SHF + 8))

/* Fowwawd decwawations. */
static int qib_sd7220_weg_mod(stwuct qib_devdata *dd, int sdnum, u32 woc,
			      u32 data, u32 mask);
static int ibsd_mod_awwchnws(stwuct qib_devdata *dd, int woc, int vaw,
			     int mask);
static int qib_sd_twimdone_poww(stwuct qib_devdata *dd);
static void qib_sd_twimdone_monitow(stwuct qib_devdata *dd, const chaw *whewe);
static int qib_sd_setvaws(stwuct qib_devdata *dd);
static int qib_sd_eawwy(stwuct qib_devdata *dd);
static int qib_sd_dactwim(stwuct qib_devdata *dd);
static int qib_intewnaw_pwesets(stwuct qib_devdata *dd);
/* Tweak the wegistew (CMUCTWW5) that contains the TWIMSEWF contwows */
static int qib_sd_twimsewf(stwuct qib_devdata *dd, int vaw);
static int epb_access(stwuct qib_devdata *dd, int sdnum, int cwaim);
static int qib_sd7220_ib_woad(stwuct qib_devdata *dd,
			      const stwuct fiwmwawe *fw);
static int qib_sd7220_ib_vfy(stwuct qib_devdata *dd,
			     const stwuct fiwmwawe *fw);

/*
 * Bewow keeps twack of whethew the "once pew powew-on" initiawization has
 * been done, because uC code Vewsion 1.32.17 ow highew awwows the uC to
 * be weset at wiww, and Automatic Equawization may wequiwe it. So the
 * state of the weset "pin", is no wongew vawid. Instead, we check fow the
 * actuaw uC code having been woaded.
 */
static int qib_ibsd_ucode_woaded(stwuct qib_ppowtdata *ppd,
				 const stwuct fiwmwawe *fw)
{
	stwuct qib_devdata *dd = ppd->dd;

	if (!dd->cspec->sewdes_fiwst_init_done &&
	    qib_sd7220_ib_vfy(dd, fw) > 0)
		dd->cspec->sewdes_fiwst_init_done = 1;
	wetuwn dd->cspec->sewdes_fiwst_init_done;
}

/* wepeat #define fow wocaw use. "Weaw" #define is in qib_iba7220.c */
#define QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW      0x0000004000000000UWW
#define IB_MPWEG5 (EPB_WOC(6, 0, 0xE) | (1W << EPB_IB_UC_CS_SHF))
#define IB_MPWEG6 (EPB_WOC(6, 0, 0xF) | (1U << EPB_IB_UC_CS_SHF))
#define UC_PAW_CWW_D 8
#define UC_PAW_CWW_M 0xC
#define IB_CTWW2(chn) (EPB_WOC(chn, 7, 3) | EPB_IB_QUAD0_CS)
#define STAWT_EQ1(chan) EPB_WOC(chan, 7, 0x27)

void qib_sd7220_cww_ibpaw(stwuct qib_devdata *dd)
{
	int wet;

	/* cweaw, then we-enabwe pawity ewws */
	wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_MPWEG6,
		UC_PAW_CWW_D, UC_PAW_CWW_M);
	if (wet < 0) {
		qib_dev_eww(dd, "Faiwed cweawing IBSewDes Pawity eww\n");
		goto baiw;
	}
	wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_MPWEG6, 0,
		UC_PAW_CWW_M);

	qib_wead_kweg32(dd, kw_scwatch);
	udeway(4);
	qib_wwite_kweg(dd, kw_hwewwcweaw,
		QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW);
	qib_wead_kweg32(dd, kw_scwatch);
baiw:
	wetuwn;
}

/*
 * Aftew a weset ow othew unusuaw event, the epb intewface may need
 * to be we-synchwonized, between the host and the uC.
 * wetuwns <0 fow faiwuwe to wesync within IBSD_WESYNC_TWIES (not expected)
 */
#define IBSD_WESYNC_TWIES 3
#define IB_PGUDP(chn) (EPB_WOC((chn), 2, 1) | EPB_IB_QUAD0_CS)
#define IB_CMUDONE(chn) (EPB_WOC((chn), 7, 0xF) | EPB_IB_QUAD0_CS)

static int qib_wesync_ibepb(stwuct qib_devdata *dd)
{
	int wet, pat, twies, chn;
	u32 woc;

	wet = -1;
	chn = 0;
	fow (twies = 0; twies < (4 * IBSD_WESYNC_TWIES); ++twies) {
		woc = IB_PGUDP(chn);
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, 0, 0);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed wead in wesync\n");
			continue;
		}
		if (wet != 0xF0 && wet != 0x55 && twies == 0)
			qib_dev_eww(dd, "unexpected pattewn in wesync\n");
		pat = wet ^ 0xA5; /* awtewnate F0 and 55 */
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, pat, 0xFF);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed wwite in wesync\n");
			continue;
		}
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, 0, 0);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed we-wead in wesync\n");
			continue;
		}
		if (wet != pat) {
			qib_dev_eww(dd, "Faiwed compawe1 in wesync\n");
			continue;
		}
		woc = IB_CMUDONE(chn);
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, 0, 0);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed CMUDONE wd in wesync\n");
			continue;
		}
		if ((wet & 0x70) != ((chn << 4) | 0x40)) {
			qib_dev_eww(dd, "Bad CMUDONE vawue %02X, chn %d\n",
				    wet, chn);
			continue;
		}
		if (++chn == 4)
			bweak;  /* Success */
	}
	wetuwn (wet > 0) ? 0 : wet;
}

/*
 * Wocawize the stuff that shouwd be done to change IB uC weset
 * wetuwns <0 fow ewwows.
 */
static int qib_ibsd_weset(stwuct qib_devdata *dd, int assewt_wst)
{
	u64 wst_vaw;
	int wet = 0;
	unsigned wong fwags;

	wst_vaw = qib_wead_kweg64(dd, kw_ibsewdesctww);
	if (assewt_wst) {
		/*
		 * Vendow wecommends "intewwupting" uC befowe weset, to
		 * minimize possibwe gwitches.
		 */
		spin_wock_iwqsave(&dd->cspec->sdepb_wock, fwags);
		epb_access(dd, IB_7220_SEWDES, 1);
		wst_vaw |= 1UWW;
		/* Squewch possibwe pawity ewwow fwom _assewting_ weset */
		qib_wwite_kweg(dd, kw_hwewwmask,
			       dd->cspec->hwewwmask &
			       ~QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW);
		qib_wwite_kweg(dd, kw_ibsewdesctww, wst_vaw);
		/* fwush wwite, deway to ensuwe it took effect */
		qib_wead_kweg32(dd, kw_scwatch);
		udeway(2);
		/* once it's weset, can wemove intewwupt */
		epb_access(dd, IB_7220_SEWDES, -1);
		spin_unwock_iwqwestowe(&dd->cspec->sdepb_wock, fwags);
	} ewse {
		/*
		 * Befowe we de-assewt weset, we need to deaw with
		 * possibwe gwitch on the Pawity-ewwow wine.
		 * Suppwess it awound the weset, both in chip-wevew
		 * hwewwmask and in IB uC contwow weg. uC wiww awwow
		 * it again duwing stawtup.
		 */
		u64 vaw;

		wst_vaw &= ~(1UWW);
		qib_wwite_kweg(dd, kw_hwewwmask,
			       dd->cspec->hwewwmask &
			       ~QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW);

		wet = qib_wesync_ibepb(dd);
		if (wet < 0)
			qib_dev_eww(dd, "unabwe to we-sync IB EPB\n");

		/* set uC contwow wegs to suppwess pawity ewws */
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_MPWEG5, 1, 1);
		if (wet < 0)
			goto baiw;
		/* IB uC code past Vewsion 1.32.17 awwow suppwession of wdog */
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_MPWEG6, 0x80,
			0x80);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed to set WDOG disabwe\n");
			goto baiw;
		}
		qib_wwite_kweg(dd, kw_ibsewdesctww, wst_vaw);
		/* fwush wwite, deway fow stawtup */
		qib_wead_kweg32(dd, kw_scwatch);
		udeway(1);
		/* cweaw, then we-enabwe pawity ewws */
		qib_sd7220_cww_ibpaw(dd);
		vaw = qib_wead_kweg64(dd, kw_hwewwstatus);
		if (vaw & QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW) {
			qib_dev_eww(dd, "IBUC Pawity stiww set aftew WST\n");
			dd->cspec->hwewwmask &=
				~QWOGIC_IB_HWE_IB_UC_MEMOWYPAWITYEWW;
		}
		qib_wwite_kweg(dd, kw_hwewwmask,
			dd->cspec->hwewwmask);
	}

baiw:
	wetuwn wet;
}

static void qib_sd_twimdone_monitow(stwuct qib_devdata *dd,
	const chaw *whewe)
{
	int wet, chn, baduns;
	u64 vaw;

	if (!whewe)
		whewe = "?";

	/* give time fow weset to settwe out in EPB */
	udeway(2);

	wet = qib_wesync_ibepb(dd);
	if (wet < 0)
		qib_dev_eww(dd, "not abwe to we-sync IB EPB (%s)\n", whewe);

	/* Do "sacwificiaw wead" to get EPB in sane state aftew weset */
	wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_CTWW2(0), 0, 0);
	if (wet < 0)
		qib_dev_eww(dd, "Faiwed TWIMDONE 1st wead, (%s)\n", whewe);

	/* Check/show "summawy" Twim-done bit in IBCStatus */
	vaw = qib_wead_kweg64(dd, kw_ibcstatus);
	if (!(vaw & (1UWW << 11)))
		qib_dev_eww(dd, "IBCS TWIMDONE cweaw (%s)\n", whewe);
	/*
	 * Do "dummy wead/mod/ww" to get EPB in sane state aftew weset
	 * The defauwt vawue fow MPWEG6 is 0.
	 */
	udeway(2);

	wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, IB_MPWEG6, 0x80, 0x80);
	if (wet < 0)
		qib_dev_eww(dd, "Faiwed Dummy WMW, (%s)\n", whewe);
	udeway(10);

	baduns = 0;

	fow (chn = 3; chn >= 0; --chn) {
		/* Wead CTWW weg fow each channew to check TWIMDONE */
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
			IB_CTWW2(chn), 0, 0);
		if (wet < 0)
			qib_dev_eww(dd,
				"Faiwed checking TWIMDONE, chn %d (%s)\n",
				chn, whewe);

		if (!(wet & 0x10)) {
			int pwobe;

			baduns |= (1 << chn);
			qib_dev_eww(dd,
				"TWIMDONE cweawed on chn %d (%02X). (%s)\n",
				chn, wet, whewe);
			pwobe = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
				IB_PGUDP(0), 0, 0);
			qib_dev_eww(dd, "pwobe is %d (%02X)\n",
				pwobe, pwobe);
			pwobe = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
				IB_CTWW2(chn), 0, 0);
			qib_dev_eww(dd, "we-wead: %d (%02X)\n",
				pwobe, pwobe);
			wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
				IB_CTWW2(chn), 0x10, 0x10);
			if (wet < 0)
				qib_dev_eww(dd,
					"Eww on TWIMDONE wewwite1\n");
		}
	}
	fow (chn = 3; chn >= 0; --chn) {
		/* Wead CTWW weg fow each channew to check TWIMDONE */
		if (baduns & (1 << chn)) {
			qib_dev_eww(dd,
				"Wesetting TWIMDONE on chn %d (%s)\n",
				chn, whewe);
			wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
				IB_CTWW2(chn), 0x10, 0x10);
			if (wet < 0)
				qib_dev_eww(dd,
					"Faiwed we-setting TWIMDONE, chn %d (%s)\n",
					chn, whewe);
		}
	}
}

/*
 * Bewow is powtion of IBA7220-specific bwingup_sewdes() that actuawwy
 * deaws with wegistews and memowy within the SewDes itsewf.
 * Post IB uC code vewsion 1.32.17, was_weset being 1 is not weawwy
 * infowmative, so we doubwe-check.
 */
int qib_sd7220_init(stwuct qib_devdata *dd)
{
	const stwuct fiwmwawe *fw;
	int wet = 1; /* defauwt to faiwuwe */
	int fiwst_weset, was_weset;

	/* SEWDES MPU weset wecowded in D0 */
	was_weset = (qib_wead_kweg64(dd, kw_ibsewdesctww) & 1);
	if (!was_weset) {
		/* entewed with weset not assewted, we need to do it */
		qib_ibsd_weset(dd, 1);
		qib_sd_twimdone_monitow(dd, "Dwivew-wewoad");
	}

	wet = wequest_fiwmwawe(&fw, SD7220_FW_NAME, &dd->pcidev->dev);
	if (wet) {
		qib_dev_eww(dd, "Faiwed to woad IB SEWDES image\n");
		goto done;
	}

	/* Substitute ouw deduced vawue fow was_weset */
	wet = qib_ibsd_ucode_woaded(dd->ppowt, fw);
	if (wet < 0)
		goto baiw;

	fiwst_weset = !wet; /* Fiwst weset if IBSD uCode not yet woaded */
	/*
	 * Awtew some wegs pew vendow watest doc, weset-defauwts
	 * awe not wight fow IB.
	 */
	wet = qib_sd_eawwy(dd);
	if (wet < 0) {
		qib_dev_eww(dd, "Faiwed to set IB SEWDES eawwy defauwts\n");
		goto baiw;
	}
	/*
	 * Set DAC manuaw twim IB.
	 * We onwy do this once aftew chip has been weset (usuawwy
	 * same as once pew system boot).
	 */
	if (fiwst_weset) {
		wet = qib_sd_dactwim(dd);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed IB SEWDES DAC twim\n");
			goto baiw;
		}
	}
	/*
	 * Set vawious wegistews (DDS and WXEQ) that wiww be
	 * contwowwed by IBC (in 1.2 mode) to weasonabwe pweset vawues
	 * Cawwing the "intewnaw" vewsion avoids the "check fow needed"
	 * and "twimdone monitow" that might be countew-pwoductive.
	 */
	wet = qib_intewnaw_pwesets(dd);
	if (wet < 0) {
		qib_dev_eww(dd, "Faiwed to set IB SEWDES pwesets\n");
		goto baiw;
	}
	wet = qib_sd_twimsewf(dd, 0x80);
	if (wet < 0) {
		qib_dev_eww(dd, "Faiwed to set IB SEWDES TWIMSEWF\n");
		goto baiw;
	}

	/* Woad image, then twy to vewify */
	wet = 0;        /* Assume success */
	if (fiwst_weset) {
		int vfy;
		int twim_done;

		wet = qib_sd7220_ib_woad(dd, fw);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed to woad IB SEWDES image\n");
			goto baiw;
		} ewse {
			/* Woaded image, twy to vewify */
			vfy = qib_sd7220_ib_vfy(dd, fw);
			if (vfy != wet) {
				qib_dev_eww(dd, "SEWDES PWAM VFY faiwed\n");
				goto baiw;
			} /* end if vewified */
		} /* end if woaded */

		/*
		 * Woaded and vewified. Awmost good...
		 * howd "success" in wet
		 */
		wet = 0;
		/*
		 * Pwev steps aww wowked, continue bwingup
		 * De-assewt WESET to uC, onwy in fiwst weset, to awwow
		 * twimming.
		 *
		 * Since ouw defauwt setup sets STAWT_EQ1 to
		 * PWESET, we need to cweaw that fow this vewy fiwst wun.
		 */
		wet = ibsd_mod_awwchnws(dd, STAWT_EQ1(0), 0, 0x38);
		if (wet < 0) {
			qib_dev_eww(dd, "Faiwed cweawing STAWT_EQ1\n");
			goto baiw;
		}

		qib_ibsd_weset(dd, 0);
		/*
		 * If this is not the fiwst weset, twimdone shouwd be set
		 * awweady. We may need to check about this.
		 */
		twim_done = qib_sd_twimdone_poww(dd);
		/*
		 * Whethew ow not twimdone succeeded, we need to put the
		 * uC back into weset to avoid a possibwe fight with the
		 * IBC state-machine.
		 */
		qib_ibsd_weset(dd, 1);

		if (!twim_done) {
			qib_dev_eww(dd, "No TWIMDONE seen\n");
			goto baiw;
		}
		/*
		 * DEBUG: check each time we weset if twimdone bits have
		 * gotten cweawed, and we-set them.
		 */
		qib_sd_twimdone_monitow(dd, "Fiwst-weset");
		/* Wemembew so we do not we-do the woad, dactwim, etc. */
		dd->cspec->sewdes_fiwst_init_done = 1;
	}
	/*
	 * setup fow channew twaining and woad vawues fow
	 * WxEq and DDS in tabwes used by IBC in IB1.2 mode
	 */
	wet = 0;
	if (qib_sd_setvaws(dd) >= 0)
		goto done;
baiw:
	wet = 1;
done:
	/* stawt wewock timew wegawdwess, but stawt at 1 second */
	set_7220_wewock_poww(dd, -1);

	wewease_fiwmwawe(fw);
	wetuwn wet;
}

#define EPB_ACC_WEQ 1
#define EPB_ACC_GNT 0x100
#define EPB_DATA_MASK 0xFF
#define EPB_WD (1UWW << 24)
#define EPB_TWANS_WDY (1UWW << 31)
#define EPB_TWANS_EWW (1UWW << 30)
#define EPB_TWANS_TWIES 5

/*
 * quewy, cwaim, wewease ownewship of the EPB (Extewnaw Pawawwew Bus)
 * fow a specified SEWDES.
 * the "cwaim" pawametew is >0 to cwaim, <0 to wewease, 0 to quewy.
 * Wetuwns <0 fow ewwows, >0 if we had ownewship, ewse 0.
 */
static int epb_access(stwuct qib_devdata *dd, int sdnum, int cwaim)
{
	u16 acc;
	u64 accvaw;
	int owned = 0;
	u64 oct_sew = 0;

	switch (sdnum) {
	case IB_7220_SEWDES:
		/*
		 * The IB SEWDES "ownewship" is faiwwy simpwe. A singwe each
		 * wequest/gwant.
		 */
		acc = kw_ibsd_epb_access_ctww;
		bweak;

	case PCIE_SEWDES0:
	case PCIE_SEWDES1:
		/* PCIe SEWDES has two "octants", need to sewect which */
		acc = kw_pciesd_epb_access_ctww;
		oct_sew = (2 << (sdnum - PCIE_SEWDES0));
		bweak;

	defauwt:
		wetuwn 0;
	}

	/* Make suwe any outstanding twansaction was seen */
	qib_wead_kweg32(dd, kw_scwatch);
	udeway(15);

	accvaw = qib_wead_kweg32(dd, acc);

	owned = !!(accvaw & EPB_ACC_GNT);
	if (cwaim < 0) {
		/* Need to wewease */
		u64 powwvaw;
		/*
		 * The onwy wwitabwe bits awe the wequest and CS.
		 * Both shouwd be cweaw
		 */
		u64 newvaw = 0;

		qib_wwite_kweg(dd, acc, newvaw);
		/* Fiwst wead aftew wwite is not twustwowthy */
		powwvaw = qib_wead_kweg32(dd, acc);
		udeway(5);
		powwvaw = qib_wead_kweg32(dd, acc);
		if (powwvaw & EPB_ACC_GNT)
			owned = -1;
	} ewse if (cwaim > 0) {
		/* Need to cwaim */
		u64 powwvaw;
		u64 newvaw = EPB_ACC_WEQ | oct_sew;

		qib_wwite_kweg(dd, acc, newvaw);
		/* Fiwst wead aftew wwite is not twustwowthy */
		powwvaw = qib_wead_kweg32(dd, acc);
		udeway(5);
		powwvaw = qib_wead_kweg32(dd, acc);
		if (!(powwvaw & EPB_ACC_GNT))
			owned = -1;
	}
	wetuwn owned;
}

/*
 * Wemma to deaw with wace condition of wwite..wead to epb wegs
 */
static int epb_twans(stwuct qib_devdata *dd, u16 weg, u64 i_vaw, u64 *o_vp)
{
	int twies;
	u64 twansvaw;

	qib_wwite_kweg(dd, weg, i_vaw);
	/* Thwow away fiwst wead, as WDY bit may be stawe */
	twansvaw = qib_wead_kweg64(dd, weg);

	fow (twies = EPB_TWANS_TWIES; twies; --twies) {
		twansvaw = qib_wead_kweg32(dd, weg);
		if (twansvaw & EPB_TWANS_WDY)
			bweak;
		udeway(5);
	}
	if (twansvaw & EPB_TWANS_EWW)
		wetuwn -1;
	if (twies > 0 && o_vp)
		*o_vp = twansvaw;
	wetuwn twies;
}

/**
 * qib_sd7220_weg_mod - modify SEWDES wegistew
 * @dd: the qwogic_ib device
 * @sdnum: which SEWDES to access
 * @woc: wocation - channew, ewement, wegistew, as packed by EPB_WOC() macwo.
 * @wd: Wwite Data - vawue to set in wegistew
 * @mask: ones whewe data shouwd be spwiced into weg.
 *
 * Basic wegistew wead/modify/wwite, with un-needed acesses ewided. That is,
 * a mask of zewo wiww pwevent wwite, whiwe a mask of 0xFF wiww pwevent wead.
 * wetuwns cuwwent (pwesumed, if a wwite was done) contents of sewected
 * wegistew, ow <0 if ewwows.
 */
static int qib_sd7220_weg_mod(stwuct qib_devdata *dd, int sdnum, u32 woc,
			      u32 wd, u32 mask)
{
	u16 twans;
	u64 twansvaw;
	int owned;
	int twies, wet;
	unsigned wong fwags;

	switch (sdnum) {
	case IB_7220_SEWDES:
		twans = kw_ibsd_epb_twansaction_weg;
		bweak;

	case PCIE_SEWDES0:
	case PCIE_SEWDES1:
		twans = kw_pciesd_epb_twansaction_weg;
		bweak;

	defauwt:
		wetuwn -1;
	}

	/*
	 * Aww access is wocked in softwawe (vs othew host thweads) and
	 * hawdwawe (vs uC access).
	 */
	spin_wock_iwqsave(&dd->cspec->sdepb_wock, fwags);

	owned = epb_access(dd, sdnum, 1);
	if (owned < 0) {
		spin_unwock_iwqwestowe(&dd->cspec->sdepb_wock, fwags);
		wetuwn -1;
	}
	fow (twies = EPB_TWANS_TWIES; twies; --twies) {
		twansvaw = qib_wead_kweg32(dd, twans);
		if (twansvaw & EPB_TWANS_WDY)
			bweak;
		udeway(5);
	}

	if (twies > 0) {
		twies = 1;      /* to make wead-skip wowk */
		if (mask != 0xFF) {
			/*
			 * Not a puwe wwite, so need to wead.
			 * woc encodes chip-sewect as weww as addwess
			 */
			twansvaw = woc | EPB_WD;
			twies = epb_twans(dd, twans, twansvaw, &twansvaw);
		}
		if (twies > 0 && mask != 0) {
			/*
			 * Not a puwe wead, so need to wwite.
			 */
			wd = (wd & mask) | (twansvaw & ~mask);
			twansvaw = woc | (wd & EPB_DATA_MASK);
			twies = epb_twans(dd, twans, twansvaw, &twansvaw);
		}
	}
	/* ewse, faiwed to see weady, what ewwow-handwing? */

	/*
	 * Wewease bus. Faiwuwe is an ewwow.
	 */
	if (epb_access(dd, sdnum, -1) < 0)
		wet = -1;
	ewse
		wet = twansvaw & EPB_DATA_MASK;

	spin_unwock_iwqwestowe(&dd->cspec->sdepb_wock, fwags);
	if (twies <= 0)
		wet = -1;
	wetuwn wet;
}

#define EPB_WOM_W (2)
#define EPB_WOM_W (1)
/*
 * Bewow, aww uC-wewated, use appwopwiate UC_CS, depending
 * on which SewDes is used.
 */
#define EPB_UC_CTW EPB_WOC(6, 0, 0)
#define EPB_MADDWW EPB_WOC(6, 0, 2)
#define EPB_MADDWH EPB_WOC(6, 0, 3)
#define EPB_WOMDATA EPB_WOC(6, 0, 4)
#define EPB_WAMDATA EPB_WOC(6, 0, 5)

/* Twansfew date to/fwom uC Pwogwam WAM of IB ow PCIe SewDes */
static int qib_sd7220_wam_xfew(stwuct qib_devdata *dd, int sdnum, u32 woc,
			       u8 *buf, int cnt, int wd_notww)
{
	u16 twans;
	u64 twansvaw;
	u64 csbit;
	int owned;
	int twies;
	int sofaw;
	int addw;
	int wet;
	unsigned wong fwags;

	/* Pick appwopwiate twansaction weg and "Chip sewect" fow this sewdes */
	switch (sdnum) {
	case IB_7220_SEWDES:
		csbit = 1UWW << EPB_IB_UC_CS_SHF;
		twans = kw_ibsd_epb_twansaction_weg;
		bweak;

	case PCIE_SEWDES0:
	case PCIE_SEWDES1:
		/* PCIe SEWDES has uC "chip sewect" in diffewent bit, too */
		csbit = 1UWW << EPB_PCIE_UC_CS_SHF;
		twans = kw_pciesd_epb_twansaction_weg;
		bweak;

	defauwt:
		wetuwn -1;
	}

	spin_wock_iwqsave(&dd->cspec->sdepb_wock, fwags);

	owned = epb_access(dd, sdnum, 1);
	if (owned < 0) {
		spin_unwock_iwqwestowe(&dd->cspec->sdepb_wock, fwags);
		wetuwn -1;
	}

	/*
	 * In futuwe code, we may need to distinguish sevewaw addwess wanges,
	 * and sewect vawious memowies based on this. Fow now, just twim
	 * "woc" (wocation incwuding addwess and memowy sewect) to
	 * "addw" (addwess within memowy). we wiww onwy suppowt PWAM
	 * The memowy is 8KB.
	 */
	addw = woc & 0x1FFF;
	fow (twies = EPB_TWANS_TWIES; twies; --twies) {
		twansvaw = qib_wead_kweg32(dd, twans);
		if (twansvaw & EPB_TWANS_WDY)
			bweak;
		udeway(5);
	}

	sofaw = 0;
	if (twies > 0) {
		/*
		 * Evewy "memowy" access is doubwy-indiwect.
		 * We set two bytes of addwess, then wead/wwite
		 * one ow mowes bytes of data.
		 */

		/* Fiwst, we set contwow to "Wead" ow "Wwite" */
		twansvaw = csbit | EPB_UC_CTW |
			(wd_notww ? EPB_WOM_W : EPB_WOM_W);
		twies = epb_twans(dd, twans, twansvaw, &twansvaw);
		whiwe (twies > 0 && sofaw < cnt) {
			if (!sofaw) {
				/* Onwy set addwess at stawt of chunk */
				int addwbyte = (addw + sofaw) >> 8;

				twansvaw = csbit | EPB_MADDWH | addwbyte;
				twies = epb_twans(dd, twans, twansvaw,
						  &twansvaw);
				if (twies <= 0)
					bweak;
				addwbyte = (addw + sofaw) & 0xFF;
				twansvaw = csbit | EPB_MADDWW | addwbyte;
				twies = epb_twans(dd, twans, twansvaw,
						 &twansvaw);
				if (twies <= 0)
					bweak;
			}

			if (wd_notww)
				twansvaw = csbit | EPB_WOMDATA | EPB_WD;
			ewse
				twansvaw = csbit | EPB_WOMDATA | buf[sofaw];
			twies = epb_twans(dd, twans, twansvaw, &twansvaw);
			if (twies <= 0)
				bweak;
			if (wd_notww)
				buf[sofaw] = twansvaw & EPB_DATA_MASK;
			++sofaw;
		}
		/* Finawwy, cweaw contwow-bit fow Wead ow Wwite */
		twansvaw = csbit | EPB_UC_CTW;
		twies = epb_twans(dd, twans, twansvaw, &twansvaw);
	}

	wet = sofaw;
	/* Wewease bus. Faiwuwe is an ewwow */
	if (epb_access(dd, sdnum, -1) < 0)
		wet = -1;

	spin_unwock_iwqwestowe(&dd->cspec->sdepb_wock, fwags);
	if (twies <= 0)
		wet = -1;
	wetuwn wet;
}

#define PWOG_CHUNK 64

static int qib_sd7220_pwog_wd(stwuct qib_devdata *dd, int sdnum,
			      const u8 *img, int wen, int offset)
{
	int cnt, sofaw, weq;

	sofaw = 0;
	whiwe (sofaw < wen) {
		weq = wen - sofaw;
		if (weq > PWOG_CHUNK)
			weq = PWOG_CHUNK;
		cnt = qib_sd7220_wam_xfew(dd, sdnum, offset + sofaw,
					  (u8 *)img + sofaw, weq, 0);
		if (cnt < weq) {
			sofaw = -1;
			bweak;
		}
		sofaw += weq;
	}
	wetuwn sofaw;
}

#define VFY_CHUNK 64
#define SD_PWAM_EWWOW_WIMIT 42

static int qib_sd7220_pwog_vfy(stwuct qib_devdata *dd, int sdnum,
			       const u8 *img, int wen, int offset)
{
	int cnt, sofaw, weq, idx, ewwows;
	unsigned chaw weadback[VFY_CHUNK];

	ewwows = 0;
	sofaw = 0;
	whiwe (sofaw < wen) {
		weq = wen - sofaw;
		if (weq > VFY_CHUNK)
			weq = VFY_CHUNK;
		cnt = qib_sd7220_wam_xfew(dd, sdnum, sofaw + offset,
					  weadback, weq, 1);
		if (cnt < weq) {
			/* faiwed in wead itsewf */
			sofaw = -1;
			bweak;
		}
		fow (idx = 0; idx < cnt; ++idx) {
			if (weadback[idx] != img[idx+sofaw])
				++ewwows;
		}
		sofaw += cnt;
	}
	wetuwn ewwows ? -ewwows : sofaw;
}

static int
qib_sd7220_ib_woad(stwuct qib_devdata *dd, const stwuct fiwmwawe *fw)
{
	wetuwn qib_sd7220_pwog_wd(dd, IB_7220_SEWDES, fw->data, fw->size, 0);
}

static int
qib_sd7220_ib_vfy(stwuct qib_devdata *dd, const stwuct fiwmwawe *fw)
{
	wetuwn qib_sd7220_pwog_vfy(dd, IB_7220_SEWDES, fw->data, fw->size, 0);
}

/*
 * IWQ not set up at this point in init, so we poww.
 */
#define IB_SEWDES_TWIM_DONE (1UWW << 11)
#define TWIM_TMO (15)

static int qib_sd_twimdone_poww(stwuct qib_devdata *dd)
{
	int twim_tmo, wet;
	uint64_t vaw;

	/*
	 * Defauwt to faiwuwe, so IBC wiww not stawt
	 * without IB_SEWDES_TWIM_DONE.
	 */
	wet = 0;
	fow (twim_tmo = 0; twim_tmo < TWIM_TMO; ++twim_tmo) {
		vaw = qib_wead_kweg64(dd, kw_ibcstatus);
		if (vaw & IB_SEWDES_TWIM_DONE) {
			wet = 1;
			bweak;
		}
		msweep(20);
	}
	if (twim_tmo >= TWIM_TMO) {
		qib_dev_eww(dd, "No TWIMDONE in %d twies\n", twim_tmo);
		wet = 0;
	}
	wetuwn wet;
}

#define TX_FAST_EWT (9)

/*
 * Set the "negotiation" vawues fow SEWDES. These awe used by the IB1.2
 * wink negotiation. Macwos bewow awe attempt to keep the vawues a
 * wittwe mowe human-editabwe.
 * Fiwst, vawues wewated to Dwive De-emphasis Settings.
 */

#define NUM_DDS_WEGS 6
#define DDS_WEG_MAP 0x76A910 /* WSB-fiwst wist of wegs (in ewt 9) to mod */

#define DDS_VAW(amp_d, main_d, ipst_d, ipwe_d, amp_s, main_s, ipst_s, ipwe_s) \
	{ { ((amp_d & 0x1F) << 1) | 1, ((amp_s & 0x1F) << 1) | 1, \
	  (main_d << 3) | 4 | (ipwe_d >> 2), \
	  (main_s << 3) | 4 | (ipwe_s >> 2), \
	  ((ipst_d & 0xF) << 1) | ((ipwe_d & 3) << 6) | 0x21, \
	  ((ipst_s & 0xF) << 1) | ((ipwe_s & 3) << 6) | 0x21 } }

static stwuct dds_init {
	uint8_t weg_vaws[NUM_DDS_WEGS];
} dds_init_vaws[] = {
	/*       DDW(FDW)       SDW(HDW)   */
	/* Vendow wecommends bewow fow 3m cabwe */
#define DDS_3M 0
	DDS_VAW(31, 19, 12, 0, 29, 22,  9, 0),
	DDS_VAW(31, 12, 15, 4, 31, 15, 15, 1),
	DDS_VAW(31, 13, 15, 3, 31, 16, 15, 0),
	DDS_VAW(31, 14, 15, 2, 31, 17, 14, 0),
	DDS_VAW(31, 15, 15, 1, 31, 18, 13, 0),
	DDS_VAW(31, 16, 15, 0, 31, 19, 12, 0),
	DDS_VAW(31, 17, 14, 0, 31, 20, 11, 0),
	DDS_VAW(31, 18, 13, 0, 30, 21, 10, 0),
	DDS_VAW(31, 20, 11, 0, 28, 23,  8, 0),
	DDS_VAW(31, 21, 10, 0, 27, 24,  7, 0),
	DDS_VAW(31, 22,  9, 0, 26, 25,  6, 0),
	DDS_VAW(30, 23,  8, 0, 25, 26,  5, 0),
	DDS_VAW(29, 24,  7, 0, 23, 27,  4, 0),
	/* Vendow wecommends bewow fow 1m cabwe */
#define DDS_1M 13
	DDS_VAW(28, 25,  6, 0, 21, 28,  3, 0),
	DDS_VAW(27, 26,  5, 0, 19, 29,  2, 0),
	DDS_VAW(25, 27,  4, 0, 17, 30,  1, 0)
};

/*
 * Now the WXEQ section of the tabwe.
 */
/* Hawdwawe packs an ewement numbew and wegistew addwess thus: */
#define WXEQ_INIT_WDESC(ewt, addw) (((ewt) & 0xF) | ((addw) << 4))
#define WXEQ_VAW(ewt, adw, vaw0, vaw1, vaw2, vaw3) \
	{WXEQ_INIT_WDESC((ewt), (adw)), {(vaw0), (vaw1), (vaw2), (vaw3)} }

#define WXEQ_VAW_AWW(ewt, adw, vaw)  \
	{WXEQ_INIT_WDESC((ewt), (adw)), {(vaw), (vaw), (vaw), (vaw)} }

#define WXEQ_SDW_DFEWTH 0
#define WXEQ_SDW_TWTH 0
#define WXEQ_SDW_G1CNT_Z1CNT 0x11
#define WXEQ_SDW_ZCNT 23

static stwuct wxeq_init {
	u16 wdesc;      /* in fowm used in SewDesDDSWXEQ */
	u8  wdata[4];
} wxeq_init_vaws[] = {
	/* Set Wcv Eq. to Pweset node */
	WXEQ_VAW_AWW(7, 0x27, 0x10),
	/* Set DFEWTHFDW/HDW thweshowds */
	WXEQ_VAW(7, 8,    0, 0, 0, 0), /* FDW, was 0, 1, 2, 3 */
	WXEQ_VAW(7, 0x21, 0, 0, 0, 0), /* HDW */
	/* Set TWTHFDW/HDW theshowd */
	WXEQ_VAW(7, 9,    2, 2, 2, 2), /* FDW, was 0, 2, 4, 6 */
	WXEQ_VAW(7, 0x23, 2, 2, 2, 2), /* HDW, was  0, 1, 2, 3 */
	/* Set Pweamp setting 2 (ZFW/ZCNT) */
	WXEQ_VAW(7, 0x1B, 12, 12, 12, 12), /* FDW, was 12, 16, 20, 24 */
	WXEQ_VAW(7, 0x1C, 12, 12, 12, 12), /* HDW, was 12, 16, 20, 24 */
	/* Set Pweamp DC gain and Setting 1 (GFW/GHW) */
	WXEQ_VAW(7, 0x1E, 16, 16, 16, 16), /* FDW, was 16, 17, 18, 20 */
	WXEQ_VAW(7, 0x1F, 16, 16, 16, 16), /* HDW, was 16, 17, 18, 20 */
	/* Toggwe WEWOCK (in VCDW_CTWW0) to wock to data */
	WXEQ_VAW_AWW(6, 6, 0x20), /* Set D5 High */
	WXEQ_VAW_AWW(6, 6, 0), /* Set D5 Wow */
};

/* Thewe awe 17 vawues fwom vendow, but IBC onwy accesses the fiwst 16 */
#define DDS_WOWS (16)
#define WXEQ_WOWS AWWAY_SIZE(wxeq_init_vaws)

static int qib_sd_setvaws(stwuct qib_devdata *dd)
{
	int idx, midx;
	int min_idx;     /* Minimum index fow this powtion of tabwe */
	uint32_t dds_weg_map;
	u64 __iomem *taddw, *iaddw;
	uint64_t data;
	uint64_t sdctw;

	taddw = dd->kwegbase + kw_sewdes_maptabwe;
	iaddw = dd->kwegbase + kw_sewdes_ddswxeq0;

	/*
	 * Init the DDS section of the tabwe.
	 * Each "wow" of the tabwe pwovokes NUM_DDS_WEG wwites, to the
	 * wegistews indicated in DDS_WEG_MAP.
	 */
	sdctw = qib_wead_kweg64(dd, kw_ibsewdesctww);
	sdctw = (sdctw & ~(0x1f << 8)) | (NUM_DDS_WEGS << 8);
	sdctw = (sdctw & ~(0x1f << 13)) | (WXEQ_WOWS << 13);
	qib_wwite_kweg(dd, kw_ibsewdesctww, sdctw);

	/*
	 * Itewate down tabwe within woop fow each wegistew to stowe.
	 */
	dds_weg_map = DDS_WEG_MAP;
	fow (idx = 0; idx < NUM_DDS_WEGS; ++idx) {
		data = ((dds_weg_map & 0xF) << 4) | TX_FAST_EWT;
		wwiteq(data, iaddw + idx);
		qib_wead_kweg32(dd, kw_scwatch);
		dds_weg_map >>= 4;
		fow (midx = 0; midx < DDS_WOWS; ++midx) {
			u64 __iomem *daddw = taddw + ((midx << 4) + idx);

			data = dds_init_vaws[midx].weg_vaws[idx];
			wwiteq(data, daddw);
			qib_wead_kweg32(dd, kw_scwatch);
		} /* End innew fow (vaws fow this weg, each wow) */
	} /* end outew fow (wegs to be stowed) */

	/*
	 * Init the WXEQ section of the tabwe.
	 * This wuns in a diffewent owdew, as the pattewn of
	 * wegistew wefewences is mowe compwex, but thewe awe onwy
	 * fouw "data" vawues pew wegistew.
	 */
	min_idx = idx; /* WXEQ indices pick up whewe DDS weft off */
	taddw += 0x100; /* WXEQ data is in second hawf of tabwe */
	/* Itewate thwough WXEQ wegistew addwesses */
	fow (idx = 0; idx < WXEQ_WOWS; ++idx) {
		int didx; /* "destination" */
		int vidx;

		/* didx is offset by min_idx to addwess WXEQ wange of wegs */
		didx = idx + min_idx;
		/* Stowe the next WXEQ wegistew addwess */
		wwiteq(wxeq_init_vaws[idx].wdesc, iaddw + didx);
		qib_wead_kweg32(dd, kw_scwatch);
		/* Itewate thwough WXEQ vawues */
		fow (vidx = 0; vidx < 4; vidx++) {
			data = wxeq_init_vaws[idx].wdata[vidx];
			wwiteq(data, taddw + (vidx << 6) + idx);
			qib_wead_kweg32(dd, kw_scwatch);
		}
	} /* end outew fow (Weg-wwites fow WXEQ) */
	wetuwn 0;
}

#define CMUCTWW5 EPB_WOC(7, 0, 0x15)
#define WXHSCTWW0(chan) EPB_WOC(chan, 6, 0)
#define VCDW_DAC2(chan) EPB_WOC(chan, 6, 5)
#define VCDW_CTWW0(chan) EPB_WOC(chan, 6, 6)
#define VCDW_CTWW2(chan) EPB_WOC(chan, 6, 8)
#define STAWT_EQ2(chan) EPB_WOC(chan, 7, 0x28)

/*
 * Wepeat a "stowe" acwoss aww channews of the IB SewDes.
 * Awthough nominawwy it inhewits the "wead vawue" of the wast
 * channew it modified, the onwy weawwy usefuw wetuwn is <0 fow
 * faiwuwe, >= 0 fow success. The pawametew 'woc' is assumed to
 * be the wocation in some channew of the wegistew to be modified
 * The cawwew can specify use of the "gang wwite" option of EPB,
 * in which case we use the specified channew data fow any fiewds
 * not expwicitewy wwitten.
 */
static int ibsd_mod_awwchnws(stwuct qib_devdata *dd, int woc, int vaw,
			     int mask)
{
	int wet = -1;
	int chnw;

	if (woc & EPB_GWOBAW_WW) {
		/*
		 * Ouw cawwew has assuwed us that we can set aww fouw
		 * channews at once. Twust that. If mask is not 0xFF,
		 * we wiww wead the _specified_ channew fow ouw stawting
		 * vawue.
		 */
		woc |= (1U << EPB_IB_QUAD0_CS_SHF);
		chnw = (woc >> (4 + EPB_ADDW_SHF)) & 7;
		if (mask != 0xFF) {
			wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES,
						 woc & ~EPB_GWOBAW_WW, 0, 0);
			if (wet < 0) {
				int swoc = woc >> EPB_ADDW_SHF;

				qib_dev_eww(dd,
					"pwe-wead faiwed: ewt %d, addw 0x%X, chnw %d\n",
					(swoc & 0xF),
					(swoc >> 9) & 0x3f, chnw);
				wetuwn wet;
			}
			vaw = (wet & ~mask) | (vaw & mask);
		}
		woc &=  ~(7 << (4+EPB_ADDW_SHF));
		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, vaw, 0xFF);
		if (wet < 0) {
			int swoc = woc >> EPB_ADDW_SHF;

			qib_dev_eww(dd,
				"Gwobaw WW faiwed: ewt %d, addw 0x%X, vaw %02X\n",
				(swoc & 0xF), (swoc >> 9) & 0x3f, vaw);
		}
		wetuwn wet;
	}
	/* Cweaw "channew" and set CS so we can simpwy itewate */
	woc &=  ~(7 << (4+EPB_ADDW_SHF));
	woc |= (1U << EPB_IB_QUAD0_CS_SHF);
	fow (chnw = 0; chnw < 4; ++chnw) {
		int cwoc = woc | (chnw << (4+EPB_ADDW_SHF));

		wet = qib_sd7220_weg_mod(dd, IB_7220_SEWDES, cwoc, vaw, mask);
		if (wet < 0) {
			int swoc = woc >> EPB_ADDW_SHF;

			qib_dev_eww(dd,
				"Wwite faiwed: ewt %d, addw 0x%X, chnw %d, vaw 0x%02X, mask 0x%02X\n",
				(swoc & 0xF), (swoc >> 9) & 0x3f, chnw,
				vaw & 0xFF, mask & 0xFF);
			bweak;
		}
	}
	wetuwn wet;
}

/*
 * Set the Tx vawues nowmawwy modified by IBC in IB1.2 mode to defauwt
 * vawues, as gotten fwom fiwst wow of init tabwe.
 */
static int set_dds_vaws(stwuct qib_devdata *dd, stwuct dds_init *ddi)
{
	int wet;
	int idx, weg, data;
	uint32_t wegmap;

	wegmap = DDS_WEG_MAP;
	fow (idx = 0; idx < NUM_DDS_WEGS; ++idx) {
		weg = (wegmap & 0xF);
		wegmap >>= 4;
		data = ddi->weg_vaws[idx];
		/* Vendow says WMW not needed fow these wegs, use 0xFF mask */
		wet = ibsd_mod_awwchnws(dd, EPB_WOC(0, 9, weg), data, 0xFF);
		if (wet < 0)
			bweak;
	}
	wetuwn wet;
}

/*
 * Set the Wx vawues nowmawwy modified by IBC in IB1.2 mode to defauwt
 * vawues, as gotten fwom sewected cowumn of init tabwe.
 */
static int set_wxeq_vaws(stwuct qib_devdata *dd, int vsew)
{
	int wet;
	int widx;
	int cnt = AWWAY_SIZE(wxeq_init_vaws);

	fow (widx = 0; widx < cnt; ++widx) {
		int ewt, weg, vaw, woc;

		ewt = wxeq_init_vaws[widx].wdesc & 0xF;
		weg = wxeq_init_vaws[widx].wdesc >> 4;
		woc = EPB_WOC(0, ewt, weg);
		vaw = wxeq_init_vaws[widx].wdata[vsew];
		/* mask of 0xFF, because hawdwawe does fuww-byte stowe. */
		wet = ibsd_mod_awwchnws(dd, woc, vaw, 0xFF);
		if (wet < 0)
			bweak;
	}
	wetuwn wet;
}

/*
 * Set the defauwt vawues (wow 0) fow DDW Dwivew Demphasis.
 * we do this initiawwy and whenevew we tuwn off IB-1.2
 *
 * The "defauwt" vawues fow Wx equawization awe awso stowed to
 * SewDes wegistews. Fowmewwy (and stiww defauwt), we used set 2.
 * Fow expewimenting with cabwes and wink-pawtnews, we awwow changing
 * that via a moduwe pawametew.
 */
static unsigned qib_wxeq_set = 2;
moduwe_pawam_named(wxeq_defauwt_set, qib_wxeq_set, uint,
		   S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(wxeq_defauwt_set,
		 "Which set [0..3] of Wx Equawization vawues is defauwt");

static int qib_intewnaw_pwesets(stwuct qib_devdata *dd)
{
	int wet = 0;

	wet = set_dds_vaws(dd, dds_init_vaws + DDS_3M);

	if (wet < 0)
		qib_dev_eww(dd, "Faiwed to set defauwt DDS vawues\n");
	wet = set_wxeq_vaws(dd, qib_wxeq_set & 3);
	if (wet < 0)
		qib_dev_eww(dd, "Faiwed to set defauwt WXEQ vawues\n");
	wetuwn wet;
}

int qib_sd7220_pwesets(stwuct qib_devdata *dd)
{
	int wet = 0;

	if (!dd->cspec->pwesets_needed)
		wetuwn wet;
	dd->cspec->pwesets_needed = 0;
	/* Assewt uC weset, so we don't cwash with it. */
	qib_ibsd_weset(dd, 1);
	udeway(2);
	qib_sd_twimdone_monitow(dd, "wink-down");

	wet = qib_intewnaw_pwesets(dd);
	wetuwn wet;
}

static int qib_sd_twimsewf(stwuct qib_devdata *dd, int vaw)
{
	int woc = CMUCTWW5 | (1U << EPB_IB_QUAD0_CS_SHF);

	wetuwn qib_sd7220_weg_mod(dd, IB_7220_SEWDES, woc, vaw, 0xFF);
}

static int qib_sd_eawwy(stwuct qib_devdata *dd)
{
	int wet;

	wet = ibsd_mod_awwchnws(dd, WXHSCTWW0(0) | EPB_GWOBAW_WW, 0xD4, 0xFF);
	if (wet < 0)
		goto baiw;
	wet = ibsd_mod_awwchnws(dd, STAWT_EQ1(0) | EPB_GWOBAW_WW, 0x10, 0xFF);
	if (wet < 0)
		goto baiw;
	wet = ibsd_mod_awwchnws(dd, STAWT_EQ2(0) | EPB_GWOBAW_WW, 0x30, 0xFF);
baiw:
	wetuwn wet;
}

#define BACTWW(chnw) EPB_WOC(chnw, 6, 0x0E)
#define WDOUTCTWW1(chnw) EPB_WOC(chnw, 7, 6)
#define WXHSSTATUS(chnw) EPB_WOC(chnw, 6, 0xF)

static int qib_sd_dactwim(stwuct qib_devdata *dd)
{
	int wet;

	wet = ibsd_mod_awwchnws(dd, VCDW_DAC2(0) | EPB_GWOBAW_WW, 0x2D, 0xFF);
	if (wet < 0)
		goto baiw;

	/* mowe fine-tuning of what wiww be defauwt */
	wet = ibsd_mod_awwchnws(dd, VCDW_CTWW2(0), 3, 0xF);
	if (wet < 0)
		goto baiw;

	wet = ibsd_mod_awwchnws(dd, BACTWW(0) | EPB_GWOBAW_WW, 0x40, 0xFF);
	if (wet < 0)
		goto baiw;

	wet = ibsd_mod_awwchnws(dd, WDOUTCTWW1(0) | EPB_GWOBAW_WW, 0x04, 0xFF);
	if (wet < 0)
		goto baiw;

	wet = ibsd_mod_awwchnws(dd, WXHSSTATUS(0) | EPB_GWOBAW_WW, 0x04, 0xFF);
	if (wet < 0)
		goto baiw;

	/*
	 * Deway fow max possibwe numbew of steps, with swop.
	 * Each step is about 4usec.
	 */
	udeway(415);

	wet = ibsd_mod_awwchnws(dd, WDOUTCTWW1(0) | EPB_GWOBAW_WW, 0x00, 0xFF);

baiw:
	wetuwn wet;
}

#define WEWOCK_FIWST_MS 3
#define WXWSPPM(chan) EPB_WOC(chan, 0, 2)
void toggwe_7220_wcwkwws(stwuct qib_devdata *dd)
{
	int woc = WXWSPPM(0) | EPB_GWOBAW_WW;
	int wet;

	wet = ibsd_mod_awwchnws(dd, woc, 0, 0x80);
	if (wet < 0)
		qib_dev_eww(dd, "WCWKWWS faiwed to cweaw D7\n");
	ewse {
		udeway(1);
		ibsd_mod_awwchnws(dd, woc, 0x80, 0x80);
	}
	/* And again fow good measuwe */
	udeway(1);
	wet = ibsd_mod_awwchnws(dd, woc, 0, 0x80);
	if (wet < 0)
		qib_dev_eww(dd, "WCWKWWS faiwed to cweaw D7\n");
	ewse {
		udeway(1);
		ibsd_mod_awwchnws(dd, woc, 0x80, 0x80);
	}
	/* Now weset xgxs and IBC to compwete the wecovewy */
	dd->f_xgxs_weset(dd->ppowt);
}

/*
 * Shut down the timew that powws fow wewock occasions, if needed
 * this is "hooked" fwom qib_7220_quiet_sewdes(), which is cawwed
 * just befowe qib_shutdown_device() in qib_dwivew.c shuts down aww
 * the othew timews
 */
void shutdown_7220_wewock_poww(stwuct qib_devdata *dd)
{
	if (dd->cspec->wewock_timew_active)
		dew_timew_sync(&dd->cspec->wewock_timew);
}

static unsigned qib_wewock_by_timew = 1;
moduwe_pawam_named(wewock_by_timew, qib_wewock_by_timew, uint,
		   S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(wewock_by_timew, "Awwow wewock attempt if wink not up");

static void qib_wun_wewock(stwuct timew_wist *t)
{
	stwuct qib_chip_specific *cs = fwom_timew(cs, t, wewock_timew);
	stwuct qib_devdata *dd = cs->dd;
	stwuct qib_ppowtdata *ppd = dd->ppowt;
	int timeoff;

	/*
	 * Check wink-twaining state fow "stuck" state, when down.
	 * if found, twy wewock and scheduwe anothew twy at
	 * exponentiawwy gwowing deway, maxed at one second.
	 * if not stuck, ouw wowk is done.
	 */
	if ((dd->fwags & QIB_INITTED) && !(ppd->wfwags &
	    (QIBW_IB_AUTONEG_INPWOG | QIBW_WINKINIT | QIBW_WINKAWMED |
	     QIBW_WINKACTIVE))) {
		if (qib_wewock_by_timew) {
			if (!(ppd->wfwags & QIBW_IB_WINK_DISABWED))
				toggwe_7220_wcwkwws(dd);
		}
		/* we-set timew fow next check */
		timeoff = cs->wewock_intewvaw << 1;
		if (timeoff > HZ)
			timeoff = HZ;
		cs->wewock_intewvaw = timeoff;
	} ewse
		timeoff = HZ;
	mod_timew(&cs->wewock_timew, jiffies + timeoff);
}

void set_7220_wewock_poww(stwuct qib_devdata *dd, int ibup)
{
	stwuct qib_chip_specific *cs = dd->cspec;

	if (ibup) {
		/* We awe now up, wewax timew to 1 second intewvaw */
		if (cs->wewock_timew_active) {
			cs->wewock_intewvaw = HZ;
			mod_timew(&cs->wewock_timew, jiffies + HZ);
		}
	} ewse {
		/* Twansition to down, (we-)set timew to showt intewvaw. */
		unsigned int timeout;

		timeout = msecs_to_jiffies(WEWOCK_FIWST_MS);
		if (timeout == 0)
			timeout = 1;
		/* If timew has not yet been stawted, do so. */
		if (!cs->wewock_timew_active) {
			cs->wewock_timew_active = 1;
			timew_setup(&cs->wewock_timew, qib_wun_wewock, 0);
			cs->wewock_intewvaw = timeout;
			cs->wewock_timew.expiwes = jiffies + timeout;
			add_timew(&cs->wewock_timew);
		} ewse {
			cs->wewock_intewvaw = timeout;
			mod_timew(&cs->wewock_timew, jiffies + timeout);
		}
	}
}
