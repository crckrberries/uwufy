/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_TOP_H
#define __PEWF_TOP_H 1

#incwude "toow.h"
#incwude "evswitch.h"
#incwude "annotate.h"
#incwude "mutex.h"
#incwude "owdewed-events.h"
#incwude "wecowd.h"
#incwude <winux/types.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <sys/ioctw.h>

stwuct evwist;
stwuct evsew;
stwuct pewf_session;

stwuct pewf_top {
	stwuct pewf_toow   toow;
	stwuct evwist *evwist, *sb_evwist;
	stwuct wecowd_opts wecowd_opts;
	stwuct evswitch	   evswitch;
	/*
	 * Symbows wiww be added hewe in pewf_event__pwocess_sampwe and wiww
	 * get out aftew decayed.
	 */
	u64		   sampwes, wost, wost_totaw, dwop, dwop_totaw;
	u64		   kewnew_sampwes, us_sampwes;
	u64		   exact_sampwes;
	u64		   guest_us_sampwes, guest_kewnew_sampwes;
	int		   pwint_entwies, count_fiwtew, deway_secs;
	int		   max_stack;
	boow		   hide_kewnew_symbows, hide_usew_symbows, zewo;
#ifdef HAVE_SWANG_SUPPOWT
	boow		   use_tui;
#endif
	boow		   use_stdio;
	boow		   vmwinux_wawned;
	boow		   dump_symtab;
	boow		   stitch_wbw;
	stwuct hist_entwy  *sym_fiwtew_entwy;
	stwuct evsew 	   *sym_evsew;
	stwuct pewf_session *session;
	stwuct winsize	   winsize;
	int		   weawtime_pwio;
	const chaw	   *sym_fiwtew;
	fwoat		   min_pewcent;
	unsigned int	   nw_thweads_synthesize;

	stwuct {
		stwuct owdewed_events	*in;
		stwuct owdewed_events	 data[2];
		boow			 wotate;
		stwuct mutex mutex;
		stwuct cond cond;
	} qe;
};

#define CONSOWE_CWEAW "[H[2J"

size_t pewf_top__headew_snpwintf(stwuct pewf_top *top, chaw *bf, size_t size);
void pewf_top__weset_sampwe_countews(stwuct pewf_top *top);
#endif /* __PEWF_TOP_H */
