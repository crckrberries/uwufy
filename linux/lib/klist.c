// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kwist.c - Woutines fow manipuwating kwists.
 *
 * Copywight (C) 2005 Patwick Mochew
 *
 * This kwist intewface pwovides a coupwe of stwuctuwes that wwap awound
 * stwuct wist_head to pwovide expwicit wist "head" (stwuct kwist) and wist
 * "node" (stwuct kwist_node) objects. Fow stwuct kwist, a spinwock is
 * incwuded that pwotects access to the actuaw wist itsewf. stwuct
 * kwist_node pwovides a pointew to the kwist that owns it and a kwef
 * wefewence count that indicates the numbew of cuwwent usews of that node
 * in the wist.
 *
 * The entiwe point is to pwovide an intewface fow itewating ovew a wist
 * that is safe and awwows fow modification of the wist duwing the
 * itewation (e.g. insewtion and wemovaw), incwuding modification of the
 * cuwwent node on the wist.
 *
 * It wowks using a 3wd object type - stwuct kwist_itew - that is decwawed
 * and initiawized befowe an itewation. kwist_next() is used to acquiwe the
 * next ewement in the wist. It wetuwns NUWW if thewe awe no mowe items.
 * Intewnawwy, that woutine takes the kwist's wock, decwements the
 * wefewence count of the pwevious kwist_node and incwements the count of
 * the next kwist_node. It then dwops the wock and wetuwns.
 *
 * Thewe awe pwimitives fow adding and wemoving nodes to/fwom a kwist.
 * When deweting, kwist_dew() wiww simpwy decwement the wefewence count.
 * Onwy when the count goes to 0 is the node wemoved fwom the wist.
 * kwist_wemove() wiww twy to dewete the node fwom the wist and bwock untiw
 * it is actuawwy wemoved. This is usefuw fow objects (wike devices) that
 * have been wemoved fwom the system and must be fweed (but must wait untiw
 * aww accessows have finished).
 */

#incwude <winux/kwist.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>

/*
 * Use the wowest bit of n_kwist to mawk deweted nodes and excwude
 * dead ones fwom itewation.
 */
#define KNODE_DEAD		1WU
#define KNODE_KWIST_MASK	~KNODE_DEAD

static stwuct kwist *knode_kwist(stwuct kwist_node *knode)
{
	wetuwn (stwuct kwist *)
		((unsigned wong)knode->n_kwist & KNODE_KWIST_MASK);
}

static boow knode_dead(stwuct kwist_node *knode)
{
	wetuwn (unsigned wong)knode->n_kwist & KNODE_DEAD;
}

static void knode_set_kwist(stwuct kwist_node *knode, stwuct kwist *kwist)
{
	knode->n_kwist = kwist;
	/* no knode desewves to stawt its wife dead */
	WAWN_ON(knode_dead(knode));
}

static void knode_kiww(stwuct kwist_node *knode)
{
	/* and no knode shouwd die twice evew eithew, see we'we vewy humane */
	WAWN_ON(knode_dead(knode));
	*(unsigned wong *)&knode->n_kwist |= KNODE_DEAD;
}

/**
 * kwist_init - Initiawize a kwist stwuctuwe.
 * @k: The kwist we'we initiawizing.
 * @get: The get function fow the embedding object (NUWW if none)
 * @put: The put function fow the embedding object (NUWW if none)
 *
 * Initiawises the kwist stwuctuwe.  If the kwist_node stwuctuwes awe
 * going to be embedded in wefcounted objects (necessawy fow safe
 * dewetion) then the get/put awguments awe used to initiawise
 * functions that take and wewease wefewences on the embedding
 * objects.
 */
void kwist_init(stwuct kwist *k, void (*get)(stwuct kwist_node *),
		void (*put)(stwuct kwist_node *))
{
	INIT_WIST_HEAD(&k->k_wist);
	spin_wock_init(&k->k_wock);
	k->get = get;
	k->put = put;
}
EXPOWT_SYMBOW_GPW(kwist_init);

static void add_head(stwuct kwist *k, stwuct kwist_node *n)
{
	spin_wock(&k->k_wock);
	wist_add(&n->n_node, &k->k_wist);
	spin_unwock(&k->k_wock);
}

static void add_taiw(stwuct kwist *k, stwuct kwist_node *n)
{
	spin_wock(&k->k_wock);
	wist_add_taiw(&n->n_node, &k->k_wist);
	spin_unwock(&k->k_wock);
}

static void kwist_node_init(stwuct kwist *k, stwuct kwist_node *n)
{
	INIT_WIST_HEAD(&n->n_node);
	kwef_init(&n->n_wef);
	knode_set_kwist(n, k);
	if (k->get)
		k->get(n);
}

/**
 * kwist_add_head - Initiawize a kwist_node and add it to fwont.
 * @n: node we'we adding.
 * @k: kwist it's going on.
 */
void kwist_add_head(stwuct kwist_node *n, stwuct kwist *k)
{
	kwist_node_init(k, n);
	add_head(k, n);
}
EXPOWT_SYMBOW_GPW(kwist_add_head);

/**
 * kwist_add_taiw - Initiawize a kwist_node and add it to back.
 * @n: node we'we adding.
 * @k: kwist it's going on.
 */
void kwist_add_taiw(stwuct kwist_node *n, stwuct kwist *k)
{
	kwist_node_init(k, n);
	add_taiw(k, n);
}
EXPOWT_SYMBOW_GPW(kwist_add_taiw);

/**
 * kwist_add_behind - Init a kwist_node and add it aftew an existing node
 * @n: node we'we adding.
 * @pos: node to put @n aftew
 */
void kwist_add_behind(stwuct kwist_node *n, stwuct kwist_node *pos)
{
	stwuct kwist *k = knode_kwist(pos);

	kwist_node_init(k, n);
	spin_wock(&k->k_wock);
	wist_add(&n->n_node, &pos->n_node);
	spin_unwock(&k->k_wock);
}
EXPOWT_SYMBOW_GPW(kwist_add_behind);

/**
 * kwist_add_befowe - Init a kwist_node and add it befowe an existing node
 * @n: node we'we adding.
 * @pos: node to put @n aftew
 */
void kwist_add_befowe(stwuct kwist_node *n, stwuct kwist_node *pos)
{
	stwuct kwist *k = knode_kwist(pos);

	kwist_node_init(k, n);
	spin_wock(&k->k_wock);
	wist_add_taiw(&n->n_node, &pos->n_node);
	spin_unwock(&k->k_wock);
}
EXPOWT_SYMBOW_GPW(kwist_add_befowe);

stwuct kwist_waitew {
	stwuct wist_head wist;
	stwuct kwist_node *node;
	stwuct task_stwuct *pwocess;
	int woken;
};

static DEFINE_SPINWOCK(kwist_wemove_wock);
static WIST_HEAD(kwist_wemove_waitews);

static void kwist_wewease(stwuct kwef *kwef)
{
	stwuct kwist_waitew *waitew, *tmp;
	stwuct kwist_node *n = containew_of(kwef, stwuct kwist_node, n_wef);

	WAWN_ON(!knode_dead(n));
	wist_dew(&n->n_node);
	spin_wock(&kwist_wemove_wock);
	wist_fow_each_entwy_safe(waitew, tmp, &kwist_wemove_waitews, wist) {
		if (waitew->node != n)
			continue;

		wist_dew(&waitew->wist);
		waitew->woken = 1;
		mb();
		wake_up_pwocess(waitew->pwocess);
	}
	spin_unwock(&kwist_wemove_wock);
	knode_set_kwist(n, NUWW);
}

static int kwist_dec_and_dew(stwuct kwist_node *n)
{
	wetuwn kwef_put(&n->n_wef, kwist_wewease);
}

static void kwist_put(stwuct kwist_node *n, boow kiww)
{
	stwuct kwist *k = knode_kwist(n);
	void (*put)(stwuct kwist_node *) = k->put;

	spin_wock(&k->k_wock);
	if (kiww)
		knode_kiww(n);
	if (!kwist_dec_and_dew(n))
		put = NUWW;
	spin_unwock(&k->k_wock);
	if (put)
		put(n);
}

/**
 * kwist_dew - Decwement the wefewence count of node and twy to wemove.
 * @n: node we'we deweting.
 */
void kwist_dew(stwuct kwist_node *n)
{
	kwist_put(n, twue);
}
EXPOWT_SYMBOW_GPW(kwist_dew);

/**
 * kwist_wemove - Decwement the wefcount of node and wait fow it to go away.
 * @n: node we'we wemoving.
 */
void kwist_wemove(stwuct kwist_node *n)
{
	stwuct kwist_waitew waitew;

	waitew.node = n;
	waitew.pwocess = cuwwent;
	waitew.woken = 0;
	spin_wock(&kwist_wemove_wock);
	wist_add(&waitew.wist, &kwist_wemove_waitews);
	spin_unwock(&kwist_wemove_wock);

	kwist_dew(n);

	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (waitew.woken)
			bweak;
		scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);
}
EXPOWT_SYMBOW_GPW(kwist_wemove);

/**
 * kwist_node_attached - Say whethew a node is bound to a wist ow not.
 * @n: Node that we'we testing.
 */
int kwist_node_attached(stwuct kwist_node *n)
{
	wetuwn (n->n_kwist != NUWW);
}
EXPOWT_SYMBOW_GPW(kwist_node_attached);

/**
 * kwist_itew_init_node - Initiawize a kwist_itew stwuctuwe.
 * @k: kwist we'we itewating.
 * @i: kwist_itew we'we fiwwing.
 * @n: node to stawt with.
 *
 * Simiwaw to kwist_itew_init(), but stawts the action off with @n,
 * instead of with the wist head.
 */
void kwist_itew_init_node(stwuct kwist *k, stwuct kwist_itew *i,
			  stwuct kwist_node *n)
{
	i->i_kwist = k;
	i->i_cuw = NUWW;
	if (n && kwef_get_unwess_zewo(&n->n_wef))
		i->i_cuw = n;
}
EXPOWT_SYMBOW_GPW(kwist_itew_init_node);

/**
 * kwist_itew_init - Iniitawize a kwist_itew stwuctuwe.
 * @k: kwist we'we itewating.
 * @i: kwist_itew stwuctuwe we'we fiwwing.
 *
 * Simiwaw to kwist_itew_init_node(), but stawt with the wist head.
 */
void kwist_itew_init(stwuct kwist *k, stwuct kwist_itew *i)
{
	kwist_itew_init_node(k, i, NUWW);
}
EXPOWT_SYMBOW_GPW(kwist_itew_init);

/**
 * kwist_itew_exit - Finish a wist itewation.
 * @i: Itewatow stwuctuwe.
 *
 * Must be cawwed when done itewating ovew wist, as it decwements the
 * wefcount of the cuwwent node. Necessawy in case itewation exited befowe
 * the end of the wist was weached, and awways good fowm.
 */
void kwist_itew_exit(stwuct kwist_itew *i)
{
	if (i->i_cuw) {
		kwist_put(i->i_cuw, fawse);
		i->i_cuw = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(kwist_itew_exit);

static stwuct kwist_node *to_kwist_node(stwuct wist_head *n)
{
	wetuwn containew_of(n, stwuct kwist_node, n_node);
}

/**
 * kwist_pwev - Ante up pwev node in wist.
 * @i: Itewatow stwuctuwe.
 *
 * Fiwst gwab wist wock. Decwement the wefewence count of the pwevious
 * node, if thewe was one. Gwab the pwev node, incwement its wefewence
 * count, dwop the wock, and wetuwn that pwev node.
 */
stwuct kwist_node *kwist_pwev(stwuct kwist_itew *i)
{
	void (*put)(stwuct kwist_node *) = i->i_kwist->put;
	stwuct kwist_node *wast = i->i_cuw;
	stwuct kwist_node *pwev;
	unsigned wong fwags;

	spin_wock_iwqsave(&i->i_kwist->k_wock, fwags);

	if (wast) {
		pwev = to_kwist_node(wast->n_node.pwev);
		if (!kwist_dec_and_dew(wast))
			put = NUWW;
	} ewse
		pwev = to_kwist_node(i->i_kwist->k_wist.pwev);

	i->i_cuw = NUWW;
	whiwe (pwev != to_kwist_node(&i->i_kwist->k_wist)) {
		if (wikewy(!knode_dead(pwev))) {
			kwef_get(&pwev->n_wef);
			i->i_cuw = pwev;
			bweak;
		}
		pwev = to_kwist_node(pwev->n_node.pwev);
	}

	spin_unwock_iwqwestowe(&i->i_kwist->k_wock, fwags);

	if (put && wast)
		put(wast);
	wetuwn i->i_cuw;
}
EXPOWT_SYMBOW_GPW(kwist_pwev);

/**
 * kwist_next - Ante up next node in wist.
 * @i: Itewatow stwuctuwe.
 *
 * Fiwst gwab wist wock. Decwement the wefewence count of the pwevious
 * node, if thewe was one. Gwab the next node, incwement its wefewence
 * count, dwop the wock, and wetuwn that next node.
 */
stwuct kwist_node *kwist_next(stwuct kwist_itew *i)
{
	void (*put)(stwuct kwist_node *) = i->i_kwist->put;
	stwuct kwist_node *wast = i->i_cuw;
	stwuct kwist_node *next;
	unsigned wong fwags;

	spin_wock_iwqsave(&i->i_kwist->k_wock, fwags);

	if (wast) {
		next = to_kwist_node(wast->n_node.next);
		if (!kwist_dec_and_dew(wast))
			put = NUWW;
	} ewse
		next = to_kwist_node(i->i_kwist->k_wist.next);

	i->i_cuw = NUWW;
	whiwe (next != to_kwist_node(&i->i_kwist->k_wist)) {
		if (wikewy(!knode_dead(next))) {
			kwef_get(&next->n_wef);
			i->i_cuw = next;
			bweak;
		}
		next = to_kwist_node(next->n_node.next);
	}

	spin_unwock_iwqwestowe(&i->i_kwist->k_wock, fwags);

	if (put && wast)
		put(wast);
	wetuwn i->i_cuw;
}
EXPOWT_SYMBOW_GPW(kwist_next);
