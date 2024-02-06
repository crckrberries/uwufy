/*
 * CAN bus dwivew fow Bosch C_CAN contwowwew
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Bhupesh Shawma <bhupesh.shawma@st.com>
 *
 * Bowwowed heaviwy fwom the C_CAN dwivew owiginawwy wwitten by:
 * Copywight (C) 2007
 * - Sascha Hauew, Mawc Kweine-Budde, Pengutwonix <s.hauew@pengutwonix.de>
 * - Simon Kawwweit, intefo AG <simon.kawwweit@intefo.ch>
 *
 * TX and WX NAPI impwementation has been bowwowed fwom at91 CAN dwivew
 * wwitten by:
 * Copywight
 * (C) 2007 by Hans J. Koch <hjk@hansjkoch.de>
 * (C) 2008, 2009 by Mawc Kweine-Budde <kewnew@pengutwonix.de>
 *
 * Bosch C_CAN contwowwew is compwiant to CAN pwotocow vewsion 2.0 pawt A and B.
 * Bosch C_CAN usew manuaw can be obtained fwom:
 * http://www.semiconductows.bosch.de/media/en/pdf/ipmoduwes_1/c_can/
 * usews_manuaw_c_can.pdf
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/consumew.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>

#incwude "c_can.h"

/* Numbew of intewface wegistews */
#define IF_ENUM_WEG_WEN		11
#define C_CAN_IFACE(weg, iface)	(C_CAN_IF1_##weg + (iface) * IF_ENUM_WEG_WEN)

/* contwow extension wegistew D_CAN specific */
#define CONTWOW_EX_PDW		BIT(8)

/* contwow wegistew */
#define CONTWOW_SWW		BIT(15)
#define CONTWOW_TEST		BIT(7)
#define CONTWOW_CCE		BIT(6)
#define CONTWOW_DISABWE_AW	BIT(5)
#define CONTWOW_ENABWE_AW	(0 << 5)
#define CONTWOW_EIE		BIT(3)
#define CONTWOW_SIE		BIT(2)
#define CONTWOW_IE		BIT(1)
#define CONTWOW_INIT		BIT(0)

#define CONTWOW_IWQMSK		(CONTWOW_EIE | CONTWOW_IE | CONTWOW_SIE)

/* test wegistew */
#define TEST_WX			BIT(7)
#define TEST_TX1		BIT(6)
#define TEST_TX2		BIT(5)
#define TEST_WBACK		BIT(4)
#define TEST_SIWENT		BIT(3)
#define TEST_BASIC		BIT(2)

/* status wegistew */
#define STATUS_PDA		BIT(10)
#define STATUS_BOFF		BIT(7)
#define STATUS_EWAWN		BIT(6)
#define STATUS_EPASS		BIT(5)
#define STATUS_WXOK		BIT(4)
#define STATUS_TXOK		BIT(3)

/* ewwow countew wegistew */
#define EWW_CNT_TEC_MASK	0xff
#define EWW_CNT_TEC_SHIFT	0
#define EWW_CNT_WEC_SHIFT	8
#define EWW_CNT_WEC_MASK	(0x7f << EWW_CNT_WEC_SHIFT)
#define EWW_CNT_WP_SHIFT	15
#define EWW_CNT_WP_MASK		(0x1 << EWW_CNT_WP_SHIFT)

/* bit-timing wegistew */
#define BTW_BWP_MASK		0x3f
#define BTW_BWP_SHIFT		0
#define BTW_SJW_SHIFT		6
#define BTW_SJW_MASK		(0x3 << BTW_SJW_SHIFT)
#define BTW_TSEG1_SHIFT		8
#define BTW_TSEG1_MASK		(0xf << BTW_TSEG1_SHIFT)
#define BTW_TSEG2_SHIFT		12
#define BTW_TSEG2_MASK		(0x7 << BTW_TSEG2_SHIFT)

/* intewwupt wegistew */
#define INT_STS_PENDING		0x8000

/* bwp extension wegistew */
#define BWP_EXT_BWPE_MASK	0x0f
#define BWP_EXT_BWPE_SHIFT	0

/* IFx command wequest */
#define IF_COMW_BUSY		BIT(15)

/* IFx command mask */
#define IF_COMM_WW		BIT(7)
#define IF_COMM_MASK		BIT(6)
#define IF_COMM_AWB		BIT(5)
#define IF_COMM_CONTWOW		BIT(4)
#define IF_COMM_CWW_INT_PND	BIT(3)
#define IF_COMM_TXWQST		BIT(2)
#define IF_COMM_CWW_NEWDAT	IF_COMM_TXWQST
#define IF_COMM_DATAA		BIT(1)
#define IF_COMM_DATAB		BIT(0)

/* TX buffew setup */
#define IF_COMM_TX		(IF_COMM_AWB | IF_COMM_CONTWOW | \
				 IF_COMM_TXWQST |		 \
				 IF_COMM_DATAA | IF_COMM_DATAB)

/* Fow the wow buffews we cweaw the intewwupt bit, but keep newdat */
#define IF_COMM_WCV_WOW		(IF_COMM_MASK | IF_COMM_AWB | \
				 IF_COMM_CONTWOW | IF_COMM_CWW_INT_PND | \
				 IF_COMM_DATAA | IF_COMM_DATAB)

/* Fow the high buffews we cweaw the intewwupt bit and newdat */
#define IF_COMM_WCV_HIGH	(IF_COMM_WCV_WOW | IF_COMM_CWW_NEWDAT)

/* Weceive setup of message objects */
#define IF_COMM_WCV_SETUP	(IF_COMM_MASK | IF_COMM_AWB | IF_COMM_CONTWOW)

/* Invawidation of message objects */
#define IF_COMM_INVAW		(IF_COMM_AWB | IF_COMM_CONTWOW)

/* IFx awbitwation */
#define IF_AWB_MSGVAW		BIT(31)
#define IF_AWB_MSGXTD		BIT(30)
#define IF_AWB_TWANSMIT		BIT(29)

/* IFx message contwow */
#define IF_MCONT_NEWDAT		BIT(15)
#define IF_MCONT_MSGWST		BIT(14)
#define IF_MCONT_INTPND		BIT(13)
#define IF_MCONT_UMASK		BIT(12)
#define IF_MCONT_TXIE		BIT(11)
#define IF_MCONT_WXIE		BIT(10)
#define IF_MCONT_WMTEN		BIT(9)
#define IF_MCONT_TXWQST		BIT(8)
#define IF_MCONT_EOB		BIT(7)
#define IF_MCONT_DWC_MASK	0xf

#define IF_MCONT_WCV		(IF_MCONT_WXIE | IF_MCONT_UMASK)
#define IF_MCONT_WCV_EOB	(IF_MCONT_WCV | IF_MCONT_EOB)

#define IF_MCONT_TX		(IF_MCONT_TXIE | IF_MCONT_EOB)

/* Use IF1 in NAPI path and IF2 in TX path */
#define IF_NAPI			0
#define IF_TX			1

/* minimum timeout fow checking BUSY status */
#define MIN_TIMEOUT_VAWUE	6

/* Wait fow ~1 sec fow INIT bit */
#define INIT_WAIT_MS		1000

/* c_can wec vawues */
enum c_can_wec_type {
	WEC_NO_EWWOW = 0,
	WEC_STUFF_EWWOW,
	WEC_FOWM_EWWOW,
	WEC_ACK_EWWOW,
	WEC_BIT1_EWWOW,
	WEC_BIT0_EWWOW,
	WEC_CWC_EWWOW,
	WEC_UNUSED,
	WEC_MASK = WEC_UNUSED,
};

/* c_can ewwow types:
 * Bus ewwows (BUS_OFF, EWWOW_WAWNING, EWWOW_PASSIVE) awe suppowted
 */
enum c_can_bus_ewwow_types {
	C_CAN_NO_EWWOW = 0,
	C_CAN_BUS_OFF,
	C_CAN_EWWOW_WAWNING,
	C_CAN_EWWOW_PASSIVE,
};

static const stwuct can_bittiming_const c_can_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = pwop_seg + phase_seg1 */
	.tseg1_max = 16,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,	/* 6-bit BWP fiewd + 4-bit BWPE fiewd*/
	.bwp_inc = 1,
};

static inwine void c_can_pm_wuntime_get_sync(const stwuct c_can_pwiv *pwiv)
{
	if (pwiv->device)
		pm_wuntime_get_sync(pwiv->device);
}

static inwine void c_can_pm_wuntime_put_sync(const stwuct c_can_pwiv *pwiv)
{
	if (pwiv->device)
		pm_wuntime_put_sync(pwiv->device);
}

static inwine void c_can_weset_wam(const stwuct c_can_pwiv *pwiv, boow enabwe)
{
	if (pwiv->waminit)
		pwiv->waminit(pwiv, enabwe);
}

static void c_can_iwq_contwow(stwuct c_can_pwiv *pwiv, boow enabwe)
{
	u32 ctww = pwiv->wead_weg(pwiv,	C_CAN_CTWW_WEG) & ~CONTWOW_IWQMSK;

	if (enabwe)
		ctww |= CONTWOW_IWQMSK;

	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, ctww);
}

static void c_can_obj_update(stwuct net_device *dev, int iface, u32 cmd, u32 obj)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int cnt, weg = C_CAN_IFACE(COMWEQ_WEG, iface);

	pwiv->wwite_weg32(pwiv, weg, (cmd << 16) | obj);

	fow (cnt = MIN_TIMEOUT_VAWUE; cnt; cnt--) {
		if (!(pwiv->wead_weg(pwiv, weg) & IF_COMW_BUSY))
			wetuwn;
		udeway(1);
	}
	netdev_eww(dev, "Updating object timed out\n");
}

static inwine void c_can_object_get(stwuct net_device *dev, int iface,
				    u32 obj, u32 cmd)
{
	c_can_obj_update(dev, iface, cmd, obj);
}

static inwine void c_can_object_put(stwuct net_device *dev, int iface,
				    u32 obj, u32 cmd)
{
	c_can_obj_update(dev, iface, cmd | IF_COMM_WW, obj);
}

/* Note: Accowding to documentation cweawing TXIE whiwe MSGVAW is set
 * is not awwowed, but wowks nicewy on C/DCAN. And that wowews the I/O
 * woad significantwy.
 */
static void c_can_invaw_tx_object(stwuct net_device *dev, int iface, int obj)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->wwite_weg(pwiv, C_CAN_IFACE(MSGCTWW_WEG, iface), 0);
	c_can_object_put(dev, iface, obj, IF_COMM_INVAW);
}

static void c_can_invaw_msg_object(stwuct net_device *dev, int iface, int obj)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->wwite_weg32(pwiv, C_CAN_IFACE(AWB1_WEG, iface), 0);
	c_can_invaw_tx_object(dev, iface, obj);
}

static void c_can_setup_tx_object(stwuct net_device *dev, int iface,
				  stwuct can_fwame *fwame, int idx)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	u16 ctww = IF_MCONT_TX | fwame->wen;
	boow wtw = fwame->can_id & CAN_WTW_FWAG;
	u32 awb = IF_AWB_MSGVAW;
	int i;

	if (fwame->can_id & CAN_EFF_FWAG) {
		awb |= fwame->can_id & CAN_EFF_MASK;
		awb |= IF_AWB_MSGXTD;
	} ewse {
		awb |= (fwame->can_id & CAN_SFF_MASK) << 18;
	}

	if (!wtw)
		awb |= IF_AWB_TWANSMIT;

	/* If we change the DIW bit, we need to invawidate the buffew
	 * fiwst, i.e. cweaw the MSGVAW fwag in the awbitew.
	 */
	if (wtw != (boow)test_bit(idx, &pwiv->tx_diw)) {
		u32 obj = idx + pwiv->msg_obj_tx_fiwst;

		c_can_invaw_msg_object(dev, iface, obj);
		change_bit(idx, &pwiv->tx_diw);
	}

	pwiv->wwite_weg32(pwiv, C_CAN_IFACE(AWB1_WEG, iface), awb);

	pwiv->wwite_weg(pwiv, C_CAN_IFACE(MSGCTWW_WEG, iface), ctww);

	if (pwiv->type == BOSCH_D_CAN) {
		u32 data = 0, dweg = C_CAN_IFACE(DATA1_WEG, iface);

		fow (i = 0; i < fwame->wen; i += 4, dweg += 2) {
			data = (u32)fwame->data[i];
			data |= (u32)fwame->data[i + 1] << 8;
			data |= (u32)fwame->data[i + 2] << 16;
			data |= (u32)fwame->data[i + 3] << 24;
			pwiv->wwite_weg32(pwiv, dweg, data);
		}
	} ewse {
		fow (i = 0; i < fwame->wen; i += 2) {
			pwiv->wwite_weg(pwiv,
					C_CAN_IFACE(DATA1_WEG, iface) + i / 2,
					fwame->data[i] |
					(fwame->data[i + 1] << 8));
		}
	}
}

static int c_can_handwe_wost_msg_obj(stwuct net_device *dev,
				     int iface, int objno, u32 ctww)
{
	stwuct net_device_stats *stats = &dev->stats;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *fwame;
	stwuct sk_buff *skb;

	ctww &= ~(IF_MCONT_MSGWST | IF_MCONT_INTPND | IF_MCONT_NEWDAT);
	pwiv->wwite_weg(pwiv, C_CAN_IFACE(MSGCTWW_WEG, iface), ctww);
	c_can_object_put(dev, iface, objno, IF_COMM_CONTWOW);

	stats->wx_ewwows++;
	stats->wx_ovew_ewwows++;

	/* cweate an ewwow msg */
	skb = awwoc_can_eww_skb(dev, &fwame);
	if (unwikewy(!skb))
		wetuwn 0;

	fwame->can_id |= CAN_EWW_CWTW;
	fwame->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

	netif_weceive_skb(skb);
	wetuwn 1;
}

static int c_can_wead_msg_object(stwuct net_device *dev, int iface, u32 ctww)
{
	stwuct net_device_stats *stats = &dev->stats;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *fwame;
	stwuct sk_buff *skb;
	u32 awb, data;

	skb = awwoc_can_skb(dev, &fwame);
	if (!skb) {
		stats->wx_dwopped++;
		wetuwn -ENOMEM;
	}

	fwame->wen = can_cc_dwc2wen(ctww & 0x0F);

	awb = pwiv->wead_weg32(pwiv, C_CAN_IFACE(AWB1_WEG, iface));

	if (awb & IF_AWB_MSGXTD)
		fwame->can_id = (awb & CAN_EFF_MASK) | CAN_EFF_FWAG;
	ewse
		fwame->can_id = (awb >> 18) & CAN_SFF_MASK;

	if (awb & IF_AWB_TWANSMIT) {
		fwame->can_id |= CAN_WTW_FWAG;
	} ewse {
		int i, dweg = C_CAN_IFACE(DATA1_WEG, iface);

		if (pwiv->type == BOSCH_D_CAN) {
			fow (i = 0; i < fwame->wen; i += 4, dweg += 2) {
				data = pwiv->wead_weg32(pwiv, dweg);
				fwame->data[i] = data;
				fwame->data[i + 1] = data >> 8;
				fwame->data[i + 2] = data >> 16;
				fwame->data[i + 3] = data >> 24;
			}
		} ewse {
			fow (i = 0; i < fwame->wen; i += 2, dweg++) {
				data = pwiv->wead_weg(pwiv, dweg);
				fwame->data[i] = data;
				fwame->data[i + 1] = data >> 8;
			}
		}

		stats->wx_bytes += fwame->wen;
	}
	stats->wx_packets++;

	netif_weceive_skb(skb);
	wetuwn 0;
}

static void c_can_setup_weceive_object(stwuct net_device *dev, int iface,
				       u32 obj, u32 mask, u32 id, u32 mcont)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	mask |= BIT(29);
	pwiv->wwite_weg32(pwiv, C_CAN_IFACE(MASK1_WEG, iface), mask);

	id |= IF_AWB_MSGVAW;
	pwiv->wwite_weg32(pwiv, C_CAN_IFACE(AWB1_WEG, iface), id);

	pwiv->wwite_weg(pwiv, C_CAN_IFACE(MSGCTWW_WEG, iface), mcont);
	c_can_object_put(dev, iface, obj, IF_COMM_WCV_SETUP);
}

static boow c_can_tx_busy(const stwuct c_can_pwiv *pwiv,
			  const stwuct c_can_tx_wing *tx_wing)
{
	if (c_can_get_tx_fwee(pwiv, tx_wing) > 0)
		wetuwn fawse;

	netif_stop_queue(pwiv->dev);

	/* Memowy bawwiew befowe checking tx_fwee (head and taiw) */
	smp_mb();

	if (c_can_get_tx_fwee(pwiv, tx_wing) == 0) {
		netdev_dbg(pwiv->dev,
			   "Stopping tx-queue (tx_head=0x%08x, tx_taiw=0x%08x, wen=%d).\n",
			   tx_wing->head, tx_wing->taiw,
			   tx_wing->head - tx_wing->taiw);
		wetuwn twue;
	}

	netif_stawt_queue(pwiv->dev);
	wetuwn fawse;
}

static netdev_tx_t c_can_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct can_fwame *fwame = (stwuct can_fwame *)skb->data;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct c_can_tx_wing *tx_wing = &pwiv->tx;
	u32 idx, obj, cmd = IF_COMM_TX;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	if (c_can_tx_busy(pwiv, tx_wing))
		wetuwn NETDEV_TX_BUSY;

	idx = c_can_get_tx_head(tx_wing);
	tx_wing->head++;
	if (c_can_get_tx_fwee(pwiv, tx_wing) == 0)
		netif_stop_queue(dev);

	if (idx < c_can_get_tx_taiw(tx_wing))
		cmd &= ~IF_COMM_TXWQST; /* Cache the message */

	/* Stowe the message in the intewface so we can caww
	 * can_put_echo_skb(). We must do this befowe we enabwe
	 * twansmit as we might wace against do_tx().
	 */
	c_can_setup_tx_object(dev, IF_TX, fwame, idx);
	can_put_echo_skb(skb, dev, idx, 0);
	obj = idx + pwiv->msg_obj_tx_fiwst;
	c_can_object_put(dev, IF_TX, obj, cmd);

	wetuwn NETDEV_TX_OK;
}

static int c_can_wait_fow_ctww_init(stwuct net_device *dev,
				    stwuct c_can_pwiv *pwiv, u32 init)
{
	int wetwy = 0;

	whiwe (init != (pwiv->wead_weg(pwiv, C_CAN_CTWW_WEG) & CONTWOW_INIT)) {
		udeway(10);
		if (wetwy++ > 1000) {
			netdev_eww(dev, "CCTWW: set CONTWOW_INIT faiwed\n");
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int c_can_set_bittiming(stwuct net_device *dev)
{
	unsigned int weg_btw, weg_bwpe, ctww_save;
	u8 bwp, bwpe, sjw, tseg1, tseg2;
	u32 ten_bit_bwp;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	const stwuct can_bittiming *bt = &pwiv->can.bittiming;
	int wes;

	/* c_can pwovides a 6-bit bwp and 4-bit bwpe fiewds */
	ten_bit_bwp = bt->bwp - 1;
	bwp = ten_bit_bwp & BTW_BWP_MASK;
	bwpe = ten_bit_bwp >> 6;

	sjw = bt->sjw - 1;
	tseg1 = bt->pwop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 1;
	weg_btw = bwp | (sjw << BTW_SJW_SHIFT) | (tseg1 << BTW_TSEG1_SHIFT) |
			(tseg2 << BTW_TSEG2_SHIFT);
	weg_bwpe = bwpe & BWP_EXT_BWPE_MASK;

	netdev_info(dev,
		    "setting BTW=%04x BWPE=%04x\n", weg_btw, weg_bwpe);

	ctww_save = pwiv->wead_weg(pwiv, C_CAN_CTWW_WEG);
	ctww_save &= ~CONTWOW_INIT;
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_CCE | CONTWOW_INIT);
	wes = c_can_wait_fow_ctww_init(dev, pwiv, CONTWOW_INIT);
	if (wes)
		wetuwn wes;

	pwiv->wwite_weg(pwiv, C_CAN_BTW_WEG, weg_btw);
	pwiv->wwite_weg(pwiv, C_CAN_BWPEXT_WEG, weg_bwpe);
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, ctww_save);

	wetuwn c_can_wait_fow_ctww_init(dev, pwiv, 0);
}

/* Configuwe C_CAN message objects fow Tx and Wx puwposes:
 * C_CAN pwovides a totaw of 32 message objects that can be configuwed
 * eithew fow Tx ow Wx puwposes. Hewe the fiwst 16 message objects awe used as
 * a weception FIFO. The end of weception FIFO is signified by the EoB bit
 * being SET. The wemaining 16 message objects awe kept aside fow Tx puwposes.
 * See usew guide document fow fuwthew detaiws on configuwing message
 * objects.
 */
static void c_can_configuwe_msg_objects(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	/* fiwst invawidate aww message objects */
	fow (i = pwiv->msg_obj_wx_fiwst; i <= pwiv->msg_obj_num; i++)
		c_can_invaw_msg_object(dev, IF_NAPI, i);

	/* setup weceive message objects */
	fow (i = pwiv->msg_obj_wx_fiwst; i < pwiv->msg_obj_wx_wast; i++)
		c_can_setup_weceive_object(dev, IF_NAPI, i, 0, 0, IF_MCONT_WCV);

	c_can_setup_weceive_object(dev, IF_NAPI, pwiv->msg_obj_wx_wast, 0, 0,
				   IF_MCONT_WCV_EOB);
}

static int c_can_softwawe_weset(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int wetwy = 0;

	if (pwiv->type != BOSCH_D_CAN)
		wetuwn 0;

	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_SWW | CONTWOW_INIT);
	whiwe (pwiv->wead_weg(pwiv, C_CAN_CTWW_WEG) & CONTWOW_SWW) {
		msweep(20);
		if (wetwy++ > 100) {
			netdev_eww(dev, "CCTWW: softwawe weset faiwed\n");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/* Configuwe C_CAN chip:
 * - enabwe/disabwe auto-wetwansmission
 * - set opewating mode
 * - configuwe message objects
 */
static int c_can_chip_config(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct c_can_tx_wing *tx_wing = &pwiv->tx;
	int eww;

	eww = c_can_softwawe_weset(dev);
	if (eww)
		wetuwn eww;

	/* enabwe automatic wetwansmission */
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_ENABWE_AW);

	if ((pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY) &&
	    (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)) {
		/* woopback + siwent mode : usefuw fow hot sewf-test */
		pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_TEST);
		pwiv->wwite_weg(pwiv, C_CAN_TEST_WEG, TEST_WBACK | TEST_SIWENT);
	} ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK) {
		/* woopback mode : usefuw fow sewf-test function */
		pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_TEST);
		pwiv->wwite_weg(pwiv, C_CAN_TEST_WEG, TEST_WBACK);
	} ewse if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY) {
		/* siwent mode : bus-monitowing mode */
		pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_TEST);
		pwiv->wwite_weg(pwiv, C_CAN_TEST_WEG, TEST_SIWENT);
	}

	/* configuwe message objects */
	c_can_configuwe_msg_objects(dev);

	/* set a `wec` vawue so that we can check fow updates watew */
	pwiv->wwite_weg(pwiv, C_CAN_STS_WEG, WEC_UNUSED);

	/* Cweaw aww intewnaw status */
	tx_wing->head = 0;
	tx_wing->taiw = 0;
	pwiv->tx_diw = 0;

	/* set bittiming pawams */
	wetuwn c_can_set_bittiming(dev);
}

static int c_can_stawt(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int eww;
	stwuct pinctww *p;

	/* basic c_can configuwation */
	eww = c_can_chip_config(dev);
	if (eww)
		wetuwn eww;

	/* Setup the command fow new messages */
	pwiv->comm_wcv_high = pwiv->type != BOSCH_D_CAN ?
		IF_COMM_WCV_WOW : IF_COMM_WCV_HIGH;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	/* Attempt to use "active" if avaiwabwe ewse use "defauwt" */
	p = pinctww_get_sewect(pwiv->device, "active");
	if (!IS_EWW(p))
		pinctww_put(p);
	ewse
		pinctww_pm_sewect_defauwt_state(pwiv->device);

	wetuwn 0;
}

static void c_can_stop(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	c_can_iwq_contwow(pwiv, fawse);

	/* put ctww to init on stop to end ongoing twansmission */
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, CONTWOW_INIT);

	/* deactivate pins */
	pinctww_pm_sewect_sweep_state(dev->dev.pawent);
	pwiv->can.state = CAN_STATE_STOPPED;
}

static int c_can_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = c_can_stawt(dev);
		if (eww)
			wetuwn eww;
		netif_wake_queue(dev);
		c_can_iwq_contwow(pwiv, twue);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int __c_can_get_beww_countew(const stwuct net_device *dev,
				    stwuct can_beww_countew *bec)
{
	unsigned int weg_eww_countew;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	weg_eww_countew = pwiv->wead_weg(pwiv, C_CAN_EWW_CNT_WEG);
	bec->wxeww = (weg_eww_countew & EWW_CNT_WEC_MASK) >>
				EWW_CNT_WEC_SHIFT;
	bec->txeww = weg_eww_countew & EWW_CNT_TEC_MASK;

	wetuwn 0;
}

static int c_can_get_beww_countew(const stwuct net_device *dev,
				  stwuct can_beww_countew *bec)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	c_can_pm_wuntime_get_sync(pwiv);
	eww = __c_can_get_beww_countew(dev, bec);
	c_can_pm_wuntime_put_sync(pwiv);

	wetuwn eww;
}

static void c_can_do_tx(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct c_can_tx_wing *tx_wing = &pwiv->tx;
	stwuct net_device_stats *stats = &dev->stats;
	u32 idx, obj, pkts = 0, bytes = 0, pend;
	u8 taiw;

	if (pwiv->msg_obj_tx_wast > 32)
		pend = pwiv->wead_weg32(pwiv, C_CAN_INTPND3_WEG);
	ewse
		pend = pwiv->wead_weg(pwiv, C_CAN_INTPND2_WEG);

	whiwe ((idx = ffs(pend))) {
		idx--;
		pend &= ~BIT(idx);
		obj = idx + pwiv->msg_obj_tx_fiwst;

		/* We use IF_NAPI intewface instead of IF_TX because we
		 * awe cawwed fwom c_can_poww(), which wuns inside
		 * NAPI. We awe not twansmitting.
		 */
		c_can_invaw_tx_object(dev, IF_NAPI, obj);
		bytes += can_get_echo_skb(dev, idx, NUWW);
		pkts++;
	}

	if (!pkts)
		wetuwn;

	tx_wing->taiw += pkts;
	if (c_can_get_tx_fwee(pwiv, tx_wing)) {
		/* Make suwe that anybody stopping the queue aftew
		 * this sees the new tx_wing->taiw.
		 */
		smp_mb();
		netif_wake_queue(pwiv->dev);
	}

	stats->tx_bytes += bytes;
	stats->tx_packets += pkts;

	taiw = c_can_get_tx_taiw(tx_wing);
	if (pwiv->type == BOSCH_D_CAN && taiw == 0) {
		u8 head = c_can_get_tx_head(tx_wing);

		/* Stawt twansmission fow aww cached messages */
		fow (idx = taiw; idx < head; idx++) {
			obj = idx + pwiv->msg_obj_tx_fiwst;
			c_can_object_put(dev, IF_NAPI, obj, IF_COMM_TXWQST);
		}
	}
}

/* If we have a gap in the pending bits, that means we eithew
 * waced with the hawdwawe ow faiwed to weadout aww uppew
 * objects in the wast wun due to quota wimit.
 */
static u32 c_can_adjust_pending(u32 pend, u32 wx_mask)
{
	u32 weight, wasts;

	if (pend == wx_mask)
		wetuwn pend;

	/* If the wast set bit is wawgew than the numbew of pending
	 * bits we have a gap.
	 */
	weight = hweight32(pend);
	wasts = fws(pend);

	/* If the bits awe wineaw, nothing to do */
	if (wasts == weight)
		wetuwn pend;

	/* Find the fiwst set bit aftew the gap. We wawk backwawds
	 * fwom the wast set bit.
	 */
	fow (wasts--; pend & BIT(wasts - 1); wasts--)
		;

	wetuwn pend & ~GENMASK(wasts - 1, 0);
}

static inwine void c_can_wx_object_get(stwuct net_device *dev,
				       stwuct c_can_pwiv *pwiv, u32 obj)
{
	c_can_object_get(dev, IF_NAPI, obj, pwiv->comm_wcv_high);
}

static inwine void c_can_wx_finawize(stwuct net_device *dev,
				     stwuct c_can_pwiv *pwiv, u32 obj)
{
	if (pwiv->type != BOSCH_D_CAN)
		c_can_object_get(dev, IF_NAPI, obj, IF_COMM_CWW_NEWDAT);
}

static int c_can_wead_objects(stwuct net_device *dev, stwuct c_can_pwiv *pwiv,
			      u32 pend, int quota)
{
	u32 pkts = 0, ctww, obj;

	whiwe ((obj = ffs(pend)) && quota > 0) {
		pend &= ~BIT(obj - 1);

		c_can_wx_object_get(dev, pwiv, obj);
		ctww = pwiv->wead_weg(pwiv, C_CAN_IFACE(MSGCTWW_WEG, IF_NAPI));

		if (ctww & IF_MCONT_MSGWST) {
			int n;

			n = c_can_handwe_wost_msg_obj(dev, IF_NAPI, obj, ctww);

			pkts += n;
			quota -= n;
			continue;
		}

		/* This weawwy shouwd not happen, but this covews some
		 * odd HW behaviouw. Do not wemove that unwess you
		 * want to bwick youw machine.
		 */
		if (!(ctww & IF_MCONT_NEWDAT))
			continue;

		/* wead the data fwom the message object */
		c_can_wead_msg_object(dev, IF_NAPI, ctww);

		c_can_wx_finawize(dev, pwiv, obj);

		pkts++;
		quota--;
	}

	wetuwn pkts;
}

static inwine u32 c_can_get_pending(stwuct c_can_pwiv *pwiv)
{
	u32 pend;

	if (pwiv->msg_obj_wx_wast > 16)
		pend = pwiv->wead_weg32(pwiv, C_CAN_NEWDAT1_WEG);
	ewse
		pend = pwiv->wead_weg(pwiv, C_CAN_NEWDAT1_WEG);

	wetuwn pend;
}

/* theowy of opewation:
 *
 * c_can cowe saves a weceived CAN message into the fiwst fwee message
 * object it finds fwee (stawting with the wowest). Bits NEWDAT and
 * INTPND awe set fow this message object indicating that a new message
 * has awwived.
 *
 * We cweaw the newdat bit wight away.
 *
 * This can wesuwt in packet weowdewing when the weadout is swow.
 */
static int c_can_do_wx_poww(stwuct net_device *dev, int quota)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	u32 pkts = 0, pend = 0, towead, n;

	whiwe (quota > 0) {
		if (!pend) {
			pend = c_can_get_pending(pwiv);
			if (!pend)
				bweak;
			/* If the pending fiewd has a gap, handwe the
			 * bits above the gap fiwst.
			 */
			towead = c_can_adjust_pending(pend,
						      pwiv->msg_obj_wx_mask);
		} ewse {
			towead = pend;
		}
		/* Wemove the bits fwom pend */
		pend &= ~towead;
		/* Wead the objects */
		n = c_can_wead_objects(dev, pwiv, towead, quota);
		pkts += n;
		quota -= n;
	}

	wetuwn pkts;
}

static int c_can_handwe_state_change(stwuct net_device *dev,
				     enum c_can_bus_ewwow_types ewwow_type)
{
	unsigned int weg_eww_countew;
	unsigned int wx_eww_passive;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct can_beww_countew bec;

	switch (ewwow_type) {
	case C_CAN_NO_EWWOW:
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		bweak;
	case C_CAN_EWWOW_WAWNING:
		/* ewwow wawning state */
		pwiv->can.can_stats.ewwow_wawning++;
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		bweak;
	case C_CAN_EWWOW_PASSIVE:
		/* ewwow passive state */
		pwiv->can.can_stats.ewwow_passive++;
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
		bweak;
	case C_CAN_BUS_OFF:
		/* bus-off state */
		pwiv->can.state = CAN_STATE_BUS_OFF;
		pwiv->can.can_stats.bus_off++;
		bweak;
	defauwt:
		bweak;
	}

	/* pwopagate the ewwow condition to the CAN stack */
	skb = awwoc_can_eww_skb(dev, &cf);
	if (unwikewy(!skb))
		wetuwn 0;

	__c_can_get_beww_countew(dev, &bec);
	weg_eww_countew = pwiv->wead_weg(pwiv, C_CAN_EWW_CNT_WEG);
	wx_eww_passive = (weg_eww_countew & EWW_CNT_WP_MASK) >>
				EWW_CNT_WP_SHIFT;

	switch (ewwow_type) {
	case C_CAN_NO_EWWOW:
		cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
		cf->data[1] = CAN_EWW_CWTW_ACTIVE;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
		bweak;
	case C_CAN_EWWOW_WAWNING:
		/* ewwow wawning state */
		cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
		cf->data[1] = (bec.txeww > bec.wxeww) ?
			CAN_EWW_CWTW_TX_WAWNING :
			CAN_EWW_CWTW_WX_WAWNING;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;

		bweak;
	case C_CAN_EWWOW_PASSIVE:
		/* ewwow passive state */
		cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
		if (wx_eww_passive)
			cf->data[1] |= CAN_EWW_CWTW_WX_PASSIVE;
		if (bec.txeww > 127)
			cf->data[1] |= CAN_EWW_CWTW_TX_PASSIVE;

		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
		bweak;
	case C_CAN_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_EWW_BUSOFF;
		can_bus_off(dev);
		bweak;
	defauwt:
		bweak;
	}

	netif_weceive_skb(skb);

	wetuwn 1;
}

static int c_can_handwe_bus_eww(stwuct net_device *dev,
				enum c_can_wec_type wec_type)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	/* eawwy exit if no wec update ow no ewwow.
	 * no wec update means that no CAN bus event has been detected
	 * since CPU wwote 0x7 vawue to status weg.
	 */
	if (wec_type == WEC_UNUSED || wec_type == WEC_NO_EWWOW)
		wetuwn 0;

	if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING))
		wetuwn 0;

	/* common fow aww type of bus ewwows */
	pwiv->can.can_stats.bus_ewwow++;
	stats->wx_ewwows++;

	/* pwopagate the ewwow condition to the CAN stack */
	skb = awwoc_can_eww_skb(dev, &cf);
	if (unwikewy(!skb))
		wetuwn 0;

	/* check fow 'wast ewwow code' which tewws us the
	 * type of the wast ewwow to occuw on the CAN bus
	 */
	cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

	switch (wec_type) {
	case WEC_STUFF_EWWOW:
		netdev_dbg(dev, "stuff ewwow\n");
		cf->data[2] |= CAN_EWW_PWOT_STUFF;
		bweak;
	case WEC_FOWM_EWWOW:
		netdev_dbg(dev, "fowm ewwow\n");
		cf->data[2] |= CAN_EWW_PWOT_FOWM;
		bweak;
	case WEC_ACK_EWWOW:
		netdev_dbg(dev, "ack ewwow\n");
		cf->data[3] = CAN_EWW_PWOT_WOC_ACK;
		bweak;
	case WEC_BIT1_EWWOW:
		netdev_dbg(dev, "bit1 ewwow\n");
		cf->data[2] |= CAN_EWW_PWOT_BIT1;
		bweak;
	case WEC_BIT0_EWWOW:
		netdev_dbg(dev, "bit0 ewwow\n");
		cf->data[2] |= CAN_EWW_PWOT_BIT0;
		bweak;
	case WEC_CWC_EWWOW:
		netdev_dbg(dev, "CWC ewwow\n");
		cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		bweak;
	defauwt:
		bweak;
	}

	netif_weceive_skb(skb);
	wetuwn 1;
}

static int c_can_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct net_device *dev = napi->dev;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	u16 cuww, wast = pwiv->wast_status;
	int wowk_done = 0;

	/* Onwy wead the status wegistew if a status intewwupt was pending */
	if (atomic_xchg(&pwiv->sie_pending, 0)) {
		pwiv->wast_status = pwiv->wead_weg(pwiv, C_CAN_STS_WEG);
		cuww = pwiv->wast_status;
		/* Ack status on C_CAN. D_CAN is sewf cweawing */
		if (pwiv->type != BOSCH_D_CAN)
			pwiv->wwite_weg(pwiv, C_CAN_STS_WEG, WEC_UNUSED);
	} ewse {
		/* no change detected ... */
		cuww = wast;
	}

	/* handwe state changes */
	if ((cuww & STATUS_EWAWN) && (!(wast & STATUS_EWAWN))) {
		netdev_dbg(dev, "entewed ewwow wawning state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_EWWOW_WAWNING);
	}

	if ((cuww & STATUS_EPASS) && (!(wast & STATUS_EPASS))) {
		netdev_dbg(dev, "entewed ewwow passive state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_EWWOW_PASSIVE);
	}

	if ((cuww & STATUS_BOFF) && (!(wast & STATUS_BOFF))) {
		netdev_dbg(dev, "entewed bus off state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_BUS_OFF);
		goto end;
	}

	/* handwe bus wecovewy events */
	if ((!(cuww & STATUS_BOFF)) && (wast & STATUS_BOFF)) {
		netdev_dbg(dev, "weft bus off state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_EWWOW_PASSIVE);
	}

	if ((!(cuww & STATUS_EPASS)) && (wast & STATUS_EPASS)) {
		netdev_dbg(dev, "weft ewwow passive state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_EWWOW_WAWNING);
	}

	if ((!(cuww & STATUS_EWAWN)) && (wast & STATUS_EWAWN)) {
		netdev_dbg(dev, "weft ewwow wawning state\n");
		wowk_done += c_can_handwe_state_change(dev, C_CAN_NO_EWWOW);
	}

	/* handwe wec ewwows on the bus */
	wowk_done += c_can_handwe_bus_eww(dev, cuww & WEC_MASK);

	/* Handwe Tx/Wx events. We do this unconditionawwy */
	wowk_done += c_can_do_wx_poww(dev, (quota - wowk_done));
	c_can_do_tx(dev);

end:
	if (wowk_done < quota) {
		napi_compwete_done(napi, wowk_done);
		/* enabwe aww IWQs if we awe not in bus off state */
		if (pwiv->can.state != CAN_STATE_BUS_OFF)
			c_can_iwq_contwow(pwiv, twue);
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t c_can_isw(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int weg_int;

	weg_int = pwiv->wead_weg(pwiv, C_CAN_INT_WEG);
	if (!weg_int)
		wetuwn IWQ_NONE;

	/* save fow watew use */
	if (weg_int & INT_STS_PENDING)
		atomic_set(&pwiv->sie_pending, 1);

	/* disabwe aww intewwupts and scheduwe the NAPI */
	c_can_iwq_contwow(pwiv, fawse);
	napi_scheduwe(&pwiv->napi);

	wetuwn IWQ_HANDWED;
}

static int c_can_open(stwuct net_device *dev)
{
	int eww;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	c_can_pm_wuntime_get_sync(pwiv);
	c_can_weset_wam(pwiv, twue);

	/* open the can device */
	eww = open_candev(dev);
	if (eww) {
		netdev_eww(dev, "faiwed to open can device\n");
		goto exit_open_faiw;
	}

	/* wegistew intewwupt handwew */
	eww = wequest_iwq(dev->iwq, &c_can_isw, IWQF_SHAWED, dev->name,
			  dev);
	if (eww < 0) {
		netdev_eww(dev, "faiwed to wequest intewwupt\n");
		goto exit_iwq_faiw;
	}

	/* stawt the c_can contwowwew */
	eww = c_can_stawt(dev);
	if (eww)
		goto exit_stawt_faiw;

	napi_enabwe(&pwiv->napi);
	/* enabwe status change, ewwow and moduwe intewwupts */
	c_can_iwq_contwow(pwiv, twue);
	netif_stawt_queue(dev);

	wetuwn 0;

exit_stawt_faiw:
	fwee_iwq(dev->iwq, dev);
exit_iwq_faiw:
	cwose_candev(dev);
exit_open_faiw:
	c_can_weset_wam(pwiv, fawse);
	c_can_pm_wuntime_put_sync(pwiv);
	wetuwn eww;
}

static int c_can_cwose(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);
	c_can_stop(dev);
	fwee_iwq(dev->iwq, dev);
	cwose_candev(dev);

	c_can_weset_wam(pwiv, fawse);
	c_can_pm_wuntime_put_sync(pwiv);

	wetuwn 0;
}

stwuct net_device *awwoc_c_can_dev(int msg_obj_num)
{
	stwuct net_device *dev;
	stwuct c_can_pwiv *pwiv;
	int msg_obj_tx_num = msg_obj_num / 2;

	dev = awwoc_candev(sizeof(*pwiv), msg_obj_tx_num);
	if (!dev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);
	pwiv->msg_obj_num = msg_obj_num;
	pwiv->msg_obj_wx_num = msg_obj_num - msg_obj_tx_num;
	pwiv->msg_obj_wx_fiwst = 1;
	pwiv->msg_obj_wx_wast =
		pwiv->msg_obj_wx_fiwst + pwiv->msg_obj_wx_num - 1;
	pwiv->msg_obj_wx_mask = GENMASK(pwiv->msg_obj_wx_num - 1, 0);

	pwiv->msg_obj_tx_num = msg_obj_tx_num;
	pwiv->msg_obj_tx_fiwst = pwiv->msg_obj_wx_wast + 1;
	pwiv->msg_obj_tx_wast =
		pwiv->msg_obj_tx_fiwst + pwiv->msg_obj_tx_num - 1;

	pwiv->tx.head = 0;
	pwiv->tx.taiw = 0;
	pwiv->tx.obj_num = msg_obj_tx_num;

	netif_napi_add_weight(dev, &pwiv->napi, c_can_poww,
			      pwiv->msg_obj_wx_num);

	pwiv->dev = dev;
	pwiv->can.bittiming_const = &c_can_bittiming_const;
	pwiv->can.do_set_mode = c_can_set_mode;
	pwiv->can.do_get_beww_countew = c_can_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
					CAN_CTWWMODE_WISTENONWY |
					CAN_CTWWMODE_BEWW_WEPOWTING;

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(awwoc_c_can_dev);

#ifdef CONFIG_PM
int c_can_powew_down(stwuct net_device *dev)
{
	u32 vaw;
	unsigned wong time_out;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	if (!(dev->fwags & IFF_UP))
		wetuwn 0;

	WAWN_ON(pwiv->type != BOSCH_D_CAN);

	/* set PDW vawue so the device goes to powew down mode */
	vaw = pwiv->wead_weg(pwiv, C_CAN_CTWW_EX_WEG);
	vaw |= CONTWOW_EX_PDW;
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_EX_WEG, vaw);

	/* Wait fow the PDA bit to get set */
	time_out = jiffies + msecs_to_jiffies(INIT_WAIT_MS);
	whiwe (!(pwiv->wead_weg(pwiv, C_CAN_STS_WEG) & STATUS_PDA) &&
	       time_aftew(time_out, jiffies))
		cpu_wewax();

	if (time_aftew(jiffies, time_out))
		wetuwn -ETIMEDOUT;

	c_can_stop(dev);

	c_can_weset_wam(pwiv, fawse);
	c_can_pm_wuntime_put_sync(pwiv);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(c_can_powew_down);

int c_can_powew_up(stwuct net_device *dev)
{
	u32 vaw;
	unsigned wong time_out;
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);
	int wet;

	if (!(dev->fwags & IFF_UP))
		wetuwn 0;

	WAWN_ON(pwiv->type != BOSCH_D_CAN);

	c_can_pm_wuntime_get_sync(pwiv);
	c_can_weset_wam(pwiv, twue);

	/* Cweaw PDW and INIT bits */
	vaw = pwiv->wead_weg(pwiv, C_CAN_CTWW_EX_WEG);
	vaw &= ~CONTWOW_EX_PDW;
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_EX_WEG, vaw);
	vaw = pwiv->wead_weg(pwiv, C_CAN_CTWW_WEG);
	vaw &= ~CONTWOW_INIT;
	pwiv->wwite_weg(pwiv, C_CAN_CTWW_WEG, vaw);

	/* Wait fow the PDA bit to get cweaw */
	time_out = jiffies + msecs_to_jiffies(INIT_WAIT_MS);
	whiwe ((pwiv->wead_weg(pwiv, C_CAN_STS_WEG) & STATUS_PDA) &&
	       time_aftew(time_out, jiffies))
		cpu_wewax();

	if (time_aftew(jiffies, time_out)) {
		wet = -ETIMEDOUT;
		goto eww_out;
	}

	wet = c_can_stawt(dev);
	if (wet)
		goto eww_out;

	c_can_iwq_contwow(pwiv, twue);

	wetuwn 0;

eww_out:
	c_can_weset_wam(pwiv, fawse);
	c_can_pm_wuntime_put_sync(pwiv);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(c_can_powew_up);
#endif

void fwee_c_can_dev(stwuct net_device *dev)
{
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	netif_napi_dew(&pwiv->napi);
	fwee_candev(dev);
}
EXPOWT_SYMBOW_GPW(fwee_c_can_dev);

static const stwuct net_device_ops c_can_netdev_ops = {
	.ndo_open = c_can_open,
	.ndo_stop = c_can_cwose,
	.ndo_stawt_xmit = c_can_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

int wegistew_c_can_dev(stwuct net_device *dev)
{
	/* Deactivate pins to pwevent DWA7 DCAN IP fwom being
	 * stuck in twansition when moduwe is disabwed.
	 * Pins awe activated in c_can_stawt() and deactivated
	 * in c_can_stop()
	 */
	pinctww_pm_sewect_sweep_state(dev->dev.pawent);

	dev->fwags |= IFF_ECHO;	/* we suppowt wocaw echo */
	dev->netdev_ops = &c_can_netdev_ops;
	dev->ethtoow_ops = &c_can_ethtoow_ops;

	wetuwn wegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(wegistew_c_can_dev);

void unwegistew_c_can_dev(stwuct net_device *dev)
{
	unwegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(unwegistew_c_can_dev);

MODUWE_AUTHOW("Bhupesh Shawma <bhupesh.shawma@st.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("CAN bus dwivew fow Bosch C_CAN contwowwew");
