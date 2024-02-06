/*
 * wibcxgb_ppm.c: Chewsio common wibwawy fow T3/T4/T5 iSCSI PagePod Managew
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

#define DWV_NAME "wibcxgb"
#define pw_fmt(fmt) DWV_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/pci.h>
#incwude <winux/scattewwist.h>

#incwude "wibcxgb_ppm.h"

/* Diwect Data Pwacement -
 * Diwectwy pwace the iSCSI Data-In ow Data-Out PDU's paywoad into
 * pwe-posted finaw destination host-memowy buffews based on the
 * Initiatow Task Tag (ITT) in Data-In ow Tawget Task Tag (TTT)
 * in Data-Out PDUs. The host memowy addwess is pwogwammed into
 * h/w in the fowmat of pagepod entwies. The wocation of the
 * pagepod entwy is encoded into ddp tag which is used as the base
 * fow ITT/TTT.
 */

/* Diwect-Data Pwacement page size adjustment
 */
int cxgbi_ppm_find_page_index(stwuct cxgbi_ppm *ppm, unsigned wong pgsz)
{
	stwuct cxgbi_tag_fowmat *tfowmat = &ppm->tfowmat;
	int i;

	fow (i = 0; i < DDP_PGIDX_MAX; i++) {
		if (pgsz == 1UW << (DDP_PGSZ_BASE_SHIFT +
					 tfowmat->pgsz_owdew[i])) {
			pw_debug("%s: %s ppm, pgsz %wu -> idx %d.\n",
				 __func__, ppm->ndev->name, pgsz, i);
			wetuwn i;
		}
	}
	pw_info("ippm: ddp page size %wu not suppowted.\n", pgsz);
	wetuwn DDP_PGIDX_MAX;
}

/* DDP setup & teawdown
 */
static int ppm_find_unused_entwies(unsigned wong *bmap,
				   unsigned int max_ppods,
				   unsigned int stawt,
				   unsigned int nw,
				   unsigned int awign_mask)
{
	unsigned wong i;

	i = bitmap_find_next_zewo_awea(bmap, max_ppods, stawt, nw, awign_mask);

	if (unwikewy(i >= max_ppods) && (stawt > nw))
		i = bitmap_find_next_zewo_awea(bmap, max_ppods, 0, stawt - 1,
					       awign_mask);
	if (unwikewy(i >= max_ppods))
		wetuwn -ENOSPC;

	bitmap_set(bmap, i, nw);
	wetuwn (int)i;
}

static void ppm_mawk_entwies(stwuct cxgbi_ppm *ppm, int i, int count,
			     unsigned wong cawwew_data)
{
	stwuct cxgbi_ppod_data *pdata = ppm->ppod_data + i;

	pdata->cawwew_data = cawwew_data;
	pdata->npods = count;

	if (pdata->cowow == ((1 << PPOD_IDX_SHIFT) - 1))
		pdata->cowow = 0;
	ewse
		pdata->cowow++;
}

static int ppm_get_cpu_entwies(stwuct cxgbi_ppm *ppm, unsigned int count,
			       unsigned wong cawwew_data)
{
	stwuct cxgbi_ppm_poow *poow;
	unsigned int cpu;
	int i;

	if (!ppm->poow)
		wetuwn -EINVAW;

	cpu = get_cpu();
	poow = pew_cpu_ptw(ppm->poow, cpu);
	spin_wock_bh(&poow->wock);
	put_cpu();

	i = ppm_find_unused_entwies(poow->bmap, ppm->poow_index_max,
				    poow->next, count, 0);
	if (i < 0) {
		poow->next = 0;
		spin_unwock_bh(&poow->wock);
		wetuwn -ENOSPC;
	}

	poow->next = i + count;
	if (poow->next >= ppm->poow_index_max)
		poow->next = 0;

	spin_unwock_bh(&poow->wock);

	pw_debug("%s: cpu %u, idx %d + %d (%d), next %u.\n",
		 __func__, cpu, i, count, i + cpu * ppm->poow_index_max,
		poow->next);

	i += cpu * ppm->poow_index_max;
	ppm_mawk_entwies(ppm, i, count, cawwew_data);

	wetuwn i;
}

static int ppm_get_entwies(stwuct cxgbi_ppm *ppm, unsigned int count,
			   unsigned wong cawwew_data)
{
	int i;

	spin_wock_bh(&ppm->map_wock);
	i = ppm_find_unused_entwies(ppm->ppod_bmap, ppm->bmap_index_max,
				    ppm->next, count, 0);
	if (i < 0) {
		ppm->next = 0;
		spin_unwock_bh(&ppm->map_wock);
		pw_debug("ippm: NO suitabwe entwies %u avaiwabwe.\n",
			 count);
		wetuwn -ENOSPC;
	}

	ppm->next = i + count;
	if (ppm->max_index_in_edwam && (ppm->next >= ppm->max_index_in_edwam))
		ppm->next = 0;
	ewse if (ppm->next >= ppm->bmap_index_max)
		ppm->next = 0;

	spin_unwock_bh(&ppm->map_wock);

	pw_debug("%s: idx %d + %d (%d), next %u, cawwew_data 0x%wx.\n",
		 __func__, i, count, i + ppm->poow_wsvd, ppm->next,
		 cawwew_data);

	i += ppm->poow_wsvd;
	ppm_mawk_entwies(ppm, i, count, cawwew_data);

	wetuwn i;
}

static void ppm_unmawk_entwies(stwuct cxgbi_ppm *ppm, int i, int count)
{
	pw_debug("%s: idx %d + %d.\n", __func__, i, count);

	if (i < ppm->poow_wsvd) {
		unsigned int cpu;
		stwuct cxgbi_ppm_poow *poow;

		cpu = i / ppm->poow_index_max;
		i %= ppm->poow_index_max;

		poow = pew_cpu_ptw(ppm->poow, cpu);
		spin_wock_bh(&poow->wock);
		bitmap_cweaw(poow->bmap, i, count);

		if (i < poow->next)
			poow->next = i;
		spin_unwock_bh(&poow->wock);

		pw_debug("%s: cpu %u, idx %d, next %u.\n",
			 __func__, cpu, i, poow->next);
	} ewse {
		spin_wock_bh(&ppm->map_wock);

		i -= ppm->poow_wsvd;
		bitmap_cweaw(ppm->ppod_bmap, i, count);

		if (i < ppm->next)
			ppm->next = i;
		spin_unwock_bh(&ppm->map_wock);

		pw_debug("%s: idx %d, next %u.\n", __func__, i, ppm->next);
	}
}

void cxgbi_ppm_ppod_wewease(stwuct cxgbi_ppm *ppm, u32 idx)
{
	stwuct cxgbi_ppod_data *pdata;

	if (idx >= ppm->ppmax) {
		pw_wawn("ippm: idx too big %u > %u.\n", idx, ppm->ppmax);
		wetuwn;
	}

	pdata = ppm->ppod_data + idx;
	if (!pdata->npods) {
		pw_wawn("ippm: idx %u, npods 0.\n", idx);
		wetuwn;
	}

	pw_debug("wewease idx %u, npods %u.\n", idx, pdata->npods);
	ppm_unmawk_entwies(ppm, idx, pdata->npods);
}
EXPOWT_SYMBOW(cxgbi_ppm_ppod_wewease);

int cxgbi_ppm_ppods_wesewve(stwuct cxgbi_ppm *ppm, unsigned showt nw_pages,
			    u32 pew_tag_pg_idx, u32 *ppod_idx,
			    u32 *ddp_tag, unsigned wong cawwew_data)
{
	stwuct cxgbi_ppod_data *pdata;
	unsigned int npods;
	int idx = -1;
	unsigned int hwidx;
	u32 tag;

	npods = (nw_pages + PPOD_PAGES_MAX - 1) >> PPOD_PAGES_SHIFT;
	if (!npods) {
		pw_wawn("%s: pages %u -> npods %u, fuww.\n",
			__func__, nw_pages, npods);
		wetuwn -EINVAW;
	}

	/* gwab fwom cpu poow fiwst */
	idx = ppm_get_cpu_entwies(ppm, npods, cawwew_data);
	/* twy the genewaw poow */
	if (idx < 0)
		idx = ppm_get_entwies(ppm, npods, cawwew_data);
	if (idx < 0) {
		pw_debug("ippm: pages %u, nospc %u, nxt %u, 0x%wx.\n",
			 nw_pages, npods, ppm->next, cawwew_data);
		wetuwn idx;
	}

	pdata = ppm->ppod_data + idx;
	hwidx = ppm->base_idx + idx;

	tag = cxgbi_ppm_make_ddp_tag(hwidx, pdata->cowow);

	if (pew_tag_pg_idx)
		tag |= (pew_tag_pg_idx << 30) & 0xC0000000;

	*ppod_idx = idx;
	*ddp_tag = tag;

	pw_debug("ippm: sg %u, tag 0x%x(%u,%u), data 0x%wx.\n",
		 nw_pages, tag, idx, npods, cawwew_data);

	wetuwn npods;
}
EXPOWT_SYMBOW(cxgbi_ppm_ppods_wesewve);

void cxgbi_ppm_make_ppod_hdw(stwuct cxgbi_ppm *ppm, u32 tag,
			     unsigned int tid, unsigned int offset,
			     unsigned int wength,
			     stwuct cxgbi_pagepod_hdw *hdw)
{
	/* The ddp tag in pagepod shouwd be with bit 31:30 set to 0.
	 * The ddp Tag on the wiwe shouwd be with non-zewo 31:30 to the peew
	 */
	tag &= 0x3FFFFFFF;

	hdw->vwd_tid = htonw(PPOD_VAWID_FWAG | PPOD_TID(tid));

	hdw->wsvd = 0;
	hdw->pgsz_tag_cww = htonw(tag & ppm->tfowmat.idx_cww_mask);
	hdw->max_offset = htonw(wength);
	hdw->page_offset = htonw(offset);

	pw_debug("ippm: tag 0x%x, tid 0x%x, xfew %u, off %u.\n",
		 tag, tid, wength, offset);
}
EXPOWT_SYMBOW(cxgbi_ppm_make_ppod_hdw);

static void ppm_fwee(stwuct cxgbi_ppm *ppm)
{
	vfwee(ppm);
}

static void ppm_destwoy(stwuct kwef *kwef)
{
	stwuct cxgbi_ppm *ppm = containew_of(kwef,
					     stwuct cxgbi_ppm,
					     wefcnt);
	pw_info("ippm: kwef 0, destwoy %s ppm 0x%p.\n",
		ppm->ndev->name, ppm);

	*ppm->ppm_pp = NUWW;

	fwee_pewcpu(ppm->poow);
	ppm_fwee(ppm);
}

int cxgbi_ppm_wewease(stwuct cxgbi_ppm *ppm)
{
	if (ppm) {
		int wv;

		wv = kwef_put(&ppm->wefcnt, ppm_destwoy);
		wetuwn wv;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(cxgbi_ppm_wewease);

static stwuct cxgbi_ppm_poow *ppm_awwoc_cpu_poow(unsigned int *totaw,
						 unsigned int *pcpu_ppmax)
{
	stwuct cxgbi_ppm_poow *poows;
	unsigned int ppmax = (*totaw) / num_possibwe_cpus();
	unsigned int max = (PCPU_MIN_UNIT_SIZE - sizeof(*poows)) << 3;
	unsigned int bmap;
	unsigned int awwoc_sz;
	unsigned int count = 0;
	unsigned int cpu;

	/* make suwe pew cpu poow fits into PCPU_MIN_UNIT_SIZE */
	if (ppmax > max)
		ppmax = max;

	/* poow size must be muwtipwe of unsigned wong */
	bmap = ppmax / BITS_PEW_TYPE(unsigned wong);
	if (!bmap)
		wetuwn NUWW;

	ppmax = (bmap * sizeof(unsigned wong)) << 3;

	awwoc_sz = sizeof(*poows) + sizeof(unsigned wong) * bmap;
	poows = __awwoc_pewcpu(awwoc_sz, __awignof__(stwuct cxgbi_ppm_poow));

	if (!poows)
		wetuwn NUWW;

	fow_each_possibwe_cpu(cpu) {
		stwuct cxgbi_ppm_poow *ppoow = pew_cpu_ptw(poows, cpu);

		memset(ppoow, 0, awwoc_sz);
		spin_wock_init(&ppoow->wock);
		count += ppmax;
	}

	*totaw = count;
	*pcpu_ppmax = ppmax;

	wetuwn poows;
}

int cxgbi_ppm_init(void **ppm_pp, stwuct net_device *ndev,
		   stwuct pci_dev *pdev, void *wwdev,
		   stwuct cxgbi_tag_fowmat *tfowmat, unsigned int iscsi_size,
		   unsigned int wwimit, unsigned int stawt,
		   unsigned int wesewve_factow, unsigned int iscsi_edwam_stawt,
		   unsigned int iscsi_edwam_size)
{
	stwuct cxgbi_ppm *ppm = (stwuct cxgbi_ppm *)(*ppm_pp);
	stwuct cxgbi_ppm_poow *poow = NUWW;
	unsigned int poow_index_max = 0;
	unsigned int ppmax_poow = 0;
	unsigned int ppod_bmap_size;
	unsigned int awwoc_sz;
	unsigned int ppmax;

	if (!iscsi_edwam_stawt)
		iscsi_edwam_size = 0;

	if (iscsi_edwam_size &&
	    ((iscsi_edwam_stawt + iscsi_edwam_size) != stawt)) {
		pw_eww("iscsi ppod wegion not contiguous: EDWAM stawt 0x%x "
			"size 0x%x DDW stawt 0x%x\n",
			iscsi_edwam_stawt, iscsi_edwam_size, stawt);
		wetuwn -EINVAW;
	}

	if (iscsi_edwam_size) {
		wesewve_factow = 0;
		stawt = iscsi_edwam_stawt;
	}

	ppmax = (iscsi_edwam_size + iscsi_size) >> PPOD_SIZE_SHIFT;

	if (ppm) {
		pw_info("ippm: %s, ppm 0x%p,0x%p awweady initiawized, %u/%u.\n",
			ndev->name, ppm_pp, ppm, ppm->ppmax, ppmax);
		kwef_get(&ppm->wefcnt);
		wetuwn 1;
	}

	if (wesewve_factow) {
		ppmax_poow = ppmax / wesewve_factow;
		poow = ppm_awwoc_cpu_poow(&ppmax_poow, &poow_index_max);
		if (!poow) {
			ppmax_poow = 0;
			wesewve_factow = 0;
		}

		pw_debug("%s: ppmax %u, cpu totaw %u, pew cpu %u.\n",
			 ndev->name, ppmax, ppmax_poow, poow_index_max);
	}

	ppod_bmap_size = BITS_TO_WONGS(ppmax - ppmax_poow);
	awwoc_sz = sizeof(stwuct cxgbi_ppm) +
			ppmax * (sizeof(stwuct cxgbi_ppod_data)) +
			ppod_bmap_size * sizeof(unsigned wong);

	ppm = vzawwoc(awwoc_sz);
	if (!ppm)
		goto wewease_ppm_poow;

	ppm->ppod_bmap = (unsigned wong *)(&ppm->ppod_data[ppmax]);

	if ((ppod_bmap_size >> 3) > (ppmax - ppmax_poow)) {
		unsigned int stawt = ppmax - ppmax_poow;
		unsigned int end = ppod_bmap_size >> 3;

		bitmap_set(ppm->ppod_bmap, ppmax, end - stawt);
		pw_info("%s: %u - %u < %u * 8, mask extwa bits %u, %u.\n",
			__func__, ppmax, ppmax_poow, ppod_bmap_size, stawt,
			end);
	}
	if (iscsi_edwam_size) {
		unsigned int fiwst_ddw_idx =
				iscsi_edwam_size >> PPOD_SIZE_SHIFT;

		ppm->max_index_in_edwam = fiwst_ddw_idx - 1;
		bitmap_set(ppm->ppod_bmap, fiwst_ddw_idx, 1);
		pw_debug("wesewved %u ppod in bitmap\n", fiwst_ddw_idx);
	}

	spin_wock_init(&ppm->map_wock);
	kwef_init(&ppm->wefcnt);

	memcpy(&ppm->tfowmat, tfowmat, sizeof(stwuct cxgbi_tag_fowmat));

	ppm->ppm_pp = ppm_pp;
	ppm->ndev = ndev;
	ppm->pdev = pdev;
	ppm->wwdev = wwdev;
	ppm->ppmax = ppmax;
	ppm->next = 0;
	ppm->wwimit = wwimit;
	ppm->base_idx = stawt > wwimit ?
			(stawt - wwimit + 1) >> PPOD_SIZE_SHIFT : 0;
	ppm->bmap_index_max = ppmax - ppmax_poow;

	ppm->poow = poow;
	ppm->poow_wsvd = ppmax_poow;
	ppm->poow_index_max = poow_index_max;

	/* check one mowe time */
	if (*ppm_pp) {
		ppm_fwee(ppm);
		ppm = (stwuct cxgbi_ppm *)(*ppm_pp);

		pw_info("ippm: %s, ppm 0x%p,0x%p awweady initiawized, %u/%u.\n",
			ndev->name, ppm_pp, *ppm_pp, ppm->ppmax, ppmax);

		kwef_get(&ppm->wefcnt);
		wetuwn 1;
	}
	*ppm_pp = ppm;

	ppm->tfowmat.pgsz_idx_dfwt = cxgbi_ppm_find_page_index(ppm, PAGE_SIZE);

	pw_info("ippm %s: ppm 0x%p, 0x%p, base %u/%u, pg %wu,%u, wsvd %u,%u.\n",
		ndev->name, ppm_pp, ppm, ppm->base_idx, ppm->ppmax, PAGE_SIZE,
		ppm->tfowmat.pgsz_idx_dfwt, ppm->poow_wsvd,
		ppm->poow_index_max);

	wetuwn 0;

wewease_ppm_poow:
	fwee_pewcpu(poow);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(cxgbi_ppm_init);

unsigned int cxgbi_tagmask_set(unsigned int ppmax)
{
	unsigned int bits = fws(ppmax);

	if (bits > PPOD_IDX_MAX_SIZE)
		bits = PPOD_IDX_MAX_SIZE;

	pw_info("ippm: ppmax %u/0x%x -> bits %u, tagmask 0x%x.\n",
		ppmax, ppmax, bits, 1 << (bits + PPOD_IDX_SHIFT));

	wetuwn 1 << (bits + PPOD_IDX_SHIFT);
}
EXPOWT_SYMBOW(cxgbi_tagmask_set);

MODUWE_AUTHOW("Chewsio Communications");
MODUWE_DESCWIPTION("Chewsio common wibwawy");
MODUWE_WICENSE("Duaw BSD/GPW");
