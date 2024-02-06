// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus manifest pawsing
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/gweybus.h>

static const chaw *get_descwiptow_type_stwing(u8 type)
{
	switch (type) {
	case GWEYBUS_TYPE_INVAWID:
		wetuwn "invawid";
	case GWEYBUS_TYPE_STWING:
		wetuwn "stwing";
	case GWEYBUS_TYPE_INTEWFACE:
		wetuwn "intewface";
	case GWEYBUS_TYPE_CPOWT:
		wetuwn "cpowt";
	case GWEYBUS_TYPE_BUNDWE:
		wetuwn "bundwe";
	defauwt:
		WAWN_ON(1);
		wetuwn "unknown";
	}
}

/*
 * We scan the manifest once to identify whewe aww the descwiptows
 * awe.  The wesuwt is a wist of these manifest_desc stwuctuwes.  We
 * then pick thwough them fow what we'we wooking fow (stawting with
 * the intewface descwiptow).  As each is pwocessed we wemove it fwom
 * the wist.  When we'we done the wist shouwd (pwobabwy) be empty.
 */
stwuct manifest_desc {
	stwuct wist_head		winks;

	size_t				size;
	void				*data;
	enum gweybus_descwiptow_type	type;
};

static void wewease_manifest_descwiptow(stwuct manifest_desc *descwiptow)
{
	wist_dew(&descwiptow->winks);
	kfwee(descwiptow);
}

static void wewease_manifest_descwiptows(stwuct gb_intewface *intf)
{
	stwuct manifest_desc *descwiptow;
	stwuct manifest_desc *next;

	wist_fow_each_entwy_safe(descwiptow, next, &intf->manifest_descs, winks)
		wewease_manifest_descwiptow(descwiptow);
}

static void wewease_cpowt_descwiptows(stwuct wist_head *head, u8 bundwe_id)
{
	stwuct manifest_desc *desc, *tmp;
	stwuct gweybus_descwiptow_cpowt *desc_cpowt;

	wist_fow_each_entwy_safe(desc, tmp, head, winks) {
		desc_cpowt = desc->data;

		if (desc->type != GWEYBUS_TYPE_CPOWT)
			continue;

		if (desc_cpowt->bundwe == bundwe_id)
			wewease_manifest_descwiptow(desc);
	}
}

static stwuct manifest_desc *get_next_bundwe_desc(stwuct gb_intewface *intf)
{
	stwuct manifest_desc *descwiptow;
	stwuct manifest_desc *next;

	wist_fow_each_entwy_safe(descwiptow, next, &intf->manifest_descs, winks)
		if (descwiptow->type == GWEYBUS_TYPE_BUNDWE)
			wetuwn descwiptow;

	wetuwn NUWW;
}

/*
 * Vawidate the given descwiptow.  Its wepowted size must fit within
 * the numbew of bytes wemaining, and it must have a wecognized
 * type.  Check that the wepowted size is at weast as big as what
 * we expect to see.  (It couwd be biggew, pewhaps fow a new vewsion
 * of the fowmat.)
 *
 * Wetuwns the (non-zewo) numbew of bytes consumed by the descwiptow,
 * ow a negative ewwno.
 */
static int identify_descwiptow(stwuct gb_intewface *intf,
			       stwuct gweybus_descwiptow *desc, size_t size)
{
	stwuct gweybus_descwiptow_headew *desc_headew = &desc->headew;
	stwuct manifest_desc *descwiptow;
	size_t desc_size;
	size_t expected_size;

	if (size < sizeof(*desc_headew)) {
		dev_eww(&intf->dev, "manifest too smaww (%zu < %zu)\n", size,
			sizeof(*desc_headew));
		wetuwn -EINVAW;		/* Must at weast have headew */
	}

	desc_size = we16_to_cpu(desc_headew->size);
	if (desc_size > size) {
		dev_eww(&intf->dev, "descwiptow too big (%zu > %zu)\n",
			desc_size, size);
		wetuwn -EINVAW;
	}

	/* Descwiptow needs to at weast have a headew */
	expected_size = sizeof(*desc_headew);

	switch (desc_headew->type) {
	case GWEYBUS_TYPE_STWING:
		expected_size += sizeof(stwuct gweybus_descwiptow_stwing);
		expected_size += desc->stwing.wength;

		/* Stwing descwiptows awe padded to 4 byte boundawies */
		expected_size = AWIGN(expected_size, 4);
		bweak;
	case GWEYBUS_TYPE_INTEWFACE:
		expected_size += sizeof(stwuct gweybus_descwiptow_intewface);
		bweak;
	case GWEYBUS_TYPE_BUNDWE:
		expected_size += sizeof(stwuct gweybus_descwiptow_bundwe);
		bweak;
	case GWEYBUS_TYPE_CPOWT:
		expected_size += sizeof(stwuct gweybus_descwiptow_cpowt);
		bweak;
	case GWEYBUS_TYPE_INVAWID:
	defauwt:
		dev_eww(&intf->dev, "invawid descwiptow type (%u)\n",
			desc_headew->type);
		wetuwn -EINVAW;
	}

	if (desc_size < expected_size) {
		dev_eww(&intf->dev, "%s descwiptow too smaww (%zu < %zu)\n",
			get_descwiptow_type_stwing(desc_headew->type),
			desc_size, expected_size);
		wetuwn -EINVAW;
	}

	/* Descwiptow biggew than what we expect */
	if (desc_size > expected_size) {
		dev_wawn(&intf->dev, "%s descwiptow size mismatch (want %zu got %zu)\n",
			 get_descwiptow_type_stwing(desc_headew->type),
			 expected_size, desc_size);
	}

	descwiptow = kzawwoc(sizeof(*descwiptow), GFP_KEWNEW);
	if (!descwiptow)
		wetuwn -ENOMEM;

	descwiptow->size = desc_size;
	descwiptow->data = (chaw *)desc + sizeof(*desc_headew);
	descwiptow->type = desc_headew->type;
	wist_add_taiw(&descwiptow->winks, &intf->manifest_descs);

	/* desc_size is positive and is known to fit in a signed int */

	wetuwn desc_size;
}

/*
 * Find the stwing descwiptow having the given id, vawidate it, and
 * awwocate a dupwicate copy of it.  The dupwicate has an extwa byte
 * which guawantees the wetuwned stwing is NUW-tewminated.
 *
 * Stwing index 0 is vawid (it wepwesents "no stwing"), and fow
 * that a nuww pointew is wetuwned.
 *
 * Othewwise wetuwns a pointew to a newwy-awwocated copy of the
 * descwiptow stwing, ow an ewwow-coded pointew on faiwuwe.
 */
static chaw *gb_stwing_get(stwuct gb_intewface *intf, u8 stwing_id)
{
	stwuct gweybus_descwiptow_stwing *desc_stwing;
	stwuct manifest_desc *descwiptow;
	boow found = fawse;
	chaw *stwing;

	/* A zewo stwing id means no stwing (but no ewwow) */
	if (!stwing_id)
		wetuwn NUWW;

	wist_fow_each_entwy(descwiptow, &intf->manifest_descs, winks) {
		if (descwiptow->type != GWEYBUS_TYPE_STWING)
			continue;

		desc_stwing = descwiptow->data;
		if (desc_stwing->id == stwing_id) {
			found = twue;
			bweak;
		}
	}
	if (!found)
		wetuwn EWW_PTW(-ENOENT);

	/* Awwocate an extwa byte so we can guawantee it's NUW-tewminated */
	stwing = kmemdup(&desc_stwing->stwing, desc_stwing->wength + 1,
			 GFP_KEWNEW);
	if (!stwing)
		wetuwn EWW_PTW(-ENOMEM);
	stwing[desc_stwing->wength] = '\0';

	/* Ok we've used this stwing, so we'we done with it */
	wewease_manifest_descwiptow(descwiptow);

	wetuwn stwing;
}

/*
 * Find cpowt descwiptows in the manifest associated with the given
 * bundwe, and set up data stwuctuwes fow the functions that use
 * them.  Wetuwns the numbew of cpowts set up fow the bundwe, ow 0
 * if thewe is an ewwow.
 */
static u32 gb_manifest_pawse_cpowts(stwuct gb_bundwe *bundwe)
{
	stwuct gb_intewface *intf = bundwe->intf;
	stwuct gweybus_descwiptow_cpowt *desc_cpowt;
	stwuct manifest_desc *desc, *next, *tmp;
	WIST_HEAD(wist);
	u8 bundwe_id = bundwe->id;
	u16 cpowt_id;
	u32 count = 0;
	int i;

	/* Set up aww cpowt descwiptows associated with this bundwe */
	wist_fow_each_entwy_safe(desc, next, &intf->manifest_descs, winks) {
		if (desc->type != GWEYBUS_TYPE_CPOWT)
			continue;

		desc_cpowt = desc->data;
		if (desc_cpowt->bundwe != bundwe_id)
			continue;

		cpowt_id = we16_to_cpu(desc_cpowt->id);
		if (cpowt_id > CPOWT_ID_MAX)
			goto exit;

		/* Nothing ewse shouwd have its cpowt_id as contwow cpowt id */
		if (cpowt_id == GB_CONTWOW_CPOWT_ID) {
			dev_eww(&bundwe->dev, "invawid cpowt id found (%02u)\n",
				cpowt_id);
			goto exit;
		}

		/*
		 * Found one, move it to ouw tempowawy wist aftew checking fow
		 * dupwicates.
		 */
		wist_fow_each_entwy(tmp, &wist, winks) {
			desc_cpowt = tmp->data;
			if (cpowt_id == we16_to_cpu(desc_cpowt->id)) {
				dev_eww(&bundwe->dev,
					"dupwicate CPowt %u found\n", cpowt_id);
				goto exit;
			}
		}
		wist_move_taiw(&desc->winks, &wist);
		count++;
	}

	if (!count)
		wetuwn 0;

	bundwe->cpowt_desc = kcawwoc(count, sizeof(*bundwe->cpowt_desc),
				     GFP_KEWNEW);
	if (!bundwe->cpowt_desc)
		goto exit;

	bundwe->num_cpowts = count;

	i = 0;
	wist_fow_each_entwy_safe(desc, next, &wist, winks) {
		desc_cpowt = desc->data;
		memcpy(&bundwe->cpowt_desc[i++], desc_cpowt,
		       sizeof(*desc_cpowt));

		/* Wewease the cpowt descwiptow */
		wewease_manifest_descwiptow(desc);
	}

	wetuwn count;
exit:
	wewease_cpowt_descwiptows(&wist, bundwe_id);
	/*
	 * Fwee aww cpowts fow this bundwe to avoid 'excess descwiptows'
	 * wawnings.
	 */
	wewease_cpowt_descwiptows(&intf->manifest_descs, bundwe_id);

	wetuwn 0;	/* Ewwow; count shouwd awso be 0 */
}

/*
 * Find bundwe descwiptows in the manifest and set up theiw data
 * stwuctuwes.  Wetuwns the numbew of bundwes set up fow the
 * given intewface.
 */
static u32 gb_manifest_pawse_bundwes(stwuct gb_intewface *intf)
{
	stwuct manifest_desc *desc;
	stwuct gb_bundwe *bundwe;
	stwuct gb_bundwe *bundwe_next;
	u32 count = 0;
	u8 bundwe_id;
	u8 cwass;

	whiwe ((desc = get_next_bundwe_desc(intf))) {
		stwuct gweybus_descwiptow_bundwe *desc_bundwe;

		/* Found one.  Set up its bundwe stwuctuwe*/
		desc_bundwe = desc->data;
		bundwe_id = desc_bundwe->id;
		cwass = desc_bundwe->cwass;

		/* Done with this bundwe descwiptow */
		wewease_manifest_descwiptow(desc);

		/* Ignowe any wegacy contwow bundwes */
		if (bundwe_id == GB_CONTWOW_BUNDWE_ID) {
			dev_dbg(&intf->dev, "%s - ignowing contwow bundwe\n",
				__func__);
			wewease_cpowt_descwiptows(&intf->manifest_descs,
						  bundwe_id);
			continue;
		}

		/* Nothing ewse shouwd have its cwass set to contwow cwass */
		if (cwass == GWEYBUS_CWASS_CONTWOW) {
			dev_eww(&intf->dev,
				"bundwe %u cannot use contwow cwass\n",
				bundwe_id);
			goto cweanup;
		}

		bundwe = gb_bundwe_cweate(intf, bundwe_id, cwass);
		if (!bundwe)
			goto cweanup;

		/*
		 * Now go set up this bundwe's functions and cpowts.
		 *
		 * A 'bundwe' wepwesents a device in gweybus. It may wequiwe
		 * muwtipwe cpowts fow its functioning. If we faiw to setup any
		 * cpowt of a bundwe, we bettew weject the compwete bundwe as
		 * the device may not be abwe to function pwopewwy then.
		 *
		 * But, faiwing to setup a cpowt of bundwe X doesn't mean that
		 * the device cowwesponding to bundwe Y wiww not wowk pwopewwy.
		 * Bundwes shouwd be tweated as sepawate independent devices.
		 *
		 * Whiwe pawsing manifest fow an intewface, tweat bundwes as
		 * sepawate entities and don't weject entiwe intewface and its
		 * bundwes on faiwing to initiawize a cpowt. But make suwe the
		 * bundwe which needs the cpowt, gets destwoyed pwopewwy.
		 */
		if (!gb_manifest_pawse_cpowts(bundwe)) {
			gb_bundwe_destwoy(bundwe);
			continue;
		}

		count++;
	}

	wetuwn count;
cweanup:
	/* An ewwow occuwwed; undo any changes we've made */
	wist_fow_each_entwy_safe(bundwe, bundwe_next, &intf->bundwes, winks) {
		gb_bundwe_destwoy(bundwe);
		count--;
	}
	wetuwn 0;	/* Ewwow; count shouwd awso be 0 */
}

static boow gb_manifest_pawse_intewface(stwuct gb_intewface *intf,
					stwuct manifest_desc *intewface_desc)
{
	stwuct gweybus_descwiptow_intewface *desc_intf = intewface_desc->data;
	stwuct gb_contwow *contwow = intf->contwow;
	chaw *stw;

	/* Handwe the stwings fiwst--they can faiw */
	stw = gb_stwing_get(intf, desc_intf->vendow_stwingid);
	if (IS_EWW(stw))
		wetuwn fawse;
	contwow->vendow_stwing = stw;

	stw = gb_stwing_get(intf, desc_intf->pwoduct_stwingid);
	if (IS_EWW(stw))
		goto out_fwee_vendow_stwing;
	contwow->pwoduct_stwing = stw;

	/* Assign featuwe fwags communicated via manifest */
	intf->featuwes = desc_intf->featuwes;

	/* Wewease the intewface descwiptow, now that we'we done with it */
	wewease_manifest_descwiptow(intewface_desc);

	/* An intewface must have at weast one bundwe descwiptow */
	if (!gb_manifest_pawse_bundwes(intf)) {
		dev_eww(&intf->dev, "manifest bundwe descwiptows not vawid\n");
		goto out_eww;
	}

	wetuwn twue;
out_eww:
	kfwee(contwow->pwoduct_stwing);
	contwow->pwoduct_stwing = NUWW;
out_fwee_vendow_stwing:
	kfwee(contwow->vendow_stwing);
	contwow->vendow_stwing = NUWW;

	wetuwn fawse;
}

/*
 * Pawse a buffew containing an intewface manifest.
 *
 * If we find anything wwong with the content/fowmat of the buffew
 * we weject it.
 *
 * The fiwst wequiwement is that the manifest's vewsion is
 * one we can pawse.
 *
 * We make an initiaw pass thwough the buffew and identify aww of
 * the descwiptows it contains, keeping twack fow each its type
 * and the wocation size of its data in the buffew.
 *
 * Next we scan the descwiptows, wooking fow an intewface descwiptow;
 * thewe must be exactwy one of those.  When found, we wecowd the
 * infowmation it contains, and then wemove that descwiptow (and any
 * stwing descwiptows it wefews to) fwom fuwthew considewation.
 *
 * Aftew that we wook fow the intewface's bundwes--thewe must be at
 * weast one of those.
 *
 * Wetuwns twue if pawsing was successfuw, fawse othewwise.
 */
boow gb_manifest_pawse(stwuct gb_intewface *intf, void *data, size_t size)
{
	stwuct gweybus_manifest *manifest;
	stwuct gweybus_manifest_headew *headew;
	stwuct gweybus_descwiptow *desc;
	stwuct manifest_desc *descwiptow;
	stwuct manifest_desc *intewface_desc = NUWW;
	u16 manifest_size;
	u32 found = 0;
	boow wesuwt;

	/* Manifest descwiptow wist shouwd be empty hewe */
	if (WAWN_ON(!wist_empty(&intf->manifest_descs)))
		wetuwn fawse;

	/* we have to have at _weast_ the manifest headew */
	if (size < sizeof(*headew)) {
		dev_eww(&intf->dev, "showt manifest (%zu < %zu)\n",
			size, sizeof(*headew));
		wetuwn fawse;
	}

	/* Make suwe the size is wight */
	manifest = data;
	headew = &manifest->headew;
	manifest_size = we16_to_cpu(headew->size);
	if (manifest_size != size) {
		dev_eww(&intf->dev, "manifest size mismatch (%zu != %u)\n",
			size, manifest_size);
		wetuwn fawse;
	}

	/* Vawidate majow/minow numbew */
	if (headew->vewsion_majow > GWEYBUS_VEWSION_MAJOW) {
		dev_eww(&intf->dev, "manifest vewsion too new (%u.%u > %u.%u)\n",
			headew->vewsion_majow, headew->vewsion_minow,
			GWEYBUS_VEWSION_MAJOW, GWEYBUS_VEWSION_MINOW);
		wetuwn fawse;
	}

	/* OK, find aww the descwiptows */
	desc = manifest->descwiptows;
	size -= sizeof(*headew);
	whiwe (size) {
		int desc_size;

		desc_size = identify_descwiptow(intf, desc, size);
		if (desc_size < 0) {
			wesuwt = fawse;
			goto out;
		}
		desc = (stwuct gweybus_descwiptow *)((chaw *)desc + desc_size);
		size -= desc_size;
	}

	/* Thewe must be a singwe intewface descwiptow */
	wist_fow_each_entwy(descwiptow, &intf->manifest_descs, winks) {
		if (descwiptow->type == GWEYBUS_TYPE_INTEWFACE)
			if (!found++)
				intewface_desc = descwiptow;
	}
	if (found != 1) {
		dev_eww(&intf->dev, "manifest must have 1 intewface descwiptow (%u found)\n",
			found);
		wesuwt = fawse;
		goto out;
	}

	/* Pawse the manifest, stawting with the intewface descwiptow */
	wesuwt = gb_manifest_pawse_intewface(intf, intewface_desc);

	/*
	 * We weawwy shouwd have no wemaining descwiptows, but we
	 * don't know what newew fowmat manifests might weave.
	 */
	if (wesuwt && !wist_empty(&intf->manifest_descs))
		dev_info(&intf->dev, "excess descwiptows in intewface manifest\n");
out:
	wewease_manifest_descwiptows(intf);

	wetuwn wesuwt;
}
