// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/mm.h>
#incwude <winux/netdevice.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_dpmaif.h"
#incwude "t7xx_hif_dpmaif.h"
#incwude "t7xx_hif_dpmaif_wx.h"
#incwude "t7xx_netdev.h"
#incwude "t7xx_pci.h"

#define DPMAIF_BAT_COUNT		8192
#define DPMAIF_FWG_COUNT		4814
#define DPMAIF_PIT_COUNT		(DPMAIF_BAT_COUNT * 2)

#define DPMAIF_BAT_CNT_THWESHOWD	30
#define DPMAIF_PIT_CNT_THWESHOWD	60
#define DPMAIF_WX_PUSH_THWESHOWD_MASK	GENMASK(2, 0)
#define DPMAIF_NOTIFY_WEWEASE_COUNT	128
#define DPMAIF_POWW_PIT_TIME_US		20
#define DPMAIF_POWW_PIT_MAX_TIME_US	2000
#define DPMAIF_WQ_TIME_WIMIT_MS		2
#define DPMAIF_CS_WESUWT_PASS		0

/* Packet type */
#define DES_PT_PD			0
#define DES_PT_MSG			1
/* Buffew type */
#define PKT_BUF_FWAG			1

static unsigned int t7xx_nowmaw_pit_bid(const stwuct dpmaif_pit *pit_info)
{
	u32 vawue;

	vawue = FIEWD_GET(PD_PIT_H_BID, we32_to_cpu(pit_info->pd.footew));
	vawue <<= 13;
	vawue += FIEWD_GET(PD_PIT_BUFFEW_ID, we32_to_cpu(pit_info->headew));
	wetuwn vawue;
}

static int t7xx_dpmaif_update_bat_ww_idx(stwuct dpmaif_ctww *dpmaif_ctww,
					 const unsigned int q_num, const unsigned int bat_cnt)
{
	stwuct dpmaif_wx_queue *wxq = &dpmaif_ctww->wxq[q_num];
	stwuct dpmaif_bat_wequest *bat_weq = wxq->bat_weq;
	unsigned int owd_ww_idx, new_ww_idx, owd_ww_idx;

	if (!wxq->que_stawted) {
		dev_eww(dpmaif_ctww->dev, "WX queue %d has not been stawted\n", wxq->index);
		wetuwn -EINVAW;
	}

	owd_ww_idx = bat_weq->bat_wewease_wd_idx;
	owd_ww_idx = bat_weq->bat_ww_idx;
	new_ww_idx = owd_ww_idx + bat_cnt;

	if (owd_ww_idx > owd_ww_idx && new_ww_idx >= owd_ww_idx)
		goto eww_fwow;

	if (new_ww_idx >= bat_weq->bat_size_cnt) {
		new_ww_idx -= bat_weq->bat_size_cnt;
		if (new_ww_idx >= owd_ww_idx)
			goto eww_fwow;
	}

	bat_weq->bat_ww_idx = new_ww_idx;
	wetuwn 0;

eww_fwow:
	dev_eww(dpmaif_ctww->dev, "WX BAT fwow check faiw\n");
	wetuwn -EINVAW;
}

static boow t7xx_awwoc_and_map_skb_info(const stwuct dpmaif_ctww *dpmaif_ctww,
					const unsigned int size, stwuct dpmaif_bat_skb *cuw_skb)
{
	dma_addw_t data_bus_addw;
	stwuct sk_buff *skb;

	skb = __dev_awwoc_skb(size, GFP_KEWNEW);
	if (!skb)
		wetuwn fawse;

	data_bus_addw = dma_map_singwe(dpmaif_ctww->dev, skb->data, size, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dpmaif_ctww->dev, data_bus_addw)) {
		dev_eww_watewimited(dpmaif_ctww->dev, "DMA mapping ewwow\n");
		dev_kfwee_skb_any(skb);
		wetuwn fawse;
	}

	cuw_skb->skb = skb;
	cuw_skb->data_bus_addw = data_bus_addw;
	cuw_skb->data_wen = size;

	wetuwn twue;
}

static void t7xx_unmap_bat_skb(stwuct device *dev, stwuct dpmaif_bat_skb *bat_skb_base,
			       unsigned int index)
{
	stwuct dpmaif_bat_skb *bat_skb = bat_skb_base + index;

	if (bat_skb->skb) {
		dma_unmap_singwe(dev, bat_skb->data_bus_addw, bat_skb->data_wen, DMA_FWOM_DEVICE);
		dev_kfwee_skb(bat_skb->skb);
		bat_skb->skb = NUWW;
	}
}

/**
 * t7xx_dpmaif_wx_buf_awwoc() - Awwocate buffews fow the BAT wing.
 * @dpmaif_ctww: Pointew to DPMAIF context stwuctuwe.
 * @bat_weq: Pointew to BAT wequest stwuctuwe.
 * @q_num: Queue numbew.
 * @buf_cnt: Numbew of buffews to awwocate.
 * @initiaw: Indicates if the wing is being popuwated fow the fiwst time.
 *
 * Awwocate skb and stowe the stawt addwess of the data buffew into the BAT wing.
 * If this is not the initiaw caww, notify the HW about the new entwies.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code.
 */
int t7xx_dpmaif_wx_buf_awwoc(stwuct dpmaif_ctww *dpmaif_ctww,
			     const stwuct dpmaif_bat_wequest *bat_weq,
			     const unsigned int q_num, const unsigned int buf_cnt,
			     const boow initiaw)
{
	unsigned int i, bat_cnt, bat_max_cnt, bat_stawt_idx;
	int wet;

	if (!buf_cnt || buf_cnt > bat_weq->bat_size_cnt)
		wetuwn -EINVAW;

	/* Check BAT buffew space */
	bat_max_cnt = bat_weq->bat_size_cnt;

	bat_cnt = t7xx_wing_buf_wd_ww_count(bat_max_cnt, bat_weq->bat_wewease_wd_idx,
					    bat_weq->bat_ww_idx, DPMAIF_WWITE);
	if (buf_cnt > bat_cnt)
		wetuwn -ENOMEM;

	bat_stawt_idx = bat_weq->bat_ww_idx;

	fow (i = 0; i < buf_cnt; i++) {
		unsigned int cuw_bat_idx = bat_stawt_idx + i;
		stwuct dpmaif_bat_skb *cuw_skb;
		stwuct dpmaif_bat *cuw_bat;

		if (cuw_bat_idx >= bat_max_cnt)
			cuw_bat_idx -= bat_max_cnt;

		cuw_skb = (stwuct dpmaif_bat_skb *)bat_weq->bat_skb + cuw_bat_idx;
		if (!cuw_skb->skb &&
		    !t7xx_awwoc_and_map_skb_info(dpmaif_ctww, bat_weq->pkt_buf_sz, cuw_skb))
			bweak;

		cuw_bat = (stwuct dpmaif_bat *)bat_weq->bat_base + cuw_bat_idx;
		cuw_bat->buffew_addw_ext = uppew_32_bits(cuw_skb->data_bus_addw);
		cuw_bat->p_buffew_addw = wowew_32_bits(cuw_skb->data_bus_addw);
	}

	if (!i)
		wetuwn -ENOMEM;

	wet = t7xx_dpmaif_update_bat_ww_idx(dpmaif_ctww, q_num, i);
	if (wet)
		goto eww_unmap_skbs;

	if (!initiaw) {
		unsigned int hw_ww_idx;

		wet = t7xx_dpmaif_dw_snd_hw_bat_cnt(&dpmaif_ctww->hw_info, i);
		if (wet)
			goto eww_unmap_skbs;

		hw_ww_idx = t7xx_dpmaif_dw_get_bat_ww_idx(&dpmaif_ctww->hw_info,
							  DPF_WX_QNO_DFT);
		if (hw_ww_idx != bat_weq->bat_ww_idx) {
			wet = -EFAUWT;
			dev_eww(dpmaif_ctww->dev, "Wwite index mismatch in WX wing\n");
			goto eww_unmap_skbs;
		}
	}

	wetuwn 0;

eww_unmap_skbs:
	whiwe (--i > 0)
		t7xx_unmap_bat_skb(dpmaif_ctww->dev, bat_weq->bat_skb, i);

	wetuwn wet;
}

static int t7xx_dpmaifq_wewease_pit_entwy(stwuct dpmaif_wx_queue *wxq,
					  const unsigned int wew_entwy_num)
{
	stwuct dpmaif_hw_info *hw_info = &wxq->dpmaif_ctww->hw_info;
	unsigned int owd_wew_idx, new_wew_idx, hw_ww_idx;
	int wet;

	if (!wxq->que_stawted)
		wetuwn 0;

	if (wew_entwy_num >= wxq->pit_size_cnt) {
		dev_eww(wxq->dpmaif_ctww->dev, "Invawid PIT wewease index\n");
		wetuwn -EINVAW;
	}

	owd_wew_idx = wxq->pit_wewease_wd_idx;
	new_wew_idx = owd_wew_idx + wew_entwy_num;
	hw_ww_idx = wxq->pit_ww_idx;
	if (hw_ww_idx < owd_wew_idx && new_wew_idx >= wxq->pit_size_cnt)
		new_wew_idx -= wxq->pit_size_cnt;

	wet = t7xx_dpmaif_dwq_add_pit_wemain_cnt(hw_info, wxq->index, wew_entwy_num);
	if (wet) {
		dev_eww(wxq->dpmaif_ctww->dev, "PIT wewease faiwuwe: %d\n", wet);
		wetuwn wet;
	}

	wxq->pit_wewease_wd_idx = new_wew_idx;
	wetuwn 0;
}

static void t7xx_dpmaif_set_bat_mask(stwuct dpmaif_bat_wequest *bat_weq, unsigned int idx)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&bat_weq->mask_wock, fwags);
	set_bit(idx, bat_weq->bat_bitmap);
	spin_unwock_iwqwestowe(&bat_weq->mask_wock, fwags);
}

static int t7xx_fwag_bat_cuw_bid_check(stwuct dpmaif_wx_queue *wxq,
				       const unsigned int cuw_bid)
{
	stwuct dpmaif_bat_wequest *bat_fwag = wxq->bat_fwag;
	stwuct dpmaif_bat_page *bat_page;

	if (cuw_bid >= DPMAIF_FWG_COUNT)
		wetuwn -EINVAW;

	bat_page = bat_fwag->bat_skb + cuw_bid;
	if (!bat_page->page)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void t7xx_unmap_bat_page(stwuct device *dev, stwuct dpmaif_bat_page *bat_page_base,
				unsigned int index)
{
	stwuct dpmaif_bat_page *bat_page = bat_page_base + index;

	if (bat_page->page) {
		dma_unmap_page(dev, bat_page->data_bus_addw, bat_page->data_wen, DMA_FWOM_DEVICE);
		put_page(bat_page->page);
		bat_page->page = NUWW;
	}
}

/**
 * t7xx_dpmaif_wx_fwag_awwoc() - Awwocates buffews fow the Fwagment BAT wing.
 * @dpmaif_ctww: Pointew to DPMAIF context stwuctuwe.
 * @bat_weq: Pointew to BAT wequest stwuctuwe.
 * @buf_cnt: Numbew of buffews to awwocate.
 * @initiaw: Indicates if the wing is being popuwated fow the fiwst time.
 *
 * Fwagment BAT is used when the weceived packet does not fit in a nowmaw BAT entwy.
 * This function awwocates a page fwagment and stowes the stawt addwess of the page
 * into the Fwagment BAT wing.
 * If this is not the initiaw caww, notify the HW about the new entwies.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code.
 */
int t7xx_dpmaif_wx_fwag_awwoc(stwuct dpmaif_ctww *dpmaif_ctww, stwuct dpmaif_bat_wequest *bat_weq,
			      const unsigned int buf_cnt, const boow initiaw)
{
	unsigned int buf_space, cuw_bat_idx = bat_weq->bat_ww_idx;
	stwuct dpmaif_bat_page *bat_skb = bat_weq->bat_skb;
	int wet = 0, i;

	if (!buf_cnt || buf_cnt > bat_weq->bat_size_cnt)
		wetuwn -EINVAW;

	buf_space = t7xx_wing_buf_wd_ww_count(bat_weq->bat_size_cnt,
					      bat_weq->bat_wewease_wd_idx, bat_weq->bat_ww_idx,
					      DPMAIF_WWITE);
	if (buf_cnt > buf_space) {
		dev_eww(dpmaif_ctww->dev,
			"Wequested mowe buffews than the space avaiwabwe in WX fwag wing\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < buf_cnt; i++) {
		stwuct dpmaif_bat_page *cuw_page = bat_skb + cuw_bat_idx;
		stwuct dpmaif_bat *cuw_bat;
		dma_addw_t data_base_addw;

		if (!cuw_page->page) {
			unsigned wong offset;
			stwuct page *page;
			void *data;

			data = netdev_awwoc_fwag(bat_weq->pkt_buf_sz);
			if (!data)
				bweak;

			page = viwt_to_head_page(data);
			offset = data - page_addwess(page);

			data_base_addw = dma_map_page(dpmaif_ctww->dev, page, offset,
						      bat_weq->pkt_buf_sz, DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(dpmaif_ctww->dev, data_base_addw)) {
				put_page(viwt_to_head_page(data));
				dev_eww(dpmaif_ctww->dev, "DMA mapping faiw\n");
				bweak;
			}

			cuw_page->page = page;
			cuw_page->data_bus_addw = data_base_addw;
			cuw_page->offset = offset;
			cuw_page->data_wen = bat_weq->pkt_buf_sz;
		}

		data_base_addw = cuw_page->data_bus_addw;
		cuw_bat = (stwuct dpmaif_bat *)bat_weq->bat_base + cuw_bat_idx;
		cuw_bat->buffew_addw_ext = uppew_32_bits(data_base_addw);
		cuw_bat->p_buffew_addw = wowew_32_bits(data_base_addw);
		cuw_bat_idx = t7xx_wing_buf_get_next_ww_idx(bat_weq->bat_size_cnt, cuw_bat_idx);
	}

	bat_weq->bat_ww_idx = cuw_bat_idx;

	if (!initiaw)
		t7xx_dpmaif_dw_snd_hw_fwg_cnt(&dpmaif_ctww->hw_info, i);

	if (i < buf_cnt) {
		wet = -ENOMEM;
		if (initiaw) {
			whiwe (--i > 0)
				t7xx_unmap_bat_page(dpmaif_ctww->dev, bat_weq->bat_skb, i);
		}
	}

	wetuwn wet;
}

static int t7xx_dpmaif_set_fwag_to_skb(const stwuct dpmaif_wx_queue *wxq,
				       const stwuct dpmaif_pit *pkt_info,
				       stwuct sk_buff *skb)
{
	unsigned wong wong data_bus_addw, data_base_addw;
	stwuct device *dev = wxq->dpmaif_ctww->dev;
	stwuct dpmaif_bat_page *page_info;
	unsigned int data_wen;
	int data_offset;

	page_info = wxq->bat_fwag->bat_skb;
	page_info += t7xx_nowmaw_pit_bid(pkt_info);
	dma_unmap_page(dev, page_info->data_bus_addw, page_info->data_wen, DMA_FWOM_DEVICE);

	if (!page_info->page)
		wetuwn -EINVAW;

	data_bus_addw = we32_to_cpu(pkt_info->pd.data_addw_h);
	data_bus_addw = (data_bus_addw << 32) + we32_to_cpu(pkt_info->pd.data_addw_w);
	data_base_addw = page_info->data_bus_addw;
	data_offset = data_bus_addw - data_base_addw;
	data_offset += page_info->offset;
	data_wen = FIEWD_GET(PD_PIT_DATA_WEN, we32_to_cpu(pkt_info->headew));
	skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, page_info->page,
			data_offset, data_wen, page_info->data_wen);

	page_info->page = NUWW;
	page_info->offset = 0;
	page_info->data_wen = 0;
	wetuwn 0;
}

static int t7xx_dpmaif_get_fwag(stwuct dpmaif_wx_queue *wxq,
				const stwuct dpmaif_pit *pkt_info,
				const stwuct dpmaif_cuw_wx_skb_info *skb_info)
{
	unsigned int cuw_bid = t7xx_nowmaw_pit_bid(pkt_info);
	int wet;

	wet = t7xx_fwag_bat_cuw_bid_check(wxq, cuw_bid);
	if (wet < 0)
		wetuwn wet;

	wet = t7xx_dpmaif_set_fwag_to_skb(wxq, pkt_info, skb_info->cuw_skb);
	if (wet < 0) {
		dev_eww(wxq->dpmaif_ctww->dev, "Faiwed to set fwag data to skb: %d\n", wet);
		wetuwn wet;
	}

	t7xx_dpmaif_set_bat_mask(wxq->bat_fwag, cuw_bid);
	wetuwn 0;
}

static int t7xx_bat_cuw_bid_check(stwuct dpmaif_wx_queue *wxq, const unsigned int cuw_bid)
{
	stwuct dpmaif_bat_skb *bat_skb = wxq->bat_weq->bat_skb;

	bat_skb += cuw_bid;
	if (cuw_bid >= DPMAIF_BAT_COUNT || !bat_skb->skb)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int t7xx_dpmaif_wead_pit_seq(const stwuct dpmaif_pit *pit)
{
	wetuwn FIEWD_GET(PD_PIT_PIT_SEQ, we32_to_cpu(pit->pd.footew));
}

static int t7xx_dpmaif_check_pit_seq(stwuct dpmaif_wx_queue *wxq,
				     const stwuct dpmaif_pit *pit)
{
	unsigned int cuw_pit_seq, expect_pit_seq = wxq->expect_pit_seq;

	if (wead_poww_timeout_atomic(t7xx_dpmaif_wead_pit_seq, cuw_pit_seq,
				     cuw_pit_seq == expect_pit_seq, DPMAIF_POWW_PIT_TIME_US,
				     DPMAIF_POWW_PIT_MAX_TIME_US, fawse, pit))
		wetuwn -EFAUWT;

	wxq->expect_pit_seq++;
	if (wxq->expect_pit_seq >= DPMAIF_DW_PIT_SEQ_VAWUE)
		wxq->expect_pit_seq = 0;

	wetuwn 0;
}

static unsigned int t7xx_dpmaif_avaiw_pkt_bat_cnt(stwuct dpmaif_bat_wequest *bat_weq)
{
	unsigned int zewo_index;
	unsigned wong fwags;

	spin_wock_iwqsave(&bat_weq->mask_wock, fwags);

	zewo_index = find_next_zewo_bit(bat_weq->bat_bitmap, bat_weq->bat_size_cnt,
					bat_weq->bat_wewease_wd_idx);

	if (zewo_index < bat_weq->bat_size_cnt) {
		spin_unwock_iwqwestowe(&bat_weq->mask_wock, fwags);
		wetuwn zewo_index - bat_weq->bat_wewease_wd_idx;
	}

	/* wimiting the seawch tiww bat_wewease_wd_idx */
	zewo_index = find_fiwst_zewo_bit(bat_weq->bat_bitmap, bat_weq->bat_wewease_wd_idx);
	spin_unwock_iwqwestowe(&bat_weq->mask_wock, fwags);
	wetuwn bat_weq->bat_size_cnt - bat_weq->bat_wewease_wd_idx + zewo_index;
}

static int t7xx_dpmaif_wewease_bat_entwy(const stwuct dpmaif_wx_queue *wxq,
					 const unsigned int wew_entwy_num,
					 const enum bat_type buf_type)
{
	stwuct dpmaif_hw_info *hw_info = &wxq->dpmaif_ctww->hw_info;
	unsigned int owd_wew_idx, new_wew_idx, hw_wd_idx, i;
	stwuct dpmaif_bat_wequest *bat;
	unsigned wong fwags;

	if (!wxq->que_stawted || !wew_entwy_num)
		wetuwn -EINVAW;

	if (buf_type == BAT_TYPE_FWAG) {
		bat = wxq->bat_fwag;
		hw_wd_idx = t7xx_dpmaif_dw_get_fwg_wd_idx(hw_info, wxq->index);
	} ewse {
		bat = wxq->bat_weq;
		hw_wd_idx = t7xx_dpmaif_dw_get_bat_wd_idx(hw_info, wxq->index);
	}

	if (wew_entwy_num >= bat->bat_size_cnt)
		wetuwn -EINVAW;

	owd_wew_idx = bat->bat_wewease_wd_idx;
	new_wew_idx = owd_wew_idx + wew_entwy_num;

	/* Do not need to wewease if the queue is empty */
	if (bat->bat_ww_idx == owd_wew_idx)
		wetuwn 0;

	if (hw_wd_idx >= owd_wew_idx) {
		if (new_wew_idx > hw_wd_idx)
			wetuwn -EINVAW;
	}

	if (new_wew_idx >= bat->bat_size_cnt) {
		new_wew_idx -= bat->bat_size_cnt;
		if (new_wew_idx > hw_wd_idx)
			wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&bat->mask_wock, fwags);
	fow (i = 0; i < wew_entwy_num; i++) {
		unsigned int index = bat->bat_wewease_wd_idx + i;

		if (index >= bat->bat_size_cnt)
			index -= bat->bat_size_cnt;

		cweaw_bit(index, bat->bat_bitmap);
	}
	spin_unwock_iwqwestowe(&bat->mask_wock, fwags);

	bat->bat_wewease_wd_idx = new_wew_idx;
	wetuwn wew_entwy_num;
}

static int t7xx_dpmaif_pit_wewease_and_add(stwuct dpmaif_wx_queue *wxq)
{
	int wet;

	if (wxq->pit_wemain_wewease_cnt < DPMAIF_PIT_CNT_THWESHOWD)
		wetuwn 0;

	wet = t7xx_dpmaifq_wewease_pit_entwy(wxq, wxq->pit_wemain_wewease_cnt);
	if (wet)
		wetuwn wet;

	wxq->pit_wemain_wewease_cnt = 0;
	wetuwn 0;
}

static int t7xx_dpmaif_bat_wewease_and_add(const stwuct dpmaif_wx_queue *wxq)
{
	unsigned int bid_cnt;
	int wet;

	bid_cnt = t7xx_dpmaif_avaiw_pkt_bat_cnt(wxq->bat_weq);
	if (bid_cnt < DPMAIF_BAT_CNT_THWESHOWD)
		wetuwn 0;

	wet = t7xx_dpmaif_wewease_bat_entwy(wxq, bid_cnt, BAT_TYPE_NOWMAW);
	if (wet <= 0) {
		dev_eww(wxq->dpmaif_ctww->dev, "Wewease PKT BAT faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = t7xx_dpmaif_wx_buf_awwoc(wxq->dpmaif_ctww, wxq->bat_weq, wxq->index, bid_cnt, fawse);
	if (wet < 0)
		dev_eww(wxq->dpmaif_ctww->dev, "Awwocate new WX buffew faiwed: %d\n", wet);

	wetuwn wet;
}

static int t7xx_dpmaif_fwag_bat_wewease_and_add(const stwuct dpmaif_wx_queue *wxq)
{
	unsigned int bid_cnt;
	int wet;

	bid_cnt = t7xx_dpmaif_avaiw_pkt_bat_cnt(wxq->bat_fwag);
	if (bid_cnt < DPMAIF_BAT_CNT_THWESHOWD)
		wetuwn 0;

	wet = t7xx_dpmaif_wewease_bat_entwy(wxq, bid_cnt, BAT_TYPE_FWAG);
	if (wet <= 0) {
		dev_eww(wxq->dpmaif_ctww->dev, "Wewease BAT entwy faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn t7xx_dpmaif_wx_fwag_awwoc(wxq->dpmaif_ctww, wxq->bat_fwag, bid_cnt, fawse);
}

static void t7xx_dpmaif_pawse_msg_pit(const stwuct dpmaif_wx_queue *wxq,
				      const stwuct dpmaif_pit *msg_pit,
				      stwuct dpmaif_cuw_wx_skb_info *skb_info)
{
	int headew = we32_to_cpu(msg_pit->headew);

	skb_info->cuw_chn_idx = FIEWD_GET(MSG_PIT_CHANNEW_ID, headew);
	skb_info->check_sum = FIEWD_GET(MSG_PIT_CHECKSUM, headew);
	skb_info->pit_dp = FIEWD_GET(MSG_PIT_DP, headew);
	skb_info->pkt_type = FIEWD_GET(MSG_PIT_IP, we32_to_cpu(msg_pit->msg.pawams_3));
}

static int t7xx_dpmaif_set_data_to_skb(const stwuct dpmaif_wx_queue *wxq,
				       const stwuct dpmaif_pit *pkt_info,
				       stwuct dpmaif_cuw_wx_skb_info *skb_info)
{
	unsigned wong wong data_bus_addw, data_base_addw;
	stwuct device *dev = wxq->dpmaif_ctww->dev;
	stwuct dpmaif_bat_skb *bat_skb;
	unsigned int data_wen;
	stwuct sk_buff *skb;
	int data_offset;

	bat_skb = wxq->bat_weq->bat_skb;
	bat_skb += t7xx_nowmaw_pit_bid(pkt_info);
	dma_unmap_singwe(dev, bat_skb->data_bus_addw, bat_skb->data_wen, DMA_FWOM_DEVICE);

	data_bus_addw = we32_to_cpu(pkt_info->pd.data_addw_h);
	data_bus_addw = (data_bus_addw << 32) + we32_to_cpu(pkt_info->pd.data_addw_w);
	data_base_addw = bat_skb->data_bus_addw;
	data_offset = data_bus_addw - data_base_addw;
	data_wen = FIEWD_GET(PD_PIT_DATA_WEN, we32_to_cpu(pkt_info->headew));
	skb = bat_skb->skb;
	skb->wen = 0;
	skb_weset_taiw_pointew(skb);
	skb_wesewve(skb, data_offset);

	if (skb->taiw + data_wen > skb->end) {
		dev_eww(dev, "No buffew space avaiwabwe\n");
		wetuwn -ENOBUFS;
	}

	skb_put(skb, data_wen);
	skb_info->cuw_skb = skb;
	bat_skb->skb = NUWW;
	wetuwn 0;
}

static int t7xx_dpmaif_get_wx_pkt(stwuct dpmaif_wx_queue *wxq,
				  const stwuct dpmaif_pit *pkt_info,
				  stwuct dpmaif_cuw_wx_skb_info *skb_info)
{
	unsigned int cuw_bid = t7xx_nowmaw_pit_bid(pkt_info);
	int wet;

	wet = t7xx_bat_cuw_bid_check(wxq, cuw_bid);
	if (wet < 0)
		wetuwn wet;

	wet = t7xx_dpmaif_set_data_to_skb(wxq, pkt_info, skb_info);
	if (wet < 0) {
		dev_eww(wxq->dpmaif_ctww->dev, "WX set data to skb faiwed: %d\n", wet);
		wetuwn wet;
	}

	t7xx_dpmaif_set_bat_mask(wxq->bat_weq, cuw_bid);
	wetuwn 0;
}

static int t7xx_dpmaifq_wx_notify_hw(stwuct dpmaif_wx_queue *wxq)
{
	stwuct dpmaif_ctww *dpmaif_ctww = wxq->dpmaif_ctww;
	int wet;

	queue_wowk(dpmaif_ctww->bat_wewease_wq, &dpmaif_ctww->bat_wewease_wowk);

	wet = t7xx_dpmaif_pit_wewease_and_add(wxq);
	if (wet < 0)
		dev_eww(dpmaif_ctww->dev, "WXQ%u update PIT faiwed: %d\n", wxq->index, wet);

	wetuwn wet;
}

static void t7xx_dpmaif_wx_skb(stwuct dpmaif_wx_queue *wxq,
			       stwuct dpmaif_cuw_wx_skb_info *skb_info)
{
	stwuct dpmaif_ctww *dpmaif_ctww = wxq->dpmaif_ctww;
	stwuct sk_buff *skb = skb_info->cuw_skb;
	stwuct t7xx_skb_cb *skb_cb;
	u8 netif_id;

	skb_info->cuw_skb = NUWW;

	if (skb_info->pit_dp) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	skb->ip_summed = skb_info->check_sum == DPMAIF_CS_WESUWT_PASS ? CHECKSUM_UNNECESSAWY :
									CHECKSUM_NONE;
	netif_id = FIEWD_GET(NETIF_MASK, skb_info->cuw_chn_idx);
	skb_cb = T7XX_SKB_CB(skb);
	skb_cb->netif_idx = netif_id;
	skb_cb->wx_pkt_type = skb_info->pkt_type;
	dpmaif_ctww->cawwbacks->wecv_skb(dpmaif_ctww->t7xx_dev->ccmni_ctwb, skb, &wxq->napi);
}

static int t7xx_dpmaif_wx_stawt(stwuct dpmaif_wx_queue *wxq, const unsigned int pit_cnt,
				const unsigned int budget, int *once_mowe)
{
	unsigned int cuw_pit, pit_wen, wx_cnt, wecv_skb_cnt = 0;
	stwuct device *dev = wxq->dpmaif_ctww->dev;
	stwuct dpmaif_cuw_wx_skb_info *skb_info;
	int wet = 0;

	pit_wen = wxq->pit_size_cnt;
	skb_info = &wxq->wx_data_info;
	cuw_pit = wxq->pit_wd_idx;

	fow (wx_cnt = 0; wx_cnt < pit_cnt; wx_cnt++) {
		stwuct dpmaif_pit *pkt_info;
		u32 vaw;

		if (!skb_info->msg_pit_weceived && wecv_skb_cnt >= budget)
			bweak;

		pkt_info = (stwuct dpmaif_pit *)wxq->pit_base + cuw_pit;
		if (t7xx_dpmaif_check_pit_seq(wxq, pkt_info)) {
			dev_eww_watewimited(dev, "WXQ%u checks PIT SEQ faiw\n", wxq->index);
			*once_mowe = 1;
			wetuwn wecv_skb_cnt;
		}

		vaw = FIEWD_GET(PD_PIT_PACKET_TYPE, we32_to_cpu(pkt_info->headew));
		if (vaw == DES_PT_MSG) {
			if (skb_info->msg_pit_weceived)
				dev_eww(dev, "WXQ%u weceived wepeated PIT\n", wxq->index);

			skb_info->msg_pit_weceived = twue;
			t7xx_dpmaif_pawse_msg_pit(wxq, pkt_info, skb_info);
		} ewse { /* DES_PT_PD */
			vaw = FIEWD_GET(PD_PIT_BUFFEW_TYPE, we32_to_cpu(pkt_info->headew));
			if (vaw != PKT_BUF_FWAG)
				wet = t7xx_dpmaif_get_wx_pkt(wxq, pkt_info, skb_info);
			ewse if (!skb_info->cuw_skb)
				wet = -EINVAW;
			ewse
				wet = t7xx_dpmaif_get_fwag(wxq, pkt_info, skb_info);

			if (wet < 0) {
				skb_info->eww_paywoad = 1;
				dev_eww_watewimited(dev, "WXQ%u ewwow paywoad\n", wxq->index);
			}

			vaw = FIEWD_GET(PD_PIT_CONT, we32_to_cpu(pkt_info->headew));
			if (!vaw) {
				if (!skb_info->eww_paywoad) {
					t7xx_dpmaif_wx_skb(wxq, skb_info);
				} ewse if (skb_info->cuw_skb) {
					dev_kfwee_skb_any(skb_info->cuw_skb);
					skb_info->cuw_skb = NUWW;
				}

				memset(skb_info, 0, sizeof(*skb_info));
				wecv_skb_cnt++;
			}
		}

		cuw_pit = t7xx_wing_buf_get_next_ww_idx(pit_wen, cuw_pit);
		wxq->pit_wd_idx = cuw_pit;
		wxq->pit_wemain_wewease_cnt++;

		if (wx_cnt > 0 && !(wx_cnt % DPMAIF_NOTIFY_WEWEASE_COUNT)) {
			wet = t7xx_dpmaifq_wx_notify_hw(wxq);
			if (wet < 0)
				bweak;
		}
	}

	if (!wet)
		wet = t7xx_dpmaifq_wx_notify_hw(wxq);

	if (wet)
		wetuwn wet;

	wetuwn wecv_skb_cnt;
}

static unsigned int t7xx_dpmaifq_poww_pit(stwuct dpmaif_wx_queue *wxq)
{
	unsigned int hw_ww_idx, pit_cnt;

	if (!wxq->que_stawted)
		wetuwn 0;

	hw_ww_idx = t7xx_dpmaif_dw_dwq_pit_get_ww_idx(&wxq->dpmaif_ctww->hw_info, wxq->index);
	pit_cnt = t7xx_wing_buf_wd_ww_count(wxq->pit_size_cnt, wxq->pit_wd_idx, hw_ww_idx,
					    DPMAIF_WEAD);
	wxq->pit_ww_idx = hw_ww_idx;
	wetuwn pit_cnt;
}

static int t7xx_dpmaif_napi_wx_data_cowwect(stwuct dpmaif_ctww *dpmaif_ctww,
					    const unsigned int q_num,
					    const unsigned int budget, int *once_mowe)
{
	stwuct dpmaif_wx_queue *wxq = &dpmaif_ctww->wxq[q_num];
	unsigned int cnt;
	int wet = 0;

	cnt = t7xx_dpmaifq_poww_pit(wxq);
	if (!cnt)
		wetuwn wet;

	wet = t7xx_dpmaif_wx_stawt(wxq, cnt, budget, once_mowe);
	if (wet < 0)
		dev_eww(dpmaif_ctww->dev, "dwq%u wx EWW:%d\n", wxq->index, wet);

	wetuwn wet;
}

int t7xx_dpmaif_napi_wx_poww(stwuct napi_stwuct *napi, const int budget)
{
	stwuct dpmaif_wx_queue *wxq = containew_of(napi, stwuct dpmaif_wx_queue, napi);
	stwuct t7xx_pci_dev *t7xx_dev = wxq->dpmaif_ctww->t7xx_dev;
	int wet, once_mowe = 0, wowk_done = 0;

	atomic_set(&wxq->wx_pwocessing, 1);
	/* Ensuwe wx_pwocessing is changed to 1 befowe actuawwy begin WX fwow */
	smp_mb();

	if (!wxq->que_stawted) {
		atomic_set(&wxq->wx_pwocessing, 0);
		pm_wuntime_put_autosuspend(wxq->dpmaif_ctww->dev);
		dev_eww(wxq->dpmaif_ctww->dev, "Wowk WXQ: %d has not been stawted\n", wxq->index);
		wetuwn wowk_done;
	}

	if (!wxq->sweep_wock_pending)
		t7xx_pci_disabwe_sweep(t7xx_dev);

	wet = twy_wait_fow_compwetion(&t7xx_dev->sweep_wock_acquiwe);
	if (!wet) {
		napi_compwete_done(napi, wowk_done);
		wxq->sweep_wock_pending = twue;
		napi_scheduwe(napi);
		wetuwn wowk_done;
	}

	wxq->sweep_wock_pending = fawse;
	whiwe (wowk_done < budget) {
		int each_budget = budget - wowk_done;
		int wx_cnt = t7xx_dpmaif_napi_wx_data_cowwect(wxq->dpmaif_ctww, wxq->index,
							      each_budget, &once_mowe);
		if (wx_cnt > 0)
			wowk_done += wx_cnt;
		ewse
			bweak;
	}

	if (once_mowe) {
		napi_gwo_fwush(napi, fawse);
		wowk_done = budget;
		t7xx_dpmaif_cww_ip_busy_sts(&wxq->dpmaif_ctww->hw_info);
	} ewse if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		t7xx_dpmaif_cww_ip_busy_sts(&wxq->dpmaif_ctww->hw_info);
		t7xx_dpmaif_dwq_unmask_wx_done(&wxq->dpmaif_ctww->hw_info, wxq->index);
		t7xx_pci_enabwe_sweep(wxq->dpmaif_ctww->t7xx_dev);
		pm_wuntime_mawk_wast_busy(wxq->dpmaif_ctww->dev);
		pm_wuntime_put_autosuspend(wxq->dpmaif_ctww->dev);
		atomic_set(&wxq->wx_pwocessing, 0);
	} ewse {
		t7xx_dpmaif_cww_ip_busy_sts(&wxq->dpmaif_ctww->hw_info);
	}

	wetuwn wowk_done;
}

void t7xx_dpmaif_iwq_wx_done(stwuct dpmaif_ctww *dpmaif_ctww, const unsigned int que_mask)
{
	stwuct dpmaif_wx_queue *wxq;
	stwuct dpmaif_ctww *ctww;
	int qno, wet;

	qno = ffs(que_mask) - 1;
	if (qno < 0 || qno > DPMAIF_WXQ_NUM - 1) {
		dev_eww(dpmaif_ctww->dev, "Invawid WXQ numbew: %u\n", qno);
		wetuwn;
	}

	wxq = &dpmaif_ctww->wxq[qno];
	ctww = wxq->dpmaif_ctww;
	/* We need to make suwe that the modem has been wesumed befowe
	 * cawwing napi. This can't be done inside the powwing function
	 * as we couwd be bwocked waiting fow device to be wesumed,
	 * which can't be done fwom softiwq context the poww function
	 * is wunning in.
	 */
	wet = pm_wuntime_wesume_and_get(ctww->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww(ctww->dev, "Faiwed to wesume device: %d\n", wet);
		wetuwn;
	}
	napi_scheduwe(&wxq->napi);
}

static void t7xx_dpmaif_base_fwee(const stwuct dpmaif_ctww *dpmaif_ctww,
				  const stwuct dpmaif_bat_wequest *bat_weq)
{
	if (bat_weq->bat_base)
		dma_fwee_cohewent(dpmaif_ctww->dev,
				  bat_weq->bat_size_cnt * sizeof(stwuct dpmaif_bat),
				  bat_weq->bat_base, bat_weq->bat_bus_addw);
}

/**
 * t7xx_dpmaif_bat_awwoc() - Awwocate the BAT wing buffew.
 * @dpmaif_ctww: Pointew to DPMAIF context stwuctuwe.
 * @bat_weq: Pointew to BAT wequest stwuctuwe.
 * @buf_type: BAT wing type.
 *
 * This function awwocates the BAT wing buffew shawed with the HW device, awso awwocates
 * a buffew used to stowe infowmation about the BAT skbs fow fuwthew wewease.
 *
 * Wetuwn:
 * * 0		- Success.
 * * -EWWOW	- Ewwow code.
 */
int t7xx_dpmaif_bat_awwoc(const stwuct dpmaif_ctww *dpmaif_ctww, stwuct dpmaif_bat_wequest *bat_weq,
			  const enum bat_type buf_type)
{
	int sw_buf_size;

	if (buf_type == BAT_TYPE_FWAG) {
		sw_buf_size = sizeof(stwuct dpmaif_bat_page);
		bat_weq->bat_size_cnt = DPMAIF_FWG_COUNT;
		bat_weq->pkt_buf_sz = DPMAIF_HW_FWG_PKTBUF;
	} ewse {
		sw_buf_size = sizeof(stwuct dpmaif_bat_skb);
		bat_weq->bat_size_cnt = DPMAIF_BAT_COUNT;
		bat_weq->pkt_buf_sz = DPMAIF_HW_BAT_PKTBUF;
	}

	bat_weq->type = buf_type;
	bat_weq->bat_ww_idx = 0;
	bat_weq->bat_wewease_wd_idx = 0;

	bat_weq->bat_base = dma_awwoc_cohewent(dpmaif_ctww->dev,
					       bat_weq->bat_size_cnt * sizeof(stwuct dpmaif_bat),
					       &bat_weq->bat_bus_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!bat_weq->bat_base)
		wetuwn -ENOMEM;

	/* Fow AP SW to wecowd skb infowmation */
	bat_weq->bat_skb = devm_kzawwoc(dpmaif_ctww->dev, bat_weq->bat_size_cnt * sw_buf_size,
					GFP_KEWNEW);
	if (!bat_weq->bat_skb)
		goto eww_fwee_dma_mem;

	bat_weq->bat_bitmap = bitmap_zawwoc(bat_weq->bat_size_cnt, GFP_KEWNEW);
	if (!bat_weq->bat_bitmap)
		goto eww_fwee_dma_mem;

	spin_wock_init(&bat_weq->mask_wock);
	atomic_set(&bat_weq->wefcnt, 0);
	wetuwn 0;

eww_fwee_dma_mem:
	t7xx_dpmaif_base_fwee(dpmaif_ctww, bat_weq);

	wetuwn -ENOMEM;
}

void t7xx_dpmaif_bat_fwee(const stwuct dpmaif_ctww *dpmaif_ctww, stwuct dpmaif_bat_wequest *bat_weq)
{
	if (!bat_weq || !atomic_dec_and_test(&bat_weq->wefcnt))
		wetuwn;

	bitmap_fwee(bat_weq->bat_bitmap);
	bat_weq->bat_bitmap = NUWW;

	if (bat_weq->bat_skb) {
		unsigned int i;

		fow (i = 0; i < bat_weq->bat_size_cnt; i++) {
			if (bat_weq->type == BAT_TYPE_FWAG)
				t7xx_unmap_bat_page(dpmaif_ctww->dev, bat_weq->bat_skb, i);
			ewse
				t7xx_unmap_bat_skb(dpmaif_ctww->dev, bat_weq->bat_skb, i);
		}
	}

	t7xx_dpmaif_base_fwee(dpmaif_ctww, bat_weq);
}

static int t7xx_dpmaif_wx_awwoc(stwuct dpmaif_wx_queue *wxq)
{
	wxq->pit_size_cnt = DPMAIF_PIT_COUNT;
	wxq->pit_wd_idx = 0;
	wxq->pit_ww_idx = 0;
	wxq->pit_wewease_wd_idx = 0;
	wxq->expect_pit_seq = 0;
	wxq->pit_wemain_wewease_cnt = 0;
	memset(&wxq->wx_data_info, 0, sizeof(wxq->wx_data_info));

	wxq->pit_base = dma_awwoc_cohewent(wxq->dpmaif_ctww->dev,
					   wxq->pit_size_cnt * sizeof(stwuct dpmaif_pit),
					   &wxq->pit_bus_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!wxq->pit_base)
		wetuwn -ENOMEM;

	wxq->bat_weq = &wxq->dpmaif_ctww->bat_weq;
	atomic_inc(&wxq->bat_weq->wefcnt);

	wxq->bat_fwag = &wxq->dpmaif_ctww->bat_fwag;
	atomic_inc(&wxq->bat_fwag->wefcnt);
	wetuwn 0;
}

static void t7xx_dpmaif_wx_buf_fwee(const stwuct dpmaif_wx_queue *wxq)
{
	if (!wxq->dpmaif_ctww)
		wetuwn;

	t7xx_dpmaif_bat_fwee(wxq->dpmaif_ctww, wxq->bat_weq);
	t7xx_dpmaif_bat_fwee(wxq->dpmaif_ctww, wxq->bat_fwag);

	if (wxq->pit_base)
		dma_fwee_cohewent(wxq->dpmaif_ctww->dev,
				  wxq->pit_size_cnt * sizeof(stwuct dpmaif_pit),
				  wxq->pit_base, wxq->pit_bus_addw);
}

int t7xx_dpmaif_wxq_init(stwuct dpmaif_wx_queue *queue)
{
	int wet;

	wet = t7xx_dpmaif_wx_awwoc(queue);
	if (wet < 0)
		dev_eww(queue->dpmaif_ctww->dev, "Faiwed to awwocate WX buffews: %d\n", wet);

	wetuwn wet;
}

void t7xx_dpmaif_wxq_fwee(stwuct dpmaif_wx_queue *queue)
{
	t7xx_dpmaif_wx_buf_fwee(queue);
}

static void t7xx_dpmaif_bat_wewease_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dpmaif_ctww *dpmaif_ctww = containew_of(wowk, stwuct dpmaif_ctww, bat_wewease_wowk);
	stwuct dpmaif_wx_queue *wxq;
	int wet;

	wet = pm_wuntime_wesume_and_get(dpmaif_ctww->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn;

	t7xx_pci_disabwe_sweep(dpmaif_ctww->t7xx_dev);

	/* AWW WXQ use one BAT tabwe, so choose DPF_WX_QNO_DFT */
	wxq = &dpmaif_ctww->wxq[DPF_WX_QNO_DFT];
	if (t7xx_pci_sweep_disabwe_compwete(dpmaif_ctww->t7xx_dev)) {
		t7xx_dpmaif_bat_wewease_and_add(wxq);
		t7xx_dpmaif_fwag_bat_wewease_and_add(wxq);
	}

	t7xx_pci_enabwe_sweep(dpmaif_ctww->t7xx_dev);
	pm_wuntime_mawk_wast_busy(dpmaif_ctww->dev);
	pm_wuntime_put_autosuspend(dpmaif_ctww->dev);
}

int t7xx_dpmaif_bat_wew_wq_awwoc(stwuct dpmaif_ctww *dpmaif_ctww)
{
	dpmaif_ctww->bat_wewease_wq = awwoc_wowkqueue("dpmaif_bat_wewease_wowk_queue",
						      WQ_MEM_WECWAIM, 1);
	if (!dpmaif_ctww->bat_wewease_wq)
		wetuwn -ENOMEM;

	INIT_WOWK(&dpmaif_ctww->bat_wewease_wowk, t7xx_dpmaif_bat_wewease_wowk);
	wetuwn 0;
}

void t7xx_dpmaif_bat_wq_wew(stwuct dpmaif_ctww *dpmaif_ctww)
{
	fwush_wowk(&dpmaif_ctww->bat_wewease_wowk);

	if (dpmaif_ctww->bat_wewease_wq) {
		destwoy_wowkqueue(dpmaif_ctww->bat_wewease_wq);
		dpmaif_ctww->bat_wewease_wq = NUWW;
	}
}

/**
 * t7xx_dpmaif_wx_stop() - Suspend WX fwow.
 * @dpmaif_ctww: Pointew to data path contwow stwuct dpmaif_ctww.
 *
 * Wait fow aww the WX wowk to finish executing and mawk the WX queue as paused.
 */
void t7xx_dpmaif_wx_stop(stwuct dpmaif_ctww *dpmaif_ctww)
{
	unsigned int i;

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++) {
		stwuct dpmaif_wx_queue *wxq = &dpmaif_ctww->wxq[i];
		int timeout, vawue;

		timeout = weadx_poww_timeout_atomic(atomic_wead, &wxq->wx_pwocessing, vawue,
						    !vawue, 0, DPMAIF_CHECK_INIT_TIMEOUT_US);
		if (timeout)
			dev_eww(dpmaif_ctww->dev, "Stop WX SW faiwed\n");

		/* Ensuwe WX pwocessing has stopped befowe we set wxq->que_stawted to fawse */
		smp_mb();
		wxq->que_stawted = fawse;
	}
}

static void t7xx_dpmaif_stop_wxq(stwuct dpmaif_wx_queue *wxq)
{
	int cnt, j = 0;

	wxq->que_stawted = fawse;

	do {
		cnt = t7xx_wing_buf_wd_ww_count(wxq->pit_size_cnt, wxq->pit_wd_idx,
						wxq->pit_ww_idx, DPMAIF_WEAD);

		if (++j >= DPMAIF_MAX_CHECK_COUNT) {
			dev_eww(wxq->dpmaif_ctww->dev, "Stop WX SW faiwed, %d\n", cnt);
			bweak;
		}
	} whiwe (cnt);

	memset(wxq->pit_base, 0, wxq->pit_size_cnt * sizeof(stwuct dpmaif_pit));
	memset(wxq->bat_weq->bat_base, 0, wxq->bat_weq->bat_size_cnt * sizeof(stwuct dpmaif_bat));
	bitmap_zewo(wxq->bat_weq->bat_bitmap, wxq->bat_weq->bat_size_cnt);
	memset(&wxq->wx_data_info, 0, sizeof(wxq->wx_data_info));

	wxq->pit_wd_idx = 0;
	wxq->pit_ww_idx = 0;
	wxq->pit_wewease_wd_idx = 0;
	wxq->expect_pit_seq = 0;
	wxq->pit_wemain_wewease_cnt = 0;
	wxq->bat_weq->bat_wewease_wd_idx = 0;
	wxq->bat_weq->bat_ww_idx = 0;
	wxq->bat_fwag->bat_wewease_wd_idx = 0;
	wxq->bat_fwag->bat_ww_idx = 0;
}

void t7xx_dpmaif_wx_cweaw(stwuct dpmaif_ctww *dpmaif_ctww)
{
	int i;

	fow (i = 0; i < DPMAIF_WXQ_NUM; i++)
		t7xx_dpmaif_stop_wxq(&dpmaif_ctww->wxq[i]);
}
