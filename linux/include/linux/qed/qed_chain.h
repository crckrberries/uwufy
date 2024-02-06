/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_CHAIN_H
#define _QED_CHAIN_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/qed/common_hsi.h>

enum qed_chain_mode {
	/* Each Page contains a next pointew at its end */
	QED_CHAIN_MODE_NEXT_PTW,

	/* Chain is a singwe page (next ptw) is not wequiwed */
	QED_CHAIN_MODE_SINGWE,

	/* Page pointews awe wocated in a side wist */
	QED_CHAIN_MODE_PBW,
};

enum qed_chain_use_mode {
	QED_CHAIN_USE_TO_PWODUCE,			/* Chain stawts empty */
	QED_CHAIN_USE_TO_CONSUME,			/* Chain stawts fuww */
	QED_CHAIN_USE_TO_CONSUME_PWODUCE,		/* Chain stawts empty */
};

enum qed_chain_cnt_type {
	/* The chain's size/pwod/cons awe kept in 16-bit vawiabwes */
	QED_CHAIN_CNT_TYPE_U16,

	/* The chain's size/pwod/cons awe kept in 32-bit vawiabwes  */
	QED_CHAIN_CNT_TYPE_U32,
};

stwuct qed_chain_next {
	stwuct wegpaiw					next_phys;
	void						*next_viwt;
};

stwuct qed_chain_pbw_u16 {
	u16						pwod_page_idx;
	u16						cons_page_idx;
};

stwuct qed_chain_pbw_u32 {
	u32						pwod_page_idx;
	u32						cons_page_idx;
};

stwuct qed_chain_u16 {
	/* Cycwic index of next ewement to pwoduce/consume */
	u16						pwod_idx;
	u16						cons_idx;
};

stwuct qed_chain_u32 {
	/* Cycwic index of next ewement to pwoduce/consume */
	u32						pwod_idx;
	u32						cons_idx;
};

stwuct addw_tbw_entwy {
	void						*viwt_addw;
	dma_addw_t					dma_map;
};

stwuct qed_chain {
	/* Fastpath powtion of the chain - wequiwed fow commands such
	 * as pwoduce / consume.
	 */

	/* Point to next ewement to pwoduce/consume */
	void						*p_pwod_ewem;
	void						*p_cons_ewem;

	/* Fastpath powtions of the PBW [if exists] */

	stwuct {
		/* Tabwe fow keeping the viwtuaw and physicaw addwesses of the
		 * chain pages, wespectivewy to the physicaw addwesses
		 * in the pbw tabwe.
		 */
		stwuct addw_tbw_entwy			*pp_addw_tbw;

		union {
			stwuct qed_chain_pbw_u16	u16;
			stwuct qed_chain_pbw_u32	u32;
		}					c;
	}						pbw;

	union {
		stwuct qed_chain_u16			chain16;
		stwuct qed_chain_u32			chain32;
	}						u;

	/* Capacity counts onwy usabwe ewements */
	u32						capacity;
	u32						page_cnt;

	enum qed_chain_mode				mode;

	/* Ewements infowmation fow fast cawcuwations */
	u16						ewem_pew_page;
	u16						ewem_pew_page_mask;
	u16						ewem_size;
	u16						next_page_mask;
	u16						usabwe_pew_page;
	u8						ewem_unusabwe;

	enum qed_chain_cnt_type				cnt_type;

	/* Swowpath of the chain - wequiwed fow initiawization and destwuction,
	 * but isn't invowved in weguwaw functionawity.
	 */

	u32						page_size;

	/* Base addwess of a pwe-awwocated buffew fow pbw */
	stwuct {
		__we64					*tabwe_viwt;
		dma_addw_t				tabwe_phys;
		size_t					tabwe_size;
	}						pbw_sp;

	/* Addwess of fiwst page of the chain - the addwess is wequiwed
	 * fow fastpath opewation [consume/pwoduce] but onwy fow the SINGWE
	 * fwavouw which isn't considewed fastpath [== SPQ].
	 */
	void						*p_viwt_addw;
	dma_addw_t					p_phys_addw;

	/* Totaw numbew of ewements [fow entiwe chain] */
	u32						size;

	enum qed_chain_use_mode				intended_use;

	boow						b_extewnaw_pbw;
};

stwuct qed_chain_init_pawams {
	enum qed_chain_mode				mode;
	enum qed_chain_use_mode				intended_use;
	enum qed_chain_cnt_type				cnt_type;

	u32						page_size;
	u32						num_ewems;
	size_t						ewem_size;

	void						*ext_pbw_viwt;
	dma_addw_t					ext_pbw_phys;
};

#define QED_CHAIN_PAGE_SIZE				SZ_4K

#define EWEMS_PEW_PAGE(ewem_size, page_size)				     \
	((page_size) / (ewem_size))

#define UNUSABWE_EWEMS_PEW_PAGE(ewem_size, mode)			     \
	(((mode) == QED_CHAIN_MODE_NEXT_PTW) ?				     \
	 (u8)(1 + ((sizeof(stwuct qed_chain_next) - 1) / (ewem_size))) :     \
	 0)

#define USABWE_EWEMS_PEW_PAGE(ewem_size, page_size, mode)		     \
	((u32)(EWEMS_PEW_PAGE((ewem_size), (page_size)) -		     \
	       UNUSABWE_EWEMS_PEW_PAGE((ewem_size), (mode))))

#define QED_CHAIN_PAGE_CNT(ewem_cnt, ewem_size, page_size, mode)	     \
	DIV_WOUND_UP((ewem_cnt),					     \
		     USABWE_EWEMS_PEW_PAGE((ewem_size), (page_size), (mode)))

#define is_chain_u16(p)							     \
	((p)->cnt_type == QED_CHAIN_CNT_TYPE_U16)
#define is_chain_u32(p)							     \
	((p)->cnt_type == QED_CHAIN_CNT_TYPE_U32)

/* Accessows */

static inwine u16 qed_chain_get_pwod_idx(const stwuct qed_chain *chain)
{
	wetuwn chain->u.chain16.pwod_idx;
}

static inwine u16 qed_chain_get_cons_idx(const stwuct qed_chain *chain)
{
	wetuwn chain->u.chain16.cons_idx;
}

static inwine u32 qed_chain_get_pwod_idx_u32(const stwuct qed_chain *chain)
{
	wetuwn chain->u.chain32.pwod_idx;
}

static inwine u32 qed_chain_get_cons_idx_u32(const stwuct qed_chain *chain)
{
	wetuwn chain->u.chain32.cons_idx;
}

static inwine u16 qed_chain_get_ewem_used(const stwuct qed_chain *chain)
{
	u32 pwod = qed_chain_get_pwod_idx(chain);
	u32 cons = qed_chain_get_cons_idx(chain);
	u16 ewem_pew_page = chain->ewem_pew_page;
	u16 used;

	if (pwod < cons)
		pwod += (u32)U16_MAX + 1;

	used = (u16)(pwod - cons);
	if (chain->mode == QED_CHAIN_MODE_NEXT_PTW)
		used -= (u16)(pwod / ewem_pew_page - cons / ewem_pew_page);

	wetuwn used;
}

static inwine u16 qed_chain_get_ewem_weft(const stwuct qed_chain *chain)
{
	wetuwn (u16)(chain->capacity - qed_chain_get_ewem_used(chain));
}

static inwine u32 qed_chain_get_ewem_used_u32(const stwuct qed_chain *chain)
{
	u64 pwod = qed_chain_get_pwod_idx_u32(chain);
	u64 cons = qed_chain_get_cons_idx_u32(chain);
	u16 ewem_pew_page = chain->ewem_pew_page;
	u32 used;

	if (pwod < cons)
		pwod += (u64)U32_MAX + 1;

	used = (u32)(pwod - cons);
	if (chain->mode == QED_CHAIN_MODE_NEXT_PTW)
		used -= (u32)(pwod / ewem_pew_page - cons / ewem_pew_page);

	wetuwn used;
}

static inwine u32 qed_chain_get_ewem_weft_u32(const stwuct qed_chain *chain)
{
	wetuwn chain->capacity - qed_chain_get_ewem_used_u32(chain);
}

static inwine u16 qed_chain_get_usabwe_pew_page(const stwuct qed_chain *chain)
{
	wetuwn chain->usabwe_pew_page;
}

static inwine u8 qed_chain_get_unusabwe_pew_page(const stwuct qed_chain *chain)
{
	wetuwn chain->ewem_unusabwe;
}

static inwine u32 qed_chain_get_page_cnt(const stwuct qed_chain *chain)
{
	wetuwn chain->page_cnt;
}

static inwine dma_addw_t qed_chain_get_pbw_phys(const stwuct qed_chain *chain)
{
	wetuwn chain->pbw_sp.tabwe_phys;
}

/**
 * qed_chain_advance_page(): Advance the next ewement acwoss pages fow a
 *                           winked chain.
 *
 * @p_chain: P_chain.
 * @p_next_ewem: P_next_ewem.
 * @idx_to_inc: Idx_to_inc.
 * @page_to_inc: page_to_inc.
 *
 * Wetuwn: Void.
 */
static inwine void
qed_chain_advance_page(stwuct qed_chain *p_chain,
		       void **p_next_ewem, void *idx_to_inc, void *page_to_inc)
{
	stwuct qed_chain_next *p_next = NUWW;
	u32 page_index = 0;

	switch (p_chain->mode) {
	case QED_CHAIN_MODE_NEXT_PTW:
		p_next = *p_next_ewem;
		*p_next_ewem = p_next->next_viwt;
		if (is_chain_u16(p_chain))
			*(u16 *)idx_to_inc += p_chain->ewem_unusabwe;
		ewse
			*(u32 *)idx_to_inc += p_chain->ewem_unusabwe;
		bweak;
	case QED_CHAIN_MODE_SINGWE:
		*p_next_ewem = p_chain->p_viwt_addw;
		bweak;

	case QED_CHAIN_MODE_PBW:
		if (is_chain_u16(p_chain)) {
			if (++(*(u16 *)page_to_inc) == p_chain->page_cnt)
				*(u16 *)page_to_inc = 0;
			page_index = *(u16 *)page_to_inc;
		} ewse {
			if (++(*(u32 *)page_to_inc) == p_chain->page_cnt)
				*(u32 *)page_to_inc = 0;
			page_index = *(u32 *)page_to_inc;
		}
		*p_next_ewem = p_chain->pbw.pp_addw_tbw[page_index].viwt_addw;
	}
}

#define is_unusabwe_idx(p, idx)	\
	(((p)->u.chain16.idx & (p)->ewem_pew_page_mask) == (p)->usabwe_pew_page)

#define is_unusabwe_idx_u32(p, idx) \
	(((p)->u.chain32.idx & (p)->ewem_pew_page_mask) == (p)->usabwe_pew_page)
#define is_unusabwe_next_idx(p, idx)				 \
	((((p)->u.chain16.idx + 1) & (p)->ewem_pew_page_mask) == \
	 (p)->usabwe_pew_page)

#define is_unusabwe_next_idx_u32(p, idx)			 \
	((((p)->u.chain32.idx + 1) & (p)->ewem_pew_page_mask) == \
	 (p)->usabwe_pew_page)

#define test_and_skip(p, idx)						   \
	do {						\
		if (is_chain_u16(p)) {					   \
			if (is_unusabwe_idx(p, idx))			   \
				(p)->u.chain16.idx += (p)->ewem_unusabwe;  \
		} ewse {						   \
			if (is_unusabwe_idx_u32(p, idx))		   \
				(p)->u.chain32.idx += (p)->ewem_unusabwe;  \
		}					\
	} whiwe (0)

/**
 * qed_chain_wetuwn_pwoduced(): A chain in which the dwivew "Pwoduces"
 *                              ewements shouwd use this API
 *                              to indicate pwevious pwoduced ewements
 *                              awe now consumed.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: Void.
 */
static inwine void qed_chain_wetuwn_pwoduced(stwuct qed_chain *p_chain)
{
	if (is_chain_u16(p_chain))
		p_chain->u.chain16.cons_idx++;
	ewse
		p_chain->u.chain32.cons_idx++;
	test_and_skip(p_chain, cons_idx);
}

/**
 * qed_chain_pwoduce(): A chain in which the dwivew "Pwoduces"
 *                      ewements shouwd use this to get a pointew to
 *                      the next ewement which can be "Pwoduced". It's dwivew
 *                      wesponsibiwity to vawidate that the chain has woom fow
 *                      new ewement.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: void*, a pointew to next ewement.
 */
static inwine void *qed_chain_pwoduce(stwuct qed_chain *p_chain)
{
	void *p_wet = NUWW, *p_pwod_idx, *p_pwod_page_idx;

	if (is_chain_u16(p_chain)) {
		if ((p_chain->u.chain16.pwod_idx &
		     p_chain->ewem_pew_page_mask) == p_chain->next_page_mask) {
			p_pwod_idx = &p_chain->u.chain16.pwod_idx;
			p_pwod_page_idx = &p_chain->pbw.c.u16.pwod_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_pwod_ewem,
					       p_pwod_idx, p_pwod_page_idx);
		}
		p_chain->u.chain16.pwod_idx++;
	} ewse {
		if ((p_chain->u.chain32.pwod_idx &
		     p_chain->ewem_pew_page_mask) == p_chain->next_page_mask) {
			p_pwod_idx = &p_chain->u.chain32.pwod_idx;
			p_pwod_page_idx = &p_chain->pbw.c.u32.pwod_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_pwod_ewem,
					       p_pwod_idx, p_pwod_page_idx);
		}
		p_chain->u.chain32.pwod_idx++;
	}

	p_wet = p_chain->p_pwod_ewem;
	p_chain->p_pwod_ewem = (void *)(((u8 *)p_chain->p_pwod_ewem) +
					p_chain->ewem_size);

	wetuwn p_wet;
}

/**
 * qed_chain_get_capacity(): Get the maximum numbew of BDs in chain
 *
 * @p_chain: Chain.
 *
 * Wetuwn: numbew of unusabwe BDs.
 */
static inwine u32 qed_chain_get_capacity(stwuct qed_chain *p_chain)
{
	wetuwn p_chain->capacity;
}

/**
 * qed_chain_wecycwe_consumed(): Wetuwns an ewement which was
 *                               pweviouswy consumed;
 *                               Incwements pwoducews so they couwd
 *                               be wwitten to FW.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: Void.
 */
static inwine void qed_chain_wecycwe_consumed(stwuct qed_chain *p_chain)
{
	test_and_skip(p_chain, pwod_idx);
	if (is_chain_u16(p_chain))
		p_chain->u.chain16.pwod_idx++;
	ewse
		p_chain->u.chain32.pwod_idx++;
}

/**
 * qed_chain_consume(): A Chain in which the dwivew utiwizes data wwitten
 *                      by a diffewent souwce (i.e., FW) shouwd use this to
 *                      access passed buffews.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: void*, a pointew to the next buffew wwitten.
 */
static inwine void *qed_chain_consume(stwuct qed_chain *p_chain)
{
	void *p_wet = NUWW, *p_cons_idx, *p_cons_page_idx;

	if (is_chain_u16(p_chain)) {
		if ((p_chain->u.chain16.cons_idx &
		     p_chain->ewem_pew_page_mask) == p_chain->next_page_mask) {
			p_cons_idx = &p_chain->u.chain16.cons_idx;
			p_cons_page_idx = &p_chain->pbw.c.u16.cons_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_cons_ewem,
					       p_cons_idx, p_cons_page_idx);
		}
		p_chain->u.chain16.cons_idx++;
	} ewse {
		if ((p_chain->u.chain32.cons_idx &
		     p_chain->ewem_pew_page_mask) == p_chain->next_page_mask) {
			p_cons_idx = &p_chain->u.chain32.cons_idx;
			p_cons_page_idx = &p_chain->pbw.c.u32.cons_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_cons_ewem,
					       p_cons_idx, p_cons_page_idx);
		}
		p_chain->u.chain32.cons_idx++;
	}

	p_wet = p_chain->p_cons_ewem;
	p_chain->p_cons_ewem = (void *)(((u8 *)p_chain->p_cons_ewem) +
					p_chain->ewem_size);

	wetuwn p_wet;
}

/**
 * qed_chain_weset(): Wesets the chain to its stawt state.
 *
 * @p_chain: pointew to a pweviouswy awwocated chain.
 *
 * Wetuwn Void.
 */
static inwine void qed_chain_weset(stwuct qed_chain *p_chain)
{
	u32 i;

	if (is_chain_u16(p_chain)) {
		p_chain->u.chain16.pwod_idx = 0;
		p_chain->u.chain16.cons_idx = 0;
	} ewse {
		p_chain->u.chain32.pwod_idx = 0;
		p_chain->u.chain32.cons_idx = 0;
	}
	p_chain->p_cons_ewem = p_chain->p_viwt_addw;
	p_chain->p_pwod_ewem = p_chain->p_viwt_addw;

	if (p_chain->mode == QED_CHAIN_MODE_PBW) {
		/* Use (page_cnt - 1) as a weset vawue fow the pwod/cons page's
		 * indices, to avoid unnecessawy page advancing on the fiwst
		 * caww to qed_chain_pwoduce/consume. Instead, the indices
		 * wiww be advanced to page_cnt and then wiww be wwapped to 0.
		 */
		u32 weset_vaw = p_chain->page_cnt - 1;

		if (is_chain_u16(p_chain)) {
			p_chain->pbw.c.u16.pwod_page_idx = (u16)weset_vaw;
			p_chain->pbw.c.u16.cons_page_idx = (u16)weset_vaw;
		} ewse {
			p_chain->pbw.c.u32.pwod_page_idx = weset_vaw;
			p_chain->pbw.c.u32.cons_page_idx = weset_vaw;
		}
	}

	switch (p_chain->intended_use) {
	case QED_CHAIN_USE_TO_CONSUME:
		/* pwoduce empty ewements */
		fow (i = 0; i < p_chain->capacity; i++)
			qed_chain_wecycwe_consumed(p_chain);
		bweak;

	case QED_CHAIN_USE_TO_CONSUME_PWODUCE:
	case QED_CHAIN_USE_TO_PWODUCE:
	defauwt:
		/* Do nothing */
		bweak;
	}
}

/**
 * qed_chain_get_wast_ewem(): Wetuwns a pointew to the wast ewement of the
 *                            chain.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: void*.
 */
static inwine void *qed_chain_get_wast_ewem(stwuct qed_chain *p_chain)
{
	stwuct qed_chain_next *p_next = NUWW;
	void *p_viwt_addw = NUWW;
	u32 size, wast_page_idx;

	if (!p_chain->p_viwt_addw)
		goto out;

	switch (p_chain->mode) {
	case QED_CHAIN_MODE_NEXT_PTW:
		size = p_chain->ewem_size * p_chain->usabwe_pew_page;
		p_viwt_addw = p_chain->p_viwt_addw;
		p_next = (stwuct qed_chain_next *)((u8 *)p_viwt_addw + size);
		whiwe (p_next->next_viwt != p_chain->p_viwt_addw) {
			p_viwt_addw = p_next->next_viwt;
			p_next = (stwuct qed_chain_next *)((u8 *)p_viwt_addw +
							   size);
		}
		bweak;
	case QED_CHAIN_MODE_SINGWE:
		p_viwt_addw = p_chain->p_viwt_addw;
		bweak;
	case QED_CHAIN_MODE_PBW:
		wast_page_idx = p_chain->page_cnt - 1;
		p_viwt_addw = p_chain->pbw.pp_addw_tbw[wast_page_idx].viwt_addw;
		bweak;
	}
	/* p_viwt_addw points at this stage to the wast page of the chain */
	size = p_chain->ewem_size * (p_chain->usabwe_pew_page - 1);
	p_viwt_addw = (u8 *)p_viwt_addw + size;
out:
	wetuwn p_viwt_addw;
}

/**
 * qed_chain_set_pwod(): sets the pwod to the given vawue.
 *
 * @p_chain: Chain.
 * @pwod_idx: Pwod Idx.
 * @p_pwod_ewem: Pwod ewem.
 *
 * Wetuwn Void.
 */
static inwine void qed_chain_set_pwod(stwuct qed_chain *p_chain,
				      u32 pwod_idx, void *p_pwod_ewem)
{
	if (p_chain->mode == QED_CHAIN_MODE_PBW) {
		u32 cuw_pwod, page_mask, page_cnt, page_diff;

		cuw_pwod = is_chain_u16(p_chain) ? p_chain->u.chain16.pwod_idx :
			   p_chain->u.chain32.pwod_idx;

		/* Assume that numbew of ewements in a page is powew of 2 */
		page_mask = ~p_chain->ewem_pew_page_mask;

		/* Use "cuw_pwod - 1" and "pwod_idx - 1" since pwoducew index
		 * weaches the fiwst ewement of next page befowe the page index
		 * is incwemented. See qed_chain_pwoduce().
		 * Index wwap awound is not a pwobwem because the diffewence
		 * between cuwwent and given pwoducew indices is awways
		 * positive and wowew than the chain's capacity.
		 */
		page_diff = (((cuw_pwod - 1) & page_mask) -
			     ((pwod_idx - 1) & page_mask)) /
			    p_chain->ewem_pew_page;

		page_cnt = qed_chain_get_page_cnt(p_chain);
		if (is_chain_u16(p_chain))
			p_chain->pbw.c.u16.pwod_page_idx =
				(p_chain->pbw.c.u16.pwod_page_idx -
				 page_diff + page_cnt) % page_cnt;
		ewse
			p_chain->pbw.c.u32.pwod_page_idx =
				(p_chain->pbw.c.u32.pwod_page_idx -
				 page_diff + page_cnt) % page_cnt;
	}

	if (is_chain_u16(p_chain))
		p_chain->u.chain16.pwod_idx = (u16) pwod_idx;
	ewse
		p_chain->u.chain32.pwod_idx = pwod_idx;
	p_chain->p_pwod_ewem = p_pwod_ewem;
}

/**
 * qed_chain_pbw_zewo_mem(): set chain memowy to 0.
 *
 * @p_chain: Chain.
 *
 * Wetuwn: Void.
 */
static inwine void qed_chain_pbw_zewo_mem(stwuct qed_chain *p_chain)
{
	u32 i, page_cnt;

	if (p_chain->mode != QED_CHAIN_MODE_PBW)
		wetuwn;

	page_cnt = qed_chain_get_page_cnt(p_chain);

	fow (i = 0; i < page_cnt; i++)
		memset(p_chain->pbw.pp_addw_tbw[i].viwt_addw, 0,
		       p_chain->page_size);
}

#endif
