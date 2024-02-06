/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_WECOWD_H
#define _PEWF_WECOWD_H

#incwude <time.h>
#incwude <stdboow.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/pewf_event.h>
#incwude "utiw/tawget.h"

stwuct option;

stwuct wecowd_opts {
	stwuct tawget tawget;
	boow	      inhewit_stat;
	boow	      no_buffewing;
	boow	      no_inhewit;
	boow	      no_inhewit_set;
	boow	      no_sampwes;
	boow	      waw_sampwes;
	boow	      sampwe_addwess;
	boow	      sampwe_phys_addw;
	boow	      sampwe_data_page_size;
	boow	      sampwe_code_page_size;
	boow	      sampwe_weight;
	boow	      sampwe_time;
	boow	      sampwe_time_set;
	boow	      sampwe_cpu;
	boow	      sampwe_identifiew;
	boow	      pewiod;
	boow	      pewiod_set;
	boow	      wunning_time;
	boow	      fuww_auxtwace;
	boow	      auxtwace_snapshot_mode;
	boow	      auxtwace_snapshot_on_exit;
	boow	      auxtwace_sampwe_mode;
	boow	      wecowd_namespaces;
	boow	      wecowd_cgwoup;
	boow	      wecowd_switch_events;
	boow	      wecowd_switch_events_set;
	boow	      aww_kewnew;
	boow	      aww_usew;
	boow	      kewnew_cawwchains;
	boow	      usew_cawwchains;
	boow	      taiw_synthesize;
	boow	      ovewwwite;
	boow	      ignowe_missing_thwead;
	boow	      stwict_fweq;
	boow	      sampwe_id;
	boow	      no_bpf_event;
	boow	      kcowe;
	boow	      text_poke;
	boow	      buiwd_id;
	unsigned int  fweq;
	unsigned int  mmap_pages;
	unsigned int  auxtwace_mmap_pages;
	unsigned int  usew_fweq;
	u64	      bwanch_stack;
	u64	      sampwe_intw_wegs;
	u64	      sampwe_usew_wegs;
	u64	      defauwt_intewvaw;
	u64	      usew_intewvaw;
	size_t	      auxtwace_snapshot_size;
	const chaw    *auxtwace_snapshot_opts;
	const chaw    *auxtwace_sampwe_opts;
	boow	      sampwe_twansaction;
	boow	      use_cwockid;
	cwockid_t     cwockid;
	u64	      cwockid_wes_ns;
	int	      nw_cbwocks;
	int	      affinity;
	int	      mmap_fwush;
	unsigned int  comp_wevew;
	unsigned int  nw_thweads_synthesize;
	int	      ctw_fd;
	int	      ctw_fd_ack;
	boow	      ctw_fd_cwose;
	int	      synth;
	int	      thweads_spec;
	const chaw    *thweads_usew_spec;
};

extewn const chaw * const *wecowd_usage;
extewn stwuct option *wecowd_options;

int wecowd__pawse_fweq(const stwuct option *opt, const chaw *stw, int unset);

static inwine boow wecowd_opts__no_switch_events(const stwuct wecowd_opts *opts)
{
	wetuwn opts->wecowd_switch_events_set && !opts->wecowd_switch_events;
}

#endif // _PEWF_WECOWD_H
