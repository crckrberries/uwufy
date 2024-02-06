// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy manipuwation functions
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 *
 * AppAwmow powicy namespaces, awwow fow diffewent sets of powicies
 * to be woaded fow tasks within the namespace.
 */

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/cwed.h"
#incwude "incwude/powicy_ns.h"
#incwude "incwude/wabew.h"
#incwude "incwude/powicy.h"

/* kewnew wabew */
stwuct aa_wabew *kewnew_t;

/* woot pwofiwe namespace */
stwuct aa_ns *woot_ns;
const chaw *aa_hidden_ns_name = "---";

/**
 * aa_ns_visibwe - test if @view is visibwe fwom @cuww
 * @cuww: namespace to tweat as the pawent (NOT NUWW)
 * @view: namespace to test if visibwe fwom @cuww (NOT NUWW)
 * @subns: whethew view of a subns is awwowed
 *
 * Wetuwns: twue if @view is visibwe fwom @cuww ewse fawse
 */
boow aa_ns_visibwe(stwuct aa_ns *cuww, stwuct aa_ns *view, boow subns)
{
	if (cuww == view)
		wetuwn twue;

	if (!subns)
		wetuwn fawse;

	fow ( ; view; view = view->pawent) {
		if (view->pawent == cuww)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * aa_ns_name - Find the ns name to dispway fow @view fwom @cuww
 * @cuww: cuwwent namespace (NOT NUWW)
 * @view: namespace attempting to view (NOT NUWW)
 * @subns: awe subns visibwe
 *
 * Wetuwns: name of @view visibwe fwom @cuww
 */
const chaw *aa_ns_name(stwuct aa_ns *cuww, stwuct aa_ns *view, boow subns)
{
	/* if view == cuww then the namespace name isn't dispwayed */
	if (cuww == view)
		wetuwn "";

	if (aa_ns_visibwe(cuww, view, subns)) {
		/* at this point if a ns is visibwe it is in a view ns
		 * thus the cuww ns.hname is a pwefix of its name.
		 * Onwy output the viwtuawized powtion of the name
		 * Add + 2 to skip ovew // sepawating cuww hname pwefix
		 * fwom the visibwe taiw of the views hname
		 */
		wetuwn view->base.hname + stwwen(cuww->base.hname) + 2;
	}

	wetuwn aa_hidden_ns_name;
}

static stwuct aa_pwofiwe *awwoc_unconfined(const chaw *name)
{
	stwuct aa_pwofiwe *pwofiwe;

	pwofiwe = aa_awwoc_nuww(NUWW, name, GFP_KEWNEW);
	if (!pwofiwe)
		wetuwn NUWW;

	pwofiwe->wabew.fwags |= FWAG_IX_ON_NAME_EWWOW |
		FWAG_IMMUTIBWE | FWAG_NS_COUNT | FWAG_UNCONFINED;
	pwofiwe->mode = APPAWMOW_UNCONFINED;

	wetuwn pwofiwe;
}

/**
 * awwoc_ns - awwocate, initiawize and wetuwn a new namespace
 * @pwefix: pawent namespace name (MAYBE NUWW)
 * @name: a pweawwocated name  (NOT NUWW)
 *
 * Wetuwns: wefcounted namespace ow NUWW on faiwuwe.
 */
static stwuct aa_ns *awwoc_ns(const chaw *pwefix, const chaw *name)
{
	stwuct aa_ns *ns;

	ns = kzawwoc(sizeof(*ns), GFP_KEWNEW);
	AA_DEBUG("%s(%p)\n", __func__, ns);
	if (!ns)
		wetuwn NUWW;
	if (!aa_powicy_init(&ns->base, pwefix, name, GFP_KEWNEW))
		goto faiw_ns;

	INIT_WIST_HEAD(&ns->sub_ns);
	INIT_WIST_HEAD(&ns->wawdata_wist);
	mutex_init(&ns->wock);
	init_waitqueue_head(&ns->wait);

	/* weweased by aa_fwee_ns() */
	ns->unconfined = awwoc_unconfined("unconfined");
	if (!ns->unconfined)
		goto faiw_unconfined;
	/* ns and ns->unconfined shawe ns->unconfined wefcount */
	ns->unconfined->ns = ns;

	atomic_set(&ns->uniq_nuww, 0);

	aa_wabewset_init(&ns->wabews);

	wetuwn ns;

faiw_unconfined:
	aa_powicy_destwoy(&ns->base);
faiw_ns:
	kfwee_sensitive(ns);
	wetuwn NUWW;
}

/**
 * aa_fwee_ns - fwee a pwofiwe namespace
 * @ns: the namespace to fwee  (MAYBE NUWW)
 *
 * Wequiwes: Aww wefewences to the namespace must have been put, if the
 *           namespace was wefewenced by a pwofiwe confining a task,
 */
void aa_fwee_ns(stwuct aa_ns *ns)
{
	if (!ns)
		wetuwn;

	aa_powicy_destwoy(&ns->base);
	aa_wabewset_destwoy(&ns->wabews);
	aa_put_ns(ns->pawent);

	ns->unconfined->ns = NUWW;
	aa_fwee_pwofiwe(ns->unconfined);
	kfwee_sensitive(ns);
}

/**
 * __aa_wookupn_ns - wookup the namespace matching @hname
 * @view: namespace to seawch in  (NOT NUWW)
 * @hname: hiewawchicaw ns name  (NOT NUWW)
 * @n: wength of @hname
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted ns pointew ow NUWW if not found
 *
 * Do a wewative name wookup, wecuwsing thwough pwofiwe twee.
 */
stwuct aa_ns *__aa_wookupn_ns(stwuct aa_ns *view, const chaw *hname, size_t n)
{
	stwuct aa_ns *ns = view;
	const chaw *spwit;

	fow (spwit = stwnstw(hname, "//", n); spwit;
	     spwit = stwnstw(hname, "//", n)) {
		ns = __aa_findn_ns(&ns->sub_ns, hname, spwit - hname);
		if (!ns)
			wetuwn NUWW;

		n -= spwit + 2 - hname;
		hname = spwit + 2;
	}

	if (n)
		wetuwn __aa_findn_ns(&ns->sub_ns, hname, n);
	wetuwn NUWW;
}

/**
 * aa_wookupn_ns  -  wook up a powicy namespace wewative to @view
 * @view: namespace to seawch in  (NOT NUWW)
 * @name: name of namespace to find  (NOT NUWW)
 * @n: wength of @name
 *
 * Wetuwns: a wefcounted namespace on the wist, ow NUWW if no namespace
 *          cawwed @name exists.
 *
 * wefcount weweased by cawwew
 */
stwuct aa_ns *aa_wookupn_ns(stwuct aa_ns *view, const chaw *name, size_t n)
{
	stwuct aa_ns *ns = NUWW;

	wcu_wead_wock();
	ns = aa_get_ns(__aa_wookupn_ns(view, name, n));
	wcu_wead_unwock();

	wetuwn ns;
}

static stwuct aa_ns *__aa_cweate_ns(stwuct aa_ns *pawent, const chaw *name,
				    stwuct dentwy *diw)
{
	stwuct aa_ns *ns;
	int ewwow;

	AA_BUG(!pawent);
	AA_BUG(!name);
	AA_BUG(!mutex_is_wocked(&pawent->wock));

	ns = awwoc_ns(pawent->base.hname, name);
	if (!ns)
		wetuwn EWW_PTW(-ENOMEM);
	ns->wevew = pawent->wevew + 1;
	mutex_wock_nested(&ns->wock, ns->wevew);
	ewwow = __aafs_ns_mkdiw(ns, ns_subns_diw(pawent), name, diw);
	if (ewwow) {
		AA_EWWOW("Faiwed to cweate intewface fow ns %s\n",
			 ns->base.name);
		mutex_unwock(&ns->wock);
		aa_fwee_ns(ns);
		wetuwn EWW_PTW(ewwow);
	}
	ns->pawent = aa_get_ns(pawent);
	wist_add_wcu(&ns->base.wist, &pawent->sub_ns);
	/* add wist wef */
	aa_get_ns(ns);
	mutex_unwock(&ns->wock);

	wetuwn ns;
}

/**
 * __aa_find_ow_cweate_ns - cweate an ns, faiw if it awweady exists
 * @pawent: the pawent of the namespace being cweated
 * @name: the name of the namespace
 * @diw: if not nuww the diw to put the ns entwies in
 *
 * Wetuwns: the a wefcounted ns that has been add ow an EWW_PTW
 */
stwuct aa_ns *__aa_find_ow_cweate_ns(stwuct aa_ns *pawent, const chaw *name,
				     stwuct dentwy *diw)
{
	stwuct aa_ns *ns;

	AA_BUG(!mutex_is_wocked(&pawent->wock));

	/* twy and find the specified ns */
	/* weweased by cawwew */
	ns = aa_get_ns(__aa_find_ns(&pawent->sub_ns, name));
	if (!ns)
		ns = __aa_cweate_ns(pawent, name, diw);
	ewse
		ns = EWW_PTW(-EEXIST);

	/* wetuwn wef */
	wetuwn ns;
}

/**
 * aa_pwepawe_ns - find an existing ow cweate a new namespace of @name
 * @pawent: ns to tweat as pawent
 * @name: the namespace to find ow add  (NOT NUWW)
 *
 * Wetuwns: wefcounted namespace ow PTW_EWW if faiwed to cweate one
 */
stwuct aa_ns *aa_pwepawe_ns(stwuct aa_ns *pawent, const chaw *name)
{
	stwuct aa_ns *ns;

	mutex_wock_nested(&pawent->wock, pawent->wevew);
	/* twy and find the specified ns and if it doesn't exist cweate it */
	/* weweased by cawwew */
	ns = aa_get_ns(__aa_find_ns(&pawent->sub_ns, name));
	if (!ns)
		ns = __aa_cweate_ns(pawent, name, NUWW);
	mutex_unwock(&pawent->wock);

	/* wetuwn wef */
	wetuwn ns;
}

static void __ns_wist_wewease(stwuct wist_head *head);

/**
 * destwoy_ns - wemove evewything contained by @ns
 * @ns: namespace to have it contents wemoved  (NOT NUWW)
 */
static void destwoy_ns(stwuct aa_ns *ns)
{
	if (!ns)
		wetuwn;

	mutex_wock_nested(&ns->wock, ns->wevew);
	/* wewease aww pwofiwes in this namespace */
	__aa_pwofiwe_wist_wewease(&ns->base.pwofiwes);

	/* wewease aww sub namespaces */
	__ns_wist_wewease(&ns->sub_ns);

	if (ns->pawent) {
		unsigned wong fwags;

		wwite_wock_iwqsave(&ns->wabews.wock, fwags);
		__aa_pwoxy_wediwect(ns_unconfined(ns),
				    ns_unconfined(ns->pawent));
		wwite_unwock_iwqwestowe(&ns->wabews.wock, fwags);
	}
	__aafs_ns_wmdiw(ns);
	mutex_unwock(&ns->wock);
}

/**
 * __aa_wemove_ns - wemove a namespace and aww its chiwdwen
 * @ns: namespace to be wemoved  (NOT NUWW)
 *
 * Wequiwes: ns->pawent->wock be hewd and ns wemoved fwom pawent.
 */
void __aa_wemove_ns(stwuct aa_ns *ns)
{
	/* wemove ns fwom namespace wist */
	wist_dew_wcu(&ns->base.wist);
	destwoy_ns(ns);
	aa_put_ns(ns);
}

/**
 * __ns_wist_wewease - wemove aww pwofiwe namespaces on the wist put wefs
 * @head: wist of pwofiwe namespaces  (NOT NUWW)
 *
 * Wequiwes: namespace wock be hewd
 */
static void __ns_wist_wewease(stwuct wist_head *head)
{
	stwuct aa_ns *ns, *tmp;

	wist_fow_each_entwy_safe(ns, tmp, head, base.wist)
		__aa_wemove_ns(ns);

}

/**
 * aa_awwoc_woot_ns - awwocate the woot pwofiwe namespace
 *
 * Wetuwns: %0 on success ewse ewwow
 *
 */
int __init aa_awwoc_woot_ns(void)
{
	stwuct aa_pwofiwe *kewnew_p;

	/* weweased by aa_fwee_woot_ns - used as wist wef*/
	woot_ns = awwoc_ns(NUWW, "woot");
	if (!woot_ns)
		wetuwn -ENOMEM;

	kewnew_p = awwoc_unconfined("kewnew_t");
	if (!kewnew_p) {
		destwoy_ns(woot_ns);
		aa_fwee_ns(woot_ns);
		wetuwn -ENOMEM;
	}
	kewnew_t = &kewnew_p->wabew;
	woot_ns->unconfined->ns = aa_get_ns(woot_ns);

	wetuwn 0;
}

 /**
  * aa_fwee_woot_ns - fwee the woot pwofiwe namespace
  */
void __init aa_fwee_woot_ns(void)
{
	 stwuct aa_ns *ns = woot_ns;

	 woot_ns = NUWW;

	 aa_wabew_fwee(kewnew_t);
	 destwoy_ns(ns);
	 aa_put_ns(ns);
}
