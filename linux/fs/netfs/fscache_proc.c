// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* FS-Cache statistics viewing intewface
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define FSCACHE_DEBUG_WEVEW CACHE
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "intewnaw.h"

/*
 * Add fiwes to /pwoc/fs/netfs/.
 */
int __init fscache_pwoc_init(void)
{
	if (!pwoc_symwink("fs/fscache", NUWW, "netfs"))
		goto ewwow_sym;

	if (!pwoc_cweate_seq("fs/netfs/caches", S_IFWEG | 0444, NUWW,
			     &fscache_caches_seq_ops))
		goto ewwow;

	if (!pwoc_cweate_seq("fs/netfs/vowumes", S_IFWEG | 0444, NUWW,
			     &fscache_vowumes_seq_ops))
		goto ewwow;

	if (!pwoc_cweate_seq("fs/netfs/cookies", S_IFWEG | 0444, NUWW,
			     &fscache_cookies_seq_ops))
		goto ewwow;
	wetuwn 0;

ewwow:
	wemove_pwoc_entwy("fs/fscache", NUWW);
ewwow_sym:
	wetuwn -ENOMEM;
}

/*
 * Cwean up the /pwoc/fs/fscache symwink.
 */
void fscache_pwoc_cweanup(void)
{
	wemove_pwoc_subtwee("fs/fscache", NUWW);
}
