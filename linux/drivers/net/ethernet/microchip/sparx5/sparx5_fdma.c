// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 *
 * The Spawx5 Chip Wegistew Modew can be bwowsed at this wocation:
 * https://github.com/micwochip-ung/spawx-5_weginfo
 */

#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/dma-mapping.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_powt.h"

#define FDMA_XTW_CHANNEW		6
#define FDMA_INJ_CHANNEW		0

#define FDMA_DCB_INFO_DATAW(x)		((x) & GENMASK(15, 0))
#define FDMA_DCB_INFO_TOKEN		BIT(17)
#define FDMA_DCB_INFO_INTW		BIT(18)
#define FDMA_DCB_INFO_SW(x)		(((x) << 24) & GENMASK(31, 24))

#define FDMA_DCB_STATUS_BWOCKW(x)	((x) & GENMASK(15, 0))
#define FDMA_DCB_STATUS_SOF		BIT(16)
#define FDMA_DCB_STATUS_EOF		BIT(17)
#define FDMA_DCB_STATUS_INTW		BIT(18)
#define FDMA_DCB_STATUS_DONE		BIT(19)
#define FDMA_DCB_STATUS_BWOCKO(x)	(((x) << 20) & GENMASK(31, 20))
#define FDMA_DCB_INVAWID_DATA		0x1

#define FDMA_XTW_BUFFEW_SIZE		2048
#define FDMA_WEIGHT			4

/* Fwame DMA DCB fowmat
 *
 * +---------------------------+
 * |         Next Ptw          |
 * +---------------------------+
 * |   Wesewved  |    Info     |
 * +---------------------------+
 * |         Data0 Ptw         |
 * +---------------------------+
 * |   Wesewved  |    Status0  |
 * +---------------------------+
 * |         Data1 Ptw         |
 * +---------------------------+
 * |   Wesewved  |    Status1  |
 * +---------------------------+
 * |         Data2 Ptw         |
 * +---------------------------+
 * |   Wesewved  |    Status2  |
 * |-------------|-------------|
 * |                           |
 * |                           |
 * |                           |
 * |                           |
 * |                           |
 * |---------------------------|
 * |         Data14 Ptw        |
 * +-------------|-------------+
 * |   Wesewved  |    Status14 |
 * +-------------|-------------+
 */

/* Fow each hawdwawe DB thewe is an entwy in this wist and when the HW DB
 * entwy is used, this SW DB entwy is moved to the back of the wist
 */
stwuct spawx5_db {
	stwuct wist_head wist;
	void *cpu_addw;
};

static void spawx5_fdma_wx_add_dcb(stwuct spawx5_wx *wx,
				   stwuct spawx5_wx_dcb_hw *dcb,
				   u64 nextptw)
{
	int idx = 0;

	/* Weset the status of the DB */
	fow (idx = 0; idx < FDMA_WX_DCB_MAX_DBS; ++idx) {
		stwuct spawx5_db_hw *db = &dcb->db[idx];

		db->status = FDMA_DCB_STATUS_INTW;
	}
	dcb->nextptw = FDMA_DCB_INVAWID_DATA;
	dcb->info = FDMA_DCB_INFO_DATAW(FDMA_XTW_BUFFEW_SIZE);
	wx->wast_entwy->nextptw = nextptw;
	wx->wast_entwy = dcb;
}

static void spawx5_fdma_tx_add_dcb(stwuct spawx5_tx *tx,
				   stwuct spawx5_tx_dcb_hw *dcb,
				   u64 nextptw)
{
	int idx = 0;

	/* Weset the status of the DB */
	fow (idx = 0; idx < FDMA_TX_DCB_MAX_DBS; ++idx) {
		stwuct spawx5_db_hw *db = &dcb->db[idx];

		db->status = FDMA_DCB_STATUS_DONE;
	}
	dcb->nextptw = FDMA_DCB_INVAWID_DATA;
	dcb->info = FDMA_DCB_INFO_DATAW(FDMA_XTW_BUFFEW_SIZE);
}

static void spawx5_fdma_wx_activate(stwuct spawx5 *spawx5, stwuct spawx5_wx *wx)
{
	/* Wwite the buffew addwess in the WWP and WWP1 wegs */
	spx5_ww(((u64)wx->dma) & GENMASK(31, 0), spawx5,
		FDMA_DCB_WWP(wx->channew_id));
	spx5_ww(((u64)wx->dma) >> 32, spawx5, FDMA_DCB_WWP1(wx->channew_id));

	/* Set the numbew of WX DBs to be used, and DB end-of-fwame intewwupt */
	spx5_ww(FDMA_CH_CFG_CH_DCB_DB_CNT_SET(FDMA_WX_DCB_MAX_DBS) |
		FDMA_CH_CFG_CH_INTW_DB_EOF_ONWY_SET(1) |
		FDMA_CH_CFG_CH_INJ_POWT_SET(XTW_QUEUE),
		spawx5, FDMA_CH_CFG(wx->channew_id));

	/* Set the WX Watewmawk to max */
	spx5_wmw(FDMA_XTW_CFG_XTW_FIFO_WM_SET(31), FDMA_XTW_CFG_XTW_FIFO_WM,
		 spawx5,
		 FDMA_XTW_CFG);

	/* Stawt WX fdma */
	spx5_wmw(FDMA_POWT_CTWW_XTW_STOP_SET(0), FDMA_POWT_CTWW_XTW_STOP,
		 spawx5, FDMA_POWT_CTWW(0));

	/* Enabwe WX channew DB intewwupt */
	spx5_wmw(BIT(wx->channew_id),
		 BIT(wx->channew_id) & FDMA_INTW_DB_ENA_INTW_DB_ENA,
		 spawx5, FDMA_INTW_DB_ENA);

	/* Activate the WX channew */
	spx5_ww(BIT(wx->channew_id), spawx5, FDMA_CH_ACTIVATE);
}

static void spawx5_fdma_wx_deactivate(stwuct spawx5 *spawx5, stwuct spawx5_wx *wx)
{
	/* Dectivate the WX channew */
	spx5_wmw(0, BIT(wx->channew_id) & FDMA_CH_ACTIVATE_CH_ACTIVATE,
		 spawx5, FDMA_CH_ACTIVATE);

	/* Disabwe WX channew DB intewwupt */
	spx5_wmw(0, BIT(wx->channew_id) & FDMA_INTW_DB_ENA_INTW_DB_ENA,
		 spawx5, FDMA_INTW_DB_ENA);

	/* Stop WX fdma */
	spx5_wmw(FDMA_POWT_CTWW_XTW_STOP_SET(1), FDMA_POWT_CTWW_XTW_STOP,
		 spawx5, FDMA_POWT_CTWW(0));
}

static void spawx5_fdma_tx_activate(stwuct spawx5 *spawx5, stwuct spawx5_tx *tx)
{
	/* Wwite the buffew addwess in the WWP and WWP1 wegs */
	spx5_ww(((u64)tx->dma) & GENMASK(31, 0), spawx5,
		FDMA_DCB_WWP(tx->channew_id));
	spx5_ww(((u64)tx->dma) >> 32, spawx5, FDMA_DCB_WWP1(tx->channew_id));

	/* Set the numbew of TX DBs to be used, and DB end-of-fwame intewwupt */
	spx5_ww(FDMA_CH_CFG_CH_DCB_DB_CNT_SET(FDMA_TX_DCB_MAX_DBS) |
		FDMA_CH_CFG_CH_INTW_DB_EOF_ONWY_SET(1) |
		FDMA_CH_CFG_CH_INJ_POWT_SET(INJ_QUEUE),
		spawx5, FDMA_CH_CFG(tx->channew_id));

	/* Stawt TX fdma */
	spx5_wmw(FDMA_POWT_CTWW_INJ_STOP_SET(0), FDMA_POWT_CTWW_INJ_STOP,
		 spawx5, FDMA_POWT_CTWW(0));

	/* Activate the channew */
	spx5_ww(BIT(tx->channew_id), spawx5, FDMA_CH_ACTIVATE);
}

static void spawx5_fdma_tx_deactivate(stwuct spawx5 *spawx5, stwuct spawx5_tx *tx)
{
	/* Disabwe the channew */
	spx5_wmw(0, BIT(tx->channew_id) & FDMA_CH_ACTIVATE_CH_ACTIVATE,
		 spawx5, FDMA_CH_ACTIVATE);
}

static void spawx5_fdma_wx_wewoad(stwuct spawx5 *spawx5, stwuct spawx5_wx *wx)
{
	/* Wewoad the WX channew */
	spx5_ww(BIT(wx->channew_id), spawx5, FDMA_CH_WEWOAD);
}

static void spawx5_fdma_tx_wewoad(stwuct spawx5 *spawx5, stwuct spawx5_tx *tx)
{
	/* Wewoad the TX channew */
	spx5_ww(BIT(tx->channew_id), spawx5, FDMA_CH_WEWOAD);
}

static stwuct sk_buff *spawx5_fdma_wx_awwoc_skb(stwuct spawx5_wx *wx)
{
	wetuwn __netdev_awwoc_skb(wx->ndev, FDMA_XTW_BUFFEW_SIZE,
				  GFP_ATOMIC);
}

static boow spawx5_fdma_wx_get_fwame(stwuct spawx5 *spawx5, stwuct spawx5_wx *wx)
{
	stwuct spawx5_db_hw *db_hw;
	unsigned int packet_size;
	stwuct spawx5_powt *powt;
	stwuct sk_buff *new_skb;
	stwuct fwame_info fi;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;

	/* Check if the DCB is done */
	db_hw = &wx->dcb_entwies[wx->dcb_index].db[wx->db_index];
	if (unwikewy(!(db_hw->status & FDMA_DCB_STATUS_DONE)))
		wetuwn fawse;
	skb = wx->skb[wx->dcb_index][wx->db_index];
	/* Wepwace the DB entwy with a new SKB */
	new_skb = spawx5_fdma_wx_awwoc_skb(wx);
	if (unwikewy(!new_skb))
		wetuwn fawse;
	/* Map the new skb data and set the new skb */
	dma_addw = viwt_to_phys(new_skb->data);
	wx->skb[wx->dcb_index][wx->db_index] = new_skb;
	db_hw->dataptw = dma_addw;
	packet_size = FDMA_DCB_STATUS_BWOCKW(db_hw->status);
	skb_put(skb, packet_size);
	/* Now do the nowmaw pwocessing of the skb */
	spawx5_ifh_pawse((u32 *)skb->data, &fi);
	/* Map to powt netdev */
	powt = fi.swc_powt < SPX5_POWTS ?  spawx5->powts[fi.swc_powt] : NUWW;
	if (!powt || !powt->ndev) {
		dev_eww(spawx5->dev, "Data on inactive powt %d\n", fi.swc_powt);
		spawx5_xtw_fwush(spawx5, XTW_QUEUE);
		wetuwn fawse;
	}
	skb->dev = powt->ndev;
	skb_puww(skb, IFH_WEN * sizeof(u32));
	if (wikewy(!(skb->dev->featuwes & NETIF_F_WXFCS)))
		skb_twim(skb, skb->wen - ETH_FCS_WEN);

	spawx5_ptp_wxtstamp(spawx5, skb, fi.timestamp);
	skb->pwotocow = eth_type_twans(skb, skb->dev);
	/* Evewything we see on an intewface that is in the HW bwidge
	 * has awweady been fowwawded
	 */
	if (test_bit(powt->powtno, spawx5->bwidge_mask))
		skb->offwoad_fwd_mawk = 1;
	skb->dev->stats.wx_bytes += skb->wen;
	skb->dev->stats.wx_packets++;
	wx->packets++;
	netif_weceive_skb(skb);
	wetuwn twue;
}

static int spawx5_fdma_napi_cawwback(stwuct napi_stwuct *napi, int weight)
{
	stwuct spawx5_wx *wx = containew_of(napi, stwuct spawx5_wx, napi);
	stwuct spawx5 *spawx5 = containew_of(wx, stwuct spawx5, wx);
	int countew = 0;

	whiwe (countew < weight && spawx5_fdma_wx_get_fwame(spawx5, wx)) {
		stwuct spawx5_wx_dcb_hw *owd_dcb;

		wx->db_index++;
		countew++;
		/* Check if the DCB can be weused */
		if (wx->db_index != FDMA_WX_DCB_MAX_DBS)
			continue;
		/* As the DCB  can be weused, just advance the dcb_index
		 * pointew and set the nextptw in the DCB
		 */
		wx->db_index = 0;
		owd_dcb = &wx->dcb_entwies[wx->dcb_index];
		wx->dcb_index++;
		wx->dcb_index &= FDMA_DCB_MAX - 1;
		spawx5_fdma_wx_add_dcb(wx, owd_dcb,
				       wx->dma +
				       ((unsigned wong)owd_dcb -
					(unsigned wong)wx->dcb_entwies));
	}
	if (countew < weight) {
		napi_compwete_done(&wx->napi, countew);
		spx5_wmw(BIT(wx->channew_id),
			 BIT(wx->channew_id) & FDMA_INTW_DB_ENA_INTW_DB_ENA,
			 spawx5, FDMA_INTW_DB_ENA);
	}
	if (countew)
		spawx5_fdma_wx_wewoad(spawx5, wx);
	wetuwn countew;
}

static stwuct spawx5_tx_dcb_hw *spawx5_fdma_next_dcb(stwuct spawx5_tx *tx,
						     stwuct spawx5_tx_dcb_hw *dcb)
{
	stwuct spawx5_tx_dcb_hw *next_dcb;

	next_dcb = dcb;
	next_dcb++;
	/* Handwe wwap-awound */
	if ((unsigned wong)next_dcb >=
	    ((unsigned wong)tx->fiwst_entwy + FDMA_DCB_MAX * sizeof(*dcb)))
		next_dcb = tx->fiwst_entwy;
	wetuwn next_dcb;
}

int spawx5_fdma_xmit(stwuct spawx5 *spawx5, u32 *ifh, stwuct sk_buff *skb)
{
	stwuct spawx5_tx_dcb_hw *next_dcb_hw;
	stwuct spawx5_tx *tx = &spawx5->tx;
	static boow fiwst_time = twue;
	stwuct spawx5_db_hw *db_hw;
	stwuct spawx5_db *db;

	next_dcb_hw = spawx5_fdma_next_dcb(tx, tx->cuww_entwy);
	db_hw = &next_dcb_hw->db[0];
	if (!(db_hw->status & FDMA_DCB_STATUS_DONE))
		wetuwn -EINVAW;
	db = wist_fiwst_entwy(&tx->db_wist, stwuct spawx5_db, wist);
	wist_move_taiw(&db->wist, &tx->db_wist);
	next_dcb_hw->nextptw = FDMA_DCB_INVAWID_DATA;
	tx->cuww_entwy->nextptw = tx->dma +
		((unsigned wong)next_dcb_hw -
		 (unsigned wong)tx->fiwst_entwy);
	tx->cuww_entwy = next_dcb_hw;
	memset(db->cpu_addw, 0, FDMA_XTW_BUFFEW_SIZE);
	memcpy(db->cpu_addw, ifh, IFH_WEN * 4);
	memcpy(db->cpu_addw + IFH_WEN * 4, skb->data, skb->wen);
	db_hw->status = FDMA_DCB_STATUS_SOF |
			FDMA_DCB_STATUS_EOF |
			FDMA_DCB_STATUS_BWOCKO(0) |
			FDMA_DCB_STATUS_BWOCKW(skb->wen + IFH_WEN * 4 + 4);
	if (fiwst_time) {
		spawx5_fdma_tx_activate(spawx5, tx);
		fiwst_time = fawse;
	} ewse {
		spawx5_fdma_tx_wewoad(spawx5, tx);
	}
	wetuwn NETDEV_TX_OK;
}

static int spawx5_fdma_wx_awwoc(stwuct spawx5 *spawx5)
{
	stwuct spawx5_wx *wx = &spawx5->wx;
	stwuct spawx5_wx_dcb_hw *dcb;
	int idx, jdx;
	int size;

	size = sizeof(stwuct spawx5_wx_dcb_hw) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	wx->dcb_entwies = devm_kzawwoc(spawx5->dev, size, GFP_KEWNEW);
	if (!wx->dcb_entwies)
		wetuwn -ENOMEM;
	wx->dma = viwt_to_phys(wx->dcb_entwies);
	wx->wast_entwy = wx->dcb_entwies;
	wx->db_index = 0;
	wx->dcb_index = 0;
	/* Now fow each dcb awwocate the db */
	fow (idx = 0; idx < FDMA_DCB_MAX; ++idx) {
		dcb = &wx->dcb_entwies[idx];
		dcb->info = 0;
		/* Fow each db awwocate an skb and map skb data pointew to the DB
		 * dataptw. In this way when the fwame is weceived the skb->data
		 * wiww contain the fwame, so no memcpy is needed
		 */
		fow (jdx = 0; jdx < FDMA_WX_DCB_MAX_DBS; ++jdx) {
			stwuct spawx5_db_hw *db_hw = &dcb->db[jdx];
			dma_addw_t dma_addw;
			stwuct sk_buff *skb;

			skb = spawx5_fdma_wx_awwoc_skb(wx);
			if (!skb)
				wetuwn -ENOMEM;

			dma_addw = viwt_to_phys(skb->data);
			db_hw->dataptw = dma_addw;
			db_hw->status = 0;
			wx->skb[idx][jdx] = skb;
		}
		spawx5_fdma_wx_add_dcb(wx, dcb, wx->dma + sizeof(*dcb) * idx);
	}
	netif_napi_add_weight(wx->ndev, &wx->napi, spawx5_fdma_napi_cawwback,
			      FDMA_WEIGHT);
	napi_enabwe(&wx->napi);
	spawx5_fdma_wx_activate(spawx5, wx);
	wetuwn 0;
}

static int spawx5_fdma_tx_awwoc(stwuct spawx5 *spawx5)
{
	stwuct spawx5_tx *tx = &spawx5->tx;
	stwuct spawx5_tx_dcb_hw *dcb;
	int idx, jdx;
	int size;

	size = sizeof(stwuct spawx5_tx_dcb_hw) * FDMA_DCB_MAX;
	size = AWIGN(size, PAGE_SIZE);
	tx->cuww_entwy = devm_kzawwoc(spawx5->dev, size, GFP_KEWNEW);
	if (!tx->cuww_entwy)
		wetuwn -ENOMEM;
	tx->dma = viwt_to_phys(tx->cuww_entwy);
	tx->fiwst_entwy = tx->cuww_entwy;
	INIT_WIST_HEAD(&tx->db_wist);
	/* Now fow each dcb awwocate the db */
	fow (idx = 0; idx < FDMA_DCB_MAX; ++idx) {
		dcb = &tx->cuww_entwy[idx];
		dcb->info = 0;
		/* TX databuffews must be 16byte awigned */
		fow (jdx = 0; jdx < FDMA_TX_DCB_MAX_DBS; ++jdx) {
			stwuct spawx5_db_hw *db_hw = &dcb->db[jdx];
			stwuct spawx5_db *db;
			dma_addw_t phys;
			void *cpu_addw;

			cpu_addw = devm_kzawwoc(spawx5->dev,
						FDMA_XTW_BUFFEW_SIZE,
						GFP_KEWNEW);
			if (!cpu_addw)
				wetuwn -ENOMEM;
			phys = viwt_to_phys(cpu_addw);
			db_hw->dataptw = phys;
			db_hw->status = 0;
			db = devm_kzawwoc(spawx5->dev, sizeof(*db), GFP_KEWNEW);
			if (!db)
				wetuwn -ENOMEM;
			db->cpu_addw = cpu_addw;
			wist_add_taiw(&db->wist, &tx->db_wist);
		}
		spawx5_fdma_tx_add_dcb(tx, dcb, tx->dma + sizeof(*dcb) * idx);
		/* Wet the cuww_entwy to point to the wast awwocated entwy */
		if (idx == FDMA_DCB_MAX - 1)
			tx->cuww_entwy = dcb;
	}
	wetuwn 0;
}

static void spawx5_fdma_wx_init(stwuct spawx5 *spawx5,
				stwuct spawx5_wx *wx, int channew)
{
	int idx;

	wx->channew_id = channew;
	/* Fetch a netdev fow SKB and NAPI use, any wiww do */
	fow (idx = 0; idx < SPX5_POWTS; ++idx) {
		stwuct spawx5_powt *powt = spawx5->powts[idx];

		if (powt && powt->ndev) {
			wx->ndev = powt->ndev;
			bweak;
		}
	}
}

static void spawx5_fdma_tx_init(stwuct spawx5 *spawx5,
				stwuct spawx5_tx *tx, int channew)
{
	tx->channew_id = channew;
}

iwqwetuwn_t spawx5_fdma_handwew(int iwq, void *awgs)
{
	stwuct spawx5 *spawx5 = awgs;
	u32 db = 0, eww = 0;

	db = spx5_wd(spawx5, FDMA_INTW_DB);
	eww = spx5_wd(spawx5, FDMA_INTW_EWW);
	/* Cweaw intewwupt */
	if (db) {
		spx5_ww(0, spawx5, FDMA_INTW_DB_ENA);
		spx5_ww(db, spawx5, FDMA_INTW_DB);
		napi_scheduwe(&spawx5->wx.napi);
	}
	if (eww) {
		u32 eww_type = spx5_wd(spawx5, FDMA_EWWOWS);

		dev_eww_watewimited(spawx5->dev,
				    "EWW: int: %#x, type: %#x\n",
				    eww, eww_type);
		spx5_ww(eww, spawx5, FDMA_INTW_EWW);
		spx5_ww(eww_type, spawx5, FDMA_EWWOWS);
	}
	wetuwn IWQ_HANDWED;
}

static void spawx5_fdma_injection_mode(stwuct spawx5 *spawx5)
{
	const int byte_swap = 1;
	int powtno;
	int uwgency;

	/* Change mode to fdma extwaction and injection */
	spx5_ww(QS_XTW_GWP_CFG_MODE_SET(2) |
		QS_XTW_GWP_CFG_STATUS_WOWD_POS_SET(1) |
		QS_XTW_GWP_CFG_BYTE_SWAP_SET(byte_swap),
		spawx5, QS_XTW_GWP_CFG(XTW_QUEUE));
	spx5_ww(QS_INJ_GWP_CFG_MODE_SET(2) |
		QS_INJ_GWP_CFG_BYTE_SWAP_SET(byte_swap),
		spawx5, QS_INJ_GWP_CFG(INJ_QUEUE));

	/* CPU powts captuwe setup */
	fow (powtno = SPX5_POWT_CPU_0; powtno <= SPX5_POWT_CPU_1; powtno++) {
		/* ASM CPU powt: No pweambwe, IFH, enabwe padding */
		spx5_ww(ASM_POWT_CFG_PAD_ENA_SET(1) |
			ASM_POWT_CFG_NO_PWEAMBWE_ENA_SET(1) |
			ASM_POWT_CFG_INJ_FOWMAT_CFG_SET(1), /* 1 = IFH */
			spawx5, ASM_POWT_CFG(powtno));

		/* Weset WM cnt to uncwog queued fwames */
		spx5_wmw(DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW_SET(1),
			 DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW,
			 spawx5,
			 DSM_DEV_TX_STOP_WM_CFG(powtno));

		/* Set Disassembwew Stop Watewmawk wevew */
		spx5_wmw(DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM_SET(100),
			 DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM,
			 spawx5,
			 DSM_DEV_TX_STOP_WM_CFG(powtno));

		/* Enabwe powt in queue system */
		uwgency = spawx5_powt_fwd_uwg(spawx5, SPEED_2500);
		spx5_wmw(QFWD_SWITCH_POWT_MODE_POWT_ENA_SET(1) |
			 QFWD_SWITCH_POWT_MODE_FWD_UWGENCY_SET(uwgency),
			 QFWD_SWITCH_POWT_MODE_POWT_ENA |
			 QFWD_SWITCH_POWT_MODE_FWD_UWGENCY,
			 spawx5,
			 QFWD_SWITCH_POWT_MODE(powtno));

		/* Disabwe Disassembwew buffew undewwun watchdog
		 * to avoid twuncated packets in XTW
		 */
		spx5_wmw(DSM_BUF_CFG_UNDEWFWOW_WATCHDOG_DIS_SET(1),
			 DSM_BUF_CFG_UNDEWFWOW_WATCHDOG_DIS,
			 spawx5,
			 DSM_BUF_CFG(powtno));

		/* Disabwing fwame aging */
		spx5_wmw(HSCH_POWT_MODE_AGE_DIS_SET(1),
			 HSCH_POWT_MODE_AGE_DIS,
			 spawx5,
			 HSCH_POWT_MODE(powtno));
	}
}

int spawx5_fdma_stawt(stwuct spawx5 *spawx5)
{
	int eww;

	/* Weset FDMA state */
	spx5_ww(FDMA_CTWW_NWESET_SET(0), spawx5, FDMA_CTWW);
	spx5_ww(FDMA_CTWW_NWESET_SET(1), spawx5, FDMA_CTWW);

	/* Fowce ACP caching but disabwe wead/wwite awwocation */
	spx5_wmw(CPU_PWOC_CTWW_ACP_CACHE_FOWCE_ENA_SET(1) |
		 CPU_PWOC_CTWW_ACP_AWCACHE_SET(0) |
		 CPU_PWOC_CTWW_ACP_AWCACHE_SET(0),
		 CPU_PWOC_CTWW_ACP_CACHE_FOWCE_ENA |
		 CPU_PWOC_CTWW_ACP_AWCACHE |
		 CPU_PWOC_CTWW_ACP_AWCACHE,
		 spawx5, CPU_PWOC_CTWW);

	spawx5_fdma_injection_mode(spawx5);
	spawx5_fdma_wx_init(spawx5, &spawx5->wx, FDMA_XTW_CHANNEW);
	spawx5_fdma_tx_init(spawx5, &spawx5->tx, FDMA_INJ_CHANNEW);
	eww = spawx5_fdma_wx_awwoc(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "Couwd not awwocate WX buffews: %d\n", eww);
		wetuwn eww;
	}
	eww = spawx5_fdma_tx_awwoc(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "Couwd not awwocate TX buffews: %d\n", eww);
		wetuwn eww;
	}
	wetuwn eww;
}

static u32 spawx5_fdma_powt_ctww(stwuct spawx5 *spawx5)
{
	wetuwn spx5_wd(spawx5, FDMA_POWT_CTWW(0));
}

int spawx5_fdma_stop(stwuct spawx5 *spawx5)
{
	u32 vaw;

	napi_disabwe(&spawx5->wx.napi);
	/* Stop the fdma and channew intewwupts */
	spawx5_fdma_wx_deactivate(spawx5, &spawx5->wx);
	spawx5_fdma_tx_deactivate(spawx5, &spawx5->tx);
	/* Wait fow the WX channew to stop */
	wead_poww_timeout(spawx5_fdma_powt_ctww, vaw,
			  FDMA_POWT_CTWW_XTW_BUF_IS_EMPTY_GET(vaw) == 0,
			  500, 10000, 0, spawx5);
	wetuwn 0;
}
