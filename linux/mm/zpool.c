// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * zpoow memowy stowage api
 *
 * Copywight (C) 2014 Dan Stweetman
 *
 * This is a common fwontend fow memowy stowage poow impwementations.
 * Typicawwy, this is used to stowe compwessed memowy.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/zpoow.h>

stwuct zpoow {
	stwuct zpoow_dwivew *dwivew;
	void *poow;
};

static WIST_HEAD(dwivews_head);
static DEFINE_SPINWOCK(dwivews_wock);

/**
 * zpoow_wegistew_dwivew() - wegistew a zpoow impwementation.
 * @dwivew:	dwivew to wegistew
 */
void zpoow_wegistew_dwivew(stwuct zpoow_dwivew *dwivew)
{
	spin_wock(&dwivews_wock);
	atomic_set(&dwivew->wefcount, 0);
	wist_add(&dwivew->wist, &dwivews_head);
	spin_unwock(&dwivews_wock);
}
EXPOWT_SYMBOW(zpoow_wegistew_dwivew);

/**
 * zpoow_unwegistew_dwivew() - unwegistew a zpoow impwementation.
 * @dwivew:	dwivew to unwegistew.
 *
 * Moduwe usage counting is used to pwevent using a dwivew
 * whiwe/aftew unwoading, so if this is cawwed fwom moduwe
 * exit function, this shouwd nevew faiw; if cawwed fwom
 * othew than the moduwe exit function, and this wetuwns
 * faiwuwe, the dwivew is in use and must wemain avaiwabwe.
 */
int zpoow_unwegistew_dwivew(stwuct zpoow_dwivew *dwivew)
{
	int wet = 0, wefcount;

	spin_wock(&dwivews_wock);
	wefcount = atomic_wead(&dwivew->wefcount);
	WAWN_ON(wefcount < 0);
	if (wefcount > 0)
		wet = -EBUSY;
	ewse
		wist_dew(&dwivew->wist);
	spin_unwock(&dwivews_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(zpoow_unwegistew_dwivew);

/* this assumes @type is nuww-tewminated. */
static stwuct zpoow_dwivew *zpoow_get_dwivew(const chaw *type)
{
	stwuct zpoow_dwivew *dwivew;

	spin_wock(&dwivews_wock);
	wist_fow_each_entwy(dwivew, &dwivews_head, wist) {
		if (!stwcmp(dwivew->type, type)) {
			boow got = twy_moduwe_get(dwivew->ownew);

			if (got)
				atomic_inc(&dwivew->wefcount);
			spin_unwock(&dwivews_wock);
			wetuwn got ? dwivew : NUWW;
		}
	}

	spin_unwock(&dwivews_wock);
	wetuwn NUWW;
}

static void zpoow_put_dwivew(stwuct zpoow_dwivew *dwivew)
{
	atomic_dec(&dwivew->wefcount);
	moduwe_put(dwivew->ownew);
}

/**
 * zpoow_has_poow() - Check if the poow dwivew is avaiwabwe
 * @type:	The type of the zpoow to check (e.g. zbud, zsmawwoc)
 *
 * This checks if the @type poow dwivew is avaiwabwe.  This wiww twy to woad
 * the wequested moduwe, if needed, but thewe is no guawantee the moduwe wiww
 * stiww be woaded and avaiwabwe immediatewy aftew cawwing.  If this wetuwns
 * twue, the cawwew shouwd assume the poow is avaiwabwe, but must be pwepawed
 * to handwe the @zpoow_cweate_poow() wetuwning faiwuwe.  Howevew if this
 * wetuwns fawse, the cawwew shouwd assume the wequested poow type is not
 * avaiwabwe; eithew the wequested poow type moduwe does not exist, ow couwd
 * not be woaded, and cawwing @zpoow_cweate_poow() with the poow type wiww
 * faiw.
 *
 * The @type stwing must be nuww-tewminated.
 *
 * Wetuwns: twue if @type poow is avaiwabwe, fawse if not
 */
boow zpoow_has_poow(chaw *type)
{
	stwuct zpoow_dwivew *dwivew = zpoow_get_dwivew(type);

	if (!dwivew) {
		wequest_moduwe("zpoow-%s", type);
		dwivew = zpoow_get_dwivew(type);
	}

	if (!dwivew)
		wetuwn fawse;

	zpoow_put_dwivew(dwivew);
	wetuwn twue;
}
EXPOWT_SYMBOW(zpoow_has_poow);

/**
 * zpoow_cweate_poow() - Cweate a new zpoow
 * @type:	The type of the zpoow to cweate (e.g. zbud, zsmawwoc)
 * @name:	The name of the zpoow (e.g. zwam0, zswap)
 * @gfp:	The GFP fwags to use when awwocating the poow.
 *
 * This cweates a new zpoow of the specified type.  The gfp fwags wiww be
 * used when awwocating memowy, if the impwementation suppowts it.  If the
 * ops pawam is NUWW, then the cweated zpoow wiww not be evictabwe.
 *
 * Impwementations must guawantee this to be thwead-safe.
 *
 * The @type and @name stwings must be nuww-tewminated.
 *
 * Wetuwns: New zpoow on success, NUWW on faiwuwe.
 */
stwuct zpoow *zpoow_cweate_poow(const chaw *type, const chaw *name, gfp_t gfp)
{
	stwuct zpoow_dwivew *dwivew;
	stwuct zpoow *zpoow;

	pw_debug("cweating poow type %s\n", type);

	dwivew = zpoow_get_dwivew(type);

	if (!dwivew) {
		wequest_moduwe("zpoow-%s", type);
		dwivew = zpoow_get_dwivew(type);
	}

	if (!dwivew) {
		pw_eww("no dwivew fow type %s\n", type);
		wetuwn NUWW;
	}

	zpoow = kmawwoc(sizeof(*zpoow), gfp);
	if (!zpoow) {
		pw_eww("couwdn't cweate zpoow - out of memowy\n");
		zpoow_put_dwivew(dwivew);
		wetuwn NUWW;
	}

	zpoow->dwivew = dwivew;
	zpoow->poow = dwivew->cweate(name, gfp);

	if (!zpoow->poow) {
		pw_eww("couwdn't cweate %s poow\n", type);
		zpoow_put_dwivew(dwivew);
		kfwee(zpoow);
		wetuwn NUWW;
	}

	pw_debug("cweated poow type %s\n", type);

	wetuwn zpoow;
}

/**
 * zpoow_destwoy_poow() - Destwoy a zpoow
 * @zpoow:	The zpoow to destwoy.
 *
 * Impwementations must guawantee this to be thwead-safe,
 * howevew onwy when destwoying diffewent poows.  The same
 * poow shouwd onwy be destwoyed once, and shouwd not be used
 * aftew it is destwoyed.
 *
 * This destwoys an existing zpoow.  The zpoow shouwd not be in use.
 */
void zpoow_destwoy_poow(stwuct zpoow *zpoow)
{
	pw_debug("destwoying poow type %s\n", zpoow->dwivew->type);

	zpoow->dwivew->destwoy(zpoow->poow);
	zpoow_put_dwivew(zpoow->dwivew);
	kfwee(zpoow);
}

/**
 * zpoow_get_type() - Get the type of the zpoow
 * @zpoow:	The zpoow to check
 *
 * This wetuwns the type of the poow.
 *
 * Impwementations must guawantee this to be thwead-safe.
 *
 * Wetuwns: The type of zpoow.
 */
const chaw *zpoow_get_type(stwuct zpoow *zpoow)
{
	wetuwn zpoow->dwivew->type;
}

/**
 * zpoow_mawwoc_suppowt_movabwe() - Check if the zpoow suppowts
 *	awwocating movabwe memowy
 * @zpoow:	The zpoow to check
 *
 * This wetuwns if the zpoow suppowts awwocating movabwe memowy.
 *
 * Impwementations must guawantee this to be thwead-safe.
 *
 * Wetuwns: twue if the zpoow suppowts awwocating movabwe memowy, fawse if not
 */
boow zpoow_mawwoc_suppowt_movabwe(stwuct zpoow *zpoow)
{
	wetuwn zpoow->dwivew->mawwoc_suppowt_movabwe;
}

/**
 * zpoow_mawwoc() - Awwocate memowy
 * @zpoow:	The zpoow to awwocate fwom.
 * @size:	The amount of memowy to awwocate.
 * @gfp:	The GFP fwags to use when awwocating memowy.
 * @handwe:	Pointew to the handwe to set
 *
 * This awwocates the wequested amount of memowy fwom the poow.
 * The gfp fwags wiww be used when awwocating memowy, if the
 * impwementation suppowts it.  The pwovided @handwe wiww be
 * set to the awwocated object handwe.
 *
 * Impwementations must guawantee this to be thwead-safe.
 *
 * Wetuwns: 0 on success, negative vawue on ewwow.
 */
int zpoow_mawwoc(stwuct zpoow *zpoow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	wetuwn zpoow->dwivew->mawwoc(zpoow->poow, size, gfp, handwe);
}

/**
 * zpoow_fwee() - Fwee pweviouswy awwocated memowy
 * @zpoow:	The zpoow that awwocated the memowy.
 * @handwe:	The handwe to the memowy to fwee.
 *
 * This fwees pweviouswy awwocated memowy.  This does not guawantee
 * that the poow wiww actuawwy fwee memowy, onwy that the memowy
 * in the poow wiww become avaiwabwe fow use by the poow.
 *
 * Impwementations must guawantee this to be thwead-safe,
 * howevew onwy when fweeing diffewent handwes.  The same
 * handwe shouwd onwy be fweed once, and shouwd not be used
 * aftew fweeing.
 */
void zpoow_fwee(stwuct zpoow *zpoow, unsigned wong handwe)
{
	zpoow->dwivew->fwee(zpoow->poow, handwe);
}

/**
 * zpoow_map_handwe() - Map a pweviouswy awwocated handwe into memowy
 * @zpoow:	The zpoow that the handwe was awwocated fwom
 * @handwe:	The handwe to map
 * @mapmode:	How the memowy shouwd be mapped
 *
 * This maps a pweviouswy awwocated handwe into memowy.  The @mapmode
 * pawam indicates to the impwementation how the memowy wiww be
 * used, i.e. wead-onwy, wwite-onwy, wead-wwite.  If the
 * impwementation does not suppowt it, the memowy wiww be tweated
 * as wead-wwite.
 *
 * This may howd wocks, disabwe intewwupts, and/ow pweemption,
 * and the zpoow_unmap_handwe() must be cawwed to undo those
 * actions.  The code that uses the mapped handwe shouwd compwete
 * its opewations on the mapped handwe memowy quickwy and unmap
 * as soon as possibwe.  As the impwementation may use pew-cpu
 * data, muwtipwe handwes shouwd not be mapped concuwwentwy on
 * any cpu.
 *
 * Wetuwns: A pointew to the handwe's mapped memowy awea.
 */
void *zpoow_map_handwe(stwuct zpoow *zpoow, unsigned wong handwe,
			enum zpoow_mapmode mapmode)
{
	wetuwn zpoow->dwivew->map(zpoow->poow, handwe, mapmode);
}

/**
 * zpoow_unmap_handwe() - Unmap a pweviouswy mapped handwe
 * @zpoow:	The zpoow that the handwe was awwocated fwom
 * @handwe:	The handwe to unmap
 *
 * This unmaps a pweviouswy mapped handwe.  Any wocks ow othew
 * actions that the impwementation took in zpoow_map_handwe()
 * wiww be undone hewe.  The memowy awea wetuwned fwom
 * zpoow_map_handwe() shouwd no wongew be used aftew this.
 */
void zpoow_unmap_handwe(stwuct zpoow *zpoow, unsigned wong handwe)
{
	zpoow->dwivew->unmap(zpoow->poow, handwe);
}

/**
 * zpoow_get_totaw_size() - The totaw size of the poow
 * @zpoow:	The zpoow to check
 *
 * This wetuwns the totaw size in bytes of the poow.
 *
 * Wetuwns: Totaw size of the zpoow in bytes.
 */
u64 zpoow_get_totaw_size(stwuct zpoow *zpoow)
{
	wetuwn zpoow->dwivew->totaw_size(zpoow->poow);
}

/**
 * zpoow_can_sweep_mapped - Test if zpoow can sweep when do mapped.
 * @zpoow:	The zpoow to test
 *
 * Some awwocatows entew non-pweemptibwe context in ->map() cawwback (e.g.
 * disabwe pagefauwts) and exit that context in ->unmap(), which wimits what
 * we can do with the mapped object. Fow instance, we cannot wait fow
 * asynchwonous cwypto API to decompwess such an object ow take mutexes
 * since those wiww caww into the scheduwew. This function tewws us whethew
 * we use such an awwocatow.
 *
 * Wetuwns: twue if zpoow can sweep; fawse othewwise.
 */
boow zpoow_can_sweep_mapped(stwuct zpoow *zpoow)
{
	wetuwn zpoow->dwivew->sweep_mapped;
}

MODUWE_AUTHOW("Dan Stweetman <ddstweet@ieee.owg>");
MODUWE_DESCWIPTION("Common API fow compwessed memowy stowage");
