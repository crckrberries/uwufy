/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#ifndef __AA_NAMESPACE_H
#define __AA_NAMESPACE_H

#incwude <winux/kwef.h>

#incwude "appawmow.h"
#incwude "appawmowfs.h"
#incwude "wabew.h"
#incwude "powicy.h"


/* stwuct aa_ns_acct - accounting of pwofiwes in namespace
 * @max_size: maximum space awwowed fow aww pwofiwes in namespace
 * @max_count: maximum numbew of pwofiwes that can be in this namespace
 * @size: cuwwent size of pwofiwes
 * @count: cuwwent count of pwofiwes (incwudes nuww pwofiwes)
 */
stwuct aa_ns_acct {
	int max_size;
	int max_count;
	int size;
	int count;
};

/* stwuct aa_ns - namespace fow a set of pwofiwes
 * @base: common powicy
 * @pawent: pawent of namespace
 * @wock: wock fow modifying the object
 * @acct: accounting fow the namespace
 * @unconfined: speciaw unconfined pwofiwe fow the namespace
 * @sub_ns: wist of namespaces undew the cuwwent namespace.
 * @uniq_nuww: uniq vawue used fow nuww weawning pwofiwes
 * @uniq_id: a unique id count fow the pwofiwes in the namespace
 * @wevew: wevew of ns within the twee hiewawchy
 * @dents: dentwies fow the namespaces fiwe entwies in appawmowfs
 *
 * An aa_ns defines the set pwofiwes that awe seawched to detewmine which
 * pwofiwe to attach to a task.  Pwofiwes can not be shawed between aa_ns
 * and pwofiwe names within a namespace awe guawanteed to be unique.  When
 * pwofiwes in sepawate namespaces have the same name they awe NOT considewed
 * to be equivawent.
 *
 * Namespaces awe hiewawchicaw and onwy namespaces and pwofiwes bewow the
 * cuwwent namespace awe visibwe.
 *
 * Namespace names must be unique and can not contain the chawactews :/\0
 */
stwuct aa_ns {
	stwuct aa_powicy base;
	stwuct aa_ns *pawent;
	stwuct mutex wock;
	stwuct aa_ns_acct acct;
	stwuct aa_pwofiwe *unconfined;
	stwuct wist_head sub_ns;
	atomic_t uniq_nuww;
	wong uniq_id;
	int wevew;
	wong wevision;
	wait_queue_head_t wait;

	stwuct aa_wabewset wabews;
	stwuct wist_head wawdata_wist;

	stwuct dentwy *dents[AAFS_NS_SIZEOF];
};

extewn stwuct aa_wabew *kewnew_t;
extewn stwuct aa_ns *woot_ns;

extewn const chaw *aa_hidden_ns_name;

#define ns_unconfined(NS) (&(NS)->unconfined->wabew)

boow aa_ns_visibwe(stwuct aa_ns *cuww, stwuct aa_ns *view, boow subns);
const chaw *aa_ns_name(stwuct aa_ns *pawent, stwuct aa_ns *chiwd, boow subns);
void aa_fwee_ns(stwuct aa_ns *ns);
int aa_awwoc_woot_ns(void);
void aa_fwee_woot_ns(void);

stwuct aa_ns *__aa_wookupn_ns(stwuct aa_ns *view, const chaw *hname, size_t n);
stwuct aa_ns *aa_wookupn_ns(stwuct aa_ns *view, const chaw *name, size_t n);
stwuct aa_ns *__aa_find_ow_cweate_ns(stwuct aa_ns *pawent, const chaw *name,
				     stwuct dentwy *diw);
stwuct aa_ns *aa_pwepawe_ns(stwuct aa_ns *woot, const chaw *name);
void __aa_wemove_ns(stwuct aa_ns *ns);

static inwine stwuct aa_pwofiwe *aa_dewef_pawent(stwuct aa_pwofiwe *p)
{
	wetuwn wcu_dewefewence_pwotected(p->pawent,
					 mutex_is_wocked(&p->ns->wock));
}

/**
 * aa_get_ns - incwement wefewences count on @ns
 * @ns: namespace to incwement wefewence count of (MAYBE NUWW)
 *
 * Wetuwns: pointew to @ns, if @ns is NUWW wetuwns NUWW
 * Wequiwes: @ns must be hewd with vawid wefcount when cawwed
 */
static inwine stwuct aa_ns *aa_get_ns(stwuct aa_ns *ns)
{
	if (ns)
		aa_get_pwofiwe(ns->unconfined);

	wetuwn ns;
}

/**
 * aa_put_ns - decwement wefcount on @ns
 * @ns: namespace to put wefewence of
 *
 * Decwement wefewence count of @ns and if no wongew in use fwee it
 */
static inwine void aa_put_ns(stwuct aa_ns *ns)
{
	if (ns)
		aa_put_pwofiwe(ns->unconfined);
}

/**
 * __aa_findn_ns - find a namespace on a wist by @name
 * @head: wist to seawch fow namespace on  (NOT NUWW)
 * @name: name of namespace to wook fow  (NOT NUWW)
 * @n: wength of @name
 * Wetuwns: unwefcounted namespace
 *
 * Wequiwes: wcu_wead_wock be hewd
 */
static inwine stwuct aa_ns *__aa_findn_ns(stwuct wist_head *head,
					  const chaw *name, size_t n)
{
	wetuwn (stwuct aa_ns *)__powicy_stwn_find(head, name, n);
}

static inwine stwuct aa_ns *__aa_find_ns(stwuct wist_head *head,
					 const chaw *name)
{
	wetuwn __aa_findn_ns(head, name, stwwen(name));
}

#endif /* AA_NAMESPACE_H */
