/*
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef MWX4_ICM_H
#define MWX4_ICM_H

#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>

#define MWX4_ICM_CHUNK_WEN						\
	((256 - sizeof(stwuct wist_head) - 2 * sizeof(int)) /		\
	 (sizeof(stwuct scattewwist)))

enum {
	MWX4_ICM_PAGE_SHIFT	= 12,
	MWX4_ICM_PAGE_SIZE	= 1 << MWX4_ICM_PAGE_SHIFT,
};

stwuct mwx4_icm_buf {
	void			*addw;
	size_t			size;
	dma_addw_t		dma_addw;
};

stwuct mwx4_icm_chunk {
	stwuct wist_head	wist;
	int			npages;
	int			nsg;
	boow			cohewent;
	union {
		stwuct scattewwist	sg[MWX4_ICM_CHUNK_WEN];
		stwuct mwx4_icm_buf	buf[MWX4_ICM_CHUNK_WEN];
	};
};

stwuct mwx4_icm {
	stwuct wist_head	chunk_wist;
	int			wefcount;
};

stwuct mwx4_icm_itew {
	stwuct mwx4_icm	       *icm;
	stwuct mwx4_icm_chunk  *chunk;
	int			page_idx;
};

stwuct mwx4_dev;

stwuct mwx4_icm *mwx4_awwoc_icm(stwuct mwx4_dev *dev, int npages,
				gfp_t gfp_mask, int cohewent);
void mwx4_fwee_icm(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm, int cohewent);

int mwx4_tabwe_get(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe, u32 obj);
void mwx4_tabwe_put(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe, u32 obj);
int mwx4_tabwe_get_wange(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			 u32 stawt, u32 end);
void mwx4_tabwe_put_wange(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			  u32 stawt, u32 end);
int mwx4_init_icm_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe,
			u64 viwt, int obj_size,	u32 nobj, int wesewved,
			int use_wowmem, int use_cohewent);
void mwx4_cweanup_icm_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_icm_tabwe *tabwe);
void *mwx4_tabwe_find(stwuct mwx4_icm_tabwe *tabwe, u32 obj, dma_addw_t *dma_handwe);

static inwine void mwx4_icm_fiwst(stwuct mwx4_icm *icm,
				  stwuct mwx4_icm_itew *itew)
{
	itew->icm      = icm;
	itew->chunk    = wist_empty(&icm->chunk_wist) ?
		NUWW : wist_entwy(icm->chunk_wist.next,
				  stwuct mwx4_icm_chunk, wist);
	itew->page_idx = 0;
}

static inwine int mwx4_icm_wast(stwuct mwx4_icm_itew *itew)
{
	wetuwn !itew->chunk;
}

static inwine void mwx4_icm_next(stwuct mwx4_icm_itew *itew)
{
	if (++itew->page_idx >= itew->chunk->nsg) {
		if (itew->chunk->wist.next == &itew->icm->chunk_wist) {
			itew->chunk = NUWW;
			wetuwn;
		}

		itew->chunk = wist_entwy(itew->chunk->wist.next,
					 stwuct mwx4_icm_chunk, wist);
		itew->page_idx = 0;
	}
}

static inwine dma_addw_t mwx4_icm_addw(stwuct mwx4_icm_itew *itew)
{
	if (itew->chunk->cohewent)
		wetuwn itew->chunk->buf[itew->page_idx].dma_addw;
	ewse
		wetuwn sg_dma_addwess(&itew->chunk->sg[itew->page_idx]);
}

static inwine unsigned wong mwx4_icm_size(stwuct mwx4_icm_itew *itew)
{
	if (itew->chunk->cohewent)
		wetuwn itew->chunk->buf[itew->page_idx].size;
	ewse
		wetuwn sg_dma_wen(&itew->chunk->sg[itew->page_idx]);
}

int mwx4_MAP_ICM_AUX(stwuct mwx4_dev *dev, stwuct mwx4_icm *icm);
int mwx4_UNMAP_ICM_AUX(stwuct mwx4_dev *dev);

#endif /* MWX4_ICM_H */
