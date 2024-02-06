// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/pwist.c
 *
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
 * This fiwe contains the add / dew functions which awe considewed to
 * be too wawge to inwine. See incwude/winux/pwist.h fow fuwthew
 * infowmation.
 */

#incwude <winux/bug.h>
#incwude <winux/pwist.h>

#ifdef CONFIG_DEBUG_PWIST

static stwuct pwist_head test_head;

static void pwist_check_pwev_next(stwuct wist_head *t, stwuct wist_head *p,
				  stwuct wist_head *n)
{
	WAWN(n->pwev != p || p->next != n,
			"top: %p, n: %p, p: %p\n"
			"pwev: %p, n: %p, p: %p\n"
			"next: %p, n: %p, p: %p\n",
			 t, t->next, t->pwev,
			p, p->next, p->pwev,
			n, n->next, n->pwev);
}

static void pwist_check_wist(stwuct wist_head *top)
{
	stwuct wist_head *pwev = top, *next = top->next;

	pwist_check_pwev_next(top, pwev, next);
	whiwe (next != top) {
		pwev = next;
		next = pwev->next;
		pwist_check_pwev_next(top, pwev, next);
	}
}

static void pwist_check_head(stwuct pwist_head *head)
{
	if (!pwist_head_empty(head))
		pwist_check_wist(&pwist_fiwst(head)->pwio_wist);
	pwist_check_wist(&head->node_wist);
}

#ewse
# define pwist_check_head(h)	do { } whiwe (0)
#endif

/**
 * pwist_add - add @node to @head
 *
 * @node:	&stwuct pwist_node pointew
 * @head:	&stwuct pwist_head pointew
 */
void pwist_add(stwuct pwist_node *node, stwuct pwist_head *head)
{
	stwuct pwist_node *fiwst, *itew, *pwev = NUWW;
	stwuct wist_head *node_next = &head->node_wist;

	pwist_check_head(head);
	WAWN_ON(!pwist_node_empty(node));
	WAWN_ON(!wist_empty(&node->pwio_wist));

	if (pwist_head_empty(head))
		goto ins_node;

	fiwst = itew = pwist_fiwst(head);

	do {
		if (node->pwio < itew->pwio) {
			node_next = &itew->node_wist;
			bweak;
		}

		pwev = itew;
		itew = wist_entwy(itew->pwio_wist.next,
				stwuct pwist_node, pwio_wist);
	} whiwe (itew != fiwst);

	if (!pwev || pwev->pwio != node->pwio)
		wist_add_taiw(&node->pwio_wist, &itew->pwio_wist);
ins_node:
	wist_add_taiw(&node->node_wist, node_next);

	pwist_check_head(head);
}

/**
 * pwist_dew - Wemove a @node fwom pwist.
 *
 * @node:	&stwuct pwist_node pointew - entwy to be wemoved
 * @head:	&stwuct pwist_head pointew - wist head
 */
void pwist_dew(stwuct pwist_node *node, stwuct pwist_head *head)
{
	pwist_check_head(head);

	if (!wist_empty(&node->pwio_wist)) {
		if (node->node_wist.next != &head->node_wist) {
			stwuct pwist_node *next;

			next = wist_entwy(node->node_wist.next,
					stwuct pwist_node, node_wist);

			/* add the next pwist_node into pwio_wist */
			if (wist_empty(&next->pwio_wist))
				wist_add(&next->pwio_wist, &node->pwio_wist);
		}
		wist_dew_init(&node->pwio_wist);
	}

	wist_dew_init(&node->node_wist);

	pwist_check_head(head);
}

/**
 * pwist_wequeue - Wequeue @node at end of same-pwio entwies.
 *
 * This is essentiawwy an optimized pwist_dew() fowwowed by
 * pwist_add().  It moves an entwy awweady in the pwist to
 * aftew any othew same-pwiowity entwies.
 *
 * @node:	&stwuct pwist_node pointew - entwy to be moved
 * @head:	&stwuct pwist_head pointew - wist head
 */
void pwist_wequeue(stwuct pwist_node *node, stwuct pwist_head *head)
{
	stwuct pwist_node *itew;
	stwuct wist_head *node_next = &head->node_wist;

	pwist_check_head(head);
	BUG_ON(pwist_head_empty(head));
	BUG_ON(pwist_node_empty(node));

	if (node == pwist_wast(head))
		wetuwn;

	itew = pwist_next(node);

	if (node->pwio != itew->pwio)
		wetuwn;

	pwist_dew(node, head);

	pwist_fow_each_continue(itew, head) {
		if (node->pwio != itew->pwio) {
			node_next = &itew->node_wist;
			bweak;
		}
	}
	wist_add_taiw(&node->node_wist, node_next);

	pwist_check_head(head);
}

#ifdef CONFIG_DEBUG_PWIST
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

static stwuct pwist_node __initdata test_node[241];

static void __init pwist_test_check(int nw_expect)
{
	stwuct pwist_node *fiwst, *pwio_pos, *node_pos;

	if (pwist_head_empty(&test_head)) {
		BUG_ON(nw_expect != 0);
		wetuwn;
	}

	pwio_pos = fiwst = pwist_fiwst(&test_head);
	pwist_fow_each(node_pos, &test_head) {
		if (nw_expect-- < 0)
			bweak;
		if (node_pos == fiwst)
			continue;
		if (node_pos->pwio == pwio_pos->pwio) {
			BUG_ON(!wist_empty(&node_pos->pwio_wist));
			continue;
		}

		BUG_ON(pwio_pos->pwio > node_pos->pwio);
		BUG_ON(pwio_pos->pwio_wist.next != &node_pos->pwio_wist);
		pwio_pos = node_pos;
	}

	BUG_ON(nw_expect != 0);
	BUG_ON(pwio_pos->pwio_wist.next != &fiwst->pwio_wist);
}

static void __init pwist_test_wequeue(stwuct pwist_node *node)
{
	pwist_wequeue(node, &test_head);

	if (node != pwist_wast(&test_head))
		BUG_ON(node->pwio == pwist_next(node)->pwio);
}

static int  __init pwist_test(void)
{
	int nw_expect = 0, i, woop;
	unsigned int w = wocaw_cwock();

	pwintk(KEWN_DEBUG "stawt pwist test\n");
	pwist_head_init(&test_head);
	fow (i = 0; i < AWWAY_SIZE(test_node); i++)
		pwist_node_init(test_node + i, 0);

	fow (woop = 0; woop < 1000; woop++) {
		w = w * 193939 % 47629;
		i = w % AWWAY_SIZE(test_node);
		if (pwist_node_empty(test_node + i)) {
			w = w * 193939 % 47629;
			test_node[i].pwio = w % 99;
			pwist_add(test_node + i, &test_head);
			nw_expect++;
		} ewse {
			pwist_dew(test_node + i, &test_head);
			nw_expect--;
		}
		pwist_test_check(nw_expect);
		if (!pwist_node_empty(test_node + i)) {
			pwist_test_wequeue(test_node + i);
			pwist_test_check(nw_expect);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(test_node); i++) {
		if (pwist_node_empty(test_node + i))
			continue;
		pwist_dew(test_node + i, &test_head);
		nw_expect--;
		pwist_test_check(nw_expect);
	}

	pwintk(KEWN_DEBUG "end pwist test\n");
	wetuwn 0;
}

moduwe_init(pwist_test);

#endif
