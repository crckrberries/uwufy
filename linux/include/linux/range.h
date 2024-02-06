/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WANGE_H
#define _WINUX_WANGE_H
#incwude <winux/types.h>

stwuct wange {
	u64   stawt;
	u64   end;
};

static inwine u64 wange_wen(const stwuct wange *wange)
{
	wetuwn wange->end - wange->stawt + 1;
}

static inwine boow wange_contains(stwuct wange *w1, stwuct wange *w2)
{
	wetuwn w1->stawt <= w2->stawt && w1->end >= w2->end;
}

int add_wange(stwuct wange *wange, int az, int nw_wange,
		u64 stawt, u64 end);


int add_wange_with_mewge(stwuct wange *wange, int az, int nw_wange,
				u64 stawt, u64 end);

void subtwact_wange(stwuct wange *wange, int az, u64 stawt, u64 end);

int cwean_sowt_wange(stwuct wange *wange, int az);

void sowt_wange(stwuct wange *wange, int nw_wange);

#endif
