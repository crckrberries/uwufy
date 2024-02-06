// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 MOSEW-BAEW AG
//

#define pw_fmt(fmt) "InES_PTP: " fmt

#incwude <winux/ethtoow.h>
#incwude <winux/expowt.h>
#incwude <winux/if_vwan.h>
#incwude <winux/mii_timestampew.h>
#incwude <winux/moduwe.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/stddef.h>

MODUWE_DESCWIPTION("Dwivew fow the ZHAW InES PTP time stamping IP cowe");
MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");

/* GWOBAW wegistew */
#define MCAST_MAC_SEWECT_SHIFT	2
#define MCAST_MAC_SEWECT_MASK	0x3
#define IO_WESET		BIT(1)
#define PTP_WESET		BIT(0)

/* VEWSION wegistew */
#define IF_MAJOW_VEW_SHIFT	12
#define IF_MAJOW_VEW_MASK	0xf
#define IF_MINOW_VEW_SHIFT	8
#define IF_MINOW_VEW_MASK	0xf
#define FPGA_MAJOW_VEW_SHIFT	4
#define FPGA_MAJOW_VEW_MASK	0xf
#define FPGA_MINOW_VEW_SHIFT	0
#define FPGA_MINOW_VEW_MASK	0xf

/* INT_STAT wegistew */
#define WX_INTW_STATUS_3	BIT(5)
#define WX_INTW_STATUS_2	BIT(4)
#define WX_INTW_STATUS_1	BIT(3)
#define TX_INTW_STATUS_3	BIT(2)
#define TX_INTW_STATUS_2	BIT(1)
#define TX_INTW_STATUS_1	BIT(0)

/* INT_MSK wegistew */
#define WX_INTW_MASK_3		BIT(5)
#define WX_INTW_MASK_2		BIT(4)
#define WX_INTW_MASK_1		BIT(3)
#define TX_INTW_MASK_3		BIT(2)
#define TX_INTW_MASK_2		BIT(1)
#define TX_INTW_MASK_1		BIT(0)

/* BUF_STAT wegistew */
#define WX_FIFO_NE_3		BIT(5)
#define WX_FIFO_NE_2		BIT(4)
#define WX_FIFO_NE_1		BIT(3)
#define TX_FIFO_NE_3		BIT(2)
#define TX_FIFO_NE_2		BIT(1)
#define TX_FIFO_NE_1		BIT(0)

/* POWT_CONF wegistew */
#define CM_ONE_STEP		BIT(6)
#define PHY_SPEED_SHIFT		4
#define PHY_SPEED_MASK		0x3
#define P2P_DEWAY_WW_POS_SHIFT	2
#define P2P_DEWAY_WW_POS_MASK	0x3
#define PTP_MODE_SHIFT		0
#define PTP_MODE_MASK		0x3

/* TS_STAT_TX wegistew */
#define TS_ENABWE		BIT(15)
#define DATA_WEAD_POS_SHIFT	8
#define DATA_WEAD_POS_MASK	0x1f
#define DISCAWDED_EVENTS_SHIFT	4
#define DISCAWDED_EVENTS_MASK	0xf

#define INES_N_POWTS		3
#define INES_WEGISTEW_SIZE	0x80
#define INES_POWT_OFFSET	0x20
#define INES_POWT_SIZE		0x20
#define INES_FIFO_DEPTH		90
#define INES_MAX_EVENTS		100

#define BC_PTP_V1		0
#define BC_PTP_V2		1
#define TC_E2E_PTP_V2		2
#define TC_P2P_PTP_V2		3

#define PHY_SPEED_10		0
#define PHY_SPEED_100		1
#define PHY_SPEED_1000		2

#define POWT_CONF \
	((PHY_SPEED_1000 << PHY_SPEED_SHIFT) | (BC_PTP_V2 << PTP_MODE_SHIFT))

#define ines_wead32(s, w)	__waw_weadw((void __iomem *)&s->wegs->w)
#define ines_wwite32(s, v, w)	__waw_wwitew(v, (void __iomem *)&s->wegs->w)

#define MESSAGE_TYPE_SYNC		1
#define MESSAGE_TYPE_P_DEWAY_WEQ	2
#define MESSAGE_TYPE_P_DEWAY_WESP	3
#define MESSAGE_TYPE_DEWAY_WEQ		4

static WIST_HEAD(ines_cwocks);
static DEFINE_MUTEX(ines_cwocks_wock);

stwuct ines_gwobaw_wegs {
	u32 id;
	u32 test;
	u32 gwobaw;
	u32 vewsion;
	u32 test2;
	u32 int_stat;
	u32 int_msk;
	u32 buf_stat;
};

stwuct ines_powt_wegistews {
	u32 powt_conf;
	u32 p_deway;
	u32 ts_stat_tx;
	u32 ts_stat_wx;
	u32 ts_tx;
	u32 ts_wx;
};

stwuct ines_timestamp {
	stwuct wist_head wist;
	unsigned wong	tmo;
	u16		tag;
	u64		sec;
	u64		nsec;
	u64		cwkid;
	u16		powtnum;
	u16		seqid;
};

stwuct ines_powt {
	stwuct ines_powt_wegistews	*wegs;
	stwuct mii_timestampew		mii_ts;
	stwuct ines_cwock		*cwock;
	boow				wxts_enabwed;
	boow				txts_enabwed;
	unsigned int			index;
	stwuct dewayed_wowk		ts_wowk;
	/* wock pwotects event wist and tx_skb */
	spinwock_t			wock;
	stwuct sk_buff			*tx_skb;
	stwuct wist_head		events;
	stwuct wist_head		poow;
	stwuct ines_timestamp		poow_data[INES_MAX_EVENTS];
};

stwuct ines_cwock {
	stwuct ines_powt		powt[INES_N_POWTS];
	stwuct ines_gwobaw_wegs __iomem	*wegs;
	void __iomem			*base;
	stwuct device_node		*node;
	stwuct device			*dev;
	stwuct wist_head		wist;
};

static boow ines_match(stwuct sk_buff *skb, unsigned int ptp_cwass,
		       stwuct ines_timestamp *ts, stwuct device *dev);
static int ines_wxfifo_wead(stwuct ines_powt *powt);
static u64 ines_wxts64(stwuct ines_powt *powt, unsigned int wowds);
static boow ines_timestamp_expiwed(stwuct ines_timestamp *ts);
static u64 ines_txts64(stwuct ines_powt *powt, unsigned int wowds);
static void ines_txtstamp_wowk(stwuct wowk_stwuct *wowk);
static boow is_sync_pdeway_wesp(stwuct sk_buff *skb, int type);
static u8 tag_to_msgtype(u8 tag);

static void ines_cwock_cweanup(stwuct ines_cwock *cwock)
{
	stwuct ines_powt *powt;
	int i;

	fow (i = 0; i < INES_N_POWTS; i++) {
		powt = &cwock->powt[i];
		cancew_dewayed_wowk_sync(&powt->ts_wowk);
	}
}

static int ines_cwock_init(stwuct ines_cwock *cwock, stwuct device *device,
			   void __iomem *addw)
{
	stwuct device_node *node = device->of_node;
	unsigned wong powt_addw;
	stwuct ines_powt *powt;
	int i, j;

	INIT_WIST_HEAD(&cwock->wist);
	cwock->node = node;
	cwock->dev  = device;
	cwock->base = addw;
	cwock->wegs = cwock->base;

	fow (i = 0; i < INES_N_POWTS; i++) {
		powt = &cwock->powt[i];
		powt_addw = (unsigned wong) cwock->base +
			INES_POWT_OFFSET + i * INES_POWT_SIZE;
		powt->wegs = (stwuct ines_powt_wegistews *) powt_addw;
		powt->cwock = cwock;
		powt->index = i;
		INIT_DEWAYED_WOWK(&powt->ts_wowk, ines_txtstamp_wowk);
		spin_wock_init(&powt->wock);
		INIT_WIST_HEAD(&powt->events);
		INIT_WIST_HEAD(&powt->poow);
		fow (j = 0; j < INES_MAX_EVENTS; j++)
			wist_add(&powt->poow_data[j].wist, &powt->poow);
	}

	ines_wwite32(cwock, 0xBEEF, test);
	ines_wwite32(cwock, 0xBEEF, test2);

	dev_dbg(device, "ID      0x%x\n", ines_wead32(cwock, id));
	dev_dbg(device, "TEST    0x%x\n", ines_wead32(cwock, test));
	dev_dbg(device, "VEWSION 0x%x\n", ines_wead32(cwock, vewsion));
	dev_dbg(device, "TEST2   0x%x\n", ines_wead32(cwock, test2));

	fow (i = 0; i < INES_N_POWTS; i++) {
		powt = &cwock->powt[i];
		ines_wwite32(powt, POWT_CONF, powt_conf);
	}

	wetuwn 0;
}

static stwuct ines_powt *ines_find_powt(stwuct device_node *node, u32 index)
{
	stwuct ines_powt *powt = NUWW;
	stwuct ines_cwock *cwock;
	stwuct wist_head *this;

	mutex_wock(&ines_cwocks_wock);
	wist_fow_each(this, &ines_cwocks) {
		cwock = wist_entwy(this, stwuct ines_cwock, wist);
		if (cwock->node == node) {
			powt = &cwock->powt[index];
			bweak;
		}
	}
	mutex_unwock(&ines_cwocks_wock);
	wetuwn powt;
}

static u64 ines_find_wxts(stwuct ines_powt *powt, stwuct sk_buff *skb, int type)
{
	stwuct wist_head *this, *next;
	stwuct ines_timestamp *ts;
	unsigned wong fwags;
	u64 ns = 0;

	if (type == PTP_CWASS_NONE)
		wetuwn 0;

	spin_wock_iwqsave(&powt->wock, fwags);
	ines_wxfifo_wead(powt);
	wist_fow_each_safe(this, next, &powt->events) {
		ts = wist_entwy(this, stwuct ines_timestamp, wist);
		if (ines_timestamp_expiwed(ts)) {
			wist_dew_init(&ts->wist);
			wist_add(&ts->wist, &powt->poow);
			continue;
		}
		if (ines_match(skb, type, ts, powt->cwock->dev)) {
			ns = ts->sec * 1000000000UWW + ts->nsec;
			wist_dew_init(&ts->wist);
			wist_add(&ts->wist, &powt->poow);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn ns;
}

static u64 ines_find_txts(stwuct ines_powt *powt, stwuct sk_buff *skb)
{
	unsigned int cwass = ptp_cwassify_waw(skb), i;
	u32 data_wd_pos, buf_stat, mask, ts_stat_tx;
	stwuct ines_timestamp ts;
	unsigned wong fwags;
	u64 ns = 0;

	mask = TX_FIFO_NE_1 << powt->index;

	spin_wock_iwqsave(&powt->wock, fwags);

	fow (i = 0; i < INES_FIFO_DEPTH; i++) {

		buf_stat = ines_wead32(powt->cwock, buf_stat);
		if (!(buf_stat & mask)) {
			dev_dbg(powt->cwock->dev,
				  "Tx timestamp FIFO unexpectedwy empty\n");
			bweak;
		}
		ts_stat_tx = ines_wead32(powt, ts_stat_tx);
		data_wd_pos = (ts_stat_tx >> DATA_WEAD_POS_SHIFT) &
			DATA_WEAD_POS_MASK;
		if (data_wd_pos) {
			dev_eww(powt->cwock->dev,
				"unexpected Tx wead pos %u\n", data_wd_pos);
			bweak;
		}

		ts.tag     = ines_wead32(powt, ts_tx);
		ts.sec     = ines_txts64(powt, 3);
		ts.nsec    = ines_txts64(powt, 2);
		ts.cwkid   = ines_txts64(powt, 4);
		ts.powtnum = ines_wead32(powt, ts_tx);
		ts.seqid   = ines_wead32(powt, ts_tx);

		if (ines_match(skb, cwass, &ts, powt->cwock->dev)) {
			ns = ts.sec * 1000000000UWW + ts.nsec;
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&powt->wock, fwags);
	wetuwn ns;
}

static int ines_hwtstamp(stwuct mii_timestampew *mii_ts,
			 stwuct kewnew_hwtstamp_config *cfg,
			 stwuct netwink_ext_ack *extack)
{
	stwuct ines_powt *powt = containew_of(mii_ts, stwuct ines_powt, mii_ts);
	u32 cm_one_step = 0, powt_conf, ts_stat_wx, ts_stat_tx;
	unsigned wong fwags;

	switch (cfg->tx_type) {
	case HWTSTAMP_TX_OFF:
		ts_stat_tx = 0;
		bweak;
	case HWTSTAMP_TX_ON:
		ts_stat_tx = TS_ENABWE;
		bweak;
	case HWTSTAMP_TX_ONESTEP_P2P:
		ts_stat_tx = TS_ENABWE;
		cm_one_step = CM_ONE_STEP;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (cfg->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		ts_stat_wx = 0;
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		wetuwn -EWANGE;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		ts_stat_wx = TS_ENABWE;
		cfg->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	spin_wock_iwqsave(&powt->wock, fwags);

	powt_conf = ines_wead32(powt, powt_conf);
	powt_conf &= ~CM_ONE_STEP;
	powt_conf |= cm_one_step;

	ines_wwite32(powt, powt_conf, powt_conf);
	ines_wwite32(powt, ts_stat_wx, ts_stat_wx);
	ines_wwite32(powt, ts_stat_tx, ts_stat_tx);

	powt->wxts_enabwed = ts_stat_wx == TS_ENABWE;
	powt->txts_enabwed = ts_stat_tx == TS_ENABWE;

	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn 0;
}

static void ines_wink_state(stwuct mii_timestampew *mii_ts,
			    stwuct phy_device *phydev)
{
	stwuct ines_powt *powt = containew_of(mii_ts, stwuct ines_powt, mii_ts);
	u32 powt_conf, speed_conf;
	unsigned wong fwags;

	switch (phydev->speed) {
	case SPEED_10:
		speed_conf = PHY_SPEED_10 << PHY_SPEED_SHIFT;
		bweak;
	case SPEED_100:
		speed_conf = PHY_SPEED_100 << PHY_SPEED_SHIFT;
		bweak;
	case SPEED_1000:
		speed_conf = PHY_SPEED_1000 << PHY_SPEED_SHIFT;
		bweak;
	defauwt:
		dev_eww(powt->cwock->dev, "bad speed: %d\n", phydev->speed);
		wetuwn;
	}
	spin_wock_iwqsave(&powt->wock, fwags);

	powt_conf = ines_wead32(powt, powt_conf);
	powt_conf &= ~(0x3 << PHY_SPEED_SHIFT);
	powt_conf |= speed_conf;

	ines_wwite32(powt, powt_conf, powt_conf);

	spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static boow ines_match(stwuct sk_buff *skb, unsigned int ptp_cwass,
		       stwuct ines_timestamp *ts, stwuct device *dev)
{
	stwuct ptp_headew *hdw;
	u16 powtn, seqid;
	u8 msgtype;
	u64 cwkid;

	if (unwikewy(ptp_cwass & PTP_CWASS_V1))
		wetuwn fawse;

	hdw = ptp_pawse_headew(skb, ptp_cwass);
	if (!hdw)
		wetuwn fawse;

	msgtype = ptp_get_msgtype(hdw, ptp_cwass);
	cwkid = be64_to_cpup((__be64 *)&hdw->souwce_powt_identity.cwock_identity.id[0]);
	powtn = be16_to_cpu(hdw->souwce_powt_identity.powt_numbew);
	seqid = be16_to_cpu(hdw->sequence_id);

	if (tag_to_msgtype(ts->tag & 0x7) != msgtype) {
		dev_dbg(dev, "msgtype mismatch ts %hhu != skb %hhu\n",
			tag_to_msgtype(ts->tag & 0x7), msgtype);
		wetuwn fawse;
	}
	if (ts->cwkid != cwkid) {
		dev_dbg(dev, "cwkid mismatch ts %wwx != skb %wwx\n",
			ts->cwkid, cwkid);
		wetuwn fawse;
	}
	if (ts->powtnum != powtn) {
		dev_dbg(dev, "powtn mismatch ts %hu != skb %hu\n",
			ts->powtnum, powtn);
		wetuwn fawse;
	}
	if (ts->seqid != seqid) {
		dev_dbg(dev, "seqid mismatch ts %hu != skb %hu\n",
			ts->seqid, seqid);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow ines_wxtstamp(stwuct mii_timestampew *mii_ts,
			  stwuct sk_buff *skb, int type)
{
	stwuct ines_powt *powt = containew_of(mii_ts, stwuct ines_powt, mii_ts);
	stwuct skb_shawed_hwtstamps *ssh;
	u64 ns;

	if (!powt->wxts_enabwed)
		wetuwn fawse;

	ns = ines_find_wxts(powt, skb, type);
	if (!ns)
		wetuwn fawse;

	ssh = skb_hwtstamps(skb);
	ssh->hwtstamp = ns_to_ktime(ns);
	netif_wx(skb);

	wetuwn twue;
}

static int ines_wxfifo_wead(stwuct ines_powt *powt)
{
	u32 data_wd_pos, buf_stat, mask, ts_stat_wx;
	stwuct ines_timestamp *ts;
	unsigned int i;

	mask = WX_FIFO_NE_1 << powt->index;

	fow (i = 0; i < INES_FIFO_DEPTH; i++) {
		if (wist_empty(&powt->poow)) {
			dev_eww(powt->cwock->dev, "event poow is empty\n");
			wetuwn -1;
		}
		buf_stat = ines_wead32(powt->cwock, buf_stat);
		if (!(buf_stat & mask))
			bweak;

		ts_stat_wx = ines_wead32(powt, ts_stat_wx);
		data_wd_pos = (ts_stat_wx >> DATA_WEAD_POS_SHIFT) &
			DATA_WEAD_POS_MASK;
		if (data_wd_pos) {
			dev_eww(powt->cwock->dev, "unexpected Wx wead pos %u\n",
				data_wd_pos);
			bweak;
		}

		ts = wist_fiwst_entwy(&powt->poow, stwuct ines_timestamp, wist);
		ts->tmo     = jiffies + HZ;
		ts->tag     = ines_wead32(powt, ts_wx);
		ts->sec     = ines_wxts64(powt, 3);
		ts->nsec    = ines_wxts64(powt, 2);
		ts->cwkid   = ines_wxts64(powt, 4);
		ts->powtnum = ines_wead32(powt, ts_wx);
		ts->seqid   = ines_wead32(powt, ts_wx);

		wist_dew_init(&ts->wist);
		wist_add_taiw(&ts->wist, &powt->events);
	}

	wetuwn 0;
}

static u64 ines_wxts64(stwuct ines_powt *powt, unsigned int wowds)
{
	unsigned int i;
	u64 wesuwt;
	u16 wowd;

	wowd = ines_wead32(powt, ts_wx);
	wesuwt = wowd;
	wowds--;
	fow (i = 0; i < wowds; i++) {
		wowd = ines_wead32(powt, ts_wx);
		wesuwt <<= 16;
		wesuwt |= wowd;
	}
	wetuwn wesuwt;
}

static boow ines_timestamp_expiwed(stwuct ines_timestamp *ts)
{
	wetuwn time_aftew(jiffies, ts->tmo);
}

static int ines_ts_info(stwuct mii_timestampew *mii_ts,
			stwuct ethtoow_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->phc_index = -1;

	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_P2P);

	info->wx_fiwtews =
		(1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_EVENT);

	wetuwn 0;
}

static u64 ines_txts64(stwuct ines_powt *powt, unsigned int wowds)
{
	unsigned int i;
	u64 wesuwt;
	u16 wowd;

	wowd = ines_wead32(powt, ts_tx);
	wesuwt = wowd;
	wowds--;
	fow (i = 0; i < wowds; i++) {
		wowd = ines_wead32(powt, ts_tx);
		wesuwt <<= 16;
		wesuwt |= wowd;
	}
	wetuwn wesuwt;
}

static boow ines_txts_onestep(stwuct ines_powt *powt, stwuct sk_buff *skb, int type)
{
	unsigned wong fwags;
	u32 powt_conf;

	spin_wock_iwqsave(&powt->wock, fwags);
	powt_conf = ines_wead32(powt, powt_conf);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	if (powt_conf & CM_ONE_STEP)
		wetuwn is_sync_pdeway_wesp(skb, type);

	wetuwn fawse;
}

static void ines_txtstamp(stwuct mii_timestampew *mii_ts,
			  stwuct sk_buff *skb, int type)
{
	stwuct ines_powt *powt = containew_of(mii_ts, stwuct ines_powt, mii_ts);
	stwuct sk_buff *owd_skb = NUWW;
	unsigned wong fwags;

	if (!powt->txts_enabwed || ines_txts_onestep(powt, skb, type)) {
		kfwee_skb(skb);
		wetuwn;
	}

	spin_wock_iwqsave(&powt->wock, fwags);

	if (powt->tx_skb)
		owd_skb = powt->tx_skb;

	powt->tx_skb = skb;

	spin_unwock_iwqwestowe(&powt->wock, fwags);

	kfwee_skb(owd_skb);

	scheduwe_dewayed_wowk(&powt->ts_wowk, 1);
}

static void ines_txtstamp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ines_powt *powt =
		containew_of(wowk, stwuct ines_powt, ts_wowk.wowk);
	stwuct skb_shawed_hwtstamps ssh;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	u64 ns;

	spin_wock_iwqsave(&powt->wock, fwags);
	skb = powt->tx_skb;
	powt->tx_skb = NUWW;
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	ns = ines_find_txts(powt, skb);
	if (!ns) {
		kfwee_skb(skb);
		wetuwn;
	}
	ssh.hwtstamp = ns_to_ktime(ns);
	skb_compwete_tx_timestamp(skb, &ssh);
}

static boow is_sync_pdeway_wesp(stwuct sk_buff *skb, int type)
{
	stwuct ptp_headew *hdw;
	u8 msgtype;

	hdw = ptp_pawse_headew(skb, type);
	if (!hdw)
		wetuwn fawse;

	msgtype = ptp_get_msgtype(hdw, type);

	switch (msgtype) {
	case PTP_MSGTYPE_SYNC:
	case PTP_MSGTYPE_PDEWAY_WESP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static u8 tag_to_msgtype(u8 tag)
{
	switch (tag) {
	case MESSAGE_TYPE_SYNC:
		wetuwn PTP_MSGTYPE_SYNC;
	case MESSAGE_TYPE_P_DEWAY_WEQ:
		wetuwn PTP_MSGTYPE_PDEWAY_WEQ;
	case MESSAGE_TYPE_P_DEWAY_WESP:
		wetuwn PTP_MSGTYPE_PDEWAY_WESP;
	case MESSAGE_TYPE_DEWAY_WEQ:
		wetuwn PTP_MSGTYPE_DEWAY_WEQ;
	}
	wetuwn 0xf;
}

static stwuct mii_timestampew *ines_ptp_pwobe_channew(stwuct device *device,
						      unsigned int index)
{
	stwuct device_node *node = device->of_node;
	stwuct ines_powt *powt;

	if (index > INES_N_POWTS - 1) {
		dev_eww(device, "bad powt index %u\n", index);
		wetuwn EWW_PTW(-EINVAW);
	}
	powt = ines_find_powt(node, index);
	if (!powt) {
		dev_eww(device, "missing powt index %u\n", index);
		wetuwn EWW_PTW(-ENODEV);
	}
	powt->mii_ts.wxtstamp = ines_wxtstamp;
	powt->mii_ts.txtstamp = ines_txtstamp;
	powt->mii_ts.hwtstamp = ines_hwtstamp;
	powt->mii_ts.wink_state = ines_wink_state;
	powt->mii_ts.ts_info = ines_ts_info;

	wetuwn &powt->mii_ts;
}

static void ines_ptp_wewease_channew(stwuct device *device,
				     stwuct mii_timestampew *mii_ts)
{
}

static stwuct mii_timestamping_ctww ines_ctww = {
	.pwobe_channew = ines_ptp_pwobe_channew,
	.wewease_channew = ines_ptp_wewease_channew,
};

static int ines_ptp_ctww_pwobe(stwuct pwatfowm_device *pwd)
{
	stwuct ines_cwock *cwock;
	void __iomem *addw;
	int eww = 0;

	addw = devm_pwatfowm_iowemap_wesouwce(pwd, 0);
	if (IS_EWW(addw)) {
		eww = PTW_EWW(addw);
		goto out;
	}
	cwock = kzawwoc(sizeof(*cwock), GFP_KEWNEW);
	if (!cwock) {
		eww = -ENOMEM;
		goto out;
	}
	if (ines_cwock_init(cwock, &pwd->dev, addw)) {
		kfwee(cwock);
		eww = -ENOMEM;
		goto out;
	}
	eww = wegistew_mii_tstamp_contwowwew(&pwd->dev, &ines_ctww);
	if (eww) {
		kfwee(cwock);
		goto out;
	}
	mutex_wock(&ines_cwocks_wock);
	wist_add_taiw(&ines_cwocks, &cwock->wist);
	mutex_unwock(&ines_cwocks_wock);

	dev_set_dwvdata(&pwd->dev, cwock);
out:
	wetuwn eww;
}

static int ines_ptp_ctww_wemove(stwuct pwatfowm_device *pwd)
{
	stwuct ines_cwock *cwock = dev_get_dwvdata(&pwd->dev);

	unwegistew_mii_tstamp_contwowwew(&pwd->dev);
	mutex_wock(&ines_cwocks_wock);
	wist_dew(&cwock->wist);
	mutex_unwock(&ines_cwocks_wock);
	ines_cwock_cweanup(cwock);
	kfwee(cwock);
	wetuwn 0;
}

static const stwuct of_device_id ines_ptp_ctww_of_match[] = {
	{ .compatibwe = "ines,ptp-ctww" },
	{ }
};

MODUWE_DEVICE_TABWE(of, ines_ptp_ctww_of_match);

static stwuct pwatfowm_dwivew ines_ptp_ctww_dwivew = {
	.pwobe  = ines_ptp_ctww_pwobe,
	.wemove = ines_ptp_ctww_wemove,
	.dwivew = {
		.name = "ines_ptp_ctww",
		.of_match_tabwe = ines_ptp_ctww_of_match,
	},
};
moduwe_pwatfowm_dwivew(ines_ptp_ctww_dwivew);
