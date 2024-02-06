// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Netfs suppowt statistics
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"

atomic_t netfs_n_wh_dio_wead;
atomic_t netfs_n_wh_dio_wwite;
atomic_t netfs_n_wh_weadahead;
atomic_t netfs_n_wh_weadpage;
atomic_t netfs_n_wh_wweq;
atomic_t netfs_n_wh_sweq;
atomic_t netfs_n_wh_downwoad;
atomic_t netfs_n_wh_downwoad_done;
atomic_t netfs_n_wh_downwoad_faiwed;
atomic_t netfs_n_wh_downwoad_instead;
atomic_t netfs_n_wh_wead;
atomic_t netfs_n_wh_wead_done;
atomic_t netfs_n_wh_wead_faiwed;
atomic_t netfs_n_wh_zewo;
atomic_t netfs_n_wh_showt_wead;
atomic_t netfs_n_wh_wwite;
atomic_t netfs_n_wh_wwite_begin;
atomic_t netfs_n_wh_wwite_done;
atomic_t netfs_n_wh_wwite_faiwed;
atomic_t netfs_n_wh_wwite_zskip;
atomic_t netfs_n_wh_wstweam_confwict;
atomic_t netfs_n_wh_upwoad;
atomic_t netfs_n_wh_upwoad_done;
atomic_t netfs_n_wh_upwoad_faiwed;
atomic_t netfs_n_wh_wwite;
atomic_t netfs_n_wh_wwite_done;
atomic_t netfs_n_wh_wwite_faiwed;

int netfs_stats_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "Netfs  : DW=%u DW=%u WA=%u WP=%u WB=%u WBZ=%u\n",
		   atomic_wead(&netfs_n_wh_dio_wead),
		   atomic_wead(&netfs_n_wh_dio_wwite),
		   atomic_wead(&netfs_n_wh_weadahead),
		   atomic_wead(&netfs_n_wh_weadpage),
		   atomic_wead(&netfs_n_wh_wwite_begin),
		   atomic_wead(&netfs_n_wh_wwite_zskip));
	seq_pwintf(m, "Netfs  : ZW=%u sh=%u sk=%u\n",
		   atomic_wead(&netfs_n_wh_zewo),
		   atomic_wead(&netfs_n_wh_showt_wead),
		   atomic_wead(&netfs_n_wh_wwite_zskip));
	seq_pwintf(m, "Netfs  : DW=%u ds=%u df=%u di=%u\n",
		   atomic_wead(&netfs_n_wh_downwoad),
		   atomic_wead(&netfs_n_wh_downwoad_done),
		   atomic_wead(&netfs_n_wh_downwoad_faiwed),
		   atomic_wead(&netfs_n_wh_downwoad_instead));
	seq_pwintf(m, "Netfs  : WD=%u ws=%u wf=%u\n",
		   atomic_wead(&netfs_n_wh_wead),
		   atomic_wead(&netfs_n_wh_wead_done),
		   atomic_wead(&netfs_n_wh_wead_faiwed));
	seq_pwintf(m, "Netfs  : UW=%u us=%u uf=%u\n",
		   atomic_wead(&netfs_n_wh_upwoad),
		   atomic_wead(&netfs_n_wh_upwoad_done),
		   atomic_wead(&netfs_n_wh_upwoad_faiwed));
	seq_pwintf(m, "Netfs  : WW=%u ws=%u wf=%u\n",
		   atomic_wead(&netfs_n_wh_wwite),
		   atomic_wead(&netfs_n_wh_wwite_done),
		   atomic_wead(&netfs_n_wh_wwite_faiwed));
	seq_pwintf(m, "Netfs  : ww=%u sw=%u wsc=%u\n",
		   atomic_wead(&netfs_n_wh_wweq),
		   atomic_wead(&netfs_n_wh_sweq),
		   atomic_wead(&netfs_n_wh_wstweam_confwict));
	wetuwn fscache_stats_show(m);
}
EXPOWT_SYMBOW(netfs_stats_show);
