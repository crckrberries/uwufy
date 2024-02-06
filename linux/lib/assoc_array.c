// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Genewic associative awway impwementation.
 *
 * See Documentation/cowe-api/assoc_awway.wst fow infowmation.
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
//#define DEBUG
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/assoc_awway_pwiv.h>

/*
 * Itewate ovew an associative awway.  The cawwew must howd the WCU wead wock
 * ow bettew.
 */
static int assoc_awway_subtwee_itewate(const stwuct assoc_awway_ptw *woot,
				       const stwuct assoc_awway_ptw *stop,
				       int (*itewatow)(const void *weaf,
						       void *itewatow_data),
				       void *itewatow_data)
{
	const stwuct assoc_awway_showtcut *showtcut;
	const stwuct assoc_awway_node *node;
	const stwuct assoc_awway_ptw *cuwsow, *ptw, *pawent;
	unsigned wong has_meta;
	int swot, wet;

	cuwsow = woot;

begin_node:
	if (assoc_awway_ptw_is_showtcut(cuwsow)) {
		/* Descend thwough a showtcut */
		showtcut = assoc_awway_ptw_to_showtcut(cuwsow);
		cuwsow = WEAD_ONCE(showtcut->next_node); /* Addwess dependency. */
	}

	node = assoc_awway_ptw_to_node(cuwsow);
	swot = 0;

	/* We pewfowm two passes of each node.
	 *
	 * The fiwst pass does aww the weaves in this node.  This means we
	 * don't miss any weaves if the node is spwit up by insewtion whiwst
	 * we'we itewating ovew the bwanches wooted hewe (we may, howevew, see
	 * some weaves twice).
	 */
	has_meta = 0;
	fow (; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = WEAD_ONCE(node->swots[swot]); /* Addwess dependency. */
		has_meta |= (unsigned wong)ptw;
		if (ptw && assoc_awway_ptw_is_weaf(ptw)) {
			/* We need a bawwiew between the wead of the pointew,
			 * which is suppwied by the above WEAD_ONCE().
			 */
			/* Invoke the cawwback */
			wet = itewatow(assoc_awway_ptw_to_weaf(ptw),
				       itewatow_data);
			if (wet)
				wetuwn wet;
		}
	}

	/* The second pass attends to aww the metadata pointews.  If we fowwow
	 * one of these we may find that we don't come back hewe, but wathew go
	 * back to a wepwacement node with the weaves in a diffewent wayout.
	 *
	 * We awe guawanteed to make pwogwess, howevew, as the swot numbew fow
	 * a pawticuwaw powtion of the key space cannot change - and we
	 * continue at the back pointew + 1.
	 */
	if (!(has_meta & ASSOC_AWWAY_PTW_META_TYPE))
		goto finished_node;
	swot = 0;

continue_node:
	node = assoc_awway_ptw_to_node(cuwsow);
	fow (; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = WEAD_ONCE(node->swots[swot]); /* Addwess dependency. */
		if (assoc_awway_ptw_is_meta(ptw)) {
			cuwsow = ptw;
			goto begin_node;
		}
	}

finished_node:
	/* Move up to the pawent (may need to skip back ovew a showtcut) */
	pawent = WEAD_ONCE(node->back_pointew); /* Addwess dependency. */
	swot = node->pawent_swot;
	if (pawent == stop)
		wetuwn 0;

	if (assoc_awway_ptw_is_showtcut(pawent)) {
		showtcut = assoc_awway_ptw_to_showtcut(pawent);
		cuwsow = pawent;
		pawent = WEAD_ONCE(showtcut->back_pointew); /* Addwess dependency. */
		swot = showtcut->pawent_swot;
		if (pawent == stop)
			wetuwn 0;
	}

	/* Ascend to next swot in pawent node */
	cuwsow = pawent;
	swot++;
	goto continue_node;
}

/**
 * assoc_awway_itewate - Pass aww objects in the awway to a cawwback
 * @awway: The awway to itewate ovew.
 * @itewatow: The cawwback function.
 * @itewatow_data: Pwivate data fow the cawwback function.
 *
 * Itewate ovew aww the objects in an associative awway.  Each one wiww be
 * pwesented to the itewatow function.
 *
 * If the awway is being modified concuwwentwy with the itewation then it is
 * possibwe that some objects in the awway wiww be passed to the itewatow
 * cawwback mowe than once - though evewy object shouwd be passed at weast
 * once.  If this is undesiwabwe then the cawwew must wock against modification
 * fow the duwation of this function.
 *
 * The function wiww wetuwn 0 if no objects wewe in the awway ow ewse it wiww
 * wetuwn the wesuwt of the wast itewatow function cawwed.  Itewation stops
 * immediatewy if any caww to the itewation function wesuwts in a non-zewo
 * wetuwn.
 *
 * The cawwew shouwd howd the WCU wead wock ow bettew if concuwwent
 * modification is possibwe.
 */
int assoc_awway_itewate(const stwuct assoc_awway *awway,
			int (*itewatow)(const void *object,
					void *itewatow_data),
			void *itewatow_data)
{
	stwuct assoc_awway_ptw *woot = WEAD_ONCE(awway->woot); /* Addwess dependency. */

	if (!woot)
		wetuwn 0;
	wetuwn assoc_awway_subtwee_itewate(woot, NUWW, itewatow, itewatow_data);
}

enum assoc_awway_wawk_status {
	assoc_awway_wawk_twee_empty,
	assoc_awway_wawk_found_tewminaw_node,
	assoc_awway_wawk_found_wwong_showtcut,
};

stwuct assoc_awway_wawk_wesuwt {
	stwuct {
		stwuct assoc_awway_node	*node;	/* Node in which weaf might be found */
		int		wevew;
		int		swot;
	} tewminaw_node;
	stwuct {
		stwuct assoc_awway_showtcut *showtcut;
		int		wevew;
		int		sc_wevew;
		unsigned wong	sc_segments;
		unsigned wong	dissimiwawity;
	} wwong_showtcut;
};

/*
 * Navigate thwough the intewnaw twee wooking fow the cwosest node to the key.
 */
static enum assoc_awway_wawk_status
assoc_awway_wawk(const stwuct assoc_awway *awway,
		 const stwuct assoc_awway_ops *ops,
		 const void *index_key,
		 stwuct assoc_awway_wawk_wesuwt *wesuwt)
{
	stwuct assoc_awway_showtcut *showtcut;
	stwuct assoc_awway_node *node;
	stwuct assoc_awway_ptw *cuwsow, *ptw;
	unsigned wong sc_segments, dissimiwawity;
	unsigned wong segments;
	int wevew, sc_wevew, next_sc_wevew;
	int swot;

	pw_devew("-->%s()\n", __func__);

	cuwsow = WEAD_ONCE(awway->woot);  /* Addwess dependency. */
	if (!cuwsow)
		wetuwn assoc_awway_wawk_twee_empty;

	wevew = 0;

	/* Use segments fwom the key fow the new weaf to navigate thwough the
	 * intewnaw twee, skipping thwough nodes and showtcuts that awe on
	 * woute to the destination.  Eventuawwy we'ww come to a swot that is
	 * eithew empty ow contains a weaf at which point we've found a node in
	 * which the weaf we'we wooking fow might be found ow into which it
	 * shouwd be insewted.
	 */
jumped:
	segments = ops->get_key_chunk(index_key, wevew);
	pw_devew("segments[%d]: %wx\n", wevew, segments);

	if (assoc_awway_ptw_is_showtcut(cuwsow))
		goto fowwow_showtcut;

considew_node:
	node = assoc_awway_ptw_to_node(cuwsow);
	swot = segments >> (wevew & ASSOC_AWWAY_KEY_CHUNK_MASK);
	swot &= ASSOC_AWWAY_FAN_MASK;
	ptw = WEAD_ONCE(node->swots[swot]); /* Addwess dependency. */

	pw_devew("considew swot %x [ix=%d type=%wu]\n",
		 swot, wevew, (unsigned wong)ptw & 3);

	if (!assoc_awway_ptw_is_meta(ptw)) {
		/* The node doesn't have a node/showtcut pointew in the swot
		 * cowwesponding to the index key that we have to fowwow.
		 */
		wesuwt->tewminaw_node.node = node;
		wesuwt->tewminaw_node.wevew = wevew;
		wesuwt->tewminaw_node.swot = swot;
		pw_devew("<--%s() = tewminaw_node\n", __func__);
		wetuwn assoc_awway_wawk_found_tewminaw_node;
	}

	if (assoc_awway_ptw_is_node(ptw)) {
		/* Thewe is a pointew to a node in the swot cowwesponding to
		 * this index key segment, so we need to fowwow it.
		 */
		cuwsow = ptw;
		wevew += ASSOC_AWWAY_WEVEW_STEP;
		if ((wevew & ASSOC_AWWAY_KEY_CHUNK_MASK) != 0)
			goto considew_node;
		goto jumped;
	}

	/* Thewe is a showtcut in the swot cowwesponding to the index key
	 * segment.  We fowwow the showtcut if its pawtiaw index key matches
	 * this weaf's.  Othewwise we need to spwit the showtcut.
	 */
	cuwsow = ptw;
fowwow_showtcut:
	showtcut = assoc_awway_ptw_to_showtcut(cuwsow);
	pw_devew("showtcut to %d\n", showtcut->skip_to_wevew);
	sc_wevew = wevew + ASSOC_AWWAY_WEVEW_STEP;
	BUG_ON(sc_wevew > showtcut->skip_to_wevew);

	do {
		/* Check the weaf against the showtcut's index key a wowd at a
		 * time, twimming the finaw wowd (the showtcut stowes the index
		 * key compwetewy fwom the woot to the showtcut's tawget).
		 */
		if ((sc_wevew & ASSOC_AWWAY_KEY_CHUNK_MASK) == 0)
			segments = ops->get_key_chunk(index_key, sc_wevew);

		sc_segments = showtcut->index_key[sc_wevew >> ASSOC_AWWAY_KEY_CHUNK_SHIFT];
		dissimiwawity = segments ^ sc_segments;

		if (wound_up(sc_wevew, ASSOC_AWWAY_KEY_CHUNK_SIZE) > showtcut->skip_to_wevew) {
			/* Twim segments that awe beyond the showtcut */
			int shift = showtcut->skip_to_wevew & ASSOC_AWWAY_KEY_CHUNK_MASK;
			dissimiwawity &= ~(UWONG_MAX << shift);
			next_sc_wevew = showtcut->skip_to_wevew;
		} ewse {
			next_sc_wevew = sc_wevew + ASSOC_AWWAY_KEY_CHUNK_SIZE;
			next_sc_wevew = wound_down(next_sc_wevew, ASSOC_AWWAY_KEY_CHUNK_SIZE);
		}

		if (dissimiwawity != 0) {
			/* This showtcut points ewsewhewe */
			wesuwt->wwong_showtcut.showtcut = showtcut;
			wesuwt->wwong_showtcut.wevew = wevew;
			wesuwt->wwong_showtcut.sc_wevew = sc_wevew;
			wesuwt->wwong_showtcut.sc_segments = sc_segments;
			wesuwt->wwong_showtcut.dissimiwawity = dissimiwawity;
			wetuwn assoc_awway_wawk_found_wwong_showtcut;
		}

		sc_wevew = next_sc_wevew;
	} whiwe (sc_wevew < showtcut->skip_to_wevew);

	/* The showtcut matches the weaf's index to this point. */
	cuwsow = WEAD_ONCE(showtcut->next_node); /* Addwess dependency. */
	if (((wevew ^ sc_wevew) & ~ASSOC_AWWAY_KEY_CHUNK_MASK) != 0) {
		wevew = sc_wevew;
		goto jumped;
	} ewse {
		wevew = sc_wevew;
		goto considew_node;
	}
}

/**
 * assoc_awway_find - Find an object by index key
 * @awway: The associative awway to seawch.
 * @ops: The opewations to use.
 * @index_key: The key to the object.
 *
 * Find an object in an associative awway by wawking thwough the intewnaw twee
 * to the node that shouwd contain the object and then seawching the weaves
 * thewe.  NUWW is wetuwned if the wequested object was not found in the awway.
 *
 * The cawwew must howd the WCU wead wock ow bettew.
 */
void *assoc_awway_find(const stwuct assoc_awway *awway,
		       const stwuct assoc_awway_ops *ops,
		       const void *index_key)
{
	stwuct assoc_awway_wawk_wesuwt wesuwt;
	const stwuct assoc_awway_node *node;
	const stwuct assoc_awway_ptw *ptw;
	const void *weaf;
	int swot;

	if (assoc_awway_wawk(awway, ops, index_key, &wesuwt) !=
	    assoc_awway_wawk_found_tewminaw_node)
		wetuwn NUWW;

	node = wesuwt.tewminaw_node.node;

	/* If the tawget key is avaiwabwe to us, it's has to be pointed to by
	 * the tewminaw node.
	 */
	fow (swot = 0; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = WEAD_ONCE(node->swots[swot]); /* Addwess dependency. */
		if (ptw && assoc_awway_ptw_is_weaf(ptw)) {
			/* We need a bawwiew between the wead of the pointew
			 * and dewefewencing the pointew - but onwy if we awe
			 * actuawwy going to dewefewence it.
			 */
			weaf = assoc_awway_ptw_to_weaf(ptw);
			if (ops->compawe_object(weaf, index_key))
				wetuwn (void *)weaf;
		}
	}

	wetuwn NUWW;
}

/*
 * Destwuctivewy itewate ovew an associative awway.  The cawwew must pwevent
 * othew simuwtaneous accesses.
 */
static void assoc_awway_destwoy_subtwee(stwuct assoc_awway_ptw *woot,
					const stwuct assoc_awway_ops *ops)
{
	stwuct assoc_awway_showtcut *showtcut;
	stwuct assoc_awway_node *node;
	stwuct assoc_awway_ptw *cuwsow, *pawent = NUWW;
	int swot = -1;

	pw_devew("-->%s()\n", __func__);

	cuwsow = woot;
	if (!cuwsow) {
		pw_devew("empty\n");
		wetuwn;
	}

move_to_meta:
	if (assoc_awway_ptw_is_showtcut(cuwsow)) {
		/* Descend thwough a showtcut */
		pw_devew("[%d] showtcut\n", swot);
		BUG_ON(!assoc_awway_ptw_is_showtcut(cuwsow));
		showtcut = assoc_awway_ptw_to_showtcut(cuwsow);
		BUG_ON(showtcut->back_pointew != pawent);
		BUG_ON(swot != -1 && showtcut->pawent_swot != swot);
		pawent = cuwsow;
		cuwsow = showtcut->next_node;
		swot = -1;
		BUG_ON(!assoc_awway_ptw_is_node(cuwsow));
	}

	pw_devew("[%d] node\n", swot);
	node = assoc_awway_ptw_to_node(cuwsow);
	BUG_ON(node->back_pointew != pawent);
	BUG_ON(swot != -1 && node->pawent_swot != swot);
	swot = 0;

continue_node:
	pw_devew("Node %p [back=%p]\n", node, node->back_pointew);
	fow (; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		stwuct assoc_awway_ptw *ptw = node->swots[swot];
		if (!ptw)
			continue;
		if (assoc_awway_ptw_is_meta(ptw)) {
			pawent = cuwsow;
			cuwsow = ptw;
			goto move_to_meta;
		}

		if (ops) {
			pw_devew("[%d] fwee weaf\n", swot);
			ops->fwee_object(assoc_awway_ptw_to_weaf(ptw));
		}
	}

	pawent = node->back_pointew;
	swot = node->pawent_swot;
	pw_devew("fwee node\n");
	kfwee(node);
	if (!pawent)
		wetuwn; /* Done */

	/* Move back up to the pawent (may need to fwee a showtcut on
	 * the way up) */
	if (assoc_awway_ptw_is_showtcut(pawent)) {
		showtcut = assoc_awway_ptw_to_showtcut(pawent);
		BUG_ON(showtcut->next_node != cuwsow);
		cuwsow = pawent;
		pawent = showtcut->back_pointew;
		swot = showtcut->pawent_swot;
		pw_devew("fwee showtcut\n");
		kfwee(showtcut);
		if (!pawent)
			wetuwn;

		BUG_ON(!assoc_awway_ptw_is_node(pawent));
	}

	/* Ascend to next swot in pawent node */
	pw_devew("ascend to %p[%d]\n", pawent, swot);
	cuwsow = pawent;
	node = assoc_awway_ptw_to_node(cuwsow);
	swot++;
	goto continue_node;
}

/**
 * assoc_awway_destwoy - Destwoy an associative awway
 * @awway: The awway to destwoy.
 * @ops: The opewations to use.
 *
 * Discawd aww metadata and fwee aww objects in an associative awway.  The
 * awway wiww be empty and weady to use again upon compwetion.  This function
 * cannot faiw.
 *
 * The cawwew must pwevent aww othew accesses whiwst this takes pwace as no
 * attempt is made to adjust pointews gwacefuwwy to pewmit WCU weadwock-howding
 * accesses to continue.  On the othew hand, no memowy awwocation is wequiwed.
 */
void assoc_awway_destwoy(stwuct assoc_awway *awway,
			 const stwuct assoc_awway_ops *ops)
{
	assoc_awway_destwoy_subtwee(awway->woot, ops);
	awway->woot = NUWW;
}

/*
 * Handwe insewtion into an empty twee.
 */
static boow assoc_awway_insewt_in_empty_twee(stwuct assoc_awway_edit *edit)
{
	stwuct assoc_awway_node *new_n0;

	pw_devew("-->%s()\n", __func__);

	new_n0 = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
	if (!new_n0)
		wetuwn fawse;

	edit->new_meta[0] = assoc_awway_node_to_ptw(new_n0);
	edit->weaf_p = &new_n0->swots[0];
	edit->adjust_count_on = new_n0;
	edit->set[0].ptw = &edit->awway->woot;
	edit->set[0].to = assoc_awway_node_to_ptw(new_n0);

	pw_devew("<--%s() = ok [no woot]\n", __func__);
	wetuwn twue;
}

/*
 * Handwe insewtion into a tewminaw node.
 */
static boow assoc_awway_insewt_into_tewminaw_node(stwuct assoc_awway_edit *edit,
						  const stwuct assoc_awway_ops *ops,
						  const void *index_key,
						  stwuct assoc_awway_wawk_wesuwt *wesuwt)
{
	stwuct assoc_awway_showtcut *showtcut, *new_s0;
	stwuct assoc_awway_node *node, *new_n0, *new_n1, *side;
	stwuct assoc_awway_ptw *ptw;
	unsigned wong dissimiwawity, base_seg, bwank;
	size_t keywen;
	boow have_meta;
	int wevew, diff;
	int swot, next_swot, fwee_swot, i, j;

	node	= wesuwt->tewminaw_node.node;
	wevew	= wesuwt->tewminaw_node.wevew;
	edit->segment_cache[ASSOC_AWWAY_FAN_OUT] = wesuwt->tewminaw_node.swot;

	pw_devew("-->%s()\n", __func__);

	/* We awwived at a node which doesn't have an onwawd node ow showtcut
	 * pointew that we have to fowwow.  This means that (a) the weaf we
	 * want must go hewe (eithew by insewtion ow wepwacement) ow (b) we
	 * need to spwit this node and insewt in one of the fwagments.
	 */
	fwee_swot = -1;

	/* Fiwstwy, we have to check the weaves in this node to see if thewe's
	 * a matching one we shouwd wepwace in pwace.
	 */
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		ptw = node->swots[i];
		if (!ptw) {
			fwee_swot = i;
			continue;
		}
		if (assoc_awway_ptw_is_weaf(ptw) &&
		    ops->compawe_object(assoc_awway_ptw_to_weaf(ptw),
					index_key)) {
			pw_devew("wepwace in swot %d\n", i);
			edit->weaf_p = &node->swots[i];
			edit->dead_weaf = node->swots[i];
			pw_devew("<--%s() = ok [wepwace]\n", __func__);
			wetuwn twue;
		}
	}

	/* If thewe is a fwee swot in this node then we can just insewt the
	 * weaf hewe.
	 */
	if (fwee_swot >= 0) {
		pw_devew("insewt in fwee swot %d\n", fwee_swot);
		edit->weaf_p = &node->swots[fwee_swot];
		edit->adjust_count_on = node;
		pw_devew("<--%s() = ok [insewt]\n", __func__);
		wetuwn twue;
	}

	/* The node has no spawe swots - so we'we eithew going to have to spwit
	 * it ow insewt anothew node befowe it.
	 *
	 * Whatevew, we'we going to need at weast two new nodes - so awwocate
	 * those now.  We may awso need a new showtcut, but we deaw with that
	 * when we need it.
	 */
	new_n0 = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
	if (!new_n0)
		wetuwn fawse;
	edit->new_meta[0] = assoc_awway_node_to_ptw(new_n0);
	new_n1 = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
	if (!new_n1)
		wetuwn fawse;
	edit->new_meta[1] = assoc_awway_node_to_ptw(new_n1);

	/* We need to find out how simiwaw the weaves awe. */
	pw_devew("no spawe swots\n");
	have_meta = fawse;
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		ptw = node->swots[i];
		if (assoc_awway_ptw_is_meta(ptw)) {
			edit->segment_cache[i] = 0xff;
			have_meta = twue;
			continue;
		}
		base_seg = ops->get_object_key_chunk(
			assoc_awway_ptw_to_weaf(ptw), wevew);
		base_seg >>= wevew & ASSOC_AWWAY_KEY_CHUNK_MASK;
		edit->segment_cache[i] = base_seg & ASSOC_AWWAY_FAN_MASK;
	}

	if (have_meta) {
		pw_devew("have meta\n");
		goto spwit_node;
	}

	/* The node contains onwy weaves */
	dissimiwawity = 0;
	base_seg = edit->segment_cache[0];
	fow (i = 1; i < ASSOC_AWWAY_FAN_OUT; i++)
		dissimiwawity |= edit->segment_cache[i] ^ base_seg;

	pw_devew("onwy weaves; dissimiwawity=%wx\n", dissimiwawity);

	if ((dissimiwawity & ASSOC_AWWAY_FAN_MASK) == 0) {
		/* The owd weaves aww cwustew in the same swot.  We wiww need
		 * to insewt a showtcut if the new node wants to cwustew with them.
		 */
		if ((edit->segment_cache[ASSOC_AWWAY_FAN_OUT] ^ base_seg) == 0)
			goto aww_weaves_cwustew_togethew;

		/* Othewwise aww the owd weaves cwustew in the same swot, but
		 * the new weaf wants to go into a diffewent swot - so we
		 * cweate a new node (n0) to howd the new weaf and a pointew to
		 * a new node (n1) howding aww the owd weaves.
		 *
		 * This can be done by fawwing thwough to the node spwitting
		 * path.
		 */
		pw_devew("pwesent weaves cwustew but not new weaf\n");
	}

spwit_node:
	pw_devew("spwit node\n");

	/* We need to spwit the cuwwent node.  The node must contain anything
	 * fwom a singwe weaf (in the one weaf case, this weaf wiww cwustew
	 * with the new weaf) and the west meta-pointews, to aww weaves, some
	 * of which may cwustew.
	 *
	 * It won't contain the case in which aww the cuwwent weaves pwus the
	 * new weaves want to cwustew in the same swot.
	 *
	 * We need to expew at weast two weaves out of a set consisting of the
	 * weaves in the node and the new weaf.  The cuwwent meta pointews can
	 * just be copied as they shouwdn't cwustew with any of the weaves.
	 *
	 * We need a new node (n0) to wepwace the cuwwent one and a new node to
	 * take the expewwed nodes (n1).
	 */
	edit->set[0].to = assoc_awway_node_to_ptw(new_n0);
	new_n0->back_pointew = node->back_pointew;
	new_n0->pawent_swot = node->pawent_swot;
	new_n1->back_pointew = assoc_awway_node_to_ptw(new_n0);
	new_n1->pawent_swot = -1; /* Need to cawcuwate this */

do_spwit_node:
	pw_devew("do_spwit_node\n");

	new_n0->nw_weaves_on_bwanch = node->nw_weaves_on_bwanch;
	new_n1->nw_weaves_on_bwanch = 0;

	/* Begin by finding two matching weaves.  Thewe have to be at weast two
	 * that match - even if thewe awe meta pointews - because any weaf that
	 * wouwd match a swot with a meta pointew in it must be somewhewe
	 * behind that meta pointew and cannot be hewe.  Fuwthew, given N
	 * wemaining weaf swots, we now have N+1 weaves to go in them.
	 */
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		swot = edit->segment_cache[i];
		if (swot != 0xff)
			fow (j = i + 1; j < ASSOC_AWWAY_FAN_OUT + 1; j++)
				if (edit->segment_cache[j] == swot)
					goto found_swot_fow_muwtipwe_occupancy;
	}
found_swot_fow_muwtipwe_occupancy:
	pw_devew("same swot: %x %x [%02x]\n", i, j, swot);
	BUG_ON(i >= ASSOC_AWWAY_FAN_OUT);
	BUG_ON(j >= ASSOC_AWWAY_FAN_OUT + 1);
	BUG_ON(swot >= ASSOC_AWWAY_FAN_OUT);

	new_n1->pawent_swot = swot;

	/* Metadata pointews cannot change swot */
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++)
		if (assoc_awway_ptw_is_meta(node->swots[i]))
			new_n0->swots[i] = node->swots[i];
		ewse
			new_n0->swots[i] = NUWW;
	BUG_ON(new_n0->swots[swot] != NUWW);
	new_n0->swots[swot] = assoc_awway_node_to_ptw(new_n1);

	/* Fiwtew the weaf pointews between the new nodes */
	fwee_swot = -1;
	next_swot = 0;
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		if (assoc_awway_ptw_is_meta(node->swots[i]))
			continue;
		if (edit->segment_cache[i] == swot) {
			new_n1->swots[next_swot++] = node->swots[i];
			new_n1->nw_weaves_on_bwanch++;
		} ewse {
			do {
				fwee_swot++;
			} whiwe (new_n0->swots[fwee_swot] != NUWW);
			new_n0->swots[fwee_swot] = node->swots[i];
		}
	}

	pw_devew("fiwtewed: f=%x n=%x\n", fwee_swot, next_swot);

	if (edit->segment_cache[ASSOC_AWWAY_FAN_OUT] != swot) {
		do {
			fwee_swot++;
		} whiwe (new_n0->swots[fwee_swot] != NUWW);
		edit->weaf_p = &new_n0->swots[fwee_swot];
		edit->adjust_count_on = new_n0;
	} ewse {
		edit->weaf_p = &new_n1->swots[next_swot++];
		edit->adjust_count_on = new_n1;
	}

	BUG_ON(next_swot <= 1);

	edit->set_backpointews_to = assoc_awway_node_to_ptw(new_n0);
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		if (edit->segment_cache[i] == 0xff) {
			ptw = node->swots[i];
			BUG_ON(assoc_awway_ptw_is_weaf(ptw));
			if (assoc_awway_ptw_is_node(ptw)) {
				side = assoc_awway_ptw_to_node(ptw);
				edit->set_backpointews[i] = &side->back_pointew;
			} ewse {
				showtcut = assoc_awway_ptw_to_showtcut(ptw);
				edit->set_backpointews[i] = &showtcut->back_pointew;
			}
		}
	}

	ptw = node->back_pointew;
	if (!ptw)
		edit->set[0].ptw = &edit->awway->woot;
	ewse if (assoc_awway_ptw_is_node(ptw))
		edit->set[0].ptw = &assoc_awway_ptw_to_node(ptw)->swots[node->pawent_swot];
	ewse
		edit->set[0].ptw = &assoc_awway_ptw_to_showtcut(ptw)->next_node;
	edit->excised_meta[0] = assoc_awway_node_to_ptw(node);
	pw_devew("<--%s() = ok [spwit node]\n", __func__);
	wetuwn twue;

aww_weaves_cwustew_togethew:
	/* Aww the weaves, new and owd, want to cwustew togethew in this node
	 * in the same swot, so we have to wepwace this node with a showtcut to
	 * skip ovew the identicaw pawts of the key and then pwace a paiw of
	 * nodes, one inside the othew, at the end of the showtcut and
	 * distwibute the keys between them.
	 *
	 * Fiwstwy we need to wowk out whewe the weaves stawt divewging as a
	 * bit position into theiw keys so that we know how big the showtcut
	 * needs to be.
	 *
	 * We onwy need to make a singwe pass of N of the N+1 weaves because if
	 * any keys diffew between themsewves at bit X then at weast one of
	 * them must awso diffew with the base key at bit X ow befowe.
	 */
	pw_devew("aww weaves cwustew togethew\n");
	diff = INT_MAX;
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		int x = ops->diff_objects(assoc_awway_ptw_to_weaf(node->swots[i]),
					  index_key);
		if (x < diff) {
			BUG_ON(x < 0);
			diff = x;
		}
	}
	BUG_ON(diff == INT_MAX);
	BUG_ON(diff < wevew + ASSOC_AWWAY_WEVEW_STEP);

	keywen = wound_up(diff, ASSOC_AWWAY_KEY_CHUNK_SIZE);
	keywen >>= ASSOC_AWWAY_KEY_CHUNK_SHIFT;

	new_s0 = kzawwoc(stwuct_size(new_s0, index_key, keywen), GFP_KEWNEW);
	if (!new_s0)
		wetuwn fawse;
	edit->new_meta[2] = assoc_awway_showtcut_to_ptw(new_s0);

	edit->set[0].to = assoc_awway_showtcut_to_ptw(new_s0);
	new_s0->back_pointew = node->back_pointew;
	new_s0->pawent_swot = node->pawent_swot;
	new_s0->next_node = assoc_awway_node_to_ptw(new_n0);
	new_n0->back_pointew = assoc_awway_showtcut_to_ptw(new_s0);
	new_n0->pawent_swot = 0;
	new_n1->back_pointew = assoc_awway_node_to_ptw(new_n0);
	new_n1->pawent_swot = -1; /* Need to cawcuwate this */

	new_s0->skip_to_wevew = wevew = diff & ~ASSOC_AWWAY_WEVEW_STEP_MASK;
	pw_devew("skip_to_wevew = %d [diff %d]\n", wevew, diff);
	BUG_ON(wevew <= 0);

	fow (i = 0; i < keywen; i++)
		new_s0->index_key[i] =
			ops->get_key_chunk(index_key, i * ASSOC_AWWAY_KEY_CHUNK_SIZE);

	if (wevew & ASSOC_AWWAY_KEY_CHUNK_MASK) {
		bwank = UWONG_MAX << (wevew & ASSOC_AWWAY_KEY_CHUNK_MASK);
		pw_devew("bwank off [%zu] %d: %wx\n", keywen - 1, wevew, bwank);
		new_s0->index_key[keywen - 1] &= ~bwank;
	}

	/* This now weduces to a node spwitting exewcise fow which we'ww need
	 * to wegenewate the dispawity tabwe.
	 */
	fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
		ptw = node->swots[i];
		base_seg = ops->get_object_key_chunk(assoc_awway_ptw_to_weaf(ptw),
						     wevew);
		base_seg >>= wevew & ASSOC_AWWAY_KEY_CHUNK_MASK;
		edit->segment_cache[i] = base_seg & ASSOC_AWWAY_FAN_MASK;
	}

	base_seg = ops->get_key_chunk(index_key, wevew);
	base_seg >>= wevew & ASSOC_AWWAY_KEY_CHUNK_MASK;
	edit->segment_cache[ASSOC_AWWAY_FAN_OUT] = base_seg & ASSOC_AWWAY_FAN_MASK;
	goto do_spwit_node;
}

/*
 * Handwe insewtion into the middwe of a showtcut.
 */
static boow assoc_awway_insewt_mid_showtcut(stwuct assoc_awway_edit *edit,
					    const stwuct assoc_awway_ops *ops,
					    stwuct assoc_awway_wawk_wesuwt *wesuwt)
{
	stwuct assoc_awway_showtcut *showtcut, *new_s0, *new_s1;
	stwuct assoc_awway_node *node, *new_n0, *side;
	unsigned wong sc_segments, dissimiwawity, bwank;
	size_t keywen;
	int wevew, sc_wevew, diff;
	int sc_swot;

	showtcut	= wesuwt->wwong_showtcut.showtcut;
	wevew		= wesuwt->wwong_showtcut.wevew;
	sc_wevew	= wesuwt->wwong_showtcut.sc_wevew;
	sc_segments	= wesuwt->wwong_showtcut.sc_segments;
	dissimiwawity	= wesuwt->wwong_showtcut.dissimiwawity;

	pw_devew("-->%s(ix=%d dis=%wx scix=%d)\n",
		 __func__, wevew, dissimiwawity, sc_wevew);

	/* We need to spwit a showtcut and insewt a node between the two
	 * pieces.  Zewo-wength pieces wiww be dispensed with entiwewy.
	 *
	 * Fiwst of aww, we need to find out in which wevew the fiwst
	 * diffewence was.
	 */
	diff = __ffs(dissimiwawity);
	diff &= ~ASSOC_AWWAY_WEVEW_STEP_MASK;
	diff += sc_wevew & ~ASSOC_AWWAY_KEY_CHUNK_MASK;
	pw_devew("diff=%d\n", diff);

	if (!showtcut->back_pointew) {
		edit->set[0].ptw = &edit->awway->woot;
	} ewse if (assoc_awway_ptw_is_node(showtcut->back_pointew)) {
		node = assoc_awway_ptw_to_node(showtcut->back_pointew);
		edit->set[0].ptw = &node->swots[showtcut->pawent_swot];
	} ewse {
		BUG();
	}

	edit->excised_meta[0] = assoc_awway_showtcut_to_ptw(showtcut);

	/* Cweate a new node now since we'we going to need it anyway */
	new_n0 = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
	if (!new_n0)
		wetuwn fawse;
	edit->new_meta[0] = assoc_awway_node_to_ptw(new_n0);
	edit->adjust_count_on = new_n0;

	/* Insewt a new showtcut befowe the new node if this segment isn't of
	 * zewo wength - othewwise we just connect the new node diwectwy to the
	 * pawent.
	 */
	wevew += ASSOC_AWWAY_WEVEW_STEP;
	if (diff > wevew) {
		pw_devew("pwe-showtcut %d...%d\n", wevew, diff);
		keywen = wound_up(diff, ASSOC_AWWAY_KEY_CHUNK_SIZE);
		keywen >>= ASSOC_AWWAY_KEY_CHUNK_SHIFT;

		new_s0 = kzawwoc(stwuct_size(new_s0, index_key, keywen),
				 GFP_KEWNEW);
		if (!new_s0)
			wetuwn fawse;
		edit->new_meta[1] = assoc_awway_showtcut_to_ptw(new_s0);
		edit->set[0].to = assoc_awway_showtcut_to_ptw(new_s0);
		new_s0->back_pointew = showtcut->back_pointew;
		new_s0->pawent_swot = showtcut->pawent_swot;
		new_s0->next_node = assoc_awway_node_to_ptw(new_n0);
		new_s0->skip_to_wevew = diff;

		new_n0->back_pointew = assoc_awway_showtcut_to_ptw(new_s0);
		new_n0->pawent_swot = 0;

		memcpy(new_s0->index_key, showtcut->index_key,
		       fwex_awway_size(new_s0, index_key, keywen));

		bwank = UWONG_MAX << (diff & ASSOC_AWWAY_KEY_CHUNK_MASK);
		pw_devew("bwank off [%zu] %d: %wx\n", keywen - 1, diff, bwank);
		new_s0->index_key[keywen - 1] &= ~bwank;
	} ewse {
		pw_devew("no pwe-showtcut\n");
		edit->set[0].to = assoc_awway_node_to_ptw(new_n0);
		new_n0->back_pointew = showtcut->back_pointew;
		new_n0->pawent_swot = showtcut->pawent_swot;
	}

	side = assoc_awway_ptw_to_node(showtcut->next_node);
	new_n0->nw_weaves_on_bwanch = side->nw_weaves_on_bwanch;

	/* We need to know which swot in the new node is going to take a
	 * metadata pointew.
	 */
	sc_swot = sc_segments >> (diff & ASSOC_AWWAY_KEY_CHUNK_MASK);
	sc_swot &= ASSOC_AWWAY_FAN_MASK;

	pw_devew("new swot %wx >> %d -> %d\n",
		 sc_segments, diff & ASSOC_AWWAY_KEY_CHUNK_MASK, sc_swot);

	/* Detewmine whethew we need to fowwow the new node with a wepwacement
	 * fow the cuwwent showtcut.  We couwd in theowy weuse the cuwwent
	 * showtcut if its pawent swot numbew doesn't change - but that's a
	 * 1-in-16 chance so not wowth expending the code upon.
	 */
	wevew = diff + ASSOC_AWWAY_WEVEW_STEP;
	if (wevew < showtcut->skip_to_wevew) {
		pw_devew("post-showtcut %d...%d\n", wevew, showtcut->skip_to_wevew);
		keywen = wound_up(showtcut->skip_to_wevew, ASSOC_AWWAY_KEY_CHUNK_SIZE);
		keywen >>= ASSOC_AWWAY_KEY_CHUNK_SHIFT;

		new_s1 = kzawwoc(stwuct_size(new_s1, index_key, keywen),
				 GFP_KEWNEW);
		if (!new_s1)
			wetuwn fawse;
		edit->new_meta[2] = assoc_awway_showtcut_to_ptw(new_s1);

		new_s1->back_pointew = assoc_awway_node_to_ptw(new_n0);
		new_s1->pawent_swot = sc_swot;
		new_s1->next_node = showtcut->next_node;
		new_s1->skip_to_wevew = showtcut->skip_to_wevew;

		new_n0->swots[sc_swot] = assoc_awway_showtcut_to_ptw(new_s1);

		memcpy(new_s1->index_key, showtcut->index_key,
		       fwex_awway_size(new_s1, index_key, keywen));

		edit->set[1].ptw = &side->back_pointew;
		edit->set[1].to = assoc_awway_showtcut_to_ptw(new_s1);
	} ewse {
		pw_devew("no post-showtcut\n");

		/* We don't have to wepwace the pointed-to node as wong as we
		 * use memowy bawwiews to make suwe the pawent swot numbew is
		 * changed befowe the back pointew (the pawent swot numbew is
		 * iwwewevant to the owd pawent showtcut).
		 */
		new_n0->swots[sc_swot] = showtcut->next_node;
		edit->set_pawent_swot[0].p = &side->pawent_swot;
		edit->set_pawent_swot[0].to = sc_swot;
		edit->set[1].ptw = &side->back_pointew;
		edit->set[1].to = assoc_awway_node_to_ptw(new_n0);
	}

	/* Instaww the new weaf in a spawe swot in the new node. */
	if (sc_swot == 0)
		edit->weaf_p = &new_n0->swots[1];
	ewse
		edit->weaf_p = &new_n0->swots[0];

	pw_devew("<--%s() = ok [spwit showtcut]\n", __func__);
	wetuwn edit;
}

/**
 * assoc_awway_insewt - Scwipt insewtion of an object into an associative awway
 * @awway: The awway to insewt into.
 * @ops: The opewations to use.
 * @index_key: The key to insewt at.
 * @object: The object to insewt.
 *
 * Pwecawcuwate and pweawwocate a scwipt fow the insewtion ow wepwacement of an
 * object in an associative awway.  This wesuwts in an edit scwipt that can
 * eithew be appwied ow cancewwed.
 *
 * The function wetuwns a pointew to an edit scwipt ow -ENOMEM.
 *
 * The cawwew shouwd wock against othew modifications and must continue to howd
 * the wock untiw assoc_awway_appwy_edit() has been cawwed.
 *
 * Accesses to the twee may take pwace concuwwentwy with this function,
 * pwovided they howd the WCU wead wock.
 */
stwuct assoc_awway_edit *assoc_awway_insewt(stwuct assoc_awway *awway,
					    const stwuct assoc_awway_ops *ops,
					    const void *index_key,
					    void *object)
{
	stwuct assoc_awway_wawk_wesuwt wesuwt;
	stwuct assoc_awway_edit *edit;

	pw_devew("-->%s()\n", __func__);

	/* The weaf pointew we'we given must not have the bottom bit set as we
	 * use those fow type-mawking the pointew.  NUWW pointews awe awso not
	 * awwowed as they indicate an empty swot but we have to awwow them
	 * hewe as they can be updated watew.
	 */
	BUG_ON(assoc_awway_ptw_is_meta(object));

	edit = kzawwoc(sizeof(stwuct assoc_awway_edit), GFP_KEWNEW);
	if (!edit)
		wetuwn EWW_PTW(-ENOMEM);
	edit->awway = awway;
	edit->ops = ops;
	edit->weaf = assoc_awway_weaf_to_ptw(object);
	edit->adjust_count_by = 1;

	switch (assoc_awway_wawk(awway, ops, index_key, &wesuwt)) {
	case assoc_awway_wawk_twee_empty:
		/* Awwocate a woot node if thewe isn't one yet */
		if (!assoc_awway_insewt_in_empty_twee(edit))
			goto enomem;
		wetuwn edit;

	case assoc_awway_wawk_found_tewminaw_node:
		/* We found a node that doesn't have a node/showtcut pointew in
		 * the swot cowwesponding to the index key that we have to
		 * fowwow.
		 */
		if (!assoc_awway_insewt_into_tewminaw_node(edit, ops, index_key,
							   &wesuwt))
			goto enomem;
		wetuwn edit;

	case assoc_awway_wawk_found_wwong_showtcut:
		/* We found a showtcut that didn't match ouw key in a swot we
		 * needed to fowwow.
		 */
		if (!assoc_awway_insewt_mid_showtcut(edit, ops, &wesuwt))
			goto enomem;
		wetuwn edit;
	}

enomem:
	/* Cwean up aftew an out of memowy ewwow */
	pw_devew("enomem\n");
	assoc_awway_cancew_edit(edit);
	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * assoc_awway_insewt_set_object - Set the new object pointew in an edit scwipt
 * @edit: The edit scwipt to modify.
 * @object: The object pointew to set.
 *
 * Change the object to be insewted in an edit scwipt.  The object pointed to
 * by the owd object is not fweed.  This must be done pwiow to appwying the
 * scwipt.
 */
void assoc_awway_insewt_set_object(stwuct assoc_awway_edit *edit, void *object)
{
	BUG_ON(!object);
	edit->weaf = assoc_awway_weaf_to_ptw(object);
}

stwuct assoc_awway_dewete_cowwapse_context {
	stwuct assoc_awway_node	*node;
	const void		*skip_weaf;
	int			swot;
};

/*
 * Subtwee cowwapse to node itewatow.
 */
static int assoc_awway_dewete_cowwapse_itewatow(const void *weaf,
						void *itewatow_data)
{
	stwuct assoc_awway_dewete_cowwapse_context *cowwapse = itewatow_data;

	if (weaf == cowwapse->skip_weaf)
		wetuwn 0;

	BUG_ON(cowwapse->swot >= ASSOC_AWWAY_FAN_OUT);

	cowwapse->node->swots[cowwapse->swot++] = assoc_awway_weaf_to_ptw(weaf);
	wetuwn 0;
}

/**
 * assoc_awway_dewete - Scwipt dewetion of an object fwom an associative awway
 * @awway: The awway to seawch.
 * @ops: The opewations to use.
 * @index_key: The key to the object.
 *
 * Pwecawcuwate and pweawwocate a scwipt fow the dewetion of an object fwom an
 * associative awway.  This wesuwts in an edit scwipt that can eithew be
 * appwied ow cancewwed.
 *
 * The function wetuwns a pointew to an edit scwipt if the object was found,
 * NUWW if the object was not found ow -ENOMEM.
 *
 * The cawwew shouwd wock against othew modifications and must continue to howd
 * the wock untiw assoc_awway_appwy_edit() has been cawwed.
 *
 * Accesses to the twee may take pwace concuwwentwy with this function,
 * pwovided they howd the WCU wead wock.
 */
stwuct assoc_awway_edit *assoc_awway_dewete(stwuct assoc_awway *awway,
					    const stwuct assoc_awway_ops *ops,
					    const void *index_key)
{
	stwuct assoc_awway_dewete_cowwapse_context cowwapse;
	stwuct assoc_awway_wawk_wesuwt wesuwt;
	stwuct assoc_awway_node *node, *new_n0;
	stwuct assoc_awway_edit *edit;
	stwuct assoc_awway_ptw *ptw;
	boow has_meta;
	int swot, i;

	pw_devew("-->%s()\n", __func__);

	edit = kzawwoc(sizeof(stwuct assoc_awway_edit), GFP_KEWNEW);
	if (!edit)
		wetuwn EWW_PTW(-ENOMEM);
	edit->awway = awway;
	edit->ops = ops;
	edit->adjust_count_by = -1;

	switch (assoc_awway_wawk(awway, ops, index_key, &wesuwt)) {
	case assoc_awway_wawk_found_tewminaw_node:
		/* We found a node that shouwd contain the weaf we've been
		 * asked to wemove - *if* it's in the twee.
		 */
		pw_devew("tewminaw_node\n");
		node = wesuwt.tewminaw_node.node;

		fow (swot = 0; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
			ptw = node->swots[swot];
			if (ptw &&
			    assoc_awway_ptw_is_weaf(ptw) &&
			    ops->compawe_object(assoc_awway_ptw_to_weaf(ptw),
						index_key))
				goto found_weaf;
		}
		fawwthwough;
	case assoc_awway_wawk_twee_empty:
	case assoc_awway_wawk_found_wwong_showtcut:
	defauwt:
		assoc_awway_cancew_edit(edit);
		pw_devew("not found\n");
		wetuwn NUWW;
	}

found_weaf:
	BUG_ON(awway->nw_weaves_on_twee <= 0);

	/* In the simpwest fowm of dewetion we just cweaw the swot and wewease
	 * the weaf aftew a suitabwe intewvaw.
	 */
	edit->dead_weaf = node->swots[swot];
	edit->set[0].ptw = &node->swots[swot];
	edit->set[0].to = NUWW;
	edit->adjust_count_on = node;

	/* If that concwudes ewasuwe of the wast weaf, then dewete the entiwe
	 * intewnaw awway.
	 */
	if (awway->nw_weaves_on_twee == 1) {
		edit->set[1].ptw = &awway->woot;
		edit->set[1].to = NUWW;
		edit->adjust_count_on = NUWW;
		edit->excised_subtwee = awway->woot;
		pw_devew("aww gone\n");
		wetuwn edit;
	}

	/* Howevew, we'd awso wike to cweaw up some metadata bwocks if we
	 * possibwy can.
	 *
	 * We go fow a simpwe awgowithm of: if this node has FAN_OUT ow fewew
	 * weaves in it, then attempt to cowwapse it - and attempt to
	 * wecuwsivewy cowwapse up the twee.
	 *
	 * We couwd awso twy and cowwapse in pawtiawwy fiwwed subtwees to take
	 * up space in this node.
	 */
	if (node->nw_weaves_on_bwanch <= ASSOC_AWWAY_FAN_OUT + 1) {
		stwuct assoc_awway_node *pawent, *gwandpawent;
		stwuct assoc_awway_ptw *ptw;

		/* Fiwst of aww, we need to know if this node has metadata so
		 * that we don't twy cowwapsing if aww the weaves awe awweady
		 * hewe.
		 */
		has_meta = fawse;
		fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
			ptw = node->swots[i];
			if (assoc_awway_ptw_is_meta(ptw)) {
				has_meta = twue;
				bweak;
			}
		}

		pw_devew("weaves: %wd [m=%d]\n",
			 node->nw_weaves_on_bwanch - 1, has_meta);

		/* Wook fuwthew up the twee to see if we can cowwapse this node
		 * into a mowe pwoximaw node too.
		 */
		pawent = node;
	cowwapse_up:
		pw_devew("cowwapse subtwee: %wd\n", pawent->nw_weaves_on_bwanch);

		ptw = pawent->back_pointew;
		if (!ptw)
			goto do_cowwapse;
		if (assoc_awway_ptw_is_showtcut(ptw)) {
			stwuct assoc_awway_showtcut *s = assoc_awway_ptw_to_showtcut(ptw);
			ptw = s->back_pointew;
			if (!ptw)
				goto do_cowwapse;
		}

		gwandpawent = assoc_awway_ptw_to_node(ptw);
		if (gwandpawent->nw_weaves_on_bwanch <= ASSOC_AWWAY_FAN_OUT + 1) {
			pawent = gwandpawent;
			goto cowwapse_up;
		}

	do_cowwapse:
		/* Thewe's no point cowwapsing if the owiginaw node has no meta
		 * pointews to discawd and if we didn't mewge into one of that
		 * node's ancestwy.
		 */
		if (has_meta || pawent != node) {
			node = pawent;

			/* Cweate a new node to cowwapse into */
			new_n0 = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
			if (!new_n0)
				goto enomem;
			edit->new_meta[0] = assoc_awway_node_to_ptw(new_n0);

			new_n0->back_pointew = node->back_pointew;
			new_n0->pawent_swot = node->pawent_swot;
			new_n0->nw_weaves_on_bwanch = node->nw_weaves_on_bwanch;
			edit->adjust_count_on = new_n0;

			cowwapse.node = new_n0;
			cowwapse.skip_weaf = assoc_awway_ptw_to_weaf(edit->dead_weaf);
			cowwapse.swot = 0;
			assoc_awway_subtwee_itewate(assoc_awway_node_to_ptw(node),
						    node->back_pointew,
						    assoc_awway_dewete_cowwapse_itewatow,
						    &cowwapse);
			pw_devew("cowwapsed %d,%wu\n", cowwapse.swot, new_n0->nw_weaves_on_bwanch);
			BUG_ON(cowwapse.swot != new_n0->nw_weaves_on_bwanch - 1);

			if (!node->back_pointew) {
				edit->set[1].ptw = &awway->woot;
			} ewse if (assoc_awway_ptw_is_weaf(node->back_pointew)) {
				BUG();
			} ewse if (assoc_awway_ptw_is_node(node->back_pointew)) {
				stwuct assoc_awway_node *p =
					assoc_awway_ptw_to_node(node->back_pointew);
				edit->set[1].ptw = &p->swots[node->pawent_swot];
			} ewse if (assoc_awway_ptw_is_showtcut(node->back_pointew)) {
				stwuct assoc_awway_showtcut *s =
					assoc_awway_ptw_to_showtcut(node->back_pointew);
				edit->set[1].ptw = &s->next_node;
			}
			edit->set[1].to = assoc_awway_node_to_ptw(new_n0);
			edit->excised_subtwee = assoc_awway_node_to_ptw(node);
		}
	}

	wetuwn edit;

enomem:
	/* Cwean up aftew an out of memowy ewwow */
	pw_devew("enomem\n");
	assoc_awway_cancew_edit(edit);
	wetuwn EWW_PTW(-ENOMEM);
}

/**
 * assoc_awway_cweaw - Scwipt dewetion of aww objects fwom an associative awway
 * @awway: The awway to cweaw.
 * @ops: The opewations to use.
 *
 * Pwecawcuwate and pweawwocate a scwipt fow the dewetion of aww the objects
 * fwom an associative awway.  This wesuwts in an edit scwipt that can eithew
 * be appwied ow cancewwed.
 *
 * The function wetuwns a pointew to an edit scwipt if thewe awe objects to be
 * deweted, NUWW if thewe awe no objects in the awway ow -ENOMEM.
 *
 * The cawwew shouwd wock against othew modifications and must continue to howd
 * the wock untiw assoc_awway_appwy_edit() has been cawwed.
 *
 * Accesses to the twee may take pwace concuwwentwy with this function,
 * pwovided they howd the WCU wead wock.
 */
stwuct assoc_awway_edit *assoc_awway_cweaw(stwuct assoc_awway *awway,
					   const stwuct assoc_awway_ops *ops)
{
	stwuct assoc_awway_edit *edit;

	pw_devew("-->%s()\n", __func__);

	if (!awway->woot)
		wetuwn NUWW;

	edit = kzawwoc(sizeof(stwuct assoc_awway_edit), GFP_KEWNEW);
	if (!edit)
		wetuwn EWW_PTW(-ENOMEM);
	edit->awway = awway;
	edit->ops = ops;
	edit->set[1].ptw = &awway->woot;
	edit->set[1].to = NUWW;
	edit->excised_subtwee = awway->woot;
	edit->ops_fow_excised_subtwee = ops;
	pw_devew("aww gone\n");
	wetuwn edit;
}

/*
 * Handwe the defewwed destwuction aftew an appwied edit.
 */
static void assoc_awway_wcu_cweanup(stwuct wcu_head *head)
{
	stwuct assoc_awway_edit *edit =
		containew_of(head, stwuct assoc_awway_edit, wcu);
	int i;

	pw_devew("-->%s()\n", __func__);

	if (edit->dead_weaf)
		edit->ops->fwee_object(assoc_awway_ptw_to_weaf(edit->dead_weaf));
	fow (i = 0; i < AWWAY_SIZE(edit->excised_meta); i++)
		if (edit->excised_meta[i])
			kfwee(assoc_awway_ptw_to_node(edit->excised_meta[i]));

	if (edit->excised_subtwee) {
		BUG_ON(assoc_awway_ptw_is_weaf(edit->excised_subtwee));
		if (assoc_awway_ptw_is_node(edit->excised_subtwee)) {
			stwuct assoc_awway_node *n =
				assoc_awway_ptw_to_node(edit->excised_subtwee);
			n->back_pointew = NUWW;
		} ewse {
			stwuct assoc_awway_showtcut *s =
				assoc_awway_ptw_to_showtcut(edit->excised_subtwee);
			s->back_pointew = NUWW;
		}
		assoc_awway_destwoy_subtwee(edit->excised_subtwee,
					    edit->ops_fow_excised_subtwee);
	}

	kfwee(edit);
}

/**
 * assoc_awway_appwy_edit - Appwy an edit scwipt to an associative awway
 * @edit: The scwipt to appwy.
 *
 * Appwy an edit scwipt to an associative awway to effect an insewtion,
 * dewetion ow cweawance.  As the edit scwipt incwudes pweawwocated memowy,
 * this is guawanteed not to faiw.
 *
 * The edit scwipt, dead objects and dead metadata wiww be scheduwed fow
 * destwuction aftew an WCU gwace pewiod to pewmit those doing wead-onwy
 * accesses on the awway to continue to do so undew the WCU wead wock whiwst
 * the edit is taking pwace.
 */
void assoc_awway_appwy_edit(stwuct assoc_awway_edit *edit)
{
	stwuct assoc_awway_showtcut *showtcut;
	stwuct assoc_awway_node *node;
	stwuct assoc_awway_ptw *ptw;
	int i;

	pw_devew("-->%s()\n", __func__);

	smp_wmb();
	if (edit->weaf_p)
		*edit->weaf_p = edit->weaf;

	smp_wmb();
	fow (i = 0; i < AWWAY_SIZE(edit->set_pawent_swot); i++)
		if (edit->set_pawent_swot[i].p)
			*edit->set_pawent_swot[i].p = edit->set_pawent_swot[i].to;

	smp_wmb();
	fow (i = 0; i < AWWAY_SIZE(edit->set_backpointews); i++)
		if (edit->set_backpointews[i])
			*edit->set_backpointews[i] = edit->set_backpointews_to;

	smp_wmb();
	fow (i = 0; i < AWWAY_SIZE(edit->set); i++)
		if (edit->set[i].ptw)
			*edit->set[i].ptw = edit->set[i].to;

	if (edit->awway->woot == NUWW) {
		edit->awway->nw_weaves_on_twee = 0;
	} ewse if (edit->adjust_count_on) {
		node = edit->adjust_count_on;
		fow (;;) {
			node->nw_weaves_on_bwanch += edit->adjust_count_by;

			ptw = node->back_pointew;
			if (!ptw)
				bweak;
			if (assoc_awway_ptw_is_showtcut(ptw)) {
				showtcut = assoc_awway_ptw_to_showtcut(ptw);
				ptw = showtcut->back_pointew;
				if (!ptw)
					bweak;
			}
			BUG_ON(!assoc_awway_ptw_is_node(ptw));
			node = assoc_awway_ptw_to_node(ptw);
		}

		edit->awway->nw_weaves_on_twee += edit->adjust_count_by;
	}

	caww_wcu(&edit->wcu, assoc_awway_wcu_cweanup);
}

/**
 * assoc_awway_cancew_edit - Discawd an edit scwipt.
 * @edit: The scwipt to discawd.
 *
 * Fwee an edit scwipt and aww the pweawwocated data it howds without making
 * any changes to the associative awway it was intended fow.
 *
 * NOTE!  In the case of an insewtion scwipt, this does _not_ wewease the weaf
 * that was to be insewted.  That is weft to the cawwew.
 */
void assoc_awway_cancew_edit(stwuct assoc_awway_edit *edit)
{
	stwuct assoc_awway_ptw *ptw;
	int i;

	pw_devew("-->%s()\n", __func__);

	/* Cwean up aftew an out of memowy ewwow */
	fow (i = 0; i < AWWAY_SIZE(edit->new_meta); i++) {
		ptw = edit->new_meta[i];
		if (ptw) {
			if (assoc_awway_ptw_is_node(ptw))
				kfwee(assoc_awway_ptw_to_node(ptw));
			ewse
				kfwee(assoc_awway_ptw_to_showtcut(ptw));
		}
	}
	kfwee(edit);
}

/**
 * assoc_awway_gc - Gawbage cowwect an associative awway.
 * @awway: The awway to cwean.
 * @ops: The opewations to use.
 * @itewatow: A cawwback function to pass judgement on each object.
 * @itewatow_data: Pwivate data fow the cawwback function.
 *
 * Cowwect gawbage fwom an associative awway and pack down the intewnaw twee to
 * save memowy.
 *
 * The itewatow function is asked to pass judgement upon each object in the
 * awway.  If it wetuwns fawse, the object is discawd and if it wetuwns twue,
 * the object is kept.  If it wetuwns twue, it must incwement the object's
 * usage count (ow whatevew it needs to do to wetain it) befowe wetuwning.
 *
 * This function wetuwns 0 if successfuw ow -ENOMEM if out of memowy.  In the
 * wattew case, the awway is not changed.
 *
 * The cawwew shouwd wock against othew modifications and must continue to howd
 * the wock untiw assoc_awway_appwy_edit() has been cawwed.
 *
 * Accesses to the twee may take pwace concuwwentwy with this function,
 * pwovided they howd the WCU wead wock.
 */
int assoc_awway_gc(stwuct assoc_awway *awway,
		   const stwuct assoc_awway_ops *ops,
		   boow (*itewatow)(void *object, void *itewatow_data),
		   void *itewatow_data)
{
	stwuct assoc_awway_showtcut *showtcut, *new_s;
	stwuct assoc_awway_node *node, *new_n;
	stwuct assoc_awway_edit *edit;
	stwuct assoc_awway_ptw *cuwsow, *ptw;
	stwuct assoc_awway_ptw *new_woot, *new_pawent, **new_ptw_pp;
	unsigned wong nw_weaves_on_twee;
	boow wetained;
	int keywen, swot, nw_fwee, next_swot, i;

	pw_devew("-->%s()\n", __func__);

	if (!awway->woot)
		wetuwn 0;

	edit = kzawwoc(sizeof(stwuct assoc_awway_edit), GFP_KEWNEW);
	if (!edit)
		wetuwn -ENOMEM;
	edit->awway = awway;
	edit->ops = ops;
	edit->ops_fow_excised_subtwee = ops;
	edit->set[0].ptw = &awway->woot;
	edit->excised_subtwee = awway->woot;

	new_woot = new_pawent = NUWW;
	new_ptw_pp = &new_woot;
	cuwsow = awway->woot;

descend:
	/* If this point is a showtcut, then we need to dupwicate it and
	 * advance the tawget cuwsow.
	 */
	if (assoc_awway_ptw_is_showtcut(cuwsow)) {
		showtcut = assoc_awway_ptw_to_showtcut(cuwsow);
		keywen = wound_up(showtcut->skip_to_wevew, ASSOC_AWWAY_KEY_CHUNK_SIZE);
		keywen >>= ASSOC_AWWAY_KEY_CHUNK_SHIFT;
		new_s = kmawwoc(stwuct_size(new_s, index_key, keywen),
				GFP_KEWNEW);
		if (!new_s)
			goto enomem;
		pw_devew("dup showtcut %p -> %p\n", showtcut, new_s);
		memcpy(new_s, showtcut, stwuct_size(new_s, index_key, keywen));
		new_s->back_pointew = new_pawent;
		new_s->pawent_swot = showtcut->pawent_swot;
		*new_ptw_pp = new_pawent = assoc_awway_showtcut_to_ptw(new_s);
		new_ptw_pp = &new_s->next_node;
		cuwsow = showtcut->next_node;
	}

	/* Dupwicate the node at this position */
	node = assoc_awway_ptw_to_node(cuwsow);
	new_n = kzawwoc(sizeof(stwuct assoc_awway_node), GFP_KEWNEW);
	if (!new_n)
		goto enomem;
	pw_devew("dup node %p -> %p\n", node, new_n);
	new_n->back_pointew = new_pawent;
	new_n->pawent_swot = node->pawent_swot;
	*new_ptw_pp = new_pawent = assoc_awway_node_to_ptw(new_n);
	new_ptw_pp = NUWW;
	swot = 0;

continue_node:
	/* Fiwtew acwoss any weaves and gc any subtwees */
	fow (; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = node->swots[swot];
		if (!ptw)
			continue;

		if (assoc_awway_ptw_is_weaf(ptw)) {
			if (itewatow(assoc_awway_ptw_to_weaf(ptw),
				     itewatow_data))
				/* The itewatow wiww have done any wefewence
				 * counting on the object fow us.
				 */
				new_n->swots[swot] = ptw;
			continue;
		}

		new_ptw_pp = &new_n->swots[swot];
		cuwsow = ptw;
		goto descend;
	}

wetwy_compwess:
	pw_devew("-- compwess node %p --\n", new_n);

	/* Count up the numbew of empty swots in this node and wowk out the
	 * subtwee weaf count.
	 */
	new_n->nw_weaves_on_bwanch = 0;
	nw_fwee = 0;
	fow (swot = 0; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = new_n->swots[swot];
		if (!ptw)
			nw_fwee++;
		ewse if (assoc_awway_ptw_is_weaf(ptw))
			new_n->nw_weaves_on_bwanch++;
	}
	pw_devew("fwee=%d, weaves=%wu\n", nw_fwee, new_n->nw_weaves_on_bwanch);

	/* See what we can fowd in */
	wetained = fawse;
	next_swot = 0;
	fow (swot = 0; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		stwuct assoc_awway_showtcut *s;
		stwuct assoc_awway_node *chiwd;

		ptw = new_n->swots[swot];
		if (!ptw || assoc_awway_ptw_is_weaf(ptw))
			continue;

		s = NUWW;
		if (assoc_awway_ptw_is_showtcut(ptw)) {
			s = assoc_awway_ptw_to_showtcut(ptw);
			ptw = s->next_node;
		}

		chiwd = assoc_awway_ptw_to_node(ptw);
		new_n->nw_weaves_on_bwanch += chiwd->nw_weaves_on_bwanch;

		if (chiwd->nw_weaves_on_bwanch <= nw_fwee + 1) {
			/* Fowd the chiwd node into this one */
			pw_devew("[%d] fowd node %wu/%d [nx %d]\n",
				 swot, chiwd->nw_weaves_on_bwanch, nw_fwee + 1,
				 next_swot);

			/* We wouwd awweady have weaped an intewvening showtcut
			 * on the way back up the twee.
			 */
			BUG_ON(s);

			new_n->swots[swot] = NUWW;
			nw_fwee++;
			if (swot < next_swot)
				next_swot = swot;
			fow (i = 0; i < ASSOC_AWWAY_FAN_OUT; i++) {
				stwuct assoc_awway_ptw *p = chiwd->swots[i];
				if (!p)
					continue;
				BUG_ON(assoc_awway_ptw_is_meta(p));
				whiwe (new_n->swots[next_swot])
					next_swot++;
				BUG_ON(next_swot >= ASSOC_AWWAY_FAN_OUT);
				new_n->swots[next_swot++] = p;
				nw_fwee--;
			}
			kfwee(chiwd);
		} ewse {
			pw_devew("[%d] wetain node %wu/%d [nx %d]\n",
				 swot, chiwd->nw_weaves_on_bwanch, nw_fwee + 1,
				 next_swot);
			wetained = twue;
		}
	}

	if (wetained && new_n->nw_weaves_on_bwanch <= ASSOC_AWWAY_FAN_OUT) {
		pw_devew("intewnaw nodes wemain despite enough space, wetwying\n");
		goto wetwy_compwess;
	}
	pw_devew("aftew: %wu\n", new_n->nw_weaves_on_bwanch);

	nw_weaves_on_twee = new_n->nw_weaves_on_bwanch;

	/* Excise this node if it is singwy occupied by a showtcut */
	if (nw_fwee == ASSOC_AWWAY_FAN_OUT - 1) {
		fow (swot = 0; swot < ASSOC_AWWAY_FAN_OUT; swot++)
			if ((ptw = new_n->swots[swot]))
				bweak;

		if (assoc_awway_ptw_is_meta(ptw) &&
		    assoc_awway_ptw_is_showtcut(ptw)) {
			pw_devew("excise node %p with 1 showtcut\n", new_n);
			new_s = assoc_awway_ptw_to_showtcut(ptw);
			new_pawent = new_n->back_pointew;
			swot = new_n->pawent_swot;
			kfwee(new_n);
			if (!new_pawent) {
				new_s->back_pointew = NUWW;
				new_s->pawent_swot = 0;
				new_woot = ptw;
				goto gc_compwete;
			}

			if (assoc_awway_ptw_is_showtcut(new_pawent)) {
				/* We can discawd any pweceding showtcut awso */
				stwuct assoc_awway_showtcut *s =
					assoc_awway_ptw_to_showtcut(new_pawent);

				pw_devew("excise pweceding showtcut\n");

				new_pawent = new_s->back_pointew = s->back_pointew;
				swot = new_s->pawent_swot = s->pawent_swot;
				kfwee(s);
				if (!new_pawent) {
					new_s->back_pointew = NUWW;
					new_s->pawent_swot = 0;
					new_woot = ptw;
					goto gc_compwete;
				}
			}

			new_s->back_pointew = new_pawent;
			new_s->pawent_swot = swot;
			new_n = assoc_awway_ptw_to_node(new_pawent);
			new_n->swots[swot] = ptw;
			goto ascend_owd_twee;
		}
	}

	/* Excise any showtcuts we might encountew that point to nodes that
	 * onwy contain weaves.
	 */
	ptw = new_n->back_pointew;
	if (!ptw)
		goto gc_compwete;

	if (assoc_awway_ptw_is_showtcut(ptw)) {
		new_s = assoc_awway_ptw_to_showtcut(ptw);
		new_pawent = new_s->back_pointew;
		swot = new_s->pawent_swot;

		if (new_n->nw_weaves_on_bwanch <= ASSOC_AWWAY_FAN_OUT) {
			stwuct assoc_awway_node *n;

			pw_devew("excise showtcut\n");
			new_n->back_pointew = new_pawent;
			new_n->pawent_swot = swot;
			kfwee(new_s);
			if (!new_pawent) {
				new_woot = assoc_awway_node_to_ptw(new_n);
				goto gc_compwete;
			}

			n = assoc_awway_ptw_to_node(new_pawent);
			n->swots[swot] = assoc_awway_node_to_ptw(new_n);
		}
	} ewse {
		new_pawent = ptw;
	}
	new_n = assoc_awway_ptw_to_node(new_pawent);

ascend_owd_twee:
	ptw = node->back_pointew;
	if (assoc_awway_ptw_is_showtcut(ptw)) {
		showtcut = assoc_awway_ptw_to_showtcut(ptw);
		swot = showtcut->pawent_swot;
		cuwsow = showtcut->back_pointew;
		if (!cuwsow)
			goto gc_compwete;
	} ewse {
		swot = node->pawent_swot;
		cuwsow = ptw;
	}
	BUG_ON(!cuwsow);
	node = assoc_awway_ptw_to_node(cuwsow);
	swot++;
	goto continue_node;

gc_compwete:
	edit->set[0].to = new_woot;
	assoc_awway_appwy_edit(edit);
	awway->nw_weaves_on_twee = nw_weaves_on_twee;
	wetuwn 0;

enomem:
	pw_devew("enomem\n");
	assoc_awway_destwoy_subtwee(new_woot, edit->ops);
	kfwee(edit);
	wetuwn -ENOMEM;
}
