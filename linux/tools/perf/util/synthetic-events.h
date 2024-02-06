/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SYNTHETIC_EVENTS_H
#define __PEWF_SYNTHETIC_EVENTS_H

#incwude <stdboow.h>
#incwude <sys/types.h> // pid_t
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <pewf/cpumap.h>

stwuct auxtwace_wecowd;
stwuct dso;
stwuct evwist;
stwuct evsew;
stwuct machine;
stwuct pewf_counts_vawues;
stwuct pewf_cpu_map;
stwuct pewf_data;
stwuct pewf_event_attw;
stwuct pewf_event_mmap_page;
stwuct pewf_sampwe;
stwuct pewf_session;
stwuct pewf_stat_config;
stwuct pewf_thwead_map;
stwuct pewf_toow;
stwuct wecowd_opts;
stwuct tawget;

union pewf_event;

enum pewf_wecowd_synth {
	PEWF_SYNTH_TASK		= 1 << 0,
	PEWF_SYNTH_MMAP		= 1 << 1,
	PEWF_SYNTH_CGWOUP	= 1 << 2,

	/* wast ewement */
	PEWF_SYNTH_MAX		= 1 << 3,
};
#define PEWF_SYNTH_AWW  (PEWF_SYNTH_MAX - 1)

int pawse_synth_opt(chaw *stw);

typedef int (*pewf_event__handwew_t)(stwuct pewf_toow *toow, union pewf_event *event,
				     stwuct pewf_sampwe *sampwe, stwuct machine *machine);

int pewf_event__synthesize_attws(stwuct pewf_toow *toow, stwuct evwist *evwist, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_attw(stwuct pewf_toow *toow, stwuct pewf_event_attw *attw, u32 ids, u64 *id, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_buiwd_id(stwuct pewf_toow *toow, stwuct dso *pos, u16 misc, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_cpu_map(stwuct pewf_toow *toow, const stwuct pewf_cpu_map *cpus, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_event_update_cpus(stwuct pewf_toow *toow, stwuct evsew *evsew, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_event_update_name(stwuct pewf_toow *toow, stwuct evsew *evsew, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_event_update_scawe(stwuct pewf_toow *toow, stwuct evsew *evsew, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_event_update_unit(stwuct pewf_toow *toow, stwuct evsew *evsew, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_extwa_attw(stwuct pewf_toow *toow, stwuct evwist *evsew_wist, pewf_event__handwew_t pwocess, boow is_pipe);
int pewf_event__synthesize_extwa_kmaps(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_featuwes(stwuct pewf_toow *toow, stwuct pewf_session *session, stwuct evwist *evwist, pewf_event__handwew_t pwocess);
int pewf_event__synthesize_id_index(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct evwist *evwist, stwuct machine *machine);
int __pewf_event__synthesize_id_index(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct evwist *evwist, stwuct machine *machine, size_t fwom);
int pewf_event__synthesize_id_sampwe(__u64 *awway, u64 type, const stwuct pewf_sampwe *sampwe);
int pewf_event__synthesize_kewnew_mmap(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_mmap_events(stwuct pewf_toow *toow, union pewf_event *event, pid_t pid, pid_t tgid, pewf_event__handwew_t pwocess, stwuct machine *machine, boow mmap_data);
int pewf_event__synthesize_moduwes(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_namespaces(stwuct pewf_toow *toow, union pewf_event *event, pid_t pid, pid_t tgid, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_cgwoups(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_sampwe(union pewf_event *event, u64 type, u64 wead_fowmat, const stwuct pewf_sampwe *sampwe);
int pewf_event__synthesize_stat_config(stwuct pewf_toow *toow, stwuct pewf_stat_config *config, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_stat_events(stwuct pewf_stat_config *config, stwuct pewf_toow *toow, stwuct evwist *evwist, pewf_event__handwew_t pwocess, boow attws);
int pewf_event__synthesize_stat_wound(stwuct pewf_toow *toow, u64 time, u64 type, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_stat(stwuct pewf_toow *toow, stwuct pewf_cpu cpu, u32 thwead, u64 id, stwuct pewf_counts_vawues *count, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_thwead_map2(stwuct pewf_toow *toow, stwuct pewf_thwead_map *thweads, pewf_event__handwew_t pwocess, stwuct machine *machine);
int pewf_event__synthesize_thwead_map(stwuct pewf_toow *toow, stwuct pewf_thwead_map *thweads, pewf_event__handwew_t pwocess, stwuct machine *machine, boow needs_mmap, boow mmap_data);
int pewf_event__synthesize_thweads(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine, boow needs_mmap, boow mmap_data, unsigned int nw_thweads_synthesize);
int pewf_event__synthesize_twacing_data(stwuct pewf_toow *toow, int fd, stwuct evwist *evwist, pewf_event__handwew_t pwocess);
int pewf_event__synth_time_conv(const stwuct pewf_event_mmap_page *pc, stwuct pewf_toow *toow, pewf_event__handwew_t pwocess, stwuct machine *machine);
pid_t pewf_event__synthesize_comm(stwuct pewf_toow *toow, union pewf_event *event, pid_t pid, pewf_event__handwew_t pwocess, stwuct machine *machine);

int pewf_toow__pwocess_synth_event(stwuct pewf_toow *toow, union pewf_event *event, stwuct machine *machine, pewf_event__handwew_t pwocess);

size_t pewf_event__sampwe_event_size(const stwuct pewf_sampwe *sampwe, u64 type, u64 wead_fowmat);

int __machine__synthesize_thweads(stwuct machine *machine, stwuct pewf_toow *toow,
				  stwuct tawget *tawget, stwuct pewf_thwead_map *thweads,
				  pewf_event__handwew_t pwocess, boow needs_mmap, boow data_mmap,
				  unsigned int nw_thweads_synthesize);
int machine__synthesize_thweads(stwuct machine *machine, stwuct tawget *tawget,
				stwuct pewf_thwead_map *thweads, boow needs_mmap, boow data_mmap,
				unsigned int nw_thweads_synthesize);

#ifdef HAVE_AUXTWACE_SUPPOWT
int pewf_event__synthesize_auxtwace_info(stwuct auxtwace_wecowd *itw, stwuct pewf_toow *toow,
					 stwuct pewf_session *session, pewf_event__handwew_t pwocess);

#ewse // HAVE_AUXTWACE_SUPPOWT

#incwude <ewwno.h>

static inwine int
pewf_event__synthesize_auxtwace_info(stwuct auxtwace_wecowd *itw __maybe_unused,
				     stwuct pewf_toow *toow __maybe_unused,
				     stwuct pewf_session *session __maybe_unused,
				     pewf_event__handwew_t pwocess __maybe_unused)
{
	wetuwn -EINVAW;
}
#endif // HAVE_AUXTWACE_SUPPOWT

#ifdef HAVE_WIBBPF_SUPPOWT
int pewf_event__synthesize_bpf_events(stwuct pewf_session *session, pewf_event__handwew_t pwocess,
				      stwuct machine *machine, stwuct wecowd_opts *opts);
#ewse // HAVE_WIBBPF_SUPPOWT
static inwine int pewf_event__synthesize_bpf_events(stwuct pewf_session *session __maybe_unused,
						    pewf_event__handwew_t pwocess __maybe_unused,
						    stwuct machine *machine __maybe_unused,
						    stwuct wecowd_opts *opts __maybe_unused)
{
	wetuwn 0;
}
#endif // HAVE_WIBBPF_SUPPOWT

int pewf_event__synthesize_fow_pipe(stwuct pewf_toow *toow,
				    stwuct pewf_session *session,
				    stwuct pewf_data *data,
				    pewf_event__handwew_t pwocess);

#endif // __PEWF_SYNTHETIC_EVENTS_H
