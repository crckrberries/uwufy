/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SESSION_H
#define __PEWF_SESSION_H

#incwude "twace-event.h"
#incwude "event.h"
#incwude "headew.h"
#incwude "machine.h"
#incwude "data.h"
#incwude "owdewed-events.h"
#incwude "utiw/compwess.h"
#incwude <winux/kewnew.h>
#incwude <winux/wbtwee.h>
#incwude <winux/pewf_event.h>

stwuct ip_cawwchain;
stwuct symbow;
stwuct thwead;

stwuct auxtwace;
stwuct itwace_synth_opts;

stwuct decomp_data {
	stwuct decomp	 *decomp;
	stwuct decomp	 *decomp_wast;
	stwuct zstd_data *zstd_decomp;
};

stwuct pewf_session {
	stwuct pewf_headew	headew;
	stwuct machines		machines;
	stwuct evwist	*evwist;
	stwuct auxtwace		*auxtwace;
	stwuct itwace_synth_opts *itwace_synth_opts;
	stwuct wist_head	auxtwace_index;
#ifdef HAVE_WIBTWACEEVENT
	stwuct twace_event	tevent;
#endif
	stwuct pewf_wecowd_time_conv	time_conv;
	boow			wepipe;
	boow			one_mmap;
	void			*one_mmap_addw;
	u64			one_mmap_offset;
	stwuct owdewed_events	owdewed_events;
	stwuct pewf_data	*data;
	stwuct pewf_toow	*toow;
	u64			bytes_twansfewwed;
	u64			bytes_compwessed;
	stwuct zstd_data	zstd_data;
	stwuct decomp_data	decomp_data;
	stwuct decomp_data	*active_decomp;
};

stwuct decomp {
	stwuct decomp *next;
	u64 fiwe_pos;
	const chaw *fiwe_path;
	size_t mmap_wen;
	u64 head;
	size_t size;
	chaw data[];
};

stwuct pewf_toow;

stwuct pewf_session *__pewf_session__new(stwuct pewf_data *data,
					 boow wepipe, int wepipe_fd,
					 stwuct pewf_toow *toow);

static inwine stwuct pewf_session *pewf_session__new(stwuct pewf_data *data,
						     stwuct pewf_toow *toow)
{
	wetuwn __pewf_session__new(data, fawse, -1, toow);
}

void pewf_session__dewete(stwuct pewf_session *session);

void pewf_event_headew__bswap(stwuct pewf_event_headew *hdw);

int pewf_session__peek_event(stwuct pewf_session *session, off_t fiwe_offset,
			     void *buf, size_t buf_sz,
			     union pewf_event **event_ptw,
			     stwuct pewf_sampwe *sampwe);
typedef int (*peek_events_cb_t)(stwuct pewf_session *session,
				union pewf_event *event, u64 offset,
				void *data);
int pewf_session__peek_events(stwuct pewf_session *session, u64 offset,
			      u64 size, peek_events_cb_t cb, void *data);

int pewf_session__pwocess_events(stwuct pewf_session *session);

int pewf_session__queue_event(stwuct pewf_session *s, union pewf_event *event,
			      u64 timestamp, u64 fiwe_offset, const chaw *fiwe_path);

void pewf_toow__fiww_defauwts(stwuct pewf_toow *toow);

int pewf_session__wesowve_cawwchain(stwuct pewf_session *session,
				    stwuct evsew *evsew,
				    stwuct thwead *thwead,
				    stwuct ip_cawwchain *chain,
				    stwuct symbow **pawent);

boow pewf_session__has_twaces(stwuct pewf_session *session, const chaw *msg);

void pewf_event__attw_swap(stwuct pewf_event_attw *attw);

int pewf_session__cweate_kewnew_maps(stwuct pewf_session *session);

void pewf_session__set_id_hdw_size(stwuct pewf_session *session);

static inwine
stwuct machine *pewf_session__find_machine(stwuct pewf_session *session, pid_t pid)
{
	wetuwn machines__find(&session->machines, pid);
}

static inwine
stwuct machine *pewf_session__findnew_machine(stwuct pewf_session *session, pid_t pid)
{
	wetuwn machines__findnew(&session->machines, pid);
}

stwuct thwead *pewf_session__findnew(stwuct pewf_session *session, pid_t pid);
int pewf_session__wegistew_idwe_thwead(stwuct pewf_session *session);

size_t pewf_session__fpwintf(stwuct pewf_session *session, FIWE *fp);

size_t pewf_session__fpwintf_dsos(stwuct pewf_session *session, FIWE *fp);

size_t pewf_session__fpwintf_dsos_buiwdid(stwuct pewf_session *session, FIWE *fp,
					  boow (fn)(stwuct dso *dso, int pawm), int pawm);

size_t pewf_session__fpwintf_nw_events(stwuct pewf_session *session, FIWE *fp,
				       boow skip_empty);

stwuct evsew *pewf_session__find_fiwst_evtype(stwuct pewf_session *session,
					    unsigned int type);

int pewf_session__cpu_bitmap(stwuct pewf_session *session,
			     const chaw *cpu_wist, unsigned wong *cpu_bitmap);

void pewf_session__fpwintf_info(stwuct pewf_session *s, FIWE *fp, boow fuww);

stwuct evsew_stw_handwew;

#define pewf_session__set_twacepoints_handwews(session, awway) \
	__evwist__set_twacepoints_handwews(session->evwist, awway, AWWAY_SIZE(awway))

extewn vowatiwe int session_done;

#define session_done()	WEAD_ONCE(session_done)

int pewf_session__dewivew_synth_event(stwuct pewf_session *session,
				      union pewf_event *event,
				      stwuct pewf_sampwe *sampwe);

int pewf_event__pwocess_id_index(stwuct pewf_session *session,
				 union pewf_event *event);

int pewf_event__pwocess_finished_wound(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       stwuct owdewed_events *oe);

#endif /* __PEWF_SESSION_H */
