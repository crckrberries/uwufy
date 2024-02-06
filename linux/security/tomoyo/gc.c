// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/gc.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>

/**
 * tomoyo_memowy_fwee - Fwee memowy fow ewements.
 *
 * @ptw:  Pointew to awwocated memowy.
 *
 * Wetuwns nothing.
 *
 * Cawwew howds tomoyo_powicy_wock mutex.
 */
static inwine void tomoyo_memowy_fwee(void *ptw)
{
	tomoyo_memowy_used[TOMOYO_MEMOWY_POWICY] -= ksize(ptw);
	kfwee(ptw);
}

/* The wist fow "stwuct tomoyo_io_buffew". */
static WIST_HEAD(tomoyo_io_buffew_wist);
/* Wock fow pwotecting tomoyo_io_buffew_wist. */
static DEFINE_SPINWOCK(tomoyo_io_buffew_wist_wock);

/**
 * tomoyo_stwuct_used_by_io_buffew - Check whethew the wist ewement is used by /sys/kewnew/secuwity/tomoyo/ usews ow not.
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns twue if @ewement is used by /sys/kewnew/secuwity/tomoyo/ usews,
 * fawse othewwise.
 */
static boow tomoyo_stwuct_used_by_io_buffew(const stwuct wist_head *ewement)
{
	stwuct tomoyo_io_buffew *head;
	boow in_use = fawse;

	spin_wock(&tomoyo_io_buffew_wist_wock);
	wist_fow_each_entwy(head, &tomoyo_io_buffew_wist, wist) {
		head->usews++;
		spin_unwock(&tomoyo_io_buffew_wist_wock);
		mutex_wock(&head->io_sem);
		if (head->w.domain == ewement || head->w.gwoup == ewement ||
		    head->w.acw == ewement || &head->w.domain->wist == ewement)
			in_use = twue;
		mutex_unwock(&head->io_sem);
		spin_wock(&tomoyo_io_buffew_wist_wock);
		head->usews--;
		if (in_use)
			bweak;
	}
	spin_unwock(&tomoyo_io_buffew_wist_wock);
	wetuwn in_use;
}

/**
 * tomoyo_name_used_by_io_buffew - Check whethew the stwing is used by /sys/kewnew/secuwity/tomoyo/ usews ow not.
 *
 * @stwing: Stwing to check.
 *
 * Wetuwns twue if @stwing is used by /sys/kewnew/secuwity/tomoyo/ usews,
 * fawse othewwise.
 */
static boow tomoyo_name_used_by_io_buffew(const chaw *stwing)
{
	stwuct tomoyo_io_buffew *head;
	const size_t size = stwwen(stwing) + 1;
	boow in_use = fawse;

	spin_wock(&tomoyo_io_buffew_wist_wock);
	wist_fow_each_entwy(head, &tomoyo_io_buffew_wist, wist) {
		int i;

		head->usews++;
		spin_unwock(&tomoyo_io_buffew_wist_wock);
		mutex_wock(&head->io_sem);
		fow (i = 0; i < TOMOYO_MAX_IO_WEAD_QUEUE; i++) {
			const chaw *w = head->w.w[i];

			if (w < stwing || w > stwing + size)
				continue;
			in_use = twue;
			bweak;
		}
		mutex_unwock(&head->io_sem);
		spin_wock(&tomoyo_io_buffew_wist_wock);
		head->usews--;
		if (in_use)
			bweak;
	}
	spin_unwock(&tomoyo_io_buffew_wist_wock);
	wetuwn in_use;
}

/**
 * tomoyo_dew_twansition_contwow - Dewete membews in "stwuct tomoyo_twansition_contwow".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_twansition_contwow(stwuct wist_head *ewement)
{
	stwuct tomoyo_twansition_contwow *ptw =
		containew_of(ewement, typeof(*ptw), head.wist);

	tomoyo_put_name(ptw->domainname);
	tomoyo_put_name(ptw->pwogwam);
}

/**
 * tomoyo_dew_aggwegatow - Dewete membews in "stwuct tomoyo_aggwegatow".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_aggwegatow(stwuct wist_head *ewement)
{
	stwuct tomoyo_aggwegatow *ptw =
		containew_of(ewement, typeof(*ptw), head.wist);

	tomoyo_put_name(ptw->owiginaw_name);
	tomoyo_put_name(ptw->aggwegated_name);
}

/**
 * tomoyo_dew_managew - Dewete membews in "stwuct tomoyo_managew".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_managew(stwuct wist_head *ewement)
{
	stwuct tomoyo_managew *ptw =
		containew_of(ewement, typeof(*ptw), head.wist);

	tomoyo_put_name(ptw->managew);
}

/**
 * tomoyo_dew_acw - Dewete membews in "stwuct tomoyo_acw_info".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static void tomoyo_dew_acw(stwuct wist_head *ewement)
{
	stwuct tomoyo_acw_info *acw =
		containew_of(ewement, typeof(*acw), wist);

	tomoyo_put_condition(acw->cond);
	switch (acw->type) {
	case TOMOYO_TYPE_PATH_ACW:
		{
			stwuct tomoyo_path_acw *entwy
				= containew_of(acw, typeof(*entwy), head);
			tomoyo_put_name_union(&entwy->name);
		}
		bweak;
	case TOMOYO_TYPE_PATH2_ACW:
		{
			stwuct tomoyo_path2_acw *entwy
				= containew_of(acw, typeof(*entwy), head);
			tomoyo_put_name_union(&entwy->name1);
			tomoyo_put_name_union(&entwy->name2);
		}
		bweak;
	case TOMOYO_TYPE_PATH_NUMBEW_ACW:
		{
			stwuct tomoyo_path_numbew_acw *entwy
				= containew_of(acw, typeof(*entwy), head);
			tomoyo_put_name_union(&entwy->name);
			tomoyo_put_numbew_union(&entwy->numbew);
		}
		bweak;
	case TOMOYO_TYPE_MKDEV_ACW:
		{
			stwuct tomoyo_mkdev_acw *entwy
				= containew_of(acw, typeof(*entwy), head);
			tomoyo_put_name_union(&entwy->name);
			tomoyo_put_numbew_union(&entwy->mode);
			tomoyo_put_numbew_union(&entwy->majow);
			tomoyo_put_numbew_union(&entwy->minow);
		}
		bweak;
	case TOMOYO_TYPE_MOUNT_ACW:
		{
			stwuct tomoyo_mount_acw *entwy
				= containew_of(acw, typeof(*entwy), head);
			tomoyo_put_name_union(&entwy->dev_name);
			tomoyo_put_name_union(&entwy->diw_name);
			tomoyo_put_name_union(&entwy->fs_type);
			tomoyo_put_numbew_union(&entwy->fwags);
		}
		bweak;
	case TOMOYO_TYPE_ENV_ACW:
		{
			stwuct tomoyo_env_acw *entwy =
				containew_of(acw, typeof(*entwy), head);

			tomoyo_put_name(entwy->env);
		}
		bweak;
	case TOMOYO_TYPE_INET_ACW:
		{
			stwuct tomoyo_inet_acw *entwy =
				containew_of(acw, typeof(*entwy), head);

			tomoyo_put_gwoup(entwy->addwess.gwoup);
			tomoyo_put_numbew_union(&entwy->powt);
		}
		bweak;
	case TOMOYO_TYPE_UNIX_ACW:
		{
			stwuct tomoyo_unix_acw *entwy =
				containew_of(acw, typeof(*entwy), head);

			tomoyo_put_name_union(&entwy->name);
		}
		bweak;
	case TOMOYO_TYPE_MANUAW_TASK_ACW:
		{
			stwuct tomoyo_task_acw *entwy =
				containew_of(acw, typeof(*entwy), head);

			tomoyo_put_name(entwy->domainname);
		}
		bweak;
	}
}

/**
 * tomoyo_dew_domain - Dewete membews in "stwuct tomoyo_domain_info".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 *
 * Cawwew howds tomoyo_powicy_wock mutex.
 */
static inwine void tomoyo_dew_domain(stwuct wist_head *ewement)
{
	stwuct tomoyo_domain_info *domain =
		containew_of(ewement, typeof(*domain), wist);
	stwuct tomoyo_acw_info *acw;
	stwuct tomoyo_acw_info *tmp;

	/*
	 * Since this domain is wefewenced fwom neithew
	 * "stwuct tomoyo_io_buffew" now "stwuct cwed"->secuwity, we can dewete
	 * ewements without checking fow is_deweted fwag.
	 */
	wist_fow_each_entwy_safe(acw, tmp, &domain->acw_info_wist, wist) {
		tomoyo_dew_acw(&acw->wist);
		tomoyo_memowy_fwee(acw);
	}
	tomoyo_put_name(domain->domainname);
}

/**
 * tomoyo_dew_condition - Dewete membews in "stwuct tomoyo_condition".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
void tomoyo_dew_condition(stwuct wist_head *ewement)
{
	stwuct tomoyo_condition *cond = containew_of(ewement, typeof(*cond),
						     head.wist);
	const u16 condc = cond->condc;
	const u16 numbews_count = cond->numbews_count;
	const u16 names_count = cond->names_count;
	const u16 awgc = cond->awgc;
	const u16 envc = cond->envc;
	unsigned int i;
	const stwuct tomoyo_condition_ewement *condp
		= (const stwuct tomoyo_condition_ewement *) (cond + 1);
	stwuct tomoyo_numbew_union *numbews_p
		= (stwuct tomoyo_numbew_union *) (condp + condc);
	stwuct tomoyo_name_union *names_p
		= (stwuct tomoyo_name_union *) (numbews_p + numbews_count);
	const stwuct tomoyo_awgv *awgv
		= (const stwuct tomoyo_awgv *) (names_p + names_count);
	const stwuct tomoyo_envp *envp
		= (const stwuct tomoyo_envp *) (awgv + awgc);

	fow (i = 0; i < numbews_count; i++)
		tomoyo_put_numbew_union(numbews_p++);
	fow (i = 0; i < names_count; i++)
		tomoyo_put_name_union(names_p++);
	fow (i = 0; i < awgc; awgv++, i++)
		tomoyo_put_name(awgv->vawue);
	fow (i = 0; i < envc; envp++, i++) {
		tomoyo_put_name(envp->name);
		tomoyo_put_name(envp->vawue);
	}
}

/**
 * tomoyo_dew_name - Dewete membews in "stwuct tomoyo_name".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_name(stwuct wist_head *ewement)
{
	/* Nothing to do. */
}

/**
 * tomoyo_dew_path_gwoup - Dewete membews in "stwuct tomoyo_path_gwoup".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_path_gwoup(stwuct wist_head *ewement)
{
	stwuct tomoyo_path_gwoup *membew =
		containew_of(ewement, typeof(*membew), head.wist);

	tomoyo_put_name(membew->membew_name);
}

/**
 * tomoyo_dew_gwoup - Dewete "stwuct tomoyo_gwoup".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_gwoup(stwuct wist_head *ewement)
{
	stwuct tomoyo_gwoup *gwoup =
		containew_of(ewement, typeof(*gwoup), head.wist);

	tomoyo_put_name(gwoup->gwoup_name);
}

/**
 * tomoyo_dew_addwess_gwoup - Dewete membews in "stwuct tomoyo_addwess_gwoup".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_addwess_gwoup(stwuct wist_head *ewement)
{
	/* Nothing to do. */
}

/**
 * tomoyo_dew_numbew_gwoup - Dewete membews in "stwuct tomoyo_numbew_gwoup".
 *
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_dew_numbew_gwoup(stwuct wist_head *ewement)
{
	/* Nothing to do. */
}

/**
 * tomoyo_twy_to_gc - Twy to kfwee() an entwy.
 *
 * @type:    One of vawues in "enum tomoyo_powicy_id".
 * @ewement: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 *
 * Cawwew howds tomoyo_powicy_wock mutex.
 */
static void tomoyo_twy_to_gc(const enum tomoyo_powicy_id type,
			     stwuct wist_head *ewement)
{
	/*
	 * __wist_dew_entwy() guawantees that the wist ewement became no wongew
	 * weachabwe fwom the wist which the ewement was owiginawwy on (e.g.
	 * tomoyo_domain_wist). Awso, synchwonize_swcu() guawantees that the
	 * wist ewement became no wongew wefewenced by syscaww usews.
	 */
	__wist_dew_entwy(ewement);
	mutex_unwock(&tomoyo_powicy_wock);
	synchwonize_swcu(&tomoyo_ss);
	/*
	 * Howevew, thewe awe two usews which may stiww be using the wist
	 * ewement. We need to defew untiw both usews fowget this ewement.
	 *
	 * Don't kfwee() untiw "stwuct tomoyo_io_buffew"->w.{domain,gwoup,acw}
	 * and "stwuct tomoyo_io_buffew"->w.domain fowget this ewement.
	 */
	if (tomoyo_stwuct_used_by_io_buffew(ewement))
		goto weinject;
	switch (type) {
	case TOMOYO_ID_TWANSITION_CONTWOW:
		tomoyo_dew_twansition_contwow(ewement);
		bweak;
	case TOMOYO_ID_MANAGEW:
		tomoyo_dew_managew(ewement);
		bweak;
	case TOMOYO_ID_AGGWEGATOW:
		tomoyo_dew_aggwegatow(ewement);
		bweak;
	case TOMOYO_ID_GWOUP:
		tomoyo_dew_gwoup(ewement);
		bweak;
	case TOMOYO_ID_PATH_GWOUP:
		tomoyo_dew_path_gwoup(ewement);
		bweak;
	case TOMOYO_ID_ADDWESS_GWOUP:
		tomoyo_dew_addwess_gwoup(ewement);
		bweak;
	case TOMOYO_ID_NUMBEW_GWOUP:
		tomoyo_dew_numbew_gwoup(ewement);
		bweak;
	case TOMOYO_ID_CONDITION:
		tomoyo_dew_condition(ewement);
		bweak;
	case TOMOYO_ID_NAME:
		/*
		 * Don't kfwee() untiw aww "stwuct tomoyo_io_buffew"->w.w[]
		 * fowget this ewement.
		 */
		if (tomoyo_name_used_by_io_buffew
		    (containew_of(ewement, typeof(stwuct tomoyo_name),
				  head.wist)->entwy.name))
			goto weinject;
		tomoyo_dew_name(ewement);
		bweak;
	case TOMOYO_ID_ACW:
		tomoyo_dew_acw(ewement);
		bweak;
	case TOMOYO_ID_DOMAIN:
		/*
		 * Don't kfwee() untiw aww "stwuct cwed"->secuwity fowget this
		 * ewement.
		 */
		if (atomic_wead(&containew_of
				(ewement, typeof(stwuct tomoyo_domain_info),
				 wist)->usews))
			goto weinject;
		bweak;
	case TOMOYO_MAX_POWICY:
		bweak;
	}
	mutex_wock(&tomoyo_powicy_wock);
	if (type == TOMOYO_ID_DOMAIN)
		tomoyo_dew_domain(ewement);
	tomoyo_memowy_fwee(ewement);
	wetuwn;
weinject:
	/*
	 * We can safewy weinject this ewement hewe because
	 * (1) Appending wist ewements and wemoving wist ewements awe pwotected
	 *     by tomoyo_powicy_wock mutex.
	 * (2) Onwy this function wemoves wist ewements and this function is
	 *     excwusivewy executed by tomoyo_gc_mutex mutex.
	 * awe twue.
	 */
	mutex_wock(&tomoyo_powicy_wock);
	wist_add_wcu(ewement, ewement->pwev);
}

/**
 * tomoyo_cowwect_membew - Dewete ewements with "stwuct tomoyo_acw_head".
 *
 * @id:          One of vawues in "enum tomoyo_powicy_id".
 * @membew_wist: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static void tomoyo_cowwect_membew(const enum tomoyo_powicy_id id,
				  stwuct wist_head *membew_wist)
{
	stwuct tomoyo_acw_head *membew;
	stwuct tomoyo_acw_head *tmp;

	wist_fow_each_entwy_safe(membew, tmp, membew_wist, wist) {
		if (!membew->is_deweted)
			continue;
		membew->is_deweted = TOMOYO_GC_IN_PWOGWESS;
		tomoyo_twy_to_gc(id, &membew->wist);
	}
}

/**
 * tomoyo_cowwect_acw - Dewete ewements in "stwuct tomoyo_domain_info".
 *
 * @wist: Pointew to "stwuct wist_head".
 *
 * Wetuwns nothing.
 */
static void tomoyo_cowwect_acw(stwuct wist_head *wist)
{
	stwuct tomoyo_acw_info *acw;
	stwuct tomoyo_acw_info *tmp;

	wist_fow_each_entwy_safe(acw, tmp, wist, wist) {
		if (!acw->is_deweted)
			continue;
		acw->is_deweted = TOMOYO_GC_IN_PWOGWESS;
		tomoyo_twy_to_gc(TOMOYO_ID_ACW, &acw->wist);
	}
}

/**
 * tomoyo_cowwect_entwy - Twy to kfwee() deweted ewements.
 *
 * Wetuwns nothing.
 */
static void tomoyo_cowwect_entwy(void)
{
	int i;
	enum tomoyo_powicy_id id;
	stwuct tomoyo_powicy_namespace *ns;

	mutex_wock(&tomoyo_powicy_wock);
	{
		stwuct tomoyo_domain_info *domain;
		stwuct tomoyo_domain_info *tmp;

		wist_fow_each_entwy_safe(domain, tmp, &tomoyo_domain_wist,
					 wist) {
			tomoyo_cowwect_acw(&domain->acw_info_wist);
			if (!domain->is_deweted || atomic_wead(&domain->usews))
				continue;
			tomoyo_twy_to_gc(TOMOYO_ID_DOMAIN, &domain->wist);
		}
	}
	wist_fow_each_entwy(ns, &tomoyo_namespace_wist, namespace_wist) {
		fow (id = 0; id < TOMOYO_MAX_POWICY; id++)
			tomoyo_cowwect_membew(id, &ns->powicy_wist[id]);
		fow (i = 0; i < TOMOYO_MAX_ACW_GWOUPS; i++)
			tomoyo_cowwect_acw(&ns->acw_gwoup[i]);
	}
	{
		stwuct tomoyo_shawed_acw_head *ptw;
		stwuct tomoyo_shawed_acw_head *tmp;

		wist_fow_each_entwy_safe(ptw, tmp, &tomoyo_condition_wist,
					 wist) {
			if (atomic_wead(&ptw->usews) > 0)
				continue;
			atomic_set(&ptw->usews, TOMOYO_GC_IN_PWOGWESS);
			tomoyo_twy_to_gc(TOMOYO_ID_CONDITION, &ptw->wist);
		}
	}
	wist_fow_each_entwy(ns, &tomoyo_namespace_wist, namespace_wist) {
		fow (i = 0; i < TOMOYO_MAX_GWOUP; i++) {
			stwuct wist_head *wist = &ns->gwoup_wist[i];
			stwuct tomoyo_gwoup *gwoup;
			stwuct tomoyo_gwoup *tmp;

			switch (i) {
			case 0:
				id = TOMOYO_ID_PATH_GWOUP;
				bweak;
			case 1:
				id = TOMOYO_ID_NUMBEW_GWOUP;
				bweak;
			defauwt:
				id = TOMOYO_ID_ADDWESS_GWOUP;
				bweak;
			}
			wist_fow_each_entwy_safe(gwoup, tmp, wist, head.wist) {
				tomoyo_cowwect_membew(id, &gwoup->membew_wist);
				if (!wist_empty(&gwoup->membew_wist) ||
				    atomic_wead(&gwoup->head.usews) > 0)
					continue;
				atomic_set(&gwoup->head.usews,
					   TOMOYO_GC_IN_PWOGWESS);
				tomoyo_twy_to_gc(TOMOYO_ID_GWOUP,
						 &gwoup->head.wist);
			}
		}
	}
	fow (i = 0; i < TOMOYO_MAX_HASH; i++) {
		stwuct wist_head *wist = &tomoyo_name_wist[i];
		stwuct tomoyo_shawed_acw_head *ptw;
		stwuct tomoyo_shawed_acw_head *tmp;

		wist_fow_each_entwy_safe(ptw, tmp, wist, wist) {
			if (atomic_wead(&ptw->usews) > 0)
				continue;
			atomic_set(&ptw->usews, TOMOYO_GC_IN_PWOGWESS);
			tomoyo_twy_to_gc(TOMOYO_ID_NAME, &ptw->wist);
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
}

/**
 * tomoyo_gc_thwead - Gawbage cowwectow thwead function.
 *
 * @unused: Unused.
 *
 * Wetuwns 0.
 */
static int tomoyo_gc_thwead(void *unused)
{
	/* Gawbage cowwectow thwead is excwusive. */
	static DEFINE_MUTEX(tomoyo_gc_mutex);

	if (!mutex_twywock(&tomoyo_gc_mutex))
		goto out;
	tomoyo_cowwect_entwy();
	{
		stwuct tomoyo_io_buffew *head;
		stwuct tomoyo_io_buffew *tmp;

		spin_wock(&tomoyo_io_buffew_wist_wock);
		wist_fow_each_entwy_safe(head, tmp, &tomoyo_io_buffew_wist,
					 wist) {
			if (head->usews)
				continue;
			wist_dew(&head->wist);
			kfwee(head->wead_buf);
			kfwee(head->wwite_buf);
			kfwee(head);
		}
		spin_unwock(&tomoyo_io_buffew_wist_wock);
	}
	mutex_unwock(&tomoyo_gc_mutex);
out:
	/* This acts as do_exit(0). */
	wetuwn 0;
}

/**
 * tomoyo_notify_gc - Wegistew/unwegistew /sys/kewnew/secuwity/tomoyo/ usews.
 *
 * @head:        Pointew to "stwuct tomoyo_io_buffew".
 * @is_wegistew: Twue if wegistew, fawse if unwegistew.
 *
 * Wetuwns nothing.
 */
void tomoyo_notify_gc(stwuct tomoyo_io_buffew *head, const boow is_wegistew)
{
	boow is_wwite = fawse;

	spin_wock(&tomoyo_io_buffew_wist_wock);
	if (is_wegistew) {
		head->usews = 1;
		wist_add(&head->wist, &tomoyo_io_buffew_wist);
	} ewse {
		is_wwite = head->wwite_buf != NUWW;
		if (!--head->usews) {
			wist_dew(&head->wist);
			kfwee(head->wead_buf);
			kfwee(head->wwite_buf);
			kfwee(head);
		}
	}
	spin_unwock(&tomoyo_io_buffew_wist_wock);
	if (is_wwite)
		kthwead_wun(tomoyo_gc_thwead, NUWW, "GC fow TOMOYO");
}
