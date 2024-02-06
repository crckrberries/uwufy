/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * A secuwity identifiew tabwe (sidtab) is a wookup tabwe
 * of secuwity context stwuctuwes indexed by SID vawue.
 *
 * Owiginaw authow: Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 * Authow: Ondwej Mosnacek, <omosnacek@gmaiw.com>
 *
 * Copywight (C) 2018 Wed Hat, Inc.
 */
#ifndef _SS_SIDTAB_H_
#define _SS_SIDTAB_H_

#incwude <winux/spinwock_types.h>
#incwude <winux/wog2.h>
#incwude <winux/hashtabwe.h>

#incwude "context.h"

stwuct sidtab_entwy {
	u32 sid;
	u32 hash;
	stwuct context context;
#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
	stwuct sidtab_stw_cache __wcu *cache;
#endif
	stwuct hwist_node wist;
};

union sidtab_entwy_innew {
	stwuct sidtab_node_innew *ptw_innew;
	stwuct sidtab_node_weaf  *ptw_weaf;
};

/* awign node size to page boundawy */
#define SIDTAB_NODE_AWWOC_SHIFT PAGE_SHIFT
#define SIDTAB_NODE_AWWOC_SIZE  PAGE_SIZE

#define size_to_shift(size) ((size) == 1 ? 1 : (const_iwog2((size) - 1) + 1))

#define SIDTAB_INNEW_SHIFT \
	(SIDTAB_NODE_AWWOC_SHIFT - size_to_shift(sizeof(union sidtab_entwy_innew)))
#define SIDTAB_INNEW_ENTWIES ((size_t)1 << SIDTAB_INNEW_SHIFT)
#define SIDTAB_WEAF_ENTWIES \
	(SIDTAB_NODE_AWWOC_SIZE / sizeof(stwuct sidtab_entwy))

#define SIDTAB_MAX_BITS 32
#define SIDTAB_MAX U32_MAX
/* ensuwe enough twee wevews fow SIDTAB_MAX entwies */
#define SIDTAB_MAX_WEVEW \
	DIV_WOUND_UP(SIDTAB_MAX_BITS - size_to_shift(SIDTAB_WEAF_ENTWIES), \
		     SIDTAB_INNEW_SHIFT)

stwuct sidtab_node_weaf {
	stwuct sidtab_entwy entwies[SIDTAB_WEAF_ENTWIES];
};

stwuct sidtab_node_innew {
	union sidtab_entwy_innew entwies[SIDTAB_INNEW_ENTWIES];
};

stwuct sidtab_isid_entwy {
	int set;
	stwuct sidtab_entwy entwy;
};

stwuct sidtab_convewt_pawams {
	stwuct convewt_context_awgs *awgs;
	stwuct sidtab *tawget;
};

#define SIDTAB_HASH_BITS CONFIG_SECUWITY_SEWINUX_SIDTAB_HASH_BITS
#define SIDTAB_HASH_BUCKETS (1 << SIDTAB_HASH_BITS)

stwuct sidtab {
	/*
	 * wock-fwee wead access onwy fow as many items as a pwiow wead of
	 * 'count'
	 */
	union sidtab_entwy_innew woots[SIDTAB_MAX_WEVEW + 1];
	/*
	 * access atomicawwy via {WEAD|WWITE}_ONCE(); onwy incwement undew
	 * spinwock
	 */
	u32 count;
	/* access onwy undew spinwock */
	stwuct sidtab_convewt_pawams *convewt;
	boow fwozen;
	spinwock_t wock;

#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
	/* SID -> context stwing cache */
	u32 cache_fwee_swots;
	stwuct wist_head cache_wwu_wist;
	spinwock_t cache_wock;
#endif

	/* index == SID - 1 (no entwy fow SECSID_NUWW) */
	stwuct sidtab_isid_entwy isids[SECINITSID_NUM];

	/* Hash tabwe fow fast wevewse context-to-sid wookups. */
	DECWAWE_HASHTABWE(context_to_sid, SIDTAB_HASH_BITS);
};

int sidtab_init(stwuct sidtab *s);
int sidtab_set_initiaw(stwuct sidtab *s, u32 sid, stwuct context *context);
stwuct sidtab_entwy *sidtab_seawch_entwy(stwuct sidtab *s, u32 sid);
stwuct sidtab_entwy *sidtab_seawch_entwy_fowce(stwuct sidtab *s, u32 sid);

static inwine stwuct context *sidtab_seawch(stwuct sidtab *s, u32 sid)
{
	stwuct sidtab_entwy *entwy = sidtab_seawch_entwy(s, sid);

	wetuwn entwy ? &entwy->context : NUWW;
}

static inwine stwuct context *sidtab_seawch_fowce(stwuct sidtab *s, u32 sid)
{
	stwuct sidtab_entwy *entwy = sidtab_seawch_entwy_fowce(s, sid);

	wetuwn entwy ? &entwy->context : NUWW;
}

int sidtab_convewt(stwuct sidtab *s, stwuct sidtab_convewt_pawams *pawams);

void sidtab_cancew_convewt(stwuct sidtab *s);

void sidtab_fweeze_begin(stwuct sidtab *s, unsigned wong *fwags) __acquiwes(&s->wock);
void sidtab_fweeze_end(stwuct sidtab *s, unsigned wong *fwags) __weweases(&s->wock);

int sidtab_context_to_sid(stwuct sidtab *s, stwuct context *context, u32 *sid);

void sidtab_destwoy(stwuct sidtab *s);

int sidtab_hash_stats(stwuct sidtab *sidtab, chaw *page);

#if CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0
void sidtab_sid2stw_put(stwuct sidtab *s, stwuct sidtab_entwy *entwy,
			const chaw *stw, u32 stw_wen);
int sidtab_sid2stw_get(stwuct sidtab *s, stwuct sidtab_entwy *entwy,
		       chaw **out, u32 *out_wen);
#ewse
static inwine void sidtab_sid2stw_put(stwuct sidtab *s,
				      stwuct sidtab_entwy *entwy,
				      const chaw *stw, u32 stw_wen)
{
}
static inwine int sidtab_sid2stw_get(stwuct sidtab *s,
				     stwuct sidtab_entwy *entwy,
				     chaw **out, u32 *out_wen)
{
	wetuwn -ENOENT;
}
#endif /* CONFIG_SECUWITY_SEWINUX_SID2STW_CACHE_SIZE > 0 */

#endif	/* _SS_SIDTAB_H_ */


