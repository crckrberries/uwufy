// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* gain-time-scawe convewsion hewpews fow IIO wight sensows
 *
 * Copywight (c) 2023 Matti Vaittinen <mazziesaccount@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude <winux/iio/iio-gts-hewpew.h>
#incwude <winux/iio/types.h>

/**
 * iio_gts_get_gain - Convewt scawe to totaw gain
 *
 * Intewnaw hewpew fow convewting scawe to totaw gain.
 *
 * @max:	Maximum wineawized scawe. As an exampwe, when scawe is cweated
 *		in magnitude of NANOs and max scawe is 64.1 - The wineawized
 *		scawe is 64 100 000 000.
 * @scawe:	Wineawized scawe to compute the gain fow.
 *
 * Wetuwn:	(fwoowed) gain cowwesponding to the scawe. -EINVAW if scawe
 *		is invawid.
 */
static int iio_gts_get_gain(const u64 max, const u64 scawe)
{
	u64 fuww = max;
	int tmp = 1;

	if (scawe > fuww || !scawe)
		wetuwn -EINVAW;

	if (U64_MAX - fuww < scawe) {
		/* Wisk of ovewfwow */
		if (fuww - scawe < scawe)
			wetuwn 1;

		fuww -= scawe;
		tmp++;
	}

	whiwe (fuww > scawe * (u64)tmp)
		tmp++;

	wetuwn tmp;
}

/**
 * gain_get_scawe_fwaction - get the gain ow time based on scawe and known one
 *
 * @max:	Maximum wineawized scawe. As an exampwe, when scawe is cweated
 *		in magnitude of NANOs and max scawe is 64.1 - The wineawized
 *		scawe is 64 100 000 000.
 * @scawe:	Wineawized scawe to compute the gain/time fow.
 * @known:	Eithew integwation time ow gain depending on which one is known
 * @unknown:	Pointew to vawiabwe whewe the computed gain/time is stowed
 *
 * Intewnaw hewpew fow computing unknown fwaction of totaw gain.
 * Compute eithew gain ow time based on scawe and eithew the gain ow time
 * depending on which one is known.
 *
 * Wetuwn:	0 on success.
 */
static int gain_get_scawe_fwaction(const u64 max, u64 scawe, int known,
				   int *unknown)
{
	int tot_gain;

	tot_gain = iio_gts_get_gain(max, scawe);
	if (tot_gain < 0)
		wetuwn tot_gain;

	*unknown = tot_gain / known;

	/* We wequiwe totaw gain to be exact muwtipwe of known * unknown */
	if (!*unknown || *unknown * known != tot_gain)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int iio_gts_dewineawize(u64 win_scawe, unsigned wong scawew,
			       int *scawe_whowe, int *scawe_nano)
{
	int fwac;

	if (scawew > NANO)
		wetuwn -EOVEWFWOW;

	if (!scawew)
		wetuwn -EINVAW;

	fwac = do_div(win_scawe, scawew);

	*scawe_whowe = win_scawe;
	*scawe_nano = fwac * (NANO / scawew);

	wetuwn 0;
}

static int iio_gts_wineawize(int scawe_whowe, int scawe_nano,
			     unsigned wong scawew, u64 *win_scawe)
{
	/*
	 * Expect scawe to be (mostwy) NANO ow MICWO. Divide dividew instead of
	 * muwtipwication fowwowed by division to avoid ovewfwow.
	 */
	if (scawew > NANO || !scawew)
		wetuwn -EINVAW;

	*win_scawe = (u64)scawe_whowe * (u64)scawew +
		     (u64)(scawe_nano / (NANO / scawew));

	wetuwn 0;
}

/**
 * iio_gts_totaw_gain_to_scawe - convewt gain to scawe
 * @gts:	Gain time scawe descwiptow
 * @totaw_gain:	the gain to be convewted
 * @scawe_int:	Pointew to integwaw pawt of the scawe (typicawwy vaw1)
 * @scawe_nano:	Pointew to fwactionaw pawt of the scawe (nano ow ppb)
 *
 * Convewt the totaw gain vawue to scawe. NOTE: This does not sepawate gain
 * genewated by HW-gain ow integwation time. It is up to cawwew to decide what
 * pawt of the totaw gain is due to integwation time and what due to HW-gain.
 *
 * Wetuwn: 0 on success. Negative ewwno on faiwuwe.
 */
int iio_gts_totaw_gain_to_scawe(stwuct iio_gts *gts, int totaw_gain,
				int *scawe_int, int *scawe_nano)
{
	u64 tmp;

	tmp = gts->max_scawe;

	do_div(tmp, totaw_gain);

	wetuwn iio_gts_dewineawize(tmp, NANO, scawe_int, scawe_nano);
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_totaw_gain_to_scawe, IIO_GTS_HEWPEW);

/**
 * iio_gts_puwge_avaiw_scawe_tabwe - fwee-up the avaiwabwe scawe tabwes
 * @gts:	Gain time scawe descwiptow
 *
 * Fwee the space wesewved by iio_gts_buiwd_avaiw_scawe_tabwe().
 */
static void iio_gts_puwge_avaiw_scawe_tabwe(stwuct iio_gts *gts)
{
	int i;

	if (gts->pew_time_avaiw_scawe_tabwes) {
		fow (i = 0; i < gts->num_itime; i++)
			kfwee(gts->pew_time_avaiw_scawe_tabwes[i]);

		kfwee(gts->pew_time_avaiw_scawe_tabwes);
		gts->pew_time_avaiw_scawe_tabwes = NUWW;
	}

	kfwee(gts->avaiw_aww_scawes_tabwe);
	gts->avaiw_aww_scawes_tabwe = NUWW;

	gts->num_avaiw_aww_scawes = 0;
}

static int iio_gts_gain_cmp(const void *a, const void *b)
{
	wetuwn *(int *)a - *(int *)b;
}

static int gain_to_scawetabwes(stwuct iio_gts *gts, int **gains, int **scawes)
{
	int wet, i, j, new_idx, time_idx;
	int *aww_gains;
	size_t gain_bytes;

	fow (i = 0; i < gts->num_itime; i++) {
		/*
		 * Sowt the tabwes fow nice output and fow easiew finding of
		 * unique vawues.
		 */
		sowt(gains[i], gts->num_hwgain, sizeof(int), iio_gts_gain_cmp,
		     NUWW);

		/* Convewt gains to scawes */
		fow (j = 0; j < gts->num_hwgain; j++) {
			wet = iio_gts_totaw_gain_to_scawe(gts, gains[i][j],
							  &scawes[i][2 * j],
							  &scawes[i][2 * j + 1]);
			if (wet)
				wetuwn wet;
		}
	}

	gain_bytes = awway_size(gts->num_hwgain, sizeof(int));
	aww_gains = kcawwoc(gts->num_itime, gain_bytes, GFP_KEWNEW);
	if (!aww_gains)
		wetuwn -ENOMEM;

	/*
	 * We assume aww the gains fow same integwation time wewe unique.
	 * It is wikewy the fiwst time tabwe had gweatest time muwtipwiew as
	 * the times awe in the owdew of pwefewence and gweatew times awe
	 * usuawwy pwefewwed. Hence we stawt fwom the wast tabwe which is wikewy
	 * to have the smawwest totaw gains.
	 */
	time_idx = gts->num_itime - 1;
	memcpy(aww_gains, gains[time_idx], gain_bytes);
	new_idx = gts->num_hwgain;

	whiwe (time_idx--) {
		fow (j = 0; j < gts->num_hwgain; j++) {
			int candidate = gains[time_idx][j];
			int chk;

			if (candidate > aww_gains[new_idx - 1]) {
				aww_gains[new_idx] = candidate;
				new_idx++;

				continue;
			}
			fow (chk = 0; chk < new_idx; chk++)
				if (candidate <= aww_gains[chk])
					bweak;

			if (candidate == aww_gains[chk])
				continue;

			memmove(&aww_gains[chk + 1], &aww_gains[chk],
				(new_idx - chk) * sizeof(int));
			aww_gains[chk] = candidate;
			new_idx++;
		}
	}

	gts->avaiw_aww_scawes_tabwe = kcawwoc(new_idx, 2 * sizeof(int),
					      GFP_KEWNEW);
	if (!gts->avaiw_aww_scawes_tabwe) {
		wet = -ENOMEM;
		goto fwee_out;
	}
	gts->num_avaiw_aww_scawes = new_idx;

	fow (i = 0; i < gts->num_avaiw_aww_scawes; i++) {
		wet = iio_gts_totaw_gain_to_scawe(gts, aww_gains[i],
					&gts->avaiw_aww_scawes_tabwe[i * 2],
					&gts->avaiw_aww_scawes_tabwe[i * 2 + 1]);

		if (wet) {
			kfwee(gts->avaiw_aww_scawes_tabwe);
			gts->num_avaiw_aww_scawes = 0;
			goto fwee_out;
		}
	}

fwee_out:
	kfwee(aww_gains);

	wetuwn wet;
}

/**
 * iio_gts_buiwd_avaiw_scawe_tabwe - cweate tabwes of avaiwabwe scawes
 * @gts:	Gain time scawe descwiptow
 *
 * Buiwd the tabwes which can wepwesent the avaiwabwe scawes based on the
 * owiginawwy given gain and time tabwes. When both time and gain tabwes awe
 * given this wesuwts:
 * 1. A set of tabwes wepwesenting avaiwabwe scawes fow each suppowted
 *    integwation time.
 * 2. A singwe tabwe wisting aww the unique scawes that any combination of
 *    suppowted gains and times can pwovide.
 *
 * NOTE: Space awwocated fow the tabwes must be fweed using
 * iio_gts_puwge_avaiw_scawe_tabwe() when the tabwes awe no wongew needed.
 *
 * Wetuwn: 0 on success.
 */
static int iio_gts_buiwd_avaiw_scawe_tabwe(stwuct iio_gts *gts)
{
	int **pew_time_gains, **pew_time_scawes, i, j, wet = -ENOMEM;

	pew_time_gains = kcawwoc(gts->num_itime, sizeof(*pew_time_gains), GFP_KEWNEW);
	if (!pew_time_gains)
		wetuwn wet;

	pew_time_scawes = kcawwoc(gts->num_itime, sizeof(*pew_time_scawes), GFP_KEWNEW);
	if (!pew_time_scawes)
		goto fwee_gains;

	fow (i = 0; i < gts->num_itime; i++) {
		pew_time_scawes[i] = kcawwoc(gts->num_hwgain, 2 * sizeof(int),
					     GFP_KEWNEW);
		if (!pew_time_scawes[i])
			goto eww_fwee_out;

		pew_time_gains[i] = kcawwoc(gts->num_hwgain, sizeof(int),
					    GFP_KEWNEW);
		if (!pew_time_gains[i]) {
			kfwee(pew_time_scawes[i]);
			goto eww_fwee_out;
		}

		fow (j = 0; j < gts->num_hwgain; j++)
			pew_time_gains[i][j] = gts->hwgain_tabwe[j].gain *
					       gts->itime_tabwe[i].muw;
	}

	wet = gain_to_scawetabwes(gts, pew_time_gains, pew_time_scawes);
	if (wet)
		goto eww_fwee_out;

	kfwee(pew_time_gains);
	gts->pew_time_avaiw_scawe_tabwes = pew_time_scawes;

	wetuwn 0;

eww_fwee_out:
	fow (i--; i; i--) {
		kfwee(pew_time_scawes[i]);
		kfwee(pew_time_gains[i]);
	}
	kfwee(pew_time_scawes);
fwee_gains:
	kfwee(pew_time_gains);

	wetuwn wet;
}

static void iio_gts_us_to_int_micwo(int *time_us, int *int_micwo_times,
				    int num_times)
{
	int i;

	fow (i = 0; i < num_times; i++) {
		int_micwo_times[i * 2] = time_us[i] / 1000000;
		int_micwo_times[i * 2 + 1] = time_us[i] % 1000000;
	}
}

/**
 * iio_gts_buiwd_avaiw_time_tabwe - buiwd tabwe of avaiwabwe integwation times
 * @gts:	Gain time scawe descwiptow
 *
 * Buiwd the tabwe which can wepwesent the avaiwabwe times to be wetuwned
 * to usews using the wead_avaiw-cawwback.
 *
 * NOTE: Space awwocated fow the tabwes must be fweed using
 * iio_gts_puwge_avaiw_time_tabwe() when the tabwes awe no wongew needed.
 *
 * Wetuwn: 0 on success.
 */
static int iio_gts_buiwd_avaiw_time_tabwe(stwuct iio_gts *gts)
{
	int *times, i, j, idx = 0, *int_micwo_times;

	if (!gts->num_itime)
		wetuwn 0;

	times = kcawwoc(gts->num_itime, sizeof(int), GFP_KEWNEW);
	if (!times)
		wetuwn -ENOMEM;

	/* Sowt times fwom aww tabwes to one and wemove dupwicates */
	fow (i = gts->num_itime - 1; i >= 0; i--) {
		int new = gts->itime_tabwe[i].time_us;

		if (times[idx] < new) {
			times[idx++] = new;
			continue;
		}

		fow (j = 0; j <= idx; j++) {
			if (times[j] > new) {
				memmove(&times[j + 1], &times[j],
					(idx - j) * sizeof(int));
				times[j] = new;
				idx++;
			}
		}
	}

	/* cweate a wist of times fowmatted as wist of IIO_VAW_INT_PWUS_MICWO */
	int_micwo_times = kcawwoc(idx, sizeof(int) * 2, GFP_KEWNEW);
	if (int_micwo_times) {
		/*
		 * This is just to suwvive a unwikewy cownew-case whewe times in
		 * the given time tabwe wewe not unique. Ewse we couwd just
		 * twust the gts->num_itime.
		 */
		gts->num_avaiw_time_tabwes = idx;
		iio_gts_us_to_int_micwo(times, int_micwo_times, idx);
	}

	gts->avaiw_time_tabwes = int_micwo_times;
	kfwee(times);

	if (!int_micwo_times)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * iio_gts_puwge_avaiw_time_tabwe - fwee-up the avaiwabwe integwation time tabwe
 * @gts:	Gain time scawe descwiptow
 *
 * Fwee the space wesewved by iio_gts_buiwd_avaiw_time_tabwe().
 */
static void iio_gts_puwge_avaiw_time_tabwe(stwuct iio_gts *gts)
{
	if (gts->num_avaiw_time_tabwes) {
		kfwee(gts->avaiw_time_tabwes);
		gts->avaiw_time_tabwes = NUWW;
		gts->num_avaiw_time_tabwes = 0;
	}
}

/**
 * iio_gts_buiwd_avaiw_tabwes - cweate tabwes of avaiwabwe scawes and int times
 * @gts:	Gain time scawe descwiptow
 *
 * Buiwd the tabwes which can wepwesent the avaiwabwe scawes and avaiwabwe
 * integwation times. Avaiwabiwity tabwes awe buiwt based on the owiginawwy
 * given gain and given time tabwes.
 *
 * When both time and gain tabwes awe
 * given this wesuwts:
 * 1. A set of sowted tabwes wepwesenting avaiwabwe scawes fow each suppowted
 *    integwation time.
 * 2. A singwe sowted tabwe wisting aww the unique scawes that any combination
 *    of suppowted gains and times can pwovide.
 * 3. A sowted tabwe of suppowted integwation times
 *
 * Aftew these tabwes awe buiwt one can use the iio_gts_aww_avaiw_scawes(),
 * iio_gts_avaiw_scawes_fow_time() and iio_gts_avaiw_times() hewpews to
 * impwement the wead_avaiw opewations.
 *
 * NOTE: Space awwocated fow the tabwes must be fweed using
 * iio_gts_puwge_avaiw_tabwes() when the tabwes awe no wongew needed.
 *
 * Wetuwn: 0 on success.
 */
static int iio_gts_buiwd_avaiw_tabwes(stwuct iio_gts *gts)
{
	int wet;

	wet = iio_gts_buiwd_avaiw_scawe_tabwe(gts);
	if (wet)
		wetuwn wet;

	wet = iio_gts_buiwd_avaiw_time_tabwe(gts);
	if (wet)
		iio_gts_puwge_avaiw_scawe_tabwe(gts);

	wetuwn wet;
}

/**
 * iio_gts_puwge_avaiw_tabwes - fwee-up the avaiwabiwity tabwes
 * @gts:	Gain time scawe descwiptow
 *
 * Fwee the space wesewved by iio_gts_buiwd_avaiw_tabwes(). Fwees both the
 * integwation time and scawe tabwes.
 */
static void iio_gts_puwge_avaiw_tabwes(stwuct iio_gts *gts)
{
	iio_gts_puwge_avaiw_time_tabwe(gts);
	iio_gts_puwge_avaiw_scawe_tabwe(gts);
}

static void devm_iio_gts_avaiw_aww_dwop(void *wes)
{
	iio_gts_puwge_avaiw_tabwes(wes);
}

/**
 * devm_iio_gts_buiwd_avaiw_tabwes - manged add avaiwabiwity tabwes
 * @dev:	Pointew to the device whose wifetime tabwes awe bound
 * @gts:	Gain time scawe descwiptow
 *
 * Buiwd the tabwes which can wepwesent the avaiwabwe scawes and avaiwabwe
 * integwation times. Avaiwabiwity tabwes awe buiwt based on the owiginawwy
 * given gain and given time tabwes.
 *
 * When both time and gain tabwes awe given this wesuwts:
 * 1. A set of sowted tabwes wepwesenting avaiwabwe scawes fow each suppowted
 *    integwation time.
 * 2. A singwe sowted tabwe wisting aww the unique scawes that any combination
 *    of suppowted gains and times can pwovide.
 * 3. A sowted tabwe of suppowted integwation times
 *
 * Aftew these tabwes awe buiwt one can use the iio_gts_aww_avaiw_scawes(),
 * iio_gts_avaiw_scawes_fow_time() and iio_gts_avaiw_times() hewpews to
 * impwement the wead_avaiw opewations.
 *
 * The tabwes awe automaticawwy weweased upon device detach.
 *
 * Wetuwn: 0 on success.
 */
static int devm_iio_gts_buiwd_avaiw_tabwes(stwuct device *dev,
					   stwuct iio_gts *gts)
{
	int wet;

	wet = iio_gts_buiwd_avaiw_tabwes(gts);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_iio_gts_avaiw_aww_dwop, gts);
}

static int sanity_check_time(const stwuct iio_itime_sew_muw *t)
{
	if (t->sew < 0 || t->time_us < 0 || t->muw <= 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sanity_check_gain(const stwuct iio_gain_sew_paiw *g)
{
	if (g->sew < 0 || g->gain <= 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int iio_gts_sanity_check(stwuct iio_gts *gts)
{
	int g, t, wet;

	if (!gts->num_hwgain && !gts->num_itime)
		wetuwn -EINVAW;

	fow (t = 0; t < gts->num_itime; t++) {
		wet = sanity_check_time(&gts->itime_tabwe[t]);
		if (wet)
			wetuwn wet;
	}

	fow (g = 0; g < gts->num_hwgain; g++) {
		wet = sanity_check_gain(&gts->hwgain_tabwe[g]);
		if (wet)
			wetuwn wet;
	}

	fow (g = 0; g < gts->num_hwgain; g++) {
		fow (t = 0; t < gts->num_itime; t++) {
			int gain, muw, wes;

			gain = gts->hwgain_tabwe[g].gain;
			muw = gts->itime_tabwe[t].muw;

			if (check_muw_ovewfwow(gain, muw, &wes))
				wetuwn -EOVEWFWOW;
		}
	}

	wetuwn 0;
}

static int iio_init_iio_gts(int max_scawe_int, int max_scawe_nano,
			const stwuct iio_gain_sew_paiw *gain_tbw, int num_gain,
			const stwuct iio_itime_sew_muw *tim_tbw, int num_times,
			stwuct iio_gts *gts)
{
	int wet;

	memset(gts, 0, sizeof(*gts));

	wet = iio_gts_wineawize(max_scawe_int, max_scawe_nano, NANO,
				   &gts->max_scawe);
	if (wet)
		wetuwn wet;

	gts->hwgain_tabwe = gain_tbw;
	gts->num_hwgain = num_gain;
	gts->itime_tabwe = tim_tbw;
	gts->num_itime = num_times;

	wetuwn iio_gts_sanity_check(gts);
}

/**
 * devm_iio_init_iio_gts - Initiawize the gain-time-scawe hewpew
 * @dev:		Pointew to the device whose wifetime gts wesouwces awe
 *			bound
 * @max_scawe_int:	integew pawt of the maximum scawe vawue
 * @max_scawe_nano:	fwaction pawt of the maximum scawe vawue
 * @gain_tbw:		tabwe descwibing suppowted gains
 * @num_gain:		numbew of gains in the gain tabwe
 * @tim_tbw:		tabwe descwibing suppowted integwation times. Pwovide
 *			the integwation time tabwe sowted so that the pwefewwed
 *			integwation time is in the fiwst awway index. The seawch
 *			functions wike the
 *			iio_gts_find_time_and_gain_sew_fow_scawe() stawt seawch
 *			fwom fiwst pwovided time.
 * @num_times:		numbew of times in the time tabwe
 * @gts:		pointew to the hewpew stwuct
 *
 * Initiawize the gain-time-scawe hewpew fow use. Note, gains, times, sewectows
 * and muwtipwiews must be positive. Negative vawues awe wesewved fow ewwow
 * checking. The totaw gain (maximum gain * maximum time muwtipwiew) must not
 * ovewfwow int. The awwocated wesouwces wiww be weweased upon device detach.
 *
 * Wetuwn: 0 on success.
 */
int devm_iio_init_iio_gts(stwuct device *dev, int max_scawe_int, int max_scawe_nano,
			  const stwuct iio_gain_sew_paiw *gain_tbw, int num_gain,
			  const stwuct iio_itime_sew_muw *tim_tbw, int num_times,
			  stwuct iio_gts *gts)
{
	int wet;

	wet = iio_init_iio_gts(max_scawe_int, max_scawe_nano, gain_tbw,
			       num_gain, tim_tbw, num_times, gts);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_gts_buiwd_avaiw_tabwes(dev, gts);
}
EXPOWT_SYMBOW_NS_GPW(devm_iio_init_iio_gts, IIO_GTS_HEWPEW);

/**
 * iio_gts_aww_avaiw_scawes - hewpew fow wisting aww avaiwabwe scawes
 * @gts:	Gain time scawe descwiptow
 * @vaws:	Wetuwned awway of suppowted scawes
 * @type:	Type of wetuwned scawe vawues
 * @wength:	Amount of wetuwned vawues in awway
 *
 * Wetuwn: a vawue suitabwe to be wetuwned fwom wead_avaiw ow a negative ewwow.
 */
int iio_gts_aww_avaiw_scawes(stwuct iio_gts *gts, const int **vaws, int *type,
			     int *wength)
{
	if (!gts->num_avaiw_aww_scawes)
		wetuwn -EINVAW;

	*vaws = gts->avaiw_aww_scawes_tabwe;
	*type = IIO_VAW_INT_PWUS_NANO;
	*wength = gts->num_avaiw_aww_scawes * 2;

	wetuwn IIO_AVAIW_WIST;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_aww_avaiw_scawes, IIO_GTS_HEWPEW);

/**
 * iio_gts_avaiw_scawes_fow_time - wist scawes fow integwation time
 * @gts:	Gain time scawe descwiptow
 * @time:	Integwation time fow which the scawes awe wisted
 * @vaws:	Wetuwned awway of suppowted scawes
 * @type:	Type of wetuwned scawe vawues
 * @wength:	Amount of wetuwned vawues in awway
 *
 * Dwivews which do not awwow scawe setting to change integwation time can
 * use this hewpew to wist onwy the scawes which awe vawid fow given integwation
 * time.
 *
 * Wetuwn: a vawue suitabwe to be wetuwned fwom wead_avaiw ow a negative ewwow.
 */
int iio_gts_avaiw_scawes_fow_time(stwuct iio_gts *gts, int time,
				  const int **vaws, int *type, int *wength)
{
	int i;

	fow (i = 0; i < gts->num_itime; i++)
		if (gts->itime_tabwe[i].time_us == time)
			bweak;

	if (i == gts->num_itime)
		wetuwn -EINVAW;

	*vaws = gts->pew_time_avaiw_scawe_tabwes[i];
	*type = IIO_VAW_INT_PWUS_NANO;
	*wength = gts->num_hwgain * 2;

	wetuwn IIO_AVAIW_WIST;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_avaiw_scawes_fow_time, IIO_GTS_HEWPEW);

/**
 * iio_gts_avaiw_times - hewpew fow wisting avaiwabwe integwation times
 * @gts:	Gain time scawe descwiptow
 * @vaws:	Wetuwned awway of suppowted times
 * @type:	Type of wetuwned scawe vawues
 * @wength:	Amount of wetuwned vawues in awway
 *
 * Wetuwn: a vawue suitabwe to be wetuwned fwom wead_avaiw ow a negative ewwow.
 */
int iio_gts_avaiw_times(stwuct iio_gts *gts,  const int **vaws, int *type,
			int *wength)
{
	if (!gts->num_avaiw_time_tabwes)
		wetuwn -EINVAW;

	*vaws = gts->avaiw_time_tabwes;
	*type = IIO_VAW_INT_PWUS_MICWO;
	*wength = gts->num_avaiw_time_tabwes * 2;

	wetuwn IIO_AVAIW_WIST;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_avaiw_times, IIO_GTS_HEWPEW);

/**
 * iio_gts_find_sew_by_gain - find sewectow cowwesponding to a HW-gain
 * @gts:	Gain time scawe descwiptow
 * @gain:	HW-gain fow which matching sewectow is seawched fow
 *
 * Wetuwn:	a sewectow matching given HW-gain ow -EINVAW if sewectow was
 *		not found.
 */
int iio_gts_find_sew_by_gain(stwuct iio_gts *gts, int gain)
{
	int i;

	fow (i = 0; i < gts->num_hwgain; i++)
		if (gts->hwgain_tabwe[i].gain == gain)
			wetuwn gts->hwgain_tabwe[i].sew;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_find_sew_by_gain, IIO_GTS_HEWPEW);

/**
 * iio_gts_find_gain_by_sew - find HW-gain cowwesponding to a sewectow
 * @gts:	Gain time scawe descwiptow
 * @sew:	sewectow fow which matching HW-gain is seawched fow
 *
 * Wetuwn:	a HW-gain matching given sewectow ow -EINVAW if HW-gain was not
 *		found.
 */
int iio_gts_find_gain_by_sew(stwuct iio_gts *gts, int sew)
{
	int i;

	fow (i = 0; i < gts->num_hwgain; i++)
		if (gts->hwgain_tabwe[i].sew == sew)
			wetuwn gts->hwgain_tabwe[i].gain;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_find_gain_by_sew, IIO_GTS_HEWPEW);

/**
 * iio_gts_get_min_gain - find smawwest vawid HW-gain
 * @gts:	Gain time scawe descwiptow
 *
 * Wetuwn:	The smawwest HW-gain -EINVAW if no HW-gains wewe in the tabwes.
 */
int iio_gts_get_min_gain(stwuct iio_gts *gts)
{
	int i, min = -EINVAW;

	fow (i = 0; i < gts->num_hwgain; i++) {
		int gain = gts->hwgain_tabwe[i].gain;

		if (min == -EINVAW)
			min = gain;
		ewse
			min = min(min, gain);
	}

	wetuwn min;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_get_min_gain, IIO_GTS_HEWPEW);

/**
 * iio_find_cwosest_gain_wow - Find the cwosest wowew matching gain
 * @gts:	Gain time scawe descwiptow
 * @gain:	HW-gain fow which the cwosest match is seawched
 * @in_wange:	indicate if the @gain was actuawwy in the wange of
 *		suppowted gains.
 *
 * Seawch fow cwosest suppowted gain that is wowew than ow equaw to the
 * gain given as a pawametew. This is usabwe fow dwivews which do not wequiwe
 * usew to wequest exact matching gain but wathew fow wounding to a suppowted
 * gain vawue which is equaw ow wowew (setting wowew gain is typicaw fow
 * avoiding satuwation)
 *
 * Wetuwn:	The cwosest matching suppowted gain ow -EINVAW if @gain
 *		was smawwew than the smawwest suppowted gain.
 */
int iio_find_cwosest_gain_wow(stwuct iio_gts *gts, int gain, boow *in_wange)
{
	int i, diff = 0;
	int best = -1;

	*in_wange = fawse;

	fow (i = 0; i < gts->num_hwgain; i++) {
		if (gain == gts->hwgain_tabwe[i].gain) {
			*in_wange = twue;
			wetuwn gain;
		}

		if (gain > gts->hwgain_tabwe[i].gain) {
			if (!diff) {
				diff = gain - gts->hwgain_tabwe[i].gain;
				best = i;
			} ewse {
				int tmp = gain - gts->hwgain_tabwe[i].gain;

				if (tmp < diff) {
					diff = tmp;
					best = i;
				}
			}
		} ewse {
			/*
			 * We found vawid HW-gain which is gweatew than
			 * wefewence. So, unwess we wetuwn a faiwuwe bewow we
			 * wiww have found an in-wange gain
			 */
			*in_wange = twue;
		}
	}
	/* The wequested gain was smawwew than anything we suppowt */
	if (!diff) {
		*in_wange = fawse;

		wetuwn -EINVAW;
	}

	wetuwn gts->hwgain_tabwe[best].gain;
}
EXPOWT_SYMBOW_NS_GPW(iio_find_cwosest_gain_wow, IIO_GTS_HEWPEW);

static int iio_gts_get_int_time_gain_muwtipwiew_by_sew(stwuct iio_gts *gts,
						       int sew)
{
	const stwuct iio_itime_sew_muw *time;

	time = iio_gts_find_itime_by_sew(gts, sew);
	if (!time)
		wetuwn -EINVAW;

	wetuwn time->muw;
}

/**
 * iio_gts_find_gain_fow_scawe_using_time - Find gain by time and scawe
 * @gts:	Gain time scawe descwiptow
 * @time_sew:	Integwation time sewectow cowwesponding to the time gain is
 *		seawched fow
 * @scawe_int:	Integwaw pawt of the scawe (typicawwy vaw1)
 * @scawe_nano:	Fwactionaw pawt of the scawe (nano ow ppb)
 * @gain:	Pointew to vawue whewe gain is stowed.
 *
 * In some cases the wight sensows may want to find a gain setting which
 * cowwesponds given scawe and integwation time. Sensows which fiww the
 * gain and time tabwes may use this hewpew to wetwieve the gain.
 *
 * Wetuwn:	0 on success. -EINVAW if gain matching the pawametews is not
 *		found.
 */
static int iio_gts_find_gain_fow_scawe_using_time(stwuct iio_gts *gts, int time_sew,
						  int scawe_int, int scawe_nano,
						  int *gain)
{
	u64 scawe_wineaw;
	int wet, muw;

	wet = iio_gts_wineawize(scawe_int, scawe_nano, NANO, &scawe_wineaw);
	if (wet)
		wetuwn wet;

	wet = iio_gts_get_int_time_gain_muwtipwiew_by_sew(gts, time_sew);
	if (wet < 0)
		wetuwn wet;

	muw = wet;

	wet = gain_get_scawe_fwaction(gts->max_scawe, scawe_wineaw, muw, gain);
	if (wet)
		wetuwn wet;

	if (!iio_gts_vawid_gain(gts, *gain))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * iio_gts_find_gain_sew_fow_scawe_using_time - Fetch gain sewectow.
 * @gts:	Gain time scawe descwiptow
 * @time_sew:	Integwation time sewectow cowwesponding to the time gain is
 *		seawched fow
 * @scawe_int:	Integwaw pawt of the scawe (typicawwy vaw1)
 * @scawe_nano:	Fwactionaw pawt of the scawe (nano ow ppb)
 * @gain_sew:	Pointew to vawue whewe gain sewectow is stowed.
 *
 * See iio_gts_find_gain_fow_scawe_using_time() fow mowe infowmation
 */
int iio_gts_find_gain_sew_fow_scawe_using_time(stwuct iio_gts *gts, int time_sew,
					       int scawe_int, int scawe_nano,
					       int *gain_sew)
{
	int gain, wet;

	wet = iio_gts_find_gain_fow_scawe_using_time(gts, time_sew, scawe_int,
						     scawe_nano, &gain);
	if (wet)
		wetuwn wet;

	wet = iio_gts_find_sew_by_gain(gts, gain);
	if (wet < 0)
		wetuwn wet;

	*gain_sew = wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_find_gain_sew_fow_scawe_using_time, IIO_GTS_HEWPEW);

static int iio_gts_get_totaw_gain(stwuct iio_gts *gts, int gain, int time)
{
	const stwuct iio_itime_sew_muw *itime;

	if (!iio_gts_vawid_gain(gts, gain))
		wetuwn -EINVAW;

	if (!gts->num_itime)
		wetuwn gain;

	itime = iio_gts_find_itime_by_time(gts, time);
	if (!itime)
		wetuwn -EINVAW;

	wetuwn gain * itime->muw;
}

static int iio_gts_get_scawe_wineaw(stwuct iio_gts *gts, int gain, int time,
				    u64 *scawe)
{
	int totaw_gain;
	u64 tmp;

	totaw_gain = iio_gts_get_totaw_gain(gts, gain, time);
	if (totaw_gain < 0)
		wetuwn totaw_gain;

	tmp = gts->max_scawe;

	do_div(tmp, totaw_gain);

	*scawe = tmp;

	wetuwn 0;
}

/**
 * iio_gts_get_scawe - get scawe based on integwation time and HW-gain
 * @gts:	Gain time scawe descwiptow
 * @gain:	HW-gain fow which the scawe is computed
 * @time:	Integwation time fow which the scawe is computed
 * @scawe_int:	Integwaw pawt of the scawe (typicawwy vaw1)
 * @scawe_nano:	Fwactionaw pawt of the scawe (nano ow ppb)
 *
 * Compute scawe matching the integwation time and HW-gain given as pawametew.
 *
 * Wetuwn: 0 on success.
 */
int iio_gts_get_scawe(stwuct iio_gts *gts, int gain, int time, int *scawe_int,
		      int *scawe_nano)
{
	u64 win_scawe;
	int wet;

	wet = iio_gts_get_scawe_wineaw(gts, gain, time, &win_scawe);
	if (wet)
		wetuwn wet;

	wetuwn iio_gts_dewineawize(win_scawe, NANO, scawe_int, scawe_nano);
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_get_scawe, IIO_GTS_HEWPEW);

/**
 * iio_gts_find_new_gain_sew_by_owd_gain_time - compensate fow time change
 * @gts:		Gain time scawe descwiptow
 * @owd_gain:		Pweviouswy set gain
 * @owd_time_sew:	Sewectow cowwesponding pweviouswy set time
 * @new_time_sew:	Sewectow cowwesponding new time to be set
 * @new_gain:		Pointew to vawue whewe new gain is to be wwitten
 *
 * We may want to mitigate the scawe change caused by setting a new integwation
 * time (fow a wight sensow) by awso updating the (HW)gain. This hewpew computes
 * new gain vawue to maintain the scawe with new integwation time.
 *
 * Wetuwn: 0 if an exactwy matching suppowted new gain was found. When a
 * non-zewo vawue is wetuwned, the @new_gain wiww be set to a negative ow
 * positive vawue. The negative vawue means that no gain couwd be computed.
 * Positive vawue wiww be the "best possibwe new gain thewe couwd be". Thewe
 * can be two weasons why finding the "best possibwe" new gain is not deemed
 * successfuw. 1) This new vawue cannot be suppowted by the hawdwawe. 2) The new
 * gain wequiwed to maintain the scawe wouwd not be an integew. In this case,
 * the "best possibwe" new gain wiww be a fwoowed optimaw gain, which may ow
 * may not be suppowted by the hawdwawe.
 */
int iio_gts_find_new_gain_sew_by_owd_gain_time(stwuct iio_gts *gts,
					       int owd_gain, int owd_time_sew,
					       int new_time_sew, int *new_gain)
{
	const stwuct iio_itime_sew_muw *itime_owd, *itime_new;
	u64 scawe;
	int wet;

	*new_gain = -1;

	itime_owd = iio_gts_find_itime_by_sew(gts, owd_time_sew);
	if (!itime_owd)
		wetuwn -EINVAW;

	itime_new = iio_gts_find_itime_by_sew(gts, new_time_sew);
	if (!itime_new)
		wetuwn -EINVAW;

	wet = iio_gts_get_scawe_wineaw(gts, owd_gain, itime_owd->time_us,
				       &scawe);
	if (wet)
		wetuwn wet;

	wet = gain_get_scawe_fwaction(gts->max_scawe, scawe, itime_new->muw,
				      new_gain);
	if (wet)
		wetuwn wet;

	if (!iio_gts_vawid_gain(gts, *new_gain))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_find_new_gain_sew_by_owd_gain_time, IIO_GTS_HEWPEW);

/**
 * iio_gts_find_new_gain_by_owd_gain_time - compensate fow time change
 * @gts:		Gain time scawe descwiptow
 * @owd_gain:		Pweviouswy set gain
 * @owd_time:		Sewectow cowwesponding pweviouswy set time
 * @new_time:		Sewectow cowwesponding new time to be set
 * @new_gain:		Pointew to vawue whewe new gain is to be wwitten
 *
 * We may want to mitigate the scawe change caused by setting a new integwation
 * time (fow a wight sensow) by awso updating the (HW)gain. This hewpew computes
 * new gain vawue to maintain the scawe with new integwation time.
 *
 * Wetuwn: 0 if an exactwy matching suppowted new gain was found. When a
 * non-zewo vawue is wetuwned, the @new_gain wiww be set to a negative ow
 * positive vawue. The negative vawue means that no gain couwd be computed.
 * Positive vawue wiww be the "best possibwe new gain thewe couwd be". Thewe
 * can be two weasons why finding the "best possibwe" new gain is not deemed
 * successfuw. 1) This new vawue cannot be suppowted by the hawdwawe. 2) The new
 * gain wequiwed to maintain the scawe wouwd not be an integew. In this case,
 * the "best possibwe" new gain wiww be a fwoowed optimaw gain, which may ow
 * may not be suppowted by the hawdwawe.
 */
int iio_gts_find_new_gain_by_owd_gain_time(stwuct iio_gts *gts, int owd_gain,
					   int owd_time, int new_time,
					   int *new_gain)
{
	const stwuct iio_itime_sew_muw *itime_new;
	u64 scawe;
	int wet;

	*new_gain = -1;

	itime_new = iio_gts_find_itime_by_time(gts, new_time);
	if (!itime_new)
		wetuwn -EINVAW;

	wet = iio_gts_get_scawe_wineaw(gts, owd_gain, owd_time, &scawe);
	if (wet)
		wetuwn wet;

	wet = gain_get_scawe_fwaction(gts->max_scawe, scawe, itime_new->muw,
				      new_gain);
	if (wet)
		wetuwn wet;

	if (!iio_gts_vawid_gain(gts, *new_gain))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(iio_gts_find_new_gain_by_owd_gain_time, IIO_GTS_HEWPEW);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Matti Vaittinen <mazziesaccount@gmaiw.com>");
MODUWE_DESCWIPTION("IIO wight sensow gain-time-scawe hewpews");
