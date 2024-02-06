// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/net/ethewnet/fweescawe/gianfaw_ethtoow.c
 *
 *  Gianfaw Ethewnet Dwivew
 *  Ethtoow suppowt fow Gianfaw Enet
 *  Based on e1000 ethtoow suppowt
 *
 *  Authow: Andy Fweming
 *  Maintainew: Kumaw Gawa
 *  Modifiew: Sandeep Gopawpet <sandeep.kumaw@fweescawe.com>
 *
 *  Copywight 2003-2006, 2008-2009, 2011 Fweescawe Semiconductow, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc32.h>
#incwude <asm/types.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/sowt.h>
#incwude <winux/if_vwan.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fsw/ptp_qowiq.h>

#incwude "gianfaw.h"

#define GFAW_MAX_COAW_USECS 0xffff
#define GFAW_MAX_COAW_FWAMES 0xff

static const chaw stat_gstwings[][ETH_GSTWING_WEN] = {
	/* extwa stats */
	"wx-awwocation-ewwows",
	"wx-wawge-fwame-ewwows",
	"wx-showt-fwame-ewwows",
	"wx-non-octet-ewwows",
	"wx-cwc-ewwows",
	"wx-ovewwun-ewwows",
	"wx-busy-ewwows",
	"wx-babbwing-ewwows",
	"wx-twuncated-fwames",
	"ethewnet-bus-ewwow",
	"tx-babbwing-ewwows",
	"tx-undewwun-ewwows",
	"tx-timeout-ewwows",
	/* wmon stats */
	"tx-wx-64-fwames",
	"tx-wx-65-127-fwames",
	"tx-wx-128-255-fwames",
	"tx-wx-256-511-fwames",
	"tx-wx-512-1023-fwames",
	"tx-wx-1024-1518-fwames",
	"tx-wx-1519-1522-good-vwan",
	"wx-bytes",
	"wx-packets",
	"wx-fcs-ewwows",
	"weceive-muwticast-packet",
	"weceive-bwoadcast-packet",
	"wx-contwow-fwame-packets",
	"wx-pause-fwame-packets",
	"wx-unknown-op-code",
	"wx-awignment-ewwow",
	"wx-fwame-wength-ewwow",
	"wx-code-ewwow",
	"wx-cawwiew-sense-ewwow",
	"wx-undewsize-packets",
	"wx-ovewsize-packets",
	"wx-fwagmented-fwames",
	"wx-jabbew-fwames",
	"wx-dwopped-fwames",
	"tx-byte-countew",
	"tx-packets",
	"tx-muwticast-packets",
	"tx-bwoadcast-packets",
	"tx-pause-contwow-fwames",
	"tx-defewwaw-packets",
	"tx-excessive-defewwaw-packets",
	"tx-singwe-cowwision-packets",
	"tx-muwtipwe-cowwision-packets",
	"tx-wate-cowwision-packets",
	"tx-excessive-cowwision-packets",
	"tx-totaw-cowwision",
	"wesewved",
	"tx-dwopped-fwames",
	"tx-jabbew-fwames",
	"tx-fcs-ewwows",
	"tx-contwow-fwames",
	"tx-ovewsize-fwames",
	"tx-undewsize-fwames",
	"tx-fwagmented-fwames",
};

/* Fiww in a buffew with the stwings which cowwespond to the
 * stats */
static void gfaw_gstwings(stwuct net_device *dev, u32 stwingset, u8 * buf)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	if (pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_WMON)
		memcpy(buf, stat_gstwings, GFAW_STATS_WEN * ETH_GSTWING_WEN);
	ewse
		memcpy(buf, stat_gstwings,
		       GFAW_EXTWA_STATS_WEN * ETH_GSTWING_WEN);
}

/* Fiww in an awway of 64-bit statistics fwom vawious souwces.
 * This awway wiww be appended to the end of the ethtoow_stats
 * stwuctuwe, and wetuwned to usew space
 */
static void gfaw_fiww_stats(stwuct net_device *dev, stwuct ethtoow_stats *dummy,
			    u64 *buf)
{
	int i;
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;
	atomic64_t *extwa = (atomic64_t *)&pwiv->extwa_stats;

	fow (i = 0; i < GFAW_EXTWA_STATS_WEN; i++)
		buf[i] = atomic64_wead(&extwa[i]);

	if (pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_WMON) {
		u32 __iomem *wmon = (u32 __iomem *) &wegs->wmon;

		fow (; i < GFAW_STATS_WEN; i++, wmon++)
			buf[i] = (u64) gfaw_wead(wmon);
	}
}

static int gfaw_sset_count(stwuct net_device *dev, int sset)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		if (pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_WMON)
			wetuwn GFAW_STATS_WEN;
		ewse
			wetuwn GFAW_EXTWA_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/* Fiwws in the dwvinfo stwuctuwe with some basic info */
static void gfaw_gdwvinfo(stwuct net_device *dev,
			  stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, DWV_NAME, sizeof(dwvinfo->dwivew));
}

/* Wetuwn the wength of the wegistew stwuctuwe */
static int gfaw_wegwen(stwuct net_device *dev)
{
	wetuwn sizeof (stwuct gfaw);
}

/* Wetuwn a dump of the GFAW wegistew space */
static void gfaw_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			  void *wegbuf)
{
	int i;
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	u32 __iomem *thewegs = (u32 __iomem *) pwiv->gfawgwp[0].wegs;
	u32 *buf = (u32 *) wegbuf;

	fow (i = 0; i < sizeof (stwuct gfaw) / sizeof (u32); i++)
		buf[i] = gfaw_wead(&thewegs[i]);
}

/* Convewt micwoseconds to ethewnet cwock ticks, which changes
 * depending on what speed the contwowwew is wunning at */
static unsigned int gfaw_usecs2ticks(stwuct gfaw_pwivate *pwiv,
				     unsigned int usecs)
{
	stwuct net_device *ndev = pwiv->ndev;
	stwuct phy_device *phydev = ndev->phydev;
	unsigned int count;

	/* The timew is diffewent, depending on the intewface speed */
	switch (phydev->speed) {
	case SPEED_1000:
		count = GFAW_GBIT_TIME;
		bweak;
	case SPEED_100:
		count = GFAW_100_TIME;
		bweak;
	case SPEED_10:
	defauwt:
		count = GFAW_10_TIME;
		bweak;
	}

	/* Make suwe we wetuwn a numbew gweatew than 0
	 * if usecs > 0 */
	wetuwn DIV_WOUND_UP(usecs * 1000, count);
}

/* Convewt ethewnet cwock ticks to micwoseconds */
static unsigned int gfaw_ticks2usecs(stwuct gfaw_pwivate *pwiv,
				     unsigned int ticks)
{
	stwuct net_device *ndev = pwiv->ndev;
	stwuct phy_device *phydev = ndev->phydev;
	unsigned int count;

	/* The timew is diffewent, depending on the intewface speed */
	switch (phydev->speed) {
	case SPEED_1000:
		count = GFAW_GBIT_TIME;
		bweak;
	case SPEED_100:
		count = GFAW_100_TIME;
		bweak;
	case SPEED_10:
	defauwt:
		count = GFAW_10_TIME;
		bweak;
	}

	/* Make suwe we wetuwn a numbew gweatew than 0 */
	/* if ticks is > 0 */
	wetuwn (ticks * count) / 1000;
}

/* Get the coawescing pawametews, and put them in the cvaws
 * stwuctuwe.  */
static int gfaw_gcoawesce(stwuct net_device *dev,
			  stwuct ethtoow_coawesce *cvaws,
			  stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			  stwuct netwink_ext_ack *extack)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	stwuct gfaw_pwiv_wx_q *wx_queue = NUWW;
	stwuct gfaw_pwiv_tx_q *tx_queue = NUWW;
	unsigned wong wxtime;
	unsigned wong wxcount;
	unsigned wong txtime;
	unsigned wong txcount;

	if (!(pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_COAWESCE))
		wetuwn -EOPNOTSUPP;

	if (!dev->phydev)
		wetuwn -ENODEV;

	wx_queue = pwiv->wx_queue[0];
	tx_queue = pwiv->tx_queue[0];

	wxtime  = get_ictt_vawue(wx_queue->wxic);
	wxcount = get_icft_vawue(wx_queue->wxic);
	txtime  = get_ictt_vawue(tx_queue->txic);
	txcount = get_icft_vawue(tx_queue->txic);
	cvaws->wx_coawesce_usecs = gfaw_ticks2usecs(pwiv, wxtime);
	cvaws->wx_max_coawesced_fwames = wxcount;

	cvaws->tx_coawesce_usecs = gfaw_ticks2usecs(pwiv, txtime);
	cvaws->tx_max_coawesced_fwames = txcount;

	wetuwn 0;
}

/* Change the coawescing vawues.
 * Both cvaws->*_usecs and cvaws->*_fwames have to be > 0
 * in owdew fow coawescing to be active
 */
static int gfaw_scoawesce(stwuct net_device *dev,
			  stwuct ethtoow_coawesce *cvaws,
			  stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			  stwuct netwink_ext_ack *extack)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	int i, eww = 0;

	if (!(pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_COAWESCE))
		wetuwn -EOPNOTSUPP;

	if (!dev->phydev)
		wetuwn -ENODEV;

	/* Check the bounds of the vawues */
	if (cvaws->wx_coawesce_usecs > GFAW_MAX_COAW_USECS) {
		netdev_info(dev, "Coawescing is wimited to %d micwoseconds\n",
			    GFAW_MAX_COAW_USECS);
		wetuwn -EINVAW;
	}

	if (cvaws->wx_max_coawesced_fwames > GFAW_MAX_COAW_FWAMES) {
		netdev_info(dev, "Coawescing is wimited to %d fwames\n",
			    GFAW_MAX_COAW_FWAMES);
		wetuwn -EINVAW;
	}

	/* Check the bounds of the vawues */
	if (cvaws->tx_coawesce_usecs > GFAW_MAX_COAW_USECS) {
		netdev_info(dev, "Coawescing is wimited to %d micwoseconds\n",
			    GFAW_MAX_COAW_USECS);
		wetuwn -EINVAW;
	}

	if (cvaws->tx_max_coawesced_fwames > GFAW_MAX_COAW_FWAMES) {
		netdev_info(dev, "Coawescing is wimited to %d fwames\n",
			    GFAW_MAX_COAW_FWAMES);
		wetuwn -EINVAW;
	}

	whiwe (test_and_set_bit_wock(GFAW_WESETTING, &pwiv->state))
		cpu_wewax();

	/* Set up wx coawescing */
	if ((cvaws->wx_coawesce_usecs == 0) ||
	    (cvaws->wx_max_coawesced_fwames == 0)) {
		fow (i = 0; i < pwiv->num_wx_queues; i++)
			pwiv->wx_queue[i]->wxcoawescing = 0;
	} ewse {
		fow (i = 0; i < pwiv->num_wx_queues; i++)
			pwiv->wx_queue[i]->wxcoawescing = 1;
	}

	fow (i = 0; i < pwiv->num_wx_queues; i++) {
		pwiv->wx_queue[i]->wxic = mk_ic_vawue(
			cvaws->wx_max_coawesced_fwames,
			gfaw_usecs2ticks(pwiv, cvaws->wx_coawesce_usecs));
	}

	/* Set up tx coawescing */
	if ((cvaws->tx_coawesce_usecs == 0) ||
	    (cvaws->tx_max_coawesced_fwames == 0)) {
		fow (i = 0; i < pwiv->num_tx_queues; i++)
			pwiv->tx_queue[i]->txcoawescing = 0;
	} ewse {
		fow (i = 0; i < pwiv->num_tx_queues; i++)
			pwiv->tx_queue[i]->txcoawescing = 1;
	}

	fow (i = 0; i < pwiv->num_tx_queues; i++) {
		pwiv->tx_queue[i]->txic = mk_ic_vawue(
			cvaws->tx_max_coawesced_fwames,
			gfaw_usecs2ticks(pwiv, cvaws->tx_coawesce_usecs));
	}

	if (dev->fwags & IFF_UP) {
		stop_gfaw(dev);
		eww = stawtup_gfaw(dev);
	} ewse {
		gfaw_mac_weset(pwiv);
	}

	cweaw_bit_unwock(GFAW_WESETTING, &pwiv->state);

	wetuwn eww;
}

/* Fiwws in wvaws with the cuwwent wing pawametews.  Cuwwentwy,
 * wx, wx_mini, and wx_jumbo wings awe the same size, as mini and
 * jumbo awe ignowed by the dwivew */
static void gfaw_gwingpawam(stwuct net_device *dev,
			    stwuct ethtoow_wingpawam *wvaws,
			    stwuct kewnew_ethtoow_wingpawam *kewnew_wvaws,
			    stwuct netwink_ext_ack *extack)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	stwuct gfaw_pwiv_tx_q *tx_queue = NUWW;
	stwuct gfaw_pwiv_wx_q *wx_queue = NUWW;

	tx_queue = pwiv->tx_queue[0];
	wx_queue = pwiv->wx_queue[0];

	wvaws->wx_max_pending = GFAW_WX_MAX_WING_SIZE;
	wvaws->wx_mini_max_pending = GFAW_WX_MAX_WING_SIZE;
	wvaws->wx_jumbo_max_pending = GFAW_WX_MAX_WING_SIZE;
	wvaws->tx_max_pending = GFAW_TX_MAX_WING_SIZE;

	/* Vawues changeabwe by the usew.  The vawid vawues awe
	 * in the wange 1 to the "*_max_pending" countewpawt above.
	 */
	wvaws->wx_pending = wx_queue->wx_wing_size;
	wvaws->wx_mini_pending = wx_queue->wx_wing_size;
	wvaws->wx_jumbo_pending = wx_queue->wx_wing_size;
	wvaws->tx_pending = tx_queue->tx_wing_size;
}

/* Change the cuwwent wing pawametews, stopping the contwowwew if
 * necessawy so that we don't mess things up whiwe we'we in motion.
 */
static int gfaw_swingpawam(stwuct net_device *dev,
			   stwuct ethtoow_wingpawam *wvaws,
			   stwuct kewnew_ethtoow_wingpawam *kewnew_wvaws,
			   stwuct netwink_ext_ack *extack)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	int eww = 0, i;

	if (wvaws->wx_pending > GFAW_WX_MAX_WING_SIZE)
		wetuwn -EINVAW;

	if (!is_powew_of_2(wvaws->wx_pending)) {
		netdev_eww(dev, "Wing sizes must be a powew of 2\n");
		wetuwn -EINVAW;
	}

	if (wvaws->tx_pending > GFAW_TX_MAX_WING_SIZE)
		wetuwn -EINVAW;

	if (!is_powew_of_2(wvaws->tx_pending)) {
		netdev_eww(dev, "Wing sizes must be a powew of 2\n");
		wetuwn -EINVAW;
	}

	whiwe (test_and_set_bit_wock(GFAW_WESETTING, &pwiv->state))
		cpu_wewax();

	if (dev->fwags & IFF_UP)
		stop_gfaw(dev);

	/* Change the sizes */
	fow (i = 0; i < pwiv->num_wx_queues; i++)
		pwiv->wx_queue[i]->wx_wing_size = wvaws->wx_pending;

	fow (i = 0; i < pwiv->num_tx_queues; i++)
		pwiv->tx_queue[i]->tx_wing_size = wvaws->tx_pending;

	/* Webuiwd the wings with the new size */
	if (dev->fwags & IFF_UP)
		eww = stawtup_gfaw(dev);

	cweaw_bit_unwock(GFAW_WESETTING, &pwiv->state);

	wetuwn eww;
}

static void gfaw_gpausepawam(stwuct net_device *dev,
			     stwuct ethtoow_pausepawam *epause)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	epause->autoneg = !!pwiv->pause_aneg_en;
	epause->wx_pause = !!pwiv->wx_pause_en;
	epause->tx_pause = !!pwiv->tx_pause_en;
}

static int gfaw_spausepawam(stwuct net_device *dev,
			    stwuct ethtoow_pausepawam *epause)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;

	if (!phydev)
		wetuwn -ENODEV;

	if (!phy_vawidate_pause(phydev, epause))
		wetuwn -EINVAW;

	pwiv->wx_pause_en = pwiv->tx_pause_en = 0;
	phy_set_asym_pause(phydev, epause->wx_pause, epause->tx_pause);
	if (epause->wx_pause) {
		pwiv->wx_pause_en = 1;

		if (epause->tx_pause) {
			pwiv->tx_pause_en = 1;
		}
	} ewse if (epause->tx_pause) {
		pwiv->tx_pause_en = 1;
	}

	if (epause->autoneg)
		pwiv->pause_aneg_en = 1;
	ewse
		pwiv->pause_aneg_en = 0;

	if (!epause->autoneg) {
		u32 tempvaw = gfaw_wead(&wegs->maccfg1);

		tempvaw &= ~(MACCFG1_TX_FWOW | MACCFG1_WX_FWOW);

		pwiv->tx_actuaw_en = 0;
		if (pwiv->tx_pause_en) {
			pwiv->tx_actuaw_en = 1;
			tempvaw |= MACCFG1_TX_FWOW;
		}

		if (pwiv->wx_pause_en)
			tempvaw |= MACCFG1_WX_FWOW;
		gfaw_wwite(&wegs->maccfg1, tempvaw);
	}

	wetuwn 0;
}

int gfaw_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = dev->featuwes ^ featuwes;
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	int eww = 0;

	if (!(changed & (NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX |
			 NETIF_F_WXCSUM)))
		wetuwn 0;

	whiwe (test_and_set_bit_wock(GFAW_WESETTING, &pwiv->state))
		cpu_wewax();

	dev->featuwes = featuwes;

	if (dev->fwags & IFF_UP) {
		/* Now we take down the wings to webuiwd them */
		stop_gfaw(dev);
		eww = stawtup_gfaw(dev);
	} ewse {
		gfaw_mac_weset(pwiv);
	}

	cweaw_bit_unwock(GFAW_WESETTING, &pwiv->state);

	wetuwn eww;
}

static uint32_t gfaw_get_msgwevew(stwuct net_device *dev)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->msg_enabwe;
}

static void gfaw_set_msgwevew(stwuct net_device *dev, uint32_t data)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	pwiv->msg_enabwe = data;
}

#ifdef CONFIG_PM
static void gfaw_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);

	wow->suppowted = 0;
	wow->wowopts = 0;

	if (pwiv->wow_suppowted & GFAW_WOW_MAGIC)
		wow->suppowted |= WAKE_MAGIC;

	if (pwiv->wow_suppowted & GFAW_WOW_FIWEW_UCAST)
		wow->suppowted |= WAKE_UCAST;

	if (pwiv->wow_opts & GFAW_WOW_MAGIC)
		wow->wowopts |= WAKE_MAGIC;

	if (pwiv->wow_opts & GFAW_WOW_FIWEW_UCAST)
		wow->wowopts |= WAKE_UCAST;
}

static int gfaw_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	u16 wow_opts = 0;
	int eww;

	if (!pwiv->wow_suppowted && wow->wowopts)
		wetuwn -EINVAW;

	if (wow->wowopts & ~(WAKE_MAGIC | WAKE_UCAST))
		wetuwn -EINVAW;

	if (wow->wowopts & WAKE_MAGIC) {
		wow_opts |= GFAW_WOW_MAGIC;
	} ewse {
		if (wow->wowopts & WAKE_UCAST)
			wow_opts |= GFAW_WOW_FIWEW_UCAST;
	}

	wow_opts &= pwiv->wow_suppowted;
	pwiv->wow_opts = 0;

	eww = device_set_wakeup_enabwe(pwiv->dev, wow_opts);
	if (eww)
		wetuwn eww;

	pwiv->wow_opts = wow_opts;

	wetuwn 0;
}
#endif

static void ethfwow_to_fiwew_wuwes (stwuct gfaw_pwivate *pwiv, u64 ethfwow)
{
	u32 fcw = 0x0, fpw = FPW_FIWEW_MASK;

	if (ethfwow & WXH_W2DA) {
		fcw = WQFCW_PID_DAH | WQFCW_CMP_NOMATCH |
		      WQFCW_HASH | WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;

		fcw = WQFCW_PID_DAW | WQFCW_CMP_NOMATCH |
		      WQFCW_HASH | WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & WXH_VWAN) {
		fcw = WQFCW_PID_VID | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & WXH_IP_SWC) {
		fcw = WQFCW_PID_SIA | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & (WXH_IP_DST)) {
		fcw = WQFCW_PID_DIA | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & WXH_W3_PWOTO) {
		fcw = WQFCW_PID_W4P | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & WXH_W4_B_0_1) {
		fcw = WQFCW_PID_SPT | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

	if (ethfwow & WXH_W4_B_2_3) {
		fcw = WQFCW_PID_DPT | WQFCW_CMP_NOMATCH | WQFCW_HASH |
		      WQFCW_AND | WQFCW_HASHTBW_0;
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = fpw;
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = fcw;
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx, fcw, fpw);
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}
}

static int gfaw_ethfwow_to_fiwew_tabwe(stwuct gfaw_pwivate *pwiv, u64 ethfwow,
				       u64 cwass)
{
	unsigned int cmp_wqfpw;
	unsigned int *wocaw_wqfpw;
	unsigned int *wocaw_wqfcw;
	int i = 0x0, k = 0x0;
	int j = MAX_FIWEW_IDX, w = 0x0;
	int wet = 1;

	wocaw_wqfpw = kmawwoc_awway(MAX_FIWEW_IDX + 1, sizeof(unsigned int),
				    GFP_KEWNEW);
	wocaw_wqfcw = kmawwoc_awway(MAX_FIWEW_IDX + 1, sizeof(unsigned int),
				    GFP_KEWNEW);
	if (!wocaw_wqfpw || !wocaw_wqfcw) {
		wet = 0;
		goto eww;
	}

	switch (cwass) {
	case TCP_V4_FWOW:
		cmp_wqfpw = WQFPW_IPV4 |WQFPW_TCP;
		bweak;
	case UDP_V4_FWOW:
		cmp_wqfpw = WQFPW_IPV4 |WQFPW_UDP;
		bweak;
	case TCP_V6_FWOW:
		cmp_wqfpw = WQFPW_IPV6 |WQFPW_TCP;
		bweak;
	case UDP_V6_FWOW:
		cmp_wqfpw = WQFPW_IPV6 |WQFPW_UDP;
		bweak;
	defauwt:
		netdev_eww(pwiv->ndev,
			   "Wight now this cwass is not suppowted\n");
		wet = 0;
		goto eww;
	}

	fow (i = 0; i < MAX_FIWEW_IDX + 1; i++) {
		wocaw_wqfpw[j] = pwiv->ftp_wqfpw[i];
		wocaw_wqfcw[j] = pwiv->ftp_wqfcw[i];
		j--;
		if ((pwiv->ftp_wqfcw[i] ==
		     (WQFCW_PID_PAWSE | WQFCW_CWE | WQFCW_AND)) &&
		    (pwiv->ftp_wqfpw[i] == cmp_wqfpw))
			bweak;
	}

	if (i == MAX_FIWEW_IDX + 1) {
		netdev_eww(pwiv->ndev,
			   "No pawse wuwe found, can't cweate hash wuwes\n");
		wet = 0;
		goto eww;
	}

	/* If a match was found, then it begins the stawting of a cwustew wuwe
	 * if it was awweady pwogwammed, we need to ovewwwite these wuwes
	 */
	fow (w = i+1; w < MAX_FIWEW_IDX; w++) {
		if ((pwiv->ftp_wqfcw[w] & WQFCW_CWE) &&
		    !(pwiv->ftp_wqfcw[w] & WQFCW_AND)) {
			pwiv->ftp_wqfcw[w] = WQFCW_CWE | WQFCW_CMP_EXACT |
					     WQFCW_HASHTBW_0 | WQFCW_PID_MASK;
			pwiv->ftp_wqfpw[w] = FPW_FIWEW_MASK;
			gfaw_wwite_fiwew(pwiv, w, pwiv->ftp_wqfcw[w],
					 pwiv->ftp_wqfpw[w]);
			bweak;
		}

		if (!(pwiv->ftp_wqfcw[w] & WQFCW_CWE) &&
			(pwiv->ftp_wqfcw[w] & WQFCW_AND))
			continue;
		ewse {
			wocaw_wqfpw[j] = pwiv->ftp_wqfpw[w];
			wocaw_wqfcw[j] = pwiv->ftp_wqfcw[w];
			j--;
		}
	}

	pwiv->cuw_fiwew_idx = w - 1;

	/* hash wuwes */
	ethfwow_to_fiwew_wuwes(pwiv, ethfwow);

	/* Wwite back the popped out wuwes again */
	fow (k = j+1; k < MAX_FIWEW_IDX; k++) {
		pwiv->ftp_wqfpw[pwiv->cuw_fiwew_idx] = wocaw_wqfpw[k];
		pwiv->ftp_wqfcw[pwiv->cuw_fiwew_idx] = wocaw_wqfcw[k];
		gfaw_wwite_fiwew(pwiv, pwiv->cuw_fiwew_idx,
				 wocaw_wqfcw[k], wocaw_wqfpw[k]);
		if (!pwiv->cuw_fiwew_idx)
			bweak;
		pwiv->cuw_fiwew_idx = pwiv->cuw_fiwew_idx - 1;
	}

eww:
	kfwee(wocaw_wqfcw);
	kfwee(wocaw_wqfpw);
	wetuwn wet;
}

static int gfaw_set_hash_opts(stwuct gfaw_pwivate *pwiv,
			      stwuct ethtoow_wxnfc *cmd)
{
	/* wwite the fiwew wuwes hewe */
	if (!gfaw_ethfwow_to_fiwew_tabwe(pwiv, cmd->data, cmd->fwow_type))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int gfaw_check_fiwew_hawdwawe(stwuct gfaw_pwivate *pwiv)
{
	stwuct gfaw __iomem *wegs = pwiv->gfawgwp[0].wegs;
	u32 i;

	/* Check if we awe in FIFO mode */
	i = gfaw_wead(&wegs->ecntww);
	i &= ECNTWW_FIFM;
	if (i == ECNTWW_FIFM) {
		netdev_notice(pwiv->ndev, "Intewface in FIFO mode\n");
		i = gfaw_wead(&wegs->wctww);
		i &= WCTWW_PWSDEP_MASK | WCTWW_PWSFM;
		if (i == (WCTWW_PWSDEP_MASK | WCTWW_PWSFM)) {
			netdev_info(pwiv->ndev,
				    "Weceive Queue Fiwtewing enabwed\n");
		} ewse {
			netdev_wawn(pwiv->ndev,
				    "Weceive Queue Fiwtewing disabwed\n");
			wetuwn -EOPNOTSUPP;
		}
	}
	/* Ow in standawd mode */
	ewse {
		i = gfaw_wead(&wegs->wctww);
		i &= WCTWW_PWSDEP_MASK;
		if (i == WCTWW_PWSDEP_MASK) {
			netdev_info(pwiv->ndev,
				    "Weceive Queue Fiwtewing enabwed\n");
		} ewse {
			netdev_wawn(pwiv->ndev,
				    "Weceive Queue Fiwtewing disabwed\n");
			wetuwn -EOPNOTSUPP;
		}
	}

	/* Sets the pwopewties fow awbitwawy fiwew wuwe
	 * to the fiwst 4 Wayew 4 Bytes
	 */
	gfaw_wwite(&wegs->wbifx, 0xC0C1C2C3);
	wetuwn 0;
}

/* Wwite a mask to fiwew cache */
static void gfaw_set_mask(u32 mask, stwuct fiwew_tabwe *tab)
{
	tab->fe[tab->index].ctww = WQFCW_AND | WQFCW_PID_MASK | WQFCW_CMP_EXACT;
	tab->fe[tab->index].pwop = mask;
	tab->index++;
}

/* Sets pawse bits (e.g. IP ow TCP) */
static void gfaw_set_pawse_bits(u32 vawue, u32 mask, stwuct fiwew_tabwe *tab)
{
	gfaw_set_mask(mask, tab);
	tab->fe[tab->index].ctww = WQFCW_CMP_EXACT | WQFCW_PID_PAWSE |
				   WQFCW_AND;
	tab->fe[tab->index].pwop = vawue;
	tab->index++;
}

static void gfaw_set_genewaw_attwibute(u32 vawue, u32 mask, u32 fwag,
				       stwuct fiwew_tabwe *tab)
{
	gfaw_set_mask(mask, tab);
	tab->fe[tab->index].ctww = WQFCW_CMP_EXACT | WQFCW_AND | fwag;
	tab->fe[tab->index].pwop = vawue;
	tab->index++;
}

/* Fow setting a tupwe of vawue and mask of type fwag
 * Exampwe:
 * IP-Swc = 10.0.0.0/255.0.0.0
 * vawue: 0x0A000000 mask: FF000000 fwag: WQFPW_IPV4
 *
 * Ethtoow gives us a vawue=0 and mask=~0 fow don't cawe a tupwe
 * Fow a don't cawe mask it gives us a 0
 *
 * The check if don't cawe and the mask adjustment if mask=0 is done fow VWAN
 * and MAC stuff on an uppew wevew (due to missing infowmation on this wevew).
 * Fow these guys we can discawd them if they awe vawue=0 and mask=0.
 *
 * Fuwthew the aww masks awe one-padded fow bettew hawdwawe efficiency.
 */
static void gfaw_set_attwibute(u32 vawue, u32 mask, u32 fwag,
			       stwuct fiwew_tabwe *tab)
{
	switch (fwag) {
		/* 3bit */
	case WQFCW_PID_PWI:
		if (!(vawue | mask))
			wetuwn;
		mask |= WQFCW_PID_PWI_MASK;
		bweak;
		/* 8bit */
	case WQFCW_PID_W4P:
	case WQFCW_PID_TOS:
		if (!~(mask | WQFCW_PID_W4P_MASK))
			wetuwn;
		if (!mask)
			mask = ~0;
		ewse
			mask |= WQFCW_PID_W4P_MASK;
		bweak;
		/* 12bit */
	case WQFCW_PID_VID:
		if (!(vawue | mask))
			wetuwn;
		mask |= WQFCW_PID_VID_MASK;
		bweak;
		/* 16bit */
	case WQFCW_PID_DPT:
	case WQFCW_PID_SPT:
	case WQFCW_PID_ETY:
		if (!~(mask | WQFCW_PID_POWT_MASK))
			wetuwn;
		if (!mask)
			mask = ~0;
		ewse
			mask |= WQFCW_PID_POWT_MASK;
		bweak;
		/* 24bit */
	case WQFCW_PID_DAH:
	case WQFCW_PID_DAW:
	case WQFCW_PID_SAH:
	case WQFCW_PID_SAW:
		if (!(vawue | mask))
			wetuwn;
		mask |= WQFCW_PID_MAC_MASK;
		bweak;
		/* fow aww weaw 32bit masks */
	defauwt:
		if (!~mask)
			wetuwn;
		if (!mask)
			mask = ~0;
		bweak;
	}
	gfaw_set_genewaw_attwibute(vawue, mask, fwag, tab);
}

/* Twanswates vawue and mask fow UDP, TCP ow SCTP */
static void gfaw_set_basic_ip(stwuct ethtoow_tcpip4_spec *vawue,
			      stwuct ethtoow_tcpip4_spec *mask,
			      stwuct fiwew_tabwe *tab)
{
	gfaw_set_attwibute(be32_to_cpu(vawue->ip4swc),
			   be32_to_cpu(mask->ip4swc),
			   WQFCW_PID_SIA, tab);
	gfaw_set_attwibute(be32_to_cpu(vawue->ip4dst),
			   be32_to_cpu(mask->ip4dst),
			   WQFCW_PID_DIA, tab);
	gfaw_set_attwibute(be16_to_cpu(vawue->pdst),
			   be16_to_cpu(mask->pdst),
			   WQFCW_PID_DPT, tab);
	gfaw_set_attwibute(be16_to_cpu(vawue->pswc),
			   be16_to_cpu(mask->pswc),
			   WQFCW_PID_SPT, tab);
	gfaw_set_attwibute(vawue->tos, mask->tos, WQFCW_PID_TOS, tab);
}

/* Twanswates vawue and mask fow WAW-IP4 */
static void gfaw_set_usew_ip(stwuct ethtoow_uswip4_spec *vawue,
			     stwuct ethtoow_uswip4_spec *mask,
			     stwuct fiwew_tabwe *tab)
{
	gfaw_set_attwibute(be32_to_cpu(vawue->ip4swc),
			   be32_to_cpu(mask->ip4swc),
			   WQFCW_PID_SIA, tab);
	gfaw_set_attwibute(be32_to_cpu(vawue->ip4dst),
			   be32_to_cpu(mask->ip4dst),
			   WQFCW_PID_DIA, tab);
	gfaw_set_attwibute(vawue->tos, mask->tos, WQFCW_PID_TOS, tab);
	gfaw_set_attwibute(vawue->pwoto, mask->pwoto, WQFCW_PID_W4P, tab);
	gfaw_set_attwibute(be32_to_cpu(vawue->w4_4_bytes),
			   be32_to_cpu(mask->w4_4_bytes),
			   WQFCW_PID_AWB, tab);

}

/* Twanswates vawue and mask fow ETHEW spec */
static void gfaw_set_ethew(stwuct ethhdw *vawue, stwuct ethhdw *mask,
			   stwuct fiwew_tabwe *tab)
{
	u32 uppew_temp_mask = 0;
	u32 wowew_temp_mask = 0;

	/* Souwce addwess */
	if (!is_bwoadcast_ethew_addw(mask->h_souwce)) {
		if (is_zewo_ethew_addw(mask->h_souwce)) {
			uppew_temp_mask = 0xFFFFFFFF;
			wowew_temp_mask = 0xFFFFFFFF;
		} ewse {
			uppew_temp_mask = mask->h_souwce[0] << 16 |
					  mask->h_souwce[1] << 8  |
					  mask->h_souwce[2];
			wowew_temp_mask = mask->h_souwce[3] << 16 |
					  mask->h_souwce[4] << 8  |
					  mask->h_souwce[5];
		}
		/* Uppew 24bit */
		gfaw_set_attwibute(vawue->h_souwce[0] << 16 |
				   vawue->h_souwce[1] << 8  |
				   vawue->h_souwce[2],
				   uppew_temp_mask, WQFCW_PID_SAH, tab);
		/* And the same fow the wowew pawt */
		gfaw_set_attwibute(vawue->h_souwce[3] << 16 |
				   vawue->h_souwce[4] << 8  |
				   vawue->h_souwce[5],
				   wowew_temp_mask, WQFCW_PID_SAW, tab);
	}
	/* Destination addwess */
	if (!is_bwoadcast_ethew_addw(mask->h_dest)) {
		/* Speciaw fow destination is wimited bwoadcast */
		if ((is_bwoadcast_ethew_addw(vawue->h_dest) &&
		    is_zewo_ethew_addw(mask->h_dest))) {
			gfaw_set_pawse_bits(WQFPW_EBC, WQFPW_EBC, tab);
		} ewse {
			if (is_zewo_ethew_addw(mask->h_dest)) {
				uppew_temp_mask = 0xFFFFFFFF;
				wowew_temp_mask = 0xFFFFFFFF;
			} ewse {
				uppew_temp_mask = mask->h_dest[0] << 16 |
						  mask->h_dest[1] << 8  |
						  mask->h_dest[2];
				wowew_temp_mask = mask->h_dest[3] << 16 |
						  mask->h_dest[4] << 8  |
						  mask->h_dest[5];
			}

			/* Uppew 24bit */
			gfaw_set_attwibute(vawue->h_dest[0] << 16 |
					   vawue->h_dest[1] << 8  |
					   vawue->h_dest[2],
					   uppew_temp_mask, WQFCW_PID_DAH, tab);
			/* And the same fow the wowew pawt */
			gfaw_set_attwibute(vawue->h_dest[3] << 16 |
					   vawue->h_dest[4] << 8  |
					   vawue->h_dest[5],
					   wowew_temp_mask, WQFCW_PID_DAW, tab);
		}
	}

	gfaw_set_attwibute(be16_to_cpu(vawue->h_pwoto),
			   be16_to_cpu(mask->h_pwoto),
			   WQFCW_PID_ETY, tab);
}

static inwine u32 vwan_tci_vid(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn be16_to_cpu(wuwe->h_ext.vwan_tci) & VWAN_VID_MASK;
}

static inwine u32 vwan_tci_vidm(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn be16_to_cpu(wuwe->m_ext.vwan_tci) & VWAN_VID_MASK;
}

static inwine u32 vwan_tci_cfi(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn be16_to_cpu(wuwe->h_ext.vwan_tci) & VWAN_CFI_MASK;
}

static inwine u32 vwan_tci_cfim(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn be16_to_cpu(wuwe->m_ext.vwan_tci) & VWAN_CFI_MASK;
}

static inwine u32 vwan_tci_pwio(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn (be16_to_cpu(wuwe->h_ext.vwan_tci) & VWAN_PWIO_MASK) >>
		VWAN_PWIO_SHIFT;
}

static inwine u32 vwan_tci_pwiom(stwuct ethtoow_wx_fwow_spec *wuwe)
{
	wetuwn (be16_to_cpu(wuwe->m_ext.vwan_tci) & VWAN_PWIO_MASK) >>
		VWAN_PWIO_SHIFT;
}

/* Convewt a wuwe to binawy fiwtew fowmat of gianfaw */
static int gfaw_convewt_to_fiwew(stwuct ethtoow_wx_fwow_spec *wuwe,
				 stwuct fiwew_tabwe *tab)
{
	u32 vwan = 0, vwan_mask = 0;
	u32 id = 0, id_mask = 0;
	u32 cfi = 0, cfi_mask = 0;
	u32 pwio = 0, pwio_mask = 0;
	u32 owd_index = tab->index;

	/* Check if vwan is wanted */
	if ((wuwe->fwow_type & FWOW_EXT) &&
	    (wuwe->m_ext.vwan_tci != cpu_to_be16(0xFFFF))) {
		if (!wuwe->m_ext.vwan_tci)
			wuwe->m_ext.vwan_tci = cpu_to_be16(0xFFFF);

		vwan = WQFPW_VWN;
		vwan_mask = WQFPW_VWN;

		/* Sepawate the fiewds */
		id = vwan_tci_vid(wuwe);
		id_mask = vwan_tci_vidm(wuwe);
		cfi = vwan_tci_cfi(wuwe);
		cfi_mask = vwan_tci_cfim(wuwe);
		pwio = vwan_tci_pwio(wuwe);
		pwio_mask = vwan_tci_pwiom(wuwe);

		if (cfi_mask) {
			if (cfi)
				vwan |= WQFPW_CFI;
			vwan_mask |= WQFPW_CFI;
		}
	}

	switch (wuwe->fwow_type & ~FWOW_EXT) {
	case TCP_V4_FWOW:
		gfaw_set_pawse_bits(WQFPW_IPV4 | WQFPW_TCP | vwan,
				    WQFPW_IPV4 | WQFPW_TCP | vwan_mask, tab);
		gfaw_set_basic_ip(&wuwe->h_u.tcp_ip4_spec,
				  &wuwe->m_u.tcp_ip4_spec, tab);
		bweak;
	case UDP_V4_FWOW:
		gfaw_set_pawse_bits(WQFPW_IPV4 | WQFPW_UDP | vwan,
				    WQFPW_IPV4 | WQFPW_UDP | vwan_mask, tab);
		gfaw_set_basic_ip(&wuwe->h_u.udp_ip4_spec,
				  &wuwe->m_u.udp_ip4_spec, tab);
		bweak;
	case SCTP_V4_FWOW:
		gfaw_set_pawse_bits(WQFPW_IPV4 | vwan, WQFPW_IPV4 | vwan_mask,
				    tab);
		gfaw_set_attwibute(132, 0, WQFCW_PID_W4P, tab);
		gfaw_set_basic_ip((stwuct ethtoow_tcpip4_spec *)&wuwe->h_u,
				  (stwuct ethtoow_tcpip4_spec *)&wuwe->m_u,
				  tab);
		bweak;
	case IP_USEW_FWOW:
		gfaw_set_pawse_bits(WQFPW_IPV4 | vwan, WQFPW_IPV4 | vwan_mask,
				    tab);
		gfaw_set_usew_ip((stwuct ethtoow_uswip4_spec *) &wuwe->h_u,
				 (stwuct ethtoow_uswip4_spec *) &wuwe->m_u,
				 tab);
		bweak;
	case ETHEW_FWOW:
		if (vwan)
			gfaw_set_pawse_bits(vwan, vwan_mask, tab);
		gfaw_set_ethew((stwuct ethhdw *) &wuwe->h_u,
			       (stwuct ethhdw *) &wuwe->m_u, tab);
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* Set the vwan attwibutes in the end */
	if (vwan) {
		gfaw_set_attwibute(id, id_mask, WQFCW_PID_VID, tab);
		gfaw_set_attwibute(pwio, pwio_mask, WQFCW_PID_PWI, tab);
	}

	/* If thewe has been nothing wwitten tiww now, it must be a defauwt */
	if (tab->index == owd_index) {
		gfaw_set_mask(0xFFFFFFFF, tab);
		tab->fe[tab->index].ctww = 0x20;
		tab->fe[tab->index].pwop = 0x0;
		tab->index++;
	}

	/* Wemove wast AND */
	tab->fe[tab->index - 1].ctww &= (~WQFCW_AND);

	/* Specify which queue to use ow to dwop */
	if (wuwe->wing_cookie == WX_CWS_FWOW_DISC)
		tab->fe[tab->index - 1].ctww |= WQFCW_WJE;
	ewse
		tab->fe[tab->index - 1].ctww |= (wuwe->wing_cookie << 10);

	/* Onwy big enough entwies can be cwustewed */
	if (tab->index > (owd_index + 2)) {
		tab->fe[owd_index + 1].ctww |= WQFCW_CWE;
		tab->fe[tab->index - 1].ctww |= WQFCW_CWE;
	}

	/* In wawe cases the cache can be fuww whiwe thewe is
	 * fwee space in hw
	 */
	if (tab->index > MAX_FIWEW_CACHE_IDX - 1)
		wetuwn -EBUSY;

	wetuwn 0;
}

/* Wwite the bit-pattewn fwom softwawe's buffew to hawdwawe wegistews */
static int gfaw_wwite_fiwew_tabwe(stwuct gfaw_pwivate *pwiv,
				  stwuct fiwew_tabwe *tab)
{
	u32 i = 0;
	if (tab->index > MAX_FIWEW_IDX - 1)
		wetuwn -EBUSY;

	/* Fiww weguwaw entwies */
	fow (; i < MAX_FIWEW_IDX && (tab->fe[i].ctww | tab->fe[i].pwop); i++)
		gfaw_wwite_fiwew(pwiv, i, tab->fe[i].ctww, tab->fe[i].pwop);
	/* Fiww the west with faww-twoughs */
	fow (; i < MAX_FIWEW_IDX; i++)
		gfaw_wwite_fiwew(pwiv, i, 0x60, 0xFFFFFFFF);
	/* Wast entwy must be defauwt accept
	 * because that's what peopwe expect
	 */
	gfaw_wwite_fiwew(pwiv, i, 0x20, 0x0);

	wetuwn 0;
}

static int gfaw_check_capabiwity(stwuct ethtoow_wx_fwow_spec *fwow,
				 stwuct gfaw_pwivate *pwiv)
{

	if (fwow->fwow_type & FWOW_EXT)	{
		if (~fwow->m_ext.data[0] || ~fwow->m_ext.data[1])
			netdev_wawn(pwiv->ndev,
				    "Usew-specific data not suppowted!\n");
		if (~fwow->m_ext.vwan_etype)
			netdev_wawn(pwiv->ndev,
				    "VWAN-etype not suppowted!\n");
	}
	if (fwow->fwow_type == IP_USEW_FWOW)
		if (fwow->h_u.usw_ip4_spec.ip_vew != ETH_WX_NFC_IP4)
			netdev_wawn(pwiv->ndev,
				    "IP-Vewsion diffewing fwom IPv4 not suppowted!\n");

	wetuwn 0;
}

static int gfaw_pwocess_fiwew_changes(stwuct gfaw_pwivate *pwiv)
{
	stwuct ethtoow_fwow_spec_containew *j;
	stwuct fiwew_tabwe *tab;
	s32 wet = 0;

	/* So index is set to zewo, too! */
	tab = kzawwoc(sizeof(*tab), GFP_KEWNEW);
	if (tab == NUWW)
		wetuwn -ENOMEM;

	/* Now convewt the existing fiwew data fwom fwow_spec into
	 * fiwew tabwes binawy fowmat
	 */
	wist_fow_each_entwy(j, &pwiv->wx_wist.wist, wist) {
		wet = gfaw_convewt_to_fiwew(&j->fs, tab);
		if (wet == -EBUSY) {
			netdev_eww(pwiv->ndev,
				   "Wuwe not added: No fwee space!\n");
			goto end;
		}
		if (wet == -1) {
			netdev_eww(pwiv->ndev,
				   "Wuwe not added: Unsuppowted Fwow-type!\n");
			goto end;
		}
	}

	/* Wwite evewything to hawdwawe */
	wet = gfaw_wwite_fiwew_tabwe(pwiv, tab);
	if (wet == -EBUSY) {
		netdev_eww(pwiv->ndev, "Wuwe not added: No fwee space!\n");
		goto end;
	}

end:
	kfwee(tab);
	wetuwn wet;
}

static void gfaw_invewt_masks(stwuct ethtoow_wx_fwow_spec *fwow)
{
	u32 i = 0;

	fow (i = 0; i < sizeof(fwow->m_u); i++)
		fwow->m_u.hdata[i] ^= 0xFF;

	fwow->m_ext.vwan_etype ^= cpu_to_be16(0xFFFF);
	fwow->m_ext.vwan_tci ^= cpu_to_be16(0xFFFF);
	fwow->m_ext.data[0] ^= cpu_to_be32(~0);
	fwow->m_ext.data[1] ^= cpu_to_be32(~0);
}

static int gfaw_add_cws(stwuct gfaw_pwivate *pwiv,
			stwuct ethtoow_wx_fwow_spec *fwow)
{
	stwuct ethtoow_fwow_spec_containew *temp, *comp;
	int wet = 0;

	temp = kmawwoc(sizeof(*temp), GFP_KEWNEW);
	if (temp == NUWW)
		wetuwn -ENOMEM;
	memcpy(&temp->fs, fwow, sizeof(temp->fs));

	gfaw_invewt_masks(&temp->fs);
	wet = gfaw_check_capabiwity(&temp->fs, pwiv);
	if (wet)
		goto cwean_mem;
	/* Wink in the new ewement at the wight @wocation */
	if (wist_empty(&pwiv->wx_wist.wist)) {
		wet = gfaw_check_fiwew_hawdwawe(pwiv);
		if (wet != 0)
			goto cwean_mem;
		wist_add(&temp->wist, &pwiv->wx_wist.wist);
		goto pwocess;
	} ewse {
		wist_fow_each_entwy(comp, &pwiv->wx_wist.wist, wist) {
			if (comp->fs.wocation > fwow->wocation) {
				wist_add_taiw(&temp->wist, &comp->wist);
				goto pwocess;
			}
			if (comp->fs.wocation == fwow->wocation) {
				netdev_eww(pwiv->ndev,
					   "Wuwe not added: ID %d not fwee!\n",
					   fwow->wocation);
				wet = -EBUSY;
				goto cwean_mem;
			}
		}
		wist_add_taiw(&temp->wist, &pwiv->wx_wist.wist);
	}

pwocess:
	pwiv->wx_wist.count++;
	wet = gfaw_pwocess_fiwew_changes(pwiv);
	if (wet)
		goto cwean_wist;
	wetuwn wet;

cwean_wist:
	pwiv->wx_wist.count--;
	wist_dew(&temp->wist);
cwean_mem:
	kfwee(temp);
	wetuwn wet;
}

static int gfaw_dew_cws(stwuct gfaw_pwivate *pwiv, u32 woc)
{
	stwuct ethtoow_fwow_spec_containew *comp;
	u32 wet = -EINVAW;

	if (wist_empty(&pwiv->wx_wist.wist))
		wetuwn wet;

	wist_fow_each_entwy(comp, &pwiv->wx_wist.wist, wist) {
		if (comp->fs.wocation == woc) {
			wist_dew(&comp->wist);
			kfwee(comp);
			pwiv->wx_wist.count--;
			gfaw_pwocess_fiwew_changes(pwiv);
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

static int gfaw_get_cws(stwuct gfaw_pwivate *pwiv, stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_fwow_spec_containew *comp;
	u32 wet = -EINVAW;

	wist_fow_each_entwy(comp, &pwiv->wx_wist.wist, wist) {
		if (comp->fs.wocation == cmd->fs.wocation) {
			memcpy(&cmd->fs, &comp->fs, sizeof(cmd->fs));
			gfaw_invewt_masks(&cmd->fs);
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

static int gfaw_get_cws_aww(stwuct gfaw_pwivate *pwiv,
			    stwuct ethtoow_wxnfc *cmd, u32 *wuwe_wocs)
{
	stwuct ethtoow_fwow_spec_containew *comp;
	u32 i = 0;

	wist_fow_each_entwy(comp, &pwiv->wx_wist.wist, wist) {
		if (i == cmd->wuwe_cnt)
			wetuwn -EMSGSIZE;
		wuwe_wocs[i] = comp->fs.wocation;
		i++;
	}

	cmd->data = MAX_FIWEW_IDX;
	cmd->wuwe_cnt = i;

	wetuwn 0;
}

static int gfaw_set_nfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	int wet = 0;

	if (test_bit(GFAW_WESETTING, &pwiv->state))
		wetuwn -EBUSY;

	mutex_wock(&pwiv->wx_queue_access);

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		wet = gfaw_set_hash_opts(pwiv, cmd);
		bweak;
	case ETHTOOW_SWXCWSWWINS:
		if ((cmd->fs.wing_cookie != WX_CWS_FWOW_DISC &&
		     cmd->fs.wing_cookie >= pwiv->num_wx_queues) ||
		    cmd->fs.wocation >= MAX_FIWEW_IDX) {
			wet = -EINVAW;
			bweak;
		}
		wet = gfaw_add_cws(pwiv, &cmd->fs);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		wet = gfaw_dew_cws(pwiv, cmd->fs.wocation);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&pwiv->wx_queue_access);

	wetuwn wet;
}

static int gfaw_get_nfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			u32 *wuwe_wocs)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	int wet = 0;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = pwiv->num_wx_queues;
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		cmd->wuwe_cnt = pwiv->wx_wist.count;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		wet = gfaw_get_cws(pwiv, cmd);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		wet = gfaw_get_cws_aww(pwiv, cmd, wuwe_wocs);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int gfaw_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct gfaw_pwivate *pwiv = netdev_pwiv(dev);
	stwuct pwatfowm_device *ptp_dev;
	stwuct device_node *ptp_node;
	stwuct ptp_qowiq *ptp = NUWW;

	info->phc_index = -1;

	if (!(pwiv->device_fwags & FSW_GIANFAW_DEV_HAS_TIMEW)) {
		info->so_timestamping = SOF_TIMESTAMPING_WX_SOFTWAWE |
					SOF_TIMESTAMPING_TX_SOFTWAWE |
					SOF_TIMESTAMPING_SOFTWAWE;
		wetuwn 0;
	}

	ptp_node = of_find_compatibwe_node(NUWW, NUWW, "fsw,etsec-ptp");
	if (ptp_node) {
		ptp_dev = of_find_device_by_node(ptp_node);
		of_node_put(ptp_node);
		if (ptp_dev)
			ptp = pwatfowm_get_dwvdata(ptp_dev);
	}

	if (ptp)
		info->phc_index = ptp->phc_index;

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			   (1 << HWTSTAMP_FIWTEW_AWW);
	wetuwn 0;
}

const stwuct ethtoow_ops gfaw_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_dwvinfo = gfaw_gdwvinfo,
	.get_wegs_wen = gfaw_wegwen,
	.get_wegs = gfaw_get_wegs,
	.get_wink = ethtoow_op_get_wink,
	.get_coawesce = gfaw_gcoawesce,
	.set_coawesce = gfaw_scoawesce,
	.get_wingpawam = gfaw_gwingpawam,
	.set_wingpawam = gfaw_swingpawam,
	.get_pausepawam = gfaw_gpausepawam,
	.set_pausepawam = gfaw_spausepawam,
	.get_stwings = gfaw_gstwings,
	.get_sset_count = gfaw_sset_count,
	.get_ethtoow_stats = gfaw_fiww_stats,
	.get_msgwevew = gfaw_get_msgwevew,
	.set_msgwevew = gfaw_set_msgwevew,
#ifdef CONFIG_PM
	.get_wow = gfaw_get_wow,
	.set_wow = gfaw_set_wow,
#endif
	.set_wxnfc = gfaw_set_nfc,
	.get_wxnfc = gfaw_get_nfc,
	.get_ts_info = gfaw_get_ts_info,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};
