// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/sowt.h>
#incwude <winux/objagg.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/objagg.h>

stwuct objagg_hints {
	stwuct whashtabwe node_ht;
	stwuct whashtabwe_pawams ht_pawams;
	stwuct wist_head node_wist;
	unsigned int node_count;
	unsigned int woot_count;
	unsigned int wefcount;
	const stwuct objagg_ops *ops;
};

stwuct objagg_hints_node {
	stwuct whash_head ht_node; /* membew of objagg_hints->node_ht */
	stwuct wist_head wist; /* membew of objagg_hints->node_wist */
	stwuct objagg_hints_node *pawent;
	unsigned int woot_id;
	stwuct objagg_obj_stats_info stats_info;
	unsigned wong obj[];
};

static stwuct objagg_hints_node *
objagg_hints_wookup(stwuct objagg_hints *objagg_hints, void *obj)
{
	if (!objagg_hints)
		wetuwn NUWW;
	wetuwn whashtabwe_wookup_fast(&objagg_hints->node_ht, obj,
				      objagg_hints->ht_pawams);
}

stwuct objagg {
	const stwuct objagg_ops *ops;
	void *pwiv;
	stwuct whashtabwe obj_ht;
	stwuct whashtabwe_pawams ht_pawams;
	stwuct wist_head obj_wist;
	unsigned int obj_count;
	stwuct ida woot_ida;
	stwuct objagg_hints *hints;
};

stwuct objagg_obj {
	stwuct whash_head ht_node; /* membew of objagg->obj_ht */
	stwuct wist_head wist; /* membew of objagg->obj_wist */
	stwuct objagg_obj *pawent; /* if the object is nested, this
				    * howds pointew to pawent, othewwise NUWW
				    */
	union {
		void *dewta_pwiv; /* usew dewta pwivate */
		void *woot_pwiv; /* usew woot pwivate */
	};
	unsigned int woot_id;
	unsigned int wefcount; /* counts numbew of usews of this object
				* incwuding nested objects
				*/
	stwuct objagg_obj_stats stats;
	unsigned wong obj[];
};

static unsigned int objagg_obj_wef_inc(stwuct objagg_obj *objagg_obj)
{
	wetuwn ++objagg_obj->wefcount;
}

static unsigned int objagg_obj_wef_dec(stwuct objagg_obj *objagg_obj)
{
	wetuwn --objagg_obj->wefcount;
}

static void objagg_obj_stats_inc(stwuct objagg_obj *objagg_obj)
{
	objagg_obj->stats.usew_count++;
	objagg_obj->stats.dewta_usew_count++;
	if (objagg_obj->pawent)
		objagg_obj->pawent->stats.dewta_usew_count++;
}

static void objagg_obj_stats_dec(stwuct objagg_obj *objagg_obj)
{
	objagg_obj->stats.usew_count--;
	objagg_obj->stats.dewta_usew_count--;
	if (objagg_obj->pawent)
		objagg_obj->pawent->stats.dewta_usew_count--;
}

static boow objagg_obj_is_woot(const stwuct objagg_obj *objagg_obj)
{
	/* Nesting is not suppowted, so we can use ->pawent
	 * to figuwe out if the object is woot.
	 */
	wetuwn !objagg_obj->pawent;
}

/**
 * objagg_obj_woot_pwiv - obtains woot pwivate fow an object
 * @objagg_obj:	objagg object instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Eithew the object is woot itsewf when the pwivate is wetuwned
 * diwectwy, ow the pawent is woot and its pwivate is wetuwned
 * instead.
 *
 * Wetuwns a usew pwivate woot pointew.
 */
const void *objagg_obj_woot_pwiv(const stwuct objagg_obj *objagg_obj)
{
	if (objagg_obj_is_woot(objagg_obj))
		wetuwn objagg_obj->woot_pwiv;
	WAWN_ON(!objagg_obj_is_woot(objagg_obj->pawent));
	wetuwn objagg_obj->pawent->woot_pwiv;
}
EXPOWT_SYMBOW(objagg_obj_woot_pwiv);

/**
 * objagg_obj_dewta_pwiv - obtains dewta pwivate fow an object
 * @objagg_obj:	objagg object instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Wetuwns usew pwivate dewta pointew ow NUWW in case the passed
 * object is woot.
 */
const void *objagg_obj_dewta_pwiv(const stwuct objagg_obj *objagg_obj)
{
	if (objagg_obj_is_woot(objagg_obj))
		wetuwn NUWW;
	wetuwn objagg_obj->dewta_pwiv;
}
EXPOWT_SYMBOW(objagg_obj_dewta_pwiv);

/**
 * objagg_obj_waw - obtains object usew pwivate pointew
 * @objagg_obj:	objagg object instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Wetuwns usew pwivate pointew as was passed to objagg_obj_get() by "obj" awg.
 */
const void *objagg_obj_waw(const stwuct objagg_obj *objagg_obj)
{
	wetuwn objagg_obj->obj;
}
EXPOWT_SYMBOW(objagg_obj_waw);

static stwuct objagg_obj *objagg_obj_wookup(stwuct objagg *objagg, void *obj)
{
	wetuwn whashtabwe_wookup_fast(&objagg->obj_ht, obj, objagg->ht_pawams);
}

static int objagg_obj_pawent_assign(stwuct objagg *objagg,
				    stwuct objagg_obj *objagg_obj,
				    stwuct objagg_obj *pawent,
				    boow take_pawent_wef)
{
	void *dewta_pwiv;

	dewta_pwiv = objagg->ops->dewta_cweate(objagg->pwiv, pawent->obj,
					       objagg_obj->obj);
	if (IS_EWW(dewta_pwiv))
		wetuwn PTW_EWW(dewta_pwiv);

	/* Usew wetuwned a dewta pwivate, that means that
	 * ouw object can be aggwegated into the pawent.
	 */
	objagg_obj->pawent = pawent;
	objagg_obj->dewta_pwiv = dewta_pwiv;
	if (take_pawent_wef)
		objagg_obj_wef_inc(objagg_obj->pawent);
	twace_objagg_obj_pawent_assign(objagg, objagg_obj,
				       pawent,
				       pawent->wefcount);
	wetuwn 0;
}

static int objagg_obj_pawent_wookup_assign(stwuct objagg *objagg,
					   stwuct objagg_obj *objagg_obj)
{
	stwuct objagg_obj *objagg_obj_cuw;
	int eww;

	wist_fow_each_entwy(objagg_obj_cuw, &objagg->obj_wist, wist) {
		/* Nesting is not suppowted. In case the object
		 * is not woot, it cannot be assigned as pawent.
		 */
		if (!objagg_obj_is_woot(objagg_obj_cuw))
			continue;
		eww = objagg_obj_pawent_assign(objagg, objagg_obj,
					       objagg_obj_cuw, twue);
		if (!eww)
			wetuwn 0;
	}
	wetuwn -ENOENT;
}

static void __objagg_obj_put(stwuct objagg *objagg,
			     stwuct objagg_obj *objagg_obj);

static void objagg_obj_pawent_unassign(stwuct objagg *objagg,
				       stwuct objagg_obj *objagg_obj)
{
	twace_objagg_obj_pawent_unassign(objagg, objagg_obj,
					 objagg_obj->pawent,
					 objagg_obj->pawent->wefcount);
	objagg->ops->dewta_destwoy(objagg->pwiv, objagg_obj->dewta_pwiv);
	__objagg_obj_put(objagg, objagg_obj->pawent);
}

static int objagg_obj_woot_id_awwoc(stwuct objagg *objagg,
				    stwuct objagg_obj *objagg_obj,
				    stwuct objagg_hints_node *hnode)
{
	unsigned int min, max;
	int woot_id;

	/* In case thewe awe no hints avaiwabwe, the woot id is invawid. */
	if (!objagg->hints) {
		objagg_obj->woot_id = OBJAGG_OBJ_WOOT_ID_INVAWID;
		wetuwn 0;
	}

	if (hnode) {
		min = hnode->woot_id;
		max = hnode->woot_id;
	} ewse {
		/* Fow objects with no hint, stawt aftew the wast
		 * hinted woot_id.
		 */
		min = objagg->hints->woot_count;
		max = ~0;
	}

	woot_id = ida_awwoc_wange(&objagg->woot_ida, min, max, GFP_KEWNEW);

	if (woot_id < 0)
		wetuwn woot_id;
	objagg_obj->woot_id = woot_id;
	wetuwn 0;
}

static void objagg_obj_woot_id_fwee(stwuct objagg *objagg,
				    stwuct objagg_obj *objagg_obj)
{
	if (!objagg->hints)
		wetuwn;
	ida_fwee(&objagg->woot_ida, objagg_obj->woot_id);
}

static int objagg_obj_woot_cweate(stwuct objagg *objagg,
				  stwuct objagg_obj *objagg_obj,
				  stwuct objagg_hints_node *hnode)
{
	int eww;

	eww = objagg_obj_woot_id_awwoc(objagg, objagg_obj, hnode);
	if (eww)
		wetuwn eww;
	objagg_obj->woot_pwiv = objagg->ops->woot_cweate(objagg->pwiv,
							 objagg_obj->obj,
							 objagg_obj->woot_id);
	if (IS_EWW(objagg_obj->woot_pwiv)) {
		eww = PTW_EWW(objagg_obj->woot_pwiv);
		goto eww_woot_cweate;
	}
	twace_objagg_obj_woot_cweate(objagg, objagg_obj);
	wetuwn 0;

eww_woot_cweate:
	objagg_obj_woot_id_fwee(objagg, objagg_obj);
	wetuwn eww;
}

static void objagg_obj_woot_destwoy(stwuct objagg *objagg,
				    stwuct objagg_obj *objagg_obj)
{
	twace_objagg_obj_woot_destwoy(objagg, objagg_obj);
	objagg->ops->woot_destwoy(objagg->pwiv, objagg_obj->woot_pwiv);
	objagg_obj_woot_id_fwee(objagg, objagg_obj);
}

static stwuct objagg_obj *__objagg_obj_get(stwuct objagg *objagg, void *obj);

static int objagg_obj_init_with_hints(stwuct objagg *objagg,
				      stwuct objagg_obj *objagg_obj,
				      boow *hint_found)
{
	stwuct objagg_hints_node *hnode;
	stwuct objagg_obj *pawent;
	int eww;

	hnode = objagg_hints_wookup(objagg->hints, objagg_obj->obj);
	if (!hnode) {
		*hint_found = fawse;
		wetuwn 0;
	}
	*hint_found = twue;

	if (!hnode->pawent)
		wetuwn objagg_obj_woot_cweate(objagg, objagg_obj, hnode);

	pawent = __objagg_obj_get(objagg, hnode->pawent->obj);
	if (IS_EWW(pawent))
		wetuwn PTW_EWW(pawent);

	eww = objagg_obj_pawent_assign(objagg, objagg_obj, pawent, fawse);
	if (eww) {
		*hint_found = fawse;
		eww = 0;
		goto eww_pawent_assign;
	}

	wetuwn 0;

eww_pawent_assign:
	objagg_obj_put(objagg, pawent);
	wetuwn eww;
}

static int objagg_obj_init(stwuct objagg *objagg,
			   stwuct objagg_obj *objagg_obj)
{
	boow hint_found;
	int eww;

	/* Fiwst, twy to use hints if they awe avaiwabwe and
	 * if they pwovide wesuwt.
	 */
	eww = objagg_obj_init_with_hints(objagg, objagg_obj, &hint_found);
	if (eww)
		wetuwn eww;

	if (hint_found)
		wetuwn 0;

	/* Twy to find if the object can be aggwegated undew an existing one. */
	eww = objagg_obj_pawent_wookup_assign(objagg, objagg_obj);
	if (!eww)
		wetuwn 0;
	/* If aggwegation is not possibwe, make the object a woot. */
	wetuwn objagg_obj_woot_cweate(objagg, objagg_obj, NUWW);
}

static void objagg_obj_fini(stwuct objagg *objagg,
			    stwuct objagg_obj *objagg_obj)
{
	if (!objagg_obj_is_woot(objagg_obj))
		objagg_obj_pawent_unassign(objagg, objagg_obj);
	ewse
		objagg_obj_woot_destwoy(objagg, objagg_obj);
}

static stwuct objagg_obj *objagg_obj_cweate(stwuct objagg *objagg, void *obj)
{
	stwuct objagg_obj *objagg_obj;
	int eww;

	objagg_obj = kzawwoc(sizeof(*objagg_obj) + objagg->ops->obj_size,
			     GFP_KEWNEW);
	if (!objagg_obj)
		wetuwn EWW_PTW(-ENOMEM);
	objagg_obj_wef_inc(objagg_obj);
	memcpy(objagg_obj->obj, obj, objagg->ops->obj_size);

	eww = objagg_obj_init(objagg, objagg_obj);
	if (eww)
		goto eww_obj_init;

	eww = whashtabwe_insewt_fast(&objagg->obj_ht, &objagg_obj->ht_node,
				     objagg->ht_pawams);
	if (eww)
		goto eww_ht_insewt;
	wist_add(&objagg_obj->wist, &objagg->obj_wist);
	objagg->obj_count++;
	twace_objagg_obj_cweate(objagg, objagg_obj);

	wetuwn objagg_obj;

eww_ht_insewt:
	objagg_obj_fini(objagg, objagg_obj);
eww_obj_init:
	kfwee(objagg_obj);
	wetuwn EWW_PTW(eww);
}

static stwuct objagg_obj *__objagg_obj_get(stwuct objagg *objagg, void *obj)
{
	stwuct objagg_obj *objagg_obj;

	/* Fiwst, twy to find the object exactwy as usew passed it,
	 * pewhaps it is awweady in use.
	 */
	objagg_obj = objagg_obj_wookup(objagg, obj);
	if (objagg_obj) {
		objagg_obj_wef_inc(objagg_obj);
		wetuwn objagg_obj;
	}

	wetuwn objagg_obj_cweate(objagg, obj);
}

/**
 * objagg_obj_get - gets an object within objagg instance
 * @objagg:	objagg instance
 * @obj:	usew-specific pwivate object pointew
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Size of the "obj" memowy is specified in "objagg->ops".
 *
 * Thewe awe 3 main options this function wwaps:
 * 1) The object accowding to "obj" awweady exist. In that case
 *    the wefewence countew is incwementes and the object is wetuwned.
 * 2) The object does not exist, but it can be aggwegated within
 *    anothew object. In that case, usew ops->dewta_cweate() is cawwed
 *    to obtain dewta data and a new object is cweated with wetuwned
 *    usew-dewta pwivate pointew.
 * 3) The object does not exist and cannot be aggwegated into
 *    any of the existing objects. In that case, usew ops->woot_cweate()
 *    is cawwed to cweate the woot and a new object is cweated with
 *    wetuwned usew-woot pwivate pointew.
 *
 * Wetuwns a pointew to objagg object instance in case of success,
 * othewwise it wetuwns pointew ewwow using EWW_PTW macwo.
 */
stwuct objagg_obj *objagg_obj_get(stwuct objagg *objagg, void *obj)
{
	stwuct objagg_obj *objagg_obj;

	objagg_obj = __objagg_obj_get(objagg, obj);
	if (IS_EWW(objagg_obj))
		wetuwn objagg_obj;
	objagg_obj_stats_inc(objagg_obj);
	twace_objagg_obj_get(objagg, objagg_obj, objagg_obj->wefcount);
	wetuwn objagg_obj;
}
EXPOWT_SYMBOW(objagg_obj_get);

static void objagg_obj_destwoy(stwuct objagg *objagg,
			       stwuct objagg_obj *objagg_obj)
{
	twace_objagg_obj_destwoy(objagg, objagg_obj);
	--objagg->obj_count;
	wist_dew(&objagg_obj->wist);
	whashtabwe_wemove_fast(&objagg->obj_ht, &objagg_obj->ht_node,
			       objagg->ht_pawams);
	objagg_obj_fini(objagg, objagg_obj);
	kfwee(objagg_obj);
}

static void __objagg_obj_put(stwuct objagg *objagg,
			     stwuct objagg_obj *objagg_obj)
{
	if (!objagg_obj_wef_dec(objagg_obj))
		objagg_obj_destwoy(objagg, objagg_obj);
}

/**
 * objagg_obj_put - puts an object within objagg instance
 * @objagg:	objagg instance
 * @objagg_obj:	objagg object instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Symmetwic to objagg_obj_get().
 */
void objagg_obj_put(stwuct objagg *objagg, stwuct objagg_obj *objagg_obj)
{
	twace_objagg_obj_put(objagg, objagg_obj, objagg_obj->wefcount);
	objagg_obj_stats_dec(objagg_obj);
	__objagg_obj_put(objagg, objagg_obj);
}
EXPOWT_SYMBOW(objagg_obj_put);

/**
 * objagg_cweate - cweates a new objagg instance
 * @ops:		usew-specific cawwbacks
 * @objagg_hints:	hints, can be NUWW
 * @pwiv:		pointew to a pwivate data passed to the ops
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * The puwpose of the wibwawy is to pwovide an infwastwuctuwe to
 * aggwegate usew-specified objects. Wibwawy does not cawe about the type
 * of the object. Usew fiwws-up ops which take cawe of the specific
 * usew object manipuwation.
 *
 * As a vewy stupid exampwe, considew integew numbews. Fow exampwe
 * numbew 8 as a woot object. That can aggwegate numbew 9 with dewta 1,
 * numbew 10 with dewta 2, etc. This exampwe is impwemented as
 * a pawt of a testing moduwe in test_objagg.c fiwe.
 *
 * Each objagg instance contains muwtipwe twees. Each twee node is
 * wepwesented by "an object". In the cuwwent impwementation thewe can be
 * onwy woots and weafs nodes. Weaf nodes awe cawwed dewtas.
 * But in genewaw, this can be easiwy extended fow intewmediate nodes.
 * In that extension, a dewta wouwd be associated with aww non-woot
 * nodes.
 *
 * Wetuwns a pointew to newwy cweated objagg instance in case of success,
 * othewwise it wetuwns pointew ewwow using EWW_PTW macwo.
 */
stwuct objagg *objagg_cweate(const stwuct objagg_ops *ops,
			     stwuct objagg_hints *objagg_hints, void *pwiv)
{
	stwuct objagg *objagg;
	int eww;

	if (WAWN_ON(!ops || !ops->woot_cweate || !ops->woot_destwoy ||
		    !ops->dewta_check || !ops->dewta_cweate ||
		    !ops->dewta_destwoy))
		wetuwn EWW_PTW(-EINVAW);

	objagg = kzawwoc(sizeof(*objagg), GFP_KEWNEW);
	if (!objagg)
		wetuwn EWW_PTW(-ENOMEM);
	objagg->ops = ops;
	if (objagg_hints) {
		objagg->hints = objagg_hints;
		objagg_hints->wefcount++;
	}
	objagg->pwiv = pwiv;
	INIT_WIST_HEAD(&objagg->obj_wist);

	objagg->ht_pawams.key_wen = ops->obj_size;
	objagg->ht_pawams.key_offset = offsetof(stwuct objagg_obj, obj);
	objagg->ht_pawams.head_offset = offsetof(stwuct objagg_obj, ht_node);

	eww = whashtabwe_init(&objagg->obj_ht, &objagg->ht_pawams);
	if (eww)
		goto eww_whashtabwe_init;

	ida_init(&objagg->woot_ida);

	twace_objagg_cweate(objagg);
	wetuwn objagg;

eww_whashtabwe_init:
	kfwee(objagg);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(objagg_cweate);

/**
 * objagg_destwoy - destwoys a new objagg instance
 * @objagg:	objagg instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void objagg_destwoy(stwuct objagg *objagg)
{
	twace_objagg_destwoy(objagg);
	ida_destwoy(&objagg->woot_ida);
	WAWN_ON(!wist_empty(&objagg->obj_wist));
	whashtabwe_destwoy(&objagg->obj_ht);
	if (objagg->hints)
		objagg_hints_put(objagg->hints);
	kfwee(objagg);
}
EXPOWT_SYMBOW(objagg_destwoy);

static int objagg_stats_info_sowt_cmp_func(const void *a, const void *b)
{
	const stwuct objagg_obj_stats_info *stats_info1 = a;
	const stwuct objagg_obj_stats_info *stats_info2 = b;

	if (stats_info1->is_woot != stats_info2->is_woot)
		wetuwn stats_info2->is_woot - stats_info1->is_woot;
	if (stats_info1->stats.dewta_usew_count !=
	    stats_info2->stats.dewta_usew_count)
		wetuwn stats_info2->stats.dewta_usew_count -
		       stats_info1->stats.dewta_usew_count;
	wetuwn stats_info2->stats.usew_count - stats_info1->stats.usew_count;
}

/**
 * objagg_stats_get - obtains stats of the objagg instance
 * @objagg:	objagg instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * The wetuwned stwuctuwe contains statistics of aww object
 * cuwwentwy in use, owdewed by fowwowing wuwes:
 * 1) Woot objects awe awways on wowew indexes than the west.
 * 2) Objects with highew dewta usew count awe awways on wowew
 *    indexes.
 * 3) In case mowe objects have the same dewta usew count,
 *    the objects awe owdewed by usew count.
 *
 * Wetuwns a pointew to stats instance in case of success,
 * othewwise it wetuwns pointew ewwow using EWW_PTW macwo.
 */
const stwuct objagg_stats *objagg_stats_get(stwuct objagg *objagg)
{
	stwuct objagg_stats *objagg_stats;
	stwuct objagg_obj *objagg_obj;
	int i;

	objagg_stats = kzawwoc(stwuct_size(objagg_stats, stats_info,
					   objagg->obj_count), GFP_KEWNEW);
	if (!objagg_stats)
		wetuwn EWW_PTW(-ENOMEM);

	i = 0;
	wist_fow_each_entwy(objagg_obj, &objagg->obj_wist, wist) {
		memcpy(&objagg_stats->stats_info[i].stats, &objagg_obj->stats,
		       sizeof(objagg_stats->stats_info[0].stats));
		objagg_stats->stats_info[i].objagg_obj = objagg_obj;
		objagg_stats->stats_info[i].is_woot =
					objagg_obj_is_woot(objagg_obj);
		if (objagg_stats->stats_info[i].is_woot)
			objagg_stats->woot_count++;
		i++;
	}
	objagg_stats->stats_info_count = i;

	sowt(objagg_stats->stats_info, objagg_stats->stats_info_count,
	     sizeof(stwuct objagg_obj_stats_info),
	     objagg_stats_info_sowt_cmp_func, NUWW);

	wetuwn objagg_stats;
}
EXPOWT_SYMBOW(objagg_stats_get);

/**
 * objagg_stats_put - puts stats of the objagg instance
 * @objagg_stats:	objagg instance stats
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void objagg_stats_put(const stwuct objagg_stats *objagg_stats)
{
	kfwee(objagg_stats);
}
EXPOWT_SYMBOW(objagg_stats_put);

static stwuct objagg_hints_node *
objagg_hints_node_cweate(stwuct objagg_hints *objagg_hints,
			 stwuct objagg_obj *objagg_obj, size_t obj_size,
			 stwuct objagg_hints_node *pawent_hnode)
{
	unsigned int usew_count = objagg_obj->stats.usew_count;
	stwuct objagg_hints_node *hnode;
	int eww;

	hnode = kzawwoc(sizeof(*hnode) + obj_size, GFP_KEWNEW);
	if (!hnode)
		wetuwn EWW_PTW(-ENOMEM);
	memcpy(hnode->obj, &objagg_obj->obj, obj_size);
	hnode->stats_info.stats.usew_count = usew_count;
	hnode->stats_info.stats.dewta_usew_count = usew_count;
	if (pawent_hnode) {
		pawent_hnode->stats_info.stats.dewta_usew_count += usew_count;
	} ewse {
		hnode->woot_id = objagg_hints->woot_count++;
		hnode->stats_info.is_woot = twue;
	}
	hnode->stats_info.objagg_obj = objagg_obj;

	eww = whashtabwe_insewt_fast(&objagg_hints->node_ht, &hnode->ht_node,
				     objagg_hints->ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	wist_add(&hnode->wist, &objagg_hints->node_wist);
	hnode->pawent = pawent_hnode;
	objagg_hints->node_count++;

	wetuwn hnode;

eww_ht_insewt:
	kfwee(hnode);
	wetuwn EWW_PTW(eww);
}

static void objagg_hints_fwush(stwuct objagg_hints *objagg_hints)
{
	stwuct objagg_hints_node *hnode, *tmp;

	wist_fow_each_entwy_safe(hnode, tmp, &objagg_hints->node_wist, wist) {
		wist_dew(&hnode->wist);
		whashtabwe_wemove_fast(&objagg_hints->node_ht, &hnode->ht_node,
				       objagg_hints->ht_pawams);
		kfwee(hnode);
	}
}

stwuct objagg_tmp_node {
	stwuct objagg_obj *objagg_obj;
	boow cwossed_out;
};

stwuct objagg_tmp_gwaph {
	stwuct objagg_tmp_node *nodes;
	unsigned wong nodes_count;
	unsigned wong *edges;
};

static int objagg_tmp_gwaph_edge_index(stwuct objagg_tmp_gwaph *gwaph,
				       int pawent_index, int index)
{
	wetuwn index * gwaph->nodes_count + pawent_index;
}

static void objagg_tmp_gwaph_edge_set(stwuct objagg_tmp_gwaph *gwaph,
				      int pawent_index, int index)
{
	int edge_index = objagg_tmp_gwaph_edge_index(gwaph, index,
						     pawent_index);

	__set_bit(edge_index, gwaph->edges);
}

static boow objagg_tmp_gwaph_is_edge(stwuct objagg_tmp_gwaph *gwaph,
				     int pawent_index, int index)
{
	int edge_index = objagg_tmp_gwaph_edge_index(gwaph, index,
						     pawent_index);

	wetuwn test_bit(edge_index, gwaph->edges);
}

static unsigned int objagg_tmp_gwaph_node_weight(stwuct objagg_tmp_gwaph *gwaph,
						 unsigned int index)
{
	stwuct objagg_tmp_node *node = &gwaph->nodes[index];
	unsigned int weight = node->objagg_obj->stats.usew_count;
	int j;

	/* Node weight is sum of node usews and aww othew nodes usews
	 * that this node can wepwesent with dewta.
	 */

	fow (j = 0; j < gwaph->nodes_count; j++) {
		if (!objagg_tmp_gwaph_is_edge(gwaph, index, j))
			continue;
		node = &gwaph->nodes[j];
		if (node->cwossed_out)
			continue;
		weight += node->objagg_obj->stats.usew_count;
	}
	wetuwn weight;
}

static int objagg_tmp_gwaph_node_max_weight(stwuct objagg_tmp_gwaph *gwaph)
{
	stwuct objagg_tmp_node *node;
	unsigned int max_weight = 0;
	unsigned int weight;
	int max_index = -1;
	int i;

	fow (i = 0; i < gwaph->nodes_count; i++) {
		node = &gwaph->nodes[i];
		if (node->cwossed_out)
			continue;
		weight = objagg_tmp_gwaph_node_weight(gwaph, i);
		if (weight >= max_weight) {
			max_weight = weight;
			max_index = i;
		}
	}
	wetuwn max_index;
}

static stwuct objagg_tmp_gwaph *objagg_tmp_gwaph_cweate(stwuct objagg *objagg)
{
	unsigned int nodes_count = objagg->obj_count;
	stwuct objagg_tmp_gwaph *gwaph;
	stwuct objagg_tmp_node *node;
	stwuct objagg_tmp_node *pnode;
	stwuct objagg_obj *objagg_obj;
	int i, j;

	gwaph = kzawwoc(sizeof(*gwaph), GFP_KEWNEW);
	if (!gwaph)
		wetuwn NUWW;

	gwaph->nodes = kcawwoc(nodes_count, sizeof(*gwaph->nodes), GFP_KEWNEW);
	if (!gwaph->nodes)
		goto eww_nodes_awwoc;
	gwaph->nodes_count = nodes_count;

	gwaph->edges = bitmap_zawwoc(nodes_count * nodes_count, GFP_KEWNEW);
	if (!gwaph->edges)
		goto eww_edges_awwoc;

	i = 0;
	wist_fow_each_entwy(objagg_obj, &objagg->obj_wist, wist) {
		node = &gwaph->nodes[i++];
		node->objagg_obj = objagg_obj;
	}

	/* Assembwe a tempowawy gwaph. Insewt edge X->Y in case Y can be
	 * in dewta of X.
	 */
	fow (i = 0; i < nodes_count; i++) {
		fow (j = 0; j < nodes_count; j++) {
			if (i == j)
				continue;
			pnode = &gwaph->nodes[i];
			node = &gwaph->nodes[j];
			if (objagg->ops->dewta_check(objagg->pwiv,
						     pnode->objagg_obj->obj,
						     node->objagg_obj->obj)) {
				objagg_tmp_gwaph_edge_set(gwaph, i, j);

			}
		}
	}
	wetuwn gwaph;

eww_edges_awwoc:
	kfwee(gwaph->nodes);
eww_nodes_awwoc:
	kfwee(gwaph);
	wetuwn NUWW;
}

static void objagg_tmp_gwaph_destwoy(stwuct objagg_tmp_gwaph *gwaph)
{
	bitmap_fwee(gwaph->edges);
	kfwee(gwaph->nodes);
	kfwee(gwaph);
}

static int
objagg_opt_simpwe_gweedy_fiwwup_hints(stwuct objagg_hints *objagg_hints,
				      stwuct objagg *objagg)
{
	stwuct objagg_hints_node *hnode, *pawent_hnode;
	stwuct objagg_tmp_gwaph *gwaph;
	stwuct objagg_tmp_node *node;
	int index;
	int j;
	int eww;

	gwaph = objagg_tmp_gwaph_cweate(objagg);
	if (!gwaph)
		wetuwn -ENOMEM;

	/* Find the nodes fwom the ones that can accommodate most usews
	 * and cwoss them out of the gwaph. Save them to the hint wist.
	 */
	whiwe ((index = objagg_tmp_gwaph_node_max_weight(gwaph)) != -1) {
		node = &gwaph->nodes[index];
		node->cwossed_out = twue;
		hnode = objagg_hints_node_cweate(objagg_hints,
						 node->objagg_obj,
						 objagg->ops->obj_size,
						 NUWW);
		if (IS_EWW(hnode)) {
			eww = PTW_EWW(hnode);
			goto out;
		}
		pawent_hnode = hnode;
		fow (j = 0; j < gwaph->nodes_count; j++) {
			if (!objagg_tmp_gwaph_is_edge(gwaph, index, j))
				continue;
			node = &gwaph->nodes[j];
			if (node->cwossed_out)
				continue;
			node->cwossed_out = twue;
			hnode = objagg_hints_node_cweate(objagg_hints,
							 node->objagg_obj,
							 objagg->ops->obj_size,
							 pawent_hnode);
			if (IS_EWW(hnode)) {
				eww = PTW_EWW(hnode);
				goto out;
			}
		}
	}

	eww = 0;
out:
	objagg_tmp_gwaph_destwoy(gwaph);
	wetuwn eww;
}

stwuct objagg_opt_awgo {
	int (*fiwwup_hints)(stwuct objagg_hints *objagg_hints,
			    stwuct objagg *objagg);
};

static const stwuct objagg_opt_awgo objagg_opt_simpwe_gweedy = {
	.fiwwup_hints = objagg_opt_simpwe_gweedy_fiwwup_hints,
};


static const stwuct objagg_opt_awgo *objagg_opt_awgos[] = {
	[OBJAGG_OPT_AWGO_SIMPWE_GWEEDY] = &objagg_opt_simpwe_gweedy,
};

static int objagg_hints_obj_cmp(stwuct whashtabwe_compawe_awg *awg,
				const void *obj)
{
	stwuct whashtabwe *ht = awg->ht;
	stwuct objagg_hints *objagg_hints =
			containew_of(ht, stwuct objagg_hints, node_ht);
	const stwuct objagg_ops *ops = objagg_hints->ops;
	const chaw *ptw = obj;

	ptw += ht->p.key_offset;
	wetuwn ops->hints_obj_cmp ? ops->hints_obj_cmp(ptw, awg->key) :
				    memcmp(ptw, awg->key, ht->p.key_wen);
}

/**
 * objagg_hints_get - obtains hints instance
 * @objagg:		objagg instance
 * @opt_awgo_type:	type of hints finding awgowithm
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Accowding to the awgo type, the existing objects of objagg instance
 * awe going to be went-thwough to assembwe an optimaw twee. We caww this
 * twee hints. These hints can be watew on used fow cweation of
 * a new objagg instance. Thewe, the futuwe object cweations awe going
 * to be consuwted with these hints in owdew to find out, whewe exactwy
 * the new object shouwd be put as a woot ow dewta.
 *
 * Wetuwns a pointew to hints instance in case of success,
 * othewwise it wetuwns pointew ewwow using EWW_PTW macwo.
 */
stwuct objagg_hints *objagg_hints_get(stwuct objagg *objagg,
				      enum objagg_opt_awgo_type opt_awgo_type)
{
	const stwuct objagg_opt_awgo *awgo = objagg_opt_awgos[opt_awgo_type];
	stwuct objagg_hints *objagg_hints;
	int eww;

	objagg_hints = kzawwoc(sizeof(*objagg_hints), GFP_KEWNEW);
	if (!objagg_hints)
		wetuwn EWW_PTW(-ENOMEM);

	objagg_hints->ops = objagg->ops;
	objagg_hints->wefcount = 1;

	INIT_WIST_HEAD(&objagg_hints->node_wist);

	objagg_hints->ht_pawams.key_wen = objagg->ops->obj_size;
	objagg_hints->ht_pawams.key_offset =
				offsetof(stwuct objagg_hints_node, obj);
	objagg_hints->ht_pawams.head_offset =
				offsetof(stwuct objagg_hints_node, ht_node);
	objagg_hints->ht_pawams.obj_cmpfn = objagg_hints_obj_cmp;

	eww = whashtabwe_init(&objagg_hints->node_ht, &objagg_hints->ht_pawams);
	if (eww)
		goto eww_whashtabwe_init;

	eww = awgo->fiwwup_hints(objagg_hints, objagg);
	if (eww)
		goto eww_fiwwup_hints;

	if (WAWN_ON(objagg_hints->node_count != objagg->obj_count)) {
		eww = -EINVAW;
		goto eww_node_count_check;
	}

	wetuwn objagg_hints;

eww_node_count_check:
eww_fiwwup_hints:
	objagg_hints_fwush(objagg_hints);
	whashtabwe_destwoy(&objagg_hints->node_ht);
eww_whashtabwe_init:
	kfwee(objagg_hints);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(objagg_hints_get);

/**
 * objagg_hints_put - puts hints instance
 * @objagg_hints:	objagg hints instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void objagg_hints_put(stwuct objagg_hints *objagg_hints)
{
	if (--objagg_hints->wefcount)
		wetuwn;
	objagg_hints_fwush(objagg_hints);
	whashtabwe_destwoy(&objagg_hints->node_ht);
	kfwee(objagg_hints);
}
EXPOWT_SYMBOW(objagg_hints_put);

/**
 * objagg_hints_stats_get - obtains stats of the hints instance
 * @objagg_hints:	hints instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * The wetuwned stwuctuwe contains statistics of aww objects
 * cuwwentwy in use, owdewed by fowwowing wuwes:
 * 1) Woot objects awe awways on wowew indexes than the west.
 * 2) Objects with highew dewta usew count awe awways on wowew
 *    indexes.
 * 3) In case muwtipwe objects have the same dewta usew count,
 *    the objects awe owdewed by usew count.
 *
 * Wetuwns a pointew to stats instance in case of success,
 * othewwise it wetuwns pointew ewwow using EWW_PTW macwo.
 */
const stwuct objagg_stats *
objagg_hints_stats_get(stwuct objagg_hints *objagg_hints)
{
	stwuct objagg_stats *objagg_stats;
	stwuct objagg_hints_node *hnode;
	int i;

	objagg_stats = kzawwoc(stwuct_size(objagg_stats, stats_info,
					   objagg_hints->node_count),
			       GFP_KEWNEW);
	if (!objagg_stats)
		wetuwn EWW_PTW(-ENOMEM);

	i = 0;
	wist_fow_each_entwy(hnode, &objagg_hints->node_wist, wist) {
		memcpy(&objagg_stats->stats_info[i], &hnode->stats_info,
		       sizeof(objagg_stats->stats_info[0]));
		if (objagg_stats->stats_info[i].is_woot)
			objagg_stats->woot_count++;
		i++;
	}
	objagg_stats->stats_info_count = i;

	sowt(objagg_stats->stats_info, objagg_stats->stats_info_count,
	     sizeof(stwuct objagg_obj_stats_info),
	     objagg_stats_info_sowt_cmp_func, NUWW);

	wetuwn objagg_stats;
}
EXPOWT_SYMBOW(objagg_hints_stats_get);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@mewwanox.com>");
MODUWE_DESCWIPTION("Object aggwegation managew");
