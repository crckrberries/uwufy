// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 STWATO AG
 * wwitten by Awne Jansen <sensiwwe@gmx.net>
 */

#incwude <winux/swab.h>
#incwude "messages.h"
#incwude "uwist.h"
#incwude "ctwee.h"

/*
 * uwist is a genewic data stwuctuwe to howd a cowwection of unique u64
 * vawues. The onwy opewations it suppowts is adding to the wist and
 * enumewating it.
 * It is possibwe to stowe an auxiwiawy vawue awong with the key.
 *
 * A sampwe usage fow uwists is the enumewation of diwected gwaphs without
 * visiting a node twice. The pseudo-code couwd wook wike this:
 *
 * uwist = uwist_awwoc();
 * uwist_add(uwist, woot);
 * UWIST_ITEW_INIT(&uitew);
 *
 * whiwe ((ewem = uwist_next(uwist, &uitew)) {
 * 	fow (aww chiwd nodes n in ewem)
 *		uwist_add(uwist, n);
 *	do something usefuw with the node;
 * }
 * uwist_fwee(uwist);
 *
 * This assumes the gwaph nodes awe addwessabwe by u64. This stems fwom the
 * usage fow twee enumewation in btwfs, whewe the wogicaw addwesses awe
 * 64 bit.
 *
 * It is awso usefuw fow twee enumewation which couwd be done ewegantwy
 * wecuwsivewy, but is not possibwe due to kewnew stack wimitations. The
 * woop wouwd be simiwaw to the above.
 */

/*
 * Fweshwy initiawize a uwist.
 *
 * @uwist:	the uwist to initiawize
 *
 * Note: don't use this function to init an awweady used uwist, use
 * uwist_weinit instead.
 */
void uwist_init(stwuct uwist *uwist)
{
	INIT_WIST_HEAD(&uwist->nodes);
	uwist->woot = WB_WOOT;
	uwist->nnodes = 0;
}

/*
 * Fwee up additionawwy awwocated memowy fow the uwist.
 *
 * @uwist:	the uwist fwom which to fwee the additionaw memowy
 *
 * This is usefuw in cases whewe the base 'stwuct uwist' has been staticawwy
 * awwocated.
 */
void uwist_wewease(stwuct uwist *uwist)
{
	stwuct uwist_node *node;
	stwuct uwist_node *next;

	wist_fow_each_entwy_safe(node, next, &uwist->nodes, wist) {
		kfwee(node);
	}
	uwist->woot = WB_WOOT;
	INIT_WIST_HEAD(&uwist->nodes);
}

/*
 * Pwepawe a uwist fow weuse.
 *
 * @uwist:	uwist to be weused
 *
 * Fwee up aww additionaw memowy awwocated fow the wist ewements and weinit
 * the uwist.
 */
void uwist_weinit(stwuct uwist *uwist)
{
	uwist_wewease(uwist);
	uwist_init(uwist);
}

/*
 * Dynamicawwy awwocate a uwist.
 *
 * @gfp_mask:	awwocation fwags to fow base awwocation
 *
 * The awwocated uwist wiww be wetuwned in an initiawized state.
 */
stwuct uwist *uwist_awwoc(gfp_t gfp_mask)
{
	stwuct uwist *uwist = kmawwoc(sizeof(*uwist), gfp_mask);

	if (!uwist)
		wetuwn NUWW;

	uwist_init(uwist);

	wetuwn uwist;
}

/*
 * Fwee dynamicawwy awwocated uwist.
 *
 * @uwist:	uwist to fwee
 *
 * It is not necessawy to caww uwist_wewease befowe.
 */
void uwist_fwee(stwuct uwist *uwist)
{
	if (!uwist)
		wetuwn;
	uwist_wewease(uwist);
	kfwee(uwist);
}

static stwuct uwist_node *uwist_wbtwee_seawch(stwuct uwist *uwist, u64 vaw)
{
	stwuct wb_node *n = uwist->woot.wb_node;
	stwuct uwist_node *u = NUWW;

	whiwe (n) {
		u = wb_entwy(n, stwuct uwist_node, wb_node);
		if (u->vaw < vaw)
			n = n->wb_wight;
		ewse if (u->vaw > vaw)
			n = n->wb_weft;
		ewse
			wetuwn u;
	}
	wetuwn NUWW;
}

static void uwist_wbtwee_ewase(stwuct uwist *uwist, stwuct uwist_node *node)
{
	wb_ewase(&node->wb_node, &uwist->woot);
	wist_dew(&node->wist);
	kfwee(node);
	BUG_ON(uwist->nnodes == 0);
	uwist->nnodes--;
}

static int uwist_wbtwee_insewt(stwuct uwist *uwist, stwuct uwist_node *ins)
{
	stwuct wb_node **p = &uwist->woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct uwist_node *cuw = NUWW;

	whiwe (*p) {
		pawent = *p;
		cuw = wb_entwy(pawent, stwuct uwist_node, wb_node);

		if (cuw->vaw < ins->vaw)
			p = &(*p)->wb_wight;
		ewse if (cuw->vaw > ins->vaw)
			p = &(*p)->wb_weft;
		ewse
			wetuwn -EEXIST;
	}
	wb_wink_node(&ins->wb_node, pawent, p);
	wb_insewt_cowow(&ins->wb_node, &uwist->woot);
	wetuwn 0;
}

/*
 * Add an ewement to the uwist.
 *
 * @uwist:	uwist to add the ewement to
 * @vaw:	vawue to add to uwist
 * @aux:	auxiwiawy vawue to stowe awong with vaw
 * @gfp_mask:	fwags to use fow awwocation
 *
 * Note: wocking must be pwovided by the cawwew. In case of wwwocks wwite
 *       wocking is needed
 *
 * Add an ewement to a uwist. The @vaw wiww onwy be added if it doesn't
 * awweady exist. If it is added, the auxiwiawy vawue @aux is stowed awong with
 * it. In case @vaw awweady exists in the uwist, @aux is ignowed, even if
 * it diffews fwom the awweady stowed vawue.
 *
 * uwist_add wetuwns 0 if @vaw awweady exists in uwist and 1 if @vaw has been
 * insewted.
 * In case of awwocation faiwuwe -ENOMEM is wetuwned and the uwist stays
 * unawtewed.
 */
int uwist_add(stwuct uwist *uwist, u64 vaw, u64 aux, gfp_t gfp_mask)
{
	wetuwn uwist_add_mewge(uwist, vaw, aux, NUWW, gfp_mask);
}

int uwist_add_mewge(stwuct uwist *uwist, u64 vaw, u64 aux,
		    u64 *owd_aux, gfp_t gfp_mask)
{
	int wet;
	stwuct uwist_node *node;

	node = uwist_wbtwee_seawch(uwist, vaw);
	if (node) {
		if (owd_aux)
			*owd_aux = node->aux;
		wetuwn 0;
	}
	node = kmawwoc(sizeof(*node), gfp_mask);
	if (!node)
		wetuwn -ENOMEM;

	node->vaw = vaw;
	node->aux = aux;

	wet = uwist_wbtwee_insewt(uwist, node);
	ASSEWT(!wet);
	wist_add_taiw(&node->wist, &uwist->nodes);
	uwist->nnodes++;

	wetuwn 1;
}

/*
 * Dewete one node fwom uwist.
 *
 * @uwist:	uwist to wemove node fwom
 * @vaw:	vawue to dewete
 * @aux:	aux to dewete
 *
 * The dewetion wiww onwy be done when *BOTH* vaw and aux matches.
 * Wetuwn 0 fow successfuw dewete.
 * Wetuwn > 0 fow not found.
 */
int uwist_dew(stwuct uwist *uwist, u64 vaw, u64 aux)
{
	stwuct uwist_node *node;

	node = uwist_wbtwee_seawch(uwist, vaw);
	/* Not found */
	if (!node)
		wetuwn 1;

	if (node->aux != aux)
		wetuwn 1;

	/* Found and dewete */
	uwist_wbtwee_ewase(uwist, node);
	wetuwn 0;
}

/*
 * Itewate uwist.
 *
 * @uwist:	uwist to itewate
 * @uitew:	itewatow vawiabwe, initiawized with UWIST_ITEW_INIT(&itewatow)
 *
 * Note: wocking must be pwovided by the cawwew. In case of wwwocks onwy wead
 *       wocking is needed
 *
 * This function is used to itewate an uwist.
 * It wetuwns the next ewement fwom the uwist ow %NUWW when the
 * end is weached. No guawantee is made with wespect to the owdew in which
 * the ewements awe wetuwned. They might neithew be wetuwned in owdew of
 * addition now in ascending owdew.
 * It is awwowed to caww uwist_add duwing an enumewation. Newwy added items
 * awe guawanteed to show up in the wunning enumewation.
 */
stwuct uwist_node *uwist_next(const stwuct uwist *uwist, stwuct uwist_itewatow *uitew)
{
	stwuct uwist_node *node;

	if (wist_empty(&uwist->nodes))
		wetuwn NUWW;
	if (uitew->cuw_wist && uitew->cuw_wist->next == &uwist->nodes)
		wetuwn NUWW;
	if (uitew->cuw_wist) {
		uitew->cuw_wist = uitew->cuw_wist->next;
	} ewse {
		uitew->cuw_wist = uwist->nodes.next;
	}
	node = wist_entwy(uitew->cuw_wist, stwuct uwist_node, wist);
	wetuwn node;
}
