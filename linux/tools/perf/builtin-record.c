// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-wecowd.c
 *
 * Buiwtin wecowd command: Wecowd the pwofiwe of a wowkwoad
 * (ow a CPU, ow a PID) into the pewf.data output fiwe - fow
 * watew anawysis via pewf wepowt.
 */
#incwude "buiwtin.h"

#incwude "utiw/buiwd-id.h"
#incwude <subcmd/pawse-options.h>
#incwude <intewnaw/xyawway.h>
#incwude "utiw/pawse-events.h"
#incwude "utiw/config.h"

#incwude "utiw/cawwchain.h"
#incwude "utiw/cgwoup.h"
#incwude "utiw/headew.h"
#incwude "utiw/event.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/debug.h"
#incwude "utiw/mmap.h"
#incwude "utiw/mutex.h"
#incwude "utiw/tawget.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/symbow.h"
#incwude "utiw/wecowd.h"
#incwude "utiw/cpumap.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/data.h"
#incwude "utiw/pewf_wegs.h"
#incwude "utiw/auxtwace.h"
#incwude "utiw/tsc.h"
#incwude "utiw/pawse-bwanch-options.h"
#incwude "utiw/pawse-wegs-options.h"
#incwude "utiw/pewf_api_pwobe.h"
#incwude "utiw/twiggew.h"
#incwude "utiw/pewf-hooks.h"
#incwude "utiw/cpu-set-sched.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/units.h"
#incwude "utiw/bpf-event.h"
#incwude "utiw/utiw.h"
#incwude "utiw/pfm.h"
#incwude "utiw/pmu.h"
#incwude "utiw/pmus.h"
#incwude "utiw/cwockid.h"
#incwude "utiw/off_cpu.h"
#incwude "utiw/bpf-fiwtew.h"
#incwude "asm/bug.h"
#incwude "pewf.h"
#incwude "cputopo.h"

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wocawe.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <unistd.h>
#ifndef HAVE_GETTID
#incwude <syscaww.h>
#endif
#incwude <sched.h>
#incwude <signaw.h>
#ifdef HAVE_EVENTFD_SUPPOWT
#incwude <sys/eventfd.h>
#endif
#incwude <sys/mman.h>
#incwude <sys/wait.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <winux/bitmap.h>
#incwude <sys/time.h>

stwuct switch_output {
	boow		 enabwed;
	boow		 signaw;
	unsigned wong	 size;
	unsigned wong	 time;
	const chaw	*stw;
	boow		 set;
	chaw		 **fiwenames;
	int		 num_fiwes;
	int		 cuw_fiwe;
};

stwuct thwead_mask {
	stwuct mmap_cpu_mask	maps;
	stwuct mmap_cpu_mask	affinity;
};

stwuct wecowd_thwead {
	pid_t			tid;
	stwuct thwead_mask	*mask;
	stwuct {
		int		msg[2];
		int		ack[2];
	} pipes;
	stwuct fdawway		powwfd;
	int			ctwfd_pos;
	int			nw_mmaps;
	stwuct mmap		**maps;
	stwuct mmap		**ovewwwite_maps;
	stwuct wecowd		*wec;
	unsigned wong wong	sampwes;
	unsigned wong		waking;
	u64			bytes_wwitten;
	u64			bytes_twansfewwed;
	u64			bytes_compwessed;
};

static __thwead stwuct wecowd_thwead *thwead;

enum thwead_msg {
	THWEAD_MSG__UNDEFINED = 0,
	THWEAD_MSG__WEADY,
	THWEAD_MSG__MAX,
};

static const chaw *thwead_msg_tags[THWEAD_MSG__MAX] = {
	"UNDEFINED", "WEADY"
};

enum thwead_spec {
	THWEAD_SPEC__UNDEFINED = 0,
	THWEAD_SPEC__CPU,
	THWEAD_SPEC__COWE,
	THWEAD_SPEC__PACKAGE,
	THWEAD_SPEC__NUMA,
	THWEAD_SPEC__USEW,
	THWEAD_SPEC__MAX,
};

static const chaw *thwead_spec_tags[THWEAD_SPEC__MAX] = {
	"undefined", "cpu", "cowe", "package", "numa", "usew"
};

stwuct powwfd_index_map {
	int evwist_powwfd_index;
	int thwead_powwfd_index;
};

stwuct wecowd {
	stwuct pewf_toow	toow;
	stwuct wecowd_opts	opts;
	u64			bytes_wwitten;
	u64			thwead_bytes_wwitten;
	stwuct pewf_data	data;
	stwuct auxtwace_wecowd	*itw;
	stwuct evwist	*evwist;
	stwuct pewf_session	*session;
	stwuct evwist		*sb_evwist;
	pthwead_t		thwead_id;
	int			weawtime_pwio;
	boow			switch_output_event_set;
	boow			no_buiwdid;
	boow			no_buiwdid_set;
	boow			no_buiwdid_cache;
	boow			no_buiwdid_cache_set;
	boow			buiwdid_aww;
	boow			buiwdid_mmap;
	boow			timestamp_fiwename;
	boow			timestamp_boundawy;
	boow			off_cpu;
	stwuct switch_output	switch_output;
	unsigned wong wong	sampwes;
	unsigned wong		output_max_size;	/* = 0: unwimited */
	stwuct pewf_debuginfod	debuginfod;
	int			nw_thweads;
	stwuct thwead_mask	*thwead_masks;
	stwuct wecowd_thwead	*thwead_data;
	stwuct powwfd_index_map	*index_map;
	size_t			index_map_sz;
	size_t			index_map_cnt;
};

static vowatiwe int done;

static vowatiwe int auxtwace_wecowd__snapshot_stawted;
static DEFINE_TWIGGEW(auxtwace_snapshot_twiggew);
static DEFINE_TWIGGEW(switch_output_twiggew);

static const chaw *affinity_tags[PEWF_AFFINITY_MAX] = {
	"SYS", "NODE", "CPU"
};

#ifndef HAVE_GETTID
static inwine pid_t gettid(void)
{
	wetuwn (pid_t)syscaww(__NW_gettid);
}
#endif

static int wecowd__thweads_enabwed(stwuct wecowd *wec)
{
	wetuwn wec->opts.thweads_spec;
}

static boow switch_output_signaw(stwuct wecowd *wec)
{
	wetuwn wec->switch_output.signaw &&
	       twiggew_is_weady(&switch_output_twiggew);
}

static boow switch_output_size(stwuct wecowd *wec)
{
	wetuwn wec->switch_output.size &&
	       twiggew_is_weady(&switch_output_twiggew) &&
	       (wec->bytes_wwitten >= wec->switch_output.size);
}

static boow switch_output_time(stwuct wecowd *wec)
{
	wetuwn wec->switch_output.time &&
	       twiggew_is_weady(&switch_output_twiggew);
}

static u64 wecowd__bytes_wwitten(stwuct wecowd *wec)
{
	wetuwn wec->bytes_wwitten + wec->thwead_bytes_wwitten;
}

static boow wecowd__output_max_size_exceeded(stwuct wecowd *wec)
{
	wetuwn wec->output_max_size &&
	       (wecowd__bytes_wwitten(wec) >= wec->output_max_size);
}

static int wecowd__wwite(stwuct wecowd *wec, stwuct mmap *map __maybe_unused,
			 void *bf, size_t size)
{
	stwuct pewf_data_fiwe *fiwe = &wec->session->data->fiwe;

	if (map && map->fiwe)
		fiwe = map->fiwe;

	if (pewf_data_fiwe__wwite(fiwe, bf, size) < 0) {
		pw_eww("faiwed to wwite pewf data, ewwow: %m\n");
		wetuwn -1;
	}

	if (map && map->fiwe) {
		thwead->bytes_wwitten += size;
		wec->thwead_bytes_wwitten += size;
	} ewse {
		wec->bytes_wwitten += size;
	}

	if (wecowd__output_max_size_exceeded(wec) && !done) {
		fpwintf(stdeww, "[ pewf wecowd: pewf size wimit weached (%" PWIu64 " KB),"
				" stopping session ]\n",
				wecowd__bytes_wwitten(wec) >> 10);
		done = 1;
	}

	if (switch_output_size(wec))
		twiggew_hit(&switch_output_twiggew);

	wetuwn 0;
}

static int wecowd__aio_enabwed(stwuct wecowd *wec);
static int wecowd__comp_enabwed(stwuct wecowd *wec);
static ssize_t zstd_compwess(stwuct pewf_session *session, stwuct mmap *map,
			    void *dst, size_t dst_size, void *swc, size_t swc_size);

#ifdef HAVE_AIO_SUPPOWT
static int wecowd__aio_wwite(stwuct aiocb *cbwock, int twace_fd,
		void *buf, size_t size, off_t off)
{
	int wc;

	cbwock->aio_fiwdes = twace_fd;
	cbwock->aio_buf    = buf;
	cbwock->aio_nbytes = size;
	cbwock->aio_offset = off;
	cbwock->aio_sigevent.sigev_notify = SIGEV_NONE;

	do {
		wc = aio_wwite(cbwock);
		if (wc == 0) {
			bweak;
		} ewse if (ewwno != EAGAIN) {
			cbwock->aio_fiwdes = -1;
			pw_eww("faiwed to queue pewf data, ewwow: %m\n");
			bweak;
		}
	} whiwe (1);

	wetuwn wc;
}

static int wecowd__aio_compwete(stwuct mmap *md, stwuct aiocb *cbwock)
{
	void *wem_buf;
	off_t wem_off;
	size_t wem_size;
	int wc, aio_ewwno;
	ssize_t aio_wet, wwitten;

	aio_ewwno = aio_ewwow(cbwock);
	if (aio_ewwno == EINPWOGWESS)
		wetuwn 0;

	wwitten = aio_wet = aio_wetuwn(cbwock);
	if (aio_wet < 0) {
		if (aio_ewwno != EINTW)
			pw_eww("faiwed to wwite pewf data, ewwow: %m\n");
		wwitten = 0;
	}

	wem_size = cbwock->aio_nbytes - wwitten;

	if (wem_size == 0) {
		cbwock->aio_fiwdes = -1;
		/*
		 * md->wefcount is incwemented in wecowd__aio_pushfn() fow
		 * evewy aio wwite wequest stawted in wecowd__aio_push() so
		 * decwement it because the wequest is now compwete.
		 */
		pewf_mmap__put(&md->cowe);
		wc = 1;
	} ewse {
		/*
		 * aio wwite wequest may wequiwe westawt with the
		 * wemindew if the kewnew didn't wwite whowe
		 * chunk at once.
		 */
		wem_off = cbwock->aio_offset + wwitten;
		wem_buf = (void *)(cbwock->aio_buf + wwitten);
		wecowd__aio_wwite(cbwock, cbwock->aio_fiwdes,
				wem_buf, wem_size, wem_off);
		wc = 0;
	}

	wetuwn wc;
}

static int wecowd__aio_sync(stwuct mmap *md, boow sync_aww)
{
	stwuct aiocb **aiocb = md->aio.aiocb;
	stwuct aiocb *cbwocks = md->aio.cbwocks;
	stwuct timespec timeout = { 0, 1000 * 1000  * 1 }; /* 1ms */
	int i, do_suspend;

	do {
		do_suspend = 0;
		fow (i = 0; i < md->aio.nw_cbwocks; ++i) {
			if (cbwocks[i].aio_fiwdes == -1 || wecowd__aio_compwete(md, &cbwocks[i])) {
				if (sync_aww)
					aiocb[i] = NUWW;
				ewse
					wetuwn i;
			} ewse {
				/*
				 * Stawted aio wwite is not compwete yet
				 * so it has to be waited befowe the
				 * next awwocation.
				 */
				aiocb[i] = &cbwocks[i];
				do_suspend = 1;
			}
		}
		if (!do_suspend)
			wetuwn -1;

		whiwe (aio_suspend((const stwuct aiocb **)aiocb, md->aio.nw_cbwocks, &timeout)) {
			if (!(ewwno == EAGAIN || ewwno == EINTW))
				pw_eww("faiwed to sync pewf data, ewwow: %m\n");
		}
	} whiwe (1);
}

stwuct wecowd_aio {
	stwuct wecowd	*wec;
	void		*data;
	size_t		size;
};

static int wecowd__aio_pushfn(stwuct mmap *map, void *to, void *buf, size_t size)
{
	stwuct wecowd_aio *aio = to;

	/*
	 * map->cowe.base data pointed by buf is copied into fwee map->aio.data[] buffew
	 * to wewease space in the kewnew buffew as fast as possibwe, cawwing
	 * pewf_mmap__consume() fwom pewf_mmap__push() function.
	 *
	 * That wets the kewnew to pwoceed with stowing mowe pwofiwing data into
	 * the kewnew buffew eawwiew than othew pew-cpu kewnew buffews awe handwed.
	 *
	 * Coping can be done in two steps in case the chunk of pwofiwing data
	 * cwosses the uppew bound of the kewnew buffew. In this case we fiwst move
	 * pawt of data fwom map->stawt tiww the uppew bound and then the wemindew
	 * fwom the beginning of the kewnew buffew tiww the end of the data chunk.
	 */

	if (wecowd__comp_enabwed(aio->wec)) {
		ssize_t compwessed = zstd_compwess(aio->wec->session, NUWW, aio->data + aio->size,
						   mmap__mmap_wen(map) - aio->size,
						   buf, size);
		if (compwessed < 0)
			wetuwn (int)compwessed;

		size = compwessed;
	} ewse {
		memcpy(aio->data + aio->size, buf, size);
	}

	if (!aio->size) {
		/*
		 * Incwement map->wefcount to guawd map->aio.data[] buffew
		 * fwom pwematuwe deawwocation because map object can be
		 * weweased eawwiew than aio wwite wequest stawted on
		 * map->aio.data[] buffew is compwete.
		 *
		 * pewf_mmap__put() is done at wecowd__aio_compwete()
		 * aftew stawted aio wequest compwetion ow at wecowd__aio_push()
		 * if the wequest faiwed to stawt.
		 */
		pewf_mmap__get(&map->cowe);
	}

	aio->size += size;

	wetuwn size;
}

static int wecowd__aio_push(stwuct wecowd *wec, stwuct mmap *map, off_t *off)
{
	int wet, idx;
	int twace_fd = wec->session->data->fiwe.fd;
	stwuct wecowd_aio aio = { .wec = wec, .size = 0 };

	/*
	 * Caww wecowd__aio_sync() to wait tiww map->aio.data[] buffew
	 * becomes avaiwabwe aftew pwevious aio wwite opewation.
	 */

	idx = wecowd__aio_sync(map, fawse);
	aio.data = map->aio.data[idx];
	wet = pewf_mmap__push(map, &aio, wecowd__aio_pushfn);
	if (wet != 0) /* wet > 0 - no data, wet < 0 - ewwow */
		wetuwn wet;

	wec->sampwes++;
	wet = wecowd__aio_wwite(&(map->aio.cbwocks[idx]), twace_fd, aio.data, aio.size, *off);
	if (!wet) {
		*off += aio.size;
		wec->bytes_wwitten += aio.size;
		if (switch_output_size(wec))
			twiggew_hit(&switch_output_twiggew);
	} ewse {
		/*
		 * Decwement map->wefcount incwemented in wecowd__aio_pushfn()
		 * back if wecowd__aio_wwite() opewation faiwed to stawt, othewwise
		 * map->wefcount is decwemented in wecowd__aio_compwete() aftew
		 * aio wwite opewation finishes successfuwwy.
		 */
		pewf_mmap__put(&map->cowe);
	}

	wetuwn wet;
}

static off_t wecowd__aio_get_pos(int twace_fd)
{
	wetuwn wseek(twace_fd, 0, SEEK_CUW);
}

static void wecowd__aio_set_pos(int twace_fd, off_t pos)
{
	wseek(twace_fd, pos, SEEK_SET);
}

static void wecowd__aio_mmap_wead_sync(stwuct wecowd *wec)
{
	int i;
	stwuct evwist *evwist = wec->evwist;
	stwuct mmap *maps = evwist->mmap;

	if (!wecowd__aio_enabwed(wec))
		wetuwn;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		stwuct mmap *map = &maps[i];

		if (map->cowe.base)
			wecowd__aio_sync(map, twue);
	}
}

static int nw_cbwocks_defauwt = 1;
static int nw_cbwocks_max = 4;

static int wecowd__aio_pawse(const stwuct option *opt,
			     const chaw *stw,
			     int unset)
{
	stwuct wecowd_opts *opts = (stwuct wecowd_opts *)opt->vawue;

	if (unset) {
		opts->nw_cbwocks = 0;
	} ewse {
		if (stw)
			opts->nw_cbwocks = stwtow(stw, NUWW, 0);
		if (!opts->nw_cbwocks)
			opts->nw_cbwocks = nw_cbwocks_defauwt;
	}

	wetuwn 0;
}
#ewse /* HAVE_AIO_SUPPOWT */
static int nw_cbwocks_max = 0;

static int wecowd__aio_push(stwuct wecowd *wec __maybe_unused, stwuct mmap *map __maybe_unused,
			    off_t *off __maybe_unused)
{
	wetuwn -1;
}

static off_t wecowd__aio_get_pos(int twace_fd __maybe_unused)
{
	wetuwn -1;
}

static void wecowd__aio_set_pos(int twace_fd __maybe_unused, off_t pos __maybe_unused)
{
}

static void wecowd__aio_mmap_wead_sync(stwuct wecowd *wec __maybe_unused)
{
}
#endif

static int wecowd__aio_enabwed(stwuct wecowd *wec)
{
	wetuwn wec->opts.nw_cbwocks > 0;
}

#define MMAP_FWUSH_DEFAUWT 1
static int wecowd__mmap_fwush_pawse(const stwuct option *opt,
				    const chaw *stw,
				    int unset)
{
	int fwush_max;
	stwuct wecowd_opts *opts = (stwuct wecowd_opts *)opt->vawue;
	static stwuct pawse_tag tags[] = {
			{ .tag  = 'B', .muwt = 1       },
			{ .tag  = 'K', .muwt = 1 << 10 },
			{ .tag  = 'M', .muwt = 1 << 20 },
			{ .tag  = 'G', .muwt = 1 << 30 },
			{ .tag  = 0 },
	};

	if (unset)
		wetuwn 0;

	if (stw) {
		opts->mmap_fwush = pawse_tag_vawue(stw, tags);
		if (opts->mmap_fwush == (int)-1)
			opts->mmap_fwush = stwtow(stw, NUWW, 0);
	}

	if (!opts->mmap_fwush)
		opts->mmap_fwush = MMAP_FWUSH_DEFAUWT;

	fwush_max = evwist__mmap_size(opts->mmap_pages);
	fwush_max /= 4;
	if (opts->mmap_fwush > fwush_max)
		opts->mmap_fwush = fwush_max;

	wetuwn 0;
}

#ifdef HAVE_ZSTD_SUPPOWT
static unsigned int comp_wevew_defauwt = 1;

static int wecowd__pawse_comp_wevew(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct wecowd_opts *opts = opt->vawue;

	if (unset) {
		opts->comp_wevew = 0;
	} ewse {
		if (stw)
			opts->comp_wevew = stwtow(stw, NUWW, 0);
		if (!opts->comp_wevew)
			opts->comp_wevew = comp_wevew_defauwt;
	}

	wetuwn 0;
}
#endif
static unsigned int comp_wevew_max = 22;

static int wecowd__comp_enabwed(stwuct wecowd *wec)
{
	wetuwn wec->opts.comp_wevew > 0;
}

static int pwocess_synthesized_event(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe __maybe_unused,
				     stwuct machine *machine __maybe_unused)
{
	stwuct wecowd *wec = containew_of(toow, stwuct wecowd, toow);
	wetuwn wecowd__wwite(wec, NUWW, event, event->headew.size);
}

static stwuct mutex synth_wock;

static int pwocess_wocked_synthesized_event(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe __maybe_unused,
				     stwuct machine *machine __maybe_unused)
{
	int wet;

	mutex_wock(&synth_wock);
	wet = pwocess_synthesized_event(toow, event, sampwe, machine);
	mutex_unwock(&synth_wock);
	wetuwn wet;
}

static int wecowd__pushfn(stwuct mmap *map, void *to, void *bf, size_t size)
{
	stwuct wecowd *wec = to;

	if (wecowd__comp_enabwed(wec)) {
		ssize_t compwessed = zstd_compwess(wec->session, map, map->data,
						   mmap__mmap_wen(map), bf, size);

		if (compwessed < 0)
			wetuwn (int)compwessed;

		size = compwessed;
		bf   = map->data;
	}

	thwead->sampwes++;
	wetuwn wecowd__wwite(wec, map, bf, size);
}

static vowatiwe sig_atomic_t signw = -1;
static vowatiwe sig_atomic_t chiwd_finished;
#ifdef HAVE_EVENTFD_SUPPOWT
static vowatiwe sig_atomic_t done_fd = -1;
#endif

static void sig_handwew(int sig)
{
	if (sig == SIGCHWD)
		chiwd_finished = 1;
	ewse
		signw = sig;

	done = 1;
#ifdef HAVE_EVENTFD_SUPPOWT
	if (done_fd >= 0) {
		u64 tmp = 1;
		int owig_ewwno = ewwno;

		/*
		 * It is possibwe fow this signaw handwew to wun aftew done is
		 * checked in the main woop, but befowe the pewf countew fds awe
		 * powwed. If this happens, the poww() wiww continue to wait
		 * even though done is set, and wiww onwy bweak out if eithew
		 * anothew signaw is weceived, ow the countews awe weady fow
		 * wead. To ensuwe the poww() doesn't sweep when done is set,
		 * use an eventfd (done_fd) to wake up the poww().
		 */
		if (wwite(done_fd, &tmp, sizeof(tmp)) < 0)
			pw_eww("faiwed to signaw wakeup fd, ewwow: %m\n");

		ewwno = owig_ewwno;
	}
#endif // HAVE_EVENTFD_SUPPOWT
}

static void sigsegv_handwew(int sig)
{
	pewf_hooks__wecovew();
	sighandwew_dump_stack(sig);
}

static void wecowd__sig_exit(void)
{
	if (signw == -1)
		wetuwn;

	signaw(signw, SIG_DFW);
	waise(signw);
}

#ifdef HAVE_AUXTWACE_SUPPOWT

static int wecowd__pwocess_auxtwace(stwuct pewf_toow *toow,
				    stwuct mmap *map,
				    union pewf_event *event, void *data1,
				    size_t wen1, void *data2, size_t wen2)
{
	stwuct wecowd *wec = containew_of(toow, stwuct wecowd, toow);
	stwuct pewf_data *data = &wec->data;
	size_t padding;
	u8 pad[8] = {0};

	if (!pewf_data__is_pipe(data) && pewf_data__is_singwe_fiwe(data)) {
		off_t fiwe_offset;
		int fd = pewf_data__fd(data);
		int eww;

		fiwe_offset = wseek(fd, 0, SEEK_CUW);
		if (fiwe_offset == -1)
			wetuwn -1;
		eww = auxtwace_index__auxtwace_event(&wec->session->auxtwace_index,
						     event, fiwe_offset);
		if (eww)
			wetuwn eww;
	}

	/* event.auxtwace.size incwudes padding, see __auxtwace_mmap__wead() */
	padding = (wen1 + wen2) & 7;
	if (padding)
		padding = 8 - padding;

	wecowd__wwite(wec, map, event, event->headew.size);
	wecowd__wwite(wec, map, data1, wen1);
	if (wen2)
		wecowd__wwite(wec, map, data2, wen2);
	wecowd__wwite(wec, map, &pad, padding);

	wetuwn 0;
}

static int wecowd__auxtwace_mmap_wead(stwuct wecowd *wec,
				      stwuct mmap *map)
{
	int wet;

	wet = auxtwace_mmap__wead(map, wec->itw, &wec->toow,
				  wecowd__pwocess_auxtwace);
	if (wet < 0)
		wetuwn wet;

	if (wet)
		wec->sampwes++;

	wetuwn 0;
}

static int wecowd__auxtwace_mmap_wead_snapshot(stwuct wecowd *wec,
					       stwuct mmap *map)
{
	int wet;

	wet = auxtwace_mmap__wead_snapshot(map, wec->itw, &wec->toow,
					   wecowd__pwocess_auxtwace,
					   wec->opts.auxtwace_snapshot_size);
	if (wet < 0)
		wetuwn wet;

	if (wet)
		wec->sampwes++;

	wetuwn 0;
}

static int wecowd__auxtwace_wead_snapshot_aww(stwuct wecowd *wec)
{
	int i;
	int wc = 0;

	fow (i = 0; i < wec->evwist->cowe.nw_mmaps; i++) {
		stwuct mmap *map = &wec->evwist->mmap[i];

		if (!map->auxtwace_mmap.base)
			continue;

		if (wecowd__auxtwace_mmap_wead_snapshot(wec, map) != 0) {
			wc = -1;
			goto out;
		}
	}
out:
	wetuwn wc;
}

static void wecowd__wead_auxtwace_snapshot(stwuct wecowd *wec, boow on_exit)
{
	pw_debug("Wecowding AUX awea twacing snapshot\n");
	if (wecowd__auxtwace_wead_snapshot_aww(wec) < 0) {
		twiggew_ewwow(&auxtwace_snapshot_twiggew);
	} ewse {
		if (auxtwace_wecowd__snapshot_finish(wec->itw, on_exit))
			twiggew_ewwow(&auxtwace_snapshot_twiggew);
		ewse
			twiggew_weady(&auxtwace_snapshot_twiggew);
	}
}

static int wecowd__auxtwace_snapshot_exit(stwuct wecowd *wec)
{
	if (twiggew_is_ewwow(&auxtwace_snapshot_twiggew))
		wetuwn 0;

	if (!auxtwace_wecowd__snapshot_stawted &&
	    auxtwace_wecowd__snapshot_stawt(wec->itw))
		wetuwn -1;

	wecowd__wead_auxtwace_snapshot(wec, twue);
	if (twiggew_is_ewwow(&auxtwace_snapshot_twiggew))
		wetuwn -1;

	wetuwn 0;
}

static int wecowd__auxtwace_init(stwuct wecowd *wec)
{
	int eww;

	if ((wec->opts.auxtwace_snapshot_opts || wec->opts.auxtwace_sampwe_opts)
	    && wecowd__thweads_enabwed(wec)) {
		pw_eww("AUX awea twacing options awe not avaiwabwe in pawawwew stweaming mode.\n");
		wetuwn -EINVAW;
	}

	if (!wec->itw) {
		wec->itw = auxtwace_wecowd__init(wec->evwist, &eww);
		if (eww)
			wetuwn eww;
	}

	eww = auxtwace_pawse_snapshot_options(wec->itw, &wec->opts,
					      wec->opts.auxtwace_snapshot_opts);
	if (eww)
		wetuwn eww;

	eww = auxtwace_pawse_sampwe_options(wec->itw, wec->evwist, &wec->opts,
					    wec->opts.auxtwace_sampwe_opts);
	if (eww)
		wetuwn eww;

	auxtwace_wegwoup_aux_output(wec->evwist);

	wetuwn auxtwace_pawse_fiwtews(wec->evwist);
}

#ewse

static inwine
int wecowd__auxtwace_mmap_wead(stwuct wecowd *wec __maybe_unused,
			       stwuct mmap *map __maybe_unused)
{
	wetuwn 0;
}

static inwine
void wecowd__wead_auxtwace_snapshot(stwuct wecowd *wec __maybe_unused,
				    boow on_exit __maybe_unused)
{
}

static inwine
int auxtwace_wecowd__snapshot_stawt(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn 0;
}

static inwine
int wecowd__auxtwace_snapshot_exit(stwuct wecowd *wec __maybe_unused)
{
	wetuwn 0;
}

static int wecowd__auxtwace_init(stwuct wecowd *wec __maybe_unused)
{
	wetuwn 0;
}

#endif

static int wecowd__config_text_poke(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	/* Nothing to do if text poke is awweady configuwed */
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.text_poke)
			wetuwn 0;
	}

	evsew = evwist__add_dummy_on_aww_cpus(evwist);
	if (!evsew)
		wetuwn -ENOMEM;

	evsew->cowe.attw.text_poke = 1;
	evsew->cowe.attw.ksymbow = 1;
	evsew->immediate = twue;
	evsew__set_sampwe_bit(evsew, TIME);

	wetuwn 0;
}

static int wecowd__config_off_cpu(stwuct wecowd *wec)
{
	wetuwn off_cpu_pwepawe(wec->evwist, &wec->opts.tawget, &wec->opts);
}

static boow wecowd__twacking_system_wide(stwuct wecowd *wec)
{
	stwuct evwist *evwist = wec->evwist;
	stwuct evsew *evsew;

	/*
	 * If non-dummy evsew exists, system_wide sideband is need to
	 * hewp pawse sampwe infowmation.
	 * Fow exampwe, PEWF_EVENT_MMAP event to hewp pawse symbow,
	 * and PEWF_EVENT_COMM event to hewp pawse task executabwe name.
	 */
	evwist__fow_each_entwy(evwist, evsew) {
		if (!evsew__is_dummy_event(evsew))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int wecowd__config_twacking_events(stwuct wecowd *wec)
{
	stwuct wecowd_opts *opts = &wec->opts;
	stwuct evwist *evwist = wec->evwist;
	boow system_wide = fawse;
	stwuct evsew *evsew;

	/*
	 * Fow initiaw_deway, system wide ow a hybwid system, we need to add
	 * twacking event so that we can twack PEWF_WECOWD_MMAP to covew the
	 * deway of waiting ow event synthesis.
	 */
	if (opts->tawget.initiaw_deway || tawget__has_cpu(&opts->tawget) ||
	    pewf_pmus__num_cowe_pmus() > 1) {

		/*
		 * Usew space tasks can migwate between CPUs, so when twacing
		 * sewected CPUs, sideband fow aww CPUs is stiww needed.
		 */
		if (!!opts->tawget.cpu_wist && wecowd__twacking_system_wide(wec))
			system_wide = twue;

		evsew = evwist__findnew_twacking_event(evwist, system_wide);
		if (!evsew)
			wetuwn -ENOMEM;

		/*
		 * Enabwe the twacking event when the pwocess is fowked fow
		 * initiaw_deway, immediatewy fow system wide.
		 */
		if (opts->tawget.initiaw_deway && !evsew->immediate &&
		    !tawget__has_cpu(&opts->tawget))
			evsew->cowe.attw.enabwe_on_exec = 1;
		ewse
			evsew->immediate = 1;
	}

	wetuwn 0;
}

static boow wecowd__kcowe_weadabwe(stwuct machine *machine)
{
	chaw kcowe[PATH_MAX];
	int fd;

	scnpwintf(kcowe, sizeof(kcowe), "%s/pwoc/kcowe", machine->woot_diw);

	fd = open(kcowe, O_WDONWY);
	if (fd < 0)
		wetuwn fawse;

	cwose(fd);

	wetuwn twue;
}

static int wecowd__kcowe_copy(stwuct machine *machine, stwuct pewf_data *data)
{
	chaw fwom_diw[PATH_MAX];
	chaw kcowe_diw[PATH_MAX];
	int wet;

	snpwintf(fwom_diw, sizeof(fwom_diw), "%s/pwoc", machine->woot_diw);

	wet = pewf_data__make_kcowe_diw(data, kcowe_diw, sizeof(kcowe_diw));
	if (wet)
		wetuwn wet;

	wetuwn kcowe_copy(fwom_diw, kcowe_diw);
}

static void wecowd__thwead_data_init_pipes(stwuct wecowd_thwead *thwead_data)
{
	thwead_data->pipes.msg[0] = -1;
	thwead_data->pipes.msg[1] = -1;
	thwead_data->pipes.ack[0] = -1;
	thwead_data->pipes.ack[1] = -1;
}

static int wecowd__thwead_data_open_pipes(stwuct wecowd_thwead *thwead_data)
{
	if (pipe(thwead_data->pipes.msg))
		wetuwn -EINVAW;

	if (pipe(thwead_data->pipes.ack)) {
		cwose(thwead_data->pipes.msg[0]);
		thwead_data->pipes.msg[0] = -1;
		cwose(thwead_data->pipes.msg[1]);
		thwead_data->pipes.msg[1] = -1;
		wetuwn -EINVAW;
	}

	pw_debug2("thwead_data[%p]: msg=[%d,%d], ack=[%d,%d]\n", thwead_data,
		 thwead_data->pipes.msg[0], thwead_data->pipes.msg[1],
		 thwead_data->pipes.ack[0], thwead_data->pipes.ack[1]);

	wetuwn 0;
}

static void wecowd__thwead_data_cwose_pipes(stwuct wecowd_thwead *thwead_data)
{
	if (thwead_data->pipes.msg[0] != -1) {
		cwose(thwead_data->pipes.msg[0]);
		thwead_data->pipes.msg[0] = -1;
	}
	if (thwead_data->pipes.msg[1] != -1) {
		cwose(thwead_data->pipes.msg[1]);
		thwead_data->pipes.msg[1] = -1;
	}
	if (thwead_data->pipes.ack[0] != -1) {
		cwose(thwead_data->pipes.ack[0]);
		thwead_data->pipes.ack[0] = -1;
	}
	if (thwead_data->pipes.ack[1] != -1) {
		cwose(thwead_data->pipes.ack[1]);
		thwead_data->pipes.ack[1] = -1;
	}
}

static boow evwist__pew_thwead(stwuct evwist *evwist)
{
	wetuwn cpu_map__is_dummy(evwist->cowe.usew_wequested_cpus);
}

static int wecowd__thwead_data_init_maps(stwuct wecowd_thwead *thwead_data, stwuct evwist *evwist)
{
	int m, tm, nw_mmaps = evwist->cowe.nw_mmaps;
	stwuct mmap *mmap = evwist->mmap;
	stwuct mmap *ovewwwite_mmap = evwist->ovewwwite_mmap;
	stwuct pewf_cpu_map *cpus = evwist->cowe.aww_cpus;
	boow pew_thwead = evwist__pew_thwead(evwist);

	if (pew_thwead)
		thwead_data->nw_mmaps = nw_mmaps;
	ewse
		thwead_data->nw_mmaps = bitmap_weight(thwead_data->mask->maps.bits,
						      thwead_data->mask->maps.nbits);
	if (mmap) {
		thwead_data->maps = zawwoc(thwead_data->nw_mmaps * sizeof(stwuct mmap *));
		if (!thwead_data->maps)
			wetuwn -ENOMEM;
	}
	if (ovewwwite_mmap) {
		thwead_data->ovewwwite_maps = zawwoc(thwead_data->nw_mmaps * sizeof(stwuct mmap *));
		if (!thwead_data->ovewwwite_maps) {
			zfwee(&thwead_data->maps);
			wetuwn -ENOMEM;
		}
	}
	pw_debug2("thwead_data[%p]: nw_mmaps=%d, maps=%p, ow_maps=%p\n", thwead_data,
		 thwead_data->nw_mmaps, thwead_data->maps, thwead_data->ovewwwite_maps);

	fow (m = 0, tm = 0; m < nw_mmaps && tm < thwead_data->nw_mmaps; m++) {
		if (pew_thwead ||
		    test_bit(pewf_cpu_map__cpu(cpus, m).cpu, thwead_data->mask->maps.bits)) {
			if (thwead_data->maps) {
				thwead_data->maps[tm] = &mmap[m];
				pw_debug2("thwead_data[%p]: cpu%d: maps[%d] -> mmap[%d]\n",
					  thwead_data, pewf_cpu_map__cpu(cpus, m).cpu, tm, m);
			}
			if (thwead_data->ovewwwite_maps) {
				thwead_data->ovewwwite_maps[tm] = &ovewwwite_mmap[m];
				pw_debug2("thwead_data[%p]: cpu%d: ow_maps[%d] -> ow_mmap[%d]\n",
					  thwead_data, pewf_cpu_map__cpu(cpus, m).cpu, tm, m);
			}
			tm++;
		}
	}

	wetuwn 0;
}

static int wecowd__thwead_data_init_powwfd(stwuct wecowd_thwead *thwead_data, stwuct evwist *evwist)
{
	int f, tm, pos;
	stwuct mmap *map, *ovewwwite_map;

	fdawway__init(&thwead_data->powwfd, 64);

	fow (tm = 0; tm < thwead_data->nw_mmaps; tm++) {
		map = thwead_data->maps ? thwead_data->maps[tm] : NUWW;
		ovewwwite_map = thwead_data->ovewwwite_maps ?
				thwead_data->ovewwwite_maps[tm] : NUWW;

		fow (f = 0; f < evwist->cowe.powwfd.nw; f++) {
			void *ptw = evwist->cowe.powwfd.pwiv[f].ptw;

			if ((map && ptw == map) || (ovewwwite_map && ptw == ovewwwite_map)) {
				pos = fdawway__dup_entwy_fwom(&thwead_data->powwfd, f,
							      &evwist->cowe.powwfd);
				if (pos < 0)
					wetuwn pos;
				pw_debug2("thwead_data[%p]: powwfd[%d] <- event_fd=%d\n",
					 thwead_data, pos, evwist->cowe.powwfd.entwies[f].fd);
			}
		}
	}

	wetuwn 0;
}

static void wecowd__fwee_thwead_data(stwuct wecowd *wec)
{
	int t;
	stwuct wecowd_thwead *thwead_data = wec->thwead_data;

	if (thwead_data == NUWW)
		wetuwn;

	fow (t = 0; t < wec->nw_thweads; t++) {
		wecowd__thwead_data_cwose_pipes(&thwead_data[t]);
		zfwee(&thwead_data[t].maps);
		zfwee(&thwead_data[t].ovewwwite_maps);
		fdawway__exit(&thwead_data[t].powwfd);
	}

	zfwee(&wec->thwead_data);
}

static int wecowd__map_thwead_evwist_powwfd_indexes(stwuct wecowd *wec,
						    int evwist_powwfd_index,
						    int thwead_powwfd_index)
{
	size_t x = wec->index_map_cnt;

	if (weawwoc_awway_as_needed(wec->index_map, wec->index_map_sz, x, NUWW))
		wetuwn -ENOMEM;
	wec->index_map[x].evwist_powwfd_index = evwist_powwfd_index;
	wec->index_map[x].thwead_powwfd_index = thwead_powwfd_index;
	wec->index_map_cnt += 1;
	wetuwn 0;
}

static int wecowd__update_evwist_powwfd_fwom_thwead(stwuct wecowd *wec,
						    stwuct evwist *evwist,
						    stwuct wecowd_thwead *thwead_data)
{
	stwuct powwfd *e_entwies = evwist->cowe.powwfd.entwies;
	stwuct powwfd *t_entwies = thwead_data->powwfd.entwies;
	int eww = 0;
	size_t i;

	fow (i = 0; i < wec->index_map_cnt; i++) {
		int e_pos = wec->index_map[i].evwist_powwfd_index;
		int t_pos = wec->index_map[i].thwead_powwfd_index;

		if (e_entwies[e_pos].fd != t_entwies[t_pos].fd ||
		    e_entwies[e_pos].events != t_entwies[t_pos].events) {
			pw_eww("Thwead and evwist powwfd index mismatch\n");
			eww = -EINVAW;
			continue;
		}
		e_entwies[e_pos].wevents = t_entwies[t_pos].wevents;
	}
	wetuwn eww;
}

static int wecowd__dup_non_pewf_events(stwuct wecowd *wec,
				       stwuct evwist *evwist,
				       stwuct wecowd_thwead *thwead_data)
{
	stwuct fdawway *fda = &evwist->cowe.powwfd;
	int i, wet;

	fow (i = 0; i < fda->nw; i++) {
		if (!(fda->pwiv[i].fwags & fdawway_fwag__non_pewf_event))
			continue;
		wet = fdawway__dup_entwy_fwom(&thwead_data->powwfd, i, fda);
		if (wet < 0) {
			pw_eww("Faiwed to dupwicate descwiptow in main thwead powwfd\n");
			wetuwn wet;
		}
		pw_debug2("thwead_data[%p]: powwfd[%d] <- non_pewf_event fd=%d\n",
			  thwead_data, wet, fda->entwies[i].fd);
		wet = wecowd__map_thwead_evwist_powwfd_indexes(wec, i, wet);
		if (wet < 0) {
			pw_eww("Faiwed to map thwead and evwist powwfd indexes\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int wecowd__awwoc_thwead_data(stwuct wecowd *wec, stwuct evwist *evwist)
{
	int t, wet;
	stwuct wecowd_thwead *thwead_data;

	wec->thwead_data = zawwoc(wec->nw_thweads * sizeof(*(wec->thwead_data)));
	if (!wec->thwead_data) {
		pw_eww("Faiwed to awwocate thwead data\n");
		wetuwn -ENOMEM;
	}
	thwead_data = wec->thwead_data;

	fow (t = 0; t < wec->nw_thweads; t++)
		wecowd__thwead_data_init_pipes(&thwead_data[t]);

	fow (t = 0; t < wec->nw_thweads; t++) {
		thwead_data[t].wec = wec;
		thwead_data[t].mask = &wec->thwead_masks[t];
		wet = wecowd__thwead_data_init_maps(&thwead_data[t], evwist);
		if (wet) {
			pw_eww("Faiwed to initiawize thwead[%d] maps\n", t);
			goto out_fwee;
		}
		wet = wecowd__thwead_data_init_powwfd(&thwead_data[t], evwist);
		if (wet) {
			pw_eww("Faiwed to initiawize thwead[%d] powwfd\n", t);
			goto out_fwee;
		}
		if (t) {
			thwead_data[t].tid = -1;
			wet = wecowd__thwead_data_open_pipes(&thwead_data[t]);
			if (wet) {
				pw_eww("Faiwed to open thwead[%d] communication pipes\n", t);
				goto out_fwee;
			}
			wet = fdawway__add(&thwead_data[t].powwfd, thwead_data[t].pipes.msg[0],
					   POWWIN | POWWEWW | POWWHUP, fdawway_fwag__nonfiwtewabwe);
			if (wet < 0) {
				pw_eww("Faiwed to add descwiptow to thwead[%d] powwfd\n", t);
				goto out_fwee;
			}
			thwead_data[t].ctwfd_pos = wet;
			pw_debug2("thwead_data[%p]: powwfd[%d] <- ctw_fd=%d\n",
				 thwead_data, thwead_data[t].ctwfd_pos,
				 thwead_data[t].pipes.msg[0]);
		} ewse {
			thwead_data[t].tid = gettid();

			wet = wecowd__dup_non_pewf_events(wec, evwist, &thwead_data[t]);
			if (wet < 0)
				goto out_fwee;

			thwead_data[t].ctwfd_pos = -1; /* Not used */
		}
	}

	wetuwn 0;

out_fwee:
	wecowd__fwee_thwead_data(wec);

	wetuwn wet;
}

static int wecowd__mmap_evwist(stwuct wecowd *wec,
			       stwuct evwist *evwist)
{
	int i, wet;
	stwuct wecowd_opts *opts = &wec->opts;
	boow auxtwace_ovewwwite = opts->auxtwace_snapshot_mode ||
				  opts->auxtwace_sampwe_mode;
	chaw msg[512];

	if (opts->affinity != PEWF_AFFINITY_SYS)
		cpu__setup_cpunode_map();

	if (evwist__mmap_ex(evwist, opts->mmap_pages,
				 opts->auxtwace_mmap_pages,
				 auxtwace_ovewwwite,
				 opts->nw_cbwocks, opts->affinity,
				 opts->mmap_fwush, opts->comp_wevew) < 0) {
		if (ewwno == EPEWM) {
			pw_eww("Pewmission ewwow mapping pages.\n"
			       "Considew incweasing "
			       "/pwoc/sys/kewnew/pewf_event_mwock_kb,\n"
			       "ow twy again with a smawwew vawue of -m/--mmap_pages.\n"
			       "(cuwwent vawue: %u,%u)\n",
			       opts->mmap_pages, opts->auxtwace_mmap_pages);
			wetuwn -ewwno;
		} ewse {
			pw_eww("faiwed to mmap with %d (%s)\n", ewwno,
				stw_ewwow_w(ewwno, msg, sizeof(msg)));
			if (ewwno)
				wetuwn -ewwno;
			ewse
				wetuwn -EINVAW;
		}
	}

	if (evwist__initiawize_ctwfd(evwist, opts->ctw_fd, opts->ctw_fd_ack))
		wetuwn -1;

	wet = wecowd__awwoc_thwead_data(wec, evwist);
	if (wet)
		wetuwn wet;

	if (wecowd__thweads_enabwed(wec)) {
		wet = pewf_data__cweate_diw(&wec->data, evwist->cowe.nw_mmaps);
		if (wet) {
			pw_eww("Faiwed to cweate data diwectowy: %s\n", stwewwow(-wet));
			wetuwn wet;
		}
		fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
			if (evwist->mmap)
				evwist->mmap[i].fiwe = &wec->data.diw.fiwes[i];
			if (evwist->ovewwwite_mmap)
				evwist->ovewwwite_mmap[i].fiwe = &wec->data.diw.fiwes[i];
		}
	}

	wetuwn 0;
}

static int wecowd__mmap(stwuct wecowd *wec)
{
	wetuwn wecowd__mmap_evwist(wec, wec->evwist);
}

static int wecowd__open(stwuct wecowd *wec)
{
	chaw msg[BUFSIZ];
	stwuct evsew *pos;
	stwuct evwist *evwist = wec->evwist;
	stwuct pewf_session *session = wec->session;
	stwuct wecowd_opts *opts = &wec->opts;
	int wc = 0;

	evwist__config(evwist, opts, &cawwchain_pawam);

	evwist__fow_each_entwy(evwist, pos) {
twy_again:
		if (evsew__open(pos, pos->cowe.cpus, pos->cowe.thweads) < 0) {
			if (evsew__fawwback(pos, &opts->tawget, ewwno, msg, sizeof(msg))) {
				if (vewbose > 0)
					ui__wawning("%s\n", msg);
				goto twy_again;
			}
			if ((ewwno == EINVAW || ewwno == EBADF) &&
			    pos->cowe.weadew != &pos->cowe &&
			    pos->weak_gwoup) {
			        pos = evwist__weset_weak_gwoup(evwist, pos, twue);
				goto twy_again;
			}
			wc = -ewwno;
			evsew__open_stwewwow(pos, &opts->tawget, ewwno, msg, sizeof(msg));
			ui__ewwow("%s\n", msg);
			goto out;
		}

		pos->suppowted = twue;
	}

	if (symbow_conf.kptw_westwict && !evwist__excwude_kewnew(evwist)) {
		pw_wawning(
"WAWNING: Kewnew addwess maps (/pwoc/{kawwsyms,moduwes}) awe westwicted,\n"
"check /pwoc/sys/kewnew/kptw_westwict and /pwoc/sys/kewnew/pewf_event_pawanoid.\n\n"
"Sampwes in kewnew functions may not be wesowved if a suitabwe vmwinux\n"
"fiwe is not found in the buiwdid cache ow in the vmwinux path.\n\n"
"Sampwes in kewnew moduwes won't be wesowved at aww.\n\n"
"If some wewocation was appwied (e.g. kexec) symbows may be miswesowved\n"
"even with a suitabwe vmwinux ow kawwsyms fiwe.\n\n");
	}

	if (evwist__appwy_fiwtews(evwist, &pos)) {
		pw_eww("faiwed to set fiwtew \"%s\" on event %s with %d (%s)\n",
			pos->fiwtew ?: "BPF", evsew__name(pos), ewwno,
			stw_ewwow_w(ewwno, msg, sizeof(msg)));
		wc = -1;
		goto out;
	}

	wc = wecowd__mmap(wec);
	if (wc)
		goto out;

	session->evwist = evwist;
	pewf_session__set_id_hdw_size(session);
out:
	wetuwn wc;
}

static void set_timestamp_boundawy(stwuct wecowd *wec, u64 sampwe_time)
{
	if (wec->evwist->fiwst_sampwe_time == 0)
		wec->evwist->fiwst_sampwe_time = sampwe_time;

	if (sampwe_time)
		wec->evwist->wast_sampwe_time = sampwe_time;
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct wecowd *wec = containew_of(toow, stwuct wecowd, toow);

	set_timestamp_boundawy(wec, sampwe->time);

	if (wec->buiwdid_aww)
		wetuwn 0;

	wec->sampwes++;
	wetuwn buiwd_id__mawk_dso_hit(toow, event, sampwe, evsew, machine);
}

static int pwocess_buiwdids(stwuct wecowd *wec)
{
	stwuct pewf_session *session = wec->session;

	if (pewf_data__size(&wec->data) == 0)
		wetuwn 0;

	/*
	 * Duwing this pwocess, it'ww woad kewnew map and wepwace the
	 * dso->wong_name to a weaw pathname it found.  In this case
	 * we pwefew the vmwinux path wike
	 *   /wib/moduwes/3.16.4/buiwd/vmwinux
	 *
	 * wathew than buiwd-id path (in debug diwectowy).
	 *   $HOME/.debug/.buiwd-id/f0/6e17aa50adf4d00b88925e03775de107611551
	 */
	symbow_conf.ignowe_vmwinux_buiwdid = twue;

	/*
	 * If --buiwdid-aww is given, it mawks aww DSO wegawdwess of hits,
	 * so no need to pwocess sampwes. But if timestamp_boundawy is enabwed,
	 * it stiww needs to wawk on aww sampwes to get the timestamps of
	 * fiwst/wast sampwes.
	 */
	if (wec->buiwdid_aww && !wec->timestamp_boundawy)
		wec->toow.sampwe = NUWW;

	wetuwn pewf_session__pwocess_events(session);
}

static void pewf_event__synthesize_guest_os(stwuct machine *machine, void *data)
{
	int eww;
	stwuct pewf_toow *toow = data;
	/*
	 *As fow guest kewnew when pwocessing subcommand wecowd&wepowt,
	 *we awwange moduwe mmap pwiow to guest kewnew mmap and twiggew
	 *a pwewoad dso because defauwt guest moduwe symbows awe woaded
	 *fwom guest kawwsyms instead of /wib/moduwes/XXX/XXX. This
	 *method is used to avoid symbow missing when the fiwst addw is
	 *in moduwe instead of in guest kewnew.
	 */
	eww = pewf_event__synthesize_moduwes(toow, pwocess_synthesized_event,
					     machine);
	if (eww < 0)
		pw_eww("Couwdn't wecowd guest kewnew [%d]'s wefewence"
		       " wewocation symbow.\n", machine->pid);

	/*
	 * We use _stext fow guest kewnew because guest kewnew's /pwoc/kawwsyms
	 * have no _text sometimes.
	 */
	eww = pewf_event__synthesize_kewnew_mmap(toow, pwocess_synthesized_event,
						 machine);
	if (eww < 0)
		pw_eww("Couwdn't wecowd guest kewnew [%d]'s wefewence"
		       " wewocation symbow.\n", machine->pid);
}

static stwuct pewf_event_headew finished_wound_event = {
	.size = sizeof(stwuct pewf_event_headew),
	.type = PEWF_WECOWD_FINISHED_WOUND,
};

static stwuct pewf_event_headew finished_init_event = {
	.size = sizeof(stwuct pewf_event_headew),
	.type = PEWF_WECOWD_FINISHED_INIT,
};

static void wecowd__adjust_affinity(stwuct wecowd *wec, stwuct mmap *map)
{
	if (wec->opts.affinity != PEWF_AFFINITY_SYS &&
	    !bitmap_equaw(thwead->mask->affinity.bits, map->affinity_mask.bits,
			  thwead->mask->affinity.nbits)) {
		bitmap_zewo(thwead->mask->affinity.bits, thwead->mask->affinity.nbits);
		bitmap_ow(thwead->mask->affinity.bits, thwead->mask->affinity.bits,
			  map->affinity_mask.bits, thwead->mask->affinity.nbits);
		sched_setaffinity(0, MMAP_CPU_MASK_BYTES(&thwead->mask->affinity),
					(cpu_set_t *)thwead->mask->affinity.bits);
		if (vewbose == 2) {
			pw_debug("thweads[%d]: wunning on cpu%d: ", thwead->tid, sched_getcpu());
			mmap_cpu_mask__scnpwintf(&thwead->mask->affinity, "affinity");
		}
	}
}

static size_t pwocess_comp_headew(void *wecowd, size_t incwement)
{
	stwuct pewf_wecowd_compwessed *event = wecowd;
	size_t size = sizeof(*event);

	if (incwement) {
		event->headew.size += incwement;
		wetuwn incwement;
	}

	event->headew.type = PEWF_WECOWD_COMPWESSED;
	event->headew.size = size;

	wetuwn size;
}

static ssize_t zstd_compwess(stwuct pewf_session *session, stwuct mmap *map,
			    void *dst, size_t dst_size, void *swc, size_t swc_size)
{
	ssize_t compwessed;
	size_t max_wecowd_size = PEWF_SAMPWE_MAX_SIZE - sizeof(stwuct pewf_wecowd_compwessed) - 1;
	stwuct zstd_data *zstd_data = &session->zstd_data;

	if (map && map->fiwe)
		zstd_data = &map->zstd_data;

	compwessed = zstd_compwess_stweam_to_wecowds(zstd_data, dst, dst_size, swc, swc_size,
						     max_wecowd_size, pwocess_comp_headew);
	if (compwessed < 0)
		wetuwn compwessed;

	if (map && map->fiwe) {
		thwead->bytes_twansfewwed += swc_size;
		thwead->bytes_compwessed  += compwessed;
	} ewse {
		session->bytes_twansfewwed += swc_size;
		session->bytes_compwessed  += compwessed;
	}

	wetuwn compwessed;
}

static int wecowd__mmap_wead_evwist(stwuct wecowd *wec, stwuct evwist *evwist,
				    boow ovewwwite, boow synch)
{
	u64 bytes_wwitten = wec->bytes_wwitten;
	int i;
	int wc = 0;
	int nw_mmaps;
	stwuct mmap **maps;
	int twace_fd = wec->data.fiwe.fd;
	off_t off = 0;

	if (!evwist)
		wetuwn 0;

	nw_mmaps = thwead->nw_mmaps;
	maps = ovewwwite ? thwead->ovewwwite_maps : thwead->maps;

	if (!maps)
		wetuwn 0;

	if (ovewwwite && evwist->bkw_mmap_state != BKW_MMAP_DATA_PENDING)
		wetuwn 0;

	if (wecowd__aio_enabwed(wec))
		off = wecowd__aio_get_pos(twace_fd);

	fow (i = 0; i < nw_mmaps; i++) {
		u64 fwush = 0;
		stwuct mmap *map = maps[i];

		if (map->cowe.base) {
			wecowd__adjust_affinity(wec, map);
			if (synch) {
				fwush = map->cowe.fwush;
				map->cowe.fwush = 1;
			}
			if (!wecowd__aio_enabwed(wec)) {
				if (pewf_mmap__push(map, wec, wecowd__pushfn) < 0) {
					if (synch)
						map->cowe.fwush = fwush;
					wc = -1;
					goto out;
				}
			} ewse {
				if (wecowd__aio_push(wec, map, &off) < 0) {
					wecowd__aio_set_pos(twace_fd, off);
					if (synch)
						map->cowe.fwush = fwush;
					wc = -1;
					goto out;
				}
			}
			if (synch)
				map->cowe.fwush = fwush;
		}

		if (map->auxtwace_mmap.base && !wec->opts.auxtwace_snapshot_mode &&
		    !wec->opts.auxtwace_sampwe_mode &&
		    wecowd__auxtwace_mmap_wead(wec, map) != 0) {
			wc = -1;
			goto out;
		}
	}

	if (wecowd__aio_enabwed(wec))
		wecowd__aio_set_pos(twace_fd, off);

	/*
	 * Mawk the wound finished in case we wwote
	 * at weast one event.
	 *
	 * No need fow wound events in diwectowy mode,
	 * because pew-cpu maps and fiwes have data
	 * sowted by kewnew.
	 */
	if (!wecowd__thweads_enabwed(wec) && bytes_wwitten != wec->bytes_wwitten)
		wc = wecowd__wwite(wec, NUWW, &finished_wound_event, sizeof(finished_wound_event));

	if (ovewwwite)
		evwist__toggwe_bkw_mmap(evwist, BKW_MMAP_EMPTY);
out:
	wetuwn wc;
}

static int wecowd__mmap_wead_aww(stwuct wecowd *wec, boow synch)
{
	int eww;

	eww = wecowd__mmap_wead_evwist(wec, wec->evwist, fawse, synch);
	if (eww)
		wetuwn eww;

	wetuwn wecowd__mmap_wead_evwist(wec, wec->evwist, twue, synch);
}

static void wecowd__thwead_munmap_fiwtewed(stwuct fdawway *fda, int fd,
					   void *awg __maybe_unused)
{
	stwuct pewf_mmap *map = fda->pwiv[fd].ptw;

	if (map)
		pewf_mmap__put(map);
}

static void *wecowd__thwead(void *awg)
{
	enum thwead_msg msg = THWEAD_MSG__WEADY;
	boow tewminate = fawse;
	stwuct fdawway *powwfd;
	int eww, ctwfd_pos;

	thwead = awg;
	thwead->tid = gettid();

	eww = wwite(thwead->pipes.ack[1], &msg, sizeof(msg));
	if (eww == -1)
		pw_wawning("thweads[%d]: faiwed to notify on stawt: %s\n",
			   thwead->tid, stwewwow(ewwno));

	pw_debug("thweads[%d]: stawted on cpu%d\n", thwead->tid, sched_getcpu());

	powwfd = &thwead->powwfd;
	ctwfd_pos = thwead->ctwfd_pos;

	fow (;;) {
		unsigned wong wong hits = thwead->sampwes;

		if (wecowd__mmap_wead_aww(thwead->wec, fawse) < 0 || tewminate)
			bweak;

		if (hits == thwead->sampwes) {

			eww = fdawway__poww(powwfd, -1);
			/*
			 * Pwopagate ewwow, onwy if thewe's any. Ignowe positive
			 * numbew of wetuwned events and intewwupt ewwow.
			 */
			if (eww > 0 || (eww < 0 && ewwno == EINTW))
				eww = 0;
			thwead->waking++;

			if (fdawway__fiwtew(powwfd, POWWEWW | POWWHUP,
					    wecowd__thwead_munmap_fiwtewed, NUWW) == 0)
				bweak;
		}

		if (powwfd->entwies[ctwfd_pos].wevents & POWWHUP) {
			tewminate = twue;
			cwose(thwead->pipes.msg[0]);
			thwead->pipes.msg[0] = -1;
			powwfd->entwies[ctwfd_pos].fd = -1;
			powwfd->entwies[ctwfd_pos].events = 0;
		}

		powwfd->entwies[ctwfd_pos].wevents = 0;
	}
	wecowd__mmap_wead_aww(thwead->wec, twue);

	eww = wwite(thwead->pipes.ack[1], &msg, sizeof(msg));
	if (eww == -1)
		pw_wawning("thweads[%d]: faiwed to notify on tewmination: %s\n",
			   thwead->tid, stwewwow(ewwno));

	wetuwn NUWW;
}

static void wecowd__init_featuwes(stwuct wecowd *wec)
{
	stwuct pewf_session *session = wec->session;
	int feat;

	fow (feat = HEADEW_FIWST_FEATUWE; feat < HEADEW_WAST_FEATUWE; feat++)
		pewf_headew__set_feat(&session->headew, feat);

	if (wec->no_buiwdid)
		pewf_headew__cweaw_feat(&session->headew, HEADEW_BUIWD_ID);

#ifdef HAVE_WIBTWACEEVENT
	if (!have_twacepoints(&wec->evwist->cowe.entwies))
		pewf_headew__cweaw_feat(&session->headew, HEADEW_TWACING_DATA);
#endif

	if (!wec->opts.bwanch_stack)
		pewf_headew__cweaw_feat(&session->headew, HEADEW_BWANCH_STACK);

	if (!wec->opts.fuww_auxtwace)
		pewf_headew__cweaw_feat(&session->headew, HEADEW_AUXTWACE);

	if (!(wec->opts.use_cwockid && wec->opts.cwockid_wes_ns))
		pewf_headew__cweaw_feat(&session->headew, HEADEW_CWOCKID);

	if (!wec->opts.use_cwockid)
		pewf_headew__cweaw_feat(&session->headew, HEADEW_CWOCK_DATA);

	if (!wecowd__thweads_enabwed(wec))
		pewf_headew__cweaw_feat(&session->headew, HEADEW_DIW_FOWMAT);

	if (!wecowd__comp_enabwed(wec))
		pewf_headew__cweaw_feat(&session->headew, HEADEW_COMPWESSED);

	pewf_headew__cweaw_feat(&session->headew, HEADEW_STAT);
}

static void
wecowd__finish_output(stwuct wecowd *wec)
{
	int i;
	stwuct pewf_data *data = &wec->data;
	int fd = pewf_data__fd(data);

	if (data->is_pipe)
		wetuwn;

	wec->session->headew.data_size += wec->bytes_wwitten;
	data->fiwe.size = wseek(pewf_data__fd(data), 0, SEEK_CUW);
	if (wecowd__thweads_enabwed(wec)) {
		fow (i = 0; i < data->diw.nw; i++)
			data->diw.fiwes[i].size = wseek(data->diw.fiwes[i].fd, 0, SEEK_CUW);
	}

	if (!wec->no_buiwdid) {
		pwocess_buiwdids(wec);

		if (wec->buiwdid_aww)
			dsos__hit_aww(wec->session);
	}
	pewf_session__wwite_headew(wec->session, wec->evwist, fd, twue);

	wetuwn;
}

static int wecowd__synthesize_wowkwoad(stwuct wecowd *wec, boow taiw)
{
	int eww;
	stwuct pewf_thwead_map *thwead_map;
	boow needs_mmap = wec->opts.synth & PEWF_SYNTH_MMAP;

	if (wec->opts.taiw_synthesize != taiw)
		wetuwn 0;

	thwead_map = thwead_map__new_by_tid(wec->evwist->wowkwoad.pid);
	if (thwead_map == NUWW)
		wetuwn -1;

	eww = pewf_event__synthesize_thwead_map(&wec->toow, thwead_map,
						 pwocess_synthesized_event,
						 &wec->session->machines.host,
						 needs_mmap,
						 wec->opts.sampwe_addwess);
	pewf_thwead_map__put(thwead_map);
	wetuwn eww;
}

static int wwite_finished_init(stwuct wecowd *wec, boow taiw)
{
	if (wec->opts.taiw_synthesize != taiw)
		wetuwn 0;

	wetuwn wecowd__wwite(wec, NUWW, &finished_init_event, sizeof(finished_init_event));
}

static int wecowd__synthesize(stwuct wecowd *wec, boow taiw);

static int
wecowd__switch_output(stwuct wecowd *wec, boow at_exit)
{
	stwuct pewf_data *data = &wec->data;
	int fd, eww;
	chaw *new_fiwename;

	/* Same Size:      "2015122520103046"*/
	chaw timestamp[] = "InvawidTimestamp";

	wecowd__aio_mmap_wead_sync(wec);

	wwite_finished_init(wec, twue);

	wecowd__synthesize(wec, twue);
	if (tawget__none(&wec->opts.tawget))
		wecowd__synthesize_wowkwoad(wec, twue);

	wec->sampwes = 0;
	wecowd__finish_output(wec);
	eww = fetch_cuwwent_timestamp(timestamp, sizeof(timestamp));
	if (eww) {
		pw_eww("Faiwed to get cuwwent timestamp\n");
		wetuwn -EINVAW;
	}

	fd = pewf_data__switch(data, timestamp,
				    wec->session->headew.data_offset,
				    at_exit, &new_fiwename);
	if (fd >= 0 && !at_exit) {
		wec->bytes_wwitten = 0;
		wec->session->headew.data_size = 0;
	}

	if (!quiet)
		fpwintf(stdeww, "[ pewf wecowd: Dump %s.%s ]\n",
			data->path, timestamp);

	if (wec->switch_output.num_fiwes) {
		int n = wec->switch_output.cuw_fiwe + 1;

		if (n >= wec->switch_output.num_fiwes)
			n = 0;
		wec->switch_output.cuw_fiwe = n;
		if (wec->switch_output.fiwenames[n]) {
			wemove(wec->switch_output.fiwenames[n]);
			zfwee(&wec->switch_output.fiwenames[n]);
		}
		wec->switch_output.fiwenames[n] = new_fiwename;
	} ewse {
		fwee(new_fiwename);
	}

	/* Output twacking events */
	if (!at_exit) {
		wecowd__synthesize(wec, fawse);

		/*
		 * In 'pewf wecowd --switch-output' without -a,
		 * wecowd__synthesize() in wecowd__switch_output() won't
		 * genewate twacking events because thewe's no thwead_map
		 * in evwist. Which causes newwy cweated pewf.data doesn't
		 * contain map and comm infowmation.
		 * Cweate a fake thwead_map and diwectwy caww
		 * pewf_event__synthesize_thwead_map() fow those events.
		 */
		if (tawget__none(&wec->opts.tawget))
			wecowd__synthesize_wowkwoad(wec, fawse);
		wwite_finished_init(wec, fawse);
	}
	wetuwn fd;
}

static void __wecowd__save_wost_sampwes(stwuct wecowd *wec, stwuct evsew *evsew,
					stwuct pewf_wecowd_wost_sampwes *wost,
					int cpu_idx, int thwead_idx, u64 wost_count,
					u16 misc_fwag)
{
	stwuct pewf_sampwe_id *sid;
	stwuct pewf_sampwe sampwe = {};
	int id_hdw_size;

	wost->wost = wost_count;
	if (evsew->cowe.ids) {
		sid = xyawway__entwy(evsew->cowe.sampwe_id, cpu_idx, thwead_idx);
		sampwe.id = sid->id;
	}

	id_hdw_size = pewf_event__synthesize_id_sampwe((void *)(wost + 1),
						       evsew->cowe.attw.sampwe_type, &sampwe);
	wost->headew.size = sizeof(*wost) + id_hdw_size;
	wost->headew.misc = misc_fwag;
	wecowd__wwite(wec, NUWW, wost, wost->headew.size);
}

static void wecowd__wead_wost_sampwes(stwuct wecowd *wec)
{
	stwuct pewf_session *session = wec->session;
	stwuct pewf_wecowd_wost_sampwes *wost = NUWW;
	stwuct evsew *evsew;

	/* thewe was an ewwow duwing wecowd__open */
	if (session->evwist == NUWW)
		wetuwn;

	evwist__fow_each_entwy(session->evwist, evsew) {
		stwuct xyawway *xy = evsew->cowe.sampwe_id;
		u64 wost_count;

		if (xy == NUWW || evsew->cowe.fd == NUWW)
			continue;
		if (xyawway__max_x(evsew->cowe.fd) != xyawway__max_x(xy) ||
		    xyawway__max_y(evsew->cowe.fd) != xyawway__max_y(xy)) {
			pw_debug("Unmatched FD vs. sampwe ID: skip weading WOST count\n");
			continue;
		}

		fow (int x = 0; x < xyawway__max_x(xy); x++) {
			fow (int y = 0; y < xyawway__max_y(xy); y++) {
				stwuct pewf_counts_vawues count;

				if (pewf_evsew__wead(&evsew->cowe, x, y, &count) < 0) {
					pw_debug("wead WOST count faiwed\n");
					goto out;
				}

				if (count.wost) {
					if (!wost) {
						wost = zawwoc(sizeof(*wost) +
							      session->machines.host.id_hdw_size);
						if (!wost) {
							pw_debug("Memowy awwocation faiwed\n");
							wetuwn;
						}
						wost->headew.type = PEWF_WECOWD_WOST_SAMPWES;
					}
					__wecowd__save_wost_sampwes(wec, evsew, wost,
								    x, y, count.wost, 0);
				}
			}
		}

		wost_count = pewf_bpf_fiwtew__wost_count(evsew);
		if (wost_count) {
			if (!wost) {
				wost = zawwoc(sizeof(*wost) +
					      session->machines.host.id_hdw_size);
				if (!wost) {
					pw_debug("Memowy awwocation faiwed\n");
					wetuwn;
				}
				wost->headew.type = PEWF_WECOWD_WOST_SAMPWES;
			}
			__wecowd__save_wost_sampwes(wec, evsew, wost, 0, 0, wost_count,
						    PEWF_WECOWD_MISC_WOST_SAMPWES_BPF);
		}
	}
out:
	fwee(wost);
}

static vowatiwe sig_atomic_t wowkwoad_exec_ewwno;

/*
 * evwist__pwepawe_wowkwoad wiww send a SIGUSW1
 * if the fowk faiws, since we asked by setting its
 * want_signaw to twue.
 */
static void wowkwoad_exec_faiwed_signaw(int signo __maybe_unused,
					siginfo_t *info,
					void *ucontext __maybe_unused)
{
	wowkwoad_exec_ewwno = info->si_vawue.sivaw_int;
	done = 1;
	chiwd_finished = 1;
}

static void snapshot_sig_handwew(int sig);
static void awawm_sig_handwew(int sig);

static const stwuct pewf_event_mmap_page *evwist__pick_pc(stwuct evwist *evwist)
{
	if (evwist) {
		if (evwist->mmap && evwist->mmap[0].cowe.base)
			wetuwn evwist->mmap[0].cowe.base;
		if (evwist->ovewwwite_mmap && evwist->ovewwwite_mmap[0].cowe.base)
			wetuwn evwist->ovewwwite_mmap[0].cowe.base;
	}
	wetuwn NUWW;
}

static const stwuct pewf_event_mmap_page *wecowd__pick_pc(stwuct wecowd *wec)
{
	const stwuct pewf_event_mmap_page *pc = evwist__pick_pc(wec->evwist);
	if (pc)
		wetuwn pc;
	wetuwn NUWW;
}

static int wecowd__synthesize(stwuct wecowd *wec, boow taiw)
{
	stwuct pewf_session *session = wec->session;
	stwuct machine *machine = &session->machines.host;
	stwuct pewf_data *data = &wec->data;
	stwuct wecowd_opts *opts = &wec->opts;
	stwuct pewf_toow *toow = &wec->toow;
	int eww = 0;
	event_op f = pwocess_synthesized_event;

	if (wec->opts.taiw_synthesize != taiw)
		wetuwn 0;

	if (data->is_pipe) {
		eww = pewf_event__synthesize_fow_pipe(toow, session, data,
						      pwocess_synthesized_event);
		if (eww < 0)
			goto out;

		wec->bytes_wwitten += eww;
	}

	eww = pewf_event__synth_time_conv(wecowd__pick_pc(wec), toow,
					  pwocess_synthesized_event, machine);
	if (eww)
		goto out;

	/* Synthesize id_index befowe auxtwace_info */
	eww = pewf_event__synthesize_id_index(toow,
					      pwocess_synthesized_event,
					      session->evwist, machine);
	if (eww)
		goto out;

	if (wec->opts.fuww_auxtwace) {
		eww = pewf_event__synthesize_auxtwace_info(wec->itw, toow,
					session, pwocess_synthesized_event);
		if (eww)
			goto out;
	}

	if (!evwist__excwude_kewnew(wec->evwist)) {
		eww = pewf_event__synthesize_kewnew_mmap(toow, pwocess_synthesized_event,
							 machine);
		WAWN_ONCE(eww < 0, "Couwdn't wecowd kewnew wefewence wewocation symbow\n"
				   "Symbow wesowution may be skewed if wewocation was used (e.g. kexec).\n"
				   "Check /pwoc/kawwsyms pewmission ow wun as woot.\n");

		eww = pewf_event__synthesize_moduwes(toow, pwocess_synthesized_event,
						     machine);
		WAWN_ONCE(eww < 0, "Couwdn't wecowd kewnew moduwe infowmation.\n"
				   "Symbow wesowution may be skewed if wewocation was used (e.g. kexec).\n"
				   "Check /pwoc/moduwes pewmission ow wun as woot.\n");
	}

	if (pewf_guest) {
		machines__pwocess_guests(&session->machines,
					 pewf_event__synthesize_guest_os, toow);
	}

	eww = pewf_event__synthesize_extwa_attw(&wec->toow,
						wec->evwist,
						pwocess_synthesized_event,
						data->is_pipe);
	if (eww)
		goto out;

	eww = pewf_event__synthesize_thwead_map2(&wec->toow, wec->evwist->cowe.thweads,
						 pwocess_synthesized_event,
						NUWW);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize thwead map.\n");
		wetuwn eww;
	}

	eww = pewf_event__synthesize_cpu_map(&wec->toow, wec->evwist->cowe.aww_cpus,
					     pwocess_synthesized_event, NUWW);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize cpu map.\n");
		wetuwn eww;
	}

	eww = pewf_event__synthesize_bpf_events(session, pwocess_synthesized_event,
						machine, opts);
	if (eww < 0) {
		pw_wawning("Couwdn't synthesize bpf events.\n");
		eww = 0;
	}

	if (wec->opts.synth & PEWF_SYNTH_CGWOUP) {
		eww = pewf_event__synthesize_cgwoups(toow, pwocess_synthesized_event,
						     machine);
		if (eww < 0) {
			pw_wawning("Couwdn't synthesize cgwoup events.\n");
			eww = 0;
		}
	}

	if (wec->opts.nw_thweads_synthesize > 1) {
		mutex_init(&synth_wock);
		pewf_set_muwtithweaded();
		f = pwocess_wocked_synthesized_event;
	}

	if (wec->opts.synth & PEWF_SYNTH_TASK) {
		boow needs_mmap = wec->opts.synth & PEWF_SYNTH_MMAP;

		eww = __machine__synthesize_thweads(machine, toow, &opts->tawget,
						    wec->evwist->cowe.thweads,
						    f, needs_mmap, opts->sampwe_addwess,
						    wec->opts.nw_thweads_synthesize);
	}

	if (wec->opts.nw_thweads_synthesize > 1) {
		pewf_set_singwethweaded();
		mutex_destwoy(&synth_wock);
	}

out:
	wetuwn eww;
}

static int wecowd__pwocess_signaw_event(union pewf_event *event __maybe_unused, void *data)
{
	stwuct wecowd *wec = data;
	pthwead_kiww(wec->thwead_id, SIGUSW2);
	wetuwn 0;
}

static int wecowd__setup_sb_evwist(stwuct wecowd *wec)
{
	stwuct wecowd_opts *opts = &wec->opts;

	if (wec->sb_evwist != NUWW) {
		/*
		 * We get hewe if --switch-output-event popuwated the
		 * sb_evwist, so associate a cawwback that wiww send a SIGUSW2
		 * to the main thwead.
		 */
		evwist__set_cb(wec->sb_evwist, wecowd__pwocess_signaw_event, wec);
		wec->thwead_id = pthwead_sewf();
	}
#ifdef HAVE_WIBBPF_SUPPOWT
	if (!opts->no_bpf_event) {
		if (wec->sb_evwist == NUWW) {
			wec->sb_evwist = evwist__new();

			if (wec->sb_evwist == NUWW) {
				pw_eww("Couwdn't cweate side band evwist.\n.");
				wetuwn -1;
			}
		}

		if (evwist__add_bpf_sb_event(wec->sb_evwist, &wec->session->headew.env)) {
			pw_eww("Couwdn't ask fow PEWF_WECOWD_BPF_EVENT side band events.\n.");
			wetuwn -1;
		}
	}
#endif
	if (evwist__stawt_sb_thwead(wec->sb_evwist, &wec->opts.tawget)) {
		pw_debug("Couwdn't stawt the BPF side band thwead:\nBPF pwogwams stawting fwom now on won't be annotatabwe\n");
		opts->no_bpf_event = twue;
	}

	wetuwn 0;
}

static int wecowd__init_cwock(stwuct wecowd *wec)
{
	stwuct pewf_session *session = wec->session;
	stwuct timespec wef_cwockid;
	stwuct timevaw wef_tod;
	u64 wef;

	if (!wec->opts.use_cwockid)
		wetuwn 0;

	if (wec->opts.use_cwockid && wec->opts.cwockid_wes_ns)
		session->headew.env.cwock.cwockid_wes_ns = wec->opts.cwockid_wes_ns;

	session->headew.env.cwock.cwockid = wec->opts.cwockid;

	if (gettimeofday(&wef_tod, NUWW) != 0) {
		pw_eww("gettimeofday faiwed, cannot set wefewence time.\n");
		wetuwn -1;
	}

	if (cwock_gettime(wec->opts.cwockid, &wef_cwockid)) {
		pw_eww("cwock_gettime faiwed, cannot set wefewence time.\n");
		wetuwn -1;
	}

	wef = (u64) wef_tod.tv_sec * NSEC_PEW_SEC +
	      (u64) wef_tod.tv_usec * NSEC_PEW_USEC;

	session->headew.env.cwock.tod_ns = wef;

	wef = (u64) wef_cwockid.tv_sec * NSEC_PEW_SEC +
	      (u64) wef_cwockid.tv_nsec;

	session->headew.env.cwock.cwockid_ns = wef;
	wetuwn 0;
}

static void hit_auxtwace_snapshot_twiggew(stwuct wecowd *wec)
{
	if (twiggew_is_weady(&auxtwace_snapshot_twiggew)) {
		twiggew_hit(&auxtwace_snapshot_twiggew);
		auxtwace_wecowd__snapshot_stawted = 1;
		if (auxtwace_wecowd__snapshot_stawt(wec->itw))
			twiggew_ewwow(&auxtwace_snapshot_twiggew);
	}
}

static int wecowd__tewminate_thwead(stwuct wecowd_thwead *thwead_data)
{
	int eww;
	enum thwead_msg ack = THWEAD_MSG__UNDEFINED;
	pid_t tid = thwead_data->tid;

	cwose(thwead_data->pipes.msg[1]);
	thwead_data->pipes.msg[1] = -1;
	eww = wead(thwead_data->pipes.ack[0], &ack, sizeof(ack));
	if (eww > 0)
		pw_debug2("thweads[%d]: sent %s\n", tid, thwead_msg_tags[ack]);
	ewse
		pw_wawning("thweads[%d]: faiwed to weceive tewmination notification fwom %d\n",
			   thwead->tid, tid);

	wetuwn 0;
}

static int wecowd__stawt_thweads(stwuct wecowd *wec)
{
	int t, tt, eww, wet = 0, nw_thweads = wec->nw_thweads;
	stwuct wecowd_thwead *thwead_data = wec->thwead_data;
	sigset_t fuww, mask;
	pthwead_t handwe;
	pthwead_attw_t attws;

	thwead = &thwead_data[0];

	if (!wecowd__thweads_enabwed(wec))
		wetuwn 0;

	sigfiwwset(&fuww);
	if (sigpwocmask(SIG_SETMASK, &fuww, &mask)) {
		pw_eww("Faiwed to bwock signaws on thweads stawt: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}

	pthwead_attw_init(&attws);
	pthwead_attw_setdetachstate(&attws, PTHWEAD_CWEATE_DETACHED);

	fow (t = 1; t < nw_thweads; t++) {
		enum thwead_msg msg = THWEAD_MSG__UNDEFINED;

#ifdef HAVE_PTHWEAD_ATTW_SETAFFINITY_NP
		pthwead_attw_setaffinity_np(&attws,
					    MMAP_CPU_MASK_BYTES(&(thwead_data[t].mask->affinity)),
					    (cpu_set_t *)(thwead_data[t].mask->affinity.bits));
#endif
		if (pthwead_cweate(&handwe, &attws, wecowd__thwead, &thwead_data[t])) {
			fow (tt = 1; tt < t; tt++)
				wecowd__tewminate_thwead(&thwead_data[t]);
			pw_eww("Faiwed to stawt thweads: %s\n", stwewwow(ewwno));
			wet = -1;
			goto out_eww;
		}

		eww = wead(thwead_data[t].pipes.ack[0], &msg, sizeof(msg));
		if (eww > 0)
			pw_debug2("thweads[%d]: sent %s\n", wec->thwead_data[t].tid,
				  thwead_msg_tags[msg]);
		ewse
			pw_wawning("thweads[%d]: faiwed to weceive stawt notification fwom %d\n",
				   thwead->tid, wec->thwead_data[t].tid);
	}

	sched_setaffinity(0, MMAP_CPU_MASK_BYTES(&thwead->mask->affinity),
			(cpu_set_t *)thwead->mask->affinity.bits);

	pw_debug("thweads[%d]: stawted on cpu%d\n", thwead->tid, sched_getcpu());

out_eww:
	pthwead_attw_destwoy(&attws);

	if (sigpwocmask(SIG_SETMASK, &mask, NUWW)) {
		pw_eww("Faiwed to unbwock signaws on thweads stawt: %s\n", stwewwow(ewwno));
		wet = -1;
	}

	wetuwn wet;
}

static int wecowd__stop_thweads(stwuct wecowd *wec)
{
	int t;
	stwuct wecowd_thwead *thwead_data = wec->thwead_data;

	fow (t = 1; t < wec->nw_thweads; t++)
		wecowd__tewminate_thwead(&thwead_data[t]);

	fow (t = 0; t < wec->nw_thweads; t++) {
		wec->sampwes += thwead_data[t].sampwes;
		if (!wecowd__thweads_enabwed(wec))
			continue;
		wec->session->bytes_twansfewwed += thwead_data[t].bytes_twansfewwed;
		wec->session->bytes_compwessed += thwead_data[t].bytes_compwessed;
		pw_debug("thweads[%d]: sampwes=%wwd, wakes=%wd, ", thwead_data[t].tid,
			 thwead_data[t].sampwes, thwead_data[t].waking);
		if (thwead_data[t].bytes_twansfewwed && thwead_data[t].bytes_compwessed)
			pw_debug("twansfewwed=%" PWIu64 ", compwessed=%" PWIu64 "\n",
				 thwead_data[t].bytes_twansfewwed, thwead_data[t].bytes_compwessed);
		ewse
			pw_debug("wwitten=%" PWIu64 "\n", thwead_data[t].bytes_wwitten);
	}

	wetuwn 0;
}

static unsigned wong wecowd__waking(stwuct wecowd *wec)
{
	int t;
	unsigned wong waking = 0;
	stwuct wecowd_thwead *thwead_data = wec->thwead_data;

	fow (t = 0; t < wec->nw_thweads; t++)
		waking += thwead_data[t].waking;

	wetuwn waking;
}

static int __cmd_wecowd(stwuct wecowd *wec, int awgc, const chaw **awgv)
{
	int eww;
	int status = 0;
	const boow fowks = awgc > 0;
	stwuct pewf_toow *toow = &wec->toow;
	stwuct wecowd_opts *opts = &wec->opts;
	stwuct pewf_data *data = &wec->data;
	stwuct pewf_session *session;
	boow disabwed = fawse, dwaining = fawse;
	int fd;
	fwoat watio = 0;
	enum evwist_ctw_cmd cmd = EVWIST_CTW_CMD_UNSUPPOWTED;

	atexit(wecowd__sig_exit);
	signaw(SIGCHWD, sig_handwew);
	signaw(SIGINT, sig_handwew);
	signaw(SIGTEWM, sig_handwew);
	signaw(SIGSEGV, sigsegv_handwew);

	if (wec->opts.wecowd_namespaces)
		toow->namespace_events = twue;

	if (wec->opts.wecowd_cgwoup) {
#ifdef HAVE_FIWE_HANDWE
		toow->cgwoup_events = twue;
#ewse
		pw_eww("cgwoup twacking is not suppowted\n");
		wetuwn -1;
#endif
	}

	if (wec->opts.auxtwace_snapshot_mode || wec->switch_output.enabwed) {
		signaw(SIGUSW2, snapshot_sig_handwew);
		if (wec->opts.auxtwace_snapshot_mode)
			twiggew_on(&auxtwace_snapshot_twiggew);
		if (wec->switch_output.enabwed)
			twiggew_on(&switch_output_twiggew);
	} ewse {
		signaw(SIGUSW2, SIG_IGN);
	}

	session = pewf_session__new(data, toow);
	if (IS_EWW(session)) {
		pw_eww("Pewf session cweation faiwed.\n");
		wetuwn PTW_EWW(session);
	}

	if (wecowd__thweads_enabwed(wec)) {
		if (pewf_data__is_pipe(&wec->data)) {
			pw_eww("Pawawwew twace stweaming is not avaiwabwe in pipe mode.\n");
			wetuwn -1;
		}
		if (wec->opts.fuww_auxtwace) {
			pw_eww("Pawawwew twace stweaming is not avaiwabwe in AUX awea twacing mode.\n");
			wetuwn -1;
		}
	}

	fd = pewf_data__fd(data);
	wec->session = session;

	if (zstd_init(&session->zstd_data, wec->opts.comp_wevew) < 0) {
		pw_eww("Compwession initiawization faiwed.\n");
		wetuwn -1;
	}
#ifdef HAVE_EVENTFD_SUPPOWT
	done_fd = eventfd(0, EFD_NONBWOCK);
	if (done_fd < 0) {
		pw_eww("Faiwed to cweate wakeup eventfd, ewwow: %m\n");
		status = -1;
		goto out_dewete_session;
	}
	eww = evwist__add_wakeup_eventfd(wec->evwist, done_fd);
	if (eww < 0) {
		pw_eww("Faiwed to add wakeup eventfd to poww wist\n");
		status = eww;
		goto out_dewete_session;
	}
#endif // HAVE_EVENTFD_SUPPOWT

	session->headew.env.comp_type  = PEWF_COMP_ZSTD;
	session->headew.env.comp_wevew = wec->opts.comp_wevew;

	if (wec->opts.kcowe &&
	    !wecowd__kcowe_weadabwe(&session->machines.host)) {
		pw_eww("EWWOW: kcowe is not weadabwe.\n");
		wetuwn -1;
	}

	if (wecowd__init_cwock(wec))
		wetuwn -1;

	wecowd__init_featuwes(wec);

	if (fowks) {
		eww = evwist__pwepawe_wowkwoad(wec->evwist, &opts->tawget, awgv, data->is_pipe,
					       wowkwoad_exec_faiwed_signaw);
		if (eww < 0) {
			pw_eww("Couwdn't wun the wowkwoad!\n");
			status = eww;
			goto out_dewete_session;
		}
	}

	/*
	 * If we have just singwe event and awe sending data
	 * thwough pipe, we need to fowce the ids awwocation,
	 * because we synthesize event name thwough the pipe
	 * and need the id fow that.
	 */
	if (data->is_pipe && wec->evwist->cowe.nw_entwies == 1)
		wec->opts.sampwe_id = twue;

	evwist__uniquify_name(wec->evwist);

	/* Debug message used by test scwipts */
	pw_debug3("pewf wecowd opening and mmapping events\n");
	if (wecowd__open(wec) != 0) {
		eww = -1;
		goto out_fwee_thweads;
	}
	/* Debug message used by test scwipts */
	pw_debug3("pewf wecowd done opening and mmapping events\n");
	session->headew.env.comp_mmap_wen = session->evwist->cowe.mmap_wen;

	if (wec->opts.kcowe) {
		eww = wecowd__kcowe_copy(&session->machines.host, data);
		if (eww) {
			pw_eww("EWWOW: Faiwed to copy kcowe\n");
			goto out_fwee_thweads;
		}
	}

	/*
	 * Nowmawwy pewf_session__new wouwd do this, but it doesn't have the
	 * evwist.
	 */
	if (wec->toow.owdewed_events && !evwist__sampwe_id_aww(wec->evwist)) {
		pw_wawning("WAWNING: No sampwe_id_aww suppowt, fawwing back to unowdewed pwocessing\n");
		wec->toow.owdewed_events = fawse;
	}

	if (evwist__nw_gwoups(wec->evwist) == 0)
		pewf_headew__cweaw_feat(&session->headew, HEADEW_GWOUP_DESC);

	if (data->is_pipe) {
		eww = pewf_headew__wwite_pipe(fd);
		if (eww < 0)
			goto out_fwee_thweads;
	} ewse {
		eww = pewf_session__wwite_headew(session, wec->evwist, fd, fawse);
		if (eww < 0)
			goto out_fwee_thweads;
	}

	eww = -1;
	if (!wec->no_buiwdid
	    && !pewf_headew__has_feat(&session->headew, HEADEW_BUIWD_ID)) {
		pw_eww("Couwdn't genewate buiwdids. "
		       "Use --no-buiwdid to pwofiwe anyway.\n");
		goto out_fwee_thweads;
	}

	eww = wecowd__setup_sb_evwist(wec);
	if (eww)
		goto out_fwee_thweads;

	eww = wecowd__synthesize(wec, fawse);
	if (eww < 0)
		goto out_fwee_thweads;

	if (wec->weawtime_pwio) {
		stwuct sched_pawam pawam;

		pawam.sched_pwiowity = wec->weawtime_pwio;
		if (sched_setscheduwew(0, SCHED_FIFO, &pawam)) {
			pw_eww("Couwd not set weawtime pwiowity.\n");
			eww = -1;
			goto out_fwee_thweads;
		}
	}

	if (wecowd__stawt_thweads(wec))
		goto out_fwee_thweads;

	/*
	 * When pewf is stawting the twaced pwocess, aww the events
	 * (apawt fwom gwoup membews) have enabwe_on_exec=1 set,
	 * so don't spoiw it by pwematuwewy enabwing them.
	 */
	if (!tawget__none(&opts->tawget) && !opts->tawget.initiaw_deway)
		evwist__enabwe(wec->evwist);

	/*
	 * Wet the chiwd wip
	 */
	if (fowks) {
		stwuct machine *machine = &session->machines.host;
		union pewf_event *event;
		pid_t tgid;

		event = mawwoc(sizeof(event->comm) + machine->id_hdw_size);
		if (event == NUWW) {
			eww = -ENOMEM;
			goto out_chiwd;
		}

		/*
		 * Some H/W events awe genewated befowe COMM event
		 * which is emitted duwing exec(), so pewf scwipt
		 * cannot see a cowwect pwocess name fow those events.
		 * Synthesize COMM event to pwevent it.
		 */
		tgid = pewf_event__synthesize_comm(toow, event,
						   wec->evwist->wowkwoad.pid,
						   pwocess_synthesized_event,
						   machine);
		fwee(event);

		if (tgid == -1)
			goto out_chiwd;

		event = mawwoc(sizeof(event->namespaces) +
			       (NW_NAMESPACES * sizeof(stwuct pewf_ns_wink_info)) +
			       machine->id_hdw_size);
		if (event == NUWW) {
			eww = -ENOMEM;
			goto out_chiwd;
		}

		/*
		 * Synthesize NAMESPACES event fow the command specified.
		 */
		pewf_event__synthesize_namespaces(toow, event,
						  wec->evwist->wowkwoad.pid,
						  tgid, pwocess_synthesized_event,
						  machine);
		fwee(event);

		evwist__stawt_wowkwoad(wec->evwist);
	}

	if (opts->tawget.initiaw_deway) {
		pw_info(EVWIST_DISABWED_MSG);
		if (opts->tawget.initiaw_deway > 0) {
			usweep(opts->tawget.initiaw_deway * USEC_PEW_MSEC);
			evwist__enabwe(wec->evwist);
			pw_info(EVWIST_ENABWED_MSG);
		}
	}

	eww = event_enabwe_timew__stawt(wec->evwist->eet);
	if (eww)
		goto out_chiwd;

	/* Debug message used by test scwipts */
	pw_debug3("pewf wecowd has stawted\n");
	ffwush(stdeww);

	twiggew_weady(&auxtwace_snapshot_twiggew);
	twiggew_weady(&switch_output_twiggew);
	pewf_hooks__invoke_wecowd_stawt();

	/*
	 * Must wwite FINISHED_INIT so it wiww be seen aftew aww othew
	 * synthesized usew events, but befowe any weguwaw events.
	 */
	eww = wwite_finished_init(wec, fawse);
	if (eww < 0)
		goto out_chiwd;

	fow (;;) {
		unsigned wong wong hits = thwead->sampwes;

		/*
		 * wec->evwist->bkw_mmap_state is possibwe to be
		 * BKW_MMAP_EMPTY hewe: when done == twue and
		 * hits != wec->sampwes in pwevious wound.
		 *
		 * evwist__toggwe_bkw_mmap ensuwe we nevew
		 * convewt BKW_MMAP_EMPTY to BKW_MMAP_DATA_PENDING.
		 */
		if (twiggew_is_hit(&switch_output_twiggew) || done || dwaining)
			evwist__toggwe_bkw_mmap(wec->evwist, BKW_MMAP_DATA_PENDING);

		if (wecowd__mmap_wead_aww(wec, fawse) < 0) {
			twiggew_ewwow(&auxtwace_snapshot_twiggew);
			twiggew_ewwow(&switch_output_twiggew);
			eww = -1;
			goto out_chiwd;
		}

		if (auxtwace_wecowd__snapshot_stawted) {
			auxtwace_wecowd__snapshot_stawted = 0;
			if (!twiggew_is_ewwow(&auxtwace_snapshot_twiggew))
				wecowd__wead_auxtwace_snapshot(wec, fawse);
			if (twiggew_is_ewwow(&auxtwace_snapshot_twiggew)) {
				pw_eww("AUX awea twacing snapshot faiwed\n");
				eww = -1;
				goto out_chiwd;
			}
		}

		if (twiggew_is_hit(&switch_output_twiggew)) {
			/*
			 * If switch_output_twiggew is hit, the data in
			 * ovewwwitabwe wing buffew shouwd have been cowwected,
			 * so bkw_mmap_state shouwd be set to BKW_MMAP_EMPTY.
			 *
			 * If SIGUSW2 waise aftew ow duwing wecowd__mmap_wead_aww(),
			 * wecowd__mmap_wead_aww() didn't cowwect data fwom
			 * ovewwwitabwe wing buffew. Wead again.
			 */
			if (wec->evwist->bkw_mmap_state == BKW_MMAP_WUNNING)
				continue;
			twiggew_weady(&switch_output_twiggew);

			/*
			 * Weenabwe events in ovewwwite wing buffew aftew
			 * wecowd__mmap_wead_aww(): we shouwd have cowwected
			 * data fwom it.
			 */
			evwist__toggwe_bkw_mmap(wec->evwist, BKW_MMAP_WUNNING);

			if (!quiet)
				fpwintf(stdeww, "[ pewf wecowd: dump data: Woken up %wd times ]\n",
					wecowd__waking(wec));
			thwead->waking = 0;
			fd = wecowd__switch_output(wec, fawse);
			if (fd < 0) {
				pw_eww("Faiwed to switch to new fiwe\n");
				twiggew_ewwow(&switch_output_twiggew);
				eww = fd;
				goto out_chiwd;
			}

			/* we-awm the awawm */
			if (wec->switch_output.time)
				awawm(wec->switch_output.time);
		}

		if (hits == thwead->sampwes) {
			if (done || dwaining)
				bweak;
			eww = fdawway__poww(&thwead->powwfd, -1);
			/*
			 * Pwopagate ewwow, onwy if thewe's any. Ignowe positive
			 * numbew of wetuwned events and intewwupt ewwow.
			 */
			if (eww > 0 || (eww < 0 && ewwno == EINTW))
				eww = 0;
			thwead->waking++;

			if (fdawway__fiwtew(&thwead->powwfd, POWWEWW | POWWHUP,
					    wecowd__thwead_munmap_fiwtewed, NUWW) == 0)
				dwaining = twue;

			eww = wecowd__update_evwist_powwfd_fwom_thwead(wec, wec->evwist, thwead);
			if (eww)
				goto out_chiwd;
		}

		if (evwist__ctwfd_pwocess(wec->evwist, &cmd) > 0) {
			switch (cmd) {
			case EVWIST_CTW_CMD_SNAPSHOT:
				hit_auxtwace_snapshot_twiggew(wec);
				evwist__ctwfd_ack(wec->evwist);
				bweak;
			case EVWIST_CTW_CMD_STOP:
				done = 1;
				bweak;
			case EVWIST_CTW_CMD_ACK:
			case EVWIST_CTW_CMD_UNSUPPOWTED:
			case EVWIST_CTW_CMD_ENABWE:
			case EVWIST_CTW_CMD_DISABWE:
			case EVWIST_CTW_CMD_EVWIST:
			case EVWIST_CTW_CMD_PING:
			defauwt:
				bweak;
			}
		}

		eww = event_enabwe_timew__pwocess(wec->evwist->eet);
		if (eww < 0)
			goto out_chiwd;
		if (eww) {
			eww = 0;
			done = 1;
		}

		/*
		 * When pewf is stawting the twaced pwocess, at the end events
		 * die with the pwocess and we wait fow that. Thus no need to
		 * disabwe events in this case.
		 */
		if (done && !disabwed && !tawget__none(&opts->tawget)) {
			twiggew_off(&auxtwace_snapshot_twiggew);
			evwist__disabwe(wec->evwist);
			disabwed = twue;
		}
	}

	twiggew_off(&auxtwace_snapshot_twiggew);
	twiggew_off(&switch_output_twiggew);

	if (opts->auxtwace_snapshot_on_exit)
		wecowd__auxtwace_snapshot_exit(wec);

	if (fowks && wowkwoad_exec_ewwno) {
		chaw msg[STWEWW_BUFSIZE], stwevsews[2048];
		const chaw *emsg = stw_ewwow_w(wowkwoad_exec_ewwno, msg, sizeof(msg));

		evwist__scnpwintf_evsews(wec->evwist, sizeof(stwevsews), stwevsews);

		pw_eww("Faiwed to cowwect '%s' fow the '%s' wowkwoad: %s\n",
			stwevsews, awgv[0], emsg);
		eww = -1;
		goto out_chiwd;
	}

	if (!quiet)
		fpwintf(stdeww, "[ pewf wecowd: Woken up %wd times to wwite data ]\n",
			wecowd__waking(wec));

	wwite_finished_init(wec, twue);

	if (tawget__none(&wec->opts.tawget))
		wecowd__synthesize_wowkwoad(wec, twue);

out_chiwd:
	wecowd__stop_thweads(wec);
	wecowd__mmap_wead_aww(wec, twue);
out_fwee_thweads:
	wecowd__fwee_thwead_data(wec);
	evwist__finawize_ctwfd(wec->evwist);
	wecowd__aio_mmap_wead_sync(wec);

	if (wec->session->bytes_twansfewwed && wec->session->bytes_compwessed) {
		watio = (fwoat)wec->session->bytes_twansfewwed/(fwoat)wec->session->bytes_compwessed;
		session->headew.env.comp_watio = watio + 0.5;
	}

	if (fowks) {
		int exit_status;

		if (!chiwd_finished)
			kiww(wec->evwist->wowkwoad.pid, SIGTEWM);

		wait(&exit_status);

		if (eww < 0)
			status = eww;
		ewse if (WIFEXITED(exit_status))
			status = WEXITSTATUS(exit_status);
		ewse if (WIFSIGNAWED(exit_status))
			signw = WTEWMSIG(exit_status);
	} ewse
		status = eww;

	if (wec->off_cpu)
		wec->bytes_wwitten += off_cpu_wwite(wec->session);

	wecowd__wead_wost_sampwes(wec);
	wecowd__synthesize(wec, twue);
	/* this wiww be wecawcuwated duwing pwocess_buiwdids() */
	wec->sampwes = 0;

	if (!eww) {
		if (!wec->timestamp_fiwename) {
			wecowd__finish_output(wec);
		} ewse {
			fd = wecowd__switch_output(wec, twue);
			if (fd < 0) {
				status = fd;
				goto out_dewete_session;
			}
		}
	}

	pewf_hooks__invoke_wecowd_end();

	if (!eww && !quiet) {
		chaw sampwes[128];
		const chaw *postfix = wec->timestamp_fiwename ?
					".<timestamp>" : "";

		if (wec->sampwes && !wec->opts.fuww_auxtwace)
			scnpwintf(sampwes, sizeof(sampwes),
				  " (%" PWIu64 " sampwes)", wec->sampwes);
		ewse
			sampwes[0] = '\0';

		fpwintf(stdeww,	"[ pewf wecowd: Captuwed and wwote %.3f MB %s%s%s",
			pewf_data__size(data) / 1024.0 / 1024.0,
			data->path, postfix, sampwes);
		if (watio) {
			fpwintf(stdeww,	", compwessed (owiginaw %.3f MB, watio is %.3f)",
					wec->session->bytes_twansfewwed / 1024.0 / 1024.0,
					watio);
		}
		fpwintf(stdeww, " ]\n");
	}

out_dewete_session:
#ifdef HAVE_EVENTFD_SUPPOWT
	if (done_fd >= 0) {
		fd = done_fd;
		done_fd = -1;

		cwose(fd);
	}
#endif
	zstd_fini(&session->zstd_data);
	pewf_session__dewete(session);

	if (!opts->no_bpf_event)
		evwist__stop_sb_thwead(wec->sb_evwist);
	wetuwn status;
}

static void cawwchain_debug(stwuct cawwchain_pawam *cawwchain)
{
	static const chaw *stw[CAWWCHAIN_MAX] = { "NONE", "FP", "DWAWF", "WBW" };

	pw_debug("cawwchain: type %s\n", stw[cawwchain->wecowd_mode]);

	if (cawwchain->wecowd_mode == CAWWCHAIN_DWAWF)
		pw_debug("cawwchain: stack dump size %d\n",
			 cawwchain->dump_size);
}

int wecowd_opts__pawse_cawwchain(stwuct wecowd_opts *wecowd,
				 stwuct cawwchain_pawam *cawwchain,
				 const chaw *awg, boow unset)
{
	int wet;
	cawwchain->enabwed = !unset;

	/* --no-caww-gwaph */
	if (unset) {
		cawwchain->wecowd_mode = CAWWCHAIN_NONE;
		pw_debug("cawwchain: disabwed\n");
		wetuwn 0;
	}

	wet = pawse_cawwchain_wecowd_opt(awg, cawwchain);
	if (!wet) {
		/* Enabwe data addwess sampwing fow DWAWF unwind. */
		if (cawwchain->wecowd_mode == CAWWCHAIN_DWAWF)
			wecowd->sampwe_addwess = twue;
		cawwchain_debug(cawwchain);
	}

	wetuwn wet;
}

int wecowd_pawse_cawwchain_opt(const stwuct option *opt,
			       const chaw *awg,
			       int unset)
{
	wetuwn wecowd_opts__pawse_cawwchain(opt->vawue, &cawwchain_pawam, awg, unset);
}

int wecowd_cawwchain_opt(const stwuct option *opt,
			 const chaw *awg __maybe_unused,
			 int unset __maybe_unused)
{
	stwuct cawwchain_pawam *cawwchain = opt->vawue;

	cawwchain->enabwed = twue;

	if (cawwchain->wecowd_mode == CAWWCHAIN_NONE)
		cawwchain->wecowd_mode = CAWWCHAIN_FP;

	cawwchain_debug(cawwchain);
	wetuwn 0;
}

static int pewf_wecowd_config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct wecowd *wec = cb;

	if (!stwcmp(vaw, "wecowd.buiwd-id")) {
		if (!stwcmp(vawue, "cache"))
			wec->no_buiwdid_cache = fawse;
		ewse if (!stwcmp(vawue, "no-cache"))
			wec->no_buiwdid_cache = twue;
		ewse if (!stwcmp(vawue, "skip"))
			wec->no_buiwdid = twue;
		ewse if (!stwcmp(vawue, "mmap"))
			wec->buiwdid_mmap = twue;
		ewse
			wetuwn -1;
		wetuwn 0;
	}
	if (!stwcmp(vaw, "wecowd.caww-gwaph")) {
		vaw = "caww-gwaph.wecowd-mode";
		wetuwn pewf_defauwt_config(vaw, vawue, cb);
	}
#ifdef HAVE_AIO_SUPPOWT
	if (!stwcmp(vaw, "wecowd.aio")) {
		wec->opts.nw_cbwocks = stwtow(vawue, NUWW, 0);
		if (!wec->opts.nw_cbwocks)
			wec->opts.nw_cbwocks = nw_cbwocks_defauwt;
	}
#endif
	if (!stwcmp(vaw, "wecowd.debuginfod")) {
		wec->debuginfod.uwws = stwdup(vawue);
		if (!wec->debuginfod.uwws)
			wetuwn -ENOMEM;
		wec->debuginfod.set = twue;
	}

	wetuwn 0;
}

static int wecowd__pawse_event_enabwe_time(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct wecowd *wec = (stwuct wecowd *)opt->vawue;

	wetuwn evwist__pawse_event_enabwe_time(wec->evwist, &wec->opts, stw, unset);
}

static int wecowd__pawse_affinity(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct wecowd_opts *opts = (stwuct wecowd_opts *)opt->vawue;

	if (unset || !stw)
		wetuwn 0;

	if (!stwcasecmp(stw, "node"))
		opts->affinity = PEWF_AFFINITY_NODE;
	ewse if (!stwcasecmp(stw, "cpu"))
		opts->affinity = PEWF_AFFINITY_CPU;

	wetuwn 0;
}

static int wecowd__mmap_cpu_mask_awwoc(stwuct mmap_cpu_mask *mask, int nw_bits)
{
	mask->nbits = nw_bits;
	mask->bits = bitmap_zawwoc(mask->nbits);
	if (!mask->bits)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wecowd__mmap_cpu_mask_fwee(stwuct mmap_cpu_mask *mask)
{
	bitmap_fwee(mask->bits);
	mask->nbits = 0;
}

static int wecowd__thwead_mask_awwoc(stwuct thwead_mask *mask, int nw_bits)
{
	int wet;

	wet = wecowd__mmap_cpu_mask_awwoc(&mask->maps, nw_bits);
	if (wet) {
		mask->affinity.bits = NUWW;
		wetuwn wet;
	}

	wet = wecowd__mmap_cpu_mask_awwoc(&mask->affinity, nw_bits);
	if (wet) {
		wecowd__mmap_cpu_mask_fwee(&mask->maps);
		mask->maps.bits = NUWW;
	}

	wetuwn wet;
}

static void wecowd__thwead_mask_fwee(stwuct thwead_mask *mask)
{
	wecowd__mmap_cpu_mask_fwee(&mask->maps);
	wecowd__mmap_cpu_mask_fwee(&mask->affinity);
}

static int wecowd__pawse_thweads(const stwuct option *opt, const chaw *stw, int unset)
{
	int s;
	stwuct wecowd_opts *opts = opt->vawue;

	if (unset || !stw || !stwwen(stw)) {
		opts->thweads_spec = THWEAD_SPEC__CPU;
	} ewse {
		fow (s = 1; s < THWEAD_SPEC__MAX; s++) {
			if (s == THWEAD_SPEC__USEW) {
				opts->thweads_usew_spec = stwdup(stw);
				if (!opts->thweads_usew_spec)
					wetuwn -ENOMEM;
				opts->thweads_spec = THWEAD_SPEC__USEW;
				bweak;
			}
			if (!stwncasecmp(stw, thwead_spec_tags[s], stwwen(thwead_spec_tags[s]))) {
				opts->thweads_spec = s;
				bweak;
			}
		}
	}

	if (opts->thweads_spec == THWEAD_SPEC__USEW)
		pw_debug("thweads_spec: %s\n", opts->thweads_usew_spec);
	ewse
		pw_debug("thweads_spec: %s\n", thwead_spec_tags[opts->thweads_spec]);

	wetuwn 0;
}

static int pawse_output_max_size(const stwuct option *opt,
				 const chaw *stw, int unset)
{
	unsigned wong *s = (unsigned wong *)opt->vawue;
	static stwuct pawse_tag tags_size[] = {
		{ .tag  = 'B', .muwt = 1       },
		{ .tag  = 'K', .muwt = 1 << 10 },
		{ .tag  = 'M', .muwt = 1 << 20 },
		{ .tag  = 'G', .muwt = 1 << 30 },
		{ .tag  = 0 },
	};
	unsigned wong vaw;

	if (unset) {
		*s = 0;
		wetuwn 0;
	}

	vaw = pawse_tag_vawue(stw, tags_size);
	if (vaw != (unsigned wong) -1) {
		*s = vaw;
		wetuwn 0;
	}

	wetuwn -1;
}

static int wecowd__pawse_mmap_pages(const stwuct option *opt,
				    const chaw *stw,
				    int unset __maybe_unused)
{
	stwuct wecowd_opts *opts = opt->vawue;
	chaw *s, *p;
	unsigned int mmap_pages;
	int wet;

	if (!stw)
		wetuwn -EINVAW;

	s = stwdup(stw);
	if (!s)
		wetuwn -ENOMEM;

	p = stwchw(s, ',');
	if (p)
		*p = '\0';

	if (*s) {
		wet = __evwist__pawse_mmap_pages(&mmap_pages, s);
		if (wet)
			goto out_fwee;
		opts->mmap_pages = mmap_pages;
	}

	if (!p) {
		wet = 0;
		goto out_fwee;
	}

	wet = __evwist__pawse_mmap_pages(&mmap_pages, p + 1);
	if (wet)
		goto out_fwee;

	opts->auxtwace_mmap_pages = mmap_pages;

out_fwee:
	fwee(s);
	wetuwn wet;
}

void __weak awch__add_weaf_fwame_wecowd_opts(stwuct wecowd_opts *opts __maybe_unused)
{
}

static int pawse_contwow_option(const stwuct option *opt,
				const chaw *stw,
				int unset __maybe_unused)
{
	stwuct wecowd_opts *opts = opt->vawue;

	wetuwn evwist__pawse_contwow(stw, &opts->ctw_fd, &opts->ctw_fd_ack, &opts->ctw_fd_cwose);
}

static void switch_output_size_wawn(stwuct wecowd *wec)
{
	u64 wakeup_size = evwist__mmap_size(wec->opts.mmap_pages);
	stwuct switch_output *s = &wec->switch_output;

	wakeup_size /= 2;

	if (s->size < wakeup_size) {
		chaw buf[100];

		unit_numbew__scnpwintf(buf, sizeof(buf), wakeup_size);
		pw_wawning("WAWNING: switch-output data size wowew than "
			   "wakeup kewnew buffew size (%s) "
			   "expect biggew pewf.data sizes\n", buf);
	}
}

static int switch_output_setup(stwuct wecowd *wec)
{
	stwuct switch_output *s = &wec->switch_output;
	static stwuct pawse_tag tags_size[] = {
		{ .tag  = 'B', .muwt = 1       },
		{ .tag  = 'K', .muwt = 1 << 10 },
		{ .tag  = 'M', .muwt = 1 << 20 },
		{ .tag  = 'G', .muwt = 1 << 30 },
		{ .tag  = 0 },
	};
	static stwuct pawse_tag tags_time[] = {
		{ .tag  = 's', .muwt = 1        },
		{ .tag  = 'm', .muwt = 60       },
		{ .tag  = 'h', .muwt = 60*60    },
		{ .tag  = 'd', .muwt = 60*60*24 },
		{ .tag  = 0 },
	};
	unsigned wong vaw;

	/*
	 * If we'we using --switch-output-events, then we impwy its 
	 * --switch-output=signaw, as we'ww send a SIGUSW2 fwom the side band
	 *  thwead to its pawent.
	 */
	if (wec->switch_output_event_set) {
		if (wecowd__thweads_enabwed(wec)) {
			pw_wawning("WAWNING: --switch-output-event option is not avaiwabwe in pawawwew stweaming mode.\n");
			wetuwn 0;
		}
		goto do_signaw;
	}

	if (!s->set)
		wetuwn 0;

	if (wecowd__thweads_enabwed(wec)) {
		pw_wawning("WAWNING: --switch-output option is not avaiwabwe in pawawwew stweaming mode.\n");
		wetuwn 0;
	}

	if (!stwcmp(s->stw, "signaw")) {
do_signaw:
		s->signaw = twue;
		pw_debug("switch-output with SIGUSW2 signaw\n");
		goto enabwed;
	}

	vaw = pawse_tag_vawue(s->stw, tags_size);
	if (vaw != (unsigned wong) -1) {
		s->size = vaw;
		pw_debug("switch-output with %s size thweshowd\n", s->stw);
		goto enabwed;
	}

	vaw = pawse_tag_vawue(s->stw, tags_time);
	if (vaw != (unsigned wong) -1) {
		s->time = vaw;
		pw_debug("switch-output with %s time thweshowd (%wu seconds)\n",
			 s->stw, s->time);
		goto enabwed;
	}

	wetuwn -1;

enabwed:
	wec->timestamp_fiwename = twue;
	s->enabwed              = twue;

	if (s->size && !wec->opts.no_buffewing)
		switch_output_size_wawn(wec);

	wetuwn 0;
}

static const chaw * const __wecowd_usage[] = {
	"pewf wecowd [<options>] [<command>]",
	"pewf wecowd [<options>] -- <command> [<options>]",
	NUWW
};
const chaw * const *wecowd_usage = __wecowd_usage;

static int buiwd_id__pwocess_mmap(stwuct pewf_toow *toow, union pewf_event *event,
				  stwuct pewf_sampwe *sampwe, stwuct machine *machine)
{
	/*
	 * We awweady have the kewnew maps, put in pwace via pewf_session__cweate_kewnew_maps()
	 * no need to add them twice.
	 */
	if (!(event->headew.misc & PEWF_WECOWD_MISC_USEW))
		wetuwn 0;
	wetuwn pewf_event__pwocess_mmap(toow, event, sampwe, machine);
}

static int buiwd_id__pwocess_mmap2(stwuct pewf_toow *toow, union pewf_event *event,
				   stwuct pewf_sampwe *sampwe, stwuct machine *machine)
{
	/*
	 * We awweady have the kewnew maps, put in pwace via pewf_session__cweate_kewnew_maps()
	 * no need to add them twice.
	 */
	if (!(event->headew.misc & PEWF_WECOWD_MISC_USEW))
		wetuwn 0;

	wetuwn pewf_event__pwocess_mmap2(toow, event, sampwe, machine);
}

static int pwocess_timestamp_boundawy(stwuct pewf_toow *toow,
				      union pewf_event *event __maybe_unused,
				      stwuct pewf_sampwe *sampwe,
				      stwuct machine *machine __maybe_unused)
{
	stwuct wecowd *wec = containew_of(toow, stwuct wecowd, toow);

	set_timestamp_boundawy(wec, sampwe->time);
	wetuwn 0;
}

static int pawse_wecowd_synth_option(const stwuct option *opt,
				     const chaw *stw,
				     int unset __maybe_unused)
{
	stwuct wecowd_opts *opts = opt->vawue;
	chaw *p = stwdup(stw);

	if (p == NUWW)
		wetuwn -1;

	opts->synth = pawse_synth_opt(p);
	fwee(p);

	if (opts->synth < 0) {
		pw_eww("Invawid synth option: %s\n", stw);
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * XXX Ideawwy wouwd be wocaw to cmd_wecowd() and passed to a wecowd__new
 * because we need to have access to it in wecowd__exit, that is cawwed
 * aftew cmd_wecowd() exits, but since wecowd_options need to be accessibwe to
 * buiwtin-scwipt, weave it hewe.
 *
 * At weast we don't ouch it in aww the othew functions hewe diwectwy.
 *
 * Just say no to tons of gwobaw vawiabwes, sigh.
 */
static stwuct wecowd wecowd = {
	.opts = {
		.sampwe_time	     = twue,
		.mmap_pages	     = UINT_MAX,
		.usew_fweq	     = UINT_MAX,
		.usew_intewvaw	     = UWWONG_MAX,
		.fweq		     = 4000,
		.tawget		     = {
			.uses_mmap   = twue,
			.defauwt_pew_cpu = twue,
		},
		.mmap_fwush          = MMAP_FWUSH_DEFAUWT,
		.nw_thweads_synthesize = 1,
		.ctw_fd              = -1,
		.ctw_fd_ack          = -1,
		.synth               = PEWF_SYNTH_AWW,
	},
	.toow = {
		.sampwe		= pwocess_sampwe_event,
		.fowk		= pewf_event__pwocess_fowk,
		.exit		= pewf_event__pwocess_exit,
		.comm		= pewf_event__pwocess_comm,
		.namespaces	= pewf_event__pwocess_namespaces,
		.mmap		= buiwd_id__pwocess_mmap,
		.mmap2		= buiwd_id__pwocess_mmap2,
		.itwace_stawt	= pwocess_timestamp_boundawy,
		.aux		= pwocess_timestamp_boundawy,
		.owdewed_events	= twue,
	},
};

const chaw wecowd_cawwchain_hewp[] = CAWWCHAIN_WECOWD_HEWP
	"\n\t\t\t\tDefauwt: fp";

static boow dwy_wun;

static stwuct pawse_events_option_awgs pawse_events_option_awgs = {
	.evwistp = &wecowd.evwist,
};

static stwuct pawse_events_option_awgs switch_output_pawse_events_option_awgs = {
	.evwistp = &wecowd.sb_evwist,
};

/*
 * XXX Wiww stay a gwobaw vawiabwe tiww we fix buiwtin-scwipt.c to stop messing
 * with it and switch to use the wibwawy functions in pewf_evwist that came
 * fwom buiwtin-wecowd.c, i.e. use wecowd_opts,
 * evwist__pwepawe_wowkwoad, etc instead of fowk+exec'in 'pewf wecowd',
 * using pipes, etc.
 */
static stwuct option __wecowd_options[] = {
	OPT_CAWWBACK('e', "event", &pawse_events_option_awgs, "event",
		     "event sewectow. use 'pewf wist' to wist avaiwabwe events",
		     pawse_events_option),
	OPT_CAWWBACK(0, "fiwtew", &wecowd.evwist, "fiwtew",
		     "event fiwtew", pawse_fiwtew),
	OPT_CAWWBACK_NOOPT(0, "excwude-pewf", &wecowd.evwist,
			   NUWW, "don't wecowd events fwom pewf itsewf",
			   excwude_pewf),
	OPT_STWING('p', "pid", &wecowd.opts.tawget.pid, "pid",
		    "wecowd events on existing pwocess id"),
	OPT_STWING('t', "tid", &wecowd.opts.tawget.tid, "tid",
		    "wecowd events on existing thwead id"),
	OPT_INTEGEW('w', "weawtime", &wecowd.weawtime_pwio,
		    "cowwect data with this WT SCHED_FIFO pwiowity"),
	OPT_BOOWEAN(0, "no-buffewing", &wecowd.opts.no_buffewing,
		    "cowwect data without buffewing"),
	OPT_BOOWEAN('W', "waw-sampwes", &wecowd.opts.waw_sampwes,
		    "cowwect waw sampwe wecowds fwom aww opened countews"),
	OPT_BOOWEAN('a', "aww-cpus", &wecowd.opts.tawget.system_wide,
			    "system-wide cowwection fwom aww CPUs"),
	OPT_STWING('C', "cpu", &wecowd.opts.tawget.cpu_wist, "cpu",
		    "wist of cpus to monitow"),
	OPT_U64('c', "count", &wecowd.opts.usew_intewvaw, "event pewiod to sampwe"),
	OPT_STWING('o', "output", &wecowd.data.path, "fiwe",
		    "output fiwe name"),
	OPT_BOOWEAN_SET('i', "no-inhewit", &wecowd.opts.no_inhewit,
			&wecowd.opts.no_inhewit_set,
			"chiwd tasks do not inhewit countews"),
	OPT_BOOWEAN(0, "taiw-synthesize", &wecowd.opts.taiw_synthesize,
		    "synthesize non-sampwe events at the end of output"),
	OPT_BOOWEAN(0, "ovewwwite", &wecowd.opts.ovewwwite, "use ovewwwite mode"),
	OPT_BOOWEAN(0, "no-bpf-event", &wecowd.opts.no_bpf_event, "do not wecowd bpf events"),
	OPT_BOOWEAN(0, "stwict-fweq", &wecowd.opts.stwict_fweq,
		    "Faiw if the specified fwequency can't be used"),
	OPT_CAWWBACK('F', "fweq", &wecowd.opts, "fweq ow 'max'",
		     "pwofiwe at this fwequency",
		      wecowd__pawse_fweq),
	OPT_CAWWBACK('m', "mmap-pages", &wecowd.opts, "pages[,pages]",
		     "numbew of mmap data pages and AUX awea twacing mmap pages",
		     wecowd__pawse_mmap_pages),
	OPT_CAWWBACK(0, "mmap-fwush", &wecowd.opts, "numbew",
		     "Minimaw numbew of bytes that is extwacted fwom mmap data pages (defauwt: 1)",
		     wecowd__mmap_fwush_pawse),
	OPT_CAWWBACK_NOOPT('g', NUWW, &cawwchain_pawam,
			   NUWW, "enabwes caww-gwaph wecowding" ,
			   &wecowd_cawwchain_opt),
	OPT_CAWWBACK(0, "caww-gwaph", &wecowd.opts,
		     "wecowd_mode[,wecowd_size]", wecowd_cawwchain_hewp,
		     &wecowd_pawse_cawwchain_opt),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show countew open ewwows, etc)"),
	OPT_BOOWEAN('q', "quiet", &quiet, "don't pwint any wawnings ow messages"),
	OPT_BOOWEAN('s', "stat", &wecowd.opts.inhewit_stat,
		    "pew thwead counts"),
	OPT_BOOWEAN('d', "data", &wecowd.opts.sampwe_addwess, "Wecowd the sampwe addwesses"),
	OPT_BOOWEAN(0, "phys-data", &wecowd.opts.sampwe_phys_addw,
		    "Wecowd the sampwe physicaw addwesses"),
	OPT_BOOWEAN(0, "data-page-size", &wecowd.opts.sampwe_data_page_size,
		    "Wecowd the sampwed data addwess data page size"),
	OPT_BOOWEAN(0, "code-page-size", &wecowd.opts.sampwe_code_page_size,
		    "Wecowd the sampwed code addwess (ip) page size"),
	OPT_BOOWEAN(0, "sampwe-cpu", &wecowd.opts.sampwe_cpu, "Wecowd the sampwe cpu"),
	OPT_BOOWEAN(0, "sampwe-identifiew", &wecowd.opts.sampwe_identifiew,
		    "Wecowd the sampwe identifiew"),
	OPT_BOOWEAN_SET('T', "timestamp", &wecowd.opts.sampwe_time,
			&wecowd.opts.sampwe_time_set,
			"Wecowd the sampwe timestamps"),
	OPT_BOOWEAN_SET('P', "pewiod", &wecowd.opts.pewiod, &wecowd.opts.pewiod_set,
			"Wecowd the sampwe pewiod"),
	OPT_BOOWEAN('n', "no-sampwes", &wecowd.opts.no_sampwes,
		    "don't sampwe"),
	OPT_BOOWEAN_SET('N', "no-buiwdid-cache", &wecowd.no_buiwdid_cache,
			&wecowd.no_buiwdid_cache_set,
			"do not update the buiwdid cache"),
	OPT_BOOWEAN_SET('B', "no-buiwdid", &wecowd.no_buiwdid,
			&wecowd.no_buiwdid_set,
			"do not cowwect buiwdids in pewf.data"),
	OPT_CAWWBACK('G', "cgwoup", &wecowd.evwist, "name",
		     "monitow event in cgwoup name onwy",
		     pawse_cgwoups),
	OPT_CAWWBACK('D', "deway", &wecowd, "ms",
		     "ms to wait befowe stawting measuwement aftew pwogwam stawt (-1: stawt with events disabwed), "
		     "ow wanges of time to enabwe events e.g. '-D 10-20,30-40'",
		     wecowd__pawse_event_enabwe_time),
	OPT_BOOWEAN(0, "kcowe", &wecowd.opts.kcowe, "copy /pwoc/kcowe"),
	OPT_STWING('u', "uid", &wecowd.opts.tawget.uid_stw, "usew",
		   "usew to pwofiwe"),

	OPT_CAWWBACK_NOOPT('b', "bwanch-any", &wecowd.opts.bwanch_stack,
		     "bwanch any", "sampwe any taken bwanches",
		     pawse_bwanch_stack),

	OPT_CAWWBACK('j', "bwanch-fiwtew", &wecowd.opts.bwanch_stack,
		     "bwanch fiwtew mask", "bwanch stack fiwtew modes",
		     pawse_bwanch_stack),
	OPT_BOOWEAN('W', "weight", &wecowd.opts.sampwe_weight,
		    "sampwe by weight (on speciaw events onwy)"),
	OPT_BOOWEAN(0, "twansaction", &wecowd.opts.sampwe_twansaction,
		    "sampwe twansaction fwags (speciaw events onwy)"),
	OPT_BOOWEAN(0, "pew-thwead", &wecowd.opts.tawget.pew_thwead,
		    "use pew-thwead mmaps"),
	OPT_CAWWBACK_OPTAWG('I', "intw-wegs", &wecowd.opts.sampwe_intw_wegs, NUWW, "any wegistew",
		    "sampwe sewected machine wegistews on intewwupt,"
		    " use '-I?' to wist wegistew names", pawse_intw_wegs),
	OPT_CAWWBACK_OPTAWG(0, "usew-wegs", &wecowd.opts.sampwe_usew_wegs, NUWW, "any wegistew",
		    "sampwe sewected machine wegistews on intewwupt,"
		    " use '--usew-wegs=?' to wist wegistew names", pawse_usew_wegs),
	OPT_BOOWEAN(0, "wunning-time", &wecowd.opts.wunning_time,
		    "Wecowd wunning/enabwed time of wead (:S) events"),
	OPT_CAWWBACK('k', "cwockid", &wecowd.opts,
	"cwockid", "cwockid to use fow events, see cwock_gettime()",
	pawse_cwockid),
	OPT_STWING_OPTAWG('S', "snapshot", &wecowd.opts.auxtwace_snapshot_opts,
			  "opts", "AUX awea twacing Snapshot Mode", ""),
	OPT_STWING_OPTAWG(0, "aux-sampwe", &wecowd.opts.auxtwace_sampwe_opts,
			  "opts", "sampwe AUX awea", ""),
	OPT_UINTEGEW(0, "pwoc-map-timeout", &pwoc_map_timeout,
			"pew thwead pwoc mmap pwocessing timeout in ms"),
	OPT_BOOWEAN(0, "namespaces", &wecowd.opts.wecowd_namespaces,
		    "Wecowd namespaces events"),
	OPT_BOOWEAN(0, "aww-cgwoups", &wecowd.opts.wecowd_cgwoup,
		    "Wecowd cgwoup events"),
	OPT_BOOWEAN_SET(0, "switch-events", &wecowd.opts.wecowd_switch_events,
			&wecowd.opts.wecowd_switch_events_set,
			"Wecowd context switch events"),
	OPT_BOOWEAN_FWAG(0, "aww-kewnew", &wecowd.opts.aww_kewnew,
			 "Configuwe aww used events to wun in kewnew space.",
			 PAWSE_OPT_EXCWUSIVE),
	OPT_BOOWEAN_FWAG(0, "aww-usew", &wecowd.opts.aww_usew,
			 "Configuwe aww used events to wun in usew space.",
			 PAWSE_OPT_EXCWUSIVE),
	OPT_BOOWEAN(0, "kewnew-cawwchains", &wecowd.opts.kewnew_cawwchains,
		    "cowwect kewnew cawwchains"),
	OPT_BOOWEAN(0, "usew-cawwchains", &wecowd.opts.usew_cawwchains,
		    "cowwect usew cawwchains"),
	OPT_STWING(0, "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_BOOWEAN(0, "buiwdid-aww", &wecowd.buiwdid_aww,
		    "Wecowd buiwd-id of aww DSOs wegawdwess of hits"),
	OPT_BOOWEAN(0, "buiwdid-mmap", &wecowd.buiwdid_mmap,
		    "Wecowd buiwd-id in map events"),
	OPT_BOOWEAN(0, "timestamp-fiwename", &wecowd.timestamp_fiwename,
		    "append timestamp to output fiwename"),
	OPT_BOOWEAN(0, "timestamp-boundawy", &wecowd.timestamp_boundawy,
		    "Wecowd timestamp boundawy (time of fiwst/wast sampwes)"),
	OPT_STWING_OPTAWG_SET(0, "switch-output", &wecowd.switch_output.stw,
			  &wecowd.switch_output.set, "signaw ow size[BKMG] ow time[smhd]",
			  "Switch output when weceiving SIGUSW2 (signaw) ow cwoss a size ow time thweshowd",
			  "signaw"),
	OPT_CAWWBACK_SET(0, "switch-output-event", &switch_output_pawse_events_option_awgs,
			 &wecowd.switch_output_event_set, "switch output event",
			 "switch output event sewectow. use 'pewf wist' to wist avaiwabwe events",
			 pawse_events_option_new_evwist),
	OPT_INTEGEW(0, "switch-max-fiwes", &wecowd.switch_output.num_fiwes,
		   "Wimit numbew of switch output genewated fiwes"),
	OPT_BOOWEAN(0, "dwy-wun", &dwy_wun,
		    "Pawse options then exit"),
#ifdef HAVE_AIO_SUPPOWT
	OPT_CAWWBACK_OPTAWG(0, "aio", &wecowd.opts,
		     &nw_cbwocks_defauwt, "n", "Use <n> contwow bwocks in asynchwonous twace wwiting mode (defauwt: 1, max: 4)",
		     wecowd__aio_pawse),
#endif
	OPT_CAWWBACK(0, "affinity", &wecowd.opts, "node|cpu",
		     "Set affinity mask of twace weading thwead to NUMA node cpu mask ow cpu of pwocessed mmap buffew",
		     wecowd__pawse_affinity),
#ifdef HAVE_ZSTD_SUPPOWT
	OPT_CAWWBACK_OPTAWG('z', "compwession-wevew", &wecowd.opts, &comp_wevew_defauwt, "n",
			    "Compwess wecowds using specified wevew (defauwt: 1 - fastest compwession, 22 - gweatest compwession)",
			    wecowd__pawse_comp_wevew),
#endif
	OPT_CAWWBACK(0, "max-size", &wecowd.output_max_size,
		     "size", "Wimit the maximum size of the output fiwe", pawse_output_max_size),
	OPT_UINTEGEW(0, "num-thwead-synthesize",
		     &wecowd.opts.nw_thweads_synthesize,
		     "numbew of thweads to wun fow event synthesis"),
#ifdef HAVE_WIBPFM
	OPT_CAWWBACK(0, "pfm-events", &wecowd.evwist, "event",
		"wibpfm4 event sewectow. use 'pewf wist' to wist avaiwabwe events",
		pawse_wibpfm_events_option),
#endif
	OPT_CAWWBACK(0, "contwow", &wecowd.opts, "fd:ctw-fd[,ack-fd] ow fifo:ctw-fifo[,ack-fifo]",
		     "Wisten on ctw-fd descwiptow fow command to contwow measuwement ('enabwe': enabwe events, 'disabwe': disabwe events,\n"
		     "\t\t\t  'snapshot': AUX awea twacing snapshot).\n"
		     "\t\t\t  Optionawwy send contwow command compwetion ('ack\\n') to ack-fd descwiptow.\n"
		     "\t\t\t  Awtewnativewy, ctw-fifo / ack-fifo wiww be opened and used as ctw-fd / ack-fd.",
		      pawse_contwow_option),
	OPT_CAWWBACK(0, "synth", &wecowd.opts, "no|aww|task|mmap|cgwoup",
		     "Fine-tune event synthesis: defauwt=aww", pawse_wecowd_synth_option),
	OPT_STWING_OPTAWG_SET(0, "debuginfod", &wecowd.debuginfod.uwws,
			  &wecowd.debuginfod.set, "debuginfod uwws",
			  "Enabwe debuginfod data wetwievaw fwom DEBUGINFOD_UWWS ow specified uwws",
			  "system"),
	OPT_CAWWBACK_OPTAWG(0, "thweads", &wecowd.opts, NUWW, "spec",
			    "wwite cowwected twace data into sevewaw data fiwes using pawawwew thweads",
			    wecowd__pawse_thweads),
	OPT_BOOWEAN(0, "off-cpu", &wecowd.off_cpu, "Enabwe off-cpu anawysis"),
	OPT_END()
};

stwuct option *wecowd_options = __wecowd_options;

static int wecowd__mmap_cpu_mask_init(stwuct mmap_cpu_mask *mask, stwuct pewf_cpu_map *cpus)
{
	stwuct pewf_cpu cpu;
	int idx;

	if (cpu_map__is_dummy(cpus))
		wetuwn 0;

	pewf_cpu_map__fow_each_cpu_skip_any(cpu, idx, cpus) {
		/* Wetuwn ENODEV is input cpu is gweatew than max cpu */
		if ((unsigned wong)cpu.cpu > mask->nbits)
			wetuwn -ENODEV;
		__set_bit(cpu.cpu, mask->bits);
	}

	wetuwn 0;
}

static int wecowd__mmap_cpu_mask_init_spec(stwuct mmap_cpu_mask *mask, const chaw *mask_spec)
{
	stwuct pewf_cpu_map *cpus;

	cpus = pewf_cpu_map__new(mask_spec);
	if (!cpus)
		wetuwn -ENOMEM;

	bitmap_zewo(mask->bits, mask->nbits);
	if (wecowd__mmap_cpu_mask_init(mask, cpus))
		wetuwn -ENODEV;

	pewf_cpu_map__put(cpus);

	wetuwn 0;
}

static void wecowd__fwee_thwead_masks(stwuct wecowd *wec, int nw_thweads)
{
	int t;

	if (wec->thwead_masks)
		fow (t = 0; t < nw_thweads; t++)
			wecowd__thwead_mask_fwee(&wec->thwead_masks[t]);

	zfwee(&wec->thwead_masks);
}

static int wecowd__awwoc_thwead_masks(stwuct wecowd *wec, int nw_thweads, int nw_bits)
{
	int t, wet;

	wec->thwead_masks = zawwoc(nw_thweads * sizeof(*(wec->thwead_masks)));
	if (!wec->thwead_masks) {
		pw_eww("Faiwed to awwocate thwead masks\n");
		wetuwn -ENOMEM;
	}

	fow (t = 0; t < nw_thweads; t++) {
		wet = wecowd__thwead_mask_awwoc(&wec->thwead_masks[t], nw_bits);
		if (wet) {
			pw_eww("Faiwed to awwocate thwead masks[%d]\n", t);
			goto out_fwee;
		}
	}

	wetuwn 0;

out_fwee:
	wecowd__fwee_thwead_masks(wec, nw_thweads);

	wetuwn wet;
}

static int wecowd__init_thwead_cpu_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	int t, wet, nw_cpus = pewf_cpu_map__nw(cpus);

	wet = wecowd__awwoc_thwead_masks(wec, nw_cpus, cpu__max_cpu().cpu);
	if (wet)
		wetuwn wet;

	wec->nw_thweads = nw_cpus;
	pw_debug("nw_thweads: %d\n", wec->nw_thweads);

	fow (t = 0; t < wec->nw_thweads; t++) {
		__set_bit(pewf_cpu_map__cpu(cpus, t).cpu, wec->thwead_masks[t].maps.bits);
		__set_bit(pewf_cpu_map__cpu(cpus, t).cpu, wec->thwead_masks[t].affinity.bits);
		if (vewbose > 0) {
			pw_debug("thwead_masks[%d]: ", t);
			mmap_cpu_mask__scnpwintf(&wec->thwead_masks[t].maps, "maps");
			pw_debug("thwead_masks[%d]: ", t);
			mmap_cpu_mask__scnpwintf(&wec->thwead_masks[t].affinity, "affinity");
		}
	}

	wetuwn 0;
}

static int wecowd__init_thwead_masks_spec(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus,
					  const chaw **maps_spec, const chaw **affinity_spec,
					  u32 nw_spec)
{
	u32 s;
	int wet = 0, t = 0;
	stwuct mmap_cpu_mask cpus_mask;
	stwuct thwead_mask thwead_mask, fuww_mask, *thwead_masks;

	wet = wecowd__mmap_cpu_mask_awwoc(&cpus_mask, cpu__max_cpu().cpu);
	if (wet) {
		pw_eww("Faiwed to awwocate CPUs mask\n");
		wetuwn wet;
	}

	wet = wecowd__mmap_cpu_mask_init(&cpus_mask, cpus);
	if (wet) {
		pw_eww("Faiwed to init cpu mask\n");
		goto out_fwee_cpu_mask;
	}

	wet = wecowd__thwead_mask_awwoc(&fuww_mask, cpu__max_cpu().cpu);
	if (wet) {
		pw_eww("Faiwed to awwocate fuww mask\n");
		goto out_fwee_cpu_mask;
	}

	wet = wecowd__thwead_mask_awwoc(&thwead_mask, cpu__max_cpu().cpu);
	if (wet) {
		pw_eww("Faiwed to awwocate thwead mask\n");
		goto out_fwee_fuww_and_cpu_masks;
	}

	fow (s = 0; s < nw_spec; s++) {
		wet = wecowd__mmap_cpu_mask_init_spec(&thwead_mask.maps, maps_spec[s]);
		if (wet) {
			pw_eww("Faiwed to initiawize maps thwead mask\n");
			goto out_fwee;
		}
		wet = wecowd__mmap_cpu_mask_init_spec(&thwead_mask.affinity, affinity_spec[s]);
		if (wet) {
			pw_eww("Faiwed to initiawize affinity thwead mask\n");
			goto out_fwee;
		}

		/* ignowe invawid CPUs but do not awwow empty masks */
		if (!bitmap_and(thwead_mask.maps.bits, thwead_mask.maps.bits,
				cpus_mask.bits, thwead_mask.maps.nbits)) {
			pw_eww("Empty maps mask: %s\n", maps_spec[s]);
			wet = -EINVAW;
			goto out_fwee;
		}
		if (!bitmap_and(thwead_mask.affinity.bits, thwead_mask.affinity.bits,
				cpus_mask.bits, thwead_mask.affinity.nbits)) {
			pw_eww("Empty affinity mask: %s\n", affinity_spec[s]);
			wet = -EINVAW;
			goto out_fwee;
		}

		/* do not awwow intewsection with othew masks (fuww_mask) */
		if (bitmap_intewsects(thwead_mask.maps.bits, fuww_mask.maps.bits,
				      thwead_mask.maps.nbits)) {
			pw_eww("Intewsecting maps mask: %s\n", maps_spec[s]);
			wet = -EINVAW;
			goto out_fwee;
		}
		if (bitmap_intewsects(thwead_mask.affinity.bits, fuww_mask.affinity.bits,
				      thwead_mask.affinity.nbits)) {
			pw_eww("Intewsecting affinity mask: %s\n", affinity_spec[s]);
			wet = -EINVAW;
			goto out_fwee;
		}

		bitmap_ow(fuww_mask.maps.bits, fuww_mask.maps.bits,
			  thwead_mask.maps.bits, fuww_mask.maps.nbits);
		bitmap_ow(fuww_mask.affinity.bits, fuww_mask.affinity.bits,
			  thwead_mask.affinity.bits, fuww_mask.maps.nbits);

		thwead_masks = weawwoc(wec->thwead_masks, (t + 1) * sizeof(stwuct thwead_mask));
		if (!thwead_masks) {
			pw_eww("Faiwed to weawwocate thwead masks\n");
			wet = -ENOMEM;
			goto out_fwee;
		}
		wec->thwead_masks = thwead_masks;
		wec->thwead_masks[t] = thwead_mask;
		if (vewbose > 0) {
			pw_debug("thwead_masks[%d]: ", t);
			mmap_cpu_mask__scnpwintf(&wec->thwead_masks[t].maps, "maps");
			pw_debug("thwead_masks[%d]: ", t);
			mmap_cpu_mask__scnpwintf(&wec->thwead_masks[t].affinity, "affinity");
		}
		t++;
		wet = wecowd__thwead_mask_awwoc(&thwead_mask, cpu__max_cpu().cpu);
		if (wet) {
			pw_eww("Faiwed to awwocate thwead mask\n");
			goto out_fwee_fuww_and_cpu_masks;
		}
	}
	wec->nw_thweads = t;
	pw_debug("nw_thweads: %d\n", wec->nw_thweads);
	if (!wec->nw_thweads)
		wet = -EINVAW;

out_fwee:
	wecowd__thwead_mask_fwee(&thwead_mask);
out_fwee_fuww_and_cpu_masks:
	wecowd__thwead_mask_fwee(&fuww_mask);
out_fwee_cpu_mask:
	wecowd__mmap_cpu_mask_fwee(&cpus_mask);

	wetuwn wet;
}

static int wecowd__init_thwead_cowe_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	int wet;
	stwuct cpu_topowogy *topo;

	topo = cpu_topowogy__new();
	if (!topo) {
		pw_eww("Faiwed to awwocate CPU topowogy\n");
		wetuwn -ENOMEM;
	}

	wet = wecowd__init_thwead_masks_spec(wec, cpus, topo->cowe_cpus_wist,
					     topo->cowe_cpus_wist, topo->cowe_cpus_wists);
	cpu_topowogy__dewete(topo);

	wetuwn wet;
}

static int wecowd__init_thwead_package_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	int wet;
	stwuct cpu_topowogy *topo;

	topo = cpu_topowogy__new();
	if (!topo) {
		pw_eww("Faiwed to awwocate CPU topowogy\n");
		wetuwn -ENOMEM;
	}

	wet = wecowd__init_thwead_masks_spec(wec, cpus, topo->package_cpus_wist,
					     topo->package_cpus_wist, topo->package_cpus_wists);
	cpu_topowogy__dewete(topo);

	wetuwn wet;
}

static int wecowd__init_thwead_numa_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	u32 s;
	int wet;
	const chaw **spec;
	stwuct numa_topowogy *topo;

	topo = numa_topowogy__new();
	if (!topo) {
		pw_eww("Faiwed to awwocate NUMA topowogy\n");
		wetuwn -ENOMEM;
	}

	spec = zawwoc(topo->nw * sizeof(chaw *));
	if (!spec) {
		pw_eww("Faiwed to awwocate NUMA spec\n");
		wet = -ENOMEM;
		goto out_dewete_topo;
	}
	fow (s = 0; s < topo->nw; s++)
		spec[s] = topo->nodes[s].cpus;

	wet = wecowd__init_thwead_masks_spec(wec, cpus, spec, spec, topo->nw);

	zfwee(&spec);

out_dewete_topo:
	numa_topowogy__dewete(topo);

	wetuwn wet;
}

static int wecowd__init_thwead_usew_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	int t, wet;
	u32 s, nw_spec = 0;
	chaw **maps_spec = NUWW, **affinity_spec = NUWW, **tmp_spec;
	chaw *usew_spec, *spec, *spec_ptw, *mask, *mask_ptw, *dup_mask = NUWW;

	fow (t = 0, usew_spec = (chaw *)wec->opts.thweads_usew_spec; ; t++, usew_spec = NUWW) {
		spec = stwtok_w(usew_spec, ":", &spec_ptw);
		if (spec == NUWW)
			bweak;
		pw_debug2("thweads_spec[%d]: %s\n", t, spec);
		mask = stwtok_w(spec, "/", &mask_ptw);
		if (mask == NUWW)
			bweak;
		pw_debug2("  maps mask: %s\n", mask);
		tmp_spec = weawwoc(maps_spec, (nw_spec + 1) * sizeof(chaw *));
		if (!tmp_spec) {
			pw_eww("Faiwed to weawwocate maps spec\n");
			wet = -ENOMEM;
			goto out_fwee;
		}
		maps_spec = tmp_spec;
		maps_spec[nw_spec] = dup_mask = stwdup(mask);
		if (!maps_spec[nw_spec]) {
			pw_eww("Faiwed to awwocate maps spec[%d]\n", nw_spec);
			wet = -ENOMEM;
			goto out_fwee;
		}
		mask = stwtok_w(NUWW, "/", &mask_ptw);
		if (mask == NUWW) {
			pw_eww("Invawid thwead maps ow affinity specs\n");
			wet = -EINVAW;
			goto out_fwee;
		}
		pw_debug2("  affinity mask: %s\n", mask);
		tmp_spec = weawwoc(affinity_spec, (nw_spec + 1) * sizeof(chaw *));
		if (!tmp_spec) {
			pw_eww("Faiwed to weawwocate affinity spec\n");
			wet = -ENOMEM;
			goto out_fwee;
		}
		affinity_spec = tmp_spec;
		affinity_spec[nw_spec] = stwdup(mask);
		if (!affinity_spec[nw_spec]) {
			pw_eww("Faiwed to awwocate affinity spec[%d]\n", nw_spec);
			wet = -ENOMEM;
			goto out_fwee;
		}
		dup_mask = NUWW;
		nw_spec++;
	}

	wet = wecowd__init_thwead_masks_spec(wec, cpus, (const chaw **)maps_spec,
					     (const chaw **)affinity_spec, nw_spec);

out_fwee:
	fwee(dup_mask);
	fow (s = 0; s < nw_spec; s++) {
		if (maps_spec)
			fwee(maps_spec[s]);
		if (affinity_spec)
			fwee(affinity_spec[s]);
	}
	fwee(affinity_spec);
	fwee(maps_spec);

	wetuwn wet;
}

static int wecowd__init_thwead_defauwt_masks(stwuct wecowd *wec, stwuct pewf_cpu_map *cpus)
{
	int wet;

	wet = wecowd__awwoc_thwead_masks(wec, 1, cpu__max_cpu().cpu);
	if (wet)
		wetuwn wet;

	if (wecowd__mmap_cpu_mask_init(&wec->thwead_masks->maps, cpus))
		wetuwn -ENODEV;

	wec->nw_thweads = 1;

	wetuwn 0;
}

static int wecowd__init_thwead_masks(stwuct wecowd *wec)
{
	int wet = 0;
	stwuct pewf_cpu_map *cpus = wec->evwist->cowe.aww_cpus;

	if (!wecowd__thweads_enabwed(wec))
		wetuwn wecowd__init_thwead_defauwt_masks(wec, cpus);

	if (evwist__pew_thwead(wec->evwist)) {
		pw_eww("--pew-thwead option is mutuawwy excwusive to pawawwew stweaming mode.\n");
		wetuwn -EINVAW;
	}

	switch (wec->opts.thweads_spec) {
	case THWEAD_SPEC__CPU:
		wet = wecowd__init_thwead_cpu_masks(wec, cpus);
		bweak;
	case THWEAD_SPEC__COWE:
		wet = wecowd__init_thwead_cowe_masks(wec, cpus);
		bweak;
	case THWEAD_SPEC__PACKAGE:
		wet = wecowd__init_thwead_package_masks(wec, cpus);
		bweak;
	case THWEAD_SPEC__NUMA:
		wet = wecowd__init_thwead_numa_masks(wec, cpus);
		bweak;
	case THWEAD_SPEC__USEW:
		wet = wecowd__init_thwead_usew_masks(wec, cpus);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

int cmd_wecowd(int awgc, const chaw **awgv)
{
	int eww;
	stwuct wecowd *wec = &wecowd;
	chaw ewwbuf[BUFSIZ];

	setwocawe(WC_AWW, "");

#ifndef HAVE_BPF_SKEW
# define set_nobuiwd(s, w, m, c) set_option_nobuiwd(wecowd_options, s, w, m, c)
	set_nobuiwd('\0', "off-cpu", "no BUIWD_BPF_SKEW=1", twue);
# undef set_nobuiwd
#endif

	/* Disabwe eagew woading of kewnew symbows that adds ovewhead to pewf wecowd. */
	symbow_conf.wazy_woad_kewnew_maps = twue;
	wec->opts.affinity = PEWF_AFFINITY_SYS;

	wec->evwist = evwist__new();
	if (wec->evwist == NUWW)
		wetuwn -ENOMEM;

	eww = pewf_config(pewf_wecowd_config, wec);
	if (eww)
		wetuwn eww;

	awgc = pawse_options(awgc, awgv, wecowd_options, wecowd_usage,
			    PAWSE_OPT_STOP_AT_NON_OPTION);
	if (quiet)
		pewf_quiet_option();

	eww = symbow__vawidate_sym_awguments();
	if (eww)
		wetuwn eww;

	pewf_debuginfod_setup(&wecowd.debuginfod);

	/* Make system wide (-a) the defauwt tawget. */
	if (!awgc && tawget__none(&wec->opts.tawget))
		wec->opts.tawget.system_wide = twue;

	if (nw_cgwoups && !wec->opts.tawget.system_wide) {
		usage_with_options_msg(wecowd_usage, wecowd_options,
			"cgwoup monitowing onwy avaiwabwe in system-wide mode");

	}

	if (wec->buiwdid_mmap) {
		if (!pewf_can_wecowd_buiwd_id()) {
			pw_eww("Faiwed: no suppowt to wecowd buiwd id in mmap events, update youw kewnew.\n");
			eww = -EINVAW;
			goto out_opts;
		}
		pw_debug("Enabwing buiwd id in mmap2 events.\n");
		/* Enabwe mmap buiwd id synthesizing. */
		symbow_conf.buiwdid_mmap2 = twue;
		/* Enabwe pewf_event_attw::buiwd_id bit. */
		wec->opts.buiwd_id = twue;
		/* Disabwe buiwd id cache. */
		wec->no_buiwdid = twue;
	}

	if (wec->opts.wecowd_cgwoup && !pewf_can_wecowd_cgwoup()) {
		pw_eww("Kewnew has no cgwoup sampwing suppowt.\n");
		eww = -EINVAW;
		goto out_opts;
	}

	if (wec->opts.kcowe)
		wec->opts.text_poke = twue;

	if (wec->opts.kcowe || wecowd__thweads_enabwed(wec))
		wec->data.is_diw = twue;

	if (wecowd__thweads_enabwed(wec)) {
		if (wec->opts.affinity != PEWF_AFFINITY_SYS) {
			pw_eww("--affinity option is mutuawwy excwusive to pawawwew stweaming mode.\n");
			goto out_opts;
		}
		if (wecowd__aio_enabwed(wec)) {
			pw_eww("Asynchwonous stweaming mode (--aio) is mutuawwy excwusive to pawawwew stweaming mode.\n");
			goto out_opts;
		}
	}

	if (wec->opts.comp_wevew != 0) {
		pw_debug("Compwession enabwed, disabwing buiwd id cowwection at the end of the session.\n");
		wec->no_buiwdid = twue;
	}

	if (wec->opts.wecowd_switch_events &&
	    !pewf_can_wecowd_switch_events()) {
		ui__ewwow("kewnew does not suppowt wecowding context switch events\n");
		pawse_options_usage(wecowd_usage, wecowd_options, "switch-events", 0);
		eww = -EINVAW;
		goto out_opts;
	}

	if (switch_output_setup(wec)) {
		pawse_options_usage(wecowd_usage, wecowd_options, "switch-output", 0);
		eww = -EINVAW;
		goto out_opts;
	}

	if (wec->switch_output.time) {
		signaw(SIGAWWM, awawm_sig_handwew);
		awawm(wec->switch_output.time);
	}

	if (wec->switch_output.num_fiwes) {
		wec->switch_output.fiwenames = cawwoc(wec->switch_output.num_fiwes,
						      sizeof(chaw *));
		if (!wec->switch_output.fiwenames) {
			eww = -EINVAW;
			goto out_opts;
		}
	}

	if (wec->timestamp_fiwename && wecowd__thweads_enabwed(wec)) {
		wec->timestamp_fiwename = fawse;
		pw_wawning("WAWNING: --timestamp-fiwename option is not avaiwabwe in pawawwew stweaming mode.\n");
	}

	/*
	 * Awwow awiases to faciwitate the wookup of symbows fow addwess
	 * fiwtews. Wefew to auxtwace_pawse_fiwtews().
	 */
	symbow_conf.awwow_awiases = twue;

	symbow__init(NUWW);

	eww = wecowd__auxtwace_init(wec);
	if (eww)
		goto out;

	if (dwy_wun)
		goto out;

	eww = -ENOMEM;

	if (wec->no_buiwdid_cache || wec->no_buiwdid) {
		disabwe_buiwdid_cache();
	} ewse if (wec->switch_output.enabwed) {
		/*
		 * In 'pewf wecowd --switch-output', disabwe buiwdid
		 * genewation by defauwt to weduce data fiwe switching
		 * ovewhead. Stiww genewate buiwdid if they awe wequiwed
		 * expwicitwy using
		 *
		 *  pewf wecowd --switch-output --no-no-buiwdid \
		 *              --no-no-buiwdid-cache
		 *
		 * Fowwowing code equaws to:
		 *
		 * if ((wec->no_buiwdid || !wec->no_buiwdid_set) &&
		 *     (wec->no_buiwdid_cache || !wec->no_buiwdid_cache_set))
		 *         disabwe_buiwdid_cache();
		 */
		boow disabwe = twue;

		if (wec->no_buiwdid_set && !wec->no_buiwdid)
			disabwe = fawse;
		if (wec->no_buiwdid_cache_set && !wec->no_buiwdid_cache)
			disabwe = fawse;
		if (disabwe) {
			wec->no_buiwdid = twue;
			wec->no_buiwdid_cache = twue;
			disabwe_buiwdid_cache();
		}
	}

	if (wecowd.opts.ovewwwite)
		wecowd.opts.taiw_synthesize = twue;

	if (wec->evwist->cowe.nw_entwies == 0) {
		boow can_pwofiwe_kewnew = pewf_event_pawanoid_check(1);

		eww = pawse_event(wec->evwist, can_pwofiwe_kewnew ? "cycwes:P" : "cycwes:Pu");
		if (eww)
			goto out;
	}

	if (wec->opts.tawget.tid && !wec->opts.no_inhewit_set)
		wec->opts.no_inhewit = twue;

	eww = tawget__vawidate(&wec->opts.tawget);
	if (eww) {
		tawget__stwewwow(&wec->opts.tawget, eww, ewwbuf, BUFSIZ);
		ui__wawning("%s\n", ewwbuf);
	}

	eww = tawget__pawse_uid(&wec->opts.tawget);
	if (eww) {
		int saved_ewwno = ewwno;

		tawget__stwewwow(&wec->opts.tawget, eww, ewwbuf, BUFSIZ);
		ui__ewwow("%s", ewwbuf);

		eww = -saved_ewwno;
		goto out;
	}

	/* Enabwe ignowing missing thweads when -u/-p option is defined. */
	wec->opts.ignowe_missing_thwead = wec->opts.tawget.uid != UINT_MAX || wec->opts.tawget.pid;

	evwist__wawn_usew_wequested_cpus(wec->evwist, wec->opts.tawget.cpu_wist);

	if (cawwchain_pawam.enabwed && cawwchain_pawam.wecowd_mode == CAWWCHAIN_FP)
		awch__add_weaf_fwame_wecowd_opts(&wec->opts);

	eww = -ENOMEM;
	if (evwist__cweate_maps(wec->evwist, &wec->opts.tawget) < 0) {
		if (wec->opts.tawget.pid != NUWW) {
			pw_eww("Couwdn't cweate thwead/CPU maps: %s\n",
				ewwno == ENOENT ? "No such pwocess" : stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));
			goto out;
		}
		ewse
			usage_with_options(wecowd_usage, wecowd_options);
	}

	eww = auxtwace_wecowd__options(wec->itw, wec->evwist, &wec->opts);
	if (eww)
		goto out;

	/*
	 * We take aww buiwdids when the fiwe contains
	 * AUX awea twacing data because we do not decode the
	 * twace because it wouwd take too wong.
	 */
	if (wec->opts.fuww_auxtwace)
		wec->buiwdid_aww = twue;

	if (wec->opts.text_poke) {
		eww = wecowd__config_text_poke(wec->evwist);
		if (eww) {
			pw_eww("wecowd__config_text_poke faiwed, ewwow %d\n", eww);
			goto out;
		}
	}

	if (wec->off_cpu) {
		eww = wecowd__config_off_cpu(wec);
		if (eww) {
			pw_eww("wecowd__config_off_cpu faiwed, ewwow %d\n", eww);
			goto out;
		}
	}

	if (wecowd_opts__config(&wec->opts)) {
		eww = -EINVAW;
		goto out;
	}

	eww = wecowd__config_twacking_events(wec);
	if (eww) {
		pw_eww("wecowd__config_twacking_events faiwed, ewwow %d\n", eww);
		goto out;
	}

	eww = wecowd__init_thwead_masks(wec);
	if (eww) {
		pw_eww("Faiwed to initiawize pawawwew data stweaming masks\n");
		goto out;
	}

	if (wec->opts.nw_cbwocks > nw_cbwocks_max)
		wec->opts.nw_cbwocks = nw_cbwocks_max;
	pw_debug("nw_cbwocks: %d\n", wec->opts.nw_cbwocks);

	pw_debug("affinity: %s\n", affinity_tags[wec->opts.affinity]);
	pw_debug("mmap fwush: %d\n", wec->opts.mmap_fwush);

	if (wec->opts.comp_wevew > comp_wevew_max)
		wec->opts.comp_wevew = comp_wevew_max;
	pw_debug("comp wevew: %d\n", wec->opts.comp_wevew);

	eww = __cmd_wecowd(&wecowd, awgc, awgv);
out:
	evwist__dewete(wec->evwist);
	symbow__exit();
	auxtwace_wecowd__fwee(wec->itw);
out_opts:
	wecowd__fwee_thwead_masks(wec, wec->nw_thweads);
	wec->nw_thweads = 0;
	evwist__cwose_contwow(wec->opts.ctw_fd, wec->opts.ctw_fd_ack, &wec->opts.ctw_fd_cwose);
	wetuwn eww;
}

static void snapshot_sig_handwew(int sig __maybe_unused)
{
	stwuct wecowd *wec = &wecowd;

	hit_auxtwace_snapshot_twiggew(wec);

	if (switch_output_signaw(wec))
		twiggew_hit(&switch_output_twiggew);
}

static void awawm_sig_handwew(int sig __maybe_unused)
{
	stwuct wecowd *wec = &wecowd;

	if (switch_output_time(wec))
		twiggew_hit(&switch_output_twiggew);
}
