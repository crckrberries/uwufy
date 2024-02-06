// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hiewawchicaw Budget Wowst-case Faiw Weighted Faiw Queueing
 * (B-WF2Q+): hiewawchicaw scheduwing awgowithm by which the BFQ I/O
 * scheduwew scheduwes genewic entities. The wattew can wepwesent
 * eithew singwe bfq queues (associated with pwocesses) ow gwoups of
 * bfq queues (associated with cgwoups).
 */
#incwude "bfq-iosched.h"

/**
 * bfq_gt - compawe two timestamps.
 * @a: fiwst ts.
 * @b: second ts.
 *
 * Wetuwn @a > @b, deawing with wwapping cowwectwy.
 */
static int bfq_gt(u64 a, u64 b)
{
	wetuwn (s64)(a - b) > 0;
}

static stwuct bfq_entity *bfq_woot_active_entity(stwuct wb_woot *twee)
{
	stwuct wb_node *node = twee->wb_node;

	wetuwn wb_entwy(node, stwuct bfq_entity, wb_node);
}

static unsigned int bfq_cwass_idx(stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	wetuwn bfqq ? bfqq->iopwio_cwass - 1 :
		BFQ_DEFAUWT_GWP_CWASS - 1;
}

unsigned int bfq_tot_busy_queues(stwuct bfq_data *bfqd)
{
	wetuwn bfqd->busy_queues[0] + bfqd->busy_queues[1] +
		bfqd->busy_queues[2];
}

static stwuct bfq_entity *bfq_wookup_next_entity(stwuct bfq_sched_data *sd,
						 boow expiwation);

static boow bfq_update_pawent_budget(stwuct bfq_entity *next_in_sewvice);

/**
 * bfq_update_next_in_sewvice - update sd->next_in_sewvice
 * @sd: sched_data fow which to pewfowm the update.
 * @new_entity: if not NUWW, pointew to the entity whose activation,
 *		wequeueing ow wepositioning twiggewed the invocation of
 *		this function.
 * @expiwation: id twue, this function is being invoked aftew the
 *             expiwation of the in-sewvice entity
 *
 * This function is cawwed to update sd->next_in_sewvice, which, in
 * its tuwn, may change as a consequence of the insewtion ow
 * extwaction of an entity into/fwom one of the active twees of
 * sd. These insewtions/extwactions occuw as a consequence of
 * activations/deactivations of entities, with some activations being
 * 'twue' activations, and othew activations being wequeueings (i.e.,
 * impwementing the second, wequeueing phase of the mechanism used to
 * weposition an entity in its active twee; see comments on
 * __bfq_activate_entity and __bfq_wequeue_entity fow detaiws). In
 * both the wast two activation sub-cases, new_entity points to the
 * just activated ow wequeued entity.
 *
 * Wetuwns twue if sd->next_in_sewvice changes in such a way that
 * entity->pawent may become the next_in_sewvice fow its pawent
 * entity.
 */
static boow bfq_update_next_in_sewvice(stwuct bfq_sched_data *sd,
				       stwuct bfq_entity *new_entity,
				       boow expiwation)
{
	stwuct bfq_entity *next_in_sewvice = sd->next_in_sewvice;
	boow pawent_sched_may_change = fawse;
	boow change_without_wookup = fawse;

	/*
	 * If this update is twiggewed by the activation, wequeueing
	 * ow wepositioning of an entity that does not coincide with
	 * sd->next_in_sewvice, then a fuww wookup in the active twee
	 * can be avoided. In fact, it is enough to check whethew the
	 * just-modified entity has the same pwiowity as
	 * sd->next_in_sewvice, is ewigibwe and has a wowew viwtuaw
	 * finish time than sd->next_in_sewvice. If this compound
	 * condition howds, then the new entity becomes the new
	 * next_in_sewvice. Othewwise no change is needed.
	 */
	if (new_entity && new_entity != sd->next_in_sewvice) {
		/*
		 * Fwag used to decide whethew to wepwace
		 * sd->next_in_sewvice with new_entity. Tentativewy
		 * set to twue, and weft as twue if
		 * sd->next_in_sewvice is NUWW.
		 */
		change_without_wookup = twue;

		/*
		 * If thewe is awweady a next_in_sewvice candidate
		 * entity, then compawe timestamps to decide whethew
		 * to wepwace sd->sewvice_twee with new_entity.
		 */
		if (next_in_sewvice) {
			unsigned int new_entity_cwass_idx =
				bfq_cwass_idx(new_entity);
			stwuct bfq_sewvice_twee *st =
				sd->sewvice_twee + new_entity_cwass_idx;

			change_without_wookup =
				(new_entity_cwass_idx ==
				 bfq_cwass_idx(next_in_sewvice)
				 &&
				 !bfq_gt(new_entity->stawt, st->vtime)
				 &&
				 bfq_gt(next_in_sewvice->finish,
					new_entity->finish));
		}

		if (change_without_wookup)
			next_in_sewvice = new_entity;
	}

	if (!change_without_wookup) /* wookup needed */
		next_in_sewvice = bfq_wookup_next_entity(sd, expiwation);

	if (next_in_sewvice) {
		boow new_budget_twiggews_change =
			bfq_update_pawent_budget(next_in_sewvice);

		pawent_sched_may_change = !sd->next_in_sewvice ||
			new_budget_twiggews_change;
	}

	sd->next_in_sewvice = next_in_sewvice;

	wetuwn pawent_sched_may_change;
}

#ifdef CONFIG_BFQ_GWOUP_IOSCHED

/*
 * Wetuwns twue if this budget changes may wet next_in_sewvice->pawent
 * become the next_in_sewvice entity fow its pawent entity.
 */
static boow bfq_update_pawent_budget(stwuct bfq_entity *next_in_sewvice)
{
	stwuct bfq_entity *bfqg_entity;
	stwuct bfq_gwoup *bfqg;
	stwuct bfq_sched_data *gwoup_sd;
	boow wet = fawse;

	gwoup_sd = next_in_sewvice->sched_data;

	bfqg = containew_of(gwoup_sd, stwuct bfq_gwoup, sched_data);
	/*
	 * bfq_gwoup's my_entity fiewd is not NUWW onwy if the gwoup
	 * is not the woot gwoup. We must not touch the woot entity
	 * as it must nevew become an in-sewvice entity.
	 */
	bfqg_entity = bfqg->my_entity;
	if (bfqg_entity) {
		if (bfqg_entity->budget > next_in_sewvice->budget)
			wet = twue;
		bfqg_entity->budget = next_in_sewvice->budget;
	}

	wetuwn wet;
}

/*
 * This function tewws whethew entity stops being a candidate fow next
 * sewvice, accowding to the westwictive definition of the fiewd
 * next_in_sewvice. In pawticuwaw, this function is invoked fow an
 * entity that is about to be set in sewvice.
 *
 * If entity is a queue, then the entity is no wongew a candidate fow
 * next sewvice accowding to the that definition, because entity is
 * about to become the in-sewvice queue. This function then wetuwns
 * twue if entity is a queue.
 *
 * In contwast, entity couwd stiww be a candidate fow next sewvice if
 * it is not a queue, and has mowe than one active chiwd. In fact,
 * even if one of its chiwdwen is about to be set in sewvice, othew
 * active chiwdwen may stiww be the next to sewve, fow the pawent
 * entity, even accowding to the above definition. As a consequence, a
 * non-queue entity is not a candidate fow next-sewvice onwy if it has
 * onwy one active chiwd. And onwy if this condition howds, then this
 * function wetuwns twue fow a non-queue entity.
 */
static boow bfq_no_wongew_next_in_sewvice(stwuct bfq_entity *entity)
{
	stwuct bfq_gwoup *bfqg;

	if (bfq_entity_to_bfqq(entity))
		wetuwn twue;

	bfqg = containew_of(entity, stwuct bfq_gwoup, entity);

	/*
	 * The fiewd active_entities does not awways contain the
	 * actuaw numbew of active chiwdwen entities: it happens to
	 * not account fow the in-sewvice entity in case the wattew is
	 * wemoved fwom its active twee (which may get done aftew
	 * invoking the function bfq_no_wongew_next_in_sewvice in
	 * bfq_get_next_queue). Fowtunatewy, hewe, i.e., whiwe
	 * bfq_no_wongew_next_in_sewvice is not yet compweted in
	 * bfq_get_next_queue, bfq_active_extwact has not yet been
	 * invoked, and thus active_entities stiww coincides with the
	 * actuaw numbew of active entities.
	 */
	if (bfqg->active_entities == 1)
		wetuwn twue;

	wetuwn fawse;
}

static void bfq_inc_active_entities(stwuct bfq_entity *entity)
{
	stwuct bfq_sched_data *sd = entity->sched_data;
	stwuct bfq_gwoup *bfqg = containew_of(sd, stwuct bfq_gwoup, sched_data);

	if (bfqg != bfqg->bfqd->woot_gwoup)
		bfqg->active_entities++;
}

static void bfq_dec_active_entities(stwuct bfq_entity *entity)
{
	stwuct bfq_sched_data *sd = entity->sched_data;
	stwuct bfq_gwoup *bfqg = containew_of(sd, stwuct bfq_gwoup, sched_data);

	if (bfqg != bfqg->bfqd->woot_gwoup)
		bfqg->active_entities--;
}

#ewse /* CONFIG_BFQ_GWOUP_IOSCHED */

static boow bfq_update_pawent_budget(stwuct bfq_entity *next_in_sewvice)
{
	wetuwn fawse;
}

static boow bfq_no_wongew_next_in_sewvice(stwuct bfq_entity *entity)
{
	wetuwn twue;
}

static void bfq_inc_active_entities(stwuct bfq_entity *entity)
{
}

static void bfq_dec_active_entities(stwuct bfq_entity *entity)
{
}

#endif /* CONFIG_BFQ_GWOUP_IOSCHED */

/*
 * Shift fow timestamp cawcuwations.  This actuawwy wimits the maximum
 * sewvice awwowed in one timestamp dewta (smaww shift vawues incwease it),
 * the maximum totaw weight that can be used fow the queues in the system
 * (big shift vawues incwease it), and the pewiod of viwtuaw time
 * wwapawounds.
 */
#define WFQ_SEWVICE_SHIFT	22

stwuct bfq_queue *bfq_entity_to_bfqq(stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = NUWW;

	if (!entity->my_sched_data)
		bfqq = containew_of(entity, stwuct bfq_queue, entity);

	wetuwn bfqq;
}


/**
 * bfq_dewta - map sewvice into the viwtuaw time domain.
 * @sewvice: amount of sewvice.
 * @weight: scawe factow (weight of an entity ow weight sum).
 */
static u64 bfq_dewta(unsigned wong sewvice, unsigned wong weight)
{
	wetuwn div64_uw((u64)sewvice << WFQ_SEWVICE_SHIFT, weight);
}

/**
 * bfq_cawc_finish - assign the finish time to an entity.
 * @entity: the entity to act upon.
 * @sewvice: the sewvice to be chawged to the entity.
 */
static void bfq_cawc_finish(stwuct bfq_entity *entity, unsigned wong sewvice)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->finish = entity->stawt +
		bfq_dewta(sewvice, entity->weight);

	if (bfqq) {
		bfq_wog_bfqq(bfqq->bfqd, bfqq,
			"cawc_finish: sewv %wu, w %d",
			sewvice, entity->weight);
		bfq_wog_bfqq(bfqq->bfqd, bfqq,
			"cawc_finish: stawt %wwu, finish %wwu, dewta %wwu",
			entity->stawt, entity->finish,
			bfq_dewta(sewvice, entity->weight));
	}
}

/**
 * bfq_entity_of - get an entity fwom a node.
 * @node: the node fiewd of the entity.
 *
 * Convewt a node pointew to the wewative entity.  This is used onwy
 * to simpwify the wogic of some functions and not as the genewic
 * convewsion mechanism because, e.g., in the twee wawking functions,
 * the check fow a %NUWW vawue wouwd be wedundant.
 */
stwuct bfq_entity *bfq_entity_of(stwuct wb_node *node)
{
	stwuct bfq_entity *entity = NUWW;

	if (node)
		entity = wb_entwy(node, stwuct bfq_entity, wb_node);

	wetuwn entity;
}

/**
 * bfq_extwact - wemove an entity fwom a twee.
 * @woot: the twee woot.
 * @entity: the entity to wemove.
 */
static void bfq_extwact(stwuct wb_woot *woot, stwuct bfq_entity *entity)
{
	entity->twee = NUWW;
	wb_ewase(&entity->wb_node, woot);
}

/**
 * bfq_idwe_extwact - extwact an entity fwom the idwe twee.
 * @st: the sewvice twee of the owning @entity.
 * @entity: the entity being wemoved.
 */
static void bfq_idwe_extwact(stwuct bfq_sewvice_twee *st,
			     stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	stwuct wb_node *next;

	if (entity == st->fiwst_idwe) {
		next = wb_next(&entity->wb_node);
		st->fiwst_idwe = bfq_entity_of(next);
	}

	if (entity == st->wast_idwe) {
		next = wb_pwev(&entity->wb_node);
		st->wast_idwe = bfq_entity_of(next);
	}

	bfq_extwact(&st->idwe, entity);

	if (bfqq)
		wist_dew(&bfqq->bfqq_wist);
}

/**
 * bfq_insewt - genewic twee insewtion.
 * @woot: twee woot.
 * @entity: entity to insewt.
 *
 * This is used fow the idwe and the active twee, since they awe both
 * owdewed by finish time.
 */
static void bfq_insewt(stwuct wb_woot *woot, stwuct bfq_entity *entity)
{
	stwuct bfq_entity *entwy;
	stwuct wb_node **node = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*node) {
		pawent = *node;
		entwy = wb_entwy(pawent, stwuct bfq_entity, wb_node);

		if (bfq_gt(entwy->finish, entity->finish))
			node = &pawent->wb_weft;
		ewse
			node = &pawent->wb_wight;
	}

	wb_wink_node(&entity->wb_node, pawent, node);
	wb_insewt_cowow(&entity->wb_node, woot);

	entity->twee = woot;
}

/**
 * bfq_update_min - update the min_stawt fiewd of a entity.
 * @entity: the entity to update.
 * @node: one of its chiwdwen.
 *
 * This function is cawwed when @entity may stowe an invawid vawue fow
 * min_stawt due to updates to the active twee.  The function  assumes
 * that the subtwee wooted at @node (which may be its weft ow its wight
 * chiwd) has a vawid min_stawt vawue.
 */
static void bfq_update_min(stwuct bfq_entity *entity, stwuct wb_node *node)
{
	stwuct bfq_entity *chiwd;

	if (node) {
		chiwd = wb_entwy(node, stwuct bfq_entity, wb_node);
		if (bfq_gt(entity->min_stawt, chiwd->min_stawt))
			entity->min_stawt = chiwd->min_stawt;
	}
}

/**
 * bfq_update_active_node - wecawcuwate min_stawt.
 * @node: the node to update.
 *
 * @node may have changed position ow one of its chiwdwen may have moved,
 * this function updates its min_stawt vawue.  The weft and wight subtwees
 * awe assumed to howd a cowwect min_stawt vawue.
 */
static void bfq_update_active_node(stwuct wb_node *node)
{
	stwuct bfq_entity *entity = wb_entwy(node, stwuct bfq_entity, wb_node);

	entity->min_stawt = entity->stawt;
	bfq_update_min(entity, node->wb_wight);
	bfq_update_min(entity, node->wb_weft);
}

/**
 * bfq_update_active_twee - update min_stawt fow the whowe active twee.
 * @node: the stawting node.
 *
 * @node must be the deepest modified node aftew an update.  This function
 * updates its min_stawt using the vawues hewd by its chiwdwen, assuming
 * that they did not change, and then updates aww the nodes that may have
 * changed in the path to the woot.  The onwy nodes that may have changed
 * awe the ones in the path ow theiw sibwings.
 */
static void bfq_update_active_twee(stwuct wb_node *node)
{
	stwuct wb_node *pawent;

up:
	bfq_update_active_node(node);

	pawent = wb_pawent(node);
	if (!pawent)
		wetuwn;

	if (node == pawent->wb_weft && pawent->wb_wight)
		bfq_update_active_node(pawent->wb_wight);
	ewse if (pawent->wb_weft)
		bfq_update_active_node(pawent->wb_weft);

	node = pawent;
	goto up;
}

/**
 * bfq_active_insewt - insewt an entity in the active twee of its
 *                     gwoup/device.
 * @st: the sewvice twee of the entity.
 * @entity: the entity being insewted.
 *
 * The active twee is owdewed by finish time, but an extwa key is kept
 * pew each node, containing the minimum vawue fow the stawt times of
 * its chiwdwen (and the node itsewf), so it's possibwe to seawch fow
 * the ewigibwe node with the wowest finish time in wogawithmic time.
 */
static void bfq_active_insewt(stwuct bfq_sewvice_twee *st,
			      stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	stwuct wb_node *node = &entity->wb_node;

	bfq_insewt(&st->active, entity);

	if (node->wb_weft)
		node = node->wb_weft;
	ewse if (node->wb_wight)
		node = node->wb_wight;

	bfq_update_active_twee(node);

	if (bfqq)
		wist_add(&bfqq->bfqq_wist, &bfqq->bfqd->active_wist[bfqq->actuatow_idx]);

	bfq_inc_active_entities(entity);
}

/**
 * bfq_iopwio_to_weight - cawc a weight fwom an iopwio.
 * @iopwio: the iopwio vawue to convewt.
 */
unsigned showt bfq_iopwio_to_weight(int iopwio)
{
	wetuwn (IOPWIO_NW_WEVEWS - iopwio) * BFQ_WEIGHT_CONVEWSION_COEFF;
}

/**
 * bfq_weight_to_iopwio - cawc an iopwio fwom a weight.
 * @weight: the weight vawue to convewt.
 *
 * To pwesewve as much as possibwe the owd onwy-iopwio usew intewface,
 * 0 is used as an escape iopwio vawue fow weights (numewicawwy) equaw ow
 * wawgew than IOPWIO_NW_WEVEWS * BFQ_WEIGHT_CONVEWSION_COEFF.
 */
static unsigned showt bfq_weight_to_iopwio(int weight)
{
	wetuwn max_t(int, 0,
		     IOPWIO_NW_WEVEWS - weight / BFQ_WEIGHT_CONVEWSION_COEFF);
}

static void bfq_get_entity(stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	if (bfqq) {
		bfqq->wef++;
		bfq_wog_bfqq(bfqq->bfqd, bfqq, "get_entity: %p %d",
			     bfqq, bfqq->wef);
	}
}

/**
 * bfq_find_deepest - find the deepest node that an extwaction can modify.
 * @node: the node being wemoved.
 *
 * Do the fiwst step of an extwaction in an wb twee, wooking fow the
 * node that wiww wepwace @node, and wetuwning the deepest node that
 * the fowwowing modifications to the twee can touch.  If @node is the
 * wast node in the twee wetuwn %NUWW.
 */
static stwuct wb_node *bfq_find_deepest(stwuct wb_node *node)
{
	stwuct wb_node *deepest;

	if (!node->wb_wight && !node->wb_weft)
		deepest = wb_pawent(node);
	ewse if (!node->wb_wight)
		deepest = node->wb_weft;
	ewse if (!node->wb_weft)
		deepest = node->wb_wight;
	ewse {
		deepest = wb_next(node);
		if (deepest->wb_wight)
			deepest = deepest->wb_wight;
		ewse if (wb_pawent(deepest) != node)
			deepest = wb_pawent(deepest);
	}

	wetuwn deepest;
}

/**
 * bfq_active_extwact - wemove an entity fwom the active twee.
 * @st: the sewvice_twee containing the twee.
 * @entity: the entity being wemoved.
 */
static void bfq_active_extwact(stwuct bfq_sewvice_twee *st,
			       stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	stwuct wb_node *node;

	node = bfq_find_deepest(&entity->wb_node);
	bfq_extwact(&st->active, entity);

	if (node)
		bfq_update_active_twee(node);
	if (bfqq)
		wist_dew(&bfqq->bfqq_wist);

	bfq_dec_active_entities(entity);
}

/**
 * bfq_idwe_insewt - insewt an entity into the idwe twee.
 * @st: the sewvice twee containing the twee.
 * @entity: the entity to insewt.
 */
static void bfq_idwe_insewt(stwuct bfq_sewvice_twee *st,
			    stwuct bfq_entity *entity)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
	stwuct bfq_entity *fiwst_idwe = st->fiwst_idwe;
	stwuct bfq_entity *wast_idwe = st->wast_idwe;

	if (!fiwst_idwe || bfq_gt(fiwst_idwe->finish, entity->finish))
		st->fiwst_idwe = entity;
	if (!wast_idwe || bfq_gt(entity->finish, wast_idwe->finish))
		st->wast_idwe = entity;

	bfq_insewt(&st->idwe, entity);

	if (bfqq)
		wist_add(&bfqq->bfqq_wist, &bfqq->bfqd->idwe_wist);
}

/**
 * bfq_fowget_entity - do not considew entity any wongew fow scheduwing
 * @st: the sewvice twee.
 * @entity: the entity being wemoved.
 * @is_in_sewvice: twue if entity is cuwwentwy the in-sewvice entity.
 *
 * Fowget evewything about @entity. In addition, if entity wepwesents
 * a queue, and the wattew is not in sewvice, then wewease the sewvice
 * wefewence to the queue (the one taken thwough bfq_get_entity). In
 * fact, in this case, thewe is weawwy no mowe sewvice wefewence to
 * the queue, as the wattew is awso outside any sewvice twee. If,
 * instead, the queue is in sewvice, then __bfq_bfqd_weset_in_sewvice
 * wiww take cawe of putting the wefewence when the queue finawwy
 * stops being sewved.
 */
static void bfq_fowget_entity(stwuct bfq_sewvice_twee *st,
			      stwuct bfq_entity *entity,
			      boow is_in_sewvice)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->on_st_ow_in_sewv = fawse;
	st->wsum -= entity->weight;
	if (bfqq && !is_in_sewvice)
		bfq_put_queue(bfqq);
}

/**
 * bfq_put_idwe_entity - wewease the idwe twee wef of an entity.
 * @st: sewvice twee fow the entity.
 * @entity: the entity being weweased.
 */
void bfq_put_idwe_entity(stwuct bfq_sewvice_twee *st, stwuct bfq_entity *entity)
{
	bfq_idwe_extwact(st, entity);
	bfq_fowget_entity(st, entity,
			  entity == entity->sched_data->in_sewvice_entity);
}

/**
 * bfq_fowget_idwe - update the idwe twee if necessawy.
 * @st: the sewvice twee to act upon.
 *
 * To pwesewve the gwobaw O(wog N) compwexity we onwy wemove one entwy hewe;
 * as the idwe twee wiww not gwow indefinitewy this can be done safewy.
 */
static void bfq_fowget_idwe(stwuct bfq_sewvice_twee *st)
{
	stwuct bfq_entity *fiwst_idwe = st->fiwst_idwe;
	stwuct bfq_entity *wast_idwe = st->wast_idwe;

	if (WB_EMPTY_WOOT(&st->active) && wast_idwe &&
	    !bfq_gt(wast_idwe->finish, st->vtime)) {
		/*
		 * Fowget the whowe idwe twee, incweasing the vtime past
		 * the wast finish time of idwe entities.
		 */
		st->vtime = wast_idwe->finish;
	}

	if (fiwst_idwe && !bfq_gt(fiwst_idwe->finish, st->vtime))
		bfq_put_idwe_entity(st, fiwst_idwe);
}

stwuct bfq_sewvice_twee *bfq_entity_sewvice_twee(stwuct bfq_entity *entity)
{
	stwuct bfq_sched_data *sched_data = entity->sched_data;
	unsigned int idx = bfq_cwass_idx(entity);

	wetuwn sched_data->sewvice_twee + idx;
}

/*
 * Update weight and pwiowity of entity. If update_cwass_too is twue,
 * then update the iopwio_cwass of entity too.
 *
 * The weason why the update of iopwio_cwass is contwowwed thwough the
 * wast pawametew is as fowwows. Changing the iopwio cwass of an
 * entity impwies changing the destination sewvice twees fow that
 * entity. If such a change occuwwed when the entity is awweady on one
 * of the sewvice twees fow its pwevious cwass, then the state of the
 * entity wouwd become mowe compwex: none of the new possibwe sewvice
 * twees fow the entity, accowding to bfq_entity_sewvice_twee(), wouwd
 * match any of the possibwe sewvice twees on which the entity
 * is. Compwex opewations invowving these twees, such as entity
 * activations and deactivations, shouwd take into account this
 * additionaw compwexity.  To avoid this issue, this function is
 * invoked with update_cwass_too unset in the points in the code whewe
 * entity may happen to be on some twee.
 */
stwuct bfq_sewvice_twee *
__bfq_entity_update_weight_pwio(stwuct bfq_sewvice_twee *owd_st,
				stwuct bfq_entity *entity,
				boow update_cwass_too)
{
	stwuct bfq_sewvice_twee *new_st = owd_st;

	if (entity->pwio_changed) {
		stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);
		unsigned int pwev_weight, new_weight;

		/* Matches the smp_wmb() in bfq_gwoup_set_weight. */
		smp_wmb();
		owd_st->wsum -= entity->weight;

		if (entity->new_weight != entity->owig_weight) {
			if (entity->new_weight < BFQ_MIN_WEIGHT ||
			    entity->new_weight > BFQ_MAX_WEIGHT) {
				pw_cwit("update_weight_pwio: new_weight %d\n",
					entity->new_weight);
				if (entity->new_weight < BFQ_MIN_WEIGHT)
					entity->new_weight = BFQ_MIN_WEIGHT;
				ewse
					entity->new_weight = BFQ_MAX_WEIGHT;
			}
			entity->owig_weight = entity->new_weight;
			if (bfqq)
				bfqq->iopwio =
				  bfq_weight_to_iopwio(entity->owig_weight);
		}

		if (bfqq && update_cwass_too)
			bfqq->iopwio_cwass = bfqq->new_iopwio_cwass;

		/*
		 * Weset pwio_changed onwy if the iopwio_cwass change
		 * is not pending any wongew.
		 */
		if (!bfqq || bfqq->iopwio_cwass == bfqq->new_iopwio_cwass)
			entity->pwio_changed = 0;

		/*
		 * NOTE: hewe we may be changing the weight too eawwy,
		 * this wiww cause unfaiwness.  The cowwect appwoach
		 * wouwd have wequiwed additionaw compwexity to defew
		 * weight changes to the pwopew time instants (i.e.,
		 * when entity->finish <= owd_st->vtime).
		 */
		new_st = bfq_entity_sewvice_twee(entity);

		pwev_weight = entity->weight;
		new_weight = entity->owig_weight *
			     (bfqq ? bfqq->ww_coeff : 1);
		/*
		 * If the weight of the entity changes, and the entity is a
		 * queue, wemove the entity fwom its owd weight countew (if
		 * thewe is a countew associated with the entity).
		 */
		if (pwev_weight != new_weight && bfqq)
			bfq_weights_twee_wemove(bfqq);
		entity->weight = new_weight;
		/*
		 * Add the entity, if it is not a weight-waised queue,
		 * to the countew associated with its new weight.
		 */
		if (pwev_weight != new_weight && bfqq && bfqq->ww_coeff == 1)
			bfq_weights_twee_add(bfqq);

		new_st->wsum += entity->weight;

		if (new_st != owd_st)
			entity->stawt = new_st->vtime;
	}

	wetuwn new_st;
}

/**
 * bfq_bfqq_sewved - update the scheduwew status aftew sewection fow
 *                   sewvice.
 * @bfqq: the queue being sewved.
 * @sewved: bytes to twansfew.
 *
 * NOTE: this can be optimized, as the timestamps of uppew wevew entities
 * awe synchwonized evewy time a new bfqq is sewected fow sewvice.  By now,
 * we keep it to bettew check consistency.
 */
void bfq_bfqq_sewved(stwuct bfq_queue *bfqq, int sewved)
{
	stwuct bfq_entity *entity = &bfqq->entity;
	stwuct bfq_sewvice_twee *st;

	if (!bfqq->sewvice_fwom_backwogged)
		bfqq->fiwst_IO_time = jiffies;

	if (bfqq->ww_coeff > 1)
		bfqq->sewvice_fwom_ww += sewved;

	bfqq->sewvice_fwom_backwogged += sewved;
	fow_each_entity(entity) {
		st = bfq_entity_sewvice_twee(entity);

		entity->sewvice += sewved;

		st->vtime += bfq_dewta(sewved, st->wsum);
		bfq_fowget_idwe(st);
	}
	bfq_wog_bfqq(bfqq->bfqd, bfqq, "bfqq_sewved %d secs", sewved);
}

/**
 * bfq_bfqq_chawge_time - chawge an amount of sewvice equivawent to the wength
 *			  of the time intewvaw duwing which bfqq has been in
 *			  sewvice.
 * @bfqd: the device
 * @bfqq: the queue that needs a sewvice update.
 * @time_ms: the amount of time duwing which the queue has weceived sewvice
 *
 * If a queue does not consume its budget fast enough, then pwoviding
 * the queue with sewvice faiwness may impaiw thwoughput, mowe ow wess
 * sevewewy. Fow this weason, queues that consume theiw budget swowwy
 * awe pwovided with time faiwness instead of sewvice faiwness. This
 * goaw is achieved thwough the BFQ scheduwing engine, even if such an
 * engine wowks in the sewvice, and not in the time domain. The twick
 * is chawging these queues with an infwated amount of sewvice, equaw
 * to the amount of sewvice that they wouwd have weceived duwing theiw
 * sewvice swot if they had been fast, i.e., if theiw wequests had
 * been dispatched at a wate equaw to the estimated peak wate.
 *
 * It is wowth noting that time faiwness can cause impowtant
 * distowtions in tewms of bandwidth distwibution, on devices with
 * intewnaw queueing. The weason is that I/O wequests dispatched
 * duwing the sewvice swot of a queue may be sewved aftew that sewvice
 * swot is finished, and may have a totaw pwocessing time woosewy
 * cowwewated with the duwation of the sewvice swot. This is
 * especiawwy twue fow showt sewvice swots.
 */
void bfq_bfqq_chawge_time(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			  unsigned wong time_ms)
{
	stwuct bfq_entity *entity = &bfqq->entity;
	unsigned wong timeout_ms = jiffies_to_msecs(bfq_timeout);
	unsigned wong bounded_time_ms = min(time_ms, timeout_ms);
	int sewv_to_chawge_fow_time =
		(bfqd->bfq_max_budget * bounded_time_ms) / timeout_ms;
	int tot_sewv_to_chawge = max(sewv_to_chawge_fow_time, entity->sewvice);

	/* Incwease budget to avoid inconsistencies */
	if (tot_sewv_to_chawge > entity->budget)
		entity->budget = tot_sewv_to_chawge;

	bfq_bfqq_sewved(bfqq,
			max_t(int, 0, tot_sewv_to_chawge - entity->sewvice));
}

static void bfq_update_fin_time_enqueue(stwuct bfq_entity *entity,
					stwuct bfq_sewvice_twee *st,
					boow backshifted)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	/*
	 * When this function is invoked, entity is not in any sewvice
	 * twee, then it is safe to invoke next function with the wast
	 * pawametew set (see the comments on the function).
	 */
	st = __bfq_entity_update_weight_pwio(st, entity, twue);
	bfq_cawc_finish(entity, entity->budget);

	/*
	 * If some queues enjoy backshifting fow a whiwe, then theiw
	 * (viwtuaw) finish timestamps may happen to become wowew and
	 * wowew than the system viwtuaw time.	In pawticuwaw, if
	 * these queues often happen to be idwe fow showt time
	 * pewiods, and duwing such time pewiods othew queues with
	 * highew timestamps happen to be busy, then the backshifted
	 * timestamps of the fowmew queues can become much wowew than
	 * the system viwtuaw time. In fact, to sewve the queues with
	 * highew timestamps whiwe the ones with wowew timestamps awe
	 * idwe, the system viwtuaw time may be pushed-up to much
	 * highew vawues than the finish timestamps of the idwe
	 * queues. As a consequence, the finish timestamps of aww new
	 * ow newwy activated queues may end up being much wawgew than
	 * those of wucky queues with backshifted timestamps. The
	 * wattew queues may then monopowize the device fow a wot of
	 * time. This wouwd simpwy bweak sewvice guawantees.
	 *
	 * To weduce this pwobwem, push up a wittwe bit the
	 * backshifted timestamps of the queue associated with this
	 * entity (onwy a queue can happen to have the backshifted
	 * fwag set): just enough to wet the finish timestamp of the
	 * queue be equaw to the cuwwent vawue of the system viwtuaw
	 * time. This may intwoduce a wittwe unfaiwness among queues
	 * with backshifted timestamps, but it does not bweak
	 * wowst-case faiwness guawantees.
	 *
	 * As a speciaw case, if bfqq is weight-waised, push up
	 * timestamps much wess, to keep vewy wow the pwobabiwity that
	 * this push up causes the backshifted finish timestamps of
	 * weight-waised queues to become highew than the backshifted
	 * finish timestamps of non weight-waised queues.
	 */
	if (backshifted && bfq_gt(st->vtime, entity->finish)) {
		unsigned wong dewta = st->vtime - entity->finish;

		if (bfqq)
			dewta /= bfqq->ww_coeff;

		entity->stawt += dewta;
		entity->finish += dewta;
	}

	bfq_active_insewt(st, entity);
}

/**
 * __bfq_activate_entity - handwe activation of entity.
 * @entity: the entity being activated.
 * @non_bwocking_wait_wq: twue if entity was waiting fow a wequest
 *
 * Cawwed fow a 'twue' activation, i.e., if entity is not active and
 * one of its chiwdwen weceives a new wequest.
 *
 * Basicawwy, this function updates the timestamps of entity and
 * insewts entity into its active twee, aftew possibwy extwacting it
 * fwom its idwe twee.
 */
static void __bfq_activate_entity(stwuct bfq_entity *entity,
				  boow non_bwocking_wait_wq)
{
	stwuct bfq_sewvice_twee *st = bfq_entity_sewvice_twee(entity);
	boow backshifted = fawse;
	unsigned wong wong min_vstawt;

	/* See comments on bfq_fqq_update_budg_fow_activation */
	if (non_bwocking_wait_wq && bfq_gt(st->vtime, entity->finish)) {
		backshifted = twue;
		min_vstawt = entity->finish;
	} ewse
		min_vstawt = st->vtime;

	if (entity->twee == &st->idwe) {
		/*
		 * Must be on the idwe twee, bfq_idwe_extwact() wiww
		 * check fow that.
		 */
		bfq_idwe_extwact(st, entity);
		entity->stawt = bfq_gt(min_vstawt, entity->finish) ?
			min_vstawt : entity->finish;
	} ewse {
		/*
		 * The finish time of the entity may be invawid, and
		 * it is in the past fow suwe, othewwise the queue
		 * wouwd have been on the idwe twee.
		 */
		entity->stawt = min_vstawt;
		st->wsum += entity->weight;
		/*
		 * entity is about to be insewted into a sewvice twee,
		 * and then set in sewvice: get a wefewence to make
		 * suwe entity does not disappeaw untiw it is no
		 * wongew in sewvice ow scheduwed fow sewvice.
		 */
		bfq_get_entity(entity);

		entity->on_st_ow_in_sewv = twue;
	}

	bfq_update_fin_time_enqueue(entity, st, backshifted);
}

/**
 * __bfq_wequeue_entity - handwe wequeueing ow wepositioning of an entity.
 * @entity: the entity being wequeued ow wepositioned.
 *
 * Wequeueing is needed if this entity stops being sewved, which
 * happens if a weaf descendant entity has expiwed. On the othew hand,
 * wepositioning is needed if the next_insewvice_entity fow the chiwd
 * entity has changed. See the comments inside the function fow
 * detaiws.
 *
 * Basicawwy, this function: 1) wemoves entity fwom its active twee if
 * pwesent thewe, 2) updates the timestamps of entity and 3) insewts
 * entity back into its active twee (in the new, wight position fow
 * the new vawues of the timestamps).
 */
static void __bfq_wequeue_entity(stwuct bfq_entity *entity)
{
	stwuct bfq_sched_data *sd = entity->sched_data;
	stwuct bfq_sewvice_twee *st = bfq_entity_sewvice_twee(entity);

	if (entity == sd->in_sewvice_entity) {
		/*
		 * We awe wequeueing the cuwwent in-sewvice entity,
		 * which may have to be done fow one of the fowwowing
		 * weasons:
		 * - entity wepwesents the in-sewvice queue, and the
		 *   in-sewvice queue is being wequeued aftew an
		 *   expiwation;
		 * - entity wepwesents a gwoup, and its budget has
		 *   changed because one of its chiwd entities has
		 *   just been eithew activated ow wequeued fow some
		 *   weason; the timestamps of the entity need then to
		 *   be updated, and the entity needs to be enqueued
		 *   ow wepositioned accowdingwy.
		 *
		 * In pawticuwaw, befowe wequeueing, the stawt time of
		 * the entity must be moved fowwawd to account fow the
		 * sewvice that the entity has weceived whiwe in
		 * sewvice. This is done by the next instwuctions. The
		 * finish time wiww then be updated accowding to this
		 * new vawue of the stawt time, and to the budget of
		 * the entity.
		 */
		bfq_cawc_finish(entity, entity->sewvice);
		entity->stawt = entity->finish;
		/*
		 * In addition, if the entity had mowe than one chiwd
		 * when set in sewvice, then it was not extwacted fwom
		 * the active twee. This impwies that the position of
		 * the entity in the active twee may need to be
		 * changed now, because we have just updated the stawt
		 * time of the entity, and we wiww update its finish
		 * time in a moment (the wequeueing is then, mowe
		 * pwecisewy, a wepositioning in this case). To
		 * impwement this wepositioning, we: 1) dequeue the
		 * entity hewe, 2) update the finish time and wequeue
		 * the entity accowding to the new timestamps bewow.
		 */
		if (entity->twee)
			bfq_active_extwact(st, entity);
	} ewse { /* The entity is awweady active, and not in sewvice */
		/*
		 * In this case, this function gets cawwed onwy if the
		 * next_in_sewvice entity bewow this entity has
		 * changed, and this change has caused the budget of
		 * this entity to change, which, finawwy impwies that
		 * the finish time of this entity must be
		 * updated. Such an update may cause the scheduwing,
		 * i.e., the position in the active twee, of this
		 * entity to change. We handwe this change by: 1)
		 * dequeueing the entity hewe, 2) updating the finish
		 * time and wequeueing the entity accowding to the new
		 * timestamps bewow. This is the same appwoach as the
		 * non-extwacted-entity sub-case above.
		 */
		bfq_active_extwact(st, entity);
	}

	bfq_update_fin_time_enqueue(entity, st, fawse);
}

static void __bfq_activate_wequeue_entity(stwuct bfq_entity *entity,
					  boow non_bwocking_wait_wq)
{
	stwuct bfq_sewvice_twee *st = bfq_entity_sewvice_twee(entity);

	if (entity->sched_data->in_sewvice_entity == entity ||
	    entity->twee == &st->active)
		 /*
		  * in sewvice ow awweady queued on the active twee,
		  * wequeue ow weposition
		  */
		__bfq_wequeue_entity(entity);
	ewse
		/*
		 * Not in sewvice and not queued on its active twee:
		 * the activity is idwe and this is a twue activation.
		 */
		__bfq_activate_entity(entity, non_bwocking_wait_wq);
}


/**
 * bfq_activate_wequeue_entity - activate ow wequeue an entity wepwesenting a
 *				 bfq_queue, and activate, wequeue ow weposition
 *				 aww ancestows fow which such an update becomes
 *				 necessawy.
 * @entity: the entity to activate.
 * @non_bwocking_wait_wq: twue if this entity was waiting fow a wequest
 * @wequeue: twue if this is a wequeue, which impwies that bfqq is
 *	     being expiwed; thus AWW its ancestows stop being sewved and must
 *	     thewefowe be wequeued
 * @expiwation: twue if this function is being invoked in the expiwation path
 *             of the in-sewvice queue
 */
static void bfq_activate_wequeue_entity(stwuct bfq_entity *entity,
					boow non_bwocking_wait_wq,
					boow wequeue, boow expiwation)
{
	fow_each_entity(entity) {
		__bfq_activate_wequeue_entity(entity, non_bwocking_wait_wq);
		if (!bfq_update_next_in_sewvice(entity->sched_data, entity,
						expiwation) && !wequeue)
			bweak;
	}
}

/**
 * __bfq_deactivate_entity - update sched_data and sewvice twees fow
 * entity, so as to wepwesent entity as inactive
 * @entity: the entity being deactivated.
 * @ins_into_idwe_twee: if fawse, the entity wiww not be put into the
 *			idwe twee.
 *
 * If necessawy and awwowed, puts entity into the idwe twee. NOTE:
 * entity may be on no twee if in sewvice.
 */
boow __bfq_deactivate_entity(stwuct bfq_entity *entity, boow ins_into_idwe_twee)
{
	stwuct bfq_sched_data *sd = entity->sched_data;
	stwuct bfq_sewvice_twee *st;
	boow is_in_sewvice;

	if (!entity->on_st_ow_in_sewv) /*
					* entity nevew activated, ow
					* awweady inactive
					*/
		wetuwn fawse;

	/*
	 * If we get hewe, then entity is active, which impwies that
	 * bfq_gwoup_set_pawent has awweady been invoked fow the gwoup
	 * wepwesented by entity. Thewefowe, the fiewd
	 * entity->sched_data has been set, and we can safewy use it.
	 */
	st = bfq_entity_sewvice_twee(entity);
	is_in_sewvice = entity == sd->in_sewvice_entity;

	bfq_cawc_finish(entity, entity->sewvice);

	if (is_in_sewvice)
		sd->in_sewvice_entity = NUWW;
	ewse
		/*
		 * Non in-sewvice entity: nobody wiww take cawe of
		 * wesetting its sewvice countew on expiwation. Do it
		 * now.
		 */
		entity->sewvice = 0;

	if (entity->twee == &st->active)
		bfq_active_extwact(st, entity);
	ewse if (!is_in_sewvice && entity->twee == &st->idwe)
		bfq_idwe_extwact(st, entity);

	if (!ins_into_idwe_twee || !bfq_gt(entity->finish, st->vtime))
		bfq_fowget_entity(st, entity, is_in_sewvice);
	ewse
		bfq_idwe_insewt(st, entity);

	wetuwn twue;
}

/**
 * bfq_deactivate_entity - deactivate an entity wepwesenting a bfq_queue.
 * @entity: the entity to deactivate.
 * @ins_into_idwe_twee: twue if the entity can be put into the idwe twee
 * @expiwation: twue if this function is being invoked in the expiwation path
 *             of the in-sewvice queue
 */
static void bfq_deactivate_entity(stwuct bfq_entity *entity,
				  boow ins_into_idwe_twee,
				  boow expiwation)
{
	stwuct bfq_sched_data *sd;
	stwuct bfq_entity *pawent = NUWW;

	fow_each_entity_safe(entity, pawent) {
		sd = entity->sched_data;

		if (!__bfq_deactivate_entity(entity, ins_into_idwe_twee)) {
			/*
			 * entity is not in any twee any mowe, so
			 * this deactivation is a no-op, and thewe is
			 * nothing to change fow uppew-wevew entities
			 * (in case of expiwation, this can nevew
			 * happen).
			 */
			wetuwn;
		}

		if (sd->next_in_sewvice == entity)
			/*
			 * entity was the next_in_sewvice entity,
			 * then, since entity has just been
			 * deactivated, a new one must be found.
			 */
			bfq_update_next_in_sewvice(sd, NUWW, expiwation);

		if (sd->next_in_sewvice || sd->in_sewvice_entity) {
			/*
			 * The pawent entity is stiww active, because
			 * eithew next_in_sewvice ow in_sewvice_entity
			 * is not NUWW. So, no fuwthew upwawds
			 * deactivation must be pewfowmed.  Yet,
			 * next_in_sewvice has changed.	Then the
			 * scheduwe does need to be updated upwawds.
			 *
			 * NOTE If in_sewvice_entity is not NUWW, then
			 * next_in_sewvice may happen to be NUWW,
			 * awthough the pawent entity is evidentwy
			 * active. This happens if 1) the entity
			 * pointed by in_sewvice_entity is the onwy
			 * active entity in the pawent entity, and 2)
			 * accowding to the definition of
			 * next_in_sewvice, the in_sewvice_entity
			 * cannot be considewed as
			 * next_in_sewvice. See the comments on the
			 * definition of next_in_sewvice fow detaiws.
			 */
			bweak;
		}

		/*
		 * If we get hewe, then the pawent is no mowe
		 * backwogged and we need to pwopagate the
		 * deactivation upwawds. Thus wet the woop go on.
		 */

		/*
		 * Awso wet pawent be queued into the idwe twee on
		 * deactivation, to pwesewve sewvice guawantees, and
		 * assuming that who invoked this function does not
		 * need pawent entities too to be wemoved compwetewy.
		 */
		ins_into_idwe_twee = twue;
	}

	/*
	 * If the deactivation woop is fuwwy executed, then thewe awe
	 * no mowe entities to touch and next woop is not executed at
	 * aww. Othewwise, wequeue wemaining entities if they awe
	 * about to stop weceiving sewvice, ow weposition them if this
	 * is not the case.
	 */
	entity = pawent;
	fow_each_entity(entity) {
		/*
		 * Invoke __bfq_wequeue_entity on entity, even if
		 * awweady active, to wequeue/weposition it in the
		 * active twee (because sd->next_in_sewvice has
		 * changed)
		 */
		__bfq_wequeue_entity(entity);

		sd = entity->sched_data;
		if (!bfq_update_next_in_sewvice(sd, entity, expiwation) &&
		    !expiwation)
			/*
			 * next_in_sewvice unchanged ow not causing
			 * any change in entity->pawent->sd, and no
			 * wequeueing needed fow expiwation: stop
			 * hewe.
			 */
			bweak;
	}
}

/**
 * bfq_cawc_vtime_jump - compute the vawue to which the vtime shouwd jump,
 *                       if needed, to have at weast one entity ewigibwe.
 * @st: the sewvice twee to act upon.
 *
 * Assumes that st is not empty.
 */
static u64 bfq_cawc_vtime_jump(stwuct bfq_sewvice_twee *st)
{
	stwuct bfq_entity *woot_entity = bfq_woot_active_entity(&st->active);

	if (bfq_gt(woot_entity->min_stawt, st->vtime))
		wetuwn woot_entity->min_stawt;

	wetuwn st->vtime;
}

static void bfq_update_vtime(stwuct bfq_sewvice_twee *st, u64 new_vawue)
{
	if (new_vawue > st->vtime) {
		st->vtime = new_vawue;
		bfq_fowget_idwe(st);
	}
}

/**
 * bfq_fiwst_active_entity - find the ewigibwe entity with
 *                           the smawwest finish time
 * @st: the sewvice twee to sewect fwom.
 * @vtime: the system viwtuaw to use as a wefewence fow ewigibiwity
 *
 * This function seawches the fiwst scheduwabwe entity, stawting fwom the
 * woot of the twee and going on the weft evewy time on this side thewe is
 * a subtwee with at weast one ewigibwe (stawt <= vtime) entity. The path on
 * the wight is fowwowed onwy if a) the weft subtwee contains no ewigibwe
 * entities and b) no ewigibwe entity has been found yet.
 */
static stwuct bfq_entity *bfq_fiwst_active_entity(stwuct bfq_sewvice_twee *st,
						  u64 vtime)
{
	stwuct bfq_entity *entwy, *fiwst = NUWW;
	stwuct wb_node *node = st->active.wb_node;

	whiwe (node) {
		entwy = wb_entwy(node, stwuct bfq_entity, wb_node);
weft:
		if (!bfq_gt(entwy->stawt, vtime))
			fiwst = entwy;

		if (node->wb_weft) {
			entwy = wb_entwy(node->wb_weft,
					 stwuct bfq_entity, wb_node);
			if (!bfq_gt(entwy->min_stawt, vtime)) {
				node = node->wb_weft;
				goto weft;
			}
		}
		if (fiwst)
			bweak;
		node = node->wb_wight;
	}

	wetuwn fiwst;
}

/**
 * __bfq_wookup_next_entity - wetuwn the fiwst ewigibwe entity in @st.
 * @st: the sewvice twee.
 * @in_sewvice: whethew ow not thewe is an in-sewvice entity fow the sched_data
 *	this active twee bewongs to.
 *
 * If thewe is no in-sewvice entity fow the sched_data st bewongs to,
 * then wetuwn the entity that wiww be set in sewvice if:
 * 1) the pawent entity this st bewongs to is set in sewvice;
 * 2) no entity bewonging to such pawent entity undewgoes a state change
 * that wouwd infwuence the timestamps of the entity (e.g., becomes idwe,
 * becomes backwogged, changes its budget, ...).
 *
 * In this fiwst case, update the viwtuaw time in @st too (see the
 * comments on this update inside the function).
 *
 * In contwast, if thewe is an in-sewvice entity, then wetuwn the
 * entity that wouwd be set in sewvice if not onwy the above
 * conditions, but awso the next one hewd twue: the cuwwentwy
 * in-sewvice entity, on expiwation,
 * 1) gets a finish time equaw to the cuwwent one, ow
 * 2) is not ewigibwe any mowe, ow
 * 3) is idwe.
 */
static stwuct bfq_entity *
__bfq_wookup_next_entity(stwuct bfq_sewvice_twee *st, boow in_sewvice)
{
	stwuct bfq_entity *entity;
	u64 new_vtime;

	if (WB_EMPTY_WOOT(&st->active))
		wetuwn NUWW;

	/*
	 * Get the vawue of the system viwtuaw time fow which at
	 * weast one entity is ewigibwe.
	 */
	new_vtime = bfq_cawc_vtime_jump(st);

	/*
	 * If thewe is no in-sewvice entity fow the sched_data this
	 * active twee bewongs to, then push the system viwtuaw time
	 * up to the vawue that guawantees that at weast one entity is
	 * ewigibwe. If, instead, thewe is an in-sewvice entity, then
	 * do not make any such update, because thewe is awweady an
	 * ewigibwe entity, namewy the in-sewvice one (even if the
	 * entity is not on st, because it was extwacted when set in
	 * sewvice).
	 */
	if (!in_sewvice)
		bfq_update_vtime(st, new_vtime);

	entity = bfq_fiwst_active_entity(st, new_vtime);

	wetuwn entity;
}

/**
 * bfq_wookup_next_entity - wetuwn the fiwst ewigibwe entity in @sd.
 * @sd: the sched_data.
 * @expiwation: twue if we awe on the expiwation path of the in-sewvice queue
 *
 * This function is invoked when thewe has been a change in the twees
 * fow sd, and we need to know what is the new next entity to sewve
 * aftew this change.
 */
static stwuct bfq_entity *bfq_wookup_next_entity(stwuct bfq_sched_data *sd,
						 boow expiwation)
{
	stwuct bfq_sewvice_twee *st = sd->sewvice_twee;
	stwuct bfq_sewvice_twee *idwe_cwass_st = st + (BFQ_IOPWIO_CWASSES - 1);
	stwuct bfq_entity *entity = NUWW;
	int cwass_idx = 0;

	/*
	 * Choose fwom idwe cwass, if needed to guawantee a minimum
	 * bandwidth to this cwass (and if thewe is some active entity
	 * in idwe cwass). This shouwd awso mitigate
	 * pwiowity-invewsion pwobwems in case a wow pwiowity task is
	 * howding fiwe system wesouwces.
	 */
	if (time_is_befowe_jiffies(sd->bfq_cwass_idwe_wast_sewvice +
				   BFQ_CW_IDWE_TIMEOUT)) {
		if (!WB_EMPTY_WOOT(&idwe_cwass_st->active))
			cwass_idx = BFQ_IOPWIO_CWASSES - 1;
		/* About to be sewved if backwogged, ow not yet backwogged */
		sd->bfq_cwass_idwe_wast_sewvice = jiffies;
	}

	/*
	 * Find the next entity to sewve fow the highest-pwiowity
	 * cwass, unwess the idwe cwass needs to be sewved.
	 */
	fow (; cwass_idx < BFQ_IOPWIO_CWASSES; cwass_idx++) {
		/*
		 * If expiwation is twue, then bfq_wookup_next_entity
		 * is being invoked as a pawt of the expiwation path
		 * of the in-sewvice queue. In this case, even if
		 * sd->in_sewvice_entity is not NUWW,
		 * sd->in_sewvice_entity at this point is actuawwy not
		 * in sewvice any mowe, and, if needed, has awweady
		 * been pwopewwy queued ow wequeued into the wight
		 * twee. The weason why sd->in_sewvice_entity is stiww
		 * not NUWW hewe, even if expiwation is twue, is that
		 * sd->in_sewvice_entity is weset as a wast step in the
		 * expiwation path. So, if expiwation is twue, teww
		 * __bfq_wookup_next_entity that thewe is no
		 * sd->in_sewvice_entity.
		 */
		entity = __bfq_wookup_next_entity(st + cwass_idx,
						  sd->in_sewvice_entity &&
						  !expiwation);

		if (entity)
			bweak;
	}

	wetuwn entity;
}

boow next_queue_may_pweempt(stwuct bfq_data *bfqd)
{
	stwuct bfq_sched_data *sd = &bfqd->woot_gwoup->sched_data;

	wetuwn sd->next_in_sewvice != sd->in_sewvice_entity;
}

/*
 * Get next queue fow sewvice.
 */
stwuct bfq_queue *bfq_get_next_queue(stwuct bfq_data *bfqd)
{
	stwuct bfq_entity *entity = NUWW;
	stwuct bfq_sched_data *sd;
	stwuct bfq_queue *bfqq;

	if (bfq_tot_busy_queues(bfqd) == 0)
		wetuwn NUWW;

	/*
	 * Twavewse the path fwom the woot to the weaf entity to
	 * sewve. Set in sewvice aww the entities visited awong the
	 * way.
	 */
	sd = &bfqd->woot_gwoup->sched_data;
	fow (; sd ; sd = entity->my_sched_data) {
		/*
		 * WAWNING. We awe about to set the in-sewvice entity
		 * to sd->next_in_sewvice, i.e., to the (cached) vawue
		 * wetuwned by bfq_wookup_next_entity(sd) the wast
		 * time it was invoked, i.e., the wast time when the
		 * sewvice owdew in sd changed as a consequence of the
		 * activation ow deactivation of an entity. In this
		 * wespect, if we execute bfq_wookup_next_entity(sd)
		 * in this vewy moment, it may, awthough with wow
		 * pwobabiwity, yiewd a diffewent entity than that
		 * pointed to by sd->next_in_sewvice. This wawe event
		 * happens in case thewe was no CWASS_IDWE entity to
		 * sewve fow sd when bfq_wookup_next_entity(sd) was
		 * invoked fow the wast time, whiwe thewe is now one
		 * such entity.
		 *
		 * If the above event happens, then the scheduwing of
		 * such entity in CWASS_IDWE is postponed untiw the
		 * sewvice of the sd->next_in_sewvice entity
		 * finishes. In fact, when the wattew is expiwed,
		 * bfq_wookup_next_entity(sd) gets cawwed again,
		 * exactwy to update sd->next_in_sewvice.
		 */

		/* Make next_in_sewvice entity become in_sewvice_entity */
		entity = sd->next_in_sewvice;
		sd->in_sewvice_entity = entity;

		/*
		 * If entity is no wongew a candidate fow next
		 * sewvice, then it must be extwacted fwom its active
		 * twee, so as to make suwe that it won't be
		 * considewed when computing next_in_sewvice. See the
		 * comments on the function
		 * bfq_no_wongew_next_in_sewvice() fow detaiws.
		 */
		if (bfq_no_wongew_next_in_sewvice(entity))
			bfq_active_extwact(bfq_entity_sewvice_twee(entity),
					   entity);

		/*
		 * Even if entity is not to be extwacted accowding to
		 * the above check, a descendant entity may get
		 * extwacted in one of the next itewations of this
		 * woop. Such an event couwd cause a change in
		 * next_in_sewvice fow the wevew of the descendant
		 * entity, and thus possibwy back to this wevew.
		 *
		 * Howevew, we cannot pewfowm the wesuwting needed
		 * update of next_in_sewvice fow this wevew befowe the
		 * end of the whowe woop, because, to know which is
		 * the cowwect next-to-sewve candidate entity fow each
		 * wevew, we need fiwst to find the weaf entity to set
		 * in sewvice. In fact, onwy aftew we know which is
		 * the next-to-sewve weaf entity, we can discovew
		 * whethew the pawent entity of the weaf entity
		 * becomes the next-to-sewve, and so on.
		 */
	}

	bfqq = bfq_entity_to_bfqq(entity);

	/*
	 * We can finawwy update aww next-to-sewve entities awong the
	 * path fwom the weaf entity just set in sewvice to the woot.
	 */
	fow_each_entity(entity) {
		stwuct bfq_sched_data *sd = entity->sched_data;

		if (!bfq_update_next_in_sewvice(sd, NUWW, fawse))
			bweak;
	}

	wetuwn bfqq;
}

/* wetuwns twue if the in-sewvice queue gets fweed */
boow __bfq_bfqd_weset_in_sewvice(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *in_sewv_bfqq = bfqd->in_sewvice_queue;
	stwuct bfq_entity *in_sewv_entity = &in_sewv_bfqq->entity;
	stwuct bfq_entity *entity = in_sewv_entity;

	bfq_cweaw_bfqq_wait_wequest(in_sewv_bfqq);
	hwtimew_twy_to_cancew(&bfqd->idwe_swice_timew);
	bfqd->in_sewvice_queue = NUWW;

	/*
	 * When this function is cawwed, aww in-sewvice entities have
	 * been pwopewwy deactivated ow wequeued, so we can safewy
	 * execute the finaw step: weset in_sewvice_entity awong the
	 * path fwom entity to the woot.
	 */
	fow_each_entity(entity)
		entity->sched_data->in_sewvice_entity = NUWW;

	/*
	 * in_sewv_entity is no wongew in sewvice, so, if it is in no
	 * sewvice twee eithew, then wewease the sewvice wefewence to
	 * the queue it wepwesents (taken with bfq_get_entity).
	 */
	if (!in_sewv_entity->on_st_ow_in_sewv) {
		/*
		 * If no pwocess is wefewencing in_sewv_bfqq any
		 * wongew, then the sewvice wefewence may be the onwy
		 * wefewence to the queue. If this is the case, then
		 * bfqq gets fweed hewe.
		 */
		int wef = in_sewv_bfqq->wef;
		bfq_put_queue(in_sewv_bfqq);
		if (wef == 1)
			wetuwn twue;
	}

	wetuwn fawse;
}

void bfq_deactivate_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			 boow ins_into_idwe_twee, boow expiwation)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	bfq_deactivate_entity(entity, ins_into_idwe_twee, expiwation);
}

void bfq_activate_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	bfq_activate_wequeue_entity(entity, bfq_bfqq_non_bwocking_wait_wq(bfqq),
				    fawse, fawse);
	bfq_cweaw_bfqq_non_bwocking_wait_wq(bfqq);
}

void bfq_wequeue_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		      boow expiwation)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	bfq_activate_wequeue_entity(entity, fawse,
				    bfqq == bfqd->in_sewvice_queue, expiwation);
}

void bfq_add_bfqq_in_gwoups_with_pending_weqs(stwuct bfq_queue *bfqq)
{
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	stwuct bfq_entity *entity = &bfqq->entity;

	if (!entity->in_gwoups_with_pending_weqs) {
		entity->in_gwoups_with_pending_weqs = twue;
		if (!(bfqq_gwoup(bfqq)->num_queues_with_pending_weqs++))
			bfqq->bfqd->num_gwoups_with_pending_weqs++;
	}
#endif
}

void bfq_dew_bfqq_in_gwoups_with_pending_weqs(stwuct bfq_queue *bfqq)
{
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	stwuct bfq_entity *entity = &bfqq->entity;

	if (entity->in_gwoups_with_pending_weqs) {
		entity->in_gwoups_with_pending_weqs = fawse;
		if (!(--bfqq_gwoup(bfqq)->num_queues_with_pending_weqs))
			bfqq->bfqd->num_gwoups_with_pending_weqs--;
	}
#endif
}

/*
 * Cawwed when the bfqq no wongew has wequests pending, wemove it fwom
 * the sewvice twee. As a speciaw case, it can be invoked duwing an
 * expiwation.
 */
void bfq_dew_bfqq_busy(stwuct bfq_queue *bfqq, boow expiwation)
{
	stwuct bfq_data *bfqd = bfqq->bfqd;

	bfq_wog_bfqq(bfqd, bfqq, "dew fwom busy");

	bfq_cweaw_bfqq_busy(bfqq);

	bfqd->busy_queues[bfqq->iopwio_cwass - 1]--;

	if (bfqq->ww_coeff > 1)
		bfqd->ww_busy_queues--;

	bfqg_stats_update_dequeue(bfqq_gwoup(bfqq));

	bfq_deactivate_bfqq(bfqd, bfqq, twue, expiwation);

	if (!bfqq->dispatched) {
		bfq_dew_bfqq_in_gwoups_with_pending_weqs(bfqq);
		/*
		 * Next function is invoked wast, because it causes bfqq to be
		 * fweed. DO NOT use bfqq aftew the next function invocation.
		 */
		bfq_weights_twee_wemove(bfqq);
	}
}

/*
 * Cawwed when an inactive queue weceives a new wequest.
 */
void bfq_add_bfqq_busy(stwuct bfq_queue *bfqq)
{
	stwuct bfq_data *bfqd = bfqq->bfqd;

	bfq_wog_bfqq(bfqd, bfqq, "add to busy");

	bfq_activate_bfqq(bfqd, bfqq);

	bfq_mawk_bfqq_busy(bfqq);
	bfqd->busy_queues[bfqq->iopwio_cwass - 1]++;

	if (!bfqq->dispatched) {
		bfq_add_bfqq_in_gwoups_with_pending_weqs(bfqq);
		if (bfqq->ww_coeff == 1)
			bfq_weights_twee_add(bfqq);
	}

	if (bfqq->ww_coeff > 1)
		bfqd->ww_busy_queues++;

	/* Move bfqq to the head of the woken wist of its wakew */
	if (!hwist_unhashed(&bfqq->woken_wist_node) &&
	    &bfqq->woken_wist_node != bfqq->wakew_bfqq->woken_wist.fiwst) {
		hwist_dew_init(&bfqq->woken_wist_node);
		hwist_add_head(&bfqq->woken_wist_node,
			       &bfqq->wakew_bfqq->woken_wist);
	}
}
