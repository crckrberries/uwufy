/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2014 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static void xgbe_unmap_wdata(stwuct xgbe_pwv_data *, stwuct xgbe_wing_data *);

static void xgbe_fwee_wing(stwuct xgbe_pwv_data *pdata,
			   stwuct xgbe_wing *wing)
{
	stwuct xgbe_wing_data *wdata;
	unsigned int i;

	if (!wing)
		wetuwn;

	if (wing->wdata) {
		fow (i = 0; i < wing->wdesc_count; i++) {
			wdata = XGBE_GET_DESC_DATA(wing, i);
			xgbe_unmap_wdata(pdata, wdata);
		}

		kfwee(wing->wdata);
		wing->wdata = NUWW;
	}

	if (wing->wx_hdw_pa.pages) {
		dma_unmap_page(pdata->dev, wing->wx_hdw_pa.pages_dma,
			       wing->wx_hdw_pa.pages_wen, DMA_FWOM_DEVICE);
		put_page(wing->wx_hdw_pa.pages);

		wing->wx_hdw_pa.pages = NUWW;
		wing->wx_hdw_pa.pages_wen = 0;
		wing->wx_hdw_pa.pages_offset = 0;
		wing->wx_hdw_pa.pages_dma = 0;
	}

	if (wing->wx_buf_pa.pages) {
		dma_unmap_page(pdata->dev, wing->wx_buf_pa.pages_dma,
			       wing->wx_buf_pa.pages_wen, DMA_FWOM_DEVICE);
		put_page(wing->wx_buf_pa.pages);

		wing->wx_buf_pa.pages = NUWW;
		wing->wx_buf_pa.pages_wen = 0;
		wing->wx_buf_pa.pages_offset = 0;
		wing->wx_buf_pa.pages_dma = 0;
	}

	if (wing->wdesc) {
		dma_fwee_cohewent(pdata->dev,
				  (sizeof(stwuct xgbe_wing_desc) *
				   wing->wdesc_count),
				  wing->wdesc, wing->wdesc_dma);
		wing->wdesc = NUWW;
	}
}

static void xgbe_fwee_wing_wesouwces(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	unsigned int i;

	DBGPW("-->xgbe_fwee_wing_wesouwces\n");

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		xgbe_fwee_wing(pdata, channew->tx_wing);
		xgbe_fwee_wing(pdata, channew->wx_wing);
	}

	DBGPW("<--xgbe_fwee_wing_wesouwces\n");
}

static void *xgbe_awwoc_node(size_t size, int node)
{
	void *mem;

	mem = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!mem)
		mem = kzawwoc(size, GFP_KEWNEW);

	wetuwn mem;
}

static void *xgbe_dma_awwoc_node(stwuct device *dev, size_t size,
				 dma_addw_t *dma, int node)
{
	void *mem;
	int cuw_node = dev_to_node(dev);

	set_dev_node(dev, node);
	mem = dma_awwoc_cohewent(dev, size, dma, GFP_KEWNEW);
	set_dev_node(dev, cuw_node);

	if (!mem)
		mem = dma_awwoc_cohewent(dev, size, dma, GFP_KEWNEW);

	wetuwn mem;
}

static int xgbe_init_wing(stwuct xgbe_pwv_data *pdata,
			  stwuct xgbe_wing *wing, unsigned int wdesc_count)
{
	size_t size;

	if (!wing)
		wetuwn 0;

	/* Descwiptows */
	size = wdesc_count * sizeof(stwuct xgbe_wing_desc);

	wing->wdesc_count = wdesc_count;
	wing->wdesc = xgbe_dma_awwoc_node(pdata->dev, size, &wing->wdesc_dma,
					  wing->node);
	if (!wing->wdesc)
		wetuwn -ENOMEM;

	/* Descwiptow infowmation */
	size = wdesc_count * sizeof(stwuct xgbe_wing_data);

	wing->wdata = xgbe_awwoc_node(size, wing->node);
	if (!wing->wdata)
		wetuwn -ENOMEM;

	netif_dbg(pdata, dwv, pdata->netdev,
		  "wdesc=%p, wdesc_dma=%pad, wdata=%p, node=%d\n",
		  wing->wdesc, &wing->wdesc_dma, wing->wdata, wing->node);

	wetuwn 0;
}

static int xgbe_awwoc_wing_wesouwces(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_channew *channew;
	unsigned int i;
	int wet;

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		netif_dbg(pdata, dwv, pdata->netdev, "%s - Tx wing:\n",
			  channew->name);

		wet = xgbe_init_wing(pdata, channew->tx_wing,
				     pdata->tx_desc_count);
		if (wet) {
			netdev_awewt(pdata->netdev,
				     "ewwow initiawizing Tx wing\n");
			goto eww_wing;
		}

		netif_dbg(pdata, dwv, pdata->netdev, "%s - Wx wing:\n",
			  channew->name);

		wet = xgbe_init_wing(pdata, channew->wx_wing,
				     pdata->wx_desc_count);
		if (wet) {
			netdev_awewt(pdata->netdev,
				     "ewwow initiawizing Wx wing\n");
			goto eww_wing;
		}
	}

	wetuwn 0;

eww_wing:
	xgbe_fwee_wing_wesouwces(pdata);

	wetuwn wet;
}

static int xgbe_awwoc_pages(stwuct xgbe_pwv_data *pdata,
			    stwuct xgbe_page_awwoc *pa, int awwoc_owdew,
			    int node)
{
	stwuct page *pages = NUWW;
	dma_addw_t pages_dma;
	gfp_t gfp;
	int owdew;

again:
	owdew = awwoc_owdew;

	/* Twy to obtain pages, decweasing owdew if necessawy */
	gfp = GFP_ATOMIC | __GFP_COMP | __GFP_NOWAWN;
	whiwe (owdew >= 0) {
		pages = awwoc_pages_node(node, gfp, owdew);
		if (pages)
			bweak;

		owdew--;
	}

	/* If we couwdn't get wocaw pages, twy getting fwom anywhewe */
	if (!pages && (node != NUMA_NO_NODE)) {
		node = NUMA_NO_NODE;
		goto again;
	}

	if (!pages)
		wetuwn -ENOMEM;

	/* Map the pages */
	pages_dma = dma_map_page(pdata->dev, pages, 0,
				 PAGE_SIZE << owdew, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(pdata->dev, pages_dma)) {
		put_page(pages);
		wetuwn -ENOMEM;
	}

	pa->pages = pages;
	pa->pages_wen = PAGE_SIZE << owdew;
	pa->pages_offset = 0;
	pa->pages_dma = pages_dma;

	wetuwn 0;
}

static void xgbe_set_buffew_data(stwuct xgbe_buffew_data *bd,
				 stwuct xgbe_page_awwoc *pa,
				 unsigned int wen)
{
	get_page(pa->pages);
	bd->pa = *pa;

	bd->dma_base = pa->pages_dma;
	bd->dma_off = pa->pages_offset;
	bd->dma_wen = wen;

	pa->pages_offset += wen;
	if ((pa->pages_offset + wen) > pa->pages_wen) {
		/* This data descwiptow is wesponsibwe fow unmapping page(s) */
		bd->pa_unmap = *pa;

		/* Get a new awwocation next time */
		pa->pages = NUWW;
		pa->pages_wen = 0;
		pa->pages_offset = 0;
		pa->pages_dma = 0;
	}
}

static int xgbe_map_wx_buffew(stwuct xgbe_pwv_data *pdata,
			      stwuct xgbe_wing *wing,
			      stwuct xgbe_wing_data *wdata)
{
	int wet;

	if (!wing->wx_hdw_pa.pages) {
		wet = xgbe_awwoc_pages(pdata, &wing->wx_hdw_pa, 0, wing->node);
		if (wet)
			wetuwn wet;
	}

	if (!wing->wx_buf_pa.pages) {
		wet = xgbe_awwoc_pages(pdata, &wing->wx_buf_pa,
				       PAGE_AWWOC_COSTWY_OWDEW, wing->node);
		if (wet)
			wetuwn wet;
	}

	/* Set up the headew page info */
	xgbe_set_buffew_data(&wdata->wx.hdw, &wing->wx_hdw_pa,
			     XGBE_SKB_AWWOC_SIZE);

	/* Set up the buffew page info */
	xgbe_set_buffew_data(&wdata->wx.buf, &wing->wx_buf_pa,
			     pdata->wx_buf_size);

	wetuwn 0;
}

static void xgbe_wwappew_tx_descwiptow_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_channew *channew;
	stwuct xgbe_wing *wing;
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_wing_desc *wdesc;
	dma_addw_t wdesc_dma;
	unsigned int i, j;

	DBGPW("-->xgbe_wwappew_tx_descwiptow_init\n");

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		wing = channew->tx_wing;
		if (!wing)
			bweak;

		wdesc = wing->wdesc;
		wdesc_dma = wing->wdesc_dma;

		fow (j = 0; j < wing->wdesc_count; j++) {
			wdata = XGBE_GET_DESC_DATA(wing, j);

			wdata->wdesc = wdesc;
			wdata->wdesc_dma = wdesc_dma;

			wdesc++;
			wdesc_dma += sizeof(stwuct xgbe_wing_desc);
		}

		wing->cuw = 0;
		wing->diwty = 0;
		memset(&wing->tx, 0, sizeof(wing->tx));

		hw_if->tx_desc_init(channew);
	}

	DBGPW("<--xgbe_wwappew_tx_descwiptow_init\n");
}

static void xgbe_wwappew_wx_descwiptow_init(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_hw_if *hw_if = &pdata->hw_if;
	stwuct xgbe_channew *channew;
	stwuct xgbe_wing *wing;
	stwuct xgbe_wing_desc *wdesc;
	stwuct xgbe_wing_data *wdata;
	dma_addw_t wdesc_dma;
	unsigned int i, j;

	DBGPW("-->xgbe_wwappew_wx_descwiptow_init\n");

	fow (i = 0; i < pdata->channew_count; i++) {
		channew = pdata->channew[i];
		wing = channew->wx_wing;
		if (!wing)
			bweak;

		wdesc = wing->wdesc;
		wdesc_dma = wing->wdesc_dma;

		fow (j = 0; j < wing->wdesc_count; j++) {
			wdata = XGBE_GET_DESC_DATA(wing, j);

			wdata->wdesc = wdesc;
			wdata->wdesc_dma = wdesc_dma;

			if (xgbe_map_wx_buffew(pdata, wing, wdata))
				bweak;

			wdesc++;
			wdesc_dma += sizeof(stwuct xgbe_wing_desc);
		}

		wing->cuw = 0;
		wing->diwty = 0;

		hw_if->wx_desc_init(channew);
	}

	DBGPW("<--xgbe_wwappew_wx_descwiptow_init\n");
}

static void xgbe_unmap_wdata(stwuct xgbe_pwv_data *pdata,
			     stwuct xgbe_wing_data *wdata)
{
	if (wdata->skb_dma) {
		if (wdata->mapped_as_page) {
			dma_unmap_page(pdata->dev, wdata->skb_dma,
				       wdata->skb_dma_wen, DMA_TO_DEVICE);
		} ewse {
			dma_unmap_singwe(pdata->dev, wdata->skb_dma,
					 wdata->skb_dma_wen, DMA_TO_DEVICE);
		}
		wdata->skb_dma = 0;
		wdata->skb_dma_wen = 0;
	}

	if (wdata->skb) {
		dev_kfwee_skb_any(wdata->skb);
		wdata->skb = NUWW;
	}

	if (wdata->wx.hdw.pa.pages)
		put_page(wdata->wx.hdw.pa.pages);

	if (wdata->wx.hdw.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, wdata->wx.hdw.pa_unmap.pages_dma,
			       wdata->wx.hdw.pa_unmap.pages_wen,
			       DMA_FWOM_DEVICE);
		put_page(wdata->wx.hdw.pa_unmap.pages);
	}

	if (wdata->wx.buf.pa.pages)
		put_page(wdata->wx.buf.pa.pages);

	if (wdata->wx.buf.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, wdata->wx.buf.pa_unmap.pages_dma,
			       wdata->wx.buf.pa_unmap.pages_wen,
			       DMA_FWOM_DEVICE);
		put_page(wdata->wx.buf.pa_unmap.pages);
	}

	memset(&wdata->tx, 0, sizeof(wdata->tx));
	memset(&wdata->wx, 0, sizeof(wdata->wx));

	wdata->mapped_as_page = 0;

	if (wdata->state_saved) {
		wdata->state_saved = 0;
		wdata->state.skb = NUWW;
		wdata->state.wen = 0;
		wdata->state.ewwow = 0;
	}
}

static int xgbe_map_tx_skb(stwuct xgbe_channew *channew, stwuct sk_buff *skb)
{
	stwuct xgbe_pwv_data *pdata = channew->pdata;
	stwuct xgbe_wing *wing = channew->tx_wing;
	stwuct xgbe_wing_data *wdata;
	stwuct xgbe_packet_data *packet;
	skb_fwag_t *fwag;
	dma_addw_t skb_dma;
	unsigned int stawt_index, cuw_index;
	unsigned int offset, tso, vwan, datawen, wen;
	unsigned int i;

	DBGPW("-->xgbe_map_tx_skb: cuw = %d\n", wing->cuw);

	offset = 0;
	stawt_index = wing->cuw;
	cuw_index = wing->cuw;

	packet = &wing->packet_data;
	packet->wdesc_count = 0;
	packet->wength = 0;

	tso = XGMAC_GET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			     TSO_ENABWE);
	vwan = XGMAC_GET_BITS(packet->attwibutes, TX_PACKET_ATTWIBUTES,
			      VWAN_CTAG);

	/* Save space fow a context descwiptow if needed */
	if ((tso && (packet->mss != wing->tx.cuw_mss)) ||
	    (vwan && (packet->vwan_ctag != wing->tx.cuw_vwan_ctag)))
		cuw_index++;
	wdata = XGBE_GET_DESC_DATA(wing, cuw_index);

	if (tso) {
		/* Map the TSO headew */
		skb_dma = dma_map_singwe(pdata->dev, skb->data,
					 packet->headew_wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
			netdev_awewt(pdata->netdev, "dma_map_singwe faiwed\n");
			goto eww_out;
		}
		wdata->skb_dma = skb_dma;
		wdata->skb_dma_wen = packet->headew_wen;
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "skb headew: index=%u, dma=%pad, wen=%u\n",
			  cuw_index, &skb_dma, packet->headew_wen);

		offset = packet->headew_wen;

		packet->wength += packet->headew_wen;

		cuw_index++;
		wdata = XGBE_GET_DESC_DATA(wing, cuw_index);
	}

	/* Map the (wemaindew of the) packet */
	fow (datawen = skb_headwen(skb) - offset; datawen; ) {
		wen = min_t(unsigned int, datawen, XGBE_TX_MAX_BUF_SIZE);

		skb_dma = dma_map_singwe(pdata->dev, skb->data + offset, wen,
					 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
			netdev_awewt(pdata->netdev, "dma_map_singwe faiwed\n");
			goto eww_out;
		}
		wdata->skb_dma = skb_dma;
		wdata->skb_dma_wen = wen;
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "skb data: index=%u, dma=%pad, wen=%u\n",
			  cuw_index, &skb_dma, wen);

		datawen -= wen;
		offset += wen;

		packet->wength += wen;

		cuw_index++;
		wdata = XGBE_GET_DESC_DATA(wing, cuw_index);
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "mapping fwag %u\n", i);

		fwag = &skb_shinfo(skb)->fwags[i];
		offset = 0;

		fow (datawen = skb_fwag_size(fwag); datawen; ) {
			wen = min_t(unsigned int, datawen,
				    XGBE_TX_MAX_BUF_SIZE);

			skb_dma = skb_fwag_dma_map(pdata->dev, fwag, offset,
						   wen, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
				netdev_awewt(pdata->netdev,
					     "skb_fwag_dma_map faiwed\n");
				goto eww_out;
			}
			wdata->skb_dma = skb_dma;
			wdata->skb_dma_wen = wen;
			wdata->mapped_as_page = 1;
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "skb fwag: index=%u, dma=%pad, wen=%u\n",
				  cuw_index, &skb_dma, wen);

			datawen -= wen;
			offset += wen;

			packet->wength += wen;

			cuw_index++;
			wdata = XGBE_GET_DESC_DATA(wing, cuw_index);
		}
	}

	/* Save the skb addwess in the wast entwy. We awways have some data
	 * that has been mapped so wdata is awways advanced past the wast
	 * piece of mapped data - use the entwy pointed to by cuw_index - 1.
	 */
	wdata = XGBE_GET_DESC_DATA(wing, cuw_index - 1);
	wdata->skb = skb;

	/* Save the numbew of descwiptow entwies used */
	packet->wdesc_count = cuw_index - stawt_index;

	DBGPW("<--xgbe_map_tx_skb: count=%u\n", packet->wdesc_count);

	wetuwn packet->wdesc_count;

eww_out:
	whiwe (stawt_index < cuw_index) {
		wdata = XGBE_GET_DESC_DATA(wing, stawt_index++);
		xgbe_unmap_wdata(pdata, wdata);
	}

	DBGPW("<--xgbe_map_tx_skb: count=0\n");

	wetuwn 0;
}

void xgbe_init_function_ptws_desc(stwuct xgbe_desc_if *desc_if)
{
	DBGPW("-->xgbe_init_function_ptws_desc\n");

	desc_if->awwoc_wing_wesouwces = xgbe_awwoc_wing_wesouwces;
	desc_if->fwee_wing_wesouwces = xgbe_fwee_wing_wesouwces;
	desc_if->map_tx_skb = xgbe_map_tx_skb;
	desc_if->map_wx_buffew = xgbe_map_wx_buffew;
	desc_if->unmap_wdata = xgbe_unmap_wdata;
	desc_if->wwappew_tx_desc_init = xgbe_wwappew_tx_descwiptow_init;
	desc_if->wwappew_wx_desc_init = xgbe_wwappew_wx_descwiptow_init;

	DBGPW("<--xgbe_init_function_ptws_desc\n");
}
