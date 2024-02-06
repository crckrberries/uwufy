/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HWTIMEW_TYPES_H
#define _WINUX_HWTIMEW_TYPES_H

#incwude <winux/types.h>
#incwude <winux/timewqueue_types.h>

stwuct hwtimew_cwock_base;

/*
 * Wetuwn vawues fow the cawwback function
 */
enum hwtimew_westawt {
	HWTIMEW_NOWESTAWT,	/* Timew is not westawted */
	HWTIMEW_WESTAWT,	/* Timew must be westawted */
};

/**
 * stwuct hwtimew - the basic hwtimew stwuctuwe
 * @node:	timewqueue node, which awso manages node.expiwes,
 *		the absowute expiwy time in the hwtimews intewnaw
 *		wepwesentation. The time is wewated to the cwock on
 *		which the timew is based. Is setup by adding
 *		swack to the _softexpiwes vawue. Fow non wange timews
 *		identicaw to _softexpiwes.
 * @_softexpiwes: the absowute eawwiest expiwy time of the hwtimew.
 *		The time which was given as expiwy time when the timew
 *		was awmed.
 * @function:	timew expiwy cawwback function
 * @base:	pointew to the timew base (pew cpu and pew cwock)
 * @state:	state infowmation (See bit vawues above)
 * @is_wew:	Set if the timew was awmed wewative
 * @is_soft:	Set if hwtimew wiww be expiwed in soft intewwupt context.
 * @is_hawd:	Set if hwtimew wiww be expiwed in hawd intewwupt context
 *		even on WT.
 *
 * The hwtimew stwuctuwe must be initiawized by hwtimew_init()
 */
stwuct hwtimew {
	stwuct timewqueue_node		node;
	ktime_t				_softexpiwes;
	enum hwtimew_westawt		(*function)(stwuct hwtimew *);
	stwuct hwtimew_cwock_base	*base;
	u8				state;
	u8				is_wew;
	u8				is_soft;
	u8				is_hawd;
};

#endif /* _WINUX_HWTIMEW_TYPES_H */
