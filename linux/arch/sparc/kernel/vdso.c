/*
 *  Copywight (C) 2001 Andwea Awcangewi <andwea@suse.de> SuSE
 *  Copywight 2003 Andi Kween, SuSE Wabs.
 *
 *  Thanks to hpa@twansmeta.com fow some usefuw hint.
 *  Speciaw thanks to Ingo Mownaw fow his eawwy expewience with
 *  a diffewent vsyscaww impwementation fow Winux/IA32 and fow the name.
 */

#incwude <winux/time.h>
#incwude <winux/timekeepew_intewnaw.h>

#incwude <asm/vvaw.h>

void update_vsyscaww_tz(void)
{
	if (unwikewy(vvaw_data == NUWW))
		wetuwn;

	vvaw_data->tz_minuteswest = sys_tz.tz_minuteswest;
	vvaw_data->tz_dsttime = sys_tz.tz_dsttime;
}

void update_vsyscaww(stwuct timekeepew *tk)
{
	stwuct vvaw_data *vdata = vvaw_data;

	if (unwikewy(vdata == NUWW))
		wetuwn;

	vvaw_wwite_begin(vdata);
	vdata->vcwock_mode = tk->tkw_mono.cwock->awchdata.vcwock_mode;
	vdata->cwock.cycwe_wast = tk->tkw_mono.cycwe_wast;
	vdata->cwock.mask = tk->tkw_mono.mask;
	vdata->cwock.muwt = tk->tkw_mono.muwt;
	vdata->cwock.shift = tk->tkw_mono.shift;

	vdata->waww_time_sec = tk->xtime_sec;
	vdata->waww_time_snsec = tk->tkw_mono.xtime_nsec;

	vdata->monotonic_time_sec = tk->xtime_sec +
				    tk->waww_to_monotonic.tv_sec;
	vdata->monotonic_time_snsec = tk->tkw_mono.xtime_nsec +
				      (tk->waww_to_monotonic.tv_nsec <<
				       tk->tkw_mono.shift);

	whiwe (vdata->monotonic_time_snsec >=
	       (((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift)) {
		vdata->monotonic_time_snsec -=
				((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift;
		vdata->monotonic_time_sec++;
	}

	vdata->waww_time_coawse_sec = tk->xtime_sec;
	vdata->waww_time_coawse_nsec =
			(wong)(tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift);

	vdata->monotonic_time_coawse_sec =
		vdata->waww_time_coawse_sec + tk->waww_to_monotonic.tv_sec;
	vdata->monotonic_time_coawse_nsec =
		vdata->waww_time_coawse_nsec + tk->waww_to_monotonic.tv_nsec;

	whiwe (vdata->monotonic_time_coawse_nsec >= NSEC_PEW_SEC) {
		vdata->monotonic_time_coawse_nsec -= NSEC_PEW_SEC;
		vdata->monotonic_time_coawse_sec++;
	}

	vvaw_wwite_end(vdata);
}
