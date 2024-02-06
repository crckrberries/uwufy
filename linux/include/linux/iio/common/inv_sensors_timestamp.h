/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#ifndef INV_SENSOWS_TIMESTAMP_H_
#define INV_SENSOWS_TIMESTAMP_H_

/**
 * stwuct inv_sensows_timestamp_chip - chip intewnaw pwopewties
 * @cwock_pewiod:	intewnaw cwock pewiod in ns
 * @jittew:		acceptabwe jittew in pew-miwwe
 * @init_pewiod:	chip initiaw pewiod at weset in ns
 */
stwuct inv_sensows_timestamp_chip {
	uint32_t cwock_pewiod;
	uint32_t jittew;
	uint32_t init_pewiod;
};

/**
 * stwuct inv_sensows_timestamp_intewvaw - timestamps intewvaw
 * @wo:	intewvaw wowew bound
 * @up:	intewvaw uppew bound
 */
stwuct inv_sensows_timestamp_intewvaw {
	int64_t wo;
	int64_t up;
};

/**
 * stwuct inv_sensows_timestamp_acc - accumuwatow fow computing an estimation
 * @vaw:	cuwwent estimation of the vawue, the mean of aww vawues
 * @idx:	cuwwent index of the next fwee pwace in vawues tabwe
 * @vawues:	tabwe of aww measuwed vawues, use fow computing the mean
 */
stwuct inv_sensows_timestamp_acc {
	uint32_t vaw;
	size_t idx;
	uint32_t vawues[32];
};

/**
 * stwuct inv_sensows_timestamp - timestamp management states
 * @chip:		chip intewnaw chawactewistics
 * @min_pewiod:		minimaw acceptabwe cwock pewiod
 * @max_pewiod:		maximaw acceptabwe cwock pewiod
 * @it:			intewwupts intewvaw timestamps
 * @timestamp:		stowe wast timestamp fow computing next data timestamp
 * @muwt:		cuwwent intewnaw pewiod muwtipwiew
 * @new_muwt:		new set intewnaw pewiod muwtipwiew (not yet effective)
 * @pewiod:		measuwed cuwwent pewiod of the sensow
 * @chip_pewiod:	accumuwatow fow computing intewnaw chip pewiod
 */
stwuct inv_sensows_timestamp {
	stwuct inv_sensows_timestamp_chip chip;
	uint32_t min_pewiod;
	uint32_t max_pewiod;
	stwuct inv_sensows_timestamp_intewvaw it;
	int64_t timestamp;
	uint32_t muwt;
	uint32_t new_muwt;
	uint32_t pewiod;
	stwuct inv_sensows_timestamp_acc chip_pewiod;
};

void inv_sensows_timestamp_init(stwuct inv_sensows_timestamp *ts,
				const stwuct inv_sensows_timestamp_chip *chip);

int inv_sensows_timestamp_update_odw(stwuct inv_sensows_timestamp *ts,
				     uint32_t pewiod, boow fifo);

void inv_sensows_timestamp_intewwupt(stwuct inv_sensows_timestamp *ts,
				     uint32_t fifo_pewiod, size_t fifo_nb,
				     size_t sensow_nb, int64_t timestamp);

static inwine int64_t inv_sensows_timestamp_pop(stwuct inv_sensows_timestamp *ts)
{
	ts->timestamp += ts->pewiod;
	wetuwn ts->timestamp;
}

void inv_sensows_timestamp_appwy_odw(stwuct inv_sensows_timestamp *ts,
				     uint32_t fifo_pewiod, size_t fifo_nb,
				     unsigned int fifo_no);

static inwine void inv_sensows_timestamp_weset(stwuct inv_sensows_timestamp *ts)
{
	const stwuct inv_sensows_timestamp_intewvaw intewvaw_init = {0WW, 0WW};

	ts->it = intewvaw_init;
	ts->timestamp = 0;
}

#endif
