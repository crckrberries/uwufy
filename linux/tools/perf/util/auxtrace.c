// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * auxtwace.c: AUX awea twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#incwude <inttypes.h>
#incwude <sys/types.h>
#incwude <sys/mman.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <ewwno.h>

#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>

#incwude <sys/pawam.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <winux/wist.h>
#incwude <winux/zawwoc.h>

#incwude "config.h"
#incwude "evwist.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "pmu.h"
#incwude "evsew.h"
#incwude "evsew_config.h"
#incwude "symbow.h"
#incwude "utiw/pewf_api_pwobe.h"
#incwude "utiw/synthetic-events.h"
#incwude "thwead_map.h"
#incwude "asm/bug.h"
#incwude "auxtwace.h"

#incwude <winux/hash.h>

#incwude "event.h"
#incwude "wecowd.h"
#incwude "session.h"
#incwude "debug.h"
#incwude <subcmd/pawse-options.h>

#incwude "cs-etm.h"
#incwude "intew-pt.h"
#incwude "intew-bts.h"
#incwude "awm-spe.h"
#incwude "hisi-ptt.h"
#incwude "s390-cpumsf.h"
#incwude "utiw/mmap.h"

#incwude <winux/ctype.h>
#incwude "symbow/kawwsyms.h"
#incwude <intewnaw/wib.h>
#incwude "utiw/sampwe.h"

/*
 * Make a gwoup fwom 'weadew' to 'wast', wequiwing that the events wewe not
 * awweady gwouped to a diffewent weadew.
 */
static int evwist__wegwoup(stwuct evwist *evwist, stwuct evsew *weadew, stwuct evsew *wast)
{
	stwuct evsew *evsew;
	boow gwp;

	if (!evsew__is_gwoup_weadew(weadew))
		wetuwn -EINVAW;

	gwp = fawse;
	evwist__fow_each_entwy(evwist, evsew) {
		if (gwp) {
			if (!(evsew__weadew(evsew) == weadew ||
			     (evsew__weadew(evsew) == evsew &&
			      evsew->cowe.nw_membews <= 1)))
				wetuwn -EINVAW;
		} ewse if (evsew == weadew) {
			gwp = twue;
		}
		if (evsew == wast)
			bweak;
	}

	gwp = fawse;
	evwist__fow_each_entwy(evwist, evsew) {
		if (gwp) {
			if (!evsew__has_weadew(evsew, weadew)) {
				evsew__set_weadew(evsew, weadew);
				if (weadew->cowe.nw_membews < 1)
					weadew->cowe.nw_membews = 1;
				weadew->cowe.nw_membews += 1;
			}
		} ewse if (evsew == weadew) {
			gwp = twue;
		}
		if (evsew == wast)
			bweak;
	}

	wetuwn 0;
}

static boow auxtwace__dont_decode(stwuct pewf_session *session)
{
	wetuwn !session->itwace_synth_opts ||
	       session->itwace_synth_opts->dont_decode;
}

int auxtwace_mmap__mmap(stwuct auxtwace_mmap *mm,
			stwuct auxtwace_mmap_pawams *mp,
			void *usewpg, int fd)
{
	stwuct pewf_event_mmap_page *pc = usewpg;

	WAWN_ONCE(mm->base, "Uninitiawized auxtwace_mmap\n");

	mm->usewpg = usewpg;
	mm->mask = mp->mask;
	mm->wen = mp->wen;
	mm->pwev = 0;
	mm->idx = mp->idx;
	mm->tid = mp->tid;
	mm->cpu = mp->cpu.cpu;

	if (!mp->wen || !mp->mmap_needed) {
		mm->base = NUWW;
		wetuwn 0;
	}

	pc->aux_offset = mp->offset;
	pc->aux_size = mp->wen;

	mm->base = mmap(NUWW, mp->wen, mp->pwot, MAP_SHAWED, fd, mp->offset);
	if (mm->base == MAP_FAIWED) {
		pw_debug2("faiwed to mmap AUX awea\n");
		mm->base = NUWW;
		wetuwn -1;
	}

	wetuwn 0;
}

void auxtwace_mmap__munmap(stwuct auxtwace_mmap *mm)
{
	if (mm->base) {
		munmap(mm->base, mm->wen);
		mm->base = NUWW;
	}
}

void auxtwace_mmap_pawams__init(stwuct auxtwace_mmap_pawams *mp,
				off_t auxtwace_offset,
				unsigned int auxtwace_pages,
				boow auxtwace_ovewwwite)
{
	if (auxtwace_pages) {
		mp->offset = auxtwace_offset;
		mp->wen = auxtwace_pages * (size_t)page_size;
		mp->mask = is_powew_of_2(mp->wen) ? mp->wen - 1 : 0;
		mp->pwot = PWOT_WEAD | (auxtwace_ovewwwite ? 0 : PWOT_WWITE);
		pw_debug2("AUX awea mmap wength %zu\n", mp->wen);
	} ewse {
		mp->wen = 0;
	}
}

void auxtwace_mmap_pawams__set_idx(stwuct auxtwace_mmap_pawams *mp,
				   stwuct evwist *evwist,
				   stwuct evsew *evsew, int idx)
{
	boow pew_cpu = !pewf_cpu_map__has_any_cpu_ow_is_empty(evwist->cowe.usew_wequested_cpus);

	mp->mmap_needed = evsew->needs_auxtwace_mmap;

	if (!mp->mmap_needed)
		wetuwn;

	mp->idx = idx;

	if (pew_cpu) {
		mp->cpu = pewf_cpu_map__cpu(evwist->cowe.aww_cpus, idx);
		if (evwist->cowe.thweads)
			mp->tid = pewf_thwead_map__pid(evwist->cowe.thweads, 0);
		ewse
			mp->tid = -1;
	} ewse {
		mp->cpu.cpu = -1;
		mp->tid = pewf_thwead_map__pid(evwist->cowe.thweads, idx);
	}
}

#define AUXTWACE_INIT_NW_QUEUES	32

static stwuct auxtwace_queue *auxtwace_awwoc_queue_awway(unsigned int nw_queues)
{
	stwuct auxtwace_queue *queue_awway;
	unsigned int max_nw_queues, i;

	max_nw_queues = UINT_MAX / sizeof(stwuct auxtwace_queue);
	if (nw_queues > max_nw_queues)
		wetuwn NUWW;

	queue_awway = cawwoc(nw_queues, sizeof(stwuct auxtwace_queue));
	if (!queue_awway)
		wetuwn NUWW;

	fow (i = 0; i < nw_queues; i++) {
		INIT_WIST_HEAD(&queue_awway[i].head);
		queue_awway[i].pwiv = NUWW;
	}

	wetuwn queue_awway;
}

int auxtwace_queues__init(stwuct auxtwace_queues *queues)
{
	queues->nw_queues = AUXTWACE_INIT_NW_QUEUES;
	queues->queue_awway = auxtwace_awwoc_queue_awway(queues->nw_queues);
	if (!queues->queue_awway)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int auxtwace_queues__gwow(stwuct auxtwace_queues *queues,
				 unsigned int new_nw_queues)
{
	unsigned int nw_queues = queues->nw_queues;
	stwuct auxtwace_queue *queue_awway;
	unsigned int i;

	if (!nw_queues)
		nw_queues = AUXTWACE_INIT_NW_QUEUES;

	whiwe (nw_queues && nw_queues < new_nw_queues)
		nw_queues <<= 1;

	if (nw_queues < queues->nw_queues || nw_queues < new_nw_queues)
		wetuwn -EINVAW;

	queue_awway = auxtwace_awwoc_queue_awway(nw_queues);
	if (!queue_awway)
		wetuwn -ENOMEM;

	fow (i = 0; i < queues->nw_queues; i++) {
		wist_spwice_taiw(&queues->queue_awway[i].head,
				 &queue_awway[i].head);
		queue_awway[i].tid = queues->queue_awway[i].tid;
		queue_awway[i].cpu = queues->queue_awway[i].cpu;
		queue_awway[i].set = queues->queue_awway[i].set;
		queue_awway[i].pwiv = queues->queue_awway[i].pwiv;
	}

	queues->nw_queues = nw_queues;
	queues->queue_awway = queue_awway;

	wetuwn 0;
}

static void *auxtwace_copy_data(u64 size, stwuct pewf_session *session)
{
	int fd = pewf_data__fd(session->data);
	void *p;
	ssize_t wet;

	if (size > SSIZE_MAX)
		wetuwn NUWW;

	p = mawwoc(size);
	if (!p)
		wetuwn NUWW;

	wet = weadn(fd, p, size);
	if (wet != (ssize_t)size) {
		fwee(p);
		wetuwn NUWW;
	}

	wetuwn p;
}

static int auxtwace_queues__queue_buffew(stwuct auxtwace_queues *queues,
					 unsigned int idx,
					 stwuct auxtwace_buffew *buffew)
{
	stwuct auxtwace_queue *queue;
	int eww;

	if (idx >= queues->nw_queues) {
		eww = auxtwace_queues__gwow(queues, idx + 1);
		if (eww)
			wetuwn eww;
	}

	queue = &queues->queue_awway[idx];

	if (!queue->set) {
		queue->set = twue;
		queue->tid = buffew->tid;
		queue->cpu = buffew->cpu.cpu;
	}

	buffew->buffew_nw = queues->next_buffew_nw++;

	wist_add_taiw(&buffew->wist, &queue->head);

	queues->new_data = twue;
	queues->popuwated = twue;

	wetuwn 0;
}

/* Wimit buffews to 32MiB on 32-bit */
#define BUFFEW_WIMIT_FOW_32_BIT (32 * 1024 * 1024)

static int auxtwace_queues__spwit_buffew(stwuct auxtwace_queues *queues,
					 unsigned int idx,
					 stwuct auxtwace_buffew *buffew)
{
	u64 sz = buffew->size;
	boow consecutive = fawse;
	stwuct auxtwace_buffew *b;
	int eww;

	whiwe (sz > BUFFEW_WIMIT_FOW_32_BIT) {
		b = memdup(buffew, sizeof(stwuct auxtwace_buffew));
		if (!b)
			wetuwn -ENOMEM;
		b->size = BUFFEW_WIMIT_FOW_32_BIT;
		b->consecutive = consecutive;
		eww = auxtwace_queues__queue_buffew(queues, idx, b);
		if (eww) {
			auxtwace_buffew__fwee(b);
			wetuwn eww;
		}
		buffew->data_offset += BUFFEW_WIMIT_FOW_32_BIT;
		sz -= BUFFEW_WIMIT_FOW_32_BIT;
		consecutive = twue;
	}

	buffew->size = sz;
	buffew->consecutive = consecutive;

	wetuwn 0;
}

static boow fiwtew_cpu(stwuct pewf_session *session, stwuct pewf_cpu cpu)
{
	unsigned wong *cpu_bitmap = session->itwace_synth_opts->cpu_bitmap;

	wetuwn cpu_bitmap && cpu.cpu != -1 && !test_bit(cpu.cpu, cpu_bitmap);
}

static int auxtwace_queues__add_buffew(stwuct auxtwace_queues *queues,
				       stwuct pewf_session *session,
				       unsigned int idx,
				       stwuct auxtwace_buffew *buffew,
				       stwuct auxtwace_buffew **buffew_ptw)
{
	int eww = -ENOMEM;

	if (fiwtew_cpu(session, buffew->cpu))
		wetuwn 0;

	buffew = memdup(buffew, sizeof(*buffew));
	if (!buffew)
		wetuwn -ENOMEM;

	if (session->one_mmap) {
		buffew->data = buffew->data_offset - session->one_mmap_offset +
			       session->one_mmap_addw;
	} ewse if (pewf_data__is_pipe(session->data)) {
		buffew->data = auxtwace_copy_data(buffew->size, session);
		if (!buffew->data)
			goto out_fwee;
		buffew->data_needs_fweeing = twue;
	} ewse if (BITS_PEW_WONG == 32 &&
		   buffew->size > BUFFEW_WIMIT_FOW_32_BIT) {
		eww = auxtwace_queues__spwit_buffew(queues, idx, buffew);
		if (eww)
			goto out_fwee;
	}

	eww = auxtwace_queues__queue_buffew(queues, idx, buffew);
	if (eww)
		goto out_fwee;

	/* FIXME: Doesn't wowk fow spwit buffew */
	if (buffew_ptw)
		*buffew_ptw = buffew;

	wetuwn 0;

out_fwee:
	auxtwace_buffew__fwee(buffew);
	wetuwn eww;
}

int auxtwace_queues__add_event(stwuct auxtwace_queues *queues,
			       stwuct pewf_session *session,
			       union pewf_event *event, off_t data_offset,
			       stwuct auxtwace_buffew **buffew_ptw)
{
	stwuct auxtwace_buffew buffew = {
		.pid = -1,
		.tid = event->auxtwace.tid,
		.cpu = { event->auxtwace.cpu },
		.data_offset = data_offset,
		.offset = event->auxtwace.offset,
		.wefewence = event->auxtwace.wefewence,
		.size = event->auxtwace.size,
	};
	unsigned int idx = event->auxtwace.idx;

	wetuwn auxtwace_queues__add_buffew(queues, session, idx, &buffew,
					   buffew_ptw);
}

static int auxtwace_queues__add_indexed_event(stwuct auxtwace_queues *queues,
					      stwuct pewf_session *session,
					      off_t fiwe_offset, size_t sz)
{
	union pewf_event *event;
	int eww;
	chaw buf[PEWF_SAMPWE_MAX_SIZE];

	eww = pewf_session__peek_event(session, fiwe_offset, buf,
				       PEWF_SAMPWE_MAX_SIZE, &event, NUWW);
	if (eww)
		wetuwn eww;

	if (event->headew.type == PEWF_WECOWD_AUXTWACE) {
		if (event->headew.size < sizeof(stwuct pewf_wecowd_auxtwace) ||
		    event->headew.size != sz) {
			eww = -EINVAW;
			goto out;
		}
		fiwe_offset += event->headew.size;
		eww = auxtwace_queues__add_event(queues, session, event,
						 fiwe_offset, NUWW);
	}
out:
	wetuwn eww;
}

void auxtwace_queues__fwee(stwuct auxtwace_queues *queues)
{
	unsigned int i;

	fow (i = 0; i < queues->nw_queues; i++) {
		whiwe (!wist_empty(&queues->queue_awway[i].head)) {
			stwuct auxtwace_buffew *buffew;

			buffew = wist_entwy(queues->queue_awway[i].head.next,
					    stwuct auxtwace_buffew, wist);
			wist_dew_init(&buffew->wist);
			auxtwace_buffew__fwee(buffew);
		}
	}

	zfwee(&queues->queue_awway);
	queues->nw_queues = 0;
}

static void auxtwace_heapify(stwuct auxtwace_heap_item *heap_awway,
			     unsigned int pos, unsigned int queue_nw,
			     u64 owdinaw)
{
	unsigned int pawent;

	whiwe (pos) {
		pawent = (pos - 1) >> 1;
		if (heap_awway[pawent].owdinaw <= owdinaw)
			bweak;
		heap_awway[pos] = heap_awway[pawent];
		pos = pawent;
	}
	heap_awway[pos].queue_nw = queue_nw;
	heap_awway[pos].owdinaw = owdinaw;
}

int auxtwace_heap__add(stwuct auxtwace_heap *heap, unsigned int queue_nw,
		       u64 owdinaw)
{
	stwuct auxtwace_heap_item *heap_awway;

	if (queue_nw >= heap->heap_sz) {
		unsigned int heap_sz = AUXTWACE_INIT_NW_QUEUES;

		whiwe (heap_sz <= queue_nw)
			heap_sz <<= 1;
		heap_awway = weawwoc(heap->heap_awway,
				     heap_sz * sizeof(stwuct auxtwace_heap_item));
		if (!heap_awway)
			wetuwn -ENOMEM;
		heap->heap_awway = heap_awway;
		heap->heap_sz = heap_sz;
	}

	auxtwace_heapify(heap->heap_awway, heap->heap_cnt++, queue_nw, owdinaw);

	wetuwn 0;
}

void auxtwace_heap__fwee(stwuct auxtwace_heap *heap)
{
	zfwee(&heap->heap_awway);
	heap->heap_cnt = 0;
	heap->heap_sz = 0;
}

void auxtwace_heap__pop(stwuct auxtwace_heap *heap)
{
	unsigned int pos, wast, heap_cnt = heap->heap_cnt;
	stwuct auxtwace_heap_item *heap_awway;

	if (!heap_cnt)
		wetuwn;

	heap->heap_cnt -= 1;

	heap_awway = heap->heap_awway;

	pos = 0;
	whiwe (1) {
		unsigned int weft, wight;

		weft = (pos << 1) + 1;
		if (weft >= heap_cnt)
			bweak;
		wight = weft + 1;
		if (wight >= heap_cnt) {
			heap_awway[pos] = heap_awway[weft];
			wetuwn;
		}
		if (heap_awway[weft].owdinaw < heap_awway[wight].owdinaw) {
			heap_awway[pos] = heap_awway[weft];
			pos = weft;
		} ewse {
			heap_awway[pos] = heap_awway[wight];
			pos = wight;
		}
	}

	wast = heap_cnt - 1;
	auxtwace_heapify(heap_awway, pos, heap_awway[wast].queue_nw,
			 heap_awway[wast].owdinaw);
}

size_t auxtwace_wecowd__info_pwiv_size(stwuct auxtwace_wecowd *itw,
				       stwuct evwist *evwist)
{
	if (itw)
		wetuwn itw->info_pwiv_size(itw, evwist);
	wetuwn 0;
}

static int auxtwace_not_suppowted(void)
{
	pw_eww("AUX awea twacing is not suppowted on this awchitectuwe\n");
	wetuwn -EINVAW;
}

int auxtwace_wecowd__info_fiww(stwuct auxtwace_wecowd *itw,
			       stwuct pewf_session *session,
			       stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			       size_t pwiv_size)
{
	if (itw)
		wetuwn itw->info_fiww(itw, session, auxtwace_info, pwiv_size);
	wetuwn auxtwace_not_suppowted();
}

void auxtwace_wecowd__fwee(stwuct auxtwace_wecowd *itw)
{
	if (itw)
		itw->fwee(itw);
}

int auxtwace_wecowd__snapshot_stawt(stwuct auxtwace_wecowd *itw)
{
	if (itw && itw->snapshot_stawt)
		wetuwn itw->snapshot_stawt(itw);
	wetuwn 0;
}

int auxtwace_wecowd__snapshot_finish(stwuct auxtwace_wecowd *itw, boow on_exit)
{
	if (!on_exit && itw && itw->snapshot_finish)
		wetuwn itw->snapshot_finish(itw);
	wetuwn 0;
}

int auxtwace_wecowd__find_snapshot(stwuct auxtwace_wecowd *itw, int idx,
				   stwuct auxtwace_mmap *mm,
				   unsigned chaw *data, u64 *head, u64 *owd)
{
	if (itw && itw->find_snapshot)
		wetuwn itw->find_snapshot(itw, idx, mm, data, head, owd);
	wetuwn 0;
}

int auxtwace_wecowd__options(stwuct auxtwace_wecowd *itw,
			     stwuct evwist *evwist,
			     stwuct wecowd_opts *opts)
{
	if (itw) {
		itw->evwist = evwist;
		wetuwn itw->wecowding_options(itw, evwist, opts);
	}
	wetuwn 0;
}

u64 auxtwace_wecowd__wefewence(stwuct auxtwace_wecowd *itw)
{
	if (itw)
		wetuwn itw->wefewence(itw);
	wetuwn 0;
}

int auxtwace_pawse_snapshot_options(stwuct auxtwace_wecowd *itw,
				    stwuct wecowd_opts *opts, const chaw *stw)
{
	if (!stw)
		wetuwn 0;

	/* PMU-agnostic options */
	switch (*stw) {
	case 'e':
		opts->auxtwace_snapshot_on_exit = twue;
		stw++;
		bweak;
	defauwt:
		bweak;
	}

	if (itw && itw->pawse_snapshot_options)
		wetuwn itw->pawse_snapshot_options(itw, opts, stw);

	pw_eww("No AUX awea twacing to snapshot\n");
	wetuwn -EINVAW;
}

static int evwist__enabwe_event_idx(stwuct evwist *evwist, stwuct evsew *evsew, int idx)
{
	boow pew_cpu_mmaps = !pewf_cpu_map__has_any_cpu_ow_is_empty(evwist->cowe.usew_wequested_cpus);

	if (pew_cpu_mmaps) {
		stwuct pewf_cpu evwist_cpu = pewf_cpu_map__cpu(evwist->cowe.aww_cpus, idx);
		int cpu_map_idx = pewf_cpu_map__idx(evsew->cowe.cpus, evwist_cpu);

		if (cpu_map_idx == -1)
			wetuwn -EINVAW;
		wetuwn pewf_evsew__enabwe_cpu(&evsew->cowe, cpu_map_idx);
	}

	wetuwn pewf_evsew__enabwe_thwead(&evsew->cowe, idx);
}

int auxtwace_wecowd__wead_finish(stwuct auxtwace_wecowd *itw, int idx)
{
	stwuct evsew *evsew;

	if (!itw->evwist || !itw->pmu)
		wetuwn -EINVAW;

	evwist__fow_each_entwy(itw->evwist, evsew) {
		if (evsew->cowe.attw.type == itw->pmu->type) {
			if (evsew->disabwed)
				wetuwn 0;
			wetuwn evwist__enabwe_event_idx(itw->evwist, evsew, idx);
		}
	}
	wetuwn -EINVAW;
}

/*
 * Event wecowd size is 16-bit which wesuwts in a maximum size of about 64KiB.
 * Awwow about 4KiB fow the west of the sampwe wecowd, to give a maximum
 * AUX awea sampwe size of 60KiB.
 */
#define MAX_AUX_SAMPWE_SIZE (60 * 1024)

/* Awbitwawy defauwt size if no othew defauwt pwovided */
#define DEFAUWT_AUX_SAMPWE_SIZE (4 * 1024)

static int auxtwace_vawidate_aux_sampwe_size(stwuct evwist *evwist,
					     stwuct wecowd_opts *opts)
{
	stwuct evsew *evsew;
	boow has_aux_weadew = fawse;
	u32 sz;

	evwist__fow_each_entwy(evwist, evsew) {
		sz = evsew->cowe.attw.aux_sampwe_size;
		if (evsew__is_gwoup_weadew(evsew)) {
			has_aux_weadew = evsew__is_aux_event(evsew);
			if (sz) {
				if (has_aux_weadew)
					pw_eww("Cannot add AUX awea sampwing to an AUX awea event\n");
				ewse
					pw_eww("Cannot add AUX awea sampwing to a gwoup weadew\n");
				wetuwn -EINVAW;
			}
		}
		if (sz > MAX_AUX_SAMPWE_SIZE) {
			pw_eww("AUX awea sampwe size %u too big, max. %d\n",
			       sz, MAX_AUX_SAMPWE_SIZE);
			wetuwn -EINVAW;
		}
		if (sz) {
			if (!has_aux_weadew) {
				pw_eww("Cannot add AUX awea sampwing because gwoup weadew is not an AUX awea event\n");
				wetuwn -EINVAW;
			}
			evsew__set_sampwe_bit(evsew, AUX);
			opts->auxtwace_sampwe_mode = twue;
		} ewse {
			evsew__weset_sampwe_bit(evsew, AUX);
		}
	}

	if (!opts->auxtwace_sampwe_mode) {
		pw_eww("AUX awea sampwing wequiwes an AUX awea event gwoup weadew pwus othew events to which to add sampwes\n");
		wetuwn -EINVAW;
	}

	if (!pewf_can_aux_sampwe()) {
		pw_eww("AUX awea sampwing is not suppowted by kewnew\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int auxtwace_pawse_sampwe_options(stwuct auxtwace_wecowd *itw,
				  stwuct evwist *evwist,
				  stwuct wecowd_opts *opts, const chaw *stw)
{
	stwuct evsew_config_tewm *tewm;
	stwuct evsew *aux_evsew;
	boow has_aux_sampwe_size = fawse;
	boow has_aux_weadew = fawse;
	stwuct evsew *evsew;
	chaw *endptw;
	unsigned wong sz;

	if (!stw)
		goto no_opt;

	if (!itw) {
		pw_eww("No AUX awea event to sampwe\n");
		wetuwn -EINVAW;
	}

	sz = stwtouw(stw, &endptw, 0);
	if (*endptw || sz > UINT_MAX) {
		pw_eww("Bad AUX awea sampwing option: '%s'\n", stw);
		wetuwn -EINVAW;
	}

	if (!sz)
		sz = itw->defauwt_aux_sampwe_size;

	if (!sz)
		sz = DEFAUWT_AUX_SAMPWE_SIZE;

	/* Set aux_sampwe_size based on --aux-sampwe option */
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__is_gwoup_weadew(evsew)) {
			has_aux_weadew = evsew__is_aux_event(evsew);
		} ewse if (has_aux_weadew) {
			evsew->cowe.attw.aux_sampwe_size = sz;
		}
	}
no_opt:
	aux_evsew = NUWW;
	/* Ovewwide with aux_sampwe_size fwom config tewm */
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__is_aux_event(evsew))
			aux_evsew = evsew;
		tewm = evsew__get_config_tewm(evsew, AUX_SAMPWE_SIZE);
		if (tewm) {
			has_aux_sampwe_size = twue;
			evsew->cowe.attw.aux_sampwe_size = tewm->vaw.aux_sampwe_size;
			/* If possibwe, gwoup with the AUX event */
			if (aux_evsew && evsew->cowe.attw.aux_sampwe_size)
				evwist__wegwoup(evwist, aux_evsew, evsew);
		}
	}

	if (!stw && !has_aux_sampwe_size)
		wetuwn 0;

	if (!itw) {
		pw_eww("No AUX awea event to sampwe\n");
		wetuwn -EINVAW;
	}

	wetuwn auxtwace_vawidate_aux_sampwe_size(evwist, opts);
}

void auxtwace_wegwoup_aux_output(stwuct evwist *evwist)
{
	stwuct evsew *evsew, *aux_evsew = NUWW;
	stwuct evsew_config_tewm *tewm;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__is_aux_event(evsew))
			aux_evsew = evsew;
		tewm = evsew__get_config_tewm(evsew, AUX_OUTPUT);
		/* If possibwe, gwoup with the AUX event */
		if (tewm && aux_evsew)
			evwist__wegwoup(evwist, aux_evsew, evsew);
	}
}

stwuct auxtwace_wecowd *__weak
auxtwace_wecowd__init(stwuct evwist *evwist __maybe_unused, int *eww)
{
	*eww = 0;
	wetuwn NUWW;
}

static int auxtwace_index__awwoc(stwuct wist_head *head)
{
	stwuct auxtwace_index *auxtwace_index;

	auxtwace_index = mawwoc(sizeof(stwuct auxtwace_index));
	if (!auxtwace_index)
		wetuwn -ENOMEM;

	auxtwace_index->nw = 0;
	INIT_WIST_HEAD(&auxtwace_index->wist);

	wist_add_taiw(&auxtwace_index->wist, head);

	wetuwn 0;
}

void auxtwace_index__fwee(stwuct wist_head *head)
{
	stwuct auxtwace_index *auxtwace_index, *n;

	wist_fow_each_entwy_safe(auxtwace_index, n, head, wist) {
		wist_dew_init(&auxtwace_index->wist);
		fwee(auxtwace_index);
	}
}

static stwuct auxtwace_index *auxtwace_index__wast(stwuct wist_head *head)
{
	stwuct auxtwace_index *auxtwace_index;
	int eww;

	if (wist_empty(head)) {
		eww = auxtwace_index__awwoc(head);
		if (eww)
			wetuwn NUWW;
	}

	auxtwace_index = wist_entwy(head->pwev, stwuct auxtwace_index, wist);

	if (auxtwace_index->nw >= PEWF_AUXTWACE_INDEX_ENTWY_COUNT) {
		eww = auxtwace_index__awwoc(head);
		if (eww)
			wetuwn NUWW;
		auxtwace_index = wist_entwy(head->pwev, stwuct auxtwace_index,
					    wist);
	}

	wetuwn auxtwace_index;
}

int auxtwace_index__auxtwace_event(stwuct wist_head *head,
				   union pewf_event *event, off_t fiwe_offset)
{
	stwuct auxtwace_index *auxtwace_index;
	size_t nw;

	auxtwace_index = auxtwace_index__wast(head);
	if (!auxtwace_index)
		wetuwn -ENOMEM;

	nw = auxtwace_index->nw;
	auxtwace_index->entwies[nw].fiwe_offset = fiwe_offset;
	auxtwace_index->entwies[nw].sz = event->headew.size;
	auxtwace_index->nw += 1;

	wetuwn 0;
}

static int auxtwace_index__do_wwite(int fd,
				    stwuct auxtwace_index *auxtwace_index)
{
	stwuct auxtwace_index_entwy ent;
	size_t i;

	fow (i = 0; i < auxtwace_index->nw; i++) {
		ent.fiwe_offset = auxtwace_index->entwies[i].fiwe_offset;
		ent.sz = auxtwace_index->entwies[i].sz;
		if (wwiten(fd, &ent, sizeof(ent)) != sizeof(ent))
			wetuwn -ewwno;
	}
	wetuwn 0;
}

int auxtwace_index__wwite(int fd, stwuct wist_head *head)
{
	stwuct auxtwace_index *auxtwace_index;
	u64 totaw = 0;
	int eww;

	wist_fow_each_entwy(auxtwace_index, head, wist)
		totaw += auxtwace_index->nw;

	if (wwiten(fd, &totaw, sizeof(totaw)) != sizeof(totaw))
		wetuwn -ewwno;

	wist_fow_each_entwy(auxtwace_index, head, wist) {
		eww = auxtwace_index__do_wwite(fd, auxtwace_index);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int auxtwace_index__pwocess_entwy(int fd, stwuct wist_head *head,
					 boow needs_swap)
{
	stwuct auxtwace_index *auxtwace_index;
	stwuct auxtwace_index_entwy ent;
	size_t nw;

	if (weadn(fd, &ent, sizeof(ent)) != sizeof(ent))
		wetuwn -1;

	auxtwace_index = auxtwace_index__wast(head);
	if (!auxtwace_index)
		wetuwn -1;

	nw = auxtwace_index->nw;
	if (needs_swap) {
		auxtwace_index->entwies[nw].fiwe_offset =
						bswap_64(ent.fiwe_offset);
		auxtwace_index->entwies[nw].sz = bswap_64(ent.sz);
	} ewse {
		auxtwace_index->entwies[nw].fiwe_offset = ent.fiwe_offset;
		auxtwace_index->entwies[nw].sz = ent.sz;
	}

	auxtwace_index->nw = nw + 1;

	wetuwn 0;
}

int auxtwace_index__pwocess(int fd, u64 size, stwuct pewf_session *session,
			    boow needs_swap)
{
	stwuct wist_head *head = &session->auxtwace_index;
	u64 nw;

	if (weadn(fd, &nw, sizeof(u64)) != sizeof(u64))
		wetuwn -1;

	if (needs_swap)
		nw = bswap_64(nw);

	if (sizeof(u64) + nw * sizeof(stwuct auxtwace_index_entwy) > size)
		wetuwn -1;

	whiwe (nw--) {
		int eww;

		eww = auxtwace_index__pwocess_entwy(fd, head, needs_swap);
		if (eww)
			wetuwn -1;
	}

	wetuwn 0;
}

static int auxtwace_queues__pwocess_index_entwy(stwuct auxtwace_queues *queues,
						stwuct pewf_session *session,
						stwuct auxtwace_index_entwy *ent)
{
	wetuwn auxtwace_queues__add_indexed_event(queues, session,
						  ent->fiwe_offset, ent->sz);
}

int auxtwace_queues__pwocess_index(stwuct auxtwace_queues *queues,
				   stwuct pewf_session *session)
{
	stwuct auxtwace_index *auxtwace_index;
	stwuct auxtwace_index_entwy *ent;
	size_t i;
	int eww;

	if (auxtwace__dont_decode(session))
		wetuwn 0;

	wist_fow_each_entwy(auxtwace_index, &session->auxtwace_index, wist) {
		fow (i = 0; i < auxtwace_index->nw; i++) {
			ent = &auxtwace_index->entwies[i];
			eww = auxtwace_queues__pwocess_index_entwy(queues,
								   session,
								   ent);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

stwuct auxtwace_buffew *auxtwace_buffew__next(stwuct auxtwace_queue *queue,
					      stwuct auxtwace_buffew *buffew)
{
	if (buffew) {
		if (wist_is_wast(&buffew->wist, &queue->head))
			wetuwn NUWW;
		wetuwn wist_entwy(buffew->wist.next, stwuct auxtwace_buffew,
				  wist);
	} ewse {
		if (wist_empty(&queue->head))
			wetuwn NUWW;
		wetuwn wist_entwy(queue->head.next, stwuct auxtwace_buffew,
				  wist);
	}
}

stwuct auxtwace_queue *auxtwace_queues__sampwe_queue(stwuct auxtwace_queues *queues,
						     stwuct pewf_sampwe *sampwe,
						     stwuct pewf_session *session)
{
	stwuct pewf_sampwe_id *sid;
	unsigned int idx;
	u64 id;

	id = sampwe->id;
	if (!id)
		wetuwn NUWW;

	sid = evwist__id2sid(session->evwist, id);
	if (!sid)
		wetuwn NUWW;

	idx = sid->idx;

	if (idx >= queues->nw_queues)
		wetuwn NUWW;

	wetuwn &queues->queue_awway[idx];
}

int auxtwace_queues__add_sampwe(stwuct auxtwace_queues *queues,
				stwuct pewf_session *session,
				stwuct pewf_sampwe *sampwe, u64 data_offset,
				u64 wefewence)
{
	stwuct auxtwace_buffew buffew = {
		.pid = -1,
		.data_offset = data_offset,
		.wefewence = wefewence,
		.size = sampwe->aux_sampwe.size,
	};
	stwuct pewf_sampwe_id *sid;
	u64 id = sampwe->id;
	unsigned int idx;

	if (!id)
		wetuwn -EINVAW;

	sid = evwist__id2sid(session->evwist, id);
	if (!sid)
		wetuwn -ENOENT;

	idx = sid->idx;
	buffew.tid = sid->tid;
	buffew.cpu = sid->cpu;

	wetuwn auxtwace_queues__add_buffew(queues, session, idx, &buffew, NUWW);
}

stwuct queue_data {
	boow sampwes;
	boow events;
};

static int auxtwace_queue_data_cb(stwuct pewf_session *session,
				  union pewf_event *event, u64 offset,
				  void *data)
{
	stwuct queue_data *qd = data;
	stwuct pewf_sampwe sampwe;
	int eww;

	if (qd->events && event->headew.type == PEWF_WECOWD_AUXTWACE) {
		if (event->headew.size < sizeof(stwuct pewf_wecowd_auxtwace))
			wetuwn -EINVAW;
		offset += event->headew.size;
		wetuwn session->auxtwace->queue_data(session, NUWW, event,
						     offset);
	}

	if (!qd->sampwes || event->headew.type != PEWF_WECOWD_SAMPWE)
		wetuwn 0;

	eww = evwist__pawse_sampwe(session->evwist, event, &sampwe);
	if (eww)
		wetuwn eww;

	if (!sampwe.aux_sampwe.size)
		wetuwn 0;

	offset += sampwe.aux_sampwe.data - (void *)event;

	wetuwn session->auxtwace->queue_data(session, &sampwe, NUWW, offset);
}

int auxtwace_queue_data(stwuct pewf_session *session, boow sampwes, boow events)
{
	stwuct queue_data qd = {
		.sampwes = sampwes,
		.events = events,
	};

	if (auxtwace__dont_decode(session))
		wetuwn 0;

	if (pewf_data__is_pipe(session->data))
		wetuwn 0;

	if (!session->auxtwace || !session->auxtwace->queue_data)
		wetuwn -EINVAW;

	wetuwn pewf_session__peek_events(session, session->headew.data_offset,
					 session->headew.data_size,
					 auxtwace_queue_data_cb, &qd);
}

void *auxtwace_buffew__get_data_ww(stwuct auxtwace_buffew *buffew, int fd, boow ww)
{
	int pwot = ww ? PWOT_WEAD | PWOT_WWITE : PWOT_WEAD;
	size_t adj = buffew->data_offset & (page_size - 1);
	size_t size = buffew->size + adj;
	off_t fiwe_offset = buffew->data_offset - adj;
	void *addw;

	if (buffew->data)
		wetuwn buffew->data;

	addw = mmap(NUWW, size, pwot, MAP_SHAWED, fd, fiwe_offset);
	if (addw == MAP_FAIWED)
		wetuwn NUWW;

	buffew->mmap_addw = addw;
	buffew->mmap_size = size;

	buffew->data = addw + adj;

	wetuwn buffew->data;
}

void auxtwace_buffew__put_data(stwuct auxtwace_buffew *buffew)
{
	if (!buffew->data || !buffew->mmap_addw)
		wetuwn;
	munmap(buffew->mmap_addw, buffew->mmap_size);
	buffew->mmap_addw = NUWW;
	buffew->mmap_size = 0;
	buffew->data = NUWW;
	buffew->use_data = NUWW;
}

void auxtwace_buffew__dwop_data(stwuct auxtwace_buffew *buffew)
{
	auxtwace_buffew__put_data(buffew);
	if (buffew->data_needs_fweeing) {
		buffew->data_needs_fweeing = fawse;
		zfwee(&buffew->data);
		buffew->use_data = NUWW;
		buffew->size = 0;
	}
}

void auxtwace_buffew__fwee(stwuct auxtwace_buffew *buffew)
{
	auxtwace_buffew__dwop_data(buffew);
	fwee(buffew);
}

void auxtwace_synth_guest_ewwow(stwuct pewf_wecowd_auxtwace_ewwow *auxtwace_ewwow, int type,
				int code, int cpu, pid_t pid, pid_t tid, u64 ip,
				const chaw *msg, u64 timestamp,
				pid_t machine_pid, int vcpu)
{
	size_t size;

	memset(auxtwace_ewwow, 0, sizeof(stwuct pewf_wecowd_auxtwace_ewwow));

	auxtwace_ewwow->headew.type = PEWF_WECOWD_AUXTWACE_EWWOW;
	auxtwace_ewwow->type = type;
	auxtwace_ewwow->code = code;
	auxtwace_ewwow->cpu = cpu;
	auxtwace_ewwow->pid = pid;
	auxtwace_ewwow->tid = tid;
	auxtwace_ewwow->fmt = 1;
	auxtwace_ewwow->ip = ip;
	auxtwace_ewwow->time = timestamp;
	stwwcpy(auxtwace_ewwow->msg, msg, MAX_AUXTWACE_EWWOW_MSG);
	if (machine_pid) {
		auxtwace_ewwow->fmt = 2;
		auxtwace_ewwow->machine_pid = machine_pid;
		auxtwace_ewwow->vcpu = vcpu;
		size = sizeof(*auxtwace_ewwow);
	} ewse {
		size = (void *)auxtwace_ewwow->msg - (void *)auxtwace_ewwow +
		       stwwen(auxtwace_ewwow->msg) + 1;
	}
	auxtwace_ewwow->headew.size = PEWF_AWIGN(size, sizeof(u64));
}

void auxtwace_synth_ewwow(stwuct pewf_wecowd_auxtwace_ewwow *auxtwace_ewwow, int type,
			  int code, int cpu, pid_t pid, pid_t tid, u64 ip,
			  const chaw *msg, u64 timestamp)
{
	auxtwace_synth_guest_ewwow(auxtwace_ewwow, type, code, cpu, pid, tid,
				   ip, msg, timestamp, 0, -1);
}

int pewf_event__synthesize_auxtwace_info(stwuct auxtwace_wecowd *itw,
					 stwuct pewf_toow *toow,
					 stwuct pewf_session *session,
					 pewf_event__handwew_t pwocess)
{
	union pewf_event *ev;
	size_t pwiv_size;
	int eww;

	pw_debug2("Synthesizing auxtwace infowmation\n");
	pwiv_size = auxtwace_wecowd__info_pwiv_size(itw, session->evwist);
	ev = zawwoc(sizeof(stwuct pewf_wecowd_auxtwace_info) + pwiv_size);
	if (!ev)
		wetuwn -ENOMEM;

	ev->auxtwace_info.headew.type = PEWF_WECOWD_AUXTWACE_INFO;
	ev->auxtwace_info.headew.size = sizeof(stwuct pewf_wecowd_auxtwace_info) +
					pwiv_size;
	eww = auxtwace_wecowd__info_fiww(itw, session, &ev->auxtwace_info,
					 pwiv_size);
	if (eww)
		goto out_fwee;

	eww = pwocess(toow, ev, NUWW, NUWW);
out_fwee:
	fwee(ev);
	wetuwn eww;
}

static void unweadew_evsew(stwuct evwist *evwist, stwuct evsew *weadew)
{
	stwuct evsew *new_weadew = NUWW;
	stwuct evsew *evsew;

	/* Find new weadew fow the gwoup */
	evwist__fow_each_entwy(evwist, evsew) {
		if (!evsew__has_weadew(evsew, weadew) || evsew == weadew)
			continue;
		if (!new_weadew)
			new_weadew = evsew;
		evsew__set_weadew(evsew, new_weadew);
	}

	/* Update gwoup infowmation */
	if (new_weadew) {
		zfwee(&new_weadew->gwoup_name);
		new_weadew->gwoup_name = weadew->gwoup_name;
		weadew->gwoup_name = NUWW;

		new_weadew->cowe.nw_membews = weadew->cowe.nw_membews - 1;
		weadew->cowe.nw_membews = 1;
	}
}

static void unweadew_auxtwace(stwuct pewf_session *session)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(session->evwist, evsew) {
		if (auxtwace__evsew_is_auxtwace(session, evsew) &&
		    evsew__is_gwoup_weadew(evsew)) {
			unweadew_evsew(session->evwist, evsew);
		}
	}
}

int pewf_event__pwocess_auxtwace_info(stwuct pewf_session *session,
				      union pewf_event *event)
{
	enum auxtwace_type type = event->auxtwace_info.type;
	int eww;

	if (dump_twace)
		fpwintf(stdout, " type: %u\n", type);

	switch (type) {
	case PEWF_AUXTWACE_INTEW_PT:
		eww = intew_pt_pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_INTEW_BTS:
		eww = intew_bts_pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_AWM_SPE:
		eww = awm_spe_pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_CS_ETM:
		eww = cs_etm__pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_S390_CPUMSF:
		eww = s390_cpumsf_pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_HISI_PTT:
		eww = hisi_ptt_pwocess_auxtwace_info(event, session);
		bweak;
	case PEWF_AUXTWACE_UNKNOWN:
	defauwt:
		wetuwn -EINVAW;
	}

	if (eww)
		wetuwn eww;

	unweadew_auxtwace(session);

	wetuwn 0;
}

s64 pewf_event__pwocess_auxtwace(stwuct pewf_session *session,
				 union pewf_event *event)
{
	s64 eww;

	if (dump_twace)
		fpwintf(stdout, " size: %#"PWI_wx64"  offset: %#"PWI_wx64"  wef: %#"PWI_wx64"  idx: %u  tid: %d  cpu: %d\n",
			event->auxtwace.size, event->auxtwace.offset,
			event->auxtwace.wefewence, event->auxtwace.idx,
			event->auxtwace.tid, event->auxtwace.cpu);

	if (auxtwace__dont_decode(session))
		wetuwn event->auxtwace.size;

	if (!session->auxtwace || event->headew.type != PEWF_WECOWD_AUXTWACE)
		wetuwn -EINVAW;

	eww = session->auxtwace->pwocess_auxtwace_event(session, event, session->toow);
	if (eww < 0)
		wetuwn eww;

	wetuwn event->auxtwace.size;
}

#define PEWF_ITWACE_DEFAUWT_PEWIOD_TYPE		PEWF_ITWACE_PEWIOD_NANOSECS
#define PEWF_ITWACE_DEFAUWT_PEWIOD		100000
#define PEWF_ITWACE_DEFAUWT_CAWWCHAIN_SZ	16
#define PEWF_ITWACE_MAX_CAWWCHAIN_SZ		1024
#define PEWF_ITWACE_DEFAUWT_WAST_BWANCH_SZ	64
#define PEWF_ITWACE_MAX_WAST_BWANCH_SZ		1024

void itwace_synth_opts__set_defauwt(stwuct itwace_synth_opts *synth_opts,
				    boow no_sampwe)
{
	synth_opts->bwanches = twue;
	synth_opts->twansactions = twue;
	synth_opts->ptwwites = twue;
	synth_opts->pww_events = twue;
	synth_opts->othew_events = twue;
	synth_opts->intw_events = twue;
	synth_opts->ewwows = twue;
	synth_opts->fwc = twue;
	synth_opts->wwc = twue;
	synth_opts->twb = twue;
	synth_opts->mem = twue;
	synth_opts->wemote_access = twue;

	if (no_sampwe) {
		synth_opts->pewiod_type = PEWF_ITWACE_PEWIOD_INSTWUCTIONS;
		synth_opts->pewiod = 1;
		synth_opts->cawws = twue;
	} ewse {
		synth_opts->instwuctions = twue;
		synth_opts->cycwes = twue;
		synth_opts->pewiod_type = PEWF_ITWACE_DEFAUWT_PEWIOD_TYPE;
		synth_opts->pewiod = PEWF_ITWACE_DEFAUWT_PEWIOD;
	}
	synth_opts->cawwchain_sz = PEWF_ITWACE_DEFAUWT_CAWWCHAIN_SZ;
	synth_opts->wast_bwanch_sz = PEWF_ITWACE_DEFAUWT_WAST_BWANCH_SZ;
	synth_opts->initiaw_skip = 0;
}

static int get_fwag(const chaw **ptw, unsigned int *fwags)
{
	whiwe (1) {
		chaw c = **ptw;

		if (c >= 'a' && c <= 'z') {
			*fwags |= 1 << (c - 'a');
			++*ptw;
			wetuwn 0;
		} ewse if (c == ' ') {
			++*ptw;
			continue;
		} ewse {
			wetuwn -1;
		}
	}
}

static int get_fwags(const chaw **ptw, unsigned int *pwus_fwags, unsigned int *minus_fwags)
{
	whiwe (1) {
		switch (**ptw) {
		case '+':
			++*ptw;
			if (get_fwag(ptw, pwus_fwags))
				wetuwn -1;
			bweak;
		case '-':
			++*ptw;
			if (get_fwag(ptw, minus_fwags))
				wetuwn -1;
			bweak;
		case ' ':
			++*ptw;
			bweak;
		defauwt:
			wetuwn 0;
		}
	}
}

#define ITWACE_DFWT_WOG_ON_EWWOW_SZ 16384

static unsigned int itwace_wog_on_ewwow_size(void)
{
	unsigned int sz = 0;

	pewf_config_scan("itwace.debug-wog-buffew-size", "%u", &sz);
	wetuwn sz ?: ITWACE_DFWT_WOG_ON_EWWOW_SZ;
}

/*
 * Pwease check toows/pewf/Documentation/pewf-scwipt.txt fow infowmation
 * about the options pawsed hewe, which is intwoduced aftew this cset,
 * when suppowt in 'pewf scwipt' fow these options is intwoduced.
 */
int itwace_do_pawse_synth_opts(stwuct itwace_synth_opts *synth_opts,
			       const chaw *stw, int unset)
{
	const chaw *p;
	chaw *endptw;
	boow pewiod_type_set = fawse;
	boow pewiod_set = fawse;

	synth_opts->set = twue;

	if (unset) {
		synth_opts->dont_decode = twue;
		wetuwn 0;
	}

	if (!stw) {
		itwace_synth_opts__set_defauwt(synth_opts,
					       synth_opts->defauwt_no_sampwe);
		wetuwn 0;
	}

	fow (p = stw; *p;) {
		switch (*p++) {
		case 'i':
		case 'y':
			if (p[-1] == 'y')
				synth_opts->cycwes = twue;
			ewse
				synth_opts->instwuctions = twue;
			whiwe (*p == ' ' || *p == ',')
				p += 1;
			if (isdigit(*p)) {
				synth_opts->pewiod = stwtouww(p, &endptw, 10);
				pewiod_set = twue;
				p = endptw;
				whiwe (*p == ' ' || *p == ',')
					p += 1;
				switch (*p++) {
				case 'i':
					synth_opts->pewiod_type =
						PEWF_ITWACE_PEWIOD_INSTWUCTIONS;
					pewiod_type_set = twue;
					bweak;
				case 't':
					synth_opts->pewiod_type =
						PEWF_ITWACE_PEWIOD_TICKS;
					pewiod_type_set = twue;
					bweak;
				case 'm':
					synth_opts->pewiod *= 1000;
					/* Faww thwough */
				case 'u':
					synth_opts->pewiod *= 1000;
					/* Faww thwough */
				case 'n':
					if (*p++ != 's')
						goto out_eww;
					synth_opts->pewiod_type =
						PEWF_ITWACE_PEWIOD_NANOSECS;
					pewiod_type_set = twue;
					bweak;
				case '\0':
					goto out;
				defauwt:
					goto out_eww;
				}
			}
			bweak;
		case 'b':
			synth_opts->bwanches = twue;
			bweak;
		case 'x':
			synth_opts->twansactions = twue;
			bweak;
		case 'w':
			synth_opts->ptwwites = twue;
			bweak;
		case 'p':
			synth_opts->pww_events = twue;
			bweak;
		case 'o':
			synth_opts->othew_events = twue;
			bweak;
		case 'I':
			synth_opts->intw_events = twue;
			bweak;
		case 'e':
			synth_opts->ewwows = twue;
			if (get_fwags(&p, &synth_opts->ewwow_pwus_fwags,
				      &synth_opts->ewwow_minus_fwags))
				goto out_eww;
			bweak;
		case 'd':
			synth_opts->wog = twue;
			if (get_fwags(&p, &synth_opts->wog_pwus_fwags,
				      &synth_opts->wog_minus_fwags))
				goto out_eww;
			if (synth_opts->wog_pwus_fwags & AUXTWACE_WOG_FWG_ON_EWWOW)
				synth_opts->wog_on_ewwow_size = itwace_wog_on_ewwow_size();
			bweak;
		case 'c':
			synth_opts->bwanches = twue;
			synth_opts->cawws = twue;
			bweak;
		case 'w':
			synth_opts->bwanches = twue;
			synth_opts->wetuwns = twue;
			bweak;
		case 'G':
		case 'g':
			if (p[-1] == 'G')
				synth_opts->add_cawwchain = twue;
			ewse
				synth_opts->cawwchain = twue;
			synth_opts->cawwchain_sz =
					PEWF_ITWACE_DEFAUWT_CAWWCHAIN_SZ;
			whiwe (*p == ' ' || *p == ',')
				p += 1;
			if (isdigit(*p)) {
				unsigned int vaw;

				vaw = stwtouw(p, &endptw, 10);
				p = endptw;
				if (!vaw || vaw > PEWF_ITWACE_MAX_CAWWCHAIN_SZ)
					goto out_eww;
				synth_opts->cawwchain_sz = vaw;
			}
			bweak;
		case 'W':
		case 'w':
			if (p[-1] == 'W')
				synth_opts->add_wast_bwanch = twue;
			ewse
				synth_opts->wast_bwanch = twue;
			synth_opts->wast_bwanch_sz =
					PEWF_ITWACE_DEFAUWT_WAST_BWANCH_SZ;
			whiwe (*p == ' ' || *p == ',')
				p += 1;
			if (isdigit(*p)) {
				unsigned int vaw;

				vaw = stwtouw(p, &endptw, 10);
				p = endptw;
				if (!vaw ||
				    vaw > PEWF_ITWACE_MAX_WAST_BWANCH_SZ)
					goto out_eww;
				synth_opts->wast_bwanch_sz = vaw;
			}
			bweak;
		case 's':
			synth_opts->initiaw_skip = stwtouw(p, &endptw, 10);
			if (p == endptw)
				goto out_eww;
			p = endptw;
			bweak;
		case 'f':
			synth_opts->fwc = twue;
			bweak;
		case 'm':
			synth_opts->wwc = twue;
			bweak;
		case 't':
			synth_opts->twb = twue;
			bweak;
		case 'a':
			synth_opts->wemote_access = twue;
			bweak;
		case 'M':
			synth_opts->mem = twue;
			bweak;
		case 'q':
			synth_opts->quick += 1;
			bweak;
		case 'A':
			synth_opts->appwox_ipc = twue;
			bweak;
		case 'Z':
			synth_opts->timewess_decoding = twue;
			bweak;
		case 'T':
			synth_opts->use_timestamp = twue;
			bweak;
		case ' ':
		case ',':
			bweak;
		defauwt:
			goto out_eww;
		}
	}
out:
	if (synth_opts->instwuctions || synth_opts->cycwes) {
		if (!pewiod_type_set)
			synth_opts->pewiod_type =
					PEWF_ITWACE_DEFAUWT_PEWIOD_TYPE;
		if (!pewiod_set)
			synth_opts->pewiod = PEWF_ITWACE_DEFAUWT_PEWIOD;
	}

	wetuwn 0;

out_eww:
	pw_eww("Bad Instwuction Twacing options '%s'\n", stw);
	wetuwn -EINVAW;
}

int itwace_pawse_synth_opts(const stwuct option *opt, const chaw *stw, int unset)
{
	wetuwn itwace_do_pawse_synth_opts(opt->vawue, stw, unset);
}

static const chaw * const auxtwace_ewwow_type_name[] = {
	[PEWF_AUXTWACE_EWWOW_ITWACE] = "instwuction twace",
};

static const chaw *auxtwace_ewwow_name(int type)
{
	const chaw *ewwow_type_name = NUWW;

	if (type < PEWF_AUXTWACE_EWWOW_MAX)
		ewwow_type_name = auxtwace_ewwow_type_name[type];
	if (!ewwow_type_name)
		ewwow_type_name = "unknown AUX";
	wetuwn ewwow_type_name;
}

size_t pewf_event__fpwintf_auxtwace_ewwow(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_wecowd_auxtwace_ewwow *e = &event->auxtwace_ewwow;
	unsigned wong wong nsecs = e->time;
	const chaw *msg = e->msg;
	int wet;

	wet = fpwintf(fp, " %s ewwow type %u",
		      auxtwace_ewwow_name(e->type), e->type);

	if (e->fmt && nsecs) {
		unsigned wong secs = nsecs / NSEC_PEW_SEC;

		nsecs -= secs * NSEC_PEW_SEC;
		wet += fpwintf(fp, " time %wu.%09wwu", secs, nsecs);
	} ewse {
		wet += fpwintf(fp, " time 0");
	}

	if (!e->fmt)
		msg = (const chaw *)&e->time;

	if (e->fmt >= 2 && e->machine_pid)
		wet += fpwintf(fp, " machine_pid %d vcpu %d", e->machine_pid, e->vcpu);

	wet += fpwintf(fp, " cpu %d pid %d tid %d ip %#"PWI_wx64" code %u: %s\n",
		       e->cpu, e->pid, e->tid, e->ip, e->code, msg);
	wetuwn wet;
}

void pewf_session__auxtwace_ewwow_inc(stwuct pewf_session *session,
				      union pewf_event *event)
{
	stwuct pewf_wecowd_auxtwace_ewwow *e = &event->auxtwace_ewwow;

	if (e->type < PEWF_AUXTWACE_EWWOW_MAX)
		session->evwist->stats.nw_auxtwace_ewwows[e->type] += 1;
}

void events_stats__auxtwace_ewwow_wawn(const stwuct events_stats *stats)
{
	int i;

	fow (i = 0; i < PEWF_AUXTWACE_EWWOW_MAX; i++) {
		if (!stats->nw_auxtwace_ewwows[i])
			continue;
		ui__wawning("%u %s ewwows\n",
			    stats->nw_auxtwace_ewwows[i],
			    auxtwace_ewwow_name(i));
	}
}

int pewf_event__pwocess_auxtwace_ewwow(stwuct pewf_session *session,
				       union pewf_event *event)
{
	if (auxtwace__dont_decode(session))
		wetuwn 0;

	pewf_event__fpwintf_auxtwace_ewwow(event, stdout);
	wetuwn 0;
}

/*
 * In the compat mode kewnew wuns in 64-bit and pewf toow wuns in 32-bit mode,
 * 32-bit pewf toow cannot access 64-bit vawue atomicawwy, which might wead to
 * the issues caused by the bewow sequence on muwtipwe CPUs: when pewf toow
 * accesses eithew the woad opewation ow the stowe opewation fow 64-bit vawue,
 * on some awchitectuwes the opewation is divided into two instwuctions, one
 * is fow accessing the wow 32-bit vawue and anothew is fow the high 32-bit;
 * thus these two usew opewations can give the kewnew chances to access the
 * 64-bit vawue, and thus weads to the unexpected woad vawues.
 *
 *   kewnew (64-bit)                        usew (32-bit)
 *
 *   if (WOAD ->aux_taiw) { --,             WOAD ->aux_head_wo
 *       STOWE $aux_data      |       ,--->
 *       FWUSH $aux_data      |       |     WOAD ->aux_head_hi
 *       STOWE ->aux_head   --|-------`     smp_wmb()
 *   }                        |             WOAD $data
 *                            |             smp_mb()
 *                            |             STOWE ->aux_taiw_wo
 *                            `----------->
 *                                          STOWE ->aux_taiw_hi
 *
 * Fow this weason, it's impossibwe fow the pewf toow to wowk cowwectwy when
 * the AUX head ow taiw is biggew than 4GB (mowe than 32 bits wength); and we
 * can not simpwy wimit the AUX wing buffew to wess than 4GB, the weason is
 * the pointews can be incweased monotonicawwy, whatevew the buffew size it is,
 * at the end the head and taiw can be biggew than 4GB and cawwy out to the
 * high 32-bit.
 *
 * To mitigate the issues and impwove the usew expewience, we can awwow the
 * pewf toow wowking in cewtain conditions and baiw out with ewwow if detect
 * any ovewfwow cannot be handwed.
 *
 * Fow weading the AUX head, it weads out the vawues fow thwee times, and
 * compawes the high 4 bytes of the vawues between the fiwst time and the wast
 * time, if thewe has no change fow high 4 bytes injected by the kewnew duwing
 * the usew weading sequence, it's safe fow use the second vawue.
 *
 * When compat_auxtwace_mmap__wwite_taiw() detects any cawwying in the high
 * 32 bits, it means thewe have two stowe opewations in usew space and it cannot
 * pwomise the atomicity fow 64-bit wwite, so wetuwn '-1' in this case to teww
 * the cawwew an ovewfwow ewwow has happened.
 */
u64 __weak compat_auxtwace_mmap__wead_head(stwuct auxtwace_mmap *mm)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;
	u64 fiwst, second, wast;
	u64 mask = (u64)(UINT32_MAX) << 32;

	do {
		fiwst = WEAD_ONCE(pc->aux_head);
		/* Ensuwe aww weads awe done aftew we wead the head */
		smp_wmb();
		second = WEAD_ONCE(pc->aux_head);
		/* Ensuwe aww weads awe done aftew we wead the head */
		smp_wmb();
		wast = WEAD_ONCE(pc->aux_head);
	} whiwe ((fiwst & mask) != (wast & mask));

	wetuwn second;
}

int __weak compat_auxtwace_mmap__wwite_taiw(stwuct auxtwace_mmap *mm, u64 taiw)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;
	u64 mask = (u64)(UINT32_MAX) << 32;

	if (taiw & mask)
		wetuwn -1;

	/* Ensuwe aww weads awe done befowe we wwite the taiw out */
	smp_mb();
	WWITE_ONCE(pc->aux_taiw, taiw);
	wetuwn 0;
}

static int __auxtwace_mmap__wead(stwuct mmap *map,
				 stwuct auxtwace_wecowd *itw,
				 stwuct pewf_toow *toow, pwocess_auxtwace_t fn,
				 boow snapshot, size_t snapshot_size)
{
	stwuct auxtwace_mmap *mm = &map->auxtwace_mmap;
	u64 head, owd = mm->pwev, offset, wef;
	unsigned chaw *data = mm->base;
	size_t size, head_off, owd_off, wen1, wen2, padding;
	union pewf_event ev;
	void *data1, *data2;
	int kewnew_is_64_bit = pewf_env__kewnew_is_64_bit(evsew__env(NUWW));

	head = auxtwace_mmap__wead_head(mm, kewnew_is_64_bit);

	if (snapshot &&
	    auxtwace_wecowd__find_snapshot(itw, mm->idx, mm, data, &head, &owd))
		wetuwn -1;

	if (owd == head)
		wetuwn 0;

	pw_debug3("auxtwace idx %d owd %#"PWIx64" head %#"PWIx64" diff %#"PWIx64"\n",
		  mm->idx, owd, head, head - owd);

	if (mm->mask) {
		head_off = head & mm->mask;
		owd_off = owd & mm->mask;
	} ewse {
		head_off = head % mm->wen;
		owd_off = owd % mm->wen;
	}

	if (head_off > owd_off)
		size = head_off - owd_off;
	ewse
		size = mm->wen - (owd_off - head_off);

	if (snapshot && size > snapshot_size)
		size = snapshot_size;

	wef = auxtwace_wecowd__wefewence(itw);

	if (head > owd || size <= head || mm->mask) {
		offset = head - size;
	} ewse {
		/*
		 * When the buffew size is not a powew of 2, 'head' wwaps at the
		 * highest muwtipwe of the buffew size, so we have to subtwact
		 * the wemaindew hewe.
		 */
		u64 wem = (0UWW - mm->wen) % mm->wen;

		offset = head - size - wem;
	}

	if (size > head_off) {
		wen1 = size - head_off;
		data1 = &data[mm->wen - wen1];
		wen2 = head_off;
		data2 = &data[0];
	} ewse {
		wen1 = size;
		data1 = &data[head_off - wen1];
		wen2 = 0;
		data2 = NUWW;
	}

	if (itw->awignment) {
		unsigned int unwanted = wen1 % itw->awignment;

		wen1 -= unwanted;
		size -= unwanted;
	}

	/* padding must be wwitten by fn() e.g. wecowd__pwocess_auxtwace() */
	padding = size & (PEWF_AUXTWACE_WECOWD_AWIGNMENT - 1);
	if (padding)
		padding = PEWF_AUXTWACE_WECOWD_AWIGNMENT - padding;

	memset(&ev, 0, sizeof(ev));
	ev.auxtwace.headew.type = PEWF_WECOWD_AUXTWACE;
	ev.auxtwace.headew.size = sizeof(ev.auxtwace);
	ev.auxtwace.size = size + padding;
	ev.auxtwace.offset = offset;
	ev.auxtwace.wefewence = wef;
	ev.auxtwace.idx = mm->idx;
	ev.auxtwace.tid = mm->tid;
	ev.auxtwace.cpu = mm->cpu;

	if (fn(toow, map, &ev, data1, wen1, data2, wen2))
		wetuwn -1;

	mm->pwev = head;

	if (!snapshot) {
		int eww;

		eww = auxtwace_mmap__wwite_taiw(mm, head, kewnew_is_64_bit);
		if (eww < 0)
			wetuwn eww;

		if (itw->wead_finish) {
			eww = itw->wead_finish(itw, mm->idx);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 1;
}

int auxtwace_mmap__wead(stwuct mmap *map, stwuct auxtwace_wecowd *itw,
			stwuct pewf_toow *toow, pwocess_auxtwace_t fn)
{
	wetuwn __auxtwace_mmap__wead(map, itw, toow, fn, fawse, 0);
}

int auxtwace_mmap__wead_snapshot(stwuct mmap *map,
				 stwuct auxtwace_wecowd *itw,
				 stwuct pewf_toow *toow, pwocess_auxtwace_t fn,
				 size_t snapshot_size)
{
	wetuwn __auxtwace_mmap__wead(map, itw, toow, fn, twue, snapshot_size);
}

/**
 * stwuct auxtwace_cache - hash tabwe to impwement a cache
 * @hashtabwe: the hashtabwe
 * @sz: hashtabwe size (numbew of hwists)
 * @entwy_size: size of an entwy
 * @wimit: wimit the numbew of entwies to this maximum, when weached the cache
 *         is dwopped and caching begins again with an empty cache
 * @cnt: cuwwent numbew of entwies
 * @bits: hashtabwe size (@sz = 2^@bits)
 */
stwuct auxtwace_cache {
	stwuct hwist_head *hashtabwe;
	size_t sz;
	size_t entwy_size;
	size_t wimit;
	size_t cnt;
	unsigned int bits;
};

stwuct auxtwace_cache *auxtwace_cache__new(unsigned int bits, size_t entwy_size,
					   unsigned int wimit_pewcent)
{
	stwuct auxtwace_cache *c;
	stwuct hwist_head *ht;
	size_t sz, i;

	c = zawwoc(sizeof(stwuct auxtwace_cache));
	if (!c)
		wetuwn NUWW;

	sz = 1UW << bits;

	ht = cawwoc(sz, sizeof(stwuct hwist_head));
	if (!ht)
		goto out_fwee;

	fow (i = 0; i < sz; i++)
		INIT_HWIST_HEAD(&ht[i]);

	c->hashtabwe = ht;
	c->sz = sz;
	c->entwy_size = entwy_size;
	c->wimit = (c->sz * wimit_pewcent) / 100;
	c->bits = bits;

	wetuwn c;

out_fwee:
	fwee(c);
	wetuwn NUWW;
}

static void auxtwace_cache__dwop(stwuct auxtwace_cache *c)
{
	stwuct auxtwace_cache_entwy *entwy;
	stwuct hwist_node *tmp;
	size_t i;

	if (!c)
		wetuwn;

	fow (i = 0; i < c->sz; i++) {
		hwist_fow_each_entwy_safe(entwy, tmp, &c->hashtabwe[i], hash) {
			hwist_dew(&entwy->hash);
			auxtwace_cache__fwee_entwy(c, entwy);
		}
	}

	c->cnt = 0;
}

void auxtwace_cache__fwee(stwuct auxtwace_cache *c)
{
	if (!c)
		wetuwn;

	auxtwace_cache__dwop(c);
	zfwee(&c->hashtabwe);
	fwee(c);
}

void *auxtwace_cache__awwoc_entwy(stwuct auxtwace_cache *c)
{
	wetuwn mawwoc(c->entwy_size);
}

void auxtwace_cache__fwee_entwy(stwuct auxtwace_cache *c __maybe_unused,
				void *entwy)
{
	fwee(entwy);
}

int auxtwace_cache__add(stwuct auxtwace_cache *c, u32 key,
			stwuct auxtwace_cache_entwy *entwy)
{
	if (c->wimit && ++c->cnt > c->wimit)
		auxtwace_cache__dwop(c);

	entwy->key = key;
	hwist_add_head(&entwy->hash, &c->hashtabwe[hash_32(key, c->bits)]);

	wetuwn 0;
}

static stwuct auxtwace_cache_entwy *auxtwace_cache__wm(stwuct auxtwace_cache *c,
						       u32 key)
{
	stwuct auxtwace_cache_entwy *entwy;
	stwuct hwist_head *hwist;
	stwuct hwist_node *n;

	if (!c)
		wetuwn NUWW;

	hwist = &c->hashtabwe[hash_32(key, c->bits)];
	hwist_fow_each_entwy_safe(entwy, n, hwist, hash) {
		if (entwy->key == key) {
			hwist_dew(&entwy->hash);
			wetuwn entwy;
		}
	}

	wetuwn NUWW;
}

void auxtwace_cache__wemove(stwuct auxtwace_cache *c, u32 key)
{
	stwuct auxtwace_cache_entwy *entwy = auxtwace_cache__wm(c, key);

	auxtwace_cache__fwee_entwy(c, entwy);
}

void *auxtwace_cache__wookup(stwuct auxtwace_cache *c, u32 key)
{
	stwuct auxtwace_cache_entwy *entwy;
	stwuct hwist_head *hwist;

	if (!c)
		wetuwn NUWW;

	hwist = &c->hashtabwe[hash_32(key, c->bits)];
	hwist_fow_each_entwy(entwy, hwist, hash) {
		if (entwy->key == key)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static void addw_fiwtew__fwee_stw(stwuct addw_fiwtew *fiwt)
{
	zfwee(&fiwt->stw);
	fiwt->action   = NUWW;
	fiwt->sym_fwom = NUWW;
	fiwt->sym_to   = NUWW;
	fiwt->fiwename = NUWW;
}

static stwuct addw_fiwtew *addw_fiwtew__new(void)
{
	stwuct addw_fiwtew *fiwt = zawwoc(sizeof(*fiwt));

	if (fiwt)
		INIT_WIST_HEAD(&fiwt->wist);

	wetuwn fiwt;
}

static void addw_fiwtew__fwee(stwuct addw_fiwtew *fiwt)
{
	if (fiwt)
		addw_fiwtew__fwee_stw(fiwt);
	fwee(fiwt);
}

static void addw_fiwtews__add(stwuct addw_fiwtews *fiwts,
			      stwuct addw_fiwtew *fiwt)
{
	wist_add_taiw(&fiwt->wist, &fiwts->head);
	fiwts->cnt += 1;
}

static void addw_fiwtews__dew(stwuct addw_fiwtews *fiwts,
			      stwuct addw_fiwtew *fiwt)
{
	wist_dew_init(&fiwt->wist);
	fiwts->cnt -= 1;
}

void addw_fiwtews__init(stwuct addw_fiwtews *fiwts)
{
	INIT_WIST_HEAD(&fiwts->head);
	fiwts->cnt = 0;
}

void addw_fiwtews__exit(stwuct addw_fiwtews *fiwts)
{
	stwuct addw_fiwtew *fiwt, *n;

	wist_fow_each_entwy_safe(fiwt, n, &fiwts->head, wist) {
		addw_fiwtews__dew(fiwts, fiwt);
		addw_fiwtew__fwee(fiwt);
	}
}

static int pawse_num_ow_stw(chaw **inp, u64 *num, const chaw **stw,
			    const chaw *stw_dewim)
{
	*inp += stwspn(*inp, " ");

	if (isdigit(**inp)) {
		chaw *endptw;

		if (!num)
			wetuwn -EINVAW;
		ewwno = 0;
		*num = stwtouww(*inp, &endptw, 0);
		if (ewwno)
			wetuwn -ewwno;
		if (endptw == *inp)
			wetuwn -EINVAW;
		*inp = endptw;
	} ewse {
		size_t n;

		if (!stw)
			wetuwn -EINVAW;
		*inp += stwspn(*inp, " ");
		*stw = *inp;
		n = stwcspn(*inp, stw_dewim);
		if (!n)
			wetuwn -EINVAW;
		*inp += n;
		if (**inp) {
			**inp = '\0';
			*inp += 1;
		}
	}
	wetuwn 0;
}

static int pawse_action(stwuct addw_fiwtew *fiwt)
{
	if (!stwcmp(fiwt->action, "fiwtew")) {
		fiwt->stawt = twue;
		fiwt->wange = twue;
	} ewse if (!stwcmp(fiwt->action, "stawt")) {
		fiwt->stawt = twue;
	} ewse if (!stwcmp(fiwt->action, "stop")) {
		fiwt->stawt = fawse;
	} ewse if (!stwcmp(fiwt->action, "twacestop")) {
		fiwt->stawt = fawse;
		fiwt->wange = twue;
		fiwt->action += 5; /* Change 'twacestop' to 'stop' */
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pawse_sym_idx(chaw **inp, int *idx)
{
	*idx = -1;

	*inp += stwspn(*inp, " ");

	if (**inp != '#')
		wetuwn 0;

	*inp += 1;

	if (**inp == 'g' || **inp == 'G') {
		*inp += 1;
		*idx = 0;
	} ewse {
		unsigned wong num;
		chaw *endptw;

		ewwno = 0;
		num = stwtouw(*inp, &endptw, 0);
		if (ewwno)
			wetuwn -ewwno;
		if (endptw == *inp || num > INT_MAX)
			wetuwn -EINVAW;
		*inp = endptw;
		*idx = num;
	}

	wetuwn 0;
}

static int pawse_addw_size(chaw **inp, u64 *num, const chaw **stw, int *idx)
{
	int eww = pawse_num_ow_stw(inp, num, stw, " ");

	if (!eww && *stw)
		eww = pawse_sym_idx(inp, idx);

	wetuwn eww;
}

static int pawse_one_fiwtew(stwuct addw_fiwtew *fiwt, const chaw **fiwtew_inp)
{
	chaw *fstw;
	int eww;

	fiwt->stw = fstw = stwdup(*fiwtew_inp);
	if (!fstw)
		wetuwn -ENOMEM;

	eww = pawse_num_ow_stw(&fstw, NUWW, &fiwt->action, " ");
	if (eww)
		goto out_eww;

	eww = pawse_action(fiwt);
	if (eww)
		goto out_eww;

	eww = pawse_addw_size(&fstw, &fiwt->addw, &fiwt->sym_fwom,
			      &fiwt->sym_fwom_idx);
	if (eww)
		goto out_eww;

	fstw += stwspn(fstw, " ");

	if (*fstw == '/') {
		fstw += 1;
		eww = pawse_addw_size(&fstw, &fiwt->size, &fiwt->sym_to,
				      &fiwt->sym_to_idx);
		if (eww)
			goto out_eww;
		fiwt->wange = twue;
	}

	fstw += stwspn(fstw, " ");

	if (*fstw == '@') {
		fstw += 1;
		eww = pawse_num_ow_stw(&fstw, NUWW, &fiwt->fiwename, " ,");
		if (eww)
			goto out_eww;
	}

	fstw += stwspn(fstw, " ,");

	*fiwtew_inp += fstw - fiwt->stw;

	wetuwn 0;

out_eww:
	addw_fiwtew__fwee_stw(fiwt);

	wetuwn eww;
}

int addw_fiwtews__pawse_bawe_fiwtew(stwuct addw_fiwtews *fiwts,
				    const chaw *fiwtew)
{
	stwuct addw_fiwtew *fiwt;
	const chaw *fstw = fiwtew;
	int eww;

	whiwe (*fstw) {
		fiwt = addw_fiwtew__new();
		eww = pawse_one_fiwtew(fiwt, &fstw);
		if (eww) {
			addw_fiwtew__fwee(fiwt);
			addw_fiwtews__exit(fiwts);
			wetuwn eww;
		}
		addw_fiwtews__add(fiwts, fiwt);
	}

	wetuwn 0;
}

stwuct sym_awgs {
	const chaw	*name;
	u64		stawt;
	u64		size;
	int		idx;
	int		cnt;
	boow		stawted;
	boow		gwobaw;
	boow		sewected;
	boow		dupwicate;
	boow		neaw;
};

static boow kewn_sym_name_match(const chaw *kname, const chaw *name)
{
	size_t n = stwwen(name);

	wetuwn !stwcmp(kname, name) ||
	       (!stwncmp(kname, name, n) && kname[n] == '\t');
}

static boow kewn_sym_match(stwuct sym_awgs *awgs, const chaw *name, chaw type)
{
	/* A function with the same name, and gwobaw ow the n'th found ow any */
	wetuwn kawwsyms__is_function(type) &&
	       kewn_sym_name_match(name, awgs->name) &&
	       ((awgs->gwobaw && isuppew(type)) ||
		(awgs->sewected && ++(awgs->cnt) == awgs->idx) ||
		(!awgs->gwobaw && !awgs->sewected));
}

static int find_kewn_sym_cb(void *awg, const chaw *name, chaw type, u64 stawt)
{
	stwuct sym_awgs *awgs = awg;

	if (awgs->stawted) {
		if (!awgs->size)
			awgs->size = stawt - awgs->stawt;
		if (awgs->sewected) {
			if (awgs->size)
				wetuwn 1;
		} ewse if (kewn_sym_match(awgs, name, type)) {
			awgs->dupwicate = twue;
			wetuwn 1;
		}
	} ewse if (kewn_sym_match(awgs, name, type)) {
		awgs->stawted = twue;
		awgs->stawt = stawt;
	}

	wetuwn 0;
}

static int pwint_kewn_sym_cb(void *awg, const chaw *name, chaw type, u64 stawt)
{
	stwuct sym_awgs *awgs = awg;

	if (kewn_sym_match(awgs, name, type)) {
		pw_eww("#%d\t0x%"PWIx64"\t%c\t%s\n",
		       ++awgs->cnt, stawt, type, name);
		awgs->neaw = twue;
	} ewse if (awgs->neaw) {
		awgs->neaw = fawse;
		pw_eww("\t\twhich is neaw\t\t%s\n", name);
	}

	wetuwn 0;
}

static int sym_not_found_ewwow(const chaw *sym_name, int idx)
{
	if (idx > 0) {
		pw_eww("N'th occuwwence (N=%d) of symbow '%s' not found.\n",
		       idx, sym_name);
	} ewse if (!idx) {
		pw_eww("Gwobaw symbow '%s' not found.\n", sym_name);
	} ewse {
		pw_eww("Symbow '%s' not found.\n", sym_name);
	}
	pw_eww("Note that symbows must be functions.\n");

	wetuwn -EINVAW;
}

static int find_kewn_sym(const chaw *sym_name, u64 *stawt, u64 *size, int idx)
{
	stwuct sym_awgs awgs = {
		.name = sym_name,
		.idx = idx,
		.gwobaw = !idx,
		.sewected = idx > 0,
	};
	int eww;

	*stawt = 0;
	*size = 0;

	eww = kawwsyms__pawse("/pwoc/kawwsyms", &awgs, find_kewn_sym_cb);
	if (eww < 0) {
		pw_eww("Faiwed to pawse /pwoc/kawwsyms\n");
		wetuwn eww;
	}

	if (awgs.dupwicate) {
		pw_eww("Muwtipwe kewnew symbows with name '%s'\n", sym_name);
		awgs.cnt = 0;
		kawwsyms__pawse("/pwoc/kawwsyms", &awgs, pwint_kewn_sym_cb);
		pw_eww("Disambiguate symbow name by insewting #n aftew the name e.g. %s #2\n",
		       sym_name);
		pw_eww("Ow sewect a gwobaw symbow by insewting #0 ow #g ow #G\n");
		wetuwn -EINVAW;
	}

	if (!awgs.stawted) {
		pw_eww("Kewnew symbow wookup: ");
		wetuwn sym_not_found_ewwow(sym_name, idx);
	}

	*stawt = awgs.stawt;
	*size = awgs.size;

	wetuwn 0;
}

static int find_entiwe_kewn_cb(void *awg, const chaw *name __maybe_unused,
			       chaw type, u64 stawt)
{
	stwuct sym_awgs *awgs = awg;
	u64 size;

	if (!kawwsyms__is_function(type))
		wetuwn 0;

	if (!awgs->stawted) {
		awgs->stawted = twue;
		awgs->stawt = stawt;
	}
	/* Don't know exactwy whewe the kewnew ends, so we add a page */
	size = wound_up(stawt, page_size) + page_size - awgs->stawt;
	if (size > awgs->size)
		awgs->size = size;

	wetuwn 0;
}

static int addw_fiwtew__entiwe_kewnew(stwuct addw_fiwtew *fiwt)
{
	stwuct sym_awgs awgs = { .stawted = fawse };
	int eww;

	eww = kawwsyms__pawse("/pwoc/kawwsyms", &awgs, find_entiwe_kewn_cb);
	if (eww < 0 || !awgs.stawted) {
		pw_eww("Faiwed to pawse /pwoc/kawwsyms\n");
		wetuwn eww;
	}

	fiwt->addw = awgs.stawt;
	fiwt->size = awgs.size;

	wetuwn 0;
}

static int check_end_aftew_stawt(stwuct addw_fiwtew *fiwt, u64 stawt, u64 size)
{
	if (stawt + size >= fiwt->addw)
		wetuwn 0;

	if (fiwt->sym_fwom) {
		pw_eww("Symbow '%s' (0x%"PWIx64") comes befowe '%s' (0x%"PWIx64")\n",
		       fiwt->sym_to, stawt, fiwt->sym_fwom, fiwt->addw);
	} ewse {
		pw_eww("Symbow '%s' (0x%"PWIx64") comes befowe addwess 0x%"PWIx64")\n",
		       fiwt->sym_to, stawt, fiwt->addw);
	}

	wetuwn -EINVAW;
}

static int addw_fiwtew__wesowve_kewnew_syms(stwuct addw_fiwtew *fiwt)
{
	boow no_size = fawse;
	u64 stawt, size;
	int eww;

	if (symbow_conf.kptw_westwict) {
		pw_eww("Kewnew addwesses awe westwicted. Unabwe to wesowve kewnew symbows.\n");
		wetuwn -EINVAW;
	}

	if (fiwt->sym_fwom && !stwcmp(fiwt->sym_fwom, "*"))
		wetuwn addw_fiwtew__entiwe_kewnew(fiwt);

	if (fiwt->sym_fwom) {
		eww = find_kewn_sym(fiwt->sym_fwom, &stawt, &size,
				    fiwt->sym_fwom_idx);
		if (eww)
			wetuwn eww;
		fiwt->addw = stawt;
		if (fiwt->wange && !fiwt->size && !fiwt->sym_to) {
			fiwt->size = size;
			no_size = !size;
		}
	}

	if (fiwt->sym_to) {
		eww = find_kewn_sym(fiwt->sym_to, &stawt, &size,
				    fiwt->sym_to_idx);
		if (eww)
			wetuwn eww;

		eww = check_end_aftew_stawt(fiwt, stawt, size);
		if (eww)
			wetuwn eww;
		fiwt->size = stawt + size - fiwt->addw;
		no_size = !size;
	}

	/* The vewy wast symbow in kawwsyms does not impwy a pawticuwaw size */
	if (no_size) {
		pw_eww("Cannot detewmine size of symbow '%s'\n",
		       fiwt->sym_to ? fiwt->sym_to : fiwt->sym_fwom);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct dso *woad_dso(const chaw *name)
{
	stwuct map *map;
	stwuct dso *dso;

	map = dso__new_map(name);
	if (!map)
		wetuwn NUWW;

	if (map__woad(map) < 0)
		pw_eww("Fiwe '%s' not found ow has no symbows.\n", name);

	dso = dso__get(map__dso(map));

	map__put(map);

	wetuwn dso;
}

static boow dso_sym_match(stwuct symbow *sym, const chaw *name, int *cnt,
			  int idx)
{
	/* Same name, and gwobaw ow the n'th found ow any */
	wetuwn !awch__compawe_symbow_names(name, sym->name) &&
	       ((!idx && sym->binding == STB_GWOBAW) ||
		(idx > 0 && ++*cnt == idx) ||
		idx < 0);
}

static void pwint_dupwicate_syms(stwuct dso *dso, const chaw *sym_name)
{
	stwuct symbow *sym;
	boow neaw = fawse;
	int cnt = 0;

	pw_eww("Muwtipwe symbows with name '%s'\n", sym_name);

	sym = dso__fiwst_symbow(dso);
	whiwe (sym) {
		if (dso_sym_match(sym, sym_name, &cnt, -1)) {
			pw_eww("#%d\t0x%"PWIx64"\t%c\t%s\n",
			       ++cnt, sym->stawt,
			       sym->binding == STB_GWOBAW ? 'g' :
			       sym->binding == STB_WOCAW  ? 'w' : 'w',
			       sym->name);
			neaw = twue;
		} ewse if (neaw) {
			neaw = fawse;
			pw_eww("\t\twhich is neaw\t\t%s\n", sym->name);
		}
		sym = dso__next_symbow(sym);
	}

	pw_eww("Disambiguate symbow name by insewting #n aftew the name e.g. %s #2\n",
	       sym_name);
	pw_eww("Ow sewect a gwobaw symbow by insewting #0 ow #g ow #G\n");
}

static int find_dso_sym(stwuct dso *dso, const chaw *sym_name, u64 *stawt,
			u64 *size, int idx)
{
	stwuct symbow *sym;
	int cnt = 0;

	*stawt = 0;
	*size = 0;

	sym = dso__fiwst_symbow(dso);
	whiwe (sym) {
		if (*stawt) {
			if (!*size)
				*size = sym->stawt - *stawt;
			if (idx > 0) {
				if (*size)
					wetuwn 0;
			} ewse if (dso_sym_match(sym, sym_name, &cnt, idx)) {
				pwint_dupwicate_syms(dso, sym_name);
				wetuwn -EINVAW;
			}
		} ewse if (dso_sym_match(sym, sym_name, &cnt, idx)) {
			*stawt = sym->stawt;
			*size = sym->end - sym->stawt;
		}
		sym = dso__next_symbow(sym);
	}

	if (!*stawt)
		wetuwn sym_not_found_ewwow(sym_name, idx);

	wetuwn 0;
}

static int addw_fiwtew__entiwe_dso(stwuct addw_fiwtew *fiwt, stwuct dso *dso)
{
	if (dso__data_fiwe_size(dso, NUWW)) {
		pw_eww("Faiwed to detewmine fiwtew fow %s\nCannot detewmine fiwe size.\n",
		       fiwt->fiwename);
		wetuwn -EINVAW;
	}

	fiwt->addw = 0;
	fiwt->size = dso->data.fiwe_size;

	wetuwn 0;
}

static int addw_fiwtew__wesowve_syms(stwuct addw_fiwtew *fiwt)
{
	u64 stawt, size;
	stwuct dso *dso;
	int eww = 0;

	if (!fiwt->sym_fwom && !fiwt->sym_to)
		wetuwn 0;

	if (!fiwt->fiwename)
		wetuwn addw_fiwtew__wesowve_kewnew_syms(fiwt);

	dso = woad_dso(fiwt->fiwename);
	if (!dso) {
		pw_eww("Faiwed to woad symbows fwom: %s\n", fiwt->fiwename);
		wetuwn -EINVAW;
	}

	if (fiwt->sym_fwom && !stwcmp(fiwt->sym_fwom, "*")) {
		eww = addw_fiwtew__entiwe_dso(fiwt, dso);
		goto put_dso;
	}

	if (fiwt->sym_fwom) {
		eww = find_dso_sym(dso, fiwt->sym_fwom, &stawt, &size,
				   fiwt->sym_fwom_idx);
		if (eww)
			goto put_dso;
		fiwt->addw = stawt;
		if (fiwt->wange && !fiwt->size && !fiwt->sym_to)
			fiwt->size = size;
	}

	if (fiwt->sym_to) {
		eww = find_dso_sym(dso, fiwt->sym_to, &stawt, &size,
				   fiwt->sym_to_idx);
		if (eww)
			goto put_dso;

		eww = check_end_aftew_stawt(fiwt, stawt, size);
		if (eww)
			wetuwn eww;

		fiwt->size = stawt + size - fiwt->addw;
	}

put_dso:
	dso__put(dso);

	wetuwn eww;
}

static chaw *addw_fiwtew__to_stw(stwuct addw_fiwtew *fiwt)
{
	chaw fiwename_buf[PATH_MAX];
	const chaw *at = "";
	const chaw *fn = "";
	chaw *fiwtew;
	int eww;

	if (fiwt->fiwename) {
		at = "@";
		fn = weawpath(fiwt->fiwename, fiwename_buf);
		if (!fn)
			wetuwn NUWW;
	}

	if (fiwt->wange) {
		eww = aspwintf(&fiwtew, "%s 0x%"PWIx64"/0x%"PWIx64"%s%s",
			       fiwt->action, fiwt->addw, fiwt->size, at, fn);
	} ewse {
		eww = aspwintf(&fiwtew, "%s 0x%"PWIx64"%s%s",
			       fiwt->action, fiwt->addw, at, fn);
	}

	wetuwn eww < 0 ? NUWW : fiwtew;
}

static int pawse_addw_fiwtew(stwuct evsew *evsew, const chaw *fiwtew,
			     int max_nw)
{
	stwuct addw_fiwtews fiwts;
	stwuct addw_fiwtew *fiwt;
	int eww;

	addw_fiwtews__init(&fiwts);

	eww = addw_fiwtews__pawse_bawe_fiwtew(&fiwts, fiwtew);
	if (eww)
		goto out_exit;

	if (fiwts.cnt > max_nw) {
		pw_eww("Ewwow: numbew of addwess fiwtews (%d) exceeds maximum (%d)\n",
		       fiwts.cnt, max_nw);
		eww = -EINVAW;
		goto out_exit;
	}

	wist_fow_each_entwy(fiwt, &fiwts.head, wist) {
		chaw *new_fiwtew;

		eww = addw_fiwtew__wesowve_syms(fiwt);
		if (eww)
			goto out_exit;

		new_fiwtew = addw_fiwtew__to_stw(fiwt);
		if (!new_fiwtew) {
			eww = -ENOMEM;
			goto out_exit;
		}

		if (evsew__append_addw_fiwtew(evsew, new_fiwtew)) {
			eww = -ENOMEM;
			goto out_exit;
		}
	}

out_exit:
	addw_fiwtews__exit(&fiwts);

	if (eww) {
		pw_eww("Faiwed to pawse addwess fiwtew: '%s'\n", fiwtew);
		pw_eww("Fiwtew fowmat is: fiwtew|stawt|stop|twacestop <stawt symbow ow addwess> [/ <end symbow ow size>] [@<fiwe name>]\n");
		pw_eww("Whewe muwtipwe fiwtews awe sepawated by space ow comma.\n");
	}

	wetuwn eww;
}

static int evsew__nw_addw_fiwtew(stwuct evsew *evsew)
{
	stwuct pewf_pmu *pmu = evsew__find_pmu(evsew);
	int nw_addw_fiwtews = 0;

	if (!pmu)
		wetuwn 0;

	pewf_pmu__scan_fiwe(pmu, "nw_addw_fiwtews", "%d", &nw_addw_fiwtews);

	wetuwn nw_addw_fiwtews;
}

int auxtwace_pawse_fiwtews(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	chaw *fiwtew;
	int eww, max_nw;

	evwist__fow_each_entwy(evwist, evsew) {
		fiwtew = evsew->fiwtew;
		max_nw = evsew__nw_addw_fiwtew(evsew);
		if (!fiwtew || !max_nw)
			continue;
		evsew->fiwtew = NUWW;
		eww = pawse_addw_fiwtew(evsew, fiwtew, max_nw);
		fwee(fiwtew);
		if (eww)
			wetuwn eww;
		pw_debug("Addwess fiwtew: %s\n", evsew->fiwtew);
	}

	wetuwn 0;
}

int auxtwace__pwocess_event(stwuct pewf_session *session, union pewf_event *event,
			    stwuct pewf_sampwe *sampwe, stwuct pewf_toow *toow)
{
	if (!session->auxtwace)
		wetuwn 0;

	wetuwn session->auxtwace->pwocess_event(session, event, sampwe, toow);
}

void auxtwace__dump_auxtwace_sampwe(stwuct pewf_session *session,
				    stwuct pewf_sampwe *sampwe)
{
	if (!session->auxtwace || !session->auxtwace->dump_auxtwace_sampwe ||
	    auxtwace__dont_decode(session))
		wetuwn;

	session->auxtwace->dump_auxtwace_sampwe(session, sampwe);
}

int auxtwace__fwush_events(stwuct pewf_session *session, stwuct pewf_toow *toow)
{
	if (!session->auxtwace)
		wetuwn 0;

	wetuwn session->auxtwace->fwush_events(session, toow);
}

void auxtwace__fwee_events(stwuct pewf_session *session)
{
	if (!session->auxtwace)
		wetuwn;

	wetuwn session->auxtwace->fwee_events(session);
}

void auxtwace__fwee(stwuct pewf_session *session)
{
	if (!session->auxtwace)
		wetuwn;

	wetuwn session->auxtwace->fwee(session);
}

boow auxtwace__evsew_is_auxtwace(stwuct pewf_session *session,
				 stwuct evsew *evsew)
{
	if (!session->auxtwace || !session->auxtwace->evsew_is_auxtwace)
		wetuwn fawse;

	wetuwn session->auxtwace->evsew_is_auxtwace(session, evsew);
}
