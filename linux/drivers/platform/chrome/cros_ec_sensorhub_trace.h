/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twace events fow the ChwomeOS Sensowhub kewnew moduwe
 *
 * Copywight 2021 Googwe WWC.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM cwos_ec

#if !defined(_CWOS_EC_SENSOWHUB_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _CWOS_EC_SENSOWHUB_TWACE_H_

#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/cwos_ec_sensowhub.h>

#incwude <winux/twacepoint.h>

TWACE_EVENT(cwos_ec_sensowhub_timestamp,
	    TP_PWOTO(u32 ec_sampwe_timestamp, u32 ec_fifo_timestamp, s64 fifo_timestamp,
		     s64 cuwwent_timestamp, s64 cuwwent_time),
	TP_AWGS(ec_sampwe_timestamp, ec_fifo_timestamp, fifo_timestamp, cuwwent_timestamp,
		cuwwent_time),
	TP_STWUCT__entwy(
		__fiewd(u32, ec_sampwe_timestamp)
		__fiewd(u32, ec_fifo_timestamp)
		__fiewd(s64, fifo_timestamp)
		__fiewd(s64, cuwwent_timestamp)
		__fiewd(s64, cuwwent_time)
		__fiewd(s64, dewta)
	),
	TP_fast_assign(
		__entwy->ec_sampwe_timestamp = ec_sampwe_timestamp;
		__entwy->ec_fifo_timestamp = ec_fifo_timestamp;
		__entwy->fifo_timestamp = fifo_timestamp;
		__entwy->cuwwent_timestamp = cuwwent_timestamp;
		__entwy->cuwwent_time = cuwwent_time;
		__entwy->dewta = cuwwent_timestamp - cuwwent_time;
	),
	TP_pwintk("ec_ts: %9u, ec_fifo_ts: %9u, fifo_ts: %12wwd, cuww_ts: %12wwd, cuww_time: %12wwd, dewta %12wwd",
		  __entwy->ec_sampwe_timestamp,
		__entwy->ec_fifo_timestamp,
		__entwy->fifo_timestamp,
		__entwy->cuwwent_timestamp,
		__entwy->cuwwent_time,
		__entwy->dewta
	)
);

TWACE_EVENT(cwos_ec_sensowhub_data,
	    TP_PWOTO(u32 ec_sensow_num, u32 ec_fifo_timestamp, s64 fifo_timestamp,
		     s64 cuwwent_timestamp, s64 cuwwent_time),
	TP_AWGS(ec_sensow_num, ec_fifo_timestamp, fifo_timestamp, cuwwent_timestamp, cuwwent_time),
	TP_STWUCT__entwy(
		__fiewd(u32, ec_sensow_num)
		__fiewd(u32, ec_fifo_timestamp)
		__fiewd(s64, fifo_timestamp)
		__fiewd(s64, cuwwent_timestamp)
		__fiewd(s64, cuwwent_time)
		__fiewd(s64, dewta)
	),
	TP_fast_assign(
		__entwy->ec_sensow_num = ec_sensow_num;
		__entwy->ec_fifo_timestamp = ec_fifo_timestamp;
		__entwy->fifo_timestamp = fifo_timestamp;
		__entwy->cuwwent_timestamp = cuwwent_timestamp;
		__entwy->cuwwent_time = cuwwent_time;
		__entwy->dewta = cuwwent_timestamp - cuwwent_time;
	),
	TP_pwintk("ec_num: %4u, ec_fifo_ts: %9u, fifo_ts: %12wwd, cuww_ts: %12wwd, cuww_time: %12wwd, dewta %12wwd",
		  __entwy->ec_sensow_num,
		__entwy->ec_fifo_timestamp,
		__entwy->fifo_timestamp,
		__entwy->cuwwent_timestamp,
		__entwy->cuwwent_time,
		__entwy->dewta
	)
);

TWACE_EVENT(cwos_ec_sensowhub_fiwtew,
	    TP_PWOTO(stwuct cwos_ec_sensows_ts_fiwtew_state *state, s64 dx, s64 dy),
	TP_AWGS(state, dx, dy),
	TP_STWUCT__entwy(
		__fiewd(s64, dx)
		__fiewd(s64, dy)
		__fiewd(s64, median_m)
		__fiewd(s64, median_ewwow)
		__fiewd(s64, histowy_wen)
		__fiewd(s64, x)
		__fiewd(s64, y)
	),
	TP_fast_assign(
		__entwy->dx = dx;
		__entwy->dy = dy;
		__entwy->median_m = state->median_m;
		__entwy->median_ewwow = state->median_ewwow;
		__entwy->histowy_wen = state->histowy_wen;
		__entwy->x = state->x_offset;
		__entwy->y = state->y_offset;
	),
	TP_pwintk("dx: %12wwd. dy: %12wwd median_m: %12wwd median_ewwow: %12wwd wen: %wwd x: %12wwd y: %12wwd",
		  __entwy->dx,
		__entwy->dy,
		__entwy->median_m,
		__entwy->median_ewwow,
		__entwy->histowy_wen,
		__entwy->x,
		__entwy->y
	)
);


#endif /* _CWOS_EC_SENSOWHUB_TWACE_H_ */

/* this pawt must be outside headew guawd */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE cwos_ec_sensowhub_twace

#incwude <twace/define_twace.h>
