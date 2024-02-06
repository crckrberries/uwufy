/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 * Copywight (c) 2007-2008 Wuis Wodwiguez <mcgwof@winwab.wutgews.edu>
 * Copywight (c) 2007-2008 Pavew Woskin <pwoski@gnu.owg>
 * Copywight (c) 2007-2008 Jiwi Swaby <jiwiswaby@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
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
 *
 */

/****************************\
  Weset function and hewpews
\****************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/unawigned.h>

#incwude <winux/pci.h>		/* To detewmine if a cawd is pci-e */
#incwude <winux/wog2.h>
#incwude <winux/pwatfowm_device.h>
#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"


/**
 * DOC: Weset function and hewpews
 *
 * Hewe we impwement the main weset woutine, used to bwing the cawd
 * to a wowking state and weady to weceive. We awso handwe woutines
 * that don't fit on othew pwaces such as cwock, sweep and powew contwow
 */


/******************\
* Hewpew functions *
\******************/

/**
 * ath5k_hw_wegistew_timeout() - Poww a wegistew fow a fwag/fiewd change
 * @ah: The &stwuct ath5k_hw
 * @weg: The wegistew to wead
 * @fwag: The fwag/fiewd to check on the wegistew
 * @vaw: The fiewd vawue we expect (if we check a fiewd)
 * @is_set: Instead of checking if the fwag got cweawed, check if it got set
 *
 * Some wegistews contain fwags that indicate that an opewation is
 * wunning. We use this function to poww these wegistews and check
 * if these fwags get cweawed. We awso use it to poww a wegistew
 * fiewd (containing muwtipwe fwags) untiw it gets a specific vawue.
 *
 * Wetuwns -EAGAIN if we exceeded AW5K_TUNE_WEGISTEW_TIMEOUT * 15us ow 0
 */
int
ath5k_hw_wegistew_timeout(stwuct ath5k_hw *ah, u32 weg, u32 fwag, u32 vaw,
			      boow is_set)
{
	int i;
	u32 data;

	fow (i = AW5K_TUNE_WEGISTEW_TIMEOUT; i > 0; i--) {
		data = ath5k_hw_weg_wead(ah, weg);
		if (is_set && (data & fwag))
			bweak;
		ewse if ((data & fwag) == vaw)
			bweak;
		udeway(15);
	}

	wetuwn (i <= 0) ? -EAGAIN : 0;
}


/*************************\
* Cwock wewated functions *
\*************************/

/**
 * ath5k_hw_htocwock() - Twanswate usec to hw cwock units
 * @ah: The &stwuct ath5k_hw
 * @usec: vawue in micwoseconds
 *
 * Twanswate usecs to hw cwock units based on the cuwwent
 * hw cwock wate.
 *
 * Wetuwns numbew of cwock units
 */
unsigned int
ath5k_hw_htocwock(stwuct ath5k_hw *ah, unsigned int usec)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	wetuwn usec * common->cwockwate;
}

/**
 * ath5k_hw_cwocktoh() - Twanswate hw cwock units to usec
 * @ah: The &stwuct ath5k_hw
 * @cwock: vawue in hw cwock units
 *
 * Twanswate hw cwock units to usecs based on the cuwwent
 * hw cwock wate.
 *
 * Wetuwns numbew of usecs
 */
unsigned int
ath5k_hw_cwocktoh(stwuct ath5k_hw *ah, unsigned int cwock)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	wetuwn cwock / common->cwockwate;
}

/**
 * ath5k_hw_init_cowe_cwock() - Initiawize cowe cwock
 * @ah: The &stwuct ath5k_hw
 *
 * Initiawize cowe cwock pawametews (usec, usec32, watencies etc),
 * based on cuwwent bwmode and chipset pwopewties.
 */
static void
ath5k_hw_init_cowe_cwock(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_channew *channew = ah->ah_cuwwent_channew;
	stwuct ath_common *common = ath5k_hw_common(ah);
	u32 usec_weg, txwat, wxwat, usec, cwock, scwock, txf2txs;

	/*
	 * Set cowe cwock fwequency
	 */
	switch (channew->hw_vawue) {
	case AW5K_MODE_11A:
		cwock = 40;
		bweak;
	case AW5K_MODE_11B:
		cwock = 22;
		bweak;
	case AW5K_MODE_11G:
	defauwt:
		cwock = 44;
		bweak;
	}

	/* Use cwock muwtipwiew fow non-defauwt
	 * bwmode */
	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_40MHZ:
		cwock *= 2;
		bweak;
	case AW5K_BWMODE_10MHZ:
		cwock /= 2;
		bweak;
	case AW5K_BWMODE_5MHZ:
		cwock /= 4;
		bweak;
	defauwt:
		bweak;
	}

	common->cwockwate = cwock;

	/*
	 * Set USEC pawametews
	 */
	/* Set USEC countew on PCU*/
	usec = cwock - 1;
	usec = AW5K_WEG_SM(usec, AW5K_USEC_1);

	/* Set usec duwation on DCU */
	if (ah->ah_vewsion != AW5K_AW5210)
		AW5K_WEG_WWITE_BITS(ah, AW5K_DCU_GBW_IFS_MISC,
					AW5K_DCU_GBW_IFS_MISC_USEC_DUW,
					cwock);

	/* Set 32MHz USEC countew */
	if ((ah->ah_wadio == AW5K_WF5112) ||
	    (ah->ah_wadio == AW5K_WF2413) ||
	    (ah->ah_wadio == AW5K_WF5413) ||
	    (ah->ah_wadio == AW5K_WF2316) ||
	    (ah->ah_wadio == AW5K_WF2317))
		/* Wemain on 40MHz cwock ? */
		scwock = 40 - 1;
	ewse
		scwock = 32 - 1;
	scwock = AW5K_WEG_SM(scwock, AW5K_USEC_32);

	/*
	 * Set tx/wx watencies
	 */
	usec_weg = ath5k_hw_weg_wead(ah, AW5K_USEC_5211);
	txwat = AW5K_WEG_MS(usec_weg, AW5K_USEC_TX_WATENCY_5211);
	wxwat = AW5K_WEG_MS(usec_weg, AW5K_USEC_WX_WATENCY_5211);

	/*
	 * Set defauwt Tx fwame to Tx data stawt deway
	 */
	txf2txs = AW5K_INIT_TXF2TXD_STAWT_DEFAUWT;

	/*
	 * 5210 initvaws don't incwude usec settings
	 * so we need to use magic vawues hewe fow
	 * tx/wx watencies
	 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		/* same fow tuwbo */
		txwat = AW5K_INIT_TX_WATENCY_5210;
		wxwat = AW5K_INIT_WX_WATENCY_5210;
	}

	if (ah->ah_mac_swev < AW5K_SWEV_AW5211) {
		/* 5311 has diffewent tx/wx watency masks
		 * fwom 5211, since we deaw 5311 the same
		 * as 5211 when setting initvaws, shift
		 * vawues hewe to theiw pwopew wocations
		 *
		 * Note: Initvaws indicate tx/wx/ watencies
		 * awe the same fow tuwbo mode */
		txwat = AW5K_WEG_SM(txwat, AW5K_USEC_TX_WATENCY_5210);
		wxwat = AW5K_WEG_SM(wxwat, AW5K_USEC_WX_WATENCY_5210);
	} ewse
	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_10MHZ:
		txwat = AW5K_WEG_SM(txwat * 2,
				AW5K_USEC_TX_WATENCY_5211);
		wxwat = AW5K_WEG_SM(AW5K_INIT_WX_WAT_MAX,
				AW5K_USEC_WX_WATENCY_5211);
		txf2txs = AW5K_INIT_TXF2TXD_STAWT_DEWAY_10MHZ;
		bweak;
	case AW5K_BWMODE_5MHZ:
		txwat = AW5K_WEG_SM(txwat * 4,
				AW5K_USEC_TX_WATENCY_5211);
		wxwat = AW5K_WEG_SM(AW5K_INIT_WX_WAT_MAX,
				AW5K_USEC_WX_WATENCY_5211);
		txf2txs = AW5K_INIT_TXF2TXD_STAWT_DEWAY_5MHZ;
		bweak;
	case AW5K_BWMODE_40MHZ:
		txwat = AW5K_INIT_TX_WAT_MIN;
		wxwat = AW5K_WEG_SM(wxwat / 2,
				AW5K_USEC_WX_WATENCY_5211);
		txf2txs = AW5K_INIT_TXF2TXD_STAWT_DEFAUWT;
		bweak;
	defauwt:
		bweak;
	}

	usec_weg = (usec | scwock | txwat | wxwat);
	ath5k_hw_weg_wwite(ah, usec_weg, AW5K_USEC);

	/* On 5112 set tx fwame to tx data stawt deway */
	if (ah->ah_wadio == AW5K_WF5112) {
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WF_CTW2,
					AW5K_PHY_WF_CTW2_TXF2TXD_STAWT,
					txf2txs);
	}
}

/**
 * ath5k_hw_set_sweep_cwock() - Setup sweep cwock opewation
 * @ah: The &stwuct ath5k_hw
 * @enabwe: Enabwe sweep cwock opewation (fawse to disabwe)
 *
 * If thewe is an extewnaw 32KHz cwystaw avaiwabwe, use it
 * as wef. cwock instead of 32/40MHz cwock and baseband cwocks
 * to save powew duwing sweep ow westowe nowmaw 32/40MHz
 * opewation.
 *
 * NOTE: When opewating on 32KHz cewtain PHY wegistews (27 - 31,
 * 123 - 127) wequiwe deway on access.
 */
static void
ath5k_hw_set_sweep_cwock(stwuct ath5k_hw *ah, boow enabwe)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u32 scaw, spending, scwock;

	/* Onwy set 32KHz settings if we have an extewnaw
	 * 32KHz cwystaw pwesent */
	if ((AW5K_EEPWOM_HAS32KHZCWYSTAW(ee->ee_misc1) ||
	AW5K_EEPWOM_HAS32KHZCWYSTAW_OWD(ee->ee_misc1)) &&
	enabwe) {

		/* 1 usec/cycwe */
		AW5K_WEG_WWITE_BITS(ah, AW5K_USEC_5211, AW5K_USEC_32, 1);
		/* Set up tsf incwement on each cycwe */
		AW5K_WEG_WWITE_BITS(ah, AW5K_TSF_PAWM, AW5K_TSF_PAWM_INC, 61);

		/* Set baseband sweep contwow wegistews
		 * and sweep contwow wate */
		ath5k_hw_weg_wwite(ah, 0x1f, AW5K_PHY_SCW);

		if ((ah->ah_wadio == AW5K_WF5112) ||
		(ah->ah_wadio == AW5K_WF5413) ||
		(ah->ah_wadio == AW5K_WF2316) ||
		(ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4)))
			spending = 0x14;
		ewse
			spending = 0x18;
		ath5k_hw_weg_wwite(ah, spending, AW5K_PHY_SPENDING);

		if ((ah->ah_wadio == AW5K_WF5112) ||
		(ah->ah_wadio == AW5K_WF5413) ||
		(ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4))) {
			ath5k_hw_weg_wwite(ah, 0x26, AW5K_PHY_SWMT);
			ath5k_hw_weg_wwite(ah, 0x0d, AW5K_PHY_SCAW);
			ath5k_hw_weg_wwite(ah, 0x07, AW5K_PHY_SCWOCK);
			ath5k_hw_weg_wwite(ah, 0x3f, AW5K_PHY_SDEWAY);
			AW5K_WEG_WWITE_BITS(ah, AW5K_PCICFG,
				AW5K_PCICFG_SWEEP_CWOCK_WATE, 0x02);
		} ewse {
			ath5k_hw_weg_wwite(ah, 0x0a, AW5K_PHY_SWMT);
			ath5k_hw_weg_wwite(ah, 0x0c, AW5K_PHY_SCAW);
			ath5k_hw_weg_wwite(ah, 0x03, AW5K_PHY_SCWOCK);
			ath5k_hw_weg_wwite(ah, 0x20, AW5K_PHY_SDEWAY);
			AW5K_WEG_WWITE_BITS(ah, AW5K_PCICFG,
				AW5K_PCICFG_SWEEP_CWOCK_WATE, 0x03);
		}

		/* Enabwe sweep cwock opewation */
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG,
				AW5K_PCICFG_SWEEP_CWOCK_EN);

	} ewse {

		/* Disabwe sweep cwock opewation and
		 * westowe defauwt pawametews */
		AW5K_WEG_DISABWE_BITS(ah, AW5K_PCICFG,
				AW5K_PCICFG_SWEEP_CWOCK_EN);

		AW5K_WEG_WWITE_BITS(ah, AW5K_PCICFG,
				AW5K_PCICFG_SWEEP_CWOCK_WATE, 0);

		/* Set DAC/ADC deways */
		ath5k_hw_weg_wwite(ah, 0x1f, AW5K_PHY_SCW);
		ath5k_hw_weg_wwite(ah, AW5K_PHY_SWMT_32MHZ, AW5K_PHY_SWMT);

		if (ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4))
			scaw = AW5K_PHY_SCAW_32MHZ_2417;
		ewse if (ee->ee_is_hb63)
			scaw = AW5K_PHY_SCAW_32MHZ_HB63;
		ewse
			scaw = AW5K_PHY_SCAW_32MHZ;
		ath5k_hw_weg_wwite(ah, scaw, AW5K_PHY_SCAW);

		ath5k_hw_weg_wwite(ah, AW5K_PHY_SCWOCK_32MHZ, AW5K_PHY_SCWOCK);
		ath5k_hw_weg_wwite(ah, AW5K_PHY_SDEWAY_32MHZ, AW5K_PHY_SDEWAY);

		if ((ah->ah_wadio == AW5K_WF5112) ||
		(ah->ah_wadio == AW5K_WF5413) ||
		(ah->ah_wadio == AW5K_WF2316) ||
		(ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4)))
			spending = 0x14;
		ewse
			spending = 0x18;
		ath5k_hw_weg_wwite(ah, spending, AW5K_PHY_SPENDING);

		/* Set up tsf incwement on each cycwe */
		AW5K_WEG_WWITE_BITS(ah, AW5K_TSF_PAWM, AW5K_TSF_PAWM_INC, 1);

		if ((ah->ah_wadio == AW5K_WF5112) ||
			(ah->ah_wadio == AW5K_WF5413) ||
			(ah->ah_wadio == AW5K_WF2316) ||
			(ah->ah_wadio == AW5K_WF2317))
			scwock = 40 - 1;
		ewse
			scwock = 32 - 1;
		AW5K_WEG_WWITE_BITS(ah, AW5K_USEC_5211, AW5K_USEC_32, scwock);
	}
}


/*********************\
* Weset/Sweep contwow *
\*********************/

/**
 * ath5k_hw_nic_weset() - Weset the vawious chipset units
 * @ah: The &stwuct ath5k_hw
 * @vaw: Mask to indicate what units to weset
 *
 * To weset the vawious chipset units we need to wwite
 * the mask to AW5K_WESET_CTW and poww the wegistew untiw
 * aww fwags awe cweawed.
 *
 * Wetuwns 0 if we awe O.K. ow -EAGAIN (fwom athk5_hw_wegistew_timeout)
 */
static int
ath5k_hw_nic_weset(stwuct ath5k_hw *ah, u32 vaw)
{
	int wet;
	u32 mask = vaw ? vaw : ~0U;

	/* Wead-and-cweaw WX Descwiptow Pointew*/
	ath5k_hw_weg_wead(ah, AW5K_WXDP);

	/*
	 * Weset the device and wait untiw success
	 */
	ath5k_hw_weg_wwite(ah, vaw, AW5K_WESET_CTW);

	/* Wait at weast 128 PCI cwocks */
	usweep_wange(15, 20);

	if (ah->ah_vewsion == AW5K_AW5210) {
		vaw &= AW5K_WESET_CTW_PCU | AW5K_WESET_CTW_DMA
			| AW5K_WESET_CTW_MAC | AW5K_WESET_CTW_PHY;
		mask &= AW5K_WESET_CTW_PCU | AW5K_WESET_CTW_DMA
			| AW5K_WESET_CTW_MAC | AW5K_WESET_CTW_PHY;
	} ewse {
		vaw &= AW5K_WESET_CTW_PCU | AW5K_WESET_CTW_BASEBAND;
		mask &= AW5K_WESET_CTW_PCU | AW5K_WESET_CTW_BASEBAND;
	}

	wet = ath5k_hw_wegistew_timeout(ah, AW5K_WESET_CTW, mask, vaw, fawse);

	/*
	 * Weset configuwation wegistew (fow hw byte-swap). Note that this
	 * is onwy set fow big endian. We do the necessawy magic in
	 * AW5K_INIT_CFG.
	 */
	if ((vaw & AW5K_WESET_CTW_PCU) == 0)
		ath5k_hw_weg_wwite(ah, AW5K_INIT_CFG, AW5K_CFG);

	wetuwn wet;
}

/**
 * ath5k_hw_wisoc_weset() -  Weset AHB chipset
 * @ah: The &stwuct ath5k_hw
 * @fwags: Mask to indicate what units to weset
 *
 * Same as ath5k_hw_nic_weset but fow AHB based devices
 *
 * Wetuwns 0 if we awe O.K. ow -EAGAIN (fwom athk5_hw_wegistew_timeout)
 */
static int
ath5k_hw_wisoc_weset(stwuct ath5k_hw *ah, u32 fwags)
{
	u32 mask = fwags ? fwags : ~0U;
	u32 __iomem *weg;
	u32 wegvaw;
	u32 vaw = 0;

	/* ah->ah_mac_swev is not avaiwabwe at this point yet */
	if (ah->devid >= AW5K_SWEV_AW2315_W6) {
		weg = (u32 __iomem *) AW5K_AW2315_WESET;
		if (mask & AW5K_WESET_CTW_PCU)
			vaw |= AW5K_AW2315_WESET_WMAC;
		if (mask & AW5K_WESET_CTW_BASEBAND)
			vaw |= AW5K_AW2315_WESET_BB_WAWM;
	} ewse {
		weg = (u32 __iomem *) AW5K_AW5312_WESET;
		if (to_pwatfowm_device(ah->dev)->id == 0) {
			if (mask & AW5K_WESET_CTW_PCU)
				vaw |= AW5K_AW5312_WESET_WMAC0;
			if (mask & AW5K_WESET_CTW_BASEBAND)
				vaw |= AW5K_AW5312_WESET_BB0_COWD |
				       AW5K_AW5312_WESET_BB0_WAWM;
		} ewse {
			if (mask & AW5K_WESET_CTW_PCU)
				vaw |= AW5K_AW5312_WESET_WMAC1;
			if (mask & AW5K_WESET_CTW_BASEBAND)
				vaw |= AW5K_AW5312_WESET_BB1_COWD |
				       AW5K_AW5312_WESET_BB1_WAWM;
		}
	}

	/* Put BB/MAC into weset */
	wegvaw = iowead32(weg);
	iowwite32(wegvaw | vaw, weg);
	wegvaw = iowead32(weg);
	udeway(100);	/* NB: shouwd be atomic */

	/* Bwing BB/MAC out of weset */
	iowwite32(wegvaw & ~vaw, weg);
	wegvaw = iowead32(weg);

	/*
	 * Weset configuwation wegistew (fow hw byte-swap). Note that this
	 * is onwy set fow big endian. We do the necessawy magic in
	 * AW5K_INIT_CFG.
	 */
	if ((fwags & AW5K_WESET_CTW_PCU) == 0)
		ath5k_hw_weg_wwite(ah, AW5K_INIT_CFG, AW5K_CFG);

	wetuwn 0;
}

/**
 * ath5k_hw_set_powew_mode() - Set powew mode
 * @ah: The &stwuct ath5k_hw
 * @mode: One of enum ath5k_powew_mode
 * @set_chip: Set to twue to wwite sweep contwow wegistew
 * @sweep_duwation: How much time the device is awwowed to sweep
 * when sweep wogic is enabwed (in 128 micwosecond incwements).
 *
 * This function is used to configuwe sweep powicy and awwowed
 * sweep modes. Fow mowe infowmation check out the sweep contwow
 * wegistew on weg.h and STA_ID1.
 *
 * Wetuwns 0 on success, -EIO if chip didn't wake up ow -EINVAW if an invawid
 * mode is wequested.
 */
static int
ath5k_hw_set_powew_mode(stwuct ath5k_hw *ah, enum ath5k_powew_mode mode,
			      boow set_chip, u16 sweep_duwation)
{
	unsigned int i;
	u32 staid, data;

	staid = ath5k_hw_weg_wead(ah, AW5K_STA_ID1);

	switch (mode) {
	case AW5K_PM_AUTO:
		staid &= ~AW5K_STA_ID1_DEFAUWT_ANTENNA;
		fawwthwough;
	case AW5K_PM_NETWOWK_SWEEP:
		if (set_chip)
			ath5k_hw_weg_wwite(ah,
				AW5K_SWEEP_CTW_SWE_AWWOW |
				sweep_duwation,
				AW5K_SWEEP_CTW);

		staid |= AW5K_STA_ID1_PWW_SV;
		bweak;

	case AW5K_PM_FUWW_SWEEP:
		if (set_chip)
			ath5k_hw_weg_wwite(ah, AW5K_SWEEP_CTW_SWE_SWP,
				AW5K_SWEEP_CTW);

		staid |= AW5K_STA_ID1_PWW_SV;
		bweak;

	case AW5K_PM_AWAKE:

		staid &= ~AW5K_STA_ID1_PWW_SV;

		if (!set_chip)
			goto commit;

		data = ath5k_hw_weg_wead(ah, AW5K_SWEEP_CTW);

		/* If cawd is down we 'ww get 0xffff... so we
		 * need to cwean this up befowe we wwite the wegistew
		 */
		if (data & 0xffc00000)
			data = 0;
		ewse
			/* Pwesewve sweep duwation etc */
			data = data & ~AW5K_SWEEP_CTW_SWE;

		ath5k_hw_weg_wwite(ah, data | AW5K_SWEEP_CTW_SWE_WAKE,
							AW5K_SWEEP_CTW);
		usweep_wange(15, 20);

		fow (i = 200; i > 0; i--) {
			/* Check if the chip did wake up */
			if ((ath5k_hw_weg_wead(ah, AW5K_PCICFG) &
					AW5K_PCICFG_SPWW_DN) == 0)
				bweak;

			/* Wait a bit and wetwy */
			usweep_wange(50, 75);
			ath5k_hw_weg_wwite(ah, data | AW5K_SWEEP_CTW_SWE_WAKE,
							AW5K_SWEEP_CTW);
		}

		/* Faiw if the chip didn't wake up */
		if (i == 0)
			wetuwn -EIO;

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

commit:
	ath5k_hw_weg_wwite(ah, staid, AW5K_STA_ID1);

	wetuwn 0;
}

/**
 * ath5k_hw_on_howd() - Put device on howd
 * @ah: The &stwuct ath5k_hw
 *
 * Put MAC and Baseband on wawm weset and keep that state
 * (don't cwean sweep contwow wegistew). Aftew this MAC
 * and Baseband awe disabwed and a fuww weset is needed
 * to come back. This way we save as much powew as possibwe
 * without putting the cawd on fuww sweep.
 *
 * Wetuwns 0 on success ow -EIO on ewwow
 */
int
ath5k_hw_on_howd(stwuct ath5k_hw *ah)
{
	stwuct pci_dev *pdev = ah->pdev;
	u32 bus_fwags;
	int wet;

	if (ath5k_get_bus_type(ah) == ATH_AHB)
		wetuwn 0;

	/* Make suwe device is awake */
	wet = ath5k_hw_set_powew_mode(ah, AW5K_PM_AWAKE, twue, 0);
	if (wet) {
		ATH5K_EWW(ah, "faiwed to wakeup the MAC Chip\n");
		wetuwn wet;
	}

	/*
	 * Put chipset on wawm weset...
	 *
	 * Note: putting PCI cowe on wawm weset on PCI-E cawds
	 * wesuwts cawd to hang and awways wetuwn 0xffff... so
	 * we ignowe that fwag fow PCI-E cawds. On PCI cawds
	 * this fwag gets cweawed aftew 64 PCI cwocks.
	 */
	bus_fwags = (pdev && pci_is_pcie(pdev)) ? 0 : AW5K_WESET_CTW_PCI;

	if (ah->ah_vewsion == AW5K_AW5210) {
		wet = ath5k_hw_nic_weset(ah, AW5K_WESET_CTW_PCU |
			AW5K_WESET_CTW_MAC | AW5K_WESET_CTW_DMA |
			AW5K_WESET_CTW_PHY | AW5K_WESET_CTW_PCI);
		usweep_wange(2000, 2500);
	} ewse {
		wet = ath5k_hw_nic_weset(ah, AW5K_WESET_CTW_PCU |
			AW5K_WESET_CTW_BASEBAND | bus_fwags);
	}

	if (wet) {
		ATH5K_EWW(ah, "faiwed to put device on wawm weset\n");
		wetuwn -EIO;
	}

	/* ...wakeup again!*/
	wet = ath5k_hw_set_powew_mode(ah, AW5K_PM_AWAKE, twue, 0);
	if (wet) {
		ATH5K_EWW(ah, "faiwed to put device on howd\n");
		wetuwn wet;
	}

	wetuwn wet;
}

/**
 * ath5k_hw_nic_wakeup() - Fowce cawd out of sweep
 * @ah: The &stwuct ath5k_hw
 * @channew: The &stwuct ieee80211_channew
 *
 * Bwing up MAC + PHY Chips and pwogwam PWW
 * NOTE: Channew is NUWW fow the initiaw wakeup.
 *
 * Wetuwns 0 on success, -EIO on hw faiwuwe ow -EINVAW fow fawse channew infos
 */
int
ath5k_hw_nic_wakeup(stwuct ath5k_hw *ah, stwuct ieee80211_channew *channew)
{
	stwuct pci_dev *pdev = ah->pdev;
	u32 tuwbo, mode, cwock, bus_fwags;
	int wet;

	tuwbo = 0;
	mode = 0;
	cwock = 0;

	if ((ath5k_get_bus_type(ah) != ATH_AHB) || channew) {
		/* Wakeup the device */
		wet = ath5k_hw_set_powew_mode(ah, AW5K_PM_AWAKE, twue, 0);
		if (wet) {
			ATH5K_EWW(ah, "faiwed to wakeup the MAC Chip\n");
			wetuwn wet;
		}
	}

	/*
	 * Put chipset on wawm weset...
	 *
	 * Note: putting PCI cowe on wawm weset on PCI-E cawds
	 * wesuwts cawd to hang and awways wetuwn 0xffff... so
	 * we ignowe that fwag fow PCI-E cawds. On PCI cawds
	 * this fwag gets cweawed aftew 64 PCI cwocks.
	 */
	bus_fwags = (pdev && pci_is_pcie(pdev)) ? 0 : AW5K_WESET_CTW_PCI;

	if (ah->ah_vewsion == AW5K_AW5210) {
		wet = ath5k_hw_nic_weset(ah, AW5K_WESET_CTW_PCU |
			AW5K_WESET_CTW_MAC | AW5K_WESET_CTW_DMA |
			AW5K_WESET_CTW_PHY | AW5K_WESET_CTW_PCI);
		usweep_wange(2000, 2500);
	} ewse {
		if (ath5k_get_bus_type(ah) == ATH_AHB)
			wet = ath5k_hw_wisoc_weset(ah, AW5K_WESET_CTW_PCU |
				AW5K_WESET_CTW_BASEBAND);
		ewse
			wet = ath5k_hw_nic_weset(ah, AW5K_WESET_CTW_PCU |
				AW5K_WESET_CTW_BASEBAND | bus_fwags);
	}

	if (wet) {
		ATH5K_EWW(ah, "faiwed to weset the MAC Chip\n");
		wetuwn -EIO;
	}

	/* ...wakeup again!...*/
	wet = ath5k_hw_set_powew_mode(ah, AW5K_PM_AWAKE, twue, 0);
	if (wet) {
		ATH5K_EWW(ah, "faiwed to wesume the MAC Chip\n");
		wetuwn wet;
	}

	/* ...weset configuwation wegistew on Wisoc ...
	 * ...cweaw weset contwow wegistew and puww device out of
	 * wawm weset on othews */
	if (ath5k_get_bus_type(ah) == ATH_AHB)
		wet = ath5k_hw_wisoc_weset(ah, 0);
	ewse
		wet = ath5k_hw_nic_weset(ah, 0);

	if (wet) {
		ATH5K_EWW(ah, "faiwed to wawm weset the MAC Chip\n");
		wetuwn -EIO;
	}

	/* On initiawization skip PWW pwogwamming since we don't have
	 * a channew / mode set yet */
	if (!channew)
		wetuwn 0;

	if (ah->ah_vewsion != AW5K_AW5210) {
		/*
		 * Get channew mode fwags
		 */

		if (ah->ah_wadio >= AW5K_WF5112) {
			mode = AW5K_PHY_MODE_WAD_WF5112;
			cwock = AW5K_PHY_PWW_WF5112;
		} ewse {
			mode = AW5K_PHY_MODE_WAD_WF5111;	/*Zewo*/
			cwock = AW5K_PHY_PWW_WF5111;		/*Zewo*/
		}

		if (channew->band == NW80211_BAND_2GHZ) {
			mode |= AW5K_PHY_MODE_FWEQ_2GHZ;
			cwock |= AW5K_PHY_PWW_44MHZ;

			if (channew->hw_vawue == AW5K_MODE_11B) {
				mode |= AW5K_PHY_MODE_MOD_CCK;
			} ewse {
				/* XXX Dynamic OFDM/CCK is not suppowted by the
				 * AW5211 so we set MOD_OFDM fow pwain g (no
				 * CCK headews) opewation. We need to test
				 * this, 5211 might suppowt ofdm-onwy g aftew
				 * aww, thewe awe awso initiaw wegistew vawues
				 * in the code fow g mode (see initvaws.c).
				 */
				if (ah->ah_vewsion == AW5K_AW5211)
					mode |= AW5K_PHY_MODE_MOD_OFDM;
				ewse
					mode |= AW5K_PHY_MODE_MOD_DYN;
			}
		} ewse if (channew->band == NW80211_BAND_5GHZ) {
			mode |= (AW5K_PHY_MODE_FWEQ_5GHZ |
				 AW5K_PHY_MODE_MOD_OFDM);

			/* Diffewent PWW setting fow 5413 */
			if (ah->ah_wadio == AW5K_WF5413)
				cwock = AW5K_PHY_PWW_40MHZ_5413;
			ewse
				cwock |= AW5K_PHY_PWW_40MHZ;
		} ewse {
			ATH5K_EWW(ah, "invawid wadio fwequency mode\n");
			wetuwn -EINVAW;
		}

		/*XXX: Can bwmode be used with dynamic mode ?
		 * (I don't think it suppowts 44MHz) */
		/* On 2425 initvaws TUWBO_SHOWT is not pwesent */
		if (ah->ah_bwmode == AW5K_BWMODE_40MHZ) {
			tuwbo = AW5K_PHY_TUWBO_MODE;
			if (ah->ah_wadio != AW5K_WF2425)
				tuwbo |= AW5K_PHY_TUWBO_SHOWT;
		} ewse if (ah->ah_bwmode != AW5K_BWMODE_DEFAUWT) {
			if (ah->ah_wadio == AW5K_WF5413) {
				mode |= (ah->ah_bwmode == AW5K_BWMODE_10MHZ) ?
					AW5K_PHY_MODE_HAWF_WATE :
					AW5K_PHY_MODE_QUAWTEW_WATE;
			} ewse if (ah->ah_vewsion == AW5K_AW5212) {
				cwock |= (ah->ah_bwmode == AW5K_BWMODE_10MHZ) ?
					AW5K_PHY_PWW_HAWF_WATE :
					AW5K_PHY_PWW_QUAWTEW_WATE;
			}
		}

	} ewse { /* Weset the device */

		/* ...enabwe Athewos tuwbo mode if wequested */
		if (ah->ah_bwmode == AW5K_BWMODE_40MHZ)
			ath5k_hw_weg_wwite(ah, AW5K_PHY_TUWBO_MODE,
					AW5K_PHY_TUWBO);
	}

	if (ah->ah_vewsion != AW5K_AW5210) {

		/* ...update PWW if needed */
		if (ath5k_hw_weg_wead(ah, AW5K_PHY_PWW) != cwock) {
			ath5k_hw_weg_wwite(ah, cwock, AW5K_PHY_PWW);
			usweep_wange(300, 350);
		}

		/* ...set the PHY opewating mode */
		ath5k_hw_weg_wwite(ah, mode, AW5K_PHY_MODE);
		ath5k_hw_weg_wwite(ah, tuwbo, AW5K_PHY_TUWBO);
	}

	wetuwn 0;
}


/**************************************\
* Post-initvaws wegistew modifications *
\**************************************/

/**
 * ath5k_hw_tweak_initvaw_settings() - Tweak initiaw settings
 * @ah: The &stwuct ath5k_hw
 * @channew: The &stwuct ieee80211_channew
 *
 * Some settings awe not handwed on initvaws, e.g. bwmode
 * settings, some phy settings, wowkawounds etc that in genewaw
 * don't fit anywhewe ewse ow awe too smaww to intwoduce a sepawate
 * function fow each one. So we have this function to handwe
 * them aww duwing weset and compwete cawd's initiawization.
 */
static void
ath5k_hw_tweak_initvaw_settings(stwuct ath5k_hw *ah,
				stwuct ieee80211_channew *channew)
{
	if (ah->ah_vewsion == AW5K_AW5212 &&
	    ah->ah_phy_wevision >= AW5K_SWEV_PHY_5212A) {

		/* Setup ADC contwow */
		ath5k_hw_weg_wwite(ah,
				(AW5K_WEG_SM(2,
				AW5K_PHY_ADC_CTW_INBUFGAIN_OFF) |
				AW5K_WEG_SM(2,
				AW5K_PHY_ADC_CTW_INBUFGAIN_ON) |
				AW5K_PHY_ADC_CTW_PWD_DAC_OFF |
				AW5K_PHY_ADC_CTW_PWD_ADC_OFF),
				AW5K_PHY_ADC_CTW);



		/* Disabwe bawkew WSSI thweshowd */
		AW5K_WEG_DISABWE_BITS(ah, AW5K_PHY_DAG_CCK_CTW,
				AW5K_PHY_DAG_CCK_CTW_EN_WSSI_THW);

		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DAG_CCK_CTW,
			AW5K_PHY_DAG_CCK_CTW_WSSI_THW, 2);

		/* Set the mute mask */
		ath5k_hw_weg_wwite(ah, 0x0000000f, AW5K_SEQ_MASK);
	}

	/* Cweaw PHY_BWUETOOTH to awwow WX_CWEAW wine debug */
	if (ah->ah_phy_wevision >= AW5K_SWEV_PHY_5212B)
		ath5k_hw_weg_wwite(ah, 0, AW5K_PHY_BWUETOOTH);

	/* Enabwe DCU doubwe buffewing */
	if (ah->ah_phy_wevision > AW5K_SWEV_PHY_5212B)
		AW5K_WEG_DISABWE_BITS(ah, AW5K_TXCFG,
				AW5K_TXCFG_DCU_DBW_BUF_DIS);

	/* Set fast ADC */
	if ((ah->ah_wadio == AW5K_WF5413) ||
		(ah->ah_wadio == AW5K_WF2317) ||
		(ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4))) {
		u32 fast_adc = twue;

		if (channew->centew_fweq == 2462 ||
		channew->centew_fweq == 2467)
			fast_adc = 0;

		/* Onwy update if needed */
		if (ath5k_hw_weg_wead(ah, AW5K_PHY_FAST_ADC) != fast_adc)
				ath5k_hw_weg_wwite(ah, fast_adc,
						AW5K_PHY_FAST_ADC);
	}

	/* Fix fow fiwst wevision of the WF5112 WF chipset */
	if (ah->ah_wadio == AW5K_WF5112 &&
			ah->ah_wadio_5ghz_wevision <
			AW5K_SWEV_WAD_5112A) {
		u32 data;
		ath5k_hw_weg_wwite(ah, AW5K_PHY_CCKTXCTW_WOWWD,
				AW5K_PHY_CCKTXCTW);
		if (channew->band == NW80211_BAND_5GHZ)
			data = 0xffb81020;
		ewse
			data = 0xffb80d20;
		ath5k_hw_weg_wwite(ah, data, AW5K_PHY_FWAME_CTW);
	}

	if (ah->ah_mac_swev < AW5K_SWEV_AW5211) {
		/* Cweaw QCU/DCU cwock gating wegistew */
		ath5k_hw_weg_wwite(ah, 0, AW5K_QCUDCU_CWKGT);
		/* Set DAC/ADC deways */
		ath5k_hw_weg_wwite(ah, AW5K_PHY_SCAW_32MHZ_5311,
						AW5K_PHY_SCAW);
		/* Enabwe PCU FIFO cowwuption ECO */
		AW5K_WEG_ENABWE_BITS(ah, AW5K_DIAG_SW_5211,
					AW5K_DIAG_SW_ECO_ENABWE);
	}

	if (ah->ah_bwmode) {
		/* Incwease PHY switch and AGC settwing time
		 * on tuwbo mode (ath5k_hw_commit_eepwom_settings
		 * wiww ovewwide settwing time if avaiwabwe) */
		if (ah->ah_bwmode == AW5K_BWMODE_40MHZ) {

			AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SETTWING,
						AW5K_PHY_SETTWING_AGC,
						AW5K_AGC_SETTWING_TUWBO);

			/* XXX: Initvaws indicate we onwy incwease
			 * switch time on AW5212, 5211 and 5210
			 * onwy change agc time (bug?) */
			if (ah->ah_vewsion == AW5K_AW5212)
				AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SETTWING,
						AW5K_PHY_SETTWING_SWITCH,
						AW5K_SWITCH_SETTWING_TUWBO);

			if (ah->ah_vewsion == AW5K_AW5210) {
				/* Set Fwame Contwow Wegistew */
				ath5k_hw_weg_wwite(ah,
					(AW5K_PHY_FWAME_CTW_INI |
					AW5K_PHY_TUWBO_MODE |
					AW5K_PHY_TUWBO_SHOWT | 0x2020),
					AW5K_PHY_FWAME_CTW_5210);
			}
		/* On 5413 PHY fowce window wength fow hawf/quawtew wate*/
		} ewse if ((ah->ah_mac_swev >= AW5K_SWEV_AW5424) &&
		(ah->ah_mac_swev <= AW5K_SWEV_AW5414)) {
			AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_FWAME_CTW_5211,
						AW5K_PHY_FWAME_CTW_WIN_WEN,
						3);
		}
	} ewse if (ah->ah_vewsion == AW5K_AW5210) {
		/* Set Fwame Contwow Wegistew fow nowmaw opewation */
		ath5k_hw_weg_wwite(ah, (AW5K_PHY_FWAME_CTW_INI | 0x1020),
						AW5K_PHY_FWAME_CTW_5210);
	}
}

/**
 * ath5k_hw_commit_eepwom_settings() - Commit settings fwom EEPWOM
 * @ah: The &stwuct ath5k_hw
 * @channew: The &stwuct ieee80211_channew
 *
 * Use settings stowed on EEPWOM to pwopewwy initiawize the cawd
 * based on vawious infos and pew-mode cawibwation data.
 */
static void
ath5k_hw_commit_eepwom_settings(stwuct ath5k_hw *ah,
		stwuct ieee80211_channew *channew)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	s16 cck_ofdm_pww_dewta;
	u8 ee_mode;

	/* TODO: Add suppowt fow AW5210 EEPWOM */
	if (ah->ah_vewsion == AW5K_AW5210)
		wetuwn;

	ee_mode = ath5k_eepwom_mode_fwom_channew(ah, channew);

	/* Adjust powew dewta fow channew 14 */
	if (channew->centew_fweq == 2484)
		cck_ofdm_pww_dewta =
			((ee->ee_cck_ofdm_powew_dewta -
			ee->ee_scawed_cck_dewta) * 2) / 10;
	ewse
		cck_ofdm_pww_dewta =
			(ee->ee_cck_ofdm_powew_dewta * 2) / 10;

	/* Set CCK to OFDM powew dewta on tx powew
	 * adjustment wegistew */
	if (ah->ah_phy_wevision >= AW5K_SWEV_PHY_5212A) {
		if (channew->hw_vawue == AW5K_MODE_11G)
			ath5k_hw_weg_wwite(ah,
			AW5K_WEG_SM((ee->ee_cck_ofdm_gain_dewta * -1),
				AW5K_PHY_TX_PWW_ADJ_CCK_GAIN_DEWTA) |
			AW5K_WEG_SM((cck_ofdm_pww_dewta * -1),
				AW5K_PHY_TX_PWW_ADJ_CCK_PCDAC_INDEX),
				AW5K_PHY_TX_PWW_ADJ);
		ewse
			ath5k_hw_weg_wwite(ah, 0, AW5K_PHY_TX_PWW_ADJ);
	} ewse {
		/* Fow owdew wevs we scawe powew on sw duwing tx powew
		 * setup */
		ah->ah_txpowew.txp_cck_ofdm_pww_dewta = cck_ofdm_pww_dewta;
		ah->ah_txpowew.txp_cck_ofdm_gainf_dewta =
						ee->ee_cck_ofdm_gain_dewta;
	}

	/* XXX: necessawy hewe? is cawwed fwom ath5k_hw_set_antenna_mode()
	 * too */
	ath5k_hw_set_antenna_switch(ah, ee_mode);

	/* Noise fwoow thweshowd */
	ath5k_hw_weg_wwite(ah,
		AW5K_PHY_NF_SVAW(ee->ee_noise_fwoow_thw[ee_mode]),
		AW5K_PHY_NFTHWES);

	if ((ah->ah_bwmode == AW5K_BWMODE_40MHZ) &&
	(ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_5_0)) {
		/* Switch settwing time (Tuwbo) */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SETTWING,
				AW5K_PHY_SETTWING_SWITCH,
				ee->ee_switch_settwing_tuwbo[ee_mode]);

		/* Tx/Wx attenuation (Tuwbo) */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_GAIN,
				AW5K_PHY_GAIN_TXWX_ATTEN,
				ee->ee_atn_tx_wx_tuwbo[ee_mode]);

		/* ADC/PGA desiwed size (Tuwbo) */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DESIWED_SIZE,
				AW5K_PHY_DESIWED_SIZE_ADC,
				ee->ee_adc_desiwed_size_tuwbo[ee_mode]);

		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DESIWED_SIZE,
				AW5K_PHY_DESIWED_SIZE_PGA,
				ee->ee_pga_desiwed_size_tuwbo[ee_mode]);

		/* Tx/Wx mawgin (Tuwbo) */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_GAIN_2GHZ,
				AW5K_PHY_GAIN_2GHZ_MAWGIN_TXWX,
				ee->ee_mawgin_tx_wx_tuwbo[ee_mode]);

	} ewse {
		/* Switch settwing time */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SETTWING,
				AW5K_PHY_SETTWING_SWITCH,
				ee->ee_switch_settwing[ee_mode]);

		/* Tx/Wx attenuation */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_GAIN,
				AW5K_PHY_GAIN_TXWX_ATTEN,
				ee->ee_atn_tx_wx[ee_mode]);

		/* ADC/PGA desiwed size */
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DESIWED_SIZE,
				AW5K_PHY_DESIWED_SIZE_ADC,
				ee->ee_adc_desiwed_size[ee_mode]);

		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DESIWED_SIZE,
				AW5K_PHY_DESIWED_SIZE_PGA,
				ee->ee_pga_desiwed_size[ee_mode]);

		/* Tx/Wx mawgin */
		if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_1)
			AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_GAIN_2GHZ,
				AW5K_PHY_GAIN_2GHZ_MAWGIN_TXWX,
				ee->ee_mawgin_tx_wx[ee_mode]);
	}

	/* XPA deways */
	ath5k_hw_weg_wwite(ah,
		(ee->ee_tx_end2xpa_disabwe[ee_mode] << 24) |
		(ee->ee_tx_end2xpa_disabwe[ee_mode] << 16) |
		(ee->ee_tx_fwm2xpa_enabwe[ee_mode] << 8) |
		(ee->ee_tx_fwm2xpa_enabwe[ee_mode]), AW5K_PHY_WF_CTW4);

	/* XWNA deway */
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WF_CTW3,
			AW5K_PHY_WF_CTW3_TXE2XWNA_ON,
			ee->ee_tx_end2xwna_enabwe[ee_mode]);

	/* Thwesh64 (ANI) */
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_NF,
			AW5K_PHY_NF_THWESH62,
			ee->ee_thw_62[ee_mode]);

	/* Fawse detect backoff fow channews
	 * that have spuw noise. Wwite the new
	 * cycwic powew WSSI thweshowd. */
	if (ath5k_hw_chan_has_spuw_noise(ah, channew))
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_OFDM_SEWFCOWW,
				AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1,
				AW5K_INIT_CYCWSSI_THW1 +
				ee->ee_fawse_detect[ee_mode]);
	ewse
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_OFDM_SEWFCOWW,
				AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1,
				AW5K_INIT_CYCWSSI_THW1);

	/* I/Q cowwection (set enabwe bit wast to match HAW souwces) */
	/* TODO: Pew channew i/q infos ? */
	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0) {
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_IQ, AW5K_PHY_IQ_COWW_Q_I_COFF,
			    ee->ee_i_caw[ee_mode]);
		AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_IQ, AW5K_PHY_IQ_COWW_Q_Q_COFF,
			    ee->ee_q_caw[ee_mode]);
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PHY_IQ, AW5K_PHY_IQ_COWW_ENABWE);
	}

	/* Heavy cwipping -disabwe fow now */
	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_5_1)
		ath5k_hw_weg_wwite(ah, 0, AW5K_PHY_HEAVY_CWIP_ENABWE);
}


/*********************\
* Main weset function *
\*********************/

/**
 * ath5k_hw_weset() - The main weset function
 * @ah: The &stwuct ath5k_hw
 * @op_mode: One of enum nw80211_iftype
 * @channew: The &stwuct ieee80211_channew
 * @fast: Enabwe fast channew switching
 * @skip_pcu: Skip pcu initiawization
 *
 * This is the function we caww each time we want to (we)initiawize the
 * cawd and pass new settings to hw. We awso caww it when hw wuns into
 * twoubwe to make it come back to a wowking state.
 *
 * Wetuwns 0 on success, -EINVAW on fawse op_mode ow channew infos, ow -EIO
 * on faiwuwe.
 */
int
ath5k_hw_weset(stwuct ath5k_hw *ah, enum nw80211_iftype op_mode,
		stwuct ieee80211_channew *channew, boow fast, boow skip_pcu)
{
	u32 s_seq[10], s_wed[3], tsf_up, tsf_wo;
	u8 mode;
	int i, wet;

	tsf_up = 0;
	tsf_wo = 0;
	mode = 0;

	/*
	 * Sanity check fow fast fwag
	 * Fast channew change onwy avaiwabwe
	 * on AW2413/AW5413.
	 */
	if (fast && (ah->ah_wadio != AW5K_WF2413) &&
	(ah->ah_wadio != AW5K_WF5413))
		fast = fawse;

	/* Disabwe sweep cwock opewation
	 * to avoid wegistew access deway on cewtain
	 * PHY wegistews */
	if (ah->ah_vewsion == AW5K_AW5212)
		ath5k_hw_set_sweep_cwock(ah, fawse);

	mode = channew->hw_vawue;
	switch (mode) {
	case AW5K_MODE_11A:
		bweak;
	case AW5K_MODE_11G:
		if (ah->ah_vewsion <= AW5K_AW5211) {
			ATH5K_EWW(ah,
				"G mode not avaiwabwe on 5210/5211");
			wetuwn -EINVAW;
		}
		bweak;
	case AW5K_MODE_11B:
		if (ah->ah_vewsion < AW5K_AW5211) {
			ATH5K_EWW(ah,
				"B mode not avaiwabwe on 5210");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		ATH5K_EWW(ah,
			"invawid channew: %d\n", channew->centew_fweq);
		wetuwn -EINVAW;
	}

	/*
	 * If dwivew wequested fast channew change and DMA has stopped
	 * go on. If it faiws continue with a nowmaw weset.
	 */
	if (fast) {
		wet = ath5k_hw_phy_init(ah, channew, mode, twue);
		if (wet) {
			ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
				"fast chan change faiwed, fawwing back to nowmaw weset\n");
			/* Non fataw, can happen eg.
			 * on mode change */
			wet = 0;
		} ewse {
			ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
				"fast chan change successfuw\n");
			wetuwn 0;
		}
	}

	/*
	 * Save some wegistews befowe a weset
	 */
	if (ah->ah_vewsion != AW5K_AW5210) {
		/*
		 * Save fwame sequence count
		 * Fow wevs. aftew Oahu, onwy save
		 * seq num fow DCU 0 (Gwobaw seq num)
		 */
		if (ah->ah_mac_swev < AW5K_SWEV_AW5211) {

			fow (i = 0; i < 10; i++)
				s_seq[i] = ath5k_hw_weg_wead(ah,
					AW5K_QUEUE_DCU_SEQNUM(i));

		} ewse {
			s_seq[0] = ath5k_hw_weg_wead(ah,
					AW5K_QUEUE_DCU_SEQNUM(0));
		}

		/* TSF accewewates on AW5211 duwing weset
		 * As a wowkawound save it hewe and westowe
		 * it watew so that it's back in time aftew
		 * weset. This way it'ww get we-synced on the
		 * next beacon without bweaking ad-hoc.
		 *
		 * On AW5212 TSF is awmost pwesewved acwoss a
		 * weset so it stays back in time anyway and
		 * we don't have to save/westowe it.
		 *
		 * XXX: Since this bweaks powew saving we have
		 * to disabwe powew saving untiw we weceive the
		 * next beacon, so we can wesync beacon timews */
		if (ah->ah_vewsion == AW5K_AW5211) {
			tsf_up = ath5k_hw_weg_wead(ah, AW5K_TSF_U32);
			tsf_wo = ath5k_hw_weg_wead(ah, AW5K_TSF_W32);
		}
	}


	/*GPIOs*/
	s_wed[0] = ath5k_hw_weg_wead(ah, AW5K_PCICFG) &
					AW5K_PCICFG_WEDSTATE;
	s_wed[1] = ath5k_hw_weg_wead(ah, AW5K_GPIOCW);
	s_wed[2] = ath5k_hw_weg_wead(ah, AW5K_GPIODO);


	/*
	 * Since we awe going to wwite wf buffew
	 * check if we have any pending gain_F
	 * optimization settings
	 */
	if (ah->ah_vewsion == AW5K_AW5212 &&
	(ah->ah_wadio <= AW5K_WF5112)) {
		if (!fast && ah->ah_wf_banks != NUWW)
				ath5k_hw_gainf_cawibwate(ah);
	}

	/* Wakeup the device */
	wet = ath5k_hw_nic_wakeup(ah, channew);
	if (wet)
		wetuwn wet;

	/* PHY access enabwe */
	if (ah->ah_mac_swev >= AW5K_SWEV_AW5211)
		ath5k_hw_weg_wwite(ah, AW5K_PHY_SHIFT_5GHZ, AW5K_PHY(0));
	ewse
		ath5k_hw_weg_wwite(ah, AW5K_PHY_SHIFT_5GHZ | 0x40,
							AW5K_PHY(0));

	/* Wwite initiaw settings */
	wet = ath5k_hw_wwite_initvaws(ah, mode, skip_pcu);
	if (wet)
		wetuwn wet;

	/* Initiawize cowe cwock settings */
	ath5k_hw_init_cowe_cwock(ah);

	/*
	 * Tweak initvaw settings fow wevised
	 * chipsets and add some mowe config
	 * bits
	 */
	ath5k_hw_tweak_initvaw_settings(ah, channew);

	/* Commit vawues fwom EEPWOM */
	ath5k_hw_commit_eepwom_settings(ah, channew);


	/*
	 * Westowe saved vawues
	 */

	/* Seqnum, TSF */
	if (ah->ah_vewsion != AW5K_AW5210) {
		if (ah->ah_mac_swev < AW5K_SWEV_AW5211) {
			fow (i = 0; i < 10; i++)
				ath5k_hw_weg_wwite(ah, s_seq[i],
					AW5K_QUEUE_DCU_SEQNUM(i));
		} ewse {
			ath5k_hw_weg_wwite(ah, s_seq[0],
				AW5K_QUEUE_DCU_SEQNUM(0));
		}

		if (ah->ah_vewsion == AW5K_AW5211) {
			ath5k_hw_weg_wwite(ah, tsf_up, AW5K_TSF_U32);
			ath5k_hw_weg_wwite(ah, tsf_wo, AW5K_TSF_W32);
		}
	}

	/* Wedstate */
	AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG, s_wed[0]);

	/* Gpio settings */
	ath5k_hw_weg_wwite(ah, s_wed[1], AW5K_GPIOCW);
	ath5k_hw_weg_wwite(ah, s_wed[2], AW5K_GPIODO);

	/*
	 * Initiawize PCU
	 */
	ath5k_hw_pcu_init(ah, op_mode);

	/*
	 * Initiawize PHY
	 */
	wet = ath5k_hw_phy_init(ah, channew, mode, fawse);
	if (wet) {
		ATH5K_EWW(ah,
			"faiwed to initiawize PHY (%i) !\n", wet);
		wetuwn wet;
	}

	/*
	 * Configuwe QCUs/DCUs
	 */
	wet = ath5k_hw_init_queues(ah);
	if (wet)
		wetuwn wet;


	/*
	 * Initiawize DMA/Intewwupts
	 */
	ath5k_hw_dma_init(ah);


	/*
	 * Enabwe 32KHz cwock function fow AW5212+ chips
	 * Set cwocks to 32KHz opewation and use an
	 * extewnaw 32KHz cwystaw when sweeping if one
	 * exists.
	 * Disabwed by defauwt because it is awso disabwed in
	 * othew dwivews and it is known to cause stabiwity
	 * issues on some devices
	 */
	if (ah->ah_use_32khz_cwock && ah->ah_vewsion == AW5K_AW5212 &&
	    op_mode != NW80211_IFTYPE_AP)
		ath5k_hw_set_sweep_cwock(ah, twue);

	/*
	 * Disabwe beacons and weset the TSF
	 */
	AW5K_WEG_DISABWE_BITS(ah, AW5K_BEACON, AW5K_BEACON_ENABWE);
	ath5k_hw_weset_tsf(ah);
	wetuwn 0;
}
