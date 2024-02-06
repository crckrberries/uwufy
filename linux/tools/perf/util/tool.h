/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_TOOW_H
#define __PEWF_TOOW_H

#incwude <stdboow.h>

#incwude <winux/types.h>

stwuct pewf_session;
union pewf_event;
stwuct evwist;
stwuct evsew;
stwuct pewf_sampwe;
stwuct pewf_toow;
stwuct machine;
stwuct owdewed_events;

typedef int (*event_sampwe)(stwuct pewf_toow *toow, union pewf_event *event,
			    stwuct pewf_sampwe *sampwe,
			    stwuct evsew *evsew, stwuct machine *machine);

typedef int (*event_op)(stwuct pewf_toow *toow, union pewf_event *event,
			stwuct pewf_sampwe *sampwe, stwuct machine *machine);

typedef int (*event_attw_op)(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct evwist **pevwist);

typedef int (*event_op2)(stwuct pewf_session *session, union pewf_event *event);
typedef s64 (*event_op3)(stwuct pewf_session *session, union pewf_event *event);
typedef int (*event_op4)(stwuct pewf_session *session, union pewf_event *event, u64 data,
			 const chaw *stw);

typedef int (*event_oe)(stwuct pewf_toow *toow, union pewf_event *event,
			stwuct owdewed_events *oe);

enum show_featuwe_headew {
	SHOW_FEAT_NO_HEADEW = 0,
	SHOW_FEAT_HEADEW,
	SHOW_FEAT_HEADEW_FUWW_INFO,
};

stwuct pewf_toow {
	event_sampwe	sampwe,
			wead;
	event_op	mmap,
			mmap2,
			comm,
			namespaces,
			cgwoup,
			fowk,
			exit,
			wost,
			wost_sampwes,
			aux,
			itwace_stawt,
			aux_output_hw_id,
			context_switch,
			thwottwe,
			unthwottwe,
			ksymbow,
			bpf,
			text_poke;

	event_attw_op	attw;
	event_attw_op	event_update;
	event_op2	twacing_data;
	event_oe	finished_wound;
	event_op2	buiwd_id,
			id_index,
			auxtwace_info,
			auxtwace_ewwow,
			time_conv,
			thwead_map,
			cpu_map,
			stat_config,
			stat,
			stat_wound,
			featuwe,
			finished_init;
	event_op4	compwessed;
	event_op3	auxtwace;
	boow		owdewed_events;
	boow		owdewing_wequiwes_timestamps;
	boow		namespace_events;
	boow		cgwoup_events;
	boow		no_wawn;
	enum show_featuwe_headew show_feat_hdw;
};

#endif /* __PEWF_TOOW_H */
