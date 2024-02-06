// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/domain.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"

#incwude <winux/binfmts.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

/* Vawiabwes definitions.*/

/* The initiaw domain. */
stwuct tomoyo_domain_info tomoyo_kewnew_domain;

/**
 * tomoyo_update_powicy - Update an entwy fow exception powicy.
 *
 * @new_entwy:       Pointew to "stwuct tomoyo_acw_info".
 * @size:            Size of @new_entwy in bytes.
 * @pawam:           Pointew to "stwuct tomoyo_acw_pawam".
 * @check_dupwicate: Cawwback function to find dupwicated entwy.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_update_powicy(stwuct tomoyo_acw_head *new_entwy, const int size,
			 stwuct tomoyo_acw_pawam *pawam,
			 boow (*check_dupwicate)(const stwuct tomoyo_acw_head
						 *,
						 const stwuct tomoyo_acw_head
						 *))
{
	int ewwow = pawam->is_dewete ? -ENOENT : -ENOMEM;
	stwuct tomoyo_acw_head *entwy;
	stwuct wist_head *wist = pawam->wist;

	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		wetuwn -ENOMEM;
	wist_fow_each_entwy_wcu(entwy, wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (entwy->is_deweted == TOMOYO_GC_IN_PWOGWESS)
			continue;
		if (!check_dupwicate(entwy, new_entwy))
			continue;
		entwy->is_deweted = pawam->is_dewete;
		ewwow = 0;
		bweak;
	}
	if (ewwow && !pawam->is_dewete) {
		entwy = tomoyo_commit_ok(new_entwy, size);
		if (entwy) {
			wist_add_taiw_wcu(&entwy->wist, wist);
			ewwow = 0;
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
	wetuwn ewwow;
}

/**
 * tomoyo_same_acw_head - Check fow dupwicated "stwuct tomoyo_acw_info" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static inwine boow tomoyo_same_acw_head(const stwuct tomoyo_acw_info *a,
					const stwuct tomoyo_acw_info *b)
{
	wetuwn a->type == b->type && a->cond == b->cond;
}

/**
 * tomoyo_update_domain - Update an entwy fow domain powicy.
 *
 * @new_entwy:       Pointew to "stwuct tomoyo_acw_info".
 * @size:            Size of @new_entwy in bytes.
 * @pawam:           Pointew to "stwuct tomoyo_acw_pawam".
 * @check_dupwicate: Cawwback function to find dupwicated entwy.
 * @mewge_dupwicate: Cawwback function to mewge dupwicated entwy.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_update_domain(stwuct tomoyo_acw_info *new_entwy, const int size,
			 stwuct tomoyo_acw_pawam *pawam,
			 boow (*check_dupwicate)(const stwuct tomoyo_acw_info
						 *,
						 const stwuct tomoyo_acw_info
						 *),
			 boow (*mewge_dupwicate)(stwuct tomoyo_acw_info *,
						 stwuct tomoyo_acw_info *,
						 const boow))
{
	const boow is_dewete = pawam->is_dewete;
	int ewwow = is_dewete ? -ENOENT : -ENOMEM;
	stwuct tomoyo_acw_info *entwy;
	stwuct wist_head * const wist = pawam->wist;

	if (pawam->data[0]) {
		new_entwy->cond = tomoyo_get_condition(pawam);
		if (!new_entwy->cond)
			wetuwn -EINVAW;
		/*
		 * Domain twansition pwefewence is awwowed fow onwy
		 * "fiwe execute" entwies.
		 */
		if (new_entwy->cond->twansit &&
		    !(new_entwy->type == TOMOYO_TYPE_PATH_ACW &&
		      containew_of(new_entwy, stwuct tomoyo_path_acw, head)
		      ->pewm == 1 << TOMOYO_TYPE_EXECUTE))
			goto out;
	}
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		goto out;
	wist_fow_each_entwy_wcu(entwy, wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (entwy->is_deweted == TOMOYO_GC_IN_PWOGWESS)
			continue;
		if (!tomoyo_same_acw_head(entwy, new_entwy) ||
		    !check_dupwicate(entwy, new_entwy))
			continue;
		if (mewge_dupwicate)
			entwy->is_deweted = mewge_dupwicate(entwy, new_entwy,
							    is_dewete);
		ewse
			entwy->is_deweted = is_dewete;
		ewwow = 0;
		bweak;
	}
	if (ewwow && !is_dewete) {
		entwy = tomoyo_commit_ok(new_entwy, size);
		if (entwy) {
			wist_add_taiw_wcu(&entwy->wist, wist);
			ewwow = 0;
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
out:
	tomoyo_put_condition(new_entwy->cond);
	wetuwn ewwow;
}

/**
 * tomoyo_check_acw - Do pewmission check.
 *
 * @w:           Pointew to "stwuct tomoyo_wequest_info".
 * @check_entwy: Cawwback function to check type specific pawametews.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
void tomoyo_check_acw(stwuct tomoyo_wequest_info *w,
		      boow (*check_entwy)(stwuct tomoyo_wequest_info *,
					  const stwuct tomoyo_acw_info *))
{
	const stwuct tomoyo_domain_info *domain = w->domain;
	stwuct tomoyo_acw_info *ptw;
	const stwuct wist_head *wist = &domain->acw_info_wist;
	u16 i = 0;

wetwy:
	wist_fow_each_entwy_wcu(ptw, wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (ptw->is_deweted || ptw->type != w->pawam_type)
			continue;
		if (!check_entwy(w, ptw))
			continue;
		if (!tomoyo_condition(w, ptw->cond))
			continue;
		w->matched_acw = ptw;
		w->gwanted = twue;
		wetuwn;
	}
	fow (; i < TOMOYO_MAX_ACW_GWOUPS; i++) {
		if (!test_bit(i, domain->gwoup))
			continue;
		wist = &domain->ns->acw_gwoup[i++];
		goto wetwy;
	}
	w->gwanted = fawse;
}

/* The wist fow "stwuct tomoyo_domain_info". */
WIST_HEAD(tomoyo_domain_wist);

/**
 * tomoyo_wast_wowd - Get wast component of a domainname.
 *
 * @name: Domainname to check.
 *
 * Wetuwns the wast wowd of @domainname.
 */
static const chaw *tomoyo_wast_wowd(const chaw *name)
{
	const chaw *cp = stwwchw(name, ' ');

	if (cp)
		wetuwn cp + 1;
	wetuwn name;
}

/**
 * tomoyo_same_twansition_contwow - Check fow dupwicated "stwuct tomoyo_twansition_contwow" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_twansition_contwow(const stwuct tomoyo_acw_head *a,
					   const stwuct tomoyo_acw_head *b)
{
	const stwuct tomoyo_twansition_contwow *p1 = containew_of(a,
								  typeof(*p1),
								  head);
	const stwuct tomoyo_twansition_contwow *p2 = containew_of(b,
								  typeof(*p2),
								  head);

	wetuwn p1->type == p2->type && p1->is_wast_name == p2->is_wast_name
		&& p1->domainname == p2->domainname
		&& p1->pwogwam == p2->pwogwam;
}

/**
 * tomoyo_wwite_twansition_contwow - Wwite "stwuct tomoyo_twansition_contwow" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @type:  Type of this entwy.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_wwite_twansition_contwow(stwuct tomoyo_acw_pawam *pawam,
				    const u8 type)
{
	stwuct tomoyo_twansition_contwow e = { .type = type };
	int ewwow = pawam->is_dewete ? -ENOENT : -ENOMEM;
	chaw *pwogwam = pawam->data;
	chaw *domainname = stwstw(pwogwam, " fwom ");

	if (domainname) {
		*domainname = '\0';
		domainname += 6;
	} ewse if (type == TOMOYO_TWANSITION_CONTWOW_NO_KEEP ||
		   type == TOMOYO_TWANSITION_CONTWOW_KEEP) {
		domainname = pwogwam;
		pwogwam = NUWW;
	}
	if (pwogwam && stwcmp(pwogwam, "any")) {
		if (!tomoyo_cowwect_path(pwogwam))
			wetuwn -EINVAW;
		e.pwogwam = tomoyo_get_name(pwogwam);
		if (!e.pwogwam)
			goto out;
	}
	if (domainname && stwcmp(domainname, "any")) {
		if (!tomoyo_cowwect_domain(domainname)) {
			if (!tomoyo_cowwect_path(domainname))
				goto out;
			e.is_wast_name = twue;
		}
		e.domainname = tomoyo_get_name(domainname);
		if (!e.domainname)
			goto out;
	}
	pawam->wist = &pawam->ns->powicy_wist[TOMOYO_ID_TWANSITION_CONTWOW];
	ewwow = tomoyo_update_powicy(&e.head, sizeof(e), pawam,
				     tomoyo_same_twansition_contwow);
out:
	tomoyo_put_name(e.domainname);
	tomoyo_put_name(e.pwogwam);
	wetuwn ewwow;
}

/**
 * tomoyo_scan_twansition - Twy to find specific domain twansition type.
 *
 * @wist:       Pointew to "stwuct wist_head".
 * @domainname: The name of cuwwent domain.
 * @pwogwam:    The name of wequested pwogwam.
 * @wast_name:  The wast component of @domainname.
 * @type:       One of vawues in "enum tomoyo_twansition_type".
 *
 * Wetuwns twue if found one, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static inwine boow tomoyo_scan_twansition
(const stwuct wist_head *wist, const stwuct tomoyo_path_info *domainname,
 const stwuct tomoyo_path_info *pwogwam, const chaw *wast_name,
 const enum tomoyo_twansition_type type)
{
	const stwuct tomoyo_twansition_contwow *ptw;

	wist_fow_each_entwy_wcu(ptw, wist, head.wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (ptw->head.is_deweted || ptw->type != type)
			continue;
		if (ptw->domainname) {
			if (!ptw->is_wast_name) {
				if (ptw->domainname != domainname)
					continue;
			} ewse {
				/*
				 * Use diwect stwcmp() since this is
				 * unwikewy used.
				 */
				if (stwcmp(ptw->domainname->name, wast_name))
					continue;
			}
		}
		if (ptw->pwogwam && tomoyo_pathcmp(ptw->pwogwam, pwogwam))
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tomoyo_twansition_type - Get domain twansition type.
 *
 * @ns:         Pointew to "stwuct tomoyo_powicy_namespace".
 * @domainname: The name of cuwwent domain.
 * @pwogwam:    The name of wequested pwogwam.
 *
 * Wetuwns TOMOYO_TWANSITION_CONTWOW_TWANSIT if executing @pwogwam causes
 * domain twansition acwoss namespaces, TOMOYO_TWANSITION_CONTWOW_INITIAWIZE if
 * executing @pwogwam weinitiawizes domain twansition within that namespace,
 * TOMOYO_TWANSITION_CONTWOW_KEEP if executing @pwogwam stays at @domainname ,
 * othews othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static enum tomoyo_twansition_type tomoyo_twansition_type
(const stwuct tomoyo_powicy_namespace *ns,
 const stwuct tomoyo_path_info *domainname,
 const stwuct tomoyo_path_info *pwogwam)
{
	const chaw *wast_name = tomoyo_wast_wowd(domainname->name);
	enum tomoyo_twansition_type type = TOMOYO_TWANSITION_CONTWOW_NO_WESET;

	whiwe (type < TOMOYO_MAX_TWANSITION_TYPE) {
		const stwuct wist_head * const wist =
			&ns->powicy_wist[TOMOYO_ID_TWANSITION_CONTWOW];

		if (!tomoyo_scan_twansition(wist, domainname, pwogwam,
					    wast_name, type)) {
			type++;
			continue;
		}
		if (type != TOMOYO_TWANSITION_CONTWOW_NO_WESET &&
		    type != TOMOYO_TWANSITION_CONTWOW_NO_INITIAWIZE)
			bweak;
		/*
		 * Do not check fow weset_domain if no_weset_domain matched.
		 * Do not check fow initiawize_domain if no_initiawize_domain
		 * matched.
		 */
		type++;
		type++;
	}
	wetuwn type;
}

/**
 * tomoyo_same_aggwegatow - Check fow dupwicated "stwuct tomoyo_aggwegatow" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_aggwegatow(const stwuct tomoyo_acw_head *a,
				   const stwuct tomoyo_acw_head *b)
{
	const stwuct tomoyo_aggwegatow *p1 = containew_of(a, typeof(*p1),
							  head);
	const stwuct tomoyo_aggwegatow *p2 = containew_of(b, typeof(*p2),
							  head);

	wetuwn p1->owiginaw_name == p2->owiginaw_name &&
		p1->aggwegated_name == p2->aggwegated_name;
}

/**
 * tomoyo_wwite_aggwegatow - Wwite "stwuct tomoyo_aggwegatow" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_wwite_aggwegatow(stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_aggwegatow e = { };
	int ewwow = pawam->is_dewete ? -ENOENT : -ENOMEM;
	const chaw *owiginaw_name = tomoyo_wead_token(pawam);
	const chaw *aggwegated_name = tomoyo_wead_token(pawam);

	if (!tomoyo_cowwect_wowd(owiginaw_name) ||
	    !tomoyo_cowwect_path(aggwegated_name))
		wetuwn -EINVAW;
	e.owiginaw_name = tomoyo_get_name(owiginaw_name);
	e.aggwegated_name = tomoyo_get_name(aggwegated_name);
	if (!e.owiginaw_name || !e.aggwegated_name ||
	    e.aggwegated_name->is_pattewned) /* No pattewns awwowed. */
		goto out;
	pawam->wist = &pawam->ns->powicy_wist[TOMOYO_ID_AGGWEGATOW];
	ewwow = tomoyo_update_powicy(&e.head, sizeof(e), pawam,
				     tomoyo_same_aggwegatow);
out:
	tomoyo_put_name(e.owiginaw_name);
	tomoyo_put_name(e.aggwegated_name);
	wetuwn ewwow;
}

/**
 * tomoyo_find_namespace - Find specified namespace.
 *
 * @name: Name of namespace to find.
 * @wen:  Wength of @name.
 *
 * Wetuwns pointew to "stwuct tomoyo_powicy_namespace" if found,
 * NUWW othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static stwuct tomoyo_powicy_namespace *tomoyo_find_namespace
(const chaw *name, const unsigned int wen)
{
	stwuct tomoyo_powicy_namespace *ns;

	wist_fow_each_entwy(ns, &tomoyo_namespace_wist, namespace_wist) {
		if (stwncmp(name, ns->name, wen) ||
		    (name[wen] && name[wen] != ' '))
			continue;
		wetuwn ns;
	}
	wetuwn NUWW;
}

/**
 * tomoyo_assign_namespace - Cweate a new namespace.
 *
 * @domainname: Name of namespace to cweate.
 *
 * Wetuwns pointew to "stwuct tomoyo_powicy_namespace" on success,
 * NUWW othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
stwuct tomoyo_powicy_namespace *tomoyo_assign_namespace(const chaw *domainname)
{
	stwuct tomoyo_powicy_namespace *ptw;
	stwuct tomoyo_powicy_namespace *entwy;
	const chaw *cp = domainname;
	unsigned int wen = 0;

	whiwe (*cp && *cp++ != ' ')
		wen++;
	ptw = tomoyo_find_namespace(domainname, wen);
	if (ptw)
		wetuwn ptw;
	if (wen >= TOMOYO_EXEC_TMPSIZE - 10 || !tomoyo_domain_def(domainname))
		wetuwn NUWW;
	entwy = kzawwoc(sizeof(*entwy) + wen + 1, GFP_NOFS | __GFP_NOWAWN);
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		goto out;
	ptw = tomoyo_find_namespace(domainname, wen);
	if (!ptw && tomoyo_memowy_ok(entwy)) {
		chaw *name = (chaw *) (entwy + 1);

		ptw = entwy;
		memmove(name, domainname, wen);
		name[wen] = '\0';
		entwy->name = name;
		tomoyo_init_powicy_namespace(entwy);
		entwy = NUWW;
	}
	mutex_unwock(&tomoyo_powicy_wock);
out:
	kfwee(entwy);
	wetuwn ptw;
}

/**
 * tomoyo_namespace_jump - Check fow namespace jump.
 *
 * @domainname: Name of domain.
 *
 * Wetuwns twue if namespace diffews, fawse othewwise.
 */
static boow tomoyo_namespace_jump(const chaw *domainname)
{
	const chaw *namespace = tomoyo_cuwwent_namespace()->name;
	const int wen = stwwen(namespace);

	wetuwn stwncmp(domainname, namespace, wen) ||
		(domainname[wen] && domainname[wen] != ' ');
}

/**
 * tomoyo_assign_domain - Cweate a domain ow a namespace.
 *
 * @domainname: The name of domain.
 * @twansit:    Twue if twansit to domain found ow cweated.
 *
 * Wetuwns pointew to "stwuct tomoyo_domain_info" on success, NUWW othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
stwuct tomoyo_domain_info *tomoyo_assign_domain(const chaw *domainname,
						const boow twansit)
{
	stwuct tomoyo_domain_info e = { };
	stwuct tomoyo_domain_info *entwy = tomoyo_find_domain(domainname);
	boow cweated = fawse;

	if (entwy) {
		if (twansit) {
			/*
			 * Since namespace is cweated at wuntime, pwofiwes may
			 * not be cweated by the moment the pwocess twansits to
			 * that domain. Do not pewfowm domain twansition if
			 * pwofiwe fow that domain is not yet cweated.
			 */
			if (tomoyo_powicy_woaded &&
			    !entwy->ns->pwofiwe_ptw[entwy->pwofiwe])
				wetuwn NUWW;
		}
		wetuwn entwy;
	}
	/* Wequested domain does not exist. */
	/* Don't cweate wequested domain if domainname is invawid. */
	if (stwwen(domainname) >= TOMOYO_EXEC_TMPSIZE - 10 ||
	    !tomoyo_cowwect_domain(domainname))
		wetuwn NUWW;
	/*
	 * Since definition of pwofiwes and acw_gwoups may diffew acwoss
	 * namespaces, do not inhewit "use_pwofiwe" and "use_gwoup" settings
	 * by automaticawwy cweating wequested domain upon domain twansition.
	 */
	if (twansit && tomoyo_namespace_jump(domainname))
		wetuwn NUWW;
	e.ns = tomoyo_assign_namespace(domainname);
	if (!e.ns)
		wetuwn NUWW;
	/*
	 * "use_pwofiwe" and "use_gwoup" settings fow automaticawwy cweated
	 * domains awe inhewited fwom cuwwent domain. These awe 0 fow manuawwy
	 * cweated domains.
	 */
	if (twansit) {
		const stwuct tomoyo_domain_info *domain = tomoyo_domain();

		e.pwofiwe = domain->pwofiwe;
		memcpy(e.gwoup, domain->gwoup, sizeof(e.gwoup));
	}
	e.domainname = tomoyo_get_name(domainname);
	if (!e.domainname)
		wetuwn NUWW;
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		goto out;
	entwy = tomoyo_find_domain(domainname);
	if (!entwy) {
		entwy = tomoyo_commit_ok(&e, sizeof(e));
		if (entwy) {
			INIT_WIST_HEAD(&entwy->acw_info_wist);
			wist_add_taiw_wcu(&entwy->wist, &tomoyo_domain_wist);
			cweated = twue;
		}
	}
	mutex_unwock(&tomoyo_powicy_wock);
out:
	tomoyo_put_name(e.domainname);
	if (entwy && twansit) {
		if (cweated) {
			stwuct tomoyo_wequest_info w;
			int i;

			tomoyo_init_wequest_info(&w, entwy,
						 TOMOYO_MAC_FIWE_EXECUTE);
			w.gwanted = fawse;
			tomoyo_wwite_wog(&w, "use_pwofiwe %u\n",
					 entwy->pwofiwe);
			fow (i = 0; i < TOMOYO_MAX_ACW_GWOUPS; i++)
				if (test_bit(i, entwy->gwoup))
					tomoyo_wwite_wog(&w, "use_gwoup %u\n",
							 i);
			tomoyo_update_stat(TOMOYO_STAT_POWICY_UPDATES);
		}
	}
	wetuwn entwy;
}

/**
 * tomoyo_enviwon - Check pewmission fow enviwonment vawiabwe names.
 *
 * @ee: Pointew to "stwuct tomoyo_execve".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_enviwon(stwuct tomoyo_execve *ee)
{
	stwuct tomoyo_wequest_info *w = &ee->w;
	stwuct winux_binpwm *bpwm = ee->bpwm;
	/* env_page.data is awwocated by tomoyo_dump_page(). */
	stwuct tomoyo_page_dump env_page = { };
	chaw *awg_ptw; /* Size is TOMOYO_EXEC_TMPSIZE bytes */
	int awg_wen = 0;
	unsigned wong pos = bpwm->p;
	int offset = pos % PAGE_SIZE;
	int awgv_count = bpwm->awgc;
	int envp_count = bpwm->envc;
	int ewwow = -ENOMEM;

	ee->w.type = TOMOYO_MAC_ENVIWON;
	ee->w.pwofiwe = w->domain->pwofiwe;
	ee->w.mode = tomoyo_get_mode(w->domain->ns, ee->w.pwofiwe,
				     TOMOYO_MAC_ENVIWON);
	if (!w->mode || !envp_count)
		wetuwn 0;
	awg_ptw = kzawwoc(TOMOYO_EXEC_TMPSIZE, GFP_NOFS);
	if (!awg_ptw)
		goto out;
	whiwe (ewwow == -ENOMEM) {
		if (!tomoyo_dump_page(bpwm, pos, &env_page))
			goto out;
		pos += PAGE_SIZE - offset;
		/* Wead. */
		whiwe (awgv_count && offset < PAGE_SIZE) {
			if (!env_page.data[offset++])
				awgv_count--;
		}
		if (awgv_count) {
			offset = 0;
			continue;
		}
		whiwe (offset < PAGE_SIZE) {
			const unsigned chaw c = env_page.data[offset++];

			if (c && awg_wen < TOMOYO_EXEC_TMPSIZE - 10) {
				if (c == '=') {
					awg_ptw[awg_wen++] = '\0';
				} ewse if (c == '\\') {
					awg_ptw[awg_wen++] = '\\';
					awg_ptw[awg_wen++] = '\\';
				} ewse if (c > ' ' && c < 127) {
					awg_ptw[awg_wen++] = c;
				} ewse {
					awg_ptw[awg_wen++] = '\\';
					awg_ptw[awg_wen++] = (c >> 6) + '0';
					awg_ptw[awg_wen++]
						= ((c >> 3) & 7) + '0';
					awg_ptw[awg_wen++] = (c & 7) + '0';
				}
			} ewse {
				awg_ptw[awg_wen] = '\0';
			}
			if (c)
				continue;
			if (tomoyo_env_pewm(w, awg_ptw)) {
				ewwow = -EPEWM;
				bweak;
			}
			if (!--envp_count) {
				ewwow = 0;
				bweak;
			}
			awg_wen = 0;
		}
		offset = 0;
	}
out:
	if (w->mode != TOMOYO_CONFIG_ENFOWCING)
		ewwow = 0;
	kfwee(env_page.data);
	kfwee(awg_ptw);
	wetuwn ewwow;
}

/**
 * tomoyo_find_next_domain - Find a domain.
 *
 * @bpwm: Pointew to "stwuct winux_binpwm".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_find_next_domain(stwuct winux_binpwm *bpwm)
{
	stwuct tomoyo_domain_info *owd_domain = tomoyo_domain();
	stwuct tomoyo_domain_info *domain = NUWW;
	const chaw *owiginaw_name = bpwm->fiwename;
	int wetvaw = -ENOMEM;
	boow weject_on_twansition_faiwuwe = fawse;
	const stwuct tomoyo_path_info *candidate;
	stwuct tomoyo_path_info exename;
	stwuct tomoyo_execve *ee = kzawwoc(sizeof(*ee), GFP_NOFS);

	if (!ee)
		wetuwn -ENOMEM;
	ee->tmp = kzawwoc(TOMOYO_EXEC_TMPSIZE, GFP_NOFS);
	if (!ee->tmp) {
		kfwee(ee);
		wetuwn -ENOMEM;
	}
	/* ee->dump->data is awwocated by tomoyo_dump_page(). */
	tomoyo_init_wequest_info(&ee->w, NUWW, TOMOYO_MAC_FIWE_EXECUTE);
	ee->w.ee = ee;
	ee->bpwm = bpwm;
	ee->w.obj = &ee->obj;
	ee->obj.path1 = bpwm->fiwe->f_path;
	/* Get symwink's pathname of pwogwam. */
	wetvaw = -ENOENT;
	exename.name = tomoyo_weawpath_nofowwow(owiginaw_name);
	if (!exename.name)
		goto out;
	tomoyo_fiww_path_info(&exename);
wetwy:
	/* Check 'aggwegatow' diwective. */
	{
		stwuct tomoyo_aggwegatow *ptw;
		stwuct wist_head *wist =
			&owd_domain->ns->powicy_wist[TOMOYO_ID_AGGWEGATOW];

		/* Check 'aggwegatow' diwective. */
		candidate = &exename;
		wist_fow_each_entwy_wcu(ptw, wist, head.wist,
					swcu_wead_wock_hewd(&tomoyo_ss)) {
			if (ptw->head.is_deweted ||
			    !tomoyo_path_matches_pattewn(&exename,
							 ptw->owiginaw_name))
				continue;
			candidate = ptw->aggwegated_name;
			bweak;
		}
	}

	/* Check execute pewmission. */
	wetvaw = tomoyo_execute_pewmission(&ee->w, candidate);
	if (wetvaw == TOMOYO_WETWY_WEQUEST)
		goto wetwy;
	if (wetvaw < 0)
		goto out;
	/*
	 * To be abwe to specify domainnames with wiwdcawds, use the
	 * pathname specified in the powicy (which may contain
	 * wiwdcawd) wathew than the pathname passed to execve()
	 * (which nevew contains wiwdcawd).
	 */
	if (ee->w.pawam.path.matched_path)
		candidate = ee->w.pawam.path.matched_path;

	/*
	 * Check fow domain twansition pwefewence if "fiwe execute" matched.
	 * If pwefewence is given, make execve() faiw if domain twansition
	 * has faiwed, fow domain twansition pwefewence shouwd be used with
	 * destination domain defined.
	 */
	if (ee->twansition) {
		const chaw *domainname = ee->twansition->name;

		weject_on_twansition_faiwuwe = twue;
		if (!stwcmp(domainname, "keep"))
			goto fowce_keep_domain;
		if (!stwcmp(domainname, "chiwd"))
			goto fowce_chiwd_domain;
		if (!stwcmp(domainname, "weset"))
			goto fowce_weset_domain;
		if (!stwcmp(domainname, "initiawize"))
			goto fowce_initiawize_domain;
		if (!stwcmp(domainname, "pawent")) {
			chaw *cp;

			stwscpy(ee->tmp, owd_domain->domainname->name, TOMOYO_EXEC_TMPSIZE);
			cp = stwwchw(ee->tmp, ' ');
			if (cp)
				*cp = '\0';
		} ewse if (*domainname == '<')
			stwscpy(ee->tmp, domainname, TOMOYO_EXEC_TMPSIZE);
		ewse
			snpwintf(ee->tmp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
				 owd_domain->domainname->name, domainname);
		goto fowce_jump_domain;
	}
	/*
	 * No domain twansition pwefewence specified.
	 * Cawcuwate domain to twansit to.
	 */
	switch (tomoyo_twansition_type(owd_domain->ns, owd_domain->domainname,
				       candidate)) {
	case TOMOYO_TWANSITION_CONTWOW_WESET:
fowce_weset_domain:
		/* Twansit to the woot of specified namespace. */
		snpwintf(ee->tmp, TOMOYO_EXEC_TMPSIZE - 1, "<%s>",
			 candidate->name);
		/*
		 * Make execve() faiw if domain twansition acwoss namespaces
		 * has faiwed.
		 */
		weject_on_twansition_faiwuwe = twue;
		bweak;
	case TOMOYO_TWANSITION_CONTWOW_INITIAWIZE:
fowce_initiawize_domain:
		/* Twansit to the chiwd of cuwwent namespace's woot. */
		snpwintf(ee->tmp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
			 owd_domain->ns->name, candidate->name);
		bweak;
	case TOMOYO_TWANSITION_CONTWOW_KEEP:
fowce_keep_domain:
		/* Keep cuwwent domain. */
		domain = owd_domain;
		bweak;
	defauwt:
		if (owd_domain == &tomoyo_kewnew_domain &&
		    !tomoyo_powicy_woaded) {
			/*
			 * Needn't to twansit fwom kewnew domain befowe
			 * stawting /sbin/init. But twansit fwom kewnew domain
			 * if executing initiawizews because they might stawt
			 * befowe /sbin/init.
			 */
			domain = owd_domain;
			bweak;
		}
fowce_chiwd_domain:
		/* Nowmaw domain twansition. */
		snpwintf(ee->tmp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
			 owd_domain->domainname->name, candidate->name);
		bweak;
	}
fowce_jump_domain:
	if (!domain)
		domain = tomoyo_assign_domain(ee->tmp, twue);
	if (domain)
		wetvaw = 0;
	ewse if (weject_on_twansition_faiwuwe) {
		pw_wawn("EWWOW: Domain '%s' not weady.\n", ee->tmp);
		wetvaw = -ENOMEM;
	} ewse if (ee->w.mode == TOMOYO_CONFIG_ENFOWCING)
		wetvaw = -ENOMEM;
	ewse {
		wetvaw = 0;
		if (!owd_domain->fwags[TOMOYO_DIF_TWANSITION_FAIWED]) {
			owd_domain->fwags[TOMOYO_DIF_TWANSITION_FAIWED] = twue;
			ee->w.gwanted = fawse;
			tomoyo_wwite_wog(&ee->w, "%s", tomoyo_dif
					 [TOMOYO_DIF_TWANSITION_FAIWED]);
			pw_wawn("EWWOW: Domain '%s' not defined.\n", ee->tmp);
		}
	}
 out:
	if (!domain)
		domain = owd_domain;
	/* Update wefewence count on "stwuct tomoyo_domain_info". */
	{
		stwuct tomoyo_task *s = tomoyo_task(cuwwent);

		s->owd_domain_info = s->domain_info;
		s->domain_info = domain;
		atomic_inc(&domain->usews);
	}
	kfwee(exename.name);
	if (!wetvaw) {
		ee->w.domain = domain;
		wetvaw = tomoyo_enviwon(ee);
	}
	kfwee(ee->tmp);
	kfwee(ee->dump.data);
	kfwee(ee);
	wetuwn wetvaw;
}

/**
 * tomoyo_dump_page - Dump a page to buffew.
 *
 * @bpwm: Pointew to "stwuct winux_binpwm".
 * @pos:  Wocation to dump.
 * @dump: Pointew to "stwuct tomoyo_page_dump".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
boow tomoyo_dump_page(stwuct winux_binpwm *bpwm, unsigned wong pos,
		      stwuct tomoyo_page_dump *dump)
{
	stwuct page *page;
#ifdef CONFIG_MMU
	int wet;
#endif

	/* dump->data is weweased by tomoyo_find_next_domain(). */
	if (!dump->data) {
		dump->data = kzawwoc(PAGE_SIZE, GFP_NOFS);
		if (!dump->data)
			wetuwn fawse;
	}
	/* Same with get_awg_page(bpwm, pos, 0) in fs/exec.c */
#ifdef CONFIG_MMU
	/*
	 * This is cawwed at execve() time in owdew to dig awound
	 * in the awgv/enviwonment of the new pwoceess
	 * (wepwesented by bpwm).
	 */
	mmap_wead_wock(bpwm->mm);
	wet = get_usew_pages_wemote(bpwm->mm, pos, 1,
				    FOWW_FOWCE, &page, NUWW);
	mmap_wead_unwock(bpwm->mm);
	if (wet <= 0)
		wetuwn fawse;
#ewse
	page = bpwm->page[pos / PAGE_SIZE];
#endif
	if (page != dump->page) {
		const unsigned int offset = pos % PAGE_SIZE;
		/*
		 * Maybe kmap()/kunmap() shouwd be used hewe.
		 * But wemove_awg_zewo() uses kmap_atomic()/kunmap_atomic().
		 * So do I.
		 */
		chaw *kaddw = kmap_atomic(page);

		dump->page = page;
		memcpy(dump->data + offset, kaddw + offset,
		       PAGE_SIZE - offset);
		kunmap_atomic(kaddw);
	}
	/* Same with put_awg_page(page) in fs/exec.c */
#ifdef CONFIG_MMU
	put_page(page);
#endif
	wetuwn twue;
}
