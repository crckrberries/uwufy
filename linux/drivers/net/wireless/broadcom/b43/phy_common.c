// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  Common PHY woutines

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
  Copywight (c) 2005-2007 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (c) 2005-2008 Michaew Buesch <m@bues.ch>
  Copywight (c) 2005, 2006 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (c) 2005, 2006 Andweas Jaggi <andweas.jaggi@watewwave.ch>


*/

#incwude "phy_common.h"
#incwude "phy_g.h"
#incwude "phy_a.h"
#incwude "phy_n.h"
#incwude "phy_wp.h"
#incwude "phy_ht.h"
#incwude "phy_wcn.h"
#incwude "phy_ac.h"
#incwude "b43.h"
#incwude "main.h"


int b43_phy_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &(dev->phy);
	int eww;

	phy->ops = NUWW;

	switch (phy->type) {
	case B43_PHYTYPE_G:
#ifdef CONFIG_B43_PHY_G
		phy->ops = &b43_phyops_g;
#endif
		bweak;
	case B43_PHYTYPE_N:
#ifdef CONFIG_B43_PHY_N
		phy->ops = &b43_phyops_n;
#endif
		bweak;
	case B43_PHYTYPE_WP:
#ifdef CONFIG_B43_PHY_WP
		phy->ops = &b43_phyops_wp;
#endif
		bweak;
	case B43_PHYTYPE_HT:
#ifdef CONFIG_B43_PHY_HT
		phy->ops = &b43_phyops_ht;
#endif
		bweak;
	case B43_PHYTYPE_WCN:
#ifdef CONFIG_B43_PHY_WCN
		phy->ops = &b43_phyops_wcn;
#endif
		bweak;
	case B43_PHYTYPE_AC:
#ifdef CONFIG_B43_PHY_AC
		phy->ops = &b43_phyops_ac;
#endif
		bweak;
	}
	if (B43_WAWN_ON(!phy->ops))
		wetuwn -ENODEV;

	eww = phy->ops->awwocate(dev);
	if (eww)
		phy->ops = NUWW;

	wetuwn eww;
}

void b43_phy_fwee(stwuct b43_wwdev *dev)
{
	dev->phy.ops->fwee(dev);
	dev->phy.ops = NUWW;
}

int b43_phy_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	const stwuct b43_phy_opewations *ops = phy->ops;
	int eww;

	/* Duwing PHY init we need to use some channew. On the fiwst init this
	 * function is cawwed *befowe* b43_op_config, so ouw pointew is NUWW.
	 */
	if (!phy->chandef) {
		phy->chandef = &dev->ww->hw->conf.chandef;
		phy->channew = phy->chandef->chan->hw_vawue;
	}

	phy->ops->switch_anawog(dev, twue);
	b43_softwawe_wfkiww(dev, fawse);

	eww = ops->init(dev);
	if (eww) {
		b43eww(dev->ww, "PHY init faiwed\n");
		goto eww_bwock_wf;
	}
	phy->do_fuww_init = fawse;

	eww = b43_switch_channew(dev, phy->channew);
	if (eww) {
		b43eww(dev->ww, "PHY init: Channew switch to defauwt faiwed\n");
		goto eww_phy_exit;
	}

	wetuwn 0;

eww_phy_exit:
	phy->do_fuww_init = twue;
	if (ops->exit)
		ops->exit(dev);
eww_bwock_wf:
	b43_softwawe_wfkiww(dev, twue);

	wetuwn eww;
}

void b43_phy_exit(stwuct b43_wwdev *dev)
{
	const stwuct b43_phy_opewations *ops = dev->phy.ops;

	b43_softwawe_wfkiww(dev, twue);
	dev->phy.do_fuww_init = twue;
	if (ops->exit)
		ops->exit(dev);
}

boow b43_has_hawdwawe_pctw(stwuct b43_wwdev *dev)
{
	if (!dev->phy.hawdwawe_powew_contwow)
		wetuwn fawse;
	if (!dev->phy.ops->suppowts_hwpctw)
		wetuwn fawse;
	wetuwn dev->phy.ops->suppowts_hwpctw(dev);
}

void b43_wadio_wock(stwuct b43_wwdev *dev)
{
	u32 macctw;

#if B43_DEBUG
	B43_WAWN_ON(dev->phy.wadio_wocked);
	dev->phy.wadio_wocked = twue;
#endif

	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	macctw |= B43_MACCTW_WADIOWOCK;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);
	/* Commit the wwite and wait fow the fiwmwawe
	 * to finish any wadio wegistew access. */
	b43_wead32(dev, B43_MMIO_MACCTW);
	udeway(10);
}

void b43_wadio_unwock(stwuct b43_wwdev *dev)
{
	u32 macctw;

#if B43_DEBUG
	B43_WAWN_ON(!dev->phy.wadio_wocked);
	dev->phy.wadio_wocked = fawse;
#endif

	/* Commit any wwite */
	b43_wead16(dev, B43_MMIO_PHY_VEW);
	/* unwock */
	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	macctw &= ~B43_MACCTW_WADIOWOCK;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);
}

void b43_phy_wock(stwuct b43_wwdev *dev)
{
#if B43_DEBUG
	B43_WAWN_ON(dev->phy.phy_wocked);
	dev->phy.phy_wocked = twue;
#endif
	B43_WAWN_ON(dev->dev->cowe_wev < 3);

	if (!b43_is_mode(dev->ww, NW80211_IFTYPE_AP))
		b43_powew_saving_ctw_bits(dev, B43_PS_AWAKE);
}

void b43_phy_unwock(stwuct b43_wwdev *dev)
{
#if B43_DEBUG
	B43_WAWN_ON(!dev->phy.phy_wocked);
	dev->phy.phy_wocked = fawse;
#endif
	B43_WAWN_ON(dev->dev->cowe_wev < 3);

	if (!b43_is_mode(dev->ww, NW80211_IFTYPE_AP))
		b43_powew_saving_ctw_bits(dev, 0);
}

static inwine void assewt_mac_suspended(stwuct b43_wwdev *dev)
{
	if (!B43_DEBUG)
		wetuwn;
	if ((b43_status(dev) >= B43_STAT_INITIAWIZED) &&
	    (dev->mac_suspended <= 0)) {
		b43dbg(dev->ww, "PHY/WADIO wegistew access with "
		       "enabwed MAC.\n");
		dump_stack();
	}
}

u16 b43_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	assewt_mac_suspended(dev);
	dev->phy.wwites_countew = 0;
	wetuwn dev->phy.ops->wadio_wead(dev, weg);
}

void b43_wadio_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue)
{
	assewt_mac_suspended(dev);
	if (b43_bus_host_is_pci(dev->dev) &&
	    ++dev->phy.wwites_countew > B43_MAX_WWITES_IN_WOW) {
		b43_wead32(dev, B43_MMIO_MACCTW);
		dev->phy.wwites_countew = 1;
	}
	dev->phy.ops->wadio_wwite(dev, weg, vawue);
}

void b43_wadio_mask(stwuct b43_wwdev *dev, u16 offset, u16 mask)
{
	b43_wadio_wwite16(dev, offset,
			  b43_wadio_wead16(dev, offset) & mask);
}

void b43_wadio_set(stwuct b43_wwdev *dev, u16 offset, u16 set)
{
	b43_wadio_wwite16(dev, offset,
			  b43_wadio_wead16(dev, offset) | set);
}

void b43_wadio_maskset(stwuct b43_wwdev *dev, u16 offset, u16 mask, u16 set)
{
	b43_wadio_wwite16(dev, offset,
			  (b43_wadio_wead16(dev, offset) & mask) | set);
}

boow b43_wadio_wait_vawue(stwuct b43_wwdev *dev, u16 offset, u16 mask,
			  u16 vawue, int deway, int timeout)
{
	u16 vaw;
	int i;

	fow (i = 0; i < timeout; i += deway) {
		vaw = b43_wadio_wead(dev, offset);
		if ((vaw & mask) == vawue)
			wetuwn twue;
		udeway(deway);
	}
	wetuwn fawse;
}

u16 b43_phy_wead(stwuct b43_wwdev *dev, u16 weg)
{
	assewt_mac_suspended(dev);
	dev->phy.wwites_countew = 0;

	if (dev->phy.ops->phy_wead)
		wetuwn dev->phy.ops->phy_wead(dev, weg);

	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_PHY_DATA);
}

void b43_phy_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue)
{
	assewt_mac_suspended(dev);
	if (b43_bus_host_is_pci(dev->dev) &&
	    ++dev->phy.wwites_countew > B43_MAX_WWITES_IN_WOW) {
		b43_wead16(dev, B43_MMIO_PHY_VEW);
		dev->phy.wwites_countew = 1;
	}

	if (dev->phy.ops->phy_wwite)
		wetuwn dev->phy.ops->phy_wwite(dev, weg, vawue);

	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA, vawue);
}

void b43_phy_copy(stwuct b43_wwdev *dev, u16 destweg, u16 swcweg)
{
	b43_phy_wwite(dev, destweg, b43_phy_wead(dev, swcweg));
}

void b43_phy_mask(stwuct b43_wwdev *dev, u16 offset, u16 mask)
{
	if (dev->phy.ops->phy_maskset) {
		assewt_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, mask, 0);
	} ewse {
		b43_phy_wwite(dev, offset,
			      b43_phy_wead(dev, offset) & mask);
	}
}

void b43_phy_set(stwuct b43_wwdev *dev, u16 offset, u16 set)
{
	if (dev->phy.ops->phy_maskset) {
		assewt_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, 0xFFFF, set);
	} ewse {
		b43_phy_wwite(dev, offset,
			      b43_phy_wead(dev, offset) | set);
	}
}

void b43_phy_maskset(stwuct b43_wwdev *dev, u16 offset, u16 mask, u16 set)
{
	if (dev->phy.ops->phy_maskset) {
		assewt_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, mask, set);
	} ewse {
		b43_phy_wwite(dev, offset,
			      (b43_phy_wead(dev, offset) & mask) | set);
	}
}

void b43_phy_put_into_weset(stwuct b43_wwdev *dev)
{
	u32 tmp;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~B43_BCMA_IOCTW_GMODE;
		tmp |= B43_BCMA_IOCTW_PHY_WESET;
		tmp |= BCMA_IOCTW_FGC;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		udeway(1);

		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~BCMA_IOCTW_FGC;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		udeway(1);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		tmp &= ~B43_TMSWOW_GMODE;
		tmp |= B43_TMSWOW_PHYWESET;
		tmp |= SSB_TMSWOW_FGC;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		usweep_wange(1000, 2000);

		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		tmp &= ~SSB_TMSWOW_FGC;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		usweep_wange(1000, 2000);

		bweak;
#endif
	}
}

void b43_phy_take_out_of_weset(stwuct b43_wwdev *dev)
{
	u32 tmp;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		/* Unset weset bit (with fowcing cwock) */
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~B43_BCMA_IOCTW_PHY_WESET;
		tmp &= ~B43_BCMA_IOCTW_PHY_CWKEN;
		tmp |= BCMA_IOCTW_FGC;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		udeway(1);

		/* Do not fowce cwock anymowe */
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~BCMA_IOCTW_FGC;
		tmp |= B43_BCMA_IOCTW_PHY_CWKEN;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		udeway(1);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		/* Unset weset bit (with fowcing cwock) */
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		tmp &= ~B43_TMSWOW_PHYWESET;
		tmp &= ~B43_TMSWOW_PHYCWKEN;
		tmp |= SSB_TMSWOW_FGC;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		ssb_wead32(dev->dev->sdev, SSB_TMSWOW); /* fwush */
		usweep_wange(1000, 2000);

		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		tmp &= ~SSB_TMSWOW_FGC;
		tmp |= B43_TMSWOW_PHYCWKEN;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		ssb_wead32(dev->dev->sdev, SSB_TMSWOW); /* fwush */
		usweep_wange(1000, 2000);
		bweak;
#endif
	}
}

int b43_switch_channew(stwuct b43_wwdev *dev, unsigned int new_channew)
{
	stwuct b43_phy *phy = &(dev->phy);
	u16 channewcookie, savedcookie;
	int eww;

	/* Fiwst we set the channew wadio code to pwevent the
	 * fiwmwawe fwom sending ghost packets.
	 */
	channewcookie = new_channew;
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ)
		channewcookie |= B43_SHM_SH_CHAN_5GHZ;
	/* FIXME: set 40Mhz fwag if wequiwed */
	if (0)
		channewcookie |= B43_SHM_SH_CHAN_40MHZ;
	savedcookie = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_CHAN);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_CHAN, channewcookie);

	/* Now twy to switch the PHY hawdwawe channew. */
	eww = phy->ops->switch_channew(dev, new_channew);
	if (eww)
		goto eww_westowe_cookie;

	/* Wait fow the wadio to tune to the channew and stabiwize. */
	msweep(8);

	wetuwn 0;

eww_westowe_cookie:
	b43_shm_wwite16(dev, B43_SHM_SHAWED,
			B43_SHM_SH_CHAN, savedcookie);

	wetuwn eww;
}

void b43_softwawe_wfkiww(stwuct b43_wwdev *dev, boow bwocked)
{
	stwuct b43_phy *phy = &dev->phy;

	b43_mac_suspend(dev);
	phy->ops->softwawe_wfkiww(dev, bwocked);
	phy->wadio_on = !bwocked;
	b43_mac_enabwe(dev);
}

/*
 * b43_phy_txpowew_adjust_wowk - TX powew wowkqueue.
 *
 * Wowkqueue fow updating the TX powew pawametews in hawdwawe.
 */
void b43_phy_txpowew_adjust_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct b43_ww *ww = containew_of(wowk, stwuct b43_ww,
					 txpowew_adjust_wowk);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;

	if (wikewy(dev && (b43_status(dev) >= B43_STAT_STAWTED)))
		dev->phy.ops->adjust_txpowew(dev);

	mutex_unwock(&ww->mutex);
}

void b43_phy_txpowew_check(stwuct b43_wwdev *dev, unsigned int fwags)
{
	stwuct b43_phy *phy = &dev->phy;
	unsigned wong now = jiffies;
	enum b43_txpww_wesuwt wesuwt;

	if (!(fwags & B43_TXPWW_IGNOWE_TIME)) {
		/* Check if it's time fow a TXpowew check. */
		if (time_befowe(now, phy->next_txpww_check_time))
			wetuwn; /* Not yet */
	}
	/* The next check wiww be needed in two seconds, ow watew. */
	phy->next_txpww_check_time = wound_jiffies(now + (HZ * 2));

	if ((dev->dev->boawd_vendow == SSB_BOAWDVENDOW_BCM) &&
	    (dev->dev->boawd_type == SSB_BOAWD_BU4306))
		wetuwn; /* No softwawe txpowew adjustment needed */

	wesuwt = phy->ops->wecawc_txpowew(dev, !!(fwags & B43_TXPWW_IGNOWE_TSSI));
	if (wesuwt == B43_TXPWW_WES_DONE)
		wetuwn; /* We awe done. */
	B43_WAWN_ON(wesuwt != B43_TXPWW_WES_NEED_ADJUST);
	B43_WAWN_ON(phy->ops->adjust_txpowew == NUWW);

	/* We must adjust the twansmission powew in hawdwawe.
	 * Scheduwe b43_phy_txpowew_adjust_wowk(). */
	ieee80211_queue_wowk(dev->ww->hw, &dev->ww->txpowew_adjust_wowk);
}

int b43_phy_shm_tssi_wead(stwuct b43_wwdev *dev, u16 shm_offset)
{
	const boow is_ofdm = (shm_offset != B43_SHM_SH_TSSI_CCK);
	unsigned int a, b, c, d;
	unsigned int avewage;
	u32 tmp;

	tmp = b43_shm_wead32(dev, B43_SHM_SHAWED, shm_offset);
	a = tmp & 0xFF;
	b = (tmp >> 8) & 0xFF;
	c = (tmp >> 16) & 0xFF;
	d = (tmp >> 24) & 0xFF;
	if (a == 0 || a == B43_TSSI_MAX ||
	    b == 0 || b == B43_TSSI_MAX ||
	    c == 0 || c == B43_TSSI_MAX ||
	    d == 0 || d == B43_TSSI_MAX)
		wetuwn -ENOENT;
	/* The vawues awe OK. Cweaw them. */
	tmp = B43_TSSI_MAX | (B43_TSSI_MAX << 8) |
	      (B43_TSSI_MAX << 16) | (B43_TSSI_MAX << 24);
	b43_shm_wwite32(dev, B43_SHM_SHAWED, shm_offset, tmp);

	if (is_ofdm) {
		a = (a + 32) & 0x3F;
		b = (b + 32) & 0x3F;
		c = (c + 32) & 0x3F;
		d = (d + 32) & 0x3F;
	}

	/* Get the avewage of the vawues with 0.5 added to each vawue. */
	avewage = (a + b + c + d + 2) / 4;
	if (is_ofdm) {
		/* Adjust fow CCK-boost */
		if (b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF1)
		    & B43_HF_CCKBOOST)
			avewage = (avewage >= 13) ? (avewage - 13) : 0;
	}

	wetuwn avewage;
}

void b43_phyop_switch_anawog_genewic(stwuct b43_wwdev *dev, boow on)
{
	b43_wwite16(dev, B43_MMIO_PHY0, on ? 0 : 0xF4);
}


boow b43_is_40mhz(stwuct b43_wwdev *dev)
{
	wetuwn dev->phy.chandef->width == NW80211_CHAN_WIDTH_40;
}

/* https://bcm-v4.sipsowutions.net/802.11/PHY/N/BmacPhyCwkFgc */
void b43_phy_fowce_cwock(stwuct b43_wwdev *dev, boow fowce)
{
	u32 tmp;

	WAWN_ON(dev->phy.type != B43_PHYTYPE_N &&
		dev->phy.type != B43_PHYTYPE_HT &&
		dev->phy.type != B43_PHYTYPE_AC);

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		if (fowce)
			tmp |= BCMA_IOCTW_FGC;
		ewse
			tmp &= ~BCMA_IOCTW_FGC;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		if (fowce)
			tmp |= SSB_TMSWOW_FGC;
		ewse
			tmp &= ~SSB_TMSWOW_FGC;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		bweak;
#endif
	}
}
