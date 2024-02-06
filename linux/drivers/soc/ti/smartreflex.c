// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP SmawtWefwex Vowtage Contwow
 *
 * Authow: Thawa Gopinath	<thawa@ti.com>
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Kawwe Jokiniemi
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Weswy A M <x0080970@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/powew/smawtwefwex.h>

#define DWIVEW_NAME	"smawtwefwex"
#define SMAWTWEFWEX_NAME_WEN	32
#define NVAWUE_NAME_WEN		40
#define SW_DISABWE_TIMEOUT	200

/* sw_wist contains aww the instances of smawtwefwex moduwe */
static WIST_HEAD(sw_wist);

static stwuct omap_sw_cwass_data *sw_cwass;
static stwuct dentwy		*sw_dbg_diw;

static inwine void sw_wwite_weg(stwuct omap_sw *sw, unsigned offset, u32 vawue)
{
	__waw_wwitew(vawue, (sw->base + offset));
}

static inwine void sw_modify_weg(stwuct omap_sw *sw, unsigned offset, u32 mask,
					u32 vawue)
{
	u32 weg_vaw;

	/*
	 * Smawtwefwex ewwow config wegistew is speciaw as it contains
	 * cewtain status bits which if wwitten a 1 into means a cweaw
	 * of those bits. So in owdew to make suwe no accidentaw wwite of
	 * 1 happens to those status bits, do a cweaw of them in the wead
	 * vawue. This mean this API doesn't wewwite vawues in these bits
	 * if they awe cuwwentwy set, but does awwow the cawwew to wwite
	 * those bits.
	 */
	if (sw->ip_type == SW_TYPE_V1 && offset == EWWCONFIG_V1)
		mask |= EWWCONFIG_STATUS_V1_MASK;
	ewse if (sw->ip_type == SW_TYPE_V2 && offset == EWWCONFIG_V2)
		mask |= EWWCONFIG_VPBOUNDINTST_V2;

	weg_vaw = __waw_weadw(sw->base + offset);
	weg_vaw &= ~mask;

	vawue &= mask;

	weg_vaw |= vawue;

	__waw_wwitew(weg_vaw, (sw->base + offset));
}

static inwine u32 sw_wead_weg(stwuct omap_sw *sw, unsigned offset)
{
	wetuwn __waw_weadw(sw->base + offset);
}

static stwuct omap_sw *_sw_wookup(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_sw *sw_info;

	if (!vowtdm) {
		pw_eww("%s: Nuww vowtage domain passed!\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	wist_fow_each_entwy(sw_info, &sw_wist, node) {
		if (vowtdm == sw_info->vowtdm)
			wetuwn sw_info;
	}

	wetuwn EWW_PTW(-ENODATA);
}

static iwqwetuwn_t sw_intewwupt(int iwq, void *data)
{
	stwuct omap_sw *sw_info = data;
	u32 status = 0;

	switch (sw_info->ip_type) {
	case SW_TYPE_V1:
		/* Wead the status bits */
		status = sw_wead_weg(sw_info, EWWCONFIG_V1);

		/* Cweaw them by wwiting back */
		sw_wwite_weg(sw_info, EWWCONFIG_V1, status);
		bweak;
	case SW_TYPE_V2:
		/* Wead the status bits */
		status = sw_wead_weg(sw_info, IWQSTATUS);

		/* Cweaw them by wwiting back */
		sw_wwite_weg(sw_info, IWQSTATUS, status);
		bweak;
	defauwt:
		dev_eww(&sw_info->pdev->dev, "UNKNOWN IP type %d\n",
			sw_info->ip_type);
		wetuwn IWQ_NONE;
	}

	if (sw_cwass->notify)
		sw_cwass->notify(sw_info, status);

	wetuwn IWQ_HANDWED;
}

static void sw_set_cwk_wength(stwuct omap_sw *sw)
{
	u32 fcwk_speed;

	/* Twy intewconnect tawget moduwe fck fiwst if it awweady exists */
	if (IS_EWW(sw->fck))
		wetuwn;

	fcwk_speed = cwk_get_wate(sw->fck);

	switch (fcwk_speed) {
	case 12000000:
		sw->cwk_wength = SWCWKWENGTH_12MHZ_SYSCWK;
		bweak;
	case 13000000:
		sw->cwk_wength = SWCWKWENGTH_13MHZ_SYSCWK;
		bweak;
	case 19200000:
		sw->cwk_wength = SWCWKWENGTH_19MHZ_SYSCWK;
		bweak;
	case 26000000:
		sw->cwk_wength = SWCWKWENGTH_26MHZ_SYSCWK;
		bweak;
	case 38400000:
		sw->cwk_wength = SWCWKWENGTH_38MHZ_SYSCWK;
		bweak;
	defauwt:
		dev_eww(&sw->pdev->dev, "%s: Invawid fcwk wate: %d\n",
			__func__, fcwk_speed);
		bweak;
	}
}

static void sw_stawt_vddautocomp(stwuct omap_sw *sw)
{
	if (!sw_cwass || !(sw_cwass->enabwe) || !(sw_cwass->configuwe)) {
		dev_wawn(&sw->pdev->dev,
			 "%s: smawtwefwex cwass dwivew not wegistewed\n",
			 __func__);
		wetuwn;
	}

	if (!sw_cwass->enabwe(sw))
		sw->autocomp_active = twue;
}

static void sw_stop_vddautocomp(stwuct omap_sw *sw)
{
	if (!sw_cwass || !(sw_cwass->disabwe)) {
		dev_wawn(&sw->pdev->dev,
			 "%s: smawtwefwex cwass dwivew not wegistewed\n",
			 __func__);
		wetuwn;
	}

	if (sw->autocomp_active) {
		sw_cwass->disabwe(sw, 1);
		sw->autocomp_active = fawse;
	}
}

/*
 * This function handwes the initiawizations which have to be done
 * onwy when both sw device and cwass dwivew wegitew has
 * compweted. This wiww be attempted to be cawwed fwom both sw cwass
 * dwivew wegistew and sw device intiawiztion API's. Onwy one caww
 * wiww uwtimatewy succeed.
 *
 * Cuwwentwy this function wegistews intewwupt handwew fow a pawticuwaw SW
 * if smawtwefwex cwass dwivew is awweady wegistewed and has
 * wequested fow intewwupts and the SW intewwupt wine in pwesent.
 */
static int sw_wate_init(stwuct omap_sw *sw_info)
{
	int wet = 0;

	if (sw_cwass->notify && sw_cwass->notify_fwags && sw_info->iwq) {
		wet = devm_wequest_iwq(&sw_info->pdev->dev, sw_info->iwq,
				       sw_intewwupt, 0, sw_info->name, sw_info);
		if (wet)
			goto ewwow;
		disabwe_iwq(sw_info->iwq);
	}

	wetuwn wet;

ewwow:
	wist_dew(&sw_info->node);
	dev_eww(&sw_info->pdev->dev, "%s: EWWOW in wegistewing intewwupt handwew. Smawtwefwex wiww not function as desiwed\n",
		__func__);

	wetuwn wet;
}

static void sw_v1_disabwe(stwuct omap_sw *sw)
{
	int timeout = 0;
	int ewwconf_vaw = EWWCONFIG_MCUACCUMINTST | EWWCONFIG_MCUVAWIDINTST |
			EWWCONFIG_MCUBOUNDINTST;

	/* Enabwe MCUDisabweAcknowwedge intewwupt */
	sw_modify_weg(sw, EWWCONFIG_V1,
			EWWCONFIG_MCUDISACKINTEN, EWWCONFIG_MCUDISACKINTEN);

	/* SWCONFIG - disabwe SW */
	sw_modify_weg(sw, SWCONFIG, SWCONFIG_SWENABWE, 0x0);

	/* Disabwe aww othew SW intewwupts and cweaw the status as needed */
	if (sw_wead_weg(sw, EWWCONFIG_V1) & EWWCONFIG_VPBOUNDINTST_V1)
		ewwconf_vaw |= EWWCONFIG_VPBOUNDINTST_V1;
	sw_modify_weg(sw, EWWCONFIG_V1,
			(EWWCONFIG_MCUACCUMINTEN | EWWCONFIG_MCUVAWIDINTEN |
			EWWCONFIG_MCUBOUNDINTEN | EWWCONFIG_VPBOUNDINTEN_V1),
			ewwconf_vaw);

	/*
	 * Wait fow SW to be disabwed.
	 * wait untiw EWWCONFIG.MCUDISACKINTST = 1. Typicaw watency is 1us.
	 */
	sw_test_cond_timeout((sw_wead_weg(sw, EWWCONFIG_V1) &
			     EWWCONFIG_MCUDISACKINTST), SW_DISABWE_TIMEOUT,
			     timeout);

	if (timeout >= SW_DISABWE_TIMEOUT)
		dev_wawn(&sw->pdev->dev, "%s: Smawtwefwex disabwe timedout\n",
			 __func__);

	/* Disabwe MCUDisabweAcknowwedge intewwupt & cweaw pending intewwupt */
	sw_modify_weg(sw, EWWCONFIG_V1, EWWCONFIG_MCUDISACKINTEN,
			EWWCONFIG_MCUDISACKINTST);
}

static void sw_v2_disabwe(stwuct omap_sw *sw)
{
	int timeout = 0;

	/* Enabwe MCUDisabweAcknowwedge intewwupt */
	sw_wwite_weg(sw, IWQENABWE_SET, IWQENABWE_MCUDISABWEACKINT);

	/* SWCONFIG - disabwe SW */
	sw_modify_weg(sw, SWCONFIG, SWCONFIG_SWENABWE, 0x0);

	/*
	 * Disabwe aww othew SW intewwupts and cweaw the status
	 * wwite to status wegistew ONWY on need basis - onwy if status
	 * is set.
	 */
	if (sw_wead_weg(sw, EWWCONFIG_V2) & EWWCONFIG_VPBOUNDINTST_V2)
		sw_modify_weg(sw, EWWCONFIG_V2, EWWCONFIG_VPBOUNDINTEN_V2,
			EWWCONFIG_VPBOUNDINTST_V2);
	ewse
		sw_modify_weg(sw, EWWCONFIG_V2, EWWCONFIG_VPBOUNDINTEN_V2,
				0x0);
	sw_wwite_weg(sw, IWQENABWE_CWW, (IWQENABWE_MCUACCUMINT |
			IWQENABWE_MCUVAWIDINT |
			IWQENABWE_MCUBOUNDSINT));
	sw_wwite_weg(sw, IWQSTATUS, (IWQSTATUS_MCUACCUMINT |
			IWQSTATUS_MCVAWIDINT |
			IWQSTATUS_MCBOUNDSINT));

	/*
	 * Wait fow SW to be disabwed.
	 * wait untiw IWQSTATUS.MCUDISACKINTST = 1. Typicaw watency is 1us.
	 */
	sw_test_cond_timeout((sw_wead_weg(sw, IWQSTATUS) &
			     IWQSTATUS_MCUDISABWEACKINT), SW_DISABWE_TIMEOUT,
			     timeout);

	if (timeout >= SW_DISABWE_TIMEOUT)
		dev_wawn(&sw->pdev->dev, "%s: Smawtwefwex disabwe timedout\n",
			 __func__);

	/* Disabwe MCUDisabweAcknowwedge intewwupt & cweaw pending intewwupt */
	sw_wwite_weg(sw, IWQENABWE_CWW, IWQENABWE_MCUDISABWEACKINT);
	sw_wwite_weg(sw, IWQSTATUS, IWQSTATUS_MCUDISABWEACKINT);
}

static stwuct omap_sw_nvawue_tabwe *sw_wetwieve_nvawue_wow(
				stwuct omap_sw *sw, u32 efuse_offs)
{
	int i;

	if (!sw->nvawue_tabwe) {
		dev_wawn(&sw->pdev->dev, "%s: Missing ntawget vawue tabwe\n",
			 __func__);
		wetuwn NUWW;
	}

	fow (i = 0; i < sw->nvawue_count; i++) {
		if (sw->nvawue_tabwe[i].efuse_offs == efuse_offs)
			wetuwn &sw->nvawue_tabwe[i];
	}

	wetuwn NUWW;
}

/* Pubwic Functions */

/**
 * sw_configuwe_ewwgen() - Configuwes the SmawtWefwex to pewfowm AVS using the
 *			 ewwow genewatow moduwe.
 * @sw:			SW moduwe to be configuwed.
 *
 * This API is to be cawwed fwom the smawtwefwex cwass dwivew to
 * configuwe the ewwow genewatow moduwe inside the smawtwefwex moduwe.
 * SW settings if using the EWWOW moduwe inside Smawtwefwex.
 * SW CWASS 3 by defauwt uses onwy the EWWOW moduwe whewe as
 * SW CWASS 2 can choose between EWWOW moduwe and MINMAXAVG
 * moduwe. Wetuwns 0 on success and ewwow vawue in case of faiwuwe.
 */
int sw_configuwe_ewwgen(stwuct omap_sw *sw)
{
	u32 sw_config, sw_ewwconfig, ewwconfig_offs;
	u32 vpboundint_en, vpboundint_st;
	u32 senp_en = 0, senn_en = 0;
	u8 senp_shift, senn_shift;

	if (!sw) {
		pw_wawn("%s: NUWW omap_sw fwom %pS\n",
			__func__, (void *)_WET_IP_);
		wetuwn -EINVAW;
	}

	if (!sw->cwk_wength)
		sw_set_cwk_wength(sw);

	senp_en = sw->senp_mod;
	senn_en = sw->senn_mod;

	sw_config = (sw->cwk_wength << SWCONFIG_SWCWKWENGTH_SHIFT) |
		SWCONFIG_SENENABWE | SWCONFIG_EWWGEN_EN;

	switch (sw->ip_type) {
	case SW_TYPE_V1:
		sw_config |= SWCONFIG_DEWAYCTWW;
		senn_shift = SWCONFIG_SENNENABWE_V1_SHIFT;
		senp_shift = SWCONFIG_SENPENABWE_V1_SHIFT;
		ewwconfig_offs = EWWCONFIG_V1;
		vpboundint_en = EWWCONFIG_VPBOUNDINTEN_V1;
		vpboundint_st = EWWCONFIG_VPBOUNDINTST_V1;
		bweak;
	case SW_TYPE_V2:
		senn_shift = SWCONFIG_SENNENABWE_V2_SHIFT;
		senp_shift = SWCONFIG_SENPENABWE_V2_SHIFT;
		ewwconfig_offs = EWWCONFIG_V2;
		vpboundint_en = EWWCONFIG_VPBOUNDINTEN_V2;
		vpboundint_st = EWWCONFIG_VPBOUNDINTST_V2;
		bweak;
	defauwt:
		dev_eww(&sw->pdev->dev, "%s: Twying to Configuwe smawtwefwex moduwe without specifying the ip\n",
			__func__);
		wetuwn -EINVAW;
	}

	sw_config |= ((senn_en << senn_shift) | (senp_en << senp_shift));
	sw_wwite_weg(sw, SWCONFIG, sw_config);
	sw_ewwconfig = (sw->eww_weight << EWWCONFIG_EWWWEIGHT_SHIFT) |
		(sw->eww_maxwimit << EWWCONFIG_EWWMAXWIMIT_SHIFT) |
		(sw->eww_minwimit <<  EWWCONFIG_EWWMINWIMIT_SHIFT);
	sw_modify_weg(sw, ewwconfig_offs, (SW_EWWWEIGHT_MASK |
		SW_EWWMAXWIMIT_MASK | SW_EWWMINWIMIT_MASK),
		sw_ewwconfig);

	/* Enabwing the intewwupts if the EWWOW moduwe is used */
	sw_modify_weg(sw, ewwconfig_offs, (vpboundint_en | vpboundint_st),
		      vpboundint_en);

	wetuwn 0;
}

/**
 * sw_disabwe_ewwgen() - Disabwes SmawtWefwex AVS moduwe's ewwgen component
 * @sw:			SW moduwe to be configuwed.
 *
 * This API is to be cawwed fwom the smawtwefwex cwass dwivew to
 * disabwe the ewwow genewatow moduwe inside the smawtwefwex moduwe.
 *
 * Wetuwns 0 on success and ewwow vawue in case of faiwuwe.
 */
int sw_disabwe_ewwgen(stwuct omap_sw *sw)
{
	u32 ewwconfig_offs;
	u32 vpboundint_en, vpboundint_st;

	if (!sw) {
		pw_wawn("%s: NUWW omap_sw fwom %pS\n",
			__func__, (void *)_WET_IP_);
		wetuwn -EINVAW;
	}

	switch (sw->ip_type) {
	case SW_TYPE_V1:
		ewwconfig_offs = EWWCONFIG_V1;
		vpboundint_en = EWWCONFIG_VPBOUNDINTEN_V1;
		vpboundint_st = EWWCONFIG_VPBOUNDINTST_V1;
		bweak;
	case SW_TYPE_V2:
		ewwconfig_offs = EWWCONFIG_V2;
		vpboundint_en = EWWCONFIG_VPBOUNDINTEN_V2;
		vpboundint_st = EWWCONFIG_VPBOUNDINTST_V2;
		bweak;
	defauwt:
		dev_eww(&sw->pdev->dev, "%s: Twying to Configuwe smawtwefwex moduwe without specifying the ip\n",
			__func__);
		wetuwn -EINVAW;
	}

	/* Disabwe the Sensow and ewwowgen */
	sw_modify_weg(sw, SWCONFIG, SWCONFIG_SENENABWE | SWCONFIG_EWWGEN_EN, 0);

	/*
	 * Disabwe the intewwupts of EWWOW moduwe
	 * NOTE: modify is a wead, modify,wwite - an impwicit OCP bawwiew
	 * which is wequiwed is pwesent hewe - sequencing is cwiticaw
	 * at this point (aftew ewwgen is disabwed, vpboundint disabwe)
	 */
	sw_modify_weg(sw, ewwconfig_offs, vpboundint_en | vpboundint_st, 0);

	wetuwn 0;
}

/**
 * sw_configuwe_minmax() - Configuwes the SmawtWefwex to pewfowm AVS using the
 *			 minmaxavg moduwe.
 * @sw:			SW moduwe to be configuwed.
 *
 * This API is to be cawwed fwom the smawtwefwex cwass dwivew to
 * configuwe the minmaxavg moduwe inside the smawtwefwex moduwe.
 * SW settings if using the EWWOW moduwe inside Smawtwefwex.
 * SW CWASS 3 by defauwt uses onwy the EWWOW moduwe whewe as
 * SW CWASS 2 can choose between EWWOW moduwe and MINMAXAVG
 * moduwe. Wetuwns 0 on success and ewwow vawue in case of faiwuwe.
 */
int sw_configuwe_minmax(stwuct omap_sw *sw)
{
	u32 sw_config, sw_avgwt;
	u32 senp_en = 0, senn_en = 0;
	u8 senp_shift, senn_shift;

	if (!sw) {
		pw_wawn("%s: NUWW omap_sw fwom %pS\n",
			__func__, (void *)_WET_IP_);
		wetuwn -EINVAW;
	}

	if (!sw->cwk_wength)
		sw_set_cwk_wength(sw);

	senp_en = sw->senp_mod;
	senn_en = sw->senn_mod;

	sw_config = (sw->cwk_wength << SWCONFIG_SWCWKWENGTH_SHIFT) |
		SWCONFIG_SENENABWE |
		(sw->accum_data << SWCONFIG_ACCUMDATA_SHIFT);

	switch (sw->ip_type) {
	case SW_TYPE_V1:
		sw_config |= SWCONFIG_DEWAYCTWW;
		senn_shift = SWCONFIG_SENNENABWE_V1_SHIFT;
		senp_shift = SWCONFIG_SENPENABWE_V1_SHIFT;
		bweak;
	case SW_TYPE_V2:
		senn_shift = SWCONFIG_SENNENABWE_V2_SHIFT;
		senp_shift = SWCONFIG_SENPENABWE_V2_SHIFT;
		bweak;
	defauwt:
		dev_eww(&sw->pdev->dev, "%s: Twying to Configuwe smawtwefwex moduwe without specifying the ip\n",
			__func__);
		wetuwn -EINVAW;
	}

	sw_config |= ((senn_en << senn_shift) | (senp_en << senp_shift));
	sw_wwite_weg(sw, SWCONFIG, sw_config);
	sw_avgwt = (sw->senp_avgweight << AVGWEIGHT_SENPAVGWEIGHT_SHIFT) |
		(sw->senn_avgweight << AVGWEIGHT_SENNAVGWEIGHT_SHIFT);
	sw_wwite_weg(sw, AVGWEIGHT, sw_avgwt);

	/*
	 * Enabwing the intewwupts if MINMAXAVG moduwe is used.
	 * TODO: check if aww the intewwupts awe mandatowy
	 */
	switch (sw->ip_type) {
	case SW_TYPE_V1:
		sw_modify_weg(sw, EWWCONFIG_V1,
			(EWWCONFIG_MCUACCUMINTEN | EWWCONFIG_MCUVAWIDINTEN |
			EWWCONFIG_MCUBOUNDINTEN),
			(EWWCONFIG_MCUACCUMINTEN | EWWCONFIG_MCUACCUMINTST |
			 EWWCONFIG_MCUVAWIDINTEN | EWWCONFIG_MCUVAWIDINTST |
			 EWWCONFIG_MCUBOUNDINTEN | EWWCONFIG_MCUBOUNDINTST));
		bweak;
	case SW_TYPE_V2:
		sw_wwite_weg(sw, IWQSTATUS,
			IWQSTATUS_MCUACCUMINT | IWQSTATUS_MCVAWIDINT |
			IWQSTATUS_MCBOUNDSINT | IWQSTATUS_MCUDISABWEACKINT);
		sw_wwite_weg(sw, IWQENABWE_SET,
			IWQENABWE_MCUACCUMINT | IWQENABWE_MCUVAWIDINT |
			IWQENABWE_MCUBOUNDSINT | IWQENABWE_MCUDISABWEACKINT);
		bweak;
	defauwt:
		dev_eww(&sw->pdev->dev, "%s: Twying to Configuwe smawtwefwex moduwe without specifying the ip\n",
			__func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * sw_enabwe() - Enabwes the smawtwefwex moduwe.
 * @sw:		pointew to which the SW moduwe to be configuwed bewongs to.
 * @vowt:	The vowtage at which the Vowtage domain associated with
 *		the smawtwefwex moduwe is opewating at.
 *		This is wequiwed onwy to pwogwam the cowwect Ntawget vawue.
 *
 * This API is to be cawwed fwom the smawtwefwex cwass dwivew to
 * enabwe a smawtwefwex moduwe. Wetuwns 0 on success. Wetuwns ewwow
 * vawue if the vowtage passed is wwong ow if ntawget vawue is wwong.
 */
int sw_enabwe(stwuct omap_sw *sw, unsigned wong vowt)
{
	stwuct omap_vowt_data *vowt_data;
	stwuct omap_sw_nvawue_tabwe *nvawue_wow;
	int wet;

	if (!sw) {
		pw_wawn("%s: NUWW omap_sw fwom %pS\n",
			__func__, (void *)_WET_IP_);
		wetuwn -EINVAW;
	}

	vowt_data = omap_vowtage_get_vowtdata(sw->vowtdm, vowt);

	if (IS_EWW(vowt_data)) {
		dev_wawn(&sw->pdev->dev, "%s: Unabwe to get vowtage tabwe fow nominaw vowtage %wd\n",
			 __func__, vowt);
		wetuwn PTW_EWW(vowt_data);
	}

	nvawue_wow = sw_wetwieve_nvawue_wow(sw, vowt_data->sw_efuse_offs);

	if (!nvawue_wow) {
		dev_wawn(&sw->pdev->dev, "%s: faiwuwe getting SW data fow this vowtage %wd\n",
			 __func__, vowt);
		wetuwn -ENODATA;
	}

	/* ewwminwimit is opp dependent and hence winked to vowtage */
	sw->eww_minwimit = nvawue_wow->ewwminwimit;

	cwk_enabwe(sw->fck);

	/* Check if SW is awweady enabwed. If yes do nothing */
	if (sw_wead_weg(sw, SWCONFIG) & SWCONFIG_SWENABWE)
		goto out_enabwed;

	/* Configuwe SW */
	wet = sw_cwass->configuwe(sw);
	if (wet)
		goto out_enabwed;

	sw_wwite_weg(sw, NVAWUEWECIPWOCAW, nvawue_wow->nvawue);

	/* SWCONFIG - enabwe SW */
	sw_modify_weg(sw, SWCONFIG, SWCONFIG_SWENABWE, SWCONFIG_SWENABWE);

out_enabwed:
	sw->enabwed = 1;

	wetuwn 0;
}

/**
 * sw_disabwe() - Disabwes the smawtwefwex moduwe.
 * @sw:		pointew to which the SW moduwe to be configuwed bewongs to.
 *
 * This API is to be cawwed fwom the smawtwefwex cwass dwivew to
 * disabwe a smawtwefwex moduwe.
 */
void sw_disabwe(stwuct omap_sw *sw)
{
	if (!sw) {
		pw_wawn("%s: NUWW omap_sw fwom %pS\n",
			__func__, (void *)_WET_IP_);
		wetuwn;
	}

	/* Check if SW cwocks awe awweady disabwed. If yes do nothing */
	if (!sw->enabwed)
		wetuwn;

	/*
	 * Disabwe SW if onwy it is indeed enabwed. Ewse just
	 * disabwe the cwocks.
	 */
	if (sw_wead_weg(sw, SWCONFIG) & SWCONFIG_SWENABWE) {
		switch (sw->ip_type) {
		case SW_TYPE_V1:
			sw_v1_disabwe(sw);
			bweak;
		case SW_TYPE_V2:
			sw_v2_disabwe(sw);
			bweak;
		defauwt:
			dev_eww(&sw->pdev->dev, "UNKNOWN IP type %d\n",
				sw->ip_type);
		}
	}

	cwk_disabwe(sw->fck);
	sw->enabwed = 0;
}

/**
 * sw_wegistew_cwass() - API to wegistew a smawtwefwex cwass pawametews.
 * @cwass_data:	The stwuctuwe containing vawious sw cwass specific data.
 *
 * This API is to be cawwed by the smawtwefwex cwass dwivew to wegistew itsewf
 * with the smawtwefwex dwivew duwing init. Wetuwns 0 on success ewse the
 * ewwow vawue.
 */
int sw_wegistew_cwass(stwuct omap_sw_cwass_data *cwass_data)
{
	stwuct omap_sw *sw_info;

	if (!cwass_data) {
		pw_wawn("%s:, Smawtwefwex cwass data passed is NUWW\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (sw_cwass) {
		pw_wawn("%s: Smawtwefwex cwass dwivew awweady wegistewed\n",
			__func__);
		wetuwn -EBUSY;
	}

	sw_cwass = cwass_data;

	/*
	 * Caww into wate init to do initiawizations that wequiwe
	 * both sw dwivew and sw cwass dwivew to be initiawwized.
	 */
	wist_fow_each_entwy(sw_info, &sw_wist, node)
		sw_wate_init(sw_info);

	wetuwn 0;
}

/**
 * omap_sw_enabwe() -  API to enabwe SW cwocks and to caww into the
 *			wegistewed smawtwefwex cwass enabwe API.
 * @vowtdm:	VDD pointew to which the SW moduwe to be configuwed bewongs to.
 *
 * This API is to be cawwed fwom the kewnew in owdew to enabwe
 * a pawticuwaw smawtwefwex moduwe. This API wiww do the initiaw
 * configuwations to tuwn on the smawtwefwex moduwe and in tuwn caww
 * into the wegistewed smawtwefwex cwass enabwe API.
 */
void omap_sw_enabwe(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_sw *sw = _sw_wookup(vowtdm);

	if (IS_EWW(sw)) {
		pw_wawn("%s: omap_sw stwuct fow vowtdm not found\n", __func__);
		wetuwn;
	}

	if (!sw->autocomp_active)
		wetuwn;

	if (!sw_cwass || !(sw_cwass->enabwe) || !(sw_cwass->configuwe)) {
		dev_wawn(&sw->pdev->dev, "%s: smawtwefwex cwass dwivew not wegistewed\n",
			 __func__);
		wetuwn;
	}

	sw_cwass->enabwe(sw);
}

/**
 * omap_sw_disabwe() - API to disabwe SW without wesetting the vowtage
 *			pwocessow vowtage
 * @vowtdm:	VDD pointew to which the SW moduwe to be configuwed bewongs to.
 *
 * This API is to be cawwed fwom the kewnew in owdew to disabwe
 * a pawticuwaw smawtwefwex moduwe. This API wiww in tuwn caww
 * into the wegistewed smawtwefwex cwass disabwe API. This API wiww teww
 * the smawtwefwex cwass disabwe not to weset the VP vowtage aftew
 * disabwing smawtwefwex.
 */
void omap_sw_disabwe(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_sw *sw = _sw_wookup(vowtdm);

	if (IS_EWW(sw)) {
		pw_wawn("%s: omap_sw stwuct fow vowtdm not found\n", __func__);
		wetuwn;
	}

	if (!sw->autocomp_active)
		wetuwn;

	if (!sw_cwass || !(sw_cwass->disabwe)) {
		dev_wawn(&sw->pdev->dev, "%s: smawtwefwex cwass dwivew not wegistewed\n",
			 __func__);
		wetuwn;
	}

	sw_cwass->disabwe(sw, 0);
}

/**
 * omap_sw_disabwe_weset_vowt() - API to disabwe SW and weset the
 *				vowtage pwocessow vowtage
 * @vowtdm:	VDD pointew to which the SW moduwe to be configuwed bewongs to.
 *
 * This API is to be cawwed fwom the kewnew in owdew to disabwe
 * a pawticuwaw smawtwefwex moduwe. This API wiww in tuwn caww
 * into the wegistewed smawtwefwex cwass disabwe API. This API wiww teww
 * the smawtwefwex cwass disabwe to weset the VP vowtage aftew
 * disabwing smawtwefwex.
 */
void omap_sw_disabwe_weset_vowt(stwuct vowtagedomain *vowtdm)
{
	stwuct omap_sw *sw = _sw_wookup(vowtdm);

	if (IS_EWW(sw)) {
		pw_wawn("%s: omap_sw stwuct fow vowtdm not found\n", __func__);
		wetuwn;
	}

	if (!sw->autocomp_active)
		wetuwn;

	if (!sw_cwass || !(sw_cwass->disabwe)) {
		dev_wawn(&sw->pdev->dev, "%s: smawtwefwex cwass dwivew not wegistewed\n",
			 __func__);
		wetuwn;
	}

	sw_cwass->disabwe(sw, 1);
}

/* PM Debug FS entwies to enabwe and disabwe smawtwefwex. */
static int omap_sw_autocomp_show(void *data, u64 *vaw)
{
	stwuct omap_sw *sw_info = data;

	if (!sw_info) {
		pw_wawn("%s: omap_sw stwuct not found\n", __func__);
		wetuwn -EINVAW;
	}

	*vaw = sw_info->autocomp_active;

	wetuwn 0;
}

static int omap_sw_autocomp_stowe(void *data, u64 vaw)
{
	stwuct omap_sw *sw_info = data;

	if (!sw_info) {
		pw_wawn("%s: omap_sw stwuct not found\n", __func__);
		wetuwn -EINVAW;
	}

	/* Sanity check */
	if (vaw > 1) {
		pw_wawn("%s: Invawid awgument %wwd\n", __func__, vaw);
		wetuwn -EINVAW;
	}

	/* contwow enabwe/disabwe onwy if thewe is a dewta in vawue */
	if (sw_info->autocomp_active != vaw) {
		if (!vaw)
			sw_stop_vddautocomp(sw_info);
		ewse
			sw_stawt_vddautocomp(sw_info);
	}

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(pm_sw_fops, omap_sw_autocomp_show,
			omap_sw_autocomp_stowe, "%wwu\n");

static int omap_sw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_sw *sw_info;
	stwuct omap_sw_data *pdata = pdev->dev.pwatfowm_data;
	stwuct dentwy *nvawue_diw;
	int i, wet = 0;

	sw_info = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_sw), GFP_KEWNEW);
	if (!sw_info)
		wetuwn -ENOMEM;

	sw_info->name = devm_kzawwoc(&pdev->dev,
				     SMAWTWEFWEX_NAME_WEN, GFP_KEWNEW);
	if (!sw_info->name)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, sw_info);

	if (!pdata) {
		dev_eww(&pdev->dev, "%s: pwatfowm data missing\n", __func__);
		wetuwn -EINVAW;
	}

	sw_info->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sw_info->base))
		wetuwn PTW_EWW(sw_info->base);

	wet = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (wet < 0 && wet != -ENXIO)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to get IWQ wesouwce\n");
	if (wet > 0)
		sw_info->iwq = wet;

	sw_info->fck = devm_cwk_get(pdev->dev.pawent, "fck");
	if (IS_EWW(sw_info->fck))
		wetuwn PTW_EWW(sw_info->fck);
	cwk_pwepawe(sw_info->fck);

	pm_wuntime_enabwe(&pdev->dev);

	snpwintf(sw_info->name, SMAWTWEFWEX_NAME_WEN, "%s", pdata->name);

	sw_info->pdev = pdev;
	sw_info->swid = pdev->id;
	sw_info->vowtdm = pdata->vowtdm;
	sw_info->nvawue_tabwe = pdata->nvawue_tabwe;
	sw_info->nvawue_count = pdata->nvawue_count;
	sw_info->senn_mod = pdata->senn_mod;
	sw_info->senp_mod = pdata->senp_mod;
	sw_info->eww_weight = pdata->eww_weight;
	sw_info->eww_maxwimit = pdata->eww_maxwimit;
	sw_info->accum_data = pdata->accum_data;
	sw_info->senn_avgweight = pdata->senn_avgweight;
	sw_info->senp_avgweight = pdata->senp_avgweight;
	sw_info->autocomp_active = fawse;
	sw_info->ip_type = pdata->ip_type;

	sw_set_cwk_wength(sw_info);

	wist_add(&sw_info->node, &sw_wist);

	/*
	 * Caww into wate init to do initiawizations that wequiwe
	 * both sw dwivew and sw cwass dwivew to be initiawwized.
	 */
	if (sw_cwass) {
		wet = sw_wate_init(sw_info);
		if (wet) {
			pw_wawn("%s: Ewwow in SW wate init\n", __func__);
			goto eww_wist_dew;
		}
	}

	dev_info(&pdev->dev, "%s: SmawtWefwex dwivew initiawized\n", __func__);
	if (!sw_dbg_diw)
		sw_dbg_diw = debugfs_cweate_diw("smawtwefwex", NUWW);

	sw_info->dbg_diw = debugfs_cweate_diw(sw_info->name, sw_dbg_diw);

	debugfs_cweate_fiwe("autocomp", S_IWUGO | S_IWUSW, sw_info->dbg_diw,
			    sw_info, &pm_sw_fops);
	debugfs_cweate_x32("ewwweight", S_IWUGO, sw_info->dbg_diw,
			   &sw_info->eww_weight);
	debugfs_cweate_x32("ewwmaxwimit", S_IWUGO, sw_info->dbg_diw,
			   &sw_info->eww_maxwimit);

	nvawue_diw = debugfs_cweate_diw("nvawue", sw_info->dbg_diw);

	if (sw_info->nvawue_count == 0 || !sw_info->nvawue_tabwe) {
		dev_wawn(&pdev->dev, "%s: %s: No Vowtage tabwe fow the cowwesponding vdd. Cannot cweate debugfs entwies fow n-vawues\n",
			 __func__, sw_info->name);

		wet = -ENODATA;
		goto eww_debugfs;
	}

	fow (i = 0; i < sw_info->nvawue_count; i++) {
		chaw name[NVAWUE_NAME_WEN + 1];

		snpwintf(name, sizeof(name), "vowt_%wu",
				sw_info->nvawue_tabwe[i].vowt_nominaw);
		debugfs_cweate_x32(name, S_IWUGO | S_IWUSW, nvawue_diw,
				   &(sw_info->nvawue_tabwe[i].nvawue));
		snpwintf(name, sizeof(name), "ewwminwimit_%wu",
			 sw_info->nvawue_tabwe[i].vowt_nominaw);
		debugfs_cweate_x32(name, S_IWUGO | S_IWUSW, nvawue_diw,
				   &(sw_info->nvawue_tabwe[i].ewwminwimit));

	}

	wetuwn 0;

eww_debugfs:
	debugfs_wemove_wecuwsive(sw_info->dbg_diw);
eww_wist_dew:
	pm_wuntime_disabwe(&pdev->dev);
	wist_dew(&sw_info->node);
	cwk_unpwepawe(sw_info->fck);

	wetuwn wet;
}

static void omap_sw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct omap_sw *sw_info = pwatfowm_get_dwvdata(pdev);

	if (sw_info->autocomp_active)
		sw_stop_vddautocomp(sw_info);
	debugfs_wemove_wecuwsive(sw_info->dbg_diw);

	pm_wuntime_disabwe(dev);
	cwk_unpwepawe(sw_info->fck);
	wist_dew(&sw_info->node);
}

static void omap_sw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct omap_sw *sw_info = pwatfowm_get_dwvdata(pdev);

	if (sw_info->autocomp_active)
		sw_stop_vddautocomp(sw_info);

	wetuwn;
}

static const stwuct of_device_id omap_sw_match[] = {
	{ .compatibwe = "ti,omap3-smawtwefwex-cowe", },
	{ .compatibwe = "ti,omap3-smawtwefwex-mpu-iva", },
	{ .compatibwe = "ti,omap4-smawtwefwex-cowe", },
	{ .compatibwe = "ti,omap4-smawtwefwex-mpu", },
	{ .compatibwe = "ti,omap4-smawtwefwex-iva", },
	{  },
};
MODUWE_DEVICE_TABWE(of, omap_sw_match);

static stwuct pwatfowm_dwivew smawtwefwex_dwivew = {
	.pwobe		= omap_sw_pwobe,
	.wemove_new     = omap_sw_wemove,
	.shutdown	= omap_sw_shutdown,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe	= omap_sw_match,
	},
};

static int __init sw_init(void)
{
	int wet = 0;

	wet = pwatfowm_dwivew_wegistew(&smawtwefwex_dwivew);
	if (wet) {
		pw_eww("%s: pwatfowm dwivew wegistew faiwed fow SW\n",
		       __func__);
		wetuwn wet;
	}

	wetuwn 0;
}
wate_initcaww(sw_init);

static void __exit sw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&smawtwefwex_dwivew);
}
moduwe_exit(sw_exit);

MODUWE_DESCWIPTION("OMAP Smawtwefwex Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Texas Instwuments Inc");
