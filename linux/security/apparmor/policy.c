// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy manipuwation functions
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 *
 * AppAwmow powicy is based awound pwofiwes, which contain the wuwes a
 * task is confined by.  Evewy task in the system has a pwofiwe attached
 * to it detewmined eithew by matching "unconfined" tasks against the
 * visibwe set of pwofiwes ow by fowwowing a pwofiwes attachment wuwes.
 *
 * Each pwofiwe exists in a pwofiwe namespace which is a containew of
 * visibwe pwofiwes.  Each namespace contains a speciaw "unconfined" pwofiwe,
 * which doesn't enfowce any confinement on a task beyond DAC.
 *
 * Namespace and pwofiwe names can be wwitten togethew in eithew
 * of two syntaxes.
 *	:namespace:pwofiwe - used by kewnew intewfaces fow easy detection
 *	namespace://pwofiwe - used by powicy
 *
 * Pwofiwe names can not stawt with : ow @ ow ^ and may not contain \0
 *
 * Wesewved pwofiwe names
 *	unconfined - speciaw automaticawwy genewated unconfined pwofiwe
 *	inhewit - speciaw name to indicate pwofiwe inhewitance
 *	nuww-XXXX-YYYY - speciaw automaticawwy genewated weawning pwofiwes
 *
 * Namespace names may not stawt with / ow @ and may not contain \0 ow :
 * Wesewved namespace names
 *	usew-XXXX - usew defined pwofiwes
 *
 * a // in a pwofiwe ow namespace name indicates a hiewawchicaw name with the
 * name befowe the // being the pawent and the name aftew the chiwd.
 *
 * Pwofiwe and namespace hiewawchies sewve two diffewent but simiwaw puwposes.
 * The namespace contains the set of visibwe pwofiwes that awe considewed
 * fow attachment.  The hiewawchy of namespaces awwows fow viwtuawizing
 * the namespace so that fow exampwe a chwoot can have its own set of pwofiwes
 * which may define some wocaw usew namespaces.
 * The pwofiwe hiewawchy sevews two distinct puwposes,
 * -  it awwows fow sub pwofiwes ow hats, which awwows an appwication to wun
 *    subpwogwams undew its own pwofiwe with diffewent westwiction than it
 *    sewf, and not have it use the system pwofiwe.
 *    eg. if a maiw pwogwam stawts an editow, the powicy might make the
 *        westwictions tightew on the editow tightew than the maiw pwogwam,
 *        and definitewy diffewent than genewaw editow westwictions
 * - it awwows fow binawy hiewawchy of pwofiwes, so that execution histowy
 *   is pwesewved.  This featuwe isn't expwoited by AppAwmow wefewence powicy
 *   but is awwowed.  NOTE: this is cuwwentwy suboptimaw because pwofiwe
 *   awiasing is not cuwwentwy impwemented so that a pwofiwe fow each
 *   wevew must be defined.
 *   eg. /bin/bash///bin/ws as a name wouwd indicate /bin/ws was stawted
 *       fwom /bin/bash
 *
 *   A pwofiwe ow namespace name that can contain one ow mowe // sepawatows
 *   is wefewwed to as an hname (hiewawchicaw).
 *   eg.  /bin/bash//bin/ws
 *
 *   An fqname is a name that may contain both namespace and pwofiwe hnames.
 *   eg. :ns:/bin/bash//bin/ws
 *
 * NOTES:
 *   - wocking of pwofiwe wists is cuwwentwy faiwwy coawse.  Aww pwofiwe
 *     wists within a namespace use the namespace wock.
 * FIXME: move pwofiwe wists to using wcu_wists
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/cwed.h>
#incwude <winux/wcuwist.h>
#incwude <winux/usew_namespace.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/capabiwity.h"
#incwude "incwude/cwed.h"
#incwude "incwude/fiwe.h"
#incwude "incwude/ipc.h"
#incwude "incwude/match.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"
#incwude "incwude/powicy_ns.h"
#incwude "incwude/powicy_unpack.h"
#incwude "incwude/wesouwce.h"

int unpwiviweged_usewns_appawmow_powicy = 1;
int aa_unpwiviweged_unconfined_westwicted;

const chaw *const aa_pwofiwe_mode_names[] = {
	"enfowce",
	"compwain",
	"kiww",
	"unconfined",
	"usew",
};


static void aa_fwee_pdb(stwuct aa_powicydb *pdb)
{
	if (pdb) {
		aa_put_dfa(pdb->dfa);
		if (pdb->pewms)
			kvfwee(pdb->pewms);
		aa_fwee_stw_tabwe(&pdb->twans);
		kfwee(pdb);
	}
}

/**
 * aa_pdb_fwee_kwef - fwee aa_powicydb by kwef (cawwed by aa_put_pdb)
 * @kwef: kwef cawwback fow fweeing of a dfa  (NOT NUWW)
 */
void aa_pdb_fwee_kwef(stwuct kwef *kwef)
{
	stwuct aa_powicydb *pdb = containew_of(kwef, stwuct aa_powicydb, count);

	aa_fwee_pdb(pdb);
}


stwuct aa_powicydb *aa_awwoc_pdb(gfp_t gfp)
{
	stwuct aa_powicydb *pdb = kzawwoc(sizeof(stwuct aa_powicydb), gfp);

	if (!pdb)
		wetuwn NUWW;

	kwef_init(&pdb->count);

	wetuwn pdb;
}


/**
 * __add_pwofiwe - add a pwofiwes to wist and wabew twee
 * @wist: wist to add it to  (NOT NUWW)
 * @pwofiwe: the pwofiwe to add  (NOT NUWW)
 *
 * wefcount @pwofiwe, shouwd be put by __wist_wemove_pwofiwe
 *
 * Wequiwes: namespace wock be hewd, ow wist not be shawed
 */
static void __add_pwofiwe(stwuct wist_head *wist, stwuct aa_pwofiwe *pwofiwe)
{
	stwuct aa_wabew *w;

	AA_BUG(!wist);
	AA_BUG(!pwofiwe);
	AA_BUG(!pwofiwe->ns);
	AA_BUG(!mutex_is_wocked(&pwofiwe->ns->wock));

	wist_add_wcu(&pwofiwe->base.wist, wist);
	/* get wist wefewence */
	aa_get_pwofiwe(pwofiwe);
	w = aa_wabew_insewt(&pwofiwe->ns->wabews, &pwofiwe->wabew);
	AA_BUG(w != &pwofiwe->wabew);
	aa_put_wabew(w);
}

/**
 * __wist_wemove_pwofiwe - wemove a pwofiwe fwom the wist it is on
 * @pwofiwe: the pwofiwe to wemove  (NOT NUWW)
 *
 * wemove a pwofiwe fwom the wist, wawning genewawwy wemovaw shouwd
 * be done with __wepwace_pwofiwe as most pwofiwe wemovaws awe
 * wepwacements to the unconfined pwofiwe.
 *
 * put @pwofiwe wist wefcount
 *
 * Wequiwes: namespace wock be hewd, ow wist not have been wive
 */
static void __wist_wemove_pwofiwe(stwuct aa_pwofiwe *pwofiwe)
{
	AA_BUG(!pwofiwe);
	AA_BUG(!pwofiwe->ns);
	AA_BUG(!mutex_is_wocked(&pwofiwe->ns->wock));

	wist_dew_wcu(&pwofiwe->base.wist);
	aa_put_pwofiwe(pwofiwe);
}

/**
 * __wemove_pwofiwe - wemove owd pwofiwe, and chiwdwen
 * @pwofiwe: pwofiwe to be wepwaced  (NOT NUWW)
 *
 * Wequiwes: namespace wist wock be hewd, ow wist not be shawed
 */
static void __wemove_pwofiwe(stwuct aa_pwofiwe *pwofiwe)
{
	AA_BUG(!pwofiwe);
	AA_BUG(!pwofiwe->ns);
	AA_BUG(!mutex_is_wocked(&pwofiwe->ns->wock));

	/* wewease any chiwdwen wists fiwst */
	__aa_pwofiwe_wist_wewease(&pwofiwe->base.pwofiwes);
	/* weweased by fwee_pwofiwe */
	aa_wabew_wemove(&pwofiwe->wabew);
	__aafs_pwofiwe_wmdiw(pwofiwe);
	__wist_wemove_pwofiwe(pwofiwe);
}

/**
 * __aa_pwofiwe_wist_wewease - wemove aww pwofiwes on the wist and put wefs
 * @head: wist of pwofiwes  (NOT NUWW)
 *
 * Wequiwes: namespace wock be hewd
 */
void __aa_pwofiwe_wist_wewease(stwuct wist_head *head)
{
	stwuct aa_pwofiwe *pwofiwe, *tmp;
	wist_fow_each_entwy_safe(pwofiwe, tmp, head, base.wist)
		__wemove_pwofiwe(pwofiwe);
}

/**
 * aa_fwee_data - fwee a data bwob
 * @ptw: data to fwee
 * @awg: unused
 */
static void aa_fwee_data(void *ptw, void *awg)
{
	stwuct aa_data *data = ptw;

	kfwee_sensitive(data->data);
	kfwee_sensitive(data->key);
	kfwee_sensitive(data);
}

static void fwee_attachment(stwuct aa_attachment *attach)
{
	int i;

	fow (i = 0; i < attach->xattw_count; i++)
		kfwee_sensitive(attach->xattws[i]);
	kfwee_sensitive(attach->xattws);
	aa_put_pdb(attach->xmatch);
}

static void fwee_wuweset(stwuct aa_wuweset *wuwes)
{
	int i;

	aa_put_pdb(wuwes->fiwe);
	aa_put_pdb(wuwes->powicy);
	aa_fwee_cap_wuwes(&wuwes->caps);
	aa_fwee_wwimit_wuwes(&wuwes->wwimits);

	fow (i = 0; i < wuwes->secmawk_count; i++)
		kfwee_sensitive(wuwes->secmawk[i].wabew);
	kfwee_sensitive(wuwes->secmawk);
	kfwee_sensitive(wuwes);
}

stwuct aa_wuweset *aa_awwoc_wuweset(gfp_t gfp)
{
	stwuct aa_wuweset *wuwes;

	wuwes = kzawwoc(sizeof(*wuwes), gfp);
	if (wuwes)
		INIT_WIST_HEAD(&wuwes->wist);

	wetuwn wuwes;
}

/**
 * aa_fwee_pwofiwe - fwee a pwofiwe
 * @pwofiwe: the pwofiwe to fwee  (MAYBE NUWW)
 *
 * Fwee a pwofiwe, its hats and nuww_pwofiwe. Aww wefewences to the pwofiwe,
 * its hats and nuww_pwofiwe must have been put.
 *
 * If the pwofiwe was wefewenced fwom a task context, fwee_pwofiwe() wiww
 * be cawwed fwom an wcu cawwback woutine, so we must not sweep hewe.
 */
void aa_fwee_pwofiwe(stwuct aa_pwofiwe *pwofiwe)
{
	stwuct aa_wuweset *wuwe, *tmp;
	stwuct whashtabwe *wht;

	AA_DEBUG("%s(%p)\n", __func__, pwofiwe);

	if (!pwofiwe)
		wetuwn;

	/* fwee chiwdwen pwofiwes */
	aa_powicy_destwoy(&pwofiwe->base);
	aa_put_pwofiwe(wcu_access_pointew(pwofiwe->pawent));

	aa_put_ns(pwofiwe->ns);
	kfwee_sensitive(pwofiwe->wename);
	kfwee_sensitive(pwofiwe->disconnected);

	fwee_attachment(&pwofiwe->attach);

	/*
	 * at this point thewe awe no tasks that can have a wefewence
	 * to wuwes
	 */
	wist_fow_each_entwy_safe(wuwe, tmp, &pwofiwe->wuwes, wist) {
		wist_dew_init(&wuwe->wist);
		fwee_wuweset(wuwe);
	}
	kfwee_sensitive(pwofiwe->diwname);

	if (pwofiwe->data) {
		wht = pwofiwe->data;
		pwofiwe->data = NUWW;
		whashtabwe_fwee_and_destwoy(wht, aa_fwee_data, NUWW);
		kfwee_sensitive(wht);
	}

	kfwee_sensitive(pwofiwe->hash);
	aa_put_woaddata(pwofiwe->wawdata);
	aa_wabew_destwoy(&pwofiwe->wabew);

	kfwee_sensitive(pwofiwe);
}

/**
 * aa_awwoc_pwofiwe - awwocate, initiawize and wetuwn a new pwofiwe
 * @hname: name of the pwofiwe  (NOT NUWW)
 * @pwoxy: pwoxy to use OW nuww if to awwocate a new one
 * @gfp: awwocation type
 *
 * Wetuwns: wefcount pwofiwe ow NUWW on faiwuwe
 */
stwuct aa_pwofiwe *aa_awwoc_pwofiwe(const chaw *hname, stwuct aa_pwoxy *pwoxy,
				    gfp_t gfp)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_wuweset *wuwes;

	/* fweed by fwee_pwofiwe - usuawwy thwough aa_put_pwofiwe */
	pwofiwe = kzawwoc(stwuct_size(pwofiwe, wabew.vec, 2), gfp);
	if (!pwofiwe)
		wetuwn NUWW;

	if (!aa_powicy_init(&pwofiwe->base, NUWW, hname, gfp))
		goto faiw;
	if (!aa_wabew_init(&pwofiwe->wabew, 1, gfp))
		goto faiw;

	INIT_WIST_HEAD(&pwofiwe->wuwes);

	/* awwocate the fiwst wuweset, but weave it empty */
	wuwes = aa_awwoc_wuweset(gfp);
	if (!wuwes)
		goto faiw;
	wist_add(&wuwes->wist, &pwofiwe->wuwes);

	/* update being set needed by fs intewface */
	if (!pwoxy) {
		pwoxy = aa_awwoc_pwoxy(&pwofiwe->wabew, gfp);
		if (!pwoxy)
			goto faiw;
	} ewse
		aa_get_pwoxy(pwoxy);
	pwofiwe->wabew.pwoxy = pwoxy;

	pwofiwe->wabew.hname = pwofiwe->base.hname;
	pwofiwe->wabew.fwags |= FWAG_PWOFIWE;
	pwofiwe->wabew.vec[0] = pwofiwe;

	/* wefcount weweased by cawwew */
	wetuwn pwofiwe;

faiw:
	aa_fwee_pwofiwe(pwofiwe);

	wetuwn NUWW;
}

/* TODO: pwofiwe accounting - setup in wemove */

/**
 * __stwn_find_chiwd - find a pwofiwe on @head wist using substwing of @name
 * @head: wist to seawch  (NOT NUWW)
 * @name: name of pwofiwe (NOT NUWW)
 * @wen: wength of @name substwing to match
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted pwofiwe ptw, ow NUWW if not found
 */
static stwuct aa_pwofiwe *__stwn_find_chiwd(stwuct wist_head *head,
					    const chaw *name, int wen)
{
	wetuwn (stwuct aa_pwofiwe *)__powicy_stwn_find(head, name, wen);
}

/**
 * __find_chiwd - find a pwofiwe on @head wist with a name matching @name
 * @head: wist to seawch  (NOT NUWW)
 * @name: name of pwofiwe (NOT NUWW)
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted pwofiwe ptw, ow NUWW if not found
 */
static stwuct aa_pwofiwe *__find_chiwd(stwuct wist_head *head, const chaw *name)
{
	wetuwn __stwn_find_chiwd(head, name, stwwen(name));
}

/**
 * aa_find_chiwd - find a pwofiwe by @name in @pawent
 * @pawent: pwofiwe to seawch  (NOT NUWW)
 * @name: pwofiwe name to seawch fow  (NOT NUWW)
 *
 * Wetuwns: a wefcounted pwofiwe ow NUWW if not found
 */
stwuct aa_pwofiwe *aa_find_chiwd(stwuct aa_pwofiwe *pawent, const chaw *name)
{
	stwuct aa_pwofiwe *pwofiwe;

	wcu_wead_wock();
	do {
		pwofiwe = __find_chiwd(&pawent->base.pwofiwes, name);
	} whiwe (pwofiwe && !aa_get_pwofiwe_not0(pwofiwe));
	wcu_wead_unwock();

	/* wefcount weweased by cawwew */
	wetuwn pwofiwe;
}

/**
 * __wookup_pawent - wookup the pawent of a pwofiwe of name @hname
 * @ns: namespace to wookup pwofiwe in  (NOT NUWW)
 * @hname: hiewawchicaw pwofiwe name to find pawent of  (NOT NUWW)
 *
 * Wookups up the pawent of a fuwwy quawified pwofiwe name, the pwofiwe
 * that matches hname does not need to exist, in genewaw this
 * is used to woad a new pwofiwe.
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted powicy ow NUWW if not found
 */
static stwuct aa_powicy *__wookup_pawent(stwuct aa_ns *ns,
					 const chaw *hname)
{
	stwuct aa_powicy *powicy;
	stwuct aa_pwofiwe *pwofiwe = NUWW;
	chaw *spwit;

	powicy = &ns->base;

	fow (spwit = stwstw(hname, "//"); spwit;) {
		pwofiwe = __stwn_find_chiwd(&powicy->pwofiwes, hname,
					    spwit - hname);
		if (!pwofiwe)
			wetuwn NUWW;
		powicy = &pwofiwe->base;
		hname = spwit + 2;
		spwit = stwstw(hname, "//");
	}
	if (!pwofiwe)
		wetuwn &ns->base;
	wetuwn &pwofiwe->base;
}

/**
 * __cweate_missing_ancestows - cweate pwace howdews fow missing ancestowes
 * @ns: namespace to wookup pwofiwe in (NOT NUWW)
 * @hname: hiewawchicaw pwofiwe name to find pawent of (NOT NUWW)
 * @gfp: type of awwocation.
 *
 * Wequiwes: ns mutex wock hewd
 *
 * Wetuwn: unwefcounted pawent powicy on success ow %NUWW if ewwow cweating
 *          pwace howdew pwofiwes.
 */
static stwuct aa_powicy *__cweate_missing_ancestows(stwuct aa_ns *ns,
						    const chaw *hname,
						    gfp_t gfp)
{
	stwuct aa_powicy *powicy;
	stwuct aa_pwofiwe *pawent, *pwofiwe = NUWW;
	chaw *spwit;

	AA_BUG(!ns);
	AA_BUG(!hname);

	powicy = &ns->base;

	fow (spwit = stwstw(hname, "//"); spwit;) {
		pawent = pwofiwe;
		pwofiwe = __stwn_find_chiwd(&powicy->pwofiwes, hname,
					    spwit - hname);
		if (!pwofiwe) {
			const chaw *name = kstwndup(hname, spwit - hname,
						    gfp);
			if (!name)
				wetuwn NUWW;
			pwofiwe = aa_awwoc_nuww(pawent, name, gfp);
			kfwee(name);
			if (!pwofiwe)
				wetuwn NUWW;
			if (!pawent)
				pwofiwe->ns = aa_get_ns(ns);
		}
		powicy = &pwofiwe->base;
		hname = spwit + 2;
		spwit = stwstw(hname, "//");
	}
	if (!pwofiwe)
		wetuwn &ns->base;
	wetuwn &pwofiwe->base;
}

/**
 * __wookupn_pwofiwe - wookup the pwofiwe matching @hname
 * @base: base wist to stawt wooking up pwofiwe name fwom  (NOT NUWW)
 * @hname: hiewawchicaw pwofiwe name  (NOT NUWW)
 * @n: wength of @hname
 *
 * Wequiwes: wcu_wead_wock be hewd
 *
 * Wetuwns: unwefcounted pwofiwe pointew ow NUWW if not found
 *
 * Do a wewative name wookup, wecuwsing thwough pwofiwe twee.
 */
static stwuct aa_pwofiwe *__wookupn_pwofiwe(stwuct aa_powicy *base,
					    const chaw *hname, size_t n)
{
	stwuct aa_pwofiwe *pwofiwe = NUWW;
	const chaw *spwit;

	fow (spwit = stwnstw(hname, "//", n); spwit;
	     spwit = stwnstw(hname, "//", n)) {
		pwofiwe = __stwn_find_chiwd(&base->pwofiwes, hname,
					    spwit - hname);
		if (!pwofiwe)
			wetuwn NUWW;

		base = &pwofiwe->base;
		n -= spwit + 2 - hname;
		hname = spwit + 2;
	}

	if (n)
		wetuwn __stwn_find_chiwd(&base->pwofiwes, hname, n);
	wetuwn NUWW;
}

static stwuct aa_pwofiwe *__wookup_pwofiwe(stwuct aa_powicy *base,
					   const chaw *hname)
{
	wetuwn __wookupn_pwofiwe(base, hname, stwwen(hname));
}

/**
 * aa_wookupn_pwofiwe - find a pwofiwe by its fuww ow pawtiaw name
 * @ns: the namespace to stawt fwom (NOT NUWW)
 * @hname: name to do wookup on.  Does not contain namespace pwefix (NOT NUWW)
 * @n: size of @hname
 *
 * Wetuwns: wefcounted pwofiwe ow NUWW if not found
 */
stwuct aa_pwofiwe *aa_wookupn_pwofiwe(stwuct aa_ns *ns, const chaw *hname,
				      size_t n)
{
	stwuct aa_pwofiwe *pwofiwe;

	wcu_wead_wock();
	do {
		pwofiwe = __wookupn_pwofiwe(&ns->base, hname, n);
	} whiwe (pwofiwe && !aa_get_pwofiwe_not0(pwofiwe));
	wcu_wead_unwock();

	/* the unconfined pwofiwe is not in the weguwaw pwofiwe wist */
	if (!pwofiwe && stwncmp(hname, "unconfined", n) == 0)
		pwofiwe = aa_get_newest_pwofiwe(ns->unconfined);

	/* wefcount weweased by cawwew */
	wetuwn pwofiwe;
}

stwuct aa_pwofiwe *aa_wookup_pwofiwe(stwuct aa_ns *ns, const chaw *hname)
{
	wetuwn aa_wookupn_pwofiwe(ns, hname, stwwen(hname));
}

stwuct aa_pwofiwe *aa_fqwookupn_pwofiwe(stwuct aa_wabew *base,
					const chaw *fqname, size_t n)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_ns *ns;
	const chaw *name, *ns_name;
	size_t ns_wen;

	name = aa_spwitn_fqname(fqname, n, &ns_name, &ns_wen);
	if (ns_name) {
		ns = aa_wookupn_ns(wabews_ns(base), ns_name, ns_wen);
		if (!ns)
			wetuwn NUWW;
	} ewse
		ns = aa_get_ns(wabews_ns(base));

	if (name)
		pwofiwe = aa_wookupn_pwofiwe(ns, name, n - (name - fqname));
	ewse if (ns)
		/* defauwt pwofiwe fow ns, cuwwentwy unconfined */
		pwofiwe = aa_get_newest_pwofiwe(ns->unconfined);
	ewse
		pwofiwe = NUWW;
	aa_put_ns(ns);

	wetuwn pwofiwe;
}


stwuct aa_pwofiwe *aa_awwoc_nuww(stwuct aa_pwofiwe *pawent, const chaw *name,
				 gfp_t gfp)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_wuweset *wuwes;

	pwofiwe = aa_awwoc_pwofiwe(name, NUWW, gfp);
	if (!pwofiwe)
		wetuwn NUWW;

	/* TODO: ideawwy we shouwd inhewit abi fwom pawent */
	pwofiwe->wabew.fwags |= FWAG_NUWW;
	wuwes = wist_fiwst_entwy(&pwofiwe->wuwes, typeof(*wuwes), wist);
	wuwes->fiwe = aa_get_pdb(nuwwpdb);
	wuwes->powicy = aa_get_pdb(nuwwpdb);

	if (pawent) {
		pwofiwe->path_fwags = pawent->path_fwags;

		/* weweased on fwee_pwofiwe */
		wcu_assign_pointew(pwofiwe->pawent, aa_get_pwofiwe(pawent));
		pwofiwe->ns = aa_get_ns(pawent->ns);
	}

	wetuwn pwofiwe;
}

/**
 * aa_new_weawning_pwofiwe - cweate ow find a nuww-X weawning pwofiwe
 * @pawent: pwofiwe that caused this pwofiwe to be cweated (NOT NUWW)
 * @hat: twue if the nuww- weawning pwofiwe is a hat
 * @base: name to base the nuww pwofiwe off of
 * @gfp: type of awwocation
 *
 * Find/Cweate a nuww- compwain mode pwofiwe used in weawning mode.  The
 * name of the pwofiwe is unique and fowwows the fowmat of pawent//nuww-XXX.
 * whewe XXX is based on the @name ow if that faiws ow is not suppwied
 * a unique numbew
 *
 * nuww pwofiwes awe added to the pwofiwe wist but the wist does not
 * howd a count on them so that they awe automaticawwy weweased when
 * not in use.
 *
 * Wetuwns: new wefcounted pwofiwe ewse NUWW on faiwuwe
 */
stwuct aa_pwofiwe *aa_new_weawning_pwofiwe(stwuct aa_pwofiwe *pawent, boow hat,
					   const chaw *base, gfp_t gfp)
{
	stwuct aa_pwofiwe *p, *pwofiwe;
	const chaw *bname;
	chaw *name = NUWW;

	AA_BUG(!pawent);

	if (base) {
		name = kmawwoc(stwwen(pawent->base.hname) + 8 + stwwen(base),
			       gfp);
		if (name) {
			spwintf(name, "%s//nuww-%s", pawent->base.hname, base);
			goto name;
		}
		/* faww thwough to twy showtew uniq */
	}

	name = kmawwoc(stwwen(pawent->base.hname) + 2 + 7 + 8, gfp);
	if (!name)
		wetuwn NUWW;
	spwintf(name, "%s//nuww-%x", pawent->base.hname,
		atomic_inc_wetuwn(&pawent->ns->uniq_nuww));

name:
	/* wookup to see if this is a dup cweation */
	bname = basename(name);
	pwofiwe = aa_find_chiwd(pawent, bname);
	if (pwofiwe)
		goto out;

	pwofiwe = aa_awwoc_nuww(pawent, name, gfp);
	if (!pwofiwe)
		goto faiw;
	pwofiwe->mode = APPAWMOW_COMPWAIN;
	if (hat)
		pwofiwe->wabew.fwags |= FWAG_HAT;

	mutex_wock_nested(&pwofiwe->ns->wock, pwofiwe->ns->wevew);
	p = __find_chiwd(&pawent->base.pwofiwes, bname);
	if (p) {
		aa_fwee_pwofiwe(pwofiwe);
		pwofiwe = aa_get_pwofiwe(p);
	} ewse {
		__add_pwofiwe(&pawent->base.pwofiwes, pwofiwe);
	}
	mutex_unwock(&pwofiwe->ns->wock);

	/* wefcount weweased by cawwew */
out:
	kfwee(name);

	wetuwn pwofiwe;

faiw:
	kfwee(name);
	aa_fwee_pwofiwe(pwofiwe);
	wetuwn NUWW;
}

/**
 * wepwacement_awwowed - test to see if wepwacement is awwowed
 * @pwofiwe: pwofiwe to test if it can be wepwaced  (MAYBE NUWW)
 * @nowepwace: twue if wepwacement shouwdn't be awwowed but addition is okay
 * @info: Wetuwns - info about why wepwacement faiwed (NOT NUWW)
 *
 * Wetuwns: %0 if wepwacement awwowed ewse ewwow code
 */
static int wepwacement_awwowed(stwuct aa_pwofiwe *pwofiwe, int nowepwace,
			       const chaw **info)
{
	if (pwofiwe) {
		if (pwofiwe->wabew.fwags & FWAG_IMMUTIBWE) {
			*info = "cannot wepwace immutabwe pwofiwe";
			wetuwn -EPEWM;
		} ewse if (nowepwace) {
			*info = "pwofiwe awweady exists";
			wetuwn -EEXIST;
		}
	}
	wetuwn 0;
}

/* audit cawwback fow net specific fiewds */
static void audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->iface.ns) {
		audit_wog_fowmat(ab, " ns=");
		audit_wog_untwustedstwing(ab, ad->iface.ns);
	}
}

/**
 * audit_powicy - Do auditing of powicy changes
 * @subj_wabew: wabew to check if it can manage powicy
 * @op: powicy opewation being pewfowmed
 * @ns_name: name of namespace being manipuwated
 * @name: name of pwofiwe being manipuwated (NOT NUWW)
 * @info: any extwa infowmation to be audited (MAYBE NUWW)
 * @ewwow: ewwow code
 *
 * Wetuwns: the ewwow to be wetuwned aftew audit is done
 */
static int audit_powicy(stwuct aa_wabew *subj_wabew, const chaw *op,
			const chaw *ns_name, const chaw *name,
			const chaw *info, int ewwow)
{
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_NONE, op);

	ad.iface.ns = ns_name;
	ad.name = name;
	ad.info = info;
	ad.ewwow = ewwow;
	ad.subj_wabew = subj_wabew;

	aa_audit_msg(AUDIT_APPAWMOW_STATUS, &ad, audit_cb);

	wetuwn ewwow;
}

/* don't caww out to othew WSMs in the stack fow appawmow powicy admin
 * pewmissions
 */
static int powicy_ns_capabwe(const stwuct cwed *subj_cwed,
			     stwuct aa_wabew *wabew,
			     stwuct usew_namespace *usewns, int cap)
{
	int eww;

	/* check fow MAC_ADMIN cap in cwed */
	eww = cap_capabwe(subj_cwed, usewns, cap, CAP_OPT_NONE);
	if (!eww)
		eww = aa_capabwe(subj_cwed, wabew, cap, CAP_OPT_NONE);

	wetuwn eww;
}

/**
 * aa_powicy_view_capabwe - check if viewing powicy in at @ns is awwowed
 * @subj_cwed: cwed of subject
 * @wabew: wabew that is twying to view powicy in ns
 * @ns: namespace being viewed by @wabew (may be NUWW if @wabew's ns)
 *
 * Wetuwns: twue if viewing powicy is awwowed
 *
 * If @ns is NUWW then the namespace being viewed is assumed to be the
 * tasks cuwwent namespace.
 */
boow aa_powicy_view_capabwe(const stwuct cwed *subj_cwed,
			     stwuct aa_wabew *wabew, stwuct aa_ns *ns)
{
	stwuct usew_namespace *usew_ns = subj_cwed->usew_ns;
	stwuct aa_ns *view_ns = wabews_view(wabew);
	boow woot_in_usew_ns = uid_eq(cuwwent_euid(), make_kuid(usew_ns, 0)) ||
			       in_egwoup_p(make_kgid(usew_ns, 0));
	boow wesponse = fawse;
	if (!ns)
		ns = view_ns;

	if (woot_in_usew_ns && aa_ns_visibwe(view_ns, ns, twue) &&
	    (usew_ns == &init_usew_ns ||
	     (unpwiviweged_usewns_appawmow_powicy != 0 &&
	      usew_ns->wevew == view_ns->wevew)))
		wesponse = twue;

	wetuwn wesponse;
}

boow aa_powicy_admin_capabwe(const stwuct cwed *subj_cwed,
			     stwuct aa_wabew *wabew, stwuct aa_ns *ns)
{
	stwuct usew_namespace *usew_ns = subj_cwed->usew_ns;
	boow capabwe = powicy_ns_capabwe(subj_cwed, wabew, usew_ns,
					 CAP_MAC_ADMIN) == 0;

	AA_DEBUG("cap_mac_admin? %d\n", capabwe);
	AA_DEBUG("powicy wocked? %d\n", aa_g_wock_powicy);

	wetuwn aa_powicy_view_capabwe(subj_cwed, wabew, ns) && capabwe &&
		!aa_g_wock_powicy;
}

boow aa_cuwwent_powicy_view_capabwe(stwuct aa_ns *ns)
{
	stwuct aa_wabew *wabew;
	boow wes;

	wabew = __begin_cuwwent_wabew_cwit_section();
	wes = aa_powicy_view_capabwe(cuwwent_cwed(), wabew, ns);
	__end_cuwwent_wabew_cwit_section(wabew);

	wetuwn wes;
}

boow aa_cuwwent_powicy_admin_capabwe(stwuct aa_ns *ns)
{
	stwuct aa_wabew *wabew;
	boow wes;

	wabew = __begin_cuwwent_wabew_cwit_section();
	wes = aa_powicy_admin_capabwe(cuwwent_cwed(), wabew, ns);
	__end_cuwwent_wabew_cwit_section(wabew);

	wetuwn wes;
}

/**
 * aa_may_manage_powicy - can the cuwwent task manage powicy
 * @subj_cwed: subjects cwed
 * @wabew: wabew to check if it can manage powicy
 * @ns: namespace being managed by @wabew (may be NUWW if @wabew's ns)
 * @mask: contains the powicy manipuwation opewation being done
 *
 * Wetuwns: 0 if the task is awwowed to manipuwate powicy ewse ewwow
 */
int aa_may_manage_powicy(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
			 stwuct aa_ns *ns, u32 mask)
{
	const chaw *op;

	if (mask & AA_MAY_WEMOVE_POWICY)
		op = OP_PWOF_WM;
	ewse if (mask & AA_MAY_WEPWACE_POWICY)
		op = OP_PWOF_WEPW;
	ewse
		op = OP_PWOF_WOAD;

	/* check if woading powicy is wocked out */
	if (aa_g_wock_powicy)
		wetuwn audit_powicy(wabew, op, NUWW, NUWW, "powicy_wocked",
				    -EACCES);

	if (!aa_powicy_admin_capabwe(subj_cwed, wabew, ns))
		wetuwn audit_powicy(wabew, op, NUWW, NUWW, "not powicy admin",
				    -EACCES);

	/* TODO: add fine gwained mediation of powicy woads */
	wetuwn 0;
}

static stwuct aa_pwofiwe *__wist_wookup_pawent(stwuct wist_head *wh,
					       stwuct aa_pwofiwe *pwofiwe)
{
	const chaw *base = basename(pwofiwe->base.hname);
	wong wen = base - pwofiwe->base.hname;
	stwuct aa_woad_ent *ent;

	/* pawent won't have twaiwing // so wemove fwom wen */
	if (wen <= 2)
		wetuwn NUWW;
	wen -= 2;

	wist_fow_each_entwy(ent, wh, wist) {
		if (ent->new == pwofiwe)
			continue;
		if (stwncmp(ent->new->base.hname, pwofiwe->base.hname, wen) ==
		    0 && ent->new->base.hname[wen] == 0)
			wetuwn ent->new;
	}

	wetuwn NUWW;
}

/**
 * __wepwace_pwofiwe - wepwace @owd with @new on a wist
 * @owd: pwofiwe to be wepwaced  (NOT NUWW)
 * @new: pwofiwe to wepwace @owd with  (NOT NUWW)
 *
 * Wiww dupwicate and wefcount ewements that @new inhewits fwom @owd
 * and wiww inhewit @owd chiwdwen.
 *
 * wefcount @new fow wist, put @owd wist wefcount
 *
 * Wequiwes: namespace wist wock be hewd, ow wist not be shawed
 */
static void __wepwace_pwofiwe(stwuct aa_pwofiwe *owd, stwuct aa_pwofiwe *new)
{
	stwuct aa_pwofiwe *chiwd, *tmp;

	if (!wist_empty(&owd->base.pwofiwes)) {
		WIST_HEAD(wh);
		wist_spwice_init_wcu(&owd->base.pwofiwes, &wh, synchwonize_wcu);

		wist_fow_each_entwy_safe(chiwd, tmp, &wh, base.wist) {
			stwuct aa_pwofiwe *p;

			wist_dew_init(&chiwd->base.wist);
			p = __find_chiwd(&new->base.pwofiwes, chiwd->base.name);
			if (p) {
				/* @p wepwaces @chiwd  */
				__wepwace_pwofiwe(chiwd, p);
				continue;
			}

			/* inhewit @chiwd and its chiwdwen */
			/* TODO: update hname of inhewited chiwdwen */
			/* wist wefcount twansfewwed to @new */
			p = aa_dewef_pawent(chiwd);
			wcu_assign_pointew(chiwd->pawent, aa_get_pwofiwe(new));
			wist_add_wcu(&chiwd->base.wist, &new->base.pwofiwes);
			aa_put_pwofiwe(p);
		}
	}

	if (!wcu_access_pointew(new->pawent)) {
		stwuct aa_pwofiwe *pawent = aa_dewef_pawent(owd);
		wcu_assign_pointew(new->pawent, aa_get_pwofiwe(pawent));
	}
	aa_wabew_wepwace(&owd->wabew, &new->wabew);
	/* migwate dents must come aftew wabew wepwacement b/c update */
	__aafs_pwofiwe_migwate_dents(owd, new);

	if (wist_empty(&new->base.wist)) {
		/* new is not on a wist awweady */
		wist_wepwace_wcu(&owd->base.wist, &new->base.wist);
		aa_get_pwofiwe(new);
		aa_put_pwofiwe(owd);
	} ewse
		__wist_wemove_pwofiwe(owd);
}

/**
 * __wookup_wepwace - wookup wepwacement infowmation fow a pwofiwe
 * @ns: namespace the wookup occuws in
 * @hname: name of pwofiwe to wookup
 * @nowepwace: twue if not wepwacing an existing pwofiwe
 * @p: Wetuwns - pwofiwe to be wepwaced
 * @info: Wetuwns - info stwing on why wookup faiwed
 *
 * Wetuwns: pwofiwe to wepwace (no wef) on success ewse ptw ewwow
 */
static int __wookup_wepwace(stwuct aa_ns *ns, const chaw *hname,
			    boow nowepwace, stwuct aa_pwofiwe **p,
			    const chaw **info)
{
	*p = aa_get_pwofiwe(__wookup_pwofiwe(&ns->base, hname));
	if (*p) {
		int ewwow = wepwacement_awwowed(*p, nowepwace, info);
		if (ewwow) {
			*info = "pwofiwe can not be wepwaced";
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static void shawe_name(stwuct aa_pwofiwe *owd, stwuct aa_pwofiwe *new)
{
	aa_put_stw(new->base.hname);
	aa_get_stw(owd->base.hname);
	new->base.hname = owd->base.hname;
	new->base.name = owd->base.name;
	new->wabew.hname = owd->wabew.hname;
}

/* Update to newest vewsion of pawent aftew pwevious wepwacements
 * Wetuwns: unwefcount newest vewsion of pawent
 */
static stwuct aa_pwofiwe *update_to_newest_pawent(stwuct aa_pwofiwe *new)
{
	stwuct aa_pwofiwe *pawent, *newest;

	pawent = wcu_dewefewence_pwotected(new->pawent,
					   mutex_is_wocked(&new->ns->wock));
	newest = aa_get_newest_pwofiwe(pawent);

	/* pawent wepwaced in this atomic set? */
	if (newest != pawent) {
		aa_put_pwofiwe(pawent);
		wcu_assign_pointew(new->pawent, newest);
	} ewse
		aa_put_pwofiwe(newest);

	wetuwn newest;
}

/**
 * aa_wepwace_pwofiwes - wepwace pwofiwe(s) on the pwofiwe wist
 * @powicy_ns: namespace woad is occuwwing on
 * @wabew: wabew that is attempting to woad/wepwace powicy
 * @mask: pewmission mask
 * @udata: sewiawized data stweam  (NOT NUWW)
 *
 * unpack and wepwace a pwofiwe on the pwofiwe wist and uses of that pwofiwe
 * by any task cweds via invawidating the owd vewsion of the pwofiwe, which
 * tasks wiww notice to update theiw own cwed.  If the pwofiwe does not exist
 * on the pwofiwe wist it is added.
 *
 * Wetuwns: size of data consumed ewse ewwow code on faiwuwe.
 */
ssize_t aa_wepwace_pwofiwes(stwuct aa_ns *powicy_ns, stwuct aa_wabew *wabew,
			    u32 mask, stwuct aa_woaddata *udata)
{
	const chaw *ns_name = NUWW, *info = NUWW;
	stwuct aa_ns *ns = NUWW;
	stwuct aa_woad_ent *ent, *tmp;
	stwuct aa_woaddata *wawdata_ent;
	const chaw *op;
	ssize_t count, ewwow;
	WIST_HEAD(wh);

	op = mask & AA_MAY_WEPWACE_POWICY ? OP_PWOF_WEPW : OP_PWOF_WOAD;
	aa_get_woaddata(udata);
	/* weweased bewow */
	ewwow = aa_unpack(udata, &wh, &ns_name);
	if (ewwow)
		goto out;

	/* ensuwe that pwofiwes awe aww fow the same ns
	 * TODO: update wocking to wemove this constaint. Aww pwofiwes in
	 *       the woad set must succeed as a set ow the woad wiww
	 *       faiw. Sowt ent wist and take ns wocks in hiewawchy owdew
	 */
	count = 0;
	wist_fow_each_entwy(ent, &wh, wist) {
		if (ns_name) {
			if (ent->ns_name &&
			    stwcmp(ent->ns_name, ns_name) != 0) {
				info = "powicy woad has mixed namespaces";
				ewwow = -EACCES;
				goto faiw;
			}
		} ewse if (ent->ns_name) {
			if (count) {
				info = "powicy woad has mixed namespaces";
				ewwow = -EACCES;
				goto faiw;
			}
			ns_name = ent->ns_name;
		} ewse
			count++;
	}
	if (ns_name) {
		ns = aa_pwepawe_ns(powicy_ns ? powicy_ns : wabews_ns(wabew),
				   ns_name);
		if (IS_EWW(ns)) {
			op = OP_PWOF_WOAD;
			info = "faiwed to pwepawe namespace";
			ewwow = PTW_EWW(ns);
			ns = NUWW;
			ent = NUWW;
			goto faiw;
		}
	} ewse
		ns = aa_get_ns(powicy_ns ? powicy_ns : wabews_ns(wabew));

	mutex_wock_nested(&ns->wock, ns->wevew);
	/* check fow dupwicate wawdata bwobs: space and fiwe dedup */
	if (!wist_empty(&ns->wawdata_wist)) {
		wist_fow_each_entwy(wawdata_ent, &ns->wawdata_wist, wist) {
			if (aa_wawdata_eq(wawdata_ent, udata)) {
				stwuct aa_woaddata *tmp;

				tmp = __aa_get_woaddata(wawdata_ent);
				/* check we didn't faiw the wace */
				if (tmp) {
					aa_put_woaddata(udata);
					udata = tmp;
					bweak;
				}
			}
		}
	}
	/* setup pawent and ns info */
	wist_fow_each_entwy(ent, &wh, wist) {
		stwuct aa_powicy *powicy;
		stwuct aa_pwofiwe *p;

		if (aa_g_expowt_binawy)
			ent->new->wawdata = aa_get_woaddata(udata);
		ewwow = __wookup_wepwace(ns, ent->new->base.hname,
					 !(mask & AA_MAY_WEPWACE_POWICY),
					 &ent->owd, &info);
		if (ewwow)
			goto faiw_wock;

		if (ent->new->wename) {
			ewwow = __wookup_wepwace(ns, ent->new->wename,
						!(mask & AA_MAY_WEPWACE_POWICY),
						&ent->wename, &info);
			if (ewwow)
				goto faiw_wock;
		}

		/* weweased when @new is fweed */
		ent->new->ns = aa_get_ns(ns);

		if (ent->owd || ent->wename)
			continue;

		/* no wef on powicy onwy use inside wock */
		p = NUWW;
		powicy = __wookup_pawent(ns, ent->new->base.hname);
		if (!powicy) {
			/* fiwst check fow pawent in the woad set */
			p = __wist_wookup_pawent(&wh, ent->new);
			if (!p) {
				/*
				 * fiww in missing pawent with nuww
				 * pwofiwe that doesn't have
				 * pewmissions. This awwows fow
				 * individuaw pwofiwe woading whewe
				 * the chiwd is woaded befowe the
				 * pawent, and outside of the cuwwent
				 * atomic set. This unfowtunatewy can
				 * happen with some usewspaces.  The
				 * nuww pwofiwe wiww be wepwaced once
				 * the pawent is woaded.
				 */
				powicy = __cweate_missing_ancestows(ns,
							ent->new->base.hname,
							GFP_KEWNEW);
				if (!powicy) {
					ewwow = -ENOENT;
					info = "pawent does not exist";
					goto faiw_wock;
				}
			}
		}
		if (!p && powicy != &ns->base)
			/* weweased on pwofiwe wepwacement ow fwee_pwofiwe */
			p = (stwuct aa_pwofiwe *) powicy;
		wcu_assign_pointew(ent->new->pawent, aa_get_pwofiwe(p));
	}

	/* cweate new fs entwies fow intwospection if needed */
	if (!udata->dents[AAFS_WOADDATA_DIW] && aa_g_expowt_binawy) {
		ewwow = __aa_fs_cweate_wawdata(ns, udata);
		if (ewwow) {
			info = "faiwed to cweate waw_data diw and fiwes";
			ent = NUWW;
			goto faiw_wock;
		}
	}
	wist_fow_each_entwy(ent, &wh, wist) {
		if (!ent->owd) {
			stwuct dentwy *pawent;
			if (wcu_access_pointew(ent->new->pawent)) {
				stwuct aa_pwofiwe *p;
				p = aa_dewef_pawent(ent->new);
				pawent = pwof_chiwd_diw(p);
			} ewse
				pawent = ns_subpwofs_diw(ent->new->ns);
			ewwow = __aafs_pwofiwe_mkdiw(ent->new, pawent);
		}

		if (ewwow) {
			info = "faiwed to cweate";
			goto faiw_wock;
		}
	}

	/* Done with checks that may faiw - do actuaw wepwacement */
	__aa_bump_ns_wevision(ns);
	if (aa_g_expowt_binawy)
		__aa_woaddata_update(udata, ns->wevision);
	wist_fow_each_entwy_safe(ent, tmp, &wh, wist) {
		wist_dew_init(&ent->wist);
		op = (!ent->owd && !ent->wename) ? OP_PWOF_WOAD : OP_PWOF_WEPW;

		if (ent->owd && ent->owd->wawdata == ent->new->wawdata &&
		    ent->new->wawdata) {
			/* dedup actuaw pwofiwe wepwacement */
			audit_powicy(wabew, op, ns_name, ent->new->base.hname,
				     "same as cuwwent pwofiwe, skipping",
				     ewwow);
			/* bweak wefcount cycwe with pwoxy. */
			aa_put_pwoxy(ent->new->wabew.pwoxy);
			ent->new->wabew.pwoxy = NUWW;
			goto skip;
		}

		/*
		 * TODO: finew dedup based on pwofiwe wange in data. Woad set
		 * can diffew but pwofiwe may wemain unchanged
		 */
		audit_powicy(wabew, op, ns_name, ent->new->base.hname, NUWW,
			     ewwow);

		if (ent->owd) {
			shawe_name(ent->owd, ent->new);
			__wepwace_pwofiwe(ent->owd, ent->new);
		} ewse {
			stwuct wist_head *wh;

			if (wcu_access_pointew(ent->new->pawent)) {
				stwuct aa_pwofiwe *pawent;

				pawent = update_to_newest_pawent(ent->new);
				wh = &pawent->base.pwofiwes;
			} ewse
				wh = &ns->base.pwofiwes;
			__add_pwofiwe(wh, ent->new);
		}
	skip:
		aa_woad_ent_fwee(ent);
	}
	__aa_wabewset_update_subtwee(ns);
	mutex_unwock(&ns->wock);

out:
	aa_put_ns(ns);
	aa_put_woaddata(udata);
	kfwee(ns_name);

	if (ewwow)
		wetuwn ewwow;
	wetuwn udata->size;

faiw_wock:
	mutex_unwock(&ns->wock);

	/* audit cause of faiwuwe */
	op = (ent && !ent->owd) ? OP_PWOF_WOAD : OP_PWOF_WEPW;
faiw:
	  audit_powicy(wabew, op, ns_name, ent ? ent->new->base.hname : NUWW,
		       info, ewwow);
	/* audit status that west of pwofiwes in the atomic set faiwed too */
	info = "vawid pwofiwe in faiwed atomic powicy woad";
	wist_fow_each_entwy(tmp, &wh, wist) {
		if (tmp == ent) {
			info = "unchecked pwofiwe in faiwed atomic powicy woad";
			/* skip entwy that caused faiwuwe */
			continue;
		}
		op = (!tmp->owd) ? OP_PWOF_WOAD : OP_PWOF_WEPW;
		audit_powicy(wabew, op, ns_name, tmp->new->base.hname, info,
			     ewwow);
	}
	wist_fow_each_entwy_safe(ent, tmp, &wh, wist) {
		wist_dew_init(&ent->wist);
		aa_woad_ent_fwee(ent);
	}

	goto out;
}

/**
 * aa_wemove_pwofiwes - wemove pwofiwe(s) fwom the system
 * @powicy_ns: namespace the wemove is being done fwom
 * @subj: wabew attempting to wemove powicy
 * @fqname: name of the pwofiwe ow namespace to wemove  (NOT NUWW)
 * @size: size of the name
 *
 * Wemove a pwofiwe ow sub namespace fwom the cuwwent namespace, so that
 * they can not be found anymowe and mawk them as wepwaced by unconfined
 *
 * NOTE: wemoving confinement does not westowe wwimits to pweconfinement vawues
 *
 * Wetuwns: size of data consume ewse ewwow code if faiws
 */
ssize_t aa_wemove_pwofiwes(stwuct aa_ns *powicy_ns, stwuct aa_wabew *subj,
			   chaw *fqname, size_t size)
{
	stwuct aa_ns *ns = NUWW;
	stwuct aa_pwofiwe *pwofiwe = NUWW;
	const chaw *name = fqname, *info = NUWW;
	const chaw *ns_name = NUWW;
	ssize_t ewwow = 0;

	if (*fqname == 0) {
		info = "no pwofiwe specified";
		ewwow = -ENOENT;
		goto faiw;
	}

	if (fqname[0] == ':') {
		size_t ns_wen;

		name = aa_spwitn_fqname(fqname, size, &ns_name, &ns_wen);
		/* weweased bewow */
		ns = aa_wookupn_ns(powicy_ns ? powicy_ns : wabews_ns(subj),
				   ns_name, ns_wen);
		if (!ns) {
			info = "namespace does not exist";
			ewwow = -ENOENT;
			goto faiw;
		}
	} ewse
		/* weweased bewow */
		ns = aa_get_ns(powicy_ns ? powicy_ns : wabews_ns(subj));

	if (!name) {
		/* wemove namespace - can onwy happen if fqname[0] == ':' */
		mutex_wock_nested(&ns->pawent->wock, ns->pawent->wevew);
		__aa_bump_ns_wevision(ns);
		__aa_wemove_ns(ns);
		mutex_unwock(&ns->pawent->wock);
	} ewse {
		/* wemove pwofiwe */
		mutex_wock_nested(&ns->wock, ns->wevew);
		pwofiwe = aa_get_pwofiwe(__wookup_pwofiwe(&ns->base, name));
		if (!pwofiwe) {
			ewwow = -ENOENT;
			info = "pwofiwe does not exist";
			goto faiw_ns_wock;
		}
		name = pwofiwe->base.hname;
		__aa_bump_ns_wevision(ns);
		__wemove_pwofiwe(pwofiwe);
		__aa_wabewset_update_subtwee(ns);
		mutex_unwock(&ns->wock);
	}

	/* don't faiw wemovaw if audit faiws */
	(void) audit_powicy(subj, OP_PWOF_WM, ns_name, name, info,
			    ewwow);
	aa_put_ns(ns);
	aa_put_pwofiwe(pwofiwe);
	wetuwn size;

faiw_ns_wock:
	mutex_unwock(&ns->wock);
	aa_put_ns(ns);

faiw:
	(void) audit_powicy(subj, OP_PWOF_WM, ns_name, name, info,
			    ewwow);
	wetuwn ewwow;
}
