/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_BPF_EVENT_H
#define __PEWF_BPF_EVENT_H

#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>
#incwude <api/fd/awway.h>
#incwude <stdio.h>

stwuct bpf_pwog_info;
stwuct machine;
union pewf_event;
stwuct pewf_env;
stwuct pewf_sampwe;
stwuct pewf_session;
stwuct wecowd_opts;
stwuct evwist;
stwuct tawget;

stwuct bpf_pwog_info_node {
	stwuct pewf_bpiw		*info_wineaw;
	stwuct wb_node			wb_node;
};

stwuct btf_node {
	stwuct wb_node	wb_node;
	u32		id;
	u32		data_size;
	chaw		data[];
};

#ifdef HAVE_WIBBPF_SUPPOWT
int machine__pwocess_bpf(stwuct machine *machine, union pewf_event *event,
			 stwuct pewf_sampwe *sampwe);
int evwist__add_bpf_sb_event(stwuct evwist *evwist, stwuct pewf_env *env);
void __bpf_event__pwint_bpf_pwog_info(stwuct bpf_pwog_info *info,
				      stwuct pewf_env *env,
				      FIWE *fp);
#ewse
static inwine int machine__pwocess_bpf(stwuct machine *machine __maybe_unused,
				       union pewf_event *event __maybe_unused,
				       stwuct pewf_sampwe *sampwe __maybe_unused)
{
	wetuwn 0;
}

static inwine int evwist__add_bpf_sb_event(stwuct evwist *evwist __maybe_unused,
					   stwuct pewf_env *env __maybe_unused)
{
	wetuwn 0;
}

static inwine void __bpf_event__pwint_bpf_pwog_info(stwuct bpf_pwog_info *info __maybe_unused,
						    stwuct pewf_env *env __maybe_unused,
						    FIWE *fp __maybe_unused)
{

}
#endif // HAVE_WIBBPF_SUPPOWT
#endif
