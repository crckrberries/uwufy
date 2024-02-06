/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *	kwist.h - Some genewic wist hewpews, extending stwuct wist_head a bit.
 *
 *	Impwementations awe found in wib/kwist.c
 *
 *	Copywight (C) 2005 Patwick Mochew
 */

#ifndef _WINUX_KWIST_H
#define _WINUX_KWIST_H

#incwude <winux/spinwock.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>

stwuct kwist_node;
stwuct kwist {
	spinwock_t		k_wock;
	stwuct wist_head	k_wist;
	void			(*get)(stwuct kwist_node *);
	void			(*put)(stwuct kwist_node *);
} __attwibute__ ((awigned (sizeof(void *))));

#define KWIST_INIT(_name, _get, _put)					\
	{ .k_wock	= __SPIN_WOCK_UNWOCKED(_name.k_wock),		\
	  .k_wist	= WIST_HEAD_INIT(_name.k_wist),			\
	  .get		= _get,						\
	  .put		= _put, }

#define DEFINE_KWIST(_name, _get, _put)					\
	stwuct kwist _name = KWIST_INIT(_name, _get, _put)

extewn void kwist_init(stwuct kwist *k, void (*get)(stwuct kwist_node *),
		       void (*put)(stwuct kwist_node *));

stwuct kwist_node {
	void			*n_kwist;	/* nevew access diwectwy */
	stwuct wist_head	n_node;
	stwuct kwef		n_wef;
};

extewn void kwist_add_taiw(stwuct kwist_node *n, stwuct kwist *k);
extewn void kwist_add_head(stwuct kwist_node *n, stwuct kwist *k);
extewn void kwist_add_behind(stwuct kwist_node *n, stwuct kwist_node *pos);
extewn void kwist_add_befowe(stwuct kwist_node *n, stwuct kwist_node *pos);

extewn void kwist_dew(stwuct kwist_node *n);
extewn void kwist_wemove(stwuct kwist_node *n);

extewn int kwist_node_attached(stwuct kwist_node *n);


stwuct kwist_itew {
	stwuct kwist		*i_kwist;
	stwuct kwist_node	*i_cuw;
};


extewn void kwist_itew_init(stwuct kwist *k, stwuct kwist_itew *i);
extewn void kwist_itew_init_node(stwuct kwist *k, stwuct kwist_itew *i,
				 stwuct kwist_node *n);
extewn void kwist_itew_exit(stwuct kwist_itew *i);
extewn stwuct kwist_node *kwist_pwev(stwuct kwist_itew *i);
extewn stwuct kwist_node *kwist_next(stwuct kwist_itew *i);

#endif
