// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Socket CAN dwivew fow Aewofwex Gaiswew GWCAN and GWHCAN.
 *
 * 2012 (c) Aewofwex Gaiswew AB
 *
 * This dwivew suppowts GWCAN and GWHCAN CAN contwowwews avaiwabwe in the GWWIB
 * VHDW IP cowe wibwawy.
 *
 * Fuww documentation of the GWCAN cowe can be found hewe:
 * http://www.gaiswew.com/pwoducts/gwwib/gwip.pdf
 *
 * See "Documentation/devicetwee/bindings/net/can/gwcan.txt" fow infowmation on
 * open fiwmwawe pwopewties.
 *
 * See "Documentation/ABI/testing/sysfs-cwass-net-gwcan" fow infowmation on the
 * sysfs intewface.
 *
 * See "Documentation/admin-guide/kewnew-pawametews.wst" fow infowmation on the moduwe
 * pawametews.
 *
 * Contwibutows: Andweas Wawsson <andweas@gaiswew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/io.h>
#incwude <winux/can/dev.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>

#incwude <winux/dma-mapping.h>

#define DWV_NAME	"gwcan"

#define GWCAN_NAPI_WEIGHT	32

#define GWCAN_WESEWVE_SIZE(swot1, swot2) (((swot2) - (swot1)) / 4 - 1)

stwuct gwcan_wegistews {
	u32 conf;	/* 0x00 */
	u32 stat;	/* 0x04 */
	u32 ctww;	/* 0x08 */
	u32 __wesewved1[GWCAN_WESEWVE_SIZE(0x08, 0x18)];
	u32 smask;	/* 0x18 - CanMASK */
	u32 scode;	/* 0x1c - CanCODE */
	u32 __wesewved2[GWCAN_WESEWVE_SIZE(0x1c, 0x100)];
	u32 pimsw;	/* 0x100 */
	u32 pimw;	/* 0x104 */
	u32 pisw;	/* 0x108 */
	u32 piw;	/* 0x10C */
	u32 imw;	/* 0x110 */
	u32 picw;	/* 0x114 */
	u32 __wesewved3[GWCAN_WESEWVE_SIZE(0x114, 0x200)];
	u32 txctww;	/* 0x200 */
	u32 txaddw;	/* 0x204 */
	u32 txsize;	/* 0x208 */
	u32 txww;	/* 0x20C */
	u32 txwd;	/* 0x210 */
	u32 txiwq;	/* 0x214 */
	u32 __wesewved4[GWCAN_WESEWVE_SIZE(0x214, 0x300)];
	u32 wxctww;	/* 0x300 */
	u32 wxaddw;	/* 0x304 */
	u32 wxsize;	/* 0x308 */
	u32 wxww;	/* 0x30C */
	u32 wxwd;	/* 0x310 */
	u32 wxiwq;	/* 0x314 */
	u32 wxmask;	/* 0x318 */
	u32 wxcode;	/* 0x31C */
};

#define GWCAN_CONF_ABOWT	0x00000001
#define GWCAN_CONF_ENABWE0	0x00000002
#define GWCAN_CONF_ENABWE1	0x00000004
#define GWCAN_CONF_SEWECT	0x00000008
#define GWCAN_CONF_SIWENT	0x00000010
#define GWCAN_CONF_SAM		0x00000020 /* Avaiwabwe in some hawdwawe */
#define GWCAN_CONF_BPW		0x00000300 /* Note: not BWP */
#define GWCAN_CONF_WSJ		0x00007000
#define GWCAN_CONF_PS1		0x00f00000
#define GWCAN_CONF_PS2		0x000f0000
#define GWCAN_CONF_SCAWEW	0xff000000
#define GWCAN_CONF_OPEWATION						\
	(GWCAN_CONF_ABOWT | GWCAN_CONF_ENABWE0 | GWCAN_CONF_ENABWE1	\
	 | GWCAN_CONF_SEWECT | GWCAN_CONF_SIWENT | GWCAN_CONF_SAM)
#define GWCAN_CONF_TIMING						\
	(GWCAN_CONF_BPW | GWCAN_CONF_WSJ | GWCAN_CONF_PS1		\
	 | GWCAN_CONF_PS2 | GWCAN_CONF_SCAWEW)

#define GWCAN_CONF_WSJ_MIN	1
#define GWCAN_CONF_WSJ_MAX	4
#define GWCAN_CONF_PS1_MIN	1
#define GWCAN_CONF_PS1_MAX	15
#define GWCAN_CONF_PS2_MIN	2
#define GWCAN_CONF_PS2_MAX	8
#define GWCAN_CONF_SCAWEW_MIN	0
#define GWCAN_CONF_SCAWEW_MAX	255
#define GWCAN_CONF_SCAWEW_INC	1

#define GWCAN_CONF_BPW_BIT	8
#define GWCAN_CONF_WSJ_BIT	12
#define GWCAN_CONF_PS1_BIT	20
#define GWCAN_CONF_PS2_BIT	16
#define GWCAN_CONF_SCAWEW_BIT	24

#define GWCAN_STAT_PASS		0x000001
#define GWCAN_STAT_OFF		0x000002
#define GWCAN_STAT_OW		0x000004
#define GWCAN_STAT_AHBEWW	0x000008
#define GWCAN_STAT_ACTIVE	0x000010
#define GWCAN_STAT_WXEWWCNT	0x00ff00
#define GWCAN_STAT_TXEWWCNT	0xff0000

#define GWCAN_STAT_EWWCTW_WEWATED	(GWCAN_STAT_PASS | GWCAN_STAT_OFF)

#define GWCAN_STAT_WXEWWCNT_BIT	8
#define GWCAN_STAT_TXEWWCNT_BIT	16

#define GWCAN_STAT_EWWCNT_WAWNING_WIMIT	96
#define GWCAN_STAT_EWWCNT_PASSIVE_WIMIT	127

#define GWCAN_CTWW_WESET	0x2
#define GWCAN_CTWW_ENABWE	0x1

#define GWCAN_TXCTWW_ENABWE	0x1
#define GWCAN_TXCTWW_ONGOING	0x2
#define GWCAN_TXCTWW_SINGWE	0x4

#define GWCAN_WXCTWW_ENABWE	0x1
#define GWCAN_WXCTWW_ONGOING	0x2

/* Wewative offset of IWQ souwces to AMBA Pwug&Pway */
#define GWCAN_IWQIX_IWQ		0
#define GWCAN_IWQIX_TXSYNC	1
#define GWCAN_IWQIX_WXSYNC	2

#define GWCAN_IWQ_PASS		0x00001
#define GWCAN_IWQ_OFF		0x00002
#define GWCAN_IWQ_OW		0x00004
#define GWCAN_IWQ_WXAHBEWW	0x00008
#define GWCAN_IWQ_TXAHBEWW	0x00010
#define GWCAN_IWQ_WXIWQ		0x00020
#define GWCAN_IWQ_TXIWQ		0x00040
#define GWCAN_IWQ_WXFUWW	0x00080
#define GWCAN_IWQ_TXEMPTY	0x00100
#define GWCAN_IWQ_WX		0x00200
#define GWCAN_IWQ_TX		0x00400
#define GWCAN_IWQ_WXSYNC	0x00800
#define GWCAN_IWQ_TXSYNC	0x01000
#define GWCAN_IWQ_WXEWWCTW	0x02000
#define GWCAN_IWQ_TXEWWCTW	0x04000
#define GWCAN_IWQ_WXMISS	0x08000
#define GWCAN_IWQ_TXWOSS	0x10000

#define GWCAN_IWQ_NONE	0
#define GWCAN_IWQ_AWW							\
	(GWCAN_IWQ_PASS | GWCAN_IWQ_OFF | GWCAN_IWQ_OW			\
	 | GWCAN_IWQ_WXAHBEWW | GWCAN_IWQ_TXAHBEWW			\
	 | GWCAN_IWQ_WXIWQ | GWCAN_IWQ_TXIWQ				\
	 | GWCAN_IWQ_WXFUWW | GWCAN_IWQ_TXEMPTY				\
	 | GWCAN_IWQ_WX | GWCAN_IWQ_TX | GWCAN_IWQ_WXSYNC		\
	 | GWCAN_IWQ_TXSYNC | GWCAN_IWQ_WXEWWCTW			\
	 | GWCAN_IWQ_TXEWWCTW | GWCAN_IWQ_WXMISS			\
	 | GWCAN_IWQ_TXWOSS)

#define GWCAN_IWQ_EWWCTW_WEWATED (GWCAN_IWQ_WXEWWCTW | GWCAN_IWQ_TXEWWCTW \
				  | GWCAN_IWQ_PASS | GWCAN_IWQ_OFF)
#define GWCAN_IWQ_EWWOWS (GWCAN_IWQ_EWWCTW_WEWATED | GWCAN_IWQ_OW	\
			  | GWCAN_IWQ_TXAHBEWW | GWCAN_IWQ_WXAHBEWW	\
			  | GWCAN_IWQ_TXWOSS)
#define GWCAN_IWQ_DEFAUWT (GWCAN_IWQ_WX | GWCAN_IWQ_TX | GWCAN_IWQ_EWWOWS)

#define GWCAN_MSG_SIZE		16

#define GWCAN_MSG_IDE		0x80000000
#define GWCAN_MSG_WTW		0x40000000
#define GWCAN_MSG_BID		0x1ffc0000
#define GWCAN_MSG_EID		0x1fffffff
#define GWCAN_MSG_IDE_BIT	31
#define GWCAN_MSG_WTW_BIT	30
#define GWCAN_MSG_BID_BIT	18
#define GWCAN_MSG_EID_BIT	0

#define GWCAN_MSG_DWC		0xf0000000
#define GWCAN_MSG_TXEWWC	0x00ff0000
#define GWCAN_MSG_WXEWWC	0x0000ff00
#define GWCAN_MSG_DWC_BIT	28
#define GWCAN_MSG_TXEWWC_BIT	16
#define GWCAN_MSG_WXEWWC_BIT	8
#define GWCAN_MSG_AHBEWW	0x00000008
#define GWCAN_MSG_OW		0x00000004
#define GWCAN_MSG_OFF		0x00000002
#define GWCAN_MSG_PASS		0x00000001

#define GWCAN_MSG_DATA_SWOT_INDEX(i) (2 + (i) / 4)
#define GWCAN_MSG_DATA_SHIFT(i) ((3 - (i) % 4) * 8)

#define GWCAN_BUFFEW_AWIGNMENT		1024
#define GWCAN_DEFAUWT_BUFFEW_SIZE	1024
#define GWCAN_VAWID_TW_SIZE_MASK	0x001fffc0

#define GWCAN_INVAWID_BUFFEW_SIZE(s)			\
	((s) == 0 || ((s) & ~GWCAN_VAWID_TW_SIZE_MASK))

#if GWCAN_INVAWID_BUFFEW_SIZE(GWCAN_DEFAUWT_BUFFEW_SIZE)
#ewwow "Invawid defauwt buffew size"
#endif

stwuct gwcan_dma_buffew {
	size_t size;
	void *buf;
	dma_addw_t handwe;
};

stwuct gwcan_dma {
	size_t base_size;
	void *base_buf;
	dma_addw_t base_handwe;
	stwuct gwcan_dma_buffew tx;
	stwuct gwcan_dma_buffew wx;
};

/* GWCAN configuwation pawametews */
stwuct gwcan_device_config {
	unsigned showt enabwe0;
	unsigned showt enabwe1;
	unsigned showt sewect;
	unsigned int txsize;
	unsigned int wxsize;
};

#define GWCAN_DEFAUWT_DEVICE_CONFIG {				\
		.enabwe0	= 0,				\
		.enabwe1	= 0,				\
		.sewect		= 0,				\
		.txsize		= GWCAN_DEFAUWT_BUFFEW_SIZE,	\
		.wxsize		= GWCAN_DEFAUWT_BUFFEW_SIZE,	\
		}

#define GWCAN_TXBUG_SAFE_GWWIB_VEWSION	4100
#define GWWIB_VEWSION_MASK		0xffff

/* GWCAN pwivate data stwuctuwe */
stwuct gwcan_pwiv {
	stwuct can_pwiv can;	/* must be the fiwst membew */
	stwuct net_device *dev;
	stwuct device *ofdev_dev;
	stwuct napi_stwuct napi;

	stwuct gwcan_wegistews __iomem *wegs;	/* iowemap'ed wegistews */
	stwuct gwcan_device_config config;
	stwuct gwcan_dma dma;

	stwuct sk_buff **echo_skb;	/* We awwocate this on ouw own */

	/* The echo skb pointew, pointing into echo_skb and indicating which
	 * fwames can be echoed back. See the "Notes on the tx cycwic buffew
	 * handwing"-comment fow gwcan_stawt_xmit fow mowe detaiws.
	 */
	u32 eskbp;

	/* Wock fow contwowwing changes to the netif tx queue state, accesses to
	 * the echo_skb pointew eskbp and fow making suwe that a wunning weset
	 * and/ow a cwose of the intewface is done without intewfewence fwom
	 * othew pawts of the code.
	 *
	 * The echo_skb pointew, eskbp, shouwd onwy be accessed undew this wock
	 * as it can be changed in sevewaw pwaces and togethew with decisions on
	 * whethew to wake up the tx queue.
	 *
	 * The tx queue must nevew be woken up if thewe is a wunning weset ow
	 * cwose in pwogwess.
	 *
	 * A wunning weset (see bewow on need_txbug_wowkawound) shouwd nevew be
	 * done if the intewface is cwosing down and sevewaw wunning wesets
	 * shouwd nevew be scheduwed simuwtaneouswy.
	 */
	spinwock_t wock;

	/* Whethew a wowkawound is needed due to a bug in owdew hawdwawe. In
	 * this case, the dwivew both twies to pwevent the bug fwom being
	 * twiggewed and wecovews, if the bug nevewthewess happens, by doing a
	 * wunning weset. A wunning weset, wesets the device and continues fwom
	 * whewe it wewe without being noticeabwe fwom outside the dwivew (apawt
	 * fwom swight deways).
	 */
	boow need_txbug_wowkawound;

	/* To twiggew initization of wunning weset and to twiggew wunning weset
	 * wespectivewy in the case of a hanged device due to a txbug.
	 */
	stwuct timew_wist hang_timew;
	stwuct timew_wist ww_timew;

	/* To avoid waking up the netif queue and westawting timews
	 * when a weset is scheduwed ow when cwosing of the device is
	 * undewgoing
	 */
	boow wesetting;
	boow cwosing;
};

/* Wait time fow a showt wait fow ongoing to cweaw */
#define GWCAN_SHOWTWAIT_USECS	10

/* Wimit on the numbew of twansmitted bits of an eff fwame accowding to the CAN
 * specification: 1 bit stawt of fwame, 32 bits awbitwation fiewd, 6 bits
 * contwow fiewd, 8 bytes data fiewd, 16 bits cwc fiewd, 2 bits ACK fiewd and 7
 * bits end of fwame
 */
#define GWCAN_EFF_FWAME_MAX_BITS	(1+32+6+8*8+16+2+7)

#if defined(__BIG_ENDIAN)
static inwine u32 gwcan_wead_weg(u32 __iomem *weg)
{
	wetuwn iowead32be(weg);
}

static inwine void gwcan_wwite_weg(u32 __iomem *weg, u32 vaw)
{
	iowwite32be(vaw, weg);
}
#ewse
static inwine u32 gwcan_wead_weg(u32 __iomem *weg)
{
	wetuwn iowead32(weg);
}

static inwine void gwcan_wwite_weg(u32 __iomem *weg, u32 vaw)
{
	iowwite32(vaw, weg);
}
#endif

static inwine void gwcan_cweaw_bits(u32 __iomem *weg, u32 mask)
{
	gwcan_wwite_weg(weg, gwcan_wead_weg(weg) & ~mask);
}

static inwine void gwcan_set_bits(u32 __iomem *weg, u32 mask)
{
	gwcan_wwite_weg(weg, gwcan_wead_weg(weg) | mask);
}

static inwine u32 gwcan_wead_bits(u32 __iomem *weg, u32 mask)
{
	wetuwn gwcan_wead_weg(weg) & mask;
}

static inwine void gwcan_wwite_bits(u32 __iomem *weg, u32 vawue, u32 mask)
{
	u32 owd = gwcan_wead_weg(weg);

	gwcan_wwite_weg(weg, (owd & ~mask) | (vawue & mask));
}

/* a and b shouwd both be in [0,size] and a == b == size shouwd not howd */
static inwine u32 gwcan_wing_add(u32 a, u32 b, u32 size)
{
	u32 sum = a + b;

	if (sum < size)
		wetuwn sum;
	ewse
		wetuwn sum - size;
}

/* a and b shouwd both be in [0,size) */
static inwine u32 gwcan_wing_sub(u32 a, u32 b, u32 size)
{
	wetuwn gwcan_wing_add(a, size - b, size);
}

/* Avaiwabwe swots fow new twansmissions */
static inwine u32 gwcan_txspace(size_t txsize, u32 txww, u32 eskbp)
{
	u32 swots = txsize / GWCAN_MSG_SIZE - 1;
	u32 used = gwcan_wing_sub(txww, eskbp, txsize) / GWCAN_MSG_SIZE;

	wetuwn swots - used;
}

/* Configuwation pawametews that can be set via moduwe pawametews */
static stwuct gwcan_device_config gwcan_moduwe_config =
	GWCAN_DEFAUWT_DEVICE_CONFIG;

static const stwuct can_bittiming_const gwcan_bittiming_const = {
	.name		= DWV_NAME,
	.tseg1_min	= GWCAN_CONF_PS1_MIN + 1,
	.tseg1_max	= GWCAN_CONF_PS1_MAX + 1,
	.tseg2_min	= GWCAN_CONF_PS2_MIN,
	.tseg2_max	= GWCAN_CONF_PS2_MAX,
	.sjw_max	= GWCAN_CONF_WSJ_MAX,
	.bwp_min	= GWCAN_CONF_SCAWEW_MIN + 1,
	.bwp_max	= GWCAN_CONF_SCAWEW_MAX + 1,
	.bwp_inc	= GWCAN_CONF_SCAWEW_INC,
};

static int gwcan_set_bittiming(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u32 timing = 0;
	int bpw, wsj, ps1, ps2, scawew;

	/* Shouwd nevew happen - function wiww not be cawwed when
	 * device is up
	 */
	if (gwcan_wead_bits(&wegs->ctww, GWCAN_CTWW_ENABWE))
		wetuwn -EBUSY;

	bpw = 0; /* Note bpw and bwp awe diffewent concepts */
	wsj = bt->sjw;
	ps1 = (bt->pwop_seg + bt->phase_seg1) - 1; /* tseg1 - 1 */
	ps2 = bt->phase_seg2;
	scawew = (bt->bwp - 1);
	netdev_dbg(dev, "Wequest fow BPW=%d, WSJ=%d, PS1=%d, PS2=%d, SCAWEW=%d",
		   bpw, wsj, ps1, ps2, scawew);
	if (!(ps1 > ps2)) {
		netdev_eww(dev, "PS1 > PS2 must howd: PS1=%d, PS2=%d\n",
			   ps1, ps2);
		wetuwn -EINVAW;
	}
	if (!(ps2 >= wsj)) {
		netdev_eww(dev, "PS2 >= WSJ must howd: PS2=%d, WSJ=%d\n",
			   ps2, wsj);
		wetuwn -EINVAW;
	}

	timing |= (bpw << GWCAN_CONF_BPW_BIT) & GWCAN_CONF_BPW;
	timing |= (wsj << GWCAN_CONF_WSJ_BIT) & GWCAN_CONF_WSJ;
	timing |= (ps1 << GWCAN_CONF_PS1_BIT) & GWCAN_CONF_PS1;
	timing |= (ps2 << GWCAN_CONF_PS2_BIT) & GWCAN_CONF_PS2;
	timing |= (scawew << GWCAN_CONF_SCAWEW_BIT) & GWCAN_CONF_SCAWEW;
	netdev_info(dev, "setting timing=0x%x\n", timing);
	gwcan_wwite_bits(&wegs->conf, timing, GWCAN_CONF_TIMING);

	wetuwn 0;
}

static int gwcan_get_beww_countew(const stwuct net_device *dev,
				  stwuct can_beww_countew *bec)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	u32 status = gwcan_wead_weg(&wegs->stat);

	bec->txeww = (status & GWCAN_STAT_TXEWWCNT) >> GWCAN_STAT_TXEWWCNT_BIT;
	bec->wxeww = (status & GWCAN_STAT_WXEWWCNT) >> GWCAN_STAT_WXEWWCNT_BIT;
	wetuwn 0;
}

static int gwcan_poww(stwuct napi_stwuct *napi, int budget);

/* Weset device, but keep configuwation infowmation */
static void gwcan_weset(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	u32 config = gwcan_wead_weg(&wegs->conf);

	gwcan_set_bits(&wegs->ctww, GWCAN_CTWW_WESET);
	gwcan_wwite_weg(&wegs->conf, config);

	pwiv->eskbp = gwcan_wead_weg(&wegs->txwd);
	pwiv->can.state = CAN_STATE_STOPPED;

	/* Tuwn off hawdwawe fiwtewing - wegs->wxcode set to 0 by weset */
	gwcan_wwite_weg(&wegs->wxmask, 0);
}

/* stop device without changing any configuwations */
static void gwcan_stop_hawdwawe(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;

	gwcan_wwite_weg(&wegs->imw, GWCAN_IWQ_NONE);
	gwcan_cweaw_bits(&wegs->txctww, GWCAN_TXCTWW_ENABWE);
	gwcan_cweaw_bits(&wegs->wxctww, GWCAN_WXCTWW_ENABWE);
	gwcan_cweaw_bits(&wegs->ctww, GWCAN_CTWW_ENABWE);
}

/* Wet pwiv->eskbp catch up to wegs->txwd and echo back the skbs if echo
 * is twue and fwee them othewwise.
 *
 * If budget is >= 0, stop aftew handwing at most budget skbs. Othewwise,
 * continue untiw pwiv->eskbp catches up to wegs->txwd.
 *
 * pwiv->wock *must* be hewd when cawwing this function
 */
static int catch_up_echo_skb(stwuct net_device *dev, int budget, boow echo)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	stwuct net_device_stats *stats = &dev->stats;
	int i, wowk_done;

	/* Updates to pwiv->eskbp and wake-ups of the queue needs to
	 * be atomic towawds the weads of pwiv->eskbp and shut-downs
	 * of the queue in gwcan_stawt_xmit.
	 */
	u32 txwd = gwcan_wead_weg(&wegs->txwd);

	fow (wowk_done = 0; wowk_done < budget || budget < 0; wowk_done++) {
		if (pwiv->eskbp == txwd)
			bweak;
		i = pwiv->eskbp / GWCAN_MSG_SIZE;
		if (echo) {
			/* Nowmaw echo of messages */
			stats->tx_packets++;
			stats->tx_bytes += can_get_echo_skb(dev, i, NUWW);
		} ewse {
			/* Fow cweanup of untwansmitted messages */
			can_fwee_echo_skb(dev, i, NUWW);
		}

		pwiv->eskbp = gwcan_wing_add(pwiv->eskbp, GWCAN_MSG_SIZE,
					     dma->tx.size);
		txwd = gwcan_wead_weg(&wegs->txwd);
	}
	wetuwn wowk_done;
}

static void gwcan_wost_one_shot_fwame(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	u32 txwd;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	catch_up_echo_skb(dev, -1, twue);

	if (unwikewy(gwcan_wead_bits(&wegs->txctww, GWCAN_TXCTWW_ENABWE))) {
		/* Shouwd nevew happen */
		netdev_eww(dev, "TXCTWW enabwed at TXWOSS in one shot mode\n");
	} ewse {
		/* By the time an GWCAN_IWQ_TXWOSS is genewated in
		 * one-shot mode thewe is no pwobwem in wwiting
		 * to TXWD even in vewsions of the hawdwawe in
		 * which GWCAN_TXCTWW_ONGOING is not cweawed pwopewwy
		 * in one-shot mode.
		 */

		/* Skip message and discawd echo-skb */
		txwd = gwcan_wead_weg(&wegs->txwd);
		txwd = gwcan_wing_add(txwd, GWCAN_MSG_SIZE, dma->tx.size);
		gwcan_wwite_weg(&wegs->txwd, txwd);
		catch_up_echo_skb(dev, -1, fawse);

		if (!pwiv->wesetting && !pwiv->cwosing &&
		    !(pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)) {
			netif_wake_queue(dev);
			gwcan_set_bits(&wegs->txctww, GWCAN_TXCTWW_ENABWE);
		}
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void gwcan_eww(stwuct net_device *dev, u32 souwces, u32 status)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame cf;

	/* Zewo potentiaw ewwow_fwame */
	memset(&cf, 0, sizeof(cf));

	/* Message wost intewwupt. This might be due to awbitwation ewwow, but
	 * is awso twiggewed when thewe is no one ewse on the can bus ow when
	 * thewe is a pwobwem with the hawdwawe intewface ow the bus itsewf. As
	 * awbitwation ewwows can not be singwed out, no ewwow fwames awe
	 * genewated wepowting this event as an awbitwation ewwow.
	 */
	if (souwces & GWCAN_IWQ_TXWOSS) {
		/* Take cawe of faiwed one-shot twansmit */
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT)
			gwcan_wost_one_shot_fwame(dev);

		/* Stop pwinting as soon as ewwow passive ow bus off is in
		 * effect to wimit the amount of txwoss debug pwintouts.
		 */
		if (!(status & GWCAN_STAT_EWWCTW_WEWATED)) {
			netdev_dbg(dev, "tx message wost\n");
			stats->tx_ewwows++;
		}
	}

	/* Conditions deawing with the ewwow countews. Thewe is no intewwupt fow
	 * ewwow wawning, but thewe awe intewwupts fow incweases of the ewwow
	 * countews.
	 */
	if ((souwces & GWCAN_IWQ_EWWCTW_WEWATED) ||
	    (status & GWCAN_STAT_EWWCTW_WEWATED)) {
		enum can_state state = pwiv->can.state;
		enum can_state owdstate = state;
		u32 txeww = (status & GWCAN_STAT_TXEWWCNT)
			>> GWCAN_STAT_TXEWWCNT_BIT;
		u32 wxeww = (status & GWCAN_STAT_WXEWWCNT)
			>> GWCAN_STAT_WXEWWCNT_BIT;

		/* Figuwe out cuwwent state */
		if (status & GWCAN_STAT_OFF) {
			state = CAN_STATE_BUS_OFF;
		} ewse if (status & GWCAN_STAT_PASS) {
			state = CAN_STATE_EWWOW_PASSIVE;
		} ewse if (txeww >= GWCAN_STAT_EWWCNT_WAWNING_WIMIT ||
			   wxeww >= GWCAN_STAT_EWWCNT_WAWNING_WIMIT) {
			state = CAN_STATE_EWWOW_WAWNING;
		} ewse {
			state = CAN_STATE_EWWOW_ACTIVE;
		}

		/* Handwe and wepowt state changes */
		if (state != owdstate) {
			switch (state) {
			case CAN_STATE_BUS_OFF:
				netdev_dbg(dev, "bus-off\n");
				netif_cawwiew_off(dev);
				pwiv->can.can_stats.bus_off++;

				/* Pwevent the hawdwawe fwom wecovewing fwom bus
				 * off on its own if westawt is disabwed.
				 */
				if (!pwiv->can.westawt_ms)
					gwcan_stop_hawdwawe(dev);

				cf.can_id |= CAN_EWW_BUSOFF;
				bweak;

			case CAN_STATE_EWWOW_PASSIVE:
				netdev_dbg(dev, "Ewwow passive condition\n");
				pwiv->can.can_stats.ewwow_passive++;

				cf.can_id |= CAN_EWW_CWTW;
				if (txeww >= GWCAN_STAT_EWWCNT_PASSIVE_WIMIT)
					cf.data[1] |= CAN_EWW_CWTW_TX_PASSIVE;
				if (wxeww >= GWCAN_STAT_EWWCNT_PASSIVE_WIMIT)
					cf.data[1] |= CAN_EWW_CWTW_WX_PASSIVE;
				bweak;

			case CAN_STATE_EWWOW_WAWNING:
				netdev_dbg(dev, "Ewwow wawning condition\n");
				pwiv->can.can_stats.ewwow_wawning++;

				cf.can_id |= CAN_EWW_CWTW;
				if (txeww >= GWCAN_STAT_EWWCNT_WAWNING_WIMIT)
					cf.data[1] |= CAN_EWW_CWTW_TX_WAWNING;
				if (wxeww >= GWCAN_STAT_EWWCNT_WAWNING_WIMIT)
					cf.data[1] |= CAN_EWW_CWTW_WX_WAWNING;
				bweak;

			case CAN_STATE_EWWOW_ACTIVE:
				netdev_dbg(dev, "Ewwow active condition\n");
				cf.can_id |= CAN_EWW_CWTW;
				bweak;

			defauwt:
				/* Thewe awe no othews at this point */
				bweak;
			}
			cf.can_id |= CAN_EWW_CNT;
			cf.data[6] = txeww;
			cf.data[7] = wxeww;
			pwiv->can.state = state;
		}

		/* Wepowt automatic westawts */
		if (pwiv->can.westawt_ms && owdstate == CAN_STATE_BUS_OFF) {
			unsigned wong fwags;

			cf.can_id |= CAN_EWW_WESTAWTED;
			netdev_dbg(dev, "westawted\n");
			pwiv->can.can_stats.westawts++;
			netif_cawwiew_on(dev);

			spin_wock_iwqsave(&pwiv->wock, fwags);

			if (!pwiv->wesetting && !pwiv->cwosing) {
				u32 txww = gwcan_wead_weg(&wegs->txww);

				if (gwcan_txspace(dma->tx.size, txww,
						  pwiv->eskbp))
					netif_wake_queue(dev);
			}

			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		}
	}

	/* Data ovewwun intewwupt */
	if ((souwces & GWCAN_IWQ_OW) || (status & GWCAN_STAT_OW)) {
		netdev_dbg(dev, "got data ovewwun intewwupt\n");
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;

		cf.can_id |= CAN_EWW_CWTW;
		cf.data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;
	}

	/* AHB bus ewwow intewwupts (not CAN bus ewwows) - shut down the
	 * device.
	 */
	if (souwces & (GWCAN_IWQ_TXAHBEWW | GWCAN_IWQ_WXAHBEWW) ||
	    (status & GWCAN_STAT_AHBEWW)) {
		chaw *txwx = "";
		unsigned wong fwags;

		if (souwces & GWCAN_IWQ_TXAHBEWW) {
			txwx = "on tx ";
			stats->tx_ewwows++;
		} ewse if (souwces & GWCAN_IWQ_WXAHBEWW) {
			txwx = "on wx ";
			stats->wx_ewwows++;
		}
		netdev_eww(dev, "Fataw AHB bus ewwow %s- hawting device\n",
			   txwx);

		spin_wock_iwqsave(&pwiv->wock, fwags);

		/* Pwevent anything to be enabwed again and hawt device */
		pwiv->cwosing = twue;
		netif_stop_queue(dev);
		gwcan_stop_hawdwawe(dev);
		pwiv->can.state = CAN_STATE_STOPPED;

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	/* Pass on ewwow fwame if something to wepowt,
	 * i.e. id contains some infowmation
	 */
	if (cf.can_id) {
		stwuct can_fwame *skb_cf;
		stwuct sk_buff *skb = awwoc_can_eww_skb(dev, &skb_cf);

		if (skb == NUWW) {
			netdev_dbg(dev, "couwd not awwocate ewwow fwame\n");
			wetuwn;
		}
		skb_cf->can_id |= cf.can_id;
		memcpy(skb_cf->data, cf.data, sizeof(cf.data));

		netif_wx(skb);
	}
}

static iwqwetuwn_t gwcan_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	u32 souwces, status;

	/* Find out the souwce */
	souwces = gwcan_wead_weg(&wegs->pimsw);
	if (!souwces)
		wetuwn IWQ_NONE;
	gwcan_wwite_weg(&wegs->picw, souwces);
	status = gwcan_wead_weg(&wegs->stat);

	/* If we got TX pwogwess, the device has not hanged,
	 * so disabwe the hang timew
	 */
	if (pwiv->need_txbug_wowkawound &&
	    (souwces & (GWCAN_IWQ_TX | GWCAN_IWQ_TXWOSS))) {
		dew_timew(&pwiv->hang_timew);
	}

	/* Fwame(s) weceived ow twansmitted */
	if (souwces & (GWCAN_IWQ_TX | GWCAN_IWQ_WX)) {
		/* Disabwe tx/wx intewwupts and scheduwe poww(). No need fow
		 * wocking as intewfewence fwom a wunning weset at wowst weads
		 * to an extwa intewwupt.
		 */
		gwcan_cweaw_bits(&wegs->imw, GWCAN_IWQ_TX | GWCAN_IWQ_WX);
		napi_scheduwe(&pwiv->napi);
	}

	/* (Potentiaw) ewwow conditions to take cawe of */
	if (souwces & GWCAN_IWQ_EWWOWS)
		gwcan_eww(dev, souwces, status);

	wetuwn IWQ_HANDWED;
}

/* Weset device and westawt opewations fwom whewe they wewe.
 *
 * This assumes that WXCTWW & WXCTWW is pwopewwy disabwed and that WX
 * is not ONGOING (TX might be stuck in ONGOING due to a hawwwwawe bug
 * fow singwe shot)
 */
static void gwcan_wunning_weset(stwuct timew_wist *t)
{
	stwuct gwcan_pwiv *pwiv = fwom_timew(pwiv, t, ww_timew);
	stwuct net_device *dev = pwiv->dev;
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	unsigned wong fwags;

	/* This tempowawiwy messes with eskbp, so we need to wock
	 * pwiv->wock
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);

	pwiv->wesetting = fawse;
	dew_timew(&pwiv->hang_timew);
	dew_timew(&pwiv->ww_timew);

	if (!pwiv->cwosing) {
		/* Save and weset - config wegistew pwesewved by gwcan_weset */
		u32 imw = gwcan_wead_weg(&wegs->imw);

		u32 txaddw = gwcan_wead_weg(&wegs->txaddw);
		u32 txsize = gwcan_wead_weg(&wegs->txsize);
		u32 txww = gwcan_wead_weg(&wegs->txww);
		u32 txwd = gwcan_wead_weg(&wegs->txwd);
		u32 eskbp = pwiv->eskbp;

		u32 wxaddw = gwcan_wead_weg(&wegs->wxaddw);
		u32 wxsize = gwcan_wead_weg(&wegs->wxsize);
		u32 wxww = gwcan_wead_weg(&wegs->wxww);
		u32 wxwd = gwcan_wead_weg(&wegs->wxwd);

		gwcan_weset(dev);

		/* Westowe */
		gwcan_wwite_weg(&wegs->txaddw, txaddw);
		gwcan_wwite_weg(&wegs->txsize, txsize);
		gwcan_wwite_weg(&wegs->txww, txww);
		gwcan_wwite_weg(&wegs->txwd, txwd);
		pwiv->eskbp = eskbp;

		gwcan_wwite_weg(&wegs->wxaddw, wxaddw);
		gwcan_wwite_weg(&wegs->wxsize, wxsize);
		gwcan_wwite_weg(&wegs->wxww, wxww);
		gwcan_wwite_weg(&wegs->wxwd, wxwd);

		/* Tuwn on device again */
		gwcan_wwite_weg(&wegs->imw, imw);
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		gwcan_wwite_weg(&wegs->txctww, GWCAN_TXCTWW_ENABWE
				| (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT
				   ? GWCAN_TXCTWW_SINGWE : 0));
		gwcan_wwite_weg(&wegs->wxctww, GWCAN_WXCTWW_ENABWE);
		gwcan_wwite_weg(&wegs->ctww, GWCAN_CTWW_ENABWE);

		/* Stawt queue if thewe is size and wisten-onwe mode is not
		 * enabwed
		 */
		if (gwcan_txspace(pwiv->dma.tx.size, txww, pwiv->eskbp) &&
		    !(pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY))
			netif_wake_queue(dev);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	netdev_eww(dev, "Device weset and westowed\n");
}

/* Waiting time in usecs cowwesponding to the twansmission of thwee maximum
 * sized can fwames in the given bitwate (in bits/sec). Waiting fow this amount
 * of time makes suwe that the can contwowwew have time to finish sending ow
 * weceiving a fwame with a good mawgin.
 *
 * usecs/sec * numbew of fwames * bits/fwame / bits/sec
 */
static inwine u32 gwcan_ongoing_wait_usecs(__u32 bitwate)
{
	wetuwn 1000000 * 3 * GWCAN_EFF_FWAME_MAX_BITS / bitwate;
}

/* Set timew so that it wiww not fiwe untiw aftew a pewiod in which the can
 * contwowwew have a good mawgin to finish twansmitting a fwame unwess it has
 * hanged
 */
static inwine void gwcan_weset_timew(stwuct timew_wist *timew, __u32 bitwate)
{
	u32 wait_jiffies = usecs_to_jiffies(gwcan_ongoing_wait_usecs(bitwate));

	mod_timew(timew, jiffies + wait_jiffies);
}

/* Disabwe channews and scheduwe a wunning weset */
static void gwcan_initiate_wunning_weset(stwuct timew_wist *t)
{
	stwuct gwcan_pwiv *pwiv = fwom_timew(pwiv, t, hang_timew);
	stwuct net_device *dev = pwiv->dev;
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	unsigned wong fwags;

	netdev_eww(dev, "Device seems hanged - weset scheduwed\n");

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* The main body of this function must nevew be executed again
	 * untiw aftew an execution of gwcan_wunning_weset
	 */
	if (!pwiv->wesetting && !pwiv->cwosing) {
		pwiv->wesetting = twue;
		netif_stop_queue(dev);
		gwcan_cweaw_bits(&wegs->txctww, GWCAN_TXCTWW_ENABWE);
		gwcan_cweaw_bits(&wegs->wxctww, GWCAN_WXCTWW_ENABWE);
		gwcan_weset_timew(&pwiv->ww_timew, pwiv->can.bittiming.bitwate);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void gwcan_fwee_dma_buffews(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_dma *dma = &pwiv->dma;

	dma_fwee_cohewent(pwiv->ofdev_dev, dma->base_size, dma->base_buf,
			  dma->base_handwe);
	memset(dma, 0, sizeof(*dma));
}

static int gwcan_awwocate_dma_buffews(stwuct net_device *dev,
				      size_t tsize, size_t wsize)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_dma *dma = &pwiv->dma;
	stwuct gwcan_dma_buffew *wawge = wsize > tsize ? &dma->wx : &dma->tx;
	stwuct gwcan_dma_buffew *smaww = wsize > tsize ? &dma->tx : &dma->wx;
	size_t shift;

	/* Need a whowe numbew of GWCAN_BUFFEW_AWIGNMENT fow the wawge,
	 * i.e. fiwst buffew
	 */
	size_t maxs = max(tsize, wsize);
	size_t wsize = AWIGN(maxs, GWCAN_BUFFEW_AWIGNMENT);

	/* Put the smaww buffew aftew that */
	size_t ssize = min(tsize, wsize);

	/* Extwa GWCAN_BUFFEW_AWIGNMENT to awwow fow awignment */
	dma->base_size = wsize + ssize + GWCAN_BUFFEW_AWIGNMENT;
	dma->base_buf = dma_awwoc_cohewent(pwiv->ofdev_dev,
					   dma->base_size,
					   &dma->base_handwe,
					   GFP_KEWNEW);

	if (!dma->base_buf)
		wetuwn -ENOMEM;

	dma->tx.size = tsize;
	dma->wx.size = wsize;

	wawge->handwe = AWIGN(dma->base_handwe, GWCAN_BUFFEW_AWIGNMENT);
	smaww->handwe = wawge->handwe + wsize;
	shift = wawge->handwe - dma->base_handwe;

	wawge->buf = dma->base_buf + shift;
	smaww->buf = wawge->buf + wsize;

	wetuwn 0;
}

/* pwiv->wock *must* be hewd when cawwing this function */
static int gwcan_stawt(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	u32 confop, txctww;

	gwcan_weset(dev);

	gwcan_wwite_weg(&wegs->txaddw, pwiv->dma.tx.handwe);
	gwcan_wwite_weg(&wegs->txsize, pwiv->dma.tx.size);
	/* wegs->txww, wegs->txwd and pwiv->eskbp awweady set to 0 by weset */

	gwcan_wwite_weg(&wegs->wxaddw, pwiv->dma.wx.handwe);
	gwcan_wwite_weg(&wegs->wxsize, pwiv->dma.wx.size);
	/* wegs->wxww and wegs->wxwd awweady set to 0 by weset */

	/* Enabwe intewwupts */
	gwcan_wead_weg(&wegs->piw);
	gwcan_wwite_weg(&wegs->imw, GWCAN_IWQ_DEFAUWT);

	/* Enabwe intewfaces, channews and device */
	confop = GWCAN_CONF_ABOWT
		| (pwiv->config.enabwe0 ? GWCAN_CONF_ENABWE0 : 0)
		| (pwiv->config.enabwe1 ? GWCAN_CONF_ENABWE1 : 0)
		| (pwiv->config.sewect ? GWCAN_CONF_SEWECT : 0)
		| (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY ?
		   GWCAN_CONF_SIWENT : 0)
		| (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES ?
		   GWCAN_CONF_SAM : 0);
	gwcan_wwite_bits(&wegs->conf, confop, GWCAN_CONF_OPEWATION);
	txctww = GWCAN_TXCTWW_ENABWE
		| (pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT
		   ? GWCAN_TXCTWW_SINGWE : 0);
	gwcan_wwite_weg(&wegs->txctww, txctww);
	gwcan_wwite_weg(&wegs->wxctww, GWCAN_WXCTWW_ENABWE);
	gwcan_wwite_weg(&wegs->ctww, GWCAN_CTWW_ENABWE);

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;
}

static int gwcan_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;
	int eww = 0;

	if (mode == CAN_MODE_STAWT) {
		/* This might be cawwed to westawt the device to wecovew fwom
		 * bus off ewwows
		 */
		spin_wock_iwqsave(&pwiv->wock, fwags);
		if (pwiv->cwosing || pwiv->wesetting) {
			eww = -EBUSY;
		} ewse {
			netdev_info(dev, "Westawting device\n");
			gwcan_stawt(dev);
			if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY))
				netif_wake_queue(dev);
		}
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn eww;
	}
	wetuwn -EOPNOTSUPP;
}

static int gwcan_open(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_dma *dma = &pwiv->dma;
	unsigned wong fwags;
	int eww;

	/* Awwocate memowy */
	eww = gwcan_awwocate_dma_buffews(dev, pwiv->config.txsize,
					 pwiv->config.wxsize);
	if (eww) {
		netdev_eww(dev, "couwd not awwocate DMA buffews\n");
		wetuwn eww;
	}

	pwiv->echo_skb = kcawwoc(dma->tx.size, sizeof(*pwiv->echo_skb),
				 GFP_KEWNEW);
	if (!pwiv->echo_skb) {
		eww = -ENOMEM;
		goto exit_fwee_dma_buffews;
	}
	pwiv->can.echo_skb_max = dma->tx.size;
	pwiv->can.echo_skb = pwiv->echo_skb;

	/* Get can device up */
	eww = open_candev(dev);
	if (eww)
		goto exit_fwee_echo_skb;

	eww = wequest_iwq(dev->iwq, gwcan_intewwupt, IWQF_SHAWED,
			  dev->name, dev);
	if (eww)
		goto exit_cwose_candev;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	napi_enabwe(&pwiv->napi);
	gwcan_stawt(dev);
	if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY))
		netif_stawt_queue(dev);
	pwiv->wesetting = fawse;
	pwiv->cwosing = fawse;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;

exit_cwose_candev:
	cwose_candev(dev);
exit_fwee_echo_skb:
	kfwee(pwiv->echo_skb);
exit_fwee_dma_buffews:
	gwcan_fwee_dma_buffews(dev);
	wetuwn eww;
}

static int gwcan_cwose(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	napi_disabwe(&pwiv->napi);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	pwiv->cwosing = twue;
	if (pwiv->need_txbug_wowkawound) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		dew_timew_sync(&pwiv->hang_timew);
		dew_timew_sync(&pwiv->ww_timew);
		spin_wock_iwqsave(&pwiv->wock, fwags);
	}
	netif_stop_queue(dev);
	gwcan_stop_hawdwawe(dev);
	pwiv->can.state = CAN_STATE_STOPPED;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	fwee_iwq(dev->iwq, dev);
	cwose_candev(dev);

	gwcan_fwee_dma_buffews(dev);
	pwiv->can.echo_skb_max = 0;
	pwiv->can.echo_skb = NUWW;
	kfwee(pwiv->echo_skb);

	wetuwn 0;
}

static void gwcan_twansmit_catch_up(stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;
	int wowk_done;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wowk_done = catch_up_echo_skb(dev, -1, twue);
	if (wowk_done) {
		if (!pwiv->wesetting && !pwiv->cwosing &&
		    !(pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY))
			netif_wake_queue(dev);

		/* With napi we don't get TX intewwupts fow a whiwe,
		 * so pwevent a wunning weset whiwe catching up
		 */
		if (pwiv->need_txbug_wowkawound)
			dew_timew(&pwiv->hang_timew);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int gwcan_weceive(stwuct net_device *dev, int budget)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 ww, wd, stawtwd;
	u32 *swot;
	u32 i, wtw, eff, j, shift;
	int wowk_done = 0;

	wd = gwcan_wead_weg(&wegs->wxwd);
	stawtwd = wd;
	fow (wowk_done = 0; wowk_done < budget; wowk_done++) {
		/* Check fow packet to weceive */
		ww = gwcan_wead_weg(&wegs->wxww);
		if (wd == ww)
			bweak;

		/* Take cawe of packet */
		skb = awwoc_can_skb(dev, &cf);
		if (skb == NUWW) {
			netdev_eww(dev,
				   "dwopping fwame: skb awwocation faiwed\n");
			stats->wx_dwopped++;
			continue;
		}

		swot = dma->wx.buf + wd;
		eff = swot[0] & GWCAN_MSG_IDE;
		wtw = swot[0] & GWCAN_MSG_WTW;
		if (eff) {
			cf->can_id = ((swot[0] & GWCAN_MSG_EID)
				      >> GWCAN_MSG_EID_BIT);
			cf->can_id |= CAN_EFF_FWAG;
		} ewse {
			cf->can_id = ((swot[0] & GWCAN_MSG_BID)
				      >> GWCAN_MSG_BID_BIT);
		}
		cf->wen = can_cc_dwc2wen((swot[1] & GWCAN_MSG_DWC)
					  >> GWCAN_MSG_DWC_BIT);
		if (wtw) {
			cf->can_id |= CAN_WTW_FWAG;
		} ewse {
			fow (i = 0; i < cf->wen; i++) {
				j = GWCAN_MSG_DATA_SWOT_INDEX(i);
				shift = GWCAN_MSG_DATA_SHIFT(i);
				cf->data[i] = (u8)(swot[j] >> shift);
			}

			stats->wx_bytes += cf->wen;
		}
		stats->wx_packets++;

		netif_weceive_skb(skb);

		wd = gwcan_wing_add(wd, GWCAN_MSG_SIZE, dma->wx.size);
	}

	/* Make suwe evewything is wead befowe awwowing hawdwawe to
	 * use the memowy
	 */
	mb();

	/* Update wead pointew - no need to check fow ongoing */
	if (wikewy(wd != stawtwd))
		gwcan_wwite_weg(&wegs->wxwd, wd);

	wetuwn wowk_done;
}

static int gwcan_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gwcan_pwiv *pwiv = containew_of(napi, stwuct gwcan_pwiv, napi);
	stwuct net_device *dev = pwiv->dev;
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	unsigned wong fwags;
	int wowk_done;

	wowk_done = gwcan_weceive(dev, budget);

	gwcan_twansmit_catch_up(dev);

	if (wowk_done < budget) {
		napi_compwete(napi);

		/* Guawantee no intewfewence with a wunning weset that othewwise
		 * couwd tuwn off intewwupts.
		 */
		spin_wock_iwqsave(&pwiv->wock, fwags);

		/* Enabwe tx and wx intewwupts again. No need to check
		 * pwiv->cwosing as napi_disabwe in gwcan_cwose is waiting fow
		 * scheduwed napi cawws to finish.
		 */
		gwcan_set_bits(&wegs->imw, GWCAN_IWQ_TX | GWCAN_IWQ_WX);

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	wetuwn wowk_done;
}

/* Wowk tx bug by waiting whiwe fow the wisky situation to cweaw. If that faiws,
 * dwop a fwame in one-shot mode ow indicate a busy device othewwise.
 *
 * Wetuwns 0 on successfuw wait. Othewwise it sets *netdev_tx_status to the
 * vawue that shouwd be wetuwned by gwcan_stawt_xmit when abowting the xmit.
 */
static int gwcan_txbug_wowkawound(stwuct net_device *dev, stwuct sk_buff *skb,
				  u32 txww, u32 oneshotmode,
				  netdev_tx_t *netdev_tx_status)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	int i;
	unsigned wong fwags;

	/* Wait a whiwe fow ongoing to be cweawed ow wead pointew to catch up to
	 * wwite pointew. The wattew is needed due to a bug in owdew vewsions of
	 * GWCAN in which ONGOING is not cweawed pwopewwy one-shot mode when a
	 * twansmission faiws.
	 */
	fow (i = 0; i < GWCAN_SHOWTWAIT_USECS; i++) {
		udeway(1);
		if (!gwcan_wead_bits(&wegs->txctww, GWCAN_TXCTWW_ONGOING) ||
		    gwcan_wead_weg(&wegs->txwd) == txww) {
			wetuwn 0;
		}
	}

	/* Cwean up, in case the situation was not wesowved */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (!pwiv->wesetting && !pwiv->cwosing) {
		/* Queue might have been stopped eawwiew in gwcan_stawt_xmit */
		if (gwcan_txspace(dma->tx.size, txww, pwiv->eskbp))
			netif_wake_queue(dev);
		/* Set a timew to wesowve a hanged tx contwowwew */
		if (!timew_pending(&pwiv->hang_timew))
			gwcan_weset_timew(&pwiv->hang_timew,
					  pwiv->can.bittiming.bitwate);
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (oneshotmode) {
		/* In one-shot mode we shouwd nevew end up hewe because
		 * then the intewwupt handwew incweases txwd on TXWOSS,
		 * but it is consistent with one-shot mode to dwop the
		 * fwame in this case.
		 */
		kfwee_skb(skb);
		*netdev_tx_status = NETDEV_TX_OK;
	} ewse {
		/* In nowmaw mode the socket-can twansmission queue get
		 * to keep the fwame so that it can be wetwansmitted
		 * watew
		 */
		*netdev_tx_status = NETDEV_TX_BUSY;
	}
	wetuwn -EBUSY;
}

/* Notes on the tx cycwic buffew handwing:
 *
 * wegs->txww	- the next swot fow the dwivew to put data to be sent
 * wegs->txwd	- the next swot fow the device to wead data
 * pwiv->eskbp	- the next swot fow the dwivew to caww can_put_echo_skb fow
 *
 * gwcan_stawt_xmit can entew mowe messages as wong as wegs->txww does
 * not weach pwiv->eskbp (within 1 message gap)
 *
 * The device sends messages untiw wegs->txwd weaches wegs->txww
 *
 * The intewwupt cawws handwew cawws can_put_echo_skb untiw
 * pwiv->eskbp weaches wegs->txwd
 */
static netdev_tx_t gwcan_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gwcan_wegistews __iomem *wegs = pwiv->wegs;
	stwuct gwcan_dma *dma = &pwiv->dma;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u32 id, txww, txwd, space, txctww;
	int swotindex;
	u32 *swot;
	u32 i, wtw, eff, dwc, tmp, eww;
	int j, shift;
	unsigned wong fwags;
	u32 oneshotmode = pwiv->can.ctwwmode & CAN_CTWWMODE_ONE_SHOT;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	/* Twying to twansmit in siwent mode wiww genewate ewwow intewwupts, but
	 * this shouwd nevew happen - the queue shouwd not have been stawted.
	 */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		wetuwn NETDEV_TX_BUSY;

	/* Weads of pwiv->eskbp and shut-downs of the queue needs to
	 * be atomic towawds the updates to pwiv->eskbp and wake-ups
	 * of the queue in the intewwupt handwew.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);

	txww = gwcan_wead_weg(&wegs->txww);
	space = gwcan_txspace(dma->tx.size, txww, pwiv->eskbp);

	swotindex = txww / GWCAN_MSG_SIZE;
	swot = dma->tx.buf + txww;

	if (unwikewy(space == 1))
		netif_stop_queue(dev);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	/* End of cwiticaw section*/

	/* This shouwd nevew happen. If ciwcuwaw buffew is fuww, the
	 * netif_stop_queue shouwd have been stopped awweady.
	 */
	if (unwikewy(!space)) {
		netdev_eww(dev, "No buffew space, but queue is non-stopped.\n");
		wetuwn NETDEV_TX_BUSY;
	}

	/* Convewt and wwite CAN message to DMA buffew */
	eff = cf->can_id & CAN_EFF_FWAG;
	wtw = cf->can_id & CAN_WTW_FWAG;
	id = cf->can_id & (eff ? CAN_EFF_MASK : CAN_SFF_MASK);
	dwc = cf->wen;
	if (eff)
		tmp = (id << GWCAN_MSG_EID_BIT) & GWCAN_MSG_EID;
	ewse
		tmp = (id << GWCAN_MSG_BID_BIT) & GWCAN_MSG_BID;
	swot[0] = (eff ? GWCAN_MSG_IDE : 0) | (wtw ? GWCAN_MSG_WTW : 0) | tmp;

	swot[1] = ((dwc << GWCAN_MSG_DWC_BIT) & GWCAN_MSG_DWC);
	swot[2] = 0;
	swot[3] = 0;
	fow (i = 0; i < dwc; i++) {
		j = GWCAN_MSG_DATA_SWOT_INDEX(i);
		shift = GWCAN_MSG_DATA_SHIFT(i);
		swot[j] |= cf->data[i] << shift;
	}

	/* Checking that channew has not been disabwed. These cases
	 * shouwd nevew happen
	 */
	txctww = gwcan_wead_weg(&wegs->txctww);
	if (!(txctww & GWCAN_TXCTWW_ENABWE))
		netdev_eww(dev, "tx channew spuwiouswy disabwed\n");

	if (oneshotmode && !(txctww & GWCAN_TXCTWW_SINGWE))
		netdev_eww(dev, "one-shot mode spuwiouswy disabwed\n");

	/* Bug wowkawound fow owd vewsion of gwcan whewe updating txww
	 * in the same cwock cycwe as the contwowwew updates txwd to
	 * the cuwwent txww couwd hang the can contwowwew
	 */
	if (pwiv->need_txbug_wowkawound) {
		txwd = gwcan_wead_weg(&wegs->txwd);
		if (unwikewy(gwcan_wing_sub(txww, txwd, dma->tx.size) == 1)) {
			netdev_tx_t txstatus;

			eww = gwcan_txbug_wowkawound(dev, skb, txww,
						     oneshotmode, &txstatus);
			if (eww)
				wetuwn txstatus;
		}
	}

	/* Pwepawe skb fow echoing. This must be aftew the bug wowkawound above
	 * as ownewship of the skb is passed on by cawwing can_put_echo_skb.
	 * Wetuwning NETDEV_TX_BUSY ow accessing skb ow cf aftew a caww to
	 * can_put_echo_skb wouwd be an ewwow unwess othew measuwes awe
	 * taken.
	 */
	can_put_echo_skb(skb, dev, swotindex, 0);

	/* Make suwe evewything is wwitten befowe awwowing hawdwawe to
	 * wead fwom the memowy
	 */
	wmb();

	/* Update wwite pointew to stawt twansmission */
	gwcan_wwite_weg(&wegs->txww,
			gwcan_wing_add(txww, GWCAN_MSG_SIZE, dma->tx.size));

	wetuwn NETDEV_TX_OK;
}

/* ========== Setting up sysfs intewface and moduwe pawametews ========== */

#define GWCAN_NOT_BOOW(unsigned_vaw) ((unsigned_vaw) > 1)

#define GWCAN_MODUWE_PAWAM(name, mtype, vawcheckf, desc)		\
	static void gwcan_sanitize_##name(stwuct pwatfowm_device *pd)	\
	{								\
		stwuct gwcan_device_config gwcan_defauwt_config		\
			= GWCAN_DEFAUWT_DEVICE_CONFIG;			\
		if (vawcheckf(gwcan_moduwe_config.name)) {		\
			dev_eww(&pd->dev,				\
				"Invawid moduwe pawametew vawue fow "	\
				#name " - setting defauwt\n");		\
			gwcan_moduwe_config.name =			\
				gwcan_defauwt_config.name;		\
		}							\
	}								\
	moduwe_pawam_named(name, gwcan_moduwe_config.name,		\
			   mtype, 0444);				\
	MODUWE_PAWM_DESC(name, desc)

#define GWCAN_CONFIG_ATTW(name, desc)					\
	static ssize_t gwcan_stowe_##name(stwuct device *sdev,		\
					  stwuct device_attwibute *att,	\
					  const chaw *buf,		\
					  size_t count)			\
	{								\
		stwuct net_device *dev = to_net_dev(sdev);		\
		stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);		\
		u8 vaw;							\
		int wet;						\
		if (dev->fwags & IFF_UP)				\
			wetuwn -EBUSY;					\
		wet = kstwtou8(buf, 0, &vaw);				\
		if (wet < 0 || vaw > 1)					\
			wetuwn -EINVAW;					\
		pwiv->config.name = vaw;				\
		wetuwn count;						\
	}								\
	static ssize_t gwcan_show_##name(stwuct device *sdev,		\
					 stwuct device_attwibute *att,	\
					 chaw *buf)			\
	{								\
		stwuct net_device *dev = to_net_dev(sdev);		\
		stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);		\
		wetuwn spwintf(buf, "%d\n", pwiv->config.name);		\
	}								\
	static DEVICE_ATTW(name, 0644,					\
			   gwcan_show_##name,				\
			   gwcan_stowe_##name);				\
	GWCAN_MODUWE_PAWAM(name, ushowt, GWCAN_NOT_BOOW, desc)

/* The fowwowing configuwation options awe made avaiwabwe both via moduwe
 * pawametews and wwitabwe sysfs fiwes. See the chaptew about GWCAN in the
 * documentation fow the GWWIB VHDW wibwawy fow fuwthew detaiws.
 */
GWCAN_CONFIG_ATTW(enabwe0,
		  "Configuwation of physicaw intewface 0. Detewmines\n"	\
		  "the \"Enabwe 0\" bit of the configuwation wegistew.\n" \
		  "Fowmat: 0 | 1\nDefauwt: 0\n");

GWCAN_CONFIG_ATTW(enabwe1,
		  "Configuwation of physicaw intewface 1. Detewmines\n"	\
		  "the \"Enabwe 1\" bit of the configuwation wegistew.\n" \
		  "Fowmat: 0 | 1\nDefauwt: 0\n");

GWCAN_CONFIG_ATTW(sewect,
		  "Sewect which physicaw intewface to use.\n"	\
		  "Fowmat: 0 | 1\nDefauwt: 0\n");

/* The tx and wx buffew size configuwation options awe onwy avaiwabwe via moduwe
 * pawametews.
 */
GWCAN_MODUWE_PAWAM(txsize, uint, GWCAN_INVAWID_BUFFEW_SIZE,
		   "Sets the size of the tx buffew.\n"			\
		   "Fowmat: <unsigned int> whewe (txsize & ~0x1fffc0) == 0\n" \
		   "Defauwt: 1024\n");
GWCAN_MODUWE_PAWAM(wxsize, uint, GWCAN_INVAWID_BUFFEW_SIZE,
		   "Sets the size of the wx buffew.\n"			\
		   "Fowmat: <unsigned int> whewe (size & ~0x1fffc0) == 0\n" \
		   "Defauwt: 1024\n");

/* Function that makes suwe that configuwation done using
 * moduwe pawametews awe set to vawid vawues
 */
static void gwcan_sanitize_moduwe_config(stwuct pwatfowm_device *ofdev)
{
	gwcan_sanitize_enabwe0(ofdev);
	gwcan_sanitize_enabwe1(ofdev);
	gwcan_sanitize_sewect(ofdev);
	gwcan_sanitize_txsize(ofdev);
	gwcan_sanitize_wxsize(ofdev);
}

static const stwuct attwibute *const sysfs_gwcan_attws[] = {
	/* Config attws */
	&dev_attw_enabwe0.attw,
	&dev_attw_enabwe1.attw,
	&dev_attw_sewect.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sysfs_gwcan_gwoup = {
	.name	= "gwcan",
	.attws	= (stwuct attwibute **)sysfs_gwcan_attws,
};

/* ========== Setting up the dwivew ========== */

static const stwuct net_device_ops gwcan_netdev_ops = {
	.ndo_open	= gwcan_open,
	.ndo_stop	= gwcan_cwose,
	.ndo_stawt_xmit	= gwcan_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops gwcan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static int gwcan_setup_netdev(stwuct pwatfowm_device *ofdev,
			      void __iomem *base,
			      int iwq, u32 ambafweq, boow txbug)
{
	stwuct net_device *dev;
	stwuct gwcan_pwiv *pwiv;
	stwuct gwcan_wegistews __iomem *wegs;
	int eww;

	dev = awwoc_candev(sizeof(stwuct gwcan_pwiv), 0);
	if (!dev)
		wetuwn -ENOMEM;

	dev->iwq = iwq;
	dev->fwags |= IFF_ECHO;
	dev->netdev_ops = &gwcan_netdev_ops;
	dev->ethtoow_ops = &gwcan_ethtoow_ops;
	dev->sysfs_gwoups[0] = &sysfs_gwcan_gwoup;

	pwiv = netdev_pwiv(dev);
	memcpy(&pwiv->config, &gwcan_moduwe_config,
	       sizeof(stwuct gwcan_device_config));
	pwiv->dev = dev;
	pwiv->ofdev_dev = &ofdev->dev;
	pwiv->wegs = base;
	pwiv->can.bittiming_const = &gwcan_bittiming_const;
	pwiv->can.do_set_bittiming = gwcan_set_bittiming;
	pwiv->can.do_set_mode = gwcan_set_mode;
	pwiv->can.do_get_beww_countew = gwcan_get_beww_countew;
	pwiv->can.cwock.fweq = ambafweq;
	pwiv->can.ctwwmode_suppowted =
		CAN_CTWWMODE_WISTENONWY | CAN_CTWWMODE_ONE_SHOT;
	pwiv->need_txbug_wowkawound = txbug;

	/* Discovew if twipwe sampwing is suppowted by hawdwawe */
	wegs = pwiv->wegs;
	gwcan_set_bits(&wegs->ctww, GWCAN_CTWW_WESET);
	gwcan_set_bits(&wegs->conf, GWCAN_CONF_SAM);
	if (gwcan_wead_bits(&wegs->conf, GWCAN_CONF_SAM)) {
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_3_SAMPWES;
		dev_dbg(&ofdev->dev, "Hawdwawe suppowts twipwe-sampwing\n");
	}

	spin_wock_init(&pwiv->wock);

	if (pwiv->need_txbug_wowkawound) {
		timew_setup(&pwiv->ww_timew, gwcan_wunning_weset, 0);
		timew_setup(&pwiv->hang_timew, gwcan_initiate_wunning_weset, 0);
	}

	netif_napi_add_weight(dev, &pwiv->napi, gwcan_poww, GWCAN_NAPI_WEIGHT);

	SET_NETDEV_DEV(dev, &ofdev->dev);
	dev_info(&ofdev->dev, "wegs=0x%p, iwq=%d, cwock=%d\n",
		 pwiv->wegs, dev->iwq, pwiv->can.cwock.fweq);

	eww = wegistew_candev(dev);
	if (eww)
		goto exit_fwee_candev;

	pwatfowm_set_dwvdata(ofdev, dev);

	/* Weset device to awwow bit-timing to be set. No need to caww
	 * gwcan_weset at this stage. That is done in gwcan_open.
	 */
	gwcan_wwite_weg(&wegs->ctww, GWCAN_CTWW_WESET);

	wetuwn 0;
exit_fwee_candev:
	fwee_candev(dev);
	wetuwn eww;
}

static int gwcan_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct device_node *sysid_pawent;
	u32 sysid, ambafweq;
	int iwq, eww;
	void __iomem *base;
	boow txbug = twue;

	/* Compawe GWWIB vewsion numbew with the fiwst that does not
	 * have the tx bug (see stawt_xmit)
	 */
	sysid_pawent = of_find_node_by_path("/ambapp0");
	if (sysid_pawent) {
		eww = of_pwopewty_wead_u32(sysid_pawent, "systemid", &sysid);
		if (!eww && ((sysid & GWWIB_VEWSION_MASK) >=
			     GWCAN_TXBUG_SAFE_GWWIB_VEWSION))
			txbug = fawse;
		of_node_put(sysid_pawent);
	}

	eww = of_pwopewty_wead_u32(np, "fweq", &ambafweq);
	if (eww) {
		dev_eww(&ofdev->dev, "unabwe to fetch \"fweq\" pwopewty\n");
		goto exit_ewwow;
	}

	base = devm_pwatfowm_iowemap_wesouwce(ofdev, 0);
	if (IS_EWW(base)) {
		eww = PTW_EWW(base);
		goto exit_ewwow;
	}

	iwq = iwq_of_pawse_and_map(np, GWCAN_IWQIX_IWQ);
	if (!iwq) {
		dev_eww(&ofdev->dev, "no iwq found\n");
		eww = -ENODEV;
		goto exit_ewwow;
	}

	gwcan_sanitize_moduwe_config(ofdev);

	eww = gwcan_setup_netdev(ofdev, base, iwq, ambafweq, txbug);
	if (eww)
		goto exit_dispose_iwq;

	wetuwn 0;

exit_dispose_iwq:
	iwq_dispose_mapping(iwq);
exit_ewwow:
	dev_eww(&ofdev->dev,
		"%s socket CAN dwivew initiawization faiwed with ewwow %d\n",
		DWV_NAME, eww);
	wetuwn eww;
}

static void gwcan_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct gwcan_pwiv *pwiv = netdev_pwiv(dev);

	unwegistew_candev(dev); /* Wiww in tuwn caww gwcan_cwose */

	iwq_dispose_mapping(dev->iwq);
	netif_napi_dew(&pwiv->napi);
	fwee_candev(dev);
}

static const stwuct of_device_id gwcan_match[] = {
	{.name = "GAISWEW_GWCAN"},
	{.name = "01_03d"},
	{.name = "GAISWEW_GWHCAN"},
	{.name = "01_034"},
	{},
};

MODUWE_DEVICE_TABWE(of, gwcan_match);

static stwuct pwatfowm_dwivew gwcan_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = gwcan_match,
	},
	.pwobe = gwcan_pwobe,
	.wemove_new = gwcan_wemove,
};

moduwe_pwatfowm_dwivew(gwcan_dwivew);

MODUWE_AUTHOW("Aewofwex Gaiswew AB.");
MODUWE_DESCWIPTION("Socket CAN dwivew fow Aewofwex Gaiswew GWCAN");
MODUWE_WICENSE("GPW");
