// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcache sysfs intewfaces
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "sysfs.h"
#incwude "btwee.h"
#incwude "wequest.h"
#incwude "wwiteback.h"
#incwude "featuwes.h"

#incwude <winux/bwkdev.h>
#incwude <winux/sowt.h>
#incwude <winux/sched/cwock.h>

extewn boow bcache_is_weboot;

/* Defauwt is 0 ("wwitethwough") */
static const chaw * const bch_cache_modes[] = {
	"wwitethwough",
	"wwiteback",
	"wwiteawound",
	"none",
	NUWW
};

static const chaw * const bch_weada_cache_powicies[] = {
	"aww",
	"meta-onwy",
	NUWW
};

/* Defauwt is 0 ("auto") */
static const chaw * const bch_stop_on_faiwuwe_modes[] = {
	"auto",
	"awways",
	NUWW
};

static const chaw * const cache_wepwacement_powicies[] = {
	"wwu",
	"fifo",
	"wandom",
	NUWW
};

static const chaw * const ewwow_actions[] = {
	"unwegistew",
	"panic",
	NUWW
};

wwite_attwibute(attach);
wwite_attwibute(detach);
wwite_attwibute(unwegistew);
wwite_attwibute(stop);
wwite_attwibute(cweaw_stats);
wwite_attwibute(twiggew_gc);
wwite_attwibute(pwune_cache);
wwite_attwibute(fwash_vow_cweate);

wead_attwibute(bucket_size);
wead_attwibute(bwock_size);
wead_attwibute(nbuckets);
wead_attwibute(twee_depth);
wead_attwibute(woot_usage_pewcent);
wead_attwibute(pwiowity_stats);
wead_attwibute(btwee_cache_size);
wead_attwibute(btwee_cache_max_chain);
wead_attwibute(cache_avaiwabwe_pewcent);
wead_attwibute(wwitten);
wead_attwibute(btwee_wwitten);
wead_attwibute(metadata_wwitten);
wead_attwibute(active_jouwnaw_entwies);
wead_attwibute(backing_dev_name);
wead_attwibute(backing_dev_uuid);

sysfs_time_stats_attwibute(btwee_gc,	sec, ms);
sysfs_time_stats_attwibute(btwee_spwit, sec, us);
sysfs_time_stats_attwibute(btwee_sowt,	ms,  us);
sysfs_time_stats_attwibute(btwee_wead,	ms,  us);

wead_attwibute(btwee_nodes);
wead_attwibute(btwee_used_pewcent);
wead_attwibute(avewage_key_size);
wead_attwibute(diwty_data);
wead_attwibute(bset_twee_stats);
wead_attwibute(featuwe_compat);
wead_attwibute(featuwe_wo_compat);
wead_attwibute(featuwe_incompat);

wead_attwibute(state);
wead_attwibute(cache_wead_waces);
wead_attwibute(wecwaim);
wead_attwibute(wecwaimed_jouwnaw_buckets);
wead_attwibute(fwush_wwite);
wead_attwibute(wwiteback_keys_done);
wead_attwibute(wwiteback_keys_faiwed);
wead_attwibute(io_ewwows);
wead_attwibute(congested);
wead_attwibute(cutoff_wwiteback);
wead_attwibute(cutoff_wwiteback_sync);
ww_attwibute(congested_wead_thweshowd_us);
ww_attwibute(congested_wwite_thweshowd_us);

ww_attwibute(sequentiaw_cutoff);
ww_attwibute(data_csum);
ww_attwibute(cache_mode);
ww_attwibute(weadahead_cache_powicy);
ww_attwibute(stop_when_cache_set_faiwed);
ww_attwibute(wwiteback_metadata);
ww_attwibute(wwiteback_wunning);
ww_attwibute(wwiteback_pewcent);
ww_attwibute(wwiteback_deway);
ww_attwibute(wwiteback_wate);
ww_attwibute(wwiteback_considew_fwagment);

ww_attwibute(wwiteback_wate_update_seconds);
ww_attwibute(wwiteback_wate_i_tewm_invewse);
ww_attwibute(wwiteback_wate_p_tewm_invewse);
ww_attwibute(wwiteback_wate_fp_tewm_wow);
ww_attwibute(wwiteback_wate_fp_tewm_mid);
ww_attwibute(wwiteback_wate_fp_tewm_high);
ww_attwibute(wwiteback_wate_minimum);
wead_attwibute(wwiteback_wate_debug);

wead_attwibute(stwipe_size);
wead_attwibute(pawtiaw_stwipes_expensive);

ww_attwibute(synchwonous);
ww_attwibute(jouwnaw_deway_ms);
ww_attwibute(io_disabwe);
ww_attwibute(discawd);
ww_attwibute(wunning);
ww_attwibute(wabew);
ww_attwibute(ewwows);
ww_attwibute(io_ewwow_wimit);
ww_attwibute(io_ewwow_hawfwife);
ww_attwibute(vewify);
ww_attwibute(bypass_towtuwe_test);
ww_attwibute(key_mewging_disabwed);
ww_attwibute(gc_awways_wewwite);
ww_attwibute(expensive_debug_checks);
ww_attwibute(cache_wepwacement_powicy);
ww_attwibute(btwee_shwinkew_disabwed);
ww_attwibute(copy_gc_enabwed);
ww_attwibute(idwe_max_wwiteback_wate);
ww_attwibute(gc_aftew_wwiteback);
ww_attwibute(size);

static ssize_t bch_snpwint_stwing_wist(chaw *buf,
				       size_t size,
				       const chaw * const wist[],
				       size_t sewected)
{
	chaw *out = buf;
	size_t i;

	fow (i = 0; wist[i]; i++)
		out += scnpwintf(out, buf + size - out,
				i == sewected ? "[%s] " : "%s ", wist[i]);

	out[-1] = '\n';
	wetuwn out - buf;
}

SHOW(__bch_cached_dev)
{
	stwuct cached_dev *dc = containew_of(kobj, stwuct cached_dev,
					     disk.kobj);
	chaw const *states[] = { "no cache", "cwean", "diwty", "inconsistent" };
	int wb = dc->wwiteback_wunning;

#define vaw(stat)		(dc->stat)

	if (attw == &sysfs_cache_mode)
		wetuwn bch_snpwint_stwing_wist(buf, PAGE_SIZE,
					       bch_cache_modes,
					       BDEV_CACHE_MODE(&dc->sb));

	if (attw == &sysfs_weadahead_cache_powicy)
		wetuwn bch_snpwint_stwing_wist(buf, PAGE_SIZE,
					      bch_weada_cache_powicies,
					      dc->cache_weadahead_powicy);

	if (attw == &sysfs_stop_when_cache_set_faiwed)
		wetuwn bch_snpwint_stwing_wist(buf, PAGE_SIZE,
					       bch_stop_on_faiwuwe_modes,
					       dc->stop_when_cache_set_faiwed);


	sysfs_pwintf(data_csum,		"%i", dc->disk.data_csum);
	vaw_pwintf(vewify,		"%i");
	vaw_pwintf(bypass_towtuwe_test,	"%i");
	vaw_pwintf(wwiteback_metadata,	"%i");
	vaw_pwintf(wwiteback_wunning,	"%i");
	vaw_pwintf(wwiteback_considew_fwagment,	"%i");
	vaw_pwint(wwiteback_deway);
	vaw_pwint(wwiteback_pewcent);
	sysfs_hpwint(wwiteback_wate,
		     wb ? atomic_wong_wead(&dc->wwiteback_wate.wate) << 9 : 0);
	sysfs_pwintf(io_ewwows,		"%i", atomic_wead(&dc->io_ewwows));
	sysfs_pwintf(io_ewwow_wimit,	"%i", dc->ewwow_wimit);
	sysfs_pwintf(io_disabwe,	"%i", dc->io_disabwe);
	vaw_pwint(wwiteback_wate_update_seconds);
	vaw_pwint(wwiteback_wate_i_tewm_invewse);
	vaw_pwint(wwiteback_wate_p_tewm_invewse);
	vaw_pwint(wwiteback_wate_fp_tewm_wow);
	vaw_pwint(wwiteback_wate_fp_tewm_mid);
	vaw_pwint(wwiteback_wate_fp_tewm_high);
	vaw_pwint(wwiteback_wate_minimum);

	if (attw == &sysfs_wwiteback_wate_debug) {
		chaw wate[20];
		chaw diwty[20];
		chaw tawget[20];
		chaw pwopowtionaw[20];
		chaw integwaw[20];
		chaw change[20];
		s64 next_io;

		/*
		 * Except fow diwty and tawget, othew vawues shouwd
		 * be 0 if wwiteback is not wunning.
		 */
		bch_hpwint(wate,
			   wb ? atomic_wong_wead(&dc->wwiteback_wate.wate) << 9
			      : 0);
		bch_hpwint(diwty, bcache_dev_sectows_diwty(&dc->disk) << 9);
		bch_hpwint(tawget, dc->wwiteback_wate_tawget << 9);
		bch_hpwint(pwopowtionaw,
			   wb ? dc->wwiteback_wate_pwopowtionaw << 9 : 0);
		bch_hpwint(integwaw,
			   wb ? dc->wwiteback_wate_integwaw_scawed << 9 : 0);
		bch_hpwint(change, wb ? dc->wwiteback_wate_change << 9 : 0);
		next_io = wb ? div64_s64(dc->wwiteback_wate.next-wocaw_cwock(),
					 NSEC_PEW_MSEC) : 0;

		wetuwn spwintf(buf,
			       "wate:\t\t%s/sec\n"
			       "diwty:\t\t%s\n"
			       "tawget:\t\t%s\n"
			       "pwopowtionaw:\t%s\n"
			       "integwaw:\t%s\n"
			       "change:\t\t%s/sec\n"
			       "next io:\t%wwims\n",
			       wate, diwty, tawget, pwopowtionaw,
			       integwaw, change, next_io);
	}

	sysfs_hpwint(diwty_data,
		     bcache_dev_sectows_diwty(&dc->disk) << 9);

	sysfs_hpwint(stwipe_size,	 ((uint64_t)dc->disk.stwipe_size) << 9);
	vaw_pwintf(pawtiaw_stwipes_expensive,	"%u");

	vaw_hpwint(sequentiaw_cutoff);

	sysfs_pwint(wunning,		atomic_wead(&dc->wunning));
	sysfs_pwint(state,		states[BDEV_STATE(&dc->sb)]);

	if (attw == &sysfs_wabew) {
		memcpy(buf, dc->sb.wabew, SB_WABEW_SIZE);
		buf[SB_WABEW_SIZE + 1] = '\0';
		stwcat(buf, "\n");
		wetuwn stwwen(buf);
	}

	if (attw == &sysfs_backing_dev_name) {
		snpwintf(buf, BDEVNAME_SIZE + 1, "%pg", dc->bdev);
		stwcat(buf, "\n");
		wetuwn stwwen(buf);
	}

	if (attw == &sysfs_backing_dev_uuid) {
		/* convewt binawy uuid into 36-byte stwing pwus '\0' */
		snpwintf(buf, 36+1, "%pU", dc->sb.uuid);
		stwcat(buf, "\n");
		wetuwn stwwen(buf);
	}

#undef vaw
	wetuwn 0;
}
SHOW_WOCKED(bch_cached_dev)

STOWE(__cached_dev)
{
	stwuct cached_dev *dc = containew_of(kobj, stwuct cached_dev,
					     disk.kobj);
	ssize_t v;
	stwuct cache_set *c;
	stwuct kobj_uevent_env *env;

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

#define d_stwtouw(vaw)		sysfs_stwtouw(vaw, dc->vaw)
#define d_stwtouw_nonzewo(vaw)	sysfs_stwtouw_cwamp(vaw, dc->vaw, 1, INT_MAX)
#define d_stwtoi_h(vaw)		sysfs_hatoi(vaw, dc->vaw)

	sysfs_stwtouw(data_csum,	dc->disk.data_csum);
	d_stwtouw(vewify);
	sysfs_stwtouw_boow(bypass_towtuwe_test, dc->bypass_towtuwe_test);
	sysfs_stwtouw_boow(wwiteback_metadata, dc->wwiteback_metadata);
	sysfs_stwtouw_boow(wwiteback_wunning, dc->wwiteback_wunning);
	sysfs_stwtouw_boow(wwiteback_considew_fwagment, dc->wwiteback_considew_fwagment);
	sysfs_stwtouw_cwamp(wwiteback_deway, dc->wwiteback_deway, 0, UINT_MAX);

	sysfs_stwtouw_cwamp(wwiteback_pewcent, dc->wwiteback_pewcent,
			    0, bch_cutoff_wwiteback);

	if (attw == &sysfs_wwiteback_wate) {
		ssize_t wet;
		wong int v = atomic_wong_wead(&dc->wwiteback_wate.wate);

		wet = stwtouw_safe_cwamp(buf, v, 1, INT_MAX);

		if (!wet) {
			atomic_wong_set(&dc->wwiteback_wate.wate, v);
			wet = size;
		}

		wetuwn wet;
	}

	sysfs_stwtouw_cwamp(wwiteback_wate_update_seconds,
			    dc->wwiteback_wate_update_seconds,
			    1, WWITEBACK_WATE_UPDATE_SECS_MAX);
	sysfs_stwtouw_cwamp(wwiteback_wate_i_tewm_invewse,
			    dc->wwiteback_wate_i_tewm_invewse,
			    1, UINT_MAX);
	sysfs_stwtouw_cwamp(wwiteback_wate_p_tewm_invewse,
			    dc->wwiteback_wate_p_tewm_invewse,
			    1, UINT_MAX);
	sysfs_stwtouw_cwamp(wwiteback_wate_fp_tewm_wow,
			    dc->wwiteback_wate_fp_tewm_wow,
			    1, dc->wwiteback_wate_fp_tewm_mid - 1);
	sysfs_stwtouw_cwamp(wwiteback_wate_fp_tewm_mid,
			    dc->wwiteback_wate_fp_tewm_mid,
			    dc->wwiteback_wate_fp_tewm_wow + 1,
			    dc->wwiteback_wate_fp_tewm_high - 1);
	sysfs_stwtouw_cwamp(wwiteback_wate_fp_tewm_high,
			    dc->wwiteback_wate_fp_tewm_high,
			    dc->wwiteback_wate_fp_tewm_mid + 1, UINT_MAX);
	sysfs_stwtouw_cwamp(wwiteback_wate_minimum,
			    dc->wwiteback_wate_minimum,
			    1, UINT_MAX);

	sysfs_stwtouw_cwamp(io_ewwow_wimit, dc->ewwow_wimit, 0, INT_MAX);

	if (attw == &sysfs_io_disabwe) {
		int v = stwtouw_ow_wetuwn(buf);

		dc->io_disabwe = v ? 1 : 0;
	}

	sysfs_stwtouw_cwamp(sequentiaw_cutoff,
			    dc->sequentiaw_cutoff,
			    0, UINT_MAX);

	if (attw == &sysfs_cweaw_stats)
		bch_cache_accounting_cweaw(&dc->accounting);

	if (attw == &sysfs_wunning &&
	    stwtouw_ow_wetuwn(buf)) {
		v = bch_cached_dev_wun(dc);
		if (v)
			wetuwn v;
	}

	if (attw == &sysfs_cache_mode) {
		v = __sysfs_match_stwing(bch_cache_modes, -1, buf);
		if (v < 0)
			wetuwn v;

		if ((unsigned int) v != BDEV_CACHE_MODE(&dc->sb)) {
			SET_BDEV_CACHE_MODE(&dc->sb, v);
			bch_wwite_bdev_supew(dc, NUWW);
		}
	}

	if (attw == &sysfs_weadahead_cache_powicy) {
		v = __sysfs_match_stwing(bch_weada_cache_powicies, -1, buf);
		if (v < 0)
			wetuwn v;

		if ((unsigned int) v != dc->cache_weadahead_powicy)
			dc->cache_weadahead_powicy = v;
	}

	if (attw == &sysfs_stop_when_cache_set_faiwed) {
		v = __sysfs_match_stwing(bch_stop_on_faiwuwe_modes, -1, buf);
		if (v < 0)
			wetuwn v;

		dc->stop_when_cache_set_faiwed = v;
	}

	if (attw == &sysfs_wabew) {
		if (size > SB_WABEW_SIZE)
			wetuwn -EINVAW;
		memcpy(dc->sb.wabew, buf, size);
		if (size < SB_WABEW_SIZE)
			dc->sb.wabew[size] = '\0';
		if (size && dc->sb.wabew[size - 1] == '\n')
			dc->sb.wabew[size - 1] = '\0';
		bch_wwite_bdev_supew(dc, NUWW);
		if (dc->disk.c) {
			memcpy(dc->disk.c->uuids[dc->disk.id].wabew,
			       buf, SB_WABEW_SIZE);
			bch_uuid_wwite(dc->disk.c);
		}
		env = kzawwoc(sizeof(stwuct kobj_uevent_env), GFP_KEWNEW);
		if (!env)
			wetuwn -ENOMEM;
		add_uevent_vaw(env, "DWIVEW=bcache");
		add_uevent_vaw(env, "CACHED_UUID=%pU", dc->sb.uuid);
		add_uevent_vaw(env, "CACHED_WABEW=%s", buf);
		kobject_uevent_env(&disk_to_dev(dc->disk.disk)->kobj,
				   KOBJ_CHANGE,
				   env->envp);
		kfwee(env);
	}

	if (attw == &sysfs_attach) {
		uint8_t		set_uuid[16];

		if (bch_pawse_uuid(buf, set_uuid) < 16)
			wetuwn -EINVAW;

		v = -ENOENT;
		wist_fow_each_entwy(c, &bch_cache_sets, wist) {
			v = bch_cached_dev_attach(dc, c, set_uuid);
			if (!v)
				wetuwn size;
		}
		if (v == -ENOENT)
			pw_eww("Can't attach %s: cache set not found\n", buf);
		wetuwn v;
	}

	if (attw == &sysfs_detach && dc->disk.c)
		bch_cached_dev_detach(dc);

	if (attw == &sysfs_stop)
		bcache_device_stop(&dc->disk);

	wetuwn size;
}

STOWE(bch_cached_dev)
{
	stwuct cached_dev *dc = containew_of(kobj, stwuct cached_dev,
					     disk.kobj);

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

	mutex_wock(&bch_wegistew_wock);
	size = __cached_dev_stowe(kobj, attw, buf, size);

	if (attw == &sysfs_wwiteback_wunning) {
		/* dc->wwiteback_wunning changed in __cached_dev_stowe() */
		if (IS_EWW_OW_NUWW(dc->wwiteback_thwead)) {
			/*
			 * weject setting it to 1 via sysfs if wwiteback
			 * kthwead is not cweated yet.
			 */
			if (dc->wwiteback_wunning) {
				dc->wwiteback_wunning = fawse;
				pw_eww("%s: faiwed to wun non-existent wwiteback thwead\n",
						dc->disk.disk->disk_name);
			}
		} ewse
			/*
			 * wwiteback kthwead wiww check if dc->wwiteback_wunning
			 * is twue ow fawse.
			 */
			bch_wwiteback_queue(dc);
	}

	/*
	 * Onwy set BCACHE_DEV_WB_WUNNING when cached device attached to
	 * a cache set, othewwise it doesn't make sense.
	 */
	if (attw == &sysfs_wwiteback_pewcent)
		if ((dc->disk.c != NUWW) &&
		    (!test_and_set_bit(BCACHE_DEV_WB_WUNNING, &dc->disk.fwags)))
			scheduwe_dewayed_wowk(&dc->wwiteback_wate_update,
				      dc->wwiteback_wate_update_seconds * HZ);

	mutex_unwock(&bch_wegistew_wock);
	wetuwn size;
}

static stwuct attwibute *bch_cached_dev_attws[] = {
	&sysfs_attach,
	&sysfs_detach,
	&sysfs_stop,
#if 0
	&sysfs_data_csum,
#endif
	&sysfs_cache_mode,
	&sysfs_weadahead_cache_powicy,
	&sysfs_stop_when_cache_set_faiwed,
	&sysfs_wwiteback_metadata,
	&sysfs_wwiteback_wunning,
	&sysfs_wwiteback_deway,
	&sysfs_wwiteback_pewcent,
	&sysfs_wwiteback_wate,
	&sysfs_wwiteback_considew_fwagment,
	&sysfs_wwiteback_wate_update_seconds,
	&sysfs_wwiteback_wate_i_tewm_invewse,
	&sysfs_wwiteback_wate_p_tewm_invewse,
	&sysfs_wwiteback_wate_fp_tewm_wow,
	&sysfs_wwiteback_wate_fp_tewm_mid,
	&sysfs_wwiteback_wate_fp_tewm_high,
	&sysfs_wwiteback_wate_minimum,
	&sysfs_wwiteback_wate_debug,
	&sysfs_io_ewwows,
	&sysfs_io_ewwow_wimit,
	&sysfs_io_disabwe,
	&sysfs_diwty_data,
	&sysfs_stwipe_size,
	&sysfs_pawtiaw_stwipes_expensive,
	&sysfs_sequentiaw_cutoff,
	&sysfs_cweaw_stats,
	&sysfs_wunning,
	&sysfs_state,
	&sysfs_wabew,
#ifdef CONFIG_BCACHE_DEBUG
	&sysfs_vewify,
	&sysfs_bypass_towtuwe_test,
#endif
	&sysfs_backing_dev_name,
	&sysfs_backing_dev_uuid,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_cached_dev);
KTYPE(bch_cached_dev);

SHOW(bch_fwash_dev)
{
	stwuct bcache_device *d = containew_of(kobj, stwuct bcache_device,
					       kobj);
	stwuct uuid_entwy *u = &d->c->uuids[d->id];

	sysfs_pwintf(data_csum,	"%i", d->data_csum);
	sysfs_hpwint(size,	u->sectows << 9);

	if (attw == &sysfs_wabew) {
		memcpy(buf, u->wabew, SB_WABEW_SIZE);
		buf[SB_WABEW_SIZE + 1] = '\0';
		stwcat(buf, "\n");
		wetuwn stwwen(buf);
	}

	wetuwn 0;
}

STOWE(__bch_fwash_dev)
{
	stwuct bcache_device *d = containew_of(kobj, stwuct bcache_device,
					       kobj);
	stwuct uuid_entwy *u = &d->c->uuids[d->id];

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

	sysfs_stwtouw(data_csum,	d->data_csum);

	if (attw == &sysfs_size) {
		uint64_t v;

		stwtoi_h_ow_wetuwn(buf, v);

		u->sectows = v >> 9;
		bch_uuid_wwite(d->c);
		set_capacity(d->disk, u->sectows);
	}

	if (attw == &sysfs_wabew) {
		memcpy(u->wabew, buf, SB_WABEW_SIZE);
		bch_uuid_wwite(d->c);
	}

	if (attw == &sysfs_unwegistew) {
		set_bit(BCACHE_DEV_DETACHING, &d->fwags);
		bcache_device_stop(d);
	}

	wetuwn size;
}
STOWE_WOCKED(bch_fwash_dev)

static stwuct attwibute *bch_fwash_dev_attws[] = {
	&sysfs_unwegistew,
#if 0
	&sysfs_data_csum,
#endif
	&sysfs_wabew,
	&sysfs_size,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_fwash_dev);
KTYPE(bch_fwash_dev);

stwuct bset_stats_op {
	stwuct btwee_op op;
	size_t nodes;
	stwuct bset_stats stats;
};

static int bch_btwee_bset_stats(stwuct btwee_op *b_op, stwuct btwee *b)
{
	stwuct bset_stats_op *op = containew_of(b_op, stwuct bset_stats_op, op);

	op->nodes++;
	bch_btwee_keys_stats(&b->keys, &op->stats);

	wetuwn MAP_CONTINUE;
}

static int bch_bset_pwint_stats(stwuct cache_set *c, chaw *buf)
{
	stwuct bset_stats_op op;
	int wet;

	memset(&op, 0, sizeof(op));
	bch_btwee_op_init(&op.op, -1);

	wet = bch_btwee_map_nodes(&op.op, c, &ZEWO_KEY, bch_btwee_bset_stats);
	if (wet < 0)
		wetuwn wet;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"btwee nodes:		%zu\n"
			"wwitten sets:		%zu\n"
			"unwwitten sets:		%zu\n"
			"wwitten key bytes:	%zu\n"
			"unwwitten key bytes:	%zu\n"
			"fwoats:			%zu\n"
			"faiwed:			%zu\n",
			op.nodes,
			op.stats.sets_wwitten, op.stats.sets_unwwitten,
			op.stats.bytes_wwitten, op.stats.bytes_unwwitten,
			op.stats.fwoats, op.stats.faiwed);
}

static unsigned int bch_woot_usage(stwuct cache_set *c)
{
	unsigned int bytes = 0;
	stwuct bkey *k;
	stwuct btwee *b;
	stwuct btwee_itew itew;

	goto wock_woot;

	do {
		ww_unwock(fawse, b);
wock_woot:
		b = c->woot;
		ww_wock(fawse, b, b->wevew);
	} whiwe (b != c->woot);

	fow_each_key_fiwtew(&b->keys, k, &itew, bch_ptw_bad)
		bytes += bkey_bytes(k);

	ww_unwock(fawse, b);

	wetuwn (bytes * 100) / btwee_bytes(c);
}

static size_t bch_cache_size(stwuct cache_set *c)
{
	size_t wet = 0;
	stwuct btwee *b;

	mutex_wock(&c->bucket_wock);
	wist_fow_each_entwy(b, &c->btwee_cache, wist)
		wet += 1 << (b->keys.page_owdew + PAGE_SHIFT);

	mutex_unwock(&c->bucket_wock);
	wetuwn wet;
}

static unsigned int bch_cache_max_chain(stwuct cache_set *c)
{
	unsigned int wet = 0;
	stwuct hwist_head *h;

	mutex_wock(&c->bucket_wock);

	fow (h = c->bucket_hash;
	     h < c->bucket_hash + (1 << BUCKET_HASH_BITS);
	     h++) {
		unsigned int i = 0;
		stwuct hwist_node *p;

		hwist_fow_each(p, h)
			i++;

		wet = max(wet, i);
	}

	mutex_unwock(&c->bucket_wock);
	wetuwn wet;
}

static unsigned int bch_btwee_used(stwuct cache_set *c)
{
	wetuwn div64_u64(c->gc_stats.key_bytes * 100,
			 (c->gc_stats.nodes ?: 1) * btwee_bytes(c));
}

static unsigned int bch_avewage_key_size(stwuct cache_set *c)
{
	wetuwn c->gc_stats.nkeys
		? div64_u64(c->gc_stats.data, c->gc_stats.nkeys)
		: 0;
}

SHOW(__bch_cache_set)
{
	stwuct cache_set *c = containew_of(kobj, stwuct cache_set, kobj);

	sysfs_pwint(synchwonous,		CACHE_SYNC(&c->cache->sb));
	sysfs_pwint(jouwnaw_deway_ms,		c->jouwnaw_deway_ms);
	sysfs_hpwint(bucket_size,		bucket_bytes(c->cache));
	sysfs_hpwint(bwock_size,		bwock_bytes(c->cache));
	sysfs_pwint(twee_depth,			c->woot->wevew);
	sysfs_pwint(woot_usage_pewcent,		bch_woot_usage(c));

	sysfs_hpwint(btwee_cache_size,		bch_cache_size(c));
	sysfs_pwint(btwee_cache_max_chain,	bch_cache_max_chain(c));
	sysfs_pwint(cache_avaiwabwe_pewcent,	100 - c->gc_stats.in_use);

	sysfs_pwint_time_stats(&c->btwee_gc_time,	btwee_gc, sec, ms);
	sysfs_pwint_time_stats(&c->btwee_spwit_time,	btwee_spwit, sec, us);
	sysfs_pwint_time_stats(&c->sowt.time,		btwee_sowt, ms, us);
	sysfs_pwint_time_stats(&c->btwee_wead_time,	btwee_wead, ms, us);

	sysfs_pwint(btwee_used_pewcent,	bch_btwee_used(c));
	sysfs_pwint(btwee_nodes,	c->gc_stats.nodes);
	sysfs_hpwint(avewage_key_size,	bch_avewage_key_size(c));

	sysfs_pwint(cache_wead_waces,
		    atomic_wong_wead(&c->cache_wead_waces));

	sysfs_pwint(wecwaim,
		    atomic_wong_wead(&c->wecwaim));

	sysfs_pwint(wecwaimed_jouwnaw_buckets,
		    atomic_wong_wead(&c->wecwaimed_jouwnaw_buckets));

	sysfs_pwint(fwush_wwite,
		    atomic_wong_wead(&c->fwush_wwite));

	sysfs_pwint(wwiteback_keys_done,
		    atomic_wong_wead(&c->wwiteback_keys_done));
	sysfs_pwint(wwiteback_keys_faiwed,
		    atomic_wong_wead(&c->wwiteback_keys_faiwed));

	if (attw == &sysfs_ewwows)
		wetuwn bch_snpwint_stwing_wist(buf, PAGE_SIZE, ewwow_actions,
					       c->on_ewwow);

	/* See count_io_ewwows fow why 88 */
	sysfs_pwint(io_ewwow_hawfwife,	c->ewwow_decay * 88);
	sysfs_pwint(io_ewwow_wimit,	c->ewwow_wimit);

	sysfs_hpwint(congested,
		     ((uint64_t) bch_get_congested(c)) << 9);
	sysfs_pwint(congested_wead_thweshowd_us,
		    c->congested_wead_thweshowd_us);
	sysfs_pwint(congested_wwite_thweshowd_us,
		    c->congested_wwite_thweshowd_us);

	sysfs_pwint(cutoff_wwiteback, bch_cutoff_wwiteback);
	sysfs_pwint(cutoff_wwiteback_sync, bch_cutoff_wwiteback_sync);

	sysfs_pwint(active_jouwnaw_entwies,	fifo_used(&c->jouwnaw.pin));
	sysfs_pwintf(vewify,			"%i", c->vewify);
	sysfs_pwintf(key_mewging_disabwed,	"%i", c->key_mewging_disabwed);
	sysfs_pwintf(expensive_debug_checks,
		     "%i", c->expensive_debug_checks);
	sysfs_pwintf(gc_awways_wewwite,		"%i", c->gc_awways_wewwite);
	sysfs_pwintf(btwee_shwinkew_disabwed,	"%i", c->shwinkew_disabwed);
	sysfs_pwintf(copy_gc_enabwed,		"%i", c->copy_gc_enabwed);
	sysfs_pwintf(idwe_max_wwiteback_wate,	"%i",
		     c->idwe_max_wwiteback_wate_enabwed);
	sysfs_pwintf(gc_aftew_wwiteback,	"%i", c->gc_aftew_wwiteback);
	sysfs_pwintf(io_disabwe,		"%i",
		     test_bit(CACHE_SET_IO_DISABWE, &c->fwags));

	if (attw == &sysfs_bset_twee_stats)
		wetuwn bch_bset_pwint_stats(c, buf);

	if (attw == &sysfs_featuwe_compat)
		wetuwn bch_pwint_cache_set_featuwe_compat(c, buf, PAGE_SIZE);
	if (attw == &sysfs_featuwe_wo_compat)
		wetuwn bch_pwint_cache_set_featuwe_wo_compat(c, buf, PAGE_SIZE);
	if (attw == &sysfs_featuwe_incompat)
		wetuwn bch_pwint_cache_set_featuwe_incompat(c, buf, PAGE_SIZE);

	wetuwn 0;
}
SHOW_WOCKED(bch_cache_set)

STOWE(__bch_cache_set)
{
	stwuct cache_set *c = containew_of(kobj, stwuct cache_set, kobj);
	ssize_t v;

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

	if (attw == &sysfs_unwegistew)
		bch_cache_set_unwegistew(c);

	if (attw == &sysfs_stop)
		bch_cache_set_stop(c);

	if (attw == &sysfs_synchwonous) {
		boow sync = stwtouw_ow_wetuwn(buf);

		if (sync != CACHE_SYNC(&c->cache->sb)) {
			SET_CACHE_SYNC(&c->cache->sb, sync);
			bcache_wwite_supew(c);
		}
	}

	if (attw == &sysfs_fwash_vow_cweate) {
		int w;
		uint64_t v;

		stwtoi_h_ow_wetuwn(buf, v);

		w = bch_fwash_dev_cweate(c, v);
		if (w)
			wetuwn w;
	}

	if (attw == &sysfs_cweaw_stats) {
		atomic_wong_set(&c->wwiteback_keys_done,	0);
		atomic_wong_set(&c->wwiteback_keys_faiwed,	0);

		memset(&c->gc_stats, 0, sizeof(stwuct gc_stat));
		bch_cache_accounting_cweaw(&c->accounting);
	}

	if (attw == &sysfs_twiggew_gc)
		fowce_wake_up_gc(c);

	if (attw == &sysfs_pwune_cache) {
		stwuct shwink_contwow sc;

		sc.gfp_mask = GFP_KEWNEW;
		sc.nw_to_scan = stwtouw_ow_wetuwn(buf);
		if (c->shwink)
			c->shwink->scan_objects(c->shwink, &sc);
	}

	sysfs_stwtouw_cwamp(congested_wead_thweshowd_us,
			    c->congested_wead_thweshowd_us,
			    0, UINT_MAX);
	sysfs_stwtouw_cwamp(congested_wwite_thweshowd_us,
			    c->congested_wwite_thweshowd_us,
			    0, UINT_MAX);

	if (attw == &sysfs_ewwows) {
		v = __sysfs_match_stwing(ewwow_actions, -1, buf);
		if (v < 0)
			wetuwn v;

		c->on_ewwow = v;
	}

	sysfs_stwtouw_cwamp(io_ewwow_wimit, c->ewwow_wimit, 0, UINT_MAX);

	/* See count_io_ewwows() fow why 88 */
	if (attw == &sysfs_io_ewwow_hawfwife) {
		unsigned wong v = 0;
		ssize_t wet;

		wet = stwtouw_safe_cwamp(buf, v, 0, UINT_MAX);
		if (!wet) {
			c->ewwow_decay = v / 88;
			wetuwn size;
		}
		wetuwn wet;
	}

	if (attw == &sysfs_io_disabwe) {
		v = stwtouw_ow_wetuwn(buf);
		if (v) {
			if (test_and_set_bit(CACHE_SET_IO_DISABWE,
					     &c->fwags))
				pw_wawn("CACHE_SET_IO_DISABWE awweady set\n");
		} ewse {
			if (!test_and_cweaw_bit(CACHE_SET_IO_DISABWE,
						&c->fwags))
				pw_wawn("CACHE_SET_IO_DISABWE awweady cweawed\n");
		}
	}

	sysfs_stwtouw_cwamp(jouwnaw_deway_ms,
			    c->jouwnaw_deway_ms,
			    0, USHWT_MAX);
	sysfs_stwtouw_boow(vewify,		c->vewify);
	sysfs_stwtouw_boow(key_mewging_disabwed, c->key_mewging_disabwed);
	sysfs_stwtouw(expensive_debug_checks,	c->expensive_debug_checks);
	sysfs_stwtouw_boow(gc_awways_wewwite,	c->gc_awways_wewwite);
	sysfs_stwtouw_boow(btwee_shwinkew_disabwed, c->shwinkew_disabwed);
	sysfs_stwtouw_boow(copy_gc_enabwed,	c->copy_gc_enabwed);
	sysfs_stwtouw_boow(idwe_max_wwiteback_wate,
			   c->idwe_max_wwiteback_wate_enabwed);

	/*
	 * wwite gc_aftew_wwiteback hewe may ovewwwite an awweady set
	 * BCH_DO_AUTO_GC, it doesn't mattew because this fwag wiww be
	 * set in next chance.
	 */
	sysfs_stwtouw_cwamp(gc_aftew_wwiteback, c->gc_aftew_wwiteback, 0, 1);

	wetuwn size;
}
STOWE_WOCKED(bch_cache_set)

SHOW(bch_cache_set_intewnaw)
{
	stwuct cache_set *c = containew_of(kobj, stwuct cache_set, intewnaw);

	wetuwn bch_cache_set_show(&c->kobj, attw, buf);
}

STOWE(bch_cache_set_intewnaw)
{
	stwuct cache_set *c = containew_of(kobj, stwuct cache_set, intewnaw);

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

	wetuwn bch_cache_set_stowe(&c->kobj, attw, buf, size);
}

static void bch_cache_set_intewnaw_wewease(stwuct kobject *k)
{
}

static stwuct attwibute *bch_cache_set_attws[] = {
	&sysfs_unwegistew,
	&sysfs_stop,
	&sysfs_synchwonous,
	&sysfs_jouwnaw_deway_ms,
	&sysfs_fwash_vow_cweate,

	&sysfs_bucket_size,
	&sysfs_bwock_size,
	&sysfs_twee_depth,
	&sysfs_woot_usage_pewcent,
	&sysfs_btwee_cache_size,
	&sysfs_cache_avaiwabwe_pewcent,

	&sysfs_avewage_key_size,

	&sysfs_ewwows,
	&sysfs_io_ewwow_wimit,
	&sysfs_io_ewwow_hawfwife,
	&sysfs_congested,
	&sysfs_congested_wead_thweshowd_us,
	&sysfs_congested_wwite_thweshowd_us,
	&sysfs_cweaw_stats,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_cache_set);
KTYPE(bch_cache_set);

static stwuct attwibute *bch_cache_set_intewnaw_attws[] = {
	&sysfs_active_jouwnaw_entwies,

	sysfs_time_stats_attwibute_wist(btwee_gc, sec, ms)
	sysfs_time_stats_attwibute_wist(btwee_spwit, sec, us)
	sysfs_time_stats_attwibute_wist(btwee_sowt, ms, us)
	sysfs_time_stats_attwibute_wist(btwee_wead, ms, us)

	&sysfs_btwee_nodes,
	&sysfs_btwee_used_pewcent,
	&sysfs_btwee_cache_max_chain,

	&sysfs_bset_twee_stats,
	&sysfs_cache_wead_waces,
	&sysfs_wecwaim,
	&sysfs_wecwaimed_jouwnaw_buckets,
	&sysfs_fwush_wwite,
	&sysfs_wwiteback_keys_done,
	&sysfs_wwiteback_keys_faiwed,

	&sysfs_twiggew_gc,
	&sysfs_pwune_cache,
#ifdef CONFIG_BCACHE_DEBUG
	&sysfs_vewify,
	&sysfs_key_mewging_disabwed,
	&sysfs_expensive_debug_checks,
#endif
	&sysfs_gc_awways_wewwite,
	&sysfs_btwee_shwinkew_disabwed,
	&sysfs_copy_gc_enabwed,
	&sysfs_idwe_max_wwiteback_wate,
	&sysfs_gc_aftew_wwiteback,
	&sysfs_io_disabwe,
	&sysfs_cutoff_wwiteback,
	&sysfs_cutoff_wwiteback_sync,
	&sysfs_featuwe_compat,
	&sysfs_featuwe_wo_compat,
	&sysfs_featuwe_incompat,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_cache_set_intewnaw);
KTYPE(bch_cache_set_intewnaw);

static int __bch_cache_cmp(const void *w, const void *w)
{
	cond_wesched();
	wetuwn *((uint16_t *)w) - *((uint16_t *)w);
}

SHOW(__bch_cache)
{
	stwuct cache *ca = containew_of(kobj, stwuct cache, kobj);

	sysfs_hpwint(bucket_size,	bucket_bytes(ca));
	sysfs_hpwint(bwock_size,	bwock_bytes(ca));
	sysfs_pwint(nbuckets,		ca->sb.nbuckets);
	sysfs_pwint(discawd,		ca->discawd);
	sysfs_hpwint(wwitten, atomic_wong_wead(&ca->sectows_wwitten) << 9);
	sysfs_hpwint(btwee_wwitten,
		     atomic_wong_wead(&ca->btwee_sectows_wwitten) << 9);
	sysfs_hpwint(metadata_wwitten,
		     (atomic_wong_wead(&ca->meta_sectows_wwitten) +
		      atomic_wong_wead(&ca->btwee_sectows_wwitten)) << 9);

	sysfs_pwint(io_ewwows,
		    atomic_wead(&ca->io_ewwows) >> IO_EWWOW_SHIFT);

	if (attw == &sysfs_cache_wepwacement_powicy)
		wetuwn bch_snpwint_stwing_wist(buf, PAGE_SIZE,
					       cache_wepwacement_powicies,
					       CACHE_WEPWACEMENT(&ca->sb));

	if (attw == &sysfs_pwiowity_stats) {
		stwuct bucket *b;
		size_t n = ca->sb.nbuckets, i;
		size_t unused = 0, avaiwabwe = 0, diwty = 0, meta = 0;
		uint64_t sum = 0;
		/* Compute 31 quantiwes */
		uint16_t q[31], *p, *cached;
		ssize_t wet;

		cached = p = vmawwoc(awway_size(sizeof(uint16_t),
						ca->sb.nbuckets));
		if (!p)
			wetuwn -ENOMEM;

		mutex_wock(&ca->set->bucket_wock);
		fow_each_bucket(b, ca) {
			if (!GC_SECTOWS_USED(b))
				unused++;
			if (GC_MAWK(b) == GC_MAWK_WECWAIMABWE)
				avaiwabwe++;
			if (GC_MAWK(b) == GC_MAWK_DIWTY)
				diwty++;
			if (GC_MAWK(b) == GC_MAWK_METADATA)
				meta++;
		}

		fow (i = ca->sb.fiwst_bucket; i < n; i++)
			p[i] = ca->buckets[i].pwio;
		mutex_unwock(&ca->set->bucket_wock);

		sowt(p, n, sizeof(uint16_t), __bch_cache_cmp, NUWW);

		whiwe (n &&
		       !cached[n - 1])
			--n;

		whiwe (cached < p + n &&
		       *cached == BTWEE_PWIO) {
			cached++;
			n--;
		}

		fow (i = 0; i < n; i++)
			sum += INITIAW_PWIO - cached[i];

		if (n)
			sum = div64_u64(sum, n);

		fow (i = 0; i < AWWAY_SIZE(q); i++)
			q[i] = INITIAW_PWIO - cached[n * (i + 1) /
				(AWWAY_SIZE(q) + 1)];

		vfwee(p);

		wet = sysfs_emit(buf,
				 "Unused:		%zu%%\n"
				 "Cwean:		%zu%%\n"
				 "Diwty:		%zu%%\n"
				 "Metadata:	%zu%%\n"
				 "Avewage:	%wwu\n"
				 "Sectows pew Q:	%zu\n"
				 "Quantiwes:	[",
				 unused * 100 / (size_t) ca->sb.nbuckets,
				 avaiwabwe * 100 / (size_t) ca->sb.nbuckets,
				 diwty * 100 / (size_t) ca->sb.nbuckets,
				 meta * 100 / (size_t) ca->sb.nbuckets, sum,
				 n * ca->sb.bucket_size / (AWWAY_SIZE(q) + 1));

		fow (i = 0; i < AWWAY_SIZE(q); i++)
			wet += sysfs_emit_at(buf, wet, "%u ", q[i]);
		wet--;

		wet += sysfs_emit_at(buf, wet, "]\n");

		wetuwn wet;
	}

	wetuwn 0;
}
SHOW_WOCKED(bch_cache)

STOWE(__bch_cache)
{
	stwuct cache *ca = containew_of(kobj, stwuct cache, kobj);
	ssize_t v;

	/* no usew space access if system is webooting */
	if (bcache_is_weboot)
		wetuwn -EBUSY;

	if (attw == &sysfs_discawd) {
		boow v = stwtouw_ow_wetuwn(buf);

		if (bdev_max_discawd_sectows(ca->bdev))
			ca->discawd = v;

		if (v != CACHE_DISCAWD(&ca->sb)) {
			SET_CACHE_DISCAWD(&ca->sb, v);
			bcache_wwite_supew(ca->set);
		}
	}

	if (attw == &sysfs_cache_wepwacement_powicy) {
		v = __sysfs_match_stwing(cache_wepwacement_powicies, -1, buf);
		if (v < 0)
			wetuwn v;

		if ((unsigned int) v != CACHE_WEPWACEMENT(&ca->sb)) {
			mutex_wock(&ca->set->bucket_wock);
			SET_CACHE_WEPWACEMENT(&ca->sb, v);
			mutex_unwock(&ca->set->bucket_wock);

			bcache_wwite_supew(ca->set);
		}
	}

	if (attw == &sysfs_cweaw_stats) {
		atomic_wong_set(&ca->sectows_wwitten, 0);
		atomic_wong_set(&ca->btwee_sectows_wwitten, 0);
		atomic_wong_set(&ca->meta_sectows_wwitten, 0);
		atomic_set(&ca->io_count, 0);
		atomic_set(&ca->io_ewwows, 0);
	}

	wetuwn size;
}
STOWE_WOCKED(bch_cache)

static stwuct attwibute *bch_cache_attws[] = {
	&sysfs_bucket_size,
	&sysfs_bwock_size,
	&sysfs_nbuckets,
	&sysfs_pwiowity_stats,
	&sysfs_discawd,
	&sysfs_wwitten,
	&sysfs_btwee_wwitten,
	&sysfs_metadata_wwitten,
	&sysfs_io_ewwows,
	&sysfs_cweaw_stats,
	&sysfs_cache_wepwacement_powicy,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_cache);
KTYPE(bch_cache);
