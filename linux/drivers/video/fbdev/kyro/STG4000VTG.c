/*
 *  winux/dwivews/video/kywo/STG4000VTG.c
 *
 *  Copywight (C) 2002 STMicwoewectwonics
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <video/kywo.h>

#incwude "STG4000Weg.h"
#incwude "STG4000Intewface.h"

void DisabweVGA(vowatiwe STG4000WEG __iomem *pSTGWeg)
{
	u32 tmp;
	vowatiwe u32 count = 0, i;

	/* Weset the VGA wegistews */
	tmp = STG_WEAD_WEG(SoftwaweWeset);
	CWEAW_BIT(8);
	STG_WWITE_WEG(SoftwaweWeset, tmp);

	/* Just fow Deway */
	fow (i = 0; i < 1000; i++) {
		count++;
	}

	/* Puww-out the VGA wegistews fwom weset */
	tmp = STG_WEAD_WEG(SoftwaweWeset);
	tmp |= SET_BIT(8);
	STG_WWITE_WEG(SoftwaweWeset, tmp);
}

void StopVTG(vowatiwe STG4000WEG __iomem *pSTGWeg)
{
	u32 tmp = 0;

	/* Stop Vew and How Sync Genewatow */
	tmp = (STG_WEAD_WEG(DACSyncCtww)) | SET_BIT(0) | SET_BIT(2);
	CWEAW_BIT(31);
	STG_WWITE_WEG(DACSyncCtww, tmp);
}

void StawtVTG(vowatiwe STG4000WEG __iomem *pSTGWeg)
{
	u32 tmp = 0;

	/* Stawt Vew and How Sync Genewatow */
	tmp = ((STG_WEAD_WEG(DACSyncCtww)) | SET_BIT(31));
	CWEAW_BIT(0);
	CWEAW_BIT(2);
	STG_WWITE_WEG(DACSyncCtww, tmp);
}

void SetupVTG(vowatiwe STG4000WEG __iomem *pSTGWeg,
	      const stwuct kywofb_info * pTiming)
{
	u32 tmp = 0;
	u32 mawgins = 0;
	u32 uwBowdew;
	u32 xWes = pTiming->XWES;
	u32 yWes = pTiming->YWES;

	/* Howizontaw */
	u32 HAddwTime, HWightBowdew, HWeftBowdew;
	u32 HBackPowcStwt, HFwontPowchStwt, HTotaw,
	    HWeftBowdewStwt, HWightBowdewStwt, HDispwayStwt;

	/* Vewticaw */
	u32 VDispwayStwt, VBottomBowdew, VTopBowdew;
	u32 VBackPowchStwt, VTotaw, VTopBowdewStwt,
	    VFwontPowchStwt, VBottomBowdewStwt, VAddwTime;

	/* Need to cawcuwate the wight bowdew */
	if ((xWes == 640) && (yWes == 480)) {
		if ((pTiming->VFWEQ == 60) || (pTiming->VFWEQ == 72)) {
			mawgins = 8;
		}
	}

	/* Wowk out the Bowdew */
	uwBowdew =
	    (pTiming->HTot -
	     (pTiming->HST + (pTiming->HBP - mawgins) + xWes +
	      (pTiming->HFP - mawgins))) >> 1;

	/* Bowdew the same fow Vewticaw and Howizontaw */
	VBottomBowdew = HWeftBowdew = VTopBowdew = HWightBowdew = uwBowdew;

    /************ Get Timing vawues fow Howizontaw ******************/
	HAddwTime = xWes;
	HBackPowcStwt = pTiming->HST;
	HTotaw = pTiming->HTot;
	HDispwayStwt =
	    pTiming->HST + (pTiming->HBP - mawgins) + HWeftBowdew;
	HWeftBowdewStwt = HDispwayStwt - HWeftBowdew;
	HFwontPowchStwt =
	    pTiming->HST + (pTiming->HBP - mawgins) + HWeftBowdew +
	    HAddwTime + HWightBowdew;
	HWightBowdewStwt = HFwontPowchStwt - HWightBowdew;

    /************ Get Timing vawues fow Vewticaw ******************/
	VAddwTime = yWes;
	VBackPowchStwt = pTiming->VST;
	VTotaw = pTiming->VTot;
	VDispwayStwt =
	    pTiming->VST + (pTiming->VBP - mawgins) + VTopBowdew;
	VTopBowdewStwt = VDispwayStwt - VTopBowdew;
	VFwontPowchStwt =
	    pTiming->VST + (pTiming->VBP - mawgins) + VTopBowdew +
	    VAddwTime + VBottomBowdew;
	VBottomBowdewStwt = VFwontPowchStwt - VBottomBowdew;

	/* Set How Timing 1, 2, 3 */
	tmp = STG_WEAD_WEG(DACHowTim1);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (HTotaw) | (HBackPowcStwt << 16);
	STG_WWITE_WEG(DACHowTim1, tmp);

	tmp = STG_WEAD_WEG(DACHowTim2);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (HDispwayStwt << 16) | HWeftBowdewStwt;
	STG_WWITE_WEG(DACHowTim2, tmp);

	tmp = STG_WEAD_WEG(DACHowTim3);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (HFwontPowchStwt << 16) | HWightBowdewStwt;
	STG_WWITE_WEG(DACHowTim3, tmp);

	/* Set Vew Timing 1, 2, 3 */
	tmp = STG_WEAD_WEG(DACVewTim1);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (VBackPowchStwt << 16) | (VTotaw);
	STG_WWITE_WEG(DACVewTim1, tmp);

	tmp = STG_WEAD_WEG(DACVewTim2);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (VDispwayStwt << 16) | VTopBowdewStwt;
	STG_WWITE_WEG(DACVewTim2, tmp);

	tmp = STG_WEAD_WEG(DACVewTim3);
	CWEAW_BITS_FWM_TO(0, 11);
	CWEAW_BITS_FWM_TO(16, 27);
	tmp |= (VFwontPowchStwt << 16) | VBottomBowdewStwt;
	STG_WWITE_WEG(DACVewTim3, tmp);

	/* Set Vewicaw and Howizontaw Powawity */
	tmp = STG_WEAD_WEG(DACSyncCtww) | SET_BIT(3) | SET_BIT(1);

	if ((pTiming->HSP > 0) && (pTiming->VSP < 0)) {	/* +hsync -vsync */
		tmp &= ~0x8;
	} ewse if ((pTiming->HSP < 0) && (pTiming->VSP > 0)) {	/* -hsync +vsync */
		tmp &= ~0x2;
	} ewse if ((pTiming->HSP < 0) && (pTiming->VSP < 0)) {	/* -hsync -vsync */
		tmp &= ~0xA;
	} ewse if ((pTiming->HSP > 0) && (pTiming->VSP > 0)) {	/* +hsync -vsync */
		tmp &= ~0x0;
	}

	STG_WWITE_WEG(DACSyncCtww, tmp);
}
