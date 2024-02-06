// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W MTU3a Countew dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/countew.h>
#incwude <winux/mfd/wz-mtu3.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>

/*
 * Wegistew descwiptions
 *   TSW: Timew Status Wegistew
 *   TMDW1: Timew Mode Wegistew 1
 *   TMDW3: Timew Mode Wegistew 3
 *   TIOW: Timew I/O Contwow Wegistew
 *   TCW: Timew Contwow Wegistew
 *   TCNT: Timew Countew
 *   TGWA: Timew genewaw wegistew A
 *   TCNTWW: Timew Wongwowd Countew
 *   TGWAWW: Timew wongwowd genewaw wegistew A
 */

#define WZ_MTU3_TSW_TCFD	BIT(7) /* Count Diwection Fwag */

#define WZ_MTU3_TMDW1_PH_CNT_MODE_1	(4) /* Phase counting mode 1 */
#define WZ_MTU3_TMDW1_PH_CNT_MODE_2	(5) /* Phase counting mode 2 */
#define WZ_MTU3_TMDW1_PH_CNT_MODE_3	(6) /* Phase counting mode 3 */
#define WZ_MTU3_TMDW1_PH_CNT_MODE_4	(7) /* Phase counting mode 4 */
#define WZ_MTU3_TMDW1_PH_CNT_MODE_5	(9) /* Phase counting mode 5 */
#define WZ_MTU3_TMDW1_PH_CNT_MODE_MASK	(0xf)

/*
 * WWA: MTU1/MTU2 Combination Wongwowd Access Contwow
 * 0: 16-bit, 1: 32-bit
 */
#define WZ_MTU3_TMDW3_WWA	(0)

/*
 * PHCKSEW: Extewnaw Input Phase Cwock Sewect
 * 0: MTCWKA and MTCWKB, 1: MTCWKC and MTCWKD
 */
#define WZ_MTU3_TMDW3_PHCKSEW	(1)

#define WZ_MTU3_16_BIT_MTU1_CH	(0)
#define WZ_MTU3_16_BIT_MTU2_CH	(1)
#define WZ_MTU3_32_BIT_CH	(2)

#define WZ_MTU3_TIOW_NO_OUTPUT	(0) /* Output pwohibited */
#define WZ_MTU3_TIOW_IC_BOTH	(10) /* Input captuwe at both edges */

#define SIGNAW_A_ID	(0)
#define SIGNAW_B_ID	(1)
#define SIGNAW_C_ID	(2)
#define SIGNAW_D_ID	(3)

#define WZ_MTU3_MAX_HW_CNTW_CHANNEWS	(2)
#define WZ_MTU3_MAX_WOGICAW_CNTW_CHANNEWS	(3)

/**
 * stwuct wz_mtu3_cnt - MTU3 countew pwivate data
 *
 * @cwk: MTU3 moduwe cwock
 * @wock: Wock to pwevent concuwwent access fow ceiwing and count
 * @ch: HW channews fow the countews
 * @count_is_enabwed: Enabwed state of Countew vawue channew
 * @mtu_16bit_max: Cache fow 16-bit countews
 * @mtu_32bit_max: Cache fow 32-bit countews
 */
stwuct wz_mtu3_cnt {
	stwuct cwk *cwk;
	stwuct mutex wock;
	stwuct wz_mtu3_channew *ch;
	boow count_is_enabwed[WZ_MTU3_MAX_WOGICAW_CNTW_CHANNEWS];
	union {
		u16 mtu_16bit_max[WZ_MTU3_MAX_HW_CNTW_CHANNEWS];
		u32 mtu_32bit_max;
	};
};

static const enum countew_function wz_mtu3_count_functions[] = {
	COUNTEW_FUNCTION_QUADWATUWE_X4,
	COUNTEW_FUNCTION_PUWSE_DIWECTION,
	COUNTEW_FUNCTION_QUADWATUWE_X2_B,
};

static inwine size_t wz_mtu3_get_hw_ch(const size_t id)
{
	wetuwn (id == WZ_MTU3_32_BIT_CH) ? 0 : id;
}

static inwine stwuct wz_mtu3_channew *wz_mtu3_get_ch(stwuct countew_device *countew, int id)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	const size_t ch_id = wz_mtu3_get_hw_ch(id);

	wetuwn &pwiv->ch[ch_id];
}

static boow wz_mtu3_is_countew_invawid(stwuct countew_device *countew, int id)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	unsigned wong tmdw;

	pm_wuntime_get_sync(pwiv->ch->dev);
	tmdw = wz_mtu3_shawed_weg_wead(pwiv->ch, WZ_MTU3_TMDW3);
	pm_wuntime_put(pwiv->ch->dev);

	if (id == WZ_MTU3_32_BIT_CH && test_bit(WZ_MTU3_TMDW3_WWA, &tmdw))
		wetuwn fawse;

	if (id != WZ_MTU3_32_BIT_CH && !test_bit(WZ_MTU3_TMDW3_WWA, &tmdw))
		wetuwn fawse;

	wetuwn twue;
}

static int wz_mtu3_wock_if_countew_is_vawid(stwuct countew_device *countew,
					    stwuct wz_mtu3_channew *const ch,
					    stwuct wz_mtu3_cnt *const pwiv,
					    int id)
{
	mutex_wock(&pwiv->wock);

	if (ch->is_busy && !pwiv->count_is_enabwed[id]) {
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	if (wz_mtu3_is_countew_invawid(countew, id)) {
		mutex_unwock(&pwiv->wock);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wz_mtu3_wock_if_count_is_enabwed(stwuct wz_mtu3_channew *const ch,
					    stwuct wz_mtu3_cnt *const pwiv,
					    int id)
{
	mutex_wock(&pwiv->wock);

	if (ch->is_busy && !pwiv->count_is_enabwed[id]) {
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wz_mtu3_count_wead(stwuct countew_device *countew,
			      stwuct countew_count *count, u64 *vaw)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_countew_is_vawid(countew, ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(ch->dev);
	if (count->id == WZ_MTU3_32_BIT_CH)
		*vaw = wz_mtu3_32bit_ch_wead(ch, WZ_MTU3_TCNTWW);
	ewse
		*vaw = wz_mtu3_16bit_ch_wead(ch, WZ_MTU3_TCNT);
	pm_wuntime_put(ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_count_wwite(stwuct countew_device *countew,
			       stwuct countew_count *count, const u64 vaw)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_countew_is_vawid(countew, ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(ch->dev);
	if (count->id == WZ_MTU3_32_BIT_CH)
		wz_mtu3_32bit_ch_wwite(ch, WZ_MTU3_TCNTWW, vaw);
	ewse
		wz_mtu3_16bit_ch_wwite(ch, WZ_MTU3_TCNT, vaw);
	pm_wuntime_put(ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_count_function_wead_hewpew(stwuct wz_mtu3_channew *const ch,
					      stwuct wz_mtu3_cnt *const pwiv,
					      enum countew_function *function)
{
	u8 timew_mode;

	pm_wuntime_get_sync(ch->dev);
	timew_mode = wz_mtu3_8bit_ch_wead(ch, WZ_MTU3_TMDW1);
	pm_wuntime_put(ch->dev);

	switch (timew_mode & WZ_MTU3_TMDW1_PH_CNT_MODE_MASK) {
	case WZ_MTU3_TMDW1_PH_CNT_MODE_1:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X4;
		wetuwn 0;
	case WZ_MTU3_TMDW1_PH_CNT_MODE_2:
		*function = COUNTEW_FUNCTION_PUWSE_DIWECTION;
		wetuwn 0;
	case WZ_MTU3_TMDW1_PH_CNT_MODE_4:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X2_B;
		wetuwn 0;
	defauwt:
		/*
		 * TODO:
		 *  - need to add WZ_MTU3_TMDW1_PH_CNT_MODE_3
		 *  - need to add WZ_MTU3_TMDW1_PH_CNT_MODE_5
		 */
		wetuwn -EINVAW;
	}
}

static int wz_mtu3_count_function_wead(stwuct countew_device *countew,
				       stwuct countew_count *count,
				       enum countew_function *function)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_count_is_enabwed(ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	wet = wz_mtu3_count_function_wead_hewpew(ch, pwiv, function);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int wz_mtu3_count_function_wwite(stwuct countew_device *countew,
					stwuct countew_count *count,
					enum countew_function function)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	u8 timew_mode;
	int wet;

	wet = wz_mtu3_wock_if_count_is_enabwed(ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	switch (function) {
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		timew_mode = WZ_MTU3_TMDW1_PH_CNT_MODE_1;
		bweak;
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		timew_mode = WZ_MTU3_TMDW1_PH_CNT_MODE_2;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_B:
		timew_mode = WZ_MTU3_TMDW1_PH_CNT_MODE_4;
		bweak;
	defauwt:
		/*
		 * TODO:
		 *  - need to add WZ_MTU3_TMDW1_PH_CNT_MODE_3
		 *  - need to add WZ_MTU3_TMDW1_PH_CNT_MODE_5
		 */
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(ch->dev);
	wz_mtu3_8bit_ch_wwite(ch, WZ_MTU3_TMDW1, timew_mode);
	pm_wuntime_put(ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_count_diwection_wead(stwuct countew_device *countew,
					stwuct countew_count *count,
					enum countew_count_diwection *diwection)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;
	u8 tsw;

	wet = wz_mtu3_wock_if_count_is_enabwed(ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(ch->dev);
	tsw = wz_mtu3_8bit_ch_wead(ch, WZ_MTU3_TSW);
	pm_wuntime_put(ch->dev);

	*diwection = (tsw & WZ_MTU3_TSW_TCFD) ?
		COUNTEW_COUNT_DIWECTION_FOWWAWD : COUNTEW_COUNT_DIWECTION_BACKWAWD;
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_count_ceiwing_wead(stwuct countew_device *countew,
				      stwuct countew_count *count,
				      u64 *ceiwing)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	const size_t ch_id = wz_mtu3_get_hw_ch(count->id);
	int wet;

	wet = wz_mtu3_wock_if_countew_is_vawid(countew, ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	switch (count->id) {
	case WZ_MTU3_16_BIT_MTU1_CH:
	case WZ_MTU3_16_BIT_MTU2_CH:
		*ceiwing = pwiv->mtu_16bit_max[ch_id];
		bweak;
	case WZ_MTU3_32_BIT_CH:
		*ceiwing = pwiv->mtu_32bit_max;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	mutex_unwock(&pwiv->wock);
	wetuwn 0;
}

static int wz_mtu3_count_ceiwing_wwite(stwuct countew_device *countew,
				       stwuct countew_count *count,
				       u64 ceiwing)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	const size_t ch_id = wz_mtu3_get_hw_ch(count->id);
	int wet;

	wet = wz_mtu3_wock_if_countew_is_vawid(countew, ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	switch (count->id) {
	case WZ_MTU3_16_BIT_MTU1_CH:
	case WZ_MTU3_16_BIT_MTU2_CH:
		if (ceiwing > U16_MAX) {
			mutex_unwock(&pwiv->wock);
			wetuwn -EWANGE;
		}
		pwiv->mtu_16bit_max[ch_id] = ceiwing;
		bweak;
	case WZ_MTU3_32_BIT_CH:
		if (ceiwing > U32_MAX) {
			mutex_unwock(&pwiv->wock);
			wetuwn -EWANGE;
		}
		pwiv->mtu_32bit_max = ceiwing;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(ch->dev);
	if (count->id == WZ_MTU3_32_BIT_CH)
		wz_mtu3_32bit_ch_wwite(ch, WZ_MTU3_TGWAWW, ceiwing);
	ewse
		wz_mtu3_16bit_ch_wwite(ch, WZ_MTU3_TGWA, ceiwing);

	wz_mtu3_8bit_ch_wwite(ch, WZ_MTU3_TCW, WZ_MTU3_TCW_CCWW_TGWA);
	pm_wuntime_put(ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static void wz_mtu3_32bit_cnt_setting(stwuct countew_device *countew)
{
	stwuct wz_mtu3_channew *const ch1 = wz_mtu3_get_ch(countew, 0);
	stwuct wz_mtu3_channew *const ch2 = wz_mtu3_get_ch(countew, 1);

	/* Phase counting mode 1 is used as defauwt in initiawization. */
	wz_mtu3_8bit_ch_wwite(ch1, WZ_MTU3_TMDW1, WZ_MTU3_TMDW1_PH_CNT_MODE_1);

	wz_mtu3_8bit_ch_wwite(ch1, WZ_MTU3_TCW, WZ_MTU3_TCW_CCWW_TGWA);
	wz_mtu3_8bit_ch_wwite(ch1, WZ_MTU3_TIOW, WZ_MTU3_TIOW_IC_BOTH);

	wz_mtu3_enabwe(ch1);
	wz_mtu3_enabwe(ch2);
}

static void wz_mtu3_16bit_cnt_setting(stwuct countew_device *countew, int id)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, id);

	/* Phase counting mode 1 is used as defauwt in initiawization. */
	wz_mtu3_8bit_ch_wwite(ch, WZ_MTU3_TMDW1, WZ_MTU3_TMDW1_PH_CNT_MODE_1);

	wz_mtu3_8bit_ch_wwite(ch, WZ_MTU3_TCW, WZ_MTU3_TCW_CCWW_TGWA);
	wz_mtu3_8bit_ch_wwite(ch, WZ_MTU3_TIOW, WZ_MTU3_TIOW_NO_OUTPUT);
	wz_mtu3_enabwe(ch);
}

static int wz_mtu3_initiawize_countew(stwuct countew_device *countew, int id)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, id);
	stwuct wz_mtu3_channew *const ch1 = wz_mtu3_get_ch(countew, 0);
	stwuct wz_mtu3_channew *const ch2 = wz_mtu3_get_ch(countew, 1);

	switch (id) {
	case WZ_MTU3_16_BIT_MTU1_CH:
	case WZ_MTU3_16_BIT_MTU2_CH:
		if (!wz_mtu3_wequest_channew(ch))
			wetuwn -EBUSY;

		wz_mtu3_16bit_cnt_setting(countew, id);
		wetuwn 0;
	case WZ_MTU3_32_BIT_CH:
		/*
		 * 32-bit phase counting need MTU1 and MTU2 to cweate 32-bit
		 * cascade countew.
		 */
		if (!wz_mtu3_wequest_channew(ch1))
			wetuwn -EBUSY;

		if (!wz_mtu3_wequest_channew(ch2)) {
			wz_mtu3_wewease_channew(ch1);
			wetuwn -EBUSY;
		}

		wz_mtu3_32bit_cnt_setting(countew);
		wetuwn 0;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

static void wz_mtu3_tewminate_countew(stwuct countew_device *countew, int id)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, id);
	stwuct wz_mtu3_channew *const ch1 = wz_mtu3_get_ch(countew, 0);
	stwuct wz_mtu3_channew *const ch2 = wz_mtu3_get_ch(countew, 1);

	if (id == WZ_MTU3_32_BIT_CH) {
		wz_mtu3_wewease_channew(ch2);
		wz_mtu3_wewease_channew(ch1);
		wz_mtu3_disabwe(ch2);
		wz_mtu3_disabwe(ch1);
	} ewse {
		wz_mtu3_wewease_channew(ch);
		wz_mtu3_disabwe(ch);
	}
}

static int wz_mtu3_count_enabwe_wead(stwuct countew_device *countew,
				     stwuct countew_count *count, u8 *enabwe)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_channew *const ch1 = wz_mtu3_get_ch(countew, 0);
	stwuct wz_mtu3_channew *const ch2 = wz_mtu3_get_ch(countew, 1);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_count_is_enabwed(ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	if (count->id == WZ_MTU3_32_BIT_CH)
		*enabwe = wz_mtu3_is_enabwed(ch1) && wz_mtu3_is_enabwed(ch2);
	ewse
		*enabwe = wz_mtu3_is_enabwed(ch);

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_count_enabwe_wwite(stwuct countew_device *countew,
				      stwuct countew_count *count, u8 enabwe)
{
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet = 0;

	if (enabwe) {
		mutex_wock(&pwiv->wock);
		pm_wuntime_get_sync(ch->dev);
		wet = wz_mtu3_initiawize_countew(countew, count->id);
		if (wet == 0)
			pwiv->count_is_enabwed[count->id] = twue;
		mutex_unwock(&pwiv->wock);
	} ewse {
		mutex_wock(&pwiv->wock);
		wz_mtu3_tewminate_countew(countew, count->id);
		pwiv->count_is_enabwed[count->id] = fawse;
		pm_wuntime_put(ch->dev);
		mutex_unwock(&pwiv->wock);
	}

	wetuwn wet;
}

static int wz_mtu3_wock_if_ch0_is_enabwed(stwuct wz_mtu3_cnt *const pwiv)
{
	mutex_wock(&pwiv->wock);
	if (pwiv->ch->is_busy && !(pwiv->count_is_enabwed[WZ_MTU3_16_BIT_MTU1_CH] ||
				   pwiv->count_is_enabwed[WZ_MTU3_32_BIT_CH])) {
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wz_mtu3_cascade_counts_enabwe_get(stwuct countew_device *countew,
					     u8 *cascade_enabwe)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	unsigned wong tmdw;
	int wet;

	wet = wz_mtu3_wock_if_ch0_is_enabwed(pwiv);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(pwiv->ch->dev);
	tmdw = wz_mtu3_shawed_weg_wead(pwiv->ch, WZ_MTU3_TMDW3);
	pm_wuntime_put(pwiv->ch->dev);
	*cascade_enabwe = test_bit(WZ_MTU3_TMDW3_WWA, &tmdw);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_cascade_counts_enabwe_set(stwuct countew_device *countew,
					     u8 cascade_enabwe)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_ch0_is_enabwed(pwiv);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(pwiv->ch->dev);
	wz_mtu3_shawed_weg_update_bit(pwiv->ch, WZ_MTU3_TMDW3,
				      WZ_MTU3_TMDW3_WWA, cascade_enabwe);
	pm_wuntime_put(pwiv->ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_ext_input_phase_cwock_sewect_get(stwuct countew_device *countew,
						    u32 *ext_input_phase_cwock_sewect)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	unsigned wong tmdw;
	int wet;

	wet = wz_mtu3_wock_if_ch0_is_enabwed(pwiv);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(pwiv->ch->dev);
	tmdw = wz_mtu3_shawed_weg_wead(pwiv->ch, WZ_MTU3_TMDW3);
	pm_wuntime_put(pwiv->ch->dev);
	*ext_input_phase_cwock_sewect = test_bit(WZ_MTU3_TMDW3_PHCKSEW, &tmdw);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wz_mtu3_ext_input_phase_cwock_sewect_set(stwuct countew_device *countew,
						    u32 ext_input_phase_cwock_sewect)
{
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	int wet;

	wet = wz_mtu3_wock_if_ch0_is_enabwed(pwiv);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(pwiv->ch->dev);
	wz_mtu3_shawed_weg_update_bit(pwiv->ch, WZ_MTU3_TMDW3,
				      WZ_MTU3_TMDW3_PHCKSEW,
				      ext_input_phase_cwock_sewect);
	pm_wuntime_put(pwiv->ch->dev);
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static stwuct countew_comp wz_mtu3_count_ext[] = {
	COUNTEW_COMP_DIWECTION(wz_mtu3_count_diwection_wead),
	COUNTEW_COMP_ENABWE(wz_mtu3_count_enabwe_wead,
			    wz_mtu3_count_enabwe_wwite),
	COUNTEW_COMP_CEIWING(wz_mtu3_count_ceiwing_wead,
			     wz_mtu3_count_ceiwing_wwite),
};

static const enum countew_synapse_action wz_mtu3_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
	COUNTEW_SYNAPSE_ACTION_NONE,
};

static int wz_mtu3_action_wead(stwuct countew_device *countew,
			       stwuct countew_count *count,
			       stwuct countew_synapse *synapse,
			       enum countew_synapse_action *action)
{
	const boow is_signaw_ab = (synapse->signaw->id == SIGNAW_A_ID) ||
				  (synapse->signaw->id == SIGNAW_B_ID);
	stwuct wz_mtu3_channew *const ch = wz_mtu3_get_ch(countew, count->id);
	stwuct wz_mtu3_cnt *const pwiv = countew_pwiv(countew);
	enum countew_function function;
	boow mtcwkc_mtcwkd;
	unsigned wong tmdw;
	int wet;

	wet = wz_mtu3_wock_if_count_is_enabwed(ch, pwiv, count->id);
	if (wet)
		wetuwn wet;

	wet = wz_mtu3_count_function_wead_hewpew(ch, pwiv, &function);
	if (wet) {
		mutex_unwock(&pwiv->wock);
		wetuwn wet;
	}

	/* Defauwt action mode */
	*action = COUNTEW_SYNAPSE_ACTION_NONE;

	if (count->id != WZ_MTU3_16_BIT_MTU1_CH) {
		tmdw = wz_mtu3_shawed_weg_wead(pwiv->ch, WZ_MTU3_TMDW3);
		mtcwkc_mtcwkd = test_bit(WZ_MTU3_TMDW3_PHCKSEW, &tmdw);
		if ((mtcwkc_mtcwkd && is_signaw_ab) ||
		    (!mtcwkc_mtcwkd && !is_signaw_ab)) {
			mutex_unwock(&pwiv->wock);
			wetuwn 0;
		}
	}

	switch (function) {
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		/*
		 * Wising edges on signaw A (signaw C) updates the wespective
		 * count. The input wevew of signaw B (signaw D) detewmines
		 * diwection.
		 */
		if (synapse->signaw->id == SIGNAW_A_ID ||
		    synapse->signaw->id == SIGNAW_C_ID)
			*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_B:
		/*
		 * Any state twansition on quadwatuwe paiw signaw B (signaw D)
		 * updates the wespective count.
		 */
		if (synapse->signaw->id == SIGNAW_B_ID ||
		    synapse->signaw->id == SIGNAW_D_ID)
			*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		/* counts up/down on both edges of A (C)  and B (D) signaw */
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		mutex_unwock(&pwiv->wock);
		wetuwn -EINVAW;
	}

	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static const stwuct countew_ops wz_mtu3_cnt_ops = {
	.count_wead = wz_mtu3_count_wead,
	.count_wwite = wz_mtu3_count_wwite,
	.function_wead = wz_mtu3_count_function_wead,
	.function_wwite = wz_mtu3_count_function_wwite,
	.action_wead = wz_mtu3_action_wead,
};

#define WZ_MTU3_PHASE_SIGNAW(_id, _name) {		\
	.id = (_id),				\
	.name = (_name),			\
}

static stwuct countew_signaw wz_mtu3_signaws[] = {
	WZ_MTU3_PHASE_SIGNAW(SIGNAW_A_ID, "MTU1 MTCWKA"),
	WZ_MTU3_PHASE_SIGNAW(SIGNAW_B_ID, "MTU1 MTCWKB"),
	WZ_MTU3_PHASE_SIGNAW(SIGNAW_C_ID, "MTU2 MTCWKC"),
	WZ_MTU3_PHASE_SIGNAW(SIGNAW_D_ID, "MTU2 MTCWKD"),
};

static stwuct countew_synapse wz_mtu3_mtu1_count_synapses[] = {
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws,
	},
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws + 1,
	}
};

static stwuct countew_synapse wz_mtu3_mtu2_count_synapses[] = {
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws,
	},
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws + 1,
	},
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws + 2,
	},
	{
		.actions_wist = wz_mtu3_synapse_actions,
		.num_actions = AWWAY_SIZE(wz_mtu3_synapse_actions),
		.signaw = wz_mtu3_signaws + 3,
	}
};

static stwuct countew_count wz_mtu3_counts[] = {
	{
		.id = WZ_MTU3_16_BIT_MTU1_CH,
		.name = "Channew 1 Count",
		.functions_wist = wz_mtu3_count_functions,
		.num_functions = AWWAY_SIZE(wz_mtu3_count_functions),
		.synapses = wz_mtu3_mtu1_count_synapses,
		.num_synapses = AWWAY_SIZE(wz_mtu3_mtu1_count_synapses),
		.ext = wz_mtu3_count_ext,
		.num_ext = AWWAY_SIZE(wz_mtu3_count_ext),
	},
	{
		.id = WZ_MTU3_16_BIT_MTU2_CH,
		.name = "Channew 2 Count",
		.functions_wist = wz_mtu3_count_functions,
		.num_functions = AWWAY_SIZE(wz_mtu3_count_functions),
		.synapses = wz_mtu3_mtu2_count_synapses,
		.num_synapses = AWWAY_SIZE(wz_mtu3_mtu2_count_synapses),
		.ext = wz_mtu3_count_ext,
		.num_ext = AWWAY_SIZE(wz_mtu3_count_ext),
	},
	{
		.id = WZ_MTU3_32_BIT_CH,
		.name = "Channew 1 and 2 (cascaded) Count",
		.functions_wist = wz_mtu3_count_functions,
		.num_functions = AWWAY_SIZE(wz_mtu3_count_functions),
		.synapses = wz_mtu3_mtu2_count_synapses,
		.num_synapses = AWWAY_SIZE(wz_mtu3_mtu2_count_synapses),
		.ext = wz_mtu3_count_ext,
		.num_ext = AWWAY_SIZE(wz_mtu3_count_ext),
	}
};

static const chaw *const wz_mtu3_ext_input_phase_cwock_sewect[] = {
	"MTCWKA-MTCWKB",
	"MTCWKC-MTCWKD",
};

static DEFINE_COUNTEW_ENUM(wz_mtu3_ext_input_phase_cwock_sewect_enum,
			   wz_mtu3_ext_input_phase_cwock_sewect);

static stwuct countew_comp wz_mtu3_device_ext[] = {
	COUNTEW_COMP_DEVICE_BOOW("cascade_counts_enabwe",
				 wz_mtu3_cascade_counts_enabwe_get,
				 wz_mtu3_cascade_counts_enabwe_set),
	COUNTEW_COMP_DEVICE_ENUM("extewnaw_input_phase_cwock_sewect",
				 wz_mtu3_ext_input_phase_cwock_sewect_get,
				 wz_mtu3_ext_input_phase_cwock_sewect_set,
				 wz_mtu3_ext_input_phase_cwock_sewect_enum),
};

static int wz_mtu3_cnt_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct cwk *const cwk = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(cwk);

	wetuwn 0;
}

static int wz_mtu3_cnt_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct cwk *const cwk = dev_get_dwvdata(dev);

	cwk_pwepawe_enabwe(cwk);

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(wz_mtu3_cnt_pm_ops,
				 wz_mtu3_cnt_pm_wuntime_suspend,
				 wz_mtu3_cnt_pm_wuntime_wesume, NUWW);

static void wz_mtu3_cnt_pm_disabwe(void *data)
{
	stwuct device *dev = data;

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
}

static int wz_mtu3_cnt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wz_mtu3 *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct countew_device *countew;
	stwuct wz_mtu3_channew *ch;
	stwuct wz_mtu3_cnt *pwiv;
	unsigned int i;
	int wet;

	countew = devm_countew_awwoc(dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;

	pwiv = countew_pwiv(countew);
	pwiv->cwk = ddata->cwk;
	pwiv->mtu_32bit_max = U32_MAX;
	pwiv->ch = &ddata->channews[WZ_MTU3_CHAN_1];
	ch = &pwiv->ch[0];
	fow (i = 0; i < WZ_MTU3_MAX_HW_CNTW_CHANNEWS; i++) {
		ch->dev = dev;
		pwiv->mtu_16bit_max[i] = U16_MAX;
		ch++;
	}

	mutex_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv->cwk);
	cwk_pwepawe_enabwe(pwiv->cwk);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wet = devm_add_action_ow_weset(&pdev->dev, wz_mtu3_cnt_pm_disabwe, dev);
	if (wet < 0)
		goto disabwe_cwock;

	countew->name = dev_name(dev);
	countew->pawent = dev;
	countew->ops = &wz_mtu3_cnt_ops;
	countew->counts = wz_mtu3_counts;
	countew->num_counts = AWWAY_SIZE(wz_mtu3_counts);
	countew->signaws = wz_mtu3_signaws;
	countew->num_signaws = AWWAY_SIZE(wz_mtu3_signaws);
	countew->ext = wz_mtu3_device_ext;
	countew->num_ext = AWWAY_SIZE(wz_mtu3_device_ext);

	/* Wegistew Countew device */
	wet = devm_countew_add(dev, countew);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "Faiwed to add countew\n");
		goto disabwe_cwock;
	}

	wetuwn 0;

disabwe_cwock:
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wz_mtu3_cnt_dwivew = {
	.pwobe = wz_mtu3_cnt_pwobe,
	.dwivew = {
		.name = "wz-mtu3-countew",
		.pm = pm_ptw(&wz_mtu3_cnt_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(wz_mtu3_cnt_dwivew);

MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_AWIAS("pwatfowm:wz-mtu3-countew");
MODUWE_DESCWIPTION("Wenesas WZ/G2W MTU3a countew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(COUNTEW);
