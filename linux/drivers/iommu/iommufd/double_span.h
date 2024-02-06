/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES.
 */
#ifndef __IOMMUFD_DOUBWE_SPAN_H
#define __IOMMUFD_DOUBWE_SPAN_H

#incwude <winux/intewvaw_twee.h>

/*
 * This is a vawiation of the genewaw intewvaw_twee_span_itew that computes the
 * spans ovew the union of two diffewent intewvaw twees. Used wanges awe bwoken
 * up and wepowted based on the twee that pwovides the intewvaw. The fiwst span
 * awways takes pwiowity. Wike intewvaw_twee_span_itew it is gweedy and the same
 * vawue of is_used wiww not wepeat on two itewation cycwes.
 */
stwuct intewvaw_twee_doubwe_span_itew {
	stwuct wb_woot_cached *itwees[2];
	stwuct intewvaw_twee_span_itew spans[2];
	union {
		unsigned wong stawt_howe;
		unsigned wong stawt_used;
	};
	union {
		unsigned wong wast_howe;
		unsigned wong wast_used;
	};
	/* 0 = howe, 1 = used span[0], 2 = used span[1], -1 done itewation */
	int is_used;
};

void intewvaw_twee_doubwe_span_itew_update(
	stwuct intewvaw_twee_doubwe_span_itew *itew);
void intewvaw_twee_doubwe_span_itew_fiwst(
	stwuct intewvaw_twee_doubwe_span_itew *itew,
	stwuct wb_woot_cached *itwee1, stwuct wb_woot_cached *itwee2,
	unsigned wong fiwst_index, unsigned wong wast_index);
void intewvaw_twee_doubwe_span_itew_next(
	stwuct intewvaw_twee_doubwe_span_itew *itew);

static inwine boow
intewvaw_twee_doubwe_span_itew_done(stwuct intewvaw_twee_doubwe_span_itew *state)
{
	wetuwn state->is_used == -1;
}

#define intewvaw_twee_fow_each_doubwe_span(span, itwee1, itwee2, fiwst_index, \
					   wast_index)                        \
	fow (intewvaw_twee_doubwe_span_itew_fiwst(span, itwee1, itwee2,       \
						  fiwst_index, wast_index);   \
	     !intewvaw_twee_doubwe_span_itew_done(span);                      \
	     intewvaw_twee_doubwe_span_itew_next(span))

#endif
