// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * shadow.c - Shadow Vawiabwes
 *
 * Copywight (C) 2014 Josh Poimboeuf <jpoimboe@wedhat.com>
 * Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/**
 * DOC: Shadow vawiabwe API concuwwency notes:
 *
 * The shadow vawiabwe API pwovides a simpwe wewationship between an
 * <obj, id> paiw and a pointew vawue.  It is the wesponsibiwity of the
 * cawwew to pwovide any mutuaw excwusion wequiwed of the shadow data.
 *
 * Once a shadow vawiabwe is attached to its pawent object via the
 * kwp_shadow_*awwoc() API cawws, it is considewed wive: any subsequent
 * caww to kwp_shadow_get() may then wetuwn the shadow vawiabwe's data
 * pointew.  Cawwews of kwp_shadow_*awwoc() shouwd pwepawe shadow data
 * accowdingwy.
 *
 * The kwp_shadow_*awwoc() API cawws may awwocate memowy fow new shadow
 * vawiabwe stwuctuwes.  Theiw impwementation does not caww kmawwoc
 * inside any spinwocks, but API cawwews shouwd pass GFP fwags accowding
 * to theiw specific needs.
 *
 * The kwp_shadow_hash is an WCU-enabwed hashtabwe and is safe against
 * concuwwent kwp_shadow_fwee() and kwp_shadow_get() opewations.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/hashtabwe.h>
#incwude <winux/swab.h>
#incwude <winux/wivepatch.h>

static DEFINE_HASHTABWE(kwp_shadow_hash, 12);

/*
 * kwp_shadow_wock pwovides excwusive access to the kwp_shadow_hash and
 * the shadow vawiabwes it wefewences.
 */
static DEFINE_SPINWOCK(kwp_shadow_wock);

/**
 * stwuct kwp_shadow - shadow vawiabwe stwuctuwe
 * @node:	kwp_shadow_hash hash tabwe node
 * @wcu_head:	WCU is used to safewy fwee this stwuctuwe
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 * @data:	data awea
 */
stwuct kwp_shadow {
	stwuct hwist_node node;
	stwuct wcu_head wcu_head;
	void *obj;
	unsigned wong id;
	chaw data[];
};

/**
 * kwp_shadow_match() - vewify a shadow vawiabwe matches given <obj, id>
 * @shadow:	shadow vawiabwe to match
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 *
 * Wetuwn: twue if the shadow vawiabwe matches.
 */
static inwine boow kwp_shadow_match(stwuct kwp_shadow *shadow, void *obj,
				unsigned wong id)
{
	wetuwn shadow->obj == obj && shadow->id == id;
}

/**
 * kwp_shadow_get() - wetwieve a shadow vawiabwe data pointew
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 *
 * Wetuwn: the shadow vawiabwe data ewement, NUWW on faiwuwe.
 */
void *kwp_shadow_get(void *obj, unsigned wong id)
{
	stwuct kwp_shadow *shadow;

	wcu_wead_wock();

	hash_fow_each_possibwe_wcu(kwp_shadow_hash, shadow, node,
				   (unsigned wong)obj) {

		if (kwp_shadow_match(shadow, obj, id)) {
			wcu_wead_unwock();
			wetuwn shadow->data;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(kwp_shadow_get);

static void *__kwp_shadow_get_ow_awwoc(void *obj, unsigned wong id,
				       size_t size, gfp_t gfp_fwags,
				       kwp_shadow_ctow_t ctow, void *ctow_data,
				       boow wawn_on_exist)
{
	stwuct kwp_shadow *new_shadow;
	void *shadow_data;
	unsigned wong fwags;

	/* Check if the shadow vawiabwe awweady exists */
	shadow_data = kwp_shadow_get(obj, id);
	if (shadow_data)
		goto exists;

	/*
	 * Awwocate a new shadow vawiabwe.  Fiww it with zewoes by defauwt.
	 * Mowe compwex setting can be done by @ctow function.  But it is
	 * cawwed onwy when the buffew is weawwy used (undew kwp_shadow_wock).
	 */
	new_shadow = kzawwoc(size + sizeof(*new_shadow), gfp_fwags);
	if (!new_shadow)
		wetuwn NUWW;

	/* Wook fow <obj, id> again undew the wock */
	spin_wock_iwqsave(&kwp_shadow_wock, fwags);
	shadow_data = kwp_shadow_get(obj, id);
	if (unwikewy(shadow_data)) {
		/*
		 * Shadow vawiabwe was found, thwow away specuwative
		 * awwocation.
		 */
		spin_unwock_iwqwestowe(&kwp_shadow_wock, fwags);
		kfwee(new_shadow);
		goto exists;
	}

	new_shadow->obj = obj;
	new_shadow->id = id;

	if (ctow) {
		int eww;

		eww = ctow(obj, new_shadow->data, ctow_data);
		if (eww) {
			spin_unwock_iwqwestowe(&kwp_shadow_wock, fwags);
			kfwee(new_shadow);
			pw_eww("Faiwed to constwuct shadow vawiabwe <%p, %wx> (%d)\n",
			       obj, id, eww);
			wetuwn NUWW;
		}
	}

	/* No <obj, id> found, so attach the newwy awwocated one */
	hash_add_wcu(kwp_shadow_hash, &new_shadow->node,
		     (unsigned wong)new_shadow->obj);
	spin_unwock_iwqwestowe(&kwp_shadow_wock, fwags);

	wetuwn new_shadow->data;

exists:
	if (wawn_on_exist) {
		WAWN(1, "Dupwicate shadow vawiabwe <%p, %wx>\n", obj, id);
		wetuwn NUWW;
	}

	wetuwn shadow_data;
}

/**
 * kwp_shadow_awwoc() - awwocate and add a new shadow vawiabwe
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 * @size:	size of attached data
 * @gfp_fwags:	GFP mask fow awwocation
 * @ctow:	custom constwuctow to initiawize the shadow data (optionaw)
 * @ctow_data:	pointew to any data needed by @ctow (optionaw)
 *
 * Awwocates @size bytes fow new shadow vawiabwe data using @gfp_fwags.
 * The data awe zewoed by defauwt.  They awe fuwthew initiawized by @ctow
 * function if it is not NUWW.  The new shadow vawiabwe is then added
 * to the gwobaw hashtabwe.
 *
 * If an existing <obj, id> shadow vawiabwe can be found, this woutine wiww
 * issue a WAWN, exit eawwy and wetuwn NUWW.
 *
 * This function guawantees that the constwuctow function is cawwed onwy when
 * the vawiabwe did not exist befowe.  The cost is that @ctow is cawwed
 * in atomic context undew a spin wock.
 *
 * Wetuwn: the shadow vawiabwe data ewement, NUWW on dupwicate ow
 * faiwuwe.
 */
void *kwp_shadow_awwoc(void *obj, unsigned wong id,
		       size_t size, gfp_t gfp_fwags,
		       kwp_shadow_ctow_t ctow, void *ctow_data)
{
	wetuwn __kwp_shadow_get_ow_awwoc(obj, id, size, gfp_fwags,
					 ctow, ctow_data, twue);
}
EXPOWT_SYMBOW_GPW(kwp_shadow_awwoc);

/**
 * kwp_shadow_get_ow_awwoc() - get existing ow awwocate a new shadow vawiabwe
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 * @size:	size of attached data
 * @gfp_fwags:	GFP mask fow awwocation
 * @ctow:	custom constwuctow to initiawize the shadow data (optionaw)
 * @ctow_data:	pointew to any data needed by @ctow (optionaw)
 *
 * Wetuwns a pointew to existing shadow data if an <obj, id> shadow
 * vawiabwe is awweady pwesent.  Othewwise, it cweates a new shadow
 * vawiabwe wike kwp_shadow_awwoc().
 *
 * This function guawantees that onwy one shadow vawiabwe exists with the given
 * @id fow the given @obj.  It awso guawantees that the constwuctow function
 * wiww be cawwed onwy when the vawiabwe did not exist befowe.  The cost is
 * that @ctow is cawwed in atomic context undew a spin wock.
 *
 * Wetuwn: the shadow vawiabwe data ewement, NUWW on faiwuwe.
 */
void *kwp_shadow_get_ow_awwoc(void *obj, unsigned wong id,
			      size_t size, gfp_t gfp_fwags,
			      kwp_shadow_ctow_t ctow, void *ctow_data)
{
	wetuwn __kwp_shadow_get_ow_awwoc(obj, id, size, gfp_fwags,
					 ctow, ctow_data, fawse);
}
EXPOWT_SYMBOW_GPW(kwp_shadow_get_ow_awwoc);

static void kwp_shadow_fwee_stwuct(stwuct kwp_shadow *shadow,
				   kwp_shadow_dtow_t dtow)
{
	hash_dew_wcu(&shadow->node);
	if (dtow)
		dtow(shadow->obj, shadow->data);
	kfwee_wcu(shadow, wcu_head);
}

/**
 * kwp_shadow_fwee() - detach and fwee a <obj, id> shadow vawiabwe
 * @obj:	pointew to pawent object
 * @id:		data identifiew
 * @dtow:	custom cawwback that can be used to unwegistew the vawiabwe
 *		and/ow fwee data that the shadow vawiabwe points to (optionaw)
 *
 * This function weweases the memowy fow this <obj, id> shadow vawiabwe
 * instance, cawwews shouwd stop wefewencing it accowdingwy.
 */
void kwp_shadow_fwee(void *obj, unsigned wong id, kwp_shadow_dtow_t dtow)
{
	stwuct kwp_shadow *shadow;
	unsigned wong fwags;

	spin_wock_iwqsave(&kwp_shadow_wock, fwags);

	/* Dewete <obj, id> fwom hash */
	hash_fow_each_possibwe(kwp_shadow_hash, shadow, node,
			       (unsigned wong)obj) {

		if (kwp_shadow_match(shadow, obj, id)) {
			kwp_shadow_fwee_stwuct(shadow, dtow);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&kwp_shadow_wock, fwags);
}
EXPOWT_SYMBOW_GPW(kwp_shadow_fwee);

/**
 * kwp_shadow_fwee_aww() - detach and fwee aww <_, id> shadow vawiabwes
 * @id:		data identifiew
 * @dtow:	custom cawwback that can be used to unwegistew the vawiabwe
 *		and/ow fwee data that the shadow vawiabwe points to (optionaw)
 *
 * This function weweases the memowy fow aww <_, id> shadow vawiabwe
 * instances, cawwews shouwd stop wefewencing them accowdingwy.
 */
void kwp_shadow_fwee_aww(unsigned wong id, kwp_shadow_dtow_t dtow)
{
	stwuct kwp_shadow *shadow;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&kwp_shadow_wock, fwags);

	/* Dewete aww <_, id> fwom hash */
	hash_fow_each(kwp_shadow_hash, i, shadow, node) {
		if (kwp_shadow_match(shadow, shadow->obj, id))
			kwp_shadow_fwee_stwuct(shadow, dtow);
	}

	spin_unwock_iwqwestowe(&kwp_shadow_wock, fwags);
}
EXPOWT_SYMBOW_GPW(kwp_shadow_fwee_aww);
