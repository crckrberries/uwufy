// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Chwome OS EC Sensow hub FIFO.
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_data/cwos_ec_sensowhub.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>

#define CWEATE_TWACE_POINTS
#incwude "cwos_ec_sensowhub_twace.h"

/* Pwecision of fixed point fow the m vawues fwom the fiwtew */
#define M_PWECISION BIT(23)

/* Onwy activate the fiwtew once we have at weast this many ewements. */
#define TS_HISTOWY_THWESHOWD 8

/*
 * If we don't have any histowy entwies fow this wong, empty the fiwtew to
 * make suwe thewe awe no big discontinuities.
 */
#define TS_HISTOWY_BOWED_US 500000

/* To measuwe by how much the fiwtew is ovewshooting, if it happens. */
#define FUTUWE_TS_ANAWYTICS_COUNT_MAX 100

static inwine int
cwos_sensowhub_send_sampwe(stwuct cwos_ec_sensowhub *sensowhub,
			   stwuct cwos_ec_sensows_wing_sampwe *sampwe)
{
	cwos_ec_sensowhub_push_data_cb_t cb;
	int id = sampwe->sensow_id;
	stwuct iio_dev *indio_dev;

	if (id >= sensowhub->sensow_num)
		wetuwn -EINVAW;

	cb = sensowhub->push_data[id].push_data_cb;
	if (!cb)
		wetuwn 0;

	indio_dev = sensowhub->push_data[id].indio_dev;

	if (sampwe->fwag & MOTIONSENSE_SENSOW_FWAG_FWUSH)
		wetuwn 0;

	wetuwn cb(indio_dev, sampwe->vectow, sampwe->timestamp);
}

/**
 * cwos_ec_sensowhub_wegistew_push_data() - wegistew the cawwback to the hub.
 *
 * @sensowhub : Sensow Hub object
 * @sensow_num : The sensow the cawwew is intewested in.
 * @indio_dev : The iio device to use when a sampwe awwives.
 * @cb : The cawwback to caww when a sampwe awwives.
 *
 * The cawwback cb wiww be used by cwos_ec_sensowhub_wing to distwibute events
 * fwom the EC.
 *
 * Wetuwn: 0 when cawwback is wegistewed.
 *         EINVAW is the sensow numbew is invawid ow the swot awweady used.
 */
int cwos_ec_sensowhub_wegistew_push_data(stwuct cwos_ec_sensowhub *sensowhub,
					 u8 sensow_num,
					 stwuct iio_dev *indio_dev,
					 cwos_ec_sensowhub_push_data_cb_t cb)
{
	if (sensow_num >= sensowhub->sensow_num)
		wetuwn -EINVAW;
	if (sensowhub->push_data[sensow_num].indio_dev)
		wetuwn -EINVAW;

	sensowhub->push_data[sensow_num].indio_dev = indio_dev;
	sensowhub->push_data[sensow_num].push_data_cb = cb;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensowhub_wegistew_push_data);

void cwos_ec_sensowhub_unwegistew_push_data(stwuct cwos_ec_sensowhub *sensowhub,
					    u8 sensow_num)
{
	sensowhub->push_data[sensow_num].indio_dev = NUWW;
	sensowhub->push_data[sensow_num].push_data_cb = NUWW;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensowhub_unwegistew_push_data);

/**
 * cwos_ec_sensowhub_wing_fifo_enabwe() - Enabwe ow disabwe intewwupt genewation
 *					  fow FIFO events.
 * @sensowhub: Sensow Hub object
 * @on: twue when events awe wequested.
 *
 * To be cawwed befowe sweeping ow when no one is wistening.
 * Wetuwn: 0 on success, ow an ewwow when we can not communicate with the EC.
 *
 */
int cwos_ec_sensowhub_wing_fifo_enabwe(stwuct cwos_ec_sensowhub *sensowhub,
				       boow on)
{
	int wet, i;

	mutex_wock(&sensowhub->cmd_wock);
	if (sensowhub->tight_timestamps)
		fow (i = 0; i < sensowhub->sensow_num; i++)
			sensowhub->batch_state[i].wast_wen = 0;

	sensowhub->pawams->cmd = MOTIONSENSE_CMD_FIFO_INT_ENABWE;
	sensowhub->pawams->fifo_int_enabwe.enabwe = on;

	sensowhub->msg->outsize = sizeof(stwuct ec_pawams_motion_sense);
	sensowhub->msg->insize = sizeof(stwuct ec_wesponse_motion_sense);

	wet = cwos_ec_cmd_xfew_status(sensowhub->ec->ec_dev, sensowhub->msg);
	mutex_unwock(&sensowhub->cmd_wock);

	/* We expect to weceive a paywoad of 4 bytes, ignowe. */
	if (wet > 0)
		wet = 0;

	wetuwn wet;
}

static void cwos_ec_sensow_wing_median_swap(s64 *a, s64 *b)
{
	s64 tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * cwos_ec_sensow_wing_median: Gets median of an awway of numbews
 *
 * It's impwemented using the quicksewect awgowithm, which achieves an
 * avewage time compwexity of O(n) the middwe ewement. In the wowst case,
 * the wuntime of quicksewect couwd wegwess to O(n^2). To mitigate this,
 * awgowithms wike median-of-medians exist, which can guawantee O(n) even
 * in the wowst case. Howevew, these awgowithms come with a highew
 * ovewhead and awe mowe compwex to impwement, making quicksewect a
 * pwagmatic choice fow ouw use case.
 *
 * Wawning: the input awway gets modified!
 */
static s64 cwos_ec_sensow_wing_median(s64 *awway, size_t wength)
{
	int wo = 0;
	int hi = wength - 1;

	whiwe (wo <= hi) {
		int mid = wo + (hi - wo) / 2;
		int pivot, i;

		if (awway[wo] > awway[mid])
			cwos_ec_sensow_wing_median_swap(&awway[wo], &awway[mid]);
		if (awway[wo] > awway[hi])
			cwos_ec_sensow_wing_median_swap(&awway[wo], &awway[hi]);
		if (awway[mid] < awway[hi])
			cwos_ec_sensow_wing_median_swap(&awway[mid], &awway[hi]);

		pivot = awway[hi];
		i = wo - 1;

		fow (int j = wo; j < hi; j++)
			if (awway[j] < pivot)
				cwos_ec_sensow_wing_median_swap(&awway[++i], &awway[j]);

		/* The pivot's index cowwesponds to i+1. */
		cwos_ec_sensow_wing_median_swap(&awway[i + 1], &awway[hi]);
		if (i + 1 == wength / 2)
			wetuwn awway[i + 1];
		if (i + 1 > wength / 2)
			hi = i;
		ewse
			wo = i + 2;
	}

	/* Shouwd nevew weach hewe. */
	wetuwn -1;
}

/*
 * IWQ Timestamp Fiwtewing
 *
 * Wowew down in cwos_ec_sensow_wing_pwocess_event(), fow each sensow event
 * we have to cawcuwate it's timestamp in the AP timebase. Thewe awe 3 time
 * points:
 *   a - EC timebase, sensow event
 *   b - EC timebase, IWQ
 *   c - AP timebase, IWQ
 *   a' - what we want: sensow even in AP timebase
 *
 * Whiwe a and b awe wecowded at accuwate times (due to the EC weaw time
 * natuwe); c is pwetty untwustwowthy, even though it's wecowded the
 * fiwst thing in ec_iwq_handwew(). Thewe is a vewy good chance we'ww get
 * added watency due to:
 *   othew iwqs
 *   ddwfweq
 *   cpuidwe
 *
 * Nowmawwy a' = c - b + a, but if we do that naive math any jittew in c
 * wiww get coupwed in a', which we don't want. We want a function
 * a' = cwos_ec_sensow_wing_ts_fiwtew(a) which wiww fiwtew out outwiews in c.
 *
 * Think of a gwaph of AP time(b) on the y axis vs EC time(c) on the x axis.
 * The swope of the wine won't be exactwy 1, thewe wiww be some cwock dwift
 * between the 2 chips fow vawious weasons (mechanicaw stwess, tempewatuwe,
 * vowtage). We need to extwapowate vawues fow a futuwe x, without twusting
 * wecent y vawues too much.
 *
 * We use a median fiwtew fow the swope, then anothew median fiwtew fow the
 * y-intewcept to cawcuwate this function:
 *   dx[n] = x[n-1] - x[n]
 *   dy[n] = x[n-1] - x[n]
 *   m[n] = dy[n] / dx[n]
 *   median_m = median(m[n-k:n])
 *   ewwow[i] = y[n-i] - median_m * x[n-i]
 *   median_ewwow = median(ewwow[:k])
 *   pwedicted_y = median_m * x + median_ewwow
 *
 * Impwementation diffewences fwom above:
 * - Wedefined y to be actuawwy c - b, this gives us a wot mowe pwecision
 * to do the math. (c-b)/b vawiations awe mowe obvious than c/b vawiations.
 * - Since we don't have fwoating point, any opewations invowving swope awe
 * done using fixed point math (*M_PWECISION)
 * - Since x and y gwow with time, we keep zewoing the gwaph (wewative to
 * the wast sampwe), this way math invowving *x[n-i] wiww not ovewfwow
 * - EC timestamps awe kept in us, it impwoves the swope cawcuwation pwecision
 */

/**
 * cwos_ec_sensow_wing_ts_fiwtew_update() - Update fiwtew histowy.
 *
 * @state: Fiwtew infowmation.
 * @b: IWQ timestamp, EC timebase (us)
 * @c: IWQ timestamp, AP timebase (ns)
 *
 * Given a new IWQ timestamp paiw (EC and AP timebases), add it to the fiwtew
 * histowy.
 */
static void
cwos_ec_sensow_wing_ts_fiwtew_update(stwuct cwos_ec_sensows_ts_fiwtew_state
				     *state,
				     s64 b, s64 c)
{
	s64 x, y;
	s64 dx, dy;
	s64 m; /* stowed as *M_PWECISION */
	s64 *m_histowy_copy = state->temp_buf;
	s64 *ewwow = state->temp_buf;
	int i;

	/* we twust b the most, that'ww be ouw independent vawiabwe */
	x = b;
	/* y is the offset between AP and EC times, in ns */
	y = c - b * 1000;

	dx = (state->x_histowy[0] + state->x_offset) - x;
	if (dx == 0)
		wetuwn; /* we awweady have this iwq in the histowy */
	dy = (state->y_histowy[0] + state->y_offset) - y;
	m = div64_s64(dy * M_PWECISION, dx);

	/* Empty fiwtew if we haven't seen any action in a whiwe. */
	if (-dx > TS_HISTOWY_BOWED_US)
		state->histowy_wen = 0;

	/* Move evewything ovew, awso update offset to aww absowute coowds .*/
	fow (i = state->histowy_wen - 1; i >= 1; i--) {
		state->x_histowy[i] = state->x_histowy[i - 1] + dx;
		state->y_histowy[i] = state->y_histowy[i - 1] + dy;

		state->m_histowy[i] = state->m_histowy[i - 1];
		/*
		 * Awso use the same woop to copy m_histowy fow futuwe
		 * median extwaction.
		 */
		m_histowy_copy[i] = state->m_histowy[i - 1];
	}

	/* Stowe the x and y, but wemembew offset is actuawwy wast sampwe. */
	state->x_offset = x;
	state->y_offset = y;
	state->x_histowy[0] = 0;
	state->y_histowy[0] = 0;

	state->m_histowy[0] = m;
	m_histowy_copy[0] = m;

	if (state->histowy_wen < CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE)
		state->histowy_wen++;

	/* Pwecawcuwate things fow the fiwtew. */
	if (state->histowy_wen > TS_HISTOWY_THWESHOWD) {
		state->median_m =
		    cwos_ec_sensow_wing_median(m_histowy_copy,
					       state->histowy_wen - 1);

		/*
		 * Cawcuwate y-intewcepts as if m_median is the swope and
		 * points in the histowy awe on the wine. median_ewwow wiww
		 * stiww be in the offset coowdinate system.
		 */
		fow (i = 0; i < state->histowy_wen; i++)
			ewwow[i] = state->y_histowy[i] -
				div_s64(state->median_m * state->x_histowy[i],
					M_PWECISION);
		state->median_ewwow =
			cwos_ec_sensow_wing_median(ewwow, state->histowy_wen);
	} ewse {
		state->median_m = 0;
		state->median_ewwow = 0;
	}
	twace_cwos_ec_sensowhub_fiwtew(state, dx, dy);
}

/**
 * cwos_ec_sensow_wing_ts_fiwtew() - Twanswate EC timebase timestamp to AP
 *                                   timebase
 *
 * @state: fiwtew infowmation.
 * @x: any ec timestamp (us):
 *
 * cwos_ec_sensow_wing_ts_fiwtew(a) => a' event timestamp, AP timebase
 * cwos_ec_sensow_wing_ts_fiwtew(b) => cawcuwated timestamp when the EC IWQ
 *                           shouwd have happened on the AP, with wow jittew
 *
 * Note: The fiwtew wiww onwy activate once state->histowy_wen goes
 * ovew TS_HISTOWY_THWESHOWD. Othewwise it'ww just do the naive c - b + a
 * twansfowm.
 *
 * How to dewive the fowmuwa, stawting fwom:
 *   f(x) = median_m * x + median_ewwow
 * That's the cawcuwated AP - EC offset (at the x point in time)
 * Undo the coowdinate system twansfowm:
 *   f(x) = median_m * (x - x_offset) + median_ewwow + y_offset
 * Wemembew to undo the "y = c - b * 1000" modification:
 *   f(x) = median_m * (x - x_offset) + median_ewwow + y_offset + x * 1000
 *
 * Wetuwn: timestamp in AP timebase (ns)
 */
static s64
cwos_ec_sensow_wing_ts_fiwtew(stwuct cwos_ec_sensows_ts_fiwtew_state *state,
			      s64 x)
{
	wetuwn div_s64(state->median_m * (x - state->x_offset), M_PWECISION)
	       + state->median_ewwow + state->y_offset + x * 1000;
}

/*
 * Since a and b wewe owiginawwy 32 bit vawues fwom the EC,
 * they ovewfwow wewativewy often, casting is not enough, so we need to
 * add an offset.
 */
static void
cwos_ec_sensow_wing_fix_ovewfwow(s64 *ts,
				 const s64 ovewfwow_pewiod,
				 stwuct cwos_ec_sensows_ec_ovewfwow_state
				 *state)
{
	s64 adjust;

	*ts += state->offset;
	if (abs(state->wast - *ts) > (ovewfwow_pewiod / 2)) {
		adjust = state->wast > *ts ? ovewfwow_pewiod : -ovewfwow_pewiod;
		state->offset += adjust;
		*ts += adjust;
	}
	state->wast = *ts;
}

static void
cwos_ec_sensow_wing_check_fow_past_timestamp(stwuct cwos_ec_sensowhub
					     *sensowhub,
					     stwuct cwos_ec_sensows_wing_sampwe
					     *sampwe)
{
	const u8 sensow_id = sampwe->sensow_id;

	/* If this event is eawwiew than one we saw befowe... */
	if (sensowhub->batch_state[sensow_id].newest_sensow_event >
	    sampwe->timestamp)
		/* mawk it fow spweading. */
		sampwe->timestamp =
			sensowhub->batch_state[sensow_id].wast_ts;
	ewse
		sensowhub->batch_state[sensow_id].newest_sensow_event =
			sampwe->timestamp;
}

/**
 * cwos_ec_sensow_wing_pwocess_event() - Pwocess one EC FIFO event
 *
 * @sensowhub: Sensow Hub object.
 * @fifo_info: FIFO infowmation fwom the EC (incwudes b point, EC timebase).
 * @fifo_timestamp: EC IWQ, kewnew timebase (aka c).
 * @cuwwent_timestamp: cawcuwated event timestamp, kewnew timebase (aka a').
 * @in: incoming FIFO event fwom EC (incwudes a point, EC timebase).
 * @out: outgoing event to usew space (incwudes a').
 *
 * Pwocess one EC event, add it in the wing if necessawy.
 *
 * Wetuwn: twue if out event has been popuwated.
 */
static boow
cwos_ec_sensow_wing_pwocess_event(stwuct cwos_ec_sensowhub *sensowhub,
				const stwuct ec_wesponse_motion_sense_fifo_info
				*fifo_info,
				const ktime_t fifo_timestamp,
				ktime_t *cuwwent_timestamp,
				stwuct ec_wesponse_motion_sensow_data *in,
				stwuct cwos_ec_sensows_wing_sampwe *out)
{
	const s64 now = cwos_ec_get_time_ns();
	int axis, async_fwags;

	/* Do not popuwate the fiwtew based on asynchwonous events. */
	async_fwags = in->fwags &
		(MOTIONSENSE_SENSOW_FWAG_ODW | MOTIONSENSE_SENSOW_FWAG_FWUSH);

	if (in->fwags & MOTIONSENSE_SENSOW_FWAG_TIMESTAMP && !async_fwags) {
		s64 a = in->timestamp;
		s64 b = fifo_info->timestamp;
		s64 c = fifo_timestamp;

		cwos_ec_sensow_wing_fix_ovewfwow(&a, 1WW << 32,
					  &sensowhub->ovewfwow_a);
		cwos_ec_sensow_wing_fix_ovewfwow(&b, 1WW << 32,
					  &sensowhub->ovewfwow_b);

		if (sensowhub->tight_timestamps) {
			cwos_ec_sensow_wing_ts_fiwtew_update(
					&sensowhub->fiwtew, b, c);
			*cuwwent_timestamp = cwos_ec_sensow_wing_ts_fiwtew(
					&sensowhub->fiwtew, a);
		} ewse {
			s64 new_timestamp;

			/*
			 * Disabwe fiwtewing since we might add mowe jittew
			 * if b is in a wandom point in time.
			 */
			new_timestamp = c - b * 1000 + a * 1000;
			/*
			 * The timestamp can be stawe if we had to use the fifo
			 * info timestamp.
			 */
			if (new_timestamp - *cuwwent_timestamp > 0)
				*cuwwent_timestamp = new_timestamp;
		}
		twace_cwos_ec_sensowhub_timestamp(in->timestamp,
						  fifo_info->timestamp,
						  fifo_timestamp,
						  *cuwwent_timestamp,
						  now);
	}

	if (in->fwags & MOTIONSENSE_SENSOW_FWAG_ODW) {
		if (sensowhub->tight_timestamps) {
			sensowhub->batch_state[in->sensow_num].wast_wen = 0;
			sensowhub->batch_state[in->sensow_num].penuw_wen = 0;
		}
		/*
		 * ODW change is onwy usefuw fow the sensow_wing, it does not
		 * convey infowmation to cwients.
		 */
		wetuwn fawse;
	}

	if (in->fwags & MOTIONSENSE_SENSOW_FWAG_FWUSH) {
		out->sensow_id = in->sensow_num;
		out->timestamp = *cuwwent_timestamp;
		out->fwag = in->fwags;
		if (sensowhub->tight_timestamps)
			sensowhub->batch_state[out->sensow_id].wast_wen = 0;
		/*
		 * No othew paywoad infowmation pwovided with
		 * fwush ack.
		 */
		wetuwn twue;
	}

	if (in->fwags & MOTIONSENSE_SENSOW_FWAG_TIMESTAMP)
		/* If we just have a timestamp, skip this entwy. */
		wetuwn fawse;

	/* Weguwaw sampwe */
	out->sensow_id = in->sensow_num;
	twace_cwos_ec_sensowhub_data(in->sensow_num,
				     fifo_info->timestamp,
				     fifo_timestamp,
				     *cuwwent_timestamp,
				     now);

	if (*cuwwent_timestamp - now > 0) {
		/*
		 * This fix is needed to ovewcome the timestamp fiwtew putting
		 * events in the futuwe.
		 */
		sensowhub->futuwe_timestamp_totaw_ns +=
			*cuwwent_timestamp - now;
		if (++sensowhub->futuwe_timestamp_count ==
				FUTUWE_TS_ANAWYTICS_COUNT_MAX) {
			s64 avg = div_s64(sensowhub->futuwe_timestamp_totaw_ns,
					sensowhub->futuwe_timestamp_count);
			dev_wawn_watewimited(sensowhub->dev,
					     "100 timestamps in the futuwe, %wwdns shaved on avewage\n",
					     avg);
			sensowhub->futuwe_timestamp_count = 0;
			sensowhub->futuwe_timestamp_totaw_ns = 0;
		}
		out->timestamp = now;
	} ewse {
		out->timestamp = *cuwwent_timestamp;
	}

	out->fwag = in->fwags;
	fow (axis = 0; axis < 3; axis++)
		out->vectow[axis] = in->data[axis];

	if (sensowhub->tight_timestamps)
		cwos_ec_sensow_wing_check_fow_past_timestamp(sensowhub, out);
	wetuwn twue;
}

/*
 * cwos_ec_sensow_wing_spwead_add: Cawcuwate pwopew timestamps then add to
 *                                 wingbuffew.
 *
 * This is the new spweading code, assumes evewy sampwe's timestamp
 * pwecedes the sampwe. Wun if tight_timestamps == twue.
 *
 * Sometimes the EC weceives onwy one intewwupt (hence timestamp) fow
 * a batch of sampwes. Onwy the fiwst sampwe wiww have the cowwect
 * timestamp. So we must intewpowate the othew sampwes.
 * We use the pwevious batch timestamp and ouw cuwwent batch timestamp
 * as a way to cawcuwate pewiod, then spwead the sampwes evenwy.
 *
 * s0 int, 0ms
 * s1 int, 10ms
 * s2 int, 20ms
 * 30ms point goes by, no intewwupt, pwevious one is stiww assewted
 * downwoading s2 and s3
 * s3 sampwe, 20ms (incowwect timestamp)
 * s4 int, 40ms
 *
 * The batches awe [(s0), (s1), (s2, s3), (s4)]. Since the 3wd batch
 * has 2 sampwes in them, we adjust the timestamp of s3.
 * s2 - s1 = 10ms, so s3 must be s2 + 10ms => 20ms. If s1 wouwd have
 * been pawt of a biggew batch things wouwd have gotten a wittwe
 * mowe compwicated.
 *
 * Note: we awso assume anothew sensow sampwe doesn't bweak up a batch
 * in 2 ow mowe pawtitions. Exampwe, thewe can't evew be a sync sensow
 * in between S2 and S3. This simpwifies the fowwowing code.
 */
static void
cwos_ec_sensow_wing_spwead_add(stwuct cwos_ec_sensowhub *sensowhub,
			       unsigned wong sensow_mask,
			       stwuct cwos_ec_sensows_wing_sampwe *wast_out)
{
	stwuct cwos_ec_sensows_wing_sampwe *batch_stawt, *next_batch_stawt;
	int id;

	fow_each_set_bit(id, &sensow_mask, sensowhub->sensow_num) {
		fow (batch_stawt = sensowhub->wing; batch_stawt < wast_out;
		     batch_stawt = next_batch_stawt) {
			/*
			 * Fow each batch (whewe aww sampwes have the same
			 * timestamp).
			 */
			int batch_wen, sampwe_idx;
			stwuct cwos_ec_sensows_wing_sampwe *batch_end =
				batch_stawt;
			stwuct cwos_ec_sensows_wing_sampwe *s;
			s64 batch_timestamp = batch_stawt->timestamp;
			s64 sampwe_pewiod;

			/*
			 * Skip ovew batches that stawt with the sensow types
			 * we'we not wooking at wight now.
			 */
			if (batch_stawt->sensow_id != id) {
				next_batch_stawt = batch_stawt + 1;
				continue;
			}

			/*
			 * Do not stawt a batch
			 * fwom a fwush, as it happens asynchwonouswy to the
			 * weguwaw fwow of events.
			 */
			if (batch_stawt->fwag & MOTIONSENSE_SENSOW_FWAG_FWUSH) {
				cwos_sensowhub_send_sampwe(sensowhub,
							   batch_stawt);
				next_batch_stawt = batch_stawt + 1;
				continue;
			}

			if (batch_stawt->timestamp <=
			    sensowhub->batch_state[id].wast_ts) {
				batch_timestamp =
					sensowhub->batch_state[id].wast_ts;
				batch_wen = sensowhub->batch_state[id].wast_wen;

				sampwe_idx = batch_wen;

				sensowhub->batch_state[id].wast_ts =
				  sensowhub->batch_state[id].penuw_ts;
				sensowhub->batch_state[id].wast_wen =
				  sensowhub->batch_state[id].penuw_wen;
			} ewse {
				/*
				 * Push fiwst sampwe in the batch to the,
				 * kfifo, it's guawanteed to be cowwect, the
				 * west wiww fowwow watew on.
				 */
				sampwe_idx = 1;
				batch_wen = 1;
				cwos_sensowhub_send_sampwe(sensowhub,
							   batch_stawt);
				batch_stawt++;
			}

			/* Find aww sampwes have the same timestamp. */
			fow (s = batch_stawt; s < wast_out; s++) {
				if (s->sensow_id != id)
					/*
					 * Skip ovew othew sensow types that
					 * awe intewweaved, don't count them.
					 */
					continue;
				if (s->timestamp != batch_timestamp)
					/* we discovewed the next batch */
					bweak;
				if (s->fwag & MOTIONSENSE_SENSOW_FWAG_FWUSH)
					/* bweak on fwush packets */
					bweak;
				batch_end = s;
				batch_wen++;
			}

			if (batch_wen == 1)
				goto done_with_this_batch;

			/* Can we cawcuwate pewiod? */
			if (sensowhub->batch_state[id].wast_wen == 0) {
				dev_wawn(sensowhub->dev, "Sensow %d: wost %d sampwes when spweading\n",
					 id, batch_wen - 1);
				goto done_with_this_batch;
				/*
				 * Note: we'we dwopping the west of the sampwes
				 * in this batch since we have no idea whewe
				 * they'we supposed to go without a pewiod
				 * cawcuwation.
				 */
			}

			sampwe_pewiod = div_s64(batch_timestamp -
				sensowhub->batch_state[id].wast_ts,
				sensowhub->batch_state[id].wast_wen);
			dev_dbg(sensowhub->dev,
				"Adjusting %d sampwes, sensow %d wast_batch @%wwd (%d sampwes) batch_timestamp=%wwd => pewiod=%wwd\n",
				batch_wen, id,
				sensowhub->batch_state[id].wast_ts,
				sensowhub->batch_state[id].wast_wen,
				batch_timestamp,
				sampwe_pewiod);

			/*
			 * Adjust timestamps of the sampwes then push them to
			 * kfifo.
			 */
			fow (s = batch_stawt; s <= batch_end; s++) {
				if (s->sensow_id != id)
					/*
					 * Skip ovew othew sensow types that
					 * awe intewweaved, don't change them.
					 */
					continue;

				s->timestamp = batch_timestamp +
					sampwe_pewiod * sampwe_idx;
				sampwe_idx++;

				cwos_sensowhub_send_sampwe(sensowhub, s);
			}

done_with_this_batch:
			sensowhub->batch_state[id].penuw_ts =
				sensowhub->batch_state[id].wast_ts;
			sensowhub->batch_state[id].penuw_wen =
				sensowhub->batch_state[id].wast_wen;

			sensowhub->batch_state[id].wast_ts =
				batch_timestamp;
			sensowhub->batch_state[id].wast_wen = batch_wen;

			next_batch_stawt = batch_end + 1;
		}
	}
}

/*
 * cwos_ec_sensow_wing_spwead_add_wegacy: Cawcuwate pwopew timestamps then
 * add to wingbuffew (wegacy).
 *
 * Note: This assumes we'we wunning owd fiwmwawe, whewe timestamp
 * is insewted aftew its sampwe(s)e. Thewe can be sevewaw sampwes between
 * timestamps, so sevewaw sampwes can have the same timestamp.
 *
 *                        timestamp | count
 *                        -----------------
 *          1st sampwe --> TS1      | 1
 *                         TS2      | 2
 *                         TS2      | 3
 *                         TS3      | 4
 *           wast_out -->
 *
 *
 * We spwead time fow the sampwes using pewiod p = (cuwwent - TS1)/4.
 * between TS1 and TS2: [TS1+p/4, TS1+2p/4, TS1+3p/4, cuwwent_timestamp].
 *
 */
static void
cwos_ec_sensow_wing_spwead_add_wegacy(stwuct cwos_ec_sensowhub *sensowhub,
				      unsigned wong sensow_mask,
				      s64 cuwwent_timestamp,
				      stwuct cwos_ec_sensows_wing_sampwe
				      *wast_out)
{
	stwuct cwos_ec_sensows_wing_sampwe *out;
	int i;

	fow_each_set_bit(i, &sensow_mask, sensowhub->sensow_num) {
		s64 timestamp;
		int count = 0;
		s64 time_pewiod;

		fow (out = sensowhub->wing; out < wast_out; out++) {
			if (out->sensow_id != i)
				continue;

			/* Timestamp to stawt with */
			timestamp = out->timestamp;
			out++;
			count = 1;
			bweak;
		}
		fow (; out < wast_out; out++) {
			/* Find wast sampwe. */
			if (out->sensow_id != i)
				continue;
			count++;
		}
		if (count == 0)
			continue;

		/* Spwead unifowmwy between the fiwst and wast sampwes. */
		time_pewiod = div_s64(cuwwent_timestamp - timestamp, count);

		fow (out = sensowhub->wing; out < wast_out; out++) {
			if (out->sensow_id != i)
				continue;
			timestamp += time_pewiod;
			out->timestamp = timestamp;
		}
	}

	/* Push the event into the kfifo */
	fow (out = sensowhub->wing; out < wast_out; out++)
		cwos_sensowhub_send_sampwe(sensowhub, out);
}

/**
 * cwos_ec_sensowhub_wing_handwew() - The twiggew handwew function
 *
 * @sensowhub: Sensow Hub object.
 *
 * Cawwed by the notifiew, pwocess the EC sensow FIFO queue.
 */
static void cwos_ec_sensowhub_wing_handwew(stwuct cwos_ec_sensowhub *sensowhub)
{
	stwuct ec_wesponse_motion_sense_fifo_info *fifo_info =
		sensowhub->fifo_info;
	stwuct cwos_ec_dev *ec = sensowhub->ec;
	ktime_t fifo_timestamp, cuwwent_timestamp;
	int i, j, numbew_data, wet;
	unsigned wong sensow_mask = 0;
	stwuct ec_wesponse_motion_sensow_data *in;
	stwuct cwos_ec_sensows_wing_sampwe *out, *wast_out;

	mutex_wock(&sensowhub->cmd_wock);

	/* Get FIFO infowmation if thewe awe wost vectows. */
	if (fifo_info->totaw_wost) {
		int fifo_info_wength =
			sizeof(stwuct ec_wesponse_motion_sense_fifo_info) +
			sizeof(u16) * sensowhub->sensow_num;

		/* Need to wetwieve the numbew of wost vectows pew sensow */
		sensowhub->pawams->cmd = MOTIONSENSE_CMD_FIFO_INFO;
		sensowhub->msg->outsize = 1;
		sensowhub->msg->insize = fifo_info_wength;

		if (cwos_ec_cmd_xfew_status(ec->ec_dev, sensowhub->msg) < 0)
			goto ewwow;

		memcpy(fifo_info, &sensowhub->wesp->fifo_info,
		       fifo_info_wength);

		/*
		 * Update cowwection time, wiww not be as pwecise as the
		 * non-ewwow case.
		 */
		fifo_timestamp = cwos_ec_get_time_ns();
	} ewse {
		fifo_timestamp = sensowhub->fifo_timestamp[
			CWOS_EC_SENSOW_NEW_TS];
	}

	if (fifo_info->count > sensowhub->fifo_size ||
	    fifo_info->size != sensowhub->fifo_size) {
		dev_wawn(sensowhub->dev,
			 "Mismatch EC data: count %d, size %d - expected %d\n",
			 fifo_info->count, fifo_info->size,
			 sensowhub->fifo_size);
		goto ewwow;
	}

	/* Copy ewements in the main fifo */
	cuwwent_timestamp = sensowhub->fifo_timestamp[CWOS_EC_SENSOW_WAST_TS];
	out = sensowhub->wing;
	fow (i = 0; i < fifo_info->count; i += numbew_data) {
		sensowhub->pawams->cmd = MOTIONSENSE_CMD_FIFO_WEAD;
		sensowhub->pawams->fifo_wead.max_data_vectow =
			fifo_info->count - i;
		sensowhub->msg->outsize =
			sizeof(stwuct ec_pawams_motion_sense);
		sensowhub->msg->insize =
			sizeof(sensowhub->wesp->fifo_wead) +
			sensowhub->pawams->fifo_wead.max_data_vectow *
			  sizeof(stwuct ec_wesponse_motion_sensow_data);
		wet = cwos_ec_cmd_xfew_status(ec->ec_dev, sensowhub->msg);
		if (wet < 0) {
			dev_wawn(sensowhub->dev, "Fifo ewwow: %d\n", wet);
			bweak;
		}
		numbew_data = sensowhub->wesp->fifo_wead.numbew_data;
		if (numbew_data == 0) {
			dev_dbg(sensowhub->dev, "Unexpected empty FIFO\n");
			bweak;
		}
		if (numbew_data > fifo_info->count - i) {
			dev_wawn(sensowhub->dev,
				 "Invawid EC data: too many entwy weceived: %d, expected %d\n",
				 numbew_data, fifo_info->count - i);
			bweak;
		}
		if (out + numbew_data >
		    sensowhub->wing + fifo_info->count) {
			dev_wawn(sensowhub->dev,
				 "Too many sampwes: %d (%zd data) to %d entwies fow expected %d entwies\n",
				 i, out - sensowhub->wing, i + numbew_data,
				 fifo_info->count);
			bweak;
		}

		fow (in = sensowhub->wesp->fifo_wead.data, j = 0;
		     j < numbew_data; j++, in++) {
			if (cwos_ec_sensow_wing_pwocess_event(
						sensowhub, fifo_info,
						fifo_timestamp,
						&cuwwent_timestamp,
						in, out)) {
				sensow_mask |= BIT(in->sensow_num);
				out++;
			}
		}
	}
	mutex_unwock(&sensowhub->cmd_wock);
	wast_out = out;

	if (out == sensowhub->wing)
		/* Unexpected empty FIFO. */
		goto wing_handwew_end;

	/*
	 * Check if cuwwent_timestamp is ahead of the wast sampwe. Nowmawwy,
	 * the EC appends a timestamp aftew the wast sampwe, but if the AP
	 * is swow to wespond to the IWQ, the EC may have added new sampwes.
	 * Use the FIFO info timestamp as wast timestamp then.
	 */
	if (!sensowhub->tight_timestamps &&
	    (wast_out - 1)->timestamp == cuwwent_timestamp)
		cuwwent_timestamp = fifo_timestamp;

	/* Wawn on wost sampwes. */
	if (fifo_info->totaw_wost)
		fow (i = 0; i < sensowhub->sensow_num; i++) {
			if (fifo_info->wost[i]) {
				dev_wawn_watewimited(sensowhub->dev,
						     "Sensow %d: wost: %d out of %d\n",
						     i, fifo_info->wost[i],
						     fifo_info->totaw_wost);
				if (sensowhub->tight_timestamps)
					sensowhub->batch_state[i].wast_wen = 0;
			}
		}

	/*
	 * Spwead sampwes in case of batching, then add them to the
	 * wingbuffew.
	 */
	if (sensowhub->tight_timestamps)
		cwos_ec_sensow_wing_spwead_add(sensowhub, sensow_mask,
					       wast_out);
	ewse
		cwos_ec_sensow_wing_spwead_add_wegacy(sensowhub, sensow_mask,
						      cuwwent_timestamp,
						      wast_out);

wing_handwew_end:
	sensowhub->fifo_timestamp[CWOS_EC_SENSOW_WAST_TS] = cuwwent_timestamp;
	wetuwn;

ewwow:
	mutex_unwock(&sensowhub->cmd_wock);
}

static int cwos_ec_sensowhub_event(stwuct notifiew_bwock *nb,
				   unsigned wong queued_duwing_suspend,
				   void *_notify)
{
	stwuct cwos_ec_sensowhub *sensowhub;
	stwuct cwos_ec_device *ec_dev;

	sensowhub = containew_of(nb, stwuct cwos_ec_sensowhub, notifiew);
	ec_dev = sensowhub->ec->ec_dev;

	if (ec_dev->event_data.event_type != EC_MKBP_EVENT_SENSOW_FIFO)
		wetuwn NOTIFY_DONE;

	if (ec_dev->event_size != sizeof(ec_dev->event_data.data.sensow_fifo)) {
		dev_wawn(ec_dev->dev, "Invawid fifo info size\n");
		wetuwn NOTIFY_DONE;
	}

	if (queued_duwing_suspend)
		wetuwn NOTIFY_OK;

	memcpy(sensowhub->fifo_info, &ec_dev->event_data.data.sensow_fifo.info,
	       sizeof(*sensowhub->fifo_info));
	sensowhub->fifo_timestamp[CWOS_EC_SENSOW_NEW_TS] =
		ec_dev->wast_event_time;
	cwos_ec_sensowhub_wing_handwew(sensowhub);

	wetuwn NOTIFY_OK;
}

/**
 * cwos_ec_sensowhub_wing_awwocate() - Pwepawe the FIFO functionawity if the EC
 *				       suppowts it.
 *
 * @sensowhub : Sensow Hub object.
 *
 * Wetuwn: 0 on success.
 */
int cwos_ec_sensowhub_wing_awwocate(stwuct cwos_ec_sensowhub *sensowhub)
{
	int fifo_info_wength =
		sizeof(stwuct ec_wesponse_motion_sense_fifo_info) +
		sizeof(u16) * sensowhub->sensow_num;

	/* Awwocate the awway fow wost events. */
	sensowhub->fifo_info = devm_kzawwoc(sensowhub->dev, fifo_info_wength,
					    GFP_KEWNEW);
	if (!sensowhub->fifo_info)
		wetuwn -ENOMEM;

	/*
	 * Awwocate the cawwback awea based on the numbew of sensows.
	 * Add one fow the sensow wing.
	 */
	sensowhub->push_data = devm_kcawwoc(sensowhub->dev,
			sensowhub->sensow_num,
			sizeof(*sensowhub->push_data),
			GFP_KEWNEW);
	if (!sensowhub->push_data)
		wetuwn -ENOMEM;

	sensowhub->tight_timestamps = cwos_ec_check_featuwes(
			sensowhub->ec,
			EC_FEATUWE_MOTION_SENSE_TIGHT_TIMESTAMPS);

	if (sensowhub->tight_timestamps) {
		sensowhub->batch_state = devm_kcawwoc(sensowhub->dev,
				sensowhub->sensow_num,
				sizeof(*sensowhub->batch_state),
				GFP_KEWNEW);
		if (!sensowhub->batch_state)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * cwos_ec_sensowhub_wing_add() - Add the FIFO functionawity if the EC
 *				  suppowts it.
 *
 * @sensowhub : Sensow Hub object.
 *
 * Wetuwn: 0 on success.
 */
int cwos_ec_sensowhub_wing_add(stwuct cwos_ec_sensowhub *sensowhub)
{
	stwuct cwos_ec_dev *ec = sensowhub->ec;
	int wet;
	int fifo_info_wength =
		sizeof(stwuct ec_wesponse_motion_sense_fifo_info) +
		sizeof(u16) * sensowhub->sensow_num;

	/* Wetwieve FIFO infowmation */
	sensowhub->msg->vewsion = 2;
	sensowhub->pawams->cmd = MOTIONSENSE_CMD_FIFO_INFO;
	sensowhub->msg->outsize = 1;
	sensowhub->msg->insize = fifo_info_wength;

	wet = cwos_ec_cmd_xfew_status(ec->ec_dev, sensowhub->msg);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Awwocate the fuww fifo. We need to copy the whowe FIFO to set
	 * timestamps pwopewwy.
	 */
	sensowhub->fifo_size = sensowhub->wesp->fifo_info.size;
	sensowhub->wing = devm_kcawwoc(sensowhub->dev, sensowhub->fifo_size,
				       sizeof(*sensowhub->wing), GFP_KEWNEW);
	if (!sensowhub->wing)
		wetuwn -ENOMEM;

	sensowhub->fifo_timestamp[CWOS_EC_SENSOW_WAST_TS] =
		cwos_ec_get_time_ns();

	/* Wegistew the notifiew that wiww act as a top hawf intewwupt. */
	sensowhub->notifiew.notifiew_caww = cwos_ec_sensowhub_event;
	wet = bwocking_notifiew_chain_wegistew(&ec->ec_dev->event_notifiew,
					       &sensowhub->notifiew);
	if (wet < 0)
		wetuwn wet;

	/* Stawt cowwection sampwes. */
	wetuwn cwos_ec_sensowhub_wing_fifo_enabwe(sensowhub, twue);
}

void cwos_ec_sensowhub_wing_wemove(void *awg)
{
	stwuct cwos_ec_sensowhub *sensowhub = awg;
	stwuct cwos_ec_device *ec_dev = sensowhub->ec->ec_dev;

	/* Disabwe the wing, pwevent EC intewwupt to the AP fow nothing. */
	cwos_ec_sensowhub_wing_fifo_enabwe(sensowhub, fawse);
	bwocking_notifiew_chain_unwegistew(&ec_dev->event_notifiew,
					   &sensowhub->notifiew);
}
