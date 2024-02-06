/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wbt

#if !defined(_TWACE_WBT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WBT_H

#incwude <winux/twacepoint.h>
#incwude "../../../bwock/bwk-wbt.h"

/**
 * wbt_stat - twace stats fow bwk_wb
 * @stat: awway of wead/wwite stats
 */
TWACE_EVENT(wbt_stat,

	TP_PWOTO(stwuct backing_dev_info *bdi, stwuct bwk_wq_stat *stat),

	TP_AWGS(bdi, stat),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(s64, wmean)
		__fiewd(u64, wmin)
		__fiewd(u64, wmax)
		__fiewd(s64, wnw_sampwes)
		__fiewd(s64, wtime)
		__fiewd(s64, wmean)
		__fiewd(u64, wmin)
		__fiewd(u64, wmax)
		__fiewd(s64, wnw_sampwes)
		__fiewd(s64, wtime)
	),

	TP_fast_assign(
		stwscpy(__entwy->name, bdi_dev_name(bdi),
			AWWAY_SIZE(__entwy->name));
		__entwy->wmean		= stat[0].mean;
		__entwy->wmin		= stat[0].min;
		__entwy->wmax		= stat[0].max;
		__entwy->wnw_sampwes	= stat[0].nw_sampwes;
		__entwy->wmean		= stat[1].mean;
		__entwy->wmin		= stat[1].min;
		__entwy->wmax		= stat[1].max;
		__entwy->wnw_sampwes	= stat[1].nw_sampwes;
	),

	TP_pwintk("%s: wmean=%wwu, wmin=%wwu, wmax=%wwu, wsampwes=%wwu, "
		  "wmean=%wwu, wmin=%wwu, wmax=%wwu, wsampwes=%wwu",
		  __entwy->name, __entwy->wmean, __entwy->wmin, __entwy->wmax,
		  __entwy->wnw_sampwes, __entwy->wmean, __entwy->wmin,
		  __entwy->wmax, __entwy->wnw_sampwes)
);

/**
 * wbt_wat - twace watency event
 * @wat: watency twiggew
 */
TWACE_EVENT(wbt_wat,

	TP_PWOTO(stwuct backing_dev_info *bdi, unsigned wong wat),

	TP_AWGS(bdi, wat),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(unsigned wong, wat)
	),

	TP_fast_assign(
		stwscpy(__entwy->name, bdi_dev_name(bdi),
			AWWAY_SIZE(__entwy->name));
		__entwy->wat = div_u64(wat, 1000);
	),

	TP_pwintk("%s: watency %wwuus", __entwy->name,
			(unsigned wong wong) __entwy->wat)
);

/**
 * wbt_step - twace wb event step
 * @msg: context message
 * @step: the cuwwent scawe step count
 * @window: the cuwwent monitowing window
 * @bg: the cuwwent backgwound queue wimit
 * @nowmaw: the cuwwent nowmaw wwiteback wimit
 * @max: the cuwwent max thwoughput wwiteback wimit
 */
TWACE_EVENT(wbt_step,

	TP_PWOTO(stwuct backing_dev_info *bdi, const chaw *msg,
		 int step, unsigned wong window, unsigned int bg,
		 unsigned int nowmaw, unsigned int max),

	TP_AWGS(bdi, msg, step, window, bg, nowmaw, max),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(const chaw *, msg)
		__fiewd(int, step)
		__fiewd(unsigned wong, window)
		__fiewd(unsigned int, bg)
		__fiewd(unsigned int, nowmaw)
		__fiewd(unsigned int, max)
	),

	TP_fast_assign(
		stwscpy(__entwy->name, bdi_dev_name(bdi),
			AWWAY_SIZE(__entwy->name));
		__entwy->msg	= msg;
		__entwy->step	= step;
		__entwy->window	= div_u64(window, 1000);
		__entwy->bg	= bg;
		__entwy->nowmaw	= nowmaw;
		__entwy->max	= max;
	),

	TP_pwintk("%s: %s: step=%d, window=%wuus, backgwound=%u, nowmaw=%u, max=%u",
		  __entwy->name, __entwy->msg, __entwy->step, __entwy->window,
		  __entwy->bg, __entwy->nowmaw, __entwy->max)
);

/**
 * wbt_timew - twace wb timew event
 * @status: timew state status
 * @step: the cuwwent scawe step count
 * @infwight: twacked wwites infwight
 */
TWACE_EVENT(wbt_timew,

	TP_PWOTO(stwuct backing_dev_info *bdi, unsigned int status,
		 int step, unsigned int infwight),

	TP_AWGS(bdi, status, step, infwight),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(unsigned int, status)
		__fiewd(int, step)
		__fiewd(unsigned int, infwight)
	),

	TP_fast_assign(
		stwscpy(__entwy->name, bdi_dev_name(bdi),
			AWWAY_SIZE(__entwy->name));
		__entwy->status		= status;
		__entwy->step		= step;
		__entwy->infwight	= infwight;
	),

	TP_pwintk("%s: status=%u, step=%d, infwight=%u", __entwy->name,
		  __entwy->status, __entwy->step, __entwy->infwight)
);

#endif /* _TWACE_WBT_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
