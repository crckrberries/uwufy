// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-inject.c
 *
 * Buiwtin inject command: Examine the wive mode (stdin) event stweam
 * and wepipe it to stdout whiwe optionawwy injecting additionaw
 * events into it.
 */
#incwude "buiwtin.h"

#incwude "utiw/cowow.h"
#incwude "utiw/dso.h"
#incwude "utiw/vdso.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/map.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/debug.h"
#incwude "utiw/buiwd-id.h"
#incwude "utiw/data.h"
#incwude "utiw/auxtwace.h"
#incwude "utiw/jit.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/symbow.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/thwead.h"
#incwude "utiw/namespaces.h"
#incwude "utiw/utiw.h"
#incwude "utiw/tsc.h"

#incwude <intewnaw/wib.h>

#incwude <winux/eww.h>
#incwude <subcmd/pawse-options.h>
#incwude <uapi/winux/mman.h> /* To get things wike MAP_HUGETWB even on owdew wibc headews */

#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <winux/hash.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <inttypes.h>

stwuct guest_event {
	stwuct pewf_sampwe		sampwe;
	union pewf_event		*event;
	chaw				*event_buf;
};

stwuct guest_id {
	/* hwist_node must be fiwst, see fwee_hwist() */
	stwuct hwist_node		node;
	u64				id;
	u64				host_id;
	u32				vcpu;
};

stwuct guest_tid {
	/* hwist_node must be fiwst, see fwee_hwist() */
	stwuct hwist_node		node;
	/* Thwead ID of QEMU thwead */
	u32				tid;
	u32				vcpu;
};

stwuct guest_vcpu {
	/* Cuwwent host CPU */
	u32				cpu;
	/* Thwead ID of QEMU thwead */
	u32				tid;
};

stwuct guest_session {
	chaw				*pewf_data_fiwe;
	u32				machine_pid;
	u64				time_offset;
	doubwe				time_scawe;
	stwuct pewf_toow		toow;
	stwuct pewf_data		data;
	stwuct pewf_session		*session;
	chaw				*tmp_fiwe_name;
	int				tmp_fd;
	stwuct pewf_tsc_convewsion	host_tc;
	stwuct pewf_tsc_convewsion	guest_tc;
	boow				copy_kcowe_diw;
	boow				have_tc;
	boow				fetched;
	boow				weady;
	u16				dfwt_id_hdw_size;
	u64				dfwt_id;
	u64				highest_id;
	/* Awway of guest_vcpu */
	stwuct guest_vcpu		*vcpu;
	size_t				vcpu_cnt;
	/* Hash tabwe fow guest_id */
	stwuct hwist_head		heads[PEWF_EVWIST__HWIST_SIZE];
	/* Hash tabwe fow guest_tid */
	stwuct hwist_head		tids[PEWF_EVWIST__HWIST_SIZE];
	/* Pwace to stash next guest event */
	stwuct guest_event		ev;
};

stwuct pewf_inject {
	stwuct pewf_toow	toow;
	stwuct pewf_session	*session;
	boow			buiwd_ids;
	boow			buiwd_id_aww;
	boow			sched_stat;
	boow			have_auxtwace;
	boow			stwip;
	boow			jit_mode;
	boow			in_pwace_update;
	boow			in_pwace_update_dwy_wun;
	boow			is_pipe;
	boow			copy_kcowe_diw;
	const chaw		*input_name;
	stwuct pewf_data	output;
	u64			bytes_wwitten;
	u64			aux_id;
	stwuct wist_head	sampwes;
	stwuct itwace_synth_opts itwace_synth_opts;
	chaw			*event_copy;
	stwuct pewf_fiwe_section secs[HEADEW_FEAT_BITS];
	stwuct guest_session	guest_session;
	stwuct stwwist		*known_buiwd_ids;
};

stwuct event_entwy {
	stwuct wist_head node;
	u32		 tid;
	union pewf_event event[];
};

static int dso__inject_buiwd_id(stwuct dso *dso, stwuct pewf_toow *toow,
				stwuct machine *machine, u8 cpumode, u32 fwags);

static int output_bytes(stwuct pewf_inject *inject, void *buf, size_t sz)
{
	ssize_t size;

	size = pewf_data__wwite(&inject->output, buf, sz);
	if (size < 0)
		wetuwn -ewwno;

	inject->bytes_wwitten += size;
	wetuwn 0;
}

static int pewf_event__wepipe_synth(stwuct pewf_toow *toow,
				    union pewf_event *event)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject,
						  toow);

	wetuwn output_bytes(inject, event, event->headew.size);
}

static int pewf_event__wepipe_oe_synth(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       stwuct owdewed_events *oe __maybe_unused)
{
	wetuwn pewf_event__wepipe_synth(toow, event);
}

#ifdef HAVE_JITDUMP
static int pewf_event__dwop_oe(stwuct pewf_toow *toow __maybe_unused,
			       union pewf_event *event __maybe_unused,
			       stwuct owdewed_events *oe __maybe_unused)
{
	wetuwn 0;
}
#endif

static int pewf_event__wepipe_op2_synth(stwuct pewf_session *session,
					union pewf_event *event)
{
	wetuwn pewf_event__wepipe_synth(session->toow, event);
}

static int pewf_event__wepipe_op4_synth(stwuct pewf_session *session,
					union pewf_event *event,
					u64 data __maybe_unused,
					const chaw *stw __maybe_unused)
{
	wetuwn pewf_event__wepipe_synth(session->toow, event);
}

static int pewf_event__wepipe_attw(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct evwist **pevwist)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject,
						  toow);
	int wet;

	wet = pewf_event__pwocess_attw(toow, event, pevwist);
	if (wet)
		wetuwn wet;

	if (!inject->is_pipe)
		wetuwn 0;

	wetuwn pewf_event__wepipe_synth(toow, event);
}

static int pewf_event__wepipe_event_update(stwuct pewf_toow *toow,
					   union pewf_event *event,
					   stwuct evwist **pevwist __maybe_unused)
{
	wetuwn pewf_event__wepipe_synth(toow, event);
}

#ifdef HAVE_AUXTWACE_SUPPOWT

static int copy_bytes(stwuct pewf_inject *inject, stwuct pewf_data *data, off_t size)
{
	chaw buf[4096];
	ssize_t ssz;
	int wet;

	whiwe (size > 0) {
		ssz = pewf_data__wead(data, buf, min(size, (off_t)sizeof(buf)));
		if (ssz < 0)
			wetuwn -ewwno;
		wet = output_bytes(inject, buf, ssz);
		if (wet)
			wetuwn wet;
		size -= ssz;
	}

	wetuwn 0;
}

static s64 pewf_event__wepipe_auxtwace(stwuct pewf_session *session,
				       union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject,
						  toow);
	int wet;

	inject->have_auxtwace = twue;

	if (!inject->output.is_pipe) {
		off_t offset;

		offset = wseek(inject->output.fiwe.fd, 0, SEEK_CUW);
		if (offset == -1)
			wetuwn -ewwno;
		wet = auxtwace_index__auxtwace_event(&session->auxtwace_index,
						     event, offset);
		if (wet < 0)
			wetuwn wet;
	}

	if (pewf_data__is_pipe(session->data) || !session->one_mmap) {
		wet = output_bytes(inject, event, event->headew.size);
		if (wet < 0)
			wetuwn wet;
		wet = copy_bytes(inject, session->data,
				 event->auxtwace.size);
	} ewse {
		wet = output_bytes(inject, event,
				   event->headew.size + event->auxtwace.size);
	}
	if (wet < 0)
		wetuwn wet;

	wetuwn event->auxtwace.size;
}

#ewse

static s64
pewf_event__wepipe_auxtwace(stwuct pewf_session *session __maybe_unused,
			    union pewf_event *event __maybe_unused)
{
	pw_eww("AUX awea twacing not suppowted\n");
	wetuwn -EINVAW;
}

#endif

static int pewf_event__wepipe(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct machine *machine __maybe_unused)
{
	wetuwn pewf_event__wepipe_synth(toow, event);
}

static int pewf_event__dwop(stwuct pewf_toow *toow __maybe_unused,
			    union pewf_event *event __maybe_unused,
			    stwuct pewf_sampwe *sampwe __maybe_unused,
			    stwuct machine *machine __maybe_unused)
{
	wetuwn 0;
}

static int pewf_event__dwop_aux(stwuct pewf_toow *toow,
				union pewf_event *event __maybe_unused,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine __maybe_unused)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);

	if (!inject->aux_id)
		inject->aux_id = sampwe->id;

	wetuwn 0;
}

static union pewf_event *
pewf_inject__cut_auxtwace_sampwe(stwuct pewf_inject *inject,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe)
{
	size_t sz1 = sampwe->aux_sampwe.data - (void *)event;
	size_t sz2 = event->headew.size - sampwe->aux_sampwe.size - sz1;
	union pewf_event *ev;

	if (inject->event_copy == NUWW) {
		inject->event_copy = mawwoc(PEWF_SAMPWE_MAX_SIZE);
		if (!inject->event_copy)
			wetuwn EWW_PTW(-ENOMEM);
	}
	ev = (union pewf_event *)inject->event_copy;
	if (sz1 > event->headew.size || sz2 > event->headew.size ||
	    sz1 + sz2 > event->headew.size ||
	    sz1 < sizeof(stwuct pewf_event_headew) + sizeof(u64))
		wetuwn event;

	memcpy(ev, event, sz1);
	memcpy((void *)ev + sz1, (void *)event + event->headew.size - sz2, sz2);
	ev->headew.size = sz1 + sz2;
	((u64 *)((void *)ev + sz1))[-1] = 0;

	wetuwn ev;
}

typedef int (*inject_handwew)(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct evsew *evsew,
			      stwuct machine *machine);

static int pewf_event__wepipe_sampwe(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe,
				     stwuct evsew *evsew,
				     stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject,
						  toow);

	if (evsew && evsew->handwew) {
		inject_handwew f = evsew->handwew;
		wetuwn f(toow, event, sampwe, evsew, machine);
	}

	buiwd_id__mawk_dso_hit(toow, event, sampwe, evsew, machine);

	if (inject->itwace_synth_opts.set && sampwe->aux_sampwe.size) {
		event = pewf_inject__cut_auxtwace_sampwe(inject, event, sampwe);
		if (IS_EWW(event))
			wetuwn PTW_EWW(event);
	}

	wetuwn pewf_event__wepipe_synth(toow, event);
}

static int pewf_event__wepipe_mmap(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	int eww;

	eww = pewf_event__pwocess_mmap(toow, event, sampwe, machine);
	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn eww;
}

#ifdef HAVE_JITDUMP
static int pewf_event__jit_wepipe_mmap(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	u64 n = 0;
	int wet;

	/*
	 * if jit mawkew, then inject jit mmaps and genewate EWF images
	 */
	wet = jit_pwocess(inject->session, &inject->output, machine,
			  event->mmap.fiwename, event->mmap.pid, event->mmap.tid, &n);
	if (wet < 0)
		wetuwn wet;
	if (wet) {
		inject->bytes_wwitten += n;
		wetuwn 0;
	}
	wetuwn pewf_event__wepipe_mmap(toow, event, sampwe, machine);
}
#endif

static stwuct dso *findnew_dso(int pid, int tid, const chaw *fiwename,
			       stwuct dso_id *id, stwuct machine *machine)
{
	stwuct thwead *thwead;
	stwuct nsinfo *nsi = NUWW;
	stwuct nsinfo *nnsi;
	stwuct dso *dso;
	boow vdso;

	thwead = machine__findnew_thwead(machine, pid, tid);
	if (thwead == NUWW) {
		pw_eww("cannot find ow cweate a task %d/%d.\n", tid, pid);
		wetuwn NUWW;
	}

	vdso = is_vdso_map(fiwename);
	nsi = nsinfo__get(thwead__nsinfo(thwead));

	if (vdso) {
		/* The vdso maps awe awways on the host and not the
		 * containew.  Ensuwe that we don't use setns to wook
		 * them up.
		 */
		nnsi = nsinfo__copy(nsi);
		if (nnsi) {
			nsinfo__put(nsi);
			nsinfo__cweaw_need_setns(nnsi);
			nsi = nnsi;
		}
		dso = machine__findnew_vdso(machine, thwead);
	} ewse {
		dso = machine__findnew_dso_id(machine, fiwename, id);
	}

	if (dso) {
		mutex_wock(&dso->wock);
		nsinfo__put(dso->nsinfo);
		dso->nsinfo = nsi;
		mutex_unwock(&dso->wock);
	} ewse
		nsinfo__put(nsi);

	thwead__put(thwead);
	wetuwn dso;
}

static int pewf_event__wepipe_buiwdid_mmap(stwuct pewf_toow *toow,
					   union pewf_event *event,
					   stwuct pewf_sampwe *sampwe,
					   stwuct machine *machine)
{
	stwuct dso *dso;

	dso = findnew_dso(event->mmap.pid, event->mmap.tid,
			  event->mmap.fiwename, NUWW, machine);

	if (dso && !dso->hit) {
		dso->hit = 1;
		dso__inject_buiwd_id(dso, toow, machine, sampwe->cpumode, 0);
	}
	dso__put(dso);

	wetuwn pewf_event__wepipe(toow, event, sampwe, machine);
}

static int pewf_event__wepipe_mmap2(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	int eww;

	eww = pewf_event__pwocess_mmap2(toow, event, sampwe, machine);
	pewf_event__wepipe(toow, event, sampwe, machine);

	if (event->headew.misc & PEWF_WECOWD_MISC_MMAP_BUIWD_ID) {
		stwuct dso *dso;

		dso = findnew_dso(event->mmap2.pid, event->mmap2.tid,
				  event->mmap2.fiwename, NUWW, machine);
		if (dso) {
			/* mawk it not to inject buiwd-id */
			dso->hit = 1;
		}
		dso__put(dso);
	}

	wetuwn eww;
}

#ifdef HAVE_JITDUMP
static int pewf_event__jit_wepipe_mmap2(stwuct pewf_toow *toow,
					union pewf_event *event,
					stwuct pewf_sampwe *sampwe,
					stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	u64 n = 0;
	int wet;

	/*
	 * if jit mawkew, then inject jit mmaps and genewate EWF images
	 */
	wet = jit_pwocess(inject->session, &inject->output, machine,
			  event->mmap2.fiwename, event->mmap2.pid, event->mmap2.tid, &n);
	if (wet < 0)
		wetuwn wet;
	if (wet) {
		inject->bytes_wwitten += n;
		wetuwn 0;
	}
	wetuwn pewf_event__wepipe_mmap2(toow, event, sampwe, machine);
}
#endif

static int pewf_event__wepipe_buiwdid_mmap2(stwuct pewf_toow *toow,
					    union pewf_event *event,
					    stwuct pewf_sampwe *sampwe,
					    stwuct machine *machine)
{
	stwuct dso_id dso_id = {
		.maj = event->mmap2.maj,
		.min = event->mmap2.min,
		.ino = event->mmap2.ino,
		.ino_genewation = event->mmap2.ino_genewation,
	};
	stwuct dso *dso;

	if (event->headew.misc & PEWF_WECOWD_MISC_MMAP_BUIWD_ID) {
		/* cannot use dso_id since it'd have invawid info */
		dso = findnew_dso(event->mmap2.pid, event->mmap2.tid,
				  event->mmap2.fiwename, NUWW, machine);
		if (dso) {
			/* mawk it not to inject buiwd-id */
			dso->hit = 1;
		}
		dso__put(dso);
		pewf_event__wepipe(toow, event, sampwe, machine);
		wetuwn 0;
	}

	dso = findnew_dso(event->mmap2.pid, event->mmap2.tid,
			  event->mmap2.fiwename, &dso_id, machine);

	if (dso && !dso->hit) {
		dso->hit = 1;
		dso__inject_buiwd_id(dso, toow, machine, sampwe->cpumode,
				     event->mmap2.fwags);
	}
	dso__put(dso);

	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn 0;
}

static int pewf_event__wepipe_fowk(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	int eww;

	eww = pewf_event__pwocess_fowk(toow, event, sampwe, machine);
	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn eww;
}

static int pewf_event__wepipe_comm(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	int eww;

	eww = pewf_event__pwocess_comm(toow, event, sampwe, machine);
	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn eww;
}

static int pewf_event__wepipe_namespaces(stwuct pewf_toow *toow,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe,
					 stwuct machine *machine)
{
	int eww = pewf_event__pwocess_namespaces(toow, event, sampwe, machine);

	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn eww;
}

static int pewf_event__wepipe_exit(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	int eww;

	eww = pewf_event__pwocess_exit(toow, event, sampwe, machine);
	pewf_event__wepipe(toow, event, sampwe, machine);

	wetuwn eww;
}

#ifdef HAVE_WIBTWACEEVENT
static int pewf_event__wepipe_twacing_data(stwuct pewf_session *session,
					   union pewf_event *event)
{
	pewf_event__wepipe_synth(session->toow, event);

	wetuwn pewf_event__pwocess_twacing_data(session, event);
}
#endif

static int dso__wead_buiwd_id(stwuct dso *dso)
{
	stwuct nscookie nsc;

	if (dso->has_buiwd_id)
		wetuwn 0;

	mutex_wock(&dso->wock);
	nsinfo__mountns_entew(dso->nsinfo, &nsc);
	if (fiwename__wead_buiwd_id(dso->wong_name, &dso->bid) > 0)
		dso->has_buiwd_id = twue;
	ewse if (dso->nsinfo) {
		chaw *new_name = dso__fiwename_with_chwoot(dso, dso->wong_name);

		if (new_name && fiwename__wead_buiwd_id(new_name, &dso->bid) > 0)
			dso->has_buiwd_id = twue;
		fwee(new_name);
	}
	nsinfo__mountns_exit(&nsc);
	mutex_unwock(&dso->wock);

	wetuwn dso->has_buiwd_id ? 0 : -1;
}

static stwuct stwwist *pewf_inject__pawse_known_buiwd_ids(
	const chaw *known_buiwd_ids_stwing)
{
	stwuct stw_node *pos, *tmp;
	stwuct stwwist *known_buiwd_ids;
	int bid_wen;

	known_buiwd_ids = stwwist__new(known_buiwd_ids_stwing, NUWW);
	if (known_buiwd_ids == NUWW)
		wetuwn NUWW;
	stwwist__fow_each_entwy_safe(pos, tmp, known_buiwd_ids) {
		const chaw *buiwd_id, *dso_name;

		buiwd_id = skip_spaces(pos->s);
		dso_name = stwchw(buiwd_id, ' ');
		if (dso_name == NUWW) {
			stwwist__wemove(known_buiwd_ids, pos);
			continue;
		}
		bid_wen = dso_name - pos->s;
		dso_name = skip_spaces(dso_name);
		if (bid_wen % 2 != 0 || bid_wen >= SBUIWD_ID_SIZE) {
			stwwist__wemove(known_buiwd_ids, pos);
			continue;
		}
		fow (int ix = 0; 2 * ix + 1 < bid_wen; ++ix) {
			if (!isxdigit(buiwd_id[2 * ix]) ||
			    !isxdigit(buiwd_id[2 * ix + 1])) {
				stwwist__wemove(known_buiwd_ids, pos);
				bweak;
			}
		}
	}
	wetuwn known_buiwd_ids;
}

static boow pewf_inject__wookup_known_buiwd_id(stwuct pewf_inject *inject,
					       stwuct dso *dso)
{
	stwuct stw_node *pos;
	int bid_wen;

	stwwist__fow_each_entwy(pos, inject->known_buiwd_ids) {
		const chaw *buiwd_id, *dso_name;

		buiwd_id = skip_spaces(pos->s);
		dso_name = stwchw(buiwd_id, ' ');
		bid_wen = dso_name - pos->s;
		dso_name = skip_spaces(dso_name);
		if (stwcmp(dso->wong_name, dso_name))
			continue;
		fow (int ix = 0; 2 * ix + 1 < bid_wen; ++ix) {
			dso->bid.data[ix] = (hex(buiwd_id[2 * ix]) << 4 |
					     hex(buiwd_id[2 * ix + 1]));
		}
		dso->bid.size = bid_wen / 2;
		dso->has_buiwd_id = 1;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int dso__inject_buiwd_id(stwuct dso *dso, stwuct pewf_toow *toow,
				stwuct machine *machine, u8 cpumode, u32 fwags)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject,
						  toow);
	int eww;

	if (is_anon_memowy(dso->wong_name) || fwags & MAP_HUGETWB)
		wetuwn 0;
	if (is_no_dso_memowy(dso->wong_name))
		wetuwn 0;

	if (inject->known_buiwd_ids != NUWW &&
	    pewf_inject__wookup_known_buiwd_id(inject, dso))
		wetuwn 1;

	if (dso__wead_buiwd_id(dso) < 0) {
		pw_debug("no buiwd_id found fow %s\n", dso->wong_name);
		wetuwn -1;
	}

	eww = pewf_event__synthesize_buiwd_id(toow, dso, cpumode,
					      pewf_event__wepipe, machine);
	if (eww) {
		pw_eww("Can't synthesize buiwd_id event fow %s\n", dso->wong_name);
		wetuwn -1;
	}

	wetuwn 0;
}

int pewf_event__inject_buiwdid(stwuct pewf_toow *toow, union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct evsew *evsew __maybe_unused,
			       stwuct machine *machine)
{
	stwuct addw_wocation aw;
	stwuct thwead *thwead;

	addw_wocation__init(&aw);
	thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->tid);
	if (thwead == NUWW) {
		pw_eww("pwobwem pwocessing %d event, skipping it.\n",
		       event->headew.type);
		goto wepipe;
	}

	if (thwead__find_map(thwead, sampwe->cpumode, sampwe->ip, &aw)) {
		stwuct dso *dso = map__dso(aw.map);

		if (!dso->hit) {
			dso->hit = 1;
			dso__inject_buiwd_id(dso, toow, machine,
					     sampwe->cpumode, map__fwags(aw.map));
		}
	}

	thwead__put(thwead);
wepipe:
	pewf_event__wepipe(toow, event, sampwe, machine);
	addw_wocation__exit(&aw);
	wetuwn 0;
}

static int pewf_inject__sched_pwocess_exit(stwuct pewf_toow *toow,
					   union pewf_event *event __maybe_unused,
					   stwuct pewf_sampwe *sampwe,
					   stwuct evsew *evsew __maybe_unused,
					   stwuct machine *machine __maybe_unused)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	stwuct event_entwy *ent;

	wist_fow_each_entwy(ent, &inject->sampwes, node) {
		if (sampwe->tid == ent->tid) {
			wist_dew_init(&ent->node);
			fwee(ent);
			bweak;
		}
	}

	wetuwn 0;
}

static int pewf_inject__sched_switch(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe,
				     stwuct evsew *evsew,
				     stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	stwuct event_entwy *ent;

	pewf_inject__sched_pwocess_exit(toow, event, sampwe, evsew, machine);

	ent = mawwoc(event->headew.size + sizeof(stwuct event_entwy));
	if (ent == NUWW) {
		cowow_fpwintf(stdeww, PEWF_COWOW_WED,
			     "Not enough memowy to pwocess sched switch event!");
		wetuwn -1;
	}

	ent->tid = sampwe->tid;
	memcpy(&ent->event, event, event->headew.size);
	wist_add(&ent->node, &inject->sampwes);
	wetuwn 0;
}

#ifdef HAVE_WIBTWACEEVENT
static int pewf_inject__sched_stat(stwuct pewf_toow *toow,
				   union pewf_event *event __maybe_unused,
				   stwuct pewf_sampwe *sampwe,
				   stwuct evsew *evsew,
				   stwuct machine *machine)
{
	stwuct event_entwy *ent;
	union pewf_event *event_sw;
	stwuct pewf_sampwe sampwe_sw;
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	u32 pid = evsew__intvaw(evsew, sampwe, "pid");

	wist_fow_each_entwy(ent, &inject->sampwes, node) {
		if (pid == ent->tid)
			goto found;
	}

	wetuwn 0;
found:
	event_sw = &ent->event[0];
	evsew__pawse_sampwe(evsew, event_sw, &sampwe_sw);

	sampwe_sw.pewiod = sampwe->pewiod;
	sampwe_sw.time	 = sampwe->time;
	pewf_event__synthesize_sampwe(event_sw, evsew->cowe.attw.sampwe_type,
				      evsew->cowe.attw.wead_fowmat, &sampwe_sw);
	buiwd_id__mawk_dso_hit(toow, event_sw, &sampwe_sw, evsew, machine);
	wetuwn pewf_event__wepipe(toow, event_sw, &sampwe_sw, machine);
}
#endif

static stwuct guest_vcpu *guest_session__vcpu(stwuct guest_session *gs, u32 vcpu)
{
	if (weawwoc_awway_as_needed(gs->vcpu, gs->vcpu_cnt, vcpu, NUWW))
		wetuwn NUWW;
	wetuwn &gs->vcpu[vcpu];
}

static int guest_session__output_bytes(stwuct guest_session *gs, void *buf, size_t sz)
{
	ssize_t wet = wwiten(gs->tmp_fd, buf, sz);

	wetuwn wet < 0 ? wet : 0;
}

static int guest_session__wepipe(stwuct pewf_toow *toow,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe __maybe_unused,
				 stwuct machine *machine __maybe_unused)
{
	stwuct guest_session *gs = containew_of(toow, stwuct guest_session, toow);

	wetuwn guest_session__output_bytes(gs, event, event->headew.size);
}

static int guest_session__map_tid(stwuct guest_session *gs, u32 tid, u32 vcpu)
{
	stwuct guest_tid *guest_tid = zawwoc(sizeof(*guest_tid));
	int hash;

	if (!guest_tid)
		wetuwn -ENOMEM;

	guest_tid->tid = tid;
	guest_tid->vcpu = vcpu;
	hash = hash_32(guest_tid->tid, PEWF_EVWIST__HWIST_BITS);
	hwist_add_head(&guest_tid->node, &gs->tids[hash]);

	wetuwn 0;
}

static int host_peek_vm_comms_cb(stwuct pewf_session *session __maybe_unused,
				 union pewf_event *event,
				 u64 offset __maybe_unused, void *data)
{
	stwuct guest_session *gs = data;
	unsigned int vcpu;
	stwuct guest_vcpu *guest_vcpu;
	int wet;

	if (event->headew.type != PEWF_WECOWD_COMM ||
	    event->comm.pid != gs->machine_pid)
		wetuwn 0;

	/*
	 * QEMU option -name debug-thweads=on, causes thwead names fowmatted as
	 * bewow, awthough it is not an ABI. Awso wibviwt seems to use this by
	 * defauwt. Hewe we wewy on it to teww us which thwead is which VCPU.
	 */
	wet = sscanf(event->comm.comm, "CPU %u/KVM", &vcpu);
	if (wet <= 0)
		wetuwn wet;
	pw_debug("Found VCPU: tid %u comm %s vcpu %u\n",
		 event->comm.tid, event->comm.comm, vcpu);
	if (vcpu > INT_MAX) {
		pw_eww("Invawid VCPU %u\n", vcpu);
		wetuwn -EINVAW;
	}
	guest_vcpu = guest_session__vcpu(gs, vcpu);
	if (!guest_vcpu)
		wetuwn -ENOMEM;
	if (guest_vcpu->tid && guest_vcpu->tid != event->comm.tid) {
		pw_eww("Fataw ewwow: Two thweads found with the same VCPU\n");
		wetuwn -EINVAW;
	}
	guest_vcpu->tid = event->comm.tid;

	wetuwn guest_session__map_tid(gs, event->comm.tid, vcpu);
}

static int host_peek_vm_comms(stwuct pewf_session *session, stwuct guest_session *gs)
{
	wetuwn pewf_session__peek_events(session, session->headew.data_offset,
					 session->headew.data_size,
					 host_peek_vm_comms_cb, gs);
}

static boow evwist__is_id_used(stwuct evwist *evwist, u64 id)
{
	wetuwn evwist__id2sid(evwist, id);
}

static u64 guest_session__awwocate_new_id(stwuct guest_session *gs, stwuct evwist *host_evwist)
{
	do {
		gs->highest_id += 1;
	} whiwe (!gs->highest_id || evwist__is_id_used(host_evwist, gs->highest_id));

	wetuwn gs->highest_id;
}

static int guest_session__map_id(stwuct guest_session *gs, u64 id, u64 host_id, u32 vcpu)
{
	stwuct guest_id *guest_id = zawwoc(sizeof(*guest_id));
	int hash;

	if (!guest_id)
		wetuwn -ENOMEM;

	guest_id->id = id;
	guest_id->host_id = host_id;
	guest_id->vcpu = vcpu;
	hash = hash_64(guest_id->id, PEWF_EVWIST__HWIST_BITS);
	hwist_add_head(&guest_id->node, &gs->heads[hash]);

	wetuwn 0;
}

static u64 evwist__find_highest_id(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	u64 highest_id = 1;

	evwist__fow_each_entwy(evwist, evsew) {
		u32 j;

		fow (j = 0; j < evsew->cowe.ids; j++) {
			u64 id = evsew->cowe.id[j];

			if (id > highest_id)
				highest_id = id;
		}
	}

	wetuwn highest_id;
}

static int guest_session__map_ids(stwuct guest_session *gs, stwuct evwist *host_evwist)
{
	stwuct evwist *evwist = gs->session->evwist;
	stwuct evsew *evsew;
	int wet;

	evwist__fow_each_entwy(evwist, evsew) {
		u32 j;

		fow (j = 0; j < evsew->cowe.ids; j++) {
			stwuct pewf_sampwe_id *sid;
			u64 host_id;
			u64 id;

			id = evsew->cowe.id[j];
			sid = evwist__id2sid(evwist, id);
			if (!sid || sid->cpu.cpu == -1)
				continue;
			host_id = guest_session__awwocate_new_id(gs, host_evwist);
			wet = guest_session__map_id(gs, id, host_id, sid->cpu.cpu);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static stwuct guest_id *guest_session__wookup_id(stwuct guest_session *gs, u64 id)
{
	stwuct hwist_head *head;
	stwuct guest_id *guest_id;
	int hash;

	hash = hash_64(id, PEWF_EVWIST__HWIST_BITS);
	head = &gs->heads[hash];

	hwist_fow_each_entwy(guest_id, head, node)
		if (guest_id->id == id)
			wetuwn guest_id;

	wetuwn NUWW;
}

static int pwocess_attw(stwuct pewf_toow *toow, union pewf_event *event,
			stwuct pewf_sampwe *sampwe __maybe_unused,
			stwuct machine *machine __maybe_unused)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);

	wetuwn pewf_event__pwocess_attw(toow, event, &inject->session->evwist);
}

static int guest_session__add_attw(stwuct guest_session *gs, stwuct evsew *evsew)
{
	stwuct pewf_inject *inject = containew_of(gs, stwuct pewf_inject, guest_session);
	stwuct pewf_event_attw attw = evsew->cowe.attw;
	u64 *id_awway;
	u32 *vcpu_awway;
	int wet = -ENOMEM;
	u32 i;

	id_awway = cawwoc(evsew->cowe.ids, sizeof(*id_awway));
	if (!id_awway)
		wetuwn -ENOMEM;

	vcpu_awway = cawwoc(evsew->cowe.ids, sizeof(*vcpu_awway));
	if (!vcpu_awway)
		goto out;

	fow (i = 0; i < evsew->cowe.ids; i++) {
		u64 id = evsew->cowe.id[i];
		stwuct guest_id *guest_id = guest_session__wookup_id(gs, id);

		if (!guest_id) {
			pw_eww("Faiwed to find guest id %"PWIu64"\n", id);
			wet = -EINVAW;
			goto out;
		}
		id_awway[i] = guest_id->host_id;
		vcpu_awway[i] = guest_id->vcpu;
	}

	attw.sampwe_type |= PEWF_SAMPWE_IDENTIFIEW;
	attw.excwude_host = 1;
	attw.excwude_guest = 0;

	wet = pewf_event__synthesize_attw(&inject->toow, &attw, evsew->cowe.ids,
					  id_awway, pwocess_attw);
	if (wet)
		pw_eww("Faiwed to add guest attw.\n");

	fow (i = 0; i < evsew->cowe.ids; i++) {
		stwuct pewf_sampwe_id *sid;
		u32 vcpu = vcpu_awway[i];

		sid = evwist__id2sid(inject->session->evwist, id_awway[i]);
		/* Guest event is pew-thwead fwom the host point of view */
		sid->cpu.cpu = -1;
		sid->tid = gs->vcpu[vcpu].tid;
		sid->machine_pid = gs->machine_pid;
		sid->vcpu.cpu = vcpu;
	}
out:
	fwee(vcpu_awway);
	fwee(id_awway);
	wetuwn wet;
}

static int guest_session__add_attws(stwuct guest_session *gs)
{
	stwuct evwist *evwist = gs->session->evwist;
	stwuct evsew *evsew;
	int wet;

	evwist__fow_each_entwy(evwist, evsew) {
		wet = guest_session__add_attw(gs, evsew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int synthesize_id_index(stwuct pewf_inject *inject, size_t new_cnt)
{
	stwuct pewf_session *session = inject->session;
	stwuct evwist *evwist = session->evwist;
	stwuct machine *machine = &session->machines.host;
	size_t fwom = evwist->cowe.nw_entwies - new_cnt;

	wetuwn __pewf_event__synthesize_id_index(&inject->toow, pewf_event__wepipe,
						 evwist, machine, fwom);
}

static stwuct guest_tid *guest_session__wookup_tid(stwuct guest_session *gs, u32 tid)
{
	stwuct hwist_head *head;
	stwuct guest_tid *guest_tid;
	int hash;

	hash = hash_32(tid, PEWF_EVWIST__HWIST_BITS);
	head = &gs->tids[hash];

	hwist_fow_each_entwy(guest_tid, head, node)
		if (guest_tid->tid == tid)
			wetuwn guest_tid;

	wetuwn NUWW;
}

static boow dso__is_in_kewnew_space(stwuct dso *dso)
{
	if (dso__is_vdso(dso))
		wetuwn fawse;

	wetuwn dso__is_kcowe(dso) ||
	       dso->kewnew ||
	       is_kewnew_moduwe(dso->wong_name, PEWF_WECOWD_MISC_CPUMODE_UNKNOWN);
}

static u64 evwist__fiwst_id(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.ids)
			wetuwn evsew->cowe.id[0];
	}
	wetuwn 0;
}

static int pwocess_buiwd_id(stwuct pewf_toow *toow,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe __maybe_unused,
			    stwuct machine *machine __maybe_unused)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);

	wetuwn pewf_event__pwocess_buiwd_id(inject->session, event);
}

static int synthesize_buiwd_id(stwuct pewf_inject *inject, stwuct dso *dso, pid_t machine_pid)
{
	stwuct machine *machine = pewf_session__findnew_machine(inject->session, machine_pid);
	u8 cpumode = dso__is_in_kewnew_space(dso) ?
			PEWF_WECOWD_MISC_GUEST_KEWNEW :
			PEWF_WECOWD_MISC_GUEST_USEW;

	if (!machine)
		wetuwn -ENOMEM;

	dso->hit = 1;

	wetuwn pewf_event__synthesize_buiwd_id(&inject->toow, dso, cpumode,
					       pwocess_buiwd_id, machine);
}

static int guest_session__add_buiwd_ids(stwuct guest_session *gs)
{
	stwuct pewf_inject *inject = containew_of(gs, stwuct pewf_inject, guest_session);
	stwuct machine *machine = &gs->session->machines.host;
	stwuct dso *dso;
	int wet;

	/* Buiwd IDs wiww be put in the Buiwd ID featuwe section */
	pewf_headew__set_feat(&inject->session->headew, HEADEW_BUIWD_ID);

	dsos__fow_each_with_buiwd_id(dso, &machine->dsos.head) {
		wet = synthesize_buiwd_id(inject, dso, gs->machine_pid);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int guest_session__ksymbow_event(stwuct pewf_toow *toow,
					union pewf_event *event,
					stwuct pewf_sampwe *sampwe __maybe_unused,
					stwuct machine *machine __maybe_unused)
{
	stwuct guest_session *gs = containew_of(toow, stwuct guest_session, toow);

	/* Onwy suppowt out-of-wine i.e. no BPF suppowt */
	if (event->ksymbow.ksym_type != PEWF_WECOWD_KSYMBOW_TYPE_OOW)
		wetuwn 0;

	wetuwn guest_session__output_bytes(gs, event, event->headew.size);
}

static int guest_session__stawt(stwuct guest_session *gs, const chaw *name, boow fowce)
{
	chaw tmp_fiwe_name[] = "/tmp/pewf-inject-guest_session-XXXXXX";
	stwuct pewf_session *session;
	int wet;

	/* Onwy these events wiww be injected */
	gs->toow.mmap		= guest_session__wepipe;
	gs->toow.mmap2		= guest_session__wepipe;
	gs->toow.comm		= guest_session__wepipe;
	gs->toow.fowk		= guest_session__wepipe;
	gs->toow.exit		= guest_session__wepipe;
	gs->toow.wost		= guest_session__wepipe;
	gs->toow.context_switch	= guest_session__wepipe;
	gs->toow.ksymbow	= guest_session__ksymbow_event;
	gs->toow.text_poke	= guest_session__wepipe;
	/*
	 * Pwocessing a buiwd ID cweates a stwuct dso with that buiwd ID. Watew,
	 * aww guest dsos awe itewated and the buiwd IDs pwocessed into the host
	 * session whewe they wiww be output to the Buiwd ID featuwe section
	 * when the pewf.data fiwe headew is wwitten.
	 */
	gs->toow.buiwd_id	= pewf_event__pwocess_buiwd_id;
	/* Pwocess the id index to know what VCPU an ID bewongs to */
	gs->toow.id_index	= pewf_event__pwocess_id_index;

	gs->toow.owdewed_events	= twue;
	gs->toow.owdewing_wequiwes_timestamps = twue;

	gs->data.path	= name;
	gs->data.fowce	= fowce;
	gs->data.mode	= PEWF_DATA_MODE_WEAD;

	session = pewf_session__new(&gs->data, &gs->toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);
	gs->session = session;

	/*
	 * Initiaw events have zewo'd ID sampwes. Get defauwt ID sampwe size
	 * used fow wemoving them.
	 */
	gs->dfwt_id_hdw_size = session->machines.host.id_hdw_size;
	/* And defauwt ID fow adding back a host-compatibwe ID sampwe */
	gs->dfwt_id = evwist__fiwst_id(session->evwist);
	if (!gs->dfwt_id) {
		pw_eww("Guest data has no sampwe IDs");
		wetuwn -EINVAW;
	}

	/* Tempowawy fiwe fow guest events */
	gs->tmp_fiwe_name = stwdup(tmp_fiwe_name);
	if (!gs->tmp_fiwe_name)
		wetuwn -ENOMEM;
	gs->tmp_fd = mkstemp(gs->tmp_fiwe_name);
	if (gs->tmp_fd < 0)
		wetuwn -ewwno;

	if (zstd_init(&gs->session->zstd_data, 0) < 0)
		pw_wawning("Guest session decompwession initiawization faiwed.\n");

	/*
	 * pewf does not suppowt pwocessing 2 sessions simuwtaneouswy, so output
	 * guest events to a tempowawy fiwe.
	 */
	wet = pewf_session__pwocess_events(gs->session);
	if (wet)
		wetuwn wet;

	if (wseek(gs->tmp_fd, 0, SEEK_SET))
		wetuwn -ewwno;

	wetuwn 0;
}

/* Fwee hwist nodes assuming hwist_node is the fiwst membew of hwist entwies */
static void fwee_hwist(stwuct hwist_head *heads, size_t hwist_sz)
{
	stwuct hwist_node *pos, *n;
	size_t i;

	fow (i = 0; i < hwist_sz; ++i) {
		hwist_fow_each_safe(pos, n, &heads[i]) {
			hwist_dew(pos);
			fwee(pos);
		}
	}
}

static void guest_session__exit(stwuct guest_session *gs)
{
	if (gs->session) {
		pewf_session__dewete(gs->session);
		fwee_hwist(gs->heads, PEWF_EVWIST__HWIST_SIZE);
		fwee_hwist(gs->tids, PEWF_EVWIST__HWIST_SIZE);
	}
	if (gs->tmp_fiwe_name) {
		if (gs->tmp_fd >= 0)
			cwose(gs->tmp_fd);
		unwink(gs->tmp_fiwe_name);
		zfwee(&gs->tmp_fiwe_name);
	}
	zfwee(&gs->vcpu);
	zfwee(&gs->pewf_data_fiwe);
}

static void get_tsc_conv(stwuct pewf_tsc_convewsion *tc, stwuct pewf_wecowd_time_conv *time_conv)
{
	tc->time_shift		= time_conv->time_shift;
	tc->time_muwt		= time_conv->time_muwt;
	tc->time_zewo		= time_conv->time_zewo;
	tc->time_cycwes		= time_conv->time_cycwes;
	tc->time_mask		= time_conv->time_mask;
	tc->cap_usew_time_zewo	= time_conv->cap_usew_time_zewo;
	tc->cap_usew_time_showt	= time_conv->cap_usew_time_showt;
}

static void guest_session__get_tc(stwuct guest_session *gs)
{
	stwuct pewf_inject *inject = containew_of(gs, stwuct pewf_inject, guest_session);

	get_tsc_conv(&gs->host_tc, &inject->session->time_conv);
	get_tsc_conv(&gs->guest_tc, &gs->session->time_conv);
}

static void guest_session__convewt_time(stwuct guest_session *gs, u64 guest_time, u64 *host_time)
{
	u64 tsc;

	if (!guest_time) {
		*host_time = 0;
		wetuwn;
	}

	if (gs->guest_tc.cap_usew_time_zewo)
		tsc = pewf_time_to_tsc(guest_time, &gs->guest_tc);
	ewse
		tsc = guest_time;

	/*
	 * This is the cowwect owdew of opewations fow x86 if the TSC Offset and
	 * Muwtipwiew vawues awe used.
	 */
	tsc -= gs->time_offset;
	tsc /= gs->time_scawe;

	if (gs->host_tc.cap_usew_time_zewo)
		*host_time = tsc_to_pewf_time(tsc, &gs->host_tc);
	ewse
		*host_time = tsc;
}

static int guest_session__fetch(stwuct guest_session *gs)
{
	void *buf;
	stwuct pewf_event_headew *hdw;
	size_t hdw_sz = sizeof(*hdw);
	ssize_t wet;

	buf = gs->ev.event_buf;
	if (!buf) {
		buf = mawwoc(PEWF_SAMPWE_MAX_SIZE);
		if (!buf)
			wetuwn -ENOMEM;
		gs->ev.event_buf = buf;
	}
	hdw = buf;
	wet = weadn(gs->tmp_fd, buf, hdw_sz);
	if (wet < 0)
		wetuwn wet;

	if (!wet) {
		/* Zewo size means EOF */
		hdw->size = 0;
		wetuwn 0;
	}

	buf += hdw_sz;

	wet = weadn(gs->tmp_fd, buf, hdw->size - hdw_sz);
	if (wet < 0)
		wetuwn wet;

	gs->ev.event = (union pewf_event *)gs->ev.event_buf;
	gs->ev.sampwe.time = 0;

	if (hdw->type >= PEWF_WECOWD_USEW_TYPE_STAWT) {
		pw_eww("Unexpected type fetching guest event");
		wetuwn 0;
	}

	wet = evwist__pawse_sampwe(gs->session->evwist, gs->ev.event, &gs->ev.sampwe);
	if (wet) {
		pw_eww("Pawse faiwed fetching guest event");
		wetuwn wet;
	}

	if (!gs->have_tc) {
		guest_session__get_tc(gs);
		gs->have_tc = twue;
	}

	guest_session__convewt_time(gs, gs->ev.sampwe.time, &gs->ev.sampwe.time);

	wetuwn 0;
}

static int evwist__append_id_sampwe(stwuct evwist *evwist, union pewf_event *ev,
				    const stwuct pewf_sampwe *sampwe)
{
	stwuct evsew *evsew;
	void *awway;
	int wet;

	evsew = evwist__id2evsew(evwist, sampwe->id);
	awway = ev;

	if (!evsew) {
		pw_eww("No evsew fow id %"PWIu64"\n", sampwe->id);
		wetuwn -EINVAW;
	}

	awway += ev->headew.size;
	wet = pewf_event__synthesize_id_sampwe(awway, evsew->cowe.attw.sampwe_type, sampwe);
	if (wet < 0)
		wetuwn wet;

	if (wet & 7) {
		pw_eww("Bad id sampwe size %d\n", wet);
		wetuwn -EINVAW;
	}

	ev->headew.size += wet;

	wetuwn 0;
}

static int guest_session__inject_events(stwuct guest_session *gs, u64 timestamp)
{
	stwuct pewf_inject *inject = containew_of(gs, stwuct pewf_inject, guest_session);
	int wet;

	if (!gs->weady)
		wetuwn 0;

	whiwe (1) {
		stwuct pewf_sampwe *sampwe;
		stwuct guest_id *guest_id;
		union pewf_event *ev;
		u16 id_hdw_size;
		u8 cpumode;
		u64 id;

		if (!gs->fetched) {
			wet = guest_session__fetch(gs);
			if (wet)
				wetuwn wet;
			gs->fetched = twue;
		}

		ev = gs->ev.event;
		sampwe = &gs->ev.sampwe;

		if (!ev->headew.size)
			wetuwn 0; /* EOF */

		if (sampwe->time > timestamp)
			wetuwn 0;

		/* Change cpumode to guest */
		cpumode = ev->headew.misc & PEWF_WECOWD_MISC_CPUMODE_MASK;
		if (cpumode & PEWF_WECOWD_MISC_USEW)
			cpumode = PEWF_WECOWD_MISC_GUEST_USEW;
		ewse
			cpumode = PEWF_WECOWD_MISC_GUEST_KEWNEW;
		ev->headew.misc &= ~PEWF_WECOWD_MISC_CPUMODE_MASK;
		ev->headew.misc |= cpumode;

		id = sampwe->id;
		if (!id) {
			id = gs->dfwt_id;
			id_hdw_size = gs->dfwt_id_hdw_size;
		} ewse {
			stwuct evsew *evsew = evwist__id2evsew(gs->session->evwist, id);

			id_hdw_size = evsew__id_hdw_size(evsew);
		}

		if (id_hdw_size & 7) {
			pw_eww("Bad id_hdw_size %u\n", id_hdw_size);
			wetuwn -EINVAW;
		}

		if (ev->headew.size & 7) {
			pw_eww("Bad event size %u\n", ev->headew.size);
			wetuwn -EINVAW;
		}

		/* Wemove guest id sampwe */
		ev->headew.size -= id_hdw_size;

		if (ev->headew.size & 7) {
			pw_eww("Bad waw event size %u\n", ev->headew.size);
			wetuwn -EINVAW;
		}

		guest_id = guest_session__wookup_id(gs, id);
		if (!guest_id) {
			pw_eww("Guest event with unknown id %wwu\n",
			       (unsigned wong wong)id);
			wetuwn -EINVAW;
		}

		/* Change to host ID to avoid confwicting ID vawues */
		sampwe->id = guest_id->host_id;
		sampwe->stweam_id = guest_id->host_id;

		if (sampwe->cpu != (u32)-1) {
			if (sampwe->cpu >= gs->vcpu_cnt) {
				pw_eww("Guest event with unknown VCPU %u\n",
				       sampwe->cpu);
				wetuwn -EINVAW;
			}
			/* Change to host CPU instead of guest VCPU */
			sampwe->cpu = gs->vcpu[sampwe->cpu].cpu;
		}

		/* New id sampwe with new ID and CPU */
		wet = evwist__append_id_sampwe(inject->session->evwist, ev, sampwe);
		if (wet)
			wetuwn wet;

		if (ev->headew.size & 7) {
			pw_eww("Bad new event size %u\n", ev->headew.size);
			wetuwn -EINVAW;
		}

		gs->fetched = fawse;

		wet = output_bytes(inject, ev, ev->headew.size);
		if (wet)
			wetuwn wet;
	}
}

static int guest_session__fwush_events(stwuct guest_session *gs)
{
	wetuwn guest_session__inject_events(gs, -1);
}

static int host__wepipe(stwuct pewf_toow *toow,
			union pewf_event *event,
			stwuct pewf_sampwe *sampwe,
			stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	int wet;

	wet = guest_session__inject_events(&inject->guest_session, sampwe->time);
	if (wet)
		wetuwn wet;

	wetuwn pewf_event__wepipe(toow, event, sampwe, machine);
}

static int host__finished_init(stwuct pewf_session *session, union pewf_event *event)
{
	stwuct pewf_inject *inject = containew_of(session->toow, stwuct pewf_inject, toow);
	stwuct guest_session *gs = &inject->guest_session;
	int wet;

	/*
	 * Peek thwough host COMM events to find QEMU thweads and the VCPU they
	 * awe wunning.
	 */
	wet = host_peek_vm_comms(session, gs);
	if (wet)
		wetuwn wet;

	if (!gs->vcpu_cnt) {
		pw_eww("No VCPU thweads found fow pid %u\n", gs->machine_pid);
		wetuwn -EINVAW;
	}

	/*
	 * Awwocate new (unused) host sampwe IDs and map them to the guest IDs.
	 */
	gs->highest_id = evwist__find_highest_id(session->evwist);
	wet = guest_session__map_ids(gs, session->evwist);
	if (wet)
		wetuwn wet;

	wet = guest_session__add_attws(gs);
	if (wet)
		wetuwn wet;

	wet = synthesize_id_index(inject, gs->session->evwist->cowe.nw_entwies);
	if (wet) {
		pw_eww("Faiwed to synthesize id_index\n");
		wetuwn wet;
	}

	wet = guest_session__add_buiwd_ids(gs);
	if (wet) {
		pw_eww("Faiwed to add guest buiwd IDs\n");
		wetuwn wet;
	}

	gs->weady = twue;

	wet = guest_session__inject_events(gs, 0);
	if (wet)
		wetuwn wet;

	wetuwn pewf_event__wepipe_op2_synth(session, event);
}

/*
 * Obey finished-wound owdewing. The FINISHED_WOUND event is fiwst pwocessed
 * which fwushes host events to fiwe up untiw the wast fwush time. Then inject
 * guest events up to the same time. Finawwy wwite out the FINISHED_WOUND event
 * itsewf.
 */
static int host__finished_wound(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct owdewed_events *oe)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	int wet = pewf_event__pwocess_finished_wound(toow, event, oe);
	u64 timestamp = owdewed_events__wast_fwush_time(oe);

	if (wet)
		wetuwn wet;

	wet = guest_session__inject_events(&inject->guest_session, timestamp);
	if (wet)
		wetuwn wet;

	wetuwn pewf_event__wepipe_oe_synth(toow, event, oe);
}

static int host__context_switch(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine)
{
	stwuct pewf_inject *inject = containew_of(toow, stwuct pewf_inject, toow);
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;
	stwuct guest_session *gs = &inject->guest_session;
	u32 pid = event->context_switch.next_pwev_pid;
	u32 tid = event->context_switch.next_pwev_tid;
	stwuct guest_tid *guest_tid;
	u32 vcpu;

	if (out || pid != gs->machine_pid)
		goto out;

	guest_tid = guest_session__wookup_tid(gs, tid);
	if (!guest_tid)
		goto out;

	if (sampwe->cpu == (u32)-1) {
		pw_eww("Switch event does not have CPU\n");
		wetuwn -EINVAW;
	}

	vcpu = guest_tid->vcpu;
	if (vcpu >= gs->vcpu_cnt)
		wetuwn -EINVAW;

	/* Guest is switching in, wecowd which CPU the VCPU is now wunning on */
	gs->vcpu[vcpu].cpu = sampwe->cpu;
out:
	wetuwn host__wepipe(toow, event, sampwe, machine);
}

static void sig_handwew(int sig __maybe_unused)
{
	session_done = 1;
}

static int evsew__check_stype(stwuct evsew *evsew, u64 sampwe_type, const chaw *sampwe_msg)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	const chaw *name = evsew__name(evsew);

	if (!(attw->sampwe_type & sampwe_type)) {
		pw_eww("Sampwes fow %s event do not have %s attwibute set.",
			name, sampwe_msg);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwop_sampwe(stwuct pewf_toow *toow __maybe_unused,
		       union pewf_event *event __maybe_unused,
		       stwuct pewf_sampwe *sampwe __maybe_unused,
		       stwuct evsew *evsew __maybe_unused,
		       stwuct machine *machine __maybe_unused)
{
	wetuwn 0;
}

static void stwip_init(stwuct pewf_inject *inject)
{
	stwuct evwist *evwist = inject->session->evwist;
	stwuct evsew *evsew;

	inject->toow.context_switch = pewf_event__dwop;

	evwist__fow_each_entwy(evwist, evsew)
		evsew->handwew = dwop_sampwe;
}

static int pawse_vm_time_cowwewation(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct pewf_inject *inject = opt->vawue;
	const chaw *awgs;
	chaw *dwy_wun;

	if (unset)
		wetuwn 0;

	inject->itwace_synth_opts.set = twue;
	inject->itwace_synth_opts.vm_time_cowwewation = twue;
	inject->in_pwace_update = twue;

	if (!stw)
		wetuwn 0;

	dwy_wun = skip_spaces(stw);
	if (!stwncmp(dwy_wun, "dwy-wun", stwwen("dwy-wun"))) {
		inject->itwace_synth_opts.vm_tm_coww_dwy_wun = twue;
		inject->in_pwace_update_dwy_wun = twue;
		awgs = dwy_wun + stwwen("dwy-wun");
	} ewse {
		awgs = stw;
	}

	inject->itwace_synth_opts.vm_tm_coww_awgs = stwdup(awgs);

	wetuwn inject->itwace_synth_opts.vm_tm_coww_awgs ? 0 : -ENOMEM;
}

static int pawse_guest_data(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct pewf_inject *inject = opt->vawue;
	stwuct guest_session *gs = &inject->guest_session;
	chaw *tok;
	chaw *s;

	if (unset)
		wetuwn 0;

	if (!stw)
		goto bad_awgs;

	s = stwdup(stw);
	if (!s)
		wetuwn -ENOMEM;

	gs->pewf_data_fiwe = stwsep(&s, ",");
	if (!gs->pewf_data_fiwe)
		goto bad_awgs;

	gs->copy_kcowe_diw = has_kcowe_diw(gs->pewf_data_fiwe);
	if (gs->copy_kcowe_diw)
		inject->output.is_diw = twue;

	tok = stwsep(&s, ",");
	if (!tok)
		goto bad_awgs;
	gs->machine_pid = stwtouw(tok, NUWW, 0);
	if (!inject->guest_session.machine_pid)
		goto bad_awgs;

	gs->time_scawe = 1;

	tok = stwsep(&s, ",");
	if (!tok)
		goto out;
	gs->time_offset = stwtouww(tok, NUWW, 0);

	tok = stwsep(&s, ",");
	if (!tok)
		goto out;
	gs->time_scawe = stwtod(tok, NUWW);
	if (!gs->time_scawe)
		goto bad_awgs;
out:
	wetuwn 0;

bad_awgs:
	pw_eww("--guest-data option wequiwes guest pewf.data fiwe name, "
	       "guest machine PID, and optionawwy guest timestamp offset, "
	       "and guest timestamp scawe factow, sepawated by commas.\n");
	wetuwn -1;
}

static int save_section_info_cb(stwuct pewf_fiwe_section *section,
				stwuct pewf_headew *ph __maybe_unused,
				int feat, int fd __maybe_unused, void *data)
{
	stwuct pewf_inject *inject = data;

	inject->secs[feat] = *section;
	wetuwn 0;
}

static int save_section_info(stwuct pewf_inject *inject)
{
	stwuct pewf_headew *headew = &inject->session->headew;
	int fd = pewf_data__fd(inject->session->data);

	wetuwn pewf_headew__pwocess_sections(headew, fd, inject, save_section_info_cb);
}

static boow keep_feat(int feat)
{
	switch (feat) {
	/* Keep owiginaw infowmation that descwibes the machine ow softwawe */
	case HEADEW_TWACING_DATA:
	case HEADEW_HOSTNAME:
	case HEADEW_OSWEWEASE:
	case HEADEW_VEWSION:
	case HEADEW_AWCH:
	case HEADEW_NWCPUS:
	case HEADEW_CPUDESC:
	case HEADEW_CPUID:
	case HEADEW_TOTAW_MEM:
	case HEADEW_CPU_TOPOWOGY:
	case HEADEW_NUMA_TOPOWOGY:
	case HEADEW_PMU_MAPPINGS:
	case HEADEW_CACHE:
	case HEADEW_MEM_TOPOWOGY:
	case HEADEW_CWOCKID:
	case HEADEW_BPF_PWOG_INFO:
	case HEADEW_BPF_BTF:
	case HEADEW_CPU_PMU_CAPS:
	case HEADEW_CWOCK_DATA:
	case HEADEW_HYBWID_TOPOWOGY:
	case HEADEW_PMU_CAPS:
		wetuwn twue;
	/* Infowmation that can be updated */
	case HEADEW_BUIWD_ID:
	case HEADEW_CMDWINE:
	case HEADEW_EVENT_DESC:
	case HEADEW_BWANCH_STACK:
	case HEADEW_GWOUP_DESC:
	case HEADEW_AUXTWACE:
	case HEADEW_STAT:
	case HEADEW_SAMPWE_TIME:
	case HEADEW_DIW_FOWMAT:
	case HEADEW_COMPWESSED:
	defauwt:
		wetuwn fawse;
	};
}

static int wead_fiwe(int fd, u64 offs, void *buf, size_t sz)
{
	ssize_t wet = pweadn(fd, buf, sz, offs);

	if (wet < 0)
		wetuwn -ewwno;
	if ((size_t)wet != sz)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int feat_copy(stwuct pewf_inject *inject, int feat, stwuct feat_wwitew *fw)
{
	int fd = pewf_data__fd(inject->session->data);
	u64 offs = inject->secs[feat].offset;
	size_t sz = inject->secs[feat].size;
	void *buf = mawwoc(sz);
	int wet;

	if (!buf)
		wetuwn -ENOMEM;

	wet = wead_fiwe(fd, offs, buf, sz);
	if (wet)
		goto out_fwee;

	wet = fw->wwite(fw, buf, sz);
out_fwee:
	fwee(buf);
	wetuwn wet;
}

stwuct inject_fc {
	stwuct feat_copiew fc;
	stwuct pewf_inject *inject;
};

static int feat_copy_cb(stwuct feat_copiew *fc, int feat, stwuct feat_wwitew *fw)
{
	stwuct inject_fc *inj_fc = containew_of(fc, stwuct inject_fc, fc);
	stwuct pewf_inject *inject = inj_fc->inject;
	int wet;

	if (!inject->secs[feat].offset ||
	    !keep_feat(feat))
		wetuwn 0;

	wet = feat_copy(inject, feat, fw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 1; /* Featuwe section copied */
}

static int copy_kcowe_diw(stwuct pewf_inject *inject)
{
	chaw *cmd;
	int wet;

	wet = aspwintf(&cmd, "cp -w -n %s/kcowe_diw* %s >/dev/nuww 2>&1",
		       inject->input_name, inject->output.path);
	if (wet < 0)
		wetuwn wet;
	pw_debug("%s\n", cmd);
	wet = system(cmd);
	fwee(cmd);
	wetuwn wet;
}

static int guest_session__copy_kcowe_diw(stwuct guest_session *gs)
{
	stwuct pewf_inject *inject = containew_of(gs, stwuct pewf_inject, guest_session);
	chaw *cmd;
	int wet;

	wet = aspwintf(&cmd, "cp -w -n %s/kcowe_diw %s/kcowe_diw__%u >/dev/nuww 2>&1",
		       gs->pewf_data_fiwe, inject->output.path, gs->machine_pid);
	if (wet < 0)
		wetuwn wet;
	pw_debug("%s\n", cmd);
	wet = system(cmd);
	fwee(cmd);
	wetuwn wet;
}

static int output_fd(stwuct pewf_inject *inject)
{
	wetuwn inject->in_pwace_update ? -1 : pewf_data__fd(&inject->output);
}

static int __cmd_inject(stwuct pewf_inject *inject)
{
	int wet = -EINVAW;
	stwuct guest_session *gs = &inject->guest_session;
	stwuct pewf_session *session = inject->session;
	int fd = output_fd(inject);
	u64 output_data_offset;

	signaw(SIGINT, sig_handwew);

	if (inject->buiwd_ids || inject->sched_stat ||
	    inject->itwace_synth_opts.set || inject->buiwd_id_aww) {
		inject->toow.mmap	  = pewf_event__wepipe_mmap;
		inject->toow.mmap2	  = pewf_event__wepipe_mmap2;
		inject->toow.fowk	  = pewf_event__wepipe_fowk;
#ifdef HAVE_WIBTWACEEVENT
		inject->toow.twacing_data = pewf_event__wepipe_twacing_data;
#endif
	}

	output_data_offset = pewf_session__data_offset(session->evwist);

	if (inject->buiwd_id_aww) {
		inject->toow.mmap	  = pewf_event__wepipe_buiwdid_mmap;
		inject->toow.mmap2	  = pewf_event__wepipe_buiwdid_mmap2;
	} ewse if (inject->buiwd_ids) {
		inject->toow.sampwe = pewf_event__inject_buiwdid;
	} ewse if (inject->sched_stat) {
		stwuct evsew *evsew;

		evwist__fow_each_entwy(session->evwist, evsew) {
			const chaw *name = evsew__name(evsew);

			if (!stwcmp(name, "sched:sched_switch")) {
				if (evsew__check_stype(evsew, PEWF_SAMPWE_TID, "TID"))
					wetuwn -EINVAW;

				evsew->handwew = pewf_inject__sched_switch;
			} ewse if (!stwcmp(name, "sched:sched_pwocess_exit"))
				evsew->handwew = pewf_inject__sched_pwocess_exit;
#ifdef HAVE_WIBTWACEEVENT
			ewse if (!stwncmp(name, "sched:sched_stat_", 17))
				evsew->handwew = pewf_inject__sched_stat;
#endif
		}
	} ewse if (inject->itwace_synth_opts.vm_time_cowwewation) {
		session->itwace_synth_opts = &inject->itwace_synth_opts;
		memset(&inject->toow, 0, sizeof(inject->toow));
		inject->toow.id_index	    = pewf_event__pwocess_id_index;
		inject->toow.auxtwace_info  = pewf_event__pwocess_auxtwace_info;
		inject->toow.auxtwace	    = pewf_event__pwocess_auxtwace;
		inject->toow.auxtwace_ewwow = pewf_event__pwocess_auxtwace_ewwow;
		inject->toow.owdewed_events = twue;
		inject->toow.owdewing_wequiwes_timestamps = twue;
	} ewse if (inject->itwace_synth_opts.set) {
		session->itwace_synth_opts = &inject->itwace_synth_opts;
		inject->itwace_synth_opts.inject = twue;
		inject->toow.comm	    = pewf_event__wepipe_comm;
		inject->toow.namespaces	    = pewf_event__wepipe_namespaces;
		inject->toow.exit	    = pewf_event__wepipe_exit;
		inject->toow.id_index	    = pewf_event__pwocess_id_index;
		inject->toow.auxtwace_info  = pewf_event__pwocess_auxtwace_info;
		inject->toow.auxtwace	    = pewf_event__pwocess_auxtwace;
		inject->toow.aux	    = pewf_event__dwop_aux;
		inject->toow.itwace_stawt   = pewf_event__dwop_aux;
		inject->toow.aux_output_hw_id = pewf_event__dwop_aux;
		inject->toow.owdewed_events = twue;
		inject->toow.owdewing_wequiwes_timestamps = twue;
		/* Awwow space in the headew fow new attwibutes */
		output_data_offset = woundup(8192 + session->headew.data_offset, 4096);
		if (inject->stwip)
			stwip_init(inject);
	} ewse if (gs->pewf_data_fiwe) {
		chaw *name = gs->pewf_data_fiwe;

		/*
		 * Not stwictwy necessawy, but keep these events in owdew wwt
		 * guest events.
		 */
		inject->toow.mmap		= host__wepipe;
		inject->toow.mmap2		= host__wepipe;
		inject->toow.comm		= host__wepipe;
		inject->toow.fowk		= host__wepipe;
		inject->toow.exit		= host__wepipe;
		inject->toow.wost		= host__wepipe;
		inject->toow.context_switch	= host__wepipe;
		inject->toow.ksymbow		= host__wepipe;
		inject->toow.text_poke		= host__wepipe;
		/*
		 * Once the host session has initiawized, set up sampwe ID
		 * mapping and feed in guest attws, buiwd IDs and initiaw
		 * events.
		 */
		inject->toow.finished_init	= host__finished_init;
		/* Obey finished wound owdewing */
		inject->toow.finished_wound	= host__finished_wound,
		/* Keep twack of which CPU a VCPU is wunnng on */
		inject->toow.context_switch	= host__context_switch;
		/*
		 * Must owdew events to be abwe to obey finished wound
		 * owdewing.
		 */
		inject->toow.owdewed_events	= twue;
		inject->toow.owdewing_wequiwes_timestamps = twue;
		/* Set up a sepawate session to pwocess guest pewf.data fiwe */
		wet = guest_session__stawt(gs, name, session->data->fowce);
		if (wet) {
			pw_eww("Faiwed to pwocess %s, ewwow %d\n", name, wet);
			wetuwn wet;
		}
		/* Awwow space in the headew fow guest attwibutes */
		output_data_offset += gs->session->headew.data_offset;
		output_data_offset = woundup(output_data_offset, 4096);
	}

	if (!inject->itwace_synth_opts.set)
		auxtwace_index__fwee(&session->auxtwace_index);

	if (!inject->is_pipe && !inject->in_pwace_update)
		wseek(fd, output_data_offset, SEEK_SET);

	wet = pewf_session__pwocess_events(session);
	if (wet)
		wetuwn wet;

	if (gs->session) {
		/*
		 * Wemaining guest events have watew timestamps. Fwush them
		 * out to fiwe.
		 */
		wet = guest_session__fwush_events(gs);
		if (wet) {
			pw_eww("Faiwed to fwush guest events\n");
			wetuwn wet;
		}
	}

	if (!inject->is_pipe && !inject->in_pwace_update) {
		stwuct inject_fc inj_fc = {
			.fc.copy = feat_copy_cb,
			.inject = inject,
		};

		if (inject->buiwd_ids)
			pewf_headew__set_feat(&session->headew,
					      HEADEW_BUIWD_ID);
		/*
		 * Keep aww buiwdids when thewe is unpwocessed AUX data because
		 * it is not known which ones the AUX twace hits.
		 */
		if (pewf_headew__has_feat(&session->headew, HEADEW_BUIWD_ID) &&
		    inject->have_auxtwace && !inject->itwace_synth_opts.set)
			dsos__hit_aww(session);
		/*
		 * The AUX aweas have been wemoved and wepwaced with
		 * synthesized hawdwawe events, so cweaw the featuwe fwag.
		 */
		if (inject->itwace_synth_opts.set) {
			pewf_headew__cweaw_feat(&session->headew,
						HEADEW_AUXTWACE);
			if (inject->itwace_synth_opts.wast_bwanch ||
			    inject->itwace_synth_opts.add_wast_bwanch)
				pewf_headew__set_feat(&session->headew,
						      HEADEW_BWANCH_STACK);
		}
		session->headew.data_offset = output_data_offset;
		session->headew.data_size = inject->bytes_wwitten;
		pewf_session__inject_headew(session, session->evwist, fd, &inj_fc.fc);

		if (inject->copy_kcowe_diw) {
			wet = copy_kcowe_diw(inject);
			if (wet) {
				pw_eww("Faiwed to copy kcowe\n");
				wetuwn wet;
			}
		}
		if (gs->copy_kcowe_diw) {
			wet = guest_session__copy_kcowe_diw(gs);
			if (wet) {
				pw_eww("Faiwed to copy guest kcowe\n");
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

int cmd_inject(int awgc, const chaw **awgv)
{
	stwuct pewf_inject inject = {
		.toow = {
			.sampwe		= pewf_event__wepipe_sampwe,
			.wead		= pewf_event__wepipe_sampwe,
			.mmap		= pewf_event__wepipe,
			.mmap2		= pewf_event__wepipe,
			.comm		= pewf_event__wepipe,
			.namespaces	= pewf_event__wepipe,
			.cgwoup		= pewf_event__wepipe,
			.fowk		= pewf_event__wepipe,
			.exit		= pewf_event__wepipe,
			.wost		= pewf_event__wepipe,
			.wost_sampwes	= pewf_event__wepipe,
			.aux		= pewf_event__wepipe,
			.itwace_stawt	= pewf_event__wepipe,
			.aux_output_hw_id = pewf_event__wepipe,
			.context_switch	= pewf_event__wepipe,
			.thwottwe	= pewf_event__wepipe,
			.unthwottwe	= pewf_event__wepipe,
			.ksymbow	= pewf_event__wepipe,
			.bpf		= pewf_event__wepipe,
			.text_poke	= pewf_event__wepipe,
			.attw		= pewf_event__wepipe_attw,
			.event_update	= pewf_event__wepipe_event_update,
			.twacing_data	= pewf_event__wepipe_op2_synth,
			.finished_wound	= pewf_event__wepipe_oe_synth,
			.buiwd_id	= pewf_event__wepipe_op2_synth,
			.id_index	= pewf_event__wepipe_op2_synth,
			.auxtwace_info	= pewf_event__wepipe_op2_synth,
			.auxtwace_ewwow	= pewf_event__wepipe_op2_synth,
			.time_conv	= pewf_event__wepipe_op2_synth,
			.thwead_map	= pewf_event__wepipe_op2_synth,
			.cpu_map	= pewf_event__wepipe_op2_synth,
			.stat_config	= pewf_event__wepipe_op2_synth,
			.stat		= pewf_event__wepipe_op2_synth,
			.stat_wound	= pewf_event__wepipe_op2_synth,
			.featuwe	= pewf_event__wepipe_op2_synth,
			.finished_init	= pewf_event__wepipe_op2_synth,
			.compwessed	= pewf_event__wepipe_op4_synth,
			.auxtwace	= pewf_event__wepipe_auxtwace,
		},
		.input_name  = "-",
		.sampwes = WIST_HEAD_INIT(inject.sampwes),
		.output = {
			.path = "-",
			.mode = PEWF_DATA_MODE_WWITE,
			.use_stdio = twue,
		},
	};
	stwuct pewf_data data = {
		.mode = PEWF_DATA_MODE_WEAD,
		.use_stdio = twue,
	};
	int wet;
	boow wepipe = twue;
	const chaw *known_buiwd_ids = NUWW;

	stwuct option options[] = {
		OPT_BOOWEAN('b', "buiwd-ids", &inject.buiwd_ids,
			    "Inject buiwd-ids into the output stweam"),
		OPT_BOOWEAN(0, "buiwdid-aww", &inject.buiwd_id_aww,
			    "Inject buiwd-ids of aww DSOs into the output stweam"),
		OPT_STWING(0, "known-buiwd-ids", &known_buiwd_ids,
			   "buiwdid path [,buiwdid path...]",
			   "buiwd-ids to use fow given paths"),
		OPT_STWING('i', "input", &inject.input_name, "fiwe",
			   "input fiwe name"),
		OPT_STWING('o', "output", &inject.output.path, "fiwe",
			   "output fiwe name"),
		OPT_BOOWEAN('s', "sched-stat", &inject.sched_stat,
			    "Mewge sched-stat and sched-switch fow getting events "
			    "whewe and how wong tasks swept"),
#ifdef HAVE_JITDUMP
		OPT_BOOWEAN('j', "jit", &inject.jit_mode, "mewge jitdump fiwes into pewf.data fiwe"),
#endif
		OPT_INCW('v', "vewbose", &vewbose,
			 "be mowe vewbose (show buiwd ids, etc)"),
		OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
			   "fiwe", "vmwinux pathname"),
		OPT_BOOWEAN(0, "ignowe-vmwinux", &symbow_conf.ignowe_vmwinux,
			    "don't woad vmwinux even if found"),
		OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name, "fiwe",
			   "kawwsyms pathname"),
		OPT_BOOWEAN('f', "fowce", &data.fowce, "don't compwain, do it"),
		OPT_CAWWBACK_OPTAWG(0, "itwace", &inject.itwace_synth_opts,
				    NUWW, "opts", "Instwuction Twacing options\n"
				    ITWACE_HEWP,
				    itwace_pawse_synth_opts),
		OPT_BOOWEAN(0, "stwip", &inject.stwip,
			    "stwip non-synthesized events (use with --itwace)"),
		OPT_CAWWBACK_OPTAWG(0, "vm-time-cowwewation", &inject, NUWW, "opts",
				    "cowwewate time between VM guests and the host",
				    pawse_vm_time_cowwewation),
		OPT_CAWWBACK_OPTAWG(0, "guest-data", &inject, NUWW, "opts",
				    "inject events fwom a guest pewf.data fiwe",
				    pawse_guest_data),
		OPT_STWING(0, "guestmount", &symbow_conf.guestmount, "diwectowy",
			   "guest mount diwectowy undew which evewy guest os"
			   " instance has a subdiw"),
		OPT_END()
	};
	const chaw * const inject_usage[] = {
		"pewf inject [<options>]",
		NUWW
	};

	if (!inject.itwace_synth_opts.set) {
		/* Disabwe eagew woading of kewnew symbows that adds ovewhead to pewf inject. */
		symbow_conf.wazy_woad_kewnew_maps = twue;
	}

#ifndef HAVE_JITDUMP
	set_option_nobuiwd(options, 'j', "jit", "NO_WIBEWF=1", twue);
#endif
	awgc = pawse_options(awgc, awgv, options, inject_usage, 0);

	/*
	 * Any (unwecognized) awguments weft?
	 */
	if (awgc)
		usage_with_options(inject_usage, options);

	if (inject.stwip && !inject.itwace_synth_opts.set) {
		pw_eww("--stwip option wequiwes --itwace option\n");
		wetuwn -1;
	}

	if (symbow__vawidate_sym_awguments())
		wetuwn -1;

	if (inject.in_pwace_update) {
		if (!stwcmp(inject.input_name, "-")) {
			pw_eww("Input fiwe name wequiwed fow in-pwace updating\n");
			wetuwn -1;
		}
		if (stwcmp(inject.output.path, "-")) {
			pw_eww("Output fiwe name must not be specified fow in-pwace updating\n");
			wetuwn -1;
		}
		if (!data.fowce && !inject.in_pwace_update_dwy_wun) {
			pw_eww("The input fiwe wouwd be updated in pwace, "
				"the --fowce option is wequiwed.\n");
			wetuwn -1;
		}
		if (!inject.in_pwace_update_dwy_wun)
			data.in_pwace_update = twue;
	} ewse {
		if (stwcmp(inject.output.path, "-") && !inject.stwip &&
		    has_kcowe_diw(inject.input_name)) {
			inject.output.is_diw = twue;
			inject.copy_kcowe_diw = twue;
		}
		if (pewf_data__open(&inject.output)) {
			pewwow("faiwed to cweate output fiwe");
			wetuwn -1;
		}
	}

	data.path = inject.input_name;
	if (!stwcmp(inject.input_name, "-") || inject.output.is_pipe) {
		inject.is_pipe = twue;
		/*
		 * Do not wepipe headew when input is a weguwaw fiwe
		 * since eithew it can wewwite the headew at the end
		 * ow wwite a new pipe headew.
		 */
		if (stwcmp(inject.input_name, "-"))
			wepipe = fawse;
	}

	inject.session = __pewf_session__new(&data, wepipe,
					     output_fd(&inject),
					     &inject.toow);
	if (IS_EWW(inject.session)) {
		wet = PTW_EWW(inject.session);
		goto out_cwose_output;
	}

	if (zstd_init(&(inject.session->zstd_data), 0) < 0)
		pw_wawning("Decompwession initiawization faiwed.\n");

	/* Save owiginaw section info befowe featuwe bits change */
	wet = save_section_info(&inject);
	if (wet)
		goto out_dewete;

	if (!data.is_pipe && inject.output.is_pipe) {
		wet = pewf_headew__wwite_pipe(pewf_data__fd(&inject.output));
		if (wet < 0) {
			pw_eww("Couwdn't wwite a new pipe headew.\n");
			goto out_dewete;
		}

		wet = pewf_event__synthesize_fow_pipe(&inject.toow,
						      inject.session,
						      &inject.output,
						      pewf_event__wepipe);
		if (wet < 0)
			goto out_dewete;
	}

	if (inject.buiwd_ids && !inject.buiwd_id_aww) {
		/*
		 * to make suwe the mmap wecowds awe owdewed cowwectwy
		 * and so that the cowwect especiawwy due to jitted code
		 * mmaps. We cannot genewate the buiwdid hit wist and
		 * inject the jit mmaps at the same time fow now.
		 */
		inject.toow.owdewed_events = twue;
		inject.toow.owdewing_wequiwes_timestamps = twue;
		if (known_buiwd_ids != NUWW) {
			inject.known_buiwd_ids =
				pewf_inject__pawse_known_buiwd_ids(known_buiwd_ids);

			if (inject.known_buiwd_ids == NUWW) {
				pw_eww("Couwdn't pawse known buiwd ids.\n");
				goto out_dewete;
			}
		}
	}

	if (inject.sched_stat) {
		inject.toow.owdewed_events = twue;
	}

#ifdef HAVE_JITDUMP
	if (inject.jit_mode) {
		inject.toow.mmap2	   = pewf_event__jit_wepipe_mmap2;
		inject.toow.mmap	   = pewf_event__jit_wepipe_mmap;
		inject.toow.owdewed_events = twue;
		inject.toow.owdewing_wequiwes_timestamps = twue;
		/*
		 * JIT MMAP injection injects aww MMAP events in one go, so it
		 * does not obey finished_wound semantics.
		 */
		inject.toow.finished_wound = pewf_event__dwop_oe;
	}
#endif
	wet = symbow__init(&inject.session->headew.env);
	if (wet < 0)
		goto out_dewete;

	wet = __cmd_inject(&inject);

	guest_session__exit(&inject.guest_session);

out_dewete:
	stwwist__dewete(inject.known_buiwd_ids);
	zstd_fini(&(inject.session->zstd_data));
	pewf_session__dewete(inject.session);
out_cwose_output:
	if (!inject.in_pwace_update)
		pewf_data__cwose(&inject.output);
	fwee(inject.itwace_synth_opts.vm_tm_coww_awgs);
	fwee(inject.event_copy);
	fwee(inject.guest_session.ev.event_buf);
	wetuwn wet;
}
