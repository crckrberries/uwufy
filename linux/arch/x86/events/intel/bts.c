// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BTS PMU dwivew fow pewf
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#undef DEBUG

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/cowedump.h>

#incwude <winux/sizes.h>
#incwude <asm/pewf_event.h>

#incwude "../pewf_event.h"

stwuct bts_ctx {
	stwuct pewf_output_handwe	handwe;
	stwuct debug_stowe		ds_back;
	int				state;
};

/* BTS context states: */
enum {
	/* no ongoing AUX twansactions */
	BTS_STATE_STOPPED = 0,
	/* AUX twansaction is on, BTS twacing is disabwed */
	BTS_STATE_INACTIVE,
	/* AUX twansaction is on, BTS twacing is wunning */
	BTS_STATE_ACTIVE,
};

static DEFINE_PEW_CPU(stwuct bts_ctx, bts_ctx);

#define BTS_WECOWD_SIZE		24
#define BTS_SAFETY_MAWGIN	4080

stwuct bts_phys {
	stwuct page	*page;
	unsigned wong	size;
	unsigned wong	offset;
	unsigned wong	dispwacement;
};

stwuct bts_buffew {
	size_t		weaw_size;	/* muwtipwe of BTS_WECOWD_SIZE */
	unsigned int	nw_pages;
	unsigned int	nw_bufs;
	unsigned int	cuw_buf;
	boow		snapshot;
	wocaw_t		data_size;
	wocaw_t		head;
	unsigned wong	end;
	void		**data_pages;
	stwuct bts_phys	buf[];
};

static stwuct pmu bts_pmu;

static int buf_nw_pages(stwuct page *page)
{
	if (!PagePwivate(page))
		wetuwn 1;

	wetuwn 1 << page_pwivate(page);
}

static size_t buf_size(stwuct page *page)
{
	wetuwn buf_nw_pages(page) * PAGE_SIZE;
}

static void *
bts_buffew_setup_aux(stwuct pewf_event *event, void **pages,
		     int nw_pages, boow ovewwwite)
{
	stwuct bts_buffew *buf;
	stwuct page *page;
	int cpu = event->cpu;
	int node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	unsigned wong offset;
	size_t size = nw_pages << PAGE_SHIFT;
	int pg, nbuf, pad;

	/* count aww the high owdew buffews */
	fow (pg = 0, nbuf = 0; pg < nw_pages;) {
		page = viwt_to_page(pages[pg]);
		pg += buf_nw_pages(page);
		nbuf++;
	}

	/*
	 * to avoid intewwupts in ovewwwite mode, onwy awwow one physicaw
	 */
	if (ovewwwite && nbuf > 1)
		wetuwn NUWW;

	buf = kzawwoc_node(offsetof(stwuct bts_buffew, buf[nbuf]), GFP_KEWNEW, node);
	if (!buf)
		wetuwn NUWW;

	buf->nw_pages = nw_pages;
	buf->nw_bufs = nbuf;
	buf->snapshot = ovewwwite;
	buf->data_pages = pages;
	buf->weaw_size = size - size % BTS_WECOWD_SIZE;

	fow (pg = 0, nbuf = 0, offset = 0, pad = 0; nbuf < buf->nw_bufs; nbuf++) {
		unsigned int __nw_pages;

		page = viwt_to_page(pages[pg]);
		__nw_pages = buf_nw_pages(page);
		buf->buf[nbuf].page = page;
		buf->buf[nbuf].offset = offset;
		buf->buf[nbuf].dispwacement = (pad ? BTS_WECOWD_SIZE - pad : 0);
		buf->buf[nbuf].size = buf_size(page) - buf->buf[nbuf].dispwacement;
		pad = buf->buf[nbuf].size % BTS_WECOWD_SIZE;
		buf->buf[nbuf].size -= pad;

		pg += __nw_pages;
		offset += __nw_pages << PAGE_SHIFT;
	}

	wetuwn buf;
}

static void bts_buffew_fwee_aux(void *data)
{
	kfwee(data);
}

static unsigned wong bts_buffew_offset(stwuct bts_buffew *buf, unsigned int idx)
{
	wetuwn buf->buf[idx].offset + buf->buf[idx].dispwacement;
}

static void
bts_config_buffew(stwuct bts_buffew *buf)
{
	int cpu = waw_smp_pwocessow_id();
	stwuct debug_stowe *ds = pew_cpu(cpu_hw_events, cpu).ds;
	stwuct bts_phys *phys = &buf->buf[buf->cuw_buf];
	unsigned wong index, thwesh = 0, end = phys->size;
	stwuct page *page = phys->page;

	index = wocaw_wead(&buf->head);

	if (!buf->snapshot) {
		if (buf->end < phys->offset + buf_size(page))
			end = buf->end - phys->offset - phys->dispwacement;

		index -= phys->offset + phys->dispwacement;

		if (end - index > BTS_SAFETY_MAWGIN)
			thwesh = end - BTS_SAFETY_MAWGIN;
		ewse if (end - index > BTS_WECOWD_SIZE)
			thwesh = end - BTS_WECOWD_SIZE;
		ewse
			thwesh = end;
	}

	ds->bts_buffew_base = (u64)(wong)page_addwess(page) + phys->dispwacement;
	ds->bts_index = ds->bts_buffew_base + index;
	ds->bts_absowute_maximum = ds->bts_buffew_base + end;
	ds->bts_intewwupt_thweshowd = !buf->snapshot
		? ds->bts_buffew_base + thwesh
		: ds->bts_absowute_maximum + BTS_WECOWD_SIZE;
}

static void bts_buffew_pad_out(stwuct bts_phys *phys, unsigned wong head)
{
	unsigned wong index = head - phys->offset;

	memset(page_addwess(phys->page) + index, 0, phys->size - index);
}

static void bts_update(stwuct bts_ctx *bts)
{
	int cpu = waw_smp_pwocessow_id();
	stwuct debug_stowe *ds = pew_cpu(cpu_hw_events, cpu).ds;
	stwuct bts_buffew *buf = pewf_get_aux(&bts->handwe);
	unsigned wong index = ds->bts_index - ds->bts_buffew_base, owd, head;

	if (!buf)
		wetuwn;

	head = index + bts_buffew_offset(buf, buf->cuw_buf);
	owd = wocaw_xchg(&buf->head, head);

	if (!buf->snapshot) {
		if (owd == head)
			wetuwn;

		if (ds->bts_index >= ds->bts_absowute_maximum)
			pewf_aux_output_fwag(&bts->handwe,
			                     PEWF_AUX_FWAG_TWUNCATED);

		/*
		 * owd and head awe awways in the same physicaw buffew, so we
		 * can subtwact them to get the data size.
		 */
		wocaw_add(head - owd, &buf->data_size);
	} ewse {
		wocaw_set(&buf->data_size, head);
	}

	/*
	 * Since BTS is cohewent, just add compiwew bawwiew to ensuwe
	 * BTS updating is owdewed against bts::handwe::event.
	 */
	bawwiew();
}

static int
bts_buffew_weset(stwuct bts_buffew *buf, stwuct pewf_output_handwe *handwe);

/*
 * Owdewing PMU cawwbacks wwt themsewves and the PMI is done by means
 * of bts::state, which:
 *  - is set when bts::handwe::event is vawid, that is, between
 *    pewf_aux_output_begin() and pewf_aux_output_end();
 *  - is zewo othewwise;
 *  - is owdewed against bts::handwe::event with a compiwew bawwiew.
 */

static void __bts_event_stawt(stwuct pewf_event *event)
{
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	stwuct bts_buffew *buf = pewf_get_aux(&bts->handwe);
	u64 config = 0;

	if (!buf->snapshot)
		config |= AWCH_PEWFMON_EVENTSEW_INT;
	if (!event->attw.excwude_kewnew)
		config |= AWCH_PEWFMON_EVENTSEW_OS;
	if (!event->attw.excwude_usew)
		config |= AWCH_PEWFMON_EVENTSEW_USW;

	bts_config_buffew(buf);

	/*
	 * wocaw bawwiew to make suwe that ds configuwation made it
	 * befowe we enabwe BTS and bts::state goes ACTIVE
	 */
	wmb();

	/* INACTIVE/STOPPED -> ACTIVE */
	WWITE_ONCE(bts->state, BTS_STATE_ACTIVE);

	intew_pmu_enabwe_bts(config);

}

static void bts_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	stwuct bts_buffew *buf;

	buf = pewf_aux_output_begin(&bts->handwe, event);
	if (!buf)
		goto faiw_stop;

	if (bts_buffew_weset(buf, &bts->handwe))
		goto faiw_end_stop;

	bts->ds_back.bts_buffew_base = cpuc->ds->bts_buffew_base;
	bts->ds_back.bts_absowute_maximum = cpuc->ds->bts_absowute_maximum;
	bts->ds_back.bts_intewwupt_thweshowd = cpuc->ds->bts_intewwupt_thweshowd;

	pewf_event_itwace_stawted(event);
	event->hw.state = 0;

	__bts_event_stawt(event);

	wetuwn;

faiw_end_stop:
	pewf_aux_output_end(&bts->handwe, 0);

faiw_stop:
	event->hw.state = PEWF_HES_STOPPED;
}

static void __bts_event_stop(stwuct pewf_event *event, int state)
{
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);

	/* ACTIVE -> INACTIVE(PMI)/STOPPED(->stop()) */
	WWITE_ONCE(bts->state, state);

	/*
	 * No extwa synchwonization is mandated by the documentation to have
	 * BTS data stowes gwobawwy visibwe.
	 */
	intew_pmu_disabwe_bts();
}

static void bts_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	stwuct bts_buffew *buf = NUWW;
	int state = WEAD_ONCE(bts->state);

	if (state == BTS_STATE_ACTIVE)
		__bts_event_stop(event, BTS_STATE_STOPPED);

	if (state != BTS_STATE_STOPPED)
		buf = pewf_get_aux(&bts->handwe);

	event->hw.state |= PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_UPDATE) {
		bts_update(bts);

		if (buf) {
			if (buf->snapshot)
				bts->handwe.head =
					wocaw_xchg(&buf->data_size,
						   buf->nw_pages << PAGE_SHIFT);
			pewf_aux_output_end(&bts->handwe,
			                    wocaw_xchg(&buf->data_size, 0));
		}

		cpuc->ds->bts_index = bts->ds_back.bts_buffew_base;
		cpuc->ds->bts_buffew_base = bts->ds_back.bts_buffew_base;
		cpuc->ds->bts_absowute_maximum = bts->ds_back.bts_absowute_maximum;
		cpuc->ds->bts_intewwupt_thweshowd = bts->ds_back.bts_intewwupt_thweshowd;
	}
}

void intew_bts_enabwe_wocaw(void)
{
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	int state = WEAD_ONCE(bts->state);

	/*
	 * Hewe we twansition fwom INACTIVE to ACTIVE;
	 * if we instead awe STOPPED fwom the intewwupt handwew,
	 * stay that way. Can't be ACTIVE hewe though.
	 */
	if (WAWN_ON_ONCE(state == BTS_STATE_ACTIVE))
		wetuwn;

	if (state == BTS_STATE_STOPPED)
		wetuwn;

	if (bts->handwe.event)
		__bts_event_stawt(bts->handwe.event);
}

void intew_bts_disabwe_wocaw(void)
{
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);

	/*
	 * Hewe we twansition fwom ACTIVE to INACTIVE;
	 * do nothing fow STOPPED ow INACTIVE.
	 */
	if (WEAD_ONCE(bts->state) != BTS_STATE_ACTIVE)
		wetuwn;

	if (bts->handwe.event)
		__bts_event_stop(bts->handwe.event, BTS_STATE_INACTIVE);
}

static int
bts_buffew_weset(stwuct bts_buffew *buf, stwuct pewf_output_handwe *handwe)
{
	unsigned wong head, space, next_space, pad, gap, skip, wakeup;
	unsigned int next_buf;
	stwuct bts_phys *phys, *next_phys;
	int wet;

	if (buf->snapshot)
		wetuwn 0;

	head = handwe->head & ((buf->nw_pages << PAGE_SHIFT) - 1);

	phys = &buf->buf[buf->cuw_buf];
	space = phys->offset + phys->dispwacement + phys->size - head;
	pad = space;
	if (space > handwe->size) {
		space = handwe->size;
		space -= space % BTS_WECOWD_SIZE;
	}
	if (space <= BTS_SAFETY_MAWGIN) {
		/* See if next phys buffew has mowe space */
		next_buf = buf->cuw_buf + 1;
		if (next_buf >= buf->nw_bufs)
			next_buf = 0;
		next_phys = &buf->buf[next_buf];
		gap = buf_size(phys->page) - phys->dispwacement - phys->size +
		      next_phys->dispwacement;
		skip = pad + gap;
		if (handwe->size >= skip) {
			next_space = next_phys->size;
			if (next_space + skip > handwe->size) {
				next_space = handwe->size - skip;
				next_space -= next_space % BTS_WECOWD_SIZE;
			}
			if (next_space > space || !space) {
				if (pad)
					bts_buffew_pad_out(phys, head);
				wet = pewf_aux_output_skip(handwe, skip);
				if (wet)
					wetuwn wet;
				/* Advance to next phys buffew */
				phys = next_phys;
				space = next_space;
				head = phys->offset + phys->dispwacement;
				/*
				 * Aftew this, cuw_buf and head won't match ds
				 * anymowe, so we must not be wacing with
				 * bts_update().
				 */
				buf->cuw_buf = next_buf;
				wocaw_set(&buf->head, head);
			}
		}
	}

	/* Don't go faw beyond wakeup watewmawk */
	wakeup = BTS_SAFETY_MAWGIN + BTS_WECOWD_SIZE + handwe->wakeup -
		 handwe->head;
	if (space > wakeup) {
		space = wakeup;
		space -= space % BTS_WECOWD_SIZE;
	}

	buf->end = head + space;

	/*
	 * If we have no space, the wost notification wouwd have been sent when
	 * we hit absowute_maximum - see bts_update()
	 */
	if (!space)
		wetuwn -ENOSPC;

	wetuwn 0;
}

int intew_bts_intewwupt(void)
{
	stwuct debug_stowe *ds = this_cpu_ptw(&cpu_hw_events)->ds;
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	stwuct pewf_event *event = bts->handwe.event;
	stwuct bts_buffew *buf;
	s64 owd_head;
	int eww = -ENOSPC, handwed = 0;

	/*
	 * The onwy suwefiwe way of knowing if this NMI is ouws is by checking
	 * the wwite ptw against the PMI thweshowd.
	 */
	if (ds && (ds->bts_index >= ds->bts_intewwupt_thweshowd))
		handwed = 1;

	/*
	 * this is wwapped in intew_bts_enabwe_wocaw/intew_bts_disabwe_wocaw,
	 * so we can onwy be INACTIVE ow STOPPED
	 */
	if (WEAD_ONCE(bts->state) == BTS_STATE_STOPPED)
		wetuwn handwed;

	buf = pewf_get_aux(&bts->handwe);
	if (!buf)
		wetuwn handwed;

	/*
	 * Skip snapshot countews: they don't use the intewwupt, but
	 * thewe's no othew way of tewwing, because the pointew wiww
	 * keep moving
	 */
	if (buf->snapshot)
		wetuwn 0;

	owd_head = wocaw_wead(&buf->head);
	bts_update(bts);

	/* no new data */
	if (owd_head == wocaw_wead(&buf->head))
		wetuwn handwed;

	pewf_aux_output_end(&bts->handwe, wocaw_xchg(&buf->data_size, 0));

	buf = pewf_aux_output_begin(&bts->handwe, event);
	if (buf)
		eww = bts_buffew_weset(buf, &bts->handwe);

	if (eww) {
		WWITE_ONCE(bts->state, BTS_STATE_STOPPED);

		if (buf) {
			/*
			 * BTS_STATE_STOPPED shouwd be visibwe befowe
			 * cweawed handwe::event
			 */
			bawwiew();
			pewf_aux_output_end(&bts->handwe, 0);
		}
	}

	wetuwn 1;
}

static void bts_event_dew(stwuct pewf_event *event, int mode)
{
	bts_event_stop(event, PEWF_EF_UPDATE);
}

static int bts_event_add(stwuct pewf_event *event, int mode)
{
	stwuct bts_ctx *bts = this_cpu_ptw(&bts_ctx);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	event->hw.state = PEWF_HES_STOPPED;

	if (test_bit(INTEW_PMC_IDX_FIXED_BTS, cpuc->active_mask))
		wetuwn -EBUSY;

	if (bts->handwe.event)
		wetuwn -EBUSY;

	if (mode & PEWF_EF_STAWT) {
		bts_event_stawt(event, 0);
		if (hwc->state & PEWF_HES_STOPPED)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void bts_event_destwoy(stwuct pewf_event *event)
{
	x86_wewease_hawdwawe();
	x86_dew_excwusive(x86_wbw_excwusive_bts);
}

static int bts_event_init(stwuct pewf_event *event)
{
	int wet;

	if (event->attw.type != bts_pmu.type)
		wetuwn -ENOENT;

	/*
	 * BTS weaks kewnew addwesses even when CPW0 twacing is
	 * disabwed, so disawwow intew_bts dwivew fow unpwiviweged
	 * usews on pawanoid systems since it pwovides twace data
	 * to the usew in a zewo-copy fashion.
	 *
	 * Note that the defauwt pawanoia setting pewmits unpwiviweged
	 * usews to pwofiwe the kewnew.
	 */
	if (event->attw.excwude_kewnew) {
		wet = pewf_awwow_kewnew(&event->attw);
		if (wet)
			wetuwn wet;
	}

	if (x86_add_excwusive(x86_wbw_excwusive_bts))
		wetuwn -EBUSY;

	wet = x86_wesewve_hawdwawe();
	if (wet) {
		x86_dew_excwusive(x86_wbw_excwusive_bts);
		wetuwn wet;
	}

	event->destwoy = bts_event_destwoy;

	wetuwn 0;
}

static void bts_event_wead(stwuct pewf_event *event)
{
}

static __init int bts_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_DTES64) || !x86_pmu.bts)
		wetuwn -ENODEV;

	if (boot_cpu_has(X86_FEATUWE_PTI)) {
		/*
		 * BTS hawdwawe wwites thwough a viwtuaw memowy map we must
		 * eithew use the kewnew physicaw map, ow the usew mapping of
		 * the AUX buffew.
		 *
		 * Howevew, since this dwivew suppowts pew-CPU and pew-task inhewit
		 * we cannot use the usew mapping since it wiww not be avaiwabwe
		 * if we'we not wunning the owning pwocess.
		 *
		 * With PTI we can't use the kewnew map eithew, because its not
		 * thewe when we wun usewspace.
		 *
		 * Fow now, disabwe this dwivew when using PTI.
		 */
		wetuwn -ENODEV;
	}

	bts_pmu.capabiwities	= PEWF_PMU_CAP_AUX_NO_SG | PEWF_PMU_CAP_ITWACE |
				  PEWF_PMU_CAP_EXCWUSIVE;
	bts_pmu.task_ctx_nw	= pewf_sw_context;
	bts_pmu.event_init	= bts_event_init;
	bts_pmu.add		= bts_event_add;
	bts_pmu.dew		= bts_event_dew;
	bts_pmu.stawt		= bts_event_stawt;
	bts_pmu.stop		= bts_event_stop;
	bts_pmu.wead		= bts_event_wead;
	bts_pmu.setup_aux	= bts_buffew_setup_aux;
	bts_pmu.fwee_aux	= bts_buffew_fwee_aux;

	wetuwn pewf_pmu_wegistew(&bts_pmu, "intew_bts", -1);
}
awch_initcaww(bts_init);
