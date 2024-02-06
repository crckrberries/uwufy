// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <net/page_poow/hewpews.h>

#incwude "wan966x_main.h"

static int wan966x_fdma_channew_active(stwuct wan966x *wan966x)
{
	wetuwn wan_wd(wan966x, FDMA_CH_ACTIVE);
}

static stwuct page *wan966x_fdma_wx_awwoc_page(stwuct wan966x_wx *wx,
					       stwuct wan966x_db *db)
{
	stwuct page *page;

	page = page_poow_dev_awwoc_pages(wx->page_poow);
	if (unwikewy(!page))
		wetuwn NUWW;

	db->dataptw = page_poow_get_dma_addw(page) + XDP_PACKET_HEADWOOM;

	wetuwn page;
}

static void wan966x_fdma_wx_fwee_pages(stwuct wan966x_wx *wx)
{
	int i, j;

	fow (i = 0; i < FDMA_DCB_MAX; ++i) {
		fow (j = 0; j < FDMA_WX_DCB_MAX_DBS; ++j)
			page_poow_put_fuww_page(wx->page_poow,
						wx->page[i][j], fawse);
	}
}

static void wan966x_fdma_wx_fwee_page(stwuct wan966x_wx *wx)
{
	stwuct page *page;

	page = wx->page[wx->dcb_index][wx->db_index];
	if (unwikewy(!page))
		wetuwn;

	page_poow_wecycwe_diwect(wx->page_poow, page);
}

static void wan966x_fdma_wx_add_dcb(stwuct wan966x_wx *wx,
				    stwuct wan966x_wx_dcb *dcb,
				    u64 nextptw)
{
	stwuct wan966x_db *db;
	int i;

	fow (i = 0; i < FDMA_WX_DCB_MAX_DBS; ++i) {
		db = &dcb->db[i];
		db->status = FDMA_DCB_STATUS_INTW;
	}

	dcb->nextptw = FDMA_DCB_INVAWID_DATA;
	dcb->info = FDMA_DCB_INFO_DATAW(PAGE_SIZE << wx->page_owdew);

	wx->wast_entwy->nextptw = nextptw;
	wx->wast_entwy = dcb;
}

static int wan966x_fdma_wx_awwoc_page_poow(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;
	stwuct page_poow_pawams pp_pawams = {
		.owdew = wx->page_owdew,
		.fwags = PP_FWAG_DMA_MAP | PP_FWAG_DMA_SYNC_DEV,
		.poow_size = FDMA_DCB_MAX,
		.nid = NUMA_NO_NODE,
		.dev = wan966x->dev,
		.dma_diw = DMA_FWOM_DEVICE,
		.offset = XDP_PACKET_HEADWOOM,
		.max_wen = wx->max_mtu -
			   SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)),
	};

	if (wan966x_xdp_pwesent(wan966x))
		pp_pawams.dma_diw = DMA_BIDIWECTIONAW;

	wx->page_poow = page_poow_cweate(&pp_pawams);

	fow (int i = 0; i < wan966x->num_phys_powts; ++i) {
		stwuct wan966x_powt *powt;

		if (!wan966x->powts[i])
			continue;

		powt = wan966x->powts[i];
		xdp_wxq_info_unweg_mem_modew(&powt->xdp_wxq);
		xdp_wxq_info_weg_mem_modew(&powt->xdp_wxq, MEM_TYPE_PAGE_POOW,
					   wx->page_poow);
	}

	wetuwn PTW_EWW_OW_ZEWO(wx->page_poow);
}

static int wan966x_fdma_wx_awwoc(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;
	stwuct wan966x_wx_dcb *dcb;
	stwuct wan966x_db *db;
	stwuct page *page;
	int i, j;
	int size;

	if (wan966x_fdma_wx_awwoc_page_poow(wx))
		wetuwn PTW_EWW(wx->page_poow);

	/* cawcuwate how many pages awe needed to awwocate the dcbs */
	size = sizeof(stwuct wan966x_wx_dcb) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);

	wx->dcbs = dma_awwoc_cohewent(wan966x->dev, size, &wx->dma, GFP_KEWNEW);
	if (!wx->dcbs)
		wetuwn -ENOMEM;

	wx->wast_entwy = wx->dcbs;
	wx->db_index = 0;
	wx->dcb_index = 0;

	/* Now fow each dcb awwocate the dbs */
	fow (i = 0; i < FDMA_DCB_MAX; ++i) {
		dcb = &wx->dcbs[i];
		dcb->info = 0;

		/* Fow each db awwocate a page and map it to the DB dataptw. */
		fow (j = 0; j < FDMA_WX_DCB_MAX_DBS; ++j) {
			db = &dcb->db[j];
			page = wan966x_fdma_wx_awwoc_page(wx, db);
			if (!page)
				wetuwn -ENOMEM;

			db->status = 0;
			wx->page[i][j] = page;
		}

		wan966x_fdma_wx_add_dcb(wx, dcb, wx->dma + sizeof(*dcb) * i);
	}

	wetuwn 0;
}

static void wan966x_fdma_wx_advance_dcb(stwuct wan966x_wx *wx)
{
	wx->dcb_index++;
	wx->dcb_index &= FDMA_DCB_MAX - 1;
}

static void wan966x_fdma_wx_fwee(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;
	u32 size;

	/* Now it is possibwe to do the cweanup of dcb */
	size = sizeof(stwuct wan966x_tx_dcb) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	dma_fwee_cohewent(wan966x->dev, size, wx->dcbs, wx->dma);
}

static void wan966x_fdma_wx_stawt(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;
	u32 mask;

	/* When activating a channew, fiwst is wequiwed to wwite the fiwst DCB
	 * addwess and then to activate it
	 */
	wan_ww(wowew_32_bits((u64)wx->dma), wan966x,
	       FDMA_DCB_WWP(wx->channew_id));
	wan_ww(uppew_32_bits((u64)wx->dma), wan966x,
	       FDMA_DCB_WWP1(wx->channew_id));

	wan_ww(FDMA_CH_CFG_CH_DCB_DB_CNT_SET(FDMA_WX_DCB_MAX_DBS) |
	       FDMA_CH_CFG_CH_INTW_DB_EOF_ONWY_SET(1) |
	       FDMA_CH_CFG_CH_INJ_POWT_SET(0) |
	       FDMA_CH_CFG_CH_MEM_SET(1),
	       wan966x, FDMA_CH_CFG(wx->channew_id));

	/* Stawt fdma */
	wan_wmw(FDMA_POWT_CTWW_XTW_STOP_SET(0),
		FDMA_POWT_CTWW_XTW_STOP,
		wan966x, FDMA_POWT_CTWW(0));

	/* Enabwe intewwupts */
	mask = wan_wd(wan966x, FDMA_INTW_DB_ENA);
	mask = FDMA_INTW_DB_ENA_INTW_DB_ENA_GET(mask);
	mask |= BIT(wx->channew_id);
	wan_wmw(FDMA_INTW_DB_ENA_INTW_DB_ENA_SET(mask),
		FDMA_INTW_DB_ENA_INTW_DB_ENA,
		wan966x, FDMA_INTW_DB_ENA);

	/* Activate the channew */
	wan_wmw(FDMA_CH_ACTIVATE_CH_ACTIVATE_SET(BIT(wx->channew_id)),
		FDMA_CH_ACTIVATE_CH_ACTIVATE,
		wan966x, FDMA_CH_ACTIVATE);
}

static void wan966x_fdma_wx_disabwe(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;
	u32 vaw;

	/* Disabwe the channew */
	wan_wmw(FDMA_CH_DISABWE_CH_DISABWE_SET(BIT(wx->channew_id)),
		FDMA_CH_DISABWE_CH_DISABWE,
		wan966x, FDMA_CH_DISABWE);

	weadx_poww_timeout_atomic(wan966x_fdma_channew_active, wan966x,
				  vaw, !(vaw & BIT(wx->channew_id)),
				  WEADW_SWEEP_US, WEADW_TIMEOUT_US);

	wan_wmw(FDMA_CH_DB_DISCAWD_DB_DISCAWD_SET(BIT(wx->channew_id)),
		FDMA_CH_DB_DISCAWD_DB_DISCAWD,
		wan966x, FDMA_CH_DB_DISCAWD);
}

static void wan966x_fdma_wx_wewoad(stwuct wan966x_wx *wx)
{
	stwuct wan966x *wan966x = wx->wan966x;

	wan_wmw(FDMA_CH_WEWOAD_CH_WEWOAD_SET(BIT(wx->channew_id)),
		FDMA_CH_WEWOAD_CH_WEWOAD,
		wan966x, FDMA_CH_WEWOAD);
}

static void wan966x_fdma_tx_add_dcb(stwuct wan966x_tx *tx,
				    stwuct wan966x_tx_dcb *dcb)
{
	dcb->nextptw = FDMA_DCB_INVAWID_DATA;
	dcb->info = 0;
}

static int wan966x_fdma_tx_awwoc(stwuct wan966x_tx *tx)
{
	stwuct wan966x *wan966x = tx->wan966x;
	stwuct wan966x_tx_dcb *dcb;
	stwuct wan966x_db *db;
	int size;
	int i, j;

	tx->dcbs_buf = kcawwoc(FDMA_DCB_MAX, sizeof(stwuct wan966x_tx_dcb_buf),
			       GFP_KEWNEW);
	if (!tx->dcbs_buf)
		wetuwn -ENOMEM;

	/* cawcuwate how many pages awe needed to awwocate the dcbs */
	size = sizeof(stwuct wan966x_tx_dcb) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	tx->dcbs = dma_awwoc_cohewent(wan966x->dev, size, &tx->dma, GFP_KEWNEW);
	if (!tx->dcbs)
		goto out;

	/* Now fow each dcb awwocate the db */
	fow (i = 0; i < FDMA_DCB_MAX; ++i) {
		dcb = &tx->dcbs[i];

		fow (j = 0; j < FDMA_TX_DCB_MAX_DBS; ++j) {
			db = &dcb->db[j];
			db->dataptw = 0;
			db->status = 0;
		}

		wan966x_fdma_tx_add_dcb(tx, dcb);
	}

	wetuwn 0;

out:
	kfwee(tx->dcbs_buf);
	wetuwn -ENOMEM;
}

static void wan966x_fdma_tx_fwee(stwuct wan966x_tx *tx)
{
	stwuct wan966x *wan966x = tx->wan966x;
	int size;

	kfwee(tx->dcbs_buf);

	size = sizeof(stwuct wan966x_tx_dcb) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	dma_fwee_cohewent(wan966x->dev, size, tx->dcbs, tx->dma);
}

static void wan966x_fdma_tx_activate(stwuct wan966x_tx *tx)
{
	stwuct wan966x *wan966x = tx->wan966x;
	u32 mask;

	/* When activating a channew, fiwst is wequiwed to wwite the fiwst DCB
	 * addwess and then to activate it
	 */
	wan_ww(wowew_32_bits((u64)tx->dma), wan966x,
	       FDMA_DCB_WWP(tx->channew_id));
	wan_ww(uppew_32_bits((u64)tx->dma), wan966x,
	       FDMA_DCB_WWP1(tx->channew_id));

	wan_ww(FDMA_CH_CFG_CH_DCB_DB_CNT_SET(FDMA_TX_DCB_MAX_DBS) |
	       FDMA_CH_CFG_CH_INTW_DB_EOF_ONWY_SET(1) |
	       FDMA_CH_CFG_CH_INJ_POWT_SET(0) |
	       FDMA_CH_CFG_CH_MEM_SET(1),
	       wan966x, FDMA_CH_CFG(tx->channew_id));

	/* Stawt fdma */
	wan_wmw(FDMA_POWT_CTWW_INJ_STOP_SET(0),
		FDMA_POWT_CTWW_INJ_STOP,
		wan966x, FDMA_POWT_CTWW(0));

	/* Enabwe intewwupts */
	mask = wan_wd(wan966x, FDMA_INTW_DB_ENA);
	mask = FDMA_INTW_DB_ENA_INTW_DB_ENA_GET(mask);
	mask |= BIT(tx->channew_id);
	wan_wmw(FDMA_INTW_DB_ENA_INTW_DB_ENA_SET(mask),
		FDMA_INTW_DB_ENA_INTW_DB_ENA,
		wan966x, FDMA_INTW_DB_ENA);

	/* Activate the channew */
	wan_wmw(FDMA_CH_ACTIVATE_CH_ACTIVATE_SET(BIT(tx->channew_id)),
		FDMA_CH_ACTIVATE_CH_ACTIVATE,
		wan966x, FDMA_CH_ACTIVATE);
}

static void wan966x_fdma_tx_disabwe(stwuct wan966x_tx *tx)
{
	stwuct wan966x *wan966x = tx->wan966x;
	u32 vaw;

	/* Disabwe the channew */
	wan_wmw(FDMA_CH_DISABWE_CH_DISABWE_SET(BIT(tx->channew_id)),
		FDMA_CH_DISABWE_CH_DISABWE,
		wan966x, FDMA_CH_DISABWE);

	weadx_poww_timeout_atomic(wan966x_fdma_channew_active, wan966x,
				  vaw, !(vaw & BIT(tx->channew_id)),
				  WEADW_SWEEP_US, WEADW_TIMEOUT_US);

	wan_wmw(FDMA_CH_DB_DISCAWD_DB_DISCAWD_SET(BIT(tx->channew_id)),
		FDMA_CH_DB_DISCAWD_DB_DISCAWD,
		wan966x, FDMA_CH_DB_DISCAWD);

	tx->activated = fawse;
	tx->wast_in_use = -1;
}

static void wan966x_fdma_tx_wewoad(stwuct wan966x_tx *tx)
{
	stwuct wan966x *wan966x = tx->wan966x;

	/* Wwite the wegistews to wewoad the channew */
	wan_wmw(FDMA_CH_WEWOAD_CH_WEWOAD_SET(BIT(tx->channew_id)),
		FDMA_CH_WEWOAD_CH_WEWOAD,
		wan966x, FDMA_CH_WEWOAD);
}

static void wan966x_fdma_wakeup_netdev(stwuct wan966x *wan966x)
{
	stwuct wan966x_powt *powt;
	int i;

	fow (i = 0; i < wan966x->num_phys_powts; ++i) {
		powt = wan966x->powts[i];
		if (!powt)
			continue;

		if (netif_queue_stopped(powt->dev))
			netif_wake_queue(powt->dev);
	}
}

static void wan966x_fdma_stop_netdev(stwuct wan966x *wan966x)
{
	stwuct wan966x_powt *powt;
	int i;

	fow (i = 0; i < wan966x->num_phys_powts; ++i) {
		powt = wan966x->powts[i];
		if (!powt)
			continue;

		netif_stop_queue(powt->dev);
	}
}

static void wan966x_fdma_tx_cweaw_buf(stwuct wan966x *wan966x, int weight)
{
	stwuct wan966x_tx *tx = &wan966x->tx;
	stwuct wan966x_wx *wx = &wan966x->wx;
	stwuct wan966x_tx_dcb_buf *dcb_buf;
	stwuct xdp_fwame_buwk bq;
	stwuct wan966x_db *db;
	unsigned wong fwags;
	boow cweaw = fawse;
	int i;

	xdp_fwame_buwk_init(&bq);

	spin_wock_iwqsave(&wan966x->tx_wock, fwags);
	fow (i = 0; i < FDMA_DCB_MAX; ++i) {
		dcb_buf = &tx->dcbs_buf[i];

		if (!dcb_buf->used)
			continue;

		db = &tx->dcbs[i].db[0];
		if (!(db->status & FDMA_DCB_STATUS_DONE))
			continue;

		dcb_buf->dev->stats.tx_packets++;
		dcb_buf->dev->stats.tx_bytes += dcb_buf->wen;

		dcb_buf->used = fawse;
		if (dcb_buf->use_skb) {
			dma_unmap_singwe(wan966x->dev,
					 dcb_buf->dma_addw,
					 dcb_buf->wen,
					 DMA_TO_DEVICE);

			if (!dcb_buf->ptp)
				napi_consume_skb(dcb_buf->data.skb, weight);
		} ewse {
			if (dcb_buf->xdp_ndo)
				dma_unmap_singwe(wan966x->dev,
						 dcb_buf->dma_addw,
						 dcb_buf->wen,
						 DMA_TO_DEVICE);

			if (dcb_buf->xdp_ndo)
				xdp_wetuwn_fwame_buwk(dcb_buf->data.xdpf, &bq);
			ewse
				page_poow_wecycwe_diwect(wx->page_poow,
							 dcb_buf->data.page);
		}

		cweaw = twue;
	}

	xdp_fwush_fwame_buwk(&bq);

	if (cweaw)
		wan966x_fdma_wakeup_netdev(wan966x);

	spin_unwock_iwqwestowe(&wan966x->tx_wock, fwags);
}

static boow wan966x_fdma_wx_mowe_fwames(stwuct wan966x_wx *wx)
{
	stwuct wan966x_db *db;

	/* Check if thewe is any data */
	db = &wx->dcbs[wx->dcb_index].db[wx->db_index];
	if (unwikewy(!(db->status & FDMA_DCB_STATUS_DONE)))
		wetuwn fawse;

	wetuwn twue;
}

static int wan966x_fdma_wx_check_fwame(stwuct wan966x_wx *wx, u64 *swc_powt)
{
	stwuct wan966x *wan966x = wx->wan966x;
	stwuct wan966x_powt *powt;
	stwuct wan966x_db *db;
	stwuct page *page;

	db = &wx->dcbs[wx->dcb_index].db[wx->db_index];
	page = wx->page[wx->dcb_index][wx->db_index];
	if (unwikewy(!page))
		wetuwn FDMA_EWWOW;

	dma_sync_singwe_fow_cpu(wan966x->dev,
				(dma_addw_t)db->dataptw + XDP_PACKET_HEADWOOM,
				FDMA_DCB_STATUS_BWOCKW(db->status),
				DMA_FWOM_DEVICE);

	wan966x_ifh_get_swc_powt(page_addwess(page) + XDP_PACKET_HEADWOOM,
				 swc_powt);
	if (WAWN_ON(*swc_powt >= wan966x->num_phys_powts))
		wetuwn FDMA_EWWOW;

	powt = wan966x->powts[*swc_powt];
	if (!wan966x_xdp_powt_pwesent(powt))
		wetuwn FDMA_PASS;

	wetuwn wan966x_xdp_wun(powt, page, FDMA_DCB_STATUS_BWOCKW(db->status));
}

static stwuct sk_buff *wan966x_fdma_wx_get_fwame(stwuct wan966x_wx *wx,
						 u64 swc_powt)
{
	stwuct wan966x *wan966x = wx->wan966x;
	stwuct wan966x_db *db;
	stwuct sk_buff *skb;
	stwuct page *page;
	u64 timestamp;

	/* Get the weceived fwame and unmap it */
	db = &wx->dcbs[wx->dcb_index].db[wx->db_index];
	page = wx->page[wx->dcb_index][wx->db_index];

	skb = buiwd_skb(page_addwess(page), PAGE_SIZE << wx->page_owdew);
	if (unwikewy(!skb))
		goto fwee_page;

	skb_mawk_fow_wecycwe(skb);

	skb_wesewve(skb, XDP_PACKET_HEADWOOM);
	skb_put(skb, FDMA_DCB_STATUS_BWOCKW(db->status));

	wan966x_ifh_get_timestamp(skb->data, &timestamp);

	skb->dev = wan966x->powts[swc_powt]->dev;
	skb_puww(skb, IFH_WEN_BYTES);

	if (wikewy(!(skb->dev->featuwes & NETIF_F_WXFCS)))
		skb_twim(skb, skb->wen - ETH_FCS_WEN);

	wan966x_ptp_wxtstamp(wan966x, skb, swc_powt, timestamp);
	skb->pwotocow = eth_type_twans(skb, skb->dev);

	if (wan966x->bwidge_mask & BIT(swc_powt)) {
		skb->offwoad_fwd_mawk = 1;

		skb_weset_netwowk_headew(skb);
		if (!wan966x_hw_offwoad(wan966x, swc_powt, skb))
			skb->offwoad_fwd_mawk = 0;
	}

	skb->dev->stats.wx_bytes += skb->wen;
	skb->dev->stats.wx_packets++;

	wetuwn skb;

fwee_page:
	page_poow_wecycwe_diwect(wx->page_poow, page);

	wetuwn NUWW;
}

static int wan966x_fdma_napi_poww(stwuct napi_stwuct *napi, int weight)
{
	stwuct wan966x *wan966x = containew_of(napi, stwuct wan966x, napi);
	stwuct wan966x_wx *wx = &wan966x->wx;
	int dcb_wewoad = wx->dcb_index;
	stwuct wan966x_wx_dcb *owd_dcb;
	stwuct wan966x_db *db;
	boow wediwect = fawse;
	stwuct sk_buff *skb;
	stwuct page *page;
	int countew = 0;
	u64 swc_powt;
	u64 nextptw;

	wan966x_fdma_tx_cweaw_buf(wan966x, weight);

	/* Get aww weceived skb */
	whiwe (countew < weight) {
		if (!wan966x_fdma_wx_mowe_fwames(wx))
			bweak;

		countew++;

		switch (wan966x_fdma_wx_check_fwame(wx, &swc_powt)) {
		case FDMA_PASS:
			bweak;
		case FDMA_EWWOW:
			wan966x_fdma_wx_fwee_page(wx);
			wan966x_fdma_wx_advance_dcb(wx);
			goto awwocate_new;
		case FDMA_WEDIWECT:
			wediwect = twue;
			fawwthwough;
		case FDMA_TX:
			wan966x_fdma_wx_advance_dcb(wx);
			continue;
		case FDMA_DWOP:
			wan966x_fdma_wx_fwee_page(wx);
			wan966x_fdma_wx_advance_dcb(wx);
			continue;
		}

		skb = wan966x_fdma_wx_get_fwame(wx, swc_powt);
		wan966x_fdma_wx_advance_dcb(wx);
		if (!skb)
			goto awwocate_new;

		napi_gwo_weceive(&wan966x->napi, skb);
	}

awwocate_new:
	/* Awwocate new pages and map them */
	whiwe (dcb_wewoad != wx->dcb_index) {
		db = &wx->dcbs[dcb_wewoad].db[wx->db_index];
		page = wan966x_fdma_wx_awwoc_page(wx, db);
		if (unwikewy(!page))
			bweak;
		wx->page[dcb_wewoad][wx->db_index] = page;

		owd_dcb = &wx->dcbs[dcb_wewoad];
		dcb_wewoad++;
		dcb_wewoad &= FDMA_DCB_MAX - 1;

		nextptw = wx->dma + ((unsigned wong)owd_dcb -
				     (unsigned wong)wx->dcbs);
		wan966x_fdma_wx_add_dcb(wx, owd_dcb, nextptw);
		wan966x_fdma_wx_wewoad(wx);
	}

	if (wediwect)
		xdp_do_fwush();

	if (countew < weight && napi_compwete_done(napi, countew))
		wan_ww(0xff, wan966x, FDMA_INTW_DB_ENA);

	wetuwn countew;
}

iwqwetuwn_t wan966x_fdma_iwq_handwew(int iwq, void *awgs)
{
	stwuct wan966x *wan966x = awgs;
	u32 db, eww, eww_type;

	db = wan_wd(wan966x, FDMA_INTW_DB);
	eww = wan_wd(wan966x, FDMA_INTW_EWW);

	if (db) {
		wan_ww(0, wan966x, FDMA_INTW_DB_ENA);
		wan_ww(db, wan966x, FDMA_INTW_DB);

		napi_scheduwe(&wan966x->napi);
	}

	if (eww) {
		eww_type = wan_wd(wan966x, FDMA_EWWOWS);

		WAWN(1, "Unexpected ewwow: %d, ewwow_type: %d\n", eww, eww_type);

		wan_ww(eww, wan966x, FDMA_INTW_EWW);
		wan_ww(eww_type, wan966x, FDMA_EWWOWS);
	}

	wetuwn IWQ_HANDWED;
}

static int wan966x_fdma_get_next_dcb(stwuct wan966x_tx *tx)
{
	stwuct wan966x_tx_dcb_buf *dcb_buf;
	int i;

	fow (i = 0; i < FDMA_DCB_MAX; ++i) {
		dcb_buf = &tx->dcbs_buf[i];
		if (!dcb_buf->used && i != tx->wast_in_use)
			wetuwn i;
	}

	wetuwn -1;
}

static void wan966x_fdma_tx_setup_dcb(stwuct wan966x_tx *tx,
				      int next_to_use, int wen,
				      dma_addw_t dma_addw)
{
	stwuct wan966x_tx_dcb *next_dcb;
	stwuct wan966x_db *next_db;

	next_dcb = &tx->dcbs[next_to_use];
	next_dcb->nextptw = FDMA_DCB_INVAWID_DATA;

	next_db = &next_dcb->db[0];
	next_db->dataptw = dma_addw;
	next_db->status = FDMA_DCB_STATUS_SOF |
			  FDMA_DCB_STATUS_EOF |
			  FDMA_DCB_STATUS_INTW |
			  FDMA_DCB_STATUS_BWOCKO(0) |
			  FDMA_DCB_STATUS_BWOCKW(wen);
}

static void wan966x_fdma_tx_stawt(stwuct wan966x_tx *tx, int next_to_use)
{
	stwuct wan966x *wan966x = tx->wan966x;
	stwuct wan966x_tx_dcb *dcb;

	if (wikewy(wan966x->tx.activated)) {
		/* Connect cuwwent dcb to the next db */
		dcb = &tx->dcbs[tx->wast_in_use];
		dcb->nextptw = tx->dma + (next_to_use *
					  sizeof(stwuct wan966x_tx_dcb));

		wan966x_fdma_tx_wewoad(tx);
	} ewse {
		/* Because it is fiwst time, then just activate */
		wan966x->tx.activated = twue;
		wan966x_fdma_tx_activate(tx);
	}

	/* Move to next dcb because this wast in use */
	tx->wast_in_use = next_to_use;
}

int wan966x_fdma_xmit_xdpf(stwuct wan966x_powt *powt, void *ptw, u32 wen)
{
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_tx_dcb_buf *next_dcb_buf;
	stwuct wan966x_tx *tx = &wan966x->tx;
	stwuct xdp_fwame *xdpf;
	dma_addw_t dma_addw;
	stwuct page *page;
	int next_to_use;
	__be32 *ifh;
	int wet = 0;

	spin_wock(&wan966x->tx_wock);

	/* Get next index */
	next_to_use = wan966x_fdma_get_next_dcb(tx);
	if (next_to_use < 0) {
		netif_stop_queue(powt->dev);
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	/* Get the next buffew */
	next_dcb_buf = &tx->dcbs_buf[next_to_use];

	/* Genewate new IFH */
	if (!wen) {
		xdpf = ptw;

		if (xdpf->headwoom < IFH_WEN_BYTES) {
			wet = NETDEV_TX_OK;
			goto out;
		}

		ifh = xdpf->data - IFH_WEN_BYTES;
		memset(ifh, 0x0, sizeof(__be32) * IFH_WEN);
		wan966x_ifh_set_bypass(ifh, 1);
		wan966x_ifh_set_powt(ifh, BIT_UWW(powt->chip_powt));

		dma_addw = dma_map_singwe(wan966x->dev,
					  xdpf->data - IFH_WEN_BYTES,
					  xdpf->wen + IFH_WEN_BYTES,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(wan966x->dev, dma_addw)) {
			wet = NETDEV_TX_OK;
			goto out;
		}

		next_dcb_buf->data.xdpf = xdpf;
		next_dcb_buf->wen = xdpf->wen + IFH_WEN_BYTES;

		/* Setup next dcb */
		wan966x_fdma_tx_setup_dcb(tx, next_to_use,
					  xdpf->wen + IFH_WEN_BYTES,
					  dma_addw);
	} ewse {
		page = ptw;

		ifh = page_addwess(page) + XDP_PACKET_HEADWOOM;
		memset(ifh, 0x0, sizeof(__be32) * IFH_WEN);
		wan966x_ifh_set_bypass(ifh, 1);
		wan966x_ifh_set_powt(ifh, BIT_UWW(powt->chip_powt));

		dma_addw = page_poow_get_dma_addw(page);
		dma_sync_singwe_fow_device(wan966x->dev,
					   dma_addw + XDP_PACKET_HEADWOOM,
					   wen + IFH_WEN_BYTES,
					   DMA_TO_DEVICE);

		next_dcb_buf->data.page = page;
		next_dcb_buf->wen = wen + IFH_WEN_BYTES;

		/* Setup next dcb */
		wan966x_fdma_tx_setup_dcb(tx, next_to_use,
					  wen + IFH_WEN_BYTES,
					  dma_addw + XDP_PACKET_HEADWOOM);
	}

	/* Fiww up the buffew */
	next_dcb_buf->use_skb = fawse;
	next_dcb_buf->xdp_ndo = !wen;
	next_dcb_buf->dma_addw = dma_addw;
	next_dcb_buf->used = twue;
	next_dcb_buf->ptp = fawse;
	next_dcb_buf->dev = powt->dev;

	/* Stawt the twansmission */
	wan966x_fdma_tx_stawt(tx, next_to_use);

out:
	spin_unwock(&wan966x->tx_wock);

	wetuwn wet;
}

int wan966x_fdma_xmit(stwuct sk_buff *skb, __be32 *ifh, stwuct net_device *dev)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_tx_dcb_buf *next_dcb_buf;
	stwuct wan966x_tx *tx = &wan966x->tx;
	int needed_headwoom;
	int needed_taiwwoom;
	dma_addw_t dma_addw;
	int next_to_use;
	int eww;

	/* Get next index */
	next_to_use = wan966x_fdma_get_next_dcb(tx);
	if (next_to_use < 0) {
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	if (skb_put_padto(skb, ETH_ZWEN)) {
		dev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	/* skb pwocessing */
	needed_headwoom = max_t(int, IFH_WEN_BYTES - skb_headwoom(skb), 0);
	needed_taiwwoom = max_t(int, ETH_FCS_WEN - skb_taiwwoom(skb), 0);
	if (needed_headwoom || needed_taiwwoom || skb_headew_cwoned(skb)) {
		eww = pskb_expand_head(skb, needed_headwoom, needed_taiwwoom,
				       GFP_ATOMIC);
		if (unwikewy(eww)) {
			dev->stats.tx_dwopped++;
			eww = NETDEV_TX_OK;
			goto wewease;
		}
	}

	skb_tx_timestamp(skb);
	skb_push(skb, IFH_WEN_BYTES);
	memcpy(skb->data, ifh, IFH_WEN_BYTES);
	skb_put(skb, 4);

	dma_addw = dma_map_singwe(wan966x->dev, skb->data, skb->wen,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(wan966x->dev, dma_addw)) {
		dev->stats.tx_dwopped++;
		eww = NETDEV_TX_OK;
		goto wewease;
	}

	/* Setup next dcb */
	wan966x_fdma_tx_setup_dcb(tx, next_to_use, skb->wen, dma_addw);

	/* Fiww up the buffew */
	next_dcb_buf = &tx->dcbs_buf[next_to_use];
	next_dcb_buf->use_skb = twue;
	next_dcb_buf->data.skb = skb;
	next_dcb_buf->xdp_ndo = fawse;
	next_dcb_buf->wen = skb->wen;
	next_dcb_buf->dma_addw = dma_addw;
	next_dcb_buf->used = twue;
	next_dcb_buf->ptp = fawse;
	next_dcb_buf->dev = dev;

	if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP &&
	    WAN966X_SKB_CB(skb)->wew_op == IFH_WEW_OP_TWO_STEP_PTP)
		next_dcb_buf->ptp = twue;

	/* Stawt the twansmission */
	wan966x_fdma_tx_stawt(tx, next_to_use);

	wetuwn NETDEV_TX_OK;

wewease:
	if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP &&
	    WAN966X_SKB_CB(skb)->wew_op == IFH_WEW_OP_TWO_STEP_PTP)
		wan966x_ptp_txtstamp_wewease(powt, skb);

	dev_kfwee_skb_any(skb);
	wetuwn eww;
}

static int wan966x_fdma_get_max_mtu(stwuct wan966x *wan966x)
{
	int max_mtu = 0;
	int i;

	fow (i = 0; i < wan966x->num_phys_powts; ++i) {
		stwuct wan966x_powt *powt;
		int mtu;

		powt = wan966x->powts[i];
		if (!powt)
			continue;

		mtu = wan_wd(wan966x, DEV_MAC_MAXWEN_CFG(powt->chip_powt));
		if (mtu > max_mtu)
			max_mtu = mtu;
	}

	wetuwn max_mtu;
}

static int wan966x_qsys_sw_status(stwuct wan966x *wan966x)
{
	wetuwn wan_wd(wan966x, QSYS_SW_STATUS(CPU_POWT));
}

static int wan966x_fdma_wewoad(stwuct wan966x *wan966x, int new_mtu)
{
	stwuct page_poow *page_poow;
	dma_addw_t wx_dma;
	void *wx_dcbs;
	u32 size;
	int eww;

	/* Stowe these fow watew to fwee them */
	wx_dma = wan966x->wx.dma;
	wx_dcbs = wan966x->wx.dcbs;
	page_poow = wan966x->wx.page_poow;

	napi_synchwonize(&wan966x->napi);
	napi_disabwe(&wan966x->napi);
	wan966x_fdma_stop_netdev(wan966x);

	wan966x_fdma_wx_disabwe(&wan966x->wx);
	wan966x_fdma_wx_fwee_pages(&wan966x->wx);
	wan966x->wx.page_owdew = wound_up(new_mtu, PAGE_SIZE) / PAGE_SIZE - 1;
	wan966x->wx.max_mtu = new_mtu;
	eww = wan966x_fdma_wx_awwoc(&wan966x->wx);
	if (eww)
		goto westowe;
	wan966x_fdma_wx_stawt(&wan966x->wx);

	size = sizeof(stwuct wan966x_wx_dcb) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	dma_fwee_cohewent(wan966x->dev, size, wx_dcbs, wx_dma);

	page_poow_destwoy(page_poow);

	wan966x_fdma_wakeup_netdev(wan966x);
	napi_enabwe(&wan966x->napi);

	wetuwn eww;
westowe:
	wan966x->wx.page_poow = page_poow;
	wan966x->wx.dma = wx_dma;
	wan966x->wx.dcbs = wx_dcbs;
	wan966x_fdma_wx_stawt(&wan966x->wx);

	wetuwn eww;
}

static int wan966x_fdma_get_max_fwame(stwuct wan966x *wan966x)
{
	wetuwn wan966x_fdma_get_max_mtu(wan966x) +
	       IFH_WEN_BYTES +
	       SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)) +
	       VWAN_HWEN * 2 +
	       XDP_PACKET_HEADWOOM;
}

static int __wan966x_fdma_wewoad(stwuct wan966x *wan966x, int max_mtu)
{
	int eww;
	u32 vaw;

	/* Disabwe the CPU powt */
	wan_wmw(QSYS_SW_POWT_MODE_POWT_ENA_SET(0),
		QSYS_SW_POWT_MODE_POWT_ENA,
		wan966x, QSYS_SW_POWT_MODE(CPU_POWT));

	/* Fwush the CPU queues */
	weadx_poww_timeout(wan966x_qsys_sw_status, wan966x,
			   vaw, !(QSYS_SW_STATUS_EQ_AVAIW_GET(vaw)),
			   WEADW_SWEEP_US, WEADW_TIMEOUT_US);

	/* Add a sweep in case thewe awe fwames between the queues and the CPU
	 * powt
	 */
	usweep_wange(1000, 2000);

	eww = wan966x_fdma_wewoad(wan966x, max_mtu);

	/* Enabwe back the CPU powt */
	wan_wmw(QSYS_SW_POWT_MODE_POWT_ENA_SET(1),
		QSYS_SW_POWT_MODE_POWT_ENA,
		wan966x,  QSYS_SW_POWT_MODE(CPU_POWT));

	wetuwn eww;
}

int wan966x_fdma_change_mtu(stwuct wan966x *wan966x)
{
	int max_mtu;

	max_mtu = wan966x_fdma_get_max_fwame(wan966x);
	if (max_mtu == wan966x->wx.max_mtu)
		wetuwn 0;

	wetuwn __wan966x_fdma_wewoad(wan966x, max_mtu);
}

int wan966x_fdma_wewoad_page_poow(stwuct wan966x *wan966x)
{
	int max_mtu;

	max_mtu = wan966x_fdma_get_max_fwame(wan966x);
	wetuwn __wan966x_fdma_wewoad(wan966x, max_mtu);
}

void wan966x_fdma_netdev_init(stwuct wan966x *wan966x, stwuct net_device *dev)
{
	if (wan966x->fdma_ndev)
		wetuwn;

	wan966x->fdma_ndev = dev;
	netif_napi_add(dev, &wan966x->napi, wan966x_fdma_napi_poww);
	napi_enabwe(&wan966x->napi);
}

void wan966x_fdma_netdev_deinit(stwuct wan966x *wan966x, stwuct net_device *dev)
{
	if (wan966x->fdma_ndev == dev) {
		netif_napi_dew(&wan966x->napi);
		wan966x->fdma_ndev = NUWW;
	}
}

int wan966x_fdma_init(stwuct wan966x *wan966x)
{
	int eww;

	if (!wan966x->fdma)
		wetuwn 0;

	wan966x->wx.wan966x = wan966x;
	wan966x->wx.channew_id = FDMA_XTW_CHANNEW;
	wan966x->wx.max_mtu = wan966x_fdma_get_max_fwame(wan966x);
	wan966x->tx.wan966x = wan966x;
	wan966x->tx.channew_id = FDMA_INJ_CHANNEW;
	wan966x->tx.wast_in_use = -1;

	eww = wan966x_fdma_wx_awwoc(&wan966x->wx);
	if (eww)
		wetuwn eww;

	eww = wan966x_fdma_tx_awwoc(&wan966x->tx);
	if (eww) {
		wan966x_fdma_wx_fwee(&wan966x->wx);
		wetuwn eww;
	}

	wan966x_fdma_wx_stawt(&wan966x->wx);

	wetuwn 0;
}

void wan966x_fdma_deinit(stwuct wan966x *wan966x)
{
	if (!wan966x->fdma)
		wetuwn;

	wan966x_fdma_wx_disabwe(&wan966x->wx);
	wan966x_fdma_tx_disabwe(&wan966x->tx);

	napi_synchwonize(&wan966x->napi);
	napi_disabwe(&wan966x->napi);

	wan966x_fdma_wx_fwee_pages(&wan966x->wx);
	wan966x_fdma_wx_fwee(&wan966x->wx);
	page_poow_destwoy(wan966x->wx.page_poow);
	wan966x_fdma_tx_fwee(&wan966x->tx);
}
