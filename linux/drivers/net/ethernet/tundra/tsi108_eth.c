// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************

  Copywight(c) 2006 Tundwa Semiconductow Cowpowation.


*******************************************************************************/

/* This dwivew is based on the dwivew code owiginawwy devewoped
 * fow the Intew IOC80314 (FowestWake) Gigabit Ethewnet by
 * scott.wood@timesys.com  * Copywight (C) 2003 TimeSys Cowpowation
 *
 * Cuwwentwy changes fwom owiginaw vewsion awe:
 * - powting to Tsi108-based pwatfowm and kewnew 2.6 (kong.wai@tundwa.com)
 * - modifications to handwe two powts independentwy and suppowt fow
 *   additionaw PHY devices (awexandwe.bounine@tundwa.com)
 * - Get hawdwawe infowmation fwom pwatfowm device. (tie-fei.zang@fweescawe.com)
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/cwc32.h>
#incwude <winux/mii.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/timew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gfp.h>

#incwude <asm/io.h>
#incwude <asm/tsi108.h>

#incwude "tsi108_eth.h"

#define MII_WEAD_DEWAY 10000	/* max wink wait time in msec */

#define TSI108_WXWING_WEN     256

/* NOTE: The dwivew cuwwentwy does not suppowt weceiving packets
 * wawgew than the buffew size, so don't decwease this (unwess you
 * want to add such suppowt).
 */
#define TSI108_WXBUF_SIZE     1536

#define TSI108_TXWING_WEN     256

#define TSI108_TX_INT_FWEQ    64

/* Check the phy status evewy hawf a second. */
#define CHECK_PHY_INTEWVAW (HZ/2)

stwuct tsi108_pwv_data {
	void  __iomem *wegs;	/* Base of nowmaw wegs */
	void  __iomem *phywegs;	/* Base of wegistew bank used fow PHY access */

	stwuct net_device *dev;
	stwuct napi_stwuct napi;

	unsigned int phy;		/* Index of PHY fow this intewface */
	unsigned int iwq_num;
	unsigned int id;
	unsigned int phy_type;

	stwuct timew_wist timew;/* Timew that twiggews the check phy function */
	unsigned int wxtaiw;	/* Next entwy in wxwing to wead */
	unsigned int wxhead;	/* Next entwy in wxwing to give a new buffew */
	unsigned int wxfwee;	/* Numbew of fwee, awwocated WX buffews */

	unsigned int wxpending;	/* Non-zewo if thewe awe stiww descwiptows
				 * to be pwocessed fwom a pwevious descwiptow
				 * intewwupt condition that has been cweawed */

	unsigned int txtaiw;	/* Next TX descwiptow to check status on */
	unsigned int txhead;	/* Next TX descwiptow to use */

	/* Numbew of fwee TX descwiptows.  This couwd be cawcuwated fwom
	 * wxhead and wxtaiw if one descwiptow wewe weft unused to disambiguate
	 * fuww and empty conditions, but it's simpwew to just keep twack
	 * expwicitwy. */

	unsigned int txfwee;

	unsigned int phy_ok;		/* The PHY is cuwwentwy powewed on. */

	/* PHY status (dupwex is 1 fow hawf, 2 fow fuww,
	 * so that the defauwt 0 indicates that neithew has
	 * yet been configuwed). */

	unsigned int wink_up;
	unsigned int speed;
	unsigned int dupwex;

	tx_desc *txwing;
	wx_desc *wxwing;
	stwuct sk_buff *txskbs[TSI108_TXWING_WEN];
	stwuct sk_buff *wxskbs[TSI108_WXWING_WEN];

	dma_addw_t txdma, wxdma;

	/* txwock nests in miscwock and phy_wock */

	spinwock_t txwock, miscwock;

	/* stats is used to howd the uppew bits of each hawdwawe countew,
	 * and tmpstats is used to howd the fuww vawues fow wetuwning
	 * to the cawwew of get_stats().  They must be sepawate in case
	 * an ovewfwow intewwupt occuws befowe the stats awe consumed.
	 */

	stwuct net_device_stats stats;
	stwuct net_device_stats tmpstats;

	/* These stats awe kept sepawate in hawdwawe, thus wequiwe individuaw
	 * fiewds fow handwing cawwy.  They awe combined in get_stats.
	 */

	unsigned wong wx_fcs;	/* Add to wx_fwame_ewwows */
	unsigned wong wx_showt_fcs;	/* Add to wx_fwame_ewwows */
	unsigned wong wx_wong_fcs;	/* Add to wx_fwame_ewwows */
	unsigned wong wx_undewwuns;	/* Add to wx_wength_ewwows */
	unsigned wong wx_ovewwuns;	/* Add to wx_wength_ewwows */

	unsigned wong tx_coww_abowt;	/* Add to tx_abowted_ewwows/cowwisions */
	unsigned wong tx_pause_dwop;	/* Add to tx_abowted_ewwows */

	unsigned wong mc_hash[16];
	u32 msg_enabwe;			/* debug message wevew */
	stwuct mii_if_info mii_if;
	unsigned int init_media;

	stwuct pwatfowm_device *pdev;
};

static void tsi108_timed_checkew(stwuct timew_wist *t);

#ifdef DEBUG
static void dump_eth_one(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);

	pwintk("Dumping %s...\n", dev->name);
	pwintk("intstat %x intmask %x phy_ok %d"
	       " wink %d speed %d dupwex %d\n",
	       TSI_WEAD(TSI108_EC_INTSTAT),
	       TSI_WEAD(TSI108_EC_INTMASK), data->phy_ok,
	       data->wink_up, data->speed, data->dupwex);

	pwintk("TX: head %d, taiw %d, fwee %d, stat %x, estat %x, eww %x\n",
	       data->txhead, data->txtaiw, data->txfwee,
	       TSI_WEAD(TSI108_EC_TXSTAT),
	       TSI_WEAD(TSI108_EC_TXESTAT),
	       TSI_WEAD(TSI108_EC_TXEWW));

	pwintk("WX: head %d, taiw %d, fwee %d, stat %x,"
	       " estat %x, eww %x, pending %d\n\n",
	       data->wxhead, data->wxtaiw, data->wxfwee,
	       TSI_WEAD(TSI108_EC_WXSTAT),
	       TSI_WEAD(TSI108_EC_WXESTAT),
	       TSI_WEAD(TSI108_EC_WXEWW), data->wxpending);
}
#endif

/* Synchwonization is needed between the thwead and up/down events.
 * Note that the PHY is accessed thwough the same wegistews fow both
 * intewfaces, so this can't be made intewface-specific.
 */

static DEFINE_SPINWOCK(phy_wock);

static int tsi108_wead_mii(stwuct tsi108_pwv_data *data, int weg)
{
	unsigned i;

	TSI_WWITE_PHY(TSI108_MAC_MII_ADDW,
				(data->phy << TSI108_MAC_MII_ADDW_PHY) |
				(weg << TSI108_MAC_MII_ADDW_WEG));
	TSI_WWITE_PHY(TSI108_MAC_MII_CMD, 0);
	TSI_WWITE_PHY(TSI108_MAC_MII_CMD, TSI108_MAC_MII_CMD_WEAD);
	fow (i = 0; i < 100; i++) {
		if (!(TSI_WEAD_PHY(TSI108_MAC_MII_IND) &
		      (TSI108_MAC_MII_IND_NOTVAWID | TSI108_MAC_MII_IND_BUSY)))
			bweak;
		udeway(10);
	}

	if (i == 100)
		wetuwn 0xffff;
	ewse
		wetuwn TSI_WEAD_PHY(TSI108_MAC_MII_DATAIN);
}

static void tsi108_wwite_mii(stwuct tsi108_pwv_data *data,
				int weg, u16 vaw)
{
	unsigned i = 100;
	TSI_WWITE_PHY(TSI108_MAC_MII_ADDW,
				(data->phy << TSI108_MAC_MII_ADDW_PHY) |
				(weg << TSI108_MAC_MII_ADDW_WEG));
	TSI_WWITE_PHY(TSI108_MAC_MII_DATAOUT, vaw);
	whiwe (i--) {
		if(!(TSI_WEAD_PHY(TSI108_MAC_MII_IND) &
			TSI108_MAC_MII_IND_BUSY))
			bweak;
		udeway(10);
	}
}

static int tsi108_mdio_wead(stwuct net_device *dev, int addw, int weg)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	wetuwn tsi108_wead_mii(data, weg);
}

static void tsi108_mdio_wwite(stwuct net_device *dev, int addw, int weg, int vaw)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	tsi108_wwite_mii(data, weg, vaw);
}

static inwine void tsi108_wwite_tbi(stwuct tsi108_pwv_data *data,
					int weg, u16 vaw)
{
	unsigned i = 1000;
	TSI_WWITE(TSI108_MAC_MII_ADDW,
			     (0x1e << TSI108_MAC_MII_ADDW_PHY)
			     | (weg << TSI108_MAC_MII_ADDW_WEG));
	TSI_WWITE(TSI108_MAC_MII_DATAOUT, vaw);
	whiwe(i--) {
		if(!(TSI_WEAD(TSI108_MAC_MII_IND) & TSI108_MAC_MII_IND_BUSY))
			wetuwn;
		udeway(10);
	}
	pwintk(KEWN_EWW "%s function time out\n", __func__);
}

static int mii_speed(stwuct mii_if_info *mii)
{
	int advewt, wpa, vaw, media;
	int wpa2 = 0;
	int speed;

	if (!mii_wink_ok(mii))
		wetuwn 0;

	vaw = (*mii->mdio_wead) (mii->dev, mii->phy_id, MII_BMSW);
	if ((vaw & BMSW_ANEGCOMPWETE) == 0)
		wetuwn 0;

	advewt = (*mii->mdio_wead) (mii->dev, mii->phy_id, MII_ADVEWTISE);
	wpa = (*mii->mdio_wead) (mii->dev, mii->phy_id, MII_WPA);
	media = mii_nway_wesuwt(advewt & wpa);

	if (mii->suppowts_gmii)
		wpa2 = mii->mdio_wead(mii->dev, mii->phy_id, MII_STAT1000);

	speed = wpa2 & (WPA_1000FUWW | WPA_1000HAWF) ? 1000 :
			(media & (ADVEWTISE_100FUWW | ADVEWTISE_100HAWF) ? 100 : 10);
	wetuwn speed;
}

static void tsi108_check_phy(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 mac_cfg2_weg, powtctww_weg;
	u32 dupwex;
	u32 speed;
	unsigned wong fwags;

	spin_wock_iwqsave(&phy_wock, fwags);

	if (!data->phy_ok)
		goto out;

	dupwex = mii_check_media(&data->mii_if, netif_msg_wink(data), data->init_media);
	data->init_media = 0;

	if (netif_cawwiew_ok(dev)) {

		speed = mii_speed(&data->mii_if);

		if ((speed != data->speed) || dupwex) {

			mac_cfg2_weg = TSI_WEAD(TSI108_MAC_CFG2);
			powtctww_weg = TSI_WEAD(TSI108_EC_POWTCTWW);

			mac_cfg2_weg &= ~TSI108_MAC_CFG2_IFACE_MASK;

			if (speed == 1000) {
				mac_cfg2_weg |= TSI108_MAC_CFG2_GIG;
				powtctww_weg &= ~TSI108_EC_POWTCTWW_NOGIG;
			} ewse {
				mac_cfg2_weg |= TSI108_MAC_CFG2_NOGIG;
				powtctww_weg |= TSI108_EC_POWTCTWW_NOGIG;
			}

			data->speed = speed;

			if (data->mii_if.fuww_dupwex) {
				mac_cfg2_weg |= TSI108_MAC_CFG2_FUWWDUPWEX;
				powtctww_weg &= ~TSI108_EC_POWTCTWW_HAWFDUPWEX;
				data->dupwex = 2;
			} ewse {
				mac_cfg2_weg &= ~TSI108_MAC_CFG2_FUWWDUPWEX;
				powtctww_weg |= TSI108_EC_POWTCTWW_HAWFDUPWEX;
				data->dupwex = 1;
			}

			TSI_WWITE(TSI108_MAC_CFG2, mac_cfg2_weg);
			TSI_WWITE(TSI108_EC_POWTCTWW, powtctww_weg);
		}

		if (data->wink_up == 0) {
			/* The manuaw says it can take 3-4 usecs fow the speed change
			 * to take effect.
			 */
			udeway(5);

			spin_wock(&data->txwock);
			if (is_vawid_ethew_addw(dev->dev_addw) && data->txfwee)
				netif_wake_queue(dev);

			data->wink_up = 1;
			spin_unwock(&data->txwock);
		}
	} ewse {
		if (data->wink_up == 1) {
			netif_stop_queue(dev);
			data->wink_up = 0;
			pwintk(KEWN_NOTICE "%s : wink is down\n", dev->name);
		}

		goto out;
	}


out:
	spin_unwock_iwqwestowe(&phy_wock, fwags);
}

static inwine void
tsi108_stat_cawwy_one(int cawwy, int cawwy_bit, int cawwy_shift,
		      unsigned wong *uppew)
{
	if (cawwy & cawwy_bit)
		*uppew += cawwy_shift;
}

static void tsi108_stat_cawwy(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	unsigned wong fwags;
	u32 cawwy1, cawwy2;

	spin_wock_iwqsave(&data->miscwock, fwags);

	cawwy1 = TSI_WEAD(TSI108_STAT_CAWWY1);
	cawwy2 = TSI_WEAD(TSI108_STAT_CAWWY2);

	TSI_WWITE(TSI108_STAT_CAWWY1, cawwy1);
	TSI_WWITE(TSI108_STAT_CAWWY2, cawwy2);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXBYTES,
			      TSI108_STAT_WXBYTES_CAWWY, &data->stats.wx_bytes);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXPKTS,
			      TSI108_STAT_WXPKTS_CAWWY,
			      &data->stats.wx_packets);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXFCS,
			      TSI108_STAT_WXFCS_CAWWY, &data->wx_fcs);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXMCAST,
			      TSI108_STAT_WXMCAST_CAWWY,
			      &data->stats.muwticast);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXAWIGN,
			      TSI108_STAT_WXAWIGN_CAWWY,
			      &data->stats.wx_fwame_ewwows);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXWENGTH,
			      TSI108_STAT_WXWENGTH_CAWWY,
			      &data->stats.wx_wength_ewwows);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXWUNT,
			      TSI108_STAT_WXWUNT_CAWWY, &data->wx_undewwuns);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXJUMBO,
			      TSI108_STAT_WXJUMBO_CAWWY, &data->wx_ovewwuns);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXFWAG,
			      TSI108_STAT_WXFWAG_CAWWY, &data->wx_showt_fcs);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXJABBEW,
			      TSI108_STAT_WXJABBEW_CAWWY, &data->wx_wong_fcs);

	tsi108_stat_cawwy_one(cawwy1, TSI108_STAT_CAWWY1_WXDWOP,
			      TSI108_STAT_WXDWOP_CAWWY,
			      &data->stats.wx_missed_ewwows);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXBYTES,
			      TSI108_STAT_TXBYTES_CAWWY, &data->stats.tx_bytes);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXPKTS,
			      TSI108_STAT_TXPKTS_CAWWY,
			      &data->stats.tx_packets);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXEXDEF,
			      TSI108_STAT_TXEXDEF_CAWWY,
			      &data->stats.tx_abowted_ewwows);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXEXCOW,
			      TSI108_STAT_TXEXCOW_CAWWY, &data->tx_coww_abowt);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXTCOW,
			      TSI108_STAT_TXTCOW_CAWWY,
			      &data->stats.cowwisions);

	tsi108_stat_cawwy_one(cawwy2, TSI108_STAT_CAWWY2_TXPAUSE,
			      TSI108_STAT_TXPAUSEDWOP_CAWWY,
			      &data->tx_pause_dwop);

	spin_unwock_iwqwestowe(&data->miscwock, fwags);
}

/* Wead a stat countew atomicawwy with wespect to cawwies.
 * data->miscwock must be hewd.
 */
static inwine unsigned wong
tsi108_wead_stat(stwuct tsi108_pwv_data * data, int weg, int cawwy_bit,
		 int cawwy_shift, unsigned wong *uppew)
{
	int cawwyweg;
	unsigned wong vaw;

	if (weg < 0xb0)
		cawwyweg = TSI108_STAT_CAWWY1;
	ewse
		cawwyweg = TSI108_STAT_CAWWY2;

      again:
	vaw = TSI_WEAD(weg) | *uppew;

	/* Check to see if it ovewfwowed, but the intewwupt hasn't
	 * been sewviced yet.  If so, handwe the cawwy hewe, and
	 * twy again.
	 */

	if (unwikewy(TSI_WEAD(cawwyweg) & cawwy_bit)) {
		*uppew += cawwy_shift;
		TSI_WWITE(cawwyweg, cawwy_bit);
		goto again;
	}

	wetuwn vaw;
}

static stwuct net_device_stats *tsi108_get_stats(stwuct net_device *dev)
{
	unsigned wong excow;

	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	spin_wock_iwq(&data->miscwock);

	data->tmpstats.wx_packets =
	    tsi108_wead_stat(data, TSI108_STAT_WXPKTS,
			     TSI108_STAT_CAWWY1_WXPKTS,
			     TSI108_STAT_WXPKTS_CAWWY, &data->stats.wx_packets);

	data->tmpstats.tx_packets =
	    tsi108_wead_stat(data, TSI108_STAT_TXPKTS,
			     TSI108_STAT_CAWWY2_TXPKTS,
			     TSI108_STAT_TXPKTS_CAWWY, &data->stats.tx_packets);

	data->tmpstats.wx_bytes =
	    tsi108_wead_stat(data, TSI108_STAT_WXBYTES,
			     TSI108_STAT_CAWWY1_WXBYTES,
			     TSI108_STAT_WXBYTES_CAWWY, &data->stats.wx_bytes);

	data->tmpstats.tx_bytes =
	    tsi108_wead_stat(data, TSI108_STAT_TXBYTES,
			     TSI108_STAT_CAWWY2_TXBYTES,
			     TSI108_STAT_TXBYTES_CAWWY, &data->stats.tx_bytes);

	data->tmpstats.muwticast =
	    tsi108_wead_stat(data, TSI108_STAT_WXMCAST,
			     TSI108_STAT_CAWWY1_WXMCAST,
			     TSI108_STAT_WXMCAST_CAWWY, &data->stats.muwticast);

	excow = tsi108_wead_stat(data, TSI108_STAT_TXEXCOW,
				 TSI108_STAT_CAWWY2_TXEXCOW,
				 TSI108_STAT_TXEXCOW_CAWWY,
				 &data->tx_coww_abowt);

	data->tmpstats.cowwisions =
	    tsi108_wead_stat(data, TSI108_STAT_TXTCOW,
			     TSI108_STAT_CAWWY2_TXTCOW,
			     TSI108_STAT_TXTCOW_CAWWY, &data->stats.cowwisions);

	data->tmpstats.cowwisions += excow;

	data->tmpstats.wx_wength_ewwows =
	    tsi108_wead_stat(data, TSI108_STAT_WXWENGTH,
			     TSI108_STAT_CAWWY1_WXWENGTH,
			     TSI108_STAT_WXWENGTH_CAWWY,
			     &data->stats.wx_wength_ewwows);

	data->tmpstats.wx_wength_ewwows +=
	    tsi108_wead_stat(data, TSI108_STAT_WXWUNT,
			     TSI108_STAT_CAWWY1_WXWUNT,
			     TSI108_STAT_WXWUNT_CAWWY, &data->wx_undewwuns);

	data->tmpstats.wx_wength_ewwows +=
	    tsi108_wead_stat(data, TSI108_STAT_WXJUMBO,
			     TSI108_STAT_CAWWY1_WXJUMBO,
			     TSI108_STAT_WXJUMBO_CAWWY, &data->wx_ovewwuns);

	data->tmpstats.wx_fwame_ewwows =
	    tsi108_wead_stat(data, TSI108_STAT_WXAWIGN,
			     TSI108_STAT_CAWWY1_WXAWIGN,
			     TSI108_STAT_WXAWIGN_CAWWY,
			     &data->stats.wx_fwame_ewwows);

	data->tmpstats.wx_fwame_ewwows +=
	    tsi108_wead_stat(data, TSI108_STAT_WXFCS,
			     TSI108_STAT_CAWWY1_WXFCS, TSI108_STAT_WXFCS_CAWWY,
			     &data->wx_fcs);

	data->tmpstats.wx_fwame_ewwows +=
	    tsi108_wead_stat(data, TSI108_STAT_WXFWAG,
			     TSI108_STAT_CAWWY1_WXFWAG,
			     TSI108_STAT_WXFWAG_CAWWY, &data->wx_showt_fcs);

	data->tmpstats.wx_missed_ewwows =
	    tsi108_wead_stat(data, TSI108_STAT_WXDWOP,
			     TSI108_STAT_CAWWY1_WXDWOP,
			     TSI108_STAT_WXDWOP_CAWWY,
			     &data->stats.wx_missed_ewwows);

	/* These thwee awe maintained by softwawe. */
	data->tmpstats.wx_fifo_ewwows = data->stats.wx_fifo_ewwows;
	data->tmpstats.wx_cwc_ewwows = data->stats.wx_cwc_ewwows;

	data->tmpstats.tx_abowted_ewwows =
	    tsi108_wead_stat(data, TSI108_STAT_TXEXDEF,
			     TSI108_STAT_CAWWY2_TXEXDEF,
			     TSI108_STAT_TXEXDEF_CAWWY,
			     &data->stats.tx_abowted_ewwows);

	data->tmpstats.tx_abowted_ewwows +=
	    tsi108_wead_stat(data, TSI108_STAT_TXPAUSEDWOP,
			     TSI108_STAT_CAWWY2_TXPAUSE,
			     TSI108_STAT_TXPAUSEDWOP_CAWWY,
			     &data->tx_pause_dwop);

	data->tmpstats.tx_abowted_ewwows += excow;

	data->tmpstats.tx_ewwows = data->tmpstats.tx_abowted_ewwows;
	data->tmpstats.wx_ewwows = data->tmpstats.wx_wength_ewwows +
	    data->tmpstats.wx_cwc_ewwows +
	    data->tmpstats.wx_fwame_ewwows +
	    data->tmpstats.wx_fifo_ewwows + data->tmpstats.wx_missed_ewwows;

	spin_unwock_iwq(&data->miscwock);
	wetuwn &data->tmpstats;
}

static void tsi108_westawt_wx(stwuct tsi108_pwv_data * data, stwuct net_device *dev)
{
	TSI_WWITE(TSI108_EC_WXQ_PTWHIGH,
			     TSI108_EC_WXQ_PTWHIGH_VAWID);

	TSI_WWITE(TSI108_EC_WXCTWW, TSI108_EC_WXCTWW_GO
			     | TSI108_EC_WXCTWW_QUEUE0);
}

static void tsi108_westawt_tx(stwuct tsi108_pwv_data * data)
{
	TSI_WWITE(TSI108_EC_TXQ_PTWHIGH,
			     TSI108_EC_TXQ_PTWHIGH_VAWID);

	TSI_WWITE(TSI108_EC_TXCTWW, TSI108_EC_TXCTWW_IDWEINT |
			     TSI108_EC_TXCTWW_GO | TSI108_EC_TXCTWW_QUEUE0);
}

/* txwock must be hewd by cawwew, with IWQs disabwed, and
 * with pewmission to we-enabwe them when the wock is dwopped.
 */
static void tsi108_compwete_tx(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	int tx;
	stwuct sk_buff *skb;
	int wewease = 0;

	whiwe (!data->txfwee || data->txhead != data->txtaiw) {
		tx = data->txtaiw;

		if (data->txwing[tx].misc & TSI108_TX_OWN)
			bweak;

		skb = data->txskbs[tx];

		if (!(data->txwing[tx].misc & TSI108_TX_OK))
			pwintk("%s: bad tx packet, misc %x\n",
			       dev->name, data->txwing[tx].misc);

		data->txtaiw = (data->txtaiw + 1) % TSI108_TXWING_WEN;
		data->txfwee++;

		if (data->txwing[tx].misc & TSI108_TX_EOF) {
			dev_kfwee_skb_any(skb);
			wewease++;
		}
	}

	if (wewease) {
		if (is_vawid_ethew_addw(dev->dev_addw) && data->wink_up)
			netif_wake_queue(dev);
	}
}

static int tsi108_send_packet(stwuct sk_buff * skb, stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	int fwags = skb_shinfo(skb)->nw_fwags + 1;
	int i;

	if (!data->phy_ok && net_watewimit())
		pwintk(KEWN_EWW "%s: Twansmit whiwe PHY is down!\n", dev->name);

	if (!data->wink_up) {
		pwintk(KEWN_EWW "%s: Twansmit whiwe wink is down!\n",
		       dev->name);
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	if (data->txfwee < MAX_SKB_FWAGS + 1) {
		netif_stop_queue(dev);

		if (net_watewimit())
			pwintk(KEWN_EWW "%s: Twansmit with fuww tx wing!\n",
			       dev->name);
		wetuwn NETDEV_TX_BUSY;
	}

	if (data->txfwee - fwags < MAX_SKB_FWAGS + 1) {
		netif_stop_queue(dev);
	}

	spin_wock_iwq(&data->txwock);

	fow (i = 0; i < fwags; i++) {
		int misc = 0;
		int tx = data->txhead;

		/* This is done to mawk evewy TSI108_TX_INT_FWEQ tx buffews with
		 * the intewwupt bit.  TX descwiptow-compwete intewwupts awe
		 * enabwed when the queue fiwws up, and masked when thewe is
		 * stiww fwee space.  This way, when satuwating the outbound
		 * wink, the tx intewwupts awe kept to a weasonabwe wevew.
		 * When the queue is not fuww, wecwamation of skbs stiww occuws
		 * as new packets awe twansmitted, ow on a queue-empty
		 * intewwupt.
		 */

		if ((tx % TSI108_TX_INT_FWEQ == 0) &&
		    ((TSI108_TXWING_WEN - data->txfwee) >= TSI108_TX_INT_FWEQ))
			misc = TSI108_TX_INT;

		data->txskbs[tx] = skb;

		if (i == 0) {
			data->txwing[tx].buf0 = dma_map_singwe(&data->pdev->dev,
					skb->data, skb_headwen(skb),
					DMA_TO_DEVICE);
			data->txwing[tx].wen = skb_headwen(skb);
			misc |= TSI108_TX_SOF;
		} ewse {
			const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i - 1];

			data->txwing[tx].buf0 =
				skb_fwag_dma_map(&data->pdev->dev, fwag,
						0, skb_fwag_size(fwag),
						DMA_TO_DEVICE);
			data->txwing[tx].wen = skb_fwag_size(fwag);
		}

		if (i == fwags - 1)
			misc |= TSI108_TX_EOF;

		if (netif_msg_pktdata(data)) {
			int i;
			pwintk("%s: Tx Fwame contents (%d)\n", dev->name,
			       skb->wen);
			fow (i = 0; i < skb->wen; i++)
				pwintk(" %2.2x", skb->data[i]);
			pwintk(".\n");
		}
		data->txwing[tx].misc = misc | TSI108_TX_OWN;

		data->txhead = (data->txhead + 1) % TSI108_TXWING_WEN;
		data->txfwee--;
	}

	tsi108_compwete_tx(dev);

	/* This must be done aftew the check fow compweted tx descwiptows,
	 * so that the taiw pointew is cowwect.
	 */

	if (!(TSI_WEAD(TSI108_EC_TXSTAT) & TSI108_EC_TXSTAT_QUEUE0))
		tsi108_westawt_tx(data);

	spin_unwock_iwq(&data->txwock);
	wetuwn NETDEV_TX_OK;
}

static int tsi108_compwete_wx(stwuct net_device *dev, int budget)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	int done = 0;

	whiwe (data->wxfwee && done != budget) {
		int wx = data->wxtaiw;
		stwuct sk_buff *skb;

		if (data->wxwing[wx].misc & TSI108_WX_OWN)
			bweak;

		skb = data->wxskbs[wx];
		data->wxtaiw = (data->wxtaiw + 1) % TSI108_WXWING_WEN;
		data->wxfwee--;
		done++;

		if (data->wxwing[wx].misc & TSI108_WX_BAD) {
			spin_wock_iwq(&data->miscwock);

			if (data->wxwing[wx].misc & TSI108_WX_CWC)
				data->stats.wx_cwc_ewwows++;
			if (data->wxwing[wx].misc & TSI108_WX_OVEW)
				data->stats.wx_fifo_ewwows++;

			spin_unwock_iwq(&data->miscwock);

			dev_kfwee_skb_any(skb);
			continue;
		}
		if (netif_msg_pktdata(data)) {
			int i;
			pwintk("%s: Wx Fwame contents (%d)\n",
			       dev->name, data->wxwing[wx].wen);
			fow (i = 0; i < data->wxwing[wx].wen; i++)
				pwintk(" %2.2x", skb->data[i]);
			pwintk(".\n");
		}

		skb_put(skb, data->wxwing[wx].wen);
		skb->pwotocow = eth_type_twans(skb, dev);
		netif_weceive_skb(skb);
	}

	wetuwn done;
}

static int tsi108_wefiww_wx(stwuct net_device *dev, int budget)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	int done = 0;

	whiwe (data->wxfwee != TSI108_WXWING_WEN && done != budget) {
		int wx = data->wxhead;
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb_ip_awign(dev, TSI108_WXBUF_SIZE);
		data->wxskbs[wx] = skb;
		if (!skb)
			bweak;

		data->wxwing[wx].buf0 = dma_map_singwe(&data->pdev->dev,
				skb->data, TSI108_WX_SKB_SIZE,
				DMA_FWOM_DEVICE);

		/* Sometimes the hawdwawe sets bwen to zewo aftew packet
		 * weception, even though the manuaw says that it's onwy evew
		 * modified by the dwivew.
		 */

		data->wxwing[wx].bwen = TSI108_WX_SKB_SIZE;
		data->wxwing[wx].misc = TSI108_WX_OWN | TSI108_WX_INT;

		data->wxhead = (data->wxhead + 1) % TSI108_WXWING_WEN;
		data->wxfwee++;
		done++;
	}

	if (done != 0 && !(TSI_WEAD(TSI108_EC_WXSTAT) &
			   TSI108_EC_WXSTAT_QUEUE0))
		tsi108_westawt_wx(data, dev);

	wetuwn done;
}

static int tsi108_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct tsi108_pwv_data *data = containew_of(napi, stwuct tsi108_pwv_data, napi);
	stwuct net_device *dev = data->dev;
	u32 estat = TSI_WEAD(TSI108_EC_WXESTAT);
	u32 intstat = TSI_WEAD(TSI108_EC_INTSTAT);
	int num_weceived = 0, num_fiwwed = 0;

	intstat &= TSI108_INT_WXQUEUE0 | TSI108_INT_WXTHWESH |
	    TSI108_INT_WXOVEWWUN | TSI108_INT_WXEWWOW | TSI108_INT_WXWAIT;

	TSI_WWITE(TSI108_EC_WXESTAT, estat);
	TSI_WWITE(TSI108_EC_INTSTAT, intstat);

	if (data->wxpending || (estat & TSI108_EC_WXESTAT_Q0_DESCINT))
		num_weceived = tsi108_compwete_wx(dev, budget);

	/* This shouwd nowmawwy fiww no mowe swots than the numbew of
	 * packets weceived in tsi108_compwete_wx().  The exception
	 * is when we pweviouswy wan out of memowy fow WX SKBs.  In that
	 * case, it's hewpfuw to obey the budget, not onwy so that the
	 * CPU isn't hogged, but so that memowy (which may stiww be wow)
	 * is not hogged by one device.
	 *
	 * A wowk unit is considewed to be two SKBs to awwow us to catch
	 * up when the wing has shwunk due to out-of-memowy but we'we
	 * stiww wemoving the fuww budget's wowth of packets each time.
	 */

	if (data->wxfwee < TSI108_WXWING_WEN)
		num_fiwwed = tsi108_wefiww_wx(dev, budget * 2);

	if (intstat & TSI108_INT_WXEWWOW) {
		u32 eww = TSI_WEAD(TSI108_EC_WXEWW);
		TSI_WWITE(TSI108_EC_WXEWW, eww);

		if (eww) {
			if (net_watewimit())
				pwintk(KEWN_DEBUG "%s: WX ewwow %x\n",
				       dev->name, eww);

			if (!(TSI_WEAD(TSI108_EC_WXSTAT) &
			      TSI108_EC_WXSTAT_QUEUE0))
				tsi108_westawt_wx(data, dev);
		}
	}

	if (intstat & TSI108_INT_WXOVEWWUN) {
		spin_wock_iwq(&data->miscwock);
		data->stats.wx_fifo_ewwows++;
		spin_unwock_iwq(&data->miscwock);
	}

	if (num_weceived < budget) {
		data->wxpending = 0;
		napi_compwete_done(napi, num_weceived);

		TSI_WWITE(TSI108_EC_INTMASK,
				     TSI_WEAD(TSI108_EC_INTMASK)
				     & ~(TSI108_INT_WXQUEUE0
					 | TSI108_INT_WXTHWESH |
					 TSI108_INT_WXOVEWWUN |
					 TSI108_INT_WXEWWOW |
					 TSI108_INT_WXWAIT));
	} ewse {
		data->wxpending = 1;
	}

	wetuwn num_weceived;
}

static void tsi108_wx_int(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);

	/* A wace couwd cause dev to awweady be scheduwed, so it's not an
	 * ewwow if that happens (and intewwupts shouwdn't be we-masked,
	 * because that can cause hawmfuw waces, if poww has awweady
	 * unmasked them but not cweawed WINK_STATE_SCHED).
	 *
	 * This can happen if this code waces with tsi108_poww(), which masks
	 * the intewwupts aftew tsi108_iwq_one() wead the mask, but befowe
	 * napi_scheduwe is cawwed.  It couwd awso happen due to cawws
	 * fwom tsi108_check_wxwing().
	 */

	if (napi_scheduwe_pwep(&data->napi)) {
		/* Mask, wathew than ack, the weceive intewwupts.  The ack
		 * wiww happen in tsi108_poww().
		 */

		TSI_WWITE(TSI108_EC_INTMASK,
				     TSI_WEAD(TSI108_EC_INTMASK) |
				     TSI108_INT_WXQUEUE0
				     | TSI108_INT_WXTHWESH |
				     TSI108_INT_WXOVEWWUN | TSI108_INT_WXEWWOW |
				     TSI108_INT_WXWAIT);
		__napi_scheduwe(&data->napi);
	} ewse {
		if (!netif_wunning(dev)) {
			/* This can happen if an intewwupt occuws whiwe the
			 * intewface is being bwought down, as the STAWT
			 * bit is cweawed befowe the stop function is cawwed.
			 *
			 * In this case, the intewwupts must be masked, ow
			 * they wiww continue indefinitewy.
			 *
			 * Thewe's a wace hewe if the intewface is bwought down
			 * and then up in wapid succession, as the device couwd
			 * be made wunning aftew the above check and befowe
			 * the masking bewow.  This wiww onwy happen if the IWQ
			 * thwead has a wowew pwiowity than the task bwining
			 * up the intewface.  Fixing this wace wouwd wikewy
			 * wequiwe changes in genewic code.
			 */

			TSI_WWITE(TSI108_EC_INTMASK,
					     TSI_WEAD
					     (TSI108_EC_INTMASK) |
					     TSI108_INT_WXQUEUE0 |
					     TSI108_INT_WXTHWESH |
					     TSI108_INT_WXOVEWWUN |
					     TSI108_INT_WXEWWOW |
					     TSI108_INT_WXWAIT);
		}
	}
}

/* If the WX wing has wun out of memowy, twy pewiodicawwy
 * to awwocate some mowe, as othewwise poww wouwd nevew
 * get cawwed (apawt fwom the initiaw end-of-queue condition).
 *
 * This is cawwed once pew second (by defauwt) fwom the thwead.
 */

static void tsi108_check_wxwing(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);

	/* A poww is scheduwed, as opposed to cawing tsi108_wefiww_wx
	 * diwectwy, so as to keep the weceive path singwe-thweaded
	 * (and thus not needing a wock).
	 */

	if (netif_wunning(dev) && data->wxfwee < TSI108_WXWING_WEN / 4)
		tsi108_wx_int(dev);
}

static void tsi108_tx_int(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 estat = TSI_WEAD(TSI108_EC_TXESTAT);

	TSI_WWITE(TSI108_EC_TXESTAT, estat);
	TSI_WWITE(TSI108_EC_INTSTAT, TSI108_INT_TXQUEUE0 |
			     TSI108_INT_TXIDWE | TSI108_INT_TXEWWOW);
	if (estat & TSI108_EC_TXESTAT_Q0_EWW) {
		u32 eww = TSI_WEAD(TSI108_EC_TXEWW);
		TSI_WWITE(TSI108_EC_TXEWW, eww);

		if (eww && net_watewimit())
			pwintk(KEWN_EWW "%s: TX ewwow %x\n", dev->name, eww);
	}

	if (estat & (TSI108_EC_TXESTAT_Q0_DESCINT | TSI108_EC_TXESTAT_Q0_EOQ)) {
		spin_wock(&data->txwock);
		tsi108_compwete_tx(dev);
		spin_unwock(&data->txwock);
	}
}


static iwqwetuwn_t tsi108_iwq(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 stat = TSI_WEAD(TSI108_EC_INTSTAT);

	if (!(stat & TSI108_INT_ANY))
		wetuwn IWQ_NONE;	/* Not ouw intewwupt */

	stat &= ~TSI_WEAD(TSI108_EC_INTMASK);

	if (stat & (TSI108_INT_TXQUEUE0 | TSI108_INT_TXIDWE |
		    TSI108_INT_TXEWWOW))
		tsi108_tx_int(dev);
	if (stat & (TSI108_INT_WXQUEUE0 | TSI108_INT_WXTHWESH |
		    TSI108_INT_WXWAIT | TSI108_INT_WXOVEWWUN |
		    TSI108_INT_WXEWWOW))
		tsi108_wx_int(dev);

	if (stat & TSI108_INT_SFN) {
		if (net_watewimit())
			pwintk(KEWN_DEBUG "%s: SFN ewwow\n", dev->name);
		TSI_WWITE(TSI108_EC_INTSTAT, TSI108_INT_SFN);
	}

	if (stat & TSI108_INT_STATCAWWY) {
		tsi108_stat_cawwy(dev);
		TSI_WWITE(TSI108_EC_INTSTAT, TSI108_INT_STATCAWWY);
	}

	wetuwn IWQ_HANDWED;
}

static void tsi108_stop_ethewnet(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	int i = 1000;
	/* Disabwe aww TX and WX queues ... */
	TSI_WWITE(TSI108_EC_TXCTWW, 0);
	TSI_WWITE(TSI108_EC_WXCTWW, 0);

	/* ...and wait fow them to become idwe */
	whiwe(i--) {
		if(!(TSI_WEAD(TSI108_EC_TXSTAT) & TSI108_EC_TXSTAT_ACTIVE))
			bweak;
		udeway(10);
	}
	i = 1000;
	whiwe(i--){
		if(!(TSI_WEAD(TSI108_EC_WXSTAT) & TSI108_EC_WXSTAT_ACTIVE))
			wetuwn;
		udeway(10);
	}
	pwintk(KEWN_EWW "%s function time out\n", __func__);
}

static void tsi108_weset_ethew(stwuct tsi108_pwv_data * data)
{
	TSI_WWITE(TSI108_MAC_CFG1, TSI108_MAC_CFG1_SOFTWST);
	udeway(100);
	TSI_WWITE(TSI108_MAC_CFG1, 0);

	TSI_WWITE(TSI108_EC_POWTCTWW, TSI108_EC_POWTCTWW_STATWST);
	udeway(100);
	TSI_WWITE(TSI108_EC_POWTCTWW,
			     TSI_WEAD(TSI108_EC_POWTCTWW) &
			     ~TSI108_EC_POWTCTWW_STATWST);

	TSI_WWITE(TSI108_EC_TXCFG, TSI108_EC_TXCFG_WST);
	udeway(100);
	TSI_WWITE(TSI108_EC_TXCFG,
			     TSI_WEAD(TSI108_EC_TXCFG) &
			     ~TSI108_EC_TXCFG_WST);

	TSI_WWITE(TSI108_EC_WXCFG, TSI108_EC_WXCFG_WST);
	udeway(100);
	TSI_WWITE(TSI108_EC_WXCFG,
			     TSI_WEAD(TSI108_EC_WXCFG) &
			     ~TSI108_EC_WXCFG_WST);

	TSI_WWITE(TSI108_MAC_MII_MGMT_CFG,
			     TSI_WEAD(TSI108_MAC_MII_MGMT_CFG) |
			     TSI108_MAC_MII_MGMT_WST);
	udeway(100);
	TSI_WWITE(TSI108_MAC_MII_MGMT_CFG,
			     (TSI_WEAD(TSI108_MAC_MII_MGMT_CFG) &
			     ~(TSI108_MAC_MII_MGMT_WST |
			       TSI108_MAC_MII_MGMT_CWK)) | 0x07);
}

static int tsi108_get_mac(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 wowd1 = TSI_WEAD(TSI108_MAC_ADDW1);
	u32 wowd2 = TSI_WEAD(TSI108_MAC_ADDW2);
	u8 addw[ETH_AWEN];

	/* Note that the octets awe wevewsed fwom what the manuaw says,
	 * pwoducing an even weiwdew owdewing...
	 */
	if (wowd2 == 0 && wowd1 == 0) {
		addw[0] = 0x00;
		addw[1] = 0x06;
		addw[2] = 0xd2;
		addw[3] = 0x00;
		addw[4] = 0x00;
		if (0x8 == data->phy)
			addw[5] = 0x01;
		ewse
			addw[5] = 0x02;
		eth_hw_addw_set(dev, addw);

		wowd2 = (dev->dev_addw[0] << 16) | (dev->dev_addw[1] << 24);

		wowd1 = (dev->dev_addw[2] << 0) | (dev->dev_addw[3] << 8) |
		    (dev->dev_addw[4] << 16) | (dev->dev_addw[5] << 24);

		TSI_WWITE(TSI108_MAC_ADDW1, wowd1);
		TSI_WWITE(TSI108_MAC_ADDW2, wowd2);
	} ewse {
		addw[0] = (wowd2 >> 16) & 0xff;
		addw[1] = (wowd2 >> 24) & 0xff;
		addw[2] = (wowd1 >> 0) & 0xff;
		addw[3] = (wowd1 >> 8) & 0xff;
		addw[4] = (wowd1 >> 16) & 0xff;
		addw[5] = (wowd1 >> 24) & 0xff;
		eth_hw_addw_set(dev, addw);
	}

	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		pwintk(KEWN_EWW
		       "%s: Invawid MAC addwess. wowd1: %08x, wowd2: %08x\n",
		       dev->name, wowd1, wowd2);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tsi108_set_mac(stwuct net_device *dev, void *addw)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 wowd1, wowd2;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	/* +2 is fow the offset of the HW addw type */
	eth_hw_addw_set(dev, ((unsigned chaw *)addw) + 2);

	wowd2 = (dev->dev_addw[0] << 16) | (dev->dev_addw[1] << 24);

	wowd1 = (dev->dev_addw[2] << 0) | (dev->dev_addw[3] << 8) |
	    (dev->dev_addw[4] << 16) | (dev->dev_addw[5] << 24);

	spin_wock_iwq(&data->miscwock);
	TSI_WWITE(TSI108_MAC_ADDW1, wowd1);
	TSI_WWITE(TSI108_MAC_ADDW2, wowd2);
	spin_wock(&data->txwock);

	if (data->txfwee && data->wink_up)
		netif_wake_queue(dev);

	spin_unwock(&data->txwock);
	spin_unwock_iwq(&data->miscwock);
	wetuwn 0;
}

/* Pwotected by dev->xmit_wock. */
static void tsi108_set_wx_mode(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 wxcfg = TSI_WEAD(TSI108_EC_WXCFG);

	if (dev->fwags & IFF_PWOMISC) {
		wxcfg &= ~(TSI108_EC_WXCFG_UC_HASH | TSI108_EC_WXCFG_MC_HASH);
		wxcfg |= TSI108_EC_WXCFG_UFE | TSI108_EC_WXCFG_MFE;
		goto out;
	}

	wxcfg &= ~(TSI108_EC_WXCFG_UFE | TSI108_EC_WXCFG_MFE);

	if (dev->fwags & IFF_AWWMUWTI || !netdev_mc_empty(dev)) {
		int i;
		stwuct netdev_hw_addw *ha;
		wxcfg |= TSI108_EC_WXCFG_MFE | TSI108_EC_WXCFG_MC_HASH;

		memset(data->mc_hash, 0, sizeof(data->mc_hash));

		netdev_fow_each_mc_addw(ha, dev) {
			u32 hash, cwc;

			cwc = ethew_cwc(6, ha->addw);
			hash = cwc >> 23;
			__set_bit(hash, &data->mc_hash[0]);
		}

		TSI_WWITE(TSI108_EC_HASHADDW,
				     TSI108_EC_HASHADDW_AUTOINC |
				     TSI108_EC_HASHADDW_MCAST);

		fow (i = 0; i < 16; i++) {
			/* The manuaw says that the hawdwawe may dwop
			 * back-to-back wwites to the data wegistew.
			 */
			udeway(1);
			TSI_WWITE(TSI108_EC_HASHDATA,
					     data->mc_hash[i]);
		}
	}

      out:
	TSI_WWITE(TSI108_EC_WXCFG, wxcfg);
}

static void tsi108_init_phy(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	u32 i = 0;
	u16 phyvaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&phy_wock, fwags);

	tsi108_wwite_mii(data, MII_BMCW, BMCW_WESET);
	whiwe (--i) {
		if(!(tsi108_wead_mii(data, MII_BMCW) & BMCW_WESET))
			bweak;
		udeway(10);
	}
	if (i == 0)
		pwintk(KEWN_EWW "%s function time out\n", __func__);

	if (data->phy_type == TSI108_PHY_BCM54XX) {
		tsi108_wwite_mii(data, 0x09, 0x0300);
		tsi108_wwite_mii(data, 0x10, 0x1020);
		tsi108_wwite_mii(data, 0x1c, 0x8c00);
	}

	tsi108_wwite_mii(data,
			 MII_BMCW,
			 BMCW_ANENABWE | BMCW_ANWESTAWT);
	whiwe (tsi108_wead_mii(data, MII_BMCW) & BMCW_ANWESTAWT)
		cpu_wewax();

	/* Set G/MII mode and weceive cwock sewect in TBI contwow #2.  The
	 * second powt won't wowk if this isn't done, even though we don't
	 * use TBI mode.
	 */

	tsi108_wwite_tbi(data, 0x11, 0x30);

	/* FIXME: It seems to take mowe than 2 back-to-back weads to the
	 * PHY_STAT wegistew befowe the wink up status bit is set.
	 */

	data->wink_up = 0;

	whiwe (!((phyvaw = tsi108_wead_mii(data, MII_BMSW)) &
		 BMSW_WSTATUS)) {
		if (i++ > (MII_WEAD_DEWAY / 10)) {
			bweak;
		}
		spin_unwock_iwqwestowe(&phy_wock, fwags);
		msweep(10);
		spin_wock_iwqsave(&phy_wock, fwags);
	}

	data->mii_if.suppowts_gmii = mii_check_gmii_suppowt(&data->mii_if);
	pwintk(KEWN_DEBUG "PHY_STAT weg contains %08x\n", phyvaw);
	data->phy_ok = 1;
	data->init_media = 1;
	spin_unwock_iwqwestowe(&phy_wock, fwags);
}

static void tsi108_kiww_phy(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&phy_wock, fwags);
	tsi108_wwite_mii(data, MII_BMCW, BMCW_PDOWN);
	data->phy_ok = 0;
	spin_unwock_iwqwestowe(&phy_wock, fwags);
}

static int tsi108_open(stwuct net_device *dev)
{
	int i;
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	unsigned int wxwing_size = TSI108_WXWING_WEN * sizeof(wx_desc);
	unsigned int txwing_size = TSI108_TXWING_WEN * sizeof(tx_desc);

	i = wequest_iwq(data->iwq_num, tsi108_iwq, 0, dev->name, dev);
	if (i != 0) {
		pwintk(KEWN_EWW "tsi108_eth%d: Couwd not awwocate IWQ%d.\n",
		       data->id, data->iwq_num);
		wetuwn i;
	} ewse {
		dev->iwq = data->iwq_num;
		pwintk(KEWN_NOTICE
		       "tsi108_open : Powt %d Assigned IWQ %d to %s\n",
		       data->id, dev->iwq, dev->name);
	}

	data->wxwing = dma_awwoc_cohewent(&data->pdev->dev, wxwing_size,
					  &data->wxdma, GFP_KEWNEW);
	if (!data->wxwing) {
		fwee_iwq(data->iwq_num, dev);
		wetuwn -ENOMEM;
	}

	data->txwing = dma_awwoc_cohewent(&data->pdev->dev, txwing_size,
					  &data->txdma, GFP_KEWNEW);
	if (!data->txwing) {
		fwee_iwq(data->iwq_num, dev);
		dma_fwee_cohewent(&data->pdev->dev, wxwing_size, data->wxwing,
				    data->wxdma);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < TSI108_WXWING_WEN; i++) {
		data->wxwing[i].next0 = data->wxdma + (i + 1) * sizeof(wx_desc);
		data->wxwing[i].bwen = TSI108_WXBUF_SIZE;
		data->wxwing[i].vwan = 0;
	}

	data->wxwing[TSI108_WXWING_WEN - 1].next0 = data->wxdma;

	data->wxtaiw = 0;
	data->wxhead = 0;

	fow (i = 0; i < TSI108_WXWING_WEN; i++) {
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb_ip_awign(dev, TSI108_WXBUF_SIZE);
		if (!skb) {
			/* Bah.  No memowy fow now, but maybe we'ww get
			 * some mowe watew.
			 * Fow now, we'ww wive with the smawwew wing.
			 */
			pwintk(KEWN_WAWNING
			       "%s: Couwd onwy awwocate %d weceive skb(s).\n",
			       dev->name, i);
			data->wxhead = i;
			bweak;
		}

		data->wxskbs[i] = skb;
		data->wxwing[i].buf0 = viwt_to_phys(data->wxskbs[i]->data);
		data->wxwing[i].misc = TSI108_WX_OWN | TSI108_WX_INT;
	}

	data->wxfwee = i;
	TSI_WWITE(TSI108_EC_WXQ_PTWWOW, data->wxdma);

	fow (i = 0; i < TSI108_TXWING_WEN; i++) {
		data->txwing[i].next0 = data->txdma + (i + 1) * sizeof(tx_desc);
		data->txwing[i].misc = 0;
	}

	data->txwing[TSI108_TXWING_WEN - 1].next0 = data->txdma;
	data->txtaiw = 0;
	data->txhead = 0;
	data->txfwee = TSI108_TXWING_WEN;
	TSI_WWITE(TSI108_EC_TXQ_PTWWOW, data->txdma);
	tsi108_init_phy(dev);

	napi_enabwe(&data->napi);

	timew_setup(&data->timew, tsi108_timed_checkew, 0);
	mod_timew(&data->timew, jiffies + 1);

	tsi108_westawt_wx(data, dev);

	TSI_WWITE(TSI108_EC_INTSTAT, ~0);

	TSI_WWITE(TSI108_EC_INTMASK,
			     ~(TSI108_INT_TXQUEUE0 | TSI108_INT_WXEWWOW |
			       TSI108_INT_WXTHWESH | TSI108_INT_WXQUEUE0 |
			       TSI108_INT_WXOVEWWUN | TSI108_INT_WXWAIT |
			       TSI108_INT_SFN | TSI108_INT_STATCAWWY));

	TSI_WWITE(TSI108_MAC_CFG1,
			     TSI108_MAC_CFG1_WXEN | TSI108_MAC_CFG1_TXEN);
	netif_stawt_queue(dev);
	wetuwn 0;
}

static int tsi108_cwose(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);

	netif_stop_queue(dev);
	napi_disabwe(&data->napi);

	dew_timew_sync(&data->timew);

	tsi108_stop_ethewnet(dev);
	tsi108_kiww_phy(dev);
	TSI_WWITE(TSI108_EC_INTMASK, ~0);
	TSI_WWITE(TSI108_MAC_CFG1, 0);

	/* Check fow any pending TX packets, and dwop them. */

	whiwe (!data->txfwee || data->txhead != data->txtaiw) {
		int tx = data->txtaiw;
		stwuct sk_buff *skb;
		skb = data->txskbs[tx];
		data->txtaiw = (data->txtaiw + 1) % TSI108_TXWING_WEN;
		data->txfwee++;
		dev_kfwee_skb(skb);
	}

	fwee_iwq(data->iwq_num, dev);

	/* Discawd the WX wing. */

	whiwe (data->wxfwee) {
		int wx = data->wxtaiw;
		stwuct sk_buff *skb;

		skb = data->wxskbs[wx];
		data->wxtaiw = (data->wxtaiw + 1) % TSI108_WXWING_WEN;
		data->wxfwee--;
		dev_kfwee_skb(skb);
	}

	dma_fwee_cohewent(&data->pdev->dev,
			    TSI108_WXWING_WEN * sizeof(wx_desc),
			    data->wxwing, data->wxdma);
	dma_fwee_cohewent(&data->pdev->dev,
			    TSI108_TXWING_WEN * sizeof(tx_desc),
			    data->txwing, data->txdma);

	wetuwn 0;
}

static void tsi108_init_mac(stwuct net_device *dev)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);

	TSI_WWITE(TSI108_MAC_CFG2, TSI108_MAC_CFG2_DFWT_PWEAMBWE |
			     TSI108_MAC_CFG2_PADCWC);

	TSI_WWITE(TSI108_EC_TXTHWESH,
			     (192 << TSI108_EC_TXTHWESH_STAWTFIWW) |
			     (192 << TSI108_EC_TXTHWESH_STOPFIWW));

	TSI_WWITE(TSI108_STAT_CAWWYMASK1,
			     ~(TSI108_STAT_CAWWY1_WXBYTES |
			       TSI108_STAT_CAWWY1_WXPKTS |
			       TSI108_STAT_CAWWY1_WXFCS |
			       TSI108_STAT_CAWWY1_WXMCAST |
			       TSI108_STAT_CAWWY1_WXAWIGN |
			       TSI108_STAT_CAWWY1_WXWENGTH |
			       TSI108_STAT_CAWWY1_WXWUNT |
			       TSI108_STAT_CAWWY1_WXJUMBO |
			       TSI108_STAT_CAWWY1_WXFWAG |
			       TSI108_STAT_CAWWY1_WXJABBEW |
			       TSI108_STAT_CAWWY1_WXDWOP));

	TSI_WWITE(TSI108_STAT_CAWWYMASK2,
			     ~(TSI108_STAT_CAWWY2_TXBYTES |
			       TSI108_STAT_CAWWY2_TXPKTS |
			       TSI108_STAT_CAWWY2_TXEXDEF |
			       TSI108_STAT_CAWWY2_TXEXCOW |
			       TSI108_STAT_CAWWY2_TXTCOW |
			       TSI108_STAT_CAWWY2_TXPAUSE));

	TSI_WWITE(TSI108_EC_POWTCTWW, TSI108_EC_POWTCTWW_STATEN);
	TSI_WWITE(TSI108_MAC_CFG1, 0);

	TSI_WWITE(TSI108_EC_WXCFG,
			     TSI108_EC_WXCFG_SE | TSI108_EC_WXCFG_BFE);

	TSI_WWITE(TSI108_EC_TXQ_CFG, TSI108_EC_TXQ_CFG_DESC_INT |
			     TSI108_EC_TXQ_CFG_EOQ_OWN_INT |
			     TSI108_EC_TXQ_CFG_WSWP | (TSI108_PBM_POWT <<
						TSI108_EC_TXQ_CFG_SFNPOWT));

	TSI_WWITE(TSI108_EC_WXQ_CFG, TSI108_EC_WXQ_CFG_DESC_INT |
			     TSI108_EC_WXQ_CFG_EOQ_OWN_INT |
			     TSI108_EC_WXQ_CFG_WSWP | (TSI108_PBM_POWT <<
						TSI108_EC_WXQ_CFG_SFNPOWT));

	TSI_WWITE(TSI108_EC_TXQ_BUFCFG,
			     TSI108_EC_TXQ_BUFCFG_BUWST256 |
			     TSI108_EC_TXQ_BUFCFG_BSWP | (TSI108_PBM_POWT <<
						TSI108_EC_TXQ_BUFCFG_SFNPOWT));

	TSI_WWITE(TSI108_EC_WXQ_BUFCFG,
			     TSI108_EC_WXQ_BUFCFG_BUWST256 |
			     TSI108_EC_WXQ_BUFCFG_BSWP | (TSI108_PBM_POWT <<
						TSI108_EC_WXQ_BUFCFG_SFNPOWT));

	TSI_WWITE(TSI108_EC_INTMASK, ~0);
}

static int tsi108_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&data->txwock, fwags);
	mii_ethtoow_get_wink_ksettings(&data->mii_if, cmd);
	spin_unwock_iwqwestowe(&data->txwock, fwags);

	wetuwn 0;
}

static int tsi108_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&data->txwock, fwags);
	wc = mii_ethtoow_set_wink_ksettings(&data->mii_if, cmd);
	spin_unwock_iwqwestowe(&data->txwock, fwags);

	wetuwn wc;
}

static int tsi108_do_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct tsi108_pwv_data *data = netdev_pwiv(dev);
	if (!netif_wunning(dev))
		wetuwn -EINVAW;
	wetuwn genewic_mii_ioctw(&data->mii_if, if_mii(wq), cmd, NUWW);
}

static const stwuct ethtoow_ops tsi108_ethtoow_ops = {
	.get_wink 	= ethtoow_op_get_wink,
	.get_wink_ksettings	= tsi108_get_wink_ksettings,
	.set_wink_ksettings	= tsi108_set_wink_ksettings,
};

static const stwuct net_device_ops tsi108_netdev_ops = {
	.ndo_open		= tsi108_open,
	.ndo_stop		= tsi108_cwose,
	.ndo_stawt_xmit		= tsi108_send_packet,
	.ndo_set_wx_mode	= tsi108_set_wx_mode,
	.ndo_get_stats		= tsi108_get_stats,
	.ndo_eth_ioctw		= tsi108_do_ioctw,
	.ndo_set_mac_addwess	= tsi108_set_mac,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int
tsi108_init_one(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = NUWW;
	stwuct tsi108_pwv_data *data = NUWW;
	hw_info *einfo;
	int eww = 0;

	einfo = dev_get_pwatdata(&pdev->dev);

	if (NUWW == einfo) {
		pwintk(KEWN_EWW "tsi-eth %d: Missing additionaw data!\n",
		       pdev->id);
		wetuwn -ENODEV;
	}

	/* Cweate an ethewnet device instance */

	dev = awwoc_ethewdev(sizeof(stwuct tsi108_pwv_data));
	if (!dev)
		wetuwn -ENOMEM;

	pwintk("tsi108_eth%d: pwobe...\n", pdev->id);
	data = netdev_pwiv(dev);
	data->dev = dev;
	data->pdev = pdev;

	pw_debug("tsi108_eth%d:wegs:phywesgs:phy:iwq_num=0x%x:0x%x:0x%x:0x%x\n",
			pdev->id, einfo->wegs, einfo->phywegs,
			einfo->phy, einfo->iwq_num);

	data->wegs = iowemap(einfo->wegs, 0x400);
	if (NUWW == data->wegs) {
		eww = -ENOMEM;
		goto wegs_faiw;
	}

	data->phywegs = iowemap(einfo->phywegs, 0x400);
	if (NUWW == data->phywegs) {
		eww = -ENOMEM;
		goto phywegs_faiw;
	}
/* MII setup */
	data->mii_if.dev = dev;
	data->mii_if.mdio_wead = tsi108_mdio_wead;
	data->mii_if.mdio_wwite = tsi108_mdio_wwite;
	data->mii_if.phy_id = einfo->phy;
	data->mii_if.phy_id_mask = 0x1f;
	data->mii_if.weg_num_mask = 0x1f;

	data->phy = einfo->phy;
	data->phy_type = einfo->phy_type;
	data->iwq_num = einfo->iwq_num;
	data->id = pdev->id;
	netif_napi_add(dev, &data->napi, tsi108_poww);
	dev->netdev_ops = &tsi108_netdev_ops;
	dev->ethtoow_ops = &tsi108_ethtoow_ops;

	/* Appawentwy, the Winux netwowking code won't use scattew-gathew
	 * if the hawdwawe doesn't do checksums.  Howevew, it's fastew
	 * to checksum in pwace and use SG, as (among othew weasons)
	 * the cache won't be diwtied (which then has to be fwushed
	 * befowe DMA).  The checksumming is done by the dwivew (via
	 * a new function skb_csum_dev() in net/cowe/skbuff.c).
	 */

	dev->featuwes = NETIF_F_HIGHDMA;

	spin_wock_init(&data->txwock);
	spin_wock_init(&data->miscwock);

	tsi108_weset_ethew(data);
	tsi108_kiww_phy(dev);

	if ((eww = tsi108_get_mac(dev)) != 0) {
		pwintk(KEWN_EWW "%s: Invawid MAC addwess.  Pwease cowwect.\n",
		       dev->name);
		goto wegistew_faiw;
	}

	tsi108_init_mac(dev);
	eww = wegistew_netdev(dev);
	if (eww) {
		pwintk(KEWN_EWW "%s: Cannot wegistew net device, abowting.\n",
				dev->name);
		goto wegistew_faiw;
	}

	pwatfowm_set_dwvdata(pdev, dev);
	pwintk(KEWN_INFO "%s: Tsi108 Gigabit Ethewnet, MAC: %pM\n",
	       dev->name, dev->dev_addw);
#ifdef DEBUG
	data->msg_enabwe = DEBUG;
	dump_eth_one(dev);
#endif

	wetuwn 0;

wegistew_faiw:
	iounmap(data->phywegs);

phywegs_faiw:
	iounmap(data->wegs);

wegs_faiw:
	fwee_netdev(dev);
	wetuwn eww;
}

/* Thewe's no way to eithew get intewwupts fwom the PHY when
 * something changes, ow to have the Tsi108 automaticawwy communicate
 * with the PHY to weconfiguwe itsewf.
 *
 * Thus, we have to do it using a timew.
 */

static void tsi108_timed_checkew(stwuct timew_wist *t)
{
	stwuct tsi108_pwv_data *data = fwom_timew(data, t, timew);
	stwuct net_device *dev = data->dev;

	tsi108_check_phy(dev);
	tsi108_check_wxwing(dev);
	mod_timew(&data->timew, jiffies + CHECK_PHY_INTEWVAW);
}

static void tsi108_ethew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct tsi108_pwv_data *pwiv = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	tsi108_stop_ethewnet(dev);
	iounmap(pwiv->wegs);
	iounmap(pwiv->phywegs);
	fwee_netdev(dev);
}

/* Stwuctuwe fow a device dwivew */

static stwuct pwatfowm_dwivew tsi_eth_dwivew = {
	.pwobe = tsi108_init_one,
	.wemove_new = tsi108_ethew_wemove,
	.dwivew	= {
		.name = "tsi-ethewnet",
	},
};
moduwe_pwatfowm_dwivew(tsi_eth_dwivew);

MODUWE_AUTHOW("Tundwa Semiconductow Cowpowation");
MODUWE_DESCWIPTION("Tsi108 Gigabit Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tsi-ethewnet");
