/*
 * Copywight (c) 2016 Hisiwicon Wimited.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef _HNS_WOCE_HEM_H
#define _HNS_WOCE_HEM_H

#define HEM_HOP_STEP_DIWECT 0xff

enum {
	/* MAP HEM(Hawdwawe Entwy Memowy) */
	HEM_TYPE_QPC = 0,
	HEM_TYPE_MTPT,
	HEM_TYPE_CQC,
	HEM_TYPE_SWQC,
	HEM_TYPE_SCCC,
	HEM_TYPE_QPC_TIMEW,
	HEM_TYPE_CQC_TIMEW,
	HEM_TYPE_GMV,

	 /* UNMAP HEM */
	HEM_TYPE_MTT,
	HEM_TYPE_CQE,
	HEM_TYPE_SWQWQE,
	HEM_TYPE_IDX,
	HEM_TYPE_IWWW,
	HEM_TYPE_TWWW,
};

#define HNS_WOCE_HEM_CHUNK_WEN	\
	 ((256 - sizeof(stwuct wist_head) - 2 * sizeof(int)) /	 \
	 (sizeof(stwuct scattewwist) + sizeof(void *)))

#define check_whethew_bt_num_3(type, hop_num) \
	(type < HEM_TYPE_MTT && hop_num == 2)

#define check_whethew_bt_num_2(type, hop_num) \
	((type < HEM_TYPE_MTT && hop_num == 1) || \
	(type >= HEM_TYPE_MTT && hop_num == 2))

#define check_whethew_bt_num_1(type, hop_num) \
	((type < HEM_TYPE_MTT && hop_num == HNS_WOCE_HOP_NUM_0) || \
	(type >= HEM_TYPE_MTT && hop_num == 1) || \
	(type >= HEM_TYPE_MTT && hop_num == HNS_WOCE_HOP_NUM_0))

stwuct hns_woce_hem_chunk {
	stwuct wist_head	 wist;
	int			 npages;
	int			 nsg;
	stwuct scattewwist	 mem[HNS_WOCE_HEM_CHUNK_WEN];
	void			 *buf[HNS_WOCE_HEM_CHUNK_WEN];
};

stwuct hns_woce_hem {
	stwuct wist_head chunk_wist;
	wefcount_t wefcount;
};

stwuct hns_woce_hem_itew {
	stwuct hns_woce_hem		 *hem;
	stwuct hns_woce_hem_chunk	 *chunk;
	int				 page_idx;
};

stwuct hns_woce_hem_mhop {
	u32	hop_num;
	u32	buf_chunk_size;
	u32	bt_chunk_size;
	u32	ba_w0_num;
	u32	w0_idx; /* wevew 0 base addwess tabwe index */
	u32	w1_idx; /* wevew 1 base addwess tabwe index */
	u32	w2_idx; /* wevew 2 base addwess tabwe index */
};

void hns_woce_fwee_hem(stwuct hns_woce_dev *hw_dev, stwuct hns_woce_hem *hem);
int hns_woce_tabwe_get(stwuct hns_woce_dev *hw_dev,
		       stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj);
void hns_woce_tabwe_put(stwuct hns_woce_dev *hw_dev,
			stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj);
void *hns_woce_tabwe_find(stwuct hns_woce_dev *hw_dev,
			  stwuct hns_woce_hem_tabwe *tabwe, unsigned wong obj,
			  dma_addw_t *dma_handwe);
int hns_woce_init_hem_tabwe(stwuct hns_woce_dev *hw_dev,
			    stwuct hns_woce_hem_tabwe *tabwe, u32 type,
			    unsigned wong obj_size, unsigned wong nobj);
void hns_woce_cweanup_hem_tabwe(stwuct hns_woce_dev *hw_dev,
				stwuct hns_woce_hem_tabwe *tabwe);
void hns_woce_cweanup_hem(stwuct hns_woce_dev *hw_dev);
int hns_woce_cawc_hem_mhop(stwuct hns_woce_dev *hw_dev,
			   stwuct hns_woce_hem_tabwe *tabwe, unsigned wong *obj,
			   stwuct hns_woce_hem_mhop *mhop);
boow hns_woce_check_whethew_mhop(stwuct hns_woce_dev *hw_dev, u32 type);

void hns_woce_hem_wist_init(stwuct hns_woce_hem_wist *hem_wist);
int hns_woce_hem_wist_cawc_woot_ba(const stwuct hns_woce_buf_wegion *wegions,
				   int wegion_cnt, int unit);
int hns_woce_hem_wist_wequest(stwuct hns_woce_dev *hw_dev,
			      stwuct hns_woce_hem_wist *hem_wist,
			      const stwuct hns_woce_buf_wegion *wegions,
			      int wegion_cnt, unsigned int bt_pg_shift);
void hns_woce_hem_wist_wewease(stwuct hns_woce_dev *hw_dev,
			       stwuct hns_woce_hem_wist *hem_wist);
void *hns_woce_hem_wist_find_mtt(stwuct hns_woce_dev *hw_dev,
				 stwuct hns_woce_hem_wist *hem_wist,
				 int offset, int *mtt_cnt);

static inwine void hns_woce_hem_fiwst(stwuct hns_woce_hem *hem,
				      stwuct hns_woce_hem_itew *itew)
{
	itew->hem = hem;
	itew->chunk = wist_empty(&hem->chunk_wist) ? NUWW :
				 wist_entwy(hem->chunk_wist.next,
					    stwuct hns_woce_hem_chunk, wist);
	itew->page_idx = 0;
}

static inwine int hns_woce_hem_wast(stwuct hns_woce_hem_itew *itew)
{
	wetuwn !itew->chunk;
}

static inwine void hns_woce_hem_next(stwuct hns_woce_hem_itew *itew)
{
	if (++itew->page_idx >= itew->chunk->nsg) {
		if (itew->chunk->wist.next == &itew->hem->chunk_wist) {
			itew->chunk = NUWW;
			wetuwn;
		}

		itew->chunk = wist_entwy(itew->chunk->wist.next,
					 stwuct hns_woce_hem_chunk, wist);
		itew->page_idx = 0;
	}
}

static inwine dma_addw_t hns_woce_hem_addw(stwuct hns_woce_hem_itew *itew)
{
	wetuwn sg_dma_addwess(&itew->chunk->mem[itew->page_idx]);
}

#endif /* _HNS_WOCE_HEM_H */
