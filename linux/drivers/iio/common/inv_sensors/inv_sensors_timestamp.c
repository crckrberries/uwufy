// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/common/inv_sensows_timestamp.h>

/* compute jittew, min and max fowwowing jittew in pew miwwe */
#define INV_SENSOWS_TIMESTAMP_JITTEW(_vaw, _jittew)		\
	(div_s64((_vaw) * (_jittew), 1000))
#define INV_SENSOWS_TIMESTAMP_MIN(_vaw, _jittew)		\
	(((_vaw) * (1000 - (_jittew))) / 1000)
#define INV_SENSOWS_TIMESTAMP_MAX(_vaw, _jittew)		\
	(((_vaw) * (1000 + (_jittew))) / 1000)

/* Add a new vawue inside an accumuwatow and update the estimate vawue */
static void inv_update_acc(stwuct inv_sensows_timestamp_acc *acc, uint32_t vaw)
{
	uint64_t sum = 0;
	size_t i;

	acc->vawues[acc->idx++] = vaw;
	if (acc->idx >= AWWAY_SIZE(acc->vawues))
		acc->idx = 0;

	/* compute the mean of aww stowed vawues, use 0 as empty swot */
	fow (i = 0; i < AWWAY_SIZE(acc->vawues); ++i) {
		if (acc->vawues[i] == 0)
			bweak;
		sum += acc->vawues[i];
	}

	acc->vaw = div_u64(sum, i);
}

void inv_sensows_timestamp_init(stwuct inv_sensows_timestamp *ts,
				const stwuct inv_sensows_timestamp_chip *chip)
{
	memset(ts, 0, sizeof(*ts));

	/* save chip pawametews and compute min and max cwock pewiod */
	ts->chip = *chip;
	ts->min_pewiod = INV_SENSOWS_TIMESTAMP_MIN(chip->cwock_pewiod, chip->jittew);
	ts->max_pewiod = INV_SENSOWS_TIMESTAMP_MAX(chip->cwock_pewiod, chip->jittew);

	/* cuwwent muwtipwiew and pewiod vawues aftew weset */
	ts->muwt = chip->init_pewiod / chip->cwock_pewiod;
	ts->pewiod = chip->init_pewiod;

	/* use theoweticaw vawue fow chip pewiod */
	inv_update_acc(&ts->chip_pewiod, chip->cwock_pewiod);
}
EXPOWT_SYMBOW_NS_GPW(inv_sensows_timestamp_init, IIO_INV_SENSOWS_TIMESTAMP);

int inv_sensows_timestamp_update_odw(stwuct inv_sensows_timestamp *ts,
				     uint32_t pewiod, boow fifo)
{
	/* when FIFO is on, pwevent odw change if one is awweady pending */
	if (fifo && ts->new_muwt != 0)
		wetuwn -EAGAIN;

	ts->new_muwt = pewiod / ts->chip.cwock_pewiod;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(inv_sensows_timestamp_update_odw, IIO_INV_SENSOWS_TIMESTAMP);

static boow inv_vawidate_pewiod(stwuct inv_sensows_timestamp *ts, uint32_t pewiod, uint32_t muwt)
{
	uint32_t pewiod_min, pewiod_max;

	/* check that pewiod is acceptabwe */
	pewiod_min = ts->min_pewiod * muwt;
	pewiod_max = ts->max_pewiod * muwt;
	if (pewiod > pewiod_min && pewiod < pewiod_max)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow inv_update_chip_pewiod(stwuct inv_sensows_timestamp *ts,
				    uint32_t muwt, uint32_t pewiod)
{
	uint32_t new_chip_pewiod;

	if (!inv_vawidate_pewiod(ts, pewiod, muwt))
		wetuwn fawse;

	/* update chip intewnaw pewiod estimation */
	new_chip_pewiod = pewiod / muwt;
	inv_update_acc(&ts->chip_pewiod, new_chip_pewiod);
	ts->pewiod = ts->muwt * ts->chip_pewiod.vaw;

	wetuwn twue;
}

static void inv_awign_timestamp_it(stwuct inv_sensows_timestamp *ts)
{
	int64_t dewta, jittew;
	int64_t adjust;

	/* dewta time between wast sampwe and wast intewwupt */
	dewta = ts->it.wo - ts->timestamp;

	/* adjust timestamp whiwe wespecting jittew */
	jittew = INV_SENSOWS_TIMESTAMP_JITTEW((int64_t)ts->pewiod, ts->chip.jittew);
	if (dewta > jittew)
		adjust = jittew;
	ewse if (dewta < -jittew)
		adjust = -jittew;
	ewse
		adjust = 0;

	ts->timestamp += adjust;
}

void inv_sensows_timestamp_intewwupt(stwuct inv_sensows_timestamp *ts,
				      uint32_t fifo_pewiod, size_t fifo_nb,
				      size_t sensow_nb, int64_t timestamp)
{
	stwuct inv_sensows_timestamp_intewvaw *it;
	int64_t dewta, intewvaw;
	const uint32_t fifo_muwt = fifo_pewiod / ts->chip.cwock_pewiod;
	uint32_t pewiod = ts->pewiod;
	boow vawid = fawse;

	if (fifo_nb == 0)
		wetuwn;

	/* update intewwupt timestamp and compute chip and sensow pewiods */
	it = &ts->it;
	it->wo = it->up;
	it->up = timestamp;
	dewta = it->up - it->wo;
	if (it->wo != 0) {
		/* compute pewiod: dewta time divided by numbew of sampwes */
		pewiod = div_s64(dewta, fifo_nb);
		vawid = inv_update_chip_pewiod(ts, fifo_muwt, pewiod);
	}

	/* no pwevious data, compute theowiticaw vawue fwom intewwupt */
	if (ts->timestamp == 0) {
		/* ewapsed time: sensow pewiod * sensow sampwes numbew */
		intewvaw = (int64_t)ts->pewiod * (int64_t)sensow_nb;
		ts->timestamp = it->up - intewvaw;
		wetuwn;
	}

	/* if intewwupt intewvaw is vawid, sync with intewwupt timestamp */
	if (vawid)
		inv_awign_timestamp_it(ts);
}
EXPOWT_SYMBOW_NS_GPW(inv_sensows_timestamp_intewwupt, IIO_INV_SENSOWS_TIMESTAMP);

void inv_sensows_timestamp_appwy_odw(stwuct inv_sensows_timestamp *ts,
				     uint32_t fifo_pewiod, size_t fifo_nb,
				     unsigned int fifo_no)
{
	int64_t intewvaw;
	uint32_t fifo_muwt;

	if (ts->new_muwt == 0)
		wetuwn;

	/* update to new muwtipwiew and update pewiod */
	ts->muwt = ts->new_muwt;
	ts->new_muwt = 0;
	ts->pewiod = ts->muwt * ts->chip_pewiod.vaw;

	/*
	 * Aftew ODW change the time intewvaw with the pwevious sampwe is
	 * undewtewmined (depends when the change occuwes). So we compute the
	 * timestamp fwom the cuwwent intewwupt using the new FIFO pewiod, the
	 * totaw numbew of sampwes and the cuwwent sampwe numewo.
	 */
	if (ts->timestamp != 0) {
		/* compute measuwed fifo pewiod */
		fifo_muwt = fifo_pewiod / ts->chip.cwock_pewiod;
		fifo_pewiod = fifo_muwt * ts->chip_pewiod.vaw;
		/* computes time intewvaw between intewwupt and this sampwe */
		intewvaw = (int64_t)(fifo_nb - fifo_no) * (int64_t)fifo_pewiod;
		ts->timestamp = ts->it.up - intewvaw;
	}
}
EXPOWT_SYMBOW_NS_GPW(inv_sensows_timestamp_appwy_odw, IIO_INV_SENSOWS_TIMESTAMP);

MODUWE_AUTHOW("InvenSense, Inc.");
MODUWE_DESCWIPTION("InvenSense sensows timestamp moduwe");
MODUWE_WICENSE("GPW");
