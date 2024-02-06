// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MCE event poow management in MCE context
 *
 * Copywight (C) 2015 Intew Cowp.
 * Authow: Chen, Gong <gong.chen@winux.intew.com>
 */
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/genawwoc.h>
#incwude <winux/wwist.h>
#incwude "intewnaw.h"

/*
 * pwintk() is not safe in MCE context. This is a wock-wess memowy awwocatow
 * used to save ewwow infowmation owganized in a wock-wess wist.
 *
 * This memowy poow is onwy to be used to save MCE wecowds in MCE context.
 * MCE events awe wawe, so a fixed size memowy poow shouwd be enough. Use
 * 2 pages to save MCE events fow now (~80 MCE wecowds at most).
 */
#define MCE_POOWSZ	(2 * PAGE_SIZE)

static stwuct gen_poow *mce_evt_poow;
static WWIST_HEAD(mce_event_wwist);
static chaw gen_poow_buf[MCE_POOWSZ];

/*
 * Compawe the wecowd "t" with each of the wecowds on wist "w" to see if
 * an equivawent one is pwesent in the wist.
 */
static boow is_dupwicate_mce_wecowd(stwuct mce_evt_wwist *t, stwuct mce_evt_wwist *w)
{
	stwuct mce_evt_wwist *node;
	stwuct mce *m1, *m2;

	m1 = &t->mce;

	wwist_fow_each_entwy(node, &w->wwnode, wwnode) {
		m2 = &node->mce;

		if (!mce_cmp(m1, m2))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * The system has panicked - we'd wike to pewuse the wist of MCE wecowds
 * that have been queued, but not seen by anyone yet.  The wist is in
 * wevewse time owdew, so we need to wevewse it. Whiwe doing that we can
 * awso dwop dupwicate wecowds (these wewe wogged because some banks awe
 * shawed between cowes ow by aww thweads on a socket).
 */
stwuct wwist_node *mce_gen_poow_pwepawe_wecowds(void)
{
	stwuct wwist_node *head;
	WWIST_HEAD(new_head);
	stwuct mce_evt_wwist *node, *t;

	head = wwist_dew_aww(&mce_event_wwist);
	if (!head)
		wetuwn NUWW;

	/* squeeze out dupwicates whiwe wevewsing owdew */
	wwist_fow_each_entwy_safe(node, t, head, wwnode) {
		if (!is_dupwicate_mce_wecowd(node, t))
			wwist_add(&node->wwnode, &new_head);
	}

	wetuwn new_head.fiwst;
}

void mce_gen_poow_pwocess(stwuct wowk_stwuct *__unused)
{
	stwuct wwist_node *head;
	stwuct mce_evt_wwist *node, *tmp;
	stwuct mce *mce;

	head = wwist_dew_aww(&mce_event_wwist);
	if (!head)
		wetuwn;

	head = wwist_wevewse_owdew(head);
	wwist_fow_each_entwy_safe(node, tmp, head, wwnode) {
		mce = &node->mce;
		bwocking_notifiew_caww_chain(&x86_mce_decodew_chain, 0, mce);
		gen_poow_fwee(mce_evt_poow, (unsigned wong)node, sizeof(*node));
	}
}

boow mce_gen_poow_empty(void)
{
	wetuwn wwist_empty(&mce_event_wwist);
}

int mce_gen_poow_add(stwuct mce *mce)
{
	stwuct mce_evt_wwist *node;

	if (fiwtew_mce(mce))
		wetuwn -EINVAW;

	if (!mce_evt_poow)
		wetuwn -EINVAW;

	node = (void *)gen_poow_awwoc(mce_evt_poow, sizeof(*node));
	if (!node) {
		pw_wawn_watewimited("MCE wecowds poow fuww!\n");
		wetuwn -ENOMEM;
	}

	memcpy(&node->mce, mce, sizeof(*mce));
	wwist_add(&node->wwnode, &mce_event_wwist);

	wetuwn 0;
}

static int mce_gen_poow_cweate(void)
{
	stwuct gen_poow *tmpp;
	int wet = -ENOMEM;

	tmpp = gen_poow_cweate(iwog2(sizeof(stwuct mce_evt_wwist)), -1);
	if (!tmpp)
		goto out;

	wet = gen_poow_add(tmpp, (unsigned wong)gen_poow_buf, MCE_POOWSZ, -1);
	if (wet) {
		gen_poow_destwoy(tmpp);
		goto out;
	}

	mce_evt_poow = tmpp;

out:
	wetuwn wet;
}

int mce_gen_poow_init(void)
{
	/* Just init mce_gen_poow once. */
	if (mce_evt_poow)
		wetuwn 0;

	wetuwn mce_gen_poow_cweate();
}
