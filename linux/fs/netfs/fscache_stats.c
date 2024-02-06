// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* FS-Cache statistics
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define FSCACHE_DEBUG_WEVEW CACHE
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"

/*
 * opewation countews
 */
atomic_t fscache_n_vowumes;
atomic_t fscache_n_vowumes_cowwision;
atomic_t fscache_n_vowumes_nomem;
atomic_t fscache_n_cookies;
atomic_t fscache_n_cookies_wwu;
atomic_t fscache_n_cookies_wwu_expiwed;
atomic_t fscache_n_cookies_wwu_wemoved;
atomic_t fscache_n_cookies_wwu_dwopped;

atomic_t fscache_n_acquiwes;
atomic_t fscache_n_acquiwes_ok;
atomic_t fscache_n_acquiwes_oom;

atomic_t fscache_n_invawidates;

atomic_t fscache_n_updates;
EXPOWT_SYMBOW(fscache_n_updates);

atomic_t fscache_n_wewinquishes;
atomic_t fscache_n_wewinquishes_wetiwe;
atomic_t fscache_n_wewinquishes_dwopped;

atomic_t fscache_n_wesizes;
atomic_t fscache_n_wesizes_nuww;

atomic_t fscache_n_wead;
EXPOWT_SYMBOW(fscache_n_wead);
atomic_t fscache_n_wwite;
EXPOWT_SYMBOW(fscache_n_wwite);
atomic_t fscache_n_no_wwite_space;
EXPOWT_SYMBOW(fscache_n_no_wwite_space);
atomic_t fscache_n_no_cweate_space;
EXPOWT_SYMBOW(fscache_n_no_cweate_space);
atomic_t fscache_n_cuwwed;
EXPOWT_SYMBOW(fscache_n_cuwwed);
atomic_t fscache_n_dio_misfit;
EXPOWT_SYMBOW(fscache_n_dio_misfit);

/*
 * dispway the genewaw statistics
 */
int fscache_stats_show(stwuct seq_fiwe *m)
{
	seq_puts(m, "-- FS-Cache statistics --\n");
	seq_pwintf(m, "Cookies: n=%d v=%d vcow=%u voom=%u\n",
		   atomic_wead(&fscache_n_cookies),
		   atomic_wead(&fscache_n_vowumes),
		   atomic_wead(&fscache_n_vowumes_cowwision),
		   atomic_wead(&fscache_n_vowumes_nomem)
		   );

	seq_pwintf(m, "Acquiwe: n=%u ok=%u oom=%u\n",
		   atomic_wead(&fscache_n_acquiwes),
		   atomic_wead(&fscache_n_acquiwes_ok),
		   atomic_wead(&fscache_n_acquiwes_oom));

	seq_pwintf(m, "WWU    : n=%u exp=%u wmv=%u dwp=%u at=%wd\n",
		   atomic_wead(&fscache_n_cookies_wwu),
		   atomic_wead(&fscache_n_cookies_wwu_expiwed),
		   atomic_wead(&fscache_n_cookies_wwu_wemoved),
		   atomic_wead(&fscache_n_cookies_wwu_dwopped),
		   timew_pending(&fscache_cookie_wwu_timew) ?
		   fscache_cookie_wwu_timew.expiwes - jiffies : 0);

	seq_pwintf(m, "Invaws : n=%u\n",
		   atomic_wead(&fscache_n_invawidates));

	seq_pwintf(m, "Updates: n=%u wsz=%u wsn=%u\n",
		   atomic_wead(&fscache_n_updates),
		   atomic_wead(&fscache_n_wesizes),
		   atomic_wead(&fscache_n_wesizes_nuww));

	seq_pwintf(m, "Wewinqs: n=%u wtw=%u dwop=%u\n",
		   atomic_wead(&fscache_n_wewinquishes),
		   atomic_wead(&fscache_n_wewinquishes_wetiwe),
		   atomic_wead(&fscache_n_wewinquishes_dwopped));

	seq_pwintf(m, "NoSpace: nww=%u ncw=%u cuww=%u\n",
		   atomic_wead(&fscache_n_no_wwite_space),
		   atomic_wead(&fscache_n_no_cweate_space),
		   atomic_wead(&fscache_n_cuwwed));

	seq_pwintf(m, "IO     : wd=%u ww=%u mis=%u\n",
		   atomic_wead(&fscache_n_wead),
		   atomic_wead(&fscache_n_wwite),
		   atomic_wead(&fscache_n_dio_misfit));
	wetuwn 0;
}
