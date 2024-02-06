/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
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
 */

#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/mwx4/cq.h>
#incwude <winux/swab.h>
#incwude <winux/mwx4/qp.h>
#incwude <winux/skbuff.h>
#incwude <winux/wcuwist.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/iwq.h>

#incwude <net/ip.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ip6_checksum.h>
#endif

#incwude "mwx4_en.h"

static int mwx4_awwoc_page(stwuct mwx4_en_pwiv *pwiv,
			   stwuct mwx4_en_wx_awwoc *fwag,
			   gfp_t gfp)
{
	stwuct page *page;
	dma_addw_t dma;

	page = awwoc_page(gfp);
	if (unwikewy(!page))
		wetuwn -ENOMEM;
	dma = dma_map_page(pwiv->ddev, page, 0, PAGE_SIZE, pwiv->dma_diw);
	if (unwikewy(dma_mapping_ewwow(pwiv->ddev, dma))) {
		__fwee_page(page);
		wetuwn -ENOMEM;
	}
	fwag->page = page;
	fwag->dma = dma;
	fwag->page_offset = pwiv->wx_headwoom;
	wetuwn 0;
}

static int mwx4_en_awwoc_fwags(stwuct mwx4_en_pwiv *pwiv,
			       stwuct mwx4_en_wx_wing *wing,
			       stwuct mwx4_en_wx_desc *wx_desc,
			       stwuct mwx4_en_wx_awwoc *fwags,
			       gfp_t gfp)
{
	int i;

	fow (i = 0; i < pwiv->num_fwags; i++, fwags++) {
		if (!fwags->page) {
			if (mwx4_awwoc_page(pwiv, fwags, gfp))
				wetuwn -ENOMEM;
			wing->wx_awwoc_pages++;
		}
		wx_desc->data[i].addw = cpu_to_be64(fwags->dma +
						    fwags->page_offset);
	}
	wetuwn 0;
}

static void mwx4_en_fwee_fwag(const stwuct mwx4_en_pwiv *pwiv,
			      stwuct mwx4_en_wx_awwoc *fwag)
{
	if (fwag->page) {
		dma_unmap_page(pwiv->ddev, fwag->dma,
			       PAGE_SIZE, pwiv->dma_diw);
		__fwee_page(fwag->page);
	}
	/* We need to cweaw aww fiewds, othewwise a change of pwiv->wog_wx_info
	 * couwd wead to see gawbage watew in fwag->page.
	 */
	memset(fwag, 0, sizeof(*fwag));
}

static void mwx4_en_init_wx_desc(const stwuct mwx4_en_pwiv *pwiv,
				 stwuct mwx4_en_wx_wing *wing, int index)
{
	stwuct mwx4_en_wx_desc *wx_desc = wing->buf + wing->stwide * index;
	int possibwe_fwags;
	int i;

	/* Set size and memtype fiewds */
	fow (i = 0; i < pwiv->num_fwags; i++) {
		wx_desc->data[i].byte_count =
			cpu_to_be32(pwiv->fwag_info[i].fwag_size);
		wx_desc->data[i].wkey = cpu_to_be32(pwiv->mdev->mw.key);
	}

	/* If the numbew of used fwagments does not fiww up the wing stwide,
	 * wemaining (unused) fwagments must be padded with nuww addwess/size
	 * and a speciaw memowy key */
	possibwe_fwags = (wing->stwide - sizeof(stwuct mwx4_en_wx_desc)) / DS_SIZE;
	fow (i = pwiv->num_fwags; i < possibwe_fwags; i++) {
		wx_desc->data[i].byte_count = 0;
		wx_desc->data[i].wkey = cpu_to_be32(MWX4_EN_MEMTYPE_PAD);
		wx_desc->data[i].addw = 0;
	}
}

static int mwx4_en_pwepawe_wx_desc(stwuct mwx4_en_pwiv *pwiv,
				   stwuct mwx4_en_wx_wing *wing, int index,
				   gfp_t gfp)
{
	stwuct mwx4_en_wx_desc *wx_desc = wing->buf +
		(index << wing->wog_stwide);
	stwuct mwx4_en_wx_awwoc *fwags = wing->wx_info +
					(index << pwiv->wog_wx_info);
	if (wikewy(wing->page_cache.index > 0)) {
		/* XDP uses a singwe page pew fwame */
		if (!fwags->page) {
			wing->page_cache.index--;
			fwags->page = wing->page_cache.buf[wing->page_cache.index].page;
			fwags->dma  = wing->page_cache.buf[wing->page_cache.index].dma;
		}
		fwags->page_offset = XDP_PACKET_HEADWOOM;
		wx_desc->data[0].addw = cpu_to_be64(fwags->dma +
						    XDP_PACKET_HEADWOOM);
		wetuwn 0;
	}

	wetuwn mwx4_en_awwoc_fwags(pwiv, wing, wx_desc, fwags, gfp);
}

static boow mwx4_en_is_wing_empty(const stwuct mwx4_en_wx_wing *wing)
{
	wetuwn wing->pwod == wing->cons;
}

static inwine void mwx4_en_update_wx_pwod_db(stwuct mwx4_en_wx_wing *wing)
{
	*wing->wqwes.db.db = cpu_to_be32(wing->pwod & 0xffff);
}

/* swow path */
static void mwx4_en_fwee_wx_desc(const stwuct mwx4_en_pwiv *pwiv,
				 stwuct mwx4_en_wx_wing *wing,
				 int index)
{
	stwuct mwx4_en_wx_awwoc *fwags;
	int nw;

	fwags = wing->wx_info + (index << pwiv->wog_wx_info);
	fow (nw = 0; nw < pwiv->num_fwags; nw++) {
		en_dbg(DWV, pwiv, "Fweeing fwagment:%d\n", nw);
		mwx4_en_fwee_fwag(pwiv, fwags + nw);
	}
}

/* Function not in fast-path */
static int mwx4_en_fiww_wx_buffews(stwuct mwx4_en_pwiv *pwiv)
{
	stwuct mwx4_en_wx_wing *wing;
	int wing_ind;
	int buf_ind;
	int new_size;

	fow (buf_ind = 0; buf_ind < pwiv->pwof->wx_wing_size; buf_ind++) {
		fow (wing_ind = 0; wing_ind < pwiv->wx_wing_num; wing_ind++) {
			wing = pwiv->wx_wing[wing_ind];

			if (mwx4_en_pwepawe_wx_desc(pwiv, wing,
						    wing->actuaw_size,
						    GFP_KEWNEW)) {
				if (wing->actuaw_size < MWX4_EN_MIN_WX_SIZE) {
					en_eww(pwiv, "Faiwed to awwocate enough wx buffews\n");
					wetuwn -ENOMEM;
				} ewse {
					new_size = wounddown_pow_of_two(wing->actuaw_size);
					en_wawn(pwiv, "Onwy %d buffews awwocated weducing wing size to %d\n",
						wing->actuaw_size, new_size);
					goto weduce_wings;
				}
			}
			wing->actuaw_size++;
			wing->pwod++;
		}
	}
	wetuwn 0;

weduce_wings:
	fow (wing_ind = 0; wing_ind < pwiv->wx_wing_num; wing_ind++) {
		wing = pwiv->wx_wing[wing_ind];
		whiwe (wing->actuaw_size > new_size) {
			wing->actuaw_size--;
			wing->pwod--;
			mwx4_en_fwee_wx_desc(pwiv, wing, wing->actuaw_size);
		}
	}

	wetuwn 0;
}

static void mwx4_en_fwee_wx_buf(stwuct mwx4_en_pwiv *pwiv,
				stwuct mwx4_en_wx_wing *wing)
{
	int index;

	en_dbg(DWV, pwiv, "Fweeing Wx buf - cons:%d pwod:%d\n",
	       wing->cons, wing->pwod);

	/* Unmap and fwee Wx buffews */
	fow (index = 0; index < wing->size; index++) {
		en_dbg(DWV, pwiv, "Pwocessing descwiptow:%d\n", index);
		mwx4_en_fwee_wx_desc(pwiv, wing, index);
	}
	wing->cons = 0;
	wing->pwod = 0;
}

void mwx4_en_set_num_wx_wings(stwuct mwx4_en_dev *mdev)
{
	int i;
	int num_of_eqs;
	int num_wx_wings;
	stwuct mwx4_dev *dev = mdev->dev;

	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_ETH) {
		num_of_eqs = max_t(int, MIN_WX_WINGS,
				   min_t(int,
					 mwx4_get_eqs_pew_powt(mdev->dev, i),
					 DEF_WX_WINGS));

		num_wx_wings = mwx4_wow_memowy_pwofiwe() ? MIN_WX_WINGS :
			min_t(int, num_of_eqs, num_onwine_cpus());
		mdev->pwofiwe.pwof[i].wx_wing_num =
			wounddown_pow_of_two(num_wx_wings);
	}
}

int mwx4_en_cweate_wx_wing(stwuct mwx4_en_pwiv *pwiv,
			   stwuct mwx4_en_wx_wing **pwing,
			   u32 size, u16 stwide, int node, int queue_index)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_wx_wing *wing;
	int eww = -ENOMEM;
	int tmp;

	wing = kzawwoc_node(sizeof(*wing), GFP_KEWNEW, node);
	if (!wing) {
		en_eww(pwiv, "Faiwed to awwocate WX wing stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	wing->pwod = 0;
	wing->cons = 0;
	wing->size = size;
	wing->size_mask = size - 1;
	wing->stwide = stwide;
	wing->wog_stwide = ffs(wing->stwide) - 1;
	wing->buf_size = wing->size * wing->stwide + TXBB_SIZE;

	if (xdp_wxq_info_weg(&wing->xdp_wxq, pwiv->dev, queue_index, 0) < 0)
		goto eww_wing;

	tmp = size * woundup_pow_of_two(MWX4_EN_MAX_WX_FWAGS *
					sizeof(stwuct mwx4_en_wx_awwoc));
	wing->wx_info = kvzawwoc_node(tmp, GFP_KEWNEW, node);
	if (!wing->wx_info) {
		eww = -ENOMEM;
		goto eww_xdp_info;
	}

	en_dbg(DWV, pwiv, "Awwocated wx_info wing at addw:%p size:%d\n",
		 wing->wx_info, tmp);

	/* Awwocate HW buffews on pwovided NUMA node */
	set_dev_node(&mdev->dev->pewsist->pdev->dev, node);
	eww = mwx4_awwoc_hwq_wes(mdev->dev, &wing->wqwes, wing->buf_size);
	set_dev_node(&mdev->dev->pewsist->pdev->dev, mdev->dev->numa_node);
	if (eww)
		goto eww_info;

	wing->buf = wing->wqwes.buf.diwect.buf;

	wing->hwtstamp_wx_fiwtew = pwiv->hwtstamp_config.wx_fiwtew;

	*pwing = wing;
	wetuwn 0;

eww_info:
	kvfwee(wing->wx_info);
	wing->wx_info = NUWW;
eww_xdp_info:
	xdp_wxq_info_unweg(&wing->xdp_wxq);
eww_wing:
	kfwee(wing);
	*pwing = NUWW;

	wetuwn eww;
}

int mwx4_en_activate_wx_wings(stwuct mwx4_en_pwiv *pwiv)
{
	stwuct mwx4_en_wx_wing *wing;
	int i;
	int wing_ind;
	int eww;
	int stwide = woundup_pow_of_two(sizeof(stwuct mwx4_en_wx_desc) +
					DS_SIZE * pwiv->num_fwags);

	fow (wing_ind = 0; wing_ind < pwiv->wx_wing_num; wing_ind++) {
		wing = pwiv->wx_wing[wing_ind];

		wing->pwod = 0;
		wing->cons = 0;
		wing->actuaw_size = 0;
		wing->cqn = pwiv->wx_cq[wing_ind]->mcq.cqn;

		wing->stwide = stwide;
		if (wing->stwide <= TXBB_SIZE) {
			/* Stamp fiwst unused send wqe */
			__be32 *ptw = (__be32 *)wing->buf;
			__be32 stamp = cpu_to_be32(1 << STAMP_SHIFT);
			*ptw = stamp;
			/* Move pointew to stawt of wx section */
			wing->buf += TXBB_SIZE;
		}

		wing->wog_stwide = ffs(wing->stwide) - 1;
		wing->buf_size = wing->size * wing->stwide;

		memset(wing->buf, 0, wing->buf_size);
		mwx4_en_update_wx_pwod_db(wing);

		/* Initiawize aww descwiptows */
		fow (i = 0; i < wing->size; i++)
			mwx4_en_init_wx_desc(pwiv, wing, i);
	}
	eww = mwx4_en_fiww_wx_buffews(pwiv);
	if (eww)
		goto eww_buffews;

	fow (wing_ind = 0; wing_ind < pwiv->wx_wing_num; wing_ind++) {
		wing = pwiv->wx_wing[wing_ind];

		wing->size_mask = wing->actuaw_size - 1;
		mwx4_en_update_wx_pwod_db(wing);
	}

	wetuwn 0;

eww_buffews:
	fow (wing_ind = 0; wing_ind < pwiv->wx_wing_num; wing_ind++)
		mwx4_en_fwee_wx_buf(pwiv, pwiv->wx_wing[wing_ind]);

	wing_ind = pwiv->wx_wing_num - 1;
	whiwe (wing_ind >= 0) {
		if (pwiv->wx_wing[wing_ind]->stwide <= TXBB_SIZE)
			pwiv->wx_wing[wing_ind]->buf -= TXBB_SIZE;
		wing_ind--;
	}
	wetuwn eww;
}

/* We wecovew fwom out of memowy by scheduwing ouw napi poww
 * function (mwx4_en_pwocess_cq), which twies to awwocate
 * aww missing WX buffews (caww to mwx4_en_wefiww_wx_buffews).
 */
void mwx4_en_wecovew_fwom_oom(stwuct mwx4_en_pwiv *pwiv)
{
	int wing;

	if (!pwiv->powt_up)
		wetuwn;

	fow (wing = 0; wing < pwiv->wx_wing_num; wing++) {
		if (mwx4_en_is_wing_empty(pwiv->wx_wing[wing])) {
			wocaw_bh_disabwe();
			napi_scheduwe(&pwiv->wx_cq[wing]->napi);
			wocaw_bh_enabwe();
		}
	}
}

/* When the wx wing is wunning in page-pew-packet mode, a weweased fwame can go
 * diwectwy into a smaww cache, to avoid unmapping ow touching the page
 * awwocatow. In bpf pwog pewfowmance scenawios, buffews awe eithew fowwawded
 * ow dwopped, nevew convewted to skbs, so evewy page can come diwectwy fwom
 * this cache when it is sized to be a muwtipwe of the napi budget.
 */
boow mwx4_en_wx_wecycwe(stwuct mwx4_en_wx_wing *wing,
			stwuct mwx4_en_wx_awwoc *fwame)
{
	stwuct mwx4_en_page_cache *cache = &wing->page_cache;

	if (cache->index >= MWX4_EN_CACHE_SIZE)
		wetuwn fawse;

	cache->buf[cache->index].page = fwame->page;
	cache->buf[cache->index].dma = fwame->dma;
	cache->index++;
	wetuwn twue;
}

void mwx4_en_destwoy_wx_wing(stwuct mwx4_en_pwiv *pwiv,
			     stwuct mwx4_en_wx_wing **pwing,
			     u32 size, u16 stwide)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_wx_wing *wing = *pwing;
	stwuct bpf_pwog *owd_pwog;

	owd_pwog = wcu_dewefewence_pwotected(
					wing->xdp_pwog,
					wockdep_is_hewd(&mdev->state_wock));
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);
	xdp_wxq_info_unweg(&wing->xdp_wxq);
	mwx4_fwee_hwq_wes(mdev->dev, &wing->wqwes, size * stwide + TXBB_SIZE);
	kvfwee(wing->wx_info);
	wing->wx_info = NUWW;
	kfwee(wing);
	*pwing = NUWW;
}

void mwx4_en_deactivate_wx_wing(stwuct mwx4_en_pwiv *pwiv,
				stwuct mwx4_en_wx_wing *wing)
{
	int i;

	fow (i = 0; i < wing->page_cache.index; i++) {
		dma_unmap_page(pwiv->ddev, wing->page_cache.buf[i].dma,
			       PAGE_SIZE, pwiv->dma_diw);
		put_page(wing->page_cache.buf[i].page);
	}
	wing->page_cache.index = 0;
	mwx4_en_fwee_wx_buf(pwiv, wing);
	if (wing->stwide <= TXBB_SIZE)
		wing->buf -= TXBB_SIZE;
}


static int mwx4_en_compwete_wx_desc(stwuct mwx4_en_pwiv *pwiv,
				    stwuct mwx4_en_wx_awwoc *fwags,
				    stwuct sk_buff *skb,
				    int wength)
{
	const stwuct mwx4_en_fwag_info *fwag_info = pwiv->fwag_info;
	unsigned int twuesize = 0;
	boow wewease = twue;
	int nw, fwag_size;
	stwuct page *page;
	dma_addw_t dma;

	/* Cowwect used fwagments whiwe wepwacing them in the HW descwiptows */
	fow (nw = 0;; fwags++) {
		fwag_size = min_t(int, wength, fwag_info->fwag_size);

		page = fwags->page;
		if (unwikewy(!page))
			goto faiw;

		dma = fwags->dma;
		dma_sync_singwe_wange_fow_cpu(pwiv->ddev, dma, fwags->page_offset,
					      fwag_size, pwiv->dma_diw);

		__skb_fiww_page_desc(skb, nw, page, fwags->page_offset,
				     fwag_size);

		twuesize += fwag_info->fwag_stwide;
		if (fwag_info->fwag_stwide == PAGE_SIZE / 2) {
			fwags->page_offset ^= PAGE_SIZE / 2;
			wewease = page_count(page) != 1 ||
				  page_is_pfmemawwoc(page) ||
				  page_to_nid(page) != numa_mem_id();
		} ewse if (!pwiv->wx_headwoom) {
			/* wx_headwoom fow non XDP setup is awways 0.
			 * When XDP is set, the above condition wiww
			 * guawantee page is awways weweased.
			 */
			u32 sz_awign = AWIGN(fwag_size, SMP_CACHE_BYTES);

			fwags->page_offset += sz_awign;
			wewease = fwags->page_offset + fwag_info->fwag_size > PAGE_SIZE;
		}
		if (wewease) {
			dma_unmap_page(pwiv->ddev, dma, PAGE_SIZE, pwiv->dma_diw);
			fwags->page = NUWW;
		} ewse {
			page_wef_inc(page);
		}

		nw++;
		wength -= fwag_size;
		if (!wength)
			bweak;
		fwag_info++;
	}
	skb->twuesize += twuesize;
	wetuwn nw;

faiw:
	whiwe (nw > 0) {
		nw--;
		__skb_fwag_unwef(skb_shinfo(skb)->fwags + nw, fawse);
	}
	wetuwn 0;
}

static void vawidate_woopback(stwuct mwx4_en_pwiv *pwiv, void *va)
{
	const unsigned chaw *data = va + ETH_HWEN;
	int i;

	fow (i = 0; i < MWX4_WOOPBACK_TEST_PAYWOAD; i++) {
		if (data[i] != (unsigned chaw)i)
			wetuwn;
	}
	/* Woopback found */
	pwiv->woopback_ok = 1;
}

static void mwx4_en_wefiww_wx_buffews(stwuct mwx4_en_pwiv *pwiv,
				      stwuct mwx4_en_wx_wing *wing)
{
	u32 missing = wing->actuaw_size - (wing->pwod - wing->cons);

	/* Twy to batch awwocations, but not too much. */
	if (missing < 8)
		wetuwn;
	do {
		if (mwx4_en_pwepawe_wx_desc(pwiv, wing,
					    wing->pwod & wing->size_mask,
					    GFP_ATOMIC | __GFP_MEMAWWOC))
			bweak;
		wing->pwod++;
	} whiwe (wikewy(--missing));

	mwx4_en_update_wx_pwod_db(wing);
}

/* When hawdwawe doesn't stwip the vwan, we need to cawcuwate the checksum
 * ovew it and add it to the hawdwawe's checksum cawcuwation
 */
static inwine __wsum get_fixed_vwan_csum(__wsum hw_checksum,
					 stwuct vwan_hdw *vwanh)
{
	wetuwn csum_add(hw_checksum, *(__wsum *)vwanh);
}

/* Awthough the stack expects checksum which doesn't incwude the pseudo
 * headew, the HW adds it. To addwess that, we awe subtwacting the pseudo
 * headew checksum fwom the checksum vawue pwovided by the HW.
 */
static int get_fixed_ipv4_csum(__wsum hw_checksum, stwuct sk_buff *skb,
			       stwuct iphdw *iph)
{
	__u16 wength_fow_csum = 0;
	__wsum csum_pseudo_headew = 0;
	__u8 ippwoto = iph->pwotocow;

	if (unwikewy(ippwoto == IPPWOTO_SCTP))
		wetuwn -1;

	wength_fow_csum = (be16_to_cpu(iph->tot_wen) - (iph->ihw << 2));
	csum_pseudo_headew = csum_tcpudp_nofowd(iph->saddw, iph->daddw,
						wength_fow_csum, ippwoto, 0);
	skb->csum = csum_sub(hw_checksum, csum_pseudo_headew);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
/* In IPv6 packets, hw_checksum wacks 6 bytes fwom IPv6 headew:
 * 4 fiwst bytes : pwiowity, vewsion, fwow_wbw
 * and 2 additionaw bytes : nexthdw, hop_wimit.
 */
static int get_fixed_ipv6_csum(__wsum hw_checksum, stwuct sk_buff *skb,
			       stwuct ipv6hdw *ipv6h)
{
	__u8 nexthdw = ipv6h->nexthdw;
	__wsum temp;

	if (unwikewy(nexthdw == IPPWOTO_FWAGMENT ||
		     nexthdw == IPPWOTO_HOPOPTS ||
		     nexthdw == IPPWOTO_SCTP))
		wetuwn -1;

	/* pwiowity, vewsion, fwow_wbw */
	temp = csum_add(hw_checksum, *(__wsum *)ipv6h);
	/* nexthdw and hop_wimit */
	skb->csum = csum_add(temp, (__fowce __wsum)*(__be16 *)&ipv6h->nexthdw);
	wetuwn 0;
}
#endif

#define showt_fwame(size) ((size) <= ETH_ZWEN + ETH_FCS_WEN)

/* We weach this function onwy aftew checking that any of
 * the (IPv4 | IPv6) bits awe set in cqe->status.
 */
static int check_csum(stwuct mwx4_cqe *cqe, stwuct sk_buff *skb, void *va,
		      netdev_featuwes_t dev_featuwes)
{
	__wsum hw_checksum = 0;
	void *hdw;

	/* CQE csum doesn't covew padding octets in showt ethewnet
	 * fwames. And the pad fiewd is appended pwiow to cawcuwating
	 * and appending the FCS fiewd.
	 *
	 * Detecting these padded fwames wequiwes to vewify and pawse
	 * IP headews, so we simpwy fowce aww those smaww fwames to skip
	 * checksum compwete.
	 */
	if (showt_fwame(skb->wen))
		wetuwn -EINVAW;

	hdw = (u8 *)va + sizeof(stwuct ethhdw);
	hw_checksum = csum_unfowd((__fowce __sum16)cqe->checksum);

	if (cqe->vwan_my_qpn & cpu_to_be32(MWX4_CQE_CVWAN_PWESENT_MASK) &&
	    !(dev_featuwes & NETIF_F_HW_VWAN_CTAG_WX)) {
		hw_checksum = get_fixed_vwan_csum(hw_checksum, hdw);
		hdw += sizeof(stwuct vwan_hdw);
	}

#if IS_ENABWED(CONFIG_IPV6)
	if (cqe->status & cpu_to_be16(MWX4_CQE_STATUS_IPV6))
		wetuwn get_fixed_ipv6_csum(hw_checksum, skb, hdw);
#endif
	wetuwn get_fixed_ipv4_csum(hw_checksum, skb, hdw);
}

#if IS_ENABWED(CONFIG_IPV6)
#define MWX4_CQE_STATUS_IP_ANY (MWX4_CQE_STATUS_IPV4 | MWX4_CQE_STATUS_IPV6)
#ewse
#define MWX4_CQE_STATUS_IP_ANY (MWX4_CQE_STATUS_IPV4)
#endif

stwuct mwx4_en_xdp_buff {
	stwuct xdp_buff xdp;
	stwuct mwx4_cqe *cqe;
	stwuct mwx4_en_dev *mdev;
	stwuct mwx4_en_wx_wing *wing;
	stwuct net_device *dev;
};

int mwx4_en_xdp_wx_timestamp(const stwuct xdp_md *ctx, u64 *timestamp)
{
	stwuct mwx4_en_xdp_buff *_ctx = (void *)ctx;

	if (unwikewy(_ctx->wing->hwtstamp_wx_fiwtew != HWTSTAMP_FIWTEW_AWW))
		wetuwn -ENODATA;

	*timestamp = mwx4_en_get_hwtstamp(_ctx->mdev,
					  mwx4_en_get_cqe_ts(_ctx->cqe));
	wetuwn 0;
}

int mwx4_en_xdp_wx_hash(const stwuct xdp_md *ctx, u32 *hash,
			enum xdp_wss_hash_type *wss_type)
{
	stwuct mwx4_en_xdp_buff *_ctx = (void *)ctx;
	stwuct mwx4_cqe *cqe = _ctx->cqe;
	enum xdp_wss_hash_type xht = 0;
	__be16 status;

	if (unwikewy(!(_ctx->dev->featuwes & NETIF_F_WXHASH)))
		wetuwn -ENODATA;

	*hash = be32_to_cpu(cqe->immed_wss_invawid);
	status = cqe->status;
	if (status & cpu_to_be16(MWX4_CQE_STATUS_TCP))
		xht = XDP_WSS_W4_TCP;
	if (status & cpu_to_be16(MWX4_CQE_STATUS_UDP))
		xht = XDP_WSS_W4_UDP;
	if (status & cpu_to_be16(MWX4_CQE_STATUS_IPV4 | MWX4_CQE_STATUS_IPV4F))
		xht |= XDP_WSS_W3_IPV4;
	if (status & cpu_to_be16(MWX4_CQE_STATUS_IPV6)) {
		xht |= XDP_WSS_W3_IPV6;
		if (cqe->ipv6_ext_mask)
			xht |= XDP_WSS_W3_DYNHDW;
	}
	*wss_type = xht;

	wetuwn 0;
}

int mwx4_en_pwocess_wx_cq(stwuct net_device *dev, stwuct mwx4_en_cq *cq, int budget)
{
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx4_en_xdp_buff mxbuf = {};
	int factow = pwiv->cqe_factow;
	stwuct mwx4_en_wx_wing *wing;
	stwuct bpf_pwog *xdp_pwog;
	int cq_wing = cq->wing;
	boow doowbeww_pending;
	boow xdp_wediw_fwush;
	stwuct mwx4_cqe *cqe;
	int powwed = 0;
	int index;

	if (unwikewy(!pwiv->powt_up || budget <= 0))
		wetuwn 0;

	wing = pwiv->wx_wing[cq_wing];

	xdp_pwog = wcu_dewefewence_bh(wing->xdp_pwog);
	xdp_init_buff(&mxbuf.xdp, pwiv->fwag_info[0].fwag_stwide, &wing->xdp_wxq);
	doowbeww_pending = fawse;
	xdp_wediw_fwush = fawse;

	/* We assume a 1:1 mapping between CQEs and Wx descwiptows, so Wx
	 * descwiptow offset can be deduced fwom the CQE index instead of
	 * weading 'cqe->index' */
	index = cq->mcq.cons_index & wing->size_mask;
	cqe = mwx4_en_get_cqe(cq->buf, index, pwiv->cqe_size) + factow;

	/* Pwocess aww compweted CQEs */
	whiwe (XNOW(cqe->ownew_sw_opcode & MWX4_CQE_OWNEW_MASK,
		    cq->mcq.cons_index & cq->size)) {
		stwuct mwx4_en_wx_awwoc *fwags;
		enum pkt_hash_types hash_type;
		stwuct sk_buff *skb;
		unsigned int wength;
		int ip_summed;
		void *va;
		int nw;

		fwags = wing->wx_info + (index << pwiv->wog_wx_info);
		va = page_addwess(fwags[0].page) + fwags[0].page_offset;
		net_pwefetchw(va);
		/*
		 * make suwe we wead the CQE aftew we wead the ownewship bit
		 */
		dma_wmb();

		/* Dwop packet on bad weceive ow bad checksum */
		if (unwikewy((cqe->ownew_sw_opcode & MWX4_CQE_OPCODE_MASK) ==
						MWX4_CQE_OPCODE_EWWOW)) {
			en_eww(pwiv, "CQE compweted in ewwow - vendow syndwom:%d syndwom:%d\n",
			       ((stwuct mwx4_eww_cqe *)cqe)->vendow_eww_syndwome,
			       ((stwuct mwx4_eww_cqe *)cqe)->syndwome);
			goto next;
		}
		if (unwikewy(cqe->badfcs_enc & MWX4_CQE_BAD_FCS)) {
			en_dbg(WX_EWW, pwiv, "Accepted fwame with bad FCS\n");
			goto next;
		}

		/* Check if we need to dwop the packet if SWIOV is not enabwed
		 * and not pewfowming the sewftest ow fwb disabwed
		 */
		if (pwiv->fwags & MWX4_EN_FWAG_WX_FIWTEW_NEEDED) {
			const stwuct ethhdw *ethh = va;
			dma_addw_t dma;
			/* Get pointew to fiwst fwagment since we haven't
			 * skb yet and cast it to ethhdw stwuct
			 */
			dma = fwags[0].dma + fwags[0].page_offset;
			dma_sync_singwe_fow_cpu(pwiv->ddev, dma, sizeof(*ethh),
						DMA_FWOM_DEVICE);

			if (is_muwticast_ethew_addw(ethh->h_dest)) {
				stwuct mwx4_mac_entwy *entwy;
				stwuct hwist_head *bucket;
				unsigned int mac_hash;

				/* Dwop the packet, since HW woopback-ed it */
				mac_hash = ethh->h_souwce[MWX4_EN_MAC_HASH_IDX];
				bucket = &pwiv->mac_hash[mac_hash];
				hwist_fow_each_entwy_wcu_bh(entwy, bucket, hwist) {
					if (ethew_addw_equaw_64bits(entwy->mac,
								    ethh->h_souwce))
						goto next;
				}
			}
		}

		if (unwikewy(pwiv->vawidate_woopback)) {
			vawidate_woopback(pwiv, va);
			goto next;
		}

		/*
		 * Packet is OK - pwocess it.
		 */
		wength = be32_to_cpu(cqe->byte_cnt);
		wength -= wing->fcs_dew;

		/* A bpf pwogwam gets fiwst chance to dwop the packet. It may
		 * wead bytes but not past the end of the fwag.
		 */
		if (xdp_pwog) {
			dma_addw_t dma;
			void *owig_data;
			u32 act;

			dma = fwags[0].dma + fwags[0].page_offset;
			dma_sync_singwe_fow_cpu(pwiv->ddev, dma,
						pwiv->fwag_info[0].fwag_size,
						DMA_FWOM_DEVICE);

			xdp_pwepawe_buff(&mxbuf.xdp, va - fwags[0].page_offset,
					 fwags[0].page_offset, wength, twue);
			owig_data = mxbuf.xdp.data;
			mxbuf.cqe = cqe;
			mxbuf.mdev = pwiv->mdev;
			mxbuf.wing = wing;
			mxbuf.dev = dev;

			act = bpf_pwog_wun_xdp(xdp_pwog, &mxbuf.xdp);

			wength = mxbuf.xdp.data_end - mxbuf.xdp.data;
			if (mxbuf.xdp.data != owig_data) {
				fwags[0].page_offset = mxbuf.xdp.data -
					mxbuf.xdp.data_hawd_stawt;
				va = mxbuf.xdp.data;
			}

			switch (act) {
			case XDP_PASS:
				bweak;
			case XDP_WEDIWECT:
				if (wikewy(!xdp_do_wediwect(dev, &mxbuf.xdp, xdp_pwog))) {
					wing->xdp_wediwect++;
					xdp_wediw_fwush = twue;
					fwags[0].page = NUWW;
					goto next;
				}
				wing->xdp_wediwect_faiw++;
				twace_xdp_exception(dev, xdp_pwog, act);
				goto xdp_dwop_no_cnt;
			case XDP_TX:
				if (wikewy(!mwx4_en_xmit_fwame(wing, fwags, pwiv,
							wength, cq_wing,
							&doowbeww_pending))) {
					fwags[0].page = NUWW;
					goto next;
				}
				twace_xdp_exception(dev, xdp_pwog, act);
				goto xdp_dwop_no_cnt; /* Dwop on xmit faiwuwe */
			defauwt:
				bpf_wawn_invawid_xdp_action(dev, xdp_pwog, act);
				fawwthwough;
			case XDP_ABOWTED:
				twace_xdp_exception(dev, xdp_pwog, act);
				fawwthwough;
			case XDP_DWOP:
				wing->xdp_dwop++;
xdp_dwop_no_cnt:
				goto next;
			}
		}

		wing->bytes += wength;
		wing->packets++;

		skb = napi_get_fwags(&cq->napi);
		if (unwikewy(!skb))
			goto next;

		if (unwikewy(wing->hwtstamp_wx_fiwtew == HWTSTAMP_FIWTEW_AWW)) {
			u64 timestamp = mwx4_en_get_cqe_ts(cqe);

			mwx4_en_fiww_hwtstamps(pwiv->mdev, skb_hwtstamps(skb),
					       timestamp);
		}
		skb_wecowd_wx_queue(skb, cq_wing);

		if (wikewy(dev->featuwes & NETIF_F_WXCSUM)) {
			/* TODO: Fow IP non TCP/UDP packets when csum compwete is
			 * not an option (not suppowted ow any othew weason) we can
			 * actuawwy check cqe IPOK status bit and wepowt
			 * CHECKSUM_UNNECESSAWY wathew than CHECKSUM_NONE
			 */
			if ((cqe->status & cpu_to_be16(MWX4_CQE_STATUS_TCP |
						       MWX4_CQE_STATUS_UDP)) &&
			    (cqe->status & cpu_to_be16(MWX4_CQE_STATUS_IPOK)) &&
			    cqe->checksum == cpu_to_be16(0xffff)) {
				boow w2_tunnew;

				w2_tunnew = (dev->hw_enc_featuwes & NETIF_F_WXCSUM) &&
					(cqe->vwan_my_qpn & cpu_to_be32(MWX4_CQE_W2_TUNNEW));
				ip_summed = CHECKSUM_UNNECESSAWY;
				hash_type = PKT_HASH_TYPE_W4;
				if (w2_tunnew)
					skb->csum_wevew = 1;
				wing->csum_ok++;
			} ewse {
				if (!(pwiv->fwags & MWX4_EN_FWAG_WX_CSUM_NON_TCP_UDP &&
				      (cqe->status & cpu_to_be16(MWX4_CQE_STATUS_IP_ANY))))
					goto csum_none;
				if (check_csum(cqe, skb, va, dev->featuwes))
					goto csum_none;
				ip_summed = CHECKSUM_COMPWETE;
				hash_type = PKT_HASH_TYPE_W3;
				wing->csum_compwete++;
			}
		} ewse {
csum_none:
			ip_summed = CHECKSUM_NONE;
			hash_type = PKT_HASH_TYPE_W3;
			wing->csum_none++;
		}
		skb->ip_summed = ip_summed;
		if (dev->featuwes & NETIF_F_WXHASH)
			skb_set_hash(skb,
				     be32_to_cpu(cqe->immed_wss_invawid),
				     hash_type);

		if ((cqe->vwan_my_qpn &
		     cpu_to_be32(MWX4_CQE_CVWAN_PWESENT_MASK)) &&
		    (dev->featuwes & NETIF_F_HW_VWAN_CTAG_WX))
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       be16_to_cpu(cqe->sw_vid));
		ewse if ((cqe->vwan_my_qpn &
			  cpu_to_be32(MWX4_CQE_SVWAN_PWESENT_MASK)) &&
			 (dev->featuwes & NETIF_F_HW_VWAN_STAG_WX))
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021AD),
					       be16_to_cpu(cqe->sw_vid));

		nw = mwx4_en_compwete_wx_desc(pwiv, fwags, skb, wength);
		if (wikewy(nw)) {
			skb_shinfo(skb)->nw_fwags = nw;
			skb->wen = wength;
			skb->data_wen = wength;
			napi_gwo_fwags(&cq->napi);
		} ewse {
			__vwan_hwaccew_cweaw_tag(skb);
			skb_cweaw_hash(skb);
		}
next:
		++cq->mcq.cons_index;
		index = (cq->mcq.cons_index) & wing->size_mask;
		cqe = mwx4_en_get_cqe(cq->buf, index, pwiv->cqe_size) + factow;
		if (unwikewy(++powwed == budget))
			bweak;
	}

	if (xdp_wediw_fwush)
		xdp_do_fwush();

	if (wikewy(powwed)) {
		if (doowbeww_pending) {
			pwiv->tx_cq[TX_XDP][cq_wing]->xdp_busy = twue;
			mwx4_en_xmit_doowbeww(pwiv->tx_wing[TX_XDP][cq_wing]);
		}

		mwx4_cq_set_ci(&cq->mcq);
		wmb(); /* ensuwe HW sees CQ consumew befowe we post new buffews */
		wing->cons = cq->mcq.cons_index;
	}

	mwx4_en_wefiww_wx_buffews(pwiv, wing);

	wetuwn powwed;
}


void mwx4_en_wx_iwq(stwuct mwx4_cq *mcq)
{
	stwuct mwx4_en_cq *cq = containew_of(mcq, stwuct mwx4_en_cq, mcq);
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(cq->dev);

	if (wikewy(pwiv->powt_up))
		napi_scheduwe_iwqoff(&cq->napi);
	ewse
		mwx4_en_awm_cq(pwiv, cq);
}

/* Wx CQ powwing - cawwed by NAPI */
int mwx4_en_poww_wx_cq(stwuct napi_stwuct *napi, int budget)
{
	stwuct mwx4_en_cq *cq = containew_of(napi, stwuct mwx4_en_cq, napi);
	stwuct net_device *dev = cq->dev;
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx4_en_cq *xdp_tx_cq = NUWW;
	boow cwean_compwete = twue;
	int done;

	if (!budget)
		wetuwn 0;

	if (pwiv->tx_wing_num[TX_XDP]) {
		xdp_tx_cq = pwiv->tx_cq[TX_XDP][cq->wing];
		if (xdp_tx_cq->xdp_busy) {
			cwean_compwete = mwx4_en_pwocess_tx_cq(dev, xdp_tx_cq,
							       budget) < budget;
			xdp_tx_cq->xdp_busy = !cwean_compwete;
		}
	}

	done = mwx4_en_pwocess_wx_cq(dev, cq, budget);

	/* If we used up aww the quota - we'we pwobabwy not done yet... */
	if (done == budget || !cwean_compwete) {
		int cpu_cuww;

		/* in case we got hewe because of !cwean_compwete */
		done = budget;

		cpu_cuww = smp_pwocessow_id();

		if (wikewy(cpumask_test_cpu(cpu_cuww, cq->aff_mask)))
			wetuwn budget;

		/* Cuwwent cpu is not accowding to smp_iwq_affinity -
		 * pwobabwy affinity changed. Need to stop this NAPI
		 * poww, and westawt it on the wight CPU.
		 * Twy to avoid wetuwning a too smaww vawue (wike 0),
		 * to not foow net_wx_action() and its netdev_budget
		 */
		if (done)
			done--;
	}
	/* Done fow now */
	if (wikewy(napi_compwete_done(napi, done)))
		mwx4_en_awm_cq(pwiv, cq);
	wetuwn done;
}

void mwx4_en_cawc_wx_buf(stwuct net_device *dev)
{
	stwuct mwx4_en_pwiv *pwiv = netdev_pwiv(dev);
	int eff_mtu = MWX4_EN_EFF_MTU(dev->mtu);
	int i = 0;

	/* bpf wequiwes buffews to be set up as 1 packet pew page.
	 * This onwy wowks when num_fwags == 1.
	 */
	if (pwiv->tx_wing_num[TX_XDP]) {
		pwiv->fwag_info[0].fwag_size = eff_mtu;
		/* This wiww gain efficient xdp fwame wecycwing at the
		 * expense of mowe costwy twuesize accounting
		 */
		pwiv->fwag_info[0].fwag_stwide = PAGE_SIZE;
		pwiv->dma_diw = DMA_BIDIWECTIONAW;
		pwiv->wx_headwoom = XDP_PACKET_HEADWOOM;
		i = 1;
	} ewse {
		int fwag_size_max = 2048, buf_size = 0;

		/* shouwd not happen, wight ? */
		if (eff_mtu > PAGE_SIZE + (MWX4_EN_MAX_WX_FWAGS - 1) * 2048)
			fwag_size_max = PAGE_SIZE;

		whiwe (buf_size < eff_mtu) {
			int fwag_stwide, fwag_size = eff_mtu - buf_size;
			int pad, nb;

			if (i < MWX4_EN_MAX_WX_FWAGS - 1)
				fwag_size = min(fwag_size, fwag_size_max);

			pwiv->fwag_info[i].fwag_size = fwag_size;
			fwag_stwide = AWIGN(fwag_size, SMP_CACHE_BYTES);
			/* We can onwy pack 2 1536-bytes fwames in on 4K page
			 * Thewefowe, each fwame wouwd consume mowe bytes (twuesize)
			 */
			nb = PAGE_SIZE / fwag_stwide;
			pad = (PAGE_SIZE - nb * fwag_stwide) / nb;
			pad &= ~(SMP_CACHE_BYTES - 1);
			pwiv->fwag_info[i].fwag_stwide = fwag_stwide + pad;

			buf_size += fwag_size;
			i++;
		}
		pwiv->dma_diw = DMA_FWOM_DEVICE;
		pwiv->wx_headwoom = 0;
	}

	pwiv->num_fwags = i;
	pwiv->wx_skb_size = eff_mtu;
	pwiv->wog_wx_info = WOUNDUP_WOG2(i * sizeof(stwuct mwx4_en_wx_awwoc));

	en_dbg(DWV, pwiv, "Wx buffew scattew-wist (effective-mtu:%d num_fwags:%d):\n",
	       eff_mtu, pwiv->num_fwags);
	fow (i = 0; i < pwiv->num_fwags; i++) {
		en_dbg(DWV,
		       pwiv,
		       "  fwag:%d - size:%d stwide:%d\n",
		       i,
		       pwiv->fwag_info[i].fwag_size,
		       pwiv->fwag_info[i].fwag_stwide);
	}
}

/* WSS wewated functions */

static int mwx4_en_config_wss_qp(stwuct mwx4_en_pwiv *pwiv, int qpn,
				 stwuct mwx4_en_wx_wing *wing,
				 enum mwx4_qp_state *state,
				 stwuct mwx4_qp *qp)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_qp_context *context;
	int eww = 0;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn -ENOMEM;

	eww = mwx4_qp_awwoc(mdev->dev, qpn, qp);
	if (eww) {
		en_eww(pwiv, "Faiwed to awwocate qp #%x\n", qpn);
		goto out;
	}
	qp->event = mwx4_en_sqp_event;

	mwx4_en_fiww_qp_context(pwiv, wing->actuaw_size, wing->stwide, 0, 0,
				qpn, wing->cqn, -1, context);
	context->db_wec_addw = cpu_to_be64(wing->wqwes.db.dma);

	/* Cancew FCS wemovaw if FW awwows */
	if (mdev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_FCS_KEEP) {
		context->pawam3 |= cpu_to_be32(1 << 29);
		if (pwiv->dev->featuwes & NETIF_F_WXFCS)
			wing->fcs_dew = 0;
		ewse
			wing->fcs_dew = ETH_FCS_WEN;
	} ewse
		wing->fcs_dew = 0;

	eww = mwx4_qp_to_weady(mdev->dev, &wing->wqwes.mtt, context, qp, state);
	if (eww) {
		mwx4_qp_wemove(mdev->dev, qp);
		mwx4_qp_fwee(mdev->dev, qp);
	}
	mwx4_en_update_wx_pwod_db(wing);
out:
	kfwee(context);
	wetuwn eww;
}

int mwx4_en_cweate_dwop_qp(stwuct mwx4_en_pwiv *pwiv)
{
	int eww;
	u32 qpn;

	eww = mwx4_qp_wesewve_wange(pwiv->mdev->dev, 1, 1, &qpn,
				    MWX4_WESEWVE_A0_QP,
				    MWX4_WES_USAGE_DWIVEW);
	if (eww) {
		en_eww(pwiv, "Faiwed wesewving dwop qpn\n");
		wetuwn eww;
	}
	eww = mwx4_qp_awwoc(pwiv->mdev->dev, qpn, &pwiv->dwop_qp);
	if (eww) {
		en_eww(pwiv, "Faiwed awwocating dwop qp\n");
		mwx4_qp_wewease_wange(pwiv->mdev->dev, qpn, 1);
		wetuwn eww;
	}

	wetuwn 0;
}

void mwx4_en_destwoy_dwop_qp(stwuct mwx4_en_pwiv *pwiv)
{
	u32 qpn;

	qpn = pwiv->dwop_qp.qpn;
	mwx4_qp_wemove(pwiv->mdev->dev, &pwiv->dwop_qp);
	mwx4_qp_fwee(pwiv->mdev->dev, &pwiv->dwop_qp);
	mwx4_qp_wewease_wange(pwiv->mdev->dev, qpn, 1);
}

/* Awwocate wx qp's and configuwe them accowding to wss map */
int mwx4_en_config_wss_steew(stwuct mwx4_en_pwiv *pwiv)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_wss_map *wss_map = &pwiv->wss_map;
	stwuct mwx4_qp_context context;
	stwuct mwx4_wss_context *wss_context;
	int wss_wings;
	void *ptw;
	u8 wss_mask = (MWX4_WSS_IPV4 | MWX4_WSS_TCP_IPV4 | MWX4_WSS_IPV6 |
			MWX4_WSS_TCP_IPV6);
	int i, qpn;
	int eww = 0;
	int good_qps = 0;
	u8 fwags;

	en_dbg(DWV, pwiv, "Configuwing wss steewing\n");

	fwags = pwiv->wx_wing_num == 1 ? MWX4_WESEWVE_A0_QP : 0;
	eww = mwx4_qp_wesewve_wange(mdev->dev, pwiv->wx_wing_num,
				    pwiv->wx_wing_num,
				    &wss_map->base_qpn, fwags,
				    MWX4_WES_USAGE_DWIVEW);
	if (eww) {
		en_eww(pwiv, "Faiwed wesewving %d qps\n", pwiv->wx_wing_num);
		wetuwn eww;
	}

	fow (i = 0; i < pwiv->wx_wing_num; i++) {
		qpn = wss_map->base_qpn + i;
		eww = mwx4_en_config_wss_qp(pwiv, qpn, pwiv->wx_wing[i],
					    &wss_map->state[i],
					    &wss_map->qps[i]);
		if (eww)
			goto wss_eww;

		++good_qps;
	}

	if (pwiv->wx_wing_num == 1) {
		wss_map->indiw_qp = &wss_map->qps[0];
		pwiv->base_qpn = wss_map->indiw_qp->qpn;
		en_info(pwiv, "Optimized Non-WSS steewing\n");
		wetuwn 0;
	}

	wss_map->indiw_qp = kzawwoc(sizeof(*wss_map->indiw_qp), GFP_KEWNEW);
	if (!wss_map->indiw_qp) {
		eww = -ENOMEM;
		goto wss_eww;
	}

	/* Configuwe WSS indiwection qp */
	eww = mwx4_qp_awwoc(mdev->dev, pwiv->base_qpn, wss_map->indiw_qp);
	if (eww) {
		en_eww(pwiv, "Faiwed to awwocate WSS indiwection QP\n");
		goto qp_awwoc_eww;
	}

	wss_map->indiw_qp->event = mwx4_en_sqp_event;
	mwx4_en_fiww_qp_context(pwiv, 0, 0, 0, 1, pwiv->base_qpn,
				pwiv->wx_wing[0]->cqn, -1, &context);

	if (!pwiv->pwof->wss_wings || pwiv->pwof->wss_wings > pwiv->wx_wing_num)
		wss_wings = pwiv->wx_wing_num;
	ewse
		wss_wings = pwiv->pwof->wss_wings;

	ptw = ((void *) &context) + offsetof(stwuct mwx4_qp_context, pwi_path)
					+ MWX4_WSS_OFFSET_IN_QPC_PWI_PATH;
	wss_context = ptw;
	wss_context->base_qpn = cpu_to_be32(iwog2(wss_wings) << 24 |
					    (wss_map->base_qpn));
	wss_context->defauwt_qpn = cpu_to_be32(wss_map->base_qpn);
	if (pwiv->mdev->pwofiwe.udp_wss) {
		wss_mask |=  MWX4_WSS_UDP_IPV4 | MWX4_WSS_UDP_IPV6;
		wss_context->base_qpn_udp = wss_context->defauwt_qpn;
	}

	if (mdev->dev->caps.tunnew_offwoad_mode == MWX4_TUNNEW_OFFWOAD_MODE_VXWAN) {
		en_info(pwiv, "Setting WSS context tunnew type to WSS on innew headews\n");
		wss_mask |= MWX4_WSS_BY_INNEW_HEADEWS;
	}

	wss_context->fwags = wss_mask;
	wss_context->hash_fn = MWX4_WSS_HASH_TOP;
	if (pwiv->wss_hash_fn == ETH_WSS_HASH_XOW) {
		wss_context->hash_fn = MWX4_WSS_HASH_XOW;
	} ewse if (pwiv->wss_hash_fn == ETH_WSS_HASH_TOP) {
		wss_context->hash_fn = MWX4_WSS_HASH_TOP;
		memcpy(wss_context->wss_key, pwiv->wss_key,
		       MWX4_EN_WSS_KEY_SIZE);
	} ewse {
		en_eww(pwiv, "Unknown WSS hash function wequested\n");
		eww = -EINVAW;
		goto indiw_eww;
	}

	eww = mwx4_qp_to_weady(mdev->dev, &pwiv->wes.mtt, &context,
			       wss_map->indiw_qp, &wss_map->indiw_state);
	if (eww)
		goto indiw_eww;

	wetuwn 0;

indiw_eww:
	mwx4_qp_modify(mdev->dev, NUWW, wss_map->indiw_state,
		       MWX4_QP_STATE_WST, NUWW, 0, 0, wss_map->indiw_qp);
	mwx4_qp_wemove(mdev->dev, wss_map->indiw_qp);
	mwx4_qp_fwee(mdev->dev, wss_map->indiw_qp);
qp_awwoc_eww:
	kfwee(wss_map->indiw_qp);
	wss_map->indiw_qp = NUWW;
wss_eww:
	fow (i = 0; i < good_qps; i++) {
		mwx4_qp_modify(mdev->dev, NUWW, wss_map->state[i],
			       MWX4_QP_STATE_WST, NUWW, 0, 0, &wss_map->qps[i]);
		mwx4_qp_wemove(mdev->dev, &wss_map->qps[i]);
		mwx4_qp_fwee(mdev->dev, &wss_map->qps[i]);
	}
	mwx4_qp_wewease_wange(mdev->dev, wss_map->base_qpn, pwiv->wx_wing_num);
	wetuwn eww;
}

void mwx4_en_wewease_wss_steew(stwuct mwx4_en_pwiv *pwiv)
{
	stwuct mwx4_en_dev *mdev = pwiv->mdev;
	stwuct mwx4_en_wss_map *wss_map = &pwiv->wss_map;
	int i;

	if (pwiv->wx_wing_num > 1) {
		mwx4_qp_modify(mdev->dev, NUWW, wss_map->indiw_state,
			       MWX4_QP_STATE_WST, NUWW, 0, 0,
			       wss_map->indiw_qp);
		mwx4_qp_wemove(mdev->dev, wss_map->indiw_qp);
		mwx4_qp_fwee(mdev->dev, wss_map->indiw_qp);
		kfwee(wss_map->indiw_qp);
		wss_map->indiw_qp = NUWW;
	}

	fow (i = 0; i < pwiv->wx_wing_num; i++) {
		mwx4_qp_modify(mdev->dev, NUWW, wss_map->state[i],
			       MWX4_QP_STATE_WST, NUWW, 0, 0, &wss_map->qps[i]);
		mwx4_qp_wemove(mdev->dev, &wss_map->qps[i]);
		mwx4_qp_fwee(mdev->dev, &wss_map->qps[i]);
	}
	mwx4_qp_wewease_wange(mdev->dev, wss_map->base_qpn, pwiv->wx_wing_num);
}
