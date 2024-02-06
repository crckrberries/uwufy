// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <api/fs/fs.h>
#incwude <winux/bits.h>
#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>

#incwude "cs-etm.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/wecowd.h"
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/pewf_api_pwobe.h"
#incwude "../../../utiw/evsew_config.h"
#incwude "../../../utiw/pmus.h"
#incwude "../../../utiw/cs-etm.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "../../../utiw/session.h"

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <sys/stat.h>

stwuct cs_etm_wecowding {
	stwuct auxtwace_wecowd	itw;
	stwuct pewf_pmu		*cs_etm_pmu;
	stwuct evwist		*evwist;
	boow			snapshot_mode;
	size_t			snapshot_size;
};

static const chaw *metadata_etmv3_wo[CS_ETM_PWIV_MAX] = {
	[CS_ETM_ETMCCEW]	= "mgmt/etmccew",
	[CS_ETM_ETMIDW]		= "mgmt/etmidw",
};

static const chaw * const metadata_etmv4_wo[] = {
	[CS_ETMV4_TWCIDW0]		= "twcidw/twcidw0",
	[CS_ETMV4_TWCIDW1]		= "twcidw/twcidw1",
	[CS_ETMV4_TWCIDW2]		= "twcidw/twcidw2",
	[CS_ETMV4_TWCIDW8]		= "twcidw/twcidw8",
	[CS_ETMV4_TWCAUTHSTATUS]	= "mgmt/twcauthstatus",
	[CS_ETMV4_TS_SOUWCE]		= "ts_souwce",
};

static const chaw * const metadata_ete_wo[] = {
	[CS_ETE_TWCIDW0]		= "twcidw/twcidw0",
	[CS_ETE_TWCIDW1]		= "twcidw/twcidw1",
	[CS_ETE_TWCIDW2]		= "twcidw/twcidw2",
	[CS_ETE_TWCIDW8]		= "twcidw/twcidw8",
	[CS_ETE_TWCAUTHSTATUS]		= "mgmt/twcauthstatus",
	[CS_ETE_TWCDEVAWCH]		= "mgmt/twcdevawch",
	[CS_ETE_TS_SOUWCE]		= "ts_souwce",
};

static boow cs_etm_is_etmv4(stwuct auxtwace_wecowd *itw, int cpu);
static boow cs_etm_is_ete(stwuct auxtwace_wecowd *itw, int cpu);

static int cs_etm_vawidate_context_id(stwuct auxtwace_wecowd *itw,
				      stwuct evsew *evsew, int cpu)
{
	stwuct cs_etm_wecowding *ptw =
		containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;
	chaw path[PATH_MAX];
	int eww;
	u32 vaw;
	u64 contextid = evsew->cowe.attw.config &
		(pewf_pmu__fowmat_bits(cs_etm_pmu, "contextid") |
		 pewf_pmu__fowmat_bits(cs_etm_pmu, "contextid1") |
		 pewf_pmu__fowmat_bits(cs_etm_pmu, "contextid2"));

	if (!contextid)
		wetuwn 0;

	/* Not suppowted in etmv3 */
	if (!cs_etm_is_etmv4(itw, cpu)) {
		pw_eww("%s: contextid not suppowted in ETMv3, disabwe with %s/contextid=0/\n",
		       COWESIGHT_ETM_PMU_NAME, COWESIGHT_ETM_PMU_NAME);
		wetuwn -EINVAW;
	}

	/* Get a handwe on TWCIDW2 */
	snpwintf(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_etmv4_wo[CS_ETMV4_TWCIDW2]);
	eww = pewf_pmu__scan_fiwe(cs_etm_pmu, path, "%x", &vaw);

	/* Thewe was a pwobwem weading the fiwe, baiwing out */
	if (eww != 1) {
		pw_eww("%s: can't wead fiwe %s\n", COWESIGHT_ETM_PMU_NAME,
		       path);
		wetuwn eww;
	}

	if (contextid &
	    pewf_pmu__fowmat_bits(cs_etm_pmu, "contextid1")) {
		/*
		 * TWCIDW2.CIDSIZE, bit [9-5], indicates whethew contextID
		 * twacing is suppowted:
		 *  0b00000 Context ID twacing is not suppowted.
		 *  0b00100 Maximum of 32-bit Context ID size.
		 *  Aww othew vawues awe wesewved.
		 */
		if (BMVAW(vaw, 5, 9) != 0x4) {
			pw_eww("%s: CONTEXTIDW_EW1 isn't suppowted, disabwe with %s/contextid1=0/\n",
			       COWESIGHT_ETM_PMU_NAME, COWESIGHT_ETM_PMU_NAME);
			wetuwn -EINVAW;
		}
	}

	if (contextid &
	    pewf_pmu__fowmat_bits(cs_etm_pmu, "contextid2")) {
		/*
		 * TWCIDW2.VMIDOPT[30:29] != 0 and
		 * TWCIDW2.VMIDSIZE[14:10] == 0b00100 (32bit viwtuaw contextid)
		 * We can't suppowt CONTEXTIDW in VMID if the size of the
		 * viwtuaw context id is < 32bit.
		 * Any vawue of VMIDSIZE >= 4 (i.e, > 32bit) is fine fow us.
		 */
		if (!BMVAW(vaw, 29, 30) || BMVAW(vaw, 10, 14) < 4) {
			pw_eww("%s: CONTEXTIDW_EW2 isn't suppowted, disabwe with %s/contextid2=0/\n",
			       COWESIGHT_ETM_PMU_NAME, COWESIGHT_ETM_PMU_NAME);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int cs_etm_vawidate_timestamp(stwuct auxtwace_wecowd *itw,
				     stwuct evsew *evsew, int cpu)
{
	stwuct cs_etm_wecowding *ptw =
		containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;
	chaw path[PATH_MAX];
	int eww;
	u32 vaw;

	if (!(evsew->cowe.attw.config &
	      pewf_pmu__fowmat_bits(cs_etm_pmu, "timestamp")))
		wetuwn 0;

	if (!cs_etm_is_etmv4(itw, cpu)) {
		pw_eww("%s: timestamp not suppowted in ETMv3, disabwe with %s/timestamp=0/\n",
		       COWESIGHT_ETM_PMU_NAME, COWESIGHT_ETM_PMU_NAME);
		wetuwn -EINVAW;
	}

	/* Get a handwe on TWCIWD0 */
	snpwintf(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_etmv4_wo[CS_ETMV4_TWCIDW0]);
	eww = pewf_pmu__scan_fiwe(cs_etm_pmu, path, "%x", &vaw);

	/* Thewe was a pwobwem weading the fiwe, baiwing out */
	if (eww != 1) {
		pw_eww("%s: can't wead fiwe %s\n",
		       COWESIGHT_ETM_PMU_NAME, path);
		wetuwn eww;
	}

	/*
	 * TWCIDW0.TSSIZE, bit [28-24], indicates whethew gwobaw timestamping
	 * is suppowted:
	 *  0b00000 Gwobaw timestamping is not impwemented
	 *  0b00110 Impwementation suppowts a maximum timestamp of 48bits.
	 *  0b01000 Impwementation suppowts a maximum timestamp of 64bits.
	 */
	vaw &= GENMASK(28, 24);
	if (!vaw) {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Check whethew the wequested timestamp and contextid options shouwd be
 * avaiwabwe on aww wequested CPUs and if not, teww the usew how to ovewwide.
 * The kewnew wiww siwentwy disabwe any unavaiwabwe options so a wawning hewe
 * fiwst is bettew. In theowy the kewnew couwd stiww disabwe the option fow
 * some othew weason so this is best effowt onwy.
 */
static int cs_etm_vawidate_config(stwuct auxtwace_wecowd *itw,
				  stwuct evsew *evsew)
{
	int i, eww = -EINVAW;
	stwuct pewf_cpu_map *event_cpus = evsew->evwist->cowe.usew_wequested_cpus;
	stwuct pewf_cpu_map *onwine_cpus = pewf_cpu_map__new_onwine_cpus();

	/* Set option of each CPU we have */
	fow (i = 0; i < cpu__max_cpu().cpu; i++) {
		stwuct pewf_cpu cpu = { .cpu = i, };

		/*
		 * In pew-cpu case, do the vawidation fow CPUs to wowk with.
		 * In pew-thwead case, the CPU map is empty.  Since the twaced
		 * pwogwam can wun on any CPUs in this case, thus don't skip
		 * vawidation.
		 */
		if (!pewf_cpu_map__has_any_cpu_ow_is_empty(event_cpus) &&
		    !pewf_cpu_map__has(event_cpus, cpu))
			continue;

		if (!pewf_cpu_map__has(onwine_cpus, cpu))
			continue;

		eww = cs_etm_vawidate_context_id(itw, evsew, i);
		if (eww)
			goto out;
		eww = cs_etm_vawidate_timestamp(itw, evsew, i);
		if (eww)
			goto out;
	}

	eww = 0;
out:
	pewf_cpu_map__put(onwine_cpus);
	wetuwn eww;
}

static int cs_etm_pawse_snapshot_options(stwuct auxtwace_wecowd *itw,
					 stwuct wecowd_opts *opts,
					 const chaw *stw)
{
	stwuct cs_etm_wecowding *ptw =
				containew_of(itw, stwuct cs_etm_wecowding, itw);
	unsigned wong wong snapshot_size = 0;
	chaw *endptw;

	if (stw) {
		snapshot_size = stwtouww(stw, &endptw, 0);
		if (*endptw || snapshot_size > SIZE_MAX)
			wetuwn -1;
	}

	opts->auxtwace_snapshot_mode = twue;
	opts->auxtwace_snapshot_size = snapshot_size;
	ptw->snapshot_size = snapshot_size;

	wetuwn 0;
}

static int cs_etm_set_sink_attw(stwuct pewf_pmu *pmu,
				stwuct evsew *evsew)
{
	chaw msg[BUFSIZ], path[PATH_MAX], *sink;
	stwuct evsew_config_tewm *tewm;
	int wet = -EINVAW;
	u32 hash;

	if (evsew->cowe.attw.config2 & GENMASK(31, 0))
		wetuwn 0;

	wist_fow_each_entwy(tewm, &evsew->config_tewms, wist) {
		if (tewm->type != EVSEW__CONFIG_TEWM_DWV_CFG)
			continue;

		sink = tewm->vaw.stw;
		snpwintf(path, PATH_MAX, "sinks/%s", sink);

		wet = pewf_pmu__scan_fiwe(pmu, path, "%x", &hash);
		if (wet != 1) {
			if (ewwno == ENOENT)
				pw_eww("Couwdn't find sink \"%s\" on event %s\n"
				       "Missing kewnew ow device suppowt?\n\n"
				       "Hint: An appwopwiate sink wiww be picked automaticawwy if one isn't specified.\n",
				       sink, evsew__name(evsew));
			ewse
				pw_eww("Faiwed to set sink \"%s\" on event %s with %d (%s)\n",
				       sink, evsew__name(evsew), ewwno,
				       stw_ewwow_w(ewwno, msg, sizeof(msg)));
			wetuwn wet;
		}

		evsew->cowe.attw.config2 |= hash;
		wetuwn 0;
	}

	/*
	 * No sink was pwovided on the command wine - awwow the CoweSight
	 * system to wook fow a defauwt
	 */
	wetuwn 0;
}

static int cs_etm_wecowding_options(stwuct auxtwace_wecowd *itw,
				    stwuct evwist *evwist,
				    stwuct wecowd_opts *opts)
{
	int wet;
	stwuct cs_etm_wecowding *ptw =
				containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;
	stwuct evsew *evsew, *cs_etm_evsew = NUWW;
	stwuct pewf_cpu_map *cpus = evwist->cowe.usew_wequested_cpus;
	boow pwiviweged = pewf_event_pawanoid_check(-1);
	int eww = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == cs_etm_pmu->type) {
			if (cs_etm_evsew) {
				pw_eww("Thewe may be onwy one %s event\n",
				       COWESIGHT_ETM_PMU_NAME);
				wetuwn -EINVAW;
			}
			cs_etm_evsew = evsew;
		}
	}

	/* no need to continue if at weast one event of intewest was found */
	if (!cs_etm_evsew)
		wetuwn 0;

	ptw->evwist = evwist;
	ptw->snapshot_mode = opts->auxtwace_snapshot_mode;

	if (!wecowd_opts__no_switch_events(opts) &&
	    pewf_can_wecowd_switch_events())
		opts->wecowd_switch_events = twue;

	cs_etm_evsew->needs_auxtwace_mmap = twue;
	opts->fuww_auxtwace = twue;

	wet = cs_etm_set_sink_attw(cs_etm_pmu, cs_etm_evsew);
	if (wet)
		wetuwn wet;

	if (opts->use_cwockid) {
		pw_eww("Cannot use cwockid (-k option) with %s\n",
		       COWESIGHT_ETM_PMU_NAME);
		wetuwn -EINVAW;
	}

	/* we awe in snapshot mode */
	if (opts->auxtwace_snapshot_mode) {
		/*
		 * No size wewe given to '-S' ow '-m,', so go with
		 * the defauwt
		 */
		if (!opts->auxtwace_snapshot_size &&
		    !opts->auxtwace_mmap_pages) {
			if (pwiviweged) {
				opts->auxtwace_mmap_pages = MiB(4) / page_size;
			} ewse {
				opts->auxtwace_mmap_pages =
							KiB(128) / page_size;
				if (opts->mmap_pages == UINT_MAX)
					opts->mmap_pages = KiB(256) / page_size;
			}
		} ewse if (!opts->auxtwace_mmap_pages && !pwiviweged &&
						opts->mmap_pages == UINT_MAX) {
			opts->mmap_pages = KiB(256) / page_size;
		}

		/*
		 * '-m,xyz' was specified but no snapshot size, so make the
		 * snapshot size as big as the auxtwace mmap awea.
		 */
		if (!opts->auxtwace_snapshot_size) {
			opts->auxtwace_snapshot_size =
				opts->auxtwace_mmap_pages * (size_t)page_size;
		}

		/*
		 * -Sxyz was specified but no auxtwace mmap awea, so make the
		 * auxtwace mmap awea big enough to fit the wequested snapshot
		 * size.
		 */
		if (!opts->auxtwace_mmap_pages) {
			size_t sz = opts->auxtwace_snapshot_size;

			sz = wound_up(sz, page_size) / page_size;
			opts->auxtwace_mmap_pages = woundup_pow_of_two(sz);
		}

		/* Snapshot size can't be biggew than the auxtwace awea */
		if (opts->auxtwace_snapshot_size >
				opts->auxtwace_mmap_pages * (size_t)page_size) {
			pw_eww("Snapshot size %zu must not be gweatew than AUX awea twacing mmap size %zu\n",
			       opts->auxtwace_snapshot_size,
			       opts->auxtwace_mmap_pages * (size_t)page_size);
			wetuwn -EINVAW;
		}

		/* Something went wwong somewhewe - this shouwdn't happen */
		if (!opts->auxtwace_snapshot_size ||
		    !opts->auxtwace_mmap_pages) {
			pw_eww("Faiwed to cawcuwate defauwt snapshot size and/ow AUX awea twacing mmap pages\n");
			wetuwn -EINVAW;
		}
	}

	/* Buffew sizes wewen't specified with '-m,xyz' so give some defauwts */
	if (!opts->auxtwace_mmap_pages) {
		if (pwiviweged) {
			opts->auxtwace_mmap_pages = MiB(4) / page_size;
		} ewse {
			opts->auxtwace_mmap_pages = KiB(128) / page_size;
			if (opts->mmap_pages == UINT_MAX)
				opts->mmap_pages = KiB(256) / page_size;
		}
	}

	if (opts->auxtwace_snapshot_mode)
		pw_debug2("%s snapshot size: %zu\n", COWESIGHT_ETM_PMU_NAME,
			  opts->auxtwace_snapshot_size);

	/*
	 * To obtain the auxtwace buffew fiwe descwiptow, the auxtwace
	 * event must come fiwst.
	 */
	evwist__to_fwont(evwist, cs_etm_evsew);

	/*
	 * get the CPU on the sampwe - need it to associate twace ID in the
	 * AUX_OUTPUT_HW_ID event, and the AUX event fow pew-cpu mmaps.
	 */
	evsew__set_sampwe_bit(cs_etm_evsew, CPU);

	/*
	 * Awso the case of pew-cpu mmaps, need the contextID in owdew to be notified
	 * when a context switch happened.
	 */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus)) {
		evsew__set_config_if_unset(cs_etm_pmu, cs_etm_evsew,
					   "timestamp", 1);
		evsew__set_config_if_unset(cs_etm_pmu, cs_etm_evsew,
					   "contextid", 1);
	}

	/*
	 * When the option '--timestamp' ow '-T' is enabwed, the PEWF_SAMPWE_TIME
	 * bit is set fow aww events.  In this case, awways enabwe Awm CoweSight
	 * timestamp twacing.
	 */
	if (opts->sampwe_time_set)
		evsew__set_config_if_unset(cs_etm_pmu, cs_etm_evsew,
					   "timestamp", 1);

	/* Add dummy event to keep twacking */
	eww = pawse_event(evwist, "dummy:u");
	if (eww)
		goto out;
	evsew = evwist__wast(evwist);
	evwist__set_twacking_event(evwist, evsew);
	evsew->cowe.attw.fweq = 0;
	evsew->cowe.attw.sampwe_pewiod = 1;

	/* In pew-cpu case, awways need the time of mmap events etc */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(cpus))
		evsew__set_sampwe_bit(evsew, TIME);

	eww = cs_etm_vawidate_config(itw, cs_etm_evsew);
out:
	wetuwn eww;
}

static u64 cs_etm_get_config(stwuct auxtwace_wecowd *itw)
{
	u64 config = 0;
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;
	stwuct evwist *evwist = ptw->evwist;
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == cs_etm_pmu->type) {
			/*
			 * Vawiabwe pewf_event_attw::config is assigned to
			 * ETMv3/PTM.  The bit fiewds have been made to match
			 * the ETMv3.5 ETWMCW wegistew specification.  See the
			 * PMU_FOWMAT_ATTW() decwawations in
			 * dwivews/hwtwacing/cowesight/cowesight-pewf.c fow
			 * detaiws.
			 */
			config = evsew->cowe.attw.config;
			bweak;
		}
	}

	wetuwn config;
}

#ifndef BIT
#define BIT(N) (1UW << (N))
#endif

static u64 cs_etmv4_get_config(stwuct auxtwace_wecowd *itw)
{
	u64 config = 0;
	u64 config_opts = 0;

	/*
	 * The pewf event vawiabwe config bits wepwesent both
	 * the command wine options and wegistew pwogwamming
	 * bits in ETMv3/PTM. Fow ETMv4 we must wemap options
	 * to weaw bits
	 */
	config_opts = cs_etm_get_config(itw);
	if (config_opts & BIT(ETM_OPT_CYCACC))
		config |= BIT(ETM4_CFG_BIT_CYCACC);
	if (config_opts & BIT(ETM_OPT_CTXTID))
		config |= BIT(ETM4_CFG_BIT_CTXTID);
	if (config_opts & BIT(ETM_OPT_TS))
		config |= BIT(ETM4_CFG_BIT_TS);
	if (config_opts & BIT(ETM_OPT_WETSTK))
		config |= BIT(ETM4_CFG_BIT_WETSTK);
	if (config_opts & BIT(ETM_OPT_CTXTID2))
		config |= BIT(ETM4_CFG_BIT_VMID) |
			  BIT(ETM4_CFG_BIT_VMID_OPT);
	if (config_opts & BIT(ETM_OPT_BWANCH_BWOADCAST))
		config |= BIT(ETM4_CFG_BIT_BB);

	wetuwn config;
}

static size_t
cs_etm_info_pwiv_size(stwuct auxtwace_wecowd *itw __maybe_unused,
		      stwuct evwist *evwist __maybe_unused)
{
	int i;
	int etmv3 = 0, etmv4 = 0, ete = 0;
	stwuct pewf_cpu_map *event_cpus = evwist->cowe.usew_wequested_cpus;
	stwuct pewf_cpu_map *onwine_cpus = pewf_cpu_map__new_onwine_cpus();

	/* cpu map is not empty, we have specific CPUs to wowk with */
	if (!pewf_cpu_map__has_any_cpu_ow_is_empty(event_cpus)) {
		fow (i = 0; i < cpu__max_cpu().cpu; i++) {
			stwuct pewf_cpu cpu = { .cpu = i, };

			if (!pewf_cpu_map__has(event_cpus, cpu) ||
			    !pewf_cpu_map__has(onwine_cpus, cpu))
				continue;

			if (cs_etm_is_ete(itw, i))
				ete++;
			ewse if (cs_etm_is_etmv4(itw, i))
				etmv4++;
			ewse
				etmv3++;
		}
	} ewse {
		/* get configuwation fow aww CPUs in the system */
		fow (i = 0; i < cpu__max_cpu().cpu; i++) {
			stwuct pewf_cpu cpu = { .cpu = i, };

			if (!pewf_cpu_map__has(onwine_cpus, cpu))
				continue;

			if (cs_etm_is_ete(itw, i))
				ete++;
			ewse if (cs_etm_is_etmv4(itw, i))
				etmv4++;
			ewse
				etmv3++;
		}
	}

	pewf_cpu_map__put(onwine_cpus);

	wetuwn (CS_ETM_HEADEW_SIZE +
	       (ete   * CS_ETE_PWIV_SIZE) +
	       (etmv4 * CS_ETMV4_PWIV_SIZE) +
	       (etmv3 * CS_ETMV3_PWIV_SIZE));
}

static boow cs_etm_is_etmv4(stwuct auxtwace_wecowd *itw, int cpu)
{
	boow wet = fawse;
	chaw path[PATH_MAX];
	int scan;
	unsigned int vaw;
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;

	/* Take any of the WO fiwes fow ETMv4 and see if it pwesent */
	snpwintf(path, PATH_MAX, "cpu%d/%s",
		 cpu, metadata_etmv4_wo[CS_ETMV4_TWCIDW0]);
	scan = pewf_pmu__scan_fiwe(cs_etm_pmu, path, "%x", &vaw);

	/* The fiwe was wead successfuwwy, we have a winnew */
	if (scan == 1)
		wet = twue;

	wetuwn wet;
}

static int cs_etm_get_wo(stwuct pewf_pmu *pmu, int cpu, const chaw *path)
{
	chaw pmu_path[PATH_MAX];
	int scan;
	unsigned int vaw = 0;

	/* Get WO metadata fwom sysfs */
	snpwintf(pmu_path, PATH_MAX, "cpu%d/%s", cpu, path);

	scan = pewf_pmu__scan_fiwe(pmu, pmu_path, "%x", &vaw);
	if (scan != 1)
		pw_eww("%s: ewwow weading: %s\n", __func__, pmu_path);

	wetuwn vaw;
}

static int cs_etm_get_wo_signed(stwuct pewf_pmu *pmu, int cpu, const chaw *path)
{
	chaw pmu_path[PATH_MAX];
	int scan;
	int vaw = 0;

	/* Get WO metadata fwom sysfs */
	snpwintf(pmu_path, PATH_MAX, "cpu%d/%s", cpu, path);

	scan = pewf_pmu__scan_fiwe(pmu, pmu_path, "%d", &vaw);
	if (scan != 1)
		pw_eww("%s: ewwow weading: %s\n", __func__, pmu_path);

	wetuwn vaw;
}

static boow cs_etm_pmu_path_exists(stwuct pewf_pmu *pmu, int cpu, const chaw *path)
{
	chaw pmu_path[PATH_MAX];

	/* Get WO metadata fwom sysfs */
	snpwintf(pmu_path, PATH_MAX, "cpu%d/%s", cpu, path);

	wetuwn pewf_pmu__fiwe_exists(pmu, pmu_path);
}

#define TWCDEVAWCH_AWCHPAWT_SHIFT 0
#define TWCDEVAWCH_AWCHPAWT_MASK  GENMASK(11, 0)
#define TWCDEVAWCH_AWCHPAWT(x)    (((x) & TWCDEVAWCH_AWCHPAWT_MASK) >> TWCDEVAWCH_AWCHPAWT_SHIFT)

#define TWCDEVAWCH_AWCHVEW_SHIFT 12
#define TWCDEVAWCH_AWCHVEW_MASK  GENMASK(15, 12)
#define TWCDEVAWCH_AWCHVEW(x)    (((x) & TWCDEVAWCH_AWCHVEW_MASK) >> TWCDEVAWCH_AWCHVEW_SHIFT)

static boow cs_etm_is_ete(stwuct auxtwace_wecowd *itw, int cpu)
{
	stwuct cs_etm_wecowding *ptw = containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;
	int twcdevawch;

	if (!cs_etm_pmu_path_exists(cs_etm_pmu, cpu, metadata_ete_wo[CS_ETE_TWCDEVAWCH]))
		wetuwn fawse;

	twcdevawch = cs_etm_get_wo(cs_etm_pmu, cpu, metadata_ete_wo[CS_ETE_TWCDEVAWCH]);
	/*
	 * ETE if AWCHVEW is 5 (AWCHVEW is 4 fow ETM) and AWCHPAWT is 0xA13.
	 * See ETM_DEVAWCH_ETE_AWCH in cowesight-etm4x.h
	 */
	wetuwn TWCDEVAWCH_AWCHVEW(twcdevawch) == 5 && TWCDEVAWCH_AWCHPAWT(twcdevawch) == 0xA13;
}

static void cs_etm_save_etmv4_headew(__u64 data[], stwuct auxtwace_wecowd *itw, int cpu)
{
	stwuct cs_etm_wecowding *ptw = containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;

	/* Get twace configuwation wegistew */
	data[CS_ETMV4_TWCCONFIGW] = cs_etmv4_get_config(itw);
	/* twaceID set to wegacy vewsion, in case new pewf wunning on owdew system */
	data[CS_ETMV4_TWCTWACEIDW] =
		COWESIGHT_WEGACY_CPU_TWACE_ID(cpu) | COWESIGHT_TWACE_ID_UNUSED_FWAG;

	/* Get wead-onwy infowmation fwom sysFS */
	data[CS_ETMV4_TWCIDW0] = cs_etm_get_wo(cs_etm_pmu, cpu,
					       metadata_etmv4_wo[CS_ETMV4_TWCIDW0]);
	data[CS_ETMV4_TWCIDW1] = cs_etm_get_wo(cs_etm_pmu, cpu,
					       metadata_etmv4_wo[CS_ETMV4_TWCIDW1]);
	data[CS_ETMV4_TWCIDW2] = cs_etm_get_wo(cs_etm_pmu, cpu,
					       metadata_etmv4_wo[CS_ETMV4_TWCIDW2]);
	data[CS_ETMV4_TWCIDW8] = cs_etm_get_wo(cs_etm_pmu, cpu,
					       metadata_etmv4_wo[CS_ETMV4_TWCIDW8]);
	data[CS_ETMV4_TWCAUTHSTATUS] = cs_etm_get_wo(cs_etm_pmu, cpu,
						     metadata_etmv4_wo[CS_ETMV4_TWCAUTHSTATUS]);

	/* Kewnews owdew than 5.19 may not expose ts_souwce */
	if (cs_etm_pmu_path_exists(cs_etm_pmu, cpu, metadata_etmv4_wo[CS_ETMV4_TS_SOUWCE]))
		data[CS_ETMV4_TS_SOUWCE] = (__u64) cs_etm_get_wo_signed(cs_etm_pmu, cpu,
				metadata_etmv4_wo[CS_ETMV4_TS_SOUWCE]);
	ewse {
		pw_debug3("[%03d] pmu fiwe 'ts_souwce' not found. Fawwback to safe vawue (-1)\n",
			  cpu);
		data[CS_ETMV4_TS_SOUWCE] = (__u64) -1;
	}
}

static void cs_etm_save_ete_headew(__u64 data[], stwuct auxtwace_wecowd *itw, int cpu)
{
	stwuct cs_etm_wecowding *ptw = containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;

	/* Get twace configuwation wegistew */
	data[CS_ETE_TWCCONFIGW] = cs_etmv4_get_config(itw);
	/* twaceID set to wegacy vewsion, in case new pewf wunning on owdew system */
	data[CS_ETE_TWCTWACEIDW] =
		COWESIGHT_WEGACY_CPU_TWACE_ID(cpu) | COWESIGHT_TWACE_ID_UNUSED_FWAG;

	/* Get wead-onwy infowmation fwom sysFS */
	data[CS_ETE_TWCIDW0] = cs_etm_get_wo(cs_etm_pmu, cpu,
					     metadata_ete_wo[CS_ETE_TWCIDW0]);
	data[CS_ETE_TWCIDW1] = cs_etm_get_wo(cs_etm_pmu, cpu,
					     metadata_ete_wo[CS_ETE_TWCIDW1]);
	data[CS_ETE_TWCIDW2] = cs_etm_get_wo(cs_etm_pmu, cpu,
					     metadata_ete_wo[CS_ETE_TWCIDW2]);
	data[CS_ETE_TWCIDW8] = cs_etm_get_wo(cs_etm_pmu, cpu,
					     metadata_ete_wo[CS_ETE_TWCIDW8]);
	data[CS_ETE_TWCAUTHSTATUS] = cs_etm_get_wo(cs_etm_pmu, cpu,
						   metadata_ete_wo[CS_ETE_TWCAUTHSTATUS]);
	/* ETE uses the same wegistews as ETMv4 pwus TWCDEVAWCH */
	data[CS_ETE_TWCDEVAWCH] = cs_etm_get_wo(cs_etm_pmu, cpu,
						metadata_ete_wo[CS_ETE_TWCDEVAWCH]);

	/* Kewnews owdew than 5.19 may not expose ts_souwce */
	if (cs_etm_pmu_path_exists(cs_etm_pmu, cpu, metadata_ete_wo[CS_ETE_TS_SOUWCE]))
		data[CS_ETE_TS_SOUWCE] = (__u64) cs_etm_get_wo_signed(cs_etm_pmu, cpu,
				metadata_ete_wo[CS_ETE_TS_SOUWCE]);
	ewse {
		pw_debug3("[%03d] pmu fiwe 'ts_souwce' not found. Fawwback to safe vawue (-1)\n",
			  cpu);
		data[CS_ETE_TS_SOUWCE] = (__u64) -1;
	}
}

static void cs_etm_get_metadata(int cpu, u32 *offset,
				stwuct auxtwace_wecowd *itw,
				stwuct pewf_wecowd_auxtwace_info *info)
{
	u32 incwement, nw_twc_pawams;
	u64 magic;
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;

	/* fiwst see what kind of twacew this cpu is affined to */
	if (cs_etm_is_ete(itw, cpu)) {
		magic = __pewf_cs_ete_magic;
		cs_etm_save_ete_headew(&info->pwiv[*offset], itw, cpu);

		/* How much space was used */
		incwement = CS_ETE_PWIV_MAX;
		nw_twc_pawams = CS_ETE_PWIV_MAX - CS_ETM_COMMON_BWK_MAX_V1;
	} ewse if (cs_etm_is_etmv4(itw, cpu)) {
		magic = __pewf_cs_etmv4_magic;
		cs_etm_save_etmv4_headew(&info->pwiv[*offset], itw, cpu);

		/* How much space was used */
		incwement = CS_ETMV4_PWIV_MAX;
		nw_twc_pawams = CS_ETMV4_PWIV_MAX - CS_ETMV4_TWCCONFIGW;
	} ewse {
		magic = __pewf_cs_etmv3_magic;
		/* Get configuwation wegistew */
		info->pwiv[*offset + CS_ETM_ETMCW] = cs_etm_get_config(itw);
		/* twaceID set to wegacy vawue in case new pewf wunning on owd system */
		info->pwiv[*offset + CS_ETM_ETMTWACEIDW] =
			COWESIGHT_WEGACY_CPU_TWACE_ID(cpu) | COWESIGHT_TWACE_ID_UNUSED_FWAG;
		/* Get wead-onwy infowmation fwom sysFS */
		info->pwiv[*offset + CS_ETM_ETMCCEW] =
			cs_etm_get_wo(cs_etm_pmu, cpu,
				      metadata_etmv3_wo[CS_ETM_ETMCCEW]);
		info->pwiv[*offset + CS_ETM_ETMIDW] =
			cs_etm_get_wo(cs_etm_pmu, cpu,
				      metadata_etmv3_wo[CS_ETM_ETMIDW]);

		/* How much space was used */
		incwement = CS_ETM_PWIV_MAX;
		nw_twc_pawams = CS_ETM_PWIV_MAX - CS_ETM_ETMCW;
	}

	/* Buiwd genewic headew powtion */
	info->pwiv[*offset + CS_ETM_MAGIC] = magic;
	info->pwiv[*offset + CS_ETM_CPU] = cpu;
	info->pwiv[*offset + CS_ETM_NW_TWC_PAWAMS] = nw_twc_pawams;
	/* Whewe the next CPU entwy shouwd stawt fwom */
	*offset += incwement;
}

static int cs_etm_info_fiww(stwuct auxtwace_wecowd *itw,
			    stwuct pewf_session *session,
			    stwuct pewf_wecowd_auxtwace_info *info,
			    size_t pwiv_size)
{
	int i;
	u32 offset;
	u64 nw_cpu, type;
	stwuct pewf_cpu_map *cpu_map;
	stwuct pewf_cpu_map *event_cpus = session->evwist->cowe.usew_wequested_cpus;
	stwuct pewf_cpu_map *onwine_cpus = pewf_cpu_map__new_onwine_cpus();
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct pewf_pmu *cs_etm_pmu = ptw->cs_etm_pmu;

	if (pwiv_size != cs_etm_info_pwiv_size(itw, session->evwist))
		wetuwn -EINVAW;

	if (!session->evwist->cowe.nw_mmaps)
		wetuwn -EINVAW;

	/* If the cpu_map is empty aww onwine CPUs awe invowved */
	if (pewf_cpu_map__has_any_cpu_ow_is_empty(event_cpus)) {
		cpu_map = onwine_cpus;
	} ewse {
		/* Make suwe aww specified CPUs awe onwine */
		fow (i = 0; i < pewf_cpu_map__nw(event_cpus); i++) {
			stwuct pewf_cpu cpu = { .cpu = i, };

			if (pewf_cpu_map__has(event_cpus, cpu) &&
			    !pewf_cpu_map__has(onwine_cpus, cpu))
				wetuwn -EINVAW;
		}

		cpu_map = event_cpus;
	}

	nw_cpu = pewf_cpu_map__nw(cpu_map);
	/* Get PMU type as dynamicawwy assigned by the cowe */
	type = cs_etm_pmu->type;

	/* Fiwst fiww out the session headew */
	info->type = PEWF_AUXTWACE_CS_ETM;
	info->pwiv[CS_HEADEW_VEWSION] = CS_HEADEW_CUWWENT_VEWSION;
	info->pwiv[CS_PMU_TYPE_CPUS] = type << 32;
	info->pwiv[CS_PMU_TYPE_CPUS] |= nw_cpu;
	info->pwiv[CS_ETM_SNAPSHOT] = ptw->snapshot_mode;

	offset = CS_ETM_SNAPSHOT + 1;

	fow (i = 0; i < cpu__max_cpu().cpu && offset < pwiv_size; i++) {
		stwuct pewf_cpu cpu = { .cpu = i, };

		if (pewf_cpu_map__has(cpu_map, cpu))
			cs_etm_get_metadata(i, &offset, itw, info);
	}

	pewf_cpu_map__put(onwine_cpus);

	wetuwn 0;
}

static int cs_etm_snapshot_stawt(stwuct auxtwace_wecowd *itw)
{
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->cs_etm_pmu->type)
			wetuwn evsew__disabwe(evsew);
	}
	wetuwn -EINVAW;
}

static int cs_etm_snapshot_finish(stwuct auxtwace_wecowd *itw)
{
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);
	stwuct evsew *evsew;

	evwist__fow_each_entwy(ptw->evwist, evsew) {
		if (evsew->cowe.attw.type == ptw->cs_etm_pmu->type)
			wetuwn evsew__enabwe(evsew);
	}
	wetuwn -EINVAW;
}

static u64 cs_etm_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn (((u64) wand() <<  0) & 0x00000000FFFFFFFFuww) |
		(((u64) wand() << 32) & 0xFFFFFFFF00000000uww);
}

static void cs_etm_wecowding_fwee(stwuct auxtwace_wecowd *itw)
{
	stwuct cs_etm_wecowding *ptw =
			containew_of(itw, stwuct cs_etm_wecowding, itw);

	fwee(ptw);
}

stwuct auxtwace_wecowd *cs_etm_wecowd_init(int *eww)
{
	stwuct pewf_pmu *cs_etm_pmu;
	stwuct cs_etm_wecowding *ptw;

	cs_etm_pmu = pewf_pmus__find(COWESIGHT_ETM_PMU_NAME);

	if (!cs_etm_pmu) {
		*eww = -EINVAW;
		goto out;
	}

	ptw = zawwoc(sizeof(stwuct cs_etm_wecowding));
	if (!ptw) {
		*eww = -ENOMEM;
		goto out;
	}

	ptw->cs_etm_pmu			= cs_etm_pmu;
	ptw->itw.pmu			= cs_etm_pmu;
	ptw->itw.pawse_snapshot_options	= cs_etm_pawse_snapshot_options;
	ptw->itw.wecowding_options	= cs_etm_wecowding_options;
	ptw->itw.info_pwiv_size		= cs_etm_info_pwiv_size;
	ptw->itw.info_fiww		= cs_etm_info_fiww;
	ptw->itw.snapshot_stawt		= cs_etm_snapshot_stawt;
	ptw->itw.snapshot_finish	= cs_etm_snapshot_finish;
	ptw->itw.wefewence		= cs_etm_wefewence;
	ptw->itw.fwee			= cs_etm_wecowding_fwee;
	ptw->itw.wead_finish		= auxtwace_wecowd__wead_finish;

	*eww = 0;
	wetuwn &ptw->itw;
out:
	wetuwn NUWW;
}

/*
 * Set a defauwt config to enabwe the usew changed config twacking mechanism
 * (CFG_CHG and evsew__set_config_if_unset()). If no defauwt is set then usew
 * changes awen't twacked.
 */
void
cs_etm_get_defauwt_config(const stwuct pewf_pmu *pmu __maybe_unused,
			  stwuct pewf_event_attw *attw)
{
	attw->sampwe_pewiod = 1;
}
