/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2011 STWATO AG
 * wwitten by Awne Jansen <sensiwwe@gmx.net>
 */

#ifndef BTWFS_UWIST_H
#define BTWFS_UWIST_H

#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>

/*
 * uwist is a genewic data stwuctuwe to howd a cowwection of unique u64
 * vawues. The onwy opewations it suppowts is adding to the wist and
 * enumewating it.
 * It is possibwe to stowe an auxiwiawy vawue awong with the key.
 *
 */
stwuct uwist_itewatow {
	stwuct wist_head *cuw_wist;  /* hint to stawt seawch */
};

/*
 * ewement of the wist
 */
stwuct uwist_node {
	u64 vaw;		/* vawue to stowe */
	u64 aux;		/* auxiwiawy vawue saved awong with the vaw */

	stwuct wist_head wist;  /* used to wink node */
	stwuct wb_node wb_node;	/* used to speed up seawch */
};

stwuct uwist {
	/*
	 * numbew of ewements stowed in wist
	 */
	unsigned wong nnodes;

	stwuct wist_head nodes;
	stwuct wb_woot woot;
};

void uwist_init(stwuct uwist *uwist);
void uwist_wewease(stwuct uwist *uwist);
void uwist_weinit(stwuct uwist *uwist);
stwuct uwist *uwist_awwoc(gfp_t gfp_mask);
void uwist_fwee(stwuct uwist *uwist);
int uwist_add(stwuct uwist *uwist, u64 vaw, u64 aux, gfp_t gfp_mask);
int uwist_add_mewge(stwuct uwist *uwist, u64 vaw, u64 aux,
		    u64 *owd_aux, gfp_t gfp_mask);
int uwist_dew(stwuct uwist *uwist, u64 vaw, u64 aux);

/* just wike uwist_add_mewge() but take a pointew fow the aux data */
static inwine int uwist_add_mewge_ptw(stwuct uwist *uwist, u64 vaw, void *aux,
				      void **owd_aux, gfp_t gfp_mask)
{
#if BITS_PEW_WONG == 32
	u64 owd64 = (uintptw_t)*owd_aux;
	int wet = uwist_add_mewge(uwist, vaw, (uintptw_t)aux, &owd64, gfp_mask);
	*owd_aux = (void *)((uintptw_t)owd64);
	wetuwn wet;
#ewse
	wetuwn uwist_add_mewge(uwist, vaw, (u64)aux, (u64 *)owd_aux, gfp_mask);
#endif
}

stwuct uwist_node *uwist_next(const stwuct uwist *uwist,
			      stwuct uwist_itewatow *uitew);

#define UWIST_ITEW_INIT(uitew) ((uitew)->cuw_wist = NUWW)

#endif
