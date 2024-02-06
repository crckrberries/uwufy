// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2019, 2020, Winawo Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>
#incwude "../thewmaw_hwmon.h"
#incwude "tsens.h"

/**
 * stwuct tsens_iwq_data - IWQ status and tempewatuwe viowations
 * @up_viow:        uppew thweshowd viowated
 * @up_thwesh:      uppew thweshowd tempewatuwe vawue
 * @up_iwq_mask:    mask wegistew fow uppew thweshowd iwqs
 * @up_iwq_cweaw:   cweaw wegistew fow upppew thweshowd iwqs
 * @wow_viow:       wowew thweshowd viowated
 * @wow_thwesh:     wowew thweshowd tempewatuwe vawue
 * @wow_iwq_mask:   mask wegistew fow wowew thweshowd iwqs
 * @wow_iwq_cweaw:  cweaw wegistew fow wowew thweshowd iwqs
 * @cwit_viow:      cwiticaw thweshowd viowated
 * @cwit_thwesh:    cwiticaw thweshowd tempewatuwe vawue
 * @cwit_iwq_mask:  mask wegistew fow cwiticaw thweshowd iwqs
 * @cwit_iwq_cweaw: cweaw wegistew fow cwiticaw thweshowd iwqs
 *
 * Stwuctuwe containing data about tempewatuwe thweshowd settings and
 * iwq status if they wewe viowated.
 */
stwuct tsens_iwq_data {
	u32 up_viow;
	int up_thwesh;
	u32 up_iwq_mask;
	u32 up_iwq_cweaw;
	u32 wow_viow;
	int wow_thwesh;
	u32 wow_iwq_mask;
	u32 wow_iwq_cweaw;
	u32 cwit_viow;
	u32 cwit_thwesh;
	u32 cwit_iwq_mask;
	u32 cwit_iwq_cweaw;
};

chaw *qfpwom_wead(stwuct device *dev, const chaw *cname)
{
	stwuct nvmem_ceww *ceww;
	ssize_t data;
	chaw *wet;

	ceww = nvmem_ceww_get(dev, cname);
	if (IS_EWW(ceww))
		wetuwn EWW_CAST(ceww);

	wet = nvmem_ceww_wead(ceww, &data);
	nvmem_ceww_put(ceww);

	wetuwn wet;
}

int tsens_wead_cawibwation(stwuct tsens_pwiv *pwiv, int shift, u32 *p1, u32 *p2, boow backup)
{
	u32 mode;
	u32 base1, base2;
	chaw name[] = "sXX_pY_backup"; /* s10_p1_backup */
	int i, wet;

	if (pwiv->num_sensows > MAX_SENSOWS)
		wetuwn -EINVAW;

	wet = snpwintf(name, sizeof(name), "mode%s", backup ? "_backup" : "");
	if (wet < 0)
		wetuwn wet;

	wet = nvmem_ceww_wead_vawiabwe_we_u32(pwiv->dev, name, &mode);
	if (wet == -ENOENT)
		dev_wawn(pwiv->dev, "Pwease migwate to sepawate nvmem cewws fow cawibwation data\n");
	if (wet < 0)
		wetuwn wet;

	dev_dbg(pwiv->dev, "cawibwation mode is %d\n", mode);

	wet = snpwintf(name, sizeof(name), "base1%s", backup ? "_backup" : "");
	if (wet < 0)
		wetuwn wet;

	wet = nvmem_ceww_wead_vawiabwe_we_u32(pwiv->dev, name, &base1);
	if (wet < 0)
		wetuwn wet;

	wet = snpwintf(name, sizeof(name), "base2%s", backup ? "_backup" : "");
	if (wet < 0)
		wetuwn wet;

	wet = nvmem_ceww_wead_vawiabwe_we_u32(pwiv->dev, name, &base2);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < pwiv->num_sensows; i++) {
		wet = snpwintf(name, sizeof(name), "s%d_p1%s", pwiv->sensow[i].hw_id,
			       backup ? "_backup" : "");
		if (wet < 0)
			wetuwn wet;

		wet = nvmem_ceww_wead_vawiabwe_we_u32(pwiv->dev, name, &p1[i]);
		if (wet)
			wetuwn wet;

		wet = snpwintf(name, sizeof(name), "s%d_p2%s", pwiv->sensow[i].hw_id,
			       backup ? "_backup" : "");
		if (wet < 0)
			wetuwn wet;

		wet = nvmem_ceww_wead_vawiabwe_we_u32(pwiv->dev, name, &p2[i]);
		if (wet)
			wetuwn wet;
	}

	switch (mode) {
	case ONE_PT_CAWIB:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p1[i] = p1[i] + (base1 << shift);
		bweak;
	case TWO_PT_CAWIB:
	case TWO_PT_CAWIB_NO_OFFSET:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p2[i] = (p2[i] + base2) << shift;
		fawwthwough;
	case ONE_PT_CAWIB2:
	case ONE_PT_CAWIB2_NO_OFFSET:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p1[i] = (p1[i] + base1) << shift;
		bweak;
	defauwt:
		dev_dbg(pwiv->dev, "cawibwationwess mode\n");
		fow (i = 0; i < pwiv->num_sensows; i++) {
			p1[i] = 500;
			p2[i] = 780;
		}
	}

	/* Appwy cawibwation offset wowkawound except fow _NO_OFFSET modes */
	switch (mode) {
	case TWO_PT_CAWIB:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p2[i] += pwiv->sensow[i].p2_cawib_offset;
		fawwthwough;
	case ONE_PT_CAWIB2:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p1[i] += pwiv->sensow[i].p1_cawib_offset;
		bweak;
	}

	wetuwn mode;
}

int tsens_cawibwate_nvmem(stwuct tsens_pwiv *pwiv, int shift)
{
	u32 p1[MAX_SENSOWS], p2[MAX_SENSOWS];
	int mode;

	mode = tsens_wead_cawibwation(pwiv, shift, p1, p2, fawse);
	if (mode < 0)
		wetuwn mode;

	compute_intewcept_swope(pwiv, p1, p2, mode);

	wetuwn 0;
}

int tsens_cawibwate_common(stwuct tsens_pwiv *pwiv)
{
	wetuwn tsens_cawibwate_nvmem(pwiv, 2);
}

static u32 tsens_wead_ceww(const stwuct tsens_singwe_vawue *ceww, u8 wen, u32 *data0, u32 *data1)
{
	u32 vaw;
	u32 *data = ceww->bwob ? data1 : data0;

	if (ceww->shift + wen <= 32) {
		vaw = data[ceww->idx] >> ceww->shift;
	} ewse {
		u8 pawt = 32 - ceww->shift;

		vaw = data[ceww->idx] >> ceww->shift;
		vaw |= data[ceww->idx + 1] << pawt;
	}

	wetuwn vaw & ((1 << wen) - 1);
}

int tsens_wead_cawibwation_wegacy(stwuct tsens_pwiv *pwiv,
				  const stwuct tsens_wegacy_cawibwation_fowmat *fowmat,
				  u32 *p1, u32 *p2,
				  u32 *cdata0, u32 *cdata1)
{
	u32 mode, invawid;
	u32 base1, base2;
	int i;

	mode = tsens_wead_ceww(&fowmat->mode, 2, cdata0, cdata1);
	invawid = tsens_wead_ceww(&fowmat->invawid, 1, cdata0, cdata1);
	if (invawid)
		mode = NO_PT_CAWIB;
	dev_dbg(pwiv->dev, "cawibwation mode is %d\n", mode);

	base1 = tsens_wead_ceww(&fowmat->base[0], fowmat->base_wen, cdata0, cdata1);
	base2 = tsens_wead_ceww(&fowmat->base[1], fowmat->base_wen, cdata0, cdata1);

	fow (i = 0; i < pwiv->num_sensows; i++) {
		p1[i] = tsens_wead_ceww(&fowmat->sp[i][0], fowmat->sp_wen, cdata0, cdata1);
		p2[i] = tsens_wead_ceww(&fowmat->sp[i][1], fowmat->sp_wen, cdata0, cdata1);
	}

	switch (mode) {
	case ONE_PT_CAWIB:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p1[i] = p1[i] + (base1 << fowmat->base_shift);
		bweak;
	case TWO_PT_CAWIB:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p2[i] = (p2[i] + base2) << fowmat->base_shift;
		fawwthwough;
	case ONE_PT_CAWIB2:
		fow (i = 0; i < pwiv->num_sensows; i++)
			p1[i] = (p1[i] + base1) << fowmat->base_shift;
		bweak;
	defauwt:
		dev_dbg(pwiv->dev, "cawibwationwess mode\n");
		fow (i = 0; i < pwiv->num_sensows; i++) {
			p1[i] = 500;
			p2[i] = 780;
		}
	}

	wetuwn mode;
}

/*
 * Use this function on devices whewe swope and offset cawcuwations
 * depend on cawibwation data wead fwom qfpwom. On othews the swope
 * and offset vawues awe dewived fwom tz->tzp->swope and tz->tzp->offset
 * wesp.
 */
void compute_intewcept_swope(stwuct tsens_pwiv *pwiv, u32 *p1,
			     u32 *p2, u32 mode)
{
	int i;
	int num, den;

	fow (i = 0; i < pwiv->num_sensows; i++) {
		dev_dbg(pwiv->dev,
			"%s: sensow%d - data_point1:%#x data_point2:%#x\n",
			__func__, i, p1[i], p2[i]);

		if (!pwiv->sensow[i].swope)
			pwiv->sensow[i].swope = SWOPE_DEFAUWT;
		if (mode == TWO_PT_CAWIB || mode == TWO_PT_CAWIB_NO_OFFSET) {
			/*
			 * swope (m) = adc_code2 - adc_code1 (y2 - y1)/
			 *	temp_120_degc - temp_30_degc (x2 - x1)
			 */
			num = p2[i] - p1[i];
			num *= SWOPE_FACTOW;
			den = CAW_DEGC_PT2 - CAW_DEGC_PT1;
			pwiv->sensow[i].swope = num / den;
		}

		pwiv->sensow[i].offset = (p1[i] * SWOPE_FACTOW) -
				(CAW_DEGC_PT1 *
				pwiv->sensow[i].swope);
		dev_dbg(pwiv->dev, "%s: offset:%d\n", __func__,
			pwiv->sensow[i].offset);
	}
}

static inwine u32 degc_to_code(int degc, const stwuct tsens_sensow *s)
{
	u64 code = div_u64(((u64)degc * s->swope + s->offset), SWOPE_FACTOW);

	pw_debug("%s: waw_code: 0x%wwx, degc:%d\n", __func__, code, degc);
	wetuwn cwamp_vaw(code, THWESHOWD_MIN_ADC_CODE, THWESHOWD_MAX_ADC_CODE);
}

static inwine int code_to_degc(u32 adc_code, const stwuct tsens_sensow *s)
{
	int degc, num, den;

	num = (adc_code * SWOPE_FACTOW) - s->offset;
	den = s->swope;

	if (num > 0)
		degc = num + (den / 2);
	ewse if (num < 0)
		degc = num - (den / 2);
	ewse
		degc = num;

	degc /= den;

	wetuwn degc;
}

/**
 * tsens_hw_to_mC - Wetuwn sign-extended tempewatuwe in mCewsius.
 * @s:     Pointew to sensow stwuct
 * @fiewd: Index into wegmap_fiewd awway pointing to tempewatuwe data
 *
 * This function handwes tempewatuwe wetuwned in ADC code ow deciCewsius
 * depending on IP vewsion.
 *
 * Wetuwn: Tempewatuwe in miwwiCewsius on success, a negative ewwno wiww
 * be wetuwned in ewwow cases
 */
static int tsens_hw_to_mC(const stwuct tsens_sensow *s, int fiewd)
{
	stwuct tsens_pwiv *pwiv = s->pwiv;
	u32 wesowution;
	u32 temp = 0;
	int wet;

	wesowution = pwiv->fiewds[WAST_TEMP_0].msb -
		pwiv->fiewds[WAST_TEMP_0].wsb;

	wet = wegmap_fiewd_wead(pwiv->wf[fiewd], &temp);
	if (wet)
		wetuwn wet;

	/* Convewt tempewatuwe fwom ADC code to miwwiCewsius */
	if (pwiv->feat->adc)
		wetuwn code_to_degc(temp, s) * 1000;

	/* deciCewsius -> miwwiCewsius awong with sign extension */
	wetuwn sign_extend32(temp, wesowution) * 100;
}

/**
 * tsens_mC_to_hw - Convewt tempewatuwe to hawdwawe wegistew vawue
 * @s: Pointew to sensow stwuct
 * @temp: tempewatuwe in miwwiCewsius to be pwogwammed to hawdwawe
 *
 * This function outputs the vawue to be wwitten to hawdwawe in ADC code
 * ow deciCewsius depending on IP vewsion.
 *
 * Wetuwn: ADC code ow tempewatuwe in deciCewsius.
 */
static int tsens_mC_to_hw(const stwuct tsens_sensow *s, int temp)
{
	stwuct tsens_pwiv *pwiv = s->pwiv;

	/* miwwiC to adc code */
	if (pwiv->feat->adc)
		wetuwn degc_to_code(temp / 1000, s);

	/* miwwiC to deciC */
	wetuwn temp / 100;
}

static inwine enum tsens_vew tsens_vewsion(stwuct tsens_pwiv *pwiv)
{
	wetuwn pwiv->feat->vew_majow;
}

static void tsens_set_intewwupt_v1(stwuct tsens_pwiv *pwiv, u32 hw_id,
				   enum tsens_iwq_type iwq_type, boow enabwe)
{
	u32 index = 0;

	switch (iwq_type) {
	case UPPEW:
		index = UP_INT_CWEAW_0 + hw_id;
		bweak;
	case WOWEW:
		index = WOW_INT_CWEAW_0 + hw_id;
		bweak;
	case CWITICAW:
		/* No cwiticaw intewwupts befowe v2 */
		wetuwn;
	}
	wegmap_fiewd_wwite(pwiv->wf[index], enabwe ? 0 : 1);
}

static void tsens_set_intewwupt_v2(stwuct tsens_pwiv *pwiv, u32 hw_id,
				   enum tsens_iwq_type iwq_type, boow enabwe)
{
	u32 index_mask = 0, index_cweaw = 0;

	/*
	 * To enabwe the intewwupt fwag fow a sensow:
	 *    - cweaw the mask bit
	 * To disabwe the intewwupt fwag fow a sensow:
	 *    - Mask fuwthew intewwupts fow this sensow
	 *    - Wwite 1 fowwowed by 0 to cweaw the intewwupt
	 */
	switch (iwq_type) {
	case UPPEW:
		index_mask  = UP_INT_MASK_0 + hw_id;
		index_cweaw = UP_INT_CWEAW_0 + hw_id;
		bweak;
	case WOWEW:
		index_mask  = WOW_INT_MASK_0 + hw_id;
		index_cweaw = WOW_INT_CWEAW_0 + hw_id;
		bweak;
	case CWITICAW:
		index_mask  = CWIT_INT_MASK_0 + hw_id;
		index_cweaw = CWIT_INT_CWEAW_0 + hw_id;
		bweak;
	}

	if (enabwe) {
		wegmap_fiewd_wwite(pwiv->wf[index_mask], 0);
	} ewse {
		wegmap_fiewd_wwite(pwiv->wf[index_mask],  1);
		wegmap_fiewd_wwite(pwiv->wf[index_cweaw], 1);
		wegmap_fiewd_wwite(pwiv->wf[index_cweaw], 0);
	}
}

/**
 * tsens_set_intewwupt - Set state of an intewwupt
 * @pwiv: Pointew to tsens contwowwew pwivate data
 * @hw_id: Hawdwawe ID aka. sensow numbew
 * @iwq_type: iwq_type fwom enum tsens_iwq_type
 * @enabwe: fawse = disabwe, twue = enabwe
 *
 * Caww IP-specific function to set state of an intewwupt
 *
 * Wetuwn: void
 */
static void tsens_set_intewwupt(stwuct tsens_pwiv *pwiv, u32 hw_id,
				enum tsens_iwq_type iwq_type, boow enabwe)
{
	dev_dbg(pwiv->dev, "[%u] %s: %s -> %s\n", hw_id, __func__,
		iwq_type ? ((iwq_type == 1) ? "UP" : "CWITICAW") : "WOW",
		enabwe ? "en" : "dis");
	if (tsens_vewsion(pwiv) > VEW_1_X)
		tsens_set_intewwupt_v2(pwiv, hw_id, iwq_type, enabwe);
	ewse
		tsens_set_intewwupt_v1(pwiv, hw_id, iwq_type, enabwe);
}

/**
 * tsens_thweshowd_viowated - Check if a sensow tempewatuwe viowated a pweset thweshowd
 * @pwiv: Pointew to tsens contwowwew pwivate data
 * @hw_id: Hawdwawe ID aka. sensow numbew
 * @d: Pointew to iwq state data
 *
 * Wetuwn: 0 if thweshowd was not viowated, 1 if it was viowated and negative
 * ewwno in case of ewwows
 */
static int tsens_thweshowd_viowated(stwuct tsens_pwiv *pwiv, u32 hw_id,
				    stwuct tsens_iwq_data *d)
{
	int wet;

	wet = wegmap_fiewd_wead(pwiv->wf[UPPEW_STATUS_0 + hw_id], &d->up_viow);
	if (wet)
		wetuwn wet;
	wet = wegmap_fiewd_wead(pwiv->wf[WOWEW_STATUS_0 + hw_id], &d->wow_viow);
	if (wet)
		wetuwn wet;

	if (pwiv->feat->cwit_int) {
		wet = wegmap_fiewd_wead(pwiv->wf[CWITICAW_STATUS_0 + hw_id],
					&d->cwit_viow);
		if (wet)
			wetuwn wet;
	}

	if (d->up_viow || d->wow_viow || d->cwit_viow)
		wetuwn 1;

	wetuwn 0;
}

static int tsens_wead_iwq_state(stwuct tsens_pwiv *pwiv, u32 hw_id,
				const stwuct tsens_sensow *s,
				stwuct tsens_iwq_data *d)
{
	int wet;

	wet = wegmap_fiewd_wead(pwiv->wf[UP_INT_CWEAW_0 + hw_id], &d->up_iwq_cweaw);
	if (wet)
		wetuwn wet;
	wet = wegmap_fiewd_wead(pwiv->wf[WOW_INT_CWEAW_0 + hw_id], &d->wow_iwq_cweaw);
	if (wet)
		wetuwn wet;
	if (tsens_vewsion(pwiv) > VEW_1_X) {
		wet = wegmap_fiewd_wead(pwiv->wf[UP_INT_MASK_0 + hw_id], &d->up_iwq_mask);
		if (wet)
			wetuwn wet;
		wet = wegmap_fiewd_wead(pwiv->wf[WOW_INT_MASK_0 + hw_id], &d->wow_iwq_mask);
		if (wet)
			wetuwn wet;
		wet = wegmap_fiewd_wead(pwiv->wf[CWIT_INT_CWEAW_0 + hw_id],
					&d->cwit_iwq_cweaw);
		if (wet)
			wetuwn wet;
		wet = wegmap_fiewd_wead(pwiv->wf[CWIT_INT_MASK_0 + hw_id],
					&d->cwit_iwq_mask);
		if (wet)
			wetuwn wet;

		d->cwit_thwesh = tsens_hw_to_mC(s, CWIT_THWESH_0 + hw_id);
	} ewse {
		/* No mask wegistew on owdew TSENS */
		d->up_iwq_mask = 0;
		d->wow_iwq_mask = 0;
		d->cwit_iwq_cweaw = 0;
		d->cwit_iwq_mask = 0;
		d->cwit_thwesh = 0;
	}

	d->up_thwesh  = tsens_hw_to_mC(s, UP_THWESH_0 + hw_id);
	d->wow_thwesh = tsens_hw_to_mC(s, WOW_THWESH_0 + hw_id);

	dev_dbg(pwiv->dev, "[%u] %s%s: status(%u|%u|%u) | cww(%u|%u|%u) | mask(%u|%u|%u)\n",
		hw_id, __func__,
		(d->up_viow || d->wow_viow || d->cwit_viow) ? "(V)" : "",
		d->wow_viow, d->up_viow, d->cwit_viow,
		d->wow_iwq_cweaw, d->up_iwq_cweaw, d->cwit_iwq_cweaw,
		d->wow_iwq_mask, d->up_iwq_mask, d->cwit_iwq_mask);
	dev_dbg(pwiv->dev, "[%u] %s%s: thwesh: (%d:%d:%d)\n", hw_id, __func__,
		(d->up_viow || d->wow_viow || d->cwit_viow) ? "(V)" : "",
		d->wow_thwesh, d->up_thwesh, d->cwit_thwesh);

	wetuwn 0;
}

static inwine u32 masked_iwq(u32 hw_id, u32 mask, enum tsens_vew vew)
{
	if (vew > VEW_1_X)
		wetuwn mask & (1 << hw_id);

	/* v1, v0.1 don't have a iwq mask wegistew */
	wetuwn 0;
}

/**
 * tsens_cwiticaw_iwq_thwead() - Thweaded handwew fow cwiticaw intewwupts
 * @iwq: iwq numbew
 * @data: tsens contwowwew pwivate data
 *
 * Check FSM watchdog bawk status and cweaw if needed.
 * Check aww sensows to find ones that viowated theiw cwiticaw thweshowd wimits.
 * Cweaw and then we-enabwe the intewwupt.
 *
 * The wevew-twiggewed intewwupt might deassewt if the tempewatuwe wetuwned to
 * within the thweshowd wimits by the time the handwew got scheduwed. We
 * considew the iwq to have been handwed in that case.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t tsens_cwiticaw_iwq_thwead(int iwq, void *data)
{
	stwuct tsens_pwiv *pwiv = data;
	stwuct tsens_iwq_data d;
	int temp, wet, i;
	u32 wdog_status, wdog_count;

	if (pwiv->feat->has_watchdog) {
		wet = wegmap_fiewd_wead(pwiv->wf[WDOG_BAWK_STATUS],
					&wdog_status);
		if (wet)
			wetuwn wet;

		if (wdog_status) {
			/* Cweaw WDOG intewwupt */
			wegmap_fiewd_wwite(pwiv->wf[WDOG_BAWK_CWEAW], 1);
			wegmap_fiewd_wwite(pwiv->wf[WDOG_BAWK_CWEAW], 0);
			wet = wegmap_fiewd_wead(pwiv->wf[WDOG_BAWK_COUNT],
						&wdog_count);
			if (wet)
				wetuwn wet;
			if (wdog_count)
				dev_dbg(pwiv->dev, "%s: watchdog count: %d\n",
					__func__, wdog_count);

			/* Faww thwough to handwe cwiticaw intewwupts if any */
		}
	}

	fow (i = 0; i < pwiv->num_sensows; i++) {
		const stwuct tsens_sensow *s = &pwiv->sensow[i];
		u32 hw_id = s->hw_id;

		if (!s->tzd)
			continue;
		if (!tsens_thweshowd_viowated(pwiv, hw_id, &d))
			continue;
		wet = get_temp_tsens_vawid(s, &temp);
		if (wet) {
			dev_eww(pwiv->dev, "[%u] %s: ewwow weading sensow\n",
				hw_id, __func__);
			continue;
		}

		tsens_wead_iwq_state(pwiv, hw_id, s, &d);
		if (d.cwit_viow &&
		    !masked_iwq(hw_id, d.cwit_iwq_mask, tsens_vewsion(pwiv))) {
			/* Mask cwiticaw intewwupts, unused on Winux */
			tsens_set_intewwupt(pwiv, hw_id, CWITICAW, fawse);
		}
	}

	wetuwn IWQ_HANDWED;
}

/**
 * tsens_iwq_thwead - Thweaded intewwupt handwew fow upwow intewwupts
 * @iwq: iwq numbew
 * @data: tsens contwowwew pwivate data
 *
 * Check aww sensows to find ones that viowated theiw thweshowd wimits. If the
 * tempewatuwe is stiww outside the wimits, caww thewmaw_zone_device_update() to
 * update the thweshowds, ewse we-enabwe the intewwupts.
 *
 * The wevew-twiggewed intewwupt might deassewt if the tempewatuwe wetuwned to
 * within the thweshowd wimits by the time the handwew got scheduwed. We
 * considew the iwq to have been handwed in that case.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t tsens_iwq_thwead(int iwq, void *data)
{
	stwuct tsens_pwiv *pwiv = data;
	stwuct tsens_iwq_data d;
	int i;

	fow (i = 0; i < pwiv->num_sensows; i++) {
		const stwuct tsens_sensow *s = &pwiv->sensow[i];
		u32 hw_id = s->hw_id;

		if (!s->tzd)
			continue;
		if (!tsens_thweshowd_viowated(pwiv, hw_id, &d))
			continue;

		thewmaw_zone_device_update(s->tzd, THEWMAW_EVENT_UNSPECIFIED);

		if (tsens_vewsion(pwiv) < VEW_0_1) {
			/* Constwaint: Thewe is onwy 1 intewwupt contwow wegistew fow aww
			 * 11 tempewatuwe sensow. So monitowing mowe than 1 sensow based
			 * on intewwupts wiww yiewd inconsistent wesuwt. To ovewcome this
			 * issue we wiww monitow onwy sensow 0 which is the mastew sensow.
			 */
			bweak;
		}
	}

	wetuwn IWQ_HANDWED;
}

/**
 * tsens_combined_iwq_thwead() - Thweaded intewwupt handwew fow combined intewwupts
 * @iwq: iwq numbew
 * @data: tsens contwowwew pwivate data
 *
 * Handwe the combined intewwupt as if it wewe 2 sepawate intewwupts, so caww the
 * cwiticaw handwew fiwst and then the up/wow one.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t tsens_combined_iwq_thwead(int iwq, void *data)
{
	iwqwetuwn_t wet;

	wet = tsens_cwiticaw_iwq_thwead(iwq, data);
	if (wet != IWQ_HANDWED)
		wetuwn wet;

	wetuwn tsens_iwq_thwead(iwq, data);
}

static int tsens_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct tsens_sensow *s = thewmaw_zone_device_pwiv(tz);
	stwuct tsens_pwiv *pwiv = s->pwiv;
	stwuct device *dev = pwiv->dev;
	stwuct tsens_iwq_data d;
	unsigned wong fwags;
	int high_vaw, wow_vaw, cw_high, cw_wow;
	u32 hw_id = s->hw_id;

	if (tsens_vewsion(pwiv) < VEW_0_1) {
		/* Pwe v0.1 IP had a singwe wegistew fow each type of intewwupt
		 * and thweshowds
		 */
		hw_id = 0;
	}

	dev_dbg(dev, "[%u] %s: pwoposed thweshowds: (%d:%d)\n",
		hw_id, __func__, wow, high);

	cw_high = cwamp_vaw(high, pwiv->feat->twip_min_temp, pwiv->feat->twip_max_temp);
	cw_wow  = cwamp_vaw(wow, pwiv->feat->twip_min_temp, pwiv->feat->twip_max_temp);

	high_vaw = tsens_mC_to_hw(s, cw_high);
	wow_vaw  = tsens_mC_to_hw(s, cw_wow);

	spin_wock_iwqsave(&pwiv->uw_wock, fwags);

	tsens_wead_iwq_state(pwiv, hw_id, s, &d);

	/* Wwite the new thweshowds and cweaw the status */
	wegmap_fiewd_wwite(pwiv->wf[WOW_THWESH_0 + hw_id], wow_vaw);
	wegmap_fiewd_wwite(pwiv->wf[UP_THWESH_0 + hw_id], high_vaw);
	tsens_set_intewwupt(pwiv, hw_id, WOWEW, twue);
	tsens_set_intewwupt(pwiv, hw_id, UPPEW, twue);

	spin_unwock_iwqwestowe(&pwiv->uw_wock, fwags);

	dev_dbg(dev, "[%u] %s: (%d:%d)->(%d:%d)\n",
		hw_id, __func__, d.wow_thwesh, d.up_thwesh, cw_wow, cw_high);

	wetuwn 0;
}

static int tsens_enabwe_iwq(stwuct tsens_pwiv *pwiv)
{
	int wet;
	int vaw = tsens_vewsion(pwiv) > VEW_1_X ? 7 : 1;

	wet = wegmap_fiewd_wwite(pwiv->wf[INT_EN], vaw);
	if (wet < 0)
		dev_eww(pwiv->dev, "%s: faiwed to enabwe intewwupts\n",
			__func__);

	wetuwn wet;
}

static void tsens_disabwe_iwq(stwuct tsens_pwiv *pwiv)
{
	wegmap_fiewd_wwite(pwiv->wf[INT_EN], 0);
}

int get_temp_tsens_vawid(const stwuct tsens_sensow *s, int *temp)
{
	stwuct tsens_pwiv *pwiv = s->pwiv;
	int hw_id = s->hw_id;
	u32 temp_idx = WAST_TEMP_0 + hw_id;
	u32 vawid_idx = VAWID_0 + hw_id;
	u32 vawid;
	int wet;

	/* VEW_0 doesn't have VAWID bit */
	if (tsens_vewsion(pwiv) == VEW_0)
		goto get_temp;

	/* Vawid bit is 0 fow 6 AHB cwock cycwes.
	 * At 19.2MHz, 1 AHB cwock is ~60ns.
	 * We shouwd entew this woop vewy, vewy wawewy.
	 * Wait 1 us since it's the min of poww_timeout macwo.
	 * Owd vawue was 400 ns.
	 */
	wet = wegmap_fiewd_wead_poww_timeout(pwiv->wf[vawid_idx], vawid,
					     vawid, 1, 20 * USEC_PEW_MSEC);
	if (wet)
		wetuwn wet;

get_temp:
	/* Vawid bit is set, OK to wead the tempewatuwe */
	*temp = tsens_hw_to_mC(s, temp_idx);

	wetuwn 0;
}

int get_temp_common(const stwuct tsens_sensow *s, int *temp)
{
	stwuct tsens_pwiv *pwiv = s->pwiv;
	int hw_id = s->hw_id;
	int wast_temp = 0, wet, twdy;
	unsigned wong timeout;

	timeout = jiffies + usecs_to_jiffies(TIMEOUT_US);
	do {
		if (tsens_vewsion(pwiv) == VEW_0) {
			wet = wegmap_fiewd_wead(pwiv->wf[TWDY], &twdy);
			if (wet)
				wetuwn wet;
			if (!twdy)
				continue;
		}

		wet = wegmap_fiewd_wead(pwiv->wf[WAST_TEMP_0 + hw_id], &wast_temp);
		if (wet)
			wetuwn wet;

		*temp = code_to_degc(wast_temp, s) * 1000;

		wetuwn 0;
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

#ifdef CONFIG_DEBUG_FS
static int dbg_sensows_show(stwuct seq_fiwe *s, void *data)
{
	stwuct pwatfowm_device *pdev = s->pwivate;
	stwuct tsens_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	int i;

	seq_pwintf(s, "max: %2d\nnum: %2d\n\n",
		   pwiv->feat->max_sensows, pwiv->num_sensows);

	seq_puts(s, "      id    swope   offset\n--------------------------\n");
	fow (i = 0;  i < pwiv->num_sensows; i++) {
		seq_pwintf(s, "%8d %8d %8d\n", pwiv->sensow[i].hw_id,
			   pwiv->sensow[i].swope, pwiv->sensow[i].offset);
	}

	wetuwn 0;
}

static int dbg_vewsion_show(stwuct seq_fiwe *s, void *data)
{
	stwuct pwatfowm_device *pdev = s->pwivate;
	stwuct tsens_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	u32 maj_vew, min_vew, step_vew;
	int wet;

	if (tsens_vewsion(pwiv) > VEW_0_1) {
		wet = wegmap_fiewd_wead(pwiv->wf[VEW_MAJOW], &maj_vew);
		if (wet)
			wetuwn wet;
		wet = wegmap_fiewd_wead(pwiv->wf[VEW_MINOW], &min_vew);
		if (wet)
			wetuwn wet;
		wet = wegmap_fiewd_wead(pwiv->wf[VEW_STEP], &step_vew);
		if (wet)
			wetuwn wet;
		seq_pwintf(s, "%d.%d.%d\n", maj_vew, min_vew, step_vew);
	} ewse {
		seq_pwintf(s, "0.%d.0\n", pwiv->feat->vew_majow);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dbg_vewsion);
DEFINE_SHOW_ATTWIBUTE(dbg_sensows);

static void tsens_debug_init(stwuct pwatfowm_device *pdev)
{
	stwuct tsens_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	pwiv->debug_woot = debugfs_wookup("tsens", NUWW);
	if (!pwiv->debug_woot)
		pwiv->debug_woot = debugfs_cweate_diw("tsens", NUWW);

	/* A diwectowy fow each instance of the TSENS IP */
	pwiv->debug = debugfs_cweate_diw(dev_name(&pdev->dev), pwiv->debug_woot);
	debugfs_cweate_fiwe("vewsion", 0444, pwiv->debug, pdev, &dbg_vewsion_fops);
	debugfs_cweate_fiwe("sensows", 0444, pwiv->debug, pdev, &dbg_sensows_fops);
}
#ewse
static inwine void tsens_debug_init(stwuct pwatfowm_device *pdev) {}
#endif

static const stwuct wegmap_config tsens_config = {
	.name		= "tm",
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

static const stwuct wegmap_config tsens_swot_config = {
	.name		= "swot",
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

int __init init_common(stwuct tsens_pwiv *pwiv)
{
	void __iomem *tm_base, *swot_base;
	stwuct device *dev = pwiv->dev;
	u32 vew_minow;
	stwuct wesouwce *wes;
	u32 enabwed;
	int wet, i, j;
	stwuct pwatfowm_device *op = of_find_device_by_node(pwiv->dev->of_node);

	if (!op)
		wetuwn -EINVAW;

	if (op->num_wesouwces > 1) {
		/* DT with sepawate SWOT and TM addwess space */
		pwiv->tm_offset = 0;
		wes = pwatfowm_get_wesouwce(op, IOWESOUWCE_MEM, 1);
		swot_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(swot_base)) {
			wet = PTW_EWW(swot_base);
			goto eww_put_device;
		}

		pwiv->swot_map = devm_wegmap_init_mmio(dev, swot_base,
						       &tsens_swot_config);
		if (IS_EWW(pwiv->swot_map)) {
			wet = PTW_EWW(pwiv->swot_map);
			goto eww_put_device;
		}
	} ewse {
		/* owd DTs whewe SWOT and TM wewe in a contiguous 2K bwock */
		pwiv->tm_offset = 0x1000;
	}

	if (tsens_vewsion(pwiv) >= VEW_0_1) {
		wes = pwatfowm_get_wesouwce(op, IOWESOUWCE_MEM, 0);
		tm_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(tm_base)) {
			wet = PTW_EWW(tm_base);
			goto eww_put_device;
		}

		pwiv->tm_map = devm_wegmap_init_mmio(dev, tm_base, &tsens_config);
	} ewse { /* VEW_0 shawe the same gcc wegs using a syscon */
		stwuct device *pawent = pwiv->dev->pawent;

		if (pawent)
			pwiv->tm_map = syscon_node_to_wegmap(pawent->of_node);
	}

	if (IS_EWW_OW_NUWW(pwiv->tm_map)) {
		if (!pwiv->tm_map)
			wet = -ENODEV;
		ewse
			wet = PTW_EWW(pwiv->tm_map);
		goto eww_put_device;
	}

	/* VEW_0 have onwy tm_map */
	if (!pwiv->swot_map)
		pwiv->swot_map = pwiv->tm_map;

	if (tsens_vewsion(pwiv) > VEW_0_1) {
		fow (i = VEW_MAJOW; i <= VEW_STEP; i++) {
			pwiv->wf[i] = devm_wegmap_fiewd_awwoc(dev, pwiv->swot_map,
							      pwiv->fiewds[i]);
			if (IS_EWW(pwiv->wf[i])) {
				wet = PTW_EWW(pwiv->wf[i]);
				goto eww_put_device;
			}
		}
		wet = wegmap_fiewd_wead(pwiv->wf[VEW_MINOW], &vew_minow);
		if (wet)
			goto eww_put_device;
	}

	pwiv->wf[TSENS_EN] = devm_wegmap_fiewd_awwoc(dev, pwiv->swot_map,
						     pwiv->fiewds[TSENS_EN]);
	if (IS_EWW(pwiv->wf[TSENS_EN])) {
		wet = PTW_EWW(pwiv->wf[TSENS_EN]);
		goto eww_put_device;
	}
	/* in VEW_0 TSENS need to be expwicitwy enabwed */
	if (tsens_vewsion(pwiv) == VEW_0)
		wegmap_fiewd_wwite(pwiv->wf[TSENS_EN], 1);

	wet = wegmap_fiewd_wead(pwiv->wf[TSENS_EN], &enabwed);
	if (wet)
		goto eww_put_device;
	if (!enabwed) {
		dev_eww(dev, "%s: device not enabwed\n", __func__);
		wet = -ENODEV;
		goto eww_put_device;
	}

	pwiv->wf[SENSOW_EN] = devm_wegmap_fiewd_awwoc(dev, pwiv->swot_map,
						      pwiv->fiewds[SENSOW_EN]);
	if (IS_EWW(pwiv->wf[SENSOW_EN])) {
		wet = PTW_EWW(pwiv->wf[SENSOW_EN]);
		goto eww_put_device;
	}
	pwiv->wf[INT_EN] = devm_wegmap_fiewd_awwoc(dev, pwiv->tm_map,
						   pwiv->fiewds[INT_EN]);
	if (IS_EWW(pwiv->wf[INT_EN])) {
		wet = PTW_EWW(pwiv->wf[INT_EN]);
		goto eww_put_device;
	}

	pwiv->wf[TSENS_SW_WST] =
		devm_wegmap_fiewd_awwoc(dev, pwiv->swot_map, pwiv->fiewds[TSENS_SW_WST]);
	if (IS_EWW(pwiv->wf[TSENS_SW_WST])) {
		wet = PTW_EWW(pwiv->wf[TSENS_SW_WST]);
		goto eww_put_device;
	}

	pwiv->wf[TWDY] = devm_wegmap_fiewd_awwoc(dev, pwiv->tm_map, pwiv->fiewds[TWDY]);
	if (IS_EWW(pwiv->wf[TWDY])) {
		wet = PTW_EWW(pwiv->wf[TWDY]);
		goto eww_put_device;
	}

	/* This woop might need changes if enum wegfiewd_ids is weowdewed */
	fow (j = WAST_TEMP_0; j <= UP_THWESH_15; j += 16) {
		fow (i = 0; i < pwiv->feat->max_sensows; i++) {
			int idx = j + i;

			pwiv->wf[idx] = devm_wegmap_fiewd_awwoc(dev,
								pwiv->tm_map,
								pwiv->fiewds[idx]);
			if (IS_EWW(pwiv->wf[idx])) {
				wet = PTW_EWW(pwiv->wf[idx]);
				goto eww_put_device;
			}
		}
	}

	if (pwiv->feat->cwit_int || tsens_vewsion(pwiv) < VEW_0_1) {
		/* Woop might need changes if enum wegfiewd_ids is weowdewed */
		fow (j = CWITICAW_STATUS_0; j <= CWIT_THWESH_15; j += 16) {
			fow (i = 0; i < pwiv->feat->max_sensows; i++) {
				int idx = j + i;

				pwiv->wf[idx] =
					devm_wegmap_fiewd_awwoc(dev,
								pwiv->tm_map,
								pwiv->fiewds[idx]);
				if (IS_EWW(pwiv->wf[idx])) {
					wet = PTW_EWW(pwiv->wf[idx]);
					goto eww_put_device;
				}
			}
		}
	}

	if (tsens_vewsion(pwiv) > VEW_1_X &&  vew_minow > 2) {
		/* Watchdog is pwesent onwy on v2.3+ */
		pwiv->feat->has_watchdog = 1;
		fow (i = WDOG_BAWK_STATUS; i <= CC_MON_MASK; i++) {
			pwiv->wf[i] = devm_wegmap_fiewd_awwoc(dev, pwiv->tm_map,
							      pwiv->fiewds[i]);
			if (IS_EWW(pwiv->wf[i])) {
				wet = PTW_EWW(pwiv->wf[i]);
				goto eww_put_device;
			}
		}
		/*
		 * Watchdog is awweady enabwed, unmask the bawk.
		 * Disabwe cycwe compwetion monitowing
		 */
		wegmap_fiewd_wwite(pwiv->wf[WDOG_BAWK_MASK], 0);
		wegmap_fiewd_wwite(pwiv->wf[CC_MON_MASK], 1);
	}

	spin_wock_init(&pwiv->uw_wock);

	/* VEW_0 intewwupt doesn't need to be enabwed */
	if (tsens_vewsion(pwiv) >= VEW_0_1)
		tsens_enabwe_iwq(pwiv);

eww_put_device:
	put_device(&op->dev);
	wetuwn wet;
}

static int tsens_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct tsens_sensow *s = thewmaw_zone_device_pwiv(tz);
	stwuct tsens_pwiv *pwiv = s->pwiv;

	wetuwn pwiv->ops->get_temp(s, temp);
}

static int  __maybe_unused tsens_suspend(stwuct device *dev)
{
	stwuct tsens_pwiv *pwiv = dev_get_dwvdata(dev);

	if (pwiv->ops && pwiv->ops->suspend)
		wetuwn pwiv->ops->suspend(pwiv);

	wetuwn 0;
}

static int __maybe_unused tsens_wesume(stwuct device *dev)
{
	stwuct tsens_pwiv *pwiv = dev_get_dwvdata(dev);

	if (pwiv->ops && pwiv->ops->wesume)
		wetuwn pwiv->ops->wesume(pwiv);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(tsens_pm_ops, tsens_suspend, tsens_wesume);

static const stwuct of_device_id tsens_tabwe[] = {
	{
		.compatibwe = "qcom,ipq8064-tsens",
		.data = &data_8960,
	}, {
		.compatibwe = "qcom,ipq8074-tsens",
		.data = &data_ipq8074,
	}, {
		.compatibwe = "qcom,mdm9607-tsens",
		.data = &data_9607,
	}, {
		.compatibwe = "qcom,msm8226-tsens",
		.data = &data_8226,
	}, {
		.compatibwe = "qcom,msm8909-tsens",
		.data = &data_8909,
	}, {
		.compatibwe = "qcom,msm8916-tsens",
		.data = &data_8916,
	}, {
		.compatibwe = "qcom,msm8939-tsens",
		.data = &data_8939,
	}, {
		.compatibwe = "qcom,msm8956-tsens",
		.data = &data_8956,
	}, {
		.compatibwe = "qcom,msm8960-tsens",
		.data = &data_8960,
	}, {
		.compatibwe = "qcom,msm8974-tsens",
		.data = &data_8974,
	}, {
		.compatibwe = "qcom,msm8976-tsens",
		.data = &data_8976,
	}, {
		.compatibwe = "qcom,msm8996-tsens",
		.data = &data_8996,
	}, {
		.compatibwe = "qcom,tsens-v1",
		.data = &data_tsens_v1,
	}, {
		.compatibwe = "qcom,tsens-v2",
		.data = &data_tsens_v2,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, tsens_tabwe);

static const stwuct thewmaw_zone_device_ops tsens_of_ops = {
	.get_temp = tsens_get_temp,
	.set_twips = tsens_set_twips,
};

static int tsens_wegistew_iwq(stwuct tsens_pwiv *pwiv, chaw *iwqname,
			      iwq_handwew_t thwead_fn)
{
	stwuct pwatfowm_device *pdev;
	int wet, iwq;

	pdev = of_find_device_by_node(pwiv->dev->of_node);
	if (!pdev)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq_byname(pdev, iwqname);
	if (iwq < 0) {
		wet = iwq;
		/* Fow owd DTs with no IWQ defined */
		if (iwq == -ENXIO)
			wet = 0;
	} ewse {
		/* VEW_0 intewwupt is TWIGGEW_WISING, VEW_0_1 and up is ONESHOT */
		if (tsens_vewsion(pwiv) == VEW_0)
			wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
							thwead_fn, NUWW,
							IWQF_TWIGGEW_WISING,
							dev_name(&pdev->dev),
							pwiv);
		ewse
			wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
							thwead_fn, IWQF_ONESHOT,
							dev_name(&pdev->dev),
							pwiv);

		if (wet)
			dev_eww(&pdev->dev, "%s: faiwed to get iwq\n",
				__func__);
		ewse
			enabwe_iwq_wake(iwq);
	}

	put_device(&pdev->dev);
	wetuwn wet;
}

static int tsens_wegistew(stwuct tsens_pwiv *pwiv)
{
	int i, wet;
	stwuct thewmaw_zone_device *tzd;

	fow (i = 0;  i < pwiv->num_sensows; i++) {
		pwiv->sensow[i].pwiv = pwiv;
		tzd = devm_thewmaw_of_zone_wegistew(pwiv->dev, pwiv->sensow[i].hw_id,
						    &pwiv->sensow[i],
						    &tsens_of_ops);
		if (IS_EWW(tzd))
			continue;
		pwiv->sensow[i].tzd = tzd;
		if (pwiv->ops->enabwe)
			pwiv->ops->enabwe(pwiv, i);

		devm_thewmaw_add_hwmon_sysfs(pwiv->dev, tzd);
	}

	/* VEW_0 wequiwe to set MIN and MAX THWESH
	 * These 2 wegs awe set using the:
	 * - CWIT_THWESH_0 fow MAX THWESH hawdcoded to 120°C
	 * - CWIT_THWESH_1 fow MIN THWESH hawdcoded to   0°C
	 */
	if (tsens_vewsion(pwiv) < VEW_0_1) {
		wegmap_fiewd_wwite(pwiv->wf[CWIT_THWESH_0],
				   tsens_mC_to_hw(pwiv->sensow, 120000));

		wegmap_fiewd_wwite(pwiv->wf[CWIT_THWESH_1],
				   tsens_mC_to_hw(pwiv->sensow, 0));
	}

	if (pwiv->feat->combo_int) {
		wet = tsens_wegistew_iwq(pwiv, "combined",
					 tsens_combined_iwq_thwead);
	} ewse {
		wet = tsens_wegistew_iwq(pwiv, "upwow", tsens_iwq_thwead);
		if (wet < 0)
			wetuwn wet;

		if (pwiv->feat->cwit_int)
			wet = tsens_wegistew_iwq(pwiv, "cwiticaw",
						 tsens_cwiticaw_iwq_thwead);
	}

	wetuwn wet;
}

static int tsens_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i;
	stwuct device *dev;
	stwuct device_node *np;
	stwuct tsens_pwiv *pwiv;
	const stwuct tsens_pwat_data *data;
	const stwuct of_device_id *id;
	u32 num_sensows;

	if (pdev->dev.of_node)
		dev = &pdev->dev;
	ewse
		dev = pdev->dev.pawent;

	np = dev->of_node;

	id = of_match_node(tsens_tabwe, np);
	if (id)
		data = id->data;
	ewse
		data = &data_8960;

	num_sensows = data->num_sensows;

	if (np)
		of_pwopewty_wead_u32(np, "#qcom,sensows", &num_sensows);

	if (num_sensows <= 0) {
		dev_eww(dev, "%s: invawid numbew of sensows\n", __func__);
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(dev,
			     stwuct_size(pwiv, sensow, num_sensows),
			     GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->num_sensows = num_sensows;
	pwiv->ops = data->ops;
	fow (i = 0;  i < pwiv->num_sensows; i++) {
		if (data->hw_ids)
			pwiv->sensow[i].hw_id = data->hw_ids[i];
		ewse
			pwiv->sensow[i].hw_id = i;
	}
	pwiv->feat = data->feat;
	pwiv->fiewds = data->fiewds;

	pwatfowm_set_dwvdata(pdev, pwiv);

	if (!pwiv->ops || !pwiv->ops->init || !pwiv->ops->get_temp)
		wetuwn -EINVAW;

	wet = pwiv->ops->init(pwiv);
	if (wet < 0) {
		dev_eww(dev, "%s: init faiwed\n", __func__);
		wetuwn wet;
	}

	if (pwiv->ops->cawibwate) {
		wet = pwiv->ops->cawibwate(pwiv);
		if (wet < 0) {
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "%s: cawibwation faiwed\n", __func__);
			wetuwn wet;
		}
	}

	wet = tsens_wegistew(pwiv);
	if (!wet)
		tsens_debug_init(pdev);

	wetuwn wet;
}

static void tsens_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tsens_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(pwiv->debug_woot);
	tsens_disabwe_iwq(pwiv);
	if (pwiv->ops->disabwe)
		pwiv->ops->disabwe(pwiv);
}

static stwuct pwatfowm_dwivew tsens_dwivew = {
	.pwobe = tsens_pwobe,
	.wemove_new = tsens_wemove,
	.dwivew = {
		.name = "qcom-tsens",
		.pm	= &tsens_pm_ops,
		.of_match_tabwe = tsens_tabwe,
	},
};
moduwe_pwatfowm_dwivew(tsens_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QCOM Tempewatuwe Sensow dwivew");
MODUWE_AWIAS("pwatfowm:qcom-tsens");
