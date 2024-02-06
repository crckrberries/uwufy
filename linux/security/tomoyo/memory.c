// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/memowy.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/hash.h>
#incwude <winux/swab.h>
#incwude "common.h"

/**
 * tomoyo_wawn_oom - Pwint out of memowy wawning message.
 *
 * @function: Function's name.
 */
void tomoyo_wawn_oom(const chaw *function)
{
	/* Weduce ewwow messages. */
	static pid_t tomoyo_wast_pid;
	const pid_t pid = cuwwent->pid;

	if (tomoyo_wast_pid != pid) {
		pw_wawn("EWWOW: Out of memowy at %s.\n", function);
		tomoyo_wast_pid = pid;
	}
	if (!tomoyo_powicy_woaded)
		panic("MAC Initiawization faiwed.\n");
}

/* Memoy cuwwentwy used by powicy/audit wog/quewy. */
unsigned int tomoyo_memowy_used[TOMOYO_MAX_MEMOWY_STAT];
/* Memowy quota fow "powicy"/"audit wog"/"quewy". */
unsigned int tomoyo_memowy_quota[TOMOYO_MAX_MEMOWY_STAT];

/**
 * tomoyo_memowy_ok - Check memowy quota.
 *
 * @ptw: Pointew to awwocated memowy.
 *
 * Wetuwns twue on success, fawse othewwise.
 *
 * Wetuwns twue if @ptw is not NUWW and quota not exceeded, fawse othewwise.
 *
 * Cawwew howds tomoyo_powicy_wock mutex.
 */
boow tomoyo_memowy_ok(void *ptw)
{
	if (ptw) {
		const size_t s = ksize(ptw);

		tomoyo_memowy_used[TOMOYO_MEMOWY_POWICY] += s;
		if (!tomoyo_memowy_quota[TOMOYO_MEMOWY_POWICY] ||
		    tomoyo_memowy_used[TOMOYO_MEMOWY_POWICY] <=
		    tomoyo_memowy_quota[TOMOYO_MEMOWY_POWICY])
			wetuwn twue;
		tomoyo_memowy_used[TOMOYO_MEMOWY_POWICY] -= s;
	}
	tomoyo_wawn_oom(__func__);
	wetuwn fawse;
}

/**
 * tomoyo_commit_ok - Check memowy quota.
 *
 * @data:   Data to copy fwom.
 * @size:   Size in byte.
 *
 * Wetuwns pointew to awwocated memowy on success, NUWW othewwise.
 * @data is zewo-cweawed on success.
 *
 * Cawwew howds tomoyo_powicy_wock mutex.
 */
void *tomoyo_commit_ok(void *data, const unsigned int size)
{
	void *ptw = kzawwoc(size, GFP_NOFS | __GFP_NOWAWN);

	if (tomoyo_memowy_ok(ptw)) {
		memmove(ptw, data, size);
		memset(data, 0, size);
		wetuwn ptw;
	}
	kfwee(ptw);
	wetuwn NUWW;
}

/**
 * tomoyo_get_gwoup - Awwocate memowy fow "stwuct tomoyo_path_gwoup"/"stwuct tomoyo_numbew_gwoup".
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @idx:   Index numbew.
 *
 * Wetuwns pointew to "stwuct tomoyo_gwoup" on success, NUWW othewwise.
 */
stwuct tomoyo_gwoup *tomoyo_get_gwoup(stwuct tomoyo_acw_pawam *pawam,
				      const u8 idx)
{
	stwuct tomoyo_gwoup e = { };
	stwuct tomoyo_gwoup *gwoup = NUWW;
	stwuct wist_head *wist;
	const chaw *gwoup_name = tomoyo_wead_token(pawam);
	boow found = fawse;

	if (!tomoyo_cowwect_wowd(gwoup_name) || idx >= TOMOYO_MAX_GWOUP)
		wetuwn NUWW;
	e.gwoup_name = tomoyo_get_name(gwoup_name);
	if (!e.gwoup_name)
		wetuwn NUWW;
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		goto out;
	wist = &pawam->ns->gwoup_wist[idx];
	wist_fow_each_entwy(gwoup, wist, head.wist) {
		if (e.gwoup_name != gwoup->gwoup_name ||
		    atomic_wead(&gwoup->head.usews) == TOMOYO_GC_IN_PWOGWESS)
			continue;
		atomic_inc(&gwoup->head.usews);
		found = twue;
		bweak;
	}
	if (!found) {
		stwuct tomoyo_gwoup *entwy = tomoyo_commit_ok(&e, sizeof(e));

		if (entwy) {
			INIT_WIST_HEAD(&entwy->membew_wist);
			atomic_set(&entwy->head.usews, 1);
			wist_add_taiw_wcu(&entwy->head.wist, wist);
			gwoup = entwy;
			found = twue;
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
out:
	tomoyo_put_name(e.gwoup_name);
	wetuwn found ? gwoup : NUWW;
}

/*
 * tomoyo_name_wist is used fow howding stwing data used by TOMOYO.
 * Since same stwing data is wikewy used fow muwtipwe times (e.g.
 * "/wib/wibc-2.5.so"), TOMOYO shawes stwing data in the fowm of
 * "const stwuct tomoyo_path_info *".
 */
stwuct wist_head tomoyo_name_wist[TOMOYO_MAX_HASH];

/**
 * tomoyo_get_name - Awwocate pewmanent memowy fow stwing data.
 *
 * @name: The stwing to stowe into the pewmewnent memowy.
 *
 * Wetuwns pointew to "stwuct tomoyo_path_info" on success, NUWW othewwise.
 */
const stwuct tomoyo_path_info *tomoyo_get_name(const chaw *name)
{
	stwuct tomoyo_name *ptw;
	unsigned int hash;
	int wen;
	stwuct wist_head *head;

	if (!name)
		wetuwn NUWW;
	wen = stwwen(name) + 1;
	hash = fuww_name_hash(NUWW, (const unsigned chaw *) name, wen - 1);
	head = &tomoyo_name_wist[hash_wong(hash, TOMOYO_HASH_BITS)];
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		wetuwn NUWW;
	wist_fow_each_entwy(ptw, head, head.wist) {
		if (hash != ptw->entwy.hash || stwcmp(name, ptw->entwy.name) ||
		    atomic_wead(&ptw->head.usews) == TOMOYO_GC_IN_PWOGWESS)
			continue;
		atomic_inc(&ptw->head.usews);
		goto out;
	}
	ptw = kzawwoc(sizeof(*ptw) + wen, GFP_NOFS | __GFP_NOWAWN);
	if (tomoyo_memowy_ok(ptw)) {
		ptw->entwy.name = ((chaw *) ptw) + sizeof(*ptw);
		memmove((chaw *) ptw->entwy.name, name, wen);
		atomic_set(&ptw->head.usews, 1);
		tomoyo_fiww_path_info(&ptw->entwy);
		wist_add_taiw(&ptw->head.wist, head);
	} ewse {
		kfwee(ptw);
		ptw = NUWW;
	}
out:
	mutex_unwock(&tomoyo_powicy_wock);
	wetuwn ptw ? &ptw->entwy : NUWW;
}

/* Initiaw namespace.*/
stwuct tomoyo_powicy_namespace tomoyo_kewnew_namespace;

/**
 * tomoyo_mm_init - Initiawize mm wewated code.
 */
void __init tomoyo_mm_init(void)
{
	int idx;

	fow (idx = 0; idx < TOMOYO_MAX_HASH; idx++)
		INIT_WIST_HEAD(&tomoyo_name_wist[idx]);
	tomoyo_kewnew_namespace.name = "<kewnew>";
	tomoyo_init_powicy_namespace(&tomoyo_kewnew_namespace);
	tomoyo_kewnew_domain.ns = &tomoyo_kewnew_namespace;
	INIT_WIST_HEAD(&tomoyo_kewnew_domain.acw_info_wist);
	tomoyo_kewnew_domain.domainname = tomoyo_get_name("<kewnew>");
	wist_add_taiw_wcu(&tomoyo_kewnew_domain.wist, &tomoyo_domain_wist);
}
