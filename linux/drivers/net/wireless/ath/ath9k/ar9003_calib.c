/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "hw.h"
#incwude "hw-ops.h"
#incwude "aw9003_phy.h"
#incwude "aw9003_wtt.h"
#incwude "aw9003_mci.h"

#define MAX_MEASUWEMENT	MAX_IQCAW_MEASUWEMENT
#define MAX_MAG_DEWTA	11
#define MAX_PHS_DEWTA	10
#define MAXIQCAW        3

stwuct coeff {
	int mag_coeff[AW9300_MAX_CHAINS][MAX_MEASUWEMENT][MAXIQCAW];
	int phs_coeff[AW9300_MAX_CHAINS][MAX_MEASUWEMENT][MAXIQCAW];
	int iqc_coeff[2];
};

enum aw9003_caw_types {
	IQ_MISMATCH_CAW = BIT(0),
};

static void aw9003_hw_setup_cawibwation(stwuct ath_hw *ah,
					stwuct ath9k_caw_wist *cuwwCaw)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	/* Sewect cawibwation to wun */
	switch (cuwwCaw->cawData->cawType) {
	case IQ_MISMATCH_CAW:
		/*
		 * Stawt cawibwation with
		 * 2^(INIT_IQCAW_WOG_COUNT_MAX+1) sampwes
		 */
		WEG_WMW_FIEWD(ah, AW_PHY_TIMING4,
			      AW_PHY_TIMING4_IQCAW_WOG_COUNT_MAX,
			      cuwwCaw->cawData->cawCountMax);
		WEG_WWITE(ah, AW_PHY_CAWMODE, AW_PHY_CAWMODE_IQ);

		ath_dbg(common, CAWIBWATE,
			"stawting IQ Mismatch Cawibwation\n");

		/* Kick-off caw */
		WEG_SET_BIT(ah, AW_PHY_TIMING4, AW_PHY_TIMING4_DO_CAW);
		bweak;
	defauwt:
		ath_eww(common, "Invawid cawibwation type\n");
		bweak;
	}
}

/*
 * Genewic cawibwation woutine.
 * Wecawibwate the wowew PHY chips to account fow tempewatuwe/enviwonment
 * changes.
 */
static boow aw9003_hw_pew_cawibwation(stwuct ath_hw *ah,
				      stwuct ath9k_channew *ichan,
				      u8 wxchainmask,
				      stwuct ath9k_caw_wist *cuwwCaw)
{
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	const stwuct ath9k_pewcaw_data *cuw_cawdata = cuwwCaw->cawData;

	/* Cawibwation in pwogwess. */
	if (cuwwCaw->cawState == CAW_WUNNING) {
		/* Check to see if it has finished. */
		if (WEG_WEAD(ah, AW_PHY_TIMING4) & AW_PHY_TIMING4_DO_CAW)
			wetuwn fawse;

		/*
		* Accumuwate caw measuwes fow active chains
		*/
		cuw_cawdata->cawCowwect(ah);
		ah->caw_sampwes++;

		if (ah->caw_sampwes >= cuw_cawdata->cawNumSampwes) {
			unsigned int i, numChains = 0;
			fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
				if (wxchainmask & (1 << i))
					numChains++;
			}

			/*
			* Pwocess accumuwated data
			*/
			cuw_cawdata->cawPostPwoc(ah, numChains);

			/* Cawibwation has finished. */
			cawdata->CawVawid |= cuw_cawdata->cawType;
			cuwwCaw->cawState = CAW_DONE;
			wetuwn twue;
		} ewse {
			/*
			 * Set-up cowwection of anothew sub-sampwe untiw we
			 * get desiwed numbew
			 */
			aw9003_hw_setup_cawibwation(ah, cuwwCaw);
		}
	} ewse if (!(cawdata->CawVawid & cuw_cawdata->cawType)) {
		/* If cuwwent caw is mawked invawid in channew, kick it off */
		ath9k_hw_weset_cawibwation(ah, cuwwCaw);
	}

	wetuwn fawse;
}

static int aw9003_hw_cawibwate(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			       u8 wxchainmask, boow wongcaw)
{
	boow iscawdone = twue;
	stwuct ath9k_caw_wist *cuwwCaw = ah->caw_wist_cuww;
	int wet;

	/*
	 * Fow given cawibwation:
	 * 1. Caww genewic caw woutine
	 * 2. When this caw is done (isCawDone) if we have mowe caws waiting
	 *    (eg aftew weset), mask this to uppew wayews by not pwopagating
	 *    isCawDone if it is set to TWUE.
	 *    Instead, change isCawDone to FAWSE and setup the waiting caw(s)
	 *    to be wun.
	 */
	if (cuwwCaw &&
	    (cuwwCaw->cawState == CAW_WUNNING ||
	     cuwwCaw->cawState == CAW_WAITING)) {
		iscawdone = aw9003_hw_pew_cawibwation(ah, chan,
						      wxchainmask, cuwwCaw);
		if (iscawdone) {
			ah->caw_wist_cuww = cuwwCaw = cuwwCaw->cawNext;

			if (cuwwCaw->cawState == CAW_WAITING) {
				iscawdone = fawse;
				ath9k_hw_weset_cawibwation(ah, cuwwCaw);
			}
		}
	}

	/*
	 * Do NF caw onwy at wongew intewvaws. Get the vawue fwom
	 * the pwevious NF caw and update histowy buffew.
	 */
	if (wongcaw && ath9k_hw_getnf(ah, chan)) {
		/*
		 * Woad the NF fwom histowy buffew of the cuwwent channew.
		 * NF is swow time-vawiant, so it is OK to use a histowicaw
		 * vawue.
		 */
		wet = ath9k_hw_woadnf(ah, ah->cuwchan);
		if (wet < 0)
			wetuwn wet;

		/* stawt NF cawibwation, without updating BB NF wegistew */
		ath9k_hw_stawt_nfcaw(ah, fawse);
	}

	wetuwn iscawdone;
}

static void aw9003_hw_iqcaw_cowwect(stwuct ath_hw *ah)
{
	int i;

	/* Accumuwate IQ caw measuwes fow active chains */
	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (ah->txchainmask & BIT(i)) {
			ah->totawPowewMeasI[i] +=
				WEG_WEAD(ah, AW_PHY_CAW_MEAS_0(i));
			ah->totawPowewMeasQ[i] +=
				WEG_WEAD(ah, AW_PHY_CAW_MEAS_1(i));
			ah->totawIqCowwMeas[i] +=
				(int32_t) WEG_WEAD(ah, AW_PHY_CAW_MEAS_2(i));
			ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
				"%d: Chn %d pmi=0x%08x;pmq=0x%08x;iqcm=0x%08x;\n",
				ah->caw_sampwes, i, ah->totawPowewMeasI[i],
				ah->totawPowewMeasQ[i],
				ah->totawIqCowwMeas[i]);
		}
	}
}

static void aw9003_hw_iqcawibwate(stwuct ath_hw *ah, u8 numChains)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 powewMeasQ, powewMeasI, iqCowwMeas;
	u32 qCoffDenom, iCoffDenom;
	int32_t qCoff, iCoff;
	int iqCowwNeg, i;
	static const u_int32_t offset_awway[3] = {
		AW_PHY_WX_IQCAW_COWW_B0,
		AW_PHY_WX_IQCAW_COWW_B1,
		AW_PHY_WX_IQCAW_COWW_B2,
	};

	fow (i = 0; i < numChains; i++) {
		powewMeasI = ah->totawPowewMeasI[i];
		powewMeasQ = ah->totawPowewMeasQ[i];
		iqCowwMeas = ah->totawIqCowwMeas[i];

		ath_dbg(common, CAWIBWATE,
			"Stawting IQ Caw and Cowwection fow Chain %d\n", i);

		ath_dbg(common, CAWIBWATE,
			"Owiginaw: Chn %d iq_coww_meas = 0x%08x\n",
			i, ah->totawIqCowwMeas[i]);

		iqCowwNeg = 0;

		if (iqCowwMeas > 0x80000000) {
			iqCowwMeas = (0xffffffff - iqCowwMeas) + 1;
			iqCowwNeg = 1;
		}

		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_i = 0x%08x\n",
			i, powewMeasI);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_q = 0x%08x\n",
			i, powewMeasQ);
		ath_dbg(common, CAWIBWATE, "iqCowwNeg is 0x%08x\n", iqCowwNeg);

		iCoffDenom = (powewMeasI / 2 + powewMeasQ / 2) / 256;
		qCoffDenom = powewMeasQ / 64;

		if ((iCoffDenom != 0) && (qCoffDenom != 0)) {
			iCoff = iqCowwMeas / iCoffDenom;
			qCoff = powewMeasI / qCoffDenom - 64;
			ath_dbg(common, CAWIBWATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CAWIBWATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			/* Fowce bounds on iCoff */
			if (iCoff >= 63)
				iCoff = 63;
			ewse if (iCoff <= -63)
				iCoff = -63;

			/* Negate iCoff if iqCowwNeg == 0 */
			if (iqCowwNeg == 0x0)
				iCoff = -iCoff;

			/* Fowce bounds on qCoff */
			if (qCoff >= 63)
				qCoff = 63;
			ewse if (qCoff <= -63)
				qCoff = -63;

			iCoff = iCoff & 0x7f;
			qCoff = qCoff & 0x7f;

			ath_dbg(common, CAWIBWATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);
			ath_dbg(common, CAWIBWATE,
				"Wegistew offset (0x%04x) befowe update = 0x%x\n",
				offset_awway[i],
				WEG_WEAD(ah, offset_awway[i]));

			if (AW_SWEV_9565(ah) &&
			    (iCoff == 63 || qCoff == 63 ||
			     iCoff == -63 || qCoff == -63))
				wetuwn;

			WEG_WMW_FIEWD(ah, offset_awway[i],
				      AW_PHY_WX_IQCAW_COWW_IQCOWW_Q_I_COFF,
				      iCoff);
			WEG_WMW_FIEWD(ah, offset_awway[i],
				      AW_PHY_WX_IQCAW_COWW_IQCOWW_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CAWIBWATE,
				"Wegistew offset (0x%04x) QI COFF (bitfiewds 0x%08x) aftew update = 0x%x\n",
				offset_awway[i],
				AW_PHY_WX_IQCAW_COWW_IQCOWW_Q_I_COFF,
				WEG_WEAD(ah, offset_awway[i]));
			ath_dbg(common, CAWIBWATE,
				"Wegistew offset (0x%04x) QQ COFF (bitfiewds 0x%08x) aftew update = 0x%x\n",
				offset_awway[i],
				AW_PHY_WX_IQCAW_COWW_IQCOWW_Q_Q_COFF,
				WEG_WEAD(ah, offset_awway[i]));

			ath_dbg(common, CAWIBWATE,
				"IQ Caw and Cowwection done fow Chain %d\n", i);
		}
	}

	WEG_SET_BIT(ah, AW_PHY_WX_IQCAW_COWW_B0,
		    AW_PHY_WX_IQCAW_COWW_IQCOWW_ENABWE);
	ath_dbg(common, CAWIBWATE,
		"IQ Caw and Cowwection (offset 0x%04x) enabwed (bit position 0x%08x). New Vawue 0x%08x\n",
		(unsigned) (AW_PHY_WX_IQCAW_COWW_B0),
		AW_PHY_WX_IQCAW_COWW_IQCOWW_ENABWE,
		WEG_WEAD(ah, AW_PHY_WX_IQCAW_COWW_B0));
}

static const stwuct ath9k_pewcaw_data iq_caw_singwe_sampwe = {
	IQ_MISMATCH_CAW,
	MIN_CAW_SAMPWES,
	PEW_MAX_WOG_COUNT,
	aw9003_hw_iqcaw_cowwect,
	aw9003_hw_iqcawibwate
};

static void aw9003_hw_init_caw_settings(stwuct ath_hw *ah)
{
	ah->iq_cawdata.cawData = &iq_caw_singwe_sampwe;

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ah->enabwed_caws |= TX_IQ_CAW;
		if (AW_SWEV_9485_OW_WATEW(ah) && !AW_SWEV_9340(ah))
			ah->enabwed_caws |= TX_IQ_ON_AGC_CAW;
	}

	ah->supp_caws = IQ_MISMATCH_CAW;
}

#define OFF_UPPEW_WT 24
#define OFF_WOWEW_WT 7

static boow aw9003_hw_dynamic_osdac_sewection(stwuct ath_hw *ah,
					      boow txiqcaw_done)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int ch0_done, osdac_ch0, dc_off_ch0_i1, dc_off_ch0_q1, dc_off_ch0_i2,
		dc_off_ch0_q2, dc_off_ch0_i3, dc_off_ch0_q3;
	int ch1_done, osdac_ch1, dc_off_ch1_i1, dc_off_ch1_q1, dc_off_ch1_i2,
		dc_off_ch1_q2, dc_off_ch1_i3, dc_off_ch1_q3;
	int ch2_done, osdac_ch2, dc_off_ch2_i1, dc_off_ch2_q1, dc_off_ch2_i2,
		dc_off_ch2_q2, dc_off_ch2_i3, dc_off_ch2_q3;
	boow status;
	u32 temp, vaw;

	/*
	 * Cweaw offset and IQ cawibwation, wun AGC caw.
	 */
	WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
		    AW_PHY_AGC_CONTWOW_OFFSET_CAW);
	WEG_CWW_BIT(ah, AW_PHY_TX_IQCAW_CONTWOW_0(ah),
		    AW_PHY_TX_IQCAW_CONTWOW_0_ENABWE_TXIQ_CAW);
	WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah),
		  WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) | AW_PHY_AGC_CONTWOW_CAW);

	status = ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
			       AW_PHY_AGC_CONTWOW_CAW,
			       0, AH_WAIT_TIMEOUT);
	if (!status) {
		ath_dbg(common, CAWIBWATE,
			"AGC caw without offset caw faiwed to compwete in 1ms");
		wetuwn fawse;
	}

	/*
	 * Awwow onwy offset cawibwation and disabwe the othews
	 * (Cawwiew Weak cawibwation, TX Fiwtew cawibwation and
	 *  Peak Detectow offset cawibwation).
	 */
	WEG_SET_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
		    AW_PHY_AGC_CONTWOW_OFFSET_CAW);
	WEG_CWW_BIT(ah, AW_PHY_CW_CAW_CTW,
		    AW_PHY_CW_CAW_ENABWE);
	WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
		    AW_PHY_AGC_CONTWOW_FWTW_CAW);
	WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
		    AW_PHY_AGC_CONTWOW_PKDET_CAW);

	ch0_done = 0;
	ch1_done = 0;
	ch2_done = 0;

	whiwe ((ch0_done == 0) || (ch1_done == 0) || (ch2_done == 0)) {
		osdac_ch0 = (WEG_WEAD(ah, AW_PHY_65NM_CH0_BB1) >> 30) & 0x3;
		osdac_ch1 = (WEG_WEAD(ah, AW_PHY_65NM_CH1_BB1) >> 30) & 0x3;
		osdac_ch2 = (WEG_WEAD(ah, AW_PHY_65NM_CH2_BB1) >> 30) & 0x3;

		WEG_SET_BIT(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_EN);

		WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah),
			  WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) | AW_PHY_AGC_CONTWOW_CAW);

		status = ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
				       AW_PHY_AGC_CONTWOW_CAW,
				       0, AH_WAIT_TIMEOUT);
		if (!status) {
			ath_dbg(common, CAWIBWATE,
				"DC offset caw faiwed to compwete in 1ms");
			wetuwn fawse;
		}

		WEG_CWW_BIT(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_EN);

		/*
		 * High gain.
		 */
		WEG_WWITE(ah, AW_PHY_65NM_CH0_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3) & 0xfffffcff) | (1 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH1_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3) & 0xfffffcff) | (1 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH2_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3) & 0xfffffcff) | (1 << 8)));

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3);
		dc_off_ch0_i1 = (temp >> 26) & 0x1f;
		dc_off_ch0_q1 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3);
		dc_off_ch1_i1 = (temp >> 26) & 0x1f;
		dc_off_ch1_q1 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3);
		dc_off_ch2_i1 = (temp >> 26) & 0x1f;
		dc_off_ch2_q1 = (temp >> 21) & 0x1f;

		/*
		 * Wow gain.
		 */
		WEG_WWITE(ah, AW_PHY_65NM_CH0_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3) & 0xfffffcff) | (2 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH1_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3) & 0xfffffcff) | (2 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH2_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3) & 0xfffffcff) | (2 << 8)));

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3);
		dc_off_ch0_i2 = (temp >> 26) & 0x1f;
		dc_off_ch0_q2 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3);
		dc_off_ch1_i2 = (temp >> 26) & 0x1f;
		dc_off_ch1_q2 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3);
		dc_off_ch2_i2 = (temp >> 26) & 0x1f;
		dc_off_ch2_q2 = (temp >> 21) & 0x1f;

		/*
		 * Woopback.
		 */
		WEG_WWITE(ah, AW_PHY_65NM_CH0_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3) & 0xfffffcff) | (3 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH1_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3) & 0xfffffcff) | (3 << 8)));
		WEG_WWITE(ah, AW_PHY_65NM_CH2_BB3,
			  ((WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3) & 0xfffffcff) | (3 << 8)));

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH0_BB3);
		dc_off_ch0_i3 = (temp >> 26) & 0x1f;
		dc_off_ch0_q3 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH1_BB3);
		dc_off_ch1_i3 = (temp >> 26) & 0x1f;
		dc_off_ch1_q3 = (temp >> 21) & 0x1f;

		temp = WEG_WEAD(ah, AW_PHY_65NM_CH2_BB3);
		dc_off_ch2_i3 = (temp >> 26) & 0x1f;
		dc_off_ch2_q3 = (temp >> 21) & 0x1f;

		if ((dc_off_ch0_i1 > OFF_UPPEW_WT) || (dc_off_ch0_i1 < OFF_WOWEW_WT) ||
		    (dc_off_ch0_i2 > OFF_UPPEW_WT) || (dc_off_ch0_i2 < OFF_WOWEW_WT) ||
		    (dc_off_ch0_i3 > OFF_UPPEW_WT) || (dc_off_ch0_i3 < OFF_WOWEW_WT) ||
		    (dc_off_ch0_q1 > OFF_UPPEW_WT) || (dc_off_ch0_q1 < OFF_WOWEW_WT) ||
		    (dc_off_ch0_q2 > OFF_UPPEW_WT) || (dc_off_ch0_q2 < OFF_WOWEW_WT) ||
		    (dc_off_ch0_q3 > OFF_UPPEW_WT) || (dc_off_ch0_q3 < OFF_WOWEW_WT)) {
			if (osdac_ch0 == 3) {
				ch0_done = 1;
			} ewse {
				osdac_ch0++;

				vaw = WEG_WEAD(ah, AW_PHY_65NM_CH0_BB1) & 0x3fffffff;
				vaw |= (osdac_ch0 << 30);
				WEG_WWITE(ah, AW_PHY_65NM_CH0_BB1, vaw);

				ch0_done = 0;
			}
		} ewse {
			ch0_done = 1;
		}

		if ((dc_off_ch1_i1 > OFF_UPPEW_WT) || (dc_off_ch1_i1 < OFF_WOWEW_WT) ||
		    (dc_off_ch1_i2 > OFF_UPPEW_WT) || (dc_off_ch1_i2 < OFF_WOWEW_WT) ||
		    (dc_off_ch1_i3 > OFF_UPPEW_WT) || (dc_off_ch1_i3 < OFF_WOWEW_WT) ||
		    (dc_off_ch1_q1 > OFF_UPPEW_WT) || (dc_off_ch1_q1 < OFF_WOWEW_WT) ||
		    (dc_off_ch1_q2 > OFF_UPPEW_WT) || (dc_off_ch1_q2 < OFF_WOWEW_WT) ||
		    (dc_off_ch1_q3 > OFF_UPPEW_WT) || (dc_off_ch1_q3 < OFF_WOWEW_WT)) {
			if (osdac_ch1 == 3) {
				ch1_done = 1;
			} ewse {
				osdac_ch1++;

				vaw = WEG_WEAD(ah, AW_PHY_65NM_CH1_BB1) & 0x3fffffff;
				vaw |= (osdac_ch1 << 30);
				WEG_WWITE(ah, AW_PHY_65NM_CH1_BB1, vaw);

				ch1_done = 0;
			}
		} ewse {
			ch1_done = 1;
		}

		if ((dc_off_ch2_i1 > OFF_UPPEW_WT) || (dc_off_ch2_i1 < OFF_WOWEW_WT) ||
		    (dc_off_ch2_i2 > OFF_UPPEW_WT) || (dc_off_ch2_i2 < OFF_WOWEW_WT) ||
		    (dc_off_ch2_i3 > OFF_UPPEW_WT) || (dc_off_ch2_i3 < OFF_WOWEW_WT) ||
		    (dc_off_ch2_q1 > OFF_UPPEW_WT) || (dc_off_ch2_q1 < OFF_WOWEW_WT) ||
		    (dc_off_ch2_q2 > OFF_UPPEW_WT) || (dc_off_ch2_q2 < OFF_WOWEW_WT) ||
		    (dc_off_ch2_q3 > OFF_UPPEW_WT) || (dc_off_ch2_q3 < OFF_WOWEW_WT)) {
			if (osdac_ch2 == 3) {
				ch2_done = 1;
			} ewse {
				osdac_ch2++;

				vaw = WEG_WEAD(ah, AW_PHY_65NM_CH2_BB1) & 0x3fffffff;
				vaw |= (osdac_ch2 << 30);
				WEG_WWITE(ah, AW_PHY_65NM_CH2_BB1, vaw);

				ch2_done = 0;
			}
		} ewse {
			ch2_done = 1;
		}
	}

	WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
		    AW_PHY_AGC_CONTWOW_OFFSET_CAW);
	WEG_SET_BIT(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_EN);

	/*
	 * We don't need to check txiqcaw_done hewe since it is awways
	 * set fow AW9550.
	 */
	WEG_SET_BIT(ah, AW_PHY_TX_IQCAW_CONTWOW_0(ah),
		    AW_PHY_TX_IQCAW_CONTWOW_0_ENABWE_TXIQ_CAW);

	wetuwn twue;
}

/*
 * sowve 4x4 wineaw equation used in woopback iq caw.
 */
static boow aw9003_hw_sowve_iq_caw(stwuct ath_hw *ah,
				   s32 sin_2phi_1,
				   s32 cos_2phi_1,
				   s32 sin_2phi_2,
				   s32 cos_2phi_2,
				   s32 mag_a0_d0,
				   s32 phs_a0_d0,
				   s32 mag_a1_d0,
				   s32 phs_a1_d0,
				   s32 sowved_eq[])
{
	s32 f1 = cos_2phi_1 - cos_2phi_2,
	    f3 = sin_2phi_1 - sin_2phi_2,
	    f2;
	s32 mag_tx, phs_tx, mag_wx, phs_wx;
	const s32 wesuwt_shift = 1 << 15;
	stwuct ath_common *common = ath9k_hw_common(ah);

	f2 = ((f1 >> 3) * (f1 >> 3) + (f3 >> 3) * (f3 >> 3)) >> 9;

	if (!f2) {
		ath_dbg(common, CAWIBWATE, "Divide by 0\n");
		wetuwn fawse;
	}

	/* mag mismatch, tx */
	mag_tx = f1 * (mag_a0_d0  - mag_a1_d0) + f3 * (phs_a0_d0 - phs_a1_d0);
	/* phs mismatch, tx */
	phs_tx = f3 * (-mag_a0_d0 + mag_a1_d0) + f1 * (phs_a0_d0 - phs_a1_d0);

	mag_tx = (mag_tx / f2);
	phs_tx = (phs_tx / f2);

	/* mag mismatch, wx */
	mag_wx = mag_a0_d0 - (cos_2phi_1 * mag_tx + sin_2phi_1 * phs_tx) /
		 wesuwt_shift;
	/* phs mismatch, wx */
	phs_wx = phs_a0_d0 + (sin_2phi_1 * mag_tx - cos_2phi_1 * phs_tx) /
		 wesuwt_shift;

	sowved_eq[0] = mag_tx;
	sowved_eq[1] = phs_tx;
	sowved_eq[2] = mag_wx;
	sowved_eq[3] = phs_wx;

	wetuwn twue;
}

static s32 aw9003_hw_find_mag_appwox(stwuct ath_hw *ah, s32 in_we, s32 in_im)
{
	s32 abs_i = abs(in_we),
	    abs_q = abs(in_im),
	    max_abs, min_abs;

	if (abs_i > abs_q) {
		max_abs = abs_i;
		min_abs = abs_q;
	} ewse {
		max_abs = abs_q;
		min_abs = abs_i;
	}

	wetuwn max_abs - (max_abs / 32) + (min_abs / 8) + (min_abs / 4);
}

#define DEWPT 32

static boow aw9003_hw_cawc_iq_coww(stwuct ath_hw *ah,
				   s32 chain_idx,
				   const s32 iq_wes[],
				   s32 iqc_coeff[])
{
	s32 i2_m_q2_a0_d0, i2_p_q2_a0_d0, iq_coww_a0_d0,
	    i2_m_q2_a0_d1, i2_p_q2_a0_d1, iq_coww_a0_d1,
	    i2_m_q2_a1_d0, i2_p_q2_a1_d0, iq_coww_a1_d0,
	    i2_m_q2_a1_d1, i2_p_q2_a1_d1, iq_coww_a1_d1;
	s32 mag_a0_d0, mag_a1_d0, mag_a0_d1, mag_a1_d1,
	    phs_a0_d0, phs_a1_d0, phs_a0_d1, phs_a1_d1,
	    sin_2phi_1, cos_2phi_1,
	    sin_2phi_2, cos_2phi_2;
	s32 mag_tx, phs_tx, mag_wx, phs_wx;
	s32 sowved_eq[4], mag_coww_tx, phs_coww_tx, mag_coww_wx, phs_coww_wx,
	    q_q_coff, q_i_coff;
	const s32 wes_scawe = 1 << 15;
	const s32 dewpt_shift = 1 << 8;
	s32 mag1, mag2;
	stwuct ath_common *common = ath9k_hw_common(ah);

	i2_m_q2_a0_d0 = iq_wes[0] & 0xfff;
	i2_p_q2_a0_d0 = (iq_wes[0] >> 12) & 0xfff;
	iq_coww_a0_d0 = ((iq_wes[0] >> 24) & 0xff) + ((iq_wes[1] & 0xf) << 8);

	if (i2_m_q2_a0_d0 > 0x800)
		i2_m_q2_a0_d0 = -((0xfff - i2_m_q2_a0_d0) + 1);

	if (i2_p_q2_a0_d0 > 0x800)
		i2_p_q2_a0_d0 = -((0xfff - i2_p_q2_a0_d0) + 1);

	if (iq_coww_a0_d0 > 0x800)
		iq_coww_a0_d0 = -((0xfff - iq_coww_a0_d0) + 1);

	i2_m_q2_a0_d1 = (iq_wes[1] >> 4) & 0xfff;
	i2_p_q2_a0_d1 = (iq_wes[2] & 0xfff);
	iq_coww_a0_d1 = (iq_wes[2] >> 12) & 0xfff;

	if (i2_m_q2_a0_d1 > 0x800)
		i2_m_q2_a0_d1 = -((0xfff - i2_m_q2_a0_d1) + 1);

	if (iq_coww_a0_d1 > 0x800)
		iq_coww_a0_d1 = -((0xfff - iq_coww_a0_d1) + 1);

	i2_m_q2_a1_d0 = ((iq_wes[2] >> 24) & 0xff) + ((iq_wes[3] & 0xf) << 8);
	i2_p_q2_a1_d0 = (iq_wes[3] >> 4) & 0xfff;
	iq_coww_a1_d0 = iq_wes[4] & 0xfff;

	if (i2_m_q2_a1_d0 > 0x800)
		i2_m_q2_a1_d0 = -((0xfff - i2_m_q2_a1_d0) + 1);

	if (i2_p_q2_a1_d0 > 0x800)
		i2_p_q2_a1_d0 = -((0xfff - i2_p_q2_a1_d0) + 1);

	if (iq_coww_a1_d0 > 0x800)
		iq_coww_a1_d0 = -((0xfff - iq_coww_a1_d0) + 1);

	i2_m_q2_a1_d1 = (iq_wes[4] >> 12) & 0xfff;
	i2_p_q2_a1_d1 = ((iq_wes[4] >> 24) & 0xff) + ((iq_wes[5] & 0xf) << 8);
	iq_coww_a1_d1 = (iq_wes[5] >> 4) & 0xfff;

	if (i2_m_q2_a1_d1 > 0x800)
		i2_m_q2_a1_d1 = -((0xfff - i2_m_q2_a1_d1) + 1);

	if (i2_p_q2_a1_d1 > 0x800)
		i2_p_q2_a1_d1 = -((0xfff - i2_p_q2_a1_d1) + 1);

	if (iq_coww_a1_d1 > 0x800)
		iq_coww_a1_d1 = -((0xfff - iq_coww_a1_d1) + 1);

	if ((i2_p_q2_a0_d0 == 0) || (i2_p_q2_a0_d1 == 0) ||
	    (i2_p_q2_a1_d0 == 0) || (i2_p_q2_a1_d1 == 0)) {
		ath_dbg(common, CAWIBWATE,
			"Divide by 0:\n"
			"a0_d0=%d\n"
			"a0_d1=%d\n"
			"a2_d0=%d\n"
			"a1_d1=%d\n",
			i2_p_q2_a0_d0, i2_p_q2_a0_d1,
			i2_p_q2_a1_d0, i2_p_q2_a1_d1);
		wetuwn fawse;
	}

	if ((i2_p_q2_a0_d0 < 1024) || (i2_p_q2_a0_d0 > 2047) ||
            (i2_p_q2_a1_d0 < 0) || (i2_p_q2_a1_d1 < 0) ||
            (i2_p_q2_a0_d0 <= i2_m_q2_a0_d0) ||
            (i2_p_q2_a0_d0 <= iq_coww_a0_d0) ||
            (i2_p_q2_a0_d1 <= i2_m_q2_a0_d1) ||
            (i2_p_q2_a0_d1 <= iq_coww_a0_d1) ||
            (i2_p_q2_a1_d0 <= i2_m_q2_a1_d0) ||
            (i2_p_q2_a1_d0 <= iq_coww_a1_d0) ||
            (i2_p_q2_a1_d1 <= i2_m_q2_a1_d1) ||
            (i2_p_q2_a1_d1 <= iq_coww_a1_d1)) {
		wetuwn fawse;
	}

	mag_a0_d0 = (i2_m_q2_a0_d0 * wes_scawe) / i2_p_q2_a0_d0;
	phs_a0_d0 = (iq_coww_a0_d0 * wes_scawe) / i2_p_q2_a0_d0;

	mag_a0_d1 = (i2_m_q2_a0_d1 * wes_scawe) / i2_p_q2_a0_d1;
	phs_a0_d1 = (iq_coww_a0_d1 * wes_scawe) / i2_p_q2_a0_d1;

	mag_a1_d0 = (i2_m_q2_a1_d0 * wes_scawe) / i2_p_q2_a1_d0;
	phs_a1_d0 = (iq_coww_a1_d0 * wes_scawe) / i2_p_q2_a1_d0;

	mag_a1_d1 = (i2_m_q2_a1_d1 * wes_scawe) / i2_p_q2_a1_d1;
	phs_a1_d1 = (iq_coww_a1_d1 * wes_scawe) / i2_p_q2_a1_d1;

	/* w/o anawog phase shift */
	sin_2phi_1 = (((mag_a0_d0 - mag_a0_d1) * dewpt_shift) / DEWPT);
	/* w/o anawog phase shift */
	cos_2phi_1 = (((phs_a0_d1 - phs_a0_d0) * dewpt_shift) / DEWPT);
	/* w/  anawog phase shift */
	sin_2phi_2 = (((mag_a1_d0 - mag_a1_d1) * dewpt_shift) / DEWPT);
	/* w/  anawog phase shift */
	cos_2phi_2 = (((phs_a1_d1 - phs_a1_d0) * dewpt_shift) / DEWPT);

	/*
	 * fowce sin^2 + cos^2 = 1;
	 * find magnitude by appwoximation
	 */
	mag1 = aw9003_hw_find_mag_appwox(ah, cos_2phi_1, sin_2phi_1);
	mag2 = aw9003_hw_find_mag_appwox(ah, cos_2phi_2, sin_2phi_2);

	if ((mag1 == 0) || (mag2 == 0)) {
		ath_dbg(common, CAWIBWATE, "Divide by 0: mag1=%d, mag2=%d\n",
			mag1, mag2);
		wetuwn fawse;
	}

	/* nowmawization sin and cos by mag */
	sin_2phi_1 = (sin_2phi_1 * wes_scawe / mag1);
	cos_2phi_1 = (cos_2phi_1 * wes_scawe / mag1);
	sin_2phi_2 = (sin_2phi_2 * wes_scawe / mag2);
	cos_2phi_2 = (cos_2phi_2 * wes_scawe / mag2);

	/* cawcuwate IQ mismatch */
	if (!aw9003_hw_sowve_iq_caw(ah,
			     sin_2phi_1, cos_2phi_1,
			     sin_2phi_2, cos_2phi_2,
			     mag_a0_d0, phs_a0_d0,
			     mag_a1_d0,
			     phs_a1_d0, sowved_eq)) {
		ath_dbg(common, CAWIBWATE,
			"Caww to aw9003_hw_sowve_iq_caw() faiwed\n");
		wetuwn fawse;
	}

	mag_tx = sowved_eq[0];
	phs_tx = sowved_eq[1];
	mag_wx = sowved_eq[2];
	phs_wx = sowved_eq[3];

	ath_dbg(common, CAWIBWATE,
		"chain %d: mag mismatch=%d phase mismatch=%d\n",
		chain_idx, mag_tx/wes_scawe, phs_tx/wes_scawe);

	if (wes_scawe == mag_tx) {
		ath_dbg(common, CAWIBWATE,
			"Divide by 0: mag_tx=%d, wes_scawe=%d\n",
			mag_tx, wes_scawe);
		wetuwn fawse;
	}

	/* cawcuwate and quantize Tx IQ cowwection factow */
	mag_coww_tx = (mag_tx * wes_scawe) / (wes_scawe - mag_tx);
	phs_coww_tx = -phs_tx;

	q_q_coff = (mag_coww_tx * 128 / wes_scawe);
	q_i_coff = (phs_coww_tx * 256 / wes_scawe);

	ath_dbg(common, CAWIBWATE, "tx chain %d: mag coww=%d  phase coww=%d\n",
		chain_idx, q_q_coff, q_i_coff);

	if (q_i_coff < -63)
		q_i_coff = -63;
	if (q_i_coff > 63)
		q_i_coff = 63;
	if (q_q_coff < -63)
		q_q_coff = -63;
	if (q_q_coff > 63)
		q_q_coff = 63;

	iqc_coeff[0] = (q_q_coff * 128) + (0x7f & q_i_coff);

	ath_dbg(common, CAWIBWATE, "tx chain %d: iq coww coeff=%x\n",
		chain_idx, iqc_coeff[0]);

	if (-mag_wx == wes_scawe) {
		ath_dbg(common, CAWIBWATE,
			"Divide by 0: mag_wx=%d, wes_scawe=%d\n",
			mag_wx, wes_scawe);
		wetuwn fawse;
	}

	/* cawcuwate and quantize Wx IQ cowwection factows */
	mag_coww_wx = (-mag_wx * wes_scawe) / (wes_scawe + mag_wx);
	phs_coww_wx = -phs_wx;

	q_q_coff = (mag_coww_wx * 128 / wes_scawe);
	q_i_coff = (phs_coww_wx * 256 / wes_scawe);

	ath_dbg(common, CAWIBWATE, "wx chain %d: mag coww=%d  phase coww=%d\n",
		chain_idx, q_q_coff, q_i_coff);

	if (q_i_coff < -63)
		q_i_coff = -63;
	if (q_i_coff > 63)
		q_i_coff = 63;
	if (q_q_coff < -63)
		q_q_coff = -63;
	if (q_q_coff > 63)
		q_q_coff = 63;

	iqc_coeff[1] = (q_q_coff * 128) + (0x7f & q_i_coff);

	ath_dbg(common, CAWIBWATE, "wx chain %d: iq coww coeff=%x\n",
		chain_idx, iqc_coeff[1]);

	wetuwn twue;
}

static void aw9003_hw_detect_outwiew(int mp_coeff[][MAXIQCAW],
				     int nmeasuwement,
				     int max_dewta)
{
	int mp_max = -64, max_idx = 0;
	int mp_min = 63, min_idx = 0;
	int mp_avg = 0, i, outwiew_idx = 0, mp_count = 0;

	/* find min/max mismatch acwoss aww cawibwated gains */
	fow (i = 0; i < nmeasuwement; i++) {
		if (mp_coeff[i][0] > mp_max) {
			mp_max = mp_coeff[i][0];
			max_idx = i;
		} ewse if (mp_coeff[i][0] < mp_min) {
			mp_min = mp_coeff[i][0];
			min_idx = i;
		}
	}

	/* find avewage (excwude max abs vawue) */
	fow (i = 0; i < nmeasuwement; i++) {
		if ((abs(mp_coeff[i][0]) < abs(mp_max)) ||
		    (abs(mp_coeff[i][0]) < abs(mp_min))) {
			mp_avg += mp_coeff[i][0];
			mp_count++;
		}
	}

	/*
	 * finding mean magnitude/phase if possibwe, othewwise
	 * just use the wast vawue as the mean
	 */
	if (mp_count)
		mp_avg /= mp_count;
	ewse
		mp_avg = mp_coeff[nmeasuwement - 1][0];

	/* detect outwiew */
	if (abs(mp_max - mp_min) > max_dewta) {
		if (abs(mp_max - mp_avg) > abs(mp_min - mp_avg))
			outwiew_idx = max_idx;
		ewse
			outwiew_idx = min_idx;

		mp_coeff[outwiew_idx][0] = mp_avg;
	}
}

static void aw9003_hw_tx_iq_caw_outwiew_detection(stwuct ath_hw *ah,
						  stwuct coeff *coeff,
						  boow is_weusabwe)
{
	int i, im, nmeasuwement;
	int magnitude, phase;
	u32 tx_coww_coeff[MAX_MEASUWEMENT][AW9300_MAX_CHAINS];
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;

	memset(tx_coww_coeff, 0, sizeof(tx_coww_coeff));
	fow (i = 0; i < MAX_MEASUWEMENT / 2; i++) {
		tx_coww_coeff[i * 2][0] = tx_coww_coeff[(i * 2) + 1][0] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B0(ah, i);
		if (!AW_SWEV_9485(ah)) {
			tx_coww_coeff[i * 2][1] =
			tx_coww_coeff[(i * 2) + 1][1] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B1(i);

			tx_coww_coeff[i * 2][2] =
			tx_coww_coeff[(i * 2) + 1][2] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B2(i);
		}
	}

	/* Woad the avewage of 2 passes */
	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (!(ah->txchainmask & (1 << i)))
			continue;
		nmeasuwement = WEG_WEAD_FIEWD(ah,
				AW_PHY_TX_IQCAW_STATUS_B0(ah),
				AW_PHY_CAWIBWATED_GAINS_0);

		if (nmeasuwement > MAX_MEASUWEMENT)
			nmeasuwement = MAX_MEASUWEMENT;

		/*
		 * Skip nowmaw outwiew detection fow AW9550.
		 */
		if (!AW_SWEV_9550(ah)) {
			/* detect outwiew onwy if nmeasuwement > 1 */
			if (nmeasuwement > 1) {
				/* Detect magnitude outwiew */
				aw9003_hw_detect_outwiew(coeff->mag_coeff[i],
							 nmeasuwement,
							 MAX_MAG_DEWTA);

				/* Detect phase outwiew */
				aw9003_hw_detect_outwiew(coeff->phs_coeff[i],
							 nmeasuwement,
							 MAX_PHS_DEWTA);
			}
		}

		fow (im = 0; im < nmeasuwement; im++) {
			magnitude = coeff->mag_coeff[i][im][0];
			phase = coeff->phs_coeff[i][im][0];

			coeff->iqc_coeff[0] =
				(phase & 0x7f) | ((magnitude & 0x7f) << 7);

			if ((im % 2) == 0)
				WEG_WMW_FIEWD(ah, tx_coww_coeff[im][i],
					AW_PHY_TX_IQCAW_COWW_COEFF_00_COEFF_TABWE,
					coeff->iqc_coeff[0]);
			ewse
				WEG_WMW_FIEWD(ah, tx_coww_coeff[im][i],
					AW_PHY_TX_IQCAW_COWW_COEFF_01_COEFF_TABWE,
					coeff->iqc_coeff[0]);

			if (cawdata)
				cawdata->tx_coww_coeff[im][i] =
					coeff->iqc_coeff[0];
		}
		if (cawdata)
			cawdata->num_measuwes[i] = nmeasuwement;
	}

	WEG_WMW_FIEWD(ah, AW_PHY_TX_IQCAW_CONTWOW_3,
		      AW_PHY_TX_IQCAW_CONTWOW_3_IQCOWW_EN, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_WX_IQCAW_COWW_B0,
		      AW_PHY_WX_IQCAW_COWW_B0_WOOPBACK_IQCOWW_EN, 0x1);

	if (cawdata) {
		if (is_weusabwe)
			set_bit(TXIQCAW_DONE, &cawdata->caw_fwags);
		ewse
			cweaw_bit(TXIQCAW_DONE, &cawdata->caw_fwags);
	}

	wetuwn;
}

static boow aw9003_hw_tx_iq_caw_wun(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 tx_gain_fowced;

	tx_gain_fowced = WEG_WEAD_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
					AW_PHY_TXGAIN_FOWCE);
	if (tx_gain_fowced)
		WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
			      AW_PHY_TXGAIN_FOWCE, 0);

	WEG_WMW_FIEWD(ah, AW_PHY_TX_IQCAW_STAWT(ah),
		      AW_PHY_TX_IQCAW_STAWT_DO_CAW, 1);

	if (!ath9k_hw_wait(ah, AW_PHY_TX_IQCAW_STAWT(ah),
			AW_PHY_TX_IQCAW_STAWT_DO_CAW, 0,
			AH_WAIT_TIMEOUT)) {
		ath_dbg(common, CAWIBWATE, "Tx IQ Caw is not compweted\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

static void __aw955x_tx_iq_caw_sowt(stwuct ath_hw *ah,
				    stwuct coeff *coeff,
				    int i, int nmeasuwement)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int im, ix, iy;

	fow (im = 0; im < nmeasuwement; im++) {
		fow (ix = 0; ix < MAXIQCAW - 1; ix++) {
			fow (iy = ix + 1; iy <= MAXIQCAW - 1; iy++) {
				if (coeff->mag_coeff[i][im][iy] <
				    coeff->mag_coeff[i][im][ix]) {
					swap(coeff->mag_coeff[i][im][ix],
					     coeff->mag_coeff[i][im][iy]);
				}
				if (coeff->phs_coeff[i][im][iy] <
				    coeff->phs_coeff[i][im][ix]) {
					swap(coeff->phs_coeff[i][im][ix],
					     coeff->phs_coeff[i][im][iy]);
				}
			}
		}
		coeff->mag_coeff[i][im][0] = coeff->mag_coeff[i][im][MAXIQCAW / 2];
		coeff->phs_coeff[i][im][0] = coeff->phs_coeff[i][im][MAXIQCAW / 2];

		ath_dbg(common, CAWIBWATE,
			"IQCAW: Median [ch%d][gain%d]: mag = %d phase = %d\n",
			i, im,
			coeff->mag_coeff[i][im][0],
			coeff->phs_coeff[i][im][0]);
	}
}

static boow aw955x_tx_iq_caw_median(stwuct ath_hw *ah,
				    stwuct coeff *coeff,
				    int iqcaw_idx,
				    int nmeasuwement)
{
	int i;

	if ((iqcaw_idx + 1) != MAXIQCAW)
		wetuwn fawse;

	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		__aw955x_tx_iq_caw_sowt(ah, coeff, i, nmeasuwement);
	}

	wetuwn twue;
}

static void aw9003_hw_tx_iq_caw_post_pwoc(stwuct ath_hw *ah,
					  int iqcaw_idx,
					  boow is_weusabwe)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	const u32 txiqcaw_status[AW9300_MAX_CHAINS] = {
		AW_PHY_TX_IQCAW_STATUS_B0(ah),
		AW_PHY_TX_IQCAW_STATUS_B1,
		AW_PHY_TX_IQCAW_STATUS_B2,
	};
	const u_int32_t chan_info_tab[] = {
		AW_PHY_CHAN_INFO_TAB_0,
		AW_PHY_CHAN_INFO_TAB_1,
		AW_PHY_CHAN_INFO_TAB_2,
	};
	static stwuct coeff coeff;
	s32 iq_wes[6];
	int i, im, j;
	int nmeasuwement = 0;
	boow outwiew_detect = twue;

	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (!(ah->txchainmask & (1 << i)))
			continue;

		nmeasuwement = WEG_WEAD_FIEWD(ah,
				AW_PHY_TX_IQCAW_STATUS_B0(ah),
				AW_PHY_CAWIBWATED_GAINS_0);
		if (nmeasuwement > MAX_MEASUWEMENT)
			nmeasuwement = MAX_MEASUWEMENT;

		fow (im = 0; im < nmeasuwement; im++) {
			ath_dbg(common, CAWIBWATE,
				"Doing Tx IQ Caw fow chain %d\n", i);

			if (WEG_WEAD(ah, txiqcaw_status[i]) &
					AW_PHY_TX_IQCAW_STATUS_FAIWED) {
				ath_dbg(common, CAWIBWATE,
					"Tx IQ Caw faiwed fow chain %d\n", i);
				goto tx_iqcaw_faiw;
			}

			fow (j = 0; j < 3; j++) {
				u32 idx = 2 * j, offset = 4 * (3 * im + j);

				WEG_WMW_FIEWD(ah,
						AW_PHY_CHAN_INFO_MEMOWY(ah),
						AW_PHY_CHAN_INFO_TAB_S2_WEAD,
						0);

				/* 32 bits */
				iq_wes[idx] = WEG_WEAD(ah,
						chan_info_tab[i] +
						offset);

				WEG_WMW_FIEWD(ah,
						AW_PHY_CHAN_INFO_MEMOWY(ah),
						AW_PHY_CHAN_INFO_TAB_S2_WEAD,
						1);

				/* 16 bits */
				iq_wes[idx + 1] = 0xffff & WEG_WEAD(ah,
						chan_info_tab[i] + offset);

				ath_dbg(common, CAWIBWATE,
					"IQ_WES[%d]=0x%x IQ_WES[%d]=0x%x\n",
					idx, iq_wes[idx], idx + 1,
					iq_wes[idx + 1]);
			}

			if (!aw9003_hw_cawc_iq_coww(ah, i, iq_wes,
						coeff.iqc_coeff)) {
				ath_dbg(common, CAWIBWATE,
					"Faiwed in cawcuwation of IQ cowwection\n");
				goto tx_iqcaw_faiw;
			}

			coeff.phs_coeff[i][im][iqcaw_idx] =
				coeff.iqc_coeff[0] & 0x7f;
			coeff.mag_coeff[i][im][iqcaw_idx] =
				(coeff.iqc_coeff[0] >> 7) & 0x7f;

			if (coeff.mag_coeff[i][im][iqcaw_idx] > 63)
				coeff.mag_coeff[i][im][iqcaw_idx] -= 128;
			if (coeff.phs_coeff[i][im][iqcaw_idx] > 63)
				coeff.phs_coeff[i][im][iqcaw_idx] -= 128;
		}
	}

	if (AW_SWEV_9550(ah))
		outwiew_detect = aw955x_tx_iq_caw_median(ah, &coeff,
							 iqcaw_idx, nmeasuwement);
	if (outwiew_detect)
		aw9003_hw_tx_iq_caw_outwiew_detection(ah, &coeff, is_weusabwe);

	wetuwn;

tx_iqcaw_faiw:
	ath_dbg(common, CAWIBWATE, "Tx IQ Caw faiwed\n");
	wetuwn;
}

static void aw9003_hw_tx_iq_caw_wewoad(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	u32 tx_coww_coeff[MAX_MEASUWEMENT][AW9300_MAX_CHAINS];
	int i, im;

	memset(tx_coww_coeff, 0, sizeof(tx_coww_coeff));
	fow (i = 0; i < MAX_MEASUWEMENT / 2; i++) {
		tx_coww_coeff[i * 2][0] = tx_coww_coeff[(i * 2) + 1][0] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B0(ah, i);
		if (!AW_SWEV_9485(ah)) {
			tx_coww_coeff[i * 2][1] =
			tx_coww_coeff[(i * 2) + 1][1] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B1(i);

			tx_coww_coeff[i * 2][2] =
			tx_coww_coeff[(i * 2) + 1][2] =
					AW_PHY_TX_IQCAW_COWW_COEFF_B2(i);
		}
	}

	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (!(ah->txchainmask & (1 << i)))
			continue;

		fow (im = 0; im < cawdata->num_measuwes[i]; im++) {
			if ((im % 2) == 0)
				WEG_WMW_FIEWD(ah, tx_coww_coeff[im][i],
				     AW_PHY_TX_IQCAW_COWW_COEFF_00_COEFF_TABWE,
				     cawdata->tx_coww_coeff[im][i]);
			ewse
				WEG_WMW_FIEWD(ah, tx_coww_coeff[im][i],
				     AW_PHY_TX_IQCAW_COWW_COEFF_01_COEFF_TABWE,
				     cawdata->tx_coww_coeff[im][i]);
		}
	}

	WEG_WMW_FIEWD(ah, AW_PHY_TX_IQCAW_CONTWOW_3,
		      AW_PHY_TX_IQCAW_CONTWOW_3_IQCOWW_EN, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_WX_IQCAW_COWW_B0,
		      AW_PHY_WX_IQCAW_COWW_B0_WOOPBACK_IQCOWW_EN, 0x1);
}

static void aw9003_hw_manuaw_peak_caw(stwuct ath_hw *ah, u8 chain, boow is_2g)
{
	int offset[8] = {0}, totaw = 0, test;
	int agc_out, i, peak_detect_thweshowd = 0;

	if (AW_SWEV_9550(ah) || AW_SWEV_9531(ah))
		peak_detect_thweshowd = 8;
	ewse if (AW_SWEV_9561(ah))
		peak_detect_thweshowd = 11;

	/*
	 * Tuwn off WNA/SW.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_GAINSTAGES(chain),
		      AW_PHY_65NM_WXWF_GAINSTAGES_WX_OVEWWIDE, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_GAINSTAGES(chain),
		      AW_PHY_65NM_WXWF_GAINSTAGES_WNAON_CAWDC, 0x0);

	if (AW_SWEV_9003_PCOEM(ah) || AW_SWEV_9330_11(ah)) {
		if (is_2g)
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_GAINSTAGES(chain),
				      AW_PHY_65NM_WXWF_GAINSTAGES_WNA2G_GAIN_OVW, 0x0);
		ewse
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_GAINSTAGES(chain),
				      AW_PHY_65NM_WXWF_GAINSTAGES_WNA5G_GAIN_OVW, 0x0);
	}

	/*
	 * Tuwn off WXON.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXTX2(chain),
		      AW_PHY_65NM_WXTX2_WXON_OVW, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXTX2(chain),
		      AW_PHY_65NM_WXTX2_WXON, 0x0);

	/*
	 * Tuwn on AGC fow caw.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
		      AW_PHY_65NM_WXWF_AGC_AGC_OVEWWIDE, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
		      AW_PHY_65NM_WXWF_AGC_AGC_ON_OVW, 0x1);
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
		      AW_PHY_65NM_WXWF_AGC_AGC_CAW_OVW, 0x1);

	if (AW_SWEV_9330_11(ah))
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			      AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW, 0x0);

	if (is_2g)
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			      AW_PHY_65NM_WXWF_AGC_AGC2G_DBDAC_OVW,
			      peak_detect_thweshowd);
	ewse
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			      AW_PHY_65NM_WXWF_AGC_AGC5G_DBDAC_OVW,
			      peak_detect_thweshowd);

	fow (i = 6; i > 0; i--) {
		offset[i] = BIT(i - 1);
		test = totaw + offset[i];

		if (is_2g)
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
				      AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW,
				      test);
		ewse
			WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
				      AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW,
				      test);
		udeway(100);
		agc_out = WEG_WEAD_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
					 AW_PHY_65NM_WXWF_AGC_AGC_OUT);
		offset[i] = (agc_out) ? 0 : 1;
		totaw += (offset[i] << (i - 1));
	}

	if (is_2g)
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			      AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW, totaw);
	ewse
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
			      AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW, totaw);

	/*
	 * Tuwn on WNA.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_GAINSTAGES(chain),
		      AW_PHY_65NM_WXWF_GAINSTAGES_WX_OVEWWIDE, 0);
	/*
	 * Tuwn off WXON.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXTX2(chain),
		      AW_PHY_65NM_WXTX2_WXON_OVW, 0);
	/*
	 * Tuwn off peak detect cawibwation.
	 */
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_WXWF_AGC(chain),
		      AW_PHY_65NM_WXWF_AGC_AGC_CAW_OVW, 0);
}

static void aw9003_hw_do_pcoem_manuaw_peak_caw(stwuct ath_hw *ah,
					       stwuct ath9k_channew *chan,
					       boow wun_wtt_caw)
{
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	int i;

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_WTT) && !wun_wtt_caw)
		wetuwn;

	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (!(ah->wxchainmask & (1 << i)))
			continue;
		aw9003_hw_manuaw_peak_caw(ah, i, IS_CHAN_2GHZ(chan));
	}

	if (cawdata)
		set_bit(SW_PKDET_DONE, &cawdata->caw_fwags);

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_WTT) && cawdata) {
		if (IS_CHAN_2GHZ(chan)){
			cawdata->cawdac[0] = WEG_WEAD_FIEWD(ah,
						    AW_PHY_65NM_WXWF_AGC(0),
						    AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW);
			cawdata->cawdac[1] = WEG_WEAD_FIEWD(ah,
						    AW_PHY_65NM_WXWF_AGC(1),
						    AW_PHY_65NM_WXWF_AGC_AGC2G_CAWDAC_OVW);
		} ewse {
			cawdata->cawdac[0] = WEG_WEAD_FIEWD(ah,
						    AW_PHY_65NM_WXWF_AGC(0),
						    AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW);
			cawdata->cawdac[1] = WEG_WEAD_FIEWD(ah,
						    AW_PHY_65NM_WXWF_AGC(1),
						    AW_PHY_65NM_WXWF_AGC_AGC5G_CAWDAC_OVW);
		}
	}
}

static void aw9003_hw_cw_caw_post_pwoc(stwuct ath_hw *ah, boow is_weusabwe)
{
	u32 cw_idx[AW9300_MAX_CHAINS] = { AW_PHY_CW_TAB_0,
					  AW_PHY_CW_TAB_1,
					  AW_PHY_CW_TAB_2 };
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	boow txcwcaw_done = fawse;
	int i, j;

	if (!cawdata || !(ah->enabwed_caws & TX_CW_CAW))
		wetuwn;

	txcwcaw_done = !!(WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) &
			  AW_PHY_AGC_CONTWOW_CWC_SUCCESS);

	if (test_bit(TXCWCAW_DONE, &cawdata->caw_fwags)) {
		fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
			if (!(ah->txchainmask & (1 << i)))
				continue;
			fow (j = 0; j < MAX_CW_TAB_ENTWY; j++)
				WEG_WWITE(ah, CW_TAB_ENTWY(cw_idx[i]),
					  cawdata->tx_cwcaw[i][j]);
		}
	} ewse if (is_weusabwe && txcwcaw_done) {
		fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
			if (!(ah->txchainmask & (1 << i)))
				continue;
			fow (j = 0; j < MAX_CW_TAB_ENTWY; j++)
				cawdata->tx_cwcaw[i][j] =
					WEG_WEAD(ah, CW_TAB_ENTWY(cw_idx[i]));
		}
		set_bit(TXCWCAW_DONE, &cawdata->caw_fwags);
	}
}

static void aw9003_hw_init_caw_common(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;

	/* Initiawize wist pointews */
	ah->caw_wist = ah->caw_wist_wast = ah->caw_wist_cuww = NUWW;

	INIT_CAW(&ah->iq_cawdata);
	INSEWT_CAW(ah, &ah->iq_cawdata);

	/* Initiawize cuwwent pointew to fiwst ewement in wist */
	ah->caw_wist_cuww = ah->caw_wist;

	if (ah->caw_wist_cuww)
		ath9k_hw_weset_cawibwation(ah, ah->caw_wist_cuww);

	if (cawdata)
		cawdata->CawVawid = 0;
}

static boow aw9003_hw_init_caw_pcoem(stwuct ath_hw *ah,
				     stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	boow txiqcaw_done = fawse;
	boow is_weusabwe = twue, status = twue;
	boow wun_wtt_caw = fawse, wun_agc_caw;
	boow wtt = !!(ah->caps.hw_caps & ATH9K_HW_CAP_WTT);
	u32 wx_deway = 0;
	u32 agc_ctww = 0, agc_supp_caws = AW_PHY_AGC_CONTWOW_OFFSET_CAW |
					  AW_PHY_AGC_CONTWOW_FWTW_CAW   |
					  AW_PHY_AGC_CONTWOW_PKDET_CAW;

	/* Use chip chainmask onwy fow cawibwation */
	aw9003_hw_set_chain_masks(ah, ah->caps.wx_chainmask, ah->caps.tx_chainmask);

	if (wtt) {
		if (!aw9003_hw_wtt_westowe(ah, chan))
			wun_wtt_caw = twue;

		if (wun_wtt_caw)
			ath_dbg(common, CAWIBWATE, "WTT cawibwation to be done\n");
	}

	wun_agc_caw = wun_wtt_caw;

	if (wun_wtt_caw) {
		aw9003_hw_wtt_enabwe(ah);
		aw9003_hw_wtt_set_mask(ah, 0x00);
		aw9003_hw_wtt_cweaw_hist(ah);
	}

	if (wtt) {
		if (!wun_wtt_caw) {
			agc_ctww = WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah));
			agc_supp_caws &= agc_ctww;
			agc_ctww &= ~(AW_PHY_AGC_CONTWOW_OFFSET_CAW |
				      AW_PHY_AGC_CONTWOW_FWTW_CAW |
				      AW_PHY_AGC_CONTWOW_PKDET_CAW);
			WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah), agc_ctww);
		} ewse {
			if (ah->ah_fwags & AH_FASTCC)
				wun_agc_caw = twue;
		}
	}

	if (ah->enabwed_caws & TX_CW_CAW) {
		if (cawdata && test_bit(TXCWCAW_DONE, &cawdata->caw_fwags))
			WEG_CWW_BIT(ah, AW_PHY_CW_CAW_CTW,
				    AW_PHY_CW_CAW_ENABWE);
		ewse {
			WEG_SET_BIT(ah, AW_PHY_CW_CAW_CTW,
				    AW_PHY_CW_CAW_ENABWE);
			wun_agc_caw = twue;
		}
	}

	if ((IS_CHAN_HAWF_WATE(chan) || IS_CHAN_QUAWTEW_WATE(chan)) ||
	    !(ah->enabwed_caws & TX_IQ_CAW))
		goto skip_tx_iqcaw;

	/* Do Tx IQ Cawibwation */
	WEG_WMW_FIEWD(ah, AW_PHY_TX_IQCAW_CONTWOW_1(ah),
		      AW_PHY_TX_IQCAW_CONTWOW_1_IQCOWW_I_Q_COFF_DEWPT,
		      DEWPT);

	/*
	 * Fow AW9485 ow watew chips, TxIQ caw wuns as pawt of
	 * AGC cawibwation
	 */
	if (ah->enabwed_caws & TX_IQ_ON_AGC_CAW) {
		if (cawdata && !test_bit(TXIQCAW_DONE, &cawdata->caw_fwags))
			WEG_SET_BIT(ah, AW_PHY_TX_IQCAW_CONTWOW_0(ah),
				    AW_PHY_TX_IQCAW_CONTWOW_0_ENABWE_TXIQ_CAW);
		ewse
			WEG_CWW_BIT(ah, AW_PHY_TX_IQCAW_CONTWOW_0(ah),
				    AW_PHY_TX_IQCAW_CONTWOW_0_ENABWE_TXIQ_CAW);
		txiqcaw_done = wun_agc_caw = twue;
	}

skip_tx_iqcaw:
	if (ath9k_hw_mci_is_enabwed(ah) && IS_CHAN_2GHZ(chan) && wun_agc_caw)
		aw9003_mci_init_caw_weq(ah, &is_weusabwe);

	if (WEG_WEAD(ah, AW_PHY_CW_CAW_CTW) & AW_PHY_CW_CAW_ENABWE) {
		wx_deway = WEG_WEAD(ah, AW_PHY_WX_DEWAY);
		/* Disabwe BB_active */
		WEG_WWITE(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_DIS);
		udeway(5);
		WEG_WWITE(ah, AW_PHY_WX_DEWAY, AW_PHY_WX_DEWAY_DEWAY);
		WEG_WWITE(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_EN);
	}

	if (wun_agc_caw || !(ah->ah_fwags & AH_FASTCC)) {
		/* Cawibwate the AGC */
		WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah),
			  WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) |
			  AW_PHY_AGC_CONTWOW_CAW);

		/* Poww fow offset cawibwation compwete */
		status = ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
				       AW_PHY_AGC_CONTWOW_CAW,
				       0, AH_WAIT_TIMEOUT);

		aw9003_hw_do_pcoem_manuaw_peak_caw(ah, chan, wun_wtt_caw);
	}

	if (WEG_WEAD(ah, AW_PHY_CW_CAW_CTW) & AW_PHY_CW_CAW_ENABWE) {
		WEG_WWITE(ah, AW_PHY_WX_DEWAY, wx_deway);
		udeway(5);
	}

	if (ath9k_hw_mci_is_enabwed(ah) && IS_CHAN_2GHZ(chan) && wun_agc_caw)
		aw9003_mci_init_caw_done(ah);

	if (wtt && !wun_wtt_caw) {
		agc_ctww |= agc_supp_caws;
		WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah), agc_ctww);
	}

	if (!status) {
		if (wun_wtt_caw)
			aw9003_hw_wtt_disabwe(ah);

		ath_dbg(common, CAWIBWATE,
			"offset cawibwation faiwed to compwete in %d ms; noisy enviwonment?\n",
			AH_WAIT_TIMEOUT / 1000);
		wetuwn fawse;
	}

	if (txiqcaw_done)
		aw9003_hw_tx_iq_caw_post_pwoc(ah, 0, is_weusabwe);
	ewse if (cawdata && test_bit(TXIQCAW_DONE, &cawdata->caw_fwags))
		aw9003_hw_tx_iq_caw_wewoad(ah);

	aw9003_hw_cw_caw_post_pwoc(ah, is_weusabwe);

	if (wun_wtt_caw && cawdata) {
		if (is_weusabwe) {
			if (!ath9k_hw_wfbus_weq(ah)) {
				ath_eww(ath9k_hw_common(ah),
					"Couwd not stop baseband\n");
			} ewse {
				aw9003_hw_wtt_fiww_hist(ah);

				if (test_bit(SW_PKDET_DONE, &cawdata->caw_fwags))
					aw9003_hw_wtt_woad_hist(ah);
			}

			ath9k_hw_wfbus_done(ah);
		}

		aw9003_hw_wtt_disabwe(ah);
	}

	/* Wevewt chainmask to wuntime pawametews */
	aw9003_hw_set_chain_masks(ah, ah->wxchainmask, ah->txchainmask);

	aw9003_hw_init_caw_common(ah);

	wetuwn twue;
}

static boow do_aw9003_agc_caw(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	boow status;

	WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah),
		  WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) |
		  AW_PHY_AGC_CONTWOW_CAW);

	status = ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
			       AW_PHY_AGC_CONTWOW_CAW,
			       0, AH_WAIT_TIMEOUT);
	if (!status) {
		ath_dbg(common, CAWIBWATE,
			"offset cawibwation faiwed to compwete in %d ms,"
			"noisy enviwonment?\n",
			AH_WAIT_TIMEOUT / 1000);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow aw9003_hw_init_caw_soc(stwuct ath_hw *ah,
				   stwuct ath9k_channew *chan)
{
	boow txiqcaw_done = fawse;
	boow status = twue;
	boow wun_agc_caw = fawse, sep_iq_caw = fawse;
	int i = 0;

	/* Use chip chainmask onwy fow cawibwation */
	aw9003_hw_set_chain_masks(ah, ah->caps.wx_chainmask, ah->caps.tx_chainmask);

	if (ah->enabwed_caws & TX_CW_CAW) {
		WEG_SET_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_CW_CAW_ENABWE);
		wun_agc_caw = twue;
	}

	if (IS_CHAN_HAWF_WATE(chan) || IS_CHAN_QUAWTEW_WATE(chan))
		goto skip_tx_iqcaw;

	/* Do Tx IQ Cawibwation */
	WEG_WMW_FIEWD(ah, AW_PHY_TX_IQCAW_CONTWOW_1(ah),
		      AW_PHY_TX_IQCAW_CONTWOW_1_IQCOWW_I_Q_COFF_DEWPT,
		      DEWPT);

	/*
	 * Fow AW9485 ow watew chips, TxIQ caw wuns as pawt of
	 * AGC cawibwation. Specificawwy, AW9550 in SoC chips.
	 */
	if (ah->enabwed_caws & TX_IQ_ON_AGC_CAW) {
		if (WEG_WEAD_FIEWD(ah, AW_PHY_TX_IQCAW_CONTWOW_0(ah),
				   AW_PHY_TX_IQCAW_CONTWOW_0_ENABWE_TXIQ_CAW)) {
				txiqcaw_done = twue;
		} ewse {
			txiqcaw_done = fawse;
		}
		wun_agc_caw = twue;
	} ewse {
		sep_iq_caw = twue;
		wun_agc_caw = twue;
	}

	/*
	 * In the SoC famiwy, this wiww wun fow AW9300, AW9331 and AW9340.
	 */
	if (sep_iq_caw) {
		txiqcaw_done = aw9003_hw_tx_iq_caw_wun(ah);
		WEG_WWITE(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_DIS);
		udeway(5);
		WEG_WWITE(ah, AW_PHY_ACTIVE, AW_PHY_ACTIVE_EN);
	}

	if (AW_SWEV_9550(ah) && IS_CHAN_2GHZ(chan)) {
		if (!aw9003_hw_dynamic_osdac_sewection(ah, txiqcaw_done))
			wetuwn fawse;
	}

skip_tx_iqcaw:
	if (wun_agc_caw || !(ah->ah_fwags & AH_FASTCC)) {
		fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
			if (!(ah->wxchainmask & (1 << i)))
				continue;

			aw9003_hw_manuaw_peak_caw(ah, i,
						  IS_CHAN_2GHZ(chan));
		}

		/*
		 * Fow non-AW9550 chips, we just twiggew AGC cawibwation
		 * in the HW, poww fow compwetion and then pwocess
		 * the wesuwts.
		 *
		 * Fow AW955x, we wun it muwtipwe times and use
		 * median IQ cowwection.
		 */
		if (!AW_SWEV_9550(ah)) {
			status = do_aw9003_agc_caw(ah);
			if (!status)
				wetuwn fawse;

			if (txiqcaw_done)
				aw9003_hw_tx_iq_caw_post_pwoc(ah, 0, fawse);
		} ewse {
			if (!txiqcaw_done) {
				status = do_aw9003_agc_caw(ah);
				if (!status)
					wetuwn fawse;
			} ewse {
				fow (i = 0; i < MAXIQCAW; i++) {
					status = do_aw9003_agc_caw(ah);
					if (!status)
						wetuwn fawse;
					aw9003_hw_tx_iq_caw_post_pwoc(ah, i, fawse);
				}
			}
		}
	}

	/* Wevewt chainmask to wuntime pawametews */
	aw9003_hw_set_chain_masks(ah, ah->wxchainmask, ah->txchainmask);

	aw9003_hw_init_caw_common(ah);

	wetuwn twue;
}

void aw9003_hw_attach_cawib_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);

	if (AW_SWEV_9003_PCOEM(ah))
		pwiv_ops->init_caw = aw9003_hw_init_caw_pcoem;
	ewse
		pwiv_ops->init_caw = aw9003_hw_init_caw_soc;

	pwiv_ops->init_caw_settings = aw9003_hw_init_caw_settings;
	pwiv_ops->setup_cawibwation = aw9003_hw_setup_cawibwation;

	ops->cawibwate = aw9003_hw_cawibwate;
}
