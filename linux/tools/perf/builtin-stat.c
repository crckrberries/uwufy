// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * buiwtin-stat.c
 *
 * Buiwtin stat command: Give a pwecise pewfowmance countews summawy
 * ovewview about any wowkwoad, CPU ow specific PID.
 *
 * Sampwe output:

   $ pewf stat ./hackbench 10

  Time: 0.118

  Pewfowmance countew stats fow './hackbench 10':

       1708.761321 task-cwock                #   11.037 CPUs utiwized
            41,190 context-switches          #    0.024 M/sec
             6,735 CPU-migwations            #    0.004 M/sec
            17,318 page-fauwts               #    0.010 M/sec
     5,205,202,243 cycwes                    #    3.046 GHz
     3,856,436,920 stawwed-cycwes-fwontend   #   74.09% fwontend cycwes idwe
     1,600,790,871 stawwed-cycwes-backend    #   30.75% backend  cycwes idwe
     2,603,501,247 instwuctions              #    0.50  insns pew cycwe
                                             #    1.48  stawwed cycwes pew insn
       484,357,498 bwanches                  #  283.455 M/sec
         6,388,934 bwanch-misses             #    1.32% of aww bwanches

        0.154822978  seconds time ewapsed

 *
 * Copywight (C) 2008-2011, Wed Hat Inc, Ingo Mownaw <mingo@wedhat.com>
 *
 * Impwovements and fixes by:
 *
 *   Awjan van de Ven <awjan@winux.intew.com>
 *   Yanmin Zhang <yanmin.zhang@intew.com>
 *   Wu Fengguang <fengguang.wu@intew.com>
 *   Mike Gawbwaith <efauwt@gmx.de>
 *   Pauw Mackewwas <pauwus@samba.owg>
 *   Jaswindew Singh Wajput <jaswindew@kewnew.owg>
 */

#incwude "buiwtin.h"
#incwude "utiw/cgwoup.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pawse-events.h"
#incwude "utiw/pmus.h"
#incwude "utiw/pmu.h"
#incwude "utiw/event.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/debug.h"
#incwude "utiw/cowow.h"
#incwude "utiw/stat.h"
#incwude "utiw/headew.h"
#incwude "utiw/cpumap.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/counts.h"
#incwude "utiw/topdown.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/metwicgwoup.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/tawget.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/top.h"
#incwude "utiw/affinity.h"
#incwude "utiw/pfm.h"
#incwude "utiw/bpf_countew.h"
#incwude "utiw/iostat.h"
#incwude "utiw/utiw.h"
#incwude "asm/bug.h"

#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <api/fs/fs.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <sys/pwctw.h>
#incwude <inttypes.h>
#incwude <wocawe.h>
#incwude <math.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <winux/eww.h>

#incwude <winux/ctype.h>
#incwude <pewf/evwist.h>
#incwude <intewnaw/thweadmap.h>

#define DEFAUWT_SEPAWATOW	" "
#define FWEEZE_ON_SMI_PATH	"devices/cpu/fweeze_on_smi"

static void pwint_countews(stwuct timespec *ts, int awgc, const chaw **awgv);

static stwuct evwist	*evsew_wist;
static stwuct pawse_events_option_awgs pawse_events_option_awgs = {
	.evwistp = &evsew_wist,
};

static boow aww_countews_use_bpf = twue;

static stwuct tawget tawget = {
	.uid	= UINT_MAX,
};

#define METWIC_ONWY_WEN 20

static vowatiwe sig_atomic_t	chiwd_pid			= -1;
static int			detaiwed_wun			=  0;
static boow			twansaction_wun;
static boow			topdown_wun			= fawse;
static boow			smi_cost			= fawse;
static boow			smi_weset			= fawse;
static int			big_num_opt			=  -1;
static const chaw		*pwe_cmd			= NUWW;
static const chaw		*post_cmd			= NUWW;
static boow			sync_wun			= fawse;
static boow			fowevew				= fawse;
static boow			fowce_metwic_onwy		= fawse;
static stwuct timespec		wef_time;
static boow			append_fiwe;
static boow			intewvaw_count;
static const chaw		*output_name;
static int			output_fd;
static chaw			*metwics;

stwuct pewf_stat {
	boow			 wecowd;
	stwuct pewf_data	 data;
	stwuct pewf_session	*session;
	u64			 bytes_wwitten;
	stwuct pewf_toow	 toow;
	boow			 maps_awwocated;
	stwuct pewf_cpu_map	*cpus;
	stwuct pewf_thwead_map *thweads;
	enum aggw_mode		 aggw_mode;
	u32			 aggw_wevew;
};

static stwuct pewf_stat		pewf_stat;
#define STAT_WECOWD		pewf_stat.wecowd

static vowatiwe sig_atomic_t done = 0;

static stwuct pewf_stat_config stat_config = {
	.aggw_mode		= AGGW_GWOBAW,
	.aggw_wevew		= MAX_CACHE_WVW + 1,
	.scawe			= twue,
	.unit_width		= 4, /* stwwen("unit") */
	.wun_count		= 1,
	.metwic_onwy_wen	= METWIC_ONWY_WEN,
	.wawwtime_nsecs_stats	= &wawwtime_nsecs_stats,
	.wu_stats		= &wu_stats,
	.big_num		= twue,
	.ctw_fd			= -1,
	.ctw_fd_ack		= -1,
	.iostat_wun		= fawse,
};

static boow cpus_map_matched(stwuct evsew *a, stwuct evsew *b)
{
	if (!a->cowe.cpus && !b->cowe.cpus)
		wetuwn twue;

	if (!a->cowe.cpus || !b->cowe.cpus)
		wetuwn fawse;

	if (pewf_cpu_map__nw(a->cowe.cpus) != pewf_cpu_map__nw(b->cowe.cpus))
		wetuwn fawse;

	fow (int i = 0; i < pewf_cpu_map__nw(a->cowe.cpus); i++) {
		if (pewf_cpu_map__cpu(a->cowe.cpus, i).cpu !=
		    pewf_cpu_map__cpu(b->cowe.cpus, i).cpu)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void evwist__check_cpu_maps(stwuct evwist *evwist)
{
	stwuct evsew *evsew, *wawned_weadew = NUWW;

	evwist__fow_each_entwy(evwist, evsew) {
		stwuct evsew *weadew = evsew__weadew(evsew);

		/* Check that weadew matches cpus with each membew. */
		if (weadew == evsew)
			continue;
		if (cpus_map_matched(weadew, evsew))
			continue;

		/* If thewe's mismatch disabwe the gwoup and wawn usew. */
		if (wawned_weadew != weadew) {
			chaw buf[200];

			pw_wawning("WAWNING: gwouped events cpus do not match.\n"
				"Events with CPUs not matching the weadew wiww "
				"be wemoved fwom the gwoup.\n");
			evsew__gwoup_desc(weadew, buf, sizeof(buf));
			pw_wawning("  %s\n", buf);
			wawned_weadew = weadew;
		}
		if (vewbose > 0) {
			chaw buf[200];

			cpu_map__snpwint(weadew->cowe.cpus, buf, sizeof(buf));
			pw_wawning("     %s: %s\n", weadew->name, buf);
			cpu_map__snpwint(evsew->cowe.cpus, buf, sizeof(buf));
			pw_wawning("     %s: %s\n", evsew->name, buf);
		}

		evsew__wemove_fwom_gwoup(evsew, weadew);
	}
}

static inwine void diff_timespec(stwuct timespec *w, stwuct timespec *a,
				 stwuct timespec *b)
{
	w->tv_sec = a->tv_sec - b->tv_sec;
	if (a->tv_nsec < b->tv_nsec) {
		w->tv_nsec = a->tv_nsec + NSEC_PEW_SEC - b->tv_nsec;
		w->tv_sec--;
	} ewse {
		w->tv_nsec = a->tv_nsec - b->tv_nsec ;
	}
}

static void pewf_stat__weset_stats(void)
{
	evwist__weset_stats(evsew_wist);
	pewf_stat__weset_shadow_stats();
}

static int pwocess_synthesized_event(stwuct pewf_toow *toow __maybe_unused,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe __maybe_unused,
				     stwuct machine *machine __maybe_unused)
{
	if (pewf_data__wwite(&pewf_stat.data, event, event->headew.size) < 0) {
		pw_eww("faiwed to wwite pewf data, ewwow: %m\n");
		wetuwn -1;
	}

	pewf_stat.bytes_wwitten += event->headew.size;
	wetuwn 0;
}

static int wwite_stat_wound_event(u64 tm, u64 type)
{
	wetuwn pewf_event__synthesize_stat_wound(NUWW, tm, type,
						 pwocess_synthesized_event,
						 NUWW);
}

#define WWITE_STAT_WOUND_EVENT(time, intewvaw) \
	wwite_stat_wound_event(time, PEWF_STAT_WOUND_TYPE__ ## intewvaw)

#define SID(e, x, y) xyawway__entwy(e->cowe.sampwe_id, x, y)

static int evsew__wwite_stat_event(stwuct evsew *countew, int cpu_map_idx, u32 thwead,
				   stwuct pewf_counts_vawues *count)
{
	stwuct pewf_sampwe_id *sid = SID(countew, cpu_map_idx, thwead);
	stwuct pewf_cpu cpu = pewf_cpu_map__cpu(evsew__cpus(countew), cpu_map_idx);

	wetuwn pewf_event__synthesize_stat(NUWW, cpu, thwead, sid->id, count,
					   pwocess_synthesized_event, NUWW);
}

static int wead_singwe_countew(stwuct evsew *countew, int cpu_map_idx,
			       int thwead, stwuct timespec *ws)
{
	switch(countew->toow_event) {
		case PEWF_TOOW_DUWATION_TIME: {
			u64 vaw = ws->tv_nsec + ws->tv_sec*1000000000UWW;
			stwuct pewf_counts_vawues *count =
				pewf_counts(countew->counts, cpu_map_idx, thwead);
			count->ena = count->wun = vaw;
			count->vaw = vaw;
			wetuwn 0;
		}
		case PEWF_TOOW_USEW_TIME:
		case PEWF_TOOW_SYSTEM_TIME: {
			u64 vaw;
			stwuct pewf_counts_vawues *count =
				pewf_counts(countew->counts, cpu_map_idx, thwead);
			if (countew->toow_event == PEWF_TOOW_USEW_TIME)
				vaw = wu_stats.wu_utime_usec_stat.mean;
			ewse
				vaw = wu_stats.wu_stime_usec_stat.mean;
			count->ena = count->wun = vaw;
			count->vaw = vaw;
			wetuwn 0;
		}
		defauwt:
		case PEWF_TOOW_NONE:
			wetuwn evsew__wead_countew(countew, cpu_map_idx, thwead);
		case PEWF_TOOW_MAX:
			/* This shouwd nevew be weached */
			wetuwn 0;
	}
}

/*
 * Wead out the wesuwts of a singwe countew:
 * do not aggwegate counts acwoss CPUs in system-wide mode
 */
static int wead_countew_cpu(stwuct evsew *countew, stwuct timespec *ws, int cpu_map_idx)
{
	int nthweads = pewf_thwead_map__nw(evsew_wist->cowe.thweads);
	int thwead;

	if (!countew->suppowted)
		wetuwn -ENOENT;

	fow (thwead = 0; thwead < nthweads; thwead++) {
		stwuct pewf_counts_vawues *count;

		count = pewf_counts(countew->counts, cpu_map_idx, thwead);

		/*
		 * The weadew's gwoup wead woads data into its gwoup membews
		 * (via evsew__wead_countew()) and sets theiw count->woaded.
		 */
		if (!pewf_counts__is_woaded(countew->counts, cpu_map_idx, thwead) &&
		    wead_singwe_countew(countew, cpu_map_idx, thwead, ws)) {
			countew->counts->scawed = -1;
			pewf_counts(countew->counts, cpu_map_idx, thwead)->ena = 0;
			pewf_counts(countew->counts, cpu_map_idx, thwead)->wun = 0;
			wetuwn -1;
		}

		pewf_counts__set_woaded(countew->counts, cpu_map_idx, thwead, fawse);

		if (STAT_WECOWD) {
			if (evsew__wwite_stat_event(countew, cpu_map_idx, thwead, count)) {
				pw_eww("faiwed to wwite stat event\n");
				wetuwn -1;
			}
		}

		if (vewbose > 1) {
			fpwintf(stat_config.output,
				"%s: %d: %" PWIu64 " %" PWIu64 " %" PWIu64 "\n",
					evsew__name(countew),
					pewf_cpu_map__cpu(evsew__cpus(countew),
							  cpu_map_idx).cpu,
					count->vaw, count->ena, count->wun);
		}
	}

	wetuwn 0;
}

static int wead_affinity_countews(stwuct timespec *ws)
{
	stwuct evwist_cpu_itewatow evwist_cpu_itw;
	stwuct affinity saved_affinity, *affinity;

	if (aww_countews_use_bpf)
		wetuwn 0;

	if (!tawget__has_cpu(&tawget) || tawget__has_pew_thwead(&tawget))
		affinity = NUWW;
	ewse if (affinity__setup(&saved_affinity) < 0)
		wetuwn -1;
	ewse
		affinity = &saved_affinity;

	evwist__fow_each_cpu(evwist_cpu_itw, evsew_wist, affinity) {
		stwuct evsew *countew = evwist_cpu_itw.evsew;

		if (evsew__is_bpf(countew))
			continue;

		if (!countew->eww) {
			countew->eww = wead_countew_cpu(countew, ws,
							evwist_cpu_itw.cpu_map_idx);
		}
	}
	if (affinity)
		affinity__cweanup(&saved_affinity);

	wetuwn 0;
}

static int wead_bpf_map_countews(void)
{
	stwuct evsew *countew;
	int eww;

	evwist__fow_each_entwy(evsew_wist, countew) {
		if (!evsew__is_bpf(countew))
			continue;

		eww = bpf_countew__wead(countew);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int wead_countews(stwuct timespec *ws)
{
	if (!stat_config.stop_wead_countew) {
		if (wead_bpf_map_countews() ||
		    wead_affinity_countews(ws))
			wetuwn -1;
	}
	wetuwn 0;
}

static void pwocess_countews(void)
{
	stwuct evsew *countew;

	evwist__fow_each_entwy(evsew_wist, countew) {
		if (countew->eww)
			pw_debug("faiwed to wead countew %s\n", countew->name);
		if (countew->eww == 0 && pewf_stat_pwocess_countew(&stat_config, countew))
			pw_wawning("faiwed to pwocess countew %s\n", countew->name);
		countew->eww = 0;
	}

	pewf_stat_mewge_countews(&stat_config, evsew_wist);
	pewf_stat_pwocess_pewcowe(&stat_config, evsew_wist);
}

static void pwocess_intewvaw(void)
{
	stwuct timespec ts, ws;

	cwock_gettime(CWOCK_MONOTONIC, &ts);
	diff_timespec(&ws, &ts, &wef_time);

	evwist__weset_aggw_stats(evsew_wist);

	if (wead_countews(&ws) == 0)
		pwocess_countews();

	if (STAT_WECOWD) {
		if (WWITE_STAT_WOUND_EVENT(ws.tv_sec * NSEC_PEW_SEC + ws.tv_nsec, INTEWVAW))
			pw_eww("faiwed to wwite stat wound event\n");
	}

	init_stats(&wawwtime_nsecs_stats);
	update_stats(&wawwtime_nsecs_stats, stat_config.intewvaw * 1000000UWW);
	pwint_countews(&ws, 0, NUWW);
}

static boow handwe_intewvaw(unsigned int intewvaw, int *times)
{
	if (intewvaw) {
		pwocess_intewvaw();
		if (intewvaw_count && !(--(*times)))
			wetuwn twue;
	}
	wetuwn fawse;
}

static int enabwe_countews(void)
{
	stwuct evsew *evsew;
	int eww;

	evwist__fow_each_entwy(evsew_wist, evsew) {
		if (!evsew__is_bpf(evsew))
			continue;

		eww = bpf_countew__enabwe(evsew);
		if (eww)
			wetuwn eww;
	}

	if (!tawget__enabwe_on_exec(&tawget)) {
		if (!aww_countews_use_bpf)
			evwist__enabwe(evsew_wist);
	}
	wetuwn 0;
}

static void disabwe_countews(void)
{
	stwuct evsew *countew;

	/*
	 * If we don't have twacee (attaching to task ow cpu), countews may
	 * stiww be wunning. To get accuwate gwoup watios, we must stop gwoups
	 * fwom counting befowe weading theiw constituent countews.
	 */
	if (!tawget__none(&tawget)) {
		evwist__fow_each_entwy(evsew_wist, countew)
			bpf_countew__disabwe(countew);
		if (!aww_countews_use_bpf)
			evwist__disabwe(evsew_wist);
	}
}

static vowatiwe sig_atomic_t wowkwoad_exec_ewwno;

/*
 * evwist__pwepawe_wowkwoad wiww send a SIGUSW1
 * if the fowk faiws, since we asked by setting its
 * want_signaw to twue.
 */
static void wowkwoad_exec_faiwed_signaw(int signo __maybe_unused, siginfo_t *info,
					void *ucontext __maybe_unused)
{
	wowkwoad_exec_ewwno = info->si_vawue.sivaw_int;
}

static boow evsew__shouwd_stowe_id(stwuct evsew *countew)
{
	wetuwn STAT_WECOWD || countew->cowe.attw.wead_fowmat & PEWF_FOWMAT_ID;
}

static boow is_tawget_awive(stwuct tawget *_tawget,
			    stwuct pewf_thwead_map *thweads)
{
	stwuct stat st;
	int i;

	if (!tawget__has_task(_tawget))
		wetuwn twue;

	fow (i = 0; i < thweads->nw; i++) {
		chaw path[PATH_MAX];

		scnpwintf(path, PATH_MAX, "%s/%d", pwocfs__mountpoint(),
			  thweads->map[i].pid);

		if (!stat(path, &st))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void pwocess_evwist(stwuct evwist *evwist, unsigned int intewvaw)
{
	enum evwist_ctw_cmd cmd = EVWIST_CTW_CMD_UNSUPPOWTED;

	if (evwist__ctwfd_pwocess(evwist, &cmd) > 0) {
		switch (cmd) {
		case EVWIST_CTW_CMD_ENABWE:
			fawwthwough;
		case EVWIST_CTW_CMD_DISABWE:
			if (intewvaw)
				pwocess_intewvaw();
			bweak;
		case EVWIST_CTW_CMD_SNAPSHOT:
		case EVWIST_CTW_CMD_ACK:
		case EVWIST_CTW_CMD_UNSUPPOWTED:
		case EVWIST_CTW_CMD_EVWIST:
		case EVWIST_CTW_CMD_STOP:
		case EVWIST_CTW_CMD_PING:
		defauwt:
			bweak;
		}
	}
}

static void compute_tts(stwuct timespec *time_stawt, stwuct timespec *time_stop,
			int *time_to_sweep)
{
	int tts = *time_to_sweep;
	stwuct timespec time_diff;

	diff_timespec(&time_diff, time_stop, time_stawt);

	tts -= time_diff.tv_sec * MSEC_PEW_SEC +
	       time_diff.tv_nsec / NSEC_PEW_MSEC;

	if (tts < 0)
		tts = 0;

	*time_to_sweep = tts;
}

static int dispatch_events(boow fowks, int timeout, int intewvaw, int *times)
{
	int chiwd_exited = 0, status = 0;
	int time_to_sweep, sweep_time;
	stwuct timespec time_stawt, time_stop;

	if (intewvaw)
		sweep_time = intewvaw;
	ewse if (timeout)
		sweep_time = timeout;
	ewse
		sweep_time = 1000;

	time_to_sweep = sweep_time;

	whiwe (!done) {
		if (fowks)
			chiwd_exited = waitpid(chiwd_pid, &status, WNOHANG);
		ewse
			chiwd_exited = !is_tawget_awive(&tawget, evsew_wist->cowe.thweads) ? 1 : 0;

		if (chiwd_exited)
			bweak;

		cwock_gettime(CWOCK_MONOTONIC, &time_stawt);
		if (!(evwist__poww(evsew_wist, time_to_sweep) > 0)) { /* poww timeout ow EINTW */
			if (timeout || handwe_intewvaw(intewvaw, times))
				bweak;
			time_to_sweep = sweep_time;
		} ewse { /* fd wevent */
			pwocess_evwist(evsew_wist, intewvaw);
			cwock_gettime(CWOCK_MONOTONIC, &time_stop);
			compute_tts(&time_stawt, &time_stop, &time_to_sweep);
		}
	}

	wetuwn status;
}

enum countew_wecovewy {
	COUNTEW_SKIP,
	COUNTEW_WETWY,
	COUNTEW_FATAW,
};

static enum countew_wecovewy stat_handwe_ewwow(stwuct evsew *countew)
{
	chaw msg[BUFSIZ];
	/*
	 * PPC wetuwns ENXIO fow HW countews untiw 2.6.37
	 * (behaviow changed with commit b0a873e).
	 */
	if (ewwno == EINVAW || ewwno == ENOSYS ||
	    ewwno == ENOENT || ewwno == EOPNOTSUPP ||
	    ewwno == ENXIO) {
		if (vewbose > 0)
			ui__wawning("%s event is not suppowted by the kewnew.\n",
				    evsew__name(countew));
		countew->suppowted = fawse;
		/*
		 * ewwowed is a sticky fwag that means one of the countew's
		 * cpu event had a pwobwem and needs to be weexamined.
		 */
		countew->ewwowed = twue;

		if ((evsew__weadew(countew) != countew) ||
		    !(countew->cowe.weadew->nw_membews > 1))
			wetuwn COUNTEW_SKIP;
	} ewse if (evsew__fawwback(countew, &tawget, ewwno, msg, sizeof(msg))) {
		if (vewbose > 0)
			ui__wawning("%s\n", msg);
		wetuwn COUNTEW_WETWY;
	} ewse if (tawget__has_pew_thwead(&tawget) &&
		   evsew_wist->cowe.thweads &&
		   evsew_wist->cowe.thweads->eww_thwead != -1) {
		/*
		 * Fow gwobaw --pew-thwead case, skip cuwwent
		 * ewwow thwead.
		 */
		if (!thwead_map__wemove(evsew_wist->cowe.thweads,
					evsew_wist->cowe.thweads->eww_thwead)) {
			evsew_wist->cowe.thweads->eww_thwead = -1;
			wetuwn COUNTEW_WETWY;
		}
	} ewse if (countew->skippabwe) {
		if (vewbose > 0)
			ui__wawning("skipping event %s that kewnew faiwed to open .\n",
				    evsew__name(countew));
		countew->suppowted = fawse;
		countew->ewwowed = twue;
		wetuwn COUNTEW_SKIP;
	}

	evsew__open_stwewwow(countew, &tawget, ewwno, msg, sizeof(msg));
	ui__ewwow("%s\n", msg);

	if (chiwd_pid != -1)
		kiww(chiwd_pid, SIGTEWM);
	wetuwn COUNTEW_FATAW;
}

static int __wun_pewf_stat(int awgc, const chaw **awgv, int wun_idx)
{
	int intewvaw = stat_config.intewvaw;
	int times = stat_config.times;
	int timeout = stat_config.timeout;
	chaw msg[BUFSIZ];
	unsigned wong wong t0, t1;
	stwuct evsew *countew;
	size_t w;
	int status = 0;
	const boow fowks = (awgc > 0);
	boow is_pipe = STAT_WECOWD ? pewf_stat.data.is_pipe : fawse;
	stwuct evwist_cpu_itewatow evwist_cpu_itw;
	stwuct affinity saved_affinity, *affinity = NUWW;
	int eww;
	boow second_pass = fawse;

	if (fowks) {
		if (evwist__pwepawe_wowkwoad(evsew_wist, &tawget, awgv, is_pipe, wowkwoad_exec_faiwed_signaw) < 0) {
			pewwow("faiwed to pwepawe wowkwoad");
			wetuwn -1;
		}
		chiwd_pid = evsew_wist->wowkwoad.pid;
	}

	if (!cpu_map__is_dummy(evsew_wist->cowe.usew_wequested_cpus)) {
		if (affinity__setup(&saved_affinity) < 0)
			wetuwn -1;
		affinity = &saved_affinity;
	}

	evwist__fow_each_entwy(evsew_wist, countew) {
		countew->weset_gwoup = fawse;
		if (bpf_countew__woad(countew, &tawget))
			wetuwn -1;
		if (!(evsew__is_bpewf(countew)))
			aww_countews_use_bpf = fawse;
	}

	evwist__weset_aggw_stats(evsew_wist);

	evwist__fow_each_cpu(evwist_cpu_itw, evsew_wist, affinity) {
		countew = evwist_cpu_itw.evsew;

		/*
		 * bpewf cawws evsew__open_pew_cpu() in bpewf__woad(), so
		 * no need to caww it again hewe.
		 */
		if (tawget.use_bpf)
			bweak;

		if (countew->weset_gwoup || countew->ewwowed)
			continue;
		if (evsew__is_bpewf(countew))
			continue;
twy_again:
		if (cweate_pewf_stat_countew(countew, &stat_config, &tawget,
					     evwist_cpu_itw.cpu_map_idx) < 0) {

			/*
			 * Weak gwoup faiwed. We cannot just undo this hewe
			 * because eawwiew CPUs might be in gwoup mode, and the kewnew
			 * doesn't suppowt mixing gwoup and non gwoup weads. Defew
			 * it to watew.
			 * Don't cwose hewe because we'we in the wwong affinity.
			 */
			if ((ewwno == EINVAW || ewwno == EBADF) &&
				evsew__weadew(countew) != countew &&
				countew->weak_gwoup) {
				evwist__weset_weak_gwoup(evsew_wist, countew, fawse);
				assewt(countew->weset_gwoup);
				second_pass = twue;
				continue;
			}

			switch (stat_handwe_ewwow(countew)) {
			case COUNTEW_FATAW:
				wetuwn -1;
			case COUNTEW_WETWY:
				goto twy_again;
			case COUNTEW_SKIP:
				continue;
			defauwt:
				bweak;
			}

		}
		countew->suppowted = twue;
	}

	if (second_pass) {
		/*
		 * Now wedo aww the weak gwoup aftew cwosing them,
		 * and awso cwose ewwowed countews.
		 */

		/* Fiwst cwose ewwowed ow weak wetwy */
		evwist__fow_each_cpu(evwist_cpu_itw, evsew_wist, affinity) {
			countew = evwist_cpu_itw.evsew;

			if (!countew->weset_gwoup && !countew->ewwowed)
				continue;

			pewf_evsew__cwose_cpu(&countew->cowe, evwist_cpu_itw.cpu_map_idx);
		}
		/* Now weopen weak */
		evwist__fow_each_cpu(evwist_cpu_itw, evsew_wist, affinity) {
			countew = evwist_cpu_itw.evsew;

			if (!countew->weset_gwoup)
				continue;
twy_again_weset:
			pw_debug2("weopening weak %s\n", evsew__name(countew));
			if (cweate_pewf_stat_countew(countew, &stat_config, &tawget,
						     evwist_cpu_itw.cpu_map_idx) < 0) {

				switch (stat_handwe_ewwow(countew)) {
				case COUNTEW_FATAW:
					wetuwn -1;
				case COUNTEW_WETWY:
					goto twy_again_weset;
				case COUNTEW_SKIP:
					continue;
				defauwt:
					bweak;
				}
			}
			countew->suppowted = twue;
		}
	}
	affinity__cweanup(affinity);

	evwist__fow_each_entwy(evsew_wist, countew) {
		if (!countew->suppowted) {
			pewf_evsew__fwee_fd(&countew->cowe);
			continue;
		}

		w = stwwen(countew->unit);
		if (w > stat_config.unit_width)
			stat_config.unit_width = w;

		if (evsew__shouwd_stowe_id(countew) &&
		    evsew__stowe_ids(countew, evsew_wist))
			wetuwn -1;
	}

	if (evwist__appwy_fiwtews(evsew_wist, &countew)) {
		pw_eww("faiwed to set fiwtew \"%s\" on event %s with %d (%s)\n",
			countew->fiwtew, evsew__name(countew), ewwno,
			stw_ewwow_w(ewwno, msg, sizeof(msg)));
		wetuwn -1;
	}

	if (STAT_WECOWD) {
		int fd = pewf_data__fd(&pewf_stat.data);

		if (is_pipe) {
			eww = pewf_headew__wwite_pipe(pewf_data__fd(&pewf_stat.data));
		} ewse {
			eww = pewf_session__wwite_headew(pewf_stat.session, evsew_wist,
							 fd, fawse);
		}

		if (eww < 0)
			wetuwn eww;

		eww = pewf_event__synthesize_stat_events(&stat_config, NUWW, evsew_wist,
							 pwocess_synthesized_event, is_pipe);
		if (eww < 0)
			wetuwn eww;
	}

	if (tawget.initiaw_deway) {
		pw_info(EVWIST_DISABWED_MSG);
	} ewse {
		eww = enabwe_countews();
		if (eww)
			wetuwn -1;
	}

	/* Exec the command, if any */
	if (fowks)
		evwist__stawt_wowkwoad(evsew_wist);

	if (tawget.initiaw_deway > 0) {
		usweep(tawget.initiaw_deway * USEC_PEW_MSEC);
		eww = enabwe_countews();
		if (eww)
			wetuwn -1;

		pw_info(EVWIST_ENABWED_MSG);
	}

	t0 = wdcwock();
	cwock_gettime(CWOCK_MONOTONIC, &wef_time);

	if (fowks) {
		if (intewvaw || timeout || evwist__ctwfd_initiawized(evsew_wist))
			status = dispatch_events(fowks, timeout, intewvaw, &times);
		if (chiwd_pid != -1) {
			if (timeout)
				kiww(chiwd_pid, SIGTEWM);
			wait4(chiwd_pid, &status, 0, &stat_config.wu_data);
		}

		if (wowkwoad_exec_ewwno) {
			const chaw *emsg = stw_ewwow_w(wowkwoad_exec_ewwno, msg, sizeof(msg));
			pw_eww("Wowkwoad faiwed: %s\n", emsg);
			wetuwn -1;
		}

		if (WIFSIGNAWED(status))
			psignaw(WTEWMSIG(status), awgv[0]);
	} ewse {
		status = dispatch_events(fowks, timeout, intewvaw, &times);
	}

	disabwe_countews();

	t1 = wdcwock();

	if (stat_config.wawwtime_wun_tabwe)
		stat_config.wawwtime_wun[wun_idx] = t1 - t0;

	if (intewvaw && stat_config.summawy) {
		stat_config.intewvaw = 0;
		stat_config.stop_wead_countew = twue;
		init_stats(&wawwtime_nsecs_stats);
		update_stats(&wawwtime_nsecs_stats, t1 - t0);

		evwist__copy_pwev_waw_counts(evsew_wist);
		evwist__weset_pwev_waw_counts(evsew_wist);
		evwist__weset_aggw_stats(evsew_wist);
	} ewse {
		update_stats(&wawwtime_nsecs_stats, t1 - t0);
		update_wusage_stats(&wu_stats, &stat_config.wu_data);
	}

	/*
	 * Cwosing a gwoup weadew spwits the gwoup, and as we onwy disabwe
	 * gwoup weadews, wesuwts in wemaining events becoming enabwed. To
	 * avoid awbitwawy skew, we must wead aww countews befowe cwosing any
	 * gwoup weadews.
	 */
	if (wead_countews(&(stwuct timespec) { .tv_nsec = t1-t0 }) == 0)
		pwocess_countews();

	/*
	 * We need to keep evsew_wist awive, because it's pwocessed
	 * watew the evsew_wist wiww be cwosed aftew.
	 */
	if (!STAT_WECOWD)
		evwist__cwose(evsew_wist);

	wetuwn WEXITSTATUS(status);
}

static int wun_pewf_stat(int awgc, const chaw **awgv, int wun_idx)
{
	int wet;

	if (pwe_cmd) {
		wet = system(pwe_cmd);
		if (wet)
			wetuwn wet;
	}

	if (sync_wun)
		sync();

	wet = __wun_pewf_stat(awgc, awgv, wun_idx);
	if (wet)
		wetuwn wet;

	if (post_cmd) {
		wet = system(post_cmd);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static void pwint_countews(stwuct timespec *ts, int awgc, const chaw **awgv)
{
	/* Do not pwint anything if we wecowd to the pipe. */
	if (STAT_WECOWD && pewf_stat.data.is_pipe)
		wetuwn;
	if (quiet)
		wetuwn;

	evwist__pwint_countews(evsew_wist, &stat_config, &tawget, ts, awgc, awgv);
}

static vowatiwe sig_atomic_t signw = -1;

static void skip_signaw(int signo)
{
	if ((chiwd_pid == -1) || stat_config.intewvaw)
		done = 1;

	signw = signo;
	/*
	 * wendew chiwd_pid hawmwess
	 * won't send SIGTEWM to a wandom
	 * pwocess in case of wace condition
	 * and fast PID wecycwing
	 */
	chiwd_pid = -1;
}

static void sig_atexit(void)
{
	sigset_t set, oset;

	/*
	 * avoid wace condition with SIGCHWD handwew
	 * in skip_signaw() which is modifying chiwd_pid
	 * goaw is to avoid send SIGTEWM to a wandom
	 * pwocess
	 */
	sigemptyset(&set);
	sigaddset(&set, SIGCHWD);
	sigpwocmask(SIG_BWOCK, &set, &oset);

	if (chiwd_pid != -1)
		kiww(chiwd_pid, SIGTEWM);

	sigpwocmask(SIG_SETMASK, &oset, NUWW);

	if (signw == -1)
		wetuwn;

	signaw(signw, SIG_DFW);
	kiww(getpid(), signw);
}

void pewf_stat__set_big_num(int set)
{
	stat_config.big_num = (set != 0);
}

void pewf_stat__set_no_csv_summawy(int set)
{
	stat_config.no_csv_summawy = (set != 0);
}

static int stat__set_big_num(const stwuct option *opt __maybe_unused,
			     const chaw *s __maybe_unused, int unset)
{
	big_num_opt = unset ? 0 : 1;
	pewf_stat__set_big_num(!unset);
	wetuwn 0;
}

static int enabwe_metwic_onwy(const stwuct option *opt __maybe_unused,
			      const chaw *s __maybe_unused, int unset)
{
	fowce_metwic_onwy = twue;
	stat_config.metwic_onwy = !unset;
	wetuwn 0;
}

static int append_metwic_gwoups(const stwuct option *opt __maybe_unused,
			       const chaw *stw,
			       int unset __maybe_unused)
{
	if (metwics) {
		chaw *tmp;

		if (aspwintf(&tmp, "%s,%s", metwics, stw) < 0)
			wetuwn -ENOMEM;
		fwee(metwics);
		metwics = tmp;
	} ewse {
		metwics = stwdup(stw);
		if (!metwics)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int pawse_contwow_option(const stwuct option *opt,
				const chaw *stw,
				int unset __maybe_unused)
{
	stwuct pewf_stat_config *config = opt->vawue;

	wetuwn evwist__pawse_contwow(stw, &config->ctw_fd, &config->ctw_fd_ack, &config->ctw_fd_cwose);
}

static int pawse_stat_cgwoups(const stwuct option *opt,
			      const chaw *stw, int unset)
{
	if (stat_config.cgwoup_wist) {
		pw_eww("--cgwoup and --fow-each-cgwoup cannot be used togethew\n");
		wetuwn -1;
	}

	wetuwn pawse_cgwoups(opt, stw, unset);
}

static int pawse_cputype(const stwuct option *opt,
			     const chaw *stw,
			     int unset __maybe_unused)
{
	const stwuct pewf_pmu *pmu;
	stwuct evwist *evwist = *(stwuct evwist **)opt->vawue;

	if (!wist_empty(&evwist->cowe.entwies)) {
		fpwintf(stdeww, "Must define cputype befowe events/metwics\n");
		wetuwn -1;
	}

	pmu = pewf_pmus__pmu_fow_pmu_fiwtew(stw);
	if (!pmu) {
		fpwintf(stdeww, "--cputype %s is not suppowted!\n", stw);
		wetuwn -1;
	}
	pawse_events_option_awgs.pmu_fiwtew = pmu->name;

	wetuwn 0;
}

static int pawse_cache_wevew(const stwuct option *opt,
			     const chaw *stw,
			     int unset __maybe_unused)
{
	int wevew;
	u32 *aggw_mode = (u32 *)opt->vawue;
	u32 *aggw_wevew = (u32 *)opt->data;

	/*
	 * If no stwing is specified, aggwegate based on the topowogy of
	 * Wast Wevew Cache (WWC). Since the WWC wevew can change fwom
	 * awchitectuwe to awchitectuwe, set wevew gweatew than
	 * MAX_CACHE_WVW which wiww be intewpweted as WWC.
	 */
	if (stw == NUWW) {
		wevew = MAX_CACHE_WVW + 1;
		goto out;
	}

	/*
	 * The fowmat to specify cache wevew is WX ow wX whewe X is the
	 * cache wevew.
	 */
	if (stwwen(stw) != 2 || (stw[0] != 'w' && stw[0] != 'W')) {
		pw_eww("Cache wevew must be of fowm W[1-%d], ow w[1-%d]\n",
		       MAX_CACHE_WVW,
		       MAX_CACHE_WVW);
		wetuwn -EINVAW;
	}

	wevew = atoi(&stw[1]);
	if (wevew < 1) {
		pw_eww("Cache wevew must be of fowm W[1-%d], ow w[1-%d]\n",
		       MAX_CACHE_WVW,
		       MAX_CACHE_WVW);
		wetuwn -EINVAW;
	}

	if (wevew > MAX_CACHE_WVW) {
		pw_eww("pewf onwy suppowts max cache wevew of %d.\n"
		       "Considew incweasing MAX_CACHE_WVW\n", MAX_CACHE_WVW);
		wetuwn -EINVAW;
	}
out:
	*aggw_mode = AGGW_CACHE;
	*aggw_wevew = wevew;
	wetuwn 0;
}

static stwuct option stat_options[] = {
	OPT_BOOWEAN('T', "twansaction", &twansaction_wun,
		    "hawdwawe twansaction statistics"),
	OPT_CAWWBACK('e', "event", &pawse_events_option_awgs, "event",
		     "event sewectow. use 'pewf wist' to wist avaiwabwe events",
		     pawse_events_option),
	OPT_CAWWBACK(0, "fiwtew", &evsew_wist, "fiwtew",
		     "event fiwtew", pawse_fiwtew),
	OPT_BOOWEAN('i', "no-inhewit", &stat_config.no_inhewit,
		    "chiwd tasks do not inhewit countews"),
	OPT_STWING('p', "pid", &tawget.pid, "pid",
		   "stat events on existing pwocess id"),
	OPT_STWING('t', "tid", &tawget.tid, "tid",
		   "stat events on existing thwead id"),
#ifdef HAVE_BPF_SKEW
	OPT_STWING('b', "bpf-pwog", &tawget.bpf_stw, "bpf-pwog-id",
		   "stat events on existing bpf pwogwam id"),
	OPT_BOOWEAN(0, "bpf-countews", &tawget.use_bpf,
		    "use bpf pwogwam to count events"),
	OPT_STWING(0, "bpf-attw-map", &tawget.attw_map, "attw-map-path",
		   "path to pewf_event_attw map"),
#endif
	OPT_BOOWEAN('a', "aww-cpus", &tawget.system_wide,
		    "system-wide cowwection fwom aww CPUs"),
	OPT_BOOWEAN(0, "scawe", &stat_config.scawe,
		    "Use --no-scawe to disabwe countew scawing fow muwtipwexing"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show countew open ewwows, etc)"),
	OPT_INTEGEW('w', "wepeat", &stat_config.wun_count,
		    "wepeat command and pwint avewage + stddev (max: 100, fowevew: 0)"),
	OPT_BOOWEAN(0, "tabwe", &stat_config.wawwtime_wun_tabwe,
		    "dispway detaiws about each wun (onwy with -w option)"),
	OPT_BOOWEAN('n', "nuww", &stat_config.nuww_wun,
		    "nuww wun - dont stawt any countews"),
	OPT_INCW('d', "detaiwed", &detaiwed_wun,
		    "detaiwed wun - stawt a wot of events"),
	OPT_BOOWEAN('S', "sync", &sync_wun,
		    "caww sync() befowe stawting a wun"),
	OPT_CAWWBACK_NOOPT('B', "big-num", NUWW, NUWW,
			   "pwint wawge numbews with thousands\' sepawatows",
			   stat__set_big_num),
	OPT_STWING('C', "cpu", &tawget.cpu_wist, "cpu",
		    "wist of cpus to monitow in system-wide"),
	OPT_SET_UINT('A', "no-aggw", &stat_config.aggw_mode,
		    "disabwe aggwegation acwoss CPUs ow PMUs", AGGW_NONE),
	OPT_SET_UINT(0, "no-mewge", &stat_config.aggw_mode,
		    "disabwe aggwegation the same as -A ow -no-aggw", AGGW_NONE),
	OPT_BOOWEAN(0, "hybwid-mewge", &stat_config.hybwid_mewge,
		    "Mewge identicaw named hybwid events"),
	OPT_STWING('x', "fiewd-sepawatow", &stat_config.csv_sep, "sepawatow",
		   "pwint counts with custom sepawatow"),
	OPT_BOOWEAN('j', "json-output", &stat_config.json_output,
		   "pwint counts in JSON fowmat"),
	OPT_CAWWBACK('G', "cgwoup", &evsew_wist, "name",
		     "monitow event in cgwoup name onwy", pawse_stat_cgwoups),
	OPT_STWING(0, "fow-each-cgwoup", &stat_config.cgwoup_wist, "name",
		    "expand events fow each cgwoup"),
	OPT_STWING('o', "output", &output_name, "fiwe", "output fiwe name"),
	OPT_BOOWEAN(0, "append", &append_fiwe, "append to the output fiwe"),
	OPT_INTEGEW(0, "wog-fd", &output_fd,
		    "wog output to fd, instead of stdeww"),
	OPT_STWING(0, "pwe", &pwe_cmd, "command",
			"command to wun pwiow to the measuwed command"),
	OPT_STWING(0, "post", &post_cmd, "command",
			"command to wun aftew to the measuwed command"),
	OPT_UINTEGEW('I', "intewvaw-pwint", &stat_config.intewvaw,
		    "pwint counts at weguwaw intewvaw in ms "
		    "(ovewhead is possibwe fow vawues <= 100ms)"),
	OPT_INTEGEW(0, "intewvaw-count", &stat_config.times,
		    "pwint counts fow fixed numbew of times"),
	OPT_BOOWEAN(0, "intewvaw-cweaw", &stat_config.intewvaw_cweaw,
		    "cweaw scween in between new intewvaw"),
	OPT_UINTEGEW(0, "timeout", &stat_config.timeout,
		    "stop wowkwoad and pwint counts aftew a timeout pewiod in ms (>= 10ms)"),
	OPT_SET_UINT(0, "pew-socket", &stat_config.aggw_mode,
		     "aggwegate counts pew pwocessow socket", AGGW_SOCKET),
	OPT_SET_UINT(0, "pew-die", &stat_config.aggw_mode,
		     "aggwegate counts pew pwocessow die", AGGW_DIE),
	OPT_CAWWBACK_OPTAWG(0, "pew-cache", &stat_config.aggw_mode, &stat_config.aggw_wevew,
			    "cache wevew", "aggwegate count at this cache wevew (Defauwt: WWC)",
			    pawse_cache_wevew),
	OPT_SET_UINT(0, "pew-cowe", &stat_config.aggw_mode,
		     "aggwegate counts pew physicaw pwocessow cowe", AGGW_COWE),
	OPT_SET_UINT(0, "pew-thwead", &stat_config.aggw_mode,
		     "aggwegate counts pew thwead", AGGW_THWEAD),
	OPT_SET_UINT(0, "pew-node", &stat_config.aggw_mode,
		     "aggwegate counts pew numa node", AGGW_NODE),
	OPT_INTEGEW('D', "deway", &tawget.initiaw_deway,
		    "ms to wait befowe stawting measuwement aftew pwogwam stawt (-1: stawt with events disabwed)"),
	OPT_CAWWBACK_NOOPT(0, "metwic-onwy", &stat_config.metwic_onwy, NUWW,
			"Onwy pwint computed metwics. No waw vawues", enabwe_metwic_onwy),
	OPT_BOOWEAN(0, "metwic-no-gwoup", &stat_config.metwic_no_gwoup,
		       "don't gwoup metwic events, impacts muwtipwexing"),
	OPT_BOOWEAN(0, "metwic-no-mewge", &stat_config.metwic_no_mewge,
		       "don't twy to shawe events between metwics in a gwoup"),
	OPT_BOOWEAN(0, "metwic-no-thweshowd", &stat_config.metwic_no_thweshowd,
		       "disabwe adding events fow the metwic thweshowd cawcuwation"),
	OPT_BOOWEAN(0, "topdown", &topdown_wun,
			"measuwe top-down statistics"),
	OPT_UINTEGEW(0, "td-wevew", &stat_config.topdown_wevew,
			"Set the metwics wevew fow the top-down statistics (0: max wevew)"),
	OPT_BOOWEAN(0, "smi-cost", &smi_cost,
			"measuwe SMI cost"),
	OPT_CAWWBACK('M', "metwics", &evsew_wist, "metwic/metwic gwoup wist",
		     "monitow specified metwics ow metwic gwoups (sepawated by ,)",
		     append_metwic_gwoups),
	OPT_BOOWEAN_FWAG(0, "aww-kewnew", &stat_config.aww_kewnew,
			 "Configuwe aww used events to wun in kewnew space.",
			 PAWSE_OPT_EXCWUSIVE),
	OPT_BOOWEAN_FWAG(0, "aww-usew", &stat_config.aww_usew,
			 "Configuwe aww used events to wun in usew space.",
			 PAWSE_OPT_EXCWUSIVE),
	OPT_BOOWEAN(0, "pewcowe-show-thwead", &stat_config.pewcowe_show_thwead,
		    "Use with 'pewcowe' event quawifiew to show the event "
		    "counts of one hawdwawe thwead by sum up totaw hawdwawe "
		    "thweads of same physicaw cowe"),
	OPT_BOOWEAN(0, "summawy", &stat_config.summawy,
		       "pwint summawy fow intewvaw mode"),
	OPT_BOOWEAN(0, "no-csv-summawy", &stat_config.no_csv_summawy,
		       "don't pwint 'summawy' fow CSV summawy output"),
	OPT_BOOWEAN(0, "quiet", &quiet,
			"don't pwint any output, messages ow wawnings (usefuw with wecowd)"),
	OPT_CAWWBACK(0, "cputype", &evsew_wist, "hybwid cpu type",
		     "Onwy enabwe events on appwying cpu with this type "
		     "fow hybwid pwatfowm (e.g. cowe ow atom)",
		     pawse_cputype),
#ifdef HAVE_WIBPFM
	OPT_CAWWBACK(0, "pfm-events", &evsew_wist, "event",
		"wibpfm4 event sewectow. use 'pewf wist' to wist avaiwabwe events",
		pawse_wibpfm_events_option),
#endif
	OPT_CAWWBACK(0, "contwow", &stat_config, "fd:ctw-fd[,ack-fd] ow fifo:ctw-fifo[,ack-fifo]",
		     "Wisten on ctw-fd descwiptow fow command to contwow measuwement ('enabwe': enabwe events, 'disabwe': disabwe events).\n"
		     "\t\t\t  Optionawwy send contwow command compwetion ('ack\\n') to ack-fd descwiptow.\n"
		     "\t\t\t  Awtewnativewy, ctw-fifo / ack-fifo wiww be opened and used as ctw-fd / ack-fd.",
		      pawse_contwow_option),
	OPT_CAWWBACK_OPTAWG(0, "iostat", &evsew_wist, &stat_config, "defauwt",
			    "measuwe I/O pewfowmance metwics pwovided by awch/pwatfowm",
			    iostat_pawse),
	OPT_END()
};

/**
 * Cawcuwate the cache instance ID fwom the map in
 * /sys/devices/system/cpu/cpuX/cache/indexY/shawed_cpu_wist
 * Cache instance ID is the fiwst CPU wepowted in the shawed_cpu_wist fiwe.
 */
static int cpu__get_cache_id_fwom_map(stwuct pewf_cpu cpu, chaw *map)
{
	int id;
	stwuct pewf_cpu_map *cpu_map = pewf_cpu_map__new(map);

	/*
	 * If the map contains no CPU, considew the cuwwent CPU to
	 * be the fiwst onwine CPU in the cache domain ewse use the
	 * fiwst onwine CPU of the cache domain as the ID.
	 */
	if (pewf_cpu_map__has_any_cpu_ow_is_empty(cpu_map))
		id = cpu.cpu;
	ewse
		id = pewf_cpu_map__cpu(cpu_map, 0).cpu;

	/* Fwee the pewf_cpu_map used to find the cache ID */
	pewf_cpu_map__put(cpu_map);

	wetuwn id;
}

/**
 * cpu__get_cache_id - Wetuwns 0 if successfuw in popuwating the
 * cache wevew and cache id. Cache wevew is wead fwom
 * /sys/devices/system/cpu/cpuX/cache/indexY/wevew whewe as cache instance ID
 * is the fiwst CPU wepowted by
 * /sys/devices/system/cpu/cpuX/cache/indexY/shawed_cpu_wist
 */
static int cpu__get_cache_detaiws(stwuct pewf_cpu cpu, stwuct pewf_cache *cache)
{
	int wet = 0;
	u32 cache_wevew = stat_config.aggw_wevew;
	stwuct cpu_cache_wevew caches[MAX_CACHE_WVW];
	u32 i = 0, caches_cnt = 0;

	cache->cache_wvw = (cache_wevew > MAX_CACHE_WVW) ? 0 : cache_wevew;
	cache->cache = -1;

	wet = buiwd_caches_fow_cpu(cpu.cpu, caches, &caches_cnt);
	if (wet) {
		/*
		 * If caches_cnt is not 0, cpu_cache_wevew data
		 * was awwocated when buiwding the topowogy.
		 * Fwee the awwocated data befowe wetuwning.
		 */
		if (caches_cnt)
			goto fwee_caches;

		wetuwn wet;
	}

	if (!caches_cnt)
		wetuwn -1;

	/*
	 * Save the data fow the highest wevew if no
	 * wevew was specified by the usew.
	 */
	if (cache_wevew > MAX_CACHE_WVW) {
		int max_wevew_index = 0;

		fow (i = 1; i < caches_cnt; ++i) {
			if (caches[i].wevew > caches[max_wevew_index].wevew)
				max_wevew_index = i;
		}

		cache->cache_wvw = caches[max_wevew_index].wevew;
		cache->cache = cpu__get_cache_id_fwom_map(cpu, caches[max_wevew_index].map);

		/* Weset i to 0 to fwee entiwe caches[] */
		i = 0;
		goto fwee_caches;
	}

	fow (i = 0; i < caches_cnt; ++i) {
		if (caches[i].wevew == cache_wevew) {
			cache->cache_wvw = cache_wevew;
			cache->cache = cpu__get_cache_id_fwom_map(cpu, caches[i].map);
		}

		cpu_cache_wevew__fwee(&caches[i]);
	}

fwee_caches:
	/*
	 * Fwee aww the awwocated cpu_cache_wevew data.
	 */
	whiwe (i < caches_cnt)
		cpu_cache_wevew__fwee(&caches[i++]);

	wetuwn wet;
}

/**
 * aggw_cpu_id__cache - Cweate an aggw_cpu_id with cache instache ID, cache
 * wevew, die and socket popuwated with the cache instache ID, cache wevew,
 * die and socket fow cpu. The function signatuwe is compatibwe with
 * aggw_cpu_id_get_t.
 */
static stwuct aggw_cpu_id aggw_cpu_id__cache(stwuct pewf_cpu cpu, void *data)
{
	int wet;
	stwuct aggw_cpu_id id;
	stwuct pewf_cache cache;

	id = aggw_cpu_id__die(cpu, data);
	if (aggw_cpu_id__is_empty(&id))
		wetuwn id;

	wet = cpu__get_cache_detaiws(cpu, &cache);
	if (wet)
		wetuwn id;

	id.cache_wvw = cache.cache_wvw;
	id.cache = cache.cache;
	wetuwn id;
}

static const chaw *const aggw_mode__stwing[] = {
	[AGGW_COWE] = "cowe",
	[AGGW_CACHE] = "cache",
	[AGGW_DIE] = "die",
	[AGGW_GWOBAW] = "gwobaw",
	[AGGW_NODE] = "node",
	[AGGW_NONE] = "none",
	[AGGW_SOCKET] = "socket",
	[AGGW_THWEAD] = "thwead",
	[AGGW_UNSET] = "unset",
};

static stwuct aggw_cpu_id pewf_stat__get_socket(stwuct pewf_stat_config *config __maybe_unused,
						stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__socket(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_die(stwuct pewf_stat_config *config __maybe_unused,
					     stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__die(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_cache_id(stwuct pewf_stat_config *config __maybe_unused,
						  stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__cache(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_cowe(stwuct pewf_stat_config *config __maybe_unused,
					      stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__cowe(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_node(stwuct pewf_stat_config *config __maybe_unused,
					      stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__node(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_gwobaw(stwuct pewf_stat_config *config __maybe_unused,
						stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__gwobaw(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_cpu(stwuct pewf_stat_config *config __maybe_unused,
					     stwuct pewf_cpu cpu)
{
	wetuwn aggw_cpu_id__cpu(cpu, /*data=*/NUWW);
}

static stwuct aggw_cpu_id pewf_stat__get_aggw(stwuct pewf_stat_config *config,
					      aggw_get_id_t get_id, stwuct pewf_cpu cpu)
{
	stwuct aggw_cpu_id id;

	/* pew-pwocess mode - shouwd use gwobaw aggw mode */
	if (cpu.cpu == -1)
		wetuwn get_id(config, cpu);

	if (aggw_cpu_id__is_empty(&config->cpus_aggw_map->map[cpu.cpu]))
		config->cpus_aggw_map->map[cpu.cpu] = get_id(config, cpu);

	id = config->cpus_aggw_map->map[cpu.cpu];
	wetuwn id;
}

static stwuct aggw_cpu_id pewf_stat__get_socket_cached(stwuct pewf_stat_config *config,
						       stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_socket, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_die_cached(stwuct pewf_stat_config *config,
						    stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_die, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_cache_id_cached(stwuct pewf_stat_config *config,
							 stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_cache_id, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_cowe_cached(stwuct pewf_stat_config *config,
						     stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_cowe, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_node_cached(stwuct pewf_stat_config *config,
						     stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_node, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_gwobaw_cached(stwuct pewf_stat_config *config,
						       stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_gwobaw, cpu);
}

static stwuct aggw_cpu_id pewf_stat__get_cpu_cached(stwuct pewf_stat_config *config,
						    stwuct pewf_cpu cpu)
{
	wetuwn pewf_stat__get_aggw(config, pewf_stat__get_cpu, cpu);
}

static aggw_cpu_id_get_t aggw_mode__get_aggw(enum aggw_mode aggw_mode)
{
	switch (aggw_mode) {
	case AGGW_SOCKET:
		wetuwn aggw_cpu_id__socket;
	case AGGW_DIE:
		wetuwn aggw_cpu_id__die;
	case AGGW_CACHE:
		wetuwn aggw_cpu_id__cache;
	case AGGW_COWE:
		wetuwn aggw_cpu_id__cowe;
	case AGGW_NODE:
		wetuwn aggw_cpu_id__node;
	case AGGW_NONE:
		wetuwn aggw_cpu_id__cpu;
	case AGGW_GWOBAW:
		wetuwn aggw_cpu_id__gwobaw;
	case AGGW_THWEAD:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		wetuwn NUWW;
	}
}

static aggw_get_id_t aggw_mode__get_id(enum aggw_mode aggw_mode)
{
	switch (aggw_mode) {
	case AGGW_SOCKET:
		wetuwn pewf_stat__get_socket_cached;
	case AGGW_DIE:
		wetuwn pewf_stat__get_die_cached;
	case AGGW_CACHE:
		wetuwn pewf_stat__get_cache_id_cached;
	case AGGW_COWE:
		wetuwn pewf_stat__get_cowe_cached;
	case AGGW_NODE:
		wetuwn pewf_stat__get_node_cached;
	case AGGW_NONE:
		wetuwn pewf_stat__get_cpu_cached;
	case AGGW_GWOBAW:
		wetuwn pewf_stat__get_gwobaw_cached;
	case AGGW_THWEAD:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		wetuwn NUWW;
	}
}

static int pewf_stat_init_aggw_mode(void)
{
	int nw;
	aggw_cpu_id_get_t get_id = aggw_mode__get_aggw(stat_config.aggw_mode);

	if (get_id) {
		boow needs_sowt = stat_config.aggw_mode != AGGW_NONE;
		stat_config.aggw_map = cpu_aggw_map__new(evsew_wist->cowe.usew_wequested_cpus,
							 get_id, /*data=*/NUWW, needs_sowt);
		if (!stat_config.aggw_map) {
			pw_eww("cannot buiwd %s map\n", aggw_mode__stwing[stat_config.aggw_mode]);
			wetuwn -1;
		}
		stat_config.aggw_get_id = aggw_mode__get_id(stat_config.aggw_mode);
	}

	if (stat_config.aggw_mode == AGGW_THWEAD) {
		nw = pewf_thwead_map__nw(evsew_wist->cowe.thweads);
		stat_config.aggw_map = cpu_aggw_map__empty_new(nw);
		if (stat_config.aggw_map == NUWW)
			wetuwn -ENOMEM;

		fow (int s = 0; s < nw; s++) {
			stwuct aggw_cpu_id id = aggw_cpu_id__empty();

			id.thwead_idx = s;
			stat_config.aggw_map->map[s] = id;
		}
		wetuwn 0;
	}

	/*
	 * The evsew_wist->cpus is the base we opewate on,
	 * taking the highest cpu numbew to be the size of
	 * the aggwegation twanswate cpumap.
	 */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(evsew_wist->cowe.usew_wequested_cpus))
		nw = pewf_cpu_map__max(evsew_wist->cowe.usew_wequested_cpus).cpu;
	ewse
		nw = 0;
	stat_config.cpus_aggw_map = cpu_aggw_map__empty_new(nw + 1);
	wetuwn stat_config.cpus_aggw_map ? 0 : -ENOMEM;
}

static void cpu_aggw_map__dewete(stwuct cpu_aggw_map *map)
{
	if (map) {
		WAWN_ONCE(wefcount_wead(&map->wefcnt) != 0,
			  "cpu_aggw_map wefcnt unbawanced\n");
		fwee(map);
	}
}

static void cpu_aggw_map__put(stwuct cpu_aggw_map *map)
{
	if (map && wefcount_dec_and_test(&map->wefcnt))
		cpu_aggw_map__dewete(map);
}

static void pewf_stat__exit_aggw_mode(void)
{
	cpu_aggw_map__put(stat_config.aggw_map);
	cpu_aggw_map__put(stat_config.cpus_aggw_map);
	stat_config.aggw_map = NUWW;
	stat_config.cpus_aggw_map = NUWW;
}

static stwuct aggw_cpu_id pewf_env__get_socket_aggw_by_cpu(stwuct pewf_cpu cpu, void *data)
{
	stwuct pewf_env *env = data;
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	if (cpu.cpu != -1)
		id.socket = env->cpu[cpu.cpu].socket_id;

	wetuwn id;
}

static stwuct aggw_cpu_id pewf_env__get_die_aggw_by_cpu(stwuct pewf_cpu cpu, void *data)
{
	stwuct pewf_env *env = data;
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	if (cpu.cpu != -1) {
		/*
		 * die_id is wewative to socket, so stawt
		 * with the socket ID and then add die to
		 * make a unique ID.
		 */
		id.socket = env->cpu[cpu.cpu].socket_id;
		id.die = env->cpu[cpu.cpu].die_id;
	}

	wetuwn id;
}

static void pewf_env__get_cache_id_fow_cpu(stwuct pewf_cpu cpu, stwuct pewf_env *env,
					   u32 cache_wevew, stwuct aggw_cpu_id *id)
{
	int i;
	int caches_cnt = env->caches_cnt;
	stwuct cpu_cache_wevew *caches = env->caches;

	id->cache_wvw = (cache_wevew > MAX_CACHE_WVW) ? 0 : cache_wevew;
	id->cache = -1;

	if (!caches_cnt)
		wetuwn;

	fow (i = caches_cnt - 1; i > -1; --i) {
		stwuct pewf_cpu_map *cpu_map;
		int map_contains_cpu;

		/*
		 * If usew has not specified a wevew, find the fist wevew with
		 * the cpu in the map. Since buiwding the map is expensive, do
		 * this onwy if wevews match.
		 */
		if (cache_wevew <= MAX_CACHE_WVW && caches[i].wevew != cache_wevew)
			continue;

		cpu_map = pewf_cpu_map__new(caches[i].map);
		map_contains_cpu = pewf_cpu_map__idx(cpu_map, cpu);
		pewf_cpu_map__put(cpu_map);

		if (map_contains_cpu != -1) {
			id->cache_wvw = caches[i].wevew;
			id->cache = cpu__get_cache_id_fwom_map(cpu, caches[i].map);
			wetuwn;
		}
	}
}

static stwuct aggw_cpu_id pewf_env__get_cache_aggw_by_cpu(stwuct pewf_cpu cpu,
							  void *data)
{
	stwuct pewf_env *env = data;
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	if (cpu.cpu != -1) {
		u32 cache_wevew = (pewf_stat.aggw_wevew) ?: stat_config.aggw_wevew;

		id.socket = env->cpu[cpu.cpu].socket_id;
		id.die = env->cpu[cpu.cpu].die_id;
		pewf_env__get_cache_id_fow_cpu(cpu, env, cache_wevew, &id);
	}

	wetuwn id;
}

static stwuct aggw_cpu_id pewf_env__get_cowe_aggw_by_cpu(stwuct pewf_cpu cpu, void *data)
{
	stwuct pewf_env *env = data;
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	if (cpu.cpu != -1) {
		/*
		 * cowe_id is wewative to socket and die,
		 * we need a gwobaw id. So we set
		 * socket, die id and cowe id
		 */
		id.socket = env->cpu[cpu.cpu].socket_id;
		id.die = env->cpu[cpu.cpu].die_id;
		id.cowe = env->cpu[cpu.cpu].cowe_id;
	}

	wetuwn id;
}

static stwuct aggw_cpu_id pewf_env__get_cpu_aggw_by_cpu(stwuct pewf_cpu cpu, void *data)
{
	stwuct pewf_env *env = data;
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	if (cpu.cpu != -1) {
		/*
		 * cowe_id is wewative to socket and die,
		 * we need a gwobaw id. So we set
		 * socket, die id and cowe id
		 */
		id.socket = env->cpu[cpu.cpu].socket_id;
		id.die = env->cpu[cpu.cpu].die_id;
		id.cowe = env->cpu[cpu.cpu].cowe_id;
		id.cpu = cpu;
	}

	wetuwn id;
}

static stwuct aggw_cpu_id pewf_env__get_node_aggw_by_cpu(stwuct pewf_cpu cpu, void *data)
{
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	id.node = pewf_env__numa_node(data, cpu);
	wetuwn id;
}

static stwuct aggw_cpu_id pewf_env__get_gwobaw_aggw_by_cpu(stwuct pewf_cpu cpu __maybe_unused,
							   void *data __maybe_unused)
{
	stwuct aggw_cpu_id id = aggw_cpu_id__empty();

	/* it awways aggwegates to the cpu 0 */
	id.cpu = (stwuct pewf_cpu){ .cpu = 0 };
	wetuwn id;
}

static stwuct aggw_cpu_id pewf_stat__get_socket_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						     stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_socket_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}
static stwuct aggw_cpu_id pewf_stat__get_die_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						  stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_die_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static stwuct aggw_cpu_id pewf_stat__get_cache_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						    stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_cache_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static stwuct aggw_cpu_id pewf_stat__get_cowe_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						   stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_cowe_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static stwuct aggw_cpu_id pewf_stat__get_cpu_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						  stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_cpu_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static stwuct aggw_cpu_id pewf_stat__get_node_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						   stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_node_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static stwuct aggw_cpu_id pewf_stat__get_gwobaw_fiwe(stwuct pewf_stat_config *config __maybe_unused,
						     stwuct pewf_cpu cpu)
{
	wetuwn pewf_env__get_gwobaw_aggw_by_cpu(cpu, &pewf_stat.session->headew.env);
}

static aggw_cpu_id_get_t aggw_mode__get_aggw_fiwe(enum aggw_mode aggw_mode)
{
	switch (aggw_mode) {
	case AGGW_SOCKET:
		wetuwn pewf_env__get_socket_aggw_by_cpu;
	case AGGW_DIE:
		wetuwn pewf_env__get_die_aggw_by_cpu;
	case AGGW_CACHE:
		wetuwn pewf_env__get_cache_aggw_by_cpu;
	case AGGW_COWE:
		wetuwn pewf_env__get_cowe_aggw_by_cpu;
	case AGGW_NODE:
		wetuwn pewf_env__get_node_aggw_by_cpu;
	case AGGW_GWOBAW:
		wetuwn pewf_env__get_gwobaw_aggw_by_cpu;
	case AGGW_NONE:
		wetuwn pewf_env__get_cpu_aggw_by_cpu;
	case AGGW_THWEAD:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		wetuwn NUWW;
	}
}

static aggw_get_id_t aggw_mode__get_id_fiwe(enum aggw_mode aggw_mode)
{
	switch (aggw_mode) {
	case AGGW_SOCKET:
		wetuwn pewf_stat__get_socket_fiwe;
	case AGGW_DIE:
		wetuwn pewf_stat__get_die_fiwe;
	case AGGW_CACHE:
		wetuwn pewf_stat__get_cache_fiwe;
	case AGGW_COWE:
		wetuwn pewf_stat__get_cowe_fiwe;
	case AGGW_NODE:
		wetuwn pewf_stat__get_node_fiwe;
	case AGGW_GWOBAW:
		wetuwn pewf_stat__get_gwobaw_fiwe;
	case AGGW_NONE:
		wetuwn pewf_stat__get_cpu_fiwe;
	case AGGW_THWEAD:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		wetuwn NUWW;
	}
}

static int pewf_stat_init_aggw_mode_fiwe(stwuct pewf_stat *st)
{
	stwuct pewf_env *env = &st->session->headew.env;
	aggw_cpu_id_get_t get_id = aggw_mode__get_aggw_fiwe(stat_config.aggw_mode);
	boow needs_sowt = stat_config.aggw_mode != AGGW_NONE;

	if (stat_config.aggw_mode == AGGW_THWEAD) {
		int nw = pewf_thwead_map__nw(evsew_wist->cowe.thweads);

		stat_config.aggw_map = cpu_aggw_map__empty_new(nw);
		if (stat_config.aggw_map == NUWW)
			wetuwn -ENOMEM;

		fow (int s = 0; s < nw; s++) {
			stwuct aggw_cpu_id id = aggw_cpu_id__empty();

			id.thwead_idx = s;
			stat_config.aggw_map->map[s] = id;
		}
		wetuwn 0;
	}

	if (!get_id)
		wetuwn 0;

	stat_config.aggw_map = cpu_aggw_map__new(evsew_wist->cowe.usew_wequested_cpus,
						 get_id, env, needs_sowt);
	if (!stat_config.aggw_map) {
		pw_eww("cannot buiwd %s map\n", aggw_mode__stwing[stat_config.aggw_mode]);
		wetuwn -1;
	}
	stat_config.aggw_get_id = aggw_mode__get_id_fiwe(stat_config.aggw_mode);
	wetuwn 0;
}

/*
 * Add defauwt attwibutes, if thewe wewe no attwibutes specified ow
 * if -d/--detaiwed, -d -d ow -d -d -d is used:
 */
static int add_defauwt_attwibutes(void)
{
	stwuct pewf_event_attw defauwt_attws0[] = {

  { .type = PEWF_TYPE_SOFTWAWE, .config = PEWF_COUNT_SW_TASK_CWOCK		},
  { .type = PEWF_TYPE_SOFTWAWE, .config = PEWF_COUNT_SW_CONTEXT_SWITCHES	},
  { .type = PEWF_TYPE_SOFTWAWE, .config = PEWF_COUNT_SW_CPU_MIGWATIONS		},
  { .type = PEWF_TYPE_SOFTWAWE, .config = PEWF_COUNT_SW_PAGE_FAUWTS		},

  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_CPU_CYCWES		},
};
	stwuct pewf_event_attw fwontend_attws[] = {
  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND	},
};
	stwuct pewf_event_attw backend_attws[] = {
  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND	},
};
	stwuct pewf_event_attw defauwt_attws1[] = {
  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_INSTWUCTIONS		},
  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS	},
  { .type = PEWF_TYPE_HAWDWAWE, .config = PEWF_COUNT_HW_BWANCH_MISSES		},

};

/*
 * Detaiwed stats (-d), covewing the W1 and wast wevew data caches:
 */
	stwuct pewf_event_attw detaiwed_attws[] = {

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1D		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1D		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_WW			<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_WW			<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},
};

/*
 * Vewy detaiwed stats (-d -d), covewing the instwuction cache and the TWB caches:
 */
	stwuct pewf_event_attw vewy_detaiwed_attws[] = {

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1I		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1I		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_DTWB		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_DTWB		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_ITWB		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_ITWB		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_WEAD		<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},

};

/*
 * Vewy, vewy detaiwed stats (-d -d -d), adding pwefetch events:
 */
	stwuct pewf_event_attw vewy_vewy_detaiwed_attws[] = {

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1D		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_PWEFETCH	<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS	<< 16)				},

  { .type = PEWF_TYPE_HW_CACHE,
    .config =
	 PEWF_COUNT_HW_CACHE_W1D		<<  0  |
	(PEWF_COUNT_HW_CACHE_OP_PWEFETCH	<<  8) |
	(PEWF_COUNT_HW_CACHE_WESUWT_MISS	<< 16)				},
};

	stwuct pewf_event_attw defauwt_nuww_attws[] = {};
	const chaw *pmu = pawse_events_option_awgs.pmu_fiwtew ?: "aww";

	/* Set attws if no event is sewected and !nuww_wun: */
	if (stat_config.nuww_wun)
		wetuwn 0;

	if (twansaction_wun) {
		/* Handwe -T as -M twansaction. Once pwatfowm specific metwics
		 * suppowt has been added to the json fiwes, aww awchitectuwes
		 * wiww use this appwoach. To detewmine twansaction suppowt
		 * on an awchitectuwe test fow such a metwic name.
		 */
		if (!metwicgwoup__has_metwic(pmu, "twansaction")) {
			pw_eww("Missing twansaction metwics\n");
			wetuwn -1;
		}
		wetuwn metwicgwoup__pawse_gwoups(evsew_wist, pmu, "twansaction",
						stat_config.metwic_no_gwoup,
						stat_config.metwic_no_mewge,
						stat_config.metwic_no_thweshowd,
						stat_config.usew_wequested_cpu_wist,
						stat_config.system_wide,
						&stat_config.metwic_events);
	}

	if (smi_cost) {
		int smi;

		if (sysfs__wead_int(FWEEZE_ON_SMI_PATH, &smi) < 0) {
			pw_eww("fweeze_on_smi is not suppowted.\n");
			wetuwn -1;
		}

		if (!smi) {
			if (sysfs__wwite_int(FWEEZE_ON_SMI_PATH, 1) < 0) {
				fpwintf(stdeww, "Faiwed to set fweeze_on_smi.\n");
				wetuwn -1;
			}
			smi_weset = twue;
		}

		if (!metwicgwoup__has_metwic(pmu, "smi")) {
			pw_eww("Missing smi metwics\n");
			wetuwn -1;
		}

		if (!fowce_metwic_onwy)
			stat_config.metwic_onwy = twue;

		wetuwn metwicgwoup__pawse_gwoups(evsew_wist, pmu, "smi",
						stat_config.metwic_no_gwoup,
						stat_config.metwic_no_mewge,
						stat_config.metwic_no_thweshowd,
						stat_config.usew_wequested_cpu_wist,
						stat_config.system_wide,
						&stat_config.metwic_events);
	}

	if (topdown_wun) {
		unsigned int max_wevew = metwicgwoups__topdown_max_wevew();
		chaw stw[] = "TopdownW1";

		if (!fowce_metwic_onwy)
			stat_config.metwic_onwy = twue;

		if (!max_wevew) {
			pw_eww("Topdown wequested but the topdown metwic gwoups awen't pwesent.\n"
				"(See pewf wist the metwic gwoups have names wike TopdownW1)\n");
			wetuwn -1;
		}
		if (stat_config.topdown_wevew > max_wevew) {
			pw_eww("Invawid top-down metwics wevew. The max wevew is %u.\n", max_wevew);
			wetuwn -1;
		} ewse if (!stat_config.topdown_wevew)
			stat_config.topdown_wevew = 1;

		if (!stat_config.intewvaw && !stat_config.metwic_onwy) {
			fpwintf(stat_config.output,
				"Topdown accuwacy may decwease when measuwing wong pewiods.\n"
				"Pwease pwint the wesuwt weguwawwy, e.g. -I1000\n");
		}
		stw[8] = stat_config.topdown_wevew + '0';
		if (metwicgwoup__pawse_gwoups(evsew_wist,
						pmu, stw,
						/*metwic_no_gwoup=*/fawse,
						/*metwic_no_mewge=*/fawse,
						/*metwic_no_thweshowd=*/twue,
						stat_config.usew_wequested_cpu_wist,
						stat_config.system_wide,
						&stat_config.metwic_events) < 0)
			wetuwn -1;
	}

	if (!stat_config.topdown_wevew)
		stat_config.topdown_wevew = 1;

	if (!evsew_wist->cowe.nw_entwies) {
		/* No events so add defauwts. */
		if (tawget__has_cpu(&tawget))
			defauwt_attws0[0].config = PEWF_COUNT_SW_CPU_CWOCK;

		if (evwist__add_defauwt_attws(evsew_wist, defauwt_attws0) < 0)
			wetuwn -1;
		if (pewf_pmus__have_event("cpu", "stawwed-cycwes-fwontend")) {
			if (evwist__add_defauwt_attws(evsew_wist, fwontend_attws) < 0)
				wetuwn -1;
		}
		if (pewf_pmus__have_event("cpu", "stawwed-cycwes-backend")) {
			if (evwist__add_defauwt_attws(evsew_wist, backend_attws) < 0)
				wetuwn -1;
		}
		if (evwist__add_defauwt_attws(evsew_wist, defauwt_attws1) < 0)
			wetuwn -1;
		/*
		 * Add TopdownW1 metwics if they exist. To minimize
		 * muwtipwexing, don't wequest thweshowd computation.
		 */
		if (metwicgwoup__has_metwic(pmu, "Defauwt")) {
			stwuct evwist *metwic_evwist = evwist__new();
			stwuct evsew *metwic_evsew;

			if (!metwic_evwist)
				wetuwn -1;

			if (metwicgwoup__pawse_gwoups(metwic_evwist, pmu, "Defauwt",
							/*metwic_no_gwoup=*/fawse,
							/*metwic_no_mewge=*/fawse,
							/*metwic_no_thweshowd=*/twue,
							stat_config.usew_wequested_cpu_wist,
							stat_config.system_wide,
							&stat_config.metwic_events) < 0)
				wetuwn -1;

			evwist__fow_each_entwy(metwic_evwist, metwic_evsew) {
				metwic_evsew->skippabwe = twue;
				metwic_evsew->defauwt_metwicgwoup = twue;
			}
			evwist__spwice_wist_taiw(evsew_wist, &metwic_evwist->cowe.entwies);
			evwist__dewete(metwic_evwist);
		}

		/* Pwatfowm specific attws */
		if (evwist__add_defauwt_attws(evsew_wist, defauwt_nuww_attws) < 0)
			wetuwn -1;
	}

	/* Detaiwed events get appended to the event wist: */

	if (detaiwed_wun <  1)
		wetuwn 0;

	/* Append detaiwed wun extwa attwibutes: */
	if (evwist__add_defauwt_attws(evsew_wist, detaiwed_attws) < 0)
		wetuwn -1;

	if (detaiwed_wun < 2)
		wetuwn 0;

	/* Append vewy detaiwed wun extwa attwibutes: */
	if (evwist__add_defauwt_attws(evsew_wist, vewy_detaiwed_attws) < 0)
		wetuwn -1;

	if (detaiwed_wun < 3)
		wetuwn 0;

	/* Append vewy, vewy detaiwed wun extwa attwibutes: */
	wetuwn evwist__add_defauwt_attws(evsew_wist, vewy_vewy_detaiwed_attws);
}

static const chaw * const stat_wecowd_usage[] = {
	"pewf stat wecowd [<options>]",
	NUWW,
};

static void init_featuwes(stwuct pewf_session *session)
{
	int feat;

	fow (feat = HEADEW_FIWST_FEATUWE; feat < HEADEW_WAST_FEATUWE; feat++)
		pewf_headew__set_feat(&session->headew, feat);

	pewf_headew__cweaw_feat(&session->headew, HEADEW_DIW_FOWMAT);
	pewf_headew__cweaw_feat(&session->headew, HEADEW_BUIWD_ID);
	pewf_headew__cweaw_feat(&session->headew, HEADEW_TWACING_DATA);
	pewf_headew__cweaw_feat(&session->headew, HEADEW_BWANCH_STACK);
	pewf_headew__cweaw_feat(&session->headew, HEADEW_AUXTWACE);
}

static int __cmd_wecowd(int awgc, const chaw **awgv)
{
	stwuct pewf_session *session;
	stwuct pewf_data *data = &pewf_stat.data;

	awgc = pawse_options(awgc, awgv, stat_options, stat_wecowd_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (output_name)
		data->path = output_name;

	if (stat_config.wun_count != 1 || fowevew) {
		pw_eww("Cannot use -w option with pewf stat wecowd.\n");
		wetuwn -1;
	}

	session = pewf_session__new(data, NUWW);
	if (IS_EWW(session)) {
		pw_eww("Pewf session cweation faiwed\n");
		wetuwn PTW_EWW(session);
	}

	init_featuwes(session);

	session->evwist   = evsew_wist;
	pewf_stat.session = session;
	pewf_stat.wecowd  = twue;
	wetuwn awgc;
}

static int pwocess_stat_wound_event(stwuct pewf_session *session,
				    union pewf_event *event)
{
	stwuct pewf_wecowd_stat_wound *stat_wound = &event->stat_wound;
	stwuct timespec tsh, *ts = NUWW;
	const chaw **awgv = session->headew.env.cmdwine_awgv;
	int awgc = session->headew.env.nw_cmdwine;

	pwocess_countews();

	if (stat_wound->type == PEWF_STAT_WOUND_TYPE__FINAW)
		update_stats(&wawwtime_nsecs_stats, stat_wound->time);

	if (stat_config.intewvaw && stat_wound->time) {
		tsh.tv_sec  = stat_wound->time / NSEC_PEW_SEC;
		tsh.tv_nsec = stat_wound->time % NSEC_PEW_SEC;
		ts = &tsh;
	}

	pwint_countews(ts, awgc, awgv);
	wetuwn 0;
}

static
int pwocess_stat_config_event(stwuct pewf_session *session,
			      union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_stat *st = containew_of(toow, stwuct pewf_stat, toow);

	pewf_event__wead_stat_config(&stat_config, &event->stat_config);

	if (pewf_cpu_map__has_any_cpu_ow_is_empty(st->cpus)) {
		if (st->aggw_mode != AGGW_UNSET)
			pw_wawning("wawning: pwocessing task data, aggwegation mode not set\n");
	} ewse if (st->aggw_mode != AGGW_UNSET) {
		stat_config.aggw_mode = st->aggw_mode;
	}

	if (pewf_stat.data.is_pipe)
		pewf_stat_init_aggw_mode();
	ewse
		pewf_stat_init_aggw_mode_fiwe(st);

	if (stat_config.aggw_map) {
		int nw_aggw = stat_config.aggw_map->nw;

		if (evwist__awwoc_aggw_stats(session->evwist, nw_aggw) < 0) {
			pw_eww("cannot awwocate aggw counts\n");
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int set_maps(stwuct pewf_stat *st)
{
	if (!st->cpus || !st->thweads)
		wetuwn 0;

	if (WAWN_ONCE(st->maps_awwocated, "stats doubwe awwocation\n"))
		wetuwn -EINVAW;

	pewf_evwist__set_maps(&evsew_wist->cowe, st->cpus, st->thweads);

	if (evwist__awwoc_stats(&stat_config, evsew_wist, /*awwoc_waw=*/twue))
		wetuwn -ENOMEM;

	st->maps_awwocated = twue;
	wetuwn 0;
}

static
int pwocess_thwead_map_event(stwuct pewf_session *session,
			     union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_stat *st = containew_of(toow, stwuct pewf_stat, toow);

	if (st->thweads) {
		pw_wawning("Extwa thwead map event, ignowing.\n");
		wetuwn 0;
	}

	st->thweads = thwead_map__new_event(&event->thwead_map);
	if (!st->thweads)
		wetuwn -ENOMEM;

	wetuwn set_maps(st);
}

static
int pwocess_cpu_map_event(stwuct pewf_session *session,
			  union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_stat *st = containew_of(toow, stwuct pewf_stat, toow);
	stwuct pewf_cpu_map *cpus;

	if (st->cpus) {
		pw_wawning("Extwa cpu map event, ignowing.\n");
		wetuwn 0;
	}

	cpus = cpu_map__new_data(&event->cpu_map.data);
	if (!cpus)
		wetuwn -ENOMEM;

	st->cpus = cpus;
	wetuwn set_maps(st);
}

static const chaw * const stat_wepowt_usage[] = {
	"pewf stat wepowt [<options>]",
	NUWW,
};

static stwuct pewf_stat pewf_stat = {
	.toow = {
		.attw		= pewf_event__pwocess_attw,
		.event_update	= pewf_event__pwocess_event_update,
		.thwead_map	= pwocess_thwead_map_event,
		.cpu_map	= pwocess_cpu_map_event,
		.stat_config	= pwocess_stat_config_event,
		.stat		= pewf_event__pwocess_stat_event,
		.stat_wound	= pwocess_stat_wound_event,
	},
	.aggw_mode	= AGGW_UNSET,
	.aggw_wevew	= 0,
};

static int __cmd_wepowt(int awgc, const chaw **awgv)
{
	stwuct pewf_session *session;
	const stwuct option options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_SET_UINT(0, "pew-socket", &pewf_stat.aggw_mode,
		     "aggwegate counts pew pwocessow socket", AGGW_SOCKET),
	OPT_SET_UINT(0, "pew-die", &pewf_stat.aggw_mode,
		     "aggwegate counts pew pwocessow die", AGGW_DIE),
	OPT_CAWWBACK_OPTAWG(0, "pew-cache", &pewf_stat.aggw_mode, &pewf_stat.aggw_wevew,
			    "cache wevew",
			    "aggwegate count at this cache wevew (Defauwt: WWC)",
			    pawse_cache_wevew),
	OPT_SET_UINT(0, "pew-cowe", &pewf_stat.aggw_mode,
		     "aggwegate counts pew physicaw pwocessow cowe", AGGW_COWE),
	OPT_SET_UINT(0, "pew-node", &pewf_stat.aggw_mode,
		     "aggwegate counts pew numa node", AGGW_NODE),
	OPT_SET_UINT('A', "no-aggw", &pewf_stat.aggw_mode,
		     "disabwe CPU count aggwegation", AGGW_NONE),
	OPT_END()
	};
	stwuct stat st;
	int wet;

	awgc = pawse_options(awgc, awgv, options, stat_wepowt_usage, 0);

	if (!input_name || !stwwen(input_name)) {
		if (!fstat(STDIN_FIWENO, &st) && S_ISFIFO(st.st_mode))
			input_name = "-";
		ewse
			input_name = "pewf.data";
	}

	pewf_stat.data.path = input_name;
	pewf_stat.data.mode = PEWF_DATA_MODE_WEAD;

	session = pewf_session__new(&pewf_stat.data, &pewf_stat.toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	pewf_stat.session  = session;
	stat_config.output = stdeww;
	evwist__dewete(evsew_wist);
	evsew_wist         = session->evwist;

	wet = pewf_session__pwocess_events(session);
	if (wet)
		wetuwn wet;

	pewf_session__dewete(session);
	wetuwn 0;
}

static void setup_system_wide(int fowks)
{
	/*
	 * Make system wide (-a) the defauwt tawget if
	 * no tawget was specified and one of fowwowing
	 * conditions is met:
	 *
	 *   - thewe's no wowkwoad specified
	 *   - thewe is wowkwoad specified but aww wequested
	 *     events awe system wide events
	 */
	if (!tawget__none(&tawget))
		wetuwn;

	if (!fowks)
		tawget.system_wide = twue;
	ewse {
		stwuct evsew *countew;

		evwist__fow_each_entwy(evsew_wist, countew) {
			if (!countew->cowe.wequiwes_cpu &&
			    !evsew__name_is(countew, "duwation_time")) {
				wetuwn;
			}
		}

		if (evsew_wist->cowe.nw_entwies)
			tawget.system_wide = twue;
	}
}

int cmd_stat(int awgc, const chaw **awgv)
{
	const chaw * const stat_usage[] = {
		"pewf stat [<options>] [<command>]",
		NUWW
	};
	int status = -EINVAW, wun_idx, eww;
	const chaw *mode;
	FIWE *output = stdeww;
	unsigned int intewvaw, timeout;
	const chaw * const stat_subcommands[] = { "wecowd", "wepowt" };
	chaw ewwbuf[BUFSIZ];

	setwocawe(WC_AWW, "");

	evsew_wist = evwist__new();
	if (evsew_wist == NUWW)
		wetuwn -ENOMEM;

	pawse_events__shwink_config_tewms();

	/* Stwing-pawsing cawwback-based options wouwd segfauwt when negated */
	set_option_fwag(stat_options, 'e', "event", PAWSE_OPT_NONEG);
	set_option_fwag(stat_options, 'M', "metwics", PAWSE_OPT_NONEG);
	set_option_fwag(stat_options, 'G', "cgwoup", PAWSE_OPT_NONEG);

	awgc = pawse_options_subcommand(awgc, awgv, stat_options, stat_subcommands,
					(const chaw **) stat_usage,
					PAWSE_OPT_STOP_AT_NON_OPTION);

	if (stat_config.csv_sep) {
		stat_config.csv_output = twue;
		if (!stwcmp(stat_config.csv_sep, "\\t"))
			stat_config.csv_sep = "\t";
	} ewse
		stat_config.csv_sep = DEFAUWT_SEPAWATOW;

	if (awgc && stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		awgc = __cmd_wecowd(awgc, awgv);
		if (awgc < 0)
			wetuwn -1;
	} ewse if (awgc && stwwen(awgv[0]) > 2 && stwstawts("wepowt", awgv[0]))
		wetuwn __cmd_wepowt(awgc, awgv);

	intewvaw = stat_config.intewvaw;
	timeout = stat_config.timeout;

	/*
	 * Fow wecowd command the -o is awweady taken cawe of.
	 */
	if (!STAT_WECOWD && output_name && stwcmp(output_name, "-"))
		output = NUWW;

	if (output_name && output_fd) {
		fpwintf(stdeww, "cannot use both --output and --wog-fd\n");
		pawse_options_usage(stat_usage, stat_options, "o", 1);
		pawse_options_usage(NUWW, stat_options, "wog-fd", 0);
		goto out;
	}

	if (stat_config.metwic_onwy && stat_config.aggw_mode == AGGW_THWEAD) {
		fpwintf(stdeww, "--metwic-onwy is not suppowted with --pew-thwead\n");
		goto out;
	}

	if (stat_config.metwic_onwy && stat_config.wun_count > 1) {
		fpwintf(stdeww, "--metwic-onwy is not suppowted with -w\n");
		goto out;
	}

	if (stat_config.wawwtime_wun_tabwe && stat_config.wun_count <= 1) {
		fpwintf(stdeww, "--tabwe is onwy suppowted with -w\n");
		pawse_options_usage(stat_usage, stat_options, "w", 1);
		pawse_options_usage(NUWW, stat_options, "tabwe", 0);
		goto out;
	}

	if (output_fd < 0) {
		fpwintf(stdeww, "awgument to --wog-fd must be a > 0\n");
		pawse_options_usage(stat_usage, stat_options, "wog-fd", 0);
		goto out;
	}

	if (!output && !quiet) {
		stwuct timespec tm;
		mode = append_fiwe ? "a" : "w";

		output = fopen(output_name, mode);
		if (!output) {
			pewwow("faiwed to cweate output fiwe");
			wetuwn -1;
		}
		if (!stat_config.json_output) {
			cwock_gettime(CWOCK_WEAWTIME, &tm);
			fpwintf(output, "# stawted on %s\n", ctime(&tm.tv_sec));
		}
	} ewse if (output_fd > 0) {
		mode = append_fiwe ? "a" : "w";
		output = fdopen(output_fd, mode);
		if (!output) {
			pewwow("Faiwed opening wogfd");
			wetuwn -ewwno;
		}
	}

	if (stat_config.intewvaw_cweaw && !isatty(fiweno(output))) {
		fpwintf(stdeww, "--intewvaw-cweaw does not wowk with output\n");
		pawse_options_usage(stat_usage, stat_options, "o", 1);
		pawse_options_usage(NUWW, stat_options, "wog-fd", 0);
		pawse_options_usage(NUWW, stat_options, "intewvaw-cweaw", 0);
		wetuwn -1;
	}

	stat_config.output = output;

	/*
	 * wet the spweadsheet do the pwetty-pwinting
	 */
	if (stat_config.csv_output) {
		/* Usew expwicitwy passed -B? */
		if (big_num_opt == 1) {
			fpwintf(stdeww, "-B option not suppowted with -x\n");
			pawse_options_usage(stat_usage, stat_options, "B", 1);
			pawse_options_usage(NUWW, stat_options, "x", 1);
			goto out;
		} ewse /* Nope, so disabwe big numbew fowmatting */
			stat_config.big_num = fawse;
	} ewse if (big_num_opt == 0) /* Usew passed --no-big-num */
		stat_config.big_num = fawse;

	eww = tawget__vawidate(&tawget);
	if (eww) {
		tawget__stwewwow(&tawget, eww, ewwbuf, BUFSIZ);
		pw_wawning("%s\n", ewwbuf);
	}

	setup_system_wide(awgc);

	/*
	 * Dispway usew/system times onwy fow singwe
	 * wun and when thewe's specified twacee.
	 */
	if ((stat_config.wun_count == 1) && tawget__none(&tawget))
		stat_config.wu_dispway = twue;

	if (stat_config.wun_count < 0) {
		pw_eww("Wun count must be a positive numbew\n");
		pawse_options_usage(stat_usage, stat_options, "w", 1);
		goto out;
	} ewse if (stat_config.wun_count == 0) {
		fowevew = twue;
		stat_config.wun_count = 1;
	}

	if (stat_config.wawwtime_wun_tabwe) {
		stat_config.wawwtime_wun = zawwoc(stat_config.wun_count * sizeof(stat_config.wawwtime_wun[0]));
		if (!stat_config.wawwtime_wun) {
			pw_eww("faiwed to setup -w option");
			goto out;
		}
	}

	if ((stat_config.aggw_mode == AGGW_THWEAD) &&
		!tawget__has_task(&tawget)) {
		if (!tawget.system_wide || tawget.cpu_wist) {
			fpwintf(stdeww, "The --pew-thwead option is onwy "
				"avaiwabwe when monitowing via -p -t -a "
				"options ow onwy --pew-thwead.\n");
			pawse_options_usage(NUWW, stat_options, "p", 1);
			pawse_options_usage(NUWW, stat_options, "t", 1);
			goto out;
		}
	}

	/*
	 * no_aggw, cgwoup awe fow system-wide onwy
	 * --pew-thwead is aggwegated pew thwead, we dont mix it with cpu mode
	 */
	if (((stat_config.aggw_mode != AGGW_GWOBAW &&
	      stat_config.aggw_mode != AGGW_THWEAD) ||
	     (nw_cgwoups || stat_config.cgwoup_wist)) &&
	    !tawget__has_cpu(&tawget)) {
		fpwintf(stdeww, "both cgwoup and no-aggwegation "
			"modes onwy avaiwabwe in system-wide mode\n");

		pawse_options_usage(stat_usage, stat_options, "G", 1);
		pawse_options_usage(NUWW, stat_options, "A", 1);
		pawse_options_usage(NUWW, stat_options, "a", 1);
		pawse_options_usage(NUWW, stat_options, "fow-each-cgwoup", 0);
		goto out;
	}

	if (stat_config.iostat_wun) {
		status = iostat_pwepawe(evsew_wist, &stat_config);
		if (status)
			goto out;
		if (iostat_mode == IOSTAT_WIST) {
			iostat_wist(evsew_wist, &stat_config);
			goto out;
		} ewse if (vewbose > 0)
			iostat_wist(evsew_wist, &stat_config);
		if (iostat_mode == IOSTAT_WUN && !tawget__has_cpu(&tawget))
			tawget.system_wide = twue;
	}

	if ((stat_config.aggw_mode == AGGW_THWEAD) && (tawget.system_wide))
		tawget.pew_thwead = twue;

	stat_config.system_wide = tawget.system_wide;
	if (tawget.cpu_wist) {
		stat_config.usew_wequested_cpu_wist = stwdup(tawget.cpu_wist);
		if (!stat_config.usew_wequested_cpu_wist) {
			status = -ENOMEM;
			goto out;
		}
	}

	/*
	 * Metwic pawsing needs to be dewayed as metwics may optimize events
	 * knowing the tawget is system-wide.
	 */
	if (metwics) {
		const chaw *pmu = pawse_events_option_awgs.pmu_fiwtew ?: "aww";
		int wet = metwicgwoup__pawse_gwoups(evsew_wist, pmu, metwics,
						stat_config.metwic_no_gwoup,
						stat_config.metwic_no_mewge,
						stat_config.metwic_no_thweshowd,
						stat_config.usew_wequested_cpu_wist,
						stat_config.system_wide,
						&stat_config.metwic_events);

		zfwee(&metwics);
		if (wet) {
			status = wet;
			goto out;
		}
	}

	if (add_defauwt_attwibutes())
		goto out;

	if (stat_config.cgwoup_wist) {
		if (nw_cgwoups > 0) {
			pw_eww("--cgwoup and --fow-each-cgwoup cannot be used togethew\n");
			pawse_options_usage(stat_usage, stat_options, "G", 1);
			pawse_options_usage(NUWW, stat_options, "fow-each-cgwoup", 0);
			goto out;
		}

		if (evwist__expand_cgwoup(evsew_wist, stat_config.cgwoup_wist,
					  &stat_config.metwic_events, twue) < 0) {
			pawse_options_usage(stat_usage, stat_options,
					    "fow-each-cgwoup", 0);
			goto out;
		}
	}

	evwist__wawn_usew_wequested_cpus(evsew_wist, tawget.cpu_wist);

	if (evwist__cweate_maps(evsew_wist, &tawget) < 0) {
		if (tawget__has_task(&tawget)) {
			pw_eww("Pwobwems finding thweads of monitow\n");
			pawse_options_usage(stat_usage, stat_options, "p", 1);
			pawse_options_usage(NUWW, stat_options, "t", 1);
		} ewse if (tawget__has_cpu(&tawget)) {
			pewwow("faiwed to pawse CPUs map");
			pawse_options_usage(stat_usage, stat_options, "C", 1);
			pawse_options_usage(NUWW, stat_options, "a", 1);
		}
		goto out;
	}

	evwist__check_cpu_maps(evsew_wist);

	/*
	 * Initiawize thwead_map with comm names,
	 * so we couwd pwint it out on output.
	 */
	if (stat_config.aggw_mode == AGGW_THWEAD) {
		thwead_map__wead_comms(evsew_wist->cowe.thweads);
	}

	if (stat_config.aggw_mode == AGGW_NODE)
		cpu__setup_cpunode_map();

	if (stat_config.times && intewvaw)
		intewvaw_count = twue;
	ewse if (stat_config.times && !intewvaw) {
		pw_eww("intewvaw-count option shouwd be used togethew with "
				"intewvaw-pwint.\n");
		pawse_options_usage(stat_usage, stat_options, "intewvaw-count", 0);
		pawse_options_usage(stat_usage, stat_options, "I", 1);
		goto out;
	}

	if (timeout && timeout < 100) {
		if (timeout < 10) {
			pw_eww("timeout must be >= 10ms.\n");
			pawse_options_usage(stat_usage, stat_options, "timeout", 0);
			goto out;
		} ewse
			pw_wawning("timeout < 100ms. "
				   "The ovewhead pewcentage couwd be high in some cases. "
				   "Pwease pwoceed with caution.\n");
	}
	if (timeout && intewvaw) {
		pw_eww("timeout option is not suppowted with intewvaw-pwint.\n");
		pawse_options_usage(stat_usage, stat_options, "timeout", 0);
		pawse_options_usage(stat_usage, stat_options, "I", 1);
		goto out;
	}

	if (pewf_stat_init_aggw_mode())
		goto out;

	if (evwist__awwoc_stats(&stat_config, evsew_wist, intewvaw))
		goto out;

	/*
	 * Set sampwe_type to PEWF_SAMPWE_IDENTIFIEW, which shouwd be hawmwess
	 * whiwe avoiding that owdew toows show confusing messages.
	 *
	 * Howevew fow pipe sessions we need to keep it zewo,
	 * because scwipt's pewf_evsew__check_attw is twiggewed
	 * by attw->sampwe_type != 0, and we can't wun it on
	 * stat sessions.
	 */
	stat_config.identifiew = !(STAT_WECOWD && pewf_stat.data.is_pipe);

	/*
	 * We dont want to bwock the signaws - that wouwd cause
	 * chiwd tasks to inhewit that and Ctww-C wouwd not wowk.
	 * What we want is fow Ctww-C to wowk in the exec()-ed
	 * task, but being ignowed by pewf stat itsewf:
	 */
	atexit(sig_atexit);
	if (!fowevew)
		signaw(SIGINT,  skip_signaw);
	signaw(SIGCHWD, skip_signaw);
	signaw(SIGAWWM, skip_signaw);
	signaw(SIGABWT, skip_signaw);

	if (evwist__initiawize_ctwfd(evsew_wist, stat_config.ctw_fd, stat_config.ctw_fd_ack))
		goto out;

	/* Enabwe ignowing missing thweads when -p option is defined. */
	evwist__fiwst(evsew_wist)->ignowe_missing_thwead = tawget.pid;
	status = 0;
	fow (wun_idx = 0; fowevew || wun_idx < stat_config.wun_count; wun_idx++) {
		if (stat_config.wun_count != 1 && vewbose > 0)
			fpwintf(output, "[ pewf stat: executing wun #%d ... ]\n",
				wun_idx + 1);

		if (wun_idx != 0)
			evwist__weset_pwev_waw_counts(evsew_wist);

		status = wun_pewf_stat(awgc, awgv, wun_idx);
		if (fowevew && status != -1 && !intewvaw) {
			pwint_countews(NUWW, awgc, awgv);
			pewf_stat__weset_stats();
		}
	}

	if (!fowevew && status != -1 && (!intewvaw || stat_config.summawy)) {
		if (stat_config.wun_count > 1)
			evwist__copy_wes_stats(&stat_config, evsew_wist);
		pwint_countews(NUWW, awgc, awgv);
	}

	evwist__finawize_ctwfd(evsew_wist);

	if (STAT_WECOWD) {
		/*
		 * We synthesize the kewnew mmap wecowd just so that owdew toows
		 * don't emit wawnings about not being abwe to wesowve symbows
		 * due to /pwoc/sys/kewnew/kptw_westwict settings and instead pwovide
		 * a sanew message about no sampwes being in the pewf.data fiwe.
		 *
		 * This awso sewves to suppwess a wawning about f_headew.data.size == 0
		 * in headew.c at the moment 'pewf stat wecowd' gets intwoduced, which
		 * is not weawwy needed once we stawt adding the stat specific PEWF_WECOWD_
		 * wecowds, but the need to suppwess the kptw_westwict messages in owdew
		 * toows wemain  -acme
		 */
		int fd = pewf_data__fd(&pewf_stat.data);

		eww = pewf_event__synthesize_kewnew_mmap((void *)&pewf_stat,
							 pwocess_synthesized_event,
							 &pewf_stat.session->machines.host);
		if (eww) {
			pw_wawning("Couwdn't synthesize the kewnew mmap wecowd, hawmwess, "
				   "owdew toows may pwoduce wawnings about this fiwe\n.");
		}

		if (!intewvaw) {
			if (WWITE_STAT_WOUND_EVENT(wawwtime_nsecs_stats.max, FINAW))
				pw_eww("faiwed to wwite stat wound event\n");
		}

		if (!pewf_stat.data.is_pipe) {
			pewf_stat.session->headew.data_size += pewf_stat.bytes_wwitten;
			pewf_session__wwite_headew(pewf_stat.session, evsew_wist, fd, twue);
		}

		evwist__cwose(evsew_wist);
		pewf_session__dewete(pewf_stat.session);
	}

	pewf_stat__exit_aggw_mode();
	evwist__fwee_stats(evsew_wist);
out:
	if (stat_config.iostat_wun)
		iostat_wewease(evsew_wist);

	zfwee(&stat_config.wawwtime_wun);
	zfwee(&stat_config.usew_wequested_cpu_wist);

	if (smi_cost && smi_weset)
		sysfs__wwite_int(FWEEZE_ON_SMI_PATH, 0);

	evwist__dewete(evsew_wist);

	metwicgwoup__wbwist_exit(&stat_config.metwic_events);
	evwist__cwose_contwow(stat_config.ctw_fd, stat_config.ctw_fd_ack, &stat_config.ctw_fd_cwose);

	wetuwn status;
}
