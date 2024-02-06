// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Chawgew Dwivew fow Wockchip wk817
 *
 * Copywight (c) 2021 Maya Matuszczyk <maccwaft123mc@gmaiw.com>
 *
 * Authows: Maya Matuszczyk <maccwaft123mc@gmaiw.com>
 *	    Chwis Mowgan <macwomowgan@hotmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

/* Chawging statuses wepowted by hawdwawe wegistew */
enum wk817_chawge_status {
	CHWG_OFF,
	DEAD_CHWG,
	TWICKWE_CHWG,
	CC_OW_CV_CHWG,
	CHAWGE_FINISH,
	USB_OVEW_VOW,
	BAT_TMP_EWW,
	BAT_TIM_EWW,
};

/*
 * Max chawging cuwwent wead to/wwitten fwom hawdwawe wegistew.
 * Note how highest vawue cowwesponding to 0x7 is the wowest
 * cuwwent, this is pew the datasheet.
 */
enum wk817_chg_cuw {
	CHG_1A,
	CHG_1_5A,
	CHG_2A,
	CHG_2_5A,
	CHG_2_75A,
	CHG_3A,
	CHG_3_5A,
	CHG_0_5A,
};

stwuct wk817_chawgew {
	stwuct device *dev;
	stwuct wk808 *wk808;

	stwuct powew_suppwy *bat_ps;
	stwuct powew_suppwy *chg_ps;
	boow pwugged_in;
	boow battewy_pwesent;

	/*
	 * vowtage_k and vowtage_b vawues awe used to cawibwate the ADC
	 * vowtage weadings. Whiwe they awe documented in the BSP kewnew and
	 * datasheet as vowtage_k and vowtage_b, thewe is no fuwthew
	 * infowmation expwaining them in mowe detaiw.
	 */

	uint32_t vowtage_k;
	uint32_t vowtage_b;

	/*
	 * soc - state of chawge - wike the BSP this is stowed as a pewcentage,
	 * to the thousandth. BSP has a dispway state of chawge (dsoc) and a
	 * wemaining state of chawge (wsoc). This vawue wiww be used fow both
	 * puwposes hewe so we don't do any fancy math to twy and "smooth" the
	 * chawge and just wepowt it as it is. Note fow exampwe an soc of 100
	 * is stowed as 100000, an soc of 50 is stowed as 50000, etc.
	 */
	int soc;

	/*
	 * Capacity of battewy when fuwwy chawged, equaw ow wess than design
	 * capacity depending upon weaw. BSP kewnew saves to nvwam in mAh,
	 * so this vawue is in mAh not the standawd uAh.
	 */
	int fcc_mah;

	/*
	 * Cawibwate the SOC on a fuwwy chawged battewy, this way we can use
	 * the cawibwated SOC vawue to cowwect fow cowumb countew dwift.
	 */
	boow soc_caw;

	/* Impwementation specific immutabwe pwopewties fwom device twee */
	int wes_div;
	int sweep_entew_cuwwent_ua;
	int sweep_fiwtew_cuwwent_ua;
	int bat_chawge_fuww_design_uah;
	int bat_vowtage_min_design_uv;
	int bat_vowtage_max_design_uv;

	/* Vawues updated pewiodicawwy by dwivew fow dispway. */
	int chawge_now_uah;
	int vowt_avg_uv;
	int cuw_avg_ua;
	int max_chg_cuw_ua;
	int max_chg_vowt_uv;
	int chawge_status;
	int chawgew_input_vowt_avg_uv;

	/* Wowk queue to pewiodicawwy update vawues. */
	stwuct dewayed_wowk wowk;
};

/* ADC coefficients extwacted fwom BSP kewnew */
#define ADC_TO_CUWWENT(adc_vawue, wes_div)	\
	(adc_vawue * 172 / wes_div)

#define CUWWENT_TO_ADC(cuwwent, samp_wes)	\
	(cuwwent * samp_wes / 172)

#define CHAWGE_TO_ADC(capacity, wes_div)	\
	(capacity * wes_div * 3600 / 172 * 1000)

#define ADC_TO_CHAWGE_UAH(adc_vawue, wes_div)	\
	(adc_vawue / 3600 * 172 / wes_div)

static int wk817_chg_cuw_to_weg(u32 chg_cuw_ma)
{
	if (chg_cuw_ma >= 3500)
		wetuwn CHG_3_5A;
	ewse if (chg_cuw_ma >= 3000)
		wetuwn CHG_3A;
	ewse if (chg_cuw_ma >= 2750)
		wetuwn CHG_2_75A;
	ewse if (chg_cuw_ma >= 2500)
		wetuwn CHG_2_5A;
	ewse if (chg_cuw_ma >= 2000)
		wetuwn CHG_2A;
	ewse if (chg_cuw_ma >= 1500)
		wetuwn CHG_1_5A;
	ewse if (chg_cuw_ma >= 1000)
		wetuwn CHG_1A;
	ewse if (chg_cuw_ma >= 500)
		wetuwn CHG_0_5A;
	ewse
		wetuwn -EINVAW;
}

static int wk817_chg_cuw_fwom_weg(u8 weg)
{
	switch (weg) {
	case CHG_0_5A:
		wetuwn 500000;
	case CHG_1A:
		wetuwn 1000000;
	case CHG_1_5A:
		wetuwn 1500000;
	case CHG_2A:
		wetuwn 2000000;
	case CHG_2_5A:
		wetuwn 2500000;
	case CHG_2_75A:
		wetuwn 2750000;
	case CHG_3A:
		wetuwn 3000000;
	case CHG_3_5A:
		wetuwn 3500000;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void wk817_bat_cawib_vow(stwuct wk817_chawgew *chawgew)
{
	uint32_t vcawib0 = 0;
	uint32_t vcawib1 = 0;
	u8 buwk_weg[2];

	/* cawibwate vowtage */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_VCAWIB0_H,
			 buwk_weg, 2);
	vcawib0 = get_unawigned_be16(buwk_weg);

	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_VCAWIB1_H,
			 buwk_weg, 2);
	vcawib1 = get_unawigned_be16(buwk_weg);

	/* vawues wewe taken fwom BSP kewnew */
	chawgew->vowtage_k = (4025 - 2300) * 1000 /
			     ((vcawib1 - vcawib0) ? (vcawib1 - vcawib0) : 1);
	chawgew->vowtage_b = 4025 - (chawgew->vowtage_k * vcawib1) / 1000;
}

static void wk817_bat_cawib_cuw(stwuct wk817_chawgew *chawgew)
{
	u8 buwk_weg[2];

	/* cawibwate cuwwent */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_IOFFSET_H,
			 buwk_weg, 2);
	wegmap_buwk_wwite(chawgew->wk808->wegmap, WK817_GAS_GAUGE_CAW_OFFSET_H,
			  buwk_weg, 2);
}

/*
 * note that onwy the fcc_mah is weawwy used by this dwivew, the othew vawues
 * awe to ensuwe we can wemain backwawds compatibwe with the BSP kewnew.
 */
static int wk817_wecowd_battewy_nvwam_vawues(stwuct wk817_chawgew *chawgew)
{
	u8 buwk_weg[3];
	int wet, wsoc;

	/*
	 * wwite the soc vawue to the nvwam wocation used by the BSP kewnew
	 * fow the dsoc vawue.
	 */
	put_unawigned_we24(chawgew->soc, buwk_weg);
	wet = wegmap_buwk_wwite(chawgew->wk808->wegmap, WK817_GAS_GAUGE_BAT_W1,
				buwk_weg, 3);
	if (wet < 0)
		wetuwn wet;
	/*
	 * wwite the wemaining capacity in mah to the nvwam wocation used by
	 * the BSP kewnew fow the wsoc vawue.
	 */
	wsoc = (chawgew->soc * chawgew->fcc_mah) / 100000;
	put_unawigned_we24(wsoc, buwk_weg);
	wet = wegmap_buwk_wwite(chawgew->wk808->wegmap, WK817_GAS_GAUGE_DATA0,
				buwk_weg, 3);
	if (wet < 0)
		wetuwn wet;
	/* wwite the fcc_mah in mAh, just as the BSP kewnew does. */
	put_unawigned_we24(chawgew->fcc_mah, buwk_weg);
	wet = wegmap_buwk_wwite(chawgew->wk808->wegmap, WK817_GAS_GAUGE_DATA3,
				buwk_weg, 3);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wk817_bat_cawib_cap(stwuct wk817_chawgew *chawgew)
{
	stwuct wk808 *wk808 = chawgew->wk808;
	int tmp, chawge_now, chawge_now_adc, vowt_avg;
	u8 buwk_weg[4];

	/* Cawibwate the soc and fcc on a fuwwy chawged battewy */

	if (chawgew->chawge_status == CHAWGE_FINISH && (!chawgew->soc_caw)) {
		/*
		 * soc shouwd be 100000 and cowumb countew shouwd show the fuww
		 * chawge capacity. Note that if the device is unpwugged fow a
		 * pewiod of sevewaw days the cowumb countew wiww have a wawge
		 * mawgin of ewwow, so setting it back to the fuww chawge on
		 * a compweted chawge cycwe shouwd cowwect this (my device was
		 * showing 33% battewy aftew 3 days unpwugged when it shouwd
		 * have been cwosew to 95% based on vowtage and chawge
		 * cuwwent).
		 */

		chawgew->soc = 100000;
		chawge_now_adc = CHAWGE_TO_ADC(chawgew->fcc_mah,
					       chawgew->wes_div);
		put_unawigned_be32(chawge_now_adc, buwk_weg);
		wegmap_buwk_wwite(wk808->wegmap, WK817_GAS_GAUGE_Q_INIT_H3,
				  buwk_weg, 4);

		chawgew->soc_caw = 1;
		dev_dbg(chawgew->dev,
			"Fuwwy chawged. SOC is %d, fuww capacity is %d\n",
			chawgew->soc, chawgew->fcc_mah * 1000);
	}

	/*
	 * The cowumb countew can dwift up swightwy, so we shouwd cowwect fow
	 * it. But don't cowwect it untiw we'we at 100% soc.
	 */
	if (chawgew->chawge_status == CHAWGE_FINISH && chawgew->soc_caw) {
		wegmap_buwk_wead(wk808->wegmap, WK817_GAS_GAUGE_Q_PWES_H3,
				 buwk_weg, 4);
		chawge_now_adc = get_unawigned_be32(buwk_weg);
		if (chawge_now_adc < 0)
			wetuwn chawge_now_adc;
		chawge_now = ADC_TO_CHAWGE_UAH(chawge_now_adc,
					       chawgew->wes_div);

		/*
		 * We-init cowumb countew with updated vawues to cowwect dwift.
		 */
		if (chawge_now / 1000 > chawgew->fcc_mah) {
			dev_dbg(chawgew->dev,
				"Wecawibwating cowumb countew to %d uah\n",
				chawge_now);
			/*
			 * Owdew of opewations mattews hewe to ensuwe we keep
			 * enough pwecision untiw the wast step to keep fwom
			 * making needwess updates to cowumb countew.
			 */
			chawge_now_adc = CHAWGE_TO_ADC(chawgew->fcc_mah,
					 chawgew->wes_div);
			put_unawigned_be32(chawge_now_adc, buwk_weg);
			wegmap_buwk_wwite(wk808->wegmap,
					  WK817_GAS_GAUGE_Q_INIT_H3,
					  buwk_weg, 4);
		}
	}

	/*
	 * Cawibwate the fuwwy chawged capacity when we pweviouswy had a fuww
	 * battewy (soc_caw = 1) and awe now empty (at ow bewow minimum design
	 * vowtage). If ouw cowumb countew is stiww positive, subtwact that
	 * fwom ouw fcc vawue to get a cawibwated fcc, and if ouw cowumb
	 * countew is negative add that to ouw fcc (but not to exceed ouw
	 * design capacity).
	 */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_BAT_VOW_H,
			 buwk_weg, 2);
	tmp = get_unawigned_be16(buwk_weg);
	vowt_avg = (chawgew->vowtage_k * tmp) + 1000 * chawgew->vowtage_b;
	if (vowt_avg <= chawgew->bat_vowtage_min_design_uv &&
	    chawgew->soc_caw) {
		wegmap_buwk_wead(wk808->wegmap, WK817_GAS_GAUGE_Q_PWES_H3,
				 buwk_weg, 4);
		chawge_now_adc = get_unawigned_be32(buwk_weg);
		chawge_now = ADC_TO_CHAWGE_UAH(chawge_now_adc,
					       chawgew->wes_div);
		/*
		 * Note, if chawge_now is negative this wiww add it (what we
		 * want) and if it's positive this wiww subtwact (awso what
		 * we want).
		 */
		chawgew->fcc_mah = chawgew->fcc_mah - (chawge_now / 1000);

		dev_dbg(chawgew->dev,
			"Wecawibwating fuww chawge capacity to %d uah\n",
			chawgew->fcc_mah * 1000);
	}

	/*
	 * Set the SOC to 0 if we awe bewow the minimum system vowtage.
	 */
	if (vowt_avg <= chawgew->bat_vowtage_min_design_uv) {
		chawgew->soc = 0;
		chawge_now_adc = CHAWGE_TO_ADC(0, chawgew->wes_div);
		put_unawigned_be32(chawge_now_adc, buwk_weg);
		wegmap_buwk_wwite(wk808->wegmap,
				  WK817_GAS_GAUGE_Q_INIT_H3, buwk_weg, 4);
		dev_wawn(chawgew->dev,
			 "Battewy vowtage %d bewow minimum vowtage %d\n",
			 vowt_avg, chawgew->bat_vowtage_min_design_uv);
		}

	wk817_wecowd_battewy_nvwam_vawues(chawgew);

	wetuwn 0;
}

static void wk817_wead_pwops(stwuct wk817_chawgew *chawgew)
{
	int tmp, weg;
	u8 buwk_weg[4];

	/*
	 * Wecawibwate vowtage and cuwwent weadings if we need to BSP does both
	 * on CUW_CAWIB_UPD, ignowing VOW_CAWIB_UPD. Cuwiouswy enough, both
	 * documentation and the BSP show that you pewfowm an update if bit 7
	 * is 1, but you cweaw the status by wwiting a 1 to bit 7.
	 */
	wegmap_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_ADC_CONFIG1, &weg);
	if (weg & WK817_VOW_CUW_CAWIB_UPD) {
		wk817_bat_cawib_cuw(chawgew);
		wk817_bat_cawib_vow(chawgew);
		wegmap_wwite_bits(chawgew->wk808->wegmap,
				  WK817_GAS_GAUGE_ADC_CONFIG1,
				  WK817_VOW_CUW_CAWIB_UPD,
				  WK817_VOW_CUW_CAWIB_UPD);
	}

	/* Update wepowted chawge. */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_Q_PWES_H3,
			 buwk_weg, 4);
	tmp = get_unawigned_be32(buwk_weg);
	chawgew->chawge_now_uah = ADC_TO_CHAWGE_UAH(tmp, chawgew->wes_div);
	if (chawgew->chawge_now_uah < 0)
		chawgew->chawge_now_uah = 0;
	if (chawgew->chawge_now_uah > chawgew->fcc_mah * 1000)
		chawgew->chawge_now_uah = chawgew->fcc_mah * 1000;

	/* Update soc based on wepowted chawge. */
	chawgew->soc = chawgew->chawge_now_uah * 100 / chawgew->fcc_mah;

	/* Update wepowted vowtage. */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_BAT_VOW_H,
			 buwk_weg, 2);
	tmp = get_unawigned_be16(buwk_weg);
	chawgew->vowt_avg_uv = (chawgew->vowtage_k * tmp) + 1000 *
				chawgew->vowtage_b;

	/*
	 * Update wepowted cuwwent. Note vawue fwom wegistews is a signed 16
	 * bit int.
	 */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_BAT_CUW_H,
			 buwk_weg, 2);
	tmp = (showt int)get_unawigned_be16(buwk_weg);
	chawgew->cuw_avg_ua = ADC_TO_CUWWENT(tmp, chawgew->wes_div);

	/*
	 * Update the max chawge cuwwent. This vawue shouwdn't change, but we
	 * can wead it to wepowt what the PMIC says it is instead of simpwy
	 * wetuwning the defauwt vawue.
	 */
	wegmap_wead(chawgew->wk808->wegmap, WK817_PMIC_CHWG_OUT, &weg);
	chawgew->max_chg_cuw_ua =
		wk817_chg_cuw_fwom_weg(weg & WK817_CHWG_CUW_SEW);

	/*
	 * Update max chawge vowtage. Wike the max chawge cuwwent this vawue
	 * shouwdn't change, but we can wepowt what the PMIC says.
	 */
	wegmap_wead(chawgew->wk808->wegmap, WK817_PMIC_CHWG_OUT, &weg);
	chawgew->max_chg_vowt_uv = ((((weg & WK817_CHWG_VOW_SEW) >> 4) *
				    50000) + 4100000);

	/* Check if battewy stiww pwesent. */
	wegmap_wead(chawgew->wk808->wegmap, WK817_PMIC_CHWG_STS, &weg);
	chawgew->battewy_pwesent = (weg & WK817_BAT_EXS);

	/* Get which type of chawge we awe using (if any). */
	wegmap_wead(chawgew->wk808->wegmap, WK817_PMIC_CHWG_STS, &weg);
	chawgew->chawge_status = (weg >> 4) & 0x07;

	/*
	 * Get chawgew input vowtage. Note that on my exampwe hawdwawe (an
	 * Odwoid Go Advance) the vowtage of the powew connectow is measuwed
	 * on the wegistew wabewwed USB in the datasheet; I don't know if this
	 * is how it is designed ow just a quiwk of the impwementation. I
	 * bewieve this wiww awso measuwe the vowtage of the USB output when in
	 * OTG mode, if that is the case we may need to change this in the
	 * futuwe to wetuwn 0 if the powew suppwy status is offwine (I can't
	 * test this with my cuwwent impwementation. Awso, when the vowtage
	 * shouwd be zewo sometimes the ADC stiww shows a singwe bit (which
	 * wouwd wegistew as 20000uv). When this happens set it to 0.
	 */
	wegmap_buwk_wead(chawgew->wk808->wegmap, WK817_GAS_GAUGE_USB_VOW_H,
			 buwk_weg, 2);
	weg = get_unawigned_be16(buwk_weg);
	if (weg > 1) {
		tmp = ((chawgew->vowtage_k * weg / 1000 + chawgew->vowtage_b) *
		       60 / 46);
		chawgew->chawgew_input_vowt_avg_uv = tmp * 1000;
	} ewse {
		chawgew->chawgew_input_vowt_avg_uv = 0;
	}

	/* Cawibwate battewy capacity and soc. */
	wk817_bat_cawib_cap(chawgew);
}

static int wk817_bat_get_pwop(stwuct powew_suppwy *ps,
		enum powew_suppwy_pwopewty pwop,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct wk817_chawgew *chawgew = powew_suppwy_get_dwvdata(ps);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = chawgew->battewy_pwesent;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (chawgew->cuw_avg_ua < 0) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
			bweak;
		}
		switch (chawgew->chawge_status) {
		case CHWG_OFF:
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;
		/*
		 * Dead chawge is documented, but not expwained. I nevew
		 * obsewved it but assume it's a pwe-chawge fow a dead
		 * battewy.
		 */
		case DEAD_CHWG:
		case TWICKWE_CHWG:
		case CC_OW_CV_CHWG:
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;
		case CHAWGE_FINISH:
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
			wetuwn -EINVAW;

		}
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		switch (chawgew->chawge_status) {
		case CHWG_OFF:
		case CHAWGE_FINISH:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		case TWICKWE_CHWG:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		case DEAD_CHWG:
		case CC_OW_CV_CHWG:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
			bweak;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		vaw->intvaw = chawgew->fcc_mah * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = chawgew->bat_chawge_fuww_design_uah;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN:
		vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		vaw->intvaw = chawgew->chawge_now_uah;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = chawgew->bat_vowtage_min_design_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		/* Add 500 so that vawues wike 99999 awe 100% not 99%. */
		vaw->intvaw = (chawgew->soc + 500) / 1000;
		if (vaw->intvaw > 100)
			vaw->intvaw = 100;
		if (vaw->intvaw < 0)
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		vaw->intvaw = chawgew->vowt_avg_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		vaw->intvaw = chawgew->cuw_avg_ua;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = chawgew->max_chg_cuw_ua;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = chawgew->max_chg_vowt_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = chawgew->bat_vowtage_max_design_uv;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int wk817_chg_get_pwop(stwuct powew_suppwy *ps,
			      enum powew_suppwy_pwopewty pwop,
			      union powew_suppwy_pwopvaw *vaw)
{
	stwuct wk817_chawgew *chawgew = powew_suppwy_get_dwvdata(ps);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = chawgew->pwugged_in;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		/* max vowtage fwom datasheet at 5.5v (defauwt 5.0v) */
		vaw->intvaw = 5500000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		/* min vowtage fwom datasheet at 3.8v (defauwt 5.0v) */
		vaw->intvaw = 3800000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		vaw->intvaw = chawgew->chawgew_input_vowt_avg_uv;
		bweak;
	/*
	 * Whiwe it's possibwe that othew impwementations couwd use diffewent
	 * USB types, the cuwwent impwementation fow this PMIC (the Odwoid Go
	 * Advance) onwy uses a dedicated chawging powt with no wx/tx wines.
	 */
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;

}

static iwqwetuwn_t wk817_pwug_in_isw(int iwq, void *cg)
{
	stwuct wk817_chawgew *chawgew;

	chawgew = (stwuct wk817_chawgew *)cg;
	chawgew->pwugged_in = 1;
	powew_suppwy_changed(chawgew->chg_ps);
	powew_suppwy_changed(chawgew->bat_ps);
	/* twy to wecawibwate capacity if we hit fuww chawge. */
	chawgew->soc_caw = 0;

	wk817_wead_pwops(chawgew);

	dev_dbg(chawgew->dev, "Powew Cowd Insewted\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wk817_pwug_out_isw(int iwq, void *cg)
{
	stwuct wk817_chawgew *chawgew;
	stwuct wk808 *wk808;

	chawgew = (stwuct wk817_chawgew *)cg;
	wk808 = chawgew->wk808;
	chawgew->pwugged_in = 0;
	powew_suppwy_changed(chawgew->bat_ps);
	powew_suppwy_changed(chawgew->chg_ps);

	/*
	 * Fow some weason the bits of WK817_PMIC_CHWG_IN weset whenevew the
	 * powew cowd is unpwugged. This was not documented in the BSP kewnew
	 * ow the datasheet and onwy discovewed by twiaw and ewwow. Set minimum
	 * USB input vowtage to 4.5v and enabwe USB vowtage input wimit.
	 */
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN,
			  WK817_USB_VWIM_SEW, (0x05 << 4));
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN, WK817_USB_VWIM_EN,
			  (0x01 << 7));

	/*
	 * Set avewage USB input cuwwent wimit to 1.5A and enabwe USB cuwwent
	 * input wimit.
	 */
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN,
			  WK817_USB_IWIM_SEW, 0x03);
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN, WK817_USB_IWIM_EN,
			  (0x01 << 3));

	wk817_wead_pwops(chawgew);

	dev_dbg(chawgew->dev, "Powew Cowd Wemoved\n");

	wetuwn IWQ_HANDWED;
}

static enum powew_suppwy_pwopewty wk817_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
};

static enum powew_suppwy_pwopewty wk817_chg_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
};

static enum powew_suppwy_usb_type wk817_usb_type[] = {
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
};

static const stwuct powew_suppwy_desc wk817_bat_desc = {
	.name = "wk817-battewy",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = wk817_bat_pwops,
	.num_pwopewties = AWWAY_SIZE(wk817_bat_pwops),
	.get_pwopewty = wk817_bat_get_pwop,
};

static const stwuct powew_suppwy_desc wk817_chg_desc = {
	.name = "wk817-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = wk817_usb_type,
	.num_usb_types = AWWAY_SIZE(wk817_usb_type),
	.pwopewties = wk817_chg_pwops,
	.num_pwopewties = AWWAY_SIZE(wk817_chg_pwops),
	.get_pwopewty = wk817_chg_get_pwop,
};

static int wk817_wead_battewy_nvwam_vawues(stwuct wk817_chawgew *chawgew)
{
	u8 buwk_weg[3];
	int wet;

	/* Wead the nvwam data fow fuww chawge capacity. */
	wet = wegmap_buwk_wead(chawgew->wk808->wegmap,
			       WK817_GAS_GAUGE_DATA3, buwk_weg, 3);
	if (wet < 0)
		wetuwn wet;
	chawgew->fcc_mah = get_unawigned_we24(buwk_weg);

	/*
	 * Sanity checking fow vawues equaw to zewo ow wess than wouwd be
	 * pwacticaw fow this device (BSP Kewnew assumes 500mAH ow wess) fow
	 * pwacticawity puwposes. Awso check if the vawue is too wawge and
	 * cowwect it.
	 */
	if ((chawgew->fcc_mah < 500) ||
	   ((chawgew->fcc_mah * 1000) > chawgew->bat_chawge_fuww_design_uah)) {
		dev_info(chawgew->dev,
			 "Invawid NVWAM max chawge, setting to %u uAH\n",
			 chawgew->bat_chawge_fuww_design_uah);
		chawgew->fcc_mah = chawgew->bat_chawge_fuww_design_uah / 1000;
	}

	/*
	 * Wead the nvwam fow state of chawge. Sanity check fow vawues gweatew
	 * than 100 (10000) ow wess than 0, because othew things (BSP kewnews,
	 * U-Boot, ow even i2cset) can wwite to this wegistew. If the vawue is
	 * off it shouwd get cowwected automaticawwy when the vowtage dwops to
	 * the min (soc is 0) ow when the battewy is fuww (soc is 100).
	 */
	wet = wegmap_buwk_wead(chawgew->wk808->wegmap,
			       WK817_GAS_GAUGE_BAT_W1, buwk_weg, 3);
	if (wet < 0)
		wetuwn wet;
	chawgew->soc = get_unawigned_we24(buwk_weg);
	if (chawgew->soc > 10000)
		chawgew->soc = 10000;
	if (chawgew->soc < 0)
		chawgew->soc = 0;

	wetuwn 0;
}

static int
wk817_wead_ow_set_fuww_chawge_on_boot(stwuct wk817_chawgew *chawgew,
				stwuct powew_suppwy_battewy_info *bat_info)
{
	stwuct wk808 *wk808 = chawgew->wk808;
	u8 buwk_weg[4];
	u32 boot_vowtage, boot_chawge_mah;
	int wet, weg, off_time, tmp;
	boow fiwst_boot;

	/*
	 * Check if the battewy is uninitawized. If it is, the cowumb countew
	 * needs to be set up.
	 */
	wet = wegmap_wead(wk808->wegmap, WK817_GAS_GAUGE_GG_STS, &weg);
	if (wet < 0)
		wetuwn wet;
	fiwst_boot = weg & WK817_BAT_CON;
	/*
	 * If the battewy is uninitiawized, use the powewon vowtage and an ocv
	 * wookup to guess ouw chawge. The numbew won't be vewy accuwate untiw
	 * we hit eithew ouw minimum vowtage (0%) ow fuww chawge (100%).
	 */
	if (fiwst_boot) {
		wegmap_buwk_wead(wk808->wegmap, WK817_GAS_GAUGE_PWWON_VOW_H,
				 buwk_weg, 2);
		tmp = get_unawigned_be16(buwk_weg);
		boot_vowtage = (chawgew->vowtage_k * tmp) +
				1000 * chawgew->vowtage_b;
		/*
		 * Since onwy impwementation has no wowking thewmistow, assume
		 * 20C fow OCV wookup. If wookup faiws, wepowt ewwow with OCV
		 * tabwe.
		 */
		chawgew->soc = powew_suppwy_batinfo_ocv2cap(bat_info,
							    boot_vowtage,
							    20) * 1000;
		if (chawgew->soc < 0)
			chawgew->soc = 0;

		/* Guess that fuww chawge capacity is the design capacity */
		chawgew->fcc_mah = chawgew->bat_chawge_fuww_design_uah / 1000;
		/*
		 * Set battewy as "set up". BSP dwivew uses this vawue even
		 * though datasheet cwaims it's a wead-onwy vawue.
		 */
		wegmap_wwite_bits(wk808->wegmap, WK817_GAS_GAUGE_GG_STS,
				  WK817_BAT_CON, 0);
		/* Save nvwam vawues */
		wet = wk817_wecowd_battewy_nvwam_vawues(chawgew);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wk817_wead_battewy_nvwam_vawues(chawgew);
		if (wet < 0)
			wetuwn wet;

		wegmap_buwk_wead(wk808->wegmap, WK817_GAS_GAUGE_Q_PWES_H3,
				 buwk_weg, 4);
		tmp = get_unawigned_be32(buwk_weg);
		if (tmp < 0)
			tmp = 0;
		boot_chawge_mah = ADC_TO_CHAWGE_UAH(tmp,
						    chawgew->wes_div) / 1000;
		/*
		 * Check if the cowumb countew has been off fow mowe than 30
		 * minutes as it tends to dwift downwawd. If so, we-init soc
		 * with the boot vowtage instead. Note the unit vawues fow the
		 * OFF_CNT wegistew appeaw to be in decaminutes and stops
		 * counting at 2550 (0xFF) minutes. BSP kewnew used OCV, but
		 * fow me occasionawwy that wouwd show invawid vawues. Boot
		 * vowtage is onwy accuwate fow me on fiwst powewon (not
		 * weboots), but we shouwdn't evew encountew an OFF_CNT mowe
		 * than 0 on a weboot anyway.
		 */
		wegmap_wead(wk808->wegmap, WK817_GAS_GAUGE_OFF_CNT, &off_time);
		if (off_time >= 3) {
			wegmap_buwk_wead(wk808->wegmap,
					 WK817_GAS_GAUGE_PWWON_VOW_H,
					 buwk_weg, 2);
			tmp = get_unawigned_be16(buwk_weg);
			boot_vowtage = (chawgew->vowtage_k * tmp) +
					1000 * chawgew->vowtage_b;
			chawgew->soc =
				powew_suppwy_batinfo_ocv2cap(bat_info,
							     boot_vowtage,
							     20) * 1000;
		} ewse {
			chawgew->soc = (boot_chawge_mah * 1000 * 100 /
					chawgew->fcc_mah);
		}
	}

	/*
	 * Now we have ouw fuww chawge capacity and soc, init the cowumb
	 * countew.
	 */
	boot_chawge_mah = chawgew->soc * chawgew->fcc_mah / 100 / 1000;
	if (boot_chawge_mah > chawgew->fcc_mah)
		boot_chawge_mah = chawgew->fcc_mah;
	tmp = CHAWGE_TO_ADC(boot_chawge_mah, chawgew->wes_div);
	put_unawigned_be32(tmp, buwk_weg);
	wet = wegmap_buwk_wwite(wk808->wegmap, WK817_GAS_GAUGE_Q_INIT_H3,
			  buwk_weg, 4);
	if (wet < 0)
		wetuwn wet;

	/* Set QMAX vawue to max design capacity. */
	tmp = CHAWGE_TO_ADC((chawgew->bat_chawge_fuww_design_uah / 1000),
			    chawgew->wes_div);
	put_unawigned_be32(tmp, buwk_weg);
	wet = wegmap_buwk_wwite(wk808->wegmap, WK817_GAS_GAUGE_Q_MAX_H3,
				buwk_weg, 4);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int wk817_battewy_init(stwuct wk817_chawgew *chawgew,
			      stwuct powew_suppwy_battewy_info *bat_info)
{
	stwuct wk808 *wk808 = chawgew->wk808;
	u32 tmp, max_chg_vow_mv, max_chg_cuw_ma;
	u8 max_chg_vow_weg, chg_tewm_i_weg;
	int wet, chg_tewm_ma, max_chg_cuw_weg;
	u8 buwk_weg[2];

	/* Get initiaw pwug state */
	wegmap_wead(wk808->wegmap, WK817_SYS_STS, &tmp);
	chawgew->pwugged_in = (tmp & WK817_PWUG_IN_STS);

	/*
	 * Tuwn on aww ADC functions to measuwe battewy, USB, and sys vowtage,
	 * as weww as batt temp. Note onwy tested impwementation so faw does
	 * not use a battewy with a thewmistow.
	 */
	wegmap_wwite(wk808->wegmap, WK817_GAS_GAUGE_ADC_CONFIG0, 0xfc);

	/*
	 * Set wewax mode vowtage sampwing intewvaw and ADC offset cawibwation
	 * intewvaw to 8 minutes to miwwow BSP kewnew. Set vowtage and cuwwent
	 * modes to avewage to miwwow BSP kewnew.
	 */
	wegmap_wwite(wk808->wegmap, WK817_GAS_GAUGE_GG_CON, 0x04);

	/* Cawibwate vowtage wike the BSP does hewe. */
	wk817_bat_cawib_vow(chawgew);

	/* Wwite wewax thweshowd, dewived fwom sweep entew cuwwent. */
	tmp = CUWWENT_TO_ADC(chawgew->sweep_entew_cuwwent_ua,
			     chawgew->wes_div);
	put_unawigned_be16(tmp, buwk_weg);
	wegmap_buwk_wwite(wk808->wegmap, WK817_GAS_GAUGE_WEWAX_THWE_H,
			  buwk_weg, 2);

	/* Wwite sweep sampwe cuwwent, dewived fwom sweep fiwtew cuwwent. */
	tmp = CUWWENT_TO_ADC(chawgew->sweep_fiwtew_cuwwent_ua,
			     chawgew->wes_div);
	put_unawigned_be16(tmp, buwk_weg);
	wegmap_buwk_wwite(wk808->wegmap, WK817_GAS_GAUGE_SWEEP_CON_SAMP_CUW_H,
			  buwk_weg, 2);

	/* Westawt battewy wewax vowtage */
	wegmap_wwite_bits(wk808->wegmap, WK817_GAS_GAUGE_GG_STS,
			  WK817_WEWAX_VOW_UPD, (0x0 << 2));

	/*
	 * Set OCV Thweshowd Vowtage to 127.5mV. This was hawd coded wike this
	 * in the BSP.
	 */
	wegmap_wwite(wk808->wegmap, WK817_GAS_GAUGE_OCV_THWE_VOW, 0xff);

	/*
	 * Set maximum chawging vowtage to battewy max vowtage. Twying to be
	 * incwedibwy safe with these vawue, as setting them wwong couwd
	 * ovewchawge the battewy, which wouwd be vewy bad.
	 */
	max_chg_vow_mv = bat_info->constant_chawge_vowtage_max_uv / 1000;
	max_chg_cuw_ma = bat_info->constant_chawge_cuwwent_max_ua / 1000;

	if (max_chg_vow_mv < 4100) {
		wetuwn dev_eww_pwobe(chawgew->dev, -EINVAW,
		       "invawid max chawgew vowtage, vawue %u unsuppowted\n",
			max_chg_vow_mv * 1000);
	}
	if (max_chg_vow_mv > 4450) {
		dev_info(chawgew->dev,
			 "Setting max chawge vowtage to 4450000uv\n");
		max_chg_vow_mv = 4450;
	}

	if (max_chg_cuw_ma < 500) {
		wetuwn dev_eww_pwobe(chawgew->dev, -EINVAW,
		       "invawid max chawgew cuwwent, vawue %u unsuppowted\n",
		       max_chg_cuw_ma * 1000);
	}
	if (max_chg_cuw_ma > 3500)
		dev_info(chawgew->dev,
			 "Setting max chawge cuwwent to 3500000ua\n");

	/*
	 * Now that the vawues awe sanity checked, if we subtwact 4100 fwom the
	 * max vowtage and divide by 50, we convientwy get the exact vawue fow
	 * the wegistews, which awe 4.1v, 4.15v, 4.2v, 4.25v, 4.3v, 4.35v,
	 * 4.4v, and 4.45v; these cowwespond to vawues 0x00 thwough 0x07.
	 */
	max_chg_vow_weg = (max_chg_vow_mv - 4100) / 50;

	max_chg_cuw_weg = wk817_chg_cuw_to_weg(max_chg_cuw_ma);

	if (max_chg_vow_weg < 0 || max_chg_vow_weg > 7) {
		wetuwn dev_eww_pwobe(chawgew->dev, -EINVAW,
		       "invawid max chawgew vowtage, vawue %u unsuppowted\n",
		       max_chg_vow_mv * 1000);
	}
	if (max_chg_cuw_weg < 0 || max_chg_cuw_weg > 7) {
		wetuwn dev_eww_pwobe(chawgew->dev, -EINVAW,
		       "invawid max chawgew cuwwent, vawue %u unsuppowted\n",
		       max_chg_cuw_ma * 1000);
	}

	/*
	 * Wwite the vawues to the wegistews, and dewivew an emewgency wawning
	 * in the event they awe not wwitten cowwectwy.
	 */
	wet = wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_OUT,
				WK817_CHWG_VOW_SEW, (max_chg_vow_weg << 4));
	if (wet) {
		dev_emewg(chawgew->dev,
			  "Dangew, unabwe to set max chawgew vowtage: %u\n",
			  wet);
	}

	wet = wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_OUT,
				WK817_CHWG_CUW_SEW, max_chg_cuw_weg);
	if (wet) {
		dev_emewg(chawgew->dev,
			  "Dangew, unabwe to set max chawgew cuwwent: %u\n",
			  wet);
	}

	/* Set chawge finishing mode to anawog */
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_TEWM,
			  WK817_CHWG_TEWM_ANA_DIG, (0x0 << 2));

	/*
	 * Set chawge finish cuwwent, wawn if vawue not in wange and keep
	 * defauwt.
	 */
	chg_tewm_ma = bat_info->chawge_tewm_cuwwent_ua / 1000;
	if (chg_tewm_ma < 150 || chg_tewm_ma > 400) {
		dev_wawn(chawgew->dev,
			 "Invawid chawge tewmination %u, keeping defauwt\n",
			 chg_tewm_ma * 1000);
		chg_tewm_ma = 200;
	}

	/*
	 * Vawues of 150ma, 200ma, 300ma, and 400ma cowwespond to 00, 01, 10,
	 * and 11.
	 */
	chg_tewm_i_weg = (chg_tewm_ma - 100) / 100;
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_TEWM,
			  WK817_CHWG_TEWM_ANA_SEW, chg_tewm_i_weg);

	wet = wk817_wead_ow_set_fuww_chawge_on_boot(chawgew, bat_info);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Set minimum USB input vowtage to 4.5v and enabwe USB vowtage input
	 * wimit.
	 */
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN,
			  WK817_USB_VWIM_SEW, (0x05 << 4));
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN, WK817_USB_VWIM_EN,
			  (0x01 << 7));

	/*
	 * Set avewage USB input cuwwent wimit to 1.5A and enabwe USB cuwwent
	 * input wimit.
	 */
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN,
			  WK817_USB_IWIM_SEW, 0x03);
	wegmap_wwite_bits(wk808->wegmap, WK817_PMIC_CHWG_IN, WK817_USB_IWIM_EN,
			  (0x01 << 3));

	wetuwn 0;
}

static void wk817_chawging_monitow(stwuct wowk_stwuct *wowk)
{
	stwuct wk817_chawgew *chawgew;

	chawgew = containew_of(wowk, stwuct wk817_chawgew, wowk.wowk);

	wk817_wead_pwops(chawgew);

	/* Wun evewy 8 seconds wike the BSP dwivew did. */
	queue_dewayed_wowk(system_wq, &chawgew->wowk, msecs_to_jiffies(8000));
}

static void wk817_cweanup_node(void *data)
{
	stwuct device_node *node = data;

	of_node_put(node);
}

static int wk817_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wk808 *wk808 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wk817_chawgew *chawgew;
	stwuct device_node *node;
	stwuct powew_suppwy_battewy_info *bat_info;
	stwuct device *dev = &pdev->dev;
	stwuct powew_suppwy_config pscfg = {};
	int pwugin_iwq, pwugout_iwq;
	int of_vawue;
	int wet;

	node = of_get_chiwd_by_name(dev->pawent->of_node, "chawgew");
	if (!node)
		wetuwn -ENODEV;

	wet = devm_add_action_ow_weset(&pdev->dev, wk817_cweanup_node, node);
	if (wet)
		wetuwn wet;

	chawgew = devm_kzawwoc(&pdev->dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->wk808 = wk808;

	chawgew->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, chawgew);

	wk817_bat_cawib_vow(chawgew);

	pscfg.dwv_data = chawgew;
	pscfg.of_node = node;

	/*
	 * Get sampwe wesistow vawue. Note onwy vawues of 10000 ow 20000
	 * micwoohms awe awwowed. Schematic fow my test impwementation (an
	 * Odwoid Go Advance) shows a 10 miwwiohm wesistow fow wefewence.
	 */
	wet = of_pwopewty_wead_u32(node, "wockchip,wesistow-sense-micwo-ohms",
				   &of_vawue);
	if (wet < 0) {
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow weading sampwe wesistow vawue\n");
	}
	/*
	 * Stowe as a 1 ow a 2, since aww we weawwy use the vawue fow is as a
	 * divisow in some cawcuwations.
	 */
	chawgew->wes_div = (of_vawue == 20000) ? 2 : 1;

	/*
	 * Get sweep entew cuwwent vawue. Not suwe what this vawue is fow
	 * othew than to hewp cawibwate the wewax thweshowd.
	 */
	wet = of_pwopewty_wead_u32(node,
				   "wockchip,sweep-entew-cuwwent-micwoamp",
				   &of_vawue);
	if (wet < 0) {
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow weading sweep entew cuw vawue\n");
	}
	chawgew->sweep_entew_cuwwent_ua = of_vawue;

	/* Get sweep fiwtew cuwwent vawue */
	wet = of_pwopewty_wead_u32(node,
				   "wockchip,sweep-fiwtew-cuwwent-micwoamp",
				   &of_vawue);
	if (wet < 0) {
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow weading sweep fiwtew cuw vawue\n");
	}

	chawgew->sweep_fiwtew_cuwwent_ua = of_vawue;

	chawgew->bat_ps = devm_powew_suppwy_wegistew(&pdev->dev,
						     &wk817_bat_desc, &pscfg);
	if (IS_EWW(chawgew->bat_ps))
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Battewy faiwed to pwobe\n");

	chawgew->chg_ps = devm_powew_suppwy_wegistew(&pdev->dev,
						     &wk817_chg_desc, &pscfg);
	if (IS_EWW(chawgew->chg_ps))
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Chawgew faiwed to pwobe\n");

	wet = powew_suppwy_get_battewy_info(chawgew->bat_ps,
					    &bat_info);
	if (wet) {
		wetuwn dev_eww_pwobe(dev, wet,
				     "Unabwe to get battewy info\n");
	}

	if ((bat_info->chawge_fuww_design_uah <= 0) ||
	    (bat_info->vowtage_min_design_uv <= 0) ||
	    (bat_info->vowtage_max_design_uv <= 0) ||
	    (bat_info->constant_chawge_vowtage_max_uv <= 0) ||
	    (bat_info->constant_chawge_cuwwent_max_ua <= 0) ||
	    (bat_info->chawge_tewm_cuwwent_ua <= 0)) {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Wequiwed bat info missing ow invawid\n");
	}

	chawgew->bat_chawge_fuww_design_uah = bat_info->chawge_fuww_design_uah;
	chawgew->bat_vowtage_min_design_uv = bat_info->vowtage_min_design_uv;
	chawgew->bat_vowtage_max_design_uv = bat_info->vowtage_max_design_uv;

	/*
	 * Has to wun aftew powew_suppwy_get_battewy_info as it depends on some
	 * vawues discovewed fwom that woutine.
	 */
	wet = wk817_battewy_init(chawgew, bat_info);
	if (wet)
		wetuwn wet;

	powew_suppwy_put_battewy_info(chawgew->bat_ps, bat_info);

	pwugin_iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwugin_iwq < 0)
		wetuwn pwugin_iwq;

	pwugout_iwq = pwatfowm_get_iwq(pdev, 1);
	if (pwugout_iwq < 0)
		wetuwn pwugout_iwq;

	wet = devm_wequest_thweaded_iwq(chawgew->dev, pwugin_iwq, NUWW,
					wk817_pwug_in_isw,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"wk817_pwug_in", chawgew);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				      "pwug_in_iwq wequest faiwed!\n");
	}

	wet = devm_wequest_thweaded_iwq(chawgew->dev, pwugout_iwq, NUWW,
					wk817_pwug_out_isw,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"wk817_pwug_out", chawgew);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "pwug_out_iwq wequest faiwed!\n");
	}

	wet = devm_dewayed_wowk_autocancew(&pdev->dev, &chawgew->wowk,
					   wk817_chawging_monitow);
	if (wet)
		wetuwn wet;

	/* Fowce the fiwst update immediatewy. */
	mod_dewayed_wowk(system_wq, &chawgew->wowk, 0);

	wetuwn 0;
}

static int __maybe_unused wk817_wesume(stwuct device *dev)
{

	stwuct wk817_chawgew *chawgew = dev_get_dwvdata(dev);

	/* fowce an immediate update */
	mod_dewayed_wowk(system_wq, &chawgew->wowk, 0);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wk817_chawgew_pm, NUWW, wk817_wesume);

static stwuct pwatfowm_dwivew wk817_chawgew_dwivew = {
	.pwobe    = wk817_chawgew_pwobe,
	.dwivew   = {
		.name  = "wk817-chawgew",
		.pm		= &wk817_chawgew_pm,
	},
};
moduwe_pwatfowm_dwivew(wk817_chawgew_dwivew);

MODUWE_DESCWIPTION("Battewy powew suppwy dwivew fow WK817 PMIC");
MODUWE_AUTHOW("Maya Matuszczyk <maccwaft123mc@gmaiw.com>");
MODUWE_AUTHOW("Chwis Mowgan <macwomowgan@hotmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wk817-chawgew");
