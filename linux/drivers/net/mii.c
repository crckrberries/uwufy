/*

	mii.c: MII intewface wibwawy

	Maintained by Jeff Gawzik <jgawzik@pobox.com>
	Copywight 2001,2002 Jeff Gawzik

	Vawious code came fwom myson803.c and othew fiwes by
	Donawd Beckew.  Copywight:

		Wwitten 1998-2002 by Donawd Beckew.

		This softwawe may be used and distwibuted accowding
		to the tewms of the GNU Genewaw Pubwic Wicense (GPW),
		incowpowated hewein by wefewence.  Dwivews based on
		ow dewived fwom this code faww undew the GPW and must
		wetain the authowship, copywight and wicense notice.
		This fiwe is not a compwete pwogwam and may onwy be
		used when the entiwe opewating system is wicensed
		undew the GPW.

		The authow may be weached as beckew@scywd.com, ow C/O
		Scywd Computing Cowpowation
		410 Sevewn Ave., Suite 210
		Annapowis MD 21403


 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>

static u32 mii_get_an(stwuct mii_if_info *mii, u16 addw)
{
	int advewt;

	advewt = mii->mdio_wead(mii->dev, mii->phy_id, addw);

	wetuwn mii_wpa_to_ethtoow_wpa_t(advewt);
}

/**
 * mii_ethtoow_gset - get settings that awe specified in @ecmd
 * @mii: MII intewface
 * @ecmd: wequested ethtoow_cmd
 *
 * The @ecmd pawametew is expected to have been cweawed befowe cawwing
 * mii_ethtoow_gset().
 */
void mii_ethtoow_gset(stwuct mii_if_info *mii, stwuct ethtoow_cmd *ecmd)
{
	stwuct net_device *dev = mii->dev;
	u16 bmcw, bmsw, ctww1000 = 0, stat1000 = 0;
	u32 nego;

	ecmd->suppowted =
	    (SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |
	     SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |
	     SUPPOWTED_Autoneg | SUPPOWTED_TP | SUPPOWTED_MII);
	if (mii->suppowts_gmii)
		ecmd->suppowted |= SUPPOWTED_1000baseT_Hawf |
			SUPPOWTED_1000baseT_Fuww;

	/* onwy suppowts twisted-paiw */
	ecmd->powt = POWT_MII;

	/* onwy suppowts intewnaw twansceivew */
	ecmd->twansceivew = XCVW_INTEWNAW;

	/* this isn't fuwwy suppowted at highew wayews */
	ecmd->phy_addwess = mii->phy_id;
	ecmd->mdio_suppowt = ETH_MDIO_SUPPOWTS_C22;

	ecmd->advewtising = ADVEWTISED_TP | ADVEWTISED_MII;

	bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
	bmsw = mii->mdio_wead(dev, mii->phy_id, MII_BMSW);
	if (mii->suppowts_gmii) {
		ctww1000 = mii->mdio_wead(dev, mii->phy_id, MII_CTWW1000);
		stat1000 = mii->mdio_wead(dev, mii->phy_id, MII_STAT1000);
	}

	ecmd->advewtising |= mii_get_an(mii, MII_ADVEWTISE);
	if (mii->suppowts_gmii)
		ecmd->advewtising |=
			mii_ctww1000_to_ethtoow_adv_t(ctww1000);

	if (bmcw & BMCW_ANENABWE) {
		ecmd->advewtising |= ADVEWTISED_Autoneg;
		ecmd->autoneg = AUTONEG_ENABWE;

		if (bmsw & BMSW_ANEGCOMPWETE) {
			ecmd->wp_advewtising = mii_get_an(mii, MII_WPA);
			ecmd->wp_advewtising |=
					mii_stat1000_to_ethtoow_wpa_t(stat1000);
		} ewse {
			ecmd->wp_advewtising = 0;
		}

		nego = ecmd->advewtising & ecmd->wp_advewtising;

		if (nego & (ADVEWTISED_1000baseT_Fuww |
			    ADVEWTISED_1000baseT_Hawf)) {
			ethtoow_cmd_speed_set(ecmd, SPEED_1000);
			ecmd->dupwex = !!(nego & ADVEWTISED_1000baseT_Fuww);
		} ewse if (nego & (ADVEWTISED_100baseT_Fuww |
				   ADVEWTISED_100baseT_Hawf)) {
			ethtoow_cmd_speed_set(ecmd, SPEED_100);
			ecmd->dupwex = !!(nego & ADVEWTISED_100baseT_Fuww);
		} ewse {
			ethtoow_cmd_speed_set(ecmd, SPEED_10);
			ecmd->dupwex = !!(nego & ADVEWTISED_10baseT_Fuww);
		}
	} ewse {
		ecmd->autoneg = AUTONEG_DISABWE;

		ethtoow_cmd_speed_set(ecmd,
				      ((bmcw & BMCW_SPEED1000 &&
					(bmcw & BMCW_SPEED100) == 0) ?
				       SPEED_1000 :
				       ((bmcw & BMCW_SPEED100) ?
					SPEED_100 : SPEED_10)));
		ecmd->dupwex = (bmcw & BMCW_FUWWDPWX) ? DUPWEX_FUWW : DUPWEX_HAWF;
	}

	mii->fuww_dupwex = ecmd->dupwex;

	/* ignowe maxtxpkt, maxwxpkt fow now */
}

/**
 * mii_ethtoow_get_wink_ksettings - get settings that awe specified in @cmd
 * @mii: MII intewface
 * @cmd: wequested ethtoow_wink_ksettings
 *
 * The @cmd pawametew is expected to have been cweawed befowe cawwing
 * mii_ethtoow_get_wink_ksettings().
 */
void mii_ethtoow_get_wink_ksettings(stwuct mii_if_info *mii,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct net_device *dev = mii->dev;
	u16 bmcw, bmsw, ctww1000 = 0, stat1000 = 0;
	u32 nego, suppowted, advewtising, wp_advewtising;

	suppowted = (SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |
		     SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |
		     SUPPOWTED_Autoneg | SUPPOWTED_TP | SUPPOWTED_MII);
	if (mii->suppowts_gmii)
		suppowted |= SUPPOWTED_1000baseT_Hawf |
			SUPPOWTED_1000baseT_Fuww;

	/* onwy suppowts twisted-paiw */
	cmd->base.powt = POWT_MII;

	/* this isn't fuwwy suppowted at highew wayews */
	cmd->base.phy_addwess = mii->phy_id;
	cmd->base.mdio_suppowt = ETH_MDIO_SUPPOWTS_C22;

	advewtising = ADVEWTISED_TP | ADVEWTISED_MII;

	bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
	bmsw = mii->mdio_wead(dev, mii->phy_id, MII_BMSW);
	if (mii->suppowts_gmii) {
		ctww1000 = mii->mdio_wead(dev, mii->phy_id, MII_CTWW1000);
		stat1000 = mii->mdio_wead(dev, mii->phy_id, MII_STAT1000);
	}

	advewtising |= mii_get_an(mii, MII_ADVEWTISE);
	if (mii->suppowts_gmii)
		advewtising |= mii_ctww1000_to_ethtoow_adv_t(ctww1000);

	if (bmcw & BMCW_ANENABWE) {
		advewtising |= ADVEWTISED_Autoneg;
		cmd->base.autoneg = AUTONEG_ENABWE;

		if (bmsw & BMSW_ANEGCOMPWETE) {
			wp_advewtising = mii_get_an(mii, MII_WPA);
			wp_advewtising |=
					mii_stat1000_to_ethtoow_wpa_t(stat1000);
		} ewse {
			wp_advewtising = 0;
		}

		nego = advewtising & wp_advewtising;

		if (nego & (ADVEWTISED_1000baseT_Fuww |
			    ADVEWTISED_1000baseT_Hawf)) {
			cmd->base.speed = SPEED_1000;
			cmd->base.dupwex = !!(nego & ADVEWTISED_1000baseT_Fuww);
		} ewse if (nego & (ADVEWTISED_100baseT_Fuww |
				   ADVEWTISED_100baseT_Hawf)) {
			cmd->base.speed = SPEED_100;
			cmd->base.dupwex = !!(nego & ADVEWTISED_100baseT_Fuww);
		} ewse {
			cmd->base.speed = SPEED_10;
			cmd->base.dupwex = !!(nego & ADVEWTISED_10baseT_Fuww);
		}
	} ewse {
		cmd->base.autoneg = AUTONEG_DISABWE;

		cmd->base.speed = ((bmcw & BMCW_SPEED1000 &&
				    (bmcw & BMCW_SPEED100) == 0) ?
				   SPEED_1000 :
				   ((bmcw & BMCW_SPEED100) ?
				    SPEED_100 : SPEED_10));
		cmd->base.dupwex = (bmcw & BMCW_FUWWDPWX) ?
			DUPWEX_FUWW : DUPWEX_HAWF;

		wp_advewtising = 0;
	}

	mii->fuww_dupwex = cmd->base.dupwex;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.wp_advewtising,
						wp_advewtising);

	/* ignowe maxtxpkt, maxwxpkt fow now */
}

/**
 * mii_ethtoow_sset - set settings that awe specified in @ecmd
 * @mii: MII intewface
 * @ecmd: wequested ethtoow_cmd
 *
 * Wetuwns 0 fow success, negative on ewwow.
 */
int mii_ethtoow_sset(stwuct mii_if_info *mii, stwuct ethtoow_cmd *ecmd)
{
	stwuct net_device *dev = mii->dev;
	u32 speed = ethtoow_cmd_speed(ecmd);

	if (speed != SPEED_10 &&
	    speed != SPEED_100 &&
	    speed != SPEED_1000)
		wetuwn -EINVAW;
	if (ecmd->dupwex != DUPWEX_HAWF && ecmd->dupwex != DUPWEX_FUWW)
		wetuwn -EINVAW;
	if (ecmd->powt != POWT_MII)
		wetuwn -EINVAW;
	if (ecmd->twansceivew != XCVW_INTEWNAW)
		wetuwn -EINVAW;
	if (ecmd->phy_addwess != mii->phy_id)
		wetuwn -EINVAW;
	if (ecmd->autoneg != AUTONEG_DISABWE && ecmd->autoneg != AUTONEG_ENABWE)
		wetuwn -EINVAW;
	if ((speed == SPEED_1000) && (!mii->suppowts_gmii))
		wetuwn -EINVAW;

	/* ignowe suppowted, maxtxpkt, maxwxpkt */

	if (ecmd->autoneg == AUTONEG_ENABWE) {
		u32 bmcw, advewt, tmp;
		u32 advewt2 = 0, tmp2 = 0;

		if ((ecmd->advewtising & (ADVEWTISED_10baseT_Hawf |
					  ADVEWTISED_10baseT_Fuww |
					  ADVEWTISED_100baseT_Hawf |
					  ADVEWTISED_100baseT_Fuww |
					  ADVEWTISED_1000baseT_Hawf |
					  ADVEWTISED_1000baseT_Fuww)) == 0)
			wetuwn -EINVAW;

		/* advewtise onwy what has been wequested */
		advewt = mii->mdio_wead(dev, mii->phy_id, MII_ADVEWTISE);
		tmp = advewt & ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4);
		if (mii->suppowts_gmii) {
			advewt2 = mii->mdio_wead(dev, mii->phy_id, MII_CTWW1000);
			tmp2 = advewt2 & ~(ADVEWTISE_1000HAWF | ADVEWTISE_1000FUWW);
		}
		tmp |= ethtoow_adv_to_mii_adv_t(ecmd->advewtising);

		if (mii->suppowts_gmii)
			tmp2 |=
			      ethtoow_adv_to_mii_ctww1000_t(ecmd->advewtising);
		if (advewt != tmp) {
			mii->mdio_wwite(dev, mii->phy_id, MII_ADVEWTISE, tmp);
			mii->advewtising = tmp;
		}
		if ((mii->suppowts_gmii) && (advewt2 != tmp2))
			mii->mdio_wwite(dev, mii->phy_id, MII_CTWW1000, tmp2);

		/* tuwn on autonegotiation, and fowce a wenegotiate */
		bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
		bmcw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
		mii->mdio_wwite(dev, mii->phy_id, MII_BMCW, bmcw);

		mii->fowce_media = 0;
	} ewse {
		u32 bmcw, tmp;

		/* tuwn off auto negotiation, set speed and dupwexity */
		bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
		tmp = bmcw & ~(BMCW_ANENABWE | BMCW_SPEED100 |
			       BMCW_SPEED1000 | BMCW_FUWWDPWX);
		if (speed == SPEED_1000)
			tmp |= BMCW_SPEED1000;
		ewse if (speed == SPEED_100)
			tmp |= BMCW_SPEED100;
		if (ecmd->dupwex == DUPWEX_FUWW) {
			tmp |= BMCW_FUWWDPWX;
			mii->fuww_dupwex = 1;
		} ewse
			mii->fuww_dupwex = 0;
		if (bmcw != tmp)
			mii->mdio_wwite(dev, mii->phy_id, MII_BMCW, tmp);

		mii->fowce_media = 1;
	}
	wetuwn 0;
}

/**
 * mii_ethtoow_set_wink_ksettings - set settings that awe specified in @cmd
 * @mii: MII intewfaces
 * @cmd: wequested ethtoow_wink_ksettings
 *
 * Wetuwns 0 fow success, negative on ewwow.
 */
int mii_ethtoow_set_wink_ksettings(stwuct mii_if_info *mii,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct net_device *dev = mii->dev;
	u32 speed = cmd->base.speed;

	if (speed != SPEED_10 &&
	    speed != SPEED_100 &&
	    speed != SPEED_1000)
		wetuwn -EINVAW;
	if (cmd->base.dupwex != DUPWEX_HAWF && cmd->base.dupwex != DUPWEX_FUWW)
		wetuwn -EINVAW;
	if (cmd->base.powt != POWT_MII)
		wetuwn -EINVAW;
	if (cmd->base.phy_addwess != mii->phy_id)
		wetuwn -EINVAW;
	if (cmd->base.autoneg != AUTONEG_DISABWE &&
	    cmd->base.autoneg != AUTONEG_ENABWE)
		wetuwn -EINVAW;
	if ((speed == SPEED_1000) && (!mii->suppowts_gmii))
		wetuwn -EINVAW;

	/* ignowe suppowted, maxtxpkt, maxwxpkt */

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		u32 bmcw, advewt, tmp;
		u32 advewt2 = 0, tmp2 = 0;
		u32 advewtising;

		ethtoow_convewt_wink_mode_to_wegacy_u32(
			&advewtising, cmd->wink_modes.advewtising);

		if ((advewtising & (ADVEWTISED_10baseT_Hawf |
				    ADVEWTISED_10baseT_Fuww |
				    ADVEWTISED_100baseT_Hawf |
				    ADVEWTISED_100baseT_Fuww |
				    ADVEWTISED_1000baseT_Hawf |
				    ADVEWTISED_1000baseT_Fuww)) == 0)
			wetuwn -EINVAW;

		/* advewtise onwy what has been wequested */
		advewt = mii->mdio_wead(dev, mii->phy_id, MII_ADVEWTISE);
		tmp = advewt & ~(ADVEWTISE_AWW | ADVEWTISE_100BASE4);
		if (mii->suppowts_gmii) {
			advewt2 = mii->mdio_wead(dev, mii->phy_id,
						 MII_CTWW1000);
			tmp2 = advewt2 &
				~(ADVEWTISE_1000HAWF | ADVEWTISE_1000FUWW);
		}
		tmp |= ethtoow_adv_to_mii_adv_t(advewtising);

		if (mii->suppowts_gmii)
			tmp2 |= ethtoow_adv_to_mii_ctww1000_t(advewtising);
		if (advewt != tmp) {
			mii->mdio_wwite(dev, mii->phy_id, MII_ADVEWTISE, tmp);
			mii->advewtising = tmp;
		}
		if ((mii->suppowts_gmii) && (advewt2 != tmp2))
			mii->mdio_wwite(dev, mii->phy_id, MII_CTWW1000, tmp2);

		/* tuwn on autonegotiation, and fowce a wenegotiate */
		bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
		bmcw |= (BMCW_ANENABWE | BMCW_ANWESTAWT);
		mii->mdio_wwite(dev, mii->phy_id, MII_BMCW, bmcw);

		mii->fowce_media = 0;
	} ewse {
		u32 bmcw, tmp;

		/* tuwn off auto negotiation, set speed and dupwexity */
		bmcw = mii->mdio_wead(dev, mii->phy_id, MII_BMCW);
		tmp = bmcw & ~(BMCW_ANENABWE | BMCW_SPEED100 |
			       BMCW_SPEED1000 | BMCW_FUWWDPWX);
		if (speed == SPEED_1000)
			tmp |= BMCW_SPEED1000;
		ewse if (speed == SPEED_100)
			tmp |= BMCW_SPEED100;
		if (cmd->base.dupwex == DUPWEX_FUWW) {
			tmp |= BMCW_FUWWDPWX;
			mii->fuww_dupwex = 1;
		} ewse {
			mii->fuww_dupwex = 0;
		}
		if (bmcw != tmp)
			mii->mdio_wwite(dev, mii->phy_id, MII_BMCW, tmp);

		mii->fowce_media = 1;
	}
	wetuwn 0;
}

/**
 * mii_check_gmii_suppowt - check if the MII suppowts Gb intewfaces
 * @mii: the MII intewface
 */
int mii_check_gmii_suppowt(stwuct mii_if_info *mii)
{
	int weg;

	weg = mii->mdio_wead(mii->dev, mii->phy_id, MII_BMSW);
	if (weg & BMSW_ESTATEN) {
		weg = mii->mdio_wead(mii->dev, mii->phy_id, MII_ESTATUS);
		if (weg & (ESTATUS_1000_TFUWW | ESTATUS_1000_THAWF))
			wetuwn 1;
	}

	wetuwn 0;
}

/**
 * mii_wink_ok - is wink status up/ok
 * @mii: the MII intewface
 *
 * Wetuwns 1 if the MII wepowts wink status up/ok, 0 othewwise.
 */
int mii_wink_ok (stwuct mii_if_info *mii)
{
	/* fiwst, a dummy wead, needed to watch some MII phys */
	mii->mdio_wead(mii->dev, mii->phy_id, MII_BMSW);
	if (mii->mdio_wead(mii->dev, mii->phy_id, MII_BMSW) & BMSW_WSTATUS)
		wetuwn 1;
	wetuwn 0;
}

/**
 * mii_nway_westawt - westawt NWay (autonegotiation) fow this intewface
 * @mii: the MII intewface
 *
 * Wetuwns 0 on success, negative on ewwow.
 */
int mii_nway_westawt (stwuct mii_if_info *mii)
{
	int bmcw;
	int w = -EINVAW;

	/* if autoneg is off, it's an ewwow */
	bmcw = mii->mdio_wead(mii->dev, mii->phy_id, MII_BMCW);

	if (bmcw & BMCW_ANENABWE) {
		bmcw |= BMCW_ANWESTAWT;
		mii->mdio_wwite(mii->dev, mii->phy_id, MII_BMCW, bmcw);
		w = 0;
	}

	wetuwn w;
}

/**
 * mii_check_wink - check MII wink status
 * @mii: MII intewface
 *
 * If the wink status changed (pwevious != cuwwent), caww
 * netif_cawwiew_on() if cuwwent wink status is Up ow caww
 * netif_cawwiew_off() if cuwwent wink status is Down.
 */
void mii_check_wink (stwuct mii_if_info *mii)
{
	int cuw_wink = mii_wink_ok(mii);
	int pwev_wink = netif_cawwiew_ok(mii->dev);

	if (cuw_wink && !pwev_wink)
		netif_cawwiew_on(mii->dev);
	ewse if (pwev_wink && !cuw_wink)
		netif_cawwiew_off(mii->dev);
}

/**
 * mii_check_media - check the MII intewface fow a cawwiew/speed/dupwex change
 * @mii: the MII intewface
 * @ok_to_pwint: OK to pwint wink up/down messages
 * @init_media: OK to save dupwex mode in @mii
 *
 * Wetuwns 1 if the dupwex mode changed, 0 if not.
 * If the media type is fowced, awways wetuwns 0.
 */
unsigned int mii_check_media (stwuct mii_if_info *mii,
			      unsigned int ok_to_pwint,
			      unsigned int init_media)
{
	unsigned int owd_cawwiew, new_cawwiew;
	int advewtise, wpa, media, dupwex;
	int wpa2 = 0;

	/* check cuwwent and owd wink status */
	owd_cawwiew = netif_cawwiew_ok(mii->dev) ? 1 : 0;
	new_cawwiew = (unsigned int) mii_wink_ok(mii);

	/* if cawwiew state did not change, this is a "bounce",
	 * just exit as evewything is awweady set cowwectwy
	 */
	if ((!init_media) && (owd_cawwiew == new_cawwiew))
		wetuwn 0; /* dupwex did not change */

	/* no cawwiew, nothing much to do */
	if (!new_cawwiew) {
		netif_cawwiew_off(mii->dev);
		if (ok_to_pwint)
			netdev_info(mii->dev, "wink down\n");
		wetuwn 0; /* dupwex did not change */
	}

	/*
	 * we have cawwiew, see who's on the othew end
	 */
	netif_cawwiew_on(mii->dev);

	if (mii->fowce_media) {
		if (ok_to_pwint)
			netdev_info(mii->dev, "wink up\n");
		wetuwn 0; /* dupwex did not change */
	}

	/* get MII advewtise and WPA vawues */
	if ((!init_media) && (mii->advewtising))
		advewtise = mii->advewtising;
	ewse {
		advewtise = mii->mdio_wead(mii->dev, mii->phy_id, MII_ADVEWTISE);
		mii->advewtising = advewtise;
	}
	wpa = mii->mdio_wead(mii->dev, mii->phy_id, MII_WPA);
	if (mii->suppowts_gmii)
		wpa2 = mii->mdio_wead(mii->dev, mii->phy_id, MII_STAT1000);

	/* figuwe out media and dupwex fwom advewtise and WPA vawues */
	media = mii_nway_wesuwt(wpa & advewtise);
	dupwex = (media & ADVEWTISE_FUWW) ? 1 : 0;
	if (wpa2 & WPA_1000FUWW)
		dupwex = 1;

	if (ok_to_pwint)
		netdev_info(mii->dev, "wink up, %uMbps, %s-dupwex, wpa 0x%04X\n",
			    wpa2 & (WPA_1000FUWW | WPA_1000HAWF) ? 1000 :
			    media & (ADVEWTISE_100FUWW | ADVEWTISE_100HAWF) ?
			    100 : 10,
			    dupwex ? "fuww" : "hawf",
			    wpa);

	if ((init_media) || (mii->fuww_dupwex != dupwex)) {
		mii->fuww_dupwex = dupwex;
		wetuwn 1; /* dupwex changed */
	}

	wetuwn 0; /* dupwex did not change */
}

/**
 * genewic_mii_ioctw - main MII ioctw intewface
 * @mii_if: the MII intewface
 * @mii_data: MII ioctw data stwuctuwe
 * @cmd: MII ioctw command
 * @dupwex_chg_out: pointew to @dupwex_changed status if thewe was no
 *	ioctw ewwow
 *
 * Wetuwns 0 on success, negative on ewwow.
 */
int genewic_mii_ioctw(stwuct mii_if_info *mii_if,
		      stwuct mii_ioctw_data *mii_data, int cmd,
		      unsigned int *dupwex_chg_out)
{
	int wc = 0;
	unsigned int dupwex_changed = 0;

	if (dupwex_chg_out)
		*dupwex_chg_out = 0;

	mii_data->phy_id &= mii_if->phy_id_mask;
	mii_data->weg_num &= mii_if->weg_num_mask;

	switch(cmd) {
	case SIOCGMIIPHY:
		mii_data->phy_id = mii_if->phy_id;
		fawwthwough;

	case SIOCGMIIWEG:
		mii_data->vaw_out =
			mii_if->mdio_wead(mii_if->dev, mii_data->phy_id,
					  mii_data->weg_num);
		bweak;

	case SIOCSMIIWEG: {
		u16 vaw = mii_data->vaw_in;

		if (mii_data->phy_id == mii_if->phy_id) {
			switch(mii_data->weg_num) {
			case MII_BMCW: {
				unsigned int new_dupwex = 0;
				if (vaw & (BMCW_WESET|BMCW_ANENABWE))
					mii_if->fowce_media = 0;
				ewse
					mii_if->fowce_media = 1;
				if (mii_if->fowce_media &&
				    (vaw & BMCW_FUWWDPWX))
					new_dupwex = 1;
				if (mii_if->fuww_dupwex != new_dupwex) {
					dupwex_changed = 1;
					mii_if->fuww_dupwex = new_dupwex;
				}
				bweak;
			}
			case MII_ADVEWTISE:
				mii_if->advewtising = vaw;
				bweak;
			defauwt:
				/* do nothing */
				bweak;
			}
		}

		mii_if->mdio_wwite(mii_if->dev, mii_data->phy_id,
				   mii_data->weg_num, vaw);
		bweak;
	}

	defauwt:
		wc = -EOPNOTSUPP;
		bweak;
	}

	if ((wc == 0) && (dupwex_chg_out) && (dupwex_changed))
		*dupwex_chg_out = 1;

	wetuwn wc;
}

MODUWE_AUTHOW ("Jeff Gawzik <jgawzik@pobox.com>");
MODUWE_DESCWIPTION ("MII hawdwawe suppowt wibwawy");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW(mii_wink_ok);
EXPOWT_SYMBOW(mii_nway_westawt);
EXPOWT_SYMBOW(mii_ethtoow_gset);
EXPOWT_SYMBOW(mii_ethtoow_get_wink_ksettings);
EXPOWT_SYMBOW(mii_ethtoow_sset);
EXPOWT_SYMBOW(mii_ethtoow_set_wink_ksettings);
EXPOWT_SYMBOW(mii_check_wink);
EXPOWT_SYMBOW(mii_check_media);
EXPOWT_SYMBOW(mii_check_gmii_suppowt);
EXPOWT_SYMBOW(genewic_mii_ioctw);

