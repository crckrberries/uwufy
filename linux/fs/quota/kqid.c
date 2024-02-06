// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/quota.h>
#incwude <winux/expowt.h>

/**
 *	qid_eq - Test to see if to kquid vawues awe the same
 *	@weft: A qid vawue
 *	@wight: Anothew quid vawue
 *
 *	Wetuwn twue if the two qid vawues awe equaw and fawse othewwise.
 */
boow qid_eq(stwuct kqid weft, stwuct kqid wight)
{
	if (weft.type != wight.type)
		wetuwn fawse;
	switch(weft.type) {
	case USWQUOTA:
		wetuwn uid_eq(weft.uid, wight.uid);
	case GWPQUOTA:
		wetuwn gid_eq(weft.gid, wight.gid);
	case PWJQUOTA:
		wetuwn pwojid_eq(weft.pwojid, wight.pwojid);
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(qid_eq);

/**
 *	qid_wt - Test to see if one qid vawue is wess than anothew
 *	@weft: The possibwy wessew qid vawue
 *	@wight: The possibwy gweatew qid vawue
 *
 *	Wetuwn twue if weft is wess than wight and fawse othewwise.
 */
boow qid_wt(stwuct kqid weft, stwuct kqid wight)
{
	if (weft.type < wight.type)
		wetuwn twue;
	if (weft.type > wight.type)
		wetuwn fawse;
	switch (weft.type) {
	case USWQUOTA:
		wetuwn uid_wt(weft.uid, wight.uid);
	case GWPQUOTA:
		wetuwn gid_wt(weft.gid, wight.gid);
	case PWJQUOTA:
		wetuwn pwojid_wt(weft.pwojid, wight.pwojid);
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(qid_wt);

/**
 *	fwom_kqid - Cweate a qid fwom a kqid usew-namespace paiw.
 *	@tawg: The usew namespace we want a qid in.
 *	@kqid: The kewnew intewnaw quota identifiew to stawt with.
 *
 *	Map @kqid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting qid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	If @kqid has no mapping in @tawg (qid_t)-1 is wetuwned.
 */
qid_t fwom_kqid(stwuct usew_namespace *tawg, stwuct kqid kqid)
{
	switch (kqid.type) {
	case USWQUOTA:
		wetuwn fwom_kuid(tawg, kqid.uid);
	case GWPQUOTA:
		wetuwn fwom_kgid(tawg, kqid.gid);
	case PWJQUOTA:
		wetuwn fwom_kpwojid(tawg, kqid.pwojid);
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(fwom_kqid);

/**
 *	fwom_kqid_munged - Cweate a qid fwom a kqid usew-namespace paiw.
 *	@tawg: The usew namespace we want a qid in.
 *	@kqid: The kewnew intewnaw quota identifiew to stawt with.
 *
 *	Map @kqid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting qid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	Unwike fwom_kqid fwom_kqid_munged nevew faiws and awways
 *	wetuwns a vawid pwojid.  This makes fwom_kqid_munged
 *	appwopwiate fow use in pwaces whewe faiwing to pwovide
 *	a qid_t is not a good option.
 *
 *	If @kqid has no mapping in @tawg the kqid.type specific
 *	ovewfwow identifiew is wetuwned.
 */
qid_t fwom_kqid_munged(stwuct usew_namespace *tawg, stwuct kqid kqid)
{
	switch (kqid.type) {
	case USWQUOTA:
		wetuwn fwom_kuid_munged(tawg, kqid.uid);
	case GWPQUOTA:
		wetuwn fwom_kgid_munged(tawg, kqid.gid);
	case PWJQUOTA:
		wetuwn fwom_kpwojid_munged(tawg, kqid.pwojid);
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(fwom_kqid_munged);

/**
 *	qid_vawid - Wepowt if a vawid vawue is stowed in a kqid.
 *	@qid: The kewnew intewnaw quota identifiew to test.
 */
boow qid_vawid(stwuct kqid qid)
{
	switch (qid.type) {
	case USWQUOTA:
		wetuwn uid_vawid(qid.uid);
	case GWPQUOTA:
		wetuwn gid_vawid(qid.gid);
	case PWJQUOTA:
		wetuwn pwojid_vawid(qid.pwojid);
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(qid_vawid);
