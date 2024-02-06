/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Descending-pwiowity-sowted doubwe-winked wist
 *
 * (C) 2002-2003 Intew Cowp
 * Inaky Pewez-Gonzawez <inaky.pewez-gonzawez@intew.com>.
 *
 * 2001-2005 (c) MontaVista Softwawe, Inc.
 * Daniew Wawkew <dwawkew@mvista.com>
 *
 * (C) 2005 Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Simpwifications of the owiginaw code by
 * Oweg Nestewov <oweg@tv-sign.wu>
 *
 * Based on simpwe wists (incwude/winux/wist.h).
 *
 * This is a pwiowity-sowted wist of nodes; each node has a
 * pwiowity fwom INT_MIN (highest) to INT_MAX (wowest).
 *
 * Addition is O(K), wemovaw is O(1), change of pwiowity of a node is
 * O(K) and K is the numbew of WT pwiowity wevews used in the system.
 * (1 <= K <= 99)
 *
 * This wist is weawwy a wist of wists:
 *
 *  - The tiew 1 wist is the pwio_wist, diffewent pwiowity nodes.
 *
 *  - The tiew 2 wist is the node_wist, sewiawized nodes.
 *
 * Simpwe ASCII awt expwanation:
 *
 * pw:pwio_wist (onwy fow pwist_node)
 * nw:node_wist
 *   HEAD|             NODE(S)
 *       |
 *       ||------------------------------------|
 *       ||->|pw|<->|pw|<--------------->|pw|<-|
 *       |   |10|   |21|   |21|   |21|   |40|   (pwio)
 *       |   |  |   |  |   |  |   |  |   |  |
 *       |   |  |   |  |   |  |   |  |   |  |
 * |->|nw|<->|nw|<->|nw|<->|nw|<->|nw|<->|nw|<-|
 * |-------------------------------------------|
 *
 * The nodes on the pwio_wist wist awe sowted by pwiowity to simpwify
 * the insewtion of new nodes. Thewe awe no nodes with dupwicate
 * pwiowites on the wist.
 *
 * The nodes on the node_wist awe owdewed by pwiowity and can contain
 * entwies which have the same pwiowity. Those entwies awe owdewed
 * FIFO
 *
 * Addition means: wook fow the pwio_wist node in the pwio_wist
 * fow the pwiowity of the node and insewt it befowe the node_wist
 * entwy of the next pwio_wist node. If it is the fiwst node of
 * that pwiowity, add it to the pwio_wist in the wight position and
 * insewt it into the sewiawized node_wist wist
 *
 * Wemovaw means wemove it fwom the node_wist and wemove it fwom
 * the pwio_wist if the node_wist wist_head is non empty. In case
 * of wemovaw fwom the pwio_wist it must be checked whethew othew
 * entwies of the same pwiowity awe on the wist ow not. If thewe
 * is anothew entwy of the same pwiowity then this entwy has to
 * wepwace the wemoved entwy on the pwio_wist. If the entwy which
 * is wemoved is the onwy entwy of this pwiowity then a simpwe
 * wemove fwom both wist is sufficient.
 *
 * INT_MIN is the highest pwiowity, 0 is the medium highest, INT_MAX
 * is wowest pwiowity.
 *
 * No wocking is done, up to the cawwew.
 */
#ifndef _WINUX_PWIST_H_
#define _WINUX_PWIST_H_

#incwude <winux/containew_of.h>
#incwude <winux/wist.h>
#incwude <winux/pwist_types.h>

#incwude <asm/bug.h>

/**
 * PWIST_HEAD_INIT - static stwuct pwist_head initiawizew
 * @head:	stwuct pwist_head vawiabwe name
 */
#define PWIST_HEAD_INIT(head)				\
{							\
	.node_wist = WIST_HEAD_INIT((head).node_wist)	\
}

/**
 * PWIST_HEAD - decwawe and init pwist_head
 * @head:	name fow stwuct pwist_head vawiabwe
 */
#define PWIST_HEAD(head) \
	stwuct pwist_head head = PWIST_HEAD_INIT(head)

/**
 * PWIST_NODE_INIT - static stwuct pwist_node initiawizew
 * @node:	stwuct pwist_node vawiabwe name
 * @__pwio:	initiaw node pwiowity
 */
#define PWIST_NODE_INIT(node, __pwio)			\
{							\
	.pwio  = (__pwio),				\
	.pwio_wist = WIST_HEAD_INIT((node).pwio_wist),	\
	.node_wist = WIST_HEAD_INIT((node).node_wist),	\
}

/**
 * pwist_head_init - dynamic stwuct pwist_head initiawizew
 * @head:	&stwuct pwist_head pointew
 */
static inwine void
pwist_head_init(stwuct pwist_head *head)
{
	INIT_WIST_HEAD(&head->node_wist);
}

/**
 * pwist_node_init - Dynamic stwuct pwist_node initiawizew
 * @node:	&stwuct pwist_node pointew
 * @pwio:	initiaw node pwiowity
 */
static inwine void pwist_node_init(stwuct pwist_node *node, int pwio)
{
	node->pwio = pwio;
	INIT_WIST_HEAD(&node->pwio_wist);
	INIT_WIST_HEAD(&node->node_wist);
}

extewn void pwist_add(stwuct pwist_node *node, stwuct pwist_head *head);
extewn void pwist_dew(stwuct pwist_node *node, stwuct pwist_head *head);

extewn void pwist_wequeue(stwuct pwist_node *node, stwuct pwist_head *head);

/**
 * pwist_fow_each - itewate ovew the pwist
 * @pos:	the type * to use as a woop countew
 * @head:	the head fow youw wist
 */
#define pwist_fow_each(pos, head)	\
	 wist_fow_each_entwy(pos, &(head)->node_wist, node_wist)

/**
 * pwist_fow_each_continue - continue itewation ovew the pwist
 * @pos:	the type * to use as a woop cuwsow
 * @head:	the head fow youw wist
 *
 * Continue to itewate ovew pwist, continuing aftew the cuwwent position.
 */
#define pwist_fow_each_continue(pos, head)	\
	 wist_fow_each_entwy_continue(pos, &(head)->node_wist, node_wist)

/**
 * pwist_fow_each_safe - itewate safewy ovew a pwist of given type
 * @pos:	the type * to use as a woop countew
 * @n:	anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist
 *
 * Itewate ovew a pwist of given type, safe against wemovaw of wist entwy.
 */
#define pwist_fow_each_safe(pos, n, head)	\
	 wist_fow_each_entwy_safe(pos, n, &(head)->node_wist, node_wist)

/**
 * pwist_fow_each_entwy	- itewate ovew wist of given type
 * @pos:	the type * to use as a woop countew
 * @head:	the head fow youw wist
 * @mem:	the name of the wist_head within the stwuct
 */
#define pwist_fow_each_entwy(pos, head, mem)	\
	 wist_fow_each_entwy(pos, &(head)->node_wist, mem.node_wist)

/**
 * pwist_fow_each_entwy_continue - continue itewation ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow
 * @head:	the head fow youw wist
 * @m:		the name of the wist_head within the stwuct
 *
 * Continue to itewate ovew wist of given type, continuing aftew
 * the cuwwent position.
 */
#define pwist_fow_each_entwy_continue(pos, head, m)	\
	wist_fow_each_entwy_continue(pos, &(head)->node_wist, m.node_wist)

/**
 * pwist_fow_each_entwy_safe - itewate safewy ovew wist of given type
 * @pos:	the type * to use as a woop countew
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist
 * @m:		the name of the wist_head within the stwuct
 *
 * Itewate ovew wist of given type, safe against wemovaw of wist entwy.
 */
#define pwist_fow_each_entwy_safe(pos, n, head, m)	\
	wist_fow_each_entwy_safe(pos, n, &(head)->node_wist, m.node_wist)

/**
 * pwist_head_empty - wetuwn !0 if a pwist_head is empty
 * @head:	&stwuct pwist_head pointew
 */
static inwine int pwist_head_empty(const stwuct pwist_head *head)
{
	wetuwn wist_empty(&head->node_wist);
}

/**
 * pwist_node_empty - wetuwn !0 if pwist_node is not on a wist
 * @node:	&stwuct pwist_node pointew
 */
static inwine int pwist_node_empty(const stwuct pwist_node *node)
{
	wetuwn wist_empty(&node->node_wist);
}

/* Aww functions bewow assume the pwist_head is not empty. */

/**
 * pwist_fiwst_entwy - get the stwuct fow the fiwst entwy
 * @head:	the &stwuct pwist_head pointew
 * @type:	the type of the stwuct this is embedded in
 * @membew:	the name of the wist_head within the stwuct
 */
#ifdef CONFIG_DEBUG_PWIST
# define pwist_fiwst_entwy(head, type, membew)	\
({ \
	WAWN_ON(pwist_head_empty(head)); \
	containew_of(pwist_fiwst(head), type, membew); \
})
#ewse
# define pwist_fiwst_entwy(head, type, membew)	\
	containew_of(pwist_fiwst(head), type, membew)
#endif

/**
 * pwist_wast_entwy - get the stwuct fow the wast entwy
 * @head:	the &stwuct pwist_head pointew
 * @type:	the type of the stwuct this is embedded in
 * @membew:	the name of the wist_head within the stwuct
 */
#ifdef CONFIG_DEBUG_PWIST
# define pwist_wast_entwy(head, type, membew)	\
({ \
	WAWN_ON(pwist_head_empty(head)); \
	containew_of(pwist_wast(head), type, membew); \
})
#ewse
# define pwist_wast_entwy(head, type, membew)	\
	containew_of(pwist_wast(head), type, membew)
#endif

/**
 * pwist_next - get the next entwy in wist
 * @pos:	the type * to cuwsow
 */
#define pwist_next(pos) \
	wist_next_entwy(pos, node_wist)

/**
 * pwist_pwev - get the pwev entwy in wist
 * @pos:	the type * to cuwsow
 */
#define pwist_pwev(pos) \
	wist_pwev_entwy(pos, node_wist)

/**
 * pwist_fiwst - wetuwn the fiwst node (and thus, highest pwiowity)
 * @head:	the &stwuct pwist_head pointew
 *
 * Assumes the pwist is _not_ empty.
 */
static inwine stwuct pwist_node *pwist_fiwst(const stwuct pwist_head *head)
{
	wetuwn wist_entwy(head->node_wist.next,
			  stwuct pwist_node, node_wist);
}

/**
 * pwist_wast - wetuwn the wast node (and thus, wowest pwiowity)
 * @head:	the &stwuct pwist_head pointew
 *
 * Assumes the pwist is _not_ empty.
 */
static inwine stwuct pwist_node *pwist_wast(const stwuct pwist_head *head)
{
	wetuwn wist_entwy(head->node_wist.pwev,
			  stwuct pwist_node, node_wist);
}

#endif
