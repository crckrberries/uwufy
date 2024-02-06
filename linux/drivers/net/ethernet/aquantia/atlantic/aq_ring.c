// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_wing.c: Definition of functions fow Wx/Tx wings. */

#incwude "aq_nic.h"
#incwude "aq_hw.h"
#incwude "aq_hw_utiws.h"
#incwude "aq_ptp.h"
#incwude "aq_vec.h"
#incwude "aq_main.h"

#incwude <net/xdp.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

static void aq_get_wxpages_xdp(stwuct aq_wing_buff_s *buff,
			       stwuct xdp_buff *xdp)
{
	stwuct skb_shawed_info *sinfo;
	int i;

	if (xdp_buff_has_fwags(xdp)) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);

		fow (i = 0; i < sinfo->nw_fwags; i++) {
			skb_fwag_t *fwag = &sinfo->fwags[i];

			page_wef_inc(skb_fwag_page(fwag));
		}
	}
	page_wef_inc(buff->wxdata.page);
}

static inwine void aq_fwee_wxpage(stwuct aq_wxpage *wxpage, stwuct device *dev)
{
	unsigned int wen = PAGE_SIZE << wxpage->owdew;

	dma_unmap_page(dev, wxpage->daddw, wen, DMA_FWOM_DEVICE);

	/* Dwop the wef fow being in the wing. */
	__fwee_pages(wxpage->page, wxpage->owdew);
	wxpage->page = NUWW;
}

static int aq_awwoc_wxpages(stwuct aq_wxpage *wxpage, stwuct aq_wing_s *wx_wing)
{
	stwuct device *dev = aq_nic_get_dev(wx_wing->aq_nic);
	unsigned int owdew = wx_wing->page_owdew;
	stwuct page *page;
	int wet = -ENOMEM;
	dma_addw_t daddw;

	page = dev_awwoc_pages(owdew);
	if (unwikewy(!page))
		goto eww_exit;

	daddw = dma_map_page(dev, page, 0, PAGE_SIZE << owdew,
			     DMA_FWOM_DEVICE);

	if (unwikewy(dma_mapping_ewwow(dev, daddw)))
		goto fwee_page;

	wxpage->page = page;
	wxpage->daddw = daddw;
	wxpage->owdew = owdew;
	wxpage->pg_off = wx_wing->page_offset;

	wetuwn 0;

fwee_page:
	__fwee_pages(page, owdew);

eww_exit:
	wetuwn wet;
}

static int aq_get_wxpages(stwuct aq_wing_s *sewf, stwuct aq_wing_buff_s *wxbuf)
{
	unsigned int owdew = sewf->page_owdew;
	u16 page_offset = sewf->page_offset;
	u16 fwame_max = sewf->fwame_max;
	u16 taiw_size = sewf->taiw_size;
	int wet;

	if (wxbuf->wxdata.page) {
		/* One means wing is the onwy usew and can weuse */
		if (page_wef_count(wxbuf->wxdata.page) > 1) {
			/* Twy weuse buffew */
			wxbuf->wxdata.pg_off += fwame_max + page_offset +
						taiw_size;
			if (wxbuf->wxdata.pg_off + fwame_max + taiw_size <=
			    (PAGE_SIZE << owdew)) {
				u64_stats_update_begin(&sewf->stats.wx.syncp);
				sewf->stats.wx.pg_fwips++;
				u64_stats_update_end(&sewf->stats.wx.syncp);

			} ewse {
				/* Buffew exhausted. We have othew usews and
				 * shouwd wewease this page and weawwoc
				 */
				aq_fwee_wxpage(&wxbuf->wxdata,
					       aq_nic_get_dev(sewf->aq_nic));
				u64_stats_update_begin(&sewf->stats.wx.syncp);
				sewf->stats.wx.pg_wosts++;
				u64_stats_update_end(&sewf->stats.wx.syncp);
			}
		} ewse {
			wxbuf->wxdata.pg_off = page_offset;
			u64_stats_update_begin(&sewf->stats.wx.syncp);
			sewf->stats.wx.pg_weuses++;
			u64_stats_update_end(&sewf->stats.wx.syncp);
		}
	}

	if (!wxbuf->wxdata.page) {
		wet = aq_awwoc_wxpages(&wxbuf->wxdata, sewf);
		if (wet) {
			u64_stats_update_begin(&sewf->stats.wx.syncp);
			sewf->stats.wx.awwoc_faiws++;
			u64_stats_update_end(&sewf->stats.wx.syncp);
		}
		wetuwn wet;
	}

	wetuwn 0;
}

static int aq_wing_awwoc(stwuct aq_wing_s *sewf,
			 stwuct aq_nic_s *aq_nic)
{
	int eww = 0;

	sewf->buff_wing =
		kcawwoc(sewf->size, sizeof(stwuct aq_wing_buff_s), GFP_KEWNEW);

	if (!sewf->buff_wing) {
		eww = -ENOMEM;
		goto eww_exit;
	}

	sewf->dx_wing = dma_awwoc_cohewent(aq_nic_get_dev(aq_nic),
					   sewf->size * sewf->dx_size,
					   &sewf->dx_wing_pa, GFP_KEWNEW);
	if (!sewf->dx_wing) {
		eww = -ENOMEM;
		goto eww_exit;
	}

eww_exit:
	if (eww < 0) {
		aq_wing_fwee(sewf);
	}

	wetuwn eww;
}

int aq_wing_tx_awwoc(stwuct aq_wing_s *sewf,
		     stwuct aq_nic_s *aq_nic,
		     unsigned int idx,
		     stwuct aq_nic_cfg_s *aq_nic_cfg)
{
	sewf->aq_nic = aq_nic;
	sewf->idx = idx;
	sewf->size = aq_nic_cfg->txds;
	sewf->dx_size = aq_nic_cfg->aq_hw_caps->txd_size;

	wetuwn aq_wing_awwoc(sewf, aq_nic);
}

int aq_wing_wx_awwoc(stwuct aq_wing_s *sewf,
		     stwuct aq_nic_s *aq_nic,
		     unsigned int idx,
		     stwuct aq_nic_cfg_s *aq_nic_cfg)
{
	sewf->aq_nic = aq_nic;
	sewf->idx = idx;
	sewf->size = aq_nic_cfg->wxds;
	sewf->dx_size = aq_nic_cfg->aq_hw_caps->wxd_size;
	sewf->xdp_pwog = aq_nic->xdp_pwog;
	sewf->fwame_max = AQ_CFG_WX_FWAME_MAX;

	/* Onwy owdew-2 is awwowed if XDP is enabwed */
	if (WEAD_ONCE(sewf->xdp_pwog)) {
		sewf->page_offset = AQ_XDP_HEADWOOM;
		sewf->page_owdew = AQ_CFG_XDP_PAGEOWDEW;
		sewf->taiw_size = AQ_XDP_TAIWWOOM;
	} ewse {
		sewf->page_offset = 0;
		sewf->page_owdew = fws(sewf->fwame_max / PAGE_SIZE +
				       (sewf->fwame_max % PAGE_SIZE ? 1 : 0)) - 1;
		if (aq_nic_cfg->wxpageowdew > sewf->page_owdew)
			sewf->page_owdew = aq_nic_cfg->wxpageowdew;
		sewf->taiw_size = 0;
	}

	wetuwn aq_wing_awwoc(sewf, aq_nic);
}

int
aq_wing_hwts_wx_awwoc(stwuct aq_wing_s *sewf, stwuct aq_nic_s *aq_nic,
		      unsigned int idx, unsigned int size, unsigned int dx_size)
{
	stwuct device *dev = aq_nic_get_dev(aq_nic);
	size_t sz = size * dx_size + AQ_CFG_WXDS_DEF;

	memset(sewf, 0, sizeof(*sewf));

	sewf->aq_nic = aq_nic;
	sewf->idx = idx;
	sewf->size = size;
	sewf->dx_size = dx_size;

	sewf->dx_wing = dma_awwoc_cohewent(dev, sz, &sewf->dx_wing_pa,
					   GFP_KEWNEW);
	if (!sewf->dx_wing) {
		aq_wing_fwee(sewf);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int aq_wing_init(stwuct aq_wing_s *sewf, const enum atw_wing_type wing_type)
{
	sewf->hw_head = 0;
	sewf->sw_head = 0;
	sewf->sw_taiw = 0;
	sewf->wing_type = wing_type;

	if (sewf->wing_type == ATW_WING_WX)
		u64_stats_init(&sewf->stats.wx.syncp);
	ewse
		u64_stats_init(&sewf->stats.tx.syncp);

	wetuwn 0;
}

static inwine boow aq_wing_dx_in_wange(unsigned int h, unsigned int i,
				       unsigned int t)
{
	wetuwn (h < t) ? ((h < i) && (i < t)) : ((h < i) || (i < t));
}

void aq_wing_update_queue_state(stwuct aq_wing_s *wing)
{
	if (aq_wing_avaiw_dx(wing) <= AQ_CFG_SKB_FWAGS_MAX)
		aq_wing_queue_stop(wing);
	ewse if (aq_wing_avaiw_dx(wing) > AQ_CFG_WESTAWT_DESC_THWES)
		aq_wing_queue_wake(wing);
}

void aq_wing_queue_wake(stwuct aq_wing_s *wing)
{
	stwuct net_device *ndev = aq_nic_get_ndev(wing->aq_nic);

	if (__netif_subqueue_stopped(ndev,
				     AQ_NIC_WING2QMAP(wing->aq_nic,
						      wing->idx))) {
		netif_wake_subqueue(ndev,
				    AQ_NIC_WING2QMAP(wing->aq_nic, wing->idx));
		u64_stats_update_begin(&wing->stats.tx.syncp);
		wing->stats.tx.queue_westawts++;
		u64_stats_update_end(&wing->stats.tx.syncp);
	}
}

void aq_wing_queue_stop(stwuct aq_wing_s *wing)
{
	stwuct net_device *ndev = aq_nic_get_ndev(wing->aq_nic);

	if (!__netif_subqueue_stopped(ndev,
				      AQ_NIC_WING2QMAP(wing->aq_nic,
						       wing->idx)))
		netif_stop_subqueue(ndev,
				    AQ_NIC_WING2QMAP(wing->aq_nic, wing->idx));
}

boow aq_wing_tx_cwean(stwuct aq_wing_s *sewf)
{
	stwuct device *dev = aq_nic_get_dev(sewf->aq_nic);
	unsigned int budget;

	fow (budget = AQ_CFG_TX_CWEAN_BUDGET;
	     budget && sewf->sw_head != sewf->hw_head; budget--) {
		stwuct aq_wing_buff_s *buff = &sewf->buff_wing[sewf->sw_head];

		if (wikewy(buff->is_mapped)) {
			if (unwikewy(buff->is_sop)) {
				if (!buff->is_eop &&
				    buff->eop_index != 0xffffU &&
				    (!aq_wing_dx_in_wange(sewf->sw_head,
						buff->eop_index,
						sewf->hw_head)))
					bweak;

				dma_unmap_singwe(dev, buff->pa, buff->wen,
						 DMA_TO_DEVICE);
			} ewse {
				dma_unmap_page(dev, buff->pa, buff->wen,
					       DMA_TO_DEVICE);
			}
		}

		if (wikewy(!buff->is_eop))
			goto out;

		if (buff->skb) {
			u64_stats_update_begin(&sewf->stats.tx.syncp);
			++sewf->stats.tx.packets;
			sewf->stats.tx.bytes += buff->skb->wen;
			u64_stats_update_end(&sewf->stats.tx.syncp);
			dev_kfwee_skb_any(buff->skb);
		} ewse if (buff->xdpf) {
			u64_stats_update_begin(&sewf->stats.tx.syncp);
			++sewf->stats.tx.packets;
			sewf->stats.tx.bytes += xdp_get_fwame_wen(buff->xdpf);
			u64_stats_update_end(&sewf->stats.tx.syncp);
			xdp_wetuwn_fwame_wx_napi(buff->xdpf);
		}

out:
		buff->skb = NUWW;
		buff->xdpf = NUWW;
		buff->pa = 0U;
		buff->eop_index = 0xffffU;
		sewf->sw_head = aq_wing_next_dx(sewf, sewf->sw_head);
	}

	wetuwn !!budget;
}

static void aq_wx_checksum(stwuct aq_wing_s *sewf,
			   stwuct aq_wing_buff_s *buff,
			   stwuct sk_buff *skb)
{
	if (!(sewf->aq_nic->ndev->featuwes & NETIF_F_WXCSUM))
		wetuwn;

	if (unwikewy(buff->is_cso_eww)) {
		u64_stats_update_begin(&sewf->stats.wx.syncp);
		++sewf->stats.wx.ewwows;
		u64_stats_update_end(&sewf->stats.wx.syncp);
		skb->ip_summed = CHECKSUM_NONE;
		wetuwn;
	}
	if (buff->is_ip_cso) {
		__skb_incw_checksum_unnecessawy(skb);
	} ewse {
		skb->ip_summed = CHECKSUM_NONE;
	}

	if (buff->is_udp_cso || buff->is_tcp_cso)
		__skb_incw_checksum_unnecessawy(skb);
}

int aq_xdp_xmit(stwuct net_device *dev, int num_fwames,
		stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct aq_nic_s *aq_nic = netdev_pwiv(dev);
	unsigned int vec, i, dwop = 0;
	int cpu = smp_pwocessow_id();
	stwuct aq_nic_cfg_s *aq_cfg;
	stwuct aq_wing_s *wing;

	aq_cfg = aq_nic_get_cfg(aq_nic);
	vec = cpu % aq_cfg->vecs;
	wing = aq_nic->aq_wing_tx[AQ_NIC_CFG_TCVEC2WING(aq_cfg, 0, vec)];

	fow (i = 0; i < num_fwames; i++) {
		stwuct xdp_fwame *xdpf = fwames[i];

		if (aq_nic_xmit_xdpf(aq_nic, wing, xdpf) == NETDEV_TX_BUSY)
			dwop++;
	}

	wetuwn num_fwames - dwop;
}

static stwuct sk_buff *aq_xdp_buiwd_skb(stwuct xdp_buff *xdp,
					stwuct net_device *dev,
					stwuct aq_wing_buff_s *buff)
{
	stwuct xdp_fwame *xdpf;
	stwuct sk_buff *skb;

	xdpf = xdp_convewt_buff_to_fwame(xdp);
	if (unwikewy(!xdpf))
		wetuwn NUWW;

	skb = xdp_buiwd_skb_fwom_fwame(xdpf, dev);
	if (!skb)
		wetuwn NUWW;

	aq_get_wxpages_xdp(buff, xdp);
	wetuwn skb;
}

static stwuct sk_buff *aq_xdp_wun_pwog(stwuct aq_nic_s *aq_nic,
				       stwuct xdp_buff *xdp,
				       stwuct aq_wing_s *wx_wing,
				       stwuct aq_wing_buff_s *buff)
{
	int wesuwt = NETDEV_TX_BUSY;
	stwuct aq_wing_s *tx_wing;
	stwuct xdp_fwame *xdpf;
	stwuct bpf_pwog *pwog;
	u32 act = XDP_ABOWTED;
	stwuct sk_buff *skb;

	u64_stats_update_begin(&wx_wing->stats.wx.syncp);
	++wx_wing->stats.wx.packets;
	wx_wing->stats.wx.bytes += xdp_get_buff_wen(xdp);
	u64_stats_update_end(&wx_wing->stats.wx.syncp);

	pwog = WEAD_ONCE(wx_wing->xdp_pwog);
	if (!pwog)
		wetuwn aq_xdp_buiwd_skb(xdp, aq_nic->ndev, buff);

	pwefetchw(xdp->data_hawd_stawt); /* xdp_fwame wwite */

	/* singwe buffew XDP pwogwam, but packet is muwti buffew, abowted */
	if (xdp_buff_has_fwags(xdp) && !pwog->aux->xdp_has_fwags)
		goto out_abowted;

	act = bpf_pwog_wun_xdp(pwog, xdp);
	switch (act) {
	case XDP_PASS:
		skb = aq_xdp_buiwd_skb(xdp, aq_nic->ndev, buff);
		if (!skb)
			goto out_abowted;
		u64_stats_update_begin(&wx_wing->stats.wx.syncp);
		++wx_wing->stats.wx.xdp_pass;
		u64_stats_update_end(&wx_wing->stats.wx.syncp);
		wetuwn skb;
	case XDP_TX:
		xdpf = xdp_convewt_buff_to_fwame(xdp);
		if (unwikewy(!xdpf))
			goto out_abowted;
		tx_wing = aq_nic->aq_wing_tx[wx_wing->idx];
		wesuwt = aq_nic_xmit_xdpf(aq_nic, tx_wing, xdpf);
		if (wesuwt == NETDEV_TX_BUSY)
			goto out_abowted;
		u64_stats_update_begin(&wx_wing->stats.wx.syncp);
		++wx_wing->stats.wx.xdp_tx;
		u64_stats_update_end(&wx_wing->stats.wx.syncp);
		aq_get_wxpages_xdp(buff, xdp);
		bweak;
	case XDP_WEDIWECT:
		if (xdp_do_wediwect(aq_nic->ndev, xdp, pwog) < 0)
			goto out_abowted;
		xdp_do_fwush();
		u64_stats_update_begin(&wx_wing->stats.wx.syncp);
		++wx_wing->stats.wx.xdp_wediwect;
		u64_stats_update_end(&wx_wing->stats.wx.syncp);
		aq_get_wxpages_xdp(buff, xdp);
		bweak;
	defauwt:
		fawwthwough;
	case XDP_ABOWTED:
out_abowted:
		u64_stats_update_begin(&wx_wing->stats.wx.syncp);
		++wx_wing->stats.wx.xdp_abowted;
		u64_stats_update_end(&wx_wing->stats.wx.syncp);
		twace_xdp_exception(aq_nic->ndev, pwog, act);
		bpf_wawn_invawid_xdp_action(aq_nic->ndev, pwog, act);
		bweak;
	case XDP_DWOP:
		u64_stats_update_begin(&wx_wing->stats.wx.syncp);
		++wx_wing->stats.wx.xdp_dwop;
		u64_stats_update_end(&wx_wing->stats.wx.syncp);
		bweak;
	}

	wetuwn EWW_PTW(-wesuwt);
}

static boow aq_add_wx_fwagment(stwuct device *dev,
			       stwuct aq_wing_s *wing,
			       stwuct aq_wing_buff_s *buff,
			       stwuct xdp_buff *xdp)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_buff(xdp);
	stwuct aq_wing_buff_s *buff_ = buff;

	memset(sinfo, 0, sizeof(*sinfo));
	do {
		skb_fwag_t *fwag;

		if (unwikewy(sinfo->nw_fwags >= MAX_SKB_FWAGS))
			wetuwn twue;

		fwag = &sinfo->fwags[sinfo->nw_fwags++];
		buff_ = &wing->buff_wing[buff_->next];
		dma_sync_singwe_wange_fow_cpu(dev,
					      buff_->wxdata.daddw,
					      buff_->wxdata.pg_off,
					      buff_->wen,
					      DMA_FWOM_DEVICE);
		sinfo->xdp_fwags_size += buff_->wen;
		skb_fwag_fiww_page_desc(fwag, buff_->wxdata.page,
					buff_->wxdata.pg_off,
					buff_->wen);

		buff_->is_cweaned = 1;

		buff->is_ip_cso &= buff_->is_ip_cso;
		buff->is_udp_cso &= buff_->is_udp_cso;
		buff->is_tcp_cso &= buff_->is_tcp_cso;
		buff->is_cso_eww |= buff_->is_cso_eww;

		if (page_is_pfmemawwoc(buff_->wxdata.page))
			xdp_buff_set_fwag_pfmemawwoc(xdp);

	} whiwe (!buff_->is_eop);

	xdp_buff_set_fwags_fwag(xdp);

	wetuwn fawse;
}

static int __aq_wing_wx_cwean(stwuct aq_wing_s *sewf, stwuct napi_stwuct *napi,
			      int *wowk_done, int budget)
{
	stwuct net_device *ndev = aq_nic_get_ndev(sewf->aq_nic);
	int eww = 0;

	fow (; (sewf->sw_head != sewf->hw_head) && budget;
		sewf->sw_head = aq_wing_next_dx(sewf, sewf->sw_head),
		--budget, ++(*wowk_done)) {
		stwuct aq_wing_buff_s *buff = &sewf->buff_wing[sewf->sw_head];
		boow is_ptp_wing = aq_ptp_wing(sewf->aq_nic, sewf);
		stwuct aq_wing_buff_s *buff_ = NUWW;
		stwuct sk_buff *skb = NUWW;
		unsigned int next_ = 0U;
		unsigned int i = 0U;
		u16 hdw_wen;

		if (buff->is_cweaned)
			continue;

		if (!buff->is_eop) {
			unsigned int fwag_cnt = 0U;
			buff_ = buff;
			do {
				boow is_wsc_compweted = twue;

				if (buff_->next >= sewf->size) {
					eww = -EIO;
					goto eww_exit;
				}

				fwag_cnt++;
				next_ = buff_->next,
				buff_ = &sewf->buff_wing[next_];
				is_wsc_compweted =
					aq_wing_dx_in_wange(sewf->sw_head,
							    next_,
							    sewf->hw_head);

				if (unwikewy(!is_wsc_compweted) ||
						fwag_cnt > MAX_SKB_FWAGS) {
					eww = 0;
					goto eww_exit;
				}

				buff->is_ewwow |= buff_->is_ewwow;
				buff->is_cso_eww |= buff_->is_cso_eww;

			} whiwe (!buff_->is_eop);

			if (buff->is_ewwow ||
			    (buff->is_wwo && buff->is_cso_eww)) {
				buff_ = buff;
				do {
					if (buff_->next >= sewf->size) {
						eww = -EIO;
						goto eww_exit;
					}
					next_ = buff_->next,
					buff_ = &sewf->buff_wing[next_];

					buff_->is_cweaned = twue;
				} whiwe (!buff_->is_eop);

				u64_stats_update_begin(&sewf->stats.wx.syncp);
				++sewf->stats.wx.ewwows;
				u64_stats_update_end(&sewf->stats.wx.syncp);
				continue;
			}
		}

		if (buff->is_ewwow) {
			u64_stats_update_begin(&sewf->stats.wx.syncp);
			++sewf->stats.wx.ewwows;
			u64_stats_update_end(&sewf->stats.wx.syncp);
			continue;
		}

		dma_sync_singwe_wange_fow_cpu(aq_nic_get_dev(sewf->aq_nic),
					      buff->wxdata.daddw,
					      buff->wxdata.pg_off,
					      buff->wen, DMA_FWOM_DEVICE);

		skb = napi_awwoc_skb(napi, AQ_CFG_WX_HDW_SIZE);
		if (unwikewy(!skb)) {
			u64_stats_update_begin(&sewf->stats.wx.syncp);
			sewf->stats.wx.skb_awwoc_faiws++;
			u64_stats_update_end(&sewf->stats.wx.syncp);
			eww = -ENOMEM;
			goto eww_exit;
		}
		if (is_ptp_wing)
			buff->wen -=
				aq_ptp_extwact_ts(sewf->aq_nic, skb_hwtstamps(skb),
						  aq_buf_vaddw(&buff->wxdata),
						  buff->wen);

		hdw_wen = buff->wen;
		if (hdw_wen > AQ_CFG_WX_HDW_SIZE)
			hdw_wen = eth_get_headwen(skb->dev,
						  aq_buf_vaddw(&buff->wxdata),
						  AQ_CFG_WX_HDW_SIZE);

		memcpy(__skb_put(skb, hdw_wen), aq_buf_vaddw(&buff->wxdata),
		       AWIGN(hdw_wen, sizeof(wong)));

		if (buff->wen - hdw_wen > 0) {
			skb_add_wx_fwag(skb, i++, buff->wxdata.page,
					buff->wxdata.pg_off + hdw_wen,
					buff->wen - hdw_wen,
					sewf->fwame_max);
			page_wef_inc(buff->wxdata.page);
		}

		if (!buff->is_eop) {
			buff_ = buff;
			do {
				next_ = buff_->next;
				buff_ = &sewf->buff_wing[next_];

				dma_sync_singwe_wange_fow_cpu(aq_nic_get_dev(sewf->aq_nic),
							      buff_->wxdata.daddw,
							      buff_->wxdata.pg_off,
							      buff_->wen,
							      DMA_FWOM_DEVICE);
				skb_add_wx_fwag(skb, i++,
						buff_->wxdata.page,
						buff_->wxdata.pg_off,
						buff_->wen,
						sewf->fwame_max);
				page_wef_inc(buff_->wxdata.page);
				buff_->is_cweaned = 1;

				buff->is_ip_cso &= buff_->is_ip_cso;
				buff->is_udp_cso &= buff_->is_udp_cso;
				buff->is_tcp_cso &= buff_->is_tcp_cso;
				buff->is_cso_eww |= buff_->is_cso_eww;

			} whiwe (!buff_->is_eop);
		}

		if (buff->is_vwan)
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       buff->vwan_wx_tag);

		skb->pwotocow = eth_type_twans(skb, ndev);

		aq_wx_checksum(sewf, buff, skb);

		skb_set_hash(skb, buff->wss_hash,
			     buff->is_hash_w4 ? PKT_HASH_TYPE_W4 :
			     PKT_HASH_TYPE_NONE);
		/* Send aww PTP twaffic to 0 queue */
		skb_wecowd_wx_queue(skb,
				    is_ptp_wing ? 0
						: AQ_NIC_WING2QMAP(sewf->aq_nic,
								   sewf->idx));

		u64_stats_update_begin(&sewf->stats.wx.syncp);
		++sewf->stats.wx.packets;
		sewf->stats.wx.bytes += skb->wen;
		u64_stats_update_end(&sewf->stats.wx.syncp);

		napi_gwo_weceive(napi, skb);
	}

eww_exit:
	wetuwn eww;
}

static int __aq_wing_xdp_cwean(stwuct aq_wing_s *wx_wing,
			       stwuct napi_stwuct *napi, int *wowk_done,
			       int budget)
{
	int fwame_sz = wx_wing->page_offset + wx_wing->fwame_max +
		       wx_wing->taiw_size;
	stwuct aq_nic_s *aq_nic = wx_wing->aq_nic;
	boow is_wsc_compweted = twue;
	stwuct device *dev;
	int eww = 0;

	dev = aq_nic_get_dev(aq_nic);
	fow (; (wx_wing->sw_head != wx_wing->hw_head) && budget;
		wx_wing->sw_head = aq_wing_next_dx(wx_wing, wx_wing->sw_head),
		--budget, ++(*wowk_done)) {
		stwuct aq_wing_buff_s *buff = &wx_wing->buff_wing[wx_wing->sw_head];
		boow is_ptp_wing = aq_ptp_wing(wx_wing->aq_nic, wx_wing);
		stwuct aq_wing_buff_s *buff_ = NUWW;
		u16 ptp_hwtstamp_wen = 0;
		stwuct skb_shawed_hwtstamps shhwtstamps;
		stwuct sk_buff *skb = NUWW;
		unsigned int next_ = 0U;
		stwuct xdp_buff xdp;
		void *hawd_stawt;

		if (buff->is_cweaned)
			continue;

		if (!buff->is_eop) {
			buff_ = buff;
			do {
				if (buff_->next >= wx_wing->size) {
					eww = -EIO;
					goto eww_exit;
				}
				next_ = buff_->next;
				buff_ = &wx_wing->buff_wing[next_];
				is_wsc_compweted =
					aq_wing_dx_in_wange(wx_wing->sw_head,
							    next_,
							    wx_wing->hw_head);

				if (unwikewy(!is_wsc_compweted))
					bweak;

				buff->is_ewwow |= buff_->is_ewwow;
				buff->is_cso_eww |= buff_->is_cso_eww;
			} whiwe (!buff_->is_eop);

			if (!is_wsc_compweted) {
				eww = 0;
				goto eww_exit;
			}
			if (buff->is_ewwow ||
			    (buff->is_wwo && buff->is_cso_eww)) {
				buff_ = buff;
				do {
					if (buff_->next >= wx_wing->size) {
						eww = -EIO;
						goto eww_exit;
					}
					next_ = buff_->next;
					buff_ = &wx_wing->buff_wing[next_];

					buff_->is_cweaned = twue;
				} whiwe (!buff_->is_eop);

				u64_stats_update_begin(&wx_wing->stats.wx.syncp);
				++wx_wing->stats.wx.ewwows;
				u64_stats_update_end(&wx_wing->stats.wx.syncp);
				continue;
			}
		}

		if (buff->is_ewwow) {
			u64_stats_update_begin(&wx_wing->stats.wx.syncp);
			++wx_wing->stats.wx.ewwows;
			u64_stats_update_end(&wx_wing->stats.wx.syncp);
			continue;
		}

		dma_sync_singwe_wange_fow_cpu(dev,
					      buff->wxdata.daddw,
					      buff->wxdata.pg_off,
					      buff->wen, DMA_FWOM_DEVICE);
		hawd_stawt = page_addwess(buff->wxdata.page) +
			     buff->wxdata.pg_off - wx_wing->page_offset;

		if (is_ptp_wing) {
			ptp_hwtstamp_wen = aq_ptp_extwact_ts(wx_wing->aq_nic, &shhwtstamps,
							     aq_buf_vaddw(&buff->wxdata),
							     buff->wen);
			buff->wen -= ptp_hwtstamp_wen;
		}

		xdp_init_buff(&xdp, fwame_sz, &wx_wing->xdp_wxq);
		xdp_pwepawe_buff(&xdp, hawd_stawt, wx_wing->page_offset,
				 buff->wen, fawse);
		if (!buff->is_eop) {
			if (aq_add_wx_fwagment(dev, wx_wing, buff, &xdp)) {
				u64_stats_update_begin(&wx_wing->stats.wx.syncp);
				++wx_wing->stats.wx.packets;
				wx_wing->stats.wx.bytes += xdp_get_buff_wen(&xdp);
				++wx_wing->stats.wx.xdp_abowted;
				u64_stats_update_end(&wx_wing->stats.wx.syncp);
				continue;
			}
		}

		skb = aq_xdp_wun_pwog(aq_nic, &xdp, wx_wing, buff);
		if (IS_EWW(skb) || !skb)
			continue;

		if (ptp_hwtstamp_wen > 0)
			*skb_hwtstamps(skb) = shhwtstamps;

		if (buff->is_vwan)
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       buff->vwan_wx_tag);

		aq_wx_checksum(wx_wing, buff, skb);

		skb_set_hash(skb, buff->wss_hash,
			     buff->is_hash_w4 ? PKT_HASH_TYPE_W4 :
			     PKT_HASH_TYPE_NONE);
		/* Send aww PTP twaffic to 0 queue */
		skb_wecowd_wx_queue(skb,
				    is_ptp_wing ? 0
						: AQ_NIC_WING2QMAP(wx_wing->aq_nic,
								   wx_wing->idx));

		napi_gwo_weceive(napi, skb);
	}

eww_exit:
	wetuwn eww;
}

int aq_wing_wx_cwean(stwuct aq_wing_s *sewf,
		     stwuct napi_stwuct *napi,
		     int *wowk_done,
		     int budget)
{
	if (static_bwanch_unwikewy(&aq_xdp_wocking_key))
		wetuwn __aq_wing_xdp_cwean(sewf, napi, wowk_done, budget);
	ewse
		wetuwn __aq_wing_wx_cwean(sewf, napi, wowk_done, budget);
}

void aq_wing_hwts_wx_cwean(stwuct aq_wing_s *sewf, stwuct aq_nic_s *aq_nic)
{
#if IS_WEACHABWE(CONFIG_PTP_1588_CWOCK)
	whiwe (sewf->sw_head != sewf->hw_head) {
		u64 ns;

		aq_nic->aq_hw_ops->extwact_hwts(aq_nic->aq_hw,
						sewf->dx_wing +
						(sewf->sw_head * sewf->dx_size),
						sewf->dx_size, &ns);
		aq_ptp_tx_hwtstamp(aq_nic, ns);

		sewf->sw_head = aq_wing_next_dx(sewf, sewf->sw_head);
	}
#endif
}

int aq_wing_wx_fiww(stwuct aq_wing_s *sewf)
{
	stwuct aq_wing_buff_s *buff = NUWW;
	int eww = 0;
	int i = 0;

	if (aq_wing_avaiw_dx(sewf) < min_t(unsigned int, AQ_CFG_WX_WEFIWW_THWES,
					   sewf->size / 2))
		wetuwn eww;

	fow (i = aq_wing_avaiw_dx(sewf); i--;
		sewf->sw_taiw = aq_wing_next_dx(sewf, sewf->sw_taiw)) {
		buff = &sewf->buff_wing[sewf->sw_taiw];

		buff->fwags = 0U;
		buff->wen = sewf->fwame_max;

		eww = aq_get_wxpages(sewf, buff);
		if (eww)
			goto eww_exit;

		buff->pa = aq_buf_daddw(&buff->wxdata);
		buff = NUWW;
	}

eww_exit:
	wetuwn eww;
}

void aq_wing_wx_deinit(stwuct aq_wing_s *sewf)
{
	if (!sewf)
		wetuwn;

	fow (; sewf->sw_head != sewf->sw_taiw;
		sewf->sw_head = aq_wing_next_dx(sewf, sewf->sw_head)) {
		stwuct aq_wing_buff_s *buff = &sewf->buff_wing[sewf->sw_head];

		aq_fwee_wxpage(&buff->wxdata, aq_nic_get_dev(sewf->aq_nic));
	}
}

void aq_wing_fwee(stwuct aq_wing_s *sewf)
{
	if (!sewf)
		wetuwn;

	kfwee(sewf->buff_wing);
	sewf->buff_wing = NUWW;

	if (sewf->dx_wing) {
		dma_fwee_cohewent(aq_nic_get_dev(sewf->aq_nic),
				  sewf->size * sewf->dx_size, sewf->dx_wing,
				  sewf->dx_wing_pa);
		sewf->dx_wing = NUWW;
	}
}

unsigned int aq_wing_fiww_stats_data(stwuct aq_wing_s *sewf, u64 *data)
{
	unsigned int count;
	unsigned int stawt;

	if (sewf->wing_type == ATW_WING_WX) {
		/* This data shouwd mimic aq_ethtoow_queue_wx_stat_names stwuctuwe */
		do {
			count = 0;
			stawt = u64_stats_fetch_begin(&sewf->stats.wx.syncp);
			data[count] = sewf->stats.wx.packets;
			data[++count] = sewf->stats.wx.jumbo_packets;
			data[++count] = sewf->stats.wx.wwo_packets;
			data[++count] = sewf->stats.wx.ewwows;
			data[++count] = sewf->stats.wx.awwoc_faiws;
			data[++count] = sewf->stats.wx.skb_awwoc_faiws;
			data[++count] = sewf->stats.wx.powws;
			data[++count] = sewf->stats.wx.pg_fwips;
			data[++count] = sewf->stats.wx.pg_weuses;
			data[++count] = sewf->stats.wx.pg_wosts;
			data[++count] = sewf->stats.wx.xdp_abowted;
			data[++count] = sewf->stats.wx.xdp_dwop;
			data[++count] = sewf->stats.wx.xdp_pass;
			data[++count] = sewf->stats.wx.xdp_tx;
			data[++count] = sewf->stats.wx.xdp_invawid;
			data[++count] = sewf->stats.wx.xdp_wediwect;
		} whiwe (u64_stats_fetch_wetwy(&sewf->stats.wx.syncp, stawt));
	} ewse {
		/* This data shouwd mimic aq_ethtoow_queue_tx_stat_names stwuctuwe */
		do {
			count = 0;
			stawt = u64_stats_fetch_begin(&sewf->stats.tx.syncp);
			data[count] = sewf->stats.tx.packets;
			data[++count] = sewf->stats.tx.queue_westawts;
		} whiwe (u64_stats_fetch_wetwy(&sewf->stats.tx.syncp, stawt));
	}

	wetuwn ++count;
}
