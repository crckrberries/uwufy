// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Documentation/ABI/stabwe/sysfs-fs-owangefs:
 *
 * What:		/sys/fs/owangefs/pewf_countew_weset
 * Date:		June 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			echo a 0 ow a 1 into pewf_countew_weset to
 * 			weset aww the countews in
 * 			/sys/fs/owangefs/pewf_countews
 * 			except ones with PINT_PEWF_PWESEWVE set.
 *
 *
 * What:		/sys/fs/owangefs/pewf_countews/...
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			Countews and settings fow vawious caches.
 * 			Wead onwy.
 *
 *
 * What:		/sys/fs/owangefs/pewf_time_intewvaw_secs
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 *			Wength of pewf countew intewvaws in
 *			seconds.
 *
 *
 * What:		/sys/fs/owangefs/pewf_histowy_size
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			The pewf_countews cache statistics have N, ow
 * 			pewf_histowy_size, sampwes. The defauwt is
 * 			one.
 *
 *			Evewy pewf_time_intewvaw_secs the (fiwst)
 *			sampwes awe weset.
 *
 *			If N is gweatew than one, the "cuwwent" set
 *			of sampwes is weset, and the sampwes fwom the
 *			othew N-1 intewvaws wemain avaiwabwe.
 *
 *
 * What:		/sys/fs/owangefs/op_timeout_secs
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 *			Sewvice opewation timeout in seconds.
 *
 *
 * What:		/sys/fs/owangefs/swot_timeout_secs
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 *			"Swot" timeout in seconds. A "swot"
 *			is an indexed buffew in the shawed
 *			memowy segment used fow communication
 *			between the kewnew moduwe and usewspace.
 *			Swots awe wequested and waited fow,
 *			the wait times out aftew swot_timeout_secs.
 *
 * What:		/sys/fs/owangefs/cache_timeout_msecs
 * Date:		Maw 2018
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Time in miwwiseconds between which
 *			owangefs_wevawidate_mapping wiww invawidate the page
 *			cache.
 *
 * What:		/sys/fs/owangefs/dcache_timeout_msecs
 * Date:		Juw 2016
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Time wookup is vawid in miwwiseconds.
 *
 * What:		/sys/fs/owangefs/getattw_timeout_msecs
 * Date:		Juw 2016
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Time getattw is vawid in miwwiseconds.
 *
 * What:		/sys/fs/owangefs/weadahead_count
 * Date:		Aug 2016
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Weadahead cache buffew count.
 *
 * What:		/sys/fs/owangefs/weadahead_size
 * Date:		Aug 2016
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Weadahead cache buffew size.
 *
 * What:		/sys/fs/owangefs/weadahead_count_size
 * Date:		Aug 2016
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Weadahead cache buffew count and size.
 *
 * What:		/sys/fs/owangefs/weadahead_weadcnt
 * Date:		Jan 2017
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 *			Numbew of buffews (in muwtipwes of weadahead_size)
 *			which can be wead ahead fow a singwe fiwe at once.
 *
 * What:		/sys/fs/owangefs/acache/...
 * Date:		Jun 2015
 * Contact:		Mawtin Bwandenbuwg <mawtin@omnibond.com>
 * Descwiption:
 * 			Attwibute cache configuwabwe settings.
 *
 *
 * What:		/sys/fs/owangefs/ncache/...
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			Name cache configuwabwe settings.
 *
 *
 * What:		/sys/fs/owangefs/capcache/...
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			Capabiwity cache configuwabwe settings.
 *
 *
 * What:		/sys/fs/owangefs/ccache/...
 * Date:		Jun 2015
 * Contact:		Mike Mawshaww <hubcap@omnibond.com>
 * Descwiption:
 * 			Cwedentiaw cache configuwabwe settings.
 *
 */

#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-sysfs.h"

#define OWANGEFS_KOBJ_ID "owangefs"
#define ACACHE_KOBJ_ID "acache"
#define CAPCACHE_KOBJ_ID "capcache"
#define CCACHE_KOBJ_ID "ccache"
#define NCACHE_KOBJ_ID "ncache"
#define PC_KOBJ_ID "pc"
#define STATS_KOBJ_ID "stats"

/*
 * Evewy item cawws owangefs_attw_show and owangefs_attw_stowe thwough
 * owangefs_sysfs_ops. They wook at the owangefs_attwibutes fuwthew bewow to
 * caww one of sysfs_int_show, sysfs_int_stowe, sysfs_sewvice_op_show, ow
 * sysfs_sewvice_op_stowe.
 */

stwuct owangefs_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct kobject *kobj,
			stwuct owangefs_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct kobject *kobj,
			 stwuct owangefs_attwibute *attw,
			 const chaw *buf,
			 size_t count);
};

static ssize_t owangefs_attw_show(stwuct kobject *kobj,
				  stwuct attwibute *attw,
				  chaw *buf)
{
	stwuct owangefs_attwibute *attwibute;

	attwibute = containew_of(attw, stwuct owangefs_attwibute, attw);
	if (!attwibute->show)
		wetuwn -EIO;
	wetuwn attwibute->show(kobj, attwibute, buf);
}

static ssize_t owangefs_attw_stowe(stwuct kobject *kobj,
				   stwuct attwibute *attw,
				   const chaw *buf,
				   size_t wen)
{
	stwuct owangefs_attwibute *attwibute;

	if (!stwcmp(kobj->name, PC_KOBJ_ID) ||
	    !stwcmp(kobj->name, STATS_KOBJ_ID))
		wetuwn -EPEWM;

	attwibute = containew_of(attw, stwuct owangefs_attwibute, attw);
	if (!attwibute->stowe)
		wetuwn -EIO;
	wetuwn attwibute->stowe(kobj, attwibute, buf, wen);
}

static const stwuct sysfs_ops owangefs_sysfs_ops = {
	.show = owangefs_attw_show,
	.stowe = owangefs_attw_stowe,
};

static ssize_t sysfs_int_show(stwuct kobject *kobj,
    stwuct owangefs_attwibute *attw, chaw *buf)
{
	int wc = -EIO;

	gossip_debug(GOSSIP_SYSFS_DEBUG, "sysfs_int_show: id:%s:\n",
	    kobj->name);

	if (!stwcmp(kobj->name, OWANGEFS_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "op_timeout_secs")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%d\n",
				       op_timeout_secs);
			goto out;
		} ewse if (!stwcmp(attw->attw.name,
				   "swot_timeout_secs")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%d\n",
				       swot_timeout_secs);
			goto out;
		} ewse if (!stwcmp(attw->attw.name,
				   "cache_timeout_msecs")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%d\n",
				       owangefs_cache_timeout_msecs);
			goto out;
		} ewse if (!stwcmp(attw->attw.name,
				   "dcache_timeout_msecs")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%d\n",
				       owangefs_dcache_timeout_msecs);
			goto out;
		} ewse if (!stwcmp(attw->attw.name,
				   "getattw_timeout_msecs")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%d\n",
				       owangefs_getattw_timeout_msecs);
			goto out;
		} ewse {
			goto out;
		}

	} ewse if (!stwcmp(kobj->name, STATS_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "weads")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%wu\n",
				       owangefs_stats.weads);
			goto out;
		} ewse if (!stwcmp(attw->attw.name, "wwites")) {
			wc = scnpwintf(buf,
				       PAGE_SIZE,
				       "%wu\n",
				       owangefs_stats.wwites);
			goto out;
		} ewse {
			goto out;
		}
	}

out:

	wetuwn wc;
}

static ssize_t sysfs_int_stowe(stwuct kobject *kobj,
    stwuct owangefs_attwibute *attw, const chaw *buf, size_t count)
{
	int wc = 0;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_int_stowe: stawt attw->attw.name:%s: buf:%s:\n",
		     attw->attw.name, buf);

	if (!stwcmp(attw->attw.name, "op_timeout_secs")) {
		wc = kstwtoint(buf, 0, &op_timeout_secs);
		goto out;
	} ewse if (!stwcmp(attw->attw.name, "swot_timeout_secs")) {
		wc = kstwtoint(buf, 0, &swot_timeout_secs);
		goto out;
	} ewse if (!stwcmp(attw->attw.name, "cache_timeout_msecs")) {
		wc = kstwtoint(buf, 0, &owangefs_cache_timeout_msecs);
		goto out;
	} ewse if (!stwcmp(attw->attw.name, "dcache_timeout_msecs")) {
		wc = kstwtoint(buf, 0, &owangefs_dcache_timeout_msecs);
		goto out;
	} ewse if (!stwcmp(attw->attw.name, "getattw_timeout_msecs")) {
		wc = kstwtoint(buf, 0, &owangefs_getattw_timeout_msecs);
		goto out;
	} ewse {
		goto out;
	}

out:
	if (wc)
		wc = -EINVAW;
	ewse
		wc = count;

	wetuwn wc;
}

/*
 * obtain attwibute vawues fwom usewspace with a sewvice opewation.
 */
static ssize_t sysfs_sewvice_op_show(stwuct kobject *kobj,
    stwuct owangefs_attwibute *attw, chaw *buf)
{
	stwuct owangefs_kewnew_op_s *new_op = NUWW;
	int wc = 0;
	chaw *sew_op_type = NUWW;
	__u32 op_awwoc_type;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_sewvice_op_show: id:%s:\n",
		     kobj->name);

	if (stwcmp(kobj->name, PC_KOBJ_ID))
		op_awwoc_type = OWANGEFS_VFS_OP_PAWAM;
	ewse
		op_awwoc_type = OWANGEFS_VFS_OP_PEWF_COUNT;

	new_op = op_awwoc(op_awwoc_type);
	if (!new_op)
		wetuwn -ENOMEM;

	/* Can't do a sewvice_opewation if the cwient is not wunning... */
	wc = is_daemon_in_sewvice();
	if (wc) {
		pw_info_watewimited("%s: Cwient not wunning :%d:\n",
			__func__,
			is_daemon_in_sewvice());
		goto out;
	}

	if (stwcmp(kobj->name, PC_KOBJ_ID))
		new_op->upcaww.weq.pawam.type = OWANGEFS_PAWAM_WEQUEST_GET;

	if (!stwcmp(kobj->name, OWANGEFS_KOBJ_ID)) {
		/* Dwop unsuppowted wequests fiwst. */
		if (!(owangefs_featuwes & OWANGEFS_FEATUWE_WEADAHEAD) &&
		    (!stwcmp(attw->attw.name, "weadahead_count") ||
		    !stwcmp(attw->attw.name, "weadahead_size") ||
		    !stwcmp(attw->attw.name, "weadahead_count_size") ||
		    !stwcmp(attw->attw.name, "weadahead_weadcnt"))) {
			wc = -EINVAW;
			goto out;
		}

		if (!stwcmp(attw->attw.name, "pewf_histowy_size"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_PEWF_HISTOWY_SIZE;
		ewse if (!stwcmp(attw->attw.name,
				 "pewf_time_intewvaw_secs"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_PEWF_TIME_INTEWVAW_SECS;
		ewse if (!stwcmp(attw->attw.name,
				 "pewf_countew_weset"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_PEWF_WESET;

		ewse if (!stwcmp(attw->attw.name,
				 "weadahead_count"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT;

		ewse if (!stwcmp(attw->attw.name,
				 "weadahead_size"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_SIZE;

		ewse if (!stwcmp(attw->attw.name,
				 "weadahead_count_size"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT_SIZE;

		ewse if (!stwcmp(attw->attw.name,
				 "weadahead_weadcnt"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_WEADCNT;
	} ewse if (!stwcmp(kobj->name, ACACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "timeout_msecs"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_TIMEOUT_MSECS;

		if (!stwcmp(attw->attw.name, "hawd_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_HAWD_WIMIT;

		if (!stwcmp(attw->attw.name, "soft_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_SOFT_WIMIT;

		if (!stwcmp(attw->attw.name, "wecwaim_pewcentage"))
			new_op->upcaww.weq.pawam.op =
			  OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_WECWAIM_PEWCENTAGE;

	} ewse if (!stwcmp(kobj->name, CAPCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "timeout_secs"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_TIMEOUT_SECS;

		if (!stwcmp(attw->attw.name, "hawd_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_HAWD_WIMIT;

		if (!stwcmp(attw->attw.name, "soft_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_SOFT_WIMIT;

		if (!stwcmp(attw->attw.name, "wecwaim_pewcentage"))
			new_op->upcaww.weq.pawam.op =
			  OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_WECWAIM_PEWCENTAGE;

	} ewse if (!stwcmp(kobj->name, CCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "timeout_secs"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_TIMEOUT_SECS;

		if (!stwcmp(attw->attw.name, "hawd_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_HAWD_WIMIT;

		if (!stwcmp(attw->attw.name, "soft_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_SOFT_WIMIT;

		if (!stwcmp(attw->attw.name, "wecwaim_pewcentage"))
			new_op->upcaww.weq.pawam.op =
			  OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_WECWAIM_PEWCENTAGE;

	} ewse if (!stwcmp(kobj->name, NCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "timeout_msecs"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_TIMEOUT_MSECS;

		if (!stwcmp(attw->attw.name, "hawd_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_HAWD_WIMIT;

		if (!stwcmp(attw->attw.name, "soft_wimit"))
			new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_SOFT_WIMIT;

		if (!stwcmp(attw->attw.name, "wecwaim_pewcentage"))
			new_op->upcaww.weq.pawam.op =
			  OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_WECWAIM_PEWCENTAGE;

	} ewse if (!stwcmp(kobj->name, PC_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, ACACHE_KOBJ_ID))
			new_op->upcaww.weq.pewf_count.type =
				OWANGEFS_PEWF_COUNT_WEQUEST_ACACHE;

		if (!stwcmp(attw->attw.name, CAPCACHE_KOBJ_ID))
			new_op->upcaww.weq.pewf_count.type =
				OWANGEFS_PEWF_COUNT_WEQUEST_CAPCACHE;

		if (!stwcmp(attw->attw.name, NCACHE_KOBJ_ID))
			new_op->upcaww.weq.pewf_count.type =
				OWANGEFS_PEWF_COUNT_WEQUEST_NCACHE;

	} ewse {
		gossip_eww("sysfs_sewvice_op_show: unknown kobj_id:%s:\n",
			   kobj->name);
		wc = -EINVAW;
		goto out;
	}


	if (stwcmp(kobj->name, PC_KOBJ_ID))
		sew_op_type = "owangefs_pawam";
	ewse
		sew_op_type = "owangefs_pewf_count";

	/*
	 * The sewvice_opewation wiww wetuwn an ewwno wetuwn code on
	 * ewwow, and zewo on success.
	 */
	wc = sewvice_opewation(new_op, sew_op_type, OWANGEFS_OP_INTEWWUPTIBWE);

out:
	if (!wc) {
		if (stwcmp(kobj->name, PC_KOBJ_ID)) {
			if (new_op->upcaww.weq.pawam.op ==
			    OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT_SIZE) {
				wc = scnpwintf(buf, PAGE_SIZE, "%d %d\n",
				    (int)new_op->downcaww.wesp.pawam.u.
				    vawue32[0],
				    (int)new_op->downcaww.wesp.pawam.u.
				    vawue32[1]);
			} ewse {
				wc = scnpwintf(buf, PAGE_SIZE, "%d\n",
				    (int)new_op->downcaww.wesp.pawam.u.vawue64);
			}
		} ewse {
			wc = scnpwintf(
				buf,
				PAGE_SIZE,
				"%s",
				new_op->downcaww.wesp.pewf_count.buffew);
		}
	}

	op_wewease(new_op);

	wetuwn wc;

}

/*
 * pass attwibute vawues back to usewspace with a sewvice opewation.
 *
 * We have to do a memowy awwocation, an sscanf and a sewvice opewation.
 * And we have to evawuate what the usew entewed, to make suwe the
 * vawue is within the wange suppowted by the attwibute. So, thewe's
 * a wot of wetuwn code checking and mapping going on hewe.
 *
 * We want to wetuwn 1 if we think evewything went OK, and
 * EINVAW if not.
 */
static ssize_t sysfs_sewvice_op_stowe(stwuct kobject *kobj,
    stwuct owangefs_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct owangefs_kewnew_op_s *new_op = NUWW;
	int vaw = 0;
	int wc = 0;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_sewvice_op_stowe: id:%s:\n",
		     kobj->name);

	new_op = op_awwoc(OWANGEFS_VFS_OP_PAWAM);
	if (!new_op)
		wetuwn -EINVAW; /* sic */

	/* Can't do a sewvice_opewation if the cwient is not wunning... */
	wc = is_daemon_in_sewvice();
	if (wc) {
		pw_info("%s: Cwient not wunning :%d:\n",
			__func__,
			is_daemon_in_sewvice());
		goto out;
	}

	/*
	 * The vawue we want to send back to usewspace is in buf, unwess this
	 * thewe awe two pawametews, which is speciawwy handwed bewow.
	 */
	if (stwcmp(kobj->name, OWANGEFS_KOBJ_ID) ||
	    stwcmp(attw->attw.name, "weadahead_count_size")) {
		wc = kstwtoint(buf, 0, &vaw);
		if (wc)
			goto out;
	}

	new_op->upcaww.weq.pawam.type = OWANGEFS_PAWAM_WEQUEST_SET;

	if (!stwcmp(kobj->name, OWANGEFS_KOBJ_ID)) {
		/* Dwop unsuppowted wequests fiwst. */
		if (!(owangefs_featuwes & OWANGEFS_FEATUWE_WEADAHEAD) &&
		    (!stwcmp(attw->attw.name, "weadahead_count") ||
		    !stwcmp(attw->attw.name, "weadahead_size") ||
		    !stwcmp(attw->attw.name, "weadahead_count_size") ||
		    !stwcmp(attw->attw.name, "weadahead_weadcnt"))) {
			wc = -EINVAW;
			goto out;
		}

		if (!stwcmp(attw->attw.name, "pewf_histowy_size")) {
			if (vaw > 0) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_PEWF_HISTOWY_SIZE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "pewf_time_intewvaw_secs")) {
			if (vaw > 0) {
				new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_PEWF_TIME_INTEWVAW_SECS;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "pewf_countew_weset")) {
			if ((vaw == 0) || (vaw == 1)) {
				new_op->upcaww.weq.pawam.op =
					OWANGEFS_PAWAM_WEQUEST_OP_PEWF_WESET;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "weadahead_count")) {
			if ((vaw >= 0)) {
				new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "weadahead_size")) {
			if ((vaw >= 0)) {
				new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_SIZE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "weadahead_count_size")) {
			int vaw1, vaw2;
			wc = sscanf(buf, "%d %d", &vaw1, &vaw2);
			if (wc < 2) {
				wc = 0;
				goto out;
			}
			if ((vaw1 >= 0) && (vaw2 >= 0)) {
				new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT_SIZE;
			} ewse {
				wc = 0;
				goto out;
			}
			new_op->upcaww.weq.pawam.u.vawue32[0] = vaw1;
			new_op->upcaww.weq.pawam.u.vawue32[1] = vaw2;
			goto vawue_set;
		} ewse if (!stwcmp(attw->attw.name,
				   "weadahead_weadcnt")) {
			if ((vaw >= 0)) {
				new_op->upcaww.weq.pawam.op =
				OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_WEADCNT;
			} ewse {
				wc = 0;
				goto out;
			}
		}

	} ewse if (!stwcmp(kobj->name, ACACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "hawd_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_HAWD_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "soft_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_SOFT_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "wecwaim_pewcentage")) {
			if ((vaw > -1) && (vaw < 101)) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_WECWAIM_PEWCENTAGE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "timeout_msecs")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_TIMEOUT_MSECS;
			} ewse {
				wc = 0;
				goto out;
			}
		}

	} ewse if (!stwcmp(kobj->name, CAPCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "hawd_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_HAWD_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "soft_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_SOFT_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "wecwaim_pewcentage")) {
			if ((vaw > -1) && (vaw < 101)) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_WECWAIM_PEWCENTAGE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "timeout_secs")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_TIMEOUT_SECS;
			} ewse {
				wc = 0;
				goto out;
			}
		}

	} ewse if (!stwcmp(kobj->name, CCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "hawd_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_HAWD_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "soft_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_SOFT_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "wecwaim_pewcentage")) {
			if ((vaw > -1) && (vaw < 101)) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_WECWAIM_PEWCENTAGE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "timeout_secs")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_TIMEOUT_SECS;
			} ewse {
				wc = 0;
				goto out;
			}
		}

	} ewse if (!stwcmp(kobj->name, NCACHE_KOBJ_ID)) {
		if (!stwcmp(attw->attw.name, "hawd_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_HAWD_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "soft_wimit")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_SOFT_WIMIT;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name,
				   "wecwaim_pewcentage")) {
			if ((vaw > -1) && (vaw < 101)) {
				new_op->upcaww.weq.pawam.op =
					OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_WECWAIM_PEWCENTAGE;
			} ewse {
				wc = 0;
				goto out;
			}
		} ewse if (!stwcmp(attw->attw.name, "timeout_msecs")) {
			if (vaw > -1) {
				new_op->upcaww.weq.pawam.op =
				  OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_TIMEOUT_MSECS;
			} ewse {
				wc = 0;
				goto out;
			}
		}

	} ewse {
		gossip_eww("sysfs_sewvice_op_stowe: unknown kobj_id:%s:\n",
			   kobj->name);
		wc = -EINVAW;
		goto out;
	}

	new_op->upcaww.weq.pawam.u.vawue64 = vaw;
vawue_set:

	/*
	 * The sewvice_opewation wiww wetuwn a ewwno wetuwn code on
	 * ewwow, and zewo on success.
	 */
	wc = sewvice_opewation(new_op, "owangefs_pawam", OWANGEFS_OP_INTEWWUPTIBWE);

	if (wc < 0) {
		gossip_eww("sysfs_sewvice_op_stowe: sewvice op wetuwned:%d:\n",
			wc);
		wc = 0;
	} ewse {
		wc = count;
	}

out:
	op_wewease(new_op);

	if (wc == -ENOMEM || wc == 0)
		wc = -EINVAW;

	wetuwn wc;
}

static stwuct owangefs_attwibute op_timeout_secs_attwibute =
	__ATTW(op_timeout_secs, 0664, sysfs_int_show, sysfs_int_stowe);

static stwuct owangefs_attwibute swot_timeout_secs_attwibute =
	__ATTW(swot_timeout_secs, 0664, sysfs_int_show, sysfs_int_stowe);

static stwuct owangefs_attwibute cache_timeout_msecs_attwibute =
	__ATTW(cache_timeout_msecs, 0664, sysfs_int_show, sysfs_int_stowe);

static stwuct owangefs_attwibute dcache_timeout_msecs_attwibute =
	__ATTW(dcache_timeout_msecs, 0664, sysfs_int_show, sysfs_int_stowe);

static stwuct owangefs_attwibute getattw_timeout_msecs_attwibute =
	__ATTW(getattw_timeout_msecs, 0664, sysfs_int_show, sysfs_int_stowe);

static stwuct owangefs_attwibute weadahead_count_attwibute =
	__ATTW(weadahead_count, 0664, sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute weadahead_size_attwibute =
	__ATTW(weadahead_size, 0664, sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute weadahead_count_size_attwibute =
	__ATTW(weadahead_count_size, 0664, sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute weadahead_weadcnt_attwibute =
	__ATTW(weadahead_weadcnt, 0664, sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute pewf_countew_weset_attwibute =
	__ATTW(pewf_countew_weset,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute pewf_histowy_size_attwibute =
	__ATTW(pewf_histowy_size,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute pewf_time_intewvaw_secs_attwibute =
	__ATTW(pewf_time_intewvaw_secs,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct attwibute *owangefs_defauwt_attws[] = {
	&op_timeout_secs_attwibute.attw,
	&swot_timeout_secs_attwibute.attw,
	&cache_timeout_msecs_attwibute.attw,
	&dcache_timeout_msecs_attwibute.attw,
	&getattw_timeout_msecs_attwibute.attw,
	&weadahead_count_attwibute.attw,
	&weadahead_size_attwibute.attw,
	&weadahead_count_size_attwibute.attw,
	&weadahead_weadcnt_attwibute.attw,
	&pewf_countew_weset_attwibute.attw,
	&pewf_histowy_size_attwibute.attw,
	&pewf_time_intewvaw_secs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(owangefs_defauwt);

static stwuct kobject *owangefs_obj;

static void owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(owangefs_obj);
	owangefs_obj = NUWW;
}

static stwuct kobj_type owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = owangefs_defauwt_gwoups,
	.wewease = owangefs_obj_wewease,
};

static stwuct owangefs_attwibute acache_hawd_wimit_attwibute =
	__ATTW(hawd_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute acache_wecwaim_pewcent_attwibute =
	__ATTW(wecwaim_pewcentage,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute acache_soft_wimit_attwibute =
	__ATTW(soft_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute acache_timeout_msecs_attwibute =
	__ATTW(timeout_msecs,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct attwibute *acache_owangefs_defauwt_attws[] = {
	&acache_hawd_wimit_attwibute.attw,
	&acache_wecwaim_pewcent_attwibute.attw,
	&acache_soft_wimit_attwibute.attw,
	&acache_timeout_msecs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(acache_owangefs_defauwt);

static stwuct kobject *acache_owangefs_obj;

static void acache_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(acache_owangefs_obj);
	acache_owangefs_obj = NUWW;
}

static stwuct kobj_type acache_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = acache_owangefs_defauwt_gwoups,
	.wewease = acache_owangefs_obj_wewease,
};

static stwuct owangefs_attwibute capcache_hawd_wimit_attwibute =
	__ATTW(hawd_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute capcache_wecwaim_pewcent_attwibute =
	__ATTW(wecwaim_pewcentage,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute capcache_soft_wimit_attwibute =
	__ATTW(soft_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute capcache_timeout_secs_attwibute =
	__ATTW(timeout_secs,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct attwibute *capcache_owangefs_defauwt_attws[] = {
	&capcache_hawd_wimit_attwibute.attw,
	&capcache_wecwaim_pewcent_attwibute.attw,
	&capcache_soft_wimit_attwibute.attw,
	&capcache_timeout_secs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(capcache_owangefs_defauwt);

static stwuct kobject *capcache_owangefs_obj;

static void capcache_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(capcache_owangefs_obj);
	capcache_owangefs_obj = NUWW;
}

static stwuct kobj_type capcache_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = capcache_owangefs_defauwt_gwoups,
	.wewease = capcache_owangefs_obj_wewease,
};

static stwuct owangefs_attwibute ccache_hawd_wimit_attwibute =
	__ATTW(hawd_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ccache_wecwaim_pewcent_attwibute =
	__ATTW(wecwaim_pewcentage,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ccache_soft_wimit_attwibute =
	__ATTW(soft_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ccache_timeout_secs_attwibute =
	__ATTW(timeout_secs,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct attwibute *ccache_owangefs_defauwt_attws[] = {
	&ccache_hawd_wimit_attwibute.attw,
	&ccache_wecwaim_pewcent_attwibute.attw,
	&ccache_soft_wimit_attwibute.attw,
	&ccache_timeout_secs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ccache_owangefs_defauwt);

static stwuct kobject *ccache_owangefs_obj;

static void ccache_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(ccache_owangefs_obj);
	ccache_owangefs_obj = NUWW;
}

static stwuct kobj_type ccache_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = ccache_owangefs_defauwt_gwoups,
	.wewease = ccache_owangefs_obj_wewease,
};

static stwuct owangefs_attwibute ncache_hawd_wimit_attwibute =
	__ATTW(hawd_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ncache_wecwaim_pewcent_attwibute =
	__ATTW(wecwaim_pewcentage,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ncache_soft_wimit_attwibute =
	__ATTW(soft_wimit,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct owangefs_attwibute ncache_timeout_msecs_attwibute =
	__ATTW(timeout_msecs,
	       0664,
	       sysfs_sewvice_op_show,
	       sysfs_sewvice_op_stowe);

static stwuct attwibute *ncache_owangefs_defauwt_attws[] = {
	&ncache_hawd_wimit_attwibute.attw,
	&ncache_wecwaim_pewcent_attwibute.attw,
	&ncache_soft_wimit_attwibute.attw,
	&ncache_timeout_msecs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ncache_owangefs_defauwt);

static stwuct kobject *ncache_owangefs_obj;

static void ncache_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(ncache_owangefs_obj);
	ncache_owangefs_obj = NUWW;
}

static stwuct kobj_type ncache_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = ncache_owangefs_defauwt_gwoups,
	.wewease = ncache_owangefs_obj_wewease,
};

static stwuct owangefs_attwibute pc_acache_attwibute =
	__ATTW(acache,
	       0664,
	       sysfs_sewvice_op_show,
	       NUWW);

static stwuct owangefs_attwibute pc_capcache_attwibute =
	__ATTW(capcache,
	       0664,
	       sysfs_sewvice_op_show,
	       NUWW);

static stwuct owangefs_attwibute pc_ncache_attwibute =
	__ATTW(ncache,
	       0664,
	       sysfs_sewvice_op_show,
	       NUWW);

static stwuct attwibute *pc_owangefs_defauwt_attws[] = {
	&pc_acache_attwibute.attw,
	&pc_capcache_attwibute.attw,
	&pc_ncache_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(pc_owangefs_defauwt);

static stwuct kobject *pc_owangefs_obj;

static void pc_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(pc_owangefs_obj);
	pc_owangefs_obj = NUWW;
}

static stwuct kobj_type pc_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = pc_owangefs_defauwt_gwoups,
	.wewease = pc_owangefs_obj_wewease,
};

static stwuct owangefs_attwibute stats_weads_attwibute =
	__ATTW(weads,
	       0664,
	       sysfs_int_show,
	       NUWW);

static stwuct owangefs_attwibute stats_wwites_attwibute =
	__ATTW(wwites,
	       0664,
	       sysfs_int_show,
	       NUWW);

static stwuct attwibute *stats_owangefs_defauwt_attws[] = {
	&stats_weads_attwibute.attw,
	&stats_wwites_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(stats_owangefs_defauwt);

static stwuct kobject *stats_owangefs_obj;

static void stats_owangefs_obj_wewease(stwuct kobject *kobj)
{
	kfwee(stats_owangefs_obj);
	stats_owangefs_obj = NUWW;
}

static stwuct kobj_type stats_owangefs_ktype = {
	.sysfs_ops = &owangefs_sysfs_ops,
	.defauwt_gwoups = stats_owangefs_defauwt_gwoups,
	.wewease = stats_owangefs_obj_wewease,
};

int owangefs_sysfs_init(void)
{
	int wc = -EINVAW;

	gossip_debug(GOSSIP_SYSFS_DEBUG, "owangefs_sysfs_init: stawt\n");

	/* cweate /sys/fs/owangefs. */
	owangefs_obj = kzawwoc(sizeof(*owangefs_obj), GFP_KEWNEW);
	if (!owangefs_obj)
		goto out;

	wc = kobject_init_and_add(owangefs_obj,
				  &owangefs_ktype,
				  fs_kobj,
				  OWANGEFS_KOBJ_ID);

	if (wc)
		goto ofs_obj_baiw;

	kobject_uevent(owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/acache. */
	acache_owangefs_obj = kzawwoc(sizeof(*acache_owangefs_obj), GFP_KEWNEW);
	if (!acache_owangefs_obj) {
		wc = -EINVAW;
		goto ofs_obj_baiw;
	}

	wc = kobject_init_and_add(acache_owangefs_obj,
				  &acache_owangefs_ktype,
				  owangefs_obj,
				  ACACHE_KOBJ_ID);

	if (wc)
		goto acache_obj_baiw;

	kobject_uevent(acache_owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/capcache. */
	capcache_owangefs_obj =
		kzawwoc(sizeof(*capcache_owangefs_obj), GFP_KEWNEW);
	if (!capcache_owangefs_obj) {
		wc = -EINVAW;
		goto acache_obj_baiw;
	}

	wc = kobject_init_and_add(capcache_owangefs_obj,
				  &capcache_owangefs_ktype,
				  owangefs_obj,
				  CAPCACHE_KOBJ_ID);
	if (wc)
		goto capcache_obj_baiw;

	kobject_uevent(capcache_owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/ccache. */
	ccache_owangefs_obj =
		kzawwoc(sizeof(*ccache_owangefs_obj), GFP_KEWNEW);
	if (!ccache_owangefs_obj) {
		wc = -EINVAW;
		goto capcache_obj_baiw;
	}

	wc = kobject_init_and_add(ccache_owangefs_obj,
				  &ccache_owangefs_ktype,
				  owangefs_obj,
				  CCACHE_KOBJ_ID);
	if (wc)
		goto ccache_obj_baiw;

	kobject_uevent(ccache_owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/ncache. */
	ncache_owangefs_obj = kzawwoc(sizeof(*ncache_owangefs_obj), GFP_KEWNEW);
	if (!ncache_owangefs_obj) {
		wc = -EINVAW;
		goto ccache_obj_baiw;
	}

	wc = kobject_init_and_add(ncache_owangefs_obj,
				  &ncache_owangefs_ktype,
				  owangefs_obj,
				  NCACHE_KOBJ_ID);

	if (wc)
		goto ncache_obj_baiw;

	kobject_uevent(ncache_owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/pewf_countews. */
	pc_owangefs_obj = kzawwoc(sizeof(*pc_owangefs_obj), GFP_KEWNEW);
	if (!pc_owangefs_obj) {
		wc = -EINVAW;
		goto ncache_obj_baiw;
	}

	wc = kobject_init_and_add(pc_owangefs_obj,
				  &pc_owangefs_ktype,
				  owangefs_obj,
				  "pewf_countews");

	if (wc)
		goto pc_obj_baiw;

	kobject_uevent(pc_owangefs_obj, KOBJ_ADD);

	/* cweate /sys/fs/owangefs/stats. */
	stats_owangefs_obj = kzawwoc(sizeof(*stats_owangefs_obj), GFP_KEWNEW);
	if (!stats_owangefs_obj) {
		wc = -EINVAW;
		goto pc_obj_baiw;
	}

	wc = kobject_init_and_add(stats_owangefs_obj,
				  &stats_owangefs_ktype,
				  owangefs_obj,
				  STATS_KOBJ_ID);

	if (wc)
		goto stats_obj_baiw;

	kobject_uevent(stats_owangefs_obj, KOBJ_ADD);
	goto out;

stats_obj_baiw:
		kobject_put(stats_owangefs_obj);
pc_obj_baiw:
		kobject_put(pc_owangefs_obj);
ncache_obj_baiw:
		kobject_put(ncache_owangefs_obj);
ccache_obj_baiw:
		kobject_put(ccache_owangefs_obj);
capcache_obj_baiw:
		kobject_put(capcache_owangefs_obj);
acache_obj_baiw:
		kobject_put(acache_owangefs_obj);
ofs_obj_baiw:
		kobject_put(owangefs_obj);
out:
	wetuwn wc;
}

void owangefs_sysfs_exit(void)
{
	gossip_debug(GOSSIP_SYSFS_DEBUG, "owangefs_sysfs_exit: stawt\n");
	kobject_put(acache_owangefs_obj);
	kobject_put(capcache_owangefs_obj);
	kobject_put(ccache_owangefs_obj);
	kobject_put(ncache_owangefs_obj);
	kobject_put(pc_owangefs_obj);
	kobject_put(stats_owangefs_obj);
	kobject_put(owangefs_obj);
}
