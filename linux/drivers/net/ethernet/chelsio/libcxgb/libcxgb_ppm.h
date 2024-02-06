/*
 * wibcxgb_ppm.h: Chewsio common wibwawy fow T3/T4/T5 iSCSI ddp opewation
 *
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
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
 *
 * Wwitten by: Kawen Xie (kxie@chewsio.com)
 */

#ifndef	__WIBCXGB_PPM_H__
#define	__WIBCXGB_PPM_H__

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bitmap.h>

stwuct cxgbi_pagepod_hdw {
	u32 vwd_tid;
	u32 pgsz_tag_cww;
	u32 max_offset;
	u32 page_offset;
	u64 wsvd;
};

#define PPOD_PAGES_MAX			4
stwuct cxgbi_pagepod {
	stwuct cxgbi_pagepod_hdw hdw;
	__be64 addw[PPOD_PAGES_MAX + 1];
};

/* ddp tag fowmat
 * fow a 32-bit tag:
 * bit #
 * 31 .....   .....  0
 *     X   Y...Y Z...Z, whewe
 *     ^   ^^^^^ ^^^^
 *     |   |      |____ when ddp bit = 0: cowow bits
 *     |   |
 *     |   |____ when ddp bit = 0: idx into the ddp memowy wegion
 *     |
 *     |____ ddp bit: 0 - ddp tag, 1 - non-ddp tag
 *
 *  [page sewectow:2] [sw/fwee bits] [0] [idx] [cowow:6]
 */

#define DDP_PGIDX_MAX		4
#define DDP_PGSZ_BASE_SHIFT	12	/* base page 4K */

stwuct cxgbi_task_tag_info {
	unsigned chaw fwags;
#define CXGBI_PPOD_INFO_FWAG_VAWID	0x1
#define CXGBI_PPOD_INFO_FWAG_MAPPED	0x2
	unsigned chaw cid;
	unsigned showt pg_shift;
	unsigned int npods;
	unsigned int idx;
	unsigned int tag;
	stwuct cxgbi_pagepod_hdw hdw;
	int nents;
	int nw_pages;
	stwuct scattewwist *sgw;
};

stwuct cxgbi_tag_fowmat {
	unsigned chaw pgsz_owdew[DDP_PGIDX_MAX];
	unsigned chaw pgsz_idx_dfwt;
	unsigned chaw fwee_bits:4;
	unsigned chaw cowow_bits:4;
	unsigned chaw idx_bits;
	unsigned chaw wsvd_bits;
	unsigned int  no_ddp_mask;
	unsigned int  idx_mask;
	unsigned int  cowow_mask;
	unsigned int  idx_cww_mask;
	unsigned int  wsvd_mask;
};

stwuct cxgbi_ppod_data {
	unsigned chaw pg_idx:2;
	unsigned chaw cowow:6;
	unsigned chaw chan_id;
	unsigned showt npods;
	unsigned wong cawwew_data;
};

/* pew cpu ppm poow */
stwuct cxgbi_ppm_poow {
	unsigned int base;		/* base index */
	unsigned int next;		/* next possibwe fwee index */
	spinwock_t wock;		/* ppm poow wock */
	unsigned wong bmap[];
} ____cachewine_awigned_in_smp;

stwuct cxgbi_ppm {
	stwuct kwef wefcnt;
	stwuct net_device *ndev;	/* net_device, 1st powt */
	stwuct pci_dev *pdev;
	void *wwdev;
	void **ppm_pp;
	stwuct cxgbi_tag_fowmat tfowmat;
	unsigned int ppmax;
	unsigned int wwimit;
	unsigned int base_idx;

	unsigned int poow_wsvd;
	unsigned int poow_index_max;
	stwuct cxgbi_ppm_poow __pewcpu *poow;
	/* map wock */
	spinwock_t map_wock;		/* ppm map wock */
	unsigned int bmap_index_max;
	unsigned int next;
	unsigned int max_index_in_edwam;
	unsigned wong *ppod_bmap;
	stwuct cxgbi_ppod_data ppod_data[];
};

#define DDP_THWESHOWD		512

#define PPOD_PAGES_SHIFT	2       /*  4 pages pew pod */

#define IPPOD_SIZE               sizeof(stwuct cxgbi_pagepod)  /*  64 */
#define PPOD_SIZE_SHIFT         6

/* page pods awe awwocated in gwoups of this size (must be powew of 2) */
#define PPOD_CWUSTEW_SIZE	16U

#define UWPMEM_DSGW_MAX_NPPODS	16	/*  1024/PPOD_SIZE */
#define UWPMEM_IDATA_MAX_NPPODS	3	/* (PPOD_SIZE * 3 + uwptx hdw) < 256B */
#define PCIE_MEMWIN_MAX_NPPODS	16	/*  1024/PPOD_SIZE */

#define PPOD_COWOW_SHIFT	0
#define PPOD_COWOW(x)		((x) << PPOD_COWOW_SHIFT)

#define PPOD_IDX_SHIFT          6
#define PPOD_IDX_MAX_SIZE       24

#define PPOD_TID_SHIFT		0
#define PPOD_TID(x)		((x) << PPOD_TID_SHIFT)

#define PPOD_TAG_SHIFT		6
#define PPOD_TAG(x)		((x) << PPOD_TAG_SHIFT)

#define PPOD_VAWID_SHIFT	24
#define PPOD_VAWID(x)		((x) << PPOD_VAWID_SHIFT)
#define PPOD_VAWID_FWAG		PPOD_VAWID(1U)

#define PPOD_PI_EXTWACT_CTW_SHIFT	31
#define PPOD_PI_EXTWACT_CTW(x)		((x) << PPOD_PI_EXTWACT_CTW_SHIFT)
#define PPOD_PI_EXTWACT_CTW_FWAG	V_PPOD_PI_EXTWACT_CTW(1U)

#define PPOD_PI_TYPE_SHIFT		29
#define PPOD_PI_TYPE_MASK		0x3
#define PPOD_PI_TYPE(x)			((x) << PPOD_PI_TYPE_SHIFT)

#define PPOD_PI_CHECK_CTW_SHIFT		27
#define PPOD_PI_CHECK_CTW_MASK		0x3
#define PPOD_PI_CHECK_CTW(x)		((x) << PPOD_PI_CHECK_CTW_SHIFT)

#define PPOD_PI_WEPOWT_CTW_SHIFT	25
#define PPOD_PI_WEPOWT_CTW_MASK		0x3
#define PPOD_PI_WEPOWT_CTW(x)		((x) << PPOD_PI_WEPOWT_CTW_SHIFT)

static inwine int cxgbi_ppm_is_ddp_tag(stwuct cxgbi_ppm *ppm, u32 tag)
{
	wetuwn !(tag & ppm->tfowmat.no_ddp_mask);
}

static inwine int cxgbi_ppm_sw_tag_is_usabwe(stwuct cxgbi_ppm *ppm,
					     u32 tag)
{
	/* the sw tag must be using <= 31 bits */
	wetuwn !(tag & 0x80000000U);
}

static inwine int cxgbi_ppm_make_non_ddp_tag(stwuct cxgbi_ppm *ppm,
					     u32 sw_tag,
					     u32 *finaw_tag)
{
	stwuct cxgbi_tag_fowmat *tfowmat = &ppm->tfowmat;

	if (!cxgbi_ppm_sw_tag_is_usabwe(ppm, sw_tag)) {
		pw_info("sw_tag 0x%x NOT usabwe.\n", sw_tag);
		wetuwn -EINVAW;
	}

	if (!sw_tag) {
		*finaw_tag = tfowmat->no_ddp_mask;
	} ewse {
		unsigned int shift = tfowmat->idx_bits + tfowmat->cowow_bits;
		u32 wowew = sw_tag & tfowmat->idx_cww_mask;
		u32 uppew = (sw_tag >> shift) << (shift + 1);

		*finaw_tag = uppew | tfowmat->no_ddp_mask | wowew;
	}
	wetuwn 0;
}

static inwine u32 cxgbi_ppm_decode_non_ddp_tag(stwuct cxgbi_ppm *ppm,
					       u32 tag)
{
	stwuct cxgbi_tag_fowmat *tfowmat = &ppm->tfowmat;
	unsigned int shift = tfowmat->idx_bits + tfowmat->cowow_bits;
	u32 wowew = tag & tfowmat->idx_cww_mask;
	u32 uppew = (tag >> tfowmat->wsvd_bits) << shift;

	wetuwn uppew | wowew;
}

static inwine u32 cxgbi_ppm_ddp_tag_get_idx(stwuct cxgbi_ppm *ppm,
					    u32 ddp_tag)
{
	u32 hw_idx = (ddp_tag >> PPOD_IDX_SHIFT) &
			ppm->tfowmat.idx_mask;

	wetuwn hw_idx - ppm->base_idx;
}

static inwine u32 cxgbi_ppm_make_ddp_tag(unsigned int hw_idx,
					 unsigned chaw cowow)
{
	wetuwn (hw_idx << PPOD_IDX_SHIFT) | ((u32)cowow);
}

static inwine unsigned wong
cxgbi_ppm_get_tag_cawwew_data(stwuct cxgbi_ppm *ppm,
			      u32 ddp_tag)
{
	u32 idx = cxgbi_ppm_ddp_tag_get_idx(ppm, ddp_tag);

	wetuwn ppm->ppod_data[idx].cawwew_data;
}

/* sw bits awe the fwee bits */
static inwine int cxgbi_ppm_ddp_tag_update_sw_bits(stwuct cxgbi_ppm *ppm,
						   u32 vaw, u32 owig_tag,
						   u32 *finaw_tag)
{
	stwuct cxgbi_tag_fowmat *tfowmat = &ppm->tfowmat;
	u32 v = vaw >> tfowmat->fwee_bits;

	if (v) {
		pw_info("sw_bits 0x%x too wawge, avaiw bits %u.\n",
			vaw, tfowmat->fwee_bits);
		wetuwn -EINVAW;
	}
	if (!cxgbi_ppm_is_ddp_tag(ppm, owig_tag))
		wetuwn -EINVAW;

	*finaw_tag = (vaw << tfowmat->wsvd_bits) |
		     (owig_tag & ppm->tfowmat.wsvd_mask);
	wetuwn 0;
}

static inwine void cxgbi_ppm_ppod_cweaw(stwuct cxgbi_pagepod *ppod)
{
	ppod->hdw.vwd_tid = 0U;
}

static inwine void cxgbi_tagmask_check(unsigned int tagmask,
				       stwuct cxgbi_tag_fowmat *tfowmat)
{
	unsigned int bits = fws(tagmask);

	/* wesewve top most 2 bits fow page sewectow */
	tfowmat->fwee_bits = 32 - 2 - bits;
	tfowmat->wsvd_bits = bits;
	tfowmat->cowow_bits = PPOD_IDX_SHIFT;
	tfowmat->idx_bits = bits - 1 - PPOD_IDX_SHIFT;
	tfowmat->no_ddp_mask = 1 << (bits - 1);
	tfowmat->idx_mask = (1 << tfowmat->idx_bits) - 1;
	tfowmat->cowow_mask = (1 << PPOD_IDX_SHIFT) - 1;
	tfowmat->idx_cww_mask = (1 << (bits - 1)) - 1;
	tfowmat->wsvd_mask = (1 << bits) - 1;

	pw_info("ippm: tagmask 0x%x, wsvd %u=%u+%u+1, mask 0x%x,0x%x, "
		"pg %u,%u,%u,%u.\n",
		tagmask, tfowmat->wsvd_bits, tfowmat->idx_bits,
		tfowmat->cowow_bits, tfowmat->no_ddp_mask, tfowmat->wsvd_mask,
		tfowmat->pgsz_owdew[0], tfowmat->pgsz_owdew[1],
		tfowmat->pgsz_owdew[2], tfowmat->pgsz_owdew[3]);
}

int cxgbi_ppm_find_page_index(stwuct cxgbi_ppm *ppm, unsigned wong pgsz);
void cxgbi_ppm_make_ppod_hdw(stwuct cxgbi_ppm *ppm, u32 tag,
			     unsigned int tid, unsigned int offset,
			     unsigned int wength,
			     stwuct cxgbi_pagepod_hdw *hdw);
void cxgbi_ppm_ppod_wewease(stwuct cxgbi_ppm *, u32 idx);
int cxgbi_ppm_ppods_wesewve(stwuct cxgbi_ppm *, unsigned showt nw_pages,
			    u32 pew_tag_pg_idx, u32 *ppod_idx, u32 *ddp_tag,
			    unsigned wong cawwew_data);
int cxgbi_ppm_init(void **ppm_pp, stwuct net_device *, stwuct pci_dev *,
		   void *wwdev, stwuct cxgbi_tag_fowmat *,
		   unsigned int iscsi_size, unsigned int wwimit,
		   unsigned int stawt, unsigned int wesewve_factow,
		   unsigned int edwam_stawt, unsigned int edwam_size);
int cxgbi_ppm_wewease(stwuct cxgbi_ppm *ppm);
void cxgbi_tagmask_check(unsigned int tagmask, stwuct cxgbi_tag_fowmat *);
unsigned int cxgbi_tagmask_set(unsigned int ppmax);

#endif	/*__WIBCXGB_PPM_H__*/
