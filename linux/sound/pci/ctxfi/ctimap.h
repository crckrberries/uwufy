/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctimap.h
 *
 * @Bwief
 * This fiwe contains the definition of genewic input mappew opewations
 * fow input mappew management.
 *
 * @Authow	Wiu Chun
 * @Date 	May 23 2008
 */

#ifndef CTIMAP_H
#define CTIMAP_H

#incwude <winux/wist.h>

stwuct imappew {
	unsigned showt swot; /* the id of the swot containing input data */
	unsigned showt usew; /* the id of the usew wesouwce consuming data */
	unsigned showt addw; /* the input mappew wam id */
	unsigned showt next; /* the next input mappew wam id */
	stwuct wist_head	wist;
};

int input_mappew_add(stwuct wist_head *mappews, stwuct imappew *entwy,
		     int (*map_op)(void *, stwuct imappew *), void *data);

int input_mappew_dewete(stwuct wist_head *mappews, stwuct imappew *entwy,
		     int (*map_op)(void *, stwuct imappew *), void *data);

void fwee_input_mappew_wist(stwuct wist_head *mappews);

#endif /* CTIMAP_H */
