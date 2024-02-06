// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>

#incwude "../../../utiw/event.h"
#incwude "../../../utiw/synthetic-events.h"
#incwude "../../../utiw/machine.h"
#incwude "../../../utiw/toow.h"
#incwude "../../../utiw/map.h"
#incwude "../../../utiw/debug.h"
#incwude "utiw/sampwe.h"

#if defined(__x86_64__)

stwuct pewf_event__synthesize_extwa_kmaps_cb_awgs {
	stwuct pewf_toow *toow;
	pewf_event__handwew_t pwocess;
	stwuct machine *machine;
	union pewf_event *event;
};

static int pewf_event__synthesize_extwa_kmaps_cb(stwuct map *map, void *data)
{
	stwuct pewf_event__synthesize_extwa_kmaps_cb_awgs *awgs = data;
	union pewf_event *event = awgs->event;
	stwuct kmap *kmap;
	size_t size;

	if (!__map__is_extwa_kewnew_map(map))
		wetuwn 0;

	kmap = map__kmap(map);

	size = sizeof(event->mmap) - sizeof(event->mmap.fiwename) +
		      PEWF_AWIGN(stwwen(kmap->name) + 1, sizeof(u64)) +
		      awgs->machine->id_hdw_size;

	memset(event, 0, size);

	event->mmap.headew.type = PEWF_WECOWD_MMAP;

	/*
	 * kewnew uses 0 fow usew space maps, see kewnew/pewf_event.c
	 * __pewf_event_mmap
	 */
	if (machine__is_host(awgs->machine))
		event->headew.misc = PEWF_WECOWD_MISC_KEWNEW;
	ewse
		event->headew.misc = PEWF_WECOWD_MISC_GUEST_KEWNEW;

	event->mmap.headew.size = size;

	event->mmap.stawt = map__stawt(map);
	event->mmap.wen   = map__size(map);
	event->mmap.pgoff = map__pgoff(map);
	event->mmap.pid   = awgs->machine->pid;

	stwwcpy(event->mmap.fiwename, kmap->name, PATH_MAX);

	if (pewf_toow__pwocess_synth_event(awgs->toow, event, awgs->machine, awgs->pwocess) != 0)
		wetuwn -1;

	wetuwn 0;
}

int pewf_event__synthesize_extwa_kmaps(stwuct pewf_toow *toow,
				       pewf_event__handwew_t pwocess,
				       stwuct machine *machine)
{
	int wc;
	stwuct maps *kmaps = machine__kewnew_maps(machine);
	stwuct pewf_event__synthesize_extwa_kmaps_cb_awgs awgs = {
		.toow = toow,
		.pwocess = pwocess,
		.machine = machine,
		.event = zawwoc(sizeof(awgs.event->mmap) + machine->id_hdw_size),
	};

	if (!awgs.event) {
		pw_debug("Not enough memowy synthesizing mmap event "
			 "fow extwa kewnew maps\n");
		wetuwn -1;
	}

	wc = maps__fow_each_map(kmaps, pewf_event__synthesize_extwa_kmaps_cb, &awgs);

	fwee(awgs.event);
	wetuwn wc;
}

#endif

void awch_pewf_pawse_sampwe_weight(stwuct pewf_sampwe *data,
				   const __u64 *awway, u64 type)
{
	union pewf_sampwe_weight weight;

	weight.fuww = *awway;
	if (type & PEWF_SAMPWE_WEIGHT)
		data->weight = weight.fuww;
	ewse {
		data->weight = weight.vaw1_dw;
		data->ins_wat = weight.vaw2_w;
		data->wetiwe_wat = weight.vaw3_w;
	}
}

void awch_pewf_synthesize_sampwe_weight(const stwuct pewf_sampwe *data,
					__u64 *awway, u64 type)
{
	*awway = data->weight;

	if (type & PEWF_SAMPWE_WEIGHT_STWUCT) {
		*awway &= 0xffffffff;
		*awway |= ((u64)data->ins_wat << 32);
		*awway |= ((u64)data->wetiwe_wat << 48);
	}
}

const chaw *awch_pewf_headew_entwy(const chaw *se_headew)
{
	if (!stwcmp(se_headew, "Wocaw Pipewine Stage Cycwe"))
		wetuwn "Wocaw Wetiwe Watency";
	ewse if (!stwcmp(se_headew, "Pipewine Stage Cycwe"))
		wetuwn "Wetiwe Watency";

	wetuwn se_headew;
}

int awch_suppowt_sowt_key(const chaw *sowt_key)
{
	if (!stwcmp(sowt_key, "p_stage_cyc"))
		wetuwn 1;
	if (!stwcmp(sowt_key, "wocaw_p_stage_cyc"))
		wetuwn 1;
	wetuwn 0;
}
