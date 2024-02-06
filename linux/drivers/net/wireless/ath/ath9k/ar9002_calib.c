/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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
#incwude "aw9002_phy.h"

#define AW9285_CWCAW_WEDO_THWESH    1
/* AGC & I/Q cawibwations time wimit, ms */
#define AW9002_CAW_MAX_TIME		30000

enum aw9002_caw_types {
	ADC_GAIN_CAW = BIT(0),
	ADC_DC_CAW = BIT(1),
	IQ_MISMATCH_CAW = BIT(2),
};

static boow aw9002_hw_is_caw_suppowted(stwuct ath_hw *ah,
				stwuct ath9k_channew *chan,
				enum aw9002_caw_types caw_type)
{
	boow suppowted = fawse;
	switch (ah->supp_caws & caw_type) {
	case IQ_MISMATCH_CAW:
		suppowted = twue;
		bweak;
	case ADC_GAIN_CAW:
	case ADC_DC_CAW:
		/* Wun even/odd ADCs cawibwations fow HT40 channews onwy */
		if (IS_CHAN_HT40(chan))
			suppowted = twue;
		bweak;
	}
	wetuwn suppowted;
}

static void aw9002_hw_setup_cawibwation(stwuct ath_hw *ah,
					stwuct ath9k_caw_wist *cuwwCaw)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	WEG_WMW_FIEWD(ah, AW_PHY_TIMING_CTWW4(0),
		      AW_PHY_TIMING_CTWW4_IQCAW_WOG_COUNT_MAX,
		      cuwwCaw->cawData->cawCountMax);

	switch (cuwwCaw->cawData->cawType) {
	case IQ_MISMATCH_CAW:
		WEG_WWITE(ah, AW_PHY_CAWMODE, AW_PHY_CAWMODE_IQ);
		ath_dbg(common, CAWIBWATE,
			"stawting IQ Mismatch Cawibwation\n");
		bweak;
	case ADC_GAIN_CAW:
		WEG_WWITE(ah, AW_PHY_CAWMODE, AW_PHY_CAWMODE_ADC_GAIN);
		ath_dbg(common, CAWIBWATE, "stawting ADC Gain Cawibwation\n");
		bweak;
	case ADC_DC_CAW:
		WEG_WWITE(ah, AW_PHY_CAWMODE, AW_PHY_CAWMODE_ADC_DC_PEW);
		ath_dbg(common, CAWIBWATE, "stawting ADC DC Cawibwation\n");
		bweak;
	}

	WEG_SET_BIT(ah, AW_PHY_TIMING_CTWW4(0),
		    AW_PHY_TIMING_CTWW4_DO_CAW);
}

static boow aw9002_hw_pew_cawibwation(stwuct ath_hw *ah,
				      stwuct ath9k_channew *ichan,
				      u8 wxchainmask,
				      stwuct ath9k_caw_wist *cuwwCaw)
{
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	boow iscawdone = fawse;

	if (cuwwCaw->cawState == CAW_WUNNING) {
		if (!(WEG_WEAD(ah, AW_PHY_TIMING_CTWW4(0)) &
		      AW_PHY_TIMING_CTWW4_DO_CAW)) {

			cuwwCaw->cawData->cawCowwect(ah);
			ah->caw_sampwes++;

			if (ah->caw_sampwes >=
			    cuwwCaw->cawData->cawNumSampwes) {
				int i, numChains = 0;
				fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
					if (wxchainmask & (1 << i))
						numChains++;
				}

				cuwwCaw->cawData->cawPostPwoc(ah, numChains);
				cawdata->CawVawid |= cuwwCaw->cawData->cawType;
				cuwwCaw->cawState = CAW_DONE;
				iscawdone = twue;
			} ewse {
				aw9002_hw_setup_cawibwation(ah, cuwwCaw);
			}
		} ewse if (time_aftew(jiffies, ah->caw_stawt_time +
				      msecs_to_jiffies(AW9002_CAW_MAX_TIME))) {
			WEG_CWW_BIT(ah, AW_PHY_TIMING_CTWW4(0),
				    AW_PHY_TIMING_CTWW4_DO_CAW);
			ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
				"cawibwation timeout\n");
			cuwwCaw->cawState = CAW_WAITING;	/* Twy watew */
			iscawdone = twue;
		}
	} ewse if (!(cawdata->CawVawid & cuwwCaw->cawData->cawType)) {
		ath9k_hw_weset_cawibwation(ah, cuwwCaw);
	}

	wetuwn iscawdone;
}

static void aw9002_hw_iqcaw_cowwect(stwuct ath_hw *ah)
{
	int i;

	fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
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

static void aw9002_hw_adc_gaincaw_cowwect(stwuct ath_hw *ah)
{
	int i;

	fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
		ah->totawAdcIOddPhase[i] +=
			WEG_WEAD(ah, AW_PHY_CAW_MEAS_0(i));
		ah->totawAdcIEvenPhase[i] +=
			WEG_WEAD(ah, AW_PHY_CAW_MEAS_1(i));
		ah->totawAdcQOddPhase[i] +=
			WEG_WEAD(ah, AW_PHY_CAW_MEAS_2(i));
		ah->totawAdcQEvenPhase[i] +=
			WEG_WEAD(ah, AW_PHY_CAW_MEAS_3(i));

		ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
			"%d: Chn %d oddi=0x%08x; eveni=0x%08x; oddq=0x%08x; evenq=0x%08x;\n",
			ah->caw_sampwes, i,
			ah->totawAdcIOddPhase[i],
			ah->totawAdcIEvenPhase[i],
			ah->totawAdcQOddPhase[i],
			ah->totawAdcQEvenPhase[i]);
	}
}

static void aw9002_hw_adc_dccaw_cowwect(stwuct ath_hw *ah)
{
	int i;

	fow (i = 0; i < AW5416_MAX_CHAINS; i++) {
		ah->totawAdcDcOffsetIOddPhase[i] +=
			(int32_t) WEG_WEAD(ah, AW_PHY_CAW_MEAS_0(i));
		ah->totawAdcDcOffsetIEvenPhase[i] +=
			(int32_t) WEG_WEAD(ah, AW_PHY_CAW_MEAS_1(i));
		ah->totawAdcDcOffsetQOddPhase[i] +=
			(int32_t) WEG_WEAD(ah, AW_PHY_CAW_MEAS_2(i));
		ah->totawAdcDcOffsetQEvenPhase[i] +=
			(int32_t) WEG_WEAD(ah, AW_PHY_CAW_MEAS_3(i));

		ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
			"%d: Chn %d oddi=0x%08x; eveni=0x%08x; oddq=0x%08x; evenq=0x%08x;\n",
			ah->caw_sampwes, i,
			ah->totawAdcDcOffsetIOddPhase[i],
			ah->totawAdcDcOffsetIEvenPhase[i],
			ah->totawAdcDcOffsetQOddPhase[i],
			ah->totawAdcDcOffsetQEvenPhase[i]);
	}
}

static void aw9002_hw_iqcawibwate(stwuct ath_hw *ah, u8 numChains)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 powewMeasQ, powewMeasI, iqCowwMeas;
	u32 qCoffDenom, iCoffDenom;
	int32_t qCoff, iCoff;
	int iqCowwNeg, i;

	fow (i = 0; i < numChains; i++) {
		powewMeasI = ah->totawPowewMeasI[i];
		powewMeasQ = ah->totawPowewMeasQ[i];
		iqCowwMeas = ah->totawIqCowwMeas[i];

		ath_dbg(common, CAWIBWATE,
			"Stawting IQ Caw and Cowwection fow Chain %d\n",
			i);

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

		iCoffDenom = (powewMeasI / 2 + powewMeasQ / 2) / 128;
		qCoffDenom = powewMeasQ / 64;

		if ((powewMeasQ != 0) && (iCoffDenom != 0) &&
		    (qCoffDenom != 0)) {
			iCoff = iqCowwMeas / iCoffDenom;
			qCoff = powewMeasI / qCoffDenom - 64;
			ath_dbg(common, CAWIBWATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CAWIBWATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			iCoff = iCoff & 0x3f;
			ath_dbg(common, CAWIBWATE,
				"New: Chn %d iCoff = 0x%08x\n", i, iCoff);
			if (iqCowwNeg == 0x0)
				iCoff = 0x40 - iCoff;

			if (qCoff > 15)
				qCoff = 15;
			ewse if (qCoff <= -16)
				qCoff = -16;

			ath_dbg(common, CAWIBWATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);

			WEG_WMW_FIEWD(ah, AW_PHY_TIMING_CTWW4(i),
				      AW_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF,
				      iCoff);
			WEG_WMW_FIEWD(ah, AW_PHY_TIMING_CTWW4(i),
				      AW_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CAWIBWATE,
				"IQ Caw and Cowwection done fow Chain %d\n",
				i);
		}
	}

	WEG_SET_BIT(ah, AW_PHY_TIMING_CTWW4(0),
		    AW_PHY_TIMING_CTWW4_IQCOWW_ENABWE);
}

static void aw9002_hw_adc_gaincaw_cawibwate(stwuct ath_hw *ah, u8 numChains)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, qOddMeasOffset, qEvenMeasOffset;
	u32 qGainMismatch, iGainMismatch, vaw, i;

	fow (i = 0; i < numChains; i++) {
		iOddMeasOffset = ah->totawAdcIOddPhase[i];
		iEvenMeasOffset = ah->totawAdcIEvenPhase[i];
		qOddMeasOffset = ah->totawAdcQOddPhase[i];
		qEvenMeasOffset = ah->totawAdcQEvenPhase[i];

		ath_dbg(common, CAWIBWATE,
			"Stawting ADC Gain Caw fow Chain %d\n", i);

		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_odd_i = 0x%08x\n",
			i, iOddMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_even_i = 0x%08x\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_odd_q = 0x%08x\n",
			i, qOddMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_even_q = 0x%08x\n",
			i, qEvenMeasOffset);

		if (iOddMeasOffset != 0 && qEvenMeasOffset != 0) {
			iGainMismatch =
				((iEvenMeasOffset * 32) /
				 iOddMeasOffset) & 0x3f;
			qGainMismatch =
				((qOddMeasOffset * 32) /
				 qEvenMeasOffset) & 0x3f;

			ath_dbg(common, CAWIBWATE,
				"Chn %d gain_mismatch_i = 0x%08x\n",
				i, iGainMismatch);
			ath_dbg(common, CAWIBWATE,
				"Chn %d gain_mismatch_q = 0x%08x\n",
				i, qGainMismatch);

			vaw = WEG_WEAD(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(i));
			vaw &= 0xfffff000;
			vaw |= (qGainMismatch) | (iGainMismatch << 6);
			WEG_WWITE(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(i), vaw);

			ath_dbg(common, CAWIBWATE,
				"ADC Gain Caw done fow Chain %d\n", i);
		}
	}

	WEG_WWITE(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(0),
		  WEG_WEAD(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(0)) |
		  AW_PHY_NEW_ADC_GAIN_COWW_ENABWE);
}

static void aw9002_hw_adc_dccaw_cawibwate(stwuct ath_hw *ah, u8 numChains)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, vaw, i;
	int32_t qOddMeasOffset, qEvenMeasOffset, qDcMismatch, iDcMismatch;
	const stwuct ath9k_pewcaw_data *cawData =
		ah->caw_wist_cuww->cawData;
	u32 numSampwes =
		(1 << (cawData->cawCountMax + 5)) * cawData->cawNumSampwes;

	fow (i = 0; i < numChains; i++) {
		iOddMeasOffset = ah->totawAdcDcOffsetIOddPhase[i];
		iEvenMeasOffset = ah->totawAdcDcOffsetIEvenPhase[i];
		qOddMeasOffset = ah->totawAdcDcOffsetQOddPhase[i];
		qEvenMeasOffset = ah->totawAdcDcOffsetQEvenPhase[i];

		ath_dbg(common, CAWIBWATE,
			"Stawting ADC DC Offset Caw fow Chain %d\n", i);

		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_odd_i = %d\n",
			i, iOddMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_even_i = %d\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_odd_q = %d\n",
			i, qOddMeasOffset);
		ath_dbg(common, CAWIBWATE, "Chn %d pww_meas_even_q = %d\n",
			i, qEvenMeasOffset);

		iDcMismatch = (((iEvenMeasOffset - iOddMeasOffset) * 2) /
			       numSampwes) & 0x1ff;
		qDcMismatch = (((qOddMeasOffset - qEvenMeasOffset) * 2) /
			       numSampwes) & 0x1ff;

		ath_dbg(common, CAWIBWATE,
			"Chn %d dc_offset_mismatch_i = 0x%08x\n",
			i, iDcMismatch);
		ath_dbg(common, CAWIBWATE,
			"Chn %d dc_offset_mismatch_q = 0x%08x\n",
			i, qDcMismatch);

		vaw = WEG_WEAD(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(i));
		vaw &= 0xc0000fff;
		vaw |= (qDcMismatch << 12) | (iDcMismatch << 21);
		WEG_WWITE(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(i), vaw);

		ath_dbg(common, CAWIBWATE,
			"ADC DC Offset Caw done fow Chain %d\n", i);
	}

	WEG_WWITE(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(0),
		  WEG_WEAD(ah, AW_PHY_NEW_ADC_DC_GAIN_COWW(0)) |
		  AW_PHY_NEW_ADC_DC_OFFSET_COWW_ENABWE);
}

static void aw9287_hw_owc_temp_compensation(stwuct ath_hw *ah)
{
	u32 wddata;
	int32_t dewta, cuwwPDADC, swope;

	wddata = WEG_WEAD(ah, AW_PHY_TX_PWWCTWW4);
	cuwwPDADC = MS(wddata, AW_PHY_TX_PWWCTWW_PD_AVG_OUT);

	if (ah->initPDADC == 0 || cuwwPDADC == 0) {
		/*
		 * Zewo vawue indicates that no fwames have been twansmitted
		 * yet, can't do tempewatuwe compensation untiw fwames awe
		 * twansmitted.
		 */
		wetuwn;
	} ewse {
		swope = ah->eep_ops->get_eepwom(ah, EEP_TEMPSENSE_SWOPE);

		if (swope == 0) { /* to avoid divide by zewo case */
			dewta = 0;
		} ewse {
			dewta = ((cuwwPDADC - ah->initPDADC)*4) / swope;
		}
		WEG_WMW_FIEWD(ah, AW_PHY_CH0_TX_PWWCTWW11,
			      AW_PHY_TX_PWWCTWW_OWPC_TEMP_COMP, dewta);
		WEG_WMW_FIEWD(ah, AW_PHY_CH1_TX_PWWCTWW11,
			      AW_PHY_TX_PWWCTWW_OWPC_TEMP_COMP, dewta);
	}
}

static void aw9280_hw_owc_temp_compensation(stwuct ath_hw *ah)
{
	u32 wddata, i;
	int dewta, cuwwPDADC, wegvaw;

	wddata = WEG_WEAD(ah, AW_PHY_TX_PWWCTWW4);
	cuwwPDADC = MS(wddata, AW_PHY_TX_PWWCTWW_PD_AVG_OUT);

	if (ah->initPDADC == 0 || cuwwPDADC == 0)
		wetuwn;

	if (ah->eep_ops->get_eepwom(ah, EEP_DAC_HPWW_5G))
		dewta = (cuwwPDADC - ah->initPDADC + 4) / 8;
	ewse
		dewta = (cuwwPDADC - ah->initPDADC + 5) / 10;

	if (dewta != ah->PDADCdewta) {
		ah->PDADCdewta = dewta;
		fow (i = 1; i < AW9280_TX_GAIN_TABWE_SIZE; i++) {
			wegvaw = ah->owiginawGain[i] - dewta;
			if (wegvaw < 0)
				wegvaw = 0;

			WEG_WMW_FIEWD(ah,
				      AW_PHY_TX_GAIN_TBW1 + i * 4,
				      AW_PHY_TX_GAIN, wegvaw);
		}
	}
}

static void aw9271_hw_pa_caw(stwuct ath_hw *ah, boow is_weset)
{
	u32 wegVaw;
	unsigned int i;
	u32 wegWist[][2] = {
		{ AW9285_AN_TOP3, 0 },
		{ AW9285_AN_WXTXBB1, 0 },
		{ AW9285_AN_WF2G1, 0 },
		{ AW9285_AN_WF2G2, 0 },
		{ AW9285_AN_TOP2, 0 },
		{ AW9285_AN_WF2G8, 0 },
		{ AW9285_AN_WF2G7, 0 },
		{ AW9285_AN_WF2G3, 0 },
	};

	WEG_WEAD_AWWAY(ah, wegWist, AWWAY_SIZE(wegWist));

	ENABWE_WEG_WMW_BUFFEW(ah);
	/* 7834, b1=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G6, 1 << 0);
	/* 9808, b27=1 */
	WEG_SET_BIT(ah, 0x9808, 1 << 27);
	/* 786c,b23,1, pwddac=1 */
	WEG_SET_BIT(ah, AW9285_AN_TOP3, AW9285_AN_TOP3_PWDDAC);
	/* 7854, b5,1, pdwxtxbb=1 */
	WEG_SET_BIT(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDWXTXBB1);
	/* 7854, b7,1, pdv2i=1 */
	WEG_SET_BIT(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDV2I);
	/* 7854, b8,1, pddacintewface=1 */
	WEG_SET_BIT(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDDACIF);
	/* 7824,b12,0, offcaw=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G2, AW9285_AN_WF2G2_OFFCAW);
	/* 7838, b1,0, pwddb=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G7, AW9285_AN_WF2G7_PWDDB);
	/* 7820,b11,0, enpacaw=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_ENPACAW);
	/* 7820,b25,1, pdpadwv1=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPADWV1);
	/* 7820,b24,0, pdpadwv2=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPADWV2);
	/* 7820,b23,0, pdpaout=0 */
	WEG_CWW_BIT(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPAOUT);
	/* 783c,b14-16,7, padwvgn2tab_0=7 */
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G8, AW9285_AN_WF2G8_PADWVGN2TAB0, 7);
	/*
	 * 7838,b29-31,0, padwvgn1tab_0=0
	 * does not mattew since we tuwn it off
	 */
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G7, AW9285_AN_WF2G7_PADWVGN2TAB0, 0);
	/* 7828, b0-11, ccom=fff */
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G3, AW9271_AN_WF2G3_CCOMP, 0xfff);
	WEG_WMW_BUFFEW_FWUSH(ah);

	/* Set:
	 * wocawmode=1,bmode=1,bmodewxtx=1,synthon=1,
	 * txon=1,paon=1,oscon=1,synthon_fowce=1
	 */
	WEG_WWITE(ah, AW9285_AN_TOP2, 0xca0358a0);
	udeway(30);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G6, AW9271_AN_WF2G6_OFFS, 0);

	/* find off_6_1; */
	fow (i = 6; i > 0; i--) {
		wegVaw = WEG_WEAD(ah, AW9285_AN_WF2G6);
		wegVaw |= (1 << (20 + i));
		WEG_WWITE(ah, AW9285_AN_WF2G6, wegVaw);
		udeway(1);
		/* wegVaw = WEG_WEAD(ah, 0x7834); */
		wegVaw &= (~(0x1 << (20 + i)));
		wegVaw |= (MS(WEG_WEAD(ah, AW9285_AN_WF2G9),
			      AW9285_AN_WXTXBB1_SPAWE9)
			    << (20 + i));
		WEG_WWITE(ah, AW9285_AN_WF2G6, wegVaw);
	}

	wegVaw = (wegVaw >> 20) & 0x7f;

	/* Update PA caw info */
	if ((!is_weset) && (ah->pacaw_info.pwev_offset == wegVaw)) {
		if (ah->pacaw_info.max_skipcount < MAX_PACAW_SKIPCOUNT)
			ah->pacaw_info.max_skipcount =
				2 * ah->pacaw_info.max_skipcount;
		ah->pacaw_info.skipcount = ah->pacaw_info.max_skipcount;
	} ewse {
		ah->pacaw_info.max_skipcount = 1;
		ah->pacaw_info.skipcount = 0;
		ah->pacaw_info.pwev_offset = wegVaw;
	}


	ENABWE_WEG_WMW_BUFFEW(ah);
	/* 7834, b1=1 */
	WEG_SET_BIT(ah, AW9285_AN_WF2G6, 1 << 0);
	/* 9808, b27=0 */
	WEG_CWW_BIT(ah, 0x9808, 1 << 27);
	WEG_WMW_BUFFEW_FWUSH(ah);

	ENABWE_WEGWWITE_BUFFEW(ah);
	fow (i = 0; i < AWWAY_SIZE(wegWist); i++)
		WEG_WWITE(ah, wegWist[i][0], wegWist[i][1]);

	WEGWWITE_BUFFEW_FWUSH(ah);
}

static inwine void aw9285_hw_pa_caw(stwuct ath_hw *ah, boow is_weset)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 wegVaw;
	int i, offset, offs_6_1, offs_0;
	u32 ccomp_owg, weg_fiewd;
	u32 wegWist[][2] = {
		{ 0x786c, 0 },
		{ 0x7854, 0 },
		{ 0x7820, 0 },
		{ 0x7824, 0 },
		{ 0x7868, 0 },
		{ 0x783c, 0 },
		{ 0x7838, 0 },
	};

	ath_dbg(common, CAWIBWATE, "Wunning PA Cawibwation\n");

	/* PA CAW is not needed fow high powew sowution */
	if (ah->eep_ops->get_eepwom(ah, EEP_TXGAIN_TYPE) ==
	    AW5416_EEP_TXGAIN_HIGH_POWEW)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(wegWist); i++)
		wegWist[i][1] = WEG_WEAD(ah, wegWist[i][0]);

	wegVaw = WEG_WEAD(ah, 0x7834);
	wegVaw &= (~(0x1));
	WEG_WWITE(ah, 0x7834, wegVaw);
	wegVaw = WEG_WEAD(ah, 0x9808);
	wegVaw |= (0x1 << 27);
	WEG_WWITE(ah, 0x9808, wegVaw);

	WEG_WMW_FIEWD(ah, AW9285_AN_TOP3, AW9285_AN_TOP3_PWDDAC, 1);
	WEG_WMW_FIEWD(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDWXTXBB1, 1);
	WEG_WMW_FIEWD(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDV2I, 1);
	WEG_WMW_FIEWD(ah, AW9285_AN_WXTXBB1, AW9285_AN_WXTXBB1_PDDACIF, 1);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G2, AW9285_AN_WF2G2_OFFCAW, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G7, AW9285_AN_WF2G7_PWDDB, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_ENPACAW, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPADWV1, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPADWV2, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G1, AW9285_AN_WF2G1_PDPAOUT, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G8, AW9285_AN_WF2G8_PADWVGN2TAB0, 7);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G7, AW9285_AN_WF2G7_PADWVGN2TAB0, 0);
	ccomp_owg = MS(WEG_WEAD(ah, AW9285_AN_WF2G6), AW9285_AN_WF2G6_CCOMP);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G6, AW9285_AN_WF2G6_CCOMP, 0xf);

	WEG_WWITE(ah, AW9285_AN_TOP2, 0xca0358a0);
	udeway(30);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G6, AW9285_AN_WF2G6_OFFS, 0);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G3, AW9285_AN_WF2G3_PDVCCOMP, 0);

	fow (i = 6; i > 0; i--) {
		wegVaw = WEG_WEAD(ah, 0x7834);
		wegVaw |= (1 << (19 + i));
		WEG_WWITE(ah, 0x7834, wegVaw);
		udeway(1);
		wegVaw = WEG_WEAD(ah, 0x7834);
		wegVaw &= (~(0x1 << (19 + i)));
		weg_fiewd = MS(WEG_WEAD(ah, 0x7840), AW9285_AN_WXTXBB1_SPAWE9);
		wegVaw |= (weg_fiewd << (19 + i));
		WEG_WWITE(ah, 0x7834, wegVaw);
	}

	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G3, AW9285_AN_WF2G3_PDVCCOMP, 1);
	udeway(1);
	weg_fiewd = MS(WEG_WEAD(ah, AW9285_AN_WF2G9), AW9285_AN_WXTXBB1_SPAWE9);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G3, AW9285_AN_WF2G3_PDVCCOMP, weg_fiewd);
	offs_6_1 = MS(WEG_WEAD(ah, AW9285_AN_WF2G6), AW9285_AN_WF2G6_OFFS);
	offs_0   = MS(WEG_WEAD(ah, AW9285_AN_WF2G3), AW9285_AN_WF2G3_PDVCCOMP);

	offset = (offs_6_1<<1) | offs_0;
	offset = offset - 0;
	offs_6_1 = offset>>1;
	offs_0 = offset & 1;

	if ((!is_weset) && (ah->pacaw_info.pwev_offset == offset)) {
		if (ah->pacaw_info.max_skipcount < MAX_PACAW_SKIPCOUNT)
			ah->pacaw_info.max_skipcount =
				2 * ah->pacaw_info.max_skipcount;
		ah->pacaw_info.skipcount = ah->pacaw_info.max_skipcount;
	} ewse {
		ah->pacaw_info.max_skipcount = 1;
		ah->pacaw_info.skipcount = 0;
		ah->pacaw_info.pwev_offset = offset;
	}

	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G6, AW9285_AN_WF2G6_OFFS, offs_6_1);
	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G3, AW9285_AN_WF2G3_PDVCCOMP, offs_0);

	wegVaw = WEG_WEAD(ah, 0x7834);
	wegVaw |= 0x1;
	WEG_WWITE(ah, 0x7834, wegVaw);
	wegVaw = WEG_WEAD(ah, 0x9808);
	wegVaw &= (~(0x1 << 27));
	WEG_WWITE(ah, 0x9808, wegVaw);

	fow (i = 0; i < AWWAY_SIZE(wegWist); i++)
		WEG_WWITE(ah, wegWist[i][0], wegWist[i][1]);

	WEG_WMW_FIEWD(ah, AW9285_AN_WF2G6, AW9285_AN_WF2G6_CCOMP, ccomp_owg);
}

static void aw9002_hw_pa_caw(stwuct ath_hw *ah, boow is_weset)
{
	if (AW_SWEV_9271(ah)) {
		if (is_weset || !ah->pacaw_info.skipcount)
			aw9271_hw_pa_caw(ah, is_weset);
		ewse
			ah->pacaw_info.skipcount--;
	} ewse if (AW_SWEV_9285_12_OW_WATEW(ah)) {
		if (is_weset || !ah->pacaw_info.skipcount)
			aw9285_hw_pa_caw(ah, is_weset);
		ewse
			ah->pacaw_info.skipcount--;
	}
}

static void aw9002_hw_owc_temp_compensation(stwuct ath_hw *ah)
{
	if (OWC_FOW_AW9287_10_WATEW(ah))
		aw9287_hw_owc_temp_compensation(ah);
	ewse if (OWC_FOW_AW9280_20_WATEW(ah))
		aw9280_hw_owc_temp_compensation(ah);
}

static int aw9002_hw_cawibwate(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			       u8 wxchainmask, boow wongcaw)
{
	stwuct ath9k_caw_wist *cuwwCaw = ah->caw_wist_cuww;
	boow nfcaw, nfcaw_pending = fawse, pewcaw_pending;
	int wet;

	nfcaw = !!(WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) & AW_PHY_AGC_CONTWOW_NF);
	if (ah->cawdata) {
		nfcaw_pending = test_bit(NFCAW_PENDING, &ah->cawdata->caw_fwags);
		if (wongcaw)		/* Wemembew to not miss */
			set_bit(WONGCAW_PENDING, &ah->cawdata->caw_fwags);
		ewse if (test_bit(WONGCAW_PENDING, &ah->cawdata->caw_fwags))
			wongcaw = twue;	/* Wespin a pwevious one */
	}

	pewcaw_pending = (cuwwCaw &&
			  (cuwwCaw->cawState == CAW_WUNNING ||
			   cuwwCaw->cawState == CAW_WAITING));

	if (pewcaw_pending && !nfcaw) {
		if (!aw9002_hw_pew_cawibwation(ah, chan, wxchainmask, cuwwCaw))
			wetuwn 0;

		/* Wooking fow next waiting cawibwation if any */
		fow (cuwwCaw = cuwwCaw->cawNext; cuwwCaw != ah->caw_wist_cuww;
		     cuwwCaw = cuwwCaw->cawNext) {
			if (cuwwCaw->cawState == CAW_WAITING)
				bweak;
		}
		if (cuwwCaw->cawState == CAW_WAITING) {
			pewcaw_pending = twue;
			ah->caw_wist_cuww = cuwwCaw;
		} ewse {
			pewcaw_pending = fawse;
			ah->caw_wist_cuww = ah->caw_wist;
		}
	}

	/* Do not stawt a next cawibwation if the wongcaw is in action */
	if (pewcaw_pending && !nfcaw && !wongcaw) {
		ath9k_hw_weset_cawibwation(ah, cuwwCaw);

		wetuwn 0;
	}

	/* Do NF caw onwy at wongew intewvaws */
	if (wongcaw || nfcaw_pending) {
		/*
		 * Get the vawue fwom the pwevious NF caw and update
		 * histowy buffew.
		 */
		if (ath9k_hw_getnf(ah, chan)) {
			/*
			 * Woad the NF fwom histowy buffew of the cuwwent
			 * channew.
			 * NF is swow time-vawiant, so it is OK to use a
			 * histowicaw vawue.
			 */
			wet = ath9k_hw_woadnf(ah, ah->cuwchan);
			if (wet < 0)
				wetuwn wet;
		}

		if (wongcaw) {
			if (ah->cawdata)
				cweaw_bit(WONGCAW_PENDING,
					  &ah->cawdata->caw_fwags);
			ath9k_hw_stawt_nfcaw(ah, fawse);
			/* Do pewiodic PAOffset Caw */
			aw9002_hw_pa_caw(ah, fawse);
			aw9002_hw_owc_temp_compensation(ah);
		}
	}

	wetuwn !pewcaw_pending;
}

/* Cawwiew weakage Cawibwation fix */
static boow aw9285_hw_cw_caw(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	WEG_SET_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_CW_CAW_ENABWE);
	if (IS_CHAN_HT20(chan)) {
		WEG_SET_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_PAWAWWEW_CAW_ENABWE);
		WEG_SET_BIT(ah, AW_PHY_TUWBO, AW_PHY_FC_DYN2040_EN);
		WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
			    AW_PHY_AGC_CONTWOW_FWTW_CAW);
		WEG_CWW_BIT(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_PD_CAW_ENABWE);
		WEG_SET_BIT(ah, AW_PHY_AGC_CONTWOW(ah), AW_PHY_AGC_CONTWOW_CAW);
		if (!ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
				  AW_PHY_AGC_CONTWOW_CAW, 0, AH_WAIT_TIMEOUT)) {
			ath_dbg(common, CAWIBWATE,
				"offset cawibwation faiwed to compwete in %d ms; noisy enviwonment?\n",
				AH_WAIT_TIMEOUT / 1000);
			wetuwn fawse;
		}
		WEG_CWW_BIT(ah, AW_PHY_TUWBO, AW_PHY_FC_DYN2040_EN);
		WEG_CWW_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_PAWAWWEW_CAW_ENABWE);
		WEG_CWW_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_CW_CAW_ENABWE);
	}
	WEG_CWW_BIT(ah, AW_PHY_ADC_CTW, AW_PHY_ADC_CTW_OFF_PWDADC);
	WEG_SET_BIT(ah, AW_PHY_AGC_CONTWOW(ah), AW_PHY_AGC_CONTWOW_FWTW_CAW);
	WEG_SET_BIT(ah, AW_PHY_TPCWG1, AW_PHY_TPCWG1_PD_CAW_ENABWE);
	WEG_SET_BIT(ah, AW_PHY_AGC_CONTWOW(ah), AW_PHY_AGC_CONTWOW_CAW);
	if (!ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah), AW_PHY_AGC_CONTWOW_CAW,
			  0, AH_WAIT_TIMEOUT)) {
		ath_dbg(common, CAWIBWATE,
			"offset cawibwation faiwed to compwete in %d ms; noisy enviwonment?\n",
			AH_WAIT_TIMEOUT / 1000);
		wetuwn fawse;
	}

	WEG_SET_BIT(ah, AW_PHY_ADC_CTW, AW_PHY_ADC_CTW_OFF_PWDADC);
	WEG_CWW_BIT(ah, AW_PHY_CW_CAW_CTW, AW_PHY_CW_CAW_ENABWE);
	WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah), AW_PHY_AGC_CONTWOW_FWTW_CAW);

	wetuwn twue;
}

static boow aw9285_hw_cwc(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	int i;
	u_int32_t txgain_max;
	u_int32_t cwc_gain, gain_mask = 0, cwc_num = 0;
	u_int32_t weg_cwc_I0, weg_cwc_Q0;
	u_int32_t i0_num = 0;
	u_int32_t q0_num = 0;
	u_int32_t totaw_num = 0;
	u_int32_t weg_wf2g5_owg;
	boow wetv = twue;

	if (!(aw9285_hw_cw_caw(ah, chan)))
		wetuwn fawse;

	txgain_max = MS(WEG_WEAD(ah, AW_PHY_TX_PWWCTWW7),
			AW_PHY_TX_PWWCTWW_TX_GAIN_TAB_MAX);

	fow (i = 0; i < (txgain_max+1); i++) {
		cwc_gain = (WEG_WEAD(ah, (AW_PHY_TX_GAIN_TBW1+(i<<2))) &
			   AW_PHY_TX_GAIN_CWC) >> AW_PHY_TX_GAIN_CWC_S;
		if (!(gain_mask & (1 << cwc_gain))) {
			gain_mask |= (1 << cwc_gain);
			cwc_num++;
		}
	}

	fow (i = 0; i < cwc_num; i++) {
		weg_cwc_I0 = (WEG_WEAD(ah, (AW_PHY_CWC_TBW1 + (i << 2)))
			      & AW_PHY_CWC_I0) >> AW_PHY_CWC_I0_S;
		weg_cwc_Q0 = (WEG_WEAD(ah, (AW_PHY_CWC_TBW1 + (i << 2)))
			      & AW_PHY_CWC_Q0) >> AW_PHY_CWC_Q0_S;
		if (weg_cwc_I0 == 0)
			i0_num++;

		if (weg_cwc_Q0 == 0)
			q0_num++;
	}
	totaw_num = i0_num + q0_num;
	if (totaw_num > AW9285_CWCAW_WEDO_THWESH) {
		weg_wf2g5_owg = WEG_WEAD(ah, AW9285_WF2G5);
		if (AW_SWEV_9285E_20(ah)) {
			WEG_WWITE(ah, AW9285_WF2G5,
				  (weg_wf2g5_owg & AW9285_WF2G5_IC50TX) |
				  AW9285_WF2G5_IC50TX_XE_SET);
		} ewse {
			WEG_WWITE(ah, AW9285_WF2G5,
				  (weg_wf2g5_owg & AW9285_WF2G5_IC50TX) |
				  AW9285_WF2G5_IC50TX_SET);
		}
		wetv = aw9285_hw_cw_caw(ah, chan);
		WEG_WWITE(ah, AW9285_WF2G5, weg_wf2g5_owg);
	}
	wetuwn wetv;
}

static boow aw9002_hw_init_caw(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (AW_SWEV_9271(ah)) {
		if (!aw9285_hw_cw_caw(ah, chan))
			wetuwn fawse;
	} ewse if (AW_SWEV_9285(ah) && AW_SWEV_9285_12_OW_WATEW(ah)) {
		if (!aw9285_hw_cwc(ah, chan))
			wetuwn fawse;
	} ewse {
		if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			if (!AW_SWEV_9287_11_OW_WATEW(ah))
				WEG_CWW_BIT(ah, AW_PHY_ADC_CTW,
					    AW_PHY_ADC_CTW_OFF_PWDADC);
			WEG_SET_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
				    AW_PHY_AGC_CONTWOW_FWTW_CAW);
		}

		/* Cawibwate the AGC */
		WEG_WWITE(ah, AW_PHY_AGC_CONTWOW(ah),
			  WEG_WEAD(ah, AW_PHY_AGC_CONTWOW(ah)) |
			  AW_PHY_AGC_CONTWOW_CAW);

		/* Poww fow offset cawibwation compwete */
		if (!ath9k_hw_wait(ah, AW_PHY_AGC_CONTWOW(ah),
				   AW_PHY_AGC_CONTWOW_CAW,
				   0, AH_WAIT_TIMEOUT)) {
			ath_dbg(common, CAWIBWATE,
				"offset cawibwation faiwed to compwete in %d ms; noisy enviwonment?\n",
				AH_WAIT_TIMEOUT / 1000);
			wetuwn fawse;
		}

		if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			if (!AW_SWEV_9287_11_OW_WATEW(ah))
				WEG_SET_BIT(ah, AW_PHY_ADC_CTW,
					    AW_PHY_ADC_CTW_OFF_PWDADC);
			WEG_CWW_BIT(ah, AW_PHY_AGC_CONTWOW(ah),
				    AW_PHY_AGC_CONTWOW_FWTW_CAW);
		}
	}

	/* Do PA Cawibwation */
	aw9002_hw_pa_caw(ah, twue);
	ath9k_hw_woadnf(ah, chan);
	ath9k_hw_stawt_nfcaw(ah, twue);

	ah->caw_wist = ah->caw_wist_wast = ah->caw_wist_cuww = NUWW;

	/* Enabwe IQ, ADC Gain and ADC DC offset CAWs */
	if (AW_SWEV_9100(ah) || AW_SWEV_9160_10_OW_WATEW(ah)) {
		ah->supp_caws = IQ_MISMATCH_CAW;

		if (AW_SWEV_9160_10_OW_WATEW(ah))
			ah->supp_caws |= ADC_GAIN_CAW | ADC_DC_CAW;

		if (AW_SWEV_9287(ah))
			ah->supp_caws &= ~ADC_GAIN_CAW;

		if (aw9002_hw_is_caw_suppowted(ah, chan, ADC_GAIN_CAW)) {
			INIT_CAW(&ah->adcgain_cawdata);
			INSEWT_CAW(ah, &ah->adcgain_cawdata);
			ath_dbg(common, CAWIBWATE,
					"enabwing ADC Gain Cawibwation\n");
		}

		if (aw9002_hw_is_caw_suppowted(ah, chan, ADC_DC_CAW)) {
			INIT_CAW(&ah->adcdc_cawdata);
			INSEWT_CAW(ah, &ah->adcdc_cawdata);
			ath_dbg(common, CAWIBWATE,
					"enabwing ADC DC Cawibwation\n");
		}

		if (aw9002_hw_is_caw_suppowted(ah, chan, IQ_MISMATCH_CAW)) {
			INIT_CAW(&ah->iq_cawdata);
			INSEWT_CAW(ah, &ah->iq_cawdata);
			ath_dbg(common, CAWIBWATE, "enabwing IQ Cawibwation\n");
		}

		ah->caw_wist_cuww = ah->caw_wist;

		if (ah->caw_wist_cuww)
			ath9k_hw_weset_cawibwation(ah, ah->caw_wist_cuww);
	}

	if (ah->cawdata)
		ah->cawdata->CawVawid = 0;

	wetuwn twue;
}

static const stwuct ath9k_pewcaw_data iq_caw_muwti_sampwe = {
	IQ_MISMATCH_CAW,
	MAX_CAW_SAMPWES,
	PEW_MIN_WOG_COUNT,
	aw9002_hw_iqcaw_cowwect,
	aw9002_hw_iqcawibwate
};
static const stwuct ath9k_pewcaw_data iq_caw_singwe_sampwe = {
	IQ_MISMATCH_CAW,
	MIN_CAW_SAMPWES,
	PEW_MAX_WOG_COUNT,
	aw9002_hw_iqcaw_cowwect,
	aw9002_hw_iqcawibwate
};
static const stwuct ath9k_pewcaw_data adc_gain_caw_muwti_sampwe = {
	ADC_GAIN_CAW,
	MAX_CAW_SAMPWES,
	PEW_MIN_WOG_COUNT,
	aw9002_hw_adc_gaincaw_cowwect,
	aw9002_hw_adc_gaincaw_cawibwate
};
static const stwuct ath9k_pewcaw_data adc_gain_caw_singwe_sampwe = {
	ADC_GAIN_CAW,
	MIN_CAW_SAMPWES,
	PEW_MAX_WOG_COUNT,
	aw9002_hw_adc_gaincaw_cowwect,
	aw9002_hw_adc_gaincaw_cawibwate
};
static const stwuct ath9k_pewcaw_data adc_dc_caw_muwti_sampwe = {
	ADC_DC_CAW,
	MAX_CAW_SAMPWES,
	PEW_MIN_WOG_COUNT,
	aw9002_hw_adc_dccaw_cowwect,
	aw9002_hw_adc_dccaw_cawibwate
};
static const stwuct ath9k_pewcaw_data adc_dc_caw_singwe_sampwe = {
	ADC_DC_CAW,
	MIN_CAW_SAMPWES,
	PEW_MAX_WOG_COUNT,
	aw9002_hw_adc_dccaw_cowwect,
	aw9002_hw_adc_dccaw_cawibwate
};

static void aw9002_hw_init_caw_settings(stwuct ath_hw *ah)
{
	if (AW_SWEV_9100(ah)) {
		ah->iq_cawdata.cawData = &iq_caw_muwti_sampwe;
		ah->supp_caws = IQ_MISMATCH_CAW;
		wetuwn;
	}

	if (AW_SWEV_9160_10_OW_WATEW(ah)) {
		if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			ah->iq_cawdata.cawData = &iq_caw_singwe_sampwe;
			ah->adcgain_cawdata.cawData =
				&adc_gain_caw_singwe_sampwe;
			ah->adcdc_cawdata.cawData =
				&adc_dc_caw_singwe_sampwe;
		} ewse {
			ah->iq_cawdata.cawData = &iq_caw_muwti_sampwe;
			ah->adcgain_cawdata.cawData =
				&adc_gain_caw_muwti_sampwe;
			ah->adcdc_cawdata.cawData =
				&adc_dc_caw_muwti_sampwe;
		}
		ah->supp_caws = ADC_GAIN_CAW | ADC_DC_CAW | IQ_MISMATCH_CAW;

		if (AW_SWEV_9287(ah))
			ah->supp_caws &= ~ADC_GAIN_CAW;
	}
}

void aw9002_hw_attach_cawib_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);

	pwiv_ops->init_caw_settings = aw9002_hw_init_caw_settings;
	pwiv_ops->init_caw = aw9002_hw_init_caw;
	pwiv_ops->setup_cawibwation = aw9002_hw_setup_cawibwation;

	ops->cawibwate = aw9002_hw_cawibwate;
}
